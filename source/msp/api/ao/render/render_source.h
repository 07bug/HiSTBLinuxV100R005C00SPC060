/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_source.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/18
  Description  :
  History       :
  1.Date        : 2016/05/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_SOURCE_H__
#define  __RENDER_SOURCE_H__

#include "render_common.h"
#include "hi_mpi_ao.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32  Source_GetSourceIDFromTrackID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID);
HI_BOOL Source_Client_CheckTrack(HI_HANDLE hTrack);
HI_BOOL Source_Client_CheckIsMediaTrack(HI_HANDLE hTrack);
HI_BOOL Source_Client_CheckIsMediaTrackCreated(HI_HANDLE hTrack);
HI_S32  Source_Client_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack);
HI_S32  Source_Client_DeApllyID(HI_HANDLE hTrack);
HI_S32  Source_GetRenderTrackID(HI_HANDLE hTrack, HI_HANDLE* phRenderTrack);
HI_S32  Source_Client_Create(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack);
HI_S32  Source_Client_DestroyTrack(HI_HANDLE hTrack);
HI_S32  Source_Client_SetTrackConfig(HI_HANDLE hTrack, const HI_VOID* pstConfig);
HI_S32  Source_Client_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pstConfig);
HI_S32  Source_Client_SetTrackAttr(HI_HANDLE hTrack, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr);
HI_S32  Source_Client_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr);
HI_S32  Source_Client_SetCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd);
HI_S32  Source_Client_GetCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd);
HI_S32  Source_Client_SendTrackData(HI_HANDLE hTrack, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame);
HI_S32  Source_Client_SendStream(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs, HI_VOID* pPesData);
HI_S32  Source_Client_GetBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream);
HI_S32  Source_Client_PutBuffer(HI_HANDLE hTrack, HI_MPI_AO_BUFID_E enBufId, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs);
HI_S32  Source_Client_StartTrack(HI_HANDLE hTrack);
HI_S32  Source_Client_StopTrack(HI_HANDLE hTrack);
HI_S32  Source_Client_PauseTrack(HI_HANDLE hTrack);
HI_S32  Source_Client_FlushTrack(HI_HANDLE hTrack);
HI_S32  Source_Client_GetSourceID(HI_HANDLE hTrack, SOURCE_ID_E* penSourceID);
HI_S32  Source_Client_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts);
HI_S32  Source_Client_SetRepeatTargetPts(HI_HANDLE hTrack);
HI_S32  Source_Client_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt);
HI_S32  Source_Client_DropTrackStream(HI_HANDLE hTrack, HI_U32 u32SeekPts);
HI_S32  Source_Client_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode);
HI_S32  Source_Client_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs);

HI_S32  Source_Client_CheckCreateSlaveTrack(HI_HANDLE hTrack, HI_HANDLE* phSlaveTrack);
HI_S32  Source_Client_DestroySlaveTrack(HI_HANDLE hTrack, HI_HANDLE hSlaveTrack);
HI_S32  Source_Client_GetSlaveTrackAttachedInfo(HI_HANDLE hTrack, HI_BOOL* pbAttached, HI_HANDLE* phSlaveTrack);

HI_S32  Source_Client_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag);
HI_S32  Source_Client_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState);
HI_S32  Source_Client_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus);
HI_S32  Source_Client_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstStreamInfo);
HI_S32  Source_Client_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32PtsMs, HI_U32* pu32OrgPtsMs);
HI_S32  Source_Client_GetCapability(HI_U32* pu32Capability);
HI_S32  Source_Client_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent);
HI_S32  Source_Client_GetRenderAllInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo);
#ifdef DPT
HI_S32  Source_Client_SetTrackMute(HI_HANDLE hTrack, HI_BOOL bMute);
HI_S32  Source_Client_GetTrackMute(HI_HANDLE hTrack, HI_BOOL* pbMute);
HI_S32  Source_Client_SetTrackPrescale(HI_HANDLE hTrack, const HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain);
HI_S32  Source_Client_GetTrackPrescale(HI_HANDLE hTrack, HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain);
HI_S32  Source_Client_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource);
#endif

HI_BOOL Source_Server_CheckIsMediaTrack(HI_HANDLE hTrack);
HI_BOOL Source_Server_CheckIsMediaTrackCreated(HI_HANDLE hTrack);
HI_BOOL Source_Server_CheckIsMediaTrackDuplicate(HI_HANDLE hTrack);
HI_MPI_RENDER_SOURCE_TYPE_E Source_Server_GetSourceTypeforTrackType(HI_UNF_SND_TRACK_TYPE_E enType);
HI_S32  Source_Server_DeallocID(HI_HANDLE hTrack);

HI_S32  Source_Server_Init(RENDER_MANAGER_S* pstRenderManager);
HI_S32  Source_Server_Deinit(HI_VOID);
HI_S32  Source_Server_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack, HI_HANDLE* phExtTrack);
HI_S32  Source_Server_DeApllyID(HI_HANDLE hTrack, HI_HANDLE hExtTrack);
HI_S32  Source_Server_DestroyTrackWithID(HI_HANDLE hTrack);
HI_S32  Source_Server_Create(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack);
HI_S32  Source_Server_DestroyTrack(HI_HANDLE hTrack);
HI_S32  Source_Server_GetIsbAddr(HI_UNF_SND_E enSound, HI_MPI_AO_SB_ATTR_S* pstIsbAttr);
HI_S32  Source_Server_SetTrackConfig(HI_HANDLE hTrack, HI_U32 u32cfgType, const HI_VOID* pstConfig);
HI_S32  Source_Server_GetTrackConfig(HI_HANDLE hTrack, HI_U32 u32cfgType, HI_VOID* pstConfig);
HI_S32  Source_Server_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr);
HI_S32  Source_Server_StartTrack(HI_HANDLE hTrack);
HI_S32  Source_Server_StopTrack(HI_HANDLE hTrack);
HI_S32  Source_Server_PauseTrack(HI_HANDLE hTrack);
HI_S32  Source_Server_FlushTrack(HI_HANDLE hTrack);
HI_S32  Source_Server_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts);
HI_S32  Source_Server_SetRepeatTargetPts(HI_HANDLE hTrack);
HI_S32  Source_Server_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt);
HI_S32  Source_Server_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode);
HI_S32  Source_Server_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs);
HI_S32  Source_Server_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag);
HI_S32  Source_Server_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState);
HI_S32  Source_Server_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus);
HI_S32  Source_Server_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstStreamInfo);
HI_S32  Source_Server_GetNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent);
HI_VOID Source_Server_DestroyMediaTrack(HI_VOID);
#ifdef DPT
HI_S32  Source_Server_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
