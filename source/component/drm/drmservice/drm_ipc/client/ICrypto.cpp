#define LOG_TAG "ICrypto"
#include <utils/Logger.h>

#include <binder/Parcel.h>
#include <binder/IMemory.h>
#include "ICrypto.h"
#include "DrmErrors.h"

#define TRANSACT_BOOL_TRUE  (1)
#define TRANSACT_BOOL_FALSE (0)

enum
{
    INIT_CHECK = IBinder::FIRST_CALL_TRANSACTION,
    IS_CRYPTO_SUPPORTED,
    CREATE_PLUGIN,
    DESTROY_PLUGIN,
    REQUIRES_SECURE_COMPONENT,
    DECRYPT,
    NOTIFY_RESOLUTION,
    SET_MEDIADRM_SESSION,
};

class BpCrypto : public BpInterface<ICrypto>
{
public:
    BpCrypto(const sp<IBinder>& impl)
        : BpInterface<ICrypto>(impl)
    {
    }

    virtual HI_BOOL initCheck() const
    {
        Parcel data, reply;
        HI_BOOL ret;

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());

        remote()->transact(INIT_CHECK, data, &reply);

        ret = (reply.readInt32() == TRANSACT_BOOL_TRUE) ? HI_TRUE : HI_FALSE;

        return ret;
    }

    virtual HI_BOOL isCryptoSchemeSupported(const HI_U8 uuid[HI_DRM_UUID_LEN])
    {
        Parcel data, reply;

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.write(uuid, HI_DRM_UUID_LEN);

        remote()->transact(IS_CRYPTO_SUPPORTED, data, &reply);

        return (reply.readInt32() != TRANSACT_BOOL_FALSE) ? HI_TRUE : HI_FALSE;
    }

    virtual HI_S32 createPlugin(const HI_U8 uuid[HI_DRM_UUID_LEN], const HI_VOID* opaqueData, HI_S32 opaqueSize)
    {
        Parcel data, reply;

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.write(uuid, HI_DRM_UUID_LEN);
        data.writeInt32(opaqueSize);

        if (opaqueSize > 0)
        {
            data.write(opaqueData, opaqueSize);
        }

        remote()->transact(CREATE_PLUGIN, data, &reply);

        return reply.readInt32();
    }

    virtual HI_S32 destroyPlugin()
    {
        Parcel data, reply;

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());

        remote()->transact(DESTROY_PLUGIN, data, &reply);

        return reply.readInt32();
    }

    virtual HI_BOOL requiresSecureDecoderComponent(const HI_CHAR* mime)
    {
        Parcel data, reply;

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.writeCString(mime);

        remote()->transact(REQUIRES_SECURE_COMPONENT, data, &reply);

        return (reply.readInt32() != TRANSACT_BOOL_FALSE) ? HI_TRUE : HI_FALSE;
    }

    virtual HI_S32 decrypt(
        HI_BOOL secure,
        const HI_U8 key[HI_DRM_KEY_LEN],
        const HI_U8 iv[HI_DRM_IV_LEN],
        CryptoPlugin::Mode mode,
        const HI_VOID* sharedBuffer, HI_S32 offset,
        const CryptoPlugin::SubSample* subSamples, HI_S32 numSubSamples,
        HI_VOID* dstPtr,
        AString* errorDetailMsg)
    {
        Parcel data, reply;
        HI_S32 totalSize = 0;
        HI_S32 i = 0;
        const HI_U8 kDummy[HI_DRM_KEY_LEN] = { 0 };

        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.writeInt32(secure);
        data.writeInt32(mode);

        if (key == NULL)
        {
            key = kDummy;
        }

        if (iv == NULL)
        {
            iv = kDummy;
        }

        data.write(key, HI_DRM_KEY_LEN);
        data.write(iv, HI_DRM_IV_LEN);

        for (i = 0; i < numSubSamples; ++i)
        {
            totalSize += subSamples[i].mNumBytesOfEncryptedData;
            totalSize += subSamples[i].mNumBytesOfClearData;
        }

        data.writeInt32(totalSize);
        data.write(sharedBuffer, totalSize);
        data.writeInt32(offset);

        data.writeInt32(numSubSamples);
        data.write(subSamples, sizeof(CryptoPlugin::SubSample) * numSubSamples);

        if (secure)
        {
            data.writeInt64(static_cast<HI_U64>(reinterpret_cast<uintptr_t>(dstPtr)));
        }

        remote()->transact(DECRYPT, data, &reply);

        ssize_t result = reply.readInt32();

        /*have error detail msg,refer to drm plugin implement*/
        if (result >= ERROR_DRM_VENDOR_MIN && result <= ERROR_DRM_VENDOR_MAX)
        {
            //add by sunlei 06-13 fix Codecc begin
            //errorDetailMsg->setTo(reply.readCString());
            const HI_U8* cError = (HI_U8*)reply.readCString();
            if (NULL == cError)
            {
                errorDetailMsg->setTo("Return null when readCString from reply!");
            }
            else
            {
                errorDetailMsg->setTo((const char*)cError);
            }
            //add by sunlei 06-13 fix Codecc end
        }

        /*no secure decrypt mode.
          need Optimized:Should use shared memory instead of copy dstPtr here
        */
        if (!secure && result >= 0)
        {
            reply.read(dstPtr, result);
        }

        return result;
    }

    virtual HI_VOID notifyResolution(
        HI_U32 width, HI_U32 height)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());
        data.writeInt32(width);
        data.writeInt32(height);
        remote()->transact(NOTIFY_RESOLUTION, data, &reply);
    }

    virtual HI_S32 setMediaDrmSession(const Vector<HI_U8>& sessionId)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ICrypto::getInterfaceDescriptor());

        writeVector(data, sessionId);
        remote()->transact(SET_MEDIADRM_SESSION, data, &reply);

        return reply.readInt32();
    }

private:
#if 0
    HI_VOID readVector(Parcel& reply, Vector<HI_U8>& vector) const
    {
        HI_U32 size = reply.readInt32();

        if (0 == size) /*if vector size is zero,skip append data*/
        { return; }

        vector.insertAt((size_t)0, size);
        reply.read(vector.editArray(), size);
    }
#endif
    HI_VOID writeVector(Parcel& data, Vector<HI_U8> const& vector) const
    {
        data.writeInt32(vector.size());

        if (0 == vector.size()) /*if vector size is zero,skip append data*/
        { return; }

        data.write(vector.array(), vector.size());
    }

};

IMPLEMENT_META_INTERFACE(Crypto, "hisi.drm.ICrypto");

////////////////////////////////////////////////////////////////////////////////

HI_VOID BnCrypto::readVector(const Parcel& data, Vector<HI_U8>& vector) const
{
    HI_U32 size = data.readInt32();

    if (0 == size) /*if vector size is zero,skip append data*/
    { return; }

    vector.insertAt((size_t)0, size);
    data.read(vector.editArray(), size);
}
#if 0
HI_VOID BnCrypto::writeVector(Parcel* reply, Vector<HI_U8> const& vector) const
{
    reply->writeInt32(vector.size());

    if (0 == vector.size()) /*if vector size is zero,skip append data*/
    { return; }

    reply->write(vector.array(), vector.size());
}
#endif
status_t BnCrypto::onTransact(
    HI_U32 code, const Parcel& data, Parcel* reply, HI_U32 flags)
{
    switch (code)
    {
        case INIT_CHECK:
        {
            HI_S32 ret = TRANSACT_BOOL_FALSE;
            CHECK_INTERFACE(ICrypto, data, reply);

            ret = (HI_TRUE == initCheck()) ? TRANSACT_BOOL_TRUE : TRANSACT_BOOL_FALSE;

            reply->writeInt32(ret);

            return OK;
        }

        case IS_CRYPTO_SUPPORTED:
        {
            HI_S32 ret = TRANSACT_BOOL_FALSE;
            HI_U8 uuid[HI_DRM_UUID_LEN];

            CHECK_INTERFACE(ICrypto, data, reply);

            data.read(uuid, sizeof(uuid));

            ret = (HI_TRUE == isCryptoSchemeSupported(uuid)) ? TRANSACT_BOOL_TRUE : TRANSACT_BOOL_FALSE;

            reply->writeInt32(ret);

            return OK;
        }

        case CREATE_PLUGIN:
        {
            CHECK_INTERFACE(ICrypto, data, reply);

            HI_U8 uuid[HI_DRM_UUID_LEN];
            data.read(uuid, sizeof(uuid));

            size_t opaqueSize = data.readInt32();
            HI_VOID* opaqueData = NULL;

            if (opaqueSize > 0)
            {
                opaqueData = malloc(opaqueSize);
                if (opaqueData)
                    data.read(opaqueData, opaqueSize);
            }

            reply->writeInt32(createPlugin(uuid, opaqueData, opaqueSize));

            if (opaqueData != NULL)
            {
                free(opaqueData);
                opaqueData = NULL;
            }

            return OK;
        }

        case DESTROY_PLUGIN:
        {
            CHECK_INTERFACE(ICrypto, data, reply);

            reply->writeInt32(destroyPlugin());

            return OK;
        }

        case REQUIRES_SECURE_COMPONENT:
        {
            HI_S32 ret = TRANSACT_BOOL_FALSE;
            CHECK_INTERFACE(ICrypto, data, reply);

            const HI_CHAR* mime = data.readCString();
            ret = (HI_TRUE == requiresSecureDecoderComponent(mime)) ? TRANSACT_BOOL_TRUE : TRANSACT_BOOL_FALSE;

            reply->writeInt32(ret);

            return OK;
        }

        case DECRYPT:
        {
            HI_U8 key[HI_DRM_KEY_LEN];
            HI_U8 iv[HI_DRM_IV_LEN];
            HI_VOID* secureBufferId = NULL;
            HI_VOID* dstPtr = NULL;


            CHECK_INTERFACE(ICrypto, data, reply);

            HI_BOOL secure = (HI_BOOL)(data.readInt32());
            CryptoPlugin::Mode mode = (CryptoPlugin::Mode)data.readInt32();

            data.read(key, sizeof(key));
            data.read(iv, sizeof(iv));

            size_t totalSize = data.readInt32();

            /*Need optimized:should use shared memory instead of copy src data*/
            HI_VOID* sharedBuffer = NULL;
            if (totalSize > 0)
            {
                sharedBuffer = malloc(totalSize);
                if (sharedBuffer)
                    data.read(sharedBuffer, totalSize);
            }

            HI_S32 offset = data.readInt32();
            HI_S32 numSubSamples = data.readInt32();

            CryptoPlugin::SubSample* subSamples = NULL;
            if (numSubSamples > 0)
            {
                subSamples = new CryptoPlugin::SubSample[numSubSamples];

                data.read(
                    subSamples,
                    sizeof(CryptoPlugin::SubSample) * numSubSamples);
            }

            if (secure)
            {
                secureBufferId = reinterpret_cast<HI_VOID*>(static_cast<uintptr_t>(data.readInt64()));
            }
            else
            {
                if (totalSize > 0)
                {
                    dstPtr = malloc(totalSize);
                    if (!dstPtr)
                    {
                        if (subSamples)
                        {
                            delete[] subSamples;
                            subSamples = NULL;
                        }

                        if (sharedBuffer)
                        {
                            free(sharedBuffer);
                            sharedBuffer = NULL;
                        }

                        return NO_MEMORY;
                    }
                }
            }

            AString errorDetailMsg;

            ssize_t result;

            result = decrypt(
                         secure,
                         key,
                         iv,
                         mode,
                         sharedBuffer, offset,
                         subSamples, numSubSamples,
                         secure ? secureBufferId : dstPtr,
                         &errorDetailMsg);


            reply->writeInt32(result);

            /*have error detail msg,refer to drm plugin implement*/
            if (result >= ERROR_DRM_VENDOR_MIN && result <= ERROR_DRM_VENDOR_MAX)
            {
                reply->writeCString(errorDetailMsg.c_str());
            }

            /*no secure decrypt mode,write dstPtr buffer
              need Optimized:Should use shared memory instead of copy dstPtr here
            */
            if (!secure)
            {
                if (result >= 0)
                {
                    reply->write(dstPtr, result);
                }

                free(dstPtr);
                dstPtr = NULL;
            }

            delete[] subSamples;
            subSamples = NULL;
            free(sharedBuffer);
            sharedBuffer = NULL;

            return OK;
        }

        case NOTIFY_RESOLUTION:
        {
            CHECK_INTERFACE(ICrypto, data, reply);

            HI_S32 width = data.readInt32();
            HI_S32 height = data.readInt32();
            notifyResolution(width, height);

            return OK;
        }

        case SET_MEDIADRM_SESSION:
        {
            CHECK_INTERFACE(IDrm, data, reply);

            Vector<HI_U8> sessionId;
            readVector(data, sessionId);
            reply->writeInt32(setMediaDrmSession(sessionId));

            return OK;
        }

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
