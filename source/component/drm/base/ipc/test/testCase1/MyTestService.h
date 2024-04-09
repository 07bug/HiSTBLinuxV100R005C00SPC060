#ifndef _MyTestService_H
#define _MyTestService_H

#include "IMyTestService.h"

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

private:

    MyTestService();
    ~MyTestService();
    void data_prepare();

    static MyTestService* pInstance;
};

#endif // _MyTestService_H