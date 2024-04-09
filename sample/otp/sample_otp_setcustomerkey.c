#include "sample_otp_base.h"
#include "hi_unf_otp.h"

HI_S32 main(int argc, char *argv[])
{
#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) ) && defined(HI_ADVCA_TYPE_NAGRA)
        sample_printf("not support\n");
        return HI_SUCCESS;
#else
    HI_S32 ret = HI_SUCCESS;
    HI_U8 customer_key[16] = {0x12,0x34,0x56,0x78,0,0,0,0,0,0,0,0,0,0,0,0};

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        sample_printf("OTP init failed, ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_SetCustomerKey(customer_key, 16);
    if(HI_SUCCESS != ret)
    {
        sample_printf("Set customer key failed, ret = 0x%x \n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    print_buffer("Set otp customer key", customer_key, sizeof(customer_key));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
#endif
}

