/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_otp_get_fuse.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-012-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "sample_otp_base.h"
#include "hi_unf_otp.h"
#include "hi_adp.h"
#include "hi_adp_mpi.h"

HI_BOOL g_otp_stop = HI_FALSE;

HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 ret;
    HI_CHAR input_cmd[32];

    ret = HI_UNF_OTP_Init();
    if (HI_SUCCESS != ret)
    {
        sample_printf("HI_UNF_ADVCA_Init failed\n");
        return HI_FAILURE;
    }

    printf("commonds:\n");
    printf("    q: quit.\n");

    while (HI_FALSE == g_otp_stop)
    {
        SAMPLE_GET_INPUTCMD(input_cmd);
        if ('q' == input_cmd[0])
        {
            printf("INFO: prepare to exit!\n");
            g_otp_stop = HI_TRUE;
        }
        else
        {
            printf("commonds:\n");
            printf("    q: quit.\n");
        }
    }

    (HI_VOID)HI_UNF_OTP_DeInit();
    return ret;
}

