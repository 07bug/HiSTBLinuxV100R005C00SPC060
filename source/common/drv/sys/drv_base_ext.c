/******************************************************************************

  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_base_ext.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/25
  Description   : common driver moudle define
******************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>

#include "hi_type.h"
#include "hi_drv_log.h"
#include "hi_drv_struct.h"
#include "hi_drv_sys.h"
#include "drv_log.h"
#include "hi_drv_proc.h"
#include "hi_drv_stat.h"
#include "drv_base_ext.h"
#include "drv_sys_ioctl.h"
#include "drv_stat_ioctl.h"
#include "hi_drv_module.h"
#include "hi_drv_mmz.h"
#include "hi_drv_userproc.h"
#include "hi_drv_dev.h"

static struct platform_device *hi_virt_dev = NULL;

int hi_get_irq_byname(char *name)
{
    struct resource* res = NULL;

    if (!hi_virt_dev)
    {
        HI_ERR_SYS("module %s is not registered.\n",name);
        return -1;
    }

    res = platform_get_resource_byname(hi_virt_dev, IORESOURCE_IRQ, name);
    if (!res)
    {
        HI_ERR_SYS("module %s  platform_get_resource_byname fail!\n", name);
        return -1;
    }

    return res->start;
}

static int hi_virt_drv_probe(struct platform_device *pdev)
{
    HI_PRINT("virtual device initialization.\n");
    hi_virt_dev = pdev;
    return 0;
}

static const struct of_device_id hi_virt_dev_match[] __maybe_unused = {
    { .compatible = "virt-device", },
    {},
};
MODULE_DEVICE_TABLE(of, hi_virt_dev_match);

struct platform_driver hi_virt_pltm_driver = {
    .probe  = hi_virt_drv_probe,
    .driver = {
        .name = "virt-device",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(hi_virt_dev_match),
    },
};

HI_S32 HI_DRV_CommonInit(HI_VOID)
{
    HI_S32 ret;

#ifndef MODULE
    ret = platform_driver_register(&hi_virt_pltm_driver);
    if (ret)
    {
        HI_ERR_SYS("register driver failed\n");
        return -1;
    }
#endif

    ret = HI_DRV_DEV_KInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("dev init failed\n");
        goto ErrExit_DEV;
    }

    ret = HI_DRV_REG_KInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("reg init failed\n");
        goto ErrorExit_REG;
    }

    ret = HI_DRV_LOG_KInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("log init failed\n");
        goto ErrExit_LOG;
    }

    ret = HI_DRV_STAT_KInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("stat init failed\n");
        goto ErrExit_STAT;
    }

    ret = HI_DRV_MMNGR_Init(HI_KMODULE_MAX_COUNT, HI_KMODULE_MEM_MAX_COUNT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("memory mng init failed\n");
        goto ErrExit_MMNGR;
    }

    ret = HI_DRV_PROC_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("proc init failed\n");
        goto ErrExit_PROC;
    }

    return HI_SUCCESS;

ErrExit_PROC:
    HI_DRV_MMNGR_Exit();

ErrExit_MMNGR:
    HI_DRV_STAT_KExit();

ErrExit_STAT:
    HI_DRV_LOG_KExit();

ErrExit_LOG:
    HI_DRV_REG_KExit();

ErrorExit_REG:
    HI_DRV_DEV_KExit();

ErrExit_DEV:
    return ret;
}

HI_VOID HI_DRV_CommonExit(HI_VOID)
{
    HI_DRV_PROC_Exit();

    HI_DRV_MMNGR_Exit();

    HI_DRV_STAT_KExit();

    HI_DRV_LOG_KExit();

    HI_DRV_REG_KExit();

    HI_DRV_DEV_KExit();

#ifndef MODULE
    platform_driver_unregister(&hi_virt_pltm_driver);
#endif

    return;
}

static int __INIT__ COMMON_DRV_ModInit(void)
{
    HI_S32 ret;

#ifdef MODULE
    ret = platform_driver_register(&hi_virt_pltm_driver);
    if (ret)
    {
        HI_ERR_SYS("register driver failed\n");
        return ret;
    }
#else
    ret = DRV_PM_ModInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("himedia init failed\n");
        return HI_FAILURE;
    }

    ret = DRV_MMZ_ModInit();
    if(HI_SUCCESS != ret)
    {
        HI_ERR_SYS("mmz init failed\n");
        goto ErrorExit_MMZ;
    }
#endif

#if !(defined(HI_MCE_SUPPORT) || defined(HI_KEYLED_CT1642_KERNEL_SUPPORT))
    ret = HI_DRV_CommonInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("common init failed\n");
        goto ErrorExit_Common;
    }
#endif

    ret = HI_DRV_LOG_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("log init failed\n");
        goto ErrorExit_LOG;
    }

    ret = HI_DRV_SYS_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("sys init failed\n");
        goto ErrorExit_SYS;
    }

    ret = HI_DRV_TEE_Common_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("tee common failed\n");
        goto ErrorExit_TEE_COMMON;
    }

    ret = HI_DRV_STAT_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("stat init failed\n");
        goto ErrorExit_STAT;
    }

    ret = MMNGR_DRV_ModInit(HI_KMODULE_MAX_COUNT, HI_KMODULE_MEM_MAX_COUNT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("memory mng init failed\n");
        goto ErrorExit_MMNGR;
    }

    ret = USRPROC_DRV_ModInit();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_SYS("userproc init failed\n");
        goto ErrorExit_USRPROC;
    }

#ifdef MODULE
    HI_PRINT("Load hi_common.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

ErrorExit_USRPROC:
    MMNGR_DRV_ModExit();

ErrorExit_MMNGR:
    HI_DRV_STAT_Exit();

ErrorExit_STAT:
    HI_DRV_SYS_Exit();

ErrorExit_TEE_COMMON:
    HI_DRV_TEE_Common_UnInit();

ErrorExit_SYS:
    HI_DRV_LOG_Exit();

ErrorExit_LOG:
#if !(defined(HI_MCE_SUPPORT) || defined(HI_KEYLED_CT1642_KERNEL_SUPPORT))
    HI_DRV_CommonExit();

ErrorExit_Common:
#endif

#ifndef MODULE
    DRV_MMZ_ModExit();

ErrorExit_MMZ:
    DRV_PM_ModExit();
#endif

    return HI_FAILURE;
}

#ifdef MODULE
static HI_VOID COMMON_DRV_ModExit(HI_VOID)
{
    USRPROC_DRV_ModExit();

    MMNGR_DRV_ModExit();

    HI_DRV_STAT_Exit();

    HI_DRV_TEE_Common_UnInit();

    HI_DRV_SYS_Exit();

    HI_DRV_LOG_Exit();

#if !(defined(HI_MCE_SUPPORT) || defined(HI_KEYLED_CT1642_KERNEL_SUPPORT))
    HI_DRV_CommonExit();
#endif

    platform_driver_unregister(&hi_virt_pltm_driver);

    HI_PRINT("remove hi_common.ko success.\n");

    return;
}
#endif

#ifdef MODULE
module_init(COMMON_DRV_ModInit);
module_exit(COMMON_DRV_ModExit);
#else
device_initcall(COMMON_DRV_ModInit);
#endif

MODULE_AUTHOR("HISILION");
MODULE_LICENSE("GPL");

