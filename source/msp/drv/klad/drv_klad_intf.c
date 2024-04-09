/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_intf.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <linux/kthread.h>
#include "hi_common.h"
#include "hal_klad.h"
#include "hi_osal.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_drv_klad.h"
#include "drv_klad.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "hal_klad_reg.h"
#include "hi_kernel_adapt.h"

#ifdef HI_TEE_SUPPORT
#include "drv_tee_klad.h"
#endif

#include "drv_klad_basic.h"
#ifdef HI_ADVCA_COMMON_CA_SUPPORT
#include "drv_klad_common_ca.h"
#endif

#ifdef HI_ADVCA_C1_SUPPORT
#include "drv_klad_nagra.h"
#endif

#ifdef HI_ADVCA_C2_SUPPORT
#include "drv_klad_irdeto.h"
#endif

#ifdef HI_ADVCA_C6_SUPPORT
#include "drv_klad_verimatrix.h"
#endif

#ifdef HI_ADVCA_C3_SUPPORT
#include "drv_klad_conax.h"
#endif

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
#include "drv_klad_proc.h"
#endif
/******* proc function end   ********/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PAGE_NUM_SHIFT          0 /* it depends on how many pages can be maped, 0:one page, 1:two pages, 2:four pages, 3: eight pages */
#define KLAD_MAP_PAGE_NUM        (1ULL << PAGE_NUM_SHIFT)
#define KLAD_MAP_MASK            (((KLAD_MAP_PAGE_NUM) << PAGE_SHIFT) - 1)

static UMAP_DEVICE_S g_ca_dev;

static HI_S32 KLAD_Open(struct inode* inode, struct file* filp)
{
    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(inode);
    KLAD_CHECK_POINTER(filp);

    DRV_KLAD_MutexLock();
    filp->private_data = (void*)(unsigned long)task_tgid_nr(current);
    DRV_KLAD_MutexUnLock();

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 KLAD_Release(struct inode* inode, struct file* filp)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(inode);
    KLAD_CHECK_POINTER(filp);

    DRV_KLAD_MutexLock();
    ret = DRV_KLAD_Release(filp);
    DRV_KLAD_MutexUnLock();

    KLAD_FUNC_EXIT();
    return ret;
}

static int KLAD_PM_Resume(PM_BASEDEV_S* pdev)
{
    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(pdev);
    DRV_KLAD_SetSecEN();
    HI_PRINT("klad resume OK\n");
    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static int KLAD_PM_Suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    KLAD_CHECK_POINTER(pdev);
    HI_PRINT("klad suspend OK\n");
    return HI_SUCCESS;
}

static long KLAD_Ioctl(struct file* ffile, unsigned int cmd, unsigned long arg)
{
    KLAD_CHECK_POINTER(ffile);
    KLAD_CHECK_POINTER(ffile->f_path.dentry->d_inode);
    return (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, DRV_KLAD_Ioctl);
}

static int _valid_mmap_phys_addr_range(unsigned long pfn, size_t size, unsigned long reg_phy_mask)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (reg_phy_mask >> PAGE_SHIFT));
}

static HI_S32 KLAD_Mmap(struct file *file, struct vm_area_struct *vma)
{
    size_t size = vma->vm_end - vma->vm_start;

    /* Invalid register address of common  */
    if ((KL_BASE_ADDR >> PAGE_SHIFT) >> PAGE_NUM_SHIFT != vma->vm_pgoff >> PAGE_NUM_SHIFT)
    {
        HI_FATAL_KLAD("Invalid page frame, vm_page_prot[%#x]\n", vma->vm_pgoff);
        return -EINVAL;
    }

    /* Invalid register address or len of common */
    if (!_valid_mmap_phys_addr_range(vma->vm_pgoff, size, KL_BASE_ADDR | KLAD_MAP_MASK))
    {
        HI_FATAL_KLAD("invalid pgoff[%#x] or size[%#x]\n", vma->vm_pgoff, size);
        return -EINVAL;
    }

    vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff, size, vma->vm_page_prot);

    if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        HI_FATAL_KLAD("remap_pfn_range fail.\n");
        return -EAGAIN;
    }

    return HI_SUCCESS;
}

static struct file_operations ca_fpops =
{
    .owner = THIS_MODULE,
    .open = KLAD_Open,
    .unlocked_ioctl = KLAD_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = KLAD_Ioctl,
#endif
    .release = KLAD_Release,
    .mmap    = KLAD_Mmap,
};

static PM_BASEOPS_S ca_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = KLAD_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = KLAD_PM_Resume,
};

/*****************************************************************************
 Prototype    :
 Description  : Keyladder proc function register
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
static HI_S32 KLAD_ProcWrite(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
    return DRV_KLAD_ProcWrite(file, buf, count, ppos);
}

static HI_S32 KLAD_ProcRead(struct seq_file* p, HI_VOID* v)
{
    KLAD_CHECK_POINTER(p);
    KLAD_CHECK_POINTER(v);

    return DRV_KLAD_ProcRead(p, v);
}
#endif
/******* proc function end   ********/

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode init.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_S32 KLAD_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    DRV_PROC_EX_S proc_func = {0};
#endif
/******* proc function end  ********/

    KLAD_FUNC_ENTER();

    HAL_KLAD_RegisterMap();

    ret = DRV_KLAD_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_Init,ret);
        goto drv_klad_err;
    }
    ret = DRV_KLAD_BASIC_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_BASIC_Init,ret);
        goto basic_init_err;
    }

#ifdef HI_ADVCA_COMMON_CA_SUPPORT
    ret = DRV_KLAD_COMMON_CA_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_Init,ret);
        goto common_ca_init_err;
    }
#endif

#ifdef HI_ADVCA_C6_SUPPORT
    ret = DRV_KLAD_C6_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C6_Init,ret);
        goto c6_init_err;
    }
#endif

#ifdef HI_ADVCA_C1_SUPPORT
    ret = DRV_KLAD_C1_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C1_Init,ret);
        goto c1_init_err;
    }
#endif

#ifdef HI_ADVCA_C2_SUPPORT
    ret = DRV_KLAD_C2_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C2_Init,ret);
        goto c2_init_err;
    }
#endif

#ifdef HI_ADVCA_C3_SUPPORT
    ret = DRV_KLAD_C3_Init();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C3_Init,ret);
        goto c3_init_err;
    }
#endif
#ifdef HI_TEE_SUPPORT
    ret = DEV_KLAD_InitTeec();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_InitTeec,ret);
        goto teec_init_err;
    }
#endif

    HI_OSAL_Snprintf(g_ca_dev.devfs_name, sizeof(g_ca_dev.devfs_name), UMAP_DEVNAME_CA);
    g_ca_dev.minor  = UMAP_MIN_MINOR_CA;
    g_ca_dev.owner  = THIS_MODULE;
    g_ca_dev.fops   = &ca_fpops;
    g_ca_dev.drvops = &ca_drvops;

    ret = HI_DRV_DEV_Register(&g_ca_dev);
    if (ret < 0)
    {
        KLAD_PrintErrorFunc(HI_DRV_DEV_Register,ret);
        goto dev_register_err;
    }
/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    proc_func.fnRead = KLAD_ProcRead;
    proc_func.fnWrite = KLAD_ProcWrite;
    HI_DRV_PROC_AddModule(HI_MOD_CA, &proc_func, NULL);
#endif
/******* proc function end  ********/
#ifdef MODULE
    HI_PRINT("Load hi_advca.ko success.\t(%s)\n", VERSION_STRING);
#endif

    ret = HI_DRV_MODULE_Register(HI_ID_CA, "HI_KLAD", &s_KladExportFunctionList);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(HI_DRV_MODULE_Register,ret);
        goto module_register_err;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;

module_register_err:
    HI_DRV_MODULE_UnRegister(HI_ID_CA);

dev_register_err:
    HI_DRV_DEV_UnRegister(&g_ca_dev);

#ifdef HI_TEE_SUPPORT
teec_init_err:
    DEV_KLAD_DeInitTeec();
#endif

#ifdef HI_ADVCA_C3_SUPPORT
c3_init_err:
    DRV_KLAD_C3_Exit();
#endif
#ifdef HI_ADVCA_C2_SUPPORT
c2_init_err:
    DRV_KLAD_C2_Exit();
#endif
#ifdef HI_ADVCA_C1_SUPPORT
c1_init_err:
    DRV_KLAD_C1_Exit();
#endif

#ifdef HI_ADVCA_C6_SUPPORT
c6_init_err:
    DRV_KLAD_C6_Exit();
#endif

#ifdef HI_ADVCA_COMMON_CA_SUPPORT
common_ca_init_err:
    DRV_KLAD_COMMON_CA_Exit();
#endif

basic_init_err:
    DRV_KLAD_BASIC_Exit();

drv_klad_err:
    DRV_KLAD_Exit();
    HAL_KLAD_RegisterUnMap();
    KLAD_FUNC_EXIT();
    return HI_FAILURE;
}

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode exit.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_VOID KLAD_ModExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_BASIC_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_BASIC_Exit,ret);
    }

#ifdef HI_ADVCA_COMMON_CA_SUPPORT
    ret = DRV_KLAD_COMMON_CA_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_Exit,ret);
    }
#endif

#ifdef HI_ADVCA_C6_SUPPORT
    ret = DRV_KLAD_C6_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C6_Exit,ret);
    }
#endif

#ifdef HI_ADVCA_C1_SUPPORT
    ret = DRV_KLAD_C1_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C1_Exit,ret);
    }
#endif

#ifdef HI_ADVCA_C2_SUPPORT
    ret = DRV_KLAD_C2_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C2_Exit,ret);
    }
#endif

#ifdef HI_ADVCA_C3_SUPPORT
    ret = DRV_KLAD_C3_Exit();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_C3_Exit,ret);
    }
#endif
#ifdef HI_TEE_SUPPORT
    ret = DEV_KLAD_DeInitTeec();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_DeInitTeec,ret);
    }
#endif
/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    HI_DRV_PROC_RemoveModule(HI_MOD_CA);
#endif
/******* proc function end  ********/
    HI_DRV_DEV_UnRegister(&g_ca_dev);
    HI_DRV_MODULE_UnRegister(HI_ID_CA);

    HAL_KLAD_RegisterUnMap();

    DRV_KLAD_Exit();

    KLAD_FUNC_EXIT();
    return;
}

#ifdef MODULE
module_init(KLAD_ModInit);
module_exit(KLAD_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
