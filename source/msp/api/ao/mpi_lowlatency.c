#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>

#include "mpi_lowlatency.h"
#include "hi_mpi_mem.h"
#include "hi_error_mpi.h"
#include "hi_drv_ao.h"
#include "drv_ao_ioctl.h"
#include "hi_audsp_aoe.h"
#include "mpi_mmz.h"

#include "api_circ_buf.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct
{
    HI_U32 u32BitPerSample;                /**<Data depth*/ /**<CNcomment:位宽*/
    HI_U32 u32SampleRate;                  /**<samplerate*/ /**<CNcomment:采样率*/
    HI_U32 u32Channels;                    /**<Channel*/ /**<Ncomment:声道数*/
    HI_U32 u32BufLevelMs;

    S_AIP_REGS_TYPE* pstAipReg;
    CIRC_BUF_S stCb;
    HI_BOOL bUsed;

    AO_Track_Mmap_Param_S stParam;
} TRACK_MMAP_SOURCE_S;

#define AO_TRACK_LOWLATENCY_DEFATTR_BUFLEVELMS 400
#define PAGE_SIZE_MASK     (0xfffff000)
#define MEM_PAGE_SIZE      (0x1000)

extern HI_S32 g_s32AOFd;
static pthread_mutex_t g_LLTMutex = PTHREAD_MUTEX_INITIALIZER;
static TRACK_MMAP_SOURCE_S g_stTrackMapSource = {0};

#define LLT_LOCK()    (void)pthread_mutex_lock(&g_LLTMutex)
#define LLT_UNLOCK()  (void)pthread_mutex_unlock(&g_LLTMutex)

static HI_VOID TrackMapSourceReset(HI_VOID)
{
    memset(&g_stTrackMapSource, 0, sizeof(TRACK_MMAP_SOURCE_S));

    g_stTrackMapSource.u32BitPerSample = HI_UNF_BIT_DEPTH_16;
    g_stTrackMapSource.u32SampleRate   = HI_UNF_SAMPLE_RATE_48K;
    g_stTrackMapSource.u32Channels     = 2;
    g_stTrackMapSource.u32BufLevelMs   = AO_TRACK_LOWLATENCY_DEFATTR_BUFLEVELMS;
}

static HI_BOOL CIRC_BUF_Check(CIRC_BUF_S* pstCb)
{
    return (HI_NULL != pstCb &&
            HI_NULL != pstCb->pu32Write &&
            HI_NULL != pstCb->pu32Read &&
            HI_NULL != pstCb->pu8Data);
}

static HI_S32 TRACKMmapWriteFrame(CIRC_BUF_S* pstCb, const HI_UNF_AO_FRAMEINFO_S* pstAoFrame)
{
    HI_U32 u32BusySize = 0;
    HI_U32 u32Latency = 0, u32FrameSize = 0, u32WriteSize = 0;

    if (HI_FALSE == CIRC_BUF_Check(pstCb))
    {
        HI_ERR_AO("Invalid lowlatency track circle buffer!\n");
        return HI_FAILURE;
    }

    u32FrameSize = pstAoFrame->u32PcmSamplesPerFrame * pstAoFrame->u32Channels * sizeof(HI_U16);

    u32Latency = g_stTrackMapSource.u32BufLevelMs * pstAoFrame->u32SampleRate * pstAoFrame->u32Channels * sizeof(HI_U16) / 1000;

    u32BusySize = CIRC_BUF_QueryBusy(pstCb);
    if ((u32BusySize + u32FrameSize) >= u32Latency)
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    u32WriteSize = CIRC_BUF_Write(pstCb, (HI_U8*)pstAoFrame->ps32PcmBuffer, u32FrameSize);

    return (u32WriteSize == u32FrameSize) ? HI_SUCCESS : HI_FAILURE;
}

static HI_VOID LOWLATENCYUnMapAip(HI_HANDLE hTrack)
{
    S_AIP_REGS_TYPE* pstAipReg = g_stTrackMapSource.pstAipReg;
    if (HI_NULL != pstAipReg)
    {
        HI_MPI_MMZ_Unmap(g_stTrackMapSource.stParam.u32AipRegAddr);
    }
}

static HI_S32 LOWLATENCYMapAip(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_VOID* pAigReg;

    g_stTrackMapSource.stParam.hTrack          = hTrack;
    g_stTrackMapSource.stParam.u32BitPerSample = g_stTrackMapSource.u32BitPerSample;
    g_stTrackMapSource.stParam.u32SampleRate   = g_stTrackMapSource.u32SampleRate;
    g_stTrackMapSource.stParam.u32Channels     = g_stTrackMapSource.u32Channels;

    s32Ret = ioctl(g_s32AOFd, CMD_AO_TRACK_MMAP, &g_stTrackMapSource.stParam);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AO("ioctl CMD_AO_TRACK_MMAPTRACKATTR failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }
    if (HI_NULL == g_stTrackMapSource.stParam.u32AipRegAddr)
    {
        HI_ERR_AO("Get Aip Register address error!\n");
        return HI_FAILURE;
    }

    pAigReg = (S_AIP_REGS_TYPE*)HI_MPI_MMZ_Map(g_stTrackMapSource.stParam.u32AipRegAddr, HI_FALSE);//hi_memmap
    if (HI_NULL == pAigReg)
    {
        HI_ERR_AO("mmap aip register failed 34234!\n");
        return HI_FAILURE;
    }

    g_stTrackMapSource.pstAipReg = pAigReg;
    return HI_SUCCESS;
}

static HI_VOID LOWLATENCYUnmapBuf(HI_HANDLE hTrack)
{
    HI_VOID* pData = (HI_VOID*)(g_stTrackMapSource.stCb.pu8Data);

    if (HI_NULL != pData)
    {
        HI_MPI_MMZ_Unmap(g_stTrackMapSource.pstAipReg->AIP_BUF_PHYADDR);
    }
}

static HI_S32 LOWLATENCYMapBuf(HI_HANDLE hTrack)
{
    HI_U8*  pu8Data = HI_NULL;
    S_AIP_REGS_TYPE* pstAipReg = g_stTrackMapSource.pstAipReg;

    pu8Data = (HI_U8*)HI_MPI_MMZ_Map(pstAipReg->AIP_BUF_PHYADDR, HI_FALSE);
    if (HI_NULL == pu8Data)
    {
        HI_ERR_AO("mmap aip buffer failed!\n");
        return HI_FAILURE;
    }

    CIRC_BUF_Init(&(g_stTrackMapSource.stCb),
                  (HI_VOID*)(&(pstAipReg->AIP_BUF_WPTR)),
                  (HI_VOID*)(&(pstAipReg->AIP_BUF_RPTR)),
                  pu8Data,
                  pstAipReg->AIP_BUF_SIZE.bits.buff_size);

    return HI_SUCCESS;
}

static HI_S32 LOWLATENCYTrackMap(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = LOWLATENCYMapAip(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("LOWLATENCYMapAip failed(0x%x)!\n", s32Ret);
        return s32Ret;
    }

    s32Ret = LOWLATENCYMapBuf(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("LOWLATENCYMapBuf failed(0x%x)!\n", s32Ret);
        LOWLATENCYUnMapAip(hTrack);
    }
    return s32Ret;
}

static HI_VOID LOWLATENCYTrackUnmap(HI_HANDLE hTrack)
{
    LOWLATENCYUnmapBuf(hTrack);
    LOWLATENCYUnMapAip(hTrack);
}

static HI_S32 LOWLATENCYTrackSetFifoBypass(HI_HANDLE hTrack, HI_BOOL bEnable)
{
    AO_Track_FifoBypass_Param_S stParam;
    stParam.hTrack = hTrack;
    stParam.bEnable = bEnable;
    CHECK_AO_TRACK_ID(hTrack);

    return ioctl(g_s32AOFd, CMD_AO_TRACK_SETFIFOBYPASS, &stParam);
}

HI_BOOL LOWLATENCY_CheckIsLowLatencyTrack(HI_HANDLE hTrack)
{
    if ((hTrack & 0xff00) == (HI_ID_LOWLATENCY_TRACK << 8))
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

HI_S32 LOWLATENCY_Enable(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    LLT_LOCK();

    if (HI_TRUE == g_stTrackMapSource.bUsed)
    {
        HI_ERR_AO("LOWLATENCYTrack is busy!\n");
        LLT_UNLOCK();
        return HI_FAILURE;
    }

    TrackMapSourceReset();

    s32Ret = LOWLATENCYTrackMap(hTrack);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AO("LOWLATENCYTrackMap failed(0x%x)!\n", s32Ret);
        LLT_UNLOCK();
        return s32Ret;
    }

    s32Ret = LOWLATENCYTrackSetFifoBypass(hTrack, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AO("LOWLATENCYTrackSetFifoBypass failed(0x%x)!\n", s32Ret);
        LOWLATENCYTrackUnmap(hTrack);
        LLT_UNLOCK();
        return s32Ret;
    }

    g_stTrackMapSource.bUsed = HI_TRUE;

    LLT_UNLOCK();
    return s32Ret;
}

HI_S32 LOWLATENCY_Disable(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    LLT_LOCK();

    s32Ret = LOWLATENCYTrackSetFifoBypass(hTrack, HI_FALSE);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AO("LOWLATENCYTrackSetFifoBypass failed(0x%x)!\n", s32Ret);
    }

    LOWLATENCYTrackUnmap(hTrack);
    TrackMapSourceReset();

    LLT_UNLOCK();
    return s32Ret;
}

HI_S32 LOWLATENCY_SendData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (pstAOFrame->u32Channels != 2 ||
        pstAOFrame->s32BitPerSample != HI_UNF_BIT_DEPTH_16 ||
        pstAOFrame->u32SampleRate != HI_UNF_SAMPLE_RATE_48K)
    {
        HI_ERR_AO("pstAOFrame Invalid param\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    LLT_LOCK();
    s32Ret =  TRACKMmapWriteFrame(&g_stTrackMapSource.stCb, pstAOFrame);
    LLT_UNLOCK();
    return s32Ret;
}

HI_S32 LOWLATENCY_GetAIPDelayMs(HI_HANDLE hTrack, HI_U32* pDelayMs)
{
    HI_U32 u32BusySize;

    LLT_LOCK();
    u32BusySize = CIRC_BUF_QueryBusy(&g_stTrackMapSource.stCb);
    LLT_UNLOCK();

    *pDelayMs = u32BusySize * 1000 / (HI_UNF_SAMPLE_RATE_48K * 2 * sizeof(HI_U16));
    return HI_SUCCESS;
}

/******************************************************************************/
#define SND_MUTES_FRAMES (10)
#define CIRCLE_BUFFER_POINT (2)

typedef struct
{
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_U8*  pDmaAddr;
    HI_U32* pu32Wptr;
    HI_U32* pu32Rptr;
    HI_U32  u32Size;
    CIRC_BUF_S stCb;
} SND_PORT_USER_ATTR_S;

typedef struct
{
    HI_U32 u32PhyAddr;
    HI_U32 u32MapSize;
    HI_VOID* pMapVirAddr;
    HI_VOID* pVirAddr;
} MAP_ATTR_S;

typedef struct
{
    MAP_ATTR_S stReadMapAttr;
    MAP_ATTR_S stWriteMapAttr;
} CIRCLE_BUFFER_MAP_ATTR_S;

typedef struct
{
    HI_BOOL                  bEnable;
    HI_UNF_SAMPLE_RATE_E     enSampleRate;
    HI_U32                   u32FrmCnt;  // debug frame count
    SND_PORT_USER_ATTR_S     stPortUAttr[HI_UNF_SND_OUTPUTPORT_MAX];
    SND_PORT_KERNEL_ATTR_S   stPortKAttr[HI_UNF_SND_OUTPUTPORT_MAX];
    CIRCLE_BUFFER_MAP_ATTR_S stCircleBufferMapAttr[HI_UNF_SND_OUTPUTPORT_MAX];
    HI_BOOL                bUsed;
} SND_DMA_SOURCE_S;

static SND_DMA_SOURCE_S g_DMASource;

static pthread_mutex_t g_DMAMutex = PTHREAD_MUTEX_INITIALIZER;

#define DMA_LOCK()    (void)pthread_mutex_lock(&g_DMAMutex)
#define DMA_UNLOCK()  (void)pthread_mutex_unlock(&g_DMAMutex)

static HI_S32 DMAMmap(MAP_ATTR_S* pstMapattr)
{
    HI_U32  u32SizeInPage;
    HI_U32  u32PageDiff;
    HI_U32  u32PhyAddrInPage;
    HI_VOID* pMapedAddr = HI_NULL;

    u32PhyAddrInPage = pstMapattr->u32PhyAddr & PAGE_SIZE_MASK;
    u32PageDiff = pstMapattr->u32PhyAddr - u32PhyAddrInPage;
    u32SizeInPage = ( ( 4 + u32PageDiff  - 1 ) & PAGE_SIZE_MASK ) + MEM_PAGE_SIZE;

    pMapedAddr = (HI_VOID*)mmap((HI_VOID*)0, u32SizeInPage, PROT_READ | PROT_WRITE, MAP_SHARED, g_s32AOFd, u32PhyAddrInPage);
    if (MAP_FAILED == pMapedAddr)
    {
        HI_ERR_AO("HIAOMmap mmap failed\n");
        return HI_FAILURE;
    }

    pstMapattr->pMapVirAddr = pMapedAddr;
    pstMapattr->pVirAddr = (HI_VOID*)(pMapedAddr + u32PageDiff);
    pstMapattr->u32MapSize = u32SizeInPage;

    return HI_SUCCESS;
}


static HI_VOID DMAUnmap(MAP_ATTR_S* pstMapattr)
{
    (HI_VOID)munmap(pstMapattr->pMapVirAddr, pstMapattr->u32MapSize);
}


static HI_VOID DMASourceReset(HI_VOID)
{
    HI_U32 u32PortNum = 0;
    memset(&g_DMASource, 0, sizeof(SND_DMA_SOURCE_S));
    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        g_DMASource.stPortUAttr[u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_BUTT;
    }
    g_DMASource.enSampleRate = HI_UNF_SAMPLE_RATE_48K;
}

static HI_S32 DMASetSndSampleRate(HI_UNF_SND_E enSound, HI_UNF_SAMPLE_RATE_E enSampleRate)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_SND_DMASetSampleRate_Param_S stParam;

    stParam.enSound = enSound;
    stParam.enSampleRate = enSampleRate;

    s32Ret = ioctl(g_s32AOFd, CMD_AO_SND_DMASETSAMPLERATE, &stParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("CMD_AO_SND_DMASETSAMPLERATE failed(%#x)\n", s32Ret);
    }

    return s32Ret;
}

static HI_S32 DMACreate(HI_UNF_SND_E enSound, SND_PORT_KERNEL_ATTR_S* pstPortKAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_SND_DMACreate_Param_S stParam;

    stParam.enSound = enSound;

    s32Ret = ioctl(g_s32AOFd, CMD_AO_SND_DMACREATE, &stParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("CMD_AO_SND_DMACREATE failed(%#x)\n", s32Ret);
        return s32Ret;
    }
    DMASourceReset();

    memcpy(pstPortKAttr, stParam.stPortKAttr, sizeof(SND_PORT_KERNEL_ATTR_S) * HI_UNF_SND_OUTPUTPORT_MAX);
    return HI_SUCCESS;
}

static HI_S32 DMADestory(HI_UNF_SND_E enSound)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_SND_DMADestory_Param_S stParam;

    stParam.enSound = enSound;

    s32Ret = ioctl(g_s32AOFd, CMD_AO_SND_DMADESTORY, &stParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("CMD_AO_SND_DMACREATE failed(%#x)\n", s32Ret);
    }
    return s32Ret;
}

static HI_S32 DMAUnmapPort(HI_UNF_SND_E enSound)
{
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;
    SND_PORT_KERNEL_ATTR_S* pstPortKAttr = HI_NULL;
    MAP_ATTR_S* pstReadMapAttr = HI_NULL;
    MAP_ATTR_S* pstWriteMapAttr = HI_NULL;

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        pstPortKAttr = &(g_DMASource.stPortKAttr[u32PortNum]);
        pstReadMapAttr = &(g_DMASource.stCircleBufferMapAttr[u32PortNum].stReadMapAttr);
        pstWriteMapAttr = &(g_DMASource.stCircleBufferMapAttr[u32PortNum].stWriteMapAttr);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            if (HI_NULL != pstPortUAttr->pDmaAddr)
            {
                HI_MPI_MMZ_Unmap(pstPortKAttr->tPhyDma);
            }

            if (HI_NULL != pstPortUAttr->pu32Wptr)
            {
                DMAUnmap(pstWriteMapAttr);
            }

            if (HI_NULL != pstPortUAttr->pu32Rptr)
            {
                DMAUnmap(pstReadMapAttr);
            }
        }
    }

    return HI_SUCCESS;
}

static HI_S32 DMAMmapPort(HI_UNF_SND_E enSound, SND_PORT_KERNEL_ATTR_S* pstPortKAttr, CIRCLE_BUFFER_MAP_ATTR_S* pstCircleBufferMapAttr)
{
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++, pstPortKAttr++, pstCircleBufferMapAttr++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        pstPortUAttr->enOutPort = pstPortKAttr->enOutPort;
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            pstPortUAttr->u32Size = pstPortKAttr->u32Size;
            pstPortUAttr->pDmaAddr = (HI_U8*)HI_MPI_MMZ_Map(pstPortKAttr->tPhyDma, HI_FALSE);

            pstCircleBufferMapAttr->stReadMapAttr.u32PhyAddr = pstPortKAttr->tPhyRptr;
            DMAMmap(&pstCircleBufferMapAttr->stReadMapAttr);
            pstPortUAttr->pu32Rptr = pstCircleBufferMapAttr->stReadMapAttr.pVirAddr;

            pstCircleBufferMapAttr->stWriteMapAttr.u32PhyAddr = pstPortKAttr->tPhyWptr;
            DMAMmap(&pstCircleBufferMapAttr->stWriteMapAttr);
            pstPortUAttr->pu32Wptr = pstCircleBufferMapAttr->stWriteMapAttr.pVirAddr;

            if (HI_NULL == pstPortUAttr->pDmaAddr ||
                HI_NULL == pstPortUAttr->pu32Wptr ||
                HI_NULL == pstPortUAttr->pu32Rptr)
            {
                HI_ERR_AO("enOutPort(%d) mmap error!\n", pstPortKAttr->enOutPort);
                DMAUnmapPort(enSound);
                return HI_FAILURE;
            }
            CIRC_BUF_Init(&pstPortUAttr->stCb,
                          pstPortUAttr->pu32Wptr,
                          pstPortUAttr->pu32Rptr,
                          pstPortUAttr->pDmaAddr,
                          pstPortUAttr->u32Size);
        }
    }

    return HI_SUCCESS;
}

static HI_S32 DMAPrepare(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;;
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            s32Ret |= CIRC_BUF_Write(&pstPortUAttr->stCb, HI_NULL, 0x100);
        }
    }

    return s32Ret;
}

static HI_VOID DMADisable(HI_UNF_SND_E enSound)
{
    g_DMASource.bEnable = HI_FALSE;
}

static HI_S32 DMAEnable(HI_UNF_SND_E enSound, HI_U32 u32SampleRate)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == g_DMASource.bEnable)
    {
        return HI_SUCCESS;
    }

    g_DMASource.enSampleRate = (HI_UNF_SAMPLE_RATE_E)u32SampleRate;

    s32Ret = DMASetSndSampleRate(enSound, g_DMASource.enSampleRate);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMASetSndSampleRate failed(%#x)!\n", s32Ret);
        g_DMASource.enSampleRate = HI_UNF_SAMPLE_RATE_48K;
        return s32Ret;
    }

    DMAPrepare();
    g_DMASource.bEnable = HI_TRUE;

    return HI_SUCCESS;
}

static HI_BOOL PortCheckAllFree(const HI_UNF_AO_FRAMEINFO_S* pstAOFrame, const HI_U32 u32LatencyMs)
{
    HI_U32 u32BusySize = 0;
    HI_U32 u32Latency = 0;
    HI_U32 u32FrameSize = 0;
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;

    u32Latency = u32LatencyMs * pstAOFrame->u32SampleRate * pstAOFrame->u32Channels * sizeof(HI_U16) / 1000;
    u32FrameSize = pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * sizeof(HI_U16);

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            u32BusySize = CIRC_BUF_QueryBusy(&pstPortUAttr->stCb);
            if ((u32BusySize + u32FrameSize) > u32Latency)
            {
                return HI_FALSE;
            }
        }
    }
    return HI_TRUE;
}

static HI_S32 PortWriteFrame(SND_PORT_USER_ATTR_S* pstAttr, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_U32 u32FrameSize = 0, u32WriteSize = 0;

    u32FrameSize = pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * sizeof(HI_U16);

    if (g_DMASource.u32FrmCnt > SND_MUTES_FRAMES)
    {
        u32WriteSize = CIRC_BUF_Write(&pstAttr->stCb, (HI_U8*)pstAOFrame->ps32PcmBuffer, u32FrameSize);
    }
    else
    {
        // mute frames
        u32WriteSize = CIRC_BUF_Write(&pstAttr->stCb, HI_NULL, u32FrameSize);
    }

    return (u32WriteSize == u32FrameSize) ? HI_SUCCESS : HI_FAILURE;
}

HI_S32 SND_DMA_Create(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    DMA_LOCK();

    if (HI_TRUE == g_DMASource.bUsed)
    {
        HI_ERR_AO("SND DMA is busy!\n");
        DMA_UNLOCK();
        return HI_FAILURE;
    }

    s32Ret = DMACreate(HI_UNF_SND_0, &g_DMASource.stPortKAttr[0]);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMACreate failed(%#x)!\n", s32Ret);
        DMA_UNLOCK();
        return s32Ret;
    }

    s32Ret = DMAMmapPort(HI_UNF_SND_0, &g_DMASource.stPortKAttr[0], &g_DMASource.stCircleBufferMapAttr[0]);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMAMmapPort failed(%#x)!\n", s32Ret);
        DMA_UNLOCK();
        return s32Ret;
    }

    g_DMASource.bUsed = HI_TRUE;

    DMA_UNLOCK();
    return s32Ret;
}

HI_S32 SND_DMA_Destroy(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    DMA_LOCK();

    s32Ret = DMAUnmapPort(HI_UNF_SND_0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMAUnmapPort failed(%#x)!\n", s32Ret);
        DMA_UNLOCK();
        return s32Ret;
    }

    s32Ret = DMADestory(HI_UNF_SND_0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMADestory failed(%#x)!\n", s32Ret);
    }

    DMADisable(HI_UNF_SND_0);
    DMASourceReset();

    DMA_UNLOCK();
    return s32Ret;
}

HI_S32 SND_DMA_SendData(const HI_UNF_AO_FRAMEINFO_S* pstAOFrame, const HI_U32 u32LatencyMs)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;

    if (HI_UNF_I2S_CHNUM_2  != pstAOFrame->u32Channels ||
        HI_UNF_BIT_DEPTH_16 != pstAOFrame->s32BitPerSample)
    {
        HI_ERR_AO("DMA only support 2ch 16bit pcm stream!\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    if (pstAOFrame->u32SampleRate != HI_UNF_SAMPLE_RATE_48K &&
        pstAOFrame->u32SampleRate != HI_UNF_SAMPLE_RATE_44K)
    {
        HI_ERR_AO("DMA support 44.1k and 48k pcm stream!\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    if (u32LatencyMs > 40 || u32LatencyMs < 10)
    {
        HI_ERR_AO("Invalid DMA LatencyMs!\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    DMA_LOCK();
    s32Ret = DMAEnable(HI_UNF_SND_0, pstAOFrame->u32SampleRate);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DMAEnable failed(%#x)!\n", s32Ret);
        DMA_UNLOCK();
        return s32Ret;
    }

    if (HI_FALSE == PortCheckAllFree(pstAOFrame, u32LatencyMs))
    {
        DMA_UNLOCK();
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            s32Ret = PortWriteFrame(pstPortUAttr, pstAOFrame);
        }
    }
    g_DMASource.u32FrmCnt++;

    DMA_UNLOCK();
    return s32Ret;
}

HI_S32 SND_DMA_GetDelayMs(HI_U32* pu32DelayMs)
{
    HI_U32 u32BusySize = 0;
    HI_U32 u32FrameSize = 0;
    HI_U32 u32PortNum = 0;
    SND_PORT_USER_ATTR_S* pstPortUAttr = HI_NULL;

    DMA_LOCK();

    u32FrameSize = ((HI_U32)(g_DMASource.enSampleRate)) * 2 * sizeof(HI_U16);
    if (0 == u32FrameSize)
    {
        *pu32DelayMs = 0;
        DMA_UNLOCK();
        return HI_SUCCESS;
    }

    for (u32PortNum = 0; u32PortNum < HI_UNF_SND_OUTPUTPORT_MAX; u32PortNum++)
    {
        pstPortUAttr = &(g_DMASource.stPortUAttr[u32PortNum]);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != pstPortUAttr->enOutPort)
        {
            u32BusySize = CIRC_BUF_QueryBusy(&pstPortUAttr->stCb);
            break;
        }
    }

    *pu32DelayMs = u32BusySize * 1000 / u32FrameSize;

    DMA_UNLOCK();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
