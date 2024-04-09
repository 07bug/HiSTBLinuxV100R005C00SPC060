#define LOG_TAG "DrmClient"
#include <utils/Logger.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "DrmClient.h"

#define MAX_TRY_COUNT (5)

#define DRM_SERVICE_NAME "hisi.drm.service"
sp<IDrmService> DrmClient::msDrmService;
//sp<DrmClient::DeathNotifier> DrmClient::mDeathNotifier;

DrmClient::DrmClient(const HI_U8 uuid[16])
{
    HI_LOGD("%s:construct", __FUNCTION__);

    mListener = NULL;
    makeDrm(uuid);

    if (mDrm != NULL)
    {
        mDrm->setListener(this);
    }
}

DrmClient::~DrmClient()
{
    HI_LOGD("%s:de-construct", __FUNCTION__);

    if (mDrm != NULL)
    {
        mDrm->destroyPlugin();
        mDrm.clear();
    }

    IPCThreadState::self()->flushCommands();
    mListener = NULL;
}

HI_VOID DrmClient::makeDrm(const HI_U8 uuid[16])
{
    HI_S32 ret = HI_FAILURE;

    HI_LOGD("%s", __FUNCTION__);

    sp<IDrmService> drmService = getDrmService();

    if (drmService == NULL)
    {
        HI_LOGE("can't get drm service!");
        return;
    }

    mDrm = drmService->makeDrm();

    if ((mDrm != NULL) && (mDrm->initCheck() == HI_FALSE))
    {
        ret = mDrm->createPlugin(uuid);

    }

    HI_LOGD("%s,create drm plugin result(%s)", __FUNCTION__,
            (ret == HI_SUCCESS) ? "success" : "fail");
}

const sp<IDrmService> DrmClient::getDrmService()
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


HI_BOOL DrmClient::isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->isCryptoSchemeSupported(uuid, mimeType);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FALSE;
}


HI_S32 DrmClient::openSession(Vector<HI_U8>& sessionId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        HI_S32 ret = mDrm->openSession(sessionId);

        HI_LOGD("result of drm client openSession:%d", ret);

        return ret;
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::closeSession(Vector<HI_U8> const& sessionId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->closeSession(sessionId);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getKeyRequest(Vector<HI_U8> const& sessionId,
                                Vector<HI_U8> const& initData,
                                String8 const& mimeType, DrmPlugin::KeyType keyType,
                                KeyedVector<String8, String8> const& optionalParameters,
                                Vector<HI_U8>& request, String8& defaultUrl,
                                DrmPlugin::KeyRequestType* keyRequestType)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getKeyRequest(sessionId,
                                   initData,
                                   mimeType,
                                   keyType,
                                   optionalParameters,
                                   request,
                                   defaultUrl,
                                   keyRequestType);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::provideKeyResponse(Vector<HI_U8> const& sessionId,
                                     Vector<HI_U8> const& response,
                                     Vector<HI_U8>& keySetId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->provideKeyResponse(sessionId, response, keySetId);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::removeKeys(Vector<HI_U8> const& keySetId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->removeKeys(keySetId);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::restoreKeys(Vector<HI_U8> const& sessionId,
                              Vector<HI_U8> const& keySetId)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->restoreKeys(sessionId, keySetId);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::queryKeyStatus(Vector<HI_U8> const& sessionId,
                                 KeyedVector<String8, String8>& infoMap)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->queryKeyStatus(sessionId, infoMap);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getProvisionRequest(String8 const& certType,
                                      String8 const& certAuthority,
                                      Vector<HI_U8>& request,
                                      String8& defaulUrl)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getProvisionRequest(certType, certAuthority, request, defaulUrl);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::provideProvisionResponse(Vector<HI_U8> const& response,
        Vector<HI_U8>& certificate,
        Vector<HI_U8>& wrappedKey)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->provideProvisionResponse(response, certificate, wrappedKey);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::unprovisionDevice()
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->unprovisionDevice();
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getSecureStops(List<Vector<HI_U8> >& secureStops)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getSecureStops(secureStops);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getSecureStop(ssid, secureStop);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::releaseSecureStops(Vector<HI_U8> const& ssRelease)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->releaseSecureStops(ssRelease);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::releaseAllSecureStops()
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->releaseAllSecureStops();
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getPropertyString(String8 const& name, String8& value)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getPropertyString(name, value);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::getPropertyByteArray(String8 const& name,
                                       Vector<HI_U8>& value)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->getPropertyByteArray(name, value);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::setPropertyString(String8 const& name,
                                    String8 const& value )
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->setPropertyString(name, value);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::setPropertyByteArray(String8 const& name,
                                       Vector<HI_U8> const& value)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->setPropertyByteArray(name, value);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                     String8 const& algorithm)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->setCipherAlgorithm(sessionId, algorithm);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                  String8 const& algorithm)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->setMacAlgorithm(sessionId, algorithm);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::encrypt(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& input,
                          Vector<HI_U8> const& iv,
                          Vector<HI_U8>& output)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->encrypt(sessionId, keyId, input, iv, output);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::decrypt(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& input,
                          Vector<HI_U8> const& iv,
                          Vector<HI_U8>& output)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->decrypt(sessionId, keyId, input, iv, output);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::sign(Vector<HI_U8> const& sessionId,
                       Vector<HI_U8> const& keyId,
                       Vector<HI_U8> const& message,
                       Vector<HI_U8>& signature)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->sign(sessionId, keyId, message, signature);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::verify(Vector<HI_U8> const& sessionId,
                         Vector<HI_U8> const& keyId,
                         Vector<HI_U8> const& message,
                         Vector<HI_U8> const& signature,
                         HI_BOOL& match)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->verify(sessionId, keyId, message, signature, match);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::signRSA(Vector<HI_U8> const& sessionId,
                          String8 const& algorithm,
                          Vector<HI_U8> const& message,
                          Vector<HI_U8> const& wrappedKey,
                          Vector<HI_U8>& signature)
{
    HI_LOGD("%s", __FUNCTION__);

    if (mDrm != NULL)
    {
        return mDrm->signRSA(sessionId, algorithm, message, wrappedKey, signature);
    }

    HI_LOGE("%s: mDrm is NULL", __FUNCTION__);

    return HI_FAILURE;
}

HI_S32 DrmClient::setListener(DrmListener* listener)
{
    HI_LOGD("%s", __FUNCTION__);

    mListener = listener;
    return HI_SUCCESS;
}

HI_VOID DrmClient::notify(DrmPlugin::EventType eventType, HI_S32 extra, const Parcel* obj)
{
    HI_LOGD("%s,event(%d)", __FUNCTION__, eventType);

    HI_DRM_EVENT_TYPE event = HI_DRM_EVENT_KEY_BUTT;
    HI_DRM_MSG_DATA stMsgdata;

    /*read session id*/
    readVector(obj, stMsgdata.sessionId);

    switch (eventType)
    {
        case DrmPlugin::kDrmPluginEventProvisionRequired:
            event = HI_DRM_EVENT_PROVISION_REQUIRED;
            stMsgdata.stEventData.s32extra = extra;
            readVector(obj, stMsgdata.stEventData.data);
            break;

        case DrmPlugin::kDrmPluginEventKeyNeeded:
            event = HI_DRM_EVENT_KEY_NEEDED;
            stMsgdata.stEventData.s32extra = extra;
            readVector(obj, stMsgdata.stEventData.data);
            break;

        case DrmPlugin::kDrmPluginEventKeyExpired:
            event = HI_DRM_EVENT_KEY_EXPIRED;
            stMsgdata.stEventData.s32extra = extra;
            readVector(obj, stMsgdata.stEventData.data);
            break;

        case DrmPlugin::kDrmPluginEventVendorDefined:
            event = HI_DRM_EVENT_VENDOR_DEFINED;
            stMsgdata.stEventData.s32extra = extra;
            readVector(obj, stMsgdata.stEventData.data);
            break;

        case DrmPlugin::kDrmPluginEventSessionReclaimed:
            event = HI_DRM_EVENT_SESSION_RECLAIMED;
            stMsgdata.stEventData.s32extra = extra;
            readVector(obj, stMsgdata.stEventData.data);
            break;

        case DrmPlugin::kDrmPluginEventExpirationUpdate:
            event = HI_DRM_EVENT_EXPIRATION_UPDATE;
            stMsgdata.s64expiryTimeInMS = obj->readInt64();
            break;

        case DrmPlugin::kDrmPluginEventKeysChange:
            event = HI_DRM_EVENT_KEY_CHANGE;
            readKeyStatusList(obj, stMsgdata.stkeyChange.stkeyStatusList);
            stMsgdata.stkeyChange.bhasNewUsableKey = (HI_BOOL)obj->readInt32();
            break;

        default:
            HI_LOGE("Invalid event DrmPlugin::EventType %d, ignored", (int)eventType);
            return;
    }

    if (mListener != NULL)
    {
        mListener->notify(event, &stMsgdata);
    }
}

HI_VOID DrmClient::readVector(const Parcel* data, Vector<HI_U8>& vector) const
{
    HI_U32 size = data->readInt32();

    if (size > 0)
    {
        vector.insertAt((size_t)0, size);
        data->read(vector.editArray(), size);
    }
}

/*must used after the sessioin haved read for Parcel obj*/
HI_VOID DrmClient::readKeyStatusList(const Parcel* data, Vector<HI_KEY_STATUS>& list) const
{
    HI_S32 i = 0;
    HI_KEY_STATUS stKeystatus;
    HI_S32 nkeys = data->readInt32();

    for (i = 0; i < nkeys; i++)
    {
        readVector(data, stKeystatus.mKeyId);
        stKeystatus.mType = (HI_DRM_KEYSTATUS_TYPE)data->readInt32();
        list.push(stKeystatus);
    }
}
