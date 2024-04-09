/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : hi_jpeg_api.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : The user will use this api to realize some function
Function List    :


History           :
Date                      Author                    Modification
2018/01/01                sdk                        Created file
************************************************************************************************/


/****************************  add include here     ********************************************/
#ifdef HI_BUILD_IN_BOOT
  #include "hi_gfx_sys.h"
  #ifndef HI_BUILD_IN_MINI_BOOT
     #include <linux/string.h>
  #else
     #include "string.h"
  #endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include "hi_jpeg_api.h"
#include "jpeg_hdec_parse.c"
/***************************** Macro Definition     ********************************************/

/***************************** Structure Definition ********************************************/

/********************** Global Variable declaration ********************************************/

/********************** API forward declarations    ********************************************/


/**********************       API realization       ********************************************/
HI_S32 HI_JPEG_SetLowDelayInf(HI_ULONG DecHandle, HI_U32 PhyLineBuf, HI_CHAR* pVirLineBuf)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if ((NULL == pVirLineBuf) || (0 == PhyLineBuf))
    {
        pJpegHandle->bLowDelayEn   = HI_FALSE;
        pJpegHandle->u32PhyLineBuf = 0;
        pJpegHandle->pVirLineBuf   = NULL;
        return HI_FAILURE;
    }

    pJpegHandle->bLowDelayEn   = HI_TRUE;
    pJpegHandle->u32PhyLineBuf = PhyLineBuf;
    pJpegHandle->pVirLineBuf   = pVirLineBuf;

    return HI_SUCCESS;
}

HI_S32 HI_JPEG_SetOutInfo(HI_ULONG DecHandle, HI_JPEG_OUT_INFO_S *pstOutInfo)
{
    JPEG_IMG_INFO_S stImgInfo;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if (NULL == pstOutInfo)
    {
       return HI_FAILURE;
    }

    HI_GFX_Memset(&stImgInfo, 0x0, sizeof(stImgInfo));

    HI_GFX_Memcpy(&stImgInfo, &(pJpegHandle->stImgInfo), sizeof(JPEG_IMG_INFO_S));

    if (HI_JPEG_FMT_BUTT != stImgInfo.output_color_space)
    {/** if has been set at jpeg_sdec_outinfo.c**/
       return HI_SUCCESS;
    }

    stImgInfo.output_color_space = pstOutInfo->OutFmt;

    switch (pstOutInfo->OutFmt)
    {
        case HI_JPEG_FMT_RGBA_8888:
        case HI_JPEG_FMT_BGRA_8888:
        case HI_JPEG_FMT_ABGR_8888:
        case HI_JPEG_FMT_ARGB_8888:
            stImgInfo.out_color_components = 4;
            stImgInfo.output_components = 4;
            break;

        case HI_JPEG_FMT_BGRA_5551:
        case HI_JPEG_FMT_RGBA_5551:
        case HI_JPEG_FMT_ARGB_1555:
        case HI_JPEG_FMT_ABGR_1555:
            stImgInfo.out_color_components = 2;
            stImgInfo.output_components = 2;
            break;

        case HI_JPEG_FMT_BGR_888:
        case HI_JPEG_FMT_RGB_888:
            stImgInfo.out_color_components = 3;
            stImgInfo.output_components = 3;
            break;

        case HI_JPEG_FMT_RGB_565:
        case HI_JPEG_FMT_BGR_565:
            stImgInfo.out_color_components = 3;
            stImgInfo.output_components = 2;
            break;

         case HI_JPEG_FMT_YCbCr:
         case HI_JPEG_FMT_CrCbY:
         case HI_JPEG_FMT_YUV400:
         case HI_JPEG_FMT_YUV420:
         case HI_JPEG_FMT_YUV422_12:
         case HI_JPEG_FMT_YUV422_21:
         case HI_JPEG_FMT_YUV444:
            stImgInfo.out_color_components = 3;
            stImgInfo.output_components = 3;
            break;
        default:
            stImgInfo.out_color_components = 1;
            stImgInfo.output_components = 1;
            break;
    }

    if ((1 != pstOutInfo->scale_num) || (pstOutInfo->scale_denom > 8))
    {
        return HI_FAILURE;
    }

    stImgInfo.scale_num   = pstOutInfo->scale_num;
    stImgInfo.scale_denom = pstOutInfo->scale_denom;

    HI_GFX_Memcpy(&(pJpegHandle->stImgInfo), &stImgInfo, sizeof(JPEG_IMG_INFO_S));

    if ((HI_JPEG_FMT_YUV420 == stImgInfo.output_color_space) && (HI_JPEG_FMT_YUV420 != stImgInfo.jpeg_color_space))
    {
        pJpegHandle->bOutYUV420SP = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32  HI_JPEG_GetJpegInfo(HI_ULONG DecHandle, HI_JPEG_INFO_S *pJpegInfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if (NULL == pJpegInfo)
    {
       return HI_FAILURE;
    }

    if (HI_FALSE == pJpegInfo->bOutInfo)
    {
        pJpegInfo->u32Width[0]  = pJpegHandle->stImgInfo.image_width;
        pJpegInfo->u32Height[0] = pJpegHandle->stImgInfo.image_height;
        pJpegInfo->enFmt = pJpegHandle->stImgInfo.jpeg_color_space;
        return HI_SUCCESS;
    }

    JPEG_HDEC_GetImagInfo(DecHandle);

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
       case HI_JPEG_FMT_YUV400:
       case HI_JPEG_FMT_YUV444:
       case HI_JPEG_FMT_YUV422_12:
       case HI_JPEG_FMT_YUV422_21:
       case HI_JPEG_FMT_YUV420:
           pJpegInfo->u32Width[0]     = pJpegHandle->stJpegSofInfo.u32YWidth;
           pJpegInfo->u32Width[1]     = pJpegHandle->stJpegSofInfo.u32CWidth;
           pJpegInfo->u32Height[0]    = pJpegHandle->stJpegSofInfo.u32YHeight;
           pJpegInfo->u32Height[1]    = pJpegHandle->stJpegSofInfo.u32CHeight;
           pJpegInfo->u32McuHeight[0] = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
           pJpegInfo->u32McuHeight[1] = pJpegHandle->stJpegSofInfo.u32CMcuHeight;
           pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32YStride;
           pJpegInfo->u32OutStride[1] = pJpegHandle->stJpegSofInfo.u32CbCrStride;
           pJpegInfo->u32OutSize[0]   = pJpegHandle->stJpegSofInfo.u32YSize;
           pJpegInfo->u32OutSize[1]   = pJpegHandle->stJpegSofInfo.u32CSize;
           break;
        default:
           pJpegInfo->u32Width[0]     = pJpegHandle->stImgInfo.output_width;
           pJpegInfo->u32Height[0]    = pJpegHandle->stImgInfo.output_height;
           pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.DecOutStride;
           pJpegInfo->u32OutSize[0]   = pJpegInfo->u32OutStride[0] * pJpegInfo->u32Height[0];
           break;
    }

    /**<--used by decode >**/
    /**<--  暂时做为解码分辨率用>**/
    pJpegInfo->u32Width[2]     = pJpegHandle->stJpegSofInfo.DecOutWidth;
    pJpegInfo->u32Height[2]    = pJpegHandle->stJpegSofInfo.DecOutHeight;
    pJpegInfo->u32OutStride[2] = pJpegHandle->stJpegSofInfo.DecOutStride;
    pJpegInfo->u32OutSize[2]   = pJpegInfo->u32OutStride[2] * pJpegInfo->u32Height[2];

    return HI_SUCCESS;
}

HI_VOID HI_JPEG_StopDec(HI_ULONG DecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    pJpegHandle->EnStopDecode = HI_TRUE;

    return;
}

HI_S32 HI_JPEG_SetStreamBufInfo(HI_ULONG DecHandle,
                                HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,
                                HI_CHAR* pFirstStreamVirBuf,HI_U32 FirstStreamBufSize,
                                HI_CHAR* pSecondStreamVirBuf,HI_U32 SecondStreamBufSize)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if ((0 == StreamPhyAddr) || (NULL == pFirstStreamVirBuf))
    {
       return HI_FAILURE;
    }

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf   = StreamPhyAddr;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize = TotalStremBufSize;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf = HI_TRUE;

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf = pFirstStreamVirBuf;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize     = FirstStreamBufSize;

    if (0 == SecondStreamBufSize)
    {
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_FALSE;
       return HI_SUCCESS;
    }

    /**<--the stream save with two buffer, should set as follows paras >**/
    /**<-- 为了提高buffer 利用率，使用buffer 池，码流存放在两块buffer 中，即支持内存回绕处理>**/
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_TRUE;

    if (NULL == pSecondStreamVirBuf)
    {
       return HI_FAILURE;
    }

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf = pSecondStreamVirBuf;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize = SecondStreamBufSize;

    /**<--default read first data buffer>**/
    /**<--默认先读取第一块码流数据>**/
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf = HI_FALSE;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize = 0;

    return HI_SUCCESS;
}

HI_S32 HI_JPEG_SetOutDesc(HI_ULONG DecHandle, const HI_JPEG_SURFACE_S *pstSurfaceDesc)
{
    HI_S32 Cnt = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if (NULL == pstSurfaceDesc)
    {
       return HI_FAILURE;
    }

    if ((HI_JPEG_FMT_YUV400 != pJpegHandle->stImgInfo.output_color_space) && (HI_TRUE == pJpegHandle->bOutYCbCrSP))
    {
        if ((0 == pstSurfaceDesc->u32OutPhy[1]) || (0 == pstSurfaceDesc->u32OutStride[1]))
        {
            return HI_FAILURE;
        }
    }

    pJpegHandle->bOutUsrBuf = HI_TRUE;

    for (Cnt = 0; Cnt < HI_JPEG_MAX_COMPONENT_NUM; Cnt++)
    {
        pJpegHandle->stOutSurface.BufPhy[Cnt] = pstSurfaceDesc->u32OutPhy[Cnt];
        pJpegHandle->stOutSurface.BufVir[Cnt] = pstSurfaceDesc->pOutVir[Cnt];
        pJpegHandle->stOutSurface.Stride[Cnt] = pstSurfaceDesc->u32OutStride[Cnt];
        if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
        {
           pJpegHandle->stDecSurface.BufPhy[Cnt] = pstSurfaceDesc->u32OutPhy[Cnt];
           pJpegHandle->stDecSurface.BufVir[Cnt] = pstSurfaceDesc->pOutVir[Cnt];
           pJpegHandle->stDecSurface.Stride[Cnt] = pstSurfaceDesc->u32OutStride[Cnt];
        }
    }

    return HI_SUCCESS;
}

HI_VOID HI_JPEG_GetLuPixSum(HI_ULONG DecHandle, HI_U64 *u64LuPixSum)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != u64LuPixSum)
    {
       *u64LuPixSum = pJpegHandle->u64LuPixValue;
    }

    return;
}

HI_VOID HI_JPEG_SetCropRect(HI_ULONG DecHandle, const HI_JPEG_RECT_S *pstCropRect)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (NULL != pstCropRect)
    {
        pJpegHandle->bCrop = HI_TRUE;
        pJpegHandle->stOutSurface.stCropRect.x = pstCropRect->x;
        pJpegHandle->stOutSurface.stCropRect.y = pstCropRect->y;
        pJpegHandle->stOutSurface.stCropRect.w = pstCropRect->w;
        pJpegHandle->stOutSurface.stCropRect.h = pstCropRect->h;
    }

    return;
}

HI_VOID HI_JPEG_IfHardDec(HI_ULONG DecHandle, HI_BOOL *pHardDec)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != pHardDec)
    {
       *pHardDec = pJpegHandle->bHdecSuccess;
    }

    return;
}

HI_S32 HI_JPEG_SetExifMark(HI_ULONG DecHandle, HI_BOOL bExifSupport)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    pJpegHandle->bExifSupport = bExifSupport;

    return HI_SUCCESS;
}

HI_U8 HI_JPEG_GetImageCount(HI_ULONG DecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return 0;
    }

    return pJpegHandle->u8ImageCount;
}

HI_U32 HI_JPEG_GetThumbnailSize(HI_ULONG DecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return 0;
    }

    return pJpegHandle->u32ThumbnailSize;
}

HI_S32 HI_JPEG_GetThumbnail(HI_ULONG DecHandle, HI_CHAR* pThumbnailAddr)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if (NULL == pThumbnailAddr)
    {
       return HI_FAILURE;
    }

    if (NULL == pJpegHandle->pThumbnailAddr)
    {
       return HI_FAILURE;
    }

    if (0 == pJpegHandle->u32ThumbnailSize)
    {
       return HI_FAILURE;
    }

    HI_GFX_Memcpy(pThumbnailAddr, pJpegHandle->pThumbnailAddr, pJpegHandle->u32ThumbnailSize);

    return HI_SUCCESS;
}

HI_BOOL HI_JPEG_IsHdr(HI_ULONG DecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FALSE;
    }

    return pJpegHandle->bIsHDR;
}
