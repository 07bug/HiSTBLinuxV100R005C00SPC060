#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_disp.h"

#include "tvos_hal_common.h"
#include "caption_out_common.h"

#ifdef LINUX_OS
#include "hi_go.h"
#include "hi_go_text.h"
#include "hi_go_bliter.h"
#else
#include "caption_osd.h"
#endif

#include "caption_cc_out.h"
#include "hi_unf_cc.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPTION"

#define  CC_SCREEN_WIDTH    (1280)
#define  CC_SCREEN_HEIGHT   (720)
#define  CC_OUTPUT_HANDLE    (0xFE00)

#define COLOR2ARGB(a, c) (a) = ((c).u8Alpha << 24) | ((c).u8Red << 16) | ((c).u8Green << 8) | (c).u8Blue
#define ANDROID_COLOR2ARGB(a, c)  (a) = ((c).u8Alpha << 24) | ((c).u8Red << 16) | ((c).u8Green << 8) | (c).u8Blue

#define SUPPORT_VBI_

#ifdef SUPPORT_VBI
static HI_HANDLE s_hVBI = 0xffffff;
#endif

#ifdef LINUX_OS
static HI_U32 s_u32CCSurfaceWidth = CC_SCREEN_WIDTH;
static HI_U32 s_u32CCSurfaceHeight = CC_SCREEN_HEIGHT;

#define CC_FONT_FILE "/usr/data/font/DroidSansMono.ttf"
#else
static HI_HANDLE s_hSurface = HI_INVALID_HANDLE;
static HI_U32 s_u32ScreenWidth = CC_SCREEN_WIDTH;
static HI_U32 s_u32ScreenHeight = CC_SCREEN_HEIGHT;
#endif

#define HI_INVALID_HANDLE (0xffffffff)

static HI_S32 cc_get_unicode_len(HI_U32 c)
{
    HI_S32 s32len = 0;

    if (c < 0x80)
    {
        s32len = 1;
    }
    else if (c < 0x800)
    {
        s32len = 2;
    }
    else if (c < 0x10000)
    {
        s32len = 3;
    }
    else if (c < 0x200000)
    {
        s32len = 4;
    }
    else if (c < 0x4000000)
    {
        s32len = 5;
    }
    else
    {
        s32len = 6;
    }

    return s32len;
}

static HI_S32 cc_convert_unicode_to_utf8( HI_U32 c, HI_U8* outbuf)
{
    HI_U32 len ;
    HI_S32 first;
    HI_S32 i;

    if (c < 0x80)
    {
        first = 0;
        len = 1;
    }
    else if (c < 0x800)
    {
        first = 0xc0;
        len = 2;
    }
    else if (c < 0x10000)
    {
        first = 0xe0;
        len = 3;
    }
    else if (c < 0x200000)
    {
        first = 0xf0;
        len = 4;
    }
    else if (c < 0x4000000)
    {
        first = 0xf8;
        len = 5;
    }
    else
    {
        first = 0xfc;
        len = 6;
    }

    for (i = len - 1; i > 0; --i)
    {
        outbuf[i] = (c & 0x3f) | 0x80;

        c >>= 6;
    }

    outbuf[0] = c | first;

    return len;
}

static HI_S32 cc_convert_utf16_to_utf8(const HI_U8* pInbuf, HI_S32 InLen, HI_U8* pOutbuf, HI_S32* pOutLen )
{
    const HI_U8* in = (const HI_U8*)pInbuf;
    HI_U8* p = pOutbuf;
    HI_U32 unicode = 0;
    HI_S32 s32Outsize = *pOutLen;
    HI_S32 s32len = 0;
    HI_S32 i = 0;
    HI_U32 tmp = 0;

    for (i = 0; i < InLen; i += 2)
    {
        if ((i + 1) < InLen)
        {
            unicode = in[i];
            tmp = in[i + 1];
            unicode |= tmp << 8;
        }
        else
        {
            break;
        }

        s32len =  cc_get_unicode_len(unicode);

        if ( s32Outsize < s32len )
        {
            break;
        }

        s32Outsize -= s32len;

        p += cc_convert_unicode_to_utf8(unicode, p);

    }

    *p = 0;
    *pOutLen = p - pOutbuf;

    return HI_SUCCESS;
}

#ifdef SUPPORT_VBI

static HI_U8 cc_reverse_char(HI_U8 Data)
{
    HI_U8 b0, b1, b2, b3, b4, b5, b6, b7;
    HI_U8  Reversed;

    b0 = (Data >> 0) & 0x1 ;
    b1 = (Data >> 1) & 0x1 ;
    b2 = (Data >> 2) & 0x1 ;
    b3 = (Data >> 3) & 0x1 ;
    b4 = (Data >> 4) & 0x1 ;
    b5 = (Data >> 5) & 0x1 ;
    b6 = (Data >> 6) & 0x1 ;
    b7 = (Data >> 7) & 0x1 ;
    Reversed = (b7 << 0)
               | (b6 << 1)
               | (b5 << 2)
               | (b4 << 3)
               | (b3 << 4)
               | (b2 << 5)
               | (b1 << 6)
               | (b0 << 7);

    return (Reversed);
}
#endif

#ifdef LINUX_OS
static HI_HANDLE s_hccLayer = HIGO_INVALID_HANDLE;
static HI_HANDLE s_LayerSurface = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hFontOutStardard = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hFontOutLarge = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hFontOutSmall = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hCCSurface = HIGO_INVALID_HANDLE;

static HI_S32 cc_higo_suraface_init(HI_HANDLE hOut)
{
    HI_S32 s32Ret = 0;
    HIGO_TEXT_INFO_S stFontInfo;

    HAL_DEBUG("%s, %d\n", __FUNCTION__, __LINE__);

    s_hccLayer = hOut;

    HAL_CHK_RETURN((HIGO_INVALID_HANDLE == s_hccLayer), HI_FAILURE,
                   "s_hccLayer failed! s32Ret = 0x%x !\n", s32Ret);

    s32Ret =  HI_GO_GetLayerSurface(s_hccLayer, &s_LayerSurface);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_GetLayerSurface failed! s32Ret = 0x%x !\n", s32Ret);

    s32Ret = HI_GO_FillRect(s_LayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_FillRect failed! s32Ret = 0x%x !\n", s32Ret);

    stFontInfo.pMbcFontFile = HI_NULL;
    stFontInfo.pSbcFontFile = CC_FONT_FILE;
    stFontInfo.u32Size = 20;

    s32Ret = HI_GO_CreateTextEx(&stFontInfo, &s_hFontOutStardard);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_CreateTextEx failed! s32Ret = 0x%x !\n", s32Ret);

    s32Ret = HI_GO_SetInputCharSet(s_hFontOutStardard, HIGO_CHARSET_UTF8);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_SetInputCharSet failed! s32Ret = 0x%x !\n", s32Ret);

    stFontInfo.u32Size = 24;
    s32Ret = HI_GO_CreateTextEx(&stFontInfo, &s_hFontOutLarge);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_CreateTextEx failed! s32Ret = 0x%x !\n", s32Ret);

    s32Ret = HI_GO_SetInputCharSet(s_hFontOutLarge, HIGO_CHARSET_UTF8);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_SetInputCharSet failed! s32Ret = 0x%x !\n", s32Ret);

    stFontInfo.u32Size = 14;
    s32Ret = HI_GO_CreateTextEx(&stFontInfo, &s_hFontOutSmall);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_CreateTextEx failed! s32Ret = 0x%x !\n", s32Ret);

    s32Ret = HI_GO_SetInputCharSet(s_hFontOutSmall, HIGO_CHARSET_UTF8);
    HAL_CHK_GOTO((HI_SUCCESS != s32Ret), RET, "HI_GO_CreateTextEx failed! s32Ret = 0x%x !\n", s32Ret);

    return HI_SUCCESS;

RET:

    if (HIGO_INVALID_HANDLE != s_hFontOutStardard)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutStardard);
        s_hFontOutStardard = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFontOutLarge)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutLarge);
        s_hFontOutLarge = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFontOutSmall)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutSmall);
        s_hFontOutSmall = HIGO_INVALID_HANDLE;
    }

    s_LayerSurface = HIGO_INVALID_HANDLE;

    return HI_FAILURE;
}

static HI_S32 cc_higo_surface_deinit()
{
    if (HIGO_INVALID_HANDLE != s_hCCSurface)
    {
        (HI_VOID)HI_GO_FreeSurface(s_hCCSurface);
        s_hCCSurface = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFontOutStardard)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutStardard);
        s_hFontOutStardard = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFontOutLarge)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutLarge);
        s_hFontOutLarge = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFontOutSmall)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFontOutSmall);
        s_hFontOutSmall = HIGO_INVALID_HANDLE;
    }

    s_LayerSurface = HIGO_INVALID_HANDLE;
    s_hccLayer = HIGO_INVALID_HANDLE;

    return HI_SUCCESS;
}

static HI_S32 cc_higo_checkSurface()
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32SurfaceWidth = 0;
    HI_S32 s32SurfaceHeight = 0;

    if (HIGO_INVALID_HANDLE == s_hCCSurface)
    {
        s32Ret = HI_GO_CreateSurface(s_u32CCSurfaceWidth, s_u32CCSurfaceHeight, HIGO_PF_8888, &s_hCCSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_CreateSurface failed!, ret = %x\n", s32Ret);
            return s32Ret;
        }

        s32Ret = HI_GO_FillRect(s_hCCSurface, HI_NULL, 0x00000000, HIGO_COMPOPT_NONE);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect failed!, ret = %x\n", s32Ret);
            return s32Ret;
        }

    }
    else
    {
        s32Ret = HI_GO_GetSurfaceSize(s_hCCSurface, &s32SurfaceWidth, &s32SurfaceHeight);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect failed!, ret = %x\n", s32Ret);
            return s32Ret;
        }

        if ((s32SurfaceWidth != s_u32CCSurfaceWidth) || (s32SurfaceHeight != s_u32CCSurfaceHeight))
        {
            (HI_VOID)HI_GO_FreeSurface(s_hCCSurface);
            (HI_VOID)HI_GO_CreateSurface(s_u32CCSurfaceWidth, s_u32CCSurfaceHeight, HIGO_PF_8888, &s_hCCSurface);
            (HI_VOID)HI_GO_FillRect(s_hCCSurface, HI_NULL, 0x00000000, HIGO_COMPOPT_NONE);
        }
    }

    return HI_SUCCESS;
}

static HIGO_LAYOUT_E cc_higo_justifyTranscode(HI_UNF_CC_JUSTIFY_E enJustify)
{
    HIGO_LAYOUT_E enHigoJustify = HIGO_LAYOUT_BUTT;

    switch (enJustify)
    {
        case HI_UNF_CC_JUSTIFY_LEFT:
            enHigoJustify = HIGO_LAYOUT_LEFT;
            break;

        case HI_UNF_CC_JUSTIFY_RIGHT:
            enHigoJustify = HIGO_LAYOUT_RIGHT;
            break;

        case HI_UNF_CC_JUSTIFY_CENTER:
            enHigoJustify = HIGO_LAYOUT_HCENTER;
            break;

        case HI_UNF_CC_JUSTIFY_FULL:
            enHigoJustify = HIGO_LAYOUT_HCENTER;
            break;

        default:
            enHigoJustify = HIGO_LAYOUT_LEFT;
            break;
    }

    return enHigoJustify;
}

static HI_VOID cc_higo_drawText(const HI_UNF_CC_TEXT_S stText, HI_UNF_CC_RECT_S stRect)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT stSrcRect = {0};
    HIGO_BLTOPT_S stBlitOpt;
    HIGO_LAYOUT_E enlayout;

    HI_U8* pu8InBuf = (HI_U8*)stText.pu16Text;
    HI_S32 s32InLen = stText.u8TextLen * 2;
    HI_U8  pu8OutBuf[128];
    HI_S32 s32OutLen = sizeof(pu8OutBuf);

    HI_U32 u32bgColor  = 0;
    HI_U32 u32fgColor  = 0;
    HI_U8  u8justify   = stText.u8Justify;
    HI_U8  u8WordWrap  = stText.u8WordWrap;
    HI_U8  u8fontstyle = stText.enFontStyle;

    stSrcRect.x = stRect.x;
    stSrcRect.y = stRect.y;
    stSrcRect.w = stRect.width;
    stSrcRect.h = stRect.height;

    cc_higo_checkSurface();

    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hccLayer), "s_hccLayer invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_LayerSurface), "s_LayerSurface invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hCCSurface), "s_hCCSurface invalid!");

    s32Ret = cc_convert_utf16_to_utf8(pu8InBuf, s32InLen, pu8OutBuf, &s32OutLen);
    HAL_CHK_PRINTF((HI_SUCCESS != s32Ret), "failed to UTF16LE_to_UTF8,ret = %x\n", s32Ret);

    HI_HANDLE hFontOut;

    if (stText.enFontSize == HI_UNF_CC_FONTSIZE_LARGE)
    {
        hFontOut = s_hFontOutLarge;
    }
    else if (stText.enFontSize == HI_UNF_CC_FONTSIZE_SMALL)
    {
        hFontOut = s_hFontOutSmall;
    }
    else
    {
        hFontOut = s_hFontOutStardard;
    }

    COLOR2ARGB(u32bgColor, stText.stBgColor);
    COLOR2ARGB(u32fgColor, stText.stFgColor);
    HI_GO_SetTextColor(hFontOut, u32fgColor);
    HI_GO_SetTextBGColor(hFontOut, u32bgColor);

    if (0 == stText.stBgColor.u8Alpha)
    {
        (HI_VOID)HI_GO_SetTextBGTransparent(hFontOut, HI_TRUE);
    }
    else
    {
        (HI_VOID)HI_GO_SetTextBGTransparent(hFontOut, HI_FALSE);
    }

    enlayout = cc_higo_justifyTranscode((HI_UNF_CC_JUSTIFY_E)u8justify);

    if (u8WordWrap)
    {
        /*lint -e655*/
        enlayout = (HIGO_LAYOUT_E)(enlayout | HIGO_LAYOUT_WRAP);
        /*lint +e655*/
    }

    if ((u8fontstyle ==  HI_UNF_CC_FONTSTYLE_ITALIC) || (u8fontstyle == HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE))
    {
        HI_GO_SetTextStyle(hFontOut, HIGO_TEXT_STYLE_ITALIC);
    }
    else
    {
        HI_GO_SetTextStyle(hFontOut, HIGO_TEXT_STYLE_NORMAL);
    }

    s32Ret = HI_GO_TextOutEx(hFontOut, s_hCCSurface, (HI_CHAR*)pu8OutBuf, &stSrcRect, enlayout);
    HAL_CHK_RETURN_VOID((HI_SUCCESS != s32Ret), "failed to text out char!,ret = %x\n", s32Ret);

    memset(&stBlitOpt, 0, sizeof(HIGO_BLTOPT_S));
    stBlitOpt.EnableScale = HI_TRUE;
    s32Ret = HI_GO_Blit(s_hCCSurface, HI_NULL, s_LayerSurface, HI_NULL, &stBlitOpt);
    HAL_CHK_RETURN_VOID((HI_SUCCESS != s32Ret), "HI_GO_Blit failed!, ret = %x\n", s32Ret);

    s32Ret = HI_GO_RefreshLayer(s_hccLayer, HI_NULL);
    HAL_CHK_RETURN_VOID((HI_SUCCESS != s32Ret), "HI_GO_RefreshLayer failed!, ret = %x\n", s32Ret);

    return;
}

static HI_VOID cc_higo_fillRect(const HI_UNF_CC_FILLRECT_S stFillRect, HI_UNF_CC_RECT_S stRect)
{
    HI_U32 u32Color = 0;
    HI_RECT stSrcRect = {0};
    HIGO_BLTOPT_S stBlitOpt;

    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hccLayer), "s_hccLayer invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_LayerSurface), "s_LayerSurface invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hCCSurface), "s_hCCSurface invalid!");

    stSrcRect.x = stRect.x;
    stSrcRect.y = stRect.y;
    stSrcRect.w = stRect.width;
    stSrcRect.h = stRect.height;

    COLOR2ARGB(u32Color, stFillRect.stColor);

    (HI_VOID)HI_GO_FillRect(s_hCCSurface, &stSrcRect, u32Color, HIGO_COMPOPT_NONE);

    memset(&stBlitOpt, 0, sizeof(HIGO_BLTOPT_S));

    stBlitOpt.EnableScale = HI_TRUE;

    (HI_VOID)HI_GO_Blit (s_hCCSurface, HI_NULL, s_LayerSurface, HI_NULL, &stBlitOpt);
    (HI_VOID)HI_GO_RefreshLayer(s_hccLayer, NULL);
}

static HI_VOID cc_higo_blit(HI_UNF_CC_RECT_S* pstSrcRect, HI_UNF_CC_RECT_S* pstDestRect)
{
    HIGO_BLTOPT_S stBlitOpt;
    HI_RECT stSrcRect = {0, 0, 0, 0};
    HI_RECT stDstRect = {0, 0, 0, 0};

    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hccLayer), "s_hccLayer invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_LayerSurface), "s_LayerSurface invalid!");
    HAL_CHK_RETURN_VOID((HIGO_INVALID_HANDLE == s_hCCSurface), "s_hCCSurface invalid!");

    stSrcRect.x = pstSrcRect->x;
    stSrcRect.y = pstSrcRect->y;
    stSrcRect.w = pstSrcRect->width;
    stSrcRect.h = pstSrcRect->height;

    stDstRect.x = pstDestRect->x;
    stDstRect.y = pstDestRect->y;
    /*lint -e655*/
    stDstRect.w = pstDestRect->width;
    /*lint +e655*/
    stDstRect.h = pstDestRect->height;

    (HI_VOID)HI_GO_Blit(s_hCCSurface, &stSrcRect, s_hCCSurface, &stDstRect, HI_NULL);

    memset(&stBlitOpt, 0, sizeof(HIGO_BLTOPT_S));

    stBlitOpt.EnableScale = HI_TRUE;

    (HI_VOID)HI_GO_Blit(s_hCCSurface, HI_NULL, s_LayerSurface, HI_NULL , &stBlitOpt);
    (HI_VOID)HI_GO_RefreshLayer(s_hccLayer, HI_NULL);

}

#else

static HI_VOID cc_osd_getSurfaceAttr(CAPTION_OSD_SURFACE_ATTR_S* pstSurfaceAttr)
{
    pstSurfaceAttr->enPixelFormat = CAPTION_OSD_PF_8888;
#ifdef LINUX_OS
    pstSurfaceAttr->u32Width = s_u32CCSurfaceWidth;
    pstSurfaceAttr->u32Height = s_u32CCSurfaceHeight;
#else
    pstSurfaceAttr->u32Width = s_u32ScreenWidth;
    pstSurfaceAttr->u32Height = s_u32ScreenHeight;
#endif
}

static HI_VOID cc_osd_getTextAttr(const HI_UNF_CC_TEXT_S stText, HI_S32 s32OutLen, CAPTION_OSD_SURFACE_ATTR_S* pstSurfaceAttr, CAPTION_OSD_CCTEXT_ATTR_S* pstCCTextAttr)
{
    HI_U32 u32bgColor, u32fgColor;
    HI_U8  u8justify = stText.u8Justify;
    HI_U8  u8WordWrap = stText.u8WordWrap;
    HI_U8  u8fontstyle = stText.enFontStyle;

    ANDROID_COLOR2ARGB(u32bgColor, stText.stBgColor);
    ANDROID_COLOR2ARGB(u32fgColor, stText.stFgColor);

    //HAL_DEBUG("u32bgColor:%#x\n",u32bgColor);
    //HAL_DEBUG("u32fgColor:%#x\n",u32fgColor);
    //HAL_DEBUG("u8edgeType:%d\n",pstDisplayParam->unDispParam.stText.enEdgetype);
    //HAL_DEBUG("u8fontSize:[%d],small,standard,large:1,2,3\n",pstDisplayParam->unDispParam.stText.enFontSize);

    pstCCTextAttr->u32BufLen = (HI_U32)s32OutLen;
    pstCCTextAttr->u32bgColor = u32bgColor;
    pstCCTextAttr->u32fgColor = u32fgColor;
    pstCCTextAttr->u8fontSize = stText.enFontSize;

    //Underline
    if ((u8fontstyle ==  HI_UNF_CC_FONTSTYLE_UNDERLINE) || (u8fontstyle == HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE))
    {
        pstCCTextAttr->bUnderline = HI_TRUE;
    }
    else
    {
        pstCCTextAttr->bUnderline = HI_FALSE;
    }

    //Italic
    if ((u8fontstyle ==  HI_UNF_CC_FONTSTYLE_ITALIC) || (u8fontstyle == HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE))
    {
        pstCCTextAttr->bItalic = HI_TRUE;
    }
    else
    {
        pstCCTextAttr->bItalic = HI_FALSE;
    }

    cc_osd_getSurfaceAttr(pstSurfaceAttr);

}

static HI_VOID cc_osd_drawText(const HI_UNF_CC_TEXT_S stText, HI_UNF_CC_RECT_S stRect)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_RECT_S stSrcRect = {0};
    HI_U8  pu8OutBuf[128];
    HI_S32 s32InLen = stText.u8TextLen * 2;
    HI_S32 s32OutLen = sizeof(pu8OutBuf);
    HI_U8* pu8InBuf = (HI_U8*)stText.pu16Text;

    CAPTION_OSD_CCTEXT_ATTR_S stCCTextAttr;
    CAPTION_OSD_SURFACE_ATTR_S stSurfaceAttr;

    stSrcRect.s32X = stRect.x;
    stSrcRect.s32Y = stRect.y;
    stSrcRect.s32Width = stRect.width;
    stSrcRect.s32Height = stRect.height;

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_subt_output_draw failed, s_hSurface = 0x%x !\n", s_hSurface);

        return;
    }

    s32Ret = cc_convert_utf16_to_utf8(pu8InBuf, s32InLen, pu8OutBuf, &s32OutLen);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to cc_osd_convert_utf16_to_utf8,ret = %x\n", s32Ret);
    }

    cc_osd_getTextAttr(stText, s32OutLen, &stSurfaceAttr, &stCCTextAttr);

    (VOID)caption_osd_drawtext(s_hSurface, &stSurfaceAttr, &stSrcRect, (HI_CHAR*)pu8OutBuf, &stCCTextAttr);
}

static HI_VOID cc_osd_fillRect(const HI_UNF_CC_FILLRECT_S stFillRect, HI_UNF_CC_RECT_S stRect)
{
    HI_U32 u32Color = 0;
    HI_RECT_S stSrcRect = {0};
    HI_S32 s32Ret = HI_SUCCESS;

    stSrcRect.s32X = stRect.x;
    stSrcRect.s32Y = stRect.y;
    stSrcRect.s32Width = stRect.width;
    stSrcRect.s32Height = stRect.height;

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_subt_output_draw failed, s_hSurface = 0x%x !\n", s_hSurface);

        return;
    }

    ANDROID_COLOR2ARGB(u32Color, stFillRect.stColor);

    CAPTION_OSD_SURFACE_ATTR_S stSurfaceAttr;

    cc_osd_getSurfaceAttr(&stSurfaceAttr);

    caption_osd_fillrect(s_hSurface, &stSurfaceAttr, &stSrcRect, u32Color);

}

static HI_VOID cc_osd_blit(HI_UNF_CC_RECT_S* pstSrcRect, HI_UNF_CC_RECT_S* pstDestRect)
{
    HI_RECT_S stSrcRect = {0, 0, 0, 0};
    HI_RECT_S stDstRect = {0, 0, 0, 0};

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_cc_output_blit failed, s_hSurface = 0x%x !\n", s_hSurface);
        return ;
    }

    stSrcRect.s32X = pstSrcRect->x;
    stSrcRect.s32Y = pstSrcRect->y;
    stSrcRect.s32Width = pstSrcRect->width;
    stSrcRect.s32Height = pstSrcRect->height;

    stDstRect.s32X = pstDestRect->x;
    stDstRect.s32Y = pstDestRect->y;
    stDstRect.s32Width = pstDestRect->width;
    stDstRect.s32Height = pstDestRect->height;

    //HAL_DEBUG("Blit:[%d,%d,%d,%d]->[%d,%d,%d,%d]\n", stSrcRect.s32X, stSrcRect.s32Y, stSrcRect.s32Width, stSrcRect.s32Height, stDstRect.s32X, stDstRect.s32Y, stDstRect.s32Width, stDstRect.s32Height);

    CAPTION_OSD_SURFACE_ATTR_S stSurfaceAttr;

    cc_osd_getSurfaceAttr(&stSurfaceAttr);

    caption_osd_cc_blit(s_hSurface, &stSurfaceAttr, &stSrcRect, &stDstRect);

}

#endif

HI_S32 caption_cc_output_init(HI_HANDLE* phOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = caption_output_init(phOut);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_init failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#ifdef LINUX_OS

    s32Ret = cc_higo_suraface_init(*phOut);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_init failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#else
    caption_cc_output_xds_init();
#endif

#ifdef SUPPORT_VBI
    HI_UNF_DISP_VBI_CFG_S stVBICfg = {0};

    stVBICfg.enType =  HI_UNF_DISP_VBI_TYPE_CC;

    s32Ret = HI_UNF_DISP_CreateVBI(HI_UNF_DISPLAY0, &stVBICfg, &s_hVBI);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_DISP_CreateVBI failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#endif

    return HI_SUCCESS;
}

HI_S32 caption_cc_output_deinit(HI_HANDLE hOut)
{
    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS
    s32Ret = cc_higo_surface_deinit();

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("cc_higo_deinit failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#endif

    s32Ret = caption_output_deinit();

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_deinit failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#ifdef SUPPORT_VBI

    if (HI_INVALID_HANDLE != s_hVBI)
    {
        s32Ret = HI_UNF_DISP_DestroyVBI(s_hVBI);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_DISP_DestroyVBI failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }

#endif

    return HI_SUCCESS;
}

HI_S32 caption_cc_output_create_surface(HI_RECT_S stRect)
{
    HI_S32 s32Ret = HI_FAILURE;

    HAL_DEBUG("%s, %d\n", __FUNCTION__, __LINE__);

#ifdef LINUX_OS

    if (HIGO_INVALID_HANDLE == s_hCCSurface)
    {
        s32Ret = HI_GO_CreateSurface(s_u32CCSurfaceWidth, s_u32CCSurfaceHeight, HIGO_PF_8888, &s_hCCSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_CreateSurface failed!, ret = %x\n", s32Ret);
            return s32Ret;
        }

        s32Ret = HI_GO_FillRect(s_hCCSurface, HI_NULL, 0x00000000, HIGO_COMPOPT_NONE);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect failed!, ret = %x\n", s32Ret);
            return s32Ret;
        }

    }

#else

    s32Ret = caption_output_create_surface(stRect, &s_hSurface);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_osd_destroy_surface failed, ret = 0x%x !\n", s32Ret);

        return HI_FAILURE;
    }

    s_u32ScreenWidth = stRect.s32Width;
    s_u32ScreenHeight = stRect.s32Height;

#endif
    return HI_SUCCESS;
}

HI_S32 caption_cc_output_destory_surface()
{
    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS

    if (HIGO_INVALID_HANDLE != s_hCCSurface)
    {
        s32Ret = HI_GO_FreeSurface(s_hCCSurface);

        if (HI_SUCCESS != s32Ret)
        {
            printf("HI_GO_FreeSurface failed, ret = 0x%x !\n", s32Ret);

            return HI_FAILURE;
        }

        s_hCCSurface = HIGO_INVALID_HANDLE;
    }

#else

    if (HI_INVALID_HANDLE != s_hSurface)
    {
        s32Ret = caption_output_destory_surface();

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("caption_osd_destroy_surface failed, ret = 0x%x !\n", s32Ret);

            return HI_FAILURE;
        }

        s_hSurface = HI_INVALID_HANDLE;
    }

#endif
    return HI_SUCCESS;
}

HI_S32 caption_cc_output_draw(HI_U32 u32UserData, HI_UNF_CC_DISPLAY_PARAM_S* pstDisplayParam)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_NULL == pstDisplayParam)
    {
        return HI_FAILURE;
    }

    if ((0 == pstDisplayParam->u32DisplayWidth) || (0 == pstDisplayParam->u32DisplayHeight))
    {
        HAL_ERROR("args error. w:h = %d, %d \n", pstDisplayParam->u32DisplayWidth, pstDisplayParam->u32DisplayHeight);

        return HI_FAILURE;
    }

    if ((0 == pstDisplayParam->stRect.width) || (0 == pstDisplayParam->stRect.height))
    {
        HAL_ERROR("args error. w:h = %d, %d \n", pstDisplayParam->stRect.width, pstDisplayParam->stRect.height);

        return HI_FAILURE;
    }
#ifdef LINUX_OS
    s_u32CCSurfaceWidth = pstDisplayParam->u32DisplayWidth;
    s_u32CCSurfaceHeight = pstDisplayParam->u32DisplayHeight;
#else
    s_u32ScreenWidth = pstDisplayParam->u32DisplayWidth;
    s_u32ScreenHeight = pstDisplayParam->u32DisplayHeight;
#endif

    switch (pstDisplayParam->enOpt)
    {
        case HI_UNF_CC_OPT_DRAWTEXT:
        {
#ifdef LINUX_OS
            cc_higo_drawText(pstDisplayParam->unDispParam.stText, pstDisplayParam->stRect);
#else
            cc_osd_drawText(pstDisplayParam->unDispParam.stText, pstDisplayParam->stRect);
#endif
            break;
        }

        case HI_UNF_CC_OPT_FILLRECT:
        {
#ifdef LINUX_OS
            cc_higo_fillRect(pstDisplayParam->unDispParam.stFillRect, pstDisplayParam->stRect);
#else
            cc_osd_fillRect(pstDisplayParam->unDispParam.stFillRect, pstDisplayParam->stRect);
#endif
            break;
        }

        case HI_UNF_CC_OPT_DRAWBITMAP:
        default:
            HAL_DEBUG("Not implement\n");
            break;

    }

    return s32Ret;
}

HI_S32 caption_cc_output_get_textsize(HI_U32 u32Userdata, HI_U16* u16Str, HI_S32 s32StrNum, HI_S32* ps32Width, HI_S32* ps32Heigth)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_U8* pu8InBuf = (HI_U8*)u16Str;
    HI_S32 s32InLen = s32StrNum * 2;
    HI_U8 pu8OutBuf[128];
    HI_S32 s32OutLen = sizeof(pu8OutBuf);

    if ((NULL == u16Str) || (0 == s32StrNum) || (NULL == ps32Width) || (NULL == ps32Heigth))
    {
        return HI_FAILURE;
    }

    *ps32Width = 0;
    *ps32Heigth = 0;

    s32Ret = cc_convert_utf16_to_utf8(pu8InBuf, s32InLen, pu8OutBuf, &s32OutLen);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to cc_osd_convert_utf16_to_utf8,ret = %x\n", s32Ret);
    }

#ifdef LINUX_OS

    if (HIGO_INVALID_HANDLE != s_hFontOutStardard)
    {
        s32Ret = HI_GO_GetTextExtent(s_hFontOutStardard, (const HI_CHAR*)pu8OutBuf, ps32Width, ps32Heigth);
    }

#else

    if (s_hSurface == HI_INVALID_HANDLE)
    {
        HAL_ERROR("caption_cc_output_get_textsize failed, s_hSurface = 0x%x !\n", s_hSurface);

        return HI_FAILURE;
    }

    s32Ret = caption_osd_cc_get_textsize((HI_CHAR* )pu8OutBuf, ps32Width, ps32Heigth);
    *ps32Heigth = *ps32Heigth + 6;

#endif

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to HI_GO_GetTextExtent,ret = %x\n", s32Ret);
    }

    return  HI_SUCCESS;
}

HI_S32 caption_cc_output_blit(HI_U32 u32UserPrivatData, HI_UNF_CC_RECT_S* pstSrcRect, HI_UNF_CC_RECT_S* pstDestRect)
{

    if (NULL == pstSrcRect || NULL == pstDestRect)
    {
        return HI_FAILURE;
    }

#ifdef LINUX_OS
    cc_higo_blit(pstSrcRect, pstDestRect);
#else
    cc_osd_blit(pstSrcRect, pstDestRect);
#endif

    return HI_SUCCESS;
}

HI_S32 caption_cc_output_vbi(HI_U32 u32UserData, HI_UNF_CC_VBI_DADA_S* pstVBIDataField1, HI_UNF_CC_VBI_DADA_S* pstVBIDataField2)
{
#ifdef SUPPORT_VBI

    HI_S32 s32Ret = HI_SUCCESS;
    static HI_U8 au8buf[25] = {0x00, 0x00, 0x01, 0xbd, 0x00, 0x13, 0x8f, 0x80, 0x05, 0x21, 0x25, 0xb5, 0xf1, 0x27, 0x99, 0xc5,
                               0x03, 0x00, 0x00, 0x00, 0xc5, 0x03, 0x00, 0x00, 0x00
                              };

    HI_UNF_DISP_VBI_DATA_S stVBIData = {0};

    au8buf[17] = 0xf5;
    au8buf[18] = cc_reverse_char(pstVBIDataField1->u8Data1);
    au8buf[19] = cc_reverse_char(pstVBIDataField1->u8Data2);

    au8buf[22] = 0xd5;
    au8buf[23] = cc_reverse_char(pstVBIDataField2->u8Data1);
    au8buf[24] = cc_reverse_char(pstVBIDataField2->u8Data2);

    stVBIData.enType = HI_UNF_DISP_VBI_TYPE_CC;
    stVBIData.pu8DataAddr = au8buf;
    stVBIData.u32DataLen = sizeof(au8buf);

    if (HI_INVALID_HANDLE != s_hVBI)
    {
        s32Ret = HI_UNF_DISP_SendVBIData(s_hVBI, &stVBIData);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_DISP_SendVBIData failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }

#endif

    return HI_SUCCESS;
}
