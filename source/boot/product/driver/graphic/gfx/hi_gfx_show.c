/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_show.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : show input data from base through vo or gfx layer
                     CNcomment: 通过图形层或者视频层将输入的数据显示出来 CNend\n
Function List      :
History            :
Date                           Author                     Modification
2018/01/01                     sdk                        Created file
************************************************************************************************/


/************************** add include here****************************************************/
#include "hi_gfx_show.h"
#include "hi_gfx_comm.h"

#include "hi_gfx_surface.h"
#include "hi_gfx_decode.h"
#include "hi_gfx_layer.h"
#include "hi_gfx_blit.h"

/************************** Macro Definition     ***********************************************/


/************************** Structure Definition ***********************************************/

/************************** Global Variable declaration ****************************************/
HI_U32 gfx_log_level = 0;

/************************** Api declaration ****************************************************/

extern HI_S32 HI_BOOT_GFX_DisplayWithLayerOrVo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_HANDLE DecSurface);


/************************** API realization ****************************************************/

static HI_VOID GFX_GetLogLevel(HI_VOID)
{
#ifndef HI_BUILD_IN_MINI_BOOT
    HI_CHAR *pString = NULL;
    if (NULL != (pString = getenv("gfx_log_level")))
    {
		gfx_log_level = (HI_U32)simple_strtoul(pString, NULL, 15);
    }
#if 0
    HI_GFX_Print("\n=============================================================\n");
    HI_GFX_Print("gfx_log_level = %d\n",gfx_log_level);
    HI_GFX_Print("=============================================================\n");
#endif
#endif
    return;
}

/***************************************************************************************
* func          : HI_GFX_ShowLogo
* description   :  display the input logo by graphic or vo
                   CNcomment: 通过图形层或者视屏层将输入的logo的数据显示处理CNend\n
* param[in]     : pInputBaseLogoInfo
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32  HI_GFX_ShowLogo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_HANDLE DecSurface = HI_GFX_INVALID_HANDLE;
     GFX_GetLogLevel();

     HI_GFX_UNF_FuncBeg();
     HI_GFX_UNF_FuncEnter();

     CHECK_POINT_NULL(pInputBaseLogoInfo);

     Ret = HI_GFX_DecImg(pInputBaseLogoInfo->LogoDataBuf,pInputBaseLogoInfo->LogoDataLen,&DecSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         HI_GFX_UNF_FuncEnd();
         return HI_FAILURE;
     }

     Ret = HI_BOOT_GFX_DisplayWithLayerOrVo(pInputBaseLogoInfo,DecSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         goto ERR_EXIT_ONE;
     }

     if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
         HI_GFX_FreeSurface(DecSurface);
     }

     HI_GFX_UNF_FuncExit();
     HI_GFX_UNF_FuncEnd();
     return HI_SUCCESS;

ERR_EXIT_ONE:

     if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
        HI_GFX_FreeSurface(DecSurface);
     }

     HI_GFX_UNF_FuncEnd();
     return HI_FAILURE;
}

/***************************************************************************************
* func          : HI_GFX_ShowAnimation
* description   : show animation
                  CNcomment: 显示开机动画, 动画显示需要双buffer，否则可能裂屏，
                             是否可以多分内存需要审视  CNend\n
* param[in]     : DataBuf    CNcomment: 保存图片数据buffer CNend\n
* param[in]     : DataLen    CNcomment: 图片数据大小       CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_ShowAnimation(HI_U32 DataBuf, HI_U32 DataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE DecSurface = HI_GFX_INVALID_HANDLE;
    HI_HANDLE LayerSurface = HI_GFX_INVALID_HANDLE;
    HI_GFX_BLTOPT_S BlitOpt = {0};
    GFX_GetLogLevel();

    HI_GFX_UNF_FuncBeg();
    HI_GFX_UNF_FuncEnter();

    Ret = HI_GFX_DecImg(DataBuf,DataLen,&DecSurface);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       HI_GFX_UNF_FuncEnd();
       return HI_FAILURE;
    }

    Ret = HI_GFX_GetLayerSurface(&LayerSurface);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       goto ERR_EXIT;
    }

    BlitOpt.EnableScale = HI_TRUE;
    Ret = HI_GFX_Blit(DecSurface, NULL, LayerSurface, NULL, &BlitOpt);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       goto ERR_EXIT;
    }

    Ret = HI_GFX_RefreshLayer(LayerSurface);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       goto ERR_EXIT;
    }

    if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
        HI_GFX_FreeSurface(DecSurface);
     }

     HI_GFX_UNF_FuncExit();
     HI_GFX_UNF_FuncEnd();
     return HI_SUCCESS;
ERR_EXIT:

     if (HI_GFX_INVALID_HANDLE != DecSurface)
     {
        HI_GFX_FreeSurface(DecSurface);
     }
     HI_GFX_LOG_PrintErrCode(HI_FAILURE);
     HI_GFX_UNF_FuncEnd();
     return HI_FAILURE;
}
