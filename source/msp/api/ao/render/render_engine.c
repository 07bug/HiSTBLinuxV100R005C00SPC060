/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_engine.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>
#include <sched.h>
#include <sys/prctl.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_engine.h"
#include "render_common.h"
#include "render_buffer.h"
#include "render_proc.h"
#include "engine_sink.h"
#include "engine_codec.h"
#include "engine_sync.h"
#include "engine_codec_private.h"
#include "pts_queue.h"
#include "ao_isb.h"
#include "engine_customer.h"
#include "engine_policy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define SOURCE_INPUT_ACQUIRE_LEN       (0xFFFFFFFF)
#define RENDER_THREAD_SLEEP_TIME       (5 * 1000)
#define MAX_PTS_FILE_PATH_LEN          (40)

#define RENDER_CODEC_VOLUME_DB_MIN     (-96)
#define RENDER_CODEC_VOLUME_DB_MAX     (0)
#define RENDER_CODEC_MUTE_FADE_MS      (10)
#define MS12_AAC_STATIC_DELAY          (80)
#define MS12_DOLBY_STATIC_DELAY        (0)

#define USER_PASSTHRUSETTING_UPDATE_FREQ  (10)

#define MIN_PTS(a,b) ((a < b) ? a : b)

const char* aPolicyResult[POLICY_DEC_BUTT + 1] =
{
    "POLICY_NONE",
    "POLICY_DEC_M",
    "POLICY_DEC_A",
    "POLICY_DEC_DUAL",
    "POLICY_DROP_M",
    "POLICY_DROP_A",
    "POLICY_DEC_BUTT",
};

static RENDER_MANAGER_S* g_pstEngineRenderManager = HI_NULL;
static ENGINE_MANAGER_S* g_pstEngineManager = HI_NULL;

#define CHECK_MEDIATRACK(enSourceID) \
    do { \
        if ((SOURCE_ID_MAIN != enSourceID) && (SOURCE_ID_ASSOC != enSourceID)) \
        { \
            HI_ERR_AO("Invalid Source id(0x%x) failed\n", enSourceID); \
            return HI_ERR_AO_INVALID_PARA; \
        } \
    } while(0)

static HI_VOID EngineLock(HI_VOID)
{
    SOURCE_ID_E enSourceID;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        SOURCE_INST_LOCK(enSourceID);
    }
}

static HI_VOID EngineUnLock(HI_VOID)
{
    SOURCE_ID_E enSourceID;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        SOURCE_INST_UNLOCK(enSourceID);
    }
}

static HI_VOID CodecLock(HI_VOID)
{
    HACODEC_INST_LOCK();
}

static HI_VOID CodecUnlock(HI_VOID)
{
    HACODEC_INST_UNLOCK();
}

static HI_VOID BufferLock(HI_VOID)
{
    BUF_ACQUIRE_LOCK();
}

static HI_VOID BufferUnlock(HI_VOID)
{
    BUF_ACQUIRE_UNLOCK();
}

#ifdef RENDER_DEBUG_SUPPORT
static HI_VOID SaveOutputPtsFile(SOURCE_S* pstSource)
{
    HI_CHAR cPts[MAX_PTS_FILE_PATH_LEN];
    FILE_DUMP_S* pstFileDump = &g_pstEngineRenderManager->stDumpManager.stPtsDump[pstSource->enSourceID];

    if (HI_FALSE == pstFileDump->bSaved)
    {
        if (HI_NULL != pstFileDump->pDumpFile)
        {
            fclose(pstFileDump->pDumpFile);
            pstFileDump->pDumpFile = HI_NULL;
        }

        return;
    }

    if (HI_NULL == pstFileDump->pDumpFile)
    {
        const HI_CHAR* aprefix = "/mnt/source_out_";
        const HI_CHAR* asuffix = ".pts";
        HI_CHAR cSoureId[2];
        HI_CHAR cFile[MAX_PTS_FILE_PATH_LEN];

        memset(cFile, 0, MAX_PTS_FILE_PATH_LEN);
        memset(cSoureId, 0, 2);

        strncpy(cFile, aprefix, strlen(aprefix));
        cSoureId[0] = pstSource->enSourceID + '0';
        strncat(cFile, cSoureId, strlen(cSoureId));
        strncat(cFile, asuffix, strlen(asuffix));
        HI_INFO_AO("fopen source in pts %s\n", cFile);

        pstFileDump->pDumpFile = fopen(cFile, "w");
        if (HI_NULL == pstFileDump->pDumpFile)
        {
            HI_ERR_AO("fopen pts debug %s failed\n", cFile);
            return;
        }

        HI_ERR_AO("[DEBUG INFO] Dump Out Pts File: SourceID(%d) %s\n", pstSource->enSourceID, cFile);
    }

    snprintf(cPts, MAX_PTS_FILE_PATH_LEN, "%08d, %10d\r", pstSource->u32CurStreamPts, pstSource->u32StreamConsumedBytes);

    HI_INFO_AO("fputs %s\n", cPts);
    fputs(cPts, pstFileDump->pDumpFile);
}
#endif

static HI_BOOL EngineIsSystemTrackAlone(HI_VOID)
{
    HI_BOOL bSystemTrackAlone = HI_TRUE;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    EngineLock();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        if (SOURCE_ID_OTTSOUND == enSourceID)
        {
            continue;
        }

        pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL != pstSource) && ((SOURCE_STATE_RUNNING == pstSource->enState) || (SOURCE_STATE_PAUSE == pstSource->enState)))
        {
            if (HI_TRUE == pstSource->bDataValid)
            {
                bSystemTrackAlone = HI_FALSE;
                break;
            }
        }
    }

    EngineUnLock();

    return bSystemTrackAlone;
}

static HI_S32 EngineCreateRenderOutBuf(HI_VOID)
{
    HI_U8* pMem;

    pMem = (HI_U8*)malloc(RENDER_BUFFER_SIZE * SOURCE_ID_BUTT);
    if (HI_NULL == pMem)
    {
        HI_ERR_AO("Source render buf malloc failed\n");
        return HI_FAILURE;
    }

    g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN]   = pMem;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_ASSOC]  = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_ASSOC;

    g_pstEngineManager->pROutBuffer[SOURCE_ID_SYSTEM] = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_SYSTEM;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_APP]    = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_APP;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_EXTDEC]  = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_EXTDEC;
    g_pstEngineManager->pROutBuffer[SOURCE_ID_OTTSOUND]  = pMem + RENDER_BUFFER_SIZE * SOURCE_ID_OTTSOUND;

    return HI_SUCCESS;
}

static HI_VOID EngineDestoryRenderOutBuf(HI_VOID)
{
    if (HI_NULL != g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN])
    {
        free(g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN]);
        g_pstEngineManager->pROutBuffer[SOURCE_ID_MAIN] = HI_NULL;
    }
}

static HI_S32 EngineLoadRenderLib(HI_VOID)
{
    HI_S32 s32Ret;

    CodecLock();

    s32Ret = HACodec_LoadRenderLib_Default(g_pstEngineManager->pstCodec);

    Sync_SetCodecHandle(g_pstEngineManager->pstCodec);

    CodecUnlock();

    return s32Ret;
}

static HI_VOID EngineGetOutFrameMs(HA_MS12_STREAM_S* pstMS12DecodeStream, SOURCE_ID_E enSourceID, HI_U32* pu32OutFrameMs)
{
    *pu32OutFrameMs = pstMS12DecodeStream->stOutput.u32OutFrameMs[enSourceID];
}

static HI_VOID EngineFindPts(SOURCE_MANAGER_S* pstSourceManager)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) || ((SOURCE_STATE_RUNNING != pstSource->enState) && (SOURCE_STATE_PAUSE != pstSource->enState)))
        {
            continue;
        }

        s32Ret = PTSQUEUE_Find(pstSource->pPtsQueue, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, &pstSource->u32CurStreamPts);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Source(%d) CurPos:%d failed(0x%x)\n", enSourceID, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, s32Ret);
        }
        else
        {
            PTS_PRINTF("Source(%d) ConsumeByte:%d DecLeftByte:%d CurPos:%d CurPts:%d\n", enSourceID,
                       pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes, pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes, pstSource->u32CurStreamPts);
        }
    }
}

static HI_VOID EngineUpdatePts(RENDER_MANAGER_S* pstRenderManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32OutFrameMs;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;
    HI_U32 u32UpdatePts;
    HA_CODEC_ID_E enCodecId = pstRenderManager->pstEngineManger->pstCodec->enCodecID;
    SOURCE_MANAGER_S* pstSourceManager = pstRenderManager->pstSourceManager;

    CHANNEL_TRACE();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_NULL == pstSource)
        {
            continue;
        }

        if ((SOURCE_STATE_RUNNING == pstSource->enState))
        {

        }
        else if ((SOURCE_STATE_PAUSE == pstSource->enState) && (HI_FALSE == pstSource->bPauseUpdateDelayMs))
        {
            pstSource->bPauseUpdateDelayMs = HI_TRUE;
        }
        else
        {
            continue;
        }

        if (0 != pstMS12DecodeStream->stOutput.u32AddMediaPauseMuteMs)
        {
            continue;
        }

        EngineGetOutFrameMs(pstMS12DecodeStream, enSourceID, &u32OutFrameMs);
        if (0 != u32OutFrameMs)
        {
            if (pstMS12DecodeStream->stOutput.u32AddMediaMixerMuteMs != 0)
            {
                HI_WARN_AO("u32AddMediaMixerMuteMs is bigger than 32, not update deta, mixerMute = %d\n", pstMS12DecodeStream->stOutput.u32AddMediaMixerMuteMs);
                pstSource->u32PreDecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID];
                continue;
            }

            u32UpdatePts = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID] + u32OutFrameMs - pstSource->u32PreDecoderPcmDelay - pstMS12DecodeStream->stOutput.u32AddMediaMixerMuteMs;
            PTSQUEUE_Update(pstSource->pPtsQueue, u32UpdatePts);
            pstSource->u32CurStreamPts = PTSQUEUE_GetReadPts(pstSource->pPtsQueue);

            PTS_PRINTF("Source(%d) PrePcmDelayMs:%d CurPcmDelayMs:%d NewCurPts:%d (AddPts:%d)\n", enSourceID,
                       pstSource->u32PreDecoderPcmDelay, pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID],
                       pstSource->u32CurStreamPts, u32UpdatePts);

            pstSource->u32PreDecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID];

            pstSource->bWorking = HI_TRUE;
            pstSource->bFirstTimeStarted = HI_FALSE;

            if (HA_AUDIO_ID_MS12_AAC == enCodecId)
            {
                if (USECASE_LOW_LATENCY == g_pstEngineManager->enUseCase)
                {
                    pstSource->u32DecoderStaticDelay = MS12_AAC_STATIC_DELAY;
                }
                else
                {
                    if (0 != pstMS12DecodeStream->stOutput.pstOutput->u32OrgSampleRate)
                    {
                        pstSource->u32DecoderStaticDelay =
                            (pstMS12DecodeStream->stOutput.u32DecoderStaticDelay[enSourceID] * 1000 / pstMS12DecodeStream->stOutput.pstOutput->u32OrgSampleRate);
                    }
                }
            }
            else if (HA_AUDIO_ID_MS12_DDP == enCodecId)
            {
                if (USECASE_LOW_LATENCY == g_pstEngineManager->enUseCase)
                {
                    pstSource->u32DecoderStaticDelay = MS12_DOLBY_STATIC_DELAY;
                }
                else
                {
                    if (0 != pstMS12DecodeStream->stOutput.pstOutput->u32OrgSampleRate)
                    {
                        pstSource->u32DecoderStaticDelay =
                            (pstMS12DecodeStream->stOutput.u32DecoderStaticDelay[enSourceID] * 1000 / pstMS12DecodeStream->stOutput.pstOutput->u32OrgSampleRate);
                    }
                }
            }
            HI_INFO_AO("DecStaticDelayMS:%d OrgSampleRate:%d\n", pstMS12DecodeStream->stOutput.u32DecoderStaticDelay[enSourceID],
                       pstMS12DecodeStream->stOutput.pstOutput->u32OrgSampleRate);

#ifdef RENDER_DEBUG_SUPPORT
            SaveOutputPtsFile(pstSource);
#endif
        }
        else
        {
            if (pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID] > pstSource->u32PreDecoderPcmDelay)
            {
                u32UpdatePts = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID] - pstSource->u32PreDecoderPcmDelay;
                PTSQUEUE_Update(pstSource->pPtsQueue, u32UpdatePts);
                pstSource->u32CurStreamPts = PTSQUEUE_GetReadPts(pstSource->pPtsQueue);
            }

            PTS_PRINTF("Source(%d) No Frame out, CurPcmDelayMs:%d, PrePcmDelayMs:%d\n", enSourceID,
                        pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID], pstSource->u32PreDecoderPcmDelay);

            pstSource->u32PreDecoderPcmDelay = pstMS12DecodeStream->stOutput.u32PcmDelayMs[enSourceID];
        }
    }
}

static HI_VOID EngineSetSinkFifoBufAvalid(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_BOOL bValid = (0 == pstMS12DecodeStream->stOutput.pstOutput->u32PcmOutSamplesPerFrame ? HI_FALSE : HI_TRUE);

    Sink_SetFifoBufValid(bValid);
}

static HI_VOID EngineUpdateStreamInfo(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream, HA_MS12_PROC_S* pstProc)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    CHANNEL_TRACE();

    // only update main stream info
    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_MAIN; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) || (SOURCE_STATE_RUNNING != pstSource->enState))
        {
            continue;
        }

        if ((HI_TRUE == pstSource->bEosFlag) &&
            (HI_FALSE == pstMS12DecodeStream->stOutput.bStreamEnough[enSourceID]))
        {
            pstSource->bEosState = HI_TRUE;
        }

        if ((pstSource->stRenderEvent.stStreamInfo.u32Channel != pstProc->stStreamProc[enSourceID].u32Acmod) ||
            (pstSource->stRenderEvent.stStreamInfo.enSampleRate != pstProc->stStreamProc[enSourceID].u32SampleRate))
        {
            pstSource->stRenderEvent.bFrameInfoChange = HI_TRUE;
        }

        pstSource->stRenderEvent.stStreamInfo.enACodecType = (HI_U32)pstProc->stStreamProc[enSourceID].enStreamType;
        pstSource->stRenderEvent.stStreamInfo.enBitDepth = HI_UNF_BIT_DEPTH_16;
        pstSource->stRenderEvent.stStreamInfo.u32Channel = pstProc->stStreamProc[enSourceID].u32Acmod;
        pstSource->stRenderEvent.stStreamInfo.u32BitRate = pstProc->stStreamProc[enSourceID].u32BitRate;
        pstSource->stRenderEvent.stStreamInfo.enSampleRate = pstProc->stStreamProc[enSourceID].u32SampleRate;
        pstSource->stRenderEvent.bUnSupportFormat = HI_FALSE;

        if (pstProc->stStreamProc[enSourceID].u32DecodeErrCnt >= RENDER_MAX_SOURCE_NUM)
        {
            pstSource->stRenderEvent.bStreamCorrupt = HI_TRUE;
        }

        if (pstMS12DecodeStream->stOutput.u32OutFrameMs[enSourceID] > 0)
        {
            pstSource->u32TotDecodeFrame++;
            pstSource->stRenderEvent.bNewFrame = HI_TRUE;
        }
    }
}

static HI_VOID EngineAcquireStreamData(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream, HI_U32* pu32StreamBufBytes)
{
    HI_S32 s32Ret;
    HI_U32 u32AcquireSize = 0;
    HI_U8* u8InputBuf[SOURCE_ID_BUTT] = {0};
    SOURCE_ID_E enSourceID = 0;
    SOURCE_S* pstSource;

    memset(pu32StreamBufBytes, 0, sizeof(HI_U32) * SOURCE_ID_BUTT);
    memset(pstMS12DecodeStream->stInput.pstInPack[SOURCE_ID_MAIN], 0, sizeof(HI_HADECODE_INPACKET_S) * SOURCE_ID_BUTT);

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource))
        {
            pstMS12DecodeStream->stInput.enStreamState[enSourceID] = MS12_STREAM_IDLE;
            continue;
        }

        if (SOURCE_STATE_PAUSE == pstSource->enState)
        {
            if ((enSourceID <= SOURCE_ID_EXTDEC) && (enSourceID != SOURCE_ID_ASSOC))
            {
                pstMS12DecodeStream->stOutput.u32AddMediaPauseMuteMs = pstSource->u32AddMediaPauseMuteMs;
            }
        }

        pstMS12DecodeStream->stInput.enStreamState[enSourceID] = (HI_U32)pstSource->enState;
        if ((SOURCE_STATE_RUNNING != pstSource->enState))
        {
            CHANNEL_PRINTF("Source(%d) stream is not available\n", enSourceID);
            continue;
        }

        if ((SOURCE_ID_OTTSOUND == enSourceID) && (HI_TRUE == pstSource->bActivate))
        {
            PTS_PRINTF("Source(%d) status is activate\n", enSourceID);
            pstMS12DecodeStream->stInput.enStreamState[enSourceID] = MS12_STREAM_ACTIVATE;
            pstSource->bActivate = HI_FALSE;
        }

        if (HI_FALSE == Sync_CheckIsSourceNeedDecode(pstSource))
        {
            continue;
        }

        u32AcquireSize = (enSourceID <= SOURCE_ID_ASSOC) ? pstSource->u32AcquireSize : SOURCE_INPUT_ACQUIRE_LEN;
        if (SOURCE_ID_EXTDEC == enSourceID)
        {
            s32Ret = RENDER_ServerFrame_Acquire(pstSource->pRBuffer, u32AcquireSize, &pstSource->stPackOut, &(pu32StreamBufBytes[enSourceID]));
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(RENDER_ServerFrame_Acquire, s32Ret);
            }

            if (pu32StreamBufBytes[enSourceID] > 0)
            {
                pstMS12DecodeStream->stInput.pstInPack[enSourceID]->pu8Data = (HI_U8*)(&pstSource->stPackOut);
                pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size = pu32StreamBufBytes[enSourceID];
            }
        }
        else
        {
            s32Ret = RENDER_ServerBuffer_Acquire(pstSource->pRBuffer, u32AcquireSize, &u8InputBuf[enSourceID], &(pu32StreamBufBytes[enSourceID]));
            if (HI_SUCCESS != s32Ret)
            {
                HI_LOG_PrintFuncErr(RENDER_ServerBuffer_Acquire, s32Ret);
            }

            if (pu32StreamBufBytes[enSourceID] > 0)
            {
                pstMS12DecodeStream->stInput.pstInPack[enSourceID]->pu8Data = u8InputBuf[enSourceID];
                pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size = pu32StreamBufBytes[enSourceID];
            }
        }
        PTS_PRINTF("Source(%d) Request InBufSizes:%d\n", enSourceID, pu32StreamBufBytes[enSourceID]);

        Proc_Source(pstSource);
    }
}

static HI_VOID EngineReleaseStreamData(SOURCE_MANAGER_S* pstSourceManager, HA_MS12_STREAM_S* pstMS12DecodeStream, HI_U32* pu32StreamBufBytes)
{
    HI_U32 u32ConsumedByte;
    HI_U32 u32DecoderLeftedByte;
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource) ||
            ((SOURCE_STATE_RUNNING != pstSource->enState) && (SOURCE_STATE_PAUSE != pstSource->enState)))
        {
            CHANNEL_PRINTF("Source(%d) stream is not available\n", enSourceID);
            continue;
        }

        u32ConsumedByte = pu32StreamBufBytes[enSourceID] - pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size;

        u32DecoderLeftedByte = pstMS12DecodeStream->stOutput.u32DecodeLeftBytes[enSourceID];
        pstSource->u32StreamConsumedBytes += u32ConsumedByte;
        pstSource->u32DecodeLeftBytes = u32DecoderLeftedByte;

        if (SOURCE_ID_ASSOC == enSourceID)
        {
            pstSource->u32DecodeLeftBytes = 0;
        }

        if (u32ConsumedByte > 0)
        {
            if (SOURCE_ID_EXTDEC == enSourceID)
            {
                RENDER_ServerFrame_Release(pstSource->pRBuffer, &pstSource->stPackOut, u32ConsumedByte);
            }
            else
            {
                RENDER_ServerBuffer_Release(pstSource->pRBuffer, u32ConsumedByte);
            }

            pstSource->bDecoderHadbeenStarted = HI_TRUE;
        }

        PTS_PRINTF("Source(%d) Request InSizeLeft:%d CurConsumeByte:%d TotalConsumeByte:%d DecLeftByte:%d\n",
                   enSourceID, pstMS12DecodeStream->stInput.pstInPack[enSourceID]->s32Size,
                   u32ConsumedByte, pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes);
    }
}

static HI_VOID EngineSendOutFrame(ENGINE_MANAGER_S* pstEngineManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_S32 s32Ret;

    CHANNEL_TRACE();

    s32Ret = Sink_SendData(pstMS12DecodeStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_AO("Sink_SendData failed(0x%x)\n", s32Ret);
    }
}

static HI_VOID EngineQueryRenderParam(HA_MS12_STREAM_S* pstMS12DecodeStream, AO_RENDER_ATTR_S* pstRenderParam)
{
    HI_S32 s32Ret;
    static HI_U32 u32UpdateCnt;

    CHANNEL_TRACE();

    if (0 == u32UpdateCnt % USER_PASSTHRUSETTING_UPDATE_FREQ)
    {
        s32Ret = Sink_UpdateRenderParam(pstRenderParam);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Sink_UpdateRenderParam, s32Ret);
            return;
        }

        pstMS12DecodeStream->stInput.bPassthruBypass = pstRenderParam->bPassthruBypass;

        s32Ret = Sink_SetOutputLatencyMode(pstRenderParam->enOutputMode);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Sink_SetOutputLatencyMode, s32Ret);
            return;
        }

        s32Ret = Sink_SetContinueOutputStatus(pstRenderParam->bContinueStatus);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Sink_SetContinueOutputStatus, s32Ret);
            return;
        }

        g_pstEngineManager->enUseCase = (HI_UNF_SND_OUTPUTLATENCY_LOW == pstRenderParam->enOutputMode) ? USECASE_LOW_LATENCY : USECASE_NORMAL;
    }

    u32UpdateCnt++;
}
#ifdef DPT
static HI_BOOL EngineCheckSourceIsFit(SOURCE_ID_E enSourceID, HI_UNF_SND_SOURCE_E enSource)
{
    if ((enSourceID <= SOURCE_ID_EXTDEC) &&
        (HI_UNF_SND_SOURCE_HDMI == enSource || HI_UNF_SND_SOURCE_DTV == enSource || HI_UNF_SND_SOURCE_MEDIA == enSource ||
         HI_UNF_SND_SOURCE_APP == enSource))
    {
        return HI_TRUE;
    }
    else if ((SOURCE_ID_OTTSOUND == enSourceID) && (HI_UNF_SND_SOURCE_UI == enSource || HI_UNF_SND_SOURCE_INJECT == enSource))
    {
        return HI_TRUE;
    }
    else if ((SOURCE_ID_SYSTEM == enSourceID) && (HI_UNF_SND_SOURCE_TTS == enSource || HI_UNF_SND_SOURCE_UI == enSource))
    {
        return HI_TRUE;
    }
    else if ((SOURCE_ID_APP == enSourceID) && (HI_UNF_SND_SOURCE_INJECT == enSource || HI_UNF_SND_SOURCE_TTS == enSource))
    {
        return HI_TRUE;
    }
    else
    {
        HI_WARN_AO("SourceID(%d)/TrackSource(%d) not fit!\n", enSourceID, enSource);
        return HI_FALSE;
    }
}

static HI_VOID EngineSetSourcePrescale(SOURCE_S* pstSource, AO_RENDER_ATTR_S* pstRenderParam)
{
    HI_UNF_SND_SOURCE_E enSource = HI_UNF_SND_SOURCE_BUTT;
    HI_UNF_SND_PRECIGAIN_ATTR_S* pstOldPrescale = HI_NULL;
    HI_UNF_SND_PRECIGAIN_ATTR_S* pstNewPrescale = HI_NULL;

    enSource = pstSource->enSource;
    if (enSource >= HI_UNF_SND_SOURCE_BUTT)
    {
        HI_ERR_AO("Invalid TrackSource(%d)!\n", enSource);
        return;
    }

    if (HI_FALSE == EngineCheckSourceIsFit(pstSource->enSourceID, enSource))
    {
        return;
    }

    pstOldPrescale = &pstSource->stPrescale[enSource];
    pstNewPrescale = &pstRenderParam->stTrackPrescale[enSource];

    if (pstOldPrescale->s32IntegerGain != pstNewPrescale->s32IntegerGain ||
        pstOldPrescale->s32DecimalGain != pstNewPrescale->s32DecimalGain)
    {
        HI_S32 s32Ret;
        HA_MS12_SET_SOURCEPRESCALE_S stPrescale = {0};

        stPrescale.enCmd = HA_CODEC_MS12_SET_SOURCEPRESCALE_CMD;
        stPrescale.s32IntegerGain = pstNewPrescale->s32IntegerGain;
        stPrescale.s32DecimalGain = pstNewPrescale->s32DecimalGain;

        s32Ret = Engine_SetCmd(pstSource->enSourceID, (HI_VOID*)&stPrescale);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Engine_SetCmd SourcePrescale (SourceID:%d) failed(0x%x)\n", pstSource->enSourceID, s32Ret);
            return;
        }

        pstOldPrescale->s32IntegerGain = pstNewPrescale->s32IntegerGain;
        pstOldPrescale->s32DecimalGain = pstNewPrescale->s32DecimalGain;
    }
}
#endif

static HI_VOID EngineApplyRenderParam(SOURCE_MANAGER_S* pstSourceManager, AO_RENDER_ATTR_S* pstRenderParam)
{
    SOURCE_ID_E enSourceID = SOURCE_ID_MAIN;
    SOURCE_S* pstSource = HI_NULL;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID < SOURCE_ID_BUTT; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource))
        {
            continue;
        }

        if ((SOURCE_STATE_RUNNING != pstSource->enState))
        {
            SYNC_PRINTF("Source(%d) stream is not available\n", enSourceID);
            continue;
        }

        if (HI_FALSE == Sync_CheckIsSourceNeedDecode(pstSource))
        {
            continue;
        }
#ifdef DPT
        EngineSetSourcePrescale(pstSource, pstRenderParam);
#endif
    }
}

static HI_BOOL EngineCheckIsStreamEnough(HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32StreamCnt;

    CHANNEL_TRACE();

    for (u32StreamCnt = 0; u32StreamCnt < MS12_MAX_STREAM_NUM; u32StreamCnt++)
    {
        if (HI_TRUE == pstMS12DecodeStream->stOutput.bStreamEnough[u32StreamCnt])
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

static HI_VOID EnginePtsMute(HI_BOOL bMute)
{
    HA_MS12_VOLUME_S stMs12Volume;

    HI_WARN_AO("EnginePtsMute bMute = %d\n", bMute);

    stMs12Volume.enCmd = HA_CODEC_MS12_SET_MIXER1_VOLUME_CMD;
    stMs12Volume.enVolumeCurve = MS12_VOLCURVE_LINEAR;
    stMs12Volume.s32VolumedB = (HI_TRUE == bMute) ? RENDER_CODEC_VOLUME_DB_MIN : RENDER_CODEC_VOLUME_DB_MAX;
    stMs12Volume.u32FadeMs = RENDER_CODEC_MUTE_FADE_MS;

    HACodec_CtlCommand(g_pstEngineManager->pstCodec, SOURCE_ID_MAIN, (HI_VOID*)&stMs12Volume);
}

static HI_VOID EngineProcessPtsMute(ENGINE_MANAGER_S* pstEngineManager)
{
    PTSMUTEQUEUE_POLICY enPtsMutePolicy;
    SOURCE_S* pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[SOURCE_ID_MAIN];
    if (HI_NULL == pstSource)
    {
        return;
    }

    enPtsMutePolicy = PTSMUTEQUEUE_Find(pstEngineManager->pPtsMuteQueue, pstSource->u32CurStreamPts);
    switch (enPtsMutePolicy)
    {
        case PTSMUTE_MUTE_NONE:
            break;
        case PTSMUTE_MUTE_START:
            EnginePtsMute(HI_TRUE);
            break;
        case PTSMUTE_MUTE_STOP:
            EnginePtsMute(HI_FALSE);
            break;
        default:
            break;
    }
}

static HI_VOID EngineGetTrackDelayMs(ENGINE_MANAGER_S* pstEngineManager, HA_MS12_STREAM_S* pstMS12DecodeStream)
{
    HI_U32 u32TrackDelayMs = 0;
    u32TrackDelayMs = *((HI_U32*)(pstEngineManager->stDelayMapAttr.pVirAddr));
    u32TrackDelayMs = u32TrackDelayMs >> 16;

    pstMS12DecodeStream->stInput.u32UseCase = (HI_U32)pstEngineManager->enUseCase;
    pstMS12DecodeStream->stInput.u32TrackDelayMs = u32TrackDelayMs;
}

static HI_VOID EngineExecuteDecPolicy(SOURCE_MANAGER_S* pstSourceManager, ENGINE_POLICY_S* pstPolicy)
{
    ENGINE_POLICY_E enDoPolicy = POLICY_NONE;
    SOURCE_S* pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    SOURCE_S* pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];
    HA_MS12_DEC_POLICY_S stPolicy = {HA_CODEC_MS12_SET_DEC_POLICY_CMD, MS12_DEC_MAIN};

    if ((HI_NULL == pstMainSource) || (HI_NULL == pstAssocSource))
    {
        return;
    }

    pstPolicy->u32CurPts[SOURCE_ID_MAIN]  = pstMainSource->u32CurStreamPts;
    pstPolicy->u32CurPts[SOURCE_ID_ASSOC] = pstAssocSource->u32CurStreamPts;

    enDoPolicy = Policy_Process(pstPolicy, pstMainSource->u32AcquireSize, pstAssocSource->u32AcquireSize);
    switch (enDoPolicy)
    {
        case POLICY_NONE:
            // SYNC_PRINTF("POLICY Status:%s\n", aPolicyResult[pstPolicy->enStatus]);
            break;
        case POLICY_DEC_M:
            SYNC_PRINTF("POLICY Update:%s -> %s   %d %d %d %d\n", aPolicyResult[pstPolicy->enLastStatus], aPolicyResult[enDoPolicy],
                        pstPolicy->bMainPtsInvert, pstPolicy->bAssocPtsInvert, pstMainSource->u32CurStreamPts, pstAssocSource->u32CurStreamPts);
            stPolicy.enPolicy = MS12_DEC_MAIN;
            pstPolicy->enLastStatus = POLICY_DEC_M;
            pstSourceManager->enPTSReportSource = SOURCE_ID_MAIN;
            HACodec_SetCmd(g_pstEngineManager->pstCodec, &stPolicy);
            break;
        case POLICY_DEC_A:
            SYNC_PRINTF("POLICY Update:%s -> %s %d %d %d %d\n", aPolicyResult[pstPolicy->enLastStatus], aPolicyResult[enDoPolicy],
                        pstPolicy->bMainPtsInvert, pstPolicy->bAssocPtsInvert, pstMainSource->u32CurStreamPts, pstAssocSource->u32CurStreamPts);
            stPolicy.enPolicy = MS12_DEC_ASSOC;
            pstPolicy->enLastStatus = POLICY_DEC_A;
            pstSourceManager->enPTSReportSource = SOURCE_ID_ASSOC;
            HACodec_SetCmd(g_pstEngineManager->pstCodec, &stPolicy);
            break;
        case POLICY_DEC_DUAL:
            SYNC_PRINTF("POLICY Update:%s -> %s  %d %d %d %d\n", aPolicyResult[pstPolicy->enLastStatus], aPolicyResult[enDoPolicy],
                        pstPolicy->bMainPtsInvert, pstPolicy->bAssocPtsInvert, pstMainSource->u32CurStreamPts, pstAssocSource->u32CurStreamPts);
            stPolicy.enPolicy = MS12_DEC_DUAL;
            pstPolicy->enLastStatus = POLICY_DEC_DUAL;
            HACodec_SetCmd(g_pstEngineManager->pstCodec, &stPolicy);
            break;
        case POLICY_DROP_M:
            SYNC_PRINTF("POLICY_DROP_M PTS(%d->%d)\n", pstMainSource->u32CurStreamPts, pstAssocSource->u32CurStreamPts);
            Sync_PolicyDropStream(pstMainSource, pstAssocSource->u32CurStreamPts, pstPolicy->bDropStream);
            break;
        case POLICY_DROP_A:
            SYNC_PRINTF("POLICY_DROP_A PTS(%d->%d)\n", pstAssocSource->u32CurStreamPts, pstMainSource->u32CurStreamPts);
            Sync_PolicyDropStream(pstAssocSource, pstMainSource->u32CurStreamPts, pstPolicy->bDropStream);
            break;
        default:
            SYNC_PRINTF("Invalid CMD(0x%x)\n", enDoPolicy);
            break;
    }

    if ((POLICY_DEC_M == pstPolicy->enStatus) || (HI_TRUE == pstPolicy->bAssocWaiting))
    {
        pstAssocSource->u32AcquireSize = 0;
    }

    if (POLICY_DEC_A == pstPolicy->enStatus)
    {
        pstMainSource->u32AcquireSize = 0;
    }

    if (HI_TRUE == pstPolicy->bMainPtsInvert)
    {
        pstPolicy->bMainPtsInvert = HI_FALSE;
        SYNC_PRINTF("Update new Main  PreCodePts:%d -> %d \n", pstMainSource->u32PreDecodePts, pstMainSource->u32CurStreamPts);
        pstMainSource->u32PreDecodePts = pstMainSource->u32CurStreamPts;
    }

    if (HI_TRUE == pstPolicy->bAssocPtsInvert)
    {
        pstPolicy->bAssocPtsInvert = HI_FALSE;
        SYNC_PRINTF("Update new Assoc PreCodePts:%d -> %d \n", pstAssocSource->u32PreDecodePts, pstAssocSource->u32CurStreamPts);
        pstAssocSource->u32PreDecodePts = pstAssocSource->u32CurStreamPts;
    }

    if (POLICY_DROP_M != enDoPolicy)
    {
        pstPolicy->u32PrePts[SOURCE_ID_MAIN]  = pstMainSource->u32CurStreamPts;
    }

    if (POLICY_DROP_A != enDoPolicy)
    {
        pstPolicy->u32PrePts[SOURCE_ID_ASSOC] = pstAssocSource->u32CurStreamPts;
    }
}

static HI_VOID EngineCheckStreamBytes(SOURCE_MANAGER_S* pstSourceManager)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TotalSize = 0;
    SOURCE_ID_E enSourceID = SOURCE_ID_MAIN;
    SOURCE_S* pstSource = HI_NULL;

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if ((HI_NULL == pstSource))
        {
            continue;
        }

        if ((SOURCE_STATE_RUNNING != pstSource->enState))
        {
            SYNC_PRINTF("Source(%d) stream is not available\n", enSourceID);
            continue;
        }

        if (HI_FALSE == Sync_CheckIsSourceNeedDecode(pstSource))
        {
            continue;
        }

        s32Ret = RENDER_ServerBuffer_GetDataSize(pstSource->pRBuffer, &u32TotalSize);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(RENDER_ServerBuffer_GetDataSize, s32Ret);
            //continue;
        }

        pstSource->u32AcquireSize = u32TotalSize;

        SYNC_PRINTF("Source(%d):InSize(%d),DecLeftByte(%d),CurPTS(%d)\n", enSourceID, u32TotalSize,
                    pstSource->u32DecodeLeftBytes, pstSource->u32CurStreamPts);
    }
}

static HI_VOID EngineProcessPolicy(SOURCE_MANAGER_S* pstSourceManager, ENGINE_POLICY_S* pstPolicy)
{
    EngineCheckStreamBytes(pstSourceManager);

    EngineExecuteDecPolicy(pstSourceManager, pstPolicy);
}

static HI_VOID* EngineDecThread(HI_VOID* arg)
{
    HI_S32 s32Ret;
    HA_MS12_DECODE_STREAM_S stMS12DecodeStream;
    HI_U32 aInStreamSize[SOURCE_ID_BUTT] = {0};
    AO_RENDER_ATTR_S stRenderParam = {0};
    struct timespec stSlpTm;

    prctl(PR_SET_NAME,"HiRenderDecThread");

#ifdef HI_LINUX_PRODUCT
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(CPU_MASK, &mask);
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0)
        {
            HI_WARN_AO("set thread HiRenderDecThread affinity failed\n");
        }
        else
        {
            HI_WARN_AO("set thread HiRenderDecThread affinity success\n");
        }
    }
#endif

    while (HI_FALSE == HACodec_CheckIsRenderLibLoaded(g_pstEngineManager->pstCodec))
    {
        stSlpTm.tv_sec = 0;
        stSlpTm.tv_nsec = RENDER_THREAD_SLEEP_TIME * 1000;
        if(0 != nanosleep(&stSlpTm, NULL))
        {
            HI_ERR_AO("nanosleep err.\n");
        }
        if (HI_TRUE == g_pstEngineManager->bThreadExit)
        {
            return (HI_VOID*)HI_NULL;
        }
    }

    s32Ret = HACodec_InitDecodeInfo(g_pstEngineManager->pstCodec, &stMS12DecodeStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HACodec_InitDecodeInfo, s32Ret);
        return (HI_VOID*)HI_NULL;
    }

    stMS12DecodeStream.enCmd = HA_CODEC_MS12_DECODE_FRAME_CMD;

    while (HI_TRUE != g_pstEngineManager->bThreadExit)
    {
        EngineQueryRenderParam(&stMS12DecodeStream.stStream, &stRenderParam);

        BufferLock();

        EngineLock();

        EngineFindPts(g_pstEngineRenderManager->pstSourceManager);

        Sync_Prepare(g_pstEngineRenderManager->pstSourceManager);

        EngineProcessPolicy(g_pstEngineRenderManager->pstSourceManager, &g_pstEngineManager->stPolicy);

        EngineAcquireStreamData(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream, aInStreamSize);

        EngineProcessPtsMute(g_pstEngineManager);

        EngineGetTrackDelayMs(g_pstEngineManager, &stMS12DecodeStream.stStream);

        EngineApplyRenderParam(g_pstEngineRenderManager->pstSourceManager, &stRenderParam);

        EngineUnLock();

        Proc_Engine(g_pstEngineManager, STATISTICS_START);

        CodecLock();

        s32Ret = HACodec_Render(g_pstEngineManager->pstCodec, &stMS12DecodeStream);
        if (HI_SUCCESS != s32Ret)
        {
            CHANNEL_PRINTF("EngineRenderSource not success(0x%x)!\n", s32Ret);
        }
        else
        {
            CHANNEL_PRINTF("EngineRenderSource success pcm sample:%d\n", stMS12DecodeStream.stStream.stOutput.pstOutput->u32PcmOutSamplesPerFrame);
        }

        HACodec_UpdateDataStatus(g_pstEngineManager->pstCodec, stMS12DecodeStream.stStream.stOutput.bStreamEnough);

        CodecUnlock();

        Proc_Engine(g_pstEngineManager, STATISTICS_STOP);

        EngineLock();

        EngineReleaseStreamData(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream, aInStreamSize);

        EngineUpdatePts(g_pstEngineRenderManager, &stMS12DecodeStream.stStream);

        EngineSetSinkFifoBufAvalid(&stMS12DecodeStream.stStream);

        EngineUnLock();

        BufferUnlock();

        EngineSendOutFrame(g_pstEngineManager, &stMS12DecodeStream.stStream);

        EngineUpdateStreamInfo(g_pstEngineRenderManager->pstSourceManager, &stMS12DecodeStream.stStream, &g_pstEngineManager->pstCodec->pstMs12Proc->stProc);

        if (HI_FALSE == EngineCheckIsStreamEnough(&stMS12DecodeStream.stStream))
        {
            stSlpTm.tv_sec = 0;
            stSlpTm.tv_nsec = RENDER_THREAD_SLEEP_TIME * 1000;
            if(0 != nanosleep(&stSlpTm, NULL))
            {
                HI_ERR_AO("nanosleep err.\n");
            }
        }
    }

    return (HI_VOID*)HI_NULL;
}

static HI_S32 EngineGetPts(SOURCE_MANAGER_S* pstSourceManager, SOURCE_ID_E enSourceID, HI_U32* pu32Pts, HI_U32* pu32OrgPtsMs)
{
    HI_S32 s32Ret;
    SOURCE_S* pstSource = pstSourceManager->pstSource[enSourceID];
    static HI_U32 s_pts = 0;

    if (HI_NULL == pstSource)
    {
        HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
        return HI_ERR_AO_INVALID_PARA;
    }

    if (HI_FALSE == pstSource->bWorking)
    {
        HI_U32 u32DataSize = 0;

        PTS_PRINTF("Source(%d) not working state(CurPts:%d)\n", enSourceID, pstSource->u32CurStreamPts);

        (HI_VOID)RENDER_ServerBuffer_GetDataSize(pstSource->pRBuffer, &u32DataSize);
        if (0 != u32DataSize)
        {
            *pu32Pts = pstSource->u32CurStreamPts;
            *pu32OrgPtsMs = pstSource->u32CurStreamPts;
            return HI_SUCCESS;
        }

        return HI_ERR_AO_NOT_INIT;
    }

    //when no data sent,just use PreDecodePts(same as stream pts)
    s32Ret = Sink_GetPreDecoderPts(pstSource, pu32Pts);
    if (HI_SUCCESS == s32Ret)
    {
        PTS_PRINTF("Source(%d) PreDecode Pts:%d\n", enSourceID, *pu32Pts);
        return HI_SUCCESS;
    }

    s32Ret = Sink_GetSyncDelayMs(pstSource, pu32Pts, pu32OrgPtsMs);
    if (HI_SUCCESS != s32Ret)
    {
        PTS_PRINTF("Source(%d) have no valid pts\n", enSourceID);
        return HI_ERR_AO_NOT_INIT;
    }

    if (*pu32Pts < s_pts) //for pts trace
    {
        HI_WARN_AO("seems error pts %d -> %d\n", s_pts, *pu32Pts);
    }

    s_pts = *pu32Pts;

    return HI_SUCCESS;
}

static HI_S32 EngineGetSinkDelayMs(ENGINE_MANAGER_S* pstEngineManager, HI_U32* pu32DelayMs)
{
    return Sink_GetDelayMs(pu32DelayMs);
}

static HI_S32 EngineSetTrackConfig(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig = pConfig;
    HI_VOID* pCmd = HI_NULL;
    HA_MS12_VOLUME_S stVolume;
    HA_MS12_SET_EOSFLAG_S stEosFlag;
    HA_MS12_SET_MEDIAVOLATTENUATE_S stAttenuate;
    HA_MS12_SET_ATMOSLOCK_S stAtmosLock;

    HI_WARN_PrintH32(pstConfig->u32ConfigType);

    switch (pstConfig->u32ConfigType)
    {
        case CONFIG_VOLUME:
        {
            VOLUME_CONFIG_S* pstVolume = pstConfig->pConfigData;

            CHECK_MEDIATRACK(enSourceID);

            stVolume.enCmd = HA_CODEC_MS12_SET_VOLUME_CMD;
            stVolume.enVolumeCurve = pstVolume->enVolumeCurve;
            stVolume.s32VolumedB = pstVolume->s32VolumedB;
            stVolume.u32FadeMs = pstVolume->u32FadeMs;
            pCmd = (HI_VOID*)&stVolume;
            break;
        }
        case CONFIG_SETEOSFLAG:
        {
            SOURCE_S* pstSource;
            SETEOSFLAG_CONFIG_S* pstEosFlag = pstConfig->pConfigData;

            SOURCE_INST_LOCK(enSourceID);

            pstSource = g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID];
            if (HI_NULL == pstSource)
            {
                HI_ERR_AO("Source(%d) is not instantiated\n", enSourceID);
                SOURCE_INST_UNLOCK(enSourceID);
                return HI_ERR_AO_INVALID_PARA;
            }

            stEosFlag.enCmd = HA_CODEC_MS12_SET_EOSFLAG_CMD;
            stEosFlag.bEosFlag = pstEosFlag->bEosFlag;
            pCmd = (HI_VOID*)&stEosFlag;
            pstSource->bDataValid = HI_FALSE;

            SOURCE_INST_UNLOCK(enSourceID);
            break;
        }
        case CONFIG_SETMEDIAVOLUMEATTENUATION:
        {
            SETMEDIAVOLUMEATTENUATION_CONFIG_S* pstAttenuate = pstConfig->pConfigData;
            stAttenuate.enCmd = HA_CODEC_MS12_SET_MEDIAVOLATTENUATE_CMD;
            stAttenuate.bEnable = pstAttenuate->bAttenuate;
            pCmd = (HI_VOID*)&stAttenuate;
            break;
        }
        case CONFIG_SETCONTINUOUSOUTPUTSTATUS:
        {
            HI_ERR_PrintInfo("Not Support: CONFIG_SETCONTINUOUSOUTPUTSTATUS");
            return HI_SUCCESS;
        }
        case CONFIG_SETATMOSLOCKOUTPUT:
        {
            SETATMOSLOCK_CONFIG_S* pstAtmosLock = pstConfig->pConfigData;
            stAtmosLock.enCmd = HA_CODEC_MS12_SET_ATMOSLOCK_CMD;
            stAtmosLock.bEnable = pstAtmosLock->bEnable;
            pCmd = (HI_VOID*)&stAtmosLock;
            break;
        }
        case CONFIG_SETCONTINUOUSOUTPUTWITHDEEPBUF:
        {
            HI_ERR_PrintInfo("Not Support: CONFIG_SETCONTINUOUSOUTPUTWITHDEEPBUF");
            return HI_SUCCESS;
        }
        default:
        {
            HI_ERR_AO("Unknown ConfigType:0x%x\n", pstConfig->u32ConfigType);
            return HI_ERR_AO_INVALID_PARA;
        }
    }

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, pCmd);
}

static HI_S32 EngineGetTrackConfig(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    HI_UNF_AUDIOTRACK_CONFIG_S* pstConfig = pConfig;

    switch (pstConfig->u32ConfigType)
    {
        case CONFIG_GETSYSTEMTRACKALONEFLAG:
        {
            GETSYSTRACKALONE_CONFIG_S* pstIsConfig = pstConfig->pConfigData;
            pstIsConfig->bAlone = EngineIsSystemTrackAlone();
            return HI_SUCCESS;
        }
        case CONFIG_GETAUDIOOUTPUTUSECASE:
        {
            GETAUDIOOUTPUTUSECASE_CONFIG_S* pstUseCaseConfig = pstConfig->pConfigData;
            pstUseCaseConfig->u32UseCase = (HI_U32)g_pstEngineManager->enUseCase;
            return HI_SUCCESS;
        }
        case CONFIG_VOLUME:
        {
            return HI_ERR_AO_NOTSUPPORT;
        }
        default:
        {
            HI_ERR_AO("Unknown ConfigType:0x%x \n", pstConfig->u32ConfigType);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 EngineResetDecoder(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID)
{
    HI_S32 s32Cmd = HA_CODEC_MS12_RESET_CMD;

    if (enSourceID >= SOURCE_ID_BUTT)
    {
        return HI_FAILURE;
    }

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, (HI_VOID*)&s32Cmd);
}

static HI_S32 EngineSetEosFlag(ENGINE_MANAGER_S* pstEngineManager, const SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    HA_MS12_SET_EOSFLAG_S stEosFlag;

    stEosFlag.enCmd = HA_CODEC_MS12_SET_EOSFLAG_CMD;
    stEosFlag.bEosFlag = bEosFlag;

    return HACodec_CtlCommand(pstEngineManager->pstCodec, enSourceID, (HI_VOID*)&stEosFlag);
}

static HI_S32 EngineGetAllInfo(ENGINE_MANAGER_S* pstEngineManager, HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo)
{
    HA_MS12_PROC_S* pstProcInfo = &(pstEngineManager->pstCodec->pstMs12Proc->stProc);
    pstAllInfo->u32TotalDecFrameNum =  pstProcInfo->stStreamProc[SOURCE_ID_MAIN].u32DecodeOkCnt;
    pstAllInfo->u32ErrDecFrameNum = pstProcInfo->stStreamProc[SOURCE_ID_MAIN].u32DecodeErrCnt;

    return HI_SUCCESS;
}

HI_S32 Engine_Init(RENDER_MANAGER_S* pstRenderManager)
{
    HI_S32 s32Ret;

    g_pstEngineManager = (ENGINE_MANAGER_S*)malloc(sizeof(ENGINE_MANAGER_S));
    if (HI_NULL == g_pstEngineManager)
    {
        HI_ERR_AO("Source manager malloc failed!\n");
        return HI_FAILURE;
    }

    memset(g_pstEngineManager, 0, sizeof(ENGINE_MANAGER_S));

    s32Ret = HACodec_Init(&g_pstEngineManager->pstCodec);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HACodec_Init, s32Ret);
        goto ERR_INITHACODEC;
    }

    s32Ret = PTSMUTEQUEUE_Create(&g_pstEngineManager->pPtsMuteQueue);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(PTSMUTEQUEUE_Create, s32Ret);
        goto ERR_CREATE_PTSMUTE;
    }

    pstRenderManager->pstEngineManger = g_pstEngineManager;
    g_pstEngineRenderManager = pstRenderManager;

    return HI_SUCCESS;

ERR_CREATE_PTSMUTE:
    HACodec_DeInit(g_pstEngineManager->pstCodec);

ERR_INITHACODEC:
    free(g_pstEngineManager);
    g_pstEngineManager = HI_NULL;

    return HI_FAILURE;
}

HI_S32 Engine_Deinit(HI_VOID)
{
    if (g_pstEngineManager)
    {
        PTSMUTEQUEUE_Destroy(g_pstEngineManager->pPtsMuteQueue);
        HACodec_DeInit(g_pstEngineManager->pstCodec);

        free(g_pstEngineManager);
        g_pstEngineManager = HI_NULL;
    }

    if (g_pstEngineRenderManager)
    {
        g_pstEngineRenderManager->pstEngineManger = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 Engine_Create(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = EngineLoadRenderLib();
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(EngineLoadRenderLib, s32Ret);
        return s32Ret;
    }

    s32Ret = EngineCreateRenderOutBuf();
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(EngineCreateRenderOutBuf, s32Ret);
        goto ERR_RENDER_OUTBUF_CREATE;
    }

    s32Ret = Sink_Init(g_pstEngineRenderManager);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Sink_Init, s32Ret);
        goto ERR_INITHADEC;
    }

    g_pstEngineManager->bThreadExit = HI_FALSE;

    s32Ret = pthread_create(&g_pstEngineManager->Thread, HI_NULL, EngineDecThread, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AO("pthread_create failied\n");
        goto ERR_SINK_CREATE;
    }

    return s32Ret;

ERR_SINK_CREATE:
    (HI_VOID)Sink_Deinit();

ERR_INITHADEC:
    EngineDestoryRenderOutBuf();

ERR_RENDER_OUTBUF_CREATE:
    HACodec_DeInitDecodeInfo(g_pstEngineManager->pstCodec);
    HACodec_UnLoadRenderLib(g_pstEngineManager->pstCodec);

    return s32Ret;
}

HI_VOID Engine_Destroy(HI_VOID)
{
    if (g_pstEngineManager)
    {
        HI_S32 s32Ret;

        g_pstEngineManager->bThreadExit = HI_TRUE;
        pthread_join(g_pstEngineManager->Thread, HI_NULL);

        s32Ret = Sink_Deinit();
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Sink_Deinit, s32Ret);
        }

        EngineDestoryRenderOutBuf();
        HACodec_DeInitDecodeInfo(g_pstEngineManager->pstCodec);
        HACodec_UnLoadRenderLib(g_pstEngineManager->pstCodec);
    }
}

HI_S32 Engine_DropTrackStream(const SOURCE_ID_E enSourceID, HI_U32 u32SeekPts)
{
    return Sync_DropStream(g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID], u32SeekPts);
}

HI_S32 Engine_SetAttr(const SOURCE_ID_E enSourceID, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret;

    CodecLock();

    s32Ret = HACodec_SetRenderAttr(g_pstEngineManager->pstCodec, pstRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HACodec_SetRenderAttr, s32Ret);
    }

    Sync_SetCodecHandle(g_pstEngineManager->pstCodec);

    CodecUnlock();

    return s32Ret;
}

HI_S32 Engine_SetCmd(const SOURCE_ID_E enSourceID, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;
    HI_U32 u32Cmd;

    CHECK_AO_NULL_PTR(pstRenderCmd);

    u32Cmd = *((HI_U32*)pstRenderCmd);
    if (HA_CODEC_MS12_SET_PTS_MUTE_CMD == u32Cmd)
    {
        HA_MS12_SET_PTS_MUTE_S* pstPtsMute;
        HI_WARN_AO("Receive SET_PTS_MUTE_CMD\n");

        pstPtsMute = (HA_MS12_SET_PTS_MUTE_S*)pstRenderCmd;
        s32Ret = PTSMUTEQUEUE_Add(g_pstEngineManager->pPtsMuteQueue, pstPtsMute->u32StartPts, pstPtsMute->u32StopPts);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(PTSMUTEQUEUE_Add, s32Ret);
        }

        return s32Ret;
    }

    s32Ret = HACodec_CtlCommand(g_pstEngineManager->pstCodec, enSourceID, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HACodec_CtlCommand, s32Ret);
        if (HA_ErrorInvalidParameter == s32Ret)
        {
            s32Ret = HI_ERR_AO_INVALID_PARA;
        }
    }

    return s32Ret;
}

HI_S32 Engine_GetCmd(HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret;

    s32Ret = HACodec_GetCmd(g_pstEngineManager->pstCodec, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HACodec_GetCmd, s32Ret);
    }

    return s32Ret;
}

HI_S32 Engine_GetTrackPts(const SOURCE_ID_E enSourceID, HI_U32* pu32Pts, HI_U32* pu32OrgPtsMs)
{
    return EngineGetPts(g_pstEngineRenderManager->pstSourceManager, enSourceID, pu32Pts, pu32OrgPtsMs);
}

HI_S32 Engine_GetSinkDelayMs(HI_U32* pu32DelayMs)
{
    return EngineGetSinkDelayMs(g_pstEngineManager, pu32DelayMs);
}

HI_S32 Engine_SetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    return EngineSetTrackConfig(g_pstEngineManager, enSourceID, pConfig);
}

HI_S32 Engine_GetTrackConfig(const SOURCE_ID_E enSourceID, HI_VOID* pConfig)
{
    return EngineGetTrackConfig(g_pstEngineManager, enSourceID, pConfig);
}

HI_S32 Engine_ResetDecoder(const SOURCE_ID_E enSourceID)
{
    HI_S32 s32Ret;

    if (SOURCE_ID_MAIN == enSourceID)
    {
        PTSMUTEQUEUE_Reset(g_pstEngineManager->pPtsMuteQueue);
    }

    BufferLock();

    s32Ret = EngineResetDecoder(g_pstEngineManager, enSourceID);

    BufferUnlock();

    return s32Ret;
}

HI_S32 Engine_SetEosFlag(const SOURCE_ID_E enSourceID, HI_BOOL bEosFlag)
{
    return EngineSetEosFlag(g_pstEngineManager, enSourceID, bEosFlag);
}

HI_S32 Engine_GetAllInfo(HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo)
{
    return EngineGetAllInfo(g_pstEngineManager, pstAllInfo);
}

HI_BOOL Engine_CheckIsInstantiated(SOURCE_ID_E enSourceID)
{
    return (HI_BOOL)(HI_NULL != g_pstEngineRenderManager->pstSourceManager->pstSource[enSourceID]);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
