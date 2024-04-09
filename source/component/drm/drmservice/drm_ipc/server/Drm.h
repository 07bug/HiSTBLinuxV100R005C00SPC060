#ifndef DRM_H__
#define DRM_H__
#include <common/hi_type.h>
#include <utils/threads.h>
#include "../client/IDrm.h"
#include "../client/IDrmClient.h"
#include "SharedLibrary.h"
#include "DrmSessionClientInterface.h"

using namespace android;

class Drm : public BnDrm, public IBinder::DeathRecipient, public DrmPluginListener
{
public:

    Drm();
    virtual ~Drm();

    virtual HI_BOOL initCheck();

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType);

    virtual HI_S32 createPlugin(const HI_U8 uuid[16]);

    virtual HI_S32 destroyPlugin();

    virtual HI_S32 openSession(Vector<HI_U8>& sessionId);

    virtual HI_S32 closeSession(Vector<HI_U8> const& sessionId);

    virtual HI_S32 getKeyRequest(Vector<HI_U8> const& sessionId,
                                 Vector<HI_U8> const& initData,
                                 String8 const& mimeType, DrmPlugin::KeyType keyType,
                                 KeyedVector<String8, String8> const& optionalParameters,
                                 Vector<HI_U8>& request, String8& defaultUrl,
                                 DrmPlugin::KeyRequestType* keyRequestType);

    virtual HI_S32 provideKeyResponse(Vector<HI_U8> const& sessionId,
                                      Vector<HI_U8> const& response,
                                      Vector<HI_U8>& keySetId);

    virtual HI_S32 removeKeys(Vector<HI_U8> const& keySetId);

    virtual HI_S32 restoreKeys(Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& keySetId);

    virtual HI_S32 queryKeyStatus(Vector<HI_U8> const& sessionId,
                                  KeyedVector<String8, String8>& infoMap);

    virtual HI_S32 getProvisionRequest(String8 const& certType,
                                       String8 const& certAuthority,
                                       Vector<HI_U8>& request,
                                       String8& defaulUrl);

    virtual HI_S32 provideProvisionResponse(Vector<HI_U8> const& response,
                                            Vector<HI_U8>& certificate,
                                            Vector<HI_U8>& wrappedKey);

    virtual HI_S32 unprovisionDevice();

    virtual HI_S32 getSecureStops(List<Vector<HI_U8> >& secureStops);
    virtual HI_S32 getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop);

    virtual HI_S32 releaseSecureStops(Vector<HI_U8> const& ssRelease);
    virtual HI_S32 releaseAllSecureStops();

    virtual HI_S32 getPropertyString(String8 const& name, String8& value );
    virtual HI_S32 getPropertyByteArray(String8 const& name,
                                        Vector<HI_U8>& value );
    virtual HI_S32 setPropertyString(String8 const& name, String8 const& value );
    virtual HI_S32 setPropertyByteArray(String8 const& name,
                                        Vector<HI_U8> const& value );

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
                          Vector<HI_U8> const& signature,
                          HI_BOOL& match);

    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature);

    virtual HI_S32 setListener(const sp<IDrmClient>& listener);

    virtual HI_VOID sendEvent(DrmPlugin::EventType eventType, int extra,
                           Vector<HI_U8> const* sessionId,
                           Vector<HI_U8> const* data);

    virtual HI_VOID sendExpirationUpdate(Vector<HI_U8> const* sessionId,
                                      HI_S64 expiryTimeInMS);

    virtual HI_VOID sendKeysChange(Vector<HI_U8> const* sessionId,
                                Vector<DrmPlugin::KeyStatus> const* keyStatusList,
                                HI_BOOL hasNewUsableKey);

    virtual HI_VOID binderDied(const wp<IBinder>& the_late_who);

private:
    static Mutex mLock;

    HI_BOOL mInitCheck;

    sp<DrmSessionClientInterface> mDrmSessionClient;

    sp<IDrmClient> mListener;
    mutable Mutex mEventLock;
    mutable Mutex mNotifyLock;

    sp<SharedLibrary> mLibrary;
    DrmFactory* mFactory;
    DrmPlugin* mPlugin;

    static KeyedVector<Vector<HI_U8>, String8> mUUIDToLibraryPathMap;
    static KeyedVector<String8, wp<SharedLibrary> > mLibraryPathToOpenLibraryMap;
    static Mutex mMapLock;

    HI_VOID findFactoryForScheme(const HI_U8 uuid[16]);
    HI_BOOL loadLibraryForScheme(const String8& path, const HI_U8 uuid[16]);
    HI_VOID closeFactory();
    HI_VOID writeByteArray(Parcel& obj, Vector<HI_U8> const* array);

};

#endif  // DRM_H__
