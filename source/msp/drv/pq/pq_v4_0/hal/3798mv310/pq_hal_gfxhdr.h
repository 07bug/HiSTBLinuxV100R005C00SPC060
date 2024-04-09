/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_gfxhdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2018/01/29
  Description  :

******************************************************************************/

#ifndef _PQ_HAL_GFXHDR_H_
#define _PQ_HAL_GFXHDR_H_

#include "hi_type.h"
#include "drv_pq_comm.h"
#include "pq_hal_gfxcsc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PQ_GFXHDR_MAX_LUMINANCE 1500
#define GFXHDR_MIN(x, y) (((x) > (y)) ? (y) : (x))
#define GFXHDR_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define GFXHDR_CLIP3(low,high,x)  (GFXHDR_MAX(GFXHDR_MIN((high),(x)),(low)))

typedef struct hiPQ_GFXHDR_TF_PARA
{
    HI_U32 *x_step;
    HI_U32 *x_pos;
    HI_U32 *x_num;
    HI_U32 *lut;
} PQ_GFXHDR_TF_PARA;

HI_S32 PQ_HAL_GetGfxHdrCfg(HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg);

HI_S32 PQ_HAL_SetGfxHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);

HI_S32 PQ_HAL_SetGfxHdrCscSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting);

HI_S32 PQ_HAL_SetGfxHDRTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);

HI_S32 PQ_HAL_InitGfxHdr(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault);

HI_S32 PQ_HAL_SetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstTmap);

HI_S32 PQ_HAL_GetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstTmap);

HI_S32 PQ_HAL_SetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode);

HI_S32 PQ_HAL_GetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode);

HI_S32 PQ_HAL_SetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstStep);

HI_S32 PQ_HAL_GetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstStep);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
