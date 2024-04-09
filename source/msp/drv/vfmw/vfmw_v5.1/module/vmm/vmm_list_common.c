#include "vmm_list_common.h"

typedef struct
{
    struct list_head list;
    VOID *pVirAddr;
} List_BufRec_S;

static SINT32 Check_ListCfg(const VMM_List_Config_S *pListCfg)
{
    UINT32 ErrFlag = 0;

    D_VMM_CHECK_PTR_RET(pListCfg, ERR_LIST_NULL_PTR);

    ErrFlag |= (pListCfg->MaxExpansionFactor == 0);
    ErrFlag |= (pListCfg->NodeNum == 0);
    ErrFlag |= (pListCfg->PerNodeSize == 0);
    ErrFlag |= (pListCfg->MemAllocMode >= ALLOC_MODE_BUTT);
    ErrFlag |= (pListCfg->LockMode >= LOCK_MODE_BUTT);

    return (ErrFlag == 0) ? LIST_SUCCESS : LIST_FAILURE;

}

static VOID *List_AllocVirMem(VMM_ALLOC_MODE_E AllocMode, UINT32 Size)
{
    VOID *pVirMem = NULL;

    switch (AllocMode)
    {
        case ALLOC_MODE_VMALLOC:
            pVirMem = (VOID *)OSAL_FP_alloc_virmem(Size);
            break;

        case ALLOC_MODE_KMALLOC_ATOMIC:
            pVirMem = (VOID *)OSAL_FP_kmalloc_virmem(Size);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d, not support this alloc mode(%d),alloc size = %d\n", __func__, __LINE__, AllocMode, Size);
            break;
    }

    return pVirMem;
}

static VOID List_FreeVirMem(VMM_ALLOC_MODE_E AllocMode, VOID *pVirMem)
{
    switch (AllocMode)
    {
        case ALLOC_MODE_VMALLOC:
            OSAL_FP_free_virmem(pVirMem);
            break;

        case ALLOC_MODE_KMALLOC_ATOMIC:
            OSAL_FP_kfree_virmem(pVirMem);
            break;

        default:
            PRINT(PRN_ERROR, "%s,%d, not support this free mode(%d),free VirMem = %p\n", __func__, __LINE__, AllocMode, pVirMem);
            break;
    }

    return;
}

static VOID *List_TakeOutDataRec(VMM_List_S *pList)
{
    List_BufRec_S *pBufRec = NULL;
    VOID *pVirAddr = NULL;

    D_VMM_CHECK_PTR_RET(pList, NULL);

    LIST_LOCK(pList);

    if (!List_IsEmpty(pList, LIST_TYPE_INTERNAL))
    {
        pBufRec = list_first_entry(&pList->data, List_BufRec_S, list);
        pVirAddr = pBufRec->pVirAddr;
        OSAL_FP_list_del(&pBufRec->list);
    }

    LIST_UNLOCK(pList);

    if (pBufRec != NULL)
    {
        List_FreeVirMem(pList->Cfg.MemAllocMode, pBufRec);
    }

    return pVirAddr;
}

SINT32 List_ExpandLen(VMM_List_S *pList)
{
    VMM_List_Config_S *pListCfg = NULL;
    List_BufRec_S *pBufRec = NULL;
    VOID *pNode = NULL;
    struct list_head *pNew = NULL;
    UINT32 NodeNum = 0;

    D_VMM_CHECK_PTR_RET(pList, ERR_LIST_NULL_PTR);
    D_VMM_CHECK_PTR_RET(pList, ERR_LIST_NULL_PTR);

    pListCfg = &pList->Cfg;

    if (Check_ListCfg(pListCfg) != LIST_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s,%d,Check_ListCfg failed!\n", __func__, __LINE__);

        return ERR_LIST_INVALID_PARA;
    }

    if (pList->CurExpansionFactor >= pListCfg->MaxExpansionFactor)
    {
        PRINT(PRN_ERROR, "List(No.%d) CurExpansionFactor(%d) is >= MaxExpansionFactor(%d). Can not be expanded!\n",
              pListCfg->MarkNo, pList->CurExpansionFactor, pListCfg->MaxExpansionFactor);

        return ERR_LIST_FULL;
    }

    PRINT(PRN_DBG, "%s,%d,===> List(No.%d) CurExpansionFactor(%d), MaxExpansionFactor(%d), CurNum = %d\n",
          __func__, __LINE__, pListCfg->MarkNo, pList->CurExpansionFactor, pListCfg->MaxExpansionFactor, pList->CurNodeNum);

    /*alloc initial node buffer*/
    pNode = List_AllocVirMem(pListCfg->MemAllocMode, (pListCfg->PerNodeSize * pListCfg->NodeNum));

    if (!pNode)
    {
        PRINT(PRN_ERROR, "%s,%d,List(No.%d) alloc vir mem (size = %d)failed!\n", __func__, __LINE__, pListCfg->MarkNo, (pListCfg->PerNodeSize * pListCfg->NodeNum));

        return ERR_LIST_ALLOC_FAILED;
    }

    /*alloc data node buffer*/
    pBufRec = (List_BufRec_S *)List_AllocVirMem(pListCfg->MemAllocMode, sizeof(List_BufRec_S));

    if (!pBufRec)
    {
        PRINT(PRN_ERROR, "%s,%d,List(No.%d) alloc vir mem (size = %d)failed!\n", __func__, __LINE__, pListCfg->MarkNo, sizeof(List_BufRec_S));
        List_FreeVirMem(pListCfg->MemAllocMode, pNode);

        return ERR_LIST_ALLOC_FAILED;
    }

    OSAL_FP_memset(pNode, 0, (pListCfg->PerNodeSize * pListCfg->NodeNum));

    pBufRec->pVirAddr = pNode;

    LIST_LOCK(pList);

    OSAL_FP_list_add(&pBufRec->list, &pList->data);

    pList->CurExpansionFactor++;

    pList->CurNodeNum += pListCfg->NodeNum;

    for (NodeNum = pListCfg->NodeNum; NodeNum > 0; NodeNum--)
    {
        pNew  = (struct list_head *)pNode;

        OSAL_FP_list_add(pNew, &pList->free);

        pNode = (SINT8 *)pNode + pListCfg->PerNodeSize;
    }

    LIST_UNLOCK(pList);

    return LIST_SUCCESS;
}

SINT32  List_IsEmpty(VMM_List_S *pList, VMM_LIST_TYPE_E eType)
{
    struct list_head *pTargetList = NULL;

    D_VMM_CHECK_PTR_RET(pList, LIST_TRUE);

    switch (eType)
    {
        case LIST_TYPE_HEAD:
            pTargetList = &pList->head;
            break;

        case LIST_TYPE_FREE:
            pTargetList = &pList->free;
            break;

        case LIST_TYPE_INTERNAL:
            pTargetList = &pList->data;
            break;

        default:
            PRINT(PRN_ERROR, "eType '%d' is not support.\n", eType);
            break;
    }

    if (pTargetList == NULL)
    {
        return LIST_TRUE;
    }

    return OSAL_FP_list_is_empty(pTargetList);
}

VMM_List_S *List_Init(const VMM_List_Config_S *pListCfg)
{
    VMM_List_S *pList;

    if (Check_ListCfg(pListCfg) != LIST_SUCCESS)
    {
        PRINT(PRN_ERROR, "%s,%d,Check_ListCfg failed!\n", __func__, __LINE__);

        return NULL;
    }

    pList = (VMM_List_S *)List_AllocVirMem(pListCfg->MemAllocMode, sizeof(VMM_List_S));

    if (!pList)
    {
        PRINT(PRN_ERROR, "%s,%d,alloc vir mem (size = %d)failed!\n", __func__, __LINE__, sizeof(VMM_List_S));

        return NULL;
    }

    OSAL_FP_memset(pList, 0, sizeof(VMM_List_S));
    OSAL_FP_memcpy(&pList->Cfg, pListCfg, sizeof(VMM_List_Config_S));

    spin_lock_init(&pList->Lock);
    sema_init(&pList->Mutex, 1);

    INIT_LIST_HEAD(&pList->head);
    INIT_LIST_HEAD(&pList->free);
    INIT_LIST_HEAD(&pList->data);

    if (List_ExpandLen(pList) != LIST_SUCCESS)
    {
        List_FreeVirMem(pListCfg->MemAllocMode, pList);

        return NULL;
    }

    return pList;
}

VOID List_Deinit(VMM_List_S *pList)
{
    UINT32 TimeCnt = 0;
    VOID *pVirAddr = NULL;
    VMM_ALLOC_MODE_E MemAllocMode;

    D_VMM_CHECK_PTR(pList);

    MemAllocMode = pList->Cfg.MemAllocMode;

    do
    {
        pVirAddr = List_TakeOutDataRec(pList);

        if (pVirAddr != NULL)
        {
            List_FreeVirMem(MemAllocMode, pVirAddr);
        }
    }
    while ((pVirAddr != NULL) && (TimeCnt > pList->Cfg.MaxExpansionFactor));

    List_FreeVirMem(MemAllocMode, pList);

    return;
}

