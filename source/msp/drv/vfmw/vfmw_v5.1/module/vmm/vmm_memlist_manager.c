#include "vmm_memlist_manager.h"
#include "vmm_list_common.h"
#include "vfmw_osal_proc.h"

#define INIT_MEM_NODE_NUM      (1024)
#define MAX_MEM_DATA_BUF_NUM   (8)

VMM_PRIVATE VMM_List_S *g_pMemListCtx = NULL;

VMM_PRIVATE VOID Memlist_AddNodeAndSort(Mem_Node_S *pMemNode, struct list_head *pListHead)
{
    Mem_Node_S *pMemNodeCheck = NULL;
    struct list_head *pCurrent = &pMemNode->list;
    struct list_head *pCheck;
    struct list_head *pos;
    struct list_head *n;

    /*ordering rule: head->tail   Size large->small */
    if (VMM_Memlist_IsEmpty())
    {
        OSAL_FP_list_add(pCurrent, pListHead);
    }
    else
    {
        list_for_each_safe(pos, n, pListHead)
        {
            pMemNodeCheck = list_entry(pos, Mem_Node_S, list);
            pCheck = &pMemNodeCheck->list;

            if (pMemNode->Data.BufInfo.Size >= pMemNodeCheck->Data.BufInfo.Size)
            {
                /*current Node size larger than CheckNode, add current before CheckNode*/
                struct list_head *pLastlist = pCheck->prev;

                pCurrent->next = pCheck;
                pCurrent->prev = pLastlist;

                pCheck->prev = pCurrent;
                pLastlist->next = pCurrent;

                break;
            }
            else if (pCheck->next == pListHead)
            {
                /*already reach the list last Node, current Node size is smallest*/
                OSAL_FP_list_add_tail(pCurrent, pListHead);
            }
        }
    }

    return;
}

VMM_PRIVATE SINT32 Memlist_MoveFromFreeToHead(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;

    LIST_LOCK(g_pMemListCtx);

    pMemNode = list_first_entry(&g_pMemListCtx->free, Mem_Node_S, list);

    if (pMemNode != NULL)
    {
        OSAL_FP_list_del(&pMemNode->list);

        OSAL_FP_memcpy(&pMemNode->Data, pData, sizeof(Mem_Data_S));

        Memlist_AddNodeAndSort(pMemNode, &g_pMemListCtx->head);

        Ret = LIST_SUCCESS;
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

VMM_PRIVATE SINT32 Memlist_MoveFromHeadToFree(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;

    LIST_LOCK(g_pMemListCtx);

    pMemNode = list_first_entry(&g_pMemListCtx->head, Mem_Node_S, list);

    if (pMemNode != NULL)
    {
        OSAL_FP_list_del(&pMemNode->list);

        OSAL_FP_memcpy(pData, &pMemNode->Data, sizeof(Mem_Data_S));

        OSAL_FP_list_add_tail(&pMemNode->list, &g_pMemListCtx->free);

        Ret = LIST_SUCCESS;
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

#if 0
VMM_PRIVATE SINT32 Memlist_MoveFromHeadToFree(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;

    LIST_LOCK(g_pMemListCtx);

    pMemNode = list_first_entry(&g_pMemListCtx->head, Mem_Node_S, list);

    if (pMemNode != NULL)
    {
        OSAL_FP_list_del(&pMemNode->list);

        OSAL_FP_memcpy(pData, &pMemNode->Data, sizeof(Mem_Data_S));

        OSAL_FP_list_add_tail(&pMemNode->list, &g_pMemListCtx->head);

        Ret = LIST_SUCCESS;
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_TakeOutNode(Mem_Data_S *pData)  //the node which be taken out should be moved from head list to free list
{
    SINT32 Ret = LIST_FAILURE;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        return ERR_LIST_EMPTY;
    }

    Ret = Memlist_MoveFromHeadToFree(pData);

    return Ret;
}

#endif

VMM_PRIVATE SINT32 Check_Location(VMM_LOCATION_E Location)
{
    return (Location >= VMM_LOCATION_BUTT) ? LIST_FAILURE : LIST_SUCCESS;
}

VMM_PRIVATE SINT32 Check_Status(Node_Status_E Status)
{
    return (Status >= Node_Status_BUTT) ? LIST_FAILURE : LIST_SUCCESS;
}

VMM_PRIVATE VOID PrintErrorDetail_MemData(const Mem_Data_S *pData)
{
    SINT32 ErrFlag = 0;

    ErrFlag |= (pData->Status >= Node_Status_BUTT);
    ErrFlag |= (pData->Location >= VMM_LOCATION_BUTT);
    ErrFlag |= (pData->BufInfo.Map > 1);
    ErrFlag |= (pData->BufInfo.Cache > 1);
    ErrFlag |= (pData->BufInfo.SecFlag > 1);
    ErrFlag |= ((pData->BufInfo.StartPhyAddr == 0) || (pData->BufInfo.StartPhyAddr == 0xffffffff));
    ErrFlag |= (pData->BufInfo.Size == 0);
    ErrFlag |= (pData->BufInfo.MemType >= VMM_MEM_TYPE_BUTT);

    if (ErrFlag)
    {
        PRINT(PRN_ERROR, "%s,%d, Check ErrConfig:status(%d)>=%d, Location(%d)>=%d, Map(%d)>%d, Cache(%d)>%d, SecFlag(%d)>%d, StartPhyAddr = 0x%x, Size = %d, MemType(%d)>=%d\n", __func__, __LINE__,
              pData->Status, Node_Status_BUTT,
              pData->Location, VMM_LOCATION_BUTT,
              pData->BufInfo.Map, 1,
              pData->BufInfo.Cache, 1,
              pData->BufInfo.SecFlag, 1,
              pData->BufInfo.StartPhyAddr, pData->BufInfo.Size,
              pData->BufInfo.MemType, VMM_MEM_TYPE_BUTT
             );
    }

    if (((pData->Location == VMM_LOCATION_INSIDE) && (pData->RefCnt != 0))
        || ((pData->Location == VMM_LOCATION_OUTSIDE) && (pData->RefCnt == 0)))
    {
        PRINT(PRN_ERROR, "%s,%d, Error:Location = %d, RefCnt(%d) invalid!\n", __func__, __LINE__, pData->Location, pData->RefCnt);
    }

    if (pData->BufInfo.Map == 1)
    {
        if ((pData->BufInfo.pStartVirAddr == 0) || (pData->BufInfo.pStartVirAddr == (-1)))
        {
            PRINT(PRN_ERROR, "%s,%d, Error:Map = %d, pStartVirAddr(%llu) invalid!\n", __func__, __LINE__, pData->BufInfo.Map, pData->BufInfo.pStartVirAddr);
        }
    }
    else
    {
        if (pData->BufInfo.pStartVirAddr != 0)
        {
            PRINT(PRN_ERROR, "%s,%d, Error:Map = %d, pStartVirAddr(%llu) invalid!\n", __func__, __LINE__, pData->BufInfo.Map, pData->BufInfo.pStartVirAddr);
        }
    }

    if ((pData->BufInfo.Cache == 1) && (pData->BufInfo.Map != 1))
    {
        PRINT(PRN_ERROR, "%s,%d, Error:Cache = %d, Map(%llu) invalid!\n", __func__, __LINE__, pData->BufInfo.Cache, pData->BufInfo.Map);
    }
}

VMM_PRIVATE SINT32 Check_MemData(const Mem_Data_S *pData)
{
    SINT32 ErrFlag = 0;
    struct list_head *pos;
    struct list_head *n;
    Mem_Node_S *pMemNode = NULL;
    UADDR TargetPhyAddr = pData->BufInfo.StartPhyAddr;

    ErrFlag |= (pData->Status >= Node_Status_BUTT);
    ErrFlag |= (pData->Location >= VMM_LOCATION_BUTT);
    ErrFlag |= (pData->BufInfo.Map > 1);
    ErrFlag |= (pData->BufInfo.Cache > 1);
    ErrFlag |= (pData->BufInfo.SecFlag > 1);
    ErrFlag |= ((pData->BufInfo.StartPhyAddr == 0) || (pData->BufInfo.StartPhyAddr == 0xffffffff));
    ErrFlag |= (pData->BufInfo.Size == 0);
    ErrFlag |= (pData->BufInfo.MemType >= VMM_MEM_TYPE_BUTT);

    if (pData->Location == VMM_LOCATION_INSIDE)
    {
        ErrFlag |= (pData->RefCnt != 0);
    }

    if (pData->Location == VMM_LOCATION_OUTSIDE)
    {
        ErrFlag |= (pData->RefCnt == 0);

        if (pData->RefCnt != 1)
        {
            PRINT(PRN_IMP, "%s,%d, Location = %d, RefCnt = %d becareful!\n", __func__, __LINE__, pData->Location, pData->RefCnt);
        }
    }

    if (pData->BufInfo.Map == 1)
    {
        ErrFlag |= ((pData->BufInfo.pStartVirAddr == 0) || (pData->BufInfo.pStartVirAddr == (-1)));
    }
    else
    {
        ErrFlag |= (pData->BufInfo.pStartVirAddr != 0);
    }

    if (pData->BufInfo.Cache == 1)
    {
        ErrFlag |= (pData->BufInfo.Map != 1);
    }

    if (ErrFlag)
    {
        PrintErrorDetail_MemData(pData);

        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (VMM_Memlist_IsEmpty() != LIST_TRUE)
    {
        list_for_each_safe(pos, n, &g_pMemListCtx->head)
        {
            pMemNode = list_entry(pos, Mem_Node_S, list);

            if (TargetPhyAddr == pMemNode->Data.BufInfo.StartPhyAddr)
            {
                ErrFlag |= 1;
                PRINT(PRN_ERROR, "%s,%d, Curent Phyaddr 0x%x is already exist!\n", __func__, __LINE__, TargetPhyAddr);
                break;
            }
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return (ErrFlag == 0) ? LIST_SUCCESS : ERR_LIST_NODE_ALREADY_EXIST;
}

VMM_PRIVATE VOID GetDefault_MemListCfg(VMM_List_Config_S *pListCfg)
{
    OSAL_FP_memset(pListCfg, 0, sizeof(VMM_List_Config_S));

    pListCfg->MaxExpansionFactor = MAX_MEM_DATA_BUF_NUM;
    pListCfg->NodeNum            = INIT_MEM_NODE_NUM;
    pListCfg->PerNodeSize        = sizeof(Mem_Node_S);
    pListCfg->MarkNo             = 1;
    pListCfg->MemAllocMode       = ALLOC_MODE_KMALLOC_ATOMIC;
    pListCfg->LockMode           = LOCK_MODE_SPINLOCK;

    return;
}

VMM_PRIVATE SINT32 IsMemNodeCanBeRls(const Mem_Data_S *pData)
{
    return (pData->Status != Node_Status_InUse) && (pData->Location != VMM_LOCATION_OUTSIDE);
}

SINT32  VMM_Memlist_AddNode(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    Ret = Check_MemData(pData);

    if (Ret != LIST_SUCCESS)
    {
        return Ret;
    }

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_FREE))
    {
        Ret = List_ExpandLen(g_pMemListCtx);

        if (Ret != LIST_SUCCESS)
        {
            return ERR_LIST_FULL;
        }
    }

    Ret = Memlist_MoveFromFreeToHead(pData);

    return Ret;
}

SINT32  VMM_Memlist_SetSpecifiedNodeNoUse(VMM_RLS_BURST_S *pRlsBurst)
{
    Mem_Node_S *pMemNode = NULL;
    UINT64 TargetPrivID = 0;
    UINT64 CurPrivID    = 0;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pRlsBurst, ERR_LIST_NULL_PTR);

    TargetPrivID = (UINT64)pRlsBurst->PrivID;
    TargetPrivID &= pRlsBurst->PrivMask;

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return LIST_SUCCESS;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);

        CurPrivID = (UINT64)pMemNode->Data.BufInfo.PrivID;
        CurPrivID &= pRlsBurst->PrivMask;

        if (CurPrivID == TargetPrivID)
        {
            pMemNode->Data.Status = Node_Status_NoUse;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return LIST_SUCCESS;
}

SINT32  VMM_Memlist_IsEmpty(VOID)
{
    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    return List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD);
}

SINT32  VMM_Memlist_FindNodeByPhyaddr(UADDR TargetPhyAddr, Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    UADDR  PhyAddr;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        PhyAddr = pMemNode->Data.BufInfo.StartPhyAddr;

        if (PhyAddr == TargetPhyAddr)
        {
            OSAL_FP_memcpy(pData, &pMemNode->Data, sizeof(Mem_Data_S));
            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32 VMM_Memlist_UpdateBufRec(VMM_BUFFER_S *pBufRec)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    struct list_head *pos;
    struct list_head *n;
    VMM_BUFFER_S *pBufNode = NULL;
    UADDR  TargetPhyAddr;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pBufRec, ERR_LIST_NULL_PTR);

    TargetPhyAddr = pBufRec->StartPhyAddr;

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        pBufNode = &pMemNode->Data.BufInfo;

        if (pBufNode->StartPhyAddr == TargetPhyAddr)
        {
            pBufNode->Cache = pBufRec->Cache;
            pBufNode->Map   = pBufRec->Map;
            pBufNode->pStartVirAddr = pBufRec->pStartVirAddr;

            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_TakeOutNode(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        return ERR_LIST_EMPTY;
    }

    Ret = Memlist_MoveFromHeadToFree(pData);

    return Ret;
}

SINT32  VMM_Memlist_DeleteNodeByPhyaddr(UADDR TargetPhyAddr)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    UADDR  PhyAddr;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        PhyAddr = pMemNode->Data.BufInfo.StartPhyAddr;

        if (PhyAddr == TargetPhyAddr)
        {
            OSAL_FP_list_del(&pMemNode->list);
            OSAL_FP_list_add_tail(&pMemNode->list, &g_pMemListCtx->free);
            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_MarkLocation(UADDR TargetPhyAddr, VMM_LOCATION_E Location)
{
    SINT32 Ret = ERR_LIST_NODE_NOT_EXIST;
    Mem_Node_S *pMemNode = NULL;
    UADDR  PhyAddr;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        PRINT(PRN_ERROR, "%s,%d, Phyaddr = 0x%x invalid!\n", __func__, __LINE__, TargetPhyAddr);
        return ERR_LIST_INVALID_PARA;
    }

    if (Check_Location(Location) != HI_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s,%d, location = %d limit exceeded!\n", __func__, __LINE__, Location);
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        PhyAddr = pMemNode->Data.BufInfo.StartPhyAddr;

        if (PhyAddr == TargetPhyAddr)
        {
            if (Location == VMM_LOCATION_OUTSIDE)
            {
                pMemNode->Data.RefCnt++;
                pMemNode->Data.Location = VMM_LOCATION_OUTSIDE;
            }
            else
            {
                if (pMemNode->Data.RefCnt == 0)
                {
                    PRINT(PRN_IMP, "%s,%d, MemNode Phyaddr = 0x%x, already inside!", __func__, __LINE__, PhyAddr);
                }

                if (pMemNode->Data.RefCnt > 0)
                {
                    pMemNode->Data.RefCnt--;
                }

                if (pMemNode->Data.RefCnt == 0)
                {
                    pMemNode->Data.Location = VMM_LOCATION_INSIDE;
                }
            }

            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_MarkStatus(UADDR TargetPhyAddr, Node_Status_E Status)
{
    SINT32 Ret = ERR_LIST_NODE_NOT_EXIST;
    Mem_Node_S *pMemNode = NULL;
    UADDR  PhyAddr;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        PRINT(PRN_ERROR, "%s,%d, Phyaddr = 0x%x invalid!\n", __func__, __LINE__, TargetPhyAddr);
        return ERR_LIST_INVALID_PARA;
    }

    if (Check_Status(Status) != HI_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s,%d, Status = 0x%x limit exceeded!\n", __func__, __LINE__, Status);
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        PhyAddr = pMemNode->Data.BufInfo.StartPhyAddr;

        if (PhyAddr == TargetPhyAddr)
        {
            VMM_ASSERT(pMemNode->Data.Status != Status);

            pMemNode->Data.Status = Status;
            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_PrintNodeStatus(VOID)
{
    Mem_Node_S *pMemNode = NULL;
    Mem_Data_S *pData = NULL;
    struct list_head *pos;
    struct list_head *n;
    SINT8 StatusTab  [Node_Status_BUTT + 1 ][8]  = {{"Idle"}, {"InUse"}, {"NoUse"}, {"Unknown"}};
    SINT8 LocationTab[VMM_LOCATION_BUTT + 1][8]  = {{"Inside"}, {"Outside"}, {"Unknown"}};
    SINT8 MemTypeTab [VMM_MEM_TYPE_BUTT + 1][10] = {{"SysAdapt"}, {"ProceMMZ"}, {"PerAlloc"}, {"ExtConfig"}, {"Unknown"}};

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return LIST_SUCCESS;
    }

    PRINT(PRN_ALWS, "-------------------------------------------------- MemNode Info ---------------------------------------------------------- \n");
    PRINT(PRN_ALWS, "\tPrivID\t   \tName\t \tPhyaddr\t \tViraddr\t     Size(KB) Cache/Map/Sec   Type      Status  Location(RefCnt)  Time(us)\n");
    PRINT(PRN_ALWS, "-------------------------------------------------------------------------------------------------------------------------- \n");
    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        pData = &pMemNode->Data;
        PRINT(PRN_ALWS, "0x%-16llx %-16s   0x%-8x   0x%-16lx %-6d    %d  %d  %d    %-10s %-8s %-8s(%-2d) %-8d\n",
              pData->BufInfo.PrivID, pData->BufInfo.BufName, pData->BufInfo.StartPhyAddr, pData->BufInfo.pStartVirAddr, pData->BufInfo.Size / 1024,
              pData->BufInfo.Cache, pData->BufInfo.Map, pData->BufInfo.SecFlag,
              MemTypeTab[(pData->BufInfo.MemType > VMM_MEM_TYPE_BUTT) ? VMM_MEM_TYPE_BUTT : pData->BufInfo.MemType],
              StatusTab[(pData->Status > Node_Status_BUTT) ? Node_Status_BUTT : pData->Status],
              LocationTab[(pData->Location > VMM_LOCATION_BUTT) ? VMM_LOCATION_BUTT : pData->Location],
              pData->RefCnt,
              pData->DbgInfo.AllocTimeConsumeInUs);
    }

    LIST_UNLOCK(g_pMemListCtx);

    return LIST_SUCCESS;
}

SINT32  VMM_Memlist_ReadProc(VOID *p)
{
    Mem_Node_S *pMemNode = NULL;
    Mem_Data_S *pData = NULL;
    struct list_head *pos;
    struct list_head *n;
    SINT8 StatusTab  [Node_Status_BUTT + 1 ][8]  = {{"Idle"}, {"InUse"}, {"NoUse"}, {"Unknown"}};
    SINT8 LocationTab[VMM_LOCATION_BUTT + 1][8]  = {{"Inside"}, {"Outside"}, {"Unknown"}};
    SINT8 MemTypeTab [VMM_MEM_TYPE_BUTT + 1][10] = {{"SysAdapt"}, {"ProceMMZ"}, {"PerAlloc"}, {"ExtConfig"}, {"Unknown"}};

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    //statistics info
    PROC_PRINT(p, "================================================= MemList Status ========================================================= \n");
    PROC_PRINT(p, "CurNodeNum                : %d\n", g_pMemListCtx->CurNodeNum);
    PROC_PRINT(p, "PerNodeSize               : %d (B)\n", g_pMemListCtx->Cfg.PerNodeSize);
    PROC_PRINT(p, "ExpansionFactor(Cur/Max)  : %d/%d\n", g_pMemListCtx->CurExpansionFactor, g_pMemListCtx->Cfg.MaxExpansionFactor);

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return LIST_SUCCESS;
    }

    PROC_PRINT(p, "-------------------------------------------------- MemNode Info ---------------------------------------------------------- \n");
    PROC_PRINT(p, "\tPrivID\t   \tName\t \tPhyaddr\t \tViraddr\t     Size(KB) Cache/Map/Sec   Type      Status  Location(RefCnt)  Time(us)\n");
    PROC_PRINT(p, "-------------------------------------------------------------------------------------------------------------------------- \n");
    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        pData = &pMemNode->Data;
        PROC_PRINT(p, "0x%-16llx %-16s   0x%-8x   0x%-16lx %-6d    %d  %d  %d    %-10s %-8s %-8s(%-2d) %-8d\n",
                   pData->BufInfo.PrivID, pData->BufInfo.BufName, pData->BufInfo.StartPhyAddr, pData->BufInfo.pStartVirAddr, pData->BufInfo.Size / 1024,
                   pData->BufInfo.Cache, pData->BufInfo.Map, pData->BufInfo.SecFlag,
                   MemTypeTab[(pData->BufInfo.MemType > VMM_MEM_TYPE_BUTT) ? VMM_MEM_TYPE_BUTT : pData->BufInfo.MemType],
                   StatusTab[(pData->Status > Node_Status_BUTT) ? Node_Status_BUTT : pData->Status],
                   LocationTab[(pData->Location > VMM_LOCATION_BUTT) ? VMM_LOCATION_BUTT : pData->Location],
                   pData->RefCnt,
                   pData->DbgInfo.AllocTimeConsumeInUs);
    }

    LIST_UNLOCK(g_pMemListCtx);

    return LIST_SUCCESS;
}

SINT32  VMM_Memlist_FindOneNodeCanBeRls(Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);

        if (IsMemNodeCanBeRls(&pMemNode->Data) == VMM_TRUE)
        {
            //PRINT(PRN_ALWS, "%s, %d, pMemNode->Data.BufInfo.StartPhyAddr = 0x%x\n", __func__, __LINE__, pMemNode->Data.BufInfo.StartPhyAddr);
            OSAL_FP_memcpy(pData, &pMemNode->Data, sizeof(Mem_Data_S));
            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_TakeOutOneNodeCanBeRls(VMM_RLS_BURST_S *pRlsBurst, Mem_Data_S *pData)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    struct list_head *pos;
    struct list_head *n;
    UINT64 TargetPrivID = 0;
    UINT64 CurPrivID    = 0;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);
    D_VMM_CHECK_PTR_RET(pData, ERR_LIST_NULL_PTR);

    TargetPrivID = (UINT64)pRlsBurst->PrivID;
    TargetPrivID &= pRlsBurst->PrivMask;

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);

        CurPrivID = (UINT64)pMemNode->Data.BufInfo.PrivID;
        CurPrivID &= pRlsBurst->PrivMask;

        if ((IsMemNodeCanBeRls(&pMemNode->Data) == VMM_TRUE) && (CurPrivID == TargetPrivID))
        {
            //PRINT(PRN_ALWS, "%s, %d, pMemNode->Data.BufInfo.StartPhyAddr = 0x%x\n", __func__, __LINE__, pMemNode->Data.BufInfo.StartPhyAddr);
            OSAL_FP_memcpy(pData, &pMemNode->Data, sizeof(Mem_Data_S));

            OSAL_FP_list_del(&pMemNode->list);
            OSAL_FP_list_add_tail(&pMemNode->list, &g_pMemListCtx->free);

            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_IsOneNodeCanBeRls(UADDR TargetPhyAddr)
{
    SINT32 Ret = LIST_FAILURE;
    Mem_Node_S *pMemNode = NULL;
    UADDR  PhyAddr;
    struct list_head *pos;
    struct list_head *n;

    D_VMM_CHECK_PTR_RET(g_pMemListCtx, ERR_LIST_NOT_INIT);

    if (TargetPhyAddr == 0 || TargetPhyAddr == 0xffffffff)
    {
        return ERR_LIST_INVALID_PARA;
    }

    LIST_LOCK(g_pMemListCtx);

    if (List_IsEmpty(g_pMemListCtx, LIST_TYPE_HEAD))
    {
        LIST_UNLOCK(g_pMemListCtx);

        return ERR_LIST_EMPTY;
    }

    list_for_each_safe(pos, n, &g_pMemListCtx->head)
    {
        pMemNode = list_entry(pos, Mem_Node_S, list);
        PhyAddr = pMemNode->Data.BufInfo.StartPhyAddr;

        if ((PhyAddr == TargetPhyAddr) && (IsMemNodeCanBeRls(&pMemNode->Data)))
        {
            //PRINT(PRN_ALWS, "%s, %d, PhyAddr = 0x%x\n", __func__, __LINE__, PhyAddr);
            Ret = LIST_SUCCESS;

            break;
        }
    }

    LIST_UNLOCK(g_pMemListCtx);

    return Ret;
}

SINT32  VMM_Memlist_Init(VOID)
{
    VMM_List_S *pMemListCtx;
    VMM_List_Config_S MemListCfg;

    GetDefault_MemListCfg(&MemListCfg);

    if (g_pMemListCtx == NULL)
    {
        pMemListCtx = List_Init(&MemListCfg);

        if (!pMemListCtx)
        {
            return ERR_LIST_INIT_FAILED;
        }

        g_pMemListCtx = pMemListCtx;
    }

    return LIST_SUCCESS;
}

VOID  VMM_Memlist_Deinit(VOID)
{
    D_VMM_CHECK_PTR(g_pMemListCtx);

    List_Deinit(g_pMemListCtx);

    g_pMemListCtx = NULL;

    return;
}

#ifdef VCODEC_UT_ENABLE
EXPORT_SYMBOL(g_pMemListCtx);
EXPORT_SYMBOL(VMM_Memlist_AddNode);
EXPORT_SYMBOL(VMM_Memlist_FindNodeByPhyaddr);
EXPORT_SYMBOL(VMM_Memlist_DeleteNodeByPhyaddr);
EXPORT_SYMBOL(VMM_Memlist_MarkLocation);
EXPORT_SYMBOL(VMM_Memlist_MarkStatus);
EXPORT_SYMBOL(VMM_Memlist_IsEmpty);
EXPORT_SYMBOL(VMM_Memlist_PrintNodeStatus);
EXPORT_SYMBOL(VMM_Memlist_FindOneNodeCanBeRls);
EXPORT_SYMBOL(VMM_Memlist_IsOneNodeCanBeRls);
EXPORT_SYMBOL(VMM_Memlist_SetSpecifiedNodeNoUse);
EXPORT_SYMBOL(VMM_Memlist_TakeOutOneNodeCanBeRls);
EXPORT_SYMBOL(VMM_Memlist_TakeOutNode);
EXPORT_SYMBOL(VMM_Memlist_UpdateBufRec);
EXPORT_SYMBOL(VMM_Memlist_Init);
EXPORT_SYMBOL(VMM_Memlist_Deinit);
#endif
