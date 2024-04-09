/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_parse.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : jpeg文件解析
Function List    :


History          :
Date                       Author                     Modification
2018/01/01                 sdk                        Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#ifdef HI_BUILD_IN_BOOT
  #ifndef HI_BUILD_IN_MINI_BOOT
     #include <linux/string.h>
  #else
     #include "string.h"
  #endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"

/***************************** Macro Definition ***************************************************/
#define JPEG_ALIGNED_SCALE(x, i)    ( ( (x) + (1 << (i)) - 1 ) >> (i) )
#define JPEG_ROUND_UP(a,b)          (0 == b) ? (a) : (( ((a) + (b) - (1L)) / (b) ))

/***************************** Structure Definition ***********************************************/
typedef enum tagJPEG_HDEC_SCALE_E
{
    JPEG_SCALEDOWN_1 = 0,      /**< scanle down 1 >**//**<CNcomment:不缩放   >**/
    JPEG_SCALEDOWN_2 = 1,      /**< scanle down 2 >**//**<CNcomment:缩小2倍 >**/
    JPEG_SCALEDOWN_4 = 2,      /**< scanle down 4 >**//**<CNcomment:缩小4倍 >**/
    JPEG_SCALEDOWN_8 = 3,      /**< scanle down 8 >**//**<CNcomment:缩小8倍 >**/
    JPEG_SCALEDOWN_BUTT
}JPEG_HDEC_SCALE_E;
/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/

static inline HI_VOID JPEG_HDEC_CalcScale(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_VOID JPEG_HDEC_GetOutSize(const HI_U32 u32Ration,const HI_U32 u32InWidth, const HI_U32 u32InHeight,HI_U32 *pu32OutWidth,HI_U32 *pu32OutHeight);
static inline HI_VOID JPEG_HDEC_SetOutColorSapceMarker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_VOID JPEG_HDEC_GetStride(HI_U32 u32SrcW, HI_U32 *pu32Stride,HI_U32 u32Align);
static inline HI_VOID JPEG_HDEC_InitCropRect(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_VOID JPEG_HDEC_CalcOutStride(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_U32 Width);
static inline HI_VOID JPEG_HDEC_GetUVResolutionForYuv420sp(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_U32 YHeightTmp, HI_U32 YStride, HI_U32 *pUVHeightTmp, HI_U32 *pUVStride);
static inline HI_VOID JPEG_HDEC_GetCalcOutXRGBSize(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_U32 *pYSize, HI_U32 *pCSize);
static inline HI_BOOL JPEG_HDEC_CheckDecXRGBSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);

/***************************** API realization ****************************************************/

/*****************************************************************************
* func         : JPEG_HDEC_GetImagInfo
* description  : get jpeg picture information
                 CNcomment:  获取图片信息 CNend\n
* param[in]    : cinfo       CNcomment: 解码对象    CNend\n
* retval       : NA
* others:      : NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_GetImagInfo(HI_ULONG HdecHandle)
{
      HI_U32 InputMcuWidth  = 0;
      HI_U32 InputMcuHeight = 0;
      HI_U32 DecWidth = 0;
      HI_U32 DecHeight = 0;
      /**<-- mcu data >**/
      /**<-- 宏块大小 >**/
      HI_U32 YWidthTmp = 0;
      HI_U32 YHeightTmp = 0;
      HI_U32 CHeightTmp = 0;
      /**<-- useful data >**/
      /**<-- 实际有用的大小 >**/
      HI_U32 u32YStride = 0;
      HI_U32 u32UVStride = 0;
      HI_U32 u32YWidth = 0;
      HI_U32 u32YHeight = 0;
      HI_U32 u32UVWidth = 0;
      HI_U32 u32UVHeight = 0;
      HI_U32 u32YSize = 0;
      HI_U32 u32CSize = 0;

      JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
      if (NULL == pJpegHandle)
      {
          return;
      }

      if (HI_TRUE == pJpegHandle->stJpegSofInfo.bCalcSize)
      {
          return;
      }

      JPEG_HDEC_CalcScale(pJpegHandle);

      JPEG_HDEC_GetOutSize(pJpegHandle->ScalRation,               \
                           pJpegHandle->stImgInfo.image_width,    \
                           pJpegHandle->stImgInfo.image_height,   \
                           &(pJpegHandle->stImgInfo.output_width),\
                           &(pJpegHandle->stImgInfo.output_height));

      JPEG_HDEC_SetOutColorSapceMarker(pJpegHandle);

      JPEG_HDEC_GetStride(pJpegHandle->stImgInfo.output_width,&u32YStride,JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN);

      u32YWidth  = (pJpegHandle->stImgInfo.output_width <= 1)  ? (2) : (pJpegHandle->stImgInfo.output_width);
      u32YHeight = (pJpegHandle->stImgInfo.output_height <= 1) ? (2) : (pJpegHandle->stImgInfo.output_height);

      if (1 == pJpegHandle->stImgInfo.u8Fac[0][0])
      {
           InputMcuWidth  = (pJpegHandle->stImgInfo.image_width  + JPEG_MCU_8ALIGN - 1) >> 3;
           DecWidth = (pJpegHandle->stImgInfo.image_width   + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
           YWidthTmp = (pJpegHandle->stImgInfo.output_width  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
      }
      else
      {
           InputMcuWidth  = (pJpegHandle->stImgInfo.image_width  + JPEG_MCU_16ALIGN - 1) >> 4;
           DecWidth  = (pJpegHandle->stImgInfo.image_width + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
           YWidthTmp = (pJpegHandle->stImgInfo.output_width + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
      }

      if (1 == pJpegHandle->stImgInfo.u8Fac[0][1])
      {
           InputMcuHeight = (pJpegHandle->stImgInfo.image_height + JPEG_MCU_8ALIGN - 1) >> 3;
           DecHeight  = (pJpegHandle->stImgInfo.image_height  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
           YHeightTmp = (pJpegHandle->stImgInfo.output_height + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1));
      }
      else
      {
           InputMcuHeight = (pJpegHandle->stImgInfo.image_height + JPEG_MCU_16ALIGN - 1) >> 4;
           DecHeight  = (pJpegHandle->stImgInfo.image_height  + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
           YHeightTmp = (pJpegHandle->stImgInfo.output_height + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1));
      }

      switch (pJpegHandle->stImgInfo.jpeg_color_space)
      {
          case HI_JPEG_FMT_YUV420:
              CHeightTmp  = YHeightTmp >> 1;
              u32UVStride = u32YStride;
              u32YWidth   = (u32YWidth  >> 1) << 1;
              u32YHeight  = (u32YHeight >> 1) << 1;
              u32UVWidth  = u32YWidth  >> 1;
              u32UVHeight = u32YHeight >> 1;
              break;
          case HI_JPEG_FMT_YUV422_21:
              CHeightTmp  = YHeightTmp;
              u32UVStride = u32YStride;
              JPEG_HDEC_GetUVResolutionForYuv420sp(pJpegHandle,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32YWidth    = (u32YWidth  >> 1) << 1;
              u32UVWidth   = u32YWidth >> 1;
              u32UVHeight  = u32YHeight;
              break;
          case HI_JPEG_FMT_YUV422_12:
              CHeightTmp  = YHeightTmp >> 1;
              u32UVStride = u32YStride << 1;
              JPEG_HDEC_GetUVResolutionForYuv420sp(pJpegHandle,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32YHeight   = (u32YHeight >> 1) << 1;
              u32UVWidth   = u32YWidth;
              u32UVHeight  = u32YHeight >> 1;
              break;
          case HI_JPEG_FMT_YUV444:
              CHeightTmp  = YHeightTmp;
              u32UVStride = u32YStride << 1;
              JPEG_HDEC_GetUVResolutionForYuv420sp(pJpegHandle,YHeightTmp,u32YStride,&CHeightTmp,&u32UVStride);
              u32UVWidth   = u32YWidth;
              u32UVHeight  = u32YHeight;
              break;
          default:
              break;
      }

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
      if ((HI_TRUE == pJpegHandle->bOutYUV420SP) && (HI_JPEG_FMT_YUV400 != pJpegHandle->stImgInfo.output_color_space))
      {
          u32YWidth  = (0 == (u32YWidth  % 2)) ? (u32YWidth)  : (u32YWidth  - 1);
          u32YHeight = (0 == (u32YHeight % 2)) ? (u32YHeight) : (u32YHeight - 1);
          u32UVWidth = u32YWidth >> 1;
          u32UVHeight = u32YHeight >> 1;
      }
#endif

      JPEG_HDEC_InitCropRect(pJpegHandle);

      JPEG_HDEC_CalcOutStride(pJpegHandle,YWidthTmp);
      pJpegHandle->stJpegSofInfo.DecOutStride = (HI_TRUE == pJpegHandle->bOutYCbCrSP) ? (u32YStride) : (pJpegHandle->stJpegSofInfo.DecOutStride);

      u32YSize = YHeightTmp * u32YStride;
      u32CSize = CHeightTmp * u32UVStride;
      JPEG_HDEC_GetCalcOutXRGBSize(pJpegHandle, &u32YSize, &u32CSize);

      /**<-- jpeg decode use mcu align  >**/
      /**<-- jpeg 解码使用的参数为MCU 对齐的 >**/
      pJpegHandle->stJpegSofInfo.bCalcSize =  HI_TRUE;

      pJpegHandle->stJpegSofInfo.u32InWandH =  (InputMcuWidth | (InputMcuHeight << 16));

      pJpegHandle->stJpegSofInfo.u32YWidth  =  u32YWidth;
      pJpegHandle->stJpegSofInfo.u32YHeight =  u32YHeight;
      pJpegHandle->stJpegSofInfo.u32YStride =  u32YStride;
      pJpegHandle->stJpegSofInfo.u32YSize   =  u32YSize;
      pJpegHandle->stJpegSofInfo.u32CWidth  =  u32UVWidth;
      pJpegHandle->stJpegSofInfo.u32CHeight =  u32UVHeight;
      pJpegHandle->stJpegSofInfo.u32CbCrStride = u32UVStride;
      pJpegHandle->stJpegSofInfo.u32CSize =  u32CSize;

      pJpegHandle->stJpegSofInfo.u32YMcuHeight = YHeightTmp;
      pJpegHandle->stJpegSofInfo.u32CMcuHeight = CHeightTmp;

      /**<-- get lu  pixel sum >**/
      /**<-- 统计亮度和使用>**/
      pJpegHandle->stJpegSofInfo.DecOutWidth = DecWidth  >> pJpegHandle->ScalRation;
      pJpegHandle->stJpegSofInfo.DecOutHeight = DecHeight >> pJpegHandle->ScalRation;

#ifdef CONFIG_JPEG_HARDDEC2ARGB
      pJpegHandle->stJpegSofInfo.u32McuWidth  =  InputMcuWidth;
      pJpegHandle->stJpegSofInfo.u32MINSize   =  InputMcuWidth * 128;
      pJpegHandle->stJpegSofInfo.u32MIN1Size  =  pJpegHandle->stJpegSofInfo.u32MINSize;
      pJpegHandle->stJpegSofInfo.u32RGBSizeReg =  2 * pJpegHandle->stJpegSofInfo.u32MINSize;
#endif

      return;
}

static inline HI_VOID JPEG_HDEC_GetUVResolutionForYuv420sp(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_U32 YHeightTmp, HI_U32 YStride, HI_U32 *pUVHeightTmp, HI_U32 *pUVStride)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
     if (HI_TRUE != pJpegHandle->bOutYUV420SP)
     {
         return;
     }

     if (HI_JPEG_FMT_YUV422_21 == pJpegHandle->stImgInfo.jpeg_color_space)
     {
         *pUVHeightTmp  = YHeightTmp >> 1;
         return;
     }

     if (HI_JPEG_FMT_YUV422_12 == pJpegHandle->stImgInfo.jpeg_color_space)
     {
         *pUVStride = (YStride << 1) >> 1;
         return;
     }

     if (HI_JPEG_FMT_YUV444 == pJpegHandle->stImgInfo.jpeg_color_space)
     {
         *pUVHeightTmp  = YHeightTmp >> 1;
         *pUVStride = (YStride << 1) >> 1;
         return;
     }
#else
    HI_UNUSED(pJpegHandle);
    HI_UNUSED(YHeightTmp);
    HI_UNUSED(YStride);
    HI_UNUSED(pUVHeightTmp);
    HI_UNUSED(pUVStride);
#endif
    return;
}

static inline HI_VOID JPEG_HDEC_InitCropRect(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle)
{
    if (HI_TRUE == pJpegHandle->bSetCropRect)
    {
         return;
    }

    pJpegHandle->stOutSurface.stCropRect.x = 0;
    pJpegHandle->stOutSurface.stCropRect.y = 0;
    pJpegHandle->stOutSurface.stCropRect.w = pJpegHandle->stImgInfo.output_width;
    pJpegHandle->stOutSurface.stCropRect.h = pJpegHandle->stImgInfo.output_height;

    return;
}

static inline HI_VOID JPEG_HDEC_GetCalcOutXRGBSize(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle, HI_U32 *pYSize, HI_U32 *pCSize)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
    unsigned long tmp_value = 0;

    if (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return;
    }

    tmp_value = (unsigned long)pJpegHandle->stJpegSofInfo.DecOutStride * (unsigned long)pJpegHandle->stOutSurface.stCropRect.h;
    *pYSize = (tmp_value > UINT_MAX) ? (0) : (tmp_value);
    *pCSize = 0;
#else
    HI_UNUSED(pJpegHandle);
    HI_UNUSED(pYSize);
    HI_UNUSED(pCSize);
#endif
    return;
}

static inline HI_VOID JPEG_HDEC_CalcScale(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_8;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 2)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_4;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 3)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 4)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_2;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 5)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 6)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 7)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 8)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_1;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 9)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 10)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 11)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 12)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 13)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 14)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else if (pJpegHandle->stImgInfo.scale_num * HI_DCT_SIZE <= pJpegHandle->stImgInfo.scale_denom * 15)
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }
    else
    {
        pJpegHandle->ScalRation = JPEG_SCALEDOWN_BUTT;
    }

    return;
}


static inline HI_VOID JPEG_HDEC_GetOutSize(const HI_U32 u32Ration,const HI_U32 u32InWidth, const HI_U32 u32InHeight,HI_U32 *pu32OutWidth,HI_U32 *pu32OutHeight)
{
      switch (u32Ration)
      {
        case 0:
            *pu32OutWidth  = u32InWidth;
            *pu32OutHeight = u32InHeight;
            break;
        case 1:
            *pu32OutWidth  = (HI_U32)JPEG_ROUND_UP((long) u32InWidth,  2L);
            *pu32OutHeight = (HI_U32)JPEG_ROUND_UP((long) u32InHeight, 2L);
            break;
        case 2:
            *pu32OutWidth  = (HI_U32)JPEG_ROUND_UP((long) u32InWidth,  4L);
            *pu32OutHeight = (HI_U32)JPEG_ROUND_UP((long) u32InHeight, 4L);
            break;
        case 3:
            *pu32OutWidth  = (HI_U32)JPEG_ROUND_UP((long) u32InWidth,  8L);
            *pu32OutHeight = (HI_U32)JPEG_ROUND_UP((long) u32InHeight, 8L);
            break;
        default:
            break;
      }
      return;
}

static inline HI_VOID JPEG_HDEC_SetOutColorSapceMarker(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle)
{
     if (  (HI_JPEG_FMT_YUV400    == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_YUV420    == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_YUV422_12 == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_YUV422_21 == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_YUV444    == pJpegHandle->stImgInfo.output_color_space))
      {
          pJpegHandle->bOutYCbCrSP = HI_TRUE;
      }
      else
      {
          pJpegHandle->bOutYCbCrSP = HI_FALSE;
      }

      if (0 == pJpegHandle->ScalRation)
      {
          pJpegHandle->bDecOutColorSpaecXRGB = JPEG_HDEC_CheckDecXRGBSupport(pJpegHandle);
      }
      else
      {
          pJpegHandle->bDecOutColorSpaecXRGB = HI_FALSE;
      }
      return;
}


static inline HI_BOOL JPEG_HDEC_CheckDecXRGBSupport(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
     if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
     {
        return HI_FALSE;
     }

     if (   (HI_JPEG_FMT_ARGB_8888 == pJpegHandle->stImgInfo.output_color_space)
          ||(HI_JPEG_FMT_ABGR_8888 == pJpegHandle->stImgInfo.output_color_space))
     {
        return HI_TRUE;
     }

     if (  (HI_JPEG_FMT_ARGB_1555 == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_ABGR_1555 == pJpegHandle->stImgInfo.output_color_space))
     {
        return HI_TRUE;
     }

     if (  (HI_JPEG_FMT_RGB_888 == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_BGR_888 == pJpegHandle->stImgInfo.output_color_space))
     {
         return HI_TRUE;
     }

     if (  (HI_JPEG_FMT_RGB_565 == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_BGR_565 == pJpegHandle->stImgInfo.output_color_space))
     {
         return HI_TRUE;
     }
#else
     HI_UNUSED(pJpegHandle);
#endif
     return HI_FALSE;
}

/*****************************************************************************
* func          : JPEG_HDEC_CalcOutStride
* description   : calculate out stride
                  CNcomment:  计算输出行间距 CNend\n
* param[in]     : cinfo       CNcomment: 解码对象    CNend\n
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_VOID JPEG_HDEC_CalcOutStride(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle, HI_U32 Width)
{
    JPEG_HDEC_GetStride(Width * pJpegHandle->stImgInfo.out_color_components,&(pJpegHandle->stJpegSofInfo.DecOutStride),JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN);

    return;
}

static inline HI_VOID JPEG_HDEC_GetStride(HI_U32 u32SrcW, HI_U32 *pu32Stride,HI_U32 u32Align)
{
     if (NULL == pu32Stride)
     {
         return;
     }

#ifdef CONFIG_GFX_256BYTE_ALIGN
     HI_UNUSED(u32Align);
     *pu32Stride = HI_SYS_GET_STRIDE(u32SrcW);
#else
     *pu32Stride = (u32SrcW + u32Align - 1) & (~(u32Align - 1));
#endif

      return;
}
