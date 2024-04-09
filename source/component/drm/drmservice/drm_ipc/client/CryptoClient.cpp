#define LOG_TAG "CryptoClient"
#include <utils/Logger.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "CryptoClient.h"
#include "DrmClient.h"

#define MAX_TRY_COUNT (5)
#define DRM_SERVICE_NAME "hisi.drm.service"
sp<IDrmService> CryptoClient::msDrmService;

CryptoClient::CryptoClient(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* initData, HI_S32 initSize)
{
    HI_LOGD("%s:construct", __FUNCTION__);
    makeCrypto(uuid, initData, initSize);
}

CryptoClient::~CryptoClient()
{
    HI_LOGD("%s:de-construct", __FUNCTION__);

    if (mCrypto != NULL)
    {
        mCrypto->destroyPlugin();
        mCrypto.clear();
    }

    IPCThreadState::self()->flushCommands();
}

HI_VOID CryptoClient::makeCrypto(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* initData, HI_S32 initSize)
{
    HI_S32 ret = HI_FAILURE;

    HI_LOGD("%s", __FUNCTION__);

    sp<IDrmService> drmService = getDrmService();

    if (drmService == NULL)
    {
        HI_LOGE("can't get drm service!");
        return;
    }

    mCrypto = drmService->makeCrypto();

    if ((mCrypto != NULL) && (mCrypto->initCheck() == HI_FALSE))
    {
        ret = mCrypto->createPlugin(uuid, initData, initSize);
    }

    HI_LOGD("%s,create plugin result(%s)", __FUNCTION__,
            (ret == HI_SUCCESS) ? "success" : "fail");
}

const sp<IDrmService> CryptoClient::getDrmService()
{
    HI_U32 u32TryCount = 0;
    HI_LOGD("%s", __FUNCTION__);

    if (msDrmService == NULL)
    {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;

        do
        {
            binder = sm->getService(String16(DRM_SERVICE_NAME));

            if (binder != NULL)
            {
                break;
            }

            HI_LOGW("drm service not published, waiting...");
            //usleep(500000); // 0.5 s
            //lint -e506 -e944
            DRMSERVICE_SLEEP(500);
            //lint +e506 +e944
            u32TryCount++;
        }
        while (u32TryCount <= MAX_TRY_COUNT);

        if (binder != NULL)
        {
            msDrmService = interface_cast<IDrmService>(binder);
        }
    }

    if (msDrmService == NULL)
    {
        HI_LOGW("no drm service!");
    }

    return msDrmService;
}

HI_BOOL CryptoClient::isCryptoSchemeSupported(const HI_U8 uuid[16])
{
    HI_LOGD("%s", __FUNCTION__);

    if (mCrypto != NULL)
    {
        return mCrypto->isCryptoSchemeSupported(uuid);
    }

    HI_LOGE("%s: mCrypto is NULL", __FUNCTION__);

    return HI_FALSE;
}

HI_BOOL CryptoClient::requiresSecureDecoderComponent(const HI_CHAR* mime)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mCrypto != NULL)
    {
        return mCrypto->requiresSecureDecoderComponent(mime);
    }

    HI_LOGE("%s: mCrypto is NULL", __FUNCTION__);

    return HI_FALSE;
}

/*not used now*/
HI_VOID CryptoClient::notifyResolution(HI_U32 width, HI_U32 height)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mCrypto != NULL)
    {
        mCrypto->notifyResolution(width, height);
        return;
    }

    HI_LOGE("%s: mCrypto is NULL", __FUNCTION__);
}

HI_S32 CryptoClient::setMediaDrmSession(const Vector<HI_U8>& sessionId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mCrypto != NULL)
    {
        return mCrypto->setMediaDrmSession(sessionId);
    }

    HI_LOGE("%s: mCrypto is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 CryptoClient::decrypt(
    HI_BOOL secure,
    const HI_U8 key[HI_DRM_KEY_LEN],
    const HI_U8 iv[HI_DRM_IV_LEN],
    CryptoPlugin::Mode mode,
    const HI_VOID* sharedBuffer, size_t offset,
    const CryptoPlugin::SubSample* subSamples, size_t numSubSamples,
    HI_VOID* dstPtr,
    AString* errorDetailMsg)
{
    HI_LOGD("%s", __FUNCTION__);

    HI_S32 result = HI_FAILURE;

    if (mCrypto != NULL)
    {
        result = mCrypto->decrypt(secure,
                                  key,
                                  iv,
                                  mode,
                                  sharedBuffer,
                                  offset,
                                  subSamples,
                                  numSubSamples,
                                  dstPtr,
                                  errorDetailMsg);
        return result;
    }

    HI_LOGE("%s: mCrypto is NULL", __FUNCTION__);

    return HI_FAILURE;
}
