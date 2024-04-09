/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pts_queue.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/06/28
  Description  :
  History       :
  1.Date        : 2016/06/28
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __PTS_QUEUE_H__
#define  __PTS_QUEUE_H__

#include "hi_type.h"
#include "render_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_STORED_PTS_NUM   (2048)

typedef enum
{
    PTS_SEEK_NONE,
    PTS_SEEK_ALIGN,
    PTS_SEEK_PACKAGE,
    PTS_SEEK_FRAME,
    PTS_SEEK_BUTT
} PTS_SEEK_E;

typedef struct
{
    HI_U32         u32PtsMs;
    HI_U32         u32OrgPts;
    HI_U32         u32BegPos;
    HI_U32         u32EndPos;
    HI_BOOL        bInjecting;    //cur queue data being injected
} PTS_ATTR_S;

typedef struct
{
    HI_BOOL        bInited;
    HI_U32         u32WIdx;
    HI_U32         u32RIdx;
    PTS_ATTR_S     astPtsAttr[MAX_STORED_PTS_NUM];
} PTS_QUEUE_S;

HI_BOOL PTSQUEUE_CheckIsFull(HI_VOID* handle);
HI_S32  PTSQUEUE_Create(HI_VOID* hISB, HI_VOID** pHandle);
HI_S32  PTSQUEUE_Detroy(HI_VOID* handle);
HI_S32  PTSQUEUE_Put(SOURCE_ID_E enSourceID, HI_VOID* handle, HI_U32 u32PtsMs, HI_U32 u32DataSize);
HI_S32  PTSQUEUE_Find(HI_VOID* handle, HI_U32 u32Pos, HI_U32* pu32Pts);
HI_S32  PTSQUEUE_Update(HI_VOID* handle, HI_U32 u32Delta);
HI_U32  PTSQUEUE_GetReadPts(HI_VOID* handle);
HI_S32  PTSQUEUE_Reset(HI_VOID* handle);
PTS_SEEK_E PTSQUEUE_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts);
PTS_SEEK_E PTSQUEUE_Drop_Seek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts);
PTS_SEEK_E PTSQUEUE_Drop_PolicySeek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts);
PTS_SEEK_E PTSQUEUE_Drop_InvertSeek(HI_VOID* handle, HI_U32 u32TargetPts, HI_U32* pu32NearbyPos, HI_U32* pu32NearbyPts);
HI_BOOL PTSQUEUE_UpdatedAlignPacket(HI_VOID* handle, HI_U32 u32ConsumedBytes, HI_U32* pu32AlignPos, HI_U32* pu32AlignPts);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
