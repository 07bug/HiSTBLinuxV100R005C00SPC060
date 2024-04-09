/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_adp_osd.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/09/21
  Description   :
  History       :
  1.Date        : 2015/09/21
    Author      :
    Modification: Created file

******************************************************************************/

#ifndef _HI_CAPTION_OSD_H_
#define _HI_CAPTION_OSD_H_

#ifndef LINUX_OS

#include "hi_type.h"
#include "hi_common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CAPTION_OSD_PF_CLUT8 = 0,  /**<Palette*//**<CNcomment:��ɫ�� */
    CAPTION_OSD_PF_CLUT1,
    CAPTION_OSD_PF_CLUT4,
    CAPTION_OSD_PF_4444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ��������� */
    CAPTION_OSD_PF_0444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ16bit��ARGBÿ����ռ4bit������ַ�ɸ���������, A������������ */

    CAPTION_OSD_PF_1555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ��������� */
    CAPTION_OSD_PF_0555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ16bit��RGBÿ����ռ5bit��A����1bit������ַ�ɸ���������, A������������ */
    CAPTION_OSD_PF_565,        /**<Each pixel occupies 16 bits, and the R/G/B components each occupies 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:һ������ռ16bit��RGBÿ�����ֱ�ռ5bit��6bit��5bit������ַ�ɸ��������� */
    CAPTION_OSD_PF_8565,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits, 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:һ������ռ24bit��ARGBÿ�����ֱ�ռ8bit, 5bit��6bit��5bit������ַ�ɸ��������� */
    CAPTION_OSD_PF_8888,       /**<Each pixel occupies 32 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order.*//**<CNcomment:һ������ռ32bit��ARGBÿ����ռ8bit������ַ�ɸ��������� */
    CAPTION_OSD_PF_0888,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:һ������ռ24bit��ARGBÿ����ռ8bit������ַ�ɸ��������У�A������������ */

    CAPTION_OSD_PF_YUV400,     /**<Semi-planar YUV 400 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 400��ʽ */
    CAPTION_OSD_PF_YUV420,     /**<Semi-planar YUV 420 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 420��ʽ */
    CAPTION_OSD_PF_YUV422,     /**<Semi-planar YUV 422 format and horizontal sampling format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 422��ʽ  ˮƽ������ʽ*/
    CAPTION_OSD_PF_YUV422_V,   /**<Semi-planar YUV 422 format and vertical sampling format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 422��ʽ  ��ֱ������ʽ*/
    CAPTION_OSD_PF_YUV444,     /**<Semi-planar YUV 444 format defined by HiSilicon*//**<CNcomment:��˼�����semi-planar YUV 444��ʽ */

    CAPTION_OSD_PF_A1,
    CAPTION_OSD_PF_A8,

    CAPTION_OSD_PF_YUV888,
    CAPTION_OSD_PF_YUV8888,
    CAPTION_OSD_PF_RLE8,
    CAPTION_OSD_PF_BUTT
} CAPTION_OSD_PF_E;

typedef struct tagCAPTION_OSD_SURFACE_ATTR_S
{
    CAPTION_OSD_PF_E   enPixelFormat;
    HI_U32         u32Width;
    HI_U32         u32Height;

}CAPTION_OSD_SURFACE_ATTR_S;

typedef struct tagCAPTION_OSD_CCTEXT_ATTR_S
{
    HI_U32   u32BufLen;

    HI_U32   u32bgColor;
    HI_U32   u32fgColor;
    HI_U32   u32edgeColor;

    HI_U8    u8justify;
    HI_U32   u8WordWrap;

    HI_U32   u8fontstyle;
    HI_U32   u8fontSize;
    HI_U32   u8edgeType;

    HI_BOOL  bUnderline;
    HI_BOOL  bItalic;

}CAPTION_OSD_CCTEXT_ATTR_S;

HI_VOID caption_osd_init(HI_VOID);

HI_VOID caption_osd_deinit(HI_VOID);

HI_S32 caption_osd_create_surface(CAPTION_OSD_SURFACE_ATTR_S *pstAttr, HI_HANDLE *phSurface);

HI_S32 caption_osd_destroy_surface(HI_HANDLE hSurface);

HI_S32 caption_osd_blit(HI_HANDLE hSrcSurface, HI_RECT_S *pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect);

HI_S32 caption_osd_fillrect(HI_HANDLE hSurface, CAPTION_OSD_SURFACE_ATTR_S *pstSurfaceAttr,HI_RECT_S *pstRect, HI_U32 u32Color);

HI_S32 caption_osd_refresh(HI_HANDLE hSurface);

HI_S32 caption_osd_clear_surface(HI_HANDLE hSurface);

HI_S32 caption_osd_cc_get_textsize(HI_CHAR* pTest,HI_S32 *pWidth, HI_S32 *pHeigh );

HI_S32 caption_osd_drawtext(HI_HANDLE hSurface, CAPTION_OSD_SURFACE_ATTR_S *pstSurfaceAttr,HI_RECT_S *pstRect, HI_CHAR *pTest,CAPTION_OSD_CCTEXT_ATTR_S * pstAttr);

HI_S32 caption_osd_cc_blit(HI_HANDLE hSrcSurface, CAPTION_OSD_SURFACE_ATTR_S *pstSurfaceAttr, HI_RECT_S *pstSrcRect, HI_RECT_S *pstDstRect);

HI_S32 caption_osd_ttx_draw_bitmap(HI_HANDLE hSrcSurface, HI_U8 *bitmap,HI_RECT_S *pstSrcRect,HI_RECT_S *pstDstRect);

HI_S32 caption_osd_subt_draw_bitmap(HI_HANDLE hSrcSurface, HI_U8 *bitmap,CAPTION_OSD_SURFACE_ATTR_S *pstAttr,HI_RECT_S *pstSrcRect);

#ifdef __cplusplus
}
#endif

#endif
#endif
