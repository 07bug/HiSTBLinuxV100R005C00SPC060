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
     \brief Get Jpeg information. CNcomment:��ȡjpegͼƬ��Ϣ CNend
     \attention \n
     if you want to get input format and input width and input height,you should set bOutInfo false.\n
     others you can get the information as follows: output rgb widht/height/stride/size or output \n
     yuvsp lu width/height/stride/size and ch width/height/stride/size.\n
     you call this function should after read header and set the ouput parameter.\n
     CNcomment:��bOutInfo���ó�FALSE��ʱ�򣬿��Ի�ȡ��ͼƬ����Ŀ�Ⱥ͸߶��Լ����ظ�ʽ�������ó�TRUE�� \n
               ʱ������Ի�ȡ��������Ϣ��Ҫ�ǽ���RGB���ȡ�����/�߶�/�м��/��С,Ҫ�ǽ������yuvsp��\n
               ����Ի�ȡ�����Ⱥ�ɫ�ȵĿ��/�߶�/�м��/��С����Ϣ�� CNend\n

     \param[in]    DecHandle. CNcomment:������� CNend
     \param[out]   pJpegInfo.  CNcomment:����jpeg�������Ϣ  CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_GetJpegInfo
     */
     HI_S32 HI_JPEG_GetJpegInfo(HI_ULONG DecHandle, HI_JPEG_INFO_S *pJpegInfo);

    /**
     \brief exit jpeg decode. CNcomment:�˳�jpeg ����CNend
     \attention \n
      when you want not to decode, call this function\n
      CNcomment:�����Ƿ��˳�����CNend\n
     \param[in] DecHandle. CNcomment:������� CNend
     \retval :: NA
     \see \n
      ::HI_JPEG_StopDec
    */
    HI_VOID HI_JPEG_StopDec(HI_ULONG DecHandle);

    /**
     \brief Sets dec output message. CNcomment:���ý����������Ϣ������ CNend
     \attention \n
     HI_JPEG_SetOutDesc should have called create jpeg decoder.set the output address \n
     and output stride,set whether crop, set crop rect \n
     CNcomment:�����ڴ���������֮����������֮ǰ���øýӿڣ���Ҫ���ý��������ַ����� \n
               �м�࣬�����Ƿ�ü��Լ���Ӧ�Ĳü����� CNend\n

     \param[in] DecHandle. CNcomment:������� CNend
     \param[in] *pstSurfaceDesc. CNcomment:�������������Ϣ CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_SetOutDesc
     */
     HI_S32 HI_JPEG_SetOutDesc(HI_ULONG DecHandle, const HI_JPEG_SURFACE_S *pstSurfaceDesc);

    /**
    \brief set stream mem information. CNcomment:���������ڴ���Ϣ CNend
    \attention \n
     if want to use this function,should call after jpeg_stdio_src or jpeg_mem_src\n
    CNcomment:���Ҫ���ã������ڹ�������֮��� CNend\n

    \param[in] DecHandle. CNcomment:������� CNend
    \param[in] StreamPhyAddr.       CNcomment:����buffer �ڴ����ʼ�����ַ CNend
    \param[in] StremBufSize.        CNcomment:����buffer �ڴ�ش�С         CNend
    \param[in] pFirstStreamVirBuf.  CNcomment: ��һ��buffer��ʼ��ַ          CNend
    \param[in] FirstStreamBufSize . CNcomment: ��һ������buffer ��С CNend
    \param[in] pSecondStreamVirBuf. CNcomment: �ڶ����ַ CNend
    \param[in] SecondStreamBufSize. CNcomment: �ڶ�������buffer ��С CNend

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
     \brief create decompress. CNcomment: ���������� CNend
     \attention \n
      create hard decompress\n
      CNcomment:���������� CNend\n
     \param[in] StreamPhyAddr �ڴ������������ʼ��ַ
     \param[in] TotalStremBufSize �ڴ�ش�С
     \param[in] pFirstStreamVirBuf ��һ��buffer��������ʼ��ַ
     \param[in] FirstStreamBufSize ��һ��buffer��С
     \param[in] pSecondStreamVirBuf �ڶ���buffer��������ʼ��ַ
     \param[in] SecondStreamBufSize �ڶ���buffer��С
     \retval :: decompress handle
     \see \n
      ::HI_JPEG_CreateDecompress
    */
    HI_ULONG HI_JPEG_CreateDecompress(HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,
                                      HI_CHAR* pFirstStreamVirBuf,HI_U32 FirstStreamBufSize,
                                      HI_CHAR* pSecondStreamVirBuf,HI_U32 SecondStreamBufSize);

    /**
     \brief destory decompress. CNcomment: ���ٽ����� CNend
     \attention \n
      destory hard decompress\n
      CNcomment:���ٽ����� CNend\n
     \param[in] DecHandle ������
     \retval :: NA
     \see \n
      ::HI_JPEG_DestroyDecompress
    */
    HI_VOID HI_JPEG_DestroyDecompress(HI_ULONG DecHandle);

    /**
     \brief scan lines. CNcomment: ��ɨ����� CNend
     \attention \n
      call this function after jpeg_start_decompress \n
      CNcomment:��ɨ����� CNend\n
     \param[in] cinfo �������
     \retval :: decompress handle
     \see \n
      ::HI_JPEG_StartDecompress
    */
    HI_S32 HI_JPEG_StartDecompress(HI_ULONG DecHandle);

    /**
     \brief Get Jpeg information. CNcomment:��ȡjpegͼƬ��Ϣ CNend
     \attention \n
           CNend\n
     \param[in]    DecHandle. CNcomment:������� CNend

     \retval ::HI_SUCCESS
     \retval ::HI_FAILURE

     \see \n
     ::HI_JPEG_ParseHeader
     */
    HI_S32 HI_JPEG_ParseHeader(HI_ULONG DecHandle);

    /**
    \brief set low delay information. CNcomment:���õ��ӳ���Ϣ,��ַ��СΪ8���ֽ� CNend
    \attention the s32LineNum value should in [1 ~ output height]\n
    NA.\n
    CNcomment:CNend\n

    \param[in]  DecHandle      CNcomment:�������                     CNend
    \param[in]  u32PhyLineBuf. CNcomment:�����к�������ַ             CNend
    \param[in]  pVirLineBuf.   CNcomment:�����к������ַ             CNend

    \retval ::HI_SUCCESS
    \retval ::HI_FAILURE

    \see \n
    ::HI_JPEG_SetLowDelayInf
    */
    HI_S32 HI_JPEG_SetLowDelayInf(HI_ULONG DecHandle, HI_U32 u32PhyLineBuf, HI_CHAR* pVirLineBuf);

    /**
     \brief set output color space information. CNcomment: ����ͼƬ���ɫ�ʿռ��ʽ CNend
     \attention \n
      call this function after jpeg_read_header\n
      CNcomment: ����ͼƬ���ɫ�ʿռ���Ϣ CNend\n
     \param[in] DecHandle ������
     \param[in] pstOutInfo ���ͼƬ��Ϣ
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
