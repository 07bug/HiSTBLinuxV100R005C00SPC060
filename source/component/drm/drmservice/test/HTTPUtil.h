//
// Copyright 2013 Google Inc. All Rights Reserved.
//

#ifndef HTTP_UTIL_H_
#define HTTP_UTIL_H_

#include <utils/Vector.h>

namespace android {

class String8;

bool DoSoapAction(const String8& url, const String8& action, const String8& xmlData,
                  Vector<uint8_t>* response);
}

#endif // HTTP_UTIL_H_
