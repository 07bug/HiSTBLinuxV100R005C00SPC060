/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_pvr_rec_ctrl.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/10
  Description   : RECORD module
  History       :
  1.Date        : 2008/04/10
    Author      : sdk
    Modification: Created file

******************************************************************************/

#include <errno.h>
#include <sched.h>
#include <pthread.h>
#include <signal.h>
#include "hi_type.h"
#include "hi_debug.h"
#include <malloc.h>
#include "hi_drv_struct.h"
#include "pvr_debug.h"
#include "hi_pvr_rec_ctrl.h"
#include "hi_pvr_play_ctrl.h"
#include "hi_pvr_intf.h"
#include "hi_pvr_index.h"
#include "hi_mpi_demux.h"
#include "hi_drv_pvr.h"
#include "hi_mpi_mem.h"
#include "hi_mpi_pvr.h"
#include <limits.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
//#define DUMP_DMX_DATA /*Set this flag  when you want watch the source data from demux,it will save these data in file linear*/
HI_S32 g_s32PvrFd = -1;      /*PVR file description used by recording and playback*/
char api_pathname_pvr[] = "/dev/" UMAP_DEVNAME_PVR;

#ifdef DUMP_DMX_DATA
static FILE* g_pvrfpTSReceive = NULL; /* handle of file */
static FILE* g_pvrfpIdxReceive = NULL; /* handle of file */
#endif

/* init flag of record module                                               */
STATIC PVR_REC_COMM_S g_stRecInit;

/* all information of record channel                                        */
STATIC PVR_REC_CHN_S g_stPvrRecChns[PVR_REC_MAX_CHN_NUM];

/*init flag of linear*/

static PVR_LINEARIZATION_CHN_S g_stPvrLinearizationChns[PVR_REC_MAX_CHN_NUM];

#define PVR_GET_RECPTR_BY_CHNID(chnId) (&g_stPvrRecChns[chnId - PVR_REC_START_NUM])
#define PVR_REC_IS_REWIND(pstRecAttr) ((pstRecAttr)->bRewind)
#define PVR_REC_IS_FIXSIZE(pstRecAttr) ((((pstRecAttr)->u64MaxFileSize > 0) || ((pstRecAttr)->u64MaxTimeInMs > 0)) && !((pstRecAttr)->bRewind))

static HI_S32 PVRRecFileLinearizationInit(HI_VOID);
static HI_S32 PVRRecFileLinearizationDeInit(HI_VOID);

#ifdef PVR_PROC_SUPPORT
static HI_PROC_ENTRY_S g_stPvrRecProcEntry;

static HI_S32 PVRRecShowProc(HI_PROC_SHOW_BUFFER_S* pstBuf, HI_VOID* pPrivData)
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 u32VidType = 0;
    PVR_REC_CHN_S* pChnAttr = g_stPvrRecChns;

    /*sream type definition, reference the HI_UNF_VCODEC_TYPE_E*/
    HI_S8 pStreamType[PVR_VIDEO_TYPE_TOTAL_NUM][32] = {"MPEG2", "MPEG4 DIVX4 DIVX5", "AVS", "H263", "H264",
            "REAL8", "REAL9", "VC-1", "VP6", "VP6F", "VP6A", "MJPEG",
            "SORENSON SPARK", "DIVX3", "RAW", "JPEG", "VP8", "MSMPEG4V1",
            "MSMPEG4V2", "MSVIDEO1", "WMV1", "WMV2", "RV10", "RV20",
            "SVQ1", "SVQ3", "H261", "VP3", "VP5", "CINEPAK", "INDEO2",
            "INDEO3", "INDEO4", "INDEO5", "MJPEGB", "MVC", "HEVC", "DV", "VP9", "INVALID"};

    /*pvr event type */
    HI_S8 pEventType[8][32] = {"DISKFUL", "ERROR", "OVER FIX", "REACH PLAY", "DISK SLOW", "REWIND_SWITCH", "LINEAR_SUCCESS", "RESV"};

#ifdef HI_TEE_PVR_SUPPORT
    /*TEE recording state.*/
    PVR_REC_SEC_OS_STATE_S* pstSecState = HI_NULL;
#endif
#ifdef PVR_PID_CHANGE_SUPPORT
    PVR_INDEX_PID_INFO_S* pstPidInfo = HI_NULL;
    HI_U32 u32PidStartNum = 0;
    HI_U32 k = 0;
#endif

    HI_PROC_Printf(pstBuf, "\n---------Hisilicon PVR Recording channel Info---------\n");

    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        /*check channel's state, only display active channel*/
        if ((pChnAttr[i].enState != HI_UNF_PVR_REC_STATE_INVALID) &&
            (pChnAttr[i].enState != HI_UNF_PVR_REC_STATE_STOPPING) &&
            (pChnAttr[i].enState != HI_UNF_PVR_REC_STATE_STOP) &&
            (pChnAttr[i].enState != HI_UNF_PVR_REC_STATE_BUTT))
        {
            if (pChnAttr[i].IndexHandle != HI_NULL)
            {
                u32VidType = PVR_Index_GetVtype(pChnAttr[i].IndexHandle) - 100;
                u32VidType = (u32VidType > (PVR_VIDEO_TYPE_TOTAL_NUM - 1)) ? (PVR_VIDEO_TYPE_TOTAL_NUM - 1) : u32VidType;
            }

            HI_PROC_Printf(pstBuf, "chan %d infomation:\n", i);
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
            if (pChnAttr[i].RecordCacheThread != HI_NULL)
            {
                HI_PROC_Printf(pstBuf, "\tUse Extra Buffer  :%s\n", "Yes");
                HI_PROC_Printf(pstBuf, "\tExtra Buffer      :%u-bytes\n", 2 * pChnAttr[i].stUserCfg.u32DavBufSize);
#ifdef HI_PVR_FIFO_DIO
                HI_PROC_Printf(pstBuf, "\tDirectIO support  :%s\n", "Yes");
#else
                HI_PROC_Printf(pstBuf, "\tDirectIO support  :%s\n", "No");
#endif
            }
            else
#endif
                HI_PROC_Printf(pstBuf, "\tUse Extra Buffer   :%s\n", "No");

            HI_PROC_Printf(pstBuf, "\tRec filename      :%s\n", pChnAttr[i].stUserCfg.szFileName);
            HI_PROC_Printf(pstBuf, "\tStream type       :%s\n", pStreamType[u32VidType]);
            if (HI_NULL != pChnAttr[i].IndexHandle)
            {
                HI_PROC_Printf(pstBuf, "\tStream packet Size:%d\n", PVR_INDEX_GET_TSPACKET_SIZE(pChnAttr[i].IndexHandle));
            }
            HI_PROC_Printf(pstBuf, "\tDemuxID           :%d\n", pChnAttr[i].stUserCfg.u32DemuxID);
#ifdef PVR_APPEND_MODE_SUPPORT
            if (HI_NULL != pChnAttr[i].IndexHandle)
            {
                HI_PROC_Printf(pstBuf, "\tAppend rec        :%d/%d (User/Actually)\n", pChnAttr[i].stUserCfg.bAppendRec, pChnAttr[i].IndexHandle->stAppendRecordInfo.bAppend);
                if (HI_TRUE == pChnAttr[i].IndexHandle->stAppendRecordInfo.bAppend)
                {
                    HI_PROC_Printf(pstBuf, "\tPrev rec S/E/L    :%d/%d/%d\n", pChnAttr[i].IndexHandle->stAppendRecordInfo.u32StartFrame, pChnAttr[i].IndexHandle->stAppendRecordInfo.u32EndFrame,
                                                                                pChnAttr[i].IndexHandle->stAppendRecordInfo.u32LastFrame);
                    HI_PROC_Printf(pstBuf, "\tPrev rec Time     :%d\n", pChnAttr[i].IndexHandle->stAppendRecordInfo.u32LastDisplayTime);
                }
            }
#endif

            HI_PROC_Printf(pstBuf, "\tRecord State      :%d\n", pChnAttr[i].enState);
            HI_PROC_Printf(pstBuf, "\tRewind            :%d\n", pChnAttr[i].stUserCfg.bRewind);
            if (HI_TRUE == pChnAttr[i].stUserCfg.bRewind)
            {
                if (PVR_INDEX_REWIND_BY_TIME == pChnAttr[i].IndexHandle->stCycMgr.enRewindType)
                {

                    HI_PROC_Printf(pstBuf, "\tRewind Type       :%s\n", "TIME");
                    HI_PROC_Printf(pstBuf, "\tRewind time       :%d\n", pChnAttr[i].IndexHandle->stCycMgr.u32MaxCycTimeInMs);
                }
                else if (PVR_INDEX_REWIND_BY_SIZE == pChnAttr[i].IndexHandle->stCycMgr.enRewindType)
                {
                    HI_PROC_Printf(pstBuf, "\tRewind Type       :%s\n", "SIZE");
                    HI_PROC_Printf(pstBuf, "\tRewind size       :%#llx\n", pChnAttr[i].IndexHandle->stCycMgr.u64MaxCycSize);
                }
                else
                {
                    HI_PROC_Printf(pstBuf, "\tRewind Type       :%s\n", "SIZE and TIME");
                    HI_PROC_Printf(pstBuf, "\tRewind size       :%#llx\n", pChnAttr[i].IndexHandle->stCycMgr.u64MaxCycSize);
                    HI_PROC_Printf(pstBuf, "\tRewind time       :%d\n", pChnAttr[i].IndexHandle->stCycMgr.u32MaxCycTimeInMs);
                }

                HI_PROC_Printf(pstBuf, "\tRewind times      :%d\n", pChnAttr[i].IndexHandle->stCycMgr.u32CycTimes);
            }
            HI_PROC_Printf(pstBuf, "\tMax size          :%#llx\n", pChnAttr[i].stUserCfg.u64MaxFileSize);
            HI_PROC_Printf(pstBuf, "\tMax time          :%#lld\n", pChnAttr[i].stUserCfg.u64MaxTimeInMs);
            HI_PROC_Printf(pstBuf, "\tUserData size     :%d\n", pChnAttr[i].stUserCfg.u32UsrDataInfoSize);
            HI_PROC_Printf(pstBuf, "\tClearStream       :%d\n", pChnAttr[i].stUserCfg.bIsClearStream);
            HI_PROC_Printf(pstBuf, "\tIndexType         :%d\n", pChnAttr[i].stUserCfg.enIndexType);
            HI_PROC_Printf(pstBuf, "\tIndexPid          :%#x/%d\n", pChnAttr[i].stUserCfg.u32IndexPid, pChnAttr[i].stUserCfg.u32IndexPid);
            if (pChnAttr[i].IndexHandle != HI_NULL)
            {
                HI_U64 u64GlobalOffset = 0;
                HI_U64 u64Offset = 0;
                HI_U32 u32DisplayTimeMs = 0;
                PVR_Index_GetIndexInfo(pChnAttr->IndexHandle, &pChnAttr[i].IndexHandle->stCurRecFrame, PVR_INDEX_GLOBAL_OFFSET, &u64GlobalOffset);
                PVR_Index_GetIndexInfo(pChnAttr->IndexHandle, &pChnAttr[i].IndexHandle->stCurRecFrame, PVR_INDEX_OFFSET, &u64Offset);
                PVR_Index_GetIndexInfo(pChnAttr->IndexHandle, &pChnAttr[i].IndexHandle->stCurRecFrame, PVR_INDEX_DISP_TIME, &u32DisplayTimeMs);
                HI_PROC_Printf(pstBuf, "\tGlobal offset     :%#llx\n", u64GlobalOffset);
                HI_PROC_Printf(pstBuf, "\tFile offset       :%#llx\n", u64Offset);
                HI_PROC_Printf(pstBuf, "\tIndex Write       :%d\n", pChnAttr[i].IndexHandle->u32WriteFrame);
                HI_PROC_Printf(pstBuf, "\tCurrentTime(ms)   :%d\n", u32DisplayTimeMs);
                HI_PROC_Printf(pstBuf, "\tIndexPos S/E/L    :%d/%d/%d\n", pChnAttr[i].IndexHandle->stCycMgr.u32StartFrame,
                               pChnAttr[i].IndexHandle->stCycMgr.u32EndFrame,
                               pChnAttr[i].IndexHandle->stCycMgr.u32LastFrame);
            }
#ifdef HI_TEE_PVR_SUPPORT
            HI_PROC_Printf(pstBuf, "\tTee State:");
            if (HI_UNF_PVR_SECURE_MODE_TEE == pChnAttr[i].stUserCfg.enSecureMode)
            {
                HI_PROC_Printf(pstBuf, "Yes!\n");
                pstSecState = (PVR_REC_SEC_OS_STATE_S*)pChnAttr[i].stTeeState.pUserAddr;
                pstSecState->u32ReeBufLen = pChnAttr[i].stReeBuff.u32Size;
                HI_PROC_Printf(pstBuf, "\t[TEE]u32TeeChnId             :%04d\n",
                               pChnAttr[i].u32TeeChnId);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32ReeBufAddr           :%p(0x%08x)\n",
                               pChnAttr[i].stReeBuff.pUserAddr, pChnAttr[i].stReeBuff.u32SmmuAddr);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32ReeBufLen            :%u\n",
                               pstSecState->u32ReeBufLen);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32TeeBufAddr           :0x%08x\n",
                               pstSecState->u32TeeBufAddr);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32TeeBufLen            :%u\n",
                               pstSecState->u32TeeBufLen);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32TeeReadPos           :%u\n",
                               pstSecState->u32TeeReadPos);
                HI_PROC_Printf(pstBuf, "\t[TEE]u32TeeWritePos          :%u\n",
                               pstSecState->u32TeeWritePos);
                HI_PROC_Printf(pstBuf, "\t[TEE]s32InsertTsPacketNum    :%d\n",
                               pstSecState->s32InsertTsPacketNum);
                HI_PROC_Printf(pstBuf, "\t[TEE]u64DataGlobalOffset     :%#llx\n",
                               pstSecState->u64DataGlobalOffset);
                HI_PROC_Printf(pstBuf, "\t[TEE]u64BaseGlobalOffset     :%#llx\n",
                               pstSecState->u64BaseGlobalOffset);
                HI_PROC_Printf(pstBuf, "\t[TEE]bUsedNext               :%s\n",
                               (HI_TRUE == pstSecState->bUsedNext) ? "true" : "false");
                HI_PROC_Printf(pstBuf, "\t[TEE]u64NextAdjustOffset     :%#llx\n",
                               pstSecState->u64NextAdjustOffset);
                HI_PROC_Printf(pstBuf, "\t[TEE]u64NextOldOffset        :%#llx\n",
                               pstSecState->u64NextOldOffset);
            }
            else
            {
                HI_PROC_Printf(pstBuf, "No!\n");
            }
#endif
#ifdef PVR_PID_CHANGE_SUPPORT
            HI_PROC_Printf(pstBuf, "\n\tPid Change Ctrl:\n");
            if (HI_NULL != pChnAttr[i].IndexHandle)
            {
                HI_PROC_Printf(pstBuf, "\t  ChangeTimes     :%u\n",pChnAttr[i].IndexHandle->pstPidCtrl->u32UsedNum);

                if (pChnAttr[i].IndexHandle->pstPidCtrl->u32UsedNum <= 6)
                {
                    u32PidStartNum = 0;
                }
                else
                {
                    u32PidStartNum = pChnAttr[i].IndexHandle->pstPidCtrl->u32UsedNum - 6;
                }

                for (j = u32PidStartNum; j < pChnAttr[i].IndexHandle->pstPidCtrl->u32UsedNum; j++)
                {
                    pstPidInfo = &pChnAttr[i].IndexHandle->pstPidCtrl->stPidInfo[j];
                    u32VidType = pstPidInfo->u32VideoType;
                    u32VidType = (u32VidType > (PVR_VIDEO_TYPE_TOTAL_NUM - 1)) ? (PVR_VIDEO_TYPE_TOTAL_NUM - 1) : u32VidType;
                    HI_PROC_Printf(pstBuf, "\t  %u - S/E         :%u(%u) / %u(%u)\n",j, pstPidInfo->u32StartFrame, pstPidInfo->u32StartDispTime, pstPidInfo->u32EndFrame, pstPidInfo->u32EndDispTime);
                    HI_PROC_Printf(pstBuf, "\t       Index Pid  :%u\n",pstPidInfo->u32IndexPid);
                    HI_PROC_Printf(pstBuf, "\t       Video Type :%s\n",pStreamType[u32VidType]);
                    HI_PROC_Printf(pstBuf, "\t       PidList    :");
                    for (k = 0; k < 6; k++)
                    {
                        HI_PROC_Printf(pstBuf, " %d",pstPidInfo->u32PidList[k]);
                    }
                    HI_PROC_Printf(pstBuf, "\n");
                }
            }
#endif
            HI_PROC_Printf(pstBuf, "\tEvent history\n");
            for (j = 0; j < PVR_REC_EVENT_HISTORY_NUM; j++)
            {
                if (pChnAttr[i].stEventHistory.u32Write < PVR_REC_EVENT_HISTORY_NUM)
                {
                    if (pChnAttr[i].stEventHistory.enEventHistory[j] != HI_UNF_PVR_EVENT_BUTT)
                    { HI_PROC_Printf(pstBuf, "\t  Event         :%s\n", pEventType[pChnAttr[i].stEventHistory.enEventHistory[j] & 0x7]); }
                }
                else
                {
                    HI_PROC_Printf(pstBuf, "\t  Event         :%s\n",
                                   pEventType[pChnAttr[i].stEventHistory.enEventHistory[(pChnAttr[i].stEventHistory.u32Write + j) % PVR_REC_EVENT_HISTORY_NUM] & 0x7]);
                }
            }
        }
    }

    return HI_SUCCESS;
}
#endif

STATIC INLINE HI_S32 PVRRecDevInit(HI_VOID)
{
    int fd;

    if (-1 == g_s32PvrFd)
    {
        fd = open (api_pathname_pvr, O_RDWR, 0);

        if (fd < 0)
        {
            HI_FATAL_PVR("Cannot open '%s'\n", api_pathname_pvr);
            return HI_FAILURE;
        }

        g_s32PvrFd = fd;
    }

    return HI_SUCCESS;
}

/*
* find free recording channel, in order to support mulit process, the channel is managed by kernel
* return the pointer of channel if success, othersize return HI_NULL
*/
STATIC INLINE PVR_REC_CHN_S* PVRRecFindFreeChn(HI_VOID)
{
    PVR_REC_CHN_S* pChnAttr = HI_NULL;

#if 0 /* not support multi-process */
    HI_U32 i;

    /* find a free play channel */
    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        if (g_stPvrRecChns[i].enState == HI_UNF_PVR_REC_STATE_INVALID)
        {
            pChnAttr = &g_stPvrRecChns[i];
            pChnAttr->enState = HI_UNF_PVR_REC_STATE_INIT;
            break;
        }
    }

#else /* support multi-process by kernel manage resources */
    HI_U32 ChanId;
    if (HI_SUCCESS != ioctl(g_s32PvrFd, CMD_PVR_CREATE_REC_CHN, &ChanId))
    {
        HI_FATAL_PVR("pvr rec creat channel error\n");
        return HI_NULL;
    }

    HI_ASSERT(g_stPvrRecChns[ChanId].enState == HI_UNF_PVR_REC_STATE_INVALID);
    pChnAttr = &g_stPvrRecChns[ChanId];

    PVR_LOCK(&(pChnAttr->stMutex));
    pChnAttr->enState = HI_UNF_PVR_REC_STATE_INIT;
    pChnAttr->RecordFileThread = 0;
    pChnAttr->RecordCacheThread = 0;
    pChnAttr->ChangeRewindThread = 0;
    PVR_UNLOCK(&(pChnAttr->stMutex));
#endif


    return pChnAttr;
}

STATIC INLINE HI_S32 PVRRecCheckAllTsCfg(const HI_UNF_PVR_REC_ATTR_S* pUserCfg)
{
    /*As the API is called by the func located in the same file, we don't check the input pointer*/

    /* all ts record, just only used for analysing, not supported cipher and rewind */
    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pUserCfg->enStreamType)
    {
        if (pUserCfg->bRewind || pUserCfg->stEncryptCfg.bDoCipher)
        {
            HI_ERR_PVR("All Ts record can't support rewind or ciphter\n");
            return HI_ERR_PVR_INVALID_PARA;
        }
    }
    return HI_SUCCESS;
}
STATIC INLINE HI_S32 PVRRecCheckRecBufCfg(const HI_UNF_PVR_REC_ATTR_S* pUserCfg)
{
    /*As the API is called by the func located in the same file, we don't check the input pointer*/
    HI_U32 u32TsPKSize = PVR_GET_TSPACKET_SIZE_BY_TYPE(pUserCfg->enTsPacketType);

    /*check recording buffer'size and this argument will be told to demux*/
    if ((((HI_U64)pUserCfg->u32DavBufSize) % PVR_FIFO_WRITE_BLOCK_SIZE(u32TsPKSize))
        || (!((pUserCfg->u32DavBufSize >= PVR_REC_MIN_DAV_BUF_LEN(u32TsPKSize))
              && (pUserCfg->u32DavBufSize <= PVR_REC_MAX_DAV_BUF_LEN(u32TsPKSize)))))
    {
        HI_ERR_PVR("invalid dav buf size:%u;the size should align %llu, and bigger than %u, less than %u\n",
                   pUserCfg->u32DavBufSize, PVR_FIFO_WRITE_BLOCK_SIZE(u32TsPKSize), PVR_REC_MIN_DAV_BUF_LEN(u32TsPKSize), PVR_REC_MAX_DAV_BUF_LEN(u32TsPKSize));
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*This argument won't be used now. it's used for 3716MV300 or before,  however, the argument is located in hi_unf_pvr.h, so we keep it*/
    if ((pUserCfg->u32ScdBufSize % 28)
        || (!((pUserCfg->u32ScdBufSize >= PVR_REC_MIN_SC_BUF)
              && (pUserCfg->u32ScdBufSize <= PVR_REC_MAX_SC_BUF))))
    {
        HI_ERR_PVR("invalid scd buf size:%u\n", pUserCfg->u32ScdBufSize);
        return HI_ERR_PVR_INVALID_PARA;
    }

    return HI_SUCCESS;
}
STATIC INLINE HI_S32 PVRRecCheckRewindCfg(const HI_UNF_PVR_REC_ATTR_S* pUserCfg)
{
    /*As the API is called by the func located in the same file, we don't check the input pointer*/
    /*suggest app that memset the HI_UNF_PVR_REC_ATTR_S before initialze it, because uninitialzed value my cause checking to fail. */

    /* check for cycle record. for cycle record, the length should more than PVR_MIN_CYC_SIZE, and it MUST not be zero */
    if (PVR_REC_IS_REWIND(pUserCfg))
    {
        if ((pUserCfg->u64MaxFileSize < PVR_MIN_CYC_SIZE)
            && (pUserCfg->u64MaxTimeInMs < PVR_MIN_CYC_TIMEMS))
        {
            HI_ERR_PVR("record file rewind, but file size:%llu(time:%llu) less than %llu(%llu).\n",
                       pUserCfg->u64MaxFileSize, pUserCfg->u64MaxTimeInMs, PVR_MIN_CYC_SIZE, PVR_MIN_CYC_TIMEMS);
            return HI_ERR_PVR_REC_INVALID_FSIZE;
        }
#ifdef PVR_APPEND_MODE_SUPPORT
        /*Append record not support rewind*/
        if (HI_TRUE == pUserCfg->bAppendRec)
        {
            HI_ERR_PVR("append record not support rewind! \n");
            return HI_ERR_PVR_NOT_SUPPORT;
        }
#endif
    }
    else
    {
        /* the length too less and not equal zero. zero means no limited */
        if (((pUserCfg->u64MaxFileSize > 0) && (pUserCfg->u64MaxFileSize < PVR_MIN_CYC_SIZE))
            || ((pUserCfg->u64MaxTimeInMs > 0) && (pUserCfg->u64MaxTimeInMs < PVR_MIN_CYC_TIMEMS)))
        {
            HI_ERR_PVR("record file not rewind, but file size:%llu(time:%llu) less than %llu(%llu) and not 0.\n",
                       pUserCfg->u64MaxFileSize, pUserCfg->u64MaxTimeInMs, PVR_MIN_CYC_SIZE, PVR_MIN_CYC_TIMEMS);
            return HI_ERR_PVR_REC_INVALID_FSIZE;
        }
    }
    return HI_SUCCESS;
}
STATIC INLINE HI_S32 PVRRecCheckDemuxCfg(const HI_UNF_PVR_REC_ATTR_S* pUserCfg)
{
    HI_U32 i;
    HI_SYS_VERSION_S stSysVer;

    /*some chip support mult recordings for the same demux, some chip don't, so the chipset info must be got first*/
    memset(&stSysVer, 0x00, sizeof(stSysVer));
    if (HI_SUCCESS != HI_SYS_GetVersion(&stSysVer))
    {
        HI_FATAL_PVR("Cannot get system version\n");
        return HI_FAILURE;
    }
    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        /* check whether the demux id used or not */
        if (HI_UNF_PVR_REC_STATE_INVALID != g_stPvrRecChns[i].enState)
        {
            /*3716MV410,3716MV420, 3798CV200*/
            switch (stSysVer.enChipTypeHardWare)
            {
                case HI_CHIP_TYPE_HI3716M:
                    if ((HI_CHIP_VERSION_V410 == stSysVer.enChipVersion) ||
                        (HI_CHIP_VERSION_V420 == stSysVer.enChipVersion))
                    { break; }
                case HI_CHIP_TYPE_HI3798C:
                    if (HI_CHIP_VERSION_V200 == stSysVer.enChipVersion)
                    { break; }
                case HI_CHIP_TYPE_HI3796M:
                    if (HI_CHIP_VERSION_V200 == stSysVer.enChipVersion)
                    { break; }
                default:
                    if (g_stPvrRecChns[i].stUserCfg.u32DemuxID == pUserCfg->u32DemuxID)
                    {
                        HI_ERR_PVR("demux %d already has been used to record.\n", pUserCfg->u32DemuxID);
                        return HI_ERR_PVR_ALREADY;
                    }
                    break;
            }

            /* recording for the same file name or not, different channel must use different filename*/
            if (0 == strncmp(g_stPvrRecChns[i].stUserCfg.szFileName, pUserCfg->szFileName, sizeof(pUserCfg->szFileName)))
            {
                HI_ERR_PVR("file %s was exist to be recording.\n", pUserCfg->szFileName);
                return HI_ERR_PVR_FILE_EXIST;
            }
        }
    }
    return HI_SUCCESS;
}

/*
  *�����ļ����������������:
  *1��"/xx/filename"
  *2��"/filename"
  *3��"filename"
*/
static HI_S32 PVRRecTransformFileName(HI_CHAR* pszFileName)
{
    HI_CHAR*  p = HI_NULL;
    HI_CHAR szAbsoluteDirName[PATH_MAX] = {0};
    HI_CHAR szOppositeDirName[PVR_MAX_FILENAME_LEN] = {0};
    HI_CHAR szFileName[PVR_MAX_FILENAME_LEN] = {0};
    HI_U32 u32OppositeDirLen = 0;
    HI_U32 u32SrcFileLen = strlen(pszFileName);

    HI_WARN_PVR("PATH_MAX : %u\n", PATH_MAX);
    p = strrchr(pszFileName, '/');

    if (NULL == p)
    {/*3��"fileName"  */
        snprintf(szOppositeDirName, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR), "%s", ".");
        memcpy(szFileName, pszFileName, u32SrcFileLen * sizeof(HI_CHAR));
        u32OppositeDirLen = 1;
    }
    else
    {
        u32OppositeDirLen = (HI_U32)(p - pszFileName);
        if (0 == u32OppositeDirLen)
        {/*2��"/fileName"  */
            snprintf(szOppositeDirName, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR), "%s", "/");
        }
        else
        {/*1��"/xx/filename"  */
            memcpy(szOppositeDirName, pszFileName, u32OppositeDirLen * sizeof(HI_CHAR));
        }

        memcpy(szFileName, ++p, (u32SrcFileLen - u32OppositeDirLen - 1) * sizeof(HI_CHAR));
    }

    szFileName[PVR_MAX_FILENAME_LEN - 1] = '\0';
    if (0 != u32OppositeDirLen)
    {
        szOppositeDirName[PVR_MAX_FILENAME_LEN - 1] = '\0';
        if(HI_NULL == realpath(szOppositeDirName, szAbsoluteDirName))
        {
            HI_ERR_PVR("get real path failed! dirName: %s\n", szOppositeDirName);
            return HI_FAILURE;
        }
    }

    HI_WARN_PVR("szOppositeDirName: %s, szAbsoluteDirName: %s, szFileName: %s\n",szOppositeDirName, szAbsoluteDirName, szFileName);
    if((strlen(szAbsoluteDirName) + strlen(szFileName) + 1) >= PVR_MAX_FILENAME_LEN)
    {
        HI_ERR_PVR("Absolute path is too long, transform fileName failed! (AbsolutePathLen, SrcPathLen): (%u, %u)\n",
                        strlen(szAbsoluteDirName), strlen(szFileName));
        return HI_FAILURE;
    }

    memset(pszFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
    snprintf(pszFileName, PVR_MAX_FILENAME_LEN - 1, "%s/%s", szAbsoluteDirName, szFileName);

    return HI_SUCCESS;
}

STATIC INLINE HI_S32 PVRRecCheckUserCfg(HI_UNF_PVR_REC_ATTR_S* pUserCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    /*As the API is called by the func located in the same file, we don't check the input pointer*/

    CHECK_REC_DEMUX_ID((HI_S32)(pUserCfg->u32DemuxID));

    /*PES recording is not supported.*/
    if ((HI_UNF_PVR_STREAM_TYPE_TS != pUserCfg->enStreamType)
        && (HI_UNF_PVR_STREAM_TYPE_ALL_TS != pUserCfg->enStreamType))
    {
        HI_ERR_PVR("enStreamType error, not support this stream type:(%d)\n", pUserCfg->enStreamType);
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*check for all ts recording*/
    s32Ret = PVRRecCheckAllTsCfg(pUserCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (pUserCfg->enTsPacketType >= HI_UNF_PVR_TS_PACKET_BUTT)
    {
        HI_ERR_PVR("Ts Package Type is invalid! Type: %x\n", pUserCfg->enTsPacketType);
        return HI_ERR_PVR_INVALID_PARA;
    }

#ifdef HI_TEE_PVR_SUPPORT
    /*TEE recording require that app register callback to pvr, so the encryption can be done in the callback*/
    if ((pUserCfg->stEncryptCfg.bDoCipher)
        && (HI_UNF_PVR_SECURE_MODE_TEE == pUserCfg->enSecureMode))
    {
        HI_ERR_PVR("For tvp: recording don't support to use cipher to encrypt the data, Please use the callback!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    if ((HI_UNF_PVR_TS_PACKET_192 == pUserCfg->enTsPacketType) && (HI_UNF_PVR_SECURE_MODE_TEE == pUserCfg->enSecureMode))
    {
        HI_ERR_PVR("tee pvr not support 192 packet type!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }
#endif

    if (pUserCfg->enIndexType >= HI_UNF_PVR_REC_INDEX_TYPE_BUTT)
    {
        HI_ERR_PVR("pUserCfg->enIndexType(%d) >= HI_UNF_PVR_REC_INDEX_TYPE_BUTT\n", pUserCfg->enIndexType);
        return HI_ERR_PVR_INVALID_PARA;
    }


    if (HI_UNF_PVR_REC_INDEX_TYPE_VIDEO == pUserCfg->enIndexType)
    {
        /*for video  index, only some stream types are supported, this is done by demux. here pvr check it using HI_UNF_VCODEC_TYPE_E*/
        if (pUserCfg->enIndexVidType >= HI_UNF_VCODEC_TYPE_BUTT)
        {
            HI_ERR_PVR("pUserCfg->enIndexVidType(%d) >= HI_UNF_VCODEC_TYPE_BUTT\n", pUserCfg->enIndexVidType);
            return HI_ERR_PVR_INVALID_PARA;
        }
    }

    /*check for recording buffer and scd buffer*/
    s32Ret = PVRRecCheckRecBufCfg(pUserCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /*check the cipher'info*/
    PVR_CHECK_CIPHER_CFG(&pUserCfg->stEncryptCfg);

    /*  if record file name ok */
    if (((strlen(pUserCfg->szFileName)) >= PVR_MAX_FILENAME_LEN)
        || (strlen(pUserCfg->szFileName) != pUserCfg->u32FileNameLen))
    {
        HI_ERR_PVR("Invalid file name, file name len=%d!\n", pUserCfg->u32FileNameLen);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }

    if(HI_SUCCESS != PVRRecTransformFileName(pUserCfg->szFileName))
    {
        HI_ERR_PVR("get real fileName failed! \n");
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }
    pUserCfg->u32FileNameLen = strlen(pUserCfg->szFileName);

    if (pUserCfg->u32UsrDataInfoSize > PVR_MAX_USERDATA_LEN)
    {
        HI_ERR_PVR("u32UsrDataInfoSize(%u) too larger\n", pUserCfg->u32UsrDataInfoSize);
        return HI_ERR_PVR_REC_INVALID_UDSIZE;
    }

    s32Ret = PVRRecCheckRewindCfg(pUserCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = PVRRecCheckDemuxCfg(pUserCfg);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

#ifdef PVR_APPEND_MODE_SUPPORT
    if (HI_TRUE != pUserCfg->bAppendRec)
#endif
    {
        HI_PVR_RemoveFile(pUserCfg->szFileName);
    }

    return HI_SUCCESS;
}
#ifndef PVR_ACQUIREDATAINDX

/*for async APIs, demux won't report overflow, so pvr has to check the record buffer always*/
STATIC HI_S32 PVRRecCheckRecBufStatus(HI_U32 u32CurOverflowTimes, PVR_REC_CHN_S* pRecChn)
{
    HI_U32 u32OverflowTimes = u32CurOverflowTimes;
    HI_UNF_DMX_RECBUF_STATUS_S stRecBufStatus;

    memset(&stRecBufStatus, 0x00, sizeof(stRecBufStatus));

    if (HI_SUCCESS == HI_UNF_DMX_GetRecBufferStatus(pRecChn->DemuxRecHandle, &stRecBufStatus))
    {
        /* used size large than 90% of ts buffer for 3 times */
        if (stRecBufStatus.u32UsedSize > stRecBufStatus.u32BufSize * 90 / 100)
        {
            u32OverflowTimes++;
            if (u32OverflowTimes > 3)
            {
                u32OverflowTimes = 0;
                PVR_Intf_DoEventCallback(pRecChn->u32ChnID, HI_UNF_PVR_EVENT_REC_DISK_SLOW, 0);
                PVR_Intf_AddEventHistory(&pRecChn->stEventHistory, HI_UNF_PVR_EVENT_REC_DISK_SLOW);
            }
        }
        else
        {
            u32OverflowTimes = 0;
        }
    }

    return u32OverflowTimes;
}
#endif
#if 0
/*TEE and HEVC recording, demux mix the index and record data may cause overflow, so mixing may be done by pvr*/
static HI_S32 PVRRecMixRecDataAndIndex(HI_MPI_DMX_REC_DATA_INDEX_S* Old, HI_MPI_DMX_REC_DATA_INDEX_S* New)
{
    if (1 != New->u32RecDataCnt)
    {
        HI_ERR_PVR("\t New->u32RecDataCnt = %u\n", New->u32RecDataCnt);
    }
    if (Old->u32IdxNum + New->u32IdxNum > DMX_MAX_IDX_ACQUIRED_EACH_TIME)
    {
        HI_ERR_PVR("(old, new) = (%u, %u)\n", Old->u32IdxNum, New->u32IdxNum);
    }

    if (1 == Old->u32RecDataCnt)
    {
        if (Old->stRecData[0].u32DataPhyAddr + Old->stRecData[0].u32Len == New->stRecData[0].u32DataPhyAddr)
        {
            Old->stRecData[0].u32Len += New->stRecData[0].u32Len;
        }
        else
        {
            Old->u32RecDataCnt = 2;

            Old->stRecData[1].pDataAddr = New->stRecData[0].pDataAddr;
            Old->stRecData[1].u32DataPhyAddr = New->stRecData[0].u32DataPhyAddr;
            Old->stRecData[1].u32Len = New->stRecData[0].u32Len;
        }

        memcpy(&Old->stIndex[Old->u32IdxNum], &New->stIndex[0], sizeof(HI_MPI_DMX_REC_INDEX_S) * New->u32IdxNum);
        Old->u32IdxNum += New->u32IdxNum;
    }
    else
    {
        if (2 != Old->u32RecDataCnt)
        {
            HI_ERR_PVR("Old->u32RecDataCnt = %u\n", Old->u32RecDataCnt);
        }

        if (Old->stRecData[1].u32DataPhyAddr + Old->stRecData[1].u32Len == New->stRecData[0].u32DataPhyAddr)
        {
            Old->stRecData[1].u32Len += New->stRecData[0].u32Len;
        }
        else
        {
            HI_ERR_PVR("(new, old0, old1) = (%#x, %u, %#x, %u, %#x, %u)",
                       New->stRecData[0].u32DataPhyAddr,
                       New->stRecData[0].u32Len,
                       Old->stRecData[0].u32DataPhyAddr,
                       Old->stRecData[0].u32Len,
                       Old->stRecData[1].u32DataPhyAddr,
                       Old->stRecData[1].u32Len);
        }

        memcpy(&Old->stIndex[Old->u32IdxNum], &New->stIndex[0], sizeof(HI_MPI_DMX_REC_INDEX_S) * New->u32IdxNum);
        Old->u32IdxNum += New->u32IdxNum;
    }

    return HI_SUCCESS;
}
#endif
STATIC HI_S32 PVRRecRequireDataAndIndex(PVR_REC_CHN_S* pChnAttr, HI_MPI_DMX_REC_DATA_INDEX_S* pstRecDataIdx)
{
#ifdef PVR_PID_CHANGE_SUPPORT
    if (HI_TRUE == pChnAttr->bChangingPid)
    {
        pChnAttr->enState = HI_UNF_PVR_REC_STATE_PID_CHANGE;
        pChnAttr->bChangingPid = HI_FALSE;
        return HI_ERR_DMX_TIMEOUT;
    }
    if (HI_UNF_PVR_REC_STATE_PID_CHANGE == pChnAttr->enState)
    {
        HI_WARN_PVR("PID is changing.... \n");
        return HI_ERR_DMX_TIMEOUT;
    }
#endif
#if 1
    return HI_MPI_DMX_AcquireRecDataAndIndex(pChnAttr->DemuxRecHandle, pstRecDataIdx);
#else
    /*TEE and HEVC recording, demux mix the index and record data may cause overflow, so mixing may be done by pvr*/

    HI_BOOL bRequireMore = HI_TRUE;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_MPI_DMX_REC_DATA_INDEX_S* pstTemp = HI_NULL;

#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE == pChnAttr->stUserCfg.enSecureMode)
    {
        bRequireMore = HI_FALSE;
    }
#endif

    memset(pstRecDataIdx, 0x00, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
    s32Ret = HI_MPI_DMX_AcquireRecDataAndIndex(pChnAttr->DemuxRecHandle, pstRecDataIdx);
    if (HI_SUCCESS != s32Ret)
    {
        goto out;
    }
    pstTemp = (HI_MPI_DMX_REC_DATA_INDEX_S*)HI_MALLOC(HI_ID_PVR, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
    if (HI_NULL == pstTemp)
    {
        goto out;
    }

    do
    {

        memset(pstTemp, 0x00, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
        s32Ret = HI_MPI_DMX_AcquireRecDataAndIndex(pChnAttr->DemuxRecHandle, pstTemp);
        if (HI_SUCCESS != s32Ret)
        {
            /* pstRecDataIdx include one index at least */
            if (0 == pstRecDataIdx->u32IdxNum)
            {
                continue;
            }
            else
            {
                break;
            }
        }

        PVRRecMixRecDataAndIndex(pstRecDataIdx, pstTemp);

        if (pstRecDataIdx->u32IdxNum > DMX_MAX_IDX_ACQUIRED_EACH_TIME * 80 / 100)
        {
            break;
        }
    }while (HI_TRUE == bRequireMore);
    HI_FREE(HI_ID_PVR, pstTemp);
    pstTemp = HI_NULL;
    s32Ret = HI_SUCCESS;

out:
    return s32Ret;
#endif
}

STATIC HI_S32 PVRRecProcCipherEncrypt(PVR_REC_CHN_S* pRecChn, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 Len = 0;
    HI_U32 i = 0;
    HI_U32 TotalLen = u32ByteLength;

    if (!pRecChn->stUserCfg.stEncryptCfg.bDoCipher)
    {
        return HI_SUCCESS;
    }
    /*1 M each time, if more than 20M, maybe error happened.*/
    while ( TotalLen > 0 )
    {
        Len = (TotalLen >= PVR_CIPHER_MAX_LEN) ? PVR_CIPHER_MAX_LEN : TotalLen;
        TotalLen -= Len;

        ret = HI_UNF_CIPHER_Encrypt(pRecChn->hCipher,
                                    u32SrcPhyAddr + i * PVR_CIPHER_MAX_LEN,
                                    u32DestPhyAddr + i * PVR_CIPHER_MAX_LEN,
                                    Len);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("HI_UNF_CIPHER_Encrypt failed:%#x!, u32SrcPhyAddr:0x%x,u32DestPhyAddr:0x%x,Len:0x%x\n", ret, u32SrcPhyAddr, u32DestPhyAddr, Len);
            return ret;
        }

        i++;
        if ( i > 20 )
        {
            HI_ERR_PVR("data len to be encrypt is too large(> 20M), Must be error!\n");
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

#ifdef HI_TEE_PVR_SUPPORT
STATIC HI_S32 PVRTeeRecDoEncryptAndCopy(PVR_REC_CHN_S* pRecChn,
                                                   HI_UNF_PVR_DATA_ATTR_S *pstDataAttr,
                                                   PVR_REE_BUFFER_INFO_S* pstReeBuf,
                                                   HI_MPI_DMX_REC_DATA_INDEX_S *pstDmxInfo)
{
    HI_BOOL bUseDmxAddr = HI_TRUE;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32DataLength = 0;
    HI_UNF_PVR_BUF_S stSrcBuf;/*source buffer info*/
    HI_UNF_PVR_BUF_S stDstBuf;/*destination buffer info*/

    memset(&stSrcBuf, 0x00, sizeof(stSrcBuf));
    memset(&stDstBuf, 0x00, sizeof(stDstBuf));

#if defined(CHIP_TYPE_hi3798mv200) && defined(HI_ADVCA_TYPE_VERIMATRIX_ULTRA)
    bUseDmxAddr = HI_FALSE;
#else
    bUseDmxAddr = HI_TRUE;
#endif

    if (HI_TRUE == bUseDmxAddr)
    {
        stSrcBuf.u32PhyAddr = pstDmxInfo->stRecData[0].u32DataPhyAddr;
        stSrcBuf.u32Len = pstDmxInfo->stRecData[0].u32Len;
        u32DataLength = pstDmxInfo->stRecData[0].u32Len;
    }
    else
    {
        stSrcBuf.u32PhyAddr = pRecChn->stTeeBuff.u32SmmuAddr;
        stSrcBuf.u32Len = pRecChn->stTeeBuff.u32Used;
    }

    stSrcBuf.pu8VirAddr = HI_NULL;
    pstReeBuf->u32Used = stSrcBuf.u32Len;
    if (0 == pstReeBuf->u32Used)
    {
        HI_WARN_PVR("No enough data now, and return!\n");
        return HI_SUCCESS;
    }

    stDstBuf.pu8VirAddr = pstReeBuf->pUserAddr;
    stDstBuf.u32PhyAddr = pstReeBuf->u32SmmuAddr;
    stDstBuf.u32Len = stSrcBuf.u32Len;
    s32Ret = pRecChn->stRecCallback.pfnCallback(pstDataAttr, &stDstBuf, &stSrcBuf,
                                                (HI_U32)pstDataAttr->u64FileReadOffset,
                                                stSrcBuf.u32Len, pRecChn->stRecCallback.pUserData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Extend record callback error:0x%08x\n", s32Ret);
        return s32Ret;
    }

    if ((HI_TRUE == bUseDmxAddr) && (2 == pstDmxInfo->u32RecDataCnt))
    {
        pstDataAttr->u64FileReadOffset += u32DataLength;
        pstDataAttr->u64GlobalOffset += u32DataLength;
        stSrcBuf.u32PhyAddr = pstDmxInfo->stRecData[1].u32DataPhyAddr;
        stSrcBuf.u32Len = pstDmxInfo->stRecData[1].u32Len;
        stSrcBuf.pu8VirAddr = HI_NULL;

        pstReeBuf->u32Used += stSrcBuf.u32Len;

        stDstBuf.pu8VirAddr = (HI_VOID *)((HI_CHAR *)pstReeBuf->pUserAddr + u32DataLength);
        stDstBuf.u32PhyAddr = pstReeBuf->u32SmmuAddr + u32DataLength;
        stDstBuf.u32Len = stSrcBuf.u32Len;
        s32Ret = pRecChn->stRecCallback.pfnCallback(pstDataAttr, &stDstBuf, &stSrcBuf,
                                                    (HI_U32)pstDataAttr->u64FileReadOffset,
                                                    stSrcBuf.u32Len, pRecChn->stRecCallback.pUserData);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("Extend record callback error:0x%08x\n", s32Ret);
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}
STATIC HI_VOID PVRRecProcExtendCallBack(PVR_REC_CHN_S* pRecChn, PVR_REE_BUFFER_INFO_S* pstReeBuf, HI_MPI_DMX_REC_DATA_INDEX_S *pstDmxInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32StartFrm;
    HI_U32 u32EndFrm;
    HI_U64 u64Offset = 0;
    HI_U64 u64OffsetInFile = 0;
    HI_U64 u64GlobalOffset;
    PVR_INDEX_ENTRY_NEW_S stStartFrame;
    PVR_INDEX_ENTRY_NEW_S stEndFrame;
    HI_UNF_PVR_DATA_ATTR_S stDataAttr;
    HI_UNF_PVR_BUF_S stSrcBuf;/*source buffer info*/
    HI_UNF_PVR_BUF_S stDstBuf;/*destination buffer info*/
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);
#endif


    memset(&stStartFrame, 0x00, sizeof(stStartFrame));
    memset(&stEndFrame, 0x00, sizeof(stEndFrame));
    memset(&stDataAttr, 0x00, sizeof(stDataAttr));
    memset(&stSrcBuf, 0x00, sizeof(stSrcBuf));
    memset(&stDstBuf, 0x00, sizeof(stDstBuf));

    pstReeBuf->u32Used = 0;

    /*only TEE recording call this API, and all ts recording is not supported*/
    if ((HI_NULL == pRecChn->stRecCallback.pfnCallback)
        || (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pRecChn->stUserCfg.enStreamType)
        || (pRecChn->IndexHandle == HI_NULL))
    {
        HI_ERR_PVR("Tee record must register record callback, and not support reocrd all ts\n");
        return ;
    }

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    u64GlobalOffset = pRecChn->u64CurFileSize + PVR_TS_CACHE_BUFFER_GetUsedSize(&pstExtraBufferInfo->stTsCacheBufInfo);
#else
    u64GlobalOffset = pRecChn->u64CurFileSize;
#endif

    if ((0 != pRecChn->IndexHandle->stCycMgr.u64MaxCycSize)
        && ((PVR_INDEX_REWIND_BY_SIZE == pRecChn->IndexHandle->stCycMgr.enRewindType)
            || (PVR_INDEX_REWIND_BY_BOTH == pRecChn->IndexHandle->stCycMgr.enRewindType)))
    {
        u64OffsetInFile = u64GlobalOffset % pRecChn->IndexHandle->stCycMgr.u64MaxCycSize;
    }
    else
    {
        u64OffsetInFile = u64GlobalOffset - pRecChn->IndexHandle->u64TimeRewindMaxSize;
    }

    u32StartFrm = pRecChn->IndexHandle->stCycMgr.u32StartFrame;

    s32Ret = PVR_Index_GetFrameByNum(pRecChn->IndexHandle, &stStartFrame, u32StartFrm);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PVR("Get Start Frame failed,ret=%d\n", s32Ret);
        stDataAttr.u64FileStartPos = 0;
    }
    else
    {
        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &stStartFrame, PVR_INDEX_OFFSET, &u64Offset);
        stDataAttr.u64FileStartPos = u64Offset;
    }

    if (pRecChn->IndexHandle->stCycMgr.u32EndFrame > 0)
    {
        u32EndFrm = pRecChn->IndexHandle->stCycMgr.u32EndFrame;
    }
    else
    {
        u32EndFrm = pRecChn->IndexHandle->stCycMgr.u32LastFrame;
    }

    s32Ret = PVR_Index_GetFrameByNum(pRecChn->IndexHandle, &stEndFrame, u32EndFrm);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PVR("Get End Frame failed,ret=%d\n", s32Ret);
        stDataAttr.u64FileEndPos = 0;
    }
    else
    {
        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &stEndFrame, PVR_INDEX_OFFSET, &u64Offset);
        stDataAttr.u64FileEndPos = u64Offset;
    }

    stDataAttr.u32ChnID = pRecChn->u32ChnID;/*recording channel id*/
    stDataAttr.u64GlobalOffset = u64GlobalOffset;/*offset in the stream*/
    stDataAttr.u64FileReadOffset = u64OffsetInFile;
    memset(stDataAttr.CurFileName, 0, sizeof(stDataAttr.CurFileName));
    PVRFileGetOffsetFName(pRecChn->dataFile, u64OffsetInFile, stDataAttr.CurFileName);
    PVR_Index_GetIdxFileName(stDataAttr.IdxFileName, pRecChn->stUserCfg.szFileName);
    (HI_VOID)PVRTeeRecDoEncryptAndCopy(pRecChn, &stDataAttr, pstReeBuf, pstDmxInfo);

    return ;
}
#endif
STATIC HI_VOID PVRRecProcExtCallBack(PVR_REC_CHN_S* pRecChn, HI_UNF_DMX_REC_DATA_S* pstRecData)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32StartFrm;
    HI_U32 u32EndFrm;
    HI_U64 u64LenAdp = 0;
    HI_U64 u64OffsetAdp = 0;
    HI_U64 u64OffsetInFile = 0;
    HI_U64 u64GlobalOffset;
    PVR_INDEX_ENTRY_NEW_S stStartFrame;
    PVR_INDEX_ENTRY_NEW_S stEndFrame;
    HI_UNF_PVR_DATA_ATTR_S stDataAttr;
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);
#endif


    memset(&stStartFrame, 0x00, sizeof(stStartFrame));
    memset(&stEndFrame, 0x00, sizeof(stEndFrame));
    memset(&stDataAttr, 0x00, sizeof(stDataAttr));

    /*TEE recording will call writeCallBack,
        REE recording will call both writeCallBack and pfnCallback
        all ts recording won't call any callback*/
#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
    {
        if ((HI_NULL == pRecChn->writeCallBack)
            || (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pRecChn->stUserCfg.enStreamType)
            || (pRecChn->IndexHandle == HI_NULL))
        {
            return;
        }
    }
    else
#endif
    {
        if (((HI_NULL == pRecChn->writeCallBack) && (HI_NULL == pRecChn->stRecCallback.pfnCallback))
            || (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pRecChn->stUserCfg.enStreamType)
            || (pRecChn->IndexHandle == HI_NULL))
        {
            return ;
        }
    }

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    u64GlobalOffset = pRecChn->u64CurFileSize + PVR_TS_CACHE_BUFFER_GetUsedSize(&pstExtraBufferInfo->stTsCacheBufInfo);;
#else
    u64GlobalOffset = pRecChn->u64CurFileSize;
#endif

    if ((0 != pRecChn->IndexHandle->stCycMgr.u64MaxCycSize)
        && ((PVR_INDEX_REWIND_BY_SIZE == pRecChn->IndexHandle->stCycMgr.enRewindType)
            || (PVR_INDEX_REWIND_BY_BOTH == pRecChn->IndexHandle->stCycMgr.enRewindType)))
    {
        u64OffsetInFile = u64GlobalOffset % pRecChn->IndexHandle->stCycMgr.u64MaxCycSize;
    }
    else
    {
        u64OffsetInFile = u64GlobalOffset - pRecChn->IndexHandle->u64TimeRewindMaxSize;
    }

    u32StartFrm = pRecChn->IndexHandle->stCycMgr.u32StartFrame;

    s32Ret = PVR_Index_GetFrameByNum(pRecChn->IndexHandle, &stStartFrame, u32StartFrm);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PVR("Get Start Frame failed,ret=%d\n", s32Ret);
        stDataAttr.u64FileStartPos = 0;

    }
    else
    {
        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &stStartFrame, PVR_INDEX_OFFSET, &stDataAttr.u64FileStartPos);
    }

    if (pRecChn->IndexHandle->stCycMgr.u32EndFrame > 0)
    {
        u32EndFrm = pRecChn->IndexHandle->stCycMgr.u32EndFrame;
    }
    else
    {
        u32EndFrm = pRecChn->IndexHandle->stCycMgr.u32LastFrame;
    }

    s32Ret = PVR_Index_GetFrameByNum(pRecChn->IndexHandle, &stEndFrame, u32EndFrm);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PVR("Get End Frame failed,ret=%d\n", s32Ret);
        stDataAttr.u64FileEndPos = 0;
    }
    else
    {
        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &stEndFrame, PVR_INDEX_OFFSET, &stDataAttr.u64FileEndPos);
    }

    stDataAttr.u32ChnID = pRecChn->u32ChnID;
    stDataAttr.u64GlobalOffset = u64GlobalOffset;
    stDataAttr.u64FileReadOffset = u64OffsetInFile;
    memset(stDataAttr.CurFileName, 0, sizeof(stDataAttr.CurFileName));
    PVRFileGetOffsetFName(pRecChn->dataFile, u64OffsetInFile, stDataAttr.CurFileName);
    PVR_Index_GetIdxFileName(stDataAttr.IdxFileName, pRecChn->stUserCfg.szFileName);

    u64LenAdp = pstRecData->u32Len;
    u64OffsetAdp = u64OffsetInFile;

    /*as data in REE, both src and dst buffer are the same buffer*/
    if (HI_NULL != pRecChn->writeCallBack)
    {
        s32Ret = pRecChn->writeCallBack(&stDataAttr, pstRecData->pDataAddr, pstRecData->u32DataPhyAddr,
                                        (HI_U32)u64OffsetAdp, (HI_U32)u64LenAdp);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PVR("write call back error:%x\n", s32Ret);
        }
    }

#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE != pRecChn->stUserCfg.enSecureMode)
#endif
    {
        if (HI_NULL != pRecChn->stRecCallback.pfnCallback)
        {
            HI_UNF_PVR_BUF_S stCbBuf;
            memset(&stCbBuf, 0x00, sizeof(stCbBuf));
            stCbBuf.pu8VirAddr = pstRecData->pDataAddr;
            stCbBuf.u32PhyAddr = pstRecData->u32DataPhyAddr;
            stCbBuf.u32Len = (HI_U32)u64LenAdp;
            s32Ret = pRecChn->stRecCallback.pfnCallback(&stDataAttr, &stCbBuf, &stCbBuf,
                     (HI_U32)u64OffsetAdp, (HI_U32)u64LenAdp, pRecChn->stRecCallback.pUserData);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_PVR("Extend record callback error:%x\n", s32Ret);
            }
        }
    }

    return ;
}

STATIC HI_VOID PVRRecProcOverFlow(PVR_REC_CHN_S* pRecChn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32DisplayTimeMs = 0;
    /*if overflow, restart demux and report event to app*/
    s32Ret = HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx stop rec chn failed! ret %x\n", s32Ret);
        return;
    }

    s32Ret = HI_UNF_DMX_StartRecChn(pRecChn->DemuxRecHandle);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx start rec chn failed! ret %x\n", s32Ret);
        return;
    }
    /*if no valid index and data received, just restart demux channel, not report event*/
    if (0 == pRecChn->u64CurFileSize)
    {
        HI_ERR_PVR("Haven't receive any valid data, not report event!\n");
        return;
    }

    PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &pRecChn->IndexHandle->stCurRecFrame, PVR_INDEX_DISP_TIME, &u32DisplayTimeMs);
    PVR_Intf_DoEventCallback(pRecChn->u32ChnID, HI_UNF_PVR_EVENT_REC_DISK_SLOW, u32DisplayTimeMs);
    PVR_Intf_AddEventHistory(&pRecChn->stEventHistory, HI_UNF_PVR_EVENT_REC_DISK_SLOW);

    /*save current globaloffset to correct the offset from demux later.*/
    PVR_Index_ProcOverFlow(pRecChn->IndexHandle);
    pRecChn->IndexHandle->u64OverflowOffset = pRecChn->u64CurFileSize;

#if defined(PVR_APPEND_MODE_SUPPORT) || defined(PVR_PID_CHANGE_SUPPORT)
    if (HI_NULL != pRecChn->IndexHandle->pstLastRecordInfo)
    {
        pRecChn->IndexHandle->u64OverflowOffset -= pRecChn->IndexHandle->pstLastRecordInfo->u64GlobalOffset;
    }
#endif

    return;
}

/* on recording, in sequence write some data into ts file */
STATIC HI_S32 PVRRecWriteStreamDirect(PVR_REC_CHN_S* pRecChn, HI_U8* pu8Buf, HI_U32 u32Len, HI_U64 u64OffsetInFile)
//STATIC HI_S32 PVRRecWriteStreamDirect(PVR_REC_CHN_S *pRecChn, HI_UNF_DMX_REC_DATA_S stDmxTsData, HI_U32 len, HI_U64 u64OffsetInFile, HI_U64 u64GlobalOffset)
{
    ssize_t sizeWrite, sizeWriten = 0;

#if defined(PVR_PID_CHANGE_SUPPORT) && defined(HI_PVR_EXTRA_BUF_SUPPORT)
    if (u32Len % PVR_DIO_ALIGN_SIZE != 0)
    {
        return PVR_WriteStreamAlign(pRecChn->dataFile, pu8Buf, u32Len, u64OffsetInFile);
    }
#endif

    /* try to cycle write*/
    do
    {
        sizeWrite = PVR_PWRITE64(&((const char*)pu8Buf)[sizeWriten],
                                 u32Len - (HI_U32)sizeWriten,
                                 pRecChn->dataFile,
                                 u64OffsetInFile + sizeWriten);
        if ((-1) == sizeWrite)
        {
            if (EINTR == errno)
            {
                HI_WARN_PVR("EINTR can't write ts. try:%u, addr:%p, fd:%d\n", u32Len, pu8Buf, pRecChn->dataFile);
                continue;
            }
            else if (ENOSPC == errno)
            {
                return HI_ERR_PVR_FILE_DISC_FULL;
            }
            else
            {
                HI_ERR_PVR("can't write ts. try:%u, addr:%p, fd:%d\n", u32Len, pu8Buf, pRecChn->dataFile);
                return HI_ERR_PVR_FILE_CANT_WRITE;
            }
        }

        sizeWriten += sizeWrite;
    } while ((HI_U32)sizeWriten < u32Len);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVRRecCycWriteStream
 Description     : write stream to file
 Input           : pBuf      **
                   len       **
                   dataFile  **
                   chnID     **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/29
    Author       : sdk
    Modification : Created function

*****************************************************************************/
STATIC HI_S32 PVRRecCycWriteStream(HI_UNF_DMX_REC_DATA_S stDmxTsData, PVR_REC_CHN_S* pRecChn)
{
    HI_U32 len1 = 0;
    HI_U32 len2 = 0;
    HI_S32 ret;
    HI_U64 u64LastFileSize = pRecChn->u64CurFileSize;
    HI_U64 u64MaxSize = 0;
    HI_BOOL bReachFix = HI_FALSE;
    HI_U64 u64GlobalOffset = 0;
    HI_U32 u32FrameSize = 0;
    HI_U64 u64TempRecordWritePos = pRecChn->u64CurWritePos;

    len1 = stDmxTsData.u32Len;

    /* record fixed file length,  reach to the length, stop record */
    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pRecChn->stUserCfg.enStreamType)
    {
        u64MaxSize =  pRecChn->stUserCfg.u64MaxFileSize;
    }
    else
    {
        if (HI_NULL == pRecChn->IndexHandle)
        {
            HI_FATAL_PVR("Index handle is null\n");
            return HI_FAILURE;
        }

        u64MaxSize =  pRecChn->IndexHandle->stCycMgr.u64MaxCycSize;
    }

    if (PVR_REC_IS_FIXSIZE(&pRecChn->stUserCfg))
    {
        if (0 < u64MaxSize)
        {
#ifdef PVR_APPEND_MODE_SUPPORT
            if ((pRecChn->u64CurFileSize - pRecChn->stLastRecInfo.u64GlobalOffset + pRecChn->stLastRecInfo.u64Offset + stDmxTsData.u32Len) >= u64MaxSize)
#else
            if ((pRecChn->u64CurFileSize + stDmxTsData.u32Len) >= u64MaxSize)
#endif
            {
                HI_ERR_PVR("cur size %#llx will over fix size %#llx !!\n",
                           pRecChn->u64CurFileSize, u64MaxSize);
                bReachFix = HI_TRUE;
                len1 = (u64MaxSize > pRecChn->u64CurFileSize) ? (HI_U32)(u64MaxSize - pRecChn->u64CurFileSize) : 0;
            }
        }
    }
    else if (PVR_REC_IS_REWIND(&pRecChn->stUserCfg))  /* case rewind record */
    {
        if (HI_NULL == pRecChn->IndexHandle)
        {
            HI_FATAL_PVR("Index handle is null\n");
            return HI_FAILURE;
        }

        if (PVR_INDEX_REWIND_BY_TIME == pRecChn->IndexHandle->stCycMgr.enRewindType)
        {
            /*��һ�λ��ƺ�ʼ���л��ƴ�����һ�λ���ǰ�����ۼ�*/
            if (0 < u64MaxSize)
            {
                /*����ʱ���������:
                1.Index���ts����ʱts�ļ����Ʊ߽�Ϊts��ǰ�ļ��Ĵ�С��tsֱ�ӽ��л��ƴ���
                2.Index��ǰts����ʱts�ļ����Ʊ߽�Ϊindex��globaloffset��ts������ڸ�ֵ�Ž��л��ƴ���
                */
                if (HI_TRUE == pRecChn->IndexHandle->bTimeRewindFlagForFile)
                {
                    if (pRecChn->u64CurFileSize + stDmxTsData.u32Len > pRecChn->IndexHandle->u64TimeRewindMaxSize)
                    {
                        //l2cache�ͷ�l2cache�����߼����Ա�֤u64TimeRewindMaxSize����u64CurFileSize
                        len1 = (HI_U32)(pRecChn->IndexHandle->u64TimeRewindMaxSize - pRecChn->u64CurFileSize);
                        len2 = stDmxTsData.u32Len - len1;
                        pRecChn->IndexHandle->bTimeRewindFlagForFile = HI_FALSE;
                        pRecChn->s32OverFixTimes++;
                        pRecChn->bEventFlg = HI_TRUE;
                    }
                }
            }
        }
        else
        {
            if ((pRecChn->u64CurWritePos + stDmxTsData.u32Len) > u64MaxSize)
            {
                //                pRecChn->IndexHandle->stCycMgr.enRewindType = PVR_INDEX_REWIND_BY_SIZE;
                pRecChn->s32OverFixTimes++;
                len1 = (HI_U32)(u64MaxSize - pRecChn->u64CurWritePos);
                len2 = stDmxTsData.u32Len - len1;
                pRecChn->bEventFlg = HI_TRUE;
            }
        }
    }

    HI_ASSERT(len1 <= stDmxTsData.u32Len);

    if (stDmxTsData.pDataAddr)
    {
        ret = PVRRecWriteStreamDirect(pRecChn, stDmxTsData.pDataAddr, len1, pRecChn->u64CurWritePos);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("Write pvr file error! ret %x\n", ret);
            return ret;
        }

        pRecChn->u64CurFileSize += len1;
        if (u64TempRecordWritePos != pRecChn->u64CurWritePos)
        {
            HI_ERR_PVR("This u64CurWritePos variable has changed elsewhere, old: %llu, new: %llu\n", u64TempRecordWritePos, pRecChn->u64CurWritePos);
        }
        pRecChn->u64CurWritePos += len1;
        u64TempRecordWritePos += len1;
    }

    if (len2 > 0)
    {
        stDmxTsData.pDataAddr += len1;
        ret = PVRRecWriteStreamDirect(pRecChn, stDmxTsData.pDataAddr, len2, 0);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("Write pvr file error! ret %x\n", ret);
            return ret;
        }

        pRecChn->u64CurFileSize += len2;
        if (u64TempRecordWritePos != pRecChn->u64CurWritePos)
        {
            HI_ERR_PVR("This u64CurWritePos variable has changed elsewhere, old: %llu, new: %llu\n", u64TempRecordWritePos, pRecChn->u64CurWritePos);
        }
        pRecChn->u64CurWritePos = len2;
    }

    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS != pRecChn->stUserCfg.enStreamType)
    {
#ifndef HI_PVR_EXTRA_BUF_SUPPORT
        pRecChn->IndexHandle->u64FileSizeGlobal = pRecChn->u64CurFileSize;
#endif

        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &pRecChn->IndexHandle->stCurPlayFrame, PVR_INDEX_GLOBAL_OFFSET, &u64GlobalOffset);
        PVR_Index_GetIndexInfo(pRecChn->IndexHandle, &pRecChn->IndexHandle->stCurPlayFrame, PVR_INDEX_FRAME_SIZE, &u32FrameSize);
        if ((u64LastFileSize < u64GlobalOffset) && (pRecChn->u64CurFileSize > u64GlobalOffset))
        {
            HI_WARN_PVR("!!rec pos will cover play, %#llx-->%#llx, ReadPos:%#llx->%#llx\n",
                        u64LastFileSize, pRecChn->u64CurFileSize,
                        u64GlobalOffset, u64GlobalOffset + u32FrameSize);
        }
    }

    if (bReachFix)
    { return HI_ERR_PVR_FILE_TILL_END; }
    else
    { return HI_SUCCESS; }
}

STATIC INLINE HI_VOID PVRRecCheckError(PVR_REC_CHN_S*  pChnAttr, HI_S32 ret)
{
    if (HI_SUCCESS == ret)
    {
        return;
    }

    if ((HI_ERR_DMX_NOAVAILABLE_DATA == ret) || (HI_ERR_DMX_TIMEOUT == ret))
    {
        return;
    }

    if (HI_ERR_PVR_FILE_DISC_FULL == ret)
    {
        PVR_Intf_DoEventCallback(pChnAttr->u32ChnID, HI_UNF_PVR_EVENT_REC_DISKFULL, 0);
        PVR_Intf_AddEventHistory(&pChnAttr->stEventHistory, HI_UNF_PVR_EVENT_REC_DISKFULL);
    }
    else if (HI_ERR_PVR_FILE_TILL_END == ret)
    {
        PVR_Intf_DoEventCallback(pChnAttr->u32ChnID, HI_UNF_PVR_EVENT_REC_OVER_FIX, 0);
        PVR_Intf_AddEventHistory(&pChnAttr->stEventHistory, HI_UNF_PVR_EVENT_REC_OVER_FIX);
    }
    else
    {
        PVR_Intf_DoEventCallback(pChnAttr->u32ChnID, HI_UNF_PVR_EVENT_REC_ERROR, ret);
        PVR_Intf_AddEventHistory(&pChnAttr->stEventHistory, HI_UNF_PVR_EVENT_REC_ERROR);
    }

    return;
}

STATIC INLINE HI_VOID PVRRecCheckRecPosition(PVR_REC_CHN_S* pChnAttr)
{
    HI_S32 times;

    if (PVR_REC_IS_REWIND(&pChnAttr->stUserCfg))
    {
        if (pChnAttr->s32OverFixTimes > 0)
        {
            times = pChnAttr->s32OverFixTimes;
            pChnAttr->s32OverFixTimes = 0;
            PVR_Intf_DoEventCallback(pChnAttr->u32ChnID, HI_UNF_PVR_EVENT_REC_OVER_FIX, times);
            PVR_Intf_AddEventHistory(&pChnAttr->stEventHistory, HI_UNF_PVR_EVENT_REC_OVER_FIX);
        }
    }
}

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
#ifndef PVR_ACQUIREDATAINDX
STATIC HI_S32 PVRRecSaveIndexToCache(PVR_REC_CHN_S* pRecChn)
{
    HI_S32 ret = HI_SUCCESS;
    HI_MPI_DMX_REC_INDEX_S stDmxIndexInfo;

    memset(&stDmxIndexInfo, 0x00, sizeof(stDmxIndexInfo));

    if (pRecChn->bUseLastDmxIdx)
    {
        memcpy(&stDmxIndexInfo, &pRecChn->stDmxIdxInfo, sizeof(HI_MPI_DMX_REC_INDEX_S));
    }
    else
    {
        ret = HI_MPI_DMX_AcquireRecIndex(pRecChn->DemuxRecHandle, &stDmxIndexInfo, 0);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }

        if (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
        {
            pRecChn->IndexHandle->u32PauseFrameCnt++;
            pRecChn->bUseLastDmxIdx = HI_FALSE;
            return HI_SUCCESS;
        }

#ifdef DUMP_DMX_DATA
        if (g_pvrfpIdxReceive)
        {
            fwrite(&stDmxIndexInfo, 1, sizeof(stDmxIndexInfo), g_pvrfpIdxReceive);
        }
#endif
    }

    ret = PVR_Index_SaveToCache(pRecChn->IndexHandle, &stDmxIndexInfo);
    if (ret != HI_SUCCESS)
    {
        memcpy(&pRecChn->stDmxIdxInfo, &stDmxIndexInfo, sizeof(HI_MPI_DMX_REC_INDEX_S));
        pRecChn->bUseLastDmxIdx = HI_TRUE;
        PVR_USLEEP(100);
        return HI_SUCCESS;
    }

    pRecChn->bUseLastDmxIdx = HI_FALSE;

    if (PVRPlayCheckSlowPauseBack(pRecChn->stUserCfg.szFileName))
    {
#if 0
        if (PVR_Index_CheckSetRecReachPlay(pRecChn->IndexHandle)) /* rec reach to play */
        {
            (HI_VOID)PVR_Index_SeekToStart(pRecChn->IndexHandle); /* force play to move forward */
            PVR_Intf_DoEventCallback(pRecChn->u32ChnID, HI_UNF_PVR_EVENT_REC_REACH_PLAY, 0);
        }
#endif
        (HI_VOID)PVR_Index_CheckSetRecReachPlay(pRecChn->IndexHandle, 0);
    }

    return ret;
}

STATIC HI_VOID* PVRRecSaveToCache(HI_VOID* args)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32OverflowTimes = 0;
    HI_UNF_DMX_REC_DATA_S stRecData = {0};
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S*)args;
    HI_U32 u32TsPKSize = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);
    HI_U32 u32SendCnt = 0;

    HI_INFO_PVR("Chn %d start to save to cache.\n", pRecChn->u32ChnID);

#ifdef DUMP_DMX_DATA
    FILE* pvrTsReceive = NULL;
    HI_CHAR saveName[256] = {0};
    snprintf(saveName, 255, "%s_receive.ts",  pRecChn->stUserCfg.szFileName);
    pvrTsReceive = fopen(saveName, "wb");
#endif
    while (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState && (HI_TRUE == pRecChn->bSavingData))
    {
        ret = PVRRecSaveIndexToCache(pRecChn);
        if (!((HI_SUCCESS == ret) || (HI_ERR_DMX_NOAVAILABLE_DATA == ret) || (HI_ERR_DMX_TIMEOUT == ret)))
        {
            break;
        }

        do
        {
            ret = HI_UNF_DMX_AcquireRecData(pRecChn->DemuxRecHandle, &stRecData, 0);
            if ((HI_SUCCESS == ret) && (stRecData.u32Len > 0))
            {
                if (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
                {
                    pRecChn->IndexHandle->u64DeltaGlobalOffset += stRecData.u32Len;

                    (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);
                    break;
                }
#ifdef DUMP_DMX_DATA
                if (pvrTsReceive)
                {
                    fwrite(stRecData.pDataAddr, 1, stRecData.u32Len, pvrTsReceive);
                }
#endif

                if ((0 != (stRecData.u32Len % u32TsPKSize)) || (0 != (stRecData.u32Len % 16)))
                {
                    HI_FATAL_PVR("Data size is not aligned by 188 and 256. size=%d.\n", stRecData.u32Len);
                    (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);
                    break;
                }

                u32SendCnt = 0;
                do
                {
                    /* if cipher, get and save the cipher data */
                    if (HI_SUCCESS != PVRRecProcCipherEncrypt(pRecChn,
                            stRecData.u32DataPhyAddr,
                            stRecData.u32DataPhyAddr,
                            stRecData.u32Len))
                    {
                        HI_ERR_PVR("PVRRecProcCipherEncrypt failed\n");
                        break;
                    }

                    /* if registed external write callback function, get and save the cipher data */
                    PVRRecProcExtCallBack(pRecChn, &stRecData);
                    ret = PVR_TS_CACHE_BUFFER_WriteToBuffer(&pstExtraBufferInfo->stTsCacheBufInfo, stRecData.pDataAddr, stRecData.u32Len);
                    if (HI_SUCCESS != ret)
                    {
                        u32SendCnt++;
                        PVR_USLEEP(10 * 1000);
                        if (u32SendCnt > 500)
                        {
                            HI_ERR_PVR("Can't save data to the cache in 5 seconds!\n");
                            break;
                        }
                    }
                    else
                    {
                        pRecChn->IndexHandle->u64FileSizeGlobal += stRecData.u32Len;
                    }
                }while (HI_SUCCESS != ret);

                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);

                if (HI_SUCCESS != ret)
                {
                    break;
                }

                PVR_Index_PushStartWhenTsLead(pRecChn->IndexHandle, pRecChn->u64CurFileSize);

                u32OverflowTimes = PVRRecCheckRecBufStatus(u32OverflowTimes, pRecChn);
            }
            else
            {
                if ((HI_ERR_DMX_NOAVAILABLE_DATA == ret) || (HI_ERR_DMX_TIMEOUT == ret))
                {
                    HI_INFO_PVR("chan:%d, rec wait .\n", pRecChn->u32ChnID);
                    PVR_USLEEP(100);
                }
                else
                {
                    HI_ERR_PVR("receive rec stream error:%#x\n", ret);
                }

                break;
            }
        }
        while (HI_SUCCESS == ret);
    }

    if (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        HI_INFO_PVR("-----PVRRecSaveToCache exiting with error:%#x...\n", ret);
        PVRRecCheckError(pRecChn, ret);
    }

#ifdef DUMP_DMX_DATA
    if (pvrTsReceive)
    {
        fclose(pvrTsReceive);
        pvrTsReceive = NULL;
    }
#endif

    HI_INFO_PVR("<==chn %d PVRRecSaveIdxRoutine ret=%#x.\n", pRecChn->u32ChnID, ret);
    return NULL;
}

#else
#ifdef HI_TEE_PVR_SUPPORT
static HI_S32 PVRRecSaveToCacheSecure(PVR_REC_CHN_S* pRecChn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32SendCnt = 0;
    HI_UNF_DMX_REC_DATA_S stReeData;
    HI_U32 u32TsPKSize = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);;

    memset(&stReeData, 0x00, sizeof(stReeData));
    if (HI_TEE_ERROR_PVR_NO_ENOUGH_DATA == HI_PVR_TeeGetReeBuffInfo(&pRecChn->stReeBuff,
            &stReeData.pDataAddr, &stReeData.u32DataPhyAddr, &stReeData.u32Len))
    {
        return HI_SUCCESS;
    }
    if ((0 == stReeData.u32Len) || (0 != stReeData.u32Len % u32TsPKSize) || (0 != stReeData.u32Len % 16))
    {
        HI_FATAL_PVR("Len=%x Mod_%d=%d Mod_16=%d\n",
                     stReeData.u32Len, u32TsPKSize, stReeData.u32Len % u32TsPKSize, stReeData.u32Len % 16);
        return HI_FAILURE;
    }
    PVRRecProcExtCallBack(pRecChn, &stReeData);

    u32SendCnt = 0;
    do
    {
        s32Ret = PVR_TS_CACHE_BUFFER_WriteToBuffer(&pstExtraBufferInfo->stTsCacheBufInfo, stReeData.pDataAddr, stReeData.u32Len);
        if (HI_SUCCESS != s32Ret)
        {
            PVR_USLEEP(10 * 1000);
            u32SendCnt++;
            if (u32SendCnt > 500)
            {
                HI_WARN_PVR("Can't save data to the cache within 5 seconds!\n");
                break;
            }
        }
        else
        {
            pRecChn->IndexHandle->u64FileSizeGlobal += stReeData.u32Len;
        }
    }while (HI_SUCCESS != s32Ret);
    return s32Ret;
}
#endif
STATIC HI_S32 PVRRecSaveToCacheNormal(PVR_REC_CHN_S* pRecChn, HI_MPI_DMX_REC_DATA_INDEX_S* pstDataIdx)
{
    HI_UNF_DMX_REC_DATA_S* pstData = HI_NULL;
    HI_S32 i = 0;
    HI_U32 u32SendCnt = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32TsPKSize = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);

    for (i = 0; i < pstDataIdx->u32RecDataCnt; i++)
    {
        pstData = &(pstDataIdx->stRecData[i]);
        if ((0 == pstData->u32Len) || (0 != pstData->u32Len % u32TsPKSize) || (0 != pstData->u32Len % 16))
        {
            HI_FATAL_PVR("Len=%x Mod_%d=%d Mod_16=%d i=%d cnt=%d\n",
                         pstData->u32Len, u32TsPKSize, pstData->u32Len % u32TsPKSize, pstData->u32Len % 16, i, pstDataIdx->u32RecDataCnt);
            s32Ret = HI_FAILURE;
            break;
        }

        if (HI_SUCCESS != PVRRecProcCipherEncrypt(pRecChn, pstData->u32DataPhyAddr, pstData->u32DataPhyAddr, pstData->u32Len))
        {
            HI_ERR_PVR("PVRRecProcCipherEncrypt failed\n");
            continue;
        }

        PVRRecProcExtCallBack(pRecChn, pstData);

        u32SendCnt = 0;
        do
        {
            s32Ret = PVR_TS_CACHE_BUFFER_WriteToBuffer(&pstExtraBufferInfo->stTsCacheBufInfo, pstData->pDataAddr, pstData->u32Len);
            if (HI_SUCCESS != s32Ret)
            {
                PVR_USLEEP(10 * 1000);
                u32SendCnt++;
                if (u32SendCnt > 500)
                {
                    HI_ERR_PVR("Can't save data to the cache within 5 seconds!\n");
                    i = pstDataIdx->u32RecDataCnt;
                    break;
                }
            }
            else
            {
                pRecChn->IndexHandle->u64FileSizeGlobal += pstData->u32Len;
            }
        }while (HI_SUCCESS != s32Ret);
    }

    return s32Ret;
}

STATIC HI_VOID* PVRRecSaveToCache(HI_VOID* args)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;
    HI_U32 u32SendCnt = 0;
    HI_MPI_DMX_REC_DATA_INDEX_S* pstDataIdx = HI_NULL;
    HI_MPI_DMX_REC_INDEX_S* pstIdx = HI_NULL;
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S*)args;
#ifdef HI_TEE_PVR_SUPPORT
    PVR_TEE_REC_PROCESS_INFO_S stTeeRecInfo;
#endif
#ifdef DUMP_DMX_DATA
    FILE* pvrTsReceive = NULL;
    HI_CHAR saveName[256] = {0};

    snprintf(saveName, 255, "%s_receive.ts",  pRecChn->stUserCfg.szFileName);
    pvrTsReceive = fopen(saveName, "wb");
#endif

    HI_INFO_PVR("Chn %d start to save to cache.\n", pRecChn->u32ChnID);
    pstDataIdx = (HI_MPI_DMX_REC_DATA_INDEX_S*)HI_MALLOC(HI_ID_PVR, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
    if (HI_NULL == pstDataIdx)
    {
        HI_ERR_PVR("malloc failed\n");
        PVRRecCheckError(pRecChn, HI_ERR_PVR_NO_MEM);
        return HI_NULL;
    }
    HI_INFO_PVR("pstDataIdx = %p, len = %#x\n", pstDataIdx, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));

    while (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState && (HI_TRUE == pRecChn->bSavingData))
    {
        ret = PVRRecRequireDataAndIndex(pRecChn, pstDataIdx);
        if (ret == HI_SUCCESS)
        {
            if (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
            {
                for (i = 0; i < pstDataIdx->u32RecDataCnt; i++)
                {
                    pRecChn->IndexHandle->u64DeltaGlobalOffset += pstDataIdx->stRecData[i].u32Len;
                }

                (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
                continue;
            }
#ifdef HI_TEE_PVR_SUPPORT
            if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
            {
                memset(&stTeeRecInfo, 0x00, sizeof(stTeeRecInfo));
                stTeeRecInfo.hDemuxHandle = pRecChn->DemuxRecHandle;
                stTeeRecInfo.pstDmxRecData = pstDataIdx;
                stTeeRecInfo.pstReeBuff = &pRecChn->stReeBuff;
                stTeeRecInfo.pstTeeBuff = &pRecChn->stTeeBuff;
                stTeeRecInfo.u64DropLength = pRecChn->IndexHandle->u64DeltaGlobalOffset;
                /*CNComment:���һ֡������ʼλ�ã���֤188���룬ͬ���޸�ts���ݺ�index����*/
                HI_PVR_TeeAdjustTsData(pRecChn->u32TeeChnId, &stTeeRecInfo);
                HI_PVR_TeeGetTeeState(pRecChn->u32TeeChnId, &pRecChn->stTeeState);
                pRecChn->stReeBuff.u32Used = 0;
                PVRRecProcExtendCallBack(pRecChn, &pRecChn->stReeBuff, pstDataIdx);
            }
#endif
            for (i = 0; i < pstDataIdx->u32IdxNum; i++)
            {
                pstIdx = &(pstDataIdx->stIndex[i]);
                u32SendCnt = 0;
                do
                {
                    ret = PVR_Index_SaveToCache(pRecChn->IndexHandle, pstIdx);
                    if (ret != HI_SUCCESS)
                    {
                        PVR_USLEEP(10 * 1000);
                        u32SendCnt++;
                        if (u32SendCnt > 500)
                        {
                            HI_ERR_PVR("Can't save idx to the cache within 5 seconds!\n");
                            i = pstDataIdx->u32IdxNum;
                            break;
                        }
                    }
                }while(ret != HI_SUCCESS);
            }

            if (HI_SUCCESS == ret)
            {
#ifdef HI_TEE_PVR_SUPPORT
                if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
                {
                    ret = PVRRecSaveToCacheSecure(pRecChn);
                }
                else
#endif
                {
                    ret = PVRRecSaveToCacheNormal(pRecChn, pstDataIdx);
                }
            }

            (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);

            if (ret != HI_SUCCESS)
            {
                break;
            }

            if (pRecChn->IndexHandle->bRecReachFix)
            {
                ret = HI_ERR_PVR_FILE_TILL_END;
                break;
            }
        }
        else if ((HI_ERR_DMX_NOAVAILABLE_DATA == ret) || (HI_ERR_DMX_TIMEOUT == ret))
        {
            PVR_USLEEP(10 * 1000);
        }
        else if (HI_ERR_DMX_OVERFLOW_BUFFER == ret)
        {
            PVRRecProcOverFlow(pRecChn);
        }
        else
        {
            HI_ERR_PVR("Acquire dataandidx failed! ret %x\n", ret);
            break;
        }
    }

    if (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        HI_INFO_PVR("-----PVRRecSaveToCache exiting with error:%#x...\n", ret);
        PVRRecCheckError(pRecChn, ret);
    }

    if (HI_NULL != pstDataIdx)
    {
        HI_FREE(HI_ID_PVR, pstDataIdx);
        pstDataIdx = HI_NULL;
    }

#ifdef DUMP_DMX_DATA
    if (pvrTsReceive)
    {
        fclose(pvrTsReceive);
        pvrTsReceive = NULL;
    }
#endif

    HI_INFO_PVR("<==chn %d PVRRecSaveIdxRoutine ret=%#x.\n", pRecChn->u32ChnID, ret);
    return NULL;
}
#endif

STATIC HI_VOID PVRRecFlushAllToFile(PVR_REC_CHN_S* pstChn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_DMX_REC_DATA_S stRecData = {0};
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pstChn->IndexHandle);
    PVR_LOCK(&pstChn->stTsCacheMutex);
    while (PVR_TS_CACHE_BUFFER_GetUsedSize(&pstExtraBufferInfo->stTsCacheBufInfo) != 0)
    {
#ifdef HI_PVR_FIFO_DIO
        s32Ret = PVR_TS_CACHE_BUFFER_FlushBegin(&(pstExtraBufferInfo->stTsCacheBufInfo), &(stRecData.pDataAddr), &stRecData.u32Len, HI_TRUE);
#else
        s32Ret = PVR_TS_CACHE_BUFFER_FlushBegin(&(pstExtraBufferInfo->stTsCacheBufInfo), &(stRecData.pDataAddr), &stRecData.u32Len);
#endif
        if (HI_SUCCESS == s32Ret)
        {
            (HI_VOID)PVRRecCycWriteStream(stRecData, pstChn);
            (HI_VOID)PVR_TS_CACHE_BUFFER_FlushEnd(&(pstExtraBufferInfo->stTsCacheBufInfo), stRecData.u32Len);
        }
    }

    (HI_VOID)PVR_TS_CACHE_BUFFER_Reset(&(pstExtraBufferInfo->stTsCacheBufInfo), pstExtraBufferInfo->stTsCacheBufInfo.u64HeadGlobalOffset);

    (HI_VOID)PVR_Index_FlushToFile(pstChn->IndexHandle);
    PVR_UNLOCK(&pstChn->stTsCacheMutex);
}

STATIC HI_VOID* PVRRecSaveToFile(HI_VOID* args)
{
    HI_U8*  pu8WriteBuff = HI_NULL;
    HI_U32 u32WriteLen = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_DMX_REC_DATA_S stTsData ;
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S*)args;
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pRecChn->IndexHandle);

    HI_INFO_PVR("chan:%d, start.\n", pRecChn->u32ChnID);

    /* this thread must wait for that save-cache thread has stoped yet */
    while (!((HI_UNF_PVR_REC_STATE_STOP == pRecChn->enState) && (0 == pRecChn->RecordCacheThread)))
    {
        memset(&stTsData, 0x00, sizeof(stTsData));
        PVR_LOCK(&pRecChn->stTsCacheMutex);
#ifdef HI_PVR_FIFO_DIO
        ret = PVR_TS_CACHE_BUFFER_FlushBegin(&(pstExtraBufferInfo->stTsCacheBufInfo), &pu8WriteBuff, &u32WriteLen, HI_FALSE);
#else
        ret = PVR_TS_CACHE_BUFFER_FlushBegin(&(pstExtraBufferInfo->stTsCacheBufInfo), &pu8WriteBuff, &u32WriteLen);
#endif
        if ((HI_SUCCESS == ret) && (u32WriteLen != 0))
        {
            stTsData.pDataAddr = pu8WriteBuff;
            stTsData.u32Len = u32WriteLen;
        }
        else
        {
            PVR_USLEEP(10 * 1000);
            goto PVR_SAVE_INDEX;
        }

        ret = PVRRecCycWriteStream(stTsData, pRecChn);
        (HI_VOID)PVR_TS_CACHE_BUFFER_FlushEnd(&(pstExtraBufferInfo->stTsCacheBufInfo), u32WriteLen);

        if (HI_SUCCESS != ret)
        {
            /*we won't save file when index has reach to fix time or size*/
            if (ret == HI_ERR_PVR_FILE_TILL_END)
            {
                (HI_VOID)PVR_Index_SaveToFile(pRecChn->IndexHandle, HI_TRUE);
            }
            PVR_UNLOCK(&pRecChn->stTsCacheMutex);
            HI_ERR_PVR("Write ts failded! ret 0x%x. data len %d . data addr %p\n",
                       ret, stTsData.u32Len, stTsData.pDataAddr);
            break;
        }

        PVRRecCheckRecPosition(pRecChn);

    PVR_SAVE_INDEX:
        ret = PVR_Index_SaveToFile(pRecChn->IndexHandle, HI_FALSE);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Save index to file failed ret %x\n", ret);
        }
        PVR_UNLOCK(&pRecChn->stTsCacheMutex);
    } /* end while */

    if (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        HI_INFO_PVR("-----PVRRecSaveToFile exiting with error:%#x...\n", ret);
        PVRRecCheckError(pRecChn, ret);
    }
    else
    {
        //Flush index and data which are both in cache to file
        PVRRecFlushAllToFile(pRecChn);
    }

    pRecChn->bSavingData = HI_FALSE;
    HI_INFO_PVR("<==PVRRecSaveToFile,FileLen:0x%llx.\n", pRecChn->u64CurFileSize);

    return NULL;
}
#else

#ifndef PVR_ACQUIREDATAINDX
STATIC HI_VOID* PVRRecSaveIndexAndStreamRoutine(HI_VOID* args)
{
    HI_U32 u32OverflowTimes = 0;
    HI_S32 ret;
    HI_BOOL bNeedNewIndex = HI_TRUE;
    HI_UNF_DMX_REC_DATA_S stRecData;
    HI_MPI_DMX_REC_INDEX_S stRecIndex;
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S*)args;
    HI_U32 u32TsPacketLen = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);

    memset(&pRecChn->stDmxIdxInfo, 0, sizeof(HI_MPI_DMX_REC_INDEX_S));
    pRecChn->bUseLastDmxIdx = HI_FALSE;
    memset(&stRecData, 0x00, sizeof(stRecData));
    memset(&stRecIndex, 0x00, sizeof(stRecIndex));
#ifdef DUMP_DMX_DATA
    FILE* pvrTsReceive = NULL;
    HI_CHAR saveName[256] = {0};
    snprintf(saveName, 255, "%s_receive.ts",  pRecChn->stUserCfg.szFileName);
    pvrTsReceive = fopen(saveName, "wb");
#endif

    while (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        ret = HI_UNF_DMX_AcquireRecData(pRecChn->DemuxRecHandle, &stRecData, 0);
        if ((ret == HI_SUCCESS) && (stRecData.u32Len > 0))
        {
            if (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
            {
                if (HI_SUCCESS == HI_MPI_DMX_AcquireRecIndex(pRecChn->DemuxRecHandle, &stRecIndex, 0))
                {
                    if (HI_NULL != pRecChn->IndexHandle)
                    {
                        pRecChn->IndexHandle->u64DeltaGlobalOffset += stRecData.u32Len;
                    }
                }

                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);
                continue;
            }

            if ((0 != (stRecData.u32Len % u32TsPacketLen)) || (0 != (stRecData.u32Len % 16)))
            {
                HI_FATAL_PVR("rec size:%u != %u*N, offset:0x%llx.\n", stRecData.u32Len, u32TsPacketLen, pRecChn->u64CurFileSize);
                ret = HI_FAILURE;
                break;
            }

#ifdef DUMP_DMX_DATA
            if (pvrTsReceive)
            {
                fwrite(stRecData.pDataAddr, 1, stRecData.u32Len, pvrTsReceive);
            }
#endif

            /* if cipher, get and save the cipher data */
            if (HI_SUCCESS != PVRRecProcCipherEncrypt(pRecChn,
                    stRecData.u32DataPhyAddr,
                    stRecData.u32DataPhyAddr,
                    stRecData.u32Len))
            {
                HI_ERR_PVR("PVRRecProcCipherEncrypt failed\n");
                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);
                continue;
            }

            PVRRecProcExtCallBack(pRecChn, &stRecData);

            ret = PVRRecCycWriteStream(stRecData, pRecChn);

            (HI_VOID)HI_UNF_DMX_ReleaseRecData(pRecChn->DemuxRecHandle, &stRecData);

            if (HI_SUCCESS != ret)
            {
                break;
            }

            if (pRecChn->IndexHandle != HI_NULL)
            {
                PVR_Index_PushStartWhenTsLead(pRecChn->IndexHandle, pRecChn->u64CurFileSize);
            }

            /* check the buffer status */
            u32OverflowTimes = PVRRecCheckRecBufStatus(u32OverflowTimes, pRecChn);

            PVRRecCheckRecPosition(pRecChn);
        }
        else if ((ret == HI_ERR_DMX_NOAVAILABLE_DATA) || (ret == HI_ERR_DMX_TIMEOUT))
        {
            PVR_USLEEP(100);
            //            continue;
        }
        else
        {
            HI_ERR_PVR("Acquire dmx rec data failed! ret %x\n", ret);
            break;
        }

        if (pRecChn->IndexHandle == HI_NULL)
        {
            continue;
        }

        /*If last index hasn't recorded yet , use last index. Otherwise acquire new index*/
        if (bNeedNewIndex == HI_TRUE)
        {
            if (HI_SUCCESS != HI_MPI_DMX_AcquireRecIndex(pRecChn->DemuxRecHandle, &stRecIndex, 0))
            {
                HI_INFO_PVR("There is no index\n");
                continue;
            }

#ifdef DUMP_DMX_DATA
            if (g_pvrfpIdxReceive)
            {
                fwrite(&stRecIndex, 1, sizeof(stRecIndex), g_pvrfpIdxReceive);
            }
#endif
        }

        /*Thread will acquiring index till index offset lead data offset*/
        if (stRecIndex.u64GlobalOffset + stRecIndex.u32FrameSize <= pRecChn->u64CurFileSize)
        {
            (HI_VOID)PVR_Index_SaveFramePosition(pRecChn->IndexHandle, &stRecIndex);

            bNeedNewIndex = HI_TRUE;
        }
        else
        {
            bNeedNewIndex = HI_FALSE;
        }
    }

    if (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        HI_INFO_PVR("-----PVRRecSaveToFile exiting with error:%#x...\n", ret);
        PVRRecCheckError(pRecChn, ret);
    }

#ifdef DUMP_DMX_DATA
    if (pvrTsReceive)
    {
        fclose(pvrTsReceive);
        pvrTsReceive = NULL;
    }
#endif

    pRecChn->bSavingData = HI_FALSE;
    HI_INFO_PVR("<==PVRRecSaveIndexAndStreamRoutine,FileLen:0x%llx.\n", pRecChn->u64CurFileSize);

    return HI_NULL;
}

#else
#ifdef HI_TEE_PVR_SUPPORT
static HI_S32 PVRRecIndexAndStreamSecure(PVR_REC_CHN_S* pRecChn,
        HI_MPI_DMX_REC_DATA_INDEX_S* pstDataIdx)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_DMX_REC_DATA_S stReeData;
    HI_U32 u32TsPacketLen = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);

    memset(&stReeData, 0x00, sizeof(stReeData));
    if (HI_TEE_ERROR_PVR_NO_ENOUGH_DATA == HI_PVR_TeeGetReeBuffInfo(&pRecChn->stReeBuff,
            &stReeData.pDataAddr, &stReeData.u32DataPhyAddr, &stReeData.u32Len))
    {
        (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
        return HI_TEE_ERROR_PVR_NO_ENOUGH_DATA;
    }
    if ((0 == stReeData.u32Len) || (0 != stReeData.u32Len % u32TsPacketLen) || (0 != stReeData.u32Len % 16))
    {
        HI_FATAL_PVR("Len=%x Mod_%d=%d Mod_16=%d\n",
                     stReeData.u32Len, u32TsPacketLen, stReeData.u32Len % u32TsPacketLen, stReeData.u32Len % 16);
        return HI_FAILURE;
    }
    PVRRecProcExtCallBack(pRecChn, &stReeData);
    s32Ret = PVRRecCycWriteStream(stReeData, pRecChn);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Write file failed ret:%#x! size:%u, addr:%p\n",
                   s32Ret, stReeData.u32Len, stReeData.pDataAddr);
        (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
    }
    return s32Ret;

}
#endif
STATIC HI_S32 PVRRecIndexAndStreamNormal(PVR_REC_CHN_S* pRecChn,
        HI_MPI_DMX_REC_DATA_INDEX_S* pstDataIdx)
{
    HI_S32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_DMX_REC_DATA_S* pstData = HI_NULL;
    HI_U32 u32TsPKSize = PVR_INDEX_GET_TSPACKET_SIZE(pRecChn->IndexHandle);

    for (i = 0; i < pstDataIdx->u32RecDataCnt; i++)
    {
        pstData = &pstDataIdx->stRecData[i];
        if ((0 == pstData->u32Len) || (0 != pstData->u32Len % u32TsPKSize) || (0 != pstData->u32Len % 16))
        {
            HI_FATAL_PVR("Len=%x Mod_%d=%d Mod_16=%d cnt=%d\n",
                         pstData->u32Len, u32TsPKSize, pstData->u32Len % u32TsPKSize, pstData->u32Len % 16, pstDataIdx->u32RecDataCnt);
            (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
            s32Ret = HI_FAILURE;
            break;
        }

        if (HI_SUCCESS != PVRRecProcCipherEncrypt(pRecChn, pstData->u32DataPhyAddr,
                pstData->u32DataPhyAddr, pstData->u32Len))
        {
            HI_ERR_PVR("PVRRecProcCipherEncrypt failed\n");
        }

        PVRRecProcExtCallBack(pRecChn, pstData);

        s32Ret = PVRRecCycWriteStream(*pstData, pRecChn);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("Write file failed ret:%#x! size:%u, addr:%p\n",
                       s32Ret, pstData->u32Len, pstData->pDataAddr);
            (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
            break;
        }
    }
    return s32Ret;
}

STATIC HI_VOID* PVRRecSaveIndexAndStreamRoutine(HI_VOID* args)
{
    HI_U32 i;
    HI_S32 ret = HI_SUCCESS;
    HI_MPI_DMX_REC_INDEX_S* pstIdx = HI_NULL;
    HI_MPI_DMX_REC_DATA_INDEX_S* pstDataIdx = HI_NULL;
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S*)args;
#ifdef HI_TEE_PVR_SUPPORT
    PVR_TEE_REC_PROCESS_INFO_S stTeeRecInfo;
#endif
#ifdef DUMP_DMX_DATA
    FILE* pvrTsReceive = NULL;
    HI_CHAR saveName[256] = {0};
    snprintf(saveName, 255, "%s_receive.ts",  pRecChn->stUserCfg.szFileName);
    pvrTsReceive = fopen(saveName, "wb");
#endif

    pstDataIdx = (HI_MPI_DMX_REC_DATA_INDEX_S*)HI_MALLOC(HI_ID_PVR, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
    if (HI_NULL == pstDataIdx)
    {
        HI_ERR_PVR("malloc failed\n");
        PVRRecCheckError(pRecChn, HI_ERR_PVR_NO_MEM);
        return HI_NULL;
    }
    HI_INFO_PVR("&stDataIdx = %p, len = %#x\n", pstDataIdx, sizeof(HI_MPI_DMX_REC_DATA_INDEX_S));
    while (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        ret = PVRRecRequireDataAndIndex(pRecChn, pstDataIdx);
        if (ret == HI_SUCCESS)
        {
            if (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
            {
                for (i = 0; i < pstDataIdx->u32RecDataCnt; i++)
                {
                    pRecChn->IndexHandle->u64DeltaGlobalOffset += pstDataIdx->stRecData[i].u32Len;
                }

                (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
                continue;
            }
#ifdef HI_TEE_PVR_SUPPORT
            if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
            {
                memset(&stTeeRecInfo, 0x00, sizeof(stTeeRecInfo));
                stTeeRecInfo.hDemuxHandle = pRecChn->DemuxRecHandle;
                stTeeRecInfo.pstDmxRecData = pstDataIdx;
                stTeeRecInfo.pstReeBuff = &pRecChn->stReeBuff;
                stTeeRecInfo.pstTeeBuff = &pRecChn->stTeeBuff;
                stTeeRecInfo.u64DropLength = pRecChn->IndexHandle->u64DeltaGlobalOffset;
                /*CNComment:���һ֡������ʼλ�ã���֤188���룬ͬ���޸�ts���ݺ�index����*/
                HI_PVR_TeeAdjustTsData(pRecChn->u32TeeChnId, &stTeeRecInfo);
                HI_PVR_TeeGetTeeState(pRecChn->u32TeeChnId, &pRecChn->stTeeState);
                pRecChn->stReeBuff.u32Used = 0;
                PVRRecProcExtendCallBack(pRecChn, &pRecChn->stReeBuff, pstDataIdx);
            }
#endif

            for (i = 0; i < pstDataIdx->u32IdxNum; i++)
            {
                pstIdx = &(pstDataIdx->stIndex[i]);
                (HI_VOID)PVR_Index_SaveFramePosition(pRecChn->IndexHandle, pstIdx);
            }
#ifdef HI_TEE_PVR_SUPPORT
            if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
            {
                ret = PVRRecIndexAndStreamSecure(pRecChn, pstDataIdx);
                if (HI_TEE_ERROR_PVR_NO_ENOUGH_DATA == ret)
                {
                    continue;
                }
            }
            else
#endif
            {
                ret = PVRRecIndexAndStreamNormal(pRecChn, pstDataIdx);
            }
            if (ret != HI_SUCCESS)
            { break; }

            PVR_Index_PushStartWhenTsLead(pRecChn->IndexHandle, pRecChn->u64CurFileSize);

            PVRRecCheckRecPosition(pRecChn);

            (HI_VOID)HI_MPI_DMX_ReleaseRecDataAndIndex(pRecChn->DemuxRecHandle, pstDataIdx);
        }
        else if (ret == HI_ERR_DMX_NOAVAILABLE_DATA || ret == HI_ERR_DMX_TIMEOUT)
        {
            PVR_USLEEP(10);
            continue;
        }
        else if (ret == HI_ERR_DMX_OVERFLOW_BUFFER)
        {
            PVRRecProcOverFlow(pRecChn);
        }
        else
        {
            HI_ERR_PVR("Acquire dmx rec data failed! ret %x\n", ret);
            break;
        }
    }

    if (HI_UNF_PVR_REC_STATE_STOP != pRecChn->enState)
    {
        HI_ERR_PVR("-----PVRRecSaveToFile exiting with error:%#x...\n", ret);
        PVRRecCheckError(pRecChn, ret);
    }
#if 1
    if (HI_NULL != pstDataIdx)
    {
        HI_FREE(HI_ID_PVR, pstDataIdx);
        pstDataIdx = HI_NULL;
    }
#else
    pstDataIdx = HI_NULL;
#endif
#ifdef DUMP_DMX_DATA
    if (pvrTsReceive)
    {
        fclose(pvrTsReceive);
        pvrTsReceive = NULL;
    }
#endif

    pRecChn->bSavingData = HI_FALSE;
    HI_INFO_PVR("<==PVRRecSaveIndexAndStreamRoutine,FileLen:0x%llx.\n", pRecChn->u64CurFileSize);

    return HI_NULL;
}
#endif
#endif

STATIC HI_VOID* PVRRecSaveStream(HI_VOID* args)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_DMX_REC_DATA_S stData;
    PVR_REC_CHN_S* pstRecChn = (PVR_REC_CHN_S*)args;

    while (HI_UNF_PVR_REC_STATE_STOP != pstRecChn->enState)
    {
        memset(&stData, 0x00, sizeof(stData));
        ret = HI_UNF_DMX_AcquireRecData(pstRecChn->DemuxRecHandle, &stData, 0);
        if (ret == HI_SUCCESS)
        {
            if (HI_UNF_PVR_REC_STATE_PAUSE == pstRecChn->enState)
            {
                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pstRecChn->DemuxRecHandle, &stData);
                continue;
            }

            if ((0 == stData.u32Len) || (0 != stData.u32Len % 188) || (0 != stData.u32Len % 16))
            {
                HI_FATAL_PVR("Len=%x Mod_188=%d Mod_16=%d\n",
                             stData.u32Len, stData.u32Len % 188, stData.u32Len % 16);
                ret = HI_FAILURE;
                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pstRecChn->DemuxRecHandle, &stData);
                break;
            }

            if (HI_SUCCESS != PVRRecProcCipherEncrypt(pstRecChn, stData.u32DataPhyAddr, stData.u32DataPhyAddr, stData.u32Len))
            {
                HI_ERR_PVR("PVRRecProcCipherEncrypt failed\n");
                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pstRecChn->DemuxRecHandle, &stData);
                continue;
            }

            ret = PVRRecCycWriteStream(stData, pstRecChn);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_PVR("Write file failed ret:%#x! size:%u, addr:%p\n", ret, stData.u32Len, stData.pDataAddr);
                (HI_VOID)HI_UNF_DMX_ReleaseRecData(pstRecChn->DemuxRecHandle, &stData);
                break;
            }

            (HI_VOID)HI_UNF_DMX_ReleaseRecData(pstRecChn->DemuxRecHandle, &stData);
        }
        else if ((HI_ERR_DMX_NOAVAILABLE_DATA == ret) || (HI_ERR_DMX_TIMEOUT == ret))
        {
            PVR_USLEEP(10000);
            continue;
        }
        else
        {
            HI_ERR_PVR("receive rec stream error:%x\n", ret);
            break;
        }
    }

    if (HI_UNF_PVR_REC_STATE_STOP != pstRecChn->enState)
    {
        HI_ERR_PVR("-----PVRRecSaveToFile exiting with error:%#x...\n", ret);
        PVRRecCheckError(pstRecChn, ret);
    }

    pstRecChn->bSavingData = HI_FALSE;
    HI_INFO_PVR("<==PVRRecSaveIndexAndStreamRoutine,FileLen:0x%llx.\n", pstRecChn->u64CurFileSize);

    return HI_NULL;
}

STATIC INLINE HI_S32 PVRRecPrepareCipher(PVR_REC_CHN_S* pChnAttr)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_PVR_CIPHER_S* pCipherCfg = HI_NULL;
    HI_UNF_CIPHER_CTRL_S ctrl;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;

    memset(&stCipherAttr, 0x00, sizeof(stCipherAttr));
    memset(&ctrl, 0x00, sizeof(ctrl));
    pCipherCfg = &(pChnAttr->stUserCfg.stEncryptCfg);
    if (!pCipherCfg->bDoCipher)
    {
        return HI_SUCCESS;
    }

    /* get cipher handle */
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = HI_UNF_CIPHER_CreateHandle(&pChnAttr->hCipher, &stCipherAttr);
    if (ret != HI_SUCCESS)
    {
        pChnAttr->hCipher = 0;
        HI_ERR_PVR("HI_UNF_CIPHER_CreateHandle failed:%#x\n", ret);
        return ret;
    }

    ctrl.enAlg = pCipherCfg->enType;
    ctrl.bKeyByCA = HI_FALSE;
    memcpy(ctrl.u32Key, pCipherCfg->au8Key, sizeof(ctrl.u32Key));
    memset(ctrl.u32IV, 0, sizeof(ctrl.u32IV));
    if (HI_UNF_CIPHER_ALG_AES == pCipherCfg->enType)
    {
        ctrl.enBitWidth = PVR_CIPHER_AES_BIT_WIDTH;
        ctrl.enWorkMode = PVR_CIPHER_AES_WORK_MODD;
        ctrl.enKeyLen = PVR_CIPHER_AES_KEY_LENGTH;
    }
    else if (HI_UNF_CIPHER_ALG_DES == pCipherCfg->enType)
    {
        ctrl.enBitWidth = PVR_CIPHER_DES_BIT_WIDTH;
        ctrl.enWorkMode = PVR_CIPHER_DES_WORK_MODD;
        ctrl.enKeyLen = PVR_CIPHER_DES_KEY_LENGTH;
    }
    else
    {
        ctrl.enBitWidth = PVR_CIPHER_3DES_BIT_WIDTH;
        ctrl.enWorkMode = PVR_CIPHER_3DES_WORK_MODD;
        ctrl.enKeyLen = PVR_CIPHER_3DES_KEY_LENGTH;
    }

    ret = HI_UNF_CIPHER_ConfigHandle(pChnAttr->hCipher, &ctrl);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("HI_UNF_CIPHER_ConfigHandle failed:%#x\n", ret);
        (HI_VOID)HI_UNF_CIPHER_DestroyHandle(pChnAttr->hCipher);
        pChnAttr->hCipher = 0;
        return ret;
    }

    return HI_SUCCESS;
}

STATIC INLINE HI_S32 PVRRecReleaseCipher(PVR_REC_CHN_S*  pChnAttr)
{
    HI_S32 ret = HI_SUCCESS;

    /* free cipher handle */
    if (pChnAttr->hCipher)
    {
        ret = HI_UNF_CIPHER_DestroyHandle(pChnAttr->hCipher);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("release Cipher handle failed! erro:%#x\n", ret);
        }

        pChnAttr->hCipher = 0;
    }

    return ret;
}

STATIC HI_VOID PVRRecCreateChnSetDemuxAttr(HI_UNF_DMX_REC_ATTR_S* pstDmxAttr, PVR_REC_CHN_S* pChnAttr)
{
    pstDmxAttr->u32DmxId       = pChnAttr->stUserCfg.u32DemuxID;
    pstDmxAttr->u32RecBufSize  = pChnAttr->stUserCfg.u32DavBufSize;
    pstDmxAttr->enVCodecType   = pChnAttr->stUserCfg.enIndexVidType;
    pstDmxAttr->u32IndexSrcPid = pChnAttr->stUserCfg.u32IndexPid;

    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS == pChnAttr->stUserCfg.enStreamType)
    {
        pstDmxAttr->enRecType = HI_UNF_DMX_REC_TYPE_ALL_PID;
    }
    else
    {
        pstDmxAttr->enRecType = HI_UNF_DMX_REC_TYPE_SELECT_PID;
    }

    if (HI_TRUE == pChnAttr->stUserCfg.bIsClearStream)
    {
        pstDmxAttr->bDescramed = HI_TRUE;
    }
    else
    {
        pstDmxAttr->bDescramed = HI_FALSE;
    }

    switch (pChnAttr->stUserCfg.enIndexType)
    {
        case HI_UNF_PVR_REC_INDEX_TYPE_VIDEO :
            pstDmxAttr->enIndexType = HI_UNF_DMX_REC_INDEX_TYPE_VIDEO;
            break;

        case HI_UNF_PVR_REC_INDEX_TYPE_AUDIO :
            pstDmxAttr->enIndexType = HI_UNF_DMX_REC_INDEX_TYPE_AUDIO;
            break;

        case HI_UNF_PVR_REC_INDEX_TYPE_NONE :
        default :
            pstDmxAttr->enIndexType = HI_UNF_DMX_REC_INDEX_TYPE_NONE;
    }

    if (HI_UNF_PVR_TS_PACKET_192 == pChnAttr->stUserCfg.enTsPacketType)
    {
        pstDmxAttr->enTsPacketType = HI_UNF_DMX_TS_PACKET_192;
    }
    else
    {
        pstDmxAttr->enTsPacketType = HI_UNF_DMX_TS_PACKET_188;
    }

#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE == pChnAttr->stUserCfg.enSecureMode)
    {
        pstDmxAttr->enSecureMode = HI_UNF_DMX_SECURE_MODE_TEE;
    }
    else
    {
        pstDmxAttr->enSecureMode = HI_UNF_DMX_SECURE_MODE_NONE;
    }
#endif
    return;
}

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    #if defined(PVR_APPEND_MODE_SUPPORT) || defined(PVR_PID_CHANGE_SUPPORT)
/**//*CNcomment: ����ӿ���Ҫ����¼��ʱ��extra bufferʱʹ�ã���Ϊ��ʱ�ļ�����Ĵ򿪲�������O_DIRECT������
                            ��ʱ��Ҫ��֤write ������512���룬�ú�������������֤д�ļ�ʱwritePos ��512�����*/
STATIC INLINE HI_S32 PVRReadAlignDataFromFile(PVR_REC_CHN_S *pChnAttr, HI_U64 u64Offset, HI_U64 u64GlobalOffset)
{
    HI_S32 s32Ret = HI_FAILURE;
    ssize_t readLen = 0;
    HI_S32 u32ReadSize = 0;
    PVR_FILE64 sysFd = PVR_FILE_INVALID_FILE;
    HI_U8 *pDataAddr = HI_NULL;
    PVR_EXTRA_BUFFER_INFO_S* pstExtraBufferInfo = PVR_INDEX_GET_EXTRA_BUFFER_INFO_ADDR(pChnAttr->IndexHandle);

    u32ReadSize = u64Offset % PVR_DIO_ALIGN_SIZE;
    pDataAddr= HI_MALLOC(HI_ID_PVR, u32ReadSize);
    if (HI_NULL == pDataAddr)
    {
        HI_ERR_PVR("malloc memory failed! \n");
        return HI_ERR_PVR_NO_MEM;
    }

    sysFd = PVR_OPEN64(pChnAttr->stUserCfg.szFileName, PVR_FOPEN_MODE_DATA_READ);
    if (PVR_FILE_INVALID_FILE == sysFd)
    {
        HI_ERR_PVR("open %s failed! \n",pChnAttr->stUserCfg.szFileName);
        HI_FREE(HI_ID_PVR, pDataAddr);
        pDataAddr = HI_NULL;
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    memset(pDataAddr, 0x00, u32ReadSize);

    readLen = PVR_PREAD64(pDataAddr, u32ReadSize, sysFd, u64Offset - u32ReadSize);
    if (-1 == readLen)
    {
        HI_ERR_PVR("read failed: want: %lu, Actually: %d, fd: %d, u64Offset: %lld\n", u32ReadSize, readLen, sysFd, u64Offset);
        HI_FREE(HI_ID_PVR, pDataAddr);
        pDataAddr = HI_NULL;
        PVR_CLOSE64(sysFd);
        return HI_ERR_PVR_FILE_CANT_READ;
    }
    else
    {
        pChnAttr->u64CurWritePos -= u32ReadSize;
        pChnAttr->u64CurFileSize -= u32ReadSize;

        s32Ret = PVR_TS_CACHE_BUFFER_Reset(&(pstExtraBufferInfo->stTsCacheBufInfo), u64GlobalOffset - u32ReadSize);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("reset TS_CACHE_BUFFER failed! \n");
            HI_FREE(HI_ID_PVR, pDataAddr);
            pDataAddr = HI_NULL;
            PVR_CLOSE64(sysFd);
            return s32Ret;
        }

#ifdef PVR_PID_CHANGE_SUPPORT
        pChnAttr->IndexHandle->pstPidCtrl->stPidInfo[pChnAttr->IndexHandle->u32CurRecIdx].u64GlobalOffset -= u32ReadSize;
        pChnAttr->IndexHandle->pstPidCtrl->stPidInfo[pChnAttr->IndexHandle->u32CurRecIdx].u64FileOffset-= u32ReadSize;
#endif

        s32Ret = PVR_TS_CACHE_BUFFER_WriteToBuffer(&pstExtraBufferInfo->stTsCacheBufInfo, pDataAddr, u32ReadSize);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("write to buffer failed ! \n");
        }
    }

    HI_FREE(HI_ID_PVR, pDataAddr);
    pDataAddr = HI_NULL;
    PVR_CLOSE64(sysFd);

    return s32Ret;
}
    #endif
#endif

static HI_S32 PVRRecFileLinearizationInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    HI_INFO_PVR("PVR: ===========> Linearization init.\n");

    /* set all linearization channel as INVALID status */
    for (i = 0; i < PVR_LINEARIZATION_MAX_NUM; i++)
    {
        PVR_MUTEX_INIT(&(g_stPvrLinearizationChns[i].stMutex), s32Ret);
        if (HI_SUCCESS != s32Ret)
        {
            for (j = 0; j < i; j++)
            {
                (HI_VOID)pthread_mutex_destroy(&(g_stPvrLinearizationChns[j].stMutex));
            }
            HI_ERR_PVR("init mutex lock for PVR linerization chn%d failed \n", i);
            return HI_FAILURE;
        }

        PVR_LOCK(&(g_stPvrLinearizationChns[i].stMutex));
        g_stPvrLinearizationChns[i].u32ChnId = i + PVR_LINEARIZATION_START_NUM;
        g_stPvrLinearizationChns[i].bUsed= HI_FALSE;
        g_stPvrLinearizationChns[i].bStopLinerization = HI_FALSE;
        g_stPvrLinearizationChns[i].u32TotalNeedFixFrameNum = 0;
        g_stPvrLinearizationChns[i].u32FixedFrameNum = 0;
        memset(&g_stPvrLinearizationChns[i].stRepairCtrl, 0x00, sizeof(PVR_REPAIR_CTRL_S));
        g_stPvrLinearizationChns[i].stRepairCtrl.s32NewIdxFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32NewTsFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32OldIdxFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32OldTsFd = PVR_FILE_INVALID_FILE;
        memset(&g_stPvrLinearizationChns[i].stRewindInfo, 0x00, sizeof(PVR_REWIND_REPAIR_S));
        memset(&g_stPvrLinearizationChns[i].stUserCfg, 0x00, sizeof(HI_UNF_PVR_LINEARIZATION_ATTR_S));
        memset(g_stPvrLinearizationChns[i].szSrcIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
        memset(g_stPvrLinearizationChns[i].szDstIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
        PVR_UNLOCK(&(g_stPvrLinearizationChns[i].stMutex));
    }

    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearizationDeInit(HI_VOID)
{
    HI_U32 i = 0;

    /* set all linearization channel as INVALID status */
    for (i = 0; i < PVR_LINEARIZATION_MAX_NUM; i++)
    {
        if (g_stPvrLinearizationChns[i].bUsed != HI_FALSE)
        {
            HI_ERR_PVR("Linearization chn%d is in use, can NOT deInit Linearization!\n", i);
            return HI_ERR_PVR_BUSY;
        }

        PVR_LOCK(&(g_stPvrLinearizationChns[i].stMutex));
        g_stPvrLinearizationChns[i].bUsed = HI_FALSE;
        g_stPvrLinearizationChns[i].bStopLinerization = HI_FALSE;
        g_stPvrLinearizationChns[i].u32TotalNeedFixFrameNum = 0;
        g_stPvrLinearizationChns[i].u32FixedFrameNum = 0;
        memset(&g_stPvrLinearizationChns[i].stRepairCtrl, 0x00, sizeof(PVR_REPAIR_CTRL_S));
        g_stPvrLinearizationChns[i].stRepairCtrl.s32NewIdxFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32NewTsFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32OldIdxFd = PVR_FILE_INVALID_FILE;
        g_stPvrLinearizationChns[i].stRepairCtrl.s32OldTsFd = PVR_FILE_INVALID_FILE;
        memset(&g_stPvrLinearizationChns[i].stRewindInfo, 0x00, sizeof(PVR_REWIND_REPAIR_S));
        memset(&g_stPvrLinearizationChns[i].stUserCfg, 0x00, sizeof(HI_UNF_PVR_LINEARIZATION_ATTR_S));
        memset(g_stPvrLinearizationChns[i].szSrcIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
        memset(g_stPvrLinearizationChns[i].szDstIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
        PVR_UNLOCK(&(g_stPvrLinearizationChns[i].stMutex));
        (HI_VOID)pthread_mutex_destroy(&(g_stPvrLinearizationChns[i].stMutex));
    }

    return HI_SUCCESS;
}

static PVR_LINEARIZATION_CHN_S* PVRRecFileLinearizationGetFreeChn()
{
    HI_U32 i = 0;
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;

    for (i = 0; i < PVR_LINEARIZATION_MAX_NUM; i++)
    {
        pstLinearChn = &g_stPvrLinearizationChns[i];
        if (HI_FALSE == pstLinearChn->bUsed)
        {
            PVR_LOCK(&pstLinearChn->stMutex);
            pstLinearChn->bUsed = HI_TRUE;
            pstLinearChn->bStopLinerization = HI_FALSE;
            pstLinearChn->u32TotalNeedFixFrameNum = 0;
            pstLinearChn->u32FixedFrameNum = 0;
            memset(&pstLinearChn->stRepairCtrl, 0x00, sizeof(PVR_REPAIR_CTRL_S));
            pstLinearChn->stRepairCtrl.s32NewIdxFd = PVR_FILE_INVALID_FILE;
            pstLinearChn->stRepairCtrl.s32NewTsFd = PVR_FILE_INVALID_FILE;
            pstLinearChn->stRepairCtrl.s32OldIdxFd = PVR_FILE_INVALID_FILE;
            pstLinearChn->stRepairCtrl.s32OldTsFd = PVR_FILE_INVALID_FILE;
            memset(&pstLinearChn->stRewindInfo, 0x00, sizeof(PVR_REWIND_REPAIR_S));
            memset(&pstLinearChn->stUserCfg, 0x00, sizeof(HI_UNF_PVR_LINEARIZATION_ATTR_S));
            memset(pstLinearChn->szSrcIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
            memset(pstLinearChn->szDstIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
            PVR_UNLOCK(&pstLinearChn->stMutex);
            return pstLinearChn;
        }
    }

    return HI_NULL;
}

static PVR_LINEARIZATION_CHN_S* PVRRecFileLinearizationGetChnById(HI_U32 u32ChnId)
{
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;

    if ((u32ChnId < PVR_LINEARIZATION_START_NUM) || (u32ChnId >= PVR_LINEARIZATION_MAX_NUM + PVR_LINEARIZATION_START_NUM))
    {
        HI_ERR_PVR("invalid chanelId(%u), MaxId: %u\n", u32ChnId, PVR_LINEARIZATION_MAX_NUM + PVR_LINEARIZATION_START_NUM - 1);
        return HI_NULL;
    }

    pstLinearChn = &g_stPvrLinearizationChns[u32ChnId - PVR_LINEARIZATION_START_NUM];
    if (HI_FALSE == pstLinearChn->bUsed)
    {
        HI_ERR_PVR("The current channel is in use! ChnnelID: %u\n", u32ChnId);
        return HI_NULL;
    }

    return (PVR_LINEARIZATION_CHN_S*)pstLinearChn;
}

static HI_S32 PVRRecFileLinearizationReleaseChn(HI_U32 u32ChnId)
{
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;

    CHECK_REC_INIT(&g_stRecInit);
    pstLinearChn = PVRRecFileLinearizationGetChnById(u32ChnId);
    if (HI_NULL == pstLinearChn)
    {
        HI_ERR_PVR("invalid chanel or the current channel is in use! channelID: %u\n", u32ChnId);
        return HI_FAILURE;
    }

    pstLinearChn->bUsed = HI_FALSE;
    pstLinearChn->bStopLinerization = HI_FALSE;
    pstLinearChn->u32TotalNeedFixFrameNum = 0;
    pstLinearChn->u32FixedFrameNum = 0;
    memset(&pstLinearChn->stRepairCtrl, 0x00, sizeof(PVR_REPAIR_CTRL_S));
    pstLinearChn->stRepairCtrl.s32NewIdxFd = PVR_FILE_INVALID_FILE;
    pstLinearChn->stRepairCtrl.s32NewTsFd = PVR_FILE_INVALID_FILE;
    pstLinearChn->stRepairCtrl.s32OldIdxFd = PVR_FILE_INVALID_FILE;
    pstLinearChn->stRepairCtrl.s32OldTsFd = PVR_FILE_INVALID_FILE;
    memset(&pstLinearChn->stRewindInfo, 0x00, sizeof(PVR_REWIND_REPAIR_S));
    memset(&pstLinearChn->stUserCfg, 0x00, sizeof(HI_UNF_PVR_LINEARIZATION_ATTR_S));
    memset(pstLinearChn->szSrcIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
    memset(pstLinearChn->szDstIndexFileName, 0x00, PVR_MAX_FILENAME_LEN * sizeof(HI_CHAR));
    
    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearizationCheckUserCfg(const HI_UNF_PVR_LINEARIZATION_ATTR_S *pstUserCfg, HI_UNF_PVR_LINEARIZATION_ATTR_S *pstLinearAttr)
{
    HI_CHAR szSrcIndexFileName[PVR_MAX_FILENAME_LEN] = {0};
    HI_CHAR szSrcRealFileName[PATH_MAX] = {0};
    HI_CHAR szDstRealFileName[PATH_MAX] = {0};

    /*����ļ��������Ƿ�һ��*/
    if ((strlen(pstUserCfg->szSrcFileName) != pstUserCfg->u32SrcFileNameLen)
            ||(strlen(pstUserCfg->szDstFileName) != pstUserCfg->u32DstFileNameLen)
            ||(pstUserCfg->u32SrcFileNameLen >= PVR_MAX_FILENAME_LEN))
    {
        HI_ERR_PVR("file name length doesn't match, strlen(srcFileName): %u, SrcFileNameLen: %u, strlen(dstFileName): %u, DstFileNameLen: %u\n",
                            strlen(pstUserCfg->szSrcFileName), pstUserCfg->u32SrcFileNameLen,
                            strlen(pstUserCfg->szDstFileName), pstUserCfg->u32DstFileNameLen);
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*realpath �ļ���*/
    if(HI_NULL == realpath(pstUserCfg->szSrcFileName, szSrcRealFileName))
    {
        HI_ERR_PVR("get real fileName failed! szFileName: %s\n", pstUserCfg->szSrcFileName);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }
    if(strlen(szSrcRealFileName) >= PVR_MAX_FILENAME_LEN)
    {
        HI_ERR_PVR("The Absolute fileName is too long, FileNameLen: %u ,MaxFileNameLen: %u\n", strlen(szSrcRealFileName), PVR_MAX_FILENAME_LEN);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }

    memcpy(szDstRealFileName, pstUserCfg->szDstFileName, strlen(pstUserCfg->szDstFileName) * sizeof(HI_CHAR));
    PVRRecTransformFileName(szDstRealFileName);
    if(strlen(szDstRealFileName) >= PVR_MAX_FILENAME_LEN)
    {
        HI_ERR_PVR("The Absolute fileName is too long, FileNameLen: %u ,MaxFileNameLen: %u\n", strlen(szDstRealFileName), PVR_MAX_FILENAME_LEN);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }

    snprintf(pstLinearAttr->szSrcFileName, PVR_MAX_FILENAME_LEN - 1,"%s", szSrcRealFileName);
    snprintf(pstLinearAttr->szDstFileName, PVR_MAX_FILENAME_LEN - 1,"%s", szDstRealFileName);
    pstLinearAttr->u32SrcFileNameLen= strlen(pstLinearAttr->szSrcFileName);
    pstLinearAttr->u32DstFileNameLen= strlen(pstLinearAttr->szDstFileName);

    (HI_VOID)PVR_Index_GetIdxFileName(szSrcIndexFileName, pstLinearAttr->szSrcFileName);

     /*����޸��ļ��Ƿ����*/
    if ((HI_FALSE == PVR_CHECK_FILE_EXIST64(pstLinearAttr->szSrcFileName)) || (HI_FALSE == PVR_CHECK_FILE_EXIST64(szSrcIndexFileName)))
    {
        HI_ERR_PVR("Linear file doesn't exist! ret = %x\n", HI_ERR_PVR_FILE_NOT_EXIST);
        return HI_ERR_PVR_FILE_NOT_EXIST;
    }

    /*����޸��ļ��Ƿ���¼��*/
    if (HI_TRUE == PVRRecCheckFileRecording(pstLinearAttr->szSrcFileName))
    {
        HI_ERR_PVR("The current file is being recorded, doesn't support linearization! ret = %x\n", HI_ERR_PVR_NOT_SUPPORT);
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    /*ɾ��һ�����ļ�*/
    (HI_VOID)HI_PVR_RemoveFile(pstLinearAttr->szDstFileName);

    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearBufferInit(PVR_LINEAR_BUFFER_S *pstBuf, HI_U32 u32Size)
{
    pstBuf->pu8Addr = (HI_U8 *)HI_MALLOC(HI_ID_PVR, u32Size * sizeof(HI_U8));
    if (HI_NULL == pstBuf->pu8Addr)
    {
        HI_ERR_PVR("malloc linear buffer error!\n");
        return HI_ERR_PVR_NO_MEM;
    }

    memset(pstBuf->pu8Addr, 0x0, u32Size * sizeof(HI_U8));
    pstBuf->u32Length = u32Size;
    pstBuf->u32Read = 0;
    pstBuf->u32Write = 0;
    pstBuf->u32Used = 0;
    pstBuf->u64Offset = 0;

    return HI_SUCCESS;
}

static HI_VOID PVRRecFileLinearBufferDeInit(PVR_LINEAR_BUFFER_S *pstBuf)
{
    if (HI_NULL != pstBuf->pu8Addr)
    {
        memset(pstBuf->pu8Addr, 0x0, pstBuf->u32Length* sizeof(HI_U8));
        HI_FREE(HI_ID_PVR, pstBuf->pu8Addr);
    }

    memset(pstBuf, 0x0, sizeof(PVR_LINEAR_BUFFER_S));

    return ;
}

static HI_S32 PVRRecFileLinearBufferReadFile(PVR_FILE64 s32Fd, HI_U64 u64Offset, HI_U32 u32Size, PVR_LINEAR_BUFFER_S *pstBuf)
{
    HI_S32 s32Length = 0;
    HI_U8 *pu8Buf = pstBuf->pu8Addr + pstBuf->u32Write;
    HI_U32 u32Len1 = 0;
    HI_U32 u32Len2 = 0;
    HI_S64 s64Offset = (HI_S64)u64Offset;
    HI_S32 s32DeltaLen = (0 > s64Offset) ? (HI_S32)abs(s64Offset) : 0;

    if (0 == u32Size)
    {
        return HI_SUCCESS;
    }

    if (u32Size > (pstBuf->u32Length - pstBuf->u32Used))
    {
        HI_ERR_PVR("current read size(%u) more than buffer free size(%u)\n", u32Size, pstBuf->u32Length - pstBuf->u32Used);
        return HI_FAILURE;
    }

    if (0 != s32DeltaLen)
    {
        if (s32DeltaLen > (HI_S32)u32Size)
        {
            HI_ERR_PVR("DeltaLen(%d) more than Readsize(%u)\n", s32DeltaLen, u32Size);
            return HI_FAILURE;
        }
        HI_WARN_PVR("u64Offset: %lld, s32DeltaLen: %d, size: %u\n", u64Offset, s32DeltaLen, u32Size);

        pstBuf->u32Write  = (pstBuf->u32Write + s32DeltaLen)%pstBuf->u32Length;
        pstBuf->u32Used += s32DeltaLen;
        u64Offset = 0;
        u32Size = u32Size - s32DeltaLen;
    }

    if (pstBuf->u32Write + u32Size <= pstBuf->u32Length)
    {
        u32Len1 = u32Size;
    }
    else
    {
        u32Len1 = pstBuf->u32Length - pstBuf->u32Write;
        u32Len2 = u32Size - u32Len1;
    }

    s32Length = PVR_PREAD64(pu8Buf, u32Len1, s32Fd, u64Offset);
    if (s32Length != u32Len1)
    {
        HI_ERR_PVR("read tsData from old ts file failed, expect:%u; actual:%u\n", u32Len1, s32Length);
        return HI_ERR_PVR_FILE_CANT_READ;
    }

    if (0 != u32Len2)
    {
        s32Length = PVR_PREAD64(pstBuf->pu8Addr, u32Len2, s32Fd, u64Offset + (HI_U64)u32Len1);
        if (s32Length != u32Len2)
        {
            HI_ERR_PVR("read tsData from old ts file failed, expect:%u; actual:%u\n", u32Len2, s32Length);
            return HI_ERR_PVR_FILE_CANT_READ;
        }
    }

    pstBuf->u32Write += u32Len1;
    pstBuf->u32Used += u32Size;
    if (0 != u32Len2)
    {
        pstBuf->u32Write = u32Len2;
    }

    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearBufferWriteFile(PVR_FILE64 s32Fd, PVR_LINEAR_BUFFER_S *pstBuf)
{
    HI_S32 s32Length = 0;
    HI_U8 *pu8Buf = pstBuf->pu8Addr + pstBuf->u32Read;
    HI_U32 u32Len = (pstBuf->u32Used / 512) * 512;
    HI_U32 u32Len1 = 0;
    HI_U32 u32Len2 = 0;

    if (0 == u32Len)
    {
        return HI_SUCCESS;
    }

    if (pstBuf->u32Read + u32Len <= pstBuf->u32Length)
    {
        u32Len1 = u32Len;
    }
    else
    {
        u32Len1 = pstBuf->u32Length - pstBuf->u32Read;
        u32Len2 = u32Len - u32Len1;
    }

    s32Length = PVR_PWRITE64(pu8Buf, u32Len1, s32Fd, pstBuf->u64Offset);
    if (s32Length != u32Len1)
    {
        HI_ERR_PVR("write tsData to new ts file failed, expect:%u; actual:%u\n", u32Len1, s32Length);
        return HI_ERR_PVR_FILE_CANT_WRITE;
    }

    s32Length = PVR_PWRITE64(pstBuf->pu8Addr, u32Len2, s32Fd, pstBuf->u64Offset + (HI_U64)u32Len1);
    if (s32Length != u32Len2)
    {
        HI_ERR_PVR("write tsData to new ts file failed, expect:%u; actual:%u\n", u32Len2, s32Length);
        return HI_ERR_PVR_FILE_CANT_WRITE;
    }

    pstBuf->u32Read = (pstBuf->u32Read + u32Len) % pstBuf->u32Length;
    pstBuf->u32Used -= u32Len;
    pstBuf->u64Offset += (HI_U64)u32Len;

    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearBufferFlushAll(PVR_FILE64 s32Fd, PVR_LINEAR_BUFFER_S *pstBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 == pstBuf->u32Used)
    {
        return HI_SUCCESS;
    }

    pstBuf->u32Used = (pstBuf->u32Used/512 + 1) * 512;

    s32Ret = PVRRecFileLinearBufferWriteFile(s32Fd, pstBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("flush all data to new file faile! ret = %x, reminderDataSize: %u\n", s32Ret, pstBuf->u32Used);
    }

    return s32Ret;
}

static HI_S32 PVRRecFileLinearizationSetAttr(PVR_LINEARIZATION_CHN_S* pstLinearChn)
{
    PVR_REPAIR_CTRL_S* pstRepairCtrl = &(pstLinearChn->stRepairCtrl);

    (HI_VOID)PVR_Index_GetIdxFileName(pstLinearChn->szSrcIndexFileName, pstLinearChn->stUserCfg.szSrcFileName);
    (HI_VOID)PVR_Index_GetIdxFileName(pstLinearChn->szDstIndexFileName, pstLinearChn->stUserCfg.szDstFileName);

    pstRepairCtrl->s32OldIdxFd = PVR_OPEN(pstLinearChn->szSrcIndexFileName, PVR_FOPEN_MODE_INDEX_READ);
    if (PVR_FILE_INVALID_FILE == pstRepairCtrl->s32OldIdxFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", pstLinearChn->szSrcIndexFileName);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    pstRepairCtrl->s32OldTsFd = PVR_OPEN64(pstLinearChn->stUserCfg.szSrcFileName, PVR_FOPEN_MODE_DATA_READ);
    if (PVR_FILE_INVALID_FILE == pstRepairCtrl->s32OldTsFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", pstLinearChn->stUserCfg.szSrcFileName);
        PVR_CLOSE(pstRepairCtrl->s32OldIdxFd);
        pstRepairCtrl->s32OldIdxFd = PVR_FILE_INVALID_FILE;
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    pstRepairCtrl->s32NewTsFd = PVR_OPEN64(pstLinearChn->stUserCfg.szDstFileName, PVR_FOPEN_MODE_DATA_WRITE);
    if (PVR_FILE_INVALID_FILE == pstRepairCtrl->s32NewTsFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", pstLinearChn->stUserCfg.szDstFileName);
        PVR_CLOSE64(pstRepairCtrl->s32OldTsFd);
        PVR_CLOSE(pstRepairCtrl->s32OldIdxFd);
        pstRepairCtrl->s32OldIdxFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32OldTsFd = PVR_FILE_INVALID_FILE;
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    pstRepairCtrl->s32NewIdxFd = PVR_OPEN(pstLinearChn->szDstIndexFileName, PVR_FOPEN_MODE_INDEX_WRITE);
    if (PVR_FILE_INVALID_FILE == pstRepairCtrl->s32NewIdxFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", pstLinearChn->szDstIndexFileName);
        PVR_CLOSE64(pstRepairCtrl->s32OldTsFd);
        PVR_CLOSE(pstRepairCtrl->s32OldIdxFd);
        PVR_CLOSE64(pstRepairCtrl->s32NewTsFd);
        pstRepairCtrl->s32OldIdxFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32OldTsFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32NewTsFd = PVR_FILE_INVALID_FILE;
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    memset(&pstRepairCtrl->stLinearBuf, 0x0, sizeof(pstRepairCtrl->stLinearBuf));
    if (HI_SUCCESS != PVRRecFileLinearBufferInit(&pstRepairCtrl->stLinearBuf, PVR_STUB_TSDATA_SIZE))
    {
        HI_ERR_PVR("init linear buffer error!\n");
        PVR_CLOSE64(pstRepairCtrl->s32OldTsFd);
        PVR_CLOSE(pstRepairCtrl->s32OldIdxFd);
        PVR_CLOSE64(pstRepairCtrl->s32NewTsFd);
        PVR_CLOSE(pstRepairCtrl->s32NewIdxFd);
        pstRepairCtrl->s32OldIdxFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32OldTsFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32NewTsFd = PVR_FILE_INVALID_FILE;
        pstRepairCtrl->s32NewIdxFd = PVR_FILE_INVALID_FILE;
        return HI_ERR_PVR_NO_MEM;
    }

    return HI_SUCCESS;
}

static HI_VOID PVRRecFileLinearizationResetAttr(PVR_LINEARIZATION_CHN_S *pstLinearChn)
{
    if (PVR_FILE_INVALID_FILE != pstLinearChn->stRepairCtrl.s32OldTsFd)
    {
        PVR_CLOSE64(pstLinearChn->stRepairCtrl.s32OldTsFd);
        pstLinearChn->stRepairCtrl.s32OldTsFd = PVR_FILE_INVALID_FILE;
    }

    if (PVR_FILE_INVALID_FILE != pstLinearChn->stRepairCtrl.s32OldIdxFd)
    {
        PVR_CLOSE(pstLinearChn->stRepairCtrl.s32OldIdxFd);
        pstLinearChn->stRepairCtrl.s32OldIdxFd = PVR_FILE_INVALID_FILE;
    }

    if (PVR_FILE_INVALID_FILE != pstLinearChn->stRepairCtrl.s32NewTsFd)
    {
        PVR_FSYNC64(pstLinearChn->stRepairCtrl.s32NewTsFd);
        PVR_CLOSE64(pstLinearChn->stRepairCtrl.s32NewTsFd);
        pstLinearChn->stRepairCtrl.s32NewTsFd = PVR_FILE_INVALID_FILE;
    }

    if (PVR_FILE_INVALID_FILE != pstLinearChn->stRepairCtrl.s32NewIdxFd)
    {
        PVR_FSYNC(pstLinearChn->stRepairCtrl.s32NewIdxFd);
        PVR_CLOSE(pstLinearChn->stRepairCtrl.s32NewIdxFd);
        pstLinearChn->stRepairCtrl.s32NewIdxFd = PVR_FILE_INVALID_FILE;
    }

    (HI_VOID)PVRRecFileLinearBufferDeInit(&pstLinearChn->stRepairCtrl.stLinearBuf);

    pstLinearChn->bStopLinerization = HI_FALSE;

    return ;
}

static HI_S32 PVRRecFileLinearizationReadOneEntry(PVR_REPAIR_CTRL_S *pstRepairCtrl)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 != pstRepairCtrl->u32Length1)
    {
        s32Ret = PVRRecFileLinearBufferReadFile(pstRepairCtrl->s32OldTsFd, pstRepairCtrl->u64Offset1, pstRepairCtrl->u32Length1, &pstRepairCtrl->stLinearBuf);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("read tsData length1 from old ts file failed, s32Ret = %x\n", s32Ret);
            return s32Ret;
        }
    }

    if (0 != pstRepairCtrl->u32Length2)
    {
        s32Ret = PVRRecFileLinearBufferReadFile(pstRepairCtrl->s32OldTsFd, pstRepairCtrl->u64Offset2, pstRepairCtrl->u32Length2, &pstRepairCtrl->stLinearBuf);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("read tsData length2 from old ts file failed, s32Ret = %x\n", s32Ret);
            return s32Ret;
        }
    }

    if (0 != pstRepairCtrl->u32Length3)
    {
        s32Ret = PVRRecFileLinearBufferReadFile(pstRepairCtrl->s32OldTsFd, pstRepairCtrl->u64Offset3, pstRepairCtrl->u32Length3, &pstRepairCtrl->stLinearBuf);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("read tsData length3 from old ts file failed, s32Ret = %x\n", s32Ret);
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 PVRRecFileLinearizationSaveTsData(PVR_REPAIR_CTRL_S *pstRepairCtrl)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PVRRecFileLinearizationReadOneEntry(pstRepairCtrl);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("read one entry from old ts file failed!, Ret = %x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = PVRRecFileLinearBufferWriteFile(pstRepairCtrl->s32NewTsFd, &pstRepairCtrl->stLinearBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("write ts data to new ts file failed!, Ret = %x\n", s32Ret);
        return s32Ret;
    }

    pstRepairCtrl->u32Length1 = 0;
    pstRepairCtrl->u32Length2 = 0;
    pstRepairCtrl->u32Length3 = 0;
    pstRepairCtrl->u64Offset1 = 0;
    pstRepairCtrl->u64Offset2 = 0;
    pstRepairCtrl->u64Offset3 = 0;

    return HI_SUCCESS;
}

static HI_VOID *PVRRecFileLinearizationThread(HI_VOID* pPara)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32ChangeSuccess = HI_SUCCESS;
    PVR_LINEARIZATION_CHN_S *pstLinearChn = (PVR_LINEARIZATION_CHN_S*)pPara;
    PVR_REWIND_REPAIR_S *pstRewindInfo = &(pstLinearChn->stRewindInfo);
    PVR_REPAIR_CTRL_S *pstRepairCtrl = &(pstLinearChn->stRepairCtrl);

    /*��������Ts���ݷֱ�ˢ���µ��ļ���*/
    while(pstRepairCtrl->u32IdxPos < pstLinearChn->u32TotalNeedFixFrameNum)
    {
        PVR_LOCK(&pstLinearChn->stMutex);
        if (HI_TRUE == pstLinearChn->bStopLinerization)
        {
            pstLinearChn->bStopLinerization = HI_FALSE;
            s32Ret = HI_FAILURE;
            PVR_UNLOCK(&pstLinearChn->stMutex);
            break;
        }

        s32Ret = PVR_Index_LinearizationGetOneIndex(pstRepairCtrl, pstRewindInfo);
        if (HI_SUCCESS != s32Ret)
        {
            if (HI_ERR_PVR_INDEX_DATA_ERR == s32Ret)
            {
                if (0 != pstRepairCtrl->u32IdxPos)
                {
                    HI_ERR_PVR("current frame size is zero, idxPos: %u\n", pstRepairCtrl->u32IdxPos);
                }
                pstRepairCtrl->u32IdxPos++;
                pstLinearChn->u32FixedFrameNum++;
                PVR_UNLOCK(&pstLinearChn->stMutex);
                PVR_USLEEP(1000);
                continue;
            }
            else
            {
                HI_ERR_PVR("get one Index failed, ret = %x!\n", s32Ret);
                PVR_UNLOCK(&pstLinearChn->stMutex);
                break;
            }
        }

        (HI_VOID)PVR_Index_LinearizationGetTsOffsetByIndex(pstRepairCtrl, pstRewindInfo);

        (HI_VOID)PVR_Index_LinearizationProccessOneIndex(pstRepairCtrl, pstRewindInfo);

        s32Ret = PVR_Index_LinearizationSaveOneIndex(pstRepairCtrl, pstRewindInfo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("save Index failed, ret = %x!\n", s32Ret);
            PVR_UNLOCK(&pstLinearChn->stMutex);
            break;
        }

        s32Ret = PVRRecFileLinearizationSaveTsData(pstRepairCtrl);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("process tsData failed, ret = %x!\n", s32Ret);
            PVR_UNLOCK(&pstLinearChn->stMutex);
            break;
        }

        pstRepairCtrl->u32IdxPos++;
        pstLinearChn->u32FixedFrameNum++;
        PVR_UNLOCK(&pstLinearChn->stMutex);
        PVR_USLEEP(1000);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Processing data error! ret = %x\n", s32Ret);
    }

    if (HI_SUCCESS != PVRRecFileLinearBufferFlushAll(pstRepairCtrl->s32NewTsFd, &pstRepairCtrl->stLinearBuf))
    {
        HI_ERR_PVR("flush linear buffer reminder data to new file. \n");
        s32Ret = HI_FAILURE;
    }

    if (pstLinearChn->u32FixedFrameNum != pstLinearChn->u32TotalNeedFixFrameNum)
    {
        HI_ERR_PVR("repaire failed, FixedFrmNum/TotalNeedFixNum: %u/%u\n",pstLinearChn->u32FixedFrameNum, pstLinearChn->u32TotalNeedFixFrameNum);
        s32Ret = HI_FAILURE;
    }

    /*������������ts�����޸���ɺ�ˢ������ͷ����*/
    pstRewindInfo->u32NewLastFrame = pstRepairCtrl->u32IdxPos - 1;
    pstRewindInfo->u32NewEndFrame = pstRewindInfo->u32NewLastFrame;
    pstRewindInfo->u32NewStartFrame= 0;
    if (HI_SUCCESS != PVR_Index_LinearizationFlushIndexHeaderInfo(pstRepairCtrl, pstRewindInfo))
    {
        HI_ERR_PVR("flush new index file headerInfo failed!\n");
        s32Ret = HI_FAILURE;
    }

    if (HI_SUCCESS != s32Ret)
    {
        s32ChangeSuccess = HI_ERR_PVR_INDEX_DATA_ERR;
    }
    PVR_Intf_DoEventCallback(pstLinearChn->u32ChnId, HI_UNF_PVR_EVENT_RECFILE_LINEARIZATION_COMPLETE, s32ChangeSuccess);

    /*�ͷ�ʹ����Դ*/
    (HI_VOID)PVRRecFileLinearizationResetAttr(pstLinearChn);

    return HI_NULL;
}

static HI_VOID *PVRRecProcessRewindThread(HI_VOID *pArgs)
{
    HI_S32 s32Ret= HI_SUCCESS;
    PVR_REC_CHN_S* pRecChn = (PVR_REC_CHN_S *)pArgs;

    s32Ret = PVR_Index_ProcessRewindChg(pRecChn->IndexHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("process rewind index failed! ret = %x\n", s32Ret);
        PVR_Intf_DoEventCallback(pRecChn->u32ChnID, HI_UNF_PVR_EVENT_REC_REWIND_TO_LINEAR_COMPLETE, HI_ERR_PVR_INDEX_DATA_ERR);
    }
    else
    {
        HI_INFO_PVR("process rewind index success!");
        PVR_Intf_DoEventCallback(pRecChn->u32ChnID, HI_UNF_PVR_EVENT_REC_REWIND_TO_LINEAR_COMPLETE, HI_SUCCESS);
    }

    PVR_Intf_AddEventHistory(&pRecChn->stEventHistory, HI_UNF_PVR_EVENT_REC_REWIND_TO_LINEAR_COMPLETE);

    return (HI_VOID *)HI_NULL;
}

static HI_S32 PVRRecCircurarToLinearCheckCfg(PVR_REC_CHN_S* pRecChn)
{
    if ((pRecChn->enState != HI_UNF_PVR_REC_STATE_RUNNING) && (pRecChn->enState != HI_UNF_PVR_REC_STATE_PAUSE))
    {
        HI_ERR_PVR("The current state(%u) doesn't support changing rewind properties!\n", pRecChn->enState);
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    if (HI_FALSE == pRecChn->stUserCfg.bRewind)
    {
        HI_ERR_PVR("Current record is non-rewind,don't need to change!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }

#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
    {
        HI_ERR_PVR("TEE record don't support change rewind properties!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }
#endif

    if (HI_TRUE == PVR_INDEX_IS_CHANGE_REWIND(pRecChn->IndexHandle))
    {
        HI_ERR_PVR("Rewind can be changed only once!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

static HI_S32 PVRRecSetRecCircurarToLinear(PVR_REC_CHN_S* pRecChn)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U64 u64LastRecWritePos = 0;

    s32Ret = PVRRecCircurarToLinearCheckCfg(pRecChn);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("user config is invalid! ret = %x\n", s32Ret);
        return s32Ret;
    }

    /*����ת�ǻ���ʱ��δ�������ƣ�ֱ���޸�bRewind���Ժ󷵻�*/
    if (0 == pRecChn->IndexHandle->stCycMgr.u32CycTimes)
    {
        pRecChn->stUserCfg.bRewind = HI_FALSE;
        pRecChn->stUserCfg.u64MaxFileSize = 0;
        pRecChn->stUserCfg.u64MaxTimeInMs = 0;
        (HI_VOID)PVR_Index_ChangeReWindAttrWhenNotRewind(pRecChn->IndexHandle);
    }
    else
    {
        /* save all data to file*/
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
        PVRRecFlushAllToFile(pRecChn);
#else
        s32Ret = PVR_Index_FlushIdxWriteCache(pRecChn->IndexHandle);
        if (HI_SUCCESS != s32Ret)
        {//�˴�ֱ�ӷ�������Ϊ���ܻᷢ����overfix���л�ʧ��
            HI_ERR_PVR("flush index to file failed! ret = %x\n",s32Ret);
            return s32Ret;
        }
#endif

        pRecChn->stUserCfg.bRewind = HI_FALSE;
        pRecChn->stUserCfg.u64MaxFileSize = 0;
        pRecChn->stUserCfg.u64MaxTimeInMs = 0;

        /*�����Ѿ����������˵����*/
        /*|--E--S--L|*  or  *|-S--E--L|*/
        u64LastRecWritePos = pRecChn->u64CurWritePos;
        pRecChn->u64CurWritePos = PVR_INDEX_MAX_FILE_SIZE(pRecChn->IndexHandle);

        s32Ret = PVR_Index_UpdateTheLastFileInfoWhenRewindChg(pRecChn->IndexHandle, u64LastRecWritePos);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("update lastFileInfo failed when changing rewind! ret = %x\n",s32Ret);
            return s32Ret;
        }
    }

    if (0 != pthread_create(&pRecChn->ChangeRewindThread, HI_NULL, PVRRecProcessRewindThread, (HI_VOID *)pRecChn))
    {
        HI_ERR_PVR("create thread to proccess rewind index failed!\n");
        return HI_FAILURE;
    }

    return s32Ret;
}

#ifdef HI_TEE_PVR_SUPPORT
static HI_S32 PVRRecTeeInit(PVR_REC_CHN_S* pChnAttr, HI_UNF_PVR_REC_ATTR_S* pstRecAttrLocal)
{
    if (HI_UNF_PVR_SECURE_MODE_TEE != pstRecAttrLocal->enSecureMode)
    {
        return HI_SUCCESS;
    }
    memset(&pChnAttr->stReeBuff, 0x00, sizeof(pChnAttr->stReeBuff));
    if (HI_SUCCESS != HI_PVR_TeeMallocReeBuffer(&pChnAttr->stReeBuff, pstRecAttrLocal->u32DavBufSize, HI_TRUE, "pvr_ree_rec_data"))
    {
        HI_ERR_PVR("malloc REE buffer failed!\n");
        return HI_ERR_PVR_NO_MEM;
    }
#ifdef PVR_PROC_SUPPORT
    memset(&pChnAttr->stTeeState, 0x00, sizeof(pChnAttr->stTeeState));
    if (HI_SUCCESS != HI_PVR_TeeMallocReeBuffer(&pChnAttr->stTeeState, sizeof(PVR_REC_SEC_OS_STATE_S), HI_TRUE, "pvr_ree_rec_proc"))
    {
        HI_ERR_PVR("malloc REE buffer failed!\n");
        HI_PVR_TeeFreeReeBuffer(&pChnAttr->stReeBuff, HI_TRUE);
        return HI_ERR_PVR_NO_MEM;
    }
#endif
    pChnAttr->u32TeeChnId = -1;
    if (HI_SUCCESS != HI_PVR_TeeOpenTeeChn(&pChnAttr->u32TeeChnId, pstRecAttrLocal->u32DavBufSize))
    {
        HI_ERR_PVR("open tee channel failed!\n");
        HI_PVR_TeeFreeReeBuffer(&pChnAttr->stReeBuff, HI_TRUE);
#ifdef PVR_PROC_SUPPORT
        HI_PVR_TeeFreeReeBuffer(&pChnAttr->stTeeState, HI_TRUE);
#endif
        return HI_ERR_PVR_NO_MEM;
    }
    return HI_SUCCESS;
}
static HI_S32 PVRRecTeeDeInit(PVR_REC_CHN_S* pRecChn)
{
    if (HI_UNF_PVR_SECURE_MODE_TEE != pRecChn->stUserCfg.enSecureMode)
    {
        return HI_SUCCESS;
    }
    (HI_VOID)HI_PVR_TeeFreeReeBuffer(&pRecChn->stReeBuff, HI_TRUE);
#ifdef PVR_PROC_SUPPORT
    (HI_VOID)HI_PVR_TeeFreeReeBuffer(&pRecChn->stTeeState, HI_TRUE);
#endif
    (HI_VOID)HI_PVR_TeeCloseTeeChn(pRecChn->u32TeeChnId);
    return HI_SUCCESS;
}
#endif

#ifdef PVR_PID_CHANGE_SUPPORT
static HI_VOID PVRRecCheckAndWaitIdle(PVR_REC_CHN_S* pstRecChn, HI_U32 u32TimeOutMs)
{
    HI_U32 u32WaitCnt = 0;

    u32WaitCnt = u32TimeOutMs/10;

    while (0 != u32WaitCnt)
    {
        if (HI_UNF_PVR_REC_STATE_PID_CHANGE == pstRecChn->enState)
        {
            break;
        }
        PVR_USLEEP(10);
        u32WaitCnt--;
    }
    return;
}

static HI_S32 PVRRecCheckPidChange(PVR_REC_CHN_S *pstChnAttr, HI_UNF_PVR_PID_CHANGE_INFO_S *pstPidInfo)
{
    HI_U32 i = 0;

    /*Index PID ��Ҫ��PidList��*/
    for (i = 0; i < pstPidInfo->u32PidNum; i++)
    {
        if (pstPidInfo->u32IndexPid == pstPidInfo->u32PidList[i])
        {
            break;
        }
    }
    if (i == pstPidInfo->u32PidNum)
    {
        HI_ERR_PVR("the Index PID not in the pidList! \n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*��֧��TEE ¼���±��PID*/
    if (HI_UNF_PVR_SECURE_MODE_TEE == pstChnAttr->stUserCfg.enSecureMode)
    {
        HI_ERR_PVR("Tee record do not support pid change!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*���PID ʱӦ��֤���ǰ������������ͬ*/
    if (pstPidInfo->enIndexType != pstChnAttr->stUserCfg.enIndexType)
    {
        HI_ERR_PVR("index types are different(old/new:%u/%u), don't support!\n", pstChnAttr->stUserCfg.enIndexType, pstPidInfo->enIndexType);
        return  HI_ERR_PVR_INVALID_PARA;
    }

    /*���PIDʱֻ֧��¼��״̬ΪRUNNING ��PAUSE ״̬*/
    if ((HI_UNF_PVR_REC_STATE_RUNNING != pstChnAttr->enState) && (HI_UNF_PVR_REC_STATE_PAUSE != pstChnAttr->enState))
    {
        HI_ERR_PVR("only running and pause state support pid change! current is:%u\n", pstChnAttr->enState);
        return HI_ERR_PVR_REC_INVALID_STATE;
    }

    /*ֻ֧����������ΪTS ��*/
    if (HI_UNF_PVR_STREAM_TYPE_TS != pstChnAttr->stUserCfg.enStreamType)
    {
        HI_ERR_PVR("only ts record support pid changed, current stream type is: %u)\n", pstChnAttr->stUserCfg.enStreamType);
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*���ֻ֧�ֱ��32��PID*/
    if (PVR_MAX_RECORD_PID_CHANGE_TIMES <= pstChnAttr->IndexHandle->u32CurRecIdx + 1)
    {
        HI_ERR_PVR("only support %d times pid changes, current has %d times!\n", PVR_MAX_RECORD_PID_CHANGE_TIMES, pstChnAttr->IndexHandle->u32CurRecIdx + 1);
        return HI_ERR_PVR_NOT_SUPPORT;
    }
    return HI_SUCCESS;
}

static HI_S32 PVRRecDestroyDemuxRecChn(HI_HANDLE hDemuxHandle)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_UNF_DMX_StopRecChn(hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Stop demux channel failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_DelAllRecPid(hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("delete recorded pid failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_DestroyRecChn(hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("destroy demux channel failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 PVRRecCreateAndCfgNewDemuxChn(PVR_REC_CHN_S* pstChnAttr, HI_UNF_PVR_PID_CHANGE_INFO_S *pstPidInfo)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i = 0;
    HI_HANDLE hDemuxHandle = HI_INVALID_HANDLE;
    HI_HANDLE hPidChannel = HI_INVALID_HANDLE;
    HI_UNF_DMX_REC_ATTR_S stRecAttr;

    memset(&stRecAttr, 0x00, sizeof(stRecAttr));
    PVRRecCreateChnSetDemuxAttr(&stRecAttr, pstChnAttr);

    stRecAttr.u32IndexSrcPid = pstPidInfo->u32IndexPid;
    stRecAttr.enVCodecType = pstPidInfo->enVidType;

    s32Ret = HI_UNF_DMX_CreateRecChn(&stRecAttr, &hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Create demux record channel failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }

    for (i = 0; i < pstPidInfo->u32PidNum; i++)
    {
        s32Ret = HI_UNF_DMX_AddRecPid(hDemuxHandle, pstPidInfo->u32PidList[i], &hPidChannel);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("add pid(0x%x) to record channel failed!ret = 0x%08x\n", pstPidInfo->u32PidList[i], s32Ret);
            goto ERR_EXIT;
        }
    }

    s32Ret = HI_UNF_DMX_StartRecChn(hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("start record channel failed!ret = 0x%08x\n", s32Ret);
        goto ERR_EXIT;
    }

    pstChnAttr->DemuxRecHandle = hDemuxHandle;

    return HI_SUCCESS;

ERR_EXIT:
    (HI_VOID)HI_UNF_DMX_DelAllRecPid(hDemuxHandle);
    (HI_VOID)HI_UNF_DMX_DestroyRecChn(hDemuxHandle);

    return s32Ret;
}
#endif

PVR_REC_CHN_S* PVRRecGetChnAttrByName(const HI_CHAR* pFileName)
{
    HI_U32 i = 0;

    if (HI_NULL == pFileName)
    {
        HI_ERR_PVR("File name point is NULL.\n");
        return HI_NULL;
    }

    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        if  (!strncmp(g_stPvrRecChns[i].stUserCfg.szFileName, pFileName, strlen(pFileName)) )
        {
            if ((g_stPvrRecChns[i].enState == HI_UNF_PVR_REC_STATE_RUNNING) ||
                (g_stPvrRecChns[i].enState == HI_UNF_PVR_REC_STATE_PAUSE))
            {
                return &g_stPvrRecChns[i];
            }
            else
            {
                break;
            }
        }
    }

    return HI_NULL;
}

/* return TRUE just only start record*/
HI_BOOL PVRRecCheckFileRecording(const HI_CHAR* pFileName)
{
    HI_U32 i;

    if (HI_NULL == pFileName)
    {
        HI_ERR_PVR("Input pointer parameter is NULL!\n");
        return HI_FALSE;
    }

    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        //if (g_stPvrRecChns[i].bSavingData)
        {
            if (!strncmp((const char*)g_stPvrRecChns[i].stUserCfg.szFileName, (const char*)pFileName, strlen(pFileName)))
            {
                if ((g_stPvrRecChns[i].enState == HI_UNF_PVR_REC_STATE_RUNNING) ||
                    (g_stPvrRecChns[i].enState == HI_UNF_PVR_REC_STATE_PAUSE))
                {
                    return HI_TRUE;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return HI_FALSE;
}

/*****************************************************************************
 Prototype       : PVRRecCheckChnRecording
 Description     : to check if record channel is recording
 Input           : u32ChnID  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/30
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_BOOL PVRRecCheckChnRecording(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S*  pRecChn = HI_NULL;

    if ((u32ChnID < PVR_REC_START_NUM) || (u32ChnID >= PVR_REC_MAX_CHN_NUM + PVR_REC_START_NUM))
    {
        return HI_FALSE;
    }

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);

    if (HI_UNF_PVR_REC_STATE_RUNNING == pRecChn->enState)
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

HI_BOOL PVRRecCheckInitStat(HI_VOID)
{
    return g_stRecInit.bInit;
}


/*****************************************************************************
 Prototype       : PVRRecMarkPausePos
 Description     : mark a flag for timeshift, and save the current record position
                        if start timeshift, playing from this position
 Input           : u32ChnID
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 PVRRecMarkPausePos(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S*  pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pRecChn->enState);

    return PVR_Index_MarkPausePos(pRecChn->IndexHandle);
}

/*****************************************************************************
 Prototype       : HI_PVR_RecInit
 Description     : init record module
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecInit(HI_VOID)
{
    HI_U32 i;
    HI_U32 j;
    HI_S32 ret;
#ifdef PVR_PROC_SUPPORT
    HI_U32 u32CurPid = getpid();
    static HI_CHAR pProcDirName[32] = {0};
#endif

    if (HI_TRUE == g_stRecInit.bInit)
    {
        HI_WARN_PVR("Record Module has been Initialized!\n");
        return HI_SUCCESS;
    }

    /* initialize all the index */
    PVR_Index_Init();

    ret = PVRRecDevInit();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = PVRIntfInitEvent();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret= PVRRecFileLinearizationInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PVR("linearization init failed!\n");
        PVRIntfDeInitEvent();
        return ret;
    }

    /* set all record channel as INVALID status                            */
    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        PVR_MUTEX_INIT(&(g_stPvrRecChns[i].stMutex), ret);
        if (HI_SUCCESS != ret)
        {
            PVRIntfDeInitEvent();
            (HI_VOID)PVRRecFileLinearizationDeInit();
            /*Add destroy mutex while failed to init*/
            for (j = 0; j < i; j++)
            {
                (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[j].stMutex));
            }
            HI_ERR_PVR("init mutex lock for PVR rec chn%d failed \n", i);
            return HI_FAILURE;
        }
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
        PVR_MUTEX_INIT(&(g_stPvrRecChns[i].stTsCacheMutex), ret);
        if (HI_SUCCESS != ret)
        {
            PVRIntfDeInitEvent();
            (HI_VOID)PVRRecFileLinearizationDeInit();
            for (j = 0; j < i; j++)
            {
                (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[j].stMutex));
                (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[j].stTsCacheMutex));
            }
            (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[i].stMutex));
            HI_ERR_PVR("init stTsCacheMutex lock for PVR rec chn%d failed \n", i);
            return HI_FAILURE;
        }
#endif
        PVR_LOCK(&(g_stPvrRecChns[i].stMutex));
        g_stPvrRecChns[i].enState  = HI_UNF_PVR_REC_STATE_INVALID;
        g_stPvrRecChns[i].u32ChnID = i + PVR_REC_START_NUM;
        g_stPvrRecChns[i].hCipher = 0;
        g_stPvrRecChns[i].writeCallBack = HI_NULL;
        g_stPvrRecChns[i].stRecCallback.pfnCallback = HI_NULL;
        g_stPvrRecChns[i].stRecCallback.pUserData = HI_NULL;
        g_stPvrRecChns[i].stRecPidChangeCB.pfnPidChangeCB = HI_NULL;
        g_stPvrRecChns[i].stRecPidChangeCB.pArgs= HI_NULL;
        g_stPvrRecChns[i].ChangeRewindThread = 0;
#ifdef PVR_APPEND_MODE_SUPPORT
        memset(&g_stPvrRecChns[i].stLastRecInfo, 0x00, sizeof(g_stPvrRecChns[i].stLastRecInfo));
#endif
#ifdef PVR_PID_CHANGE_SUPPORT
        g_stPvrRecChns[i].bChangingPid = HI_FALSE;
#endif
        PVR_UNLOCK(&(g_stPvrRecChns[i].stMutex));
    }

#ifdef PVR_PROC_SUPPORT
    memset(pProcDirName, 0, sizeof(pProcDirName));
    if (!PVRPlayCheckInitStat())
    {
        ret = HI_MODULE_Register(HI_ID_PVR, PVR_USR_PROC_DIR);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("HI_MODULE_Register(\"%s\") return %d\n", PVR_USR_PROC_DIR, ret);
        }

        /* Add proc dir */
        snprintf(pProcDirName, sizeof(pProcDirName) - 1, "%s_%d", PVR_USR_PROC_DIR, u32CurPid);
        ret = HI_PROC_AddDir(pProcDirName);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("HI_PROC_AddDir(\"%s\") return %d\n", PVR_USR_PROC_DIR, ret);
        }
    }

    if (0 == strlen(pProcDirName))
    {
        snprintf(pProcDirName, sizeof(pProcDirName) - 1, "%s_%d", PVR_USR_PROC_DIR, u32CurPid);
    }
    /* Will be added at /proc/hisi/${DIRNAME} directory */
    g_stPvrRecProcEntry.pszDirectory = pProcDirName;
    g_stPvrRecProcEntry.pszEntryName = PVR_USR_PROC_REC_ENTRY_NAME;
    g_stPvrRecProcEntry.pfnShowProc = PVRRecShowProc;
    g_stPvrRecProcEntry.pfnCmdProc = NULL;
    g_stPvrRecProcEntry.pPrivData = g_stPvrRecChns;
    ret = HI_PROC_AddEntry(HI_ID_PVR, &g_stPvrRecProcEntry);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PVR("HI_PROC_AddEntry(\"%s\") return %d\n", PVR_USR_PROC_REC_ENTRY_NAME, ret);
    }
#endif

    g_stRecInit.bInit = HI_TRUE;

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : HI_PVR_RecDeInit
 Description     : deinit record module
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecDeInit(HI_VOID)
{
    HI_U32 i;

    if (HI_FALSE == g_stRecInit.bInit)
    {
        HI_WARN_PVR("Record Module is not Initialized!\n");
        return HI_SUCCESS;
    }
    else
    {
        /* set all record channel as INVALID status                            */
        for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
        {
            if (g_stPvrRecChns[i].enState != HI_UNF_PVR_REC_STATE_INVALID)
            {
                HI_ERR_PVR("rec chn%d is in use, can NOT deInit REC!\n", i);
                return HI_ERR_PVR_BUSY;
            }

            (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[i].stMutex));
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
            (HI_VOID)pthread_mutex_destroy(&(g_stPvrRecChns[i].stTsCacheMutex));
#endif
        }

        if (HI_SUCCESS != PVRRecFileLinearizationDeInit())
        {
            HI_ERR_PVR("inearization deinit failed!\n");
            return HI_ERR_PVR_BUSY;
        }

#ifdef PVR_PROC_SUPPORT
        (HI_VOID)HI_PROC_RemoveEntry(HI_ID_PVR, &g_stPvrRecProcEntry);
        if (!PVRPlayCheckInitStat())
        {
            HI_PROC_RemoveDir(g_stPvrRecProcEntry.pszDirectory);
            HI_MODULE_UnRegister(HI_ID_PVR);
        }
#endif

        PVRIntfDeInitEvent();
        g_stRecInit.bInit = HI_FALSE;
        return HI_SUCCESS;
    }
}

/*****************************************************************************
 Prototype       : HI_PVR_RecCreateChn
 Description     : apply a new reocrd channel
 Input           : pstRecAttr  **the attr user config
 Output          : pu32ChnID   **the chn id we get
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecCreateChn(HI_U32* pu32ChnID, const HI_UNF_PVR_REC_ATTR_S* pstRecAttr)
{
    HI_U32 u32RecIdInteral, i;
    HI_S32 ret;
    HI_U64 u64FileSizeReal;
    HI_UNF_PVR_REC_ATTR_S stRecAttrLocal;
    HI_UNF_DMX_REC_ATTR_S stRecAttr;
    PVR_REC_CHN_S* pChnAttr = HI_NULL;
#if defined(PVR_APPEND_MODE_SUPPORT) && defined(PVR_PID_CHANGE_SUPPORT)
    PVR_INDEX_PID_INFO_S *pstLastRecPidInfo = HI_NULL;
#endif
    HI_U32 u32TsPKSize;

    PVR_CHECK_POINTER(pu32ChnID);
    PVR_CHECK_POINTER(pstRecAttr);

    memset(&stRecAttr, 0x00, sizeof(stRecAttr));
    memset(&stRecAttrLocal, 0x00, sizeof(stRecAttrLocal));
    CHECK_REC_INIT(&g_stRecInit);

    u32TsPKSize = PVR_GET_TSPACKET_SIZE_BY_TYPE(pstRecAttr->enTsPacketType);
    memcpy(&stRecAttrLocal, pstRecAttr, sizeof(HI_UNF_PVR_REC_ATTR_S));

    ret = PVRRecCheckUserCfg(&stRecAttrLocal);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    u64FileSizeReal = (stRecAttrLocal.u64MaxFileSize / PVR_FIFO_WRITE_BLOCK_SIZE(u32TsPKSize)) * PVR_FIFO_WRITE_BLOCK_SIZE(u32TsPKSize);
    stRecAttrLocal.u64MaxFileSize = u64FileSizeReal;

    pChnAttr = PVRRecFindFreeChn();
    if (NULL == pChnAttr)
    {
        HI_ERR_PVR("Not enough channel to be used!\n");
        return HI_ERR_PVR_NO_CHN_LEFT;
    }

    PVR_LOCK(&(pChnAttr->stMutex));
    u32RecIdInteral = pChnAttr->u32ChnID - PVR_REC_START_NUM;
#ifdef PVR_PID_CHANGE_SUPPORT
    pChnAttr->bChangingPid = HI_FALSE;
#endif
#ifdef HI_TEE_PVR_SUPPORT
    ret = PVRRecTeeInit(pChnAttr, &stRecAttrLocal);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PVR("initialize the tee failed!\n");
        goto INIT_EXIT;
    }
#endif

#ifdef PVR_APPEND_MODE_SUPPORT
    /*CNcomment: ����Ƿ���¼*/
    memset(&pChnAttr->stLastRecInfo, 0x00, sizeof(pChnAttr->stLastRecInfo));
    if (HI_TRUE == stRecAttrLocal.bAppendRec)
    {
        ret = PVR_Index_RecAppendCheck(&stRecAttrLocal, &pChnAttr->stLastRecInfo);
        if (HI_FAILURE == ret)
        {
            HI_ERR_PVR("Append record failed! \n");
            memset(&pChnAttr->stLastRecInfo, 0x00, sizeof(pChnAttr->stLastRecInfo));
            goto TEE_EXIT;
        }

        if (pChnAttr->stLastRecInfo.bAppend != HI_TRUE)
        {
            HI_INFO_PVR("not append record, first record starting! \n");
            HI_PVR_RemoveFile(stRecAttrLocal.szFileName);
        }
    }
#endif

    /* create an data file and open it */
    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS == stRecAttrLocal.enStreamType)
    {
        pChnAttr->dataFile = PVR_OPEN64(stRecAttrLocal.szFileName, PVR_FOPEN_MODE_DATA_WRITE_ALL_TS);
    }
    else
    {
        pChnAttr->dataFile = PVR_OPEN64(stRecAttrLocal.szFileName, PVR_FOPEN_MODE_DATA_WRITE);
    }
    if (PVR_FILE_INVALID_FILE == pChnAttr->dataFile)
    {
        HI_ERR_PVR("Create stream file error!\n");
        PVR_REMOVE_FILE64(stRecAttrLocal.szFileName);
        ret = HI_ERR_PVR_FILE_CANT_OPEN;
        goto TEE_EXIT;
    }

    PVR_SET_MAXFILE_SIZE(pChnAttr->dataFile, u64FileSizeReal);

    /* save chn user-config attr */
    memcpy(&pChnAttr->stUserCfg, &stRecAttrLocal, sizeof(HI_UNF_PVR_REC_ATTR_S));
    pChnAttr->stUserCfg.u64MaxFileSize = u64FileSizeReal;
    if (HI_UNF_PVR_STREAM_TYPE_ALL_TS != stRecAttrLocal.enStreamType)
    {
        /* get a new index handle  */
        pChnAttr->IndexHandle = PVR_Index_CreatRec(pChnAttr->u32ChnID, &stRecAttrLocal);
        if (HI_NULL_PTR == pChnAttr->IndexHandle)
        {
            ret = HI_ERR_PVR_INDEX_CANT_MKIDX;
            goto TSOPEN_EXIT;
        }

#if defined(PVR_APPEND_MODE_SUPPORT) || defined(PVR_PID_CHANGE_SUPPORT)
        if (HI_TRUE == pChnAttr->stLastRecInfo.bAppend)
        {
            ret = PVR_Index_ReadRewindChgInfoFromFile(pChnAttr->IndexHandle);
            if (HI_SUCCESS != ret)
            {
                HI_ERR_PVR("PVR get rewind info failed !\n");
                goto INDEX_EXIT;
            }
        }
#endif

        ret = PVRRecPrepareCipher(pChnAttr);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Pvr recorde prepare cipher error!\n");
            goto INDEX_EXIT;
        }
    }
    else
    {
        pChnAttr->IndexHandle = HI_NULL;
    }

//�����ϴ���¼����Ϣ�����µ�pstPidCtrl�У����ж��Ƿ�������¼
#if defined(PVR_APPEND_MODE_SUPPORT) && defined(PVR_PID_CHANGE_SUPPORT)
    if ((HI_NULL != pChnAttr->IndexHandle) && (HI_TRUE == pChnAttr->stLastRecInfo.bAppend))
    {
        if (2 > pChnAttr->IndexHandle->u32EntryVersion)
        {
            HI_ERR_PVR("change PID not support for old Index Version!\n");
            ret = HI_FAILURE;
            goto CIPHER_EXIT;
        }

        ret = PVR_Index_ParseAllPidList(pChnAttr->IndexHandle, stRecAttrLocal.szFileName);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("get pid list failed, not able to append record!\n");
            goto CIPHER_EXIT;
        }

        ret = PVR_Index_RecReviseThePidCtrlInfoWhenAppendRecord(pChnAttr->IndexHandle, &pChnAttr->stLastRecInfo);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("revise PidCtrl failed!\n");
            goto CIPHER_EXIT;
        }

        pstLastRecPidInfo = &(pChnAttr->IndexHandle->pstPidCtrl->stPidInfo[pChnAttr->IndexHandle->pstPidCtrl->u32UsedNum - 1]);
        if ((pstLastRecPidInfo->u32IndexType != stRecAttrLocal.enIndexType) ||
            (pstLastRecPidInfo->u32VideoType != stRecAttrLocal.enIndexVidType) ||
                (pstLastRecPidInfo->u32IndexPid != stRecAttrLocal.u32IndexPid))
        {
            HI_ERR_PVR("append record attribute not satisfied with Last PidInfo condition, not able to append record! \n");
            HI_ERR_PVR("(IndexType, VideoType, IndexPid): config(%d, %d, %d)   Last(%d, %d, %d)\n",
                            stRecAttrLocal.enIndexType, stRecAttrLocal.enIndexVidType, stRecAttrLocal.u32IndexPid,
                            pstLastRecPidInfo->u32IndexType, pstLastRecPidInfo->u32VideoType, pstLastRecPidInfo->u32IndexPid);
            ret = HI_FAILURE;
            goto CIPHER_EXIT;
        }
    }
#endif

    PVRRecCreateChnSetDemuxAttr(&stRecAttr, pChnAttr);
    ret = HI_UNF_DMX_CreateRecChn(&stRecAttr, &pChnAttr->DemuxRecHandle);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx create rec chn failed! ret 0x%x\n", ret);
        goto CIPHER_EXIT;
    }
    for (i = 0; i < PVR_REC_EVENT_HISTORY_NUM; i++)
    {
        pChnAttr->stEventHistory.enEventHistory[i] = HI_UNF_PVR_EVENT_BUTT;
    }
    pChnAttr->stEventHistory.u32Write = 0;

    HI_INFO_PVR("file size adjust to :%lld.\n", u64FileSizeReal);

    /* here we get record channel successfully */
    *pu32ChnID = pChnAttr->u32ChnID;
    HI_INFO_PVR("record creat ok\n");
    PVR_UNLOCK(&(pChnAttr->stMutex));

    return HI_SUCCESS;

CIPHER_EXIT:
    (HI_VOID)PVRRecReleaseCipher(pChnAttr);
INDEX_EXIT:
    (HI_VOID)PVR_Index_Destroy(pChnAttr->IndexHandle, PVR_INDEX_REC);
TSOPEN_EXIT:
    PVR_CLOSE64(pChnAttr->dataFile);
#ifdef PVR_APPEND_MODE_SUPPORT
    if (HI_TRUE != pChnAttr->stLastRecInfo.bAppend)
#endif
    {
        PVR_REMOVE_FILE64(stRecAttrLocal.szFileName);
    }
TEE_EXIT:
#ifdef HI_TEE_PVR_SUPPORT
    (HI_VOID)PVRRecTeeDeInit(pChnAttr);
INIT_EXIT:
#endif
    (HI_VOID)ioctl(g_s32PvrFd, CMD_PVR_DESTROY_REC_CHN, &u32RecIdInteral);
    pChnAttr->enState = HI_UNF_PVR_REC_STATE_INVALID;
    PVR_UNLOCK(&(pChnAttr->stMutex));
    HI_ERR_PVR("Create recording channel failed, ret = %x\n", ret);
    return ret;

}

/*****************************************************************************
 Prototype       : HI_PVR_RecDestroyChn
 Description     : free record channel
 Input           : u32ChnID  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecDestroyChn(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S* pRecChn = NULL;
    HI_U32 u32RecIdInteral;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /* to affirm record channel stopped */
    if ((HI_UNF_PVR_REC_STATE_RUNNING == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_STOPPING == pRecChn->enState))
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        HI_ERR_PVR(" can't destroy rec chn%d : chn still runing\n", u32ChnID);
        return HI_ERR_PVR_BUSY;
    }

    /* we don't care about whether it is timeshifting! */
#ifdef HI_TEE_PVR_SUPPORT
    if (HI_UNF_PVR_SECURE_MODE_TEE == pRecChn->stUserCfg.enSecureMode)
    {
        (HI_VOID)PVRRecTeeDeInit(pRecChn);
    }
#endif

    (HI_VOID)HI_UNF_DMX_DestroyRecChn(pRecChn->DemuxRecHandle);

    /* close index handle */
    if (HI_NULL != pRecChn->IndexHandle)
    {
        (HI_VOID)PVR_Index_Destroy(pRecChn->IndexHandle, PVR_INDEX_REC);
        pRecChn->IndexHandle = HI_NULL;
    }
    (HI_VOID)PVRRecReleaseCipher(pRecChn);
    (HI_VOID)PVR_FSYNC64(pRecChn->dataFile);

    /* close data file */
    (HI_VOID)PVR_CLOSE64(pRecChn->dataFile);

#ifdef PVR_APPEND_MODE_SUPPORT
    memset(&pRecChn->stLastRecInfo, 0x00, sizeof(pRecChn->stLastRecInfo));
#endif

    /* set channel state to invalid */
    pRecChn->enState = HI_UNF_PVR_REC_STATE_INVALID;
    u32RecIdInteral = u32ChnID - PVR_REC_START_NUM;
#ifdef PVR_PID_CHANGE_SUPPORT
    pRecChn->bChangingPid = HI_FALSE;
#endif
    if (HI_SUCCESS != ioctl(g_s32PvrFd, CMD_PVR_DESTROY_REC_CHN, &u32RecIdInteral))
    {
        HI_FATAL_PVR("pvr rec destroy channel error.\n");
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_FAILURE;
    }

    PVR_UNLOCK(&(pRecChn->stMutex));

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : HI_PVR_RecSetChn
 Description     : set record channel attributes
 Input           : u32ChnID  **
                   pRecAttr  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecSetChn(HI_U32 u32ChnID, const HI_UNF_PVR_REC_ATTR_S* pstRecAttr)
{
    PVR_REC_CHN_S* pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(pstRecAttr);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pRecChn->enState);

    /* currently, we can't set record channel dynamically. */

    return HI_ERR_PVR_NOT_SUPPORT;
}

HI_S32 HI_PVR_RecSetAttr(HI_U32 u32RecChnID, HI_UNF_PVR_REC_ATTR_ID_E enRecAttrID, HI_VOID *pPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PVR_REC_CHN_S* pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32RecChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32RecChnID);
    CHECK_REC_CHN_INIT(pRecChn->enState);

    if (HI_UNF_PVR_REC_ATTR_ID_REWIND == enRecAttrID)
    {
        PVR_LOCK(&pRecChn->stMutex);
        s32Ret = PVRRecSetRecCircurarToLinear(pRecChn);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("Dynamically change recording rewind properties failed! ret = %x\n",s32Ret);
        }

        PVR_UNLOCK(&pRecChn->stMutex);
    }
    else
    {
        HI_ERR_PVR("invalid RecAttrID(%u)!\n", enRecAttrID);
        s32Ret = HI_ERR_PVR_INVALID_PARA;
    }

    return s32Ret;
}

HI_S32 HI_PVR_RecFileStartLinearization(HI_U32 *pu32ChnId, const HI_UNF_PVR_LINEARIZATION_ATTR_S *pstRepaireAttr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bNeedRepairTsFile = HI_TRUE;
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;
    HI_UNF_PVR_LINEARIZATION_ATTR_S stLinearizationAttr;

    PVR_CHECK_POINTER(pu32ChnId);
    PVR_CHECK_POINTER(pstRepaireAttr);

    memset(&stLinearizationAttr, 0x00, sizeof(stLinearizationAttr));
    /*check init*/
    CHECK_REC_INIT(&g_stRecInit);

    /*check user config*/
    s32Ret = PVRRecFileLinearizationCheckUserCfg(pstRepaireAttr, &stLinearizationAttr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("invalid user config, ret = %x\n", s32Ret);
        return s32Ret;
    }

    /*Check the necessity of linearization*/
    s32Ret = PVR_Index_LinearizationCheckNeedToDo(stLinearizationAttr.szSrcFileName, &bNeedRepairTsFile);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("check if the current file needs to be linearized failed! Ret = %x\n", s32Ret);
        return s32Ret;
    }

    if (HI_FALSE == bNeedRepairTsFile)
    {
        HI_ERR_PVR("current file(%s) is Lineary,don't need to Linear!\n", stLinearizationAttr.szSrcFileName);
        return HI_ERR_PVR_INVALID_PARA;
    }

    /*get free channel*/
    pstLinearChn = PVRRecFileLinearizationGetFreeChn();
    if (HI_NULL == pstLinearChn)
    {
        HI_ERR_PVR("get free linerization chnnel failed!\n");
        return HI_FAILURE;
    }

    /*prepare for linearization*/
    PVR_LOCK(&pstLinearChn->stMutex);
    memcpy(&pstLinearChn->stUserCfg, &stLinearizationAttr, sizeof(HI_UNF_PVR_LINEARIZATION_ATTR_S));
    s32Ret = PVRRecFileLinearizationSetAttr(pstLinearChn);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("init LinearCtrl parameter failed! ret = %x\n", s32Ret);
        (HI_VOID)PVRRecFileLinearizationReleaseChn(pstLinearChn->u32ChnId);
        PVR_UNLOCK(&pstLinearChn->stMutex);
        return s32Ret;
    }

    s32Ret = PVR_Index_LinearizationAnalyzeIndexHeader(&pstLinearChn->stRepairCtrl, &pstLinearChn->stRewindInfo, &pstLinearChn->u32TotalNeedFixFrameNum);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("analyze source index header failed! ret = %x\n", s32Ret);
        (HI_VOID)PVRRecFileLinearizationResetAttr(pstLinearChn);
        (HI_VOID)PVRRecFileLinearizationReleaseChn(pstLinearChn->u32ChnId);
        PVR_UNLOCK(&pstLinearChn->stMutex);
        return s32Ret;
    }

    /*start linearization*/
    if (0 != pthread_create(&pstLinearChn->RepaireThread, HI_NULL, PVRRecFileLinearizationThread, (HI_VOID *)pstLinearChn))
    {
        HI_ERR_PVR("create process index and ts data thread failed!\n");
        (HI_VOID)PVRRecFileLinearizationResetAttr(pstLinearChn);
        (HI_VOID)PVRRecFileLinearizationReleaseChn(pstLinearChn->u32ChnId);
        PVR_UNLOCK(&pstLinearChn->stMutex);
        return HI_FAILURE;
    }

    PVR_UNLOCK(&pstLinearChn->stMutex);
    *pu32ChnId = pstLinearChn->u32ChnId;

    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecFileLinearizationGetStatus(HI_U32 u32ChnId, HI_UNF_PVR_LINEARIZATION_STATUS_S *pstLineariztionStatus)
{
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;

    PVR_CHECK_POINTER(pstLineariztionStatus);

    CHECK_REC_INIT(&g_stRecInit);

    pstLinearChn = PVRRecFileLinearizationGetChnById(u32ChnId);
    if (HI_NULL == pstLinearChn)
    {
        HI_ERR_PVR("Linearization channel is invalid or the current channel is not used, ChannelId: %u!\n", u32ChnId);
        return HI_FAILURE;
    }

    memset(pstLineariztionStatus, 0x00, sizeof(HI_UNF_PVR_LINEARIZATION_STATUS_S));
    PVR_LOCK(&pstLinearChn->stMutex);
    pstLineariztionStatus->u32TotalFrameNum = pstLinearChn->u32TotalNeedFixFrameNum;
    pstLineariztionStatus->u32CurrentFixFrameNum= pstLinearChn->u32FixedFrameNum;
    PVR_UNLOCK(&pstLinearChn->stMutex);

    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecFileStopLinearization(HI_U32 u32ChnId)
{
    PVR_LINEARIZATION_CHN_S *pstLinearChn = HI_NULL;

    CHECK_REC_INIT(&g_stRecInit);

    pstLinearChn = PVRRecFileLinearizationGetChnById(u32ChnId);
    if (HI_NULL == pstLinearChn)
    {
        HI_ERR_PVR("Linearization channel is invalid, ChannelID: %u!\n", u32ChnId);
        return HI_FAILURE;
    }

    if (HI_TRUE == pstLinearChn->bStopLinerization)
    {
        HI_ERR_PVR("Linearization is stopping,please wait!\n");
        return HI_FAILURE;
    }

    PVR_LOCK(&pstLinearChn->stMutex);
    pstLinearChn->bStopLinerization = HI_TRUE;
    PVR_UNLOCK(&pstLinearChn->stMutex);

    if (0 != pstLinearChn->RepaireThread)
    {
        (HI_VOID)pthread_join(pstLinearChn->RepaireThread, HI_NULL);
    }

    PVR_LOCK(&pstLinearChn->stMutex);
    if (HI_SUCCESS != PVRRecFileLinearizationReleaseChn(u32ChnId))
    {
        HI_ERR_PVR("realease linearization channel(%u) failed!\n", u32ChnId);
        PVR_UNLOCK(&pstLinearChn->stMutex);
        return HI_ERR_PVR_INVALID_CHNID;
    }
    PVR_UNLOCK(&pstLinearChn->stMutex);

    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype       : HI_PVR_RecGetChn
 Description     : get record channel attributes
 Input           : u32ChnID  **
                   pRecAttr  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecGetChn(HI_U32 u32ChnID, HI_UNF_PVR_REC_ATTR_S* pstRecAttr)
{
    PVR_REC_CHN_S* pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    PVR_CHECK_POINTER(pstRecAttr);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pRecChn->enState);

    memcpy(pstRecAttr, &(pRecChn->stUserCfg), sizeof(HI_UNF_PVR_REC_ATTR_S));

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : HI_PVR_RecStartChn
 Description     : start record channel
 Input           : u32ChnID, the record channel ID
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecStartChn(HI_U32 u32ChnID)
{
    HI_S32 ret = HI_SUCCESS;
    PVR_REC_CHN_S* pRecChn = HI_NULL;
    HI_UNF_PVR_REC_ATTR_S* pUserCfg __attribute__((unused))  = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    if ((HI_UNF_PVR_REC_STATE_RUNNING == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState))
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_ALREADY;
    }
    else
    {
        pRecChn->enState = HI_UNF_PVR_REC_STATE_RUNNING;
    }

    pUserCfg = &(pRecChn->stUserCfg);

    //PVRRecCheckExistFile(pUserCfg->szFileName);

    /* create record thread to receive index from the channel */
    ret = HI_UNF_DMX_StartRecChn(pRecChn->DemuxRecHandle);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("start demux record channel failure! ret %x\n", ret);
        pRecChn->enState = HI_UNF_PVR_REC_STATE_INIT;
        PVR_UNLOCK(&(pRecChn->stMutex));
        return ret;
    }
    else
    {
        HI_INFO_PVR("start demux OK, indexTYpe:%d!\n", pUserCfg->enIndexType);
    }

    pRecChn->u64CurFileSize  = 0;
    pRecChn->u64CurWritePos  = 0;
    pRecChn->bSavingData     = HI_TRUE;
    pRecChn->s32OverFixTimes = 0;
    pRecChn->bEventFlg       = HI_FALSE;

    (HI_VOID)HI_SYS_GetTimeStampMs(&pRecChn->u32RecStartTimeMs);

    if (HI_NULL == pRecChn->IndexHandle)
    {
        ret = pthread_create(&pRecChn->RecordFileThread, NULL, PVRRecSaveStream, pRecChn);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("call pthread_create failed!ret = 0x%08x!\n", ret);
        }
    }
    else
    {
        PVR_Index_ResetRecAttr(pRecChn->IndexHandle);
#ifdef PVR_APPEND_MODE_SUPPORT
        if (HI_TRUE == pRecChn->stLastRecInfo.bAppend)
        {
            ret = PVR_Index_RecAppendConfigure(pRecChn->IndexHandle, &pRecChn->stLastRecInfo);
            if (HI_SUCCESS != ret)
            {
                pRecChn->enState = HI_UNF_PVR_REC_STATE_STOP;
                HI_ERR_PVR("call PVR_Index_RecAppendConfigure failure!\n");
                (HI_VOID)HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
                PVR_UNLOCK(&(pRecChn->stMutex));
                return ret;
            }
            pRecChn->u64CurWritePos = pRecChn->stLastRecInfo.u64Offset;
            pRecChn->u64CurFileSize = pRecChn->stLastRecInfo.u64GlobalOffset;
    #ifdef HI_PVR_EXTRA_BUF_SUPPORT
    /*��������������ʱ(O_DIRECT)��Ҫ�ж���¼���Ƿ���Ҫ����,�����Ҫ�򽫶����ʣ�������д�����������*/
            HI_S32 residualSize = pRecChn->stLastRecInfo.u64Offset % PVR_DIO_ALIGN_SIZE;
            if (residualSize != 0)
            {
                ret = PVRReadAlignDataFromFile(pRecChn, pRecChn->stLastRecInfo.u64Offset, pRecChn->stLastRecInfo.u64GlobalOffset);
                if (HI_SUCCESS != ret)
                {
                    HI_ERR_PVR("align 512 failed! remainder: %d ,ret: %x\n",residualSize, ret);
                    pRecChn->enState = HI_UNF_PVR_REC_STATE_STOP;
                    (HI_VOID)HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
                    PVR_UNLOCK(&(pRecChn->stMutex));
                    return ret;
                }
            }
    #endif
        }
#endif

        /* failure to write user data, but still, continue to record. just only print the error info */
        if (HI_SUCCESS != PVR_Index_PrepareHeaderInfo(pRecChn->IndexHandle, pRecChn->stUserCfg.u32UsrDataInfoSize, pRecChn->stUserCfg.enIndexVidType))
        {
            HI_ERR_PVR("PVR_Index_PrepareHeaderInfo fail\n");
        }

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
        ret = pthread_create(&pRecChn->RecordCacheThread, NULL, PVRRecSaveToCache, pRecChn);
        if (ret != HI_SUCCESS)
        {
            pRecChn->enState = HI_UNF_PVR_REC_STATE_STOP;
            HI_ERR_PVR("Create save cache thread failure!\n");
            (HI_VOID)HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
            PVR_UNLOCK(&(pRecChn->stMutex));
            return HI_FAILURE;
        }

        ret = pthread_create(&pRecChn->RecordFileThread, NULL, PVRRecSaveToFile, pRecChn);
        if (ret != HI_SUCCESS)
        {
            PVR_UNLOCK(&(pRecChn->stMutex));
            HI_ERR_PVR("create record STREAM thread failure!\n");
            (HI_VOID)pthread_join(pRecChn->RecordCacheThread, NULL);
            (HI_VOID)HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
            pRecChn->enState = HI_UNF_PVR_REC_STATE_INIT;
            return HI_FAILURE;
        }
#else
        ret = pthread_create(&pRecChn->RecordFileThread, NULL, PVRRecSaveIndexAndStreamRoutine, pRecChn);

        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("create record STREAM thread failure!\n");
            (HI_VOID)HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
            pRecChn->enState = HI_UNF_PVR_REC_STATE_INIT;
            PVR_UNLOCK(&(pRecChn->stMutex));
            return HI_FAILURE;
        }
#endif
    }

    HI_INFO_PVR("channel %d start ok.\n", u32ChnID);

    PVR_UNLOCK(&(pRecChn->stMutex));
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : HI_PVR_RecStopChn
 Description     : stop the pointed record channel
 Input           : u32ChnId, channle id
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecStopChn(HI_U32 u32ChnID)
{
    HI_S32 ret = HI_SUCCESS;

    //HI_UNF_PVR_FILE_ATTR_S  fileAttr;

    PVR_REC_CHN_S*  pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /* to confirm the record channel running                           */
    if ((HI_UNF_PVR_REC_STATE_RUNNING != pRecChn->enState)
        && (HI_UNF_PVR_REC_STATE_PAUSE != pRecChn->enState))
    {
        HI_WARN_PVR("Channel has already stopped!\n");
        //PVR_UNLOCK(&(pRecChn->stMutex));
        //return HI_ERR_PVR_ALREADY;
    }

    /* state: stoping -> stop. make sure the index thread exit first   */
    //pRecChn->enState = HI_UNF_PVR_REC_STATE_STOPPING;

    //(HI_VOID)HI_PthreadJoin(pRecChn->RecordCacheThread, NULL);
    //HI_ASSERT(HI_UNF_PVR_REC_STATE_STOP == pRecChn->enState);

#if 0
    ret = PVR_Index_RecGetFileAttr(pRecChn->IndexHandle, &fileAttr);
    if (HI_SUCCESS == ret)
    {
        indexedSize = fileAttr.u64ValidSizeInByte;
    }
    else
    {
        indexedSize = pRecChn->u64CurFileSize;
    }

    HI_ERR_PVR("file size:%llu, index size:%llu\n", pRecChn->u64CurFileSize,
               fileAttr.u64ValidSizeInByte);

    while ((pRecChn->u64CurFileSize < indexedSize)
           && (waitTimes < 30)
           && pRecChn->bSavingData)    /*If returned already by error,go ahead*/ /*CNcomment:����Ѿ������˳������Բ��ü����ȴ� */
    {
        PVR_USLEEP(1000 * 40);
        waitTimes++;
        HI_ERR_PVR("wait%u, file size:%llu, index size:%llu\n", waitTimes,
                   pRecChn->u64CurFileSize,
                   fileAttr.u64ValidSizeInByte);
    }
#endif

    pRecChn->enState = HI_UNF_PVR_REC_STATE_STOP;

    if (0 != pRecChn->ChangeRewindThread)
    {
        (HI_VOID)pthread_join(pRecChn->ChangeRewindThread, HI_NULL);
        pRecChn->ChangeRewindThread = 0;
    }

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    if ((pRecChn->IndexHandle != HI_NULL) && (0 != pRecChn->RecordCacheThread))
    {
        (HI_VOID)pthread_join(pRecChn->RecordCacheThread, HI_NULL);
        pRecChn->RecordCacheThread = 0;
    }
#endif

    if (0 != pRecChn->RecordFileThread)
    {
        (HI_VOID)pthread_join(pRecChn->RecordFileThread, HI_NULL);
        pRecChn->RecordFileThread = 0;
    }
    ret = HI_UNF_DMX_StopRecChn(pRecChn->DemuxRecHandle);
    if (HI_SUCCESS != ret)
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        HI_ERR_PVR("demux stop error:%#x\n", ret);
        return ret;
    }
    else
    {
        HI_INFO_PVR("stop demux rec ok\n");
    }

    PVR_UNLOCK(&(pRecChn->stMutex));
#ifdef DUMP_DMX_DATA
    if (NULL != g_pvrfpTSReceive)
    {
        fclose(g_pvrfpTSReceive);
        g_pvrfpTSReceive = NULL;
    }
    if (NULL != g_pvrfpIdxReceive)
    {
        fclose(g_pvrfpIdxReceive);
        g_pvrfpIdxReceive = NULL;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecPauseChn(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S*  pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /* to confirm the record channel running  */
    if ((HI_UNF_PVR_REC_STATE_RUNNING != pRecChn->enState)
        && (HI_UNF_PVR_REC_STATE_PAUSE != pRecChn->enState))
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        HI_ERR_PVR("Channel not started!\n");
        return HI_ERR_PVR_REC_INVALID_STATE;
    }

    pRecChn->enState = HI_UNF_PVR_REC_STATE_PAUSE;
    PVR_UNLOCK(&(pRecChn->stMutex));
    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecResumeChn(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S*  pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /* to confirm the record channel running  */
    if ((HI_UNF_PVR_REC_STATE_RUNNING != pRecChn->enState)
        && (HI_UNF_PVR_REC_STATE_PAUSE != pRecChn->enState))
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        HI_ERR_PVR("Channel not started!\n");
        return HI_ERR_PVR_REC_INVALID_STATE;
    }

    pRecChn->enState = HI_UNF_PVR_REC_STATE_RUNNING;
    PVR_UNLOCK(&(pRecChn->stMutex));
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : HI_PVR_RecGetStatus
 Description     : get record status and recorded file size
 Input           : u32ChnID    **
                   pRecStatus  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/10
    Author       : sdk
    Modification : Created function

*****************************************************************************/
HI_S32 HI_PVR_RecGetStatus(HI_U32 u32ChnID, HI_UNF_PVR_REC_STATUS_S* pstRecStatus)
{
    HI_S32 ret = HI_SUCCESS;
    PVR_REC_CHN_S*   pRecChn = HI_NULL;
    //    HI_UNF_PVR_FILE_ATTR_S fileAttr;
    HI_UNF_DMX_RECBUF_STATUS_S stStatus;
    //HI_U32 u32DeltaTimeMs = 0;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(pstRecStatus);

    memset(&stStatus, 0x00, sizeof(stStatus));
    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    if ((HI_UNF_PVR_REC_STATE_INIT == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_INVALID == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_STOPPING == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_STOP == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_BUTT == pRecChn->enState)) /* not running, just return state */
    {
        memset(pstRecStatus, 0, sizeof(HI_UNF_PVR_REC_STATUS_S));
        pstRecStatus->enState = pRecChn->enState;
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_SUCCESS;
    }

    /* get record state                                                        */
    pstRecStatus->enState = pRecChn->enState;

    ret = HI_UNF_DMX_GetRecBufferStatus(pRecChn->DemuxRecHandle, &stStatus);
    if (HI_SUCCESS == ret)
    {
        pstRecStatus->stRecBufStatus.u32BufSize  = stStatus.u32BufSize;
        pstRecStatus->stRecBufStatus.u32UsedSize = stStatus.u32UsedSize;
    }
    else
    {
        HI_ERR_PVR("Get recording buffer status fail! set buffer status to 0. ret=%#x\n", ret);
        pstRecStatus->stRecBufStatus.u32BufSize  = 0;
        pstRecStatus->stRecBufStatus.u32UsedSize = 0;
    }

    if (HI_NULL == pRecChn->IndexHandle)
    {
        pstRecStatus->u32CurTimeInMs   = 0;
        pstRecStatus->u32CurWriteFrame = 0;
        pstRecStatus->u64CurWritePos   = pRecChn->u64CurFileSize;
        pstRecStatus->u32StartTimeInMs = 0;
        pstRecStatus->u32EndTimeInMs = 0;
        PVR_UNLOCK(&(pRecChn->stMutex));

        return HI_SUCCESS;
    }

    /* get recorded file size                                                  */

    //pstRecStatus->u64CurWritePos = pRecChn->u64CurFileSize;
#if 0
    PVR_Index_FlushIdxWriteCache(pRecChn->IndexHandle);

    ret = PVR_Index_PlayGetFileAttrByFileName(pRecChn->stUserCfg.szFileName, pRecChn->IndexHandle, &fileAttr);
    if (HI_SUCCESS == ret)
    {
#if 0
        /*attention: this condition is fo situation such as: tuner signal droped and so on,
        but ,using this condition may cause the u32CurTimeInMs and u32EndTimeInMs changes not linear,
        because when acquire demux rec tsbuf ,may be will wait until timeout ,in this time ,pRecChn->bSavingData is false
        */
        if ((HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState) ||
            (HI_UNF_PVR_REC_STATE_STOP == pRecChn->enState) ||
            (pRecChn->bSavingData  == HI_FALSE))
        {
            pstRecStatus->u32CurTimeInMs = pRecChn->IndexHandle->stCurRecFrame.u32DisplayTimeMs - fileAttr.u32StartTimeInMs;
            pstRecStatus->u32EndTimeInMs = fileAttr.u32EndTimeInMs;
        }
        else
        {
            if (0 == pRecChn->IndexHandle->stCycMgr.u32CycTimes)
            {
                u32DeltaTimeMs = (u32CurTimeMs - pRecChn->u32RecStartTimeMs) - (pRecChn->IndexHandle->stCurRecFrame.u32DisplayTimeMs - fileAttr.u32StartTimeInMs);
            }
            else
            {
                u32DeltaTimeMs = 0;
            }

            if (u32DeltaTimeMs > 1000)
            {
                pstRecStatus->u32CurTimeInMs = u32CurTimeMs - u32DeltaTimeMs - pRecChn->u32RecStartTimeMs;
            }
            else
            {
                pstRecStatus->u32CurTimeInMs = u32CurTimeMs - pRecChn->u32RecStartTimeMs;
            }

            pstRecStatus->u32EndTimeInMs = pstRecStatus->u32CurTimeInMs;
        }
#else
        pstRecStatus->u32CurTimeInMs = pRecChn->IndexHandle->stCurRecFrame.u32DisplayTimeMs;
        pstRecStatus->u32EndTimeInMs = fileAttr.u32EndTimeInMs;
#endif

        pstRecStatus->u32CurWriteFrame = fileAttr.u32FrameNum;
        pstRecStatus->u64CurWritePos   = pRecChn->u64CurWritePos;
        pstRecStatus->u32StartTimeInMs = fileAttr.u32StartTimeInMs;
    }
#else
    ret = PVR_Index_GetRecStatus(pRecChn->IndexHandle, pstRecStatus);
    if (ret == HI_SUCCESS)
    {
        pstRecStatus->u64CurWritePos = pRecChn->u64CurWritePos;
    }
#endif

    PVR_UNLOCK(&(pRecChn->stMutex));

    return ret;
}

HI_S32 HI_PVR_RecRegisterWriteCallBack(HI_U32 u32ChnID, ExtraCallBack writeCallBack)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(writeCallBack);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /*modify for DTS2014032900795, callback only supported by ts recording*/
    if (HI_UNF_PVR_STREAM_TYPE_TS == pRecChn->stUserCfg.enStreamType)
    {
        pRecChn->writeCallBack = writeCallBack;
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_SUCCESS;
    }
    else
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_NOT_SUPPORT;
    }
}

HI_S32 HI_PVR_RecRegisterRecordCallBack(HI_U32 u32ChnID, ExtendCallBack RecCallBack, HI_VOID* pUserData)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(RecCallBack);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /*record callback only supported by ts recording*/
    if (HI_UNF_PVR_STREAM_TYPE_TS == pRecChn->stUserCfg.enStreamType)
    {
        pRecChn->stRecCallback.pfnCallback = RecCallBack;
        pRecChn->stRecCallback.pUserData = pUserData;
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_SUCCESS;
    }
    else
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_NOT_SUPPORT;
    }
}

HI_S32 HI_PVR_RecRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback, HI_VOID *pArgs)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(fCallback);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    /*record callback only supported by ts recording*/
    if (HI_UNF_PVR_STREAM_TYPE_TS == pRecChn->stUserCfg.enStreamType)
    {
        pRecChn->stRecPidChangeCB.pfnPidChangeCB= fCallback;
        pRecChn->stRecPidChangeCB.pArgs= pArgs;
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_SUCCESS;
    }
    else
    {
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_NOT_SUPPORT;
    }
}


HI_S32 HI_PVR_RecUnRegisterWriteCallBack(HI_U32 u32ChnID)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);
    pRecChn->writeCallBack = HI_NULL;
    PVR_UNLOCK(&(pRecChn->stMutex));

    return HI_SUCCESS;
}


HI_S32 HI_PVR_RecUnRegisterRecordCallBack(HI_U32 u32ChnID, ExtendCallBack pRecCallback)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(pRecCallback);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);
    if (pRecCallback != pRecChn->stRecCallback.pfnCallback)
    {
        HI_ERR_PVR("The input callback hasn't been registered!\n");
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_INVALID_PARA;
    }
    pRecChn->stRecCallback.pfnCallback = HI_NULL;
    pRecChn->stRecCallback.pUserData = HI_NULL;
    PVR_UNLOCK(&(pRecChn->stMutex));

    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecUnRegisterPidChangeCallBack(HI_U32 u32ChnID, PidChangeCallBack fCallback)
{
    PVR_REC_CHN_S*   pRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);
    PVR_CHECK_POINTER(fCallback);

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);
    if (fCallback != pRecChn->stRecPidChangeCB.pfnPidChangeCB)
    {
        HI_ERR_PVR("The input callback hasn't been registered!\n");
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_INVALID_PARA;
    }
    pRecChn->stRecPidChangeCB.pfnPidChangeCB = HI_NULL;
    pRecChn->stRecPidChangeCB.pArgs= HI_NULL;
    PVR_UNLOCK(&(pRecChn->stMutex));

    return HI_SUCCESS;
}

/*
 * suggesting, the user should set/get the user data by TS file name. as extend, also used by *.idx
 */
HI_S32 HI_PVR_SetUsrDataInfoByFileName(const HI_CHAR* pFileName, HI_U8* pInfo, HI_U32 u32UsrDataLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Fd = -1;
    HI_CHAR strIdxFileName[PVR_MAX_FILENAME_LEN] = {0};

    PVR_CHECK_POINTER(pFileName);
    PVR_CHECK_POINTER(pInfo);

    if (0 == u32UsrDataLen)
    {
        return HI_SUCCESS;
    }

    PVR_Index_GetIdxFileName(strIdxFileName, (HI_CHAR*)pFileName);
    /*checking  if the file is existed is needed, because open the file with PVR_FOPEN_MODE_INDEX_BOTH*/
    if (HI_FALSE == PVR_CHECK_FILE_EXIST(strIdxFileName))
    {
        HI_ERR_PVR("file:%s not exist.\n", strIdxFileName);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    s32Fd = PVR_OPEN(strIdxFileName, PVR_FOPEN_MODE_INDEX_BOTH);
    if (s32Fd < 0)
    {
        HI_ERR_PVR("open file:%s fail:0x%x\n", strIdxFileName, s32Fd);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    s32Ret = PVR_Index_SetUsrDataInfo(s32Fd, pInfo, u32UsrDataLen);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("PVR_Index_SetUsrDataInfo fail, ret = 0x%08x\n", s32Ret);
    }

    PVR_CLOSE(s32Fd);
    return s32Ret;
}

HI_S32 HI_PVR_GetUsrDataInfoByFileName(const HI_CHAR* pFileName, HI_U8* pInfo, HI_U32 u32BufLen, HI_U32* pUsrDataLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Fd;
    HI_CHAR strIdxFileName[PVR_MAX_FILENAME_LEN] = {0};

    PVR_CHECK_POINTER(pFileName);
    PVR_CHECK_POINTER(pInfo);
    PVR_CHECK_POINTER(pUsrDataLen);

    if (0 == u32BufLen)
    {
        return HI_SUCCESS;
    }

    PVR_Index_GetIdxFileName(strIdxFileName, (HI_CHAR*)pFileName);

    s32Fd = PVR_OPEN(strIdxFileName, PVR_FOPEN_MODE_INDEX_READ);
    if (s32Fd < 0)
    {
        HI_ERR_PVR("open file:%s fail:0x%x\n", strIdxFileName, s32Fd);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    s32Ret = PVR_Index_GetUsrDataInfo(s32Fd, pInfo, u32BufLen, pUsrDataLen);
    if (HI_SUCCESS != s32Ret)
    {
        *pUsrDataLen = 0;
        HI_ERR_PVR("PVR_Index_GetUsrDataInfo fail, ret = 0x%08x\n", s32Ret);
    }

    PVR_CLOSE(s32Fd);
    return s32Ret;
}

HI_S32 HI_PVR_SetCAData(const HI_CHAR* pIdxFileName, HI_U8* pInfo, HI_U32 u32CADataLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Fd;

    PVR_CHECK_POINTER(pIdxFileName);
    PVR_CHECK_POINTER(pInfo);

    if ((0 == u32CADataLen ) || (PVR_MAX_CADATA_LEN < u32CADataLen))
    {
        HI_ERR_PVR("u32CADataLen (%d) invalid!\n", u32CADataLen);
        return HI_FAILURE;
    }

    //PVR_Index_GetIdxFileName(strIdxFileName, (HI_CHAR*)pFileName);

    s32Fd = PVR_OPEN(pIdxFileName, PVR_FOPEN_MODE_INDEX_BOTH);
    if (s32Fd < 0)
    {
        HI_ERR_PVR("open file:%s fail:0x%x\n", pIdxFileName, s32Fd);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    s32Ret = PVR_Index_SetCADataInfo(s32Fd, pInfo, u32CADataLen);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("PVR_Index_SetCADataInfo fail\n");
    }

    PVR_CLOSE(s32Fd);
    return s32Ret;
}

HI_S32 HI_PVR_GetCAData(const HI_CHAR* pIdxFileName, HI_U8* pInfo, HI_U32 u32BufLen, HI_U32* u32CADataLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Fd;

    PVR_CHECK_POINTER(pIdxFileName);
    PVR_CHECK_POINTER(pInfo);
    PVR_CHECK_POINTER(u32CADataLen);

    if (!u32BufLen)
    {
        return HI_SUCCESS;
    }

    //PVR_Index_GetIdxFileName(strIdxFileName, (HI_CHAR*)pFileName);

    s32Fd = PVR_OPEN(pIdxFileName, PVR_FOPEN_MODE_INDEX_READ);
    if (s32Fd < 0)
    {
        HI_ERR_PVR("open file:%s fail:0x%x\n", pIdxFileName, s32Fd);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    s32Ret = PVR_Index_GetCADataInfo(s32Fd, pInfo, u32BufLen, u32CADataLen);
    if (HI_SUCCESS != s32Ret)
    {
        *u32CADataLen = 0;
        HI_ERR_PVR("PVR_Index_GetCADataInfo fail\n");
    }

    PVR_CLOSE(s32Fd);
    return s32Ret;
}

HI_S32 HI_PVR_RecAddPid(HI_U32 u32ChnID, HI_U32 u32Pid)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hPidChn = HI_INVALID_HANDLE;
    PVR_REC_CHN_S* pstRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pstRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pstRecChn->enState);

#ifdef PVR_PID_CHANGE_SUPPORT
    s32Ret = PVR_INDEX_AddPidNormal(pstRecChn->IndexHandle, 1, &u32Pid);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Add pid to current failed, ret = 0x%08x\n", s32Ret);
        return s32Ret;
    }
#endif
    s32Ret = HI_UNF_DMX_AddRecPid(pstRecChn->DemuxRecHandle, u32Pid, &hPidChn);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx add rec pid %d failed! ret %x\n", u32Pid, s32Ret);
    }

    return s32Ret;
}

HI_S32 HI_PVR_RecDelPid(HI_U32 u32ChnID, HI_U32 u32Pid)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hPidChn = HI_INVALID_HANDLE;
    PVR_REC_CHN_S* pstRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pstRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pstRecChn->enState);

    s32Ret = HI_UNF_DMX_GetChannelHandle(pstRecChn->stUserCfg.u32DemuxID, u32Pid, &hPidChn);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx get pid handle failed! ret %x. demuxid %d, pid %d\n",
                   s32Ret, pstRecChn->stUserCfg.u32DemuxID, u32Pid);
        return s32Ret;
    }

    s32Ret = HI_UNF_DMX_DelRecPid(pstRecChn->DemuxRecHandle, hPidChn);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx del rec pid %d failed! ret %x\n", u32Pid, s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_PVR_RecDelAllPid(HI_U32 u32ChnID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PVR_REC_CHN_S* pstRecChn = HI_NULL;

    CHECK_REC_CHNID(u32ChnID);

    pstRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    CHECK_REC_CHN_INIT(pstRecChn->enState);

    s32Ret = HI_UNF_DMX_DelAllRecPid(pstRecChn->DemuxRecHandle);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Dmx del all rec pid failed! ret %x\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 HI_PVR_RecChangePid(HI_U32 u32ChnId, HI_UNF_PVR_PID_CHANGE_INFO_S *pstPidInfo)
{
#ifndef PVR_PID_CHANGE_SUPPORT
    return HI_ERR_PVR_NOT_SUPPORT;
#else
    HI_S32 s32Ret = HI_FAILURE;
    PVR_REC_CHN_S* pstChnAttr = HI_NULL;
    HI_UNF_PVR_REC_STATE_E enOldState = HI_UNF_PVR_REC_STATE_BUTT;
    HI_HANDLE hDemuxHandle = HI_INVALID_HANDLE;
    HI_UNF_PVR_PID_CHANGE_INFO_S stOldPidInfo;
    HI_U64 u64PreRecFileOffset = 0;
    HI_U64 u64PreRecGlobalOffset = 0;
#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    HI_S32 u32ResidualSize = 0;
#endif

    CHECK_REC_CHNID(u32ChnId);
    if (HI_NULL == pstPidInfo)
    {
        HI_ERR_PVR("null point for pidInfo \n");
        return HI_ERR_PVR_NUL_PTR;
    }

    memset(&stOldPidInfo, 0x00, sizeof(stOldPidInfo));
    pstChnAttr = PVR_GET_RECPTR_BY_CHNID(u32ChnId);
    PVR_LOCK(&(pstChnAttr->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pstChnAttr);

    /*check input and if support pid change*/
    s32Ret = PVRRecCheckPidChange(pstChnAttr, pstPidInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("invlaid input paramter!\n");
        PVR_UNLOCK(&(pstChnAttr->stMutex));
        return s32Ret;
    }
    HI_INFO_PVR("\tbegin to do the pid change!\n");

    enOldState = pstChnAttr->enState;
    hDemuxHandle = pstChnAttr->DemuxRecHandle;
    pstChnAttr->bChangingPid = HI_TRUE;

    /*check and wait the state to switch, in case calling demux destroy while calling acquire in another thread*/
    PVRRecCheckAndWaitIdle(pstChnAttr, 1000);
    if (HI_UNF_PVR_REC_STATE_PID_CHANGE != pstChnAttr->enState)
    {
        HI_ERR_PVR("wait timeout, acquire error!enOldState: %d\n", enOldState);
        pstChnAttr->DemuxRecHandle = hDemuxHandle;
        pstChnAttr->enState = enOldState;
        pstChnAttr->bChangingPid = HI_FALSE;
        PVR_UNLOCK(&(pstChnAttr->stMutex));
        return HI_ERR_PVR_REC_INVALID_STATE;
    }

    /*destroy the demux channel*/
    s32Ret = PVRRecDestroyDemuxRecChn(hDemuxHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("destroy demux record channel failed, ret = 0x%08x\n", s32Ret);
        pstChnAttr->DemuxRecHandle = hDemuxHandle;
        PVR_UNLOCK(&(pstChnAttr->stMutex));
        return s32Ret;
    }

    /*create and configure the new demux channel*/
    s32Ret = PVRRecCreateAndCfgNewDemuxChn(pstChnAttr, pstPidInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("create and start the new demux record channel failed, ret = 0x%08x\n", s32Ret);
        PVR_UNLOCK(&(pstChnAttr->stMutex));
        return s32Ret;
    }

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    PVRRecFlushAllToFile(pstChnAttr);
#endif

    //align at the offset
    s32Ret = PVR_Index_RecAlignTheLastPidInfoWhenChangePid(pstChnAttr->IndexHandle, pstChnAttr->stUserCfg.szFileName);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Align the last pidInfo offset failed!\n");
        PVR_UNLOCK(&(pstChnAttr->stMutex));
        return s32Ret;
    }

    //update the LastRecordInfo
    PVR_Index_UpdateLastRecordInfo(pstChnAttr->IndexHandle, &(pstChnAttr->stLastRecInfo), &u64PreRecFileOffset, &u64PreRecGlobalOffset);

    /*update the related record infomation*/
    //pstChnAttr->enState = enOldState;
    pstChnAttr->u64CurWritePos = u64PreRecFileOffset;

#ifdef HI_PVR_EXTRA_BUF_SUPPORT
    /*��������������ʱ(O_DIRECT)��Ҫ�жϱ����¼���Ƿ���Ҫ����,�����Ҫ�򽫶����ʣ�������д�����������*/
    u32ResidualSize = u64PreRecFileOffset % PVR_DIO_ALIGN_SIZE;
    if (u32ResidualSize != 0)
    {
        s32Ret = PVRReadAlignDataFromFile(pstChnAttr, u64PreRecFileOffset, u64PreRecGlobalOffset);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PVR("align 512 failed! remainder: %d \n",u32ResidualSize);
            PVR_UNLOCK(&(pstChnAttr->stMutex));
            return s32Ret;
        }
    }
#endif

    /*save the new pid info to files*/
    PVR_INDEX_AddPidChange(pstChnAttr->IndexHandle, pstPidInfo);
    PVR_Index_GetPrePidInfo(pstChnAttr->IndexHandle, &stOldPidInfo);
    pstChnAttr->enState = enOldState;
    PVR_UNLOCK(&(pstChnAttr->stMutex));

    if (HI_NULL != pstChnAttr->stRecPidChangeCB.pfnPidChangeCB)
    {
        pstChnAttr->stRecPidChangeCB.pfnPidChangeCB(u32ChnId, &stOldPidInfo, pstPidInfo, pstChnAttr->stRecPidChangeCB.pArgs);
    }

    return s32Ret;
#endif
}

HI_BOOL HI_PVR_AdvcaRecCheckAppend(HI_U32 u32ChnId, HI_U64 *p64LastRecGlobalOffset, HI_U32 *p32LastRecDisPlayTime)
{
    HI_BOOL bAppend = HI_FALSE;
#ifdef PVR_APPEND_MODE_SUPPORT
    PVR_REC_CHN_S* pstChnAttr = HI_NULL;

    if ((HI_NULL == p64LastRecGlobalOffset) || (HI_NULL == p32LastRecDisPlayTime))
    {
        HI_ERR_PVR("null point for p64LastRecGlobalOffset(%p) or p32LastRecDisPlayTime(%p) \n",p64LastRecGlobalOffset, p32LastRecDisPlayTime);
        return bAppend;
    }

    if( g_stRecInit.bInit == HI_FALSE)
    {
        HI_ERR_PVR("pvr rec is not init!\n");
        return bAppend;
    }
    if ((u32ChnId < PVR_REC_START_NUM) || (u32ChnId >= (PVR_REC_MAX_CHN_NUM + PVR_REC_START_NUM)))
    {
       HI_ERR_PVR("Rec chn(%u) id invalid!\n", u32ChnId);
       return bAppend;
    }

    pstChnAttr = PVR_GET_RECPTR_BY_CHNID(u32ChnId);
    if (HI_UNF_PVR_REC_STATE_INVALID ==  pstChnAttr->enState)
    {
        return bAppend;
    }

    if (HI_NULL != p64LastRecGlobalOffset)
    {
        *p64LastRecGlobalOffset = pstChnAttr->stLastRecInfo.u64GlobalOffset;
        *p32LastRecDisPlayTime = pstChnAttr->stLastRecInfo.u32LastDisplayTime;
    }
    bAppend = pstChnAttr->stLastRecInfo.bAppend;
#endif
    return bAppend;
}

HI_U64 HI_PVR_AdvcaRecCorrectFileOffset(HI_U32 u32ChnId, HI_U64 u64GlobalOffset)
{
    HI_U64 u64CorrectGlobalOffset = 0;
#ifdef PVR_APPEND_MODE_SUPPORT
    PVR_REC_CHN_S* pstChnAttr = HI_NULL;

    if( g_stRecInit.bInit == HI_FALSE)
    {
        HI_ERR_PVR("pvr rec is not init!\n");
        return u64CorrectGlobalOffset;
    }
    if ((u32ChnId < PVR_REC_START_NUM) || (u32ChnId >= (PVR_REC_MAX_CHN_NUM + PVR_REC_START_NUM)))
    {
       HI_ERR_PVR("Rec chn(%u) id invalid!\n", u32ChnId);
       return u64CorrectGlobalOffset;
    }

    pstChnAttr = PVR_GET_RECPTR_BY_CHNID(u32ChnId);
    if (HI_UNF_PVR_REC_STATE_INVALID ==  pstChnAttr->enState)
    {
        return u64CorrectGlobalOffset;
    }

    if (HI_NULL != pstChnAttr->IndexHandle)
    {
        u64CorrectGlobalOffset = PVR_Index_CACorrectFileOffset(pstChnAttr->IndexHandle, u64GlobalOffset, &pstChnAttr->stLastRecInfo);
    }
#endif
    return u64CorrectGlobalOffset;
}

HI_S32 HI_PVR_RecGetHandle(HI_HANDLE hPVR, HI_MOD_ID_E enModID, HI_HANDLE *pHandle, HI_U32 *pu32DemuxID)
{
    HI_U32 u32ChnID = (HI_U32)hPVR;
    PVR_REC_CHN_S* pRecChn = HI_NULL;

    HI_PVR_DEBUG_ENTER();

    CHECK_REC_CHNID(u32ChnID);

    if ((HI_NULL == pHandle) || (HI_NULL == pu32DemuxID))
    {
        HI_ERR_PVR("null pointer for pHandle");
        return HI_ERR_PVR_NUL_PTR;
    }

    if (HI_ID_DEMUX != enModID)
    {
        HI_ERR_PVR("input mod(%d) is not supported!\n", enModID);
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    pRecChn = PVR_GET_RECPTR_BY_CHNID(u32ChnID);
    PVR_LOCK(&(pRecChn->stMutex));
    CHECK_REC_CHN_INIT_UNLOCK(pRecChn);

    if ((HI_UNF_PVR_REC_STATE_INIT == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_RUNNING == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_PAUSE == pRecChn->enState)
        || (HI_UNF_PVR_REC_STATE_STOP == pRecChn->enState))
    {
        *pHandle = pRecChn->DemuxRecHandle;
        *pu32DemuxID = pRecChn->stUserCfg.u32DemuxID;
    }
    else
    {
        HI_ERR_PVR("Current state(%d) is invalid!\n", pRecChn->enState);
        PVR_UNLOCK(&(pRecChn->stMutex));
        return HI_ERR_PVR_REC_INVALID_STATE;
    }

    PVR_UNLOCK(&(pRecChn->stMutex));

    HI_PVR_DEBUG_EXIT();
    return HI_SUCCESS;
}

/*�����κϷ���*/
static HI_S32 PVRRecFileTruncateCheckUserCfg(const HI_CHAR *pszSrcFileName, HI_U32 u32SrcFileNameLen, const HI_CHAR *pszDstFileName, const HI_MPI_PVR_RECFILE_TRUNCATE_INFO_S *pstTruncInfo)
{
    if (HI_FALSE == pstTruncInfo->bTruncateTail)
    {
        HI_ERR_PVR("User configuration doesn't require truncate operation!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    if (HI_TRUE == pstTruncInfo->bTruncateHead)
    {/*��֧�ִ���ͷ��*/
        HI_ERR_PVR("Truncate does not support processing file headers!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    if (HI_NULL != pszDstFileName)
    {
        HI_ERR_PVR("Does not support truncate on target files!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    if (strlen(pszSrcFileName) != u32SrcFileNameLen)
    {
        HI_ERR_PVR("Invalid filename configuration!\n");
        return HI_ERR_PVR_INVALID_PARA;
    }

    if (HI_FALSE == pstTruncInfo->bSync)
    {/*��֧���첽����*/
        HI_ERR_PVR("Does not support asynchronous processing!\n");
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

/*׼��������Դ*/
static HI_S32 PVRRecFileTruncatePrepare(const HI_CHAR *pszSrcFileName, PVR_TRUNCATE_PROC_S *pstTruncateProcInfo)
{
    HI_CHAR szSrcRealFileName[PATH_MAX] = {0};
    HI_CHAR szSrcIndexFileName[PVR_MAX_FILENAME_LEN] = {0};

    if(strlen(pszSrcFileName) >= PVR_MAX_FILENAME_LEN)
    {
        HI_ERR_PVR("The Absolute fileName is too long, FileNameLen: %u ,MaxFileNameLen: %u\n", strlen(szSrcRealFileName), PVR_MAX_FILENAME_LEN);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }

    //ԭ�ļ�
    if(HI_NULL == realpath(pszSrcFileName, szSrcRealFileName))
    {
        HI_ERR_PVR("get real fileName failed! szFileName: %s\n", pszSrcFileName);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }
    if(strlen(szSrcRealFileName) >= PVR_MAX_FILENAME_LEN)
    {
        HI_ERR_PVR("The Absolute fileName is too long, FileNameLen: %u ,MaxFileNameLen: %u\n", strlen(szSrcRealFileName), PVR_MAX_FILENAME_LEN);
        return HI_ERR_PVR_FILE_INVALID_FNAME;
    }
    snprintf(pstTruncateProcInfo->szSrcFileName, PVR_MAX_FILENAME_LEN - 1,"%s", szSrcRealFileName);

    (HI_VOID)PVR_Index_GetIdxFileName(szSrcIndexFileName, pstTruncateProcInfo->szSrcFileName);
     /*���ԭ�ļ��Ƿ����*/
    if ((HI_FALSE == PVR_CHECK_FILE_EXIST64(pstTruncateProcInfo->szSrcFileName)) || (HI_FALSE == PVR_CHECK_FILE_EXIST64(szSrcIndexFileName)))
    {
        HI_ERR_PVR("original file(%s) doesn't exist! Ret = 0x%x\n", pstTruncateProcInfo->szSrcFileName, HI_ERR_PVR_FILE_NOT_EXIST);
        return HI_ERR_PVR_FILE_NOT_EXIST;
    }
    /*���ԭ�ļ��Ƿ���¼��*/
    if (HI_TRUE == PVRRecCheckFileRecording(pstTruncateProcInfo->szSrcFileName))
    {
        HI_ERR_PVR("The current file(%s) is being recorded! Ret = %x\n", pstTruncateProcInfo->szSrcFileName, HI_ERR_PVR_NOT_SUPPORT);
        return HI_ERR_PVR_NOT_SUPPORT;
    }

    /*open file*/
    pstTruncateProcInfo->s32OrigIdxFd = PVR_OPEN(szSrcIndexFileName, PVR_FOPEN_MODE_INDEX_BOTH);
    if (PVR_FILE_INVALID_FILE == pstTruncateProcInfo->s32OrigIdxFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", szSrcIndexFileName);
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    pstTruncateProcInfo->s32OrigTsFd = PVR_OPEN64(pstTruncateProcInfo->szSrcFileName, PVR_FOPEN_MODE_DATA_BOTH);
    if (PVR_FILE_INVALID_FILE == pstTruncateProcInfo->s32OrigTsFd)
    {
        HI_ERR_PVR("open file(%s) failed!\n", pstTruncateProcInfo->szSrcFileName);
        PVR_CLOSE(pstTruncateProcInfo->s32OrigIdxFd);
        pstTruncateProcInfo->s32OrigIdxFd = PVR_FILE_INVALID_FILE;
        return HI_ERR_PVR_FILE_CANT_OPEN;
    }

    return HI_SUCCESS;
}

/*ͬ������*/
static HI_S32 PVRRecFileTruncateSynchronizeProc(PVR_TRUNCATE_PROC_S *pstTruncateProcInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    /*���������ļ�*/
    s32Ret = PVR_Index_RecFileTruncateProccessIndex(pstTruncateProcInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("truncate index file failed! Ret = %x\n", s32Ret);
        return s32Ret;
    }

    /*����TS�ļ�*/
    s32Ret = PVR_FTRUNCATE64(pstTruncateProcInfo->s32OrigTsFd, pstTruncateProcInfo->u64TsTruncateOffset);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("truncate ts file failed! Ret = %x \n", s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

static HI_VOID PVRRecFileTruncateRelease(PVR_TRUNCATE_PROC_S *pstTruncateProcInfo)
{
    if (PVR_FILE_INVALID_FILE != pstTruncateProcInfo->s32OrigTsFd)
    {
        PVR_CLOSE64(pstTruncateProcInfo->s32OrigTsFd);
    }

    if (PVR_FILE_INVALID_FILE != pstTruncateProcInfo->s32OrigIdxFd)
    {
        PVR_CLOSE(pstTruncateProcInfo->s32OrigIdxFd);
    }

    memset(pstTruncateProcInfo, 0x00, sizeof(PVR_TRUNCATE_PROC_S));

    return ;
}

HI_S32 HI_PVR_RecFileTruncate(const HI_CHAR *pszSrcFileName, HI_U32 u32SrcFileNameLen, const HI_CHAR *pszDstFileName, HI_U32 u32DstFileNameLen, const HI_MPI_PVR_RECFILE_TRUNCATE_INFO_S *pstTruncInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U64 u64OrigTsFileSize = 0;
    PVR_TRUNCATE_PROC_S *pstTruncateProcInfo = HI_NULL;

    PVR_CHECK_POINTER(pszSrcFileName);
    PVR_CHECK_POINTER(pstTruncInfo);

    /*����������*/
    s32Ret = PVRRecFileTruncateCheckUserCfg(pszSrcFileName, u32SrcFileNameLen, pszDstFileName, pstTruncInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("invalid paramenters! Ret = %x\n", s32Ret);
        return s32Ret;
    }

    /*mallc truncateProcInfo*/
    pstTruncateProcInfo = HI_MALLOC(HI_ID_PVR, sizeof(PVR_TRUNCATE_PROC_S));
    if (HI_NULL == pstTruncateProcInfo)
    {
        HI_ERR_PVR("malloc truncateProcInfo buffer failed!\n");
        return HI_ERR_PVR_NO_MEM;
    }

    /*��ʼ����ز���*/
    memset(pstTruncateProcInfo, 0x00, sizeof(PVR_TRUNCATE_PROC_S));
    pstTruncateProcInfo->s32OrigTsFd = PVR_FILE_INVALID_FILE;
    pstTruncateProcInfo->s32OrigIdxFd = PVR_FILE_INVALID_FILE;
    memset(pstTruncateProcInfo->szSrcFileName, 0x00, sizeof(HI_CHAR) * PVR_MAX_FILENAME_LEN);
    memcpy(&pstTruncateProcInfo->stTruncateUserCfg, pstTruncInfo, sizeof(HI_MPI_PVR_RECFILE_TRUNCATE_INFO_S));

    s32Ret = PVRRecFileTruncatePrepare(pszSrcFileName, pstTruncateProcInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Failed to prepare truncate parameters! Ret = %x\n", s32Ret);
        HI_FREE(HI_ID_PVR, pstTruncateProcInfo);
        return s32Ret;
    }

    /*�޸�����*/
    u64OrigTsFileSize = PVR_FILE_GetFileSize64(pstTruncateProcInfo->szSrcFileName);
    s32Ret = PVR_Index_CorretIndexFile(pstTruncateProcInfo, u64OrigTsFileSize);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("correct index file failed! Ret = %x\n", s32Ret);
        (HI_VOID)PVRRecFileTruncateRelease(pstTruncateProcInfo);
        HI_FREE(HI_ID_PVR, pstTruncateProcInfo);
        return s32Ret;
    }

    /*����Ƿ��������truncate������*/
    s32Ret = PVR_Index_RecFileTruncateCheckNeedToDo(pstTruncateProcInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Current conditions cannot be truncate! Ret = %x\n", s32Ret);
        (HI_VOID)PVRRecFileTruncateRelease(pstTruncateProcInfo);
        HI_FREE(HI_ID_PVR, pstTruncateProcInfo);
        return s32Ret;
    }

    /*����ԭ�ļ�ͬ������*/
    s32Ret = PVRRecFileTruncateSynchronizeProc(pstTruncateProcInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Failed to synchronize truncate! Ret = %x\n", s32Ret);
    }

    /*�ͷ���Դ*/
    (HI_VOID)PVRRecFileTruncateRelease(pstTruncateProcInfo);
    HI_FREE(HI_ID_PVR, pstTruncateProcInfo);

    return s32Ret;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

