#include <stdio.h>
#include <time.h>
#include <utils/Log.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "IMyTestService.h"

#define TEST_TIME 10
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

int main(int argc, char** argv)
{
    //const sp<IMyTestService>& myservice = NULL;
    sp<IMyTestService> myservice;
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
    uint32_t retry = 0;
    char* buf =NULL;
    int32_t len;
    char buf_4byte[4];
    char buf_16byte[16];
    char buf_64byte[64];
    char buf_256byte[256];
    char buf_1Kbyte[1024];
    char buf_4kbyte[4096];
    int i;

    struct timeval time_start={0, 0},time_end={0, 0};

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
        printf("====have binder,get service sucess!\n");
        myservice = interface_cast<IMyTestService>(binder);
    }

     if(myservice == NULL)
     {
        printf("myservice is NULL,return\n");
        return -1;
     }

     //0byte
        printf("********start call,0 bytes test******\n");
        //time_start.tv_sec = time_start.tv_nsec = time_end.tv_sec = time_end.tv_nsec =0;
        gettimeofday(&time_start,NULL);
        for(i =0;i<TEST_TIME;i++)
        {
            myservice->func_0byte();
        }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     //4byte
        printf("********start call,4 bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
        gettimeofday(&time_start,NULL);
        for(i =0;i<TEST_TIME;i++)
        {
            memset(buf_4byte, 0, sizeof(buf_4byte));
            myservice->func_getData(buf_4byte,4);
        }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     //16byte
         printf("********start call,16 bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
          gettimeofday(&time_start,NULL);
         for(i =0;i<TEST_TIME;i++)
         {
             memset(buf_16byte, 0, sizeof(buf_16byte));
             myservice->func_getData(buf_16byte,16);
         }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     //64byte
         printf("********start call,64 bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
         gettimeofday(&time_start,NULL);
         for(i =0;i<TEST_TIME;i++)
         {
             memset(buf_64byte, 0, sizeof(buf_64byte));
             myservice->func_getData(buf_64byte,64);
         }
         gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     //256byte
         printf("********start call,256 bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
          gettimeofday(&time_start,NULL);
         for(i =0;i<TEST_TIME;i++)
         {
             memset(buf_256byte, 0, sizeof(buf_256byte));
             myservice->func_getData(buf_256byte,256);
         }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     //1Kbyte
         printf("********start call,1K bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
          gettimeofday(&time_start,NULL);
         for(i =0;i<TEST_TIME;i++)
         {
             memset(buf_1Kbyte, 0, sizeof(buf_1Kbyte));
             myservice->func_getData(buf_1Kbyte,1024);
         }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

    //4Kbyte
         printf("********start call,4k bytes test******\n");
         time_start.tv_sec =0;
         time_start.tv_usec =0;
         time_end.tv_sec = 0;
         time_end.tv_usec =0;
         gettimeofday(&time_start,NULL);
         for(i=0;i< TEST_TIME;i++)
         {
             memset(buf_4kbyte, 0, sizeof(buf_4kbyte));
             myservice->func_getData(buf_4kbyte,4096);
         }
        gettimeofday(&time_end,NULL);
        printf("start time %ld s,%ld us\n", time_start.tv_sec, time_start.tv_usec);
        printf("endtime %ld s,%ld us\n", time_end.tv_sec, time_end.tv_usec);
        printf("usetime:%ld ms\n", (time_end.tv_sec*1000+ time_end.tv_usec/1000)-(time_start.tv_sec*1000+time_start.tv_usec/1000));

     return 0;

}
