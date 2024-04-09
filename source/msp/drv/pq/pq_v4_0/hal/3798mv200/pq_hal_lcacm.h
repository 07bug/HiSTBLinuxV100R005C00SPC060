/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_lcacm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/07/18
  Description   :

******************************************************************************/
#ifndef __PQ_HAL_LCACM_H__
#define __PQ_HAL_LCACM_H__

#include "hi_type.h"
#include "drv_pq_table.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    HI_U32 acm0_en;
    HI_U32 acm1_en;
    HI_U32 acm2_en;
    HI_U32 acm3_en;
    HI_U32 acm_dbg_mode;
    HI_U32 acm_test_en;
    HI_U32 bw_pro_mode;

} PQ_HAL_ACM_CFG_S;

typedef struct
{
    HI_S32 acm0_sec_blk;
    HI_S32 acm0_fir_blk;
    HI_S32 acm0_d_u_off;
    HI_S32 acm0_c_u_off;
    HI_S32 acm0_b_u_off;
    HI_S32 acm0_a_u_off;
    HI_S32 acm0_d_v_off;
    HI_S32 acm0_c_v_off;
    HI_S32 acm0_b_v_off;
    HI_S32 acm0_a_v_off;

    HI_S32 acm1_sec_blk;
    HI_S32 acm1_fir_blk;
    HI_S32 acm1_d_u_off;
    HI_S32 acm1_c_u_off;
    HI_S32 acm1_b_u_off;
    HI_S32 acm1_a_u_off;
    HI_S32 acm1_d_v_off;
    HI_S32 acm1_c_v_off;
    HI_S32 acm1_b_v_off;
    HI_S32 acm1_a_v_off;

    HI_S32 acm2_sec_blk;
    HI_S32 acm2_fir_blk;
    HI_S32 acm2_d_u_off;
    HI_S32 acm2_c_u_off;
    HI_S32 acm2_b_u_off;
    HI_S32 acm2_a_u_off;
    HI_S32 acm2_d_v_off;
    HI_S32 acm2_c_v_off;
    HI_S32 acm2_b_v_off;
    HI_S32 acm2_a_v_off;

    HI_S32 acm3_sec_blk;
    HI_S32 acm3_fir_blk;
    HI_S32 acm3_d_u_off;
    HI_S32 acm3_c_u_off;
    HI_S32 acm3_b_u_off;
    HI_S32 acm3_a_u_off;
    HI_S32 acm3_d_v_off;
    HI_S32 acm3_c_v_off;
    HI_S32 acm3_b_v_off;
    HI_S32 acm3_a_v_off;
} PQ_HAL_ACM_PARA_S;

/* ACM demo mode */
typedef enum hiHAL_ACM_DEMO_MODE_E
{
    HAL_ACM_DEMO_ENABLE_L = 0,
    HAL_ACM_DEMO_ENABLE_R    ,

    HAL_ACM_DEMO_BUTT
} HAL_ACM_DEMO_MODE_E;

HI_VOID PQ_HAL_SetACMDemoEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

HI_VOID PQ_HAL_SetACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HAL_ACM_DEMO_MODE_E enACMDemoMode);

HI_VOID PQ_HAL_SetACMEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

HI_VOID PQ_HAL_SetLCACMPara(HI_U32 enLayer, PQ_HAL_ACM_PARA_S *pstAcmPara);

HI_VOID PQ_HAL_SetAcmTestEn(HI_U32 u32Data, HI_U32 acm_test_en);

HI_VOID PQ_HAL_SetAcmDbgMode(HI_U32 u32Data, HI_U32 acm_dbg_mode);

HI_VOID PQ_HAL_SetAcmProtMode(HI_U32 u32Data, HI_U32 bw_pro_mode);

HI_S32 PQ_HAL_SetNormLcacmFleshToneCfg(HI_PQ_FLESHTONE_E enGainLevel);

HI_S32 PQ_HAL_SetNormLcacmCfg(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode);

HI_S32 PQ_HAL_GetHdrLcacmCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo);

HI_S32 PQ_HAL_InitLcacm(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault);

HI_S32 PQ_HAL_Tool_SetHdrAcmMode(HI_PQ_HDR_ACM_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_GetHdrAcmMode(HI_PQ_HDR_ACM_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_SetHdrAcmRegCfg(HI_PQ_HDR_ACM_REGCFG_S *pstCfg);

HI_S32 PQ_HAL_Tool_GetHdrAcmRegCfg(HI_PQ_HDR_ACM_REGCFG_S *pstCfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

