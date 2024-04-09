#define LOG_TAG "CryptoInterfaceImpl"
#include <utils/Logger.h>
#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>
#include <CryptoAPI.h>
#include "CryptoInterfaceImpl.h"
#define DRMINTFMAXTRANSLENGTH (1024*1024)

static HI_VOID transToPluginMode(HI_CRYPTO_MODE mode, CryptoPlugin::Mode* plugin_mode)
{
    switch (mode)
    {
        case HI_CRYPTO_MODE_UNENCRYPTED:
            *plugin_mode = CryptoPlugin::kMode_Unencrypted;
            break;

        case HI_CRYPTO_MODE_AES_CTR:
            *plugin_mode = CryptoPlugin::kMode_AES_CTR;
            break;

        case HI_CRYPTO_MODE_AES_WV:
            *plugin_mode = CryptoPlugin::kMode_AES_WV;
            break;

        case HI_CRYPTO_MODE_AES_CBC:
            *plugin_mode = CryptoPlugin::kMode_AES_CBC;
            break;

        default:
            break;
    }
}

CryptoInterface* CryptoInterface::Create(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* initData, HI_S32 initSize)
{
    // Modify initSize for DTS2016042008898
    if ((HI_NULL != uuid) && (HI_NULL != initData) && (initSize > 0 && initSize < DRMINTFMAXTRANSLENGTH) && strlen((const char*)initData) < DRMINTFMAXTRANSLENGTH)
    {
        return new CryptoInterfaceImpl(uuid, initData, initSize);
    }

    HI_LOGE("%s: input parameter wrong", __FUNCTION__);

    return HI_NULL;
}

HI_S32 CryptoInterface::Destroy(CryptoInterface* &object)
{
    if (object != HI_NULL)
    {
        delete object;
        object = HI_NULL;
        return HI_SUCCESS;
    }

    HI_LOGE("%s: input object HI_NULL", __FUNCTION__);

    return HI_FAILURE;
}

CryptoInterfaceImpl::CryptoInterfaceImpl(const HI_U8 uuid[16], const HI_VOID* initData, HI_S32 initSize)
{
#ifdef MULTI_PROCESS
    mCryptoClient = new CryptoClient(uuid, initData, initSize);
    if (!mCryptoClient){
        HI_LOGE("%s: CryptoClient FAIL", __FUNCTION__);
        return;
    }
#else
    mCryptoClient = new Crypto;
    mCryptoClient->createPlugin(uuid, initData, initSize);
#endif
}

CryptoInterfaceImpl::~CryptoInterfaceImpl()
{
    if (mCryptoClient != HI_NULL)
    {
        delete mCryptoClient;
        mCryptoClient = HI_NULL;
    }
}

HI_BOOL CryptoInterfaceImpl::isCryptoSchemeSupported(const HI_U8 uuid[16])
{
    if (HI_NULL == uuid)
    {
        HI_LOGE("%s: input parameter is HI_NULL", __FUNCTION__);
        return HI_FALSE;
    }

    return mCryptoClient->isCryptoSchemeSupported(uuid);
}

HI_BOOL CryptoInterfaceImpl::requiresSecureDecoderComponent(const HI_CHAR* mime)
{
    if (HI_NULL == mime)
    {
        HI_LOGE("%s: input mime is HI_NULL", __FUNCTION__);
        return HI_FALSE;
    }
    if (strlen(mime) > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: mime size is too big", __FUNCTION__);
        return HI_FALSE;
    }

    return mCryptoClient->requiresSecureDecoderComponent(mime);
}

HI_S32 CryptoInterfaceImpl::setMediaDrmSession(const Vector<HI_U8>& sessionId)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mCryptoClient->setMediaDrmSession(sessionId);
}

HI_S32 CryptoInterfaceImpl::decrypt(
    HI_BOOL secure,
    const HI_U8 key[HI_DRM_KEY_LEN],
    const HI_U8 iv[HI_DRM_IV_LEN],
    HI_CRYPTO_MODE mode,
    const HI_VOID* pSrc, HI_S32 s32srcSize,
    const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
    HI_VOID* pDst,
    String8& errorDetailMsg)
{
    HI_S32 ret = HI_FAILURE;
    AString errorInfo;
    CryptoPlugin::Mode plugin_mode = CryptoPlugin::kMode_Unencrypted;

    HI_LOGD("%s:enter func ", __FUNCTION__);

    if ((HI_NULL == key) || (HI_NULL == iv) || (HI_NULL == pSrc) || (HI_NULL == subSamples) || (HI_NULL == pDst))
    {
        HI_LOGE("%s: Para is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (s32srcSize > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para s32srcSize is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    // Modify numSubSamples for DTS2016042009197
    if (numSubSamples < 0)
    {
        HI_LOGE("numSubSamples:Parameter error ");
        return HI_FAILURE;
    }
    transToPluginMode(mode, &plugin_mode);

    ret = mCryptoClient->decrypt(secure,
                                 key,
                                 iv,
                                 plugin_mode,
                                 pSrc,
                                 0,
                                 (CryptoPlugin::SubSample *)subSamples,
                                 numSubSamples,
                                 pDst,
                                 &errorInfo);

    /*return decrypt byte < 0,error occurs.may have a error info*/
    if (ret < 0)
    {
        HI_LOGW("%s: do decrypt fail", __FUNCTION__);

        if (errorInfo.size() > 0)
        {
            HI_LOGI("%s: decrypt done,have error info", __FUNCTION__);
            errorDetailMsg.setTo(errorInfo.c_str(), errorInfo.size());
        }
    }

    HI_LOGD("%s:end func,result(%d)", __FUNCTION__, ret);

    return ret;
}
