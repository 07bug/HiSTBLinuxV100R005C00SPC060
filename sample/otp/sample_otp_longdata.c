#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_unf_otp.h"
#include "hi_type.h"


HI_VOID help_show(HI_VOID)
{
    printf("\nhelp:\n");
    printf("./sample_otp_longdata wvalue [reserved_long_x] [u32Offset] [u32Length] [data0] [data1] ... \n");
    printf("./sample_otp_longdata rvalue [reserved_long_x] [u32Offset] [u32Length] \n");
    printf("./sample_otp_longdata [wlock,rlock] [reserved_long_x] [u32Offset] [u32Length] \n");
    printf("data : only write OTP data. \n");
    printf("./sample_otp_longdata wvalue reserved_long_0 0 1 0x11 \n");
    printf("./sample_otp_longdata rvalue reserved_long_0 0 1 \n");
    printf("./sample_otp_longdata wlock reserved_long_0 0 16 \n");
    printf("./sample_otp_longdata rlock reserved_long_0 0 16 \n");
    printf("\n");

}

HI_S32 main(int argc, char* argv[])
{
#define name_max_size 32
#define value_max_size 1024
    HI_S32          ret = HI_SUCCESS;
    HI_U32          func_type = 0;
    HI_U32          i   = 0;
    HI_CHAR         fuse_name[name_max_size];
    HI_U32          offset = 0;
    HI_U8           value[value_max_size] = {0};
    HI_U32          len;
    HI_U32          lock;

    if (argc <= 4 ||  0 == strncmp(argv[1], "help", 4) )
    {
        help_show();

        return 0;
    }

    ret = HI_UNF_OTP_Init();

    if (HI_SUCCESS != ret)
    {
        printf("OTP init failed!\n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    memcpy(fuse_name, argv[2], name_max_size);
    offset = strtol(argv[3], NULL, 10);
    len = strtol(argv[4], NULL, 10);

    if (0 == strncmp(argv[1], "wvalue", 6))
    {
        func_type = 1;
    }
    else if (0 == strncmp(argv[1], "rvalue", 6))
    {
        func_type = 2;
    }
    else if (0 == strncmp(argv[1], "wlock", 5))
    {
        func_type = 3;
    }
    else if (0 == strncmp(argv[1], "rlock", 5))
    {
        func_type = 4;
    }

    switch (func_type)
    {
        case 1:
            for (i = 0; i < len; i++)
            {
                if ( 5 + i < argc)
                {
                    value[i] = strtol(argv[5 + i], NULL, 16);
                }
                else
                {
                    value[i] =  0x0;
                }

                if (i > 0 && 0 == i % 16 )
                {
                    printf("\n");
                }

                printf("0X%02X ", value[i]);
            }

            printf("\n");

            HI_UNF_OTP_SetLongData(fuse_name, offset, value, len);
            break;
        case 2:
            ret = HI_UNF_OTP_GetLongData(fuse_name, offset, value, len);

            if (HI_SUCCESS == ret)
            {
                for (i = 0; i < len; i++)
                {
                    printf("aValue[%d]=0X%02X\n", i, value[i]);
                }
            }

            break;
        case 3:
            HI_UNF_OTP_SetLongDataLock(fuse_name, offset, len);
            break;
        case 4:
            ret = HI_UNF_OTP_GetLongDataLock(fuse_name, offset, len, &lock);

            if (HI_SUCCESS == ret)
            {
                printf("bLock[%d]\n", lock);
            }

            break;
        default:
            help_show();

            break;
    }

    (HI_VOID)HI_UNF_OTP_DeInit();
    return HI_SUCCESS;
}

