/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_otp_set_fuse.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-07-20
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "sample_otp_base.h"
#include "hi_unf_otp.h"

#define CHECK_PARAM_NULL(param)    \
        do \
        {  \
            if(NULL == (param)) { \
                sample_printf("sample parameter error.\n");   \
                return (HI_ERR_OTP_INVALID_PARA);   \
            } \
        }while(0)

#define otp_table_size  (sizeof(otp_table)/sizeof(otp_table[0]))

HI_S32 marketid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 bootversionid_sample(HI_S32 argc, HI_CHAR** argv,OTP_SAMPLE*sample);
HI_S32 scs_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 trustzone_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 normal_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 secure_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 rsakey_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 close_usb_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 close_uart_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 close_netport_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 bootmode_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample);
HI_S32 taid_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample);
HI_S32 sos_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);

static OTP_SAMPLE otp_table[] =
{
    {0 ,"help"              , NULL                      , {"Display this help and exit.", "example: ./sample_otp_set_fuse help"}},
    {1 ,"marketid"          , &marketid_sample          , {"[value] ---> value is a 32-bit integer.","example: ./sample_otp_set_fuse marketid 0x12345678"} },
    {2 ,"bootversionid"     , &bootversionid_sample     , {"[value] ---> value is a 32-bit integer."," example: ./sample_otp_set_fuse bootversionid 0x00000001"} },
    {3 ,"scs"               , &scs_sample               , {"[type] ---> type[spi | nand | emmc].","example:./sample_otp_set_fuse scs [emmc],The type field is discarded by NAGRA."}},
    {4 ,"trustzone"         , &trustzone_sample         , {"Set trustzone enable.","example: ./sample_otp_set_fuse trustzone"}},
    {5 ,"normal"            , &normal_sample            , {"Set non-CA chipset.","example: ./sample_otp_set_fuse normal"}},
    {6 ,"secure"            , &secure_sample            , {"Set CA chipset.","example: ./sample_otp_set_fuse secure"}},
    {7 ,"rsakey"            , &rsakey_sample            , {"[filename] ---> filename:The root key file name.","example: ./sample_otp_set_fuse rsakey root_rsa_pub.bin"}},
    {8 ,"usb2_disable"      , &close_usb_sample         , {"USB2.0 is hardware disabled.","example: ./sample_otp_set_fuse usb2_disable"}},
    {9 ,"usb30_disable"     , &close_usb_sample         , {"USB3.0 is hardware disabled.","example: ./sample_otp_set_fuse usb30_disable"}},
    {10,"mcu_disable"       , &close_uart_sample        , {"UART 0 is hardware disabled.","example: ./sample_otp_set_fuse mcu_disable"}},
    {11,"uart_disable"      , &close_uart_sample        , {"UART 2/3 is hardware disabled.","example: ./sample_otp_set_fuse uart_disable"}},
    {12,"suart_disable"     , &close_uart_sample        , {"Panda UART is hardware disabled.","example: ./sample_otp_set_fuse suart_disable"}},
    {13,"gemac0_disable"    , &close_netport_sample     , {"GEMAC 0 is hardware disabled.","example: ./sample_otp_set_fuse gemac0_disable"}},
    {14,"gemac1_disable"    , &close_netport_sample     , {"GEMAC 1 is hardware disabled.","example: ./sample_otp_set_fuse gemac1_disable"}},
    {15,"femac_disable"     , &close_netport_sample     , {"FEMAC is hardware disabled.","example: ./sample_otp_set_fuse femac_disable"}},
    {16,"taid_msid"         , &taid_msid_sample         , {"[index] [taid] [msid] ---> index[1~6],taid and msid is a 32-bit integer.","example: ./sample_otp_set_fuse taid_msid 1 0x12345678 0x12345678"}},
    {17,"sos_msid"          , &sos_msid_sample          , {"[value] ---> value is a 32-bit integer.","example: ./sample_otp_set_fuse sos_msid 0x12345678"}},
};

OTP_SAMPLE* get_opt(HI_CHAR* argv)
{
    HI_U32 i;

    for (i = 0; i < otp_table_size; i++)
    {
        if (case_strcmp(otp_table[i].name, argv))
        {
            return &otp_table[i];
        }
    }
    return NULL;
}

HI_S32 get_flash_type(HI_CHAR* pValue, HI_UNF_OTP_FLASH_TYPE_E* penFlashType)
{
    HI_S32 ret = HI_SUCCESS;

    if (case_strcmp(pValue, "spi"))
    {
        *penFlashType = HI_UNF_OTP_FLASH_TYPE_SPI;
    }
    else if (case_strcmp(pValue, "nand"))
    {
        *penFlashType = HI_UNF_OTP_FLASH_TYPE_NAND;
    }
    else if (case_strcmp(pValue, "emmc"))
    {
        *penFlashType = HI_UNF_OTP_FLASH_TYPE_EMMC;
    }
    else
    {
        ret = HI_ERR_OTP_INVALID_PARA;
    }

    return ret;
}

HI_S32 marketid_sample(HI_S32 argc, HI_CHAR** argv,OTP_SAMPLE*sample)
{
    HI_U8   buf[4] = {0};
    HI_U32  length = 4;
    HI_U32  value = 0;

    CHECK_PARAM_NULL(argv[1]);
    CHECK_PARAM_NULL(argv[2]);
    value = strtoul(argv[2], NULL, 16);
    buf[0] =  value        & 0xFF;
    buf[1] = (value >> 8)  & 0xFF;
    buf[2] = (value >> 16) & 0xFF;
    buf[3] = (value >> 24) & 0xFF;
    sample_printf("%s:0x%x\n", argv[1], value);
    return HI_UNF_OTP_SetMSID(buf, length);
}

HI_S32 sos_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_U8   buf[4] = {0};
    HI_U32  length = 4;
    HI_U32  value = 0;
    CHECK_PARAM_NULL(argv[1]);
    CHECK_PARAM_NULL(argv[2]);
    value = strtoul(argv[2], NULL, 16);
    buf[0] =  value        & 0xFF;
    buf[1] = (value >> 8)  & 0xFF;
    buf[2] = (value >> 16) & 0xFF;
    buf[3] = (value >> 24) & 0xFF;
    sample_printf("%s:0x%x\n", argv[1], value);
    return HI_UNF_OTP_SetSOSMSID(buf, length);
}

HI_S32 bootversionid_sample(HI_S32 argc, HI_CHAR** argv,OTP_SAMPLE*sample)
{
    HI_U8   buf[4] = {0};
    HI_U32  length = 4;
    HI_U32  value = 0;

    CHECK_PARAM_NULL(argv[1]);
    CHECK_PARAM_NULL(argv[2]);
    value = strtoul(argv[2], NULL, 16);
    buf[0] =  value        & 0xFF;
    buf[1] = (value >> 8)  & 0xFF;
    buf[2] = (value >> 16) & 0xFF;
    buf[3] = (value >> 24) & 0xFF;
    sample_printf("%s:0x%x\n", argv[1], value);
    return HI_UNF_OTP_SetBootVersionID(buf, length);
}

HI_S32 scs_sample(HI_S32 argc, HI_CHAR** argv,OTP_SAMPLE*sample)
{
    HI_S32 ret = HI_FAILURE;
#ifndef HI_ADVCA_TYPE_NAGRA
    HI_UNF_OTP_FLASH_TYPE_E flash_type;

    CHECK_PARAM_NULL(argv[2]);

    memset(&flash_type,0, sizeof(flash_type));
    ret = get_flash_type(argv[2], &flash_type);
    if (HI_SUCCESS != ret)
    {
        sample_printf("sample parameter error.\n\n");
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }
#endif
    ret = HI_UNF_OTP_EnableSCS();
    if (HI_SUCCESS !=  ret )
    {
        sample_printf("enable scs failed.\n\n");
        return ret;
    }
#ifndef HI_ADVCA_TYPE_NAGRA
    ret = HI_UNF_OTP_SetBootMode(flash_type);
#endif
    return ret;
}

HI_S32 rsakey_sample(HI_S32 argc, HI_CHAR** argv,OTP_SAMPLE*sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_U32  length = 512;
    HI_U8 rsa_key[512] = {0};
    FILE* fp = NULL;

    CHECK_PARAM_NULL(argv[2]);
    fp = fopen(argv[2], "rb");
    if (NULL == fp)
    {
        sample_printf("Open root_rsa_pub.bin failed.\n");
        return ret;
    }

    fread(rsa_key, 1, length, fp);
    fclose(fp);
    print_buffer(argv[1], rsa_key, length);
    ret = HI_UNF_OTP_SetRSAKey(rsa_key, length);
    return ret;
}

HI_S32 trustzone_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) ) && defined(HI_ADVCA_TYPE_NAGRA)
        sample_printf("Not support\n");
        return HI_SUCCESS;
#else
    return HI_UNF_OTP_EnableTrustZone();
#endif
}

HI_S32 normal_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    return HI_UNF_OTP_BurnToNormalChipset();
}

HI_S32 secure_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    return HI_UNF_OTP_BurnToSecureChipset();
}

HI_S32 close_usb_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_UNF_OTP_BURN_PV_ITEM_S pv_data[] =
    {
        {HI_FALSE, "hard_usb2_disable", 0x1, {0x1}, HI_TRUE},
        {HI_FALSE, "hard_usb30_disable", 0x1, {0x1}, HI_TRUE},
    };

    CHECK_PARAM_NULL(argv[1]);

    if (case_strcmp(argv[1], "usb2_disable"))
    {
        pv_data[0].bBurn = HI_TRUE;
    }
    else if (case_strcmp(argv[1], "usb30_disable"))
    {
        pv_data[1].bBurn = HI_TRUE;
    }
    else
    {
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }

    ret = HI_UNF_OTP_BurnProductPV(pv_data, sizeof(pv_data) / sizeof(pv_data[0]));
    return ret;
}

HI_S32 close_uart_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_UNF_OTP_BURN_PV_ITEM_S pv_data[] =
    {
        {HI_FALSE, "hard_uart_mcu_disable", 0x1, {0x1}  , HI_TRUE},
        {HI_FALSE, "hard_uart_disable", 0x1, {0x1}  , HI_TRUE},
        {HI_FALSE, "hard_suart_disable", 0x1, {0x1}  , HI_TRUE},
    };

    CHECK_PARAM_NULL(argv[1]);

    if (case_strcmp(argv[1], "mcu_disable"))
    {
        pv_data[0].bBurn = HI_TRUE;
    }
    else if (case_strcmp(argv[1], "uart_disable"))
    {
        pv_data[1].bBurn = HI_TRUE;
    }
    else if (case_strcmp(argv[1], "suart_disable"))
    {
        pv_data[2].bBurn = HI_TRUE;
    }
    else
    {
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }

    ret = HI_UNF_OTP_BurnProductPV(pv_data, sizeof(pv_data) / sizeof(pv_data[0]));
    return ret;
}

HI_S32 close_netport_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_UNF_OTP_BURN_PV_ITEM_S pv_data[] =
    {
        {HI_FALSE, "hard_gemac0_disable", 0x1, {0x1} , HI_TRUE},
        {HI_FALSE, "hard_gemac1_disable", 0x1, {0x1} , HI_TRUE},
        {HI_FALSE, "hard_femac_disable", 0x1, {0x1} , HI_TRUE},
    };

    CHECK_PARAM_NULL(argv[1]);

    if (case_strcmp(argv[1], "gemac0_disable"))
    {
        pv_data[0].bBurn = HI_TRUE;
    }
    else if (case_strcmp(argv[1], "gemac1_disable"))
    {
        pv_data[1].bBurn = HI_TRUE;
    }
    else if (case_strcmp(argv[1], "femac_disable"))
    {
        pv_data[2].bBurn = HI_TRUE;
    }
    else
    {
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }

    ret = HI_UNF_OTP_BurnProductPV(pv_data, sizeof(pv_data) / sizeof(pv_data[0]));
    return ret;
}

HI_S32 taid_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_U32 ta_id = 0x0;
    HI_U32 ms_id = 0x0;
    HI_UNF_OTP_TA_INDEX_E ta_index;
    HI_S32 index = -1;

    CHECK_PARAM_NULL(argv[2]);
    CHECK_PARAM_NULL(argv[3]);
    CHECK_PARAM_NULL(argv[4]);

    index = strtoul(argv[2], NULL, 10);
    ta_index = index + HI_UNF_OTP_TA_INDEX_1 - 1;
    if (HI_UNF_OTP_TA_INDEX_1 > ta_index || HI_UNF_OTP_TA_INDEX_BUTT <= ta_index)
    {
        sample_printf("Parameter index error:index=%d\n", index);
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }
    ta_id = strtoul(argv[3], NULL, 16);
    ms_id = strtoul(argv[4], NULL, 16);
    sample_printf("index:0x%x\n", index);
    sample_printf(" taid:0x%x\n", ta_id);
    sample_printf(" msid:0x%x\n", ms_id);

    ret = HI_UNF_OTP_SetTAIDAndMSID(ta_index, ta_id, ms_id);
    return ret;
}

HI_S32 bootmode_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_UNF_OTP_BURN_PV_ITEM_S pv_data[] =
    {
        {HI_TRUE, "bootsel_ctrl", 0x1, {0x1}, HI_TRUE},
    };

    CHECK_PARAM_NULL(argv[1]);

    if (case_strcmp(argv[1], sample->name))
    {
        pv_data[0].bBurn = HI_TRUE;
    }
    else
    {
        ret = HI_ERR_OTP_INVALID_PARA;
        return ret;
    }

    ret = HI_UNF_OTP_BurnProductPV(pv_data, sizeof(pv_data) / sizeof(pv_data[0]));
    return ret;
}

HI_S32 run_cmdline(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 ret = HI_FAILURE;
    OTP_SAMPLE* sample = NULL;

    CHECK_PARAM_NULL(argv[1]);
    sample = get_opt(argv[1]);
    CHECK_PARAM_NULL(sample);
    if (sample->run_sample)
    {
        ret = (*sample->run_sample)(argc, argv,sample);
    }
    else
    {
        sample_printf(" otp sample error.\n");
    }

    return ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 ret = HI_SUCCESS;

    if (argc < 2)
    {
        sample_printf("sample parameter error.\n");
        ret = HI_ERR_OTP_INVALID_PARA;
        goto DEINIT;
    }

    if (case_strcmp("help", argv[1]))
    {
        show_usage(otp_table, otp_table_size);
        goto EXIT_SAMPLE;
    }

    ret = HI_UNF_OTP_Init();

    if (HI_SUCCESS != ret)
    {
        sample_printf("OTP init failed\n");
        return HI_FAILURE;
    }

    ret = run_cmdline(argc, argv);
    (HI_VOID)HI_UNF_OTP_DeInit();

DEINIT:
    show_returne_msg(otp_table, otp_table_size, ret);

EXIT_SAMPLE:
    return ret;
}

