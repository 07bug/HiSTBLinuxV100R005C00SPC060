/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : hi_jpeg_api.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                        Author                     Modification
2018/01/01                   sdk                       Created file
**********************************************************************************************/

#ifndef __HI_JPEG_API_H__
#define __HI_JPEG_API_H__


/*********************************add include here********************************************/
#include "hi_type.h"

/*********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

     /***************************** Macro Definition *****************************************/
     /** \addtogroup      JPEG */
     /** @{ */    /** <!--[JPEG]*/
     #define HI_JPEG_MAX_COMPONENT_NUM            3
     #define HI_DCT_SIZE                          8
     #define HI_DCT_SIZE2                         64
     #define HI_MAX_COMPS_IN_SCAN                 4
     /** @} */  /** <!-- ==== Macro Definition end ==== */

     /*************************** Enum Definition ********************************************/
     /** \addtogroup      JPEG */
     /** @{ */    /** <!--[JPEG]*/
     typedef enum hiJPEG_FMT_E
     {
         HI_JPEG_FMT_ARGB_8888 = 0,
         HI_JPEG_FMT_BGRA_8888,
         HI_JPEG_FMT_ABGR_8888,
         HI_JPEG_FMT_RGBA_8888,
         HI_JPEG_FMT_ARGB_1555,
         HI_JPEG_FMT_BGRA_5551,
         HI_JPEG_FMT_ABGR_1555,
         HI_JPEG_FMT_RGBA_5551,
         HI_JPEG_FMT_RGB_888,
         HI_JPEG_FMT_BGR_888,
         HI_JPEG_FMT_RGB_565,
         HI_JPEG_FMT_BGR_565,
         HI_JPEG_FMT_YCbCr,
         HI_JPEG_FMT_CrCbY,
         HI_JPEG_FMT_YCCK,
         HI_JPEG_FMT_CMYK,
         HI_JPEG_FMT_YUV400,
         HI_JPEG_FMT_YUV420,
         HI_JPEG_FMT_YUV422_21,
         HI_JPEG_FMT_YUV422_12,
         HI_JPEG_FMT_YUV444,
         HI_JPEG_FMT_BUTT
     }HI_JPEG_FMT_E;
     /** @} */  /** <!-- ==== enum Definition end ==== */

    /*************************** Structure Definition ****************************************/

    /** \addtogroup      JPEG */
    /** @{ */    /** <!--[JPEG]*/
    typedef struct hiJPEG_RECT_S
    {
        HI_U32 x, y;
        HI_U32 w, h;
    }HI_JPEG_RECT_S;

    typedef struct hiJPEG_SURFACE_S
    {
        HI_CHAR* pOutVir[HI_JPEG_MAX_COMPONENT_NUM];
        HI_U32 u32OutPhy[HI_JPEG_MAX_COMPONENT_NUM];
        HI_U32 u32OutStride[HI_JPEG_MAX_COMPONENT_NUM];
    }HI_JPEG_SURFACE_S;

    typedef struct hiJPEG_INFO_S
    {
         HI_BOOL bOutInfo;
         HI_BOOL LowDelay;
         HI_U32  u32Width[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32  u32Height[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32  u32McuHeight[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32  u32OutStride[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32  u32OutSize[HI_JPEG_MAX_COMPONENT_NUM];
         HI_JPEG_FMT_E enFmt;
    }HI_JPEG_INFO_S;

    typedef struct hiJPEG_OUT_INFO_S
    {
        HI_U32 scale_num;
        HI_U32 scale_denom;
        HI_JPEG_FMT_E OutFmt;
    }HI_JPEG_OUT_INFO_S;

    /** @} */  /** <!-- ==== Structure Definition End ==== */

    /********************** Global Variable declaration **************************************/

    /******************************* API declaration *****************************************/
    /**
     \brief Get Jpeg information. CNcomment:获取jpeg图片信息 CNend
     \attention \n
     if you want to get input format and input width and input height,you should set bOutInfo false.\n
     others you can get the information as follows: output rgb widht/height/stride/size or output \n
     yuvsp lu width/height/stride/size and ch width/height/stride/size.\n
     you call this function should after read header and set the ouput parameter.\n
     CNcomment:当bOutInfo设置成FALSE的时候，可以获取到图片输入的宽度和高度以及像素格式，当设置成TRUE的 \n
               时候则可以获取到如下信息，要是解码RGB则获取到宽度/高度/行间距/大小,要是解码输出yuvsp，\n
               则可以获取的亮度和色度的宽度/高度/行间距/大小的信息。 CNend\n

     \param[in]    DecHandle. CNcomment:解码对象 CNend
     \param[out]   pJpegInfo.  CNcomment:解码jpeg的相关信息  CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_GetJpegInfo
     */
     HI_S32 HI_JPEG_GetJpegInfo(HI_ULONG DecHandle, HI_JPEG_INFO_S *pJpegInfo);

    /**
     \brief exit jpeg decode. CNcomment:退出jpeg 解码CNend
     \attention \n
      when you want not to decode, call this function\n
      CNcomment:设置是否退出解码CNend\n
     \param[in] DecHandle. CNcomment:解码对象 CNend
     \retval :: NA
     \see \n
      ::HI_JPEG_StopDec
    */
    HI_VOID HI_JPEG_StopDec(HI_ULONG DecHandle);

    /**
     \brief Sets dec output message. CNcomment:设置解码输出的信息上下文 CNend
     \attention \n
     HI_JPEG_SetOutDesc should have called create jpeg decoder.set the output address \n
     and output stride,set whether crop, set crop rect \n
     CNcomment:必须在创建解码器之后，启动解码之前调用该接口，主要设置解码输出地址和输出 \n
               行间距，设置是否裁剪以及对应的裁剪区域 CNend\n

     \param[in] DecHandle. CNcomment:解码对象 CNend
     \param[in] *pstSurfaceDesc. CNcomment:解码输出描述信息 CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_SetOutDesc
     */
     HI_S32 HI_JPEG_SetOutDesc(HI_ULONG DecHandle, const HI_JPEG_SURFACE_S *pstSurfaceDesc);

    /**
    \brief set stream mem information. CNcomment:设置码流内存信息 CNend
    \attention \n
     if want to use this function,should call after jpeg_stdio_src or jpeg_mem_src\n
    CNcomment:如果要调用，必须在关联码流之后调 CNend\n

    \param[in] DecHandle. CNcomment:解码对象 CNend
    \param[in] StreamPhyAddr.       CNcomment:码流buffer 内存池起始物理地址 CNend
    \param[in] StremBufSize.        CNcomment:码流buffer 内存池大小         CNend
    \param[in] pFirstStreamVirBuf.  CNcomment: 第一块buffer起始地址          CNend
    \param[in] FirstStreamBufSize . CNcomment: 第一块码流buffer 大小 CNend
    \param[in] pSecondStreamVirBuf. CNcomment: 第二块地址 CNend
    \param[in] SecondStreamBufSize. CNcomment: 第二块码流buffer 大小 CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE
    \see \n
    ::HI_JPEG_SetStreamBufInfo
    */
    HI_S32 HI_JPEG_SetStreamBufInfo(HI_ULONG DecHandle,
                                    HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,
                                    HI_CHAR* pFirstStreamVirBuf,HI_U32 FirstStreamBufSize,
                                    HI_CHAR* pSecondStreamVirBuf,HI_U32 SecondStreamBufSize);

    /**
     \brief create decompress. CNcomment: 创建解码器 CNend
     \attention \n
      create hard decompress\n
      CNcomment:创建解码器 CNend\n
     \param[in] StreamPhyAddr 内存池连续物理起始地址
     \param[in] TotalStremBufSize 内存池大小
     \param[in] pFirstStreamVirBuf 第一块buffer的虚拟起始地址
     \param[in] FirstStreamBufSize 第一块buffer大小
     \param[in] pSecondStreamVirBuf 第二块buffer的虚拟起始地址
     \param[in] SecondStreamBufSize 第二块buffer大小
     \retval :: decompress handle
     \see \n
      ::HI_JPEG_CreateDecompress
    */
    HI_ULONG HI_JPEG_CreateDecompress(HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,
                                      HI_CHAR* pFirstStreamVirBuf,HI_U32 FirstStreamBufSize,
                                      HI_CHAR* pSecondStreamVirBuf,HI_U32 SecondStreamBufSize);

    /**
     \brief destory decompress. CNcomment: 销毁解码器 CNend
     \attention \n
      destory hard decompress\n
      CNcomment:销毁解码器 CNend\n
     \param[in] DecHandle 解码器
     \retval :: NA
     \see \n
      ::HI_JPEG_DestroyDecompress
    */
    HI_VOID HI_JPEG_DestroyDecompress(HI_ULONG DecHandle);

    /**
     \brief scan lines. CNcomment: 行扫描输出 CNend
     \attention \n
      call this function after jpeg_start_decompress \n
      CNcomment:行扫描输出 CNend\n
     \param[in] cinfo 软解码器
     \retval :: decompress handle
     \see \n
      ::HI_JPEG_StartDecompress
    */
    HI_S32 HI_JPEG_StartDecompress(HI_ULONG DecHandle);

    /**
     \brief Get Jpeg information. CNcomment:获取jpeg图片信息 CNend
     \attention \n
           CNend\n
     \param[in]    DecHandle. CNcomment:解码对象 CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_ParseHeader
     */
    HI_S32 HI_JPEG_ParseHeader(HI_ULONG DecHandle);

    /**
    \brief set low delay information. CNcomment:设置低延迟信息,地址大小为8个字节 CNend
    \attention the s32LineNum value should in [1 ~ output height]\n
    NA.\n
    CNcomment:CNend\n

    \param[in]  DecHandle      CNcomment:解码对象                     CNend
    \param[in]  u32PhyLineBuf. CNcomment:保存行号连续地址             CNend
    \param[in]  pVirLineBuf.   CNcomment:保存行号虚拟地址             CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE

    \see \n
    ::HI_JPEG_SetLowDelayInf
    */
    HI_S32 HI_JPEG_SetLowDelayInf(HI_ULONG DecHandle, HI_U32 u32PhyLineBuf, HI_CHAR* pVirLineBuf);

    /**
     \brief set output color space information. CNcomment: 设置图片输出色彩空间格式 CNend
     \attention \n
      call this function after jpeg_read_header\n
      CNcomment: 设置图片输出色彩空间信息 CNend\n
     \param[in] DecHandle 解码器
     \param[in] pstOutInfo 输出图片信息
     \see \n
      ::HI_JPEG_SetOutInfo
    */
    HI_S32 HI_JPEG_SetOutInfo(HI_ULONG DecHandle, HI_JPEG_OUT_INFO_S *pstOutInfo);

    /** @} */  /** <!-- ==== API Declaration End ==== */

    /*****************************************************************************************/


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPEG_API_H__*/
