#include "vmm.h"
#include "vmm_osal.h"
#include "vmm_core.h"
#include "vmm_memlist_manager.h"
#include "vmm_msglist_manager.h"
#include "vmm_memory_ops.h"
#include "vfmw_osal_proc.h"

#define VMM_PROC_NAME                        "vfmw_vmm"
#define VMM_CMD_NUM                          (2)
#define VMM_CMD_LEN                          (50)

#define VMM_DEFAULT_WAITTIME                 (5)
#define VMM_MAX_RLSNUM_BY_CMD                (5)
#define VMM_MAX_RLSNUM_BY_THREAD             (20)

#define MAX_STATISTIC_NUM                    (30)

#define START_TICK                           (0)
#define ADDMSG_END_TICK                      (1)
#define THREAD_RESPOND_TICK                  (2)
#define PROCESS_END_TICK                     (3)
#define CALLBACK_END_TICK                    (4)
#define TICK_NUM                             (CALLBACK_END_TICK + 1)

#define VMM_MUTEX_INIT(pMutex)                \
    do                                        \
    {                                         \
        sema_init(pMutex, 1);                 \
    }while(0)

#define VMM_MUTEX_LOCK(pMutex)                \
    do                                        \
    {                                         \
        SINT32 Ret;                           \
        Ret = down_interruptible(pMutex);     \
    }while(0)

#define VMM_MUTEX_UNLOCK(pMutex)              \
    do                                        \
    {                                         \
        (VOID)up(pMutex);                     \
    }while(0)

#define VMM_SPINLOCK_INIT(pLock)              \
    do                                        \
    {                                         \
        spin_lock_init(pLock);                \
    }while(0)

#define VMM_SPINLOCK_LOCK(pLock, Flags)                         \
    do                                                          \
    {                                                           \
        spin_lock_irqsave(pLock, Flags);                        \
    }while(0)

#define VMM_SPINLOCK_UNLOCK(pLock, Flags)                       \
    do                                                          \
    {                                                           \
        spin_unlock_irqrestore(pLock, Flags);                   \
    }while(0)

typedef enum
{
    THREAD_STATUS_PREPARE = 0,
    THREAD_STATUS_STOP,
    THREAD_STATUS_RUNNING,
    THREAD_STATUS_EXIT,
    THREAD_STATUS_SLEEP,
    THREAD_STATUS_BUTT,
} THREAD_STATUS_E;

typedef struct
{
    UINT32     TimeTick[TICK_NUM];
    UINT32     TimeConsume[TICK_NUM];
    Msg_Data_S MsgInfo;
    UINT32     PriorFlag;
} VMM_Statistic_S;

typedef struct
{
    UINT32          MaxTimeConsume[TICK_NUM];
    UINT32          LastPriorMsgTimeConsume[TICK_NUM];
    VMM_Statistic_S TimeStatInUs[MAX_STATISTIC_NUM];
    UINT32          WritePointer;
    UINT32          MsgCnt;
} VMM_DBG_S;

typedef struct
{
    UINT32 IsInit;
    SINT32 StopThead;
    VOID *hThread;
    struct semaphore Mutex;
    spinlock_t       Lock;
    unsigned long    LockFlags;
    VMM_EVENT_S Event;
    THREAD_STATUS_E ThreadStatus;
    UINT32 ThreadWaitTimeInMs;
    PFN_VMM_CALLBACK pfCallback;

    VMM_DBG_S        *pDbgInfo;
} VMM_GLOBAL_CTX_S;

extern UINT32 g_VmmPrintEn;

static VMM_GLOBAL_CTX_S g_VmmCtx =
{
    .IsInit = 0,
    .StopThead = 0,
    .pfCallback = NULL,
    .hThread = NULL,
    .ThreadStatus = THREAD_STATUS_BUTT,
    .ThreadWaitTimeInMs = VMM_DEFAULT_WAITTIME,
};

static SINT32 VMM_Core_Alloc_FromThread(VOID *pParamIn);

static const VMM_CMD_NODE g_VMM_BLK_CommandTable[] =
{
    {VMM_CMD_BLK_SetLocation,                 VMM_Core_SetLocation},
    {VMM_CMD_BLK_Alloc,                       VMM_Core_Alloc},
    {VMM_CMD_BLK_Release,                     VMM_Core_Release},
    {VMM_CMD_BLK_ConfigMemNode,               VMM_Core_ConfigMemNode},
    {VMM_CMD_BLK_Map,                         VMM_Core_Map},
    {VMM_CMD_BLK_Unmap,                       VMM_Core_Unmap},
    {VMM_CMD_BLK_ConfigMemPool,               VMM_Core_ConfigMemBlock},
    {VMM_CMD_BLK_ReleaseBurst,                VMM_Core_ReleaseBurst},
    {VMM_CMD_BLK_SetPriorityPolicy,           VMM_Core_SetPriorityPolicy},
    {VMM_CMD_BLK_GetMemNodeInfo,              VMM_Core_GetMemNodeInfo},
    {VMM_CMD_BLK_CancleCmd,                   VMM_Core_CancleCmd},
    {VMM_CMD_BLK_TYPE_BUTT,                   HI_NULL}, //terminal element
};

static const VMM_CMD_NODE g_VMM_CommandTable[] =
{
    {VMM_CMD_Alloc,                          VMM_Core_Alloc_FromThread},
    {VMM_CMD_Release,                        VMM_Core_Release},
    {VMM_CMD_ReleaseBurst,                   VMM_Core_ReleaseBurst},

    {VMM_CMD_BLK_TYPE_BUTT,                  HI_NULL}, //terminal element
};

static FN_VMM_CMD_HANDLER VMM_Core_Get_Handler(UINT32 CmdID, UINT32 BlkCmdFlag)
{
    UINT32 Index = 0;
    const VMM_CMD_NODE *pCmdTable = NULL;
    SINT32 LoopTime = 0;
    FN_VMM_CMD_HANDLER pTargetHandler = NULL;

    if (BlkCmdFlag)
    {
        pCmdTable = g_VMM_BLK_CommandTable;
        LoopTime = sizeof(g_VMM_BLK_CommandTable) / sizeof(VMM_CMD_NODE);
    }
    else
    {
        pCmdTable = g_VMM_CommandTable;
        LoopTime = sizeof(g_VMM_CommandTable) / sizeof(VMM_CMD_NODE);
    }

    while (Index < LoopTime)
    {
        if (pCmdTable[Index].CmdID == EVNT_BUTT || pCmdTable[Index].pHandler == HI_NULL)
        {
            break;
        }

        if (CmdID == pCmdTable[Index].CmdID)
        {
            pTargetHandler = pCmdTable[Index].pHandler;
            break;
        }

        Index++;
    }

    return pTargetHandler;
}

static SINT32 Convert_MsgData(VMM_CMD_TYPE_E CmdID, VOID *pArgs, Msg_Data_S *pMsgData)
{
    SINT32 Ret = VMM_SUCCESS;

    switch (CmdID)
    {
        case VMM_CMD_Alloc:
        case VMM_CMD_Release:
        {
            VMM_BUFFER_S *pBufRec = (VMM_BUFFER_S *)pArgs;

            pMsgData->PrivID = pBufRec->PrivID;
            pMsgData->CmdID  = CmdID;
            OSAL_FP_memcpy(&pMsgData->Param.BufRec, pBufRec, sizeof(VMM_BUFFER_S));
        }
        break;

        case VMM_CMD_ReleaseBurst:
        {
            VMM_RLS_BURST_S *pRlsBurst = (VMM_RLS_BURST_S *)pArgs;

            pMsgData->PrivID = pRlsBurst->PrivID;
            pMsgData->CmdID  = CmdID;
            OSAL_FP_memcpy(&pMsgData->Param.RlsBurst, pRlsBurst, sizeof(VMM_RLS_BURST_S));
        }
        break;

        default:
        {
            Ret = VMM_FAILURE;
            PRINT(PRN_ERROR, "%s,%d, not support CmdID = %d\n", __func__, __LINE__, CmdID);
        }
        break;
    }

    return Ret;
}

static VOID Convert_MemData_FirstTime(VMM_BUFFER_S *pBuferInfo, UINT32 TimeConsume, Mem_Data_S *pMemData)
{
    OSAL_FP_memset(pMemData, 0, sizeof(Mem_Data_S));

    pMemData->Status = Node_Status_InUse;
    pMemData->Location = VMM_LOCATION_INSIDE;

    OSAL_FP_memcpy(&pMemData->BufInfo, pBuferInfo, sizeof(VMM_BUFFER_S));

    pMemData->DbgInfo.AllocTimeConsumeInUs = TimeConsume;

    return;
}

static VOID WakeUp_Thread(VOID)
{
    VMM_Osal_GiveEvent(&g_VmmCtx.Event);
}

static VOID WaitForEvent_Thread(VOID)
{
    VMM_Osal_WaitEvent(&g_VmmCtx.Event, g_VmmCtx.ThreadWaitTimeInMs);
}

static SINT32 ProtectedWithSpinLock_BlkCmd(VMM_CMD_BLK_TYPE_E Cmd)
{
    SINT32 Ret = VMM_FALSE;

    if ((Cmd == VMM_CMD_BLK_SetLocation) || (Cmd == VMM_CMD_BLK_CancleCmd))
    {
        Ret = VMM_TRUE;
    }

    return Ret;
}

static SINT32 GetDbgInfoID(UINT32 MsgTick, UINT32 *pIndex)
{
    UINT32 i;
    SINT32 Ret = VMM_FAILURE;
    VMM_DBG_S *pDbg = g_VmmCtx.pDbgInfo;
    UINT32 Index = pDbg->WritePointer;

    for (i = 0; i < MAX_STATISTIC_NUM; i++)
    {
        if (pDbg->TimeStatInUs[Index].MsgInfo.Tick == MsgTick)
        {
            *pIndex = Index;
            Ret = VMM_SUCCESS;

            return Ret;
        }

        Index = (Index == (MAX_STATISTIC_NUM - 1)) ? (0) : (Index + 1);
    }

    return Ret;
}

static SINT32 VMM_Dbg_Initial(VOID)
{
    g_VmmCtx.pDbgInfo = (VMM_DBG_S *)OSAL_FP_alloc_virmem(sizeof(VMM_DBG_S));

    if (g_VmmCtx.pDbgInfo == NULL)
    {
        PRINT(PRN_FATAL, "%s,%d, alloc Debug mem failed! size = %d\n", __func__, __LINE__, sizeof(VMM_DBG_S));

        return VMM_FAILURE;
    }

    OSAL_FP_memset(g_VmmCtx.pDbgInfo, 0, sizeof(VMM_DBG_S));
    g_VmmCtx.pDbgInfo->MsgCnt = 1;

    return VMM_SUCCESS;
}

static VOID VMM_Dbg_DeInitial(VOID)
{
    if (g_VmmCtx.pDbgInfo)
    {
        OSAL_FP_free_virmem(g_VmmCtx.pDbgInfo);
        g_VmmCtx.pDbgInfo = NULL;
    }
}

static VOID VMM_Dbg_CalculateTime(UINT32 Index)
{
    UINT32 i;
    VMM_DBG_S *pDbg = g_VmmCtx.pDbgInfo;
    UINT32 *pTimeTick = &pDbg->TimeStatInUs[Index].TimeTick[0];
    UINT32 *pTimeConsume = &pDbg->TimeStatInUs[Index].TimeConsume[0];
    UINT32 *pMaxTimeConsume = &pDbg->MaxTimeConsume[0];

    for (i = 0; i < (TICK_NUM - 1); i++)
    {
        pTimeConsume[i] = pTimeTick[i + 1] - pTimeTick[i];
    }

    pTimeConsume[TICK_NUM - 1] = pTimeTick[TICK_NUM - 1] - pTimeTick[0];

    for (i = 0; i < TICK_NUM; i++)
    {
        if (pMaxTimeConsume[i] < pTimeConsume[i])
        {
            pMaxTimeConsume[i] = pTimeConsume[i];
        }
    }

    if (pDbg->TimeStatInUs[Index].PriorFlag || pDbg->TimeStatInUs[Index].MsgInfo.Tick == 1)
    {
        OSAL_FP_memcpy(pDbg->LastPriorMsgTimeConsume, pTimeConsume, sizeof(UINT32)*TICK_NUM);
    }

    return;
}

static VOID VMM_Dbg_RecordTime(Msg_Data_S *pMsgData, UINT32 Pos, UINT32 PriorFlag)
{
    VMM_DBG_S *pDbg = g_VmmCtx.pDbgInfo;
    UINT32 CurTime = OSAL_FP_get_time_us();
    UINT32 Index = pDbg->WritePointer;

    if (Pos >= TICK_NUM)
    {
        PRINT(PRN_ERROR, "Pos(%d) not support !\n", Pos);
    }

    if (Pos == START_TICK)
    {
        OSAL_FP_memset(&pDbg->TimeStatInUs[Index].TimeTick[0], 0, sizeof(UINT32)*TICK_NUM);
        pMsgData->Tick = pDbg->MsgCnt;
        pDbg->TimeStatInUs[Index].TimeTick[START_TICK] = CurTime;
    }
    else if (Pos == ADDMSG_END_TICK)
    {
        pDbg->TimeStatInUs[Index].TimeTick[ADDMSG_END_TICK] = CurTime;
        OSAL_FP_memcpy(&pDbg->TimeStatInUs[Index].MsgInfo, pMsgData, sizeof(Msg_Data_S));
        pDbg->TimeStatInUs[Index].PriorFlag = PriorFlag;

        pDbg->WritePointer = (pDbg->WritePointer == (MAX_STATISTIC_NUM - 1)) ? (0) : (pDbg->WritePointer + 1); //updata wp
        pDbg->MsgCnt++;
    }
    else if (GetDbgInfoID(pMsgData->Tick, &Index) == VMM_SUCCESS)
    {
        if (Pos >= 5)
        {
            PRINT(PRN_FATAL, "line %d func %s pos = %d\n", __LINE__, __func__, Pos);
            return;
        }

        pDbg->TimeStatInUs[Index].TimeTick[Pos] = CurTime;

        if (Pos == CALLBACK_END_TICK)
        {
            VMM_Dbg_CalculateTime(Index);
        }
    }

    return;
}

static SINT32 VMM_Dbg_ReadProc(VOID *p)
{
    UINT32 i;
    UINT32 Index;
    VMM_DBG_S *pDbg = g_VmmCtx.pDbgInfo;
    VMM_Statistic_S *pStatistic = pDbg->TimeStatInUs;
    SINT8 CmdIdTab  [VMM_CMD_TYPE_BUTT + 1 ][16]  = {{"Alloc"}, {"Release"}, {"ReleaseBurst"}, {"Unknown"}};
    UINT32 ShowNum = 10; //MAX_STATISTIC_NUM

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);

    //statistics info
    PROC_PRINT(p, "------------------------------------------------- Msg History ----------------------------------------------------------- \n");

    PROC_PRINT(p, "  NO.\t        PrivID\t              CmdID    |   AddMsg\t Thread\t\t Process\t  CallBack\t    Total\n");
    PROC_PRINT(p, "\t\t\t                       |  %-7d\t %-7d\t %-7d\t %-7d\t  %-7d\t\n",
               pDbg->LastPriorMsgTimeConsume[0], pDbg->LastPriorMsgTimeConsume[1], pDbg->LastPriorMsgTimeConsume[2],
               pDbg->LastPriorMsgTimeConsume[3], pDbg->LastPriorMsgTimeConsume[4]);
    PROC_PRINT(p, "\t\t\t                       |  %-7d\t %-7d\t %-7d\t %-7d\t  %-7d\t\n",
               pDbg->MaxTimeConsume[0], pDbg->MaxTimeConsume[1], pDbg->MaxTimeConsume[2],
               pDbg->MaxTimeConsume[3], pDbg->MaxTimeConsume[4]);
    PROC_PRINT(p, "-----------------------------------------------|------------------------------------------------------------------------- \n");

    Index = (pDbg->WritePointer == 0) ? (MAX_STATISTIC_NUM - 1) : (pDbg->WritePointer - 1);

    for (i = 0; i < ShowNum; i++)
    {
        PROC_PRINT(p, "%-4d\t 0x%-16llx\t %-12s  |  %-7d\t %-7d\t %-7d\t %-7d\t  %-7d\t\n",
                   pStatistic[Index].MsgInfo.Tick, pStatistic[Index].MsgInfo.PrivID, CmdIdTab[pStatistic[Index].MsgInfo.CmdID],
                   pStatistic[Index].TimeConsume[0], pStatistic[Index].TimeConsume[1], pStatistic[Index].TimeConsume[2],
                   pStatistic[Index].TimeConsume[3], pStatistic[Index].TimeConsume[4]);
        Index = (Index == 0) ? (MAX_STATISTIC_NUM - 1) : (Index - 1);
    }

    return VMM_SUCCESS;
}

static SINT32 VMM_Proc_Read(struct seq_file *p, VOID *v)
{
    VMM_Msglist_ReadProc(p);

    VMM_Dbg_ReadProc(p);

    PROC_PRINT(p, "\n");

    VMM_Memlist_ReadProc(p);

    PROC_PRINT(p, "\n\n");

    return VDEC_OK;
}

static VOID VMM_Proc_ParseParam(UINT8 *pParam, UINT8 pCmd[VMM_CMD_NUM][VMM_CMD_LEN])
{
    UINT32 ParsePos = 0;
    UINT32 ParseNum = 0;
    UINT32 StrLen = 0;
    UINT8 *pCurStr = NULL;

    OSAL_FP_memset(pCmd, 0, VMM_CMD_NUM * VMM_CMD_LEN);

    do
    {
        StrLen = 0;
        pCurStr = pCmd[ParseNum];

        for (; ParsePos < OSAL_FP_strlen(pParam); ParsePos++)
        {
            if (StrLen == 0 && pParam[ParsePos] == ' ')
            {
                continue;
            }

            if (pParam[ParsePos] > ' ')
            {
                pCurStr[StrLen++] = pParam[ParsePos];
            }

            if (StrLen > 0 && pParam[ParsePos] == ' ')
            {
                break;
            }
        }

        pCurStr[StrLen] = '\0';
        ParseNum++;

    }
    while (ParseNum < VMM_CMD_NUM);

    return;
}

static VOID VMM_Proc_Help(VOID)
{
    PRINT(PRN_ALWS, "------ VMM Proc Help ------\n");
    PRINT(PRN_ALWS, "USAGE:echo [cmd] [para1] [para2] > /proc/vfmw/vmm\n");
    PRINT(PRN_ALWS, "cmd = PrintEn,     para1 = print_enable_word  \n");
    PRINT(PRN_ALWS, "--------------------------- \n");
    PRINT(PRN_ALWS, "'print_enable_word' definition, from bit31 to bit0: \n");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "--", "--", "--");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "--", "DBG", "INFO", "TimeDly");
    PRINT(PRN_ALWS, "%8s  %8s  %8s   %8s\n", "IMP", "WARN", "ERROR", "FATAL");
}

static VOID VMM_Proc_CommandHanlder(UINT8 pCmd[VMM_CMD_NUM][VMM_CMD_LEN])
{
    UINT32 Value = 0;
    UINT32 CmdNum = 0;

    if (!OSAL_FP_strncmp(pCmd[CmdNum], "PrintEn", OSAL_FP_strlen("PrintEn")))
    {
        if (string_to_value(pCmd[CmdNum + 1], &Value) != 0)
        {
            PRINT(PRN_ALWS, "error string_to_value '%s'!\n", pCmd[CmdNum + 1]);

            return;
        }

        g_VmmPrintEn = Value;
        PRINT(PRN_ALWS, "Set g_VmmPrintEn %d\n", g_VmmPrintEn);
    }
    else
    {
        VMM_Proc_Help();
    }

    return;
}

static SINT32 VMM_Proc_Write(struct file *file, const char __user *buffer, size_t count, loff_t *data)
{
    UINT8 Param[VMM_CMD_LEN];
    UINT8 CmdStr[VMM_CMD_NUM][VMM_CMD_LEN];

    if (count < 1 || count >= sizeof(Param))
    {
        PRINT(PRN_ALWS, "parameter string invalid!\n");

        return VDEC_ERR;
    }

    if (copy_from_user(Param, buffer, count))
    {
        PRINT(PRN_ALWS, "copy_from_user failed!\n");

        return VDEC_ERR;
    }

    Param[count] = '\0';

    VMM_Proc_ParseParam(Param, CmdStr);

    VMM_Proc_CommandHanlder(CmdStr);

    return count;
}

static SINT32 VMM_Alloc_Real(VMM_BUFFER_S *pMemInfo)
{
    SINT32 Ret;
    Mem_Data_S MemData;
    UINT32 StartTime = 0;
    UINT32 StopTime = 0;

    StartTime = OSAL_FP_get_time_us();
    Ret = VMM_Ops_Alloc(pMemInfo);
    StopTime = OSAL_FP_get_time_us();

    if (Ret == VMM_SUCCESS)
    {
        Convert_MemData_FirstTime(pMemInfo, StopTime - StartTime, &MemData);

        Ret = VMM_Memlist_AddNode(&MemData);

        if (Ret != VMM_SUCCESS)
        {
            PRINT(PRN_ERROR, "%s,%d,add Memlist failed!, Name = '%s', Size = %d\n", __func__, __LINE__, pMemInfo->BufName, pMemInfo->Size);

            if (VMM_Ops_Release(pMemInfo) != VMM_SUCCESS)
            {
                PRINT(PRN_ERROR, "%s,%d, Memlist AddNode failed!, BufferName = '%s', BuferAddr = 0x%x, Size = %d\n", __func__, __LINE__,
                      pMemInfo->BufName, pMemInfo->StartPhyAddr, pMemInfo->Size);
            }
        }
    }

    return Ret;
}

static SINT32 VMM_Release_Real(VMM_BUFFER_S *pMemInfo)
{
    SINT32 Ret;

    Ret = VMM_Ops_Release(pMemInfo);

    if (Ret == VMM_SUCCESS)
    {
        if (VMM_Memlist_DeleteNodeByPhyaddr(pMemInfo->StartPhyAddr) != VMM_SUCCESS)
        {
            PRINT(PRN_ERROR, "%s,%d,Delete Memlist failed!, BuferAddr = 0x%x, Size = %d\n", __func__, __LINE__, pMemInfo->StartPhyAddr, pMemInfo->Size);
        }
    }

    return Ret;
}

static VOID VMM_Release_ExpectLen(UINT32 ExpectLen, UINT32 MaxRlsNum, UINT32 LockEn)
{
    SINT32 Ret = VMM_SUCCESS;
    UINT32 LoopCntMax = 0;
    UINT32 RlsLen = 0;
    Mem_Data_S  MemData;

    while ((!g_VmmCtx.StopThead) && (Ret == VMM_SUCCESS) && (RlsLen < ExpectLen) && (LoopCntMax < MaxRlsNum))
    {
        OSAL_FP_memset(&MemData, 0, sizeof(Mem_Data_S));

        if (LockEn)
        {
            VMM_MUTEX_LOCK(&g_VmmCtx.Mutex);
        }

        Ret = VMM_Memlist_FindOneNodeCanBeRls(&MemData);

        if (Ret == VMM_SUCCESS)
        {
            if (VMM_Release_Real(&MemData.BufInfo) != VMM_SUCCESS)
            {
                PRINT(PRN_ERROR, "%s,%d, Release buffer failed\n", __func__, __LINE__);
            }
            else
            {
                RlsLen += MemData.BufInfo.Size;
            }

            LoopCntMax++;
        }

        if (LockEn)
        {
            VMM_MUTEX_UNLOCK(&g_VmmCtx.Mutex);
        }
    }

    if (LoopCntMax >= MaxRlsNum)
    {
        PRINT(PRN_ERROR, "%s,%d, continuity release Memory %d time(ExpectLen = %d),don't go to release this time.\n", __func__, __LINE__, LoopCntMax, ExpectLen);
    }

    return;
}

static SINT32 VMM_Core_Alloc_FromThread(VOID *pParamIn)
{
    SINT32 Ret = VMM_SUCCESS;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;

    D_VMM_CHECK_PTR_RET(pMemInfo, ERR_VMM_NULL_PTR);
    VMM_Release_ExpectLen(pMemInfo->Size, VMM_MAX_RLSNUM_BY_CMD, 0);

    Ret = VMM_Alloc_Real(pMemInfo);

    return Ret;
}

static VOID CallBack_ExceptionHandle(VMM_CMD_TYPE_E CmdID, VOID *pParamOut, SINT32 RetVal)
{
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamOut;

    if (RetVal == VMM_SUCCESS)
    {
        if (CmdID == VMM_CMD_Alloc)
        {
            if (VMM_Release_Real(pMemInfo) != VMM_SUCCESS)
            {
                PRINT(PRN_ERROR, "%s,%d, Release remain Memory failed! BufName = %s, Phyaddr = 0x%x, Size = %d\n", __func__, __LINE__,
                      pMemInfo->BufName, pMemInfo->StartPhyAddr, pMemInfo->Size);
            }
        }
    }

    return;
}

static VOID CallBack_ReturnResult(VMM_CMD_TYPE_E CmdID, VOID *pParamOut, SINT32 RetVal)
{
    if (g_VmmCtx.pfCallback(CmdID, pParamOut, RetVal) != VMM_SUCCESS)
    {
        CallBack_ExceptionHandle(CmdID, pParamOut, RetVal);
    }

    return;
}

static SINT32 VMM_CmdProcess_OneCase(Msg_Data_S *pMsgData)
{
    SINT32 Ret = VMM_SUCCESS;
    FN_VMM_CMD_HANDLER pCmdHandler = HI_NULL;
    VOID *pParamIn = &pMsgData->Param;

    VMM_Dbg_RecordTime(pMsgData, THREAD_RESPOND_TICK, 0);

    pCmdHandler = VMM_Core_Get_Handler(pMsgData->CmdID, 0);

    D_VMM_CHECK_PTR_RET(pCmdHandler, ERR_VMM_NOT_SUPPORT);

    Ret = pCmdHandler(pParamIn);

    VMM_Dbg_RecordTime(pMsgData, PROCESS_END_TICK, 0);

    CallBack_ReturnResult(pMsgData->CmdID, pParamIn, Ret);

    VMM_Dbg_RecordTime(pMsgData, CALLBACK_END_TICK, 0);

    return Ret;
}

static VOID VMM_CmdProcess_All(VOID)
{
    Msg_Data_S MsgData;
    SINT32 Ret = VMM_OSAL_SUCCESS;

    while ((!g_VmmCtx.StopThead) && (VMM_Msglist_IsEmpty() != VMM_TRUE))
    {
        OSAL_FP_memset(&MsgData, 0, sizeof(Msg_Data_S));

        VMM_MUTEX_LOCK(&g_VmmCtx.Mutex);

        Ret = VMM_Msglist_TakeOutNode(&MsgData);

        if (Ret == VMM_OSAL_SUCCESS)
        {
            VMM_CmdProcess_OneCase(&MsgData);
        }
        else
        {
            PRINT(PRN_ERROR, "%s,%d,MsgList isn't Empty, but TakeOut Node Failed!\n", __func__, __LINE__);
        }

        VMM_MUTEX_UNLOCK(&g_VmmCtx.Mutex);
    }

    return;
}

static VOID VMM_TryToRelease_All(VOID)
{
    VMM_Release_ExpectLen(-1, VMM_MAX_RLSNUM_BY_THREAD, 1);
}

static VOID VMM_Thread_Process(VOID)
{
    g_VmmCtx.ThreadStatus = THREAD_STATUS_PREPARE;

    while (!g_VmmCtx.StopThead)
    {
        g_VmmCtx.ThreadStatus = THREAD_STATUS_RUNNING;

        VMM_CmdProcess_All();

        VMM_TryToRelease_All();

        if ((!g_VmmCtx.StopThead) && VMM_Msglist_IsEmpty())
        {
            g_VmmCtx.ThreadStatus = THREAD_STATUS_SLEEP;

            WaitForEvent_Thread();
        }
    }

    g_VmmCtx.ThreadStatus = THREAD_STATUS_EXIT;

    return;
}

SINT32 VMM_Core_Alloc(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pMemInfo, ERR_VMM_NULL_PTR);

    Ret = VMM_Alloc_Real(pMemInfo);

    return Ret;
}

SINT32 VMM_Core_Release(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pMemInfo, ERR_VMM_NULL_PTR);

    Ret = VMM_Memlist_MarkStatus(pMemInfo->StartPhyAddr, Node_Status_NoUse);

    if (Ret != VMM_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s mark mem %s status failed!\n", __func__, pMemInfo->BufName);
        return Ret;
    }

    if (VMM_Memlist_IsOneNodeCanBeRls(pMemInfo->StartPhyAddr) == VMM_SUCCESS)
    {
        Ret = VMM_Release_Real(pMemInfo);
    }

    return Ret;
}

SINT32 VMM_Core_Map(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pMemInfo, ERR_VMM_NULL_PTR);

    Ret = VMM_Ops_Map(pMemInfo);

    if (Ret == VMM_SUCCESS)
    {
        VMM_ASSERT(VMM_Memlist_UpdateBufRec(pMemInfo) == VMM_SUCCESS);
    }

    return Ret;
}

SINT32 VMM_Core_Unmap(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pParamIn, ERR_VMM_NULL_PTR);

    Ret = VMM_Ops_Unmap(pMemInfo);

    if (Ret == VMM_SUCCESS)
    {
        VMM_ASSERT(VMM_Memlist_UpdateBufRec(pMemInfo) == VMM_SUCCESS);
    }

    return Ret;
}

SINT32 VMM_Core_ConfigMemBlock(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_BUFFER_S *pMemInfo = (VMM_BUFFER_S *)pParamIn;
    UINT32 StartTime = 0;
    UINT32 StopTime = 0;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pMemInfo, ERR_VMM_NULL_PTR);

    StartTime = OSAL_FP_get_time_us();
    Ret = VMM_Ops_ConfigMemBlock(pMemInfo);
    StopTime = OSAL_FP_get_time_us();

    if (Ret == VMM_SUCCESS)
    {
        Mem_Data_S MemData;

        Convert_MemData_FirstTime(pMemInfo, StopTime - StartTime, &MemData);

        Ret = VMM_Memlist_AddNode(&MemData);

        if (Ret != VMM_SUCCESS)
        {
            PRINT(PRN_ERROR, "%s,%d,add Memlist failed!, BuferAddr = 0x%x, Size = %d\n", __func__, __LINE__,
                  pMemInfo->StartPhyAddr, pMemInfo->Size);
        }
    }

    return Ret;
}

SINT32 VMM_Core_ConfigMemNode(VOID *pParamIn)
{
    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);

    return ERR_VMM_NOT_SUPPORT;
}

SINT32 VMM_Core_SetLocation(VOID *pParamIn)
{
    SINT32 Ret;
    VMM_ATTR_S *pInput = (VMM_ATTR_S *)pParamIn;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pInput, ERR_VMM_NULL_PTR);

    Ret = VMM_Memlist_MarkLocation(pInput->PhyAddr, pInput->Location);

    return Ret;
}

SINT32 VMM_Core_ReleaseBurst(VOID *pParamIn)
{
    SINT32 Ret = VMM_SUCCESS;
    SINT32 RetTemp = VMM_SUCCESS;
    SINT32 RlsCnt = 0;
    VMM_RLS_BURST_S *pRlsBurst = (VMM_RLS_BURST_S *)pParamIn;
    Msg_Delete_S MsgDelete;
    Mem_Data_S MemData;
    VMM_BUFFER_S *pBufInfo = &MemData.BufInfo;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pParamIn, ERR_VMM_NULL_PTR);

    OSAL_FP_memset(&MsgDelete, 0, sizeof(Msg_Delete_S));
    MsgDelete.PrivIDValid = 1;
    MsgDelete.PrivID      = pRlsBurst->PrivID;
    MsgDelete.PrivMask    = pRlsBurst->PrivMask;
    Ret |= VMM_Msglist_DeleteSpecifiedNode(&MsgDelete);

    Ret |= VMM_Memlist_SetSpecifiedNodeNoUse(pRlsBurst);

    while ((RetTemp == VMM_SUCCESS) && (RlsCnt < 64))
    {
        OSAL_FP_memset(&MemData, 0, sizeof(Mem_Data_S));

        RetTemp = VMM_Memlist_TakeOutOneNodeCanBeRls(pRlsBurst, &MemData);

        if (RetTemp == VMM_SUCCESS)
        {
            RlsCnt++;

            if (VMM_Ops_Release(pBufInfo) != VMM_SUCCESS)
            {
                PRINT(PRN_ERROR, "%s,%d, BufName = %s,Phyaddr = 0x%x,Size = %d can be released,but release failed!\n", __func__, __LINE__,
                      pBufInfo->BufName, pBufInfo->StartPhyAddr, pBufInfo->Size);
            }
        }
    }

    return Ret;
}

SINT32 VMM_Core_SetPriorityPolicy(VOID *pParamIn)
{
    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);

    return ERR_VMM_NOT_SUPPORT;
}

SINT32 VMM_Core_GetMemNodeInfo(VOID *pParamIn)
{
    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);

    return ERR_VMM_NOT_SUPPORT;
}

SINT32 VMM_Core_CancleCmd(VOID *pParamIn)
{
    SINT32 Ret = VMM_SUCCESS;
    VMM_CANCLE_CMD_S *pCancleCmd = (VMM_CANCLE_CMD_S *)pParamIn;
    Msg_Delete_S MsgDelete;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pParamIn, ERR_VMM_NULL_PTR);

    OSAL_FP_memset(&MsgDelete, 0, sizeof(Msg_Delete_S));

    MsgDelete.CmdValid = 1;
    MsgDelete.CmdID = pCancleCmd->CmdID;
    MsgDelete.PrivIDValid = 1;
    MsgDelete.PrivID = pCancleCmd->PrivID;
    MsgDelete.PrivMask = pCancleCmd->PrivMask;

    Ret = VMM_Msglist_DeleteSpecifiedNode(&MsgDelete);

    return Ret;
}

SINT32 VMM_Core_AddMsg(const VMM_CMD_TYPE_E CmdID, VMM_CMD_PRIO_E Proir, VOID *pArgs)
{
    SINT32 Ret = VMM_SUCCESS;
    Msg_Data_S MsgData;

    D_VMM_ASSERT_RET((g_VmmCtx.IsInit == 1), ERR_VMM_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pArgs, ERR_VMM_NULL_PTR);

    OSAL_FP_memset(&MsgData, 0, sizeof(Msg_Data_S));

    VMM_Dbg_RecordTime(&MsgData, START_TICK, 0);

    if (Convert_MsgData(CmdID, pArgs, &MsgData) != VMM_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s command %d Convert_MsgData failed.\n", __func__, CmdID);
        return ERR_VMM_INVALID_PARA;
    }

    Ret = VMM_Msglist_AddNode(&MsgData, Proir);

    VMM_Dbg_RecordTime(&MsgData, ADDMSG_END_TICK, Proir);

    WakeUp_Thread();

    return Ret;
}

SINT32 VMM_Core_SendCmdBlock(VMM_CMD_BLK_TYPE_E CmdID, VOID *pParamInOut)
{
    SINT32 Ret = VMM_SUCCESS;
    FN_VMM_CMD_HANDLER pCmdHandler = HI_NULL;

    D_VMM_CHECK_PTR_RET(pParamInOut, ERR_VMM_NULL_PTR);

    if (CmdID >= VMM_CMD_BLK_TYPE_BUTT)
    {
        PRINT(PRN_ERROR, "%s invalid command %d\n", __func__, CmdID);
        return ERR_VMM_INVALID_PARA;
    }

    pCmdHandler = VMM_Core_Get_Handler(CmdID, 1);

    D_VMM_CHECK_PTR_RET(pCmdHandler, ERR_VMM_NOT_SUPPORT);

    if (ProtectedWithSpinLock_BlkCmd(CmdID) == VMM_TRUE)
    {
        VMM_SPINLOCK_LOCK(&g_VmmCtx.Lock, g_VmmCtx.LockFlags);

        Ret = pCmdHandler(pParamInOut);

        VMM_SPINLOCK_UNLOCK(&g_VmmCtx.Lock, g_VmmCtx.LockFlags);
    }
    else
    {
        VMM_MUTEX_LOCK(&g_VmmCtx.Mutex);

        Ret = pCmdHandler(pParamInOut);

        VMM_MUTEX_UNLOCK(&g_VmmCtx.Mutex);
    }

    return Ret;
}

SINT32 VMM_Core_Init(PFN_VMM_CALLBACK pfCallback)
{
    SINT32 Ret = VMM_SUCCESS;

    D_VMM_CHECK_PTR_RET(pfCallback, ERR_VMM_NULL_PTR);

    if (g_VmmCtx.IsInit == 0)
    {
        VMM_Osal_InitEvent(&g_VmmCtx.Event, 0);

        VMM_MUTEX_INIT(&g_VmmCtx.Mutex);
        VMM_SPINLOCK_INIT(&g_VmmCtx.Lock);

        Ret = VMM_Dbg_Initial();

        if (Ret != VMM_SUCCESS)
        {
            goto Error;
        }

        Ret = VMM_Msglist_Init();

        if (Ret != VMM_SUCCESS)
        {
            PRINT(PRN_FATAL, "%s,%d, MsgList Init Failed!\n", __func__, __LINE__);

            goto Error_0;
        }

        Ret = VMM_Memlist_Init();

        if (Ret != VMM_SUCCESS)
        {
            PRINT(PRN_FATAL, "%s,%d, MsgList Init Failed!\n", __func__, __LINE__);

            goto Error_1;
        }

        g_VmmCtx.StopThead = 0;

        if (OSAL_FP_create_task(&g_VmmCtx.hThread, "VMM_PROCESS", VMM_Thread_Process) != VMM_SUCCESS)
        {
            PRINT(PRN_FATAL, "%s create task %s failed!\n", __func__, "VMM_PROCESS");

            goto Error_2;
        }

        VMM_MUTEX_LOCK(&g_VmmCtx.Mutex);

        g_VmmCtx.IsInit = 1;
        g_VmmCtx.pfCallback = pfCallback;

        VMM_MUTEX_UNLOCK(&g_VmmCtx.Mutex);

        if (OSAL_FP_proc_create(VMM_PROC_NAME, VMM_Proc_Read, VMM_Proc_Write) != VMM_SUCCESS)
        {
            PRINT(PRN_FATAL, "%s create proc %s failed!\n", __func__, VMM_PROC_NAME);

            goto Error_3;
        }
    }

    return Ret;

Error_3:
    g_VmmCtx.StopThead = 1;

Error_2:
    VMM_Memlist_Deinit();

Error_1:
    VMM_Msglist_Deinit();

Error_0:

    if (g_VmmCtx.pDbgInfo)
    {
        OSAL_FP_free_virmem(g_VmmCtx.pDbgInfo);
        g_VmmCtx.pDbgInfo = NULL;
    }

Error:
    g_VmmCtx.IsInit = 0;

    return Ret;
}

SINT32 VMM_Core_Deinit(VOID)
{
    SINT32 Ret = VMM_OSAL_SUCCESS;
    Mem_Data_S MemData;
    SINT32 RecycleCnt = 0;

    OSAL_FP_memset(&MemData, 0, sizeof(Mem_Data_S));

    if (g_VmmCtx.IsInit)
    {
        g_VmmCtx.StopThead = 1;

        OSAL_FP_proc_destroy(VMM_PROC_NAME);

        while ((g_VmmCtx.ThreadStatus != THREAD_STATUS_EXIT) && (RecycleCnt < 50))
        {
            RecycleCnt++;
            msleep(1);
        }

        if (RecycleCnt == 50)
        {
            PRINT(PRN_ERROR, "%s,%d,Task stop timeout!! ThreadStatus = %d\n", __func__, __LINE__, g_VmmCtx.ThreadStatus);
        }

        VMM_Msglist_Deinit();

        do
        {
            Ret = VMM_Memlist_TakeOutNode(&MemData);

            if (Ret == VMM_OSAL_SUCCESS)
            {
                if (VMM_Ops_Release(&MemData.BufInfo) != MEM_OPS_SUCCESS)
                {
                    PRINT(PRN_ERROR, "%s,%d, want to release Mem(Addr = 0x%x, Size = %d, Name = '%s') failed!\n", __func__, __LINE__,
                          MemData.BufInfo.StartPhyAddr, MemData.BufInfo.Size, MemData.BufInfo.BufName);
                }
            }
        }
        while (Ret == VMM_OSAL_SUCCESS);

        VMM_Memlist_Deinit();

        VMM_Dbg_DeInitial();

        g_VmmCtx.pfCallback = NULL;
        g_VmmCtx.IsInit = 0;
    }

    return VMM_SUCCESS;
}

VOID *VMM_Core_GetCallBackFunc(VOID)
{
    VOID *pFunc = NULL;

    if (g_VmmCtx.IsInit)
    {
        pFunc = (VOID *)g_VmmCtx.pfCallback;
    }

    return pFunc;
}

#ifdef VCODEC_UT_ENABLE
EXPORT_SYMBOL(VMM_Core_GetCallBackFunc);
#endif

