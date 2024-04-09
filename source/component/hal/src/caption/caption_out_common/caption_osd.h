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
    CAPTION_OSD_PF_CLUT8 = 0,  /**<Palette*//**<CNcomment:调色板 */
    CAPTION_OSD_PF_CLUT1,
    CAPTION_OSD_PF_CLUT4,
    CAPTION_OSD_PF_4444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order.*//**<CNcomment:一个像素占16bit，ARGB每分量占4bit，按地址由高至低排列 */
    CAPTION_OSD_PF_0444,       /**<Each pixel occupies 16 bits, and the A/R/G/B components each occupies 4 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:一个像素占16bit，ARGB每分量占4bit，按地址由高至低排列, A分量不起作用 */

    CAPTION_OSD_PF_1555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order.*//**<CNcomment:一个像素占16bit，RGB每分量占5bit，A分量1bit，按地址由高至低排列 */
    CAPTION_OSD_PF_0555,       /**<Each pixel occupies 16 bits, the R/G/B components each occupies 5 bits, and the A component occupies 1 bit. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:一个像素占16bit，RGB每分量占5bit，A分量1bit，按地址由高至低排列, A分量不起作用 */
    CAPTION_OSD_PF_565,        /**<Each pixel occupies 16 bits, and the R/G/B components each occupies 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:一个像素占16bit，RGB每分量分别占5bit、6bit和5bit，按地址由高至低排列 */
    CAPTION_OSD_PF_8565,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits, 5 bits, 6 bits, and 5 bits respectively. They are sorted by address in descending order.*//**<CNcomment:一个像素占24bit，ARGB每分量分别占8bit, 5bit、6bit和5bit，按地址由高至低排列 */
    CAPTION_OSD_PF_8888,       /**<Each pixel occupies 32 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order.*//**<CNcomment:一个像素占32bit，ARGB每分量占8bit，按地址由高至低排列 */
    CAPTION_OSD_PF_0888,       /**<Each pixel occupies 24 bits, and the A/R/G/B components each occupies 8 bits. They are sorted by address in descending order. The A component does not take effect.*//**<CNcomment:一个像素占24bit，ARGB每分量占8bit，按地址由高至低排列，A分量不起作用 */

    CAPTION_OSD_PF_YUV400,     /**<Semi-planar YUV 400 format defined by HiSilicon*//**<CNcomment:海思定义的semi-planar YUV 400格式 */
    CAPTION_OSD_PF_YUV420,     /**<Semi-planar YUV 420 format defined by HiSilicon*//**<CNcomment:海思定义的semi-planar YUV 420格式 */
    CAPTION_OSD_PF_YUV422,     /**<Semi-planar YUV 422 format and horizontal sampling format defined by HiSilicon*//**<CNcomment:海思定义的semi-planar YUV 422格式  水平采样格式*/
    CAPTION_OSD_PF_YUV422_V,   /**<Semi-planar YUV 422 format and vertical sampling format defined by HiSilicon*//**<CNcomment:海思定义的semi-planar YUV 422格式  垂直采样格式*/
    CAPTION_OSD_PF_YUV444,     /**<Semi-planar YUV 444 format defined by HiSilicon*//**<CNcomment:海思定义的semi-planar YUV 444格式 */

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
