/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name           : png_osr.c
Version             : Initial Draft
Author              :
Created             : 2018/01/01
Description         : implemention of PNG ioctl
Function List       :


History             :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
**************************************************************************************************/
#include <linux/version.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include "hi_kernel_adapt.h"
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "hi_drv_struct.h"
#include "hi_drv_png.h"
#include "png_hal.h"
#include "png_osires.h"
#include "png_osi.h"
#include "png_proc.h"
#include "png_define.h"
#include "hi_png_config.h"
#include "drv_png_ext.h"

#include "hi_gfx_comm_k.h"
#include "hi_gfx_sys_k.h"


#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)

#define PNGNAME "HI_PNG"
extern HI_S32 PngOsiInit(HI_VOID);
extern HI_S32 PngOsiDeinit(HI_VOID);
extern HI_VOID PngOsiIntHandle(HI_U32 u32Int);
extern HI_S32 PngOsiSuspend(HI_VOID);
extern HI_S32 pngOsiResume(HI_VOID);
HI_BOOL gs_PngDebugInterApi = HI_FALSE;
HI_BOOL gs_PngDebugUnf = HI_FALSE;

static long png_ioctl(struct file  *ffile, unsigned int  cmd, unsigned long arg);

static HI_S32 png_open(struct inode *finode, struct file  *ffile);
static HI_S32 png_close(struct inode *finode, struct file  *ffile);
static HI_S32 png_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state);
static HI_S32 png_pm_resume(PM_BASEDEV_S *pdev);
DECLARE_GFX_NODE("hi_png", png_open, png_close, NULL, png_ioctl, png_ioctl, png_pm_suspend, png_pm_resume);

static PNG_EXPORT_FUNC_S s_PngExportFuncs =
{
    .pfnPngModInit  = PNG_DRV_ModInit,
    .pfnPngModExit  = PNG_DRV_ModExit,
    .pfnPngSuspend  = png_pm_suspend,
    .pfnPngResume   = png_pm_resume,
};

static HI_S32 png_isr(int irq, void *dev_id)
{
    HI_U32 u32IntValue;
    HI_UNUSED(irq);
    HI_UNUSED(dev_id);

    u32IntValue = PngHalGetIntStatus();

    PngOsiIntHandle(u32IntValue);

    return IRQ_HANDLED;
}

HI_VOID PNG_DRV_ModExit(void);

#ifndef CONFIG_PNG_VERSION_DISABLE
static HI_VOID HI_GFX_ShowVersionK(void)
{
#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE) && defined(MODULE)
    GFX_Printk("Load hi_png.ko success.\t\t(%s)\n", VERSION_STRING);
#endif
    return;
}
#endif

static HI_VOID PNG_ShowCmd(HI_VOID)
{
#if 0
    HI_PRINT("0x%x  /**<-- PNG_CREATE_DECODER                >**/\n",PNG_CREATE_DECODER);
    HI_PRINT("0x%x  /**<-- PNG_DESTROY_DECODER               >**/\n",PNG_DESTROY_DECODER);
    HI_PRINT("0x%x  /**<-- PNG_ALLOC_BUF                     >**/\n",PNG_ALLOC_BUF);
    HI_PRINT("0x%x  /**<-- PNG_RELEASE_BUF                   >**/\n",PNG_RELEASE_BUF);
    HI_PRINT("0x%x  /**<-- PNG_SET_STREAMLEN                 >**/\n",PNG_SET_STREAMLEN);
    HI_PRINT("0x%x  /**<-- PNG_GET_STREAMLEN                 >**/\n",PNG_GET_STREAMLEN);
    HI_PRINT("0x%x  /**<-- PNG_DECODE                        >**/\n",PNG_DECODE);
    HI_PRINT("0x%x  /**<-- PNG_GET_DECRESULT                 >**/\n",PNG_GET_DECRESULT);
#endif
   return;
}

/* module init */
HI_S32 PNG_DRV_ModInit(void)
{
    HI_S32 Ret = HI_SUCCESS;
    /* Hal init*/
    if (HI_SUCCESS != PngHalInit())
    {
        HI_GFX_LOG_PrintFuncErr(PngHalInit,HI_FAILURE);
        return HI_FAILURE;
    }

    /* Osires init*/
    if (HI_SUCCESS != PngOsiResInitHandle())
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiResInitHandle,HI_FAILURE);
        goto ERR3;
    }

    if (HI_SUCCESS != PngOsiInit())
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiInit,HI_FAILURE);
        goto ERR2;
    }

    /* register interrupt function*/
    if (HI_SUCCESS != osal_request_irq(PngHalGetIrqNum(), (irq_handler_t)png_isr, IRQF_PROBE_SHARED, "png", NULL))
    {
        HI_GFX_LOG_PrintFuncErr(osal_request_irq,HI_FAILURE);
        goto ERR1;
    }

    Ret = HI_GFX_SetIrq(HIGFX_PNG_ID, PngHalGetIrqNum(), "png");
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintFuncErr(HI_GFX_SetIrq,HI_FAILURE);
        PNG_DRV_ModExit();
        goto ERR1;
    }

    /* register device*/
    HI_GFX_PM_Register();
    /* proc init*/
#ifndef  CONFIG_GFX_PROC_UNSUPPORT
    PNG_ProcInit();
#endif

#ifndef CONFIG_PNG_VERSION_DISABLE
    HI_GFX_ShowVersionK();
#endif

    Ret = HI_GFX_MODULE_Register(HIGFX_PNG_ID, PNGNAME, &s_PngExportFuncs);
    if (HI_SUCCESS != Ret)
    {
        PNG_DRV_ModExit();
        HI_GFX_LOG_PrintFuncErr(HI_GFX_MODULE_Register,HI_FAILURE);
        goto ERR1;
    }

    PNG_ShowCmd();

    return HI_SUCCESS;

ERR1:
    PngOsiDeinit();
ERR2:
    PngOsiResDeinitHandle();
ERR3:
    PngHalDeinit();

    HI_GFX_LOG_PrintErrCode(HI_FAILURE);

    return HI_FAILURE;
}

HI_VOID PNG_DRV_ModExit(void)
{
#ifndef CONFIG_GFX_PROC_UNSUPPORT
    PNG_ProcCleanup();
#endif

    HI_GFX_PM_UnRegister();
    HI_GFX_MODULE_UnRegister(HIGFX_PNG_ID);

    osal_free_irq(PngHalGetIrqNum(), "png",  NULL);

    PngOsiDeinit();
    PngOsiResDeinitHandle();
    PngHalDeinit();

    return;
}

static HI_S32 png_open(struct inode *finode, struct file  *ffile)
{
    HI_S32 Ret = HI_SUCCESS;
    if (HI_TRUE == gs_PngDebugUnf)
    {
        HI_GFX_UNF_FuncBeg();
    }
    else if (HI_TRUE == gs_PngDebugInterApi)
    {
        HI_GFX_LOG_FuncBeg();
    }
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);
    HI_UNUSED(finode);
    HI_UNUSED(ffile);
    Ret = PngOsiOpen();
    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);
    return Ret;
}

static HI_S32 png_close(struct inode *finode, struct file  *ffile)
{
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);
    HI_UNUSED(finode);
    HI_UNUSED(ffile);
    PngOsiClose();
    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);
    if (HI_TRUE == gs_PngDebugUnf)
    {
        HI_GFX_UNF_FuncEnd();
    }
    else if (HI_TRUE == gs_PngDebugInterApi)
    {
        HI_GFX_LOG_FuncEnd();
    }
    return HI_SUCCESS;
}

static HI_S32 PngOsrCreateDecoder(void __user *argp)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PNG_HANDLE s32Handle = -1;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    s32Ret = PngOsiCreateDecoder(&s32Handle);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiCreateDecoder,HI_FAILURE);
        return s32Ret;
    }

    if (copy_to_user(argp, &s32Handle, sizeof(HI_PNG_HANDLE)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 PngOsrDestroyDecoder(void __user *argp)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_PNG_HANDLE s32Handle = -1;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    if (copy_from_user(&s32Handle, argp, sizeof(HI_PNG_HANDLE)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    Ret = PngOsiDestroyDecoder(s32Handle);

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return Ret;
}

static HI_S32 PngOsrAllocBuf(void __user *argp)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_GETBUF_CMD_S stCmd;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_GETBUF_CMD_S));

    if (copy_from_user(&stCmd, argp, sizeof(PNG_GETBUF_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    s32Ret = PngOsiAllocBuf(stCmd.s32Handle, &stCmd.stBuf);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiAllocBuf,HI_FAILURE);
        return s32Ret;
    }

    if (copy_to_user(argp, &stCmd, sizeof(PNG_GETBUF_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 PngOsrReleaseBuf(void __user *argp)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PNG_HANDLE s32Handle = 0;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    if (copy_from_user(&s32Handle, argp, sizeof(HI_PNG_HANDLE)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    s32Ret = PngOsiReleaseBuf(s32Handle);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiReleaseBuf,HI_FAILURE);
        return s32Ret;
    }

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 PngOsrSetStreamLen(void __user *argp)
{
    HI_S32 Ret = HI_SUCCESS;
    PNG_SETSTREAM_CMD_S stCmd;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_SETSTREAM_CMD_S));

    if (copy_from_user(&stCmd, argp, sizeof(PNG_SETSTREAM_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    Ret = PngOsiSetStreamLen(stCmd.s32Handle, stCmd.u32Phyaddr, stCmd.u32Len);

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return Ret;
}

static HI_S32 PngOsrGetStreamLen(void __user *argp)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_SETSTREAM_CMD_S stCmd;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_SETSTREAM_CMD_S));

    if (copy_from_user(&stCmd, argp, sizeof(PNG_SETSTREAM_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    s32Ret = PngOsiGetStreamLen(stCmd.s32Handle, stCmd.u32Phyaddr, &stCmd.u32Len);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiGetStreamLen,HI_FAILURE);
        return s32Ret;
    }

    if (copy_to_user(argp, &stCmd, sizeof(PNG_SETSTREAM_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return HI_SUCCESS;
}

static HI_S32 PngOsrDecode(void __user *argp)
{
    HI_S32 Ret = HI_SUCCESS;
    PNG_DECODE_CMD_S stCmd;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_DECODE_CMD_S));

    if (copy_from_user(&stCmd, argp, sizeof(PNG_DECODE_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    stCmd.stDecInfo.bSync = HI_TRUE;
    Ret = PngOsiDecode(stCmd.s32Handle, &stCmd.stDecInfo);

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return Ret;
}

static HI_S32 PngOsrGetResult(void __user *argp)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PNG_DECRESULT_CMD_S stCmd;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);

    HI_GFX_Memset(&stCmd, 0x0, sizeof(PNG_DECRESULT_CMD_S));

    if (copy_from_user(&stCmd, argp, sizeof(PNG_DECRESULT_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user,HI_FAILURE);
        return -EFAULT;
    }

    s32Ret = PngOsiGetResult(stCmd.s32Handle, stCmd.bBlock, &stCmd.eDecResult);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PngOsiGetResult,HI_FAILURE);
        return s32Ret;
    }

    if (copy_to_user(argp, &stCmd, sizeof(PNG_DECRESULT_CMD_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user,HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);

    return HI_SUCCESS;
}

/* ioctl function */
static long png_ioctl(struct file  *ffile, unsigned int  cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;

    if (NULL == argp)
    {
        PNG_ERROR("NULL param!\n");
        return -EFAULT;
    }

    switch (cmd)
    {
        case PNG_CREATE_DECODER:
        {
            return PngOsrCreateDecoder(argp);
        }
        case PNG_DESTROY_DECODER:
        {
            return PngOsrDestroyDecoder(argp);
        }
        case PNG_ALLOC_BUF:
        {
            return PngOsrAllocBuf(argp);
        }
        case PNG_RELEASE_BUF:
        {
            return PngOsrReleaseBuf(argp);
        }
        case PNG_SET_STREAMLEN:
        {
            return PngOsrSetStreamLen(argp);
        }
        case PNG_GET_STREAMLEN:
        {
            return PngOsrGetStreamLen(argp);
        }
        case PNG_DECODE:
        {
            return PngOsrDecode(argp);
        }
        case PNG_GET_DECRESULT:
        {
            return PngOsrGetResult(argp);
        }
        default:
        {
            return -EFAULT;
        }
    }
}

static HI_S32 png_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);
    HI_UNUSED(pdev);
    HI_UNUSED(state);
    Ret = PngOsiSuspend();
    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);
    return Ret;
}

static HI_S32 png_pm_resume(PM_BASEDEV_S *pdev)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_GFX_UNF_FuncEnter(gs_PngDebugUnf);
    HI_UNUSED(pdev);
    Ret = pngOsiResume();
    HI_GFX_UNF_FuncExit(gs_PngDebugUnf);
    return Ret;
}

#ifdef MODULE
module_init(PNG_DRV_ModInit);
module_exit(PNG_DRV_ModExit);
#endif

#ifndef CONFIG_GFX_PROC_UNSUPPORT
MODULE_DESCRIPTION("driver for the all png");
MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0.0.0");
#else
MODULE_DESCRIPTION("");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
MODULE_VERSION("");
#endif
