#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "../drm_ipc/server/DrmService.h"


int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());

    DrmService::instantiate();

    ProcessState::self()->startThreadPool();

    IPCThreadState::self()->joinThreadPool();

    return 1;
}
