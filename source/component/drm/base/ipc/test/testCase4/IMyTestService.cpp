#include <stdio.h>
#include <utils/Log.h>
#include "IMyTestService.h"

#define BP_TEST_FUNC(x) \
    void func##x##_getData(char* buf,int32_t len) \
    { \
         Parcel data, reply; \
         if(buf != NULL && len > 0) \
        { \
            data.writeInt32(len); \
            remote()->transact(TEST_CMD_GET_DATA_F##x, data, &reply);\
            data.read(buf,len);\
        } \
        else if(len ==0)\
        {\
            data.writeInt32(len); \
            remote()->transact(TEST_CMD_GET_DATA_F##x, data, &reply);\
        }\
        return; \
    }

#define TRANSACT_CASE(x) \
       case TEST_CMD_GET_DATA_F##x:\
        {\
            void* buf = NULL;\
            int32_t len = data.readInt32();\
            if(len > 0)\
            {\
                buf = malloc(len);\
                func##x##_getData((char*)buf,len);\
                reply->write(buf,len);\
                free(buf);\
            }\
            else if(len ==0)\
            {\
                func##x##_getData(NULL,0);\
            }\
            return NO_ERROR;\
         }\
        break;

enum
{
    TEST_CMD_GET_DATA_F1 = IBinder::FIRST_CALL_TRANSACTION,
    TEST_CMD_GET_DATA_F2,
    TEST_CMD_GET_DATA_F3,
    TEST_CMD_GET_DATA_F4,
    TEST_CMD_GET_DATA_F5,
    TEST_CMD_GET_DATA_F6,
    TEST_CMD_GET_DATA_F7,
    TEST_CMD_GET_DATA_F8,
    TEST_CMD_GET_DATA_F9,
    TEST_CMD_GET_DATA_F10,
    TEST_CMD_GET_DATA_F11,
    TEST_CMD_GET_DATA_F12,
    TEST_CMD_GET_DATA_F13,
    TEST_CMD_GET_DATA_F14,
    TEST_CMD_GET_DATA_F15,
    TEST_CMD_GET_DATA_F16,
    TEST_CMD_GET_DATA_F17,
    TEST_CMD_GET_DATA_F18,
    TEST_CMD_GET_DATA_F19,
    TEST_CMD_GET_DATA_F20,
    TEST_CMD_GET_DATA_F21,
    TEST_CMD_GET_DATA_F22,
    TEST_CMD_GET_DATA_F23,
    TEST_CMD_GET_DATA_F24,
    TEST_CMD_GET_DATA_F25,
    TEST_CMD_GET_DATA_F26,
    TEST_CMD_GET_DATA_F27,
    TEST_CMD_GET_DATA_F28,
    TEST_CMD_GET_DATA_F29,
    TEST_CMD_GET_DATA_F30,
    TEST_CMD_GET_DATA_F31,
    TEST_CMD_GET_DATA_F32,
    TEST_CMD_GET_DATA_SlEEP,
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

    /*void func1_getData(char*buf,int32_t len)
    {

        //printf("call BpMyTestService::func_getData()\n");
        Parcel data, reply;

        //len size range: 4,16,64,256,1K,4k bytes
        if(buf != NULL && len > 0)
        {
            //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
            data.writeInt32(len);
            remote()->transact(TEST_CMD_GET_DATA, data, &reply);
            data.read(buf,len);
        }
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }*/

    BP_TEST_FUNC(1)
    BP_TEST_FUNC(2)
    BP_TEST_FUNC(3)
    BP_TEST_FUNC(4)
    BP_TEST_FUNC(5)
    BP_TEST_FUNC(6)
    BP_TEST_FUNC(7)
    BP_TEST_FUNC(8)
    BP_TEST_FUNC(9)
    BP_TEST_FUNC(10)
    BP_TEST_FUNC(11)
    BP_TEST_FUNC(12)
    BP_TEST_FUNC(13)
    BP_TEST_FUNC(14)
    BP_TEST_FUNC(15)
    BP_TEST_FUNC(16)
    BP_TEST_FUNC(17)
    BP_TEST_FUNC(18)
    BP_TEST_FUNC(19)
    BP_TEST_FUNC(20)
    BP_TEST_FUNC(21)
    BP_TEST_FUNC(22)
    BP_TEST_FUNC(23)
    BP_TEST_FUNC(24)
    BP_TEST_FUNC(25)
    BP_TEST_FUNC(26)
    BP_TEST_FUNC(27)
    BP_TEST_FUNC(28)
    BP_TEST_FUNC(29)
    BP_TEST_FUNC(30)
    BP_TEST_FUNC(31)
    BP_TEST_FUNC(32)

   void func_getData_sleep_n_second(int32_t nSec)
    {
         Parcel data, reply;

        data.writeInt32(nSec);
        remote()->transact(TEST_CMD_GET_DATA_SlEEP, data, &reply);

        return;
    }

    void func_0byte()
    {
        //printf("call BpMyTestService::func_0byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        //data.writeCString("BpMyTestService::func1");
        remote()->transact(TEST_CMD_0_BYTE, data, &reply);

        //printf("reply data is :%s\n",reply.readCString());;
        return;
    }

    void func_4byte(char* buf)
    {
        //printf("call BpMyTestService::func_4byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_4_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_16byte(char* buf)
    {
        //printf("call BpMyTestService::func_16byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_16_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_64byte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_64_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_256byte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_256_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_1Kbyte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_1K_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

    void func_4Kbyte(char* buf)
    {
        //printf("call BpMyTestService::func_64byte()\n");
        Parcel data, reply;

        //data.writeInterfaceToken(IMyTestService::getInterfaceDescriptor());
        remote()->transact(TEST_CMD_4K_BYTE, data, &reply);
        data.read(buf,sizeof(buf));
        //printf("read buf size %d\n",sizeof(buf));
        return;
    }

};

IMPLEMENT_META_INTERFACE(MyTestService,"tcase.service");

// ----------------------------------------------------------------------

status_t BnMyTestService::onTransact(uint32_t code,
                                      const Parcel& data,
                                      Parcel* reply,
                                      uint32_t flags)
{
    switch(code)
    {

        /*case TEST_CMD_GET_DATA:
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
        break;*/
        TRANSACT_CASE(1)
        TRANSACT_CASE(2)
        TRANSACT_CASE(3)
        TRANSACT_CASE(4)
        TRANSACT_CASE(5)
        TRANSACT_CASE(6)
        TRANSACT_CASE(7)
        TRANSACT_CASE(8)
        TRANSACT_CASE(9)
        TRANSACT_CASE(10)
        TRANSACT_CASE(11)
        TRANSACT_CASE(12)
        TRANSACT_CASE(13)
        TRANSACT_CASE(14)
        TRANSACT_CASE(15)
        TRANSACT_CASE(16)
        TRANSACT_CASE(17)
        TRANSACT_CASE(18)
        TRANSACT_CASE(19)
        TRANSACT_CASE(20)
        TRANSACT_CASE(21)
        TRANSACT_CASE(22)
        TRANSACT_CASE(23)
        TRANSACT_CASE(24)
        TRANSACT_CASE(25)
        TRANSACT_CASE(26)
        TRANSACT_CASE(27)
        TRANSACT_CASE(28)
        TRANSACT_CASE(29)
        TRANSACT_CASE(30)
        TRANSACT_CASE(31)
        TRANSACT_CASE(32)

        case TEST_CMD_GET_DATA_SlEEP:
        {

            int32_t nSeconds = data.readInt32();

            func_getData_sleep_n_second(nSeconds);

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
