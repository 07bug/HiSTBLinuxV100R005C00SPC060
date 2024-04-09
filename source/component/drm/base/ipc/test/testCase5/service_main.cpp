#include <utils/Log.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "MyTestService.h"

int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());

    printf("start my service...\n");
    //sp<IServiceManager> sm = defaultServiceManager();
    MyTestService::instantiate();

    ProcessState::self()->startThreadPool();

    printf("start join thread pool...\n");
    IPCThreadState::self()->joinThreadPool();
 }