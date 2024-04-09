/******************************************************************************

Copyright (C), 2004-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_otp_setscsenable.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-07-18
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_unf_otp.h"


HI_S32 main(int argc, char *argv[])
{
    HI_S32 ret =HI_SUCCESS;
    HI_BOOL pbEnable;

    ret = HI_UNF_OTP_Init();
    if(HI_SUCCESS != ret)
    {
        printf("OTP init failed, ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_GetSCSStat(&pbEnable);
    if(HI_SUCCESS != ret)
    {
        printf("Failed to get scs status, return:%x\n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    if(HI_TRUE == pbEnable)
    {
        printf("OTP SCS has already been enabled.\n");
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_OTP_EnableSCS();
    if(HI_SUCCESS != ret)
    {
        printf("OTP enable SCS enable failed, ret = 0x%x \n", ret);
        (HI_VOID)HI_UNF_OTP_DeInit();
        return HI_FAILURE;
    }

    printf("OTP enable SCS enable success\n");

    (HI_VOID)HI_UNF_OTP_DeInit();

    return HI_SUCCESS;
}


