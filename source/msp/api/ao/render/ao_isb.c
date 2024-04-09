/******************************************************************************

  Copyright (C), 2011-2020, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ao_isb.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/07/25
  Description  :
  History       :
  1.Date        : 2017/07/25
    Author      :
    Modification: Created file

*******************************************************************************/
#include "hi_type.h"
#include "hi_error_mpi.h"
#include "hi_mpi_ao.h"
#include "mpi_mmz.h"
#include "ao_isb.h"
#include "pts_queue.h"
#include "kfifo2.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#define BUF_OFFSETSIZE        0
#define BUF_TOTAL_SIZE        (sizeof(BUFFER_S))
#define PTS_OFFSETSIZE        BUF_TOTAL_SIZE
#define PTS_TOTAL_SIZE        (sizeof(PTS_QUEUE_S))
#define AOFRAME_OFFSETSIZE    BUF_TOTAL_SIZE
#define AOFRAME_TOTAL_SIZE    (sizeof(AOFRAME_QUEUE_S))
#define BITSTREAM_OFFSETSIZE  (sizeof(BUFFER_S) + sizeof(AOFRAME_QUEUE_S))
#define BITSTREAM_TOTAL_SIZE  (sizeof(BITSTREAM_S))

typedef struct
{
    HI_VOID*         pIsbVirtAddr;
    HI_PHYS_ADDR_T   tPhyIsbAddr;
    kfifo2_s         stBufFifo;
    HI_VOID*         pPtsQue;
    kfifo2_s         stFrameFifo;
    kfifo2_s         stBitsFifo;
    SOURCE_ID_E      enSourceID;
} ISB_STATE_S;

static HI_S32 ISBMemMap(ISB_STATE_S* state, ISB_ATTR_S* pstIsbAttr)
{
#if defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT)
    HI_VOID* pRealDmaAddr = (HI_VOID*)pstIsbAttr->tPhyIsbAddr;

    xthal_dcache_region_invalidate(pRealDmaAddr, pstIsbAttr->u32IsbSize);
    state->pIsbVirtAddr = pRealDmaAddr;
#else
    state->pIsbVirtAddr = HI_MPI_MMZ_Map(pstIsbAttr->tPhyIsbAddr, HI_FALSE);
    if (HI_NULL == state->pIsbVirtAddr)
    {
        HI_ERR_AO("HI_MPI_MMZ_Map ISB failed!\n");
        return HI_ERR_AO_NULL_PTR;
    }
    state->tPhyIsbAddr = pstIsbAttr->tPhyIsbAddr;
#endif

    return HI_SUCCESS;
}

static HI_VOID ISBMemUnMap(ISB_STATE_S* state)
{
#if !(defined (__XTENSA__) && defined (DSP_DDR_CACHE_DMA_SUPPORT))
    if (state->pIsbVirtAddr)
    {
        HI_MPI_MMZ_Unmap(state->tPhyIsbAddr);
        state->pIsbVirtAddr = HI_NULL;
    }
#endif
}

#ifdef AUD_ISB_PTSPROFILE
/* do not delete, use to debug pts is right */
static HI_U32 FirstSysTimeMs = 0;
static HI_U32 FirstPtsMs = HI_INVALID_PTS;
static HI_U32 CurSysTimeMs = 0;
static HI_U32 LatSysTimeMs = 0;
static HI_U32 CurPtsMs = HI_INVALID_PTS;

static HI_VOID ISBDebugPTsPrint(HI_U32 u32PtsMs, HI_U32 u32DataSize)
{
    if (HI_INVALID_PTS == u32PtsMs)
    {
        return;
    }

    HI_SYS_GetTimeStampMs(&CurSysTimeMs);

    if (CurSysTimeMs > LatSysTimeMs + 8000)
    {
        FirstPtsMs = u32PtsMs;
        FirstSysTimeMs = CurSysTimeMs;
        HI_ERR_AO("FirstPtsMs = %d, FirstSysTimeMs = %d\n", FirstPtsMs, FirstSysTimeMs);
    }
    else
    {
        HI_U32 PtsDelta;
        HI_U32 SysTimeDelta;
        SysTimeDelta = CurSysTimeMs - FirstSysTimeMs;
        CurPtsMs = u32PtsMs;
        PtsDelta = CurPtsMs - FirstPtsMs;

        if (SysTimeDelta > PtsDelta)
        {
            HI_ERR_AO("size = %d, CurPtsMs = %d, CurSysTimeMs = %d, PtsDelta = %d, SysTimeDelta = %d, SysTimeDelta - PtsDelta = %d\n", u32DataSize, CurPtsMs, CurSysTimeMs, PtsDelta, SysTimeDelta, SysTimeDelta - PtsDelta);
        }
        else
        {
            HI_ERR_AO("size = %d, CurPtsMs = %d, CurSysTimeMs = %d, PtsDelta = %d, SysTimeDelta = %d, SysTimeDelta - PtsDelta = -%d\n", u32DataSize, CurPtsMs, CurSysTimeMs, PtsDelta, SysTimeDelta, PtsDelta - SysTimeDelta);
        }
    }

    LatSysTimeMs = CurSysTimeMs;
}
#endif

static HI_S32 ISBCheckSize(HI_BOOL bPtsExist, HI_BOOL bAoFrameExist, HI_BOOL bBitstreamIsb, HI_U32 u32IsbSize)
{
    HI_U32 u32TotalSize = BUF_TOTAL_SIZE;

    if (HI_TRUE == bPtsExist)
    {
        u32TotalSize += PTS_TOTAL_SIZE;
    }

    if (HI_TRUE == bAoFrameExist)
    {
        u32TotalSize += AOFRAME_TOTAL_SIZE;
    }

    if (HI_TRUE == bBitstreamIsb)
    {
        u32TotalSize += BITSTREAM_TOTAL_SIZE;
    }

    if (u32IsbSize < u32TotalSize)  //double check the size
    {
        HI_ERR_AO("Err: Isbsize(%d) is small than needed(%d)!\n", u32IsbSize, u32TotalSize);
        return HI_ERR_AO_DATASIZE_EXCEED;
    }

    return HI_SUCCESS;
}

static HI_S32 ISBBufInit(HI_VOID* pIsbVirtAddr, kfifo2_s* pstBufFifo)
{
    HI_S32    s32Ret = HI_SUCCESS;
    BUFFER_S* pstBuffer;

    pstBuffer = (BUFFER_S*)((HI_U8*)pIsbVirtAddr + BUF_OFFSETSIZE);
    s32Ret = kfifo2_init(pstBufFifo, &pstBuffer->u32Write, &pstBuffer->u32Read, pstBuffer->au8Data, 1, RENDER_BUFFER_SIZE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("kfifo_init failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }

    pstBuffer->u32ServerLinearSize = 0;
    HI_WARN_AO("kfifo2_init success\n");

    return HI_SUCCESS;
}

static HI_S32 ISBBitStreamInit(HI_VOID* pIsbVirtAddr, kfifo2_s* pstBufFifo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    BITSTREAM_S* pstBuffer;

    pstBuffer = (BITSTREAM_S*)((HI_U8*)pIsbVirtAddr + BITSTREAM_OFFSETSIZE);
    s32Ret = kfifo2_init(pstBufFifo, &pstBuffer->u32Write, &pstBuffer->u32Read, pstBuffer->au8Data, 1, RENDER_BITSTREAM_SIZE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("kfifo_init failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }

    pstBuffer->u32ServerLinearSize = 0;
    HI_WARN_AO("kfifo2_init success\n");

    return HI_SUCCESS;
}

static HI_S32 ISBFrameInit(HI_VOID* pIsbVirtAddr, kfifo2_s* pstFrmaeFifo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AOFRAME_QUEUE_S* pstFrame;

    pstFrame = (AOFRAME_QUEUE_S*)((HI_U8*)pIsbVirtAddr + AOFRAME_OFFSETSIZE);
    s32Ret = kfifo2_init(pstFrmaeFifo, &pstFrame->u32WIdx, &pstFrame->u32RIdx, pstFrame->astAoFrameAttr,
                         sizeof(HI_HADECODE_OUTPUT_S), sizeof(HI_HADECODE_OUTPUT_S) * RENDER_MAX_EXTDEC_AOFRAME_NUM);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("kfifo_init failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("kfifo2_init success\n");

    return HI_SUCCESS;
}

static HI_VOID ISBPtsInit(HI_VOID* pIsbVirtAddr, HI_VOID** ppPtsQue)
{
    *ppPtsQue = (HI_VOID*)((HI_U8*)pIsbVirtAddr + PTS_OFFSETSIZE);
}

HI_S32 AO_ISB_Create(HI_VOID** phISB, ISB_ATTR_S* pstIsbAttr)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_BOOL bPtsExist = HI_FALSE;
    HI_BOOL bAoFrameExist = HI_FALSE;
    HI_BOOL bBitstreamIsb = HI_FALSE;
    ISB_STATE_S* state;

    if (HI_NULL == phISB || HI_NULL == pstIsbAttr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    if (SOURCE_ID_MAIN == pstIsbAttr->enSourceID || SOURCE_ID_ASSOC == pstIsbAttr->enSourceID)
    {
        bPtsExist = HI_TRUE;
    }

    if (SOURCE_ID_EXTDEC == pstIsbAttr->enSourceID)
    {
        bAoFrameExist = HI_TRUE;
        bBitstreamIsb = HI_TRUE;
    }

    s32Ret = ISBCheckSize(bPtsExist, bAoFrameExist, bBitstreamIsb, pstIsbAttr->u32IsbSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ISBCheckSize failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }

    state = (ISB_STATE_S*)malloc(sizeof(ISB_STATE_S));
    if (HI_NULL == state)
    {
        HI_ERR_AO("Malloc ISB instance failed!\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }
    memset(state, 0, sizeof(ISB_STATE_S));

    s32Ret = ISBMemMap(state, pstIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ISBMemMap failed(0x%x)!\n", s32Ret);
        goto ERR1;
    }

    s32Ret = ISBBufInit(state->pIsbVirtAddr, &state->stBufFifo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ISBBufInit failed(0x%x)!\n", s32Ret);
        goto ERR2;
    }

    // PtsExist and AoFrameExist can not at the same time
    if (HI_TRUE == bPtsExist)
    {
        ISBPtsInit(state->pIsbVirtAddr, &state->pPtsQue);
    }

    if (HI_TRUE == bAoFrameExist)
    {
        s32Ret = ISBFrameInit(state->pIsbVirtAddr, &state->stFrameFifo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("ISBFrameInit failed(0x%x)!\n", s32Ret);
            goto ERR2;
        }
    }

    if (HI_TRUE == bBitstreamIsb)
    {
        s32Ret = ISBBitStreamInit(state->pIsbVirtAddr, &state->stBitsFifo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("ISBBitStreamInit failed(0x%x)!\n", s32Ret);
            goto ERR2;
        }
    }

    HI_WARN_AO("state=%p, SourceID=%d\n", state, pstIsbAttr->enSourceID);

    state->enSourceID = pstIsbAttr->enSourceID;
    *phISB = (HI_VOID*)state;
    return HI_SUCCESS;

    /* No need to do xxx_deInit: 1.no memory to release. 2.xxx_fifo is invalid when state is free.*/
ERR2:
    ISBMemUnMap(state);
ERR1:
    free(state);
    return s32Ret;
}

HI_VOID AO_ISB_Destroy(HI_VOID* hISB)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return;
    }

    state = (ISB_STATE_S*)hISB;
    ISBMemUnMap(state);
    free(state);
}

HI_S32 AO_ISB_SendData(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf)
{
    HI_S32 s32WLen = 0;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstIsbBuf)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr || HI_NULL == pstIsbBuf->pu8Data)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    s32WLen = kfifo2_in(&state->stBufFifo, pstIsbBuf->pu8Data, pstIsbBuf->u32Size);
    if (0 == s32WLen)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_SendBitstream(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf)
{
    HI_S32 s32WLen = 0;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstIsbBuf)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr || HI_NULL == pstIsbBuf->pu8Data)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    s32WLen = kfifo2_in(&state->stBitsFifo, pstIsbBuf->pu8Data, pstIsbBuf->u32Size);
    if (0 == s32WLen)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_CheckFrameInfo(HI_VOID* hISB)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    if (kfifo2_unused(&state->stFrameFifo) < 1)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetBusyFrames(HI_VOID* hISB, HI_U32* pu32FrameCnt)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    *pu32FrameCnt = kfifo2_used(&state->stFrameFifo);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_SendFrameInfo(HI_VOID* hISB, HI_HADECODE_OUTPUT_S* pstPackOut)
{
    HI_S32 s32WLen = 0;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstPackOut)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    s32WLen = kfifo2_in(&state->stFrameFifo, pstPackOut, 1);
    if (0 == s32WLen)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_ReadData(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf)
{
    HI_U32 u32BusyBytes;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstIsbBuf)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr || HI_NULL == pstIsbBuf->pu8Data)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    u32BusyBytes = kfifo2_used(&state->stBufFifo);
    if (u32BusyBytes < pstIsbBuf->u32Size)
    {
        pstIsbBuf->u32Size = u32BusyBytes;
    }

    kfifo2_out(&state->stBufFifo, pstIsbBuf->pu8Data, pstIsbBuf->u32Size);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_ReadBitstream(HI_VOID* hISB, ISB_BUF_S* pstIsbBuf)
{
    HI_U32 u32BusyBytes;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstIsbBuf)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr || HI_NULL == pstIsbBuf->pu8Data)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    u32BusyBytes = kfifo2_used(&state->stBitsFifo);
    if (u32BusyBytes < pstIsbBuf->u32Size)
    {
        pstIsbBuf->u32Size = u32BusyBytes;
    }

    kfifo2_out(&state->stBitsFifo, pstIsbBuf->pu8Data, pstIsbBuf->u32Size);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_AcquireFrameInfo(HI_VOID* hISB, HI_HADECODE_OUTPUT_S* pstPackOut)
{
    HI_S32 s32WLen = 0;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pstPackOut)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    s32WLen = kfifo2_out_prepare(&state->stFrameFifo, pstPackOut, 1);
    if (0 == s32WLen)
    {
        return HI_ERR_AO_INBUF_EMPTY;
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_ReleaseFrameInfo(HI_VOID* hISB, HI_U32 u32Len)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    kfifo2_out_finish(&state->stFrameFifo, u32Len);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetPtsQue(HI_VOID* hISB, HI_VOID** phPtsQue)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == phPtsQue)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    if (HI_NULL == state->pPtsQue)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    *phPtsQue = state->pPtsQue;

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetBusyBytes(HI_VOID* hISB, HI_U32* pu32BusyBytes)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pu32BusyBytes)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    *pu32BusyBytes = kfifo2_used(&state->stBufFifo);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetFreeBytes(HI_VOID* hISB, HI_U32* pu32AllFreeBytes, HI_U32* pu32LinearFreeBytes)
{
    HI_U32 u32FifoBusy = 0;
    BUFFER_S* pstBuffer;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pu32AllFreeBytes)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    pstBuffer = (BUFFER_S*)((HI_U8*)state->pIsbVirtAddr + BUF_OFFSETSIZE);

    u32FifoBusy = kfifo2_used(&state->stBufFifo);

    if (RENDER_BUFFER_SIZE <= u32FifoBusy + pstBuffer->u32ServerLinearSize)
    {
        *pu32AllFreeBytes = 0;
    }
    else
    {
        *pu32AllFreeBytes = RENDER_BUFFER_SIZE - u32FifoBusy - pstBuffer->u32ServerLinearSize;
    }

    if (HI_NULL != pu32LinearFreeBytes)
    {
        *pu32LinearFreeBytes = kfifo2_linear_avail(&state->stBufFifo);
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetBistreamFreeBytes(HI_VOID* hISB, HI_U32* pu32AllFreeBytes, HI_U32* pu32LinearFreeBytes)
{
    HI_U32 u32FifoBusy = 0;
    BITSTREAM_S* pstBuffer;
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == pu32AllFreeBytes)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    pstBuffer = (BITSTREAM_S*)((HI_U8*)state->pIsbVirtAddr + BITSTREAM_OFFSETSIZE);

    u32FifoBusy = kfifo2_used(&state->stBitsFifo);

    if (RENDER_BITSTREAM_SIZE <= u32FifoBusy + pstBuffer->u32ServerLinearSize)
    {
        *pu32AllFreeBytes = 0;
    }
    else
    {
        *pu32AllFreeBytes = RENDER_BITSTREAM_SIZE - u32FifoBusy - pstBuffer->u32ServerLinearSize;
    }

    if (HI_NULL != pu32LinearFreeBytes)
    {
        *pu32LinearFreeBytes = kfifo2_linear_avail(&state->stBitsFifo);
    }

    return HI_SUCCESS;
}

HI_S32 AO_ISB_GetWptr(HI_VOID* hISB, HI_U8** ppu8Data)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB || HI_NULL == ppu8Data)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    kfifo2_get_wptr(&state->stBufFifo, (HI_VOID**)ppu8Data);
    return HI_SUCCESS;
}

HI_S32 AO_ISB_UpdateWptr(HI_VOID* hISB, HI_U32 u32DataSize)
{
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    kfifo2_update_wptr(&state->stBufFifo, u32DataSize);

    return HI_SUCCESS;
}

HI_S32 AO_ISB_SetLinearBusyBytes(HI_VOID* hISB, HI_U32 u32LinearBusy)
{
    BUFFER_S* pstBuffer;
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    pstBuffer = (BUFFER_S*)((HI_U8*)state->pIsbVirtAddr + BUF_OFFSETSIZE);
    pstBuffer->u32ServerLinearSize = u32LinearBusy;

    return HI_SUCCESS;
}

HI_S32 AO_ISB_SetBistreamLinearBusyBytes(HI_VOID* hISB, HI_U32 u32LinearBusy)
{
    BITSTREAM_S* pstBuffer;
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    pstBuffer = (BITSTREAM_S*)((HI_U8*)state->pIsbVirtAddr + BITSTREAM_OFFSETSIZE);
    pstBuffer->u32ServerLinearSize = u32LinearBusy;

    return HI_SUCCESS;
}

HI_S32 AO_ISB_Reset(HI_VOID* hISB)
{
    BUFFER_S* pstBuffer;
    ISB_STATE_S* state;

    if (HI_NULL == hISB)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    state = (ISB_STATE_S*)hISB;

    if (HI_NULL == state->pIsbVirtAddr)
    {
        return HI_ERR_AO_NULL_PTR;
    }

    pstBuffer = (BUFFER_S*)((HI_U8*)state->pIsbVirtAddr + BUF_OFFSETSIZE);

    kfifo2_reset(&state->stBufFifo);
    pstBuffer->u32ServerLinearSize = 0;

    if (SOURCE_ID_EXTDEC == state->enSourceID)
    {
        BITSTREAM_S* pstBitstream;
        kfifo2_reset(&state->stFrameFifo);

        pstBitstream = (BITSTREAM_S*)((HI_U8*)state->pIsbVirtAddr + BITSTREAM_OFFSETSIZE);
        kfifo2_reset(&state->stBitsFifo);
        pstBitstream->u32ServerLinearSize = 0;
    }

    HI_WARN_AO("\n");
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
