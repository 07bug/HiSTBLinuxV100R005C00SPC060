/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_common.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2016/05/30
  Description  :
  History       :
  1.Date        : 2016/05/30
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_COMMON_H__
#define  __RENDER_COMMON_H__

#include <pthread.h>
#include <stdio.h>

#include "hi_type.h"
#include "hi_unf_sound.h"
#include "hi_mpi_ao.h"
#include "engine_policy.h"
#include "HA.AUDIO.DOLBYMS12EXT.decode.h"
#include "hi_mpi_adec.h"
#include "hi_log_aorender.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef HI_PROC_SUPPORT
#define RENDER_DEBUG_SUPPORT
#endif

/**** Debug printf ***/
#define CHANNEL_DEBUG
#ifdef CHANNEL_DEBUG
#define CHANNEL_PRINTF    HI_INFO_AO
#define CHANNEL_TRACE()   HI_INFO_AO("%s called\n", __func__)
#else
#define CHANNEL_PRINTF(...)
#define CHANNEL_TRACE(...)
#endif
#define CPU_MASK                  (3)

#define RENDER_PTS_DEBUG
#ifdef RENDER_PTS_DEBUG
#define PTS_PRINTF        HI_WARN_AO
#else
#define PTS_PRINTF(...)
#endif

#define RENDER_SYNC_DEBUG
#ifdef RENDER_SYNC_DEBUG
#define SYNC_PRINTF       HI_WARN_AO
#else
#define SYNC_PRINTF(...)
#endif

/**** Source ***/
#define RENDER_MAX_SOURCE_NUM       (4)
#define RENDER_OUT_FRAME_CHANNEL    (2)
#define RENDER_OUT_FRAME_SAMPLERATE (48000)
#define RENDER_OUT_FRAME_BITWIDTH   (16)
#define RENDER_OUT_FRAME_BYTES      (4)
#define RENDER_PTS_MAX_DIFF         (0)
#define RENDER_MAX_EXTDEC_AOFRAME_NUM  (32) //Լ����824*1024(BufSize)/32768(DTSHD HBR), and must be power of 2
#define PES_PRIVATE_DATA_SIZE       (16)


typedef enum
{
    SOURCE_ID_MAIN = 0, /*Main audio*/
    SOURCE_ID_ASSOC,    /*Assoc/SecMain audio*/
    SOURCE_ID_EXTDEC,   /*Ext Main audio*/
    SOURCE_ID_OTTSOUND, /*OTT UI audio*/
    SOURCE_ID_SYSTEM,   /*System UI audio/TTS */
    SOURCE_ID_APP,      /*OTT TTS/System Accessibility*/
    SOURCE_ID_BUTT
} SOURCE_ID_E;

typedef enum
{
    SOURCE_STATE_IDLE,
    SOURCE_STATE_RUNNING,
    SOURCE_STATE_PAUSE,
    SOURCE_STATE_STOP,
    SOURCE_STATE_RESERVED //mapped for ui audio activate state
} SOURCE_STATE_E;

typedef struct
{
    HI_U32 u32SampleRate;
    HI_U32 u32BitPerSample;
    HI_U32 u32Channels;
} SOURCE_PCM_ATTR_S;

typedef enum
{
    SOURCE_SEEK_NONE,
    SOURCE_SEEK_ALIGN,
    SOURCE_SEEK_ES,
    SOURCE_SEEK_FRAME
} SOURCE_SEEK_E;

typedef enum
{
    PKG_SEEK_MODE_NONE,
    PKG_SEEK_MODE_INTER,
    PKG_SEEK_MODE_INTRA
} PKG_SEEK_MODE_E;

typedef enum
{
    USECASE_NORMAL = 0,
    USECASE_LOW_LATENCY,
    USECASE_DEEP_LATENCY,
} USE_CASE;

typedef struct
{
    HI_U8 au8Data[PES_PRIVATE_DATA_SIZE];
} AUD_PES_DATA_S;

typedef struct
{
    HI_U32                u32WIdx;
    HI_U32                u32RIdx;
    HI_HADECODE_OUTPUT_S  astAoFrameAttr[RENDER_MAX_EXTDEC_AOFRAME_NUM];
} AOFRAME_QUEUE_S;

typedef struct
{
    HI_U32 u32PhyAddr;
    HI_U32 u32MapSize;
    HI_VOID* pMapVirAddr;
    HI_VOID* pVirAddr;
} RENDER_MAP_ATTR_S;

typedef struct
{
    SOURCE_ID_E           enSourceID;
    SOURCE_STATE_E        enState;
    SOURCE_PCM_ATTR_S     stPcmAttr;

    HI_VOID*              pRBuffer;

    HI_U32                u32CurStreamPts; //u64 the stream pts, no async protect
    HI_U32                u32PreDecodePts; //the pts before decoding, used by gettrackpts with async protect

    HI_BOOL               bSinkStarted;
    HI_U32                u32SinkPts; //the pts after decoding, used by gettrackpts with async protect
    HI_BOOL               bRepeatEnable;

    HI_U32                u32DelayMs;
    HI_U32                u32DecoderPcmDelay;
    HI_U32                u32DecoderStaticDelay;
    HI_U32                u32PreDecoderPcmDelay;

    HI_BOOL               bDual;
    HI_BOOL               bWorking;
    HI_BOOL               bActivate;

    HI_BOOL               bSeekFrame;
    HI_U32                u32TargetPts;
    HI_U32                u32OrgTargetPts;
    PKG_SEEK_MODE_E       enPkGSeekType;

    HI_BOOL               bDoWipeInvalidPTS;
    HI_U32                u32SeekFrameTimeout; //In dual decoder mode, when the other source reach targetpts, the source timeout would be add

    HI_BOOL               bDropFrame;
    HI_U32                u32DropFrameCnt;

    HI_BOOL               bEnableMixer;
    HI_BOOL               bEnableDecoder;
    HI_BOOL               bMixing;
    HI_BOOL               bDecoding;

    HI_BOOL               bEosFlag;
    HI_BOOL               bEosState;
    //inter data
    HI_BOOL               bDecoderHadbeenStarted;
    HI_U32                u32StreamConsumedBytes; //u64
    HI_U32                u32DecodeLeftBytes; //u64
    HI_U32                u32AcquireSize;
    HI_BOOL               bFirstTimeStarted;

    HI_VOID*              pPtsQueue;
    HI_BOOL               bPesDataValid;
    AUD_PES_DATA_S        stPesData;

    HI_BOOL               bDataValid; //identify whether the data had been sent, used by check systemtrack alone

    HI_U32                u32InBufUsed;
    HI_U32                u32InBufSize;
    HI_U32                u32InBufUsedPercent;
    HI_U32                u32DecOkCnt;
    HI_U32                u32DecTryCnt;
    HI_U32                u32MixerCnt;
    HI_U32                u32DropStreamCnt;
    HI_U32                u32GetBufTryCnt;
    HI_U32                u32GetBufOkCnt;
    HI_U32                u32PutBufTryCnt;
    HI_U32                u32PutBufOkCnt;
    HI_U32                u32SendStreamTryCnt;
    HI_U32                u32SendStreamOkCnt;
    HI_U32                u32SendTrackDataTryCnt;
    HI_U32                u32SendTrackDataOkCnt;
    HI_U32                u32TotDecodeFrame;

    HI_MPI_AO_RENDER_EVENT_S stRenderEvent;
    HI_HADECODE_OUTPUT_S  stPackOut;
#ifdef DPT
    HI_UNF_SND_SOURCE_E   enSource;
    HI_UNF_SND_PRECIGAIN_ATTR_S stPrescale[HI_UNF_SND_SOURCE_BUTT];
#endif
    HI_U32                u32PauseDelayms;
    HI_U32                u32AddMediaPauseMuteMs;
    HI_U32                u32AddMediaMixerMuteMs;
    HI_U32                u32ExtraTargetPtsMs;
    HI_U32                u32PausePts;
    HI_U32                u32PauseDelay;
    HI_BOOL               bPauseUpdateDelayMs;
} SOURCE_S;

typedef struct
{
    SOURCE_S* pstSource[SOURCE_ID_BUTT];
    SOURCE_ID_E enPTSReportSource;
} SOURCE_MANAGER_S;

/**** Engine ***/
typedef struct
{
    HA_CODEC_ID_E  enCodecID;
    HI_HA_DECODE_S* pEntry;
    HI_VOID* pDllModule;
    HI_VOID* hDecoder;
    HI_BOOL  bLibInited;
    HI_VOID* pAdecIOMem;
    HA_MS12_SET_PROCINFO_S* pstMs12Proc;
    DOLBYMS12_CODEC_OPENCONFIG_S stMs12Cfg;
    HI_BOOL  bDataAvailable[SOURCE_ID_BUTT];
} ENGINE_CODEC_S;

typedef struct
{
    pthread_t Thread;
    HI_BOOL bThreadExit;
    HI_VOID* pROutBuffer[SOURCE_ID_BUTT];   //render outbuf malloced by engine, used by source
    ENGINE_CODEC_S* pstCodec;
    HI_HANDLE hExtTrack;
    HI_VOID* pPtsMuteQueue;
    ENGINE_POLICY_S stPolicy;
    USE_CASE enUseCase;
    HI_VIRT_ADDR_T tDelayMsVirAddr;
    RENDER_MAP_ATTR_S stDelayMapAttr;

#ifdef RENDER_DEBUG_SUPPORT
    HI_U32   u32RenderTimeOutCnt;
    HI_U32   u32SinkTimeOutCnt;
    HI_U32   u32SinkTrackId;
    HI_U32   u32SinkOutFrameCnt;
#endif
} ENGINE_MANAGER_S;

/**** Dump File ***/
typedef struct
{
    HI_BOOL bSaved;
    HI_U32  u32CurFileIndex;
    FILE*   pDumpFile;
    FILE*   pInPtsFile;
} FILE_DUMP_S;

typedef struct
{
    FILE_DUMP_S stEsDump[SOURCE_ID_BUTT];
    FILE_DUMP_S stPtsDump[SOURCE_ID_BUTT];
} DUMP_MANAGER_S;

typedef struct
{
    HI_BOOL bAllLogEnable;
    HI_BOOL bSyncLogEnable;
    HI_BOOL bCallLogEnable;
    HI_BOOL bCodecLogEnable;
    HI_BOOL bPtsLogEnable;
} LOG_MANAGER_S;

/**** Render Manager ***/
typedef struct
{
    SOURCE_MANAGER_S* pstSourceManager;
    ENGINE_MANAGER_S* pstEngineManger;

#ifdef RENDER_DEBUG_SUPPORT
    HI_BOOL           bProcInited;
    HI_PROC_ENTRY_S   stRenderProcEntry;
    HI_PROC_ENTRY_S   stCodecProcEntry;
    DUMP_MANAGER_S    stDumpManager;
    LOG_MANAGER_S     stLogManager;
#endif
} RENDER_MANAGER_S;

HI_VOID RENDER_LOCK(HI_VOID);
HI_VOID RENDER_UNLOCK(HI_VOID);
HI_VOID HACODEC_INST_LOCK(HI_VOID);
HI_VOID HACODEC_INST_UNLOCK(HI_VOID);
HI_VOID SOURCE_INST_LOCK(SOURCE_ID_E enSourceID);
HI_VOID SOURCE_INST_UNLOCK(SOURCE_ID_E enSourceID);
HI_VOID SOURCE_INST2_LOCK(SOURCE_ID_E enSourceID);
HI_VOID SOURCE_INST2_UNLOCK(SOURCE_ID_E enSourceID);
HI_VOID SOURCE_IO_LOCK(SOURCE_ID_E enSourceID);
HI_VOID SOURCE_IO_UNLOCK(SOURCE_ID_E enSourceID);
HI_VOID SINK_LOCK(HI_VOID);
HI_VOID SINK_UNLOCK(HI_VOID);
HI_VOID BUF_ACQUIRE_LOCK(HI_VOID);
HI_VOID BUF_ACQUIRE_UNLOCK(HI_VOID);
HI_VOID PROC_LOCK(HI_VOID);
HI_S32  PROC_TRYLOCK(HI_VOID);
HI_VOID PROC_UNLOCK(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
