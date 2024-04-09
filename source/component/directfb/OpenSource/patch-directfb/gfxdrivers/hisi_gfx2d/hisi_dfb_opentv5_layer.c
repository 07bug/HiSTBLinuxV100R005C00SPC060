/******************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hisi_dfb_opentv5_layer.c
Version          : Initial Draft
Author           :
Created          : 2017/07/05
Description      : control hard decode dispose
Function List    :


History          :
Date                      Author                    Modification
2017/07/05                sdk                       Created file
******************************************************************************/

/****************************  add include here     *******************************/
#include <config.h>
#include <asm/types.h>
#include <stdio.h>
#include <sys/mman.h>
#include <directfb.h>
#include <direct/debug.h>
#include <direct/messages.h>
#include <sys/ioctl.h>
#include <fbdev/fbdev.h>
#include <core/layers.h>

#include "hi_mpi_disp.h"
#include "hi_unf_vo.h"
#include "hi_mpi_win.h"
#include "hi_mpi_hdmi.h"

/***************************** Macro Definition     *******************************/
#define VIDEO_LAY_ID (1UL)

/***************************** Structure Definition *******************************/


/********************** Global Variable declaration *******************************/



/********************** API forward declarations    ********************************/

/**********************       API realization       ***********************************/

static DFBResult video_init_layer (CoreLayer                  *layer,
                                      void                       *driver_data,
                                      void                       *layer_data,
                                      DFBDisplayLayerDescription *description,
                                      DFBDisplayLayerConfig      *config,
                                      DFBColorAdjustment         *adjustment )
{
    if (HI_SUCCESS != HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL))
    {
		D_ERROR("+++ WARNING HI_MPI_WIN_Init Failure\n");
		return DFB_OK;
	}

    description->caps = DLCAPS_SCREEN_LOCATION | DLCAPS_LEVELS;// | DLCAPS_SURFACE;
    description->type = DLTF_VIDEO | DLTF_STILL_PICTURE;

    /** set name **/
    snprintf(description->name, DFB_DISPLAY_LAYER_DESC_NAME_LENGTH, "HISI Video");

    /** fill out the default configuration **/
    config->flags      = DLCONF_WIDTH | DLCONF_HEIGHT | DLCONF_BUFFERMODE;
    config->buffermode = DLBM_FRONTONLY;
    config->width      = 1920;
    config->height     = 1080;

    return DFB_OK;
}

static DFBResult video_shuttdown_layer(CoreLayer    *layer,
                                              void         *driver_data,
                                              void         *layer_data)
{
    HI_UNF_VO_DeInit();
    return DFB_OK;
}

static DFBResult video_set_region(CoreLayer                  *layer,
                                       void                       *driver_data,
                                       void                       *layer_data,
                                       void                       *region_data,
                                       CoreLayerRegionConfig      *config,
                                       CoreLayerRegionConfigFlags  updated,
                                       CoreSurface                *surface,
                                       CorePalette                *palette,
                                       CoreSurfaceBufferLock      *lock )
{
	HI_UNF_WINDOW_ATTR_S attr;
	HI_HANDLE win;

	if (!layer || !layer->shared)
    {
		D_ERROR("+++ WARNING %s->%d, !layer %d, !layer->shared:%d,Cannot get window handle!\n",__func__,__LINE__,!layer, !layer->shared);
		return DFB_OK;
	}

	win = (HI_HANDLE)((HI_ID_VO << 16) | (HI_UNF_DISPLAY1 << 8)  |(((HI_U32)layer->shared->layer_id - VIDEO_LAY_ID)&0xff));

	if (HI_SUCCESS != HI_UNF_VO_GetWindowAttr(win,  &attr))
    {
		D_ERROR("+++ WARNING HI_UNF_VO_GetWindowAttr Failure\n");
		return DFB_OK;
	}

#if 0/** if set fmt, can not display full screen **/
	attr.stInputRect.s32X       = config->source.x;
	attr.stInputRect.s32Y       = config->source.y;
	attr.stInputRect.s32Width   = config->source.w;
	attr.stInputRect.s32Height  = config->source.h;
#endif
	attr.stOutputRect.s32X      = config->dest.x;
	attr.stOutputRect.s32Y      = config->dest.y;
	attr.stOutputRect.s32Width  = config->dest.w;
	attr.stOutputRect.s32Height = config->dest.h;

	if (HI_SUCCESS != HI_UNF_VO_SetWindowAttr(win, &attr))
    {
		D_ERROR("+++ WARNING HI_UNF_VO_SetWindowAttr Failure\n");
		return DFB_OK;
	}

	return DFB_OK;
}


static DFBResult video_test_region(CoreLayer                   *layer,
                                        void                       *driver_data,
                                        void                       *layer_data,
                                        CoreLayerRegionConfig      *config,
                                        CoreLayerRegionConfigFlags *failed )
{
    return video_set_region(layer, driver_data, layer_data, NULL, config, 0, NULL, NULL, NULL);
}

static DFBResult video_get_level(CoreLayer *layer, void *driver_data, void *layer_data, int *level)
{
    D_ERROR("+++ WARNING UnSupport Get Video Level\n");
	return DFB_OK;
}


static DFBResult video_set_level(CoreLayer *layer, void *driver_data, void *layer_data, int level)
{
    HI_S32 Ret = HI_SUCCESS;

    if (level > 0)
    {
        Ret = HI_UNF_DISP_SetLayerZorder(HI_UNF_DISPLAY1, HI_UNF_DISP_LAYER_VIDEO, HI_LAYER_ZORDER_MOVETOP);
    }
    else if (level < 0)
    {
        Ret = HI_UNF_DISP_SetLayerZorder(HI_UNF_DISPLAY1, HI_UNF_DISP_LAYER_VIDEO, HI_LAYER_ZORDER_MOVEBOTTOM);
    }
    else
    {
        return DFB_OK;
    }

    if (HI_SUCCESS != Ret)
    {
        D_ERROR("+++ WARNING HI_UNF_DISP_SetLayerZorder Fail,ret:0x%x!\n",Ret);
        return DFB_OK;
    }

	return DFB_OK;
}


static DFBResult video_set_color_adjustment(CoreLayer *layer, void *driver_data, void *layer_data, DFBColorAdjustment *adjustment)
{
    //D_ERROR("+++ WARNING Set color adjustment can not support\n");
	return DFB_OK;
}


static DisplayLayerFuncs video_layer_funcs = {
	.InitLayer     = video_init_layer,
    .ShutdownLayer = video_shuttdown_layer,
	.TestRegion    = video_test_region,
	.SetRegion     = video_set_region,
    .GetLevel      = video_get_level,
    .SetLevel      = video_set_level,
    .SetColorAdjustment = video_set_color_adjustment,
};
