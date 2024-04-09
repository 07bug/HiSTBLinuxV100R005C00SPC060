/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_handle_k.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/

/*********************************add include here**********************************************/
#ifndef HI_BUILD_IN_BOOT
#include <linux/kthread.h>
#include <linux/list.h>
#include <linux/mm.h>
#include "hi_gfx_comm_k.h"
#else
#include "hi_gfx_list.h"
#include "wmalloc.h"
#include "hi_gfx_mem.h"
#endif
#include "tde_define.h"
#include "tde_handle.h"
#include "tde_check_para.h"
#include "hi_gfx_sys_k.h"


/***************************** Macro Definition ********************************************/

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/********************** Global Variable declaration ****************************************/
HI_HANDLE_MGR *s_pstTdeHandleList = NULL;

STATIC HI_S32 s_handle = 1;

#ifndef HI_BUILD_IN_BOOT
STATIC spinlock_t s_handlelock;
#endif

extern HI_BOOL gs_TdeDebugInterApi;
/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/
HI_BOOL initial_handle(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);

    if (NULL == s_pstTdeHandleList)
    {
#ifndef HI_BUILD_IN_BOOT
        s_pstTdeHandleList = (HI_HANDLE_MGR *)HI_GFX_KMALLOC(HIGFX_TDE_ID, sizeof(HI_HANDLE_MGR), GFP_KERNEL);
#else
        s_pstTdeHandleList = (HI_HANDLE_MGR *)HI_GFX_Malloc(sizeof(HI_HANDLE_MGR), "tde handle");
#endif
        if (NULL == s_pstTdeHandleList)
        {
            HI_GFX_LOG_PrintFuncErr(HI_GFX_Malloc,HI_FAILURE);
            return HI_FALSE;
        }

        /* Initialize list head */
        INIT_LIST_HEAD(&s_pstTdeHandleList->stHeader);

#ifndef HI_BUILD_IN_BOOT
        spin_lock_init(&s_pstTdeHandleList->lock);
        spin_lock_init(&s_handlelock);
#endif
    }

    s_handle = 1;

    HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);

    return HI_TRUE;
}

HI_VOID get_handle(HI_HANDLE_MGR *res, HI_S32 *handle)
{
#ifndef HI_BUILD_IN_BOOT
    HI_SIZE_T lockflags = 0;
    HI_SIZE_T handlockflags = 0;
#endif
    TDE_CHECK_NULLPOINTER_RETURN_NOVALUE(res);
    TDE_CHECK_NULLPOINTER_RETURN_NOVALUE(handle);
    TDE_CHECK_NULLPOINTER_RETURN_NOVALUE(s_pstTdeHandleList);

    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);

    TDE_LOCK(&s_handlelock, handlockflags);

    if (TDE_MAX_HANDLE_VALUE == s_handle)
    {
        s_handle = 1;
    }

    res->handle = s_handle;
    *handle = s_handle++;
    TDE_UNLOCK(&s_handlelock, handlockflags);

    TDE_LOCK(&s_pstTdeHandleList->lock,lockflags);
    list_add_tail(&res->stHeader, &s_pstTdeHandleList->stHeader);
    TDE_UNLOCK(&s_pstTdeHandleList->lock,lockflags);

    HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);

    return;
}

HI_BOOL query_handle(HI_S32 handle, HI_HANDLE_MGR **res)
{
#ifndef HI_BUILD_IN_BOOT
    HI_SIZE_T lockflags = 0;
#endif
    HI_HANDLE_MGR *pstHandle = NULL;
    TDE_CHECK_NULLPOINTER_RETURN_VALUE(res, HI_FALSE);
    TDE_CHECK_NULLPOINTER_RETURN_VALUE(s_pstTdeHandleList, HI_FALSE);

    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);

    TDE_LOCK(&s_pstTdeHandleList->lock, lockflags);

    pstHandle = list_entry(s_pstTdeHandleList->stHeader.prev, HI_HANDLE_MGR, stHeader);
    if (NULL == pstHandle)
    {
        TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FALSE;
    }

    while (pstHandle != s_pstTdeHandleList)
    {
        if (pstHandle->handle == handle)
        {
            *res = pstHandle;
            TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
            HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);
            return HI_TRUE;
        }

        pstHandle = list_entry(pstHandle->stHeader.prev, HI_HANDLE_MGR, stHeader);
        if (NULL == pstHandle)
        {
            TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            return HI_FALSE;
        }
    }

    TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);

    return HI_FALSE;
}

HI_BOOL release_handle(HI_S32 handle)
{
#ifndef HI_BUILD_IN_BOOT
    HI_SIZE_T lockflags;
#endif
    HI_HANDLE_MGR *pstHandle = NULL;
    TDE_CHECK_NULLPOINTER_RETURN_VALUE(s_pstTdeHandleList, HI_FALSE);

    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);

    TDE_LOCK(&s_pstTdeHandleList->lock, lockflags);
    pstHandle = list_entry(s_pstTdeHandleList->stHeader.next, HI_HANDLE_MGR, stHeader);
    if (NULL == pstHandle)
    {
        TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FALSE;
    }

    while (pstHandle != s_pstTdeHandleList)
    {
        if (pstHandle->handle == handle)
        {
            list_del_init(&pstHandle->stHeader);
            TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
            HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);
            return HI_TRUE;
        }
        pstHandle = list_entry(pstHandle->stHeader.next, HI_HANDLE_MGR, stHeader);
        if (NULL == pstHandle)
        {
            TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            return HI_FALSE;
        }
    }

    TDE_UNLOCK(&s_pstTdeHandleList->lock, lockflags);

    HI_GFX_LOG_PrintErrCode(HI_FAILURE);

    return HI_FALSE;
}

HI_VOID destroy_handle(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);

    if (NULL != s_pstTdeHandleList)
    {
    #ifndef HI_BUILD_IN_BOOT
       HI_GFX_KFREE(HIGFX_TDE_ID, s_pstTdeHandleList);
    #else
       HI_GFX_Free((HI_CHAR *)s_pstTdeHandleList);
    #endif
    }

    s_pstTdeHandleList = NULL;

    HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);

    return;
}

