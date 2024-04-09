/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_hdmi_tsplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"


FILE               *g_pTsFile = HI_NULL;
static pthread_t   g_TsThd;
static pthread_mutex_t g_TsMutex;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
HI_HANDLE          g_TsBuf;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

extern HI_HANDLE               g_hWin;

#define  PLAY_DMX_ID  0

HI_VOID TsTthread(HI_VOID *args)
{
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, 188*50, &StreamBuf, 1000);
        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0)
        {
         //   printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Ret = HIADP_DMX_PushTsBuffer(g_TsBuf, &StreamBuf, 0, Readlen);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
        pthread_mutex_unlock(&g_TsMutex);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    return;
}
extern HI_U32 HDMI_Test_CMD(HI_CHAR * u8String);

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                  Ret;
    HI_HANDLE               hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    //when use cec cmd, we need longer cmd len
    HI_CHAR                 InputCmd[128];
    HI_UNF_ENC_FMT_E   enFormat = HI_UNF_ENC_FMT_720P_60;
    HI_U32             ProgNum;

    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;
    HI_SYS_VERSION_S            SysVersion;
    HI_CHIP_TYPE_E              ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E           ChipVersion = HI_CHIP_VERSION_BUTT;

    if (argc < 2)
    {
        printf("Usage: %s file [vo_format]\n", argv[0]);
        printf("\tvo_format: 2160P_30 | 2160P_24 | 1080P_60 | 1080P_50 | 1080i_60 | 1080i_50 | 720P_60 | 720P_50\n");
        printf("\t\t   480p_60 | 576P_50 | PAL | NTSC\n");
        printf("Example: %s ./test.ts 1080P_60\n", argv[0]);
        return 0;
    }

    if (argc >= 3)
    {

        enFormat = HIADP_Disp_StrToFmt(argv[2]);
    }

    printf("enFormat %s - [%d] \n", argv[2], enFormat);

    g_pTsFile = fopen(argv[1], "rb");
    if (!g_pTsFile)
    {
        printf("open file %s error!\n", argv[1]);
        return -1;
    }

    HI_SYS_Init();

    Ret = HI_SYS_GetVersion(&SysVersion);
    if (HI_SUCCESS == Ret)
    {
        ChipType    = SysVersion.enChipTypeHardWare;
        ChipVersion = SysVersion.enChipVersion;

        if (   ((HI_CHIP_TYPE_HI3798M == ChipType) && (HI_CHIP_VERSION_V100 == ChipVersion))
            || ((HI_CHIP_TYPE_HI3796M == ChipType) && (HI_CHIP_VERSION_V100 == ChipVersion)) )
        {
            system("echo volt=1140 > /proc/msp/pm_core");
        }
    }

    HIADP_MCE_Exit();

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call SndInit failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&g_hWin);
    if (HI_SUCCESS != Ret)
    {
        printf("call VoInit failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto VO_DEINIT;
    }

    Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    if (HI_SUCCESS != Ret)
    {
        printf("call RegADecLib failed.\n");
        goto TSBUF_FREE;
    }

    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.u32DemuxId = PLAY_DMX_ID;
    AvplayAttr.stStreamAttr.u32VidBufSize = (3*1024*1024);
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(g_hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",Ret);
    }
    Ret = HI_UNF_VO_SetWindowEnable(g_hWin, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    //stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_SND_Attach failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;
    pthread_create(&g_TsThd, HI_NULL, (HI_VOID *)TsTthread, HI_NULL);

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
    if (Ret != HI_SUCCESS)
    {
        printf("call HIADP_Search_GetAllPmt failed.\n");
        goto PSISI_FREE;
    }

#if 0
    printf("select channel number to start play\n");
    SAMPLE_GET_INPUTCMD(InputCmd);
    ProgNum = atoi(InputCmd);
#endif
    ProgNum = 0;

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

    Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    while(1)
    {

        //SAMPLE_GET_INPUTCMD(InputCmd);
        printf("please input 'h' to get help or 'q' to quit!\n");
        printf("hdmi_cmd >");
        memset(InputCmd, 0, 128);
        SAMPLE_GET_INPUTCMD(InputCmd);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        HDMI_Test_CMD(InputCmd);
        #if 0
        ProgNum = atoi(InputCmd);
        if (ProgNum == 0)
            ProgNum = 1;

        pthread_mutex_lock(&g_TsMutex);
        rewind(g_pTsFile);
        HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
        pthread_mutex_unlock(&g_TsMutex);
        Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum-1,HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            printf("call SwitchProgfailed!\n");
            break;
        }
        #endif
    }

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;
    HIADP_Search_DeInit();

    g_bStopTsThread = HI_TRUE;
    pthread_join(g_TsThd, HI_NULL);
    pthread_mutex_destroy(&g_TsMutex);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(g_hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(g_hWin, hAvplay);

    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSBUF_FREE:
    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(g_hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    if (   ((HI_CHIP_TYPE_HI3798M == ChipType) && (HI_CHIP_VERSION_V100 == ChipVersion))
        || ((HI_CHIP_TYPE_HI3796M == ChipType) && (HI_CHIP_VERSION_V100 == ChipVersion)) )
    {
        system("echo volt=0 > /proc/msp/pm_core");
    }

    HI_SYS_DeInit();

    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return Ret;
}


