#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include "MyTestService.h"

#define SERVICE_TEST_FUNC(x) void MyTestService::func##x##_getData(char*buf,int32_t len)\
{\
    printf("call MyTestService::func%d_getData()\n",x);\
    if((NULL != buf)&& (len >0)) \
        memset(buf,'a',len);\
}

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
    defaultServiceManager()->addService(String16("case2.service1"), pInstance);
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

/*void MyTestService::func_getData(char*buf,int32_t len)
{
    if((NULL != buf)&& (len >0))
        memset(buf,'a',len);
}*/
SERVICE_TEST_FUNC(1)
SERVICE_TEST_FUNC(2)
SERVICE_TEST_FUNC(3)
SERVICE_TEST_FUNC(4)
SERVICE_TEST_FUNC(5)
SERVICE_TEST_FUNC(6)
SERVICE_TEST_FUNC(7)
SERVICE_TEST_FUNC(8)
SERVICE_TEST_FUNC(9)
SERVICE_TEST_FUNC(10)
SERVICE_TEST_FUNC(11)
SERVICE_TEST_FUNC(12)
SERVICE_TEST_FUNC(13)
SERVICE_TEST_FUNC(14)
SERVICE_TEST_FUNC(15)
SERVICE_TEST_FUNC(16)
SERVICE_TEST_FUNC(17)
SERVICE_TEST_FUNC(18)
SERVICE_TEST_FUNC(19)
SERVICE_TEST_FUNC(20)
SERVICE_TEST_FUNC(21)
SERVICE_TEST_FUNC(22)
SERVICE_TEST_FUNC(23)
SERVICE_TEST_FUNC(24)
SERVICE_TEST_FUNC(25)
SERVICE_TEST_FUNC(26)
SERVICE_TEST_FUNC(27)
SERVICE_TEST_FUNC(28)
SERVICE_TEST_FUNC(29)
SERVICE_TEST_FUNC(30)
SERVICE_TEST_FUNC(31)
SERVICE_TEST_FUNC(32)

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
