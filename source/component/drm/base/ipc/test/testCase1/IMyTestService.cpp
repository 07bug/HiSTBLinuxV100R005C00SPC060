#include <stdio.h>
#include <utils/Log.h>
#include "IMyTestService.h"

enum
{
    TEST_CMD_GET_DATA = IBinder::FIRST_CALL_TRANSACTION,
    TEST_CMD_0_BYTE,
    TEST_CMD_4_BYTE,
    TEST_CMD_16_BYTE,
    TEST_CMD_64_BYTE,
    TEST_CMD_256_BYTE,
    TEST_CMD_1K_BYTE,
    TEST_CMD_4K_BYTE
};

class BpMyTestService: public BpInterface<IMyTestService>
{
public:
    BpMyTestService(const sp<IBinder>& impl)
    : BpInterface<IMyTestService>(impl)
    {
    }

    void func_getData(char*buf,int32_t len)
    {

        //printf("call BpMyTestService::func_getData()\n");
        Parcel data, reply;

        //len size range: 4,16,64,256,1K,4k bytes
        if(buf != NULL && len > 0)
        {
            //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
            data.writeInt32(len);
            remote()->transact(TEST_CMD_GET_DATA, data, &reply);
            reply.read(buf,/*sizeof(buf)*/len);
        }
        printf("read buf size %d, buf0:%d\n",sizeof(buf), buf[0]);
        return;
    }

    void func_0byte()
    {
        //printf("call BpMyTestService::func_0byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        data.writeCString("BpMyTestService::func1");
        remote()->transact(TEST_CMD_0_BYTE, data, &reply);

        printf("reply data is :%s\n",reply.readCString());;
        return;
    }

    void func_4byte(char* buf)
    {
        //printf("call BpMyTestService::func_4byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_4_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_16byte(char* buf)
    {
        //printf("call BpMyTestService::func_16byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_16_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_64byte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_64_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_256byte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_256_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_1Kbyte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_1K_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_4Kbyte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_4K_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

};

IMPLEMENT_META_INTERFACE(MyTestService,"test.MyTestService");

// ----------------------------------------------------------------------

status_t BnMyTestService::onTransact(uint32_t code,
                                      const Parcel& data,
                                      Parcel* reply,
                                      uint32_t flags)
{
    switch(code)
    {

        case TEST_CMD_GET_DATA:
        {
            //printf("Receive TEST_CMD_GET_DATA\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);
            void* buf = NULL;
            int32_t len = data.readInt32();

            buf = malloc(len);
            func_getData((char*)buf,len);
            reply->write(buf,len);
            free(buf);
            return NO_ERROR;
         }
        break;

        case TEST_CMD_0_BYTE:
        {
            //printf("Receive TEST_CMD_0_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);
            func_0byte();
            return NO_ERROR;
         }
        break;

        case TEST_CMD_4_BYTE:
        {
            printf("Receive TEST_CMD_4_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

        case TEST_CMD_16_BYTE:
        {
            printf("Receive TEST_CMD_16_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

        case TEST_CMD_64_BYTE:
        {
            printf("Receive TEST_CMD_64_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

        case TEST_CMD_256_BYTE:
        {
            printf("Receive TEST_CMD_256_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

        case TEST_CMD_1K_BYTE:
        {
            printf("Receive TEST_CMD_1K_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

        case TEST_CMD_4K_BYTE:
        {
            printf("Receive TEST_CMD_4K_BYTE\n");
            //CHECK_INTERFACE(IMyTestService, data, reply);

            return NO_ERROR;
         }
        break;

    default:

        return BBinder::onTransact(code, data, reply, flags);
    }
}
