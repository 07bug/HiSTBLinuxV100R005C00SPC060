/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_acc.c
  Version       : Initial Draft
  Author        :
  Created       : 2016/09/23
  Description   :

******************************************************************************/
#include "hi_math.h"
#include "pq_mng_acc.h"
#include "pq_hal_acc.h"

static ALG_ACC_S sg_stPQACCInfo;
static PQ_PARAM_S *sg_pstPqParam  = HI_NULL;

#if defined(PQ_ACC_45_SUPPORT)
static HI_S32 sg_au32AccUse[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 139, 279, 414, 549, 647, 793, 911, 1023, //LowTable
    0, 109, 226, 362, 511, 665, 804, 917, 1023, //MidTable
    0, 114, 236, 356, 484, 614, 771, 911, 1023, //HighTable
    0, 109, 238, 383, 535, 675, 804, 917, 1023, //MidLowTable
    0, 110, 226, 347, 483, 639, 789, 917, 1023  //MidHighTable
};

static HI_S32 sg_au32AccGallerySdr[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 130, 270, 406, 530, 640, 768, 896, 1023, /* LowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidTable */
    0, 100, 240, 360, 496, 620, 764, 864, 1023, /* HighTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidLowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidHighTable */
};

static HI_S32 sg_au32AccGalleryHdr[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 130, 270, 406, 530, 640, 768, 896, 1023, /* LowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidTable */
    0, 100, 240, 360, 496, 620, 764, 864, 1023, /* HighTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidLowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidHighTable */
};

static HI_S32 sg_au32AccBasic[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023
};

static HI_S32 sg_au32AccStreamId1[ACC_TABLE_LEVEL_PARA] =
{
    0, 64, 142, 237, 328, 752, 886, 961, 1023, //LowTable
};

static HI_S32 sg_au32AccStreamId1_1[ACC_TABLE_LEVEL_PARA] =
{
    0, 68, 129, 260, 455, 741, 885, 968, 1023, //HighTable
};

static HI_S32 sg_au32AccStreamId2_low[ACC_TABLE_LEVEL_PARA] =
{
    //0, 51, 111, 209, 422, 636, 891, 986, 1023, //LowTable

    0, 89, 183, 288, 434, 668, 874, 983, 1023, //LowTable
};

static HI_S32 sg_au32AccStreamId2_mid[ACC_TABLE_LEVEL_PARA] =
{
    0, 109, 226, 413, 590, 784,  929, 1000, 1023, /* MidTable */
};

#elif defined(PQ_ACC_27_SUPPORT)

static HI_S32 sg_au32AccUse[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 139, 279, 414, 549, 647, 793, 911, 1023, //LowTable
    0, 109, 226, 362, 511, 665, 804, 917, 1023, //MidTable
    0, 114, 236, 356, 484, 614, 771, 911, 1023, //HighTable
};

static HI_S32 sg_au32AccGallerySdr[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 130, 270, 406, 530, 640, 768, 896, 1023, /* LowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidTable */
    0, 100, 240, 360, 496, 620, 764, 864, 1023, /* HighTable */
};

static HI_S32 sg_au32AccGalleryHdr[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 130, 270, 406, 530, 640, 768, 896, 1023, /* LowTable */
    0, 110, 240, 384, 540, 670, 800, 880, 1023, /* MidTable */
    0, 100, 240, 360, 496, 620, 764, 864, 1023, /* HighTable */
};

static HI_S32 sg_au32AccBasic[ACC_TABLE_LEVEL_MAX *ACC_TABLE_LEVEL_PARA] =
{
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
    0, 128, 256, 384, 512, 640, 768, 896, 1023,
};
#if !defined(CHIP_TYPE_hi3798mv310)
static HI_S32 sg_au32AccStreamId1[ACC_TABLE_LEVEL_PARA] =
{
    0, 64, 142, 237, 328, 752, 886, 961, 1023, //LowTable
};

static HI_S32 sg_au32AccStreamId2_low[ACC_TABLE_LEVEL_PARA] =
{
    0, 89, 183, 288, 434, 668, 874, 983, 1023, //LowTable
};

#else
static HI_S32 sg_au32AccStreamId2_low[ACC_TABLE_LEVEL_PARA] =
{
    0, 133, 281, 432, 567, 701, 822, 918, 1023, //LowTable
};
#endif

static HI_S32 sg_au32AccStreamId1_1[ACC_TABLE_LEVEL_PARA] =
{
    0, 68, 129, 260, 455, 741, 885, 968, 1023, //HighTable
};

static HI_S32 sg_au32AccStreamId2_mid[ACC_TABLE_LEVEL_PARA] =
{
    0, 109, 226, 413, 590, 784,  929, 1000, 1023, /* MidTable */
};

#endif

HI_S32 PQ_MNG_SetAccLevel(HI_U32 u32ACCLevel);

static HI_S32 PQ_MNG_ACCParaInit(HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_HAL_ACC_PARA_S stAccPara;

    stAccPara.stAccCfg.acc_en       = HI_TRUE;
    stAccPara.stAccCfg.acc_mode     = HI_FALSE;
    stAccPara.stAccCfg.acc_dbg_mode = HI_TRUE;
    stAccPara.stAccCfg.acc_dbg_en   = HI_FALSE;
    stAccPara.stAccCfg.acc_rst      = HI_FALSE;

    stAccPara.thd_med_low   = 280;
    stAccPara.thd_high      = 620;
    stAccPara.thd_low       = 400;
    stAccPara.thd_med_high  = 740;

    s32Ret = PQ_HAL_SetAccPara(PQ_HAL_LAYER_VID0, stAccPara);

    return s32Ret;
}

static HI_VOID PQ_MNG_ACCLutInit(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    PQ_CHECK_NULL_PTR_RE_NULL(pstPqParam);

    sg_pstPqParam = pstPqParam;

    if (HI_TRUE == bDefault)
    {
        memcpy((HI_VOID *)(pstPqParam->stPQCoef.stACCCoef.as32AccLut), (HI_VOID *)sg_au32AccUse,
               sizeof(sg_au32AccUse));
    }
    else
    {
        memcpy((HI_VOID *)sg_au32AccUse, (HI_VOID *)(pstPqParam->stPQCoef.stACCCoef.as32AccLut),
               sizeof(sg_au32AccUse));
    }

    return ;
}

HI_S32 PQ_MNG_GetACCHistgram(HI_PQ_ACC_HISTGRAM_S *pstACCHist)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCHist);

    s32Ret = PQ_HAL_GetACCHistgram((ACC_HISTGRAM_S *)pstACCHist);

    return s32Ret;
}

HI_S32 PQ_MNG_InitACC(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == sg_stPQACCInfo.bInit)
    {
        return HI_SUCCESS;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqParam);

    sg_stPQACCInfo.bEnable        = HI_TRUE;
    sg_stPQACCInfo.u32Strength    = 50;
    sg_stPQACCInfo.bHdrProcessEn  = HI_FALSE;
    sg_stPQACCInfo.bDemoEnable    = HI_FALSE;
    sg_stPQACCInfo.eDemoMode      = PQ_DEMO_ENABLE_R;
    sg_stPQACCInfo.u32StreamId    = 0;
    sg_stPQACCInfo.u32StreamIdSetMode  = HI_TRUE; //Default Para On

    s32Ret = PQ_MNG_ACCParaInit(bParaUseTableDefault);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_ACCParaInit error!\n");
        sg_stPQACCInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    s32Ret = PQ_TABLE_InitPhyList(PQ_VDP_LAYER_VID0, HI_PQ_MODULE_DCI, PQ_SOURCE_MODE_NO, PQ_OUTPUT_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("DCI InitPhyList error\n");
        sg_stPQACCInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    PQ_MNG_ACCLutInit(pstPqParam, bParaUseTableDefault);

    PQ_MNG_SetAccLevel(50);

    sg_stPQACCInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitACC(HI_VOID)
{
    if (HI_FALSE == sg_stPQACCInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQACCInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCEn(HI_U32 *pu32OnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32OnOff);

    *pu32OnOff = sg_stPQACCInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCEn(HI_BOOL bOnOff)
{
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutputMode = PQ_COMM_GetOutputMode();
    PQ_STATUS_S stPqStatus = {0};
    HI_BOOL bAccEn1 = HI_TRUE;
    HI_BOOL bAccEn2 = HI_TRUE;
    HI_BOOL bAccEn3 = HI_TRUE;

    if ((OUTPUT_MODE_PREVIEW == enOutputMode) || (OUTPUT_MODE_REMOTE == enOutputMode))
    {
        bAccEn1 = HI_FALSE;
    }

    if ((enSourceMode < PQ_SOURCE_MODE_BUTT)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DCI, enSourceMode)))
    {
        bAccEn2 = HI_FALSE;
    }

    PQ_COMM_GetPqStatus(&stPqStatus);

    if (PQ_IMAGE_MODE_VIDEOPHONE == stPqStatus.enImageMode)
    {
        bAccEn3 = HI_FALSE;
    }

    sg_stPQACCInfo.bEnable = bOnOff & bAccEn1 & bAccEn2 & bAccEn3;

    PQ_HAL_SetAccAccEn(PQ_HAL_LAYER_VID0, sg_stPQACCInfo.bEnable);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCDemoEn(HI_BOOL bOnOff)
{
    /* acc demo off for only support 50% pos */
    PQ_HAL_SetAccDemoEn(PQ_HAL_LAYER_VID0, HI_FALSE);

    sg_stPQACCInfo.bDemoEnable = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQACCInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCDemoMode(PQ_DEMO_MODE_E enMode)
{
    PQ_HAL_LAYER_VID_E u32ChId   = PQ_HAL_LAYER_VID0;
    ACC_DEMO_MODE_E    enAccMode = ACC_DEMO_ENABLE_R;

    sg_stPQACCInfo.eDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enAccMode = ACC_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enAccMode = ACC_DEMO_ENABLE_R;
    }

    PQ_HAL_SetAccDemoMode(u32ChId, enAccMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetACCDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penMode);

    *penMode = sg_stPQACCInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetAccLevel(HI_U32 *pu32ACCLevel)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32ACCLevel);

    *pu32ACCLevel = sg_stPQACCInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetAccLevel(HI_U32 u32ACCLevel)
{
    HI_U32 i;
    HI_U32 au32AccTable[ACC_TABLE_LEVEL_MAX * ACC_TABLE_LEVEL_PARA] = {0};
    HI_S32 s32TmpTableDate = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_STATUS_S stPqStatus = {0};

    if (u32ACCLevel > 100)
    {
        HI_ERR_PQ("%d:ACC Level is over range!\n", u32ACCLevel);
        return HI_FAILURE;
    }

    PQ_COMM_GetPqStatus(&stPqStatus);

    sg_stPQACCInfo.u32Strength = u32ACCLevel;

    if (PQ_IMAGE_MODE_GALLERY == stPqStatus.enImageMode)
    {
        for (i = 0; i < ACC_TABLE_LEVEL_MAX * ACC_TABLE_LEVEL_PARA; i++)
        {
            if (HI_TRUE == sg_stPQACCInfo.bHdrProcessEn)
            {
                if ( u32ACCLevel < 50)
                {
                    s32TmpTableDate = sg_au32AccBasic[i] + (sg_au32AccGalleryHdr[i] - sg_au32AccBasic[i]) * (HI_S32)u32ACCLevel / 50;
                }
                else
                {
                    s32TmpTableDate = (sg_au32AccGalleryHdr[i] + (sg_au32AccGalleryHdr[i] - sg_au32AccBasic[i]) * ((HI_S32)u32ACCLevel - 50) / 50);
                }
            }
            else
            {
                if ( u32ACCLevel < 50)
                {
                    s32TmpTableDate = sg_au32AccBasic[i] + (sg_au32AccGallerySdr[i] - sg_au32AccBasic[i]) * (HI_S32)u32ACCLevel / 50;
                }
                else
                {
                    s32TmpTableDate = (sg_au32AccGallerySdr[i] + (sg_au32AccGallerySdr[i] - sg_au32AccBasic[i]) * ((HI_S32)u32ACCLevel - 50) / 50);
                }
            }

            au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
        }
    }
    else
    {
        /* Hdr process use 1:1 */
        if ((HI_TRUE == sg_stPQACCInfo.bHdrProcessEn) || (PQ_SOURCE_MODE_UHD == enSourceMode))
        {
            for (i = 0; i < ACC_TABLE_LEVEL_MAX * ACC_TABLE_LEVEL_PARA; i++)
            {
                s32TmpTableDate = sg_au32AccBasic[i];
                au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
            }
        }
        else
        {
            for (i = 0; i < ACC_TABLE_LEVEL_MAX * ACC_TABLE_LEVEL_PARA; i++)
            {
                if ( u32ACCLevel < 50)
                {
                    s32TmpTableDate = sg_au32AccBasic[i] + (sg_au32AccUse[i] - sg_au32AccBasic[i]) * (HI_S32)u32ACCLevel / 50;
                }
                else
                {
                    s32TmpTableDate = (sg_au32AccUse[i] + (sg_au32AccUse[i] - sg_au32AccBasic[i]) * ((HI_S32)u32ACCLevel - 50) / 50);
                }

                au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
            }
        }
    }
#if defined(CHIP_TYPE_hi3798mv310)

    if (PQ_SOURCE_MODE_SD == enSourceMode)
    {
        for (i = 0; i < ACC_TABLE_LEVEL_PARA; i++)
        {
            au32AccTable[i] = CLIP3(sg_au32AccStreamId2_low[i], 0, 1023);
            au32AccTable[i + 1 * ACC_TABLE_LEVEL_PARA] = CLIP3(sg_au32AccStreamId2_mid[i], 0, 1023);
            au32AccTable[i + 2 * ACC_TABLE_LEVEL_PARA] = CLIP3(sg_au32AccStreamId1_1[i], 0, 1023);
        }
    }
#else
    if (HI_TRUE == sg_stPQACCInfo.u32StreamIdSetMode)
    {
        /* stream Id : 1 , high para */
        if (0x67 == sg_stPQACCInfo.u32StreamId)
        {
            for (i = 0; i < ACC_TABLE_LEVEL_PARA; i++)
            {
                s32TmpTableDate = sg_au32AccStreamId1[i];
                au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
                au32AccTable[i + 2 * ACC_TABLE_LEVEL_PARA] = CLIP3(sg_au32AccStreamId1_1[i], 0, 1023);
            }
        }
        /* stream Id : 2 , mid para*/
        if (0x68 == sg_stPQACCInfo.u32StreamId)
        {
            for (i = 0; i < ACC_TABLE_LEVEL_PARA; i++)
            {
                s32TmpTableDate = sg_au32AccStreamId2_low[i];
                au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
                au32AccTable[i + 1 * ACC_TABLE_LEVEL_PARA] = CLIP3(sg_au32AccStreamId2_mid[i], 0, 1023);
            }
        }
        if (0x69 == sg_stPQACCInfo.u32StreamId)
        {
            for (i = 0; i < ACC_TABLE_LEVEL_MAX * ACC_TABLE_LEVEL_PARA; i++)
            {
                s32TmpTableDate = sg_au32AccBasic[i];
                au32AccTable[i] = CLIP3(s32TmpTableDate, 0, 1023);
            }
        }
    }
#endif
    s32Ret = PQ_HAL_SetAccTab(PQ_HAL_LAYER_VID0,  au32AccTable);

    return s32Ret;
}

HI_S32 PQ_MNG_SetACCLut(PQ_ACC_LUT_S *pstACCLut)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCLut);
    PQ_CHECK_NULL_PTR_RE_FAIL(sg_pstPqParam);

    memcpy((HI_VOID *)(sg_pstPqParam->stPQCoef.stACCCoef.as32AccLut), (HI_VOID *)pstACCLut,
           sizeof(PQ_ACC_LUT_S));

    memcpy((HI_VOID *)sg_au32AccUse, (HI_VOID *)pstACCLut, sizeof(PQ_ACC_LUT_S));

    s32Ret = PQ_MNG_SetAccLevel(sg_stPQACCInfo.u32Strength);

    return s32Ret;
}

HI_S32 PQ_MNG_GetACCLut(PQ_ACC_LUT_S *pstACCLut)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCLut);
    PQ_CHECK_NULL_PTR_RE_FAIL(sg_pstPqParam);

    memcpy((HI_VOID *)pstACCLut, (HI_VOID *)sg_au32AccUse, sizeof(PQ_ACC_LUT_S));

    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_GetHdrAccCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqHdrCfg);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enDispType, HI_PQ_DISP_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enInCS, HI_DRV_CS_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enOutCS, HI_DRV_CS_BUTT);

    /* sdr->sdr : use hdr adjust para */
    if ((HI_DRV_VIDEO_FRAME_TYPE_SDR == pstXdrFrameInfo->enSrcFrameType)
        && (HI_PQ_DISP_TYPE_NORMAL == pstXdrFrameInfo->enDispType))
    {
        sg_stPQACCInfo.bHdrProcessEn = HI_FALSE;
        return HI_SUCCESS;
    }
    else
    {
        sg_stPQACCInfo.bHdrProcessEn = HI_TRUE;
    }

    return s32Ret;
}

HI_S32 PQ_MNG_SetACCStreamId(HI_U32 u32StreamId)
{
    sg_stPQACCInfo.u32StreamId  = u32StreamId; //special para

    PQ_MNG_SetAccLevel(sg_stPQACCInfo.u32Strength);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetACCStreamIdSetEnable(HI_U32 u32StreamIdSetMode)
{
    sg_stPQACCInfo.u32StreamIdSetMode = u32StreamIdSetMode;

    return HI_SUCCESS;
}

static stPQAlgFuncs stACCFuncs =
{
    .Init               = PQ_MNG_InitACC,
    .DeInit             = PQ_MNG_DeInitACC,
    .SetEnable          = PQ_MNG_SetACCEn,
    .GetEnable          = PQ_MNG_GetACCEn,
    .SetDemo            = PQ_MNG_SetACCDemoEn,
    .GetDemo            = PQ_MNG_GetACCDemoEn,
    .SetDemoMode        = PQ_MNG_SetACCDemoMode,
    .GetDemoMode        = PQ_MNG_GetACCDemoMode,
    .SetStrength        = PQ_MNG_SetAccLevel,
    .GetStrength        = PQ_MNG_GetAccLevel,
    .GetACCHistGram     = PQ_MNG_GetACCHistgram,
    .GetHdrCfg          = PQ_MNG_GetHdrAccCfg,
    .SetStreamId        = PQ_MNG_SetACCStreamId,
    .SetStreamSetON     = PQ_MNG_SetACCStreamIdSetEnable,
};

HI_S32 PQ_MNG_RegisterACC(PQ_REG_TYPE_E enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_DCI, enType, PQ_BIN_ADAPT_SINGLE, "acc", HI_NULL, &stACCFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterACC(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_DCI);

    return s32Ret;
}

