/******************************************************************************
 Copyright (C), 2015-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name    : ModularDrmInterface.h
Version        : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2016/02
Last Modified :
Description   : modular drm interface api definition.
                CNcomment: Modular Drm接口头文件定义CNend
Function List :
History       :
******************************************************************************/

#ifndef MODULAR_DRM_INTERFACE_H__
#define MODULAR_DRM_INTERFACE_H__

#include <utils/KeyedVector.h>
#include <utils/List.h>
#include "DrmDefines.h"

/******************************* API Declaration *****************************/
/** \addtogroup      DrmService_API */
/** @{ */


/** Modular Drm interface api */
class ModularDrmInterface
{
public:
    virtual ~ModularDrmInterface() {};

    /**
    \brief create and instance the drm access object.
    \attention \n
    if want to access the drm function, this must be call first.

    param [in] uuid The UUID of the crypto scheme

    \retval ::ModularDrmInterface*  drm object access handle.
    \retval ::NULL  create drm handle fail.
    \see \n
    None
    */
    static ModularDrmInterface* Create(const HI_U8 uuid[HI_DRM_UUID_LEN]);

    /**
    \brief Destroy drm instance.
    \attention \n
    if exit to access the drm feature,should call destroy.

    \param [in] object the drm instance handle that will be destroy.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    static HI_S32 Destroy(ModularDrmInterface* &object);

    /**
    \brief Query if the given scheme identified by its UUID is supported on \n
           this device, and whether the drm plugin is able to handle the \n
           media container format specified by mimeType.
    \attention \n
    None

    \param [in] uuid The UUID of the crypto scheme.
    \param [in] mimeType mimeType The MIME type of the media container, e.g. "video/mp4" .

    \retval ::HI_TRUE scheme is supported.
    \retval ::HI_FALSE scheme is not supported.

    \see \n
    None
    */
    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_KEY_LEN], const HI_CHAR* mimeType) = 0;

    /**
    \brief Open a new session with the object.

    \attention \n
    None.

    \param [out] sessionId session id.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 openSession(Vector<HI_U8>& sessionId) = 0;

    /**
    \brief close a session which opened by ::openSession .

    \attention \n
    None.

    \param [in] sessionId session id.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 closeSession(Vector<HI_U8> const& sessionId) = 0;

    /**
    \brief obtain an opaque key request blob that is delivered to the license server

    \attention \n
     A key request/response exchange occurs between the app and a License
     Server to obtain the keys required to decrypt the content.
     The opaque key request byte array is returned in pKeyRequest->pData .
     The recommended URL to deliver the key request to is returned in pKeyRequest->pDefaultUrl.
     After the app has received the key request response from the server,
     it should deliver to the response to the DRM engine plugin using the method
     ::provideKeyResponse .

     This a synchronous interface,may consume some time within different drm plugin.

    \param [in] scope scope may be a sessionId or a keySetId, depending on the specified keyType.
                When the keyType is ::HI_DRM_KEY_TYPE_OFFLINE or ::HI_DRM_KEY_TYPE_STREAMING,
                scope should be set to the sessionId the keys will be provided to.  When the keyType
                is ::HI_DRM_KEY_TYPE_RELEASE, scope should be set to the keySetId of the keys
                being released. Releasing keys from a device invalidates them for all sessions.

    \param [in] initData container-specific data, its meaning is interpreted based on the
                mime type provided in the mimeType parameter.  It could contain, for example,
                the content ID, key ID or other data obtained from the content metadata that is
                required in generating the key request. init may be null when keyType is
                ::HI_DRM_KEY_TYPE_RELEASE.

    \param [in] mimeType identifies the mime type of the content

    \param [in] keyType specifes the type of the request. The request may be to acquire
                keys for streaming or offline content, or to release previously acquired
                keys, which are identified by a keySetId

    \param [in] optionalParameters are included in the key request message to allow a
                client application to provide additional message parameters to the server.
                this may be null if no additional param data.

    \param [out] pKeyRequest request data delivered to the license server.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 getKeyRequest(Vector<HI_U8> const& scope,
                                 Vector<HI_U8> const& initData,
                                 HI_CHAR const* mimeType, HI_DRM_KEY_TYPE keyType,
                                 KeyedVector<String8, String8> const& optionalParameters,
                                 HI_DRM_KEY_REQUEST* pKeyRequest) = 0;

    /**
    \brief key response to drm engine.

    \attention \n
     After a key response is received by the app, it is provided to the
     Drm engine using provideKeyResponse.

    This a synchronous interface,may consume some time within different drm plugin.

    \param [in] scope may be a sessionId or keySetId depending on the type of the
                response.scope should be set to the sessionId when the response is for either
                streaming or offline key requests.  Scope should be set to the keySetId when
                the response is for a release request.

    \param [in] response the response data from the server

    \param [out] keySetId When the response is for key request, a keySetId is returned.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 provideKeyResponse(Vector<HI_U8> const& scope,
                                      Vector<HI_U8> const& response,
                                      Vector<HI_U8>& keySetId) = 0;

    /**
    \brief Remove the current keys from a session.

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

    \param [in] sessionId the session ID for the DRM session.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 removeKeys(Vector<HI_U8> const& sessionId) = 0;

    /**
    \brief Restore persisted offline keys into a new session.

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     keySetId identifies the keys to load,
     obtained from a prior call to ::provideKeyResponse.

     This a synchronous interface.

    \param [in] sessionId the session ID for the DRM session.
    \param [in] keySetId identifies the saved key set to restore.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 restoreKeys(Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& keySetId) = 0;

    /**
    \brief Request an informative description of the key status for the session.

    \attention \n
     Not support now in drm plugin.(either playready or widevine).

     The status is in the form of {name, value} pairs.Since DRM license policies vary by
     vendor, the specific status field names are determined by each DRM vendor.
     Refer to your DRM provider documentation for definitions of the field names
     for a particular DrmEngine.

    \param [in] sessionId the session ID for the DRM session.
    \param [out] infoMap  the status in the form of {name, value} pairs.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 queryKeyStatus(Vector<HI_U8> const& sessionId,
                                  KeyedVector<String8, String8>& infoMap) = 0;

    /**
    \brief Obtain the opaque provision request byte array that
           should be delivered to the provisioning server.

    \attention \n
     A provision request/response exchange occurs between the app and a provisioning
     server to retrieve a device certificate.  If provisionining is required, the
     ::HI_DRM_EVENT_PROVISION_REQUIRED event will be sent.

    \param [in] certType.
    \param [in] certAuthority.
    \param [out] request request data returned from drm engine.refer to ::HI_DRM_PROVITION_REQUEST

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 getProvisionRequest(String8 const& certType,
                                       String8 const& certAuthority,
                                       HI_DRM_PROVITION_REQUEST* request) = 0;

    /**
    \brief provision response to drm engine.

    \attention \n
     After a provision response is received by the app, it is provided to the
     Drm engine using this function.

    \param [in] response reponse data received from provision server
    \param [out] certificate identifies the saved key set to restore.
    \param [out] wrappedKey

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 provideProvisionResponse(Vector<HI_U8> const& response,
                                            Vector<HI_U8>& certificate,
                                            Vector<HI_U8>& wrappedKey) = 0;
    /**
    \brief Remove device provisioning.

    \attention \n
     Only system apps may unprovision a device.
     Note that removing provisioning will invalidate any keys saved
     for offline use ::HI_DRM_KEY_TYPE_OFFLINE, which may render downloaded content
     unplayable until new licenses are acquired.  Since provisioning is global
     to the device, license invalidation will apply to all content downloaded
     by any app, so appropriate warnings should be given to the user.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 unprovisionDevice() = 0;

    /**
    \brief get Secure stops

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     A means of enforcing limits on the number of concurrent streams per subscriber
     across devices is provided via SecureStop. This is achieved by securely
     monitoring the lifetime of sessions.
     Information from the server related to the current playback session is written
     to persistent storage on the device when each MediaCrypto object is created.
     In the normal case, playback will be completed, the session destroyed and the
     Secure Stops will be queried. The app queries secure stops and forwards the
     secure stop message to the server which verifies the signature and notifies the
     server side database that the session destruction has been confirmed. The persisted
     record on the client is only removed after positive confirmation that the server
     received the message using releaseSecureStops().

    \param [out] secureStops

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 getSecureStops(List<Vector<HI_U8> >& secureStops) = 0;

    /**
    \brief Access secure stop by secure stop ID.

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

    \param [in] ssid The secure stop ID provided by the license server
    \param [out] secureStop

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop) = 0;

    /**
    \brief release the secure stops

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     Process the SecureStop server response message ssRelease.  After authenticating
     the message, remove the SecureStops identified in the response.

    \param [in] ssRelease the server response indicating which secure stops to release

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 releaseSecureStops(Vector<HI_U8> const& ssRelease) = 0;

    /**
    \brief release all secure stops

    \attention \n
     Not support now in drm plugin.(either playready or widevine).

     Remove all secure stops without requiring interaction with the server.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 releaseAllSecureStops() = 0;

    /**
    \brief Read a DRM engine plugin String property value, given the property name string

    \attention \n
     Not support now in drm plugin.(either playready or widevine).

     Since DRM plugin properties may vary, additional field names may be defined
     by each DRM vendor.  Refer to your DRM provider documentation for definitions
     of its additional field names.
     Standard fields names are:
     vendor:  identifies the maker of the engine
     version:  identifies the version of the engine
     description:  describes the drm engine

    \param [in] name field names.
    \param [out] value field values

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 getPropertyString(String8 const& name, String8& value) = 0;
    virtual HI_S32 getPropertyByteArray(String8 const& name,
                                        Vector<HI_U8>& value) = 0;

    /**
    \brief Set a DRM engine plugin String property value

    \attention \n
     Not support now in drm plugin.(either playready or widevine)

     Since DRM plugin properties may vary, additional field names may be defined
     by each DRM vendor.  Refer to your DRM provider documentation for definitions
     of its additional field names.

    \param [in] name field names.
    \param [in] value field values

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 setPropertyString(String8 const& name,
                                     String8 const& value ) = 0;
    virtual HI_S32 setPropertyByteArray(String8 const& name,
                                        Vector<HI_U8> const& value) = 0;


    /**
    \brief Set Cipher algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     This methods implement operations on a CryptoSession to support
     encrypt, decrypt, operations on operator-provided session keys.
     Algorithm string conforms to JCA Standard Names for Cipher Transforms and is case insensitive.
     For example "AES/CBC/PKCS5Padding"
     Return HI_SUCCESS if the algorithm is supported, otherwise return HI_FAILURE.

    \param [in] sessionId the session ID for the DRM session.
    \param [in] algorithm algorithm strings

    \retval ::HI_SUCCESS the algorithm is supported.
    \retval ::HI_FAILURE the algorithm is not supported.

    \see \n
    None
    */
    virtual HI_S32 setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                      String8 const& algorithm) = 0;

    /**
    \brief Set Cipher algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     This methods implement operations on a CryptoSession to support
     sign /verify operations on operator-provided session keys.
     Algorithm string conforms to JCA Standard Names for Mac algorithms and is case insensitive.
     For example "HmacSHA256".
     Return HI_SUCCESS if the algorithm is supported, otherwise return HI_FAILURE.

    \param [in] sessionId the session ID for the DRM session
    \param [in] algorithm algorithm strings

    \retval ::HI_SUCCESS the algorithm is supported.
    \retval ::HI_FAILURE the algorithm is not supported.

    \see \n
    None
    */
    virtual HI_S32 setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                   String8 const& algorithm) = 0;

    /**
    \brief Encrypt the provided input buffer with the cipher algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     Encrypt the provided input buffer with the cipher algorithm specified by setCipherAlgorithm
     and the key selected by keyId.and return the encrypted data.

    \param [in] sessionId the session ID for the DRM session
    \param [in] keyId specifies which key to use
    \param [in] input the data to encrypt
    \param [in] iv the initialization vector to use for the cipher
    \param [out] output encrypt data.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 encrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output) = 0;

    /**
    \brief Decrypt the provided input buffer with the cipher algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     Decrypt the provided input buffer with the cipher algorithm specified by setCipherAlgorithm
     and the key selected by keyId.and return the decrypted data.

    \param [in] sessionId the session ID for the DRM session
    \param [in] keyId specifies which key to use
    \param [in] input the data to decrypt
    \param [in] iv the initialization vector to use for the cipher
    \param [out] output encrypt data.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 decrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output) = 0;

    /**
    \brief Sign message data using the mac algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     Compute a signature on the provided message using the mac algorithm
     specified by setMacAlgorithm and the key selected by keyId,
     and return the signature.

    \param [in] sessionId the session ID for the DRM session
    \param [in] keyId specifies which key to use
    \param [in] message the data for which a signature is to be computeds.
    \param [out] signature out signature data.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 sign(Vector<HI_U8> const& sessionId,
                        Vector<HI_U8> const& keyId,
                        Vector<HI_U8> const& message,
                        Vector<HI_U8>& signature) = 0;

    /**
    \brief Verify message data using the mac algorithm

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

     Compute a signature on the provided message using the mac algorithm
     specified by setMacAlgorithm and the key selected by keyId,
     and compare with the expected result.  Set result to true or
     false depending on the outcome.

    \param [in] sessionId the session ID for the DRM session
    \param [in] keyId specifies which key to use
    \param [in] message the data to verify.
    \param [in] signaturethe reference signature which will be compared with the
                 computed signature
    \param [out] match  true if the signatures match, false if no match.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 verify(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& message,
                          Vector<HI_U8>const& signature,
                          HI_BOOL& match) = 0;

    /**
    \brief Sign data using an RSA key

    \attention \n
     Not ready now in drm plugin.(either playready or widevine)

    \param [in] sessionId the session ID for the DRM session
    \param [in] algorithm the signing algorithm to use, e.g. "PKCS1-BlockType1"
    \param [in] message the data for which a signature is to be computed.
    \param [in] wrappedKey the wrapped (encrypted) RSA private keys.
    \param [out] signature out signature data.

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature) = 0;

    /**
    \brief Set event listener.

    \attention \n
     None.

    \param [in] listener listener implement by user.refer to ::DrmListener

    \retval ::HI_SUCCESS operation success.
    \retval ::HI_FAILURE operation fail.

    \see \n
    None
    */
    virtual HI_S32 setListener(DrmListener* listener) = 0;
};

/** @}*/  /** <!-- ==== API Declaration End ====*/

#endif //MODULAR_DRM_INTERFACE_H__
