/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_hal_lchdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2018/01/12
  Description  :

******************************************************************************/

#ifndef _PQ_HAL_LCHDR_H_
#define _PQ_HAL_LCHDR_H_

#include "hi_type.h"
#include "drv_pq_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define TM_LUT_SIZE 64
#define SatM_LUT_SIZE 65

HI_S32 PQ_HAL_SetLCHDREn(HI_U32 u32HandleNo, HI_BOOL bEnable);

HI_S32 PQ_HAL_GetLCHDREn(HI_BOOL *pbEnable);

HI_S32 PQ_HAL_SetLCHDRDemoEn(HI_U32 u32HandleNo, HI_BOOL bEnable);

HI_S32 PQ_HAL_SetLCHDRDemoMode(HI_U32 u32HandleNo, PQ_DEMO_MODE_E enMode);

HI_S32 PQ_HAL_SetLCHDRDemoPos(HI_U32 u32HandleNo, HI_U32 u32XPos);

HI_S32 PQ_HAL_GetLCHDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstVpssReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
