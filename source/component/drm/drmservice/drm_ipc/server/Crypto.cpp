#define LOG_TAG "Crypto"
#include <utils/Logger.h>

#include <dirent.h>
#include <dlfcn.h>

#include <binder/IMemory.h>
#include <CryptoAPI.h>
#include "Crypto.h"

KeyedVector<Vector<HI_U8>, String8> Crypto::mUUIDToLibraryPathMap;
KeyedVector<String8, wp<SharedLibrary> > Crypto::mLibraryPathToOpenLibraryMap;
Mutex Crypto::mMapLock;

#define TRACE_INFO() HI_LOGD("%s",__FUNCTION__)

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

Crypto::Crypto()
    : mInitCheck(HI_FALSE),
      mFactory(NULL),
      mPlugin(NULL)
{
    TRACE_INFO();
}

Crypto::~Crypto()
{
    TRACE_INFO();
    delete mPlugin;
    mPlugin = NULL;
    closeFactory();
}

HI_VOID Crypto::closeFactory()
{
    TRACE_INFO();
    delete mFactory;
    mFactory = NULL;
    mLibrary.clear();
}

HI_BOOL Crypto::initCheck() const
{
    return mInitCheck;
}

/*
 * Search the plugins directory for a plugin that supports the scheme
 * specified by uuid
 *
 * If found:
 *    mLibrary holds a strong pointer to the dlopen'd library
 *    mFactory is set to the library's factory method
 *    mInitCheck is set to OK
 *
 * If not found:
 *    mLibrary is cleared and mFactory are set to NULL
 *    mInitCheck is set to an error (!OK)
 */
HI_VOID Crypto::findFactoryForScheme(const HI_U8 uuid[HI_DRM_UUID_LEN])
{
    TRACE_INFO();

    //clear facotry and plugin library
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
            HI_LOGE("Successed to load from cached library path!");
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

    if (pDir)
    {
        struct dirent* pEntry;

        while ((pEntry = readdir(pDir)))
        {
            String8 pluginPath;
            pluginPath.append(dirPath);
            pluginPath.append("/");
            pluginPath.append(pEntry->d_name);

            if (pluginPath.getPathExtension() == ".so")
            {
                HI_LOGD("path = %s", pluginPath.string());

                if (loadLibraryForScheme(pluginPath, uuid))
                {
                    HI_LOGD("Successed to load drm lib = %s", pluginPath.string());
                    mUUIDToLibraryPathMap.add(uuidVector, pluginPath);
                    mInitCheck = HI_TRUE;
                    closedir(pDir);
                    return;
                }
            }
        }

        closedir(pDir);
    }

    // try the legacy libdrmdecrypt.so
    String8 pluginPathName;
    pluginPathName = "libdrmdecrypt.so";

    if (loadLibraryForScheme(pluginPathName, uuid))
    {
        HI_LOGD("Successed to load drm lib = %s", pluginPathName.string());
        mUUIDToLibraryPathMap.add(uuidVector, pluginPathName);
        mInitCheck = HI_TRUE;
        return;
    }

    mInitCheck = HI_FALSE;

    HI_LOGE("%s,failed to load drm library,dir path(%s)", dirPath.string());
}

HI_BOOL Crypto::loadLibraryForScheme(const String8& path, const HI_U8 uuid[16])
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
            HI_LOGE("loadLibraryForScheme failed:%s", mLibrary->lastError());
            return HI_FALSE;
        }

        mLibraryPathToOpenLibraryMap.replaceValueAt(hisi_index, mLibrary);
    }

    typedef CryptoFactory *(*CreateCryptoFactoryFunc)();

    CreateCryptoFactoryFunc hisi_createCryptoFactory =
        (CreateCryptoFactoryFunc)(mLibrary->lookup("createCryptoFactory"));

    if (hisi_createCryptoFactory == NULL ||
        (mFactory = hisi_createCryptoFactory()) == NULL ||
        !mFactory->isCryptoSchemeSupported(uuid))
    {
        HI_LOGE("hisi_createCryptoFactory failed:%s", mLibrary->lastError());
        closeFactory();
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL Crypto::isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN])
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (!mFactory)
    {
        HI_LOGD("%s mFactory is NULL", __FUNCTION__);
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

    return HI_TRUE;
}

HI_S32 Crypto::createPlugin(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* data, HI_S32 size)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mPlugin != NULL)
    {
        HI_LOGE("plugin already exist");
        return HI_FAILURE;
    }

    if (!mFactory || !mFactory->isCryptoSchemeSupported(uuid))
    {
        findFactoryForScheme(uuid);
    }

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("Crypto not init");
        return HI_FAILURE;
    }

    return mFactory->createPlugin(uuid, data, size, &mPlugin);
}

HI_S32 Crypto::destroyPlugin()
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("Crypto not init");
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("plugin is null");
        return HI_FAILURE;
    }

    delete mPlugin;
    mPlugin = NULL;

    return HI_SUCCESS;
}

HI_BOOL Crypto::requiresSecureDecoderComponent(const HI_CHAR* mime)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("Crypto not init");
        return HI_FALSE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("plugin is null");
        return HI_FALSE;
    }

    return (HI_BOOL)(mPlugin->requiresSecureDecoderComponent(mime));
}

HI_S32 Crypto::decrypt(
    HI_BOOL secure,
    const HI_U8 key[HI_DRM_KEY_LEN],
    const HI_U8 iv[HI_DRM_IV_LEN],
    CryptoPlugin::Mode mode,
    const HI_VOID* sharedBuffer, HI_S32 offset,
    const CryptoPlugin::SubSample* subSamples, HI_S32 numSubSamples,
    HI_VOID* dstPtr,
    AString* errorDetailMsg)
{
    HI_S32 ret = HI_FAILURE;
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck != HI_TRUE)
    {
        HI_LOGE("%s,crypto not init", __FUNCTION__);
        return HI_FAILURE;
    }

    if (mPlugin == NULL)
    {
        HI_LOGE("%s,crypto plugin is null", __FUNCTION__);
        return HI_FAILURE;
    }

    const HI_VOID* srcPtr = sharedBuffer;/* + offset;*/

    ret = mPlugin->decrypt(secure, key, iv, mode, srcPtr,
                           subSamples, numSubSamples, dstPtr, errorDetailMsg);

    HI_LOGD("%s,crypto decrypt done ,ret = %d", __FUNCTION__, ret);

    return ret;
}

HI_VOID Crypto::notifyResolution(HI_U32 width, HI_U32 height)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    if (mInitCheck == HI_TRUE && mPlugin != NULL)
    {
        mPlugin->notifyResolution(width, height);
    }
}

HI_S32 Crypto::setMediaDrmSession(const Vector<HI_U8>& sessionId)
{
    TRACE_INFO();
    Mutex::Autolock autoLock(mLock);

    HI_S32 result = HI_FAILURE;

    if (mInitCheck == HI_TRUE && mPlugin != NULL)
    {
        result = mPlugin->setMediaDrmSession(sessionId);
    }

    return result;
}
