/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_caption_osd.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/09/21
  Description   :
  History       :
  1.Date        : 2015/09/21
    Author      :
    Modification: Created file

******************************************************************************/
#ifndef LINUX_OS

#include <stdio.h>
#include <stdlib.h>

#include "OsdManager.h"
#include "caption_osd.h"

#define OSD_PRINT   ALOGE

#define OSD_CHECK_INIT()    \
do{                                 \
    if (g_om == HI_NULL)            \
    {                               \
        OSD_PRINT("not init!\n");   \
        return HI_FAILURE;          \
    }                               \
}while (0)

static android::OsdManager *g_om = HI_NULL;

static HI_S32 get_bytes_perpixel(CAPTION_OSD_PF_E enPF)
{
    switch(enPF)
    {
        case CAPTION_OSD_PF_8888:
            return 4;
        case CAPTION_OSD_PF_565:
        case CAPTION_OSD_PF_1555:
        case CAPTION_OSD_PF_4444:
            return 2;
        default:
            return 4;
    }

    return 4;
}

static HI_S32 convert_pixelformat_to_android(CAPTION_OSD_PF_E enPF)
{
    int pixelFormat = android::PIXEL_FORMAT_RGBA_8888;

    switch (enPF)
    {
        case CAPTION_OSD_PF_565:
            pixelFormat = android::PIXEL_FORMAT_RGB_565;
             break;

        case CAPTION_OSD_PF_1555:
            pixelFormat = android::PIXEL_FORMAT_RGBA_5551;
             break;

        case CAPTION_OSD_PF_4444:
            pixelFormat = android::PIXEL_FORMAT_RGBA_4444;
             break;

        case CAPTION_OSD_PF_8888:
            pixelFormat = android::PIXEL_FORMAT_RGBA_8888;
             break;

        default:
            OSD_PRINT("this pixel mode can not be supported: %d\n", enPF);
            break;
    }

     return pixelFormat;
}

static CAPTION_OSD_PF_E convert_pixelformat_to_osd(int pixelFormat)
{
    CAPTION_OSD_PF_E enPF = CAPTION_OSD_PF_8888;

    switch (pixelFormat)
    {
        case android::PIXEL_FORMAT_RGB_565:
            enPF = CAPTION_OSD_PF_565;
             break;

        case android::PIXEL_FORMAT_RGBA_5551:
            enPF = CAPTION_OSD_PF_1555;
             break;

        case android::PIXEL_FORMAT_RGBA_4444:
            enPF = CAPTION_OSD_PF_4444;
             break;

        case android::PIXEL_FORMAT_BGRA_8888:
            enPF = CAPTION_OSD_PF_8888;
             break;

        default:
            OSD_PRINT("this pixel mode can not be supported:%d\n", pixelFormat);
            break;
    }
     return enPF;
}

static HI_VOID convert_surfaceattr_to_osd(CAPTION_MGR_SURFACE_ATTR_S *pstMgrAttr, CAPTION_OSD_SURFACE_ATTR_S *pstOsdAttr)
{
    pstOsdAttr->enPixelFormat = convert_pixelformat_to_osd(pstMgrAttr->s32PixelFormat);
    pstOsdAttr->u32Width = pstMgrAttr->u32Width;
    pstOsdAttr->u32Height = pstMgrAttr->u32Height;
}

static HI_VOID convert_surfaceattr_to_mgr(CAPTION_OSD_SURFACE_ATTR_S *pstOsdAttr, CAPTION_MGR_SURFACE_ATTR_S *pstMgrAttr)
{
    pstMgrAttr->s32PixelFormat = convert_pixelformat_to_android(pstOsdAttr->enPixelFormat);
    pstMgrAttr->u32Width = pstOsdAttr->u32Width;
    pstMgrAttr->u32Height = pstOsdAttr->u32Height;
    pstMgrAttr->u32Stride = pstOsdAttr->u32Width * get_bytes_perpixel(pstOsdAttr->enPixelFormat);
}

static HI_VOID convert_cctextattr_to_mgr(CAPTION_OSD_CCTEXT_ATTR_S *pstOsdAttr, CAPTION_MGR_CCTEXT_ATTR_S *pstMgrAttr)
{

    memset(pstMgrAttr,0,sizeof(CAPTION_MGR_CCTEXT_ATTR_S));
    memcpy(pstMgrAttr, pstOsdAttr,sizeof(CAPTION_MGR_CCTEXT_ATTR_S));
}

static HI_VOID convert_cctextattr_to_osd(CAPTION_MGR_CCTEXT_ATTR_S *pstMgrAttr, CAPTION_OSD_CCTEXT_ATTR_S *pstOsdAttr)
{
    memset(pstOsdAttr, 0, sizeof(CAPTION_MGR_CCTEXT_ATTR_S));
    memcpy(pstOsdAttr, pstMgrAttr, sizeof(CAPTION_MGR_CCTEXT_ATTR_S));
}

HI_VOID caption_osd_init(HI_VOID)
{
    if (g_om != HI_NULL)
    {
        return;
    }

    g_om = new android::OsdManager();

    return;
}

HI_VOID caption_osd_deinit(HI_VOID)
{
    if (HI_NULL != g_om)
    {
        delete g_om;
        g_om = HI_NULL;
    }

    return;
}

HI_S32 caption_osd_create_surface(CAPTION_OSD_SURFACE_ATTR_S *pstAttr, HI_HANDLE *phSurface)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CAPTION_MGR_SURFACE_ATTR_S  stSurfaceAttr;

    OSD_CHECK_INIT();

    if (HI_NULL == pstAttr || HI_NULL == phSurface)
    {
        OSD_PRINT("pstAttr or phSurface is null!\n");

        return HI_FAILURE;
    }

    if (pstAttr->u32Width > 1920 || pstAttr->u32Height > 1080)
    {
        OSD_PRINT("pstAttr->u32Width or pstAttr->u32Height is invalid!\n");

        return HI_FAILURE;
    }

    convert_surfaceattr_to_mgr(pstAttr, &stSurfaceAttr);

    s32Ret = g_om->CreateSurface(&stSurfaceAttr, phSurface);

    return s32Ret;
}

HI_S32 caption_osd_destroy_surface(HI_HANDLE hSurface)
{
    OSD_CHECK_INIT();

    return g_om->DestroySurface(hSurface);
}

HI_S32 caption_osd_blit(HI_HANDLE hSrcSurface, HI_RECT_S *pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect)
{
    OSD_CHECK_INIT();

    return g_om->Blit(hSrcSurface, pstSrcRect, hDstSurface, pstDstRect);
}

HI_S32 caption_osd_fillrect(HI_HANDLE hSurface, CAPTION_OSD_SURFACE_ATTR_S *pstSurfaceAttr,HI_RECT_S *pstRect, HI_U32 u32Color)
{
    OSD_CHECK_INIT();

    CAPTION_MGR_SURFACE_ATTR_S  stSurfaceAttr;

    convert_surfaceattr_to_mgr(pstSurfaceAttr, &stSurfaceAttr);

    return g_om->FillCCRect(hSurface, &stSurfaceAttr, pstRect, u32Color);
}

HI_S32 caption_osd_refresh(HI_HANDLE hSurface)
{
    OSD_CHECK_INIT();

    return g_om->Refresh(hSurface);
}

HI_S32 caption_osd_clear_surface(HI_HANDLE hSurface)
{
    OSD_CHECK_INIT();

    return g_om->ClearSurface(hSurface);
}

HI_S32 caption_osd_cc_get_textsize(HI_CHAR* pTest,HI_S32 *pWidth, HI_S32 *pHeigh )
{
    OSD_CHECK_INIT();

    return g_om->GetCCTextSize(pTest, pWidth,pHeigh);
}

HI_S32 caption_osd_drawtext(HI_HANDLE hSurface, CAPTION_OSD_SURFACE_ATTR_S * pstSurfaceAttr,HI_RECT_S *pstRect, HI_CHAR *pTest, CAPTION_OSD_CCTEXT_ATTR_S * pstAttr)
{
    OSD_CHECK_INIT();

    CAPTION_MGR_CCTEXT_ATTR_S  stCCTextAtrr;
    CAPTION_MGR_SURFACE_ATTR_S stSurfaceAttr;

    convert_surfaceattr_to_mgr(pstSurfaceAttr, &stSurfaceAttr);
    convert_cctextattr_to_mgr(pstAttr,&stCCTextAtrr);

    return g_om->DrawCCText(hSurface, &stSurfaceAttr,pstRect, pTest, &stCCTextAtrr);
}

HI_S32 caption_osd_cc_blit(HI_HANDLE hSrcSurface, CAPTION_OSD_SURFACE_ATTR_S * pstSurfaceAttr,HI_RECT_S *pstSrcRect, HI_RECT_S *pstDstRect)
{

    OSD_CHECK_INIT();

    CAPTION_MGR_SURFACE_ATTR_S stSurfaceAttr;

    convert_surfaceattr_to_mgr(pstSurfaceAttr, &stSurfaceAttr);

    return g_om->CCBlit(hSrcSurface, &stSurfaceAttr, pstSrcRect, pstDstRect);
}

HI_S32 caption_osd_ttx_draw_bitmap(HI_HANDLE hSrcSurface, HI_U8 *bitmap,HI_RECT_S *pstSrcRect,HI_RECT_S *pstDstRect)
{
    OSD_CHECK_INIT();

    return g_om->TeletextDrawBitmap(hSrcSurface, bitmap,pstSrcRect,pstDstRect);
}

HI_S32 caption_osd_subt_draw_bitmap(HI_HANDLE hSrcSurface, HI_U8* bitmap, CAPTION_OSD_SURFACE_ATTR_S* pstAttr, HI_RECT_S* pstSrcRect)
{

    OSD_CHECK_INIT();

    HI_RECT_S stDstRect;

    stDstRect.s32Height = pstAttr->u32Height;
    stDstRect.s32Width = pstAttr->u32Width;
    stDstRect.s32X = 0;
    stDstRect.s32Y = 0;

    return g_om->SubDrawBitmap(hSrcSurface, bitmap, &stDstRect, pstSrcRect);
}

#endif
