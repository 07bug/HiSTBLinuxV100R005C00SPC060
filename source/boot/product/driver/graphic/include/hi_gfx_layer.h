/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_layer.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : display through gfx layer or vo
                     CNcomment: 显示输出处理CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                    sdk                          Created file
************************************************************************************************/

#ifndef  __HI_GFX_LAYER_H__
#define  __HI_GFX_LAYER_H__


/*********************************add include here**********************************************/

#include "hi_type.h"
#include "hi_gfx_comm.h"

/***************************** Macro Definition ************************************************/

#define CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH     4096
#define CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH           3840
#define CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT          2160

/** 这个要和驱动保持一致，否则无法释放 **/
#define DISPLAY_BUFFER_HD           "HIFB_DispBuf_HD"
#define DISPLAY_BUFFER_SD           "HIFB_DispBuf_SD"
#define HI_GFX_LAYER_MAXCOUNT       6

/*************************** Structure Definition *********************************************/
typedef struct hiFbAlpha_S
{
    HI_BOOL bAlphaEnable;
    HI_BOOL bAlphaChannel;
    HI_U8 u8Alpha0;
    HI_U8 u8Alpha1;
    HI_U8 u8GlobalAlpha;
    HI_U8 u8Reserved;
}HI_FB_ALPHA_S;

typedef struct hiGfxDisplayInfo_S
{
    HI_U32 u32Stride;
    HI_U32 u32ScreenAddr;
    HI_RECT stInRect;
    HI_RECT stOutRect;
    HI_FB_ALPHA_S stAlpha;
}HI_GFX_DISPLAY_INFO_S;

/********************** Global Variable declaration ********************************************/


/******************************* API declaration ***********************************************/
/***************************************************************************************
* func          : HI_GFX_GetLayerSurface
* description   : get layer surface
                  CNcomment:获取layer surface, 要是有帧切换就要重新获取一次 CNend\n
* param[in]     : pSurface        CNcomment: layer surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_GetLayerSurface(HI_HANDLE *pSurface);

/***************************************************************************************
* func          : HI_GFX_RefreshLayer
* description   : refresh layer
                  CNcomment: 刷新显示 CNend\n
* param[in]     : hSurface        CNcomment: layer surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_RefreshLayer(HI_HANDLE hSurface);

#endif /*__HI_GFX_LAYER_H__ */
