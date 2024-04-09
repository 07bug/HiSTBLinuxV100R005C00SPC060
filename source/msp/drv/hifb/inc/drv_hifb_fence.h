/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : drv_hifb_fence.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                      Author                Modification
2018/01/01                sdk                   Created file
***************************************************************************************************/
#ifndef __DRV_HIFB_FENCE_H__
#define __DRV_HIFB_FENCE_H__

/*********************************add include here************************************************/
#include <sw_sync.h>

#include "drv_hifb_osr.h"

/*************************************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */


/***************************** Macro Definition **************************************************/
#define HIFB_SYNC_NAME                   "hifb_fence"

#define HIFB_DISP_BUFFER_NUM_MAX         3

#if defined(CFG_HIFB_FENCE_TIMELINE_NUM) && ((CFG_HIFB_FENCE_TIMELINE_NUM) >= 1) && ((CFG_HIFB_FENCE_TIMELINE_NUM) <= (HIFB_DISP_BUFFER_NUM_MAX))
    #define HIFB_DISP_TIMELINE_NUM_MAX   (CFG_HIFB_FENCE_TIMELINE_NUM)
#else
    #define HIFB_DISP_TIMELINE_NUM_MAX   1
#endif

/*************************** Structure Definition ************************************************/
typedef struct
{
    HI_BOOL  bFrameHit;
    HI_U8    RegUpdateCnt[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32   FenceValue[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32   TimeLine[HIFB_DISP_BUFFER_NUM_MAX];
    HI_S32   ReleaseFenceFd[HIFB_DISP_BUFFER_NUM_MAX];
    HI_U32   FrameEndFlag;
    HI_U32   PreTimeMs;                        /** 上一次进入FrameEnd中断的时间                    **/
    HI_U32   MaxTimeMs;                        /** 上一次进入FrameEnd中断和当前进入VO中断的时间差  **/
    HI_U32   RunMaxTimeMs;                     /** FrameEnd中断函数执行的最长时间                  **/
    HI_ULONG EndSoftCallBackCnt;               /** FrameEnd中断函数执行的次数                      **/
    HI_ULONG ActualIntLineNumsForEndCallBack;  /** FrameEnd实际上报的行数                          **/
    HI_ULONG HardIntCntForEndCallBack;         /** FrameEnd中断函数硬件的中断个数                  **/
    spinlock_t lock;
    wait_queue_head_t FrameEndEvent;
    struct sw_sync_timeline *pstTimeline[HIFB_DISP_BUFFER_NUM_MAX];
}HIFB_SYNC_INFO_S;

/********************** Global Variable declaration **********************************************/

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 9, 0)
#define hi_sync_fence                           sync_file
#define hi_sync_fence_create(sync_pt)           sync_file_create(&sync_pt->base)
#define hi_sync_fence_install(fence,fence_fd)   fd_install(fence_fd, fence->file)
#define hi_sync_fence_wait(fence,timeout)       fence_wait_timeout(fence->fence, true, timeout)
#define hi_sync_fence_fdget                     sync_file_fdget
#define hi_sync_fence_put(fence)                fput(fence->file)
#else
#define hi_sync_fence                           sync_fence
#define hi_sw_sync_timeline_create              sw_sync_timeline_create
#define hi_sync_fence_create(sync_pt)           sync_fence_create(HIFB_SYNC_NAME, sync_pt)
#define hi_sync_timeline_destroy                sync_timeline_destroy
#define hi_sync_fence_install(fence,fence_fd)   sync_fence_install(fence, fence_fd)
#define hi_sync_fence_wait(fence,timeout)       sync_fence_wait(fence, timeout)
#define hi_sw_sync_timeline_inc                 sw_sync_timeline_inc
#define hi_sw_sync_pt_create                    sw_sync_pt_create
#define hi_sync_pt_free                         sync_pt_free
#define hi_sync_fence_fdget                     sync_fence_fdget
#define hi_sync_fence_put(fence)                sync_fence_put(fence)
#endif

/******************************* API declaration *************************************************/

HI_S32  DRV_HIFB_FenceInit(HIFB_PAR_S *par);
HI_VOID DRV_HIFB_FenceDInit(HIFB_PAR_S *par);
HI_VOID DRV_HIFB_FENCE_FrameEndCallBack(HI_VOID *pParaml, HI_VOID *pParamr);
HI_S32  DRV_HIFB_FENCE_Create(HI_U32 BufferId);
HI_VOID DRV_HIFB_IncRefreshTime(HI_BOOL bLayerEnable, HI_U32 BufferId);
HI_VOID DRV_HIFB_ReleaseFence(HI_U32 BufferId, HI_U8 *pFenceRefreshCount);
HI_BOOL DRV_HIFB_GetBufState(HI_U32 BufferId);
HI_VOID DRV_HIFB_WaiteRefreshEnd(HI_BOOL ShouldWaite);
HI_S32  DRV_HIFB_FENCE_Waite(struct hi_sync_fence *fence, long timeout);
HI_VOID DRV_HIFB_GetRegUpdateCnt(HI_U32* pRegUpdateCnt, HI_U32 BufferIndex);

//HI_BOOL DRV_HIFB_FENCE_IsRefresh(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
