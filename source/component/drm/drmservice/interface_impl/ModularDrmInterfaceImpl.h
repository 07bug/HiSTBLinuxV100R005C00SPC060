#ifndef MODULAR_DRM_INTERFACE_IMPL_H__
#define MODULAR_DRM_INTERFACE_IMPL_H__

#include <ModularDrmInterface.h>
#include <DrmClient.h>
#include "Drm.h"

class ModularDrmInterfaceImpl: public ModularDrmInterface
{
public:

    ModularDrmInterfaceImpl(const HI_U8 uuid[HI_DRM_UUID_LEN]);
    ~ModularDrmInterfaceImpl();

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_CHAR* mimeType);
    virtual HI_S32 openSession(Vector<HI_U8>& sessionId);
    virtual HI_S32 closeSession(Vector<HI_U8> const& sessionId);
    virtual HI_S32 getKeyRequest(Vector<HI_U8> const& scope,
                                 Vector<HI_U8> const& initData,
                                 HI_CHAR const* mimeType, HI_DRM_KEY_TYPE keyType,
                                 KeyedVector<String8, String8> const& optionalParameters,
                                 HI_DRM_KEY_REQUEST* pKeyRequest);

    virtual HI_S32 provideKeyResponse(Vector<HI_U8> const& scope,
                                      Vector<HI_U8> const& response,
                                      Vector<HI_U8>& keySetId);
    virtual HI_S32 removeKeys(Vector<HI_U8> const& sessionId);
    virtual HI_S32 restoreKeys(Vector<HI_U8> const& sessionId, Vector<HI_U8> const& keySetId);
    virtual HI_S32 queryKeyStatus(Vector<HI_U8> const& sessionId,
                                  KeyedVector<String8, String8>& infoMap);
    virtual HI_S32 getProvisionRequest(String8 const& certType,
                                       String8 const& certAuthority,
                                       HI_DRM_PROVITION_REQUEST* request);

    virtual HI_S32 provideProvisionResponse(Vector<HI_U8> const& response,
                                            Vector<HI_U8>& certificate,
                                            Vector<HI_U8>& wrappedKey);

    virtual HI_S32 unprovisionDevice();

    virtual HI_S32 getSecureStops(List<Vector<HI_U8> >& secureStops);
    virtual HI_S32 getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop);
    virtual HI_S32 releaseSecureStops(Vector<HI_U8> const& ssRelease);
    virtual HI_S32 releaseAllSecureStops();

    virtual HI_S32 getPropertyString(String8 const& name, String8& value);
    virtual HI_S32 getPropertyByteArray(String8 const& name,
                                        Vector<HI_U8>& value);

    virtual HI_S32 setPropertyString(String8 const& name,
                                     String8 const& value );
    virtual HI_S32 setPropertyByteArray(String8 const& name,
                                        Vector<HI_U8> const& value);
    virtual HI_S32 setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                      String8 const& algorithm);

    virtual HI_S32 setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                   String8 const& algorithm);

    virtual HI_S32 encrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output);
    virtual HI_S32 decrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output);
    virtual HI_S32 sign(Vector<HI_U8> const& sessionId,
                        Vector<HI_U8> const& keyId,
                        Vector<HI_U8> const& message,
                        Vector<HI_U8>& signature);
    virtual HI_S32 verify(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& message,
                          Vector<HI_U8>const& signature,
                          HI_BOOL& match);

    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature);

    virtual HI_S32 setListener(DrmListener* listener);

private:
#ifdef MULTI_PROCESS
    DrmClient* mDrmClient; /*drm object handle*/
#else
    Drm* mDrmClient; /*drm object handle*/
#endif

    ModularDrmInterfaceImpl(const ModularDrmInterfaceImpl& modulardrm);
    ModularDrmInterfaceImpl& operator = (const ModularDrmInterfaceImpl& modulardrm);
};

#endif //MODULAR_DRM_INTERFACE_IMPL_H__
