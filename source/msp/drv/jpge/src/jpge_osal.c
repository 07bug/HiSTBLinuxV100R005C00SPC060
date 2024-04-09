/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name         : jpge_osal.c
Version           : Initial Draft
Author            :
Created           : 2018/01/01
Description       :  CNcomment:  CNend\n
Function List     :


History           :
Date                            Author                   Modification
2018/01/01                      sdk                      Created file
*************************************************************************************************/


/*********************************add include here***********************************************/
#include "jpge_osal.h"
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include "hi_gfx_comm_k.h"
#include "hi_gfx_sys_k.h"
#include "hi_kernel_adapt.h"
#include "drv_jpge_paracheck.h"

/***************************** Macro Definition *************************************************/

/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/
static HI_HANDLE hJpgeIrq = HI_INVALID_HANDLE;

extern HI_BOOL gs_JpgeDebugInterApi;
extern HI_BOOL gs_JpgeDebugUnf;

/********************** API forward declarations     ********************************************/

static HI_VOID (*ptrJpgeCallBack)(HI_VOID);

/********************** API forward release          ********************************************/

static irqreturn_t JpgeOsal_JencISR(HI_S32 Irq, HI_VOID* DevID)
{
    HI_UNUSED(Irq);
    HI_UNUSED(DevID);

    if (NULL != ptrJpgeCallBack)
    {
       (*ptrJpgeCallBack)();
    }

    return IRQ_HANDLED;
}


/***************************************************************************
* func         : JpgeOsal_IrqInit
* description  : CNcomment: 中断初始化 CNend\n
* retval       : NA
* others:      : NA
****************************************************************************/
HI_S32 JpgeOsal_IrqInit( HI_U32 Irq, HI_VOID (*ptrCallBack)(HI_VOID) )
{
    HI_S32 s32Ret = HI_SUCCESS;

    ptrJpgeCallBack = ptrCallBack;
    JPGE_CHECK_NULLPOINTER_RETURN(ptrJpgeCallBack, HI_FAILURE);

    if (HI_SUCCESS != osal_request_irq(Irq, JpgeOsal_JencISR, IRQF_SHARED, "jpge", &hJpgeIrq))
    {
        HI_GFX_LOG_PrintFuncErr(osal_request_irq, HI_FAILURE);
        return HI_FAILURE;
    }

    s32Ret = HI_GFX_SetIrq(HIGFX_JPGENC_ID,Irq, "jpge");
    if (HI_SUCCESS != s32Ret)
    {
        osal_free_irq(Irq, "jpge", &hJpgeIrq);
        HI_GFX_LOG_PrintFuncErr(HI_GFX_SetIrq, HI_FAILURE);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/***************************************************************************
* func          : JpgeOsal_IrqFree
* description   : CNcomment: 释放中断响应 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JpgeOsal_IrqFree( HI_U32 Irq )
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    osal_free_irq(Irq, "jpge", &hJpgeIrq);
    hJpgeIrq = HI_INVALID_HANDLE;
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_SUCCESS;
}


/***************************************************************************
* func          : JpgeOsal_LockInit
* description   : init lock
                  CNcomment: 锁初始化 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JpgeOsal_LockInit(JPGE_LOCK_S *pLock)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_RETURN(pLock, HI_FAILURE);
    spin_lock_init(pLock);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_SUCCESS;
}

/***************************************************************************
* func          : JpgeOsal_Lock
* description   : lock
                  CNcomment: 加锁 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID JpgeOsal_Lock(JPGE_LOCK_S *pLock, JPGE_LOCK_FLAG *pFlag)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pLock);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pFlag);
    spin_lock_irqsave((spinlock_t *)pLock, *pFlag);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
}

/***************************************************************************
* func          : JpgeOsal_Unlock
* description   : unlock
                  CNcomment: 解锁 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID JpgeOsal_Unlock(JPGE_LOCK_S *pLock, JPGE_LOCK_FLAG *pFlag)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pLock);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pFlag);
    spin_unlock_irqrestore((spinlock_t *)pLock, *pFlag);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
}

/***************************************************************************
* func          : JpgeOsal_MutexInit
* description   : init mutex
                  CNcomment: 信号量初始化 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JpgeOsal_MutexInit(JPGE_SEM_S *pMutex)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_RETURN(pMutex, HI_FAILURE);
    sema_init(pMutex,1);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_SUCCESS;
}

/***************************************************************************
* func          : JpgeOsal_MutexLock
* description   : lock with mutex
                  CNcomment: 使用信号量锁 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JpgeOsal_MutexLock(JPGE_SEM_S *pMutex)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_RETURN(pMutex, HI_FAILURE);
    if (down_interruptible(pMutex))
    {
        HI_GFX_LOG_PrintFuncErr(down_interruptible, HI_FAILURE);
        return HI_FAILURE;
    }
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_SUCCESS;
}

/***************************************************************************
* func          : JpgeOsal_MutexUnlock
* description   : unlock with mutex
                  CNcomment: 使用信号量解锁 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JpgeOsal_MutexUnlock(JPGE_SEM_S *pMutex)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_RETURN(pMutex, HI_FAILURE);
    up(pMutex);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_SUCCESS;
}

/***************************************************************************
* func          : JpgeOsal_MapRegisterAddr
* description   : map register ddr
                  CNcomment: 映射寄存器地址 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID* JpgeOsal_MapRegisterAddr(HI_U32 phyAddr, HI_U32 len)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_EQUAL_RETURN(0, phyAddr, NULL);
    JPGE_CHECK_EQUAL_RETURN(0, len, NULL);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return HI_GFX_REG_MAP(phyAddr, len);
}


/***************************************************************************
* func          : JpgeOsal_UnmapRegisterAddr
* description   : unmap register ddr
                  CNcomment: 逆映射寄存器地址 CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_VOID JpgeOsal_UnmapRegisterAddr(HI_VOID* pVir)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pVir);
    HI_GFX_REG_UNMAP(pVir);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return;
}
