#include <utils/Errors.h>  // for status_t
#include <utils/String8.h>

#include <binder/Parcel.h>
#include "ICrypto.h"
#include "IDrm.h"
#include "IDrmService.h"

enum
{
    MAKE_CRYPTO = IBinder::FIRST_CALL_TRANSACTION,
    MAKE_DRM,
};

class BpDrmService: public BpInterface<IDrmService>
{
public:
    BpDrmService(const sp<IBinder>& impl)
        : BpInterface<IDrmService>(impl)
    {
    }

    virtual sp<ICrypto> makeCrypto()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrmService::getInterfaceDescriptor());

        remote()->transact(MAKE_CRYPTO, data, &reply);

        return interface_cast<ICrypto>(reply.readStrongBinder());
    }

    virtual sp<IDrm> makeDrm()
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrmService::getInterfaceDescriptor());

        remote()->transact(MAKE_DRM, data, &reply);

        return interface_cast<IDrm>(reply.readStrongBinder());
    }
};

IMPLEMENT_META_INTERFACE(DrmService, "hisi.drm.IDrmService");

status_t BnDrmService::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch (code)
    {

        case MAKE_CRYPTO:
        {
            CHECK_INTERFACE(IDrmService, data, reply);
            sp<ICrypto> crypto = makeCrypto();
            reply->writeStrongBinder(crypto->asBinder());
            return NO_ERROR;
        }

        case MAKE_DRM:
        {
            CHECK_INTERFACE(IDrmService, data, reply);
            sp<IDrm> drm = makeDrm();
            reply->writeStrongBinder(drm->asBinder());
            return NO_ERROR;
        }

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
