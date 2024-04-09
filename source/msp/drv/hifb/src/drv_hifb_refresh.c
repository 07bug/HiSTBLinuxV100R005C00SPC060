/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : drv_hifb_refresh.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                  Author                Modification
2018/01/01             sdk                 Created file
***************************************************************************************************/


/*********************************add include here*************************************************/
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/file.h>
#include <linux/fb.h>

#include "hifb.h"
#include "drv_hifb_osr.h"
#include "drv_hifb_config.h"
#include "drv_hifb_paracheck.h"

#ifdef CFG_HIFB_FENCE_SUPPORT
#include "drv_hifb_fence.h"
#endif
/***************************** Macro Definition ***************************************************/


/*************************** Structure Definition *************************************************/
#ifdef CFG_HIFB_FENCE_SUPPORT
typedef struct tagHifbRefreshWorkQueue_S
{
    HIFB_PAR_S *pstPar;
    HIFB_HWC_LAYERINFO_S stLayerInfo;
    struct hi_sync_fence *pSyncfence;
    struct work_struct FenceRefreshWork;
}HIFB_REFRESH_WORKQUEUE_S;
#endif


/********************** Global Variable declaration ***********************************************/


/******************************* API declaration **************************************************/
static HI_S32  HIFB_PanDisplayForStero(struct fb_var_screeninfo *var, struct fb_info *info);
static HI_VOID HIFB_PanDisplayForNoStero(struct fb_var_screeninfo *var, struct fb_info *info);
static HI_VOID HIFB_UpNonStereoADDR(struct fb_var_screeninfo *var, struct fb_info *info);
static HI_U32  HIFB_GetNonStereoADDR(struct fb_var_screeninfo *var, struct fb_info *info);

#ifdef CFG_HIFB_FENCE_SUPPORT
static HI_VOID DRV_HIFB_HwcRefreshWork(struct work_struct *work);
static HI_VOID HIFB_HwcRefresh(HIFB_REFRESH_WORKQUEUE_S *pstWork);
#endif


#ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
static HI_VOID DRV_HIFB_SetLowPowerInfo(HIFB_PAR_S* pstPar, HIFB_HWC_LAYERINFO_S *pstHwcLayerInfo);
#endif

/******************************* API realization **************************************************/

HI_S32 DRV_HIFB_PanDisplay(struct fb_var_screeninfo *var, struct fb_info *info)
{
    HI_ULONG StereoLockFlag = 0;
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(var, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

    HIFB_CHECK_UNEQUAL_RETURN(HIFB_REFRESH_MODE_WITH_PANDISPLAY, pstPar->stExtendInfo.enBufMode, HI_SUCCESS);

    DRV_HIFB_Lock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
    if (HI_TRUE == pstPar->st3DInfo.IsStereo)
    {
        pstPar->st3DInfo.BegUpStereoInfo = HI_TRUE;
        DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);
        HIFB_PanDisplayForStero(var,info);
        return HI_SUCCESS;
    }
    DRV_HIFB_UnLock(&pstPar->st3DInfo.StereoLock,&StereoLockFlag);

    HIFB_PanDisplayForNoStero(var,info);

    pstPar->hifb_sync = HI_FALSE;

    return HI_SUCCESS;
}

static HI_S32 HIFB_PanDisplayForStero(struct fb_var_screeninfo *var, struct fb_info *info)
{
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
     HI_S32 Ret = HI_SUCCESS;
     HIFB_PAR_S *pstPar = NULL;
     HIFB_BUFFER_S stInputDataBuf;
     HIFB_BLIT_OPT_S stBlitOpt;

     HIFB_CHECK_NULLPOINTER_RETURN(var, HI_FAILURE);
     HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);
     pstPar = (HIFB_PAR_S *)info->par;
     HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);

     if ((HIFB_STEREO_FRMPACKING == pstPar->st3DInfo.StereoMode) || (0 == pstPar->st3DInfo.st3DMemInfo.u32StereoMemStart))
     {
        HIFB_UpNonStereoADDR(var,info);
        return HI_SUCCESS;
     }

     HI_GFX_Memset(&stInputDataBuf, 0x0, sizeof(stInputDataBuf));
     stInputDataBuf.stCanvas.enFmt      = pstPar->stExtendInfo.enColFmt;
     stInputDataBuf.stCanvas.u32Pitch   = info->fix.line_length;
     stInputDataBuf.stCanvas.u32PhyAddr = HIFB_GetNonStereoADDR(var,info);
     stInputDataBuf.stCanvas.u32Width   = info->var.xres;
     stInputDataBuf.stCanvas.u32Height  = info->var.yres;

     stInputDataBuf.UpdateRect.x = 0;
     stInputDataBuf.UpdateRect.y = 0;
     stInputDataBuf.UpdateRect.w = stInputDataBuf.stCanvas.u32Width;
     stInputDataBuf.UpdateRect.h = stInputDataBuf.stCanvas.u32Height;

     pstPar->st3DInfo.st3DSurface.enFmt      = stInputDataBuf.stCanvas.enFmt;
     pstPar->st3DInfo.st3DSurface.u32Width   = stInputDataBuf.stCanvas.u32Width;
     pstPar->st3DInfo.st3DSurface.u32Height  = stInputDataBuf.stCanvas.u32Height;

     HIFB_CHECK_ARRAY_OVER_RETURN(pstPar->stRunInfo.u32IndexForInt, CONFIG_HIFB_LAYER_BUFFER_MAX_NUM, HI_FAILURE);
     pstPar->st3DInfo.st3DSurface.u32PhyAddr = pstPar->st3DInfo.u32DisplayAddr[pstPar->stRunInfo.u32IndexForInt];

     HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));
     stBlitOpt.bScale = HI_TRUE;
     stBlitOpt.bBlock = HI_TRUE;
     stBlitOpt.bRegionDeflicker = HI_TRUE;
     if (HIFB_ANTIFLICKER_TDE == pstPar->stBaseInfo.enAntiflickerMode)
     {
         stBlitOpt.enAntiflickerLevel = pstPar->stBaseInfo.enAntiflickerLevel;
     }

     stBlitOpt.pParam = &(pstPar->stBaseInfo.u32LayerID);
     stBlitOpt.bCallBack = HI_TRUE;
     stBlitOpt.pfnCallBack = (IntCallBack)DRV_HIFB_BlitFinishCallBack;

     Ret = DRV_HIFB_UpStereoData(pstPar->stBaseInfo.u32LayerID, &stInputDataBuf, &stBlitOpt);
     if (HI_SUCCESS != Ret)
     {
         HIFB_ERROR("pandisplay config stereo data failure!");
         return HI_FAILURE;
     }

    /** can relese stereo memory **/
    pstPar->st3DInfo.BegUpStereoInfo = HI_FALSE;
    wake_up_interruptible(&pstPar->st3DInfo.WaiteFinishUpStereoInfoMutex);
#endif

#ifndef CFG_HIFB_STEREO3D_HW_SUPPORT
     HI_UNUSED(info);
#endif

     return HI_SUCCESS;
}

static HI_VOID HIFB_PanDisplayForNoStero(struct fb_var_screeninfo *var, struct fb_info *info)
{
    HIFB_PAR_S *pstPar = NULL;
    HI_U32 CurDispAddr = 0;

    HIFB_CHECK_NULLPOINTER_UNRETURN(var);
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    HIFB_UpNonStereoADDR(var,info);

    if ((var->activate & FB_ACTIVATE_VBL) && (HI_TRUE == pstPar->bVblank))
    {
        DRV_HIFB_WaitVBlank(pstPar->stBaseInfo.u32LayerID);

        g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerAddr(pstPar->stBaseInfo.u32LayerID, &CurDispAddr);

        if (CurDispAddr != pstPar->stRunInfo.CurScreenAddr)
        {
            DRV_HIFB_WaitVBlank(pstPar->stBaseInfo.u32LayerID);
        }
    }

    return;
}

static HI_VOID HIFB_UpNonStereoADDR(struct fb_var_screeninfo *var, struct fb_info *info)
{
    HIFB_PAR_S *pstPar = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(info);
    pstPar = (HIFB_PAR_S *)info->par;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    pstPar->stRunInfo.bModifying = HI_TRUE;
    pstPar->stRunInfo.CurScreenAddr       = HIFB_GetNonStereoADDR(var,info);
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_STRIDE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_DISPLAYADDR;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.bModifying = HI_FALSE;

    return;
}

static HI_U32 HIFB_GetNonStereoADDR(struct fb_var_screeninfo *var, struct fb_info *info)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 u32Align = 0xf;
     HI_U32 PerPixDepth = 0;
     HI_U32 PixXOffset = 0;
     HI_U32 PixYOffset = 0;
     HI_U32 u32TmpSize = 0;
     HI_U32 StartDisplayAddr = 0;
     HIFB_PAR_S *pstPar = NULL;

     HIFB_CHECK_NULLPOINTER_RETURN(var, 0x0);
     HIFB_CHECK_NULLPOINTER_RETURN(info, 0x0);
     pstPar = (HIFB_PAR_S *)info->par;
     HIFB_CHECK_NULLPOINTER_RETURN(pstPar, 0x0);

     Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_WIDTH | HIFB_PARA_CHECK_HEIGHT | HIFB_PARA_CHECK_STRIDE | HIFB_PARA_CHECK_BITSPERPIXEL,
                                   var->xoffset, var->yoffset, info->fix.line_length, 0, var->bits_per_pixel);
     if (HI_SUCCESS != Ret)
     {
         HIFB_ERROR("var->xoffset = %d var->yoffset = %d info->fix.line_length = %d\n",var->xoffset,var->yoffset,info->fix.line_length);
         return info->fix.smem_start;
     }

     PerPixDepth = DRV_HIFB_GetPixDepth(var->bits_per_pixel);
     PixXOffset  = var->xoffset * PerPixDepth;
     PixYOffset  = info->fix.line_length * var->yoffset;

     if (0 != pstPar->stRunInfo.LastScreenAddr)
     {
         return pstPar->stRunInfo.LastScreenAddr;
     }

     u32TmpSize = PixYOffset + PixXOffset;
     HI_GFX_CHECK_U64_ADDITION_REVERSAL_RETURN(info->fix.smem_start,u32TmpSize, info->fix.smem_start);
     HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN((info->fix.smem_start + u32TmpSize), info->fix.smem_start);

     if ( (info->var.bits_per_pixel == 24) && ( (info->var.xoffset != 0) || (info->var.yoffset != 0) ) )
     {
        StartDisplayAddr = (info->fix.smem_start + u32TmpSize)/16/3;
        StartDisplayAddr = StartDisplayAddr * 16 * 3;
     }
     else
     {
        StartDisplayAddr = (info->fix.smem_start + u32TmpSize) & (~u32Align);
     }

     return StartDisplayAddr;
}

#ifdef CFG_HIFB_FENCE_SUPPORT
HI_S32 DRV_HIFB_FenceRefresh(HIFB_PAR_S* pstPar, HI_VOID *pArgs)
{
    HI_S32 s32FenceFd = -1;
    HI_U32 BufferId = 0;
    struct fb_info *FbInfo = NULL;
    HIFB_REFRESH_WORKQUEUE_S *pstWork = NULL;

    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, -EFAULT);
    HIFB_CHECK_NULLPOINTER_RETURN(pArgs, -EFAULT);

    FbInfo = s_stLayer[pstPar->stBaseInfo.u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(FbInfo, HI_FAILURE);

    HIFB_CHECK_NULLPOINTER_RETURN(current, -EFAULT);
    if (0 == pstPar->pid)
    {
       pstPar->pid = current->pid; /** pid name is current->comm **/
    }

    if (pstPar->pid != current->pid)
    {/**should support mult process, for example dfb **/
        //HIFB_ERROR("+++++++is not be used by hwcomposer\n");
        //return HI_FAILURE;
    }

    pstWork = (HIFB_REFRESH_WORKQUEUE_S*)HI_GFX_KMALLOC(HIGFX_FB_ID,sizeof(HIFB_REFRESH_WORKQUEUE_S), GFP_KERNEL);
    HIFB_CHECK_NULLPOINTER_RETURN(pstWork, -EFAULT);

    if (copy_from_user(&(pstWork->stLayerInfo), pArgs, sizeof(HIFB_HWC_LAYERINFO_S)))
    {
       HIFB_ERROR("+++++++copy_from_user failure\n");
       HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
       return -EFAULT;
    }


    if (   (pstWork->stLayerInfo.u32LayerAddr != FbInfo->fix.smem_start)
        && (pstWork->stLayerInfo.u32LayerAddr != FbInfo->fix.smem_start + FbInfo->fix.line_length * pstPar->stExtendInfo.u32DisplayHeight)
        && (pstWork->stLayerInfo.u32LayerAddr != FbInfo->fix.smem_start + FbInfo->fix.line_length * pstPar->stExtendInfo.u32DisplayHeight * 2))
    {
        HIFB_ERROR("+++++++0x%x != 0x%x 0x%x 0x%x\n",pstWork->stLayerInfo.u32LayerAddr,FbInfo->fix.smem_start,
                                                     FbInfo->fix.smem_start + (FbInfo->fix.line_length * pstPar->stExtendInfo.u32DisplayHeight),
                                                     FbInfo->fix.smem_start + (FbInfo->fix.line_length * pstPar->stExtendInfo.u32DisplayHeight * 2));
        HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
        return -EFAULT;
    }

#ifdef CONFIG_GFX_PROC_SUPPORT
    pstPar->stProcInfo.b3DStatus = pstPar->st3DInfo.IsStereo;
    pstPar->stProcInfo.bHwcRefreshInDeCmpStatus = pstWork->stLayerInfo.bDeCompress;
    pstPar->stProcInfo.HwcRefreshInDispFmt      = (HI_U32)pstWork->stLayerInfo.eFmt;
    pstPar->stProcInfo.HwcRefreshInDispStride   = pstWork->stLayerInfo.u32Stride;
    pstPar->stProcInfo.HwcRefreshInDispAdress   = pstWork->stLayerInfo.u32LayerAddr;
#endif

    /*************************** check whether has repeat frame ***************/
    if (pstWork->stLayerInfo.u32LayerAddr == pstPar->stRunInfo.PreRefreshAddr)
    {
        pstPar->stFrameInfo.RepeatFrameCnt++;
    }
    pstPar->stRunInfo.PreRefreshAddr = pstWork->stLayerInfo.u32LayerAddr;

    /*************************** refresh  *************************************/
    BufferId = DRV_HIFB_GetBufferId(pstPar->stBaseInfo.u32LayerID, pstWork->stLayerInfo.u32LayerAddr);
    s32FenceFd = DRV_HIFB_FENCE_Create(BufferId);
    if (s32FenceFd < 0)
    {
        HIFB_ERROR("DRV_HIFB_FENCE_Create failed\n");
        HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
        return -EFAULT;
    }

    pstWork->pstPar = pstPar;
    pstWork->stLayerInfo.s32ReleaseFenceFd = s32FenceFd;

    /**<-- save draw fence -->**/
    if (pstWork->stLayerInfo.s32AcquireFenceFd >= 0)
    {/** if not use gpu composer, no need wait, because hwcomposer sync **/
        pstWork->pSyncfence = hi_sync_fence_fdget(pstWork->stLayerInfo.s32AcquireFenceFd);
    }
    else
    {
        pstWork->pSyncfence = NULL;
    }

    if (NULL == pstPar->pFenceRefreshWorkqueue)
    {
        HIFB_ERROR("+++++++pFenceRefreshWorkqueue is null\n");
        put_unused_fd(pstWork->stLayerInfo.s32ReleaseFenceFd);
        HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
        return -EFAULT;
    }

    pstWork->stLayerInfo.bStereo = pstPar->st3DInfo.IsStereo;
    if (copy_to_user(pArgs,&(pstWork->stLayerInfo),sizeof(HIFB_HWC_LAYERINFO_S)))
    {
        HIFB_ERROR("+++++++copy_to_user failure\n");
        put_unused_fd(pstWork->stLayerInfo.s32ReleaseFenceFd);
        HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
        return -EFAULT;
    }

    pstPar->bEndFenceRefresh = HI_FALSE;
    INIT_WORK(&(pstWork->FenceRefreshWork), DRV_HIFB_HwcRefreshWork);
    queue_work(pstPar->pFenceRefreshWorkqueue, &(pstWork->FenceRefreshWork));

#if 0
    Ret = wait_event_interruptible_timeout(pstPar->WaiteEndFenceRefresh, HI_TRUE == pstPar->bEndFenceRefresh,50 * HZ/1000);
    if (Ret <= 0)
    {
        HIFB_INFO("+++++++warnint:refresh time out\n");
    }
#endif

    pstPar->bEndFenceRefresh = HI_FALSE;

    return HI_SUCCESS;
}

static HI_VOID DRV_HIFB_HwcRefreshWork(struct work_struct *work)
{
    HI_U32 BufferId = 0;
    HIFB_PAR_S *pstPar  = NULL;
    HI_BOOL NoDiscardFrame = HI_FALSE;
    HIFB_REFRESH_WORKQUEUE_S *pstWork = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(work);
    pstWork = (HIFB_REFRESH_WORKQUEUE_S*)container_of(work, HIFB_REFRESH_WORKQUEUE_S, FenceRefreshWork);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstWork);

    /**<-- waite draw fence -->**/
    if (NULL != pstWork->pSyncfence)
    {
        DRV_HIFB_FENCE_Waite(pstWork->pSyncfence, 4000);
        hi_sync_fence_put(pstWork->pSyncfence);
        pstWork->pSyncfence = NULL;
    }

    pstPar = pstWork->pstPar;
    if (NULL == pstPar)
    {
         HIFB_ERROR("+++++++pstPar is null\n");
         HI_GFX_KFREE(HIGFX_FB_ID,pstWork);
         return;
    }

    if (pstPar->FenceRefreshCount > 0)
    {
       BufferId = DRV_HIFB_GetBufferId(pstPar->stBaseInfo.u32LayerID,pstPar->stRunInfo.CurScreenAddr);

       g_stDrvAdpCallBackFunction.HIFB_DRV_WhetherDiscardFrame(pstPar->stBaseInfo.u32LayerID, &NoDiscardFrame);
       NoDiscardFrame = (HI_FALSE == pstWork->stLayerInfo.bDiscardFrame) ? NoDiscardFrame : HI_FALSE;

       DRV_HIFB_WaiteRefreshEnd(NoDiscardFrame);

       if (HI_FALSE == NoDiscardFrame)
       {/**<--¶ªÆúÉÏÒ»Ö¡-->**/
          DRV_HIFB_ReleaseFence(BufferId,&(pstPar->FenceRefreshCount));
          pstPar->DiscardFrame = HI_TRUE;
       }
    }

    HIFB_HwcRefresh(pstWork);

    pstPar->stFrameInfo.RefreshFrame++;
    pstPar->hifb_sync = HI_TRUE;

    HI_GFX_KFREE(HIGFX_FB_ID,pstWork);

    pstPar->bEndFenceRefresh = HI_TRUE;
    wake_up_interruptible(&pstPar->WaiteEndFenceRefresh);

    return;
}

static HI_VOID HIFB_HwcRefresh(HIFB_REFRESH_WORKQUEUE_S *pstWork)
{
    HI_U32 BufferId = 0;
    HI_BOOL bDispEnable = HI_FALSE;
    HI_ULONG LockParFlag = 0;
    HI_BOOL bShouldClosePreMult = HI_FALSE;
    HIFB_PAR_S *pstPar = NULL;
    struct fb_info *info = NULL;

    HIFB_CHECK_NULLPOINTER_UNRETURN(pstWork);
    pstPar  = pstWork->pstPar;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(pstPar->stBaseInfo.u32LayerID);
    info = s_stLayer[pstPar->stBaseInfo.u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    if ((HI_TRUE == pstWork->stLayerInfo.bDeCompress) && (HI_TRUE == pstPar->st3DInfo.IsStereo))
    {
        HIFB_WARNING("3d and decompress state is wrong\n");
        return;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetClosePreMultState(pstPar->stBaseInfo.u32LayerID, &bShouldClosePreMult);
    if (HI_TRUE == bShouldClosePreMult)
    {
        pstPar->stBaseInfo.bPreMul = HI_FALSE;
    }
    else
    {
        pstPar->stBaseInfo.bPreMul = pstWork->stLayerInfo.bPreMul;
    }

    pstPar->stRunInfo.LastScreenAddr = pstWork->stLayerInfo.u32LayerAddr;
    pstPar->stExtendInfo.enColFmt    = pstWork->stLayerInfo.eFmt;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(pstPar->stBaseInfo.u32LayerID, pstWork->stLayerInfo.eFmt);

    if (HI_TRUE == pstPar->st3DInfo.IsStereo)
    {
        pstPar->bDeCompress = HI_FALSE;
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetDeCmpSwitch(pstPar->stBaseInfo.u32LayerID, HI_FALSE);

        HIFB_CHECK_EQUAL_UNRETURN(0, pstWork->stLayerInfo.u32Stride);
        HIFB_CHECK_LEFT_LARGER_RIGHT_UNRETURN(info->fix.smem_start, pstWork->stLayerInfo.u32LayerAddr);
        info->var.yoffset = (pstWork->stLayerInfo.u32LayerAddr - info->fix.smem_start)/pstWork->stLayerInfo.u32Stride;

        DRV_HIFB_PanDisplay(&info->var, info);

        g_stDrvAdpCallBackFunction.HIFB_DRV_GetHaltDispStatus(pstPar->stBaseInfo.u32LayerID, &bDispEnable);

        BufferId = DRV_HIFB_GetBufferId(pstPar->stBaseInfo.u32LayerID,pstWork->stLayerInfo.u32LayerAddr);

        DRV_HIFB_IncRefreshTime(bDispEnable, BufferId);

        return;
    }

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&LockParFlag);
    pstPar->stRunInfo.bModifying          = HI_TRUE;
    #ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
    DRV_HIFB_SetLowPowerInfo(pstPar,&(pstWork->stLayerInfo));
    #endif
    pstPar->bDeCompress                   = pstWork->stLayerInfo.bDeCompress;
    pstPar->stRunInfo.CurScreenAddr       = pstWork->stLayerInfo.u32LayerAddr;
    pstPar->stExtendInfo.stPos.s32XPos    = pstWork->stLayerInfo.stInRect.x;
    pstPar->stExtendInfo.stPos.s32YPos    = pstWork->stLayerInfo.stInRect.y;
    pstPar->stExtendInfo.u32DisplayWidth  = pstWork->stLayerInfo.stInRect.w;
    pstPar->stExtendInfo.u32DisplayHeight = pstWork->stLayerInfo.stInRect.h;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FENCE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_BMUL;
    pstPar->stRunInfo.bModifying          = HI_FALSE;
    pstPar->FenceRefreshCount++;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockParFlag);

    return;
}

#else
HI_S32 DRV_HIFB_NoFenceRefresh(HIFB_PAR_S* pstPar, HI_VOID *pArgs)
{
    HI_BOOL bShouldClosePreMult = HI_FALSE;
    HI_ULONG LockParFlag = 0;
    struct fb_info *info = NULL;
    HIFB_HWC_LAYERINFO_S stHwcLayerInfo;

    HIFB_CHECK_NULLPOINTER_RETURN(pstPar, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pArgs, HI_FAILURE);

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(pstPar->stBaseInfo.u32LayerID,-EFAULT);
    info = s_stLayer[pstPar->stBaseInfo.u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    HI_GFX_Memset(&stHwcLayerInfo, 0x0, sizeof(stHwcLayerInfo));

    if (copy_from_user(&stHwcLayerInfo, pArgs, sizeof(HIFB_HWC_LAYERINFO_S)))
    {
       HIFB_ERROR("copy no fence hwc layerinfo from user failure\n");
       return HI_FAILURE;
    }

#ifdef CONFIG_GFX_PROC_SUPPORT
    pstPar->stProcInfo.b3DStatus = pstPar->st3DInfo.IsStereo;
    pstPar->stProcInfo.bHwcRefreshInDeCmpStatus = stHwcLayerInfo.bDeCompress;
    pstPar->stProcInfo.HwcRefreshInDispFmt      = (HI_U32)stHwcLayerInfo.eFmt;
    pstPar->stProcInfo.HwcRefreshInDispStride   = stHwcLayerInfo.u32Stride;
    pstPar->stProcInfo.HwcRefreshInDispAdress   = stHwcLayerInfo.u32LayerAddr;
#endif

    /*************************** check whether has repeat frame ***************/
    if (stHwcLayerInfo.u32LayerAddr == pstPar->stRunInfo.PreRefreshAddr)
    {
        pstPar->stFrameInfo.RepeatFrameCnt++;
    }
    pstPar->stRunInfo.PreRefreshAddr = stHwcLayerInfo.u32LayerAddr;

    /*************************** refresh  *************************************/
    stHwcLayerInfo.bStereo = pstPar->st3DInfo.IsStereo;
    if (copy_to_user(pArgs,&stHwcLayerInfo,sizeof(HIFB_HWC_LAYERINFO_S)))
    {
        HIFB_ERROR("copy layerinfo to user failure\n");
        return HI_FAILURE;
    }

    if ((HI_TRUE == stHwcLayerInfo.bDeCompress) && (HI_TRUE == pstPar->st3DInfo.IsStereo))
    {
        HIFB_WARNING("3d and decompress state is wrong\n");
        return HI_FAILURE;
    }

    g_stDrvAdpCallBackFunction.HIFB_DRV_GetClosePreMultState(pstPar->stBaseInfo.u32LayerID, &bShouldClosePreMult);
    if (HI_TRUE == bShouldClosePreMult)
    {
        pstPar->stBaseInfo.bPreMul = HI_FALSE;
    }
    else
    {
        pstPar->stBaseInfo.bPreMul = stHwcLayerInfo.bPreMul;
    }

    pstPar->stRunInfo.LastScreenAddr = stHwcLayerInfo.u32LayerAddr;
    pstPar->stExtendInfo.enColFmt = stHwcLayerInfo.eFmt;

    g_stDrvAdpCallBackFunction.HIFB_DRV_SetLayerDataFmt(pstPar->stBaseInfo.u32LayerID, stHwcLayerInfo.eFmt);

    if (HI_TRUE == pstPar->st3DInfo.IsStereo)
    {
        pstPar->bDeCompress = HI_FALSE;
        g_stDrvAdpCallBackFunction.HIFB_DRV_SetDeCmpSwitch(pstPar->stBaseInfo.u32LayerID, HI_FALSE);

        HIFB_CHECK_EQUAL_RETURN(0, stHwcLayerInfo.u32Stride, -EFAULT);
        HIFB_CHECK_LEFT_LARGER_RIGHT_RETURN(info->fix.smem_start, stHwcLayerInfo.u32LayerAddr,HI_FAILURE);
        info->var.yoffset = (stHwcLayerInfo.u32LayerAddr - info->fix.smem_start) / stHwcLayerInfo.u32Stride;

        DRV_HIFB_PanDisplay(&info->var, info);

        return HI_SUCCESS;
    }

    DRV_HIFB_Lock(&pstPar->stBaseInfo.lock,&LockParFlag);
    pstPar->stRunInfo.bModifying          = HI_TRUE;
    #ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
    DRV_HIFB_SetLowPowerInfo(pstPar,&stHwcLayerInfo);
    #endif
    pstPar->bDeCompress                   = stHwcLayerInfo.bDeCompress;
    pstPar->stRunInfo.CurScreenAddr       = stHwcLayerInfo.u32LayerAddr;
    pstPar->stExtendInfo.stPos.s32XPos    = stHwcLayerInfo.stInRect.x;
    pstPar->stExtendInfo.stPos.s32YPos    = stHwcLayerInfo.stInRect.y;
    pstPar->stExtendInfo.u32DisplayWidth  = stHwcLayerInfo.stInRect.w;
    pstPar->stExtendInfo.u32DisplayHeight = stHwcLayerInfo.stInRect.h;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_INRECT;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_REFRESH;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_FENCE;
    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_BMUL;
    pstPar->stRunInfo.bModifying          = HI_FALSE;
    DRV_HIFB_UnLock(&pstPar->stBaseInfo.lock,&LockParFlag);

    pstPar->stFrameInfo.RefreshFrame++;
    pstPar->hifb_sync = HI_TRUE;

    return HI_SUCCESS;
}
#endif


#ifdef CONFIG_HIFB_LOWPOWER_SUPPORT
static HI_VOID DRV_HIFB_SetLowPowerInfo(HIFB_PAR_S* pstPar, HIFB_HWC_LAYERINFO_S *pstHwcLayerInfo)
{
    HI_S32 Index = 0;
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstPar);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstHwcLayerInfo);

    pstPar->stLowPowerInfo.LowPowerEn = pstHwcLayerInfo->stLowPowerInfo.LowPowerEn;

    for (Index = 0; Index < CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT; Index++)
    {
       pstPar->stLowPowerInfo.LpInfo[Index] = pstHwcLayerInfo->stLowPowerInfo.LpInfo[Index];
    }

    pstPar->stRunInfo.u32ParamModifyMask |= HIFB_LAYER_PARAMODIFY_LOWPOWER;

    return;
}
#endif
