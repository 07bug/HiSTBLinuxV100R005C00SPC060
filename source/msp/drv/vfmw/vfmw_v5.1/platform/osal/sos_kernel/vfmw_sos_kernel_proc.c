#include "fsp.h"
#include "vfmw_ctrl.h"
#include "vfmw_tee_client.h"

extern SINT32 g_CurProcChan;
extern UINT32 g_ClkSelect;
extern SINT32 g_VfmwInitCount;
extern UINT32 g_StandardObedience;
extern SM_IIS_S  s_SmIIS[MAX_CHAN_NUM];
extern VDMDRV_EXT_S g_VdmExtParam[MAX_VDH_NUM];
extern VFMW_CHAN_S *s_pstVfmwChan[MAX_CHAN_NUM];
extern SMDRV_PARAM_S g_ScdDrvParam[MAX_SCD_NUM];
extern VFMW_CHAN_STAT_S g_VfmwChanStat[MAX_CHAN_NUM];
extern VFMW_GLOBAL_STAT_S g_VfmwGlobalStat[MAX_VDH_NUM];
extern UINT32 g_TimeRecTable[MAX_RECORD_POS][MAX_RECORD_NUM];
extern UINT8  g_TimeRecId[MAX_RECORD_POS];
extern UINT32 g_DataTable[MAX_RECORD_DATA][MAX_RECORD_NUM];
extern UINT8  g_DataRecId[MAX_RECORD_DATA];
extern VBOOL  g_StatisticsEnable;

READ_PROC_TYPE_E g_SecProcSelect = READ_PROC_CHAN;

#ifdef  STAT_DUMP
#undef  STAT_DUMP
#endif
#define STAT_DUMP(page, fmt, arg...) (UsedSize += OSAL_FP_snprintf(((char *)page + UsedSize), (PageSize - UsedSize), fmt, ##arg))

#define STAT_ASSERT_RET(Cond, Ret, Fmt, Arg...) \
    do { \
        if(!(Cond)) \
        { \
            dprint(PRN_ALWS, Fmt, ##Arg); \
            return Ret; \
        } \
    }while(0)

static SINT32 SOS_show_first_frame_time(SINT32 ChanId, SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    VFMW_CHAN_STAT_S *pChanStat = NULL;

    pChanStat = &g_VfmwChanStat[ChanId];

    STAT_DUMP(Page, "---------------------- First Frame INFO -----------------------\n");
    STAT_DUMP(Page, "%s :%d ms\n",    "FsRequire    - FirstRaw    use",    pChanStat->u32FirstFrameStoreRequireTime - pChanStat->u32FirstRawArrivedTime);
    STAT_DUMP(Page, "%s :%d ms\n",    "FsReady      - FsRequire   use",    pChanStat->u32FirstFrameStoreReadyTime   - pChanStat->u32FirstFrameStoreRequireTime);
    STAT_DUMP(Page, "%s :%d ms\n",    "StartDecode  - FsReady     use",    pChanStat->u32FirstFrameStartDecodeTime  - pChanStat->u32FirstFrameStoreReadyTime);
    STAT_DUMP(Page, "%s :%d ms\n",    "DecodeOver   - StartDecode use",    pChanStat->u32FirstFrameDecodeOverTime   - pChanStat->u32FirstFrameStartDecodeTime);
    STAT_DUMP(Page, "%s :%d ms\n",    "FrameOutput  - StartDecode use",    pChanStat->u32FirstFrameOutputTime       - pChanStat->u32FirstFrameDecodeOverTime);
    STAT_DUMP(Page, "%s :%d ms\n",    "FrameReceive - FrameOutput use",    pChanStat->u32FirstFrameReceiveTime      - pChanStat->u32FirstFrameOutputTime);
    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "%s :%d ms\n",    "First Frame Decode Total   use",    pChanStat->u32FirstFrameReceiveTime - pChanStat->u32FirstRawArrivedTime);
    STAT_DUMP(Page, "\n");

    return UsedSize;
}

static SINT32 SOS_show_resize_time(SINT32 ChanId, SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;

    STAT_DUMP(Page, "---------------------- Reszie INFO -----------------------\n");

    STAT_DUMP(Page, "%s :%d ms\n",    "Wait              use", g_VfmwChanStat[ChanId].u32WaitCost);
    STAT_DUMP(Page, "%s :%d ms\n",    "Partition         use", g_VfmwChanStat[ChanId].u32PartitionCost);
    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "%s :%d ms\n",    "Last Resize Total use", g_VfmwChanStat[ChanId].u32ResizeTotalCost);
    STAT_DUMP(Page, "\n");

    return UsedSize;
}

SINT32 SOS_PROC_ReadChan(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    SINT32 ChanId;
    SINT32 i;
    VFMW_CHAN_S *pChan = NULL;
    IMAGE_VO_QUEUE *pstDecQue = NULL;
    SINT32 RefNum = 0, ReadNum = 0, NewNum = 0;
    SINT32 QueHist = 0, QueHead = 0, QueTail = 0;

    extern UADDR  g_TracerPhyAddr;
    extern UINT32 g_SaveRawAfterReset;
    extern SINT8  g_SaveFilePath[64];

    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "------------------------- VFMW INFO ---------------------------\n");
    STAT_DUMP(Page, "%s :%s\n",   "Version           ",           VFMW_VERSION);
    STAT_DUMP(Page, "%s :%s\n\n", "Modification Date ",           VFMW_MODIFICATION_DATE);
    STAT_DUMP(Page, "%s :%d\n",   "CurProcChan       ",           g_CurProcChan);
    STAT_DUMP(Page, "%s :%d\n",   "VfmwInitCount     ",           g_VfmwInitCount);
    STAT_DUMP(Page, "%s :0x%x\n", "print enable word ",           g_PrintEnable);
    STAT_DUMP(Page, "%s :%d\n",   "SecProcSelect     ",           g_SecProcSelect);
    STAT_DUMP(Page, "%s :0x%x\n", "ClkSelect         ",           g_ClkSelect);
    STAT_DUMP(Page, "%s :%d\n",   "StandardObedience ",           g_StandardObedience);
    STAT_DUMP(Page, "\n");

    STAT_DUMP(Page, "------------------------ MAX %d CHAN --------------------------\n", MAX_CHAN_NUM);
    STAT_DUMP(Page, "Chan Status:\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (s_pstVfmwChan[i] != NULL)
        {
            STAT_DUMP(Page, "Chan: %d, is open: %d, is run: %d, priority: %d\n", i, s_pstVfmwChan[i]->s32IsOpen, s_pstVfmwChan[i]->s32IsRun, s_pstVfmwChan[i]->s32Priority);
        }
    }

    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "---------------------------------------------------------------\n");

    ChanId = g_CurProcChan;

    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return UsedSize;
    }

    pChan = s_pstVfmwChan[ChanId];

    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "Chan %d inactive\n", ChanId);
        return UsedSize;
    }

    VCTRL_GetChanImgNum(ChanId, &RefNum, &ReadNum, &NewNum);

    pstDecQue = VCTRL_GetChanVoQue(ChanId);

    if (pstDecQue != NULL)
    {
        QueHist = pstDecQue->history;
        QueHead = pstDecQue->head;
        QueTail = pstDecQue->tail;
    }

    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "------------------------ CHAN [%d] INFO -----------------------\n", ChanId);
    STAT_DUMP(Page, "%s :%d\n",          "IsOpen            ",       pChan->s32IsOpen);
    STAT_DUMP(Page, "%s :%d\n",          "IsRun             ",       pChan->s32IsRun);
    STAT_DUMP(Page, "%s :%d\n",          "Priority          ",       pChan->s32Priority);
    STAT_DUMP(Page, "%s :%d\n",          "eVidStd           ",       pChan->eVidStd);
    STAT_DUMP(Page, "%s :%d\n",          "ChanCapLevel      ",       pChan->eChanCapLevel);
    STAT_DUMP(Page, "%s :%d\n",          "LastFrameState    ",       pChan->eLastFrameState);
    STAT_DUMP(Page, "%s :%d\n",          "IsOmxPath         ",       pChan->stChanCfg.s32IsOmxPath);
    STAT_DUMP(Page, "%s :%d\n",          "CfgDecMode        ",       pChan->stChanCfg.s32DecMode);
    STAT_DUMP(Page, "%s :%d\n",          "CfgOutputOrder    ",       pChan->stChanCfg.s32DecOrderOutput);
    STAT_DUMP(Page, "%s :%d\n",          "ErrorThred        ",       pChan->stChanCfg.s32ChanErrThr);
    STAT_DUMP(Page, "%s :%d\n",          "StreamThred       ",       pChan->stChanCfg.s32ChanStrmOFThr);
    STAT_DUMP(Page, "%s :%d\n",          "CompressCfg       ",       pChan->stChanCfg.enCompress);
    STAT_DUMP(Page, "%s :%d\n",          "Compress          ",       pChan->stSynExtraData.CompressEn);
    STAT_DUMP(Page, "%s :%d\n",          "DecCompress       ",       pChan->stSynExtraData.DecCompressEn);
    STAT_DUMP(Page, "%s :%d\n",          "LossCompress      ",       pChan->stSynExtraData.LossCompressEn);
    STAT_DUMP(Page, "%s :%d\n",          "BitDepthCfg       ",       pChan->stChanCfg.enBitDepthCfg);
    STAT_DUMP(Page, "%s :%d\n",          "BitDepth          ",       pChan->stSynExtraData.s32BitDepth);
    STAT_DUMP(Page, "%s :%d\n",          "WaitFsFlag        ",       pChan->stSynExtraData.s32WaitFsFlag);
    STAT_DUMP(Page, "%s :%d\n",          "DecodeFrameNum    ",       pChan->DecodeFrameNumber);
    STAT_DUMP(Page, "%s :%d\n",          "OutputFrameNum    ",       pChan->OutputFrameNumber);
    STAT_DUMP(Page, "%s :%d\n",          "DecIFrameNum      ",       pChan->DecIFrameNum);
    STAT_DUMP(Page, "%s :%d\n",          "DecPFrameNum      ",       pChan->DecPFrameNum);
    STAT_DUMP(Page, "%s :%d\n",          "DecBFrameNum      ",       pChan->DecBFrameNum);
    STAT_DUMP(Page, "%s :0x%x\n",        "CTX Mem Phy       ",       pChan->stChanMem_ctx.PhyAddr);
    STAT_DUMP(Page, "%s :%d\n",          "CTX Mem Size      ",       pChan->stChanMem_ctx.Length);
    STAT_DUMP(Page, "%s :0x%x\n",        "SCD Mem Phy       ",       pChan->stChanMem_scd.PhyAddr);
    STAT_DUMP(Page, "%s :%d\n",          "SCD Mem Size      ",       pChan->stChanMem_scd.Length);
    STAT_DUMP(Page, "%s :0x%x\n",        "VDH Mem Phy       ",       pChan->stChanMem_vdh.PhyAddr);
    STAT_DUMP(Page, "%s :%d\n",          "VDH Mem Size      ",       pChan->stChanMem_vdh.Length);
    STAT_DUMP(Page, "%s :(%d,%d,%d)\n",  "Ref,Read,New      ",       RefNum, ReadNum, NewNum);
    STAT_DUMP(Page, "%s :(%d,%d,%d)\n",  "VoQue detail      ",       QueHist, QueHead, QueTail);
    STAT_DUMP(Page, "%s :%d\n",          "Act DecMode       ",       pChan->stSynExtraData.s32DecMode);
    STAT_DUMP(Page, "%s :%d\n",          "Act OutputOrder   ",       pChan->stSynExtraData.eOutputOrder);
    STAT_DUMP(Page, "%s :%d\n",          "Frame Packing Type",       pChan->eLastFramePackingType);

    if (pChan->stSynExtraData.LossCompressEn == 1)
    {
        STAT_DUMP(Page, "%s :%d\n",          "YCompressRatio    ",       pChan->stSynExtraData.YCompRatio);
        STAT_DUMP(Page, "%s :%d\n",          "UVCompressRatio   ",       pChan->stSynExtraData.UVCompRatio);
    }

    STAT_DUMP(Page, "\n");

    UsedSize += SOS_show_first_frame_time(ChanId, Page, PageSize);
    UsedSize += SOS_show_resize_time(ChanId, Page, PageSize);

    STAT_DUMP(Page, "---------------------------------------------------------------\n");

    return UsedSize;
}

SINT32 SOS_PROC_ReadFsp(SINT8 *Page, SINT32 PageSize)
{
    SINT32 i;
    SINT32 ChanId;
    UINT8  IsFree;
    UINT32 TotalFree;
    UINT32 ExtraNum;
    UINT32 OccupiedNum;
    SINT32 UsedSize = 0;
    FSP_INST_S *pFsp = NULL;
    FSP_LOGIC_FS_S *pLogicFs;

    ChanId = g_CurProcChan;

    pFsp = FSP_GetInst(ChanId);
    STAT_ASSERT_RET(pFsp != NULL, UsedSize, "pFsp %d invalid\n", ChanId);

    ExtraNum    = VCTRL_GetExtraFrameNum(ChanId);
    OccupiedNum = VCTRL_GetOccupiedNum(ChanId, pFsp->stInstCfg.DecFsWidth, pFsp->stInstCfg.DecFsHeight);

    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "----------------------------- FSP %d --------------------------\n", pFsp->InstID);
    STAT_DUMP(Page, "%s :%d\n", "InstState         ",      pFsp->eInstState);
    STAT_DUMP(Page, "%s :%d\n", "PartitionState    ",      pFsp->ePartitionState);
    STAT_DUMP(Page, "%s :%d\n", "ExtraFrameNum     ",      ExtraNum);
    STAT_DUMP(Page, "%s :%d\n", "OccupiedFrameNum  ",      OccupiedNum);
    STAT_DUMP(Page, "\n");

    STAT_DUMP(Page, "----------------------------- CFG -----------------------------\n");
    STAT_DUMP(Page, "%s :%d\n", "VidStd            ",      pFsp->stInstCfg.eVidStd);
    STAT_DUMP(Page, "%s :%d\n", "BitDepth          ",      pFsp->stInstCfg.BitDepth);
    STAT_DUMP(Page, "%s :%d\n", "UserDec           ",      pFsp->stInstCfg.UserDec);
    STAT_DUMP(Page, "%s :%d\n", "DecFsWidth        ",      pFsp->stInstCfg.DecFsWidth);
    STAT_DUMP(Page, "%s :%d\n", "DecFsHeight       ",      pFsp->stInstCfg.DecFsHeight);
    STAT_DUMP(Page, "%s :%d\n", "ExpectDecFsNum    ",      pFsp->stInstCfg.ExpectDecFsNum);
    STAT_DUMP(Page, "%s :%d\n", "ExpectPmvNum      ",      pFsp->stInstCfg.ExpectPmvNum);
    STAT_DUMP(Page, "\n");

    STAT_DUMP(Page, "--------------------------- MEM NEED --------------------------\n");
    STAT_DUMP(Page, "%s :%d\n", "DecFsNum          ",      pFsp->stMemNeed.stDecInfo.DecFsNum);
    STAT_DUMP(Page, "%s :%d\n", "DecFsSize         ",      pFsp->stMemNeed.stDecInfo.DecFsSize);
    STAT_DUMP(Page, "%s :%d\n", "DecLinearEn       ",      pFsp->stMemNeed.stDecInfo.LinearEn);
    STAT_DUMP(Page, "%s :%d\n", "DecCompressEn     ",      pFsp->stMemNeed.stDecInfo.CompressEn);
    STAT_DUMP(Page, "%s :%d\n", "DecBitDepth       ",      pFsp->stMemNeed.stDecInfo.BitDepth);
    STAT_DUMP(Page, "%s :%d\n", "DecHeadStride     ",      pFsp->stMemNeed.stDecInfo.HeadStride);
    STAT_DUMP(Page, "%s :%d\n", "DecHeadSize       ",      pFsp->stMemNeed.stDecInfo.HeadSize);
    STAT_DUMP(Page, "%s :%d\n", "DecYStride        ",      pFsp->stMemNeed.stDecInfo.YStride);
    STAT_DUMP(Page, "%s :%d\n", "DecUVStride       ",      pFsp->stMemNeed.stDecInfo.UVStride);
    STAT_DUMP(Page, "%s :%d\n", "DecChromOffset    ",      pFsp->stMemNeed.stDecInfo.ChromOffset);
    STAT_DUMP(Page, "%s :%d\n", "DecStride_nbit    ",      pFsp->stMemNeed.stDecInfo.Stride_nbit);
    STAT_DUMP(Page, "%s :%d\n", "LumaOffset_nbit   ",      pFsp->stMemNeed.stDecInfo.LumaOffset_nbit);
    STAT_DUMP(Page, "%s :%d\n", "ChromOffset_nbit  ",      pFsp->stMemNeed.stDecInfo.ChromOffset_nbit);
    STAT_DUMP(Page, "%s :%d\n", "LineNumOffset     ",      pFsp->stMemNeed.LineNumOffset);

    STAT_DUMP(Page, "%s :%s\n", "NeedDispFs        ", (pFsp->stMemNeed.NeedDispFs == 1) ? "Yes" : "No");

    if (pFsp->stMemNeed.NeedDispFs)
    {
        STAT_DUMP(Page, "%s :%d\n", "DispFsNum         ",      pFsp->stMemNeed.stDispInfo.DispFsNum);
        STAT_DUMP(Page, "%s :%d\n", "DispFsSize        ",      pFsp->stMemNeed.stDispInfo.DispFsSize);
        STAT_DUMP(Page, "%s :%d\n", "DispLinearEn      ",      pFsp->stMemNeed.stDispInfo.LinearEn);
        STAT_DUMP(Page, "%s :%d\n", "DispCompressEn    ",      pFsp->stMemNeed.stDispInfo.CompressEn);
        STAT_DUMP(Page, "%s :%d\n", "DispBitDepth      ",      pFsp->stMemNeed.stDispInfo.BitDepth);
        STAT_DUMP(Page, "%s :%d\n", "DispHeadStride    ",      pFsp->stMemNeed.stDispInfo.HeadStride);
        STAT_DUMP(Page, "%s :%d\n", "DispHeadSize      ",      pFsp->stMemNeed.stDispInfo.HeadSize);
        STAT_DUMP(Page, "%s :%d\n", "DispYStride       ",      pFsp->stMemNeed.stDispInfo.YStride);
        STAT_DUMP(Page, "%s :%d\n", "DispUVStride      ",      pFsp->stMemNeed.stDispInfo.UVStride);
        STAT_DUMP(Page, "%s :%d\n", "DispChromOffset   ",      pFsp->stMemNeed.stDispInfo.ChromOffset);
    }

    STAT_DUMP(Page, "%s :%s\n", "NeedPmv           ", (pFsp->stMemNeed.NeedPmv == 1) ? "Yes" : "No");

    if (pFsp->stMemNeed.NeedPmv)
    {
        STAT_DUMP(Page, "%s :%d\n", "PmvNum            ",      pFsp->stMemNeed.PmvNum);
        STAT_DUMP(Page, "%s :%d\n", "PmvSize           ",      pFsp->stMemNeed.PmvSize);
    }

    STAT_DUMP(Page, "%s :%s\n", "NeedMetadata      ", (pFsp->stMemNeed.NeedMetadata == 1) ? "Yes" : "No");

    if (pFsp->stMemNeed.NeedMetadata)
    {
        STAT_DUMP(Page, "%s :%d\n", "MetadataNum       ",      pFsp->stMemNeed.MetadataNum);
        STAT_DUMP(Page, "%s :%d\n", "MetadataSize      ",      pFsp->stMemNeed.MetadataSize);
    }

    STAT_DUMP(Page, "\n");

    TotalFree = 0;
    STAT_DUMP(Page, "--------------------------- LOGIC FS --------------------------\n");

    for (i = 0; i < MAX_FRAME_NUM; i++)
    {
        pLogicFs = &pFsp->stLogicFs[i];
        IsFree = FSP_IsLogicFsAvailable(pLogicFs);

        if (IsFree)
        {
            TotalFree += IsFree;
            continue;
        }

        if (TotalFree == i)
        {
            STAT_DUMP(Page, "%s  %s  %s  %s  %s  %s  %s\n", "Num", "Tick", "IsRef", "FsType", "FsState", "DecPhy", "DispPhy");
        }

        STAT_DUMP(Page, " %d  %d  %d  %d  %d  0x%x  0x%x\n", pLogicFs->LogicFsID,
                  pLogicFs->Tick,      pLogicFs->IsRef,
                  pLogicFs->FsType,    pLogicFs->FsState,
                  (pLogicFs->pstDecodeFs != NULL) ? pLogicFs->pstDecodeFs->PhyAddr : 0,
                  (pLogicFs->pstDispOutFs != NULL) ? pLogicFs->pstDispOutFs->PhyAddr : 0);
    }

    STAT_DUMP(Page, "%s :%d/%d\n", "LogicFs(Free/Total)", TotalFree, MAX_FRAME_NUM);
    STAT_DUMP(Page, "\n");

    if (pFsp->CfgDecFsNum > 0)
    {
        TotalFree = 0;
        STAT_DUMP(Page, "---------------------------- DEC FS ---------------------------\n");
        STAT_DUMP(Page, "%s  %s  %s  %s  %s  %s  %s  %s\n", "Num", "IsValid", "Tick", "IsRef", "LinkRef", "FsState", "Size", "Address");

        for (i = 0; i < pFsp->CfgDecFsNum; i++)
        {
            IsFree = FSP_IsDecFsAvailable(pFsp, &pFsp->stDecFsRec[i]);
            TotalFree += IsFree;

            STAT_DUMP(Page, " %d  %d  %d  %d  %d  %d  %d  0x%x  %s\n", pFsp->stDecFsRec[i].PhyFsID,
                      pFsp->stDecFsRec[i].IsValid,   pFsp->stDecFsRec[i].Tick,
                      pFsp->stDecFsRec[i].IsRef,     pFsp->stDecFsRec[i].LinkRef,
                      pFsp->stDecFsRec[i].FsState,   pFsp->stDecFsRec[i].BufSize,
                      pFsp->stDecFsRec[i].PhyAddr, (IsFree) ? "(Free)" : "");
        }

        STAT_DUMP(Page, "%s :%d/%d\n", "DecFs(Free/Total)", TotalFree, pFsp->CfgDecFsNum);
        STAT_DUMP(Page, "\n");
    }

    if (pFsp->CfgDispFsNum > 0)
    {
        TotalFree = 0;
        STAT_DUMP(Page, "---------------------------- DISP FS --------------------------\n");
        STAT_DUMP(Page, "%s  %s  %s  %s  %s  %s  %s  %s\n", "Num", "IsValid", "Tick", "IsRef", "LinkRef", "FsState", "Size", "Address");

        for (i = 0; i < pFsp->CfgDispFsNum; i++)
        {
            IsFree = FSP_IsDispFsAvailable(pFsp, &pFsp->stDispFsRec[i]);
            TotalFree += IsFree;

            STAT_DUMP(Page, " %d  %d  %d  %d  %d  %d  %d  0x%x  %s\n", pFsp->stDispFsRec[i].PhyFsID,
                      pFsp->stDispFsRec[i].IsValid,   pFsp->stDispFsRec[i].Tick,
                      pFsp->stDispFsRec[i].IsRef,     pFsp->stDispFsRec[i].LinkRef,
                      pFsp->stDispFsRec[i].FsState,   pFsp->stDispFsRec[i].BufSize,
                      pFsp->stDispFsRec[i].PhyAddr, (IsFree) ? "(Free)" : "");
        }

        STAT_DUMP(Page, "%s :%d/%d\n", "DispFs(Free/Total)", TotalFree, pFsp->CfgDispFsNum);
        STAT_DUMP(Page, "\n");
    }

    if (pFsp->CfgPmvNum > 0)
    {
        TotalFree = 0;
        STAT_DUMP(Page, "------------------------------ PMV ----------------------------\n");
        STAT_DUMP(Page, "%s  %s  %s  %s  %s  %s\n", "Num", "IsValid", "IsInUse", "HalfOffset", "Size", "Address");

        for (i = 0; i < pFsp->CfgPmvNum; i++)
        {
            IsFree = FSP_IsPmvAvailable(pFsp, &pFsp->stPmvRec[i]);
            TotalFree += IsFree;

            STAT_DUMP(Page, " %d  %d  %d  %d  %d  0x%x  %s\n", pFsp->stPmvRec[i].PmvIdc,
                      pFsp->stPmvRec[i].IsValid,       pFsp->stPmvRec[i].IsInUse,
                      pFsp->stPmvRec[i].PmvHalfOffset, pFsp->stPmvRec[i].PmvSize,
                      pFsp->stPmvRec[i].PmvAddr, (IsFree) ? "(Free)" : "");
        }

        STAT_DUMP(Page, "%s :%d/%d\n", "Pmv(Free/Total)", TotalFree, pFsp->CfgPmvNum);
        STAT_DUMP(Page, "\n");
    }

    if (pFsp->CfgMetadataNum > 0)
    {
        TotalFree = 0;
        STAT_DUMP(Page, "--------------------------- METADATA --------------------------\n");
        STAT_DUMP(Page, "%s  %s  %s  %s  %s  %s\n", "Num", "IsValid", "IsInUse", "IsOut", "Size", "Address");

        for (i = 0; i < pFsp->CfgMetadataNum; i++)
        {
            IsFree = FSP_IsMetadataAvailable(pFsp, &pFsp->stMetadataRec[i]);
            TotalFree += IsFree;

            STAT_DUMP(Page, " %d  %d  %d  %d  %d  0x%x  %s\n", pFsp->stMetadataRec[i].MetadataIdc,
                      pFsp->stMetadataRec[i].IsValid,      pFsp->stMetadataRec[i].IsInUse,
                      pFsp->stMetadataRec[i].IsOutHanging, pFsp->stMetadataRec[i].MetadataSize,
                      pFsp->stMetadataRec[i].MetadataAddr, (IsFree) ? "(Free)" : "");
        }

        STAT_DUMP(Page, "%s :%d/%d\n", "Metadata(Free/Total)", TotalFree, pFsp->CfgMetadataNum);
        STAT_DUMP(Page, "\n");
    }

    return UsedSize;
}

SINT32 SOS_PROC_ReadScd(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    SINT32 ret;
    SINT32 ChanId;
    SINT32 ModuleId;
    SINT32 SegUsedPercent;
    SINT32 RawNum, RawSize, SegNum, SegSize = 0, BufSize;
    SM_INSTANCE_S *pInst = NULL;
    SMDRV_PARAM_S *pScdDrvParam = NULL;
    VFMW_CHAN_S *pChan = NULL;

    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "--------------------------- SCD INFO --------------------------\n");

    for (ModuleId = 0; ModuleId < MAX_VDH_NUM; ModuleId++)
    {
        pScdDrvParam = &g_ScdDrvParam[ModuleId];
        STAT_DUMP(Page, "%s :%d\n",    "IsScdDrvOpen      ",  pScdDrvParam->IsScdDrvOpen);
        STAT_DUMP(Page, "%s :%d\n",    "SCDState          ",  pScdDrvParam->SCDState);
        STAT_DUMP(Page, "%s :%d\n",    "ThisInstID        ",  pScdDrvParam->ThisInstID);
        STAT_DUMP(Page, "%s :%d\n",    "LastProcessTime   ",  pScdDrvParam->LastProcessTime);
        STAT_DUMP(Page, "%s :0x%x\n",  "HwMemAddr         ",  pScdDrvParam->ScdDrvMem.HwMemAddr);
        STAT_DUMP(Page, "%s :%d\n",    "HwMemSize         ",  pScdDrvParam->ScdDrvMem.HwMemSize);
        STAT_DUMP(Page, "%s :0x%x\n",  "DownMsgMemAddr    ",  pScdDrvParam->ScdDrvMem.DownMsgMemAddr);
        STAT_DUMP(Page, "%s :0x%x\n",  "UpMsgMemAddr      ",  pScdDrvParam->ScdDrvMem.UpMsgMemAddr);
    }

    STAT_DUMP(Page, "\n");

    ChanId = g_CurProcChan;

    if (ChanId < 0 || ChanId >= MAX_CHAN_NUM)
    {
        dprint(PRN_ALWS, "ChanId %d invalid\n", ChanId);
        return UsedSize;
    }

    pChan = s_pstVfmwChan[ChanId];

    if (pChan == NULL)
    {
        dprint(PRN_ALWS, "Chan %d inactive\n", ChanId);
        return UsedSize;
    }

    pInst = s_SmIIS[ChanId].pSmInstArray;

    if (pInst == NULL || pInst->Mode == SM_INST_MODE_IDLE)
    {
        dprint(PRN_ALWS, "pInst %d invalid\n", ChanId);
        return UsedSize;
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

    STAT_DUMP(Page, "------------------------- STREAM INFO -------------------------\n");
    STAT_DUMP(Page, "%s :%d\n",      "Chan              ",    ChanId);
    STAT_DUMP(Page, "%s :%d\n",      "Mode              ",    pInst->Mode);
    STAT_DUMP(Page, "%s :%d\n",      "Cfg standard      ",    pChan->eVidStd);
    STAT_DUMP(Page, "%s :0x%x\n",    "Cfg buf addr      ",    pInst->Config.BufPhyAddr);
    STAT_DUMP(Page, "%s :%d\n",      "Cfg buf size      ",    pInst->Config.BufSize);
    STAT_DUMP(Page, "%s :0x%x\n",    "Seg read addr     ",    pInst->StreamSegArray.SegBufReadAddr);
    STAT_DUMP(Page, "%s :0x%x\n",    "Seg write addr    ",    pInst->StreamSegArray.SegBufWriteAddr);
    STAT_DUMP(Page, "%s :%d\n",      "Is counting       ",    pInst->IsCounting);
    STAT_DUMP(Page, "%s :%d\n",      "Is omx path       ",    pInst->Config.IsOmxPath);
    STAT_DUMP(Page, "%s :%d\n",      "Raw current size  ",    RawSize);
    STAT_DUMP(Page, "%s :%d\n",      "Raw current num   ",    RawNum);
    STAT_DUMP(Page, "%s :%d\n",      "Raw size count    ",    pInst->RawSizeCount);
    STAT_DUMP(Page, "%s :%d\n",      "Raw num count     ",    pInst->RawNumCount);
    STAT_DUMP(Page, "%s :%d\n",      "Seg current size  ",    SegSize);
    STAT_DUMP(Page, "%s :%d\n",      "Seg current num   ",    SegNum);
    STAT_DUMP(Page, "%s :%d%%\n",    "Seg used percent) ",    SegUsedPercent);
    STAT_DUMP(Page, "%s :%d Kbps\n", "Actual bitrate    ",    pInst->BitRate);
    STAT_DUMP(Page, "\n");
    STAT_DUMP(Page, "---------------------------------------------------------------\n");

    return UsedSize;
}

SINT32 SOS_PROC_ReadVdh(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    SINT32 i;
    SINT32 ChanId;
    SINT32 VdhId;
    UINT32 DecNum = 0;
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
        return UsedSize;
    }

    pFsp = FSP_GetInst(ChanId);

    if (pFsp == NULL)
    {
        dprint(PRN_ALWS, "FSP Chan %d invalid\n", ChanId);
        return UsedSize;
    }

    VdhId = g_ChanCtx.ChanDecByVdhPlusOne[ChanId] - 1;

    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    STAT_DUMP(Page, "--------------------------- VDH INFO --------------------------\n");

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

        STAT_DUMP(Page, "%s :%d\n",                  "VDH ID            ",  i);
        STAT_DUMP(Page, "%s :%d.%d%%\n",             "Load              ",  VdhLoad, pVfmwGlobalStat->u32VdhLoad % 10);
        STAT_DUMP(Page, "%s :%d.%d fps(Chan %d)\n",  "Frame Rate        ",  VdhFps,  pVfmwChanStat->u32FrFrameRate % 10, ChanId);
        STAT_DUMP(Page, "%s :%d/mb\n",               "Cycle State       ",  VdhCycle);
    }

    STAT_DUMP(Page, "\n");

    if (VdhId < 0)
    {
        STAT_DUMP(Page, "Chan %d NOT decoding.\n", ChanId);
    }
    else
    {
        STAT_DUMP(Page, "Chan %d decoding use VDH %d(%s).\n", ChanId, VdhId, \
                  (g_VdmExtParam[VdhId].VdmAttachStr.VdmAttachMode == VDMDRV_ATTACH_NULL) ? "Not_Attach" : "Attach");
    }

    STAT_DUMP(Page, "\n");

    STAT_DUMP(Page, "Decoding List & Priority Queue:\n");

    for (i = 0; i < MAX_CHAN_NUM; i++)
    {
        if (g_ChanCtx.ChanDecByVdhPlusOne[i] != 0)
        {
            STAT_DUMP(Page, "Chan %d decoding by %d\n", i, g_ChanCtx.ChanDecByVdhPlusOne[i] - 1);
        }

        if (g_ChanCtx.ChanIdTabByPrior[i] != -1)
        {
            STAT_DUMP(Page, "Chan %d priority is %d\n", i, g_ChanCtx.ChanIdTabByPrior[i]);
        }

        STAT_DUMP(Page, "\n");
    }

    STAT_DUMP(Page, "---------------------------------------------------------------\n");

    return UsedSize;
}

SINT32 SOS_PROC_ReadStatis(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    UINT32 TotalDiff = 0;
    UINT32 cycle = 0;
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;

    if (g_StatisticsEnable != 1)
    {
        STAT_DUMP(Page, "Statistics not enable\n");
        return 0;
    }

    OSAL_FP_memset(&diff, 0, sizeof(UINT32) * (7));

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    STAT_DUMP(Page, "---------------------------- VFMW STATICS (Unit:us)---------------\n");
    STAT_DUMP(Page, "Task\t SegCope(Size)\t RandTab  Syntax  VDH    IsrProcess   Wakeup\t fps\n");

    for (i = (MAX_RECORD_NUM - 1); i >= 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_END][i]        - g_TimeRecTable[THREAD_START][i]) / 1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_END][i]       - g_TimeRecTable[SEGCOPY_START][i]) / 1000;
        diff[2] = (g_TimeRecTable[MAP_END][i]           - g_TimeRecTable[MAP_START][i]) / 1000;
        diff[3] = (g_TimeRecTable[SYNTAX_END][i]        - g_TimeRecTable[SYNTAX_START][i]) / 1000;
        diff[4] = (g_TimeRecTable[VDH_HARDWARE_END][i]  - g_TimeRecTable[VDH_HARDWARE_START][i]) / 1000;
        diff[5] = (g_TimeRecTable[ISR_END][i]           - g_TimeRecTable[ISR_START][i]) / 1000;
        diff[6] = (g_TimeRecTable[NEXT_THREAD_START][i] - g_TimeRecTable[ISR_END][i]) / 1000;

        cycle = g_DataTable[VDH_DATA][i] / (345600) ;

        TotalDiff = (g_TimeRecTable[ISR_END][i] - g_TimeRecTable[SEGCOPY_START][i]);
        STAT_DUMP(Page, "%u   %u(%u)   %u   %u   %u(%u)   %u   %u || %d.%d fps ==> %u\n",
                  diff[0], diff[1], g_DataTable[COPY_SIZE_DATA][i], diff[2], diff[3], diff[4], cycle, diff[5], diff[6],
                  pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10, g_DataTable[VDH_DATA][i]);
    }

    STAT_DUMP(Page, "----------------------------------------------------------------\n");

    return UsedSize;
}

SINT32 SOS_PROC_ReadDiff(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;
    SINT32 i = 0;
    UINT32 ChanId;
    UINT32 diff[7];
    VFMW_CHAN_STAT_S *pVfmwChanStat = NULL;

    if (g_StatisticsEnable != 1)
    {
        STAT_DUMP(Page, "Statistics not enable\n");
        return 0;
    }

    OSAL_FP_memset(&diff, 0, sizeof(UINT32) * (7));

    ChanId = g_CurProcChan;
    pVfmwChanStat = &g_VfmwChanStat[ChanId];

    STAT_DUMP(Page, "---------------------------- VFMW STATICS (Unit:ms)---------------\n");
    STAT_DUMP(Page, "Task\t   SegCope(Size)\t    RandTab     Syntax     VDH       IsrProcess      Wakeup\t    fps\n");

    for (i = (MAX_RECORD_NUM - 1); i > 0; i--)
    {
        diff[0] = (g_TimeRecTable[THREAD_START][i]  - g_TimeRecTable[THREAD_START][i - 1]) / 1000;
        diff[1] = (g_TimeRecTable[SEGCOPY_START][i] - g_TimeRecTable[SEGCOPY_START][i - 1]) / 1000;
        diff[2] = (g_TimeRecTable[MAP_START][i]     - g_TimeRecTable[MAP_START][i - 1]) / 1000;
        diff[3] = (g_TimeRecTable[SYNTAX_START][i]  - g_TimeRecTable[SYNTAX_START][i - 1]);
        diff[4] = (g_TimeRecTable[VDH_HARDWARE_START][i]     - g_TimeRecTable[VDH_HARDWARE_START][i - 1]) / 1000;
        diff[5] = (g_TimeRecTable[ISR_START][i]     - g_TimeRecTable[ISR_START][i - 1]) / 1000;
        diff[6] = (g_TimeRecTable[VDH_HARDWARE_END][i]       - g_TimeRecTable[VDH_HARDWARE_START][i]) / 1000;
        STAT_DUMP(Page, "%u    %u    %u    %u    %u    %u   ==>   %u || %d.%d fps\n",
                  diff[0], diff[1], diff[2], diff[3], diff[4], diff[5], diff[6],
                  pVfmwChanStat->u32FrFrameRate / 10, pVfmwChanStat->u32FrFrameRate % 10);
    }

    STAT_DUMP(Page, "----------------------------------------------------------------\n");

    return UsedSize;
}

SINT32 SOS_PROC_Read(SINT8 *Page, SINT32 PageSize)
{
    SINT32 UsedSize = 0;

    switch (g_SecProcSelect)
    {
        case READ_PROC_CHAN:
            UsedSize = SOS_PROC_ReadChan(Page, PageSize);
            break;

        case READ_PROC_FSP:
            UsedSize = SOS_PROC_ReadFsp(Page, PageSize);
            break;

        case READ_PROC_SCD:
            UsedSize = SOS_PROC_ReadScd(Page, PageSize);
            break;

        case READ_PROC_VDH:
            UsedSize = SOS_PROC_ReadVdh(Page, PageSize);
            break;

        case READ_PROC_STATIS:
            UsedSize = SOS_PROC_ReadStatis(Page, PageSize);
            break;

        case READ_PROC_DIFF:
            UsedSize = SOS_PROC_ReadDiff(Page, PageSize);
            break;

        default:
            dprint(PRN_ALWS, "unsupport secure proc select %d\n", g_SecProcSelect);
            return UsedSize;
    }

    return UsedSize;
}

SINT32 SOS_PROC_Write(UINT32 Option, SINT32 Value)
{
    VCTRL_SetDbgOption(Option, (UINT8 *)(&Value));

    return VDEC_OK;
}

