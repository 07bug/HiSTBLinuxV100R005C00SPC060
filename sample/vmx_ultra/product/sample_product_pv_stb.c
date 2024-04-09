/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_otp.h"
#include "hi_unf_ecs.h"


#define HI_VMX_PRODUCT_CONFIT_NUM 1024

#define HI_DEBUG_OTP printf

static HI_U32 g_u32PVDataCount = 0;
static HI_UNF_OTP_BURN_PV_ITEM_S g_stPVCustomerCfg[HI_VMX_PRODUCT_CONFIT_NUM];
static HI_CHAR g_acVerifyFuseName[][OTP_FIELD_NAME_MAX_LEN] =
{
    "HDCP_RootKey",
    "CRC_HDCP_RootKey",
    "STB_TA_RootKey",
    "CRC_STB_TA_RootKey",
    "stb_ta_kl_disable",
    "STB_RootKey",
    "CRC_STB_RootKey",
    "SW_RootKey",
    "CRC_SW_RootKey",
    "sw_kl_disable",
    "STB_Version_REF",
    "MSID",
    "ASC_MSID",
    "SOS_MSID",
    "TA1_SMID",
    "TA2_SMID",
    "TA3_SMID",
    "TA4_SMID",
    "TA5_SMID",
    "TA6_SMID",
    "TA1_Cert_SecVersion_Ref",
    "TA1_SecVersion_Ref",
    "TA2_Cert_SecVersion_Ref",
    "TA2_SecVersion_Ref",
    "TA3_Cert_SecVersion_Ref",
    "TA3_SecVersion_Ref",
    "TA4_Cert_SecVersion_Ref",
    "TA4_SecVersion_Ref",
    "TA5_Cert_SecVersion_Ref",
    "TA5_SecVersion_Ref",
    "TA6_Cert_SecVersion_Ref",
    "TA6_SecVersion_Ref",
    "sm1_disable",
    "sm2_disable",
    "sm3_disable",
    "r2r_sm4_disable",
    "ts_tdes_disable",
    "ts_sm4_disable",
    "hard_uart_disable",
    "hard_uart_mcu_disable",
    "chip_jtag_prt_mode",
    "boot_mode_sel",
    "bootsel_ctrl",
    "ddr_wakeup_disable",
    "runtime_check_en",
    "bload_dec_en",
    "soc_tee_enable",
    "SCS_activation"
};


/******************************* API declaration *****************************/

static HI_BOOL HI_VMX_Product_CheckFuseName()
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 flag = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 k = 0;

    HI_DEBUG_OTP("\n ************ verify fuse name. *************\n");

    for (i = 0; i < g_u32PVDataCount; i++ )
    {
        flag = HI_FAILURE;

        for (k = 0; k < sizeof(g_acVerifyFuseName) / sizeof(g_acVerifyFuseName[0]); k++)
        {
            if (0 == strncasecmp(g_acVerifyFuseName[k], g_stPVCustomerCfg[i].aszFieldName, OTP_FIELD_NAME_MAX_LEN ))
            {
                flag = HI_SUCCESS;
                break;
            }
        }

        if (flag != HI_SUCCESS)
        {
            HI_DEBUG_OTP(" OTP %s verify failure.\n", g_stPVCustomerCfg[i].aszFieldName);
            ret = HI_FAILURE;
        }
    }

    if (ret == HI_SUCCESS)
    {
        HI_DEBUG_OTP(" OTP fuse name verify success.\n");
    }
    else
    {
        HI_DEBUG_OTP(" OTP fuse name verify failure.\n");
    }

    HI_DEBUG_OTP(" ************ Verify fuse name end. *************\n");
    return ret;
}

static HI_VOID HI_VMX_Product_ShowPVData(HI_UNF_OTP_BURN_PV_ITEM_S* pv_data)
{
    HI_U32 i = 0;

    if (NULL == pv_data)
    {
        HI_DEBUG_OTP("pv_data is null. line(%d)\n", __LINE__);
        return ;
    }

    HI_DEBUG_OTP("fuse_name: %s\n", pv_data->aszFieldName);
    HI_DEBUG_OTP("     Burn: %s\n", (pv_data->bBurn == HI_TRUE) ? "true" : "false" );
    HI_DEBUG_OTP("     Lock: %s\n", (pv_data->bLock == HI_TRUE) ? "true" : "false" );
    HI_DEBUG_OTP("value len: 0x%x\n", pv_data->u32ValueLen);
    HI_DEBUG_OTP("value:\n");
    HI_DEBUG_OTP("%8s", "");

    for (i = 0 ; i < pv_data->u32ValueLen; i++)
    {
        if ( (i != 0) && (0 == (i % 16)))
        {
            HI_DEBUG_OTP("\n%8s", "");
        }

        HI_DEBUG_OTP("0x%02x ", pv_data->au8Value[i]);
    }

    HI_DEBUG_OTP("\n\n");
}

static HI_S32 HI_VMX_Product_SetOTPValue(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;

    HI_DEBUG_OTP("\n ************ Burn PV DATA *************\n");

    for (i = 0; i < g_u32PVDataCount; i++)
    {
        if (g_stPVCustomerCfg[i].bBurn == HI_FALSE)
        {
            HI_DEBUG_OTP("Not burn %s OTP.\n", g_stPVCustomerCfg[i].aszFieldName);
            continue;
        }

        ret = HI_UNF_OTP_BurnProductPV(&g_stPVCustomerCfg[i], 1);
        if (HI_SUCCESS != ret)
        {
            HI_DEBUG_OTP("\nBurn %s OTP Failure.\n", g_stPVCustomerCfg[i].aszFieldName);
            HI_VMX_Product_ShowPVData(&g_stPVCustomerCfg[i]);
        }
        else
        {
            HI_DEBUG_OTP("Burn %s OTP Success.\n", g_stPVCustomerCfg[i].aszFieldName);
        }
    }

    HI_DEBUG_OTP("\n ************ Burn PV DATA, End *************\n");
    return ret;
}

static HI_VOID PrintHelpInfo(HI_VOID)
{
    HI_DEBUG_OTP("Usage: ./sample_product_pv_stb  pv_cfg_file    ---->  set pv value\n");
    return;
}

static HI_S32 HI_VMX_Product_ReadPVDATAConfig(HI_CHAR* pFileNamePVCfg)
{
    HI_S32 s32Count;
    HI_S32 i;
    FILE* pFileInput = HI_NULL;
    HI_CHAR line_str[2048] = {0};
    HI_CHAR fusename[OTP_FIELD_NAME_MAX_LEN] = {""};
    HI_CHAR lock[6] = {""};
    HI_CHAR burn[6] = {""};
    HI_CHAR len[32] = {""};
    HI_CHAR value[OTP_FIELD_VALUE_MAX_LEN] = {""};
    HI_CHAR* p = NULL;
    HI_U32 u32OTPByteCnt = 1;

    if (HI_NULL == pFileNamePVCfg)
    {
        HI_DEBUG_OTP("file name error!\n");
        return HI_FAILURE;
    }

    pFileInput = fopen(pFileNamePVCfg, "rb");
    if (NULL == pFileInput)
    {
        HI_DEBUG_OTP("open file %s error!\n", pFileNamePVCfg);
        return HI_FAILURE;
    }

    if (HI_NULL != pFileInput)
    {

        memset(g_stPVCustomerCfg, 0, sizeof(g_stPVCustomerCfg));

        while (1)
        {
            memset(fusename, 0, sizeof(fusename));
            memset(lock, 0, sizeof(lock));
            memset(burn, 0, sizeof(burn));
            memset(len, 0, sizeof(len));
            memset(value, 0, sizeof(value));
            memset(line_str, 0, sizeof(line_str));
            p = fgets(line_str, 2048, pFileInput);
            if (p == HI_NULL)
            {
                //HI_DEBUG_OTP("Read to end of the file\n");
                break;
            }

            if (0 == strncmp("/", line_str, 1))
            {
                //HI_DEBUG_OTP("Comment line\n");
                continue;
            }

            if (strlen(line_str) < 5)
            {
                HI_DEBUG_OTP("error line\n");
                break;
            }

            s32Count = sscanf(line_str, "%s %s %s %s %s", fusename, burn, lock, len, value);
            if (s32Count <= 0)
            {
                break;
            }

            for (i = 0; i < 32; i++)
            {
                g_stPVCustomerCfg[g_u32PVDataCount].aszFieldName[i] = tolower(fusename[i]);
            }

            g_stPVCustomerCfg[g_u32PVDataCount].u32ValueLen = strtol(len, NULL, 16);

            if (g_stPVCustomerCfg[g_u32PVDataCount].u32ValueLen < 1)
            {
                HI_DEBUG_OTP("Value Len:%x\n", g_stPVCustomerCfg[g_u32PVDataCount].u32ValueLen);
                break;
            }

            if (0 == strncmp(burn, "false", 5))
            {
                g_stPVCustomerCfg[g_u32PVDataCount].bBurn = HI_FALSE;
            }
            else if (0 == strncmp(burn, "true", 4))
            {
                g_stPVCustomerCfg[g_u32PVDataCount].bBurn = HI_TRUE;
            }
            else
            {

            }

            if (0 == strncmp(lock, "false", 5))
            {
                g_stPVCustomerCfg[g_u32PVDataCount].bLock = HI_FALSE;
            }
            else if (0 == strncmp(lock, "true", 4))
            {
                g_stPVCustomerCfg[g_u32PVDataCount].bLock = HI_TRUE;
            }
            else
            {

            }

            p = 0;
            u32OTPByteCnt = 1;
            p = strtok(value, ",");

            if (p != 0)
            {
                g_stPVCustomerCfg[g_u32PVDataCount].au8Value[0] = strtol(p, NULL, 16);

                while ( 0 != (p = strtok(NULL, ",")) )
                {
                    g_stPVCustomerCfg[g_u32PVDataCount].au8Value[u32OTPByteCnt] = strtol(p, NULL, 16);
                    u32OTPByteCnt++;
                }
            }

            g_u32PVDataCount++;
        }

        fclose(pFileInput);
    }

    return HI_SUCCESS;
}

static HI_VOID HI_VMX_Product_ShowPVLIST()
{
    HI_U32 i = 0;

    HI_DEBUG_OTP("\n ************ Show PV DATA *************\n");

    for (i = 0; i < g_u32PVDataCount; i++ )
    {
        HI_VMX_Product_ShowPVData(&g_stPVCustomerCfg[i]);
        HI_DEBUG_OTP("\n\n");
    }

    HI_DEBUG_OTP("\n ************ Show PV DATA, End *************\n");
}


HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_S32 s32Confirm = 0;

    if (argc < 2)
    {
        PrintHelpInfo();
        return HI_FAILURE;
    }

    if (argv[1] == HI_NULL)
    {
        PrintHelpInfo();
        return HI_FAILURE;

    }

    HI_VMX_Product_ReadPVDATAConfig(argv[1]);

    if (HI_FAILURE == HI_VMX_Product_CheckFuseName())
    {
        HI_DEBUG_OTP("\n Please check the %s configuration file otp fuse name.\n", argv[1]);
        return HI_FAILURE;
    }

    HI_VMX_Product_ShowPVLIST();
    HI_DEBUG_OTP("\n\n ************ Check the burnt PV DATA. *************\n\n");
    HI_DEBUG_OTP("\nEnter 1 to confirm the burning. Other values exit. Please enter:");
    scanf("%d", &s32Confirm);

    if (1 != s32Confirm)
    {
        HI_DEBUG_OTP("Exit burn\n");
        goto EXIT_SAMPLE;
    }

    Ret = HI_UNF_OTP_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_OTP("call HI_UNF_OTP_Init() failed, ret=0x%x\n", Ret);
        goto EXIT_SAMPLE;
    }

    Ret = HI_VMX_Product_SetOTPValue();
    if (HI_SUCCESS != Ret)
    {
        HI_DEBUG_OTP("call HI_VMX_Product_SetOTPValue() failed, ret=0x%x\n", Ret);
        goto EXIT_SAMPLE;
    }

    (HI_VOID)HI_UNF_OTP_DeInit();

EXIT_SAMPLE:

    HI_DEBUG_OTP("\r\n************ Set/Get PV List End, Ret=0x%x *************\n\n", Ret);

    return Ret;
}
