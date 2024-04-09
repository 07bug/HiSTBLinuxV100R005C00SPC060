#include <stdio.h>
#include <string.h>
#include <utils/Log.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "MyTestService.h"

/*
@argv[1]:server name,should be 1,2,3...32
*/
int main(int argc, char** argv)
{
    char serviceName[32]="tcase.server";
    sp<ProcessState> proc(ProcessState::self());
    if(argc < 2)
   {
        printf("wrong input params,return...\n");
        return 0;
   }

    strcat(serviceName,argv[1]);

    printf("start service:%s...\n",serviceName);
    //sp<IServiceManager> sm = defaultServiceManager();
    MyTestService::instantiate(serviceName);

    ProcessState::self()->startThreadPool();

    printf("start join thread pool...\n");
    IPCThreadState::self()->joinThreadPool();
 }