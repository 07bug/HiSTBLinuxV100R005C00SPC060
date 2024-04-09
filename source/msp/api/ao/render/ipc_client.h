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
#ifndef  __IPC_CLIENT_H__
#define  __IPC_CLIENT_H__

#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAINASSOCAUDIOPAYLOADCNT   (3)  //main & assoc & extmain create together

HI_BOOL IPC_Client_CheckISMediaTrackCreate(HI_HANDLE hTrack);
HI_S32  IPC_Client_ApllyID(const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* pMAINhTrack, HI_HANDLE* pExtMainhTrack);
HI_S32  IPC_Client_DeApllyID(HI_HANDLE hTrack, HI_HANDLE hExtTrack);
HI_S32  IPC_Client_CreateTrackWithID(HI_HANDLE hTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr);
HI_S32  IPC_Client_DestroyTrackWithID(HI_HANDLE hTrack);
HI_S32  IPC_Client_CreateTrack(HI_UNF_SND_E enSound, const HI_UNF_AUDIOTRACK_ATTR_S* pstTrackAttr, HI_HANDLE* phTrack, HI_MPI_AO_SB_ATTR_S* pstAoIsbAttr);
HI_S32  IPC_Client_DestroyTrack(HI_HANDLE hTrack);
HI_S32  IPC_Client_SetTrackConfig(HI_HANDLE hTrack, const HI_VOID* pstConfig);
HI_S32  IPC_Client_GetTrackConfig(HI_HANDLE hTrack, HI_VOID* pstConfig);
HI_S32  IPC_Client_ActiveTrack(HI_HANDLE hTrack, HI_BOOL bActived);
HI_S32  IPC_Client_SetTrackCmd(HI_HANDLE hTrack, HI_VOID* pstRenderCmd);
HI_S32  IPC_Client_SetTrackAttr(const SOURCE_ID_E enHalID, const HI_UNF_ACODEC_ATTR_S* pstRenderAttr);
HI_S32  IPC_Client_GetTrackAttr(HI_HANDLE hTrack, HI_UNF_AUDIOTRACK_ATTR_S* pstAttr);
HI_S32  IPC_Client_StartTrack(HI_HANDLE hTrack);
HI_S32  IPC_Client_StopTrack(HI_HANDLE hTrack);
HI_S32  IPC_Client_PauseTrack(HI_HANDLE hTrack);
HI_S32  IPC_Client_FlushTrack(HI_HANDLE hTrack);
HI_S32  IPC_Client_SetTargetPts(HI_HANDLE hTrack, HI_U32 u32TargetPts);
HI_S32  IPC_Client_SetRepeatTargetPts(HI_HANDLE hTrack);
HI_S32  IPC_Client_GetTrackPts(HI_HANDLE hTrack, HI_U32* pu32PtsMs, HI_U32* pu32OrgPtsMs);
HI_S32  IPC_Client_DropTrackStream(HI_HANDLE hTrack, HI_U32 u32SeekPts);
HI_S32  IPC_Client_DropFrame(HI_HANDLE hTrack, HI_U32 u32FrameCnt);
HI_S32  IPC_Client_SetSyncMode(HI_HANDLE hTrack, HI_MPI_AUDIOTRACK_SYNCMODE_E enSyncMode);
HI_S32  IPC_Client_GetDelayMs(HI_HANDLE hTrack, HI_U32* pu32DelayMs);
HI_S32  IPC_Client_SetEosFlag(HI_HANDLE hTrack, HI_BOOL bEosFlag);
HI_S32  IPC_Client_GetEosState(HI_HANDLE hTrack, HI_BOOL* bEosState);
HI_S32  IPC_Client_GetBufferStatus(HI_HANDLE hTrack, ADEC_BUFSTATUS_S* pstBufStatus);
HI_S32  IPC_Client_GetStreamInfo(HI_HANDLE hTrack, ADEC_STREAMINFO_S* pstStreamInfo);
HI_S32  IPC_Client_GetCapability(HI_U32* pu32Capability);
HI_S32  IPC_Client_CheckNewEvent(HI_HANDLE hTrack, HI_MPI_AO_RENDER_EVENT_S* pstNewEvent);
HI_S32  IPC_Client_GetRenderAllInfo(HI_HANDLE hTrack, HI_MPI_AO_RENDER_ALLINFO_S* pstAllInfo);
#ifdef DPT
HI_S32  IPC_Client_SetTrackMute(HI_HANDLE hTrack, HI_BOOL bMute);
HI_S32  IPC_Client_SetTrackPrescale(HI_HANDLE hTrack, const HI_UNF_SND_PRECIGAIN_ATTR_S* pstPreciGain);
HI_S32  IPC_Client_SetTrackSource(HI_HANDLE hTrack, HI_UNF_SND_SOURCE_E enSource);
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
