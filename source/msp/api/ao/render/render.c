/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render.c
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
#include "hi_mpi_ao.h"

#include "render.h"
#include "render_engine.h"
#include "render_source.h"
#include "render_proc.h"
#include "render_common.h"
#include "render_buffer.h"

#include "ipc_server.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define RENDERNAME        "DolbyMS12Decoder"
#define RENDERCODECID     (0x20351012)
#define RENDER_BUFEMPTY_THRESHOLD_MS (42)  //aip 5ms + engine 5ms + ms12 32ms

static RENDER_MANAGER_S g_stRenderManager;

#define CHECK_FORMAT_AND_RETURN_VALUE(format, capability, psupport) \
    do { \
        if(((FORMAT_MS12_DDP == format) && (0 != (capability & MS12_SUPPORT_FORMAT_DDP))) || \
           ((FORMAT_MS12_AAC == format) && (0 != (capability & MS12_SUPPORT_FORMAT_AAC))) || \
           ((FORMAT_MS12_AC4 == format) && (0 != (capability & FORMAT_MS12_AC4)))) \
        { \
            *psupport = HI_TRUE; \
        } \
        else \
        { \
            *psupport = HI_FALSE; \
        } \
    } while(0)


HI_S32 RENDERGetHaSzNameInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_SZNAMEINFO_S* pstAdecName)
{
    HI_LOG_CHECK_PARAM(HI_NULL_PTR == pstAdecName);

    strncpy(pstAdecName->szHaCodecName, RENDERNAME, sizeof(pstAdecName->szHaCodecName));
    return HI_SUCCESS;
}

static HI_S32 RENDERGetIsSupport(HI_BOOL* pbSupport)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_RENDER_ATTR_S stRenderParam;

    memset(&stRenderParam, 0, sizeof(AO_RENDER_ATTR_S));

    *pbSupport = HI_FALSE;

    s32Ret = HI_MPI_AO_SND_GetRenderParam(HI_UNF_SND_0, &stRenderParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("Call HI_MPI_AO_SND_GetRenderParam failed(0x%x)\n", s32Ret);
        return HI_SUCCESS;
    }

    *pbSupport = stRenderParam.bSupport;

    return HI_SUCCESS;
}

static HI_S32 RENDERSaveAttrToDRV(HI_UNF_SND_RENDER_ATTR_S* pstAttr, HI_BOOL bSave)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_RENDER_ATTR_S stRenderAttr = {0};

    stRenderAttr.u32Capability = 0;
    stRenderAttr.bSupport = HI_FALSE;
    memset(stRenderAttr.aCommPath, 0, AO_COMM_PATH_MAX_LENGTH);

    if (HI_TRUE == bSave)
    {
        HA_MS12_GET_CAPABILITY_S stCapability;
        stCapability.enCmd = HA_CODEC_MS12_GET_CAPABILITY_CMD;
        stCapability.u32Capability = 0;

        s32Ret = Engine_GetCmd(&stCapability);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Engine_GetCmd, s32Ret);
            return s32Ret;
        }

        if (HI_NULL == pstAttr || HI_NULL == pstAttr->pCommPath)
        {
            HI_ERR_PrintInfo("RenderAttr is NULL PTR");
            return HI_ERR_AO_NULL_PTR;
        }

        if (strlen(pstAttr->pCommPath) > AO_COMM_PATH_MAX_LENGTH)
        {
            HI_ERR_AO("pCommPath length(%d) is large than %d", strlen(pstAttr->pCommPath), AO_COMM_PATH_MAX_LENGTH);
            return HI_ERR_AO_INVALID_PARA;
        }

        stRenderAttr.u32Capability = stCapability.u32Capability;
        stRenderAttr.bSupport = HI_TRUE;
        memcpy(stRenderAttr.aCommPath, pstAttr->pCommPath, AO_COMM_PATH_MAX_LENGTH);
    }

    s32Ret = HI_MPI_AO_SND_SetRenderParam(HI_UNF_SND_0, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_SetRenderParam, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

#ifdef DPT
static HI_S32 RENDERResetTrackConfig(HI_HANDLE hTrack)
{
    HI_S32 s32Ret;
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;

    s32Ret = Source_Client_SetTrackMute(hTrack, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackMute, s32Ret);
        return s32Ret;
    }

    stPreciGain.s32IntegerGain = 0;
    stPreciGain.s32DecimalGain = 0;
    s32Ret = Source_Client_SetTrackPrescale(hTrack, &stPreciGain);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackPrescale, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}
#endif

HI_S32 RENDER_CheckIsRenderSupport(HI_BOOL* pbSupport)
{
    return RENDERGetIsSupport(pbSupport);
}

HI_BOOL RENDER_CheckIsTrackTypeSupport(const HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    if ((HI_UNF_SND_TRACK_TYPE_MASTER == pstAttr->enTrackType)      ||
        (HI_UNF_SND_TRACK_TYPE_SLAVE  == pstAttr->enTrackType)      ||
        (HI_UNF_SND_TRACK_TYPE_OTTSOUND == pstAttr->enTrackType)    ||
        (HI_UNF_SND_TRACK_TYPE_SYSTEMAUDIO == pstAttr->enTrackType) ||
        (HI_UNF_SND_TRACK_TYPE_APPAUDIO == pstAttr->enTrackType))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_S32 RENDER_CheckIsCodecSupport(const HA_CODEC_ID_E enCodecId, HI_BOOL* pbSupport)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_RENDER_ATTR_S stRenderAttr;

    *pbSupport = HI_FALSE;

    s32Ret = HI_MPI_AO_SND_GetRenderParam(HI_UNF_SND_0, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_AO("Call HI_MPI_AO_SND_GetRenderParam failed(0x%x)\n", s32Ret);
        return HI_SUCCESS;
    }

    if (((HA_AUDIO_ID_MP2 == enCodecId || HA_AUDIO_ID_MP3 == enCodecId) && (0 != (stRenderAttr.u32Capability & MS12_SUPPORT_FORMAT_MP3)))      ||
         ((HA_AUDIO_ID_AAC == enCodecId || HA_AUDIO_ID_MS12_AAC == enCodecId) && (0 != (stRenderAttr.u32Capability & MS12_SUPPORT_FORMAT_AAC))) ||
         ((HA_AUDIO_ID_DOLBY_PLUS == enCodecId || HA_AUDIO_ID_MS12_DDP == enCodecId) && (0 != (stRenderAttr.u32Capability & MS12_SUPPORT_FORMAT_DDP)))
         )
    {
        *pbSupport = HI_TRUE;
    }

    HI_WARN_AO("RenderSupport:0x%x Capability:0x%x CodecID:0x%x\n", stRenderAttr.bSupport, stRenderAttr.u32Capability, enCodecId);

    return HI_SUCCESS;
}

HI_BOOL RENDER_CheckTrack(HI_HANDLE hTrack)
{
    return Source_Client_CheckTrack(hTrack);
}

HI_BOOL RENDER_CheckIsMediaTrack(HI_HANDLE hTrack)
{
    return Source_Client_CheckIsMediaTrack(hTrack);
}

HI_S32 RENDER_GetRenderTrackID(HI_HANDLE hTrack, HI_HANDLE* phRenderTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    s32Ret = Source_GetRenderTrackID(hTrack, phRenderTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_GetRenderTrackID, s32Ret);
        return s32Ret;
    }

    HI_INFO_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_CreateTrack(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL_PTR == pstTrackAttr);
    HI_LOG_CHECK_PARAM(HI_NULL_PTR == phTrack);

    HI_WARN_PrintH32(pstTrackAttr->enTrackType);

    if ((HI_UNF_SND_TRACK_TYPE_MASTER == pstTrackAttr->enTrackType) ||
        (HI_UNF_SND_TRACK_TYPE_SLAVE  == pstTrackAttr->enTrackType))
    {
        s32Ret = Source_Client_ApllyID(pstTrackAttr, phTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Source_Client_ApllyID, s32Ret);
            return s32Ret;
        }
    }
    else
    {
        s32Ret = Source_Client_Create(enSound, pstTrackAttr, phTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Source_Client_Create, s32Ret);
            return s32Ret;
        }
    }
#ifdef DPT
    s32Ret = RENDERResetTrackConfig(*phTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDERResetTrackConfig, s32Ret);
        return s32Ret;
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_DestroyTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE == Source_Client_CheckIsMediaTrack(hTrack))
    {
        s32Ret = Source_Client_DeApllyID(hTrack);
        if (HI_SUCCESS != s32Ret)
        {
            HI_LOG_PrintFuncErr(Source_Client_DeApllyID, s32Ret);
        }
        return s32Ret;
    }

    s32Ret = Source_Client_DestroyTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_DestroyTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetTrackConfig(hTrack, pConfig);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackConfig, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pConfig)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_GetTrackConfig(hTrack, pConfig);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetTrackConfig, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_GetTrackAttr(hTrack, pstAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetTrackAttr, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetTrackAttr(hTrack, pstRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackAttr, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetTrackCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetCmd(hTrack, pstRenderCmd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetCmd, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    s32Ret = Source_Client_SendTrackData(hTrack, pstAOFrame);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    HI_INFO_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs, HI_VOID* pPesData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_SendStream(hTrack, enBufId, pstStream, u32PtsMs, pPesData);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    HI_INFO_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_GetBuffer(hTrack, enBufId, u32RequestSize, pstStream);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    HI_INFO_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_PutBuffer(hTrack, enBufId, pstStream, u32PtsMs);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    HI_INFO_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_StartTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_StartTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_StartTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_StopTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_StopTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_StopTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_PauseTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_PauseTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_PauseTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_FlushTrack(HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_FlushTrack(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_FlushTrack, s32Ret);
        HI_ERR_PrintH32(hTrack);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32  RENDER_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32PtsMs, HI_U32* pu32OrgPtsMs)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_INFO_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_GetTrackPts(hTrack, pu32PtsMs, pu32OrgPtsMs);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_AO_NOT_INIT != s32Ret))
    {
        HI_LOG_PrintFuncErr(Source_Client_GetTrackPts, s32Ret);
    }

    HI_INFO_FuncExit();
    return s32Ret;
}

HI_S32 RENDER_DropTrackStream(const HI_HANDLE hTrack, HI_U32 u32SeekPts)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_DropTrackStream(hTrack, u32SeekPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_DropTrackStream, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetTargetPts(const HI_HANDLE hTrack, HI_U32 u32TargetPts)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_SetTargetPts(hTrack, u32TargetPts);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTargetPts, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetRepeatTargetPts(const HI_HANDLE hTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_SetRepeatTargetPts(hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetRepeatTargetPts, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_DropFrame(const HI_HANDLE hTrack, HI_U32 u32FrameCnt)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_DropFrame(hTrack, u32FrameCnt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_DropFrame, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetSyncMode(const HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    if (HI_TRUE != Source_Client_CheckIsMediaTrack(hTrack))
    {
        HI_ERR_PrintInfo("Invalid Track parameter! Only support MediaTrack.");
        HI_ERR_PrintH32(hTrack);
        HI_LOG_PrintErrCode(HI_ERR_AO_NOTSUPPORT);
        return HI_ERR_AO_NOTSUPPORT;
    }

    s32Ret = Source_Client_SetSyncMode(hTrack, enSyncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetSyncMode, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetEosFlag(hTrack, bEosFlag);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetEosFlag, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_GetInfo(const HI_HANDLE hTrack, HI_MPI_TRACK_INFO_E enInfoCmd, HI_VOID* pTrackInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    HI_LOG_CHECK_PARAM(HI_NULL_PTR == pTrackInfo);

    switch (enInfoCmd)
    {
        case TRACK_INFO_WORKSTATE:
            break;
        case TRACK_INFO_INBUFSIZE:
            break;
        case TRACK_INFO_OUTBUFNUM:
            break;
        case TRACK_INFO_ALLINFO:
            return Source_Client_GetRenderAllInfo(hTrack, (HI_MPI_AO_RENDER_ALLINFO_S*)pTrackInfo);
        case TRACK_INFO_EOSSTATEFLAG:
            return Source_Client_GetEosState(hTrack, (HI_BOOL*)pTrackInfo);
        case TRACK_INFO_STREAM:
            return Source_Client_GetStreamInfo(hTrack, (ADEC_STREAMINFO_S*)pTrackInfo);
        case TRACK_INFO_BUFFERSTATUS:
            return Source_Client_GetBufferStatus(hTrack, (ADEC_BUFSTATUS_S*)pTrackInfo);
        case TRACK_INFO_HASZNAME:
            return RENDERGetHaSzNameInfo(hTrack, (HI_MPI_AO_RENDER_SZNAMEINFO_S*)pTrackInfo);
        default:
            HI_ERR_AO("Unknown info cmd(0x%x)\n", enInfoCmd);
            return HI_ERR_AO_INVALID_PARA;
    }

    return s32Ret;
}

HI_S32 RENDER_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs)
{
    HI_S32 s32Ret;

    s32Ret = Source_Client_GetDelayMs(hTrack, pu32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetDelayMs, s32Ret);
        HI_ERR_PrintH32(hTrack);
    }

    return s32Ret;
}

HI_S32 RENDER_IsBufEmpty(const HI_HANDLE hTrack, HI_BOOL* pbEmpty)
{
    HI_S32 s32Ret;
    HI_U32 u32DelayMs = 0;

    *pbEmpty = HI_FALSE;

    s32Ret = Source_Client_GetDelayMs(hTrack, &u32DelayMs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncWarn(Source_Client_GetDelayMs, s32Ret);
        HI_WARN_PrintH32(hTrack);
        return s32Ret;
    }

    if (u32DelayMs <= RENDER_BUFEMPTY_THRESHOLD_MS)
    {
        *pbEmpty = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32 RENDER_CheckCreateSlaveTrack(HI_HANDLE hTrack, HI_HANDLE* phSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_CheckCreateSlaveTrack(hTrack, phSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_CheckCreateSlaveTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_DestroySlaveTrack(HI_HANDLE hTrack, HI_HANDLE hSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_DestroySlaveTrack(hTrack, hSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_DestroySlaveTrack, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_GetSlaveTrackAttachedInfo(HI_HANDLE hTrack, HI_BOOL* pbAttached, HI_HANDLE* phSlaveTrack)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_GetSlaveTrackAttachedInfo(hTrack, pbAttached, phSlaveTrack);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetSlaveTrackAttachedInfo, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 RENDER_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent)
{
    return Source_Client_CheckNewEvent(hTrack, pstNewEvent);
}

HI_S32 RENDER_Server_Create(HI_UNF_SND_E enSound, HI_UNF_SND_RENDER_ATTR_S* pstAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AO_RENDER_ATTR_S stRenderAttr;

    HI_LOG_FuncEnter();

    //inquiry from drv whether RenderServer had been create. HERE
    //LOCK HERE
    stRenderAttr.bSupport = HI_FALSE;
    s32Ret = HI_MPI_AO_SND_GetRenderParam(enSound, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_GetRenderParam, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE == stRenderAttr.bSupport)
    {
        HI_ERR_PrintInfo("RenderEngine has been created");
        HI_LOG_PrintErrCode(HI_ERR_AO_DEVICE_BUSY);
        return HI_ERR_AO_DEVICE_BUSY;
    }

    s32Ret = Source_Server_Init(&g_stRenderManager);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Server_Init, s32Ret);
        return s32Ret;
    }

    s32Ret = Engine_Init(&g_stRenderManager);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Engine_Init, s32Ret);
        goto ERR_ENGINE_INIT;
    }

    s32Ret = Engine_Create();
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Engine_Create, s32Ret);
        goto ERR_ENGINE_CREATE;
    }

    s32Ret = Proc_Init(&g_stRenderManager);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Proc_Init, s32Ret);
        goto ERR_PROC_CREATE;
    }

    s32Ret = IPC_Service_Create(pstAttr->pCommPath);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(IPC_Service_Create, s32Ret);
        goto ERR_IPCSERVICE_CREATE;
    }

    s32Ret = RENDERSaveAttrToDRV(pstAttr, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(RENDERSaveAttrToDRV, s32Ret);
        goto ERR_RECORDCOMMONATTR;
    }

    HI_INFO_PrintInfo("Render Server All Created Successfully");
    HI_LOG_FuncExit();

    return HI_SUCCESS;

ERR_RECORDCOMMONATTR:
    IPC_Service_Destroy();

ERR_IPCSERVICE_CREATE:
    Proc_DeInit(&g_stRenderManager);

ERR_PROC_CREATE:
    Engine_Destroy();

ERR_ENGINE_CREATE:
    Engine_Deinit();

ERR_ENGINE_INIT:
    Source_Server_Deinit();

    return s32Ret;
}

HI_S32 RENDER_Server_Destroy(HI_UNF_SND_E enSound)
{
    HI_S32 s32Ret;
    AO_RENDER_ATTR_S stRenderAttr;
    HI_LOG_FuncEnter();

    stRenderAttr.bSupport = HI_FALSE;

    s32Ret = HI_MPI_AO_SND_GetRenderParam(enSound, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(HI_MPI_AO_SND_GetRenderParam, s32Ret);
        return s32Ret;
    }

    if (HI_TRUE != stRenderAttr.bSupport)
    {
        HI_ERR_PrintInfo("RenderEngine has not been created");
        return HI_ERR_AO_DEV_NOT_OPEN;
    }

    RENDERSaveAttrToDRV(HI_NULL, HI_FALSE);
    IPC_Service_Destroy();
    Source_Server_DestroyMediaTrack();
    Source_Server_Deinit();
    Engine_Destroy();
    Engine_Deinit();
    Proc_DeInit(&g_stRenderManager);

    HI_LOG_FuncExit();

    return HI_SUCCESS;
}
#ifdef DPT
HI_S32  RENDER_SetTrackMute(HI_HANDLE hTrack, HI_BOOL bMute)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetTrackMute(hTrack, bMute);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackMute, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32  RENDER_GetTrackMute(HI_HANDLE hTrack, HI_BOOL* pbMute)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_GetTrackMute(hTrack, pbMute);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetTrackMute, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32  RENDER_SetTrackPrescale(HI_HANDLE hTrack, const HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetTrackPrescale(hTrack, pstPreciGain);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackPrescale, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32  RENDER_GetTrackPrescale(HI_HANDLE hTrack, HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_GetTrackPrescale(hTrack, pstPreciGain);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_GetTrackPrescale, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32  RENDER_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_LOG_FuncEnter();

    s32Ret = Source_Client_SetTrackSource(hTrack, enSource);
    if (HI_SUCCESS != s32Ret)
    {
        HI_LOG_PrintFuncErr(Source_Client_SetTrackSource, s32Ret);
        return s32Ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
