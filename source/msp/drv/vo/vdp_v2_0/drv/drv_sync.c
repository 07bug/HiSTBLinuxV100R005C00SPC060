#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>

#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>

#include "drv_sync.h"
#include "drv_disp_osal.h"
#include "hi_osal.h"

#define FENCE_DBG 0

#ifdef HI_VO_WIN_SYNC_SUPPORT
HI_S32 DRV_SYNC_Init(WIN_SYNC_INFO_S *pstSyncInfo,HI_U32 u32Index)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    HI_U32 u32Cnt = 0;
    HI_U8  u8DefaultName[12] = {0};
    HI_U8  u8TimelineName[12] = {0};

    if (HI_NULL == pstSyncInfo)
    {
        WIN_ERROR("Invalid pstSyncInfo\n");
        return HI_FAILURE;
    }

    pstSyncInfo->u32RefreshCnt = 0;

    pstSyncInfo->u32LastRefreshIdx = 0xffffffff;

    pstSyncInfo->u32FenceCnt = 0;

    pstSyncInfo->u32NextFenceValue = 1;

    pstSyncInfo->u32Timeline = 0;

    pstSyncInfo->pstTimeline = HI_NULL;

    HI_OSAL_Snprintf(u8TimelineName, 12, "vo%04x", u32Index);
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
    pstSyncInfo->pstTimeline = sw_sync_timeline_create(u8TimelineName);
#else
    pstSyncInfo->pstTimeline = hi_sw_sync_timeline_create(u8TimelineName);
#endif
    if (pstSyncInfo->pstTimeline == HI_NULL)
    {
        WIN_ERROR("Create Sync TimeLine Failed\n");
        return HI_FAILURE;
    }

    HI_OSAL_Snprintf(u8DefaultName, 12, "win%04x", u32Index);

    memcpy(pstSyncInfo->u8FenceName,u8DefaultName,sizeof(u8DefaultName));

    for(u32Cnt = 0; u32Cnt < DEF_FENCE_ARRAY_LENTH; u32Cnt ++)
    {
        pstSyncInfo->u32FenceArray[u32Cnt][0] = DEF_FENCE_INVALID_INDEX;
        pstSyncInfo->u32FenceArray[u32Cnt][1] = DEF_FENCE_INVALID_INDEX;
    }

    pstSyncInfo->u32ArrayHead = 0;
    pstSyncInfo->u32ArrayTail = 0;

#endif
    return HI_SUCCESS;
}

HI_S32 DRV_SYNC_DeInit(WIN_SYNC_INFO_S *pstSyncInfo)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT

    if (HI_NULL == pstSyncInfo)
    {
      WIN_ERROR("Invalid pstSyncInfo\n");
      return HI_FAILURE;
    }

    if (pstSyncInfo->pstTimeline != HI_NULL)
    {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
        sync_timeline_destroy((struct sync_timeline*)pstSyncInfo->pstTimeline);
#else
        hi_sync_timeline_destroy((struct sync_timeline*)pstSyncInfo->pstTimeline);
#endif    
        pstSyncInfo->pstTimeline = HI_NULL;
    }   
#endif

    return HI_SUCCESS;
}


HI_VOID  DRV_SYNC_AddData(WIN_SYNC_INFO_S *pstSyncInfo, HI_U32 u32NewIndex,HI_U32 u32NewAddr)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    struct sw_sync_timeline *timeline = HI_NULL;
    HI_U32 u32Head = 0;
    HI_U32 u32Tail = 0;
    HI_U32 u32PtValue = 0;

    if (HI_NULL == pstSyncInfo)
    {
        WIN_ERROR("Invalid pstSyncInfo\n");
        return ;
    }

    timeline = pstSyncInfo->pstTimeline;
    if (timeline == NULL) {
        return;
    }

    u32PtValue = pstSyncInfo->u32NextFenceValue;

    u32Head = pstSyncInfo->u32ArrayHead;
    u32Tail = pstSyncInfo->u32ArrayTail;

    if ((u32Tail+1)%DEF_FENCE_ARRAY_LENTH == u32Head)
    {
        WIN_ERROR("FenceArray is Full\n");
        return;
    }

    //add idx and pt_value into array
    pstSyncInfo->u32FenceArray[u32Tail][0] = u32NewIndex;
    pstSyncInfo->u32FenceArray[u32Tail][1] = pstSyncInfo->u32NextFenceValue;

#if FENCE_DBG
    WIN_ERROR("Create %d idx %d addr %#x\n",pstSyncInfo->u32NextFenceValue,u32NewIndex,u32NewAddr);
#endif

    //update related cnt
    pstSyncInfo->u32NextFenceValue++;
    pstSyncInfo->u32FenceCnt++;

    pstSyncInfo->u32ArrayTail = (u32Tail+1) % DEF_FENCE_ARRAY_LENTH;
#endif
    return ;
}
WIN_FENCE_FD DRV_SYNC_CreateFence(WIN_SYNC_INFO_S *pstSyncInfo, HI_U32 u32NewIndex,HI_U32 u32NewAddr)
{
    int fd = 0;
#ifdef HI_VO_WIN_SYNC_SUPPORT
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
    struct sync_fence *fence = HI_NULL;
#else
    struct sync_file *fence = HI_NULL; 
#endif	
    struct sync_pt *pt = HI_NULL;
    struct sw_sync_timeline *timeline = HI_NULL;
    HI_U32 u32Head = 0;
    HI_U32 u32Tail = 0;
    HI_U32 u32PtValue = 0;

    if (HI_NULL == pstSyncInfo)
    {
      WIN_ERROR("Invalid pstSyncInfo\n");
      return -EINVAL;
    }

    timeline = pstSyncInfo->pstTimeline;
    if (timeline == NULL) {
        return -EINVAL;
    }

    u32PtValue = pstSyncInfo->u32NextFenceValue;
    u32Head = pstSyncInfo->u32ArrayHead;
    u32Tail = pstSyncInfo->u32ArrayTail;

    if ((u32Tail+1)%DEF_FENCE_ARRAY_LENTH == u32Head)
    {
        WIN_ERROR("FenceArray is Full\n");
        return -EINVAL;
    }

    //create fence
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 19, 0)
    fd = get_unused_fd();
#else
    fd = get_unused_fd_flags(0);
#endif
    if (fd < 0) {
        WIN_ERROR("get_unused_fd_flags failed!\n");
        return fd;
    }
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
    pt = sw_sync_pt_create(timeline, u32PtValue);
#else
    pt = hi_sw_sync_pt_create(timeline, u32PtValue);
#endif
    if (pt == NULL) {
        return -ENOMEM;
    }
    
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
    fence = sync_fence_create(pstSyncInfo->u8FenceName, pt);
    if (fence == NULL) {
        sync_pt_free(pt);
        return -ENOMEM;
    }

    sync_fence_install(fence, fd);
#else
    fence = sync_file_create(&pt->base); 
    if (fence == NULL) {
        hi_sync_pt_free(pt);
        return -ENOMEM;
    }
    fd_install(fd, fence->file);
#endif
    //add idx and pt_value into array
    pstSyncInfo->u32FenceArray[u32Tail][0] = u32NewIndex;
    pstSyncInfo->u32FenceArray[u32Tail][1] = pstSyncInfo->u32NextFenceValue;

#if FENCE_DBG
    WIN_ERROR("Create %d idx %d addr %#x\n",pstSyncInfo->u32NextFenceValue,u32NewIndex,u32NewAddr);
#endif

    //update related cnt
    pstSyncInfo->u32NextFenceValue++;
    pstSyncInfo->u32FenceCnt++;

    pstSyncInfo->u32ArrayTail = (u32Tail+1) % DEF_FENCE_ARRAY_LENTH;
#endif
    return fd;
}


/*
SD : 1 1 2 2 3 3 4 4

HD :   1   2   3   4

when SD config the 2 twice,if release 1 ,the HD is still using it.

to solve this problem,calculate the repeat times.

when repeat 3 times ,release last frame.
*/
HI_U32 u32VoFenceRepeatCnt = 0;

HI_S32 DRV_SYNC_Signal(WIN_SYNC_INFO_S *pstSyncInfo,HI_U32 u32RefreshIndex,HI_U32 u32RefreshAddr)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    struct sw_sync_timeline *pstTimeline = HI_NULL;
    HI_U32 u32SearchHead = 0;
    HI_U32 u32SearchTail = 0;
    HI_U32 u32SearchCnt = 0;
    HI_U32 u32SignalLine = 0;

    if (HI_NULL == pstSyncInfo)
    {
      WIN_ERROR("Invalid pstSyncInfo\n");
      return -EINVAL;
    }

    pstTimeline = pstSyncInfo->pstTimeline;
    if (HI_NULL == pstTimeline)
    {
        WIN_ERROR("Invalid Time line\n");
        return -ENOMEM;
    }

    pstSyncInfo->u32RefreshCnt ++;

    u32SearchHead = pstSyncInfo->u32ArrayHead;
    u32SearchTail = pstSyncInfo->u32ArrayTail;
    u32SearchCnt = u32SearchHead;

#if FENCE_DBG
    WIN_ERROR("signal %d addr %#x \n", u32RefreshIndex, u32RefreshAddr);
#endif

    if (u32RefreshIndex != pstSyncInfo->u32LastRefreshIdx)
    {
        u32SignalLine = u32RefreshIndex - 1;

        u32VoFenceRepeatCnt = 0;
    }
    else
    {
        u32VoFenceRepeatCnt++;

        if (u32VoFenceRepeatCnt >= 3)
        {
            u32SignalLine = u32RefreshIndex;
        }
        else
        {
            u32SignalLine = u32RefreshIndex - 1;
        }
    }

    while(u32SearchHead != u32SearchTail
            &&
        pstSyncInfo->u32FenceArray[u32SearchCnt][0] < u32SignalLine
            &&
        pstSyncInfo->u32FenceArray[u32SearchCnt][0] != pstSyncInfo->u32LastRefreshIdx
        )
    {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
        sw_sync_timeline_inc(pstSyncInfo->pstTimeline, 1);
#else    
        hi_sw_sync_timeline_inc(pstSyncInfo->pstTimeline, 1);
#endif        

        pstSyncInfo->u32Timeline ++;

#if FENCE_DBG
        WIN_ERROR("time line %d\n",pstSyncInfo->u32Timeline);
#endif

        u32SearchHead = (u32SearchHead + 1)%DEF_FENCE_ARRAY_LENTH;
        u32SearchCnt = u32SearchHead;

        pstSyncInfo->u32ArrayHead = u32SearchHead;
    }

    pstSyncInfo->u32LastRefreshIdx = u32RefreshIndex;
#endif


    return HI_SUCCESS;
}


HI_S32 DRV_SYNC_Flush(WIN_SYNC_INFO_S *pstSyncInfo)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    struct sw_sync_timeline *pstTimeline = HI_NULL;
    HI_U32 u32SearchHead = 0;
    HI_U32 u32SearchTail = 0;
    HI_U32 u32SearchCnt  = 0;

    if (HI_NULL == pstSyncInfo)
    {
        WIN_ERROR("Invalid pstSyncInfo\n");
        return -EINVAL;
    }

    pstTimeline = pstSyncInfo->pstTimeline;
    if (HI_NULL == pstTimeline)
    {
        WIN_ERROR("Invalid Time line\n");
        return -ENOMEM;
    }

    pstSyncInfo->u32RefreshCnt ++;
    u32SearchHead = pstSyncInfo->u32ArrayHead;
    u32SearchTail = pstSyncInfo->u32ArrayTail;
    u32SearchCnt = u32SearchHead;

#if FENCE_DBG
    WIN_ERROR("head %d tail %d\n",u32SearchHead,u32SearchTail);
#endif

    if (u32SearchHead >= DEF_FENCE_ARRAY_LENTH || u32SearchTail >= DEF_FENCE_ARRAY_LENTH)
    {
        WIN_ERROR("u32SearchHead or u32SearchTail out of range\n");
        return -EINVAL;
    }

    while(u32SearchHead != u32SearchTail)
    {
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 9, 0)
        sw_sync_timeline_inc(pstSyncInfo->pstTimeline, 1);
#else
        hi_sw_sync_timeline_inc(pstSyncInfo->pstTimeline, 1);
#endif
        pstSyncInfo->u32Timeline ++;

#if FENCE_DBG
WIN_ERROR("time line %d\n",pstSyncInfo->u32Timeline);
#endif

        u32SearchHead = (u32SearchHead + 1)%DEF_FENCE_ARRAY_LENTH;
        u32SearchCnt = u32SearchHead;

        pstSyncInfo->u32ArrayHead = u32SearchHead;
    }
#endif

    return HI_SUCCESS;
}
#endif
