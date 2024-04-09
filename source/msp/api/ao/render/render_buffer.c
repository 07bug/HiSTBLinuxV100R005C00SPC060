/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_buffer.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "hi_drv_ao.h"
#include "hi_error_mpi.h"

#include "render_buffer.h"
#include "pts_queue.h"
#include "ao_isb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#define EXTMAIN_LATENCYMS_MAX  (350)

typedef struct
{
    SOURCE_ID_E enSourceID;
    HI_VOID*    hISB;
    HI_VOID*    pLinearBuf;
    HI_U32      u32OutBufSize;

    HI_VOID*    pBitsLinearBuf;
    HI_U32      u32BitsOutBufSize;

    HI_MPI_AO_SB_ATTR_S stISBAttr;
} RENDER_SERVER_BUFFER_S;

typedef struct
{
    SOURCE_ID_E enSourceID;
    HI_VOID*    hISB;
    HI_VOID*    pLinearBuf;
    HI_BOOL     bLinearBufUsed;
} RENDER_CLIENT_BUFFER_S;

static HI_VOID RenderDestroyISB(HI_VOID* hISB)
{
    AO_ISB_Destroy(hISB);
}

static HI_S32 RenderCreateISB(HI_VOID** phISB, HI_MPI_AO_SB_ATTR_S* pstISBAttr)
{
    ISB_ATTR_S stIsbAttr = {0};

    stIsbAttr.enSourceID  = (SOURCE_ID_E)pstISBAttr->enType;
    stIsbAttr.tPhyIsbAddr = pstISBAttr->u32BufPhyAddr;
    stIsbAttr.u32IsbSize  = pstISBAttr->u32BufSize;

    return AO_ISB_Create(phISB, &stIsbAttr);
}

static HI_S32 RenderServerCreateISB(RENDER_SERVER_BUFFER_S* pstBuffer)
{
    HI_S32  s32Ret;
    HI_U32  u32BufSize = 0, u32PtsSize = 0;
    SOURCE_ID_E enSourceID = pstBuffer->enSourceID;

    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        //PCM + AOFrame + LBR + HBR
        u32BufSize = sizeof(BUFFER_S) + sizeof(AOFRAME_QUEUE_S) + sizeof(BITSTREAM_S);
    }
    else
    {
        u32BufSize = sizeof(BUFFER_S);
    }

    if (SOURCE_ID_MAIN == enSourceID || SOURCE_ID_ASSOC == enSourceID)
    {
        u32PtsSize = sizeof(PTS_QUEUE_S);
    }

    pstBuffer->stISBAttr.u32BufSize = u32PtsSize + u32BufSize;
    pstBuffer->stISBAttr.enType = (HI_MPI_RENDER_SOURCE_TYPE_E)enSourceID;

    s32Ret = HI_MPI_AO_SND_CreateShareBuffer(HI_UNF_SND_0, &pstBuffer->stISBAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_CreateShareBuffer, s32Ret);
        return s32Ret;
    }

    s32Ret = RenderCreateISB(&pstBuffer->hISB, &pstBuffer->stISBAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RenderCreateISB, s32Ret);
        goto ERR_EXIT0;
    }

    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        // LBR + HBR linear buf for ms12dec
        pstBuffer->pBitsLinearBuf = (HI_VOID*)malloc(RENDER_BITSTREAM_SIZE);
        if (HI_NULL == pstBuffer->pBitsLinearBuf)
        {
            HI_ERR_AO("malloc BitsLinearBuf failed!\n");
            s32Ret = HI_ERR_AO_MALLOC_FAILED;
            goto ERR_EXIT1;
        }
    }

    return HI_SUCCESS;

ERR_EXIT1:
    RenderDestroyISB(pstBuffer->hISB);
ERR_EXIT0:
    HI_MPI_AO_SND_DestroyShareBuffer(HI_UNF_SND_0, &pstBuffer->stISBAttr);
    return s32Ret;
}

static HI_VOID RenderServerDestroyISB(RENDER_SERVER_BUFFER_S* pstBuffer)
{
    HI_S32 s32Ret;

    if (SOURCE_ID_EXTDEC == pstBuffer->enSourceID)
    {
        if (HI_NULL != pstBuffer->pBitsLinearBuf)
        {
            free(pstBuffer->pBitsLinearBuf);
            pstBuffer->pBitsLinearBuf = HI_NULL;
        }
    }

    RenderDestroyISB(pstBuffer->hISB);

    s32Ret = HI_MPI_AO_SND_DestroyShareBuffer(HI_UNF_SND_0, &pstBuffer->stISBAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_DestroyShareBuffer, s32Ret);
    }
}

HI_S32 RENDER_ServerBuffer_Init(HI_VOID** phHandle, SOURCE_ID_E enSourceID, HI_U32 u32BufSize, HI_VOID* pExtOutBuf)
{
    HI_S32 s32Ret;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(phHandle);
    CHECK_AO_NULL_PTR(pExtOutBuf);

    if (0 == u32BufSize)
    {
        HI_ERR_AO("Invalid arg %d\n", u32BufSize);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstBuffer = (RENDER_SERVER_BUFFER_S*)malloc(sizeof(RENDER_SERVER_BUFFER_S));
    if (HI_NULL == pstBuffer)
    {
        HI_ERR_AO("malloc render server buffer failed!\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }
    memset(pstBuffer, 0, sizeof(RENDER_SERVER_BUFFER_S));

    pstBuffer->enSourceID = enSourceID;
    pstBuffer->pLinearBuf = pExtOutBuf;

    s32Ret = RenderServerCreateISB(pstBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        free(pstBuffer);
        return s32Ret;
    }

    *phHandle = (HI_VOID*)pstBuffer;

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_DeInit(HI_VOID* handle)
{
    RENDER_SERVER_BUFFER_S* pstBuffer;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    RenderServerDestroyISB(pstBuffer);
    free(pstBuffer);

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_Acquire(HI_VOID* handle, HI_U32 u32NeedSize, HI_U8** ppu8Data, HI_U32* pu32Size)
{
    HI_S32 s32Ret;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;
    ISB_BUF_S stIsbBuf = {0};

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(ppu8Data);
    CHECK_AO_NULL_PTR(pu32Size);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    if (u32NeedSize > RENDER_BUFFER_SIZE)
    {
        u32NeedSize = RENDER_BUFFER_SIZE;
    }

    if (pstBuffer->u32OutBufSize > RENDER_BUFFER_SIZE)
    {
        HI_ERR_AO("Invalid Source(%d) LinearOutBufSize(%d) > Max(%d)\n", pstBuffer->enSourceID,
                  pstBuffer->u32OutBufSize, RENDER_BUFFER_SIZE);
        return HI_ERR_AO_DATASIZE_EXCEED;
    }

    stIsbBuf.pu8Data = pstBuffer->pLinearBuf + pstBuffer->u32OutBufSize;
    if (u32NeedSize > pstBuffer->u32OutBufSize)
    {
        stIsbBuf.u32Size = u32NeedSize - pstBuffer->u32OutBufSize;
        s32Ret = AO_ISB_ReadData(pstBuffer->hISB, &stIsbBuf);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(AO_ISB_ReadData, s32Ret);
            return s32Ret;
        }
    }
    else
    {
        stIsbBuf.u32Size = 0;
    }

    pstBuffer->u32OutBufSize += stIsbBuf.u32Size;

    (HI_VOID)AO_ISB_SetLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32OutBufSize);

    *ppu8Data = pstBuffer->pLinearBuf;

    *pu32Size = (u32NeedSize < pstBuffer->u32OutBufSize) ? u32NeedSize : pstBuffer->u32OutBufSize;

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_Release(HI_VOID* handle, HI_U32 u32Size)
{
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);

    if (0 == u32Size)
    {
        return HI_SUCCESS;
    }

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;
    if (u32Size > pstBuffer->u32OutBufSize)
    {
        HI_WARN_AO("Release size(%d) larger than RingBuffersize(%d)\n", u32Size, pstBuffer->u32OutBufSize);
        return HI_FAILURE;
    }

    memmove(pstBuffer->pLinearBuf, (HI_U8*)pstBuffer->pLinearBuf + u32Size, pstBuffer->u32OutBufSize - u32Size);
    pstBuffer->u32OutBufSize -= u32Size;

    (HI_VOID)AO_ISB_SetLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32OutBufSize);

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerFrame_Acquire(HI_VOID* handle, HI_U32 u32NeedSize, HI_HADECODE_OUTPUT_S* pstPackOut, HI_U32* pu32Size)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_U32  u32FrameCnt = 0, u32FrameSize = 0;
    HI_BOOL bReleaseFrame = HI_FALSE;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;
    ISB_BUF_S stIsbBuf = {0};

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pstPackOut);
    CHECK_AO_NULL_PTR(pu32Size);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    s32Ret = AO_ISB_AcquireFrameInfo(pstBuffer->hISB, pstPackOut);
    if ((HI_SUCCESS != s32Ret) && (0 == pstBuffer->u32OutBufSize))
    {
        if (HI_ERR_AO_INBUF_EMPTY == s32Ret)
        {
            HI_INFO_AO("AO_ISB_AcquireFrameInfo OutBuf Empty, no frame!\n");
            *pu32Size = 0;
            return HI_SUCCESS;
        }

        HI_LOG_PrintFuncErr(AO_ISB_AcquireFrameInfo, s32Ret);
        return s32Ret;
    }

    HI_WARN_AO("BitsBytesPerFrame=0x%x, PcmSamplesPerFrame=%d, SampleRate=%d, Bitdepth=%d\n",
               pstPackOut->u32BitsOutBytesPerFrame, pstPackOut->u32PcmOutSamplesPerFrame, pstPackOut->u32OutSampleRate, pstPackOut->u32BitPerSample);

    if (16 == pstPackOut->u32BitPerSample)
    {
        u32FrameSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U16);
    }
    else
    {
        u32FrameSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U32);
    }

    if (0 == u32FrameSize)
    {
        HI_ERR_AO("Invalid OutFrame(Samples:%d, Ch:%d)!", pstPackOut->u32PcmOutSamplesPerFrame, pstPackOut->u32OutChannels);
        return HI_ERR_AO_INVALID_OUTFRAME;
    }

    u32NeedSize = u32FrameSize;  // alway acquire a fame one times
    u32FrameCnt = u32NeedSize / u32FrameSize;

    HI_WARN_AO("u32NeedSize=%d, u32FrameCnt=%d\n", u32NeedSize, u32FrameCnt);

    // pcm
    {
        stIsbBuf.pu8Data = pstBuffer->pLinearBuf + pstBuffer->u32OutBufSize;

        if (u32NeedSize > pstBuffer->u32OutBufSize)
        {
            stIsbBuf.u32Size = u32NeedSize - pstBuffer->u32OutBufSize;
            s32Ret = AO_ISB_ReadData(pstBuffer->hISB, &stIsbBuf);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_AO("AO_ISB_ReadData failed(0x%x)\n", s32Ret);
                return s32Ret;
            }

            bReleaseFrame = HI_TRUE;
        }
        else
        {
            stIsbBuf.u32Size = 0;
        }

        pstBuffer->u32OutBufSize += stIsbBuf.u32Size;
        (HI_VOID)AO_ISB_SetLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32OutBufSize);
        pstPackOut->ps32PcmOutBuf = (HI_S32*)pstBuffer->pLinearBuf;

        *pu32Size = (u32NeedSize < pstBuffer->u32OutBufSize) ? u32NeedSize : pstBuffer->u32OutBufSize;
    }

    // bitstream
    if (0 != pstPackOut->u32BitsOutBytesPerFrame)
    {
        u32NeedSize = u32FrameCnt * ((pstPackOut->u32BitsOutBytesPerFrame >> 16) + (pstPackOut->u32BitsOutBytesPerFrame & 0x7fff));
        HI_INFO_AO("NeedSize=%d, FrameCnt=%d, BitsOutBufSize=%d\n", u32NeedSize, u32FrameCnt, pstBuffer->u32BitsOutBufSize);

        stIsbBuf.pu8Data = pstBuffer->pBitsLinearBuf + pstBuffer->u32BitsOutBufSize;
        if (u32NeedSize > pstBuffer->u32BitsOutBufSize)
        {
            stIsbBuf.u32Size = u32NeedSize - pstBuffer->u32BitsOutBufSize;
            s32Ret = AO_ISB_ReadBitstream(pstBuffer->hISB, &stIsbBuf);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_AO("AO_ISB_ReadData failed(0x%x)\n", s32Ret);
                return s32Ret;
            }

            bReleaseFrame = HI_TRUE;
        }
        else
        {
            stIsbBuf.u32Size = 0;
        }

        pstBuffer->u32BitsOutBufSize += stIsbBuf.u32Size;
        (HI_VOID)AO_ISB_SetBistreamLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32BitsOutBufSize);
        pstPackOut->ps32BitsOutBuf = (HI_S32*)pstBuffer->pBitsLinearBuf;
    }

    if (HI_TRUE == bReleaseFrame)
    {
        (HI_VOID)AO_ISB_ReleaseFrameInfo(pstBuffer->hISB, u32FrameCnt);
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerFrame_Release(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut, HI_U32 u32Size)
{
    HI_U32 u32FrameCnt, u32FrameSize, u32ReleaseSize;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pstPackOut);

    if (0 == u32Size)
    {
        return HI_SUCCESS;
    }

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    if (16 == pstPackOut->u32BitPerSample)
    {
        u32FrameSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U16);
    }
    else
    {
        u32FrameSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U32);
    }

    if (0 == u32FrameSize)
    {
        HI_ERR_AO("Invalid OutFrame(Samples:%d, Ch:%d)!", pstPackOut->u32PcmOutSamplesPerFrame, pstPackOut->u32OutChannels);
        return HI_ERR_AO_INVALID_OUTFRAME;
    }

    u32ReleaseSize = u32Size;
    u32FrameCnt = u32ReleaseSize / u32FrameSize;

    // PCM
    {
        if (u32ReleaseSize > pstBuffer->u32OutBufSize)
        {
            HI_WARN_AO("Release size(%d) larger than RingBuffersize(%d)\n", u32ReleaseSize, pstBuffer->u32OutBufSize);
            return HI_FAILURE;
        }

        memmove(pstBuffer->pLinearBuf, (HI_U8*)pstBuffer->pLinearBuf + u32ReleaseSize, pstBuffer->u32OutBufSize - u32ReleaseSize);
        pstBuffer->u32OutBufSize -= u32ReleaseSize;

        (HI_VOID)AO_ISB_SetLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32OutBufSize);
    }

    // bitstream
    if (0 != pstPackOut->u32BitsOutBytesPerFrame)
    {
        u32ReleaseSize = u32FrameCnt * ((pstPackOut->u32BitsOutBytesPerFrame >> 16) + (pstPackOut->u32BitsOutBytesPerFrame & 0x7fff));
        HI_INFO_AO("ReleaseSize=%d, FrameCnt=%d\n", u32ReleaseSize, u32FrameCnt);

        if (u32ReleaseSize > pstBuffer->u32BitsOutBufSize)
        {
            HI_WARN_AO("Release size(%d) larger than RingBuffersize(%d)\n", u32ReleaseSize, pstBuffer->u32BitsOutBufSize);
            return HI_FAILURE;
        }

        memmove(pstBuffer->pBitsLinearBuf, (HI_U8*)pstBuffer->pBitsLinearBuf + u32ReleaseSize, pstBuffer->u32BitsOutBufSize - u32ReleaseSize);
        pstBuffer->u32BitsOutBufSize -= u32ReleaseSize;

        (HI_VOID)AO_ISB_SetBistreamLinearBusyBytes(pstBuffer->hISB, pstBuffer->u32BitsOutBufSize);
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_GetFrameInfo(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut)
{
    HI_S32 s32Ret = HI_SUCCESS;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pstPackOut);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    s32Ret = AO_ISB_AcquireFrameInfo(pstBuffer->hISB, pstPackOut);
    if (HI_SUCCESS != s32Ret)
    {
        if (HI_ERR_AO_INBUF_EMPTY == s32Ret)
        {
            HI_INFO_AO("AO_ISB_AcquireFrameInfo OutBuf Empty, no frame!\n");
            return HI_SUCCESS;
        }

        HI_LOG_PrintFuncErr(AO_ISB_AcquireFrameInfo, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_Enquire(HI_VOID* handle, HI_U32* pu32UsedSize, HI_U32* pu32TotSize)
{
    HI_S32 s32Ret;
    HI_U32 u32BusyBytes = 0;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pu32UsedSize);
    CHECK_AO_NULL_PTR(pu32TotSize);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;
    s32Ret = AO_ISB_GetBusyBytes(pstBuffer->hISB, &u32BusyBytes);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_GetBusyBytes, s32Ret);
        return s32Ret;
    }

    *pu32TotSize  = RENDER_BUFFER_SIZE;
    *pu32UsedSize = u32BusyBytes + pstBuffer->u32OutBufSize;

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_Reset(HI_VOID* handle)
{
    HI_S32 s32Ret;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    s32Ret = AO_ISB_Reset(pstBuffer->hISB);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_Reset, s32Ret);
    }

    if (HI_NULL != pstBuffer->pLinearBuf)
    {
        memset(pstBuffer->pLinearBuf, 0, RENDER_BUFFER_SIZE);
    }
    pstBuffer->u32OutBufSize = 0;

    if (SOURCE_ID_EXTDEC == pstBuffer->enSourceID)
    {
        if (HI_NULL != pstBuffer->pBitsLinearBuf)
        {
            memset(pstBuffer->pBitsLinearBuf, 0, RENDER_BITSTREAM_SIZE);
        }
        pstBuffer->u32BitsOutBufSize = 0;
    }

    return s32Ret;
}

HI_S32 RENDER_ServerBuffer_GetDataSize(HI_VOID* handle, HI_U32* pu32BufSize)
{
    HI_S32 s32Ret;
    HI_U32 u32BusyBytes = 0;
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pu32BufSize);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    s32Ret = AO_ISB_GetBusyBytes(pstBuffer->hISB, &u32BusyBytes);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_GetBusyBytes, s32Ret);
        return s32Ret;
    }

    *pu32BufSize = pstBuffer->u32OutBufSize + u32BusyBytes;

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_GetISBHandle(HI_VOID* handle, HI_VOID** phISB)
{
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(phISB);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;
    *phISB = pstBuffer->hISB;

    return HI_SUCCESS;
}

HI_S32 RENDER_ServerBuffer_GetISBAttr(HI_VOID* handle, HI_MPI_AO_SB_ATTR_S* pstSBAttr)
{
    RENDER_SERVER_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pstSBAttr);

    pstBuffer = (RENDER_SERVER_BUFFER_S*)handle;

    memcpy(pstSBAttr, &pstBuffer->stISBAttr, sizeof(HI_MPI_AO_SB_ATTR_S));

    return HI_SUCCESS;
}

HI_S32  RENDER_ClientBuffer_Init(HI_VOID** phHandle, SOURCE_ID_E enSourceID, HI_MPI_AO_SB_ATTR_S* pstSBAttr)
{
    HI_S32  s32Ret;
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(phHandle);
    CHECK_AO_NULL_PTR(pstSBAttr);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)malloc(sizeof(RENDER_CLIENT_BUFFER_S));
    if (HI_NULL == pstBuffer)
    {
        HI_ERR_AO("malloc Render client buffer failed!\n");
        return HI_ERR_AO_MALLOC_FAILED;
    }

    memset(pstBuffer, 0, sizeof(RENDER_CLIENT_BUFFER_S));
    pstBuffer->enSourceID = enSourceID;

    pstBuffer->pLinearBuf = (HI_VOID*)malloc(RENDER_BUFFER_SIZE);
    if (HI_NULL == pstBuffer->pLinearBuf)
    {
        HI_ERR_AO("malloc LinearBuf failed!\n");
        s32Ret = HI_ERR_AO_MALLOC_FAILED;
        goto ERR_EXIT0;
    }

    s32Ret = RenderCreateISB(&pstBuffer->hISB, pstSBAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RenderCreateISB, s32Ret);
        goto ERR_EXIT1;
    }

    *phHandle = (HI_VOID*)pstBuffer;

    return HI_SUCCESS;

ERR_EXIT1:
    free(pstBuffer->pLinearBuf);
ERR_EXIT0:
    free(pstBuffer);
    return s32Ret;
}

HI_S32 RENDER_ClientBuffer_DeInit(HI_VOID* handle)
{
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    RenderDestroyISB(pstBuffer->hISB);

    if (HI_NULL != pstBuffer->pLinearBuf)
    {
        free(pstBuffer->pLinearBuf);
    }

    free(pstBuffer);

    return HI_SUCCESS;
}

HI_S32 RENDER_ClientBuffer_GetISBHandle(HI_VOID* handle, HI_VOID** phISB)
{
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(phISB);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;
    *phISB = pstBuffer->hISB;

    return HI_SUCCESS;
}

HI_S32 RENDER_ClientBuffer_Send(HI_VOID* handle, HI_U8* pu8Data, HI_U32 u32Size)
{
    HI_S32 s32Ret;
    HI_U32 u32FreeSize = 0;
    ISB_BUF_S stIsbBuf = {0};
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pu8Data);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    s32Ret = AO_ISB_GetFreeBytes(pstBuffer->hISB, &u32FreeSize, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_GetFreeBytes, s32Ret);
        return s32Ret;
    }

    HI_INFO_AO("Render Buffer FreeBytes(%d), SendBytes(%d)\n", u32FreeSize, u32Size);

    if (u32Size > u32FreeSize)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    stIsbBuf.pu8Data = pu8Data;
    stIsbBuf.u32Size = u32Size;

    return AO_ISB_SendData(pstBuffer->hISB, &stIsbBuf);
}

HI_S32 RENDER_ClientBuffer_SendAoFrame(HI_VOID* handle, HI_HADECODE_OUTPUT_S* pstPackOut)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32FrameCnt = 0;
    HI_U32 u32LbrSize  = 0, u32HbrSize  = 0;
    HI_U32 u32SendSize = 0, u32FreeSize = 0;
    ISB_BUF_S stIsbBuf = {0};
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pstPackOut);

    if (0 == pstPackOut->u32PcmOutSamplesPerFrame && 0 == pstPackOut->u32BitsOutBytesPerFrame)
    {
        HI_ERR_PrintInfo("Invalid AoFrame no samples");
        HI_LOG_PrintErrCode(HI_ERR_AO_INVALID_OUTFRAME);
        return HI_ERR_AO_INVALID_OUTFRAME;
    }

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    HI_WARN_AO("BitsBytesPerFrame=0x%x, PcmSamplesPerFrame=%d, SampleRate=%d, Bitdepth=%d\n",
               pstPackOut->u32BitsOutBytesPerFrame, pstPackOut->u32PcmOutSamplesPerFrame, pstPackOut->u32OutSampleRate, pstPackOut->u32BitPerSample);

    s32Ret = AO_ISB_GetBusyFrames(pstBuffer->hISB, &u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_SendFrameInfo, s32Ret);
        return s32Ret;
    }

    if (0 != pstPackOut->u32OutSampleRate)
    {
        HI_U32 u32ExtMainDelayMs = 0;
        u32ExtMainDelayMs = u32FrameCnt * pstPackOut->u32PcmOutSamplesPerFrame * 1000 / pstPackOut->u32OutSampleRate;

        HI_WARN_AO("FrameCnt:%d ExtMainDelayMs:%d\n", u32FrameCnt, u32ExtMainDelayMs);

        if (u32ExtMainDelayMs >= EXTMAIN_LATENCYMS_MAX)
        {
            return HI_ERR_AO_OUT_BUF_FULL;
        }
    }

    s32Ret = AO_ISB_CheckFrameInfo(pstBuffer->hISB);
    if (HI_SUCCESS != s32Ret)
    {
        if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
        {
            HI_INFO_AO("AO_ISB_SendFrameInfo Buf Full!");
        }
        else
        {
            HI_LOG_PrintFuncErr(AO_ISB_SendFrameInfo, s32Ret);
        }

        return s32Ret;
    }

    if (0 != pstPackOut->u32BitsOutBytesPerFrame && HI_NULL != pstPackOut->ps32BitsOutBuf)
    {
        s32Ret = AO_ISB_GetBistreamFreeBytes(pstBuffer->hISB, &u32FreeSize, HI_NULL);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(AO_ISB_GetBistreamFreeBytes, s32Ret);
            return s32Ret;
        }

        u32LbrSize = pstPackOut->u32BitsOutBytesPerFrame & 0x7fff;
        u32HbrSize = (pstPackOut->u32BitsOutBytesPerFrame >> 16) & 0xffff;

        HI_INFO_AO("Render BitsStream FreeBytes(%d), SendBytes(%d)\n", u32FreeSize, u32HbrSize + u32LbrSize);

        if (u32HbrSize + u32LbrSize > u32FreeSize)
        {
            return HI_ERR_AO_OUT_BUF_FULL;
        }
    }

    if (0 != pstPackOut->u32PcmOutSamplesPerFrame && HI_NULL != pstPackOut->ps32PcmOutBuf)
    {
        s32Ret = AO_ISB_GetFreeBytes(pstBuffer->hISB, &u32FreeSize, HI_NULL);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(AO_ISB_GetFreeBytes, s32Ret);
            return s32Ret;
        }

        if (16 == pstPackOut->u32BitPerSample)
        {
            u32SendSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U16);
        }
        else
        {
            u32SendSize = pstPackOut->u32PcmOutSamplesPerFrame * pstPackOut->u32OutChannels * sizeof(HI_U32);
        }

        HI_INFO_AO("Render Buffer FreeBytes(%d), SendBytes(%d)\n", u32FreeSize, u32SendSize);

        if (u32SendSize > u32FreeSize)
        {
            return HI_ERR_AO_OUT_BUF_FULL;
        }
    }

    if (0 != pstPackOut->u32BitsOutBytesPerFrame && HI_NULL != pstPackOut->ps32BitsOutBuf)
    {
        // LBR
        if (0 != u32LbrSize)
        {
            stIsbBuf.pu8Data = (HI_U8*)pstPackOut->ps32BitsOutBuf;
            stIsbBuf.u32Size = u32LbrSize;
            s32Ret = AO_ISB_SendBitstream(pstBuffer->hISB, &stIsbBuf);
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(AO_ISB_SendBitstream, s32Ret);
                return s32Ret;
            }
        }

        // HBR
        if (0 != u32HbrSize)
        {
            stIsbBuf.pu8Data = (HI_U8*)pstPackOut->ps32BitsOutBuf + (pstPackOut->u32BitsOutBytesPerFrame & 0x7fff);
            stIsbBuf.u32Size = u32HbrSize;
            s32Ret = AO_ISB_SendBitstream(pstBuffer->hISB, &stIsbBuf);
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(AO_ISB_SendBitstream, s32Ret);
                return s32Ret;
            }
        }
    }

    if (0 != pstPackOut->u32PcmOutSamplesPerFrame && HI_NULL != pstPackOut->ps32PcmOutBuf)
    {
        stIsbBuf.pu8Data = (HI_U8*)pstPackOut->ps32PcmOutBuf;
        stIsbBuf.u32Size = u32SendSize;

        s32Ret = AO_ISB_SendData(pstBuffer->hISB, &stIsbBuf);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(AO_ISB_SendData, s32Ret);
            return s32Ret;
        }
    }

    s32Ret = AO_ISB_SendFrameInfo(pstBuffer->hISB, pstPackOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_SendFrameInfo, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_ClientBuffer_Get(HI_VOID* handle, HI_U32 u32RequestSize, HI_U8** ppu8Data)
{
    HI_S32 s32Ret;
    HI_U32 u32FreeSize = 0, u32LinearSize = 0;
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(ppu8Data);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    s32Ret = AO_ISB_GetFreeBytes(pstBuffer->hISB, &u32FreeSize, &u32LinearSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_GetFreeBytes, s32Ret);
        return s32Ret;
    }

    if (u32FreeSize < u32RequestSize)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    if (u32RequestSize <= u32LinearSize)
    {
        return AO_ISB_GetWptr(pstBuffer->hISB, ppu8Data);
    }

    *ppu8Data = pstBuffer->pLinearBuf;
    pstBuffer->bLinearBufUsed = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 RENDER_ClientBuffer_Put(HI_VOID* handle, HI_U32 u32DataSize, HI_U8* pu8Data)
{
    HI_S32 s32Ret;
    ISB_BUF_S stIsbBuf = {0};
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);
    CHECK_AO_NULL_PTR(pu8Data);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    if (HI_TRUE != pstBuffer->bLinearBufUsed)
    {
        (HI_VOID)AO_ISB_UpdateWptr(pstBuffer->hISB, u32DataSize);
        return HI_SUCCESS;
    }

    stIsbBuf.pu8Data = pu8Data;
    stIsbBuf.u32Size = u32DataSize;

    s32Ret = AO_ISB_SendData(pstBuffer->hISB, &stIsbBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("AO_ISB_SendData write %d failed(0x%x)\n", u32DataSize, s32Ret);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    pstBuffer->bLinearBufUsed = HI_FALSE;
    return HI_SUCCESS;
}

HI_S32 RENDER_ClientBuffer_Reset(HI_VOID* handle)
{
    HI_S32 s32Ret;
    RENDER_CLIENT_BUFFER_S* pstBuffer = HI_NULL;

    CHECK_AO_NULL_PTR(handle);

    pstBuffer = (RENDER_CLIENT_BUFFER_S*)handle;

    s32Ret = AO_ISB_Reset(pstBuffer->hISB);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(AO_ISB_Reset, s32Ret);
    }

    return s32Ret;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
