/***********************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName   :  drv_sys_ext.c
* Description:  Define interfaces of demux hardware abstract layer.
*
* History:
* Version      Date         Author        DefectNum    Description
* main\1    20091217    sdk      NULL      Create this file.
***********************************************************************************/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/mman.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <asm/io.h>

#include "hi_type.h"
#include "hi_unf_version.h"

#include "hi_osal.h"
#include "hi_reg_common.h"
#include "hi_drv_struct.h"
#include "hi_drv_dev.h"
#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_drv_reg.h"
#include "hi_drv_mem.h"
#include "drv_sys_ioctl.h"

static HI_CHAR s_szCommonVersion[] __attribute__((used)) = VERSION_STRING;

typedef struct hiHIxxxx_SOC_S
{
    struct semaphore stSem;
    HI_SYS_CONF_S stChipConf;
}HIxxxx_SOC_S;

static HIxxxx_SOC_S s_stSocData;

extern const char * get_sdkversion(void);

HI_S32 SYS_GetBootVersion(HI_CHAR *pVersion,HI_U32 u32VersionLen)
{
    const HI_U8* pu8BootVer = get_sdkversion();

    if (HI_NULL == pVersion || u32VersionLen == 0)
    {
        HI_WARN_SYS("SYS_GetBootVersion failure line:%d\n", __LINE__);
        return HI_FAILURE;
    }

    if (pu8BootVer != NULL)
    {
        if (u32VersionLen > strlen(pu8BootVer))
        {
            u32VersionLen = strlen(pu8BootVer);
        }
        else
        {
            HI_ERR_SYS("SYS_GetBootVersion input buf too short\n");
            return HI_FAILURE;
        }

        memcpy(pVersion, pu8BootVer, u32VersionLen);
        pVersion[u32VersionLen] = '\0';

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 SysSetConfig(HI_SYS_CONF_S *pstConf)
{
    memcpy(&s_stSocData.stChipConf, pstConf, sizeof(*pstConf));
    return 0;
}

HI_S32 SysGetConfig(HI_SYS_CONF_S *pstConf)
{
    memcpy(pstConf, &s_stSocData.stChipConf, sizeof(*pstConf));
    return 0;
}

static HI_S32 SYS_Ioctl(struct inode *pInode, struct file *pFile, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = -ENOIOCTLCMD;
    HI_SYS_VERSION_S* chiptype;

    down(&s_stSocData.stSem);
    switch (cmd)
    {
        case SYS_SET_CONFIG_CTRL :
            ret = SysSetConfig((HI_SYS_CONF_S*)arg);
            break;

        case SYS_GET_CONFIG_CTRL :
            ret = SysGetConfig((HI_SYS_CONF_S*)arg);
            break;

        case SYS_GET_SYS_VERSION :
            chiptype = (HI_SYS_VERSION_S*)arg;
            HI_DRV_SYS_GetChipVersion(&chiptype->enChipTypeHardWare, &chiptype->enChipVersion);
            SYS_GetBootVersion(chiptype->BootVersion, sizeof(chiptype->BootVersion));
            HI_DRV_SYS_GetSecureOSImageVersion(chiptype->SecureOSImageVersion, sizeof(chiptype->SecureOSImageVersion));
            ret = HI_SUCCESS;
            break;

        case SYS_GET_TIMESTAMPMS :
            ret = HI_DRV_SYS_GetTimeStampMs((HI_U32*)arg);
            break;

        case SYS_GET_DOLBYSUPPORT :
            ret = HI_DRV_SYS_GetDolbySupport((HI_U32*)arg);
            break;

        case SYS_GET_DTSSUPPORT :
            ret = HI_DRV_SYS_GetDtsSupport((HI_U32*)arg);
            break;

        case SYS_GET_ADVCASUPPORT :
            ret = HI_DRV_SYS_GetAdvcaSupport((HI_U32*)arg);
            break;

        case SYS_GET_MACROVISIONSUPPORT :
            ret = HI_DRV_SYS_GetRoviSupport((HI_U32*)arg);
            break;

        case SYS_GET_HDR10SUPPORT :
            ret = HI_DRV_SYS_GetHdrSupport((HI_U32*)arg);
            break;

        case SYS_GET_DOLBYVISIONSUPPORT :
            ret = HI_DRV_SYS_GetDolbyvisionSupport((HI_U32*)arg);
            break;

        case SYS_GET_DDRCONFIG :
            ret = HI_DRV_SYS_GetMemConfig((HI_SYS_MEM_CONFIG_S*)arg);
            break;

        case SYS_GET_64DIEID :
            ret = HI_DRV_SYS_Get64DieID((HI_U64 *)arg);
            break;

        case SYS_GET_32DIEID :
            ret = HI_DRV_SYS_Get32DieID((HI_U32 *)arg);
            break;

        case SYS_GET_CHIPPACKAGETYPE :
            ret = HI_DRV_SYS_GetChipPackageType((HI_CHIP_PACKAGE_TYPE_E*)arg);
            break;

        case SYS_GET_SYS_ATTR:
            ret = HI_DRV_SYS_Get_Attrs((HI_SYS_ATTR_S*)arg);
            break;

        case SYS_DISABLE_VIDEOCODEC:
            ret = HI_DRV_SYS_DisableVideoCodec(*((HI_SYS_VIDEO_CODEC_E *)arg));
            break;
        default :
            HI_WARN_SYS("ioctl cmd %d nonexist!\n", cmd);
    }
    up(&s_stSocData.stSem);
    return ret;
}

static HI_VOID SystGetChipName(HI_CHIP_TYPE_E ChipType, HI_CHAR **pChipName)
{
    if (HI_NULL == pChipName)
    {
        HI_ERR_SYS("Invalid parament pChipName[%#x]!\n", pChipName);
        return;
    }

    switch (ChipType)
    {
        case HI_CHIP_TYPE_HI3716M :
            *pChipName = "Hi3716M";
            break;

        case HI_CHIP_TYPE_HI3798C :
            *pChipName = "Hi3798C";
            break;

        case HI_CHIP_TYPE_HI3796M :
            *pChipName = "Hi3796M";
            break;

        case HI_CHIP_TYPE_HI3798M :
            *pChipName = "Hi3798M";
            break;

        case HI_CHIP_TYPE_HI3798M_H :
            *pChipName = "Hi3798M_H";
            break;

        default:
            *pChipName = "UNKNOWN";
    }

    return;
}

static HI_VOID SystGetChipPackageType(HI_CHIP_PACKAGE_TYPE_E PackageType, HI_CHAR **pPackageName)
{

    if (HI_NULL == pPackageName)
    {
        HI_ERR_SYS("Invalid parament pPackageName[%#x]!\n", pPackageName);
        return;
    }

    switch (PackageType)
    {
        case HI_CHIP_PACKAGE_TYPE_BGA_14_14 :
            *pPackageName = "BGA 14*14";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_15_15 :
            *pPackageName = "BGA 15*15";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_16_16 :
            *pPackageName = "BGA 16*16";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_19_19 :
            *pPackageName = "BGA 19*19";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_21_21:
            *pPackageName = "BGA 21*21";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_23_23 :
            *pPackageName = "BGA 23*23";
            break;

        case HI_CHIP_PACKAGE_TYPE_BGA_31_31 :
            *pPackageName = "BGA 31*31";
            break;

        case HI_CHIP_PACKAGE_TYPE_QFP_216 :
            *pPackageName = "QFP 216";
            break;

        default:
            *pPackageName = "UNKNOWN";
    }

    return;
}

static HI_S32 SysProcShow(struct seq_file *s, HI_VOID *pArg)
{
    HI_CHIP_TYPE_E          ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E       ChipVersion = 0;
    HI_CHIP_PACKAGE_TYPE_E  PackageType = HI_CHIP_PACKAGE_TYPE_BUTT;
    HI_U32                  DolbySupport;
    HI_U32                  Hdr10Support;
    HI_U32                  DolbyvisionSupport;
    HI_U32                  DtsSupport;
    HI_U32                  RoviSupport;
    HI_U32                  AdvcaSupport;
    HI_CHAR                 *ChipName = HI_NULL;
    HI_CHAR                 *PackageName = HI_NULL;
#if defined(COMMON_TEE_SUPPORT) && defined(ADVCA_TYPE)
    HI_U8                   Version[96];
#endif

    HI_DRV_SYS_GetChipVersion(&ChipType, &ChipVersion);

    PROC_PRINT(s, "%s\n", s_szCommonVersion);

    PROC_PRINT(s, "UNF_VERSION: %d.%d.%d\n", (UNF_VERSION_CODE >> 8) & 0xFF, UNF_VERSION_CODE & 0xFF, UNF_SUBVERSION_CODE);

    SystGetChipName(ChipType, &ChipName);

    PROC_PRINT(s, "CHIP_VERSION: %sV%x\n", ChipName, ChipVersion);

    if (HI_SUCCESS == HI_DRV_SYS_GetChipPackageType(&PackageType))
    {
        SystGetChipPackageType(PackageType, &PackageName);

        PROC_PRINT(s, "PACKAGE_TYPE: %s\n", PackageName);
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetDolbySupport(&DolbySupport))
    {
        PROC_PRINT(s, "DOLBY: %s\n", (DolbySupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetDtsSupport(&DtsSupport))
    {
        PROC_PRINT(s, "DTS: %s\n", (DtsSupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetAdvcaSupport(&AdvcaSupport))
    {
        PROC_PRINT(s, "ADVCA: %s\n", (AdvcaSupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetRoviSupport(&RoviSupport))
    {
        PROC_PRINT(s, "ROVI(Macrovision): %s\n", (RoviSupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetHdrSupport(&Hdr10Support))
    {
        PROC_PRINT(s, "HDR10: %s\n", (Hdr10Support) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetDolbyvisionSupport(&DolbyvisionSupport))
    {
        PROC_PRINT(s, "DolbyVision: %s\n", (DolbyvisionSupport) ? "YES" : "NO");
    }

#if defined(COMMON_TEE_SUPPORT) && defined(ADVCA_TYPE)
    if (HI_SUCCESS == HI_DRV_SYS_GetSecureOSImageVersion(Version, sizeof(Version)))
    {
        PROC_PRINT(s, "SecureOSVersion: %s\n", Version);
    }
#endif

    return 0;
}

static long CMPI_SYS_Ioctl(struct file *file, HI_U32 cmd, unsigned long arg)
{
    long ret;
    ret=(long)HI_DRV_UserCopy(file->f_path.dentry->d_inode, file, cmd, arg, SYS_Ioctl);

    return ret;
}


static HI_S32 CMPI_SYS_Open(struct inode * vinode, struct file * vfile)
{
    return 0;
}

static HI_S32 CMPI_SYS_Close(struct inode * vinode, struct file * vfile)
{
    return 0;
}

/***********************************sys map begin*****************************************************/
/*
*map range 0xF8000000~0xF8000FFF(sys can map one page only)
*map range 0xF8A20000~0xF8A20FFF(per can map one page only)
*/
#define PAGE_NUM_SHIFT          0 /* it depends on how many pages can be maped, 0:one page, 1:two pages, 2:four pages, 3: eight pages */
#define SYS_MAP_PAGE_NUM        (1ULL << PAGE_NUM_SHIFT)
#define SYS_MAP_MASK            (((SYS_MAP_PAGE_NUM) << PAGE_SHIFT) - 1)

static int _valid_mmap_phys_addr_range(unsigned long pfn, size_t size, unsigned long reg_phy_mask)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (reg_phy_mask >> PAGE_SHIFT));
}

static HI_S32 CMPI_SYS_Mmap(struct file *file, struct vm_area_struct *vma)
{
    size_t size = vma->vm_end - vma->vm_start;

    /* Invalid register address or size of sys&perl  */
    if (!((((HI_SYS_BASE_ADDR >> PAGE_SHIFT) >> PAGE_NUM_SHIFT == vma->vm_pgoff >> PAGE_NUM_SHIFT)
            &&_valid_mmap_phys_addr_range(vma->vm_pgoff, size, HI_SYS_BASE_ADDR | SYS_MAP_MASK))
         ||(((HI_PERI_BASE_ADDR >> PAGE_SHIFT) >> PAGE_NUM_SHIFT == vma->vm_pgoff >> PAGE_NUM_SHIFT)
           &&_valid_mmap_phys_addr_range(vma->vm_pgoff, size, HI_PERI_BASE_ADDR | SYS_MAP_MASK))))
    {
        HI_ERR_SYS("invalid vm_pgoff[%#x] or size[%#x]\n", vma->vm_pgoff, size);
        return -EINVAL;
    }

    vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff, size, vma->vm_page_prot);

    if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        HI_FATAL_SYS("remap_pfn_range fail.\n");
        return -EAGAIN;
    }

    return HI_SUCCESS;
}
/***********************************sys map end*****************************************************/

static struct file_operations stFileOp =
{
     .owner = THIS_MODULE,
     .open = CMPI_SYS_Open,
     .unlocked_ioctl = CMPI_SYS_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl = CMPI_SYS_Ioctl,
#endif
     .release = CMPI_SYS_Close,
     .mmap    = CMPI_SYS_Mmap
};

static UMAP_DEVICE_S s_stDevice;

HI_S32 HI_DRV_REG_KInit(HI_VOID)
{
    HI_U8 *pu8OtpAddr = HI_NULL;

    g_pstRegSysCtrl = (HI_REG_SYSCTRL_S*)ioremap_nocache(HI_SYS_BASE_ADDR, sizeof(S_SYSCTRL_REGS_TYPE));
    if (HI_NULL == g_pstRegSysCtrl)
    {
        HI_PRINT("HI_SYS_BASE_ADDR ioremap error!\n");
        goto err5;
    }

    g_pstRegPeri = (HI_REG_PERI_S*)ioremap_nocache(HI_PERI_BASE_ADDR, sizeof(HI_REG_PERI_S));
    if (HI_NULL == g_pstRegPeri)
    {
        HI_PRINT("HI_PERI_BASE_ADDR ioremap error!\n");
        goto err4;
    }

    g_pstRegIO = (HI_REG_IO_S*)ioremap_nocache(HI_IO_BASE_ADDR, sizeof(HI_REG_IO_S));
    if (HI_NULL == g_pstRegIO)
    {
        HI_PRINT("HI_IO_BASE_ADDR ioremap error!\n");
        goto err3;
    }

    g_pstRegCrg = (HI_REG_CRG_S*)ioremap_nocache(HI_CRG_BASE_ADDR, sizeof(HI_REG_CRG_S));
    if (HI_NULL == g_pstRegCrg)
    {
        HI_PRINT("HI_CRG_BASE_ADDR ioremap error!\n");
        goto err2;
    }

    pu8OtpAddr = (HI_U8*)ioremap_nocache(HI_OTP_BASE_ADDR, 0x1000);
    if (HI_NULL == pu8OtpAddr)
    {
        HI_PRINT("HI_OTP_BASE_ADDR ioremap error!\n");
        goto err1;
    }

    g_pOtpBaseVirAddr = HI_KMALLOC(HI_ID_SYS, 0x1000, GFP_KERNEL);
    if (HI_NULL == g_pOtpBaseVirAddr)
    {
        HI_PRINT("g_pOtpBaseVirAddr kmalloc error!\n");
        goto err0;
    }

    memcpy(g_pOtpBaseVirAddr, pu8OtpAddr, 0x800);

    iounmap((HI_VOID *)pu8OtpAddr);
    pu8OtpAddr = HI_NULL;

    return HI_SUCCESS;

err0:
    iounmap((HI_VOID *)pu8OtpAddr);
    pu8OtpAddr = HI_NULL;

err1:
    iounmap((HI_VOID *)g_pstRegCrg);
    g_pstRegCrg = HI_NULL;

err2:
    iounmap((HI_VOID *)g_pstRegIO);
    g_pstRegIO = HI_NULL;

err3:
    iounmap((HI_VOID *)g_pstRegPeri);
    g_pstRegPeri = HI_NULL;

err4:
    iounmap((HI_VOID *)g_pstRegSysCtrl);
    g_pstRegSysCtrl = HI_NULL;

err5:

    return HI_FAILURE;
}

HI_VOID HI_DRV_REG_KExit(HI_VOID)
{
    if (HI_NULL != g_pOtpBaseVirAddr)
    {
        HI_KFREE(HI_ID_SYS, g_pOtpBaseVirAddr);
        g_pOtpBaseVirAddr = HI_NULL;
    }

    if (HI_NULL != g_pstRegSysCtrl)
    {
        iounmap((HI_VOID *)g_pstRegSysCtrl);
        g_pstRegSysCtrl = HI_NULL;
    }

    if (HI_NULL != g_pstRegPeri)
    {
        iounmap((HI_VOID *)g_pstRegPeri);
        g_pstRegPeri = HI_NULL;
    }

    if (HI_NULL != g_pstRegIO)
    {
        iounmap((HI_VOID *)g_pstRegIO);
        g_pstRegIO = HI_NULL;
    }

    if (HI_NULL != g_pstRegCrg)
    {
        iounmap((HI_VOID *)g_pstRegCrg);
        g_pstRegCrg = HI_NULL;
    }

    return;
}

HI_S32 HI_DRV_SYS_Init(HI_VOID)
{
    HI_S32 ret;
    DRV_PROC_EX_S stFnOpt =
    {
         .fnRead = SysProcShow,
    };

    ret = HI_DRV_MODULE_Register(HI_ID_SYS, "HI_SYS", HI_NULL);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    sema_init(&s_stSocData.stSem, 1);

    HI_OSAL_Snprintf(s_stDevice.devfs_name, sizeof(s_stDevice.devfs_name), UMAP_DEVNAME_SYS);
    s_stDevice.fops = &stFileOp;
    s_stDevice.minor = UMAP_MIN_MINOR_SYS;
    s_stDevice.owner  = THIS_MODULE;
    s_stDevice.drvops = NULL;

    if (HI_DRV_DEV_Register(&s_stDevice))
    {
        HI_ERR_SYS("Register system device failed!\n");
        goto OUT;
    }

    HI_DRV_PROC_AddModule(HI_MOD_SYS, &stFnOpt, 0);

    return 0;

OUT:
    HI_WARN_SYS("load sys ...FAILED!\n");
    return HI_FAILURE;
}

HI_VOID HI_DRV_SYS_Exit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule(HI_MOD_SYS);
    HI_DRV_DEV_UnRegister(&s_stDevice);
    HI_DRV_MODULE_UnRegister(HI_ID_SYS);
}

