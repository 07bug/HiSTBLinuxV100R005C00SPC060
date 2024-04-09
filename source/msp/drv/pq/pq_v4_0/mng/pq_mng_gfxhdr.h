/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_gfxhdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2018/01/29
  Description  :

******************************************************************************/


#ifndef __PQ_MNG_GFXHDR_H__
#define __PQ_MNG_GFXHDR_H__

#include "drv_pq_comm.h"
#include "pq_hal_gfxhdr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32 PQ_MNG_SetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstGfxHdrTmap);

HI_S32 PQ_MNG_GetGfxHdrTmapByTool(HI_PQ_GFXHDR_TMAP_S *pstGfxHdrTmap);

HI_S32 PQ_MNG_SetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode);

HI_S32 PQ_MNG_GetGfxHdrModeByTool(HI_PQ_GFXHDR_MODE_S *pstMode);

HI_S32 PQ_MNG_SetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstGfxHdrStep);

HI_S32 PQ_MNG_GetGfxHdrStepByTool(HI_PQ_GFXHDR_STEP_S *pstGfxHdrStep);

HI_S32 PQ_MNG_RegisterGfxHdr(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterGfxHdr(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


