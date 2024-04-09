/*****************************************************************************
*              Copyright 2004 - 2016, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: render_proc.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01
*
*****************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <dlfcn.h>

#include "hi_error_mpi.h"
#include "hi_drv_ao.h"

#include "engine_sink.h"
#include "render_common.h"
#include "render_buffer.h"
#include "render_proc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


#define RENDER_PROCESS_TIMEOUT     (27)
#define SINK_PROCESS_TIMEOUT       (30)
#define PROC_RENDER_MAXNUM         (6)
#define PROC_RENDER_NAME_LEN       (128)
#define PROC_DECODER_NAME_LEN      (128)
#define PROC_RENDER_NODE_NAME      "render0"
#define PROC_CODEC_NODE_NAME       "render_codec0"
#define PROC_RENDER_DIR_NAME       "msp"
#define PROC_RENDER_ABSOLUTE_PATH  "/proc/msp/render0"

#define FIRST_IDX                  (0)
#define SECOND_IDX                 (1)
#define THIRD_IDX                  (2)
#define MAX_MS12_LOG_LEVEL         (5)

typedef struct
{
    HI_CHAR* pCmd;
    HI_VOID (*func) (HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData);
} RENDER_WRITE_PROC_S;

static HI_U32 ProcTimeProbe(STATISTICS_CMD_E enCmd)
{
    HI_U32 u32CurTime = 0;
    static HI_U32 u32StatTime;

    CHANNEL_TRACE();

    HI_SYS_GetTimeStampMs(&u32CurTime);

    if (STATISTICS_START == enCmd)
    {
        u32StatTime = u32CurTime;
        return 0;
    }

    return u32CurTime - u32StatTime;
}

HI_VOID ShowHelpInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    HI_PROC_Printf(pstBuf, "-----------------------------------Render HELP-------------------------------------------------------------------------\n");
    HI_PROC_Printf(pstBuf, "echo  log_ms12                                       [0/1/2/3/4]                                   >  /proc/msp/render0\n");
    HI_PROC_Printf(pstBuf, "echo  dump_ms12                                      [0/1]                                         >  /proc/msp/render0\n");
    HI_PROC_Printf(pstBuf, "echo  dump_section_ms12                              [0/1]                                         >  /proc/msp/render0\n");
    HI_PROC_Printf(pstBuf, "-----------------------------------------------------------------------------------------------------------------------\n");
}

static HI_VOID SetDecDebugLevel(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;
    HI_CHAR* pcOneCmd = "0";
    HI_S32   s32DebugLevel = 0;

    if (u32Argc < 2)
    {
        return;
    }

    s32DebugLevel = pu8Argv[1][0] - pcOneCmd[0];

    if ((s32DebugLevel > MAX_MS12_LOG_LEVEL) || (s32DebugLevel < 0))
    {
        return;
    }

    pstRender->pstEngineManger->pstCodec->pstMs12Proc->stProc.u32DebugLevel = s32DebugLevel;

    HI_ERR_AO("[DEBUG INFO] Command: %s %d\n", (HI_CHAR*)pu8Argv[0], s32DebugLevel);
}

static HI_VOID DumpMs12File(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    HI_U32 u32EnableFlag;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;

    if (u32Argc < 2)
    {
        return;
    }

    u32EnableFlag = strtoul((HI_CHAR*)pu8Argv[1], HI_NULL, 10);
    if (u32EnableFlag >= 2)
    {
        HI_ERR_AO("Invalid argv[1] u32EnableFlag(%d)\n", u32EnableFlag);
        return;
    }

    HI_ERR_AO("[DEBUG INFO] Command: DumpMs12File %d\n", u32EnableFlag);

    pstRender->pstEngineManger->pstCodec->pstMs12Proc->stProc.bDumpFile = (0 == u32EnableFlag) ? HI_FALSE : HI_TRUE;
}

static HI_VOID DumpMs12SectionFile(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    HI_U32 u32EnableFlag;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;

    if (u32Argc < 2)
    {
        return;
    }

    u32EnableFlag = strtoul((HI_CHAR*)pu8Argv[1], HI_NULL, 10);
    if (u32EnableFlag >= 2)
    {
        HI_ERR_AO("Invalid argv[1] u32EnableFlag(%d)\n", u32EnableFlag);
        return;
    }

    HI_ERR_AO("[DEBUG INFO] Command: DumpMs12SectionFile %d\n", u32EnableFlag);

    pstRender->pstEngineManger->pstCodec->pstMs12Proc->stProc.bDumpSectionFile = (0 == u32EnableFlag) ? HI_FALSE : HI_TRUE;
}

static HI_VOID ShowSourceInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_CHAR aszBuf[25], astBuf[25];
    SOURCE_ID_E enSourceID;
    SOURCE_S* pstSource;
    SOURCE_S* pstMSource;
    SOURCE_S* pstASource;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;
    SOURCE_MANAGER_S* pstSourceManager = pstRender->pstSourceManager;
    HI_CHAR* ppSourceName[] = {"Main", "Assoc", "EXT Audio", "OTT Sound", "System", "App"};
    HI_CHAR* ppSourceStatus[] = {"Idle", "Running", "Pause", "Stop", "Unknown"};

    HI_PROC_Printf(pstBuf, "______________________________Source______________________________\n");
    HI_PROC_Printf(pstBuf, "%32s                  %s", ppSourceName[SOURCE_ID_MAIN], ppSourceName[SOURCE_ID_ASSOC]);

    HI_PROC_Printf(pstBuf, "\nStatus                   :");
    pstMSource = pstSourceManager->pstSource[SOURCE_ID_MAIN];
    if (HI_NULL != pstMSource)
    {
        HI_PROC_Printf(pstBuf, "%-20s | ", ppSourceStatus[pstMSource->enState]);
    }
    pstASource = pstSourceManager->pstSource[SOURCE_ID_ASSOC];
    if (HI_NULL != pstASource)
    {
        HI_PROC_Printf(pstBuf, "%s", ppSourceStatus[pstASource->enState]);
    }

    HI_PROC_Printf(pstBuf, "\nInBuf(Total/Use/Percent) :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d/%d%%", pstMSource->u32InBufSize, pstMSource->u32InBufUsed, pstMSource->u32InBufUsedPercent);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d/%d%%", pstASource->u32InBufSize, pstASource->u32InBufUsed, pstASource->u32InBufUsedPercent);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

#if 0
    HI_PROC_Printf(pstBuf, "\nGetBuf(Try/Ok)           :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstMSource->u32GetBufTryCnt, pstMSource->u32GetBufOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstASource->u32GetBufTryCnt, pstASource->u32GetBufOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\nPutBuf(Try/Ok)           :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstMSource->u32PutBufTryCnt, pstMSource->u32PutBufOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstASource->u32PutBufTryCnt, pstASource->u32PutBufOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\nSendStream(Try/Ok)       :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstMSource->u32SendStreamTryCnt, pstMSource->u32SendStreamOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstASource->u32SendStreamTryCnt, pstASource->u32SendStreamOkCnt);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }
#endif

    HI_PROC_Printf(pstBuf, "\nPts                      :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", (HI_FALSE == pstMSource->bSinkStarted) ? pstMSource->u32CurStreamPts :
                 (pstMSource->u32SinkPts - pstMSource->u32DelayMs));
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", (HI_FALSE == pstASource->bSinkStarted) ? pstASource->u32CurStreamPts :
                 (pstASource->u32SinkPts - pstASource->u32DelayMs));
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\nDecStreamPts             :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", pstMSource->u32CurStreamPts);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", pstASource->u32CurStreamPts);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\nSinkPts/DelayMs          :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstMSource->u32SinkPts, pstMSource->u32DelayMs);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstASource->u32SinkPts, pstASource->u32DelayMs);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\nTargetPts                :");
    if (HI_NULL != pstMSource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", pstMSource->u32TargetPts);
        HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    }
    if (HI_NULL != pstASource)
    {
        snprintf(aszBuf, sizeof(aszBuf), "%d", pstASource->u32TargetPts);
        HI_PROC_Printf(pstBuf, "%-20s", aszBuf);
    }

    HI_PROC_Printf(pstBuf, "\n\n            Status       |SendData(Try/Ok)     | InBuf(Total/Use/Percent)\n");

    for (enSourceID = SOURCE_ID_EXTDEC; enSourceID <= SOURCE_ID_APP; enSourceID++)
    {
        HI_PROC_Printf(pstBuf, "%-10s: ", ppSourceName[enSourceID]);
        pstSource = pstSourceManager->pstSource[enSourceID];
        if (HI_NULL == pstSource)
        {
            HI_PROC_Printf(pstBuf, "\n");
            continue;
        }

        snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstSource->u32SendTrackDataTryCnt, pstSource->u32SendTrackDataOkCnt);
        snprintf(astBuf, sizeof(astBuf), "%d/%d/%d%%", pstSource->u32InBufSize, pstSource->u32InBufUsed, pstSource->u32InBufUsedPercent);
        HI_PROC_Printf(pstBuf, "%-10s   |%-20s | %-20s\n", ppSourceStatus[pstSource->enState], aszBuf, astBuf);
    }
}

static HI_VOID ShowRenderInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;
    ENGINE_MANAGER_S* pstEngineManger = pstRender->pstEngineManger;

    HI_PROC_Printf(pstBuf, "\n------------------------  Audio Render Info  -------------------------\n");

    ShowSourceInfo(pstBuf, pPrivData);

    HI_PROC_Printf(pstBuf, "\n______________________________Engine______________________________\n");
    HI_PROC_Printf(pstBuf, "RendTimeout              :%d\n", pstEngineManger->u32RenderTimeOutCnt);
    HI_PROC_Printf(pstBuf, "SinkTimeOut              :%d\n", pstEngineManger->u32SinkTimeOutCnt);
}

static HI_VOID ShowRenderDecoderInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_CHAR aszBuf[25];
    HA_MS12_PROC_S* pstMs12Proc;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;
    ENGINE_MANAGER_S* pstEngineManger = pstRender->pstEngineManger;
    MS12_STREAM_PROC_S* pstStreamProc;
    HI_CHAR* ppChnName[] = {"Main", "Assoc"};
    HI_CHAR* ppStreamTypeName[] = {"Dolby Digtal", "Dolby Digtal Plus", "Dolby Atmos", "AAC", "Dolby AC4", "PCM"};

    pstMs12Proc = &(pstEngineManger->pstCodec->pstMs12Proc->stProc);
    pstStreamProc = &(pstMs12Proc->stStreamProc[0]);

    HI_PROC_Printf(pstBuf, "______________________________Decoder______________________________\n");
    HI_PROC_Printf(pstBuf, "%32s                  %s\n", ppChnName[FIRST_IDX], ppChnName[SECOND_IDX]);

    if ((pstStreamProc[FIRST_IDX].enStreamType < 6) && (pstStreamProc[SECOND_IDX].enStreamType < 6))
    {
        HI_PROC_Printf(pstBuf, "StreamType               :%-20s | %-20s\n", ppStreamTypeName[pstStreamProc[FIRST_IDX].enStreamType],
                       ppStreamTypeName[pstStreamProc[SECOND_IDX].enStreamType]);
    }

    HI_PROC_Printf(pstBuf, "Dec(Ok/Err)              :");
    snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstStreamProc[FIRST_IDX].u32DecodeOkCnt, pstStreamProc[FIRST_IDX].u32DecodeErrCnt);
    HI_PROC_Printf(pstBuf, "%-20s | ", aszBuf);
    snprintf(aszBuf, sizeof(aszBuf), "%d/%d", pstStreamProc[SECOND_IDX].u32DecodeOkCnt, pstStreamProc[SECOND_IDX].u32DecodeErrCnt);
    HI_PROC_Printf(pstBuf, "%-20s", aszBuf);

    HI_PROC_Printf(pstBuf, "\nDec(UnderRun)            :%-20d | %-20d\n", pstStreamProc[FIRST_IDX].u32NotEnoughCnt, pstStreamProc[SECOND_IDX].u32NotEnoughCnt);
    HI_PROC_Printf(pstBuf, "----------------------------------------------------------------------\n");
}

static HI_S32 ProcShowRenderInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_S32 s32Ret;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;

    s32Ret = PROC_TRYLOCK();
    if (HI_SUCCESS != s32Ret)
    {
        return HI_SUCCESS;
    }

    if (HI_FALSE == pstRender->bProcInited)
    {
        PROC_UNLOCK();
        return HI_SUCCESS;
    }

    ShowRenderInfo(pstBuf, pPrivData);
    ShowRenderDecoderInfo(pstBuf, pPrivData);

    PROC_UNLOCK();

    return HI_SUCCESS;
}

static HI_S32 ProcSetCmd(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_U32 u32Argc, HI_U8* pu8Argv[], HI_VOID* pPrivData)
{
    HI_U32 u32CmdId;
    HI_CHAR* pcCMD = (HI_CHAR*)(pu8Argv[0]);

    RENDER_WRITE_PROC_S stWritePoc[] =
    {
        {"help", ShowHelpInfo},
        {"log_ms12", SetDecDebugLevel},
        {"dump_ms12", DumpMs12File},
        {"dump_section_ms12", DumpMs12SectionFile}
    };

    if (u32Argc < 1)
    {
        HI_ERR_AO("Invalid argc(%d)\n", u32Argc);
        return HI_FAILURE;
    }

    for (u32CmdId = 0; u32CmdId < sizeof(stWritePoc) / sizeof(stWritePoc[0]); u32CmdId++)
    {
        if (pcCMD == strstr(pcCMD, stWritePoc[u32CmdId].pCmd))
        {
            stWritePoc[u32CmdId].func(pstBuf, u32Argc, pu8Argv, pPrivData);
            break;
        }
    }

    return HI_SUCCESS;
}

static HI_VOID ShowCodecInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_CHAR aszBuf1[25];
    HI_CHAR aszBuf2[25];
    HA_MS12_PROC_S* pstMs12Proc;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;
    ENGINE_MANAGER_S* pstEngineManger = pstRender->pstEngineManger;
    MS12_STREAM_PROC_S* pstStreamProc;
    MS12_MIXER_PROC_S* pstMixerProc;
    HI_CHAR* ppProductConfig[] = {"MS11", "MS12(B)", "MS12(D)"};
    HI_CHAR* ppSupportHeaac[] = {"NO_HEAAC", "HEAAC"};
    HI_CHAR* ppChnName[] = {"Main", "Assoc", "Ott"};
    HI_CHAR* ppMix2InputName[] = {"Media", "Tts", "System"};
    HI_CHAR* ppStreamTypeName[] = {"Dolby Digtal", "Dolby Digtal Plus", "Dolby Atmos", "AAC", "Dolby AC4", "PCM"};
    HI_CHAR* ppDmxMode[] = {"Lt/Rt", "Lo/Ro", "ARIB"};
    HI_CHAR* ppDrcMode[] = {"Line", "RF"};
    HI_CHAR* ppLfeMode[] = {"Off", "On"};

    pstMs12Proc = &(pstEngineManger->pstCodec->pstMs12Proc->stProc);
    pstStreamProc = &(pstMs12Proc->stStreamProc[0]);
    pstMixerProc = &(pstMs12Proc->stMixerProc[0]);

    HI_PROC_Printf(pstBuf, "\n------------------------  Render Codec Info  -------------------------\n");

    if (HI_NULL != pstEngineManger->pstCodec->pEntry)
    {
        HI_PROC_Printf(pstBuf, "DecoderName    : %s\n", pstEngineManger->pstCodec->pEntry->szName);
        HI_PROC_Printf(pstBuf, "Description    : %s\n", pstEngineManger->pstCodec->pEntry->pszDescription);
    }

    if (pstMs12Proc->enConfig < 3)
    {
        HI_PROC_Printf(pstBuf, "Product Config : %s %s\n\n", ppProductConfig[pstMs12Proc->enConfig], ppSupportHeaac[pstMs12Proc->bSupportHeaac]);
    }

    HI_PROC_Printf(pstBuf, "Codec Settings :\n");

    HI_PROC_Printf(pstBuf, " DmxMode:%-6s| DrcMode:%-11s| DrcCut:%-11d | DrcBoost:%-6d\n",
        (pstMs12Proc->stCodecConfig.enDmxMode <= 2 ? ppDmxMode[pstMs12Proc->stCodecConfig.enDmxMode] : "UnKown"),
        (pstMs12Proc->stCodecConfig.enDrcMode <= 1 ? ppDrcMode[pstMs12Proc->stCodecConfig.enDrcMode] : "UnKown"),
        pstMs12Proc->stCodecConfig.u32DrcCut, pstMs12Proc->stCodecConfig.u32DrcBoost);

    HI_PROC_Printf(pstBuf, " LfeOut: %-6s| ADBalance:%-6d\n",
        (pstMs12Proc->stCodecConfig.enLfeOutMode <= 1 ? ppLfeMode[pstMs12Proc->stCodecConfig.enLfeOutMode] : "UnKown"),
        pstMs12Proc->stCodecConfig.s32AdBalance);

    HI_PROC_Printf(pstBuf, "\n______________________________Decoder______________________________\n");
    HI_PROC_Printf(pstBuf, "                 %-8s        %8s       \n", ppChnName[FIRST_IDX], ppChnName[SECOND_IDX]);

    if ((pstStreamProc[FIRST_IDX].enStreamType < 6) && (pstStreamProc[SECOND_IDX].enStreamType < 6))
    {
        HI_PROC_Printf(pstBuf, "StreamType     : %-18s | %-18s\n", ppStreamTypeName[pstStreamProc[FIRST_IDX].enStreamType], ppStreamTypeName[pstStreamProc[SECOND_IDX].enStreamType]);
    }

    HI_PROC_Printf(pstBuf, "DecInBufBytes  : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32DecodeInBufBytes, pstStreamProc[SECOND_IDX].u32DecodeInBufBytes);

    HI_PROC_Printf(pstBuf, "Dec(Try/Ok)    : ");
    snprintf(aszBuf1, sizeof(aszBuf1), "%d/%d", pstStreamProc[FIRST_IDX].u32DecodeTryCnt, pstStreamProc[FIRST_IDX].u32DecodeOkCnt);
    snprintf(aszBuf2, sizeof(aszBuf2), "%d/%d", pstStreamProc[SECOND_IDX].u32DecodeTryCnt,pstStreamProc[SECOND_IDX].u32DecodeOkCnt);
    HI_PROC_Printf(pstBuf, "%-18s | %-18s |\n", aszBuf1, aszBuf2);

    HI_PROC_Printf(pstBuf, "DecUnderRun    : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32NotEnoughCnt, pstStreamProc[SECOND_IDX].u32NotEnoughCnt);
    HI_PROC_Printf(pstBuf, "DecErr         : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32DecodeErrCnt, pstStreamProc[SECOND_IDX].u32DecodeErrCnt);
    HI_PROC_Printf(pstBuf, "BytesLeft      : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32StreamLeftBytes, pstStreamProc[SECOND_IDX].u32StreamLeftBytes);

    HI_PROC_Printf(pstBuf, "Acmod          : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32Acmod, pstStreamProc[SECOND_IDX].u32Acmod);
    HI_PROC_Printf(pstBuf, "LfeExit        : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].bLfeExist, pstStreamProc[SECOND_IDX].bLfeExist);
    HI_PROC_Printf(pstBuf, "SampleRate     : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32SampleRate, pstStreamProc[SECOND_IDX].u32SampleRate);
    HI_PROC_Printf(pstBuf, "BitRate        : %-18d | %-18d |\n", pstStreamProc[FIRST_IDX].u32BitRate, pstStreamProc[SECOND_IDX].u32BitRate);

    HI_PROC_Printf(pstBuf, "______________________________MIXER 1______________________________\n");
    HI_PROC_Printf(pstBuf, "                 %-18s %-18s   %-18s\n", ppChnName[FIRST_IDX], ppChnName[SECOND_IDX], ppChnName[THIRD_IDX]);
    HI_PROC_Printf(pstBuf, "Mix1InBufBytes : %-18d | %-18d | %-18d\n", pstMixerProc[FIRST_IDX].u32InBufBytes[FIRST_IDX],pstMixerProc[FIRST_IDX].u32InBufBytes[SECOND_IDX],
                                                                       pstMixerProc[FIRST_IDX].u32InBufBytes[THIRD_IDX]);

    HI_PROC_Printf(pstBuf, "Mix1(Try/Ok)   : ");
    snprintf(aszBuf1, sizeof(aszBuf1), "%d/%d", pstMixerProc[FIRST_IDX].u32TryCnt, pstMixerProc[FIRST_IDX].u32OkCnt);
    HI_PROC_Printf(pstBuf, "%-18s | %-18s | %-18s\n", aszBuf1, aszBuf1, aszBuf1);

    HI_PROC_Printf(pstBuf, "Mix1UnderRun   : %-18d | %-18d | %-18d\n", pstMixerProc[FIRST_IDX].u32PriUnderRunCnt, pstMixerProc[FIRST_IDX].u32SecUnderRunCnt,
                                                                             pstMixerProc[FIRST_IDX].u32ThirdUnderRunCnt);

    HI_PROC_Printf(pstBuf, "______________________________MIXER 2______________________________\n");
    HI_PROC_Printf(pstBuf, "                 %-18s %-18s   %-18s\n", ppMix2InputName[FIRST_IDX], ppMix2InputName[SECOND_IDX], ppMix2InputName[THIRD_IDX]);
    HI_PROC_Printf(pstBuf, "Mix2InBufBytes : %-18d | %-18d | %-18d\n", pstMixerProc[SECOND_IDX].u32InBufBytes[FIRST_IDX], pstMixerProc[SECOND_IDX].u32InBufBytes[SECOND_IDX],
                                                                       pstMixerProc[SECOND_IDX].u32InBufBytes[THIRD_IDX]);

    HI_PROC_Printf(pstBuf, "Mix2(Try/Ok)   : ");
    snprintf(aszBuf1, sizeof(aszBuf1), "%d/%d", pstMixerProc[SECOND_IDX].u32TryCnt, pstMixerProc[SECOND_IDX].u32OkCnt);
    HI_PROC_Printf(pstBuf, "%-18s | %-18s | %-18s\n", aszBuf1, aszBuf1, aszBuf1);

    HI_PROC_Printf(pstBuf, "Mix2UnderRun   : %-18d | %-18d | %-18d\n", pstMixerProc[SECOND_IDX].u32PriUnderRunCnt, pstMixerProc[SECOND_IDX].u32SecUnderRunCnt,
                                                                             pstMixerProc[SECOND_IDX].u32ThirdUnderRunCnt);

    HI_PROC_Printf(pstBuf, "___________________________OUTPUT STATUS___________________________\n");
    HI_PROC_Printf(pstBuf, "AtmosOutput    : %-18s\n", (HI_TRUE == pstMs12Proc->bAtmosOutput) ? "True" : "False");

    HI_PROC_Printf(pstBuf, "\n----------------------------------------------------------------------\n");
}

static HI_S32 ProcShowCodecInfo(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_S32 s32Ret;
    RENDER_MANAGER_S* pstRender = (RENDER_MANAGER_S*)pPrivData;

    s32Ret = PROC_TRYLOCK();
    if (HI_SUCCESS != s32Ret)
    {
        return HI_SUCCESS;
    }

    if (HI_FALSE == pstRender->bProcInited)
    {
        PROC_UNLOCK();
        return HI_SUCCESS;
    }

    ShowCodecInfo(pstBuf, pPrivData);

    PROC_UNLOCK();

    return HI_SUCCESS;
}

static HI_S32 ProcFindAvalidIndex(HI_U32* pu32Index)
{
    HI_U32 u32Index;
    HI_CHAR aPathName[18] = {0};

    CHANNEL_TRACE();

    strncpy(aPathName, PROC_RENDER_ABSOLUTE_PATH, sizeof(aPathName));

    for (u32Index = 0; u32Index < PROC_RENDER_MAXNUM; u32Index++)
    {
        aPathName[16] = u32Index + '0';        /*16 means render(X)*/

        if (0 != access(aPathName, F_OK))
        {
            *pu32Index = u32Index;
            return HI_SUCCESS;
        }
    }

    HI_ERR_AO("Too much msp render proc failed\n");

    return HI_FAILURE;
}

HI_S32 Proc_Init(RENDER_MANAGER_S* pstRender)
{
    HI_S32   s32Ret;
    HI_U32   u32ProcIndex;
    HI_CHAR* aProcRenderName = HI_NULL;
    HI_CHAR* aProcDecoderName = HI_NULL;

    CHANNEL_TRACE();

    aProcRenderName = (HI_CHAR*)malloc(PROC_RENDER_NAME_LEN);
    if (HI_NULL == aProcRenderName)
    {
        HI_ERR_AO("Malloc aProcRenderName failed.\n");
        return HI_FAILURE;
    }
    memset(aProcRenderName, 0, PROC_RENDER_NAME_LEN);
    strncpy(aProcRenderName, PROC_RENDER_NODE_NAME, PROC_RENDER_NAME_LEN);

    aProcDecoderName = (HI_CHAR*)malloc(PROC_DECODER_NAME_LEN);
    if (HI_NULL == aProcDecoderName)
    {
        free(aProcRenderName);
        HI_ERR_AO("Malloc aProcDecoderName failed.\n");
        return HI_FAILURE;
    }
    memset(aProcDecoderName, 0, PROC_DECODER_NAME_LEN);
    strncpy(aProcDecoderName, PROC_CODEC_NODE_NAME, PROC_DECODER_NAME_LEN);

    s32Ret = ProcFindAvalidIndex(&u32ProcIndex);
    if (HI_SUCCESS != s32Ret)
    {
        free(aProcRenderName);
        free(aProcDecoderName);
        HI_ERR_AO("ProcFindAvalidIndex failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    aProcRenderName[6] += u32ProcIndex;            /*6 means render(X)*/
    aProcDecoderName[11] += u32ProcIndex;          /*11 means render_codec(X)*/

    pstRender->stRenderProcEntry.pszDirectory = PROC_RENDER_DIR_NAME;
    pstRender->stRenderProcEntry.pszEntryName = aProcRenderName;
    pstRender->stRenderProcEntry.pfnShowProc  = ProcShowRenderInfo;
    pstRender->stRenderProcEntry.pfnCmdProc   = ProcSetCmd;
    pstRender->stRenderProcEntry.pPrivData    = pstRender;

    pstRender->stCodecProcEntry.pszDirectory = PROC_RENDER_DIR_NAME;
    pstRender->stCodecProcEntry.pszEntryName = aProcDecoderName;
    pstRender->stCodecProcEntry.pfnShowProc  = ProcShowCodecInfo;
    pstRender->stCodecProcEntry.pPrivData    = pstRender;

    memset(&(pstRender->stDumpManager), 0, sizeof(DUMP_MANAGER_S));

    s32Ret = HI_PROC_AddEntry(HI_ID_AO, &pstRender->stRenderProcEntry);
    if (HI_SUCCESS != s32Ret)
    {
        free(aProcRenderName);
        free(aProcDecoderName);
        HI_ERR_AO("HI_PROC_AddEntry failed(0x%x)\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret = HI_PROC_AddEntry(HI_ID_AO, &pstRender->stCodecProcEntry);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PROC_RemoveEntry(HI_ID_AO, &pstRender->stRenderProcEntry);
        free(aProcRenderName);
        free(aProcDecoderName);
        HI_ERR_AO("HI_PROC_AddEntry failed(0x%x)\n", s32Ret);
        return HI_FAILURE;
    }

    pstRender->bProcInited = HI_TRUE;

    return s32Ret;
}

HI_VOID Proc_DeInit(RENDER_MANAGER_S* pstRender)
{
    CHANNEL_TRACE();

    if (HI_TRUE == pstRender->bProcInited)
    {
        HI_PROC_RemoveEntry(HI_ID_AO, &pstRender->stRenderProcEntry);
        HI_PROC_RemoveEntry(HI_ID_AO, &pstRender->stCodecProcEntry);

        free(pstRender->stRenderProcEntry.pszEntryName);
        free(pstRender->stCodecProcEntry.pszEntryName);
        pstRender->stRenderProcEntry.pszEntryName = HI_NULL;
        pstRender->stCodecProcEntry.pszEntryName = HI_NULL;

        pstRender->bProcInited = HI_FALSE;
    }
}

HI_VOID Proc_Source(SOURCE_S* pstSource)
{
    CHANNEL_TRACE();

    (HI_VOID)RENDER_ServerBuffer_Enquire(pstSource->pRBuffer, &pstSource->u32InBufUsed, &pstSource->u32InBufSize);

    if (0 != pstSource->u32InBufSize)
    {
        pstSource->u32InBufUsedPercent = pstSource->u32InBufUsed * 100 / pstSource->u32InBufSize;
    }
}

HI_VOID Proc_Engine(ENGINE_MANAGER_S* pstEngine, STATISTICS_CMD_E enCmd)
{
    HI_U32 u32CostTime;

    CHANNEL_TRACE();

    u32CostTime = ProcTimeProbe(enCmd);

    if (STATISTICS_STOP == enCmd)
    {
        if (u32CostTime >= RENDER_PROCESS_TIMEOUT)
        {
            HI_INFO_AO("**********TimeOut ConsumeMs(%d)!!!!!!!\n", u32CostTime);
            pstEngine->u32RenderTimeOutCnt++;
        }
        HI_INFO_AO("ConsumeMs(%d)\n", u32CostTime);
    }
}

HI_VOID Proc_Sink(ENGINE_MANAGER_S* pstEngine, STATISTICS_CMD_E enCmd)
{
    HI_U32 u32CostTime;

    CHANNEL_TRACE();

    u32CostTime = ProcTimeProbe(enCmd);

    if (STATISTICS_STOP == enCmd)
    {
        if (u32CostTime > SINK_PROCESS_TIMEOUT)
        {
            pstEngine->u32SinkTimeOutCnt++;
        }
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
