/******************************************************************************

  Copyright (C), 2001-2018, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sync.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   :
******************************************************************************/
#ifndef __DRV_SYNC_H__
#define __DRV_SYNC_H__

#include "hi_drv_sync.h"
#include "drv_sync_ioctl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_BOOL SYNC_VerifyHandle(HI_HANDLE hSync);
HI_S32  SYNC_StartSync(HI_HANDLE hSync);
HI_VOID SYNC_VidProc(HI_HANDLE hSync, SYNC_VID_INFO_S *pVidInfo, SYNC_VID_OPT_S *pVidOpt);
HI_VOID SYNC_AudProc(HI_HANDLE hSync, SYNC_AUD_INFO_S *pAudInfo, SYNC_AUD_OPT_S *pAudOpt);
HI_VOID SYNC_PcrProc(HI_HANDLE hSync, HI_U64 PcrValue, HI_U64  StcValue);
HI_S32  SYNC_PauseSync(HI_U32 SyncId);
HI_S32  SYNC_ResumeSync(HI_U32 SyncId);
HI_S32  SYNC_GetTime(HI_U32 SyncId, HI_U32 *pLocalTime, HI_U32 *pPlayTime);
HI_U32  SYNC_GetLocalTime(SYNC_S *pSync, SYNC_CHAN_E enChn);
HI_U32  SYNC_GetSysTime(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
