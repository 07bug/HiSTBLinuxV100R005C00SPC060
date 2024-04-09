#define LOG_TAG "IDrmClient"
#include <utils/Logger.h>

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "IDrmClient.h"

enum
{
    NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
};

class BpDrmClient: public BpInterface<IDrmClient>
{
public:
    BpDrmClient(const sp<IBinder>& impl)
        : BpInterface<IDrmClient>(impl)
    {
    }

    virtual HI_VOID notify(DrmPlugin::EventType eventType, HI_S32 extra, const Parcel* obj)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDrmClient::getInterfaceDescriptor());
        data.writeInt32((int)eventType);
        data.writeInt32(extra);

        if (obj && obj->dataSize() > 0)
        {
            data.appendFrom(const_cast<Parcel*>(obj), 0, obj->dataSize());
        }

        remote()->transact(NOTIFY, data, &reply, IBinder::FLAG_ONEWAY);
    }
};

IMPLEMENT_META_INTERFACE(DrmClient, "hisi.drm.IDrmClient");

// ----------------------------------------------------------------------

status_t BnDrmClient::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    switch (code)
    {
        case NOTIFY:
        {
            CHECK_INTERFACE(IDrmClient, data, reply);
            int eventType = data.readInt32();
            int extra = data.readInt32();
            Parcel obj;

            if (data.dataAvail() > 0)
            {
                obj.appendFrom(const_cast<Parcel*>(&data), data.dataPosition(), data.dataAvail());
            }

            notify((DrmPlugin::EventType)eventType, extra, &obj);
            return NO_ERROR;
        }
        break;

        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
