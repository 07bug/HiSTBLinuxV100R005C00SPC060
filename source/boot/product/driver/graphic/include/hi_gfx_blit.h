/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_blit.h
Version            : Initial Draft
Author             :
Created            : 2017/09/01
Description        : display through gfx layer or vo
                     CNcomment: 2D加速CNend\n
Function List      :
History            :
Date                           Author                     Modification
2017/09/01                      sdk                        Created file
************************************************************************************************/

#ifndef  __HI_GFX_BLIT_H__
#define  __HI_GFX_BLIT_H__


/*********************************add include here**********************************************/

#include "hi_type.h"

/***************************** Macro Definition ************************************************/


/*************************** Structure Definition **********************************************/
typedef struct hiGFXBLTOPT_S
{
   HI_BOOL EnableScale;
}HI_GFX_BLTOPT_S;

typedef enum hiGFXCOMPOPT_E
{
    HI_GFX_COMPOPT_NONE = 0,
    HI_GFX_COMPOPT_BUTT
}HI_GFX_COMPOPT_E;
/********************** Global Variable declaration ********************************************/


/******************************* API declaration ***********************************************/

/*****************************************************************************
* func         : HI_GFX_FillRect
* description  : 填充矩形
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_S32 HI_GFX_FillRect(HI_HANDLE hSurface, const HI_RECT* pstRect, HI_U32 u32Color, HI_GFX_COMPOPT_E eComPopt);

/***************************************************************************************
* func          : HI_GFX_Blit
* description   : blit src surface to dst surface
                  CNcomment: 将源surface数据搬移到目标surface上CNend\n
* param[in]     : hSrcSurface        CNcomment:源surface    CNend\n
* param[in]     : pSrcRect           CNcomment:源矩形大小   CNend\n
* param[in]     : hDstSurface        CNcomment:目标surface  CNend\n
* param[in]     : pDstRect           CNcomment:目标矩形大小 CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_Blit(HI_HANDLE hSrcSurface, HI_RECT* pSrcRect, HI_HANDLE hDstSurface, HI_RECT* pDstRect, const HI_GFX_BLTOPT_S* pBlitOpt);


#endif /*__HI_GFX_BLIT_H__ */
