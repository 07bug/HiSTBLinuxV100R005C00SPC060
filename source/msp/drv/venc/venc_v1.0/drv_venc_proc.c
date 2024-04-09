/***********************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  vi_proc.c
* Description:
*
***********************************************************************************/

#include "hi_drv_proc.h"
#include "hi_drv_file.h"
#include "hi_drv_mem.h"
#include "hi_drv_mmz.h"
#include "hi_drv_venc.h"
#include "drv_venc.h"
#include "hi_osal.h"
#include "hi_drv_log.h"
#include "drv_venc_osal.h"

#define CMD_LEN_MAX      (256)

#ifdef HI_PROC_SUPPORT
HI_CHAR  g_VencSavePath[PATH_LEN]    = {'/','m','n','t','\0'};

extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];
extern spinlock_t g_SendFrame_Lock[HI_VENC_MAX_CHN];     /*lock the destroy and send frame*/

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
           u32VeChn = HI_VENC_MAX_CHN;\
           break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)


static HI_VOID VENC_DRV_ProcHelp(HI_VOID)
{
    HI_DRV_PROC_EchoHelper("------ VENC Proc Help ------\n");
    HI_DRV_PROC_EchoHelper("USAGE:echo [cmd] [para1] [para2] > /proc/msp/vencXX\n");
    HI_DRV_PROC_EchoHelper("cmd = save_yuv,    para1 = start   start to save the yuv data before Encode\n");
    HI_DRV_PROC_EchoHelper("cmd = save_yuv,    para1 = stop    stop to save the yuv data before Encode\n");
    HI_DRV_PROC_EchoHelper("cmd = save_stream, para1 = second  save the streams after Encode for [para2] seconds\n");
    HI_DRV_PROC_EchoHelper("cmd = save_stream, para1 = frame  save the streams after Encode for [para2] frames\n");
    HI_DRV_PROC_EchoHelper("cmd = ClkGateEn,   para1          if [para1]=0,means unable clkGate\n");
    HI_DRV_PROC_EchoHelper("                                  if [para1]=1,means enable clkGate of frame level\n");
    HI_DRV_PROC_EchoHelper("                                  if [para1]=2,means enable clkGate both of frame and MB level\n");
    HI_DRV_PROC_EchoHelper("cmd = LowPowEn,    para1          if [para1]=0,means unable the low power control of algorithm\n");
    HI_DRV_PROC_EchoHelper("                                  if [para1]=0,means enable the low power control of algorithm\n");
    HI_DRV_PROC_EchoHelper("cmd = SaveFilePath,para1 = Path   Set save file path\n");
    HI_DRV_PROC_EchoHelper("cmd = InFrmrateType, para1        if [para1]=auto,means set InFrmrateType to auto detection\n");
    HI_DRV_PROC_EchoHelper("                                  if [para1]=stream,means set InFrmrateType from stream info\n");
    HI_DRV_PROC_EchoHelper("                                  if [para1]=user,means set InFrmrateType to user config\n");
}


static HI_S32 str2val(HI_CHAR *str, HI_U32 strLen, HI_U32 *data)
{
    HI_U32 i, d, dat, weight;

    dat = 0;

    if (strLen <= 2)
    {
        return HI_FAILURE;
    }

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        weight = 16;
    }
    else
    {
        i = 0;
        weight = 10;
    }

    for (; (i < 10) && (i < strLen); i++)
    {
        if (str[i] < 0x20) 
        { 
            break;
        }
        else if (weight == 16 && str[i] >= 'a' && str[i] <= 'f')
        {
            d = str[i] - 'a' + 10;
        }
        else if (weight == 16 && str[i] >= 'A' && str[i] <= 'F')
        {
            d = str[i] - 'A' + 10;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            d = str[i] - '0';
        }
        else
        {
            return -1;
        }

        dat = dat * weight + d;
    }

    *data = dat;

    return 0;
}

static HI_S32 val2str(HI_U32 data, HI_S32 radix, HI_CHAR* str, HI_U32 strLen)
{
    HI_CHAR tmp[32] = {'\0'};
    HI_U32 tmpval = data;
    HI_S32 i, j;

    for (i = 0; i < 32; i++)
    {
        tmp[i] = (tmpval % radix) + '0';
        tmpval = tmpval / radix;

        if (tmpval == 0)
        { break; }
    }

    for (j = 0; (i >= 0) && (i < 32) && (j < (strLen -1)); i--) 
    { 
        str[j++] = tmp[i]; 
    }

    str[j] = '\0';
    return 0;
}

static HI_U32 get_current_level(int EncWidth, int EncHeight)
{
    HI_U32 TotalMb = 0;
    HI_U32 WidthInMB = (EncWidth + 15) >> 4;
    HI_U32 HeightInMB = (EncHeight + 15) >> 4;
    HI_U32 level_idc;
    TotalMb = WidthInMB * HeightInMB;

    if (TotalMb <= 99)
    {
        level_idc = 10;
    }
    else if (TotalMb <= 396)
    {
        level_idc = 20;
    }
    else if (TotalMb <= 792)
    {
        level_idc = 21;
    }
    else if (TotalMb <= 1620)
    {
        level_idc = 30;
    }
    else if (TotalMb <= 3600)
    {
        level_idc = 31;
    }
    else if (TotalMb <= 5120)
    {
        level_idc = 32;
    }
    else if (TotalMb <= 8192)
    {
        level_idc = 41;
    }
    else
    {
        level_idc = 0;
    }

    return level_idc;
}

static HI_BOOL IsParameterSet(VeduEfl_NALU_S* pNalu, HI_U32 Protocol)
{
    HI_BOOL Flag = HI_FALSE;

    if (Protocol == VEDU_H264)
    {
        Flag = (pNalu->NaluType == 7/*SPS*/) ? HI_TRUE : HI_FALSE;
    }

    return Flag;
}


static HI_S32 VENC_DRV_ProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_S32 s32Ret = HI_FAILURE;
    DRV_PROC_ITEM_S *pProcItem;
    VeduEfl_EncPara_S* pEncPara = NULL;
    VeduEfl_EncPara_S* hVenc;
    HI_U32 u32ChnID = 0;
    HI_U32 u32SkipFrmNum = 0;
    HI_U32 u32LevelID = 0;
    VeduEfl_StatInfo_S StatInfo;
    VeduEfl_StatInfo_S *pStatInfo = &StatInfo;
    HI_U32  srcID;
    HI_CHAR srcTab[4][8]={{"VI"},{"Win"},{"DISP"},{"User"}};

    HI_CHAR szProtocol[][8] = {"MPEG2", "MPEG4", "AVS",  "H.263",    "H.264", "REAL8", "REAL9",
                               "VC1",   "VP6", "VP6F", "VP6A", "SORENSON", "MJPEG", "DIVX3", "RAW",   "JPEG",  "UNKNOWN"
                              };
    HI_CHAR szAVCProfile[][16] = {"Baseline","Main","Extended","High","UNKNOWN"};
    HI_CHAR szEncodeLevel[][8] = {"QCIF", "CIF", "D1",  "720P", "1080P", "UNKNOWN"};

    HI_CHAR szBoolTab[][8] = {"FALSE", "TRUE"};
    HI_CHAR szStateTab[][8] = {"Stop", "Start"};
    HI_CHAR szPixFormat[][16] = {"SP420_UV", "SP420_VU", "Planer420",  "Planer422", "Package422_YUYV", "Package422_UYVY", "Package422_YVYU", "SP422", "UNKNOWN"};
    HI_CHAR szBufStateTab[][8] = {"NA", "NA"};
    HI_CHAR szMaxMinQP[][8] = {"NA", "NA"};
    HI_CHAR szInputFrmRateType[4][8] = {"Auto", "Stream", "User", "UNKNOWN"};
    HI_CHAR szRCSkipThr[8] = "";
    HI_S32 ICatchEnable;
    HI_S32 InputFrmRateTypeDefaultId;
    HI_S32 InputFrmRateTypeConfigId;
    HI_S32 LowDlyMod;
    unsigned long flags;

    pProcItem = p->private;
    hVenc = (VeduEfl_EncPara_S*)pProcItem->data;

    D_VENC_GET_CHN(u32ChnID, hVenc);
    D_VENC_CHECK_CHN(u32ChnID);

    spin_lock_irqsave(&g_SendFrame_Lock[u32ChnID], flags);
    pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;
    if ((pEncPara != NULL) && (VENC_DRV_CheckChnStateSafe(u32ChnID) == HI_TRUE))
    {
        s32Ret = VENC_DRV_EflQueryStatInfo(pEncPara, pStatInfo);

        if (s32Ret != HI_SUCCESS)
        {
            spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);
            return HI_FAILURE;
        }
        ICatchEnable = pEncPara->ICatchEnable;
        LowDlyMod    = pEncPara->LowDlyMod;
        InputFrmRateTypeDefaultId = pEncPara->InputFrmRateTypeDefault;
        InputFrmRateTypeConfigId  = pEncPara->InputFrmRateTypeConfig;
    }
    else
    {
        spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);
        return HI_FAILURE;
    }
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);

    switch (g_stVencChn[u32ChnID].enSrcModId)
    {
    #ifdef VENC_SUPPORT_ATTACH_VI
        case HI_ID_VI:
            srcID = 0;
            break;
    #endif
    #ifdef VENC_SUPPORT_ATTACH_VO
        case HI_ID_VO:
            srcID = 1;
            break;
    #endif
    #ifdef VENC_SUPPORT_ATTACH_CAST
        case HI_ID_DISP:
            srcID = 2;
            break;
    #endif
        default:
            srcID = 3;
            break;
    }

    memcpy(szBufStateTab[0], "6", 2);
    val2str(pStatInfo->QueueNum, 10, szBufStateTab[1], 8);
#ifdef VENC_SUPPORT_JPGE
    if (g_stVencChn[u32ChnID].stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_JPEG)
    {
        /* CBR */
        memcpy(szMaxMinQP[0], "NA", 3);
        memcpy(szMaxMinQP[1], "NA", 3);
    }
    else
#endif
    {
        /* VBR */
        val2str( g_stVencChn[u32ChnID].stChnUserCfg.u32MaxQp, 10, szMaxMinQP[0], 8);
        val2str( g_stVencChn[u32ChnID].stChnUserCfg.u32MinQp, 10, szMaxMinQP[1], 8);
    }

    if (g_stVencChn[u32ChnID].stChnUserCfg.u32DriftRateThr > 100)
    {
        memcpy(szRCSkipThr, "NA", 3);
    }
    else
    {
        val2str(g_stVencChn[u32ChnID].stChnUserCfg.u32DriftRateThr, 10, szRCSkipThr, 8);
        HI_OSAL_Strncat(szRCSkipThr, "%", 2);
    }

    u32LevelID = get_current_level(g_stVencChn[u32ChnID].stChnUserCfg.u32Width, g_stVencChn[u32ChnID].stChnUserCfg.u32Height);
    u32SkipFrmNum = pStatInfo->QuickEncodeSkip + pStatInfo->ErrCfgSkip + pStatInfo->FrmRcCtrlSkip
                    + pStatInfo->TooFewBufferSkip + pStatInfo->SamePTSSkip + pStatInfo->TooManyBitsSkip;

    PROC_PRINT(p, "--------------------- VENC[%02d] -----------------------\n", u32ChnID);
    PROC_PRINT(p, "SavePath                      :%s\n"                     ,g_VencSavePath);
    PROC_PRINT(p, "-------------------- User  Config ----------------------\n");
    PROC_PRINT(p,
               "Version                       :%s\n"
               "CodecID                       :%s(0x%x)\n"
               "Capability                    :%s\n"
               "Profile(Level)                :%s(%d)\n"
               "Resolution                    :%uX%u\n"
               "TargetBitRate                 :%u(kbps)\n"
               "Gop                           :%u\n"
               "FrmRate(Input/OutPut)         :%u/%u(fps)\n"
               "priority                      :%u\n"
               "QuickEncode                   :%s\n"
               "DriftRateThr                  :%s\n"
               "Split                         :Enable(%s)    Size(%u byte)\n"
               "StreamBufSize                 :%u(KB)\n"
               "MaxQP/MinQP                   :%s/%s\n"
               "QLevel                        :%u\n"
               "Rotation                      :%u\n"
               "AutoRequestIFrm               :Enable(%s)\n"
               "InFrmRateType(Default/Config) :%s/%s\n"
               ,
               VENC_FIRMWARE_VERSION,
               szProtocol[g_stVencChn[u32ChnID].stChnUserCfg.enVencType], g_stVencChn[u32ChnID].stChnUserCfg.enVencType,
               szEncodeLevel[g_stVencChn[u32ChnID].stChnUserCfg.enCapLevel],
               szAVCProfile[g_stVencChn[u32ChnID].stChnUserCfg.enVencProfile], u32LevelID,
               g_stVencChn[u32ChnID].stChnUserCfg.u32Width,
               g_stVencChn[u32ChnID].stChnUserCfg.u32Height,
               g_stVencChn[u32ChnID].stChnUserCfg.u32TargetBitRate / 1024U,
               g_stVencChn[u32ChnID].stChnUserCfg.u32Gop,
               g_stVencChn[u32ChnID].stChnUserCfg.u32InputFrmRate, g_stVencChn[u32ChnID].stChnUserCfg.u32TargetFrmRate,
               g_stVencChn[u32ChnID].stChnUserCfg.u8Priority,
               szBoolTab[g_stVencChn[u32ChnID].stChnUserCfg.bQuickEncode],
               szRCSkipThr,
               szBoolTab[g_stVencChn[u32ChnID].stChnUserCfg.bSlcSplitEn], g_stVencChn[u32ChnID].u32SliceSize ,
               g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize / 1000U,
               szMaxMinQP[0], szMaxMinQP[1],
               g_stVencChn[u32ChnID].stChnUserCfg.u32Qlevel,
               g_stVencChn[u32ChnID].stChnUserCfg.u32RotationAngle,
               szBoolTab[ICatchEnable],
               szInputFrmRateType[InputFrmRateTypeDefaultId],szInputFrmRateType[InputFrmRateTypeConfigId]);
    PROC_PRINT(p, "------------------ Real-time  Statistics ----------------------\n");
    PROC_PRINT(p,
               "WorkStatus                    :%s\n"
               "SourceID                      :%s%02u\n"
               "FrameInfo                     :%s\n"
               "LowDelayMod                   :%d\n"
               "InputFrmRate(Use/Real)        :%u/%u(fps)\n"
               "TargetFrmRate(Use/Real)       :%u/%u(fps)\n"
               "BitRate                       :%u(kbps)\n"
               "EncodeNum                     :%u\n"
               "SkipNum                       :Total(%u) FrmRateCtrl(%u) SamePTS(%u) QuickEncode(%u) TooFewBuf(%u) TooManyBits(%u),ErrCfg(%u)\n"
               "TooFewBufferWaitCnt           :%d\n"
               "TooFewBufferQueFailCnt        :%d\n"
               "QueueFrmByAttachCnt           :%d\n"
               "FrameBuffer:\n"
               "    VencQueueBuf(Total/Used)  :%s/%s\n"
               "StreamBuffer:\n"
               "    Total/Used/Percent(Bytes) :%u/%u/%u%%\n"
               "Statistics(Total):\n"
               "    AcquireFrame(Try/OK)      :%d/%d\n"
               "    ReleaseFrame(Try/OK)      :%d/%d\n"
               "    AcquireStream(Try/OK)     :%d/%d\n"
               "    ReleaseStream(Try/OK)     :%d/%d\n"
               "    Input        (ETB/EBD)    :%d/%d\n"
               "    Output       (FTB/FBD)    :%d/%d\n"
               "Statistics(PerSecond):\n"
               "    AcquireFrame(Try/OK)      :%d/%d\n"
               "    ReleaseFrame(Try/OK)      :%d/%d\n"
               "    AcquireStream(Try/OK)     :%d/%d\n"
               "    ReleaseStream(Try/OK)     :%d/%d\n"
               ,
               szStateTab[g_stVencChn[u32ChnID].bEnable],
               srcTab[srcID], (g_stVencChn[u32ChnID].hSource == HI_INVALID_HANDLE ? 0 : g_stVencChn[u32ChnID].hSource & 0xff),
               szPixFormat[pStatInfo->u32FrameType],
               LowDlyMod,
               pStatInfo->u32RealSendInputRrmRate, g_stVencChn[u32ChnID].u32LastSecInputFps,
               pStatInfo->u32RealSendOutputFrmRate, g_stVencChn[u32ChnID].u32LastSecEncodedFps,
               g_stVencChn[u32ChnID].u32LastSecKbps * 8 / 1024U,
               (pStatInfo->GetFrameNumOK - u32SkipFrmNum),
               u32SkipFrmNum,
               pStatInfo->FrmRcCtrlSkip, pStatInfo->SamePTSSkip, pStatInfo->QuickEncodeSkip,
               pStatInfo->TooFewBufferSkip, pStatInfo->TooManyBitsSkip, pStatInfo->ErrCfgSkip,
               pStatInfo->TooFewBufferWaitCnt, pStatInfo->TooFewBufferQueFailCnt, pStatInfo->QueueFrmByAttachCnt,
               szBufStateTab[0], szBufStateTab[1],
               g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize, pStatInfo->UsedStreamBuf, pStatInfo->UsedStreamBuf * 100 / g_stVencChn[u32ChnID].stChnUserCfg.u32StrmBufSize,
               pStatInfo->GetFrameNumTry, pStatInfo->GetFrameNumOK,
               pStatInfo->PutFrameNumTry, pStatInfo->PutFrameNumOK,
               pStatInfo->GetStreamNumTry, pStatInfo->GetStreamNumOK,
               pStatInfo->PutStreamNumTry, pStatInfo->PutStreamNumOK,
               pStatInfo->EtbCnt,pStatInfo->EbdCnt,
               pStatInfo->FtbCnt,pStatInfo->FbdCnt,
               g_stVencChn[u32ChnID].u32LastSecTryNum, g_stVencChn[u32ChnID].u32LastSecOKNum,
               g_stVencChn[u32ChnID].u32LastSecPutNum, g_stVencChn[u32ChnID].u32LastSecPutNum,
               g_stVencChn[u32ChnID].u32LastSecStrmGetTryNum, g_stVencChn[u32ChnID].u32LastSecStrmGetOKNum,
               g_stVencChn[u32ChnID].u32LastSecStrmRlsTryNum, g_stVencChn[u32ChnID].u32LastSecStrmRlsOKNum);

    return HI_SUCCESS;
}


static void VENC_DRV_ProcCmdSaveYuv(HI_CHAR *str, HI_U32 u32ChnID)
{
    if (!HI_OSAL_Strncmp(str,"start",CMD_LEN_MAX))
    {
       g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun = HI_TRUE;
    }
    else if (!HI_OSAL_Strncmp(str,"stop",CMD_LEN_MAX))
    {
       g_stVencChn[u32ChnID].stProcWrite.bSaveYUVFileRun = HI_FALSE;
    }
    else
    {
       VENC_DRV_ProcHelp();
    }

    return;
}

static HI_VOID VENC_DRV_ProcSaveStreamBySecond(HI_S32 num, size_t count, HI_CHAR *buf, HI_U32 u32ChnID)
{
    HI_CHAR str3[CMD_LEN_MAX];
    HI_CHAR FileName[130];
    HI_U32 parm = 0;
    HI_U32 j = 0;
    HI_U32 i = num;

    memset(str3, 0, sizeof(str3));
    memset(FileName, 0, sizeof(FileName));

    for (; (i < count) && (i < CMD_LEN_MAX) && (j < (CMD_LEN_MAX - 1)); i++)
    {
        if (j == 0 && buf[i] == ' ') { continue; }
        if (buf[i] > ' ') { str3[j++] = buf[i]; }
        if (j > 0 && buf[i] == ' ') { break; }
    }
    str3[j] = '\0';

    if(str2val(str3, CMD_LEN_MAX, &parm) != 0)
    {
        HI_ERR_VENC("error: echo cmd '%s' is worng!\n", buf);

        return;
    }

    if ( parm > 3600 )
    {
        HI_ERR_VENC("error: not support save too large stream file!\n");

        return;
    }

    HI_OSAL_Snprintf(FileName, 130, "%s/%s", g_VencSavePath,g_stVencChn[u32ChnID].stProcWrite.StreamFileName);

    g_stVencChn[u32ChnID].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen(FileName,  O_RDWR | O_CREAT|O_APPEND, 0);
    if (g_stVencChn[u32ChnID].stProcWrite.fpSaveFile == HI_NULL)
    {
        HI_ERR_VENC("Can not create %s file.\n", FileName);
        g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_FALSE;

        return;
    }
    g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_TRUE;
    msleep(1000 * parm);
    g_stVencChn[u32ChnID].stProcWrite.bTimeModeRun = HI_FALSE;
    VENC_DRV_OsalFclose(g_stVencChn[u32ChnID].stProcWrite.fpSaveFile);

    return;
}

static HI_VOID VENC_DRV_ProcSaveStreamByFrame(HI_S32 num, size_t count, HI_CHAR *buf, HI_U32 u32ChnID)
{
    HI_CHAR str3[CMD_LEN_MAX];
    HI_CHAR FileName[130];
    HI_U32 parm;
    HI_U32 j = 0;
    HI_U32 i = num;
    HI_U32 cnt = 0;

    memset(str3, 0, sizeof(str3));
    memset(FileName, 0, sizeof(FileName));

    for (; (i < count) && (i < CMD_LEN_MAX) && (j < (CMD_LEN_MAX - 1)); i++)
    {
        if (j == 0 && buf[i] == ' ') { continue; }
        if (buf[i] > ' ') { str3[j++] = buf[i]; }
        if (j > 0 && buf[i] == ' ') { break; }
    }
    str3[j] = '\0';

    if (str2val(str3, CMD_LEN_MAX, &parm) != 0)
    {
        HI_ERR_VENC("error: echo cmd '%s' is worng!\n", buf);

        return;
    }

    if (parm > 100000)
    {
        HI_ERR_VENC("error: not support save too large YUV file!\n");

        return;
    }

    HI_OSAL_Snprintf(FileName, 130, "%s/%s", g_VencSavePath,g_stVencChn[u32ChnID].stProcWrite.StreamFileName);

    g_stVencChn[u32ChnID].stProcWrite.fpSaveFile = VENC_DRV_OsalFopen(FileName,  O_RDWR | O_CREAT|O_APPEND, 0);

    if (g_stVencChn[u32ChnID].stProcWrite.fpSaveFile == HI_NULL)
    {
        HI_ERR_VENC("Can not create %s file.\n", FileName);
        g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun = HI_FALSE;

        return;
    }
    g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun = HI_TRUE;
    g_stVencChn[u32ChnID].stProcWrite.u32FrameModeCount = parm;
    while (1)
    {
        /* if the frame count reaches to aim, break */
        if (g_stVencChn[u32ChnID].stProcWrite.bFrameModeRun == HI_FALSE)
        {
            break;
        }
        else
        {
            cnt++;
            if (cnt == 6000)
            {
                HI_ERR_VENC("Time of saving frame is 60s,stop saving!\n");
                break;
            }
            msleep(100);
        }
    }
    VENC_DRV_OsalFclose(g_stVencChn[u32ChnID].stProcWrite.fpSaveFile);

    return;
}

static HI_VOID VENC_DRV_ProcCmdSaveStream(HI_CHAR *str, HI_S32 i, size_t count, HI_CHAR *buf, HI_U32 u32ChnID)
{
    if (!HI_OSAL_Strncmp(str,"second",CMD_LEN_MAX))   /*time mode*/
    {
        VENC_DRV_ProcSaveStreamBySecond(i, count, buf, u32ChnID);
    }
    else if (!HI_OSAL_Strncmp(str,"frame",CMD_LEN_MAX))
    {
        VENC_DRV_ProcSaveStreamByFrame(i, count, buf, u32ChnID);
    }
    else
    {
       VENC_DRV_ProcHelp();
    }

    return;
}

static void VENC_DRV_ProcCmdClkGateEn(HI_CHAR *str, HI_U32 u32ChnID)
{
    VeduEfl_EncPara_S *pEncPara;
    unsigned long flags;
    HI_U32 ErrLog = 0;

    spin_lock_irqsave(&g_SendFrame_Lock[u32ChnID], flags);
    pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;
    if ((pEncPara != NULL) && (VENC_DRV_CheckChnStateSafe(u32ChnID) == HI_TRUE))
    {
        if (!HI_OSAL_Strncmp(str,"0",CMD_LEN_MAX))
        {
           pEncPara->ClkGateEn = 0;
        }
        else if (!HI_OSAL_Strncmp(str,"1",CMD_LEN_MAX))
        {
           pEncPara->ClkGateEn = 1;
        }
        else if (!HI_OSAL_Strncmp(str,"2",CMD_LEN_MAX))
        {
           pEncPara->ClkGateEn = 2;
        }
        else
        {
           ErrLog = 1;
        }    
    }
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);

    if (ErrLog)
    {
        VENC_DRV_ProcHelp();
    }

    return;
}

static void VENC_DRV_ProcCmdLowPowEn(HI_CHAR *str, HI_U32 u32ChnID)
{
    VeduEfl_EncPara_S *pEncPara;
    unsigned long flags;
    HI_U32 ErrLog = 0;

    spin_lock_irqsave(&g_SendFrame_Lock[u32ChnID], flags);
    pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;
    if ((pEncPara != NULL) && (VENC_DRV_CheckChnStateSafe(u32ChnID) == HI_TRUE))
    {
        if (!HI_OSAL_Strncmp(str,"0",CMD_LEN_MAX))
        {
            pEncPara->IntraLowpowEn    = 0;
            pEncPara->intpLowpowEn     = 0;
            pEncPara->fracLowpowEn     = 0;
        }
        else if (!HI_OSAL_Strncmp(str,"1",CMD_LEN_MAX))
        {
            pEncPara->IntraLowpowEn    = 1;
            pEncPara->intpLowpowEn     = 1;
            pEncPara->fracLowpowEn     = 1;
        }
        else
        {
           ErrLog = 1;
        }    
    }
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);

    if (ErrLog)
    {
        VENC_DRV_ProcHelp();
    }

    return;
}

static void VENC_DRV_ProcCmdSaveFilePath(HI_CHAR *str)
{
    if ((strlen(str) > sizeof(g_VencSavePath)) || (strlen(str) == 0))
    {
        HI_ERR_VENC("%s lenght larger than sizeof(g_VencSavePath) = %d\n", str, sizeof(g_VencSavePath));

        VENC_DRV_ProcHelp();
        return;
    }

    HI_OSAL_Strncpy(g_VencSavePath, str, PATH_LEN);
    g_VencSavePath[PATH_LEN - 1] = '\0';
    HI_DRV_PROC_EchoHelper("[venc] Set Save File Path = %s success\n",g_VencSavePath);

    return;
}

static void VENC_DRV_ProcWrite_SetInputFrmrateType(HI_CHAR* str, HI_U32 u32ChnID)
{
    VeduEfl_EncPara_S *pEncPara;
    unsigned long flags;
    HI_U32 ErrLog = 0;

    spin_lock_irqsave(&g_SendFrame_Lock[u32ChnID], flags);
    pEncPara = (VeduEfl_EncPara_S*)g_stVencChn[u32ChnID].hVEncHandle;
    if ((pEncPara != NULL) && (VENC_DRV_CheckChnStateSafe(u32ChnID) == HI_TRUE))
    {
        if (!HI_OSAL_Strncmp(str, "auto", CMD_LEN_MAX))
        {
            if (VENC_DRV_SetInFrmRateType(pEncPara, VENC_DRV_FRMRATE_AUTO) == HI_SUCCESS)
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to auto success.\n",u32ChnID);
            }
            else
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to auto failed.\n",u32ChnID);
            }
        }
        else if (!HI_OSAL_Strncmp(str, "stream", CMD_LEN_MAX))
        {
            if (VENC_DRV_SetInFrmRateType(pEncPara, VENC_DRV_FRMRATE_STREAM) == HI_SUCCESS)
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to stream success.\n",u32ChnID);
            }
            else
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to stream failed.\n",u32ChnID);
            }
        }
        else if (!HI_OSAL_Strncmp(str, "user", CMD_LEN_MAX))
        {
            if (VENC_DRV_SetInFrmRateType(pEncPara, VENC_DRV_FRMRATE_USER) == HI_SUCCESS)
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to user success.\n",u32ChnID);
            }
            else
            {
                HI_DRV_PROC_EchoHelper("Set channel (%d) InputFrmRate type to user failed.\n",u32ChnID);
            }
        }
        else
        {
            ErrLog = 1;
        }
    }
    spin_unlock_irqrestore(&g_SendFrame_Lock[u32ChnID], flags);

    if (ErrLog)
    {
        VENC_DRV_ProcHelp();
    }

    return;
}

static void VENC_DRV_ParseOneWord(HI_S32 count, HI_S32 *ppos, HI_CHAR *buf, HI_CHAR *str)
{
    HI_S32 j = 0;
    HI_S32 i = *ppos;
    for (; (i < count) && (i < CMD_LEN_MAX) && (j < (CMD_LEN_MAX - 1)); i++)
    {
        if (j == 0 && buf[i] == ' ') { continue; }
        if (buf[i] > ' ') { str[j++] = buf[i]; }
        if (j > 0 && buf[i] == ' ') { break; }
    }
    str[j] = '\0';
    *ppos = i;

    return;
}

static HI_S32 VENC_DRV_ProcWrite(struct file *file, const char __user *buffer, size_t count, loff_t *ppos)
{
    struct seq_file *q = file->private_data;
    DRV_PROC_ITEM_S *pProcItem = q->private;
    VeduEfl_EncPara_S *hVenc;
    static HI_CHAR buf[CMD_LEN_MAX];
    static HI_CHAR str1[CMD_LEN_MAX];
    static HI_CHAR str2[CMD_LEN_MAX];
    HI_U32 u32ChnID;
    HI_S32 pos = 0;

    memset(buf, 0, sizeof(buf));
    memset(str1, 0, sizeof(str1));
    memset(str2, 0, sizeof(str2));

    hVenc = (VeduEfl_EncPara_S*)(pProcItem->data);
    D_VENC_GET_CHN(u32ChnID, hVenc);

    if (u32ChnID >= HI_VENC_MAX_CHN)
    {
        return HI_FAILURE;
    }

    if (count >= sizeof(buf))
    {
        HI_PRINT("MMZ: your echo parameter string is too long!\n");

        return -EIO;
    }

    if (count >= 1)
    {
        memset(buf, 0, sizeof(buf));
        if (copy_from_user(buf, buffer, count))
        {
            HI_PRINT("MMZ: copy_from_user failed!\n");

            return -EIO;
        }

        buf[count] = '\0';

        /* dat1 */
        pos = 0;
        VENC_DRV_ParseOneWord(count, &pos, buf, str1);

        /* dat2 */
        VENC_DRV_ParseOneWord(count, &pos, buf, str2);

        if (!HI_OSAL_Strncmp(str1, "save_yuv", CMD_LEN_MAX))
        {
            VENC_DRV_ProcCmdSaveYuv(str2, u32ChnID);
        }
        else if (!HI_OSAL_Strncmp(str1, "save_stream", CMD_LEN_MAX))
        {
            VENC_DRV_ProcCmdSaveStream(str2, pos, count, buf, u32ChnID);
        }
        else if (!HI_OSAL_Strncmp(str1, "ClkGateEn", CMD_LEN_MAX))
        {
            VENC_DRV_ProcCmdClkGateEn(str2, u32ChnID);
        }
        else if (!HI_OSAL_Strncmp(str1, "LowPowEn", CMD_LEN_MAX))
        {
            VENC_DRV_ProcCmdLowPowEn(str2, u32ChnID);
        }
        else if (!HI_OSAL_Strncmp(str1, "SaveFilePath", CMD_LEN_MAX))
        {
            VENC_DRV_ProcCmdSaveFilePath(str2);
        }
        else if (!HI_OSAL_Strncmp(str1, "InFrmrateType", 256))
        {
            VENC_DRV_ProcWrite_SetInputFrmrateType(str2, u32ChnID);
        }
        else
        {
            VENC_DRV_ProcHelp();
        }
    }
    else
    {
        VENC_DRV_ProcHelp();
    }

    return count;
}

static HI_S32 CheckOmxImgCfg(const venc_user_buf *pstPreImage,HI_U32 yuvStoreType)
{
    HI_BOOL flag = 0;

    flag |= (pstPreImage->picWidth > HI_VENC_MAX_WIDTH)||(pstPreImage->picWidth < HI_VENC_MIN_WIDTH);
    flag |= (pstPreImage->picHeight > HI_VENC_MAX_HEIGTH)||(pstPreImage->picHeight < HI_VENC_MIN_HEIGTH);
    flag |= (!pstPreImage->bufferaddr_Phy) || (pstPreImage->bufferaddr_Phy % 16);
    flag |= (!pstPreImage->strideY) || (pstPreImage->strideY  % 16);
    flag |= (pstPreImage->strideY > FRMBUF_STRIDE_LIMIT);

    if (VENC_STORE_PLANNAR == yuvStoreType)
    {
        flag |= (!pstPreImage->offset_YC)  || (pstPreImage->offset_YC %16);
        flag |= (!pstPreImage->offset_YCr) || (pstPreImage->offset_YCr%16);
        flag |= (!pstPreImage->strideC)  || (pstPreImage->strideC %16);
        flag |= (pstPreImage->strideC > FRMBUF_STRIDE_LIMIT);
    }
    else if (VENC_STORE_SEMIPLANNAR == yuvStoreType)
    {
        flag |= (!pstPreImage->offset_YC)  || (pstPreImage->offset_YC %16);
        flag |= (!pstPreImage->strideC )  || (pstPreImage->strideC  %16);
        flag |= (pstPreImage->strideC > FRMBUF_STRIDE_LIMIT);
    }

    if (HI_TRUE == flag)
    {
       return HI_FAILURE;
    }
    else { return HI_SUCCESS; }
}
#endif
HI_S32 VENC_DRV_ProcAdd(VeduEfl_EncPara_S* hVenc, HI_U32 u32ChnID)   /**/
{
#ifdef HI_PROC_SUPPORT
    HI_S32 Ret;
    DRV_PROC_ITEM_S *pProcItem;
    HI_CHAR ProcName[12];

    if (NULL == hVenc)
    {
        return HI_FAILURE;
    }

    Ret = HI_OSAL_Snprintf(ProcName, sizeof(ProcName), "venc%02x", u32ChnID);
    if (0 == Ret)
    {
        HI_ERR_VENC("HI_OSAL_Snprintf failed!\n");
        return HI_FAILURE;
    }

    pProcItem = HI_DRV_PROC_AddModule(ProcName, HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_ERR_VENC("VENC add proc failed!\n");
        return HI_FAILURE;
    }

    pProcItem->data  = (HI_VOID *)hVenc;
    pProcItem->read  = VENC_DRV_ProcRead;
    pProcItem->write = VENC_DRV_ProcWrite;
#endif
    return HI_SUCCESS;
}

HI_VOID VENC_DRV_ProcDel(VeduEfl_EncPara_S* hVenc, HI_U32 u32ChnID)
{
#ifdef HI_PROC_SUPPORT
    HI_S32 Ret;
    HI_CHAR ProcName[12];

    if (NULL == hVenc)
    {
        return;
    }

    Ret = HI_OSAL_Snprintf(ProcName, sizeof(ProcName), "venc%02x", u32ChnID);
    if (0 == Ret)
    {
        return;
    }

    HI_DRV_PROC_RemoveModule(ProcName);
#endif
}

HI_S32 VENC_DRV_DbgWriteYUV(HI_DRV_VIDEO_FRAME_S* pstFrame, HI_CHAR* pFileName)
{
#ifdef HI_PROC_SUPPORT
    char str[130] = {0};
    unsigned char* ptr;
    struct file* fp;
    HI_U32 BufSize;
    HI_U32 len;
    HI_U8* pu8Udata;
    HI_U8* pu8Vdata;
    HI_U8* pu8Ydata;
    HI_U32 i, j;
    HI_U8* StartVirAddr = HI_NULL;
#ifdef HI_SMMU_SUPPORT
    VENC_BUFFER_S stMBuf;
    HI_S32 Ret;

    memset(&stMBuf, 0, sizeof(VENC_BUFFER_S));
#endif

    D_VENC_CHECK_PTR(pstFrame);
    D_VENC_CHECK_PTR(pFileName);
    if ((pstFrame->ePixFormat == HI_DRV_PIX_FMT_YUYV)
      ||(pstFrame->ePixFormat == HI_DRV_PIX_FMT_YVYU)
      || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_UYVY))
    {
        HI_ERR_VENC("not support format package422!\n");
        return HI_FAILURE;
    }

    pu8Udata = HI_VMALLOC(HI_ID_VENC, pstFrame->u32Width * pstFrame->u32Height / 2 / 2);

    if (pu8Udata == HI_NULL)
    {
        return HI_FAILURE;
    }
    memset(pu8Udata, 0, pstFrame->u32Width * pstFrame->u32Height / 2 / 2);

    pu8Vdata = HI_VMALLOC(HI_ID_VENC, pstFrame->u32Width * pstFrame->u32Height / 2 / 2);

    if (pu8Vdata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC, pu8Udata);
        return HI_FAILURE;
    }
    memset(pu8Vdata, 0, pstFrame->u32Width * pstFrame->u32Height / 2 / 2);

    pu8Ydata = HI_VMALLOC(HI_ID_VENC, pstFrame->stBufAddr[0].u32Stride_Y);

    if (pu8Ydata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC, pu8Udata);
        HI_VFREE(HI_ID_VENC, pu8Vdata);
        return HI_FAILURE;
    }
    memset(pu8Ydata, 0, pstFrame->stBufAddr[0].u32Stride_Y);

    BufSize = pstFrame->stBufAddr[0].u32Stride_Y * pstFrame->u32Height * 3 / 2;

#ifdef HI_SMMU_SUPPORT
    stMBuf.u32StartPhyAddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;
    Ret = HI_DRV_VENC_Map(&stMBuf);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("SMMU map is failure!\n");
        HI_VFREE(HI_ID_VENC, pu8Udata);
        HI_VFREE(HI_ID_VENC, pu8Vdata);
        HI_VFREE(HI_ID_VENC, pu8Ydata);

        return HI_FAILURE;
    }
    else
    {
        ptr = stMBuf.pu8StartVirAddr;
    }
#else
    ptr = (unsigned char*)phys_to_virt(pstFrame->stBufAddr[0].u32PhyAddr_Y);
#endif
    StartVirAddr = ptr;
    if (!ptr)
    {
        HI_ERR_VENC("address is not valid!\n");
    }
    else
    {

        HI_OSAL_Snprintf(str, 130, "%s/%s", g_VencSavePath, pFileName);

        fp = VENC_DRV_OsalFopen(str, O_RDWR | O_CREAT | O_APPEND, 0);

        if (fp == HI_NULL)
        {
            HI_ERR_VENC("open file '%s' fail!\n", str);
            HI_VFREE(HI_ID_VENC, pu8Udata);
            HI_VFREE(HI_ID_VENC, pu8Vdata);
            HI_VFREE(HI_ID_VENC, pu8Ydata);
        #ifdef HI_SMMU_SUPPORT
            HI_DRV_VENC_Unmap(&stMBuf);
        #endif

            return HI_FAILURE;
        }

        /*D¡ä Y ¨ºy?Y*/
        for (i = 0; i < pstFrame->u32Height; i++)
        {
            memcpy(pu8Ydata, ptr, sizeof(HI_U8)*pstFrame->stBufAddr[0].u32Stride_Y);

            if (pstFrame->u32Width != VENC_DRV_OsalFwrite(pu8Ydata, pstFrame->u32Width, fp))
            {
                HI_ERR_VENC("fwrite fail!\n");
            }

            ptr += pstFrame->stBufAddr[0].u32Stride_Y;
        }

#ifdef HI_SMMU_SUPPORT
        ptr = stMBuf.pu8StartVirAddr + (pstFrame->stBufAddr[0].u32PhyAddr_C - pstFrame->stBufAddr[0].u32PhyAddr_Y);
#else
        ptr = (unsigned char*)phys_to_virt(pstFrame->stBufAddr[0].u32PhyAddr_C);
#endif
        if (ptr >= (StartVirAddr + BufSize))
        {
            HI_ERR_VENC("UV VirAddr(%p) maybe invalid!\n",ptr);
            VENC_DRV_OsalFclose(fp);
            goto Exit;
        }

        /* U V ¨ºy?Y ¡Áa¡ä?*/
        if (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21 || pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12)
        {
            for (i = 0; i < pstFrame->u32Height / 2; i++)
            {
                for (j = 0; j < pstFrame->u32Width / 2; j++)
                {
                    if (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21)
                    {
                        pu8Vdata[i * pstFrame->u32Width / 2 + j] = ptr[2 * j];
                        pu8Udata[i * pstFrame->u32Width / 2 + j] = ptr[2 * j + 1];
                    }
                    else if (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12)
                    {
                        pu8Udata[i * pstFrame->u32Width / 2 + j] = ptr[2 * j];
                        pu8Vdata[i * pstFrame->u32Width / 2 + j] = ptr[2 * j + 1];
                    }
                    else
                    {
                        HI_ERR_VENC("other pix formet= %d\n", pstFrame->ePixFormat);
                    }
                }

                ptr += pstFrame->stBufAddr[0].u32Stride_C;
            }
        }
        else if (pstFrame->ePixFormat == HI_DRV_PIX_FMT_YUV420p)
        {
             for (i = 0; i < pstFrame->u32Height / 2; i++)
             {
                  memcpy(&pu8Udata[i*pstFrame->u32Width/2], ptr, sizeof(HI_U8)* pstFrame->u32Width/2);
                  ptr += pstFrame->stBufAddr[0].u32Stride_C;
             }

#ifdef HI_SMMU_SUPPORT
             ptr = stMBuf.pu8StartVirAddr + (pstFrame->stBufAddr[0].u32PhyAddr_Cr - pstFrame->stBufAddr[0].u32PhyAddr_Y);
#else
             ptr = (unsigned char*)phys_to_virt(pstFrame->stBufAddr[0].u32PhyAddr_Cr);
#endif
             if (ptr >= (StartVirAddr + BufSize))
             {
                 HI_ERR_VENC("UV VirAddr(%p) maybe invalid!\n",ptr);
                 VENC_DRV_OsalFclose(fp);
                 goto Exit;
             }

             for (i = 0; i < pstFrame->u32Height / 2; i++)
             {
                  memcpy(&pu8Vdata[i*pstFrame->u32Width/2], ptr, sizeof(HI_U8)* pstFrame->u32Width/2);
                  ptr += pstFrame->stBufAddr[0].u32Stride_C;
             }
        }
        else
        {
            HI_ERR_VENC("other pix formet= %d, error!!!!\n", pstFrame->ePixFormat);
            VENC_DRV_OsalFclose(fp);
            goto Exit;
        }

        /*D¡ä U */
        len = pstFrame->u32Width * pstFrame->u32Height / 2 / 2;
        if (len != VENC_DRV_OsalFwrite(pu8Udata, len, fp))
        {
            HI_ERR_VENC("fwrite fail!\n");
        }

        /*D¡ä V */
        if (len != VENC_DRV_OsalFwrite(pu8Vdata, len, fp))
        {
            HI_ERR_VENC("fwrite fail!\n");
        }

        VENC_DRV_OsalFclose(fp);
        HI_INFO_VENC("2d image has been saved to '%s' W=%d H=%d Format=%d \n",
                     str, pstFrame->u32Width, pstFrame->u32Height, pstFrame->ePixFormat);
    }

Exit:
    HI_VFREE(HI_ID_VENC, pu8Udata);
    HI_VFREE(HI_ID_VENC, pu8Vdata);
    HI_VFREE(HI_ID_VENC, pu8Ydata);
#ifdef HI_SMMU_SUPPORT
    HI_DRV_VENC_Unmap(&stMBuf);
#endif
#endif
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_DbgWriteYUV_OMX(venc_user_buf *pstFrameOmx, HI_CHAR* pFileName)
{
#ifdef HI_PROC_SUPPORT
    char str[130] = {0};
    unsigned char *ptr;
    struct file *fp;
    HI_U32 BufSize;
    HI_U32 len;
    HI_U8 *pu8Udata;
    HI_U8 *pu8Vdata;
    HI_U8 *pu8Ydata;
    HI_U32 i,j;
    HI_U8* StartVirAddr = HI_NULL;

#ifdef HI_SMMU_SUPPORT
    VENC_BUFFER_S stMBuf;
    HI_S32 Ret;

    memset(&stMBuf, 0, sizeof(VENC_BUFFER_S));
#endif

    D_VENC_CHECK_PTR(pstFrameOmx);
    D_VENC_CHECK_PTR(pFileName);

    if (pstFrameOmx->store_type == VENC_STORE_PACKAGE)
    {
        HI_ERR_VENC("not support format package422!\n");
        return HI_FAILURE;
    }

    if (CheckOmxImgCfg(pstFrameOmx, pstFrameOmx->store_type) != HI_SUCCESS)
    {
        HI_ERR_VENC("format check failed!\n");
        return HI_FAILURE;
    }

    BufSize = pstFrameOmx->strideY * pstFrameOmx->picHeight * 3 / 2;

    pu8Udata = HI_VMALLOC(HI_ID_VENC, pstFrameOmx->picWidth * pstFrameOmx->picHeight / 2 /2);
    if (pu8Udata == HI_NULL)
    {
        return HI_FAILURE;
    }
    pu8Vdata = HI_VMALLOC(HI_ID_VENC, pstFrameOmx->picWidth * pstFrameOmx->picHeight / 2 /2);
    if (pu8Vdata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC,pu8Udata);
        return HI_FAILURE;
    }
    pu8Ydata = HI_VMALLOC(HI_ID_VENC, pstFrameOmx->strideY);
    if (pu8Ydata == HI_NULL)
    {
        HI_VFREE(HI_ID_VENC,pu8Udata);
        HI_VFREE(HI_ID_VENC,pu8Vdata);
        return HI_FAILURE;
    }

#ifdef HI_SMMU_SUPPORT
    stMBuf.u32StartPhyAddr = pstFrameOmx->bufferaddr_Phy;
    Ret = HI_DRV_VENC_Map(&stMBuf);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_VENC("SMMU map is failure!\n");
        HI_VFREE(HI_ID_VENC, pu8Udata);
        HI_VFREE(HI_ID_VENC, pu8Vdata);
        HI_VFREE(HI_ID_VENC, pu8Ydata);

        return HI_FAILURE;
    }
    else
    {
        ptr = stMBuf.pu8StartVirAddr;
    }
#else
    ptr = (unsigned char*)phys_to_virt(pstFrameOmx->bufferaddr_Phy);
#endif
    StartVirAddr = ptr;
    if (!ptr)
    {
        HI_ERR_VENC("address is not valid!\n");
    }
    else
    {
        HI_OSAL_Snprintf(str, 130, "%s/%s", g_VencSavePath, pFileName);

        fp = VENC_DRV_OsalFopen(str, O_RDWR | O_CREAT|O_APPEND, 0);
        if (fp == HI_NULL)
        {
            HI_ERR_VENC("open file '%s' fail!\n", str);
            HI_VFREE(HI_ID_VENC,pu8Udata);
            HI_VFREE(HI_ID_VENC,pu8Vdata);
            HI_VFREE(HI_ID_VENC,pu8Ydata);
        #ifdef HI_SMMU_SUPPORT
            HI_DRV_VENC_Unmap(&stMBuf);
        #endif

            return HI_FAILURE;
        }

        /*write Y data*/
        for (i=0; i < pstFrameOmx->picHeight; i++)
        {
            memcpy(pu8Ydata, ptr, sizeof(HI_U8)* pstFrameOmx->strideY);

            if (pstFrameOmx->picWidth != VENC_DRV_OsalFwrite(pu8Ydata, pstFrameOmx->picWidth, fp))
            {
                HI_ERR_VENC("fwrite fail!\n");
            }

            ptr += pstFrameOmx->strideY;
        }
#ifdef HI_SMMU_SUPPORT
        ptr = stMBuf.pu8StartVirAddr + (pstFrameOmx->offset_YC);
#else
        ptr = (unsigned char*)phys_to_virt(pstFrameOmx->bufferaddr_Phy) + (pstFrameOmx->offset_YC);
#endif
        if (ptr >= (StartVirAddr + BufSize))
        {
            HI_ERR_VENC("UV VirAddr(%p) maybe invalid!\n",ptr);
            VENC_DRV_OsalFclose(fp);
            goto Exit;
        }

        /*put U or V data together*/
        if ((pstFrameOmx->store_type == VENC_STORE_SEMIPLANNAR) && (pstFrameOmx->sample_type == VENC_YUV_420))
        {
            for (i=0; i<pstFrameOmx->picHeight/2; i++)
            {
                for (j=0; j<pstFrameOmx->picWidth/2; j++)
                {
                    if(pstFrameOmx->package_sel == VENC_V_U)
                    {
                        pu8Vdata[i*pstFrameOmx->picWidth/2+j] = ptr[2*j];
                        pu8Udata[i*pstFrameOmx->picWidth/2+j] = ptr[2*j+1];
                    }
                    else if (pstFrameOmx->package_sel == VENC_U_V)
                    {
                        pu8Udata[i*pstFrameOmx->picWidth/2+j] = ptr[2*j];
                        pu8Vdata[i*pstFrameOmx->picWidth/2+j] = ptr[2*j+1];
                    }
                    else
                    {
                        HI_ERR_VENC("other pix formet= %d\n",pstFrameOmx->package_sel);
                    }
                }

                ptr += pstFrameOmx->strideC;
            }
        }
        else if ((pstFrameOmx->store_type == VENC_STORE_PLANNAR) && (pstFrameOmx->sample_type == VENC_YUV_420))
        {
             for (i = 0; i < pstFrameOmx->picHeight/2; i++)
             {
                  memcpy(&pu8Udata[i*pstFrameOmx->picWidth/2], ptr, sizeof(HI_U8)* pstFrameOmx->picWidth/2);
                  ptr += pstFrameOmx->strideC;
             }

#ifdef HI_SMMU_SUPPORT
             ptr = stMBuf.pu8StartVirAddr + (pstFrameOmx->offset_YCr);
#else
             ptr = (unsigned char*)phys_to_virt(pstFrameOmx->bufferaddr_Phy) + (pstFrameOmx->offset_YCr);
#endif
             if (ptr >= (StartVirAddr + BufSize))
             {
                 HI_ERR_VENC("UV VirAddr(%p) maybe invalid!\n",ptr);
                 VENC_DRV_OsalFclose(fp);
                 goto Exit;
             }

             for (i = 0; i < pstFrameOmx->picHeight/2; i++)
             {
                  memcpy(&pu8Vdata[i*pstFrameOmx->picWidth/2], ptr, sizeof(HI_U8)* pstFrameOmx->picWidth/2);
                  ptr += pstFrameOmx->strideC;
             }
        }
        else
        {
            HI_ERR_VENC("other pix formet= %d, error!!!!\n", pstFrameOmx->store_type);
            VENC_DRV_OsalFclose(fp);
            goto Exit;
        }

        /*write U data*/
        len = pstFrameOmx->picWidth * pstFrameOmx->picHeight/ 2 / 2;
        if (len != VENC_DRV_OsalFwrite(pu8Udata, len, fp))
        {
            HI_ERR_VENC("fwrite fail!\n");
        }

        /*write V data*/
        if (len != VENC_DRV_OsalFwrite(pu8Vdata, len, fp))
        {
            HI_ERR_VENC("fwrite fail!\n");
        }

        VENC_DRV_OsalFclose(fp);
        HI_INFO_VENC("2d image has been saved to '%s' W=%d H=%d Format=%d,%d,%d \n",
                     str, pstFrameOmx->picWidth, pstFrameOmx->picHeight, pstFrameOmx->store_type, pstFrameOmx->sample_type, pstFrameOmx->package_sel);
    }

Exit:
    HI_VFREE(HI_ID_VENC, pu8Udata);
    HI_VFREE(HI_ID_VENC, pu8Vdata);
    HI_VFREE(HI_ID_VENC, pu8Ydata);
#ifdef HI_SMMU_SUPPORT
    HI_DRV_VENC_Unmap(&stMBuf);
#endif
#endif
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_DbgSaveStream(VeduEfl_NALU_S* pNalu, VeduEfl_EncPara_S* phVencChn)
{
#ifdef HI_PROC_SUPPORT
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_StatInfo_S StatInfo;
    static HI_BOOL bTagFirstTimeSave = HI_TRUE;
    static HI_BOOL bTagFirstPsGet    = HI_FALSE;
    static HI_U32 u32SaveFrameStartCount = 0;
    HI_U32 u32SkipFrmNum = 0;
    HI_U32 u32VeChn = HI_VENC_MAX_CHN;

    D_VENC_GET_CHN(u32VeChn, phVencChn);
    if (u32VeChn >= HI_VENC_MAX_CHN)
    {
        return HI_FAILURE;
    }

    D_VENC_CHECK_PTR(pNalu);

    if ((g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun == HI_TRUE) || (g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun == HI_TRUE))
    {
        s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[u32VeChn].hVEncHandle, &StatInfo);

        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_VENC("VeduEfl_QueryStatInfo failed.\n");

            return HI_FAILURE;
        }

        u32SkipFrmNum = StatInfo.QuickEncodeSkip + StatInfo.SamePTSSkip + StatInfo.ErrCfgSkip
                        + StatInfo.FrmRcCtrlSkip + StatInfo.TooFewBufferSkip;

        /* request one I frame and record u32SaveFrameStartCount to compare with g_VencSaveFrameCount when save file firstly */
        if (bTagFirstTimeSave == HI_TRUE)
        {
            if (!IsParameterSet(pNalu, phVencChn->Protocol))
            {
                HI_ERR_VENC(" request one I frame\n");
                VENC_DRV_EflRequestIframe(phVencChn);
                phVencChn->IFrmInsertBySaveStrm = 1;
                bTagFirstTimeSave = HI_FALSE;

                u32SaveFrameStartCount = StatInfo.GetFrameNumOK - u32SkipFrmNum;

                return HI_SUCCESS;
            }
            else
            {
                bTagFirstTimeSave = HI_FALSE;
            }
        }

        /* compare with u32FrameModeCount each time */
        if ((g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun == HI_TRUE)
            && (StatInfo.GetFrameNumOK - u32SkipFrmNum - u32SaveFrameStartCount) > g_stVencChn[u32VeChn].stProcWrite.u32FrameModeCount)
        {
            /* time to stop save file */
            g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun = HI_FALSE;

            return HI_SUCCESS;
        }

        if (!bTagFirstPsGet)
        {
            if (IsParameterSet(pNalu, phVencChn->Protocol))
            {
                HI_INFO_VENC("Get First Parameter Set!\n");
                bTagFirstPsGet = HI_TRUE;
            }
            else
            {
                u32SaveFrameStartCount = StatInfo.GetFrameNumOK - u32SkipFrmNum;
                HI_INFO_VENC("No First Parameter Set!\n");
                return HI_SUCCESS;
            }
        }

        if (pNalu->SlcLen[0] > 0)
        {
            s32Ret = VENC_DRV_OsalFwrite((char*)pNalu->pVirtAddr[0], pNalu->SlcLen[0] , g_stVencChn[u32VeChn].stProcWrite.fpSaveFile);
            if (s32Ret != pNalu->SlcLen[0])
            {
                HI_ERR_VENC("VeduOsal_Fwrite[0] failed.\n");
                g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun  = HI_FALSE;
                g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun = HI_FALSE;

                return HI_FAILURE;
            }
        }

        if (pNalu->SlcLen[1] > 0)
        {
            s32Ret = VENC_DRV_OsalFwrite((char*)pNalu->pVirtAddr[1], pNalu->SlcLen[1] , g_stVencChn[u32VeChn].stProcWrite.fpSaveFile);
            if (s32Ret != pNalu->SlcLen[1])
            {
                HI_ERR_VENC("VeduOsal_Fwrite failed.\n");
                g_stVencChn[u32VeChn].stProcWrite.bTimeModeRun  = HI_FALSE;
                g_stVencChn[u32VeChn].stProcWrite.bFrameModeRun = HI_FALSE;

                return HI_FAILURE;
            }
        }
    }
    else
    {
        bTagFirstTimeSave = HI_TRUE;
        bTagFirstPsGet    = HI_FALSE;
    }
#endif
    return HI_SUCCESS;
}


