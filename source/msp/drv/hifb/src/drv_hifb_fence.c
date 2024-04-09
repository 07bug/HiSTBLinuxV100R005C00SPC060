/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name     : drv_hifb_fence.c
Version       : Initial Draft
Author        :
Created       : 2018/01/01
Description   :
Function List :


History       :
Date                       Author                 Modification
2018/01/01                 sdk                    Created file
**************************************************************************************************/


/*********************************add include here************************************************/
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

#include "drv_hifb_mem.h"

#ifdef CFG_HIFB_FENCE_SUPPORT
#include "drv_hifb_fence.h"
#include "drv_hifb_config.h"
#include "drv_hifb_paracheck.h"
/***************************** Macro Definition **************************************************/


/*************************** Structure Definition ************************************************/


/********************** Global Variable declaration **********************************************/
HIFB_SYNC_INFO_S gs_SyncInfo;
extern HIFB_DRV_OPS_S g_stDrvAdpCallBackFunction;

/******************************* API declaration *************************************************/
HI_S32 DRV_HIFB_FenceInit(HIFB_PAR_S *par)
{
    HI_S32 SyncIndex = 0;
    HI_CHAR SyncName[256] = {'\0'};

    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);
    if (HIFB_LAYER_HD_0 != par->stBaseInfo.u32LayerID)
    {
        return HI_SUCCESS;
    }

    for (SyncIndex = 0; SyncIndex < HIFB_DISP_TIMELINE_NUM_MAX; SyncIndex++)
    {
        gs_SyncInfo.TimeLine[SyncIndex]       = 0;
        gs_SyncInfo.FenceValue[SyncIndex]     = (1 == HIFB_DISP_TIMELINE_NUM_MAX)? (1) : (0);
        gs_SyncInfo.RegUpdateCnt[SyncIndex]   = 0;
        gs_SyncInfo.ReleaseFenceFd[SyncIndex] = -1;

        snprintf(SyncName, sizeof(SyncName), "hifb-sync-%d", SyncIndex);
        SyncName[sizeof(SyncName) - 1] = '\0';

        gs_SyncInfo.pstTimeline[SyncIndex] = hi_sw_sync_timeline_create(SyncName);
    }

    gs_SyncInfo.FrameEndFlag  = 0;

    spin_lock_init(&gs_SyncInfo.lock);
    init_waitqueue_head(&gs_SyncInfo.FrameEndEvent);

    par->FenceRefreshCount = 0;
    par->bEndFenceRefresh  = HI_FALSE;

    par->pFenceRefreshWorkqueue = create_singlethread_workqueue(HIFB_HWC_REFRESH_WORK_QUEUE);
    if (NULL == par->pFenceRefreshWorkqueue)
    {
        HIFB_ERROR("create hwc refresh work queue failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID DRV_HIFB_FenceDInit(HIFB_PAR_S *par)
{
    HI_S32 SyncIndex = 0;

    HIFB_CHECK_NULLPOINTER_UNRETURN(par);
    if (HIFB_LAYER_HD_0 != par->stBaseInfo.u32LayerID)
    {
        return;
    }

    for (SyncIndex = 0; SyncIndex < HIFB_DISP_TIMELINE_NUM_MAX; SyncIndex++)
    {
        if (NULL != gs_SyncInfo.pstTimeline[SyncIndex])
        {
            hi_sync_timeline_destroy((struct sync_timeline*)gs_SyncInfo.pstTimeline[SyncIndex]);
        }
        gs_SyncInfo.pstTimeline[SyncIndex] = NULL;
    }

    HIFB_CHECK_NULLPOINTER_UNRETURN(par->pFenceRefreshWorkqueue);
    destroy_workqueue(par->pFenceRefreshWorkqueue);

    par->pFenceRefreshWorkqueue = NULL;
    par->bEndFenceRefresh = HI_FALSE;

    return;
}

HI_VOID DRV_HIFB_GetRegUpdateCnt(HI_U32* pRegUpdateCnt, HI_U32 BufferIndex)
{
    if (BufferIndex >= HIFB_DISP_BUFFER_NUM_MAX)
    {
        return;
    }

    if (NULL != pRegUpdateCnt)
    {
       *pRegUpdateCnt = gs_SyncInfo.RegUpdateCnt[BufferIndex];
    }

    return;
}

HI_VOID DRV_HIFB_FENCE_FrameEndCallBack(HI_VOID *pParaml, HI_VOID *pParamr)
{
    HI_BOOL bHasOtherBufferUp = HI_FALSE;
    HI_U32 BufferIndex = 0;
    HI_U32 BufferId = 0;
    HI_U32 RegAddr = 0;
    HI_U32 *LayerId = NULL;
    HI_ULONG LockFlag = 0;
    HI_U32 NowTimeMs = 0;
    HI_U32 EndTimeMs = 0;
    HI_BOOL HasBeenClosedForEndCallBack = HI_FALSE;
    HI_ULONG ActualIntLineNumsEndCallBack  = 0;
    HI_ULONG HardIntCntForEndCallBack = 0;
    HI_GFX_TINIT();
    HI_UNUSED(pParamr);

    /*************************** check para ***********************************/
    HIFB_CHECK_NULLPOINTER_UNRETURN(pParaml);
    LayerId = (HI_U32*)pParaml;
    if (HIFB_LAYER_HD_0 != *LayerId)
    {
        return;
    }

    /*************************** count times **********************************/
    HI_GFX_TSTART(NowTimeMs);
    g_stDrvAdpCallBackFunction.HIFB_ADP_GetCloseState(*LayerId, NULL, &HasBeenClosedForEndCallBack);
    if (HI_TRUE == HasBeenClosedForEndCallBack)
    {
        gs_SyncInfo.PreTimeMs = 0;
        gs_SyncInfo.MaxTimeMs = 0;
    }

    if (0 == gs_SyncInfo.PreTimeMs)
    {
        gs_SyncInfo.PreTimeMs = NowTimeMs;
    }
    if ((NowTimeMs - gs_SyncInfo.PreTimeMs) > gs_SyncInfo.MaxTimeMs)
    {
        gs_SyncInfo.MaxTimeMs = NowTimeMs - gs_SyncInfo.PreTimeMs;
    }
    gs_SyncInfo.PreTimeMs = NowTimeMs;

    /*************************** count interupt information *******************/
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetDhd0Info(*LayerId,NULL,NULL,&ActualIntLineNumsEndCallBack,&HardIntCntForEndCallBack);
    gs_SyncInfo.ActualIntLineNumsForEndCallBack  = ActualIntLineNumsEndCallBack;
    gs_SyncInfo.HardIntCntForEndCallBack         = HardIntCntForEndCallBack;

    gs_SyncInfo.EndSoftCallBackCnt++;

    /*************************** release fence ********************************/
    g_stDrvAdpCallBackFunction.HIFB_DRV_GetLayerAddr(*LayerId, &RegAddr);
    if (0 == RegAddr)
    {
        return;
    }

    BufferId = DRV_HIFB_GetBufferId(*LayerId,RegAddr);
    if (1 == HIFB_DISP_TIMELINE_NUM_MAX)
    {
        bHasOtherBufferUp = HI_TRUE;
    }

    for (BufferIndex = 0; BufferIndex < HIFB_DISP_TIMELINE_NUM_MAX; BufferIndex++)
    {
        if (BufferId == BufferIndex)
        {
           continue;
        }

        if (gs_SyncInfo.RegUpdateCnt[BufferIndex] > 0)
        {
           bHasOtherBufferUp = HI_TRUE;
        }
    }

    if (HI_FALSE == bHasOtherBufferUp)
    {
        return;
    }

    spin_lock_irqsave(&gs_SyncInfo.lock,LockFlag);

      gs_SyncInfo.bFrameHit = HI_FALSE;
      if (NULL == gs_SyncInfo.pstTimeline[BufferId])
      {
         wake_up_interruptible(&gs_SyncInfo.FrameEndEvent);
         spin_unlock_irqrestore(&gs_SyncInfo.lock,LockFlag);
         return;
      }

      while (gs_SyncInfo.RegUpdateCnt[BufferId] > 0)
      {
          gs_SyncInfo.bFrameHit = HI_TRUE;
          gs_SyncInfo.RegUpdateCnt[BufferId]--;
          hi_sw_sync_timeline_inc(gs_SyncInfo.pstTimeline[BufferId], 1);
          gs_SyncInfo.TimeLine[BufferId]++;
      }

      gs_SyncInfo.FrameEndFlag = 1;

    wake_up_interruptible(&gs_SyncInfo.FrameEndEvent);
	spin_unlock_irqrestore(&gs_SyncInfo.lock,LockFlag);

    HI_GFX_TEND(EndTimeMs);
    if ((EndTimeMs - NowTimeMs) > gs_SyncInfo.RunMaxTimeMs)
    {
        gs_SyncInfo.RunMaxTimeMs = EndTimeMs - NowTimeMs;
    }

    return;
}

HI_S32 DRV_HIFB_FENCE_Create(HI_U32 BufferId)
{
    HI_S32 FenceFd   = -1;
    HI_U32 FenceValue = 0;
    struct hi_sync_fence *fence = NULL;
    struct sync_pt *pt = NULL;

    HIFB_CHECK_ARRAY_OVER_RETURN(BufferId, HIFB_DISP_TIMELINE_NUM_MAX, -EINVAL);
    HIFB_CHECK_NULLPOINTER_RETURN(gs_SyncInfo.pstTimeline[BufferId], -EINVAL);

    FenceFd = get_unused_fd_flags(0);
    if (FenceFd < 0)
    {
        HIFB_ERROR("get_unused_fd_flags failed!\n");
        return FenceFd;
    }

    gs_SyncInfo.ReleaseFenceFd[BufferId] = FenceFd;

    FenceValue = ++(gs_SyncInfo.FenceValue[BufferId]);

    pt = hi_sw_sync_pt_create(gs_SyncInfo.pstTimeline[BufferId], FenceValue);
    HIFB_CHECK_NULLPOINTER_RETURN(pt, HI_FAILURE);

    fence = hi_sync_fence_create(pt);
    if (NULL == fence)
    {
        hi_sync_pt_free(pt);
        return -ENOMEM;
    }

    hi_sync_fence_install(fence, FenceFd);

    return FenceFd;
}

HI_VOID DRV_HIFB_WaiteRefreshEnd(HI_BOOL ShouldWaite)
{
    if (HI_TRUE == ShouldWaite)
    {
      gs_SyncInfo.FrameEndFlag = 0;
      wait_event_interruptible_timeout(gs_SyncInfo.FrameEndEvent, gs_SyncInfo.FrameEndFlag, HZ);
    }

    return;
}

HI_VOID DRV_HIFB_IncRefreshTime(HI_BOOL bLayerEnable, HI_U32 BufferId)
{
    HI_BOOL bHasOtherBufferUp = HI_FALSE;
    HI_U32 BufferIndex = 0;
    HI_ULONG LockFlag;

    HIFB_CHECK_ARRAY_OVER_UNRETURN(BufferId, HIFB_DISP_TIMELINE_NUM_MAX);

    spin_lock_irqsave(&gs_SyncInfo.lock,LockFlag);
      gs_SyncInfo.RegUpdateCnt[BufferId]++;
    spin_unlock_irqrestore(&gs_SyncInfo.lock,LockFlag);

    if (HI_TRUE == bLayerEnable)
    {
        return;
    }

    if (1 == HIFB_DISP_TIMELINE_NUM_MAX)
    {
        bHasOtherBufferUp = HI_TRUE;
    }

    for (BufferIndex = 0; BufferIndex < HIFB_DISP_TIMELINE_NUM_MAX; BufferIndex++)
    {
        if (BufferId == BufferIndex)
        {
           continue;
        }
        if (gs_SyncInfo.RegUpdateCnt[BufferIndex] > 0)
        {
           bHasOtherBufferUp = HI_TRUE;
        }
    }

    if (HI_FALSE == bHasOtherBufferUp)
    {
        return;
    }

    if (1 == HIFB_DISP_TIMELINE_NUM_MAX)
    {
        BufferIndex = 0;
    }

    if (NULL == gs_SyncInfo.pstTimeline[BufferIndex])
    {
       return;
    }

    while (gs_SyncInfo.RegUpdateCnt[BufferIndex] > 0)
    {
        gs_SyncInfo.RegUpdateCnt[BufferIndex]--;
        hi_sw_sync_timeline_inc(gs_SyncInfo.pstTimeline[BufferIndex], 1);
        gs_SyncInfo.TimeLine[BufferIndex]++;
    }

    return;
}

HI_VOID DRV_HIFB_ReleaseFence(HI_U32 BufferId, HI_U8 *pFenceRefreshCount)
{
    HI_ULONG LockFlag;
    if (1 == HIFB_DISP_TIMELINE_NUM_MAX)
    {
        return;
    }
    HIFB_CHECK_ARRAY_OVER_UNRETURN(BufferId, HIFB_DISP_TIMELINE_NUM_MAX);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pFenceRefreshCount);
    HIFB_CHECK_NULLPOINTER_UNRETURN(gs_SyncInfo.pstTimeline[BufferId]);

    spin_lock_irqsave(&gs_SyncInfo.lock,LockFlag);
       (*pFenceRefreshCount)--;
       hi_sw_sync_timeline_inc(gs_SyncInfo.pstTimeline[BufferId], 1);
       gs_SyncInfo.TimeLine[BufferId]++;
    spin_unlock_irqrestore(&gs_SyncInfo.lock,LockFlag);

    return;
}

HI_BOOL DRV_HIFB_GetBufState(HI_U32 BufferId)
{
    HIFB_CHECK_ARRAY_OVER_RETURN(BufferId, HIFB_DISP_TIMELINE_NUM_MAX, HI_TRUE);

    if (gs_SyncInfo.TimeLine[BufferId] == gs_SyncInfo.FenceValue[BufferId])
    {
       return HI_FALSE;
    }

    return HI_TRUE;
}

HI_S32 DRV_HIFB_FENCE_Waite(struct hi_sync_fence *fence, long timeout)
{
    HI_S32 Err = 1;

    HIFB_CHECK_NULLPOINTER_RETURN(fence, HI_FAILURE);

    Err = hi_sync_fence_wait(fence, timeout);
    if (Err == -ETIME)
    {/**10 * MSEC_PER_SEC  in time.h **/
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#if 0
HI_BOOL DRV_HIFB_FENCE_IsRefresh(HI_VOID)
{
    return gs_SyncInfo.bFrameHit;
}
#endif
#endif
