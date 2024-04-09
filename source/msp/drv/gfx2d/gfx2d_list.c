/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : gfx2d_list.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                  Author                Modification
2018/01/01            sdk                   Created file
**************************************************************************************************/

/*********************************add include here************************************************/
#include <linux/list.h>
#include <linux/spinlock.h>

#include "hi_kernel_adapt.h"
#include "hi_gfx_sys_k.h"
#include "hi_gfx2d_type.h"
#include "hi_gfx2d_errcode.h"
#include "hi_gfx_comm_k.h"
#include "gfx2d_hal.h"
#include "gfx2d_mem.h"
#include "gfx2d_config.h"
#include "gfx2d_fence.h"
#include "gfx2d_list.h"
#include "gfx2d_checkpara.h"
#ifdef GFX2D_SYNC_TDE
#include "drv_tde_ext.h"
#endif

/***************************** Macro Definition **************************************************/
#define GFX2D_ALIGN(value) ((value + 0xf) & 0xfffffff0)

#define GFX2D_LIST_CHECK_DEVID(id) do\
    {\
        if (id > HI_GFX2D_DEV_ID_0)\
        {\
            return HI_ERR_GFX2D_INVALID_DEVID;\
        }\
    }while(0)

#define GFX2D_LIST_CHECK_DEVTYPE(type) do\
    {\
        if (type > GFX2D_HAL_DEV_TYPE_HWC)\
        {\
            return HI_ERR_GFX2D_INVALID_DEVID;\
        }\
    }while(0)

/*************************** Structure Definition ************************************************/
typedef enum tagGFX2D_LIST_TASKSTATE_E
{
    GFX2D_LIST_TASKSTATE_UNFINISH = 0x0,
    GFX2D_LIST_TASKSTATE_FINISH,
} GFX2D_LIST_TASKSTATE_E;

/*task descriptor*/
typedef struct tagGFX2D_LIST_TASK_S
{
    /*List which links all submitted task by submit order.*/
    struct list_head stList;
    spinlock_t lock;                    /* Spin lock for concurrent access*/
    HI_VOID *pNode;                     /* First node of task,which include info for hardware*/
    HI_GFX2D_DEV_ID_E enDevId;          /* Dev id the task submitted to */
    GFX2D_HAL_DEV_TYPE_E enDevType;     /* Dev type the task submitted to */
    GFX2D_LIST_TASKSTATE_E enState;     /*Task state*/
    HI_U32 u32Ref;                      /*Reference count*/
    HI_BOOL bWait;                      /*Whether some process is waiting for the task finish*/
    wait_queue_head_t stWaitQueueHead;  /*wait queue head*/
#ifdef GFX2D_FENCE_SUPPORT
    HI_S32 s32ReleaseFenceFd;           /*release fence fd*/
#endif
    HI_GFX2D_EXTINFO_S ExtInfo;
} GFX2D_LIST_TASK_S;

/*task management descriptor*/
typedef struct tagGFX2D_LIST_TASK_MGR_S
{
    struct list_head stListHead;             /*List head which links all submitted task*/
    spinlock_t lock;                         /*Spin lock for concurrent access */
    GFX2D_LIST_TASK_S *pstSubmitedHeadTask;  /*First task submiited to hardware*/
    GFX2D_LIST_TASK_S *pstSubmitedTailTask;  /*Last task submiited to hardware*/
    GFX2D_LIST_TASK_S *pstToSubmitTask;      /*First task waitting or submmitting to hardware*/
    GFX2D_HAL_NODE_OPS_S *pstNodeOps;        /*functions for access node*/
#ifndef GFX2D_PROC_UNSUPPORT
    /*proc info*/
    HI_U32 u32TotalTaskNum;          /*total task num submitted */
    HI_U32 u32RunTaskNum;            /*working task num*/
    HI_U32 u32WaitTaskNum;           /*waiting task num*/
    HI_U32 u32MaxTaskPerList;        /*max task num submitted to hardware*/
    HI_U32 u32LastTimeCost;          /*last task time cost*/
    HI_U32 u32MaxTimeCost;           /*max time cost*/
    HI_U32 u32TotalTimeCost;         /*total time cost*/
    HI_U32 u32CollisionCnt;
    HI_U32 u32LastCollisionTimeCost;
    HI_U32 u32MaxCollisionTimeCost;
#endif
} GFX2D_LIST_TASK_MGR_S;

/********************** Global Variable declaration **********************************************/

/******************************* API forward declarations ****************************************/
static GFX2D_LIST_TASK_MGR_S gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0 + 1][GFX2D_HAL_DEV_TYPE_HWC + 1];

HI_S32 GFX2D_LIST_Isr(HI_S32 irq, HI_VOID *dev_id);

static inline GFX2D_LIST_TASK_S *CreateTask(const HI_GFX2D_DEV_ID_E enDevId, HI_VOID *pNode,
        GFX2D_HAL_DEV_TYPE_E enNodeType, const HI_BOOL bSync,
        const HI_U32 u32Timeout, HI_S32 s32ReleaseFenceFd);

static inline HI_VOID DestroyTask(GFX2D_LIST_TASK_S *pstTask);

static inline HI_VOID InsertTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr,
                                 GFX2D_LIST_TASK_S *pstTask);

static inline HI_VOID DeleteTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr,
                                 GFX2D_LIST_TASK_S *pstTask);

static inline HI_VOID SubmitTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr);

static inline HI_VOID UnrefTask(GFX2D_LIST_TASK_S *pstTask);

static GFX2D_LIST_TASK_S *GetTailTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr);

static HI_S32 WaitForDone(GFX2D_LIST_TASK_S *pstTask, HI_U32 u32Timeout);

#ifdef GFX2D_SYNC_TDE
static HI_U32 g_HWCIrqHandle = 0;
#endif

/******************************* API realization *************************************************/
HI_S32 GFX2D_LIST_Init(HI_VOID)
{
    HI_U32 u32IntNum = 0;
    HI_U32 u32NodeNum = 0;
    HI_U32 u32NodeSize = 0;
    HI_S32 s32Ret = HI_FAILURE;
    GFX2D_LIST_TASK_MGR_S *pstTaskMgr = &gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0][GFX2D_HAL_DEV_TYPE_HWC];

#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_U32 u32BaseAddr = 0;
#endif

    HI_GFX_Memset(pstTaskMgr, 0, sizeof(GFX2D_LIST_TASK_MGR_S));
    INIT_LIST_HEAD(&(pstTaskMgr->stListHead));
    spin_lock_init(&(pstTaskMgr->lock));

    GFX2D_HAL_GetNodeOps(GFX2D_HAL_DEV_TYPE_HWC, &(pstTaskMgr->pstNodeOps));
    if (NULL == pstTaskMgr->pstNodeOps)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "failed!\n");
        return HI_ERR_GFX2D_SYS;
    }

    u32IntNum = GFX2D_HAL_GetIsrNum(HI_GFX2D_DEV_ID_0, GFX2D_HAL_DEV_TYPE_HWC);

#ifdef GFX2D_SYNC_TDE
    if (0 != osal_request_irq(u32IntNum, (irq_handler_t)GFX2D_LIST_Isr,IRQF_SHARED, "gfx2d", &g_HWCIrqHandle))
#else
    if (0 != osal_request_irq(u32IntNum, (irq_handler_t)GFX2D_LIST_Isr,IRQF_PROBE_SHARED, "gfx2d", NULL))
#endif
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "osal_request_irq failed!\n");
        return HI_ERR_GFX2D_SYS;
    }

    s32Ret = HI_GFX_SetIrq(HIGFX_GFX2D_ID, u32IntNum,"gfx2d");
    if (HI_SUCCESS != s32Ret)
    {
#ifdef GFX2D_SYNC_TDE
        osal_free_irq(u32IntNum, "gfx2d", &g_HWCIrqHandle);
#else
        osal_free_irq(u32IntNum, "gfx2d", NULL);
#endif
        return s32Ret;
    }

    u32NodeNum  = GFX2D_CONFIG_GetNodeNum();
    u32NodeSize = ((sizeof(GFX2D_LIST_TASK_S) + 0xf) & 0xfffffff0);

    s32Ret = GFX2D_MEM_Register(u32NodeSize, u32NodeNum);
    if (HI_SUCCESS != s32Ret)
    {
#ifdef GFX2D_SYNC_TDE
        osal_free_irq(u32IntNum, "gfx2d", &g_HWCIrqHandle);
#else
        osal_free_irq(u32IntNum, "gfx2d", NULL);
#endif
        return s32Ret;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    u32BaseAddr = GFX2D_HAL_GetBaseAddr(HI_GFX2D_DEV_ID_0, GFX2D_HAL_DEV_TYPE_HWC);
    s32Ret = HI_GFX_MapSmmuReg(u32BaseAddr + 0xf000);
    s32Ret |= HI_GFX_InitSmmu(u32BaseAddr + 0xf000);
    if (HI_SUCCESS != s32Ret)
    {
        GFX2D_Mem_UnRegister(u32NodeSize);
#ifdef GFX2D_SYNC_TDE
        osal_free_irq(u32IntNum, "gfx2d", &g_HWCIrqHandle);
#else
        osal_free_irq(u32IntNum, "gfx2d", NULL);
#endif
        return s32Ret;
    }
#endif

    return HI_SUCCESS;
}

HI_VOID GFX2D_LIST_Deinit(HI_VOID)
{
    HI_U32 u32IntNum = 0;
    HI_U32 u32NodeSize = 0;

#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_GFX_DeinitSmmu();
    HI_GFX_UnMapSmmuReg();
#endif

    u32NodeSize = GFX2D_ALIGN(sizeof(GFX2D_LIST_TASK_S));
    GFX2D_Mem_UnRegister(u32NodeSize);

    u32IntNum = GFX2D_HAL_GetIsrNum(HI_GFX2D_DEV_ID_0, GFX2D_HAL_DEV_TYPE_HWC);
#ifdef GFX2D_SYNC_TDE
    osal_free_irq(u32IntNum, "gfx2d", &g_HWCIrqHandle);
#else
    osal_free_irq(u32IntNum, "gfx2d", NULL);
#endif

    return;
}

#ifdef GFX2D_SYNC_TDE
static TDE_EXPORT_FUNC_S *ps_TdeExportFuncs = HI_NULL;
#endif

HI_S32 GFX2D_LIST_Open(HI_VOID)
{
#ifdef GFX2D_SYNC_TDE
    if (ps_TdeExportFuncs != HI_NULL)
    {
        return HI_SUCCESS;
    }

    if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_TDE, (HI_VOID **)&ps_TdeExportFuncs))
    {
        ps_TdeExportFuncs = HI_NULL;
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "\n");
        return HI_FAILURE;
    }

    if (   (HI_NULL == ps_TdeExportFuncs)
        || (HI_NULL == ps_TdeExportFuncs->pfnTdeLockWorkingFlag)
        || (HI_NULL == ps_TdeExportFuncs->pfnTdeGetWorkingFlag)
        || (HI_NULL == ps_TdeExportFuncs->pfnTdeUnlockWorkingFlag)
        || (HI_NULL == ps_TdeExportFuncs->pfnTdeSetWorkingFlag))
    {
        ps_TdeExportFuncs = HI_NULL;
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "\n");
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

HI_VOID GFX2D_LIST_Close(HI_VOID)
{
#ifdef GFX2D_SYNC_TDE
    ps_TdeExportFuncs = HI_NULL;
#endif

    return;
}

HI_S32 GFX2D_LIST_SubNode(GFX2D_LIST_NODE_S *pstNode, HI_GFX2D_EXTINFO_S *ExtInfo)
{
    GFX2D_LIST_TASK_S *pstTask = NULL;
    GFX2D_LIST_TASK_MGR_S *pstTaskMgr = NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    GFX2D_CHECK_NULLPOINTER_RETURN_VALUE(pstNode, HI_FAILURE);
    GFX2D_CHECK_NULLPOINTER_RETURN_VALUE(ExtInfo, HI_FAILURE);

    GFX2D_LIST_CHECK_DEVID(pstNode->enDevId);
    GFX2D_LIST_CHECK_DEVTYPE(pstNode->enNodeType);

    pstTaskMgr = &gs_astLISTTaskMgr[pstNode->enDevId][pstNode->enNodeType];

    pstTask = CreateTask(pstNode->enDevId, pstNode->pNode, pstNode->enNodeType,
                         pstNode->bSync, pstNode->u32Timeout, pstNode->s32ReleaseFenceFd);
    if (HI_NULL == pstTask)
    {
        if (pstTaskMgr->pstNodeOps && pstTaskMgr->pstNodeOps->pfnFreeNode)
        {
            pstTaskMgr->pstNodeOps->pfnFreeNode(pstNode->pNode);
        }
        return HI_ERR_GFX2D_NO_MEM;
    }

    InsertTask(pstTaskMgr, pstTask);

    SubmitTask(pstTaskMgr);

    if (pstNode->bSync)
    {
        s32Ret = WaitForDone(pstTask, pstNode->u32Timeout);
        if (HI_SUCCESS != s32Ret)
        {
            DestroyTask(pstTask);
            return s32Ret;
        }
        HI_GFX_Memcpy(ExtInfo, &(pstTask->ExtInfo), sizeof(HI_GFX2D_EXTINFO_S));
        DestroyTask(pstTask);
    }
    else
    {
        HI_GFX_Memcpy(ExtInfo, &(pstTask->ExtInfo), sizeof(HI_GFX2D_EXTINFO_S));
        UnrefTask(pstTask);
    }

    return HI_SUCCESS;
}

HI_S32 GFX2D_LIST_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId, const HI_U32 u32Timeout)
{
    GFX2D_LIST_TASK_S *pstTask = NULL;
    HI_S32 s32Ret = HI_FAILURE;

    GFX2D_LIST_CHECK_DEVID(enDevId);

    pstTask = GetTailTask(&gs_astLISTTaskMgr[enDevId][GFX2D_HAL_DEV_TYPE_HWC]);
    if (HI_NULL == pstTask)
    {
        return HI_SUCCESS;
    }

    s32Ret = WaitForDone(pstTask, u32Timeout);
    if (HI_SUCCESS != s32Ret)
    {
        DestroyTask(pstTask);
        return s32Ret;
    }

    DestroyTask(pstTask);

    return HI_SUCCESS;
}

static inline GFX2D_LIST_TASK_S *CreateTask(const HI_GFX2D_DEV_ID_E enDevId, HI_VOID *pNode,
                                            GFX2D_HAL_DEV_TYPE_E enNodeType, const HI_BOOL bSync,
                                            const HI_U32 u32Timeout, HI_S32 s32ReleaseFenceFd)
{
    GFX2D_LIST_TASK_S *pstTask = NULL;

    pstTask = (GFX2D_LIST_TASK_S *)HI_GFX_KMALLOC(HIGFX_GFX2D_ID, sizeof(GFX2D_LIST_TASK_S), GFP_KERNEL);
    if (HI_NULL == pstTask)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "Alloc %d failed!\n", sizeof(GFX2D_LIST_TASK_S));
        return HI_NULL;
    }

    HI_GFX_Memset(pstTask, 0, sizeof(GFX2D_LIST_TASK_S));

    INIT_LIST_HEAD(&(pstTask->stList));
    spin_lock_init(&(pstTask->lock));
    init_waitqueue_head(&(pstTask->stWaitQueueHead));

    pstTask->u32Ref    = 1;
    pstTask->pNode     = pNode;
    pstTask->enDevId   = enDevId;
    pstTask->enDevType = enNodeType;

#ifdef GFX2D_FENCE_SUPPORT
    pstTask->s32ReleaseFenceFd = s32ReleaseFenceFd;
#endif

    HI_GFX_Memset(&(pstTask->ExtInfo.AlphaSum), 0xff, sizeof(pstTask->ExtInfo.AlphaSum));

    return pstTask;
}

static inline HI_VOID DestroyTask(GFX2D_LIST_TASK_S *pstTask)
{
    unsigned long lockflag = 0;
    GFX2D_LIST_TASK_MGR_S *pstTaskMgr = &gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0][GFX2D_HAL_DEV_TYPE_HWC];
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTask);

    spin_lock_irqsave(&(pstTask->lock),lockflag);
    pstTask->u32Ref--;
    if (0 == pstTask->u32Ref && (GFX2D_LIST_TASKSTATE_FINISH == pstTask->enState))
    {
        if (pstTaskMgr->pstNodeOps && pstTaskMgr->pstNodeOps->pfnFreeNode)
        {
            pstTaskMgr->pstNodeOps->pfnFreeNode(pstTask->pNode);
        }
        spin_unlock_irqrestore(&(pstTask->lock),lockflag);
        HI_GFX_KFREE(HIGFX_GFX2D_ID, pstTask);
        return;
    }

    spin_unlock_irqrestore(&(pstTask->lock),lockflag);

    return;
}

static inline HI_VOID InsertTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr,GFX2D_LIST_TASK_S *pstTask)
{
    unsigned long lockflag = 0;
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTaskMgr);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTask);

    spin_lock_irqsave(&(pstTaskMgr->lock), lockflag);

    list_add_tail(&(pstTask->stList), &(pstTaskMgr->stListHead));
    if (NULL == pstTaskMgr->pstToSubmitTask)
    {
        pstTaskMgr->pstToSubmitTask = pstTask;
    }

#ifndef GFX2D_PROC_UNSUPPORT
    pstTaskMgr->u32TotalTaskNum++;
    pstTaskMgr->u32WaitTaskNum++;
#endif

    spin_unlock_irqrestore(&(pstTaskMgr->lock), lockflag);

    return;
}

static inline HI_VOID DeleteTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr,GFX2D_LIST_TASK_S *pstTask)
{
    unsigned long lockflag = 0;
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTaskMgr);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTask);

    spin_lock_irqsave(&(pstTaskMgr->lock),lockflag);

    list_del_init(&(pstTask->stList));

    spin_unlock_irqrestore(&(pstTaskMgr->lock),lockflag);

    return;
}

static inline HI_VOID SubmitTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr)
{
    unsigned long lockflag = 0;
    struct list_head *pstCur = NULL, *pstNext = NULL;
    GFX2D_LIST_TASK_S *pstCurTask = NULL, *pstNextTask = NULL;
    HI_S32 s32Ret = HI_FAILURE;
#ifdef GFX2D_SYNC_TDE
    HI_BOOL bDeviceBusy = HI_FALSE;
    unsigned long deviceflag = 0;
#endif
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTaskMgr);

    spin_lock_irqsave(&(pstTaskMgr->lock), lockflag);

    /*If the hardware is working or no task is submited by app,return!
    Use the pstTaskMgr->pstSubmitedHeadTask to judge whether the hardware
    is working or not:when submitting task to hardware,set the flag the addr
    of submitted task.After the task is done,set the flag null to denote the
    hardware is idle!*/
    if ((NULL != pstTaskMgr->pstSubmitedHeadTask) || (NULL == pstTaskMgr->pstToSubmitTask))
    {
        spin_unlock_irqrestore(&(pstTaskMgr->lock),lockflag);
        return;
    }

#ifdef GFX2D_SYNC_TDE
    ps_TdeExportFuncs->pfnTdeLockWorkingFlag(&deviceflag);

    ps_TdeExportFuncs->pfnTdeGetWorkingFlag(&bDeviceBusy);

    if (bDeviceBusy)
    {
        ps_TdeExportFuncs->pfnTdeUnlockWorkingFlag(&deviceflag);
        spin_unlock_irqrestore(&(pstTaskMgr->lock), lockflag);
#ifndef GFX2D_PROC_UNSUPPORT
        GFX2D_CONFIG_StartTime();
        pstTaskMgr->u32CollisionCnt++;
#endif

        return;
    }
#endif
    pstCur = &(pstTaskMgr->pstToSubmitTask->stList);
    pstNext = pstCur->next;

#ifndef GFX2D_PROC_UNSUPPORT
    pstTaskMgr->u32RunTaskNum = 1;
    pstTaskMgr->u32WaitTaskNum--;
#endif

    while (pstNext != (&pstTaskMgr->stListHead))
    {
        pstCurTask = (GFX2D_LIST_TASK_S *)pstCur;
        pstNextTask = (GFX2D_LIST_TASK_S *)pstNext;

        if ((HI_NULL == pstTaskMgr->pstNodeOps) || (HI_NULL == pstTaskMgr->pstNodeOps->pfnLinkNode))
        {
            break;
        }

        /*Hardware can process many tasks one time,requires that the tasks
        link each other by the promissory format!*/
        s32Ret = pstTaskMgr->pstNodeOps->pfnLinkNode(pstCurTask->pNode, pstNextTask->pNode);
        if (s32Ret < 0)
        {
            break;
        }
#ifndef GFX2D_PROC_UNSUPPORT
        pstTaskMgr->u32RunTaskNum++;
        pstTaskMgr->u32WaitTaskNum--;
#endif
        pstCur = pstNext;
        pstNext = pstNext->next;
    }

    /*Submit task to hardware!*/
    pstTaskMgr->pstSubmitedHeadTask = pstTaskMgr->pstToSubmitTask;
    pstTaskMgr->pstSubmitedTailTask = (GFX2D_LIST_TASK_S *)pstCur;

    if (pstNext == &(pstTaskMgr->stListHead))
    {
        pstTaskMgr->pstToSubmitTask = HI_NULL;
    }
    else
    {
        pstTaskMgr->pstToSubmitTask = (GFX2D_LIST_TASK_S *)pstNext;
    }

#ifndef GFX2D_PROC_UNSUPPORT
    if (pstTaskMgr->u32RunTaskNum > pstTaskMgr->u32MaxTaskPerList)
    {
        pstTaskMgr->u32MaxTaskPerList = pstTaskMgr->u32RunTaskNum;
    }
#endif


#ifndef GFX2D_PROC_UNSUPPORT
    pstTaskMgr->u32LastCollisionTimeCost = GFX2D_CONFIG_EndTime();
    if (pstTaskMgr->u32LastCollisionTimeCost > pstTaskMgr->u32MaxCollisionTimeCost)
    {
        pstTaskMgr->u32MaxCollisionTimeCost = pstTaskMgr->u32LastCollisionTimeCost;
    }

    GFX2D_CONFIG_StartTime();
#endif

    if (pstTaskMgr->pstNodeOps && pstTaskMgr->pstNodeOps->pfnSubNode)
    {
        pstTaskMgr->pstNodeOps->pfnSubNode(pstTaskMgr->pstSubmitedHeadTask->enDevId,
                                           pstTaskMgr->pstSubmitedHeadTask->pNode);
    }

#ifdef GFX2D_SYNC_TDE
    ps_TdeExportFuncs->pfnTdeSetWorkingFlag(HI_TRUE);
    ps_TdeExportFuncs->pfnTdeUnlockWorkingFlag(&deviceflag);
#endif
    spin_unlock_irqrestore(&(pstTaskMgr->lock), lockflag);

    return;
}

static GFX2D_LIST_TASK_S *GetTailTask(GFX2D_LIST_TASK_MGR_S *pstTaskMgr)
{
    unsigned long listlockflag = 0;
    unsigned long tasklockflag = 0;
    GFX2D_LIST_TASK_S *pstTask = NULL;
    GFX2D_CHECK_NULLPOINTER_RETURN_VALUE(pstTaskMgr, NULL);

    spin_lock_irqsave(&(pstTaskMgr->lock),listlockflag);
    if (list_empty(&(pstTaskMgr->stListHead)))
    {
        spin_unlock_irqrestore(&(pstTaskMgr->lock),listlockflag);
        return HI_NULL;
    }

    pstTask = (GFX2D_LIST_TASK_S *)pstTaskMgr->stListHead.prev;
    spin_unlock_irqrestore(&(pstTaskMgr->lock),listlockflag);

    /*Add task ref to avoid the task is destroyed by other process!*/
    spin_lock_irqsave(&(pstTask->lock),tasklockflag);
    pstTask->u32Ref++;
    spin_unlock_irqrestore(&(pstTask->lock),tasklockflag);

    return pstTask;
}

static HI_VOID ListCompIsr(HI_VOID)
{
    GFX2D_LIST_TASK_S *pstTask = NULL;
    GFX2D_LIST_TASK_S *pstNextTask = NULL;
    GFX2D_LIST_TASK_MGR_S *pstTaskMgr = &gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0][GFX2D_HAL_DEV_TYPE_HWC];
    unsigned long lockflag = 0;

#ifndef GFX2D_PROC_UNSUPPORT
    pstTaskMgr->u32LastTimeCost = GFX2D_CONFIG_EndTime();
    pstTaskMgr->u32TotalTimeCost += pstTaskMgr->u32LastTimeCost;
    if (pstTaskMgr->u32LastTimeCost > pstTaskMgr->u32MaxTimeCost)
    {
        pstTaskMgr->u32MaxTimeCost = pstTaskMgr->u32LastTimeCost;
    }
#endif
    pstNextTask = pstTaskMgr->pstSubmitedHeadTask;
    do
    {
        pstTask = pstNextTask;

        /*Get the next task before wake_up,because process waked up may
        delete the task from the list!*/
        spin_lock_irqsave(&(pstTaskMgr->lock), lockflag);
        pstNextTask = (GFX2D_LIST_TASK_S *)(pstTask->stList.next);
        spin_unlock_irqrestore(&(pstTaskMgr->lock), lockflag);

        if (pstTaskMgr->pstNodeOps && pstTaskMgr->pstNodeOps->pfnNodeIsr)
        {
            pstTaskMgr->pstNodeOps->pfnNodeIsr(pstTask->pNode);
        }

        spin_lock_irqsave(&(pstTask->lock), lockflag);
        pstTask->enState = GFX2D_LIST_TASKSTATE_FINISH;
        pstTask->u32Ref++;
#ifdef GFX2D_ALPHADETECT_SUPPORT
        if (pstTask->bWait)
        {
            GFX2D_HAL_GetTransparent(&(pstTask->ExtInfo));
        }
#endif
        spin_unlock_irqrestore(&(pstTask->lock), lockflag);

#ifdef GFX2D_FENCE_SUPPORT
        if (pstTask->s32ReleaseFenceFd >= 0)
        {
            GFX2D_FENCE_WakeUp();
        }
#endif
        DeleteTask(pstTaskMgr, pstTask);

        if (pstTask->bWait)
        {
            UnrefTask(pstTask);
            wake_up(&pstTask->stWaitQueueHead);
        }
        else
        {
            DestroyTask(pstTask);
        }
#ifndef GFX2D_PROC_UNSUPPORT
        spin_lock_irqsave(&(pstTaskMgr->lock), lockflag);
        pstTaskMgr->u32RunTaskNum--;
        spin_unlock_irqrestore(&(pstTaskMgr->lock), lockflag);
#endif
    }while(pstTask != pstTaskMgr->pstSubmitedTailTask);

    spin_lock_irqsave(&(pstTaskMgr->lock), lockflag);
    pstTaskMgr->pstSubmitedHeadTask = HI_NULL;
    pstTaskMgr->pstSubmitedTailTask = HI_NULL;
    if (pstTaskMgr->pstNodeOps && pstTaskMgr->pstNodeOps->pfnAllNodeIsr)
    {
        pstTaskMgr->pstNodeOps->pfnAllNodeIsr();
    }
    spin_unlock_irqrestore(&(pstTaskMgr->lock),lockflag);

#ifdef GFX2D_SYNC_TDE
    ps_TdeExportFuncs->pfnTdeLockWorkingFlag(&lockflag);
    ps_TdeExportFuncs->pfnTdeSetWorkingFlag(HI_FALSE);
    ps_TdeExportFuncs->pfnTdeUnlockWorkingFlag(&lockflag);
#endif

    return;
}

static void Gfx2dTaskletFunc(unsigned long int_status);
DECLARE_TASKLET(g_Gfx2dTasklet, Gfx2dTaskletFunc, 0);

static void Gfx2dTaskletFunc(unsigned long int_status)
{
    g_Gfx2dTasklet.data &= (~int_status);

    SubmitTask(&gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0][GFX2D_HAL_DEV_TYPE_HWC]);
}

HI_S32 GFX2D_LIST_Isr(HI_S32 irq, HI_VOID *dev_id)
{
    HI_U32 u32Status = 0;

#ifdef GFX2D_SYNC_TDE
    if (ps_TdeExportFuncs == NULL)
    {
        return IRQ_HANDLED;
    }
#endif

#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_GFX_SmmuIsr("HI_MOD_GFX2D");
#endif

    u32Status = GFX2D_HAL_GetIntStatus(GFX2D_HAL_DEV_TYPE_HWC);
    if (u32Status & 0x1)
    {
        ListCompIsr();
    }
    g_Gfx2dTasklet.data = g_Gfx2dTasklet.data |((unsigned long)u32Status);

    tasklet_schedule(&g_Gfx2dTasklet);

    return IRQ_HANDLED;
}


static inline HI_VOID UnrefTask(GFX2D_LIST_TASK_S *pstTask)
{
    unsigned long lockflag = 0;
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(pstTask);

    spin_lock_irqsave(&(pstTask->lock),lockflag);
    pstTask->u32Ref--;
    spin_unlock_irqrestore(&(pstTask->lock),lockflag);

    return;
}

static HI_S32 WaitForDone(GFX2D_LIST_TASK_S *pstTask, HI_U32 u32Timeout)
{
    unsigned long lockflag = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Jiffies = 0;
    GFX2D_LIST_TASKSTATE_E enState;
    GFX2D_CHECK_NULLPOINTER_RETURN_VALUE(pstTask, HI_FAILURE);

    if ((0 == u32Timeout) || (u32Timeout > 10000))
    {
        u32Jiffies = 10000 * HZ / 1000;
    }
    else
    {
        u32Jiffies = u32Timeout * HZ / 1000;
    }

    spin_lock_irqsave(&(pstTask->lock),lockflag);
    pstTask->bWait = HI_TRUE;
    spin_unlock_irqrestore(&(pstTask->lock), lockflag);

    s32Ret = wait_event_timeout(pstTask->stWaitQueueHead,(GFX2D_LIST_TASKSTATE_FINISH == pstTask->enState), u32Jiffies);
    if (s32Ret <= 0)
    {
        s32Ret = HI_ERR_GFX2D_TIMEOUT;
    }

    spin_lock_irqsave(&(pstTask->lock), lockflag);
    pstTask->bWait = HI_FALSE;
    enState = pstTask->enState;
    spin_unlock_irqrestore(&(pstTask->lock), lockflag);

    if (GFX2D_LIST_TASKSTATE_FINISH == enState)
    {
        s32Ret = HI_SUCCESS;
    }
    else
    {
        HI_GFX_COMM_LOG_WARNING(HIGFX_GFX2D_ID, "timeout!\n");
    }

    return s32Ret;
}

HI_S32 GFX2D_LIST_Resume(HI_VOID)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_U32 u32BaseAddr = 0;

    u32BaseAddr = GFX2D_HAL_GetBaseAddr(HI_GFX2D_DEV_ID_0, GFX2D_HAL_DEV_TYPE_HWC);

    (HI_VOID)HI_GFX_MapSmmuReg(u32BaseAddr + 0xf000);

    return HI_GFX_InitSmmu(u32BaseAddr + 0xf000);
#else
    return HI_SUCCESS;
#endif
}

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_LIST_ReadProc(struct seq_file *p, HI_VOID *v)
{
    GFX2D_LIST_TASK_MGR_S *pstTaskMgr = &gs_astLISTTaskMgr[HI_GFX2D_DEV_ID_0][GFX2D_HAL_DEV_TYPE_HWC];
    HI_UNUSED(v);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(p);

    SEQ_Printf(p, "---------------------GFX2D Task Info--------------------\n");
    SEQ_Printf(p, "TotalTaskNum\t:%u\n",            pstTaskMgr->u32TotalTaskNum);
    SEQ_Printf(p, "RunTaskNum\t:%u\n",              pstTaskMgr->u32RunTaskNum);
    SEQ_Printf(p, "WaitTaskNum\t:%u\n",             pstTaskMgr->u32WaitTaskNum);
    SEQ_Printf(p, "MaxTaskPerList\t:%d\n",          pstTaskMgr->u32MaxTaskPerList);
    SEQ_Printf(p, "TotalTimeCost\t:%uus\n",         pstTaskMgr->u32TotalTimeCost);
    SEQ_Printf(p, "MaxTimeCost\t:%uus\n",           pstTaskMgr->u32MaxTimeCost);
    SEQ_Printf(p, "LastTimeCost\t:%uus\n",          pstTaskMgr->u32LastTimeCost);
    SEQ_Printf(p, "CollisionCnt\t:%uus\n",          pstTaskMgr->u32CollisionCnt);
    SEQ_Printf(p, "LastCollisionTimeCost\t:%uus\n", pstTaskMgr->u32LastCollisionTimeCost);
    SEQ_Printf(p, "MaxCollisionTimeCost\t:%uus\n",  pstTaskMgr->u32MaxCollisionTimeCost);
    return;
}

HI_VOID GFX2D_LIST_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    HI_UNUSED(file);
    HI_UNUSED(buf);
    HI_UNUSED(ppos);
    return;
}
#endif
