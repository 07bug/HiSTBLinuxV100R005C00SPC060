/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : mpi_aenc_core.c
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <dlfcn.h>
#include <dirent.h>

#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_module.h"
#include "hi_mpi_mem.h"
#include "hi_drv_struct.h"

#include "hi_audio_codec.h"
#include "hi_drv_ao.h"
#include "hi_mpi_ao.h"
#include "hi_unf_sound.h"
#include "hi_drv_aenc.h"
#include "hi_common.h"
#include "mpi_adec_assembly.h"
#include "mpi_mmz.h"

#ifdef HI_AENC_AI_SUPPORT
#include "hi_mpi_ai.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define PTS_SUPPORT
#define ENA_AENC_AUTOSRC
#define AENC_MAX_STORED_PTS_NUM 256
#define AENC_SYS_SLEEP_TIME 10   //for adec pull thread

typedef struct
{
    HI_U32 u32PtsMs;        /* Play Time Stamp */
    HI_U8* pu8BegPtr;      /* Stream start address of PTS */
    HI_U8* pu8EndPtr;      /* Stream end   address of PTS */
} AENC_PTS;

typedef struct
{
    HI_U32   u32LastPtsMs;
    HI_U32   ulPTSreadIdx;     /* PTS buffer read  ptr */
    HI_U32   ulPTSwriteIdx;    /* PTS buffer write ptr */
    AENC_PTS tPTSArry[AENC_MAX_STORED_PTS_NUM];
} AENC_PTS_QUE_S;

typedef struct
{
    HI_U8*       pRealAddr;
    HI_U8*       pStart;
    HI_U8*       pEnd;
    HI_U8*       pWrite;
    HI_U8*       pRead;
    HI_MMZ_BUF_S sMMzBuf;
} AENC_PCM_BUFFER_S;

typedef struct
{
    HI_BOOL      bFlag;       /* Buffer Flag */
    HI_U32       u32PtsMs;    /* Play Time Stamp */
    HI_U8*       pu8Data;     /* Output Buffer */
    HI_U32       u32Bytes;
} AENC_OUTPUTBUF_S;

typedef struct
{
    HI_U32           u32FrameNum;
    HI_U32           u32ReadIdx;
    HI_U32           u32WriteIdx;
    HI_U8*           pBaseAddr;
    HI_U32           u32FrameSize;
    HI_MMZ_BUF_S     sMMzBuf;
    AENC_OUTPUTBUF_S outBuf[AENC_MAX_STORED_PTS_NUM];
} AENC_Stream_OutBuf_S;

typedef struct
{
    HI_HAENCODE_OPENPARAM_S              stOpenParam;
    HI_VOID*                             pAudPrivDataBak; /* backup private data */
    HI_U32                               u32AudPrivDataBakDize;
} AENC_ENCODER_INFO_S;

typedef struct
{
    HI_BOOL              beAssigned;
    HI_BOOL              bStart;
    HI_U32               u32CodecID;
    HI_U32               u32InBufSize;                     /* Input buffer size */
    HI_U32               u32OutBufNum;                     /* output frame number */
    HI_U32               u32ChID;
    HI_VOID*             hHaEntry;
    HI_VOID*             hEncoder;
    HI_S32               AencDevFd;

    HI_BOOL bAutoSRC;

    HI_U32*              pu32WorkBuf;
    HI_U32               u32WorkBufIdx;

    /* keep encoder open param */
    HI_U32  u32DesiredOutChannels;
    HI_BOOL bInterleaved;
    HI_U32  u32BitPerSample;
    HI_U32  u32DesiredSampleRate;
    HI_U32  u32SamplePerFrame;
    AENC_ENCODER_INFO_S  stEncoderInfo;

    AENC_PTS_QUE_S       PTSQue;
    AENC_PCM_BUFFER_S    sInPcmBuf;
    AENC_Stream_OutBuf_S sOutStreamBuf;

    AENC_INFO_ATTACH_S stAttach;

    AENC_PROC_ITEM_S*    pstAencInfo;
    HI_U32               u32PhyAddr;
    HI_BOOL              AencThreadRun;
    pthread_t            AencThreadInst;
} AENC_CHAN_S;

static AENC_CHAN_S* g_pstAencChan[AENC_INSTANCE_MAXNUM];
static HI_U32 g_u32AencInitCnt = 0;
static const HI_CHAR g_acAencDevName[] = "/dev/" UMAP_DEVNAME_AENC;
static HI_HA_ENCODE_S* g_hFirstCodec = HI_NULL;

static pthread_mutex_t g_AencMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t g_AencChanMutex[AENC_INSTANCE_MAXNUM] = {[0 ... (AENC_INSTANCE_MAXNUM - 1)] = PTHREAD_MUTEX_INITIALIZER};

#ifdef  ENA_AENC_AUTOSRC
#include "mpi_resample_linear.h"
static SRC_Linear g_sAencLinearSRC[AENC_INSTANCE_MAXNUM];
#endif

#define AENC_LOCK()    (void)pthread_mutex_lock(&g_AencMutex)
#define AENC_UNLOCK()  (void)pthread_mutex_unlock(&g_AencMutex)
#define AENC_CHAN_LOCK(AencId)    (void)pthread_mutex_lock(&g_AencChanMutex[AencId])
#define AENC_CHAN_UNLOCK(AencId)  (void)pthread_mutex_unlock(&g_AencChanMutex[AencId])

#define AENC_CHAN_TRY_LOCK(AencId) \
    do \
    { \
        if (0 != pthread_mutex_trylock(&g_AencChanMutex[AencId])) \
        { \
            return HI_FAILURE; \
        } \
    } while (0)

//#define AENC_MMZ_BUF_SUPPORT
#ifdef AENC_MMZ_BUF_SUPPORT
static HI_CHAR g_szAencInBuf_MMzName[AENC_INSTANCE_MAXNUM][MAX_BUFFER_NAME_SIZE] =
{
    "AENCInBuf0",
    "AENCInBuf1",
    "AENCInBuf2"
};

static HI_CHAR g_szAencOutBuf_MMzName[AENC_INSTANCE_MAXNUM][MAX_BUFFER_NAME_SIZE] =
{
    "AENCOutBuf0",
    "AENCOutBuf1",
    "AENCOutBuf2"
};
#endif

static HI_VOID* AENC_Thread(HI_VOID* arg);

static HI_S32 AENCCreateWorkBuf(AENC_CHAN_S* pstAencChan)
{
    HI_U32 AencWorkingBuffferSize = 0;
    AencWorkingBuffferSize = AENC_WORK_BUFFER_NUM * sizeof(HI_U32) * (AENC_MAX_POSTPROCESS_FRAME + 1);
    pstAencChan->pu32WorkBuf = (HI_U32*)HI_MALLOC(HI_ID_AENC, AencWorkingBuffferSize);
    if (HI_NULL == pstAencChan->pu32WorkBuf)
    {
        HI_ERR_AENC("malloc AENC WorkingBufffer fail\n");
        return HI_FAILURE;
    }

    memset(pstAencChan->pu32WorkBuf, 0, AencWorkingBuffferSize);
    pstAencChan->u32WorkBufIdx = 0;

    return HI_SUCCESS;
}

static HI_VOID AENCDestroyWorkBuf(AENC_CHAN_S* pstAencChan)
{
    if (HI_NULL != pstAencChan->pu32WorkBuf)
    {
        HI_FREE(HI_ID_AENC, (HI_VOID*)pstAencChan->pu32WorkBuf);
        pstAencChan->pu32WorkBuf = HI_NULL;
    }
    pstAencChan->u32WorkBufIdx = 0;
}

static HI_U32* AENCGetWorkBuf(AENC_CHAN_S* pstAencChan)
{
    HI_U32* pu32WorkBuf;

    if (pstAencChan->u32WorkBufIdx >= AENC_WORK_BUFFER_NUM)
    {
        pstAencChan->u32WorkBufIdx = 0;
    }

    pu32WorkBuf = pstAencChan->pu32WorkBuf + pstAencChan->u32WorkBufIdx * (AENC_MAX_POSTPROCESS_FRAME + 1);
    pstAencChan->u32WorkBufIdx++;

    return pu32WorkBuf;
}

#ifdef ENA_AENC_AUTOSRC
/* use LinearSRC to do simple SRC for AENC */
static HI_VOID LinearSRCProcess(HI_UNF_AO_FRAMEINFO_S* pstAOFrame, SRC_Linear* pInst, HI_U32 u32DesiredSampleRate, AENC_CHAN_S* pstAencChan)
{
    HI_BOOL doSRC = HI_FALSE;

    /* LinearSRC place after resampler, inrate == outrate, just do slowly samplerate adjust */
    LinearSRC_UpdateChange(pInst, (HI_S32)pstAOFrame->u32SampleRate, (HI_S32)u32DesiredSampleRate,
                           pstAOFrame->s32BitPerSample,
                           (HI_S32)pstAOFrame->u32Channels);

    doSRC = LinearSRC_CheckDoSRC(pInst);
    if (HI_TRUE == doSRC)
    {
        HI_S32 uPcmSamplesPerFrame = (HI_S32)pstAOFrame->u32PcmSamplesPerFrame;
        HI_S32* ps32LinearSRC_Out = (HI_S32*)AENCGetWorkBuf(pstAencChan);
        HI_S32 outsamps;
        outsamps = LinearSRC_ProcessFrame(pInst, (HI_S32*)(pstAOFrame->ps32PcmBuffer), ps32LinearSRC_Out,
                                          (HI_S32)uPcmSamplesPerFrame);

        /* after LinearSRC, update info */
        pstAOFrame->ps32PcmBuffer = (HI_S32*)(ps32LinearSRC_Out);
        pstAOFrame->u32PcmSamplesPerFrame = (HI_U32)outsamps;
    }
}
#endif

static HI_HA_ENCODE_S* AENCFindHaEncoder(HI_U32 enCodecID)
{
    HI_HA_ENCODE_S* p;

    p = g_hFirstCodec;
    while (p)
    {
        if ((HA_GET_ID(p->enCodecID) == HA_GET_ID(enCodecID)))
        {
            return p;
        }

        p = p->pstNext;
    }

    HI_ERR_AENC("AENCFindHaEncoder Encoder(ID=0x%x) Fail\n", enCodecID);

    return HI_NULL;
}

static HI_S32 AENCCheckHaEncoder(const HI_HA_ENCODE_S* pEntry)
{
    CHECK_AENC_NULL_PTR(pEntry->EncodeInit);
    CHECK_AENC_NULL_PTR(pEntry->EncodeDeInit);
    CHECK_AENC_NULL_PTR(pEntry->EncodeSetConfig);
    CHECK_AENC_NULL_PTR(pEntry->EncodeGetMaxBitsOutSize);
    CHECK_AENC_NULL_PTR(pEntry->EncodeFrame);

    return HI_SUCCESS;
}

static HI_S32 AENCRegisterHaEncoder(const HI_CHAR* pszDecoderDllName)
{
    HI_HA_ENCODE_S** p;
    HI_VOID* pDllModule;
    HI_HA_ENCODE_S* pEntry;

    pDllModule = dlopen(pszDecoderDllName, RTLD_LAZY | RTLD_GLOBAL);
    if (pDllModule == NULL)
    {
        HI_ERR_AENC("  ****** AENCRegisterHaEncoder %s Failed because dlopen fail %s\n\n", pszDecoderDllName, dlerror());
        return HI_FAILURE;
    }

    pEntry = dlsym(pDllModule, "ha_audio_encode_entry");
    if (pEntry == NULL)
    {
        HI_ERR_AENC("  %s Failed because dlsym fail %s\n\n", pszDecoderDllName, dlerror());
        dlclose(pDllModule);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != AENCCheckHaEncoder(pEntry))
    {
        HI_ERR_AENC(" Register %s Failed \n", pszDecoderDllName);
        dlclose(pDllModule);
        return HI_FAILURE;
    }

    p = &g_hFirstCodec;
    while (*p != NULL)
    {
        if (HA_GET_ID((*p)->enCodecID) == HA_GET_ID(pEntry->enCodecID))
        {
            HI_WARN_AENC(" Fail:Encoder(CodecID=0x%x) had been Registered \n\n",
                         pEntry->enCodecID);
            dlclose(pDllModule);
            return HI_SUCCESS;
        }

        p = &(*p)->pstNext;
    }

    HI_INFO_AENC("##### Register %s Encoder Success #####\n\n", (HI_CHAR*)(pEntry->szName));

    *p = pEntry;
    (*p)->pstNext = HI_NULL;
    (*p)->pDllModule = pDllModule;
    return HI_SUCCESS;
}

static HI_VOID AENC_DbgCountTryEncodeCount(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    AENC_PROC_ITEM_S* pstAencInfo = HI_NULL_PTR;

    pstAencChan = g_pstAencChan[hAenc];
    pstAencInfo = pstAencChan->pstAencInfo;
    pstAencInfo->u32DbgTryEncodeCount++;
}

static HI_VOID AENC_DbgCountTryReceiveStream(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    AENC_PROC_ITEM_S* pstAencInfo = HI_NULL_PTR;

    pstAencChan = g_pstAencChan[hAenc];
    pstAencInfo = pstAencChan->pstAencInfo;
    pstAencInfo->u32DbgReceiveStreamCount_Try++;
}

static HI_VOID AENC_DbgCountReceiveStream(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    AENC_PROC_ITEM_S* pstAencInfo = HI_NULL_PTR;

    pstAencChan = g_pstAencChan[hAenc];
    pstAencInfo = pstAencChan->pstAencInfo;
    pstAencInfo->u32DbgReceiveStreamCount++;
}

static HI_VOID AENC_DbgCountTryReleaseStream(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    AENC_PROC_ITEM_S* pstAencInfo = HI_NULL_PTR;

    pstAencChan = g_pstAencChan[hAenc];
    pstAencInfo = pstAencChan->pstAencInfo;
    pstAencInfo->u32DbgReleaseStreamCount_Try++;
}

static HI_VOID AENC_DbgCountReleaseStream(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    AENC_PROC_ITEM_S* pstAencInfo = HI_NULL_PTR;

    pstAencChan = g_pstAencChan[hAenc];
    pstAencInfo = pstAencChan->pstAencInfo;
    pstAencInfo->u32DbgReleaseStreamCount++;
}

static HI_VOID AENC_DbgCountTrySendBuf(AENC_CHAN_S* pstAencChan)
{
    pstAencChan->pstAencInfo->u32DbgSendBufCount_Try++;
}

static HI_VOID AENC_DbgCountSendBuf(AENC_CHAN_S* pstAencChan)
{
    pstAencChan->pstAencInfo->u32DbgSendBufCount++;
}

static HI_S32 AENCInitInBuf(AENC_CHAN_S* pstAencChan, HI_U32 u32Size, HI_U32 u32FrameSize)
{
    HI_U32 u32RealSize;
    AENC_PCM_BUFFER_S* pstInBuf = &(pstAencChan->sInPcmBuf);

    if (0 == u32FrameSize)
    {
        HI_ERR_AENC(" invalid frame size(0)\n");
        return HI_FAILURE;
    }

    if ((u32Size < AENC_MIN_INPUT_BUFFER_SIZE) || (u32Size > AENC_MAX_INPUT_BUFFER_SIZE))
    {
        HI_ERR_AENC(" invalid input buffer size(%d) minsize(%d) maxsize(%d)!\n", u32Size, AENC_MIN_INPUT_BUFFER_SIZE,
                    AENC_MAX_INPUT_BUFFER_SIZE);
        return HI_FAILURE;
    }

    /* integral multiple to deal with buffer loop */
    if (u32Size > u32FrameSize)
    {
        u32RealSize = u32FrameSize * (u32Size / u32FrameSize);
    }
    else
    {
        u32RealSize = u32FrameSize * 16;
    }

#ifdef AENC_MMZ_BUF_SUPPORT
    strncpy(pstInBuf->sMMzBuf.bufname, g_szAencInBuf_MMzName[pstAencChan->u32ChID], sizeof(g_szAencInBuf_MMzName[pstAencChan->u32ChID]));
    pstInBuf->sMMzBuf.bufsize = u32RealSize;
    pstInBuf->sMMzBuf.phyaddr = (HI_U32)HI_MPI_MMZ_New(pstInBuf->sMMzBuf.bufsize, 0x32, HI_NULL,
                                pstInBuf->sMMzBuf.bufname);

    if (pstInBuf->sMMzBuf.phyaddr)
    {
        pstInBuf->sMMzBuf.user_viraddr = (HI_U8*)HI_MPI_MMZ_Map(pstInBuf->sMMzBuf.phyaddr, HI_FALSE);
        pstInBuf->pRealAddr = pstInBuf->sMMzBuf.user_viraddr;
    }
    else
    {
        pstInBuf->pRealAddr = HI_NULL_PTR;
    }

#else
    pstInBuf->pRealAddr = (HI_U8*)HI_MALLOC(HI_ID_AENC, u32RealSize);
#endif
    if (HI_NULL_PTR == pstInBuf->pRealAddr)
    {
        HI_ERR_AENC("aenc inbuf alloc error\n");
        return HI_FAILURE;
    }

    memset(pstInBuf->pRealAddr, 0, u32RealSize);

    pstInBuf->pStart = pstInBuf->pRealAddr;
    pstInBuf->pEnd   = pstInBuf->pStart + u32RealSize;
    pstInBuf->pWrite = pstInBuf->pStart;
    pstInBuf->pRead  = pstInBuf->pStart;

    pstAencChan->u32InBufSize = u32RealSize;

    return HI_SUCCESS;
}

static HI_VOID AENCResetInBuf(AENC_PCM_BUFFER_S* pstInBuf)
{
    pstInBuf->pWrite = pstInBuf->pStart;
    pstInBuf->pRead = pstInBuf->pStart;
}

static HI_VOID AENCDeInitInBuf(AENC_CHAN_S* pstAencChan)
{
    AENC_PCM_BUFFER_S* pstInBuf = &pstAencChan->sInPcmBuf;

    if (HI_NULL_PTR != pstInBuf->pRealAddr)
    {
#ifdef AENC_MMZ_BUF_SUPPORT
        (HI_VOID)HI_MPI_MMZ_Unmap(pstInBuf->sMMzBuf.phyaddr);
        (HI_VOID)HI_MPI_MMZ_Delete(pstInBuf->sMMzBuf.phyaddr);
#else
        HI_FREE(HI_ID_AENC, pstInBuf->pRealAddr);
#endif
        pstInBuf->pRealAddr = HI_NULL_PTR;
        pstInBuf->pStart = HI_NULL_PTR;
        pstInBuf->pEnd   = HI_NULL_PTR;
        pstInBuf->pWrite = HI_NULL_PTR;
        pstInBuf->pRead  = HI_NULL_PTR;
    }
}

static HI_VOID AENCAllCHNLock(HI_VOID)
{
    HI_U32 i;

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        AENC_CHAN_LOCK(i);
    }
}

static HI_VOID AENCAllCHNUnLock(HI_VOID)
{
    HI_U32 i;

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        AENC_CHAN_UNLOCK(i);
    }
}

static HI_S32 AENCInitOutBuf(AENC_CHAN_S* pstAencChan, HI_U32 u32BitsMaxFrameSize, HI_U32 u32FrameNum)
{
    HI_U32 i;
    HI_U8* pBuf;
    AENC_Stream_OutBuf_S*  pstOutBuf = &pstAencChan->sOutStreamBuf;

    if (u32FrameNum > AENC_MAX_STORED_PTS_NUM)
    {
        HI_ERR_AENC(" u32FrameNum(%d) exceed maxnum(%d)\n", u32FrameNum, AENC_MAX_STORED_PTS_NUM);
        return HI_FAILURE;
    }

#ifdef AENC_MMZ_BUF_SUPPORT
    strncpy(pstOutBuf->sMMzBuf.bufname, g_szAencOutBuf_MMzName[u32ChID], sizeof(g_szAencOutBuf_MMzName[u32ChID]));
    pstOutBuf->sMMzBuf.bufsize = (u32FrameNum * u32BitsMaxFrameSize) * sizeof(HI_U8);
    pstOutBuf->sMMzBuf.phyaddr = (HI_U32)HI_MPI_MMZ_New(pstOutBuf->sMMzBuf.bufsize, 0x32, HI_NULL,
                                 pstOutBuf->sMMzBuf.bufname);
    if (pstOutBuf->sMMzBuf.phyaddr)
    {
        pstOutBuf->sMMzBuf.user_viraddr = (HI_U8*)HI_MPI_MMZ_Map(pstOutBuf->sMMzBuf.phyaddr, HI_FALSE);
        pBuf = pstOutBuf->sMMzBuf.user_viraddr;
    }
    else
    {
        pBuf = HI_NULL_PTR;
    }

#else
    pBuf = (HI_U8*)HI_MALLOC(HI_ID_AENC, u32FrameNum * u32BitsMaxFrameSize * sizeof(HI_U8));
#endif
    if (HI_NULL_PTR == pBuf)
    {
        HI_ERR_AENC("OutBuf malloc error\n");
        return HI_FAILURE;
    }

    memset(pBuf, 0, u32FrameNum * u32BitsMaxFrameSize * sizeof(HI_U8));

    // Assigning output buffer
    for (i = 0; i < u32FrameNum; i++)
    {
        pstOutBuf->outBuf[i].pu8Data = pBuf + i * u32BitsMaxFrameSize;
        pstOutBuf->outBuf[i].bFlag = HI_FALSE;
    }

    // Reset output buffer pointer
    pstOutBuf->u32FrameNum  = u32FrameNum;
    pstOutBuf->u32FrameSize = u32BitsMaxFrameSize;
    pstOutBuf->pBaseAddr   = pBuf;
    pstOutBuf->u32WriteIdx = 0;
    pstOutBuf->u32ReadIdx  = 0;

    return HI_SUCCESS;
}

static HI_VOID AENCResetOutBuf(AENC_Stream_OutBuf_S* pstOutBuf)
{
    HI_U32 i;
    HI_U8* pBuf;

    if (HI_NULL_PTR == pstOutBuf)
    {
        return;
    }

    // Assigning output buffer
    pBuf = pstOutBuf->pBaseAddr;
    for (i = 0; i < pstOutBuf->u32FrameNum; i++)
    {
        pstOutBuf->outBuf[i].pu8Data = pBuf + i * pstOutBuf->u32FrameSize;
        pstOutBuf->outBuf[i].bFlag = HI_FALSE;
    }

    // Reset output buffer pointer
    pstOutBuf->u32ReadIdx  = 0;
    pstOutBuf->u32WriteIdx = 0;
}

static HI_VOID AENCDeInitOutBuf(AENC_CHAN_S* pstAencChan)
{
    AENC_Stream_OutBuf_S* pstOutBuf = &pstAencChan->sOutStreamBuf;

    if (HI_NULL_PTR != pstOutBuf->pBaseAddr)
    {
        AENCResetOutBuf(pstOutBuf);
#ifdef AENC_MMZ_BUF_SUPPORT
        (HI_VOID)HI_MPI_MMZ_Unmap(pstOutBuf->sMMzBuf.phyaddr);
        (HI_VOID)HI_MPI_MMZ_Delete(pstOutBuf->sMMzBuf.phyaddr);
#else
        HI_FREE(HI_ID_AENC, pstOutBuf->pBaseAddr);
#endif
        pstOutBuf->pBaseAddr = HI_NULL_PTR;
    }
}

static HI_S32 AENCGetOutBufIdleUnit(AENC_Stream_OutBuf_S*  pstOutBuf, AENC_OUTPUTBUF_S** pstOutBufUnit)
{
    if (HI_FALSE == (pstOutBuf->outBuf[pstOutBuf->u32WriteIdx].bFlag))
    {
        *pstOutBufUnit = &(pstOutBuf->outBuf[pstOutBuf->u32WriteIdx]);
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

static HI_S32 AENCReceiveOutBufUnit(AENC_Stream_OutBuf_S* pstOutBuf, AENC_OUTPUTBUF_S** pstOutBufUnit)
{
    if (HI_TRUE == (pstOutBuf->outBuf[pstOutBuf->u32ReadIdx].bFlag))
    {
        *pstOutBufUnit = &(pstOutBuf->outBuf[pstOutBuf->u32ReadIdx]);
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

static HI_S32 AENCReleaseCurrentOutBufUnit(AENC_Stream_OutBuf_S* pstOutBuf, const AENC_STREAM_S* pstStream)
{
    AENC_OUTPUTBUF_S* pstOutBufUnit;

    pstOutBufUnit = &(pstOutBuf->outBuf[pstOutBuf->u32ReadIdx]);
    if (pstStream->pu8Data == pstOutBufUnit->pu8Data)
    {

        if (HI_TRUE == (pstOutBuf->outBuf[pstOutBuf->u32ReadIdx].bFlag))
        {
            pstOutBuf->outBuf[pstOutBuf->u32ReadIdx].bFlag = HI_FALSE;
            pstOutBuf->u32ReadIdx += 1;
            if (pstOutBuf->u32ReadIdx == pstOutBuf->u32FrameNum)
            {
                pstOutBuf->u32ReadIdx = 0;
            }

            return HI_SUCCESS;
        }
        else
        {
            HI_ERR_AENC("invalid outBuf->bFlag, shuold be HI_TRUE \n ");
            return HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_AENC("invalid pstStream->pu8Data(0x%x), pstOutBufUnit->pu8Data(0x%x)\n ", pstStream->pu8Data,
                    pstOutBufUnit->pu8Data);
        return HI_ERR_AENC_OUT_BUF_BAD;
    }
}

static HI_VOID AENCNextOutBufUnit(AENC_Stream_OutBuf_S* pstOutBuf)
{
    pstOutBuf->u32WriteIdx += 1;
    if (pstOutBuf->u32WriteIdx == pstOutBuf->u32FrameNum)
    {
        pstOutBuf->u32WriteIdx = 0;
    }
}

static HI_VOID AENCResetPTSQue(AENC_PTS_QUE_S* pstPTSQue)
{
    if (!pstPTSQue)
    {
        return;
    }

    memset(pstPTSQue->tPTSArry, 0, sizeof(AENC_PTS) * AENC_MAX_STORED_PTS_NUM);
    pstPTSQue->ulPTSreadIdx  = 0;
    pstPTSQue->ulPTSwriteIdx = 0;
    pstPTSQue->u32LastPtsMs = HI_INVALID_PTS;
}

/*
 * AENC PTS use Read and Write Position to manage PTS Que, AENC use  Read and Write Poniter !
 */
static HI_U32 AENCFindPTS(AENC_PTS_QUE_S* pstPTSQue, HI_U8* pu8StartPtr, HI_U32 u32PcmSamplesPerFrame,
                          HI_U32 u32PcmSampleRate)
{
    HI_U32 u32PtsMs;
    HI_U32 Pos, FoundPtsPos = (HI_U32) - 1;
    HI_U32 rdPos;
    HI_U32 wtPos;
    AENC_PTS* ptPTS = HI_NULL;

    rdPos = (HI_U32)pstPTSQue->ulPTSreadIdx;
    wtPos = (HI_U32)pstPTSQue->ulPTSwriteIdx;
    ptPTS = pstPTSQue->tPTSArry;

    for (Pos = rdPos; Pos != wtPos;  Pos = (Pos + 1) % AENC_MAX_STORED_PTS_NUM)
    {
        if (ptPTS[Pos].pu8BegPtr < ptPTS[Pos].pu8EndPtr)
        {
            if ((ptPTS[Pos].pu8BegPtr <= pu8StartPtr) && (ptPTS[Pos].pu8EndPtr >= pu8StartPtr))
            {
                FoundPtsPos = ptPTS[Pos].u32PtsMs;
                break;
            }
        }
        else
        {
            if ((ptPTS[Pos].pu8BegPtr <= pu8StartPtr) || (ptPTS[Pos].pu8EndPtr >= pu8StartPtr))
            {
                FoundPtsPos = ptPTS[Pos].u32PtsMs;
                break;
            }
        }
    }

    if (((HI_U32) - 1) == FoundPtsPos)
    {
        /*can not find a valid PTS*/
        if (HI_INVALID_PTS != pstPTSQue->u32LastPtsMs)
        {
            HI_U32 u32Delta;
            u32Delta = (u32PcmSamplesPerFrame * 1000) / u32PcmSampleRate;
            u32PtsMs = pstPTSQue->u32LastPtsMs + u32Delta;
            if (HI_INVALID_PTS == u32PtsMs)
            {
                u32PtsMs = 0;
            }
        }
        else
        {
            u32PtsMs = HI_INVALID_PTS;   /* if the PTS of first Frame isnot valid, dont insert the PTS*/
        }
        if (Pos != wtPos)
        {
            /* Found a invalid PTS */
            pstPTSQue->ulPTSreadIdx = (HI_U32)Pos;
        }
    }
    else
    {
        /* Found a valid PTS */
        u32PtsMs = FoundPtsPos;
        ptPTS[Pos].u32PtsMs = HI_INVALID_PTS;
        pstPTSQue->ulPTSreadIdx = (HI_U32)Pos;
    }

    pstPTSQue->u32LastPtsMs = u32PtsMs;
    return u32PtsMs;
}

static HI_VOID AENCStorePTS(AENC_CHAN_S* pstAencChan, HI_U8* pu8Write, HI_U32 u32PtsMs, HI_U32 u32Size)
{
    AENC_PTS_QUE_S* pstPTSQue = &pstAencChan->PTSQue;
    AENC_PTS* ptPTSArray = pstPTSQue->tPTSArry;
    HI_U8* pu8CalcEndPtr;

    /* make sure there are space to store */
    if ((pstPTSQue->ulPTSwriteIdx + 1) % AENC_MAX_STORED_PTS_NUM != pstPTSQue->ulPTSreadIdx)
    {
        if ((pu8Write - pstAencChan->sInPcmBuf.pRealAddr + u32Size) < pstAencChan->u32InBufSize)
        {
            pu8CalcEndPtr = pu8Write + u32Size;
        }
        else
        {
            pu8CalcEndPtr = pu8Write + u32Size - pstAencChan->u32InBufSize;
        }

        ptPTSArray[pstPTSQue->ulPTSwriteIdx].u32PtsMs  = u32PtsMs;
        ptPTSArray[pstPTSQue->ulPTSwriteIdx].pu8BegPtr = pu8Write;
        ptPTSArray[pstPTSQue->ulPTSwriteIdx].pu8EndPtr = pu8CalcEndPtr;
        pstPTSQue->ulPTSwriteIdx = (pstPTSQue->ulPTSwriteIdx + 1) % AENC_MAX_STORED_PTS_NUM;
    }
    else
    {
        HI_WARN_AENC("Not enough PTS buffer, discard current PTS(%d)\n", u32PtsMs);
    }
}

static HI_S32 AENCCreateEncoder(AENC_CHAN_S* pstAencChan, AENC_ATTR_S* pstAencAttr)
{
    HI_HA_ENCODE_S* hHaEntry;
    HI_VOID* hEncoder = HI_NULL;
    HI_S32 nRet;
    HI_U32 u32FrameSize, u32BitsMaxFrameSize;
    HI_HAENCODE_OPENPARAM_S* pstOpenParms;
    HI_HAENCODE_OPENPARAM_S* pstChnOpenParms;
    AENC_ENCODER_INFO_S* pstEncoderInfo;

    hHaEntry = AENCFindHaEncoder(pstAencAttr->u32CodecID);
    if (HI_NULL == hHaEntry)
    {
        HI_ERR_AENC("AENCFindHaEncoder fail u32CodecID(0x%x)!\n", pstAencAttr->u32CodecID);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    pstOpenParms = (HI_HAENCODE_OPENPARAM_S*)(&(pstAencAttr->sOpenParam));
    pstEncoderInfo = &pstAencChan->stEncoderInfo;
    pstChnOpenParms = &pstEncoderInfo->stOpenParam;

    memcpy(pstChnOpenParms, &pstAencAttr->sOpenParam, sizeof(HI_HAENCODE_OPENPARAM_S));

    if ((HI_NULL != pstOpenParms->pCodecPrivateData) && (0 != pstOpenParms->u32CodecPrivateDataSize))
    {
        HI_U32 u32AudPrivDataDize;

        u32AudPrivDataDize = pstOpenParms->u32CodecPrivateDataSize;

        if ((HI_NULL != pstEncoderInfo->pAudPrivDataBak) && (pstEncoderInfo->u32AudPrivDataBakDize >= u32AudPrivDataDize))
        {
            /* only update u32AudPrivDataDize, avoid HI_MALLOC again */
            pstEncoderInfo->u32AudPrivDataBakDize = u32AudPrivDataDize;
        }
        else
        {
            HI_VOID* pSrcAudPrivData;
            if (HI_NULL != pstEncoderInfo->pAudPrivDataBak)
            {
                HI_FREE(HI_ID_AENC, pstEncoderInfo->pAudPrivDataBak);
                pstEncoderInfo->pAudPrivDataBak = HI_NULL_PTR;
            }

            /*HI_MALLOC privattr structure*/
            pSrcAudPrivData = (HI_VOID*)HI_MALLOC(HI_ID_AENC, u32AudPrivDataDize);
            if (HI_NULL == pSrcAudPrivData)
            {
                HI_ERR_AENC("  HI_MALLOC AudPrivData fail \n");
                return HI_FAILURE;
            }

            memset(pSrcAudPrivData, 0, u32AudPrivDataDize);

            pstEncoderInfo->pAudPrivDataBak = pSrcAudPrivData;
            pstEncoderInfo->u32AudPrivDataBakDize = u32AudPrivDataDize;
        }

        memcpy(pstEncoderInfo->pAudPrivDataBak, (const HI_VOID*)(pstOpenParms->pCodecPrivateData), u32AudPrivDataDize);

        /* use pAudPrivDataBak mem */
        pstChnOpenParms->pCodecPrivateData = pstEncoderInfo->pAudPrivDataBak;
        pstChnOpenParms->u32CodecPrivateDataSize = pstEncoderInfo->u32AudPrivDataBakDize;
    }

    else
    {
        HI_WARN_AENC("Invalid Encodec private data.\n");
        //return HI_FAILURE;
    }

    // 1 Init Encoder
    nRet = hHaEntry->EncodeInit(&hEncoder, (const HI_HAENCODE_OPENPARAM_S*)(pstChnOpenParms));
    if (HA_ErrorNone != nRet)
    {
        HI_ERR_AENC("ha_err: EncodeInit (codec:%s), err=0x%x\n", (HI_CHAR*)(hHaEntry->szName), nRet);
        HI_ERR_AENC("enCodecID=0x%x\n", hHaEntry->enCodecID);
        HI_ERR_AENC("u32DesiredOutChannels=0x%x\n", pstOpenParms->u32DesiredOutChannels);
        HI_ERR_AENC("s32BitPerSample=0x%x\n", pstOpenParms->s32BitPerSample);
        HI_ERR_AENC("u32DesiredSampleRate=0x%x\n", pstOpenParms->u32DesiredSampleRate);
        HI_ERR_AENC("pCodecPrivateData=0x%x\n", pstOpenParms->pCodecPrivateData);
        HI_ERR_AENC("u32CodecPrivateDataSize=0x%x\n", pstOpenParms->u32CodecPrivateDataSize);

        return HI_ERR_AENC_CREATECH_FAIL;
    }

    if (HI_NULL == hEncoder)
    {
        HI_ERR_AENC(" ha_err:HA EncodeInit fail hEncoder==0! \n");
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    pstAencChan->hEncoder = (HI_VOID*)hEncoder;
    pstAencChan->hHaEntry = (HI_VOID*)hHaEntry;

    nRet = hHaEntry->EncodeGetMaxBitsOutSize(hEncoder, &u32BitsMaxFrameSize);
    if (HA_ErrorNone != nRet)
    {
        (HI_VOID)hHaEntry->EncodeDeInit(hEncoder);
        HI_ERR_AENC(" ha_err: HA EncodeGetMaxBitsOutSize fail err=0x%x! \n", nRet);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    // 2  Allocate Input Buffer
    if (16 == pstAencAttr->sOpenParam.s32BitPerSample)
    {
        u32FrameSize = pstAencAttr->sOpenParam.u32SamplePerFrame * pstAencAttr->sOpenParam.u32DesiredOutChannels * sizeof(HI_U16);
    }
    else
    {
        u32FrameSize = pstAencAttr->sOpenParam.u32SamplePerFrame * pstAencAttr->sOpenParam.u32DesiredOutChannels * sizeof(HI_U32);
    }

    nRet = AENCInitInBuf(pstAencChan, pstAencAttr->u32InBufSize, u32FrameSize);
    if (HI_SUCCESS != nRet)
    {
        (HI_VOID)hHaEntry->EncodeDeInit(hEncoder);
        HI_ERR_AENC(" AENCInitInBuf fail errCode=0x%x! \n", nRet);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    // 3  Allocate Output Buffer
    nRet = AENCInitOutBuf(pstAencChan, u32BitsMaxFrameSize, pstAencAttr->u32OutBufNum);
    if (HI_SUCCESS != nRet)
    {
        AENCDeInitInBuf(pstAencChan);
        (HI_VOID)hHaEntry->EncodeDeInit(hEncoder);
        HI_ERR_AENC(" AENCInitOutBuf fail errCode=0x%x! \n", nRet);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    // 4 Reset PTSQue
    AENCResetPTSQue(&pstAencChan->PTSQue);

    pstAencChan->u32OutBufNum = pstAencAttr->u32OutBufNum;

    pstAencChan->u32DesiredOutChannels = pstAencAttr->sOpenParam.u32DesiredOutChannels;
    pstAencChan->bInterleaved = pstAencAttr->sOpenParam.bInterleaved;
    pstAencChan->u32BitPerSample = (HI_U32)pstAencAttr->sOpenParam.s32BitPerSample;
    pstAencChan->u32DesiredSampleRate = pstAencAttr->sOpenParam.u32DesiredSampleRate;
    pstAencChan->u32SamplePerFrame = pstAencAttr->sOpenParam.u32SamplePerFrame;

    pstAencChan->pstAencInfo->u32InBufSize  = pstAencChan->u32InBufSize;
    pstAencChan->pstAencInfo->tInBufRead  = (HI_U8*)(pstAencChan->sInPcmBuf.pRead) - (HI_U8*)(HI_NULL);
    pstAencChan->pstAencInfo->tInBufWrite = (HI_U8*)(pstAencChan->sInPcmBuf.pWrite) - (HI_U8*)(HI_NULL);

    pstAencChan->pstAencInfo->u32OutFrameNum  = pstAencAttr->u32OutBufNum;
    pstAencChan->pstAencInfo->u32OutFrameRIdx = pstAencChan->sOutStreamBuf.u32ReadIdx;
    pstAencChan->pstAencInfo->u32OutFrameWIdx = pstAencChan->sOutStreamBuf.u32WriteIdx;

    return HI_SUCCESS;
}

static HI_S32 AENCDestroyEncoder(AENC_CHAN_S* pstAencChan)
{
    HI_HA_ENCODE_S* hHaEntry = (HI_HA_ENCODE_S*)(pstAencChan->hHaEntry);
    HI_S32 nRet;

    AENCResetPTSQue(&(pstAencChan->PTSQue));
    AENCDeInitOutBuf(pstAencChan);
    AENCDeInitInBuf(pstAencChan);

    nRet = hHaEntry->EncodeDeInit(pstAencChan->hEncoder);
    if (HA_ErrorNone != nRet)
    {
        HI_ERR_AENC(" ha_err:HA EncodeDeInit fail errCode=0x%x! \n", nRet);
        return HI_FAILURE;
    }

    pstAencChan->hHaEntry = (HI_VOID*)HI_NULL;
    pstAencChan->hEncoder = (HI_VOID*)HI_NULL;

    pstAencChan->pstAencInfo->u32InBufSize = 0;
    pstAencChan->pstAencInfo->tInBufRead  = 0;
    pstAencChan->pstAencInfo->tInBufWrite = 0;

    pstAencChan->pstAencInfo->u32OutFrameNum  = 0;
    pstAencChan->pstAencInfo->u32OutFrameRIdx = 0;
    pstAencChan->pstAencInfo->u32OutFrameWIdx = 0;

    return HI_SUCCESS;
}

static HI_S32 AENCGetInBufIdleSize(AENC_PCM_BUFFER_S* pstInBuf)
{
    if (pstInBuf->pRead > pstInBuf->pWrite)
    {
        return (pstInBuf->pRead - pstInBuf->pWrite);
    }
    else
    {
        return ((pstInBuf->pEnd - pstInBuf->pStart) + pstInBuf->pRead) - pstInBuf->pWrite;
    }
}

static HI_S32 AENCGetInBufDataSize(AENC_PCM_BUFFER_S* pstInBuf)
{
    if (pstInBuf->pWrite == pstInBuf->pRead)
    {
        return 0;
    }

    if (pstInBuf->pWrite > pstInBuf->pRead)
    {
        return (pstInBuf->pWrite - pstInBuf->pRead);
    }
    else
    {
        return (pstInBuf->pEnd - pstInBuf->pStart) - (pstInBuf->pRead - pstInBuf->pWrite);
    }
}

static HI_VOID AENCUpdateInBufReadPtr(AENC_PCM_BUFFER_S* pstInBuf, HI_U32 u32Size)
{
    pstInBuf->pRead += u32Size;

    if (pstInBuf->pRead >= pstInBuf->pEnd)
    {
        pstInBuf->pRead -= (pstInBuf->pEnd - pstInBuf->pStart);
    }
}

static HI_VOID AENCFillDataInBuf(AENC_PCM_BUFFER_S* pstInBuf, HI_VOID* pPcmBuf, HI_U32 u32Size)
{
    HI_U32 u32TailSpace;

    if (pstInBuf->pWrite < pstInBuf->pRead)
    {
        u32TailSpace = (HI_U32)(pstInBuf->pRead - pstInBuf->pWrite);
    }
    else
    {
        u32TailSpace = (HI_U32)(pstInBuf->pEnd - pstInBuf->pWrite);
    }

    // copy data
    if (u32Size <= u32TailSpace)
    {
        memcpy((HI_VOID*)pstInBuf->pWrite, (HI_VOID*)pPcmBuf, u32Size);
    }
    else
    {
        memcpy((HI_VOID*)pstInBuf->pWrite, (HI_VOID*)pPcmBuf, u32TailSpace);
        memcpy((HI_VOID*)pstInBuf->pStart, (HI_VOID*)((HI_U8*)pPcmBuf + u32TailSpace), u32Size - u32TailSpace);
    }

    /* update WritePtr */
    pstInBuf->pWrite += u32Size;
    if (pstInBuf->pWrite >= pstInBuf->pEnd)
    {
        pstInBuf->pWrite -= (pstInBuf->pEnd - pstInBuf->pStart);
    }
}

static HI_U32 AENCGetEncodeInDataSize(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan;

    pstAencChan = g_pstAencChan[hAenc];

    if (16 == pstAencChan->u32BitPerSample)
    {
        return pstAencChan->u32SamplePerFrame * pstAencChan->u32DesiredOutChannels * sizeof(HI_U16);
    }

    return pstAencChan->u32SamplePerFrame * pstAencChan->u32DesiredOutChannels * sizeof(HI_U32);
}

static HI_VOID AutoMixProcess(HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                              HI_U32  u32DesiredChannels, AENC_CHAN_S* pstAencChan)
{
    HI_U32 i;
    HI_U32 u32PcmSamplesPerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    HI_U32* pu32WorkBuf = AENCGetWorkBuf(pstAencChan);

    if ((2 == u32DesiredChannels) && (1 == pstAOFrame->u32Channels))
    {
        HI_S16* ps16Src;
        HI_S16* ps16Dst = (HI_S16*)pu32WorkBuf;
        HI_S16 s16Data;

        ps16Src = (HI_S16*)(pstAOFrame->ps32PcmBuffer);
        for (i = 0; i < u32PcmSamplesPerFrame; i++)
        {
            s16Data = (*ps16Src++);
            *ps16Dst++ = s16Data;
            *ps16Dst++ = s16Data;
        }
    }
    else if ((1 == u32DesiredChannels) && (2 == pstAOFrame->u32Channels))
    {
        HI_S16* ps16Src;
        HI_S16* ps16Dst = (HI_S16*)pu32WorkBuf;
        HI_S32 s32DataL, s32DataR;

        ps16Src = (HI_S16*)(pstAOFrame->ps32PcmBuffer);
        for (i = 0; i < u32PcmSamplesPerFrame; i++)
        {
            s32DataL   = (*ps16Src++);
            s32DataR   = (*ps16Src++);
            *ps16Dst++ = CLIPTOSHORT(s32DataL + s32DataR);
        }
    }
    else
    {
        HI_WARN_AENC("encoder DesiredChannels=%d, intput channels=%d\n", u32DesiredChannels, pstAOFrame->u32Channels);

        /* TODO, suppurt more upmix or downmix */
        return;
    }

    pstAOFrame->u32Channels   = u32DesiredChannels;
    pstAOFrame->ps32PcmBuffer = (HI_S32*)pu32WorkBuf;
}

static HI_VOID AENCUnifyIntreleavedPcmData(HI_UNF_AO_FRAMEINFO_S* pstAOFrame, AENC_CHAN_S* pstAencChan)
{
    HI_U32 i;
    HI_U32 uPcmSamplesPerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    HI_U32* pu32WorkBuf = AENCGetWorkBuf(pstAencChan);

    if (HI_TRUE == pstAOFrame->bInterleaved)
    {
        return;
    }

    if (16 == pstAOFrame->s32BitPerSample)
    {
        HI_S16* pSrcL16, *pSrcR16;
        pSrcL16 = (HI_S16*)(pstAOFrame->ps32PcmBuffer);
        HI_U16* pu16Data = (HI_U16*)pu32WorkBuf;

        if (2 == pstAOFrame->u32Channels)
        {
            pSrcR16 = (HI_S16*)(pstAOFrame->ps32PcmBuffer) + pstAOFrame->u32PcmSamplesPerFrame;
        }
        else
        {
            pSrcR16 = pSrcL16;
        }

        for (i = 0; i < uPcmSamplesPerFrame; i++)
        {
            *pu16Data++ = (HI_U16)(*pSrcL16++);
            *pu16Data++ = (HI_U16)(*pSrcR16++);
        }
    }
    else
    {
        HI_S32* pSrcL32, *pSrcR32;
        HI_U32* pu32Data = (HI_U32*)pu32WorkBuf;

        pSrcL32 = (HI_S32*)(pstAOFrame->ps32PcmBuffer);
        if (2 == pstAOFrame->u32Channels)
        {
            pSrcR32 = pSrcL32 + pstAOFrame->u32PcmSamplesPerFrame;
        }
        else
        {
            pSrcR32 = pSrcL32;
        }

        for (i = 0; i < uPcmSamplesPerFrame; i++)
        {
            *pu32Data++ = (HI_U32)(*pSrcL32++);
            *pu32Data++ = (HI_U32)(*pSrcR32++);
        }
    }

    pstAOFrame->bInterleaved  = HI_TRUE;
    pstAOFrame->ps32PcmBuffer = (HI_S32*)pu32WorkBuf;
}

static HI_VOID AENCUnifyBitDepthPcmData(HI_UNF_AO_FRAMEINFO_S* pstAOFrame, AENC_CHAN_S* pstAencChan)
{
    HI_U32 i;
    HI_S32* ps32Src;
    HI_S16* ps16Dst;
    HI_U32* pu32WorkBuf = AENCGetWorkBuf(pstAencChan);

    if (16 == pstAOFrame->s32BitPerSample)
    {
        return;
    }
    ps16Dst = (HI_S16*)pu32WorkBuf;

    ps32Src = (HI_S32*)(pstAOFrame->ps32PcmBuffer);

    for (i = 0; i < pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels; i++)
    {
        *ps16Dst++ = (HI_S16)((HI_U32)(*ps32Src++) >> 16);
    }

    pstAOFrame->s32BitPerSample = 16;
    pstAOFrame->ps32PcmBuffer = (HI_S32*)pu32WorkBuf;
}

/*****************************************************************************
 Description: AO Data change to one single format in order to easy later
*****************************************************************************/
static HI_U32 AENCUnifyPcmData(AENC_CHAN_S* pstAencChan, HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_U32 u32RealFrameSize, u32SamplePerFrame;
    HI_U32 u32DesiredChannels;

#ifdef ENA_AENC_AUTOSRC
    HI_U32 u32DesiredSampleRate;
#endif

    u32DesiredChannels   = pstAencChan->u32DesiredOutChannels;

#ifdef ENA_AENC_AUTOSRC
    u32DesiredSampleRate = pstAencChan->u32DesiredSampleRate;
#endif

    if (HI_FALSE == pstAOFrame->bInterleaved)
    {
        AENCUnifyIntreleavedPcmData(pstAOFrame, pstAencChan);
    }

    if (16 != pstAOFrame->s32BitPerSample)
    {
        AENCUnifyBitDepthPcmData(pstAOFrame, pstAencChan);
    }

    if (u32DesiredChannels != pstAOFrame->u32Channels)
    {
        AutoMixProcess(pstAOFrame, u32DesiredChannels, pstAencChan);
    }

#ifdef ENA_AENC_AUTOSRC
    if (HI_TRUE == pstAencChan->bAutoSRC)
    {
        if (u32DesiredSampleRate != pstAOFrame->u32SampleRate)
        {
            LinearSRCProcess(pstAOFrame, &g_sAencLinearSRC[pstAencChan->u32ChID], u32DesiredSampleRate, pstAencChan);
        }
    }
#endif

    u32SamplePerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    if (16 == pstAOFrame->s32BitPerSample)
    {
        u32RealFrameSize = u32SamplePerFrame * pstAOFrame->u32Channels * sizeof(HI_U16);
    }
    else
    {
        u32RealFrameSize = u32SamplePerFrame * pstAOFrame->u32Channels * sizeof(HI_U32);
    }

    return u32RealFrameSize;
}

static HI_U32 AENCCalcInBufNeedSize(HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                                    HI_U32                 u32DesiredChannels,
                                    HI_U32                 u32DesiredSampleRate,
                                    HI_U32                 u32DesiredBitPerSample)
{
    HI_U32 u32NeedSize, u32SamplePerFrame;

    u32SamplePerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    if (16 == pstAOFrame->s32BitPerSample)
    {
        u32NeedSize = u32SamplePerFrame * pstAOFrame->u32Channels * sizeof(HI_U16);
    }
    else
    {
        u32NeedSize = u32SamplePerFrame * pstAOFrame->u32Channels * sizeof(HI_U32);
    }

    /* bitdepth translate */
    if ((16 != pstAOFrame->s32BitPerSample) && (16 == u32DesiredBitPerSample))
    {
        u32NeedSize >>= 1;    /* 32bit to 16bit */
    }

    /* downmix or unmix translate */
    if ((2 == u32DesiredChannels) && (1 == pstAOFrame->u32Channels))
    {
        u32NeedSize <<= 1;    /* mono to stereo */
    }
    else if ((1 == u32DesiredChannels) && (2 == pstAOFrame->u32Channels))
    {
        u32NeedSize >>= 1;    /* stereo to mono */
    }

    /* SRC translate */
    if (u32DesiredSampleRate > pstAOFrame->u32SampleRate)
    {
        u32NeedSize  = (u32NeedSize * u32DesiredSampleRate) / pstAOFrame->u32SampleRate;
        u32NeedSize += AENC_MAX_CHANNELS * 4 * (sizeof(HI_U16));  /* add at less 4 sample space for SRC padding, such as 48kHz SRC to 44.1kHz  */
    }

    return u32NeedSize;
}

static HI_S32 AENCSentInputData(AENC_CHAN_S* pstAencChan, HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_U32 u32InBufSize, u32NeedFrameSize, u32RealFrameSize;

#ifdef HI_PROC_SUPPORT
    static FILE* fPcm = NULL;
#endif

    AENC_DbgCountTrySendBuf(pstAencChan);

    CHECK_AENC_NULL_PTR(pstAencChan->pstAencInfo);

    if (HI_NULL == pstAOFrame->ps32PcmBuffer || 0 == pstAOFrame->u32PcmSamplesPerFrame)
    {
        HI_WARN_AENC("no input data\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == pstAencChan->bAutoSRC)
    {
        if (pstAOFrame->u32SampleRate != pstAencChan->u32DesiredSampleRate)
        {
            HI_ERR_AENC(" current version AENC  dont support diffrent SampleRate!  inSampleRate=%d, outSampleRate=%d\n",
                        pstAOFrame->u32SampleRate, pstAencChan->u32DesiredSampleRate);
            return HI_ERR_AENC_INVALID_PARA;
        }
    }

    u32NeedFrameSize = AENCCalcInBufNeedSize(pstAOFrame, pstAencChan->u32DesiredOutChannels,
                       pstAencChan->u32DesiredSampleRate,
                       pstAencChan->u32BitPerSample);

    u32InBufSize = (HI_U32)AENCGetInBufIdleSize(&pstAencChan->sInPcmBuf);
    if (u32InBufSize <= u32NeedFrameSize)
    {
        return HI_ERR_AENC_IN_BUF_FULL;
    }

    /* translate input pcm format to encoder pcm format */
    u32RealFrameSize = AENCUnifyPcmData(pstAencChan, pstAOFrame);
    if (pstAOFrame->u32Channels != pstAencChan->u32DesiredOutChannels)
    {
        HI_ERR_AENC(" current version AENC  dont support diffrent Channels!  in Channels=%d, outChannels=%d\n",
                    pstAOFrame->u32Channels, pstAencChan->u32DesiredOutChannels);
        return HI_ERR_AENC_INVALID_PARA;
    }

#ifdef HI_PROC_SUPPORT
    if ( pstAencChan->pstAencInfo->enPcmCtrlState == AENC_CMD_CTRL_START )
    {
        if (!fPcm)
        {
            fPcm = fopen(pstAencChan->pstAencInfo->filePath, "wb");
            if (!fPcm)
            {
                HI_ERR_AENC("can not open file (%s)\n", pstAencChan->pstAencInfo->filePath);
            }
        }

        if (fPcm)
        {
            HI_S32 s32Len = fwrite((HI_VOID*)pstAOFrame->ps32PcmBuffer, 1, u32RealFrameSize, fPcm);
            if (u32RealFrameSize != s32Len)
            {
                HI_ERR_AENC("write (%s) failed\n", pstAencChan->pstAencInfo->filePath);
                fclose(fPcm);
                fPcm = HI_NULL;
                pstAencChan->pstAencInfo->enPcmCtrlState = AENC_CMD_CTRL_STOP;
            }
        }
    }

    if ( pstAencChan->pstAencInfo->enPcmCtrlState == AENC_CMD_CTRL_STOP )
    {
        if (fPcm)
        {
            fclose(fPcm);
            fPcm = HI_NULL;
        }
    }
#endif

    AENCFillDataInBuf(&pstAencChan->sInPcmBuf, (HI_VOID*)(pstAOFrame->ps32PcmBuffer), u32RealFrameSize);
#ifdef PTS_SUPPORT  //TODO if store pts should be bofore fill data
    AENCStorePTS(pstAencChan, pstAencChan->sInPcmBuf.pWrite, pstAOFrame->u32PtsMs, u32RealFrameSize);
#endif

    pstAencChan->pstAencInfo->tInBufWrite = (HI_U8*)(pstAencChan->sInPcmBuf.pWrite) - (HI_U8*)(HI_NULL);
    AENC_DbgCountSendBuf(pstAencChan);
    return HI_SUCCESS;
}

static HI_S32 AENCOpenDevice(HI_VOID)
{
    return open(g_acAencDevName, O_RDWR, 0);
}

static HI_S32 AENCCloseDevice(HI_S32 AudioDevFd)
{
    HI_S32 ret = HI_SUCCESS;

    if (AudioDevFd < 0)
    {
        return HI_FAILURE;
    }

    ret = close(AudioDevFd);
    if (HI_SUCCESS != ret)
    {
        HI_WARN_AENC("Aenc Close err=0x%x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID ANECGetHaSzname(AENC_CHAN_S* pstAencChan)
{
    HI_HA_ENCODE_S* hHaEntry;

    hHaEntry = (HI_HA_ENCODE_S*)(pstAencChan->hHaEntry);

    if (hHaEntry)
    {
        if (hHaEntry->szName)
        {
            memcpy(pstAencChan->pstAencInfo->szCodecType, hHaEntry->szName, sizeof(pstAencChan->pstAencInfo->szCodecType));
        }
        else
        {
            strncpy((HI_CHAR*)pstAencChan->pstAencInfo->szCodecType, "UNKNOWN", sizeof(pstAencChan->pstAencInfo->szCodecType));
        }

        pstAencChan->u32CodecID = hHaEntry->enCodecID;
        pstAencChan->pstAencInfo->u32CodecID = hHaEntry->enCodecID;
    }
}

static HI_VOID AENCInitProcInfo(AENC_CHAN_S* pstAencChan)
{
    AENC_PROC_ITEM_S* pstAencInfo = pstAencChan->pstAencInfo;

    memset(pstAencInfo, 0, sizeof(AENC_PROC_ITEM_S));

    pstAencInfo->bAencWorkEnable = HI_TRUE;
    pstAencInfo->u32BitWidth   = pstAencChan->u32BitPerSample;
    pstAencInfo->u32SampleRate = pstAencChan->u32DesiredSampleRate;
    pstAencInfo->u32Channels = pstAencChan->u32DesiredOutChannels;

    pstAencInfo->enPcmCtrlState = AENC_CMD_CTRL_STOP;
    pstAencInfo->enEsCtrlState = AENC_CMD_CTRL_STOP;

    pstAencInfo->stAttach.eType = ANEC_SOURCE_BUTT;
    pstAencInfo->stAttach.hSource = HI_INVALID_HANDLE;

    ANECGetHaSzname(pstAencChan);
}

static HI_S32 AENCResetBuf(HI_HANDLE hAenc, HI_U32 u32BufType)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_CH_CREATE(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    /*reset in buf*/
    if (u32BufType & 0x01)
    {
        AENCResetInBuf(&(pstAencChan->sInPcmBuf));
        pstAencChan->pstAencInfo->tInBufRead  = (HI_U8*)(pstAencChan->sInPcmBuf.pRead) - (HI_U8*)HI_NULL;
        pstAencChan->pstAencInfo->tInBufWrite = (HI_U8*)(pstAencChan->sInPcmBuf.pWrite) - (HI_U8*)HI_NULL;
    }

    /*reset out buf*/
    if (u32BufType & 0x02)
    {
        AENCResetOutBuf(&(pstAencChan->sOutStreamBuf));
        pstAencChan->pstAencInfo->u32OutFrameRIdx = pstAencChan->sOutStreamBuf.u32ReadIdx;
        pstAencChan->pstAencInfo->u32OutFrameWIdx = pstAencChan->sOutStreamBuf.u32WriteIdx;
    }

    return HI_SUCCESS;
}

HI_S32 AENC_RegisterEncoder(const HI_CHAR* pszCodecDllName)
{
    CHECK_AENC_NULL_PTR(pszCodecDllName);

    return AENCRegisterHaEncoder(pszCodecDllName);
}

HI_S32 AENC_Init(HI_VOID)
{
    HI_U32 i;
    HI_VOID* pBase;

    AENC_LOCK();

    if (0 != g_u32AencInitCnt)
    {
        g_u32AencInitCnt++;

        AENC_UNLOCK();
        return HI_SUCCESS;
    }

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        g_pstAencChan[i] = HI_NULL;
    }

    pBase = (HI_VOID*)HI_MALLOC(HI_ID_AENC, sizeof(AENC_CHAN_S) * AENC_INSTANCE_MAXNUM);
    if (NULL == pBase)
    {
        HI_ERR_AENC("malloc AENC_CHAN_S fail\n");
        AENC_UNLOCK();
        return HI_FAILURE;
    }

    memset(pBase, 0, sizeof(AENC_CHAN_S) * AENC_INSTANCE_MAXNUM);
    g_pstAencChan[0] = (AENC_CHAN_S*)pBase;

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        g_pstAencChan[i] = &(((AENC_CHAN_S*)pBase)[i]);
        g_pstAencChan[i]->beAssigned = HI_FALSE;
        g_pstAencChan[i]->stAttach.hSource = HI_INVALID_HANDLE;
    }

    g_u32AencInitCnt++;

    AENC_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 AENC_DeInit(HI_VOID)
{
    HI_U32 i;
    AENC_CHAN_S* pstAencChan;
    HI_VOID* pChBase;

    AENC_LOCK();
    AENCAllCHNLock();

    if (0 == g_u32AencInitCnt)
    {
        HI_WARN_AENC("Aenc is not inited!\n");

        AENCAllCHNUnLock();
        AENC_UNLOCK();

        return HI_SUCCESS;
    }

    g_u32AencInitCnt--;

    if (0 != g_u32AencInitCnt)
    {
        AENCAllCHNUnLock();
        AENC_UNLOCK();

        return HI_SUCCESS;
    }

    AENCAllCHNUnLock();

    pChBase = g_pstAencChan[0];

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        AENC_CHAN_LOCK(i);

        pstAencChan = g_pstAencChan[i];
        if (HI_NULL == pstAencChan)
        {
            AENC_CHAN_UNLOCK(i);
            continue;
        }

        if (HI_INVALID_HANDLE != pstAencChan->stAttach.hSource)
        {
            HI_ERR_AENC("please destroy detach hsource(0x%x) first.\n", pstAencChan->stAttach.hSource);
            AENC_CHAN_UNLOCK(i);
            continue;
        }

        pstAencChan->AencThreadRun = HI_FALSE;

        if (pstAencChan->beAssigned == HI_TRUE)
        {
            (HI_VOID)AENCDestroyEncoder(pstAencChan);
            (HI_VOID)AENCCloseDevice(pstAencChan->AencDevFd);
            pstAencChan->AencDevFd = -1;
            pstAencChan->pstAencInfo->bAencWorkEnable = HI_FALSE;
        }

        g_pstAencChan[i] = HI_NULL;

        AENC_CHAN_UNLOCK(i);
    }

    if (HI_NULL != pChBase)
    {
        HI_FREE(HI_ID_AENC, pChBase);
    }

    AENC_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 AENC_Open(HI_HANDLE* phAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    HI_U32 i;
    HI_S32 s32Ret;
    HI_U32 phy_adress;
    AENC_CHAN_S* pstAencChan;
    AENC_ATTR_S  stAencAttr;

    CHECK_AENC_NULL_PTR(phAenc);
    CHECK_AENC_NULL_PTR(pstAencAttr);
    CHECK_AENC_OPEN_FORMAT(pstAencAttr->sOpenParam.u32DesiredSampleRate, pstAencAttr->sOpenParam.u32DesiredOutChannels,
                           pstAencAttr->sOpenParam.s32BitPerSample, pstAencAttr->sOpenParam.bInterleaved);

    stAencAttr.u32CodecID   = pstAencAttr->enAencType;
    stAencAttr.sOpenParam   = pstAencAttr->sOpenParam;
    stAencAttr.u32InBufSize = AENC_DEFAULT_INPUT_BUFFER_SIZE;
    stAencAttr.u32OutBufNum = AENC_DEFAULT_OUTBUF_NUM;

    AENC_LOCK();

    if (!g_u32AencInitCnt)
    {
        HI_ERR_AENC(" Please init aenc first\n" );
        AENC_UNLOCK();
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        if (HI_NULL == g_pstAencChan[i])
        {
            continue;
        }

        if (HI_FALSE == g_pstAencChan[i]->beAssigned)
        {
            break;
        }
    }

    if (i >= AENC_INSTANCE_MAXNUM)
    {
        HI_ERR_AENC(" not support so much aenc\n");
        AENC_UNLOCK();
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    AENC_UNLOCK();
    AENC_CHAN_LOCK(i);

    if (HI_NULL == g_pstAencChan[i])
    {
        AENC_CHAN_UNLOCK(i);
        return HI_FAILURE;
    }

    pstAencChan = g_pstAencChan[i];
    pstAencChan->u32ChID = i;

    /* Check if initialized */
    pstAencChan->AencDevFd = AENCOpenDevice();
    if (pstAencChan->AencDevFd < 0)
    {
        HI_ERR_AENC("AENCOpenDevice failed\n");
        AENC_CHAN_UNLOCK(i);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    s32Ret = ioctl(pstAencChan->AencDevFd, DRV_AENC_PROC_INIT, &phy_adress);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("ioctl DRV_AENC_PROC_INIT failed(0x%x)\n", s32Ret);
        goto ERR1;
    }

    pstAencChan->pstAencInfo = (AENC_PROC_ITEM_S*)HI_MPI_MMZ_Map(phy_adress, HI_FALSE);
    if (HI_NULL == pstAencChan->pstAencInfo)
    {
        HI_ERR_AENC("AENC_PROC_ITEM_S memmap fail \n");
        goto ERR2;
    }
    pstAencChan->u32PhyAddr = phy_adress;

    s32Ret = AENCCreateWorkBuf(pstAencChan);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENCCreateWorkBuf failed(0x%x)\n", s32Ret);
        goto ERR3;
    }

    memset(&pstAencChan->stEncoderInfo, 0, sizeof(AENC_ENCODER_INFO_S));
    s32Ret = AENCCreateEncoder(pstAencChan, &stAencAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENCCreateEncoder failed(0x%x)\n", s32Ret);
        goto ERR4;
    }

    AENCInitProcInfo(pstAencChan);

#ifdef ENA_AENC_AUTOSRC
    g_sAencLinearSRC[pstAencChan->u32ChID].InRate = 0;
#endif

    pstAencChan->bAutoSRC   = HI_TRUE;
    pstAencChan->beAssigned = HI_TRUE;
    pstAencChan->bStart = HI_FALSE;
    pstAencChan->stAttach.eType = ANEC_SOURCE_BUTT;
    pstAencChan->stAttach.hSource = HI_INVALID_HANDLE;
    memcpy(&pstAencChan->pstAencInfo->stAttach, &pstAencChan->stAttach, sizeof(AENC_INFO_ATTACH_S));

    HI_INFO_AENC("open aenc chans %d succeed!\n", i);

    *phAenc = i;
    pstAencChan->AencThreadRun = HI_TRUE;
    s32Ret = pthread_create(&pstAencChan->AencThreadInst, HI_NULL, AENC_Thread, (HI_VOID*)((HI_U8*)HI_NULL + *phAenc));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENC Create Thread err\n");
        goto ERR5;
    }

    AENC_CHAN_UNLOCK(i);

    return HI_SUCCESS;
ERR5:
    AENCDestroyEncoder(pstAencChan);
ERR4:
    (HI_VOID)AENCDestroyWorkBuf(pstAencChan);
ERR3:
    (HI_VOID)HI_MPI_MMZ_Unmap(pstAencChan->u32PhyAddr);
ERR2:
    (HI_VOID)ioctl(pstAencChan->AencDevFd, DRV_AENC_PROC_EXIT, &pstAencChan->pstAencInfo);
ERR1:
    (HI_VOID)AENCCloseDevice(pstAencChan->AencDevFd);
    pstAencChan->AencDevFd = -1;

    AENC_CHAN_UNLOCK(i);
    return HI_ERR_AENC_CREATECH_FAIL;
}

HI_S32 AENC_Close(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_HANDLE(hAenc);

    AENC_CHAN_LOCK(hAenc);

    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    if (pstAencChan->bStart)
    {
        HI_ERR_AENC("please stop aenc first.\n");
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    if (HI_INVALID_HANDLE != pstAencChan->stAttach.hSource)
    {
        HI_ERR_AENC("please detach aenc first.\n");
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    pstAencChan->AencThreadRun = HI_FALSE;
    (HI_VOID)pthread_join(pstAencChan->AencThreadInst, HI_NULL);

    (HI_VOID)AENCDestroyEncoder(pstAencChan);
    (HI_VOID)AENCDestroyWorkBuf(pstAencChan);

    if (HI_NULL != pstAencChan->stEncoderInfo.pAudPrivDataBak)
    {
        HI_FREE(HI_ID_AENC, pstAencChan->stEncoderInfo.pAudPrivDataBak);
        pstAencChan->stEncoderInfo.pAudPrivDataBak = HI_NULL_PTR;
        pstAencChan->stEncoderInfo.u32AudPrivDataBakDize = 0;
    }

    (HI_VOID)ioctl(pstAencChan->AencDevFd, DRV_AENC_PROC_EXIT, &pstAencChan->pstAencInfo);

    (HI_VOID)AENCCloseDevice(pstAencChan->AencDevFd);
    pstAencChan->AencDevFd = -1;
    pstAencChan->pstAencInfo->bAencWorkEnable = HI_FALSE;
    (HI_VOID)HI_MPI_MMZ_Unmap(pstAencChan->u32PhyAddr);

    pstAencChan->beAssigned = HI_FALSE;
    pstAencChan->stAttach.eType = ANEC_SOURCE_BUTT;
    pstAencChan->stAttach.hSource = HI_INVALID_HANDLE;

    AENC_CHAN_UNLOCK(hAenc);

    return HI_SUCCESS;
}

static HI_S32 AENC_Pull(HI_HANDLE hAenc)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AENC_CHAN_S* pstAencChan;
    HI_HA_ENCODE_S* hHaEntry;
    HI_HAENCODE_INPACKET_S sApkt;
    HI_HAENCODE_OUTPUT_S sAOut;
    HI_U32 u32EncodeInDataSize;
    AENC_OUTPUTBUF_S* pstOutBufUnit;

    CHECK_AENC_HANDLE(hAenc);

    AENC_CHAN_TRY_LOCK(hAenc);

    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    AENC_DbgCountTryEncodeCount(hAenc);

    hHaEntry = (HI_HA_ENCODE_S*)(pstAencChan->hHaEntry);

    /* check input buf have enough data to ecoder*/
    u32EncodeInDataSize = AENCGetEncodeInDataSize(hAenc);

    while (1)
    {
        sApkt.pu8Data = pstAencChan->sInPcmBuf.pRead;
        sApkt.u32Size = (HI_U32)AENCGetInBufDataSize(&pstAencChan->sInPcmBuf);

        /* sInPcmBuf, don't need consider loop in the buffer end*/
        if (sApkt.u32Size < u32EncodeInDataSize)
        {
            s32Ret = HI_ERR_AENC_IN_BUF_FULL;
            break;
        }

        /* check output buf for ecoder*/
        s32Ret = AENCGetOutBufIdleUnit(&pstAencChan->sOutStreamBuf, &pstOutBufUnit);
        if (HI_SUCCESS != s32Ret)
        {
            s32Ret = HI_ERR_AENC_OUT_BUF_FULL;
            break;
        }

        sAOut.ps32BitsOutBuf = (HI_S32*)(pstOutBufUnit->pu8Data);
        sAOut.u32BitsOutBufSize = pstAencChan->sOutStreamBuf.u32FrameSize;

        /* encoder one frame*/
        s32Ret = hHaEntry->EncodeFrame(pstAencChan->hEncoder, &sApkt, &sAOut);
        if (HA_ErrorNone != s32Ret)
        {
            HI_ERR_AENC("HA EncodeFrame fail errCode = 0x%x!\n", s32Ret);
            pstAencChan->pstAencInfo->u32ErrFrame += 1;
            s32Ret = HI_ERR_AENC_INVALID_OUTFRAME;
            break;
        }

#ifdef PTS_SUPPORT
        // PTS
        pstOutBufUnit->u32PtsMs = AENCFindPTS(&pstAencChan->PTSQue, (HI_U8*)pstAencChan->sInPcmBuf.pRead,
                                              pstAencChan->u32SamplePerFrame,
                                              pstAencChan->u32DesiredSampleRate);
#endif

        /* encoder success, update input/output buffer*/
        pstOutBufUnit->bFlag = HI_TRUE;
        pstOutBufUnit->u32Bytes = sAOut.u32BitsOutBytesPerFrame;
        AENCUpdateInBufReadPtr(&pstAencChan->sInPcmBuf, u32EncodeInDataSize);
        AENCNextOutBufUnit(&pstAencChan->sOutStreamBuf);

        pstAencChan->pstAencInfo->tInBufRead = (HI_U8*)(pstAencChan->sInPcmBuf.pRead) - (HI_U8*)HI_NULL;
        pstAencChan->pstAencInfo->u32OutFrameWIdx = pstAencChan->sOutStreamBuf.u32WriteIdx;
        pstAencChan->pstAencInfo->u32EncFrame += 1;
        s32Ret = HI_SUCCESS;
    }

    AENC_CHAN_UNLOCK(hAenc);
    return s32Ret;
}

HI_S32 AENC_SendBuffer(HI_HANDLE hAenc, const HI_UNF_AO_FRAMEINFO_S* pstOrgAOFrame)
{
    HI_S32 s32Ret;
    AENC_CHAN_S* pstAencChan;
    HI_UNF_AO_FRAMEINFO_S stAOFrame = { 0 };

    CHECK_AENC_NULL_PTR(pstOrgAOFrame);
    CHECK_AENC_PCM_CHANNEL(pstOrgAOFrame->u32Channels);
    CHECK_AENC_PCM_SAMPLERATE(pstOrgAOFrame->u32SampleRate);
    CHECK_AENC_PCM_BITWIDTH(pstOrgAOFrame->s32BitPerSample);
    CHECK_AENC_PCM_SAMPLESIZE(pstOrgAOFrame->u32PcmSamplesPerFrame);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    memcpy(&stAOFrame, pstOrgAOFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));

    pstAencChan = g_pstAencChan[hAenc];

    if (!pstAencChan->bStart)
    {
        HI_ERR_AENC("hAenc(%d) not start.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    if ((HI_INVALID_HANDLE != pstAencChan->stAttach.hSource) && (HI_ID_AI != ((pstAencChan->stAttach.hSource) >> 16))) //if attach Ai,Ai send data to Aenc
    {
        HI_ERR_AENC("hAenc(%d) work at Attatch mode.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    s32Ret = AENCSentInputData(pstAencChan, &stAOFrame);
    HI_MPI_AENC_RetUserErr(s32Ret, hAenc);

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_U32 AENC_GetInBufDataSize(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan;
    HI_U32 u32InBufDataSize = 0;

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    u32InBufDataSize = (HI_U32)AENCGetInBufDataSize(&pstAencChan->sInPcmBuf);

    AENC_CHAN_UNLOCK(hAenc);
    return u32InBufDataSize;
}

/* To obtain audio stream from an audio encoder. */
HI_S32 AENC_ReceiveStream(HI_HANDLE hAenc, AENC_STREAM_S* pstStream, HI_U32 u32TimeoutMs)
{
    HI_S32 s32Ret;
    HI_U32 u32SleepCnt;
    AENC_CHAN_S* pstAencChan;
    AENC_OUTPUTBUF_S* pstOutBufUnit;
    struct timespec stSlpTm;

#ifdef HI_PROC_SUPPORT
    static FILE* fEstream = NULL;
#endif

    CHECK_AENC_NULL_PTR(pstStream);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    AENC_DbgCountTryReceiveStream(hAenc);

    pstStream->pu8Data  = HI_NULL;
    pstStream->u32Bytes = 0;

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_NULL == pstAencChan->pstAencInfo)
    {
        HI_ERR_AENC("pstAencChan->pstAencInfo is NULL(hAenc = 0x%x)\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_NULL_PTR;
    }

    if (!pstAencChan->bStart)
    {
        HI_ERR_AENC("hAenc(%d) not start.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    s32Ret = AENCReceiveOutBufUnit(&pstAencChan->sOutStreamBuf, &pstOutBufUnit);
    if (HI_SUCCESS != s32Ret)
    {
        if (0 == u32TimeoutMs)
        {
            s32Ret = HI_ERR_AENC_OUT_BUF_EMPTY;
            HI_MPI_AENC_RetUserErr(s32Ret, hAenc);
        }
        else
        {
            for (u32SleepCnt = 0; u32SleepCnt < u32TimeoutMs; u32SleepCnt++)
            {
                AENC_CHAN_UNLOCK(hAenc);
                stSlpTm.tv_sec = 0;
                stSlpTm.tv_nsec = 1000 * 1000;
                if(0 != nanosleep(&stSlpTm, NULL))
                {
                    HI_ERR_AENC("nanosleep err.\n");
                }
                AENC_CHAN_LOCK(hAenc);
                s32Ret = AENCReceiveOutBufUnit(&pstAencChan->sOutStreamBuf, &pstOutBufUnit);
                if (HI_SUCCESS == s32Ret)
                {
                    break;
                }
            }
            if (HI_SUCCESS != s32Ret)
            {
                s32Ret = HI_ERR_AENC_OUT_BUF_EMPTY;
                HI_MPI_AENC_RetUserErr(s32Ret, hAenc);
            }
        }
    }

    pstStream->pu8Data  = pstOutBufUnit->pu8Data;
    pstStream->u32Bytes = pstOutBufUnit->u32Bytes;
    pstStream->u32PtsMs = pstOutBufUnit->u32PtsMs;

#ifdef HI_PROC_SUPPORT
    if ( pstAencChan->pstAencInfo->enEsCtrlState == AENC_CMD_CTRL_START )
    {
        if (!fEstream)
        {
            fEstream = fopen(pstAencChan->pstAencInfo->filePath, "wb");
            if (!fEstream)
            {
                HI_ERR_AENC("can not open file (%s)\n", pstAencChan->pstAencInfo->filePath);
            }
        }
        if (fEstream)
        {
            HI_S32 s32Len = fwrite(pstStream->pu8Data, 1, pstStream->u32Bytes, fEstream);
            if (pstStream->u32Bytes != s32Len)
            {
                HI_ERR_AENC("write (%s) failed\n", pstAencChan->pstAencInfo->filePath);
                fclose(fEstream);
                fEstream = HI_NULL;
                pstAencChan->pstAencInfo->enEsCtrlState = AENC_CMD_CTRL_STOP;
            }
        }
    }
    if ( pstAencChan->pstAencInfo->enEsCtrlState == AENC_CMD_CTRL_STOP )
    {
        if (fEstream)
        {
            fclose(fEstream);
            fEstream = HI_NULL;
        }
    }
#endif

    AENC_DbgCountReceiveStream(hAenc);

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_S32 AENC_ReleaseStream(HI_U32 hAenc, const AENC_STREAM_S* pstStream)
{
    HI_S32 s32Ret;
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_NULL_PTR(pstStream);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    AENC_DbgCountTryReleaseStream(hAenc);

    pstAencChan = g_pstAencChan[hAenc];
    if (HI_FALSE == pstAencChan->beAssigned)
    {
        HI_ERR_AENC("hAenc(%d) not Assigned.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_OPEN;
    }

    if (!pstAencChan->bStart)
    {
        HI_ERR_AENC("hAenc(%d) not start.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    /* output buf keep line, must fist in last out*/
    s32Ret = AENCReleaseCurrentOutBufUnit(&pstAencChan->sOutStreamBuf, pstStream);
    pstAencChan->pstAencInfo->u32OutFrameRIdx = pstAencChan->sOutStreamBuf.u32ReadIdx;

    AENC_DbgCountReleaseStream(hAenc);
    AENC_CHAN_UNLOCK(hAenc);
    return s32Ret;
}

static HI_S32 AENC_SendInnerBuffer(AENC_CHAN_S* pstAencChan)
{
    HI_S32 nRet = HI_FAILURE;
    HI_UNF_AO_FRAMEINFO_S stSendFrame = { 0 };
    HI_UNF_AO_FRAMEINFO_S stOrgFrame  = { 0 };

    AENC_CHAN_TRY_LOCK(pstAencChan->u32ChID);

    if (ANEC_SOURCE_AI == pstAencChan->stAttach.eType)
    {
#if  0
#ifdef HI_AENC_AI_SUPPORT
        if (HI_SUCCESS == HI_MPI_AI_AcquireFrame(pstAencChan->stAttach.hSource, &stOrgFrame))
        {
            memcpy(&stSendFrame, &stOrgFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));
            if (HI_SUCCESS == AENCSentInputData(pstAencChan, &stSendFrame))
            {
                nRet = HI_MPI_AI_ReleaseFrame(pstAencChan->stAttach.hSource, &stOrgFrame);
            }
        }
#endif
#endif
    }
    else if (ANEC_SOURCE_CAST == pstAencChan->stAttach.eType)
    {
        if (HI_SUCCESS == HI_MPI_AO_SND_AcquireCastFrame(pstAencChan->stAttach.hSource, &stOrgFrame))
        {
            memcpy(&stSendFrame, &stOrgFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));
            if (HI_SUCCESS == AENCSentInputData(pstAencChan, &stSendFrame))
            {
                nRet = HI_MPI_AO_SND_ReleaseCastFrame(pstAencChan->stAttach.hSource, &stOrgFrame);
            }
        }
    }
    else if (ANEC_SOURCE_VIRTRACK == pstAencChan->stAttach.eType)
    {
        if (HI_SUCCESS == HI_MPI_AO_Track_AcquireFrame(pstAencChan->stAttach.hSource, &stOrgFrame, 0))
        {
            memcpy(&stSendFrame, &stOrgFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));
            if (HI_SUCCESS == AENCSentInputData(pstAencChan, &stSendFrame))
            {
                nRet = HI_MPI_AO_Track_ReleaseFrame(pstAencChan->stAttach.hSource, &stOrgFrame);
            }
        }
    }

    AENC_CHAN_UNLOCK(pstAencChan->u32ChID);
    return nRet;
}

static HI_VOID* AENC_Thread(HI_VOID* arg)
{
    HI_HANDLE hAenc = (HI_HANDLE)((HI_U8*)arg - (HI_U8*)HI_NULL);
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;
    struct timespec stSlpTm;

    pstAencChan = g_pstAencChan[hAenc];

    while (pstAencChan->AencThreadRun)
    {
        if ((HI_TRUE == pstAencChan->beAssigned) && (HI_TRUE == pstAencChan->bStart))
        {
            if (HI_INVALID_HANDLE != pstAencChan->stAttach.hSource)
            {
                (HI_VOID)AENC_SendInnerBuffer(pstAencChan);
            }

            s32Ret = AENC_Pull(hAenc);
            if (HI_SUCCESS != s32Ret)
            {
                stSlpTm.tv_sec = 0;
                stSlpTm.tv_nsec = AENC_SYS_SLEEP_TIME * 1000;
                if(0 != nanosleep(&stSlpTm, NULL))
                {
                    HI_ERR_AENC("nanosleep err.\n");
                }
            }
        }
        else
        {
            stSlpTm.tv_sec = 0;
            stSlpTm.tv_nsec = AENC_SYS_SLEEP_TIME * 1000;
            if(0 != nanosleep(&stSlpTm, NULL))
            {
                HI_ERR_AENC("nanosleep err.\n");
            }
        }
    }

    return HI_NULL;
}

HI_S32 AENC_SetEnable(HI_HANDLE hAenc, HI_BOOL bEnable)
{
    AENC_CHAN_S* pstAencChan;
    HI_S32 nRet;

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_TRUE == bEnable)
    {
        pstAencChan->bStart = HI_TRUE;
    }
    else
    {
        if (!pstAencChan->bStart)
        {
            AENC_CHAN_UNLOCK(hAenc);
            return HI_SUCCESS;
        }

        nRet = AENCResetBuf(hAenc, 3);
        if (nRet != HI_SUCCESS)
        {
            AENC_CHAN_UNLOCK(hAenc);
            HI_ERR_AENC("call AENC_ResetBuf failed:%#x.\n", nRet);
            return nRet;
        }
        pstAencChan->bStart = HI_FALSE;
    }
    pstAencChan->pstAencInfo->bAencWorkEnable = pstAencChan->bStart;  // update proc info

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_S32 AENC_AttachInput(HI_HANDLE hAenc, HI_HANDLE hSource)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_INVALID_HANDLE != pstAencChan->stAttach.hSource)
    {
        HI_ERR_AENC("hAenc(%d) had been attach.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    if ((hSource & 0xffff0000) == (HI_ID_AO << 16))
    {
        if ((hSource & 0xff00) == (HI_ID_MASTER_SLAVE_TRACK << 8))
        {
            pstAencChan->stAttach.eType   = ANEC_SOURCE_VIRTRACK;
            pstAencChan->stAttach.hSource = hSource;
            HI_INFO_AENC("Aenc attach Virtual Track(0x%x)\n", hSource);
        }
        else if ((hSource & 0xff00) == (HI_ID_CAST << 8))
        {
            pstAencChan->stAttach.eType   = ANEC_SOURCE_CAST;
            pstAencChan->stAttach.hSource = hSource;
            HI_INFO_AENC("Aenc attach Cast(0x%x)\n", hSource);
        }
        memcpy( &pstAencChan->pstAencInfo->stAttach, &pstAencChan->stAttach, sizeof(AENC_INFO_ATTACH_S));
    }
#ifdef HI_AENC_AI_SUPPORT
    else if ((hSource & 0xffff0000) == (HI_ID_AI << 16))
    {
        pstAencChan->stAttach.eType   = ANEC_SOURCE_AI;
        pstAencChan->stAttach.hSource = hSource;
        HI_INFO_AENC("Aenc attach AI(0x%x)\n", hSource);
        memcpy(&pstAencChan->pstAencInfo->stAttach, &pstAencChan->stAttach, sizeof(AENC_INFO_ATTACH_S));
    }
#endif

    if (HI_INVALID_HANDLE == pstAencChan->stAttach.hSource)
    {
        HI_ERR_AENC("hAenc(%d) invalid hSource(0x%x).\n", hAenc, hSource);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CH_NOT_SUPPORT;
    }

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_S32 AENC_GetAttachSrc(HI_HANDLE hAenc, HI_HANDLE* hSrc)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_NULL_PTR(hSrc);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_INVALID_HANDLE == pstAencChan->stAttach.hSource)
    {
        HI_ERR_AENC("hAenc(%d) had been dettach.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_FAILURE;
    }

    *hSrc = pstAencChan->stAttach.hSource;

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_S32 AENC_DetachInput(HI_HANDLE hAenc)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_INVALID_HANDLE == pstAencChan->stAttach.hSource)
    {
        HI_WARN_AENC("hAenc(%d) had been dettach.\n", hAenc);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_SUCCESS;
    }

    pstAencChan->stAttach.hSource = HI_INVALID_HANDLE;
    pstAencChan->stAttach.eType = ANEC_SOURCE_BUTT;

    HI_INFO_AENC("Aenc Dettach Source.\n");

    AENC_CHAN_UNLOCK(hAenc);
    return HI_SUCCESS;
}

HI_S32 AENC_SetConfigEncoder(HI_HANDLE hAenc, HI_VOID* pstConfigStructure)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AENC_CHAN_S* pstAencChan = HI_NULL_PTR;
    HI_HA_ENCODE_S* hHaEntry;

    CHECK_AENC_NULL_PTR(pstConfigStructure);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    hHaEntry = (HI_HA_ENCODE_S*)(pstAencChan->hHaEntry);
    if (hHaEntry && hHaEntry->EncodeSetConfig)
    {
        s32Ret = (HI_S32)hHaEntry->EncodeSetConfig(pstAencChan->hEncoder, pstConfigStructure);
        if (HA_ErrorNone != s32Ret)
        {
            HI_ERR_AENC("EncodeSetConfig failed(0x%x)\n", s32Ret);
        }
        else
        {
            s32Ret = HI_SUCCESS;
        }
    }

    AENC_CHAN_UNLOCK(hAenc);
    return s32Ret;
}

HI_S32 AENC_SetAttr(HI_HANDLE hAenc, const HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    HI_S32 s32Ret;
    AENC_CHAN_S* pstAencChan;
    AENC_ATTR_S stAencAttr;

    CHECK_AENC_NULL_PTR(pstAencAttr);
    CHECK_AENC_OPEN_FORMAT(pstAencAttr->sOpenParam.u32DesiredSampleRate, pstAencAttr->sOpenParam.u32DesiredOutChannels,
                           pstAencAttr->sOpenParam.s32BitPerSample, pstAencAttr->sOpenParam.bInterleaved);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    stAencAttr.u32CodecID    = pstAencAttr->enAencType;
    stAencAttr.sOpenParam    = pstAencAttr->sOpenParam;
    stAencAttr.u32InBufSize = AENC_DEFAULT_INPUT_BUFFER_SIZE;
    stAencAttr.u32OutBufNum = AENC_DEFAULT_OUTBUF_NUM;

    pstAencChan = g_pstAencChan[hAenc];

    if (HI_TRUE == pstAencChan->bStart)
    {
        HI_ERR_AENC("First stop aenc before set attr!\n");
        AENC_CHAN_UNLOCK(hAenc);
        return HI_FAILURE;
    }

    (HI_VOID)AENCDestroyEncoder(pstAencChan);

    s32Ret = AENCCreateEncoder(pstAencChan, &stAencAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("AENCCreateEncoder failed(0x%x)\n", s32Ret);
        AENC_CHAN_UNLOCK(hAenc);
        return HI_ERR_AENC_CREATECH_FAIL;
    }

    pstAencChan->pstAencInfo->u32BitWidth   = pstAencChan->u32BitPerSample;
    pstAencChan->pstAencInfo->u32SampleRate = pstAencChan->u32DesiredSampleRate;
    pstAencChan->pstAencInfo->u32Channels = pstAencChan->u32DesiredOutChannels;

    AENC_CHAN_UNLOCK(hAenc);

    return HI_SUCCESS;
}

HI_S32 AENC_GetAttr(HI_HANDLE hAenc, HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    AENC_CHAN_S* pstAencChan;

    CHECK_AENC_NULL_PTR(pstAencAttr);

    CHECK_AENC_HANDLE(hAenc);
    AENC_CHAN_LOCK(hAenc);
    CHECK_AENC_CHN_OPEN_RET(hAenc);

    pstAencChan = g_pstAencChan[hAenc];

    pstAencAttr->enAencType = pstAencChan->u32CodecID;
    memcpy(&pstAencAttr->sOpenParam, &pstAencChan->stEncoderInfo.stOpenParam, sizeof(HI_HAENCODE_OPENPARAM_S));

    AENC_CHAN_UNLOCK(hAenc);

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
