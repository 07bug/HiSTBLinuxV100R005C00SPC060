#include "vmm_msglist_manager.h"
#include "vmm_list_common.h"
#include "vfmw_osal_proc.h"
#include "vfmw_osal_ext.h"

#define INIT_NODE_NUM      (200)
#define MAX_DATA_BUF_NUM   (5)

VMM_PRIVATE VMM_List_S *g_pMsgListCtx = NULL;

//SINT32  VMM_Msglist_DeleteNode(const VMM_CMD_BLK_TYPE_E CmdID, Msg_Node_S *pNode)
//SINT32  VMM_Msglist_SetPriorityPolicy()   //default

VMM_PRIVATE SINT32 Msglist_MoveFromFreeToHead(Msg_Data_S *pData, VMM_CMD_PRIO_E Proir)
{
    SINT32 Ret = LIST_FAILURE;
    Msg_Node_S *pMsgNode = NULL;

    LIST_LOCK(g_pMsgListCtx);

    pMsgNode = list_first_entry(&g_pMsgListCtx->free, Msg_Node_S, list);

    if (pMsgNode != NULL)
    {
        OSAL_FP_list_del(&pMsgNode->list);

        OSAL_FP_memcpy(&pMsgNode->Data, pData, sizeof(Msg_Data_S));

        if (Proir == VMM_CMD_PRIO_MAX)
        {
            OSAL_FP_list_add(&pMsgNode->list, &g_pMsgListCtx->head);
        }
        else
        {
            OSAL_FP_list_add_tail(&pMsgNode->list, &g_pMsgListCtx->head);
        }

        Ret = LIST_SUCCESS;
    }

    LIST_UNLOCK(g_pMsgListCtx);

    return Ret;
}

VMM_PRIVATE SINT32 Msglist_MoveFromHeadToFree(Msg_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Msg_Node_S *pMsgNode = NULL;

    LIST_LOCK(g_pMsgListCtx);

    pMsgNode = list_first_entry(&g_pMsgListCtx->head, Msg_Node_S, list);

    if (pMsgNode != NULL)
    {
        OSAL_FP_list_del(&pMsgNode->list);

        OSAL_FP_memcpy(pData, &pMsgNode->Data, sizeof(Msg_Data_S));

        OSAL_FP_list_add_tail(&pMsgNode->list, &g_pMsgListCtx->free);

        Ret = LIST_SUCCESS;
    }

    LIST_UNLOCK(g_pMsgListCtx);

    return Ret;
}

VMM_PRIVATE VOID PrintErrorDetail_MsgData(Msg_Data_S *pData)
{
    SINT64 PrivID = 0xffffffff;
    VMM_RLS_BURST_S *pRlsBurst = NULL;
    VMM_BUFFER_S *pBufRec = NULL;

    switch (pData->CmdID)
    {
        case VMM_CMD_ReleaseBurst:
        {
            pRlsBurst = &pData->Param.RlsBurst;
            PrivID = pRlsBurst->PrivID;

            PRINT(PRN_ERROR, "%s,%d, ERROR: CurCmd = ReleaseBurst, PrivMask = %d is invalid!\n", __func__, __LINE__, pRlsBurst->PrivMask);
        }
        break;

        case VMM_CMD_Alloc:
        {
            pBufRec = &pData->Param.BufRec;
            PrivID = pBufRec->PrivID;

            PRINT(PRN_ERROR, "%s,%d, ERROR: MemType(%d) should < %d,Cache(%d) should < 2, Map(%d) should < 2, SecFlag(%d) should < 2, Size(%d) should != 0\n", __func__, __LINE__,
                  pBufRec->MemType, VMM_MEM_TYPE_BUTT, pBufRec->Cache, pBufRec->Map, pBufRec->SecFlag, pBufRec->Size);
        }
        break;

        case VMM_CMD_Release:
        {
            pBufRec = &pData->Param.BufRec;
            PrivID = pBufRec->PrivID;

            PRINT(PRN_ERROR, "%s,%d, ERROR: MemType(%d) should < %d,Cache(%d) should < 2, Map(%d) should < 2, SecFlag(%d) should < 2, Size(%d) should != 0\n", __func__, __LINE__,
                  pBufRec->MemType, VMM_MEM_TYPE_BUTT, pBufRec->Cache, pBufRec->Map, pBufRec->SecFlag, pBufRec->Size);
            PRINT(PRN_ERROR, "              Current StartPhyAddr(0x%x) pStartVirAddr(0x%llx)\n", pBufRec->StartPhyAddr, pBufRec->pStartVirAddr);

        }
        break;

        default:
            PRINT(PRN_ERROR, "Unknow Command ID %d\n", pData->CmdID);
            break;
    }
}

VMM_PRIVATE SINT32 MsgDateCheck(Msg_Data_S *pData)
{
    SINT64 PrivID = 0xffffffff;
    VMM_RLS_BURST_S *pRlsBurst = NULL;
    VMM_BUFFER_S *pBufRec = NULL;
    SINT32 ErrFlag = 0;

    switch (pData->CmdID)
    {
        case VMM_CMD_ReleaseBurst:
        {
            pRlsBurst = &pData->Param.RlsBurst;
            PrivID = pRlsBurst->PrivID;

            ErrFlag |= (pRlsBurst->PrivMask == 0);
        }
        break;

        case VMM_CMD_Alloc:
        {
            pBufRec = &pData->Param.BufRec;
            PrivID = pBufRec->PrivID;

            ErrFlag |= (pBufRec->MemType   >= VMM_MEM_TYPE_BUTT);
            ErrFlag |= (pBufRec->Cache     >= 2);
            ErrFlag |= (pBufRec->Map       >= 2);
            ErrFlag |= (pBufRec->SecFlag   >= 2);
            ErrFlag |= (pBufRec->Size      == 0);

            if (pBufRec->Cache != 0)
            {
                ErrFlag |= (pBufRec->Map == 0);
            }
        }
        break;

        case VMM_CMD_Release:
        {
            pBufRec = &pData->Param.BufRec;
            PrivID = pBufRec->PrivID;

            ErrFlag |= (pBufRec->MemType   >= VMM_MEM_TYPE_BUTT);
            ErrFlag |= (pBufRec->Cache     >= 2);
            ErrFlag |= (pBufRec->Map       >= 2);
            ErrFlag |= (pBufRec->SecFlag   >= 2);
            ErrFlag |= (pBufRec->Size      == 0);
            ErrFlag |= (pBufRec->StartPhyAddr == 0) || (pBufRec->StartPhyAddr == 0xffffffff);

            if (pBufRec->Map != 0)
            {
                ErrFlag |= (pBufRec->pStartVirAddr == 0) || (pBufRec->pStartVirAddr == (-1));
            }
            else
            {
                ErrFlag |= (pBufRec->pStartVirAddr != 0) && (pBufRec->StartPhyAddr != 0xffffffff);
            }

            if (pBufRec->Cache != 0)
            {
                ErrFlag |= (pBufRec->Map == 0);
            }
        }
        break;

        default:
            PRINT(PRN_ERROR, "Unknow Command ID %d\n", pData->CmdID);
            break;
    }

    if (PrivID != pData->PrivID)
    {
        ErrFlag |= (PrivID != pData->PrivID);
        PRINT(PRN_ERROR, "%s,%d, MsgData PrivID conflict!(%d,%d)\n", PrivID, pData->PrivID);
    }

    if (ErrFlag != 0)
    {
        PrintErrorDetail_MsgData(pData);

        return LIST_FAILURE;
    }

    return LIST_SUCCESS;
}

VMM_PRIVATE VOID GetDefault_MsgListCfg(VMM_List_Config_S *pListCfg)
{
    OSAL_FP_memset(pListCfg, 0, sizeof(VMM_List_Config_S));

    pListCfg->MaxExpansionFactor = MAX_DATA_BUF_NUM;
    pListCfg->NodeNum            = INIT_NODE_NUM;
    pListCfg->PerNodeSize        = sizeof(Msg_Node_S);
    pListCfg->MarkNo             = 0;
    pListCfg->MemAllocMode       = ALLOC_MODE_KMALLOC_ATOMIC;
    pListCfg->LockMode           = LOCK_MODE_SPINLOCK;

    return;
}

VMM_PRIVATE VOID CheckAndDeleteNode(UINT64 TargetPrivID, Msg_Delete_S *pMsgDelete, Msg_Node_S *pMsgNode)
{
    UINT64 CurPrivID    = 0;
    UINT32 DeleteFlag   = 1;

    CurPrivID = (UINT64)pMsgNode->Data.PrivID;
    CurPrivID &= pMsgDelete->PrivMask;

    if (pMsgDelete->PrivIDValid)
    {
        DeleteFlag &= (CurPrivID == TargetPrivID);
    }

    if (pMsgDelete->CmdValid)
    {
        DeleteFlag &= (pMsgNode->Data.CmdID == pMsgDelete->CmdID);
    }

    if (DeleteFlag)
    {
        OSAL_FP_list_del(&pMsgNode->list);
        OSAL_FP_list_add_tail(&pMsgNode->list, &g_pMsgListCtx->free);
    }

    return;
}

SINT32  VMM_Msglist_ReadProc(VOID *p)
{
    Msg_Node_S *pMsgNode = NULL;
    Msg_Data_S *pData = NULL;
    struct list_head *pos;
    struct list_head *n;
    SINT8 MsgCmdTab [VMM_CMD_TYPE_BUTT + 1][16] = {{"Alloc"}, {"Release"}, {"ReleaseBurst"}, {"Unknown"}};

    D_VMM_CHECK_PTR_RET(g_pMsgListCtx, ERR_LIST_NOT_INIT);

    //statistics info
    PROC_PRINT(p, "================================================= MsgList Status ========================================================= \n");
    PROC_PRINT(p, "CurNodeNum                : %d\n", g_pMsgListCtx->CurNodeNum);
    PROC_PRINT(p, "PerNodeSize               : %d (B)\n", g_pMsgListCtx->Cfg.PerNodeSize);
    PROC_PRINT(p, "ExpansionFactor(Cur/Max)  : %d/%d\n", g_pMsgListCtx->CurExpansionFactor, g_pMsgListCtx->Cfg.MaxExpansionFactor);

    LIST_LOCK(g_pMsgListCtx);

    if (List_IsEmpty(g_pMsgListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMsgListCtx);

        return LIST_SUCCESS;
    }

    PROC_PRINT(p, "------------------------------------------------- MsgNode Info ----------------------------------------------------------- \n");
    PROC_PRINT(p, "\tPrivID\t    CmdID\t\n");
    PROC_PRINT(p, "-------------------------------------------------------------------------------------------------------------------------- \n");

    list_for_each_safe(pos, n, &g_pMsgListCtx->head)
    {
        pMsgNode = list_entry(pos, Msg_Node_S, list);
        pData = &pMsgNode->Data;

        PROC_PRINT(p, "0x%-16llx %-16s \n", pData->PrivID, MsgCmdTab[pData->CmdID]);
    }

    LIST_UNLOCK(g_pMsgListCtx);

    return LIST_SUCCESS;
}


SINT32  VMM_Msglist_AddNode(Msg_Data_S *pData, VMM_CMD_PRIO_E Proir)
{
    SINT32 Ret = LIST_FAILURE;

    D_VMM_CHECK_PTR_RET(g_pMsgListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    //PRINT(PRN_ALWS, "%s, %d\n", __func__, __LINE__);

    if (Proir >= VMM_CMD_PRIO_BUTT)
    {
        PRINT(PRN_ERROR, "%s,%d, Proir not support!\n", __func__, __LINE__);
        return ERR_LIST_INVALID_PARA;
    }

    if (MsgDateCheck(pData) != LIST_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s CmdID %d MsgDateCheck failed.\n", __func__, pData->CmdID);
        return ERR_LIST_INVALID_PARA;
    }

    if (List_IsEmpty(g_pMsgListCtx, LIST_TYPE_FREE))
    {
        Ret = List_ExpandLen(g_pMsgListCtx);

        if (Ret != LIST_SUCCESS)
        {
            return ERR_LIST_FULL;
        }
    }

    Ret = Msglist_MoveFromFreeToHead(pData, Proir);

    return Ret;
}

SINT32  VMM_Msglist_TakeOutNode(Msg_Data_S *pData)  //the node which be taken out should be moved from head list to free list
{
    SINT32 Ret = LIST_FAILURE;

    D_VMM_CHECK_PTR_RET(g_pMsgListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    if (List_IsEmpty(g_pMsgListCtx, LIST_TYPE_HEAD))
    {
        return ERR_LIST_EMPTY;
    }

    Ret = Msglist_MoveFromHeadToFree(pData);

    return Ret;
}

SINT32  VMM_Msglist_DeleteSpecifiedNode(Msg_Delete_S *pMsgDelete)
{
    Msg_Node_S *pMsgNode = NULL;
    UINT64 TargetPrivID = 0;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMsgListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pMsgDelete, ERR_LIST_NULL_PTR);

    VMM_ASSERT((pMsgDelete->PrivIDValid == 1) || (pMsgDelete->CmdValid == 1));

    TargetPrivID = (UINT64)pMsgDelete->PrivID;
    TargetPrivID &= pMsgDelete->PrivMask;

    LIST_LOCK(g_pMsgListCtx);

    if (List_IsEmpty(g_pMsgListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMsgListCtx);

        return LIST_SUCCESS;
    }

    list_for_each_safe(pos, n, &g_pMsgListCtx->head)
    {
        pMsgNode = list_entry(pos, Msg_Node_S, list);

        CheckAndDeleteNode(TargetPrivID, pMsgDelete, pMsgNode);
    }

    LIST_UNLOCK(g_pMsgListCtx);

    return LIST_SUCCESS;
}

SINT32  VMM_Msglist_IsEmpty(VOID)
{
    D_VMM_CHECK_PTR_RET(g_pMsgListCtx, ERR_LIST_NOT_INIT);

    return List_IsEmpty(g_pMsgListCtx, LIST_TYPE_HEAD);
}

SINT32 VMM_Msglist_Init(VOID)
{
    VMM_List_S *pMsgListCtx;
    VMM_List_Config_S MsgListCfg;

    GetDefault_MsgListCfg(&MsgListCfg);

    if (g_pMsgListCtx == NULL)
    {
        pMsgListCtx = List_Init(&MsgListCfg);

        if (!pMsgListCtx)
        {
            return ERR_LIST_INIT_FAILED;
        }

        g_pMsgListCtx = pMsgListCtx;
    }

    return LIST_SUCCESS;
}

VOID  VMM_Msglist_Deinit(VOID)
{
    D_VMM_CHECK_PTR(g_pMsgListCtx);

    List_Deinit(g_pMsgListCtx);

    g_pMsgListCtx = NULL;

    return;
}

#ifdef VCODEC_UT_ENABLE
EXPORT_SYMBOL(g_pMsgListCtx);
EXPORT_SYMBOL(VMM_Msglist_AddNode);
EXPORT_SYMBOL(VMM_Msglist_TakeOutNode);
EXPORT_SYMBOL(VMM_Msglist_DeleteSpecifiedNode);
EXPORT_SYMBOL(VMM_Msglist_IsEmpty);
EXPORT_SYMBOL(VMM_Msglist_Init);
EXPORT_SYMBOL(VMM_Msglist_Deinit);
#endif

