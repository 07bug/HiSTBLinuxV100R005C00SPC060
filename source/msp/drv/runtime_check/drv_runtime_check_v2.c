/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name             :     drv_runtime_check_v2.c
  Version               :     Initial Draft
  Author                :     Hisilicon multimedia software group
  Created               :     2012/09/07
  Last Modified         :
  Description           :     This file is for 96mv200
  Function List         :
  History               :
  Date                  :     2018/01/31
  Author                :
  Modification          :     Created file

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#include <linux/module.h>
#include <linux/signal.h>
#include <linux/spinlock.h>
#include <linux/personality.h>
#include <linux/ptrace.h>
#include <linux/kallsyms.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/seq_file.h>
#include <linux/version.h>

#include <asm/atomic.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/traps.h>
#include <linux/semaphore.h>

#include <linux/miscdevice.h>

#include <linux/vmalloc.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/io.h>
#include <asm/pgalloc.h>

#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/slab.h>

#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/time.h>

#include <linux/statfs.h>
#include <linux/fs.h>
#include <linux/stat.h>
#include <linux/namei.h>

#include "hi_drv_mem.h"

#include "hi_drv_mmz.h"
#include "hi_drv_mailbox.h"
#include "drv_mailbox.h"
#include "drv_mailbox_ext.h"
#include "hi_drv_module.h"

#include "drv_cipher_compat.h" //for hash 256
#include "drv_cipher_kapi.h"
#include "drv_cipher_ext.h"
#include "drv_runtime_check.h"

#define MAX_BUFFER_LENGTH                       (0x20000)
#define REG_MAILBOX_TOTEECPU_ADDRESS            (0xf9a39310)//check smcu status is ok
#define MAILBOX_ACPU_RUNTIME_CHECK              (0x64)
#define MID_SMCU_RUNTIME_CHECK_FS               (0x24)
#define HASH_CAL_QUIT                           (0x12345678)
#define HASH_VALUE_LEN                          (32)
#define MAILBOX_TIME_OUT                        (0x806d000e)
#define MAILBOX_REG_COUNT                       (8)
#define MAILBOX_STATUS_LOAD_OK                  (0x80510002)

//OTP:runtime_check_en indicator :0xF8AB0004[1]
#define RUNTIME_CHECK_EN_REG_ADDR               (0xF8AB0004)
#define SC_SYS_BASE                             (0xF8000000)
#define SC_SYSRES                               (SC_SYS_BASE + 0x0004)
#define MAX_IOMEM_SIZE                          (0x400)
#define REG_CPU_FREQ                            (0xf8a22048)
#define REG_DDR_FREQ                            (0xf8a22128)
#define MAILBOX_RUNTIME_CHECK_FAIL              (0xA5A54B4B)
#define MAILBOX_SMCU_TO_ACPU_PARAM_ADDRESS      (0xf9a39110)

#define HI_REG_WRITE32(addr, val) (*(volatile unsigned int*)(addr) = (val))
#define HI_REG_READ32(addr, val)  ((val) = *(volatile unsigned int*)(addr))

// a dump area of check .text section of the module
#define KO_DUMP_AREA    (10 * 1024)

#define DELAY_TIME      (HI_ROOTFS_CALCULATE_DELAY_TIME)

static struct task_struct* g_pModuleCopyThread = NULL;
static struct task_struct* g_pFsCheckThread = NULL;
static unsigned int g_u32ModulePhyAddr = 0;
static unsigned char* g_pModuleVirAddr = NULL;
static int g_bRuntimeCheckEnable = HI_FALSE;
static int g_u32ModuleUsedSize = 0;
static MMZ_BUFFER_S g_stMmzBuf = {0};

static int g_bIsFirstCopy = HI_TRUE;
static int g_bRuntimeCheckSuspend = HI_FALSE;
static int g_bHashCalculateFlag = HI_FALSE;

static MAILBOX_EXPORT_FUNC_S *s_pMailboxExportFuncs = HI_NULL;
CIPHER_EXPORT_FUNC_S *s_pCipherExportFuncs = HI_NULL;

#define HI_FATAL_RTC(fmt...)                    HI_FATAL_PRINT(HI_ID_RUNTIME, fmt)
#define HI_RTC_PrintFuncErr(Func, ErrCode)      HI_FATAL_RTC("Call %s return [0x%08X]\n", #Func, ErrCode);

struct timer_list  runtime_check_timer;
static int timer_add_flag = HI_FALSE;

static void errorreset(void)
{
    unsigned int* pVIR_ADDRESS = NULL;
    HI_FATAL_RTC("runtime check error, reboot\n");
    /*  error process: reset the whole chipset */

    /* set CPU freq to 24M*/
    pVIR_ADDRESS  = (unsigned int*)ioremap_nocache(REG_CPU_FREQ, 32);
    writel(0x204, pVIR_ADDRESS);
    mdelay(1);
    writel(0x604, pVIR_ADDRESS);
    mdelay(1);
    iounmap(pVIR_ADDRESS);

    /* set DDR freq to 24M*/
    pVIR_ADDRESS  = (unsigned int*)ioremap_nocache(REG_DDR_FREQ, 32);
    writel(0x204, pVIR_ADDRESS);
    mdelay(1);
    writel(0x604, pVIR_ADDRESS);
    mdelay(1);
    iounmap(pVIR_ADDRESS);

    pVIR_ADDRESS  = (unsigned int*)ioremap_nocache(SC_SYSRES, 32);
    writel(0x1, pVIR_ADDRESS);
    iounmap(pVIR_ADDRESS);

    return;
}

static void check_hash_failed(void)
{
    unsigned int* pVIR_ADDRESS = NULL;

    pVIR_ADDRESS  = (unsigned int*)ioremap_nocache(MAILBOX_SMCU_TO_ACPU_PARAM_ADDRESS, 32);

    if (MAILBOX_RUNTIME_CHECK_FAIL == readl(pVIR_ADDRESS))
    {
        HI_FATAL_RTC("check_hash_failed error\n");
        errorreset();
    }

    iounmap(pVIR_ADDRESS);

    return;
}

static void runtime_check_timer_handler(unsigned long arg)
{
    check_hash_failed();

    if (HI_TRUE == g_bRuntimeCheckSuspend)
    {
        return;
    }

    mod_timer(&runtime_check_timer, jiffies + (HZ/10));
}

void add_runtime_check_timer(void)
{
    init_timer(&runtime_check_timer);

    runtime_check_timer.function = runtime_check_timer_handler;
    runtime_check_timer.data = (unsigned long)0;
    runtime_check_timer.expires = jiffies + (HZ/10);

    add_timer(&runtime_check_timer);
    timer_add_flag = HI_TRUE;
}

static int runtime_check_enable_check(int* pbRuntimeCheckFlag)
{
    unsigned int* pu32RegVirAddr = NULL;

    *pbRuntimeCheckFlag = HI_FALSE;

    pu32RegVirAddr = (unsigned int*)ioremap_nocache(RUNTIME_CHECK_EN_REG_ADDR, 32);
    if (pu32RegVirAddr == NULL)
    {
        HI_FATAL_RTC("ioremap_nocache error\n");
        errorreset();
        return -1;
    }

    if (*pu32RegVirAddr & 0x2)
    {
        *pbRuntimeCheckFlag = HI_TRUE;
    }

    iounmap((void*)pu32RegVirAddr);

    return 0;
}

#ifndef HI_TEE_SUPPORT
#define MAX_CHECK_COUNT 1000
static int check_SMCU_status(void)
{
    unsigned int* pu32RegVirAddr = NULL;
    unsigned int u32Count = 0;

    while (u32Count++ < MAX_CHECK_COUNT)
    {
        pu32RegVirAddr = (unsigned int*)ioremap_nocache(REG_MAILBOX_TOTEECPU_ADDRESS, 32);
        if (pu32RegVirAddr == NULL)
        {
            HI_FATAL_RTC("ioremap_nocache error\n");
            errorreset();
            return -1;
        }

        if (MAILBOX_STATUS_LOAD_OK == *pu32RegVirAddr)
        {
            break;
        }
        msleep(1);
    }

    if (u32Count >= MAX_CHECK_COUNT)
    {
        HI_FATAL_RTC("smcu status err! \n");
        iounmap((void*)pu32RegVirAddr);
        return HI_FAILURE;
    }

    iounmap((void*)pu32RegVirAddr);

    return 0;
}
#endif

void set_fisrt_copy_flag(HI_BOOL bFistCopy)
{
    g_bIsFirstCopy = bFistCopy;
    return;
}

void set_suspend_flag(HI_BOOL bRuntimeCheckSuspend)
{
    g_bRuntimeCheckSuspend = bRuntimeCheckSuspend;
    return;
}

void delete_timer(void)
{
    if (HI_TRUE == timer_add_flag)
    {
        del_timer(&runtime_check_timer);
        timer_add_flag = HI_FALSE;
    }

    return;
}

#ifdef HI_ROOTFS_RUNTIME_CHECK_ENABLE
void set_hash_calculate_flag(HI_BOOL bCalulate)
{
    g_bHashCalculateFlag = bCalulate;
    return;
}

HI_BOOL get_hash_calculate_flag(void)
{
    return g_bHashCalculateFlag;
}

HI_BOOL get_runtime_check_enable_flag(void)
{
    return g_bRuntimeCheckEnable;
}

static int calc_fs_hash(unsigned int u32Hash[8])
{
    int Ret = 0;
    unsigned int id = 0;
    unsigned char u8HashValue[HASH_VALUE_LEN];
    static unsigned char* pTmpbuf = NULL;
    struct file* fp = NULL;
    mm_segment_t fs = {0};
    struct path path = {0};
    struct kstatfs st = {0};
    loff_t pos = {0};
    unsigned int u32ReadLength = 0;
    unsigned int u32LeftLength = 0;
    unsigned int u32HashLen = 0;

    Ret = HI_DRV_MODULE_GetFunction(HI_ID_CIPHER, (HI_VOID**)&s_pCipherExportFuncs);
    if ((HI_SUCCESS != Ret) || (HI_NULL == s_pCipherExportFuncs))
    {
        HI_RTC_PrintFuncErr(HI_DRV_MODULE_GetFunction, Ret);
        return -1;
    }

    memset(u8HashValue, 0, sizeof(char) * HASH_VALUE_LEN);

    fs = get_fs();
    set_fs(KERNEL_DS);
    set_fs(fs);

    Ret = user_path("/", &path);
    if (0 != Ret || path.dentry == NULL)
    {
        HI_FATAL_RTC("user_path() error, reboot\n");
        errorreset();
        return -1;
    }

    Ret = vfs_statfs(&path, &st);
    if (0 != Ret)
    {
        HI_FATAL_RTC("vfs_statfs() error, reboot\n");
        errorreset();
        return -1;
    }
    path_put(&path);

    /* get file handle */
    fp = filp_open("/dev/ram0", O_RDONLY | O_LARGEFILE, 0644);
    if (IS_ERR(fp))
    {
        HI_FATAL_RTC("filp_open() error, reboot\n");
        errorreset();
        return -1;
    }

    if (pTmpbuf == NULL)
    {
        pTmpbuf = HI_VMALLOC(HI_ID_CA, MAX_BUFFER_LENGTH);
        if (pTmpbuf == NULL)
        {
            filp_close(fp, NULL);
            HI_FATAL_RTC("filp_close() error, reboot\n");
            errorreset();
            return -1;
        }
    }

    Ret = s_pCipherExportFuncs->pfnCipherHashStart(&id, CRYP_CIPHER_HASH_TYPE_SHA256, NULL, 0);
    if (HI_SUCCESS != Ret)
    {
        filp_close(fp, NULL);
        HI_RTC_PrintFuncErr(HI_DRV_CIPHER_HashStart, Ret);
        errorreset();
        return -1;
    }

    /* get file content */
    pos = 0;
    u32LeftLength = st.f_bsize * st.f_blocks;
    while (u32LeftLength > 0)
    {
        if (HI_TRUE == g_bRuntimeCheckSuspend) //It means Runtime-Check module is to suspend.
        {
            Ret = s_pCipherExportFuncs->pfnCipherHashFinish(id, u8HashValue, &u32HashLen);
            if (HI_SUCCESS != Ret)
            {
                filp_close(fp, NULL);
                HI_RTC_PrintFuncErr(HI_DRV_CIPHER_HashFinish, Ret);
            }
            g_bHashCalculateFlag = HI_FALSE; //close hash calculate and then go to standby

            return HASH_CAL_QUIT;
        }

        u32ReadLength = u32LeftLength >= MAX_BUFFER_LENGTH ? MAX_BUFFER_LENGTH : u32LeftLength;
        u32LeftLength -= u32ReadLength;
        fs = get_fs();
        set_fs(KERNEL_DS);
        vfs_read(fp, pTmpbuf, u32ReadLength, &pos);
        set_fs(fs);

        Ret = s_pCipherExportFuncs->pfnCipherHashUpdate(id, pTmpbuf, u32ReadLength);
        if (HI_SUCCESS != Ret)
        {
            filp_close(fp, NULL);
            HI_RTC_PrintFuncErr(HI_DRV_CIPHER_HashUpdate, Ret);
            errorreset();
            return -1;
        }

        if (HI_TRUE == g_bRuntimeCheckSuspend) //It means Runtime-Check module is to suspend.
        {
            Ret = s_pCipherExportFuncs->pfnCipherHashFinish(id, u8HashValue, &u32HashLen);
            if (HI_SUCCESS != Ret)
            {
                filp_close(fp, NULL);
                HI_RTC_PrintFuncErr(HI_DRV_CIPHER_HashFinish, Ret);
            }

            g_bHashCalculateFlag = HI_FALSE; //close hash calculate and then go to standby

            return HASH_CAL_QUIT;
        }
        msleep(1);

    }

    Ret = s_pCipherExportFuncs->pfnCipherHashFinish(id, u8HashValue, &u32HashLen);
    if (HI_SUCCESS != Ret)
    {
        filp_close(fp, NULL);
        HI_RTC_PrintFuncErr(HI_DRV_CIPHER_HashFinish, Ret);
        errorreset();
        return -1;
    }

    if (HASH_VALUE_LEN != u32HashLen)
    {
        filp_close(fp, NULL);
        errorreset();
        return -1;
    }

    memcpy(u32Hash, u8HashValue, u32HashLen);

    /* close file handle */
    filp_close(fp, NULL);

    if (NULL != pTmpbuf)
    {
        HI_VFREE(HI_ID_CA, (HI_VOID*)pTmpbuf);
        pTmpbuf = NULL;
    }

    return 0;
}

static int send_fs_check_vector(unsigned int handle)
{
    HI_DRV_MAILBOX_BUFFER_S stBufferInfo;
    unsigned int au32MailboxBuf[MAILBOX_REG_COUNT] = {0};
    unsigned int u32HashValue[8] = {0};
    unsigned int u32ReceiveLen  = MAILBOX_REG_COUNT * sizeof(unsigned int);
    unsigned int i = 0;
    int Ret = 0;

    Ret = calc_fs_hash(u32HashValue);
    if (HASH_CAL_QUIT == Ret)
    {
        //HI_RTC_PrintFuncErr(calc_fs_hash, Ret)
        //HI_FATAL_RTC("HASH_CAL_QUIT! \n");
        return 0;
    }
    else if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(calc_fs_hash, Ret)
        errorreset();
        return -1;
    }

    for (i = 0; i < HASH_VALUE_LEN / 4; i++)
    {
        au32MailboxBuf[i] = u32HashValue[i];
    }

    memset(&stBufferInfo, 0x00, sizeof(HI_DRV_MAILBOX_BUFFER_S));
    stBufferInfo.pMessage = au32MailboxBuf;
    stBufferInfo.u32MessageLen = 8 * sizeof(unsigned int);
    stBufferInfo.pOutBuffer = au32MailboxBuf;
    stBufferInfo.pu32OutBufferLen = &u32ReceiveLen;

    Ret = s_pMailboxExportFuncs->pfnMailbox_SendMessage(handle, MID_SMCU_RUNTIME_CHECK_FS, &stBufferInfo, 1, 1000);
    if (MAILBOX_TIME_OUT == Ret)
    {
        //HI_FATAL_RTC("mailbox timeout! \n");
        return MAILBOX_TIME_OUT;
    }
    else if ((0 != Ret) || (MAILBOX_STATUS_LOAD_OK != au32MailboxBuf[0]))
    {
        HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_SendMessage, Ret);
        errorreset();
        return -1;
    }

    return 0;
}

static int fs_check_thread_proc(void* argv)
{
    unsigned int handle = HI_INVALID_HANDLE;
    int Ret = 0;

    while (g_bRuntimeCheckEnable)
    {
        if (g_bIsFirstCopy == HI_TRUE) //It means Runtime-Checking is not ready.
        {
            msleep(DELAY_TIME);
            continue;
        }

        if (HI_TRUE == g_bRuntimeCheckSuspend) //It means Runtime-Checking is not ready.
        {
            g_bHashCalculateFlag = HI_FALSE;

            msleep(DELAY_TIME);
            continue;
        }

        Ret = HI_DRV_MODULE_GetFunction(HI_ID_MAILBOX, (HI_VOID**)&s_pMailboxExportFuncs);
        if ((HI_SUCCESS != Ret) || (HI_NULL == s_pMailboxExportFuncs))
        {
            HI_RTC_PrintFuncErr(HI_DRV_MODULE_GetFunction, Ret);
            return -1;
        }

        Ret = s_pMailboxExportFuncs->pfnMailbox_Open(&handle, MID_ACPU_COMMON);
        if (0 != Ret)
        {
            HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_Open, Ret);
            errorreset();
            return -1;
        }

        Ret = send_fs_check_vector(handle);
        if (MAILBOX_TIME_OUT == Ret)
        {
            (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);

            msleep(DELAY_TIME);
            continue;
        }
        else if (0 != Ret)
        {
            HI_RTC_PrintFuncErr(send_fs_check_vector, Ret)
            (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
            errorreset();
            return -1;
        }

        Ret = s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        if (0 != Ret)
        {
            HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_Close, Ret);
            errorreset();
            return -1;
        }

        if (HI_TRUE == g_bRuntimeCheckSuspend) //It means Runtime-Checking is not ready.
        {
            g_bHashCalculateFlag = HI_FALSE;

            msleep(DELAY_TIME);
            continue;
        }

        msleep(DELAY_TIME);
    }

    return 0;
}
#endif

static int calc_ko_size(void)
{
    int u32ko_size = 0;
    struct module* p = NULL;
    struct module* mod = NULL;
    struct list_head* pModules = NULL;

    module_get_pointer(&pModules);
    list_for_each_entry_rcu(mod, pModules, list)
    {
        p = find_module(mod->name);
        if (p)
        {
            u32ko_size += p->core_text_size;
            //HI_FATAL_CA("module:%s, size: %d\n", mod->name, p->core_text_size);
        }
    }

    return u32ko_size;
}

static int get_kernel_info(unsigned int* pu32StartAddr, unsigned int* pu32EndAddr)
{
    unsigned char* pTmpbuf = NULL;
    struct file* fp = NULL;
    mm_segment_t fs;
    loff_t pos = 0;
    char s8TmpBuf[32];
    char* pstr = NULL;

    memset(s8TmpBuf, 0, sizeof(s8TmpBuf));
    memcpy(s8TmpBuf, "Kernel code", strlen("Kernel code"));
    s8TmpBuf[sizeof (s8TmpBuf) - 1] = '\0';

    memset(&fs, 0, sizeof(mm_segment_t));

    fs = get_fs();
    set_fs(KERNEL_DS);
    set_fs(fs);

    /* get file handle */
    fp = filp_open("/proc/iomem", O_RDONLY | O_LARGEFILE, 0644);
    if (IS_ERR(fp))
    {
        HI_FATAL_RTC("open /proc/iomem error, reboot\n");
        errorreset();
        return -1;
    }

    pTmpbuf = kmalloc(MAX_IOMEM_SIZE, GFP_TEMPORARY);
    if (pTmpbuf == NULL)
    {
        filp_close(fp, NULL);
        HI_FATAL_RTC("kmalloc error, reboot\n");
        errorreset();
        return -1;
    }
    memset(pTmpbuf, 0, MAX_IOMEM_SIZE);

    /* get file content */
    pos = 0;
    fs = get_fs();
    set_fs(KERNEL_DS);
    vfs_read(fp, pTmpbuf, MAX_IOMEM_SIZE - 1, &pos);
    set_fs(fs);

    pstr = strstr(pTmpbuf, s8TmpBuf);
    if (pstr == NULL)
    {
        kfree(pTmpbuf);
        filp_close(fp, NULL);
        HI_FATAL_RTC("Get file content error, reboot\n");
        errorreset();
        return -1;
    }
    pos = pstr - (char*)pTmpbuf;

    memset(s8TmpBuf, 0, sizeof(s8TmpBuf));
    memcpy(s8TmpBuf, pTmpbuf + pos - 20, 8);
    *pu32StartAddr = simple_strtoul(s8TmpBuf, 0, 16);

    memset(s8TmpBuf, 0, sizeof(s8TmpBuf));
    memcpy(s8TmpBuf, pTmpbuf + pos - 11, 8);
    *pu32EndAddr = simple_strtoul(s8TmpBuf, 0, 16);

    kfree(pTmpbuf);
    /* close file handle */
    filp_close(fp, NULL);

    return 0;
}

static int send_check_vector(void)
{
    unsigned int handle = HI_INVALID_HANDLE;
    HI_DRV_MAILBOX_BUFFER_S stBufferInfo;
    unsigned int au32MailboxBuf[MAILBOX_REG_COUNT] = {0};
    unsigned int u32SectionNum = 2; //kernel, KO
    unsigned int u32KernelStartAddr = 0;
    unsigned int u32KernelEndAddr = 0;
    unsigned int u32ReceiveLen  = MAILBOX_REG_COUNT * sizeof(unsigned int);
    int Ret = 0;

#ifndef HI_TEE_SUPPORT
    Ret = check_SMCU_status();
    if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(check_SMCU_status, Ret);
        errorreset();
        return -1;
    }
#endif

    Ret = HI_DRV_MODULE_GetFunction(HI_ID_MAILBOX, (HI_VOID**)&s_pMailboxExportFuncs);
    if ((HI_SUCCESS != Ret) || (HI_NULL == s_pMailboxExportFuncs))
    {
        HI_RTC_PrintFuncErr(HI_DRV_MODULE_GetFunction, Ret);
        errorreset();
        return -1;
    }

    Ret = s_pMailboxExportFuncs->pfnMailbox_Open(&handle, MID_ACPU_COMMON);
    if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_Open, Ret);
        errorreset();
        return -1;
    }

    //kernel address, length
    Ret = get_kernel_info(&u32KernelStartAddr, &u32KernelEndAddr);
    if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(get_kernel_info, Ret);
        (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        errorreset();
        return -1;
    }

    au32MailboxBuf[0] = u32SectionNum;
    au32MailboxBuf[1] = u32KernelStartAddr; /* start address of kernel checked area*/
    au32MailboxBuf[2] = u32KernelEndAddr - u32KernelStartAddr; /* size of kernel checked area */
    au32MailboxBuf[3] = g_u32ModulePhyAddr; /* start address of KO checked area*/
    au32MailboxBuf[4] = g_u32ModuleUsedSize; /* size of KO checked area */

    memset(&stBufferInfo, 0x00, sizeof(HI_DRV_MAILBOX_BUFFER_S));
    stBufferInfo.pMessage = au32MailboxBuf;
    stBufferInfo.u32MessageLen = 5 * sizeof(unsigned int);
    stBufferInfo.pOutBuffer = au32MailboxBuf;
    stBufferInfo.pu32OutBufferLen = &u32ReceiveLen;

    Ret = s_pMailboxExportFuncs->pfnMailbox_SendMessage(handle, MID_SMCU_RUNTIME_CHECK, &stBufferInfo, 1, 1000);
    if (MAILBOX_TIME_OUT == Ret)
    {
        (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        //HI_FATAL_RTC("mailbox timeout! \n");
        return MAILBOX_TIME_OUT;
    }
    else if ((0 != Ret) || (MAILBOX_STATUS_LOAD_OK != au32MailboxBuf[0]))
    {
        HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_SendMessage, Ret);
        (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        errorreset();
        return -1;
    }

#ifdef HI_ROOTFS_RUNTIME_CHECK_ENABLE
    Ret = send_fs_check_vector(handle);
    if (MAILBOX_TIME_OUT == Ret)
    {
        (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        //HI_FATAL_RTC("mailbox timeout! \n");
        return MAILBOX_TIME_OUT;
    }
    else if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(send_fs_check_vector, Ret)
        (HI_VOID)s_pMailboxExportFuncs->pfnMailbox_Close(handle);
        errorreset();
        return -1;
    }
#endif

    Ret = s_pMailboxExportFuncs->pfnMailbox_Close(handle);
    if (0 != Ret)
    {
        HI_RTC_PrintFuncErr(HI_DRV_MAILBOX_Close, Ret);
        errorreset();
        return -1;
    }

    return 0;
}

static int module_copy_thread_proc(void* argv)
{
    struct module* p = NULL;
    struct module* mod = NULL;
    struct list_head* pModules = NULL;
    int Ret = 0;
    unsigned char* pAddr = NULL;
    unsigned int u32ModuleSize;

    g_u32ModuleUsedSize = calc_ko_size() + KO_DUMP_AREA;
    memset(&g_stMmzBuf, 0, sizeof(MMZ_BUFFER_S));

    Ret =  HI_DRV_MMZ_AllocAndMap("RUNTIME_CHECK", "RT", g_u32ModuleUsedSize, 0, &g_stMmzBuf);
    if (HI_FAILURE == Ret)
    {
        kthread_stop(g_pFsCheckThread);

        HI_FATAL_RTC("Failed to malloc MMZ buffer!, reboot\n");
        errorreset();
        return -1;
    }

    g_u32ModulePhyAddr = g_stMmzBuf.u32StartPhyAddr;
    g_pModuleVirAddr = g_stMmzBuf.pu8StartVirAddr;

    if ((!g_bRuntimeCheckEnable) || (g_u32ModulePhyAddr == 0))
    {
        errorreset();
        return 0;
    }

    memset(g_pModuleVirAddr, 0x0, g_u32ModuleUsedSize);

    module_get_pointer(&pModules);
    while (1)
    {
        if (HI_TRUE == g_bRuntimeCheckSuspend)
        {
            msleep(DELAY_TIME);
            continue;
        }

        pAddr = g_pModuleVirAddr;
        u32ModuleSize = 0;

        list_for_each_entry_rcu(mod, pModules, list)
        {
            p = find_module(mod->name);
            if (p)
            {
                u32ModuleSize += p->core_text_size;
                if (g_u32ModuleUsedSize < u32ModuleSize)
                {
                    HI_FATAL_RTC("total ko size error, reboot\n");
                    errorreset();
                    return 0;
                }

                memcpy((void*)pAddr, (void*)(p->module_core), p->core_text_size);
                pAddr += p->core_text_size;
            }
        }

        if (g_u32ModuleUsedSize != u32ModuleSize + KO_DUMP_AREA) //alloc mem size is u32ModuleSize + KO_DUMP_AREA
        {
            HI_FATAL_RTC("Runtime-Checking ko error, reboot\n");
            errorreset();
            return 0;
        }

        if (g_bIsFirstCopy)
        {
            Ret = send_check_vector();
            if (MAILBOX_TIME_OUT == Ret)
            {
                msleep(DELAY_TIME);
                continue;
            }
            if (0 != Ret)
            {
                HI_RTC_PrintFuncErr(send_check_vector, Ret);
                errorreset();
                return -1;
            }

            g_bIsFirstCopy = HI_FALSE;  //It means runtime-checking is ready.
            HI_PRINT("Runtime check start\n");

            add_runtime_check_timer();
        }

        msleep(DELAY_TIME);
    }

    return Ret;
}

int  DRV_RUNTIME_CHECK_Init(void)
{
    int Ret = 0;

    Ret = runtime_check_enable_check(&g_bRuntimeCheckEnable);
    if (0 != Ret)
    {
        HI_FATAL_RTC("runtime_check_enable_check error\n");
        errorreset();
        return -1;
    }

    if (g_bRuntimeCheckEnable != HI_TRUE)
    {
        return 0;
    }

    if (NULL == g_pModuleCopyThread)
    {
        g_pModuleCopyThread = kthread_create(module_copy_thread_proc, NULL, "ModuleCopyThread");
        if (NULL == g_pModuleCopyThread)
        {
            errorreset();
            return -1;
        }
        wake_up_process(g_pModuleCopyThread);
    }

#ifdef HI_ROOTFS_RUNTIME_CHECK_ENABLE
    if (NULL == g_pFsCheckThread)
    {
        g_pFsCheckThread = kthread_create(fs_check_thread_proc, NULL, "FsCheckThread");
        if (NULL == g_pFsCheckThread)
        {
            errorreset();
            return -1;
        }
        wake_up_process(g_pFsCheckThread);
    }

#endif

    return 0;
}

void DRV_RUNTIME_CHECK_Exit(void)
{
    if (g_bRuntimeCheckEnable != HI_TRUE)
    {
        return;
    }

    HI_FATAL_RTC("runtime check ko can not deinit, reboot\n");
    errorreset();

    if (NULL != g_pModuleCopyThread)
    {
        kthread_stop(g_pModuleCopyThread);
    }

    if (NULL != g_pFsCheckThread)
    {
        kthread_stop(g_pFsCheckThread);
    }

    if (g_pModuleVirAddr != 0)
    {
        HI_DRV_MMZ_UnmapAndRelease(&g_stMmzBuf);
    }

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

