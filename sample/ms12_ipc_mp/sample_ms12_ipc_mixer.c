/******************************************************************************

  Copyright (C), 20016-2019, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_ms12_ipc_mixer.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       :
  Description   :
  History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_mpi.h"

#include "HA.AUDIO.G711.codec.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.AMRWB.codec.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"
#include "HA.AUDIO.DOLBYTRUEHD.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"
#if defined (DOLBYPLUS_HACODEC_SUPPORT)
 #include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif
#include "HA.AUDIO.AC3PASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSM6.decode.h"

#include "HA.AUDIO.DTSPASSTHROUGH.decode.h"
#include "HA.AUDIO.FFMPEG_DECODE.decode.h"
#include "HA.AUDIO.AAC.encode.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"
#include "HA.AUDIO.DOLBYMS12EXT.decode.h"

#include "engine_codec_private.h"

#define  PLAY_DMX_ID    0
#define  TTS_INDEX      0
#define  UIAUDIO_INDEX  1
#define  SYSTEM_INDEX   2

#define  THREAD_TYPE_MAIN    0
#define  THREAD_TYPE_AD      1

static FILE*            g_pTsFile = HI_NULL;
static FILE*            g_pEsFile = HI_NULL;
static FILE*            g_pEsAdFile = HI_NULL;
static FILE*            g_pcmFile[SYSTEM_INDEX + 1];

static HI_HANDLE        g_hOttTrack = HI_NULL;
static HI_HANDLE        g_hSysTrack = HI_NULL;
static HI_HANDLE        g_hTtsTrack = HI_NULL;

static pthread_t        g_TsThd;
static HI_BOOL          g_bStopTsThread = HI_FALSE;
static pthread_t        g_EsThd;
static HI_BOOL          g_StopAudThread = HI_FALSE;
static pthread_t        g_EsAdThd;
static HI_BOOL          g_StopAudAdThread = HI_FALSE;

static HI_BOOL          g_bStopFlag[SYSTEM_INDEX + 1];
static pthread_t        g_hPcmThread[SYSTEM_INDEX + 1];

static pthread_mutex_t  g_TsMutex;
static HI_HANDLE        g_TsBuf;
static PMT_COMPACT_TBL* g_pProgTbl = HI_NULL;

static HI_HANDLE        g_hWin    = HI_INVALID_HANDLE;
static HI_HANDLE        g_hAvplay = HI_INVALID_HANDLE;
static HI_HANDLE        g_hTrack  = HI_INVALID_HANDLE;

HI_BOOL                 g_bUseMS12 = HI_TRUE;

static HI_S32           g_s32EsBufCnt = 1;
static HI_S32           g_s32OttPlay  = 1;
static HI_S32           g_s32FrameCnt = 0;
static HA_CODEC_ID_E    g_enCodecID;
static HI_U8            g_u8DecOpenBuf[1024];

#if defined (DOLBYPLUS_HACODEC_SUPPORT)

DOLBYPLUS_STREAM_INFO_S g_stDDpStreamInfo;

/*dolby Dual Mono type control*/
static HI_U32  g_u32DolbyAcmod = 0;
static HI_BOOL g_bDrawChnBar = HI_TRUE;

#endif

static HI_S32 HIADP_AVPlay_PlayProg_MS12_PRIV(HI_HANDLE hAvplay,PMT_COMPACT_TBL *pProgTbl,HI_U32 ProgNum,HI_BOOL bAudPlay);
static HI_S32 HIADP_AVPlay_SetAdecAttr_MS12_PRIV(HI_HANDLE hAvplay, HI_U32 enADecType, HI_HA_DECODEMODE_E enMode);

HI_VOID TsTthread(HI_VOID* args)
{
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                s32Ret;
    //UNUSED(args);

    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        s32Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, 188 * 50, &StreamBuf, 1000);
        if (s32Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188 * 50, g_pTsFile);
        if (Readlen <= 0)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        s32Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (s32Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }

        pthread_mutex_unlock(&g_TsMutex);
        g_s32FrameCnt++;

        usleep(10000);
    }

    s32Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (s32Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }
}

HI_VOID EsAudTthread(HI_VOID* args)
{
    HI_HANDLE hAvplay;
    HI_UNF_STREAM_BUF_S StreamBuf;
    HI_U32 Readlen;
    HI_S32 s32Ret;
    HI_U32 u32ThreadType;
    HI_UNF_AVPLAY_PUTBUFEX_OPT_S  stExOpt;
    HI_U32 u32BufId = HI_UNF_AVPLAY_BUF_ID_ES_AUD;
    FILE* pFile = HI_NULL;
    HI_BOOL* pbStopThreadFlag = HI_NULL;

    hAvplay = g_hAvplay;
    HI_U32 u32Pts = 0;
    stExOpt.bContinue = HI_TRUE;
    stExOpt.bEndOfFrm = HI_FALSE;
    u32ThreadType = *((HI_U32*)args);

    if (THREAD_TYPE_MAIN == u32ThreadType)
    {
        pFile = g_pEsFile;
        u32BufId = HI_UNF_AVPLAY_BUF_ID_ES_AUD;
        pbStopThreadFlag = &g_StopAudThread;
    }
    else
    {
        pFile = g_pEsAdFile;
        u32BufId = HI_UNF_AVPLAY_BUF_ID_ES_AUD_AD;
        pbStopThreadFlag = &g_StopAudAdThread;
    }

    while (!(*pbStopThreadFlag))
    {
        if (g_s32EsBufCnt == 0)
        {
            usleep(5 * 1000);
            continue;
        }

        s32Ret = HI_UNF_AVPLAY_GetBuf(hAvplay, u32BufId, 1024, &StreamBuf, 0);
        if (HI_SUCCESS == s32Ret)
        {
            Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 1024, pFile);
            if (Readlen > 0)
            {
                s32Ret = HI_UNF_AVPLAY_PutBufEx(hAvplay, u32BufId, Readlen, u32Pts, &stExOpt);
                if (s32Ret != HI_SUCCESS)
                {
                    printf("call HI_UNF_AVPLAY_PutBufEx failed.\n");
                }
                u32Pts += Readlen;
            }
            else if (Readlen == 0)
            {
                //printf("read aud file end and rewind!\n");
                rewind(pFile);
            }
            else
            {
                perror("read aud file error\n");
            }
        }
        else
        {
            usleep(5 * 1000);
        }

        //usleep(1000 * 17);
    }
}

HI_VOID PcmThread(HI_VOID* args)
{
    HI_S32 s32Ret;
    HI_U32 u32Readlen;
    HI_U32 u32WantedSize;
    HI_U32 u32StreamId = *((HI_U32*)args);
    HI_BOOL bAudBufAvail = HI_FALSE;

    HI_UNF_AO_FRAMEINFO_S stAOFrame;
    HI_VOID* PmcBuf = HI_NULL;
    HI_HANDLE* phTrack;

    if (UIAUDIO_INDEX == u32StreamId)
    {
        phTrack = &g_hOttTrack;
    }
    else if (TTS_INDEX == u32StreamId)
    {
        phTrack = &g_hTtsTrack;
    }
    else if (SYSTEM_INDEX == u32StreamId)
    {
        phTrack = &g_hSysTrack;
    }
    else
    {
        printf("Error pcm stream id (0x%x)\n", u32StreamId);
        return;
    }

    //for Ott audio or tts, only support 48K 16bit pcm
    stAOFrame.s32BitPerSample = 16;
    stAOFrame.u32Channels   = 2;
    stAOFrame.bInterleaved  = 1;
    stAOFrame.u32SampleRate = 48000;
    stAOFrame.u32PtsMs = 0xffffffff;
    stAOFrame.ps32BitsBuffer = HI_NULL;
    stAOFrame.u32BitsBytesPerFrame = 0;
    stAOFrame.u32FrameIndex = 0;
    stAOFrame.u32PcmSamplesPerFrame = 1536;

    u32WantedSize = 1536 * 2 * sizeof(HI_S16);
    PmcBuf = (HI_VOID*)malloc(u32WantedSize);
    stAOFrame.ps32PcmBuffer = (HI_S32*)(PmcBuf);

    while (HI_TRUE != g_bStopFlag[u32StreamId])
    {
        if ((g_s32OttPlay == 0) && (UIAUDIO_INDEX == u32StreamId))
        {
            usleep(5 * 1000);
            continue;
        }

        if (HI_FALSE == bAudBufAvail)
        {
            u32Readlen = fread(PmcBuf, 1, u32WantedSize,  g_pcmFile[u32StreamId]);
            if (u32Readlen != u32WantedSize)
            {
                rewind(g_pcmFile[u32StreamId]);
            }
        }

        s32Ret = HI_UNF_SND_SendTrackData(*phTrack, &stAOFrame);
        if (HI_SUCCESS == s32Ret)
        {
            bAudBufAvail = HI_FALSE;
            usleep(1000 * 30);
            continue;
        }
        else if (HI_FAILURE == s32Ret)
        {
            printf("HI_UNF_SND_SendTrackData failed(0x%x)!\n", s32Ret);
            break;
        }
        else
        {
            usleep(5 * 1000);
            bAudBufAvail = HI_TRUE;
            continue;
        }
    }

    free(PmcBuf);
}
#if defined (DOLBYPLUS_HACODEC_SUPPORT)

static HI_VOID DDPlusCallBack(DOLBYPLUS_EVENT_E Event, HI_VOID *pUserData)
{
    DOLBYPLUS_STREAM_INFO_S *pstInfo = (DOLBYPLUS_STREAM_INFO_S *)pUserData;
#if 0
    printf( "DDPlusCallBack show info:\n \
                s16StreamType          = %d\n \
                s16Acmod               = %d\n \
                s32BitRate             = %d\n \
                s32SampleRateRate      = %d\n \
                Event                  = %d\n",
                pstInfo->s16StreamType, pstInfo->s16Acmod, pstInfo->s32BitRate, pstInfo->s32SampleRateRate,Event);
#endif
    g_u32DolbyAcmod = pstInfo->s16Acmod;

    if (HA_DOLBYPLUS_EVENT_SOURCE_CHANGE == Event)
    {
        g_bDrawChnBar = HI_TRUE;
        //printf("DDPlusCallBack enent !\n");
    }
    return;
}

#endif

HI_S32 HIADP_AVPlay_SetAdecAttr_MS12_PRIV(HI_HANDLE hAvplay, HI_U32 enADecType, HI_HA_DECODEMODE_E enMode)
{
    HI_UNF_ACODEC_ATTR_S AdecAttr;
    DOLBYMS12_CODEC_OPENCONFIG_S stMs12Cfg; //NOTE Static mem when being called

    HIAPI_RUN_RETURN(HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr));
    AdecAttr.enType = enADecType;

    if (HA_AUDIO_ID_AAC == AdecAttr.enType)
    {
        HA_AAC_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_MP3 == AdecAttr.enType)
    {
        HA_MP3_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
    }
    else if (HA_AUDIO_ID_MS12_AAC == AdecAttr.enType)
    {
        HA_DOLBYMS12_CodecGetDefaultOpenConfig(&stMs12Cfg);
        stMs12Cfg.enInputType = MS12_HEAAC;
        HA_DOLBYMS12_CodecGetDefaultOpenParam(&AdecAttr.stDecodeParam, &stMs12Cfg);
    }
    else if (HA_AUDIO_ID_AC3PASSTHROUGH == AdecAttr.enType)
    {
        HA_AC3PASSTHROUGH_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam));
        AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_THRU;
    }
    else if (HA_AUDIO_ID_DTSHD == AdecAttr.enType)
    {
        DTSHD_DECODE_OPENCONFIG_S *pstConfig = (DTSHD_DECODE_OPENCONFIG_S *)g_u8DecOpenBuf;
        HA_DTSHD_DecGetDefalutOpenConfig(pstConfig);
        HA_DTSHD_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), pstConfig);
        AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;
    }
    else if (HA_AUDIO_ID_DOLBY_PLUS== AdecAttr.enType)
    {
        DOLBYPLUS_DECODE_OPENCONFIG_S *pstConfig = (DOLBYPLUS_DECODE_OPENCONFIG_S *)g_u8DecOpenBuf;
        HA_DOLBYPLUS_DecGetDefalutOpenConfig(pstConfig);
        pstConfig->pfnEvtCbFunc[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE] = DDPlusCallBack;
        pstConfig->pAppData[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE] = &g_stDDpStreamInfo;
        /* Dolby DVB Broadcast default settings */
        pstConfig->enDrcMode = DOLBYPLUS_DRC_RF;
        pstConfig->enDmxMode = DOLBYPLUS_DMX_SRND;
        HA_DOLBYPLUS_DecGetDefalutOpenParam(&(AdecAttr.stDecodeParam), pstConfig);
        AdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;
        AdecAttr.enType = HA_AUDIO_ID_DOLBY_PLUS;
    }
    else if (HA_AUDIO_ID_MS12_DDP== AdecAttr.enType)
    {
        HA_DOLBYMS12_CodecGetDefaultOpenConfig(&stMs12Cfg);
        HA_DOLBYMS12_CodecGetDefaultOpenParam(&AdecAttr.stDecodeParam, &stMs12Cfg);
    }
    else
    {
        printf(" func:%s line:%d Unkown Type: 0x%x\n", __func__, __LINE__, AdecAttr.enType);
        return HI_FAILURE;
    }

    HIAPI_RUN_RETURN(HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AdecAttr));

    return HI_SUCCESS;
}

HI_S32 HIADP_AVPlay_PlayProg_MS12_PRIV(HI_HANDLE hAvplay,PMT_COMPACT_TBL *pProgTbl,HI_U32 ProgNum,HI_BOOL bAudPlay)
{
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_U32                  VidPid;
    HI_U32                  AudPid;
    HI_U32                  PcrPid;
    HI_UNF_VCODEC_TYPE_E    enVidType;
    HI_U32                  u32AudType;
    HI_S32                  Ret;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_AVPLAY_Stop failed.\n");
        return Ret;
    }

    ProgNum = ProgNum % pProgTbl->prog_num;
    if (pProgTbl->proginfo[ProgNum].VElementNum > 0 )
    {
        VidPid = pProgTbl->proginfo[ProgNum].VElementPid;
        enVidType = pProgTbl->proginfo[ProgNum].VideoType;
    }
    else
    {
        VidPid = INVALID_TSPID;
        enVidType = HI_UNF_VCODEC_TYPE_BUTT;
    }

    if (pProgTbl->proginfo[ProgNum].AElementNum > 0)
    {
        AudPid  = pProgTbl->proginfo[ProgNum].AElementPid;
        u32AudType = pProgTbl->proginfo[ProgNum].AudioType;
    }
    else
    {
        AudPid = INVALID_TSPID;
        u32AudType = 0xffffffff;
    }

#ifdef ROUTE_MS12_METHOD_B  //Method B. How to route MS12
    if ((HA_AUDIO_ID_AAC == u32AudType) || (HA_AUDIO_ID_DOLBY_PLUS == u32AudType) || (HA_AUDIO_ID_AC3PASSTHROUGH == u32AudType))
    {
        if (HI_TRUE == g_bUseMS12)
        {
            HI_BOOL bMS12Support;
            if (HA_AUDIO_ID_AAC == u32AudType)
            {
                Ret = HI_UNF_AVPLAY_IsAudioFormatSupport(FORMAT_MS12_AAC, &bMS12Support);
                printf(" func:%s line:%d ret:0x%x bsupport: %d\n", __func__, __LINE__, Ret, bMS12Support);
                if ((HI_SUCCESS == Ret) && (HI_TRUE == bMS12Support))
                {
                    printf("\n\nMethod B to route [MS12 AAC] \n\n");
                    u32AudType = HA_AUDIO_ID_MS12_AAC;
                }
            }
            else
            {
                Ret = HI_UNF_AVPLAY_IsAudioFormatSupport(FORMAT_MS12_DDP, &bMS12Support);
                printf(" func:%s line:%d ret:0x%x bsupport: %d\n", __func__, __LINE__, Ret, bMS12Support);
                if ((HI_SUCCESS == Ret) && (HI_TRUE == bMS12Support))
                {
                    printf("\n\nMethod B to route [MS12 DDP] \n\n");
                    u32AudType = HA_AUDIO_ID_MS12_DDP;
                }
            }
        }
    }
#endif

    PcrPid = pProgTbl->proginfo[ProgNum].PcrPid;
    if (INVALID_TSPID != PcrPid)
    {
        Ret = HI_UNF_AVPLAY_SetAttr(hAvplay,HI_UNF_AVPLAY_ATTR_ID_PCR_PID,&PcrPid);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_AVPLAY_SetAttr failed.\n");

            PcrPid = INVALID_TSPID;
            Ret = HI_UNF_AVPLAY_SetAttr(hAvplay,HI_UNF_AVPLAY_ATTR_ID_PCR_PID,&PcrPid);
            if (HI_SUCCESS != Ret)
            {
                printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
                return Ret;
            }
        }
    }

    if (VidPid != INVALID_TSPID)
    {
        Ret = HIADP_AVPlay_SetVdecAttr(hAvplay,enVidType,HI_UNF_VCODEC_MODE_NORMAL);
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID,&VidPid);
        if (Ret != HI_SUCCESS)
        {
            printf("call HIADP_AVPlay_SetVdecAttr failed.\n");
            return Ret;
        }

        Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_AVPLAY_Start failed.\n");
            return Ret;
        }
    }

    if (HI_TRUE == bAudPlay && AudPid != INVALID_TSPID)
    {
        Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &AudPid);
        if (HI_SUCCESS != Ret)
        {
            printf("HIADP_AVPlay_SetAdecAttr failed:%#x\n",Ret);
            return Ret;
        }

        Ret = HIADP_AVPlay_SetAdecAttr_MS12_PRIV(hAvplay, u32AudType, HD_DEC_MODE_RAWPCM);

        Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_AVPLAY_Start to start audio failed.\n");
            //return Ret;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 System_init(HI_VOID)
{
    HI_S32    s32Ret;

    HI_SYS_Init();

    HIADP_MCE_Exit();

    s32Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
    }
    HIADP_Disp_Init(HI_UNF_ENC_FMT_1080P_50);

    return s32Ret;
}

static HI_VOID System_Deinit(HI_VOID)
{
    HIADP_Disp_DeInit();
    HIADP_Snd_DeInit();
    HI_SYS_DeInit();
}

static HI_S32 Create_TsMedia(HI_VOID)
{
    HI_S32                      s32Ret;
    HI_HANDLE                   hAvplay;
    HI_HANDLE                   hTrack;
    HI_HANDLE                   hWin;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    s32Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_1080i_50);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        return s32Ret;
    }

    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    s32Ret |= HIADP_VO_CreatWin(HI_NULL, &hWin);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }
    g_hWin = hWin;
    s32Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto VO_DEINIT;
    }

    s32Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID, HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_AVPLAY_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto TSBUF_FREE;
    }

    //step 2 Create avplay
    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    s32Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    g_hAvplay = hAvplay;

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }

    s32Ret = HI_UNF_VO_AttachWindow(g_hWin, hAvplay);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n", s32Ret);
        goto ACHN_CLOSE;
    }

    s32Ret = HI_UNF_VO_SetWindowEnable(g_hWin, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    //step 3 Create Salvetrack
    //In some usecase: SlaveTrack should be created, Because when only TTS/UI Audio Track exists, MS12 would
    //create mastertrack to passthrough, So User do not create mastertrack.
    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    g_hTrack = hTrack;

    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;

    s32Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }
    s32Ret =  HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_I2S0, HI_FALSE);
    s32Ret |=  HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_I2S1, HI_FALSE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_SetMute failed.\n");
        goto SND_DETACH;
    }


    s32Ret = HI_UNF_AVPLAY_GetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    s32Ret |= HI_UNF_AVPLAY_SetAttr(g_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    pthread_mutex_init(&g_TsMutex, NULL);
    g_bStopTsThread = HI_FALSE;
    pthread_create(&g_TsThd, HI_NULL, (HI_VOID*)TsTthread, HI_NULL);

    HIADP_Search_Init();
    s32Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HIADP_Search_GetAllPmt failed.\n");
        goto PSISI_FREE;
    }

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

    s32Ret = HIADP_AVPlay_PlayProg_MS12_PRIV(g_hAvplay, g_pProgTbl, 0, HI_TRUE);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HIADP_AVPlay_PlayProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    return HI_SUCCESS;

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;
    HIADP_Search_DeInit();
    pthread_mutex_destroy(&g_TsMutex);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(g_hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(g_hWin, hAvplay);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSBUF_FREE:
    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

    return s32Ret;
}

static HI_S32 Create_EsMedia(HI_BOOL bAdEnable)
{
    HI_S32                      s32Ret;
    static HI_U32               u32ThreadType = THREAD_TYPE_MAIN;
    HI_HANDLE                   hTrack;
    HI_HANDLE                   hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;
    HI_UNF_ENC_FMT_E g_enDefaultFmt = HI_UNF_ENC_FMT_720P_50;

    s32Ret = HI_UNF_AVPLAY_Init();
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        return s32Ret;
    }

    s32Ret  = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    s32Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    g_hAvplay = hAvplay;
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    s32Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto AVPLAY_DESTROY;
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto ACHN_CLOSE;
    }
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto ACHN_CLOSE;
    }

    g_hTrack = hTrack;
    s32Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    s32Ret = HIADP_AVPlay_SetAdecAttr_MS12_PRIV(hAvplay, (HI_U32)g_enCodecID, HD_DEC_MODE_RAWPCM);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    s32Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Start failed.\n");
        goto SND_DETACH;
    }

    s32Ret = HIADP_Disp_Init(g_enDefaultFmt);
    if (s32Ret != HI_SUCCESS)
    {
        printf("call DispInit failed.\n");
        goto AVPLAY_STOP;
    }

    g_StopAudThread = HI_FALSE;
    pthread_create(&g_EsThd, HI_NULL, (HI_VOID*)EsAudTthread, (HI_VOID*)(&u32ThreadType));

    if (HI_TRUE == bAdEnable)
    {
        printf("Create ad thread\n");
        static HI_U32  u32AdThreadType = THREAD_TYPE_AD;

        g_StopAudAdThread = HI_FALSE;
        pthread_create(&g_EsAdThd, HI_NULL, (HI_VOID*)EsAudTthread, (HI_VOID*)(&u32AdThreadType));
    }

    return HI_SUCCESS;

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

    return s32Ret;
}

static HI_VOID Destroy_TsMedia(HI_VOID)
{
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    g_bStopTsThread = HI_TRUE;
    pthread_join(g_TsThd, HI_NULL);

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

    HIADP_Search_FreeAllPmt(g_pProgTbl);
    HIADP_Search_DeInit();

    HI_UNF_SND_Detach(g_hTrack, g_hAvplay);

    HI_UNF_SND_DestroyTrack(g_hTrack);

    HI_UNF_VO_SetWindowEnable(g_hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(g_hWin, g_hAvplay);

    HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

    HI_UNF_AVPLAY_Destroy(g_hAvplay);

    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

    HI_UNF_AVPLAY_DeInit();

    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

    HI_UNF_VO_DestroyWindow(g_hWin);
    HIADP_VO_DeInit();

}

static HI_VOID Destroy_EsMedia(HI_BOOL bAdEnable)
{
    HI_UNF_AVPLAY_STOP_OPT_S  Stop;

    g_StopAudThread = HI_TRUE;
    pthread_join(g_EsThd, HI_NULL);

    if (HI_TRUE == bAdEnable)
    {
        g_StopAudAdThread = HI_TRUE;
        pthread_join(g_EsAdThd, HI_NULL);
    }

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

    HI_UNF_SND_Detach(g_hTrack, g_hAvplay);

    HI_UNF_SND_DestroyTrack(g_hTrack);

    HI_UNF_AVPLAY_ChnClose(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_AVPLAY_Destroy(g_hAvplay);

    HI_UNF_AVPLAY_DeInit();
}

static HI_S32 Create_Ott_Track(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_OTTSOUND, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_hOttTrack);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Destroy_Ott_Track(HI_VOID)
{
    if (HI_NULL != g_hOttTrack)
    {
        HI_UNF_SND_DestroyTrack(g_hOttTrack);
    }
    g_hOttTrack = HI_NULL;
}

static HI_S32 Create_Tts_Track(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_APPAUDIO, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_hTtsTrack);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Destroy_Tts_Track(HI_VOID)
{
    if (HI_NULL != g_hTtsTrack)
    {
        SETEOSFLAG_CONFIG_S stRendeCmd;
        HI_UNF_AUDIOTRACK_CONFIG_S stConfig;

        stRendeCmd.bEosFlag = HI_TRUE;
        stConfig.u32ConfigType = CONFIG_SETEOSFLAG;
        stConfig.pConfigData = &stRendeCmd;

        HI_UNF_SND_SetTrackConfig(g_hTtsTrack, &stConfig);
        HI_UNF_SND_DestroyTrack(g_hTtsTrack);
    }
    g_hTtsTrack = HI_NULL;
}

static HI_S32 Create_Sys_Track(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SYSTEMAUDIO, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &g_hSysTrack);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID Destroy_Sys_Track(HI_VOID)
{
    if (HI_NULL != g_hSysTrack)
    {
        HI_UNF_SND_DestroyTrack(g_hSysTrack);
    }
    g_hSysTrack = HI_NULL;
}

static void print_usage()
{
    printf("Usage: sample_ms12_ipc_mixer esddp/esaac/esadddp/esadaac/esmp3/esdts es_file [sys raw_48k_16bit_2ch.pcm] [tts raw_48k_16bit_2ch.pcm] [ott raw_48k_16bit_2ch.pcm]\n");
    printf("Example1:./sample_ms12_ipc_mixer esddp ./Dual_Strm_2PID_swp_AssocRouting_ddp_main.ec3 tts ./48k2ch16bit_tts_music.pcm ott ./netflix_tts_007_tc1.pcm\n");
    printf("Example2:./sample_ms12_ipc_mixer esddp ./main.ec3 esadddp ./ad.ec3\n");
    printf("Example3:./sample_ms12_ipc_mixer esaac ./Large_PES_Size_aac.adts\n");
    printf("Example4:./sample_ms12_ipc_mixer sys ./raw_48k_16bit_2ch.pcm\n");
    printf("Example5:./sample_ms12_ipc_mixer tts ./raw_48k_16bit_2ch.pcm\n");
    printf("Example6:./sample_ms12_ipc_mixer ott ./raw_48k_16bit_2ch.pcm\n");
    printf("Example7:./sample_ms12_ipc_mixer sys ./raw_48k_16bit_2ch.pcm ott ./raw_48k_16bit_2ch.pcm\n");
}

HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_BOOL                     bTsMedia = HI_FALSE;
    HI_BOOL                     bEsMedia = HI_FALSE;
    HI_BOOL                     bUIAudio = HI_FALSE;
    HI_BOOL                     bSystem = HI_FALSE;
    HI_BOOL                     bTts = HI_FALSE;
    HI_BOOL                     bEsAd = HI_FALSE;
    HI_U32                      u32Cnt;
    HI_U32                      u32TtsFileID = -1;
    HI_U32                      u32SysFileID = -1;
    HI_U32                      u32UIAudioFileID = -1;
    HI_U32                      u32EsFileID = -1;
    HI_U32                      u32EsAdFileID = -1;
    HI_U32                      u32TsFileID = -1;
    HI_CHAR                     InputCmd[32];
    HI_U32                      u32StreamId = 0;

    if (argc < 3)
    {
        print_usage();
        return -1;
    }

    g_bUseMS12 = HI_TRUE;

    for (u32Cnt = 1; u32Cnt <= argc - 1; u32Cnt++)
    {
        if (!strcasecmp("tts", argv[u32Cnt]))
        {
            u32TtsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32TtsFileID])
            {
                bTts = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }

        if (!strcasecmp("ott", argv[u32Cnt]))
        {
            u32UIAudioFileID = ++u32Cnt;
            if (HI_NULL != argv[u32UIAudioFileID])
            {
                bUIAudio = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }

        if (!strcasecmp("sys", argv[u32Cnt]))
        {
            u32SysFileID = ++u32Cnt;
            if (HI_NULL != argv[u32SysFileID])
            {
                printf("--play system audio--\n");
                bSystem = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }

        if (!strcasecmp("esddp", argv[u32Cnt]))
        {
            printf("--play dolby es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            u32EsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsFileID])
            {
                bEsMedia = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
            g_enCodecID = HA_AUDIO_ID_DOLBY_PLUS;
        }

        if (!strcasecmp("esadddp", argv[u32Cnt]))
        {
            printf("--play dolby ad es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            if (HI_FALSE == bEsMedia)
            {
                printf("No main audio to play ad\n");
                return -1;
            }

            u32EsAdFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsAdFileID])
            {
                bEsAd = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }

        }

        if (!strcasecmp("esaac", argv[u32Cnt]))
        {
            printf("--play aac es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            u32EsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsFileID])
            {
                bEsMedia = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
            g_enCodecID = HA_AUDIO_ID_AAC;
        }

        if (!strcasecmp("esadaac", argv[u32Cnt]))
        {
            printf("--play aac ad es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            if (HI_FALSE == bEsMedia)
            {
                printf("No main audio to play ad\n");
                return -1;
            }

            u32EsAdFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsAdFileID])
            {
                bEsAd = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }

        if (!strcasecmp("esmp3", argv[u32Cnt]))
        {
            printf("--play mp3 es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            u32EsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsFileID])
            {
                bEsMedia = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
            g_enCodecID = HA_AUDIO_ID_MP3;
        }

        if (!strcasecmp("esdts", argv[u32Cnt]))
        {
            printf("--play dts es--\n");
            if (HI_TRUE == bTsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            u32EsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32EsFileID])
            {
                bEsMedia = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
            g_enCodecID = HA_AUDIO_ID_DTSHD;
        }

        if (!strcasecmp("ts", argv[u32Cnt]))
        {
            if (HI_TRUE == bEsMedia)
            {
                printf("Only suport es or ts play at the same time");
                return -1;
            }

            u32TsFileID = ++u32Cnt;
            if (HI_NULL != argv[u32TsFileID])
            {
                bTsMedia = HI_TRUE;
            }
            else
            {
                print_usage();
                return -1;
            }
        }

        if (!strcasecmp("pm", argv[u32Cnt]))
        {
            g_s32EsBufCnt = 0;
        }

        if (!strcasecmp("po", argv[u32Cnt]))
        {
            g_s32OttPlay = 0;
        }
    }

    if (HI_TRUE == bTsMedia)
    {
        printf("Open Ts file:%s\n", argv[u32TsFileID]);
        g_pTsFile = fopen(argv[u32TsFileID], "rb");
        if (!g_pTsFile)
        {
            printf("open file %s error no media found!\n", argv[u32TsFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bEsMedia)
    {
        printf("Open Es file:%s\n", argv[u32EsFileID]);
        g_pEsFile = fopen(argv[u32EsFileID], "rb");
        if (!g_pEsFile)
        {
            printf("open file %s error no media found!\n", argv[u32EsFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bEsAd)
    {
        printf("Open Es file:%s\n", argv[u32EsAdFileID]);
        g_pEsAdFile = fopen(argv[u32EsAdFileID], "rb");
        if (!g_pEsAdFile)
        {
            printf("open file %s error no media found!\n", argv[u32EsAdFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bTts)
    {
        printf("Open TTS file:%s\n", argv[u32TtsFileID]);
        g_pcmFile[TTS_INDEX] = fopen(argv[u32TtsFileID], "rb");
        if (!g_pcmFile[TTS_INDEX])
        {
            printf("open TTS file %s error!\n", argv[u32TtsFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bSystem)
    {
        printf("Open System file:%s\n", argv[u32SysFileID]);
        g_pcmFile[SYSTEM_INDEX] = fopen(argv[u32SysFileID], "rb");
        if (!g_pcmFile[SYSTEM_INDEX])
        {
            printf("open System file %s error!\n", argv[u32SysFileID]);
            return -1;
        }
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("open OTT file %s \n", argv[u32UIAudioFileID]);
        g_pcmFile[UIAUDIO_INDEX] = fopen(argv[u32UIAudioFileID], "rb");
        if (!g_pcmFile[UIAUDIO_INDEX])
        {
            printf("open OTT file %s error!\n", argv[u32UIAudioFileID]);
            return -1;
        }
    }

    System_init();
    HIADP_AVPlay_RegADecLib();

    if (HI_TRUE == bTsMedia)
    {
        printf("Creat TsMedia & thread\n");
        Create_TsMedia();
    }

    if (HI_TRUE == bEsMedia)
    {
        printf("Creat EsMedia & thread\n");
        Create_EsMedia(bEsAd);
    }

    if (HI_TRUE == bTts)
    {
        printf("Creat tts track & thread\n");
        Create_Tts_Track();
        g_bStopFlag[TTS_INDEX] = HI_FALSE;
        u32StreamId = TTS_INDEX;
        pthread_create(&g_hPcmThread[TTS_INDEX], HI_NULL, (HI_VOID*)PcmThread, (HI_VOID*)(&u32StreamId));
    }

    if (HI_TRUE == bSystem)
    {
        printf("Creat system track & thread\n");
        Create_Sys_Track();
        g_bStopFlag[SYSTEM_INDEX] = HI_FALSE;
        u32StreamId = SYSTEM_INDEX;
        pthread_create(&g_hPcmThread[SYSTEM_INDEX], HI_NULL, (HI_VOID*)PcmThread, (HI_VOID*)(&u32StreamId));
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("Creat ui audio track & thread\n");
        Create_Ott_Track();
        g_bStopFlag[UIAUDIO_INDEX] = HI_FALSE;
        u32StreamId = UIAUDIO_INDEX;
        pthread_create(&g_hPcmThread[UIAUDIO_INDEX], HI_NULL, (HI_VOID*)PcmThread, (HI_VOID*)(&u32StreamId));
    }

    while (1)
    {
        printf("please input 'q' to quit!\n");

        SAMPLE_GET_INPUTCMD(InputCmd);

        printf("InputCmd:%s\n", InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('d' == InputCmd[0])
        {
            if (HI_TRUE == bEsMedia)
            {
                printf("Destory EsMedia & thread\n");
                Destroy_EsMedia(bEsAd);
                bEsMedia = HI_FALSE;
            }

            if (HI_TRUE == bTsMedia)
            {
                printf("Destory TsMedia & thread\n");
                Destroy_TsMedia();
                bTsMedia = HI_FALSE;
            }
            continue;
        }

        if ('c' == InputCmd[0])
        {
            if (HI_FALSE == bEsMedia)
            {
                printf("Create EsMedia & thread\n");

                if ('m' == InputCmd[2] && 'p' == InputCmd[3] && '3' == InputCmd[4])
                {
                    if (g_pEsFile)
                    {
                        fclose(g_pEsFile);
                    }

                    printf("Open Es file:%s\n", "/mnt/atmos/loveyou_48K.mp3");
                    g_pEsFile = fopen("/mnt/atmos/loveyou_48K.mp3", "rb");
                    if (!g_pEsFile)
                    {
                        printf("open file %s error no media found!\n", "/mnt/atmos/loveyou_48K.mp3");
                        break;
                    }
                    g_enCodecID = HA_AUDIO_ID_MP3;
                }
                else if ('a' == InputCmd[2] && 'a' == InputCmd[3] && 'c' == InputCmd[4])
                {
                    if (g_pEsFile)
                    {
                        fclose(g_pEsFile);
                    }

                    printf("Open Es file:%s\n", "/mnt/atmos/mouse_love_rice.aac");
                    g_pEsFile = fopen("/mnt/atmos/mouse_love_rice.aac", "rb");
                    if (!g_pEsFile)
                    {
                        printf("open file %s error no media found!\n", "/mnt/atmos/mouse_love_rice.aac");
                        break;
                    }
                    g_enCodecID = HA_AUDIO_ID_MS12_AAC;
                }
                else if ('d' == InputCmd[2] && 'd' == InputCmd[3] && 'p' == InputCmd[4])
                {
                    if (g_pEsFile)
                    {
                        fclose(g_pEsFile);
                    }

                    printf("Open Es file:%s\n", "/mnt/atmos/afraic_48k.ac3");
                    g_pEsFile = fopen("/mnt/atmos/afraic_48k.ac3", "rb");
                    if (!g_pEsFile)
                    {
                        printf("open file %s error no media found!\n", "/mnt/atmos/afraic_48k.ac3");
                        break;
                    }
                    g_enCodecID = HA_AUDIO_ID_MS12_DDP;
                }

                Create_EsMedia(bEsAd);
                bEsMedia = HI_TRUE;
            }
            continue;
        }

        if ('p' == InputCmd[0])
        {
            if ('o' == InputCmd[1])
            {
                g_s32OttPlay = 0;
                printf("begin stop ott\n");
                continue;
            }

            if ('m' == InputCmd[1])
            {
                g_s32EsBufCnt = 0;
                printf("begin stop media\n");

                HI_UNF_AVPLAY_STOP_OPT_S  Stop;
                Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
                Stop.u32TimeoutMs = 0;

                HI_S32 s32Ret;
                s32Ret = HI_UNF_AVPLAY_Stop(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
                if (s32Ret != HI_SUCCESS)
                {
                    printf("stop AVPLAY failed.\n");
                }
                continue;
            }

            printf("do nothing\n");
            continue;
        }

        if ('r' == InputCmd[0])
        {
            if ('o' == InputCmd[1])
            {
                g_s32OttPlay = 1;
                printf("begin play ott\n");
                continue;
            }

            if ('m' == InputCmd[1])
            {
                g_s32EsBufCnt = 1;
                printf("begin play media\n");

                HI_S32 s32Ret;
                s32Ret = HI_UNF_AVPLAY_Start(g_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
                if (s32Ret != HI_SUCCESS)
                {
                    printf("restart AVPLAY failed.\n");
                }
                continue;
            }

            printf("do nothing\n");
            continue;
        }
    }

    if (HI_TRUE == bUIAudio)
    {
        printf("Destory ui audio track & thread\n");
        g_bStopFlag[UIAUDIO_INDEX] = HI_TRUE;
        pthread_join(g_hPcmThread[UIAUDIO_INDEX], HI_NULL);
        Destroy_Ott_Track();
    }

    if (HI_TRUE == bSystem)
    {
        printf("Destory system audio track & thread\n");
        g_bStopFlag[SYSTEM_INDEX] = HI_TRUE;
        pthread_join(g_hPcmThread[SYSTEM_INDEX], HI_NULL);
        Destroy_Sys_Track();
    }

    if (HI_TRUE == bTts)
    {
        printf("Destory tts audio track & thread\n");
        g_bStopFlag[TTS_INDEX] = HI_TRUE;
        pthread_join(g_hPcmThread[TTS_INDEX], HI_NULL);
        Destroy_Tts_Track();
    }

    if (HI_TRUE == bTsMedia)
    {
        printf("Destory TsMedia & thread\n");
        Destroy_TsMedia();
    }

    if (HI_TRUE == bEsMedia)
    {
        printf("Destory EsMedia & thread\n");
        Destroy_EsMedia(bEsAd);
    }

    System_Deinit();

    if (g_pTsFile)
    {
        fclose(g_pTsFile);
    }

    if (g_pEsFile)
    {
        fclose(g_pEsFile);
    }

    if (g_pcmFile[TTS_INDEX])
    {
        fclose(g_pcmFile[TTS_INDEX]);
    }

    if (g_pcmFile[UIAUDIO_INDEX])
    {
        fclose(g_pcmFile[UIAUDIO_INDEX]);
    }

    if (g_pcmFile[SYSTEM_INDEX])
    {
        fclose(g_pcmFile[SYSTEM_INDEX]);
    }

    return HI_SUCCESS;
}
