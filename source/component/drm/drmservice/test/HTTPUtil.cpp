//
// Copyright 2013 Google Inc. All Rights Reserved.
//

//#define LOG_NDEBUG 0
#define LOG_TAG "HTTPUtil"
#include <utils/Logger.h>

#include "HTTPUtil.h"

#include "HTTPSource.h"

//#include <UniquePtr.h>
#include <utils/KeyedVector.h>
#include <utils/String8.h>

namespace android {

bool DoSoapAction(const String8& url, const String8& action, const String8& xmlData,
                  Vector<uint8_t>* response) {
    KeyedVector<String8, String8> headers;
    headers.add(String8("Content-Type"), String8("text/xml; charset=utf-8"));
    headers.add(String8("Proxy-Connection"), String8("Keep-Alive"));
    headers.add(String8("Pragma"), String8("no-cache"));
    if (!action.isEmpty()) {
        headers.add(String8("SOAPAction"), action);
    }

    sp<HTTPSource> source(new HTTPSource());
    if (source->connect(url.string(), &headers, 0, xmlData.string()) != OK) {
        HI_LOGE("Failed in connect()");
        return false;
    }
    off64_t size;
    if (source->getSize(&size) != OK) {
      HI_LOGE("Failed in getSize()");
      return false;
    }
    Vector<uint8_t> responseBuffer;
    responseBuffer.setCapacity(size);
    ssize_t read = source->readAt(0, responseBuffer.editArray(), size);
    (void)read;
    source->disconnect();
    response->appendArray(responseBuffer.array(), size);
    return true;
}

} // namespace android
