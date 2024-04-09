/******************************************************************************
  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_win_hdr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015-09-23
  Description   :structures define and functions declaration for processing
                 Dolby HDR in window.
  History       :
  1.Date        : 2015-09-23
    Author      : sdk
    Modification: Created file
*******************************************************************************/

#ifndef __DRV_WIN_HDR_H__
#define __DRV_WIN_HDR_H__

#include "hi_type.h"
#include "hi_drv_win.h"
#include "hi_drv_video.h"
#include "drv_win_buffer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#ifdef VDP_DOLBY_HDR_SUPPORT
HI_S32 WinQueueDolbyFrame(HI_HANDLE hWin, WIN_XDR_FRAME_S *pstWinXdrFrm);

//put a new Dolby frame into buffer
HI_S32 WinBuf_PutNewDolbyFrame(WB_POOL_S       *pstWinBP,
                               WIN_XDR_FRAME_S *pstWinXdrFrm,
                               HI_U32           u32PlayCnt);

HI_S32 WIN_SetDolbyLibInfo(WIN_DOLBY_LIB_INFO_S  *pstDolbyLibInfo);

HI_VOID WIN_ShowDolbyLibInfo(HI_VOID);

HI_BOOL WIN_GetDolbyLibStatus(HI_VOID);
#else

#define WinQueueDolbyFrame(a,b)             HI_SUCCESS
#define WinBuf_PutNewDolbyFrame(a,b,c)      HI_SUCCESS
#define WIN_SetDolbyLibInfo(a)              HI_SUCCESS
#define WIN_GetDolbyLibStatus()             HI_TRUE
#define WIN_ShowDolbyLibInfo()
#endif

HI_S32 WIN_SetMode(HI_HANDLE hWin, HI_DRV_WINDOW_MODE_E enWinMode);

/* default enable win's hdr function. */
HI_S32 WIN_CloseHdrPath(HI_HANDLE hWin,HI_BOOL bEnable);

/* put a new hdr10 frame into buffer,bDolbyHdr=false indicate to go through Hisi-self HDR path */
HI_S32 WinBuf_PutNewHdrFrame(WB_POOL_S            *pstWinBP,
                             WIN_XDR_FRAME_S      *pstWinXdrFrm,
                             HI_U32                u32PlayCnt);

//get next frame for winDoviRefInfo ,note:the node of current frame has been removed in FULL array in this interrupt.
HI_DRV_VIDEO_FRAME_S* WinBuf_GetNextCfgFrm(WB_POOL_S *pstWinBP);


/* get display output type and gfx exist state,ONLY use for Dolby update metadata. */
HI_S32 WIN_GetDispOutputAndGfxState(HI_HANDLE hWin,
                                    HI_DRV_DISP_OUT_TYPE_E *penDispType,
                                    HI_BOOL  *pbNeedProcessGfx);

/* set window whether to go through Hisi-self path */
HI_S32 WIN_SetHisiPath(HI_HANDLE hWin,HI_BOOL bEnable);



HI_VOID WIN_JudgeHdrFrame(HI_DRV_VIDEO_FRAME_TYPE_E  enFrameType,HI_BOOL *pbIsHdrFrame);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

