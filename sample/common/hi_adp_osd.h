/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_adp_osd.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/02/18
  Description   :
  History       :
  1.Date        : 2014/02/18
    Author      :  
    Modification: Created file

******************************************************************************/

#ifndef _HI_ADP_OSD_H_
#define _HI_ADP_OSD_H_

#include "hi_type.h"
#include "hi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    HIADP_PF_CLUT8 = 0,  /**<Palette*//**<CNcomment:��ɫ�� */
    HIADP_PF_CLUT1,
    HIADP_PF_CLUT4,
    HIADP_PF_4444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ��������� */
    HIADP_PF_0444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ���������, A������������ */

    HIADP_PF_1555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ��������� */
    HIADP_PF_0555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ���������, A������������ */
    HIADP_PF_565,        /**<Each pixel occupies 16 bits, and the R/G/B components each occupies 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��RGBÿ�����ֱ�ռ5bit��6bit��5bit������ַ�ɸ��������� */
    HIADP_PF_8565,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits, 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:һ������ռ24bit��ARGBÿ�����ֱ�ռ8bit, 5bit��6bit��5bit������ַ�ɸ��������� */
    HIADP_PF_8888,       /**<Each pixel occupies 32 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order.*//**<CNcomment:һ������ռ32bit��ARGBÿ����ռ8bit������ַ�ɸ��������� */
    HIADP_PF_0888,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ24bit��ARGBÿ����ռ8bit������ַ�ɸ��������У�A������������ */

    HIADP_PF_YUV400,     /**<Semi-planar YUV 400 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 400��ʽ */
    HIADP_PF_YUV420,     /**<Semi-planar YUV 420 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 420��ʽ */
    HIADP_PF_YUV422,     /**<Semi-planar YUV 422 format and horizontal sampling format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 422��ʽ  ˮƽ������ʽ*/
    HIADP_PF_YUV422_V,   /**<Semi-planar YUV 422 format and vertical sampling format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 422��ʽ  ��ֱ������ʽ*/
    HIADP_PF_YUV444,     /**<Semi-planar YUV 444 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 444��ʽ */

    HIADP_PF_A1,
    HIADP_PF_A8,

    HIADP_PF_YUV888,
    HIADP_PF_YUV8888,
    HIADP_PF_RLE8,
    HIADP_PF_BUTT
} HIADP_PF_E;

typedef struct tagHIADP_SURFACE_ATTR_S
{
    HIADP_PF_E          enPixelFormat;
    HI_U32              u32Width;
    HI_U32              u32Height;

}HIADP_SURFACE_ATTR_S;

typedef struct tagHIADP_CCTEXT_ATTR_S
{
    HI_U32       u32BufLen;

    HI_U32       u32bgColor;
    HI_U32       u32fgColor;
    HI_U32       u32edgeColor;

    HI_U8        u8justify;
    HI_U32       u8WordWrap;

    HI_U32       u8fontstyle;
    HI_U32       u8fontSize;
    HI_U32       u8edgeType;

    HI_BOOL      bUnderline;
    HI_BOOL      bItalic;

}HIADP_CCTEXT_ATTR_S;

HI_VOID HIADP_OSD_Init(HI_VOID);

HI_VOID HIADP_OSD_DeInit(HI_VOID);

HI_S32 HIADP_OSD_CreateSurface(HIADP_SURFACE_ATTR_S *pstAttr, HI_HANDLE *phSurface);

HI_S32 HIADP_OSD_DestroySurface(HI_HANDLE hSurface);

HI_S32 HIADP_OSD_Blit(HI_HANDLE hSrcSurface, HI_RECT_S *pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect);

HI_S32 HIADP_OSD_BlitFrameToSurface(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect);

HI_S32 HIADP_OSD_FillRect(HI_HANDLE hSurface, HI_RECT_S *pstRect, HI_U32 u32Color);

HI_S32 HIADP_OSD_Refresh(HI_HANDLE hSurface);

HI_S32 HIADP_OSD_ClearSurface(HI_HANDLE hSurface);

// Only support jpg:1
HI_S32 HIADP_OSD_EncodeFrame(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_S32 EncodeType, HI_CHAR *DstFile);

HI_S32 HIADP_OSD_GetCCTextSize(HI_CHAR* pTest,HI_S32 *pWidth, HI_S32 *pHeigh );

HI_S32 HIADP_OSD_FillCCRect(HI_HANDLE hSurface, HIADP_SURFACE_ATTR_S *pstSurfaceAttr,HI_RECT_S *pstRect, HI_U32 u32Color);

HI_S32 HIADP_OSD_DrawCCText(HI_HANDLE hSurface, HIADP_SURFACE_ATTR_S *pstSurfaceAttr,HI_RECT_S *pstRect, HI_CHAR *pTest,HIADP_CCTEXT_ATTR_S * pstAttr);

HI_S32 HIADP_OSD_CCBlit(HI_HANDLE hSrcSurface, HIADP_SURFACE_ATTR_S *pstSurfaceAttr, HI_RECT_S *pstSrcRect, HI_RECT_S *pstDstRect);

HI_S32 HIADP_OSD_TeletextDrawBitmap(HI_HANDLE hSrcSurface, HI_U8 *bitmap,HI_RECT_S *pstSrcRect,HI_RECT_S *pstDstRect);

HI_S32 HIADP_OSD_SubDrawBitmap(HI_HANDLE hSrcSurface, HI_U8 *bitmap,HIADP_SURFACE_ATTR_S *pstAttr,HI_RECT_S *pstSrcRect);

#ifdef __cplusplus
}
#endif

#endif
