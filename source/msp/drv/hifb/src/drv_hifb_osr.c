/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name       : drv_hifb_osr.c
Version         : Initial Draft
Author          :
Created         : 2018/08/01
Description     :
Function List   :


History         :
Date                    Author                Modification
2018/08/01               sdk                  Created file
*************************************************************************************************/


/*********************************add include here***********************************************/
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/file.h>
#include <linux/slab.h>
#include <linux/mm.h>

#include <linux/fb.h>
#include <asm/uaccess.h>

#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>

#include <linux/interrupt.h>
#include "hi_module.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "drv_pdm_ext.h"

#include "hifb.h"
#include "drv_hifb_osr.h"
#include "drv_hifb_mem.h"

#ifdef CFG_HIFB_LOGO_SUPPORT
#include "drv_hifb_logo.h"
#endif

#ifdef CFG_HIFB_FENCE_SUPPORT
#include "drv_hifb_fence.h"
#endif

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
#include "drv_hifb_scrolltext.h"
#endif

#include "drv_hifb_ext.h"
#include "drv_hifb_err.h"

#include "drv_hifb_paracheck.h"
#include "drv_hifb_config.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition *************************************************/
//#define CFG_HIFB_SUPPORT_CONSOLE
//#define CFG_HIFB_PROC_DEBUG

/**
 **mod init this var
 **/
#define HIFB_MAX_WIDTH(u32LayerId)     gs_pstCapacity[u32LayerId].u32MaxWidth
#define HIFB_MAX_HEIGHT(u32LayerId)    gs_pstCapacity[u32LayerId].u32MaxHeight
#define HIFB_MIN_WIDTH(u32LayerId)     gs_pstCapacity[u32LayerId].u32MinWidth
#define HIFB_MIN_HEIGHT(u32LayerId)    gs_pstCapacity[u32LayerId].u32MinHeight

#define IS_STEREO_SBS(par)  ((par->st3DInfo.StereoMode == HIFB_STEREO_SIDEBYSIDE_HALF))
#define IS_STEREO_TAB(par)  ((par->st3DInfo.StereoMode == HIFB_STEREO_TOPANDBOTTOM))
#define IS_STEREO_FPK(par)  ((par->st3DInfo.StereoMode == HIFB_STEREO_FRMPACKING))

#define IS_2BUF_MODE(par)  ((par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_DOUBLE || par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_DOUBLE_IMMEDIATE))
#define IS_1BUF_MODE(par)  ((par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_ONE))


#define FBNAME "HI_FB"

#define DRV_HIFB_IOCTLCMD_NUM_MAX            150
#define DRV_HIFB_IOCTLFUNC_ITEM_NUM_MAX      50

#define DRV_HIFB_CHECK_IOCTL_CMD(CmdNum)\
    if ((CmdNum < 1) || (CmdNum > DRV_HIFB_IOCTLCMD_NUM_MAX))\
    {\
        return HI_FAILURE;\
    }\

#define DRV_HIFB_CHECK_IOCTL_NUM(CmdFunc)\
        if ((CmdFunc < 1) || (CmdFunc > DRV_HIFB_IOCTLFUNC_ITEM_NUM_MAX))\
        {\
            return HI_FAILURE;\
        }\

typedef HI_S32(*DRV_HIFB_IoctlFunc)(struct fb_info *info, HI_ULONG arg);


/*************************** Structure Definition ***********************************************/
static char* video = HI_NULL;
module_param(video, charp, S_IRUGO);

static char* tc_wbc = "off";
module_param(tc_wbc, charp, S_IRUGO);


HIFB_DRV_OPS_S    g_stDrvAdpCallBackFunction;
HIFB_DRV_TDEOPS_S g_stGfx2dCallBackFunction;

/* to save layer id and layer size */
HIFB_LAYER_S s_stLayer[HIFB_MAX_LAYER_NUM];

const static HIFB_CAPABILITY_S *gs_pstCapacity = NULL;

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
HIFB_SCROLLTEXT_INFO_S s_stTextLayer[HIFB_LAYER_ID_BUTT];
#endif

typedef struct tagDrvHifbIoctlFunc
{
    HI_U32 Cmd;
    DRV_HIFB_IoctlFunc DrvHifbIoctlFunc;
}DRV_HIFB_IOCTLFUNC_ITEM;


/********************** Global Variable declaration *********************************************/
#define CONFIG_GFX_HIFB_DEFAULT_SIZE    ((HIFB_HD_DEF_STRIDE) * (HIFB_HD_DEF_HEIGHT))

static HI_U32 gs_u32MenuconfigLayerSize[HIFB_MAX_LAYER_NUM] =
{
    #ifdef CFG_HI_HD0_FB_VRAM_SIZE
        CFG_HI_HD0_FB_VRAM_SIZE,
    #else
        0,
    #endif
    #ifdef CFG_HI_HD1_FB_VRAM_SIZE
        CFG_HI_HD1_FB_VRAM_SIZE,
    #else
        0,
    #endif
    #ifdef CFG_HI_HD2_FB_VRAM_SIZE
        CFG_HI_HD2_FB_VRAM_SIZE,
    #else
        0,
    #endif
    #ifdef CFG_HI_HD3_FB_VRAM_SIZE
        CFG_HI_HD3_FB_VRAM_SIZE,
    #else
        0,
    #endif
        0,
        0,
};

static struct fb_fix_screeninfo gs_stDefFix =
{
    .id          = "hifb",
    .type        = FB_TYPE_PACKED_PIXELS,
    .visual      = FB_VISUAL_TRUECOLOR,
    .xpanstep    = 1,
    .ypanstep    = 1,
    .ywrapstep   = 0,
    .line_length = HIFB_HD_DEF_STRIDE,
    .accel       = FB_ACCEL_NONE,
    .mmio_len    = 0,
    .mmio_start  = 0,
};

static struct fb_var_screeninfo s_stDefVar[HIFB_LAYER_TYPE_BUTT] =
{
    {
        .xres           = HIFB_HD_DEF_WIDTH,
        .yres           = HIFB_HD_DEF_HEIGHT,
        .xres_virtual   = HIFB_HD_DEF_WIDTH,
        .yres_virtual   = HIFB_HD_DEF_HEIGHT,
        .xoffset        = 0,
        .yoffset        = 0,
        .bits_per_pixel = HIFB_DEF_DEPTH,
        .red            = {10, 5, 0},
        .green          = { 5, 5, 0},
        .blue           = { 0, 5, 0},
        .transp         = {15, 1, 0},
        .activate       = FB_ACTIVATE_NOW,
        .pixclock       = -1,
        .left_margin    = -1,
        .right_margin   = -1,
        .upper_margin   = -1,
        .lower_margin   = -1,
        .hsync_len      = -1,
        .vsync_len      = -1,
    },
    {
        .xres           = HIFB_SD_DEF_WIDTH,
        .yres           = HIFB_SD_DEF_HEIGHT,
        .xres_virtual   = HIFB_SD_DEF_WIDTH,
        .yres_virtual   = HIFB_SD_DEF_HEIGHT,
        .xoffset        = 0,
        .yoffset        = 0,
        .bits_per_pixel = HIFB_DEF_DEPTH,
        .red            = {10, 5, 0},
        .green          = { 5, 5, 0},
        .blue           = { 0, 5, 0},
        .transp         = {15, 1, 0},
        .activate       = FB_ACTIVATE_NOW,
        .pixclock       = -1,
        .left_margin    = -1,
        .right_margin   = -1,
        .upper_margin   = -1,
        .lower_margin   = -1,
        .hsync_len      = -1,
        .vsync_len      = -1,
    },
    {
        .xres           = HIFB_AD_DEF_WIDTH,
        .yres           = HIFB_AD_DEF_HEIGHT,
        .xres_virtual   = HIFB_AD_DEF_WIDTH,
        .yres_virtual   = HIFB_AD_DEF_HEIGHT,
        .xoffset        = 0,
        .yoffset        = 0,
        .bits_per_pixel = HIFB_DEF_DEPTH,
        .red            = {10, 5, 0},
        .green          = { 5, 5, 0},
        .blue           = { 0, 5, 0},
        .transp         = {15, 1, 0},
        .activate       = FB_ACTIVATE_NOW,
        .pixclock       = -1,
        .left_margin    = -1,
        .right_margin   = -1,
        .upper_margin   = -1,
        .lower_margin   = -1,
        .hsync_len      = -1,
        .vsync_len      = -1,
    },
    {
        .xres           = HIFB_CURSOR_DEF_WIDTH,
        .yres           = HIFB_CURSOR_DEF_HEIGHT,
        .xres_virtual   = HIFB_CURSOR_DEF_WIDTH,
        .yres_virtual   = HIFB_CURSOR_DEF_HEIGHT,
        .xoffset        = 0,
        .yoffset        = 0,
        .bits_per_pixel = HIFB_DEF_DEPTH,
        .red            = {10, 5, 0},
        .green          = { 5, 5, 0},
        .blue           = { 0, 5, 0},
        .transp         = {15, 1, 0},
        .activate       = FB_ACTIVATE_NOW,
        .pixclock       = -1,
        .left_margin    = -1,
        .right_margin   = -1,
        .upper_margin   = -1,
        .lower_margin   = -1,
        .hsync_len      = -1,
        .vsync_len      = -1,
    }
};

/** bit filed info of color fmt, the order must be the same as HIFB_COLOR_FMT_E **/
HIFB_ARGB_BITINFO_S s_stArgbBitField[HIFB_MAX_PIXFMT_NUM] =
{   /*RGB565*/
    {
        .stRed    = {11, 5, 0},
        .stGreen  = {5, 6, 0},
        .stBlue   = {0, 5, 0},
        .stTransp = {0, 0, 0},
    },
    /*RGB888*/
    {
        .stRed    = {16, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {0, 8, 0},
        .stTransp = {0, 0, 0},
    },
    /*KRGB444*/
    {
        .stRed    = {8, 4, 0},
        .stGreen  = {4, 4, 0},
        .stBlue   = {0, 4, 0},
        .stTransp = {0, 0, 0},
    },
    /*KRGB555*/
    {
        .stRed    = {10, 5, 0},
        .stGreen  = {5, 5, 0},
        .stBlue   = {0, 5, 0},
        .stTransp = {0, 0, 0},
    },
    /*KRGB888*/
    {
        .stRed    = {16,8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {0, 8, 0},
        .stTransp = {0, 0, 0},
    },
    /*ARGB4444*/
    {
        .stRed    = {8, 4, 0},
        .stGreen  = {4, 4, 0},
        .stBlue   = {0, 4, 0},
        .stTransp = {12, 4, 0},
    },
    /*ARGB1555*/
    {
        .stRed    = {10, 5, 0},
        .stGreen  = {5, 5, 0},
        .stBlue   = {0, 5, 0},
        .stTransp = {15, 1, 0},
    },
    /*ARGB8888*/
    {
        .stRed    = {16, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {0, 8, 0},
        .stTransp = {24, 8, 0},
    },
    /*ARGB8565*/
    {
        .stRed    = {11, 5, 0},
        .stGreen  = {5, 6, 0},
        .stBlue   = {0, 5, 0},
        .stTransp = {16, 8, 0},
    },
    /*RGBA4444*/
    {
        .stRed    = {12, 4, 0},
        .stGreen  = {8, 4, 0},
        .stBlue   = {4, 4, 0},
        .stTransp = {0, 4, 0},
    },
    /*RGBA5551*/
    {
        .stRed    = {11, 5, 0},
        .stGreen  = {6, 5, 0},
        .stBlue   = {1, 5, 0},
        .stTransp = {0, 1, 0},
    },
    /*RGBA5658*/
    {
        .stRed    = {19, 5, 0},
        .stGreen  = {13, 6, 0},
        .stBlue   = {8, 5, 0},
        .stTransp = {0, 8, 0},
    },
    /*RGBA8888*/
    {
        .stRed    = {24, 8, 0},
        .stGreen  = {16, 8, 0},
        .stBlue   = {8, 8, 0},
        .stTransp = {0, 8, 0},
    },
    /*BGR565*/
    {
        .stRed    = {0, 5, 0},
        .stGreen  = {5, 6, 0},
        .stBlue   = {11, 5, 0},
        .stTransp = {0, 0, 0},
    },
    /*BGR888*/
    {
        .stRed    = {0, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {16, 8, 0},
        .stTransp = {0, 0, 0},
    },
    /*ABGR4444*/
    {
        .stRed    = {0, 4, 0},
        .stGreen  = {4, 4, 0},
        .stBlue   = {8, 4, 0},
        .stTransp = {12, 4, 0},
    },
    /*ABGR1555*/
    {
        .stRed    = {0, 5, 0},
        .stGreen  = {5, 5, 0},
        .stBlue   = {10, 5, 0},
        .stTransp = {15, 1, 0},
    },
    /*ABGR8888*/
    {
        .stRed    = {0, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {16, 8, 0},
        .stTransp = {24, 8, 0},
    },
    /*ABGR8565*/
    {
        .stRed    = {0, 5, 0},
        .stGreen  = {5, 6, 0},
        .stBlue   = {11, 5, 0},
        .stTransp = {16, 8, 0},
    },
    /*KBGR444 16bpp*/
    {
        .stRed    = {0, 4, 0},
        .stGreen  = {4, 4, 0},
        .stBlue   = {8, 4, 0},
        .stTransp = {0, 0, 0},
    },
    /*KBGR555 16bpp*/
    {
        .stRed    = {0, 5, 0},
        .stGreen  = {5, 5, 0},
        .stBlue   = {10, 5, 0},
        .stTransp = {0, 0, 0},
    },
    /*KBGR888 32bpp*/
    {
        .stRed    = {0, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {16, 8, 0},
        .stTransp = {0, 0, 0},
    },

    /*1bpp*/
    {
        .stRed    = {0, 1, 0},
        .stGreen  = {0, 1, 0},
        .stBlue   = {0, 1, 0},
        .stTransp = {0, 0, 0},
    },
    /*2bpp*/
    {
        .stRed    = {0, 2, 0},
        .stGreen  = {0, 2, 0},
        .stBlue   = {0, 2, 0},
        .stTransp = {0, 0, 0},
    },
    /*4bpp*/
    {
        .stRed    = {0, 4, 0},
        .stGreen  = {0, 4, 0},
        .stBlue   = {0, 4, 0},
        .stTransp = {0, 0, 0},
    },
    /*8bpp*/
    {
        .stRed    = {0, 8, 0},
        .stGreen  = {0, 8, 0},
        .stBlue   = {0, 8, 0},
        .stTransp = {0, 0, 0},
    },
    /*ACLUT44*/
    {
        .stRed    = {4, 4, 0},
        .stGreen  = {4, 4, 0},
        .stBlue   = {4, 4, 0},
        .stTransp = {0, 4, 0},
    },
    /*ACLUT88*/
    {
        .stRed    = {8, 8, 0},
        .stGreen  = {8, 8, 0},
        .stBlue   = {8, 8, 0},
        .stTransp = {0, 8, 0},
    }
};

static HI_S32 DRV_HIFB_Open    (struct fb_info *info, HI_S32 user);
static HI_S32 DRV_HIFB_Close   (struct fb_info *info, HI_S32 user);
static HI_S32 hifb_check_var   (struct fb_var_screeninfo *var, struct fb_info *info);
static HI_S32 hifb_set_par     (struct fb_info *info);
static HI_S32 hifb_ioctl       (struct fb_info *info, HI_U32 cmd, unsigned long arg);
static HI_S32 hifb_setcmap     (struct fb_cmap *cmap, struct fb_info *info);
#ifdef CONFIG_DMA_SHARED_BUFFER
static struct dma_buf* hifb_dmabuf_export (struct fb_info *info);
#endif
#ifdef CONFIG_GFX_MMU_SUPPORT
static HI_S32 hifb_map_mem_kernel_to_user (struct fb_info *info, struct vm_area_struct *vma);
#endif
static HI_S32 hifb_setcolreg(unsigned regno, unsigned red, unsigned green,unsigned blue, unsigned transp, struct fb_info *info);
#ifdef CFG_HIFB_SUPPORT_CONSOLE
static HI_VOID hifb_fillrect   (struct fb_info *p, const struct fb_fillrect *rect);
static HI_VOID hifb_copyarea   (struct fb_info *p, const struct fb_copyarea *area);
static HI_VOID hifb_imageblit  (struct fb_info *p, const struct fb_image *image);
#endif

extern HI_S32 DRV_HIFB_PanDisplay(struct fb_var_screeninfo *var, struct fb_info *info);

#ifdef CFG_HIFB_FENCE_SUPPORT
extern HI_S32 DRV_HIFB_FenceRefresh(HIFB_PAR_S* pstPar, HI_VOID *pArgs);
#else
extern HI_S32 DRV_HIFB_NoFenceRefresh(HIFB_PAR_S* pstPar, HI_VOID *pArgs);
#endif

#ifdef CONFIG_COMPAT
static HI_S32 hifb_compat_ioctl (struct fb_info *info, HI_U32 cmd, unsigned long arg);
#endif


static struct fb_ops s_sthifbops =
{
    .owner          = THIS_MODULE,
    .fb_open        = DRV_HIFB_Open,
    .fb_release     = DRV_HIFB_Close,
    .fb_check_var   = hifb_check_var,
    .fb_set_par     = hifb_set_par,
    .fb_pan_display = DRV_HIFB_PanDisplay,
#ifdef CONFIG_COMPAT
    .fb_compat_ioctl= hifb_compat_ioctl,
#endif
    .fb_ioctl       = hifb_ioctl,
    .fb_setcolreg   = hifb_setcolreg,
    .fb_setcmap     = hifb_setcmap,
#ifdef CFG_HIFB_SUPPORT_CONSOLE
    .fb_fillrect    = hifb_fillrect,
    .fb_copyarea    = hifb_copyarea,
    .fb_imageblit   = hifb_imageblit,
#endif
#ifdef CONFIG_DMA_SHARED_BUFFER
    .fb_dmabuf_export = hifb_dmabuf_export,
#endif
#ifdef CONFIG_GFX_MMU_SUPPORT
    .fb_mmap          = hifb_map_mem_kernel_to_user
#endif
};

static HI_S32 HIFB_OSR_GetColorKey         (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetColorKey         (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetLayerAlpha       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetLayerAlpha       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetScreenOriginPos  (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetScreenOriginPos  (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetDeFlicker        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetDeFlicker        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetVblank           (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ShowLayer           (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetLayerShowState   (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetCapablity        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetDecompress       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetLayerInfo        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetLayerInfo        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetCanvasBuffer     (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_RefreshLayer        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_WaiteRefreshFinish  (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetSteroFraming     (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetSteroFraming     (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetSteroMode        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetSteroMode        (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetScreenSize       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetScreenSize       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetCompress         (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetCompress         (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ScrolltextCreate    (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ScrolltextFill      (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ScrolltextPause     (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ScrolltextResume    (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ScrolltextDestory   (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetSteroDepth       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetSteroDepth       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetLayerZorder      (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetLayerZorder      (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_ReleaseLogo         (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_SetCompressionMode  (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetCompressionMode  (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_FenceRefresh          (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_GetSmemStartPhy     (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_FixScreenInfo       (struct fb_info *info, HI_ULONG arg);
static HI_S32 HIFB_OSR_HwcGetLayerInfo     (struct fb_info *info, HI_ULONG arg);


static HI_S32 gs_DrvHifbCtlNum[DRV_HIFB_IOCTLCMD_NUM_MAX] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,/** index = 89 **/
     1,  2,  3,  4,  5,  6,  0,  0,  7,  8, 9,
     11, 12, 13, 15,/** index = 104 **/
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,/** index = 119 **/
     17, 18, 0,  19, 21, 22, 23, 24, 25, 26, /** index = 129 **/
     27, 28, 29, 30, 31, 32, 33, 34, 35, 37, /** index = 139 **/
     38, 39, 40, 41, 43, 44, 45, 47, 48, 49
   };

static DRV_HIFB_IOCTLFUNC_ITEM gs_DrvHifbCtlFunc[DRV_HIFB_IOCTLFUNC_ITEM_NUM_MAX] = {{0,NULL},
   {FBIOGET_COLORKEY_HIFB,      HIFB_OSR_GetColorKey},            {FBIOPUT_COLORKEY_HIFB,      HIFB_OSR_SetColorKey},
   {FBIOGET_ALPHA_HIFB,         HIFB_OSR_GetLayerAlpha},          {FBIOPUT_ALPHA_HIFB,         HIFB_OSR_SetLayerAlpha},
   {FBIOGET_SCREEN_ORIGIN_HIFB, HIFB_OSR_GetScreenOriginPos},     {FBIOPUT_SCREEN_ORIGIN_HIFB, HIFB_OSR_SetScreenOriginPos},
   {FBIOGET_DEFLICKER_HIFB,     HIFB_OSR_GetDeFlicker},           {FBIOPUT_DEFLICKER_HIFB,     HIFB_OSR_SetDeFlicker},
   {FBIOGET_VBLANK_HIFB,        HIFB_OSR_GetVblank},              {0, NULL},/** index = 10**/
   {FBIOPUT_SHOW_HIFB,          HIFB_OSR_ShowLayer},              {FBIOGET_SHOW_HIFB,          HIFB_OSR_GetLayerShowState},
   {FBIOGET_CAPABILITY_HIFB,    HIFB_OSR_GetCapablity},           {0, NULL},
   {FBIOPUT_DECOMPRESS_HIFB,    HIFB_OSR_SetDecompress},          {0, NULL},
   {FBIOPUT_LAYER_INFO,         HIFB_OSR_SetLayerInfo},           {FBIOGET_LAYER_INFO,         HIFB_OSR_GetLayerInfo},
   {FBIOGET_CANVAS_BUFFER,      HIFB_OSR_GetCanvasBuffer},        {0, NULL},/** index = 20**/
   {FBIO_REFRESH,               HIFB_OSR_RefreshLayer},           {FBIO_WAITFOR_FREFRESH_DONE, HIFB_OSR_WaiteRefreshFinish},
   {FBIOPUT_ENCODER_PICTURE_FRAMING, HIFB_OSR_SetSteroFraming},   {FBIOGET_ENCODER_PICTURE_FRAMING,  HIFB_OSR_GetSteroFraming},
   {FBIOPUT_STEREO_MODE,        HIFB_OSR_SetSteroMode},           {FBIOGET_STEREO_MODE,        HIFB_OSR_GetSteroMode},
   {FBIOPUT_SCREENSIZE,         HIFB_OSR_SetScreenSize},          {FBIOGET_SCREENSIZE,         HIFB_OSR_GetScreenSize},
   {FBIOPUT_COMPRESSION,        HIFB_OSR_SetCompress},            {FBIOGET_COMPRESSION,        HIFB_OSR_GetCompress},/** index = 30**/
   {FBIO_SCROLLTEXT_CREATE,     HIFB_OSR_ScrolltextCreate},       {FBIO_SCROLLTEXT_FILL,       HIFB_OSR_ScrolltextFill},
   {FBIO_SCROLLTEXT_PAUSE,      HIFB_OSR_ScrolltextPause},        {FBIO_SCROLLTEXT_RESUME,     HIFB_OSR_ScrolltextResume},
   {FBIO_SCROLLTEXT_DESTORY,    HIFB_OSR_ScrolltextDestory},      {0, NULL},
   {FBIOPUT_STEREO_DEPTH,       HIFB_OSR_SetSteroDepth},          {FBIOGET_STEREO_DEPTH,       HIFB_OSR_GetSteroDepth},
   {FBIOPUT_ZORDER,             HIFB_OSR_SetLayerZorder},         {FBIOGET_ZORDER,             HIFB_OSR_GetLayerZorder},/** index = 40**/
   {FBIO_FREE_LOGO,             HIFB_OSR_ReleaseLogo},            {0,NULL},
   {FBIOPUT_COMPRESSIONMODE,    HIFB_OSR_SetCompressionMode},     {FBIOGET_COMPRESSIONMODE,    HIFB_OSR_GetCompressionMode},
   {FBIO_HWC_REFRESH,           HIFB_OSR_FenceRefresh},           {0,NULL},
   {FBIOGET_SMEMSTART_PHY,      HIFB_OSR_GetSmemStartPhy},        {FBIO_HWC_GETLAYERINFO,      HIFB_OSR_HwcGetLayerInfo},
   {FBIOGET_FSCREENINFO_HIFB,   HIFB_OSR_FixScreenInfo}};

/******************************* API declaration ************************************************/
static HI_S32  hifb_refresh(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf, HIFB_LAYER_BUF_E enBufMode);
static HI_VOID DRV_HIFB_SelectAntiflickerMode(HIFB_PAR_S *pstPar);
static HI_S32  hifb_refreshall(struct fb_info *info);
static HI_VOID hifb_assign_dispbuf(HI_U32 u32LayerId);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
static HI_S32  DRV_OSR_StereoCallBack   (HI_VOID * pParaml,HI_VOID * pParamr);
#endif

#ifdef CONFIG_DMA_SHARED_BUFFER
extern struct dma_buf *hifb_memblock_export(phys_addr_t base, size_t size, int flags);
#endif

static HI_S32 DRV_HIFB_ParseInsmodParameter(HI_VOID);
static inline unsigned long DRV_HIFB_GetVramSize(HI_CHAR* pstr);
static inline HI_S32  DRV_HIFB_RegisterFrameBuffer   (HI_U32 u32LayerId);
static inline HI_VOID DRV_HIFB_UnRegisterFrameBuffer (HI_U32 u32LayerId);
static inline HI_S32 DRV_HIFB_ReAllocLayerBuffer     (HI_U32 u32LayerId, HI_U32 BufSize);
static inline HI_S32 DRV_HIFB_AllocLayerBuffer       (HI_U32 u32LayerId, HI_U32 BufSize);
static inline HI_VOID DRV_HIFB_FreeLayerBuffer       (HI_U32 u32LayerId);
static inline HI_S32  DRV_HIFB_InitAllocCmapBuffer   (HI_U32 u32LayerId);
static inline HI_VOID DRV_HIFB_DInitAllocCmapBuffer  (HI_U32 u32LayerId);
static inline HI_BOOL DRV_HIFB_CheckSmmuSupport      (HI_U32 LayerId);
static inline HI_VOID DRV_HIFB_PrintVersion(HI_BOOL bLoad);


static HI_S32  DRV_HIFB_InitLayerInfo      (HI_U32 u32LayerID);
static HI_S32  DRV_HIFB_GetLayerBufferInfo (HI_U32 u32LayerID);
static HI_VOID DRV_HIFB_SetDisplayBuffer   (HI_U32 u32LayerId);
static inline  HI_S32 DRV_HIFB_RegisterCallBackFunction (HI_U32 u32LayerId);
static inline  HI_VOID DRV_HIFB_ReleaseScrollText (struct fb_info *info);

#ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
static inline HI_VOID DRV_HIFB_UpLowPowerInfo(HI_U32 LayerId);
#endif

static inline HI_VOID HIFB_OSR_UpdataRefreshInfo(HI_U32 LayerId);
static inline HI_VOID HIFB_OSR_UpdataInputDataFmt    (HI_U32 LayerId);
static inline HI_VOID HIFB_OSR_UpdataInputDataStride (HI_U32 LayerId);
static inline HI_VOID HIFB_OSR_UpdataInputDataDDR    (HI_U32 LayerId);
static inline HI_VOID HIFB_OSR_SwitchDispBuffer      (HI_U32 LayerId);

static inline HI_S32  HIFB_OSR_CheckWhetherResolutionSupport(HI_U32 LayerId, HI_U32 Width, HI_U32 Height);
static inline HI_VOID HIFB_OSR_SetDispInfo(HI_U32 LayerId);
static inline HI_S32  HIFB_OSR_CheckWhetherLayerSizeSupport(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo);
static inline HI_S32  HIFB_OSR_CheckWhetherLayerPosSupport(HIFB_LAYER_INFO_S *pstLayerInfo);
static inline HI_VOID HIFB_OSR_CheckWhetherDispSizeChange(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo);
static inline HI_S32  HIFB_OSR_CheckWhetherMemSizeEnough(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo);

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
static inline HI_S32 HIFB_OSR_SCROLLTEXT_Enable(HI_BOOL bEnable, HI_ULONG arg);
#endif

/******************************* API realization ************************************************/
/***************************************************************************************
* func        : hifb_getfmtbyargb
* description : CNcomment: 从argb中判断像素格式 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HIFB_COLOR_FMT_E hifb_getfmtbyargb(struct fb_bitfield *red,struct fb_bitfield *green,struct fb_bitfield *blue,struct fb_bitfield *transp,HI_U32 u32ColorDepth)
{
    HI_U32 i = 0;
    HI_U32 u32Bpp = 0;

    for (i = 0; i < sizeof(s_stArgbBitField)/sizeof(HIFB_ARGB_BITINFO_S); i++)
    {
        if (   (hifb_bitfieldcmp(*red, s_stArgbBitField[i].stRed)       == 0)
            && (hifb_bitfieldcmp(*green, s_stArgbBitField[i].stGreen)   == 0)
            && (hifb_bitfieldcmp(*blue, s_stArgbBitField[i].stBlue)     == 0)
            && (hifb_bitfieldcmp(*transp, s_stArgbBitField[i].stTransp) == 0))
        {
            u32Bpp = DRV_HIFB_GetBppByFmt(i);
            if (u32Bpp == u32ColorDepth)
            {
                return i;
            }
        }
    }

    switch(u32ColorDepth)
    {
        case 1:
            i = HIFB_FMT_1BPP;
            break;
        case 2:
            i = HIFB_FMT_2BPP;
            break;
        case 4:
            i = HIFB_FMT_4BPP;
            break;
        case 8:
            i = HIFB_FMT_8BPP;
            break;
        case 16:
            i = HIFB_FMT_RGB565;
            break;
        case 24:
            i = HIFB_FMT_RGB888;
            break;
        case 32:
            i = HIFB_FMT_ARGB8888;
            break;
        default:
            i = HIFB_FMT_BUTT;
            break;
    }

    if(HIFB_FMT_BUTT != i)
    {
        *red    = s_stArgbBitField[i].stRed;
        *green  = s_stArgbBitField[i].stGreen;
        *blue   = s_stArgbBitField[i].stBlue;
        *transp = s_stArgbBitField[i].stTransp;
    }

    return i;
}

/***************************************************************************************
* func          : HIFB_ReAllocWork
* description   : CNcomment: 重新分配内存，旧内存释放处理,放这里的原因是为了
                             保证这快内存不再被逻辑使用的时候才释放，这样就不会发生访问页表错误
                             CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID HIFB_ReAllocWork(struct work_struct *work)
{
    HIFB_DISP_TMPBUF_S *pstDispTmpBuf = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(work);
    pstDispTmpBuf = (HIFB_DISP_TMPBUF_S *)container_of(work, HIFB_DISP_TMPBUF_S, bDisBufWork);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstDispTmpBuf);

    if (NULL != pstDispTmpBuf->pVirBuf)
    {
        hifb_buf_ummap(pstDispTmpBuf->pVirBuf);
    }

    if (0 != pstDispTmpBuf->u32SmemStartPhy)
    {
        hifb_buf_unmapsmmu(pstDispTmpBuf->u32PhyBuf);
        hifb_buf_freemem(pstDispTmpBuf->u32SmemStartPhy,HI_FALSE);
    }
    else
    {
        hifb_buf_freemem(pstDispTmpBuf->u32PhyBuf,HI_TRUE);
    }

    pstDispTmpBuf->pVirBuf         = NULL;
    pstDispTmpBuf->u32PhyBuf       = 0;
    pstDispTmpBuf->u32SmemStartPhy = 0;

    return;
}


/***************************************************************************************
* func          : hifb_checkmem_enough
* description   : CNcomment: 判断内存是否足够 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 hifb_checkmem_enough(struct fb_info *info,HI_U32 u32Stride,HI_U32 u32Height)
{
    HI_U32 u32BufferNum = 0;
    HI_U32 u32BufSize   = 0;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    switch (par->stExtendInfo.enBufMode)
    {
        case HIFB_LAYER_BUF_DOUBLE:
        case HIFB_LAYER_BUF_DOUBLE_IMMEDIATE:
            u32BufferNum = 2;
            break;
        case HIFB_LAYER_BUF_ONE:
        case HIFB_REFRESH_MODE_WITH_PANDISPLAY:
            u32BufferNum = 1;
            break;
        default:
            u32BufferNum = 0;
            break;
    }

    u32BufSize = HI_HIFB_GetMemSize(u32Stride,u32Height);
    if (0 != u32BufferNum)
    {
       HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(u32BufferNum,u32BufSize,HI_FAILURE);
    }
    u32BufSize = u32BufferNum * u32BufSize;

    if (info->fix.smem_len >= u32BufSize)
    {
        return HI_SUCCESS;
    }

    HIFB_ERROR("memory is not enough!  now is %d u32Pitch %d u32Height %d expect %d\n",
               info->fix.smem_len,
               u32Stride,
               u32Height,
               u32BufSize);
    return HI_FAILURE;
}

/***************************************************************************************
* func        : hifb_check_fmt
* description : CNcomment: 判断像素格式是否合法 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 hifb_check_fmt(struct fb_var_screeninfo *var, struct fb_info *info)
{
    HI_U32 u32MaxXRes = 0;
    HI_U32 u32MaxYRes = 0;
    HIFB_PAR_S *par    = NULL;
    HI_U32 u32LayerID  = 0;
    HIFB_COLOR_FMT_E enFmt = HIFB_FMT_BUTT;

    HIFB_CHECK_NULLPOINTER_RETURN(var,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);
    u32LayerID = par->stBaseInfo.u32LayerID;

    enFmt = hifb_getfmtbyargb(&var->red,&var->green,&var->blue,&var->transp,var->bits_per_pixel);
    if (enFmt == HIFB_FMT_BUTT)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return -EINVAL;
    }

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(par->stBaseInfo.u32LayerID,-EINVAL);

    if (  (!gs_pstCapacity[par->stBaseInfo.u32LayerID].bColFmt[enFmt])
        ||(!g_stGfx2dCallBackFunction.HIFB_DRV_TdeSupportFmt(enFmt) && par->stExtendInfo.enBufMode != HIFB_REFRESH_MODE_WITH_PANDISPLAY))
    {
        HIFB_ERROR("Unsupported PIXEL FORMAT!\n");
        return -EINVAL;
    }

    if (var->xres_virtual < HIFB_MIN_WIDTH(u32LayerID))
    {
        var->xres_virtual = HIFB_MIN_WIDTH(u32LayerID);
    }
    if (var->yres_virtual < HIFB_MIN_HEIGHT(u32LayerID))
    {
        var->yres_virtual = HIFB_MIN_HEIGHT(u32LayerID);
    }

    u32MaxXRes = var->xres_virtual;
    if (var->xres > u32MaxXRes)
    {
        var->xres = u32MaxXRes;
    }
    else if (var->xres < HIFB_MIN_WIDTH(u32LayerID))
    {
        var->xres = HIFB_MIN_WIDTH(u32LayerID);
    }

    u32MaxYRes = var->yres_virtual;
    if (var->yres > u32MaxYRes)
    {
        var->yres = u32MaxYRes;
    }
    else if (var->yres < HIFB_MIN_HEIGHT(u32LayerID))
    {
        var->yres = HIFB_MIN_HEIGHT(u32LayerID);
    }

    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(var->xres, var->xoffset, HI_FAILURE);
    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(var->yres, var->yoffset, HI_FAILURE);
    if (   (var->xoffset > var->xres_virtual)
        || (var->yoffset > var->yres_virtual)
        || (var->xoffset + var->xres > var->xres_virtual)
        || (var->yoffset + var->yres > var->yres_virtual))
    {
        HIFB_ERROR("offset is invalid! xoffset:%d, yoffset:%d\n", var->xoffset, var->yoffset);
        return -EINVAL;
    }

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : hifb_check_var
* description  : CNcomment: 判断参数是否合法 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
    return hifb_check_fmt(var, info);
}


/***************************************************************************************
* func        : hifb_assign_dispbuf
* description : CNcomment: 分配display buffer CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_VOID hifb_assign_dispbuf(HI_U32 u32LayerId)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_U32 u32BufSize  = 0;
    HI_S32 Ret = HI_SUCCESS;

    HIFB_CHECK_ARRAY_OVER_UNRETURN(u32LayerId, HIFB_MAX_LAYER_NUM);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if (pstPar->st3DInfo.IsStereo)
    {
        HI_U32 CmpStride = 0;
        HI_U32 Stride = 0;
        HI_U32 u32StartAddr = 0;

        Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT | HIFB_PARA_CHECK_STRIDE,
                                      info->var.xres, info->var.yres, 0, 0, info->var.bits_per_pixel);
        if (HI_SUCCESS != Ret)
        {
            HIFB_ERROR("Failure\n");
            return;
        }

        Stride = CONIFG_HIFB_GetMaxStride(info->var.xres,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
        HIFB_CHECK_EQUAL_UNRETURN(Stride, 0);

        u32BufSize = HI_HIFB_GetMemSize(Stride,info->var.yres);
        HIFB_CHECK_EQUAL_UNRETURN(u32BufSize, 0);

        if (IS_2BUF_MODE(pstPar) || IS_1BUF_MODE(pstPar))
        {
            u32StartAddr = info->fix.smem_start;
            if (1 == pstPar->stRunInfo.StereoBufNum)
            {
                pstPar->st3DInfo.u32DisplayAddr[0] = u32StartAddr;
                pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr;
            }
            else if (2 == pstPar->stRunInfo.StereoBufNum)
            {
                pstPar->st3DInfo.u32DisplayAddr[0] = u32StartAddr;
                if (u32BufSize > (info->fix.smem_len / 2))
                {
                    pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr;
                }
                else
                {
                    pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr + u32BufSize;
                }
            }
            return;
        }
        else if (  (0 == pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart)
                || (0 == pstPar->st3DInfo.st3DMemInfo.u32StereoMemLen)
                || (0 == pstPar->stRunInfo.StereoBufNum))
        {
            return;
        }
        else
        {/**<-- android used pandisplay refresh **/
            u32StartAddr = pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart;
        }

        if (1 == pstPar->stRunInfo.StereoBufNum)
        {
            pstPar->st3DInfo.u32DisplayAddr[0] = u32StartAddr;
            pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr;
        }
        else if (2 == pstPar->stRunInfo.StereoBufNum)
        {/**<-- generally is two buffer **/
            pstPar->st3DInfo.u32DisplayAddr[0] = u32StartAddr;
            if (HIFB_STEREO_SIDEBYSIDE_HALF == pstPar->st3DInfo.StereoMode)
            {
                pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr + pstPar->st3DInfo.st3DSurface.u32Pitch / 2;
            }
            else if (HIFB_STEREO_TOPANDBOTTOM == pstPar->st3DInfo.StereoMode)
            {
                pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr + pstPar->st3DInfo.st3DSurface.u32Pitch * pstPar->stExtendInfo.u32DisplayHeight / 2;
            }
            else
            {/**<-- frame packing user display buffer, no user 3d buffer **/
                pstPar->st3DInfo.u32DisplayAddr[1] = u32StartAddr + u32BufSize;
            }
        }
    }
    else
#endif
    {
        DRV_HIFB_SetDisplayBuffer(u32LayerId);
    }

    return;
}


/***************************************************************************************
* func         : hifb_getupdate_rect
* description  : CNcomment: 获取图层的更新区域 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_getupdate_rect(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf, HIFB_RECT *pstUpdateRect)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *pstPar;
    struct fb_info *info = NULL;
    TDE2_RECT_S SrcRect   = {0};
    TDE2_RECT_S DstRect   = {0};
    TDE2_RECT_S InSrcRect = {0};
    TDE2_RECT_S InDstRect = {0};

    HIFB_CHECK_ARRAY_OVER_RETURN(u32LayerId, HIFB_MAX_LAYER_NUM,HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar,HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstUpdateRect,HI_FAILURE);

    SrcRect.u32Width  = pstCanvasBuf->stCanvas.u32Width;
    SrcRect.u32Height = pstCanvasBuf->stCanvas.u32Height;

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  pstPar->stExtendInfo.u32DisplayWidth, pstPar->stExtendInfo.u32DisplayHeight, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    if (pstPar->st3DInfo.StereoMode == HIFB_STEREO_SIDEBYSIDE_HALF)
    {
        DstRect.u32Width  = pstPar->stExtendInfo.u32DisplayWidth >> 1;
        DstRect.u32Height = pstPar->stExtendInfo.u32DisplayHeight;
    }
    else if (pstPar->st3DInfo.StereoMode == HIFB_STEREO_TOPANDBOTTOM)
    {
        DstRect.u32Width  = pstPar->stExtendInfo.u32DisplayWidth;
        DstRect.u32Height = pstPar->stExtendInfo.u32DisplayHeight >> 1;
    }
    else
    {
        DstRect.u32Width  = pstPar->stExtendInfo.u32DisplayWidth;
        DstRect.u32Height = pstPar->stExtendInfo.u32DisplayHeight;
    }

    if (SrcRect.u32Width != DstRect.u32Width || SrcRect.u32Height != DstRect.u32Height)
    {
        InSrcRect.s32Xpos   = pstCanvasBuf->UpdateRect.x;
        InSrcRect.s32Ypos   = pstCanvasBuf->UpdateRect.y;
        InSrcRect.u32Width  = pstCanvasBuf->UpdateRect.w;
        InSrcRect.u32Height = pstCanvasBuf->UpdateRect.h;

        g_stGfx2dCallBackFunction.HIFB_DRV_CalScaleRect(&SrcRect, &DstRect, &InSrcRect, &InDstRect);

        pstUpdateRect->x = InDstRect.s32Xpos;
        pstUpdateRect->y = InDstRect.s32Ypos;
        pstUpdateRect->w = InDstRect.u32Width;
        pstUpdateRect->h = InDstRect.u32Height;
    }
    else
    {
        HI_GFX_Memcpy(pstUpdateRect, &pstCanvasBuf->UpdateRect, sizeof(HIFB_RECT));
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : hifb_backup_forebuf
* description  : CNcomment: 更新前景数据CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_backup_forebuf(HI_U32 u32LayerId, HIFB_BUFFER_S *pstBackBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 ForePhyAddr = 0;
    HIFB_PAR_S *pstPar = NULL;
    HIFB_RECT  *pstForeUpdateRect = NULL;
    struct fb_info *info = NULL;
    HIFB_BUFFER_S stForeBuf;
    HIFB_BUFFER_S stBackBuf;
    HIFB_BLIT_OPT_S stBlitTmp;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstBackBuf, HI_FAILURE);
    HI_GFX_Memcpy(&stBackBuf, pstBackBuf, sizeof(HIFB_BUFFER_S));

    HIFB_CHECK_ARRAY_OVER_RETURN((1 - pstPar->stRunInfo.u32IndexForInt), CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    if ((pstPar->st3DInfo.StereoMode != HIFB_STEREO_MONO) && (pstPar->st3DInfo.StereoMode != HIFB_STEREO_BUTT))
    {
        pstForeUpdateRect = &pstPar->st3DInfo.st3DUpdateRect;
        ForePhyAddr = pstPar->st3DInfo.u32DisplayAddr[1 - pstPar->stRunInfo.u32IndexForInt];
    }
    else
    {
        pstForeUpdateRect = &pstPar->stDispInfo.stUpdateRect;
        ForePhyAddr = pstPar->stDispInfo.u32DisplayAddr[1 - pstPar->stRunInfo.u32IndexForInt];
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  stBackBuf.stCanvas.u32Width, stBackBuf.stCanvas.u32Height, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    if (pstPar->st3DInfo.StereoMode == HIFB_STEREO_SIDEBYSIDE_HALF)
    {
        stBackBuf.stCanvas.u32Width  = stBackBuf.stCanvas.u32Width >> 1;
    }
    else if (pstPar->st3DInfo.StereoMode == HIFB_STEREO_TOPANDBOTTOM)
    {
        stBackBuf.stCanvas.u32Height = stBackBuf.stCanvas.u32Height >> 1;
    }

    if (0 == pstForeUpdateRect->w)
    {
        pstForeUpdateRect->w = stBackBuf.stCanvas.u32Width;
    }

    if (0 == pstForeUpdateRect->h)
    {
        pstForeUpdateRect->h = stBackBuf.stCanvas.u32Height;
    }

    if (HI_TRUE == hifb_iscontain(&stBackBuf.UpdateRect, pstForeUpdateRect))
    {
        return HI_SUCCESS;
    }

    HI_GFX_Memcpy(&stForeBuf, &stBackBuf, sizeof(stBackBuf));
    stForeBuf.stCanvas.u32PhyAddr = ForePhyAddr;

    HI_GFX_Memcpy(&stForeBuf.UpdateRect, pstForeUpdateRect, sizeof(HIFB_RECT));
    HI_GFX_Memcpy(&stBackBuf.UpdateRect, &stForeBuf.UpdateRect , sizeof(HIFB_RECT));

    HI_GFX_Memset(&stBlitTmp, 0x0, sizeof(stBlitTmp));

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(&stForeBuf, &stBackBuf, &stBlitTmp, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("HIFB_DRV_Blit failure\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : hifb_disp_setdispsize
* description  : CNcomment: set display size CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_disp_setdispsize(HI_U32 u32LayerId, HI_U32 u32Width, HI_U32 u32Height)
{
    HI_S32 Ret = HI_SUCCESS;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride = 0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    if ((pstPar->stExtendInfo.u32DisplayWidth == u32Width) && (pstPar->stExtendInfo.u32DisplayHeight == u32Height))
    {
        return HI_SUCCESS;
    }

    if ((u32Width > CONFIG_HIFB_HD_LAYER_MAXWIDTH) || (u32Height > CONFIG_HIFB_HD_LAYER_MAXHEIGHT))
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_BITSPERPIXEL,0,0,0, 0,info->var.bits_per_pixel);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    u32Stride = CONIFG_HIFB_GetMaxStride(u32Width,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    HIFB_CHECK_EQUAL_RETURN(u32Stride, 0, HI_FAILURE);

    if (HI_FAILURE == hifb_checkmem_enough(info, u32Stride, u32Height))
    {
       HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
       return HI_FAILURE;
    }

    pstPar->stExtendInfo.u32DisplayWidth  = u32Width;
    pstPar->stExtendInfo.u32DisplayHeight = u32Height;

    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;

    DRV_HIFB_SelectAntiflickerMode(pstPar);

    return HI_SUCCESS;
}


/***************************************************************************************
* func        : hifb_set_canvasbufinfo
* description : CNcomment: 设置canvas buffer 信息 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 hifb_set_canvasbufinfo(struct fb_info *info, HIFB_LAYER_INFO_S *pLayerInfo)
{
    HIFB_PAR_S *par = NULL;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(pLayerInfo,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (!(pLayerInfo->u32Mask & HIFB_LAYERMASK_CANVASSIZE))
    {
        HI_GFX_UNF_FuncExit(par->debug);
        return HI_SUCCESS;
    }

    if ((pLayerInfo->u32CanvasWidth > CONFIG_HIFB_HD_LAYER_MAXWIDTH) || (pLayerInfo->u32CanvasHeight > CONFIG_HIFB_HD_LAYER_MAXHEIGHT))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    u32Stride = CONIFG_HIFB_GetMaxStride(pLayerInfo->u32CanvasWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);

    par->stDispInfo.stCanvasSur.u32Width  = pLayerInfo->u32CanvasWidth;
    par->stDispInfo.stCanvasSur.u32Height = pLayerInfo->u32CanvasHeight;
    par->stDispInfo.stCanvasSur.enFmt     = hifb_getfmtbyargb(&info->var.red, &info->var.green, &info->var.blue, &info->var.transp, info->var.bits_per_pixel);
    par->stDispInfo.stCanvasSur.u32Pitch  = u32Stride;

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
static HI_VOID HIFB_OSR_FreeStereoBuf(HIFB_PAR_S *par)
{
    HI_ULONG StereoLockFlag = 0;
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);
    g_stGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone(HI_TRUE);

    DRV_HIFB_Lock(&par->st3DInfo.StereoLock,&StereoLockFlag);
    par->st3DInfo.IsStereo = HI_FALSE;
    DRV_HIFB_UnLock(&par->st3DInfo.StereoLock,&StereoLockFlag);

    (HI_VOID)wait_event_interruptible_timeout(par->st3DInfo.WaiteFinishUpStereoInfoMutex,
                                              (HI_FALSE == par->st3DInfo.BegUpStereoInfo),
                                              CONFIG_HIFB_STEREO_WAITE_TIME);
    /** delay ensure for gfx finish display **/
    msleep(25 * 4);

    hifb_buf_freemem(par->st3DInfo.st3DMemInfo.u32StereoMemStart,HI_TRUE);

    DRV_HIFB_Lock(&par->st3DInfo.StereoLock,&StereoLockFlag);
    par->st3DInfo.BegUpStereoInfo = HI_FALSE;
    par->st3DInfo.st3DMemInfo.u32StereoMemStart = 0;
    par->st3DInfo.st3DMemInfo.u32StereoMemLen   = 0;
    par->st3DInfo.st3DSurface.u32PhyAddr        = 0;
    DRV_HIFB_UnLock(&par->st3DInfo.StereoLock,&StereoLockFlag);

    return;
}

static HI_S32 HIFB_OSR_AllocStereoBuf(struct fb_info *info, HI_U32 u32BufSize)
{
    HIFB_PAR_S *par = NULL;
    HI_CHAR name[256] = "\0";

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HIFB_CHECK_EQUAL_RETURN(0, u32BufSize, HI_FAILURE);

    HIFB_CHECK_EQUAL_RETURN(u32BufSize, par->st3DInfo.st3DMemInfo.u32StereoMemLen, HI_SUCCESS);

    if (par->st3DInfo.st3DMemInfo.u32StereoMemStart)
    {
        HIFB_OSR_FreeStereoBuf(par);
    }

    snprintf(name, sizeof(name), "HIFB_StereoBuf%d", par->stBaseInfo.u32LayerID);
    name[sizeof(name) - 1] = '\0';

    par->st3DInfo.st3DMemInfo.u32StereoMemStart = hifb_buf_allocmem(name, "iommu", u32BufSize);

    if (0 == par->st3DInfo.st3DMemInfo.u32StereoMemStart)
    {
        HIFB_ERROR("alloc stereo buffer no mem, u32BufSize:%d\n", u32BufSize);
        return HI_FAILURE;
    }

    par->st3DInfo.st3DMemInfo.u32StereoMemLen = u32BufSize;

    return HI_SUCCESS;
}

static HI_VOID HIFB_OSR_ClearStereoBuf(struct fb_info *info)
{
    HIFB_PAR_S *par = NULL;
    HIFB_BLIT_OPT_S stOpt;

    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    if ((0 == par->st3DInfo.st3DMemInfo.u32StereoMemStart) || (0 == par->st3DInfo.st3DMemInfo.u32StereoMemLen))
    {
       return;
    }

    HI_GFX_Memset(&stOpt, 0x0, sizeof(stOpt));
    par->st3DInfo.st3DSurface.u32PhyAddr = par->st3DInfo.st3DMemInfo.u32StereoMemStart;

    stOpt.bBlock = HI_TRUE;
    g_stGfx2dCallBackFunction.HIFB_DRV_ClearRect(&(par->st3DInfo.st3DSurface), &stOpt);

    return;
}


static HI_S32 HIFB_OSR_ClearUnUsedStereoBuf(struct fb_info *info)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride = 0;
    HIFB_PAR_S *par = NULL;
    HIFB_BLIT_OPT_S stOpt;
    HIFB_SURFACE_S Surface;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    if (par->stExtendInfo.enBufMode == HIFB_REFRESH_MODE_WITH_PANDISPLAY || par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_NONE)
    {
        HIFB_OSR_ClearStereoBuf(info);
        return HI_SUCCESS;
    }

    HI_GFX_Memset(&stOpt, 0x0, sizeof(stOpt));
    HI_GFX_Memset(&Surface, 0x0, sizeof(Surface));

    Surface.enFmt     = par->stExtendInfo.enColFmt;
    Surface.u32Height = par->stExtendInfo.u32DisplayHeight;
    Surface.u32Width  = par->stExtendInfo.u32DisplayWidth;

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_BITSPERPIXEL,par->stExtendInfo.u32DisplayWidth,0,0, 0,info->var.bits_per_pixel);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    u32Stride = CONIFG_HIFB_GetMaxStride(par->stExtendInfo.u32DisplayWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    Surface.u32Pitch  = u32Stride;

    if ((par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_DOUBLE) || (par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_DOUBLE_IMMEDIATE))
    {
        HIFB_CHECK_ARRAY_OVER_RETURN(par->stRunInfo.u32IndexForInt, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
        Surface.u32PhyAddr = par->st3DInfo.u32DisplayAddr[par->stRunInfo.u32IndexForInt];
    }
    else
    {
        Surface.u32PhyAddr = par->st3DInfo.u32DisplayAddr[0];
    }

    if (HI_NULL == Surface.u32PhyAddr)
    {
        HIFB_ERROR("fail to clear stereo rect.\n");
        return HI_FAILURE;
    }

    stOpt.bBlock = HI_TRUE;
    g_stGfx2dCallBackFunction.HIFB_DRV_ClearRect(&Surface, &stOpt);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ReAllocStereoBuf(HIFB_LAYER_ID_E enLayerId, HI_U32 u32BufStride, HI_U32 u32BufferSize)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *info = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    info = s_stLayer[enLayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    if (HIFB_STEREO_MONO == pstPar->st3DInfo.StereoMode)
    {
        return HI_SUCCESS;
    }

    if ((HIFB_LAYER_BUF_NONE != pstPar->stExtendInfo.enBufMode) && (HIFB_REFRESH_MODE_WITH_PANDISPLAY != pstPar->stExtendInfo.enBufMode))
    {
        return HI_SUCCESS;
    }

    if ((HIFB_REFRESH_MODE_WITH_PANDISPLAY == pstPar->stExtendInfo.enBufMode) && (HIFB_STEREO_FRMPACKING  == pstPar->st3DInfo.StereoMode))
    {
        return HI_SUCCESS;
    }

    if (u32BufferSize <= pstPar->st3DInfo.st3DMemInfo.u32StereoMemLen)
    {
        return HI_SUCCESS;
    }

    Ret = HIFB_OSR_AllocStereoBuf(info, u32BufferSize);
    if (Ret != HI_SUCCESS)
    {
        HIFB_ERROR("alloc 3D buffer failure!, expect mem size: %d\n", u32BufferSize);
        return Ret;
    }

    pstPar->st3DInfo.st3DSurface.u32Width  = info->var.xres;
    pstPar->st3DInfo.st3DSurface.u32Height = info->var.yres;
    pstPar->st3DInfo.st3DSurface.u32Pitch  = u32BufStride;
    pstPar->st3DInfo.st3DSurface.u32PhyAddr = pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart;
    pstPar->st3DInfo.u32rightEyeAddr = pstPar->st3DInfo.st3DSurface.u32PhyAddr;
    pstPar->stRunInfo.u32IndexForInt = 0;

    HIFB_OSR_ClearStereoBuf(info);

    hifb_assign_dispbuf(pstPar->stBaseInfo.u32LayerID);

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func         : hifb_set_par
* description  : CNcomment: 配置参数 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_set_par(struct fb_info *info)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride = 0;
    HI_U32 u32BufSize = 0;
    HIFB_PAR_S *pstPar = NULL;
    HIFB_COLOR_FMT_E enFmt = HIFB_FMT_ARGB8888;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    Ret = HIFB_OSR_CheckWhetherResolutionSupport(pstPar->stBaseInfo.u32LayerID, info->var.xres, info->var.yres);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    enFmt = hifb_getfmtbyargb(&info->var.red, &info->var.green, &info->var.blue, &info->var.transp, info->var.bits_per_pixel);

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_BITSPERPIXEL,info->var.xres_virtual,0,0, 0,info->var.bits_per_pixel);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }
    u32Stride = CONIFG_HIFB_GetMaxStride(info->var.xres_virtual,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);

    if (!pstPar->bPanFlag)
    {
        u32BufSize = HI_HIFB_GetMemSize(u32Stride,info->var.yres_virtual);
        HIFB_CHECK_EQUAL_RETURN(u32BufSize, 0, HI_FAILURE);

        if (u32BufSize > info->fix.smem_len)
        {
            HI_GFX_Memset(&(pstPar->stDispTmpBuf),0,sizeof(pstPar->stDispTmpBuf));
            pstPar->stDispTmpBuf.u32SmemStartPhy  = pstPar->u32SmemStartPhy;
            pstPar->stDispTmpBuf.u32PhyBuf = info->fix.smem_start;
            pstPar->stDispTmpBuf.pVirBuf = info->screen_base;

            Ret = DRV_HIFB_AllocLayerBuffer(pstPar->stBaseInfo.u32LayerID,u32BufSize);
            if (HI_FAILURE == Ret)
            {
                HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
                return HI_FAILURE;
            }

            info->fix.smem_len = u32BufSize;

            pstPar->stRunInfo.u32IndexForInt = 0;
            hifb_assign_dispbuf(pstPar->stBaseInfo.u32LayerID);

            pstPar->stRunInfo.bModifying = HI_TRUE;
            pstPar->stRunInfo.CurScreenAddr = info->fix.smem_start;
            pstPar->st3DInfo.u32rightEyeAddr = info->fix.smem_start;
            pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
            pstPar->stRunInfo.bModifying = HI_FALSE;

            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(pstPar->stBaseInfo.u32LayerID, info->fix.smem_start);

            INIT_WORK(&(pstPar->stDispTmpBuf.bDisBufWork), HIFB_ReAllocWork);
            pstPar->stDispTmpBuf.bStartRelease = HI_TRUE;

        }
    }
    else
    {
        Ret = hifb_checkmem_enough(info, u32Stride, info->var.yres_virtual);
        if (HI_FAILURE == Ret)
        {
            HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
            return HI_FAILURE;
        }
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if ((pstPar->st3DInfo.IsStereo) && (HIFB_REFRESH_MODE_WITH_PANDISPLAY == pstPar->stExtendInfo.enBufMode))
    {
        u32Stride = CONIFG_HIFB_GetMaxStride(info->var.xres,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);

        pstPar->st3DInfo.st3DSurface.enFmt     = enFmt;
        pstPar->st3DInfo.st3DSurface.u32Width  = info->var.xres;
        pstPar->st3DInfo.st3DSurface.u32Height = info->var.yres;

        pstPar->stRunInfo.bModifying           = HI_TRUE;
        pstPar->st3DInfo.st3DSurface.u32Pitch  = u32Stride;
        pstPar->stRunInfo.u32ParamModifyMask  |= HIFB_LAYER_PARAMODIFY_STRIDE;
        pstPar->stRunInfo.bModifying           = HI_FALSE;
        info->fix.line_length = u32Stride;
    }
    else
#endif
    {
        u32Stride = CONIFG_HIFB_GetMaxStride(info->var.xres_virtual,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
        if ((u32Stride != info->fix.line_length) ||(info->var.yres != pstPar->stExtendInfo.u32DisplayHeight))
        {
            pstPar->stRunInfo.bModifying     = HI_TRUE;
            info->fix.line_length            = u32Stride;
            hifb_assign_dispbuf(pstPar->stBaseInfo.u32LayerID);
            pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
            pstPar->stRunInfo.bModifying      = HI_FALSE;
        }
    }

    if ((pstPar->stExtendInfo.enColFmt != enFmt))
    {
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
        HIFB_CHECK_LAYERID_SUPPORT_RETURN(pstPar->stBaseInfo.u32LayerID, HI_FAILURE);

        if (s_stTextLayer[pstPar->stBaseInfo.u32LayerID].bAvailable)
        {
            HI_U32 i = 0;
            for (i = 0; i < SCROLLTEXT_NUM; i++)
            {
                if (s_stTextLayer[pstPar->stBaseInfo.u32LayerID].stScrollText[i].bAvailable)
                {
                    hifb_freescrolltext_cachebuf(&(s_stTextLayer[pstPar->stBaseInfo.u32LayerID].stScrollText[i]));
                    HI_GFX_Memset(&s_stTextLayer[pstPar->stBaseInfo.u32LayerID].stScrollText[i],0,sizeof(HIFB_SCROLLTEXT_S));
                }
            }
            s_stTextLayer[pstPar->stBaseInfo.u32LayerID].bAvailable      = HI_FALSE;
            s_stTextLayer[pstPar->stBaseInfo.u32LayerID].u32textnum      = 0;
            s_stTextLayer[pstPar->stBaseInfo.u32LayerID].u32ScrollTextId = 0;
        }
#endif
        pstPar->stRunInfo.bModifying   = HI_TRUE;
        pstPar->stExtendInfo.enColFmt = enFmt;
        pstPar->stRunInfo.u32ParamModifyMask  |= HIFB_LAYER_PARAMODIFY_FMT;
        pstPar->stRunInfo.bModifying = HI_FALSE;

    }

    HIFB_OSR_SetDispInfo(pstPar->stBaseInfo.u32LayerID);

    pstPar->bPanFlag = HI_TRUE;

    return HI_SUCCESS;
}

static inline HI_S32 HIFB_OSR_CheckWhetherResolutionSupport(HI_U32 LayerId, HI_U32 Width, HI_U32 Height)
{
    switch (LayerId)
    {
       case HIFB_LAYER_HD_0:
       case HIFB_LAYER_HD_1:
       case HIFB_LAYER_HD_2:
       case HIFB_LAYER_HD_3:
           if (Width > CONFIG_HIFB_HD_LAYER_MAXWIDTH || Height > CONFIG_HIFB_HD_LAYER_MAXHEIGHT)
           {
               HIFB_INFO("the hd input ui size is not support\n ");
               return HI_FAILURE;
           }
           break;
       case HIFB_LAYER_SD_0:
       case HIFB_LAYER_SD_1:
           if (Width > CONFIG_HIFB_SD_LAYER_MAXWIDTH || Height > CONFIG_HIFB_SD_LAYER_MAXHEIGHT)
           {
               HIFB_INFO("the sd input ui size is not support\n ");
               return HI_FAILURE;
           }
           break;
       default:
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static inline HI_VOID HIFB_OSR_SetDispInfo(HI_U32 LayerId)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if ((info->var.xres == pstPar->stExtendInfo.u32DisplayWidth) && (info->var.yres == pstPar->stExtendInfo.u32DisplayHeight))
    {
        return;
    }

    if ((0 == info->var.xres) || (0 == info->var.yres))
    {
        if (HI_TRUE == pstPar->stExtendInfo.bShow)
        {
            pstPar->stRunInfo.bModifying          = HI_TRUE;
            pstPar->stExtendInfo.bShow            = HI_FALSE;
            pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_SHOW;
            pstPar->stRunInfo.bModifying          = HI_FALSE;
        }
    }

    hifb_disp_setdispsize(LayerId, info->var.xres, info->var.yres);
    hifb_assign_dispbuf(LayerId);

   return;
}

static HI_VOID hifb_disp_setlayerpos(HI_U32 u32LayerId, HI_S32 s32XPos, HI_S32 s32YPos)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stExtendInfo.stPos.s32XPos = s32XPos;
    pstPar->stExtendInfo.stPos.s32YPos = s32YPos;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    return;
}

static HI_VOID hifb_buf_setbufmode(HI_U32 u32LayerId, HIFB_LAYER_BUF_E enLayerBufMode)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if ((pstPar->stExtendInfo.enBufMode == HIFB_LAYER_BUF_NONE) && (pstPar->stExtendInfo.enBufMode != enLayerBufMode))
    {
        pstPar->stRunInfo.bModifying = HI_TRUE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FMT;
        pstPar->stRunInfo.bModifying = HI_FALSE;
    }

    pstPar->stExtendInfo.enBufMode = enLayerBufMode;

    return;
}


/***************************************************************************************
* func         : hifb_disp_setdispsize
* description  : CNcomment: choose the module to do  flicker resiting,
                            TDE or VOU ? the rule is as this ,the moudle
                            should do flicker resisting who has do scaling CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_VOID DRV_HIFB_SelectAntiflickerMode(HIFB_PAR_S *pstPar)
{
    HIFB_RECT stOutputRect = {0};

    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if (HIFB_LAYER_ANTIFLICKER_NONE == pstPar->stBaseInfo.enAntiflickerLevel)
    {
       pstPar->stBaseInfo.bNeedAntiflicker = HI_FALSE;
       pstPar->stBaseInfo.enAntiflickerMode = HIFB_ANTIFLICKER_NONE;
       return;
    }

    pstPar->stBaseInfo.bNeedAntiflicker = HI_TRUE;

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerOutRect(pstPar->stBaseInfo.u32LayerID, &stOutputRect);

   if ((pstPar->stExtendInfo.u32DisplayWidth != stOutputRect.w) || (pstPar->stExtendInfo.u32DisplayHeight != stOutputRect.h))
   {
       pstPar->stBaseInfo.enAntiflickerMode = HIFB_ANTIFLICKER_VO;
       return;
   }

   pstPar->stBaseInfo.enAntiflickerMode = HIFB_ANTIFLICKER_TDE;

   return;
}


/***************************************************************************************
* func         : DRV_HIFB_SetAntiflickerLevel
* description  : CNcomment: 设置抗闪级别 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_VOID DRV_HIFB_SetAntiflickerLevel(HI_U32 u32LayerId, HIFB_LAYER_ANTIFLICKER_LEVEL_E enAntiflickerLevel)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    pstPar->stBaseInfo.enAntiflickerLevel = enAntiflickerLevel;
    DRV_HIFB_SelectAntiflickerMode(pstPar);

    return;
}

static HI_S32 DRV_HIFB_SetDispAddressr(HI_U32 u32LayerId)
{
    HI_U32 u32Index;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (pstPar->st3DInfo.IsStereo)
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(u32LayerId, pstPar->st3DInfo.u32DisplayAddr[u32Index]);
        pstPar->stRunInfo.CurScreenAddr  = pstPar->st3DInfo.u32DisplayAddr[u32Index];
        pstPar->st3DInfo.u32rightEyeAddr = pstPar->stRunInfo.CurScreenAddr;
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimAddr(u32LayerId, pstPar->st3DInfo.u32rightEyeAddr);
    }
    else
#endif
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(u32LayerId, pstPar->stDispInfo.u32DisplayAddr[u32Index]);
        pstPar->stRunInfo.CurScreenAddr  = pstPar->stDispInfo.u32DisplayAddr[u32Index];
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (HI_TRUE == pstPar->st3DInfo.IsStereo)
    {
        pstPar->stRunInfo.u32IndexForInt = (++u32Index) % pstPar->stRunInfo.StereoBufNum;
    }
    else
#endif
    {
        pstPar->stRunInfo.u32IndexForInt = (++u32Index) % pstPar->stRunInfo.u32BufNum;
    }

    pstPar->stRunInfo.bFliped = HI_TRUE;
    pstPar->stRunInfo.bNeedFlip = HI_FALSE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : hifb_vo_callback
* description  : CNcomment: vo中断处理 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_vo_callback(HI_VOID *pParaml, HI_VOID *pParamr)
{
    HI_U32 *pu32LayerId  = NULL;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar   = NULL;
    HIFB_RECT stInRect   = {0};
    HI_U32 NowTimeMs = 0;
    HI_U32 EndTimeMs = 0;
    static HI_U32 FlipFps = 0;
    HI_BOOL  HasBeenClosedForVoCallBack = HI_FALSE;
    HI_BOOL  bARDataDecompressErr = HI_FALSE;
    HI_BOOL  bGBDataDecompressErr = HI_FALSE;
    HI_ULONG ExpectIntLineNumsForVoCallBack  = 0;
    HI_ULONG ExpectIntLineNumsForEndCallBack = 0;
    HI_ULONG ActualIntLineNumsForVoCallBack  = 0;
    HI_ULONG HardIntCntForVoCallBack = 0;
    HI_GFX_TINIT();
    HI_UNUSED(pParamr);

    /*************************** check para ***********************************/
    HIFB_CHECK_NULLPOINTER_RETURN(pParaml, HI_FAILURE);
    pu32LayerId  = (HI_U32*)pParaml;
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(*pu32LayerId, HI_FAILURE);

    info = s_stLayer[*pu32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    /*************************** count fps ************************************/
    HI_GFX_TSTART(NowTimeMs);
    FlipFps++;
    if ((NowTimeMs - pstPar->stFrameInfo.StartTimeMs) >= 1000)
    {
        pstPar->stFrameInfo.StartTimeMs = NowTimeMs;
        pstPar->stFrameInfo.FlipFps = (FlipFps != pstPar->stFrameInfo.FlipFps) ? FlipFps : pstPar->stFrameInfo.FlipFps;
        pstPar->stFrameInfo.DrawFps = pstPar->stFrameInfo.RefreshFrame;
        pstPar->stFrameInfo.RefreshFrame = 0;
        FlipFps = 0;
    }
    pstPar->stFrameInfo.bFrameHit = HI_FALSE;

    /*************************** count times **********************************/
    g_stDrvAdpCallBackFunction.HIFB_ADP_GetCloseState(*pu32LayerId,&HasBeenClosedForVoCallBack, NULL);
    if (HI_TRUE == HasBeenClosedForVoCallBack)
    {
        pstPar->stFrameInfo.PreTimeMs = 0;
        pstPar->stFrameInfo.MaxTimeMs = 0;
    }
    if (0 == pstPar->stFrameInfo.PreTimeMs)
    {
        pstPar->stFrameInfo.PreTimeMs = NowTimeMs;
    }
    if ((NowTimeMs - pstPar->stFrameInfo.PreTimeMs) > pstPar->stFrameInfo.MaxTimeMs)
    {
        pstPar->stFrameInfo.MaxTimeMs = NowTimeMs - pstPar->stFrameInfo.PreTimeMs;
    }
    pstPar->stFrameInfo.PreTimeMs = NowTimeMs;

    /*************************** count interupt information *******************/
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetDhd0Info(*pu32LayerId,&ExpectIntLineNumsForVoCallBack,
                                                    &ExpectIntLineNumsForEndCallBack,&ActualIntLineNumsForVoCallBack,
                                                    &HardIntCntForVoCallBack);
    pstPar->stFrameInfo.ExpectIntLineNumsForVoCallBack  = ExpectIntLineNumsForVoCallBack;
    pstPar->stFrameInfo.ExpectIntLineNumsForEndCallBack = ExpectIntLineNumsForEndCallBack;
    pstPar->stFrameInfo.ActualIntLineNumsForVoCallBack  = ActualIntLineNumsForVoCallBack;
    pstPar->stFrameInfo.HardIntCntForVoCallBack         = HardIntCntForVoCallBack;

    pstPar->stFrameInfo.VoSoftCallBackCnt++;

    /*************************** count decompress times ***********************/
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetDecompressStatus(*pu32LayerId, &bARDataDecompressErr, &bGBDataDecompressErr);
    if (HI_TRUE == bARDataDecompressErr)
    {
       pstPar->stFrameInfo.ARDataDecompressErrCnt++;
    }

    if (HI_TRUE == bGBDataDecompressErr)
    {
       pstPar->stFrameInfo.GBDataDecompressErrCnt++;
    }

    /*************************** up register information **********************/
    if (!pstPar->stRunInfo.bModifying)
    {
        if (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_SHOW)
        {
            g_stDrvAdpCallBackFunction.HIFB_DRV_EnableLayer(*pu32LayerId, pstPar->stExtendInfo.bShow);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_SHOW;
        }

        if (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_ALPHA)
        {
            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAlpha(*pu32LayerId, &pstPar->stExtendInfo.stAlpha);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_ALPHA;
        }

        if (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_COLORKEY)
        {
            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerKeyMask(*pu32LayerId, &pstPar->stExtendInfo.stCkey);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_COLORKEY;
        }

        if (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_BMUL)
        {
            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerPreMult(*pu32LayerId, pstPar->stBaseInfo.bPreMul);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_BMUL;
        }

        if (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_ANTIFLICKERLEVEL)
        {
            HIFB_DEFLICKER_S stDeflicker;
            stDeflicker.pu8HDfCoef  = pstPar->stBaseInfo.ucHDfcoef;
            stDeflicker.pu8VDfCoef  = pstPar->stBaseInfo.ucVDfcoef;
            stDeflicker.u32HDfLevel = pstPar->stBaseInfo.u32HDflevel;
            stDeflicker.u32VDfLevel = pstPar->stBaseInfo.u32VDflevel;

            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDeFlicker(*pu32LayerId, &stDeflicker);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_ANTIFLICKERLEVEL;
        }

        if (  (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_INRECT)
            ||(pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_OUTRECT))
        {
            stInRect.x = pstPar->stExtendInfo.stPos.s32XPos;
            stInRect.y = pstPar->stExtendInfo.stPos.s32YPos;
            stInRect.w = (HI_S32)pstPar->stExtendInfo.u32DisplayWidth;
            stInRect.h = (HI_S32)pstPar->stExtendInfo.u32DisplayHeight;

            g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerInRect(*pu32LayerId, &stInRect);
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_INRECT;
            pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_OUTRECT;
        }

        HIFB_OSR_UpdataInputDataFmt(*pu32LayerId);

        HIFB_OSR_UpdataInputDataStride(*pu32LayerId);

        #ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
        DRV_HIFB_UpLowPowerInfo(*pu32LayerId);
        #endif

        HIFB_OSR_UpdataRefreshInfo(*pu32LayerId);
    }

    HIFB_OSR_SwitchDispBuffer(*pu32LayerId);

    g_stDrvAdpCallBackFunction.HIFB_DRV_UpdataLayerReg(*pu32LayerId);

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    hifb_scrolltext_blit(*pu32LayerId);
#endif

    /*************************** count run times ******************************/
    HI_GFX_TEND(EndTimeMs);
    if ((EndTimeMs - NowTimeMs) > pstPar->stFrameInfo.RunMaxTimeMs)
    {
        pstPar->stFrameInfo.RunMaxTimeMs = EndTimeMs - NowTimeMs;
    }

    return HI_SUCCESS;
}


#ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
static inline HI_VOID DRV_HIFB_UpLowPowerInfo(HI_U32 LayerId)
{
    HI_U32 IsLowPowerHasRfresh = 0x0;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *info = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    IsLowPowerHasRfresh = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_LOWPOWER);
    if (!IsLowPowerHasRfresh)
    {
       return;
    }

    g_stDrvAdpCallBackFunction.HIFB_OSI_SetLowPowerInfo(LayerId,&(pstPar->stLowPowerInfo));

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_LOWPOWER;

    return;
}
#endif

//#define CONFIG_HIFB_RESUME
static inline HI_VOID HIFB_OSR_UpdataRefreshInfo(HI_U32 LayerId)
{
#ifdef CONFIG_HIFB_RESUME
    HI_BOOL bResume = HI_FALSE;
#endif
    HI_U32 IsInputDataHasRfresh = 0x0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

#if defined(CFG_HIFB_FENCE_SUPPORT) && defined(CONFIG_HIFB_RESUME)
    HI_BOOL bDispEnable = HI_FALSE;
    HI_U32 BufferId = 0;
#endif

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    IsInputDataHasRfresh = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_REFRESH);

#ifdef CONFIG_HIFB_RESUME
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetResumeStatus(LayerId,&bResume);
    if (HI_TRUE == bResume)
    {
        IsInputDataHasRfresh = 0x1;
#ifdef CFG_HIFB_FENCE_SUPPORT
        g_stDrvAdpCallBackFunction.HIFB_DRV_GetHaltDispStatus(pstPar->stBaseInfo.u32LayerID, &bDispEnable);
        while (pstPar->FenceRefreshCount > 0)
        {
            BufferId = DRV_HIFB_GetBufferId(pstPar->stBaseInfo.u32LayerID, pstPar->stRunInfo.CurScreenAddr);
            DRV_HIFB_IncRefreshTime(bDispEnable, BufferId);
            pstPar->FenceRefreshCount--;
        }
#endif
    }
#endif

    if (!IsInputDataHasRfresh)
    {
        return;
    }

    HIFB_OSR_UpdataInputDataDDR(LayerId);

#if defined(CFG_HIFB_FENCE_SUPPORT) || defined(CFG_HI_FB_DECOMPRESS_SUPPORT)
    DRV_HIFB_SetDecmpLayerInfo(LayerId);
#endif

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_REFRESH;

    return;
}

static inline HI_VOID HIFB_OSR_UpdataInputDataFmt(HI_U32 LayerId)
{
    HI_U32 IsInputDataFmtHasChanged = 0x0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    IsInputDataFmtHasChanged = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_FMT);
    if (!IsInputDataFmtHasChanged)
    {
         return;
    }

    if ((pstPar->stExtendInfo.enBufMode == HIFB_LAYER_BUF_NONE) && pstPar->stDispInfo.stUserBuffer.stCanvas.u32PhyAddr)
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(LayerId, pstPar->stDispInfo.stUserBuffer.stCanvas.enFmt);
    }
    else
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(LayerId, pstPar->stExtendInfo.enColFmt);
    }

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_FMT;

    return;
}

static inline HI_VOID HIFB_OSR_UpdataInputDataStride(HI_U32 LayerId)
{
     HI_U32 InputDataStride = 0;
     HI_U32 IsInputDataStrideHasChanged = 0x0;
     struct fb_info *info = NULL;
     HIFB_PAR_S *pstPar = NULL;

     HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
     info = s_stLayer[LayerId].pstInfo;
     HIFB_CHECK_NULLPOINTER_UNRETURN(info);

     pstPar = (HIFB_PAR_S *)(info->par);
     HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

     IsInputDataStrideHasChanged = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_STRIDE);
     if (!IsInputDataStrideHasChanged)
     {
         return;
     }

 #ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
     if (pstPar->st3DInfo.IsStereo)
     {
        InputDataStride = pstPar->st3DInfo.st3DSurface.u32Pitch;
     }
     else
 #endif
    {
         if ((pstPar->stExtendInfo.enBufMode == HIFB_LAYER_BUF_NONE) && (pstPar->stDispInfo.stUserBuffer.stCanvas.u32PhyAddr))
         {
             InputDataStride = pstPar->stDispInfo.stUserBuffer.stCanvas.u32Pitch;
         }
         else
         {
             InputDataStride = info->fix.line_length;
         }
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerStride(LayerId, InputDataStride);

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_STRIDE;

    return;
}


static inline HI_VOID HIFB_OSR_UpdataInputDataDDR(HI_U32 LayerId)
{
    HI_U32 IsInputDataDDRHasChanged = 0x0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    IsInputDataDDRHasChanged = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_DISPLAYADDR);
    if (!IsInputDataDDRHasChanged)
    {
       return;
    }

    pstPar->stFrameInfo.RefreshFrame++;
    pstPar->stFrameInfo.bFrameHit = HI_TRUE;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(LayerId, pstPar->stRunInfo.CurScreenAddr);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (pstPar->st3DInfo.IsStereo)
    {
        pstPar->st3DInfo.u32rightEyeAddr = pstPar->stRunInfo.CurScreenAddr;

        g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimAddr(LayerId, pstPar->st3DInfo.u32rightEyeAddr);
    }
#endif

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_DISPLAYADDR;

    return;
}

static inline HI_VOID HIFB_OSR_SwitchDispBuffer(HI_U32 LayerId)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if ((pstPar->stExtendInfo.enBufMode == HIFB_LAYER_BUF_DOUBLE) && (pstPar->stRunInfo.bNeedFlip == HI_TRUE))
    {
        DRV_HIFB_SetDispAddressr(LayerId);
    }

    if (HI_TRUE == pstPar->stDispTmpBuf.bStartRelease)
    {
        schedule_work(&(pstPar->stDispTmpBuf.bDisBufWork));
        pstPar->stDispTmpBuf.bStartRelease = HI_FALSE;
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    else if ((pstPar->stExtendInfo.enBufMode == HIFB_REFRESH_MODE_WITH_PANDISPLAY)
            && pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart
            && pstPar->st3DInfo.IsStereo
            && (pstPar->stRunInfo.bNeedFlip == HI_TRUE))
    {
        DRV_HIFB_SetDispAddressr(LayerId);
    }
#endif

    return;
}


/***************************************************************************************
* func          : hifb_refresh_0buf
* description   : CNcomment: no display buffer refresh CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 hifb_refresh_0buf(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_U32 u32StartAddr;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);
    u32StartAddr = pstCanvasBuf->stCanvas.u32PhyAddr;

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.CurScreenAddr = u32StartAddr;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;

    pstPar->stDispInfo.stUserBuffer.stCanvas.u32Pitch = pstCanvasBuf->stCanvas.u32Pitch;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;

    pstPar->stDispInfo.stUserBuffer.stCanvas.enFmt = pstCanvasBuf->stCanvas.enFmt;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FMT;

    hifb_disp_setdispsize(u32LayerId, pstCanvasBuf->stCanvas.u32Width, pstCanvasBuf->stCanvas.u32Height);

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;

    pstPar->stRunInfo.bModifying = HI_FALSE;

    DRV_HIFB_WaitVBlank(u32LayerId);

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : hifb_refresh_1buf
* description  : CNcomment: one canvas buffer,one display buffer refresh CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_refresh_1buf(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_BUFFER_S stDisplayBuf;
    HIFB_OSD_DATA_S stOsdData;
    HIFB_BLIT_OPT_S stBlitOpt;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HI_GFX_Memset(&stBlitOpt,    0, sizeof(stBlitOpt));
    HI_GFX_Memset(&stDisplayBuf, 0, sizeof(stDisplayBuf));

    stDisplayBuf.stCanvas.enFmt      = pstPar->stExtendInfo.enColFmt;
    stDisplayBuf.stCanvas.u32Height  = pstPar->stExtendInfo.u32DisplayHeight;
    stDisplayBuf.stCanvas.u32Width   = pstPar->stExtendInfo.u32DisplayWidth;
    stDisplayBuf.stCanvas.u32Pitch   = info->fix.line_length;
    stDisplayBuf.stCanvas.u32PhyAddr = pstPar->stDispInfo.u32DisplayAddr[0];

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetOSDData(u32LayerId, &stOsdData);

    if (stOsdData.u32RegPhyAddr != pstPar->stDispInfo.u32DisplayAddr[0] && pstPar->stDispInfo.u32DisplayAddr[0])
    {
        pstPar->stRunInfo.bModifying = HI_TRUE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
        pstPar->stRunInfo.CurScreenAddr = pstPar->stDispInfo.u32DisplayAddr[0];
        HI_GFX_Memset(info->screen_base, 0x0, info->fix.smem_len);
        pstPar->stRunInfo.bModifying = HI_FALSE;
    }

    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        //stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);

    if (   pstCanvasBuf->stCanvas.u32Height != pstPar->stExtendInfo.u32DisplayHeight
        || pstCanvasBuf->stCanvas.u32Width != pstPar->stExtendInfo.u32DisplayWidth)
    {
        stBlitOpt.bScale = HI_TRUE;
        stDisplayBuf.UpdateRect.x = 0;
        stDisplayBuf.UpdateRect.y = 0;
        stDisplayBuf.UpdateRect.w = stDisplayBuf.stCanvas.u32Width;
        stDisplayBuf.UpdateRect.h = stDisplayBuf.stCanvas.u32Height;
    }
    else
    {
        stDisplayBuf.UpdateRect = pstCanvasBuf->UpdateRect;
    }

    stBlitOpt.bRegionDeflicker = HI_TRUE;

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(pstCanvasBuf, &stDisplayBuf, &stBlitOpt, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("hifb_refresh_1buf blit err 5!\n");
        return HI_FAILURE;
    }

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : hifb_refresh_2buf
* description  : CNcomment: 异步刷新 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_refresh_2buf(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index;
    unsigned long lockflag;
    HIFB_BUFFER_S stForeBuf;
    HIFB_BUFFER_S stBackBuf;
    HIFB_BLIT_OPT_S stBlitOpt;
    HIFB_OSD_DATA_S stOsdData;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(1-u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    HI_GFX_Memset(&stForeBuf, 0, sizeof(stForeBuf));
    HI_GFX_Memset(&stBackBuf, 0, sizeof(stBackBuf));

    stBlitOpt.bCallBack = HI_TRUE;
    stBlitOpt.pfnCallBack = (IntCallBack)DRV_HIFB_BlitFinishCallBack;
    stBlitOpt.pParam = &(pstPar->stBaseInfo.u32LayerID);

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&lockflag);
    pstPar->stRunInfo.bNeedFlip = HI_FALSE;
    pstPar->stRunInfo.s32RefreshHandle = 0;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&lockflag);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetOSDData(u32LayerId, &stOsdData);

    stBackBuf.stCanvas.enFmt      = pstPar->stExtendInfo.enColFmt;
    stBackBuf.stCanvas.u32Width   = pstPar->stExtendInfo.u32DisplayWidth;
    stBackBuf.stCanvas.u32Height  = pstPar->stExtendInfo.u32DisplayHeight;
    stBackBuf.stCanvas.u32Pitch   = info->fix.line_length;
    stBackBuf.stCanvas.u32PhyAddr = pstPar->stDispInfo.u32DisplayAddr[u32Index];

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);

    if (  (pstCanvasBuf->stCanvas.u32Height != pstPar->stExtendInfo.u32DisplayHeight)
        ||(pstCanvasBuf->stCanvas.u32Width  != pstPar->stExtendInfo.u32DisplayWidth))
    {
        stBlitOpt.bScale = HI_TRUE;
    }

    hifb_getupdate_rect(u32LayerId, pstCanvasBuf, &stBackBuf.UpdateRect);

    if ((pstPar->stRunInfo.bFliped) && (stOsdData.u32RegPhyAddr == pstPar->stDispInfo.u32DisplayAddr[1-u32Index]))
    {
        hifb_backup_forebuf(u32LayerId, &stBackBuf);
        HI_GFX_Memset(&(pstPar->stDispInfo.stUpdateRect), 0, sizeof(pstPar->stDispInfo.stUpdateRect));
        pstPar->stRunInfo.bFliped = HI_FALSE;
    }

    /* update union rect */
    if ((pstPar->stDispInfo.stUpdateRect.w == 0) || (pstPar->stDispInfo.stUpdateRect.h == 0))
    {
        HI_GFX_Memcpy(&pstPar->stDispInfo.stUpdateRect, &stBackBuf.UpdateRect, sizeof(HIFB_RECT));
    }
    else
    {
        HIFB_UNITE_RECT(pstPar->stDispInfo.stUpdateRect, stBackBuf.UpdateRect);
    }

    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    if (stBlitOpt.bScale == HI_TRUE)
    {
        stBackBuf.UpdateRect.x = 0;
        stBackBuf.UpdateRect.y = 0;
        stBackBuf.UpdateRect.w = stBackBuf.stCanvas.u32Width;
        stBackBuf.UpdateRect.h = stBackBuf.stCanvas.u32Height;
    }
    else
    {
        stBackBuf.UpdateRect = pstCanvasBuf->UpdateRect;
    }

    stBlitOpt.bRegionDeflicker = HI_TRUE;

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(pstCanvasBuf, &stBackBuf,&stBlitOpt, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("2buf blit err7!\n");
        goto RET;
    }

    pstPar->stRunInfo.s32RefreshHandle = Ret;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.bModifying = HI_FALSE;

RET:
    return HI_SUCCESS;
}

/***************************************************************************************
* func         : hifb_refresh_2buf_immediate_display
* description  : CNcomment: 同步刷新 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_refresh_2buf_immediate_display(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    unsigned long lockflag = 0;
    HIFB_BUFFER_S stForeBuf;
    HIFB_BUFFER_S stBackBuf;
    HIFB_BLIT_OPT_S stBlitOpt;
    HIFB_OSD_DATA_S stOsdData;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(1-u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    HI_GFX_Memset(&stForeBuf, 0, sizeof(stForeBuf));
    HI_GFX_Memset(&stBackBuf, 0, sizeof(stBackBuf));

    stBlitOpt.bCallBack = HI_FALSE;
    stBlitOpt.pParam = &(pstPar->stBaseInfo.u32LayerID);

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&lockflag);
    pstPar->stRunInfo.bNeedFlip = HI_FALSE;
    pstPar->stRunInfo.s32RefreshHandle = 0;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&lockflag);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetOSDData(u32LayerId, &stOsdData);

    stBackBuf.stCanvas.enFmt      = pstPar->stExtendInfo.enColFmt;
    stBackBuf.stCanvas.u32Width   = pstPar->stExtendInfo.u32DisplayWidth;
    stBackBuf.stCanvas.u32Height  = pstPar->stExtendInfo.u32DisplayHeight;
    stBackBuf.stCanvas.u32Pitch   = info->fix.line_length;
    stBackBuf.stCanvas.u32PhyAddr = pstPar->stDispInfo.u32DisplayAddr[u32Index];

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);

    if (   (pstCanvasBuf->stCanvas.u32Height != pstPar->stExtendInfo.u32DisplayHeight)
        || (pstCanvasBuf->stCanvas.u32Width  != pstPar->stExtendInfo.u32DisplayWidth))
    {
        stBlitOpt.bScale = HI_TRUE;
    }

    hifb_getupdate_rect(u32LayerId, pstCanvasBuf, &stBackBuf.UpdateRect);

    hifb_backup_forebuf(u32LayerId, &stBackBuf);

    HI_GFX_Memcpy(&pstPar->stDispInfo.stUpdateRect, &stBackBuf.UpdateRect, sizeof(HIFB_RECT));

    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    if (stBlitOpt.bScale == HI_TRUE)
    {
        stBackBuf.UpdateRect.x = 0;
        stBackBuf.UpdateRect.y = 0;
        stBackBuf.UpdateRect.w = stBackBuf.stCanvas.u32Width;
        stBackBuf.UpdateRect.h = stBackBuf.stCanvas.u32Height;
    }
    else
    {
        stBackBuf.UpdateRect = pstCanvasBuf->UpdateRect;
    }

    stBlitOpt.bRegionDeflicker = HI_TRUE;
    stBlitOpt.bBlock           = HI_TRUE;

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(pstCanvasBuf, &stBackBuf,&stBlitOpt, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("2buf blit err 0x%x!\n",Ret);
        goto RET;
    }

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.CurScreenAddr = pstPar->stDispInfo.u32DisplayAddr[u32Index];
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    pstPar->stRunInfo.u32IndexForInt = 1 - u32Index;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    DRV_HIFB_WaitVBlank(u32LayerId);
RET:
    return HI_SUCCESS;
}

/***************************************************************************************
* func         : hifb_refresh_panbuf
* description  : CNcomment: 给android使用 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
static HI_S32 hifb_refresh_panbuf(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_ULONG StereoLockFlag = 0;
    HI_U32 u32TmpAddr = 0;
    HI_U32 u32TmpSize = 0;
    HIFB_RECT UpdateRect;
    HIFB_BLIT_OPT_S stBlitOpt;
    HIFB_BUFFER_S stCanvasBuf;
    HIFB_BUFFER_S stDisplayBuf;
    struct fb_var_screeninfo *var = NULL;
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    var = &(info->var);
    HIFB_CHECK_NULLPOINTER_RETURN(var, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);
    UpdateRect = pstCanvasBuf->UpdateRect;

    if (   (UpdateRect.x >=  par->stExtendInfo.u32DisplayWidth)
        || (UpdateRect.y >= par->stExtendInfo.u32DisplayHeight)
        || (UpdateRect.w == 0) || (UpdateRect.h == 0))
    {
        HIFB_ERROR("hifb_refresh_panbuf upate rect invalid\n");
        return HI_FAILURE;
    }

    DRV_HIFB_Lock(&par->st3DInfo.StereoLock,&StereoLockFlag);
    /** IsStereo and BegUpStereoInfo should in one lock**/
    if (HI_FALSE == par->st3DInfo.IsStereo)
    {
        DRV_HIFB_UnLock(&par->st3DInfo.StereoLock,&StereoLockFlag);
        return HI_SUCCESS;
    }

    if (0 == par->st3DInfo.st3DMemInfo.u32StereoMemStart)
    {
       DRV_HIFB_UnLock(&par->st3DInfo.StereoLock,&StereoLockFlag);
       return HI_SUCCESS;
    }
    par->st3DInfo.BegUpStereoInfo = HI_TRUE;
    DRV_HIFB_UnLock(&par->st3DInfo.StereoLock,&StereoLockFlag);

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    stBlitOpt.bScale = HI_TRUE;

    if (HIFB_ANTIFLICKER_TDE == par->stBaseInfo.enAntiflickerMode)
    {
        stBlitOpt.enAntiflickerLevel = par->stBaseInfo.enAntiflickerLevel;
    }

    stBlitOpt.bBlock = HI_TRUE;
    stBlitOpt.bRegionDeflicker = HI_TRUE;

    /** get address **/
    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT | HIFB_PARA_CHECK_STRIDE | HIFB_PARA_CHECK_BITSPERPIXEL,
                                  var->xoffset, var->yoffset, info->fix.line_length, 0, var->bits_per_pixel);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    if (var->bits_per_pixel >= 8)
    {
        u32TmpSize = info->fix.line_length * var->yoffset + var->xoffset * (var->bits_per_pixel >> 3);
    }
    else
    {
        u32TmpSize = info->fix.line_length * var->yoffset + var->xoffset * var->bits_per_pixel / 8;
    }

    HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(u32TmpSize,info->fix.smem_len, HI_FAILURE);
    HI_GFX_CHECK_U64_ADDITION_REVERSAL_RETURN(info->fix.smem_start,u32TmpSize, HI_FAILURE);
    HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN(info->fix.smem_start + u32TmpSize, HI_FAILURE);
    u32TmpAddr = info->fix.smem_start + u32TmpSize;

    if ((var->bits_per_pixel == 24) && ((var->xoffset != 0)||(var->yoffset != 0)))
    {
        u32TmpSize = info->fix.line_length * var->yoffset + var->xoffset * (var->bits_per_pixel >> 3);

        HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(u32TmpSize,info->fix.smem_len, HI_FAILURE);
        HI_GFX_CHECK_U64_ADDITION_REVERSAL_RETURN(info->fix.smem_start,u32TmpSize, HI_FAILURE);
        HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN(info->fix.smem_start + u32TmpSize, HI_FAILURE);

        u32TmpAddr = (info->fix.smem_start + u32TmpSize)/16/3;
        u32TmpAddr = u32TmpAddr * 16 * 3;
    }

    /********************config pan buffer*******************/
    HI_GFX_Memset(&stCanvasBuf, 0, sizeof(stCanvasBuf));
    stCanvasBuf.stCanvas.enFmt      = par->stExtendInfo.enColFmt;
    stCanvasBuf.stCanvas.u32Pitch   = info->fix.line_length;
    stCanvasBuf.stCanvas.u32PhyAddr = u32TmpAddr;
    stCanvasBuf.stCanvas.u32Width   = par->stExtendInfo.u32DisplayWidth;
    stCanvasBuf.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stCanvasBuf.UpdateRect          = UpdateRect;
    /***********************end**************************/

    /*******************config 3D buffer********************/
    HI_GFX_Memset(&stDisplayBuf, 0, sizeof(stDisplayBuf));
    stDisplayBuf.stCanvas.enFmt      = par->st3DInfo.st3DSurface.enFmt;
    stDisplayBuf.stCanvas.u32Pitch   = par->st3DInfo.st3DSurface.u32Pitch;
    stDisplayBuf.stCanvas.u32PhyAddr = par->stRunInfo.CurScreenAddr;
    stDisplayBuf.stCanvas.u32Width   = par->st3DInfo.st3DSurface.u32Width;
    stDisplayBuf.stCanvas.u32Height  = par->st3DInfo.st3DSurface.u32Height;
    /***********************end**************************/

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  stDisplayBuf.stCanvas.u32Width, stDisplayBuf.stCanvas.u32Height, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }
    if (HIFB_STEREO_SIDEBYSIDE_HALF == par->st3DInfo.StereoMode)
    {
        stDisplayBuf.stCanvas.u32Width >>= 1;
    }
    else if (HIFB_STEREO_TOPANDBOTTOM == par->st3DInfo.StereoMode)
    {
        stDisplayBuf.stCanvas.u32Height >>= 1;
    }

    stDisplayBuf.UpdateRect.x = 0;
    stDisplayBuf.UpdateRect.y = 0;
    stDisplayBuf.UpdateRect.w = stDisplayBuf.stCanvas.u32Width;
    stDisplayBuf.UpdateRect.h = stDisplayBuf.stCanvas.u32Height;

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(&stCanvasBuf, &stDisplayBuf, &stBlitOpt, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("stereo blit error!\n");
        return HI_FAILURE;
    }

    /** can relese stereo memory **/
    par->st3DInfo.BegUpStereoInfo = HI_FALSE;
    wake_up_interruptible(&par->st3DInfo.WaiteFinishUpStereoInfoMutex);

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : hifb_refresh_0buf_3D
* description  : CNcomment: 单buffer刷新 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_refresh_0buf_3D(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 BufferSize = 0;
    HI_ULONG StereoLockFlag = 0;
    HIFB_BLIT_OPT_S stBlitOpt;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    /**<--config 3D surface par >**/
    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);
    pstPar->st3DInfo.st3DSurface.enFmt     = pstCanvasBuf->stCanvas.enFmt;
    pstPar->st3DInfo.st3DSurface.u32Pitch  = pstCanvasBuf->stCanvas.u32Pitch;
    pstPar->st3DInfo.st3DSurface.u32Width  = pstCanvasBuf->stCanvas.u32Width;
    pstPar->st3DInfo.st3DSurface.u32Height = pstCanvasBuf->stCanvas .u32Height;

    BufferSize = HI_HIFB_GetMemSize(pstCanvasBuf->stCanvas.u32Pitch,pstCanvasBuf->stCanvas.u32Height);
    HIFB_CHECK_EQUAL_RETURN(BufferSize, 0, HI_FAILURE);

    Ret = wait_event_interruptible_timeout(pstPar->st3DInfo.WaiteFinishFreeStereoMemMutex,
                                              (HI_FALSE == pstPar->st3DInfo.BegFreeStereoMem),
                                              CONFIG_HIFB_STEREO_WAITE_TIME);
    HI_UNUSED(Ret);

    DRV_HIFB_Lock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
    /** IsStereo and BegUpStereoInfo should in one lock**/
    if (HI_FALSE == pstPar->st3DInfo.IsStereo)
    {
        DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
        return HI_SUCCESS;
    }
    pstPar->st3DInfo.BegUpStereoInfo = HI_TRUE;
    DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);

    /**<--alloc stereo buffer >**/
    Ret = HIFB_OSR_ReAllocStereoBuf(u32LayerId, pstCanvasBuf->stCanvas.u32Pitch, BufferSize);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return Ret;
    }

    /**<--config 3D surface par, user display buffer0 >**/
    pstPar->st3DInfo.st3DSurface.u32PhyAddr= pstPar->st3DInfo.u32DisplayAddr[0];

    /**<--config 3D buffer >**/
    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    stBlitOpt.bScale = HI_TRUE;
    stBlitOpt.bRegionDeflicker = HI_TRUE;

    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    DRV_HIFB_UpStereoData(u32LayerId, pstCanvasBuf, &stBlitOpt);

    pstPar->stRunInfo.bModifying = HI_TRUE;
       pstPar->stRunInfo.CurScreenAddr = pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart;
       pstPar->stDispInfo.stUserBuffer.stCanvas.u32Pitch = pstCanvasBuf->stCanvas.u32Pitch;
       pstPar->stDispInfo.stUserBuffer.stCanvas.enFmt = pstCanvasBuf->stCanvas.enFmt;
       hifb_disp_setdispsize(u32LayerId,pstCanvasBuf->stCanvas.u32Width,pstCanvasBuf->stCanvas.u32Height);

       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FMT;
       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
       pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    DRV_HIFB_WaitVBlank(u32LayerId);

    DRV_HIFB_Lock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
    /** can relese stereo memory **/
    pstPar->st3DInfo.BegUpStereoInfo = HI_FALSE;
    DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);

    wake_up_interruptible(&pstPar->st3DInfo.WaiteFinishUpStereoInfoMutex);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : hifb_refresh_1buf_3D
* description   : CNcomment: 双buffer刷新 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 hifb_refresh_1buf_3D(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HIFB_BLIT_OPT_S stBlitOpt;
    HIFB_OSD_DATA_S stOsdData;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride = 0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetOSDData(u32LayerId, &stOsdData);

    if ((stOsdData.u32RegPhyAddr != pstPar->stDispInfo.u32DisplayAddr[0]) && (pstPar->stDispInfo.u32DisplayAddr[0]))
    {
        pstPar->stRunInfo.bModifying = HI_TRUE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
        pstPar->stRunInfo.CurScreenAddr = pstPar->stDispInfo.u32DisplayAddr[0];

        HIFB_CHECK_NULLPOINTER_RETURN(info->screen_base,HI_FAILURE);
        HIFB_CHECK_EQUAL_RETURN(info->fix.smem_len, 0, HI_FAILURE);
        HI_GFX_Memset(info->screen_base, 0x0, info->fix.smem_len);

        pstPar->stRunInfo.bModifying = HI_FALSE;
    }

    u32Stride = CONIFG_HIFB_GetMaxStride(pstPar->stExtendInfo.u32DisplayWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    HIFB_CHECK_EQUAL_RETURN(u32Stride, 0, HI_FAILURE);

    pstPar->st3DInfo.st3DSurface.enFmt     = pstPar->stExtendInfo.enColFmt;
    pstPar->st3DInfo.st3DSurface.u32Pitch  = u32Stride;
    pstPar->st3DInfo.st3DSurface.u32Width  = pstPar->stExtendInfo.u32DisplayWidth;
    pstPar->st3DInfo.st3DSurface.u32Height = pstPar->stExtendInfo.u32DisplayHeight;
    pstPar->st3DInfo.st3DSurface.u32PhyAddr= pstPar->st3DInfo.u32DisplayAddr[0];

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));

    stBlitOpt.bRegionDeflicker = HI_TRUE;
    stBlitOpt.bScale = HI_TRUE;
    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);
    DRV_HIFB_UpStereoData(u32LayerId, pstCanvasBuf, &stBlitOpt);

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : hifb_refresh_2buf_3D
* description   : CNcomment: 3 buffer刷新 异步，刷新不等更新完，允许丢帧 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 hifb_refresh_2buf_3D(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_U32 u32Index;
    unsigned long lockflag;
    HIFB_BUFFER_S stBackBuf;
    HIFB_BLIT_OPT_S stBlitOpt;
    HIFB_OSD_DATA_S stOsdData;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride   = 0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN((1 - u32Index), CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    HI_GFX_Memset(&stBackBuf, 0, sizeof(stBackBuf));

    stBlitOpt.bCallBack = HI_TRUE;
    stBlitOpt.pfnCallBack = (IntCallBack)DRV_HIFB_BlitFinishCallBack;
    stBlitOpt.pParam = &(pstPar->stBaseInfo.u32LayerID);

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&lockflag);
    pstPar->stRunInfo.bNeedFlip        = HI_FALSE;
    pstPar->stRunInfo.s32RefreshHandle = 0;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&lockflag);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetOSDData(u32LayerId, &stOsdData);

    u32Stride = CONIFG_HIFB_GetMaxStride(pstPar->stExtendInfo.u32DisplayWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    HIFB_CHECK_EQUAL_RETURN(u32Stride, 0, HI_FAILURE);

    pstPar->st3DInfo.st3DSurface.enFmt      = pstPar->stExtendInfo.enColFmt;
    pstPar->st3DInfo.st3DSurface.u32Pitch   = u32Stride;
    pstPar->st3DInfo.st3DSurface.u32Width   = pstPar->stExtendInfo.u32DisplayWidth;
    pstPar->st3DInfo.st3DSurface.u32Height  = pstPar->stExtendInfo.u32DisplayHeight;
    pstPar->st3DInfo.st3DSurface.u32PhyAddr = pstPar->st3DInfo.u32DisplayAddr[u32Index];

    HI_GFX_Memcpy(&stBackBuf.stCanvas, &pstPar->st3DInfo.st3DSurface, sizeof(HIFB_SURFACE_S));

    hifb_getupdate_rect(u32LayerId, pstCanvasBuf, &stBackBuf.UpdateRect);

    if (pstPar->stRunInfo.bFliped && (stOsdData.u32RegPhyAddr == pstPar->st3DInfo.u32DisplayAddr[1 - u32Index]))
    {
        hifb_backup_forebuf(u32LayerId, &stBackBuf);
        HI_GFX_Memset(&(pstPar->st3DInfo.st3DUpdateRect), 0, sizeof(HIFB_RECT));
        pstPar->stRunInfo.bFliped = HI_FALSE;
    }

    if ((pstPar->st3DInfo.st3DUpdateRect.w == 0) || (pstPar->st3DInfo.st3DUpdateRect.h == 0))
    {
        HI_GFX_Memcpy(&pstPar->st3DInfo.st3DUpdateRect, &stBackBuf.UpdateRect, sizeof(HIFB_RECT));
    }
    else
    {
        HIFB_UNITE_RECT(pstPar->st3DInfo.st3DUpdateRect, stBackBuf.UpdateRect);
    }

    stBlitOpt.bScale = HI_TRUE;
    stBlitOpt.bRegionDeflicker = HI_TRUE;
    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    DRV_HIFB_UpStereoData(u32LayerId, pstCanvasBuf, &stBlitOpt);

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : hifb_refresh_2buf_immediate_display_3D
* description : CNcomment: 3 buffer 同步，刷新等待更新完 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 hifb_refresh_2buf_immediate_display_3D(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf)
{
    HI_U32 u32Index = 0;
    unsigned long lockflag;
    HIFB_BUFFER_S stBackBuf;
    HIFB_BLIT_OPT_S stBlitOpt;
    HI_U32 u32Stride = 0;
    HI_U32 CmpStride   = 0;
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN((1 - u32Index), CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(pstCanvasBuf, HI_FAILURE);

    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
    HI_GFX_Memset(&stBackBuf, 0, sizeof(stBackBuf));

    stBlitOpt.bCallBack = HI_FALSE;
    stBlitOpt.pParam = &(pstPar->stBaseInfo.u32LayerID);

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&lockflag);
    pstPar->stRunInfo.bNeedFlip        = HI_FALSE;
    pstPar->stRunInfo.s32RefreshHandle = 0;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&lockflag);

    u32Stride = CONIFG_HIFB_GetMaxStride(pstPar->stExtendInfo.u32DisplayWidth,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    HIFB_CHECK_EQUAL_RETURN(u32Stride, 0, HI_FAILURE);

    pstPar->st3DInfo.st3DSurface.enFmt     = pstPar->stExtendInfo.enColFmt;
    pstPar->st3DInfo.st3DSurface.u32Pitch  = u32Stride;
    pstPar->st3DInfo.st3DSurface.u32Width  = pstPar->stExtendInfo.u32DisplayWidth;
    pstPar->st3DInfo.st3DSurface.u32Height = pstPar->stExtendInfo.u32DisplayHeight;
    pstPar->st3DInfo.st3DSurface.u32PhyAddr= pstPar->st3DInfo.u32DisplayAddr[u32Index];

    HI_GFX_Memcpy(&stBackBuf.stCanvas, &pstPar->st3DInfo.st3DSurface, sizeof(HIFB_SURFACE_S));

    hifb_getupdate_rect(u32LayerId, pstCanvasBuf, &stBackBuf.UpdateRect);

    hifb_backup_forebuf(u32LayerId, &stBackBuf);

    HI_GFX_Memcpy(&pstPar->st3DInfo.st3DUpdateRect, &stBackBuf.UpdateRect, sizeof(HIFB_RECT));

    stBlitOpt.bScale = HI_TRUE;
    stBlitOpt.bBlock = HI_TRUE;
    stBlitOpt.bRegionDeflicker = HI_TRUE;
    if (pstPar->stBaseInfo.enAntiflickerMode == HIFB_ANTIFLICKER_TDE)
    {
        stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
    }

    DRV_HIFB_UpStereoData(u32LayerId, pstCanvasBuf, &stBlitOpt);

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.CurScreenAddr       = pstPar->st3DInfo.u32DisplayAddr[u32Index];
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    pstPar->stRunInfo.u32IndexForInt = 1 - u32Index;

    HI_GFX_Memcpy(&(pstPar->stDispInfo.stUserBuffer), pstCanvasBuf, sizeof(HIFB_BUFFER_S));

    DRV_HIFB_WaitVBlank(u32LayerId);

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func         : hifb_refresh
* description  : CNcomment: 刷新 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 hifb_refresh(HI_U32 u32LayerId, HIFB_BUFFER_S *pstCanvasBuf, HIFB_LAYER_BUF_E enBufMode)
{
    HI_S32 Ret = HI_FAILURE;
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (par->st3DInfo.IsStereo)
    {
        switch (enBufMode)
        {
            case HIFB_LAYER_BUF_DOUBLE:
                Ret = hifb_refresh_2buf_3D(u32LayerId, pstCanvasBuf);
                break;
            case HIFB_LAYER_BUF_ONE:
                Ret = hifb_refresh_1buf_3D(u32LayerId, pstCanvasBuf);
                break;
            case HIFB_LAYER_BUF_NONE:
               Ret = hifb_refresh_0buf_3D(u32LayerId, pstCanvasBuf);
               break;
            case HIFB_LAYER_BUF_DOUBLE_IMMEDIATE:
                Ret = hifb_refresh_2buf_immediate_display_3D(u32LayerId, pstCanvasBuf);
                break;
            default:
                break;
        }
        return Ret;
    }
#endif
    switch (enBufMode)
    {
        case HIFB_LAYER_BUF_DOUBLE:
            Ret = hifb_refresh_2buf(u32LayerId, pstCanvasBuf);
            break;
        case HIFB_LAYER_BUF_ONE:
            Ret = hifb_refresh_1buf(u32LayerId, pstCanvasBuf);
            break;
        case HIFB_LAYER_BUF_NONE:
           Ret = hifb_refresh_0buf(u32LayerId, pstCanvasBuf);
           break;
        case HIFB_LAYER_BUF_DOUBLE_IMMEDIATE:
            Ret = hifb_refresh_2buf_immediate_display(u32LayerId, pstCanvasBuf);
            break;
        default:
            break;
    }

    return Ret;
}

static HI_S32 DRV_HIFB_Refresh(HIFB_PAR_S* par, HI_VOID __user *argp)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_BUFFER_S stCanvasBuf;

    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    if (copy_from_user(&stCanvasBuf, argp, sizeof(HIFB_BUFFER_S)))
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return -EFAULT;
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (   (par->stExtendInfo.enBufMode == HIFB_REFRESH_MODE_WITH_PANDISPLAY)
         &&((par->st3DInfo.st3DMemInfo.u32StereoMemStart != 0) && (par->st3DInfo.IsStereo)))
    {
        return hifb_refresh_panbuf(par->stBaseInfo.u32LayerID, &stCanvasBuf);
    }

    if (par->stExtendInfo.enBufMode == HIFB_REFRESH_MODE_WITH_PANDISPLAY)
    {
        return HI_FAILURE;
    }
#endif

    if ((0 == stCanvasBuf.stCanvas.u32Width) || (0 == stCanvasBuf.stCanvas.u32Height))
    {
        HIFB_ERROR("canvas buffer's width or height can't be zero.\n");
        return HI_FAILURE;
    }

    if (stCanvasBuf.stCanvas.enFmt >= HIFB_FMT_BUTT)
    {
        HIFB_ERROR("color format of canvas buffer unsupported.\n");
        return HI_FAILURE;
    }

    if (  (stCanvasBuf.UpdateRect.x >=  stCanvasBuf.stCanvas.u32Width)
        ||(stCanvasBuf.UpdateRect.y >= stCanvasBuf.stCanvas.u32Height)
        ||(stCanvasBuf.UpdateRect.w == 0) || (stCanvasBuf.UpdateRect.h == 0))
    {
        HIFB_ERROR("rect error: update rect:(%d,%d,%d,%d), canvas range:(%d,%d)\n",
                  stCanvasBuf.UpdateRect.x, stCanvasBuf.UpdateRect.y,
                  stCanvasBuf.UpdateRect.w, stCanvasBuf.UpdateRect.h,
                  stCanvasBuf.stCanvas.u32Width, stCanvasBuf.stCanvas.u32Height);
        return HI_FAILURE;
    }

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(stCanvasBuf.UpdateRect.w, stCanvasBuf.UpdateRect.x, HI_FAILURE);
    HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(stCanvasBuf.UpdateRect.x,stCanvasBuf.stCanvas.u32Width,HI_FAILURE);
    if (stCanvasBuf.UpdateRect.x + stCanvasBuf.UpdateRect.w > stCanvasBuf.stCanvas.u32Width)
    {
        stCanvasBuf.UpdateRect.w = stCanvasBuf.stCanvas.u32Width - stCanvasBuf.UpdateRect.x;
    }

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(stCanvasBuf.UpdateRect.h, stCanvasBuf.UpdateRect.y, HI_FAILURE);
    HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(stCanvasBuf.UpdateRect.y,stCanvasBuf.stCanvas.u32Height,HI_FAILURE);
    if (stCanvasBuf.UpdateRect.y + stCanvasBuf.UpdateRect.h > stCanvasBuf.stCanvas.u32Height)
    {
        stCanvasBuf.UpdateRect.h =  stCanvasBuf.stCanvas.u32Height - stCanvasBuf.UpdateRect.y;
    }

    if (par->stExtendInfo.enBufMode == HIFB_LAYER_BUF_NONE)
    {
        if ((stCanvasBuf.stCanvas.u32PhyAddr & 0xf) || (stCanvasBuf.stCanvas.u32Pitch & 0xf))
        {
            HIFB_ERROR("addr 0x%x or pitch: 0x%x is not 16 bytes align !\n",stCanvasBuf.stCanvas.u32PhyAddr, stCanvasBuf.stCanvas.u32Pitch);
            return HI_FAILURE;
        }
    }

    Ret = hifb_refresh(par->stBaseInfo.u32LayerID, &stCanvasBuf, par->stExtendInfo.enBufMode);

    return Ret;
}

static HI_S32 DRV_HIFB_SetLayerInfo(struct fb_info *info, HIFB_PAR_S* par, HI_VOID __user *argp)
{
    HI_S32 Ret   = HI_SUCCESS;
    HIFB_LAYER_INFO_S stLayerInfo;

    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    if (copy_from_user(&stLayerInfo, argp, sizeof(HIFB_LAYER_INFO_S)))
    {
       HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
       return -EFAULT;
    }

    Ret = hifb_set_canvasbufinfo(info, &stLayerInfo);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintFuncErr(hifb_set_canvasbufinfo, HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = HIFB_OSR_CheckWhetherMemSizeEnough(info,&stLayerInfo);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_CheckWhetherMemSizeEnough failed\n");
        return HI_FAILURE;
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
     if((stLayerInfo.u32Mask & HIFB_LAYERMASK_DISPSIZE) && par->st3DInfo.IsStereo)
     {
        HIFB_OSR_ClearUnUsedStereoBuf(info);
     }
#endif

    Ret = HIFB_OSR_CheckWhetherLayerSizeSupport(info, &stLayerInfo);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_CheckWhetherLayerSizeSupport failed\n");
        return HI_FAILURE;
    }

    Ret = HIFB_OSR_CheckWhetherLayerPosSupport(&stLayerInfo);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_CheckWhetherLayerPosSupport failed\n");
        return HI_FAILURE;
    }

    if ((stLayerInfo.u32Mask & HIFB_LAYERMASK_BMUL) && par->stExtendInfo.stCkey.bKeyEnable)
    {
       HIFB_ERROR("Colorkey and premul couldn't take effect at same time!\n");
       return HI_FAILURE;
    }

    par->stRunInfo.bModifying = HI_TRUE;

    if (stLayerInfo.u32Mask & HIFB_LAYERMASK_BMUL)
    {
        par->stBaseInfo.bPreMul = stLayerInfo.bPreMul;
        par->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_BMUL;
    }

    if (stLayerInfo.u32Mask & HIFB_LAYERMASK_BUFMODE)
    {
        hifb_buf_setbufmode(par->stBaseInfo.u32LayerID, stLayerInfo.BufMode);
    }

    if (stLayerInfo.u32Mask & HIFB_LAYERMASK_POS)
    {
        hifb_disp_setlayerpos(par->stBaseInfo.u32LayerID, stLayerInfo.s32XPos, stLayerInfo.s32YPos);
    }

    if (stLayerInfo.u32Mask & HIFB_LAYERMASK_ANTIFLICKER_MODE)
    {
        DRV_HIFB_SetAntiflickerLevel(par->stBaseInfo.u32LayerID, stLayerInfo.eAntiflickerLevel);
    }

    HIFB_OSR_CheckWhetherDispSizeChange(info,&stLayerInfo);

    par->stRunInfo.bModifying = HI_FALSE;

    return Ret;
}

static inline HI_S32 HIFB_OSR_CheckWhetherMemSizeEnough(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo)
{
     HI_U32 Stride   = 0;
     HI_U32 CmpStride   = 0;
     HI_U32 IsInputDataSizeHasChanged = 0x0;

     HIFB_CHECK_NULLPOINTER_RETURN(pstLayerInfo, HI_FAILURE);
     IsInputDataSizeHasChanged = (pstLayerInfo->u32Mask & HIFB_LAYERMASK_DISPSIZE);

     if (!IsInputDataSizeHasChanged)
     {
        return HI_SUCCESS;
     }

     Stride = CONIFG_HIFB_GetMaxStride(pstLayerInfo->u32DisplayWidth, info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
     HIFB_CHECK_EQUAL_RETURN(Stride, 0, HI_FAILURE);

     if (pstLayerInfo->u32DisplayWidth == 0 || pstLayerInfo->u32DisplayHeight == 0)
     {
         HIFB_ERROR("display witdh/height shouldn't be 0!\n");
         return HI_FAILURE;
     }

     if (HI_FAILURE == hifb_checkmem_enough(info, Stride, pstLayerInfo->u32DisplayHeight))
     {
         HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
         return HI_FAILURE;
     }

     return HI_SUCCESS;
}

static inline HI_S32 HIFB_OSR_CheckWhetherLayerSizeSupport(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo)
{
    HI_U32 LayerSize = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(pstLayerInfo, HI_FAILURE);
    if (HIFB_LAYERMASK_BUFMODE == (pstLayerInfo->u32Mask & HIFB_LAYERMASK_BUFMODE))
    {
       return HI_SUCCESS;
    }

    LayerSize = HI_HIFB_GetMemSize(info->fix.line_length,info->var.yres);
    HIFB_CHECK_EQUAL_RETURN(LayerSize, 0, HI_FAILURE);

    if (pstLayerInfo->BufMode == HIFB_LAYER_BUF_ONE)
    {
       LayerSize = 1 * LayerSize;
    }
    else if ((pstLayerInfo->BufMode == HIFB_LAYER_BUF_DOUBLE) || (pstLayerInfo->BufMode == HIFB_LAYER_BUF_DOUBLE_IMMEDIATE))
    {
       HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(LayerSize,2,HI_FAILURE);
       LayerSize = 2 * LayerSize;
    }
    else
    {
       LayerSize = 0 * LayerSize;
    }

    if (LayerSize > info->fix.smem_len)
    {
       HIFB_ERROR("No enough mem! layer real memory size:%d KBytes, expected:%d KBtyes\n",
                   info->fix.smem_len/1024,
                   LayerSize/1024);
       return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static inline HI_S32 HIFB_OSR_CheckWhetherLayerPosSupport(HIFB_LAYER_INFO_S *pstLayerInfo)
{
    HIFB_CHECK_NULLPOINTER_RETURN(pstLayerInfo, HI_FAILURE);
    if ((pstLayerInfo->u32Mask & HIFB_LAYERMASK_POS) && ((pstLayerInfo->s32XPos < 0) || (pstLayerInfo->s32YPos < 0)))
    {
       HIFB_ERROR("Pos err!\n");
       return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static inline HI_VOID HIFB_OSR_CheckWhetherDispSizeChange(struct fb_info *info, HIFB_LAYER_INFO_S *pstLayerInfo)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 IsInputDataSizeHasChanged = 0x0;
     HIFB_PAR_S *pstPar = NULL;

     HIFB_CHECK_NULLPOINTER_UNRETURN(info);
     pstPar = (HIFB_PAR_S *)info->par;
     HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

     HIFB_CHECK_NULLPOINTER_UNRETURN(pstLayerInfo);
     IsInputDataSizeHasChanged = (pstLayerInfo->u32Mask & HIFB_LAYERMASK_DISPSIZE);
     if (!IsInputDataSizeHasChanged)
     {
        return;
     }

     if ((pstLayerInfo->u32DisplayWidth > info->var.xres_virtual) || (pstLayerInfo->u32DisplayHeight > info->var.yres_virtual))
     {
          return;
     }

     Ret = hifb_disp_setdispsize(pstPar->stBaseInfo.u32LayerID, pstLayerInfo->u32DisplayWidth, pstLayerInfo->u32DisplayHeight);
     if (Ret == HI_SUCCESS)
     {
         info->var.xres = pstLayerInfo->u32DisplayWidth;
         info->var.yres = pstLayerInfo->u32DisplayHeight;
         hifb_assign_dispbuf(pstPar->stBaseInfo.u32LayerID);
     }

     hifb_refreshall(info);

     return;
}

static HI_S32 DRV_HIFB_RefreshUserBuffer(HI_U32 u32LayerId)
{
    HIFB_BUFFER_S stCanvas;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *info = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    if (pstPar->stDispInfo.stUserBuffer.stCanvas.u32PhyAddr)
    {/**<-- has user buffer >**/
        HI_GFX_Memset(&stCanvas, 0x0, sizeof(stCanvas));
        stCanvas = pstPar->stDispInfo.stUserBuffer;
        stCanvas.UpdateRect.x = 0;
        stCanvas.UpdateRect.y = 0;
        stCanvas.UpdateRect.w = stCanvas.stCanvas.u32Width;
        stCanvas.UpdateRect.h = stCanvas.stCanvas.u32Height;

        hifb_refresh(pstPar->stBaseInfo.u32LayerID, &stCanvas, pstPar->stExtendInfo.enBufMode);
    }
    else
    {/**<-- after open, change un stereo to stereo, now has not user buffer >**/
        pstPar->stRunInfo.bModifying = HI_TRUE;
        pstPar->stRunInfo.CurScreenAddr = info->fix.smem_start;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FMT;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
        pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
        pstPar->stRunInfo.bModifying = HI_FALSE;
    }

    return HI_SUCCESS;
}

static HI_S32 hifb_refreshall(struct fb_info *info)
{
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if (par->st3DInfo.IsStereo)
    {
        if (HIFB_REFRESH_MODE_WITH_PANDISPLAY == par->stExtendInfo.enBufMode)
        {
            DRV_HIFB_PanDisplay(&info->var, info);
        }

        if (HIFB_LAYER_BUF_NONE == par->stExtendInfo.enBufMode)
        {
            DRV_HIFB_RefreshUserBuffer(par->stBaseInfo.u32LayerID);
        }
    }
#endif

    if (HIFB_REFRESH_MODE_WITH_PANDISPLAY != par->stExtendInfo.enBufMode && HIFB_LAYER_BUF_NONE != par->stExtendInfo.enBufMode)
    {
        DRV_HIFB_RefreshUserBuffer(par->stBaseInfo.u32LayerID);
    }

    return HI_SUCCESS;
}


#ifdef CONFIG_COMPAT
static HI_S32 hifb_compat_ioctl(struct fb_info *info, HI_U32 cmd, unsigned long arg)
{
    struct fb_fix_screeninfo *fix = NULL;
    struct fb_fix_compat_screeninfo *fix32 = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_U32 VirMemStart = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    fix = &(info->fix);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    if (FBIOGET_FSCREENINFO_HIFB == cmd)
    {
         if (0 == arg)
         {
            HIFB_ERROR("input para error\n");
            return HI_FAILURE;
         }

         fix32 = compat_ptr(arg);
         HIFB_CHECK_NULLPOINTER_RETURN(fix32, HI_FAILURE);

         HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN(fix->mmio_start, HI_FAILURE);
         VirMemStart = (HI_U32)(unsigned long)fix->mmio_start;

         if (copy_to_user(&fix32->id, &(fix->id), sizeof(fix32->id)))
         {
             return -EFAULT;
         }

         if (copy_to_user(fix32->reserved, fix->reserved, sizeof(fix->reserved)))
         {
             return -EFAULT;
         }

         if (put_user(pstPar->u32SmemStartPhy, &(fix32->smem_start)))
         {
             return -EFAULT;
         }

         if (put_user(fix->smem_len, &(fix32->smem_len)))
         {
             return -EFAULT;
         }

         if (put_user(fix->type, &(fix32->type)))
         {
             return -EFAULT;
         }

         if (put_user(fix->type_aux,  &(fix32->type_aux)))
         {
             return -EFAULT;
         }

         if (put_user(fix->visual, &(fix32->visual)))
         {
             return -EFAULT;
         }

         if (put_user(fix->xpanstep, &(fix32->xpanstep)))
         {
             return -EFAULT;
         }

         if (put_user(fix->ypanstep, &(fix32->ypanstep)))
         {
             return -EFAULT;
         }

         if (put_user(fix->ywrapstep, &(fix32->ywrapstep)))
         {
             return -EFAULT;
         }

         if (put_user(fix->line_length, &(fix32->line_length)))
         {
             return -EFAULT;
         }

         if (put_user(VirMemStart,  &(fix32->mmio_start)))
         {
             return -EFAULT;
         }

         if (put_user(fix->mmio_len,  &(fix32->mmio_len)))
         {
             return -EFAULT;
         }

         if (put_user(fix->accel, &(fix32->accel)))
         {
             return -EFAULT;
         }

         if (put_user(fix->capabilities,    &(fix32->capabilities)))
         {
             return -EFAULT;
         }

         return HI_SUCCESS;
    }

    return hifb_ioctl(info, cmd, arg);
}
#endif

static HI_S32 hifb_ioctl(struct fb_info *info, HI_U32 cmd, unsigned long arg)
{
    HI_S32 s32Cnt = 0;
    HI_U8 u8Cmd = _IOC_NR(cmd);
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info,-EFAULT);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar,-EFAULT);

    s32Cnt = atomic_read(&pstPar->stBaseInfo.ref_count);
    if (s32Cnt <= 0)
    {
        HIFB_ERROR("hifb%d not open\n",pstPar->stBaseInfo.u32LayerID);
        return -EINVAL;
    }

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(pstPar->stBaseInfo.u32LayerID, HI_FAILURE);
    if (!gs_pstCapacity[pstPar->stBaseInfo.u32LayerID].bLayerSupported)
    {
        HIFB_ERROR("not supprot layer %d!\n", pstPar->stBaseInfo.u32LayerID);
        return HI_FAILURE;
    }

    if (FBIOGET_FSCREENINFO_HIFB == cmd)
    {
        return gs_DrvHifbCtlFunc[49].DrvHifbIoctlFunc(info,arg);
    }

    DRV_HIFB_CHECK_IOCTL_CMD(u8Cmd);
    DRV_HIFB_CHECK_IOCTL_NUM(gs_DrvHifbCtlNum[u8Cmd]);

    if (NULL == gs_DrvHifbCtlFunc[gs_DrvHifbCtlNum[u8Cmd]].DrvHifbIoctlFunc)
    {
        HIFB_ERROR("this cmd not support\n");
        return HI_FAILURE;
    }

    if (cmd != gs_DrvHifbCtlFunc[gs_DrvHifbCtlNum[u8Cmd]].Cmd)
    {
        HIFB_ERROR("this cmd not support\n");
        return HI_FAILURE;
    }

    return gs_DrvHifbCtlFunc[gs_DrvHifbCtlNum[u8Cmd]].DrvHifbIoctlFunc(info,arg);
}


static HI_S32 HIFB_OSR_GetColorKey(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_COLORKEY_S ck;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HI_GFX_Memset(&ck, 0x0, sizeof(ck));
    ck.bKeyEnable = par->stExtendInfo.stCkey.bKeyEnable;
    ck.u32Key = par->stExtendInfo.stCkey.u32Key;
    if (copy_to_user(argp, &ck, sizeof(HIFB_COLORKEY_S)))
    {
        HIFB_ERROR("HIFB_OSR_GetColorKey failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetColorKey(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *pstPar = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_COLORKEY_S ckey;
    HI_U32 RLen = 0, GLen = 0, BLen = 0;
    HI_U32 ROffset = 0, GOffset = 0, BOffset = 0;
    HI_U8 RMask = 0, GMask = 0, BMask = 0;
    HI_U8 RKey = 0, GKey = 0, BKey = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(pstPar->debug);

    if (copy_from_user(&ckey, argp, sizeof(HIFB_COLORKEY_S)))
    {
        HIFB_ERROR("HIFB_OSR_SetColorKey failure\n");
        return -EFAULT;
    }

    if (ckey.bKeyEnable && pstPar->stBaseInfo.bPreMul)
    {
        HIFB_ERROR("colorkey and premul couldn't take effect at the same time!\n");
        return HI_FAILURE;
    }

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stExtendInfo.stCkey.u32Key = ckey.u32Key;
    pstPar->stExtendInfo.stCkey.bKeyEnable = ckey.bKeyEnable;

    HIFB_CHECK_EQUAL_RETURN(info->var.bits_per_pixel, 0, HI_FAILURE);
    if (info->var.bits_per_pixel <= 8)
    {
        if (ckey.u32Key >= (1 << info->var.bits_per_pixel))
        {
            HIFB_ERROR("The key :%d is out of range the palette: %d!\n",ckey.u32Key, 1 << info->var.bits_per_pixel);
            return HI_FAILURE;
        }
        pstPar->stExtendInfo.stCkey.u8BlueMax  = pstPar->stExtendInfo.stCkey.u8BlueMin  = info->cmap.blue[ckey.u32Key];
        pstPar->stExtendInfo.stCkey.u8GreenMax = pstPar->stExtendInfo.stCkey.u8GreenMin = info->cmap.green[ckey.u32Key];
        pstPar->stExtendInfo.stCkey.u8RedMax   = pstPar->stExtendInfo.stCkey.u8RedMin   = info->cmap.red[ckey.u32Key];
    }
    else
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_ColorConvert(&info->var, &pstPar->stExtendInfo.stCkey);

        HIFB_CHECK_ARRAY_OVER_RETURN(pstPar->stExtendInfo.enColFmt, HIFB_MAX_PIXFMT_NUM, HI_FAILURE);
        RLen = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stRed.length;
        GLen = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stGreen.length;
        BLen = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stBlue.length;

        RMask  = (0xff >> (8 - RLen));
        GMask  = (0xff >> (8 - GLen));
        BMask  = (0xff >> (8 - BLen));

        ROffset = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stRed.offset;
        GOffset = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stGreen.offset;
        BOffset = s_stArgbBitField[pstPar->stExtendInfo.enColFmt].stBlue.offset;

        if (HIFB_FMT_ABGR8888 != pstPar->stExtendInfo.enColFmt)
        {
            RKey = (pstPar->stExtendInfo.stCkey.u32Key >> (BLen + GLen)) & (RMask);
            GKey = (pstPar->stExtendInfo.stCkey.u32Key >> (BLen)) & (GMask);
            BKey = (pstPar->stExtendInfo.stCkey.u32Key) & (BMask);
        }
        else
        {
            RKey = (pstPar->stExtendInfo.stCkey.u32Key >> ROffset) & (RMask);
            GKey = (pstPar->stExtendInfo.stCkey.u32Key >> GOffset) & (GMask);
            BKey = (pstPar->stExtendInfo.stCkey.u32Key >> BOffset) & (BMask);
        }

        /** add low bit with 0 value **/
        pstPar->stExtendInfo.stCkey.u8RedMin   = RKey << (8 - RLen);
        pstPar->stExtendInfo.stCkey.u8GreenMin = GKey << (8 - GLen);
        pstPar->stExtendInfo.stCkey.u8BlueMin  = BKey << (8 - BLen);

        /** add low bit with 1 value **/
        pstPar->stExtendInfo.stCkey.u8RedMax   = pstPar->stExtendInfo.stCkey.u8RedMin   | (0xff >> RLen);
        pstPar->stExtendInfo.stCkey.u8GreenMax = pstPar->stExtendInfo.stCkey.u8GreenMin | (0xff >> GLen);
        pstPar->stExtendInfo.stCkey.u8BlueMax  = pstPar->stExtendInfo.stCkey.u8BlueMin  | (0xff >> BLen);
    }

    pstPar->stExtendInfo.stCkey.u8RedMask   = 0xff;
    pstPar->stExtendInfo.stCkey.u8BlueMask  = 0xff;
    pstPar->stExtendInfo.stCkey.u8GreenMask = 0xff;

    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_COLORKEY;
    pstPar->stRunInfo.bModifying          = HI_FALSE;

    HI_GFX_UNF_FuncExit(pstPar->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetLayerAlpha(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_to_user(argp, &par->stExtendInfo.stAlpha, sizeof(HIFB_ALPHA_S)))
    {
        HIFB_ERROR("HIFB_OSR_GetLayerAlpha failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetLayerAlpha(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_ALPHA_S stAlpha = {0};

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&(par->stExtendInfo.stAlpha), argp, sizeof(HIFB_ALPHA_S)))
    {
        HIFB_ERROR("HIFB_OSR_SetLayerAlpha failure\n");
        return -EFAULT;
    }

    stAlpha = par->stExtendInfo.stAlpha;
    if (!par->stExtendInfo.stAlpha.bAlphaChannel)
    {
        stAlpha.u8GlobalAlpha |= 0xff;
        par->stExtendInfo.stAlpha.u8GlobalAlpha |= 0xff;
    }

    par->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_ALPHA;

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}


static HI_S32 HIFB_OSR_GetScreenOriginPos(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_to_user(argp, &par->stExtendInfo.stPos, sizeof(HIFB_POINT_S)))
    {
        HIFB_ERROR("HIFB_OSR_GetScreenOriginPos failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetScreenOriginPos(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_POINT_S origin;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&origin, argp, sizeof(HIFB_POINT_S)))
    {
        HIFB_ERROR("HIFB_OSR_SetScreenOriginPos failure\n");
        return -EFAULT;
    }

    if (par->stBaseInfo.u32LayerID != HIFB_LAYER_HD_3)
    {
         if (origin.s32XPos < 0 || origin.s32YPos < 0)
         {
             HIFB_ERROR("It's not supported to set start pos of layer to negative!\n");
             return HI_FAILURE;
         }
    }

    par->stRunInfo.bModifying = HI_TRUE;
    par->stExtendInfo.stPos.s32XPos = origin.s32XPos;
    par->stExtendInfo.stPos.s32YPos = origin.s32YPos;

    par->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    par->stRunInfo.bModifying = HI_FALSE;

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetDeFlicker(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_FAILURE;
}

static HI_S32 HIFB_OSR_SetDeFlicker(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_FAILURE;
}

static HI_S32 HIFB_OSR_GetVblank(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_FAILURE;
    HIFB_PAR_S *par = NULL;
    HI_UNUSED(arg);

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_WaitVBlank(par->stBaseInfo.u32LayerID);
    if (Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(HIFB_DRV_WaitVBlank,Ret);
        return -EPERM;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ShowLayer(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HI_BOOL bShow = HI_FALSE;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = copy_from_user(&bShow, argp, sizeof(HI_BOOL));
    if (Ret)
    {
        HI_GFX_LOG_PrintErrCode(Ret);
        return -EFAULT;
    }

    /* reset the same status */
    if (bShow == par->stExtendInfo.bShow)
    {
        HI_GFX_UNF_FuncExit(par->debug);
        return 0;
    }

    par->stRunInfo.bModifying          = HI_TRUE;
    par->stExtendInfo.bShow            = bShow;
    par->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_SHOW;
    par->stRunInfo.bModifying          = HI_FALSE;

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetLayerShowState(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_to_user(argp, &par->stExtendInfo.bShow, sizeof(HI_BOOL)))
    {
        HIFB_ERROR("HIFB_OSR_GetLayerShowState failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetCapablity(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(par->stBaseInfo.u32LayerID,-EFAULT);
    if (copy_to_user(argp, (HI_VOID *)&gs_pstCapacity[par->stBaseInfo.u32LayerID], sizeof(HIFB_CAPABILITY_S)))
    {
        HIFB_ERROR("FBIOGET_CAPABILITY_HIFB error\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetDecompress(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HI_FB_DECOMPRESS_SUPPORT
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HI_BOOL bDeComp = HI_FALSE;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&bDeComp, argp, sizeof(HI_BOOL)))
    {
        HIFB_ERROR("HIFB_OSR_SetDecompress failure\n");
        return -EFAULT;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetDeCmpSwitch(par->stBaseInfo.u32LayerID, bDeComp);

    par->bDeCompress = bDeComp;

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetLayerInfo(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = DRV_HIFB_SetLayerInfo(info, par, argp);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_SetLayerInfo failure\n");
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetLayerInfo(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_LAYER_INFO_S stLayerInfo = {0};

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    DRV_HIFB_WaitVBlank(par->stBaseInfo.u32LayerID);

    stLayerInfo.bPreMul           = par->stBaseInfo.bPreMul;
    stLayerInfo.BufMode           = par->stExtendInfo.enBufMode;
    stLayerInfo.eAntiflickerLevel = par->stBaseInfo.enAntiflickerLevel;
    stLayerInfo.s32XPos           = par->stExtendInfo.stPos.s32XPos;
    stLayerInfo.s32YPos           = par->stExtendInfo.stPos.s32YPos;
    stLayerInfo.u32DisplayWidth   = par->stExtendInfo.u32DisplayWidth;
    stLayerInfo.u32DisplayHeight  = par->stExtendInfo.u32DisplayHeight;
    stLayerInfo.u32ScreenWidth    = par->stExtendInfo.u32DisplayWidth;
    stLayerInfo.u32ScreenHeight   = par->stExtendInfo.u32DisplayHeight;

    if (copy_to_user(argp, &stLayerInfo, sizeof(HIFB_LAYER_INFO_S)))
    {
       HIFB_ERROR("HIFB_OSR_GetLayerInfo failure\n");
       return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetCanvasBuffer(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_to_user(argp, &(par->stDispInfo.stCanvasSur), sizeof(HIFB_SURFACE_S)))
    {
        HIFB_ERROR("HIFB_OSR_GetCanvasBuffer failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_RefreshLayer(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = DRV_HIFB_Refresh(par, argp);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_RefreshLayer failure\n");
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_WaiteRefreshFinish(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_UNUSED(arg);

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if ((par->stRunInfo.s32RefreshHandle) && (par->stExtendInfo.enBufMode != HIFB_LAYER_BUF_ONE))
    {
        Ret = g_stGfx2dCallBackFunction.HIFB_DRV_WaitForDone(par->stRunInfo.s32RefreshHandle, 1000);
    }

    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_WaiteRefreshFinish failure\n");
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetSteroFraming(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_FAILURE;
}

static HI_S32 HIFB_OSR_GetSteroFraming(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_FAILURE;
}

static HI_S32 HIFB_OSR_SetSteroMode(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetSteroMode(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetScreenSize(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    HIFB_ERROR("call HI_UNF_DISP_SetScreenOffset function substitute for this function\n");
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetScreenSize(struct fb_info *info, HI_ULONG arg)
{
    HIFB_SIZE_S stScreenSize = {0};
    HIFB_RECT stOutputRect = {0};
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerOutRect(par->stBaseInfo.u32LayerID, &stOutputRect);

    stScreenSize.u32Width = stOutputRect.w;
    stScreenSize.u32Height = stOutputRect.h;
    if (copy_to_user(argp, &stScreenSize, sizeof(HIFB_SIZE_S)))
    {
        HIFB_ERROR("HIFB_OSR_GetScreenSize failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetCompress(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetCompress(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ScrolltextCreate(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_SCROLLTEXT_CREATE_S stScrollText;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HI_GFX_Memset(&stScrollText, 0x0, sizeof(stScrollText));
    if (copy_from_user(&stScrollText, argp, sizeof(HIFB_SCROLLTEXT_CREATE_S)))
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextCreate failure\n");
        return -EFAULT;
    }

    if (stScrollText.stAttr.ePixelFmt >= HIFB_FMT_BUTT)
    {
        HIFB_ERROR("Invalid attributes.\n");
        return HI_FAILURE;
    }

    if (stScrollText.stAttr.stRect.w < 0 || stScrollText.stAttr.stRect.h < 0)
    {
        HIFB_ERROR("Invalid attributes.\n");
        return HI_FAILURE;
    }

    Ret = hifb_create_scrolltext(par->stBaseInfo.u32LayerID, &stScrollText);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextCreate failure\n");
        return -EFAULT;
    }

    if (copy_to_user(argp, &stScrollText, sizeof(HIFB_SCROLLTEXT_CREATE_S)))
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextCreate failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ScrolltextFill(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_SCROLLTEXT_DATA_S stScrollTextData;
    HIFB_SCROLLTEXT_DATA_64BITS_S stScrollText64BitsData;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HI_GFX_Memset(&stScrollTextData, 0x0, sizeof(stScrollTextData));
    HI_GFX_Memset(&stScrollText64BitsData, 0x0, sizeof(stScrollText64BitsData));
    if (copy_from_user(&stScrollText64BitsData, argp, sizeof(HIFB_SCROLLTEXT_DATA_64BITS_S)))
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextFill failure\n");
        return -EFAULT;
    }

    stScrollTextData.u32Handle  = stScrollText64BitsData.u32Handle;
    stScrollTextData.u32PhyAddr = stScrollText64BitsData.u32PhyAddr;
    stScrollTextData.pu8VirAddr = (HI_U8*)(unsigned long)stScrollText64BitsData.u64VirAddr;
    stScrollTextData.u32Stride  = stScrollText64BitsData.u32Stride;

    if ((HI_NULL == stScrollTextData.u32PhyAddr) && (HI_NULL == stScrollTextData.pu8VirAddr))
    {
        HIFB_ERROR("invalid usr data!\n");
        return -EFAULT;
    }

    Ret = hifb_fill_scrolltext(&stScrollTextData);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextFill failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ScrolltextPause(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = HIFB_OSR_SCROLLTEXT_Enable(HI_TRUE, arg);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextPause failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ScrolltextResume(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    Ret = HIFB_OSR_SCROLLTEXT_Enable(HI_FALSE, arg);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextResume failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
static inline HI_S32 HIFB_OSR_SCROLLTEXT_Enable(HI_BOOL bEnable, HI_ULONG arg)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 u32LayerId;
     HI_U32 u32ScrollTextID;
     HI_U32 u32Handle;
     HIFB_SCROLLTEXT_S *pstScrollText = NULL;
     HI_VOID __user *argp = (HI_VOID __user *)arg;

     HIFB_CHECK_NULLPOINTER_RETURN(argp, HI_FAILURE);
     if (copy_from_user(&u32Handle, argp, sizeof(HI_U32)))
     {
         HIFB_ERROR("HIFB_OSR_SCROLLTEXT_Enable failure\n");
         return HI_FAILURE;
     }

     Ret = hifb_parse_scrolltexthandle(u32Handle,&u32LayerId,&u32ScrollTextID);
     if (HI_SUCCESS != Ret)
     {
         HIFB_ERROR("invalid scrolltext handle!\n");
         return HI_FAILURE;
     }

     HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
     HIFB_CHECK_ARRAY_OVER_RETURN(u32ScrollTextID, SCROLLTEXT_NUM, HI_FAILURE);
     pstScrollText = &(s_stTextLayer[u32LayerId].stScrollText[u32ScrollTextID]);

     pstScrollText->bPause = bEnable;

     return HI_SUCCESS;
}
#endif

static HI_S32 HIFB_OSR_ScrolltextDestory(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HI_U32 u32LayerId, u32ScrollTextID, u32Handle;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(argp, -EFAULT);
    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&u32Handle, argp, sizeof(HI_U32)))
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextDestory failure\n");
        return -EFAULT;
    }

    Ret = hifb_parse_scrolltexthandle(u32Handle,&u32LayerId,&u32ScrollTextID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("invalid scrolltext handle!\n");
        return -EFAULT;
    }

    Ret = hifb_destroy_scrolltext(u32LayerId,u32ScrollTextID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_ScrolltextDestory failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetSteroDepth(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HI_S32 s32StereoDepth = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&s32StereoDepth, argp, sizeof(HI_S32)))
    {
        HIFB_ERROR("HIFB_OSR_SetSteroDepth failure\n");
        return -EFAULT;
    }

    if (!par->st3DInfo.IsStereo)
    {
        HIFB_ERROR("u need to set disp stereo mode first.\n");
        return HI_FAILURE;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetStereoDepth(par->stBaseInfo.u32LayerID, s32StereoDepth);

    par->st3DInfo.s32StereoDepth = s32StereoDepth;

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetSteroDepth(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (!par->st3DInfo.IsStereo)
    {
        HIFB_ERROR("u need to set disp stereo mode first.\n");
        return HI_FAILURE;
    }

    if (copy_to_user(argp, &(par->st3DInfo.s32StereoDepth), sizeof(HI_S32)))
    {
        HIFB_ERROR("HIFB_OSR_GetSteroDepth failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetLayerZorder(struct fb_info *info, HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_ZORDER_E enZorder;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&enZorder, argp, sizeof(HIFB_ZORDER_E)))
    {
        HIFB_ERROR("HIFB_OSR_SetLayerZorder failure\n");
        return -EFAULT;
    }

    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerPriority(par->stBaseInfo.u32LayerID, enZorder);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_SetLayerZorder failure\n");
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetLayerZorder(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HI_U32 u32Zorder = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerPriority(par->stBaseInfo.u32LayerID, &u32Zorder);
    if (copy_to_user(argp, &(u32Zorder), sizeof(HI_U32)))
    {
        HIFB_ERROR("HIFB_OSR_GetLayerZorder failure\n");
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_ReleaseLogo(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_UNUSED(arg);

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (0 == par->stBaseInfo.u32LayerID)
    {
       DRV_HIFB_CloseLogo(par->stBaseInfo.u32LayerID);
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_SetCompressionMode(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetCompressionMode(struct fb_info *info, HI_ULONG arg)
{
    HI_UNUSED(info);
    HI_UNUSED(arg);
    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_FenceRefresh(struct fb_info *info, HI_ULONG arg)
{
    HI_BOOL ResumeForPowerOff = HI_FALSE;
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (0 != par->stBaseInfo.u32LayerID)
    {
        HIFB_ERROR("+++++++fence refresh not support layer%d\n",par->stBaseInfo.u32LayerID);
        return HI_FAILURE;
    }

    if (HI_TRUE == par->bSuspendForPowerOff)
    {
       g_stDrvAdpCallBackFunction.HIFB_DRV_GetResumeForPowerOffStatus(par->stBaseInfo.u32LayerID, &ResumeForPowerOff);
       if (HI_TRUE == ResumeForPowerOff)
       {
          par->bSuspendForPowerOff = HI_FALSE;
       }
    }
    if (HI_TRUE == par->bSuspendForPowerOff)
    {/** if suspend should not refresh black ui, and can soon resume **/
       //return HI_SUCCESS;
    }

#ifdef CFG_HIFB_FENCE_SUPPORT
    Ret = DRV_HIFB_FenceRefresh(par, argp);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_FenceRefresh failure\n");
        return HI_FAILURE;
    }
#else
    Ret = DRV_HIFB_NoFenceRefresh(par, argp);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_OSR_FenceRefresh failure\n");
        return HI_FAILURE;
    }
#endif

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_GetSmemStartPhy(struct fb_info *info, HI_ULONG arg)
{
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_to_user(argp, &(par->u32SmemStartPhy), sizeof(HI_U32)))
    {
        HIFB_ERROR("HIFB_OSR_GetSmemStartPhy failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_FixScreenInfo(struct fb_info *info, HI_ULONG arg)
{
    struct fb_fix_screeninfo fix;
    HIFB_PAR_S *par = NULL;
    HI_VOID __user *argp = (HI_VOID __user *)arg;

    HIFB_CHECK_NULLPOINTER_RETURN(argp, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HI_GFX_Memcpy(&fix, &(info->fix), sizeof(fix));
#ifdef CONFIG_GFX_MMU_SUPPORT
    fix.smem_start = par->u32SmemStartPhy;
#endif
    if (copy_to_user(argp, &fix, sizeof(fix)))
    {
        HIFB_ERROR("HIFB_OSR_FixScreenInfo failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 HIFB_OSR_HwcGetLayerInfo(struct fb_info *info, HI_ULONG arg)
{
#ifdef CFG_HIFB_FENCE_SUPPORT
    HIFB_PAR_S *par = NULL;
    HI_U32 BufferIndex = 0;
    HI_U32 Stride = 0;
    HI_U32 CmpStride = 0;
    HI_VOID __user *argp = (HI_VOID __user *)arg;
    HIFB_HWC_LAYERINFO_S stLayerInfo = {0};
    HI_U32 BitsPerPixel = 0;

    HIFB_CHECK_NULLPOINTER_RETURN(info,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(argp,HI_FAILURE);

    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par,HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (copy_from_user(&stLayerInfo, argp, sizeof(HIFB_HWC_LAYERINFO_S)))
    {
       HIFB_ERROR("HIFB_OSR_HwcGetLayerInfo failure\n");
       return -EFAULT;
    }

    if ((HIFB_FMT_ABGR8888 == stLayerInfo.eFmt) || (HIFB_FMT_ARGB8888 == stLayerInfo.eFmt) || (HIFB_FMT_RGBA8888 == stLayerInfo.eFmt))
    {
        BitsPerPixel = 32;
    }
    else if ((HIFB_FMT_RGB888 == stLayerInfo.eFmt) || (HIFB_FMT_BGR888 == stLayerInfo.eFmt))
    {
        BitsPerPixel = 24;
    }
    else if ((HIFB_FMT_ABGR1555 == stLayerInfo.eFmt) || (HIFB_FMT_ARGB1555 == stLayerInfo.eFmt) || (HIFB_FMT_RGBA5551 == stLayerInfo.eFmt))
    {
        BitsPerPixel = 16;
    }
    else
    {
        HIFB_ERROR("HIFB_OSR_HwcGetLayerInfo failure\n");
        return -EFAULT;
    }

    Stride = CONIFG_HIFB_GetMaxStride(par->stExtendInfo.u32DisplayWidth,BitsPerPixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    stLayerInfo.u32NoCmpStride = Stride;
    stLayerInfo.u32Stride = CmpStride;

    for (BufferIndex = 0; (BufferIndex < HIFB_DISP_TIMELINE_NUM_MAX) && (BufferIndex < CONFIG_HIFB_LAYER_BUFFER_NUM_MAX); BufferIndex++)
    {
         stLayerInfo.bOutBufBusy[BufferIndex] = DRV_HIFB_GetBufState(BufferIndex);
    }

    if (copy_to_user(argp, &stLayerInfo, sizeof(stLayerInfo)))
    {
        HIFB_ERROR("HIFB_OSR_HwcGetLayerInfo failure\n");
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(par->debug);

#else
    HI_UNUSED(info);
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
/***************************************************************************
* func          : DRV_OSR_StereoCallBack
* description   : NA
                  CNcomment: 使用工作队列方式 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static HI_S32 DRV_OSR_StereoCallBack(HI_VOID * pParaml,HI_VOID * pParamr)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 LayerId = 0,BufferSize = 0,CompressStride = 0, UnCompressStride = 0;
    HIFB_PAR_S *pstPar = NULL;
    HI_ULONG StereoLockFlag = 0;
    struct fb_info *info = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(pParamr, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pParaml, HI_FAILURE);

    LayerId = *((HI_U32*)pParaml);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, HI_FAILURE);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(pstPar->debug);

    pstPar->st3DInfo.StereoMode = *((HIFB_STEREO_MODE_E*)pParamr);

    if (HIFB_STEREO_MONO == pstPar->st3DInfo.StereoMode)
    {
        pstPar->st3DInfo.BegFreeStereoMem = HI_TRUE;
        HIFB_OSR_FreeStereoBuf(pstPar);
        pstPar->st3DInfo.BegFreeStereoMem = HI_FALSE;
        wake_up_interruptible(&pstPar->st3DInfo.WaiteFinishFreeStereoMemMutex);
    }
    else
    {
        if (HIFB_REFRESH_MODE_WITH_PANDISPLAY == pstPar->stExtendInfo.enBufMode)
        {
            UnCompressStride = CONIFG_HIFB_GetMaxStride(info->var.xres,info->var.bits_per_pixel,&CompressStride,CONFIG_HIFB_STRIDE_16ALIGN);
            HIFB_CHECK_EQUAL_RETURN(UnCompressStride, 0, HI_FAILURE);

            /**<-- one buffer need size >**/
            BufferSize = HI_HIFB_GetMemSize(UnCompressStride,info->var.yres) / 2;
            HIFB_CHECK_EQUAL_RETURN(BufferSize, 0, HI_FAILURE);

            /**<-- generally need two buffer >**/
            HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(BufferSize,pstPar->stRunInfo.StereoBufNum,HI_FAILURE);
            BufferSize *= pstPar->stRunInfo.StereoBufNum;
            Ret = HIFB_OSR_ReAllocStereoBuf(pstPar->stBaseInfo.u32LayerID, UnCompressStride, BufferSize);
            HIFB_CHECK_UNEQUAL_RETURN(Ret, HI_SUCCESS, HI_FAILURE);

            pstPar->st3DInfo.st3DSurface.u32Pitch = UnCompressStride;
        }
        DRV_HIFB_Lock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
        pstPar->st3DInfo.IsStereo = HI_TRUE;
        DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
    }

    if (   (0 == pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart)
        && (pstPar->st3DInfo.StereoMode == HIFB_STEREO_SIDEBYSIDE_HALF || pstPar->st3DInfo.StereoMode == HIFB_STEREO_TOPANDBOTTOM)
        && (HIFB_REFRESH_MODE_WITH_PANDISPLAY == pstPar->stExtendInfo.enBufMode))
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimMode(pstPar->stBaseInfo.u32LayerID, pstPar->st3DInfo.StereoMode, HIFB_STEREO_MONO);
    }
    else
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimMode(pstPar->stBaseInfo.u32LayerID, pstPar->st3DInfo.StereoMode, pstPar->st3DInfo.StereoMode);
    }

    hifb_assign_dispbuf(pstPar->stBaseInfo.u32LayerID);
    HIFB_OSR_ClearUnUsedStereoBuf(info);

    if (HIFB_REFRESH_MODE_WITH_PANDISPLAY == pstPar->stExtendInfo.enBufMode)
    {
        DRV_HIFB_PanDisplay(&info->var, info);
    }
    else
    {
        DRV_HIFB_RefreshUserBuffer(pstPar->stBaseInfo.u32LayerID);
    }

    HI_GFX_UNF_FuncExit(pstPar->debug);

    return HI_SUCCESS;
}
#endif

#ifdef CONFIG_GFX_MMU_SUPPORT
extern phys_addr_t hisi_iommu_domain_iova_to_phys(unsigned long iova);
extern struct sg_table *get_meminfo(u32 addr, u32 iommu, u32 *size, u32 *base);

static inline int hifb_valid_mmap_phys_addr_range(unsigned long pfn, size_t size)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
}

/***************************************************************************
* func          : HI_GFX_MapToUser
* description   :
                  CNcomment: 将内核态的内存映射到用户态使用 CNend\n
* retval        : HI_SUCCESS 成功
* retval        : HI_FAILURE 失败
* others:       : NA
****************************************************************************/
static inline HI_S32 hifb_smmu_map_to_user(HI_U32 u32PhyAddr,struct vm_area_struct *vma)
{
    HI_U32 Size = 0;
    HI_U32 u32Cnt  = 0;
    HI_U32 u32Len  = 0;
    HI_U32 pfn     = 0;
    HI_U32 BaseAddr = 0;
    struct sg_table  *pTable = NULL;
    struct scatterlist *sg   = NULL;
    struct page *page        = NULL;
    unsigned long addr = 0;

    if ((0 == u32PhyAddr) || (NULL == vma))
    {
        HIFB_ERROR("hifb_smmu_map_to_user failure\n");
        return HI_FAILURE;
    }

    pTable = get_meminfo(u32PhyAddr, 1, &Size, &BaseAddr);
    HI_UNUSED(BaseAddr);
    if (!pTable)
    {
        HIFB_ERROR("hifb_smmu_map_to_user failure\n");
        return HI_FAILURE;
    }

    if (Size != (vma->vm_end - vma->vm_start))
    {
        HIFB_ERROR("hifb_smmu_map_to_user failure\n");
        return -EINVAL;
    }

    /**<--check valid_mmap_phys_addr_range() >**/
    if (!hifb_valid_mmap_phys_addr_range(vma->vm_pgoff, Size))
    {
        HIFB_ERROR("hifb_smmu_map_to_user failure\n");
        return EINVAL;
    }

    addr = vma->vm_start;

    for_each_sg(pTable->sgl, sg, pTable->nents, u32Cnt)
    {
        page    = sg_page(sg);
        pfn     = page_to_pfn(page);
        u32Len  = PAGE_ALIGN(sg->length);
        if (!hifb_valid_mmap_phys_addr_range(vma->vm_pgoff, u32Len))
        {
            HIFB_ERROR("hifb_smmu_map_to_user failure\n");
            return HI_FAILURE;
        }
        remap_pfn_range(vma, addr, pfn, u32Len, vma->vm_page_prot);
        addr = addr + u32Len;
    }

    return HI_SUCCESS;
}

static HI_S32 hifb_map_mem_kernel_to_user(struct fb_info *info, struct vm_area_struct *vma)
{
    HI_U32 Size = 0;
    unsigned long iova = 0;
    unsigned long addr = 0;
    unsigned long phy_addr;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(vma, HI_FAILURE);

    iova = (unsigned long)info->fix.smem_start;
    addr = vma->vm_start;

    if (0 == info->fix.smem_start)
    {
       HIFB_ERROR("+++info->fix.smem_start is zero\n");
       return HI_FAILURE;
    }

    Size = vma->vm_end - vma->vm_start;
    if (info->fix.smem_len < Size)
    {
        HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);

    if (info->fix.smem_len == Size)
    {
        return hifb_smmu_map_to_user((HI_U32)info->fix.smem_start,vma);
    }

    while (addr < vma->vm_end)
    {
        phy_addr = (unsigned long)hisi_iommu_domain_iova_to_phys(iova);
        if (!phy_addr)
        {
            HIFB_ERROR("===func : %s line : %d error\n",__FUNCTION__,__LINE__);
            return HI_FAILURE;
        }

        if (!hifb_valid_mmap_phys_addr_range(vma->vm_pgoff, SZ_4K))
        {
            HIFB_ERROR("hifb_map_mem_kernel_to_user failure\n");
            return HI_FAILURE;
        }

        remap_pfn_range(vma, addr, __phys_to_pfn(phy_addr), SZ_4K, vma->vm_page_prot);
        addr = addr + SZ_4K;
        iova = iova + SZ_4K;
    }

    return HI_SUCCESS;
}
#endif

static HI_S32 DRV_HIFB_Close(struct fb_info *info, HI_S32 user)
{
    HIFB_PAR_S *par = NULL;
    HI_U32 s32Cnt = 0;
#ifdef CFG_HIFB_LOGO_SUPPORT
    HI_U32 StartTimeMs = 0;
    HI_U32 EndTimeMs = 0;
    HI_U32 TotalTimeMs = 0;
#endif

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    s32Cnt = atomic_read(&par->stBaseInfo.ref_count);
    if (s32Cnt <= 0)
    {
        HIFB_ERROR("DRV_HIFB_Close failure\n");
        return -EINVAL;
    }

    if (s32Cnt > 1)
    {
        atomic_dec(&par->stBaseInfo.ref_count);
        HI_GFX_UNF_FuncExit(par->debug);
        return HI_SUCCESS;
    }

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(par->stBaseInfo.u32LayerID, HI_FAILURE);

    g_stGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone(HI_TRUE);

    par->stExtendInfo.bShow = HI_FALSE;

    g_stDrvAdpCallBackFunction.HIFB_DRV_EnableLayer(par->stBaseInfo.u32LayerID, HI_FALSE);

    g_stDrvAdpCallBackFunction.HIFB_DRV_UpdataLayerReg(par->stBaseInfo.u32LayerID);

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetIntCallback(HIFB_CALLBACK_TYPE_VO,         HI_NULL, par->stBaseInfo.u32LayerID);
    g_stDrvAdpCallBackFunction.HIFB_DRV_SetIntCallback(HIFB_CALLBACK_TYPE_3DMode_CHG, HI_NULL, par->stBaseInfo.u32LayerID);

    DRV_HIFB_ReleaseScrollText(info);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_OSR_FreeStereoBuf(par);
    par->st3DInfo.StereoMode = HIFB_STEREO_MONO;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimMode(par->stBaseInfo.u32LayerID, HIFB_STEREO_MONO, HIFB_STEREO_MONO);

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimAddr(par->stBaseInfo.u32LayerID, HI_NULL);

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(par->stBaseInfo.u32LayerID, HI_NULL);
#endif

    g_stDrvAdpCallBackFunction.HIFB_DRV_CloseLayer(par->stBaseInfo.u32LayerID);

#ifdef CONFIG_GFX_PROC_SUPPORT
    DRV_HIFB_DestoryProc(par->stBaseInfo.u32LayerID);
#endif

#ifdef CFG_HIFB_FENCE_SUPPORT
    DRV_HIFB_FenceDInit(par);
#endif

    if ((NULL != info->screen_base) && (0 != info->fix.smem_len))
    {
       HI_GFX_Memset(info->screen_base,0x0,info->fix.smem_len);
    }

    atomic_dec(&par->stBaseInfo.ref_count);

#ifdef CFG_HIFB_LOGO_SUPPORT
    if (HIFB_LAYER_HD_0 == par->stBaseInfo.u32LayerID)
    {
        HI_GFX_GetTimeStamp(&StartTimeMs,NULL);
        while (1)
        {
            if ((HI_TRUE == par->FinishHdLogoWork) && (HI_TRUE == par->FinishSdLogoWork))
            {
                break;
            }

            HI_GFX_GetTimeStamp(&EndTimeMs,NULL);
            TotalTimeMs = EndTimeMs - StartTimeMs;
            if (TotalTimeMs >= 100)
            {
               break;
            }
            udelay(1);
        }
    }
#endif

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}


static inline HI_VOID DRV_HIFB_ReleaseScrollText(struct fb_info *info)
{
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_U32 ScrollTextCnt = 0;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(par->stBaseInfo.u32LayerID);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (HI_TRUE != s_stTextLayer[par->stBaseInfo.u32LayerID].bAvailable)
    {
        HI_GFX_UNF_FuncExit(par->debug);
        return;
    }

    for (ScrollTextCnt = 0; ScrollTextCnt < SCROLLTEXT_NUM; ScrollTextCnt++)
    {
        if (HI_TRUE != s_stTextLayer[par->stBaseInfo.u32LayerID].stScrollText[ScrollTextCnt].bAvailable)
        {
           continue;
        }
        hifb_freescrolltext_cachebuf(&(s_stTextLayer[par->stBaseInfo.u32LayerID].stScrollText[ScrollTextCnt]));
        HI_GFX_Memset(&s_stTextLayer[par->stBaseInfo.u32LayerID].stScrollText[ScrollTextCnt],0,sizeof(HIFB_SCROLLTEXT_S));
    }

    s_stTextLayer[par->stBaseInfo.u32LayerID].bAvailable = HI_FALSE;
    s_stTextLayer[par->stBaseInfo.u32LayerID].u32textnum = 0;
    s_stTextLayer[par->stBaseInfo.u32LayerID].u32ScrollTextId = 0;

    flush_work(&s_stTextLayer[par->stBaseInfo.u32LayerID].blitScrollTextWork);

    HI_GFX_UNF_FuncExit(par->debug);
#else
    HI_UNUSED(info);
#endif

    return;
}


static HI_S32 DRV_HIFB_SetCmpReg(unsigned regno, unsigned red, unsigned green,unsigned blue, unsigned transp, struct fb_info *info, HI_BOOL bUpdateReg)
{
    HI_U32 argb = 0x0;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    argb = ((transp & 0xff) << 24) | ((red & 0xff) << 16) | ((green & 0xff) << 8) | (blue & 0xff);

    if (regno > 255)
    {
        HIFB_ERROR("DRV_HIFB_SetCmpReg failure\n");
        return HI_FAILURE;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetColorReg(par->stBaseInfo.u32LayerID, regno, argb, bUpdateReg);

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}


static HI_S32 DRV_HIFB_SetCmapColor(unsigned regno, unsigned red, unsigned green, unsigned blue, unsigned transp, struct fb_info *info)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HIFB_CHECK_ARRAY_OVER_RETURN(regno, 256, HI_FAILURE);

    if ((1 == info->var.bits_per_pixel) || (2 == info->var.bits_per_pixel) || (4 == info->var.bits_per_pixel) || (8 == info->var.bits_per_pixel))
    {
         Ret = DRV_HIFB_SetCmpReg(regno, red, green, blue, transp, info, HI_TRUE);
         return Ret;
    }

    if ((16 == info->var.bits_per_pixel) && (8 == info->var.red.offset))
    {/** ACLUT88 **/
         Ret = DRV_HIFB_SetCmpReg(regno, red, green, blue, transp, info, HI_TRUE);
         return Ret;
    }

    switch (info->var.bits_per_pixel)
    {
        case 16:
            if (regno >= 16)
            {
                break;
            }
            if (info->var.red.offset == 10)
            {
                /* 1:5:5:5 */
                ((u32*) (info->pseudo_palette))[regno] =
                    ((red   & 0xf800) >>  1) |
                    ((green & 0xf800) >>  6) |
                    ((blue  & 0xf800) >> 11);
            }
            else
            {
                /* 0:5:6:5 */
                ((u32*) (info->pseudo_palette))[regno] =
                    ((red   & 0xf800)      ) |
                    ((green & 0xfc00) >>  5) |
                    ((blue  & 0xf800) >> 11);
            }
            break;
        case 24:
        case 32:
            red   >>= 8;
            green >>= 8;
            blue  >>= 8;
            transp >>= 8;
            ((u32 *)(info->pseudo_palette))[regno] =
                (red   << info->var.red.offset)   |
                (green << info->var.green.offset) |
                (blue  << info->var.blue.offset)  |
                (transp  << info->var.transp.offset) ;
            break;
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return Ret;
}

static HI_S32 hifb_setcolreg(unsigned regno, unsigned red, unsigned green,unsigned blue, unsigned transp, struct fb_info *info)
{
    return DRV_HIFB_SetCmapColor(regno, red, green, blue, transp, info);
}


/***************************************************************************************
* func          : hifb_setcmap
* description   : CNcomment: 设置调色板 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 hifb_setcmap(struct fb_cmap *cmap, struct fb_info *info)
{
    HI_S32 Index = 0, Start = 0;
    unsigned short *Red = NULL, *Green = NULL, *Blue = NULL, *Transp = NULL;
    unsigned short hRed = 0, hGreen= 0, hBlue= 0, hTransp = 0xffff;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(par->stBaseInfo.u32LayerID, -EINVAL);
    if (!gs_pstCapacity[par->stBaseInfo.u32LayerID].bCmap)
    {
        HIFB_ERROR("hifb_setcmap failure\n");
        return HI_FAILURE;
    }

    if (cmap->len > 256)
    {
       HIFB_ERROR("hifb_setcmap failure\n");
       return HI_FAILURE;
    }

    Red    = cmap->red;
    Green  = cmap->green;
    Blue   = cmap->blue;
    Transp = cmap->transp;
    Start  = cmap->start;

    if ((NULL == Red) || (NULL == Green) || (NULL == Blue))
    {
        return HI_FAILURE;
    }

    for (Index = 0; Index < cmap->len; Index++)
    {
        hRed   = *Red++;
        hGreen = *Green++;
        hBlue  = *Blue++;
        hTransp = (Transp != NULL)? (*Transp++) : (0xffff);
        DRV_HIFB_SetCmapColor(Start++, hRed, hGreen, hBlue, hTransp, info);
    }

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

#ifdef CFG_HIFB_SUPPORT_CONSOLE
static HI_VOID hifb_fillrect(struct fb_info *p, const struct fb_fillrect *rect)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(p);
    HIFB_CHECK_NULLPOINTER_UNRETURN(rect);
    cfb_fillrect(p, rect);
}
static HI_VOID hifb_copyarea(struct fb_info *p, const struct fb_copyarea *area)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(p);
    HIFB_CHECK_NULLPOINTER_UNRETURN(area);
    cfb_copyarea(p, area);
}
static HI_VOID hifb_imageblit(struct fb_info *p, const struct fb_image *image)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(p);
    HIFB_CHECK_NULLPOINTER_UNRETURN(image);
    cfb_imageblit(p, image);
}
#endif


#ifdef CONFIG_DMA_SHARED_BUFFER
static struct dma_buf * hifb_dmabuf_export(struct fb_info *info)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
     HIFB_PAR_S *pstPar = NULL;

     HIFB_CHECK_NULLPOINTER_RETURN(info, NULL);
     pstPar = (HIFB_PAR_S *)info->par;
     HIFB_CHECK_NULLPOINTER_RETURN(pstPar, NULL);

     switch(pstPar->stBaseInfo.u32LayerID)
     {
         case 0:
     #ifdef CONFIG_GFX_HI_FB0_SMMU_SUPPORT
            HIFB_ERROR("export dmabuf failure, should set smmu mem support through make menuconfig\n");
            return NULL;
     #else
            return hifb_memblock_export(pstPar->u32SmemStartPhy, info->fix.smem_len, 0);
     #endif
         case 1:
     #ifdef CONFIG_GFX_HI_FB1_SMMU_SUPPORT
            HIFB_ERROR("export dmabuf failure, should set smmu mem support through make menuconfig\n");
            return NULL;
     #else
            return hifb_memblock_export(pstPar->u32SmemStartPhy, info->fix.smem_len, 0);
     #endif
         case 2:
     #ifdef CONFIG_GFX_HI_FB2_SMMU_SUPPORT
            HIFB_ERROR("export dmabuf failure, should set smmu mem support through make menuconfig\n");
            return NULL;
     #else
            return hifb_memblock_export(pstPar->u32SmemStartPhy, info->fix.smem_len, 0);
     #endif
         default:
            HIFB_ERROR("export dmabuf failure, should set smmu mem support through make menuconfig\n");
            return NULL;
     }
#else
     return hifb_memblock_export(info->fix.smem_start, info->fix.smem_len, 0);
#endif
}
#endif

static HI_S32 DRV_HIFB_Open(struct fb_info *info, HI_S32 user)
{
    HI_S32 HifbDevOpenCnt = 0;
    HI_S32 Ret   = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
    par = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    HifbDevOpenCnt = atomic_read(&par->stBaseInfo.ref_count);
    atomic_inc(&par->stBaseInfo.ref_count);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(par->stBaseInfo.u32LayerID, HI_FAILURE);
    if (HI_TRUE != gs_pstCapacity[par->stBaseInfo.u32LayerID].bLayerSupported)
    {
        HIFB_ERROR("the fb%d layer is not supported!\n", par->stBaseInfo.u32LayerID);
        goto ERROR_EXIT;
    }

    if (0 != HifbDevOpenCnt)
    {
        HI_GFX_UNF_FuncExit(par->debug);
        return HI_SUCCESS;
    }

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_TdeOpen();
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("tde was not avaliable!\n");
        goto ERROR_EXIT;
    }

#ifdef CFG_HIFB_LOGO_SUPPORT
    if (HIFB_LAYER_HD_0 == par->stBaseInfo.u32LayerID)
    {/** if not open fb0 first, you should clear logo to release logo **/
        DRV_HIFB_ResetLogoState();
        DRV_HIFB_WhetherHasLogo();
        DRV_HIFB_GetLogoData(par->stBaseInfo.u32LayerID);
    }
#endif

    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_OpenLayer(par->stBaseInfo.u32LayerID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("failed to open layer%d !\n", par->stBaseInfo.u32LayerID);
        goto ERROR_EXIT;
    }

#ifdef CFG_HIFB_FENCE_SUPPORT
    Ret = DRV_HIFB_FenceInit(par);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("DRV_HIFB_FenceInit failure\n");
        goto ERROR_EXIT;
    }
#endif

    Ret = DRV_HIFB_InitLayerInfo(par->stBaseInfo.u32LayerID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("hifb layer init failed\n");
        goto ERROR_EXIT;
    }

#ifdef CFG_HIFB_LOGO_SUPPORT
    if (HIFB_LAYER_HD_0 == par->stBaseInfo.u32LayerID)
    {/** if not open fb0 first, you should clear logo to release logo **/
        DRV_HIFB_GetBaseData(par->stBaseInfo.u32LayerID);
    }
#endif

    Ret = DRV_HIFB_GetLayerBufferInfo(par->stBaseInfo.u32LayerID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("DRV_HIFB_GetLayerBufferInfo failed\n");
        goto ERROR_EXIT;
    }

    par->stRunInfo.LastScreenAddr = 0;
    par->stRunInfo.CurScreenAddr  = info->fix.smem_start;
    par->st3DInfo.u32rightEyeAddr = par->stRunInfo.CurScreenAddr;
    par->stRunInfo.u32IndexForInt = 0;
    DRV_HIFB_SetDisplayBuffer(par->stBaseInfo.u32LayerID);

#ifdef CFG_HIFB_LOGO_SUPPORT
    if (HIFB_LAYER_HD_0 == par->stBaseInfo.u32LayerID)
    {/** if not open fb0 first, you should clear logo to release logo **/
        DRV_HIFB_LogoToApp(par->stBaseInfo.u32LayerID);
    }
#endif

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerStride (par->stBaseInfo.u32LayerID, info->fix.line_length);

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(par->stBaseInfo.u32LayerID, info->fix.smem_start);

    Ret = DRV_HIFB_RegisterCallBackFunction(par->stBaseInfo.u32LayerID);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("register callback function failed\n");
        goto ERROR_EXIT;
    }

#ifdef CONFIG_GFX_PROC_SUPPORT
    DRV_HIFB_CreateProc(par->stBaseInfo.u32LayerID);
#endif

    par->stExtendInfo.bShow = HI_TRUE;
    par->bVblank = HI_TRUE;

    g_stDrvAdpCallBackFunction.HIFB_DRV_EnableLayer(par->stBaseInfo.u32LayerID, HI_TRUE);

#ifdef CFG_HIFB_LOGO_SUPPORT
    if (HIFB_LAYER_HD_0 == par->stBaseInfo.u32LayerID)
    {/** if not open fb0 first, you should clear logo to release logo **/
        DRV_HIFB_CloseLogo(HIFB_LAYER_HD_0);
    }
#endif

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;

ERROR_EXIT:

    DRV_HIFB_Close(info,user);

    HIFB_ERROR("hifb open failed\n");

    return HI_FAILURE;
}

static HI_S32 DRV_HIFB_InitLayerInfo(HI_U32 u32LayerID)
{
    struct fb_info *info        = NULL;
    HIFB_PAR_S *par             = NULL;
    HIFB_COLOR_FMT_E enColorFmt = HIFB_FMT_BUTT;
    HIFB_RECT stInRect   = {0};
    HI_U32 u32Stride     = 0;
    HI_U32 CmpStride     = 0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerID, HI_FAILURE);
    info = s_stLayer[u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par  = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(par->debug);

    if (IS_HD_LAYER(u32LayerID))
    {
        info->var = s_stDefVar[HIFB_LAYER_TYPE_HD];
    }
    else if (IS_SD_LAYER(u32LayerID))
    {
        info->var = s_stDefVar[HIFB_LAYER_TYPE_SD];
    }
    else if(IS_MINOR_HD_LAYER(u32LayerID))
    {
        info->var = s_stDefVar[HIFB_LAYER_TYPE_AD];
    }
    else
    {
        return HI_FAILURE;
    }

    HI_GFX_Memset(&(par->stDispInfo.stUserBuffer), 0, sizeof(par->stDispInfo.stUserBuffer));
    HI_GFX_Memset(&(par->stDispInfo.stCanvasSur),  0, sizeof(par->stDispInfo.stCanvasSur));
    HI_GFX_Memset(&(par->stExtendInfo.stCkey),     0, sizeof(par->stExtendInfo.stCkey));
    HI_GFX_Memset(&(par->stExtendInfo.stPos),      0, sizeof(par->stExtendInfo.stPos));

    par->stBaseInfo.bNeedAntiflicker = HI_FALSE;
    DRV_HIFB_SetAntiflickerLevel(par->stBaseInfo.u32LayerID, HIFB_LAYER_ANTIFLICKER_AUTO);

    par->stRunInfo.bModifying               = HI_FALSE;
    par->stRunInfo.u32ParamModifyMask       = 0;
    par->stExtendInfo.stAlpha.bAlphaEnable  = HI_TRUE;
    par->stExtendInfo.stAlpha.bAlphaChannel = HI_FALSE;
    par->stExtendInfo.stAlpha.u8Alpha0      = HIFB_ALPHA_TRANSPARENT;
    par->stExtendInfo.stAlpha.u8Alpha1      = HIFB_ALPHA_OPAQUE;
    par->stExtendInfo.stAlpha.u8GlobalAlpha = HIFB_ALPHA_OPAQUE;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAlpha(par->stBaseInfo.u32LayerID, &par->stExtendInfo.stAlpha);

    par->stExtendInfo.stCkey.u8RedMask   = 0xff;
    par->stExtendInfo.stCkey.u8GreenMask = 0xff;
    par->stExtendInfo.stCkey.u8BlueMask  = 0xff;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerKeyMask(par->stBaseInfo.u32LayerID, &par->stExtendInfo.stCkey);

    enColorFmt = hifb_getfmtbyargb(&info->var.red, &info->var.green, &info->var.blue, &info->var.transp, info->var.bits_per_pixel);
    par->stExtendInfo.enColFmt = enColorFmt;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(par->stBaseInfo.u32LayerID, par->stExtendInfo.enColFmt);

    u32Stride = CONIFG_HIFB_GetMaxStride(info->var.xres_virtual, info->var.bits_per_pixel, &CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    info->fix.line_length = u32Stride;

    par->stExtendInfo.u32DisplayWidth           = info->var.xres;
    par->stExtendInfo.u32DisplayHeight          = info->var.yres;

    par->st3DInfo.st3DSurface.u32Pitch          = info->fix.line_length;
    par->st3DInfo.st3DSurface.enFmt             = par->stExtendInfo.enColFmt;
    par->st3DInfo.st3DSurface.u32Width          = info->var.xres;
    par->st3DInfo.st3DSurface.u32Height         = info->var.yres;
    par->st3DInfo.st3DMemInfo.u32StereoMemLen   = HI_NULL;
    par->st3DInfo.st3DMemInfo.u32StereoMemStart = HI_NULL;

    stInRect.x = 0;
    stInRect.y = 0;
    stInRect.w = info->var.xres;
    stInRect.h = info->var.yres;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerInRect(par->stBaseInfo.u32LayerID, &stInRect);

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerStride(par->stBaseInfo.u32LayerID, info->fix.line_length);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    g_stDrvAdpCallBackFunction.HIFB_DRV_SetTriDimMode(par->stBaseInfo.u32LayerID, HIFB_STEREO_MONO, HIFB_STEREO_MONO);
#endif

    par->stExtendInfo.enBufMode = HIFB_REFRESH_MODE_WITH_PANDISPLAY;
    par->stRunInfo.u32BufNum    = CONFIG_HIFB_LAYER_BUFFER_MAX_NUM;
    par->stRunInfo.StereoBufNum = CONFIG_HIFB_STEREO_BUFFER_MAX_NUM;

    par->bPanFlag  = HI_FALSE;
    spin_lock_init(&par->stBaseInfo.lock);
    spin_lock_init(&par->st3DInfo.StereoLock);
    init_waitqueue_head(&par->st3DInfo.WaiteFinishUpStereoInfoMutex);
    init_waitqueue_head(&par->st3DInfo.WaiteFinishFreeStereoMemMutex);

    HI_GFX_UNF_FuncExit(par->debug);

    return HI_SUCCESS;
}

static HI_S32 DRV_HIFB_GetLayerBufferInfo(HI_U32 u32LayerID)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 MemStride = 0;
    HI_U32 CmpStride     = 0;
    HI_U32 LayerBufferNewSize = 0;
    HI_U32 LayerBufferOldSize = 0;
    struct fb_info *info = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerID, HI_FAILURE);
    info = s_stLayer[u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    MemStride = CONIFG_HIFB_GetMaxStride(info->var.xres_virtual,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);
    HIFB_CHECK_EQUAL_RETURN(MemStride, 0, HI_FAILURE);

    LayerBufferNewSize = HI_HIFB_GetMemSize(MemStride,info->var.yres_virtual);
    HIFB_CHECK_EQUAL_RETURN(LayerBufferNewSize, 0, HI_FAILURE);

    LayerBufferOldSize = info->fix.smem_len;

    if (LayerBufferOldSize >= LayerBufferNewSize)
    {
       return HI_SUCCESS;
    }

    Ret = DRV_HIFB_ReAllocLayerBuffer(u32LayerID,LayerBufferNewSize);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failed to ReAlloc mem\n");
        return HI_FAILURE;
    }

    info->fix.line_length = MemStride;
    info->fix.smem_len    = LayerBufferNewSize;

    return HI_SUCCESS;
}


static HI_VOID DRV_HIFB_SetDisplayBuffer(HI_U32 u32LayerId)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_U32 OneBufSize = 0;
    HI_U32 BufferNum  = 0;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    HI_GFX_UNF_FuncEnter(pstPar->debug);

    OneBufSize = HI_HIFB_GetMemSize(info->fix.line_length,info->var.yres);
    HIFB_CHECK_EQUAL_UNRETURN(0, OneBufSize);
    BufferNum = info->fix.smem_len / OneBufSize;

    if (CONFIG_HIFB_LAYER_0BUFFER == BufferNum)
    {
       return;
    }
    else if (CONFIG_HIFB_LAYER_1BUFFER == BufferNum)
    {
       pstPar->stDispInfo.u32DisplayAddr[0] = info->fix.smem_start;
       pstPar->stDispInfo.u32DisplayAddr[1] = info->fix.smem_start;
    }
    else
    {
       HI_GFX_CHECK_U64_ADDITION_REVERSAL_UNRETURN(info->fix.smem_start,OneBufSize);
       HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_UNRETURN((info->fix.smem_start + OneBufSize));
       pstPar->stDispInfo.u32DisplayAddr[0] = info->fix.smem_start;
       if (OneBufSize <= info->fix.smem_len / 2)
       {
          pstPar->stDispInfo.u32DisplayAddr[1] = info->fix.smem_start + OneBufSize;
       }
       else
       {
          pstPar->stDispInfo.u32DisplayAddr[1] = info->fix.smem_start;
       }
    }

    HI_GFX_UNF_FuncExit(pstPar->debug);

    return;
}


static inline HI_S32 DRV_HIFB_RegisterCallBackFunction(HI_U32 u32LayerId)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_SetIntCallback(HIFB_CALLBACK_TYPE_VO, (IntCallBack)hifb_vo_callback, u32LayerId);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("failed to set vo callback function, open layer%d failure\n", u32LayerId);
        return HI_FAILURE;
    }

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_SetIntCallback(HIFB_CALLBACK_TYPE_3DMode_CHG, (IntCallBack)DRV_OSR_StereoCallBack, u32LayerId);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("failed to set stereo mode change callback function, open layer%d failure\n", u32LayerId);
        return HI_FAILURE;
    }
#endif

#ifdef CFG_HIFB_FENCE_SUPPORT
    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_SetIntCallback(HIFB_CALLBACK_TYPE_FRAME_END, (IntCallBack)DRV_HIFB_FENCE_FrameEndCallBack, u32LayerId);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("failed to set frame end callback function, open layer%d failure\n", u32LayerId);
        return HI_FAILURE;
    }
#endif

   return HI_SUCCESS;
}


HI_U32 DRV_HIFB_GetPixDepth(HI_U32 BitsPerPixel)
{
     HI_U32 PerPixDepth = 0;

     if (BitsPerPixel <= 32)
     {
        PerPixDepth = (BitsPerPixel >= 8) ? (BitsPerPixel >> 3) : (BitsPerPixel / 8);
     }

     return PerPixDepth;
}


HI_VOID DRV_HIFB_WaitVBlank(HIFB_LAYER_ID_E enLayerId)
{
    g_stDrvAdpCallBackFunction.HIFB_DRV_WaitVBlank(enLayerId);
    return;
}

HI_S32 DRV_HIFB_UpStereoData(HIFB_LAYER_ID_E enLayerId, HIFB_BUFFER_S *pstSrcBuffer, HIFB_BLIT_OPT_S *pstBlitOpt)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;
    HI_S32 Ret = HI_SUCCESS;
    HI_ULONG LockFlag = 0;
    HIFB_BUFFER_S stDstBuf;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    info = s_stLayer[enLayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(pstPar->debug);

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&LockFlag);
      pstPar->stRunInfo.bNeedFlip        = HI_FALSE;
      pstPar->stRunInfo.s32RefreshHandle = 0;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockFlag);

    HI_GFX_Memcpy(&stDstBuf.stCanvas, &pstPar->st3DInfo.st3DSurface, sizeof(HIFB_SURFACE_S));

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  stDstBuf.stCanvas.u32Width, stDstBuf.stCanvas.u32Height, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }
    stDstBuf.stCanvas.u32Width  = (HIFB_STEREO_SIDEBYSIDE_HALF == pstPar->st3DInfo.StereoMode) ? (stDstBuf.stCanvas.u32Width >> 1) : (stDstBuf.stCanvas.u32Width);
    stDstBuf.stCanvas.u32Height = (HIFB_STEREO_TOPANDBOTTOM == pstPar->st3DInfo.StereoMode) ? (stDstBuf.stCanvas.u32Height >> 1) : (stDstBuf.stCanvas.u32Height);

    stDstBuf.UpdateRect.x = 0;
    stDstBuf.UpdateRect.y = 0;
    stDstBuf.UpdateRect.w = stDstBuf.stCanvas.u32Width;
    stDstBuf.UpdateRect.h = stDstBuf.stCanvas.u32Height;

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(pstSrcBuffer, &stDstBuf, pstBlitOpt, HI_TRUE);
    if (Ret <= 0)
    {
        HIFB_ERROR("tde blit error!\n");
        return HI_FAILURE;
    }

    pstPar->stRunInfo.s32RefreshHandle = Ret;

    HI_GFX_UNF_FuncExit(pstPar->debug);

#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(pstSrcBuffer);
    HI_UNUSED(pstBlitOpt);
#endif

    return HI_SUCCESS;
}

HI_S32 DRV_HIFB_BlitFinishCallBack(HI_VOID *pParaml, HI_VOID *pParamr)
{
    HI_U32 LayerId = 0;
    HIFB_PAR_S *pstPar = NULL;

#if defined(CFG_HIFB_FENCE_SUPPORT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
    HI_U32 u32Index = 0;
#endif

    HIFB_CHECK_NULLPOINTER_RETURN(pParaml, HI_FAILURE);
    LayerId = *(HI_U32 *)pParaml;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, HI_FAILURE);
    pstPar = (HIFB_PAR_S *)(s_stLayer[LayerId].pstInfo->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HI_GFX_UNF_FuncEnter(pstPar->debug);

#ifndef CFG_HIFB_FENCE_SUPPORT
    pstPar->stRunInfo.bNeedFlip = HI_TRUE;
#endif

#if defined(CFG_HIFB_FENCE_SUPPORT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
    if (HI_FALSE ==  pstPar->st3DInfo.IsStereo)
    {
        HI_GFX_UNF_FuncExit(pstPar->debug);
        return HI_SUCCESS;
    }

    u32Index = pstPar->stRunInfo.u32IndexForInt;
    HIFB_CHECK_ARRAY_OVER_RETURN(u32Index, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);

    pstPar->stRunInfo.CurScreenAddr  = pstPar->st3DInfo.u32DisplayAddr[u32Index];
    pstPar->st3DInfo.u32rightEyeAddr = pstPar->stRunInfo.CurScreenAddr;
    pstPar->stRunInfo.u32IndexForInt = (++u32Index) % pstPar->stRunInfo.StereoBufNum;

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

#endif

    HI_GFX_UNF_FuncExit(pstPar->debug);

    return HI_SUCCESS;
}

static HI_VOID HIFB_ShowCmd(HI_VOID)
{
#if 0
    HI_PRINT("0x%x   /**<-- FBIOGET_COLORKEY_HIFB                 >**/\n",FBIOGET_COLORKEY_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_COLORKEY_HIFB                 >**/\n",FBIOPUT_COLORKEY_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_ALPHA_HIFB                    >**/\n",FBIOGET_ALPHA_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_ALPHA_HIFB                    >**/\n",FBIOPUT_ALPHA_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_SCREEN_ORIGIN_HIFB            >**/\n",FBIOGET_SCREEN_ORIGIN_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_SCREEN_ORIGIN_HIFB            >**/\n",FBIOPUT_SCREEN_ORIGIN_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_DEFLICKER_HIFB                >**/\n",FBIOGET_DEFLICKER_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_DEFLICKER_HIFB                >**/\n",FBIOPUT_DEFLICKER_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_VBLANK_HIFB                   >**/\n",FBIOGET_VBLANK_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_SHOW_HIFB                     >**/\n",FBIOPUT_SHOW_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_SHOW_HIFB                     >**/\n",FBIOGET_SHOW_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOGET_CAPABILITY_HIFB               >**/\n",FBIOGET_CAPABILITY_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_DECOMPRESS_HIFB               >**/\n",FBIOPUT_DECOMPRESS_HIFB);
    HI_PRINT("0x%x   /**<-- FBIOPUT_LAYER_INFO                    >**/\n",FBIOPUT_LAYER_INFO);
    HI_PRINT("0x%x   /**<-- FBIOGET_LAYER_INFO                    >**/\n",FBIOGET_LAYER_INFO);
    HI_PRINT("0x%x   /**<-- FBIOGET_CANVAS_BUFFER                 >**/\n",FBIOGET_CANVAS_BUFFER);
    HI_PRINT("0x%x   /**<-- FBIO_REFRESH                          >**/\n",FBIO_REFRESH);
    HI_PRINT("0x%x   /**<-- FBIO_WAITFOR_FREFRESH_DONE            >**/\n",FBIO_WAITFOR_FREFRESH_DONE);
    HI_PRINT("0x%x   /**<-- FBIOPUT_ENCODER_PICTURE_FRAMING       >**/\n",FBIOPUT_ENCODER_PICTURE_FRAMING);
    HI_PRINT("0x%x   /**<-- FBIOGET_ENCODER_PICTURE_FRAMING       >**/\n",FBIOGET_ENCODER_PICTURE_FRAMING);
    HI_PRINT("0x%x   /**<-- FBIOPUT_STEREO_MODE                   >**/\n",FBIOPUT_STEREO_MODE);
    HI_PRINT("0x%x   /**<-- FBIOGET_STEREO_MODE                   >**/\n",FBIOGET_STEREO_MODE);
    HI_PRINT("0x%x   /**<-- FBIOPUT_SCREENSIZE                    >**/\n",FBIOPUT_SCREENSIZE);
    HI_PRINT("0x%x   /**<-- FBIOGET_SCREENSIZE                    >**/\n",FBIOGET_SCREENSIZE);
    HI_PRINT("0x%x   /**<-- FBIOPUT_COMPRESSION                   >**/\n",FBIOPUT_COMPRESSION);
    HI_PRINT("0x%x   /**<-- FBIOGET_COMPRESSION                   >**/\n",FBIOGET_COMPRESSION);
    HI_PRINT("0x%x   /**<-- FBIO_SCROLLTEXT_CREATE                >**/\n",FBIO_SCROLLTEXT_CREATE);
    HI_PRINT("0x%x   /**<-- FBIO_SCROLLTEXT_FILL                  >**/\n",FBIO_SCROLLTEXT_FILL);
    HI_PRINT("0x%x   /**<-- FBIO_SCROLLTEXT_PAUSE                 >**/\n",FBIO_SCROLLTEXT_PAUSE);
    HI_PRINT("0x%x   /**<-- FBIO_SCROLLTEXT_RESUME                >**/\n",FBIO_SCROLLTEXT_RESUME);
    HI_PRINT("0x%x   /**<-- FBIO_SCROLLTEXT_DESTORY               >**/\n",FBIO_SCROLLTEXT_DESTORY);
    HI_PRINT("0x%x   /**<-- FBIOPUT_STEREO_DEPTH                  >**/\n",FBIOPUT_STEREO_DEPTH);
    HI_PRINT("0x%x   /**<-- FBIOGET_STEREO_DEPTH                  >**/\n",FBIOGET_STEREO_DEPTH);
    HI_PRINT("0x%x   /**<-- FBIOPUT_ZORDER                        >**/\n",FBIOPUT_ZORDER);
    HI_PRINT("0x%x   /**<-- FBIOGET_ZORDER                        >**/\n",FBIOGET_ZORDER);
    HI_PRINT("0x%x   /**<-- FBIO_FREE_LOGO                        >**/\n",FBIO_FREE_LOGO);
    HI_PRINT("0x%x   /**<-- FBIOPUT_COMPRESSIONMODE               >**/\n",FBIOPUT_COMPRESSIONMODE);
    HI_PRINT("0x%x   /**<-- FBIOGET_COMPRESSIONMODE               >**/\n",FBIOGET_COMPRESSIONMODE);
    HI_PRINT("0x%x   /**<-- FBIO_HWC_REFRESH                      >**/\n",FBIO_HWC_REFRESH);
    HI_PRINT("0x%x   /**<-- FBIOGET_SMEMSTART_PHY                 >**/\n",FBIOGET_SMEMSTART_PHY);
    HI_PRINT("0x%x   /**<-- FBIO_HWC_GETLAYERINFO                 >**/\n",FBIO_HWC_GETLAYERINFO);
#endif
   return;
}

/***************************************************************************************
* func        : HIFB_DRV_ModInit
* description : CNcomment: insmod ko initialCNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 HIFB_DRV_ModInit(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32LayerId = HIFB_LAYER_HD_0;

    HI_GFX_Memset(&s_stLayer, 0x0, sizeof(s_stLayer));

    DRV_HIFB_GetAdpCallBackFunction(&g_stDrvAdpCallBackFunction);
    DRV_HIFB_GetGfx2dCallBackFunction(&g_stGfx2dCallBackFunction);

    Ret = g_stDrvAdpCallBackFunction.HIFB_DRV_GfxInit();
    if (HI_SUCCESS != Ret)
    {
        goto ERR_EXIT;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetGFXCap(&gs_pstCapacity);

    if (!strncmp("on", tc_wbc, 2))
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetTCFlag(HI_TRUE);
    }

    Ret = DRV_HIFB_ParseInsmodParameter();
    if (HI_SUCCESS != Ret)
    {
        goto ERR_EXIT;
    }

    for (u32LayerId = HIFB_LAYER_HD_0; u32LayerId < (HIFB_LAYER_HD_0 + CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT); u32LayerId++)
    {
        Ret = DRV_HIFB_RegisterFrameBuffer(u32LayerId);
        if (HI_SUCCESS != Ret)
        {
            goto ERR_EXIT;
        }

        Ret = DRV_HIFB_AllocLayerBuffer(u32LayerId,s_stLayer[u32LayerId].u32LayerSize);
        if (HI_SUCCESS != Ret)
        {
            continue;
        }

        Ret = DRV_HIFB_InitAllocCmapBuffer(u32LayerId);
        if (HI_SUCCESS != Ret)
        {
            continue;
        }

        #ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
            HI_GFX_Memset(&s_stTextLayer[u32LayerId], 0, sizeof(s_stTextLayer[u32LayerId]));
        #endif
    }

#ifndef HI_MCE_SUPPORT
    DRV_HIFB_ModInit_K();
#endif

#ifdef CFG_HIFB_LOGO_SUPPORT
    DRV_HIFB_ResetLogoState();
    DRV_HIFB_WhetherHasLogo();
#endif

    DRV_HIFB_PrintVersion(HI_TRUE);
    HIFB_ShowCmd();

    return HI_SUCCESS;

ERR_EXIT:

    HIFB_DRV_ModExit();

    return HI_FAILURE;

}

/***************************************************************************************
* func        : HIFB_DRV_ModExit
* description : CNcomment: rmmod ko dinitialCNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID HIFB_DRV_ModExit(HI_VOID)
{
    HI_U32 u32LayerId    = HIFB_LAYER_HD_0;
#ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
    HI_U32 ScrollTextNum = 0;
#endif

    g_stDrvAdpCallBackFunction.HIFB_DRV_GfxDeInit();

    for (u32LayerId = HIFB_LAYER_HD_0; u32LayerId <= HIFB_LAYER_SD_1; u32LayerId++)
    {
        DRV_HIFB_DInitAllocCmapBuffer(u32LayerId);
        DRV_HIFB_FreeLayerBuffer(u32LayerId);
        DRV_HIFB_UnRegisterFrameBuffer(u32LayerId);

        #ifdef CFG_HIFB_SCROLLTEXT_SUPPORT
           if (s_stTextLayer[u32LayerId].bAvailable)
           {
               continue;
           }

           for (ScrollTextNum = 0; ScrollTextNum < SCROLLTEXT_NUM; ScrollTextNum++)
           {
               if (s_stTextLayer[u32LayerId].stScrollText[ScrollTextNum].bAvailable)
               {
                   hifb_freescrolltext_cachebuf(&(s_stTextLayer[u32LayerId].stScrollText[ScrollTextNum]));
                   HI_GFX_Memset(&s_stTextLayer[u32LayerId].stScrollText[ScrollTextNum],0,sizeof(HIFB_SCROLLTEXT_S));
               }
           }

           s_stTextLayer[u32LayerId].bAvailable = HI_FALSE;
           s_stTextLayer[u32LayerId].u32textnum = 0;
           s_stTextLayer[u32LayerId].u32ScrollTextId = 0;
           flush_work(&s_stTextLayer[u32LayerId].blitScrollTextWork);
        #endif
    }

    g_stGfx2dCallBackFunction.HIFB_DRV_TdeClose();

#ifndef HI_MCE_SUPPORT
    DRV_HIFB_ModExit_K();
#endif

    DRV_HIFB_PrintVersion(HI_FALSE);

    return;
}

static HI_S32 DRV_HIFB_ParseInsmodParameter(HI_VOID)
{
    HI_CHAR *pInputStr = NULL;
    HI_CHAR number[4] = {0};
    HI_U32 LayerCnt = 0;
    HI_U32 u32LayerId = 0;

    if (video == HI_NULL)
    {
       /** stereo should need one buffer at least **/
       /** 3D至少需要一块显存buffer，否则在切换过程中重新分配内存会出现功能异常 **/
       for (u32LayerId = HIFB_LAYER_HD_0; u32LayerId <= HIFB_LAYER_SD_1; u32LayerId++)
       {
          s_stLayer[u32LayerId].u32LayerSize = (0 == gs_u32MenuconfigLayerSize[u32LayerId]) ?
                                               (CONFIG_GFX_HIFB_DEFAULT_SIZE) : (HI_HIFB_GetMemSize(gs_u32MenuconfigLayerSize[u32LayerId] * 1024,1));
       }

       return HI_SUCCESS;
    }

    pInputStr = strstr(video, "vram");
    while (pInputStr != NULL)
    {
        LayerCnt   = 0;
        pInputStr += 4;
        while (*pInputStr != '_')
        {
            if (LayerCnt > 1)
            {
                HIFB_ERROR("layer id is out of range!\n");
                return HI_FAILURE;
            }
            number[LayerCnt] = *pInputStr;
            LayerCnt++;
            pInputStr++;
        }
        number[LayerCnt] = '\0';

        u32LayerId = simple_strtoul(number, (char **)NULL, 10);
        HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);

        if (HI_FALSE == gs_pstCapacity[u32LayerId].bLayerSupported)
        {
            HIFB_ERROR("chip doesn't support layer %d!\n", u32LayerId);
            return HI_FAILURE;
        }

        pInputStr += sizeof("size") + LayerCnt;
        s_stLayer[u32LayerId].u32LayerSize = DRV_HIFB_GetVramSize(pInputStr);

        pInputStr = strstr(pInputStr, "vram");
    }

    return HI_SUCCESS;
}

static inline unsigned long DRV_HIFB_GetVramSize(HI_CHAR* pstr)
{
    HI_BOOL str_is_valid = HI_TRUE;
    unsigned long vram_size = 0;
    HI_CHAR* ptr = pstr;

    if ((ptr == NULL) || (*ptr == '\0'))
    {
        return 0;
    }

    while (*ptr != '\0')
    {
        if (*ptr == ',')
        {
            break;
        }
        else if ((!isdigit(*ptr)) && ('X' != *ptr) && ('x' != *ptr) && ((*ptr > 'f' && *ptr <= 'z') || (*ptr > 'F' && *ptr <= 'Z')))
        {
            str_is_valid = HI_FALSE;
            break;
        }
        ptr++;
    }

    if (HI_TRUE == str_is_valid)
    {
        vram_size = simple_strtoul(pstr, (char **)NULL, 0);
        vram_size = ((vram_size * 1024 + PAGE_SIZE - 1) & PAGE_MASK)/1024;
    }

    /** stereo should need one buffer at least **/
    /** 3D至少需要一块显存buffer，否则在切换过程中重新分配内存会出现功能异常 **/
    vram_size = (0 == vram_size) ? CONFIG_GFX_HIFB_DEFAULT_SIZE : HI_HIFB_GetMemSize(vram_size * 1024,1);

    return vram_size;
}

static inline HI_S32 DRV_HIFB_RegisterFrameBuffer(HI_U32 u32LayerId)
{
    HI_S32 Ret = 0;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *FbInfo = NULL;

    FbInfo = framebuffer_alloc( ( (sizeof(HIFB_PAR_S)) + (sizeof(HI_U32) * 256) ), NULL);
    if (NULL == FbInfo)
    {
        HIFB_ERROR("failed to malloc the fb_info!\n");
        return -ENOMEM;
    }

    pstPar = (HIFB_PAR_S *)(FbInfo->par);
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    s_stLayer[u32LayerId].pstInfo = FbInfo;

    FbInfo->fix = gs_stDefFix;
    FbInfo->fbops = &s_sthifbops;
    FbInfo->flags = FBINFO_FLAG_DEFAULT | FBINFO_HWACCEL_YPAN | FBINFO_HWACCEL_XPAN;
    FbInfo->pseudo_palette = (HI_U8*)(FbInfo->par) + sizeof(HIFB_PAR_S);
    FbInfo->fix.smem_len = s_stLayer[u32LayerId].u32LayerSize;

    Ret = register_framebuffer(FbInfo);
    if (Ret < 0)
    {
        HIFB_ERROR("failed to register_framebuffer!\n");
        framebuffer_release(FbInfo);
        s_stLayer[u32LayerId].pstInfo = NULL;
        return HI_FAILURE;
    }

    pstPar->bFrameBufferRegister = HI_TRUE;

#ifdef CFG_HIFB_FENCE_SUPPORT
    init_waitqueue_head(&pstPar->WaiteEndFenceRefresh);
#endif

    return HI_SUCCESS;
}

static inline HI_VOID DRV_HIFB_UnRegisterFrameBuffer(HI_U32 u32LayerId)
{
    HIFB_PAR_S *pstPar   = NULL;
    struct fb_info* FbInfo = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    FbInfo = s_stLayer[u32LayerId].pstInfo;
    if (NULL == FbInfo)
    {
       return;
    }

    pstPar = (HIFB_PAR_S *)FbInfo->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if (HI_TRUE == pstPar->bFrameBufferRegister)
    {
        unregister_framebuffer(FbInfo);
    }

    framebuffer_release(FbInfo);

    s_stLayer[u32LayerId].pstInfo = NULL;

    return;
}

static inline HI_S32 DRV_HIFB_ReAllocLayerBuffer(HI_U32 u32LayerId, HI_U32 BufSize)
{
    HI_S32 Ret = HI_SUCCESS;
    DRV_HIFB_FreeLayerBuffer(u32LayerId);
    Ret = DRV_HIFB_AllocLayerBuffer(u32LayerId,BufSize);
    return Ret;
}

static inline HI_S32 DRV_HIFB_AllocLayerBuffer(HI_U32 u32LayerId, HI_U32 BufSize)
{
    HI_CHAR LayerBufferName[256] = {'\0'};
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *FbInfo = NULL;
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_BOOL bSmmu = HI_FALSE;
#endif

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    FbInfo = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(FbInfo, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)FbInfo->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    pstPar->u32SmemStartPhy = 0;
    pstPar->stBaseInfo.u32LayerID = u32LayerId;
    pstPar->stDispInfo.stCanvasSur.u32PhyAddr = 0;

    snprintf(LayerBufferName, sizeof(LayerBufferName), "HIFB_Fb%d", u32LayerId);
    LayerBufferName[sizeof(LayerBufferName) - 1] = '\0';

#ifdef CONFIG_GFX_MMU_SUPPORT
    bSmmu = DRV_HIFB_CheckSmmuSupport(u32LayerId);
    if (HI_FALSE == bSmmu)
    {
        pstPar->u32SmemStartPhy = hifb_buf_allocmem(LayerBufferName, NULL, BufSize);
        FbInfo->fix.smem_start  = hifb_buf_map2smmu(pstPar->u32SmemStartPhy);
    }
    else
#endif
    {
        pstPar->u32SmemStartPhy = 0;
        FbInfo->fix.smem_start = hifb_buf_allocmem(LayerBufferName, "iommu", BufSize);
    }

    if (0 == FbInfo->fix.smem_start)
    {
       return HI_FAILURE;
    }

    FbInfo->screen_base = hifb_buf_map(FbInfo->fix.smem_start);
    if (HI_NULL == FbInfo->screen_base)
    {
       return HI_FAILURE;
    }

    HI_GFX_Memset(FbInfo->screen_base, 0x0, BufSize);

    return HI_SUCCESS;
}

static inline HI_VOID DRV_HIFB_FreeLayerBuffer(HI_U32 u32LayerId)
{
    struct fb_info* FbInfo = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    FbInfo = s_stLayer[u32LayerId].pstInfo;
    if (NULL == FbInfo)
    {
       return;
    }

    pstPar = (HIFB_PAR_S *)FbInfo->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    if (NULL != FbInfo->screen_base)
    {
        hifb_buf_ummap(FbInfo->screen_base);
        FbInfo->screen_base = NULL;
    }

    if (0 == FbInfo->fix.smem_start)
    {
       return;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (0 != pstPar->u32SmemStartPhy)
    {
        hifb_buf_unmapsmmu(FbInfo->fix.smem_start);
        hifb_buf_freemem(pstPar->u32SmemStartPhy,HI_FALSE);
    }
    else
    {
        hifb_buf_freemem(FbInfo->fix.smem_start,HI_TRUE);
    }
#else
    hifb_buf_freemem(FbInfo->fix.smem_start,HI_FALSE);
#endif

    pstPar->u32SmemStartPhy = 0;
    FbInfo->fix.smem_start  = 0;

    return;
}

static inline HI_S32 DRV_HIFB_InitAllocCmapBuffer(HI_U32 u32LayerId)
{
    HI_U32 CmapLen = 256;
    struct fb_info* FbInfo = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    FbInfo = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(FbInfo, HI_FAILURE);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(u32LayerId, HI_FAILURE);
    if (HI_TRUE != gs_pstCapacity[u32LayerId].bCmap)
    {
         return HI_SUCCESS;
    }

    if (fb_alloc_cmap(&FbInfo->cmap, CmapLen, 1) < 0)
    {
        HIFB_WARNING("fb_alloc_cmap failed!\n");
        FbInfo->cmap.len = 0;
        return HI_FAILURE;
    }

    FbInfo->cmap.len = CmapLen;

    return HI_SUCCESS;
}

static inline HI_VOID DRV_HIFB_DInitAllocCmapBuffer(HI_U32 u32LayerId)
{
    struct fb_cmap *cmap   = NULL;
    struct fb_info *FbInfo = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerId);
    FbInfo = s_stLayer[u32LayerId].pstInfo;
    if (NULL == FbInfo)
    {
       return;
    }

    cmap = &FbInfo->cmap;
    if (0 != cmap->len)
    {
        fb_dealloc_cmap(cmap);
    }

    return;
}

static inline HI_BOOL DRV_HIFB_CheckSmmuSupport(HI_U32 LayerId)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
      switch(LayerId)
      {
          case HIFB_LAYER_HD_0:
          {
             #ifdef CONFIG_GFX_HI_FB0_SMMU_SUPPORT
               return HI_TRUE;
             #else
               return HI_FALSE;
             #endif
          }
          case HIFB_LAYER_HD_1:
          {
             #ifdef CONFIG_GFX_HI_FB1_SMMU_SUPPORT
                return HI_TRUE;
             #else
                return HI_FALSE;
             #endif
          }
          case HIFB_LAYER_HD_2:
          {
             #ifdef CONFIG_GFX_HI_FB2_SMMU_SUPPORT
                return HI_TRUE;
             #else
                return HI_FALSE;
             #endif
          }
          default:
          {
             return HI_FALSE;
          }
      }
 #else
      return HI_FALSE;
 #endif
}

static inline HI_VOID DRV_HIFB_PrintVersion(HI_BOOL bLoad)
{
#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE) && defined(MODULE)
     if (HI_TRUE == bLoad)
     {
        GFX_Printk("Load hi_fb.ko success.\t\t(%s)\n", VERSION_STRING);
     }
     else
     {
        GFX_Printk("UnLoad hi_fb.ko success.\t(%s)\n", VERSION_STRING);
     }
#endif
     return;
}

HI_VOID DRV_HIFB_SetDecmpLayerInfo(HI_U32 LayerId)
{
#ifdef CFG_HIFB_FENCE_SUPPORT
    HI_U32 BufferId = 0;
    HI_BOOL bDispEnable = HI_FALSE;
#endif
    HI_U32 IsFenceRefresh = 0x0;
    HI_ULONG LockParFlag = 0;
    HI_U32 CmpStride   = 0;
    HI_U32 UnCmpStride = 0;
    HIFB_PAR_S *pstPar = NULL;
    HI_S32 Ret = HI_SUCCESS;

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE)
    HI_U32 HeadSize  = 0;
    HI_U32 ARHeadDdr = 0;
    HI_U32 ARDataDdr = 0;
    HI_U32 GBHeadDdr = 0;
    HI_U32 GBDataDdr = 0;
#endif

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    if ((NULL == s_stLayer[LayerId].pstInfo) || (NULL == s_stLayer[LayerId].pstInfo->par))
    {
        HIFB_ERROR("+++++++pstInfo or par is null\n");
        return;
    }
    pstPar = (HIFB_PAR_S *)s_stLayer[LayerId].pstInfo->par;

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&LockParFlag);

#ifdef CFG_HIFB_FENCE_SUPPORT
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetHaltDispStatus(pstPar->stBaseInfo.u32LayerID, &bDispEnable);
    while (pstPar->FenceRefreshCount > 0)
    {
        BufferId = DRV_HIFB_GetBufferId(pstPar->stBaseInfo.u32LayerID, pstPar->stRunInfo.CurScreenAddr);
        DRV_HIFB_IncRefreshTime(bDispEnable, BufferId);
        pstPar->FenceRefreshCount--;
    }
#endif

    IsFenceRefresh = (pstPar->stRunInfo.u32ParamModifyMask & HIFB_LAYER_PARAMODIFY_FENCE);
    if (!IsFenceRefresh)
    {
       pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_FENCE;
       DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockParFlag);
       return;
    }

    if (HI_TRUE == pstPar->st3DInfo.IsStereo)
    {
        pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_FENCE;
        DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockParFlag);
        return;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,pstPar->stExtendInfo.u32DisplayWidth,pstPar->stExtendInfo.u32DisplayHeight,0,0,0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return;
    }

    UnCmpStride = CONIFG_HIFB_GetMaxStride(pstPar->stExtendInfo.u32DisplayWidth,32,&CmpStride,CONFIG_HIFB_DECOMPRESS_DATA_STRIDE_ALIGN);

#ifdef CFG_HI_FB_DECOMPRESS_SUPPORT
    #ifndef CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE
    if (HI_TRUE == pstPar->bDeCompress)
    {
        DRV_HIFB_MEM_GetCmpHeadInfo(pstPar->stExtendInfo.u32DisplayHeight,&HeadSize,NULL);
        ARHeadDdr = pstPar->stRunInfo.CurScreenAddr;

        HI_GFX_CHECK_INT_ADDITION_REVERSAL_UNRETURN(ARHeadDdr,HeadSize);
        ARDataDdr = ARHeadDdr + HeadSize;
        HI_GFX_CHECK_INT_ADDITION_REVERSAL_UNRETURN(ARDataDdr,CmpStride * pstPar->stExtendInfo.u32DisplayHeight);
        GBHeadDdr = ARDataDdr + CmpStride * pstPar->stExtendInfo.u32DisplayHeight;
        HI_GFX_CHECK_INT_ADDITION_REVERSAL_UNRETURN(GBHeadDdr,HeadSize);
        GBDataDdr = GBHeadDdr + HeadSize;

        g_stDrvAdpCallBackFunction.HIFB_DRV_SetDeCmpDdrInfo(LayerId, ARHeadDdr,ARDataDdr,GBHeadDdr,GBDataDdr,CmpStride);
    }
    else
    #endif
    {
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerStride(LayerId, UnCmpStride);
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(LayerId, pstPar->stRunInfo.CurScreenAddr);
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetDeCmpSwitch (LayerId, pstPar->bDeCompress);
#else
    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerStride(LayerId, UnCmpStride);
    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerAddr(LayerId, pstPar->stRunInfo.CurScreenAddr);
#endif

    pstPar->stRunInfo.u32ParamModifyMask &= ~HIFB_LAYER_PARAMODIFY_FENCE;

    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockParFlag);

    return;
}


HI_U32 DRV_HIFB_GetBufferId(HI_U32 LayerId, HI_U32 DispAddr)
{
    HI_U32 buffer_id = 0;
#ifndef CFG_HIFB_FENCE_SUPPORT
    HI_UNUSED(LayerId);
    HI_UNUSED(DispAddr);
#else
    struct fb_info *info = NULL;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, 0);
    info = s_stLayer[LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info,0);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, 0);

    HIFB_CHECK_EQUAL_RETURN(0,DispAddr,0);
    HIFB_CHECK_EQUAL_RETURN(0,info->fix.line_length,0);

    if (info->fix.smem_start > DispAddr)
    {
        return 0;
    }

    if (DispAddr == pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart)
    {
        info->var.yoffset = 0;
    }
    else
    {
        info->var.yoffset = (DispAddr - info->fix.smem_start) / info->fix.line_length;
    }
    if (info->var.yoffset > (info->var.yres * CONFIG_HIFB_LAYER_BUFFER_MAX_NUM))
    {
        info->var.yoffset = 0;
    }

    HIFB_CHECK_EQUAL_RETURN(0,info->var.yres,0);
    buffer_id = info->var.yoffset / info->var.yres;
    if (buffer_id >= HIFB_DISP_TIMELINE_NUM_MAX)
    {
       buffer_id = 0;
    }
#endif
    return buffer_id;
}


HI_VOID DRV_HIFB_Lock(spinlock_t *pLock, HI_ULONG *pLockParFlag)
{
    spin_lock_irqsave(pLock,*pLockParFlag);
    return;
}

HI_VOID DRV_HIFB_UnLock(spinlock_t *pLock, HI_ULONG *pLockParFlag)
{
    spin_unlock_irqrestore(pLock,*pLockParFlag);
    return;
}

#if 0
HI_BOOL HI_DRV_HIFB_IfFrameRefresh(HI_VOID)
{
    HIFB_PAR_S *pstPar = s_stLayer[HIFB_LAYER_HD_0].pstInfo->par;
    if (NULL == pstPar)
    {
       return HI_FALSE;
    }

#ifdef CFG_HIFB_FENCE_SUPPORT
    if (HI_TRUE == pstPar->hifb_sync)
    {
        return DRV_HIFB_FENCE_IsRefresh();
    }
#endif

    return pstPar->stFrameInfo.bFrameHit;
}

/*****************************************************************************/
/*****************************************************************************/
#define HIFB_DRV_IsFrameHit  HI_DRV_HIFB_IfFrameRefresh
EXPORT_SYMBOL(HIFB_DRV_IsFrameHit);
#endif

#ifdef MODULE
module_init(HIFB_DRV_ModInit);
module_exit(HIFB_DRV_ModExit);
MODULE_LICENSE("GPL");
#endif
