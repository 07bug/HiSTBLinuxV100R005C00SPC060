#include <stdio.h>
#include <utils/Log.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "MyTestClient.h"
#include "IMyTestService.h"

using namespace android;
#define TEST_PRINTF

MyTestClient::MyTestClient()
{
}

MyTestClient::~MyTestClient()
{
}

void MyTestClient::notify()
{
    printf("====================== call me, you are welcome!!!!!!!!!!!! \n");
    return;
}

void MyTestClient::Cll_client()
{
    sp<IMyTestService> myservice;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    uint32_t retry = 0;

    do
    {
        binder = sm->getService(String16("test.mytestservice"));
        if ((binder != NULL) || (retry >= 2))
        {
            printf("retry = %d\n", retry);
            break;
        }
        TEST_PRINTF("mytestservice not published, waiting...\n");
        usleep(500000); // 0.5 s
        retry++;
    } while(true);

    if (binder != NULL)
    {
        TEST_PRINTF("====+++++++++++++have binder,get service sucess!\n");
        myservice = interface_cast<IMyTestService>(binder);
        TEST_PRINTF("====+++++++++++++have binder,get service sucess 0!\n");
        myservice->func_0byte();
        TEST_PRINTF("====+++++++++++++have binder,get service sucess 1!\n");
    }
}

void MyTestClient::call_server()
{
    sp<IMyTestService> myservice;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    uint32_t retry = 0;

    do
    {
        binder = sm->getService(String16("test.mytestservice"));
        if ((binder != NULL) || (retry >= 2))
        {
            printf("retry = %d\n", retry);
            break;
        }
        TEST_PRINTF("mytestservice not published, waiting...\n");
        usleep(500000); // 0.5 s
        retry++;
    } while(true);

    if (binder != NULL)
    {
        TEST_PRINTF("====have binder,get service sucess!\n");
        myservice = interface_cast<IMyTestService>(binder);
        printf("====have binder,get service sucess 0!\n");
        myservice->create(this);
        printf("====have binder,get service sucess 1!\n");
    }
}
