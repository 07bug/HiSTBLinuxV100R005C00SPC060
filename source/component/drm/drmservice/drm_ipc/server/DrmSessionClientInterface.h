#ifndef DRM_PROXY_INTERFACE_H_
#define DRM_PROXY_INTERFACE_H_
#include <common/hi_type.h>
#include <utils/RefBase.h>
#include <utils/Vector.h>
using namespace android;

class DrmSessionClientInterface : public RefBase
{
public:
    virtual HI_BOOL reclaimSession(const Vector<HI_U8>& sessionId) = 0;

protected:
    virtual ~DrmSessionClientInterface() {}
};

#endif  // DRM_PROXY_INTERFACE_H_
