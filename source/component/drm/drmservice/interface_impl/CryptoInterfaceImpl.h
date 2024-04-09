#ifndef CRYPTO_INTERFACE_IMPL_H__
#define CRYPTO_INTERFACE_IMPL_H__

#include <CryptoInterface.h>
#include <CryptoClient.h>
#include "Crypto.h"

class CryptoInterfaceImpl : public CryptoInterface
{
public:

    CryptoInterfaceImpl(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* initData, HI_S32 initSize);
    ~CryptoInterfaceImpl();

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]);
    virtual HI_BOOL requiresSecureDecoderComponent(const HI_CHAR* mime);
    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId);
    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        HI_CRYPTO_MODE mode,
        const HI_VOID* pSrc, HI_S32 s32srcSize,
        const HI_DRM_SUBSAMPLES* subSamples, HI_S32 numSubSamples,
        HI_VOID* pDst,
        String8 &errorDetailMsg);
private:
#ifdef MULTI_PROCESS
    CryptoClient* mCryptoClient; /*crypto client object handle*/
#else
    Crypto* mCryptoClient; /*crypto client object handle*/
#endif
    CryptoInterfaceImpl(const CryptoInterfaceImpl& crypto);
    CryptoInterfaceImpl& operator = (const CryptoInterfaceImpl& crypto);
};

#endif //CRYPTO_INTERFACE_IMPL_H__
