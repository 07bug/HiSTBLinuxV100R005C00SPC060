#define LOG_TAG "ModularDrmInterfaceImpl"
#include <utils/Logger.h>

#include <DrmAPI.h>
#include "ModularDrmInterfaceImpl.h"
#define DRMINTFMAXTRANSLENGTH (1024*1024)
static DrmPlugin::KeyType convertToPluginKeyType(HI_DRM_KEY_TYPE type)
{
    switch (type)
    {
        case HI_DRM_KEY_TYPE_OFFLINE:
            return DrmPlugin::kKeyType_Offline;

        case HI_DRM_KEY_TYPE_STREAMING:
            return DrmPlugin::kKeyType_Streaming;

        case HI_DRM_KEY_TYPE_RELEASE:
            return DrmPlugin::kKeyType_Release;

        default:
            break;
    }

    return DrmPlugin::kKeyType_Offline;
}

static HI_DRM_KEYREQUEST_TYPE convertPluginKeyRequestType(DrmPlugin::KeyRequestType type)
{
    switch (type)
    {
        case DrmPlugin::kKeyRequestType_Unknown:
            return HI_DRM_KEYRST_TYPE_UNKNOWN;

        case DrmPlugin::kKeyRequestType_Renewal:
            return HI_DRM_KEYRST_TYPE_RENEWAL;

        case DrmPlugin::kKeyRequestType_Release:
            return HI_DRM_KEYRST_TYPE_RELEASE;

        case DrmPlugin::kKeyRequestType_Initial:
            return HI_DRM_KEYRST_TYPE_INITIAL;

        default:
            break;
    }

    return HI_DRM_KEYRST_TYPE_BUTT;
}

ModularDrmInterface* ModularDrmInterface::Create(const HI_U8 uuid[16])
{
    if (HI_NULL != uuid)
    {
        return new ModularDrmInterfaceImpl(uuid);
    }

    return HI_NULL;
}

HI_S32 ModularDrmInterface::Destroy(ModularDrmInterface* &object)
{
    if (object != HI_NULL)
    {
        delete object;
        object = HI_NULL;
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

ModularDrmInterfaceImpl::ModularDrmInterfaceImpl(const HI_U8 uuid[16])
{
#ifdef MULTI_PROCESS
    mDrmClient = new DrmClient(uuid);
    if (HI_NULL == mDrmClient)
    {
        HI_LOGE("mDrmClient malloc memory failed!");
    }
#else
    mDrmClient = new Drm;
    if (HI_NULL == mDrmClient)
    {
        HI_LOGE("mDrmClient malloc memory failed!");
        return;
    }
    if( mDrmClient->createPlugin(uuid) !=0)
        HI_LOGE("%s: createPlugin FAIL", __FUNCTION__);
#endif
}

ModularDrmInterfaceImpl::~ModularDrmInterfaceImpl()
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrmClient != HI_NULL)
    {
        delete mDrmClient;
        mDrmClient = HI_NULL;
    }
}

HI_BOOL ModularDrmInterfaceImpl::isCryptoSchemeSupported(const HI_U8 uuid[16], const HI_CHAR* mimeType)
{
    String8 mime;

    if (HI_NULL == uuid)
    {
        HI_LOGE("%s: Para uuid is invalid", __FUNCTION__);
        return HI_FALSE;
    }

    if (HI_NULL != mimeType && strlen(mimeType) < DRMINTFMAXTRANSLENGTH)
    {
        mime.setTo(mimeType);
    }

    return mDrmClient->isCryptoSchemeSupported(uuid, mime);
}

HI_S32 ModularDrmInterfaceImpl::openSession(Vector<HI_U8>& sessionId)
{
    HI_S32 res = mDrmClient->openSession(sessionId);

    HI_LOGD("mDrmClient openSession result:%d", res);
    return res;
}

HI_S32 ModularDrmInterfaceImpl::closeSession(Vector<HI_U8> const& sessionId)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->closeSession(sessionId);
}

HI_S32 ModularDrmInterfaceImpl::getKeyRequest(Vector<HI_U8> const& scope,
        Vector<HI_U8> const& initData,
        HI_CHAR const* mimeType, HI_DRM_KEY_TYPE keyType,
        KeyedVector<String8, String8> const& optionalParameters,
        HI_DRM_KEY_REQUEST* pKeyRequest)
{
    HI_S32 ret = HI_FAILURE;
    DrmPlugin::KeyType pluginKeyType;
    DrmPlugin::KeyRequestType pluginKeyRstType;
    String8 mime;
    int CountSize = 0;
    String8 Val_1, Val_2;

    HI_LOGD("%s,keyType(%d)", __FUNCTION__, keyType);

    if (HI_NULL == pKeyRequest)
    {
        HI_LOGE("%s: Para pKeyRequest is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (scope.isEmpty() || scope.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para initData is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (initData.isEmpty() || initData.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para initData is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (HI_NULL != mimeType && (strlen(mimeType) < DRMINTFMAXTRANSLENGTH/4))
    {
        mime.setTo(mimeType);
    }

    for (int i = 0; i < (int)optionalParameters.size(); i++)
    {
        Val_1 = optionalParameters.keyAt(i);
        Val_2 = optionalParameters.valueAt(i);
        CountSize += Val_1.size();
        CountSize += Val_2.size();
        Val_1.clear();
        Val_2.clear();
    }

    if (CountSize > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para optionalParameters is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    pluginKeyType = convertToPluginKeyType(keyType);

    ret = mDrmClient->getKeyRequest(scope,
                                    initData,
                                    mime,
                                    pluginKeyType,
                                    optionalParameters,
                                    pKeyRequest->requestData,
                                    pKeyRequest->defaultUrl,
                                    &pluginKeyRstType);

    pKeyRequest->eKeyRequestType = convertPluginKeyRequestType(pluginKeyRstType);

    return ret;
}

HI_S32 ModularDrmInterfaceImpl::provideKeyResponse(Vector<HI_U8> const& scope,
        Vector<HI_U8> const& response,
        Vector<HI_U8>& keySetId)
{
    HI_LOGD("%s", __FUNCTION__);
    if (scope.isEmpty() || scope.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para scope is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (response.isEmpty() || response.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para response is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->provideKeyResponse(scope, response, keySetId);
}

HI_S32 ModularDrmInterfaceImpl::removeKeys(Vector<HI_U8> const& sessionId)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->removeKeys(sessionId);
}

HI_S32 ModularDrmInterfaceImpl::restoreKeys(Vector<HI_U8> const& sessionId, Vector<HI_U8> const& keySetId)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (keySetId.isEmpty() || keySetId.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para keySetId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->restoreKeys(sessionId, keySetId);
}

HI_S32 ModularDrmInterfaceImpl::queryKeyStatus(Vector<HI_U8> const& sessionId,
        KeyedVector<String8, String8>& infoMap)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->queryKeyStatus(sessionId, infoMap);
}

HI_S32 ModularDrmInterfaceImpl::getProvisionRequest(String8 const& certType,
        String8 const& certAuthority,
        HI_DRM_PROVITION_REQUEST* request)
{
    HI_LOGD("%s", __FUNCTION__);
    if (certType.isEmpty() || certType.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para certType is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (certAuthority.isEmpty() || certAuthority.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para certAuthority is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    if (request != HI_NULL)
    {
        return mDrmClient->getProvisionRequest(certType,
                                               certAuthority,
                                               request->requestData,
                                               request->defaultUrl);
    }

    HI_LOGE("%s: request is HI_NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 ModularDrmInterfaceImpl::provideProvisionResponse(Vector<HI_U8> const& response,
        Vector<HI_U8>& certificate,
        Vector<HI_U8>& wrappedKey)
{
    HI_LOGD("%s", __FUNCTION__);
    if (response.isEmpty() || response.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para response is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->provideProvisionResponse(response, certificate, wrappedKey);
}

HI_S32 ModularDrmInterfaceImpl::unprovisionDevice()
{
    HI_LOGD("%s", __FUNCTION__);
    if (!mDrmClient)
    {
        HI_LOGE("%s : mDrmClient is HI_NULL", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->unprovisionDevice();
}

HI_S32 ModularDrmInterfaceImpl::getSecureStops(List<Vector<HI_U8> >& secureStops)
{
    HI_U32 u32limitedSize = 0;
    List<Vector<HI_U8> >::iterator iter;
    for (iter = secureStops.begin(); iter != secureStops.end(); iter++)
    {
        u32limitedSize += iter->size();;
    }

    if (u32limitedSize > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para secureStops is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->getSecureStops(secureStops);
}

HI_S32 ModularDrmInterfaceImpl::getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop)
{
    if (ssid.isEmpty() || ssid.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para ssid is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->getSecureStop(ssid, secureStop);
}

HI_S32 ModularDrmInterfaceImpl::releaseSecureStops(Vector<HI_U8> const& ssRelease)
{
    if (ssRelease.isEmpty() || ssRelease.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para ssRelease is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->releaseSecureStops(ssRelease);
}

HI_S32 ModularDrmInterfaceImpl::releaseAllSecureStops()
{
    return mDrmClient->releaseAllSecureStops();
}

HI_S32 ModularDrmInterfaceImpl::getPropertyString(String8 const& name, String8& value)
{
    if (name.isEmpty() || name.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para name is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->getPropertyString(name, value);
}

HI_S32 ModularDrmInterfaceImpl::getPropertyByteArray(String8 const& name,
        Vector<HI_U8>& value)
{
    if (name.isEmpty() || name.size() > DRMINTFMAXTRANSLENGTH)
    {
        HI_LOGE("%s: Para name is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    return mDrmClient->getPropertyByteArray(name, value);
}

HI_S32 ModularDrmInterfaceImpl::setPropertyString(String8 const& name,
        String8 const& value )
{
    if (name.isEmpty() || name.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para name is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (value.isEmpty() || value.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para value is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->setPropertyString(name, value);
}

HI_S32 ModularDrmInterfaceImpl::setPropertyByteArray(String8 const& name,
        Vector<HI_U8> const& value)
{
    if (name.isEmpty() || name.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para name is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (value.isEmpty() || value.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para value is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->setPropertyByteArray(name, value);
}

HI_S32 ModularDrmInterfaceImpl::setCipherAlgorithm(Vector<HI_U8> const& sessionId,
        String8 const& algorithm)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (algorithm.isEmpty() || algorithm.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para algorithm is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->setCipherAlgorithm(sessionId, algorithm);
}

HI_S32 ModularDrmInterfaceImpl::setMacAlgorithm(Vector<HI_U8> const& sessionId,
        String8 const& algorithm)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (algorithm.isEmpty() || algorithm.size() > DRMINTFMAXTRANSLENGTH/2)
    {
        HI_LOGE("%s: Para algorithm is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->setMacAlgorithm(sessionId, algorithm);
}

HI_S32 ModularDrmInterfaceImpl::encrypt(Vector<HI_U8> const& sessionId,
                                        Vector<HI_U8> const& keyId,
                                        Vector<HI_U8> const& input,
                                        Vector<HI_U8> const& iv,
                                        Vector<HI_U8>& output)
{
    if (output.isEmpty())
    {
        HI_LOGE("%s: Para output is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (keyId.isEmpty() || keyId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para keyId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (input.isEmpty() || input.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para input is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (iv.isEmpty() || iv.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para iv is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->encrypt(sessionId, keyId, input, iv, output);
}

HI_S32 ModularDrmInterfaceImpl::decrypt(Vector<HI_U8> const& sessionId,
                                        Vector<HI_U8> const& keyId,
                                        Vector<HI_U8> const& input,
                                        Vector<HI_U8> const& iv,
                                        Vector<HI_U8>& output)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (keyId.isEmpty() || keyId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para keyId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (input.isEmpty() || input.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para input is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (iv.isEmpty() || iv.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para iv is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->decrypt(sessionId, keyId, input, iv, output);
}

HI_S32 ModularDrmInterfaceImpl::sign(Vector<HI_U8> const& sessionId,
                                     Vector<HI_U8> const& keyId,
                                     Vector<HI_U8> const& message,
                                     Vector<HI_U8>& signature)
{
    if (signature.isEmpty())
    {
        HI_LOGE("%s: Para signature is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/3)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (keyId.isEmpty() || keyId.size() > DRMINTFMAXTRANSLENGTH/3)
    {
        HI_LOGE("%s: Para keyId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (message.isEmpty() || message.size() > DRMINTFMAXTRANSLENGTH/3)
    {
        HI_LOGE("%s: Para message is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->sign(sessionId, keyId, message, signature);
}

HI_S32 ModularDrmInterfaceImpl::verify(Vector<HI_U8> const& sessionId,
                                       Vector<HI_U8> const& keyId,
                                       Vector<HI_U8> const& message,
                                       Vector<HI_U8>const& signature,
                                       HI_BOOL& match)
{
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (keyId.isEmpty() || keyId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para keyId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (message.isEmpty() || message.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para message is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (signature.isEmpty() || signature.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para signature is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->verify(sessionId, keyId, message, signature, match);
}

HI_S32 ModularDrmInterfaceImpl::signRSA(Vector<HI_U8> const& sessionId,
                                        String8 const& algorithm,
                                        Vector<HI_U8> const& message,
                                        Vector<HI_U8> const& wrappedKey,
                                        Vector<HI_U8>& signature)
{
    if (signature.isEmpty())
    {
        HI_LOGE("%s: Para signature is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (sessionId.isEmpty() || sessionId.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para sessionId is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (algorithm.isEmpty() || algorithm.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para algorithm is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (message.isEmpty() || message.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para message is invalid", __FUNCTION__);
        return HI_FAILURE;
    }
    if (wrappedKey.isEmpty() || wrappedKey.size() > DRMINTFMAXTRANSLENGTH/4)
    {
        HI_LOGE("%s: Para wrappedKey is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->signRSA(sessionId, algorithm, message, wrappedKey, signature);
}

HI_S32 ModularDrmInterfaceImpl::setListener(DrmListener* listener)
{
#if MULTI_PROCESS
    if (HI_NULL == listener)
    {
        HI_LOGE("%s: Para listener is invalid", __FUNCTION__);
        return HI_FAILURE;
    }

    return mDrmClient->setListener(listener);
#endif
    return HI_SUCCESS;
}
