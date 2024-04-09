/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_hdr.c
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/03/19
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "pq_mng_hdr.h"
#include "pq_hal_comm.h"
#include "pq_hal_hdr.h"

static HI_BOOL sg_bHdrInitFlag      = HI_FALSE;

HI_S32 PQ_MNG_InitHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == sg_bHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqParam);

    s32Ret = PQ_HAL_InitHDR(pstPqParam, bParaUseTableDefault);
    if (HI_SUCCESS != s32Ret)
    {
        sg_bHdrInitFlag = HI_FALSE;

        return s32Ret;
    }

    sg_bHdrInitFlag = HI_TRUE;

    return s32Ret;
}

HI_S32 PQ_MNG_DeInitHDR(HI_VOID)
{
    if (HI_FALSE == sg_bHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    sg_bHdrInitFlag   = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetHDRCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqHdrCfg);

    s32Ret = PQ_HAL_GetHDRCfg(pstXdrFrameInfo, pstPqHdrCfg);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    s32Ret = PQ_HAL_Tool_GetHDRParaMode(pstMode);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    s32Ret = PQ_HAL_Tool_SetHDRParaMode(pstMode);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_SetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrTmap);

    s32Ret = PQ_HAL_Tool_SetHdrTMap(pstHdrTmap);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_GetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrTmap);

    s32Ret = PQ_HAL_Tool_GetHdrTMap(pstHdrTmap);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_SetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrSmap);

    s32Ret = PQ_HAL_Tool_SetHdrSMap(pstHdrSmap);

    return s32Ret;
}

HI_S32 PQ_MNG_Tool_GetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrSmap);

    s32Ret = PQ_HAL_Tool_GetHdrSMap(pstHdrSmap);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetHDRTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    s32Ret = PQ_HAL_SetHDRTMCurve(pstHdrOffsetPara);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetHdrCSCSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPicSetting);

    s32Ret = PQ_HAL_SetHdrCscSetting(pstPicSetting);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    s32Ret = PQ_HAL_SetHdrOffset(pstHdrOffsetPara);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetHdrACCHistGram(HI_U32 u32ACCOutWidth, HI_U32 u32ACCOutHeight, HI_PQ_ACC_HISTGRAM_S *pstACCHistGram)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCHistGram);

    s32Ret = PQ_HAL_SetHDRACCHistGram(u32ACCOutWidth, u32ACCOutHeight, pstACCHistGram);

    return s32Ret;
}

static stPQAlgFuncs stHDRFuncs =
{
    .Init                  = PQ_MNG_InitHDR,
    .DeInit                = PQ_MNG_DeInitHDR,
    .GetHdrCfg             = PQ_MNG_GetHDRCfg,
    .SetHdrACCHistGram     = PQ_MNG_SetHdrACCHistGram,
    .SetHdrCSCVideoSetting = PQ_MNG_SetHdrCSCSetting,
    .SetHdrOffset          = PQ_MNG_SetHdrOffset,
    .SetHdrTMCurve         = PQ_MNG_SetHDRTMCurve,
};

HI_S32 PQ_MNG_RegisterHDR(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_HDR, enType, PQ_BIN_ADAPT_SINGLE, "hdr", HI_NULL, &stHDRFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterHDR(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_HDR);

    return s32Ret;
}

