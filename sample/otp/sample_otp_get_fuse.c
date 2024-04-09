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

#define CHECK_PARAM_NULL(param)    \
        do \
        {  \
            if(NULL == (param)) { \
                sample_printf("sample parameter error.\n");   \
                return (HI_ERR_OTP_INVALID_PARA);   \
            } \
        }while(0)

#define otp_table_size  (sizeof(otp_table)/sizeof(otp_table[0]))

OTP_SAMPLE* get_opt(HI_CHAR* argv);
HI_S32 marketid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 bootversionid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 scs_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 trustzone_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 idword_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 rsakeylock_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);
HI_S32 taid_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample);
HI_S32 sos_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample);

static OTP_SAMPLE otp_table[] =
{
    {0 ,"help"             , NULL                          , {"Display this help and exit.", "example: ./sample_otp_get_fuse help"}},
    {1 ,"marketid"         , &marketid_sample              , {"Get market segment id.", "example: ./sample_otp_get_fuse marketid"}},
    {2 ,"bootversionid"    , &bootversionid_sample         , {"Get boot version id.","example: ./sample_otp_get_fuse bootversionid"}},
    {3 ,"scs"              , &scs_sample                   , {"Get secure chipset startup status.","example: ./sample_otp_get_fuse scs"}},
    //{4 ,"id_word"          , &idword_sample              , {""}},
    {5 ,"rsakeylock"       , &rsakeylock_sample            , {"Get root RSA key lock status.", "example: ./sample_otp_get_fuse rsakeylock"}},
    {6 ,"trustzone"        , &trustzone_sample             , {"Get trustzone status.", "example: ./sample_otp_get_fuse trustzone"}},
    {7 ,"taid_msid"        , &taid_msid_sample             , {"[index] ---> index[1~6].","example: ./sample_otp_get_fuse taid_msid 1"}},
    {8 ,"sos_msid"         , &sos_msid_sample              , {"Get sos market segment id.","example: ./sample_otp_get_fuse sos_msid"}},
};

HI_S32 rsakeylock_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_BOOL state;
    HI_S32 ret;

    ret = HI_UNF_OTP_GetRSALockStat(&state);
    if (HI_SUCCESS == ret)
    {
        sample_printf("rsakeylock status %s.\n", ((state == HI_FALSE) ? "not locked" : "locked" ));
    }
    return ret;
}

HI_S32 idword_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    sample_printf("id_word sample not supported.\n");
    return HI_SUCCESS;
}

HI_S32 trustzone_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
#if (defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) ) && defined(HI_ADVCA_TYPE_NAGRA)
            sample_printf("not support\n");
            return HI_SUCCESS;
#else
    HI_BOOL state;
    HI_S32 ret;

    ret = HI_UNF_OTP_GetTrustZoneStat(&state);
    if (HI_SUCCESS == ret)
    {
        sample_printf("trustzone %s.\n", ((state == HI_FALSE) ? "not enabled" : "enabled" ));
    }
    return ret;
#endif
}

HI_S32 taid_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE* sample)
{
    HI_S32  ret = HI_FAILURE;
    HI_U32 ta_id = 0x0;
    HI_U32 ms_id = 0x0;
    HI_UNF_OTP_TA_INDEX_E ta_index;
    HI_S32 index = -1;

    CHECK_PARAM_NULL(argv[2]);

    index = strtoul(argv[2], NULL, 10);
    ta_index = index + HI_UNF_OTP_TA_INDEX_1 - 1;
    if (HI_UNF_OTP_TA_INDEX_1 > ta_index || HI_UNF_OTP_TA_INDEX_BUTT <= ta_index)
    {
        sample_printf("Parameter index error:index=%d\n", index);
        return ret;
    }

    ret = HI_UNF_OTP_GetTAIDAndMSID(ta_index, &ta_id, &ms_id);
    if (HI_SUCCESS == ret)
    {
        sample_printf("taid:0x%x\n", ta_id);
        sample_printf("msid:0x%x\n", ms_id);
    }

    return ret;
}

HI_S32 scs_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_BOOL state;
    HI_S32 ret;

    ret = HI_UNF_OTP_GetSCSStat(&state);
    if (HI_SUCCESS == ret)
    {
        sample_printf("scs %s.\n", ((state == HI_FALSE) ? "not enabled" : "enabled" ));
    }
    return ret;
}

HI_S32 bootversionid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_U32 length = 4;
    HI_U8   buf[4] = {0};
    HI_S32 ret;
    HI_U32 i = 0, version_id;

    ret = HI_UNF_OTP_GetBootVersionID(buf, &length);
    if (HI_SUCCESS == ret)
    {
        version_id = 0x0;
        for (i = 0; i < length; i++)
        {
            version_id  |= ((buf[i] & 0xFF )  << i*8 );
        }
        sample_printf("boot version id: 0x%x\n", version_id);
    }
    return ret;
}

HI_S32 marketid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_U32 length = 4;
    HI_U8   buf[4] = {0};
    HI_S32 ret;
    HI_U32 i = 0, marketid;

    ret = HI_UNF_OTP_GetMSID(buf, &length);
    if (HI_SUCCESS == ret)
    {
        marketid = 0x0;
        for (i = 0; i < length; i++)
        {
            marketid  |= ((buf[i] & 0xFF )  << i*8 );
        }
        sample_printf("market id: 0x%x\n", marketid);

    }
    return ret;
}

HI_S32 sos_msid_sample(HI_S32 argc, HI_CHAR** argv, OTP_SAMPLE*sample)
{
    HI_U32 length = 4;
    HI_U8   buf[4] = {0};
    HI_S32 ret;
    HI_U32 i = 0, sos_msid;

    ret = HI_UNF_OTP_GetSOSMSID(buf, &length);
    if (HI_SUCCESS == ret)
    {
        sos_msid = 0x0;
        for (i = 0; i < length; i++)
        {
            sos_msid  |= ((buf[i] & 0xFF )  << i*8 );
        }
        sample_printf("sos market id: 0x%x\n", sos_msid);

    }
    return ret;
}

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

