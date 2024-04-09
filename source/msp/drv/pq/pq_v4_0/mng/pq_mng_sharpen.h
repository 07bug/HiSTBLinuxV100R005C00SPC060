/******************************************************************************
 Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : pq_mng_sharpen.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2013/10/12
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_SHARPEN_H__
#define __PQ_MNG_SHARPEN_H__

#include "hi_type.h"
#include "pq_hal_sharpen.h"
#include "drv_pq_table.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct hiALG_SHARPEN_S
{
    HI_BOOL     bInit;
    HI_BOOL     bEnable;
    HI_U32      u32Strength;
    HI_BOOL     bDemoEnable;
    PQ_DEMO_MODE_E eDemoMode;
    HI_PQ_SHARP_RESO_S stSharpReso;
    HI_U32      u32StreamId;
    HI_U32      u32StreamIdSetMode;
    PQ_PARAM_S  *pstParam;
    HI_U32      (*pPeakGain)[PQ_OUTPUT_MODE_BUTT];
    HI_U32      (*pEdgeGain)[PQ_OUTPUT_MODE_BUTT];
} ALG_SHARPEN_S;

HI_S32 PQ_MNG_RegisterSharp(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterSharp(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

