#ifndef DRM_SERVICE_H__
#define DRM_SERVICE_H__

#include "../client/IDrm.h"
#include "../client/ICrypto.h"
#include "../client/IDrmService.h"

class DrmService: public BnDrmService
{
public:

    DrmService();
    ~DrmService();
    static  HI_VOID    instantiate(); /**< instantiate a drm server */
    virtual sp<ICrypto>         makeCrypto();
    virtual sp<IDrm>            makeDrm();
};

#endif //DRM_SERVICE_H__
