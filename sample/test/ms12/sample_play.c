#include "sample_ms12.h"
#include "sample_play.h"

static SAMPLE_AC4_PROCESS_FB g_AC4CallBack = HI_NULL;
typedef struct tagSAMPLE_PROG_INFO_S
{
    HI_BOOL bPlay;
    HI_HANDLE hAvplay;
    HI_U32 u32TotalProg;
    HI_U32 u32CurProgIdx;
    HI_U32 u32CurAudIdx;
    HI_U32 u32ADLevel;
    PMT_COMPACT_PROG stProg[SAMPLE_MAX_PROG_NUM];
}SAMPLE_PROG_INFO_S;

SAMPLE_PROG_INFO_S s_stProgInfo =
{
    .u32TotalProg = 0,
    .bPlay = HI_FALSE,
};

#define SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(prognum)\
    do{\
        if (0 == (prognum)){\
            sample_printf("no progam!\n");\
            return HI_FAILURE;\
        }\
    }while(0)
#define SAMPLE_PLAY_CHECK_NO_PLAY_RETURN()\
    do{\
        if (HI_TRUE != s_stProgInfo.bPlay)\
        {\
            sample_printf("no progamis played!\n");\
            return HI_FAILURE;\
        }\
    }while(0)

static HI_VOID DefalutOpenParam(HI_UNF_ACODEC_ATTR_S *pstAttr)
{
    if (HA_AUDIO_ID_MP2 == pstAttr->enType)
    {
        HA_MP2_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam));
    }
#if 0
    else if (HA_AUDIO_ID_AAC == pstAttr->enType)
    {
        HA_AAC_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam));
    }
#endif
    else if (HA_AUDIO_ID_MP3 == pstAttr->enType)
    {
        HA_MP3_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam));
    }
    else if (HA_AUDIO_ID_DTSHD == pstAttr->enType)
    {
        static DTSHD_DECODE_OPENCONFIG_S DtsConfig = {0};
        HA_DTSHD_DecGetDefalutOpenConfig(&DtsConfig);
        HA_DTSHD_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam), &DtsConfig);
        pstAttr->stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;
    }
#if 0
#ifdef DOLBYPLUS_HACODEC_SUPPORT
    else if (HA_AUDIO_ID_DOLBY_PLUS == pstAttr->enType)
    {
        static DOLBYPLUS_DECODE_OPENCONFIG_S DolbyConfig = {0};
        HA_DOLBYPLUS_DecGetDefalutOpenConfig(&DolbyConfig);
        /* Dolby DVB Broadcast default settings */
        DolbyConfig.enDrcMode = DOLBYPLUS_DRC_RF;
        DolbyConfig.enDmxMode = DOLBYPLUS_DMX_SRND;
        HA_DOLBYPLUS_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam), &DolbyConfig);
        pstAttr->stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;
    }
#endif
#endif
 else if (HA_AUDIO_ID_TRUEHD == pstAttr->enType)
    {
        HA_TRUEHD_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam));
        pstAttr->stDecodeParam.enDecMode = HD_DEC_MODE_THRU;        /* truehd just support pass-through */
        sample_printf(" TrueHD decoder(HBR Pass-through only).\n");
    }
    else if (HA_AUDIO_ID_DOLBY_TRUEHD == pstAttr->enType)
    {
        static TRUEHD_DECODE_OPENCONFIG_S DolbyTrueHDConfig = {0};
        HA_DOLBY_TRUEHD_DecGetDefalutOpenConfig(&DolbyTrueHDConfig);
        HA_DOLBY_TRUEHD_DecGetDefalutOpenParam(&(pstAttr->stDecodeParam), &DolbyTrueHDConfig);
    }
    else if (HA_AUDIO_ID_DOLBY_PLUS == pstAttr->enType)
    {
        static DOLBYMS12_CODEC_OPENCONFIG_S stMs12Cfg;

        pstAttr->enType = HA_AUDIO_ID_MS12_DDP;
        HA_DOLBYMS12_CodecGetDefaultOpenConfig(&stMs12Cfg);
        stMs12Cfg.enInputType = MS12_DOLBY_DIGITAL_PLUS;
        HA_DOLBYMS12_CodecGetDefaultOpenParam(&(pstAttr->stDecodeParam), &stMs12Cfg);
    }
    else if (HA_AUDIO_ID_AAC == pstAttr->enType)
    {
        static DOLBYMS12_CODEC_OPENCONFIG_S stMs12Cfg;

        pstAttr->enType = HA_AUDIO_ID_MS12_AAC;
        HA_DOLBYMS12_CodecGetDefaultOpenConfig(&stMs12Cfg);
        stMs12Cfg.enInputType = MS12_HEAAC;
        HA_DOLBYMS12_CodecGetDefaultOpenParam(&(pstAttr->stDecodeParam), &stMs12Cfg);
    }

    return;
}

#define AUDIO_MAX_TRACK_NUM 12

typedef struct
{
     HI_U32                          AudPid[AUDIO_MAX_TRACK_NUM];
     HI_UNF_ACODEC_ATTR_S            AudAttr[AUDIO_MAX_TRACK_NUM];
     HI_U32                          AudTrackNum;
     HI_U8                           AudLang[AUDIO_MAX_TRACK_NUM][3];
}AUD_INFO_S;

HI_S32 SamplePlayProg(HI_U32 ProgNum)
{
    HI_S32                   Ret;
    HI_U32                   PcrPid;
    HI_S32                   i, j, k;
    AUD_INFO_S               AudInfo;
    AUD_INFO_S               AudAdInfo;
    HI_UNF_AVPLAY_STOP_OPT_S Stop;
    HI_BOOL bAC4AudioPlay = HI_TRUE;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

    j = 0;
    k = 0;
    memset(&AudInfo, 0, sizeof(AUD_INFO_S));
    memset(&AudAdInfo, 0, sizeof(AUD_INFO_S));

    for (i = 0; i < s_stProgInfo.stProg[ProgNum].AElementNum; i++)
    {
        /*Main Audio*/
        if (1 != s_stProgInfo.stProg[ProgNum].Audioinfo[i].u16ADType)
        {
            AudInfo.AudAttr[j].enType = s_stProgInfo.stProg[ProgNum].Audioinfo[i].u32AudioEncType;
            DefalutOpenParam(&AudInfo.AudAttr[j]);
            AudInfo.AudPid[j] = (HI_U32)(s_stProgInfo.stProg[ProgNum].Audioinfo[i].u16AudioPid);
            memcpy((HI_CHAR*)&AudInfo.AudLang[j][0], (HI_CHAR*)s_stProgInfo.stProg[ProgNum].Audioinfo[i].u8AudLang, 3);
            j++;
        }
        /*Audio Description*/
        else
        {
            AudAdInfo.AudAttr[k].enType = s_stProgInfo.stProg[ProgNum].Audioinfo[i].u32AudioEncType;
            DefalutOpenParam(&AudAdInfo.AudAttr[k]);
            AudAdInfo.AudPid[k] = (HI_U32)(s_stProgInfo.stProg[ProgNum].Audioinfo[i].u16AudioPid);
            memcpy((HI_CHAR*)&AudAdInfo.AudLang[k][0], (HI_CHAR*)s_stProgInfo.stProg[ProgNum].Audioinfo[i].u8AudLang, 3);
            k++;
        }
    }

    AudInfo.AudTrackNum = j;
    AudAdInfo.AudTrackNum = k;

    printf("Main Audio[%d]\n", j);
    for (i = 0; i < AudInfo.AudTrackNum; i++)
    {
        printf("Aud[%d] Pid:0x%x Language: 0x%x 0x%x 0x%x\n", i,
               AudInfo.AudPid[i], AudInfo.AudLang[i][0], AudInfo.AudLang[i][1], AudInfo.AudLang[i][2]);
    }

    printf("Assoc Audio[%d]\n", k);
    for (i = 0; i < AudAdInfo.AudTrackNum; i++)
    {
        printf("Aud[%d] Pid:0x%x Language: 0x%x 0x%x 0x%x\n", i,
               AudAdInfo.AudPid[i], AudAdInfo.AudLang[i][0], AudAdInfo.AudLang[i][1], AudAdInfo.AudLang[i][2]);
    }

    if (0 == AudAdInfo.AudTrackNum)
    {
        HI_UNF_AVPLAY_AD_ATTR_S AdAttr;

        memset(&AdAttr, 0, sizeof(HI_UNF_AVPLAY_AD_ATTR_S));

        AdAttr.bAdEnble = HI_FALSE;
        HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_AD, &AdAttr);
    }

    HI_U32 AudTrackIndex = 0;
    HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_ADEC, &AudInfo.AudAttr[AudTrackIndex]);
    HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &AudInfo.AudPid[AudTrackIndex]);

    printf("main aud 0x%x pid\n", AudInfo.AudPid[AudTrackIndex]);

    /*Get AD Audio based on Main Audio Information*/
    for (i = 0; i < AudAdInfo.AudTrackNum; i++)
    {
        if (!strncmp((HI_CHAR*)AudInfo.AudLang[AudTrackIndex], (HI_CHAR*)AudAdInfo.AudLang[i], 3))
        {
            printf("ad aud 0x%x pid\n", AudAdInfo.AudPid[i]);
            HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_AD_PID, &AudAdInfo.AudPid[i]);
        }
    }

    HIADP_AVPlay_SetVdecAttr(s_stProgInfo.hAvplay, s_stProgInfo.stProg[ProgNum].VideoType, HI_UNF_VCODEC_MODE_NORMAL);
    HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &s_stProgInfo.stProg[ProgNum].VElementPid);
    printf("Vid pid 0x%x\n", s_stProgInfo.stProg[ProgNum].VElementPid);

    PcrPid = s_stProgInfo.stProg[ProgNum].PcrPid;
    if (INVALID_TSPID != PcrPid)
    {
        HI_UNF_SYNC_ATTR_S  SyncAttr;

        Ret = HI_UNF_AVPLAY_GetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("HI_UNF_AVPLAY_GetAttr Sync failed 0x%x\n", Ret);
            return HI_FAILURE;
        }

        if (HI_UNF_SYNC_REF_PCR == SyncAttr.enSyncRef)
        {
            Ret = HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &PcrPid);
            if (HI_SUCCESS != Ret)
            {
                printf("HI_UNF_AVPLAY_SetAttr Sync failed 0x%x\n", Ret);
                return HI_SUCCESS;
            }
        }
    }

    HI_UNF_AVPLAY_Start(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    HI_UNF_AVPLAY_Start(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);

    s_stProgInfo.u32CurProgIdx = ProgNum;
    s_stProgInfo.bPlay = HI_TRUE;
    s_stProgInfo.u32CurAudIdx = 0;

    if (s_stProgInfo.stProg[0].AudioType != HA_AUDIO_ID_MS12_AC4)
    {
        bAC4AudioPlay = HI_FALSE;
    }

    if (HI_NULL != g_AC4CallBack)
    {
        g_AC4CallBack(bAC4AudioPlay);
    }

    return HI_SUCCESS;
}

HI_S32 SamplePlayAudio(HI_BOOL bNext)
{
    HI_U32 u32AudPid = 0x1ff;
    HI_U32 u32AudIdx = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    PMT_COMPACT_PROG *pstProgInfo = HI_NULL;

    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);
    if (HI_TRUE != s_stProgInfo.bPlay)
    {
        return HI_FAILURE;
    }

    u32AudIdx = s_stProgInfo.u32CurAudIdx;
    pstProgInfo = &s_stProgInfo.stProg[s_stProgInfo.u32CurProgIdx];
    if (HI_TRUE == bNext)
    {
        u32AudIdx = (u32AudIdx + 1)%pstProgInfo->AElementNum;
        if (SAMPLE_MAX_AUDIO_NUM <= u32AudIdx)
            u32AudIdx = 0;
    }
    else
    {
        u32AudIdx = (0 == u32AudIdx) ? (pstProgInfo->AElementNum - 1) : (u32AudIdx - 1);
        if (SAMPLE_MAX_AUDIO_NUM <= u32AudIdx)
            u32AudIdx = SAMPLE_MAX_AUDIO_NUM - 1;
    }
    u32AudPid = pstProgInfo->Audioinfo[u32AudIdx].u16AudioPid;
    SAMPLE_DOFUNC_RETURN(HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &u32AudPid), s32Ret);
    s_stProgInfo.u32CurAudIdx = u32AudIdx;
    return HI_SUCCESS;
}

HI_S32 Sample_Play_SaveProgInfo(PMT_COMPACT_TBL *pstProgInfo, HI_HANDLE hAvplay)
{
    HI_U32 i = 0;

    SAMPLE_CHECK_POINTER_RETURN(pstProgInfo);
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(pstProgInfo->prog_num);

    memset(&s_stProgInfo, 0x00, sizeof(s_stProgInfo));

    s_stProgInfo.u32TotalProg = pstProgInfo->prog_num;
    if (SAMPLE_MAX_PROG_NUM < s_stProgInfo.u32TotalProg)
    {
        sample_printf("prog num(%d) is more than %d\n", s_stProgInfo.u32TotalProg, SAMPLE_MAX_PROG_NUM);
        s_stProgInfo.u32TotalProg = SAMPLE_MAX_PROG_NUM;
    }

    for (i = 0; i < s_stProgInfo.u32TotalProg; i++)
    {
        memcpy(&s_stProgInfo.stProg[i], &pstProgInfo->proginfo[i], sizeof(PMT_COMPACT_PROG));
        s_stProgInfo.u32CurProgIdx = 0;
    }

    s_stProgInfo.bPlay = HI_FALSE;
    s_stProgInfo.hAvplay = hAvplay;

    return HI_SUCCESS;
}

HI_S32 Sample_Play_PlayByIdx(HI_U32 u32Idx)
{
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);

    u32Idx = u32Idx%s_stProgInfo.u32TotalProg;
    return SamplePlayProg(u32Idx);
}

HI_S32 Sample_Play_PlayByProg(PMT_COMPACT_PROG *pstProg)
{
    HI_U32 i = 0;
    SAMPLE_CHECK_POINTER_RETURN(pstProg);
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);
    for (i = 0; i < s_stProgInfo.u32TotalProg; i++)
    {
        if ((pstProg->VideoType == s_stProgInfo.stProg[i].VideoType)
            || (pstProg->VElementPid == s_stProgInfo.stProg[i].VElementPid))
        {
            break;
        }
    }

    if (i >= s_stProgInfo.u32TotalProg)
    {
        sample_printf("can't find the prog(0x%x)!\n", pstProg->VElementPid);
        return HI_FAILURE;
    }
    return SamplePlayProg(i);
}

HI_S32 Sample_Play_PlayPrev(HI_VOID)
{
    HI_U32 u32Idx = s_stProgInfo.u32CurProgIdx;
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();

    u32Idx = (0 == u32Idx) ? (s_stProgInfo.u32TotalProg - 1) : (u32Idx - 1);
    u32Idx = u32Idx%s_stProgInfo.u32TotalProg;
    return SamplePlayProg(u32Idx);
}

HI_S32 Sample_Play_PlayNext(HI_VOID)
{
    HI_U32 u32Idx = s_stProgInfo.u32CurProgIdx + 1;
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();

    u32Idx = u32Idx%s_stProgInfo.u32TotalProg;
    return SamplePlayProg(u32Idx);
}

HI_S32 Sample_Play_PlayAudioNext(HI_VOID)
{
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();
    return SamplePlayAudio(HI_TRUE);
}

HI_S32 Sample_Play_PlayAudioPrev(HI_VOID)
{
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();
    return SamplePlayAudio(HI_FALSE);
}

HI_S32 Sample_Play_GetPlayAudio(HI_U32 *pu32Idx, HI_U32 *pu32ADLevel)
{
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();
    SAMPLE_CHECK_POINTER_RETURN(pu32Idx);
    SAMPLE_CHECK_POINTER_RETURN(pu32ADLevel);
    *pu32Idx = s_stProgInfo.u32CurAudIdx;
    *pu32ADLevel = s_stProgInfo.u32ADLevel;
    return HI_SUCCESS;
}

HI_S32 Sample_Play_GetAudioInfo(SAMPLE_OSD_AUDIO_INFO_S* pstAudInfo)
{
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();

    memset(&pstAudInfo->stStreamInfo, 0, sizeof(HA_MS12_GET_STREAM_INFO_S));

    pstAudInfo->stStreamInfo.enCmd = HA_CODEC_MS12_GET_STREAM_INFO_CMD;

    (HI_VOID)HI_UNF_AVPLAY_Invoke(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&pstAudInfo->stStreamInfo));

    return HI_SUCCESS;
}

HI_S32 Sample_Play_SetPlayAudio(HI_U32 u32Idx)
{
    int j = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 AudPid[SAMPLE_MAX_AUDIO_NUM] = {0};
    PMT_COMPACT_TBL stProgInfo;

    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();

    if (HI_TRUE == s_stProgInfo.bPlay)
    {
        SAMPLE_DOFUNC_NO_RETURN(HI_UNF_AVPLAY_Stop(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL), s32Ret);
        s_stProgInfo.bPlay = HI_FALSE;
    }

    memset(&stProgInfo, 0x00, sizeof(stProgInfo));
    stProgInfo.prog_num = 1;
    stProgInfo.proginfo = &s_stProgInfo.stProg[s_stProgInfo.u32CurProgIdx];

    for (j = 0; j < stProgInfo.proginfo->AElementNum; j++)
    {
        AudPid[j] = (HI_U32)(stProgInfo.proginfo->Audioinfo[j].u16AudioPid);

        if ((1 == stProgInfo.proginfo->Audioinfo[j].u16ADType) &&
            (!strncmp((HI_CHAR*)stProgInfo.proginfo->Audioinfo[u32Idx].u8AudLang, (HI_CHAR*)stProgInfo.proginfo->Audioinfo[j].u8AudLang, 3)))
        {
           SAMPLE_DOFUNC_NO_RETURN(HI_UNF_AVPLAY_SetAttr(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_ATTR_ID_AD_PID, &AudPid[j]), s32Ret);
           break;
        }
    }

    SAMPLE_DOFUNC_NO_RETURN(HIADP_AVPlay_PlayProg_MS12(s_stProgInfo.hAvplay, &stProgInfo, u32Idx), s32Ret);

    s_stProgInfo.bPlay = HI_TRUE;
    s_stProgInfo.u32CurAudIdx = u32Idx;

    return HI_SUCCESS;
}

HI_S32 Sample_Play_SetAudioBalance(HI_U32 u32ADLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HA_MS12_SET_AD_BALANCE_S stAdBalance;

    memset(&stAdBalance, 0, sizeof(HA_MS12_SET_AD_BALANCE_S));

    stAdBalance.enCmd = HA_CODEC_MS12_SET_AD_BALANCE_CMD;

    switch (u32ADLevel)
    {
        case 0:
            stAdBalance.s32Balance = -32;
            break;
        case 1:
            stAdBalance.s32Balance = -12;
            break;
        case 2:
            stAdBalance.s32Balance = 0;
            break;
        case 3:
            stAdBalance.s32Balance = 32;
            break;
        default:
            break;
    }

    SAMPLE_DOFUNC_NO_RETURN(HI_UNF_AVPLAY_Invoke(s_stProgInfo.hAvplay, HI_UNF_AVPLAY_INVOKE_ACODEC, (HI_VOID*)(&stAdBalance)), s32Ret);

    s_stProgInfo.u32ADLevel = u32ADLevel;

    return HI_SUCCESS;
}

HI_S32 Sample_Play_GetAudioNum(HI_U32 *pu32AudNum)
{
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();
    SAMPLE_CHECK_POINTER_RETURN(pu32AudNum);
    *pu32AudNum = s_stProgInfo.stProg[s_stProgInfo.u32CurProgIdx].AElementNum;
    return HI_SUCCESS;
}

HI_S32 Sample_Play_GetProgNum(HI_U32 *pu32ProgNum)
{
    SAMPLE_CHECK_POINTER_RETURN(pu32ProgNum);
    *pu32ProgNum = s_stProgInfo.u32TotalProg;
    return HI_SUCCESS;
}

HI_S32 Sample_Play_GetCurPlayProg(HI_U32 *pu32ProgNum)
{
    SAMPLE_CHECK_POINTER_RETURN(pu32ProgNum);
    SAMPLE_PLAY_CHECK_NO_PLAY_RETURN();
    *pu32ProgNum = s_stProgInfo.u32CurProgIdx;
    return HI_SUCCESS;
}
HI_S32 Sample_Play_RegisterCallBack(SAMPLE_AC4_PROCESS_FB pCallBack)
{
    g_AC4CallBack = pCallBack;
    return HI_SUCCESS;
}
HI_S32 Sample_Play_UnRegisterCallBack(HI_VOID)
{
    g_AC4CallBack = HI_NULL;
    return HI_SUCCESS;
}

HI_S32 Sample_Play_GetProgInfoByIdx(HI_U32 u32Idx, PMT_COMPACT_PROG *pstProg)
{
    SAMPLE_CHECK_POINTER_RETURN(pstProg);
    SAMPLE_PLAY_CHECK_PROG_NUM_RETURN(s_stProgInfo.u32TotalProg);
    if (u32Idx >= s_stProgInfo.u32TotalProg)
    {
        sample_printf("only has (%d) program, input is (%d)!\n", s_stProgInfo.u32TotalProg, u32Idx);
        return HI_FAILURE;
    }

    memcpy(pstProg, &s_stProgInfo.stProg[u32Idx], sizeof(PMT_COMPACT_PROG));
    return HI_SUCCESS;
}
