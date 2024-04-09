#include <stdio.h>
#include <utils/Log.h>
#include "IMyTestClient.h"

using namespace android;

#define TEST_PRINTF

enum
{
    TEST_CMD_NOTIFY = IBinder::FIRST_CALL_TRANSACTION,
};

class BpMyTestClient: public BpInterface<IMyTestClient>
{
public:
    BpMyTestClient(const sp<IBinder>& impl)
    : BpInterface<IMyTestClient>(impl)
    {
    }

    void notify()
    {
        TEST_PRINTF("call notify function %d\n", __LINE__);
        TEST_PRINTF("==== %s:%d \n", __FUNCTION__, __LINE__);
        Parcel data, reply;
        printf("==== [%s:%d] ================= call trancat, cmd is TEST_CMD_NOTIFY before \n", __FUNCTION__, __LINE__);
        remote()->transact(TEST_CMD_NOTIFY, data, &reply);
        printf("==== [%s:%d] ================= call trancat, cmd is TEST_CMD_NOTIFY end\n", __FUNCTION__, __LINE__);
        return;
    }
};

IMPLEMENT_META_INTERFACE(MyTestClient,"test.MyTestClient");
// ----------------------------------------------------------------------

status_t BnMyTestClient::onTransact(uint32_t code,
                                      const Parcel& data,
                                      Parcel* reply,
                                      uint32_t flags)
{
    switch(code)
    {
        case TEST_CMD_NOTIFY:
        {
            printf("000000000000000000 ************ &&&&&&&&&&&&Receive TEST_CMD_NOTIFY \n");
            notify();
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
        }
        break;

    default:

        return BBinder::onTransact(code, data, reply, flags);
    }
}
