/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : drv_hifb_logo.c
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                Modification
2018/01/01           sdk                  Created file
************************************************************************************************/
#ifdef CFG_HIFB_LOGO_SUPPORT

/*********************************add include here**********************************************/
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/time.h>
#include <linux/fb.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>
#include <linux/sched.h>

#include "drv_hifb_common.h"
#include "drv_hifb_mem.h"
#include "drv_hifb_logo.h"
#include "drv_hifb_wbc.h"
#include "drv_hifb_osr.h"
#include "drv_hifb_config.h"
#include "drv_hifb_paracheck.h"

#include "drv_pdm_ext.h"
#include "drv_disp_ext.h"
/***************************** Macro Definition ************************************************/
#define CHECK_WHETHER_IS_HD0LOGOID(layerid)\
        do {\
               if (HIFB_LOGO_LAYER_HD0_ID != layerid){\
                   return;\
               }\
        }while (0)

#define CONFIG_HIFB_OPENWBC_WAITE_TIME      ((4000 * HZ) / 1000)

/*************************** Structure Definition **********************************************/


/********************** Global Variable declaration ********************************************/
static HIFB_LOGO_S gs_stLogo;

extern HIFB_LAYER_S s_stLayer[HIFB_MAX_LAYER_NUM];
extern OPTM_GFX_WBC_S  g_stGfxWbc2;


static HIFB_DRV_TDEOPS_S    gs_stLogoGfx2dCallBackFunction;
static HIFB_DRV_OPS_S       gs_stLogoHifbAdpCallBackFunction;

static PDM_EXPORT_FUNC_S   *gs_pstPdmExportFuncs  = HI_NULL;

/******************************* API declaration ***********************************************/
static inline HI_VOID HIFB_GetLogoData           (HI_U32 LogoLayerId);
static inline HI_U32  HIFB_GetLogoInfoIndex      (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_BlitHdLogoToApp       (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_QuickCpyHdLogoToApp   (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_QuickCpySdLogoToApp   (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_CloseLogoLayer        (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_FreeLogoMem           (HI_U32 LogoLayerId);
static inline HI_VOID HIFB_freeHDlogoMem         (HIFB_LOGO_LAYER_E LogoLayerId);
static inline HI_VOID HIFB_freeWBClogoMem        (HIFB_LOGO_LAYER_E LogoLayerId);
static inline HI_VOID HIFB_FreeHDLogoMemWork     (struct work_struct *work);
static inline HI_VOID HIFB_FreeWBCLogoMemWork    (struct work_struct *work);

static inline HIFB_COLOR_FMT_E DRV_HIFB_ConvertBootFmtToLayerFmt(HI_U32 BootFmt);

/******************************* API relese ****************************************************/


/***************************************************************************************
* func         : DRV_HIFB_ResetLogoState
* description  : CNcomment: reset logo information state CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_HIFB_ResetLogoState(HI_VOID)
{
    HI_GFX_Memset(&gs_stLogo,0,sizeof(gs_stLogo));
    gs_stLogo.stGfxLogoInfo[HIFB_LOGO_HD0].eLogoID     = HIFB_LOGO_LAYER_HD0_ID;
    gs_stLogo.stGfxLogoInfo[HIFB_LOGO_HD1].eLogoID     = HIFB_LOGO_LAYER_HD1_ID;
    gs_stLogo.stGfxLogoInfo[HIFB_LOGO_WBC_HD0].eLogoID = HIFB_LOGO_LAYER_WBC_HD0_ID;
    gs_stLogo.stGfxLogoInfo[HIFB_LOGO_WBC_HD1].eLogoID = HIFB_LOGO_LAYER_WBC_HD1_ID;

    DRV_HIFB_GetGfx2dCallBackFunction(&gs_stLogoGfx2dCallBackFunction);
    DRV_HIFB_GetAdpCallBackFunction(&gs_stLogoHifbAdpCallBackFunction);

    (HI_VOID)HI_DRV_MODULE_GetFunction(HI_ID_PDM,  (HI_VOID**)&gs_pstPdmExportFuncs);

    return;
}


/***************************************************************************************
* func         : DRV_HIFB_WhetherHasLogo
* description  : CNcomment: check whether has logo CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_HIFB_WhetherHasLogo(HI_VOID)
{
     HI_U32 LogoInfoIndex = HIFB_LOGO_HD0;
     HIFB_LOGO_DATA_S stLogoData;

#ifndef CONFIG_HIFB_WBC_UNSUPPORT
     for (LogoInfoIndex = HIFB_LOGO_HD0; LogoInfoIndex < HIFB_LOGO_WBC_HD1; LogoInfoIndex++)
     {
          HI_GFX_Memset(&stLogoData, 0, sizeof(stLogoData));
          gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_GetLogoData(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID, &stLogoData);

          if (HI_FALSE == stLogoData.LogoEnable)
          {
             gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow = HI_FALSE;
             continue;
          }

          gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow = HI_TRUE;
     }
#else
     HI_GFX_Memset(&stLogoData, 0, sizeof(stLogoData));
     gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_GetLogoData(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID, &stLogoData);
     gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow = stLogoData.LogoEnable;
#endif

     return;
}


/***************************************************************************************
* func        : DRV_HIFB_GetLogoData
* description : CNcomment: get logo date from gfx register or video register CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID DRV_HIFB_GetLogoData(HI_U32 u32LayerId)
{
    CHECK_WHETHER_IS_HD0LOGOID(u32LayerId);

    HIFB_GetLogoData(u32LayerId);
    if (HIFB_LOGO_LAYER_HD0_ID == u32LayerId)
    {
        HIFB_GetLogoData(HIFB_LOGO_LAYER_WBC_HD0_ID);
    }

    return;
}

static inline HI_VOID HIFB_GetLogoData(HI_U32 LogoLayerId)
{
    HI_U32 LogoInfoIndex = 0;
    HIFB_LOGO_DATA_S stLogoData;

    LogoInfoIndex = HIFB_GetLogoInfoIndex(LogoLayerId);
    if ((LogoInfoIndex >= HIFB_LOGO_BUTT) || (HI_FALSE == gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow))
    {
        return;
    }

    HI_GFX_Memset(&stLogoData,0,sizeof(stLogoData));

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_GetLogoData);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_GetLogoData(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID, &stLogoData);

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerMaskFlag);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerMaskFlag(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID, HI_TRUE);

    gs_stLogo.stLogoDataInfo[LogoInfoIndex].Support4KLogo  = stLogoData.Support4KLogo;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr      = stLogoData.LogoYAddr;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoCbCrAddr   = stLogoData.LogoCbCrAddr;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoWidth      = stLogoData.LogoWidth;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoHeight     = stLogoData.LogoHeight;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYStride    = stLogoData.LogoYStride;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoCbCrStride = stLogoData.LogoCbCrStride;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].eLogoPixFmt    = stLogoData.eLogoPixFmt;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.x    = stLogoData.stOutRect.x;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.y    = stLogoData.stOutRect.y;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.w    = stLogoData.stOutRect.w;
    gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.h    = stLogoData.stOutRect.h;

    return;
}

static inline HI_U32 HIFB_GetLogoInfoIndex(HI_U32 LogoLayerId)
{
     if (HIFB_LOGO_LAYER_HD0_ID == LogoLayerId)
     {
         return HIFB_LOGO_HD0;
     }

     if (HIFB_LOGO_LAYER_WBC_HD0_ID == LogoLayerId)
     {
         return HIFB_LOGO_WBC_HD0;
     }

     return HIFB_LOGO_BUTT;
}


/***************************************************************************************
* func         : DRV_HIFB_LogoToApp
* description  : CNcomment: logo to app CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_HIFB_LogoToApp(HI_U32 u32LayerId)
{
    HI_U32 LogoInfoIndex = 0;

    CHECK_WHETHER_IS_HD0LOGOID(u32LayerId);

    LogoInfoIndex = HIFB_GetLogoInfoIndex(u32LayerId);
    if ((LogoInfoIndex >= HIFB_LOGO_BUTT) || (HI_FALSE == gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow))
    {
        return;
    }

    if (HI_TRUE == gs_stLogo.stLogoDataInfo[LogoInfoIndex].Support4KLogo)
    {
        HIFB_BlitHdLogoToApp(u32LayerId);
    }
    else
    {
        HIFB_QuickCpyHdLogoToApp(u32LayerId);
    }

    HIFB_QuickCpySdLogoToApp(HIFB_LOGO_LAYER_WBC_HD0_ID);

    return;
}

static inline HI_VOID HIFB_BlitHdLogoToApp(HI_U32 LogoLayerId)
{
    HI_U32 LogoInfoIndex  = 0;
    struct fb_info *info  = NULL;
    HIFB_PAR_S *par = NULL;
    HIFB_BLIT_BUFFER_S stLogoBuf;
    HIFB_BLIT_BUFFER_S stAppBuf;
    HIFB_BLIT_OPT_S stOpt;

    CHECK_WHETHER_IS_HD0LOGOID(LogoLayerId);
    info = s_stLayer[LogoLayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    LogoInfoIndex = HIFB_GetLogoInfoIndex(LogoLayerId);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(LogoInfoIndex, HIFB_LOGO_BUTT);

    if (0 == gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr)
    {
       return;
    }

    HI_GFX_Memset(&stOpt, 0, sizeof(stOpt));
    HI_GFX_Memset(&stLogoBuf, 0, sizeof(stLogoBuf));
    HI_GFX_Memset(&stAppBuf,  0, sizeof(stAppBuf));

    stLogoBuf.stCanvas.YAddr   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr;
    stLogoBuf.stCanvas.Width   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoWidth;
    stLogoBuf.stCanvas.Height  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoHeight;
    stLogoBuf.stCanvas.YStride = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYStride;
    stLogoBuf.stCanvas.enFmt   = HIFB_FMT_ARGB8888;
    if (HIFB_LOGO_PIX_FMT_ARGB1555 == gs_stLogo.stLogoDataInfo[LogoInfoIndex].eLogoPixFmt)
    {
       stLogoBuf.stCanvas.enFmt = HIFB_FMT_ARGB1555;
    }

    stLogoBuf.UpdateRect.x  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.x;
    stLogoBuf.UpdateRect.y  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.y;
    stLogoBuf.UpdateRect.w  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.w;
    stLogoBuf.UpdateRect.h  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].stOutRect.h;

    stAppBuf.stCanvas.enFmt      = par->stExtendInfo.enColFmt;
    stAppBuf.stCanvas.YAddr      = info->fix.smem_start;
    stAppBuf.stCanvas.Width      = par->stExtendInfo.u32DisplayWidth;
    stAppBuf.stCanvas.Height     = par->stExtendInfo.u32DisplayHeight;
    stAppBuf.stCanvas.YStride    = info->fix.line_length;

    stAppBuf.UpdateRect.x        = 0;
    stAppBuf.UpdateRect.y        = 0;
    stAppBuf.UpdateRect.w        = stAppBuf.stCanvas.Width;
    stAppBuf.UpdateRect.h        = stAppBuf.stCanvas.Height;

    stOpt.bScale = HI_TRUE;

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_MbBlitEx);
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone);

    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_MbBlitEx(&stLogoBuf, &stAppBuf, &stOpt);
    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone(HI_TRUE);

#if 0
    HI_PRINT("\n===================================================\n");
    HI_PRINT("hd blit logo buffer\n");
    HI_PRINT("layer id = %d\n",  LogoLayerId);
    HI_PRINT("y ddr  = 0x%x\n",  stLogoBuf.stCanvas.YAddr);
    HI_PRINT("width  = %d\n",    stLogoBuf.stCanvas.Width);
    HI_PRINT("height = %d\n",    stLogoBuf.stCanvas.Height);
    HI_PRINT("stride = %d\n",    stLogoBuf.stCanvas.YStride);
    HI_PRINT("pix format = %d\n",stLogoBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stLogoBuf.UpdateRect.x,stLogoBuf.UpdateRect.y,stLogoBuf.UpdateRect.w,stLogoBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");

    HI_PRINT("\n===================================================\n");
    HI_PRINT("hd app buffer\n");
    HI_PRINT("y ddr  = 0x%x\n",  stAppBuf.stCanvas.YAddr);
    HI_PRINT("width  = %d\n",    stAppBuf.stCanvas.Width);
    HI_PRINT("height = %d\n",    stAppBuf.stCanvas.Height);
    HI_PRINT("stride = %d\n",    stAppBuf.stCanvas.YStride);
    HI_PRINT("pix format = %d\n",stAppBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stAppBuf.UpdateRect.x,stAppBuf.UpdateRect.y,stAppBuf.UpdateRect.w,stAppBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");
#endif

    return;
}


static inline HI_VOID HIFB_QuickCpyHdLogoToApp(HI_U32 LogoLayerId)
{
    struct fb_info *info  = NULL;
    HIFB_PAR_S *par = NULL;
    HIFB_BUFFER_S stLogoBuf;
    HIFB_BUFFER_S stAppBuf;
    HI_U32 LogoInfoIndex  = 0;

    CHECK_WHETHER_IS_HD0LOGOID(LogoLayerId);
    info  = s_stLayer[LogoLayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    LogoInfoIndex = HIFB_GetLogoInfoIndex(LogoLayerId);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(LogoInfoIndex, HIFB_LOGO_BUTT);

    if (0 == gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr)
    {
       return;
    }

    HI_GFX_Memset(&stLogoBuf, 0, sizeof(stLogoBuf));
    HI_GFX_Memset(&stAppBuf,  0, sizeof(stAppBuf));

    stLogoBuf.stCanvas.u32PhyAddr = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr;
    stLogoBuf.stCanvas.u32Width   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoWidth;
    stLogoBuf.stCanvas.u32Height  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoHeight;
    stLogoBuf.stCanvas.u32Pitch   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYStride;
    stLogoBuf.stCanvas.enFmt      = HIFB_FMT_ARGB8888;
    if (HIFB_LOGO_PIX_FMT_ARGB1555 == gs_stLogo.stLogoDataInfo[LogoInfoIndex].eLogoPixFmt)
    {
       stLogoBuf.stCanvas.enFmt = HIFB_FMT_ARGB1555;
    }
    stLogoBuf.UpdateRect.x        = 0;
    stLogoBuf.UpdateRect.y        = 0;
    stLogoBuf.UpdateRect.w        = stLogoBuf.stCanvas.u32Width;
    stLogoBuf.UpdateRect.h        = stLogoBuf.stCanvas.u32Height;

    stAppBuf.stCanvas.enFmt      = par->stExtendInfo.enColFmt;
    stAppBuf.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stAppBuf.stCanvas.u32Width   = par->stExtendInfo.u32DisplayWidth;
    stAppBuf.stCanvas.u32Pitch   = info->fix.line_length;
    stAppBuf.stCanvas.u32PhyAddr = info->fix.smem_start;
    stAppBuf.UpdateRect.x        = 0;
    stAppBuf.UpdateRect.y        = 0;
    stAppBuf.UpdateRect.w        = stAppBuf.stCanvas.u32Width;
    stAppBuf.UpdateRect.h        = stAppBuf.stCanvas.u32Height;

#ifdef CONFIG_GFX_MMU_SUPPORT
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy);
    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stLogoBuf, &stAppBuf, HI_TRUE);
#else
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy);
    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stLogoBuf, &stAppBuf, HI_FALSE);
#endif

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone);
    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone(HI_TRUE);

#if 0
    HI_PRINT("\n===================================================\n");
    HI_PRINT("hd quickcpy logo buffer\n");
    HI_PRINT("layer id = %d\n",  LogoLayerId);
    HI_PRINT("y ddr  = 0x%x\n",  stLogoBuf.stCanvas.u32PhyAddr);
    HI_PRINT("width  = %d\n",    stLogoBuf.stCanvas.u32Width);
    HI_PRINT("height = %d\n",    stLogoBuf.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",    stLogoBuf.stCanvas.u32Pitch);
    HI_PRINT("pix format = %d\n",stLogoBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stLogoBuf.UpdateRect.x,stLogoBuf.UpdateRect.y,stLogoBuf.UpdateRect.w,stLogoBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");

    HI_PRINT("\n===================================================\n");
    HI_PRINT("hd app buffer\n");
    HI_PRINT("y ddr  = 0x%x\n",  stAppBuf.stCanvas.u32PhyAddr);
    HI_PRINT("width  = %d\n",    stAppBuf.stCanvas.u32Width);
    HI_PRINT("height = %d\n",    stAppBuf.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",    stAppBuf.stCanvas.u32Pitch);
    HI_PRINT("pix format = %d\n",stAppBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stAppBuf.UpdateRect.x,stAppBuf.UpdateRect.y,stAppBuf.UpdateRect.w,stAppBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");
#endif
    return;
}


static inline HI_VOID HIFB_QuickCpySdLogoToApp(HI_U32 LogoLayerId)
{
    HI_U32 LogoInfoIndex  = 0;
    HIFB_BUFFER_S stLogoBuf;
    HIFB_BUFFER_S stAppBuf;

    LogoInfoIndex = HIFB_GetLogoInfoIndex(LogoLayerId);
    if ((LogoInfoIndex >= HIFB_LOGO_BUTT) || (HI_FALSE == gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow))
    {
        return;
    }

    if (0 == gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr)
    {
       return;
    }

    HI_GFX_Memset(&stLogoBuf, 0, sizeof(stLogoBuf));
    HI_GFX_Memset(&stAppBuf,  0, sizeof(stAppBuf));

    stLogoBuf.stCanvas.u32PhyAddr = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYAddr;
    stLogoBuf.stCanvas.u32Width   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoWidth;
    stLogoBuf.stCanvas.u32Height  = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoHeight;
    stLogoBuf.stCanvas.u32Pitch   = gs_stLogo.stLogoDataInfo[LogoInfoIndex].LogoYStride;
    stLogoBuf.stCanvas.enFmt      = HIFB_FMT_ARGB8888;

    stLogoBuf.UpdateRect.x  = 0;
    stLogoBuf.UpdateRect.y  = 0;
    stLogoBuf.UpdateRect.w  = stLogoBuf.stCanvas.u32Width;
    stLogoBuf.UpdateRect.h  = stLogoBuf.stCanvas.u32Height;

    (HI_VOID)wait_event_interruptible_timeout(g_stGfxWbc2.WaiteWbcWorkqueueMutex,
                                              (0 != g_stGfxWbc2.u32WBCBuffer[g_stGfxWbc2.u32BufIndex]),
                                              CONFIG_HIFB_OPENWBC_WAITE_TIME);

    stAppBuf.stCanvas.enFmt      = HIFB_FMT_ARGB8888;
    stAppBuf.stCanvas.u32PhyAddr = g_stGfxWbc2.u32WBCBuffer[g_stGfxWbc2.u32BufIndex];
    stAppBuf.stCanvas.u32Width   = g_stGfxWbc2.s32BufferWidth;
    stAppBuf.stCanvas.u32Height  = g_stGfxWbc2.s32BufferHeight;
    stAppBuf.stCanvas.u32Pitch   = g_stGfxWbc2.u32BufferStride;

    stAppBuf.UpdateRect.x  = 0;
    stAppBuf.UpdateRect.y  = 0;
    stAppBuf.UpdateRect.w  = stAppBuf.stCanvas.u32Width;
    stAppBuf.UpdateRect.h  = stAppBuf.stCanvas.u32Height;

    #ifdef CONFIG_GFX_MMU_SUPPORT
       HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy);
       gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stLogoBuf, &stAppBuf, HI_TRUE);
    #else
       HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy);
       gs_stLogoGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stLogoBuf, &stAppBuf, HI_FALSE);
    #endif

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone);
    gs_stLogoGfx2dCallBackFunction.HIFB_DRV_WaitAllTdeDone(HI_TRUE);

#if 0
    HI_PRINT("\n===================================================\n");
    HI_PRINT("wbc quickcpy logo buffer\n");
    HI_PRINT("layer id = %d\n",  LogoLayerId);
    HI_PRINT("y ddr  = 0x%x\n",  stLogoBuf.stCanvas.u32PhyAddr);
    HI_PRINT("width  = %d\n",    stLogoBuf.stCanvas.u32Width);
    HI_PRINT("height = %d\n",    stLogoBuf.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",    stLogoBuf.stCanvas.u32Pitch);
    HI_PRINT("pix format = %d\n",stLogoBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stLogoBuf.UpdateRect.x,stLogoBuf.UpdateRect.y,stLogoBuf.UpdateRect.w,stLogoBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");

    HI_PRINT("\n===================================================\n");
    HI_PRINT("wbc app buffer\n");
    HI_PRINT("y ddr  = 0x%x\n",  stAppBuf.stCanvas.u32PhyAddr);
    HI_PRINT("BufIndex = %d\n",  g_stGfxWbc2.u32BufIndex);
    HI_PRINT("width  = %d\n",    stAppBuf.stCanvas.u32Width);
    HI_PRINT("height = %d\n",    stAppBuf.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",    stAppBuf.stCanvas.u32Pitch);
    HI_PRINT("pix format = %d\n",stAppBuf.stCanvas.enFmt);
    HI_PRINT("[%d %d %d %d]\n",  stAppBuf.UpdateRect.x,stAppBuf.UpdateRect.y,stAppBuf.UpdateRect.w,stAppBuf.UpdateRect.h);
    HI_PRINT("===================================================\n");
#endif

    return;
}


/***************************************************************************************
* func         : DRV_HIFB_CloseLogo
* description  : CNcomment: close logo CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_HIFB_CloseLogo(HI_U32 u32LayerId)
{
    DRV_HIFB_CloseLogoByMask(u32LayerId);
    return;
}


HI_VOID DRV_HIFB_CloseLogoByMask(HI_U32 u32LayerId)
{
    HIFB_CloseLogoLayer(u32LayerId);

    if (HIFB_LOGO_LAYER_HD0_ID == u32LayerId)
    {
        HIFB_CloseLogoLayer(HIFB_LOGO_LAYER_WBC_HD0_ID);
    }

    HIFB_FreeLogoMem(u32LayerId);

    return;
}

static inline HI_VOID HIFB_CloseLogoLayer(HI_U32 LogoLayerId)
{
    HI_U32 LogoInfoIndex = 0;

    LogoInfoIndex = HIFB_GetLogoInfoIndex(LogoLayerId);
    if ((LogoInfoIndex >= HIFB_LOGO_BUTT) || (HI_FALSE == gs_stLogo.stGfxLogoInfo[LogoInfoIndex].bShow))
    {
        return;
    }

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerMaskFlag);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerMaskFlag(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID, HI_FALSE);

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_ClearLogo);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_ClearLogo(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID);

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_UpdataLayerReg);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_UpdataLayerReg(gs_stLogo.stGfxLogoInfo[LogoInfoIndex].eLogoID);

    return;
}


static inline HI_VOID HIFB_FreeLogoMem(HI_U32 LogoLayerId)
{
    HI_U32 LogoHDInfoIndex  = 0;
    HI_U32 LogoWBCInfoIndex = 0;

    msleep(80);

    LogoHDInfoIndex  = HIFB_GetLogoInfoIndex(LogoLayerId);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(LogoHDInfoIndex, HIFB_LOGO_BUTT);

    if (HIFB_LOGO_LAYER_HD0_ID == LogoLayerId)
    {
        LogoWBCInfoIndex = HIFB_GetLogoInfoIndex(HIFB_LOGO_LAYER_WBC_HD0_ID);
    }

    if (HI_TRUE == gs_stLogo.stGfxLogoInfo[LogoHDInfoIndex].bShow)
    {
        /** should not set in work queue **/
        /** 不要在工作队里中赋值，否则工作队列还没有执行又调用INIT_WORK将工作队列至空导致队列空指针访问 **/
        gs_stLogo.stGfxLogoInfo[LogoHDInfoIndex].bShow = HI_FALSE;
        INIT_WORK(&(gs_stLogo.stGfxLogoInfo[LogoHDInfoIndex].freeLogoMemWork),  HIFB_FreeHDLogoMemWork);
        schedule_work(&(gs_stLogo.stGfxLogoInfo[LogoHDInfoIndex].freeLogoMemWork));
    }

    if (HI_TRUE == gs_stLogo.stGfxLogoInfo[LogoWBCInfoIndex].bShow)
    {
        /** should not set in work queue **/
        /** 不要在工作队里中赋值，否则工作队列还没有执行又调用INIT_WORK将工作队列至空导致队列空指针访问 **/
        gs_stLogo.stGfxLogoInfo[LogoWBCInfoIndex].bShow = HI_FALSE;
        INIT_WORK(&(gs_stLogo.stGfxLogoInfo[LogoWBCInfoIndex].freeLogoMemWork), HIFB_FreeWBCLogoMemWork);
        schedule_work(&(gs_stLogo.stGfxLogoInfo[LogoWBCInfoIndex].freeLogoMemWork));
    }

    return;
}

static inline HI_VOID HIFB_freeHDlogoMem(HIFB_LOGO_LAYER_E LogoLayerId)
{
    if (HI_NULL == gs_pstPdmExportFuncs)
    {
        return;
    }

#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
    if (NULL != gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem)
    {
        gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_HD);
    }
#endif

    return;
}

static inline HI_VOID HIFB_freeWBClogoMem(HIFB_LOGO_LAYER_E LogoLayerId)
{
    if (HI_NULL == gs_pstPdmExportFuncs)
    {
        return;
    }

    (HI_VOID)wait_event_interruptible_timeout(g_stGfxWbc2.WaiteWbcWorkqueueMutex,
                                              (1 == g_stGfxWbc2.u32BufIndex),
                                              CONFIG_HIFB_OPENWBC_WAITE_TIME);

#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
    if (NULL != gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem)
    {
       gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem(OPTM_GFX_WBC2_BUFFER);
       gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_SD);
    }
#endif

#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
    if (NULL != gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem)
    {
       gs_pstPdmExportFuncs->pfnPDM_ReleaseReserveMem(HIFB_ZME_COEF_BUFFER);
    }
#endif

    return;
}

static inline HI_VOID HIFB_FreeHDLogoMemWork(struct work_struct *work)
{
    HIFB_GFX_LOGO_INFO_S *pstGfxLogoInfo  = NULL;
    HI_U32 LogoInfoIndex  = 0;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *FbInfo = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(work);
    pstGfxLogoInfo = (HIFB_GFX_LOGO_INFO_S *)container_of(work, HIFB_GFX_LOGO_INFO_S, freeLogoMemWork);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstGfxLogoInfo);

    LogoInfoIndex  = HIFB_GetLogoInfoIndex(pstGfxLogoInfo->eLogoID);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(LogoInfoIndex, HIFB_LOGO_BUTT);

    HIFB_freeHDlogoMem(LogoInfoIndex);

    FbInfo = s_stLayer[HIFB_LAYER_HD_0].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(FbInfo);
    pstPar = (HIFB_PAR_S *)FbInfo->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);
    pstPar->FinishHdLogoWork = HI_TRUE;

    return;
}

static inline HI_VOID HIFB_FreeWBCLogoMemWork(struct work_struct *work)
{
    HIFB_GFX_LOGO_INFO_S *pstGfxLogoInfo  = NULL;
    HI_U32 LogoInfoIndex  = 0;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *FbInfo = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(work);
    pstGfxLogoInfo = (HIFB_GFX_LOGO_INFO_S *)container_of(work, HIFB_GFX_LOGO_INFO_S, freeLogoMemWork);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstGfxLogoInfo);

    LogoInfoIndex  = HIFB_GetLogoInfoIndex(pstGfxLogoInfo->eLogoID);
    HIFB_CHECK_ARRAY_OVER_UNRETURN(LogoInfoIndex, HIFB_LOGO_BUTT);

    HIFB_freeWBClogoMem(LogoInfoIndex);

    FbInfo = s_stLayer[HIFB_LAYER_HD_0].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(FbInfo);
    pstPar = (HIFB_PAR_S *)FbInfo->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);
    pstPar->FinishSdLogoWork = HI_TRUE;

    return;
}


/***************************************************************************************
* func          : DRV_HIFB_GetBaseData
* description   : CNcomment: get base data if has base partition CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID DRV_HIFB_GetBaseData(HI_U32 u32LayerId)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_PAR_S *par = NULL;
    struct fb_info *info = NULL;
    HIFB_RECT         stInRect  = {0};
    HIFB_COLOR_FMT_E  enHifbFmt = HIFB_FMT_BUTT;
    HI_DISP_PARAM_S   stDispParam;
    HI_U32 u32PixDepth = 0;
    HI_U32 CmpStride   = 0;
    HI_U32 LayerStride = 0;

    if (HIFB_LOGO_LAYER_HD0_ID != u32LayerId)
    {
       return ;
    }
#if 0
    if (HI_FALSE == gs_stLogo.stGfxLogoInfo[HIFB_LOGO_LAYER_HD0_ID].bShow)
    {
        return HI_SUCCESS;
    }
#endif
    info = s_stLayer[u32LayerId].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    HI_GFX_Memset(&stDispParam,0,sizeof(stDispParam));

    if ((NULL == gs_pstPdmExportFuncs) || (NULL == gs_pstPdmExportFuncs->pfnPDM_GetDispParam) )
    {
        //HIFB_WARNING("get pdm module function failed\n");
        return ;
    }

    Ret = gs_pstPdmExportFuncs->pfnPDM_GetDispParam(HI_UNF_DISPLAY1, &stDispParam);
    if (HI_FAILURE == Ret)
    {
        //HIFB_WARNING("PDM_GetDispParam failed\n");
        return ;
    }

    if ( (0 == stDispParam.u32VirtScreenWidth) || (0 == stDispParam.u32VirtScreenHeight))
    {
        //HIFB_ERROR("logo virtual screen error\n");
        return ;
    }

    enHifbFmt = DRV_HIFB_ConvertBootFmtToLayerFmt((HI_U32)stDispParam.enPixelFormat);
    if (enHifbFmt >= HIFB_FMT_PUYVY)
    {
        //HIFB_ERROR("unsupported fmt received from boot!\n");
        return ;
    }

    info->var.bits_per_pixel = DRV_HIFB_GetBppByFmt(enHifbFmt);
    if (0 == info->var.bits_per_pixel)
    {
        //HIFB_WARNING("unsupported fmt received from boot!\n");
        return ;
    }

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT | HIFB_PARA_CHECK_BITSPERPIXEL,
                                  stDispParam.u32VirtScreenWidth, stDispParam.u32VirtScreenHeight, 0, 0, info->var.bits_per_pixel);
    if (HI_SUCCESS != Ret)
    {
        //HIFB_WARNING("unsupported width and height from boot!\n");
        return ;
    }

    info->var.xres = stDispParam.u32VirtScreenWidth;
    info->var.yres = stDispParam.u32VirtScreenHeight;
    info->var.xres_virtual = info->var.xres;
    info->var.yres_virtual = info->var.yres * CONFIG_HIFB_LAYER_BUFFER_MAX_NUM;
    info->var.xoffset = 0;
    info->var.yoffset = 0;

    HIFB_CHECK_ARRAY_OVER_UNRETURN(enHifbFmt, HIFB_MAX_PIXFMT_NUM);
    info->var.red    = s_stArgbBitField[enHifbFmt].stRed;
    info->var.green  = s_stArgbBitField[enHifbFmt].stGreen;
    info->var.blue   = s_stArgbBitField[enHifbFmt].stBlue;
    info->var.transp = s_stArgbBitField[enHifbFmt].stTransp;

    info->fix.line_length  = CONIFG_HIFB_GetMaxStride(info->var.xres_virtual,info->var.bits_per_pixel,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);

    u32PixDepth = info->var.bits_per_pixel >> 3;
    LayerStride = (info->var.xres_virtual * u32PixDepth + CONFIG_HIFB_STRIDE_16ALIGN - 1) & (~(CONFIG_HIFB_STRIDE_16ALIGN - 1));

    par->stExtendInfo.enColFmt         = enHifbFmt;
    par->stExtendInfo.stPos.s32XPos    = 0;
    par->stExtendInfo.stPos.s32YPos    = 0;
    par->stExtendInfo.u32DisplayWidth  = info->var.xres;
    par->stExtendInfo.u32DisplayHeight = info->var.yres;

    stInRect.x = par->stExtendInfo.stPos.s32XPos;
    stInRect.y = par->stExtendInfo.stPos.s32YPos;
    stInRect.w = par->stExtendInfo.u32DisplayWidth;
    stInRect.h = par->stExtendInfo.u32DisplayHeight;

    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerInRect);
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerStride);
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerInRect(u32LayerId, &stInRect);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerStride(u32LayerId, LayerStride);
    gs_stLogoHifbAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(u32LayerId, par->stExtendInfo.enColFmt);

    return ;
}

static inline HIFB_COLOR_FMT_E DRV_HIFB_ConvertBootFmtToLayerFmt(HI_U32 BootFmt)
{
    if (HIFB_BOOT_FMT_1555 == BootFmt)
    {
         return HIFB_FMT_ARGB1555;
    }
    else if (HIFB_BOOT_FMT_8888 == BootFmt)
    {
         return HIFB_FMT_ARGB8888;
    }
    else
    {
         return HIFB_FMT_BUTT;
    }
}

#endif
