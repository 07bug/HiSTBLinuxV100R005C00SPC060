/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_gfxcsc.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/10/10
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_GFXCSC_H__
#define __PQ_HAL_GFXCSC_H__

#include "hi_type.h"

#define CscPre           1 << 10
#define PQ_GFX_TABLE_MAX 61

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct
{
    HI_U32 CscCoefPre;      /* Csc 系数精度 */
    HI_U32 CscInDcCoefPre;  /* Csc 直流分量精度 */
    HI_U32 CscOutDcCoefPre; /* Csc 直流分量精度 */

} PQ_GFX_CSC_PRE_S;


/* GRAPH CSC LAYER */
typedef enum hiHAL_GFX_LAYER_E
{
    HAL_GFX_GP0 = 0  , /* HD */
    HAL_GFX_GP1      , /* SD */
    HAL_GFX_WBC_GP   ,

    HAL_GFX_LAYER_BUTT
} HAL_GFX_LAYER_E;

typedef enum PQ_HAL_GFX_COLOR_SPACE_E
{
    PQ_HAL_GFX_CS_UNKNOWN = 0,

    PQ_HAL_GFX_CS_BT601_YUV_LIMITED,  /* BT.601 */
    PQ_HAL_GFX_CS_BT601_YUV_FULL,
    PQ_HAL_GFX_CS_BT601_RGB_LIMITED,
    PQ_HAL_GFX_CS_BT601_RGB_FULL,

    PQ_HAL_GFX_CS_BT709_YUV_LIMITED,  /* BT.709 */
    PQ_HAL_GFX_CS_BT709_YUV_FULL,
    PQ_HAL_GFX_CS_BT709_RGB_LIMITED,
    PQ_HAL_GFX_CS_BT709_RGB_FULL,

    PQ_HAL_GFX_CS_BT2020_YUV_LIMITED, /* BT.2020 */
    PQ_HAL_GFX_CS_BT2020_RGB_FULL,

    PQ_HAL_GFX_CS_BUTT
} PQ_HAL_GFX_COLOR_SPACE_E;

typedef struct PQ_HAL_GFX_CSC_MODE_S
{
    PQ_HAL_GFX_COLOR_SPACE_E eInputCS;  /* input  color space type, should be set carefully according to the application situation. */
    PQ_HAL_GFX_COLOR_SPACE_E eOutputCS; /* output color space type, should be set carefully according to the application situation. */

} PQ_HAL_GFX_CSC_MODE_S;

/* CSC matrix coefficient */
typedef struct
{
    HI_S32 csc_coef00;   /* member 00 of 3*3 matrix */
    HI_S32 csc_coef01;   /* member 01 of 3*3 matrix */
    HI_S32 csc_coef02;   /* member 02 of 3*3 matrix */

    HI_S32 csc_coef10;   /* member 10 of 3*3 matrix */
    HI_S32 csc_coef11;   /* member 11 of 3*3 matrix */
    HI_S32 csc_coef12;   /* member 12 of 3*3 matrix */

    HI_S32 csc_coef20;   /* member 20 of 3*3 matrix */
    HI_S32 csc_coef21;   /* member 21 of 3*3 matrix */
    HI_S32 csc_coef22;   /* member 22 of 3*3 matrix */

} PQ_GFX_CSC_COEF_S;

/* CSC DC component */
typedef struct
{
    HI_S32 csc_in_dc0;    /* input color space DC value of component 0; */
    HI_S32 csc_in_dc1;    /* input color space DC value of component 1; */
    HI_S32 csc_in_dc2;    /* input color space DC value of component 2; */

    HI_S32 csc_out_dc0;   /* output color space DC value of component 0; */
    HI_S32 csc_out_dc1;   /* output color space DC value of component 1; */
    HI_S32 csc_out_dc2;   /* output color space DC value of component 2; */

} PQ_GFX_CSC_DCCOEF_S;


/* CSC 参数结构 */
typedef struct hiPQ_GFX_CSC_TUNING_S
{
    HI_U32  u32Bright;      /* bright adjust value,range[0,100],default setting 50; */
    HI_U32  u32Contrst;     /* contrast adjust value,range[0,100],default setting 50; */
    HI_U32  u32Hue;         /* hue adjust value,range[0,100],default setting 50; */
    HI_U32  u32Satur;       /* saturation adjust value,range[0,100],default setting 50; */
    HI_U32  u32Kr;          /* red   component gain adjust value for color temperature adjust,range[0,100],default setting 50; */
    HI_U32  u32Kg;          /* green component gain adjust value for color temperature adjust,range[0,100],default setting 50; */
    HI_U32  u32Kb;          /* blue  component gain adjust value for color temperature adjust,range[0,100],default setting 50; */

} PQ_GFX_CSC_TUNING_S;

HI_S32 PQ_HAL_SetGfxGdmCsc(HI_U32 enLayer, HI_BOOL bCSCEn, PQ_GFX_CSC_COEF_S *pstCscCoef, PQ_GFX_CSC_DCCOEF_S *pstCscDcCoef);

HI_S32 PQ_HAL_SetGfxCsc(HI_U32 enLayer, HI_BOOL bCSCEn, PQ_GFX_CSC_COEF_S *pstCscCoef, PQ_GFX_CSC_DCCOEF_S *pstCscDcCoef);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
