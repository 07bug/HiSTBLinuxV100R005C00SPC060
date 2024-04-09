/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_advca_intf.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <linux/jiffies.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/delay.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include "hi_common.h"
#include "hi_module.h"
#include "hi_unf_advca.h"
#include "hi_drv_cipher.h"
#include "hi_drv_otp.h"
#include "hi_drv_sys.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_drv_reg.h"
#include "drv_advca.h"
#include "drv_advca_ext.h"
#include "drv_otp_ext.h"
#include "drv_advca_ioctl.h"
#include "hi_drv_module.h"
#include "drv_advca_internal.h"
#include "drv_advca_external.h"
#include "drv_tee_advca.h"
#include "drv_tee_advca_agent.h"

atomic_t g_CaRefCnt = ATOMIC_INIT(0);

#define MUTEX_MAX_NUMBER 2
#define MUTEX_NAME_MAX_LEN 100

typedef struct CA_Sema
{
    struct semaphore CaSem;
    HI_BOOL isUsed;
} CA_Sema_S;

typedef struct CA_Mutex
{
    struct mutex  ca_oplock;
    CA_Sema_S ca_sema[MUTEX_MAX_NUMBER];
} CA_Mutex_S;

CA_Mutex_S g_ca_mutex;

static UMAP_DEVICE_S caUmapDev;

extern HI_S32  DRV_ADVCA_ModeInit_0(HI_VOID);
extern HI_VOID DRV_ADVCA_ModeExit_0(HI_VOID);
extern int DRV_ADVCA_Open(struct inode* inode, struct file* filp);
extern int DRV_ADVCA_Release(struct inode* inode, struct file* filp);
extern OTP_EXPORT_FUNC_S* g_pOTPExportFunctionList;

#define CA_BASE     0x10000000

HI_S32 CA_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, void* arg);

HI_S32 ca_atomic_read(HI_U32* pu32Value)
{
    if (NULL == pu32Value)
    {
        HI_FATAL_CA("Error! Null pointer input in ca atomic read!\n");
        return HI_FAILURE;
    }

    *pu32Value = atomic_read(&g_CaRefCnt);

    return HI_SUCCESS;
}

HI_S32 ca_atomic_dec_return(HI_U32* pu32Value)
{
    if (NULL == pu32Value)
    {
        HI_FATAL_CA("Error! Null pointer input in ca atomic read!\n");
        return HI_FAILURE;
    }

    *pu32Value = atomic_dec_return(&g_CaRefCnt);

    return HI_SUCCESS;
}

HI_S32 ca_atomic_inc_return(HI_U32* pu32Value)
{
    if (NULL == pu32Value)
    {
        HI_FATAL_CA("Error! Null pointer input in ca atomic inc return!\n");
        return HI_FAILURE;
    }

    *pu32Value = atomic_inc_return(&g_CaRefCnt);
    return HI_SUCCESS;
}

HI_S32 ca_down_interruptible(HI_U32* pu32Value)
{
    struct semaphore* pCaSem = NULL;

    pCaSem = (struct semaphore*)pu32Value;
    if (NULL == pCaSem)
    {
        return HI_FAILURE;
    }

    if (down_interruptible(pCaSem))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 ca_down_trylock(HI_U32* pu32Value)
{
    HI_S32 s32Ret = 0;
    struct semaphore* pCaSem = NULL;

    pCaSem = (struct semaphore*)pu32Value;
    if (NULL == pCaSem)
    {
        return HI_FAILURE;
    }

    s32Ret = down_trylock(pCaSem);
    if (0 != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID ca_up(HI_U32* pu32Value)
{
    struct semaphore* pCaSem = NULL;

    pCaSem = (struct semaphore*)pu32Value;
    if (NULL == pCaSem)
    {
        return ;
    }

    up(pCaSem);
    return ;
}

HI_VOID ca_initMutex(HI_U32* pu32Value)
{
    struct semaphore* pCaSem = NULL;

    if (NULL == pu32Value)
    {
        HI_FATAL_CA("Invalid Input param, NULL pointer in ca_initMutex.\n");
        return;
    }

    pCaSem = (struct semaphore*)pu32Value;

    sema_init(pCaSem, 1);

    return;
}

HI_U32* ca_create_mutex(HI_VOID)
{
    HI_U8 i = 0;
    HI_U32* pu32Value = NULL;

    mutex_lock(&g_ca_mutex.ca_oplock);
    for (i = 0; i < MUTEX_MAX_NUMBER; i++)
    {
        if (g_ca_mutex.ca_sema[i].isUsed == HI_FALSE)
        {
            break;
        }
    }

    if (i < MUTEX_MAX_NUMBER)
    {
        pu32Value = (HI_U32*)&g_ca_mutex.ca_sema[i].CaSem;
        g_ca_mutex.ca_sema[i].isUsed = HI_TRUE;
    }
    else
    {
        HI_FATAL_CA("Error! fail to create ca mutex!\n");
        pu32Value = NULL;
    }
    mutex_unlock(&g_ca_mutex.ca_oplock);

    return pu32Value;
}

HI_VOID* ca_ioremap_nocache(HI_U32 u32Addr, HI_U32 u32Len)
{
    return ioremap_nocache(u32Addr, u32Len);
}

HI_VOID ca_iounmap(HI_VOID* pAddr)
{
    if (NULL == pAddr)
    {
        HI_ERR_CA("Invalid Input param\n");
        return;
    }
    iounmap(pAddr);
    return;
}

HI_VOID ca_msleep(HI_U32 u32Time)
{
    msleep(u32Time);
    return;
}

HI_S32 ca_snprintf(char* buf, HI_U32 size, const char* fmt, ...)
{
    HI_S32 retval;
    va_list ap;

    va_start(ap, fmt);
    retval = vsnprintf(buf, size, fmt, ap);
    va_end(ap);

    return retval;
}

HI_VOID CA_readReg(HI_U8* addr, HI_U32* pu32Result)
{
    if ((NULL == addr) || (NULL == pu32Result))
    {
        HI_ERR_CA("Invalid Input param\n");
        return;
    }
    HI_REG_READ32(addr, *pu32Result);
    HI_INFO_CA("[r]0x%08x][v]0x%08x\n", addr, *pu32Result);
    return;
}

HI_VOID CA_writeReg(HI_U8* addr, HI_U32 u32Result)
{
    if (NULL == addr)
    {
        HI_ERR_CA("Invalid Input param\n");
        return;
    }
    HI_REG_WRITE32(addr, u32Result);
    HI_INFO_CA("[w]0x%08x][v]0x%08x\n", addr, u32Result);
    return;
}

HI_VOID CA_OTP_READ_REG(HI_U32 addr, HI_U32* pu32Result)
{
    HI_U8* pu8VirAddr = HI_NULL;

    if (NULL == pu32Result)
    {
        HI_ERR_OTP("Invalid Input param\n");
        return;
    }
    pu8VirAddr = (HI_U8*)ioremap_nocache(addr, 0x10);
    if (HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return;
    }
    HI_REG_READ32(pu8VirAddr, *pu32Result);
    iounmap(pu8VirAddr);
    return;
}

HI_VOID CA_OTP_WRITE_REG(HI_U32 addr, HI_U32 u32Result)
{
    HI_U8* pu8VirAddr = HI_NULL;

    pu8VirAddr = (HI_U8*)ioremap_nocache(addr, 0x10);
    if (HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return;
    }
    HI_REG_READ32(pu8VirAddr, u32Result);
    iounmap(pu8VirAddr);
    return;
}

/*
 *  Notice:
 *  For Linux 3.18:
 *  1. if we are ARM64 kernel, we must use the psci and atf to do the
 *  suspend/resume
 *  2. if we are ARM32 kernel, and if we have the ARM_PSCI support, we assume
 *  we have the atf(maybe corner case this is not always true)
 *
 *  For Linux 4.4 and higher:
 *  1. if we support CONFIG_ARM_PSCI_FW(this is not available in Linux 3.18),no
 *  matter we are ARM64 or ARM32, we must use the psci and atf to do the
 *  suspend/resume.(If it is not that case, we need adjust here)
 *
 */
#if !(defined(CONFIG_ARM_PSCI_FW) || defined(ARM64)|| defined(CONFIG_ARM_PSCI))
unsigned int ddr_wakeup_check_code[] =
{
#include DDR_WAKEUP_SRC
};

extern int (* ca_pm_suspend)(HI_VOID* sramAddr, int length);

int locate_ca_pm_suspend(HI_VOID* sramAddr, int length)
{
    if (NULL == sramAddr)
    {
        HI_ERR_CA("Invalid Input param\n");
        return -1;
    }

    if (length <= sizeof (ddr_wakeup_check_code))
    {
        return -1;
    }

    memcpy(sramAddr, ddr_wakeup_check_code, sizeof (ddr_wakeup_check_code));

    return 0;
}
#endif

int ADVCA_PM_Resume(PM_BASEDEV_S* pdev)
{
#if   (defined(CHIP_TYPE_hi3798cv200) && !defined(HI_TEE_SUPPORT)) \
    || (defined(CHIP_TYPE_hi3798mv200) && !defined(HI_TEE_SUPPORT)) \
    || (defined(CHIP_TYPE_hi3798mv300) && !defined(HI_TEE_SUPPORT)) \
    || (defined(CHIP_TYPE_hi3798mv310) && !defined(HI_TEE_SUPPORT))
    DRV_ADVCA_WriteReg(CA_V300_KL_SEC_EN, CA_V300_KL_EN_MASK);
#endif

    HI_PRINT("ADVCA resume OK\n");
    return HI_SUCCESS;
}


int ADVCA_PM_Suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    HI_PRINT("ADVCA suspend OK\n");
/*
 *  Notice:
 *  For Linux 3.18:
 *  1. if we are ARM64 kernel, we must use the psci and atf to do the
 *  suspend/resume
 *  2. if we are ARM32 kernel, and if we have the ARM_PSCI support, we assume
 *  we have the atf(maybe corner case this is not always true)
 *
 *  For Linux 4.4 and higher:
 *  1. if we support CONFIG_ARM_PSCI_FW(this is not available in Linux 3.18),no
 *  matter we are ARM64 or ARM32, we must use the psci and atf to do the
 *  suspend/resume.(If it is not that case, we need adjust here)
 *
 */
#if !(defined(CONFIG_ARM_PSCI_FW) || defined(ARM64)|| defined(CONFIG_ARM_PSCI))
    ca_pm_suspend = locate_ca_pm_suspend;
#endif
    return HI_SUCCESS;
}

static long DRV_ADVCA_Ioctl(struct file* ffile, unsigned int cmd, unsigned long arg)
{
    long ret;

    ret = (long)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, CA_Ioctl);

    return ret;
}

static struct file_operations ca_fpops =
{
    .owner = THIS_MODULE,
    .open = DRV_ADVCA_Open,
    .release = DRV_ADVCA_Release,
    .unlocked_ioctl = DRV_ADVCA_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = DRV_ADVCA_Ioctl,
#endif
};

static PM_BASEOPS_S ca_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = ADVCA_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = ADVCA_PM_Resume,
};

/*****************************************************************************
 Prototype    :
 Description  : CA模块 proc 函数
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
extern HI_S32 DRV_ADVCA_GetChipVersion(HI_CHIP_TYPE_E* penChipType, HI_CHIP_VERSION_E* penChipVersion);

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
static HI_S32 DRV_ADVCA_ProcGetSCSStatus(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32SCSStatus = 0;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_SCSACTIVE, &u32SCSStatus);
    if (HI_SUCCESS != ret)
    {
        PROC_PRINT(p, "Get SCS Status failed!: 0x%x\n", ret);
        return ret;
    }

    if (1 == u32SCSStatus)
    {
        PROC_PRINT(p, "SCS(Secure Boot Activation): enabled\n");
    }
    else
    {
        PROC_PRINT(p, "SCS(Secure Boot Activation): not enabled\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetCAVendorType(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32VendorID = 0;
    CA_CMD_SUPPER_ID_S stSupperIDParam = {0};

    memset(&stSupperIDParam, 0, sizeof(stSupperIDParam));
    stSupperIDParam.enCmdChildID = CMD_CHILD_ID_GET_VENDOR_ID;
    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_SUPPER_ID, &stSupperIDParam);
    if (HI_SUCCESS != ret)
    {
        PROC_PRINT(p, "Get CA Vendor Type failed!: 0x%x\n", ret);
        return ret;
    }

    memcpy(&u32VendorID, stSupperIDParam.pu8ParamBuf, sizeof(u32VendorID));
    switch (u32VendorID)
    {
        case HI_UNF_ADVCA_NULL:
            PROC_PRINT(p, "CA vendor type: 0x%08x(NULL)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_NAGRA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Nagra)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_IRDETO:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Irdeto)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_CONAX:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Conax)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_SUMA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Suma)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_NOVEL:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Novel)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_VERIMATRIX:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Vermatrix)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_CTI:
            PROC_PRINT(p, "CA vendor type: 0x%08x(CTI)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_COMMONCA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(CommonCA)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_DCAS:
            PROC_PRINT(p, "CA vendor type: 0x%08x(DCAS)\n", u32VendorID);
            break;
        case HI_UNF_ADVCA_PANACCESS:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Panaccess)\n", u32VendorID);
            break;
        default:
            PROC_PRINT(p, "CA vendor type: 0x%08x(UnkownCA)\n", u32VendorID);
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetChipID(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    CA_OTP_ATTR_S stOtpAttr;
    HI_U32 index = 0;
    HI_U8 *ptr = NULL;

    memset(&stOtpAttr, 0, sizeof(stOtpAttr));

    stOtpAttr.enOtpFuseId = HI_UNF_ADVCA_OTP_CHIP_ID;
    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_OTP_FUSE, (HI_VOID*)&stOtpAttr);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("ca ioctl CMD_CA_GET_OTP_FUSE err:0x%x. \n", ret);
        return ret;
    }

    ptr = stOtpAttr.stOtpAttr.unOtpFuseAttr.stChipId.au8ChipId;
    PROC_PRINT(p, "Chip ID: ");
    for(index = 0; index < 8; index ++)
    {
        PROC_PRINT(p, "0x%02x ", ptr[index]);
    }
    PROC_PRINT(p, "\n");
    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetMSID(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32MarketID = 0;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_MARKETID, &u32MarketID);
    if ( HI_SUCCESS != ret )
    {
        PROC_PRINT(p, "Get Market ID failed!: 0x%x\n", ret);
        return ret;
    }

    PROC_PRINT(p, "Market ID: 0x%02x 0x%02x 0x%02x 0x%02x\n",
               ((HI_U8*)&u32MarketID)[3], ((HI_U8*)&u32MarketID)[2], ((HI_U8*)&u32MarketID)[1], ((HI_U8*)&u32MarketID)[0]);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetMSIDCheckEn(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bNeedCheck = HI_FALSE;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_BL_MSID_CHECK_EN, &bNeedCheck);
    if ( HI_SUCCESS != ret )
    {
        PROC_PRINT(p, "Get MSID Check En failed!: 0x%x\n", ret);
        return ret;
    }

    if (HI_TRUE == bNeedCheck)
    {
        PROC_PRINT(p, "MSID need to check\n");
    }
    else
    {
        PROC_PRINT(p, "MSID do not need to check\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetVersionID(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32VersionID = 0;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_VERSIONID, &u32VersionID);
    if ( HI_SUCCESS != ret )
    {
        PROC_PRINT(p, "Get Version ID failed!: 0x%x\n", ret);
        return ret;
    }

    PROC_PRINT(p, "Version ID: 0x%02x 0x%02x 0x%02x 0x%02x\n",
               ((HI_U8*)&u32VersionID)[3], ((HI_U8*)&u32VersionID)[2], ((HI_U8*)&u32VersionID)[1], ((HI_U8*)&u32VersionID)[0]);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetVersionIDCheckEn(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bNeedCheck = HI_FALSE;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_VERSION_CHECK_EN, &bNeedCheck);
    if ( HI_SUCCESS != ret )
    {
        PROC_PRINT(p, "Get Version ID Check En failed!: 0x%x\n", ret);
        return ret;
    }

    if (HI_TRUE == bNeedCheck)
    {
        PROC_PRINT(p, "Version ID need to check\n");
    }
    else
    {
        PROC_PRINT(p, "Version ID do not need to check\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetSecretKeyChecksumStatus(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_CHECKSUM_FLAG_U unChecksum;
    CA_CMD_SUPPER_ID_S stSupperIDParam = {0};

    unChecksum.u32 = 0;
    memset(&stSupperIDParam, 0, sizeof(stSupperIDParam));
    stSupperIDParam.enCmdChildID = CMD_CHILD_ID_GET_CHECKSUM_FLAG;
    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_SUPPER_ID, &stSupperIDParam);
    if (HI_SUCCESS != ret)
    {
        PROC_PRINT(p, "Get Secret Key Checksum Status failed!: 0x%x\n", ret);
        return ret;
    }

    memcpy(&unChecksum.u32, stSupperIDParam.pu8ParamBuf, sizeof(unChecksum.u32));
    PROC_PRINT(p, "CA secret key checksum flag: 0x%08x\n", unChecksum.u32);

    if (0 == unChecksum.bits.CSA2_RootKey)
    {
        PROC_PRINT(p, "--CSA2_RootKey verify:       failed\n");
    }
    else
    {
        PROC_PRINT(p, "--CSA2_RootKey verify:       success\n");
    }

    if (0 == unChecksum.bits.R2R_RootKey)
    {
        PROC_PRINT(p, "--R2R_RootKey verify:        failed\n");
    }
    else
    {
        PROC_PRINT(p, "--R2R_RootKey verify:        success\n");
    }

    if (0 == unChecksum.bits.SP_RootKey)
    {
        PROC_PRINT(p, "--SP_RootKey verify:         failed\n");
    }
    else
    {
        PROC_PRINT(p, "--SP_RootKey verify:         success\n");
    }

    if (0 == unChecksum.bits.CSA3_RootKey)
    {
        PROC_PRINT(p, "--CSA3_RootKey verify:       failed\n");
    }
    else
    {
        PROC_PRINT(p, "--CSA3_RootKey verify:       success\n");
    }

    if (0 == unChecksum.bits.ChipID_JTAGKey)
    {
        PROC_PRINT(p, "--ChipID_JTAGKey verify:     failed\n");
    }
    else
    {
        PROC_PRINT(p, "--ChipID_JTAGKey verify      success\n");
    }

    if (0 == unChecksum.bits.ESCK)
    {
        PROC_PRINT(p, "--ESCK verify:               failed\n");
    }
    else
    {
        PROC_PRINT(p, "--ESCK verify:               success\n");
    }

    if (0 == unChecksum.bits.BOOT_RootKey)
    {
        PROC_PRINT(p, "--BOOT_RootKey verify:       failed\n");
    }
    else
    {
        PROC_PRINT(p, "--BOOT_RootKey verify:       success\n");
    }

    if (0 == unChecksum.bits.MISC_RootKey)
    {
        PROC_PRINT(p, "--MISC_RootKey verify:       failed\n");
    }
    else
    {
        PROC_PRINT(p, "--MISC_RootKey verify:       success\n");
    }

    if (0 == unChecksum.bits.HDCP_RootKey)
    {
        PROC_PRINT(p, "--HDCP_RootKey verify:       failed\n");
    }
    else
    {
        PROC_PRINT(p, "--HDCP_RootKey verify:       success\n");
    }

    if (0 == unChecksum.bits.OEM_RootKey)
    {
        PROC_PRINT(p, "--OEM_RootKey verify:        failed\n");
    }
    else
    {
        PROC_PRINT(p, "--OEM_RootKey verify:        success\n");
    }

    if (0 == unChecksum.bits.STB_RootKey)
    {
        PROC_PRINT(p, "--STB_RootKey verify:        failed\n");
    }
    else
    {
        PROC_PRINT(p, "--STB_RootKey verify:        success\n");
    }

    if (0 == unChecksum.bits.CA_TA_RootKey)
    {
        PROC_PRINT(p, "--CA_TA_RootKey verify:      failed\n");
    }
    else
    {
        PROC_PRINT(p, "--CA_TA_RootKey verify:      success\n");
    }

    if (0 == unChecksum.bits.STB_TA_RootKey)
    {
        PROC_PRINT(p, "--STB_TA_RootKey verify:     failed\n");
    }
    else
    {
        PROC_PRINT(p, "--STB_TA_RootKey verify:     success\n");
    }

    if (0 == unChecksum.bits.TZ_JTAG_RootKey)
    {
        PROC_PRINT(p, "--TZ_JTAG_RootKey verify:    failed\n");
    }
    else
    {
        PROC_PRINT(p, "--TZ_JTAG_RootKey verify:     success\n");
    }

    if (0 == unChecksum.bits.SEC_STORE_RootKey)
    {
        PROC_PRINT(p, "--SEC_STORE_RootKey verify:   failed\n");
    }
    else
    {
        PROC_PRINT(p, "--SEC_STORE_RootKey verify:   success\n");
    }
    if (0 == unChecksum.bits.LP_RootKey)
    {
        PROC_PRINT(p, "--LP_RootKey verify:          failed\n");
    }
    else
    {
        PROC_PRINT(p, "--LP_RootKey verify:          success\n");
    }
    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_GetRSAKeyLockFlag(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32LockFlag = 0;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_RSA_KEY_LOCK, &u32LockFlag);
    if (HI_SUCCESS != ret)
    {
        PROC_PRINT(p, "Get rsa key lock flag failed!\n");
        return HI_FAILURE;
    }

    if ( 0 == u32LockFlag )
    {
        PROC_PRINT(p, "RSA key is not locked.\n");
    }
    else
    {
        PROC_PRINT(p, "RSA key is locked.\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetChipType(struct seq_file* p)
{
    HI_CHIP_TYPE_E      enChipType      = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   enChipVersion   = HI_CHIP_VERSION_BUTT;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    if ((HI_CHIP_TYPE_HI3798M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion))
    {
        PROC_PRINT(p, "Chipset type: Hi3798MV100\n");
    }
    else if ((HI_CHIP_TYPE_HI3796M == enChipType) && (HI_CHIP_VERSION_V100 == enChipVersion))
    {
        PROC_PRINT(p, "Chipset type: Hi3796MV100\n");
    }
    else
    {
        PROC_PRINT(p, "Chipset type: Unknown chip type\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetBootMode(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_FLASH_TYPE_E enBootMode = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
    HI_U32 u32BootSel = 0;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_BOOTMODE, &enBootMode);
    if (ret != HI_SUCCESS)
    {
        PROC_PRINT(p, "Get Boot Mode failed!: 0x%x\n", ret);
        return ret;
    }

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_BOOTSEL_CTRL, &u32BootSel);
    if (ret != HI_SUCCESS)
    {
        PROC_PRINT(p, "Get BootSel ctrl failed!: 0x%x\n", ret);
        return ret;
    }

    if (0 == u32BootSel)
    {
        PROC_PRINT(p, "boot mode is controlled by chipset pin\n");
        return HI_SUCCESS;
    }

    PROC_PRINT(p, "Boot Mode: %s\n", enBootMode == HI_UNF_ADVCA_FLASH_TYPE_SPI ? "SPI" :
               (enBootMode == HI_UNF_ADVCA_FLASH_TYPE_NAND ? "NAND" : (enBootMode == HI_UNF_ADVCA_FLASH_TYPE_EMMC ? "EMMC" :
                       (enBootMode == HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND ? "SPI_NAND" :
                        (enBootMode == HI_UNF_ADVCA_FLASH_TYPE_SD ? "SD" : "Unknow")))));

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetCWState(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bCWState = HI_FALSE;

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_STATHARDCWSEL, &bCWState);
    if (ret != HI_SUCCESS)
    {
        PROC_PRINT(p, "Get Hard CW Sel failed!: 0x%x\n", ret);
        return ret;
    }

    PROC_PRINT(p, "CW State: %s\n", bCWState == 1 ? "Hardware CW only" : "Software CW");

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetCAState(struct seq_file* p)
{
    HI_S32 ret = HI_SUCCESS;
    CA_CMD_SUPPER_ID_S stSupperIDParam = {0};
    HI_U32 u32CAState = 0;

    memset(&stSupperIDParam, 0, sizeof(stSupperIDParam));
    stSupperIDParam.enCmdChildID = CMD_CHILD_ID_GET_CASTATE;
    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_SUPPER_ID, &stSupperIDParam);
    if (ret != HI_SUCCESS)
    {
        PROC_PRINT(p, "Get CA Error State failed!: 0x%x\n", ret);
        return ret;
    }

    memcpy(&u32CAState, stSupperIDParam.pu8ParamBuf, sizeof(u32CAState));
    PROC_PRINT(p, "CA Error state: 0x%x\n", (u32CAState & 0xF));

    return HI_SUCCESS;
}

static HI_S32 ADVCA_DebugKey(struct seq_file* p, HI_U8 KeyData[16])
{
    HI_U8 index;

    for (index = 0; index < 16; index ++)
    {
        PROC_PRINT(p, "%02X ", KeyData[index]);
    }
    PROC_PRINT(p, "\n");
    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetCSA2KeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "CSA2 Key Ladder Stage: %d Level\n", g_CSA2Info.MaxLevel);
    if (g_CSA2Info.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "CSA2 Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "CSA2 Key Ladder Alg is TDES\n");
    }

    PROC_PRINT(p, "CSA2 Key Ladder ReadyStatusStage:0x%08x\n", g_CSA2Info.Keyladder_Ready);
    CAStatus.u32 = g_CSA2Info.Keyladder_Ready;
    if (CAStatus.bits.csa2_klad0_rdy == 0x01)
    {
        PROC_PRINT(p, "CSA2 Key Ladder klad0(ready) ");
    }
    else
    {
        PROC_PRINT(p, "CSA2 Key Ladder klad0(no ready) ");
    }

    if (CAStatus.bits.csa2_klad1_rdy == 0x01)
    {
        PROC_PRINT(p, "klad1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "klad1(no ready) ");
    }

    if (CAStatus.bits.csa2_klad2_rdy == 0x01)
    {
        PROC_PRINT(p, " klad2(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "klad2(no ready)\n");
    }

    for (index = 0; index < g_CSA2Info.MaxLevel; index ++)
    {
        PROC_PRINT(p, "CSA2 klad%d [time:0x%08x]:", index, g_CSA2Info.SessionKey_sec[index]);
        ADVCA_DebugKey(p, g_CSA2Info.SessionKey[index]);
    }

    //Now print the Even/Odd Key
    PROC_PRINT(p, "CSA2 Even  [time:0x%08x]:", g_CSA2Info.LastEvenKey_secTime);
    ADVCA_DebugKey(p, g_CSA2Info.LastEvenKey);
    PROC_PRINT(p, "CSA2 Odd   [time:0x%08x]:", g_CSA2Info.LastOddKey_secTime);
    ADVCA_DebugKey(p, g_CSA2Info.LastOddKey);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetR2RKeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "R2R Key Ladder Stage: %d Level\n", g_R2RInfo.MaxLevel);
    if (g_R2RInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "R2R Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "R2R Key Ladder Alg is TDES\n");
    }
    PROC_PRINT(p, "R2R Key Ladder ReadyStatusStage:0x%08x\n", g_R2RInfo.Keyladder_Ready);
    CAStatus.u32 = g_R2RInfo.Keyladder_Ready;
    if (CAStatus.bits.r2r_klad0_rdy == 0x01)
    {
        PROC_PRINT(p, "R2R Key Ladder klad0(ready) ");
    }
    else
    {
        PROC_PRINT(p, "R2R Key Ladder klad0(no ready) ");
    }

    if (CAStatus.bits.r2r_klad1_rdy == 0x01)
    {
        PROC_PRINT(p, "klad1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "klad1(no ready) ");
    }

    if (CAStatus.bits.r2r_klad2_rdy == 0x01)
    {
        PROC_PRINT(p, " klad2(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "klad2(no ready)\n");
    }

    for (index = 0; index < g_R2RInfo.MaxLevel; index ++)
    {
        PROC_PRINT(p, "R2R klad%d [time:0x%08x]:", index, g_R2RInfo.SessionKey_sec[index]);
        ADVCA_DebugKey(p, g_R2RInfo.SessionKey[index]);
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetCSA3KeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "CSA3 Key Ladder Stage: %d Level\n", g_CSA3Info.MaxLevel);
    if (g_CSA3Info.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "CSA3 Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "CSA3 Key Ladder Alg is TDES\n");
    }
    PROC_PRINT(p, "CSA3 Key Ladder ReadyStatusStage:0x%08x\n", g_CSA3Info.Keyladder_Ready);
    CAStatus.u32 = g_CSA3Info.Keyladder_Ready;
    if (CAStatus.bits.csa3_klad0_rdy == 0x01)
    {
        PROC_PRINT(p, "CSA3 Key Ladder klad0(ready) ");
    }
    else
    {
        PROC_PRINT(p, "CSA3 Key Ladder klad0(no ready) ");
    }

    if (CAStatus.bits.csa3_klad1_rdy == 0x01)
    {
        PROC_PRINT(p, "klad1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "klad1(no ready) ");
    }

    if (CAStatus.bits.csa3_klad2_rdy == 0x01)
    {
        PROC_PRINT(p, " klad2(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "klad2(no ready)\n");
    }

    for (index = 0; index < g_CSA3Info.MaxLevel; index ++)
    {
        PROC_PRINT(p, "CSA3 klad%d [time:0x%08x]:", index, g_CSA3Info.SessionKey_sec[index]);
        ADVCA_DebugKey(p, g_CSA3Info.SessionKey[index]);
    }

    //Now print the Even/Odd Key
    PROC_PRINT(p, "CSA3 Even  [time:0x%08x]:", g_CSA3Info.LastEvenKey_secTime);
    ADVCA_DebugKey(p, g_CSA3Info.LastEvenKey);
    PROC_PRINT(p, "CSA3 Odd   [time:0x%08x]:", g_CSA3Info.LastOddKey_secTime);
    ADVCA_DebugKey(p, g_CSA3Info.LastOddKey);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetSPKeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "SP Key Ladder Stage: %d Level\n", g_SPInfo.MaxLevel);
    if (g_SPInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "SP Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "SP Key Ladder Alg is TDES\n");
    }
    PROC_PRINT(p, "SP Key Ladder ReadyStatusStage:0x%08x\n", g_SPInfo.Keyladder_Ready);
    CAStatus.u32 = g_SPInfo.Keyladder_Ready;
    if (CAStatus.bits.sp_klad0_rdy == 0x01)
    {
        PROC_PRINT(p, "SP Key Ladder klad0(ready) ");
    }
    else
    {
        PROC_PRINT(p, "SP Key Ladder klad0(no ready) ");
    }

    if (CAStatus.bits.sp_klad1_rdy == 0x01)
    {
        PROC_PRINT(p, "klad1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "klad1(no ready) ");
    }

    if (CAStatus.bits.sp_klad2_rdy == 0x01)
    {
        PROC_PRINT(p, " klad2(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "klad2(no ready)\n");
    }

    for (index = 0; index < g_SPInfo.MaxLevel; index ++)
    {
        PROC_PRINT(p, "SP klad%d [time:0x%08x]:", index, g_SPInfo.SessionKey_sec[index]);
        ADVCA_DebugKey(p, g_SPInfo.SessionKey[index]);
    }

    //Now print the Even/Odd Key
    PROC_PRINT(p, "SP Even  [time:0x%08x]:", g_SPInfo.LastEvenKey_secTime);
    ADVCA_DebugKey(p, g_SPInfo.LastEvenKey);
    PROC_PRINT(p, "SP Odd   [time:0x%08x]:", g_SPInfo.LastOddKey_secTime);
    ADVCA_DebugKey(p, g_SPInfo.LastOddKey);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetMiscKeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "MISC Key Ladder Stage: %d Level\n", g_MiscInfo.MaxLevel);
    if (g_MiscInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "Misc Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "Misc Key Ladder Alg is TDES\n");
    }
    PROC_PRINT(p, "Misc Key Ladder ReadyStatusStage:0x%08x\n", g_MiscInfo.Keyladder_Ready);
    CAStatus.u32 = g_MiscInfo.Keyladder_Ready;
    if (CAStatus.bits.misc_klad0_rdy == 0x01)
    {
        PROC_PRINT(p, "Misc Key Ladder klad0(ready) ");
    }
    else
    {
        PROC_PRINT(p, "Misc Key Ladder klad0(no ready) ");
    }

    if (CAStatus.bits.misc_klad1_rdy == 0x01)
    {
        PROC_PRINT(p, "klad1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "klad1(no ready) ");
    }

    if (CAStatus.bits.misc_klad2_rdy == 0x01)
    {
        PROC_PRINT(p, " klad2(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "klad2(no ready)\n");
    }

    for (index = 0; index < g_MiscInfo.MaxLevel; index ++)
    {
        PROC_PRINT(p, "Misc klad%d [time:0x%08x]:", index, g_MiscInfo.SessionKey_sec[index]);
        ADVCA_DebugKey(p, g_MiscInfo.SessionKey[index]);
    }

    //Now print the Even/Odd Key
    PROC_PRINT(p, "Misc Even  [time:0x%08x]:", g_MiscInfo.LastEvenKey_secTime);
    ADVCA_DebugKey(p, g_MiscInfo.LastEvenKey);
    PROC_PRINT(p, "Misc Odd   [time:0x%08x]:", g_MiscInfo.LastOddKey_secTime);
    ADVCA_DebugKey(p, g_MiscInfo.LastOddKey);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetDCASKeyLadderinfo(struct seq_file* p)
{
    CA_V300_CA_STATE_U CAStatus;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "DCAS Key Ladder Stage: %d Level\n", g_DCASInfo.MaxLevel);
    if (g_DCASInfo.Alg == 0x02) //history reason, it is AES.
    {
        PROC_PRINT(p, "DCAS Key Ladder Alg is AES[0X%02d]\n", g_DCASInfo.Alg);
    }
    else
    {
        PROC_PRINT(p, "DCAS Key Ladder Alg is TDES[0X%02d]\n", g_DCASInfo.Alg);
    }
    PROC_PRINT(p, "DCAS Key Ladder ReadyStatusStage:0x%08x\n", g_DCASInfo.Keyladder_Ready);
    CAStatus.u32 = g_DCASInfo.Keyladder_Ready;
    if (CAStatus.bits.k1_rdy == 0x01)
    {
        PROC_PRINT(p, "DCAS Key Ladder k1(ready) ");
    }
    else
    {
        PROC_PRINT(p, "DCAS Key Ladder kl(no ready) ");
    }

    if (CAStatus.bits.k2_rdy == 0x01)
    {
        PROC_PRINT(p, "k2(ready) ");
    }
    else
    {
        PROC_PRINT(p, "k2(no ready) ");
    }

    if (CAStatus.bits.k3_rdy == 0x01)
    {
        PROC_PRINT(p, " k3(ready)\n");
    }
    else
    {
        PROC_PRINT(p, "k3(no ready)\n");
    }

    PROC_PRINT(p, "DCAS vendor[time:0x%08x]:", g_DCASInfo.SessionKey_sec[HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID]);
    ADVCA_DebugKey(p, g_DCASInfo.SessionKey[HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID]);

    PROC_PRINT(p, "DCAS Ek1   [time:0x%08x]:", g_DCASInfo.SessionKey_sec[HI_UNF_ADVCA_DCAS_KEYLADDER_EK1]);
    ADVCA_DebugKey(p, g_DCASInfo.SessionKey[HI_UNF_ADVCA_DCAS_KEYLADDER_EK1]);

    PROC_PRINT(p, "DCAS Ek2   [time:0x%08x]:", g_DCASInfo.SessionKey_sec[HI_UNF_ADVCA_DCAS_KEYLADDER_EK2]);
    ADVCA_DebugKey(p, g_DCASInfo.SessionKey[HI_UNF_ADVCA_DCAS_KEYLADDER_EK2]);

    PROC_PRINT(p, "DCAS none  [time:0x%08x]:", g_DCASInfo.SessionKey_sec[HI_UNF_ADVCA_DCAS_KEYLADDER_NONCE]);
    ADVCA_DebugKey(p, g_DCASInfo.SessionKey[HI_UNF_ADVCA_DCAS_KEYLADDER_NONCE]);

    //Now print the Even/Odd Key
    PROC_PRINT(p, "DCAS Even  [time:0x%08x]:", g_DCASInfo.LastEvenKey_secTime);
    ADVCA_DebugKey(p, g_DCASInfo.LastEvenKey);
    PROC_PRINT(p, "DCAS Odd   [time:0x%08x]:", g_DCASInfo.LastOddKey_secTime);
    ADVCA_DebugKey(p, g_DCASInfo.LastOddKey);

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetWidevineKeyLadderinfo(struct seq_file* p)
{
    HI_U8 index = 0;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "Widevine Key Ladder Stage: %d Level\n", g_GDRMInfo.MaxLevel);

    if (((g_GDRMInfo.Keyladder_Ready >> 3) & 0x1) == 0)
    {
        PROC_PRINT(p, "Widevine status: encrypt device key\n");
        PROC_PRINT(p, "Clean Device key     [time:0x%08x]:", g_GDRMInfo.SessionKey_sec[0]);
        ADVCA_DebugKey(p, g_GDRMInfo.SessionKey[0]);
        PROC_PRINT(p, "Encrypted Device key [time:0x%08x]:", g_GDRMInfo.SessionKey_sec[0]);
        ADVCA_DebugKey(p, g_GDRMInfo.SessionKey[1]);
    }
    else
    {
        PROC_PRINT(p, "Widevine status: decrypt data\n");
        for (index = 0; index < g_GDRMInfo.MaxLevel - 1; index++)
        {
            PROC_PRINT(p, "Widevine klad%d [time:0x%08x]:", index, g_GDRMInfo.SessionKey_sec[index]);
            ADVCA_DebugKey(p, g_GDRMInfo.SessionKey[index]);
        }

        PROC_PRINT(p, "Widevine klad%d [time:0x%08x]:", HI_UNF_ADVCA_KEYLADDER_LEV3, g_GDRMInfo.SessionKey_sec[index]);
        for (index = 0; index < 32; index++)
        {
            if (index == 16)
            {
                PROC_PRINT(p, "\n");
                PROC_PRINT(p, "Widevine klad%d [time:0x%08x]:", HI_UNF_ADVCA_KEYLADDER_LEV3, g_GDRMInfo.SessionKey_sec[HI_UNF_ADVCA_KEYLADDER_LEV3]);
            }
            PROC_PRINT(p, "%02X ", g_GDRMInfo.SessionKey[HI_UNF_ADVCA_KEYLADDER_LEV3][index]);

        }
        PROC_PRINT(p, "\n");
        PROC_PRINT(p, "Widevine Flag:");
        for (index = 0; index < 4; index++)
        {
            PROC_PRINT(p, "%02X ", g_GDRMInfo.GG_Flag[index]);
        }
        PROC_PRINT(p, "\n");

    }

    return HI_SUCCESS;
}

static HI_S32 DRV_ADVCA_ProcGetTAKeyLadderinfo(struct seq_file* p)
{
    HI_U32 TACtrlValue = 0;
    HI_U32 CurrentTAKladLevel = 0;

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "TA Key Ladder Stage: %d Level\n", g_TAInfo.MaxLevel);
    if (g_TAInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_AES)
    {
        PROC_PRINT(p, "TA Key Ladder Alg is AES\n");
    }
    else
    {
        PROC_PRINT(p, "TA Key Ladder Alg is TDES\n");
    }
    PROC_PRINT(p, "TA Key Ladder ReadyStatusStage:0x%08x\n", g_TAInfo.Keyladder_Ready);

    TACtrlValue = DRV_ADVCA_ReadReg(CA_V300_TA_KL_CTRL);
    CurrentTAKladLevel = (TACtrlValue & 0x3) + 1;

    if (1 == CurrentTAKladLevel)
    {
        PROC_PRINT(p, "TA Key Ladder klad0(ready) klad1(no ready) klad2(no ready)\n");
    }
    else if (2 == CurrentTAKladLevel)
    {
        PROC_PRINT(p, "TA Key Ladder klad0(ready) klad1(ready) klad2(no ready)\n");
    }
    else if (3 == CurrentTAKladLevel)
    {
        PROC_PRINT(p, "TA Key Ladder klad0(ready) klad1(ready) klad2(ready)\n");
    }

    PROC_PRINT(p, "TA klad0 [time:0x%08x]:", g_TAInfo.SessionKey_sec[0]);
    ADVCA_DebugKey(p, g_TAInfo.SessionKey[0]);

    return HI_SUCCESS;
}

HI_S32 DRV_ADVCA_ProcRead(struct seq_file* p, HI_VOID* v)
{
    HI_S32 ret;
    HI_U32 au32Debug[4] = {0};

    if (HI_NULL == p)
    {
        HI_FATAL_CA("invalid param\n");
        return HI_FAILURE;
    }

    if ( NULL == g_pOTPExportFunctionList)
    {
        ret = HI_DRV_MODULE_GetFunction(HI_ID_OTP, (HI_VOID**)&g_pOTPExportFunctionList);
        if ((ret != HI_SUCCESS) || (NULL == g_pOTPExportFunctionList))
        {
            PROC_PRINT(p, "Get otp functions failed!\n");
            return HI_FAILURE;
        }
    }

    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetSCSStatus(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetCAVendorType(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetChipID(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetMSID(p);
    (HI_VOID)DRV_ADVCA_ProcGetMSIDCheckEn(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetVersionID(p);
    (HI_VOID)DRV_ADVCA_ProcGetVersionIDCheckEn(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetSecretKeyChecksumStatus(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_GetRSAKeyLockFlag(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetChipType(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetBootMode(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetCWState(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_ADVCA_ProcGetCAState(p);
    PROC_PRINT(p, "====================================\n");
    ret = HAL_ADVCA_ProcGetReginfo(au32Debug);
    if ( ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get reg infomation\n");
    }
    else
    {
        PROC_PRINT(p, "Register infomation: 0x%08x, 0x%08x, 0x%08x, 0x%08x\n", au32Debug[0], au32Debug[1], au32Debug[2], au32Debug[3]);
    }

    PROC_PRINT(p, "====================================\n");
    ret = DRV_ADVCA_ProcGetCSA2KeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get CSA2 key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetR2RKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get R2R key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetCSA3KeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get CSA3 key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetSPKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get SP key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetMiscKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get Misc key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetDCASKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get DCAS key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetWidevineKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get Widevine key ladder infomation\n");
    }

    ret = DRV_ADVCA_ProcGetTAKeyLadderinfo(p);
    if ( ret  != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get TA key ladder infomation\n");
    }

    return HI_SUCCESS;
}
#endif
/******* proc function end   ********/

/*****************************************************************************
 Prototype    :
 Description  : CA模块 注册函数
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_S32 ADVCA_DRV_ModeInit(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 i = 0;

    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    DRV_PROC_EX_S stProcFunc = {0};
#endif
    /******* proc function end   ********/

    mutex_init(&g_ca_mutex.ca_oplock);
	advca_agent_register();

    for (i = 0; i < MUTEX_MAX_NUMBER; i++)
    {
        g_ca_mutex.ca_sema[i].isUsed = HI_FALSE;
    }

    ret = DRV_ADVCA_ModeInit_0();
    if (ret != HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    ca_snprintf(caUmapDev.devfs_name, sizeof(caUmapDev.devfs_name), UMAP_DEVNAME_CA);
    caUmapDev.minor  = UMAP_MIN_MINOR_CA;
    caUmapDev.owner  = THIS_MODULE;
    caUmapDev.fops   = &ca_fpops;
    caUmapDev.drvops = &ca_drvops;
    if (HI_DRV_DEV_Register(&caUmapDev) < 0)
    {
        HI_FATAL_CA("register CA failed.\n");
        goto err0;
    }

    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    stProcFunc.fnRead = DRV_ADVCA_ProcRead;

    HI_DRV_PROC_AddModule(HI_MOD_CA, &stProcFunc, NULL);
#endif
    /******* proc function end   ********/


#if defined(KLAD_TYPE_TEE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200)
    ret = DEV_ADVCA_InitTeec();
    if (HI_SUCCESS != ret)
    {
        DRV_ADVCA_ModeExit_0();
        return HI_FAILURE;
    }
#endif

#ifdef MODULE
    HI_PRINT("Load hi_advca.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;

err0:

    DRV_ADVCA_ModeExit_0();
    return HI_FAILURE;
}

HI_VOID ADVCA_DRV_ModeExit(HI_VOID)
{
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    HI_DRV_PROC_RemoveModule(HI_MOD_CA);
#endif
    /******* proc function end   ********/

    HI_DRV_DEV_UnRegister(&caUmapDev);

    DRV_ADVCA_ModeExit_0();

#if defined(KLAD_TYPE_TEE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200)
    DEV_ADVCA_DeInitTeec();
#endif
	advca_agent_unregister();

    return;
}

#ifdef MODULE
module_init(ADVCA_DRV_ModeInit);
module_exit(ADVCA_DRV_ModeExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");

