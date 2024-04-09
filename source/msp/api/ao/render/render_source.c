/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_source.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <string.h>
#include <stdlib.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"
#include "hi_mpi_ao.h"

#include "render_common.h"
#include "render_buffer.h"
#include "pts_queue.h"

#include "ipc_client.h"
#include "ao_isb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)
#define line()  HI_WARN_AO("%s line:%d\n", __func__, __LINE__)

#define MS12_TRACK_MASK          (0x88)
#define RENDER_TRACK_MASK        (0xff)
#define RENDER_TRACK_MAXNUM      (0x0f)
#define RENDER_TRACK_IDOFFSET    (0x08)
#define MAX_PTS_FILE_PATH_LEN    (40)
#define VALIDATE_PTS_WRITE_LEN   (22)
#define INVALIDATE_PTS_WRITE_LEN (11)
#define RENDER_FORMAT_ATMOS      (0x1b0)

typedef struct
{
    HI_BOOL       bInited;
    HI_BOOL       bIDAlloced[RENDER_TRACK_MAXNUM];
    HI_BOOL       bTrackCreated[RENDER_TRACK_MAXNUM];
} SOURCE_IDM_S;


static SOURCE_MANAGER_S* g_pstSourceManager = HI_NULL;
static RENDER_MANAGER_S* g_pstSourceRenderManager = HI_NULL;

static SOURCE_IDM_S g_stMediaTrackIDM =
{
    .bInited = HI_FALSE,
};

#define CHECK_AND_GET_SOURCEIDFROMTRACKID(u32TrackID, enSourceID) \
    do { \
        if (((u32TrackID & 0xf000) != (HI_ID_RENDER_TRACK << 12)) || \
            (SOURCE_ID_BUTT <= (u32TrackID & RENDER_TRACK_MASK))) \
        { \
            HI_ERR_AO("Invalid TrackID(0x%x) failed\n", u32TrackID); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
        enSourceID = (SOURCE_ID_E)(u32TrackID & RENDER_TRACK_MASK); \
    } while(0)

#define CHECK_AND_GET_SOURCEIDFROMBUFID(enBufId, enSourceID) \
    do { \
        if (enBufId >= HI_MPI_AO_BUF_ID_BUTT) \
        { \
            HI_ERR_AO("Invalid BufID(%d) failed\n", enBufId); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
        enSourceID = (HI_MPI_AO_BUF_ID_ES_MAIN == enBufId) ? SOURCE_ID_MAIN : SOURCE_ID_ASSOC; \
    } while(0)

#define GET_SOURCEIDFROMTRACKID(u32TrackID, enSourceID) \
    do { \
        if (((u32TrackID & 0xf000) != (HI_ID_RENDER_TRACK << 12)) || \
            (SOURCE_ID_BUTT <= (u32TrackID & RENDER_TRACK_MASK))) \
        { \
            HI_ERR_AO("Invalid TrackID(0x%x) failed\n", u32TrackID); \
            enSourceID = SOURCE_ID_BUTT; \
        } \
        else \
        { \
            enSourceID = (SOURCE_ID_E)(u32TrackID & RENDER_TRACK_MASK); \
        } \
    } while(0)

#define CHECK_TRACK_SYNCMODE(enSyncMode) \
    do { \
        if (HI_MPI_AO_TRACK_SYNCMODE_BUTT == enSyncMode) \
        { \
            HI_ERR_AO("Invalid Sync Mode(%d)\n", enSyncMode); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
    } while(0)

#ifdef DPT
#define CHECK_TRACK_ABSLUTEPRECIVOLUME(absintvolume, absdecvolume)  \
    do                                              \
    {                                               \
        if((absintvolume > 0 && absdecvolume < 0) || (absintvolume < 0 && absdecvolume > 0))  \
        {                                           \
            HI_ERR_AO("invalid precision volume decimal\n");  \
            return HI_ERR_AO_INVALID_PARA;          \
        }                                           \
        if ((absdecvolume < -AO_MIN_DECIMALVOLUME_AMPLIFICATION) || (absdecvolume > AO_MIN_DECIMALVOLUME_AMPLIFICATION) || (0 != absdecvolume % 125))  \
        {                                           \
            HI_ERR_AO("invalid precision volume decimal part(%d), min(%d), max(%d), step(125)\n", absdecvolume, -AO_MIN_DECIMALVOLUME_AMPLIFICATION, AO_MIN_DECIMALVOLUME_AMPLIFICATION);   \
            return HI_ERR_AO_INVALID_PARA;          \
        }     \
        if ((absintvolume < AO_MIN_ABSOLUTEVOLUMEEXT) || (absintvolume > AO_MAX_ABSOLUTEVOLUMEEXT))   \
        {                                           \
            HI_ERR_AO("invalid precision volume, min(%d), max(%d)\n", AO_MIN_ABSOLUTEVOLUMEEXT, AO_MAX_ABSOLUTEVOLUMEEXT);   \
            return HI_ERR_AO_INVALID_PARA;          \
        }                                           \
        if(absdecvolume < 0)  \
        {     \
            if (absintvolume - 1 < AO_MIN_ABSOLUTEVOLUMEEXT)  \
            {                                       \
                HI_ERR_AO("invalid precision volume, min(%d)\n", AO_MIN_ABSOLUTEVOLUMEEXT);   \
                return HI_ERR_AO_INVALID_PARA;      \
            } \
        }     \
        if(absdecvolume > 0)  \
        {     \
            if (absintvolume + 1 > AO_MAX_ABSOLUTEVOLUMEEXT)  \
            {                                       \
                HI_ERR_AO("invalid precision volume, max(%d)\n", AO_MAX_ABSOLUTEVOLUMEEXT);   \
                return HI_ERR_AO_INVALID_PARA;      \
            } \
        }     \
    } while (0)
#endif

static HI_BOOL CheckIsSourceDuplicate(SOURCE_ID_E enSourceID)
{
    if (HI_NULL != g_pstSourceManager && HI_NULL != g_pstSourceManager->pstSource[enSourceID])
    {
        return g_pstSourceManager->pstSource[enSourceID]->bDual;
    }

    return HI_FALSE;
}

static HI_BOOL CheckIsMediaTrack(HI_HANDLE hTrack)
{
    SOURCE_ID_E enSourceID;

    GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    return (HI_BOOL)((SOURCE_ID_MAIN == enSourceID) ||
                     (SOURCE_ID_ASSOC == enSourceID) ||
                     (SOURCE_ID_EXTDEC == enSourceID));
}

static HI_BOOL CheckIsMediaSource(SOURCE_ID_E enSourceID)
{
    return (HI_BOOL)((SOURCE_ID_MAIN == enSourceID) ||
                     (SOURCE_ID_ASSOC == enSourceID) ||
                     (SOURCE_ID_EXTDEC == enSourceID));
}

static HI_BOOL CheckIsMediaTrackIDApplied(HI_HANDLE hTrack)
{
    if (0 == ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM))
    {
        HI_ERR_AO("Invalid TrackID(0x%x)\n", hTrack);
        return HI_FALSE;
    }

    return g_stMediaTrackIDM.bIDAlloced[((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1];
}

static HI_BOOL CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    if (0 == ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM))
    {
        HI_ERR_AO("Invalid TrackID(0x%x)\n", hTrack);
        return HI_FALSE;
    }

    return g_stMediaTrackIDM.bTrackCreated[((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1];
}

static HI_UNF_SND_TRACK_TYPE_E GetTrackTypeFromSourceID(SOURCE_ID_E enSourceID)
{
    if (SOURCE_ID_MAIN == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_MASTER;
    }
    else if (SOURCE_ID_EXTDEC == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_MASTER;
    }
    else if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_OTTSOUND;
    }
    else if (SOURCE_ID_SYSTEM == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_SYSTEMAUDIO;
    }
    else if (SOURCE_ID_APP == enSourceID)
    {
        return HI_UNF_SND_TRACK_TYPE_APPAUDIO;
    }
    else
    {
        HI_ERR_AO("Unknown source id (0x%x)\n", enSourceID);
    }

    return HI_UNF_SND_TRACK_TYPE_BUTT;
}

static SOURCE_ID_E GetSourceIDFromTrackType(HI_UNF_SND_TRACK_TYPE_E enType)
{
    if ((HI_UNF_SND_TRACK_TYPE_MASTER == enType) ||
        (HI_UNF_SND_TRACK_TYPE_SLAVE == enType))
    {
        return SOURCE_ID_MAIN;
    }
    else if (HI_UNF_SND_TRACK_TYPE_OTTSOUND == enType)
    {
        return SOURCE_ID_OTTSOUND;
    }
    else if (HI_UNF_SND_TRACK_TYPE_SYSTEMAUDIO == enType)
    {
        return SOURCE_ID_SYSTEM;
    }
    else if (HI_UNF_SND_TRACK_TYPE_APPAUDIO == enType)
    {
        return SOURCE_ID_APP;
    }
    else
    {
        HI_ERR_AO("Invalid Track Type(0x%x)\n", enType);
    }

    return SOURCE_ID_BUTT;
}

static SOURCE_ID_E GetSourceIDFromSourceType(HI_MPI_RENDER_SOURCE_TYPE_E enType)
{
    if (HI_MPI_RENDER_SOURCE_TYPE_MAIN == enType)
    {
        return SOURCE_ID_MAIN;
    }
    else if (HI_MPI_RENDER_SOURCE_TYPE_ASSOC == enType)
    {
        return SOURCE_ID_ASSOC;
    }
    else if (HI_MPI_RENDER_SOURCE_TYPE_EXTMAIN == enType)
    {
        return SOURCE_ID_EXTDEC;
    }
    else if (HI_MPI_RENDER_SOURCE_TYPE_OTTSOUND == enType)
    {
        return SOURCE_ID_OTTSOUND;
    }
    else if (HI_MPI_RENDER_SOURCE_TYPE_SYSTEMAUDIO == enType)
    {
        return SOURCE_ID_SYSTEM;
    }
    else if (HI_MPI_RENDER_SOURCE_TYPE_APPAUDIO == enType)
    {
        return SOURCE_ID_APP;
    }
    else
    {
        HI_ERR_AO("Invalid Track Type(0x%x)\n", enType);
    }

    return SOURCE_ID_BUTT;
}

static HI_U32 GetTrackIDFromSourceID(SOURCE_ID_E enSourceID)
{
    /*
      define of Track Handle :
      bit31                                                                    bit0
        |<----   16bit --------->|<--   4bit  -->|<--  4bit  -->|<---  8bit  --->|
        |------------------------------------------------------------------------|
        |      HI_MOD_ID_E       | render defined | idm defined  |     chnID     |
        |------------------------------------------------------------------------|
      */

    return (HI_ID_AO << 16) | (HI_ID_RENDER_TRACK << 12) | enSourceID;
}

static HI_VOID RecordPauseDelay(SOURCE_S* pstSource)
{
    if (HI_NULL == pstSource)
    {
        return;
    }

    if ((SOURCE_ID_MAIN != pstSource->enSourceID) && (SOURCE_ID_EXTDEC != pstSource->enSourceID))
    {
        return;
    }

    if ((SOURCE_ID_MAIN == pstSource->enSourceID) && (0 == pstSource->u32StreamConsumedBytes))
    {
        return;
    }

    pstSource->u32PauseDelay = (*((HI_U32*)g_pstSourceRenderManager->pstEngineManger->stDelayMapAttr.pVirAddr) >> 16)
                                + pstSource->u32DecoderPcmDelay + pstSource->u32DecoderStaticDelay;
    if (pstSource->u32SinkPts > pstSource->u32PauseDelay)
    {
        pstSource->u32PausePts = pstSource->u32SinkPts - pstSource->u32PauseDelay;
    }
    else
    {
        pstSource->u32PausePts = pstSource->u32PreDecodePts;
    }

    HI_WARN_AO("Track Delay = %d\n", *((HI_U32*)g_pstSourceRenderManager->pstEngineManger->stDelayMapAttr.pVirAddr) >> 16);
    HI_WARN_AO("u32DecoderPcmDelay = %d, u32DecoderStaticDelay = %d\n", pstSource->u32DecoderPcmDelay, pstSource->u32DecoderStaticDelay);
    HI_WARN_AO("RecordPauseDelay Calc, pstSource->u32PauseDelay = %d, pts = %d\n", pstSource->u32PauseDelay, pstSource->u32PausePts);
}

static HI_VOID MediaTrackIDMInit(HI_VOID)
{
    CHANNEL_TRACE();

    if (HI_FALSE == g_stMediaTrackIDM.bInited)
    {
        memset(&g_stMediaTrackIDM, 0, sizeof(SOURCE_IDM_S));
        g_stMediaTrackIDM.bInited = HI_TRUE;
    }
}

static HI_S32 MediaTrackIDMAlloc(SOURCE_ID_E enSourceID, HI_HANDLE* phTrack)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if (HI_FALSE == g_stMediaTrackIDM.bIDAlloced[u32ID])
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Too many render track(0x%x)!\n", u32ID);
        return HI_FAILURE;
    }

    g_stMediaTrackIDM.bIDAlloced[u32ID] = HI_TRUE;
    g_stMediaTrackIDM.bTrackCreated[u32ID] = HI_FALSE;

    *phTrack = (HI_ID_AO << 16) | (HI_ID_RENDER_TRACK << 12) | ((u32ID + 1) << RENDER_TRACK_IDOFFSET | enSourceID);

    HI_WARN_AO("Alloc id (0x%x)!\n", *phTrack);

    return HI_SUCCESS;
}

static HI_S32 MediaTrackIDMDeAlloc(HI_HANDLE hTrack)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    if (0 == ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM))
    {
        HI_ERR_AO("Invalid TrackID(0x%x)\n", hTrack);
        return HI_FAILURE;
    }

    u32ID = ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1;

    HI_INFO_AO("DeAlloc id (0x%x)!\n", u32ID);

    g_stMediaTrackIDM.bIDAlloced[u32ID] = HI_FALSE;

    return HI_SUCCESS;
}

static HI_VOID MediaTrackIDMDestory(HI_HANDLE hTrack)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    if (0 == ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM))
    {
        HI_ERR_AO("Invalid TrackID(0x%x)\n", hTrack);
        return;
    }

    u32ID = ((hTrack >> RENDER_TRACK_IDOFFSET) & RENDER_TRACK_MAXNUM) - 1;

    CHANNEL_PRINTF("Release ID(0x%x)\n", u32ID);

    if (HI_TRUE != g_stMediaTrackIDM.bIDAlloced[u32ID])
    {
        HI_ERR_AO("Track(0x%x) ID is not alloc!\n", hTrack);
    }

    g_stMediaTrackIDM.bTrackCreated[u32ID] = HI_FALSE;
}

static HI_BOOL SourceServerCheckIsInstantiated(SOURCE_ID_E enSourceID)
{
    return (HI_BOOL)(HI_NULL != g_pstSourceManager->pstSource[enSourceID]);
}

static HI_S32 SourceSetDuplicateStatus(SOURCE_ID_E enSourceID, HI_BOOL bDuplicate)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceSetDuplicateStatus enSourceID = %d, bDuplicate = %d\n", enSourceID, bDuplicate);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bDual = bDuplicate;

    return HI_SUCCESS;
}

static HI_S32 SourceCreatePtsQueue(SOURCE_ID_E enSourceID, HI_VOID* pRBuffer, HI_VOID** pPtsQueue, HI_BOOL bServer)
{
    HI_S32 s32Ret;
    HI_VOID* hISB = HI_NULL;

    CHANNEL_TRACE();

    if ((SOURCE_ID_MAIN != enSourceID) && (SOURCE_ID_ASSOC != enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = (HI_TRUE == bServer) ? RENDER_ServerBuffer_GetISBHandle(pRBuffer, &hISB) : RENDER_ClientBuffer_GetISBHandle(pRBuffer, &hISB);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("RENDER_(%s)Buffer_GetISBHandle failed(0x%x)!", (HI_TRUE == bServer) ? "Server" : "Client", s32Ret);
        return s32Ret;
    }

    s32Ret = PTSQUEUE_Create(hISB, pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("%s PTSQUEUE_Create failed(0x%x)!", (HI_TRUE == bServer) ? "Server" : "Client");
        return s32Ret;
    }

    if (HI_TRUE == bServer)
    {
        HI_U32 u32Idx;
        PTS_QUEUE_S* pstPtsQue = (PTS_QUEUE_S*)(*pPtsQueue);
        for (u32Idx = 0; u32Idx < MAX_STORED_PTS_NUM; u32Idx++)
        {
            pstPtsQue->astPtsAttr[u32Idx].u32PtsMs = HI_INVALID_PTS;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 SourceDestoryPtsQueue(SOURCE_ID_E enSourceID, HI_VOID* pPtsQueue)
{
    CHANNEL_TRACE();

    if ((SOURCE_ID_MAIN != enSourceID) && (SOURCE_ID_ASSOC != enSourceID))
    {
        return HI_SUCCESS;
    }

    if (HI_NULL != pPtsQueue)
    {
        return PTSQUEUE_Detroy(pPtsQueue);
    }

    return HI_FAILURE;
}

static HI_S32 SourceGetExtRenderOutBuf(SOURCE_ID_E enSourceID, HI_VOID** ppROutBuffer)
{
    *ppROutBuffer = g_pstSourceRenderManager->pstEngineManger->pROutBuffer[enSourceID];
    if (HI_NULL == *ppROutBuffer)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 SourceAllocID(SOURCE_ID_E enSourceID, HI_HANDLE* phTrack)
{
    MediaTrackIDMInit();

    return MediaTrackIDMAlloc(enSourceID, phTrack);
}

static HI_S32 SourceDeallocID(HI_HANDLE hTrack)
{
    return MediaTrackIDMDeAlloc(hTrack);
}

static HI_S32 SourceCreate(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    HI_VOID* pROutBuffer;
    SOURCE_S* pstSource;

    pstSource = (SOURCE_S*)malloc(sizeof(SOURCE_S));
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Souce malloc failed!\n");
        return HI_FAILURE;
    }

    memset(pstSource, 0, sizeof(SOURCE_S));

    pstSource->enState = SOURCE_STATE_IDLE;
    pstSource->enSourceID = enSourceID;
    pstSource->u32CurStreamPts = HI_INVALID_PTS;
    pstSource->bMixing = HI_TRUE;
    pstSource->bDecoding = HI_TRUE;
    pstSource->bEnableMixer = HI_TRUE;
    pstSource->bEnableDecoder = HI_TRUE;
    pstSource->bWorking = HI_FALSE;
    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->u32PreDecodePts = HI_INVALID_PTS;
    pstSource->bDataValid = HI_FALSE;
    pstSource->bDoWipeInvalidPTS = HI_FALSE;
    pstSource->bFirstTimeStarted = HI_TRUE;
    pstSource->bRepeatEnable = HI_FALSE;

    s32Ret = SourceGetExtRenderOutBuf(enSourceID, &pROutBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceGetExtRenderOutBuf, s32Ret);
        goto ERR_BUFFER_INIT;
    }

    s32Ret = RENDER_ServerBuffer_Init(&pstSource->pRBuffer, enSourceID, RENDER_BUFFER_SIZE, pROutBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_Init, s32Ret);
        goto ERR_BUFFER_INIT;
    }

    s32Ret = SourceCreatePtsQueue(enSourceID, pstSource->pRBuffer, &pstSource->pPtsQueue, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceCreatePtsQueue, s32Ret);
        goto ERR_PTSQUEUE_CREATE;
    }

    g_pstSourceManager->pstSource[pstSource->enSourceID] = pstSource;

    return HI_SUCCESS;

ERR_PTSQUEUE_CREATE:
    s32Ret = RENDER_ServerBuffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_DeInit, s32Ret);
    }

ERR_BUFFER_INIT:
    free(pstSource);

    return HI_FAILURE;
}

HI_S32 SourceDestroyTrack(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    if (SOURCE_ID_BUTT <= enSourceID)
    {
        HI_ERR_AO("enSourceID(%d) is not available.\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_TRUE == CheckIsMediaSource(enSourceID))
    {
        s32Ret = SourceDestoryPtsQueue(enSourceID, pstSource->pPtsQueue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SourceDestoryPtsQueue, s32Ret);
            return HI_ERR_AO_INVALID_PARA;
        }
    }

    s32Ret = RENDER_ServerBuffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_DeInit, s32Ret);
        return HI_ERR_AO_INVALID_PARA;
    }

    free(pstSource);
    g_pstSourceManager->pstSource[enSourceID] = HI_NULL;

    return s32Ret;
}

HI_S32  SourceStartTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_RUNNING;

    return HI_SUCCESS;
}

HI_S32  SourceStopTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    HI_WARN_AO("Stop track %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_STOP;

    pstSource->u32StreamConsumedBytes = 0;
    pstSource->u32DecodeLeftBytes = 0;
    pstSource->u32CurStreamPts = HI_INVALID_PTS;
    pstSource->bMixing = HI_TRUE;
    pstSource->bDecoding = HI_TRUE;
    pstSource->bEnableMixer = HI_TRUE;
    pstSource->bEnableDecoder = HI_TRUE;
    pstSource->bEosFlag = HI_FALSE;
    pstSource->bEosState = HI_FALSE;
    pstSource->bWorking = HI_FALSE;

    pstSource->u32SinkPts = HI_INVALID_PTS;
    pstSource->bSinkStarted = HI_FALSE;
    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->u32PreDecodePts = HI_INVALID_PTS;
    pstSource->bDataValid = HI_FALSE;
    pstSource->u32DecoderPcmDelay = 0;
    pstSource->u32GetBufTryCnt = 0;
    pstSource->u32GetBufOkCnt = 0;
    pstSource->u32PutBufTryCnt = 0;
    pstSource->u32PutBufOkCnt = 0;
    pstSource->u32SendStreamTryCnt = 0;
    pstSource->u32SendStreamOkCnt = 0;
    pstSource->u32SendTrackDataTryCnt = 0;
    pstSource->u32SendTrackDataOkCnt = 0;
    pstSource->u32DecoderStaticDelay = 0;
    pstSource->u32AcquireSize = 0;
    pstSource->bFirstTimeStarted = HI_TRUE;
    pstSource->u32InBufUsed = 0;
    pstSource->u32InBufSize = 0;
    pstSource->u32InBufUsedPercent = 0;
    pstSource->u32TotDecodeFrame = 0;

    pstSource->u32SeekFrameTimeout = 0;
    pstSource->bDoWipeInvalidPTS = HI_FALSE;
    pstSource->bRepeatEnable = HI_FALSE;
    pstSource->u32PauseDelayms = 0;
    pstSource->u32AddMediaMixerMuteMs = 0;
    pstSource->u32AddMediaPauseMuteMs = 0;
    pstSource->u32ExtraTargetPtsMs = 0;

    if ((SOURCE_ID_MAIN == pstSource->enSourceID) || (SOURCE_ID_ASSOC == pstSource->enSourceID))
    {
        g_pstSourceManager->enPTSReportSource = SOURCE_ID_BUTT;
        PTSQUEUE_Reset(pstSource->pPtsQueue);
    }

    RENDER_ServerBuffer_Reset(pstSource->pRBuffer);

    return HI_SUCCESS;
}

HI_S32  SourcePauseTrack(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    HI_WARN_AO("Pause track %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enState = SOURCE_STATE_PAUSE;

    RecordPauseDelay(pstSource);

    return HI_SUCCESS;
}

HI_S32 SourceFlushTrack(SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource;

    HI_WARN_AO("Flush track %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_ServerBuffer_Reset(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_Reset, s32Ret);
    }

    if ((SOURCE_ID_MAIN == enSourceID) || (SOURCE_ID_ASSOC == enSourceID))
    {
        s32Ret |= PTSQUEUE_Reset(pstSource->pPtsQueue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(PTSQUEUE_Reset, s32Ret);
            return s32Ret;
        }
    }

    pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->bDataValid = HI_FALSE;
    pstSource->u32DecodeLeftBytes = 0;
    pstSource->bActivate = HI_FALSE;
    pstSource->bFirstTimeStarted = HI_TRUE;
    pstSource->bRepeatEnable = HI_FALSE;
    pstSource->u32InBufUsed = 0;
    pstSource->u32InBufSize = 0;
    pstSource->u32InBufUsedPercent = 0;
    pstSource->u32TotDecodeFrame = 0;
    pstSource->u32PauseDelayms = 0;
    pstSource->u32AddMediaMixerMuteMs = 0;
    pstSource->u32AddMediaPauseMuteMs = 0;
    pstSource->u32ExtraTargetPtsMs = 0;

    return s32Ret;
}

HI_S32 SourceSetTargetPts(SOURCE_ID_E enSourceID, HI_U32 u32TargetPts)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d TargetPts:%dms\n", enSourceID, u32TargetPts);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (!((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        HI_ERR_AO("Source(%d) SetTargetPts only work syncmode pause!\n", enSourceID);
        return HI_FAILURE;
    }

    pstSource->bSeekFrame = HI_TRUE;
    pstSource->enPkGSeekType = PKG_SEEK_MODE_INTER;
    pstSource->u32TargetPts = u32TargetPts;
    pstSource->u32OrgTargetPts = u32TargetPts;
    pstSource->bDoWipeInvalidPTS = HI_TRUE;
    pstSource->bRepeatEnable = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 SourceSetRepeatTargetPts(SOURCE_ID_E enSourceID)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d RepeatTargetPts\n", enSourceID);

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (!((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        return HI_FAILURE;
    }

    SYNC_PRINTF("Set source:%d RepeatTarget:%d\n", enSourceID, pstSource->u32CurStreamPts);

    pstSource->bRepeatEnable = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 SourceDropFrame(SOURCE_ID_E enSourceID, HI_U32 u32FrameCnt)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d DropFrame:%d\n", enSourceID, u32FrameCnt);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (!((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        HI_ERR_AO("Source(%d) DropFrame only work syncmode pause!\n", enSourceID);
        return HI_FAILURE;
    }

    pstSource->bDropFrame = HI_TRUE;
    pstSource->u32DropFrameCnt = u32FrameCnt;

    return HI_SUCCESS;
}

HI_S32 SourceSetSyncMode(SOURCE_ID_E enSourceID, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_BOOL bValue;
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d SyncMode:%d\n", enSourceID, enSyncMode);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    bValue = (HI_MPI_AO_TRACK_SYNCMODE_STARTOUTPUT == enSyncMode) ? HI_TRUE : HI_FALSE;

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bEnableDecoder = bValue;
    pstSource->bEnableMixer   = bValue;

    if (HI_MPI_AO_TRACK_SYNCMODE_STARTOUTPUT == enSyncMode)
    {
        //force exit presync mode
        pstSource->bDropFrame = HI_FALSE;
        pstSource->bSeekFrame = HI_FALSE;
        pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
        pstSource->bRepeatEnable = HI_FALSE;
    }

    return HI_SUCCESS;
}

#ifdef DPT
HI_S32 SourceSetTrackSource(SOURCE_ID_E enSourceID, HI_UNF_SND_SOURCE_E enSource)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d enSource:%d\n", enSourceID, enSource);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->enSource = enSource;

    return HI_SUCCESS;
}
#endif

HI_S32 SourceSetEosFlag(SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    SOURCE_S* pstSource;

    SYNC_PRINTF("Set source:%d EosFlag:%d\n", enSourceID, bEosFlag);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    pstSource->bEosFlag = bEosFlag;

    return HI_SUCCESS;
}

HI_S32 SourceGetDelayMs(SOURCE_ID_E enSourceID, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32OutBufSize = 0;
    HI_U32 u32SampleRate = RENDER_OUT_FRAME_SAMPLERATE;
    HI_U32 u32FrameBytes = RENDER_OUT_FRAME_BYTES;
    HI_U32 u32LeftDelayMs = 0;
    SOURCE_S* pstSource;

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_ServerBuffer_GetDataSize(pstSource->pRBuffer, &u32OutBufSize);
    if (HI_SUCCESS != s32Ret)
    {
        *pu32DelayMs = 0;
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_GetDataSize, s32Ret);
        return s32Ret;
    }

    if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        pstSource->bActivate = HI_TRUE;
    }

    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        HI_HADECODE_OUTPUT_S* pstPackOut = &pstSource->stPackOut;

        if (0 == pstPackOut->u32OutSampleRate || 0 == pstPackOut->u32BitPerSample || 0 == pstPackOut->u32OutChannels)
        {
            s32Ret = RENDER_ServerBuffer_GetFrameInfo(pstSource->pRBuffer, pstPackOut);
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(RENDER_ServerBuffer_GetFrameInfo, s32Ret);
            }
        }

        if (0 != pstPackOut->u32OutSampleRate && 0 != pstPackOut->u32BitPerSample && 0 != pstPackOut->u32OutChannels)
        {
            u32SampleRate = pstPackOut->u32OutSampleRate;
            u32FrameBytes = (16 == pstPackOut->u32BitPerSample) ? (sizeof(HI_U16) * pstPackOut->u32OutChannels) : (sizeof(HI_U32) * pstPackOut->u32OutChannels);
        }

        HI_WARN_AO("Source(%d) SampleRate:%d BitPerSample:%d OutChannels:%d\n", enSourceID, pstPackOut->u32OutSampleRate,
                   pstPackOut->u32BitPerSample, pstPackOut->u32OutChannels);
    }

    //Notes: add decoder leftbuf

    u32LeftDelayMs = pstSource->u32AddMediaPauseMuteMs + pstSource->u32DecoderPcmDelay;
    HI_WARN_AO("pause to start: add delayms=%d(%d+%d)\n",
               pstSource->u32AddMediaPauseMuteMs,
               pstSource->u32DecoderPcmDelay);

    HI_WARN_AO("u32AddMediaPauseMuteMs = %d\n", pstSource->u32AddMediaPauseMuteMs);
    HI_WARN_AO("u32DecoderPcmDelay = %d\n", pstSource->u32DecoderPcmDelay);
    HI_WARN_AO("u32DataSizeDelayMS = %d\n", (u32OutBufSize * 1000) / (u32SampleRate * u32FrameBytes));

    *pu32DelayMs = (u32OutBufSize * 1000) / (u32SampleRate * u32FrameBytes) + u32LeftDelayMs;

    HI_WARN_AO("Source(%d) delayMS:%dms (RenderBufSize:%d DecodeLeftBytes:%d)\n", enSourceID, *pu32DelayMs, u32OutBufSize, pstSource->u32DecodeLeftBytes);

    return HI_SUCCESS;
}

HI_S32 SourceGetEosState(SOURCE_ID_E enSourceID, HI_BOOL* bEosFlag)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceGetEosState source %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    *bEosFlag = pstSource->bEosState;

    return HI_SUCCESS;
}

HI_S32 SourceGetBufferStatus(SOURCE_ID_E enSourceID, ADEC_BUFSTATUS_S* pstBufStatus)
{
    SOURCE_S* pstSource;
    HI_U32 u32InBufUsed;
    HI_U32 u32InBufSize;
    HI_S32 s32Ret;

    HI_INFO_AO("SourceGetBufferStatus source %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    s32Ret = RENDER_ServerBuffer_Enquire(pstSource->pRBuffer, &u32InBufUsed, &u32InBufSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ServerBuffer_Enquire, s32Ret);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstBufStatus->u32BufferSize = u32InBufSize;
    pstBufStatus->u32BufferUsed = u32InBufUsed;
    pstBufStatus->u32BufferAvailable = u32InBufSize - u32InBufUsed;
    pstBufStatus->u32TotDecodeFrame  = pstSource->u32TotDecodeFrame;
    pstBufStatus->u32SamplesPerFrame = 1536;
    pstBufStatus->bEndOfFrame = pstSource->bEosState;

    return s32Ret;
}

HI_S32 SourceGetStreamInfo(SOURCE_ID_E enSourceID, ADEC_STREAMINFO_S* pstStreamInfo)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceGetStreamInfo source %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    pstStreamInfo->enSampleRate = pstSource->stRenderEvent.stStreamInfo.enSampleRate;
    pstStreamInfo->u32BitRate   = pstSource->stRenderEvent.stStreamInfo.u32BitRate;
    pstStreamInfo->enBitDepth   = pstSource->stRenderEvent.stStreamInfo.enBitDepth;
    pstStreamInfo->u32Channel   = pstSource->stRenderEvent.stStreamInfo.u32Channel;

    if (HI_NULL != g_pstSourceRenderManager && HI_NULL != g_pstSourceRenderManager->pstEngineManger &&
        HI_NULL != g_pstSourceRenderManager->pstEngineManger->pstCodec)
    {
        pstStreamInfo->u32CodecID = g_pstSourceRenderManager->pstEngineManger->pstCodec->enCodecID;
    }

    return HI_SUCCESS;
}

HI_S32 SourceGetNewEvent(SOURCE_ID_E enSourceID, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    SOURCE_S* pstSource;

    HI_INFO_AO("SourceGetNewEvent source %d\n", enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];

    memcpy(pstNewEvent, &pstSource->stRenderEvent, sizeof(HI_MPI_AO_RENDER_EVENT_S));

    pstSource->stRenderEvent.bNewFrame = HI_FALSE;
    pstSource->stRenderEvent.bFrameInfoChange = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 Source_GetSourceIDFromTrackID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID)
{
    if ((hTrack & RENDER_TRACK_MASK) >= SOURCE_ID_BUTT)
    {
        return HI_FAILURE;
    }

    *penSourceID = (SOURCE_ID_E)(hTrack & RENDER_TRACK_MASK);

    return HI_SUCCESS;
}

HI_BOOL Source_Client_CheckTrack(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    if ((hTrack & 0xf000) != (HI_ID_RENDER_TRACK << 12) ||
        (SOURCE_ID_BUTT <= (hTrack & RENDER_TRACK_MASK)))   //lowbit 8: render sub_mod
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL Source_Client_CheckIsMediaTrack(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    return CheckIsMediaTrack(hTrack);
}

HI_BOOL Source_Client_CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    CHANNEL_PRINTF("Track id:0x%x!\n", hTrack);

    return IPC_Client_CheckISMediaTrackCreate(hTrack);
}


/*******************************************************************************
                                 Render Client
*******************************************************************************/
#define CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM   (0xF)
#define CLIENT_APP_TRACK_MAXNUM              (0x2)
#define CLIENT_MEDIA_TRACK_SOURCE_MAXNUM     (2)
#define CLIENT_MEDIA_TRACK_SOURCE_MAIN       (0)  // Main  or EXTMAIN
#define CLIENT_MEDIA_TRACK_SOURCE_SECOND     (1)  // Assoc or SecondMain

typedef struct
{
    SOURCE_ID_E   enSourceID;
    HI_VOID*      pRBuffer;
    HI_VOID*      pPtsQueue;
    HI_BOOL       bTrackStart;
    AUD_PES_DATA_S stPesData;
#ifdef DPT
    HI_BOOL       bTrackMute;
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;
#endif
} CLIENT_SOURCE_S;

typedef struct
{
    HI_BOOL       bRouteToMain;
    HI_HANDLE     hExtMainTrack;
    HI_HANDLE     hMainTrack;

    HI_HANDLE     hSlaveTrack; //ATV
} TRACK_MMAP_STATUS_S;

typedef struct
{
    HI_BOOL       bActived;
    HI_BOOL       bInputTypeInited;
    HI_HANDLE     hTrack;      //by avplay or unf default
    CLIENT_SOURCE_S* pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_MAXNUM];
} CLIENT_MEDIA_S;

typedef struct
{
    HI_BOOL              bIDAlloced[RENDER_TRACK_MAXNUM];
    TRACK_MMAP_STATUS_S  stTrackMMap[RENDER_TRACK_MAXNUM];
    CLIENT_MEDIA_S stClientMedia[CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM];
} CLIENT_MEDIATRACK_S;

typedef struct
{
    CLIENT_MEDIATRACK_S stMediaTrackManager;

    CLIENT_SOURCE_S*  pstOTTSound;    //ott uiaudio
    CLIENT_SOURCE_S*  pstSystemAudio; //system ui audio
    CLIENT_SOURCE_S*  pastAppAudio[CLIENT_APP_TRACK_MAXNUM]; //ott tts or accessibility
} CLIENT_TRACK_MANAGER_S;

static CLIENT_TRACK_MANAGER_S g_stClientTrackIDM;


static HI_BOOL ClientCheckSourceIsInstantiated(SOURCE_ID_E enSourceID)
{
    if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        return (HI_BOOL)(HI_NULL != g_stClientTrackIDM.pstOTTSound);
    }
    else if (SOURCE_ID_SYSTEM == enSourceID)
    {
        return (HI_BOOL)(HI_NULL != g_stClientTrackIDM.pstSystemAudio);
    }
    else if (SOURCE_ID_APP == enSourceID)
    {
        return (HI_BOOL)(HI_NULL != g_stClientTrackIDM.pastAppAudio[0]);  //TODO
    }

    return HI_FALSE;
}

static CLIENT_SOURCE_S* ClientGetSourceInstantiated(SOURCE_ID_E enSourceID)
{
    if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        return g_stClientTrackIDM.pstOTTSound;
    }
    else if (SOURCE_ID_SYSTEM == enSourceID)
    {
        return g_stClientTrackIDM.pstSystemAudio;
    }
    else if (SOURCE_ID_APP == enSourceID)
    {
        return g_stClientTrackIDM.pastAppAudio[0];  //TODO
    }

    return HI_NULL;
}

static HI_VOID ClientSaveSourceInstantiated(SOURCE_ID_E enSourceID, CLIENT_SOURCE_S* pstSource)
{
    if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        g_stClientTrackIDM.pstOTTSound = pstSource;
    }
    else if (SOURCE_ID_SYSTEM == enSourceID)
    {
        g_stClientTrackIDM.pstSystemAudio = pstSource;
    }
    else if (SOURCE_ID_APP == enSourceID)
    {
        g_stClientTrackIDM.pastAppAudio[0] = pstSource;
    }
}

static HI_VOID ClientDeleteSourceInstantiated(SOURCE_ID_E enSourceID)
{
    if (SOURCE_ID_OTTSOUND == enSourceID)
    {
        g_stClientTrackIDM.pstOTTSound = HI_NULL;
    }
    else if (SOURCE_ID_SYSTEM == enSourceID)
    {
        g_stClientTrackIDM.pstSystemAudio = HI_NULL;
    }
    else if (SOURCE_ID_APP == enSourceID)
    {
        g_stClientTrackIDM.pastAppAudio[0] = HI_NULL;
    }
}

static HI_BOOL ClientCheckIsMediaInstantiated(HI_U32 u32ID)
{
    return (HI_BOOL)(HI_NULL != g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_MAIN]);
}

static HI_S32  ClientGetSourceArrayIDFromSourceID(SOURCE_ID_E enSourceID, HI_U32* pu32ArrayID)
{
    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        *pu32ArrayID = CLIENT_MEDIA_TRACK_SOURCE_MAIN;
    }
    else if (SOURCE_ID_MAIN == enSourceID)
    {
        *pu32ArrayID = CLIENT_MEDIA_TRACK_SOURCE_MAIN;
    }
    else if (SOURCE_ID_ASSOC == enSourceID)
    {
        *pu32ArrayID = CLIENT_MEDIA_TRACK_SOURCE_SECOND;
    }
    else
    {
        HI_WARN_AO("Invalid Source:0x%d\n", enSourceID);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ClientGetAllocIDFromTrack(HI_HANDLE hTrack, HI_U32* pu32HandleID)
{
    *pu32HandleID = (hTrack & (0xF << RENDER_TRACK_IDOFFSET)) >> RENDER_TRACK_IDOFFSET;

    HI_WARN_AO("Client track(0x%x) -> AllocId(0x%x)\n", hTrack, *pu32HandleID);

    if (*pu32HandleID >= CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM)
    {
        HI_ERR_PrintInfo("Invalid HandleID, too many media track instance!");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ClientGetSourceIDFromTrack(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID)
{
    *penSourceID = hTrack & 0xf;

    HI_WARN_AO("Client track(0x%x) -> SourceId(0x%x)\n", hTrack, *penSourceID);

    if (*penSourceID >= SOURCE_ID_BUTT)
    {
        HI_ERR_PrintInfo("Invalid SourceID!");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMInsert(HI_HANDLE hMainTrack, HI_HANDLE hExtMainTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if (HI_FALSE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID])
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Too many client track(0x%x)!\n", u32ID);
        return HI_FAILURE;
    }

    g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID] = HI_TRUE;
    g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hMainTrack = hMainTrack;
    g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack = hExtMainTrack;
    g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].bRouteToMain = HI_FALSE;

    HI_WARN_AO("Insert Track(Main:0x%x ExtMain:0x%x) ID:%d successful\n", hMainTrack, hExtMainTrack, u32ID);

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMDelete(HI_HANDLE hTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID]) &&
            (hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack))
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID] = HI_FALSE;

    HI_WARN_AO("Delete Track(Main:0x%x) ID:%d successful\n", hTrack, u32ID);

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMInsertSlave(HI_HANDLE hTrack, HI_HANDLE hSlaveTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID]) &&
            (hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack))
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (0 != g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack)
    {
        HI_ERR_AO("Slave track(0x%x) inserted\n", g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack);
        return HI_FAILURE;
    }

    g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack = hSlaveTrack;

    HI_WARN_AO("Insert SlaveTrack(0x%x) ID:%d successful\n", hTrack, u32ID);

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMDeleteSlave(HI_HANDLE hTrack, HI_HANDLE hSlaveTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID]) &&
            (hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack))
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (hSlaveTrack != g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack)
    {
        HI_ERR_AO("Slave track(0x%x) different id\n", g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack = 0;

    HI_WARN_AO("Delete Track(0x%x) SlaveTrack(0x%x) ID:%d successful\n", hTrack, hSlaveTrack, u32ID);

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMEnquireSlaveAttachedInfo(HI_HANDLE hTrack, HI_BOOL* pbAttached, HI_HANDLE* phSlaveTrack)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID]) &&
            ((hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack) ||
             (hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hMainTrack)))
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_INFO_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (0 == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack)
    {
        HI_INFO_AO("Track(0x%x) Slavetrack not attached\n", hTrack);
        *pbAttached = HI_FALSE;
        return HI_SUCCESS;
    }

    *pbAttached = HI_TRUE;
    *phSlaveTrack = g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hSlaveTrack;

    HI_INFO_AO("Enquire SlaveTrackAttachedInfo(0x%x) (0x%x) ID:%d successful\n", hTrack, *phSlaveTrack, u32ID);

    return HI_SUCCESS;
}

static HI_S32 ClientTrackIDMEnquire(HI_HANDLE hTrack, HI_HANDLE* phRenderTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < RENDER_TRACK_MAXNUM - 1; u32ID++)
    {
        if ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.bIDAlloced[u32ID]) &&
            (hTrack == g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack))
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (RENDER_TRACK_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    phRenderTrack[RENDER_MAINAUDIO_NUM] = g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hMainTrack;
    phRenderTrack[RENDER_EXTMAINAUDIO_NUM] = g_stClientTrackIDM.stMediaTrackManager.stTrackMMap[u32ID].hExtMainTrack;

    HI_INFO_AO("Track(0x%x -> 0x%x/0x%x) successful\n", hTrack, *phRenderTrack, *(phRenderTrack + 1));

    return HI_SUCCESS;
}

static HI_S32 CreateMediaAssocTrack(HI_U32 u32HandleID, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr)
{
    HI_S32 s32Ret;
    CLIENT_SOURCE_S* pstSource;
    SOURCE_ID_E enSourceID;

    enSourceID = SOURCE_ID_ASSOC;

    pstSource = (CLIENT_SOURCE_S*)malloc(sizeof(CLIENT_SOURCE_S));
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Client Souce malloc failed!\n");
        return HI_FAILURE;
    }
    memset(pstSource, 0, sizeof(CLIENT_SOURCE_S));

    pstSource->enSourceID = enSourceID;

    s32Ret = RENDER_ClientBuffer_Init(&pstSource->pRBuffer, enSourceID, pstAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Init, s32Ret);
        goto ERR1;
    }

    s32Ret = SourceCreatePtsQueue(enSourceID, pstSource->pRBuffer, &pstSource->pPtsQueue, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceCreatePtsQueue, s32Ret);
        goto ERR2;
    }

    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_SECOND] = pstSource;

    return HI_SUCCESS;

ERR2:
    (HI_VOID)RENDER_ClientBuffer_DeInit(pstSource->pRBuffer);
ERR1:
    free(pstSource);

    return s32Ret;
}

static HI_S32 CreateMediaTrack(HI_HANDLE hTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32HandleID = 0;
    CLIENT_SOURCE_S* pstSource = HI_NULL;
    SOURCE_ID_E enSourceID = SOURCE_ID_BUTT;
    HI_U32 u32ArrayID = 0;

    s32Ret = ClientGetAllocIDFromTrack(hTrack, &u32HandleID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientGetAllocIDFromTrack, s32Ret);
        return s32Ret;
    }

    s32Ret = ClientGetSourceIDFromTrack(hTrack, &enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientGetSourceIDFromTrack, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == ClientCheckIsMediaInstantiated(u32HandleID))
    {
        HI_ERR_AO("Track(0x%x) is already instantiated\n", hTrack);
        return HI_FAILURE;
    }

    pstSource = (CLIENT_SOURCE_S*)malloc(sizeof(CLIENT_SOURCE_S));
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Client Souce malloc failed!\n");
        return HI_FAILURE;
    }
    memset(pstSource, 0, sizeof(CLIENT_SOURCE_S));

    pstSource->enSourceID = enSourceID;

    s32Ret = RENDER_ClientBuffer_Init(&pstSource->pRBuffer, enSourceID, pstAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Init, s32Ret);
        goto ERR1;
    }

    s32Ret = SourceCreatePtsQueue(enSourceID, pstSource->pRBuffer, &pstSource->pPtsQueue, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceCreatePtsQueue, s32Ret);
        goto ERR2;
    }

    s32Ret = ClientGetSourceArrayIDFromSourceID(enSourceID, &u32ArrayID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientGetSourceArrayIDFromSourceID, s32Ret);
        goto ERR2;
    }

    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].bActived = HI_FALSE;
    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].hTrack = hTrack;
    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[u32ArrayID] = pstSource;

    if (SOURCE_ID_MAIN != enSourceID)
    {
        return HI_SUCCESS;
    }

    s32Ret = CreateMediaAssocTrack(u32HandleID, pstAoIsbAttr + 1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(CreateMediaAssocTrack, s32Ret);
        goto ERR3;
    }

    return HI_SUCCESS;

ERR3:
    (HI_VOID)SourceDestoryPtsQueue(enSourceID, pstSource->pPtsQueue);
ERR2:
    (HI_VOID)RENDER_ClientBuffer_DeInit(pstSource->pRBuffer);
ERR1:
    free(pstSource);

    return s32Ret;
}

static HI_S32 DestroyMediaTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    HI_U32 u32HandleID = 0;
    CLIENT_SOURCE_S* pstSource;

    CHANNEL_TRACE();

    s32Ret = ClientGetAllocIDFromTrack(hTrack, &u32HandleID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientGetAllocIDFromTrack, s32Ret);
        return s32Ret;
    }

    if (HI_FALSE == ClientCheckIsMediaInstantiated(u32HandleID))
    {
        HI_ERR_AO("ID(%d) is not instantiated\n", u32HandleID);
        return HI_FAILURE;
    }

    pstSource = g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_MAIN];

    s32Ret = RENDER_ClientBuffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ClientBuffer_DeInit, s32Ret);
    }

    s32Ret = SourceDestoryPtsQueue(pstSource->enSourceID, pstSource->pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceDestoryPtsQueue, s32Ret);
    }

    if (SOURCE_ID_MAIN == pstSource->enSourceID)
    {
        CLIENT_SOURCE_S* pstAssocSource =
            g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_SECOND];

        s32Ret = RENDER_ClientBuffer_DeInit(pstAssocSource->pRBuffer);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(RENDER_ClientBuffer_DeInit, s32Ret);
        }

        s32Ret = SourceDestoryPtsQueue(pstAssocSource->enSourceID, pstAssocSource->pPtsQueue);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(SourceDestoryPtsQueue, s32Ret);
        }

        free(pstAssocSource);
        g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_SECOND] = HI_NULL;
    }

    free(pstSource);
    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].pstClientSource[CLIENT_MEDIA_TRACK_SOURCE_MAIN] = HI_NULL;
    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32HandleID].hTrack = HI_INVALID_HANDLE;

    return s32Ret;
}

static HI_S32 ClientCreateMediaTrack(HI_HANDLE hTrack, HI_HANDLE hExtTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr)
{
    HI_S32 s32Ret;

    s32Ret = CreateMediaTrack(hTrack, pstAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("CreateWithID Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = CreateMediaTrack(hExtTrack, &pstAoIsbAttr[2]);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("CreateWithID ExtMain failed(0x%x)\n", s32Ret);
        goto ERR_CREATE_EXT;
    }

    return HI_SUCCESS;

ERR_CREATE_EXT:
    (HI_VOID)DestroyMediaTrack(hTrack);

    return s32Ret;
}

static HI_S32 ClientDestroyMediaTrack(HI_HANDLE hTrack, HI_HANDLE hExtTrack)
{
    HI_S32 s32Ret;

    s32Ret = DestroyMediaTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DestroyTrackWithID Main failed(0x%x)\n", s32Ret);
    }

    s32Ret |= DestroyMediaTrack(hExtTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("DestroyTrackWithID Ext failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

static HI_S32 ClientGetShareBufferAttr(HI_HANDLE hTrack, HI_MPI_AO_SB_ATTR_S* pstSBAttr)
{
    HI_S32 s32Ret;

    s32Ret = IPC_Client_CreateTrackWithID(hTrack, pstSBAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_CreateTrackWithID, s32Ret);
    }

    return s32Ret;
}

static HI_BOOL ClientCheckIsActivedTrack(HI_HANDLE hTrack)
{
    HI_U32 u32ID;

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FALSE;
    }

    if (HI_FALSE == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bActived)
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_S32 ClientFindActivedSourceFromTrack(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, CLIENT_SOURCE_S** ppstSource)
{
    HI_U32 u32ID;

    if (enBufId >= HI_MPI_AO_BUF_ID_BUTT)
    {
        HI_ERR_AO("Invalid AoBufId(%d)\n", enBufId);
        return HI_ERR_AO_INVALID_PARA;
    }

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (HI_FALSE == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bActived)
    {
        return HI_ERR_AO_DEVICE_BUSY;
    }

    *ppstSource = g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].pstClientSource[enBufId];

    return HI_SUCCESS;
}

#ifdef DPT
static CLIENT_SOURCE_S* ClientFindMediaSourceFromTrack(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId)
{
    HI_U32 u32ID;

    if (enBufId >= HI_MPI_AO_BUF_ID_BUTT)
    {
        HI_ERR_AO("Invalid AoBufId(%d)\n", enBufId);
        return HI_NULL;
    }

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_NULL;
    }

    return g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].pstClientSource[enBufId];
}
#endif
static HI_S32 ClientActiveTrack(HI_HANDLE hTrack, HI_BOOL bActived)
{
    HI_U32 u32ID;
    HI_S32 s32Ret;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (((HI_FALSE == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bActived) && (HI_FALSE == bActived)) ||
        ((HI_TRUE == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bActived) && (HI_TRUE == bActived)))
    {
        return HI_SUCCESS;
    }

    HI_WARN_AO("Track(0x%x) Active:%d\n", hTrack, bActived);
    s32Ret = IPC_Client_ActiveTrack(hTrack, bActived);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_AO("ActiveTrack failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bActived = bActived;

    return HI_SUCCESS;
}

static HI_S32 ClientSetInputTypeStatus(HI_HANDLE hTrack, HI_BOOL bEnable)
{
    HI_U32 u32ID;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bInputTypeInited = bEnable;

    HI_WARN_AO("Track(0x%x) Set InputType inited(%d)\n", hTrack, bEnable);

    return HI_SUCCESS;
}

static HI_S32 ClientMakeSureInputTypeInited(HI_HANDLE hTrack)
{
    HI_U32 u32ID;
    HI_S32 s32Ret;

    CHANNEL_TRACE();

    for (u32ID = 0; u32ID < CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1; u32ID++)
    {
        if (hTrack == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].hTrack)
        {
            HI_INFO_AO("Find valid ID(0x%x)!\n", u32ID);
            break;
        }
    }

    if (u32ID >= (CLIENT_MEDIA_TRACK_INSTANCE_MAXNUM - 1))
    {
        HI_ERR_AO("Client track(0x%x) not found\n", hTrack);
        return HI_FAILURE;
    }

    if (HI_FALSE == g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bInputTypeInited)
    {
        HI_UNF_ACODEC_ATTR_S stRenderAttr;

        HI_WARN_AO("Track(0x%x) InputType not inited set default inputtype\n", hTrack);

        memset(&stRenderAttr, 0, sizeof(HI_UNF_ACODEC_ATTR_S));

        stRenderAttr.enType = HA_AUDIO_ID_PCM;

        s32Ret = IPC_Client_SetTrackAttr(hTrack, &stRenderAttr);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(IPC_Client_SetTrackAttr, s32Ret);
            return s32Ret;
        }

        g_stClientTrackIDM.stMediaTrackManager.stClientMedia[u32ID].bInputTypeInited = HI_TRUE;
    }

    return HI_SUCCESS;
}

static HI_BOOL ClientCheckIsPesDataValid(AUD_PES_DATA_S* pstPesData)
{
    HI_U32 u32Cnt = 6;
    if ((0xF8 == pstPesData->au8Data[0]) && (0x44 == pstPesData->au8Data[1]) &&
        (0x54 == pstPesData->au8Data[2]) && (0x47 == pstPesData->au8Data[3]) &&
        (0x41 == pstPesData->au8Data[4]) && (0x44 == pstPesData->au8Data[5]) &&
        (0x31 == pstPesData->au8Data[6]))
    {
        HI_INFO_AO("ClientCheckIsPesDataValid true\n");
        return HI_TRUE;
    }

    for(u32Cnt = 0; u32Cnt<7; u32Cnt++)
    {
       HI_INFO_AO("ClientCheckIsPesDataValid u32Cnt %x, bytes %x\n",u32Cnt, pstPesData->au8Data[u32Cnt]);
    }

    return HI_FALSE;
}

static HI_BOOL ClientCheckIsPesDataChange(AUD_PES_DATA_S* pstOrgPesData, AUD_PES_DATA_S* pstNewPesData)
{
    HI_U32 u32Cnt = 6;

    if ((pstOrgPesData->au8Data[7] != pstNewPesData->au8Data[7]) ||   //FADE BYTE
        (pstOrgPesData->au8Data[8] != pstNewPesData->au8Data[8]))     //PAN  BYTE
    {
        HI_INFO_AO("ClientCheckIsPesDataChange true\n");
        return HI_TRUE;
    }

    for(u32Cnt = 7; u32Cnt < 9; u32Cnt++)
    {
       HI_INFO_AO("ClientCheckIsPesDataValid u32Cnt %x, old %x, new %x\n",u32Cnt, pstOrgPesData->au8Data[u32Cnt],pstNewPesData->au8Data[u32Cnt]);
    }

    return HI_FALSE;
}

static HI_VOID ClientTrackParserPesPrivData(HI_HANDLE hTrack, CLIENT_SOURCE_S* pstSource, HI_VOID* pPesData)
{
    if (HI_NULL != pPesData && SOURCE_ID_ASSOC == pstSource->enSourceID)
    {
        HI_S32 s32Ret;
        AUD_PES_DATA_S* pstPesData = pPesData;
        HA_MS12_SET_PES_DATA_S stMs12PesData;
        if ((HI_TRUE == ClientCheckIsPesDataValid(pstPesData)) && (HI_TRUE == ClientCheckIsPesDataChange(&pstSource->stPesData, pstPesData)))
        {
            memcpy(&pstSource->stPesData, pstPesData, sizeof(AUD_PES_DATA_S));
            CHANNEL_PRINTF("FadeByte:0x%x PanByte:0x%x\n", pstPesData->au8Data[7], pstPesData->au8Data[8]);
            memset(&stMs12PesData, 0, sizeof(HA_MS12_SET_PES_DATA_S));
            stMs12PesData.enCmd = HA_CODEC_MS12_SET_PES_DATA_CMD;
            stMs12PesData.au8Data[0] = pstPesData->au8Data[7];
            stMs12PesData.au8Data[4] = pstPesData->au8Data[8];
            s32Ret = IPC_Client_SetTrackCmd(hTrack, (HI_VOID*)(&stMs12PesData));
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_AO("SET_PES_DATA failed(0x%x)\n", s32Ret);
            }
        }
    }
}

static HI_VOID ClientBuildPackOutput(const HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_HADECODE_OUTPUT_S* pstPackOut)
{
    pstPackOut->u32BitPerSample          = pstAOFrame->s32BitPerSample;
    pstPackOut->u32OutChannels           = pstAOFrame->u32Channels;
    pstPackOut->u32OutSampleRate         = pstAOFrame->u32SampleRate;
    pstPackOut->u32BitsOutBytesPerFrame  = pstAOFrame->u32BitsBytesPerFrame;
    pstPackOut->ps32BitsOutBuf           = pstAOFrame->ps32BitsBuffer;
    pstPackOut->u32PcmOutSamplesPerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    pstPackOut->ps32PcmOutBuf            = pstAOFrame->ps32PcmBuffer;
}

HI_S32 Source_Client_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;
    HI_HANDLE hMainTrack;
    HI_HANDLE hExtMainTrack;
    HI_MPI_AO_SB_ATTR_S astAoIsbAttr[MAINASSOCAUDIOPAYLOADCNT] = {{0}, {0}, {0}};

    CHANNEL_TRACE();

    s32Ret = IPC_Client_ApllyID(pstTrackAttr, &hMainTrack, &hExtMainTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("IPC_Client_ApllyID failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    s32Ret = ClientGetShareBufferAttr(hMainTrack, astAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientGetShareBufferAttr, s32Ret);
        return s32Ret;
    }

    s32Ret = ClientCreateMediaTrack(hMainTrack, hExtMainTrack, astAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientCreateMediaTrack, s32Ret);
    }

    s32Ret = ClientTrackIDMInsert(hMainTrack, hExtMainTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientTrackIDMInsert failed(0x%x)\n", s32Ret);
        IPC_Client_DeApllyID(hMainTrack, hExtMainTrack);
        return s32Ret;
    }

    *phTrack = hExtMainTrack;

    HI_WARN_AO("TrackID:0x%x Main/ExtMain:0x%x/0x%x\n", *phTrack, hMainTrack, hExtMainTrack);

    return s32Ret;
}

HI_S32 Source_Client_DeApllyID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    HI_BOOL bAttached = HI_FALSE;
    HI_HANDLE hSlaveTrack;
    HI_HANDLE aRenderTrack[RENDER_TRACK_MAX_NUM];

    CHANNEL_TRACE();

    memset(aRenderTrack, 0, sizeof(HI_HANDLE) * RENDER_TRACK_MAX_NUM);

    s32Ret = ClientActiveTrack(hTrack, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientActiveTrack, s32Ret);
    }

    /* destroy rendertrack */
    s32Ret = ClientTrackIDMEnquire(hTrack, aRenderTrack);
    if (HI_SUCCESS == s32Ret)
    {
        s32Ret = IPC_Client_DeApllyID(aRenderTrack[RENDER_MAINAUDIO_NUM], aRenderTrack[RENDER_EXTMAINAUDIO_NUM]);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("IPC_Client_DeApllyID failed(0x%x)\n", s32Ret);
        }

        s32Ret = ClientDestroyMediaTrack(aRenderTrack[RENDER_MAINAUDIO_NUM], aRenderTrack[RENDER_EXTMAINAUDIO_NUM]);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(ClientDestroyMediaTrack, s32Ret);
        }
    }
    else
    {
        HI_ERR_AO("ClientTrackIDMEnquire failed(0x%x)\n", s32Ret);
    }

    /* destroy Slavetrack */
    s32Ret = ClientTrackIDMEnquireSlaveAttachedInfo(hTrack, &bAttached, &hSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientTrackIDMEnquireSlaveAttachedInfo, s32Ret);
    }

    if (HI_TRUE == bAttached)
    {
        s32Ret = HI_MPI_RENDER_DestroyTrack(hSlaveTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(HI_MPI_RENDER_DestroyTrack, s32Ret);
        }
    }

    /* destroy IDM */
    s32Ret = ClientTrackIDMDelete(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientTrackIDMDelete failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_GetRenderTrackID(HI_HANDLE hTrack, HI_HANDLE* phRenderTrack)
{
    return ClientTrackIDMEnquire(hTrack, phRenderTrack);
}

HI_S32 Source_Client_Create(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    HI_MPI_AO_SB_ATTR_S stAoIsbAttr = {0};
    CLIENT_SOURCE_S* pstSource;

    CHANNEL_TRACE();

    enSourceID = GetSourceIDFromTrackType(pstTrackAttr->enTrackType);
    if (SOURCE_ID_BUTT == enSourceID)
    {
        HI_ERR_AO("GetSourceID failed!\n");
        return HI_FAILURE;
    }

    if (HI_TRUE == ClientCheckSourceIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is always instantiated\n", enSourceID);
        return HI_FAILURE;
    }

    pstSource = (CLIENT_SOURCE_S*)malloc(sizeof(CLIENT_SOURCE_S));
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Client Souce malloc failed!\n");
        return HI_FAILURE;
    }
    memset(pstSource, 0, sizeof(CLIENT_SOURCE_S));

    pstSource->enSourceID = enSourceID;

    s32Ret = IPC_Client_CreateTrack(enSound, pstTrackAttr, phTrack, &stAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_CreateTrack, s32Ret);
        goto ERR1;
    }

    s32Ret = RENDER_ClientBuffer_Init(&pstSource->pRBuffer, enSourceID, &stAoIsbAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Init, s32Ret);
        goto ERR2;
    }

    s32Ret = SourceCreatePtsQueue(enSourceID, pstSource->pRBuffer, &pstSource->pPtsQueue, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceCreatePtsQueue, s32Ret);
        goto ERR3;
    }

    ClientSaveSourceInstantiated(enSourceID, pstSource);

    return HI_SUCCESS;

ERR3:
    (HI_VOID)RENDER_ClientBuffer_DeInit(pstSource->pRBuffer);
ERR2:
    (HI_VOID)IPC_Client_DestroyTrack(*phTrack);
ERR1:
    free(pstSource);
    return s32Ret;
}

HI_S32  Source_Client_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;
    CLIENT_SOURCE_S* pstSource;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstSource = ClientGetSourceInstantiated(enSourceID);
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Source(%d) resource is invalid\n", enSourceID);
        return HI_ERR_AO_NULL_PTR;
    }

    s32Ret = RENDER_ClientBuffer_DeInit(pstSource->pRBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDER_ClientBuffer_DeInit, s32Ret);
    }

    s32Ret |= SourceDestoryPtsQueue(enSourceID, pstSource->pPtsQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceDestoryPtsQueue, s32Ret);
    }

    s32Ret |= IPC_Client_DestroyTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_DestroyTrack, s32Ret);
    }

    free(pstSource);

    ClientDeleteSourceInstantiated(enSourceID);

    return s32Ret;
}

HI_S32 Source_Client_SetTrackConfig(HI_HANDLE hTrack, const HI_VOID* pstConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_DBG_PrintU32(hTrack);

    s32Ret = IPC_Client_SetTrackConfig(hTrack, pstConfig);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackConfig, s32Ret);
    }

    return s32Ret;
}

HI_S32  Source_Client_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pstConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_DBG_PrintU32(hTrack);

    s32Ret = IPC_Client_GetTrackConfig(hTrack, pstConfig);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetTrackConfig, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_DBG_PrintU32(hTrack);

    s32Ret = ClientActiveTrack(hTrack, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientActiveTrack, s32Ret);
        return s32Ret;
    }

    s32Ret = IPC_Client_SetTrackAttr(hTrack, pstRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackAttr, s32Ret);
        return s32Ret;
    }

    s32Ret = ClientSetInputTypeStatus(hTrack, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(ClientSetInputTypeStatus, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = IPC_Client_GetTrackAttr(hTrack, pstAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetTrackAttr, s32Ret);
    }

    return s32Ret;
}

HI_S32  Source_Client_SetCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = IPC_Client_SetTrackCmd(hTrack, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackCmd, s32Ret);
    }

    return s32Ret;
}

HI_S32  Source_Client_GetCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd)
{
    return HI_FAILURE;
}

HI_S32 Source_Client_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32FrameSize = 0;
    SOURCE_ID_E enSourceID;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientFindActivedSourceFromTrack(hTrack, 0, &pstSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Track(0x%x) not instantiated or actived\n", hTrack);
            return HI_ERR_AO_INVALID_PARA;
        }
    }
    else
    {
        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Source(%d) resource is invalid\n", enSourceID);
        return HI_ERR_AO_NULL_PTR;
    }

    if (SOURCE_ID_EXTDEC == enSourceID)
    {
        HI_HADECODE_OUTPUT_S stPackOut;

        memset(&stPackOut, 0, sizeof(HI_HADECODE_OUTPUT_S));
        ClientBuildPackOutput(pstAOFrame, &stPackOut);

        s32Ret = RENDER_ClientBuffer_SendAoFrame(pstSource->pRBuffer, &stPackOut);
        if (HI_SUCCESS != s32Ret)
        {
            if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
            {
                HI_INFO_AO("Track(0x%x) Buffer is full\n", hTrack);
            }
            else
            {
                HI_LOG_PrintFuncErr(RENDER_ClientBuffer_SendAoFrame, s32Ret);
            }
            return s32Ret;
        }
    }
    else
    {
        if (16 == pstAOFrame->s32BitPerSample)
        {
            u32FrameSize = pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * sizeof(HI_U16);
        }
        else
        {
            u32FrameSize = pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels * sizeof(HI_U32);
        }

        s32Ret = RENDER_ClientBuffer_Send(pstSource->pRBuffer, (HI_U8*)pstAOFrame->ps32PcmBuffer, u32FrameSize);
        if (HI_SUCCESS != s32Ret)
        {
            if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
            {
                HI_INFO_AO("Track(0x%x) Buffer is full\n", hTrack);
            }
            else
            {
                HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Send, s32Ret);
            }
            return s32Ret;
        }
    }

    HI_WARN_AO("Track(0x%x) SendData FrameSize=%d\n", hTrack, u32FrameSize);
    return HI_SUCCESS;
}

HI_S32 Source_Client_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs, HI_VOID* pPesData)
{
    HI_S32 s32Ret;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    CHANNEL_TRACE();

    s32Ret = ClientFindActivedSourceFromTrack(hTrack, enBufId, &pstSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Track(%d) resource is invalid\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    if (HI_TRUE == PTSQUEUE_CheckIsFull(pstSource->pPtsQueue))
    {
        HI_INFO_AO("Track(0x%x) PTSQUEUE is full\n", hTrack);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_ClientBuffer_Send(pstSource->pRBuffer, pstStream->pu8Data, pstStream->u32Size);
    if (HI_SUCCESS != s32Ret)
    {
        if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
        {
            HI_INFO_AO("Track(0x%x) Buffer is full\n", hTrack);
        }
        else
        {
            HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Send, s32Ret);
        }
        return s32Ret;
    }

    ClientTrackParserPesPrivData(hTrack, pstSource, pPesData);
    return PTSQUEUE_Put(hTrack, pstSource->pPtsQueue, u32PtsMs, pstStream->u32Size);
}

HI_S32 Source_Client_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    HI_S32 s32Ret;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    CHANNEL_TRACE();

    s32Ret = ClientFindActivedSourceFromTrack(hTrack, enBufId, &pstSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Track(%d) resource is invalid\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    if (HI_TRUE == PTSQUEUE_CheckIsFull(pstSource->pPtsQueue))
    {
        HI_INFO_AO("Track(0x%x) PTSQUEUE is full\n", hTrack);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_ClientBuffer_Get(pstSource->pRBuffer, u32RequestSize, &pstStream->pu8Data);
    if (HI_SUCCESS != s32Ret)
    {
        if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
        {
            HI_INFO_AO("Track(0x%x) Buffer is full\n", hTrack);
        }
        else
        {
            HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Get, s32Ret);
        }
        return s32Ret;
    }

    pstStream->u32Size = u32RequestSize;

    return HI_SUCCESS;
}

HI_S32 Source_Client_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    CHANNEL_TRACE();

    s32Ret = ClientFindActivedSourceFromTrack(hTrack, enBufId, &pstSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Track(%d) resource is invalid\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    if (HI_TRUE == PTSQUEUE_CheckIsFull(pstSource->pPtsQueue))
    {
        HI_INFO_AO("Track(0x%x) PTSQUEUE is full\n", hTrack);
        return HI_ERR_AO_OUT_BUF_FULL;
    }

    s32Ret = RENDER_ClientBuffer_Put(pstSource->pRBuffer, pstStream->u32Size, pstStream->pu8Data);
    if (HI_SUCCESS != s32Ret)
    {
        if (HI_ERR_AO_OUT_BUF_FULL == s32Ret)
        {
            HI_INFO_AO("Track(0x%x) Buffer is full\n", hTrack);
        }
        else
        {
            HI_LOG_PrintFuncErr(RENDER_ClientBuffer_Put, s32Ret);
        }
        return s32Ret;
    }

    return PTSQUEUE_Put(hTrack, pstSource->pPtsQueue, u32PtsMs, pstStream->u32Size);
}

HI_S32 Source_Client_StartTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source StartTrack 0x%x\n", hTrack);

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientActiveTrack(hTrack, HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(ClientActiveTrack, s32Ret);
            return s32Ret;
        }

        s32Ret = ClientMakeSureInputTypeInited(hTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(ClientMakeSureInputTypeInited, s32Ret);
            (HI_VOID)ClientActiveTrack(hTrack, HI_FALSE);
            return s32Ret;
        }

        s32Ret = ClientFindActivedSourceFromTrack(hTrack, 0, &pstSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Track(0x%x) not instantiated or actived\n", hTrack);
            return HI_ERR_AO_INVALID_PARA;
        }
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Track(%d) resource is invalid\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    if (HI_TRUE == pstSource->bTrackStart)
    {
        HI_INFO_AO("Source had StartTrack 0x%x, no need to send socket cmd\n", hTrack);
        return HI_SUCCESS;
    }

    s32Ret = IPC_Client_StartTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_StartTrack, s32Ret);
        return s32Ret;
    }

    pstSource->bTrackStart = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 Source_Client_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source StopTrack 0x%x\n", hTrack);

    s32Ret = IPC_Client_StopTrack(hTrack);
    if (HI_SUCCESS != s32Ret && HI_ERR_AO_NOT_ACTIVED != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_StopTrack, s32Ret);
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientFindActivedSourceFromTrack(hTrack, 0, &pstSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        }

        s32Ret = ClientActiveTrack(hTrack, HI_FALSE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(ClientActiveTrack, s32Ret);
        }
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL != pstSource)
    {
        pstSource->bTrackStart = HI_FALSE;
    }

    return s32Ret;
}

HI_S32 Source_Client_PauseTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source PauseTrack 0x%x\n", hTrack);

    s32Ret = IPC_Client_PauseTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_PauseTrack, s32Ret);
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientFindActivedSourceFromTrack(hTrack, 0, &pstSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        }
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL != pstSource)
    {
        pstSource->bTrackStart = HI_FALSE;
    }

    return s32Ret;
}

HI_S32 Source_Client_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source FlushTrack 0x%x\n", hTrack);

    s32Ret = IPC_Client_FlushTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_FlushTrack, s32Ret);
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientFindActivedSourceFromTrack(hTrack, 0, &pstSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_AO("Track(0x%x) not instantiated or actived\n", hTrack);
        }
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL != pstSource)
    {
        pstSource->bTrackStart = HI_FALSE;
    }

    return s32Ret;
}

HI_S32 Source_Client_GetSourceID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID)
{
    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, *penSourceID);

    return HI_SUCCESS;
}

HI_S32 Source_Client_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    s32Ret = IPC_Client_SetTargetPts(hTrack, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTargetPts, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_SetRepeatTargetPts(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    s32Ret = IPC_Client_SetRepeatTargetPts(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetRepeatTargetPts, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    s32Ret = IPC_Client_DropFrame(hTrack, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_DropFrame, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_DropTrackStream(HI_HANDLE hTrack, HI_U32 u32SeekPts)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = IPC_Client_DropTrackStream(hTrack, u32SeekPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_DropTrackStream, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_TRACK_SYNCMODE(enSyncMode);

    HI_WARN_AO("Source SetSyncMode 0x%x\n", hTrack);

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        s32Ret = ClientActiveTrack(hTrack, HI_TRUE);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(ClientActiveTrack, s32Ret);
            return s32Ret;
        }
    }

    s32Ret = IPC_Client_SetSyncMode(hTrack, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetSyncMode, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Source Track 0x%x bEosFlag:%d\n", hTrack, bEosFlag);

    s32Ret = IPC_Client_SetEosFlag(hTrack, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetEosFlag, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32DelayMs = 0;
    HI_HANDLE SrcTrack = 0;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    SrcTrack = hTrack;

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (SOURCE_ID_MAIN == enSourceID)
        {
            if (HI_TRUE != ClientCheckIsActivedTrack(hTrack))
            {
                *pu32DelayMs = 0;
                return HI_SUCCESS;
            }
        }
        else
        {
            HI_HANDLE aRenderTrack[RENDER_TRACK_MAX_NUM];

            s32Ret = ClientTrackIDMEnquire(hTrack, aRenderTrack);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_AO("ClientTrackIDMEnquire failed(0x%x)\n", s32Ret);
                return s32Ret;
            }

            if (HI_TRUE == ClientCheckIsActivedTrack(aRenderTrack[RENDER_EXTMAINAUDIO_NUM]))
            {
                SrcTrack = aRenderTrack[RENDER_EXTMAINAUDIO_NUM];
            }
            else if (HI_TRUE == ClientCheckIsActivedTrack(aRenderTrack[RENDER_MAINAUDIO_NUM]))
            {
                SrcTrack = aRenderTrack[RENDER_MAINAUDIO_NUM];
            }
            else
            {
                *pu32DelayMs = 0;
                return HI_SUCCESS;
            }
        }
    }

    s32Ret = IPC_Client_GetDelayMs(SrcTrack, &u32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncWarn(IPC_Client_GetDelayMs, s32Ret);
        return s32Ret;
    }

    *pu32DelayMs = u32DelayMs;

    return HI_SUCCESS;
}

HI_S32 Source_Client_CheckCreateSlaveTrack(HI_HANDLE hTrack, HI_HANDLE* phSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    s32Ret = HI_MPI_RENDER_GetDefaultOpenAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_RENDER_GetDefaultOpenAttr, s32Ret);
        return s32Ret;
    }

    s32Ret = HI_MPI_RENDER_CreateTrack(HI_UNF_SND_0, &stTrackAttr, phSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_RENDER_CreateTrack, s32Ret);
        return s32Ret;
    }

    s32Ret = ClientTrackIDMInsertSlave(hTrack, *phSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientTrackIDMInsertSlave track(0x%x) failed(0x%x)", hTrack, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_DestroySlaveTrack(HI_HANDLE hTrack, HI_HANDLE hSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);

    s32Ret = HI_MPI_RENDER_DestroyTrack(hSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_RENDER_DestroyTrack, s32Ret);
        return s32Ret;
    }

    s32Ret = ClientTrackIDMDeleteSlave(hTrack, hSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientTrackIDMDeleteSlave track(0x%x) failed(0x%x)", hTrack, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetSlaveTrackAttachedInfo(HI_HANDLE hTrack, HI_BOOL* pbAttached, HI_HANDLE* phSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = ClientTrackIDMEnquireSlaveAttachedInfo(hTrack, pbAttached, phSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("ClientTrackIDMEnquireSlaveAttachedInfo track(0x%x) failed(0x%x)\n", hTrack, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetEosState(HI_HANDLE hTrack, HI_BOOL* pbEosState)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bEos = HI_FALSE;

    HI_WARN_AO("Track 0x%x\n", hTrack);
    s32Ret = IPC_Client_GetEosState(hTrack, &bEos);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetEosState, s32Ret);
        return s32Ret;
    }

    *pbEosState = bEos;

    return HI_SUCCESS;
}

HI_S32 Source_Client_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32PtsMs, HI_U32* pu32OrgPtsMs)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);
    s32Ret = IPC_Client_GetTrackPts(hTrack, pu32PtsMs, pu32OrgPtsMs);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_AO_NOT_INIT != s32Ret))
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetTrackPts, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);
    s32Ret = IPC_Client_GetBufferStatus(hTrack, pstBufStatus);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_AO_NOT_ACTIVED != s32Ret))
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetBufferStatus, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstStreamInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Track 0x%x\n", hTrack);
    s32Ret = IPC_Client_GetStreamInfo(hTrack, pstStreamInfo);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_AO_NOT_ACTIVED != s32Ret))
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetStreamInfo, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Client_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    HI_WARN_AO("Track 0x%x\n", hTrack);
    return IPC_Client_CheckNewEvent(hTrack, pstNewEvent);
}

#ifdef DPT
HI_S32 Source_Client_SetTrackMute(HI_HANDLE hTrack, HI_BOOL bMute)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source SetTrackMute 0x%x\n", hTrack);

    s32Ret = IPC_Client_SetTrackMute(hTrack, bMute);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackMute, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        HI_HANDLE aRenderTrack[RENDER_TRACK_MAX_NUM];

        s32Ret = ClientTrackIDMEnquire(hTrack, aRenderTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("ClientTrackIDMEnquire failed(0x%x)\n", s32Ret);
            return s32Ret;
        }

        s32Ret = IPC_Client_SetTrackMute(aRenderTrack[RENDER_MAINAUDIO_NUM], bMute);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(IPC_Client_SetTrackMute, s32Ret);
            return s32Ret;
        }

        pstSource = ClientFindMediaSourceFromTrack(hTrack, 0);
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Invalid SourceTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    pstSource->bTrackMute = bMute;

    return HI_SUCCESS;
}

HI_S32 Source_Client_GetTrackMute(HI_HANDLE hTrack, HI_BOOL* pbMute)
{
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        pstSource = ClientFindMediaSourceFromTrack(hTrack, 0);
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Invalid SourceTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    *pbMute = pstSource->bTrackMute;

    return HI_SUCCESS;
}

HI_S32 Source_Client_SetTrackPrescale(HI_HANDLE hTrack, const HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain)
{
    HI_S32 s32Ret = HI_SUCCESS;
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    HI_WARN_AO("Source SetTrackPrescale 0x%x\n", hTrack);

    CHECK_TRACK_ABSLUTEPRECIVOLUME(pstPreciGain->s32IntegerGain, pstPreciGain->s32DecimalGain);

    s32Ret = IPC_Client_SetTrackPrescale(hTrack, pstPreciGain);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackPrescale, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        HI_HANDLE aRenderTrack[RENDER_TRACK_MAX_NUM];

        s32Ret = ClientTrackIDMEnquire(hTrack, aRenderTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("ClientTrackIDMEnquire failed(0x%x)\n", s32Ret);
            return s32Ret;
        }

        s32Ret = IPC_Client_SetTrackPrescale(aRenderTrack[RENDER_MAINAUDIO_NUM], pstPreciGain);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(IPC_Client_SetTrackPrescale, s32Ret);
            return s32Ret;
        }

        pstSource = ClientFindMediaSourceFromTrack(hTrack, 0);
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Invalid SourceTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    pstSource->stPreciGain.s32IntegerGain = pstPreciGain->s32IntegerGain;
    pstSource->stPreciGain.s32DecimalGain = pstPreciGain->s32DecimalGain;

    return HI_SUCCESS;
}

HI_S32 Source_Client_GetTrackPrescale(HI_HANDLE hTrack, HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain)
{
    CLIENT_SOURCE_S* pstSource = HI_NULL;

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        pstSource = ClientFindMediaSourceFromTrack(hTrack, 0);
    }
    else
    {
        SOURCE_ID_E enSourceID;
        CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

        if (HI_FALSE == ClientCheckSourceIsInstantiated(enSourceID))
        {
            HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
            return HI_ERR_AO_INVALID_PARA;
        }

        pstSource = ClientGetSourceInstantiated(enSourceID);
    }

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Invalid SourceTrack(0x%x)\n", hTrack);
        return HI_ERR_AO_NULL_PTR;
    }

    pstPreciGain->s32IntegerGain = pstSource->stPreciGain.s32IntegerGain;
    pstPreciGain->s32DecimalGain = pstSource->stPreciGain.s32DecimalGain;

    return HI_SUCCESS;
}

HI_S32 Source_Client_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_WARN_AO("Source SetTrackSource 0x%x\n", hTrack);

    s32Ret = IPC_Client_SetTrackSource(hTrack, enSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_SetTrackSource, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == CheckIsMediaTrack(hTrack))
    {
        HI_HANDLE aRenderTrack[RENDER_TRACK_MAX_NUM];

        s32Ret = ClientTrackIDMEnquire(hTrack, aRenderTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("ClientTrackIDMEnquire failed(0x%x)\n", s32Ret);
            return s32Ret;
        }

        s32Ret = IPC_Client_SetTrackSource(aRenderTrack[RENDER_MAINAUDIO_NUM], enSource);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(IPC_Client_SetTrackSource, s32Ret);
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}
#endif

HI_S32  Source_Client_GetRenderAllInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_DBG_PrintU32(hTrack);

    s32Ret = IPC_Client_GetRenderAllInfo(hTrack, pstAllInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Client_GetRenderAllInfo, s32Ret);
    }

    return s32Ret;
}

HI_BOOL Source_Server_CheckIsMediaTrack(HI_HANDLE hTrack)
{
    return CheckIsMediaTrack(hTrack);
}

HI_BOOL Source_Server_CheckIsMediaTrackCreated(HI_HANDLE hTrack)
{
    return CheckIsMediaTrackCreated(hTrack);
}

HI_BOOL Source_Server_CheckIsMediaTrackDuplicate(HI_HANDLE hTrack)
{
    SOURCE_ID_E enSourceID;

    if (HI_TRUE != CheckIsMediaTrack(hTrack))
    {
        return HI_FALSE;
    }

    if (((hTrack & 0xf000) != (HI_ID_RENDER_TRACK << 12)) ||
        (SOURCE_ID_BUTT <= (hTrack & RENDER_TRACK_MASK)))
    {
        HI_ERR_AO("Invalid TrackID(0x%x) failed\n", hTrack);
        return HI_FALSE;
    }

    enSourceID = (SOURCE_ID_E)(hTrack & RENDER_TRACK_MASK);

    return CheckIsSourceDuplicate(enSourceID);
}

HI_MPI_RENDER_SOURCE_TYPE_E Source_Server_GetSourceTypeforTrackType(HI_UNF_SND_TRACK_TYPE_E enType)
{
    HI_MPI_RENDER_SOURCE_TYPE_E enSourceType;

    switch (enType)
    {
        case HI_UNF_SND_TRACK_TYPE_OTTSOUND:
            enSourceType = HI_MPI_RENDER_SOURCE_TYPE_OTTSOUND;
            break;
        case HI_UNF_SND_TRACK_TYPE_SYSTEMAUDIO:
            enSourceType = HI_MPI_RENDER_SOURCE_TYPE_SYSTEMAUDIO;
            break;
        case HI_UNF_SND_TRACK_TYPE_APPAUDIO:
            enSourceType = HI_MPI_RENDER_SOURCE_TYPE_APPAUDIO;
            break;
        default:
            HI_ERR_AO("Invalid TrackType(0x%x)\n", enType);
            enSourceType = HI_MPI_RENDER_SOURCE_TYPE_BUTT;
            break;
    }

    HI_WARN_AO("TrackType(0x%x) -> SourceType(0x%x)\n", enType, enSourceType);

    return enSourceType;
}

HI_S32 Source_Server_DeallocID(HI_HANDLE hTrack)
{
    return MediaTrackIDMDeAlloc(hTrack);
}

HI_S32 Source_Server_Init(RENDER_MANAGER_S* pstRenderManager)
{
    CHANNEL_TRACE();

    g_pstSourceManager = (SOURCE_MANAGER_S*)malloc(sizeof(SOURCE_MANAGER_S));
    if (HI_NULL == g_pstSourceManager)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    memset(g_pstSourceManager, 0, sizeof(SOURCE_MANAGER_S));

    pstRenderManager->pstSourceManager = g_pstSourceManager;
    g_pstSourceRenderManager = pstRenderManager;

    return HI_SUCCESS;
}

HI_S32 Source_Server_Deinit(HI_VOID)
{
    CHANNEL_TRACE();

    if (g_pstSourceManager)
    {
        free(g_pstSourceManager);
        g_pstSourceManager = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 Source_Server_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack, HI_HANDLE* phExtTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    enSourceID = GetSourceIDFromTrackType(pstTrackAttr->enTrackType);
    if (SOURCE_ID_MAIN != enSourceID)
    {
        HI_ERR_AO("Get invalid sourceID(0x%x) failed or invalid type(0x%x)!\n", enSourceID, pstTrackAttr->enTrackType);
        return HI_FAILURE;
    }

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    /*always prepare ext track for maintrack */
    s32Ret = SourceAllocID(SOURCE_ID_MAIN, phTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceAllocID Main failed(0x%x)\n", s32Ret);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return s32Ret;
    }

    s32Ret = SourceAllocID(SOURCE_ID_EXTDEC, phExtTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceAllocID ExtMain failed(0x%x)\n", s32Ret);
        goto ERR_ALLOC_EXT;
    }

    //instant
    if (HI_TRUE == SourceServerCheckIsInstantiated(SOURCE_ID_MAIN))
    {
        HI_WARN_AO("Source(%d) is already instantiated\n", SOURCE_ID_MAIN);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_SUCCESS;
    }

    s32Ret = SourceCreate(SOURCE_ID_MAIN);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate Main failed(0x%x)\n", s32Ret);
        goto ERR_CREATE_MAIN;
    }

    s32Ret = SourceCreate(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate Assoc failed(0x%x)\n", s32Ret);
        goto ERR_CREATE_ASSOC;
    }

    (HI_VOID)SourceSetDuplicateStatus(SOURCE_ID_MAIN, HI_TRUE);

    s32Ret = SourceCreate(SOURCE_ID_EXTDEC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate ExtDec failed(0x%x)\n", s32Ret);
        goto ERR_CREATE_EXTDEC;
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;

ERR_CREATE_EXTDEC:
    SourceDestroyTrack(SOURCE_ID_ASSOC);

ERR_CREATE_ASSOC:
    SourceDestroyTrack(SOURCE_ID_MAIN);

ERR_CREATE_MAIN:
    SourceDeallocID(*phExtTrack);

ERR_ALLOC_EXT:
    SourceDeallocID(*phTrack);

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_Server_DeApllyID(HI_HANDLE hTrack, HI_HANDLE hExtTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if ((HI_TRUE != CheckIsMediaTrack(hTrack)) || (HI_TRUE != CheckIsMediaTrackIDApplied(hTrack)))
    {
        HI_ERR_AO("Invalid TrackID(0x%x)\n", hTrack);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_FAILURE;
    }

    if (HI_TRUE != SourceServerCheckIsInstantiated(SOURCE_ID_MAIN))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", SOURCE_ID_MAIN);
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        return HI_FAILURE;
    }

    s32Ret = SourceDeallocID(hExtTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDeallocID ExtTrack failed(0x%x)\n", s32Ret);
    }

    s32Ret = SourceDeallocID(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDeallocID Track failed(0x%x)\n", s32Ret);
    }

    //IF count down to 0
    HI_WARN_AO("\n **********DO NOT Destory Track***********\n");
    goto Exit;

#if 0
    // tmp reserved
    s32Ret = SourceDestroyTrack(SOURCE_ID_MAIN);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroyTrack SOURCE_ID_MAIN failed(0x%x)\n", s32Ret);
    }

    s32Ret = SourceDestroyTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroyTrack SOURCE_ID_ASSOC failed(0x%x)\n", s32Ret);
    }

    s32Ret = SourceDestroyTrack(SOURCE_ID_EXTDEC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroyTrack SOURCE_ID_EXTDEC failed(0x%x)\n", s32Ret);
    }
#endif

Exit:
    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);
    return s32Ret;
}

HI_S32 Source_Server_Create(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AO_NULL_PTR(pstTrackAttr);
    CHECK_AO_NULL_PTR(phTrack);

    enSourceID = GetSourceIDFromTrackType(pstTrackAttr->enTrackType);
    if ((SOURCE_ID_ASSOC == enSourceID) ||
        (SOURCE_ID_MAIN == enSourceID)  ||
        (SOURCE_ID_BUTT == enSourceID))
    {
        HI_ERR_AO("Invalid Source(0x%x)failed!\n", enSourceID);
        return HI_FAILURE;
    }

    if (HI_TRUE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is always instantiated\n", enSourceID);
        return HI_FAILURE;
    }

    s32Ret = SourceCreate(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceCreate Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    *phTrack = GetTrackIDFromSourceID(enSourceID);

    HI_WARN_AO("Source(%d) TrackHandle(0x%x)\n", enSourceID, *phTrack);

    return HI_SUCCESS;
}

HI_S32  Source_Server_GetIsbAddr(HI_UNF_SND_E enSound, HI_MPI_AO_SB_ATTR_S* pstIsbAttr)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    CHANNEL_TRACE();

    CHECK_AO_NULL_PTR(pstIsbAttr);

    enSourceID = GetSourceIDFromSourceType(pstIsbAttr->enType);
    if (SOURCE_ID_BUTT == enSourceID)
    {
        HI_ERR_AO("GetSourceID failed!\n");
        return HI_FAILURE;
    }

    pstSource = g_pstSourceManager->pstSource[enSourceID];
    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Source(%d) resource is invalid\n", enSourceID);
        return HI_ERR_AO_NULL_PTR;
    }

    return RENDER_ServerBuffer_GetISBAttr(pstSource->pRBuffer, pstIsbAttr);
}

HI_S32  Source_Server_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_TRUE == CheckIsSourceDuplicate(enSourceID))
    {
        s32Ret = SourceDestroyTrack(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("SourceDestroy Assoc failed(0x%x)\n", s32Ret);
        }
    }

    s32Ret = SourceDestroyTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroy Main failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_Server_DestroyTrackWithID(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    if ((HI_TRUE == CheckIsMediaTrack(hTrack)) || (HI_TRUE == CheckIsMediaTrackIDApplied(hTrack)))
    {
        if (HI_FALSE == CheckIsMediaTrackCreated(hTrack))
        {
            SOURCE_IO_UNLOCK(enSourceID);
            SOURCE_INST2_UNLOCK(enSourceID);
            SOURCE_INST_UNLOCK(enSourceID);
            //only id applied, do nothing
            return HI_SUCCESS;
        }

        MediaTrackIDMDestory(hTrack);
    }

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        SOURCE_IO_UNLOCK(enSourceID);
        SOURCE_INST2_UNLOCK(enSourceID);
        SOURCE_INST_UNLOCK(enSourceID);
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_TRUE == CheckIsSourceDuplicate(enSourceID))
    {
        s32Ret = SourceDestroyTrack(SOURCE_ID_ASSOC);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("SourceDestroy Assoc failed(0x%x)\n", s32Ret);
        }
    }

    s32Ret = SourceDestroyTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDestroy Main failed(0x%x)\n", s32Ret);
    }

    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32 Source_Server_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AO_NULL_PTR(pstAttr);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    if (HI_FALSE == SourceServerCheckIsInstantiated(enSourceID))
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    pstAttr->enTrackType = GetTrackTypeFromSourceID(enSourceID);
    pstAttr->u32StartThresholdMs = 0;
    // TODO: other attrs
    return HI_SUCCESS;
}

HI_S32 Source_Server_StartTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceStartTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStartTrack Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceStartTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStartTrack Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32  Source_Server_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source StopTrack %d\n", enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    s32Ret = SourceStopTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack Main failed(0x%x)\n", s32Ret);
        goto EXIT;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        goto EXIT;
    }

    s32Ret = SourceStopTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack Assoc failed(0x%x)\n", s32Ret);
    }

EXIT:
    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);

    return s32Ret;
}

HI_S32  Source_Server_PauseTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source PauseTrack %d\n", enSourceID);

    s32Ret = SourcePauseTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceStopTrack Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourcePauseTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourcePauseTrack Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source FlushTrack %d\n", enSourceID);

    SOURCE_INST_LOCK(enSourceID);
    SOURCE_INST2_LOCK(enSourceID);
    SOURCE_IO_LOCK(enSourceID);

    s32Ret = SourceFlushTrack(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceFlushTrack Main failed(0x%x)\n", s32Ret);
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        goto EXIT;
    }

    s32Ret = SourceFlushTrack(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceFlushTrack Assoc failed(0x%x)\n", s32Ret);
    }

EXIT:
    SOURCE_IO_UNLOCK(enSourceID);
    SOURCE_INST2_UNLOCK(enSourceID);
    SOURCE_INST_UNLOCK(enSourceID);
    return s32Ret;
}

HI_S32 Source_Server_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceSetTargetPts(enSourceID, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTargetPts Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceSetTargetPts(SOURCE_ID_ASSOC, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTargetPts Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_SetRepeatTargetPts(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceSetRepeatTargetPts(enSourceID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetRepeatTargetPts Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceSetRepeatTargetPts(SOURCE_ID_ASSOC);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetRepeatTargetPts Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceDropFrame(enSourceID, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDropFrame Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceDropFrame(SOURCE_ID_ASSOC, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceDropFrame Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_TRACK_SYNCMODE(enSyncMode);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceSetSyncMode(enSourceID, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetSyncMode Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceSetSyncMode(SOURCE_ID_ASSOC, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetSyncMode Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

#ifdef DPT
HI_S32 Source_Server_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    if ((HI_UNF_SND_SOURCE_ATV > enSource) || (HI_UNF_SND_SOURCE_BUTT <= enSource))
    {
        HI_ERR_AO("Source(0x%x) invalid!\n", enSource);
        return HI_ERR_AO_INVALID_PARA;
    }

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceSetTrackSource(enSourceID, enSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTrackSource (%d) failed(0x%x)\n", s32Ret, enSourceID);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceSetTrackSource(SOURCE_ID_ASSOC, enSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetTrackSource Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}
#endif

HI_S32 Source_Server_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    HI_WARN_AO("Source SetEosFlag %d bEosFlag:%d\n", enSourceID, bEosFlag);

    s32Ret = SourceSetEosFlag(enSourceID, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetEosFlag Main failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != CheckIsSourceDuplicate(enSourceID))
    {
        return HI_SUCCESS;
    }

    s32Ret = SourceSetEosFlag(SOURCE_ID_ASSOC, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("SourceSetEosFlag Assoc failed(0x%x)\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret;
    HI_U32 u32DelayMs = 0;
    SOURCE_ID_E enSourceID;

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    if (SOURCE_ID_MAIN == enSourceID)
    {
        *pu32DelayMs = u32DelayMs;
        return HI_SUCCESS;
    }

    s32Ret = SourceGetDelayMs(enSourceID, &u32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        *pu32DelayMs = 0;
        HI_ERR_AO("Source(%d) GetDelayMs failed(0x%x)\n", enSourceID, s32Ret);
        return s32Ret;
    }

    *pu32DelayMs = u32DelayMs;

    return HI_SUCCESS;
}

HI_S32 Source_Server_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AO_NULL_PTR(bEosState);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceGetEosState(enSourceID, bEosState);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceGetEosState, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AO_NULL_PTR(pstBufStatus);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceGetBufferStatus(enSourceID, pstBufStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceGetBufferStatus, s32Ret);
    }

    return s32Ret;
}

HI_S32  Source_Server_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstStreamInfo)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHECK_AO_NULL_PTR(pstStreamInfo);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceGetStreamInfo(enSourceID, pstStreamInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceGetStreamInfo, s32Ret);
    }

    return s32Ret;
}

HI_S32 Source_Server_GetNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    HI_S32 s32Ret;
    SOURCE_ID_E enSourceID;

    CHANNEL_TRACE();

    CHECK_AO_NULL_PTR(pstNewEvent);

    CHECK_AND_GET_SOURCEIDFROMTRACKID(hTrack, enSourceID);

    s32Ret = SourceGetNewEvent(enSourceID, pstNewEvent);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(SourceGetNewEvent, s32Ret);
    }

    return s32Ret;
}

HI_VOID Source_Server_DestroyMediaTrack(HI_VOID)
{
    if (g_pstSourceManager)
    {
        (HI_VOID)SourceDestroyTrack(SOURCE_ID_MAIN);
        (HI_VOID)SourceDestroyTrack(SOURCE_ID_ASSOC);
        (HI_VOID)SourceDestroyTrack(SOURCE_ID_EXTDEC);
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
