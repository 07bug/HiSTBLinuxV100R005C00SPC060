/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : jpeg_hdec_subtile.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     : sub tile decode
                  区域解码
Function List   :

History         :
Date                    Author                    Modification
2018/01/01              sdk                        Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/

/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
/*****************************************************************************
 * func         : JPEG_DEC_SetCropRect
 * description  : set crop rect
                  CNcomment: 设置裁剪区域 CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : PosX   CNcomment:    X坐标    CNend\n
 * param[in]    : PosY   CNcomment:    Y坐标     CNend\n
 * param[in]    : Width  CNcomment:    宽度      CNend\n
 * param[in]    : Height CNcomment:    高度      CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetCropRect(HI_ULONG HdecHandle,HI_U32 PosX, HI_U32 PosY, HI_U32 Width,HI_U32 Height)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    pJpegHandle->bCrop = HI_TRUE;
    pJpegHandle->stOutSurface.stCropRect.x = PosX;
    pJpegHandle->stOutSurface.stCropRect.y = PosY;
    pJpegHandle->stOutSurface.stCropRect.w = Width;
    pJpegHandle->stOutSurface.stCropRect.h = Height;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetCropXW
 * description  : set crop x and width
                  CNcomment: 设置解码输出x坐标和宽度 CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : Crop_X      CNcomment:    X坐标      CNend\n
 * param[in]    : Crop_Width  CNcomment:    宽度       CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetCropXW(HI_ULONG HdecHandle,HI_U32 Crop_X, HI_U32 Crop_Width)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    pJpegHandle->bCrop = HI_TRUE;
    pJpegHandle->stOutSurface.stCropRect.x = Crop_X;
    pJpegHandle->stOutSurface.stCropRect.w = Crop_Width;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetCropYH
 * description  : set crop y and height
                  CNcomment: 设置解码输出y坐标和高度 CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : Crop_Y      CNcomment:    Y坐标      CNend\n
 * param[in]    : Crop_H      CNcomment:    高度       CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
 HI_S32 JPEG_DEC_SetCropYH(HI_ULONG HdecHandle, HI_U32 Crop_Y, HI_U32 Crop_H)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (HI_TRUE != pJpegHandle->SupportHardDec)
    {
       return HI_SUCCESS;
    }

    /**<-- if not support crop, should not set crop_rect >**/
    /**<-- 如果不是区域解码，不需要设置裁剪区域 >**/
    if (HI_TRUE != pJpegHandle->bCrop)
    {
       return HI_SUCCESS;
    }

    /**<-- if decode to user buffer, but not set crop rect, not support >**/
    /**<-- 如果没有设置区域使用解码输出到用户buffer 不支持，因为用户内存不够用 >**/
    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_FALSE == pJpegHandle->bSetCropRect))
    {
       return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->bSetCropRect)
    {
       return HI_SUCCESS;
    }

    /**<-- if has been set crop_y, should not set again,  call HI_JPEG_SetCropRect for example >**/
    /**<-- 如果设置了区域大小就不需要重新再设置了 >**/
    if (0 == pJpegHandle->stOutSurface.stCropRect.y)
    {
        pJpegHandle->stOutSurface.stCropRect.y = Crop_Y;
    }

    if (0 == pJpegHandle->stOutSurface.stCropRect.h)
    {
        pJpegHandle->stOutSurface.stCropRect.h = Crop_H;
    }

    pJpegHandle->bSetCropRect = HI_TRUE;

    return HI_SUCCESS;
}


/*****************************************************************************
 * func         : JPEG_DEC_SetSkipLines
 * description  : set skip lines
                  CNcomment: 设置丢了多少行 CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : SkipLines   CNcomment:    丢的行数   CNend\n
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_S32  JPEG_DEC_SetSkipLines(HI_ULONG HdecHandle, HI_U32 SkipLines)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_FALSE == pJpegHandle->bCrop))
    {/**<-- hard decode support skip decode >**/
       return HI_FAILURE;
    }

    pJpegHandle->SkipLines += SkipLines;

    return HI_SUCCESS;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetSkipLines
 * description  : get skip lines
                  CNcomment: 获取丢了多少行 CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : SkipLines   CNcomment:    获取丢的行数   CNend\n
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetSkipLines(HI_ULONG HdecHandle, HI_U32 *SkipLines)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (NULL != SkipLines)
    {
       *SkipLines = pJpegHandle->SkipLines;
    }

    return;
}


HI_BOOL JPEG_DEC_SupportCrop(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FALSE;
    }

    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
       return HI_FALSE;
    }

    return HI_TRUE;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetDisScanMark
 * description  : set skip mark
                  CNcomment: 设置丢行标记  CNend\n
 * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
 * param[in]    : bDiscardScanlines   CNcomment:标记   CNend\n
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetDisScanMark(HI_ULONG HdecHandle, HI_BOOL bDiscardScanlines)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    pJpegHandle->bDiscardScanlines = bDiscardScanlines;

    return;
}
