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
#include <pthread.h>
#define TEST_PRINTF printf

void MyTestService::instantiate()
{
    pInstance = new MyTestService();
    defaultServiceManager()->addService(String16("test.mytestservice"), pInstance);
}

static pthread_t dispatcher_tid;

static void *dispatch_event_thread(void *ptr)
{
    MyTestService *pTestService = (MyTestService*)ptr;

    char *sender_name;
    char *receiver_name;

    TEST_PRINTF("create dispatch_event_thread thread\n");

    while(1)
    {
        pTestService->func_0byte();

        TEST_PRINTF("==== %s:%d  \n", __FUNCTION__, __LINE__);

        sleep(3);
    }

    TEST_PRINTF("==== %s:%d  \n", __FUNCTION__, __LINE__);
    pthread_exit(NULL);
    TEST_PRINTF("==== %s:%d  \n", __FUNCTION__, __LINE__);

    return NULL;
}

MyTestService::MyTestService()
{
    TEST_PRINTF("MyTestService created\n");

    int ret;

    pthread_attr_t r;
    pthread_attr_init(&r);
    pthread_attr_setdetachstate(&r, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&dispatcher_tid, &r, dispatch_event_thread, (void *)this);
    if(ret)
    {
        TEST_PRINTF("create dispatcher thread fail\n");
    }
}

MyTestService::~MyTestService()
{
    TEST_PRINTF("MyTestService destroyed\n");
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
    if (m_mytestclient != NULL)
    {
        TEST_PRINTF("==== %s:%d  \n", __FUNCTION__, __LINE__);
        m_mytestclient->notify();
    }
}

void MyTestService::create(const sp<IMyTestClient> client)
{
    TEST_PRINTF("==== %s:%d set test client \n", __FUNCTION__, __LINE__);
    m_mytestclient = client;
    TEST_PRINTF("==== %s:%d \n", __FUNCTION__, __LINE__);
    return ;
}

void MyTestService::func_0byte()
{
    printf("==== %s:%d call client notify \n", __FUNCTION__, __LINE__);
    if (m_mytestclient != NULL)
    {
        printf("==== %s:%d call client notify \n", __FUNCTION__, __LINE__);
        m_mytestclient->notify();
    }
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
