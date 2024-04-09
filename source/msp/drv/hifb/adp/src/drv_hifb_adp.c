/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : drv_hifb_adp.c
Version         : Initial Draft
Author          : sdk
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                Author                  Modification
2018/01/01           sdk                    Created file
***************************************************************************************************/


/***************************** add include here****************************************************/
#ifndef HI_BUILD_IN_BOOT
    #include <linux/string.h>
    #include <linux/fb.h>
    #include <linux/time.h>
    #include <linux/version.h>
    #include <linux/module.h>
    #include <linux/types.h>
    #include <linux/errno.h>
    #include <linux/fcntl.h>
    #include <linux/mm.h>
    #include <linux/miscdevice.h>
    #include <linux/proc_fs.h>
    #include <linux/fs.h>
    #include <linux/slab.h>
    #include <linux/init.h>
    #include <linux/delay.h>
    #include <asm/uaccess.h>
    #include <asm/io.h>
    #include <linux/interrupt.h>
    #include <linux/ioport.h>
    #include <linux/string.h>
    #include <linux/workqueue.h>
    #include "hi_module.h"
    #include "hi_drv_module.h"
#else
    #include "hifb_debug.h"
    #include "hi_drv_pq.h"
    #include "hi_gfx_mem.h"
#endif


#include "drv_disp_ext.h"
#include "drv_hifb_hal.h"
#include "drv_hifb_adp.h"
#include "hi_drv_disp.h"
#include "drv_hifb_wbc.h"
#include "drv_pq_ext.h"

#ifdef CONFIG_GFX_PROC_SUPPORT
#include "drv_hifb_proc.h"
#endif

#include "drv_hifb_paracheck.h"
#include "drv_hifb_config.h"
#include "hi_gfx_sys_k.h"
#include "drv_hifb_common.h"

#ifdef CONFIG_HIFB_VERSION_1_0
#include "optm_alg_csc.h"
#include "optm_alg_gzme.h"
#include "optm_alg_gsharp.h"
#endif

/***************************** Macro Definition ***************************************************/
#ifndef HI_BUILD_IN_BOOT
static DISP_EXPORT_FUNC_S *ps_DispExportFuncs = HI_NULL;
#endif

#ifndef HI_BUILD_IN_BOOT
#define OPTM_HIFB_WVM_ENABLE                       1
#define OPTM_HIFB_GFXRR_ENABLE                     1
#define CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH     4096
#define CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH           3840
#define CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT          2160
#endif

#define DispWidth_HD                     1280
#define DispHeight_HD                    720
#define DispWidth_SD                     720
#define DispHeight_SD                    576
#define OPTM_COLOR_DEFVALUE              50
#define OPTM_EXTRACTLINE_RATIO           4
#define OPTM_EXTRACTLINE_WIDTH           1080

#ifdef CONFIG_HIFB_VERSION_1_0
#define OPTM_CURSOR_LAYERID              HIFB_LAYER_SD_1
#else
#define OPTM_CURSOR_LAYERID              HIFB_LAYER_HD_2
#endif

#define OPTM_GP_SUPPORT_MAXLAYERNUM      5
#define OPTM_GP0_GFX_COUNT               CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT
#define OPTM_GP1_GFX_COUNT               CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT
#define OPTM_GFXCLUT_LENGTH              256

#define HIFB_CHECK_LAYER_OPEN(enLayerId)  \
        do{ if (enLayerId >= HIFB_LAYER_ID_BUTT){\
              HIFB_ERROR("no suppout fb%d!\n",enLayerId);       \
              return HI_FAILURE;}\
            if (g_pstGfxDevice[enLayerId]->bOpened != HI_TRUE){ \
              HIFB_ERROR("Error! fb%d not open!\n",enLayerId);  \
              return HI_FAILURE;}\
        }while(0)

#define HIFB_CHECK_GP_OPEN(enGpId)  \
        do{ if (enGpId >= OPTM_GFX_GP_BUTT){\
              HIFB_ERROR("no suppout gp%d!\n",enGpId);       \
              return HI_FAILURE;}\
            if (HI_FALSE == g_pstGfxGPDevice[enGpId]->bOpen){\
              HIFB_ERROR("Error! gp%d not open!\n",enGpId);  \
              return HI_FAILURE;}\
        }while(0)

#ifndef HI_BUILD_IN_BOOT
#define STATIC static
#else
#define STATIC
#endif

/***************************** Structure Definition ***********************************************/
typedef enum tagOPTM_VDP_CONNECT_E
{
    OPTM_VDP_CONNECT_G3_DHD0 = 0,
    OPTM_VDP_CONNECT_G3_DHD1,
    OPTM_VDP_CONNECT_BUTT,
}OPTM_VDP_CONNECT_E;

typedef enum tagOPTM_WBC_BUFFER_STATUS_E
{
    OPTM_WBC_BUFFER_RELEASED = 0,
    OPTM_WBC_BUFFER_ACQUIRED
}OPTM_WBC_BUFFER_STATUS_E;


typedef struct tagOPTM_GFX_IRQ_S
{
    HI_VOID* pParam0;   /** layer id      **/
    HI_U32   u32Param1;
    IntCallBack pFunc;  /** irq function **/
#ifndef HI_BUILD_IN_BOOT
    spinlock_t FuncLock;
#endif
}OPTM_GFX_IRQ_S;

typedef struct tagOPTM_GFX_CALLBACK_S
{
    HI_U32 u32CTypeFlag;
    OPTM_GFX_IRQ_S stGfxIrq[HIFB_CALLBACK_TYPE_BUTT];
}OPTM_GFX_CALLBACK_S;

typedef struct tagOPTM_GP_IRQ_S
{
    HI_BOOL bRegistered[HI_DRV_DISP_C_TYPE_BUTT];
    OPTM_GFX_CALLBACK_S stGfxCallBack[OPTM_GP_SUPPORT_MAXLAYERNUM];
}OPTM_GP_IRQ_S;

/***************************** Global Variable declaration ****************************************/
static volatile HI_U32 *gs_Phyaddr = HI_NULL;
static HI_U32 gs_GFXInitFlag = OPTM_DISABLE;

#ifndef CONFIG_GFX_PQ
static OPTM_ALG_GZME_MEM_S gs_stGPZme;
#endif

HIFB_GFX_MODE_EN g_enOptmGfxWorkMode = HIFB_GFX_MODE_NORMAL;

OPTM_GFX_GP_S *g_pstGfxGPDevice[OPTM_GFX_GP_BUTT] = {NULL};
OPTM_GFX_LAYER_S *g_pstGfxDevice[OPTM_MAX_LOGIC_HIFB_LAYER] = {NULL};
HIFB_CAPABILITY_S *g_pstGfxCap[OPTM_MAX_LOGIC_HIFB_LAYER] = {NULL};

static OPTM_GP_IRQ_S *g_pstGfxGPIrq[OPTM_GFX_GP_BUTT] = {NULL};
extern OPTM_GFX_WBC_S g_stGfxWbc2;

#ifndef HI_BUILD_IN_BOOT
   static PQ_EXPORT_FUNC_S* gs_pstPqFuncs = HI_NULL;
   static HIFB_LAYER_ID_E gs_CallBackLayerId[HIFB_LAYER_ID_BUTT];
#endif

/***************************** API forward declarations *******************************************/
#ifdef OPTM_HIFB_WVM_ENABLE
static HI_VOID OPTM_GfxWVBCallBack(HI_U32 enLayerId);
#endif

#ifndef HI_BUILD_IN_BOOT
static HI_S32 OPTM_DispInfoUpdate(OPTM_VDP_LAYER_GP_E enGPId);
static HI_S32  OPTM_Distribute_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1);
static HI_VOID DRV_HIFB_ADP_FrameEndCallBack (HI_VOID* u32Param0, HI_VOID* u32Param1);
#endif

#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
static HI_S32  OPTM_GFX_SetStereoDepth(HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth);
#endif

static HI_S32 OPTM_GPRecovery(OPTM_GFX_GP_E enGPId);
static HI_S32 OPTM_GPSetCsc(OPTM_GFX_GP_E enGfxGpId, OPTM_GFX_CSC_PARA_S *pstCscPara, HI_BOOL bIsBGRIn);

#ifndef CONFIG_GFX_PQ
static OPTM_COLOR_SPACE_E OPTM_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc);
#else
static HI_PQ_GFX_COLOR_SPACE_E PQ_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc);
#endif

static inline OPTM_VDP_GFX_IFMT_E OPTM_ClutPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_RGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_XRGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline OPTM_VDP_GFX_IFMT_E OPTM_XYCbCrPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt);

#ifndef HI_BUILD_IN_BOOT
static inline HIFB_COLOR_FMT_E OPTM_ClutHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_RGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_XRGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HIFB_COLOR_FMT_E OPTM_XYCbCrHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt);
static inline HI_VOID HIFB_ADP_ReOpen(OPTM_GFX_GP_E enGpId);
static inline HI_VOID HIFB_ADP_ReClose(OPTM_GFX_GP_E enGpId);
static inline HI_VOID HIFB_ADP_DispSetting(OPTM_GFX_GP_E enGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo);
static inline HI_VOID HIFB_ADP_UpdataLayerInfo(HI_VOID* u32Param0, HI_VOID* u32Param1);
#endif

static inline HI_VOID HIFB_ADP_ResetLayerInRect(OPTM_GFX_GP_E enGpId);

#ifndef CONFIG_GFX_PQ
static inline HI_VOID HIFB_ADP_SetZme(OPTM_GFX_GP_E enGpId, HI_BOOL bGfxSharpen, OPTM_ALG_GZME_RTL_PARA_S *pstZmeRtlPara, OPTM_ALG_GDTI_RTL_PARA_S *pstDtiRtlPara);
#endif

static inline HI_S32 HIFB_ADP_SetLayerDataBigEndianFmt(HIFB_LAYER_ID_E enLayerId);
static inline HI_S32 HIFB_ADP_SetLayerDataLittleEndianFmt(HIFB_LAYER_ID_E enLayerId);

/***************************** API realization ****************************************************/
/***************************************************************************************
* func        : HIFB_PARA_CHECK_SUPPORT
* description : CNcomment: 判断输入参数是否支持 CNend\n
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 HIFB_PARA_CHECK_SUPPORT(HI_U32 Mask, HI_U32 Width, HI_U32 Height, HI_U32 Stride, HI_U32 Fmt, HI_U32 BitsPerPixel)
{
    if (Mask & HIFB_PARA_CHECK_FMT)
    {
    }

    if ((Mask & HIFB_PARA_CHECK_WIDTH) && (Width > CONFIG_HIFB_LAYER_MAXWIDTH))
    {
        HIFB_ERROR("Width = %d\n",Width);
        return HI_FAILURE;
    }

    if ((Mask & HIFB_PARA_CHECK_HEIGHT) && (Height > CONFIG_HIFB_LAYER_MAXHEIGHT))
    {
        HIFB_ERROR("Height = %d\n",Height);
        return HI_FAILURE;
    }

    if ((Mask & HIFB_PARA_CHECK_STRIDE) && (Stride > CONFIG_HIFB_LAYER_STRIDE))
    {
        HIFB_ERROR("Stride = %d\n",Stride);
        return HI_FAILURE;
    }

    if ((Mask & HIFB_PARA_CHECK_BITSPERPIXEL) && (BitsPerPixel > CONFIG_HIFB_LAYER_BITSPERPIX))
    {
        HIFB_ERROR("BitsPerPixel = %d\n",BitsPerPixel);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT
static HI_U32 OPTM_AlignUp(const HI_U32 x, const HI_U32 a)
{
    return (0 == a) ? (x) : ( (( x + (a - 1) ) / a ) * a);
}
#else

#define IO_ADDRESS(addr) (addr)

extern HI_S32 GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,
                                  const HI_DRV_DISP_OFFSET_S *stOffsetInfo,
                                  const HI_RECT_S *stFmtResolution,
                                  const HI_RECT_S *stPixelFmtResolution,
                                  HI_RECT_S *stToBeRevisedRect,
                                  HI_RECT_S *stRevisedRect);

/***************************************************************************************
* func         : OPTM_GpInitFromDisp
* description  : CNcomment: 初始化参数，参数来源于display  CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GpInitFromDisp(OPTM_GFX_GP_E enGPId, HI_BOOL Support4KLogo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_DRV_DISPLAY_E enDisp = HI_DRV_DISPLAY_0;
    HI_DISP_DISPLAY_INFO_S stInfo;

#ifndef CONFIG_GFX_PQ
    OPTM_COLOR_SPACE_E enGpCsc = OPTM_CS_BT709_YUV_LIMITED;
#else
    HI_PQ_GFX_COLOR_SPACE_E enGpCsc = PQ_GFX_CS_BUTT;
#endif

    HIFB_CHECK_GP_OPEN(enGPId);

    enDisp = (enGPId == OPTM_GFX_GP_0) ? (HI_DRV_DISPLAY_1) : (HI_DRV_DISPLAY_0);

    HI_GFX_Memset(&stInfo, 0, sizeof(stInfo));
    Ret = HI_DISP_GetDisplayInfo(enDisp, &stInfo);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    g_pstGfxGPDevice[enGPId]->bInterface = stInfo.bInterlace;

    GfxWinReviseOutRect(&stInfo.stVirtaulScreen,
                        &stInfo.stOffsetInfo,
                        &stInfo.stFmtResolution,
                        &stInfo.stPixelFmtResolution,
                        &stInfo.stVirtaulScreen,
                        &g_pstGfxGPDevice[enGPId]->stOutRect);

    if ((OPTM_GFX_GP_0 == enGPId) && (HI_TRUE == Support4KLogo))
    {
        g_pstGfxGPDevice[enGPId]->stOutRect.s32X      = 0;
        g_pstGfxGPDevice[enGPId]->stOutRect.s32Y      = 0;
        g_pstGfxGPDevice[enGPId]->stOutRect.s32Width  = stInfo.stFmtResolution.s32Width;
        g_pstGfxGPDevice[enGPId]->stOutRect.s32Height = stInfo.stFmtResolution.s32Height;
    }

    if ((HI_TRUE == stInfo.bIsMaster) && (enGPId == OPTM_GFX_GP_0))
    {
#ifndef CONFIG_HIFB_WBC_UNSUPPORT
        g_enOptmGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
#endif
    }

    OPTM_GPRecovery(enGPId);

#ifndef CONFIG_GFX_PQ
    enGpCsc = OPTM_AdaptCscTypeFromDisp(stInfo.eColorSpace);
#else
    enGpCsc = PQ_AdaptCscTypeFromDisp(stInfo.eColorSpace);
#endif

    g_pstGfxGPDevice[enGPId]->enOutputCsc = enGpCsc;
    OPTM_GPSetCsc(enGPId, &g_pstGfxGPDevice[enGPId]->stCscPara, g_pstGfxGPDevice[enGPId]->bBGRState);

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func         : OPTM_GFX_GetDevCap
* description  : CNcomment: 获取图层能力级 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static inline HI_VOID OPTM_GFX_GetDevCap(const HIFB_CAPABILITY_S **pstCap)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstCap);
    HIFB_CHECK_NULLPOINTER_UNRETURN(g_pstGfxCap[0]);

    *pstCap = g_pstGfxCap[0];

    return;
}

/***************************************************************************************
* func         : GFXCAPABILITY_Init
* description  : CNcomment: 图层能力级 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static inline HI_VOID GFXCAPABILITY_Init(HI_VOID)
{
    HI_S32 Index = 0;

    HIFB_CAPABILITY_S stHdGfxCap = {
                                       .bKeyAlpha       = 1,
                                       .bGlobalAlpha    = 1,
                                       .bCmap           = 1,
                                       .bHasCmapReg     = 1,
                                       .bColFmt         = {1,1,0,0,     \
                                                           0,0,1,1,     \
                                                           0,0,0,0,     \
                                                           0,1,1,0,     \
                                                           1,1,0,0,     \
                                                           0,0,1,1,     \
                                                           1,1,1,1,     \
                                                           0,0,0,0,     \
                                                           0,0},
                                       .bVoScale        = HI_TRUE,
                                       .bLayerSupported = CONFIG_HIFB_HD0_LAYER_SUPPORT,
                                       .bCompression    = CONFIG_HIFB_HD0_COMPRESSION_SUPPORT,
                                       .bStereo         = 1,
                                       .u32MaxWidth     = CONFIG_HIFB_HD_LAYER_MAXWIDTH,
                                       .u32MaxHeight    = CONFIG_HIFB_HD_LAYER_MAXHEIGHT,
                                       .u32MinWidth     = 0,
                                       .u32MinHeight    = 0,
                                       .u32VDefLevel    = 0,
                                       .u32HDefLevel    = 0,
                                   };

    if (OPTM_MAX_LOGIC_HIFB_LAYER > 6)
    {
        return;
    }

    for (Index = 0; Index < OPTM_MAX_LOGIC_HIFB_LAYER; Index++)
    {
        HIFB_CHECK_NULLPOINTER_UNRETURN(g_pstGfxCap[Index]);
        HI_GFX_Memcpy(g_pstGfxCap[Index], &stHdGfxCap, sizeof(stHdGfxCap));
    }

    g_pstGfxCap[1]->bLayerSupported = CONFIG_HIFB_HD1_LAYER_SUPPORT;
    g_pstGfxCap[1]->bCompression    = CONFIG_HIFB_HD1_COMPRESSION_SUPPORT;

    g_pstGfxCap[2]->bLayerSupported = CONFIG_HIFB_HD2_LAYER_SUPPORT;
    g_pstGfxCap[2]->bCompression    = CONFIG_HIFB_HD2_COMPRESSION_SUPPORT;

    g_pstGfxCap[3]->bLayerSupported = CONFIG_HIFB_HD3_LAYER_SUPPORT;
    g_pstGfxCap[3]->bCompression    = CONFIG_HIFB_HD3_COMPRESSION_SUPPORT;

    g_pstGfxCap[4]->bLayerSupported = CONFIG_HIFB_SD0_LAYER_SUPPORT;
    g_pstGfxCap[4]->bCompression    = CONFIG_HIFB_SD0_COMPRESSION_SUPPORT;

    g_pstGfxCap[5]->bLayerSupported = CONFIG_HIFB_SD1_LAYER_SUPPORT;
    g_pstGfxCap[5]->bCompression    = CONFIG_HIFB_SD1_COMPRESSION_SUPPORT;

    return;
}

/***************************************************************************************
* func         : OPTM_GetGfxHalId
* description  : CNcomment: hifb ID 转换成 图层ID，配寄存器使用 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static OPTM_VDP_LAYER_GFX_E OPTM_GetGfxHalId(HIFB_LAYER_ID_E enLayerId)
{
#ifdef CONFIG_HIFB_VERSION_1_0
    if ((HIFB_LAYER_SD_1 == enLayerId) && (OPTM_GP0_GFX_COUNT < 4))
    {
        #ifdef CONFIG_HIFB_GFX3_TO_GFX5
            return OPTM_VDP_LAYER_GFX3;
        #else
            return OPTM_VDP_LAYER_GFX_BUTT;
        #endif
    }
    else if(enLayerId < HIFB_LAYER_SD_1)
    {
        return (OPTM_VDP_LAYER_GFX_E)enLayerId;
    }
#else
    if (enLayerId < HIFB_LAYER_HD_2)
    {
        return (OPTM_VDP_LAYER_GFX_E)enLayerId;
    }
    else if(enLayerId == HIFB_LAYER_HD_2)
    {
        return OPTM_VDP_LAYER_GFX3;
    }
    else if(enLayerId == HIFB_LAYER_SD_0)
    {
        return (OPTM_VDP_LAYER_GFX_E)enLayerId;
    }
#endif
    else
    {
        return OPTM_VDP_LAYER_GFX_BUTT;
    }
}

/***************************************************************************************
* func          : OPTM_GFX_GetGpId
* description   : CNcomment: 将layer id 转换成 GP ID CNend\n
* param[in]     : LayerId
* retval        : NA
* others:       : NA
***************************************************************************************/
static OPTM_GFX_GP_E OPTM_GFX_GetGpId(HIFB_LAYER_ID_E LayerId)
{
    if (LayerId <= HIFB_LAYER_HD_3)
    {
        return OPTM_GFX_GP_0;
    }

    return OPTM_GFX_GP_1;
}

/***************************************************************************************
* func         : OPTM_AdaptCscTypeFromDisp
* description  : CNcomment: 从disp中获取CSC类型 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifndef CONFIG_GFX_PQ
static OPTM_COLOR_SPACE_E OPTM_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc)
{
    switch (enHiDrvCsc)
    {
        case HI_DRV_CS_BT601_YUV_LIMITED:
            return OPTM_CS_BT601_YUV_LIMITED;
        case HI_DRV_CS_BT601_YUV_FULL:
            return OPTM_CS_BT601_YUV_FULL;
        case HI_DRV_CS_BT601_RGB_FULL:
            return OPTM_CS_BT601_RGB_FULL;
        case HI_DRV_CS_BT709_YUV_LIMITED:
            return OPTM_CS_BT709_YUV_LIMITED;
        case HI_DRV_CS_BT709_YUV_FULL:
            return OPTM_CS_BT709_YUV_FULL;
        case HI_DRV_CS_BT709_RGB_FULL:
            return OPTM_CS_BT709_RGB_FULL;
        default:
            return OPTM_CS_BUTT;
    }
}
#else
static HI_PQ_GFX_COLOR_SPACE_E PQ_AdaptCscTypeFromDisp(HI_DRV_COLOR_SPACE_E enHiDrvCsc)
{
    switch (enHiDrvCsc)
    {
        case HI_DRV_CS_BT601_YUV_LIMITED:
            return PQ_GFX_CS_BT601_YUV_LIMITED;
        case HI_DRV_CS_BT601_YUV_FULL:
            return PQ_GFX_CS_BT601_YUV_FULL;
        case HI_DRV_CS_BT601_RGB_FULL:
            return PQ_GFX_CS_BT601_RGB_FULL;
        case HI_DRV_CS_BT709_YUV_LIMITED:
            return PQ_GFX_CS_BT709_YUV_LIMITED;
        case HI_DRV_CS_BT709_YUV_FULL:
            return PQ_GFX_CS_BT709_YUV_FULL;
        case HI_DRV_CS_BT709_RGB_FULL:
            return PQ_GFX_CS_BT709_RGB_FULL;
#ifdef CONFIG_HIFB_BI2020_SUPPORT
        case  HI_DRV_CS_BT2020_YUV_LIMITED:
            return PQ_GFX_CS_BT2020_YUV_LIMITED;
        case HI_DRV_CS_BT2020_YUV_FULL:
            return PQ_GFX_CS_BT2020_YUV_LIMITED;
        case HI_DRV_CS_BT2020_RGB_LIMITED:
            return PQ_GFX_CS_BT2020_RGB_FULL;
        case HI_DRV_CS_BT2020_RGB_FULL:
            return PQ_GFX_CS_BT2020_RGB_FULL;
#endif
        default:
            return PQ_GFX_CS_BUTT;
    }
}
#endif

#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
/***************************************************************************************
* func        : OPTM_AdaptTriDimModeFromDisp
* description : CNcomment: 从disp中获取3D模式 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HIFB_STEREO_MODE_E OPTM_AdaptTriDimModeFromDisp(OPTM_VDP_DISP_MODE_E enDispStereo)
{
    switch (enDispStereo)
    {
        case VDP_DISP_MODE_2D:
            return HIFB_STEREO_MONO;
        case VDP_DISP_MODE_SBS:
            return HIFB_STEREO_SIDEBYSIDE_HALF;
        case VDP_DISP_MODE_TAB:
            return HIFB_STEREO_TOPANDBOTTOM;
        case VDP_DISP_MODE_FP:
            return HIFB_STEREO_FRMPACKING;
        default:
            return HIFB_STEREO_BUTT;
    }

    return HIFB_STEREO_BUTT;
}
#endif


/***************************************************************************************
* func        : DRV_VDPREG_Init
* description : CNcomment: vdp register inital  CNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_S32 DRV_VDPREG_Init(HI_VOID)
{
#ifdef HI_BUILD_IN_BOOT
    gs_Phyaddr = (volatile HI_U32*)IO_ADDRESS(CONFIG_VDP_REG_BASEADDR);
#else
    gs_Phyaddr = (volatile HI_U32*)HI_GFX_REG_MAP(CONFIG_VDP_REG_BASEADDR, CONFIG_VDP_SIZE);
#endif
    if (NULL == gs_Phyaddr)
    {
        HIFB_ERROR("map vdp register failed\n");
        return HI_FAILURE;
    }

    OPTM_VDP_DRIVER_Initial(gs_Phyaddr);

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : DRV_VDPREG_DInit
* description : CNcomment: vdp register dinital  CNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_VOID DRV_VDPREG_DInit(HI_VOID)
{
#ifndef HI_BUILD_IN_BOOT
    if (NULL != gs_Phyaddr)
    {
       HI_GFX_REG_UNMAP((HI_VOID*)gs_Phyaddr);
    }

    gs_Phyaddr = NULL;
#endif
    return;
}

/***************************************************************************************
* func        : DRV_GPIRQ_Init
* description : CNcomment: GP IRQ inital  CNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_S32 DRV_GPIRQ_Init(HI_VOID)
{
    HI_S32 Index = 0;

#ifdef HI_BUILD_IN_BOOT
    g_pstGfxGPIrq[0] = (OPTM_GP_IRQ_S*)malloc(sizeof(OPTM_GP_IRQ_S) * OPTM_GFX_GP_BUTT);
#else
    g_pstGfxGPIrq[0] = (OPTM_GP_IRQ_S*)HI_GFX_VMALLOC(HIGFX_FB_ID, sizeof(OPTM_GP_IRQ_S) * OPTM_GFX_GP_BUTT);
#endif
    if (NULL == g_pstGfxGPIrq[0])
    {
        HIFB_ERROR("HI_GFX_VMALLOC g_pstGfxGPIrq mem failure\n");
        return HI_FAILURE;
    }
    for (Index = 0; Index < OPTM_GFX_GP_BUTT; Index++)
    {
        g_pstGfxGPIrq[Index] = (OPTM_GP_IRQ_S*)((HI_VOID*)g_pstGfxGPIrq[0] + Index * sizeof(OPTM_GP_IRQ_S));
        HI_GFX_Memset(g_pstGfxGPIrq[Index], 0, sizeof(OPTM_GP_IRQ_S));
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : DRV_GPIRQ_DInit
* description : CNcomment: GP IRQ dinital  CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_VOID DRV_GPIRQ_DInit(HI_VOID)
{
    if (NULL != g_pstGfxGPIrq[0])
#ifdef HI_BUILD_IN_BOOT
    {
        free((HI_VOID*)g_pstGfxGPIrq[0]);
    }
#else
    {
        HI_GFX_VFREE(HIGFX_FB_ID, (HI_VOID*)g_pstGfxGPIrq[0]);
    }
#endif
    g_pstGfxGPIrq[0] = NULL;

    return;
}

/***************************************************************************************
* func        : DRV_GPDEV_Init
* description : CNcomment: GP Device inital  CNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_S32 DRV_GPDEV_Init(HI_VOID)
{
    HI_S32 Index = 0;

#ifdef HI_BUILD_IN_BOOT
    g_pstGfxGPDevice[0] = (OPTM_GFX_GP_S*)malloc(sizeof(OPTM_GFX_GP_S) * OPTM_GFX_GP_BUTT);
#else
    g_pstGfxGPDevice[0] = (OPTM_GFX_GP_S*)HI_GFX_VMALLOC(HIGFX_FB_ID, sizeof(OPTM_GFX_GP_S) * OPTM_GFX_GP_BUTT);
#endif
    if (NULL == g_pstGfxGPDevice[0])
    {
        HIFB_ERROR("HI_GFX_VMALLOC g_pstGfxGPDevice mem failure\n");
        return HI_FAILURE;
    }
    for (Index = 0; Index < OPTM_GFX_GP_BUTT; Index++)
    {
        g_pstGfxGPDevice[Index] = (OPTM_GFX_GP_S*)((HI_VOID*)g_pstGfxGPDevice[0] + Index * sizeof(OPTM_GFX_GP_S));
        HI_GFX_Memset(g_pstGfxGPDevice[Index], 0, sizeof(OPTM_GFX_GP_S));
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : DRV_GPDEV_DInit
* description : CNcomment: GP Device dinital  CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_VOID DRV_GPDEV_DInit(HI_VOID)
{
    if (NULL != g_pstGfxGPDevice[0])
#ifdef HI_BUILD_IN_BOOT
    {
        free((HI_VOID*)g_pstGfxGPDevice[0]);
    }
#else
    {
        HI_GFX_VFREE(HIGFX_FB_ID, (HI_VOID*)g_pstGfxGPDevice[0]);
    }
#endif
    g_pstGfxGPDevice[0] = NULL;

    return;
}

/***************************************************************************************
* func        : DRV_GFXDEV_Init
* description : CNcomment: GFX Device inital  CNend\n
* param[in]   : HI_S32
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_S32 DRV_GFXDEV_Init(HI_VOID)
{
    HI_S32 Index = 0;

#ifdef HI_BUILD_IN_BOOT
    g_pstGfxDevice[0] = (OPTM_GFX_LAYER_S*)malloc(sizeof(OPTM_GFX_LAYER_S) * OPTM_MAX_LOGIC_HIFB_LAYER);
#else
    g_pstGfxDevice[0] = (OPTM_GFX_LAYER_S*)HI_GFX_VMALLOC(HIGFX_FB_ID, sizeof(OPTM_GFX_LAYER_S) * OPTM_MAX_LOGIC_HIFB_LAYER);
#endif
    if (NULL == g_pstGfxDevice[0])
    {
        HIFB_ERROR("HI_GFX_VMALLOC g_pstGfxDevice mem failure\n");
        return HI_FAILURE;
    }

    for (Index = 0; Index < OPTM_MAX_LOGIC_HIFB_LAYER; Index++)
    {
        g_pstGfxDevice[Index] = (OPTM_GFX_LAYER_S*)((HI_VOID*)g_pstGfxDevice[0] + Index * sizeof(OPTM_GFX_LAYER_S));
        HI_GFX_Memset(g_pstGfxDevice[Index], 0, sizeof(OPTM_GFX_LAYER_S));
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : DRV_GFXDEV_DInit
* description : CNcomment: GFX Device dinital  CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_VOID DRV_GFXDEV_DInit(HI_VOID)
{
    if (NULL != g_pstGfxDevice[0])
#ifdef HI_BUILD_IN_BOOT
    {
        free((HI_VOID*)g_pstGfxDevice[0]);
    }
#else
    {
        HI_GFX_VFREE(HIGFX_FB_ID, (HI_VOID*)g_pstGfxDevice[0]);
    }
#endif
    g_pstGfxDevice[0] = NULL;

    return;
}

/***************************************************************************************
* func         : DRV_GFXCAPABILITY_Init
* description  : CNcomment: 初始化图层能力级 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static inline HI_S32 DRV_GFXCAPABILITY_Init(HI_VOID)
{
    HI_S32 Index = 0;

 #ifdef HI_BUILD_IN_BOOT
    g_pstGfxCap[0] = (HIFB_CAPABILITY_S*)malloc(sizeof(HIFB_CAPABILITY_S) * OPTM_MAX_LOGIC_HIFB_LAYER);
#else
    g_pstGfxCap[0] = (HIFB_CAPABILITY_S*)HI_GFX_VMALLOC(HIGFX_FB_ID, sizeof(HIFB_CAPABILITY_S) * OPTM_MAX_LOGIC_HIFB_LAYER);
#endif
    if (NULL == g_pstGfxCap[0])
    {
        HIFB_ERROR("HI_GFX_VMALLOC g_pstGfxDevice mem failure\n");
        return HI_FAILURE;
    }

    for (Index = 0; Index < OPTM_MAX_LOGIC_HIFB_LAYER; Index++)
    {
        g_pstGfxCap[Index] = (HIFB_CAPABILITY_S*)((HI_VOID*)g_pstGfxCap[0] + Index * sizeof(HIFB_CAPABILITY_S));
        HI_GFX_Memset(g_pstGfxCap[Index], 0, sizeof(HIFB_CAPABILITY_S));
    }

    GFXCAPABILITY_Init();

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : DRV_GFXCAPABILITY_DInit
* description  : CNcomment: 去初始化图层能力级 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static inline HI_VOID DRV_GFXCAPABILITY_DInit(HI_VOID)
{
    if (NULL != g_pstGfxCap[0])
#ifdef HI_BUILD_IN_BOOT
    {
        free((HI_VOID*)g_pstGfxCap[0]);
    }
#else
    {
        HI_GFX_VFREE(HIGFX_FB_ID, (HI_VOID*)g_pstGfxCap[0]);
    }
#endif
    g_pstGfxCap[0] = NULL;

    return;
}

/***************************************************************************************
* func         : OPTM_GfxInit
* description  : CNcomment: 驱动初始化 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxInit(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;

    if (OPTM_ENABLE == gs_GFXInitFlag)
    {
        return HI_SUCCESS;
    }

    Ret = DRV_VDPREG_Init();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }

    Ret = DRV_GFXCAPABILITY_Init();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }

    Ret = DRV_GFXDEV_Init();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }

    Ret = DRV_GPDEV_Init();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }

    Ret = DRV_GPIRQ_Init();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }

    HIFB_WBC2_Init();

#ifndef CONFIG_GFX_PQ
    Ret = OPTM_ALG_GZmeVdpComnInit(&gs_stGPZme);
    if (HI_SUCCESS != Ret)
    {
       goto INIT_ERR;
    }
#else
  #ifdef HI_BUILD_IN_BOOT
    Ret = DRV_PQ_InitGfxZme();
    if (HI_SUCCESS != Ret)
    {
        goto INIT_ERR;
    }
  #endif
#endif

    gs_GFXInitFlag = OPTM_ENABLE;

    return HI_SUCCESS;

INIT_ERR:

    DRV_GPIRQ_DInit();
    DRV_GPDEV_DInit();
    DRV_GFXDEV_DInit();
    DRV_GFXCAPABILITY_DInit();
    DRV_VDPREG_DInit();

    gs_GFXInitFlag = OPTM_DISABLE;

    return HI_FAILURE;
}


/***************************************************************************************
* func        : OPTM_GfxDeInit
* description : CNcomment: 图形设备去初始化 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 OPTM_GfxDeInit(HI_VOID)
{
#ifndef HI_BUILD_IN_BOOT
    HI_U32 u32LayerId = HIFB_LAYER_HD_0;

    if (OPTM_DISABLE == gs_GFXInitFlag)
    {
        return HI_SUCCESS;
    }

    for (u32LayerId = HIFB_LAYER_HD_0; u32LayerId < HIFB_LAYER_ID_BUTT; u32LayerId++)
    {
        if (HI_FALSE != g_pstGfxDevice[u32LayerId]->bOpened)
        {
            (HI_VOID)OPTM_GfxCloseLayer(u32LayerId);
        }
    }

    #ifndef CONFIG_GFX_PQ
        OPTM_ALG_GZmeVdpComnDeInit(&gs_stGPZme);
    #endif

    HIFB_WBC2_Dinit();
    HIFB_WBC2_SetTcFlag(HI_FALSE);

    gs_GFXInitFlag     = OPTM_DISABLE;
    ps_DispExportFuncs = HI_NULL;
#endif

    DRV_GPIRQ_DInit();
    DRV_GPDEV_DInit();
    DRV_GFXDEV_DInit();
    DRV_GFXCAPABILITY_DInit();
    DRV_VDPREG_DInit();

    return HI_SUCCESS;
}


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_3DMode_Callback
* description  : CNcomment: 执行3D  工作对列函数 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_VOID OPTM_3DMode_Callback(struct work_struct *data)
{
    HI_U32 i = 0;
    //unsigned long LockFlag = 0;
    HI_U32 u32CTypeFlag = 0;
    HI_U32 u32LayerCount = 0;
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;
    OPTM_GFX_WORK_S *pst3DModeWork = HI_NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(data);
    pst3DModeWork = container_of(data, OPTM_GFX_WORK_S, work);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pst3DModeWork);

    enGpId = (OPTM_GFX_GP_E)(pst3DModeWork->u32Data);
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

    u32LayerCount = (OPTM_GFX_GP_0 == enGpId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    HIFB_CHECK_ARRAY_OVER_UNRETURN(u32LayerCount,OPTM_GP_SUPPORT_MAXLAYERNUM);

    for (i = 0; i < u32LayerCount;i++)
    {
        u32CTypeFlag = g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].u32CTypeFlag;
        if (0 == u32CTypeFlag)
        {
            continue;
        }

        if (u32CTypeFlag & HIFB_CALLBACK_TYPE_3DMode_CHG)
        {
         //spin_lock_irqsave(&(g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].FuncLock),LockFlag);
            if (g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pFunc)
            {
                g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pFunc(
                    g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].pParam0,
                    (HI_VOID*)&g_pstGfxGPDevice[enGpId]->enTriDimMode);
            }
         //spin_unlock_irqrestore(&(g_pstGfxGPIrq[enGpId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_3DMode_CHG].FuncLock),LockFlag);
        }
    }

    return;
}
#endif

/***************************************************************************************
* func        : OPTM_ALG_Init
* description : CNcomment: 算法初始化 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_VOID OPTM_ALG_Init(OPTM_GFX_GP_E enGPId)
{
#ifndef CONFIG_GFX_PQ
    OPTM_ALG_GDTI_RTL_PARA_S stDtiRtlPara;
    HI_GFX_Memset(&stDtiRtlPara, 0, sizeof(stDtiRtlPara));

    OPTM_ALG_GDtiInit(HI_NULL, &stDtiRtlPara);

    OPTM_VDP_GP_SetTiHpCoef(enGPId, VDP_TI_MODE_CHM, (HI_S32 *)stDtiRtlPara.s32CTIHPTmp);
    OPTM_VDP_GP_SetTiHpCoef(enGPId, VDP_TI_MODE_LUM, (HI_S32 *)stDtiRtlPara.s32LTIHPTmp);

    OPTM_VDP_GP_SetTiGainRatio(enGPId, VDP_TI_MODE_CHM, (HI_S32)stDtiRtlPara.s16CTICompsatRatio);
    OPTM_VDP_GP_SetTiGainRatio(enGPId, VDP_TI_MODE_LUM, (HI_S32)stDtiRtlPara.s16LTICompsatRatio);

    OPTM_VDP_GP_SetTiCoringThd(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u16CTICoringThrsh);
    OPTM_VDP_GP_SetTiCoringThd(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u16LTICoringThrsh);

    OPTM_VDP_GP_SetTiSwingThd(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u16CTIOverSwingThrsh, (HI_U32)stDtiRtlPara.u16CTIUnderSwingThrsh);
    OPTM_VDP_GP_SetTiSwingThd(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u16LTIOverSwingThrsh, (HI_U32)stDtiRtlPara.u16LTIUnderSwingThrsh);

    OPTM_VDP_GP_SetTiMixRatio(enGPId, VDP_TI_MODE_CHM, (HI_U32)stDtiRtlPara.u8CTIMixingRatio);
    OPTM_VDP_GP_SetTiMixRatio(enGPId, VDP_TI_MODE_LUM, (HI_U32)stDtiRtlPara.u8LTIMixingRatio);

    OPTM_VDP_GP_SetTiHfThd(enGPId, VDP_TI_MODE_LUM, (HI_U32 *)stDtiRtlPara.u32LTIHFreqThrsh);
    OPTM_VDP_GP_SetTiGainCoef(enGPId, VDP_TI_MODE_LUM, (HI_U32 *)stDtiRtlPara.u32LTICompsatMuti);
#else
    HI_UNUSED(enGPId);
#endif
    return;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_Aapt_Module_GetFunction
* description  : CNcomment: 获取函数指针 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static inline HI_S32 OPTM_Aapt_Module_GetFunction(HI_U32 u32ModuleID, HI_VOID** ppFunc)
{
    HIFB_CHECK_NULLPOINTER_RETURN(ppFunc, HI_FAILURE);

    if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(u32ModuleID, ppFunc))
    {
        return HI_FAILURE;
    }

    HIFB_CHECK_NULLPOINTER_RETURN(*ppFunc, HI_FAILURE);

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func         : OPTM_GPOpen
* description  : CNcomment: 打开GP设备并设置ZME系数 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GPOpen(OPTM_GFX_GP_E enGPId)
{
    HI_U32 i = 0;
    OPTM_VDP_BKG_S  stBkg = {0};
    HI_U32 u32InitLayerID = 0;
    HI_U32 u32MaxLayerCount = 0;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(g_pstGfxGPDevice[0], HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(g_pstGfxDevice[0],   HI_FAILURE);

    if (HI_TRUE == g_pstGfxGPDevice[enGPId]->bOpen)
    {
        return HI_SUCCESS;
    }

#ifndef HI_BUILD_IN_BOOT
    if (HI_NULL == ps_DispExportFuncs)
    {
        if (HI_SUCCESS != OPTM_Aapt_Module_GetFunction(HI_ID_DISP, (HI_VOID**)&ps_DispExportFuncs))
        {
            HIFB_ERROR("Fail to get disp export functions!\n");
            return HI_FAILURE;
        }
        HIFB_CHECK_NULLPOINTER_RETURN(ps_DispExportFuncs, HI_FAILURE);
    }

    if (OPTM_GFX_GP_0 == enGPId)
    {
        init_waitqueue_head(&g_stGfxWbc2.WaiteWbcWorkqueueMutex);

        g_pstGfxGPDevice[enGPId]->queue = create_workqueue(HIFB_WORK_QUEUE);
        if (HI_NULL == g_pstGfxGPDevice[enGPId]->queue)
        {
            HIFB_ERROR("create_workqueue failure.\n");
            return HI_FAILURE;
        }

        INIT_WORK(&g_pstGfxGPDevice[enGPId]->stOpenSlvWork.work,   HIFB_WBC_StartWorkQueue);
        INIT_WORK(&g_pstGfxGPDevice[enGPId]->st3DModeChgWork.work, OPTM_3DMode_Callback);
    }
#endif

    g_pstGfxGPDevice[enGPId]->u32ZmeDeflicker = (OPTM_GFX_GP_0 == enGPId)? (0) : (1);

    g_pstGfxGPDevice[enGPId]->u32Alpha          = 0xff;
    g_pstGfxGPDevice[enGPId]->enReadMode        = VDP_RMODE_PROGRESSIVE;
    g_pstGfxGPDevice[enGPId]->stBkg             = stBkg;
#ifndef CONFIG_GFX_PQ
    g_pstGfxGPDevice[enGPId]->enInputCsc        = OPTM_CS_BT709_RGB_FULL;
    g_pstGfxGPDevice[enGPId]->enOutputCsc       = OPTM_CS_UNKNOWN;
#else
    g_pstGfxGPDevice[enGPId]->enInputCsc        = PQ_GFX_CS_BT709_RGB_FULL;
    g_pstGfxGPDevice[enGPId]->enOutputCsc       = PQ_GFX_CS_BUTT;
#endif
    g_pstGfxGPDevice[enGPId]->bBGRState         = HI_FALSE;
    g_pstGfxGPDevice[enGPId]->bGpClose          = HI_FALSE;
    g_pstGfxGPDevice[enGPId]->bRecoveryInNextVT = HI_TRUE;
    g_pstGfxGPDevice[enGPId]->bDispInitial      = HI_FALSE;

    if (OPTM_GFX_GP_0 == enGPId)
    {
        g_pstGfxGPDevice[enGPId]->enMixg     = VDP_CBM_MIXG0;
        g_pstGfxGPDevice[enGPId]->enGpHalId  = OPTM_VDP_LAYER_GP0;
        g_pstGfxGPDevice[enGPId]->enDispCh   = OPTM_DISPCHANNEL_1;
        u32InitLayerID                       = (HI_U32)HIFB_LAYER_HD_0;
        u32MaxLayerCount                     = (HI_U32)(OPTM_GP0_GFX_COUNT + u32InitLayerID - 1);
    }
    else
    {
        g_pstGfxGPDevice[enGPId]->enMixg     = VDP_CBM_MIXG1;
        g_pstGfxGPDevice[enGPId]->enGpHalId  = OPTM_VDP_LAYER_GP1;
        g_pstGfxGPDevice[enGPId]->enDispCh   = OPTM_DISPCHANNEL_0;
        u32InitLayerID                       = (HI_U32)HIFB_LAYER_SD_0;
        u32MaxLayerCount                     = (HI_U32)(OPTM_GP1_GFX_COUNT + u32InitLayerID - 1);
    }

    OPTM_VDP_GP_SetLayerGalpha(enGPId, g_pstGfxGPDevice[enGPId]->u32Alpha);
    OPTM_VDP_GP_SetReadMode   (enGPId, g_pstGfxGPDevice[enGPId]->enReadMode);
    OPTM_VDP_GP_SetUpMode     (enGPId, g_pstGfxGPDevice[enGPId]->enReadMode);
    OPTM_VDP_CBM_SetMixerBkg  (g_pstGfxGPDevice[enGPId]->enMixg, &(g_pstGfxGPDevice[enGPId]->stBkg));

    g_pstGfxGPDevice[enGPId]->u32Prior = 0x0;

    HIFB_CHECK_ARRAY_OVER_RETURN(u32MaxLayerCount,OPTM_MAX_LOGIC_HIFB_LAYER, HI_FAILURE);

    for (i = u32InitLayerID; i <= u32MaxLayerCount; i++)
    {
        g_pstGfxDevice[i]->u32ZOrder = i;
        OPTM_VDP_CBM_SetMixerPrio(g_pstGfxGPDevice[enGPId]->enMixg, i, g_pstGfxDevice[i]->u32ZOrder);
        g_pstGfxDevice[i]->enGfxHalId = OPTM_GetGfxHalId(i);
     #ifdef CONFIG_HIFB_VERSION_1_0
        g_pstGfxGPDevice[enGPId]->u32Prior |= ((i + 1) << (i * 4));
     #else
        g_pstGfxGPDevice[enGPId]->u32Prior |= (i < 2) ? ((i+1)<<(i*4)) : (((i+1)+1)<<(i*4));
     #endif
    }

    OPTM_ALG_Init(enGPId);

    g_pstGfxGPDevice[enGPId]->bOpen = HI_TRUE;

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GPClose
* description  : CNcomment: 关闭GP设备 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GPClose(OPTM_GFX_GP_E enGPId)
{
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(g_pstGfxGPDevice[0], HI_FAILURE);

    if (HI_FALSE == g_pstGfxGPDevice[enGPId]->bOpen)
    {
        return HI_SUCCESS;
    }

    g_enOptmGfxWorkMode = HIFB_GFX_MODE_NORMAL;

#ifndef HI_BUILD_IN_BOOT
    OPTM_SetCallbackToDisp(enGPId, (IntCallBack)DRV_HIFB_ADP_UpDataCallBack,   HI_DRV_DISP_C_INTPOS_90_PERCENT,  HI_FALSE);
    OPTM_SetCallbackToDisp(enGPId, (IntCallBack)DRV_HIFB_ADP_FrameEndCallBack, HI_DRV_DISP_C_INTPOS_100_PERCENT, HI_FALSE);

    if (NULL != g_pstGfxGPDevice[enGPId]->queue)
    {
        destroy_workqueue(g_pstGfxGPDevice[enGPId]->queue);
        g_pstGfxGPDevice[enGPId]->queue = HI_NULL;
    }
#endif

    g_pstGfxGPDevice[enGPId]->bOpen            = HI_FALSE;
    g_pstGfxGPDevice[enGPId]->bDispInitial     = HI_FALSE;
    g_pstGfxGPDevice[enGPId]->bNeedExtractLine = HI_FALSE;
    g_pstGfxGPDevice[enGPId]->bMaskFlag        = HI_FALSE;

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetLayerReadMode
* description  : CNcomment: 设置读取数据模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerReadMode(HIFB_LAYER_ID_E enLayerId, OPTM_VDP_DATA_RMODE_E enReadMode)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId,HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId,HI_FAILURE);

    OPTM_VDP_GFX_SetReadMode(g_pstGfxDevice[enLayerId]->enGfxHalId, enReadMode);
    OPTM_VDP_GP_SetReadMode(g_pstGfxGPDevice[enGPId]->enGpHalId,   enReadMode);

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxInitLayer
* description  : CNcomment: 初始化图层信息 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_GfxInitLayer(HIFB_LAYER_ID_E enLayerId)
{
#ifndef HI_BUILD_IN_BOOT
    HI_U32 GfxIndex = 0;
    HIFB_CALLBACK_TPYE_E CallBackType = 0;
#endif
    OPTM_VDP_BKG_S stBkg = {0};

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);

    init_waitqueue_head(&(g_pstGfxDevice[enLayerId]->vblEvent));

    g_pstGfxDevice[enLayerId]->stBkg        = stBkg;
    g_pstGfxDevice[enLayerId]->enGfxHalId   = OPTM_GetGfxHalId(enLayerId);
    g_pstGfxDevice[enLayerId]->CscState     = OPTM_CSC_SET_PARA_RGB;
    g_pstGfxDevice[enLayerId]->enBitExtend  = VDP_GFX_BITEXTEND_3RD;
    g_pstGfxDevice[enLayerId]->enReadMode   = VDP_RMODE_PROGRESSIVE;
    g_pstGfxDevice[enLayerId]->enUpDateMode = VDP_RMODE_PROGRESSIVE;
#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    g_pstGfxDevice[enLayerId]->enGPId = (g_pstGfxDevice[enLayerId]->enGfxHalId > OPTM_VDP_LAYER_GFX2) ?
                                        (OPTM_GFX_GP_1) : (OPTM_GFX_GP_0);
#else
    g_pstGfxDevice[enLayerId]->enGPId = (g_pstGfxDevice[enLayerId]->enGfxHalId > OPTM_VDP_LAYER_GFX3) ?
                                        (OPTM_GFX_GP_1) : (OPTM_GFX_GP_0);
#endif

    OPTM_VDP_GFX_SetNoSecFlag  (g_pstGfxDevice[enLayerId]->enGfxHalId, HI_TRUE);
    OPTM_VDP_GFX_SetDcmpEnable (g_pstGfxDevice[enLayerId]->enGfxHalId, HI_FALSE);
    OPTM_VDP_GFX_SetLayerBkg   (g_pstGfxDevice[enLayerId]->enGfxHalId, &(g_pstGfxDevice[enLayerId]->stBkg));
    OPTM_VDP_GFX_SetBitExtend  (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enBitExtend);
    OPTM_VDP_GFX_SetReadMode   (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enReadMode);
    OPTM_VDP_GFX_SetUpdMode    (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enUpDateMode);

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    if (OPTM_VDP_LAYER_GFX3 == g_pstGfxDevice[enLayerId]->enGfxHalId)
    {
        OPTM_VDP_SetLayerConnect(OPTM_VDP_CONNECT_G3_DHD1);
        OPTM_VDP_OpenGFX3(HI_TRUE);
    }
#endif

#ifdef CONFIG_HIFB_VERSION_1_0
    OPTM_VDP_GFX_SetRegUp(g_pstGfxDevice[enLayerId]->enGfxHalId);
#endif

#ifndef HI_BUILD_IN_BOOT
    GfxIndex = (enLayerId > HIFB_LAYER_HD_3) ? (enLayerId - HIFB_LAYER_HD_3 - 1) : enLayerId;
    if (GfxIndex < OPTM_GP_SUPPORT_MAXLAYERNUM)
    {
        for (CallBackType = HIFB_CALLBACK_TYPE_VO; CallBackType < HIFB_CALLBACK_TYPE_BUTT; CallBackType++)
        {
          spin_lock_init(&(g_pstGfxGPIrq[g_pstGfxDevice[enLayerId]->enGPId]->stGfxCallBack[GfxIndex].stGfxIrq[CallBackType].FuncLock));
        }
    }
#endif

    return;
}

/***************************************************************************************
* func          : OPTM_GFX_ReleaseClutBuf
* description   : CNcomment: 释放调色板内存 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_ReleaseClutBuf(HIFB_LAYER_ID_E enLayerId)
{
#ifndef HI_BUILD_IN_BOOT
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId,HI_FAILURE);

    if (HI_FALSE == g_pstGfxCap[enLayerId]->bHasCmapReg)
    {
       return HI_SUCCESS;
    }

    if (NULL == g_pstGfxDevice[enLayerId]->stCluptTable.pu8StartVirAddr)
    {
        return HI_SUCCESS;
    }

    OPTM_UnmapAndRelease(&(g_pstGfxDevice[enLayerId]->stCluptTable));
    g_pstGfxDevice[enLayerId]->stCluptTable.pu8StartVirAddr  = NULL;
    g_pstGfxDevice[enLayerId]->stCluptTable.u32StartPhyAddr  = 0;
    g_pstGfxDevice[enLayerId]->stCluptTable.u32StartSmmuAddr = 0;
    g_pstGfxDevice[enLayerId]->stCluptTable.u32Size          = 0;
    g_pstGfxDevice[enLayerId]->stCluptTable.bSmmu            = HI_FALSE;
#else
    HI_UNUSED(enLayerId);
#endif

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GPSetCsc
* description : CNcomment: 设置GP CSC系数 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
#ifndef CONFIG_GFX_PQ
static HI_S32 OPTM_GPSetCsc(OPTM_GFX_GP_E enGfxGpId, OPTM_GFX_CSC_PARA_S *pstCscPara, HI_BOOL bIsBGRIn)
{
    OPTM_ALG_CSC_DRV_PARA_S stCscDrvPara;
    OPTM_ALG_CSC_RTL_PARA_S stCscRtlPara;
    OPTM_VDP_CSC_COEF_S     stVDPCscCoef;
    OPTM_VDP_CSC_DC_COEF_S  stVDPCscDcCoef;

#ifndef HI_BUILD_IN_BOOT
    OPTM_GFX_CSC_PARA_S stCscPara;
    HI_PQ_PICTURE_SETTING_S stPictureSetting = {50, 50, 50, 50};
#else
    HI_U32 enChan;
    HI_U32 u32Bright  = 50;  /** 亮度   **/
    HI_U32 u32Contrst = 50;  /** 对比度 **/
    HI_U32 u32Hue     = 50;  /** 色调   **/
    HI_U32 u32Satur   = 50;  /** 饱和度 **/
#endif

    HI_UNUSED(pstCscPara);
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGfxGpId,HI_FAILURE);

    HI_GFX_Memset(&stCscDrvPara,   0x0, sizeof(stCscDrvPara));
    HI_GFX_Memset(&stCscRtlPara,   0x0, sizeof(stCscRtlPara));
    HI_GFX_Memset(&stVDPCscCoef,   0x0, sizeof(stVDPCscCoef));
    HI_GFX_Memset(&stVDPCscDcCoef, 0x0, sizeof(stVDPCscDcCoef));

#ifndef HI_BUILD_IN_BOOT
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs->pfnPQ_GetHDPictureSetting,HI_FAILURE);

    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        gs_pstPqFuncs->pfnPQ_GetHDPictureSetting(&stPictureSetting);
    }
    else
    {
        gs_pstPqFuncs->pfnPQ_GetSDPictureSetting(&stPictureSetting);
    }

    stCscPara.u32Bright     = stCscDrvPara.u32Bright  = stPictureSetting.u16Brightness;
    stCscPara.u32Contrast   = stCscDrvPara.u32Contrst = stPictureSetting.u16Contrast;
    stCscPara.u32Hue        = stCscDrvPara.u32Hue     = stPictureSetting.u16Hue;
    stCscPara.u32Saturation = stCscDrvPara.u32Satur   = stPictureSetting.u16Saturation;

    stCscPara.u32Kb = stCscDrvPara.u32Kb = 50;
    stCscPara.u32Kg = stCscDrvPara.u32Kg = 50;
    stCscPara.u32Kr = stCscDrvPara.u32Kr = 50;

    if (memcmp(&g_pstGfxGPDevice[enGfxGpId]->stCscPara, &stCscPara, sizeof(OPTM_GFX_CSC_PARA_S)) != 0)
    {
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Bright          = stCscDrvPara.u32Bright;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Contrast        = stCscDrvPara.u32Contrst;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Hue             = stCscDrvPara.u32Hue;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Kb              = stCscDrvPara.u32Kb;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Kg              = stCscDrvPara.u32Kg;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Kr              = stCscDrvPara.u32Kr;
        g_pstGfxGPDevice[enGfxGpId]->stCscPara.u32Saturation      = stCscDrvPara.u32Satur;
        HIFB_WBC2_Reset(HI_TRUE);
    }

#else
    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        enChan = HI_UNF_DISPLAY1;
    }
    else
    {
        enChan = HI_UNF_DISPLAY0;
    }

    HI_PQ_GetBrightness   (enChan, &u32Bright);
    HI_PQ_GetContrast     (enChan, &u32Contrst);
    HI_PQ_GetHue          (enChan, &u32Hue);
    HI_PQ_GetSaturation   (enChan, &u32Satur);

    stCscDrvPara.u32Bright  = u32Bright;
    stCscDrvPara.u32Contrst = u32Contrst;
    stCscDrvPara.u32Hue     = u32Hue;
    stCscDrvPara.u32Satur   = u32Satur;
    stCscDrvPara.u32Kb      = 50;
    stCscDrvPara.u32Kg      = 50;
    stCscDrvPara.u32Kr      = 50;

#endif

    g_pstGfxGPDevice[enGfxGpId]->enInputCsc  = OPTM_CS_BT709_RGB_FULL;

    OPTM_CheckGPMask_BYGPID(enGfxGpId);

    stCscDrvPara.eInputCS   = g_pstGfxGPDevice[enGfxGpId]->enInputCsc;
    stCscDrvPara.eOutputCS  = g_pstGfxGPDevice[enGfxGpId]->enOutputCsc;
    stCscDrvPara.bIsBGRIn   = bIsBGRIn;

    OPTM_ALG_CscCoefSet(&stCscDrvPara, &stCscRtlPara);

    stVDPCscCoef.csc_coef00 = stCscRtlPara.s32CscCoef_00;
    stVDPCscCoef.csc_coef01 = stCscRtlPara.s32CscCoef_01;
    stVDPCscCoef.csc_coef02 = stCscRtlPara.s32CscCoef_02;
    stVDPCscCoef.csc_coef10 = stCscRtlPara.s32CscCoef_10;
    stVDPCscCoef.csc_coef11 = stCscRtlPara.s32CscCoef_11;
    stVDPCscCoef.csc_coef12 = stCscRtlPara.s32CscCoef_12;
    stVDPCscCoef.csc_coef20 = stCscRtlPara.s32CscCoef_20;
    stVDPCscCoef.csc_coef21 = stCscRtlPara.s32CscCoef_21;
    stVDPCscCoef.csc_coef22 = stCscRtlPara.s32CscCoef_22;

#ifdef CONFIG_HIFB_GP0CSC_USE_HDRMOD
    stVDPCscCoef.rgb2yuv_coef00 = stCscRtlPara.s32Rgb2YuvCoef_00;
    stVDPCscCoef.rgb2yuv_coef01 = stCscRtlPara.s32Rgb2YuvCoef_01;
    stVDPCscCoef.rgb2yuv_coef02 = stCscRtlPara.s32Rgb2YuvCoef_02;
    stVDPCscCoef.rgb2yuv_coef10 = stCscRtlPara.s32Rgb2YuvCoef_10;
    stVDPCscCoef.rgb2yuv_coef11 = stCscRtlPara.s32Rgb2YuvCoef_11;
    stVDPCscCoef.rgb2yuv_coef12 = stCscRtlPara.s32Rgb2YuvCoef_12;
    stVDPCscCoef.rgb2yuv_coef20 = stCscRtlPara.s32Rgb2YuvCoef_20;
    stVDPCscCoef.rgb2yuv_coef21 = stCscRtlPara.s32Rgb2YuvCoef_21;
    stVDPCscCoef.rgb2yuv_coef22 = stCscRtlPara.s32Rgb2YuvCoef_22;
#endif

    stVDPCscDcCoef.csc_in_dc0 = stCscRtlPara.s32CscDcIn_0;
    stVDPCscDcCoef.csc_in_dc1 = stCscRtlPara.s32CscDcIn_1;
    stVDPCscDcCoef.csc_in_dc2 = stCscRtlPara.s32CscDcIn_2;

    stVDPCscDcCoef.csc_out_dc0 = stCscRtlPara.s32CscDcOut_0;
    stVDPCscDcCoef.csc_out_dc1 = stCscRtlPara.s32CscDcOut_1;
    stVDPCscDcCoef.csc_out_dc2 = stCscRtlPara.s32CscDcOut_2;

#ifdef CONFIG_HIFB_GP0CSC_USE_HDRMOD
    stVDPCscDcCoef.rgb2yuv_out_dc0 = stCscRtlPara.s32Rgb2YuvOut_0;
    stVDPCscDcCoef.rgb2yuv_out_dc1 = stCscRtlPara.s32Rgb2YuvOut_1;
    stVDPCscDcCoef.rgb2yuv_out_dc2 = stCscRtlPara.s32Rgb2YuvOut_2;

    OPTM_VDP_GP_SetRgb2YuvScale2p  (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  stCscDrvPara.u32Rgb2YuvScale2p);
    OPTM_VDP_GP_SetRgb2YuvMin      (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  stCscDrvPara.u32Rgb2YuvMin);
    OPTM_VDP_GP_SetRgb2YuvMax      (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  stCscDrvPara.u32Rgb2YuvMax);
#endif

    OPTM_VDP_GP_SetCscCoef         (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  &stVDPCscCoef);
    OPTM_VDP_GP_SetCscDcCoef       (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  &stVDPCscDcCoef);
    OPTM_VDP_GP_SetCscEnable       (g_pstGfxGPDevice[enGfxGpId]->enGpHalId,  HI_TRUE);

    return HI_SUCCESS;
}
#else
static HI_S32 OPTM_GPSetCsc(OPTM_GFX_GP_E enGfxGpId, OPTM_GFX_CSC_PARA_S *pstCscPara, HI_BOOL bIsBGRIn)
{
    HI_PQ_GFX_CSC_PARA_S stGfxCscPara;

    HI_UNUSED(pstCscPara);
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGfxGpId,HI_FAILURE);

    HI_GFX_Memset(&stGfxCscPara, 0x0, sizeof(stGfxCscPara));

    g_pstGfxGPDevice[enGfxGpId]->enInputCsc = PQ_GFX_CS_BT709_RGB_FULL;

    OPTM_CheckGPMask_BYGPID(enGfxGpId);

    stGfxCscPara.sGfxCscMode.eInputCS   = g_pstGfxGPDevice[enGfxGpId]->enInputCsc;
    stGfxCscPara.sGfxCscMode.eOutputCS  = g_pstGfxGPDevice[enGfxGpId]->enOutputCsc;
    stGfxCscPara.bIsBGRIn   = bIsBGRIn;

#ifndef HI_BUILD_IN_BOOT
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs->pfnPQ_SetGfxCscCoef,HI_FAILURE);

    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        gs_pstPqFuncs->pfnPQ_SetGfxCscCoef(PQ_GFX_GP0,&stGfxCscPara);
    }
    else
    {
        gs_pstPqFuncs->pfnPQ_SetGfxCscCoef(PQ_GFX_GP1,&stGfxCscPara);
    }
#else
    if (enGfxGpId == OPTM_GFX_GP_0)
    {
        DRV_PQ_SetGfxCscCoef(PQ_GFX_GP0, &stGfxCscPara);
    }
    else
    {
        DRV_PQ_SetGfxCscCoef(PQ_GFX_GP1, &stGfxCscPara);
    }
#endif

    OPTM_VDP_GP_SetRegUp(g_pstGfxGPDevice[enGfxGpId]->enGpHalId);

    return HI_SUCCESS;
}
#endif


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_GfxSetCallback
* description  : CNcomment: set call back function
                             设置中断响应函数,在对应的中断中调用该对应的赋值函数 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetCallback(HIFB_CALLBACK_TPYE_E enCType, IntCallBack pCallBack, HIFB_LAYER_ID_E enLayerId)
{
    HI_U32 u32GfxIndex = 0;
    HI_ULONG LockFlag;
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    if (enCType >= HIFB_CALLBACK_TYPE_BUTT)
    {
        HIFB_ERROR("Fail to set callback func!\n");
        return HI_FAILURE;
    }

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId,HI_FAILURE);

    u32GfxIndex = (enLayerId > HIFB_LAYER_HD_3) ? (enLayerId - HIFB_LAYER_HD_3 - 1) : enLayerId;
    if (u32GfxIndex >= OPTM_GP_SUPPORT_MAXLAYERNUM)
    {
        HIFB_ERROR("Fail to set callback func!\n");
        return HI_FAILURE;
    }

    gs_CallBackLayerId[enLayerId] = enLayerId;
    if (HI_NULL != pCallBack)
    {
        g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].stGfxIrq[enCType].pFunc   = pCallBack;
        g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].stGfxIrq[enCType].pParam0 = (HI_VOID*)&gs_CallBackLayerId[enLayerId];
        g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].u32CTypeFlag |= enCType;

        return HI_SUCCESS;
    }

    spin_lock_irqsave(&(g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].stGfxIrq[enCType].FuncLock),LockFlag);

    g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].u32CTypeFlag &= ~((HI_U32)enCType);
    g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].stGfxIrq[enCType].pFunc = HI_NULL;

    spin_unlock_irqrestore(&(g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32GfxIndex].stGfxIrq[enCType].FuncLock),LockFlag);

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_CheckGfxCallbackReg
* description  : CNcomment: check whether call back function have register
                       判断相应的回调函数是否被注册 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_CheckGfxCallbackReg(OPTM_GFX_GP_E enGPId, HIFB_CALLBACK_TPYE_E eCallbackType)
{
    HI_U32 u32LayerCount = (enGPId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    HI_U32 u32LayerId = 0;

    HIFB_CHECK_ARRAY_OVER_RETURN(enGPId,OPTM_GFX_GP_BUTT,HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(u32LayerCount,OPTM_GP_SUPPORT_MAXLAYERNUM,HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(eCallbackType,HIFB_CALLBACK_TYPE_BUTT,HI_FAILURE);

    for (u32LayerId = 0; u32LayerId < u32LayerCount; u32LayerId++)
    {
        if (g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32LayerId].u32CTypeFlag & eCallbackType)
        {
            if (g_pstGfxGPIrq[enGPId]->stGfxCallBack[u32LayerId].stGfxIrq[eCallbackType].pFunc)
            {
                return HI_SUCCESS;
            }
        }
    }

    return HI_FAILURE;
}
#endif


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_GetScreenRectFromDispInfo
* description  : CNcomment: 从disp中获取screen rect CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GetScreenRectFromDispInfo(const HI_RECT_S *tmp_virtscreen,      \
                                             const OPTM_GFX_OFFSET_S *stOffsetInfo,\
                                             const HI_RECT_S *stFmtResolution,     \
                                             const HI_RECT_S *stPixelFmtResolution,\
                                             HI_RECT_S *stScreenRect)
{
    HI_S32 Ret = HI_SUCCESS;
    OPTM_GFX_OFFSET_S tmp_offsetInfo;

    HIFB_CHECK_NULLPOINTER_RETURN(tmp_virtscreen,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stOffsetInfo,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stFmtResolution,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stPixelFmtResolution,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(stScreenRect,HI_FAILURE);

    HI_GFX_Memcpy(&tmp_offsetInfo, stOffsetInfo, sizeof(tmp_offsetInfo));

    if ((tmp_virtscreen->s32Width == 0) || (tmp_virtscreen->s32Height == 0))
    {
        return HI_FAILURE;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  stPixelFmtResolution->s32Width, stPixelFmtResolution->s32Height,0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    if ( (stFmtResolution->s32Width * 2) == stPixelFmtResolution->s32Width)
    {
        tmp_offsetInfo.u32Left  *= 2;
        tmp_offsetInfo.u32Right *= 2;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  tmp_offsetInfo.u32Left, tmp_offsetInfo.u32Top,0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  tmp_offsetInfo.u32Right, tmp_offsetInfo.u32Bottom,0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    if (   (stPixelFmtResolution->s32Width <= (tmp_offsetInfo.u32Left + tmp_offsetInfo.u32Right))
        || (stPixelFmtResolution->s32Height <= (tmp_offsetInfo.u32Top + tmp_offsetInfo.u32Bottom)))
    {
        return HI_FAILURE;
    }

    stScreenRect->s32X      = tmp_offsetInfo.u32Left;
    stScreenRect->s32Y      = tmp_offsetInfo.u32Top;
    stScreenRect->s32Width  = (stPixelFmtResolution->s32Width - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    stScreenRect->s32Height = (stPixelFmtResolution->s32Height - tmp_offsetInfo.u32Top - tmp_offsetInfo.u32Bottom);
    stScreenRect->s32X      = OPTM_AlignUp(stScreenRect->s32X, 2);
    stScreenRect->s32Y      = OPTM_AlignUp(stScreenRect->s32Y, 2);
    stScreenRect->s32Width  = OPTM_AlignUp(stScreenRect->s32Width, 2);
    stScreenRect->s32Height = OPTM_AlignUp(stScreenRect->s32Height, 2);

    return HI_SUCCESS;
}
#endif


#ifndef HI_BUILD_IN_BOOT
static HI_VOID DRV_HIFB_ADP_FrameEndCallBack(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifdef CFG_HIFB_FENCE_SUPPORT
    //unsigned long LockFlag = 0;
    HI_U32 u32CTypeFlag = 0;
    HI_VOID* pLayerId   = NULL;
  #ifndef CONFIG_HIFB_VERSION_1_0
    HI_U32 WorkedLayerDdr = 0;
    HI_U32 WillWorkLayerDdr = 0;
  #endif
#endif
    HIFB_LAYER_ID_E enLayerId = HIFB_LAYER_HD_0;
    OPTM_GFX_GP_E  *pEnGpId   = (OPTM_GFX_GP_E *)u32Param0;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);

    if (OPTM_GFX_GP_0 != *pEnGpId)
    {
        return;
    }

    if (HI_FALSE == g_pstGfxGPDevice[*pEnGpId]->bOpen)
    {
        return;
    }

    (HI_VOID)HIFB_WBC_FrameEndProcess(*pEnGpId);

    for (enLayerId = HIFB_LAYER_HD_0; enLayerId <= HIFB_LAYER_HD_3; enLayerId++)
    {
#ifdef CFG_HIFB_FENCE_SUPPORT
        pLayerId = g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pParam0;
        if (NULL == pLayerId)
        {
           continue;
        }
  #ifndef CONFIG_HIFB_VERSION_1_0
        HIFB_HAL_GetWorkedLayerAddr(enLayerId,&WorkedLayerDdr);
        HIFB_HAL_GetWillWorkLayerAddr(enLayerId,&WillWorkLayerDdr);
        if (WorkedLayerDdr != WillWorkLayerDdr)
        {
           return;
        }
  #endif
        u32CTypeFlag = g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].u32CTypeFlag;

        /**TODO: here spin lock should test by peach-driver **/
        //spin_lock_irqsave(&(g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].FuncLock),LockFlag);

        if ((u32CTypeFlag & HIFB_CALLBACK_TYPE_FRAME_END) && (NULL != g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pFunc))
        {
           g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].pFunc(pLayerId,HI_NULL);
        }

        //spin_unlock_irqrestore(&(g_pstGfxGPIrq[*pEnGpId]->stGfxCallBack[enLayerId].stGfxIrq[HIFB_CALLBACK_TYPE_FRAME_END].FuncLock),LockFlag);
#endif

#ifdef OPTM_HIFB_WVM_ENABLE
        OPTM_GfxWVBCallBack(enLayerId);
#endif
    }

    return;
}

/***************************************************************************************
* func        : OPTM_DispInfoProcess
* description : CNcomment: display信息处理 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_BOOL OPTM_DispInfoProcess(OPTM_VDP_LAYER_GP_E eGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo)
{
    HI_BOOL bDispInfoChange = HI_FALSE;
    HI_RECT_S stOutRect;

    HIFB_CHECK_GPID_SUPPORT_RETURN(eGpId, HI_FALSE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstDispInfo,HI_FALSE);

#ifdef CONFIG_HIFB_VERSION_1_0
    OPTM_GPSetCsc(eGpId, &g_pstGfxGPDevice[eGpId]->stCscPara,g_pstGfxGPDevice[eGpId]->bBGRState);
#endif

    if (  (g_pstGfxGPDevice[eGpId]->stInRect.s32Width  != pstDispInfo->stDispInfo.stVirtaulScreen.s32Width)
        ||(g_pstGfxGPDevice[eGpId]->stInRect.s32Height != pstDispInfo->stDispInfo.stVirtaulScreen.s32Height))
    {
        bDispInfoChange = HI_TRUE;
    }

    g_pstGfxGPDevice[eGpId]->stInRect.s32X = pstDispInfo->stDispInfo.stVirtaulScreen.s32X;
    g_pstGfxGPDevice[eGpId]->stInRect.s32Y = pstDispInfo->stDispInfo.stVirtaulScreen.s32Y;
    g_pstGfxGPDevice[eGpId]->stInRect.s32Width  = pstDispInfo->stDispInfo.stVirtaulScreen.s32Width;
    g_pstGfxGPDevice[eGpId]->stInRect.s32Height = pstDispInfo->stDispInfo.stVirtaulScreen.s32Height;

    OPTM_GetScreenRectFromDispInfo(&pstDispInfo->stDispInfo.stVirtaulScreen,
                                   (OPTM_GFX_OFFSET_S *)&pstDispInfo->stDispInfo.stOffsetInfo,
                                   &pstDispInfo->stDispInfo.stFmtResolution,
                                   &pstDispInfo->stDispInfo.stPixelFmtResolution,
                                   &stOutRect);

    if ((g_pstGfxGPDevice[eGpId]->stOutRect.s32Width  != stOutRect.s32Width)  ||
        (g_pstGfxGPDevice[eGpId]->stOutRect.s32Height != stOutRect.s32Height) ||
        (g_pstGfxGPDevice[eGpId]->stOutRect.s32X != stOutRect.s32X)           ||
        (g_pstGfxGPDevice[eGpId]->stOutRect.s32Y != stOutRect.s32Y))
    {
        bDispInfoChange = HI_TRUE;
    }

    HI_GFX_Memcpy(&g_pstGfxGPDevice[eGpId]->stOutRect, &stOutRect, sizeof(stOutRect));

    return bDispInfoChange;
}

/***************************************************************************************
* func          : OPTM_SET_GPMask
* description   : CNcomment: 在90%中断处理中调用,设置GP掩码 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_SET_GPMask(OPTM_GFX_GP_E enGPId, HI_BOOL bFlag)
{
    HI_U32 i = 0;
    HI_BOOL bEnable  = HI_FALSE;
    HI_U32 u32LayerCount = 0;
    HIFB_LAYER_ID_E  enLayerId = HIFB_LAYER_HD_0;
    OPTM_GFX_WBC_S   *pstWbc2  = &g_stGfxWbc2;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (HI_FALSE == g_pstGfxGPDevice[enGPId]->bOpen)
    {
        return HI_SUCCESS;
    }

    u32LayerCount = (OPTM_GFX_GP_0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    HIFB_CHECK_LAYERID_SUPPORT_RETURN((enLayerId + u32LayerCount), HI_FAILURE);

    enLayerId = (OPTM_GFX_GP_0 == enGPId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    g_pstGfxGPDevice[enGPId]->bMaskFlag = bFlag;

    if (IS_MASTER_GP((OPTM_GFX_GP_E)enGPId))
    {
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->bMaskFlag = bFlag;
    }

    if (IS_SLAVER_GP(enGPId))
    {
        bEnable = bFlag ? HI_FALSE : g_pstGfxDevice[HIFB_LAYER_SD_0]->bEnable;
        OPTM_VDP_WBC_SetEnable      (pstWbc2->enWbcHalId, bEnable);
        OPTM_VDP_WBC_SetRegUp       (pstWbc2->enWbcHalId);
        OPTM_VDP_GFX_SetLayerEnable (g_pstGfxDevice[HIFB_LAYER_SD_0]->enGfxHalId, bEnable);
        OPTM_VDP_GFX_SetRegUp       (g_pstGfxDevice[HIFB_LAYER_SD_0]->enGfxHalId);
        return HI_SUCCESS;
    }

    for (i = 0; i < u32LayerCount;i++)
    {
        if (HI_FALSE == g_pstGfxDevice[enLayerId + i]->bOpened)
        {
            continue;
        }

        bEnable = bFlag ? (HI_FALSE) : (g_pstGfxDevice[enLayerId+i]->bEnable);
        OPTM_VDP_GFX_SetLayerEnable(g_pstGfxDevice[enLayerId + i]->enGfxHalId, bEnable);
        g_pstGfxDevice[HIFB_LAYER_SD_0]->bEnable = bEnable;
    }

    if (IS_MASTER_GP((OPTM_GFX_GP_E)enGPId))
    {
        g_pstGfxDevice[HIFB_LAYER_SD_0]->bEnable = bFlag ? (HI_FALSE) : (g_pstGfxDevice[HIFB_LAYER_SD_0]->bEnable);
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->unUpFlag.bits.IsEnable = 1;
    }

    return HI_SUCCESS;
}

STATIC HI_VOID HIFB_ADP_GetResumeStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbResume)
{
    HIFB_CHECK_ARRAY_OVER_UNRETURN(enLayerId, HIFB_LAYER_SD_0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pbResume);

    *pbResume = g_pstGfxGPDevice[0]->bResume;
    g_pstGfxGPDevice[0]->bResume = HI_FALSE;

    return;
}

STATIC HI_VOID HIFB_ADP_GetResumeForPowerOffStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *ResumeForPowerOff)
{
    HIFB_CHECK_ARRAY_OVER_UNRETURN(enLayerId, HIFB_LAYER_SD_0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(ResumeForPowerOff);

    *ResumeForPowerOff = g_pstGfxGPDevice[0]->bResumeForPowerOff;
    g_pstGfxGPDevice[0]->bResumeForPowerOff = HI_FALSE;

    return;
}

STATIC HI_VOID HIFB_ADP_SetLowPowerInfo(HIFB_LAYER_ID_E enLayerId,HIFB_ADP_LOWPOWER_INFO_S *pstLowPowerInfo)
{
#ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
     HIFB_CHECK_NULLPOINTER_UNRETURN(pstLowPowerInfo);
     HIFB_HAL_EnableLayerLowPower(enLayerId, pstLowPowerInfo->LowPowerEn);
     HIFB_HAL_EnableGpLowPower(OPTM_GFX_GetGpId(enLayerId), pstLowPowerInfo->LowPowerEn);
     HIFB_HAL_SetLowPowerInfo(enLayerId,pstLowPowerInfo->LpInfo);
#else
     HI_UNUSED(enLayerId);
     HI_UNUSED(pstLowPowerInfo);
#endif
}
#endif


STATIC HI_VOID HIFB_ADP_SetDeCmpDdrInfo(HIFB_LAYER_ID_E enLayerId, HI_U32 ARHeadDdr,HI_U32 ARDataDdr,HI_U32 GBHeadDdr,HI_U32 GBDataDdr,HI_U32 DeCmpStride)
{
#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE)
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);
    g_pstGfxDevice[enLayerId]->ARHeadDdr = ARHeadDdr;
    g_pstGfxDevice[enLayerId]->ARDataDdr = ARDataDdr;
    g_pstGfxDevice[enLayerId]->GBHeadDdr = GBHeadDdr;
    g_pstGfxDevice[enLayerId]->GBDataDdr = GBDataDdr;
    g_pstGfxDevice[enLayerId]->CmpStride = (HI_U16)DeCmpStride;
    DRV_HAL_SetDeCmpDdrInfo(enLayerId,ARHeadDdr,ARDataDdr,GBHeadDdr,GBDataDdr,DeCmpStride);
#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(ARHeadDdr);
    HI_UNUSED(ARDataDdr);
    HI_UNUSED(GBHeadDdr);
    HI_UNUSED(GBDataDdr);
    HI_UNUSED(DeCmpStride);
#endif
    return;
}

STATIC HI_VOID HIFB_ADP_GetDecompressStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbARDataDecompressErr, HI_BOOL *pbGBDataDecompressErr)
{
#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE)
    DRV_HAL_GetDeCmpStatus(enLayerId, pbARDataDecompressErr, pbGBDataDecompressErr);
#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(pbARDataDecompressErr);
    HI_UNUSED(pbGBDataDecompressErr);
#endif
    return;
}

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT)
STATIC HI_VOID OPTM_GFX_DECMP_Open(HIFB_LAYER_ID_E enLayerId)
{
    g_pstGfxDevice[enLayerId]->bDmpOpened = HI_TRUE;
    OPTM_VDP_GFX_SetDcmpEnable(enLayerId,HI_TRUE);
}

STATIC HI_VOID OPTM_GFX_DECMP_Close(HIFB_LAYER_ID_E enLayerId)
{
    g_pstGfxDevice[enLayerId]->bDmpOpened = HI_FALSE;
    OPTM_VDP_GFX_SetDcmpEnable(enLayerId,HI_FALSE);
}
#endif

#ifndef HI_BUILD_IN_BOOT
HI_VOID DRV_HIFB_ADP_UpDataCallBack(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
    OPTM_GFX_GP_E *pEnGpId = NULL;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);

    pEnGpId = (OPTM_GFX_GP_E *)u32Param0;
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(*pEnGpId);

    pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if (HI_FALSE == g_pstGfxGPDevice[*pEnGpId]->bOpen)
    {
        return;
    }

    /** not support wbc, so should not up gp1 **/
    if ((g_enOptmGfxWorkMode != HIFB_GFX_MODE_HD_WBC) && (OPTM_GFX_GP_1 == *pEnGpId))
    {
        return;
    }

#ifdef CHIP_TYPE_hi3798cv200/** support hdmi cts **/
    g_pstGfxGPDevice[*pEnGpId]->enDispFmt = pstDispInfo->stDispInfo.eFmt;
#endif

    if (  (g_enOptmGfxWorkMode == HIFB_GFX_MODE_NORMAL)
        &&(HI_TRUE == pstDispInfo->stDispInfo.bIsMaster)
        &&(OPTM_GFX_GP_0 == *pEnGpId))
    {
#ifndef CONFIG_HIFB_WBC_UNSUPPORT
        g_enOptmGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
#endif
        if (NULL != g_pstGfxGPDevice[*pEnGpId]->queue)
        {
            g_pstGfxGPDevice[*pEnGpId]->stOpenSlvWork.u32Data = HIFB_LAYER_SD_0;
            queue_work(g_pstGfxGPDevice[*pEnGpId]->queue, &g_pstGfxGPDevice[*pEnGpId]->stOpenSlvWork.work);
        }
    }

    if ((HI_DRV_DISP_C_PREPARE_TO_PEND == pstDispInfo->eEventType) || (HI_DRV_DISP_C_PREPARE_CLOSE == pstDispInfo->eEventType))
    {
        return HIFB_ADP_ReClose(*pEnGpId);
    }

    if ((HI_DRV_DISP_C_RESUME == pstDispInfo->eEventType) || (HI_DRV_DISP_C_OPEN == pstDispInfo->eEventType))
    {
        g_pstGfxGPDevice[*pEnGpId]->bHasBeenReOpen[0] = HI_TRUE;
        g_pstGfxGPDevice[*pEnGpId]->bHasBeenReOpen[1] = HI_TRUE;
        g_pstGfxGPDevice[*pEnGpId]->bResume  = HI_TRUE;
        g_pstGfxGPDevice[*pEnGpId]->bResumeForPowerOff = HI_TRUE;
        return HIFB_ADP_ReOpen(*pEnGpId);
    }

    if (HI_DRV_DISP_C_DISPLAY_SETTING_CHANGE == pstDispInfo->eEventType)
    {
        HIFB_ADP_DispSetting(*pEnGpId,pstDispInfo);
    }

    if (HI_FALSE == g_pstGfxGPDevice[*pEnGpId]->bGpClose)
    {
         return HIFB_ADP_UpdataLayerInfo(u32Param0,u32Param1);
    }
}

static inline HI_VOID HIFB_ADP_ReOpen(OPTM_GFX_GP_E enGpId)
{
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);
    if (HI_FALSE == g_pstGfxGPDevice[enGpId]->bDispInitial)
    {
        return;
    }

    if (HI_TRUE == g_pstGfxGPDevice[enGpId]->bGpClose)
    {
        g_pstGfxGPDevice[enGpId]->bGpClose = HI_FALSE;
        g_pstGfxGPDevice[enGpId]->bRecoveryInNextVT = HI_TRUE;
    }

    HIFB_WBC2_Reset(HI_FALSE);

    OPTM_SET_GPMask(enGpId, HI_FALSE);

    return;
}

static inline HI_VOID HIFB_ADP_ReClose(OPTM_GFX_GP_E enGpId)
{
     HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

     if (HI_FALSE == g_pstGfxGPDevice[enGpId]->bDispInitial)
     {
         return;
     }

     g_pstGfxGPDevice[enGpId]->bGpClose = HI_TRUE;

     OPTM_SET_GPMask(enGpId, HI_TRUE);

     return;
}

static inline HI_VOID HIFB_ADP_DispSetting(OPTM_GFX_GP_E enGpId, HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo)
{
     HI_BOOL bDispInfoChange = HI_FALSE;

     bDispInfoChange = OPTM_DispInfoProcess(enGpId, pstDispInfo);
     if (HI_FALSE == bDispInfoChange)
     {
         return;
     }

     OPTM_DispInfoUpdate(enGpId);

     if ((enGpId == OPTM_GFX_GP_1) || IS_MASTER_GP(enGpId))
     {
         HIFB_WBC2_Reset(HI_TRUE);
         g_pstGfxGPDevice[OPTM_GFX_GP_1]->unUpFlag.bits.IsNeedUpInRect = 1;
         g_stGfxWbc2.s32WbcCnt = 2;
     }

     return;
}

static inline HI_VOID HIFB_ADP_UpdataLayerInfo(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifndef CONFIG_GFX_PQ
    OPTM_COLOR_SPACE_E enGpCsc = OPTM_CS_BUTT;
#else
    HI_PQ_GFX_COLOR_SPACE_E  enGpCsc  = PQ_GFX_CS_BUTT;
#endif

#ifndef CONFIG_HIFB_VERSION_1_0
    HI_BOOL bHDR = HI_FALSE;
#endif
    OPTM_GFX_GP_E *enGpId = NULL;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param0);
    HIFB_CHECK_NULLPOINTER_UNRETURN(u32Param1);

    enGpId = (OPTM_GFX_GP_E *)u32Param0;
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(*enGpId);

    pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if (HI_TRUE == g_pstGfxGPDevice[*enGpId]->bRecoveryInNextVT)
    {
        g_pstGfxGPDevice[*enGpId]->bInterface = pstDispInfo->stDispInfo.bInterlace;

        g_pstGfxGPDevice[*enGpId]->stInRect.s32X = pstDispInfo->stDispInfo.stVirtaulScreen.s32X;
        g_pstGfxGPDevice[*enGpId]->stInRect.s32Y = pstDispInfo->stDispInfo.stVirtaulScreen.s32Y;
        g_pstGfxGPDevice[*enGpId]->stInRect.s32Width  = pstDispInfo->stDispInfo.stVirtaulScreen.s32Width;
        g_pstGfxGPDevice[*enGpId]->stInRect.s32Height = pstDispInfo->stDispInfo.stVirtaulScreen.s32Height;

        OPTM_GetScreenRectFromDispInfo(&pstDispInfo->stDispInfo.stVirtaulScreen,                   \
                                       (OPTM_GFX_OFFSET_S *)&pstDispInfo->stDispInfo.stOffsetInfo, \
                                       &pstDispInfo->stDispInfo.stFmtResolution,                   \
                                       &pstDispInfo->stDispInfo.stPixelFmtResolution,              \
                                       &g_pstGfxGPDevice[*enGpId]->stOutRect);

        OPTM_GPRecovery(*enGpId);

        g_pstGfxGPDevice[*enGpId]->bRecoveryInNextVT = HI_FALSE;
        g_pstGfxGPDevice[*enGpId]->bDispInitial      = HI_TRUE;

    }

#ifndef CONFIG_GFX_PQ
    enGpCsc = OPTM_AdaptCscTypeFromDisp(pstDispInfo->stDispInfo.eColorSpace);
#else
    enGpCsc = PQ_AdaptCscTypeFromDisp(pstDispInfo->stDispInfo.eColorSpace);
#endif

#ifdef CONFIG_HIFB_VERSION_1_0
    g_pstGfxGPDevice[*enGpId]->enOutputCsc = enGpCsc;
    OPTM_GPSetCsc(*enGpId, &g_pstGfxGPDevice[*enGpId]->stCscPara,g_pstGfxGPDevice[*enGpId]->bBGRState);
#else
   g_pstGfxGPDevice[*enGpId]->enOutputCsc = enGpCsc;

   bHDR = (HI_DRV_DISP_PROCESS_MODE_HDR == pstDispInfo->stDispInfo.enDispProcessMode)? (HI_TRUE) : (HI_FALSE);
   g_pstGfxGPDevice[*enGpId]->bHdr = bHDR;

   if ((HI_FALSE == bHDR) || (OPTM_GFX_GP_1 == *enGpId))
   {
       OPTM_GPSetCsc(*enGpId, &g_pstGfxGPDevice[*enGpId]->stCscPara, g_pstGfxGPDevice[*enGpId]->bBGRState);
   }
#endif

    if (IS_SLAVER_GP(*enGpId))
    {
        HIFB_WBC_Process(*enGpId);
    }
    else
    {
        OPTM_Distribute_Callback(u32Param0, u32Param1);
    }

    return;
}

/***************************************************************************************
* func        : OPTM_GfxChn2DispChn
* description : CNcomment: 获取display通道 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_DRV_DISPLAY_E OPTM_GfxChn2DispChn(OPTM_DISPCHANNEL_E enDispCh)
{
    if (OPTM_DISPCHANNEL_0 == enDispCh)
    {
        return HI_DRV_DISPLAY_0;
    }

    if (OPTM_DISPCHANNEL_1 == enDispCh)
    {
        return HI_DRV_DISPLAY_1;
    }

    return HI_DRV_DISPLAY_BUTT;
}

/***************************************************************************************
* func         : OPTM_SetCallbackToDisp
* description  : CNcomment: 向Display注册中断 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_SetCallbackToDisp(OPTM_GFX_GP_E enGPId, IntCallBack pCallBack, HI_DRV_DISP_CALLBACK_TYPE_E eType, HI_BOOL bFlag)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_DISPLAY_E enDisp;
    HI_DRV_DISP_CALLBACK_S stCallback;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);
    HIFB_CHECK_ARRAY_OVER_RETURN(eType,HI_DRV_DISP_C_TYPE_BUTT,HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pCallBack, HI_FAILURE);

    if (bFlag == g_pstGfxGPIrq[enGPId]->bRegistered[eType])
    {
        return HI_SUCCESS;
    }

    enDisp = OPTM_GfxChn2DispChn(g_pstGfxGPDevice[enGPId]->enDispCh);
    stCallback.hDst = (HI_VOID*)(&g_pstGfxGPDevice[enGPId]->enGpHalId);
    stCallback.pfDISP_Callback = (HI_VOID*)pCallBack;

    HIFB_CHECK_NULLPOINTER_RETURN(ps_DispExportFuncs, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(ps_DispExportFuncs->pfnDispRegCallback, HI_FAILURE);
    if (bFlag)
    {
        s32Ret = ps_DispExportFuncs->pfnDispRegCallback(enDisp,eType,&stCallback);
    }
    else
    {
        s32Ret = ps_DispExportFuncs->pfnDispUnRegCallback(enDisp,eType,&stCallback);
    }

    if (HI_SUCCESS == s32Ret)
    {
        g_pstGfxGPIrq[enGPId]->bRegistered[eType] = bFlag;
    }

    return s32Ret;
}
#endif


/***************************************************************************************
* func         : OPTM_GfxOpenLayer
* description  : CNcomment: 打开图层 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxOpenLayer(HIFB_LAYER_ID_E enLayerId)
{
#ifndef HI_BUILD_IN_BOOT
    HI_S32 s32Ret = HI_SUCCESS;
#endif
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    if (HI_TRUE != g_pstGfxCap[enLayerId]->bLayerSupported)
    {
        HIFB_ERROR("fb%d was not supported!\n",enLayerId);
        return HI_FAILURE;
    }

    if (HI_TRUE == g_pstGfxDevice[enLayerId]->bOpened)
    {
        return HI_SUCCESS;
    }

    if ((HIFB_GFX_MODE_HD_WBC == g_enOptmGfxWorkMode) && (HIFB_LAYER_SD_0 == enLayerId))
    {
        return HI_FAILURE;
    }

#ifndef HI_BUILD_IN_BOOT
    if (HI_NULL == gs_pstPqFuncs)
    {
        if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_PQ, (HI_VOID**)&gs_pstPqFuncs))
        {
            return HI_FAILURE;
        }
    }
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs, HI_FAILURE);
#endif

    OPTM_GfxInitLayer(enLayerId);

#ifndef HI_BUILD_IN_BOOT
    s32Ret = OPTM_GPOpen(g_pstGfxDevice[enLayerId]->enGPId);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
#else
    (HI_VOID)OPTM_GPOpen(g_pstGfxDevice[enLayerId]->enGPId);
#endif

#ifndef HI_BUILD_IN_BOOT
    s32Ret = OPTM_SetCallbackToDisp(g_pstGfxDevice[enLayerId]->enGPId, (IntCallBack)DRV_HIFB_ADP_UpDataCallBack, HI_DRV_DISP_C_INTPOS_90_PERCENT, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HIFB_ERROR("you should initial and open display first, open fb%d failure!\n", enLayerId);
        return HI_FAILURE;
    }

    s32Ret = OPTM_SetCallbackToDisp(g_pstGfxDevice[enLayerId]->enGPId, (IntCallBack)DRV_HIFB_ADP_FrameEndCallBack, HI_DRV_DISP_C_INTPOS_100_PERCENT, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HIFB_ERROR("fail to register FrameEndCallBack\n");
        return HI_FAILURE;
    }
#endif

    if (g_pstGfxCap[enLayerId]->bHasCmapReg != HI_FALSE)
    {
        HI_CHAR name[256] = {'\0'};
        snprintf(name, sizeof(name), "HIFB_Fb%d_Clut", enLayerId);
        name[sizeof(name) - 1] = '\0';

        if (OPTM_Adapt_AllocAndMap(name, NULL, OPTM_CMAP_SIZE, 0, &g_pstGfxDevice[enLayerId]->stCluptTable) != HI_SUCCESS)
        {
            HIFB_ERROR("GFX Get clut buffer failed!\n");
            return HI_FAILURE;
        }
        OPTM_VDP_GFX_SetLutAddr(g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->stCluptTable.u32StartPhyAddr);
    }

    g_pstGfxDevice[enLayerId]->bOpened = HI_TRUE;

    return HI_SUCCESS;
}


/***************************************************************************************
* func        : OPTM_CheckGpState
* description : CNcomment: 判断GP状态 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 OPTM_CheckGpState(OPTM_GFX_GP_E enGPId)
{
    HI_U32 i = 0;
    HI_U32 u32LayerIdSta = 0;
    HI_U32 u32LayerIdEnd = 0;

    if (OPTM_GFX_GP_0 == enGPId)
    {
        u32LayerIdSta = HIFB_LAYER_HD_0;
        u32LayerIdEnd = HIFB_LAYER_HD_3;
    }
    else if (OPTM_GFX_GP_1 == enGPId)
    {
        u32LayerIdSta = HIFB_LAYER_SD_0;
        u32LayerIdEnd = HIFB_LAYER_SD_1;
    }
    else
    {
        return OPTM_DISABLE;
    }

    for (i = u32LayerIdSta; i <= u32LayerIdEnd; i++)
    {
        if (HI_TRUE == g_pstGfxDevice[i]->bOpened)
        {
            return OPTM_ENABLE;
        }
    }

    return OPTM_DISABLE;
}


/***************************************************************************************
* func        : OPTM_GfxCloseLayer
* description : CNcomment: 关闭打开的图层 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 OPTM_GfxCloseLayer(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (HI_FALSE == g_pstGfxDevice[enLayerId]->bOpened)
    {
        return HI_SUCCESS;
    }

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
    if (OPTM_VDP_LAYER_GFX3 == g_pstGfxDevice[enLayerId]->enGfxHalId)
    {
        OPTM_VDP_OpenGFX3(HI_FALSE);
        OPTM_VDP_SetLayerConnect(OPTM_VDP_CONNECT_G3_DHD0);
    }
#endif

    OPTM_GfxSetEnable(enLayerId, HI_FALSE);
    OPTM_VDP_GFX_SetNoSecFlag(g_pstGfxDevice[enLayerId]->enGfxHalId, HI_TRUE);
    OPTM_VDP_GFX_SetRegUp(g_pstGfxDevice[enLayerId]->enGfxHalId);
    OPTM_GFX_ReleaseClutBuf(enLayerId);

    g_pstGfxDevice[enLayerId]->bExtractLine = HI_FALSE;
    g_pstGfxDevice[enLayerId]->bOpened      = HI_FALSE;

    if(!OPTM_CheckGpState(enGPId))
    {
        if (g_enOptmGfxWorkMode == HIFB_GFX_MODE_HD_WBC)
        {
            HIFB_WBC_DinitLayer(OPTM_SLAVER_LAYERID);
            OPTM_GPClose(OPTM_SLAVER_GPID);
        }
        OPTM_GPClose(enGPId);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GfxSetEnable
* description : CNcomment: 图层使能 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetEnable(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->bEnable = bEnable;
    OPTM_CheckGPMask_BYGPID(enGPId);

    OPTM_VDP_GFX_SetLayerEnable(g_pstGfxDevice[enLayerId]->enGfxHalId, bEnable);
    OPTM_VDP_GFX_SetRegUp(g_pstGfxDevice[enLayerId]->enGfxHalId);

    if (IS_MASTER_GP(enGPId))
    {
        HIFB_WBC2_SetEnable(bEnable);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetLayerAddr
* description  : CNcomment: 设置显示地址 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr)
{
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->NoCmpBufAddr = u32Addr;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetLayerAddrEX(g_pstGfxDevice[enLayerId]->enGfxHalId, u32Addr);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxGetLayerAddr
* description   : CNcomment: 获取显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GfxGetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 *pu32Addr)
{
#ifndef HI_BUILD_IN_BOOT
    OPTM_VDP_GFX_GetLayerAddr(enLayerId,pu32Addr);
#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(pu32Addr);
#endif
    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GfxSetLayerStride
* description : CNcomment: 设置图层stride CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerStride(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->Stride = (HI_U16)u32Stride;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    if (g_pstGfxGPDevice[enGPId]->bNeedExtractLine && (OPTM_CURSOR_LAYERID != enLayerId))
    {
        OPTM_VDP_GFX_SetLayerStride(g_pstGfxDevice[enLayerId]->enGfxHalId, (u32Stride * 2));
    }
    else
    {
        OPTM_VDP_GFX_SetLayerStride(g_pstGfxDevice[enLayerId]->enGfxHalId, u32Stride);
    }

    return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func        : OPTM_HalFmtTransferToPixerFmt
* description : CNcomment: 由VDP像素格式转换成hifb像素格式 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HIFB_COLOR_FMT_E OPTM_HalFmtTransferToPixerFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
    HIFB_COLOR_FMT_E ePixFmt = HIFB_FMT_BUTT;

    ePixFmt = OPTM_ClutHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_XYCbCrHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_RGBHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    ePixFmt = OPTM_XRGBHalFmtTransferToPixFmt(enDataFmt);
    if (HIFB_FMT_BUTT != ePixFmt)
    {
        return ePixFmt;
    }

    return HIFB_FMT_BUTT;
}

static inline HIFB_COLOR_FMT_E OPTM_ClutHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch (enDataFmt)
     {
         case VDP_GFX_IFMT_CLUT_1BPP:
            return HIFB_FMT_1BPP;
         case VDP_GFX_IFMT_CLUT_2BPP:
            return HIFB_FMT_2BPP;
         case VDP_GFX_IFMT_CLUT_4BPP:
            return HIFB_FMT_4BPP;
         case VDP_GFX_IFMT_CLUT_8BPP:
            return HIFB_FMT_8BPP;
         case VDP_GFX_IFMT_ACLUT_44:
            return HIFB_FMT_ACLUT44;
         case VDP_GFX_IFMT_ACLUT_88:
            return HIFB_FMT_ACLUT88;
         default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_RGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch (enDataFmt)
     {
         case VDP_GFX_IFMT_RGB_565:
            return HIFB_FMT_RGB565;
         case VDP_GFX_IFMT_RGB_888:
            return HIFB_FMT_RGB888;
         default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_XRGBHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch(enDataFmt)
     {
        case VDP_GFX_IFMT_RGB_444:
           return HIFB_FMT_KRGB444;
        case VDP_GFX_IFMT_RGB_555:
           return HIFB_FMT_KRGB555;
        case VDP_GFX_IFMT_ARGB_8565:
           return HIFB_FMT_ARGB8565;
        case VDP_GFX_IFMT_KRGB_888:
           return HIFB_FMT_KRGB888;
        case VDP_GFX_IFMT_ARGB_8888:
            return HIFB_FMT_ARGB8888;
        case VDP_GFX_IFMT_ARGB_4444:
            return HIFB_FMT_ARGB4444;
        case VDP_GFX_IFMT_ARGB_1555:
            return HIFB_FMT_ARGB1555;
        case VDP_GFX_IFMT_RGBA_4444:
            return HIFB_FMT_RGBA4444;
        case VDP_GFX_IFMT_RGBA_5551:
            return HIFB_FMT_RGBA5551;
        case VDP_GFX_IFMT_RGBA_5658:
            return HIFB_FMT_RGBA5658;
        case VDP_GFX_IFMT_RGBA_8888:
            return HIFB_FMT_RGBA8888;
        default:
            return HIFB_FMT_BUTT;
     }
}

static inline HIFB_COLOR_FMT_E OPTM_XYCbCrHalFmtTransferToPixFmt(OPTM_VDP_GFX_IFMT_E enDataFmt)
{
     switch(enDataFmt)
     {
         case VDP_GFX_IFMT_PKG_UYVY:
            return HIFB_FMT_PUYVY;
         case VDP_GFX_IFMT_PKG_YUYV:
            return HIFB_FMT_PYUYV;
         case VDP_GFX_IFMT_PKG_YVYU:
            return HIFB_FMT_PYVYU;
         case VDP_GFX_IFMT_YCBCR_888:
            return HIFB_FMT_YUV888;
         case VDP_GFX_IFMT_AYCBCR_8888:
            return HIFB_FMT_AYUV8888;
         case VDP_GFX_IFMT_YCBCRA_8888:
            return HIFB_FMT_YUVA8888;
         default:
            return HIFB_FMT_BUTT;
     }
}
#endif

/***************************************************************************************
* func          : OPTM_PixerFmtTransferToHalFmt
* description   : CNcomment: 由hifb像素格式转换成图形层像素格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
OPTM_VDP_GFX_IFMT_E OPTM_PixerFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    OPTM_VDP_GFX_IFMT_E eHalFmt = VDP_GFX_IFMT_BUTT;

    eHalFmt = OPTM_ClutPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_XRGBPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_RGBPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    eHalFmt = OPTM_XYCbCrPixFmtTransferToHalFmt(enDataFmt);
    if (VDP_GFX_IFMT_BUTT != eHalFmt)
    {
        return eHalFmt;
    }

    return VDP_GFX_IFMT_BUTT;
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_ClutPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch (enDataFmt)
     {
        case HIFB_FMT_1BPP:
            return VDP_GFX_IFMT_CLUT_1BPP;
        case HIFB_FMT_2BPP:
            return VDP_GFX_IFMT_CLUT_2BPP;
        case HIFB_FMT_4BPP:
            return VDP_GFX_IFMT_CLUT_4BPP;
        case HIFB_FMT_8BPP:
            return VDP_GFX_IFMT_CLUT_8BPP;
        case HIFB_FMT_ACLUT44:
            return VDP_GFX_IFMT_ACLUT_44;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}


static inline OPTM_VDP_GFX_IFMT_E OPTM_RGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch (enDataFmt)
     {
        case HIFB_FMT_KRGB444:
           return VDP_GFX_IFMT_RGB_444;
        case HIFB_FMT_KRGB555:
           return VDP_GFX_IFMT_RGB_555;
        case HIFB_FMT_RGB565:
            return VDP_GFX_IFMT_RGB_565;
        case HIFB_FMT_RGB888:
           return VDP_GFX_IFMT_RGB_888;
        case HIFB_FMT_YUV888:
           return VDP_GFX_IFMT_YCBCR_888;
        case HIFB_FMT_KRGB888:
           return VDP_GFX_IFMT_KRGB_888;
        case HIFB_FMT_BGR565:
            return VDP_GFX_IFMT_RGB_565;
        case HIFB_FMT_BGR888:
            return VDP_GFX_IFMT_RGB_888;
        case HIFB_FMT_KBGR444:
            return VDP_GFX_IFMT_RGB_444;
        case HIFB_FMT_KBGR555:
            return VDP_GFX_IFMT_RGB_555;
        case HIFB_FMT_KBGR888:
            return VDP_GFX_IFMT_KRGB_888;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_XRGBPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch (enDataFmt)
     {
        case HIFB_FMT_ARGB8888:
            return VDP_GFX_IFMT_ARGB_8888;
        case HIFB_FMT_ARGB4444:
            return VDP_GFX_IFMT_ARGB_4444;
        case HIFB_FMT_ARGB1555:
            return VDP_GFX_IFMT_ARGB_1555;
        case HIFB_FMT_RGBA4444:
            return VDP_GFX_IFMT_RGBA_4444;
        case HIFB_FMT_RGBA5551:
            return VDP_GFX_IFMT_RGBA_5551;
        case HIFB_FMT_RGBA5658:
            return VDP_GFX_IFMT_RGBA_5658;
        case HIFB_FMT_RGBA8888:
            return VDP_GFX_IFMT_RGBA_8888;
        case HIFB_FMT_ABGR4444:
            return VDP_GFX_IFMT_ARGB_4444;
        case HIFB_FMT_ABGR1555:
            return VDP_GFX_IFMT_ARGB_1555;
        case HIFB_FMT_ABGR8888:
            return VDP_GFX_IFMT_ABGR_8888;
        case HIFB_FMT_ABGR8565:
            return VDP_GFX_IFMT_ARGB_8565;
        case HIFB_FMT_ARGB8565:
            return VDP_GFX_IFMT_ARGB_8565;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}

static inline OPTM_VDP_GFX_IFMT_E OPTM_XYCbCrPixFmtTransferToHalFmt(HIFB_COLOR_FMT_E enDataFmt)
{
     switch (enDataFmt)
     {
        case HIFB_FMT_PUYVY:
            return VDP_GFX_IFMT_PKG_UYVY;
        case HIFB_FMT_PYUYV:
            return VDP_GFX_IFMT_PKG_YUYV;
        case HIFB_FMT_PYVYU:
            return VDP_GFX_IFMT_PKG_YVYU;
        case HIFB_FMT_ACLUT88:
           return VDP_GFX_IFMT_ACLUT_88;
        case HIFB_FMT_YUVA8888:
            return VDP_GFX_IFMT_YCBCRA_8888;
        case HIFB_FMT_AYUV8888:
            return VDP_GFX_IFMT_AYCBCR_8888;
        default:
            return VDP_GFX_IFMT_BUTT;
     }
}

/***************************************************************************************
* func        : OPTM_GfxSetLayerDataFmt
* description : CNcomment: 设置图层格式 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerDataFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt)
{
    HI_S32 Ret = HI_SUCCESS;
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    HIFB_CHECK_ARRAY_OVER_RETURN(enDataFmt, HIFB_FMT_BUTT, HI_FAILURE);
    if (HI_FALSE == g_pstGfxCap[enLayerId]->bColFmt[enDataFmt])
    {
        HIFB_ERROR("unSupport color format.\n");
        return HI_FAILURE;
    }

    g_pstGfxDevice[enLayerId]->enDataFmt = enDataFmt;

    OPTM_CheckGPMask_BYGPID(enGPId);

    if (   (HIFB_FMT_ABGR8888 != enDataFmt)
        && ((enDataFmt >= HIFB_FMT_BGR565) && (HIFB_FMT_KBGR888 >= enDataFmt))
        && (g_pstGfxDevice[enLayerId]->CscState == OPTM_CSC_SET_PARA_RGB))
    {
        Ret = HIFB_ADP_SetLayerDataBigEndianFmt(enLayerId);
    }
    else if (  ((HIFB_FMT_ABGR8888 == enDataFmt) || (HIFB_FMT_BGR565 > enDataFmt || enDataFmt > HIFB_FMT_KBGR888))
            && (g_pstGfxDevice[enLayerId]->CscState == OPTM_CSC_SET_PARA_BGR))
    {
        Ret = HIFB_ADP_SetLayerDataLittleEndianFmt(enLayerId);
    }

    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    OPTM_VDP_GFX_SetInDataFmt(g_pstGfxDevice[enLayerId]->enGfxHalId,OPTM_PixerFmtTransferToHalFmt(enDataFmt));

    return HI_SUCCESS;
}

static inline HI_S32 HIFB_ADP_SetLayerDataBigEndianFmt(HIFB_LAYER_ID_E enLayerId)
{
     HI_S32 s32Cnt = 0;
     HI_U32 u32LayerCount = 0;
     OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

     HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
     enGPId = g_pstGfxDevice[enLayerId]->enGPId;
     HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

     u32LayerCount = (HIFB_LAYER_HD_3 >= enLayerId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

     for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
     {
         if ((s32Cnt != enLayerId) && (g_pstGfxDevice[s32Cnt]->bEnable) && (g_pstGfxDevice[s32Cnt]->CscState != OPTM_CSC_SET_PARA_BGR))
         {
             HIFB_ERROR("fail to set color format.\n");
             return HI_FAILURE;
         }
     }

     g_pstGfxDevice[enLayerId]->CscState = OPTM_CSC_SET_PARA_BGR;
     g_pstGfxGPDevice[enGPId]->bBGRState = HI_TRUE;

     OPTM_GPSetCsc(enGPId,  &g_pstGfxGPDevice[enGPId]->stCscPara, HI_TRUE);

     if (IS_MASTER_GP(enGPId))
     {
         OPTM_GPSetCsc(OPTM_SLAVER_GPID,  &g_pstGfxGPDevice[OPTM_SLAVER_GPID]->stCscPara, HI_TRUE);
         g_pstGfxGPDevice[OPTM_SLAVER_GPID]->bBGRState = HI_TRUE;
     }

     return HI_SUCCESS;
}

static inline HI_S32 HIFB_ADP_SetLayerDataLittleEndianFmt(HIFB_LAYER_ID_E enLayerId)
{
     HI_S32 s32Cnt = 0;
     HI_U32 u32LayerCount = 0;
     OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

     HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
     enGPId = g_pstGfxDevice[enLayerId]->enGPId;
     HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

     u32LayerCount = (HIFB_LAYER_HD_3 >= enLayerId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

     for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
     {
         if ( (s32Cnt != enLayerId) && (g_pstGfxDevice[s32Cnt]->bEnable) && (g_pstGfxDevice[s32Cnt]->CscState != OPTM_CSC_SET_PARA_RGB))
         {
             HIFB_ERROR("fail to set color format.\n");
             return HI_FAILURE;
         }
     }

     g_pstGfxDevice[enLayerId]->CscState = OPTM_CSC_SET_PARA_RGB;
     g_pstGfxGPDevice[enGPId]->bBGRState = HI_FALSE;

     OPTM_GPSetCsc(enGPId, &g_pstGfxGPDevice[enGPId]->stCscPara, HI_FALSE);

     if(IS_MASTER_GP(enGPId))
     {
         OPTM_GPSetCsc(OPTM_SLAVER_GPID,  &g_pstGfxGPDevice[OPTM_SLAVER_GPID]->stCscPara, HI_FALSE);
         g_pstGfxGPDevice[OPTM_SLAVER_GPID]->bBGRState = HI_FALSE;
     }

     return HI_SUCCESS;
}


/***************************************************************************************
* func         : OPTM_GFX_SetClutColorReg
* description  : CNcomment: 设置调色板颜色寄存器 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GFX_SetClutColorReg(HIFB_LAYER_ID_E enLayerId, HI_U32 u32OffSet, HI_U32 u32Color, HI_S32 UpFlag)
{
    HI_U32 *pCTab = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    pCTab = (HI_U32 *)(g_pstGfxDevice[enLayerId]->stCluptTable.pu8StartVirAddr);
    HIFB_CHECK_NULLPOINTER_RETURN(pCTab, HI_FAILURE);

    HIFB_CHECK_ARRAY_OVER_RETURN(u32OffSet, OPTM_CMAP_SIZE, HI_FAILURE);
    pCTab[u32OffSet] = u32Color;

    if (UpFlag != 0)
    {
        OPTM_VDP_GFX_SetParaUpd(g_pstGfxDevice[enLayerId]->enGfxHalId,VDP_DISP_COEFMODE_LUT);
    }

    return HI_SUCCESS;
}


#ifdef OPTM_HIFB_WVM_ENABLE
/***************************************************************************************
* func        : OPTM_GfxWVBCallBack
* description : CNcomment: 等中断完成 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_VOID OPTM_GfxWVBCallBack(HI_U32 enLayerId)
{
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);

    if (HI_FALSE == g_pstGfxDevice[enLayerId]->bOpened)
    {
        return;
    }

    g_pstGfxDevice[enLayerId]->vblflag = 1;
    wake_up_interruptible(&(g_pstGfxDevice[enLayerId]->vblEvent));

    return;
}

/***************************************************************************************
* func         : OPTM_GfxWaitVBlank
* description  : CNcomment: 等中断 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxWaitVBlank(HIFB_LAYER_ID_E enLayerId)
{
    HI_U32 u32TimeOutMs = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    HIFB_CHECK_LAYER_OPEN(enLayerId);

    u32TimeOutMs = (200 * HZ)/1000;

    g_pstGfxDevice[enLayerId]->vblflag = 0;
    s32Ret = wait_event_interruptible_timeout(g_pstGfxDevice[enLayerId]->vblEvent, g_pstGfxDevice[enLayerId]->vblflag, u32TimeOutMs);
    if (s32Ret <= 0)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#else

HI_S32 OPTM_GfxWaitVBlank(HIFB_LAYER_ID_E enLayerId)
{
    HI_UNUSED(enLayerId);
    return HI_FAILURE;
}

#endif

/***************************************************************************************
* func        : OPTM_GfxSetLayerDeFlicker
* description : CNcomment: 设置图层抗闪，不支持 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetLayerDeFlicker(HIFB_LAYER_ID_E enLayerId, HIFB_DEFLICKER_S *pstDeFlicker)
{
    HI_UNUSED(enLayerId);
    HI_UNUSED(pstDeFlicker);
    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetLayerAlpha
* description  : CNcomment: 设置图层alpha CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerAlpha(HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha)
{
    HIFB_CHECK_NULLPOINTER_RETURN(pstAlpha, HI_FAILURE);
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    HI_GFX_Memcpy(&g_pstGfxDevice[enLayerId]->stAlpha, pstAlpha, sizeof(HIFB_ALPHA_S));

    /** 是否已经开机过渡完 **/
    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetPalpha(g_pstGfxDevice[enLayerId]->enGfxHalId,pstAlpha->bAlphaEnable,HI_TRUE,pstAlpha->u8Alpha0,pstAlpha->u8Alpha1);
    OPTM_VDP_GFX_SetLayerGalpha(g_pstGfxDevice[enLayerId]->enGfxHalId, pstAlpha->u8GlobalAlpha);

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GfxGetLayerRect
* description : CNcomment: 获取图层输入分辨率 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static HI_S32 OPTM_GfxGetLayerRect(HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstRect)
{
    HIFB_CHECK_NULLPOINTER_RETURN(pstRect, HI_FAILURE);
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    HI_GFX_Memcpy(pstRect, &g_pstGfxDevice[enLayerId]->stInRect, sizeof(HIFB_RECT));

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxSetLayerRect
* description   : CNcomment: 设置图层输入矩形 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetLayerRect(HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstRect)
{
    HI_S32 Ret = HI_SUCCESS;
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;
    OPTM_VDP_DISP_RECT_S stGfxRect;

    HIFB_CHECK_NULLPOINTER_RETURN(pstRect, HI_FAILURE);
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    enGpId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->stInRect.x = pstRect->x;
    g_pstGfxDevice[enLayerId]->stInRect.y = pstRect->y;
    g_pstGfxDevice[enLayerId]->stInRect.w = pstRect->w;
    g_pstGfxDevice[enLayerId]->stInRect.h = pstRect->h;

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  g_pstGfxDevice[enLayerId]->stInRect.w, g_pstGfxDevice[enLayerId]->stInRect.h, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT,
                                  g_pstGfxDevice[enLayerId]->stInRect.x, g_pstGfxDevice[enLayerId]->stInRect.y, 0, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    OPTM_CheckGPMask_BYLayerID(enLayerId);
#if 0
    if (OPTM_CURSOR_LAYERID == enLayerId)
    {/**
      **硬件鼠标层，配置鼠标区域
      **/
        return OPTM_GfxConfigCursorRect(enLayerId, pstRect);
    }
#endif

    HI_GFX_Memset(&stGfxRect, 0, sizeof(stGfxRect));

    stGfxRect.u32VX   = g_pstGfxDevice[enLayerId]->stInRect.x;
    stGfxRect.u32DXS  = g_pstGfxDevice[enLayerId]->stInRect.x;
    stGfxRect.u32VY   = g_pstGfxDevice[enLayerId]->stInRect.y;
    stGfxRect.u32DYS  = g_pstGfxDevice[enLayerId]->stInRect.y;
    stGfxRect.u32IWth = g_pstGfxDevice[enLayerId]->stInRect.w;
    stGfxRect.u32IHgt = g_pstGfxDevice[enLayerId]->stInRect.h;

    HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(g_pstGfxCap[enLayerId]->u32MinWidth,  g_pstGfxGPDevice[enGpId]->stInRect.s32Width, HI_FAILURE);
    if (g_pstGfxDevice[enLayerId]->stInRect.x > g_pstGfxGPDevice[enGpId]->stInRect.s32Width - g_pstGfxCap[enLayerId]->u32MinWidth)
    {
        g_pstGfxDevice[enLayerId]->stInRect.x = g_pstGfxGPDevice[enGpId]->stInRect.s32Width - g_pstGfxCap[enLayerId]->u32MinWidth;
    }

    HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(g_pstGfxCap[enLayerId]->u32MinHeight, g_pstGfxGPDevice[enGpId]->stInRect.s32Height, HI_FAILURE);
    if (g_pstGfxDevice[enLayerId]->stInRect.y > g_pstGfxGPDevice[enGpId]->stInRect.s32Height - g_pstGfxCap[enLayerId]->u32MinHeight)
    {
        g_pstGfxDevice[enLayerId]->stInRect.y = g_pstGfxGPDevice[enGpId]->stInRect.s32Height - g_pstGfxCap[enLayerId]->u32MinHeight;
    }

    if (!IS_SLAVER_GP(enGpId))
    {
        HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(g_pstGfxDevice[enLayerId]->stInRect.x, g_pstGfxGPDevice[enGpId]->stInRect.s32Width, HI_FAILURE);
        if ((g_pstGfxDevice[enLayerId]->stInRect.x + g_pstGfxDevice[enLayerId]->stInRect.w) > g_pstGfxGPDevice[enGpId]->stInRect.s32Width)
        {
            stGfxRect.u32IWth = g_pstGfxGPDevice[enGpId]->stInRect.s32Width - g_pstGfxDevice[enLayerId]->stInRect.x;
        }

        HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(g_pstGfxDevice[enLayerId]->stInRect.y, g_pstGfxGPDevice[enGpId]->stInRect.s32Height, HI_FAILURE);
        if ((g_pstGfxDevice[enLayerId]->stInRect.y + g_pstGfxDevice[enLayerId]->stInRect.h) > g_pstGfxGPDevice[enGpId]->stInRect.s32Height)
        {
            stGfxRect.u32IHgt = g_pstGfxGPDevice[enGpId]->stInRect.s32Height - g_pstGfxDevice[enLayerId]->stInRect.y;
        }
    }

    if (g_pstGfxGPDevice[enGpId]->bNeedExtractLine)
    {/** 是否抽行处理 **/
        stGfxRect.u32IHgt /= 2;
        stGfxRect.u32VY   /= 2;
        stGfxRect.u32DYS  /= 2;
        g_pstGfxDevice[enLayerId]->bExtractLine = HI_TRUE;
        OPTM_VDP_GFX_SetLayerStride(g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->Stride * 2);
    }
    else if (HI_TRUE == g_pstGfxDevice[enLayerId]->bExtractLine)
    {
        OPTM_GfxSetLayerStride(enLayerId, g_pstGfxDevice[enLayerId]->Stride);
        g_pstGfxDevice[enLayerId]->bExtractLine = HI_FALSE;
    }


    stGfxRect.u32OWth = stGfxRect.u32IWth;
    stGfxRect.u32OHgt = stGfxRect.u32IHgt;
    stGfxRect.u32DXL  = g_pstGfxDevice[enLayerId]->stInRect.x + stGfxRect.u32OWth;
    stGfxRect.u32DYL  = g_pstGfxDevice[enLayerId]->stInRect.y + stGfxRect.u32OHgt;

    /*************************************/
    if ( (g_enOptmGfxWorkMode == HIFB_GFX_MODE_NORMAL) && (enGpId == OPTM_GFX_GP_1))
    {
        stGfxRect.u32DXS = 0;
        stGfxRect.u32DYS = 0;
        stGfxRect.u32DXL = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
        stGfxRect.u32DYL = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;

        if (g_pstGfxGPDevice[enGpId]->bNeedExtractLine)
        {
            stGfxRect.u32DYL /= 2;
        }
    }
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    if ((HIFB_STEREO_SIDEBYSIDE_HALF == g_pstGfxDevice[enLayerId]->enTriDimMode) || (HIFB_STEREO_TOPANDBOTTOM == g_pstGfxDevice[enLayerId]->enTriDimMode))
    {
        stGfxRect.u32DXS = 0;
        stGfxRect.u32DYS = 0;
        stGfxRect.u32DXL = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
        stGfxRect.u32DYL = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;
    }

    if (HIFB_STEREO_SIDEBYSIDE_HALF == g_pstGfxDevice[enLayerId]->enTriDimMode)
    {
        stGfxRect.u32IWth = stGfxRect.u32IWth/2;
        stGfxRect.u32IWth &= 0xfffffffe;
        stGfxRect.u32OWth = (stGfxRect.u32IWth)*2;
    }
    else if (HIFB_STEREO_TOPANDBOTTOM == g_pstGfxDevice[enLayerId]->enTriDimMode)
    {
        stGfxRect.u32IHgt = stGfxRect.u32IHgt/2;
        stGfxRect.u32IHgt &= 0xfffffffe;
        stGfxRect.u32OHgt = (stGfxRect.u32IHgt)*2;
    }
#endif
    if(OPTM_CURSOR_LAYERID != enLayerId){
        /** cursor support odd size **/
        stGfxRect.u32VX   &= 0xfffffffe;
        stGfxRect.u32VY   &= 0xfffffffe;
        stGfxRect.u32DXS  &= 0xfffffffe;
        stGfxRect.u32DYS  &= 0xfffffffe;
        stGfxRect.u32DXL  &= 0xfffffffe;
        stGfxRect.u32DYL  &= 0xfffffffe;
        stGfxRect.u32IWth &= 0xfffffffe;
        stGfxRect.u32IHgt &= 0xfffffffe;
        stGfxRect.u32OWth &= 0xfffffffe;
        stGfxRect.u32OHgt &= 0xfffffffe;
    }

    OPTM_VDP_GFX_SetLayerReso(g_pstGfxDevice[enLayerId]->enGfxHalId, &stGfxRect);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_GfxGetDispFMTSize
* description   : CNcomment: 获取disp大小 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GfxGetDispFMTSize(HIFB_LAYER_ID_E LayerId, HIFB_RECT *pstOutRect)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_BUTT;

    HIFB_CHECK_NULLPOINTER_RETURN(pstOutRect, HI_FAILURE);
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, HI_FAILURE);
    enGpId = OPTM_GFX_GetGpId(LayerId);

    pstOutRect->x = g_pstGfxGPDevice[enGpId]->stOutRect.s32X;
    pstOutRect->y = g_pstGfxGPDevice[enGpId]->stOutRect.s32Y;
    pstOutRect->w = g_pstGfxGPDevice[enGpId]->stOutRect.s32Width;
    pstOutRect->h = g_pstGfxGPDevice[enGpId]->stOutRect.s32Height;

    if (pstOutRect->w == 0 || pstOutRect->h == 0)
    {
        pstOutRect->x = 0;
        pstOutRect->y = 0;
        pstOutRect->w = 1280;
        pstOutRect->h = 720;
    }

    if (pstOutRect->w == 1440 && (pstOutRect->h == 576 || pstOutRect->h == 480))
    {
        pstOutRect->w /= 2;
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetDispFMTSize
* description  : CNcomment: 设置display像素格式和大小 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxSetDispFMTSize(OPTM_GFX_GP_E enGpId, const HI_RECT_S *pstOutRect)
{
#ifndef CONFIG_HIFB_EXTRACE_DISABLE
    HI_U32    u32Ratio    = 0;
#endif
    HIFB_RECT stInputRect = {0};

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstOutRect, HI_FAILURE);

    if (pstOutRect->s32X < 0 || pstOutRect->s32Y < 0)
    {
        return HI_FAILURE;
    }

    if (pstOutRect->s32Width <= 0 || pstOutRect->s32Height <= 0)
    {
        return HI_FAILURE;
    }

    g_pstGfxGPDevice[enGpId]->stOutRect.s32X      = pstOutRect->s32X;
    g_pstGfxGPDevice[enGpId]->stOutRect.s32Y      = pstOutRect->s32Y;
    g_pstGfxGPDevice[enGpId]->stOutRect.s32Width  = pstOutRect->s32Width;
    g_pstGfxGPDevice[enGpId]->stOutRect.s32Height = pstOutRect->s32Height;

    OPTM_CheckGPMask_BYGPID(enGpId);

    stInputRect.x = g_pstGfxGPDevice[enGpId]->stInRect.s32X;
    stInputRect.y = g_pstGfxGPDevice[enGpId]->stInRect.s32Y;
    stInputRect.w = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
    stInputRect.h = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;

#ifndef CONFIG_HIFB_EXTRACE_DISABLE
    /*judge wether need to extract line for layer or not*/
    u32Ratio =  g_pstGfxGPDevice[enGpId]->stInRect.s32Height * 2;
    u32Ratio /= g_pstGfxGPDevice[enGpId]->stOutRect.s32Height;

    if (g_pstGfxGPDevice[enGpId]->bInterface)
    {
        //u32Ratio *= 2;
    }
    /**
     ** 是否需要抽行处理只和性能有关
     ** 比如3840 * 2560(IN) 1280 * 720(OUT) 2560 / 720 > 3
     **/
    if (u32Ratio >= OPTM_EXTRACTLINE_RATIO && !IS_SLAVER_GP(enGpId))
    {
        g_pstGfxGPDevice[enGpId]->bNeedExtractLine = HI_TRUE;
    }
    else
    {
        g_pstGfxGPDevice[enGpId]->bNeedExtractLine = HI_FALSE;
    }
#endif

    if (stInputRect.w && stInputRect.h)
    {
        OPTM_GfxSetGpRect(enGpId, &stInputRect);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GfxSetGpRect
* description : CNcomment: 设置GP RECT CNend\n
*                    (1)回写更新需要设置GP寄存器
                      (2)显示制式发生变化的时候
                      (3)输入分辨率发生变化的时候
                      (4)待机打开图层需要重新配置GP
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
#ifndef CONFIG_GFX_PQ
#define SHARPEN_RATIO        3
#define SHARPEN_MAX_WIDTH    1920
HI_S32 OPTM_GfxSetGpRect(OPTM_GFX_GP_E enGpId, const HIFB_RECT * pstInputRect)
{
    HI_BOOL bGfxSharpen = HI_FALSE;
    OPTM_VDP_DISP_RECT_S stGfxRect        = {0};
    OPTM_ALG_GZME_DRV_PARA_S stZmeDrvPara = {0};
    OPTM_ALG_GZME_RTL_PARA_S stZmeRtlPara = {0};
    OPTM_ALG_GDTI_DRV_PARA_S stDtiDrvPara = {0};
    OPTM_ALG_GDTI_RTL_PARA_S stDtiRtlPara = {0};

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstInputRect, HI_FAILURE);

    g_pstGfxGPDevice[enGpId]->stInRect.s32Width  = pstInputRect->w;
    g_pstGfxGPDevice[enGpId]->stInRect.s32Height = pstInputRect->h;

    OPTM_CheckGPMask_BYGPID(enGpId);

    stGfxRect.u32IWth = g_pstGfxGPDevice[enGpId]->stInRect.s32Width   & 0xfffffffe;
    stGfxRect.u32IHgt = g_pstGfxGPDevice[enGpId]->stInRect.s32Height  & 0xfffffffe;
    stGfxRect.u32OWth = g_pstGfxGPDevice[enGpId]->stOutRect.s32Width  & 0xfffffffe;
    stGfxRect.u32OHgt = g_pstGfxGPDevice[enGpId]->stOutRect.s32Height & 0xfffffffe;

    stGfxRect.u32DXS  = g_pstGfxGPDevice[enGpId]->stOutRect.s32X & 0xfffffffe;
    stGfxRect.u32DYS  = g_pstGfxGPDevice[enGpId]->stOutRect.s32Y & 0xfffffffe;

    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OWth,stGfxRect.u32DXS,HI_FAILURE);
    stGfxRect.u32DXL  = stGfxRect.u32OWth + stGfxRect.u32DXS;
    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OHgt,stGfxRect.u32DYS,HI_FAILURE);
    stGfxRect.u32DYL  = stGfxRect.u32OHgt + stGfxRect.u32DYS;

    stGfxRect.u32VX   = stGfxRect.u32DXS;
    stGfxRect.u32VY   = stGfxRect.u32DYS;

    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OWth,stGfxRect.u32VX,HI_FAILURE);
    stGfxRect.u32VXL  = stGfxRect.u32OWth + stGfxRect.u32VX;
    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OHgt,stGfxRect.u32VY,HI_FAILURE);
    stGfxRect.u32VYL  = stGfxRect.u32OHgt + stGfxRect.u32VY;

    if ((stGfxRect.u32IWth == 0) || (stGfxRect.u32IHgt == 0) || (stGfxRect.u32OWth == 0) || (stGfxRect.u32OHgt == 0))
    {
        return HI_SUCCESS;
    }

    if (g_pstGfxGPDevice[enGpId]->bNeedExtractLine == HI_TRUE)
    {
        stGfxRect.u32IHgt /= 2;
    }

    OPTM_VDP_GP_SetLayerReso(enGpId, &stGfxRect);

    /**
     ** Frame format for zme : 0-field; 1-frame
     **/
    stZmeDrvPara.bZmeFrmFmtIn  = HI_TRUE;
    stZmeDrvPara.bZmeFrmFmtOut = g_pstGfxGPDevice[enGpId]->bInterface ? HI_FALSE : HI_TRUE;

    if (IS_SLAVER_GP(enGpId))
    {/** 回写模式并且打开的是标清层 **/
        stGfxRect.u32IWth  = g_stGfxWbc2.stInRect.w & 0xfffffffe;
        stGfxRect.u32IHgt  = g_stGfxWbc2.stInRect.h & 0xfffffffe;

        if (stGfxRect.u32IWth == 0 || stGfxRect.u32IHgt == 0)
        {
            return HI_SUCCESS;
        }

        /*in wbc work mode, slavery channel show 2D image*/
        if (HIFB_STEREO_SIDEBYSIDE_HALF == g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode)
        {
            stGfxRect.u32IWth /= 2;
        }
        else if (HIFB_STEREO_TOPANDBOTTOM == g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode)
        {
            stGfxRect.u32IHgt /= 2;
        }

        if ((g_pstGfxGPDevice[OPTM_MASTER_GPID]->bNeedExtractLine == HI_TRUE))
        {
            stGfxRect.u32IHgt /= 2;
        }

        HIFB_WBC2_SetCropReso(stGfxRect);

    }

    stZmeDrvPara.u32ZmeFrmWIn  = stGfxRect.u32IWth;
    stZmeDrvPara.u32ZmeFrmHIn  = stGfxRect.u32IHgt;
    stZmeDrvPara.u32ZmeFrmWOut = stGfxRect.u32OWth;
    stZmeDrvPara.u32ZmeFrmHOut = stGfxRect.u32OHgt;

    if (OPTM_DISPCHANNEL_1 == g_pstGfxGPDevice[enGpId]->enDispCh)
    {
        stZmeDrvPara.u32ZmeHdDeflicker = g_pstGfxGPDevice[enGpId]->u32ZmeDeflicker;
        OPTM_ALG_GZmeHDSet(&gs_stGPZme, &stZmeDrvPara, &stZmeRtlPara);
    }
    else if (OPTM_DISPCHANNEL_0 == g_pstGfxGPDevice[enGpId]->enDispCh)
    {
        HIFB_WBC2_SetPreZmeEn(&stZmeDrvPara);
        stZmeDrvPara.u32ZmeSdDeflicker = g_pstGfxGPDevice[enGpId]->u32ZmeDeflicker;
        OPTM_ALG_GZmeSDSet(&gs_stGPZme, &stZmeDrvPara, &stZmeRtlPara);
    }
    else
    {
        return HI_FAILURE;
    }

    stDtiDrvPara.u32ZmeFrmWIn  = stGfxRect.u32IWth;
    stDtiDrvPara.u32ZmeFrmHIn  = stGfxRect.u32IHgt;
    stDtiDrvPara.u32ZmeFrmWOut = stGfxRect.u32OWth;
    stDtiDrvPara.u32ZmeFrmHOut = stGfxRect.u32OHgt;

    OPTM_ALG_GDtiSet(&stDtiDrvPara, &stDtiRtlPara);

    if (stZmeDrvPara.u32ZmeFrmWIn > SHARPEN_MAX_WIDTH)
    {
        stZmeRtlPara.bZmeEnH = HI_FALSE;
        stZmeRtlPara.bZmeEnV = HI_FALSE;
    }

    /*zme enable horizontal*/
    OPTM_VDP_GP_SetZmeEnable(enGpId, VDP_ZME_MODE_HOR, stZmeRtlPara.bZmeEnH);
    OPTM_VDP_GP_SetZmeEnable(enGpId, VDP_ZME_MODE_VER, stZmeRtlPara.bZmeEnV);

    if (stZmeRtlPara.bZmeEnH && stZmeRtlPara.bZmeEnV)
    {
          bGfxSharpen = HI_TRUE;
    }

    HIFB_CHECK_EQUAL_RETURN(0, stDtiDrvPara.u32ZmeFrmWOut, HI_FAILURE);
    HIFB_CHECK_EQUAL_RETURN(0, stDtiDrvPara.u32ZmeFrmHOut, HI_FAILURE);
    if (   (stDtiDrvPara.u32ZmeFrmWIn * 2 / stDtiDrvPara.u32ZmeFrmWOut > SHARPEN_RATIO) \
        || (stDtiDrvPara.u32ZmeFrmHIn * 2/ stDtiDrvPara.u32ZmeFrmHOut > SHARPEN_RATIO))
    {
        bGfxSharpen = HI_FALSE;
    }

    HIFB_ADP_SetZme(enGpId,bGfxSharpen,&stZmeRtlPara,&stDtiRtlPara);

    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_HOR);
    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_VER);

    HIFB_ADP_ResetLayerInRect(enGpId);

    return HI_SUCCESS;
}

static inline HI_VOID HIFB_ADP_SetZme(OPTM_GFX_GP_E enGpId, HI_BOOL bGfxSharpen, OPTM_ALG_GZME_RTL_PARA_S *pstZmeRtlPara, OPTM_ALG_GDTI_RTL_PARA_S *pstDtiRtlPara)
{
    HI_BOOL  bSlvGp = HI_FALSE;

    if (IS_SLAVER_GP(enGpId))
    {
       bSlvGp  = HI_TRUE;
    }

    HIFB_CHECK_NULLPOINTER_UNRETURN(pstZmeRtlPara);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstDtiRtlPara);

    if ((HI_FALSE == pstZmeRtlPara->bZmeEnH) && (HI_FALSE == pstZmeRtlPara->bZmeEnV))
    {
        OPTM_VDP_GP_SetTiEnable       (enGpId, VDP_TI_MODE_CHM, HI_FALSE);
        OPTM_VDP_GP_SetTiEnable       (enGpId, VDP_TI_MODE_LUM, HI_FALSE);
        OPTM_VDP_GP_SetIpOrder        (enGpId, bSlvGp, VDP_GP_ORDER_CSC);
        return;
    }

    OPTM_VDP_GP_SetIpOrder            (enGpId, bSlvGp, VDP_GP_ORDER_ZME_CSC);
    OPTM_VDP_GP_SetZmeHfirOrder       (enGpId, VDP_ZME_ORDER_HV);
    OPTM_VDP_GP_SetZmeCoefAddr        (enGpId, VDP_GP_PARA_ZME_HOR, pstZmeRtlPara->u32ZmeCoefAddrHL);
    OPTM_VDP_GP_SetZmeFirEnable       (enGpId, VDP_ZME_MODE_HOR,    pstZmeRtlPara->bZmeMdHLC);
    OPTM_VDP_GP_SetZmeFirEnable       (enGpId, VDP_ZME_MODE_ALPHA,  pstZmeRtlPara->bZmeMdHA);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_ALPHA,  pstZmeRtlPara->bZmeMedHA);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_HORL,   pstZmeRtlPara->bZmeMedHL);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_HORC,   pstZmeRtlPara->bZmeMedHC);
    OPTM_VDP_GP_SetZmePhase           (enGpId, VDP_ZME_MODE_HORL,   pstZmeRtlPara->s32ZmeOffsetHL);
    OPTM_VDP_GP_SetZmePhase           (enGpId, VDP_ZME_MODE_HORC,   pstZmeRtlPara->s32ZmeOffsetHC);
    OPTM_VDP_GP_SetZmeHorRatio        (enGpId, pstZmeRtlPara->u32ZmeRatioHL);
    OPTM_VDP_GP_SetZmeCoefAddr        (enGpId, VDP_GP_PARA_ZME_VER, pstZmeRtlPara->u32ZmeCoefAddrVL);
    OPTM_VDP_GP_SetZmeFirEnable       (enGpId, VDP_ZME_MODE_VER,    pstZmeRtlPara->bZmeMdVLC);
    OPTM_VDP_GP_SetZmeFirEnable       (enGpId, VDP_ZME_MODE_ALPHAV, pstZmeRtlPara->bZmeMdVA);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_ALPHAV, pstZmeRtlPara->bZmeMedVA);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_VERL,   pstZmeRtlPara->bZmeMedVL);
    OPTM_VDP_GP_SetZmeMidEnable       (enGpId, VDP_ZME_MODE_VERC,   pstZmeRtlPara->bZmeMedVC);
    OPTM_VDP_GP_SetZmePhase           (enGpId, VDP_ZME_MODE_VERL,   pstZmeRtlPara->s32ZmeOffsetVBtm);
    OPTM_VDP_GP_SetZmePhase           (enGpId, VDP_ZME_MODE_VERC,   pstZmeRtlPara->s32ZmeOffsetVTop);
    OPTM_VDP_GP_SetZmeVerRatio        (enGpId, pstZmeRtlPara->u32ZmeRatioVL);

    if (OPTM_DISPCHANNEL_1 == g_pstGfxGPDevice[enGpId]->enDispCh && bGfxSharpen)
    {
         OPTM_VDP_GP_SetTiEnable     (enGpId, VDP_TI_MODE_CHM, pstDtiRtlPara->bEnCTI);
         OPTM_VDP_GP_SetTiEnable     (enGpId, VDP_TI_MODE_LUM, pstDtiRtlPara->bEnLTI);
         OPTM_VDP_GP_SetZmeHfirOrder (enGpId, VDP_ZME_ORDER_VH);
    }
    else
    {
         OPTM_VDP_GP_SetTiEnable     (enGpId, VDP_TI_MODE_CHM, HI_FALSE);
         OPTM_VDP_GP_SetTiEnable     (enGpId, VDP_TI_MODE_LUM, HI_FALSE);
    }

    OPTM_VDP_GP_SetTiHpCoef       (enGpId, VDP_TI_MODE_CHM, (HI_S32 *)pstDtiRtlPara->s32CTIHPTmp);
    OPTM_VDP_GP_SetTiHpCoef       (enGpId, VDP_TI_MODE_LUM, (HI_S32 *)pstDtiRtlPara->s32LTIHPTmp);
    OPTM_VDP_GP_SetTiGainRatio    (enGpId, VDP_TI_MODE_CHM, (HI_S32)pstDtiRtlPara->s16CTICompsatRatio);
    OPTM_VDP_GP_SetTiGainRatio    (enGpId, VDP_TI_MODE_LUM, (HI_S32)pstDtiRtlPara->s16LTICompsatRatio);
    OPTM_VDP_GP_SetTiCoringThd    (enGpId, VDP_TI_MODE_CHM, (HI_U32)pstDtiRtlPara->u16CTICoringThrsh);
    OPTM_VDP_GP_SetTiCoringThd    (enGpId, VDP_TI_MODE_LUM, (HI_U32)pstDtiRtlPara->u16LTICoringThrsh);
    OPTM_VDP_GP_SetTiSwingThd     (enGpId, VDP_TI_MODE_CHM, (HI_U32)pstDtiRtlPara->u16CTIOverSwingThrsh, (HI_U32)pstDtiRtlPara->u16CTIUnderSwingThrsh);
    OPTM_VDP_GP_SetTiSwingThd     (enGpId, VDP_TI_MODE_LUM, (HI_U32)pstDtiRtlPara->u16LTIOverSwingThrsh, (HI_U32)pstDtiRtlPara->u16LTIUnderSwingThrsh);
    OPTM_VDP_GP_SetTiMixRatio     (enGpId, VDP_TI_MODE_CHM, (HI_U32)pstDtiRtlPara->u8CTIMixingRatio);
    OPTM_VDP_GP_SetTiMixRatio     (enGpId, VDP_TI_MODE_LUM, (HI_U32)pstDtiRtlPara->u8LTIMixingRatio);
    OPTM_VDP_GP_SetTiHfThd        (enGpId, VDP_TI_MODE_LUM, (HI_U32 *)pstDtiRtlPara->u32LTIHFreqThrsh);
    OPTM_VDP_GP_SetTiGainCoef     (enGpId, VDP_TI_MODE_LUM, (HI_U32 *)pstDtiRtlPara->u32LTICompsatMuti);

    return;
}
#else
static HI_VOID OPTM_GfxGetPqGpFromDispChannel(const OPTM_DISPCHANNEL_E enChannel, HI_PQ_GFX_LAYER_E *pPqGp)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(pPqGp);

    if (OPTM_DISPCHANNEL_1 == enChannel)
    {
       *pPqGp = PQ_GFX_GP0;
    }
    else if (OPTM_DISPCHANNEL_0 == enChannel)
    {
       *pPqGp = PQ_GFX_GP1;
    }
    else
    {
        *pPqGp = PQ_GFX_LAYER_BUTT;
    }

    return;
}

HI_S32 OPTM_GfxSetGpRect(OPTM_GFX_GP_E enGpId, const HIFB_RECT * pstInputRect)
{
    HI_S32 Ret = HI_SUCCESS;
    OPTM_VDP_DISP_RECT_S stGfxRect    = {0};
    HI_PQ_GFX_ZME_PARA_S stGfxZmePara = {0};
    HI_RECT_S stOutRect               = {0};
    HI_PQ_GFX_LAYER_E enPqGfxGp = PQ_GFX_LAYER_BUTT;

#ifdef CHIP_TYPE_hi3798cv200/** fuction for cts test **/
    HI_DRV_DISP_FMT_E  enDispFmt  = HI_DRV_DISP_FMT_1080P_50;
    #ifdef HI_BUILD_IN_BOOT
        HI_DISP_DISPLAY_INFO_S stDispInfo;
    #endif
#endif

     HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);
     HIFB_CHECK_NULLPOINTER_RETURN(pstInputRect, HI_FAILURE);

#ifdef CHIP_TYPE_hi3798cv200
     #ifdef HI_BUILD_IN_BOOT
        HI_GFX_Memset(&stDispInfo,0,sizeof(stDispInfo));
        if (enGpId == OPTM_GFX_GP_0)
        {
            HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &stDispInfo);
        }
        else
        {
            HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &stDispInfo);
        }
        g_pstGfxGPDevice[enGpId]->enDispFmt = stDispInfo.eFmt;
    #endif
    enDispFmt = g_pstGfxGPDevice[enGpId]->enDispFmt;
#endif

    g_pstGfxGPDevice[enGpId]->stInRect.s32Width  = pstInputRect->w;
    g_pstGfxGPDevice[enGpId]->stInRect.s32Height = pstInputRect->h;

    if ((0 == g_pstGfxGPDevice[enGpId]->stOutRect.s32Width) || (0 == g_pstGfxGPDevice[enGpId]->stOutRect.s32Height))
    {
       return HI_FAILURE;
    }
    stOutRect.s32X      = g_pstGfxGPDevice[enGpId]->stOutRect.s32X;
    stOutRect.s32Y      = g_pstGfxGPDevice[enGpId]->stOutRect.s32Y;
    stOutRect.s32Width  = g_pstGfxGPDevice[enGpId]->stOutRect.s32Width;
    stOutRect.s32Height = g_pstGfxGPDevice[enGpId]->stOutRect.s32Height;

    OPTM_CheckGPMask_BYGPID(enGpId);

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT, stOutRect.s32X, stOutRect.s32Y,0,0,0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT, stOutRect.s32Width, stOutRect.s32Height,0,0,0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

#ifdef CHIP_TYPE_hi3798cv200
    if ( (OPTM_GFX_GP_0 == enGpId) && (HI_DRV_DISP_FMT_1440x576i_50 == enDispFmt || HI_DRV_DISP_FMT_1440x480i_60 == enDispFmt))
    {
        stOutRect.s32X      = g_pstGfxGPDevice[enGpId]->stOutRect.s32X * 2;
        stOutRect.s32Width  = g_pstGfxGPDevice[enGpId]->stOutRect.s32Width * 2;
        stOutRect.s32Y      = g_pstGfxGPDevice[enGpId]->stOutRect.s32Y;
        stOutRect.s32Height = g_pstGfxGPDevice[enGpId]->stOutRect.s32Height;
    }
#endif

    stGfxRect.u32IWth = g_pstGfxGPDevice[enGpId]->stInRect.s32Width   & 0xfffffffe;
    stGfxRect.u32IHgt = g_pstGfxGPDevice[enGpId]->stInRect.s32Height  & 0xfffffffe;
    stGfxRect.u32OWth = stOutRect.s32Width  & 0xfffffffe;
    stGfxRect.u32OHgt = stOutRect.s32Height & 0xfffffffe;

    stGfxRect.u32DXS  = stOutRect.s32X & 0xfffffffe;
    stGfxRect.u32DYS  = stOutRect.s32Y & 0xfffffffe;

    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OWth, stGfxRect.u32DXS, HI_FAILURE);
    stGfxRect.u32DXL  = stGfxRect.u32OWth + stGfxRect.u32DXS;
    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OHgt, stGfxRect.u32DYS, HI_FAILURE);
    stGfxRect.u32DYL  = stGfxRect.u32OHgt + stGfxRect.u32DYS;

    stGfxRect.u32VX   = stGfxRect.u32DXS;
    stGfxRect.u32VY   = stGfxRect.u32DYS;

    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OWth, stGfxRect.u32VX, HI_FAILURE);
    stGfxRect.u32VXL  = stGfxRect.u32OWth + stGfxRect.u32VX;
    HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(stGfxRect.u32OHgt, stGfxRect.u32VY, HI_FAILURE);
    stGfxRect.u32VYL  = stGfxRect.u32OHgt + stGfxRect.u32VY;

    if (g_pstGfxGPDevice[enGpId]->bNeedExtractLine == HI_TRUE)
    {
        stGfxRect.u32IHgt /= 2;
    }

    if ( (0 == stGfxRect.u32IWth) || (0 == stGfxRect.u32IHgt) || (0 == stGfxRect.u32OWth) || (0 == stGfxRect.u32OHgt))
    {
        return HI_SUCCESS;
    }

    OPTM_VDP_GP_SetLayerReso(enGpId, &stGfxRect);

    if (IS_SLAVER_GP(enGpId))
    {
        stGfxRect.u32IWth  = g_stGfxWbc2.stInRect.w & 0xfffffffe;
        stGfxRect.u32IHgt  = g_stGfxWbc2.stInRect.h & 0xfffffffe;
        if ((0 == stGfxRect.u32IWth) || (0 == stGfxRect.u32IHgt))
        {
            return HI_SUCCESS;
        }

        if (HIFB_STEREO_SIDEBYSIDE_HALF == g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode)
        {
            stGfxRect.u32IWth /= 2;
        }
        else if (HIFB_STEREO_TOPANDBOTTOM == g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode)
        {
            stGfxRect.u32IHgt /= 2;
        }

        if ( HI_TRUE == g_pstGfxGPDevice[OPTM_MASTER_GPID]->bNeedExtractLine)
        {
            stGfxRect.u32IHgt /= 2;
        }

        HIFB_WBC2_SetCropReso(stGfxRect);
    }

    /**here set layer rect  that been opened by usered **/
    HIFB_ADP_ResetLayerInRect(enGpId);

    /**set zme, if wbc mode, should not set gp1 zme **/
    stGfxZmePara.u32ZmeFrmWIn  = stGfxRect.u32IWth;
    stGfxZmePara.u32ZmeFrmHIn  = stGfxRect.u32IHgt;
    stGfxZmePara.u32ZmeFrmWOut = stOutRect.s32Width;
    stGfxZmePara.u32ZmeFrmHOut = stOutRect.s32Height;
    stGfxZmePara.bDeFlicker    = g_pstGfxGPDevice[enGpId]->u32ZmeDeflicker ? HI_FALSE : HI_TRUE;
    stGfxZmePara.bZmeFrmFmtIn  = HI_TRUE;
    stGfxZmePara.bZmeFrmFmtOut = g_pstGfxGPDevice[enGpId]->bInterface ? HI_FALSE : HI_TRUE;

    OPTM_GfxGetPqGpFromDispChannel(g_pstGfxGPDevice[enGpId]->enDispCh,&enPqGfxGp);
    if (PQ_GFX_LAYER_BUTT == enPqGfxGp)
    {
       return HI_FAILURE;
    }

    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_HOR);
    OPTM_VDP_GP_SetParaUpd(enGpId,VDP_ZME_MODE_VER);

#ifndef HI_BUILD_IN_BOOT
    if (IS_SLAVER_GP(enGpId))
    {/** 如果是同源的，这里不处理GP1**/
       return HI_SUCCESS;
    }
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(gs_pstPqFuncs->pfnPQ_SetGfxZme, HI_FAILURE);
    gs_pstPqFuncs->pfnPQ_SetGfxZme(enPqGfxGp, &stGfxZmePara);
#endif

#ifdef HI_BUILD_IN_BOOT
    DRV_PQ_SetGfxZme(enPqGfxGp, &stGfxZmePara);
#endif

    return HI_SUCCESS;
}
#endif

static inline HI_VOID HIFB_ADP_ResetLayerInRect(OPTM_GFX_GP_E enGpId)
{
    HI_S32 s32Cnt = 0;
    HI_U32 u32LayerCount  = 0;
    HIFB_LAYER_ID_E enLayerId      = HIFB_LAYER_ID_BUTT;
    HIFB_LAYER_ID_E enInitLayerId  = HIFB_LAYER_ID_BUTT;

    u32LayerCount = (OPTM_GFX_GP_0 == enGpId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_GFX_GP_0 == enGpId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    for (s32Cnt = 0; s32Cnt < u32LayerCount; s32Cnt++)
    {
        enLayerId = enInitLayerId + s32Cnt;
        if (!g_pstGfxDevice[enLayerId]->bOpened)
        {
            continue;
        }
        OPTM_GfxSetLayerRect(enLayerId, &g_pstGfxDevice[enLayerId]->stInRect);
    }

    return;
}

/***************************************************************************************
* func          : OPTM_GfxSetGpDeflicker
* description   : CNcomment: 设置GP抗闪 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GfxSetGpDeflicker(HI_U32 u32DispChn, HI_BOOL bDeflicker)
{
    HIFB_RECT stInputRect = {0};
    OPTM_GFX_GP_E enGpId = u32DispChn ? OPTM_GFX_GP_0 : OPTM_GFX_GP_1;

    stInputRect.x = g_pstGfxGPDevice[enGpId]->stInRect.s32X;
    stInputRect.y = g_pstGfxGPDevice[enGpId]->stInRect.s32Y;
    stInputRect.w = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
    stInputRect.h = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;

    g_pstGfxGPDevice[enGpId]->u32ZmeDeflicker = (HI_U32)bDeflicker;

    OPTM_GfxSetGpRect(enGpId, &stInputRect);

    return HI_SUCCESS;
}

/***************************************************************************************
* func        : OPTM_GfxGetOutRect
* description : CNcomment: 获取输出分辨率 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GfxGetOutRect(HIFB_LAYER_ID_E enLayerId, HIFB_RECT * pstOutputRect)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstOutputRect, HI_FAILURE);

    enGpId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);

    pstOutputRect->x = 0;
    pstOutputRect->y = 0;
    pstOutputRect->w = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
    pstOutputRect->h = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetLayKeyMask
* description  : CNcomment:设置图层color key 信息CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GfxSetLayKeyMask(HIFB_LAYER_ID_E enLayerId, const HIFB_COLORKEYEX_S *pstColorkey)
{
    OPTM_VDP_GFX_CKEY_S ckey_info;
    OPTM_VDP_GFX_MASK_S ckey_mask;

    HIFB_CHECK_LAYER_OPEN(enLayerId);
    HIFB_CHECK_NULLPOINTER_RETURN(pstColorkey, HI_FAILURE);

    HI_GFX_Memset(&ckey_info, 0, sizeof(ckey_info));
    HI_GFX_Memset(&ckey_mask, 0, sizeof(ckey_mask));

    HI_GFX_Memcpy(&g_pstGfxDevice[enLayerId]->stColorkey, pstColorkey, sizeof(HIFB_COLORKEYEX_S));

    /** 是否已经开机logo过渡完 **/
    OPTM_CheckGPMask_BYLayerID(enLayerId);

    ckey_info.bKeyMode  = pstColorkey->u32KeyMode;

    if (g_pstGfxDevice[enLayerId]->CscState == OPTM_CSC_SET_PARA_BGR)
    {
        ckey_info.u32Key_r_min = pstColorkey->u8BlueMin;
        ckey_info.u32Key_g_min = pstColorkey->u8GreenMin;
        ckey_info.u32Key_b_min = pstColorkey->u8RedMin;

        ckey_info.u32Key_r_max = pstColorkey->u8BlueMax;
        ckey_info.u32Key_g_max = pstColorkey->u8GreenMax;
        ckey_info.u32Key_b_max = pstColorkey->u8RedMax;

        ckey_mask.u32Mask_r = pstColorkey->u8BlueMask;
        ckey_mask.u32Mask_g = pstColorkey->u8GreenMask;
        ckey_mask.u32Mask_b = pstColorkey->u8RedMask;
    }
    else
    {
        ckey_info.u32Key_r_min = pstColorkey->u8RedMin;
        ckey_info.u32Key_g_min = pstColorkey->u8GreenMin;
        ckey_info.u32Key_b_min = pstColorkey->u8BlueMin;

        ckey_info.u32Key_r_max = pstColorkey->u8RedMax;
        ckey_info.u32Key_g_max = pstColorkey->u8GreenMax;
        ckey_info.u32Key_b_max = pstColorkey->u8BlueMax;

        ckey_mask.u32Mask_r = pstColorkey->u8RedMask;
        ckey_mask.u32Mask_g = pstColorkey->u8GreenMask;
        ckey_mask.u32Mask_b = pstColorkey->u8BlueMask;
    }

    OPTM_VDP_GFX_SetKeyMask(g_pstGfxDevice[enLayerId]->enGfxHalId, &ckey_mask);
    OPTM_VDP_GFX_SetColorKey(g_pstGfxDevice[enLayerId]->enGfxHalId, pstColorkey->bKeyEnable, &ckey_info);

    OPTM_VDP_GFX_SetRegUp(g_pstGfxDevice[enLayerId]->enGfxHalId);

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : OPTM_GfxSetLayerPreMult
* description  : CNcomment: 设置图层预乘 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GfxSetLayerPreMult(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable)
{
    HI_BOOL bHdr = HI_FALSE;
    OPTM_GFX_GP_E enGpId  = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGpId  = g_pstGfxDevice[enLayerId]->enGPId;

    g_pstGfxDevice[enLayerId]->bPreMute = bEnable;

    OPTM_CheckGPMask_BYGPID(enGpId);

    bHdr = g_pstGfxGPDevice[enGpId]->bHdr;

    OPTM_VDP_GFX_SetPreMultEnable(g_pstGfxDevice[enLayerId]->enGfxHalId, bEnable, bHdr);

    return HI_SUCCESS;
}

STATIC HI_VOID OPTM_GfxGetLayerPreMult(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pPreMul)
{
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);

    OPTM_VDP_GFX_GetPreMultEnable(g_pstGfxDevice[enLayerId]->enGfxHalId, pPreMul);

    return;
}

STATIC HI_VOID OPTM_GfxGetLayerHdr(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pHdr)
{
    OPTM_GFX_GP_E enGpId  = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(enLayerId);
    enGpId  = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

    *pHdr = g_pstGfxGPDevice[enGpId]->bHdr;

    return;
}

STATIC HI_VOID OPTM_GfxGetClosePreMultState(HIFB_LAYER_ID_E LayerId, HI_BOOL *pbShouldClosePreMult)
{
#ifdef CHIP_TYPE_hi3798cv200
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;
#endif

    HIFB_CHECK_NULLPOINTER_UNRETURN(pbShouldClosePreMult);

#ifdef CHIP_TYPE_hi3798cv200
    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    enGpId = OPTM_GFX_GetGpId(LayerId);
    *pbShouldClosePreMult = g_pstGfxGPDevice[enGpId]->bHdr;
#else
    HI_UNUSED(LayerId);
    *pbShouldClosePreMult = HI_FALSE;
#endif
}

STATIC HI_VOID OPTM_GfxReadRegister(HI_U32 Offset)
{
    OPTM_VDP_GFX_ReadRegister(Offset);
}

STATIC HI_VOID OPTM_GfxWriteRegister(HI_U32 Offset,HI_U32 Value)
{
    OPTM_VDP_GFX_WriteRegister(Offset,Value);
}

#ifndef HI_BUILD_IN_BOOT
STATIC HI_VOID OPTM_GfxWhetherDiscardFrame(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pNoDiscardFrame)
{
#ifndef CONFIG_HIFB_VERSION_1_0
    HI_S32 Ret = HI_SUCCESS;
    DISP_EXPORT_FUNC_S *DispExportFuncs = NULL;
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    HI_DRV_DISPLAY_E enDisp;

    if (enLayerId < HIFB_LAYER_SD_0)
    {
       enDisp = HI_DRV_DISPLAY_1;
    }
    else
    {
       enDisp = HI_DRV_DISPLAY_0;
    }

    HI_GFX_Memset(&stDispInfo,0x0,sizeof(stDispInfo));
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_DISP, (HI_VOID**)&DispExportFuncs);
    if ( (HI_SUCCESS != Ret) || (NULL == DispExportFuncs))
    {
        HIFB_ERROR("disp export funcs get failure\n");
        return;
    }

    HIFB_CHECK_NULLPOINTER_UNRETURN(pNoDiscardFrame);
    HIFB_CHECK_NULLPOINTER_UNRETURN(DispExportFuncs->pfnDispGetDispInfo);

    Ret = DispExportFuncs->pfnDispGetDispInfo(enDisp,&stDispInfo);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("pfnDispGetDispInfo get failure\n");
        return;
    }

    if (  (HI_DRV_DISP_FMT_1080P_24 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_1080P_25 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_1080P_30 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_1080P_23_976 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_1080P_29_97 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_24 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_25 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_30 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_23_976 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_3840X2160_29_97 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_4096X2160_24 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_4096X2160_25 == stDispInfo.eFmt)
        ||(HI_DRV_DISP_FMT_4096X2160_30 == stDispInfo.eFmt))
    {
       *pNoDiscardFrame = HI_FALSE;
    }
    else
    {
       *pNoDiscardFrame = HI_TRUE;
    }
#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(pNoDiscardFrame);
#endif
    return;
}

/***************************************************************************************
* func        : OPTM_GfxGetOSDData
* description : CNcomment: 获取对应图层得OSD数据 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
STATIC HI_VOID OPTM_GfxGetOSDData(HIFB_LAYER_ID_E enLayerId, HIFB_OSD_DATA_S *pstLayerData)
{
    HI_U32 u32Enable     = HI_FALSE;
    HI_U32 u32KeyEnable  = HI_FALSE;
    HI_U32 alpharange    = 0;
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_BUTT;
    OPTM_VDP_DISP_RECT_S  stRect     = {0};
    OPTM_VDP_DISP_RECT_S stInRect    = {0};
    OPTM_VDP_GFX_MASK_S  stckey_mask = {0};
    OPTM_VDP_GFX_CKEY_S  stKey       = {0};
    OPTM_VDP_GFX_IFMT_E  enDataFmt   = VDP_GFX_IFMT_BUTT;

    enGPId = OPTM_GFX_GetGpId(enLayerId);

    OPTM_VDP_GFX_GetLayerEnable(OPTM_GetGfxHalId(enLayerId), &u32Enable);

    HIFB_CHECK_NULLPOINTER_UNRETURN(pstLayerData);
    if (u32Enable)
    {
        pstLayerData->eState = HIFB_LAYER_STATE_ENABLE;
    }
    else
    {
        pstLayerData->eState = HIFB_LAYER_STATE_DISABLE;
    }

    /** 获取surface 帧buffer地址 **/
    OPTM_VDP_GFX_GetLayerAddr(OPTM_GetGfxHalId(enLayerId), &pstLayerData->u32RegPhyAddr);

    OPTM_VDP_GFX_GetLayerStride(OPTM_GetGfxHalId(enLayerId), &pstLayerData->u32Stride);

    OPTM_VDP_GFX_GetLayerInRect(OPTM_GetGfxHalId(enLayerId), &stInRect);
    pstLayerData->stInRect.x = stInRect.u32DXS;
    pstLayerData->stInRect.y = stInRect.u32DYS;
    pstLayerData->stInRect.w = stInRect.u32IWth;
    pstLayerData->stInRect.h = stInRect.u32IHgt;

    OPTM_VDP_GP_GetRect(enGPId, &stRect);

    pstLayerData->stOutRect.x = 0;
    pstLayerData->stOutRect.y = 0;
    pstLayerData->stOutRect.w = stRect.u32IWth;
    pstLayerData->stOutRect.h = stRect.u32IHgt;

    pstLayerData->DisplayWidth = stRect.u32OWth;
    pstLayerData->DisplayHeight= stRect.u32OHgt;

    OPTM_VDP_WBC_GetEnable(OPTM_VDP_LAYER_WBC_GP0, &u32Enable);
    if (u32Enable)
    {
    /**同源**/
        pstLayerData->eGfxWorkMode = HIFB_GFX_MODE_HD_WBC;
        pstLayerData->enSlaveryLayerID = OPTM_SLAVER_LAYERID;
    }
    else
    {/**非同源**/
        pstLayerData->eGfxWorkMode = HIFB_GFX_MODE_NORMAL;
        pstLayerData->enSlaveryLayerID = HIFB_LAYER_ID_BUTT;
    }

    OPTM_VDP_GFX_GetPalpha( OPTM_GetGfxHalId(enLayerId),               \
                           &pstLayerData->stAlpha.bAlphaEnable,        \
                           &alpharange,&pstLayerData->stAlpha.u8Alpha0,\
                           &pstLayerData->stAlpha.u8Alpha1);

    OPTM_VDP_GFX_GetLayerGalpha(OPTM_GetGfxHalId(enLayerId),     \
                                &pstLayerData->stAlpha.u8GlobalAlpha);

    OPTM_VDP_GFX_GetKeyMask (OPTM_GetGfxHalId(enLayerId), &stckey_mask);
    OPTM_VDP_GFX_GetColorKey(OPTM_GetGfxHalId(enLayerId), &u32KeyEnable,&stKey);

    pstLayerData->stColorKey.u8RedMask   = stckey_mask .u32Mask_r;
    pstLayerData->stColorKey.u8GreenMask = stckey_mask .u32Mask_g;
    pstLayerData->stColorKey.u8BlueMask  = stckey_mask .u32Mask_b;

    pstLayerData->stColorKey.bMaskEnable = HI_TRUE;
    pstLayerData->stColorKey.bKeyEnable  = u32KeyEnable;
    pstLayerData->stColorKey.u32KeyMode  = stKey.bKeyMode;

    pstLayerData->stColorKey.u8RedMax    = stKey.u32Key_r_max;
    pstLayerData->stColorKey.u8GreenMax  = stKey.u32Key_g_max;
    pstLayerData->stColorKey.u8BlueMax   = stKey.u32Key_b_max;

    pstLayerData->stColorKey.u8RedMin    = stKey.u32Key_r_min;
    pstLayerData->stColorKey.u8GreenMin  = stKey.u32Key_g_min;
    pstLayerData->stColorKey.u8BlueMin   = stKey.u32Key_b_min;

    OPTM_VDP_GFX_GetPreMultEnable(OPTM_GetGfxHalId(enLayerId), &pstLayerData->bPreMul);

    OPTM_VDP_GFX_GetInDataFmt(OPTM_GetGfxHalId(enLayerId), &enDataFmt);

    pstLayerData->eFmt = OPTM_HalFmtTransferToPixerFmt(enDataFmt);
}

STATIC HI_VOID HIFB_ADP_GetLogoData(HIFB_LAYER_ID_E enLayerId, HIFB_LOGO_DATA_S *pstLogoData)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 LayerEnable = 0;
     OPTM_VDP_GFX_IFMT_E  enDataFmt   = VDP_GFX_IFMT_BUTT;
     HIFB_COLOR_FMT_E enFmt = HIFB_FMT_BUTT;
     DISP_EXPORT_FUNC_S *DispExportFuncs = NULL;
     HI_DISP_DISPLAY_INFO_S stDispInfo;
     HI_DRV_DISPLAY_E enDisp;
     HI_RECT_S stOutRect = {0};
     OPTM_VDP_DISP_RECT_S stInRect = {0};

     if (enLayerId < HIFB_LAYER_SD_0)
     {
        enDisp = HI_DRV_DISPLAY_1;
     }
     else
     {
        enDisp = HI_DRV_DISPLAY_0;
     }

     HIFB_CHECK_NULLPOINTER_UNRETURN(pstLogoData);

     HI_GFX_Memset(&stDispInfo,0x0,sizeof(stDispInfo));

     Ret = HI_DRV_MODULE_GetFunction(HI_ID_DISP, (HI_VOID**)&DispExportFuncs);
     if ( (HI_SUCCESS != Ret) || (NULL == DispExportFuncs))
     {
         HIFB_ERROR("disp export funcs get failure\n");
         return;
     }

     HIFB_CHECK_NULLPOINTER_UNRETURN(DispExportFuncs->pfnDispGetDispInfo);
     Ret = DispExportFuncs->pfnDispGetDispInfo(enDisp,&stDispInfo);
     if (HI_SUCCESS != Ret)
     {
         //HIFB_ERROR("pfnDispGetDispInfo get failure\n");
         return;
     }
     OPTM_GetScreenRectFromDispInfo(&stDispInfo.stVirtaulScreen, (OPTM_GFX_OFFSET_S *)&stDispInfo.stOffsetInfo,
                                    &stDispInfo.stFmtResolution,&stDispInfo.stPixelFmtResolution,
                                    &stOutRect);

     OPTM_VDP_GFX_GetLayerInRect (OPTM_GetGfxHalId(enLayerId), &stInRect);
     OPTM_VDP_GFX_GetLayerEnable (OPTM_GetGfxHalId(enLayerId), &LayerEnable);
     OPTM_VDP_GFX_GetLayerAddr   (OPTM_GetGfxHalId(enLayerId), &pstLogoData->LogoYAddr);
     OPTM_VDP_GFX_GetInDataFmt   (OPTM_GetGfxHalId(enLayerId), &enDataFmt);
     enFmt = OPTM_HalFmtTransferToPixerFmt(enDataFmt);

     if (   (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == stInRect.u32IWth || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == stInRect.u32IWth)
         && (CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH == stDispInfo.stFmtResolution.s32Width || CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH == stDispInfo.stFmtResolution.s32Width)
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == stInRect.u32IHgt)
         && (CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT == stDispInfo.stFmtResolution.s32Height))
     {
         pstLogoData->Support4KLogo = HI_TRUE;
     }

     pstLogoData->LogoEnable     = (1 == LayerEnable) ? (HI_TRUE) : (HI_FALSE);
     pstLogoData->LogoCbCrAddr   = 0x0;

     if ((enLayerId < HIFB_LAYER_SD_0) && (HI_FALSE == pstLogoData->Support4KLogo))
     {
        pstLogoData->LogoWidth      = stDispInfo.stVirtaulScreen.s32Width;
        pstLogoData->LogoHeight     = stDispInfo.stVirtaulScreen.s32Height;
     }
     else
     {
        pstLogoData->LogoWidth      = stDispInfo.stFmtResolution.s32Width;
        pstLogoData->LogoHeight     = stDispInfo.stFmtResolution.s32Height;
     }
     pstLogoData->stOutRect.x    = stOutRect.s32X;
     pstLogoData->stOutRect.y    = stOutRect.s32Y;
     pstLogoData->stOutRect.w    = stOutRect.s32Width;
     pstLogoData->stOutRect.h    = stOutRect.s32Height;
     pstLogoData->eLogoPixFmt    = HIFB_LOGO_PIX_FMT_ARGB8888;
     pstLogoData->LogoYStride    = pstLogoData->LogoWidth * 4;
     if (HIFB_FMT_ARGB1555 == enFmt)
     {
        pstLogoData->eLogoPixFmt = HIFB_LOGO_PIX_FMT_ARGB1555;
        pstLogoData->LogoYStride = pstLogoData->LogoWidth * 2;
     }
     return;
}
#endif

/***************************************************************************************
* func         : OPTM_GfxUpLayerReg
* description  : CNcomment: 更新寄存器 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 OPTM_GfxUpLayerReg(HIFB_LAYER_ID_E enLayerId)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGpId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);

    OPTM_CheckGPMask_BYGPID(enGpId);

    OPTM_VDP_GFX_SetRegUp(g_pstGfxDevice[enLayerId]->enGfxHalId);
    OPTM_VDP_GP_SetRegUp (g_pstGfxGPDevice[enGpId]->enGpHalId);

    if (IS_MASTER_GP(enGpId))
    {
        HIFB_WBC2_Reset(HI_TRUE);
    }

    return HI_SUCCESS;
}

static HI_VOID HIFB_ADP_GetCloseState(HIFB_LAYER_ID_E LayerId, HI_BOOL *pHasBeenClosedForVoCallBack, HI_BOOL *pHasBeenClosedForEndCallBack)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerId);
    enGpId = g_pstGfxDevice[LayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_UNRETURN(enGpId);

    if ((HI_TRUE == g_pstGfxGPDevice[enGpId]->bHasBeenReOpen[0]) && (NULL != pHasBeenClosedForVoCallBack))
    {
        *pHasBeenClosedForVoCallBack = HI_TRUE;
        g_pstGfxGPDevice[enGpId]->bHasBeenReOpen[0] = HI_FALSE;
    }

    if ((HI_TRUE == g_pstGfxGPDevice[enGpId]->bHasBeenReOpen[1]) && (NULL != pHasBeenClosedForEndCallBack))
    {
        *pHasBeenClosedForEndCallBack = HI_TRUE;
        g_pstGfxGPDevice[enGpId]->bHasBeenReOpen[1] = HI_FALSE;
    }

    return;
}

static HI_VOID HIFB_ADP_GetDhd0Info(HIFB_LAYER_ID_E LayerId, HI_ULONG *pExpectIntLineNumsForVoCallBack,HI_ULONG *pExpectIntLineNumsForEndCallBack,HI_ULONG *pActualIntLineNumsForVoCallBack,HI_ULONG *pHardIntCntForVoCallBack)
{
    HI_UNUSED(LayerId);
#if !defined(HI_BUILD_IN_BOOT) && !defined(CONFIG_HIFB_VERSION_1_0)
    HIFB_HAL_GetDhd0Vtthd3(pExpectIntLineNumsForEndCallBack);
    HIFB_HAL_GetDhd0Vtthd(pExpectIntLineNumsForVoCallBack);
    HIFB_HAL_GetDhd0State(pActualIntLineNumsForVoCallBack,pHardIntCntForVoCallBack);
#else
    HI_UNUSED(pExpectIntLineNumsForEndCallBack);
    HI_UNUSED(pExpectIntLineNumsForVoCallBack);
    HI_UNUSED(pActualIntLineNumsForVoCallBack);
    HI_UNUSED(pHardIntCntForVoCallBack);
#endif
    return;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_GfxSetTriDimMode
* description  : CNcomment: 设置3D模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetTriDimMode(HIFB_LAYER_ID_E enLayerId, HIFB_STEREO_MODE_E enMode, HIFB_STEREO_MODE_E enWbcSteroMode)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGpId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->enTriDimMode = enMode;
    g_pstGfxGPDevice[enGpId]->enTriDimMode  = enMode;

    OPTM_CheckGPMask_BYGPID(enGpId);

    OPTM_VDP_GP_SetRegUp(g_pstGfxDevice[enLayerId]->enGPId);

    if (IS_MASTER_GP(enGpId))
    {
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode = enWbcSteroMode;
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->stInRect.s32Width  = g_pstGfxGPDevice[enGpId]->stInRect.s32Width;
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->stInRect.s32Height = g_pstGfxGPDevice[enGpId]->stInRect.s32Height;

        if (HIFB_STEREO_MONO == enWbcSteroMode)
        {
            g_stGfxWbc2.enWbcMode = OPTM_WBC_MODE_MONO;
        }
        else
        {
            g_stGfxWbc2.enWbcMode = OPTM_WBC_MODE_LFET_EYE;
        }

        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->unUpFlag.bits.WbcMode          = 1;
        g_pstGfxGPDevice[OPTM_SLAVER_GPID]->unUpFlag.bits.IsNeedUpInRect   = 1;

        HIFB_WBC2_Reset(HI_TRUE);
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GfxSetTriDimAddr
* description  : CNcomment: 设置3D显示地址 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetTriDimAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32TriDimAddr)
{
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);

    g_pstGfxDevice[enLayerId]->u32TriDimAddr= u32TriDimAddr;

    OPTM_CheckGPMask_BYLayerID(enLayerId);

    OPTM_VDP_GFX_SetLayerNAddr(enLayerId, u32TriDimAddr);

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func          : OPTM_GfxGetLayerPriority
* description   : CNcomment: 获取图层在GP 中的优先级 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GfxGetLayerPriority(HIFB_LAYER_ID_E enLayerId, HI_U32 *pPriority)
{
    HI_U32 i            = 0;
    HI_U32 u32prio      = 0;
    HI_U32 u32Index     = 0;
    HI_U32 u32LayerPrio = 0;
    HI_U32 u32LayerIdIndex = 0;
    OPTM_VDP_CBM_MIX_E eCbmMixg;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pPriority, HI_FAILURE);

    u32Index = (g_pstGfxDevice[enLayerId]->enGPId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    eCbmMixg = (g_pstGfxDevice[enLayerId]->enGPId == OPTM_GFX_GP_0) ? VDP_CBM_MIXG0 : VDP_CBM_MIXG1;
    OPTM_VDP_CBM_GetMixerPrio(eCbmMixg, &u32prio);

    if (HIFB_LAYER_HD_2 == enLayerId)
    {
        u32LayerIdIndex = 3; /** G3 **/
    }
    else
    {
        u32LayerIdIndex = enLayerId - OPTM_GP0_GFX_COUNT * g_pstGfxDevice[enLayerId]->enGPId;
    }

    for (i = 0; i < u32Index; i++)
    {
        u32LayerPrio = u32prio & 0xf;
        u32prio      = u32prio >> 4;

        if ((u32LayerPrio - 1) == u32LayerIdIndex)
        {
            *pPriority = i + 1;
            return HI_SUCCESS;
        }
    }

    HIFB_ERROR("info:fail to get z_order of gfx%d!\n",enLayerId);

    return HI_FAILURE;
}

/***************************************************************************************
* func         : OPTM_GfxSetLayerPriority
* description  : CNcomment: 设置图层在GP 中的优先级 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GfxSetLayerPriority(HIFB_LAYER_ID_E enLayerId, HIFB_ZORDER_E enZOrder)
{
    HI_U32  u32Prio        = 0;
    HI_U32  u32LayerPrio   = 0;
    HI_U32  u32MaskUpBit   = 0;
    HI_U32  u32MaskDownBit = 0;
    HI_U32  u32SwitchBit   = 0;
    HI_U32  u32MaskTopBit  = 0;
    HI_U32  u32MaskBit     = 0;
    HI_U32  u32LayerCount  = 0;
    HI_S32  count          = 0;
    OPTM_VDP_CBM_MIX_E eCbmMixg = VDP_CBM_MIX_BUTT;
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_0;

    if (HI_SUCCESS != OPTM_GfxGetLayerPriority(enLayerId, &u32LayerPrio))
    {
        HIFB_ERROR("info:fail to set z_order of gfx%d!\n",enLayerId);
        return HI_FAILURE;
    }

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGpId = g_pstGfxDevice[enLayerId]->enGPId;
    HIFB_CHECK_GPID_SUPPORT_RETURN(enGpId, HI_FAILURE);

    eCbmMixg = (enGpId == OPTM_GFX_GP_0) ? VDP_CBM_MIXG0 : VDP_CBM_MIXG1;

    OPTM_VDP_CBM_GetMixerPrio(eCbmMixg, &u32Prio);
    u32LayerCount = (enGpId == OPTM_GFX_GP_0) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;

    u32SwitchBit = (u32Prio >> (4 * (u32LayerPrio - 1))) & 0xf;

    for (count = u32LayerPrio; count > 0; count--)
    {
        u32MaskUpBit = 0xf | (u32MaskUpBit << 4);
    }

    for (count = u32LayerPrio; count <= u32LayerCount; count++)
    {
        u32MaskDownBit = 0xf | (u32MaskDownBit << 4);
    }
    u32MaskDownBit <<= 4 * (u32LayerPrio - 1);

    u32MaskBit = 0xf;
    u32MaskTopBit = 0xf;
    for(count = 1; count < u32LayerCount; count++)
    {
        u32MaskBit = 0xf | (u32MaskBit << 4);
        u32MaskTopBit = u32MaskTopBit << 4;
    }

    u32Prio &= u32MaskBit;
    switch (enZOrder)
    {
        case HIFB_ZORDER_MOVEBOTTOM:
        {
            if (u32LayerPrio == 1)
            {
               return HI_SUCCESS;
            }
            /*当前layer之上的Z序值保持不变|当前layer之下的Z序值上移|当前layer Z序值*/
            u32Prio = (u32Prio&(~u32MaskUpBit)) | \
                      ((u32MaskUpBit&((u32Prio&u32MaskUpBit)<<4))&(~0xf)) |
                      u32SwitchBit;
            break;
        }
        case HIFB_ZORDER_MOVEDOWN:
        {
            if (u32LayerPrio == 1)
            {
               return HI_SUCCESS;
            }

            u32Prio = ((u32Prio & (0xf << 4 * (u32LayerPrio - 1))) >> 4) | \
                      ((u32Prio & (0xf << 4 * (u32LayerPrio - 2))) << 4) | \
                       (~((0xf << 4 * (u32LayerPrio - 1)) | (0xf << 4 * (u32LayerPrio - 2))) & u32Prio);
            break;
        }
        case HIFB_ZORDER_MOVETOP:
        {
            if (u32LayerPrio == u32LayerCount)
            {
               return HI_SUCCESS;
            }
            /*当前layer之下的Z序值保持不变|当前layer之上的Z序值下移|当前layer Z序值*/
            u32Prio = (u32Prio & (~u32MaskDownBit)) | \
                      ((u32MaskDownBit & ((u32Prio & u32MaskDownBit) >> 4)) & (~u32MaskTopBit)) | \
                      (u32SwitchBit << (4 * (u32LayerCount - 1)));
            break;
        }
        case HIFB_ZORDER_MOVEUP:
        {

            if (u32LayerPrio == u32LayerCount)
            {
               return HI_SUCCESS;
            }
            u32Prio = ((u32Prio & (0xf << 4 * (u32LayerPrio - 1))) << 4) | \
                      ((u32Prio & (0xf << 4 * u32LayerPrio)) >> 4) | \
                       (~((0xf << 4 * (u32LayerPrio - 1)) | (0xf << 4 * u32LayerPrio)) & u32Prio);
            break;
        }
        default:
        {
            return HI_FAILURE;
        }
    }

    u32Prio &= u32MaskBit;

    OPTM_VDP_SetMixgPrio(eCbmMixg, u32Prio);

    g_pstGfxGPDevice[enGpId]->u32Prior = u32Prio;

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_DispInfoUpdate
* description   : CNcomment: 更新display信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
STATIC HI_S32 OPTM_DispInfoUpdate(OPTM_VDP_LAYER_GP_E enGPId)
{
    HI_U32           i;
    HI_U32           u32LayerCount;
    HI_RECT_S        *pstDispRect;
    HIFB_LAYER_ID_E  enInitLayerId;
    HIFB_LAYER_ID_E  enLayerId;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (!g_pstGfxGPDevice[enGPId]->bOpen)
    {
        return HI_SUCCESS;
    }

    OPTM_CheckGPMask_BYGPID((OPTM_GFX_GP_E)enGPId);

    u32LayerCount = (OPTM_VDP_LAYER_GP0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_VDP_LAYER_GP0 == enGPId) ? HIFB_LAYER_HD_0 : HIFB_LAYER_SD_0;

    pstDispRect = &g_pstGfxGPDevice[enGPId]->stOutRect;

    if (IS_SLAVER_GP((OPTM_GFX_GP_E)enGPId))
    {
        OPTM_GPSetCsc(enGPId, &g_pstGfxGPDevice[enGPId]->stCscPara,g_pstGfxGPDevice[enGPId]->bBGRState);
    #ifdef CONFIG_HIFB_VERSION_1_0
        HIFB_WBC2_CfgSlvLayer(HIFB_LAYER_SD_0, pstDispRect);
    #endif
        return HI_SUCCESS;
    }

    OPTM_GfxSetDispFMTSize((OPTM_GFX_GP_E)enGPId, pstDispRect);

#ifdef CONFIG_HIFB_VERSION_1_0
    OPTM_GPSetCsc(enGPId, &g_pstGfxGPDevice[enGPId]->stCscPara,g_pstGfxGPDevice[enGPId]->bBGRState);
#endif

    for (i = 0; i < u32LayerCount;i++)
    {
        enLayerId = enInitLayerId + i;

        if (!g_pstGfxDevice[enLayerId]->bOpened)
        {
            continue;
        }

        OPTM_GfxSetLayerRect(enLayerId, &g_pstGfxDevice[enLayerId]->stInRect);
        OPTM_VDP_GFX_SetUpdMode(g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enUpDateMode);
        #ifndef CONFIG_HIFB_VERSION_1_0
        OPTM_VDP_GFX_SetRegUp(enLayerId);
        #endif
    }

    OPTM_VDP_GP_SetRegUp   (enGPId);

    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GPRecovery
* description  : CNcomment: 重新设置GP属性 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GPRecovery(OPTM_GFX_GP_E enGPId)
{
    HI_U32           i             = 0;
    HI_U32           u32LayerCount = 0;
    HI_RECT_S        *pstDispRect  = NULL;
    HIFB_LAYER_ID_E  enInitLayerId = HIFB_LAYER_HD_0;
    HIFB_LAYER_ID_E  enLayerId     = HIFB_LAYER_HD_0;

    HIFB_CHECK_GPID_SUPPORT_RETURN(enGPId, HI_FAILURE);

    if (!g_pstGfxGPDevice[enGPId]->bOpen)
    {
        return HI_SUCCESS;
    }

    pstDispRect = &g_pstGfxGPDevice[enGPId]->stOutRect;

    OPTM_CheckGPMask_BYGPID(enGPId);

    u32LayerCount = (OPTM_GFX_GP_0 == enGPId) ? OPTM_GP0_GFX_COUNT : OPTM_GP1_GFX_COUNT;
    enInitLayerId = (OPTM_GFX_GP_0 == enGPId) ? HIFB_LAYER_HD_0    : HIFB_LAYER_SD_0;

    OPTM_VDP_CBM_SetMixerBkg    (g_pstGfxGPDevice[enGPId]->enMixg, &(g_pstGfxGPDevice[enGPId]->stBkg));
    OPTM_VDP_SetMixgPrio        (g_pstGfxGPDevice[enGPId]->enMixg, g_pstGfxGPDevice[enGPId]->u32Prior);
    OPTM_VDP_GP_SetLayerGalpha  (enGPId, g_pstGfxGPDevice[enGPId]->u32Alpha);

#ifdef CONFIG_HIFB_VERSION_1_0
    OPTM_GPSetCsc(enGPId, &g_pstGfxGPDevice[enGPId]->stCscPara,g_pstGfxGPDevice[enGPId]->bBGRState);
#endif

    if (IS_SLAVER_GP(enGPId))
    {
        HIFB_WBC2_Recovery(enGPId);
        return HI_SUCCESS;
    }

    OPTM_GfxSetDispFMTSize (enGPId, pstDispRect);
    OPTM_VDP_GP_SetRegUp   (enGPId);

    for (i = 0; i < u32LayerCount;i++)
    {
        enLayerId = enInitLayerId + i;
        if (!g_pstGfxDevice[enLayerId]->bOpened)
        {
            OPTM_VDP_GFX_SetLayerEnable (g_pstGfxDevice[enLayerId]->enGfxHalId, HI_FALSE);
            OPTM_VDP_GFX_SetRegUp       (g_pstGfxDevice[enLayerId]->enGfxHalId);
            continue;
        }

        OPTM_GfxSetLayerAlpha     (enLayerId, &g_pstGfxDevice[enLayerId]->stAlpha);
        OPTM_GfxSetLayKeyMask     (enLayerId, &g_pstGfxDevice[enLayerId]->stColorkey);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
        OPTM_GfxSetTriDimMode     (enLayerId, g_pstGfxDevice[enLayerId]->enTriDimMode, g_pstGfxGPDevice[OPTM_SLAVER_GPID]->enTriDimMode);
        OPTM_GfxSetTriDimAddr     (enLayerId, g_pstGfxDevice[enLayerId]->u32TriDimAddr);
        OPTM_GFX_SetStereoDepth   (enLayerId, g_pstGfxDevice[enLayerId]->s32Depth);
#endif

        OPTM_GfxSetLayerPreMult   (enLayerId, g_pstGfxDevice[enLayerId]->bPreMute);
        OPTM_GfxSetLayerDataFmt   (enLayerId, g_pstGfxDevice[enLayerId]->enDataFmt);
        OPTM_GfxSetLayerRect      (enLayerId, &g_pstGfxDevice[enLayerId]->stInRect);

        OPTM_VDP_GFX_SetLutAddr   (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->stCluptTable.u32StartPhyAddr);
        OPTM_VDP_GFX_SetParaUpd   (g_pstGfxDevice[enLayerId]->enGfxHalId, VDP_DISP_COEFMODE_LUT);
        OPTM_VDP_GFX_SetLayerBkg  (g_pstGfxDevice[enLayerId]->enGfxHalId, &(g_pstGfxDevice[enLayerId]->stBkg));
        OPTM_VDP_GFX_SetBitExtend (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enBitExtend);

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(HI_BUILD_IN_BOOT)
        if ((HIFB_LAYER_HD_0 == enLayerId) && (HI_TRUE == g_pstGfxDevice[enLayerId]->bDmpOpened))
        {
            OPTM_GFX_DECMP_Open(enLayerId);
        }
#endif

#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT) && !defined(CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE) && !defined(HI_BUILD_IN_BOOT)
        if (HI_TRUE == g_pstGfxDevice[enLayerId]->bDmpOpened)
        {
           DRV_HAL_SetDeCmpDdrInfo(enLayerId,g_pstGfxDevice[enLayerId]->ARHeadDdr,g_pstGfxDevice[enLayerId]->ARDataDdr,g_pstGfxDevice[enLayerId]->GBHeadDdr,g_pstGfxDevice[enLayerId]->GBDataDdr,g_pstGfxDevice[enLayerId]->CmpStride);
        }
        else
#endif
        {
            OPTM_GfxSetLayerStride(enLayerId, g_pstGfxDevice[enLayerId]->Stride);
            OPTM_GfxSetLayerAddr(enLayerId, g_pstGfxDevice[enLayerId]->NoCmpBufAddr);
        }

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
        /*gfx3 have no zme*/
        if (OPTM_VDP_LAYER_GFX3 == g_pstGfxDevice[enLayerId]->enGfxHalId)
        {
            g_pstGfxDevice[enLayerId]->enReadMode = VDP_RMODE_PROGRESSIVE;
        }
#endif
        OPTM_GfxSetLayerReadMode(enLayerId, g_pstGfxDevice[enLayerId]->enReadMode);
        OPTM_VDP_GFX_SetUpdMode (g_pstGfxDevice[enLayerId]->enGfxHalId, g_pstGfxDevice[enLayerId]->enUpDateMode);
        OPTM_GfxSetEnable       (enLayerId, g_pstGfxDevice[enLayerId]->bEnable);
   }

   return HI_SUCCESS;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func        : OPTM_VO_Callback
* description : CNcomment: VO CALLBACK CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 OPTM_VO_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
    HI_U32 i;
    HI_U32 u32CTypeFlag;
    HI_U32 u32LayerCount;
    HI_ULONG LockFlag = 0;
    HIFB_LAYER_ID_E enInitLayerId;
    OPTM_VDP_LAYER_GP_E *pEnGpHalId  = (OPTM_VDP_LAYER_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if ((NULL == pEnGpHalId) || (NULL == pstDispInfo))
    {
        return HI_FAILURE;
    }

    u32LayerCount = (OPTM_VDP_LAYER_GP0 == *pEnGpHalId) ? (OPTM_GP0_GFX_COUNT) : (OPTM_GP1_GFX_COUNT);
    enInitLayerId = (OPTM_VDP_LAYER_GP0 == *pEnGpHalId) ? (HIFB_LAYER_HD_0) : (HIFB_LAYER_SD_0);

    HIFB_CHECK_GPID_SUPPORT_RETURN(*pEnGpHalId, HI_FAILURE);

    for (i = 0; i < u32LayerCount;i++)
    {
        u32CTypeFlag = g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].u32CTypeFlag;
        if (HIFB_CALLBACK_TYPE_VO != (u32CTypeFlag & HIFB_CALLBACK_TYPE_VO))
        {
           continue;
        }

        /**ensure the func has not be set null **/
        spin_lock_irqsave(&(g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].FuncLock),LockFlag);

        if (NULL != g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pFunc)
        {
            if (g_pstGfxGPDevice[*pEnGpHalId]->bHdr != g_pstGfxGPDevice[*pEnGpHalId]->bPreHdr)
            {
               g_pstGfxGPDevice[*pEnGpHalId]->bPreHdr = g_pstGfxGPDevice[*pEnGpHalId]->bHdr;
               OPTM_VDP_GFX_SetPreMultEnable(g_pstGfxDevice[i]->enGfxHalId, g_pstGfxDevice[i]->bPreMute, g_pstGfxGPDevice[*pEnGpHalId]->bHdr);
            }
            g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pFunc(
                g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].pParam0,HI_NULL);
        }

        spin_unlock_irqrestore(&(g_pstGfxGPIrq[*pEnGpHalId]->stGfxCallBack[i].stGfxIrq[HIFB_CALLBACK_TYPE_VO].FuncLock),LockFlag);
    }

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : OPTM_Distribute_Callback
* description   : CNcomment: 分发中断处理类型 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_Distribute_Callback(HI_VOID* u32Param0, HI_VOID* u32Param1)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_STEREO_MODE_E enTriDimMode;
#endif
    OPTM_GFX_GP_E *penGpId = (OPTM_GFX_GP_E *)u32Param0;
    HI_DRV_DISP_CALLBACK_INFO_S *pstDispInfo = (HI_DRV_DISP_CALLBACK_INFO_S *)u32Param1;

    if (penGpId == HI_NULL || pstDispInfo == HI_NULL)
    {
        return HI_FAILURE;
    }

    OPTM_VO_Callback(u32Param0, u32Param1);

#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
    HIFB_CHECK_GPID_SUPPORT_RETURN(*penGpId, HI_FAILURE);

    enTriDimMode = OPTM_AdaptTriDimModeFromDisp(OPTM_DISP_GetDispMode(g_pstGfxGPDevice[*penGpId]->enGpHalId));

    if ((enTriDimMode != g_pstGfxGPDevice[*penGpId]->enTriDimMode) && (HIFB_STEREO_BUTT > enTriDimMode))
    {
        if (OPTM_CheckGfxCallbackReg((OPTM_GFX_GP_E)(*penGpId), HIFB_CALLBACK_TYPE_3DMode_CHG) != HI_SUCCESS)
        {
           return HI_SUCCESS;
        }

        g_pstGfxGPDevice[*penGpId]->enTriDimMode = enTriDimMode;

        OPTM_VDP_GP_SetRegUp(*penGpId);

        g_pstGfxGPDevice[*penGpId]->st3DModeChgWork.u32Data = *penGpId;

        if (NULL != g_pstGfxGPDevice[*penGpId]->queue)
        {
           queue_work(g_pstGfxGPDevice[*penGpId]->queue, &g_pstGfxGPDevice[*penGpId]->st3DModeChgWork.work);
        }
    }
#endif

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func          : OPTM_GFX_SetGPMask
* description   : CNcomment: 这个接口只有开机logo才会用到，主要是用来过渡使用的
                        设置GP0和GP1掩码，并且在logo过渡完之后重新设置GP CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GFX_SetGPMask(HIFB_LAYER_ID_E LayerId, HI_BOOL bFlag)
{
#ifndef HI_BUILD_IN_BOOT
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_BUTT;
    HIFB_OSD_DATA_S stLayerData;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, HI_FAILURE);
    enGpId = OPTM_GFX_GetGpId(LayerId);

    g_pstGfxGPDevice[enGpId]->bMaskFlag = bFlag;

    if (!bFlag)
    {
        OPTM_GPRecovery(enGpId);
    }

    if (OPTM_MASTER_GPID == enGpId)
    {
        OPTM_GfxGetOSDData(HIFB_LAYER_SD_0, &stLayerData);

        if (IS_MASTER_GP(enGpId) || HIFB_LAYER_STATE_ENABLE == stLayerData.eState)
        {
            g_pstGfxGPDevice[OPTM_SLAVER_GPID]->bMaskFlag = bFlag;
            if(!bFlag && g_stGfxWbc2.IsOpen)
            {
                OPTM_GPRecovery(OPTM_SLAVER_GPID);
            }
        }
    }
#else
    HI_UNUSED(LayerId);
    HI_UNUSED(bFlag);
#endif
    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GFX_GetGfxMask
* description  : CNcomment: 获取GP设置掩码 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GFX_GetGfxMask(HIFB_LAYER_ID_E LayerId)
{
    OPTM_GFX_GP_E enGpId = OPTM_GFX_GP_BUTT;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerId, HI_FAILURE);
    enGpId = OPTM_GFX_GetGpId(LayerId);

    return g_pstGfxGPDevice[enGpId]->bMaskFlag;
}

/***************************************************************************************
* func          : OPTM_GFX_ClearLogoOsd
* description   : CNcomment: 清logo CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
STATIC HI_S32 OPTM_GFX_ClearLogoOsd(HIFB_LAYER_ID_E enLayerId)
{
    HI_UNUSED(enLayerId);
    return HI_SUCCESS;
}

#if !defined(HI_BUILD_IN_BOOT) && defined(CFG_HIFB_STEREO3D_HW_SUPPORT)
/***************************************************************************************
* func          : OPTM_GFX_SetStereoDepth
* description   : CNcomment: 设置3D  景深，与人眼的距离 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 OPTM_GFX_SetStereoDepth(HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth)
{
    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    g_pstGfxDevice[enLayerId]->s32Depth = s32Depth;

    if (g_pstGfxDevice[enLayerId]->s32Depth != 0)
    {
        OPTM_VDP_GFX_SetThreeDimDofEnable(OPTM_GetGfxHalId(enLayerId), HI_TRUE);
    }

    OPTM_VDP_GFX_SetThreeDimDofStep(OPTM_GetGfxHalId(enLayerId), s32Depth, (0 - s32Depth));

    return HI_SUCCESS;
}
#endif

/***************************************************************************************
* func          : OPTM_GFX_SetTCFlag
* description   : CNcomment: 设置是不是TC使用场景标识 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_GFX_SetTCFlag(HI_BOOL bFlag)
{
    HIFB_WBC2_SetTcFlag(bFlag);
    return HI_SUCCESS;
}

/***************************************************************************************
* func         : OPTM_GFX_GetHaltDispStatus
* description  : CNcomment: 获取显示状态 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
static HI_S32 OPTM_GFX_GetHaltDispStatus(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbDispInit)
{
    OPTM_GFX_GP_E enGPId = OPTM_GFX_GP_0;

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(enLayerId, HI_FAILURE);
    enGPId = OPTM_GFX_GetGpId(enLayerId);

    HIFB_CHECK_NULLPOINTER_RETURN(pbDispInit, HI_FAILURE);
    *pbDispInit =  g_pstGfxGPDevice[enGPId]->bGpClose? HI_FALSE : HI_TRUE;

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : OPTM_AllocAndMap
* description   : CNcomment: alloc and map mem CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf)
{
#ifndef HI_BUILD_IN_BOOT
    return HI_GFX_AllocAndMap(bufname, zone_name, size, align, psMBuf);
#else
    HIFB_CHECK_EQUAL_RETURN(0, size, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(psMBuf, HI_FAILURE);
    if (HI_SUCCESS == HI_DRV_PDM_AllocReserveMem(bufname, size, &psMBuf->u32StartPhyAddr))
    {
        psMBuf->pu8StartVirAddr = (HI_U8*)psMBuf->u32StartPhyAddr;
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
#endif
}

/***************************************************************************************
* func         : OPTM_UnmapAndRelease
* description  : unmap the ddr and release it\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_UnmapAndRelease(GFX_MMZ_BUFFER_S *psMBuf)
{
#ifdef HI_BUILD_IN_BOOT
    HI_UNUSED(psMBuf);
    return;
#else
    HI_GFX_UnmapAndRelease(psMBuf);
#endif
}

/***************************************************************************************
* func          : OPTM_Adapt_AllocAndMap
* description   : CNcomment: 分配内存并映射地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_Adapt_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, GFX_MMZ_BUFFER_S *psMBuf)
{
#ifndef HI_BUILD_IN_BOOT
    return HI_GFX_AllocAndMap(bufname, zone_name, size, align, psMBuf);
#else

    HIFB_CHECK_EQUAL_RETURN(0, size, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(psMBuf, HI_FAILURE);

    psMBuf->u32StartPhyAddr = (HI_U32)HI_GFX_Malloc(size,"hifb_wbc_buffer");
    if (HI_NULL == psMBuf->u32StartPhyAddr)
    {
        HIFB_ERROR("fail to alloc buffer.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
#endif
}


#ifdef HI_BUILD_IN_BOOT
HI_BOOL HIFB_ADP_GetIsGfxWorkAtWbc(HI_VOID)
{
    return (HIFB_GFX_MODE_HD_WBC == g_enOptmGfxWorkMode) ? (HI_TRUE) : (HI_FALSE);
}
#endif


#ifndef HI_BUILD_IN_BOOT
static HI_S32 OPTM_GFX_ColorConvert(const struct fb_var_screeninfo *pstVar, HIFB_COLORKEYEX_S *pCkey)
{
    HI_U8 rOff, gOff, bOff;

    if ((NULL == pstVar) || (NULL == pCkey))
    {
       return HI_FAILURE;
    }

    rOff = pstVar->red.length;
    gOff = pstVar->green.length;
    bOff = pstVar->blue.length;

    pCkey->u8RedMask   = (0xff >> rOff);
    pCkey->u8GreenMask = (0xff >> gOff);
    pCkey->u8BlueMask  = (0xff >> bOff);

    return HI_SUCCESS;
}
#endif

static HI_S32 OPTM_GFX_PauseCompression(HIFB_LAYER_ID_E enLayerId)
{
     HI_UNUSED(enLayerId);
     return HI_SUCCESS;
}

static HI_S32 OPTM_GFX_ResumeCompression(HIFB_LAYER_ID_E enLayerId)
{
     HI_UNUSED(enLayerId);
     return HI_SUCCESS;
}

static HI_VOID OPTM_GFX_SetDeCmpSwitch(HIFB_LAYER_ID_E enLayerId, HI_BOOL bOpen)
{
#if defined(CFG_HI_FB_DECOMPRESS_SUPPORT)
    if (bOpen)
    {
        OPTM_GFX_DECMP_Open(enLayerId);
    }
    else
    {
        OPTM_GFX_DECMP_Close(enLayerId);
    }
#else
    HI_UNUSED(enLayerId);
    HI_UNUSED(bOpen);
#endif
}

/***************************************************************************************
* func        : DRV_HIFB_GetAdpCallBackFunction
* description : CNcomment: 获取设备上下文 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID DRV_HIFB_GetAdpCallBackFunction(HIFB_DRV_OPS_S *AdpCallBackFunction)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(AdpCallBackFunction);
    AdpCallBackFunction->HIFB_DRV_CloseLayer                    = OPTM_GfxCloseLayer;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_ColorConvert                  = OPTM_GFX_ColorConvert;
#endif
    AdpCallBackFunction->HIFB_DRV_EnableLayer                   = OPTM_GfxSetEnable;
    AdpCallBackFunction->HIFB_DRV_GetGFXCap                     = OPTM_GFX_GetDevCap;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_GetOSDData                    = OPTM_GfxGetOSDData;
    AdpCallBackFunction->HIFB_DRV_GetLogoData                   = HIFB_ADP_GetLogoData;
#endif
    AdpCallBackFunction->HIFB_DRV_GetLayerPriority              = OPTM_GfxGetLayerPriority;
    AdpCallBackFunction->HIFB_DRV_GfxDeInit                     = OPTM_GfxDeInit;
    AdpCallBackFunction->HIFB_DRV_GfxInit                       = OPTM_GfxInit;
    AdpCallBackFunction->HIFB_DRV_OpenLayer                     = OPTM_GfxOpenLayer;
    AdpCallBackFunction->HIFB_DRV_PauseCompression              = OPTM_GFX_PauseCompression;
    AdpCallBackFunction->HIFB_DRV_ResumeCompression             = OPTM_GFX_ResumeCompression;
    AdpCallBackFunction->HIFB_DRV_SetColorReg                   = OPTM_GFX_SetClutColorReg;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_SetTriDimMode                 = OPTM_GfxSetTriDimMode;
    AdpCallBackFunction->HIFB_DRV_SetTriDimAddr                 = OPTM_GfxSetTriDimAddr;
#endif
    AdpCallBackFunction->HIFB_DRV_SetLayerAddr                  = OPTM_GfxSetLayerAddr;
    AdpCallBackFunction->HIFB_DRV_GetLayerAddr                  = OPTM_GfxGetLayerAddr;
    AdpCallBackFunction->HIFB_DRV_SetLayerAlpha                 = OPTM_GfxSetLayerAlpha;
    AdpCallBackFunction->HIFB_DRV_SetLayerDataFmt               = OPTM_GfxSetLayerDataFmt;
    AdpCallBackFunction->HIFB_DRV_SetLayerDeFlicker             = OPTM_GfxSetLayerDeFlicker;
    AdpCallBackFunction->HIFB_DRV_SetLayerPriority              = OPTM_GfxSetLayerPriority;
    AdpCallBackFunction->HIFB_DRV_UpdataLayerReg                = OPTM_GfxUpLayerReg;
    AdpCallBackFunction->HIFB_DRV_GetDhd0Info                   = HIFB_ADP_GetDhd0Info;
    AdpCallBackFunction->HIFB_ADP_GetCloseState                 = HIFB_ADP_GetCloseState;
    AdpCallBackFunction->HIFB_DRV_WaitVBlank                    = OPTM_GfxWaitVBlank;
    AdpCallBackFunction->HIFB_DRV_SetLayerKeyMask               = OPTM_GfxSetLayKeyMask;
    AdpCallBackFunction->HIFB_DRV_SetLayerPreMult               = OPTM_GfxSetLayerPreMult;
    AdpCallBackFunction->HIFB_DRV_GetLayerPreMult               = OPTM_GfxGetLayerPreMult;
    AdpCallBackFunction->HIFB_DRV_GetLayerHdr                   = OPTM_GfxGetLayerHdr;
    AdpCallBackFunction->HIFB_DRV_GetClosePreMultState          = OPTM_GfxGetClosePreMultState;
    AdpCallBackFunction->HIFB_DRV_ReadRegister                  = OPTM_GfxReadRegister;
    AdpCallBackFunction->HIFB_DRV_WriteRegister                 = OPTM_GfxWriteRegister;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_WhetherDiscardFrame           = OPTM_GfxWhetherDiscardFrame;
    AdpCallBackFunction->HIFB_DRV_SetIntCallback                = OPTM_GfxSetCallback;
#endif
    AdpCallBackFunction->HIFB_DRV_SetLayerStride                = OPTM_GfxSetLayerStride;
    AdpCallBackFunction->HIFB_DRV_SetLayerInRect                = OPTM_GfxSetLayerRect;
    AdpCallBackFunction->HIFB_DRV_GetLayerOutRect               = OPTM_GfxGetOutRect;
    AdpCallBackFunction->HIFB_DRV_GetLayerInRect                = OPTM_GfxGetLayerRect;
    AdpCallBackFunction->HIFB_DRV_SetLayerMaskFlag              = OPTM_GFX_SetGPMask;
    AdpCallBackFunction->HIFB_DRV_GetLayerMaskFlag              = OPTM_GFX_GetGfxMask;
    AdpCallBackFunction->HIFB_DRV_GetDispSize                   = OPTM_GfxGetDispFMTSize;
    AdpCallBackFunction->HIFB_DRV_ClearLogo                     = OPTM_GFX_ClearLogoOsd;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_SetStereoDepth                = OPTM_GFX_SetStereoDepth;
#endif
    AdpCallBackFunction->HIFB_DRV_SetTCFlag                     = OPTM_GFX_SetTCFlag;
    AdpCallBackFunction->HIFB_DRV_SetDeCmpSwitch                = OPTM_GFX_SetDeCmpSwitch;
    AdpCallBackFunction->HIFB_DRV_SetDeCmpDdrInfo               = HIFB_ADP_SetDeCmpDdrInfo;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_OSI_SetLowPowerInfo               = HIFB_ADP_SetLowPowerInfo;
#endif
    AdpCallBackFunction->HIFB_DRV_GetDecompressStatus           = HIFB_ADP_GetDecompressStatus;
#ifndef HI_BUILD_IN_BOOT
    AdpCallBackFunction->HIFB_DRV_GetResumeStatus               = HIFB_ADP_GetResumeStatus;
    AdpCallBackFunction->HIFB_DRV_GetResumeForPowerOffStatus    = HIFB_ADP_GetResumeForPowerOffStatus;
#endif
    AdpCallBackFunction->HIFB_DRV_SetGpDeflicker                = OPTM_GfxSetGpDeflicker;
    AdpCallBackFunction->HIFB_DRV_GetHaltDispStatus             = OPTM_GFX_GetHaltDispStatus;
    return;
}
