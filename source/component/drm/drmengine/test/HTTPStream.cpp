//
// Copyright 2013 Google Inc. All Rights Reserved.
//

//#define LOG_NDEBUG 0
#define LOG_TAG "HTTPStream"
#include <utils/Logger.h>

#include "HTTPStream.h"

#include <sys/socket.h>

#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <ADebug.h>
#include <ALooper.h>
#include <DrmErrors.h>

#include <openssl/ssl.h>

namespace {

using android::AString;
using android::status_t;
using android::Compare_EQ;

bool MakeSocketBlocking(int s, bool blocking) {
    // Make socket non-blocking.
    int flags = fcntl(s, F_GETFL, 0);
    if (flags == -1) {
        return false;
    }

    if (blocking) {
        flags &= ~O_NONBLOCK;
    } else {
        flags |= O_NONBLOCK;
    }

    return fcntl(s, F_SETFL, flags) != -1;
}

status_t MyConnect(int s, const struct sockaddr *addr, socklen_t addrlen, int timeout) {
    status_t result = android::UNKNOWN_ERROR;

    MakeSocketBlocking(s, false);

    if (connect(s, addr, addrlen) == 0) {
        result = android::OK;
    } else if (errno != EINPROGRESS) {
        result = -errno;
    } else {
      struct timespec end_time;
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      end_time.tv_sec += timeout;
        for (;;) {
            fd_set rs, ws;
            FD_ZERO(&rs);
            FD_ZERO(&ws);
            FD_SET(s, &rs);
            FD_SET(s, &ws);

            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = 100000ll;

            int nfds = ::select(s + 1, &rs, &ws, NULL, &tv);

            if (nfds < 0) {
                if (errno == EINTR) {
                    continue;
                }

                result = -errno;
                break;
            }

            if (FD_ISSET(s, &ws) && !FD_ISSET(s, &rs)) {
                result = android::OK;
                break;
            }

            if (FD_ISSET(s, &rs) || FD_ISSET(s, &ws)) {
                // Get the pending error.
                int error = 0;
                socklen_t errorLen = sizeof(error);
                if (getsockopt(s, SOL_SOCKET, SO_ERROR, &error, &errorLen) == -1) {
                    // Couldn't get the real error, so report why not.
                    result = -errno;
                } else {
                    result = -error;
                }
                break;
            }

            // Timeout expired. Try again.
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            if (now.tv_sec >= end_time.tv_sec) {
              if ((now.tv_sec > end_time.tv_sec) ||
                  (now.tv_nsec >= end_time.tv_nsec)) {
                result = ERROR_CONNECTION_LOST;
                break;
              }
            }
        }
    }

    MakeSocketBlocking(s, true);

    return result;
}

// Apparently under out linux closing a socket descriptor from one thread
// will not unblock a pending send/recv on that socket on another thread.
ssize_t MySendReceive(int s, void *data, size_t size, int flags, bool sendData, int timeout) {
    ssize_t result = 0;

    if (s < 0) {
        return -1;
    }
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    end_time.tv_sec += timeout;
    while (size > 0) {
        fd_set rs, ws, es;
        FD_ZERO(&rs);
        FD_ZERO(&ws);
        FD_ZERO(&es);
        FD_SET(s, sendData ? &ws : &rs);
        FD_SET(s, &es);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000ll;

        int nfds = ::select(
                s + 1,
                sendData ? NULL : &rs,
                sendData ? &ws : NULL,
                &es,
                &tv);

        if (nfds < 0) {
            if (errno == EINTR) {
                continue;
            }

            result = -errno;
            break;
        } else if (nfds == 0) {
            // timeout
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            if (now.tv_sec >= end_time.tv_sec) {
              if ((now.tv_sec > end_time.tv_sec) ||
                  (now.tv_nsec >= end_time.tv_nsec)) {
                result = ERROR_CONNECTION_LOST;
                break;
              }
            }
            continue;
        }

        CHECK_EQ(nfds, 1);

        ssize_t nbytes =
            sendData ? send(s, data, size, flags) : recv(s, data, size, flags);

        if (nbytes < 0) {
            if (errno == EINTR) {
                continue;
            }

            result = -errno;
            break;
        } else if (nbytes == 0) {
            result = 0;
            break;
        }

        data = (uint8_t *)data + nbytes;
        size -= nbytes;

        result = nbytes;
        break;
    }

    return result;
}

ssize_t MySend(int s, const void *data, size_t size, int flags, int timeout) {
    return MySendReceive(s, const_cast<void *>(data), size, flags, true /* sendData */,
                         timeout);
}

ssize_t MyReceive(int s, void *data, size_t size, int flags, int timeout) {
    return MySendReceive(s, data, size, flags, false /* sendData */, timeout);
}

} // namespace anonymous

namespace android {

// static
const char *HTTPStream::kStatusKey = ":status:";  // MUST be lowercase.

HTTPStream::HTTPStream()
    : mState(READY),
      mSocket(-1),
      mTimeoutSec(30),
      mSSLContext(NULL),
      mSSL(NULL),
      mTotalDownloadTimeoutSec(0) {
}

HTTPStream::~HTTPStream() {
    disconnect();

    if (mSSLContext != NULL) {
        SSL_CTX_free((SSL_CTX *)mSSLContext);
        mSSLContext = NULL;
    }
}

status_t HTTPStream::connect(const char *server, int port, bool https) {
    HI_LOGD("%s >>", __PRETTY_FUNCTION__);
    if (port < 0) {
        port = https ? 443 : 80;
    }

    Mutex::Autolock autoLock(mLock);

    //status_t err = OK;

    if (mState == CONNECTED) {
        HI_LOGE("connect() failed with ERROR_ALREADY_CONNECTED");
        return ERROR_ALREADY_CONNECTED;
    }

    struct hostent *ent = gethostbyname(server);
    if (ent == NULL) {
        HI_LOGE("connect() failed with ERROR_UNKNONW_HOST");
        return ERROR_UNKNOWN_HOST;
    }

    CHECK_EQ(mSocket, -1);
    mSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (mSocket < 0) {
        HI_LOGE("connect() failed with UNKNONW_ERROR in socket");
        return UNKNOWN_ERROR;
    }

    setReceiveTimeout(30);  // Time out reads after 30 secs by default

    mState = CONNECTING;

    int s = mSocket;

    mLock.unlock();

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(in_addr_t *)ent->h_addr;
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));

    status_t res = MyConnect(s, (const struct sockaddr *)&addr, sizeof(addr),
                             mTimeoutSec);

    mLock.lock();

    if (mState != CONNECTING) {
        HI_LOGE("connect() failed with UNKNONW_ERROR");
        return UNKNOWN_ERROR;
    }

    if (res != OK) {
        HI_LOGE("MyConnect() failed with %d", res);
        close(mSocket);
        mSocket = -1;

        mState = READY;
        return res;
    }

    if (https) {
        CHECK(mSSL == NULL);

        if (mSSLContext == NULL) {
            SSL_library_init();

            mSSLContext = SSL_CTX_new(TLSv1_client_method());

            if (mSSLContext == NULL) {
                HI_LOGE("failed to create SSL context");
                mState = READY;
                return ERROR_IO;
            }
        }

        mSSL = SSL_new((SSL_CTX *)mSSLContext);

        if (mSSL == NULL) {
            HI_LOGE("failed to create SSL session");

            mState = READY;
            return ERROR_IO;
        }

        int res = SSL_set_fd((SSL *)mSSL, mSocket);

        if (res == 1) {
            res = SSL_connect((SSL *)mSSL);
        }

        if (res != 1) {
            SSL_free((SSL *)mSSL);
            mSSL = NULL;

            HI_LOGE("failed to connect over SSL");
            mState = READY;

            return ERROR_IO;
        }
    }

    mState = CONNECTED;

    return OK;
}

status_t HTTPStream::disconnect() {
    Mutex::Autolock autoLock(mLock);

    if (mState != CONNECTED && mState != CONNECTING) {
        return ERROR_NOT_CONNECTED;
    }

    if (mSSL != NULL) {
        SSL_shutdown((SSL *)mSSL);

        SSL_free((SSL *)mSSL);
        mSSL = NULL;
    }

    CHECK(mSocket >= 0);
    close(mSocket);
    mSocket = -1;

    mState = READY;

    return OK;
}

status_t HTTPStream::send(const char *data, size_t size) {
    if (mState != CONNECTED) {
        return ERROR_NOT_CONNECTED;
    }

    while (size > 0) {
        ssize_t n;
        if (mSSL != NULL) {
            n = SSL_write((SSL *)mSSL, data, size);

            if (n < 0) {
                n = -SSL_get_error((SSL *)mSSL, n);
            }
        } else {
            n = MySend(mSocket, data, size, 0, mTimeoutSec);
        }

        if (n < 0) {
            disconnect();

            return n;
        } else if (n == 0) {
            disconnect();

            return ERROR_CONNECTION_LOST;
        }

        size -= (size_t)n;
        data += (size_t)n;
    }

    return OK;
}

status_t HTTPStream::send(const char *data) {
    return send(data, strlen(data));
}

// A certain application spawns a local webserver that sends invalid responses,
// specifically it terminates header line with only a newline instead of the
// CRLF (carriage-return followed by newline) required by the HTTP specs.
// The workaround accepts both behaviours but could potentially break
// legitimate responses that use a single newline to "fold" headers, which is
// why it's not yet on by default.
#define WORKAROUND_FOR_MISSING_CR       1

status_t HTTPStream::receive_line(char *line, size_t size) {
    if (mState != CONNECTED) {
        return ERROR_NOT_CONNECTED;
    }

    bool saw_CR = false;
    size_t length = 0;

    for (;;) {
        char c;
        ssize_t n;
        if (mSSL != NULL) {
            n = SSL_read((SSL *)mSSL, &c, 1);

            if (n < 0) {
                n = -SSL_get_error((SSL *)mSSL, n);
            }
        } else {
            n = MyReceive(mSocket, &c, 1, 0, mTimeoutSec);
        }

        if (n < 0) {
            disconnect();

            return ERROR_IO;
        } else if (n == 0) {
            disconnect();

            return ERROR_CONNECTION_LOST;
        }

#if WORKAROUND_FOR_MISSING_CR
        if (c == '\n') {
            // We have a complete line.

            line[saw_CR ? length - 1 : length] = '\0';
            return OK;
        }
#else
        if (saw_CR &&  c == '\n') {
            // We have a complete line.

            line[length - 1] = '\0';
            return OK;
        }
#endif

        saw_CR = (c == '\r');

        if (length + 1 >= size) {
            return ERROR_MALFORMED;
        }
        line[length++] = c;
    }
}

status_t HTTPStream::receive_header(int *http_status) {
    *http_status = -1;
    mHeaders.clear();

    char line[2048];
    status_t err = receive_line(line, sizeof(line));
    if (err != OK) {
        return err;
    }

    mHeaders.add(AString(kStatusKey), AString(line));

    char *spacePos = strchr(line, ' ');
    if (spacePos == NULL) {
        // Malformed response?
        return UNKNOWN_ERROR;
    }

    char *status_start = spacePos + 1;
    char *status_end = status_start;
    while (isdigit(*status_end)) {
        ++status_end;
    }

    if (status_end == status_start) {
        // Malformed response, status missing?
        return UNKNOWN_ERROR;
    }

    memmove(line, status_start, status_end - status_start);
    line[status_end - status_start] = '\0';

    long tmp = strtol(line, NULL, 10);
    if (tmp < 0 || tmp > 999) {
        return UNKNOWN_ERROR;
    }

    *http_status = (int)tmp;

    for (;;) {
        err = receive_line(line, sizeof(line));
        if (err != OK) {
            return err;
        }

        if (*line == '\0') {
            // Empty line signals the end of the header.
            break;
        }

        // puts(line);

        char *colonPos = strchr(line, ':');
        if (colonPos == NULL) {
            AString key = line;
            key.tolower();

            mHeaders.add(key, AString());
        } else {
            char *end_of_key = colonPos;
            while (end_of_key > line && isspace(end_of_key[-1])) {
                --end_of_key;
            }

            char *start_of_value = colonPos + 1;
            while (isspace(*start_of_value)) {
                ++start_of_value;
            }

            *end_of_key = '\0';

            AString key = line;
            key.tolower();

            mHeaders.add(key, AString(start_of_value));
        }
    }

    return OK;
}

ssize_t HTTPStream::receive(void *data, size_t size) {
    size_t total = 0;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    end_time.tv_sec += mTotalDownloadTimeoutSec;
    while (total < size) {
        if (mTotalDownloadTimeoutSec != 0) {
            struct timespec now;
            clock_gettime(CLOCK_MONOTONIC, &now);
            if (now.tv_sec >= end_time.tv_sec) {
                if ((now.tv_sec > end_time.tv_sec) ||
                        (now.tv_nsec >= end_time.tv_nsec)) {
                    disconnect();
                    HI_LOGE("Timeout by total download timeout");
                    return (ssize_t)ERROR_CONNECTION_LOST;
                }
            }
        }

        ssize_t n;
        if (mSSL != NULL) {
            n = SSL_read((SSL *)mSSL, (char *)data + total, size - total);

            if (n < 0) {
                n = -SSL_get_error((SSL *)mSSL, n);
            }
        } else {
            n = MyReceive(mSocket, (char *)data + total, size - total, 0,
                          mTimeoutSec);
        }

        if (n < 0) {
            HI_LOGE("recv failed, errno = %d (%s)", (int)n, strerror(-n));

            disconnect();
            return (ssize_t)ERROR_IO;
        } else if (n == 0) {
            disconnect();

            HI_LOGE("recv failed, server is gone, total received: %d bytes",
                 total);

            return total == 0 ? (ssize_t)ERROR_CONNECTION_LOST : total;
        }

        total += (size_t)n;
    }

    return (ssize_t)total;
}

bool HTTPStream::find_header_value(const AString &key, AString *value) const {
    AString key_lower = key;
    key_lower.tolower();

    ssize_t index = mHeaders.indexOfKey(key_lower);
    if (index < 0) {
        value->clear();
        return false;
    }

    *value = mHeaders.valueAt(index);

    return true;
}

void HTTPStream::setReceiveTimeout(int seconds) {
    if (seconds < 0) {
        // Disable the timeout.
        seconds = 0;
    }

    mTimeoutSec = seconds;
    struct timeval tv;
    tv.tv_usec = 0;
    tv.tv_sec = seconds;
    CHECK_EQ(0, setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)));
}

}  // namespace android
