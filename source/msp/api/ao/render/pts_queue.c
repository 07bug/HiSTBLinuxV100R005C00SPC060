/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pts_queue.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/06/28
  Description  :
  History       :
  1.Date        : 2016/06/28
    Author      :
    Modification: Created file

*******************************************************************************/
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pts_queue.h"
#include "ao_isb.h"
#include "hi_drv_ao.h"
#include "hi_error_mpi.h"
#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define PTS_MASK  (MAX_STORED_PTS_NUM - 1)
#define STREAM_WRAP_PTS_THRESHOLD   (5000)


static PTS_SEEK_E PTSQUEUEDropSeek(PTS_QUEUE_S* pstPtsQueue, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32Idx;
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    HI_U32 u32ReadCnt = 0;
    HI_U32 u32TotalSize;
    PTS_ATTR_S* pstPtsAttr = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx;
    u32WIdx = pstPtsQueue->u32WIdx;
    PTS_PRINTF("RIdx:%d,WIdx:%d,TargetPts:%d\n", u32RIdx, u32WIdx, u32TargetPts);

    u32TotalSize = u32WIdx >= u32RIdx ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx + 1);
    if (0 == u32TotalSize)
    {
        return PTS_SEEK_NONE;
    }

    for (u32Idx = (u32RIdx & PTS_MASK); u32Idx != (u32WIdx & PTS_MASK); u32Idx = ((u32Idx + 1) & PTS_MASK))
    {
        if (pstPtsAttr[u32Idx].u32PtsMs >= u32TargetPts)
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32PtsMs;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BegPos;
            pstPtsQueue->u32RIdx += u32ReadCnt;

            return PTS_SEEK_PACKAGE;
        }

        u32ReadCnt++;
    }

    PTS_PRINTF("u32Idx:%d,u32ReadCnt:%d,Pts:%d,Pos:%d\n", u32Idx, u32ReadCnt, pstPtsAttr[u32Idx - 1].u32PtsMs, pstPtsAttr[u32Idx - 1].u32BegPos);

    *pu32NearbyPts = pstPtsAttr[u32Idx - 1].u32PtsMs;
    *pu32NearbyPos = pstPtsAttr[u32Idx - 1].u32BegPos;
    pstPtsQueue->u32RIdx += u32ReadCnt;

    return PTS_SEEK_PACKAGE;
}

HI_S32 PTSQUEUE_Create(HI_VOID* hISB, HI_VOID** pHandle)
{
    CHECK_AO_NULL_PTR(hISB);
    CHECK_AO_NULL_PTR(pHandle);

    return AO_ISB_GetPtsQue(hISB, pHandle);
}

HI_S32 PTSQUEUE_Detroy(HI_VOID* handle)
{
    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Put(SOURCE_ID_E enSourceID, HI_VOID* handle, HI_U32 u32PtsMs, HI_U32 u32DataSize)
{
    HI_U32 u32PreWIdx = 0;
    HI_U32 u32CurWIdx = 0;
    PTS_ATTR_S* pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr  = pstPtsQueue->astPtsAttr;

    if (HI_INVALID_PTS == u32PtsMs || pstPtsAttr[u32CurWIdx].u32PtsMs == u32PtsMs)
    {
        u32CurWIdx = pstPtsQueue->u32WIdx & PTS_MASK;
        pstPtsAttr[u32CurWIdx].u32EndPos += u32DataSize;
    }
    else
    {
        if (HI_FALSE == pstPtsQueue->bInited)
        {
            u32CurWIdx = pstPtsQueue->u32WIdx & PTS_MASK;
            pstPtsAttr[u32CurWIdx].u32BegPos = 0;
        }
        else
        {
            u32PreWIdx = pstPtsQueue->u32WIdx & PTS_MASK;
            pstPtsQueue->u32WIdx = (pstPtsQueue->u32WIdx + 1) & PTS_MASK;
            u32CurWIdx = pstPtsQueue->u32WIdx & PTS_MASK;

            pstPtsAttr[u32CurWIdx].u32BegPos = pstPtsAttr[u32PreWIdx].u32EndPos;
            pstPtsAttr[u32PreWIdx].bInjecting  = HI_FALSE;
        }

        pstPtsAttr[u32CurWIdx].u32PtsMs = u32PtsMs;
        pstPtsAttr[u32CurWIdx].u32OrgPts = u32PtsMs;
        pstPtsAttr[u32CurWIdx].u32EndPos = pstPtsAttr[u32CurWIdx].u32BegPos + u32DataSize;
    }

    PTS_PRINTF("Source(%d) Put NewPts:%d Size:%d -> Queue[%d].Pts:%d BegPos:%d EndPos:%d RIdx:%d WIdx:%d\n", enSourceID, u32PtsMs, u32DataSize, u32CurWIdx,
               pstPtsAttr[u32CurWIdx].u32PtsMs, pstPtsAttr[u32CurWIdx].u32BegPos, pstPtsAttr[u32CurWIdx].u32EndPos, pstPtsQueue->u32RIdx, pstPtsQueue->u32WIdx);

    if (HI_FALSE == pstPtsQueue->bInited)
    {
        pstPtsQueue->bInited = HI_TRUE;
    }

    pstPtsAttr[u32CurWIdx].bInjecting = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Find(HI_VOID* handle, HI_U32 u32Pos, HI_U32* pu32Pts)
{
    HI_U32 u32Idx;
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    HI_U32 u32QueueSize = 0;
    PTS_ATTR_S*  pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr  = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx;
    u32WIdx = pstPtsQueue->u32WIdx;

    PTS_PRINTF("FindPts RIdx:%d WIdx:%d FindPos:%d\n", u32RIdx, u32WIdx, u32Pos);

    if (u32RIdx == u32WIdx)
    {
        u32QueueSize = (HI_TRUE == pstPtsAttr[u32WIdx].bInjecting) ? 1 : 0; //only one package
    }
    else
    {
        u32QueueSize = (u32WIdx > u32RIdx) ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx);
    }

    for (u32Idx = 0; u32Idx < u32QueueSize; u32Idx++)
    {
        u32RIdx = (pstPtsQueue->u32RIdx + u32Idx) & PTS_MASK;

        PTS_PRINTF("FindPts RIdx:%d BegPos:%d EndPos:%d\n", u32RIdx, pstPtsAttr[u32RIdx].u32BegPos, pstPtsAttr[u32RIdx].u32EndPos);

        if (pstPtsAttr[u32RIdx].u32BegPos < pstPtsAttr[u32RIdx].u32EndPos)
        {
            if ((pstPtsAttr[u32RIdx].u32BegPos <= u32Pos) && (pstPtsAttr[u32RIdx].u32EndPos > u32Pos))
            {
                *pu32Pts = pstPtsAttr[u32RIdx].u32PtsMs;

                PTS_PRINTF("FindPts Pos:%d Pts:%d BegPos:%d EndPos:%d\n",
                           u32Pos, pstPtsAttr[u32RIdx].u32PtsMs,
                           pstPtsAttr[u32RIdx].u32BegPos, pstPtsAttr[u32RIdx].u32EndPos);
                break;
            }
        }
        else
        {
            if ((pstPtsAttr[u32RIdx].u32BegPos <= u32Pos) || (pstPtsAttr[u32RIdx].u32EndPos > u32Pos))
            {
                *pu32Pts = pstPtsAttr[u32RIdx].u32PtsMs;

                PTS_PRINTF("FindPts Pos:%d Pts:%d BegPos:%d EndPos:%d\n",
                           u32Pos, pstPtsAttr[u32RIdx].u32PtsMs,
                           pstPtsAttr[u32RIdx].u32BegPos, pstPtsAttr[u32RIdx].u32EndPos);
                break;
            }
        }
    }

    pstPtsQueue->u32RIdx = u32RIdx;

    return HI_SUCCESS;
}

HI_S32 PTSQUEUE_Update(HI_VOID* handle, HI_U32 u32Delta)
{
    HI_U32 u32RIdx;
    PTS_ATTR_S*  pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue  = (PTS_QUEUE_S*)handle;
    pstPtsAttr   = pstPtsQueue->astPtsAttr;
    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;

    if (HI_INVALID_PTS != pstPtsAttr[u32RIdx].u32PtsMs)
    {
        pstPtsAttr[u32RIdx].u32PtsMs += u32Delta;
    }

    return HI_SUCCESS;
}

HI_U32 PTSQUEUE_GetReadPts(HI_VOID* handle)
{
    HI_U32 u32RIdx;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    if (HI_NULL == handle)
    {
        return HI_INVALID_PTS;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;
    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;

    return pstPtsAttr[u32RIdx].u32PtsMs;
}

HI_BOOL PTSQUEUE_CheckIsFull(HI_VOID* handle)
{
    HI_U32 u32PtsCnt = 0;
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    PTS_ATTR_S*  pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    if (HI_NULL == handle)
    {
        return HI_TRUE;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr  = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;
    u32WIdx = pstPtsQueue->u32WIdx & PTS_MASK;

    if (u32RIdx == u32WIdx)
    {
        u32PtsCnt = (HI_TRUE == pstPtsAttr[u32WIdx].bInjecting) ? 1 : 0;
    }
    else
    {
        u32PtsCnt = (u32WIdx > u32RIdx) ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx);
    }

    return (((MAX_STORED_PTS_NUM - 1) == u32PtsCnt) ? HI_TRUE : HI_FALSE);
}

PTS_SEEK_E PTSQUEUE_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32Idx;
    HI_U32 u32RIdx;
    HI_U32 u32ReadCnt = 0;
    HI_U32 u32WIdx;
    HI_U32 u32TotalSize;
    PTS_ATTR_S*  pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    if (HI_NULL == handle)
    {
        return PTS_SEEK_BUTT;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;
    u32WIdx = pstPtsQueue->u32WIdx & PTS_MASK;

    if (u32RIdx == u32WIdx)
    {
        if (HI_TRUE != pstPtsAttr[u32WIdx].bInjecting)
        {
            return PTS_SEEK_NONE;
        }
        u32TotalSize = 1;
    }
    else
    {
        u32TotalSize = (u32WIdx > u32RIdx) ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx + 1);
    }

    u32Idx = (u32RIdx & PTS_MASK);

    PTS_PRINTF("SeekPts Cur u32RIdx:%d u32WIdx:%d totalReadCnt:%d\n", u32RIdx, u32WIdx, u32TotalSize);

    for (u32ReadCnt = 0; u32ReadCnt < u32TotalSize; u32ReadCnt++)
    {
        if (HI_INVALID_PTS == pstPtsAttr[u32Idx].u32PtsMs)
        {
            u32Idx = (u32Idx + 1) & PTS_MASK;
            continue;
        }

        if ((pstPtsAttr[u32Idx].u32PtsMs + RENDER_PTS_MAX_DIFF) >= u32TargetPts)
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32PtsMs;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BegPos;
            pstPtsQueue->u32RIdx += u32ReadCnt;
            PTS_PRINTF("SeekPts Queue[%d] NearbyPts:%d EndPos:%d\n", pstPtsQueue->u32RIdx, *pu32NearbyPts, *pu32NearbyPos);
            return PTS_SEEK_ALIGN;
        }

        u32Idx = (u32Idx + 1) & PTS_MASK;
    }

    PTS_PRINTF("SeekPts end u32Idx:%d u32ReadCnt:%d\n", u32Idx, u32ReadCnt);

    if (u32Idx >= 1)
    {
        *pu32NearbyPts = pstPtsAttr[u32Idx - 1].u32PtsMs;
        *pu32NearbyPos = pstPtsAttr[u32Idx - 1].u32BegPos;
        PTS_PRINTF("SeekPts find NearbyPos:%d NearbyPts:%d u32Idx:%d\n", *pu32NearbyPos, *pu32NearbyPts, u32Idx);
    }

    if (u32ReadCnt >= 1)    //likely
    {
        pstPtsQueue->u32RIdx += (u32ReadCnt - 1);
    }

    return PTS_SEEK_PACKAGE;
}

PTS_SEEK_E PTSQUEUE_Drop_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    if (HI_NULL == handle)
    {
        return PTS_SEEK_BUTT;
    }

    return PTSQUEUEDropSeek((PTS_QUEUE_S*)handle, u32TargetPts, pu32NearbyPos, pu32NearbyPts);
}

PTS_SEEK_E PTSQUEUE_Drop_PolicySeek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32Idx;
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    HI_U32 u32ReadCnt = 0;
    HI_U32 u32TotalSize;
    PTS_ATTR_S* pstPtsAttr = HI_NULL;
    PTS_QUEUE_S* pstPtsQueue = HI_NULL;

    if (HI_NULL == handle)
    {
        return PTS_SEEK_BUTT;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;
    u32WIdx = pstPtsQueue->u32WIdx & PTS_MASK;
    PTS_PRINTF("RIdx:%d,WIdx:%d,TargetPts:%d\n", u32RIdx, u32WIdx, u32TargetPts);

    u32TotalSize = u32WIdx >= u32RIdx ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx + 1);
    if (0 == u32TotalSize)
    {
        return PTS_SEEK_NONE;
    }

    for (u32Idx = (u32RIdx & PTS_MASK); u32Idx != (u32WIdx & PTS_MASK); u32Idx = ((u32Idx + 1) & PTS_MASK))
    {
        if (pstPtsAttr[u32Idx].u32PtsMs >= u32TargetPts)
        {
            *pu32NearbyPts = pstPtsAttr[u32Idx].u32PtsMs;
            *pu32NearbyPos = pstPtsAttr[u32Idx].u32BegPos;
            pstPtsQueue->u32RIdx += u32ReadCnt;

            return PTS_SEEK_PACKAGE;
        }

        u32ReadCnt++;
    }

    PTS_PRINTF("u32Idx:%d,u32ReadCnt:%d,Pts:%d,Pos:%d\n", u32Idx, u32ReadCnt, pstPtsAttr[u32Idx - 1].u32PtsMs, pstPtsAttr[u32Idx - 1].u32BegPos);

    *pu32NearbyPts = pstPtsAttr[u32Idx - 1].u32PtsMs;
    *pu32NearbyPos = pstPtsAttr[u32Idx - 1].u32EndPos;
    pstPtsQueue->u32RIdx += u32ReadCnt;

    return PTS_SEEK_PACKAGE;
}

PTS_SEEK_E PTSQUEUE_Drop_InvertSeek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts)
{
    HI_U32 u32RCnt, u32WCnt;
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    HI_U32 u32TotalSize;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    if (HI_NULL == handle)
    {
        return PTS_SEEK_BUTT;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;
    u32WIdx = pstPtsQueue->u32WIdx & PTS_MASK;
    PTS_PRINTF("RIdx:%d,WIdx:%d,TargetPts:%d\n", u32RIdx, u32WIdx, u32TargetPts);

    if (u32RIdx == u32WIdx)
    {
        return PTS_SEEK_NONE;
    }
    else
    {
        u32TotalSize = (u32WIdx > u32RIdx) ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx + 1);
    }

    if (0 == u32TotalSize)
    {
        return PTS_SEEK_NONE;
    }

    u32WCnt = (u32WIdx & PTS_MASK);
    for (u32RCnt = (pstPtsQueue->u32RIdx & PTS_MASK); u32RCnt != u32WCnt; (u32RCnt = ((u32RCnt + 1) & PTS_MASK)))
    {
        if (pstPtsAttr[u32RCnt].u32PtsMs >= pstPtsAttr[u32WCnt].u32PtsMs + STREAM_WRAP_PTS_THRESHOLD)
        {
            pstPtsQueue->u32RIdx++;
            continue;
        }
    }

    *pu32NearbyPts = pstPtsAttr[pstPtsQueue->u32RIdx & PTS_MASK].u32PtsMs;
    *pu32NearbyPos = pstPtsAttr[pstPtsQueue->u32RIdx & PTS_MASK].u32BegPos;

    if (pstPtsQueue->u32RIdx == pstPtsQueue->u32WIdx)
    {
        return PTS_SEEK_PACKAGE;
    }

    return PTSQUEUEDropSeek(pstPtsQueue, u32TargetPts, pu32NearbyPos, pu32NearbyPts);
}

HI_S32 PTSQUEUE_Reset(HI_VOID* handle)
{
    HI_U32 u32Idx = 0;
    PTS_ATTR_S*  pstPtsAttr;
    PTS_QUEUE_S* pstPtsQueue;

    CHECK_AO_NULL_PTR(handle);

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;

    pstPtsQueue->bInited = HI_FALSE;
    pstPtsQueue->u32RIdx = 0;
    pstPtsQueue->u32WIdx = 0;

    memset(pstPtsAttr, 0, sizeof(PTS_ATTR_S) * MAX_STORED_PTS_NUM);
    for (u32Idx = 0; u32Idx < MAX_STORED_PTS_NUM; u32Idx++)
    {
        pstPtsAttr[u32Idx].u32PtsMs = HI_INVALID_PTS;
    }

    return HI_SUCCESS;
}

HI_BOOL PTSQUEUE_UpdatedAlignPacket(HI_VOID* handle, HI_U32 u32ConsumedBytes, HI_U32* pu32AlignPos, HI_U32* pu32AlignPts)
{
    HI_U32 u32RIdx;
    HI_U32 u32WIdx;
    HI_U32 u32Idx;
    HI_U32 u32QueueSize;
    HI_U32 u32ReadID = 0;
    PTS_QUEUE_S* pstPtsQueue;
    PTS_ATTR_S* pstPtsAttr;

    if (HI_NULL == handle)
    {
        return HI_FALSE;
    }

    pstPtsQueue = (PTS_QUEUE_S*)handle;
    pstPtsAttr = pstPtsQueue->astPtsAttr;

    u32RIdx = pstPtsQueue->u32RIdx & PTS_MASK;
    u32WIdx = pstPtsQueue->u32WIdx & PTS_MASK;

    if (u32RIdx == u32WIdx)
    {
        u32QueueSize = (HI_TRUE == pstPtsAttr[u32WIdx].bInjecting) ? 1 : 0; //only one package
    }
    else
    {
        u32QueueSize = (u32WIdx > u32RIdx) ? (u32WIdx - u32RIdx + 1) : (MAX_STORED_PTS_NUM - u32RIdx + u32WIdx);
    }

    if ((0 == u32QueueSize) || (1 == u32QueueSize))
    {
        PTS_PRINTF("No Ptsqueue Data\n");
        return HI_FALSE;
    }

    PTS_PRINTF("ToFind align pos, ConsumedBytes:%d QueueSize:%d\n", u32ConsumedBytes, u32QueueSize);

    for (u32Idx = 0; u32Idx < u32QueueSize; u32Idx++)
    {
        u32ReadID = (pstPtsQueue->u32RIdx + u32Idx) & PTS_MASK;

        PTS_PRINTF("UpdateAlignPts Queue[%d] Pts:%d BegPos:%d EndPos:%d\n", u32ReadID, pstPtsAttr[u32ReadID].u32PtsMs, pstPtsAttr[u32ReadID].u32BegPos, pstPtsAttr[u32ReadID].u32EndPos);

        if (pstPtsAttr[u32ReadID].u32BegPos < pstPtsAttr[u32ReadID].u32EndPos)
        {
            if ((pstPtsAttr[u32ReadID].u32BegPos <= u32ConsumedBytes) && (pstPtsAttr[u32ReadID].u32EndPos >= u32ConsumedBytes))
            {
                PTS_PRINTF("FindPts Cirtcl Pos:%d Pts:%d BegPos:%d EndPos:%d\n",
                           u32ConsumedBytes, pstPtsAttr[u32ReadID].u32PtsMs,
                           pstPtsAttr[u32ReadID].u32BegPos, pstPtsAttr[u32ReadID].u32EndPos);
                break;
            }
        }
        else
        {
            if ((pstPtsAttr[u32ReadID].u32BegPos <= u32ConsumedBytes) || (pstPtsAttr[u32ReadID].u32EndPos >= u32ConsumedBytes))
            {
                PTS_PRINTF("FindPts Pos:%d Pts:%d BegPos:%d EndPos:%d\n",
                           u32ConsumedBytes, pstPtsAttr[u32ReadID].u32PtsMs,
                           pstPtsAttr[u32ReadID].u32BegPos, pstPtsAttr[u32ReadID].u32EndPos);

                break;
            }
        }
    }

    if (pstPtsAttr[u32ReadID].u32BegPos == u32ConsumedBytes)
    {
        PTS_PRINTF("Find align pos: %d update Pts:%d RIdx:%d to %d\n", *pu32AlignPos, pstPtsAttr[u32ReadID].u32PtsMs, pstPtsQueue->u32RIdx & PTS_MASK, u32ReadID);
        pstPtsQueue->u32RIdx = u32ReadID;
        *pu32AlignPts = pstPtsAttr[u32ReadID].u32PtsMs;
        *pu32AlignPos = pstPtsAttr[u32ReadID].u32BegPos;
    }
    else
    {
        *pu32AlignPos = pstPtsAttr[u32ReadID].u32EndPos;

        if (u32ReadID == pstPtsQueue->u32WIdx)
        {
            *pu32AlignPts = pstPtsAttr[u32ReadID].u32PtsMs;
            pstPtsAttr[u32WIdx].bInjecting = HI_FALSE;
            pstPtsQueue->u32RIdx = u32ReadID;
        }
        else
        {
            pstPtsQueue->u32RIdx = (u32ReadID + 1) & PTS_MASK;
            *pu32AlignPts = pstPtsAttr[pstPtsQueue->u32RIdx].u32PtsMs;
        }

        PTS_PRINTF("Found align pos , alignPos:%d  alignPts:%d updateReadIndex:%d\n", *pu32AlignPos, *pu32AlignPts, pstPtsQueue->u32RIdx);
    }

    return HI_TRUE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
