/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : dvbplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : sdk
    Modification: Created file

******************************************************************************/
#include "sample_ms12.h"
#include "sample_ir.h"
#include "sample_osd.h"
#include "sample_play.h"
#include "sample_service.h"

static PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;


HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                      Ret = HI_SUCCESS;
    HI_HANDLE                   hWin;
    HI_HANDLE                   hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                     InputCmd[32];
    HI_U32                      ProgNum;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    TrackAttr;
    HI_U32                      Tuner = 0;
    HI_U32                      TunerFreq;
    HI_U32                      TunerSrate;
    HI_U32                      ThirdParam;
    HI_UNF_ENC_FMT_E            Format = HI_UNF_ENC_FMT_1080i_50;
    HI_BOOL                     bRepeat = HI_FALSE;
    SAMPLE_THREAD_INFO_S        stIrThreadInfo;
    HI_UNF_SND_GAIN_ATTR_S      stGain = {HI_TRUE, 10};

    if (argc < 2)
    {
        printf("Usage: %s [freq] [srate] [qamtype or polarization] [vo_format] [tuner]\n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50  default HI_UNF_ENC_FMT_1080i_50\n"
                "       Tuner: value can be 0, 1, 2, 3\n"
                "       muxAudNum: 0 - 32",
                argv[0]);

        printf("Example: %s 618 6875 64 1080i_50 0 32\n", argv[0]);
        return HI_FAILURE;
    }

    TunerFreq  = strtol(argv[1], NULL, 0);
    TunerSrate = (TunerFreq > 1000) ? 27500 : 6875;
    ThirdParam = (TunerFreq > 1000) ? 0 : 64;

    switch(argc)
    {
        case 6:
            Tuner = strtol(argv[5], NULL, 0);
        case 5:
            Format = HIADP_Disp_StrToFmt(argv[4]);
        case 4:
            ThirdParam = strtol(argv[3], NULL, 0);
        case 3:
            TunerSrate = strtol(argv[2], NULL, 0);
            break;
        default:
            sample_printf("Invalid argc(%d)!\n", argc);
            break;
    }

    SAMPLE_DOFUNC_RETURN(HI_SYS_Init(), Ret);
    SAMPLE_DOFUNC_GOTO(Sample_Ir_Init(), Ret, SYS_DEINIT);
    SAMPLE_DOFUNC_GOTO(Sample_Ir_RegKeyProcessFn(Sample_Service_ProcessKeys), Ret, IR_DEINIT);
    stIrThreadInfo.bExitFlag = HI_FALSE;
    pthread_create(&stIrThreadInfo.threadID, HI_NULL, Sample_Ir_ProcessRoutine, &stIrThreadInfo);
    SAMPLE_DOFUNC_NO_RETURN(HIADP_MCE_Exit(), Ret);
    SAMPLE_DOFUNC_GOTO(HIADP_Snd_Init(), Ret, OSD_DEINIT);
    SAMPLE_DOFUNC_GOTO(HIADP_Disp_Init(Format), Ret, SND_DEINIT);
    SAMPLE_DOFUNC_GOTO(Sample_Osd_Init(), Ret, DISP_DEINIT);
    SAMPLE_DOFUNC_GOTO(HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL), Ret, OSD_DEINIT);
    SAMPLE_DOFUNC_GOTO(HIADP_VO_CreatWin(HI_NULL,&hWin), Ret, VO_DEINIT);
    SAMPLE_DOFUNC_GOTO(HI_UNF_DMX_Init(), Ret, WIN_DEINIT);
    SAMPLE_DOFUNC_GOTO(HIADP_DMX_AttachTSPort(0, Tuner), Ret, WIN_DEINIT);
    SAMPLE_DOFUNC_GOTO(HIADP_Tuner_Init(), Ret, DMX_DEINIT);
    SAMPLE_DOFUNC_NO_RETURN(Sample_Play_RegisterCallBack(Sample_Osd_AC4Display), Ret);
REPEAT_SEARCH:
    SAMPLE_DOFUNC_GOTO(Sample_Service_GetFreqParams(&Tuner, &TunerFreq, &TunerSrate, &ThirdParam, bRepeat), Ret, REPEAT_SEARCH);
    bRepeat = HI_TRUE;
    SAMPLE_DOFUNC_GOTO(HIADP_Tuner_Connect(Tuner, TunerFreq, TunerSrate, ThirdParam), Ret, REPEAT_SEARCH);
    HIADP_Search_Init();
    SAMPLE_DOFUNC_GOTO(HIADP_Search_GetAllPmt(0,&g_pProgTbl), Ret, REPEAT_SEARCH);
    bRepeat = HI_FALSE;
    SAMPLE_DOFUNC_NO_RETURN(HIADP_AVPlay_RegADecLib(), Ret);
    SAMPLE_DOFUNC_GOTO(HI_UNF_AVPLAY_Init(), Ret, PSISI_FREE);
    SAMPLE_DOFUNC_NO_RETURN(HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS), Ret);
    AvplayAttr.u32DemuxId = 0;
    SAMPLE_DOFUNC_GOTO(HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay), Ret, AVPLAY_DEINIT);
    SAMPLE_DOFUNC_GOTO(HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL), Ret, CHN_CLOSE);
    SAMPLE_DOFUNC_GOTO(HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL), Ret, CHN_CLOSE);

    SAMPLE_DOFUNC_GOTO(HI_UNF_VO_AttachWindow(hWin, hAvplay), Ret, CHN_CLOSE);
    SAMPLE_DOFUNC_GOTO(HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE), Ret, WIN_DETACH);
    SAMPLE_DOFUNC_GOTO(HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &TrackAttr), Ret, WIN_DETACH);
    SAMPLE_DOFUNC_GOTO(HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &TrackAttr, &hTrack), Ret, WIN_DETACH);
    SAMPLE_DOFUNC_GOTO(HI_UNF_SND_Attach(hTrack, hAvplay), Ret, TRACK_DESTROY);

    SAMPLE_DOFUNC_NO_RETURN(HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr), Ret);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_PCR;
    SyncAttr.stSyncStartRegion.s32VidPlusTime = 30;
    SyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
    SyncAttr.bQuickOutput = HI_FALSE;
    SyncAttr.s32VidPtsAdjust = 300;
    SyncAttr.s32AudPtsAdjust = 300;

    SAMPLE_DOFUNC_GOTO(HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr), Ret, SND_DETACH);

    SAMPLE_DOFUNC_GOTO(Sample_Play_SaveProgInfo(g_pProgTbl, hAvplay), Ret, SND_DETACH);
    SAMPLE_DOFUNC_GOTO(Sample_Play_PlayByIdx(0), Ret, AVPLAY_STOP);

    HI_UNF_SND_SetVolume(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, &stGain);

    while(1)
    {
#ifdef HI_ADVCA_FUNCTION_RELEASE
        sleep(1);
        continue;
#endif
        printf("please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('i' == InputCmd[0])
        {
            stGain.s32Gain += 5;
            stGain.s32Gain = (stGain.s32Gain > 100) ? 100 : stGain.s32Gain;
            HI_UNF_SND_SetVolume(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &stGain);
            continue;
        }

        if ('b' == InputCmd[0])
        {
            static HI_U32 u32Delayms = 0;

            HI_UNF_SND_SetDelayCompensationMs(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, u32Delayms);
            printf("set spdif delay compensation (%dms)!\n", u32Delayms);

            u32Delayms += 100;
            u32Delayms = (u32Delayms > 500) ? 0 : u32Delayms;

            continue;
        }

        if ('e' == InputCmd[0])
        {
            static HI_U32 u32Delayms = 0;

            HI_UNF_SND_SetDelayCompensationMs(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, u32Delayms);
            printf("set hdmi delay compensation (%dms)!\n", u32Delayms);

            u32Delayms += 100;
            u32Delayms = (u32Delayms > 500) ? 0 : u32Delayms;

            continue;
        }

        if ('s' == InputCmd[0])
        {
            static int spdif_toggle = 0;
            spdif_toggle++;

            if (spdif_toggle & 1)
            {
                HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_RAW);
                printf("spdif pass-through on!\n");
            }
            else
            {
                HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_LPCM);
                printf("spdif pass-through off!\n");
            }
            continue;
        }

        if ('h' == InputCmd[0])
        {
            static int hdmi_toggle = 0;
            hdmi_toggle++;

            if (hdmi_toggle & 1)
            {
                HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
                printf("hmdi pass-through on!\n");
            }
            else
            {
                HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_LPCM);
                printf("hmdi pass-through off!\n");
            }
            continue;
        }

        if ('d' == InputCmd[0])
        {
            stGain.s32Gain -= 5;
            stGain.s32Gain = (stGain.s32Gain < 0) ? 0 : stGain.s32Gain;
            HI_UNF_SND_SetVolume(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &stGain);
            continue;
        }

        if ('r' == InputCmd[0])
        {
            static int mode = 0;
            HA_MS12_SET_DRC_MODE_S stDrcMode;
            memset(&stDrcMode, 0, sizeof(HA_MS12_SET_DRC_MODE_S));

            stDrcMode.enCmd = HA_CODEC_MS12_SET_DRC_MODE_CMD;
            stDrcMode.enDrcMode = (MS12_DRC_MODE_E)(mode % 2);
            mode++;
            HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stDrcMode));
            printf(">>>>enDrcMode=%d\n", stDrcMode.enDrcMode);
            continue;
        }

        if ('l' == InputCmd[0])
        {
            static HI_U32 scale = 100;
            HA_MS12_SET_DRC_SCALE_S stDrcScale;
            memset(&stDrcScale, 0, sizeof(HA_MS12_SET_DRC_SCALE_S));

            stDrcScale.enCmd = HA_CODEC_MS12_SET_DRC_SCALE_CMD;
            stDrcScale.u32DrcCut = scale;
            stDrcScale.u32DrcBoost = scale;
            scale = (0 == scale) ? 100 : (scale - 50);
            HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stDrcScale));
            printf(">>>>u32DrcScale=%d\n", stDrcScale.u32DrcCut);
            continue;
        }

        if ('m' == InputCmd[0])
        {
            static HI_U32 dualmono = 0;
            HA_MS12_SET_DUAL_MODE_S stDualMode;
            memset(&stDualMode, 0, sizeof(HA_MS12_SET_DUAL_MODE_S));

            stDualMode.enCmd = HA_CODEC_MS12_SET_DUAL_MODE_CMD;
            stDualMode.enDualMode = (MS12_DUAL_MODE_E)(dualmono % 3);
            dualmono++;
            HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stDualMode));
            printf(">>>>enDualMode=%d\n", stDualMode.enDualMode);
            continue;
        }

        if ('g' == InputCmd[0])
        {
            HA_MS12_GET_STREAM_INFO_S stStreamInfo;
            memset(&stStreamInfo, 0, sizeof(HA_MS12_GET_STREAM_INFO_S));

            stStreamInfo.enCmd = HA_CODEC_MS12_GET_STREAM_INFO_CMD;

            HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stStreamInfo));
            printf(">>>>MAIN: bLfeExist=%d, enStreamType=%d, u32Acmod=%d, u32BitRate=%d, u32SampleRate=%d\n",
                stStreamInfo.bLfeExist,
                stStreamInfo.enStreamType,
                stStreamInfo.u32Acmod,
                stStreamInfo.u32BitRate,
                stStreamInfo.u32SampleRate);
            continue;
        }

        if ('a' == InputCmd[0])
        {
            HA_MS12_GET_STREAM_INFO_S stStreamInfo;
            memset(&stStreamInfo, 0, sizeof(HA_MS12_GET_STREAM_INFO_S));

            stStreamInfo.enCmd = HA_CODEC_MS12_GET_AD_STREAM_INFO_CMD;

            HI_UNF_AVPLAY_Invoke(hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stStreamInfo));
            printf(">>>>ASSC: bLfeExist=%d, enStreamType=%d, u32Acmod=%d, u32BitRate=%d, u32SampleRate=%d\n",
                stStreamInfo.bLfeExist,
                stStreamInfo.enStreamType,
                stStreamInfo.u32Acmod,
                stStreamInfo.u32BitRate,
                stStreamInfo.u32SampleRate);
            continue;
        }

        if ('c' == InputCmd[0])
        {
            SAMPLE_DOFUNC_NO_RETURN(Sample_Play_PlayAudioNext(), Ret);
            continue;
        }

        ProgNum = (0 == atoi(InputCmd)) ? 1 : atoi(InputCmd);
        SAMPLE_DOFUNC_GOTO(Sample_Play_PlayByIdx(ProgNum), Ret, AVPLAY_STOP);
    }

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);
TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);
WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);
CHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    HI_UNF_AVPLAY_Destroy(hAvplay);
AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();
PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    HIADP_Search_DeInit();
    HIADP_Tuner_DeInit();
DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();
WIN_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
VO_DEINIT:
    HIADP_VO_DeInit();
OSD_DEINIT:
    Sample_Osd_DeInit();
DISP_DEINIT:
    HIADP_Disp_DeInit();
SND_DEINIT:
    HIADP_Snd_DeInit();
IR_DEINIT:
    stIrThreadInfo.bExitFlag = HI_TRUE;
    Sample_Ir_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();

    return Ret;
}
