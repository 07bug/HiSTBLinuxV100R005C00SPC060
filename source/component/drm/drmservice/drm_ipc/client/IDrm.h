#ifndef IDRM_H__
#define IDRM_H__
#include <common/hi_type.h>
#include <binder/IInterface.h>
#include <DrmAPI.h>
#include "IDrmClient.h"

using namespace android;

class IDrm : public IInterface
{

public:

    DECLARE_META_INTERFACE(Drm);

    virtual HI_BOOL initCheck() = 0;

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType) = 0;

    virtual HI_S32 createPlugin(const HI_U8 uuid[16]) = 0;

    virtual HI_S32 destroyPlugin() = 0;

    virtual HI_S32 openSession(Vector<HI_U8>& sessionId) = 0;

    virtual HI_S32 closeSession(Vector<HI_U8> const& sessionId) = 0;

    virtual HI_S32 getKeyRequest(Vector<HI_U8> const& sessionId,
                                 Vector<HI_U8> const& initData,
                                 String8 const& mimeType, DrmPlugin::KeyType keyType,
                                 KeyedVector<String8, String8> const& optionalParameters,
                                 Vector<HI_U8>& request, String8& defaultUrl,
                                 DrmPlugin::KeyRequestType* keyRequestType) = 0;

    virtual HI_S32 provideKeyResponse(Vector<HI_U8> const& sessionId,
                                      Vector<HI_U8> const& response,
                                      Vector<HI_U8>& keySetId) = 0;

    virtual HI_S32 removeKeys(Vector<HI_U8> const& keySetId) = 0;

    virtual HI_S32 restoreKeys(Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& keySetId) = 0;

    virtual HI_S32 queryKeyStatus(Vector<HI_U8> const& sessionId,
                                  KeyedVector<String8, String8>& infoMap) = 0;

    virtual HI_S32 getProvisionRequest(String8 const& certType,
                                       String8 const& certAuthority,
                                       Vector<HI_U8>& request,
                                       String8& defaulUrl) = 0;

    virtual HI_S32 provideProvisionResponse(Vector<HI_U8> const& response,
                                            Vector<HI_U8>& certificate,
                                            Vector<HI_U8>& wrappedKey) = 0;

    virtual HI_S32 unprovisionDevice() = 0;

    virtual HI_S32 getSecureStops(List<Vector<HI_U8> >& secureStops) = 0;
    virtual HI_S32 getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop) = 0;

    virtual HI_S32 releaseSecureStops(Vector<HI_U8> const& ssRelease) = 0;
    virtual HI_S32 releaseAllSecureStops() = 0;

    virtual HI_S32 getPropertyString(String8 const& name, String8& value) = 0;
    virtual HI_S32 getPropertyByteArray(String8 const& name,
                                        Vector<HI_U8>& value) = 0;
    virtual HI_S32 setPropertyString(String8 const& name,
                                     String8 const& value ) = 0;
    virtual HI_S32 setPropertyByteArray(String8 const& name,
                                        Vector<HI_U8> const& value) = 0;

    virtual HI_S32 setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                      String8 const& algorithm) = 0;

    virtual HI_S32 setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                   String8 const& algorithm) = 0;

    virtual HI_S32 encrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output) = 0;

    virtual HI_S32 decrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output) = 0;

    virtual HI_S32 sign(Vector<HI_U8> const& sessionId,
                        Vector<HI_U8> const& keyId,
                        Vector<HI_U8> const& message,
                        Vector<HI_U8>& signature) = 0;

    virtual HI_S32 verify(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& message,
                          Vector<HI_U8> const& signature,
                          HI_BOOL& match) = 0;

    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature) = 0;

    virtual HI_S32 setListener(const sp<IDrmClient>& listener) = 0;
};

class BnDrm : public BnInterface<IDrm>
{
public:
    virtual status_t onTransact(
        uint32_t code, const Parcel& data, Parcel* reply,
        uint32_t flags = 0);
private:
    HI_VOID readVector(const Parcel& data, Vector<HI_U8>& vector);
    HI_VOID writeVector(Parcel* reply, Vector<HI_U8> const& vector);
};

#endif // IDRM_H__
