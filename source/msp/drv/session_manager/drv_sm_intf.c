/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sm_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#include "session_manager_debug.h"
#include "drv_sm_tee_func.h"
#include "linux/compat.h"
#include "linux/fs.h"
#include "hi_kernel_adapt.h"
#include "hi_type.h"
#include "hi_drv_dev.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "drv_sm_ioctl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

/***************************** Macro Definition ******************************/

#define SM_NAME "HI_SESSION_MANAGE"

/**************************** global variables ****************************/

static UMAP_DEVICE_S  s_session_manager_device;

HI_DECLARE_MUTEX(s_sm_mutex);

#define DRV_SM_LOCK()

#ifdef HI_PROC_SUPPORT

HI_S32 SM_ProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_S32 ret = HI_SUCCESS;

    SM_FUNC_ENTER();
    PROC_PRINT(p, "\n------------------Session manage status------------\n");
    SM_TEEC_PrintProc();
    SM_FUNC_EXIT();
    return ret;
}

static HI_VOID DRV_SM_ProcInit(HI_VOID)
{
    DRV_PROC_EX_S sm_proc = {0};

    sm_proc.fnRead   = SM_ProcRead;
    sm_proc.fnWrite  = HI_NULL;

    HI_DRV_PROC_AddModule(HI_MOD_SM, &sm_proc, NULL);
}

static HI_VOID DRV_SM_ProcDeInit(HI_VOID)
{
    SM_FUNC_ENTER();
    HI_DRV_PROC_RemoveModule(HI_MOD_SM);
    SM_FUNC_EXIT();
}

#endif


HI_S32 DRV_SM_Open(struct inode * inode, struct file * file)
{
    SM_FUNC_ENTER();
    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_SM_Close(struct inode * inode, struct file * file)
{
    SM_FUNC_ENTER();
    SM_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 SM_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *argp)
{
    HI_S32 ret = HI_FAILURE;

    SM_FUNC_ENTER();
    SM_CHECK_POINTER(argp);

    if (down_interruptible(&s_sm_mutex))
    {
        SM_PrintErrorFunc(down_interruptible, HI_FAILURE);
        return HI_FAILURE;
    }

    switch(cmd)
    {
        case CMD_SM_CREATE:
        {
            SM_CTL_CREATE_S *p = (SM_CTL_CREATE_S *)argp;

            ret = SM_TEEC_Create(&p->hCreate, &p->stSMAttr);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_Create, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_DESTORY:
        {
            SM_CTL_DESTROY_S *p = (SM_CTL_DESTROY_S *)argp;

            ret = SM_TEEC_Destroy(p->hSM);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_Destroy, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_ADD_RESOURCE:
        {
            SM_CTL_ADD_S *p = (SM_CTL_ADD_S *)argp;

            ret = SM_TEEC_Add(p->hSM, p->enModule, &p->stModule);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_Add, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_DEL_RESOURCE:
        {
            SM_CTL_DEL_S *p = (SM_CTL_DEL_S *)argp;

            ret = SM_TEEC_Del(p->hSM, p->enModule, &p->stModule);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_Del, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_SET_INTENT:
        {
            SM_CTL_INTENT_S *p = (SM_CTL_INTENT_S *)argp;

            ret = SM_TEEC_SetIntent(p->hSM, p->enIntent);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_SetIntent, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_GET_RESOURCE:
        {
            SM_CTL_MODULE_S *p = (SM_CTL_MODULE_S *)argp;
            ret = SM_TEEC_GetResource(p->enSrcModule, p->hSrcHandle, p->enModule, (HI_UNF_SM_MODULE_S *)&p->stModule, &p->u32ModuleNum);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_GetHandle, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_GET_SMHANDLE:
        {
            SM_CTL_SMHANDLE_S *p = (SM_CTL_SMHANDLE_S *)argp;
            ret = SM_TEEC_GetSMHandle(p->u32SessionID, &p->hHandle);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_GetSMHandle, ret);
                goto RET;
            }

            break;
        }
        case CMD_SM_GET_INTENT:
        {
            SM_CTL_INTENT_S *p = (SM_CTL_INTENT_S *) argp;
            ret = SM_TEEC_GetIntent(p->hSM, &p->enIntent);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(SM_TEEC_GetIntent, ret);
                goto RET;
            }
            break;
        }
        case CMD_SM_GET_RESOURCE_BYSM:
        {
            SM_CTL_MODULEBYSM_S *p = (SM_CTL_MODULEBYSM_S *) argp;
            ret = SM_TEEC_GetResourceBySM(p->hSM, p->enModule, p->stModule, &p->u32ModuleNum);
            if (HI_SUCCESS != ret)
            {
                SM_PrintErrorFunc(DRV_SM_GetResourceBySM, ret);
                goto RET;
            }
            break;
        }

        default:
        {
            SM_PrintErrorCode(HI_FAILURE);
            ret = HI_FAILURE;
            break;
        }
    }

    SM_FUNC_EXIT();
RET:
    up(&s_sm_mutex);
    return ret;
}

static long DRV_SM_Ioctl(struct file *ffile, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, SM_Ioctl);

    return ret;
}

static struct file_operations DRV_SM_Fops=
{
    .owner            = THIS_MODULE,
    .open             = DRV_SM_Open,
    .unlocked_ioctl   = DRV_SM_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl     = DRV_SM_Ioctl,
#endif
    .release          = DRV_SM_Close,
};

static HI_S32  DRV_SM_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_PRINT("SM suspend OK\n");
    return 0;
}

static HI_S32 DRV_SM_Resume(PM_BASEDEV_S *pdev)
{
    HI_PRINT("SM resume OK\n");
    return HI_SUCCESS;
}

static PM_BASEOPS_S sm_drvops = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = DRV_SM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = DRV_SM_Resume,
};

HI_S32 SM_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;

    strncpy(s_session_manager_device.devfs_name, UMAP_DEVNAME_SM, strlen(UMAP_DEVNAME_SM));
    s_session_manager_device.fops = &DRV_SM_Fops;
    s_session_manager_device.minor = UMAP_MIN_MINOR_SM;
    s_session_manager_device.owner  = THIS_MODULE;
    s_session_manager_device.drvops = &sm_drvops;

    ret = HI_DRV_MODULE_Register(HI_ID_SM, SM_NAME, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(HI_DRV_MODULE_Register, ret);
        goto out0;
    }

    if (HI_DRV_DEV_Register(&s_session_manager_device) < 0)
    {
        ret = HI_FAILURE;
        SM_PrintErrorFunc(HI_DRV_DEV_Register, ret);
        goto out1;
    }

    ret = SM_TEEC_Init();
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(SM_TEEC_Init, ret);
        goto out2;
    }
#ifdef HI_PROC_SUPPORT
    DRV_SM_ProcInit();
#endif

#ifdef MODULE
    HI_PRINT("Load hi_sm.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

out2:
    HI_DRV_DEV_UnRegister(&s_session_manager_device);
out1:
    HI_DRV_MODULE_UnRegister(HI_ID_SM);
out0:
    return ret;
}

HI_VOID SM_DRV_ModExit(HI_VOID)
{
#ifdef HI_PROC_SUPPORT
    DRV_SM_ProcDeInit();
#endif

    SM_TEEC_DeInit();
    HI_DRV_MODULE_UnRegister(HI_ID_SM);
    HI_DRV_DEV_UnRegister(&s_session_manager_device);

    return ;
}

#ifdef MODULE
module_init(SM_DRV_ModInit);
module_exit(SM_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

