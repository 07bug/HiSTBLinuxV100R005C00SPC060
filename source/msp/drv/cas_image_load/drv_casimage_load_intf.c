/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_casimage_load_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_casimage.h"
#include "drv_casimage_ext.h"
#include <linux/uaccess.h>
#include "hi_kernel_adapt.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_drv_mem.h"
#include "hi_drv_struct.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

static UMAP_DEVICE_S   s_casiamge_load_umap_dev;

static struct file_operations casiamge_load_fops =
{
    .owner          = THIS_MODULE,
    .open           = HI_NULL,
    .unlocked_ioctl = HI_NULL,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = HI_NULL,
#endif
    .release        = HI_NULL,
};

int CASIMAGE_LOAD_PM_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    return HI_SUCCESS;
}

int CASIMAGE_LOAD_PM_Resume(PM_BASEDEV_S *pdev)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_CASIMAGE_LoadImage();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_CASIMAGE, "DRV_CASIMAGE_LoadImage failed, ret:%x\n", ret);
        return ret;
    }

    return HI_SUCCESS;
}

static PM_BASEOPS_S  casimage_load_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = CASIMAGE_LOAD_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = CASIMAGE_LOAD_PM_Resume,
};


HI_S32 CASIMAGE_LOAD_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    snprintf(s_casiamge_load_umap_dev.devfs_name, sizeof(UMAP_DEVNAME_CASIMAGE), UMAP_DEVNAME_CASIMAGE);
    s_casiamge_load_umap_dev.minor = UMAP_MIN_MINOR_CASIMAGE;
    s_casiamge_load_umap_dev.owner  = THIS_MODULE;
    s_casiamge_load_umap_dev.drvops = &casimage_load_drvops;
    s_casiamge_load_umap_dev.fops = &casiamge_load_fops;

    ret = HI_DRV_DEV_Register(&s_casiamge_load_umap_dev);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_CASIMAGE, "HI_DRV_DEV_Register failed, ret:%x\n", ret);
        goto ERROR;
    }

    ret = HI_DRV_MODULE_Register(HI_ID_CASIMAGE, HI_MOD_CASIMAGE, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_CASIMAGE, "HI_DRV_MODULE_Register failed, ret:%x\n", ret);
        goto DEV_DEINIT;
    }

    ret = DRV_CASIMAGE_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_CASIMAGE, "DRV_CASIMAGE_Init failed, ret:%x\n", ret);
        goto MODULE_DEINIT;
    }

    ret = DRV_CASIMAGE_LoadImage();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PRINT(HI_ID_CASIMAGE, "DRV_CASIMAGE_LoadImage failed, ret:%x\n", ret);
        goto CAS_DEINIT;
    }

#ifdef MODULE
    HI_PRINT("Load hi_casimage.ko success.  \t(%s)\n", VERSION_STRING);
#endif
    return HI_SUCCESS;

CAS_DEINIT:
    (HI_VOID)DRV_CASIMAGE_DeInit();
MODULE_DEINIT:
    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_CASIMAGE);
DEV_DEINIT:
    (HI_VOID)HI_DRV_DEV_UnRegister(&s_casiamge_load_umap_dev);
ERROR:
    return ret;
}

HI_VOID CASIMAGE_LOAD_DRV_ModExit(HI_VOID)
{
    DRV_CASIMAGE_DeInit();
    HI_DRV_DEV_UnRegister(&s_casiamge_load_umap_dev);
    HI_DRV_MODULE_UnRegister(HI_ID_CASIMAGE);
    return;
}

#ifdef MODULE
module_init(CASIMAGE_LOAD_DRV_ModInit);
module_exit(CASIMAGE_LOAD_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

