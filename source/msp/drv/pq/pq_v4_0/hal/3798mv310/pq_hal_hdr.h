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

/* DYN_TM */
#define HIST_BIN_NUM_BIT    6       // eg: 2^6 = 64 bins;
#define HIST_BIN_NUM        64      // eg: 2^6 = 64 bins;
#define HIST_BIN_NUM_LTD    56      // Limited Range Y
#define HIST_BIN_WIDTH      16
#define HIST_BIN_LTD_IDX    4

#define ALPHA_SCALE2P       10
#define DYN_TM_COEF_SCALE2P 8
#define FNL_TM_COEF_SCALE2P 8
#define HDR_TM_LUT_SIZE     64
#define HDR_TM_LUT_SEG      8
#define UHD_PIX_NUM         8294400 //3840*2160
#define LUMI_BIT            21


#define UI_u32MaxLumiDisplay    3000000
#define UI_u32DarkDetailGain    950
#define UI_u32DarkDetailGmm     3072
#define UI_u32BrightDetailGain  1024
#define UI_u32BrightDetailGmm   2048
#define UI_u32DynTmGain         1024
#define UI_u32DynTmGmm          1024
#define UI_u32DarkSceneDynTM    0
#define UI_u32DarkLimit         32768
#define UI_u32BleachingLevel    30
#define UI_u32TemporalSmooth    500

#define UI_u32BrightDetailPro 50
#define UI_u32DarkDetailPro   50

typedef struct hiPQ_HDR_TF_PARA
{
    HI_U32 *x_step;
    HI_U32 *x_pos;
    HI_U32 *x_num;
    HI_U32 *lut;
} PQ_HDR_TF_PARA;

typedef struct HiPP_HDR_DYN_TM_FRM_SIZE
{
    HI_U32   u32Width;
    HI_U32   u32Height;
    HI_U32   u32BitDep;
} HiPP_HDR_DYN_TM_FRM_SIZE;

typedef struct HiPP_HDR_DYN_ACC_DETAIL
{
    // 安卓菜单调节功能，替换ACC亮/暗细节保护系数
    HI_U32 u32BrightDetailPro;      //[0,2048]~[0,2.0]
    HI_U32 u32DarkDetailPro;        //[0,2048]~[0,2.0]
} HiPP_HDR_DYN_ACC_DETAIL;

typedef struct
{
    HI_U32 au32StepTM[8];
    HI_U32 au32PosTM[8];
    HI_U32 au32NumTM[8];       //num 改为累加段数
    HI_U32 pu32LUTTM[HDR_TM_LUT_SIZE];         //查找表
} HiPP_HDR_TM_PARA;

typedef struct HiPP_HDR_DYN_TM
{
    /********** ToneMapping **********/
    HI_U16 u16TmScaleCoef ;             // U4.0  [1,13]
    HiPP_HDR_TM_PARA stTM;
} HiPP_HDR_DYN_TM;

HI_S32 PQ_HAL_GetHDRCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg);

HI_S32 PQ_HAL_InitHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault);

HI_S32 PQ_HAL_Tool_SetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_GetHDRParaMode(HI_PQ_HDR_PARA_MODE_S *pstMode);

HI_S32 PQ_HAL_Tool_SetHdrDynCfg(HI_PQ_HDR_DYN_TM_TUNING_S *pstMode);

HI_S32 PQ_HAL_Tool_GetHdrDynCfg(HI_PQ_HDR_DYN_TM_TUNING_S *pstMode);

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
