#ifndef CRYPTO_H__
#define CRYPTO_H__
#include <utils/threads.h>
#include <utils/KeyedVector.h>
#include "../client/ICrypto.h"
#include "SharedLibrary.h"

using namespace android;

class Crypto : public BnCrypto
{
public:
    Crypto();
    virtual ~Crypto();

    virtual HI_BOOL initCheck() const;

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]);

    virtual HI_S32 createPlugin(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* data, HI_S32 size);

    virtual HI_S32 destroyPlugin();

    virtual HI_BOOL requiresSecureDecoderComponent(
        const HI_CHAR* mime);

    virtual HI_VOID notifyResolution(HI_U32 width, HI_U32 height);

    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId);

    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        CryptoPlugin::Mode mode,
        const HI_VOID *sharedBuffer, HI_S32 offset,
        const CryptoPlugin::SubSample* subSamples, HI_S32 numSubSamples,
        HI_VOID* dstPtr,
        AString* errorDetailMsg);

private:
    mutable Mutex mLock;

    HI_BOOL mInitCheck;
    sp<SharedLibrary> mLibrary;
    CryptoFactory* mFactory;
    CryptoPlugin* mPlugin;

    static KeyedVector<Vector<HI_U8>, String8> mUUIDToLibraryPathMap;
    static KeyedVector<String8, wp<SharedLibrary> > mLibraryPathToOpenLibraryMap;
    static Mutex mMapLock;

    HI_VOID findFactoryForScheme(const HI_U8 uuid[HI_DRM_UUID_LEN]);
    HI_BOOL loadLibraryForScheme(const String8& path, const HI_U8 uuid[HI_DRM_UUID_LEN]);
    HI_VOID closeFactory();

};

#endif  // CRYPTO_H__
