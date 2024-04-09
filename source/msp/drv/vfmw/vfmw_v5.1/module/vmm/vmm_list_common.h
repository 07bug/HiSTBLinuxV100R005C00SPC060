#ifndef __VMM_LIST_COMMON_H__
#define __VMM_LIST_COMMON_H__

#include "vmm.h"
#include "vmm_osal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIST_SUCCESS                     (SINT32)(0)
#define LIST_FAILURE                     (SINT32)(0xFFFFFFFF)
#define ERR_LIST_ALLOC_FAILED            (SINT32)(0xFF010000)
#define ERR_LIST_INIT_FAILED             (SINT32)(0xFF010001)
#define ERR_LIST_INVALID_PARA            (SINT32)(0xFF010002)
#define ERR_LIST_NULL_PTR                (SINT32)(0xFF010003)
#define ERR_LIST_NOT_SUPPORT             (SINT32)(0xFF010004)
#define ERR_LIST_FULL                    (SINT32)(0xFF010005)
#define ERR_LIST_EMPTY                   (SINT32)(0xFF010006)
#define ERR_LIST_NOT_INIT                (SINT32)(0xFF010007)
#define ERR_LIST_NODE_ALREADY_EXIST      (SINT32)(0xFF010008)
#define ERR_LIST_LOCATION_CONFLICT       (SINT32)(0xFF010009)
#define ERR_LIST_NODE_NOT_EXIST          (SINT32)(0xFF01000A)

#define LIST_TRUE                        (SINT32)(1)
#define LIST_FALSE                       (SINT32)(0)

#define LIST_LOCK(pList)                                               \
    do                                                                 \
    {                                                                  \
        if (pList->Cfg.LockMode == LOCK_MODE_MUTEX)                    \
        {                                                              \
            SINT32 Ret;                                                \
            Ret = down_interruptible(&pList->Mutex);                   \
        }                                                              \
        else if (pList->Cfg.LockMode == LOCK_MODE_SPINLOCK)            \
        {                                                              \
            spin_lock_irqsave(&pList->Lock, pList->LockFlags);         \
        }                                                              \
    }while(0)

#define LIST_UNLOCK(pList)                                             \
    do                                                                 \
    {                                                                  \
        if (pList->Cfg.LockMode == LOCK_MODE_MUTEX)                    \
        {                                                              \
            (VOID)up(&pList->Mutex);                                   \
        }                                                              \
        else if (pList->Cfg.LockMode == LOCK_MODE_SPINLOCK)            \
        {                                                              \
            spin_unlock_irqrestore(&pList->Lock, pList->LockFlags);    \
        }                                                              \
    }while(0)

typedef enum
{
    LIST_TYPE_HEAD,
    LIST_TYPE_FREE,
    LIST_TYPE_INTERNAL,
    LIST_TYPE_BUTT
} VMM_LIST_TYPE_E;

typedef enum
{
    ALLOC_MODE_VMALLOC,
    ALLOC_MODE_KMALLOC_ATOMIC,
    ALLOC_MODE_BUTT
} VMM_ALLOC_MODE_E;

typedef enum
{
    LOCK_MODE_MUTEX,
    LOCK_MODE_SPINLOCK,
    LOCK_MODE_BUTT
} VMM_LOCK_MODE_E;

typedef struct
{
    UINT32 MaxExpansionFactor;
    UINT32 NodeNum;
    UINT32 PerNodeSize;
    UINT32 MarkNo;              //priv reserve

    VMM_ALLOC_MODE_E MemAllocMode;
    VMM_LOCK_MODE_E  LockMode;
} VMM_List_Config_S;

typedef struct
{
    VMM_List_Config_S Cfg;
    UINT32 CurNodeNum;
    UINT32 CurExpansionFactor;

    struct list_head data;
    struct list_head head;
    struct list_head free;

    spinlock_t       Lock;
    unsigned long    LockFlags;
    struct semaphore Mutex;
} VMM_List_S;

VMM_List_S *List_Init(const VMM_List_Config_S *pListCfg);

VOID List_Deinit(VMM_List_S *pList);

SINT32 List_IsEmpty(VMM_List_S *pList, VMM_LIST_TYPE_E eType);

SINT32 List_ExpandLen(VMM_List_S *pList);

#ifdef __cplusplus
}
#endif

#endif  // __VMM_LIST_COMMON_H__
