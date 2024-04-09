//
// Copyright 2013 Google Inc. All Rights Reserved.
//

#ifndef HTTP_STREAM_H_
#define HTTP_STREAM_H_

#include <utils/KeyedVector.h>
#include <utils/threads.h>

namespace android {

class AString;

class HTTPStream {
public:
    HTTPStream();
    ~HTTPStream();

    status_t connect(const char *server, int port = -1, bool https = false);
    status_t disconnect();

    status_t send(const char *data, size_t size);

    // Assumes data is a '\0' terminated string.
    status_t send(const char *data);

    // Receive up to "size" bytes of data.
    ssize_t receive(void *data, size_t size);

    status_t receive_header(int *http_status);

    // The header key used to retrieve the status line.
    static const char *kStatusKey;

    bool find_header_value(const AString &key, AString *value) const;

    // Pass a negative value to disable the timeout.
    void setReceiveTimeout(int seconds);

    // Receive a line of data terminated by CRLF, line will be '\0' terminated
    // _excluding_ the termianting CRLF.
    status_t receive_line(char *line, size_t size);

private:
    enum State {
        READY,
        CONNECTING,
        CONNECTED
    };

    State mState;
    Mutex mLock;
    int mSocket;
    int mTimeoutSec;

    KeyedVector<AString, AString> mHeaders;

    void *mSSLContext;
    void *mSSL;

    int mTotalDownloadTimeoutSec;

    HTTPStream(const HTTPStream &);
    HTTPStream &operator=(const HTTPStream &);
};

}  // namespace android

#endif  // HTTP_STREAM_H_
