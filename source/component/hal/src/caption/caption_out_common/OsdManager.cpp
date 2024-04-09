/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : OsdManager.c
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

#include "OsdManager.h"
#include <utils/Log.h>

#include "hi_type.h"
#include "hi_jpge_api.h"
#include "hi_jpge_type.h"
#include "hi_jpge_errcode.h"
#include "hi_common.h"

#ifdef ANDROIDO
    #include "SkRegion.h"
//  #include "SkPaint.h"
//  #include "SkTypeface.h"
//  #include "sk_tool_utils.h"
#endif

#define CC_FONT_FILE_SERIF "serif"
#define CC_FONT_FILE_MONOSPACE "monospace"

namespace android
{

    //pixel byte
    const HI_U8 CAPTION_PIXBYTE = 4;

    static HI_VOID InitDispSurface(CAPTION_MGR_DISP_SURFACE_S* pstSurface)
    {
        pstSurface->hSurface = HI_INVALID_HANDLE;
        pstSurface->stAttr.u32Width = SURFACE_DEFAULT_WIDTH;
        pstSurface->stAttr.u32Height = SURFACE_DEFAULT_HEIGHT;
        pstSurface->stAttr.s32PixelFormat = PIXEL_FORMAT_RGBA_8888;
        pstSurface->stAttr.u32Stride = SURFACE_DEFAULT_WIDTH * CAPTION_PIXBYTE;
    }

    static TDE2_COLOR_FMT_E FORMAT_TO_TDE(int aformat)
    {
        TDE2_COLOR_FMT_E tdeformat = TDE2_COLOR_FMT_ARGB8888;
        switch(aformat)
        {
            case PIXEL_FORMAT_RGBA_8888:
                tdeformat = TDE2_COLOR_FMT_ARGB8888;
                break;
            case PIXEL_FORMAT_RGB_565:
                tdeformat = TDE2_COLOR_FMT_RGB565;
                break;
            case PIXEL_FORMAT_RGBA_5551:
                tdeformat = TDE2_COLOR_FMT_ARGB1555;
                break;
            case PIXEL_FORMAT_RGBA_4444:
                tdeformat = TDE2_COLOR_FMT_ARGB4444;
                break;
            default:
                tdeformat = TDE2_COLOR_FMT_ARGB8888;
        }

        return tdeformat;
    }

    static int tde_bytepp(int fmt)
    {
        switch(fmt)
        {
            case TDE2_COLOR_FMT_ARGB8888:
                return 4;

            case TDE2_COLOR_FMT_ABGR8888:
                return 4;

            case TDE2_COLOR_FMT_RGB888:
                return 3;

            case TDE2_COLOR_FMT_RGB565:
            case TDE2_COLOR_FMT_ARGB1555:
            case TDE2_COLOR_FMT_ARGB4444:
                return 2;
        }

        return 4;
    }

    OsdManager::OsdManager()
    {
        HI_U32  i;

        for (i = 0; i < MAX_SURFACE_NUM; i++)
        {
            // display surface source
            memset(&m_DispSurface[i], 0x0, sizeof(CAPTION_MGR_DISP_SURFACE_S));

            InitDispSurface(&m_DispSurface[i]);
        }

        HI_TDE2_Open();

        pPixels = HI_NULL;
    }

    OsdManager::~OsdManager()
    {
        HI_TDE2_Close();

        if (HI_NULL != pPixels)
        {
            free(pPixels);
        }
    }

    CAPTION_MGR_DISP_SURFACE_S* OsdManager::GetSurfaceInst(HI_HANDLE hSurface)
    {
        HI_U32 i = 0;

        for (i = 0; i < MAX_SURFACE_NUM; i++)
        {
            if (m_DispSurface[i].hSurface == hSurface)
            {
                return &(m_DispSurface[i]);
            }
        }

        return HI_NULL;
    }

    HI_S32 OsdManager::CreateSurface(CAPTION_MGR_SURFACE_ATTR_S* pstAttr, HI_HANDLE* phSurface)
    {
        HI_U32 i;

        for (i = 0; i < MAX_SURFACE_NUM; i++)
        {
            if (m_DispSurface[i].hSurface == HI_INVALID_HANDLE)
            {
                break;
            }
        }

        if (i == MAX_SURFACE_NUM)
        {
            ALOGE("there is no free display surface!\n");
            return HI_FAILURE;
        }

        // create new display surface
        m_DispSurface[i].Client = new SurfaceComposerClient();

        m_DispSurface[i].surfaceControl = (m_DispSurface[i].Client)->createSurface(String8("hisiSurfaceDemo"), pstAttr->u32Width, pstAttr->u32Height, pstAttr->s32PixelFormat, 0);

        m_DispSurface[i].surface = (m_DispSurface[i].surfaceControl)->getSurface();

        SurfaceComposerClient::openGlobalTransaction();
        (m_DispSurface[i].surfaceControl)->setLayer(300000 + i);
        (m_DispSurface[i].surfaceControl)->setPosition(0, 0);

        (m_DispSurface[i].surfaceControl)->setFlags(0x20, 0x20);

        SurfaceComposerClient::closeGlobalTransaction();

        m_DispSurface[i].Window = m_DispSurface[i].surface.get();

        m_DispSurface[i].WindowBuffer = HI_NULL;

        memcpy(&(m_DispSurface[i].stAttr), pstAttr, sizeof(CAPTION_MGR_SURFACE_ATTR_S));

        m_DispSurface[i].hSurface = SURFACE_HANDLE_INDEX | i;

        *phSurface = m_DispSurface[i].hSurface;

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::DestroySurface(HI_HANDLE hSurface)
    {
        CAPTION_MGR_DISP_SURFACE_S*      pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        InitDispSurface(pSurface);

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::ClearSurface(HI_HANDLE hSurface)
    {
        CAPTION_MGR_DISP_SURFACE_S*      pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if (pSurface->WindowBuffer == HI_NULL)
        {
            lock(hSurface);
        }

        if(HI_NULL != pSurface->VirtualAddr)
        {
            memset(pSurface->VirtualAddr, 0x0, pSurface->stAttr.u32Stride * pSurface->stAttr.u32Height);
        }

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::lock(HI_HANDLE hSurface)
    {
        CAPTION_MGR_DISP_SURFACE_S*      pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        native_window_dequeue_buffer_and_wait(pSurface->Window, &(pSurface->WindowBuffer));
        if (NULL == pSurface->WindowBuffer)
        {
            ALOGE("NULL == pSurface->WindowBuffer ");
            return HI_FAILURE;
        }

        GraphicBufferMapper& mapper = GraphicBufferMapper::get();

        Rect bounds(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height);

        private_handle_t* priv_hnd = (private_handle_t*)((pSurface->WindowBuffer)->handle);

        if (HI_NULL != priv_hnd)
        {
            pSurface->PhyAddr = priv_hnd->ion_phy_addr;
        }
        else
        {
            ALOGE("disp surface, priv_hnd is null!\n");
            return HI_FAILURE;
        }

        mapper.lock((pSurface->WindowBuffer)->handle, GRALLOC_USAGE_SW_WRITE_OFTEN, bounds, &(pSurface->VirtualAddr));

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::unLock(HI_HANDLE hSurface)
    {
        CAPTION_MGR_DISP_SURFACE_S*      pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        GraphicBufferMapper& mapper = GraphicBufferMapper::get();

        mapper.unlock((pSurface->WindowBuffer)->handle);

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::FillRect(HI_HANDLE hSurface, HI_RECT_S* pstRect, HI_U32 u32Color)
    {
        TDE_HANDLE          s32Handle = 0;
        HI_S32              s32Ret = 0;
        TDE2_SURFACE_S      stDst;
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if (pSurface->WindowBuffer == HI_NULL)
        {
            lock(hSurface);
        }

        memset(&stDst, 0, sizeof(TDE2_SURFACE_S));

        stDst.u32Width  = pSurface->stAttr.u32Width;
        stDst.u32Height = pSurface->stAttr.u32Height;
        stDst.u32Stride = pSurface->stAttr.u32Stride;
        stDst.enColorFmt = FORMAT_TO_TDE(pSurface->stAttr.s32PixelFormat);;
        stDst.u32PhyAddr = pSurface->PhyAddr;

        stDst.bAlphaMax255 = HI_TRUE;

        s32Handle = HI_TDE2_BeginJob();

        if (HI_ERR_TDE_INVALID_HANDLE == s32Handle)
        {
            ALOGE("Fail to create Job.\n");
            return HI_FAILURE;
        }

        TDE2_RECT_S TdeRect;
        TdeRect.s32Xpos = pstRect->s32X;
        TdeRect.s32Ypos = pstRect->s32Y;
        TdeRect.u32Width = pstRect->s32Width;
        TdeRect.u32Height = pstRect->s32Height;

        s32Ret = HI_TDE2_QuickFill(s32Handle, &stDst, &TdeRect, u32Color);

        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("HI_TDE2_QuickFill failed!\n");
            HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 1000);
            return HI_FAILURE;
        }

        s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 1000);

        if (HI_SUCCESS != s32Ret)
        {
            ALOGE("Fail to End Job. ret=%p\n", (void*)s32Ret);
            return HI_FAILURE;
        }

        s32Ret = HI_TDE2_WaitForDone(s32Handle);

        if (HI_ERR_TDE_QUERY_TIMEOUT == s32Ret)
        {
            ALOGE("wait for done time out");
            return HI_FAILURE;
        }

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::Refresh(HI_HANDLE hSurface)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if (HI_NULL != pSurface->WindowBuffer)
        {
            unLock(hSurface);

            // show
            (pSurface->Window)->queueBuffer(pSurface->Window, pSurface->WindowBuffer, -1);
        }

        pSurface->WindowBuffer = HI_NULL;

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::Blit(HI_HANDLE hSrcSurface, HI_RECT_S* pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S* pstDstRect)
    {
        HI_S32              Ret;
        CAPTION_MGR_DISP_SURFACE_S*  pSrcSurface, *pDstSurface;

        TDE2_SURFACE_S      stSrc;
        TDE2_SURFACE_S      stDst;
        TDE_HANDLE          s32Handle = 0;
        TDE2_OPT_S          stOpt;

        TDE2_RECT_S         srcRect = {0, 0, 0, 0};
        TDE2_RECT_S         dstRect = {0, 0, 0, 0};

        pSrcSurface = GetSurfaceInst(hSrcSurface);

        pDstSurface = GetSurfaceInst(hDstSurface);

        if (pSrcSurface == HI_NULL || pDstSurface == HI_NULL)
        {
            ALOGE("hSrcSurface or hDstSurface is invalid!\n");
            return HI_FAILURE;
        }

        if (HI_NULL == pstSrcRect || HI_NULL == pstDstRect)
        {
            ALOGE("pstSrcRect or pstDstRect is invalid!\n");
            return HI_FAILURE;
        }

        if (HI_NULL == pSrcSurface->WindowBuffer)
        {
            lock(hSrcSurface);
        }

        if (HI_NULL == pDstSurface->WindowBuffer)
        {
            lock(hDstSurface);
        }

        memset(&stSrc, 0, sizeof(TDE2_SURFACE_S));
        memset(&stDst, 0, sizeof(TDE2_SURFACE_S));
        memset(&stOpt, 0, sizeof(TDE2_OPT_S));

        stSrc.u32Width  = pSrcSurface->stAttr.u32Width;
        stSrc.u32Height = pSrcSurface->stAttr.u32Height;
        stSrc.enColorFmt = FORMAT_TO_TDE(pSrcSurface->stAttr.s32PixelFormat);
        stSrc.u32PhyAddr = pSrcSurface->PhyAddr;
        stSrc.u32Stride = stSrc.u32Width * tde_bytepp(stSrc.enColorFmt);
        stSrc.bAlphaMax255 = HI_TRUE;

        stDst.u32Width  = pDstSurface->stAttr.u32Width;
        stDst.u32Height = pDstSurface->stAttr.u32Height;
        stDst.enColorFmt = FORMAT_TO_TDE(pDstSurface->stAttr.s32PixelFormat);
        stDst.u32PhyAddr = pDstSurface->PhyAddr;
        stDst.u32Stride = stDst.u32Width * tde_bytepp(stDst.enColorFmt);
        stDst.bAlphaMax255 = HI_TRUE;

        srcRect.s32Xpos = pstSrcRect->s32X;
        srcRect.s32Ypos = pstSrcRect->s32Y;
        srcRect.u32Width = pstSrcRect->s32Width;
        srcRect.u32Height = pstSrcRect->s32Height;

        dstRect.s32Xpos = pstDstRect->s32X;
        dstRect.s32Ypos = pstDstRect->s32Y;
        dstRect.u32Width = pstDstRect->s32Width;
        dstRect.u32Height = pstDstRect->s32Height;

        stOpt.enAluCmd = TDE2_ALUCMD_NONE;
        //stOpt.u8GlobalAlpha = 0x40;
        stOpt.stBlendOpt.bGlobalAlphaEnable = HI_FALSE;
        stOpt.stBlendOpt.bPixelAlphaEnable = HI_FALSE;
        stOpt.stBlendOpt.eBlendCmd = TDE2_BLENDCMD_NONE;
        stOpt.stBlendOpt.bSrc2AlphaPremulti = HI_FALSE;
        stOpt.bResize = HI_TRUE;

        s32Handle = HI_TDE_BeginJob();

        if (HI_ERR_TDE_INVALID_HANDLE == s32Handle)
        {
            ALOGE("Fail to create Job.\n");
            return HI_FAILURE;
        }

        Ret = HI_TDE2_Bitblit(s32Handle,
                              &stDst, &dstRect,
                              &stSrc, &srcRect,
                              &stDst, &dstRect,
                              &stOpt);

        if (HI_SUCCESS != Ret)
        {
            ALOGE(" TDE blit failed ,error code %x" , Ret);
            HI_TDE2_CancelJob(s32Handle);
            return HI_FAILURE;
        }

        Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);

        if (HI_SUCCESS != Ret)
        {
            ALOGE(" TDE blit end job failed");
            return HI_FAILURE;
        }

        Ret = HI_TDE2_WaitForDone(s32Handle);

        if (HI_ERR_TDE_QUERY_TIMEOUT == Ret)
        {
            ALOGE("wait for done time out");
            return HI_FAILURE;
        }

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::DrawCCText(HI_HANDLE hSurface, CAPTION_MGR_SURFACE_ATTR_S* pstSurfaceAttr, HI_RECT_S* pstRect, HI_CHAR* pTest, CAPTION_MGR_CCTEXT_ATTR_S* pstAttr)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;
        HI_VOID* pBitmapAddr = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if ((HI_NULL == pPixels ) || (captionSurfaceW != pstSurfaceAttr->u32Width ) || (captionSurfaceH != pstSurfaceAttr->u32Height))
        {
            captionSurfaceW = pstSurfaceAttr->u32Width;
            captionSurfaceH  = pstSurfaceAttr->u32Height;

            if (HI_NULL != pPixels )
            {
                free(pPixels);
            }

            pPixels = (HI_U8*)malloc(captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
            memset(pPixels, 0, captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
        }

#ifdef ANDROID44
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.u32Width, pSurface->stAttr.u32Height);
        tempBitmap.allocPixels(NULL);
#endif

#if defined(ANDROID5) || defined(ANDROIDN)
        const SkImageInfo bitMapInfo = SkImageInfo::Make(captionSurfaceW, captionSurfaceH,
                                       kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        bitmap.installPixels(bitMapInfo, const_cast<void*>((void*)pPixels), captionSurfaceW * CAPTION_PIXBYTE);
        //bitmap.setPixels(pPixels);

        pBitmapAddr = malloc(pSurface->stAttr.u32Width * pSurface->stAttr.u32Height * 4);
        if (HI_NULL == pBitmapAddr)
        {
            ALOGE("pBitmapAddr map error\n");
        }

        const SkImageInfo tmpBitMapInfo = SkImageInfo::Make(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height,
                                          kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        //tempBitmap.installPixels(tmpBitMapInfo, NULL, pSurface->stAttr.u32Width * CAPTION_PIXBYTE);
        //tempBitmap.allocPixels(NULL);
        tempBitmap.installPixels(tmpBitMapInfo, const_cast<void*>(pBitmapAddr), pSurface->stAttr.u32Width * CAPTION_PIXBYTE);

#endif

        SkPaint paint;
        SkCanvas canvas(bitmap);
        SkColor color;
        SkRect rect;

        //draw text background on the bitmap
        color = pstAttr->u32bgColor;
        //color = 0xffff0000;
        paint.setColor(color);
        rect.set(pstRect->s32X, pstRect->s32Y, pstRect->s32Width + pstRect->s32X, pstRect->s32Height + pstRect->s32Y);

        canvas.save();
        canvas.clipRect(rect, SkRegion::kReplace_Op);
        paint.setColor(color);

#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif
        canvas.drawPaint(paint);

        //draw text  on the bitmap
        color = pstAttr->u32fgColor;
        paint.setColor(color);//color
        size_t byteLength = strlen(pTest);
        //paint.setUnderlineText(pstAttr->bUnderline);//underline

        if (HI_TRUE == pstAttr->bItalic) //italic
        {
#ifdef ANDROIDO
        paint.setTypeface(SkTypeface::MakeFromName(CC_FONT_FILE_MONOSPACE, SkFontStyle::FromOldStyle(SkTypeface::kItalic)));
#else
            SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName(CC_FONT_FILE_MONOSPACE, SkTypeface::kItalic)));
#endif
        }
        else
        {
#ifdef ANDROIDO
        paint.setTypeface(SkTypeface::MakeFromName(CC_FONT_FILE_MONOSPACE, SkFontStyle::FromOldStyle(SkTypeface::kNormal)));
#else
            SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName(CC_FONT_FILE_MONOSPACE, SkTypeface::kNormal)));
#endif
        }

        //fontsize
        SkScalar ts;

        if ( 1 == pstAttr->u8fontSize) //HI_UNF_CC_FONTSIZE_SMALL
        {
            ts = SkIntToScalar(15);
        }
        else if (3 == pstAttr->u8fontSize) //HI_UNF_CC_FONTSIZE_LARGE
        {
            ts = SkIntToScalar(27);
        }
        else//HI_UNF_CC_FONTSIZE_STANDARD
        {
            ts = SkIntToScalar(21);
        }

        paint.setTextSize(ts);

        //align
        SkScalar x;

        if (1 == pstAttr->u8justify) //HI_UNF_CC_JUSTIFY_RIGHT
        {
            paint.setTextAlign(SkPaint::kRight_Align);
            x = pstRect->s32X + pstRect->s32Width;

        }
        else if (2 == pstAttr->u8justify) //HI_UNF_CC_JUSTIFY_CENTER
        {
            paint.setTextAlign(SkPaint::kCenter_Align);
            x = (pstRect->s32X + pstRect->s32Width) / 2;
        }
        else//HI_UNF_CC_JUSTIFY_LEFT
        {
            paint.setTextAlign(SkPaint::kLeft_Align);
            x = pstRect->s32X;
        }

        canvas.drawText((HI_CHAR*)pTest, byteLength,  x,  pstRect->s32Y + ts, paint);
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;

        SkScalar sx = (float)pSurface->stAttr.u32Width / captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.u32Height / captionSurfaceH;
#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif

        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();

        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret = pSurface->surface->lock(&Buffer, NULL);

        //copy the bitmap to surface
        memset(Buffer.bits, 0, Buffer.width * Buffer.height * CAPTION_PIXBYTE);
        memcpy(Buffer.bits, tempBitmap.getPixels(), Buffer.width * Buffer.height * CAPTION_PIXBYTE);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

#if defined(ANDROID5) || defined(ANDROIDN)
        if (HI_NULL != pBitmapAddr)
        {
            free(pBitmapAddr);
            pBitmapAddr = HI_NULL;
        }
#endif

    return HI_SUCCESS;

 }

    HI_S32 OsdManager::FillCCRect(HI_HANDLE hSurface, CAPTION_MGR_SURFACE_ATTR_S* pstSurfaceAttr, HI_RECT_S* pstRect, HI_U32 u32Color)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;
        HI_VOID* pBitmapAddr = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if ((HI_NULL == pPixels ) || (captionSurfaceW != pstSurfaceAttr->u32Width ) || (captionSurfaceH != pstSurfaceAttr->u32Height))
        {
            captionSurfaceW = pstSurfaceAttr->u32Width;
            captionSurfaceH  = pstSurfaceAttr->u32Height;

            if (HI_NULL != pPixels )
            {
                free(pPixels);
            }

            pPixels = (HI_U8*)malloc(captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
            memset(pPixels, 0, captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
        }

#ifdef ANDROID44
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.u32Width, pSurface->stAttr.u32Height);
        tempBitmap.allocPixels(NULL);
#endif

#if defined(ANDROID5) || defined(ANDROIDN)
        const SkImageInfo bitMapInfo = SkImageInfo::Make(captionSurfaceW, captionSurfaceH,
                                       kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        bitmap.installPixels(bitMapInfo, const_cast<void*>((void*)pPixels), captionSurfaceW * CAPTION_PIXBYTE);

        pBitmapAddr = malloc(pSurface->stAttr.u32Width * pSurface->stAttr.u32Height * 4);
        if (HI_NULL == pBitmapAddr)
        {
            ALOGE("pBitmapAddr map error\n");
        }

        memset(pBitmapAddr, 0x0, pSurface->stAttr.u32Width * pSurface->stAttr.u32Height * 4);
        const SkImageInfo tmpBitMapInfo = SkImageInfo::Make(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height,
                                          kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        tempBitmap.installPixels(tmpBitMapInfo, const_cast<void*>(pBitmapAddr), pSurface->stAttr.u32Width * CAPTION_PIXBYTE);
#endif
        SkCanvas canvas(bitmap);
        SkPaint paint;
        SkColor color;
        SkRect rect;

        //draw rect on the bitmap
        color = u32Color;
        //color = 0xff0000ff;
        paint.setColor(color);
        rect.set(pstRect->s32X, pstRect->s32Y, pstRect->s32Width + pstRect->s32X, pstRect->s32Height + pstRect->s32Y);

        canvas.save();
        canvas.clipRect(rect, SkRegion::kReplace_Op);
        paint.setColor(color);
#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif
        canvas.drawPaint(paint);
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;

        SkScalar sx = (float)pSurface->stAttr.u32Width / captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.u32Height / captionSurfaceH;
#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif

        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();

        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret = pSurface->surface->lock(&Buffer, NULL);

        if (HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }

        //copy the bitmap to surface
        memset(Buffer.bits, 0, Buffer.width * Buffer.height * CAPTION_PIXBYTE);
        memcpy(Buffer.bits, tempBitmap.getPixels(), Buffer.width * Buffer.height * CAPTION_PIXBYTE);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

#if defined(ANDROID5) || defined(ANDROIDN)
        if (HI_NULL != pBitmapAddr)
        {
            free(pBitmapAddr);
            pBitmapAddr = HI_NULL;
        }
#endif

        return HI_SUCCESS;
    }

    HI_S32 OsdManager::GetCCTextSize(HI_CHAR* pTest, HI_S32* pWidth, HI_S32* pHeigh )
    {

        if (HI_NULL == pTest)
        {
            * pWidth = 0;
            * pHeigh = 0;
            return HI_SUCCESS;
        }

        SkPaint paint;
        SkScalar ts = SkIntToScalar(21); //normal
        paint.setTextSize(ts);
#ifdef ANDROIDO
        paint.setTypeface(SkTypeface::MakeFromName(CC_FONT_FILE_MONOSPACE, SkFontStyle::FromOldStyle(SkTypeface::kNormal)));
#else
        SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName(CC_FONT_FILE_MONOSPACE, SkTypeface::kNormal)));
#endif
        size_t byteLength = strlen(pTest);
        SkScalar width = paint.measureText(pTest, byteLength);

        *pWidth = (HI_S32)width;

        *pHeigh = 21;

        return HI_SUCCESS;

    }

    HI_S32 OsdManager::CCBlit(HI_HANDLE hSurface, CAPTION_MGR_SURFACE_ATTR_S* pstSurfaceAttr, HI_RECT_S* pstSrcRect, HI_RECT_S* pstDstRect)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;
        HI_VOID* pBitmapAddr = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if ((HI_NULL == pPixels ) || (captionSurfaceW != pstSurfaceAttr->u32Width ) || (captionSurfaceH != pstSurfaceAttr->u32Height))
        {
            captionSurfaceW = pstSurfaceAttr->u32Width;
            captionSurfaceH  = pstSurfaceAttr->u32Height;

            if (HI_NULL != pPixels )
            {
                free(pPixels);
            }

            pPixels = (HI_U8*)malloc(captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
            memset(pPixels, 0, captionSurfaceW * captionSurfaceH * CAPTION_PIXBYTE);
        }

#ifdef ANDROID44
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.u32Width, pSurface->stAttr.u32Height);
        tempBitmap.allocPixels(NULL);
#endif

#if defined(ANDROID5) || defined(ANDROIDN)
        const SkImageInfo bitMapInfo = SkImageInfo::Make(captionSurfaceW, captionSurfaceH,
                                       kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        bitmap.installPixels(bitMapInfo, const_cast<void*>((void*)pPixels), captionSurfaceW * CAPTION_PIXBYTE);

        pBitmapAddr = malloc(pSurface->stAttr.u32Width * pSurface->stAttr.u32Height * CAPTION_PIXBYTE);
        if (HI_NULL == pBitmapAddr)
        {
            ALOGE("pBitmapAddr map error\n");
        }

        const SkImageInfo tmpBitMapInfo = SkImageInfo::Make(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height,
                                          kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        tempBitmap.installPixels(tmpBitMapInfo, const_cast<void*>(pBitmapAddr), pSurface->stAttr.u32Width * CAPTION_PIXBYTE);
#endif

        SkCanvas canvas(bitmap);
        SkPaint paint;
        SkRect src;
        SkRect dst;

        src.set(pstSrcRect->s32X, pstSrcRect->s32Y, pstSrcRect->s32X + pstSrcRect->s32Width, pstSrcRect->s32Y + pstSrcRect->s32Height);
        dst.set(pstDstRect->s32X, pstDstRect->s32Y, pstDstRect->s32X + pstDstRect->s32Width, pstDstRect->s32Y + pstDstRect->s32Height);

#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif

        canvas.save();

#if (defined ANDROIDN) || (defined ANDROIDO)
        canvas.drawBitmapRect(bitmap, src, dst, &paint);
#else
        canvas.drawBitmapRectToRect(bitmap, &src, dst, &paint);
#endif
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;

        SkScalar sx = (float)pSurface->stAttr.u32Width / captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.u32Height / captionSurfaceH;

#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif
        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();

        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret = pSurface->surface->lock(&Buffer, NULL);

        //copy the bitmap to surface
        memset(Buffer.bits, 0, Buffer.width * Buffer.height * CAPTION_PIXBYTE);
        memcpy(Buffer.bits, tempBitmap.getPixels(), Buffer.width * Buffer.height * CAPTION_PIXBYTE);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

#if defined(ANDROID5) || defined(ANDROIDN)
    if (HI_NULL != pBitmapAddr)
    {
        free(pBitmapAddr);
        pBitmapAddr = HI_NULL;
    }
#endif

        return HI_SUCCESS;

    }

    //translate and scale
    HI_S32 OsdManager::TeletextDrawBitmap(HI_HANDLE hSurface, HI_U8* bitmapBuffer, HI_RECT_S* pstSrcRect, HI_RECT_S* pstDstRect)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;
        HI_VOID* pBitmapAddr = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

#ifdef ANDROID44
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pstSrcRect->s32Width, pstSrcRect->s32Height);
        tempBitmap.setPixels(bitmapBuffer);
        bitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.u32Width, pSurface->stAttr.u32Height);
        bitmap.allocPixels(NULL);
#endif

#if defined(ANDROID5) || defined(ANDROIDN)
        const SkImageInfo bitMapInfo = SkImageInfo::Make(pstSrcRect->s32Width, pstSrcRect->s32Height,
                                       kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        tempBitmap.installPixels(bitMapInfo, const_cast<void*>((void*)bitmapBuffer), captionSurfaceW * CAPTION_PIXBYTE);

         //set pBitmapAddr to bitmap
         pBitmapAddr = malloc(pSurface->stAttr.u32Width * pSurface->stAttr.u32Height * CAPTION_PIXBYTE);

         if (HI_NULL == pBitmapAddr)
         {
             ALOGE("pBitmapAddr map error\n");
             printf("====TeletextDrawBitmap pBitmapAddr map error\n");
             return HI_FAILURE;
         }

        const SkImageInfo tmpBitMapInfo = SkImageInfo::Make(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height,
                                          kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        bitmap.installPixels(tmpBitMapInfo, const_cast<void*>(pBitmapAddr), pSurface->stAttr.u32Width * CAPTION_PIXBYTE);
#endif

        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret = pSurface->surface->lock(&Buffer, NULL);

        if (HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }

        SkCanvas canvas(bitmap);
        SkPaint paint;

#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif
        SkScalar sx = (float)pstDstRect->s32Width/pstSrcRect->s32Width;
        SkScalar sy = (float)pstDstRect->s32Height/pstSrcRect->s32Height;

        canvas.save();
        canvas.scale(sx, sy);
        canvas.drawBitmap(tempBitmap, pstDstRect->s32X/sx, pstDstRect->s32Y/sy, &paint);
        canvas.restore();

        //copy the bitmap to surface
        memset(Buffer.bits, 0, Buffer.width * Buffer.height * CAPTION_PIXBYTE);
        memcpy(Buffer.bits, bitmap.getPixels(), Buffer.width * Buffer.height * CAPTION_PIXBYTE);

        s32Ret = pSurface->surface->unlockAndPost();

        SurfaceComposerClient::closeGlobalTransaction();

#if defined(ANDROID5) || defined(ANDROIDN)
        if (HI_NULL != pBitmapAddr)
        {
            free(pBitmapAddr);
            pBitmapAddr = HI_NULL;
        }
#endif

        return HI_SUCCESS;
    }

    //translate and scale
    HI_S32 OsdManager::SubDrawBitmap(HI_HANDLE hSurface, HI_U8* pu8BitmapBuffer, HI_RECT_S* pstDstRect, HI_RECT_S* pstSrcRect)
    {
        CAPTION_MGR_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        HI_U32 u32SurfaceBufferSize = 0;
        HI_U32 u32SurfaceWidth = 0;
        HI_U32 u32SurfaceHeight = 0;
        ANativeWindow_Buffer Buffer;
        HI_VOID *pBitmapAddr = HI_NULL;

        pSurface = GetSurfaceInst(hSurface);

        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        u32SurfaceWidth = pSurface->stAttr.u32Width;
        u32SurfaceHeight = pSurface->stAttr.u32Height;

        u32SurfaceBufferSize = u32SurfaceWidth * u32SurfaceHeight * CAPTION_PIXBYTE;

        if (HI_NULL == pPixels)
        {
            pPixels = (HI_U8*)malloc(u32SurfaceBufferSize);
            memset(pPixels, 0, u32SurfaceBufferSize);
        }

        if (!android::Surface::isValid(pSurface->surface))
        {
            ALOGE("surface is invalid \n");
            return HI_FAILURE;
        }

        memset(pPixels, 0x0, u32SurfaceBufferSize);
#if defined(ANDROID5) || defined(ANDROIDN)
        const SkImageInfo bitMapInfo = SkImageInfo::Make(pstDstRect->s32Width, pstDstRect->s32Height,
                                       kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        tempBitmap.installPixels(bitMapInfo, const_cast<void*>((void*)pu8BitmapBuffer), pstDstRect->s32Width * CAPTION_PIXBYTE);

        const SkImageInfo tmpBitMapInfo = SkImageInfo::Make(pSurface->stAttr.u32Width, pSurface->stAttr.u32Height,
                                          kRGBA_8888_SkColorType, kPremul_SkAlphaType);

        bitmap.installPixels(tmpBitMapInfo, const_cast<void*>((void*)pPixels), pSurface->stAttr.u32Width * CAPTION_PIXBYTE);
#endif

        //blit scal buffer to canvasBitmap, and then copy to screen surface.
        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret = pSurface->surface->lock(&Buffer, NULL);

        if (HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }

        SkCanvas canvas(bitmap);
        SkPaint paint;

#ifdef ANDROIDO
        paint.setBlendMode(SkBlendMode::kSrc);
#else
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
#endif
        SkScalar sx = (float)pSurface->stAttr.u32Width / pstDstRect->s32Width;
        SkScalar sy = (float)pSurface->stAttr.u32Height / pstDstRect->s32Height;

        canvas.save();
        canvas.scale(sx, sy);
        canvas.drawBitmap(tempBitmap, pstSrcRect->s32X, pstSrcRect->s32Y, &paint);
        canvas.restore();

        //copy the bitmap to surface
        memset(Buffer.bits, 0x0, Buffer.width * Buffer.height * CAPTION_PIXBYTE);
        memcpy(Buffer.bits, pPixels, Buffer.width * Buffer.height * CAPTION_PIXBYTE);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

        return HI_SUCCESS;

    }

} // end of namespace
#endif
