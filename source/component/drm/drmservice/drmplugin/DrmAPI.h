#ifndef DRM_API_H_
#define DRM_API_H_

#include <common/hi_type.h>
#include <utils/List.h>
#include <utils/String8.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/threads.h>

namespace android {

    class DrmPlugin;
    class DrmPluginListener;

    class DrmFactory
    {
    public:
        DrmFactory() {}
        virtual ~DrmFactory() {}

        // DrmFactory::isCryptoSchemeSupported can be called to determine
        // if the plugin factory is able to construct plugins that support a
        // given crypto scheme, which is specified by a UUID.
        virtual bool isCryptoSchemeSupported(const HI_U8 uuid[16]) = 0;

        // DrmFactory::isContentTypeSupported can be called to determine
        // if the plugin factory is able to construct plugins that support a
        // given media container format specified by mimeType
        virtual bool isContentTypeSupported(const String8& mimeType) = 0;

        // Construct a DrmPlugin for the crypto scheme specified by UUID.
        virtual status_t createDrmPlugin(
            const HI_U8 uuid[16], DrmPlugin** plugin) = 0;

    private:
        DrmFactory(const DrmFactory&);
        DrmFactory& operator=(const DrmFactory&);
    };

    class DrmPlugin
    {
    public:
        enum EventType
        {
            kDrmPluginEventProvisionRequired = 1,
            kDrmPluginEventKeyNeeded,
            kDrmPluginEventKeyExpired,
            kDrmPluginEventVendorDefined,
            kDrmPluginEventSessionReclaimed,
            kDrmPluginEventExpirationUpdate,
            kDrmPluginEventKeysChange,
        };

        // Drm keys can be for offline content or for online streaming.
        // Offline keys are persisted on the device and may be used when the device
        // is disconnected from the network.  The Release type is used to request
        // that offline keys be no longer restricted to offline use.
        enum KeyType
        {
            kKeyType_Offline,
            kKeyType_Streaming,
            kKeyType_Release
        };

        // Enumerate KeyRequestTypes to allow an app to determine the
        // type of a key request returned from getKeyRequest.
        enum KeyRequestType
        {
            kKeyRequestType_Unknown,
            kKeyRequestType_Initial,
            kKeyRequestType_Renewal,
            kKeyRequestType_Release
        };

        // Enumerate KeyStatusTypes which indicate the state of a key
        enum KeyStatusType
        {
            kKeyStatusType_Usable,
            kKeyStatusType_Expired,
            kKeyStatusType_OutputNotAllowed,
            kKeyStatusType_StatusPending,
            kKeyStatusType_InternalError
        };

        // Used by sendKeysChange to report the usability status of each
        // key to the app.
        struct KeyStatus
        {
            Vector<HI_U8> mKeyId;
            KeyStatusType mType;
        };

        DrmPlugin() {}
        virtual ~DrmPlugin() {}

        // Open a new session with the DrmPlugin object.  A session ID is returned
        // in the sessionId parameter.
        virtual status_t openSession(Vector<HI_U8>& sessionId) = 0;

        // Close a session on the DrmPlugin object.
        virtual status_t closeSession(Vector<HI_U8> const& sessionId) = 0;

        // A key request/response exchange occurs between the app and a License
        // Server to obtain the keys required to decrypt the content.  getKeyRequest()
        // is used to obtain an opaque key request blob that is delivered to the
        // license server.
        //
        // The scope parameter may be a sessionId or a keySetId, depending on the
        // specified keyType.  When the keyType is kKeyType_Offline or
        // kKeyType_Streaming, scope should be set to the sessionId the keys will be
        // provided to.  When the keyType is kKeyType_Release, scope should be set to
        // the keySetId of the keys being released.  Releasing keys from a device
        // invalidates them for all sessions.
        //
        // The init data passed to getKeyRequest is container-specific and its
        // meaning is interpreted based on the mime type provided in the mimeType
        // parameter to getKeyRequest.  It could contain, for example, the content
        // ID, key ID or other data obtained from the content metadata that is required
        // in generating the key request.  Init may be null when keyType is
        // kKeyType_Release.
        //
        // mimeType identifies the mime type of the content
        //
        // keyType specifies if the keys are to be used for streaming or offline content
        //
        // optionalParameters are included in the key request message to allow a
        // client application to provide additional message parameters to the server.
        //
        // If successful, the opaque key request blob is returned to the caller.
        virtual status_t
        getKeyRequest(Vector<HI_U8> const& scope,
                  Vector<HI_U8> const& initData,
                  String8 const& mimeType, KeyType keyType,
                  KeyedVector<String8, String8> const& optionalParameters,
                  Vector<HI_U8>& request, String8& defaultUrl,
                  KeyRequestType* keyRequestType) = 0;

        //
        // After a key response is received by the app, it is provided to the
        // Drm plugin using provideKeyResponse.
        //
        // scope may be a sessionId or a keySetId depending on the type of the
        // response.  Scope should be set to the sessionId when the response is
        // for either streaming or offline key requests.  Scope should be set to the
        // keySetId when the response is for a release request.
        //
        // When the response is for an offline key request, a keySetId is returned
        // in the keySetId vector parameter that can be used to later restore the
        // keys to a new session with the method restoreKeys. When the response is
        // for a streaming or release request, no keySetId is returned.
        //
        virtual status_t provideKeyResponse(Vector<HI_U8> const& scope,
                                            Vector<HI_U8> const& response,
                                            Vector<HI_U8>& keySetId) = 0;

        // Remove the current keys from a session
        virtual status_t removeKeys(Vector<HI_U8> const& sessionId) = 0;

        // Restore persisted offline keys into a new session.  keySetId identifies
        // the keys to load, obtained from a prior call to provideKeyResponse().
        virtual status_t restoreKeys(Vector<HI_U8> const& sessionId,
                                     Vector<HI_U8> const& keySetId) = 0;

        // Request an informative description of the license for the session.  The status
        // is in the form of {name, value} pairs.  Since DRM license policies vary by
        // vendor, the specific status field names are determined by each DRM vendor.
        // Refer to your DRM provider documentation for definitions of the field names
        // for a particular DrmEngine.
        virtual status_t
        queryKeyStatus(Vector<HI_U8> const& sessionId,
                       KeyedVector<String8, String8>& infoMap) const = 0;

        // A provision request/response exchange occurs between the app and a
        // provisioning server to retrieve a device certificate.  getProvisionRequest
        // is used to obtain an opaque key request blob that is delivered to the
        // provisioning server.
        //
        // If successful, the opaque provision request blob is returned to the caller.
        virtual status_t getProvisionRequest(String8 const& cert_type,
                                         String8 const& cert_authority,
                                         Vector<HI_U8>& request,
                                         String8& defaultUrl) = 0;

        // After a provision response is received by the app, it is provided to the
        // Drm plugin using provideProvisionResponse.
        virtual status_t provideProvisionResponse(Vector<HI_U8> const& response,
                Vector<HI_U8>& certificate,
                Vector<HI_U8>& wrapped_key) = 0;

        // Remove device provisioning.
        virtual status_t unprovisionDevice() = 0;

        // A means of enforcing the contractual requirement for a concurrent stream
        // limit per subscriber across devices is provided via SecureStop.  SecureStop
        // is a means of securely monitoring the lifetime of sessions. Since playback
        // on a device can be interrupted due to reboot, power failure, etc. a means
        // of persisting the lifetime information on the device is needed.
        //
        // A signed version of the sessionID is written to persistent storage on the
        // device when each MediaCrypto object is created. The sessionID is signed by
        // the device private key to prevent tampering.
        //
        // In the normal case, playback will be completed, the session destroyed and
        // the Secure Stops will be queried. The App queries secure stops and forwards
        // the secure stop message to the server which verifies the signature and
        // notifies the server side database that the session destruction has been
        // confirmed. The persisted record on the client is only removed after positive
        // confirmation that the server received the message using releaseSecureStops().
        virtual status_t getSecureStops(List<Vector<HI_U8> >& secureStops) = 0;
        virtual status_t getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop) = 0;
        virtual status_t releaseSecureStops(Vector<HI_U8> const& ssRelease) = 0;
        virtual status_t releaseAllSecureStops() = 0;

        // Read a property value given the device property string.  There are a few forms
        // of property access methods, depending on the data type returned.
        // Since DRM plugin properties may vary, additional field names may be defined
        // by each DRM vendor.  Refer to your DRM provider documentation for definitions
        // of its additional field names.
        //
        // Standard values are:
        //   "vendor" [string] identifies the maker of the plugin
        //   "version" [string] identifies the version of the plugin
        //   "description" [string] describes the plugin
        //   'deviceUniqueId' [byte array] The device unique identifier is established
        //   during device provisioning and provides a means of uniquely identifying
        //   each device.
        virtual status_t getPropertyString(String8 const& name, String8& value ) const = 0;
        virtual status_t getPropertyByteArray(String8 const& name,
                                          Vector<HI_U8>& value ) const = 0;

        // Write  a property value given the device property string.  There are a few forms
        // of property setting methods, depending on the data type.
        // Since DRM plugin properties may vary, additional field names may be defined
        // by each DRM vendor.  Refer to your DRM provider documentation for definitions
        // of its field names.
        virtual status_t setPropertyString(String8 const& name,
                                           String8 const& value ) = 0;
        virtual status_t setPropertyByteArray(String8 const& name,
                                          Vector<HI_U8> const& value ) = 0;

        // The following methods implement operations on a CryptoSession to support
        // encrypt, decrypt, sign verify operations on operator-provided
        // session keys.

        //
        // The algorithm string conforms to JCA Standard Names for Cipher
        // Transforms and is case insensitive.  For example "AES/CBC/PKCS5Padding".
        //
        // Return OK if the algorithm is supported, otherwise return BAD_VALUE
        //
        virtual status_t setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                            String8 const& algorithm) = 0;

        //
        // The algorithm string conforms to JCA Standard Names for Mac
        // Algorithms and is case insensitive.  For example "HmacSHA256".
        //
        // Return OK if the algorithm is supported, otherwise return BAD_VALUE
        //
        virtual status_t setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                         String8 const& algorithm) = 0;

        // Encrypt the provided input buffer with the cipher algorithm
        // specified by setCipherAlgorithm and the key selected by keyId,
        // and return the encrypted data.
        virtual status_t encrypt(Vector<HI_U8> const& sessionId,
                                 Vector<HI_U8> const& keyId,
                                 Vector<HI_U8> const& input,
                                 Vector<HI_U8> const& iv,
                                 Vector<HI_U8>& output) = 0;

        // Decrypt the provided input buffer with the cipher algorithm
        // specified by setCipherAlgorithm and the key selected by keyId,
        // and return the decrypted data.
        virtual status_t decrypt(Vector<HI_U8> const& sessionId,
                                 Vector<HI_U8> const& keyId,
                                 Vector<HI_U8> const& input,
                                 Vector<HI_U8> const& iv,
                                 Vector<HI_U8>& output) = 0;

        // Compute a signature on the provided message using the mac algorithm
        // specified by setMacAlgorithm and the key selected by keyId,
        // and return the signature.
        virtual status_t sign(Vector<HI_U8> const& sessionId,
                              Vector<HI_U8> const& keyId,
                              Vector<HI_U8> const& message,
                              Vector<HI_U8>& signature) = 0;

        // Compute a signature on the provided message using the mac algorithm
        // specified by setMacAlgorithm and the key selected by keyId,
        // and compare with the expected result.  Set result to true or
        // false depending on the outcome.
        virtual status_t verify(Vector<HI_U8> const& sessionId,
                                Vector<HI_U8> const& keyId,
                                Vector<HI_U8> const& message,
                                Vector<HI_U8> const& signature,
                                bool& match) = 0;


        // Compute an RSA signature on the provided message using the algorithm
        // specified by algorithm.
        virtual status_t signRSA(Vector<HI_U8> const& sessionId,
                                 String8 const& algorithm,
                                 Vector<HI_U8> const& message,
                                 Vector<HI_U8> const& wrapped_key,
                                 Vector<HI_U8>& signature) = 0;


        status_t setListener(const sp<DrmPluginListener>& listener)
        {
            Mutex::Autolock lock(mEventLock);
            mListener = listener;
            return OK;
        }

    protected:
        // Plugins call these methods to deliver events to the java app
        HI_VOID sendEvent(EventType eventType, int extra,
                          Vector<HI_U8> const* sessionId,
                          Vector<HI_U8> const* data);

        HI_VOID sendExpirationUpdate(Vector<HI_U8> const* sessionId,
                                 HI_S64 expiryTimeInMS);

    HI_VOID sendKeysChange(Vector<HI_U8> const* sessionId,
                               Vector<DrmPlugin::KeyStatus> const* keyStatusList,
                               HI_BOOL hasNewUsableKey);

    private:
        Mutex mEventLock;
        sp<DrmPluginListener> mListener;
    };

    class DrmPluginListener: virtual public RefBase
    {
    public:
        virtual HI_VOID sendEvent(DrmPlugin::EventType eventType, int extra,
                                  Vector<HI_U8> const* sessionId,
                                  Vector<HI_U8> const* data) = 0;

        virtual HI_VOID sendExpirationUpdate(Vector<HI_U8> const* sessionId,
                                             HI_S64 expiryTimeInMS) = 0;

        virtual HI_VOID sendKeysChange(Vector<HI_U8> const* sessionId,
                                       Vector<DrmPlugin::KeyStatus> const* keyStatusList,
                                       HI_BOOL hasNewUsableKey) = 0;
    };

    inline HI_VOID DrmPlugin::sendEvent(EventType eventType, int extra,
                                        Vector<HI_U8> const* sessionId,
                                        Vector<HI_U8> const* data)
    {
        mEventLock.lock();
        sp<DrmPluginListener> listener = mListener;
        mEventLock.unlock();

        if (listener != NULL)
        {
            listener->sendEvent(eventType, extra, sessionId, data);
        }
    }

    inline HI_VOID DrmPlugin::sendExpirationUpdate(Vector<HI_U8> const* sessionId,
            HI_S64 expiryTimeInMS)
    {
        mEventLock.lock();
        sp<DrmPluginListener> listener = mListener;
        mEventLock.unlock();

        if (listener != NULL)
        {
            listener->sendExpirationUpdate(sessionId, expiryTimeInMS);
        }
    }

    inline HI_VOID DrmPlugin::sendKeysChange(Vector<HI_U8> const* sessionId,
            Vector<DrmPlugin::KeyStatus> const* keyStatusList,
            HI_BOOL hasNewUsableKey)
    {
        mEventLock.lock();
        sp<DrmPluginListener> listener = mListener;
        mEventLock.unlock();

        if (listener != NULL)
        {
            listener->sendKeysChange(sessionId, keyStatusList, hasNewUsableKey);
        }
    }

}  // namespace android
#endif // DRM_API_H_
