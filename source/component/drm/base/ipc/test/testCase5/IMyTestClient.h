#ifndef _IMMPLAYER_XXX_H_
#define _IMMPLAYER_XXX_H_

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

using namespace android;

class IMyTestClient: public IInterface
{
    public:
    DECLARE_META_INTERFACE(MyTestClient);

    virtual void notify() = 0;
};

class BnMyTestClient: public BnInterface<IMyTestClient>
{
    public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0);
};

#endif // _IMMPLAYER_XXX_H_
