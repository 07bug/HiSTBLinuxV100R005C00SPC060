#ifndef _IMMPLAYER_CLIENT_H_
#define _IMMPLAYER_CLIENT_H_

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "IMyTestClient.h"

using namespace android;

class IMyTestService: public IInterface
{
    public:
    DECLARE_META_INTERFACE(MyTestService);

    virtual void func_getData(char*buf,int32_t len) = 0;
    virtual void func_0byte() = 0;
    virtual void func_4byte(char* buf) = 0;
    virtual void func_16byte(char* buf) = 0;
    virtual void func_64byte(char* buf) = 0;
    virtual void func_256byte(char* buf) = 0;
    virtual void func_1Kbyte(char* buf) = 0;
    virtual void func_4Kbyte(char* buf) = 0;
    virtual void create(const sp<IMyTestClient> client) = 0;
};

class BnMyTestService: public BnInterface<IMyTestService>
{
    public:
    virtual status_t onTransact(uint32_t code,
                                const Parcel& data,
                                Parcel* reply,
                                uint32_t flags = 0);
};

#endif // _IMMPLAYER_CLIENT_H_
