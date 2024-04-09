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

#include "hi_unf_disp.h"

#ifdef LINUX_OS
#include "hi_go.h"
#endif

#include "hi_type.h"
#include "hi_common.h"
#include "tvos_hal_common.h"
#include "caption_osd.h"
#include "caption_out_common.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPTION"

#define  HI_INVALID_HANDLE    (0xffffffff)

//init flag
static HI_BOOL s_bInit = HI_FALSE;

#ifndef LINUX_OS

#define SUBT_OUTPUT_HANDLE    (0xFE00)

//subt surface handle
static HI_HANDLE s_hSurface = HI_INVALID_HANDLE;

//screen width
static HI_U32 s_u32ScreenWidth = 0;

//screen height
static HI_U32 s_u32ScreenHeight = 0;
#endif

#ifdef LINUX_OS
static HI_HANDLE s_hLayer = HIGO_INVALID_HANDLE;

static HI_S32 caption_output_higo_init(HI_HANDLE* phLayer)
{
    HI_U32 u32Width = 0;
    HI_U32 u32Height = 0;
    HI_S32 s32Ret = HI_FAILURE;

    *phLayer = HIGO_INVALID_HANDLE;

    HIGO_LAYER_INFO_S stLayerInfo = {0};

    HAL_DEBUG("-----%s, %d---\n", __FUNCTION__, __LINE__);

    s32Ret = HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to create the layer hd 0, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_DISP_GetVirtualScreen(HI_UNF_DISPLAY1, &u32Width, &u32Height);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to get the virtual screen, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    stLayerInfo.CanvasWidth = u32Width;
    stLayerInfo.CanvasHeight = u32Height;
    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_NORMAL;
    stLayerInfo.PixelFormat = HIGO_PF_8888;
    s32Ret = HI_GO_CreateLayer(&stLayerInfo, phLayer);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to create the layer hd 0, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    HIGO_LAYER_KEY_S stKey;
    stKey.ColorKey = HIGO_TRANSPARENT_COLOR_KEY;
    stKey.bEnableCK = HI_TRUE;
    s32Ret = HI_GO_SetLayerColorkey(*phLayer, &stKey);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_GO_SetLayerColorkey ret = 0x%x !\n", s32Ret);
    }

    return HI_SUCCESS;
}

static HI_S32 caption_output_higo_deinit(HI_HANDLE hLayer)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HIGO_INVALID_HANDLE != hLayer)
    {
        s32Ret = HI_GO_DestroyLayer(hLayer);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_GO_DestroyLayer failed, ret = 0x%x  hLayer 0x%x !\n", s32Ret, hLayer);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

#endif

HI_S32 caption_output_create_surface(HI_RECT_S stRect, HI_HANDLE* phSurface)
{

    if (HI_NULL == phSurface)
    {
        HAL_ERROR("NULL param !\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == s_bInit)
    {
        HAL_ERROR("caption_subt_output_create_surface failed, s_bInit = 0x%x !\n", s_bInit);
        return HI_FAILURE;
    }

#ifndef LINUX_OS
    HI_S32 s32Ret = HI_FAILURE;
    CAPTION_OSD_SURFACE_ATTR_S stOsdAttr;

    stOsdAttr.u32Width = stRect.s32Width;
    stOsdAttr.u32Height = stRect.s32Height;
    stOsdAttr.enPixelFormat = CAPTION_OSD_PF_8888;

    if ((s_u32ScreenWidth != stOsdAttr.u32Width) || (s_u32ScreenHeight != stOsdAttr.u32Height))
    {
        if (HI_INVALID_HANDLE != s_hSurface)
        {
            caption_osd_destroy_surface(s_hSurface);
            s_hSurface = HI_INVALID_HANDLE;
        }

        s32Ret = caption_osd_create_surface(&stOsdAttr, &s_hSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("caption_osd_create_surface failed, ret = 0x%x !\n", s32Ret);
            return HI_FAILURE;
        }

        s_u32ScreenWidth = stOsdAttr.u32Width;
        s_u32ScreenHeight = stOsdAttr.u32Height;
    }

    *phSurface = s_hSurface;

#endif
    return HI_SUCCESS;
}

HI_S32 caption_output_destory_surface()
{

#ifndef LINUX_OS
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_INVALID_HANDLE != s_hSurface)
    {
        s32Ret = caption_osd_clear_surface(s_hSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("caption_osd_clear_surface failed, ret = 0x%x !\n", s32Ret);
        }

        s32Ret = caption_osd_destroy_surface(s_hSurface);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("caption_osd_destroy_surface failed, ret = 0x%x !\n", s32Ret);
        }

        s_hSurface = HI_INVALID_HANDLE;

        s_u32ScreenWidth = 0;
        s_u32ScreenHeight = 0;
    }

#endif
    return HI_SUCCESS;
}

HI_S32 caption_output_init(HI_HANDLE* phOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    //init
#ifdef LINUX_OS

    //already init
    if ((s_bInit) && (HIGO_INVALID_HANDLE != s_hLayer))
    {
        *phOut = s_hLayer;
        return HI_SUCCESS;
    }

    *phOut = HIGO_INVALID_HANDLE;

    s32Ret = caption_output_higo_init(&s_hLayer);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("failed to init higo! ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    *phOut = s_hLayer;
#else

    if (s_bInit)
    {
        return HI_SUCCESS;
    }

    caption_osd_init();

    s_u32ScreenWidth = 0;
    s_u32ScreenHeight = 0;
    s_hSurface = HI_INVALID_HANDLE;

    *phOut = SUBT_OUTPUT_HANDLE;

#endif

    s_bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 caption_output_deinit()
{
    HI_S32 s32Ret = HI_FAILURE;

    //not init
    if (!s_bInit)
    {
        return HI_SUCCESS;
    }

    //deinit
#ifdef LINUX_OS
    s32Ret = caption_output_higo_deinit(s_hLayer);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_destory_surface failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s_hLayer = HIGO_INVALID_HANDLE;
#else

    s32Ret = caption_output_destory_surface();

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("caption_output_destory_surface failed, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    caption_osd_deinit();

#endif

    s_bInit = HI_FALSE;

    return HI_SUCCESS;
}
