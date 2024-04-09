/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_csc.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/
#ifndef CONFIG_JPEG_CSC_DISABLE

/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hi_jpeg_config.h"
#include "hi_gfx_sys.h"
#include  "hi_drv_tde.h"

#include "jpeg_hdec_api.h"

/***************************** Macro Definition ***************************************************/


/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/

/***************************** API realization ****************************************************/
static HI_S32 JPEG_DEC_CSC_Open()
{
    HI_S32 CscDev = -1;
    CscDev = open("/dev/hi_tde", O_RDWR, S_IRUSR);
    if (CscDev < 0)
    {
        return -1;
    }

    return CscDev;
}

static HI_VOID JPEG_DEC_CSC_Close(HI_S32 CscDev)
{
    if (CscDev < 0)
    {
       return;
    }

    close(CscDev);

    return;
}

static inline TDE2_COLOR_FMT_E JPEG_HDEC_GetXRGB8888(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    /** inline function,should not check null pointer **/

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
        case HI_JPEG_FMT_RGBA_8888:
            return TDE2_COLOR_FMT_RGBA8888;
        case HI_JPEG_FMT_BGRA_8888:
            return TDE2_COLOR_FMT_BGRA8888;
        case HI_JPEG_FMT_ABGR_8888:
            return TDE2_COLOR_FMT_ABGR8888;
        case HI_JPEG_FMT_ARGB_8888:
            return TDE2_COLOR_FMT_ARGB8888;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static inline TDE2_COLOR_FMT_E JPEG_HDEC_GetXRGB1555(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    /** inline function,should not check null pointer **/

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
        case HI_JPEG_FMT_BGRA_5551:
            return TDE2_COLOR_FMT_BGRA1555;
        case HI_JPEG_FMT_RGBA_5551:
            return TDE2_COLOR_FMT_RGBA1555;
        case HI_JPEG_FMT_ARGB_1555:
            return TDE2_COLOR_FMT_ARGB1555;
        case HI_JPEG_FMT_ABGR_1555:
            return TDE2_COLOR_FMT_ABGR1555;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static inline TDE2_COLOR_FMT_E JPEG_HDEC_GetRGB888(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    /** inline function,should not check null pointer **/

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
        case HI_JPEG_FMT_BGR_888:
            return TDE2_COLOR_FMT_BGR888;
        case HI_JPEG_FMT_RGB_888:
            return TDE2_COLOR_FMT_RGB888;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static inline TDE2_COLOR_FMT_E JPEG_HDEC_GetRGB565(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    /** inline function,should not check null pointer **/

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
        case HI_JPEG_FMT_RGB_565:
            return TDE2_COLOR_FMT_RGB565;
        case HI_JPEG_FMT_BGR_565:
            return TDE2_COLOR_FMT_BGR565;
        default:
            return TDE2_COLOR_FMT_BUTT;
    }
}

static inline TDE2_COLOR_FMT_E JPEG_HDEC_ConvertJpegFmtToTdeFmt(HI_ULONG HdecHandle)
{
    TDE2_COLOR_FMT_E eCSCFmt = TDE2_COLOR_FMT_BUTT;

    eCSCFmt = JPEG_HDEC_GetXRGB8888(HdecHandle);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetXRGB1555(HdecHandle);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetRGB888(HdecHandle);
    if (TDE2_COLOR_FMT_BUTT != eCSCFmt)
    {
       return eCSCFmt;
    }

    eCSCFmt = JPEG_HDEC_GetRGB565(HdecHandle);

    return eCSCFmt;
}

static inline HI_S32 JPEG_HDEC_CSC_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst,TDE2_RECT_S  *pstDstRect,TDE2_MBOPT_S* pstMbOpt,HI_S32 CscDev)
{
    TDE_MBBITBLT_CMD_S stMbBlit;
    HI_GFX_Memset(&stMbBlit,0,sizeof(stMbBlit));
    /** inline function,should not check null pointer **/

    stMbBlit.s32Handle = s32Handle;
    HI_GFX_Memcpy(&stMbBlit.stMB, pstMB, sizeof(TDE2_MB_S));
    HI_GFX_Memcpy(&stMbBlit.stMbRect, pstMbRect, sizeof(TDE2_RECT_S));
    HI_GFX_Memcpy(&stMbBlit.stDstRect, pstDstRect, sizeof(TDE2_RECT_S));
    HI_GFX_Memcpy(&stMbBlit.stMbOpt, pstMbOpt, sizeof(TDE2_MBOPT_S));

    stMbBlit.stDst.bAlphaExt1555  = pstDst->bAlphaExt1555;
    stMbBlit.stDst.bAlphaMax255   = pstDst->bAlphaMax255;
    stMbBlit.stDst.bYCbCrClut     = pstDst->bYCbCrClut;
    stMbBlit.stDst.enColorFmt     = pstDst->enColorFmt;
    stMbBlit.stDst.u32ClutPhyAddr = 0;
    stMbBlit.stDst.u32CbCrPhyAddr = pstDst->u32CbCrPhyAddr;
    stMbBlit.stDst.u32CbCrStride  = pstDst->u32CbCrStride;
    stMbBlit.stDst.u32Height      = pstDst->u32Height;
    stMbBlit.stDst.u32PhyAddr     = pstDst->u32PhyAddr;
    stMbBlit.stDst.u32Stride      = pstDst->u32Stride;
    stMbBlit.stDst.u32Width       = pstDst->u32Width;
    stMbBlit.stDst.u8Alpha0       = pstDst->u8Alpha0;
    stMbBlit.stDst.u8Alpha1       = pstDst->u8Alpha1;

    return ioctl(CscDev, TDE_MB_BITBLT, &stMbBlit);
}

static inline HI_S32 JPEG_HDEC_CSC_BeginJob(HI_S32 CscDev)
{
    TDE_HANDLE Handle = HI_ERR_TDE_INVALID_HANDLE;

    if (ioctl(CscDev, TDE_BEGIN_JOB, &Handle) < 0)
    {
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    return Handle;
}

static inline HI_S32 JPEG_HDEC_CSC_EndJob(TDE_HANDLE s32Handle, HI_BOOL bBlock, HI_U32 u32TimeOut,HI_S32 CscDev)
{
    HI_S32 Ret = HI_FAILURE;
    TDE_ENDJOB_CMD_S stEndJob;
    HI_GFX_Memset(&stEndJob,0,sizeof(stEndJob));

    stEndJob.s32Handle  = s32Handle;
    stEndJob.bSync      = HI_FALSE;
    stEndJob.bBlock     = bBlock;
    stEndJob.u32TimeOut = u32TimeOut;

    Ret = ioctl(CscDev, TDE_END_JOB, &stEndJob);
    if (HI_ERR_TDE_INTERRUPT == Ret)
    {
       Ret = ioctl(CscDev, TDE_WAITFORDONE, &s32Handle);
    }

    return Ret;
}

static HI_S32 JPEG_HDEC_HardCSC(HI_ULONG HdecHandle)
{
    HI_S32 Ret =  HI_SUCCESS;
    TDE2_MB_S SrcSurface;
    TDE2_SURFACE_S DstSurface;
    TDE2_RECT_S SrcRect,DstRect;
    TDE2_MBOPT_S stMbOpt;
    TDE_HANDLE s32Handle;
//   HI_U32 Row = 0;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        JPEG_TRACE("+++++++%s %d failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {/** jpeg dec to xrgb, should not with tde to csc **/
        pJpegHandle->bCSCEnd = HI_TRUE;
        return HI_SUCCESS;
    }

    if ( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bCSCEnd))
    {/** if dec out to yuv or csc is finish, should not csc again **/
        pJpegHandle->bCSCEnd = HI_TRUE;
        return HI_SUCCESS;
    }

    if (pJpegHandle->CscDev < 0)
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&SrcRect,0,sizeof(SrcRect));
    HI_GFX_Memset(&DstRect,0,sizeof(DstRect));
    HI_GFX_Memset(&SrcSurface,0,sizeof(SrcSurface));
    HI_GFX_Memset(&DstSurface,0,sizeof(DstSurface));
    HI_GFX_Memset(&stMbOpt,0,sizeof(stMbOpt));

    SrcSurface.u32YPhyAddr    = pJpegHandle->stDecSurface.BufPhy[0];
    SrcSurface.u32CbCrPhyAddr = pJpegHandle->stDecSurface.BufPhy[1];
    SrcSurface.u32YWidth      = pJpegHandle->stJpegSofInfo.u32YWidth;
    SrcSurface.u32YHeight     = pJpegHandle->stJpegSofInfo.u32YHeight;
    SrcSurface.u32YStride     = pJpegHandle->stJpegSofInfo.u32YStride;
    SrcSurface.u32CbCrStride  = pJpegHandle->stJpegSofInfo.u32CbCrStride;

    switch (pJpegHandle->stImgInfo.jpeg_color_space)
    {
        case HI_JPEG_FMT_YUV400:
            SrcSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP;
            break;
        case HI_JPEG_FMT_YUV420:
            SrcSurface.u32YWidth  = (0 == (SrcSurface.u32YWidth  % 2)) ? (SrcSurface.u32YWidth)  : (SrcSurface.u32YWidth  - 1);
            SrcSurface.u32YHeight = (0 == (SrcSurface.u32YHeight % 2)) ? (SrcSurface.u32YHeight) : (SrcSurface.u32YHeight - 1);
            SrcSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP;
            break;
        case HI_JPEG_FMT_YUV422_21:
            SrcSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP;
            break;
        case HI_JPEG_FMT_YUV422_12:
            SrcSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP;
            break;
         case HI_JPEG_FMT_YUV444:
            SrcSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP;
            break;
         default:
            return HI_FAILURE;
    }

#if 0
    JPEG_TRACE("============================================================================\n");
    JPEG_TRACE("SrcSurface.u32YWidth      = %d\n",SrcSurface.u32YWidth);
    JPEG_TRACE("SrcSurface.u32YHeight     = %d\n",SrcSurface.u32YHeight);
    JPEG_TRACE("SrcSurface.u32YStride     = %d\n",SrcSurface.u32YStride);
    JPEG_TRACE("SrcSurface.u32CbCrStride  = %d\n",SrcSurface.u32CbCrStride);
    JPEG_TRACE("============================================================================\n");
#endif

    DstSurface.enColorFmt = JPEG_HDEC_ConvertJpegFmtToTdeFmt(HdecHandle);
    DstSurface.u32PhyAddr = pJpegHandle->stOutSurface.BufPhy[0];

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {
       DstSurface.u32Stride = pJpegHandle->stOutSurface.Stride[0];
    }
    else
    {
       DstSurface.u32Stride = pJpegHandle->stJpegSofInfo.DecOutStride;
    }

    DstSurface.u32Width       = pJpegHandle->stOutSurface.stCropRect.w;
    DstSurface.u32Height      = pJpegHandle->stOutSurface.stCropRect.h;
    DstSurface.pu8ClutPhyAddr = NULL;
    DstSurface.bYCbCrClut     = HI_FALSE;
    DstSurface.bAlphaMax255   = HI_TRUE;
    DstSurface.bAlphaExt1555  = HI_TRUE;
    DstSurface.u8Alpha0       = 0;
    DstSurface.u8Alpha1       = 255;
    DstSurface.u32CbCrPhyAddr = 0;
    DstSurface.u32CbCrStride  = 0;

    SrcRect.s32Xpos   = pJpegHandle->stOutSurface.stCropRect.x;
    SrcRect.s32Ypos   = pJpegHandle->stOutSurface.stCropRect.y;
    SrcRect.u32Width  = pJpegHandle->stOutSurface.stCropRect.w;
    SrcRect.u32Height = pJpegHandle->stOutSurface.stCropRect.h;
    DstRect.s32Xpos   = 0;
    DstRect.s32Ypos   = 0;
    DstRect.u32Width  = pJpegHandle->stOutSurface.stCropRect.w;
    DstRect.u32Height = pJpegHandle->stOutSurface.stCropRect.h;

#if 0
    JPEG_TRACE("============================================================================\n");
    JPEG_TRACE("DstSurface.u32Width  = %d\n",DstSurface.u32Width);
    JPEG_TRACE("DstSurface.u32Height = %d\n",DstSurface.u32Height);
    JPEG_TRACE("DstSurface.u32Stride = %d\n",DstSurface.u32Stride);
    JPEG_TRACE("SrcRect.s32Xpos      = %d\n",SrcRect.s32Xpos);
    JPEG_TRACE("SrcRect.s32Ypos      = %d\n",SrcRect.s32Ypos);
    JPEG_TRACE("SrcRect.u32Width     = %d\n",SrcRect.u32Width);
    JPEG_TRACE("SrcRect.u32Height    = %d\n",SrcRect.u32Height);
    JPEG_TRACE("DstRect.s32Xpos      = %d\n",DstRect.s32Xpos);
    JPEG_TRACE("DstRect.s32Ypos      = %d\n",DstRect.s32Ypos);
    JPEG_TRACE("DstRect.u32Width     = %d\n",DstRect.u32Width);
    JPEG_TRACE("DstRect.u32Height    = %d\n",DstRect.u32Height);
    JPEG_TRACE("============================================================================\n");
#endif

    if ((SrcSurface.u32YWidth == DstSurface.u32Width) && (SrcSurface.u32YHeight == DstSurface.u32Height))
    {
       stMbOpt.enResize = TDE2_MBRESIZE_NONE;
    }
    else
    {
       stMbOpt.enResize = TDE2_MBRESIZE_QUALITY_LOW;
    }
#if 0/**<-- csc by scanlines **/
    while (Row < pJpegHandle->stOutSurface.stCropRect.h)
    {
        SrcRect.s32Xpos   = pJpegHandle->stOutSurface.stCropRect.x;
        SrcRect.s32Ypos   = Row;
        SrcRect.u32Width  = pJpegHandle->stOutSurface.stCropRect.w;
        SrcRect.u32Height = 1;
        DstRect.s32Xpos   = 0;
        DstRect.s32Ypos   = Row;
        DstRect.u32Width  = pJpegHandle->stOutSurface.stCropRect.w;
        DstRect.u32Height = 1;
#endif
        if ((s32Handle = JPEG_HDEC_CSC_BeginJob(pJpegHandle->CscDev)) != HI_ERR_TDE_INVALID_HANDLE)
        {
          Ret = JPEG_HDEC_CSC_MbBlit(s32Handle, &SrcSurface, &SrcRect, &DstSurface, &DstRect, &stMbOpt,pJpegHandle->CscDev);
          if (HI_SUCCESS != Ret)
          {
              JPEG_TRACE("==== JPEG_HDEC_CSC_MbBlit Failure,s32Ret = 0x%x!\n",Ret);
              return HI_FAILURE;
          }

          Ret = JPEG_HDEC_CSC_EndJob(s32Handle, HI_TRUE, 10000,pJpegHandle->CscDev);
          if (HI_SUCCESS != Ret)
          {
              JPEG_TRACE("==== JPEG_HDEC_CSC_EndJob Failure,s32Ret = 0x%x!\n",Ret);
              return HI_FAILURE;
          }
        }
#if 0
        Row++;
    }
#endif

    pJpegHandle->bCSCEnd = HI_TRUE;

    return HI_SUCCESS;
}

static inline HI_S32 JPEG_HDEC_NeedCpyDataToUserBuffer(HI_ULONG HdecHandle, HI_U32 MaxLines, HI_U32 *pCurScanlines)
{
    HI_U32 Cnt = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    /** inline function,should not check null pointer **/

    if ((HI_FALSE == pJpegHandle->bCSCEnd) || (HI_TRUE == pJpegHandle->bOutUsrBuf))
    {
        for (Cnt = 0; Cnt < MaxLines; Cnt++)
        {
            (*pCurScanlines)++;
        }

        return (HI_S32)MaxLines;
    }

    return HI_FAILURE;
}

static HI_U32 JPEG_HDEC_OutUserBuf(HI_ULONG HdecHandle, HI_CHAR* ScanlineBuf, HI_U32 MaxLines, HI_U32 *pCurScanlines)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 Cnt = 0;
    HI_U32 SrcStride = 0;
    HI_S32 BufSrcLength = 0;
    HI_CHAR *pSrcBuf = NULL;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        JPEG_TRACE("+++++++%s %d failure\n",__FUNCTION__,__LINE__);
        return 0;
    }

    if ((MaxLines + *pCurScanlines) > (pJpegHandle->stImgInfo.output_height))
    {
        MaxLines = pJpegHandle->stImgInfo.output_height - *pCurScanlines;
    }

    Ret = JPEG_HDEC_NeedCpyDataToUserBuffer(HdecHandle,MaxLines,pCurScanlines);
    if (HI_FAILURE != Ret)
    {
        return (HI_U32)Ret;
    }

    if (NULL == ScanlineBuf)
    {
        return MaxLines;
    }

    if (NULL == pJpegHandle->stOutSurface.BufVir[0])
    {
        return MaxLines;
    }

    if (*pCurScanlines < pJpegHandle->stOutSurface.stCropRect.y)
    {
        return MaxLines;
    }

    SrcStride = pJpegHandle->stJpegSofInfo.DecOutStride;
    pSrcBuf = pJpegHandle->stOutSurface.BufVir[0] + (HI_S32)((*pCurScanlines - pJpegHandle->stOutSurface.stCropRect.y) * SrcStride);

    BufSrcLength = (pJpegHandle->stImgInfo.output_components) * (pJpegHandle->stOutSurface.stCropRect.w);
    if (0 == BufSrcLength)
    {
        return MaxLines;
    }

    for (Cnt = 0; Cnt < MaxLines; Cnt++)
    {
       HI_GFX_Memcpy(ScanlineBuf, pSrcBuf, (size_t)BufSrcLength);
    }

    return MaxLines;
}
#endif
