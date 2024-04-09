#define LOG_TAG "DrmService"
#include <utils/Logger.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>

#include "Crypto.h"
#include "Drm.h"
#include "DrmService.h"

DrmService::DrmService()
{
    HI_LOGD("%s",__FUNCTION__);
}

DrmService::~DrmService()
{
    HI_LOGD("%s",__FUNCTION__);
}

HI_VOID DrmService::instantiate()
{
    defaultServiceManager()->addService(
        String16("hisi.drm.service"), new DrmService());
}

sp<ICrypto> DrmService::makeCrypto()
{
    HI_LOGD("%s",__FUNCTION__);
    return new Crypto;
}

sp<IDrm> DrmService::makeDrm()
{
    HI_LOGD("%s",__FUNCTION__);
    return new Drm;
}
