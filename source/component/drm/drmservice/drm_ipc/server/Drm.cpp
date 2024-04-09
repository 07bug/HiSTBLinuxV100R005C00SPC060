#define LOG_TAG "Drm"
#include <utils/Logger.h>

#include <dirent.h>
#include <dlfcn.h>

#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <DrmErrors.h>
#include <DrmAPI.h>
#include "DrmSessionClientInterface.h"
#include "DrmSessionManager.h"
#include "Drm.h"

KeyedVector<Vector<HI_U8>, String8> Drm::mUUIDToLibraryPathMap;
KeyedVector<String8, wp<SharedLibrary> > Drm::mLibraryPathToOpenLibraryMap;
Mutex Drm::mMapLock;
Mutex Drm::mLock;

#define TRACE_INFO() HI_LOGI("%s",__FUNCTION__)

static inline HI_S32 getCallingPid()
{
    return IPCThreadState::self()->getCallingPid();
}
#if 0
static HI_BOOL checkPermission(const HI_CHAR* permissionString)
{
    return HI_TRUE;
}
#endif
static HI_BOOL operator<(const Vector<HI_U8>& lhs, const Vector<HI_U8>& rhs)
{
    if (lhs.size() < rhs.size())
    {
        return HI_TRUE;
    }
    else if (lhs.size() > rhs.size())
    {
        return HI_FALSE;
    }

    return (memcmp((HI_VOID*)lhs.array(), (HI_VOID*)rhs.array(), rhs.size()) < 0) ? HI_TRUE : HI_FALSE;
}

struct DrmSessionClient : public DrmSessionClientInterface
{
    DrmSessionClient(Drm* drm) : mDrm(drm)
    {

    }

    virtual HI_BOOL reclaimSession(const Vector<HI_U8>& sessionId)
    {
        sp<Drm> drm = mDrm.promote();

        if (drm == NULL)
        {
            return HI_TRUE;
        }

        HI_S32 ret = drm->closeSession(sessionId);

        if (ret != HI_TRUE)
        {
            return HI_FALSE;
        }

        drm->sendEvent(DrmPlugin::kDrmPluginEventSessionReclaimed, 0, &sessionId, NULL);
        return HI_TRUE;
    }

protected:
    virtual ~DrmSessionClient() {}

private:
    wp<Drm> mDrm;
};

Drm::Drm()
    : mInitCheck(HI_FALSE),
      mDrmSessionClient(new DrmSessionClient(this)),
      mListener(NULL),
      mEventLock(0),
      mNotifyLock(0),
      mLibrary(NULL),
      mFactory(NULL),
      mPlugin(NULL)
{
    TRACE_INFO();
}

Drm::~Drm()
{
    TRACE_INFO();
#ifdef MULTI_PROCESS
    DrmSessionManager::Instance()->removeDrm(mDrmSessionClient);
    if (mPlugin)
    {
        delete mPlugin;
        mPlugin = NULL;
    }
#endif
    closeFactory();
}

HI_VOID Drm::closeFactory()
{
    TRACE_INFO();
    if (mFactory)
    {
        delete mFactory;
        mFactory = NULL;
    }
    mLibrary.clear();
}

HI_BOOL Drm::initCheck()
{
    TRACE_INFO();
    return mInitCheck;
}

HI_S32 Drm::setListener(const sp<IDrmClient>& listener)
{
#ifdef MULTI_PROCESS
    TRACE_INFO();
    Mutex::Autolock lock(mEventLock);

    if (mListener != NULL && (mListener->asBinder()) != NULL)
    {
        mListener->asBinder()->unlinkToDeath(this);
    }

    if (listener != NULL && (listener->asBinder()) != NULL)
    {
        listener->asBinder()->linkToDeath(this);
    }

    mListener = listener;
#endif
    return HI_SUCCESS;
}

HI_VOID Drm::sendEvent(DrmPlugin::EventType eventType, int extra,
                       Vector<HI_U8> const* sessionId,
                       Vector<HI_U8> const* data)
{
#ifdef MULTI_PROCESS
    TRACE_INFO();
    mEventLock.lock();
    sp<IDrmClient> listener = mListener;
    mEventLock.unlock();

    if (listener != NULL)
    {
        Parcel obj;
        writeByteArray(obj, sessionId);
        writeByteArray(obj, data);

        Mutex::Autolock lock(mNotifyLock);
        listener->notify(eventType, extra, &obj);
    }
#endif
}

HI_VOID Drm::sendExpirationUpdate(Vector<HI_U8> const* sessionId,
                                  HI_S64 expiryTimeInMS)
{
#ifdef MULTI_PROCESS
    TRACE_INFO();
    mEventLock.lock();
    sp<IDrmClient> listener = mListener;
    mEventLock.unlock();

    if (listener != NULL)
    {
        Parcel obj;
        writeByteArray(obj, sessionId);
        obj.writeInt64(expiryTimeInMS);

        Mutex::Autolock lock(mNotifyLock);
        listener->notify(DrmPlugin::kDrmPluginEventExpirationUpdate, 0, &obj);
    }
#endif
}

HI_VOID Drm::sendKeysChange(Vector<HI_U8> const* sessionId,
                            Vector<DrmPlugin::KeyStatus> const* keyStatusList,
                            HI_BOOL hasNewUsableKey)
{
#ifdef MULTI_PROCESS
    TRACE_INFO();
    mEventLock.lock();
    sp<IDrmClient> listener = mListener;
    mEventLock.unlock();

    if (listener != NULL)
    {
        Parcel obj;
        writeByteArray(obj, sessionId);

        size_t nkeys = keyStatusList->size();
        obj.writeInt32(keyStatusList->size());

        for (size_t i = 0; i < nkeys; ++i)
        {
            const DrmPlugin::KeyStatus* keyStatus = &keyStatusList->itemAt(i);
            writeByteArray(obj, &keyStatus->mKeyId);
            obj.writeInt32(keyStatus->mType);
        }

        obj.writeInt32(hasNewUsableKey);

        Mutex::Autolock lock(mNotifyLock);
        listener->notify(DrmPlugin::kDrmPluginEventKeysChange, 0, &obj);
    }
#endif
}

/*
 * Search the plugins directory for a plugin that supports the scheme
 * specified by uuid
 *
 * If found:
 *    mLibrary holds a strong pointer to the dlopen'd library
 *    mFactory is set to the library's factory method
 *    mInitCheck is set to HI_TRUE
 *
 * If not found:
 *    mLibrary is cleared and mFactory are set to NULL
 *    mInitCheck is set to an error (HI_FAIL)
 */
HI_VOID Drm::findFactoryForScheme(const HI_U8 uuid[16])
{
    TRACE_INFO();
    closeFactory();

    // lock static maps
    Mutex::Autolock autoLock(mMapLock);

    // first check cache
    Vector<HI_U8> uuidVector;
    uuidVector.appendArray(uuid, sizeof(uuid[0]) * 16);
    ssize_t hisi_index = mUUIDToLibraryPathMap.indexOfKey(uuidVector);

    if (hisi_index >= 0)
    {
        if (loadLibraryForScheme(mUUIDToLibraryPathMap[hisi_index], uuid))
        {
            mInitCheck = HI_TRUE;
            return;
        }
        else
        {
            HI_LOGE("Failed to load from cached library path!");
            mInitCheck = HI_FALSE;
            return;
        }
    }

    // no luck, have to search
    String8 dirPath("/vendor/lib/mediadrm");
    DIR* pDir = opendir(dirPath.string());

    if (pDir == NULL)
    {
        mInitCheck = HI_FALSE;
        HI_LOGE("Failed to open plugin directory %s", dirPath.string());
        return;
    }

    struct dirent* pEntry;

    while ((pEntry = readdir(pDir)))
    {
        String8 pluginPath;
        pluginPath.append(dirPath);
        pluginPath.append("/");
        pluginPath.append(pEntry->d_name);

        if (pluginPath.getPathExtension() == ".so")
        {
            HI_LOGD("%s,pluginPath = %s", __FUNCTION__, pluginPath.string());

            if (loadLibraryForScheme(pluginPath, uuid))
            {
                mUUIDToLibraryPathMap.add(uuidVector, pluginPath);
                mInitCheck = HI_TRUE;
                closedir(pDir);
                return;
            }
        }
    }

    closedir(pDir);

    HI_LOGE("Failed to find drm plugin");
    mInitCheck = HI_FALSE;
}

HI_BOOL Drm::loadLibraryForScheme(const String8& path, const HI_U8 uuid[16])
{
    TRACE_INFO();
    // get strong pointer to open shared library
    ssize_t hisi_index = mLibraryPathToOpenLibraryMap.indexOfKey(path);

    if (hisi_index >= 0)
    {
        mLibrary = mLibraryPathToOpenLibraryMap[hisi_index].promote();
    }
    else
    {
        hisi_index = mLibraryPathToOpenLibraryMap.add(path, NULL);
    }

    if (!mLibrary.get())
    {
        mLibrary = new SharedLibrary(path);

        if (!*mLibrary)
        {
            HI_LOGE("%s mLibrary is NULL", __FUNCTION__);
            return HI_FALSE;
        }

        mLibraryPathToOpenLibraryMap.replaceValueAt(hisi_index, mLibrary);
    }

    typedef DrmFactory *(*CreateDrmFactoryFunc)();
    CreateDrmFactoryFunc hisi_createDrmFactory =
        (CreateDrmFactoryFunc)(mLibrary->lookup("createDrmFactory"));
    HI_LOGD("%s hisi_createDrmFactory result:%p", __FUNCTION__, hisi_createDrmFactory);

    if (hisi_createDrmFactory == NULL ||
        (mFactory = hisi_createDrmFactory()) == NULL ||
        !mFactory->isCryptoSchemeSupported(uuid))
    {
        closeFactory();
        HI_LOGE("%s error occur in create drm factory", __FUNCTION__);

        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL Drm::isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);
    if (!mFactory)
    {
        findFactoryForScheme(uuid);

        if (mInitCheck != HI_TRUE)
        {
            HI_LOGE("%s drm plugin not init", __FUNCTION__);
            return HI_FALSE;
        }
    }

    if (!mFactory->isCryptoSchemeSupported(uuid))
    {
        HI_LOGE("%s drm plugin not supported", __FUNCTION__);
        return HI_FALSE;
    }

    if (mimeType != "")
    {
        return (HI_BOOL)(mFactory->isContentTypeSupported(mimeType));
    }

    return HI_FALSE;
}

HI_S32 Drm::createPlugin(const HI_U8 uuid[16])
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mPlugin != NULL)
    {
        HI_LOGE("%s drm plugin already exist", __FUNCTION__);
        return HI_FAILURE;
    }

    if (!mFactory || !mFactory->isCryptoSchemeSupported(uuid))
    {
        findFactoryForScheme(uuid);
    }

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    HI_S32 result = mFactory->createDrmPlugin(uuid, &mPlugin);

    mPlugin->setListener(this);

    return result;
}

HI_S32 Drm::destroyPlugin()
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    delete mPlugin;
    mPlugin = NULL;

    return HI_SUCCESS;
}

HI_S32 Drm::openSession(Vector<HI_U8>& sessionId)
{
    HI_S32 result = HI_FAILURE;

    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    result = mPlugin->openSession(sessionId);

    if (result == HI_SUCCESS)
    {
        HI_LOGI("mPlugin openSession OK!");
        DrmSessionManager::Instance()->addSession(getCallingPid(), mDrmSessionClient, sessionId);
    }

    return result;
}

HI_S32 Drm::closeSession(Vector<HI_U8> const& sessionId)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    HI_S32 err = mPlugin->closeSession(sessionId);

    if (err == OK)
    {
        DrmSessionManager::Instance()->removeSession(sessionId);
    }

    return err;
}

HI_S32 Drm::getKeyRequest(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& initData,
                          String8 const& mimeType, DrmPlugin::KeyType keyType,
                          KeyedVector<String8, String8> const& optionalParameters,
                          Vector<HI_U8>& request, String8& defaultUrl,
                          DrmPlugin::KeyRequestType* keyRequestType)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->getKeyRequest(sessionId, initData, mimeType, keyType,
                                  optionalParameters, request, defaultUrl,
                                  keyRequestType);
}

HI_S32 Drm::provideKeyResponse(Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& response,
                               Vector<HI_U8>& keySetId)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->provideKeyResponse(sessionId, response, keySetId);
}

HI_S32 Drm::removeKeys(Vector<HI_U8> const& keySetId)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->removeKeys(keySetId);
}

HI_S32 Drm::restoreKeys(Vector<HI_U8> const& sessionId,
                        Vector<HI_U8> const& keySetId)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->restoreKeys(sessionId, keySetId);
}

HI_S32 Drm::queryKeyStatus(Vector<HI_U8> const& sessionId,
                           KeyedVector<String8, String8>& infoMap)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->queryKeyStatus(sessionId, infoMap);
}

HI_S32 Drm::getProvisionRequest(String8 const& certType, String8 const& certAuthority,
                                Vector<HI_U8>& request, String8& defaultUrl)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->getProvisionRequest(certType, certAuthority,
                                        request, defaultUrl);
}

HI_S32 Drm::provideProvisionResponse(Vector<HI_U8> const& response,
                                     Vector<HI_U8>& certificate,
                                     Vector<HI_U8>& wrappedKey)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->provideProvisionResponse(response, certificate, wrappedKey);
}

HI_S32 Drm::unprovisionDevice()
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }
    /*checkPermission 永远返回非零值 ， 此处做预留，以后可扩展*/
/*
    if (!checkPermission("permission.REMOVE_DRM_CERTIFICATES"))
    {
        return HI_FAILURE;
    }
*/
    return mPlugin->unprovisionDevice();
}

HI_S32 Drm::getSecureStops(List<Vector<HI_U8> >& secureStops)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->getSecureStops(secureStops);
}

HI_S32 Drm::getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->getSecureStop(ssid, secureStop);
}

HI_S32 Drm::releaseSecureStops(Vector<HI_U8> const& ssRelease)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->releaseSecureStops(ssRelease);
}

HI_S32 Drm::releaseAllSecureStops()
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->releaseAllSecureStops();
}

HI_S32 Drm::getPropertyString(String8 const& name, String8& value )
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->getPropertyString(name, value);
}

HI_S32 Drm::getPropertyByteArray(String8 const& name, Vector<HI_U8>& value )
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->getPropertyByteArray(name, value);
}

HI_S32 Drm::setPropertyString(String8 const& name, String8 const& value )
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->setPropertyString(name, value);
}

HI_S32 Drm::setPropertyByteArray(String8 const& name,
                                 Vector<HI_U8> const& value )
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    return mPlugin->setPropertyByteArray(name, value);
}

HI_S32 Drm::setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                               String8 const& algorithm)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->setCipherAlgorithm(sessionId, algorithm);
}

HI_S32 Drm::setMacAlgorithm(Vector<HI_U8> const& sessionId,
                            String8 const& algorithm)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->setMacAlgorithm(sessionId, algorithm);
}

HI_S32 Drm::encrypt(Vector<HI_U8> const& sessionId,
                    Vector<HI_U8> const& keyId,
                    Vector<HI_U8> const& input,
                    Vector<HI_U8> const& iv,
                    Vector<HI_U8>& output)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->encrypt(sessionId, keyId, input, iv, output);
}

HI_S32 Drm::decrypt(Vector<HI_U8> const& sessionId,
                    Vector<HI_U8> const& keyId,
                    Vector<HI_U8> const& input,
                    Vector<HI_U8> const& iv,
                    Vector<HI_U8>& output)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->decrypt(sessionId, keyId, input, iv, output);
}

HI_S32 Drm::sign(Vector<HI_U8> const& sessionId,
                 Vector<HI_U8> const& keyId,
                 Vector<HI_U8> const& message,
                 Vector<HI_U8>& signature)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->sign(sessionId, keyId, message, signature);
}

HI_S32 Drm::verify(Vector<HI_U8> const& sessionId,
                   Vector<HI_U8> const& keyId,
                   Vector<HI_U8> const& message,
                   Vector<HI_U8> const& signature,
                   HI_BOOL& match)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->verify(sessionId, keyId, message, signature, (bool&)match);
}

HI_S32 Drm::signRSA(Vector<HI_U8> const& sessionId,
                    String8 const& algorithm,
                    Vector<HI_U8> const& message,
                    Vector<HI_U8> const& wrappedKey,
                    Vector<HI_U8>& signature)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s drm plugin not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s drm plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }
    /*checkPermission 永远返回非零值 ， 此处做预留，以后可扩展*/
/*
    if (!checkPermission("permission.ACCESS_DRM_CERTIFICATES"))
    {
        return HI_FAILURE;
    }
*/
    DrmSessionManager::Instance()->useSession(sessionId);

    return mPlugin->signRSA(sessionId, algorithm, message, wrappedKey, signature);
}

HI_VOID Drm::binderDied(const wp<IBinder>& the_late_who)
{
    TRACE_INFO();
    mEventLock.lock();
    mListener.clear();
    mEventLock.unlock();

    Mutex::Autolock autoLock(mLock);
    delete mPlugin;
    mPlugin = NULL;
    closeFactory();
}

HI_VOID Drm::writeByteArray(Parcel& obj, Vector<HI_U8> const* array)
{
    if (array && array->size())
    {
        obj.writeInt32(array->size());
        obj.write(array->array(), array->size());
    }
    else
    {
        obj.writeInt32(0);
    }
}
