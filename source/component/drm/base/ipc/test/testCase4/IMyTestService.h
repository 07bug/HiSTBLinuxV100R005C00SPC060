#ifndef _IMMPLAYER_CLIENT_H_
#define _IMMPLAYER_CLIENT_H_

#include <binder/IInterface.h>
#include <binder/Parcel.h>

using namespace android;

class IMyTestService: public IInterface
{
    public:
    DECLARE_META_INTERFACE(MyTestService);

    virtual void func1_getData(char*buf,int32_t len) = 0;
    virtual void func2_getData(char*buf,int32_t len) = 0;
    virtual void func3_getData(char*buf,int32_t len) = 0;
    virtual void func4_getData(char*buf,int32_t len) = 0;
    virtual void func5_getData(char*buf,int32_t len) = 0;
    virtual void func6_getData(char*buf,int32_t len) = 0;
    virtual void func7_getData(char*buf,int32_t len) = 0;
    virtual void func8_getData(char*buf,int32_t len) = 0;
    virtual void func9_getData(char*buf,int32_t len) = 0;
    virtual void func10_getData(char*buf,int32_t len) = 0;
    virtual void func11_getData(char*buf,int32_t len) = 0;
    virtual void func12_getData(char*buf,int32_t len) = 0;
    virtual void func13_getData(char*buf,int32_t len) = 0;
    virtual void func14_getData(char*buf,int32_t len) = 0;
    virtual void func15_getData(char*buf,int32_t len) = 0;
    virtual void func16_getData(char*buf,int32_t len) = 0;
    virtual void func17_getData(char*buf,int32_t len) = 0;
    virtual void func18_getData(char*buf,int32_t len) = 0;
    virtual void func19_getData(char*buf,int32_t len) = 0;
    virtual void func20_getData(char*buf,int32_t len) = 0;
    virtual void func21_getData(char*buf,int32_t len) = 0;
    virtual void func22_getData(char*buf,int32_t len) = 0;
    virtual void func23_getData(char*buf,int32_t len) = 0;
    virtual void func24_getData(char*buf,int32_t len) = 0;
    virtual void func25_getData(char*buf,int32_t len) = 0;
    virtual void func26_getData(char*buf,int32_t len) = 0;
    virtual void func27_getData(char*buf,int32_t len) = 0;
    virtual void func28_getData(char*buf,int32_t len) = 0;
    virtual void func29_getData(char*buf,int32_t len) = 0;
    virtual void func30_getData(char*buf,int32_t len) = 0;
    virtual void func31_getData(char*buf,int32_t len) = 0;
    virtual void func32_getData(char*buf,int32_t len) = 0;

    virtual void func_getData_sleep_n_second(int32_t nSec) = 0;

    virtual void func_0byte() = 0;
    virtual void func_4byte(char* buf) = 0;
    virtual void func_16byte(char* buf) = 0;
    virtual void func_64byte(char* buf) = 0;
    virtual void func_256byte(char* buf) = 0;
    virtual void func_1Kbyte(char* buf) = 0;
    virtual void func_4Kbyte(char* buf) = 0;

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
