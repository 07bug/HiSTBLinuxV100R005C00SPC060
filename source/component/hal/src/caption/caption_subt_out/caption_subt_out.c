#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <assert.h>
#include <unistd.h>

#include "hi_type.h"
#include "hi_common.h"

#include "hi_unf_disp.h"
#include "hi_unf_avplay.h"
#include "hi_unf_so.h"

#include "tvos_hal_common.h"
#include "caption_out_common.h"

#ifdef LINUX_OS
#include "hi_go.h"
#else
#include "caption_osd.h"
#include "caption_subt_out.h"
#endif

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPTION"

#define  HI_INVALID_HANDLE    (0xffffffff)

#define  SUBT_SURFACE_WIDTH   (720)
#define  SUBT_SURFACE_HEIGHT  (576)
#define  SUBT_SCREEN_WIDTH    (1920)
#define  SUBT_SCREEN_HEIGHT   (1080)

#define SUBT_OUTPUT_HANDLE    (0xFE00)
#define SUBT_BITWIDTH_8_BITS  (8)
#define SUBT_BITWIDTH_32_BITS (32)
#define SUBT_PIXBYTE          (4)

#ifdef LINUX_OS
#define SUBT_FONT_FILE "/usr/data/font/higo_gb2312.ubf"
#endif

//subt bitmap buffer struct
typedef struct hiSUBT_RENDER_BUFFER_S
{
    HI_U8* pu8Buffer;
    HI_U32 u32BufferW;
    HI_U32 u32BufferH;
} SUBT_BUFFER_S;

//int flag
static HI_BOOL s_bInit = HI_FALSE;

#ifdef LINUX_OS
//osd layer
static HI_HANDLE s_hLayer = HIGO_INVALID_HANDLE;

//layer surface
static HI_HANDLE s_hLayerSurface = HIGO_INVALID_HANDLE;

//subt surface
static HI_HANDLE s_hSubtSurface = HIGO_INVALID_HANDLE;

//font
static HI_HANDLE s_hFont = HIGO_INVALID_HANDLE;

//surface lock data
HI_PIXELDATA s_pData;

#else

//subt surface handle
static HI_HANDLE s_hSurface = HI_INVALID_HANDLE;

//screen width
static HI_U32 s_u32ScreenWidth = SUBT_SCREEN_WIDTH;

//screen height
static HI_U32 s_u32ScreenHeight = SUBT_SCREEN_HEIGHT;

//bitmap buff info
static SUBT_BUFFER_S s_stBitmapBuffInfo = {HI_NULL, SUBT_SURFACE_WIDTH, SUBT_SURFACE_HEIGHT};

#endif

static HI_S32 subt_draw_8bitmap(const HI_UNF_SO_GFX_S* pstGfx, unsigned char* pBuffer)
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 u32TmpPointIdx   = 0;
    HI_U32 u32TmpBaseIdx = 0;
    HI_U32 u32PaletteIdx = 0;

    for (i = 0; i < pstGfx->h; i++)
    {
        for (j = 0; j < pstGfx->w; j++)
        {
            u32TmpPointIdx = i * pstGfx->w + j;

            if (u32TmpPointIdx > pstGfx->u32Len)
            {
                break;
            }

#ifdef LINUX_OS
            //i * pData[0].Pitch + 4 * j
            u32TmpBaseIdx = (i * s_pData[0].Pitch) + (4 * j);
#else

            //i * SurfaceWidth*4 + 4 * j
            u32TmpBaseIdx = SUBT_PIXBYTE * u32TmpPointIdx;
#endif

            u32PaletteIdx = pstGfx->pu8PixData[u32TmpPointIdx];

            if (u32PaletteIdx >= HI_UNF_SO_PALETTE_ENTRY)
            {
                break;
            }

#ifdef LINUX_OS
            pBuffer[u32TmpBaseIdx + 3] = pstGfx->stPalette[u32PaletteIdx].u8Alpha;
            pBuffer[u32TmpBaseIdx + 2] = pstGfx->stPalette[u32PaletteIdx].u8Red;
            pBuffer[u32TmpBaseIdx + 1] = pstGfx->stPalette[u32PaletteIdx].u8Green;
            pBuffer[u32TmpBaseIdx + 0] = pstGfx->stPalette[u32PaletteIdx].u8Blue;

#else
            pBuffer[u32TmpBaseIdx + 3] = pstGfx->stPalette[u32PaletteIdx].u8Alpha;
            pBuffer[u32TmpBaseIdx + 2] = pstGfx->stPalette[u32PaletteIdx].u8Blue;
            pBuffer[u32TmpBaseIdx + 1] = pstGfx->stPalette[u32PaletteIdx].u8Green;
            pBuffer[u32TmpBaseIdx + 0] = pstGfx->stPalette[u32PaletteIdx].u8Red;
#endif
        }
    }

    return HI_SUCCESS;
}

static HI_S32 subt_draw_32bitmap(const HI_UNF_SO_GFX_S* pstGfx, unsigned char* pBuffer)
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 u32PixIdx = 0;
    HI_U32 u32TmpPointIdx = 0;
    HI_U32 u32TmpBaseIdx = 0;

    for (i = 0; i < pstGfx->h; i++)
    {
        for (j = 0; j < pstGfx->w; j++)
        {
            u32TmpPointIdx = i * pstGfx->w + j;

            if (u32TmpPointIdx > (pstGfx->u32Len))
            {
                break;
            }

#ifdef LINUX_OS
            //i * pData[0].Pitch + 4 * j
            u32TmpBaseIdx = (i * s_pData[0].Pitch) + (4 * j);

            pBuffer[u32TmpBaseIdx + 3] = pstGfx->pu8PixData[u32PixIdx++];/*alpha*/
            pBuffer[u32TmpBaseIdx + 0] = pstGfx->pu8PixData[u32PixIdx++];/*u8Red*/
            pBuffer[u32TmpBaseIdx + 1] = pstGfx->pu8PixData[u32PixIdx++];/*u8Green*/
            pBuffer[u32TmpBaseIdx + 2] = pstGfx->pu8PixData[u32PixIdx++];/*u8Blue*/

#else

            //i * SurfaceWidth*4 + 4 * j
            u32TmpBaseIdx = SUBT_PIXBYTE * u32TmpPointIdx;

            pBuffer[u32TmpBaseIdx + 3] = pstGfx->pu8PixData[u32PixIdx++];/*alpha*/
            pBuffer[u32TmpBaseIdx + 0] = pstGfx->pu8PixData[u32PixIdx++];/*u8Blue*/
            pBuffer[u32TmpBaseIdx + 1] = pstGfx->pu8PixData[u32PixIdx++];/*u8Green*/
            pBuffer[u32TmpBaseIdx + 2] = pstGfx->pu8PixData[u32PixIdx++];/*u8Red*/
#endif
        }
    }

    return HI_SUCCESS;
}

static HI_S32 subt_blit_gfx_to_buff(const HI_UNF_SO_GFX_S* pstGfx, unsigned char* pBuffer)
{
    if (SUBT_BITWIDTH_8_BITS == pstGfx->s32BitWidth)
    {
        subt_draw_8bitmap(pstGfx, pBuffer);
    }
    else if (SUBT_BITWIDTH_32_BITS == pstGfx->s32BitWidth)
    {
        subt_draw_32bitmap(pstGfx, pBuffer);
    }

    return HI_SUCCESS;
}

#ifdef LINUX_OS
static HI_S32 subt_higo_surface_init(HI_HANDLE hOut)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s_hLayer = hOut;

    if (HIGO_INVALID_HANDLE == s_hLayer)
    {
        HAL_ERROR( "s_hLayer failed! s32Ret = 0x%x !\n", s32Ret);

        return HI_FAILURE;
    }

    HAL_DEBUG("s_hLayer = 0x%x !\n", s_hLayer);

    s32Ret =  HI_GO_GetLayerSurface(s_hLayer, &s_hLayerSurface);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to get layer surface! s32Ret = 0x%x !\n", s32Ret);
        goto RET;
    }

    HAL_DEBUG("s_hLayerSurface = 0x%x !\n", s_hLayerSurface);

    s32Ret = HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to HI_GO_FillRect, s32Ret = 0x%x !\n", s32Ret);
        goto RET;
    }

    s32Ret = HI_GO_CreateText(SUBT_FONT_FILE, NULL, &s_hFont);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to create the font: higo_gb2312.ubf s32Ret = 0x%x!\n", s32Ret);
        goto RET;
    }

    HAL_DEBUG("-----%s, %d---\n", __FUNCTION__, __LINE__);

    s32Ret = HI_GO_SetTextColor(s_hFont, 0xffffffff);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_GO_SetTextColor failed. s32Ret = 0x%x!\n", s32Ret);
    }

    return HI_SUCCESS;

RET:

    if (HIGO_INVALID_HANDLE != s_hSubtSurface)
    {
        (HI_VOID)HI_GO_FreeSurface(s_hSubtSurface);
        s_hSubtSurface = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFont)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFont);
        s_hFont = HIGO_INVALID_HANDLE;
    }

    s_hLayerSurface = HIGO_INVALID_HANDLE;
    s_hLayer = HIGO_INVALID_HANDLE;

    HAL_ERROR("%s, %d\n", __FUNCTION__, __LINE__);

    return HI_FAILURE;
}

static HI_S32 subt_higo_surface_deInit()
{
    if (HIGO_INVALID_HANDLE != s_hFont)
    {
        (HI_VOID)HI_GO_DestroyText(s_hFont);
        s_hFont = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hSubtSurface)
    {
        (HI_VOID)HI_GO_FreeSurface(s_hSubtSurface);
        s_hSubtSurface = HIGO_INVALID_HANDLE;
    }

    s_hLayerSurface = HIGO_INVALID_HANDLE;

    return HI_FAILURE;
}

static HI_S32 subt_higo_checkSurfaceSize(const HI_UNF_SO_GFX_S* pstGfx)
{
    HI_S32 s32Width = 0;
    HI_S32 s32Height = 0;
    HI_PIXELDATA pData;
    HI_S32 s32Ret = HI_SUCCESS;

    if (HIGO_INVALID_HANDLE != s_hSubtSurface)
    {
        (HI_VOID)HI_GO_LockSurface(s_hSubtSurface, pData, HI_TRUE);
        (HI_VOID)HI_GO_GetSurfaceSize(s_hSubtSurface, &s32Width, &s32Height);
        (HI_VOID)HI_GO_UnlockSurface(s_hSubtSurface);
    }

    if (s32Width != pstGfx->u32CanvasWidth ||
        s32Height != pstGfx->u32CanvasHeight)
    {
        if (HIGO_INVALID_HANDLE != s_hSubtSurface)
        {
            (HI_VOID)HI_GO_FreeSurface(s_hSubtSurface);
            s_hSubtSurface = HIGO_INVALID_HANDLE;
        }

        s32Ret = HI_GO_CreateSurface(pstGfx->u32CanvasWidth, pstGfx->u32CanvasHeight, HIGO_PF_8888, &s_hSubtSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_CreateSurface Failed. s32Ret = 0x%x!\n", s32Ret);
        }
    }

    return s32Ret;
}
static HI_S32 subt_higo_lockSurfaceAddr(const HI_UNF_SO_GFX_S* pstGfx)
{
    HI_S32 s32Width = 0;
    HI_S32 s32Height = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_GO_LockSurface(s_hSubtSurface, s_pData, HI_TRUE);

    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    s32Ret = HI_GO_GetSurfaceSize(s_hSubtSurface, &s32Width, &s32Height);

    if (HI_SUCCESS != s32Ret)
    {
        (HI_VOID)HI_GO_UnlockSurface(s_hSubtSurface);
        return HI_FAILURE;
    }

    if (NULL == (HI_U8*)s_pData[0].pData)
    {
        (HI_VOID)HI_GO_UnlockSurface(s_hSubtSurface);
        return HI_FAILURE;
    }

    if (s32Width * s32Height * s_pData[0].Bpp < pstGfx->h * pstGfx->w * 4)
    {
        (HI_VOID)HI_GO_UnlockSurface(s_hSubtSurface);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_higo_unLockSurfaceAddr()
{
    return HI_GO_UnlockSurface(s_hSubtSurface);
}

static HI_VOID subt_higo_convertRect(HI_HANDLE hSrcSurface, HI_HANDLE hDstSurface, HI_RECT stSrcRect, HI_RECT* pstDstRect)
{
    HI_S32 s32SrcWidth = 0;
    HI_S32 s32SrcHeight = 0;
    HI_S32 s32DstWidth = 0;
    HI_S32 s32DstHeight = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_GO_GetSurfaceSize(hSrcSurface, &s32SrcWidth, &s32SrcHeight);
    s32Ret |= HI_GO_GetSurfaceSize(hDstSurface, &s32DstWidth, &s32DstHeight);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("----\n %s, %d HI_GO_GetSurfaceSize fail , ret = 0x%x-----\n",  __FUNCTION__, __LINE__, s32Ret);
        return;
    }

    pstDstRect->x = (stSrcRect.x * s32DstWidth) / s32SrcWidth;
    pstDstRect->y = (stSrcRect.y * s32DstHeight) / s32SrcHeight;
    pstDstRect->w = (stSrcRect.w * s32DstWidth) / s32SrcWidth;
    pstDstRect->h = (stSrcRect.h * s32DstHeight) / s32SrcHeight;

    if ((pstDstRect->x + pstDstRect->w) > s32DstWidth)
    {
        pstDstRect->w = s32DstWidth - pstDstRect->x;
    }

    if ((pstDstRect->y + pstDstRect->h) > s32DstHeight)
    {
        pstDstRect->h = s32DstHeight - pstDstRect->y;
    }
}

static HI_S32 subt_higo_draw_blit(const HI_UNF_SO_GFX_S* pstGfx)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HIGO_BLTOPT_S stBlitOpt;
    HI_RECT stSrcRect = {0, 0, 0, 0};
    HI_RECT stDstRect = {0, 0, 0, 0};

    stSrcRect.x = pstGfx->x;
    stSrcRect.y = pstGfx->y;
    stSrcRect.w = pstGfx->w;
    stSrcRect.h = pstGfx->h;

    subt_higo_convertRect(s_hSubtSurface, s_hLayerSurface, stSrcRect, &stDstRect);

    stSrcRect.x = 0;
    stSrcRect.y = 0;

    memset(&stBlitOpt, 0, sizeof(HIGO_BLTOPT_S));
    stBlitOpt.EnableScale = HI_TRUE;

    s32Ret = HI_GO_Blit(s_hSubtSurface, &stSrcRect, s_hLayerSurface, &stDstRect, &stBlitOpt);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("----\n %s, %d HI_GO_Blit fail , ret = 0x%x-----\n",  __FUNCTION__, __LINE__, s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_GO_RefreshLayer(s_hLayer, HI_NULL);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("----\n %s, %d HI_GO_RefreshLayer fail , ret = 0x%x-----\n",  __FUNCTION__, __LINE__, s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_higo_draw_bitmap(const HI_UNF_SO_GFX_S* pstGfx)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if ((HIGO_INVALID_HANDLE == s_hLayer) ||
        (HIGO_INVALID_HANDLE == s_hLayerSurface) ||
        (HIGO_INVALID_HANDLE == s_hSubtSurface))
    {
        HAL_ERROR("error, osd deinit already. \n");
        return HI_FAILURE;
    }

    if (HI_SUCCESS != subt_higo_checkSurfaceSize(pstGfx))
    {
        HAL_ERROR("subt_higo_checkSurfaceSize failed!\n");
        return HI_FAILURE;
    }

    s32Ret = subt_higo_lockSurfaceAddr(pstGfx);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_getSurfaceAddr failed, ret = 0x%x !\n", s32Ret);

        return HI_FAILURE;
    }

    s32Ret = subt_blit_gfx_to_buff(pstGfx, (unsigned char*)s_pData[0].pData);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_remalloc_buff failed, ret = 0x%x !\n", s32Ret);
        subt_higo_unLockSurfaceAddr();
        return HI_FAILURE;
    }

    s32Ret = subt_higo_unLockSurfaceAddr();

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_higo_unLockSurfaceAddr failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret = subt_higo_draw_blit(pstGfx);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_higo_draw_blit failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_higo_draw_text(const HI_UNF_SO_TEXT_S* pstText)
{
    HI_RECT stSrcRect = {0, 0, 0, 0};
    HI_RECT stDstRect = {0, 0, 0, 0};
    HIGO_BLTOPT_S stBlitOpt;
    HI_S32 s32Ret = HI_SUCCESS;

    stSrcRect.x = pstText->x;
    stSrcRect.y = pstText->y;
    stSrcRect.w = pstText->w;
    stSrcRect.h = pstText->h;

    if ((HIGO_INVALID_HANDLE == s_hLayer) || (HIGO_INVALID_HANDLE == s_hLayerSurface) || (HIGO_INVALID_HANDLE == s_hSubtSurface))
    {
        HAL_ERROR("error, osd deinit already. \n");
        return HI_FAILURE;
    }

    subt_higo_convertRect(s_hSubtSurface, s_hLayerSurface, stSrcRect, &stDstRect);

    if (HIGO_INVALID_HANDLE != s_hFont && HIGO_INVALID_HANDLE != s_hLayer)
    {
        HI_CHAR* pszText = (HI_CHAR*)pstText->pu8Data;
        //lint -e655
        s32Ret = HI_GO_TextOutEx(s_hFont, s_hSubtSurface, pszText, &stSrcRect,
            (HIGO_LAYOUT_E)(HIGO_LAYOUT_WRAP | HIGO_LAYOUT_HCENTER | HIGO_LAYOUT_BOTTOM));
        //lint +e655

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_TextOutEx failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }

        memset(&stBlitOpt, 0, sizeof(HIGO_BLTOPT_S));

        stBlitOpt.EnableScale = HI_TRUE;

        s32Ret = HI_GO_Blit (s_hSubtSurface, &stSrcRect, s_hLayerSurface, &stDstRect, &stBlitOpt);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_Blit failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }

        s32Ret = HI_GO_RefreshLayer(s_hLayer, HI_NULL);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_Blit failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 subt_higo_clear(HI_UNF_SO_CLEAR_PARAM_S* pParam)
{
    HI_CHAR aTextClear[] = "";
    HI_RECT stSrcRect = {0, 0, 0, 0};
    HI_RECT stDstRect = {0, 0, 0, 0};
    HI_S32 s32Ret = HI_SUCCESS;

    HAL_CHK_RETURN((HIGO_INVALID_HANDLE == s_hLayer), HI_FAILURE, "s_hLayer invalid");
    HAL_CHK_RETURN((HIGO_INVALID_HANDLE == s_hLayerSurface), HI_FAILURE, "s_hLayerSurface invalid");
    HAL_CHK_RETURN((HIGO_INVALID_HANDLE == s_hSubtSurface), HI_FAILURE, "s_hSubtSurface invalid");

    if (HI_NULL == pParam)
    {
        stSrcRect.x = 0;
        stSrcRect.y = 0;
        stSrcRect.w = 0;
        stSrcRect.h = 0;
    }
    else
    {
        stSrcRect.x = pParam->x;
        stSrcRect.y = pParam->y;
        stSrcRect.w = pParam->w;
        stSrcRect.h = pParam->h;
    }

    subt_higo_convertRect(s_hSubtSurface, s_hLayerSurface, stSrcRect, &stDstRect);

    if (stDstRect.w == 0 || stDstRect.h == 0)
    {
        s32Ret = HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }
    else
    {
        s32Ret = HI_GO_FillRect(s_hLayerSurface, &stDstRect, 0x00000000, HIGO_COMPOPT_NONE);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }

    if (HIGO_INVALID_HANDLE != s_hFont)
    {
        //lint -e655
        s32Ret = HI_GO_TextOutEx(s_hFont, s_hLayerSurface, aTextClear, &stDstRect,
                                 (HIGO_LAYOUT_E)(HIGO_LAYOUT_WRAP | HIGO_LAYOUT_HCENTER | HIGO_LAYOUT_BOTTOM));
        //lint +e655

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_TextOutEx failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }
    }

    s32Ret = HI_GO_RefreshLayer(s_hLayer, NULL);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_GO_TextOutEx failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#else

static HI_S32 subt_osd_check_buffinit(SUBT_BUFFER_S* pstCurBuffInfo)
{
    if (HI_NULL == pstCurBuffInfo->pu8Buffer)
    {
        pstCurBuffInfo->pu8Buffer = (HI_U8*)malloc(SUBT_SURFACE_WIDTH * SUBT_SURFACE_HEIGHT * SUBT_PIXBYTE);

        if (HI_NULL == pstCurBuffInfo->pu8Buffer)
        {
            return HI_FAILURE;
        }

        pstCurBuffInfo->u32BufferW = SUBT_SURFACE_WIDTH;
        pstCurBuffInfo->u32BufferH = SUBT_SURFACE_HEIGHT;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_osd_get_rect( HI_S32 x, HI_S32 y, HI_S32 w, HI_S32 h, HI_RECT_S* pstRect)
{

    pstRect->s32X = (x * s_u32ScreenWidth) / s_stBitmapBuffInfo.u32BufferW;
    pstRect->s32Y = (y * s_u32ScreenHeight) / s_stBitmapBuffInfo.u32BufferH;
    pstRect->s32Width = (w * s_u32ScreenWidth) / s_stBitmapBuffInfo.u32BufferW;
    pstRect->s32Height = (h * s_u32ScreenHeight) / s_stBitmapBuffInfo.u32BufferH;

    if ((HI_U32)(pstRect->s32X + pstRect->s32Width) > s_u32ScreenWidth)
    {
        pstRect->s32Width = s_u32ScreenWidth - pstRect->s32X;
    }

    if ((HI_U32)(pstRect->s32Y + pstRect->s32Height) > s_u32ScreenHeight)
    {
        pstRect->s32Height = s_u32ScreenHeight - pstRect->s32Y;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_osd_remalloc_buff(SUBT_BUFFER_S* pstCurBuffInfo, const HI_U32 u32NewWidth, const HI_U32 u32NewHeight)
{
    if (NULL == pstCurBuffInfo)
    {
        HAL_ERROR("pstCurBuffInfo is null");
        return HI_FAILURE;
    }

    if ((0 == u32NewWidth) || (0 == u32NewHeight))
    {
        HAL_ERROR("0 == u32NewW || 0 == u32NewH");
        return HI_FAILURE;
    }

    if ((pstCurBuffInfo->u32BufferW == u32NewWidth) && (pstCurBuffInfo->u32BufferH == u32NewHeight))
    {
        return HI_SUCCESS;
    }

    if (HI_NULL != pstCurBuffInfo->pu8Buffer)
    {
        free(pstCurBuffInfo->pu8Buffer);
        pstCurBuffInfo->pu8Buffer = HI_NULL;
        pstCurBuffInfo->u32BufferW = 0;
        pstCurBuffInfo->u32BufferH = 0;
    }

    pstCurBuffInfo->pu8Buffer = (HI_U8*)malloc(u32NewWidth * u32NewHeight * SUBT_PIXBYTE);

    if (HI_NULL == pstCurBuffInfo->pu8Buffer)
    {
        HAL_ERROR("create subt bitmapbuffer fail!\n");
        return HI_FAILURE;
    }

    pstCurBuffInfo->u32BufferW = u32NewWidth;
    pstCurBuffInfo->u32BufferH = u32NewHeight;

    memset(pstCurBuffInfo->pu8Buffer, 0x0, u32NewWidth * u32NewHeight * SUBT_PIXBYTE);

    return HI_SUCCESS;
}

static HI_S32 subt_osd_draw_bitmap(const HI_UNF_SO_GFX_S* pstGfx)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_subt_output_draw failed, s_hSurface = 0x%x !\n", s_hSurface);
        return HI_FAILURE;
    }

    s32Ret = subt_osd_check_buffinit(&s_stBitmapBuffInfo);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_check_buffinit failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret = subt_osd_remalloc_buff(&s_stBitmapBuffInfo, pstGfx->u32CanvasWidth, pstGfx->u32CanvasHeight);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_remalloc_buff failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret = subt_blit_gfx_to_buff(pstGfx, s_stBitmapBuffInfo.pu8Buffer);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_remalloc_buff failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    HI_RECT_S stSrcRect = {0, 0, 0, 0};

    stSrcRect.s32X = pstGfx->x;
    stSrcRect.s32Y = pstGfx->y;
    stSrcRect.s32Width = pstGfx->w;
    stSrcRect.s32Height = pstGfx->h;

    CAPTION_OSD_SURFACE_ATTR_S stAttr;

    memset(&stAttr, 0x0, sizeof(CAPTION_OSD_SURFACE_ATTR_S));

    stAttr.u32Width = s_stBitmapBuffInfo.u32BufferW;
    stAttr.u32Height = s_stBitmapBuffInfo.u32BufferH;
    stAttr.enPixelFormat = CAPTION_OSD_PF_8888;

    HAL_DEBUG("caption_osd_subt_draw_bitmap()! W:H = %d:%d\n", stAttr.u32Width, stAttr.u32Height);

    s32Ret = caption_osd_subt_draw_bitmap(s_hSurface, s_stBitmapBuffInfo.pu8Buffer, &stAttr, &stSrcRect);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_remalloc_buff failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_osd_draw_text(const HI_UNF_SO_TEXT_S* pstText)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_RECT_S stSrcRect = {0, 0, 0, 0};
    HI_RECT_S stDesRect = {0, 0, 0, 0};
    HI_CHAR* pszText = (HI_CHAR*)pstText->pu8Data;

    if (HI_NULL == pstText->pu8Data)
    {
        return HI_FAILURE;
    }

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_subt_output_draw failed, s_hSurface = 0x%x !\n", s_hSurface);
        return HI_FAILURE;
    }

    stSrcRect.s32X = 0;
    stSrcRect.s32Y = 0;
    stSrcRect.s32Width = pstText->w;
    stSrcRect.s32Height = pstText->h;

    subt_osd_get_rect(pstText->x, pstText->y, pstText->w, pstText->h, &stDesRect);

    CAPTION_OSD_CCTEXT_ATTR_S pstCCTextAttr;

    pstCCTextAttr.u32BufLen = strlen(pszText);
    pstCCTextAttr.u32bgColor = 0xff000000;
    pstCCTextAttr.u32fgColor = 0xffffffff;
    pstCCTextAttr.u8fontSize = 21;

    CAPTION_OSD_SURFACE_ATTR_S pstSurAttr;

    pstSurAttr.u32Width = s_u32ScreenWidth;
    pstSurAttr.u32Height = s_u32ScreenHeight;
    pstSurAttr.enPixelFormat = CAPTION_OSD_PF_8888;

    s32Ret = caption_osd_drawtext(s_hSurface, &pstSurAttr, &stDesRect, (HI_CHAR*)pszText, &pstCCTextAttr);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_remalloc_buff failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subt_osd_clear(HI_UNF_SO_CLEAR_PARAM_S* pParam)
{
    HI_RECT_S stDesRect = {0, 0, 0, 0};
    CAPTION_OSD_SURFACE_ATTR_S   pstSurAttr;

    if (HI_INVALID_HANDLE == s_hSurface)
    {
        HAL_ERROR("caption_subt_output_draw failed, s_hSurface = 0x%x !\n", s_hSurface);
        return HI_FAILURE;
    }

    if (HI_NULL == pParam)
    {
        stDesRect.s32Width = 0;
        stDesRect.s32Height = 0;
    }
    else
    {
        subt_osd_get_rect(pParam->x, pParam->y, pParam->w, pParam->h, &stDesRect);
    }

    pstSurAttr.u32Width = s_u32ScreenWidth;
    pstSurAttr.u32Height = s_u32ScreenHeight;
    pstSurAttr.enPixelFormat = CAPTION_OSD_PF_8888;

    if ((0 == stDesRect.s32Width) || (0 == stDesRect.s32Height))
    {
        stDesRect.s32X = 0 ;
        stDesRect.s32Y = 0 ;
        stDesRect.s32Width = s_u32ScreenWidth;
        stDesRect.s32Height = s_u32ScreenHeight;
    }

    caption_osd_fillrect(s_hSurface, &pstSurAttr, &stDesRect, 0x00000000);
    return HI_SUCCESS;
}

#endif

static HI_S32 subt_draw_bitmap(const HI_UNF_SO_GFX_S* pstGfx)
{

    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS
    s32Ret = subt_higo_draw_bitmap(pstGfx);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_higo_draw_bitmap failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#else
    s32Ret = subt_osd_draw_bitmap(pstGfx);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_draw_bitmap failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#endif

    return HI_SUCCESS;
}

static HI_S32 subt_draw_text(const HI_UNF_SO_TEXT_S* pstText)
{
    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS
    s32Ret = subt_higo_draw_text(pstText);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_higo_draw_text failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#else
    s32Ret = subt_osd_draw_text(pstText);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_draw_text failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#endif

    return HI_SUCCESS;
}

HI_S32 caption_subt_output_init(HI_HANDLE* phOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (s_bInit)
    {
        return HI_SUCCESS;
    }

    HAL_DEBUG("-----%s, %d---\n", __FUNCTION__, __LINE__);

    s32Ret = caption_output_init(phOut);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_init failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

#ifdef LINUX_OS
    s32Ret = subt_higo_surface_init(*phOut);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_higo_init failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    *phOut = SUBT_OUTPUT_HANDLE;

#endif

    s_bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 caption_subt_output_deinit(HI_HANDLE hOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (!s_bInit)
    {
        return HI_SUCCESS;
    }

#ifdef LINUX_OS
    (HI_VOID)subt_higo_surface_deInit();
#else

    if (HI_NULL != s_stBitmapBuffInfo.pu8Buffer)
    {
        free(s_stBitmapBuffInfo.pu8Buffer);

        s_stBitmapBuffInfo.pu8Buffer = HI_NULL;
    }

#endif

    s32Ret = caption_output_deinit();

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("subt_osd_deinit failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s_bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 caption_subt_output_create_surface(HI_RECT_S stRect)
{
    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS

    if (HIGO_INVALID_HANDLE == s_hSubtSurface)
    {
        s32Ret = HI_GO_CreateSurface(SUBT_SURFACE_WIDTH, SUBT_SURFACE_HEIGHT, HIGO_PF_8888, &s_hSubtSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_CreateSurface Failed. s32Ret = 0x%x!\n", s32Ret);

            return HI_FAILURE;
        }

        s32Ret = HI_GO_FillRect(s_hSubtSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FillRect Failed. s32Ret = 0x%x!\n", s32Ret);

            return HI_FAILURE;
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

HI_S32 caption_subt_output_destory_surface()
{
    HI_S32 s32Ret = HI_FAILURE;

#ifdef LINUX_OS

    if (HIGO_INVALID_HANDLE != s_hSubtSurface)
    {
        s32Ret = HI_GO_FreeSurface(s_hSubtSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_FreeSurface failed, ret = 0x%x !\n", s32Ret);

            return HI_FAILURE;
        }

        s_hSubtSurface = HIGO_INVALID_HANDLE;
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

HI_S32 caption_subt_output_draw(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S* pstInfo, HI_VOID* pArg)
{
    HI_S32 s32Ret = HI_FAILURE;

    HAL_DEBUG("\n %s, %d \n", __FUNCTION__, __LINE__);

    if ((0 == pstInfo->unSubtitleParam.stGfx.u32CanvasWidth) ||
        (0 == pstInfo->unSubtitleParam.stGfx.u32CanvasHeight))
    {
        return HI_SUCCESS;
    }

    HAL_DEBUG("display w/h is [%d][%d]\n", pstInfo->unSubtitleParam.stGfx.u32CanvasWidth,
              pstInfo->unSubtitleParam.stGfx.u32CanvasHeight);

    switch (pstInfo->eType)
    {
        case HI_UNF_SUBTITLE_BITMAP:
        {
            HAL_ERROR("\n %s, %d , draw bitmap\n", __FUNCTION__, __LINE__);

            s32Ret = subt_draw_bitmap(&(pstInfo->unSubtitleParam.stGfx));
            break;
        }

        case HI_UNF_SUBTITLE_TEXT:
        {
            HAL_ERROR("subt_draw_text() \n");

            s32Ret = subt_draw_text(&(pstInfo->unSubtitleParam.stText));
            break;
        }

        case HI_UNF_SUBTITLE_ASS:
        default:
            break;
    }

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_subt_output_draw failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 caption_subt_output_clear(HI_U32 u32UserData, HI_VOID* pArg)
{
    HI_UNF_SO_CLEAR_PARAM_S* pParam = (HI_UNF_SO_CLEAR_PARAM_S*)pArg;

#ifdef LINUX_OS
    subt_higo_clear(pParam);
#else
    subt_osd_clear(pParam);
#endif

    return HI_SUCCESS;
}
