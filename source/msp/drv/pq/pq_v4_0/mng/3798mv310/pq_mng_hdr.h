/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_hdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/03/19
  Description  :

******************************************************************************/


#ifndef __PQ_MNG_HDR_H__
#define __PQ_MNG_HDR_H__

#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32 PQ_MNG_RegisterHDR(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterHDR(HI_VOID);

HI_S32 PQ_MNG_Tool_SetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap);

HI_S32 PQ_MNG_Tool_GetHdrTMap(HI_PQ_HDR_TMAP_S *pstHdrTmap);

HI_S32 PQ_MNG_Tool_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pParaMode);

HI_S32 PQ_MNG_Tool_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pParaMode);

HI_S32 PQ_MNG_Tool_SetHdrDynCfg(HI_PQ_HDR_DYN_TM_TUNING_S *pstMode);

HI_S32 PQ_MNG_Tool_GetHdrDynCfg(HI_PQ_HDR_DYN_TM_TUNING_S *pstMode);

HI_S32 PQ_MNG_Tool_SetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap);

HI_S32 PQ_MNG_Tool_GetHdrSMap(HI_PQ_HDR_SMAP_S *pstHdrSmap);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


