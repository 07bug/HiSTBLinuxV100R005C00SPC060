//
// Copyright 2013 Google Inc. All Rights Reserved.
//

//#define LOG_NDEBUG 0
#define LOG_TAG "HTTPSource"
#include <utils/Logger.h>

#include "HTTPSource.h"

#include <cutils/properties.h>
#include <ALooper.h>
#include <ADebug.h>
#include <AString.h>
#include <DrmErrors.h>

namespace {

using android::String8;

const int kDefaultMaxRedirects = 5;

bool ParseSingleUnsignedLong(const char *from, unsigned long *x) {
    char *end;
    *x = strtoul(from, &end, 10);

    if (end == from || *end != '\0') {
        return false;
    }

    return true;
}

bool ParseURL(const char *url, String8 *host, unsigned *port,
              String8 *path, bool *https) {
    host->setTo("");
    *port = 0;
    path->setTo("");

    size_t hostStart;
    if (!strncasecmp("http://", url, 7)) {
        hostStart = 7;
        *https = false;
    } else if (!strncasecmp("https://", url, 8)) {
        hostStart = 8;
        *https = true;
    } else {
        return false;
    }

    const char *slashPos = strchr(&url[hostStart], '/');

    if (slashPos == NULL) {
        host->setTo(&url[hostStart]);
        path->setTo("/");
    } else {
        host->setTo(&url[hostStart], slashPos - &url[hostStart]);
        path->setTo(slashPos);
    }

    const char *colonPos = strchr(host->string(), ':');

    if (colonPos != NULL) {
        unsigned long x;
        if (!ParseSingleUnsignedLong(colonPos + 1, &x) || x >= 65536) {
            return false;
        }

        *port = x;

        size_t colonOffset = colonPos - host->string();
        String8 tmp(host->string(), colonOffset);
        *host = tmp;
    } else {
        *port = (*https) ? 443 : 80;
    }

    return true;
}

bool IsRedirectStatusCode(int httpStatus) {
    return httpStatus == 301 || httpStatus == 302 || httpStatus == 303 || httpStatus == 307;
}

} // namespace anonymous

namespace android {

HTTPSource::HTTPSource(uint32_t flags) : mFlags(flags),
        mState(DISCONNECTED), mPort(0), mHTTPS(false), mOffset(0), mContentLength(0),
        mContentLengthValid(false), mHasChunkedTransferEncoding(false), mChunkDataBytesLeft(0),
        mRedirectCount(0), mMaxRedirectCount(kDefaultMaxRedirects) {
}

HTTPSource::~HTTPSource() {
}

status_t HTTPSource::connect(const char *uri, const KeyedVector<String8, String8> *overrides,
                             off64_t offset, const char *postData) {
    String8 headers;
    if (mUserAgentHeader.isEmpty()) {
      // This code was moved from MakeFullHeaders to allow for setting of
      // custom user agent string
      mUserAgentHeader = "User-Agent: stagefright/1.1 (Linux;Android ";
    }
    MakeFullHeaders(overrides, &headers, &mUserAgentHeader);
    mRedirectCount = 0;
    return connect(uri, headers, offset, postData);
}

status_t HTTPSource::connect(const char *uri, const String8 &headers, off64_t offset,
                             const char *postData) {
    String8 host, path;
    unsigned port;

    mUri = uri;

    bool https;
    if (!ParseURL(uri, &host, &port, &path, &https)) {
        HI_LOGE("HTTPSource::connet() failed with malformed URL");
        return ERROR_MALFORMED;
    }

    return connect(host, port, path, https, headers, offset, postData);
}

status_t HTTPSource::connect(const char *host, unsigned port, const char *path, bool https,
                             const String8 &headers, off64_t offset, const char *postData) {
    if (!(mFlags & kFlagIncognito)) {
        HI_LOGI("connect to %s:%u%s @%lld", host, port, path, offset);
    } else {
        HI_LOGI("connect to <URL suppressed> @%lld", offset);
    }

    bool needsToReconnect = true;

    if (mState == CONNECTED && host == mHost && port == mPort
            && https == mHTTPS && offset == mOffset) {
        if (mContentLengthValid && mOffset == mContentLength) {
            HI_LOGI("Didn't have to reconnect, old one's still good.");
            needsToReconnect = false;
        }
    }

    mHost = host;
    mPort = port;
    mPath = path;
    mHTTPS = https;
    mHeaders = headers;

    status_t err = OK;

    mState = CONNECTING;

    if (needsToReconnect) {
        mHTTP.disconnect();
        err = mHTTP.connect(host, port, https);
    }

    if (err != OK) {
        mState = DISCONNECTED;
    } else if (mState != CONNECTING) {
        err = UNKNOWN_ERROR;
    } else {
        mState = CONNECTED;

        mOffset = offset;
        mContentLength = 0;
        mContentLengthValid = false;

        String8 request(postData == NULL ? "GET " : "POST ");
        request.append(mPath);
        request.append(" HTTP/1.1\r\n");
        request.append("Host: ");
        request.append(mHost);
        if (mPort != 80) {
            request.append(AStringPrintf(":%u", mPort).c_str());
        }
        request.append("\r\n");

        if (offset != 0) {
            char rangeHeader[128];
            sprintf(rangeHeader, "Range: bytes=%lld-\r\n", offset);
            request.append(rangeHeader);
        }

        request.append(mHeaders);

        if (postData != NULL) {
            char lengthHeader[128];
            sprintf(lengthHeader, "Content-Length: %d\r\n", strlen(postData));
            request.append(lengthHeader);
        }

        request.append("\r\n");

        if (postData != NULL) {
            request.append(postData);
        }

        int httpStatus;
        if ((err = mHTTP.send(request.string(), request.size())) != OK
                || (err = mHTTP.receive_header(&httpStatus)) != OK) {
            mHTTP.disconnect();
            mState = DISCONNECTED;
            return err;
        }

        if (IsRedirectStatusCode(httpStatus)) {
            AString value;
            CHECK(mHTTP.find_header_value("Location", &value));

            mState = DISCONNECTED;

            mHTTP.disconnect();

            // GTV changes(ftsui):
            // need to set a max redirect count.
            if (mMaxRedirectCount != 0 && mRedirectCount < mMaxRedirectCount) {
              mRedirectCount++;
              return connect(value.c_str(), headers, offset, postData);
            } else {
              HI_LOGE("HTTP request exceeded max redirect count");
              return ERROR_IO;
            }
        }

        mRedirectCount = 0;
        if (httpStatus < 200 || httpStatus >= 300) {
            mState = DISCONNECTED;
            mHTTP.disconnect();

            return ERROR_IO;
        }

        mHasChunkedTransferEncoding = false;

        {
            AString value;
            if (mHTTP.find_header_value("Transfer-Encoding", &value)) {
                // We don't currently support any transfer encodings but
                // chunked.

                if (!strcasecmp(value.c_str(), "chunked")) {
                    HI_LOGI("Chunked transfer encoding applied.");
                    mHasChunkedTransferEncoding = true;
                    mChunkDataBytesLeft = 0;
                } else {
                    mState = DISCONNECTED;
                    mHTTP.disconnect();

                    HI_LOGE("We don't support '%s' transfer encoding.", value.c_str());

                    return ERROR_UNSUPPORTED;
                }
            }
        }

        applyTimeoutResponse();

        if (offset == 0) {
            AString value;
            unsigned long x;
            if (mHTTP.find_header_value(AString("Content-Length"), &value)
                    && ParseSingleUnsignedLong(value.c_str(), &x)) {
                mContentLength = (off64_t)x;
                mContentLengthValid = true;
            } else {
                HI_LOGW("Server did not give us the content length!");
            }
        } else {
            if (httpStatus != 206 /* Partial Content */) {
                // We requested a range but the server didn't support that.
                HI_LOGE("We requested a range but the server didn't "
                     "support that.");
                return ERROR_UNSUPPORTED;
            }

            AString value;
            unsigned long x;
            if (mHTTP.find_header_value(AString("Content-Range"), &value)) {
                const char *slashPos = strchr(value.c_str(), '/');
                if (slashPos != NULL
                        && ParseSingleUnsignedLong(slashPos + 1, &x)) {
                    mContentLength = x;
                    mContentLengthValid = true;
                }
            }
        }
    }

    return err;
}

void HTTPSource::disconnect() {
    if (mState == CONNECTING || mState == CONNECTED) {
        mHTTP.disconnect();
    }
    mState = DISCONNECTED;
}

ssize_t HTTPSource::internalRead(void *data, size_t size) {
    if (!mHasChunkedTransferEncoding) {
        return mHTTP.receive(data, size);
    }

    if (mChunkDataBytesLeft < 0) {
        return 0;
    } else if (mChunkDataBytesLeft == 0) {
        char line[1024];
        status_t err = mHTTP.receive_line(line, sizeof(line));

        if (err != OK) {
            return err;
        }

        HI_LOGI("line = '%s'", line);

        char *end;
        unsigned long n = strtoul(line, &end, 16);

        if (end == line || (*end != ';' && *end != '\0')) {
            HI_LOGE("malformed HTTP chunk '%s'", line);
            return ERROR_MALFORMED;
        }

        mChunkDataBytesLeft = n;
        HI_LOGI("chunk data size = %lu", n);

        if (mChunkDataBytesLeft == 0) {
            mChunkDataBytesLeft = -1;
            return 0;
        }

        // fall through
    }

    if (size > (size_t)mChunkDataBytesLeft) {
        size = mChunkDataBytesLeft;
    }

    ssize_t n = mHTTP.receive(data, size);

    if (n < 0) {
        return n;
    }

    mChunkDataBytesLeft -= (size_t)n;

    if (mChunkDataBytesLeft == 0) {
        char line[1024];
        status_t err = mHTTP.receive_line(line, sizeof(line));

        if (err != OK) {
            return err;
        }

        if (line[0] != '\0') {
            HI_LOGE("missing HTTP chunk terminator.");
            return ERROR_MALFORMED;
        }
    }

    return n;
}

ssize_t HTTPSource::readAt(off64_t offset, void *data, size_t size) {
    HI_LOGI("readAt offset %ld, size %d", offset, size);

    Mutex::Autolock autoLock(mLock);

    if (offset != mOffset) {
        String8 host = mHost;
        String8 path = mPath;
        String8 headers = mHeaders;
        status_t err = connect(host, mPort, path, mHTTPS, headers, offset, NULL);

        if (err != OK) {
            return err;
        }
    }

    if (mContentLengthValid) {
        size_t avail =
            (offset >= mContentLength) ? 0 : mContentLength - offset;

        if (size > avail) {
            size = avail;
        }
    }

    size_t numBytesRead = 0;
    while (numBytesRead < size) {
        //int64_t startTimeUs = ALooper::GetNowUs();

        ssize_t n =
            internalRead((uint8_t *)data + numBytesRead, size - numBytesRead);

        if (n < 0) {
            if (numBytesRead == 0 || mContentLengthValid) {
                return n;
            }

            // If there was an error we want to at least return the data
            // we've already successfully read. The next call to read will
            // then return the error.
            n = 0;
        }

        numBytesRead += (size_t)n;

        if (n == 0) {
            if (mContentLengthValid) {
                // We know the content length and made sure not to read beyond
                // it and yet the server closed the connection on us.
                return ERROR_IO;
            }

            break;
        }
    }

    mOffset += numBytesRead;

    return numBytesRead;
}

status_t HTTPSource::getSize(off64_t *size) {
    *size = 0;

    if (mState != CONNECTED) {
        return ERROR_IO;
    }

    if (mContentLengthValid) {
        *size = mContentLength;
        return OK;
    }

    return ERROR_UNSUPPORTED;
}

void HTTPSource::MakeFullHeaders(const KeyedVector<String8, String8> *overrides, String8 *headers,
                                 const String8 *userAgentHeader) {
    headers->setTo("");

    // GTV changes(ftsui)
    // Original Android header creation moved to connect() method to allow
    // for setting of custom user agent string.
    if (userAgentHeader != NULL) {
      headers->append(*userAgentHeader);
    }
    headers->append("\r\n");

    if (overrides == NULL) {
        return;
    }

    for (size_t i = 0; i < overrides->size(); ++i) {
        String8 line;
        line.append(overrides->keyAt(i));
        line.append(": ");
        line.append(overrides->valueAt(i));
        line.append("\r\n");

        headers->append(line);
    }
}

void HTTPSource::applyTimeoutResponse() {
    AString timeout;
    if (mHTTP.find_header_value("X-SocketTimeout", &timeout)) {
        const char *s = timeout.c_str();
        char *end;
        long tmp = strtol(s, &end, 10);
        if (end == s || *end != '\0') {
            HI_LOGW("Illegal X-SocketTimeout value given.");
            return;
        }

        HI_LOGI("overriding default timeout, new timeout is %ld seconds", tmp);
        mHTTP.setReceiveTimeout(tmp);
    }
}

String8 HTTPSource::getUri() {
    return mUri;
}

}  // namespace android
