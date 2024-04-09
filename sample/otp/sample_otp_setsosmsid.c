#include <stdio.h>
#include <stdlib.h>
#include "hi_unf_otp.h"
#include "hi_type.h"

HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 msid[4] = {0,0,0,0};
    HI_U32 id = 0;

    if(argc != 2)
    {
        printf("useage:input 4 byte stb sos market id.\n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        printf("OTP init failed, ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    id = strtol(argv[1], NULL, 16);
    msid[3] = (id >> 24) & 0xFF;
    msid[2] = (id >> 16) & 0xFF;
    msid[1] = (id >> 8)  & 0xFF;
    msid[0] = id         & 0xFF;
    ret = HI_UNF_OTP_SetSOSMSID(msid, 4);
    if(HI_SUCCESS != ret)
    {
        printf("Set OTP SOS market ID failed, ret = 0x%x \n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    printf("Set OTP SOS market ID:0x%x\n", id);
    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}


