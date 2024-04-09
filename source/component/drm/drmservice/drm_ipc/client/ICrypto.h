#ifndef ICRYPTO_H__
#define  ICRYPTO_H__
#include <common/hi_type.h>
#include <binder/IInterface.h>
#include <binder/IMemory.h>
#include <CryptoAPI.h>

using namespace android;

struct ICrypto : public IInterface
{

    DECLARE_META_INTERFACE(Crypto);

    virtual HI_BOOL initCheck() const = 0;

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN]) = 0;

    virtual HI_S32 createPlugin(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* data, HI_S32 size) = 0;

    virtual HI_S32 destroyPlugin() = 0;

    virtual HI_BOOL requiresSecureDecoderComponent(const HI_CHAR* mime) = 0;

    virtual HI_VOID notifyResolution(HI_U32 width, HI_U32 height) = 0;

    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId) = 0;

    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        CryptoPlugin::Mode mode,
        const HI_VOID* sharedBuffer, HI_S32 offset,
        const CryptoPlugin::SubSample* subSamples, HI_S32 numSubSamples,
        HI_VOID* dstPtr,
        AString* errorDetailMsg) = 0;

};

struct BnCrypto : public BnInterface<ICrypto>
{
    virtual status_t onTransact(
        HI_U32 code, const Parcel& data, Parcel* reply,
        HI_U32 flags = 0);
private:
    HI_VOID readVector(const Parcel& data, Vector<HI_U8>& vector) const;
    //HI_VOID writeVector(Parcel* reply, Vector<HI_U8> const& vector) const;
};

#endif // ICRYPTO_H__
