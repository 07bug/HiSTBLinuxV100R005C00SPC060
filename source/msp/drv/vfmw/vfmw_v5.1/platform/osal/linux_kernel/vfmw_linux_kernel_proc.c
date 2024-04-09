#include "scd_drv.h"
#include "fsp.h"
#include "vfmw_ctrl.h"
#include "vfmw_linux_kernel_proc.h"

#if 0
#ifdef ENV_ARMLINUX_KERNEL

#ifdef HI_ADVCA_FUNCTION_RELEASE
#undef  HI_VFMW_PROC_SUPPORT
#else
#define HI_VFMW_PROC_SUPPORT
#endif
#endif
#endif

#define HI_VFMW_PROC_SUPPORT

#ifdef HI_VFMW_PROC_SUPPORT

#define MAX_VID_PROTOCOL_NAME       (20)

#define VFMW_PROC_NAME_INFO     "vfmw_info"
#define VFMW_PROC_NAME_HELP     "vfmw_help"
#define VFMW_PROC_NAME_CHN      "vfmw_chan"
#define VFMW_PROC_NAME_SCD      "vfmw_scd"
#define VFMW_PROC_NAME_VDH      "vfmw_vdh"
#define VFMW_PROC_NAME_FSP      "vfmw_fsp"
#define VFMW_PROC_NAME_LWD      "vfmw_lowdelay"
#define VFMW_PROC_NAME_STATIS   "vfmw_statis"
#define VFMW_PROC_NAME_DIFF     "vfmw_diff"

extern SINT32 g_ExtraRef;
extern SINT32 g_ExtraDisp;
extern UINT32 g_ExtraCommand;
extern SINT32 g_VfmwInitCount;
extern SINT32 g_CurProcChan;
extern SM_IIS_S  s_SmIIS[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern SMDRV_PARAM_S   g_ScdDrvParam[MAX_SCD_NUM];
extern VFMW_CHAN_S *s_pstVfmwChan[MAX_CHAN_NUM];
extern UINT32 g_ClkSelect;
extern UINT32 g_StandardObedience;
extern UINT32 g_TimeRecTable[MAX_RECORD_POS][MAX_RECORD_NUM];
extern UINT8  g_TimeRecId[MAX_RECORD_POS];
extern UINT32 g_DataTable[MAX_RECORD_DATA][MAX_RECORD_NUM];
extern UINT8  g_DataRecId[MAX_RECORD_DATA];
extern SINT8  g_SaveFilePath[64];
extern VBOOL  g_StatisticsEnable;

module_param(g_ExtraRef,     int, 0000);
module_param(g_ExtraDisp,    int, 0000);
module_param(g_ExtraCommand, int, 0000);

struct proc_dir_entry *g_pVfmwProc = NULL;

SINT32 vfmw_proc_fops_open(struct inode *inode, struct file *file)
{
    vfmw_proc_func *proc;

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0)
    proc = PDE(inode)->data;
#else
    proc = PDE_DATA(inode);
#endif

    if (NULL == proc)
    {
        return -ENOSYS;
    }

    if (proc->read)
    {
        return single_open(file, proc->read, proc);
    }

    return -ENOSYS;
}

ssize_t vfmw_proc_fops_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct seq_file *s      = file->private_data;
    vfmw_proc_func  *proc   = s->private;

    if (proc->write)
    {
        return proc->write(file, buf, count, ppos);
    }

    return -ENOSYS;
}

static const struct file_operations vfmw_proc_fops =
{
    .owner   = THIS_MODULE,
    .open    = vfmw_proc_fops_open,
    .read    = seq_read,
    .write   = vfmw_proc_fops_write,
    .llseek  = seq_lseek,
    .release = single_release,
};

VOID show_standard(VFMW_CHAN_S *pChan, char *strVidStd)
{
    char *strVidstdTemp = NULL;

    switch (pChan->eVidStd)
    {
        case VFMW_H264:
            strVidstdTemp = "H264";
            break;

        case VFMW_VC1:
            strVidstdTemp = "VC1";
            break;

        case VFMW_MPEG4:
            strVidstdTemp = "MPEG4";
            break;

        case VFMW_MPEG2:
            strVidstdTemp = "MPEG2";
            break;

        case VFMW_DIVX3:
            strVidstdTemp = "DIVX3";
            break;
#ifdef VFMW_AVS_SUPPORT

        case VFMW_AVS:
            if (pChan->stSynCtx.unSyntax.stAvsCtx.SyntaxNew.bAvsPlus)
            {
                strVidstdTemp = "AVS+";
            }
            else
            {
                strVidstdTemp = "AVS";
            }

            break;
#endif

        case VFMW_JPEG:
            strVidstdTemp = "JPEG";
            break;

        case VFMW_REAL8:
            strVidstdTemp = "REAL8";
            break;

        case VFMW_REAL9:
            strVidstdTemp = "REAL9";
            break;

        case VFMW_VP6:
            strVidstdTemp = "VP6";
            break;

        case VFMW_VP6F:
            strVidstdTemp = "VP6F";
            break;

        case VFMW_VP6A:
            strVidstdTemp = "VP6A";
            break;

        case VFMW_VP8:
            strVidstdTemp = "VP8";
            break;

        case VFMW_VP9:
            strVidstdTemp = "VP9";
            break;

        case VFMW_H263:
            strVidstdTemp = "H263";
            break;

        case VFMW_SORENSON:
            strVidstdTemp = "SORENSON";
            break;

        case VFMW_MVC:
            strVidstdTemp = "MVC";
            break;

        case VFMW_HEVC:
            strVidstdTemp = "HEVC";
            break;

        case VFMW_RAW:
            strVidstdTemp = "RAW";
            break;

        case VFMW_USER:
            strVidstdTemp = "USER";
            break;

        case VFMW_AVS2:
            strVidstdTemp = "AVS2";
            break;

        case VFMW_END_RESERVED:
            strVidstdTemp = "RESERVED";
            break;

        default:
            *strVidStd = '\0';
            break;
    }

    if (strVidstdTemp)
    {
        strncpy(strVidStd, strVidstdTemp, strlen(strVidstdTemp));
        strVidStd[strlen(strVidstdTemp)] = '\0';
    }

    return;
}

VOID show_eof_state(LAST_FRAME_STATE_E eState, char *strState)
{
    char *strStateTemp = NULL;

    switch (eState)
    {
        case LAST_FRAME_INIT:
            strStateTemp = "BLANK";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_RECEIVE:
            strStateTemp = "RECEIVED";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_SUCCESS:
            strStateTemp = "SUCCESS";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FAILURE:
            strStateTemp = "FAILURE";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case LAST_FRAME_REPORT_FRAMEID:
            strStateTemp = "FRAMEID";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        default:
            *strState = '\0';
            break;
    }

    return;
}

#ifdef MV_HEVC_SUPPORT
VOID show_layer_state(UINT32 LayerId, OUTPUT_ORDER_E eOrder, char *strState)
{
    char *strStateTemp = NULL;

    switch (eOrder)
    {
        case DISP_ORDER:
            strStateTemp = (LayerId == 0) ? "Output" : "Discard";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_BASE_LAYER:
            strStateTemp = (LayerId == 0) ? "Output" : "Discard";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_ENHANCED_LAYER:
            strStateTemp = (LayerId == 0) ? "Ignor" : "Output";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;

        case DISP_ORDER_ALL_LAYERS:
        default:
            strStateTemp = (LayerId == 0) ? "Output" : "Output";
            strncpy(strState, strStateTemp, strlen(strStateTemp));
            strState[strlen(strStateTemp)] = '\0';
            break;
    }

    return;
}

VOID show_shvc_infor(struct seq_file *p, VFMW_CHAN_S *pChan)
{
    SINT32 i;
    UINT32 OverLap = 0;
    char strLayerState[MAX_VID_PROTOCOL_NAME];

    HEVC_CTX_S *pCtx = (HEVC_CTX_S *)(&pChan->stSynCtx.unSyntax);

    seq_printf(p, "%-40s :%d\n", "IsMvHevc", pCtx->IsMultiLayers);
    seq_printf(p, "%-40s :%d\n", "IsShvc",   pCtx->IsShvcType);

    for (i = 0; i < pCtx->LayerNum; i++)
    {
        show_layer_state(i, pChan->stSynExtraData.eOutputOrder, strLayerState);
        seq_printf(p, "%s%-34d :%dx%d -- %s\n", "Layer ",   i, pCtx->LayerWidth[i], pCtx->LayerHeight[i], strLayerState);
    }

    for (i = 0; i < pCtx->MaxVpsNum; i++)
    {
        OverLap = HEVC_CheckVpsExtOverlap(&(pCtx->pVPS[i].vps_extension));

        if (OverLap != 0)
        {
            seq_printf(p, "%s%-36d :%s\n", "VPS ", i, (OverLap == 3) ? "both overlap" : ((OverLap == 2) ? "tail overlap" : "head overlap"));
        }
    }

    for (i = 0; i < pCtx->MaxPpsNum; i++)
    {
        OverLap = HEVC_CheckPpsExtOverlap(&(pCtx->pPPS[i].pps_extension));

        if (OverLap != 0)
        {
            seq_printf(p, "%s%-36d :%s\n", "PPS ", i, (OverLap == 3) ? "both overlap" : ((OverLap == 2) ? "tail overlap" : "head overlap"));
        }
    }

    OverLap = HEVC_CheckSliceExtOverlap(&(pCtx->CurrSlice.slice_extension));

    if (OverLap != 0)
    {
        seq_printf(p, "%-40s :%s\n", "Slice ", (OverLap == 3) ? "both overlap" : ((OverLap == 2) ? "tail overlap" : "head overlap"));
    }

    return;
}
#endif

static VOID show_stdard_information(struct seq_file *p, SINT32 ChanId)
{
    VFMW_CHAN_S *pChan = NULL;
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;

    pChan = s_pstVfmwChan[ChanId];

    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "ChanId %d inactive\n", ChanId);
        return;
    }

    seq_printf(p, "-------------------- Video Standard INFO ----------------------\n");

    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    if (pChan->eVidStd == VFMW_HEVC)
    {
#ifdef MV_HEVC_SUPPORT
        show_shvc_infor(p, pChan);
#endif
    }

#ifdef VFMW_VC1_SUPPORT

    if (pChan->eVidStd == VFMW_VC1)
    {
        seq_printf(p, "%-40s :%d\n", "g_Use_FFAPT_Enable", g_Use_FFAPT_Enable);
        seq_printf(p, "%-40s :%d\n", "StdExt AP",          pChan->stChanCfg.StdExt.Vc1Ext.IsAdvProfile);
        seq_printf(p, "%-40s :%d\n", "StdExt CodecVer",    pChan->stChanCfg.StdExt.Vc1Ext.CodecVersion);
    }

#endif
#ifdef VFMW_VP6_SUPPORT
    else if (pChan->eVidStd == VFMW_VP6 || pChan->eVidStd == VFMW_VP6F || pChan->eVidStd == VFMW_VP6A)
    {
        seq_printf(p, "%-40s :%d\n", "StdExt Reversed", pChan->stChanCfg.StdExt.Vp6Ext.bReversed);
    }

#endif
#ifdef VFMW_VP9_SUPPORT
    else if (pChan->eVidStd == VFMW_VP9)
    {
        VP9_CTX_S *pVp9Ctx = (VP9_CTX_S *)(&pChan->stSynCtx.unSyntax);

        seq_printf(p, "%-40s :%d\n", "NeedFrmNum", pVp9Ctx->NeedFrmNum);
        seq_printf(p, "%-40s :%d\n", "MaxRefNum",  pVp9Ctx->MaxRefNum);
        seq_printf(p, "%-40s :%d\n", "CurRefNum",  pVp9Ctx->CurRefNum);
    }

#endif
#ifdef VFMW_MPEG4_SUPPORT
    else if (pChan->eVidStd == VFMW_MPEG4)
    {
        seq_printf(p, "%-40s :%d\n", "Skip Frame Found",     pVfmwChanStat->u32SkipFind);
        seq_printf(p, "%-40s :%d\n", "Skip Frame Discarded", pVfmwChanStat->u32SkipDiscard);
        seq_printf(p, "%-40s :%d\n", "Is Short Headed", ((MP4_CTX_S *)(&pChan->stSynCtx.unSyntax))->ScdUpMsg.IsShStreamFlag);
    }

#endif
#ifdef VFMW_USER_SUPPORT
    else if (pChan->eVidStd == VFMW_USER)
    {
        USRDEC_FRAME_DESC_S *FrameDesc = &pChan->stRecentUsrdecFrame;
        seq_printf(p, "Recent UsrdecFrame: enFmt=%d,w=%d,h=%d,Ystride=%d,Cstride=%d,PTS=%lld\n",
                   FrameDesc->enFmt, FrameDesc->s32YWidth, FrameDesc->s32YHeight, FrameDesc->s32LumaStride, FrameDesc->s32ChromStride, FrameDesc->Pts);
    }
#endif
#ifdef VFMW_AVS2_SUPPORT
    else if (pChan->eVidStd == VFMW_AVS2)
    {
        AVS2_CTX_S *pAVS2Ctx = (AVS2_CTX_S *)(&pChan->stSynCtx.unSyntax);

        seq_printf(p, "%-40s :%d\n", "ProfileID", pAVS2Ctx->SyntaxNew.syn_seq.profile_id);
        seq_printf(p, "%-40s :%d\n", "LevelID",   pAVS2Ctx->SyntaxNew.syn_seq.level_id);
        seq_printf(p, "%-40s :%d\n", "MaxDpbNum", pAVS2Ctx->SyntaxNew.syn_seq.ucMaxDpbNum);
    }
#endif

    seq_printf(p, "\n");
}

static VOID show_first_frame_time(struct seq_file *p, SINT32 ChanId)
{
    VFMW_CHAN_STAT_S *pChanStat = NULL;

    pChanStat = &g_VfmwChanStat[ChanId];

    seq_printf(p, "---------------------- First Frame INFO -----------------------\n");
    seq_printf(p, "%-40s :%d ms\n",    "FsRequire    - FirstRaw    use", pChanStat->u32FirstFrameStoreRequireTime - pChanStat->u32FirstRawArrivedTime);
    seq_printf(p, "%-40s :%d ms\n",    "FsReady      - FsRequire   use", pChanStat->u32FirstFrameStoreReadyTime   - pChanStat->u32FirstFrameStoreRequireTime);
    seq_printf(p, "%-40s :%d ms\n",    "StartDecode  - FsReady     use", pChanStat->u32FirstFrameStartDecodeTime  - pChanStat->u32FirstFrameStoreReadyTime);
    seq_printf(p, "%-40s :%d ms\n",    "DecodeOver   - StartDecode use", pChanStat->u32FirstFrameDecodeOverTime   - pChanStat->u32FirstFrameStartDecodeTime);
    seq_printf(p, "%-40s :%d ms\n",    "FrameOutput  - StartDecode use", pChanStat->u32FirstFrameOutputTime       - pChanStat->u32FirstFrameDecodeOverTime);
    seq_printf(p, "%-40s :%d ms\n",    "FrameReceive - FrameOutput use", pChanStat->u32FirstFrameReceiveTime      - pChanStat->u32FirstFrameOutputTime);
    seq_printf(p, "\n");
    seq_printf(p, "%-40s :%d ms\n",    "First Frame Decode Total   use", pChanStat->u32FirstFrameReceiveTime - pChanStat->u32FirstRawArrivedTime);
    seq_printf(p, "\n");
}

static VOID show_resize_time(struct seq_file *p, SINT32 ChanId)
{
    seq_printf(p, "---------------------- Reszie INFO -----------------------\n");

    seq_printf(p, "%-40s :%d ms\n",    "Wait              use", g_VfmwChanStat[ChanId].u32WaitCost);
    seq_printf(p, "%-40s :%d ms\n",    "Partition         use", g_VfmwChanStat[ChanId].u32PartitionCost);
    seq_printf(p, "\n");
    seq_printf(p, "%-40s :%d ms\n",    "Last Resize Total use", g_VfmwChanStat[ChanId].u32ResizeTotalCost);
    seq_printf(p, "\n");
}

SINT32 string_to_value(char *str, UINT32 *data)
{
    UINT32 i, d, dat, weight;

    dat = 0;

    i = 0;
    weight = 10;

    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        weight = 16;
    }

    for (; i < 10; i++)
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

static void get_string_from_command(char *cmd, UINT32 count, SINT32 *index, char *str)
{
    SINT32 i, j;

    i = *index;
    j = 0;

    for (; i < count; i++)
    {
        if (j == 0 && cmd[i] == ' ') { continue; }

        if (cmd[i] > ' ') { str[j++] = cmd[i]; }

        if (j > 0 && cmd[i] == ' ') { break; }
    }

    str[j] = 0;

    *index = i;
}

static SINT32 get_path_from_command(char *cmd, UINT32 count, SINT32 *index, char *str)
{
    SINT32 i, j = 0;
    i = *index;

    for (; i < count; i++)
    {
        if (j == 0 && cmd[i] == ' ') { continue; }

        if (cmd[i] > ' ') { str[j++] = cmd[i]; }

        if (j > 0 && cmd[i] <= ' ') { break; }
    }

    *index = i;
    str[j] = 0;

    if (str[0] == '/')
    {
        if (j >= 1)
        {
            if (str[j - 1] == '/')
            {
                str[j - 1] = 0;
            }

            dprint(PRN_ALWS, "******* vfmw save path: %s ********\n", str);
            strncpy(g_SaveFilePath, str, sizeof(g_SaveFilePath));
            g_SaveFilePath[sizeof(g_SaveFilePath) - 1] = '\0';
        }
        else
        {
            dprint(PRN_ALWS, "%s %d j < 1!!\n", __FUNCTION__, __LINE__);
            return -1;
        }
    }

    return 0;
}

static SINT32 analysis_params(char *cmd, char *str, unsigned long count, UINT32 *dat)
{
    /* dat[0] */
    SINT32 i = 0;

    get_string_from_command(cmd, count, &i, str);

    if (string_to_value(str, &dat[0]) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* dat[1] */
    get_string_from_command(cmd, count, &i, str);

    if (string_to_value(str, &dat[1]) != 0)
    {
        dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
        return -1;
    }

    /* extra arguments */
    if (dat[0] >= 0x200 && dat[0] < 0x300)
    {
        if (get_path_from_command(cmd, count, &i, str) < 0)
        {
            dprint(PRN_ALWS, "error echo cmd '%s'!\n", cmd);
            return -1;
        }
    }

    return 0;
}

SINT32 vfmw_read_proc_info(struct seq_file *p, VOID *v)
{
    SINT32 i;
    extern UADDR  g_TracerPhyAddr;
    extern UINT32 g_SaveRawAfterReset;
    extern SINT8  g_SaveFilePath[64];

    if (p == NULL)
    {
        dprint(PRN_ALWS, "p invalid\n");
        return -1;
    }

    seq_printf(p, "\n");
    seq_printf(p, "------------------------- VFMW INFO ---------------------------\n");
    seq_printf(p, "%-40s :%s\n",   "Version",                     VFMW_VERSION);
    seq_printf(p, "%-40s :%s\n\n", "Modification Date",           VFMW_MODIFICATION_DATE);
#ifdef VFMW_8K_SUPPORT
    seq_printf(p, "%-40s :%s\n",   "MaxCapSupport",               "8K");
#else
    seq_printf(p, "%-40s :%s\n",   "MaxCapSupport",               "4K");
#endif
    seq_printf(p, "%-40s :%d\n",   "VfmwInitCount",               g_VfmwInitCount);
    seq_printf(p, "%-40s :0x%x\n", "print enable word",           g_PrintEnable);
    seq_printf(p, "%-40s :%s\n",   "path to save debug data", (char *)g_SaveFilePath);
    seq_printf(p, "%-40s :0x%x\n", "tracer address",              g_TracerPhyAddr);
    seq_printf(p, "%-40s :0x%x\n", "vfmw_state enable word",      g_TraceCtrl);
    seq_printf(p, "%-40s :%d\n",   "bitstream control period",    g_TraceBsPeriod);
    seq_printf(p, "%-40s :%d\n",   "frame control period",        g_TraceFramePeriod);
    seq_printf(p, "%-40s :%d\n",   "rcv/rls img control period",  g_TraceImgPeriod);
    seq_printf(p, "%-40s :%d\n",   "Use_FFAPT_Enable",            g_Use_FFAPT_Enable);
    seq_printf(p, "%-40s :%d\n",   "ResetSaveNewRaw",             g_SaveRawAfterReset);
    seq_printf(p, "%-40s :0x%x\n", "ClkSelect",                   g_ClkSelect);
    seq_printf(p, "%-40s :%d\n",   "StandardObedience",           g_StandardObedience);
    seq_printf(p, "\n");

    seq_printf(p, "------------------------ MAX %d CHAN --------------------------\n", MAX_CHAN_NUM);
    seq_printf(p, "Chan Status:\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (s_pstVfmwChan[i] != NULL)
        {
            seq_printf(p, "Chan: %d, is open: %d, is run: %d, priority: %d\n", i, s_pstVfmwChan[i]->s32IsOpen, s_pstVfmwChan[i]->s32IsRun, s_pstVfmwChan[i]->s32Priority);
        }
    }

    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_help(struct seq_file *p, VOID *v)
{
    SINT32 ret;
    UINT32 ProcCmdIndex = 0;
    char ProcCmdString[50];

    if (p == NULL)
    {
        dprint(PRN_ALWS, "p invalid\n");
        return -1;
    }

#define PRINT_WORD(x)       seq_printf(p, "  %-15s  0x%x\n", #x, 1<<(x))

    seq_printf(p, "\n");
    seq_printf(p, "------------------------- HELP INFO ---------------------------\n");
    seq_printf(p, "you can perform vfmw debug with such commond:\n");
    seq_printf(p, "echo [arg1] [arg2] > /proc/vfmw\n");
    seq_printf(p, "\n");

    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'proc command list' cmd id & cmd desc\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    do
    {
        ret = VCTRL_ShowProcCommand(ProcCmdIndex, ProcCmdString, sizeof(ProcCmdString));

        if (ret != VCTRL_OK)
        {
            break;
        }

        ProcCmdIndex++;

        seq_printf(p, "%s\n", ProcCmdString);
    }
    while (1);

    seq_printf(p, "\n");

    seq_printf(p, "---------------------------------------------------------------\n");
    seq_printf(p, "'print_enable_word' definition:\n");
    seq_printf(p, "---------------------------------------------------------------\n");
    PRINT_WORD(PRN_FATAL);
    PRINT_WORD(PRN_ERROR);
    PRINT_WORD(PRN_WARN);
    PRINT_WORD(PRN_CTRL);
    PRINT_WORD(PRN_VDMREG);
    PRINT_WORD(PRN_DNMSG);
    PRINT_WORD(PRN_RPMSG);
    PRINT_WORD(PRN_UPMSG);
    PRINT_WORD(PRN_STREAM);
    PRINT_WORD(PRN_IMAGE);
    PRINT_WORD(PRN_QUEUE);
    PRINT_WORD(PRN_REF);
    PRINT_WORD(PRN_DPB);
    PRINT_WORD(PRN_POC);
    PRINT_WORD(PRN_FSP);
    PRINT_WORD(PRN_SEQ);
    PRINT_WORD(PRN_PIC);
    PRINT_WORD(PRN_SLICE);
    PRINT_WORD(PRN_SEI);
    PRINT_WORD(PRN_SE);
    PRINT_WORD(PRN_DBG);
    PRINT_WORD(PRN_SCD_INFO);
    PRINT_WORD(PRN_TEE);
    PRINT_WORD(PRN_BLOCK);
    PRINT_WORD(PRN_PTS);
    PRINT_WORD(PRN_DEC_MODE);
    PRINT_WORD(PRN_FRAME);
    PRINT_WORD(PRN_UNUSED_27);
    PRINT_WORD(PRN_UNUSED_28);
    PRINT_WORD(PRN_UNUSED_29);
    PRINT_WORD(PRN_UNUSED_30);
    PRINT_WORD(PRN_UNUSED_31);
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_chn(struct seq_file *p, VOID *v)
{
    SINT32 ChanId;
    VFMW_CHAN_S *pChan = NULL;
    IMAGE_VO_QUEUE *pstDecQue = NULL;
    SINT32 RefNum = 0, ReadNum = 0, NewNum = 0;
    SINT32 QueHist = 0, QueHead = 0, QueTail = 0;
    char strVidStd[MAX_VID_PROTOCOL_NAME];
    char strEofState[MAX_VID_PROTOCOL_NAME];

    ChanId = g_CurProcChan;

    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    pChan = s_pstVfmwChan[ChanId];

    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "ChanId %d inactive\n", ChanId);
        return 0;
    }

    VCTRL_GetChanImgNum(ChanId, &RefNum, &ReadNum, &NewNum);

    pstDecQue = VCTRL_GetChanVoQue(ChanId);

    if (pstDecQue != NULL)
    {
        QueHist = pstDecQue->history;
        QueHead = pstDecQue->head;
        QueTail = pstDecQue->tail;
    }

    show_standard(pChan, strVidStd);
    show_eof_state(pChan->eLastFrameState, strEofState);

    seq_printf(p, "\n");
    seq_printf(p, "------------------------ CHAN %2d INFO ------------------------\n", ChanId);
    seq_printf(p, "%-40s :%d\n",          "IsOpen",                pChan->s32IsOpen);
    seq_printf(p, "%-40s :%d\n",          "IsRun",                 pChan->s32IsRun);
    seq_printf(p, "%-40s :%d\n",          "Priority",              pChan->s32Priority);
    seq_printf(p, "%-40s :%s\n",          "eVidStd",               strVidStd);
    seq_printf(p, "%-40s :%d\n",          "ChanCapLevel",          pChan->eChanCapLevel);
    seq_printf(p, "%-40s :%s\n",          "LastFrameState",        strEofState);
    seq_printf(p, "%-40s :%d\n",          "IsOmxPath",             pChan->stChanCfg.s32IsOmxPath);
    seq_printf(p, "%-40s :%d\n",          "CfgDecMode",            pChan->stChanCfg.s32DecMode);
    seq_printf(p, "%-40s :%d\n",          "CfgOutputOrder",        pChan->stChanCfg.s32DecOrderOutput);
    seq_printf(p, "%-40s :%d\n",          "ErrorThred",            pChan->stChanCfg.s32ChanErrThr);
    seq_printf(p, "%-40s :%d\n",          "StreamThred",           pChan->stChanCfg.s32ChanStrmOFThr);
    seq_printf(p, "%-40s :%d\n",          "UvmosEnable",           pChan->stChanCfg.bUVMOSEnable);
    seq_printf(p, "%-40s :%d\n",          "CompressCfg",           pChan->stChanCfg.enCompress);
    seq_printf(p, "%-40s :%d\n",          "Compress",              pChan->stSynExtraData.CompressEn);
    seq_printf(p, "%-40s :%d\n",          "DecCompress",           pChan->stSynExtraData.DecCompressEn);
    seq_printf(p, "%-40s :%d\n",          "LossCompress",          pChan->stSynExtraData.LossCompressEn);
    seq_printf(p, "%-40s :%d\n",          "BitDepthCfg",           pChan->stChanCfg.enBitDepthCfg);
    seq_printf(p, "%-40s :%d\n",          "BitDepth",              pChan->stSynExtraData.s32BitDepth);
    seq_printf(p, "%-40s :%d\n",          "WaitFsFlag",            pChan->stSynExtraData.s32WaitFsFlag);
    seq_printf(p, "%-40s :%d\n",          "DecodeFrameNum",        pChan->DecodeFrameNumber);
    seq_printf(p, "%-40s :%d\n",          "OutputFrameNum",        pChan->OutputFrameNumber);
    seq_printf(p, "%-40s :%d\n",          "DecIFrameNum",          pChan->DecIFrameNum);
    seq_printf(p, "%-40s :%d\n",          "DecPFrameNum",          pChan->DecPFrameNum);
    seq_printf(p, "%-40s :%d\n",          "DecBFrameNum",          pChan->DecBFrameNum);
    seq_printf(p, "%-40s :0x%x\n",        "CTX Mem Phy",           pChan->stChanMem_ctx.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "CTX Mem Size",          pChan->stChanMem_ctx.Length);
    seq_printf(p, "%-40s :0x%x\n",        "SCD Mem Phy",           pChan->stChanMem_scd.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "SCD Mem Size",          pChan->stChanMem_scd.Length);
    seq_printf(p, "%-40s :0x%x\n",        "VDH Mem Phy",           pChan->stChanMem_vdh.PhyAddr);
    seq_printf(p, "%-40s :%d\n",          "VDH Mem Size",          pChan->stChanMem_vdh.Length);
    seq_printf(p, "%-40s :(%d,%d,%d)\n",  "Ref,Read,New",          RefNum, ReadNum, NewNum);
    seq_printf(p, "%-40s :(%d,%d,%d)\n",  "VoQue detail",          QueHist, QueHead, QueTail);
    seq_printf(p, "%-40s :%d\n",          "Act DecMode ",          pChan->stSynExtraData.s32DecMode);
    seq_printf(p, "%-40s :%d\n",          "Act OutputOrder",       pChan->stSynExtraData.eOutputOrder);
    seq_printf(p, "%-40s :%d\n",          "Frame Packing Type",    pChan->eLastFramePackingType);

    if (pChan->stSynExtraData.LossCompressEn == 1)
    {
        seq_printf(p, "%-40s :%d\n",          "YCompressRatio",        pChan->stSynExtraData.YCompRatio);
        seq_printf(p, "%-40s :%d\n",          "UVCompressRatio",       pChan->stSynExtraData.UVCompRatio);
    }

    seq_printf(p, "\n");

    show_stdard_information(p, ChanId);
    show_first_frame_time(p, ChanId);
    show_resize_time(p, ChanId);

    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_scd(struct seq_file *p, VOID *v)
{
    SINT32 ret;
    SINT32 ChanId;
    SINT32 ModuleId;
    SINT32 SegUsedPercent;
    SINT32 RawNum, RawSize, SegNum, SegSize = 0, BufSize;
    SM_INSTANCE_S *pInst = NULL;
    SMDRV_PARAM_S *pScdDrvParam = NULL;
    char strVidStd[MAX_VID_PROTOCOL_NAME];
    VFMW_CHAN_S *pChan = NULL;

    seq_printf(p, "\n");
    seq_printf(p, "--------------------------- SCD INFO --------------------------\n");

    for (ModuleId = 0; ModuleId < MAX_VDH_NUM; ModuleId++)
    {
        pScdDrvParam = &g_ScdDrvParam[ModuleId];
        seq_printf(p, "%-40s :%d\n",    "IsScdDrvOpen",    pScdDrvParam->IsScdDrvOpen);
        seq_printf(p, "%-40s :%d\n",    "SCDState",        pScdDrvParam->SCDState);
        seq_printf(p, "%-40s :%d\n",    "ThisInstID",      pScdDrvParam->ThisInstID);
        seq_printf(p, "%-40s :%d\n",    "LastProcessTime", pScdDrvParam->LastProcessTime);
        seq_printf(p, "%-40s :%#x\n",   "HwMemAddr",       pScdDrvParam->ScdDrvMem.HwMemAddr);
        seq_printf(p, "%-40s :%d\n",    "HwMemSize",       pScdDrvParam->ScdDrvMem.HwMemSize);
        seq_printf(p, "%-40s :%#x\n",   "DownMsgMemAddr",  pScdDrvParam->ScdDrvMem.DownMsgMemAddr);
        seq_printf(p, "%-40s :%#x\n",   "UpMsgMemAddr",    pScdDrvParam->ScdDrvMem.UpMsgMemAddr);
    }

    seq_printf(p, "\n");

    ChanId = g_CurProcChan;

    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    pChan = s_pstVfmwChan[ChanId];

    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "ChanId %d inactive\n", ChanId);
        return 0;
    }

    pInst = s_SmIIS[ChanId].pSmInstArray;

    if (pInst == NULL || pInst->Mode == SM_INST_MODE_IDLE)
    {
        dprint(PRN_ALWS, "pInst %d invalid\n", ChanId);
        return 0;
    }

    ret = GetRawStreamSize(&pInst->RawPacketArray, &RawSize);

    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetRawStreamSize return failed!\n", __func__);
    }

    ret = GetRawStreamNum(&pInst->RawPacketArray, &RawNum);

    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetRawStreamNum return failed!\n", __func__);
    }

    ret = GetSegStreamSize(&pInst->StreamSegArray, &SegSize);

    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetSegStreamSize return failed!\n", __func__);
    }

    SegNum = GetSegStreamNum(&pInst->StreamSegArray);

    if (ret != FMW_OK)
    {
        dprint(PRN_ALWS, "%s call GetSegStreamNum return failed!\n", __func__);
    }

    BufSize = pInst->StreamSegArray.SegBufSize;

    if (BufSize == 0)
    {
        SegUsedPercent = 0;
    }
    else
    {
        SegUsedPercent = SegSize * 100 / BufSize;
    }

    show_standard(pChan, strVidStd);

    seq_printf(p, "------------------------- STREAM INFO -------------------------\n");
    seq_printf(p, "%-40s :%d\n",      "Mode",              pInst->Mode);
    seq_printf(p, "%-40s :%d\n",      "Chan",              ChanId);
    seq_printf(p, "%-40s :%s\n",      "Cfg standard",      strVidStd);
    seq_printf(p, "%-40s :%#x\n",     "Cfg buf addr",      pInst->Config.BufPhyAddr);
    seq_printf(p, "%-40s :%d\n",      "Cfg buf size",      pInst->Config.BufSize);
    seq_printf(p, "%-40s :%#x\n",     "Seg read addr",     pInst->StreamSegArray.SegBufReadAddr);
    seq_printf(p, "%-40s :%#x\n",     "Seg write addr",    pInst->StreamSegArray.SegBufWriteAddr);
    seq_printf(p, "%-40s :%d\n",      "Is counting",       pInst->IsCounting);
    seq_printf(p, "%-40s :%d\n",      "Is omx path",       pInst->Config.IsOmxPath);
    seq_printf(p, "%-40s :%d\n",      "Raw current size",  RawSize);
    seq_printf(p, "%-40s :%d\n",      "Raw current num",   RawNum);
    seq_printf(p, "%-40s :%d\n",      "Raw size count",    pInst->RawSizeCount);
    seq_printf(p, "%-40s :%d\n",      "Raw num count",     pInst->RawNumCount);
    seq_printf(p, "%-40s :%d\n",      "Seg current size",  SegSize);
    seq_printf(p, "%-40s :%d\n",      "Seg current num",   SegNum);
    seq_printf(p, "%-40s :%d%%\n",    "Seg used percent)", SegUsedPercent);
    seq_printf(p, "%-40s :%d Kbps\n", "Actual bitrate", pInst->BitRate);
    seq_printf(p, "\n");
    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_vdh(struct seq_file *p, VOID *v)
{
    SINT32 i;
    SINT32 ChanId;
    SINT32 VdhId;
    SINT32 VdhFps = 0;
    SINT32 VdhLoad = 0;
    SINT32 VdhCycle = 0;
    FSP_INST_S *pFsp = NULL;
    VFMW_GLOBAL_STAT_S *pVfmwGlobalStat = NULL;
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;

    ChanId = g_CurProcChan;

    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return 0;
    }

    pFsp = FSP_GetInst(ChanId);

    if (pFsp == NULL)
    {
        dprint(PRN_ALWS, "Proc VDH: chan %d invalid\n", ChanId);
        return 0;
    }

    VdhId = g_ChanCtx.ChanDecByVdhPlusOne[ChanId] - 1;

    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    seq_printf(p, "--------------------------- VDH INFO --------------------------\n");

    for (i = 0; i < MAX_VDH_NUM; i++)
    {
        pVfmwGlobalStat = &g_VfmwGlobalStat[i];
        VdhLoad  = pVfmwGlobalStat->u32VdhLoad / 10;
        VdhFps   = pVfmwChanStat->u32FrFrameRate / 10;

        if ((VdhFps != 0) && (pFsp->stInstCfg.DecFsWidth / 16 != 0) && (pFsp->stInstCfg.DecFsHeight / 16 != 0))
        {
            VdhCycle = pVfmwGlobalStat->u32VdhKiloCyclePerSecond * 1000 / VdhFps / (pFsp->stInstCfg.DecFsWidth / 16) / (pFsp->stInstCfg.DecFsHeight / 16);
        }
        else
        {
            VdhCycle = 0;
        }

        seq_printf(p, "%s%-36d :%d.%d%%\n", "VDH ",   i, VdhLoad, pVfmwGlobalStat->u32VdhLoad % 10);
        seq_printf(p, "%-40s :%d.%d fps(Chan %d)\n",  "Frame Rate",  VdhFps,  pVfmwChanStat->u32FrFrameRate % 10, ChanId);
        seq_printf(p, "%-40s :%d/mb\n",               "Cycle State", VdhCycle);
    }

    seq_printf(p, "\n");

    if (VdhId < 0)
    {
        seq_printf(p, "Chan %d NOT decoding.\n", ChanId);
    }
    else
    {
        seq_printf(p, "Chan %d decoding use VDH %d(%s).\n", ChanId, VdhId, \
                   (g_VdmExtParam[VdhId].VdmAttachStr.VdmAttachMode == VDMDRV_ATTACH_NULL) ? "Not_Attach" : "Attach");
    }

    seq_printf(p, "\n");

    seq_printf(p, "Decoding List & Priority Queue:\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (g_ChanCtx.ChanDecByVdhPlusOne[i] != 0)
        {
            seq_printf(p, "Chan %d decoding by %-3d\n", i, g_ChanCtx.ChanDecByVdhPlusOne[i] - 1);
        }

        if (g_ChanCtx.ChanIdTabByPrior[i] != -1)
        {
            seq_printf(p, "Chan %d priority is %-3d\n", i, g_ChanCtx.ChanIdTabByPrior[i]);
        }

        seq_printf(p, "\n");
    }

    seq_printf(p, "---------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_read_proc_fsp(struct seq_file *p, VOID *v)
{
    FSP_DumpState(g_CurProcChan, p);

    return 0;
}

SINT32 vfmw_read_proc_statis(struct seq_file *p, VOID *v)
{
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    UINT32 TotalDiff = 0;
    UINT32 cycle = 0;

    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;
    OSAL_FP_memset(&diff, 0, sizeof(UINT32) * (7));

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    if (g_StatisticsEnable != 1)
    {
        seq_printf(p, "Statistics not enable\n");
        return 0;
    }

    seq_printf(p, "---------------------------- VFMW STATICS (Unit:us)---------------\n");
    seq_printf(p, "Task\t SegCope(Size)\t RandTab  Syntax  VDH    IsrProcess   Wakeup\t fps\n");

    for (i = (MAX_RECORD_NUM - 1); i >= 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_END][i] - g_TimeRecTable[THREAD_START][i]) / 1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_END][i] - g_TimeRecTable[SEGCOPY_START][i]) / 1000;
        diff[2] = (g_TimeRecTable[MAP_END][i] - g_TimeRecTable[MAP_START][i]) / 1000;
        diff[3] = (g_TimeRecTable[SYNTAX_END][i] - g_TimeRecTable[SYNTAX_START][i]) / 1000;
        diff[4] = (g_TimeRecTable[VDH_HARDWARE_END][i] - g_TimeRecTable[VDH_HARDWARE_START][i]) / 1000;
        diff[5] = (g_TimeRecTable[ISR_END][i] - g_TimeRecTable[ISR_START][i]) / 1000;
        diff[6] = (g_TimeRecTable[NEXT_THREAD_START][i] - g_TimeRecTable[ISR_END][i]) / 1000;

        cycle = g_DataTable[VDH_DATA][i] / (345600) ;

        TotalDiff = (g_TimeRecTable[ISR_END][i] - g_TimeRecTable[SEGCOPY_START][i]);
        seq_printf(p, "%6u %6u(%8u) %6u %6u %6u(%6u) %6u %6u || %d.%dfps==> %u\n",
                   diff[0], diff[1], g_DataTable[COPY_SIZE_DATA][i], diff[2], diff[3], diff[4], cycle, diff[5], diff[6],
                   pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10, g_DataTable[VDH_DATA][i]);
    }

    seq_printf(p, "----------------------------------------------------------------\n");

    return 0;
}


SINT32 vfmw_read_proc_diff(struct seq_file *p, VOID *v)
{
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;
    OSAL_FP_memset(&diff, 0, sizeof(UINT32) * (7));

    if (g_StatisticsEnable != 1)
    {
        seq_printf(p, "Statistics not enable\n");
        return 0;
    }

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    seq_printf(p, "---------------------------- VFMW STATICS (Unit:ms)---------------\n");
    seq_printf(p, "Task\t   SegCope(Size)\t    RandTab     Syntax     VDH       IsrProcess      Wakeup\t    fps\n");

    for (i = (MAX_RECORD_NUM - 1); i > 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_START][i] - g_TimeRecTable[THREAD_START][i - 1]) / 1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_START][i] - g_TimeRecTable[SEGCOPY_START][i - 1]) / 1000;
        diff[2] = (g_TimeRecTable[MAP_START][i] - g_TimeRecTable[MAP_START][i - 1]) / 1000;
        diff[3] = (g_TimeRecTable[SYNTAX_START][i] - g_TimeRecTable[SYNTAX_START][i - 1]);
        diff[4] = (g_TimeRecTable[VDH_HARDWARE_START][i] - g_TimeRecTable[VDH_HARDWARE_START][i - 1]) / 1000;
        diff[5] = (g_TimeRecTable[ISR_START][i] - g_TimeRecTable[ISR_START][i - 1]) / 1000;
        diff[6] = (g_TimeRecTable[VDH_HARDWARE_END][i] - g_TimeRecTable[VDH_HARDWARE_START][i]) / 1000;
        seq_printf(p, "%u    %10u    %10u    %10u    %10u    %10u   ==>   %15u|| %d.%dfps\n",
                   diff[0], diff[1], diff[2], diff[3], diff[4], diff[5], diff[6],
                   pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10);
    }

    seq_printf(p, "----------------------------------------------------------------\n");

    return 0;
}

SINT32 vfmw_write_proc(struct file *file, const char __user *buffer, size_t count, loff_t *pos)
{
    static char cmd[256], str[256];
    UINT32 dat[6] = {0};
    UINT32 args[5];

    if (count >= sizeof(cmd))
    {
        dprint(PRN_ALWS, "MMZ: your parameter string is too long!\n");
        return -EIO;
    }

    memset(cmd, 0, sizeof(cmd));

    if (copy_from_user(cmd, buffer, count))
    {
        dprint(PRN_ALWS, "MMZ: copy_from_user failed!\n");
        return -EIO;
    }

    cmd[count] = 0;

    if (analysis_params(cmd, str, count, dat) < 0)
    {
        dprint(PRN_ALWS, "%s %d analysis params error!\n", __func__, __LINE__);
        return -EIO;
    }

    dprint(PRN_ALWS, "\nvfmw debug: arg1=%#x, arg2=%#x, dat3=%#x, dat4=%#x, dat5=%#x, dat6=%#x\n", dat[0], dat[1], dat[2], dat[3], dat[4], dat[5]);

    memcpy(args, &dat[1], sizeof(args));

    VCTRL_SetDbgOption(dat[0], (UINT8 *)args);

    return count;
}


SINT32 vfmw_proc_create(HI_CHAR *proc_name, vfmw_proc_read_fn read, vfmw_proc_write_fn write)
{
    HI_CHAR aszBuf[16];
    DRV_PROC_ITEM_S *pstItem;

    if (proc_name == NULL)
    {
        dprint(PRN_ALWS, "param is invalid\n");
        return -1;
    }

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), proc_name);
    aszBuf[sizeof(aszBuf) - 1] = '\0';
    pstItem = HI_DRV_PROC_AddModule(aszBuf, HI_NULL, HI_NULL);

    if (!pstItem)
    {
        dprint(PRN_ALWS, "Create %s proc entry fail!\n", proc_name);
        return HI_FAILURE;
    }

    /* Set functions */
    pstItem->read  = read;
    pstItem->write = write;

    return 0;
}

VOID vfmw_proc_destroy(HI_CHAR *proc_name)
{
    HI_CHAR aszBuf[16];

    if (proc_name == NULL)
    {
        dprint(PRN_ALWS, "param is invalid\n");
        return;
    }

    snprintf(aszBuf, sizeof(aszBuf), proc_name);
    HI_DRV_PROC_RemoveModule(aszBuf);
}


#endif

SINT32 vfmw_proc_init(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    SINT32  ret;

    ret = vfmw_proc_create(VFMW_PROC_NAME_INFO, vfmw_read_proc_info, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_HELP, vfmw_read_proc_help, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_CHN, vfmw_read_proc_chn, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_SCD, vfmw_read_proc_scd, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_VDH, vfmw_read_proc_vdh, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_FSP, vfmw_read_proc_fsp, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_STATIS, vfmw_read_proc_statis, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

    ret = vfmw_proc_create(VFMW_PROC_NAME_DIFF, vfmw_read_proc_diff, vfmw_write_proc);

    if (0 != ret)
    {
        return -1;
    }

#endif

    return 0;
}

VOID vfmw_proc_exit(VOID)
{
#ifdef HI_VFMW_PROC_SUPPORT
    vfmw_proc_destroy(VFMW_PROC_NAME_INFO);
    vfmw_proc_destroy(VFMW_PROC_NAME_HELP);
    vfmw_proc_destroy(VFMW_PROC_NAME_CHN);
    vfmw_proc_destroy(VFMW_PROC_NAME_SCD);
    vfmw_proc_destroy(VFMW_PROC_NAME_VDH);
    vfmw_proc_destroy(VFMW_PROC_NAME_FSP);
    vfmw_proc_destroy(VFMW_PROC_NAME_STATIS);
    vfmw_proc_destroy(VFMW_PROC_NAME_DIFF);
#endif
}

