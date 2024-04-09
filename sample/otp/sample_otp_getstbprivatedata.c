#include "sample_otp_base.h"
#include "hi_unf_otp.h"

HI_S32 main(int argc, char *argv[])
{
#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) ) && defined(HI_ADVCA_TYPE_NAGRA)
    sample_printf("not support\n");
    return HI_SUCCESS;
#else
    HI_S32 ret = HI_SUCCESS;
    HI_U8 stb_privdata[16] = {0};
    HI_U32 i = 0;

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        sample_printf("OTP init failed, ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    for(i = 0; i < 16; i++)
    {
        ret = HI_UNF_OTP_GetStbPrivData(i, &stb_privdata[i]);
        if(HI_SUCCESS != ret)
        {
            sample_printf("Failed to get STB private data, ret = 0x%x \n", ret);
            (HI_VOID)HI_UNF_OTP_DeInit();
            return HI_FAILURE;
        }
    }

    print_buffer("Get STB private data", stb_privdata, sizeof(stb_privdata));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return ret;
#endif
}

