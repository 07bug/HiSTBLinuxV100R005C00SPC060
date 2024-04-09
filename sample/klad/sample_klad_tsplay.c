/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_klad_tsplay.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-08-29
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#include "hi_unf_common.h"
#include "hi_unf_ecs.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_descrambler.h"
#include "hi_unf_klad.h"
#include "hi_unf_klad_common_ca.h"
#include "hi_unf_demux.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"
#include "parse_config_file.h"

#define WAKEUP_TEST 0

FILE               *g_pTsFile = HI_NULL;
static pthread_t   g_TsThd;
static pthread_mutex_t g_TsMutex;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
HI_HANDLE          g_TsBuf;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

HI_S32             g_CwType = 0;

HI_U32 g_KladType;
HI_UNF_KLAD_ALG_TYPE_E       g_kladAlg  = HI_UNF_KLAD_ALG_TYPE_BUTT;
HI_UNF_KLAD_TARGET_ENGINE_E  g_engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;

HI_U8 g_u8Session1[16] = {0};
HI_U8 g_u8SessionKey2[16] = {0};
HI_U8 g_u8SessionKey3[16] = {0};
HI_U8 g_u8SessionKey4[16] = {0};
HI_U8 g_u8EncrytedOddKey[16] = {0};
HI_U8 g_u8EncrytedEvenKey[16] = {0};
HI_U8 g_u8ClearOddKey[16] = {0};
HI_U8 g_u8ClearEvenKey[16] = {0};

#define  PLAY_DMX_ID  0
#if WAKEUP_TEST
HI_S32 TEST_PMOC(HI_U32 u32WakeUpTime,HI_U32 resetenable)
{
    HI_S32                        ret = HI_SUCCESS;
    HI_UNF_PMOC_WKUP_S wakeup = {0};
    HI_UNF_PMOC_ACTUAL_WKUP_E actual;

    ret = HI_UNF_PMOC_Init();
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_Init err, 0x%08x !\n", ret);
        return ret;
    }
    memset(&wakeup, 0, sizeof(HI_UNF_PMOC_WKUP_S));
    wakeup.u32WakeUpTime = u32WakeUpTime;
    wakeup.bResumeResetEnable=resetenable;
    ret = HI_UNF_PMOC_SetWakeUpAttr(&wakeup);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_SetWakeUpAttr err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }
    ret = HI_UNF_PMOC_SetScene(HI_UNF_PMOC_SCENE_STANDARD);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_SetScene err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }

    ret  = HI_UNF_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_SLOW, &actual);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_SwitchSystemMode err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }

    if (actual == HI_UNF_PMOC_WKUP_TIMEOUT)
    {
        printf("wakeup by timeout !!!\n");
    }

    HI_UNF_PMOC_DeInit();

    return HI_SUCCESS;

}
#endif

static HI_VOID printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if (NULL != string)
    {
        printf("%s\n", string);
    }

    for (i = 0 ; i < u32Length; i++)
    {
        if((i % 16 == 0) && (i != 0))
            printf("\n");

        printf("0x%02x ", pu8Input[i]);
    }

    printf("\n");

    return;
}

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
            printf("read ts file end and rewind!\n");
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

static HI_S32 setCw(HI_HANDLE hKlad,HI_HANDLE hKey)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_KLAD_LEVEL_E enStage = HI_UNF_KLAD_LEVEL3;
    HI_UNF_KLAD_ATTR_S stKladAttr = {0};
    HI_UNF_KLAD_SESSION_KEY_S sessionkey = {0};
    HI_UNF_KLAD_CONTENT_KEY_S OddContentkey = {0};
    HI_UNF_KLAD_CONTENT_KEY_S EvenContentkey = {0};

    stKladAttr.u32KladType= g_KladType;
    stKladAttr.enAlg = g_kladAlg;
    if(HI_UNF_KLAD_COMMON_CA_TYPE_CSA2 == g_KladType)
    {
        stKladAttr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA2;
    }
    else if(HI_UNF_KLAD_COMMON_CA_TYPE_CSA3 == g_KladType)
    {
        stKladAttr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA3;
    }
    else if(HI_UNF_KLAD_COMMON_CA_TYPE_MISC == g_KladType)
    {
        stKladAttr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_PAYLOAD_CSA2;
        enStage = HI_UNF_KLAD_LEVEL5;
    }

    printf("g_KladType is :0x%X\n", g_KladType);

    Ret = HI_UNF_KLAD_SetAttr(hKlad,&stKladAttr);
    if(Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_KLAD_SetAttr failed,ret = 0x%x\n",Ret);
        return Ret;
    }

    printf("keyladder level is :%d\n", enStage + 1);
    if (enStage >= HI_UNF_KLAD_LEVEL2)
    {
        get_key_value("SESSIONKEY1", g_u8Session1, 16);
        printBuffer("Sessionkey1:", g_u8Session1, 16);
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL1;
        memcpy(sessionkey.au8Key,g_u8Session1,16);
        Ret = HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_KLAD_SetSessionKey level1 failed,ret = 0x%x\n",Ret);
            return Ret;
        }
    }

    if (enStage >= HI_UNF_KLAD_LEVEL3)
    {
        get_key_value("SESSIONKEY2", g_u8SessionKey2, 16);
        printBuffer("Sessionkey2:", g_u8SessionKey2, 16);
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL2;
        memcpy(sessionkey.au8Key,g_u8SessionKey2,16);
        Ret |= HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_KLAD_SetSessionKey level2 failed,ret = 0x%x\n",Ret);
            return HI_FAILURE;
        }
    }

        if (enStage >= HI_UNF_KLAD_LEVEL4)
    {
        get_key_value("SESSIONKEY3", g_u8SessionKey3, 16);
        printBuffer("Sessionkey3:", g_u8SessionKey3, 16);
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL3;
        memcpy(sessionkey.au8Key,g_u8SessionKey3,16);
        Ret |= HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_KLAD_SetSessionKey level3 failed,ret = 0x%x\n",Ret);
            return HI_FAILURE;
        }
    }

    if (enStage >= HI_UNF_KLAD_LEVEL5)
    {
        get_key_value("SESSIONKEY4", g_u8SessionKey4, 16);
        printBuffer("Sessionkey4:", g_u8SessionKey4, 16);
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL4;
        memcpy(sessionkey.au8Key,g_u8SessionKey4,16);
        Ret |= HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_KLAD_SetSessionKey level4 failed,ret = 0x%x\n",Ret);
            return HI_FAILURE;
        }
    }

    get_key_value("ENCRYPTEDODDKEY", g_u8EncrytedOddKey, 16);
    get_key_value("ENCRYPTEDEVENKEY", g_u8EncrytedEvenKey, 16);

    printBuffer("Encrypted Odd key :", g_u8EncrytedOddKey, 16);
    printBuffer("Encrypted enen key:", g_u8EncrytedEvenKey, 16);

    OddContentkey.bOdd = 1;
    memcpy(OddContentkey.au8Key,g_u8EncrytedOddKey,16);

    EvenContentkey.bOdd = 0;
    memcpy(EvenContentkey.au8Key,g_u8EncrytedEvenKey,16);

    Ret = HI_UNF_KLAD_SetContentKey(hKlad,&OddContentkey);
    Ret |= HI_UNF_KLAD_SetContentKey(hKlad,&EvenContentkey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_SetContentKey failed,ret = 0x%x\n",Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#if !(defined(CHIP_TYPE_hi3716mv420) || defined(CHIP_TYPE_hi3716mv410))
static HI_S32 setClearCw(HI_HANDLE hKlad,HI_HANDLE hKey)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_KLAD_ATTR_S stKladAttr = {0};
    HI_UNF_KLAD_CONTENT_KEY_S OddContentkey = {0};
    HI_UNF_KLAD_CONTENT_KEY_S EvenContentkey = {0};

    stKladAttr.u32KladType= HI_UNF_KLAD_TYPE_CLEARCW;
    stKladAttr.enAlg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    stKladAttr.enEngine = g_engine;
    Ret = HI_UNF_KLAD_SetAttr(hKlad,&stKladAttr);
    if(Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_KLAD_SetAttr failed,ret = 0x%x\n",Ret);
        return Ret;
    }

    OddContentkey.bOdd = 1;
    memcpy(OddContentkey.au8Key,g_u8ClearOddKey,16);

    EvenContentkey.bOdd = 0;
    memcpy(EvenContentkey.au8Key,g_u8ClearEvenKey,16);

    Ret = HI_UNF_KLAD_SetContentKey(hKlad,&OddContentkey);
    Ret |= HI_UNF_KLAD_SetContentKey(hKlad,&EvenContentkey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_SetContentKey failed,ret = 0x%x\n",Ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif

HI_S32 AVPLAY_SetCW(HI_HANDLE hKlad,HI_HANDLE hKey)
{
    HI_S32 Ret = HI_SUCCESS;

    if (0 == g_CwType)
    {
        get_key_value("CLEARODDKEY", g_u8ClearOddKey, 8);
        get_key_value("CLEAREVENKEY", g_u8ClearEvenKey, 8);

        printBuffer("Clear Odd key :", g_u8ClearOddKey, 8);
        printBuffer("Clear Even key:", g_u8ClearEvenKey, 8);
    #if defined(CHIP_TYPE_hi3716mv420) ||defined(CHIP_TYPE_hi3716mv410)
        Ret = HI_UNF_DMX_SetDescramblerOddKey(hKey,g_u8ClearOddKey);
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(hKey,g_u8ClearEvenKey);
    #else
        Ret = setClearCw(hKlad,hKey);
    #endif
    }
    else
    {
        Ret = setCw(hKlad,hKey);
    }

    return Ret;
}

HI_S32 AVPLAY_AttachDescramble(HI_HANDLE hAvplay,HI_HANDLE *phKey)
{
    HI_S32 Ret;
    HI_UNF_DMX_DESCRAMBLER_ATTR_S stDesramblerAttr;
    HI_HANDLE hKey;
    HI_HANDLE hDmxVidChn,hDmxAudChn;

    memset(&stDesramblerAttr,0,sizeof(HI_UNF_DMX_DESCRAMBLER_ATTR_S));
    if (0 == g_CwType)
    {
        stDesramblerAttr.enCaType = HI_UNF_DMX_CA_NORMAL;
    }
    else
    {
        stDesramblerAttr.enCaType = HI_UNF_DMX_CA_ADVANCE;
    }

    if (HI_UNF_KLAD_COMMON_CA_TYPE_CSA2 == g_KladType)
    {
        stDesramblerAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
    }
    else if (HI_UNF_KLAD_COMMON_CA_TYPE_CSA3 == g_KladType)
    {
        stDesramblerAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3;
    }
    else if (HI_UNF_KLAD_COMMON_CA_TYPE_MISC == g_KladType)
    {
        stDesramblerAttr.enDescramblerType = HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2;
    }

    stDesramblerAttr.enEntropyReduction = HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE;
    Ret = HI_UNF_DMX_CreateDescramblerExt(0,&stDesramblerAttr,&hKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_CreateDescramblerExt failed %#x\n",Ret);
        return HI_FAILURE;
    }

    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hAvplay,&hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hAvplay,&hDmxAudChn);
    Ret = HI_UNF_DMX_AttachDescrambler(hKey,hDmxVidChn);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachDescrambler hDmxVidChn failed\n");
        (HI_VOID)HI_UNF_DMX_DestroyDescrambler(hKey);
        return HI_FAILURE;
    }

    Ret = HI_UNF_DMX_AttachDescrambler(hKey,hDmxAudChn);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachDescrambler hDmxAudChn failed\n");
        (HI_VOID)HI_UNF_DMX_DetachDescrambler(hKey,hDmxVidChn);
        (HI_VOID)HI_UNF_DMX_DestroyDescrambler(hKey);
        return HI_FAILURE;
    }
    *phKey = hKey;

    return HI_SUCCESS;
}

HI_S32 AVPLAY_DetachDescramble(HI_HANDLE hAvplay,HI_HANDLE hKey)
{
    HI_S32 Ret;
    HI_HANDLE hDmxVidChn,hDmxAudChn;

    Ret = HI_UNF_AVPLAY_GetDmxVidChnHandle(hAvplay,&hDmxVidChn);
    Ret |= HI_UNF_AVPLAY_GetDmxAudChnHandle(hAvplay,&hDmxAudChn);
    Ret |= HI_UNF_DMX_DetachDescrambler(hKey,hDmxVidChn);
    Ret |= HI_UNF_DMX_DetachDescrambler(hKey,hDmxAudChn);
    Ret |= HI_UNF_DMX_DestroyDescrambler(hKey);

    return Ret;
}


static HI_VOID show_usage(HI_VOID)
{
    printf("./sample_ca_tsplay configfilename tsfilename\n");
}

static HI_S32 get_cw_type()
{
    HI_CHAR *value = HI_NULL;

    value = get_config_var("ENCRYPTCW");
    if (HI_NULL == value)
    {
        return -1;
    }

    if (0 == strncmp(value, "NO", sizeof ("NO")))
    {
        g_CwType = 0;
        printf("clear cw selected\n");
        return 0;
    }

    if (0 == strncmp(value, "YES", sizeof ("YES")))
    {
        g_CwType = 1;
        printf("encrypt cw selected\n");
        return 0;
    }

    g_CwType = 0;
    printf("not set cw type, clear cw selected\n");

    return 0;
}

static HI_S32 readConfigFile(HI_CHAR *pFileName)
{
    HI_S32 s32ValueNum = 0;
    HI_S32 s32Ret = 0;

    s32ValueNum = parse_config_file(pFileName);
    if (0 == s32ValueNum || MAX_VAR_NUM < s32ValueNum)
    {
        return HI_FAILURE;
    }

    get_cw_type();

    s32Ret |= get_keyladder_type(&g_KladType);
    s32Ret |= get_keyladder_alg(&g_kladAlg);
    s32Ret |= get_keyladder_engine(&g_engine);
    if (s32Ret != 0)
    {
        printf("read config key failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_HANDLE                   hWin = HI_INVALID_HANDLE;
    HI_HANDLE                   hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                     InputCmd[32];
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32                      ProgNum;
    HI_HANDLE                   hKey;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;
    HI_HANDLE                   hKlad = HI_INVALID_HANDLE;
#if WAKEUP_TEST
    struct timeval              tv_start = {0};
    struct timeval              tv_end = {0};
    HI_BOOL                     standby = HI_TRUE;
    gettimeofday(&tv_start,0);
#endif
    if(argc < 3)
    {
        show_usage();
        return 0;
    }

    Ret = readConfigFile(argv[1]);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    enFormat = HI_UNF_ENC_FMT_1080i_50;

    g_pTsFile = fopen(argv[2], "rb");
    if (!g_pTsFile)
    {
        printf("open file %s error!\n", argv[1]);
        return -1;
    }

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HI_UNF_KLAD_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_Init failed\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
        goto CA_DEINIT;
    }

    Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_VO_Init failed.\n");
        goto DISP_DEINIT;
    }

    Ret = HIADP_VO_CreatWin(HI_NULL, &hWin);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_VO_CreatWin failed.\n");
        goto VO_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_Init failed.\n");
        goto VO_DEINIT;
    }

    Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,HI_UNF_DMX_PORT_RAM_0);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto DMX_DEINIT;
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

    Ret = AVPLAY_AttachDescramble(hAvplay,&hKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call AVPLAY_AttachDescramble failed.\n");
        goto ACHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",Ret);
        goto ACHN_CLOSE;
    }

    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
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

    ProgNum = 0;

    pthread_mutex_lock(&g_TsMutex);
    rewind(g_pTsFile);
    HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

    Ret = HI_UNF_KLAD_Create(&hKlad);
    if(Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_KLAD_Create failed,ret = 0x%x\n",Ret);
        goto KLAD_STOP;
    }
    Ret = HI_UNF_KLAD_Attach(hKlad,hKey);
    if(Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_KLAD_Attach failed,ret = 0x%x\n",Ret);
        goto KLAD_DETACH;
    }

    Ret = AVPLAY_SetCW(hKlad,hKey);
    if (Ret != HI_SUCCESS)
    {
        printf("call AVPLAY_SetCW failed. ret = 0x%x\n",Ret);
        goto KLAD_DETACH;
    }

    Ret |= HIADP_AVPlay_PlayProg(hAvplay, g_pProgTbl, ProgNum, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HIADP_AVPlay_PlayProg failed.\n");
        goto AVPLAY_STOP;
    }

    pthread_mutex_unlock(&g_TsMutex);

    while (1)
    {
        static HI_U32 u32TplaySpeed = 2;
        printf("please input 'q' to quit!\n");
        memset(InputCmd, 0, 30);
        (HI_VOID)fgets(InputCmd, 30, stdin);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('t' == InputCmd[0])
        {
            HI_UNF_AVPLAY_TPLAY_OPT_S stTplayOpt;
            printf("%dx tplay\n",u32TplaySpeed);

            stTplayOpt.enTplayDirect = HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD;
            stTplayOpt.u32SpeedInteger = u32TplaySpeed;
            stTplayOpt.u32SpeedDecimal = 0;

            HI_UNF_AVPLAY_SetDecodeMode(hAvplay, HI_UNF_VCODEC_MODE_I);
            HI_UNF_AVPLAY_Tplay(hAvplay,&stTplayOpt);
            u32TplaySpeed = (32 == u32TplaySpeed * 2) ? (2) : (u32TplaySpeed * 2) ;
            continue;
        }

        if ('r' == InputCmd[0])
        {
            printf("resume\n");
            HI_UNF_AVPLAY_SetDecodeMode(hAvplay, HI_UNF_VCODEC_MODE_NORMAL);
            HI_UNF_AVPLAY_Resume(hAvplay,HI_NULL);
            u32TplaySpeed = 2;
            continue;
        }

        if ('g' == InputCmd[0])
        {
            HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
            HI_UNF_AVPLAY_GetStatusInfo(hAvplay,&stStatusInfo);
            printf("localtime %u playtime %u\n",stStatusInfo.stSyncStatus.u32LocalTime,stStatusInfo.stSyncStatus.u32PlayTime);
            continue;
        }

        ProgNum = atoi(InputCmd);
        if (ProgNum == 0)
            ProgNum = 1;

        pthread_mutex_lock(&g_TsMutex);
        rewind(g_pTsFile);
        HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

        #if WAKEUP_TEST
        gettimeofday(&tv_end,0);
        printf("tv_start.tv_sec = %d!\n",(HI_U32)tv_start.tv_sec);
        printf("tv_end.tv_sec = %d!\n",(HI_U32)tv_end.tv_sec);
        if(((tv_end.tv_sec - tv_start.tv_sec) > 10) && standby)
        {
            TEST_PMOC(2,0);
            standby = HI_FALSE;
        }
        #endif
        Ret = AVPLAY_SetCW(hKlad,hKey);
        Ret |= HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum-1,HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            printf("call HIADP_AVPlay_PlayProg failed!\n");
            break;
        }

        pthread_mutex_unlock(&g_TsMutex);
    }

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

KLAD_DETACH:
    HI_UNF_KLAD_Detach(hKlad,hKey);

KLAD_STOP:
    HI_UNF_KLAD_Destroy(hKlad);

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
    HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

    AVPLAY_DetachDescramble(hAvplay,hKey);

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

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    if (HI_INVALID_HANDLE != hWin)
    {
        HI_UNF_VO_DestroyWindow(hWin);
    }
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

CA_DEINIT:
    HI_UNF_KLAD_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return Ret;
}


