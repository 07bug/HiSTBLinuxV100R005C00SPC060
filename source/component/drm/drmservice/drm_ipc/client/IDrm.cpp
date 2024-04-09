#define LOG_TAG "IDrm"
#include <utils/Logger.h>

#include <binder/Parcel.h>
#include "IDrm.h"

enum
{
    INIT_CHECK = IBinder::FIRST_CALL_TRANSACTION,
    IS_CRYPTO_SUPPORTED,
    CREATE_PLUGIN,
    DESTROY_PLUGIN,
    OPEN_SESSION,
    CLOSE_SESSION,
    GET_KEY_REQUEST,
    PROVIDE_KEY_RESPONSE,
    REMOVE_KEYS,
    RESTORE_KEYS,
    QUERY_KEY_STATUS,
    GET_PROVISION_REQUEST,
    PROVIDE_PROVISION_RESPONSE,
    GET_SECURE_STOPS,
    RELEASE_SECURE_STOPS,
    GET_PROPERTY_STRING,
    GET_PROPERTY_BYTE_ARRAY,
    SET_PROPERTY_STRING,
    SET_PROPERTY_BYTE_ARRAY,
    SET_CIPHER_ALGORITHM,
    SET_MAC_ALGORITHM,
    ENCRYPT,
    DECRYPT,
    SIGN,
    SIGN_RSA,
    VERIFY,
    SET_LISTENER,
    UNPROVISION_DEVICE,
    GET_SECURE_STOP,
    RELEASE_ALL_SECURE_STOPS
};

class BpDrm : public BpInterface<IDrm>
{
public:
    BpDrm(const sp<IBinder>& impl): BpInterface<IDrm>(impl)
    {
    }

    virtual HI_BOOL initCheck()
    {
        Parcel data, reply;
        HI_BOOL ret = HI_FALSE;

        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        remote()->transact(INIT_CHECK, data, &reply);

        ret = (HI_BOOL)(reply.readInt32());

        return ret;
    }

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[16], const String8& mimeType)
    {
        Parcel data, reply;

        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());
        data.write(uuid, 16);
        data.writeString8(mimeType);

        status_t status = remote()->transact(IS_CRYPTO_SUPPORTED, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FALSE;
        }

        return (HI_BOOL)(reply.readInt32());
    }

    virtual HI_S32 createPlugin(const HI_U8 uuid[16])
    {
        Parcel data, reply;

        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());
        data.write(uuid, 16);

        status_t status = remote()->transact(CREATE_PLUGIN, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 destroyPlugin()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());
        status_t status = remote()->transact(DESTROY_PLUGIN, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 openSession(Vector<HI_U8>& sessionId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        status_t status = remote()->transact(OPEN_SESSION, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, sessionId);

        return reply.readInt32();
    }

    virtual HI_S32 closeSession(Vector<HI_U8> const& sessionId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        status_t status = remote()->transact(CLOSE_SESSION, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 getKeyRequest(Vector<HI_U8> const& sessionId,
                                 Vector<HI_U8> const& initData,
                                 String8 const& mimeType, DrmPlugin::KeyType keyType,
                                 KeyedVector<String8, String8> const& optionalParameters,
                                 Vector<HI_U8>& request, String8& defaultUrl,
                                 DrmPlugin::KeyRequestType* keyRequestType)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, initData);
        data.writeString8(mimeType);
        data.writeInt32((HI_U32)keyType);

        data.writeInt32(optionalParameters.size());

        for (size_t i = 0; i < optionalParameters.size(); ++i)
        {
            data.writeString8(optionalParameters.keyAt(i));
            data.writeString8(optionalParameters.valueAt(i));
        }

        status_t status = remote()->transact(GET_KEY_REQUEST, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, request);

        defaultUrl = reply.readString8();
        // When defaultUrl.size is 0, in the replay to write will be written 2 times,
        // but readString8 read only read once.In order to ensure the data read and write
        //symmetry so need to add a read when the defaultUrl.size for 0 time
        //if (0 == defaultUrl.size())
        //{
        //    HI_S32 tmpMissValue = reply.readInt32();
        //    HI_LOGD("Miss Read Value:%d", tmpMissValue);
        //}
        *keyRequestType = static_cast<DrmPlugin::KeyRequestType>(reply.readInt32());

        return reply.readInt32();
    }

    virtual HI_S32 provideKeyResponse(Vector<HI_U8> const& sessionId,
                                      Vector<HI_U8> const& response,
                                      Vector<HI_U8>& keySetId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());
        writeVector(data, sessionId);
        writeVector(data, response);

        status_t status = remote()->transact(PROVIDE_KEY_RESPONSE, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, keySetId);

        return reply.readInt32();
    }

    virtual HI_S32 removeKeys(Vector<HI_U8> const& keySetId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, keySetId);
        status_t status = remote()->transact(REMOVE_KEYS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 restoreKeys(Vector<HI_U8> const& sessionId,
                               Vector<HI_U8> const& keySetId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, keySetId);
        status_t status = remote()->transact(RESTORE_KEYS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 queryKeyStatus(Vector<HI_U8> const& sessionId,
                                  KeyedVector<String8, String8>& infoMap)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        status_t status = remote()->transact(QUERY_KEY_STATUS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        infoMap.clear();
        size_t count = reply.readInt32();

        for (size_t i = 0; i < count; i++)
        {
            String8 key = reply.readString8();
            String8 value = reply.readString8();
            infoMap.add(key, value);
        }

        return reply.readInt32();
    }

    virtual HI_S32 getProvisionRequest(String8 const& certType,
                                       String8 const& certAuthority,
                                       Vector<HI_U8>& request,
                                       String8& defaultUrl)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeString8(certType);
        data.writeString8(certAuthority);
        status_t status = remote()->transact(GET_PROVISION_REQUEST, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, request);
        defaultUrl = reply.readString8();

        return reply.readInt32();
    }

    virtual HI_S32 provideProvisionResponse(Vector<HI_U8> const& response,
                                            Vector<HI_U8>& certificate,
                                            Vector<HI_U8>& wrappedKey)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, response);
        status_t status = remote()->transact(PROVIDE_PROVISION_RESPONSE, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, certificate);
        readVector(reply, wrappedKey);

        return reply.readInt32();
    }

    virtual HI_S32 unprovisionDevice()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        status_t status = remote()->transact(UNPROVISION_DEVICE, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 getSecureStops(List<Vector<HI_U8> >& secureStops)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        status_t status = remote()->transact(GET_SECURE_STOPS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        secureStops.clear();
        HI_U32 count = reply.readInt32();

        for (size_t i = 0; i < count; i++)
        {
            Vector<HI_U8> secureStop;
            readVector(reply, secureStop);
            secureStops.push_back(secureStop);
        }

        return reply.readInt32();
    }

    virtual HI_S32 getSecureStop(Vector<HI_U8> const& ssid, Vector<HI_U8>& secureStop)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, ssid);
        status_t status = remote()->transact(GET_SECURE_STOP, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, secureStop);
        return reply.readInt32();
    }

    virtual HI_S32 releaseSecureStops(Vector<HI_U8> const& ssRelease)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, ssRelease);
        status_t status = remote()->transact(RELEASE_SECURE_STOPS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 releaseAllSecureStops()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        status_t status = remote()->transact(RELEASE_ALL_SECURE_STOPS, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 getPropertyString(String8 const& name, String8& value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeString8(name);
        status_t status = remote()->transact(GET_PROPERTY_STRING, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        value = reply.readString8();
        return reply.readInt32();
    }

    virtual HI_S32 getPropertyByteArray(String8 const& name, Vector<HI_U8>& value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeString8(name);
        status_t status = remote()->transact(GET_PROPERTY_BYTE_ARRAY, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, value);
        return reply.readInt32();
    }

    virtual HI_S32 setPropertyString(String8 const& name, String8 const& value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeString8(name);
        data.writeString8(value);
        status_t status = remote()->transact(SET_PROPERTY_STRING, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 setPropertyByteArray(String8 const& name,
                                        Vector<HI_U8> const& value)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeString8(name);
        writeVector(data, value);
        status_t status = remote()->transact(SET_PROPERTY_BYTE_ARRAY, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 setCipherAlgorithm(Vector<HI_U8> const& sessionId,
                                      String8 const& algorithm)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        data.writeString8(algorithm);
        status_t status = remote()->transact(SET_CIPHER_ALGORITHM, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 setMacAlgorithm(Vector<HI_U8> const& sessionId,
                                   String8 const& algorithm)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        data.writeString8(algorithm);
        status_t status = remote()->transact(SET_MAC_ALGORITHM, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

    virtual HI_S32 encrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, keyId);
        writeVector(data, input);
        writeVector(data, iv);

        status_t status = remote()->transact(ENCRYPT, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, output);

        return reply.readInt32();
    }

    virtual HI_S32 decrypt(Vector<HI_U8> const& sessionId,
                           Vector<HI_U8> const& keyId,
                           Vector<HI_U8> const& input,
                           Vector<HI_U8> const& iv,
                           Vector<HI_U8>& output)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, keyId);
        writeVector(data, input);
        writeVector(data, iv);

        status_t status = remote()->transact(DECRYPT, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, output);

        return reply.readInt32();
    }

    virtual HI_S32 sign(Vector<HI_U8> const& sessionId,
                        Vector<HI_U8> const& keyId,
                        Vector<HI_U8> const& message,
                        Vector<HI_U8>& signature)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, keyId);
        writeVector(data, message);

        status_t status = remote()->transact(SIGN, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, signature);

        return reply.readInt32();
    }

    virtual HI_S32 verify(Vector<HI_U8> const& sessionId,
                          Vector<HI_U8> const& keyId,
                          Vector<HI_U8> const& message,
                          Vector<HI_U8> const& signature,
                          HI_BOOL& match)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        writeVector(data, keyId);
        writeVector(data, message);
        writeVector(data, signature);

        status_t status = remote()->transact(VERIFY, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        match = (HI_BOOL)reply.readInt32();
        return reply.readInt32();
    }

    virtual HI_S32 signRSA(Vector<HI_U8> const& sessionId,
                           String8 const& algorithm,
                           Vector<HI_U8> const& message,
                           Vector<HI_U8> const& wrappedKey,
                           Vector<HI_U8>& signature)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        writeVector(data, sessionId);
        data.writeString8(algorithm);
        writeVector(data, message);
        writeVector(data, wrappedKey);

        status_t status = remote()->transact(SIGN_RSA, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d", __FUNCTION__, status);
            return HI_FAILURE;
        }

        readVector(reply, signature);

        return reply.readInt32();
    }

    virtual HI_S32 setListener(const sp<IDrmClient>& listener)
    {
        Parcel data, reply;

        data.writeInterfaceToken(IDrm::getInterfaceDescriptor());

        data.writeStrongBinder(listener->asBinder());
        status_t status = remote()->transact(SET_LISTENER, data, &reply);

        if (status != OK)
        {
            HI_LOGE("%s: binder call failed: %d",__FUNCTION__,status);
            return HI_FAILURE;
        }

        return reply.readInt32();
    }

private:
    HI_VOID readVector(Parcel& reply, Vector<HI_U8>& vector)
    {
        HI_U32 size = reply.readInt32();

        if (0 == size) /*if vector size is zero,skip append data*/
        { return; }

        vector.insertAt((size_t)0, size);
        reply.read(vector.editArray(), size);
        vector.editArray()[size] = '\0';
    }

    HI_VOID writeVector(Parcel& data, Vector<HI_U8> const& vector)
    {
        data.writeInt32(vector.size());

        if (0 == vector.size()) /*if vector size is zero,skip append data*/
        { return; }

        data.write(vector.array(), vector.size());
    }

};

IMPLEMENT_META_INTERFACE(Drm, "hisi.drm.IDrm");

////////////////////////////////////////////////////////////////////////////////

void BnDrm::readVector(const Parcel& data, Vector<HI_U8>& vector)
{
    HI_U32 size = data.readInt32();

    if (0 == size) /*if vector size is zero,skip append data*/
    { return; }

    vector.insertAt((size_t)0, size);
    data.read(vector.editArray(), size);
}

void BnDrm::writeVector(Parcel* reply, Vector<HI_U8> const& vector)
{
    reply->writeInt32(vector.size());

    if (0 == vector.size()) /*if vector size is zero,skip append data*/
    { return; }

    reply->write(vector.array(), vector.size());
}

status_t BnDrm::onTransact( HI_U32 code, const Parcel& data, Parcel* reply, HI_U32 flags)
{
    switch (code)
    {
        case INIT_CHECK:
        {
            CHECK_INTERFACE(IDrm, data, reply);
            reply->writeInt32((HI_S32)initCheck());

            return OK;
        }

        case IS_CRYPTO_SUPPORTED:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            HI_U8 uuid[16];
            data.read(uuid, sizeof(uuid));
            String8 mimeType = data.readString8();
            reply->writeInt32(isCryptoSchemeSupported(uuid, mimeType));

            return OK;
        }

        case CREATE_PLUGIN:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            HI_U8 uuid[16];
            data.read(uuid, sizeof(uuid));
            reply->writeInt32(createPlugin(uuid));

            return OK;
        }

        case DESTROY_PLUGIN:
        {
            CHECK_INTERFACE(IDrm, data, reply);
            reply->writeInt32(destroyPlugin());

            return OK;
        }

        case OPEN_SESSION:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId;
            status_t result = openSession(sessionId);
            writeVector(reply, sessionId);
            reply->writeInt32(result);

            return OK;
        }

        case CLOSE_SESSION:
        {
            CHECK_INTERFACE(IDrm, data, reply);
            Vector<HI_U8> sessionId;
            readVector(data, sessionId);
            reply->writeInt32(closeSession(sessionId));
            return OK;
        }

        case GET_KEY_REQUEST:
        {
            CHECK_INTERFACE(IDrm, data, reply);
            Vector<HI_U8> sessionId, initData;

            readVector(data, sessionId);
            readVector(data, initData);
            String8 mimeType = data.readString8();
            DrmPlugin::KeyType keyType = (DrmPlugin::KeyType)data.readInt32();

            KeyedVector<String8, String8> optionalParameters;
            HI_U32 count = data.readInt32();

            for (size_t i = 0; i < count; ++i)
            {
                String8 key, value;
                key = data.readString8();
                value = data.readString8();
                optionalParameters.add(key, value);
            }

            Vector<HI_U8> request;
            String8 defaultUrl;
            DrmPlugin::KeyRequestType keyRequestType;

            status_t result = getKeyRequest(sessionId, initData, mimeType,
                                            keyType, optionalParameters, request, defaultUrl,
                                            &keyRequestType);

            writeVector(reply, request);

            reply->writeString8(defaultUrl);
            reply->writeInt32(static_cast<HI_S32>(keyRequestType));

            reply->writeInt32(result);

            return OK;
        }

        case PROVIDE_KEY_RESPONSE:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, response, keySetId;
            readVector(data, sessionId);
            readVector(data, response);

            HI_U32 result = provideKeyResponse(sessionId, response, keySetId);

            writeVector(reply, keySetId);
            reply->writeInt32(result);

            return OK;
        }

        case REMOVE_KEYS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> keySetId;
            readVector(data, keySetId);

            reply->writeInt32(removeKeys(keySetId));

            return OK;
        }

        case RESTORE_KEYS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, keySetId;
            readVector(data, sessionId);
            readVector(data, keySetId);

            reply->writeInt32(restoreKeys(sessionId, keySetId));

            return OK;
        }

        case QUERY_KEY_STATUS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId;
            readVector(data, sessionId);
            KeyedVector<String8, String8> infoMap;


            status_t result = queryKeyStatus(sessionId, infoMap);
            size_t count = infoMap.size();
            reply->writeInt32(count);

            for (size_t i = 0; i < count; ++i)
            {
                reply->writeString8(infoMap.keyAt(i));
                reply->writeString8(infoMap.valueAt(i));
            }

            reply->writeInt32(result);

            return OK;
        }

        case GET_PROVISION_REQUEST:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            String8 certType = data.readString8();
            String8 certAuthority = data.readString8();

            Vector<HI_U8> request;
            String8 defaultUrl;
            status_t result = getProvisionRequest(certType, certAuthority,
                                                  request, defaultUrl);
            writeVector(reply, request);
            reply->writeString8(defaultUrl);
            reply->writeInt32(result);

            return OK;
        }

        case PROVIDE_PROVISION_RESPONSE:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> response;
            Vector<HI_U8> certificate;
            Vector<HI_U8> wrappedKey;
            readVector(data, response);

            status_t result = provideProvisionResponse(response, certificate, wrappedKey);

            writeVector(reply, certificate);
            writeVector(reply, wrappedKey);
            reply->writeInt32(result);
            return OK;
        }

        case UNPROVISION_DEVICE:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            status_t result = unprovisionDevice();
            reply->writeInt32(result);

            return OK;
        }

        case GET_SECURE_STOPS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            List<Vector<HI_U8> > secureStops;

            status_t result = getSecureStops(secureStops);

            size_t count = secureStops.size();
            reply->writeInt32(count);
            List<Vector<HI_U8> >::iterator iter = secureStops.begin();

            while (iter != secureStops.end())
            {
                size_t size = iter->size();
                reply->writeInt32(size);
                reply->write(iter->array(), iter->size());
                iter++;
            }

            reply->writeInt32(result);

            return OK;
        }

        case GET_SECURE_STOP:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> ssid, secureStop;
            readVector(data, ssid);

            status_t result = getSecureStop(ssid, secureStop);

            writeVector(reply, secureStop);
            reply->writeInt32(result);

            return OK;
        }

        case RELEASE_SECURE_STOPS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> ssRelease;
            readVector(data, ssRelease);

            reply->writeInt32(releaseSecureStops(ssRelease));

            return OK;
        }

        case RELEASE_ALL_SECURE_STOPS:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            reply->writeInt32(releaseAllSecureStops());

            return OK;
        }

        case GET_PROPERTY_STRING:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            String8 name = data.readString8();
            String8 value;

            status_t result = getPropertyString(name, value);

            reply->writeString8(value);
            reply->writeInt32(result);

            return OK;
        }

        case GET_PROPERTY_BYTE_ARRAY:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            String8 name = data.readString8();
            Vector<HI_U8> value;

            status_t result = getPropertyByteArray(name, value);

            writeVector(reply, value);
            reply->writeInt32(result);

            return OK;
        }

        case SET_PROPERTY_STRING:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            String8 name = data.readString8();
            String8 value = data.readString8();

            reply->writeInt32(setPropertyString(name, value));

            return OK;
        }

        case SET_PROPERTY_BYTE_ARRAY:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            String8 name = data.readString8();
            Vector<HI_U8> value;
            readVector(data, value);

            reply->writeInt32(setPropertyByteArray(name, value));

            return OK;
        }

        case SET_CIPHER_ALGORITHM:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId;
            readVector(data, sessionId);
            String8 algorithm = data.readString8();

            reply->writeInt32(setCipherAlgorithm(sessionId, algorithm));

            return OK;
        }

        case SET_MAC_ALGORITHM:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId;
            readVector(data, sessionId);
            String8 algorithm = data.readString8();

            reply->writeInt32(setMacAlgorithm(sessionId, algorithm));

            return OK;
        }

        case ENCRYPT:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, keyId, input, iv, output;
            readVector(data, sessionId);
            readVector(data, keyId);
            readVector(data, input);
            readVector(data, iv);

            HI_U32 result = encrypt(sessionId, keyId, input, iv, output);

            writeVector(reply, output);
            reply->writeInt32(result);

            return OK;
        }

        case DECRYPT:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, keyId, input, iv, output;
            readVector(data, sessionId);
            readVector(data, keyId);
            readVector(data, input);
            readVector(data, iv);

            HI_U32 result = decrypt(sessionId, keyId, input, iv, output);

            writeVector(reply, output);
            reply->writeInt32(result);

            return OK;
        }

        case SIGN:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, keyId, message, signature;
            readVector(data, sessionId);
            readVector(data, keyId);
            readVector(data, message);

            HI_U32 result = sign(sessionId, keyId, message, signature);

            writeVector(reply, signature);
            reply->writeInt32(result);

            return OK;
        }

        case VERIFY:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, keyId, message, signature;
            readVector(data, sessionId);
            readVector(data, keyId);
            readVector(data, message);
            readVector(data, signature);
            HI_BOOL match;

            HI_U32 result = verify(sessionId, keyId, message, signature, match);
            reply->writeInt32(match);
            reply->writeInt32(result);

            return OK;
        }

        case SIGN_RSA:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId, message, wrappedKey, signature;
            readVector(data, sessionId);
            String8 algorithm = data.readString8();
            readVector(data, message);
            readVector(data, wrappedKey);

            HI_U32 result = signRSA(sessionId, algorithm, message, wrappedKey, signature);
            writeVector(reply, signature);
            reply->writeInt32(result);

            return OK;
        }

        case SET_LISTENER:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            sp<IDrmClient> listener =
                interface_cast<IDrmClient>(data.readStrongBinder());

            reply->writeInt32(setListener(listener));

            return OK;
        }
        break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
