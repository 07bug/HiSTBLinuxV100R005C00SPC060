#ifndef IDRMCLIENT_H__
#define IDRMCLIENT_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <DrmAPI.h>
using namespace android;
class IDrmClient: public IInterface
{
public:
    DECLARE_META_INTERFACE(DrmClient);

    virtual HI_VOID notify(DrmPlugin::EventType eventType, HI_S32 extra, const Parcel* obj) = 0;
};


// ----------------------------------------------------------------------------

class BnDrmClient: public BnInterface<IDrmClient>
{
public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0);
};

#endif // IDRMCLIENT_H__
