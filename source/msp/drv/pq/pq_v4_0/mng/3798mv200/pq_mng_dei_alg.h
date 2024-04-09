/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_dei_alg.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016-03-02
  Description   : soft alg

******************************************************************************/
#ifndef __PQ_MNG_DEI_ALG_H__
#define __PQ_MNG_DEI_ALG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PQ_MCDI_SPLIT_WTH 384
#define PQ_MCDI_RGMV_WTH  64
#define DEI_CLIP3(low,high,x)  (MAX2(MIN2((high),(x)),(low)))
#define PQ_MCDI_ALIGN_8BIT_YSTRIDE(x)  HI_SYS_GET_STRIDE(x)

typedef struct
{
    HI_U32 u32GlobalMotion; /* TNR Motion Value */
    HI_U32 u32AdjustGain;   /* Global Motion Adjust Value */
} MOTION_RESULT_S;

typedef struct
{
    HI_S32 TH_H_GMDDIF_MC;
    HI_S32 TH_L_GMDDIF_MC;
    HI_S32 TH_MIN_GMDDIF_MC;

    HI_S32 TH_H_GMDDIF_MC_P;
    HI_S32 TH_L_GMDDIF_MC_P;

    /* SW Alg Config */
    HI_S32 TH_GMD_STAT;
    HI_S32 TH_GMD_STAT_P;
    HI_S32 TH_H_VMVSUM;
    HI_S32 TH_L_VMVSUM;
    HI_S32 TH_H_HMVSUM;
    HI_S32 TH_L_HMVSUM;
    HI_S32 TH_GMD_MA;

    /*SW get FrmIndex*/
    HI_S32 s32GlbFrmIndex[4];
} DeiSwAlgCfg_S;

typedef struct hiMVStruct
{
    /* �ӵ͵���˳�����У����3 bit������ */
    HI_S32 x;         /* [8:0] */
    HI_U32 sad;       /* [9:0] */
    HI_U32 mag;       /* [9:0] */
    HI_S32 vstillsad; /* [9:0] */
    HI_S32 mvy;       /* [7:0] */
    HI_U32 vsad;      /* [9:0] */
    HI_U32 ls;        /* [3:0] */

} MVStruct;

typedef enum hiMNG_PQ_MCDI_SPLIT_MODE_E
{
    HI_MNG_PQ_MCDI_SPLIT_MODE_0 = 0, /* Mcdi Split Mode */
    HI_MNG_PQ_MCDI_SPLIT_MODE_1 = 1, /* Mcdi Split Mode */
    HI_MNG_PQ_MCDI_SPLIT_MODE_2 = 2, /* Mcdi Split Mode */
    HI_MNG_PQ_MCDI_SPLIT_MODE_3 = 3, /* Mcdi Split Mode */
    HI_MNG_PQ_MCDI_SPLIT_MODE_4 = 4, /* Mcdi Split Mode */
    HI_MNG_PQ_MCDI_SPLIT_MODE_5 = 5, /* Mcdi Split Mode */

    HI_MNG_PQ_MCDI_SPLIT_MODE_BUTT
} HI_MNG_PQ_MCDI_SPLIT_MODE_E;

HI_S32  PQ_MNG_ALG_API_GMD(const HI_S32 *ps32Iglb2MtnNum, HI_S32 s32Width, HI_S32 s32Height, HI_S32 *ps32AdjK_STAT);
HI_S32  PQ_MNG_ALG_API_GMD_P(const HI_S32 *ps32Iglb1MtnNum,  HI_S32 s32Width, HI_S32 s32Height, HI_S32 *ps32AdjK_STAT);
HI_VOID PQ_MNG_ALG_RGMV_HVCHK( HI_S32 *ps32VmvSum, HI_S32 *ps32HmvSum, HI_VOID *pRGMV, \
                               HI_S32 s32Width, HI_S32 s32Height, HI_U32 stride, HI_MNG_PQ_MCDI_SPLIT_MODE_E enSplitMode);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

