#ifndef CRYPTOCLIENT_H__
#define  CRYPTOCLIENT_H__

#include <binder/IInterface.h>
#include <CryptoAPI.h>
#include "IDrmService.h"
#include "DrmDefines.h"

using namespace android;

class CryptoClient : public RefBase
{
public:
    CryptoClient(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID *initData, HI_S32 initSize);
    ~CryptoClient();

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]);

    virtual HI_BOOL requiresSecureDecoderComponent(
        const HI_CHAR* mime);

    virtual HI_VOID notifyResolution(HI_U32 width, HI_U32 height);

    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId);

    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        CryptoPlugin::Mode mode,
        const HI_VOID *sharedBuffer,size_t offset,
        const CryptoPlugin::SubSample* subSamples, size_t numSubSamples,
        HI_VOID* dstPtr,
        AString* errorDetailMsg);

private:
    HI_VOID makeCrypto(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID *initData, HI_S32 initSize);
    static const sp<IDrmService> getDrmService(); /**< get drm service */
    static  sp<IDrmService>    msDrmService;
    sp<ICrypto>                   mCrypto;                /**< remote drm operation handle */
};

#endif // CRYPTOCLIENT_H__
