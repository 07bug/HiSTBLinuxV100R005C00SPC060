#ifndef _MyTestService_H
#define _MyTestService_H

#include "IMyTestService.h"
#include "IMyTestClient.h"

using namespace android;

class MyTestService: public BnMyTestService
{
public:
    static void instantiate();
    static MyTestService* getInstance();

    void func_getData(char*buf,int32_t len);
    void func_0byte();
    void func_4byte(char* buf);
    void func_16byte(char* buf);
    void func_64byte(char* buf);
    void func_256byte(char* buf);
    void func_1Kbyte(char* buf);
    void func_4Kbyte(char* buf);
    virtual void create(const sp<IMyTestClient> client);

private:

    MyTestService();
    ~MyTestService();
    void data_prepare();

    static MyTestService* pInstance;
    sp<IMyTestClient> m_mytestclient;
};

#endif // _MyTestService_H