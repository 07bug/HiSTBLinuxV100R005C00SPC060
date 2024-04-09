/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_hdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/06/15
  Description  :

******************************************************************************/

#ifndef _PQ_HAL_HDR_H_
#define _PQ_HAL_HDR_H_

#include "hi_type.h"
#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* sdr2hdr */
#define PQ_MAX_LUMINANCE 1600

typedef struct hiPQ_HDR_TF_PARA
{
    HI_U32 *x_step;
    HI_U32 *x_pos;
    HI_U32 *x_num;
    HI_U32 *lut;
} PQ_HDR_TF_PARA;

HI_S32 PQ_HAL_GetHDRCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);

HI_S32 PQ_HAL_InitHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault);

HI_S32 PQ_HAL_Tool_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_SetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap);

HI_S32 PQ_HAL_Tool_GetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap);

HI_S32 PQ_HAL_Tool_SetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap);

HI_S32 PQ_HAL_Tool_GetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap);

HI_S32 PQ_HAL_SetHDRACCHistGram(HI_U32 u32ACCOutWidth, HI_U32 u32ACCOutHeight, HI_PQ_ACC_HISTGRAM_S *pstACCHistGram);

HI_S32 PQ_HAL_SetHDRTMCurve(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);

HI_S32 PQ_HAL_SetHdrOffset(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara);

HI_S32 PQ_HAL_SetHdrCscSetting(HI_PQ_PICTURE_SETTING_S *pstPicSetting);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
