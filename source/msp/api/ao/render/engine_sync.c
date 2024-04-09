/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: engine_codec.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "render_common.h"
#include "render_buffer.h"
#include "engine_codec.h"
#include "engine_codec_private.h"
#include "engine_sink.h"
#include "pts_queue.h"

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#define trace()  HI_INFO_AO("%s called\n", __func__)

#define STREAM_WRAP_PTS_THRESHOLD   (5000)
#define SEEK_FRAME_TIMEOUT_MAX_CNT  (6)  //about 30ms

ENGINE_CODEC_S* g_pstSyncCodec;

const char* aSeekResult[PTS_SEEK_BUTT] =
{
    "PTS_SEEK_NONE",
    "PTS_SEEK_ALIGN",
    "PTS_SEEK_PACKAGE",
    "PTS_SEEK_FRAME",
};

static HI_VOID EnableDecode(SOURCE_S* pstSource, HI_BOOL bEnable)
{
    trace();

    if ((HI_TRUE == bEnable) && (HI_FALSE == pstSource->bDecoding))
    {
        pstSource->bDecoding = HI_TRUE;
    }
    else if ((HI_FALSE == bEnable) && (HI_TRUE == pstSource->bDecoding) &&
             (HI_FALSE == pstSource->bEnableDecoder))
    {
        pstSource->bDecoding = HI_FALSE;
    }

    HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, pstSource->bDecoding);
}

static HI_VOID DropStream(HI_VOID* handle, HI_U32 u32DataSize)
{
    HI_S32 i;
    HI_S32 s32Ret;
    HI_U32 u32ReleaseSize = u32DataSize;
    HI_U32 u32Size = 0;
    HI_U8* pTempBuf = HI_NULL;

    trace();

    for (i = 0; i < 2; i++)
    {
        s32Ret = RENDER_ServerBuffer_Acquire(handle, u32ReleaseSize, &pTempBuf, &u32Size);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Acquire buf failed(0x%x)\n", s32Ret);
            return;
        }

        SYNC_PRINTF("RENDER_ServerBuffer_Release wantedsize:%d realsize:%d\n", u32ReleaseSize, u32Size);

        s32Ret = RENDER_ServerBuffer_Release(handle, u32Size);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_AO("Release buf failed(0x%x)\n", s32Ret);
            return;
        }

        u32ReleaseSize -= u32Size;
        if (0 == u32ReleaseSize)
        {
            break;
        }
    }
}

static HI_BOOL CheckIsPreSyncModeValid(SOURCE_S* pstSource)
{
    if (HI_NULL == pstSource || HI_FALSE == pstSource->bSeekFrame)
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_VOID SyncUpdateTargetPts(SOURCE_S* pstSource)
{
    HI_S32 s32Ret;
    HI_U32 u32DelayMs = 0;

    s32Ret = Sink_GetTrackDelayMs(&u32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        PTS_PRINTF("Sink_GetTrackDelayMs Failed(0x%x)\n", s32Ret);
    }

    PTS_PRINTF("Update TargetPts %d to %d  OrgTargetPts/Trackdelay/Staticdelay:(%d/%d/%d)\n",
                pstSource->u32TargetPts, pstSource->u32OrgTargetPts + u32DelayMs,
                pstSource->u32OrgTargetPts, u32DelayMs, pstSource->u32DecoderStaticDelay);

    pstSource->u32TargetPts = pstSource->u32OrgTargetPts + u32DelayMs + pstSource->u32DecoderStaticDelay;
    pstSource->u32ExtraTargetPtsMs = u32DelayMs + pstSource->u32DecoderStaticDelay;
}

static HI_BOOL CheckIsTargetRequirementMeeted(SOURCE_S* pstSource)
{
    if (HI_INVALID_PTS == pstSource->u32CurStreamPts)
    {
        SYNC_PRINTF("Source[%d] TargetPts:%d > CurPts:%d\n", pstSource->enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);
        return HI_FALSE;
    }

    SyncUpdateTargetPts(pstSource);

    if ((pstSource->u32CurStreamPts + RENDER_PTS_MAX_DIFF) < pstSource->u32TargetPts)
    {
        SYNC_PRINTF("Source[%d] TargetPts:%d > CurPts:%d\n", pstSource->enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);
        return HI_FALSE;
    }

    if (pstSource->u32CurStreamPts > pstSource->u32TargetPts + STREAM_WRAP_PTS_THRESHOLD)
    {
        SYNC_PRINTF("Source[%d] CurPts:%d TargetPts:%d Maybe Invert\n", pstSource->enSourceID, pstSource->u32CurStreamPts, pstSource->u32TargetPts);
        return HI_FALSE;
    }

    pstSource->bDoWipeInvalidPTS = HI_FALSE;    //exitdropmode maybe called by policy, but Invalid Pts should be wiped out, so it's here.

    return HI_TRUE;
}

static HI_BOOL CheckIsAdjustStreamNeeded(SOURCE_S* pstSource)
{
    if (PKG_SEEK_MODE_INTER == pstSource->enPkGSeekType)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL CheckIsDecoderHadbeenStart(SOURCE_S* pstSource)
{
    return pstSource->bDecoderHadbeenStarted;
}

static HI_BOOL CheckIsExitDropMode(SOURCE_S* pstSource)
{
    if ((HI_FALSE == pstSource->bSeekFrame) && (PKG_SEEK_MODE_NONE == pstSource->enPkGSeekType))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

/*static HI_VOID ForceAdjustFrameMode(SOURCE_S* pstSource)
{
    pstSource->enPkGSeekType = PKG_SEEK_MODE_INTRA;;
}*/

static HI_VOID ExitDropMode(SOURCE_S* pstSource)
{
    SYNC_PRINTF("Source[%d] TargetPts:%d  CurPts:%d EXIT Drop Mode\n", pstSource->enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

    EnableDecode(pstSource, HI_FALSE);

    //when target is 0, PredecodePts has to update here
    pstSource->u32PreDecodePts = pstSource->u32CurStreamPts;

    pstSource->bSeekFrame = HI_FALSE;
    pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
    pstSource->bWorking = HI_TRUE;
    pstSource->u32SeekFrameTimeout = 0;
}

/* for pcr sync mode, we first reset the decoder, and the lastest that had been update */
static HI_VOID SyncPCRAlignPacket(SOURCE_S* pstSource, HI_BOOL* pbPCRSyncMode, HI_BOOL* pbDoresetCodec)
{
    HI_U32 u32AlignedPos = 0;
    HI_U32 u32AlignedPts = 0;

    *pbPCRSyncMode = HI_FALSE;

    if (HI_TRUE != CheckIsDecoderHadbeenStart(pstSource))
    {
        *pbDoresetCodec = HI_FALSE;
        return;
    }

    SYNC_PRINTF("Decoder Source(%d) is started, reset decoder\n", pstSource->enSourceID);

    HACodec_SoftResetDecoder(g_pstSyncCodec, pstSource->enSourceID);
    //pstSource->bDecoderHadbeenStarted = HI_FALSE;
    pstSource->u32DecodeLeftBytes = 0;
    pstSource->u32DecoderPcmDelay = 0;
    pstSource->u32PreDecoderPcmDelay = 0;
    *pbDoresetCodec = HI_TRUE;

    //the packet pts being updated means it is not align packet
    if (HI_TRUE == PTSQUEUE_UpdatedAlignPacket(pstSource->pPtsQueue, pstSource->u32StreamConsumedBytes, &u32AlignedPos, &u32AlignedPts))
    {
        HI_S32 s32DropBytes;

        SYNC_PRINTF("WipeUpdatedPacket Source(%d) NeW StreamConsumedBytes:%d CurStreamPts:%d\n", pstSource->enSourceID, u32AlignedPos, u32AlignedPts);

        s32DropBytes = (HI_S32)u32AlignedPos - pstSource->u32StreamConsumedBytes;
        if (s32DropBytes > 0)
        {
            DropStream(pstSource->pRBuffer, s32DropBytes);
            pstSource->u32StreamConsumedBytes = u32AlignedPos;
        }

        pstSource->u32PreDecodePts = u32AlignedPts;
        pstSource->u32CurStreamPts = u32AlignedPts;
        pstSource->u32SinkPts = u32AlignedPts;
    }

    //redo wipe invalid pts for avlid the leftbytes with invalid pts in demux.
    pstSource->bDoWipeInvalidPTS = HI_TRUE;
    *pbPCRSyncMode = HI_TRUE;
}

static HI_VOID AdjustStream(SOURCE_S* pstSource)
{
    HI_BOOL bPCRSyncMode = HI_FALSE;
    HI_BOOL bDoresetCodec;
    HI_S32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = HI_INVALID_PTS;
    PTS_SEEK_E enPtsSeekState;

    trace();

    SyncPCRAlignPacket(pstSource, &bPCRSyncMode, &bDoresetCodec);

    HI_WARN_AO("Source(%d) TargetPts:%d CurPts:%d beStarted:%d\n", pstSource->enSourceID, pstSource->u32TargetPts,
               pstSource->u32CurStreamPts, pstSource->bDecoderHadbeenStarted);

    if ((pstSource->u32CurStreamPts > pstSource->u32TargetPts + STREAM_WRAP_PTS_THRESHOLD) &&
        (HI_INVALID_PTS != pstSource->u32CurStreamPts) &&
        (HI_TRUE != pstSource->bFirstTimeStarted))
    {
        enPtsSeekState = PTSQUEUE_Drop_InvertSeek(pstSource->pPtsQueue, pstSource->u32TargetPts, &u32SeekedPos, &u32SeekedPts);
    }
    else
    {
        enPtsSeekState = PTSQUEUE_Seek(pstSource->pPtsQueue, pstSource->u32TargetPts, &u32SeekedPos, &u32SeekedPts);
    }

    PTS_PRINTF("Source:%d u32TargetPts:%d u32SeekedPos:%d u32SeekedPts:%d\n", pstSource->enSourceID, pstSource->u32TargetPts, u32SeekedPos, u32SeekedPts);

    if (HI_TRUE == bDoresetCodec)
    {
        pstSource->bDecoderHadbeenStarted = HI_FALSE;
    }

    if ((PTS_SEEK_NONE == enPtsSeekState) || (PTS_SEEK_BUTT == enPtsSeekState)) //maybe no pts data
    {
        HI_WARN_AO("PTSQUEUE_Seek source(%d) %d no pts data found\n", pstSource->enSourceID, enPtsSeekState);
        return;
    }

    if (PTS_SEEK_ALIGN == enPtsSeekState)
    {
        pstSource->enPkGSeekType = PKG_SEEK_MODE_NONE;
        pstSource->bSeekFrame = HI_FALSE;
    }

    SYNC_PRINTF("Seek Source(%d)(package->%s) TargetPts:%d PtsSeekts:%d PtsSeekPos:%d \n", pstSource->enSourceID,
                aSeekResult[(HI_U32)enPtsSeekState], pstSource->u32TargetPts, u32SeekedPts, u32SeekedPos);

    s32DropBytes = (HI_S32)u32SeekedPos - pstSource->u32StreamConsumedBytes;
    if (s32DropBytes > 0)
    {
        DropStream(pstSource->pRBuffer, s32DropBytes);
        pstSource->u32StreamConsumedBytes = u32SeekedPos;
    }

    if ((PKG_SEEK_MODE_NONE == pstSource->enPkGSeekType) || (0 < s32DropBytes))
    {
        pstSource->bWorking = HI_TRUE;
        pstSource->bFirstTimeStarted = HI_FALSE;
    }

    pstSource->u32PreDecodePts = u32SeekedPts;
    pstSource->u32CurStreamPts = u32SeekedPts;
    pstSource->u32SinkPts = u32SeekedPts;
    SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d Pts:%d\n",
                pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
}

static HI_VOID AdjustFrame(SOURCE_S* pstSource)
{
    HI_S32 s32DropPts = 0;

    trace();

    if (HI_TRUE != pstSource->bSeekFrame)
    {
        return;
    }

    if (PKG_SEEK_MODE_INTRA == pstSource->enPkGSeekType)
    {
        EnableDecode(pstSource, HI_TRUE);

        s32DropPts = (HI_S32)(pstSource->u32TargetPts) - pstSource->u32CurStreamPts;
        SYNC_PRINTF("Source %d Drop pts:%d\n", pstSource->enSourceID, s32DropPts);
        HACodec_DropPts(g_pstSyncCodec, pstSource->enSourceID, s32DropPts);
        pstSource->bDecoderHadbeenStarted = HI_TRUE;
    }
}

static HI_BOOL SyncCheckIsPreModeEnable(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if (((HI_NULL != pstMainSource) && (HI_TRUE == pstMainSource->bSeekFrame)) ||
        ((HI_NULL != pstAssocSource) && (HI_TRUE == pstAssocSource->bSeekFrame)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL SyncCheckIsDropFrameEnable(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;

    trace();

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if (((HI_NULL != pstMainSource) && (HI_TRUE == pstMainSource->bDropFrame)) ||
        ((HI_NULL != pstAssocSource) && (HI_TRUE == pstAssocSource->bDropFrame)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL SyncCheckIsRepeatEnable(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if (((HI_NULL != pstMainSource) && (HI_TRUE == pstMainSource->bRepeatEnable)) ||
        ((HI_NULL != pstAssocSource) && (HI_TRUE == pstAssocSource->bRepeatEnable)))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID SyncApplySyncMode(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];

        if (HI_NULL == pstSource)
        {
            continue;
        }

        //SYNC_PRINTF("sourceID:%d EnableMixer:%d Mixing:%d EnableDecoder:%d Decoding:%d\n",
        //            enSourceID, pstSource->bEnableMixer, pstSource->bMixing,
        //            pstSource->bEnableDecoder, pstSource->bDecoding);

        if ((HI_TRUE == pstSource->bEnableMixer) && (HI_FALSE == pstSource->bMixing))
        {
            HACodec_EnableMixer(g_pstSyncCodec, pstSource->enSourceID, HI_TRUE);
            pstSource->bMixing = HI_TRUE;
        }
        else if ((HI_FALSE == pstSource->bEnableMixer) && (HI_TRUE == pstSource->bMixing))
        {
            HACodec_EnableMixer(g_pstSyncCodec, pstSource->enSourceID, HI_FALSE);
            pstSource->bMixing = HI_FALSE;
        }

        if ((HI_TRUE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bDecoding))
        {
            HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, HI_TRUE);
            pstSource->bDecoding = HI_TRUE;
        }
        else if ((HI_FALSE == pstSource->bEnableDecoder) && (HI_TRUE == pstSource->bDecoding))
        {
            HACodec_EnableDecoder(g_pstSyncCodec, pstSource->enSourceID, HI_FALSE);
            pstSource->bDecoding = HI_FALSE;
        }
    }
}

static HI_VOID SyncDropFrame(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_NULL == pstSource || HI_FALSE == pstSource->bDropFrame)
        {
            continue;
        }

        HACodec_DropFrame(g_pstSyncCodec, pstSource->enSourceID, pstSource->u32DropFrameCnt);

        pstSource->bDropFrame = HI_FALSE;
        pstSource->bDecoderHadbeenStarted = HI_TRUE;
    }
}

static HI_VOID SyncJudgeSyncMode(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_S* pstMainSource;
    SOURCE_S* pstAssocSource;
    HI_BOOL bMainExit;
    HI_BOOL bAssocExit;

    pstMainSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    pstAssocSource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];

    if ((HI_NULL == pstMainSource) || (HI_NULL == pstAssocSource))
    {
        return;
    }

    bMainExit = CheckIsExitDropMode(pstMainSource);
    bAssocExit = CheckIsExitDropMode(pstAssocSource);
    SYNC_PRINTF("MainSource ExitSyncMode[%d] AssocSource ExitSyncMode[%d]\n", bMainExit, bAssocExit);

    if ((HI_TRUE == bMainExit) && (HI_TRUE == bAssocExit))
    {
        if (SOURCE_ID_BUTT == pstSourceManager->enPTSReportSource)
        {
            SYNC_PRINTF("Set MainSource to PTSReportSource Default\n");
            pstSourceManager->enPTSReportSource = SOURCE_ID_MAIN;
        }
    }
    else if ((HI_TRUE == bMainExit) && (HI_FALSE == bAssocExit))
    {
        pstAssocSource->u32SeekFrameTimeout++;
        if (pstAssocSource->u32SeekFrameTimeout > SEEK_FRAME_TIMEOUT_MAX_CNT)
        {
            SYNC_PRINTF("Assoc Source SeetFrame Timeout[%d], Force to Exit\n", pstAssocSource->u32SeekFrameTimeout);
            ExitDropMode(pstAssocSource);   //Assoc seeFrame timeout being forced to exit.
            SYNC_PRINTF("Set MainSource to PTSReportSource\n");
            pstSourceManager->enPTSReportSource = SOURCE_ID_MAIN;
        }
    }
    else if ((HI_FALSE == bMainExit) && (HI_TRUE == bAssocExit))
    {
        pstMainSource->u32SeekFrameTimeout++;
        if (pstMainSource->u32SeekFrameTimeout > SEEK_FRAME_TIMEOUT_MAX_CNT)
        {
            SYNC_PRINTF("Main Source SeetFrame Timeout[%d], Force to Exit\n", pstAssocSource->u32SeekFrameTimeout);
            ExitDropMode(pstMainSource);   //Main seeFrame timeout being forced to exit.
            SYNC_PRINTF("Set AssocSource to PTSReportSource\n");
            pstSourceManager->enPTSReportSource = SOURCE_ID_ASSOC;
        }
    }
}

static HI_VOID SyncPreModeAdjustStream(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_FALSE == CheckIsPreSyncModeValid(pstSource))
        {
            continue;
        }

        SYNC_PRINTF("Source[%d] DropTargetPts:%d CurPts:%d\n", enSourceID, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

        if (HI_TRUE == CheckIsTargetRequirementMeeted(pstSource))
        {
            ExitDropMode(pstSource);
            continue;
        }

        if (HI_TRUE == CheckIsAdjustStreamNeeded(pstSource))
        {
            /*if (HI_FALSE == CheckIsDecoderHadbeenStart(pstSource))
            {
                AdjustStream(pstSource);
            }
            else
            {
                //if decoder started, only used drop frame to seek target pts
                ForceAdjustFrameMode(pstSource);
            }*/
            AdjustStream(pstSource);
        }

        AdjustFrame(pstSource); //disable
    }

    SyncJudgeSyncMode(pstSourceManager);
}

static HI_VOID SyncDropInValidPtsStream(SOURCE_S* pstSource, HI_BOOL* pbDropComplete)
{
    HI_S32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = HI_INVALID_PTS;
    PTS_SEEK_E enPtsSeekState;

    trace();

    *pbDropComplete = HI_FALSE;

    enPtsSeekState = PTSQUEUE_Seek(pstSource->pPtsQueue, 0, &u32SeekedPos, &u32SeekedPts);
    if ((PTS_SEEK_NONE == enPtsSeekState) || (PTS_SEEK_BUTT == enPtsSeekState)) //maybe no pts data
    {
        HI_INFO_AO("PTSQUEUE_Seek source(%d) %d no pts data found\n", pstSource->enSourceID, enPtsSeekState);
        return;
    }

    if (PTS_SEEK_ALIGN == enPtsSeekState) //else PTS_SEEK_PACKAGE
    {
        HI_WARN_AO("PTSQUEUE_Seek source(%d) Valid pts(%d) found\n", pstSource->enSourceID, u32SeekedPts);
        *pbDropComplete = HI_TRUE;
    }

    s32DropBytes = (HI_S32)u32SeekedPos - pstSource->u32StreamConsumedBytes;
    if (s32DropBytes > 0)
    {
        DropStream(pstSource->pRBuffer, s32DropBytes);
        pstSource->u32StreamConsumedBytes = u32SeekedPos;
    }
    else
    {
        HI_WARN_AO("Err Source:%d  u32SeekedPos :%d\n", pstSource->enSourceID, u32SeekedPos);
    }

    pstSource->u32PreDecodePts = u32SeekedPts;
    pstSource->u32CurStreamPts = u32SeekedPts;

    SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d StreamPts:%d\n",
                pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
}

static HI_VOID SyncWipeOutInvalidPts(SOURCE_MANAGER_S* pstSourceManager)
{
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;

    trace();

    for (enSourceID = SOURCE_ID_MAIN; enSourceID <= SOURCE_ID_ASSOC; enSourceID++)
    {
        HI_BOOL bDropComplete;
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_NULL == pstSource)
        {
            continue;
        }

        if (HI_FALSE == pstSource->bDoWipeInvalidPTS)
        {
            continue;
        }

        SyncDropInValidPtsStream(pstSource, &bDropComplete);
        if (HI_TRUE == bDropComplete)
        {
            SYNC_PRINTF("Source:%d DoWipeInvalidPTS complete NewStreamPts:%d\n", enSourceID, pstSource->u32CurStreamPts);
            pstSource->bDoWipeInvalidPTS = HI_FALSE;
        }
    }
}

HI_VOID Sync_SetCodecHandle(ENGINE_CODEC_S* pstCodec)
{
    g_pstSyncCodec = pstCodec;
}

HI_BOOL Sync_CheckIsSourceNeedDecode(SOURCE_S* pstSource)
{
    if (((HI_TRUE == pstSource->bSeekFrame) && (PKG_SEEK_MODE_INTER == pstSource->enPkGSeekType)) ||
        (HI_TRUE == pstSource->bDoWipeInvalidPTS))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_VOID Sync_Prepare(SOURCE_MANAGER_S* pstSourceManager)
{
    SyncApplySyncMode(pstSourceManager);

    if (HI_TRUE == SyncCheckIsRepeatEnable(pstSourceManager))
    {
        SYNC_PRINTF("Source Repeat enable\n");
        return;
    }

    if (HI_TRUE == SyncCheckIsPreModeEnable(pstSourceManager))
    {
        SyncPreModeAdjustStream(pstSourceManager);
        return;
    }

    //if PreSyncMode exit, DO Wipe out invalid pts for dualdecoder.
    SyncWipeOutInvalidPts(pstSourceManager);

    if (HI_TRUE == SyncCheckIsDropFrameEnable(pstSourceManager))
    {
        SyncDropFrame(pstSourceManager);
    }
}

HI_S32 Sync_DropStream(SOURCE_S* pstSource, HI_U32 u32SeekPts)
{
    HI_S32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = 0;
    PTS_SEEK_E enPtsSeekState;

    trace();

    if ((HI_NULL == pstSource) ||
        !((HI_FALSE == pstSource->bEnableDecoder) && (HI_FALSE == pstSource->bEnableMixer)))   //syncmode pause
    {
        return HI_FAILURE;
    }

    if ((pstSource->u32CurStreamPts >= u32SeekPts) && (HI_INVALID_PTS != pstSource->u32CurStreamPts))
    {
        HI_WARN_AO("Source[%d] SeekPts:%d  CurPts:%d EXIT DropStream Mode\n", pstSource->enSourceID, u32SeekPts, pstSource->u32CurStreamPts);
        pstSource->bWorking = HI_TRUE;
        return HI_SUCCESS;
    }

    HI_WARN_AO("Source[%d] enState:%d DropTargetPts:%d  CurPts:%d\n", pstSource->enSourceID, pstSource->enState, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

    enPtsSeekState = PTSQUEUE_Drop_Seek(pstSource->pPtsQueue, u32SeekPts, &u32SeekedPos, &u32SeekedPts);
    if (PTS_SEEK_NONE == enPtsSeekState) //maybe no pts data
    {
        HI_WARN_AO("PTSQUEUE_Drop_Seek source(%d) no pts data found\n", pstSource->enSourceID);
        pstSource->bWorking = HI_TRUE;
        return HI_SUCCESS;
    }

    s32DropBytes = (HI_S32)u32SeekedPos - (pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes);

    HI_WARN_AO("PtsSeekState:%d TargetPts:%d PtsSeekPts:%d PtsSeekPos:%d u32SeekPts:%d s32DropBytes=%d ConsumeByte:%d LeftByte:%d\n",
        enPtsSeekState, pstSource->u32TargetPts, u32SeekedPts, u32SeekedPos, u32SeekPts, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes);

    if (s32DropBytes >= 0)
    {
        DropStream(pstSource->pRBuffer, (HI_U32)s32DropBytes);
        pstSource->u32StreamConsumedBytes += (HI_U32)s32DropBytes;
        pstSource->u32CurStreamPts = u32SeekedPts;
        pstSource->u32PreDecodePts = u32SeekedPts;
        pstSource->bWorking = HI_TRUE;
        SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d Pts:%d\n", pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
    }

    return HI_SUCCESS;
}

HI_S32 Sync_PolicyDropStream(SOURCE_S* pstSource, HI_U32 u32SeekPts, HI_BOOL bPtsInvert)
{
    HI_S32 s32DropBytes;
    HI_U32 u32SeekedPos = 0;
    HI_U32 u32SeekedPts = 0;
    PTS_SEEK_E enPtsSeekState;

    trace();

    HI_WARN_AO("Source[%d] enState:%d DropTargetPts:%d  CurPts:%d\n", pstSource->enSourceID, pstSource->enState, pstSource->u32TargetPts, pstSource->u32CurStreamPts);

    if (HI_TRUE == bPtsInvert)
    {
        enPtsSeekState = PTSQUEUE_Drop_InvertSeek(pstSource->pPtsQueue, u32SeekPts, &u32SeekedPos, &u32SeekedPts);
    }
    else
    {
        enPtsSeekState = PTSQUEUE_Drop_PolicySeek(pstSource->pPtsQueue, u32SeekPts, &u32SeekedPos, &u32SeekedPts);
    }

    if (PTS_SEEK_NONE == enPtsSeekState) //maybe no pts data
    {
        HI_WARN_AO("PTSQUEUE_Drop_Seek source(%d) no pts data found\n", pstSource->enSourceID);
        return HI_SUCCESS;
    }

    s32DropBytes = (HI_S32)u32SeekedPos - (pstSource->u32StreamConsumedBytes - pstSource->u32DecodeLeftBytes);

    HI_WARN_AO("PtsSeekState:%d TargetPts:%d PtsSeekPts:%d PtsSeekPos:%d u32SeekPts:%d s32DropBytes=%d ConsumeByte:%d LeftByte:%d\n",
        enPtsSeekState, pstSource->u32TargetPts, u32SeekedPts, u32SeekedPos, u32SeekPts, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32DecodeLeftBytes);

    if (s32DropBytes > 0)
    {
        DropStream(pstSource->pRBuffer, (HI_U32)s32DropBytes);
        pstSource->u32StreamConsumedBytes += (HI_U32)s32DropBytes;
        pstSource->u32CurStreamPts = u32SeekedPts;
        pstSource->u32PreDecodePts = u32SeekedPts;
        pstSource->bWorking = HI_TRUE;
        SYNC_PRINTF("Source:%d Drop InBufSize:%d New Pos:%d Pts:%d\n", pstSource->enSourceID, s32DropBytes, pstSource->u32StreamConsumedBytes, pstSource->u32CurStreamPts);
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
