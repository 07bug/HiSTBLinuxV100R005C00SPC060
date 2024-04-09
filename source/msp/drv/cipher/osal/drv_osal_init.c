/******************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_aead.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_cipher_ext.h"
#include "drv_symc.h"
#include "drv_hash.h"
#include "drv_osal_tee.h"

/************************ Internal Structure Definition *********************/

extern s32 crypto_ioctl(u32 cmd, HI_VOID *argp);
extern s32 crypto_entry(void);
extern s32 crypto_exit(void);
extern s32 crypto_release(void);
extern s32 crypto_recover_hdcp_key(void);

static UMAP_DEVICE_S    g_CipherDevice;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      link*/
/** @{*/  /** <!-- [link]*/

CIPHER_EXPORT_FUNC_S s_CipherExportFuncs =
{
    .pfnCipherCreateHandle      = HI_DRV_CIPHER_CreateHandle,
    .pfnCipherDestroyHandle     = HI_DRV_CIPHER_DestroyHandle,
    .pfnCipherConfigChn         = HI_DRV_CIPHER_ConfigChn,
    .pfnCipherEncrypt           = HI_DRV_CIPHER_Encrypt,
    .pfnCipherDecrypt           = HI_DRV_CIPHER_Decrypt,
    .pfnCipherGetRandomNumber   = HI_DRV_CIPHER_GetRandomNumber,
    .pfnCipherLoadHdcpKey       = HI_DRV_CIPHER_LoadHdcpKey,
    .pfnCipherSoftReset         = HI_DRV_CIPHER_SoftReset,
    .pfnCipherSetHdmiReadClk    = HI_DRV_CIPHER_SetHdmiReadClk,
    .pfnCipherHashStart         = HI_DRV_CIPHER_HashStart,
    .pfnCipherHashUpdate        = HI_DRV_CIPHER_HashUpdate,
    .pfnCipherHashFinish        = HI_DRV_CIPHER_HashFinish,
};

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
HI_S32 symc_proc_read(struct seq_file *p, HI_VOID *v)
{
    symc_chn_status status[8];
    int i = 0;
    s32 ret = HI_SUCCESS;

    PROC_PRINT(p, "\n------------------------------------------"
                  "CIPHER STATUS-------------------------------"
                  "--------------------------------------------"
                  "--------------------\n");
    PROC_PRINT(p, "Chnid   Status   Decrypt   Alg   Mode   KeyLen    "
                  "Addr in/out      KeyFrom  INT-RAW in/out  INT-EN "
                  "in/out INT_OCNTCFG    IVOUT\n");

    crypto_memset(status, sizeof(status), 0, sizeof(status));
    for(i = 0; i < 8; i++)
    {
        status[i].id = i;
    }

    ret = drv_symc_proc_status(status);
    if(HI_SUCCESS != ret)
    {
        PROC_PRINT(p, "CIPHER_ProcGetStatus failed!\n");
        return HI_FAILURE;
    }

    for(i=0; i< CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        PROC_PRINT(p, " %d       %s      %d      %s  %s    %03d    %08x/%08x   "
                      " %s           %d/%d            %d/%d        %08x     %s\n",
                        i,
                        status[i].open,
                        status[i].decrypt,
                        status[i].alg,
                        status[i].mode,
                        status[i].klen,
                        status[i].inaddr,
                        status[i].outaddr,
                        status[i].ksrc,
                        status[i].inraw,
                        status[i].outraw,
                        status[i].inten,
                        status[i].outen,
                        status[i].outintcnt,
                        status[i].iv);
    }

    return HI_SUCCESS;
}

HI_S32 symc_proc_write(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
    return count;
}

static HI_VOID symc_proc_init(HI_VOID)
{
    DRV_PROC_EX_S stProc = {0};

    stProc.fnRead   = symc_proc_read;
    stProc.fnWrite  = symc_proc_write;

    HI_DRV_PROC_AddModule(HI_MOD_CIPHER, &stProc, NULL);
}

static HI_VOID symc_proc_deinit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule(HI_MOD_CIPHER);
}
#endif
/******* proc function end ********/


static int hi_cipher_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    drv_symc_suspend();

#ifdef CHIP_HASH_SUPPORT
    drv_hash_suspend();
#endif

    HI_PRINT("CIPHER suspend OK\n");

    return HI_SUCCESS;
}

static int hi_cipher_resume(PM_BASEDEV_S *pdev)
{
    s32 ret = HI_SUCCESS;

    ret = drv_symc_resume();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

#ifdef CHIP_HASH_SUPPORT
    drv_hash_resume();
#endif

    ret = crypto_recover_hdcp_key();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    HI_PRINT("CIPHER resume OK\n");

    return HI_SUCCESS;
}

HI_S32 _crypto_ioctl(struct inode *inode, struct file *file,
                       HI_U32 cmd, HI_VOID *arg)
{
    return crypto_ioctl(cmd, arg);
}

static long hi_cipher_ioctl(struct file *ffile, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, _crypto_ioctl);

    return ret;
}

static s32 hi_cipher_release(struct inode * inode, struct file * file)
{
    return crypto_release();
}

static struct file_operations dev_cipher_fops=
{
    .owner            = THIS_MODULE,
    .open             = HI_NULL,
    .unlocked_ioctl   = hi_cipher_ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl     = hi_cipher_ioctl,
#endif
    .release          = hi_cipher_release,
};

static PM_BASEOPS_S cipher_drvops = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = hi_cipher_suspend,
    .suspend_late = NULL,
    .resume_early = hi_cipher_resume,
    .resume       = NULL,
};

HI_S32 CIPHER_DRV_ModInit(HI_VOID)
{
    s32 ret = HI_SUCCESS;

    snprintf(g_CipherDevice.devfs_name, sizeof(UMAP_DEVNAME_CIPHER), UMAP_DEVNAME_CIPHER);
    g_CipherDevice.fops = &dev_cipher_fops;
    g_CipherDevice.minor = UMAP_MIN_MINOR_CIPHER;
    g_CipherDevice.owner  = THIS_MODULE;
    g_CipherDevice.drvops = &cipher_drvops;

    if (HI_DRV_DEV_Register(&g_CipherDevice) < 0)
    {
        HI_LOG_PrintFuncErr(HI_DRV_DEV_Register, HI_FAILURE);
        return HI_FAILURE;
    }

    ret = HI_DRV_MODULE_Register(HI_ID_CIPHER, CIPHER_NAME, &s_CipherExportFuncs);
    if(HI_SUCCESS != ret)
    {
        HI_DRV_DEV_UnRegister(&g_CipherDevice);
        HI_LOG_PrintFuncErr(HI_DRV_MODULE_Register, ret);
        return ret;
    }

    ret = crypto_entry();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(crypto_entry, ret);
        goto error;
    }

    ret = drv_osal_tee_open_session();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_osal_tee_open_session, ret);
        (HI_VOID)crypto_exit();
        goto error;
    }

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    symc_proc_init();
#endif
/******* proc function end ********/

#ifdef MODULE
    HI_PRINT("Load hi_cipher.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

error:
    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_CIPHER);
    (HI_VOID)HI_DRV_DEV_UnRegister(&g_CipherDevice);

    return ret;
}

HI_VOID CIPHER_DRV_ModExit(HI_VOID)
{

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    symc_proc_deinit();
#endif
/******* proc function end ********/

    HI_DRV_DEV_UnRegister(&g_CipherDevice);
    (HI_VOID)crypto_exit();
    (HI_VOID)drv_osal_tee_close_session();
    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_CIPHER);
    HI_DRV_MODULE_UnRegister(HI_ID_CIPHER);

    return ;
}

#ifdef MODULE
module_init(CIPHER_DRV_ModInit);
module_exit(CIPHER_DRV_ModExit);
#endif

MODULE_AUTHOR("Hi3720 MPP GRP");
MODULE_LICENSE("GPL");

/** @}*/  /** <!-- ==== Structure Definition end ====*/
