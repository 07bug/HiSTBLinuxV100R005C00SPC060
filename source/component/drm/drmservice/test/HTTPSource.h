//
// Copyright 2013 Google Inc. All Rights Reserved.
//

#ifndef HTTP_SOURCE_H_
#define HTTP_SOURCE_H_

#include "HTTPStream.h"

#include <utils/List.h>
#include <utils/String8.h>
#include <utils/threads.h>

namespace android {

/*
 * HTTPSource comes from NuHHTPDataSource.cpp.
 * It removes the hicherarcy of DataSource, and DRM related things to make it
 * work with PlayReady DRM plugin.
 */
struct HTTPSource : public RefBase {
    enum Flags {
        // Don't log any URLs.
        kFlagIncognito = 1
    };
    HTTPSource(uint32_t flags = 0);

    // It can accept only NULL-terminated string as a postData.
    status_t connect(const char *uri,
                     const KeyedVector<String8, String8> *headers = NULL,
                     off64_t offset = 0,
                     const char *postData = NULL);

    void disconnect();

    virtual ssize_t readAt(off64_t offset, void *data, size_t size);
    virtual status_t getSize(off64_t *size);

    virtual String8 getUri();

protected:
    virtual ~HTTPSource();

private:
    enum State {
        DISCONNECTED,
        CONNECTING,
        CONNECTED
    };

    Mutex mLock;

    uint32_t mFlags;

    State mState;

    String8 mHost;
    unsigned mPort;
    String8 mPath;
    bool mHTTPS;
    String8 mHeaders;
    String8 mUri;

    HTTPStream mHTTP;
    off64_t mOffset;
    off64_t mContentLength;
    bool mContentLengthValid;
    bool mHasChunkedTransferEncoding;

    // The number of data bytes in the current chunk before any subsequent
    // chunk header (or -1 if no more chunks).
    ssize_t mChunkDataBytesLeft;

    // This field includes the User-Agent: part of the header.
    String8 mUserAgentHeader;

    int mRedirectCount;
    const int mMaxRedirectCount;

    status_t connect(const char *uri, const String8 &headers, off64_t offset, const char *postData);

    status_t connect(const char *host, unsigned port, const char *path,
                     bool https, const String8 &headers, off64_t offset, const char *postData);

    // Read up to "size" bytes of data, respect transfer encoding.
    ssize_t internalRead(void *data, size_t size);

    void applyTimeoutResponse();

    static void MakeFullHeaders(const KeyedVector<String8, String8> *overrides,
                                String8 *headers, const String8 *userAgentHeader);

    HTTPSource(const HTTPSource &);
    HTTPSource &operator=(const HTTPSource &);
};

}  // namespace android

#endif  // HTTP_DATA_SOURCE_H_
