/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_gfxhdr.c
  Version       : Initial Draft
  Author        : sdk
  Created      : 2018/01/29
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "pq_mng_gfxhdr.h"
#include "pq_hal_comm.h"

static HI_BOOL sg_bGfxHdrInitFlag      = HI_FALSE;

HI_S32 PQ_MNG_InitGfxHdr(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == sg_bGfxHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqParam);

    s32Ret = PQ_HAL_InitGfxHdr(pstPqParam, bDefault);
    if (HI_SUCCESS != s32Ret)
    {
        sg_bGfxHdrInitFlag = HI_FALSE;

        return s32Ret;
    }

    sg_bGfxHdrInitFlag = HI_TRUE;

    return s32Ret;
}

HI_S32 PQ_MNG_DeInitGfxHdr(HI_VOID)
{
    if (HI_FALSE == sg_bGfxHdrInitFlag)
    {
        return HI_SUCCESS;
    }

    sg_bGfxHdrInitFlag   = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetGfxHdrCfg(HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqGfxHdrCfg);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstGfxHdrInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstGfxHdrInfo->enDispType, HI_PQ_DISP_TYPE_BUTT);

    s32Ret = PQ_HAL_GetGfxHdrCfg(pstGfxHdrInfo, pstPqGfxHdrCfg);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetGfxHdrCSCSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPicSetting);

    s32Ret = PQ_HAL_SetGfxHdrCscSetting(pstPicSetting);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetGfxHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    s32Ret = PQ_HAL_SetGfxHdrOffset(pstHdrOffsetPara);

    return s32Ret;
}

static HI_S32 PQ_MNG_SetGfxHdrTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    s32Ret = PQ_HAL_SetGfxHDRTMCurve(pstHdrOffsetPara);

    return s32Ret;
}

HI_S32 PQ_MNG_SetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstGfxHdrTmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrTmap);

    s32Ret = PQ_HAL_SetGfxHdrTmapByTool(pstGfxHdrTmap);

    return s32Ret;
}

HI_S32 PQ_MNG_GetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstGfxHdrTmap)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrTmap);

    s32Ret = PQ_HAL_GetGfxHdrTmapByTool(pstGfxHdrTmap);

    return s32Ret;
}

HI_S32 PQ_MNG_SetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstGfxHdrStep)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrStep);

    s32Ret = PQ_HAL_SetGfxHdrStepByTool(pstGfxHdrStep);

    return s32Ret;
}

HI_S32 PQ_MNG_GetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstGfxHdrStep)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrStep);

    s32Ret = PQ_HAL_GetGfxHdrStepByTool(pstGfxHdrStep);

    return s32Ret;
}

HI_S32 PQ_MNG_SetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    s32Ret = PQ_HAL_SetGfxHdrModeByTool(pstMode);

    return s32Ret;
}

HI_S32 PQ_MNG_GetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    s32Ret = PQ_HAL_GetGfxHdrModeByTool(pstMode);

    return s32Ret;
}

static stPQAlgFuncs stGfxHdrFuncs =
{
    .Init                  = PQ_MNG_InitGfxHdr,
    .DeInit                = PQ_MNG_DeInitGfxHdr,
    .GetGfxHdrCfg          = PQ_MNG_GetGfxHdrCfg,
    .SetHdrCSCVideoSetting = PQ_MNG_SetGfxHdrCSCSetting,
    .SetHdrOffset          = PQ_MNG_SetGfxHdrOffset,
    .SetHdrTMCurve         = PQ_MNG_SetGfxHdrTMCurve,
};

HI_S32 PQ_MNG_RegisterGfxHdr(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_GFXHDR, enType, PQ_BIN_ADAPT_SINGLE, "gfxhdr", HI_NULL, &stGfxHdrFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterGfxHdr(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_GFXHDR);

    return s32Ret;
}

