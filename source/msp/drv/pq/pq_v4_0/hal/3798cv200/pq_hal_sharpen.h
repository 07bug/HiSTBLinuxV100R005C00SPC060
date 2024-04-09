/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_sharpen.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/10
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_SHARPEN_H__
#define __PQ_HAL_SHARPEN_H__

#include "hi_type.h"
#include "pq_hal_comm.h"
#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* Sharpen in v0 */
#define SHARP_EDGE_GAIN_ADDR      0x621c
#define SHARP_EDGE_GAIN_LSB       10
#define SHARP_EDGE_GAIN_MSB       19

#define SHARP_PEAK_GAIN_ADDR      0x621c
#define SHARP_PEAK_GAIN_LSB       0
#define SHARP_PEAK_GAIN_MSB       9

#define SHARP_SUPPORT_MAX_W          1920
#define SHARP_SUPPORT_MAX_H          1080
#define SHARP_ZME2_SCALE_UP_THD      2
#define SHARP_DHD1_OUT_1080P_W_THD   1920
#define SHARP_DHD1_OUT_1080P_H_THD   1080
#define SHARP_DHD1_OUT_4K_W_THD      3840
#define SHARP_DHD1_OUT_4K_H_THD      2160

typedef struct hiPQ_SHARP_GAIN_S
{
    HI_U32 u32PeakGain;
    HI_U32 u32EdgeGain;
} PQ_SHARP_GAIN_S;

typedef enum hi_SHARP_DEMO_MODE_E
{
    SHARP_DEMO_ENABLE_R = 0,
    SHARP_DEMO_ENABLE_L    ,

    SHARP_DEMO_BUTT
} SHARP_DEMO_MODE_E;


HI_S32  PQ_HAL_EnableSharp(HI_BOOL bOnOff);
HI_S32  PQ_HAL_SetSharpStrReg(HI_U32 u32Data, HI_U32 u32PeakGain, HI_U32 u32EdgeGain);
HI_S32  PQ_HAL_EnableSharpDemo(HI_U32 u32Data, HI_BOOL bOnOff);
HI_S32  PQ_HAL_SetSharpDemoMode(HI_U32 u32Data, HI_U32 u32SharpDemoMode);
HI_S32  PQ_HAL_SetSharpDemoPos(HI_U32 u32Data, HI_U32 u32Pos);
HI_S32  PQ_HAL_GetSharpDemoPos(HI_U32 u32Data, HI_U32 *pu32XPos);
HI_S32  PQ_HAL_SetSharpDetecEn(HI_U32 u32Data, HI_BOOL bOnOff);
HI_S32  PQ_HAL_SetSharpPeakGain(HI_U32 u32Data, HI_U32 u32PeakGain);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

