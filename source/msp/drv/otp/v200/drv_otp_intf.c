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
#include <linux/uaccess.h>
#include "hi_kernel_adapt.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hal_otp.h"
#include "hi_error_mpi.h"
#include "drv_otp_ioctl.h"
#include "hi_drv_proc.h"
#include "hi_drv_mem.h"
#include "drv_otp_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define PAGE_NUM_SHIFT          0 /* it depends on how many pages can be maped, 0:one page, 1:two pages, 2:four pages, 3: eight pages */
#define OTP_MAP_PAGE_NUM        (1ULL << PAGE_NUM_SHIFT)
#define OTP_MAP_MASK            (((OTP_MAP_PAGE_NUM) << PAGE_SHIFT) - 1)

#define DRV_OTP_PROC_SEPARATE         "===============================================\n"
#define DRV_OTP_PROC_PRINT(fmt...)    PROC_PRINT(p, fmt)

static UMAP_DEVICE_S   g_otp_umap_dev;

HI_DECLARE_MUTEX(g_otp_mutex);

typedef struct
{
    HI_U32 cmd;
    HI_S32 (*fun_ioctl)(HI_VOID* arg);
} DRV_OTP_IOCTL_FUNC_MAP_S;

HI_S32 DRV_OTP_Read(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    return HAL_OTP_Read(otp_entry->addr, &(otp_entry->value));
}

HI_S32 DRV_OTP_ReadByte(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;
    HI_U8 value = 0;
    HI_S32 ret;
    CHECK_NULL_PTR(arg);

    otp_entry = (OTP_ENTRY_S*)arg;
    ret = HAL_OTP_ReadByte(otp_entry->addr, &value);
    otp_entry->value = value;
    return ret;
}

HI_S32 DRV_OTP_ReadBitsOneByte(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;
    HI_U8 start_bit = 0;
    HI_U8 bit_width = 0;
    HI_U8 value = 0;
    HI_S32 ret;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    start_bit = OTP_START_BIT(otp_entry->value);
    bit_width = OTP_BIT_WIDTH(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);

    if (start_bit > 7)
    {
        HI_ERR_OTP("start_bit check failed. [%d]\n", start_bit);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (bit_width + start_bit > 8)
    {
        HI_ERR_OTP("bit_width check failed. [%d-%d]\n", start_bit, bit_width);
        return HI_ERR_OTP_INVALID_PARA;
    }
    ret = HAL_OTP_ReadBitsOnebyte(otp_entry->addr, start_bit, bit_width, &value);
    otp_entry->value = OTP_GET_PARA(start_bit, bit_width, value);
    return ret;
}

HI_S32 DRV_OTP_Write(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    return HAL_OTP_Write(otp_entry->addr, otp_entry->value);
}

HI_S32 DRV_OTP_WriteByte(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    return HAL_OTP_WriteByte(otp_entry->addr, (HI_U8)otp_entry->value);
}

HI_S32 DRV_OTP_WriteBit(HI_VOID* arg)
{

    OTP_ENTRY_S* otp_entry = NULL;
    HI_U8 bit_pos = 0;
    HI_U8 value = 0;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    bit_pos = OTP_START_BIT(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);

    if (bit_pos > 7)
    {
        HI_ERR_OTP("bit_pos check failed. [%d]\n", bit_pos);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (value != 0 && value != 1)
    {
        HI_ERR_OTP("value check failed. [%d]\n", value);
        return HI_ERR_OTP_INVALID_PARA;
    }
    return HAL_OTP_WriteBit(otp_entry->addr, bit_pos, (HI_BOOL)value);
}

HI_S32 DRV_OTP_WriteBitsOneByte(HI_VOID* arg)
{
    OTP_ENTRY_S* otp_entry = NULL;
    HI_U8 start_bit = 0;
    HI_U8 bit_width = 0;
    HI_U8 value = 0;

    CHECK_NULL_PTR(arg);
    otp_entry = (OTP_ENTRY_S*)arg;
    start_bit = OTP_START_BIT(otp_entry->value);
    bit_width = OTP_BIT_WIDTH(otp_entry->value);
    value = OTP_VALUE_BYTE(otp_entry->value);

    if (start_bit > 7)
    {
        HI_ERR_OTP("start_bit check failed. [%d]\n", start_bit);
        return HI_ERR_OTP_INVALID_PARA;
    }
    if (bit_width + start_bit > 8)
    {
        HI_ERR_OTP("bit_width check failed. [%d-%d]\n", start_bit, bit_width);
        return HI_ERR_OTP_INVALID_PARA;
    }
    return HAL_OTP_WriteBitsOnebyte(otp_entry->addr, start_bit, bit_width, value);
}

HI_S32 DRV_OTP_Reset(HI_VOID* arg)
{
    return HAL_OTP_Reset();
}

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
static HI_U8  g_fake_otp_buffer[8096] = {0};
static HI_U32 g_fake_otp_buffer_length = 0;
static DRV_OTP_FAKE_FLAG_E g_fake_otp_flag = DRV_OTP_NO_FAKE_FLAG;

HI_BOOL DRV_OTP_IsFakeOTPBuffer_Flag(HI_VOID)
{
    if (g_fake_otp_flag == DRV_OTP_FAKE_BUFFER_FLAG)
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

HI_BOOL DRV_OTP_IsFakeOTPAccessErr_Flag(HI_VOID)
{
    if (g_fake_otp_flag == DRV_OTP_FAKE_ACCESS_ERR_FLAG)
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

HI_S32 DRV_OTP_GetFakeOTPFlag(HI_VOID)
{
    return g_fake_otp_flag;
}

HI_VOID DRV_OTP_ClearFakeOTPBuffer(HI_VOID)
{
    memset(g_fake_otp_buffer, 0, sizeof(g_fake_otp_buffer));
    return;
}

extern HI_S32 HAL_OTP_ProcReadByte(HI_U32 addr, HI_U8* value);
HI_S32 DRV_OTP_SetFakeOTPFlag(HI_U32 value)
{
    HI_U32 index;
    HI_U8 val = 0;
    HI_S32 ret = HI_SUCCESS;

    if (g_fake_otp_flag == value)
    {
        return HI_SUCCESS;
    }
    if (value == DRV_OTP_FAKE_BUFFER_FLAG)
    {
        g_fake_otp_buffer_length = 4096;
        for (index = 0; index < g_fake_otp_buffer_length; index ++)
        {
            ret |= HAL_OTP_ProcReadByte(index, &val);
            g_fake_otp_buffer[index] = val;
        }
        g_fake_otp_flag = DRV_OTP_FAKE_BUFFER_FLAG;
        if (ret != HI_SUCCESS)
        {
            HI_ERR_OTP("HAL_OTP_ProcReadByte error code [0x%08X]\n", ret);
        }
    }
    else if (value == DRV_OTP_FAKE_ACCESS_ERR_FLAG)
    {
        g_fake_otp_flag = DRV_OTP_FAKE_ACCESS_ERR_FLAG;
    }
    else if (value == DRV_OTP_NO_FAKE_FLAG)
    {
        g_fake_otp_flag = DRV_OTP_NO_FAKE_FLAG;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_FakeOTP_ReadByte(HI_U32 addr)
{
    if (addr >= g_fake_otp_buffer_length)
    {
        return 0;
    }
    return g_fake_otp_buffer[addr];
}

HI_S32 DRV_OTP_FakeOTP_WriteByte(HI_U32 addr, HI_U8 value)
{
    if (addr >= g_fake_otp_buffer_length)
    {
        return HI_FAILURE;
    }
    g_fake_otp_buffer[addr] = g_fake_otp_buffer[addr] | value;

    return HI_SUCCESS;
}

static HI_VOID OTP_ProcGetHelpInfo(HI_VOID)
{
    HI_DRV_PROC_EchoHelper("\nUsage as following: \n");
    HI_DRV_PROC_EchoHelper("    cat /proc/msp/otp                      Display all proc information \n");
    HI_DRV_PROC_EchoHelper("    echo help > /proc/msp/otp              Display help infomation for otp proc module \n");
    HI_DRV_PROC_EchoHelper("    echo write addr data > /proc/msp/otp   Set data to addr in otp, byte by byte \n");
    HI_DRV_PROC_EchoHelper("    For example: echo write 0x******** 0x** > /proc/msp/otp \n");

    HI_DRV_PROC_EchoHelper("\n    Attention:\n");
    HI_DRV_PROC_EchoHelper("        1 Operations must be carefully when setting data to otp !!!\n");
    HI_DRV_PROC_EchoHelper("        2 Input 'addr' and 'data' must be take the '0x' prefix in hex format !!!\n");
    HI_DRV_PROC_EchoHelper("        3 Otp must be set byte by byte !!!\n");
    return;
}

#define HI_REG_READ32(addr,result)  ((result) = *(volatile unsigned int *)(addr))

static HI_S32 OTP_ProcReadAllOver(struct seq_file* p)
{
    HI_U32* value = NULL;
    HI_U32 addr = 0, val;

    if (DRV_OTP_IsFakeOTPAccessErr_Flag() == HI_TRUE)
    {
        PROC_PRINT(p, "OTP Enter Access Error Test Mode.\n");
        PROC_PRINT(p, "Can not get any value from OTP\n");
        return HI_SUCCESS;
    }

    if (DRV_OTP_IsFakeOTPBuffer_Flag() == HI_TRUE)
    {
        PROC_PRINT(p, "OTP Get from Fake buffer\n");
    }

    PROC_PRINT(p, "OTP read all over:\n");

    value = (HI_U32*)HI_VMALLOC(HI_ID_OTP, 0x1000);
    if (NULL == value)
    {
        HI_ERR_OTP("vmalloc(size 0x800) failed!");
        return HI_ERR_OTP_MALLOC_ERR;
    }

    for (addr = 0; addr < 0x1000; addr += 4)
    {
        if (0 == (addr & 0xF))
        {
            PROC_PRINT(p, "\n%04x: ", addr);
        }
        HAL_OTP_Read(addr, &val);
        value[addr / 4] = val;
        PROC_PRINT(p, "%08x ", value[addr / 4]);
    }

    PROC_PRINT(p, "\n");

    HI_VFREE(HI_ID_OTP, (HI_VOID*)value);

    return HI_SUCCESS;
}

//Below command is just use for OTP test.
//u8Value[0]:type
//u8Value[1]~u8Value[15]:parameter
static HI_U32 OTP_VisualTest(HI_U8 value[16])
{
    HI_U32 ret_value = 0;

    if (HI_NULL == value)
    {
        HI_ERR_OTP("invalid param\n");
        return HI_ERR_OTP_PTR_NULL;
    }

    switch (value[0])
    {
        case DRV_OTP_GET_FAKE_BUFFER_FLAG:  //0x01
            ret_value = DRV_OTP_GetFakeOTPFlag();
            value[1] = (HI_U8)0xAA;
            value[2] = (HI_U8)ret_value;
            HI_ERR_OTP("OTP get special test flag(0X%02x)\n", ret_value);
            break;

        case DRV_OTP_FAKE_BUFFER_FLAG:      //0x10
            ret_value = DRV_OTP_SetFakeOTPFlag(value[0]);
            HI_ERR_OTP("OTP Set special test flag(0X%02x) :0x%02x\n", value[0], ret_value);
            break;

        case DRV_OTP_FAKE_BUFFER_RESET_FLAG://0x11
            HI_ERR_OTP("OTP Set special test flag(Reset) :0x%02x\n", ret_value);
            DRV_OTP_SetFakeOTPFlag(DRV_OTP_NO_FAKE_FLAG);
            DRV_OTP_SetFakeOTPFlag(DRV_OTP_FAKE_BUFFER_FLAG);
            break;

        case DRV_OTP_FAKE_ACCESS_ERR_FLAG:  //0x20
            ret_value = DRV_OTP_SetFakeOTPFlag(value[0]);
            HI_ERR_OTP("OTP Set special test flag(0X%02x) : :0x%02x\n", value[0], ret_value);
            break;

        case DRV_OTP_NO_FAKE_FLAG:          //0x00
            ret_value = DRV_OTP_SetFakeOTPFlag(value[0]);
            HI_ERR_OTP("OTP Set special test flag(0X%02x) : :0x%02x\n", value[0], ret_value);
            break;

        case DRV_OTP_CLEAR_OTP_FAKE_BUFFER:
            DRV_OTP_ClearFakeOTPBuffer();
            break;
        default:
            return HI_ERR_OTP_INVALID_PARA;
    }

    return HI_SUCCESS;
}

HI_S32 OTP_ProcRead(struct seq_file* p, HI_VOID* v)
{
    CHECK_NULL_PTR(p);

    PROC_PRINT(p, "---------Hisilicon OTP Info---------\n");
    OTP_ProcReadAllOver(p);
    PROC_PRINT(p, "---------Hisilicon otp Info End---------\n");
    return HI_SUCCESS;
}

HI_S32 OTP_ProcWrite(struct file* file, const char __user* pBufIn, size_t count, loff_t* ppos)
{
    HI_S32 ret = HI_SUCCESS;
    HI_CHAR param[256];
    HI_CHAR* ptr1 = NULL;
    HI_CHAR* ptr2 = NULL;
    HI_CHAR* p = NULL;
    HI_U32 addr = 0;
    HI_U32 value = 0;

    CHECK_NULL_PTR(pBufIn);

    memset(param, 0, 256);

    if (count >= 256)
    {
        HI_ERR_OTP("The command string is out of buf space :%d bytes !\n", sizeof(param));
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }
    p = param;

    if (copy_from_user((void*)p, (void*)pBufIn, count))
    {
        HI_ERR_OTP("failed to call copy_from_user !\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return -EFAULT;
    }
    p[count] = 0;

    if (strlen(p) <= 0)
    {
        HI_ERR_OTP("the ProcParam is null string!\n");
        return HI_FAILURE;
    }

    ptr1 = strstr(p, "help");
    if ( NULL != ptr1)
    {
        (HI_VOID)OTP_ProcGetHelpInfo();
        return count;
    }
    ptr1 = strstr(p, "write");
    if ( NULL == ptr1)
    {
        HI_ERR_OTP("Invalid write otp command !\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }

    ptr1 = strstr(p, "0x");
    if ( NULL == ptr1)
    {
        HI_ERR_OTP("Invalid write otp command !\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }

    addr = (HI_U32)simple_strtoul(ptr1, &ptr2, 16);
    if (NULL == ptr2)
    {
        HI_ERR_OTP("Invalid write otp command !\n");
        return HI_FAILURE;
    }

    ptr2 = strstr(ptr2, "0x");
    if ( NULL == ptr2)
    {
        HI_ERR_OTP("Invalid write otp command !\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }

    if ( 0x1000 <= addr )
    {
        HI_ERR_OTP("Invalid input addr !\n\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }

    value = (HI_U32)simple_strtoul(ptr2, &ptr1, 16);
    if (0 != (value & 0xffffff00))
    {
        HI_ERR_OTP("Invalid input data, data should be type of HI_U8 !\n\n");
        (HI_VOID)OTP_ProcGetHelpInfo();
        return HI_FAILURE;
    }

    HI_WARN_OTP("u32Addr = 0x%08x  ", addr);
    HI_WARN_OTP("u8Value = 0x%02x\n", value & 0xff);

    ret = HAL_OTP_WriteByte(addr, (HI_U8)(value & 0xff));
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Write otp failed, ret = 0x%08x !\n", ret);
        return HI_FAILURE;
    }

    return count;
}

HI_S32 DRV_OTP_Test(HI_VOID* arg)
{
    HI_U8 value[16] = {0};

    memcpy(value, arg, sizeof(value));
    return OTP_VisualTest(value);
}
#endif
/******* proc function end   ********/

static DRV_OTP_IOCTL_FUNC_MAP_S g_ioctl_func_map[] =
{
    {CMD_OTP_READ,               DRV_OTP_Read},
    {CMD_OTP_READ_BYTE,          DRV_OTP_ReadByte},
    {CMD_OTP_READ_BITS_ONEBYTE,  DRV_OTP_ReadBitsOneByte},
    {CMD_OTP_WRITE,              DRV_OTP_Write},
    {CMD_OTP_WRITE_BYTE,         DRV_OTP_WriteByte},
    {CMD_OTP_WRITE_BIT,          DRV_OTP_WriteBit},
    {CMD_OTP_WRITE_BITS_ONEBYTE, DRV_OTP_WriteBitsOneByte},
    {CMD_OTP_RESET,              DRV_OTP_Reset},
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    {CMD_OTP_TEST,               DRV_OTP_Test},
#endif
    /******* proc function end   ********/
};

HI_S32 OTP_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, HI_VOID* arg)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 i = 0;
    HI_S32 size = 0;

    size = sizeof(g_ioctl_func_map) / sizeof(g_ioctl_func_map[0]);
    for (i = 0; i < size; i++)
    {
        if (cmd == g_ioctl_func_map[i].cmd)
        {
            if (down_interruptible(&g_otp_mutex))
            {
                return -1;
            }
            ret = g_ioctl_func_map[i].fun_ioctl(arg);
            if (ret != HI_SUCCESS)
            {
                HI_ERR_OTP("cmd ID: 0x%x failed, ret: 0x%x\n", cmd, ret);
            }
            up(&g_otp_mutex);
            return ret;
        }
    }

    HI_ERR_OTP("not support cmd ID: 0x%x\n", cmd);
    return HI_ERR_OTP_INVALID_PARA;
}

static HI_S32 OTP_DRV_Open(struct inode* inode, struct file* filp)
{
    return 0;
}

static HI_S32 OTP_DRV_Close(struct inode* inode, struct file* filp)
{
    return 0;
}

HI_S32 HI_DRV_OTP_Suspend(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 HI_DRV_OTP_Resume(HI_VOID)
{
    return HI_SUCCESS;
}

static OTP_EXPORT_FUNC_S s_OTPExportFuncs =
{
    .HAL_OTP_V200_Read              =   HAL_OTP_Export_Read,
    .HAL_OTP_V200_ReadByte          =   HAL_OTP_Export_ReadByte,
    .HAL_OTP_V200_Write             =   HAL_OTP_Write,
    .HAL_OTP_V200_WriteByte         =   HAL_OTP_WriteByte,
    .HAL_OTP_V200_WriteBit          =   HAL_OTP_WriteBit,
    .pfnOTPSuspend                  =   HI_DRV_OTP_Suspend,
    .pfnOTPResume                   =   HI_DRV_OTP_Resume,
};

#define OTP_NAME "HI_OTP"
HI_S32 OTP_DRV_Init(void)
{
    HI_S32 ret = HI_SUCCESS;

    ret = HI_DRV_MODULE_Register(HI_ID_OTP, OTP_NAME, (HI_VOID*)&s_OTPExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_OTP("HI_DRV_MODULE_Register otp failed\n");
        return ret;
    }
    ret = HAL_OTP_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_OTP("HAL_OTP_Init otp failed\n");
        return ret;
    }
    return HI_SUCCESS;
}

HI_S32 OTP_DRV_DeInit(void)
{
    HI_DRV_MODULE_UnRegister(HI_ID_OTP);
    return HI_SUCCESS;
}

static HI_SLONG OTP_DRV_Ioctl(struct file* ffile, HI_U32 cmd, HI_ULONG arg)
{
    HI_SLONG ret;
    ret = (HI_SLONG)HI_DRV_UserCopy(ffile->f_path.dentry->d_inode, ffile, cmd, arg, OTP_Ioctl);
    return ret;
}


static int _valid_mmap_phys_addr_range(unsigned long pfn, size_t size, unsigned long reg_phy_mask)
{
    return (pfn + (size >> PAGE_SHIFT)) <= (1 + (reg_phy_mask >> PAGE_SHIFT));
}

static HI_S32 DRV_OTP_Mmap(struct file *file, struct vm_area_struct *vma)
{
    size_t size = vma->vm_end - vma->vm_start;

    /* Invalid register address of common  */
    if ((PERM_REG_BASE >> PAGE_SHIFT) >> PAGE_NUM_SHIFT != vma->vm_pgoff >> PAGE_NUM_SHIFT)
    {
        HI_FATAL_OTP("Invalid page frame, vm_page_prot[%#x]\n", vma->vm_pgoff);
        return -EINVAL;
    }

    /* Invalid register address or len of common */
    if (!_valid_mmap_phys_addr_range(vma->vm_pgoff, size, PERM_REG_BASE | OTP_MAP_MASK))
    {
        HI_FATAL_OTP("invalid pgoff[%#x] or size[%#x]\n", vma->vm_pgoff, size);
        return -EINVAL;
    }

    vma->vm_page_prot = phys_mem_access_prot(file, vma->vm_pgoff, size, vma->vm_page_prot);

    if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        HI_FATAL_OTP("remap_pfn_range fail.\n");
        return -EAGAIN;
    }

    return HI_SUCCESS;
}

static struct file_operations otp_fops =
{
    .owner          = THIS_MODULE,
    .open           = OTP_DRV_Open,
    .unlocked_ioctl = OTP_DRV_Ioctl,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = OTP_DRV_Ioctl,
#endif
    .release        = OTP_DRV_Close,
    .mmap           = DRV_OTP_Mmap
};

int OTP_PM_Suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    return HI_SUCCESS;
}

int OTP_PM_Resume(PM_BASEDEV_S* pdev)
{
    //return HAL_OTP_Reset();
    return HI_SUCCESS;
}

static PM_BASEOPS_S  otp_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = OTP_PM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = OTP_PM_Resume,
};


HI_S32 OTP_DRV_ModInit(HI_VOID)
{
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    DRV_PROC_EX_S proc_func = {0};
#endif
    /******* proc function end   ********/
    snprintf(g_otp_umap_dev.devfs_name, sizeof(UMAP_DEVNAME_OTP), UMAP_DEVNAME_OTP);
    g_otp_umap_dev.minor = UMAP_MIN_MINOR_OTP;
    g_otp_umap_dev.owner  = THIS_MODULE;
    g_otp_umap_dev.drvops = &otp_drvops;
    g_otp_umap_dev.fops = &otp_fops;

    if (HI_DRV_DEV_Register(&g_otp_umap_dev) < 0)
    {
        HI_FATAL_OTP("register otp failed.\n");
        return HI_ERR_OTP_NOT_INITRDY;
    }
    OTP_DRV_Init();
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    proc_func.fnRead   = OTP_ProcRead;
    proc_func.fnWrite  = OTP_ProcWrite;
    HI_DRV_PROC_AddModule(HI_MOD_OTP, &proc_func, NULL);
#endif
    /******* proc function end   ********/
#ifdef MODULE
    HI_PRINT("Load hi_otp.ko success.  \t(%s)\n", VERSION_STRING);
#endif
    return 0;
}

HI_VOID OTP_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_otp_umap_dev);
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    HI_DRV_PROC_RemoveModule(HI_MOD_OTP);
#endif
    /******* proc function end   ********/
    OTP_DRV_DeInit();
    return;
}

#ifdef MODULE
module_init(OTP_DRV_ModInit);
module_exit(OTP_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

