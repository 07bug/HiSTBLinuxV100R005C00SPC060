/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : hi_gfx2d_api.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/
#ifndef _HI_GFX2D_API_H_
#define _HI_GFX2D_API_H_

#include "hi_gfx2d_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/********************************* API declaration *****************************/

/** \addtogroup      GFX2D API */
/** @{ */  /** <!-- ��GFX2D API�� */

/**
\brief Open device. CNcomment:���豸CNend
\attention \n
Call this interface to open gfx engine device before using it.\n
CNcomment:��Ҫʹ�ø��ļ��ṩ�Ľӿ�ʱ,�ȵ��ñ��ӿڴ��豸\n CNend

\param[in] enDevId Device id. CNcomment:�豸��CNend
\retval 0 success. CNcomment:�ɹ�CNend
\retval ::HI_ERR_GFX2D_INVALID_DEVID Invalid device id. CNcomment:����ȷ���豸��CNend
\retval ::HI_ERR_GFX2D_DEV_PERMISSION Failed to access to device. CNcomment:�����豸ʧ��CNend
\see \n
::HI_GFX2D_Close
 */
HI_S32 HI_GFX2D_Open(const HI_GFX2D_DEV_ID_E enDevId);

/**
\brief Close device. CNcomment:�ر��豸CNend
\attention \n
Call this interface to close gfx engine device.\n
Keep calling HI_GFX2D_Open and HI_GFX2D_Close in pairs.\n
CNcomment:���ñ��ӿڹر��豸\n
ʼ�ձ���HI_GFX2D_Open��HI_GFX2D_Close�ɶԵ���\n CNend

\param[in] enDevId Device id. CNcomment:�豸��CNend
\retval 0 success. CNcomment:�ɹ�CNend
\see \n
::HI_GFX2D_Open
 */
HI_S32 HI_GFX2D_Close(const HI_GFX2D_DEV_ID_E enDevId);

/**
\brief Submit sync compose task. CNcomment:�ύͬ����������CNend
\attention \n
Task submitted by this interface is sync.Returning success indicates the task is completed.If it returns timeout,the task will finish in future time.\n
The interface supports composing seven layers at most.\n
Six layers of them can support such color fmts:ARGB8888��ABGR8888��KRGB888��KBGR888��ARGB1555��RGB565��RGB888��BGR888��YUYV422��YVYU422��UYVY422��YYUV422��VYUY422��VUYY422��SEMIPLANAR420UV��SEMIPLANAR420VU��SEMIPLANAR422UV_H��SEMIPLANAR422VU_H��SEMIPLANAR422UV_V��SEMIPLANAR422VU_V��PLANAR400��PLANAR420��PLANAR411��PLANAR410��PLANAR422H��PLANAR422V��PLANAR444.\n
Lowest resolution supported is 1*1,highest is 2560*1600.\n
The other layer can support more color fmts:ARGB8888��ABGR8888��KRGB888��KBGR888��ARGB1555��RGB565��RGB888��BGR888
Lowest resolution supported by this layer is 32*32,highest is 2560*1600.\n
This layer only supportes mem type surface.
In addition,this layer supports zoom.Horizontal deflate ratio shoule be less than 256, vertical should be less than 16.There is no limit to magnify ratio.\n
Output fmt supported by this interface is:ARGB8888��ABGR8888��ARGB1555��RGB888��BGR888��SEMIPLANAR420UV.\n
If the output fmt is ARGB8888,setting the compression of dst surface will enable compression.In this case,mem size and stride of dst surface should be get by calling HI_GFX2D_GetCmpSurfaceStride and HI_GFX2D_GetCmpSurfaceSize,and width of dst surface should be even.\n
If the output fmt is SEMIPLANAR420UV, setting the histogram addr of dst surface will enable histogram stat.Size of histogram mem is 64byte.
Stride of surface should be 16 byte aligned.
Colorkey and ROP are both not supported.

CNcomment:�ýӿ��ύ����ͬ������,���سɹ�����ʾ�ύ���������,�����س�ʱ,��������ڽ�����ĳ��ʱ����ɣ����ᶪ��\n
������֧��7�����\n
��������֧�ֵ������ʽΪ:ARGB8888��ABGR8888��KRGB888��KBGR888��ARGB1555��RGB565��RGB888��BGR888\n
֧�ֵ�����ֱ�����СΪ1*1,���2560*1600\n
����һ����֧�ֵ������ʽΪ:\n
ARGB8888��ABGR8888��KRGB888��KBGR888��ARGB1555��RGB565��RGB888��BGR888\n
YUYV422��YVYU422��UYVY422��YYUV422��VYUY422��VUYY422\n
SEMIPLANAR420UV��SEMIPLANAR420VU��SEMIPLANAR422UV_H��SEMIPLANAR422VU_H��SEMIPLANAR422UV_V��SEMIPLANAR422VU_V\n
PLANAR400��PLANAR420��PLANAR411��PLANAR410��PLANAR422H��PLANAR422V��PLANAR444\n
֧�ֵ�����ֱ�����СΪ32*32,���2560*1600\n
�ò�ֻ֧��mem���͵�����surface\n
�ò�֧������:ˮƽ�����С����Ϊ256(����)����ֱ�����С����Ϊ16(����)���Ŵ�������\n
֧�ֵ������ʽΪ:\n
ARGB8888��ABGR8888��ARGB1555��RGB888��BGR888��SEMIPLANAR420UV\n
�����ARGB8888��ʽʱ������֧�ֶ�������ݽ���ѹ������ʱ�����surface��stride����Ҫ���ڴ�\n
��С���ѹ��ʱ�в��죬��Ҫͨ��HI_GFX2D_GetCmpSurfaceStride��HI_GFX2D_GetCmpSurfaceSize����ȡ\n
���ѹ��ʱ��Ҫ������Ŀ��Ϊż��\n
�����SEMIPLANAR420UVʱ��֧�ֻ�ȡ�������Y������ֱ��ͼ������Ҫ��ȡֱ��ͼ��Ϣ����Ҫ�����surface\n
��ָ��64byte��С�ڴ���׵�ַ\n
���롢�����strideҪ��16byte����\n
��֧��colorkey����\n
��֧��ROP����\n
��֧������surfaceΪѹ�����͵�surface\n
����Color���͵�surface,���ʽ�̶�ΪARGB8888,colorֵ����ARGB8888������\n
��ʱֵ����Ϊ0����һֱ�ȴ�ֱ���������\nCNend

\param[in]  enDevId Device id. CNcomment:�豸��CNend
\param[in]  pstComposeList Input surface list. CNcomment:����surface����CNend
\param[in]  pstDst Dst surface. CNcomment:Ŀ��surfaceCNend
\param[in]  u32Timeout Timeout value,measured in ms. CNcomment:��ʱֵ������Ϊ��λCNend

\retval 0 Success. CNcomment:�ɹ�CNend
\retval ::HI_ERR_GFX2D_INVALID_DEVID Invalid device id. CNcomment:����ȷ���豸��CNend
\retval ::HI_ERR_GFX2D_DEV_NOT_OPEN Device not opened. CNcomment:�豸δ��CNend
\retval ::HI_ERR_GFX2D_NULL_PTR Null pointer param. CNcomment:��ָ�����CNend
\retval ::HI_ERR_GFX2D_INVALID_COMPOSECNT Invalid input surface count. CNcomment:����ȷ������surface����CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_TYPE Invalid surface type. CNcomment:����ȷ��surface����CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_RESO Invalid surface resolution. CNcomment:����ȷ��surface�ֱ���CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_FMT Invalid surface color format. CNcomment:����ȷ��surface���ظ�ʽCNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_ADDR Invalid surface addr. CNcomment:����ȷ��surface��ַCNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_STRIDE Invalid surface stride. CNcomment:����ȷ��surface�м��CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_CMPTYPE Invalid surface cmpression type. CNcomment:����ȷ��ѹ������CNend
\retval ::HI_ERR_GFX2D_INVALID_RECT Invalid operation rect. CNcomment:����ȷ�Ĳ�������CNend
\retval ::HI_ERR_GFX2D_INVALID_RESIZE_FILTERMODE Invalid filter mode. CNcomment:����ȷ���˲�ģʽCNend
\retval ::HI_ERR_GFX2D_INVALID_RESIZE_RATIO Invalid resize ratio. CNcomment:����ȷ�����ű�CNend
\retval ::HI_ERR_GFX2D_INVALID_CLIP_MODE Invalid clip mode. CNcomment:����ȷ�ļ���ģʽCNend
\retval ::HI_ERR_GFX2D_INVALID_CLIP_RECT Invalid clip rect. CNcomment:����ȷ�ļ��о���CNend
\retval ::HI_ERR_GFX2D_UNSUPPORT Unsupport operation. CNcomment:��֧�ֵĲ���CNend
\retval ::HI_ERR_GFX2D_NO_MEM Mem is not enough. CNcomment:�ڴ治��CNend
\retval ::HI_ERR_GFX2D_TIMEOUT Task is not finished in appointed time. CNcomment:����δ��ָ���ĳ�ʱʱ�������CNend

 \see \n
::HI_GFX2D_ComposeAsync
 */
HI_S32 HI_GFX2D_ComposeSync(const HI_GFX2D_DEV_ID_E enDevId,
                            HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                            HI_GFX2D_SURFACE_S *pstDst,
                            const HI_U32 u32Timeout);



/**
\brief show sdk version. CNcomment:�ύ�첽��������\n CNend
\attention \n
\n
CNcomment:�ýӿ��ύ�����첽���񣬷��سɹ�������������������ɲο��ӿ�HI_GFX2D_ComposeSync CNend\n

\param[in]  enDevId Device id. CNcomment:�豸��CNend
\param[in]  pstComposeList Input surface list. CNcomment:����surface����CNend
\param[in]  pstDst Dst surface. CNcomment:Ŀ��surfaceCNend

\retval 0 Success. CNcomment:�ɹ�CNend
\retval ::HI_ERR_GFX2D_INVALID_DEVID Invalid device id. CNcomment:����ȷ���豸��CNend
\retval ::HI_ERR_GFX2D_DEV_NOT_OPEN Device not opened. CNcomment:�豸δ��CNend
\retval ::HI_ERR_GFX2D_NULL_PTR Null pointer param. CNcomment:��ָ�����CNend
\retval ::HI_ERR_GFX2D_INVALID_COMPOSECNT Invalid input surface count. CNcomment:����ȷ������surface����CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_TYPE Invalid surface type. CNcomment:����ȷ��surface����CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_RESO Invalid surface resolution. CNcomment:����ȷ��surface�ֱ���CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_FMT Invalid surface color format. CNcomment:����ȷ��surface���ظ�ʽCNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_ADDR Invalid surface addr. CNcomment:����ȷ��surface��ַCNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_STRIDE Invalid surface stride. CNcomment:����ȷ��surface�м��CNend
\retval ::HI_ERR_GFX2D_INVALID_SURFACE_CMPTYPE Invalid surface cmpression type. CNcomment:����ȷ��ѹ������CNend
\retval ::HI_ERR_GFX2D_INVALID_RECT Invalid operation rect. CNcomment:����ȷ�Ĳ�������CNend
\retval ::HI_ERR_GFX2D_INVALID_RESIZE_FILTERMODE Invalid filter mode. CNcomment:����ȷ���˲�ģʽCNend
\retval ::HI_ERR_GFX2D_INVALID_RESIZE_RATIO Invalid resize ratio. CNcomment:����ȷ�����ű�CNend
\retval ::HI_ERR_GFX2D_INVALID_CLIP_MODE Invalid clip mode. CNcomment:����ȷ�ļ���ģʽCNend
\retval ::HI_ERR_GFX2D_INVALID_CLIP_RECT Invalid clip rect. CNcomment:����ȷ�ļ��о���CNend
\retval ::HI_ERR_GFX2D_UNSUPPORT Unsupport operation. CNcomment:��֧�ֵĲ���CNend
\retval ::HI_ERR_GFX2D_NO_MEM Mem is not enough. CNcomment:�ڴ治��CNend

 \see \n
::HI_GFX_ComposeSync
 */
HI_S32 HI_GFX2D_ComposeAsync(const HI_GFX2D_DEV_ID_E enDevId,
                             HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                             HI_GFX2D_SURFACE_S *pstDst);

/**
\brief Wait all tasks submitted finished. CNcomment:�ȴ������������CNend
\attention \n
If u32Timeout is zero,the interface will wait forever until tasks are finished.\n
CNcomment:��u32Timeout��ֵΪ0ʱ����һֱ�ȴ�ֱ���������\n CNend
\param[in]  enDevId Device id. CNcomment:�豸��CNend
\param[in]  u32TimeOut Timeout value,measured in ms. CNcomment:��ʱֵ,��λΪ����CNend
\retval 0 Success. CNcomment:�ɹ�CNend
\retval ::HI_ERR_GFX2D_INVALID_DEVID Invalid device id. CNcomment:����ȷ���豸��CNend
\retval ::HI_ERR_GFX2D_DEV_NOT_OPEN Device not opened. CNcomment:�豸δ��CNend
\retval ::HI_ERR_GFX2D_TIMEOUT Tasks are not finished in appointed time. CNcomment:����δ��ָ���ĳ�ʱʱ�������CNend
\see N/A
*/
HI_S32 HI_GFX2D_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId, const HI_U32 u32TimeOut);


#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/


#endif  /*_HI_GFX2D_API_H_*/
