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
                  �������
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
                  CNcomment: ���òü����� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : PosX   CNcomment:    X����    CNend\n
 * param[in]    : PosY   CNcomment:    Y����     CNend\n
 * param[in]    : Width  CNcomment:    ���      CNend\n
 * param[in]    : Height CNcomment:    �߶�      CNend\n
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
                  CNcomment: ���ý������x����Ϳ�� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : Crop_X      CNcomment:    X����      CNend\n
 * param[in]    : Crop_Width  CNcomment:    ���       CNend\n
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
                  CNcomment: ���ý������y����͸߶� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : Crop_Y      CNcomment:    Y����      CNend\n
 * param[in]    : Crop_H      CNcomment:    �߶�       CNend\n
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
    /**<-- �������������룬����Ҫ���òü����� >**/
    if (HI_TRUE != pJpegHandle->bCrop)
    {
       return HI_SUCCESS;
    }

    /**<-- if decode to user buffer, but not set crop rect, not support >**/
    /**<-- ���û����������ʹ�ý���������û�buffer ��֧�֣���Ϊ�û��ڴ治���� >**/
    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_FALSE == pJpegHandle->bSetCropRect))
    {
       return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->bSetCropRect)
    {
       return HI_SUCCESS;
    }

    /**<-- if has been set crop_y, should not set again,  call HI_JPEG_SetCropRect for example >**/
    /**<-- ��������������С�Ͳ���Ҫ������������ >**/
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
                  CNcomment: ���ö��˶����� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : SkipLines   CNcomment:    ��������   CNend\n
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
                  CNcomment: ��ȡ���˶����� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : SkipLines   CNcomment:    ��ȡ��������   CNend\n
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
                  CNcomment: ���ö��б��  CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : bDiscardScanlines   CNcomment:���   CNend\n
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
