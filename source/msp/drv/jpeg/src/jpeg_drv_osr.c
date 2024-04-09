/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : jpeg_drv_osr.c
Version          : Initial Draft
Author           : sdk
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                Author                Modification
2018/01/01          sdk                  Created file
*************************************************************************************************/

/***************************** add include here**************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/ioctl.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/stddef.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/atomic.h>
#include <asm/bitops.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>
#include <asm/barrier.h>
#include "hi_kernel_adapt.h"

#include "hi_jpeg_config.h"

#ifdef CONFIG_JPEG_PROC_ENABLE
#include "jpeg_drv_proc.h"
#endif

#include "hi_drv_reg.h"
#include "hi_reg_common.h"

#ifndef CONFIG_GFX_BVT_SDK
#include "drv_jpeg_ext.h"
#endif

#include "hi_drv_jpeg.h"
#include "hi_jpeg_reg.h"
#include "hi_jpeg_checkpara.h"

#include "jpeg_drv_hal.h"
#include "jpeg_drv_suspend.h"
#include "jpeg_drv_osr.h"
#include "hi_type.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition *************************************************/

#define JPEGNAME                  "jpeg"
#define JPEGDEVNAME               "jpeg"

#define DRV_JPEG_IOCTLFUNC_ITEM_NUM_MAX      9

typedef HI_S32(*DRV_JPEG_IoctlFunc)(HI_ULONG arg);

#define  DRV_JPEG_CHECK_IOCTL_CMD(Cmd)\
    if (Cmd >= DRV_JPEG_IOCTLFUNC_ITEM_NUM_MAX)\
    {\
        return HI_FAILURE;\
    }\


#ifdef CONFIG_GFX_MMU_CLOCK
//#define CONFIG_GFX_SMMU_RESET
//#define CONFIG_GFX_SMMU_CLOSE_CLOCK
#endif

/***************************** Structure Definition *********************************************/

typedef struct tagDrvJpegIoctlFunc
{
    HI_U32 Cmd;
    DRV_JPEG_IoctlFunc DrvJpegIoctlFunc;
}DRV_JPEG_IOCTLFUNC_ITEM;


/***************************** Global Variable declaration **************************************/
#ifdef CONFIG_JPEG_SUSPEND
static HI_BOOL gs_bSuspend = HI_FALSE;
#endif

static HI_BOOL gs_bJpegDevInit = HI_FALSE;
static volatile HI_U32  *s_pJpegRegBase = HI_NULL;
static JPG_OSRDEV_S *s_pstruJpgOsrDev   = HI_NULL;

HI_GFX_DECLARE_MUTEX(s_JpegMutex);
HI_GFX_DECLARE_MUTEX(s_SuspendMutex);

static HI_S32 JPEG_OSR_GetDevice(HI_ULONG arg);
static HI_S32 JPEG_OSR_GetSuspend(HI_ULONG arg);
static HI_S32 JPEG_OSR_GetResume(HI_ULONG arg);
static HI_S32 JPEG_OSR_Reset(HI_ULONG arg);
static HI_S32 JPEG_OSR_CancelReset(HI_ULONG arg);
static HI_S32 JPEG_OSR_GetIntStatus(HI_ULONG arg);
static HI_S32 JPEG_OSR_GetResumeValue(HI_ULONG arg);
static HI_S32 JPEG_OSR_LowdelayLineInfo(HI_ULONG arg);
static HI_S32 JPEG_DRV_GetIntStatusValue(JPEG_GETINTTYPE_S *pstIntType);

#if defined(CONFIG_JPEG_LOW_DELAY_SUPPORT) && defined(CONFIG_COMPAT)
static HI_S32 JPEG_OSR_CompatLowdelayLineInfo(HI_ULONG arg);
#endif

static HI_VOID JPEG_DRV_UnLock(JPEG_INTTYPE_E eIntType);


static DRV_JPEG_IOCTLFUNC_ITEM gs_DrvJpegCtlFunc[DRV_JPEG_IOCTLFUNC_ITEM_NUM_MAX] = {
     {CMD_JPG_GETDEVICE,         JPEG_OSR_GetDevice},
     {CMD_JPG_GETSUSPEND,        JPEG_OSR_GetSuspend},
     {CMD_JPG_GETRESUME,         JPEG_OSR_GetResume},
     {CMD_JPG_RESET,             JPEG_OSR_Reset},
     {CMD_JPG_CANCEL_RESET,      JPEG_OSR_CancelReset},
     {CMD_JPG_GETINTSTATUS,      JPEG_OSR_GetIntStatus},
     {CMD_JPG_GETRESUMEVALUE,    JPEG_OSR_GetResumeValue},
     {CMD_JPG_LOWDELAY_LINEINFO, JPEG_OSR_LowdelayLineInfo},
     {DRV_JPEG_IOCTLFUNC_ITEM_NUM_MAX-1,NULL},
   };


/***************************** API forward declarations *****************************************/
static HI_S32 DRV_JPEG_Open(struct inode *inode, struct file *file);
static HI_S32 DRV_JPEG_Close(struct inode *inode, struct file *file);
static HI_S32 DRV_JPEG_Mmap(struct file * filp, struct vm_area_struct *vma);

static long jpg_osr_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg);
#ifdef CONFIG_COMPAT
static long jpg_osr_compat_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg);
#endif

static inline HI_VOID JPEG_DRV_ShowVersion(HI_BOOL bLoad);


#ifndef CONFIG_GFX_BVT_SDK
DECLARE_GFX_NODE(JPEGDEVNAME,DRV_JPEG_Open,    DRV_JPEG_Close,       DRV_JPEG_Mmap,
                             jpg_osr_ioctl,    jpg_osr_compat_ioctl,
                             JPGE_DRV_Suspend, JPGE_DRV_Resume);
#else
DECLARE_GFX_NODE(JPEGDEVNAME,DRV_JPEG_Open, DRV_JPEG_Close, DRV_JPEG_Mmap, jpg_osr_ioctl,
                             NULL,          NULL,           NULL);
#endif

extern HI_BOOL gs_JpegDebugInterApi;
extern HI_BOOL gs_JpegDebugUnf;

/***************************** API realization **************************************************/
HI_VOID DRV_JPEG_CancelReset(HI_VOID)
{
    volatile U_PERI_CRG31 unTempValue;
#ifdef CONFIG_GFX_MMU_CLOCK
    volatile U_PERI_CRG205 unTempSmmuValue;
#endif
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(g_pstRegCrg);

#ifdef CONFIG_GFX_MMU_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    if (0 == unTempSmmuValue.bits.jpgd_smmu_cken)
    {
        HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
        return;
    }
#endif

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    if (0 == unTempValue.bits.jpgd_cken)
    {
       HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
       return;
    }

#ifdef CONFIG_GFX_MMU_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    mb();
#endif

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_srst_req  = 0x0;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    mb();

    udelay(1);
    (HI_VOID)HI_GFX_InitSmmu((HI_U32)(JPGD_MMU_REG_BASEADDR));
    DRV_JPEG_SetIntMask(JPEG_REG_INTMASK_VALUE);

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return;
}

HI_VOID DRV_JPEG_ResetReg(HI_VOID)
{
#ifdef CONFIG_GFX_SMMU_RESET
    HI_U32 SmmuBusyValue = 0;
    volatile U_PERI_CRG205 unTempSmmuValue;
#endif
    volatile U_PERI_CRG31 unTempValue;
    volatile HI_U32* pBusyAddr = s_pJpegRegBase;

    HI_U32 CurClockState  = 0x1;
    HI_U32 u32StartTimeMs = 0;
    HI_U32 u32EndTimeMs   = 0;
    HI_U32 u32TotalTime   = 0;

    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(s_pJpegRegBase);
    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(g_pstRegCrg);

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    if (0x0 == unTempValue.bits.jpgd_cken)
    {
        CurClockState = 0x0;
        unTempValue.bits.jpgd_cken = 0x1;
        g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
        mb();
        udelay(1);
    }

    //DRV_JPEG_SetIntMask(0x3f);

    /**<-- reset register >**/
    /**<-- ��λ�Ĵ��� >**/
    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_srst_req = 0x1;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    mb();

    /**<-- check reset success >**/
    /**<-- �ж��Ƿ�λ�ɹ� >**/
    HI_GFX_GetTimeStamp(&u32StartTimeMs,NULL);
    while (*pBusyAddr & 0x2)
    {
        HI_GFX_GetTimeStamp(&u32EndTimeMs,NULL);
        u32TotalTime = u32EndTimeMs - u32StartTimeMs;
        if (u32TotalTime >= 1)
        {/**<-- reset failure, should not close clock >**/
         /**<-- ��λʧ�ܲ��ܹ�ʱ��>**/
           break;
        }
        udelay(1);
    }

#ifdef CONFIG_GFX_SMMU_RESET
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_srst_req = 0x1;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    mb();

    HI_GFX_SmmuResetValue(JPGD_MMU_REG_BASEADDR,&SmmuBusyValue);
    HI_GFX_GetTimeStamp(&u32StartTimeMs,NULL);
    while (0x0 == SmmuBusyValue)
    {
        HI_GFX_GetTimeStamp(&u32EndTimeMs,NULL);
        u32TotalTime = u32EndTimeMs - u32StartTimeMs;
        if (u32TotalTime >= 1)
        {
           break;
        }
        HI_GFX_SmmuResetValue(JPGD_MMU_REG_BASEADDR,&SmmuBusyValue);
        #if 1
        udelay(1);
        break;
       #endif
    }
#endif

#ifdef CONFIG_GFX_SMMU_RESET
    HI_GFX_DeinitSmmu();
    udelay(1);
#endif

    /**<-- recover clock register >**/
    /**<-- ʱ��״̬��ԭ >**/
    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_cken  = CurClockState;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    mb();
    udelay(1);

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return;
}

/***************************************************************************************
* func         : DRV_JPEG_OffClock
* description  : close the jpeg clock
                 CNcomment: �ر�jpegʱ�� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_JPEG_OffClock(HI_VOID)
{
#ifdef CONFIG_GFX_SMMU_CLOSE_CLOCK
    volatile U_PERI_CRG205 unTempSmmuValue;
#endif
    volatile U_PERI_CRG31 unTempValue;

    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(g_pstRegCrg);

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_cken = 0x0;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    mb();

#ifdef CONFIG_GFX_SMMU_CLOSE_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_cken = 0x0;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    mb();
#endif

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return;
}

/***************************************************************************************
* func         : DRV_JPEG_OnClock
* description  : open the jpeg clock
                 CNcomment: ��jpegʱ�� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID DRV_JPEG_OnClock(HI_VOID)
{
    HI_S32 s32Cnt = 0;
 #ifdef CONFIG_GFX_MMU_CLOCK
    volatile U_PERI_CRG205 unTempSmmuValue;
 #endif
    volatile U_PERI_CRG31 unTempValue;

    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(g_pstRegCrg);

#ifdef CONFIG_GFX_MMU_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_cken = 0x1;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    mb();

    s32Cnt = 0;
    do
    {
        s32Cnt++;
        unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
        if (0x1 == unTempValue.bits.jpgd_cken)
        {
            break;
        }
    }while(s32Cnt < 10);
    s32Cnt = 0;
#endif

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_cken  = 0x1;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    mb();

    do
    {
        s32Cnt++;
        unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
        if (0x1 == unTempValue.bits.jpgd_cken)
        {
            break;
        }
    }while(s32Cnt < 10);

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return;
}

#ifndef CONFIG_GFX_BVT_SDK
/***************************************************************************************
* func          : JPGE_DRV_Suspend
* description   : get the suspend signale.
                  CNcomment: �յ������ź� CNend\n
* param[in]     : *pdev
* param[in]     : state
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
***************************************************************************************/
HI_S32 JPGE_DRV_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
#ifdef CONFIG_JPEG_SUSPEND
    HI_S32 Ret  = 0;
#endif
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    HI_UNUSED(pdev);
    HI_UNUSED(state);

    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev,HI_FAILURE);

#ifdef CONFIG_JPEG_SUSPEND
    Ret  = down_interruptible(&s_SuspendMutex);
    if (0 != Ret)
    {
        HI_GFX_LOG_PrintFuncErr(down_interruptible,Ret);
        return HI_SUCCESS;
    }
    gs_bSuspend = HI_TRUE;

    if (HI_TRUE == s_pstruJpgOsrDev->bDecTask)
    {
       JPG_WaitDecTaskDone();
       s_pstruJpgOsrDev->bSuspendSignal = HI_TRUE;
    }
#endif

    DRV_JPEG_ResetReg();
    DRV_JPEG_OffClock();
    s_pstruJpgOsrDev->IntType = JPG_INTTYPE_FINISH;

    JPEG_TRACE("jpeg suspend ok\n");

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

    return HI_SUCCESS;
}


/***************************************************************************************
* func         : JPGE_DRV_Resume
* description  : get the resume signale.
                 CNcomment: �յ����������ź� CNend\n
* param[in]   : *pdev
* retval      : HI_SUCCESS �ɹ�
* retval      : HI_FAILURE ʧ��
* others:     : NA
***************************************************************************************/
HI_S32 JPGE_DRV_Resume(PM_BASEDEV_S *pdev)
{
    HI_UNUSED(pdev);
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

#ifdef CONFIG_JPEG_SUSPEND
    if (HI_TRUE == gs_bSuspend)
    {
       up(&s_SuspendMutex);
       gs_bSuspend = HI_FALSE;
    }

    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev,HI_FAILURE);
    if (HI_TRUE == s_pstruJpgOsrDev->bDecTask)
    {
        s_pstruJpgOsrDev->bResumeSignal  = HI_TRUE;
    }
#endif

    DRV_JPEG_OnClock();
    DRV_JPEG_CancelReset();

    JPEG_TRACE("jpeg resume ok\n");

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

    return HI_SUCCESS;
}

static JPEG_EXPORT_FUNC_S s_JpegExportFuncs =
{
    .pfnJpegModInit      = JPEG_DRV_ModInit,
    .pfnJpegModExit      = JPEG_DRV_ModExit,
    .pfnJpegSuspend      = JPGE_DRV_Suspend,
    .pfnJpegResume       = JPGE_DRV_Resume,
#ifndef CONFIG_JPEG_UT_UNSUPPORT
    .pfnJpegOsrGetIntStatus  = JPEG_DRV_GetIntStatusValue,
    .pfnJpegHalReadReg       = jpeg_reg_read,
    .pfnJpegHalWriteReg      = jpeg_reg_write,
    .pfnJpegHalGetIntStatus  = DRV_JPEG_GetIntStatus,
#endif
};
#endif

static HI_S32 DRV_JPEG_Open(struct inode *inode, struct file *file)
{
     HI_S32 s32Ret = HI_SUCCESS;
     HI_ULONG LockFlag = 0;
     if (HI_TRUE == gs_JpegDebugUnf)
     {
         HI_GFX_UNF_FuncBeg();
     }
     else if (HI_TRUE == gs_JpegDebugInterApi)
     {
         HI_GFX_LOG_FuncBeg();
     }

     HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

     HI_UNUSED(inode);
     HI_UNUSED(file);
     CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev, HI_FAILURE);

#ifdef CONFIG_JPEG_PROC_ENABLE
     JPEG_PROC_SetPthreadNum(s_pstruJpgOsrDev->SystemAbnormalTimes);
     JPEG_PROC_SetDecLockTimes(s_pstruJpgOsrDev->LockCnt);
#endif

     spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);
     if (   ((HI_TRUE == s_pstruJpgOsrDev->bLock) || (0 != s_pstruJpgOsrDev->OpenTimes))
         && (s_pstruJpgOsrDev->SystemAbnormalTimes <= CONFIG_JPEG_FIND_SYSTEM_ABNORMAL_TIMES))
     {
         s_pstruJpgOsrDev->SystemAbnormalTimes++;
         spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         return HI_FAILURE;
     }
     (s_pstruJpgOsrDev->OpenTimes)++;
     s_pstruJpgOsrDev->SystemAbnormalTimes = 0;
     spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);

     /** waite 2s, if long time wiil product anr problem **/
     s32Ret = wait_event_interruptible_timeout(s_pstruJpgOsrDev->QWaitMutex,HI_FALSE == s_pstruJpgOsrDev->bLock,2000 * HZ/1000);
     HI_UNUSED(s32Ret);
     if (HI_TRUE == s_pstruJpgOsrDev->bLock)
     {
        JPEG_TRACE("warning: ++++++++open state block %d\n",s_pstruJpgOsrDev->bLock);
     }

     if (s_pstruJpgOsrDev->OpenTimes > 1)
     {
        JPEG_TRACE("warning: ++++++++has been open times %d\n",s_pstruJpgOsrDev->OpenTimes);
     }

     if (s32Ret <= 0)
     {
         DRV_JPEG_ResetReg();
         DRV_JPEG_CancelReset();
         JPEG_DRV_UnLock(JPG_INTTYPE_ERROR);
         HI_GFX_LOG_PrintFuncErr(wait_event_interruptible_timeout,s32Ret);
         return HI_FAILURE;
     }

#ifdef CONFIG_JPEG_PROC_ENABLE
     JPEG_PROC_SetOpenDevCnt(1);
#endif

     spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);
     s_pstruJpgOsrDev->bEnableMap = HI_FALSE;
     spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);

     HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

     return HI_SUCCESS;
}

static HI_S32 DRV_JPEG_Close( struct inode *inode, struct file *file)
{
    HI_ULONG LockFlag = 0;
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    HI_UNUSED(inode);
    HI_UNUSED(file);
#ifdef CONFIG_JPEG_PROC_ENABLE
    JPEG_PROC_SetOpenDevCnt(-1);
#endif

    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev, HI_FAILURE);

    spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);
    if (0 == s_pstruJpgOsrDev->OpenTimes)
    {
       spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);
       HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
       if (HI_TRUE == gs_JpegDebugUnf)
       {
          HI_GFX_UNF_FuncEnd();
       }
       else if (HI_TRUE == gs_JpegDebugInterApi)
       {
          HI_GFX_LOG_FuncEnd();
       }
       return HI_SUCCESS;
    }
    spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);

    JPEG_DRV_UnLock(JPG_INTTYPE_ERROR);

    spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);
    (s_pstruJpgOsrDev->OpenTimes)--;
    spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
    if (HI_TRUE == gs_JpegDebugUnf)
    {
       HI_GFX_UNF_FuncEnd();
    }
    else if (HI_TRUE == gs_JpegDebugInterApi)
    {
       HI_GFX_LOG_FuncEnd();
    }

    return HI_SUCCESS;
}

static inline int jpeg_valid_mmap_phys_addr_range(unsigned long pfn, size_t size)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
}

static HI_S32 DRV_JPEG_Mmap(struct file * filp, struct vm_area_struct *vma)
{
    HI_U32 Size = 0;
    HI_U32 Phys = 0;
    HI_U64 u64BaseAddr = JPGD_REG_BASEADDR;
    HI_U32 u32Length   = 0;
    HI_UNUSED(filp);

    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    if (HI_FALSE == s_pstruJpgOsrDev->bEnableMap)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return -EINVAL;
    }
    s_pstruJpgOsrDev->bEnableMap = HI_FALSE;

    u32Length = (JPGD_REG_LENGTH + 4096 - 1) & (~(4096 - 1));

    if (NULL == vma)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return -EINVAL;
    }

    Size = vma->vm_end - vma->vm_start;
    if (Size > u32Length)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return -EINVAL;
    }

    /**<--check valid_mmap_phys_addr_range() >**/
    if (!jpeg_valid_mmap_phys_addr_range(vma->vm_pgoff, Size))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return EINVAL;
    }

    Phys = (u64BaseAddr >> PAGE_SHIFT);
    vma->vm_flags |= VM_LOCKED | VM_IO;

    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    if (remap_pfn_range(vma, vma->vm_start, Phys, vma->vm_end - vma->vm_start,vma->vm_page_prot))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return -EAGAIN;
    }

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 DRV_JPEG_IsrFunction(HI_S32 irq, HI_VOID * devId, struct pt_regs * ptrReg)
{
    HI_U32 IntType = 0;
    HI_S32 s32Ret  = HI_SUCCESS;
    HI_UNUSED(irq);
    HI_UNUSED(devId);
    HI_UNUSED(ptrReg);

    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev, HI_FAILURE);
    DRV_JPEG_GetIntStatus(&IntType);
    DRV_JPEG_ClearIntStatus(IntType);

    s32Ret = HI_GFX_SmmuIsr("HI_MOD_JPEG");
    if (HI_SUCCESS != s32Ret)
    {
       s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
    }

    if (IntType & 0x1)
    {
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_FINISH;
    }
    else if (IntType & 0x2)
    {
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_ERROR;
    }
    else if (IntType & 0x4)
    {
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_CONTINUE;
    }
    else if (IntType & 0x20)
    {
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_LOWDEALY;
    }
    else if (IntType & 0x40)
    {
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_STREAM_ERROR;
    }
    else
    {
        /** nothing to do **/
    }

    wake_up_interruptible(&s_pstruJpgOsrDev->QWaitInt);

    return IRQ_HANDLED;
}

 /***************************************************************************************
 * func           : JPEG_DRV_ModExit
 * description    : remount the jpeg driver
                    CNcomment: ж���豸 CNend\n
 * param[in]      : *pOsrDev
 * retval         : NA
 * others:        : NA
 ***************************************************************************************/
HI_VOID JPEG_DRV_ModExit(HI_VOID)
{
    if (HI_FALSE == gs_bJpegDevInit)
    {
       return;
    }

    gs_bJpegDevInit = HI_FALSE;

#ifndef CONFIG_GFX_BVT_SDK
    HI_GFX_MODULE_UnRegister(HIGFX_JPGDEC_ID);
#endif

    HI_GFX_PM_UnRegister();

#ifdef CONFIG_JPEG_PROC_ENABLE
    JPEG_PROC_DInit();
#endif

    JPEG_HAL_DInit();

    osal_free_irq(JPGD_IRQ_NUM, JPEGNAME,(HI_VOID*)s_pstruJpgOsrDev);

    if (NULL != s_pstruJpgOsrDev)
    {
       HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID*)s_pstruJpgOsrDev);
    }
    s_pstruJpgOsrDev = HI_NULL;

    if (NULL != s_pJpegRegBase)
    {
       HI_GFX_REG_UNMAP((HI_VOID*)s_pJpegRegBase);
    }
    s_pJpegRegBase  = NULL;

    HI_GFX_UnMapSmmuReg();

    JPEG_DRV_ShowVersion(HI_FALSE);

    return;
}


/***************************************************************************************
* func         : JPEG_DRV_K_ModInit
* description  : build into kernel to mce, mce will call this function
                 CNcomment: ���뵽�ں��н���MCE����,MCE�л����������� CNend\n
* param[in]    : NA
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
* others:      : NA
***************************************************************************************/
HI_S32 JPEG_DRV_K_ModInit(HI_VOID)
{
     HI_S32 s32Ret = HI_SUCCESS;
     HI_U64 u64BaseAddr = JPGD_REG_BASEADDR;

     if (NULL != s_pstruJpgOsrDev)
     {
        return HI_SUCCESS;
     }

     HI_GFX_INIT_MUTEX(&s_JpegMutex);
     HI_GFX_INIT_MUTEX(&s_SuspendMutex);

     s_pJpegRegBase = (volatile HI_U32*)HI_GFX_REG_MAP(u64BaseAddr, JPGD_REG_LENGTH);
     CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pJpegRegBase, HI_FAILURE);

     JPEG_HAL_Init(s_pJpegRegBase);

#ifndef CONFIG_GFX_BVT_SDK
     s32Ret = HI_GFX_MODULE_Register(HIGFX_JPGDEC_ID, JPEGDEVNAME, &s_JpegExportFuncs);
     if (HI_SUCCESS != s32Ret)
     {
          JPEG_DRV_ModExit();
          return HI_FAILURE;
     }
#endif
     s_pstruJpgOsrDev = (JPG_OSRDEV_S *)HI_GFX_KMALLOC(HIGFX_JPGDEC_ID,sizeof(JPG_OSRDEV_S),GFP_KERNEL);
     if (HI_NULL == s_pstruJpgOsrDev)
     {
         JPEG_DRV_ModExit();
         return -ENOMEM;
     }
     HI_GFX_Memset(s_pstruJpgOsrDev, 0x0, sizeof(JPG_OSRDEV_S));

     s32Ret = osal_request_irq(JPGD_IRQ_NUM, (irq_handler_t)DRV_JPEG_IsrFunction, IRQF_SHARED, JPEGNAME, s_pstruJpgOsrDev);
     if (HI_SUCCESS != s32Ret)
     {
         JPEG_DRV_ModExit();
         return HI_FAILURE;
     }

     s32Ret = HI_GFX_SetIrq(HIGFX_JPGDEC_ID,JPGD_IRQ_NUM, JPEGNAME);
     if (HI_SUCCESS != s32Ret )
     {
         JPEG_DRV_ModExit();
         return HI_FAILURE;
     }

     s32Ret = HI_GFX_MapSmmuReg((HI_U32)(JPGD_MMU_REG_BASEADDR));
     if (HI_SUCCESS != s32Ret )
     {
         JPEG_DRV_ModExit();
         return HI_FAILURE;
     }

     init_waitqueue_head(&s_pstruJpgOsrDev->QWaitInt);
     init_waitqueue_head(&s_pstruJpgOsrDev->QWaitMutex);
     spin_lock_init(&s_pstruJpgOsrDev->DecLock);

     s_pstruJpgOsrDev->bLock     = HI_FALSE;
     s_pstruJpgOsrDev->LockCnt   = 0;
     s_pstruJpgOsrDev->OpenTimes = 0;

     return HI_SUCCESS;
}


static HI_VOID JPEG_ShowCmd(HI_VOID)
{
#if 0
    HI_PRINT("0x%x   /**<-- CMD_JPG_GETDEVICE                >**/\n",CMD_JPG_GETDEVICE);
    HI_PRINT("0x%x   /**<-- CMD_JPG_GETSUSPEND               >**/\n",CMD_JPG_GETSUSPEND);
    HI_PRINT("0x%x   /**<-- CMD_JPG_GETRESUME                >**/\n",CMD_JPG_GETRESUME);
    HI_PRINT("0x%x   /**<-- CMD_JPG_RESET                    >**/\n",CMD_JPG_RESET);
    HI_PRINT("0x%x   /**<-- CMD_JPG_CANCEL_RESET             >**/\n",CMD_JPG_CANCEL_RESET);
    HI_PRINT("0x%x   /**<-- CMD_JPG_GETINTSTATUS             >**/\n",CMD_JPG_GETINTSTATUS);
    HI_PRINT("0x%x   /**<-- CMD_JPG_GETRESUMEVALUE           >**/\n",CMD_JPG_GETRESUMEVALUE);
    HI_PRINT("0x%x   /**<-- CMD_JPG_LOWDELAY_LINEINFO        >**/\n",CMD_JPG_LOWDELAY_LINEINFO);
    HI_PRINT("0x%x   /**<-- CMD_JPG_COMPAT_LOWDELAY_LINEINFO >**/\n",CMD_JPG_COMPAT_LOWDELAY_LINEINFO);
#endif
   return;
}

/***************************************************************************************
* func         : JPEG_DRV_ModInit
* description  : when insmod the driver call this function
                 CNcomment: �����豸��ʼ�� CNend\n
* param[in]    : NA
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
* others:      : NA
***************************************************************************************/
HI_S32 JPEG_DRV_ModInit(HI_VOID)
{
     HI_S32 s32Ret = HI_FAILURE;

     if (HI_TRUE == gs_bJpegDevInit)
     {
        return HI_SUCCESS;
     }

 #ifndef HI_MCE_SUPPORT
     s32Ret = JPEG_DRV_K_ModInit();
     if (HI_SUCCESS != s32Ret)
     {
        return HI_FAILURE;
     }
 #endif

     s32Ret = HI_GFX_PM_Register();
     if (HI_SUCCESS != s32Ret)
     {
         JPEG_DRV_ModExit();
         return HI_FAILURE;
     }

 #ifdef CONFIG_JPEG_PROC_ENABLE
     s32Ret = JPEG_PROC_Init();
     if (HI_SUCCESS != s32Ret)
     {
         JPEG_DRV_ModExit();
         return HI_FAILURE;
     }
 #endif

     JPEG_DRV_ShowVersion(HI_TRUE);
     JPEG_ShowCmd();

     gs_bJpegDevInit = HI_TRUE;

     return HI_SUCCESS;
}


static inline HI_VOID JPEG_DRV_ShowVersion(HI_BOOL bLoad)
{
#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE) && defined(MODULE)
     if (HI_TRUE == bLoad)
     {
        GFX_Printk("Load hi_jpegdec.ko success.\t(%s)\n", VERSION_STRING);
     }
     else
     {
        GFX_Printk("UnLoad hi_jpegdec.ko success.\t(%s)\n", VERSION_STRING);
     }
#endif
     return;
}


/***************************************************************************************
 * func            : JPEG_DRV_Lock
 * description     : lock dec
                     CNcomment: ��״̬ CNend\n
 * retval          : HI_SUCCESS �ɹ�
 * retval          : HI_FAILURE ʧ��
 * others:         : NA
 ***************************************************************************************/
static inline HI_S32 JPEG_DRV_Lock(HI_VOID)
{
    HI_ULONG LockFlag = 0;
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    if (down_interruptible(&s_JpegMutex))
    {
        HI_GFX_LOG_PrintFuncErr(down_interruptible,HI_FAILURE);
        return HI_FAILURE;
    }

    if (NULL != s_pstruJpgOsrDev)
    {
       spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);
         (s_pstruJpgOsrDev->LockCnt)++;
         s_pstruJpgOsrDev->bLock = HI_TRUE;
       spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);
    }

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return HI_SUCCESS;
}

/***************************************************************************************
 * func           : JPEG_DRV_UnLock
 * description    : release dec mutex
                    CNcomment: �ͷŽ����ź��� CNend\n
 * param[in]      : eIntType : ����״̬
 * retval         : HI_SUCCESS �ɹ�
 * retval         : HI_FAILURE ʧ��
 * others:        : NA
 ***************************************************************************************/
static inline HI_VOID JPEG_DRV_UnLock(JPEG_INTTYPE_E eIntType)
{
    HI_ULONG LockFlag = 0;
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_NOVALUE(s_pstruJpgOsrDev);

    spin_lock_irqsave(&s_pstruJpgOsrDev->DecLock, LockFlag);

    if (HI_FALSE == s_pstruJpgOsrDev->bLock)
    {
        spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);
        HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
        return;
    }

    if ((JPG_INTTYPE_FINISH != eIntType) && (JPG_INTTYPE_ERROR != eIntType))
    {
        spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);
        HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
        return;
    }

    DRV_JPEG_ResetReg();
    DRV_JPEG_OffClock();

    up(&s_JpegMutex);

    (s_pstruJpgOsrDev->LockCnt)--;
    s_pstruJpgOsrDev->bLock = HI_FALSE;
    wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);

    spin_unlock_irqrestore(&s_pstruJpgOsrDev->DecLock, LockFlag);

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return;
}

/***************************************************************************************
 * func           : JPEG_DRV_GetIntStatusValue
 * description    : CNcomment: ��ȡ�ж�״̬ CNend\n
 * param[in]      : irq
 * param[in]      : * devId
 * param[in]      : * ptrReg
 * retval         : HI_SUCCESS �ɹ�
 * retval         : HI_FAILURE ʧ��
 * others:        : NA
 ***************************************************************************************/
static HI_S32 JPEG_DRV_GetIntStatusValue(JPEG_GETINTTYPE_S *pstIntType)
{
    JPEG_GETINTTYPE_S IntInfo = {0};
    HI_S32 Ret = 0;
    HI_S32 loop = 0;
    HI_U32 FirstCount = 1;
    HI_S32 IRQ_NUM    = JPGD_IRQ_NUM;
    HI_U32 u32StartTimeMs = 0;
    HI_U32 u32EndTimeMs   = 0;
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(pstIntType, HI_FAILURE);
    CHECK_JPEG_GREATER_RETURN(pstIntType->TimeOut,JPEG_INTTYPE_DELAY_TIME, HI_FAILURE);
    CHECK_JPEG_NULLPOINTER_RETURN_VALUE(s_pstruJpgOsrDev, HI_FAILURE);

    IntInfo.IntType = pstIntType->IntType;
    IntInfo.TimeOut = pstIntType->TimeOut;

    disable_irq(IRQ_NUM);

    if ((JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType) || (0 == IntInfo.TimeOut))
    {
        IntInfo.IntType = s_pstruJpgOsrDev->IntType;
        s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
        enable_irq(IRQ_NUM);

        pstIntType->IntType = IntInfo.IntType;
        HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
        return HI_SUCCESS;
    }

    enable_irq(IRQ_NUM);

    do
    {
        Ret = wait_event_interruptible_timeout(s_pstruJpgOsrDev->QWaitInt,
                                               JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType,
                                               IntInfo.TimeOut * HZ / 1000);

        if (Ret > 0 || (JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType))
        {
            disable_irq(IRQ_NUM);
            IntInfo.IntType = s_pstruJpgOsrDev->IntType;
            s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
            enable_irq(IRQ_NUM);
            break;
        }
        else if (-ERESTARTSYS == Ret)
        {
            if (FirstCount)
            {
                HI_GFX_GetTimeStamp(&u32StartTimeMs,NULL);
                FirstCount = 0;
                loop = 1;
            }
            else
            {
                HI_GFX_GetTimeStamp(&u32EndTimeMs,NULL);
                /** avoid dead lock **/
                loop = ((u32EndTimeMs - u32StartTimeMs) <  IntInfo.TimeOut)?1:0;
                /** check timeout **/
                if(!loop)
                {
                    HI_GFX_LOG_PrintErrCode(HI_FAILURE);
                    return HI_FAILURE;
                }
            }

        }
        else /** == 0(wait timeout) and others **/
        {
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            return HI_FAILURE;
        }

    }while(loop);

    pstIntType->IntType = IntInfo.IntType;

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

    return HI_SUCCESS;
}

static long jpg_osr_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 u8Cmd = _IOC_NR(Cmd);
    HI_UNUSED(file);
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    DRV_JPEG_CHECK_IOCTL_CMD(u8Cmd);

    if (NULL == gs_DrvJpegCtlFunc[u8Cmd].DrvJpegIoctlFunc)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (Cmd != gs_DrvJpegCtlFunc[u8Cmd].Cmd)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = gs_DrvJpegCtlFunc[u8Cmd].DrvJpegIoctlFunc(Arg);
    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
    return Ret;
}

#ifdef CONFIG_COMPAT
static long jpg_osr_compat_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg)
{
    HI_S32 Ret = HI_SUCCESS;
#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);
    HI_UNUSED(file);
    if (CMD_JPG_COMPAT_LOWDELAY_LINEINFO == Cmd)
    {
       Ret = JPEG_OSR_CompatLowdelayLineInfo(Arg);
       HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
       return Ret;
    }
#endif

    Ret = jpg_osr_ioctl(file,Cmd,Arg);
    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
    return Ret;
}
#endif

static inline HI_S32 JPEG_DRV_GetDevice(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    s32Ret = JPEG_DRV_Lock();
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(JPEG_DRV_Lock,HI_FAILURE);
        return HI_FAILURE;
    }

    DRV_JPEG_ResetReg();
    DRV_JPEG_OnClock();
    DRV_JPEG_CancelReset();

    if (NULL != s_pstruJpgOsrDev)
    {
       s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
       s_pstruJpgOsrDev->bEnableMap = HI_TRUE;
    }

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

    return HI_SUCCESS;
}


static HI_S32 JPEG_OSR_GetDevice(HI_ULONG arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNUSED(arg);
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    Ret = JPEG_DRV_GetDevice();
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintFuncErr(JPEG_DRV_GetDevice,HI_FAILURE);
       return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 JPEG_OSR_GetSuspend(HI_ULONG arg)
{
 #ifdef CONFIG_JPEG_SUSPEND
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    if ((0 == arg) || (NULL == s_pstruJpgOsrDev))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (copy_to_user((HI_VOID *)arg, (HI_VOID *)&(s_pstruJpgOsrDev->bSuspendSignal),sizeof(s_pstruJpgOsrDev->bSuspendSignal)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

#else
    HI_UNUSED(arg);
#endif
    return HI_SUCCESS;
}

static HI_S32 JPEG_OSR_GetResume(HI_ULONG arg)
{
#ifdef CONFIG_JPEG_SUSPEND
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

    if ((0 == arg) || (NULL == s_pstruJpgOsrDev))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (copy_to_user((HI_VOID *)arg, (HI_VOID *)&(s_pstruJpgOsrDev->bResumeSignal),sizeof(s_pstruJpgOsrDev->bResumeSignal)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
#else
    HI_UNUSED(arg);
#endif

    return HI_SUCCESS;
}

static HI_S32 JPEG_OSR_Reset(HI_ULONG arg)
{
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);
    HI_UNUSED(arg);
    DRV_JPEG_ResetReg();
    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
    return HI_SUCCESS;
}

static HI_S32 JPEG_OSR_CancelReset(HI_ULONG arg)
{
    HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);
    HI_UNUSED(arg);
    DRV_JPEG_CancelReset();
    HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
    return HI_SUCCESS;
}

static HI_S32 JPEG_OSR_GetIntStatus(HI_ULONG arg)
{
     HI_S32 Ret = HI_SUCCESS;
     JPEG_GETINTTYPE_S IntInfo = {0};
     HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

     if (0 == arg)
     {
         JPEG_DRV_UnLock(JPG_INTTYPE_ERROR);
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         return HI_FAILURE;
     }

     if (copy_from_user((HI_VOID *)&IntInfo, (HI_VOID *)arg, sizeof(JPEG_GETINTTYPE_S)))
     {
         JPEG_DRV_UnLock(JPG_INTTYPE_ERROR);
         HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
         return -EFAULT;
     }

     Ret = JPEG_DRV_GetIntStatusValue(&IntInfo);
     if (HI_SUCCESS != Ret)
     {
         IntInfo.IntType = JPG_INTTYPE_ERROR;
     }

     if (copy_to_user((HI_VOID *)arg, (HI_VOID *)(&IntInfo),sizeof(JPEG_GETINTTYPE_S)))
     {
         JPEG_DRV_UnLock(JPG_INTTYPE_ERROR);
         HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
         return -EFAULT;
     }

     JPEG_DRV_UnLock(IntInfo.IntType);

     HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);

     return HI_SUCCESS;
}


static HI_S32 JPEG_OSR_GetResumeValue(HI_ULONG arg)
{
 #ifdef CONFIG_JPEG_SUSPEND
     HI_JPG_SAVEINFO_S stSaveInfo = {0};
     HI_GFX_UNF_FuncEnter(gs_JpegDebugUnf);

     if (0 == arg)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         return -EFAULT;
     }

     JPG_GetResumeValue(&stSaveInfo);
     if (copy_to_user((HI_VOID *)arg, (HI_VOID *)(&stSaveInfo),sizeof(stSaveInfo)))
     {
         HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
         return -EFAULT;
     }

     if (NULL != s_pstruJpgOsrDev)
     {
        s_pstruJpgOsrDev->bSuspendSignal = HI_FALSE;
        s_pstruJpgOsrDev->bResumeSignal  = HI_FALSE;
     }
     HI_GFX_UNF_FuncExit(gs_JpegDebugUnf);
#else
     HI_UNUSED(arg);
#endif
     return HI_SUCCESS;
}

#if defined(CONFIG_JPEG_LOW_DELAY_SUPPORT) && defined(CONFIG_COMPAT)
static HI_S32 JPEG_OSR_CompatLowdelayLineInfo(HI_ULONG arg)
{
    HI_UNUSED(arg);
    return HI_SUCCESS;
}
#endif

static HI_S32 JPEG_OSR_LowdelayLineInfo(HI_ULONG arg)
{
     HI_UNUSED(arg);
     return HI_SUCCESS;
}

/*****************************************************************************************/
/*****************************************************************************************/
EXPORT_SYMBOL(JPEG_DRV_K_ModInit);

#ifdef MODULE
   module_init(JPEG_DRV_ModInit);
   module_exit(JPEG_DRV_ModExit);
#endif

#ifndef CONFIG_GFX_PROC_UNSUPPORT
    MODULE_DESCRIPTION("driver for the all jpeg");
    MODULE_AUTHOR("HISILICON");
    MODULE_LICENSE("GPL");
#else
    MODULE_DESCRIPTION("");
    MODULE_AUTHOR("");
    MODULE_LICENSE("GPL");
#endif
