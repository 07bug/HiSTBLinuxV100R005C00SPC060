#ifndef DRMCLIENT_H__
#define DRMCLIENT_H__
#include <common/hi_type.h>
#include <binder/IInterface.h>
#include <DrmDefines.h>
#include <DrmAPI.h>
#include "IDrmService.h"
#include "IDrmClient.h"

#ifndef DRMSERVICE_SLEEP
#define DRMSERVICE_SLEEP(ms) \
do \
{ \
struct timespec _ts; \
_ts.tv_sec = (ms) >= 1000 ? (ms)/1000 : 0; \
_ts.tv_nsec = (_ts.tv_sec > 0) ? ((ms)%1000)*1000000LL : (ms)*1000000LL; \
(HI_VOID)nanosleep(&_ts, NULL); \
} while (0)
#endif

using namespace android;

class DrmClient : public BnDrmClient
{
public:
    DrmClient(const HI_U8 uuid[16]);
    ~DrmClient();

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType);

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
                          Vector<HI_U8> const& signature,
                          HI_BOOL& match);

    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature);

    virtual HI_S32 setListener(DrmListener* listener);
    virtual HI_VOID notify(DrmPlugin::EventType eventType, HI_S32 extra, const Parcel* obj);

private:
    HI_VOID makeDrm(const HI_U8 uuid[16]);
    static const sp<IDrmService> getDrmService(); /**< get drm service */
    virtual HI_VOID readVector(const Parcel* data, Vector<HI_U8>& vector) const;
    virtual HI_VOID readKeyStatusList(const Parcel* data, Vector<HI_KEY_STATUS>& list) const;

    static  sp<IDrmService>    msDrmService;
    sp<IDrm>                   mDrm;                /**< remote drm operation handle */
    DrmListener* mListener;
};
#endif // DRMCLIENT_H__
