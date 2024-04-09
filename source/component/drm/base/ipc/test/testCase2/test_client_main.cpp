#include <stdio.h>
#include <string.h>
#include <time.h>
#include <utils/Log.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "IMyTestService.h"

#define TEST_TIME 10000
#define SERVICE_NAME "case2.service1"

#if 0
const sp<IMyTestService>& getMyTestService()
{
        sp<IMyTestService> myservice;
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        uint32_t retry = 0;

        printf("getMyTestService\n");

        do
        {
            binder = sm->getService(String16("test.mytestservice"));
            if((binder != NULL) || (retry >= 2))
            {
                break;
            }
            printf("mytestservice not published, waiting...\n");
            usleep(500000); // 0.5 s
            retry++;
        } while(true);

        if(binder != NULL)
        {
            myservice = interface_cast<IMyTestService>(binder);
        }

        return myservice;
}
#endif

/*struct timespec
{
time_t tv_sec;
long int tv_nsec;
};*/

/*struct tmieval{
    time_t tv_sec;
    suseconds_t tv_usec;
};
*/

typedef void (IMyTestService::*call_func)(char* buf,int32_t len);

/*call_func select_call_function(int client,sp<IMyTestService> myservice)
{
    call_func pfunc;

    switch(client)
    {
        case 1:
            pfunc = myservice->func1_getData;
            break;
        case 2:
            pfunc = myservice->func2_getData;
            break;
        case 3:
            pfunc = myservice->func3_getData;
            break;
        case 4:
            pfunc = myservice->func4_getData;
            break;
        case 5:
            pfunc = myservice->func5_getData;
            break;
        case 6:
            pfunc = myservice->func6_getData;
            break;
        case 7:
            pfunc = myservice->func7_getData;
            break;
        case 8:
            pfunc = myservice->func8_getData;
            break;
        case 9:
            pfunc = myservice->func9_getData;
            break;
        case 10:
            pfunc = myservice->func10_getData;
            break;
        case 11:
            pfunc = myservice->func11_getData;
            break;
        case 12:
            pfunc = myservice->func12_getData;
            break;
        case 13:
            pfunc = myservice->func13_getData;
            break;
        case 14:
            pfunc = myservice->func14_getData;
            break;
        case 15:
            pfunc = myservice->func15_getData;
            break;
        case 16:
            pfunc = myservice->func16_getData;
            break;
        case 17:
            pfunc = myservice->func17_getData;
            break;
        case 18:
            pfunc = myservice->func18_getData;
            break;
        case 19:
            pfunc = myservice->func19_getData;
            break;
        case 20:
            pfunc = myservice->func20_getData;
            break;
        case 21:
            pfunc = myservice->func21_getData;
            break;
        case 22:
            pfunc = myservice->func22_getData;
            break;
        case 23:
            pfunc = myservice->func23_getData;
            break;
        case 24:
            pfunc = myservice->func24_getData;
            break;
        case 25:
            pfunc = myservice->func25_getData;
            break;
        case 26:
            pfunc = myservice->func26_getData;
            break;
        case 27:
            pfunc = myservice->func27_getData;
            break;
        case 28:
            pfunc = myservice->func28_getData;
            break;
        case 29:
            pfunc = myservice->func29_getData;
            break;
        case 30:
            pfunc = myservice->func30_getData;
            break;
        case 31:
            pfunc = myservice->func31_getData;
            break;
        case 32:
            pfunc = myservice->func32_getData;
            break;
         default:
            pfunc = myservice->func1_getData;
            break;
    }

    return pfunc;

}
*/
/*
@argv[1]:client name,shoule be 1,2,...32
@argv[2]:data len,should be 4,16,64,256,1024,4096
@argv[3]:client process count,used for sync...
@argv[4]:function flag<1:call same function,0:call diff functions>
*/
int main(int argc, char** argv)
{
    //const sp<IMyTestService>& myservice = NULL;
    sp<IMyTestService> myservice;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    uint32_t retry = 0;
    char* pbuf =NULL;
    int i;

    //client number,transact data size,client process name,call same func ?
    char clientName[16] ="client-";
    int  client;
    int dataLen;
    int clientCount;
    int funcFlag;

    struct timeval time_start={0, 0},time_end={0, 0};

    call_func pfunc;

    if(argc < 5)
    {
        printf("wrong params number,return...\n");
        return 0;
    }

    strcat(clientName,argv[1]);
    client = atoi(argv[1]);
    dataLen =atoi(argv[2]);
    clientCount = atoi(argv[3]);
    funcFlag = atoi(argv[4]);
    //printf("clientName = %s,dataLen =%d,clientCount = %d,funcFlag = %d...\n",clientName,dataLen,clientCount,funcFlag);

    printf("%s getMyTestService\n",clientName);

    do
    {
        binder = sm->getService(String16(SERVICE_NAME));
        if((binder != NULL) || (retry >= 2))
        {
            break;
        }
        printf("mytestservice not published, waiting...\n");
        usleep(500000); // 0.5 s
        retry++;
    } while(true);

    if(binder != NULL)
    {
        printf("****** Process %s,get service sucess! ******\n",clientName);
        myservice = interface_cast<IMyTestService>(binder);
    }

     if(myservice == NULL)
     {
        printf("******Process %s get service is NULL,return\n",clientName);
        return -1;
     }

         pbuf = (char*)malloc(dataLen);

    switch(client)
    {
        case 1:
            pfunc = &IMyTestService::func1_getData;
            break;
        case 2:
            pfunc = &IMyTestService::func2_getData;
            break;
        case 3:
            pfunc = &IMyTestService::func3_getData;
            break;
        case 4:
            pfunc = &IMyTestService::func4_getData;
            break;
        case 5:
            pfunc = &IMyTestService::func5_getData;
            break;
        case 6:
            pfunc = &IMyTestService::func6_getData;
            break;
        case 7:
            pfunc = &IMyTestService::func7_getData;
            break;
        case 8:
            pfunc = &IMyTestService::func8_getData;
            break;
        case 9:
            pfunc = &IMyTestService::func9_getData;
            break;
        case 10:
            pfunc = &IMyTestService::func10_getData;
            break;
        case 11:
            pfunc = &IMyTestService::func11_getData;
            break;
        case 12:
            pfunc = &IMyTestService::func12_getData;
            break;
        case 13:
            pfunc = &IMyTestService::func13_getData;
            break;
        case 14:
            pfunc = &IMyTestService::func14_getData;
            break;
        case 15:
            pfunc = &IMyTestService::func15_getData;
            break;
        case 16:
            pfunc = &IMyTestService::func16_getData;
            break;
        case 17:
            pfunc = &IMyTestService::func17_getData;
            break;
        case 18:
            pfunc = &IMyTestService::func18_getData;
            break;
        case 19:
            pfunc = &IMyTestService::func19_getData;
            break;
        case 20:
            pfunc = &IMyTestService::func20_getData;
            break;
        case 21:
            pfunc = &IMyTestService::func21_getData;
            break;
        case 22:
            pfunc = &IMyTestService::func22_getData;
            break;
        case 23:
            pfunc = &IMyTestService::func23_getData;
            break;
        case 24:
            pfunc = &IMyTestService::func24_getData;
            break;
        case 25:
            pfunc = &IMyTestService::func25_getData;
            break;
        case 26:
            pfunc = &IMyTestService::func26_getData;
            break;
        case 27:
            pfunc = &IMyTestService::func27_getData;
            break;
        case 28:
            pfunc = &IMyTestService::func28_getData;
            break;
        case 29:
            pfunc = &IMyTestService::func29_getData;
            break;
        case 30:
            pfunc = &IMyTestService::func30_getData;
            break;
        case 31:
            pfunc = &IMyTestService::func31_getData;
            break;
        case 32:
            pfunc = &IMyTestService::func32_getData;
            break;
         default:
            pfunc = &IMyTestService::func1_getData;
            break;
    }

        printf("********[client %s] start test,%d bytes test******\n",clientName,dataLen);
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
        gettimeofday(&time_start,NULL);
        for(i =0;i<TEST_TIME;i++)
        {
            ((*myservice).*pfunc)(pbuf,dataLen);
        }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("[client %s,len %d]usetime:%ld ms\n", clientName,dataLen,
            (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     free(pbuf);
     return 0;

}
