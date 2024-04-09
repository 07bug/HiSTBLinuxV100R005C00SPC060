#include "sample_otp_base.h"
#include "hi_unf_otp.h"

HI_S32 main(int argc, char* argv[])
{
#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) ) && defined(HI_ADVCA_TYPE_NAGRA)
    sample_printf("Not support\n");
    return HI_SUCCESS;
#else
    HI_S32 ret = HI_SUCCESS;
    HI_U8 customer_key[16] = {0};

    ret = HI_UNF_OTP_Init();
    if (HI_SUCCESS != ret)
    {
        sample_printf("OTP init failed, return 0x%x\n", ret);
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_GetCustomerKey(customer_key, 16);
    if (HI_SUCCESS != ret)
    {
        sample_printf("Failed to get customer key, ret = 0x%x \n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    print_buffer("Get otp customer key", customer_key, sizeof(customer_key));

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
#endif
}

