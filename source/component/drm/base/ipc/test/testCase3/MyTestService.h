#ifndef _MyTestService_H
#define _MyTestService_H

#include "IMyTestService.h"

using namespace android;

class MyTestService: public BnMyTestService
{
public:
    static void instantiate(char* pServiceName);
    static MyTestService* getInstance();

    void func1_getData(char*buf,int32_t len);
    void func2_getData(char*buf,int32_t len);
    void func3_getData(char*buf,int32_t len);
    void func4_getData(char*buf,int32_t len);
    void func5_getData(char*buf,int32_t len);
    void func6_getData(char*buf,int32_t len);
    void func7_getData(char*buf,int32_t len);
    void func8_getData(char*buf,int32_t len);
    void func9_getData(char*buf,int32_t len);
    void func10_getData(char*buf,int32_t len);
    void func11_getData(char*buf,int32_t len);
    void func12_getData(char*buf,int32_t len);
    void func13_getData(char*buf,int32_t len);
    void func14_getData(char*buf,int32_t len);
    void func15_getData(char*buf,int32_t len);
    void func16_getData(char*buf,int32_t len);
    void func17_getData(char*buf,int32_t len);
    void func18_getData(char*buf,int32_t len);
    void func19_getData(char*buf,int32_t len);
    void func20_getData(char*buf,int32_t len);
    void func21_getData(char*buf,int32_t len);
    void func22_getData(char*buf,int32_t len);
    void func23_getData(char*buf,int32_t len);
    void func24_getData(char*buf,int32_t len);
    void func25_getData(char*buf,int32_t len);
    void func26_getData(char*buf,int32_t len);
    void func27_getData(char*buf,int32_t len);
    void func28_getData(char*buf,int32_t len);
    void func29_getData(char*buf,int32_t len);
    void func30_getData(char*buf,int32_t len);
    void func31_getData(char*buf,int32_t len);
    void func32_getData(char*buf,int32_t len);

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