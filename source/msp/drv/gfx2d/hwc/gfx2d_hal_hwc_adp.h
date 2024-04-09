/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_hal_hwc_adp.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/

#ifndef _GFX2D_HAL_HWC_ADP_H_
#define _GFX2D_HWC_HWC_ADP_H_

/*********************************add include here*********************************************/

#include <linux/fs.h>

#include "hi_gfx2d_type.h"

/**********************************************************************************************/


/**********************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ***********************************************/

#define HWC_MAX_LAYERS 7


/*************************** Structure Definition *********************************************/
typedef struct tagHWC_CAPABILITY_S
{
    HI_U8 u8MaxLayerNum;        /*���֧����������*/
    HI_U8 u8MaxGLayerNum;       /*���ͼ�β����*/
    HI_U8 u8MaxVLayerNum;       /*�����Ƶ�����*/
    HI_U32 au32InputFmtBitmap[2];
    HI_U32 au32OutputFmtBitmap[2];
    HI_U32 u32MinStride;
    HI_U32 u32MaxStride;
    HI_U8 u8StrideAlign;
    HI_U32 u32MinWidth;
    HI_U32 u32MaxWidth;
    HI_U32 u32MinHeight;
    HI_U32 u32MaxHeight;
    HI_U32 u32MinVWidth;            /*��Ƶ����С���*/
    HI_U32 u32MinVHeight;           /*��Ƶ����С�߶�*/
    HI_U32 u32MaxHorizonZmeRatio;   /*ˮƽ�����С����*/
    HI_U32 u32MaxVerticalZmeRatio;  /*��ֱ�����С����*/
    HI_U8 u32CmpWidthAlign;         /*ѹ����ȶ���Ҫ��*/
    HI_U32 au32CmpFmtBitmap[2];     /*ѹ��֧�ֵĸ�ʽ*/
    HI_BOOL bGZmeSupport;           /*ͼ�β��Ƿ�֧������*/
    HI_BOOL bClipSupport;           /*�Ƿ�֧��clip*/
    HI_U8 u8ZmeLayerNum;
    HI_U8 u8ZmeAlign;
}HWC_CAPABILITY_S;


/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/

HI_VOID HWC_ADP_GetCapability(HWC_CAPABILITY_S *pstCapability);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_HWC_HWC_ADP_H_*/
