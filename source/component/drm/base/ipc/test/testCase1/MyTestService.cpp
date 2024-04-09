#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include "MyTestService.h"

MyTestService* MyTestService::pInstance = NULL;

char buf_4byte[4];
char buf_16byte[16];
char buf_64byte[64];
char buf_256byte[256];
char buf_1Kbyte[1024];
char buf_4kbyte[4096];

void MyTestService::instantiate()
{
    pInstance = new MyTestService();
    defaultServiceManager()->addService(String16("test.mytestservice"), pInstance);
}

MyTestService::MyTestService()
{
    printf("MyTestService created\n");
}

MyTestService::~MyTestService()
{
    printf("MyTestService destroyed\n");
}

MyTestService* MyTestService::getInstance()
{
    return pInstance;
}

void MyTestService::data_prepare()
{

}

void MyTestService::func_getData(char*buf,int32_t len)
{
    if((NULL != buf)&& (len >0))
        memset(buf,'a',len);
}

void MyTestService::func_0byte()
{

}
void MyTestService::func_4byte(char* buf)
{

}
void MyTestService::func_16byte(char* buf)
{

}
void MyTestService::func_64byte(char* buf)
{

}
void MyTestService::func_256byte(char* buf)
{

}
void MyTestService::func_1Kbyte(char* buf)
{

}
void MyTestService::func_4Kbyte(char* buf)
{

}
