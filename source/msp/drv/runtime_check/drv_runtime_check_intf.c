/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_runtime_check.h"
#include <linux/delay.h>
#include <linux/uaccess.h>
#include "hi_kernel_adapt.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hi_error_mpi.h"
#include "hi_drv_proc.h"
#include "hi_drv_mem.h"
#include "hi_drv_struct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


static UMAP_DEVICE_S   g_runtime_check_umap_dev;

static struct file_operations runtime_check_fops =
{
    .owner          = THIS_MODULE,
    .open           = HI_NULL,
    .unlocked_ioctl = HI_NULL,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = HI_NULL,
#endif
    .release        = HI_NULL,
};

int RUNTIME_CHECK_PM_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    set_suspend_flag(HI_TRUE);

#ifdef HI_ROOTFS_RUNTIME_CHECK_ENABLE
    set_hash_calculate_flag(HI_TRUE);

    while (get_hash_calculate_flag()&& get_runtime_check_enable_flag())
    {
        udelay(1000);
    }
#endif

    delete_timer();
#endif

    HI_PRINT("RUNTIME_CHECK suspend ok \n");

    return HI_SUCCESS;
}

int RUNTIME_CHECK_PM_Resume(PM_BASEDEV_S *pdev)
{
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    set_suspend_flag(HI_FALSE);
    set_fisrt_copy_flag(HI_TRUE);
#else
    DRV_RUNTIME_CHECK_ConfigLPC();
#endif

    HI_PRINT("RUNTIME_CHECK resume ok \n");

    return HI_SUCCESS;
}

static PM_BASEOPS_S  runtime_check_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = RUNTIME_CHECK_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = RUNTIME_CHECK_PM_Resume,
};


HI_S32 RUNTIME_CHECK_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    snprintf(g_runtime_check_umap_dev.devfs_name, sizeof(UMAP_DEVNAME_RUNTIMECHECK), UMAP_DEVNAME_RUNTIMECHECK);
    g_runtime_check_umap_dev.minor = UMAP_MIN_MINOR_RUNTIMECHECK;
    g_runtime_check_umap_dev.owner  = THIS_MODULE;
    g_runtime_check_umap_dev.drvops = &runtime_check_drvops;
    g_runtime_check_umap_dev.fops = &runtime_check_fops;

    ret = HI_DRV_DEV_Register(&g_runtime_check_umap_dev);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_RUNTIME, "HI_DRV_DEV_Register failed, ret:%x\n", ret);
        return ret;
    }

    ret = HI_DRV_MODULE_Register(HI_ID_RUNTIME, HI_MOD_RUNTIMECHECK, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        (HI_VOID)HI_DRV_DEV_UnRegister(&g_runtime_check_umap_dev);
        HI_ERR_PRINT(HI_ID_RUNTIME, "HI_DRV_MODULE_Register failed, ret:%x\n", ret);
        return ret;
    }

    (HI_VOID)DRV_RUNTIME_CHECK_Init();

#ifdef MODULE
    HI_PRINT("Load hi_runtime.ko success.  \t(%s)\n", VERSION_STRING);
#endif
    return HI_SUCCESS;
}

HI_VOID RUNTIME_CHECK_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_runtime_check_umap_dev);
    HI_DRV_MODULE_UnRegister(HI_ID_RUNTIME);
    DRV_RUNTIME_CHECK_Exit();
    return;
}

#ifdef MODULE
module_init(RUNTIME_CHECK_DRV_ModInit);
module_exit(RUNTIME_CHECK_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

