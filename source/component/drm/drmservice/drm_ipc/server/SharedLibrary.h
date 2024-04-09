#ifndef SHARED_LIBRARY_H__
#define SHARED_LIBRARY_H__
#include <common/hi_type.h>
#include <utils/RefBase.h>
#include <utils/String8.h>

using namespace android;

class SharedLibrary : public RefBase
{
public:
    SharedLibrary(const String8& path);
    ~SharedLibrary();

    HI_BOOL operator!() const;
    HI_VOID* lookup(const char* symbol) const;
    const HI_CHAR* lastError() const;

private:
    HI_VOID* mLibHandle;
};
#endif //SHARED_LIBRARY_H__
