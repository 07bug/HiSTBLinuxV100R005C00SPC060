#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include "hi_common.h"
#include "hi_osal.h"
#include "hi_reg_common.h"
#include "hi_drv_proc.h"
#include "hi_drv_pmoc.h"
#include "drv_pmoc_priv.h"
#include "clock.h"
#include "hi_dvfs.h"
#include "hipm.h"

#define TEMP_DOWN HI_TEMP_CTRL_DOWN_THRESHOLD
#define TEMP_UP HI_TEMP_CTRL_UP_THRESHOLD
#define TEMP_REBOOT HI_TEMP_CTRL_REBOOT_THRESHOLD
#define CPU_SCALING_MAX_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
#define CPU_SCALING_MIN_FREQ "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"

HI_U8 g_u8TempCtrlEnable;
HI_U32 g_bEneterLowTemp = HI_FALSE;
static HI_S16 g_s16TempUp;
static HI_S16 g_s16TempDown;
static HI_S16 g_s16TempReboot;
static struct task_struct *pstTempCtrlThread = HI_NULL;

extern struct clk mpu_ck;
extern struct mutex hi_cpufreq_lock;
extern unsigned int cpu_dvfs_enable;
extern HI_S32 set_mcu_status(HI_BOOL bStart);
extern HI_VOID get_mcu_status(HI_BOOL * bStart);
extern HI_S32  c51_loadPara(HI_VOID);
extern HI_VOID smcu_close_clk(HI_VOID);
extern HI_BOOL bSMCULoadOK;
extern int write_cpufreq_node(const char * node, int value);
extern int read_cpufreq_node(const char * node);

#ifdef HI_PROC_SUPPORT
static HI_VOID TempProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo tempctrl=1 > /proc/hisi/msp/pm_temp, enable temperature control\n"
        "echo tempdown=110 > /proc/hisi/msp/pm_temp, set down threshold temperature.\n"
        "echo tempup=100 > /proc/hisi/msp/pm_temp, set up threshold temperature.\n"
        "echo tempreboot=125 > /proc/hisi/msp/pm_temp, set reboot threshold temperature.\n"
        );

    return;
}

static HI_S32 TempProcRead(struct seq_file *p, HI_VOID *v)
{
    PROC_PRINT(p, "Temperature control is %s \n", (g_u8TempCtrlEnable == HI_TRUE) ? "On" : "Off");
    PROC_PRINT(p, "Temperature down threshold:  %d degree\n", g_s16TempDown);
    PROC_PRINT(p, "Temperature up threshold:  %d degree\n", g_s16TempUp);
    PROC_PRINT(p, "Temperature reboot threshold:  %d degree\n", g_s16TempReboot);

    return HI_SUCCESS;
}

static HI_S32 TempProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if ((count > 63) || (copy_from_user(ProcPara, buf, count)))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        return count;
    }

    if (1 == u32CmdNum)
    {
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPCTRL, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_u8TempCtrlEnable = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPDOWN, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempDown = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPUP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempUp = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPREBOOT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempReboot = PMParseValue(pstCmd[0].aszValue);
        }
        else
        {
            HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
            TempProcHelper();
            return count;
        }
    }

    return count;
}

#endif  // #ifdef HI_PROC_SUPPORT

HI_VOID adjust_volt_in_low_temp(HI_VOID)
{
    HI_U32 u32OriCpuFreq;

    /* lock to avoid DVFS at the same time */
    mutex_lock(&hi_cpufreq_lock);

    u32OriCpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
#if defined(CHIP_TYPE_hi3798mv300)
    if ((u32OriCpuFreq < 400000) || (u32OriCpuFreq > 800000))
    {
        mutex_unlock(&hi_cpufreq_lock);
        return;
    }
#endif
    hi_device_scale(&mpu_dev, u32OriCpuFreq, u32OriCpuFreq);

    mutex_unlock(&hi_cpufreq_lock);

    /* do not adjust too often */
    msleep(2000);

    return;
}

HI_VOID cpu_low_temp_ctl(HI_S16 s16Temp)
{
    if (s16Temp <= TEMP_LOW)
    {
        if (HI_FALSE == g_bEneterLowTemp)
        {
            HI_INFO_PM(" enter cpu_low_tmp_ctl\n");
            adjust_volt_in_low_temp();
        }
    }
    else
    {
        if (HI_TRUE == g_bEneterLowTemp)
        {
            HI_INFO_PM(" quit cpu_low_tmp_ctl\n");
            adjust_volt_in_low_temp();
        }
    }

    return;
}

HI_S32 temp_control_thread(void *Arg)
{
    HI_S16 s16Temp;
    HI_U32 u32OriCpuFreq = DEFAULT_INIT_FREQ;
    HI_U8 u8TimeInterval = 100;
    HI_BOOL bNeedReboot = HI_TRUE;
    HI_BOOL bStatus = HI_FALSE;
    HI_U32 u32TempStatus = TEMP_STATUS_NORMAL;

    HI_INFO_PM("enter temperature_control_thread\n");

    g_s16TempUp = TEMP_UP;
    g_s16TempDown = TEMP_DOWN;
    g_s16TempReboot = TEMP_REBOOT;
    g_u8TempCtrlEnable = HI_TRUE;

    while (!kthread_should_stop())
    {
        msleep(u8TimeInterval);

        if (HI_FALSE == g_u8TempCtrlEnable)
        {
            continue;
        }

        mpu_get_temp(&s16Temp);

        cpu_low_temp_ctl(s16Temp);

        if (s16Temp <= TEMP_LOW)
        {
            u32TempStatus = TEMP_STATUS_LOW;
        }
        else if (s16Temp < g_s16TempUp)
        {
            if (u32TempStatus == TEMP_STATUS_CONTROL)
            {
                write_cpufreq_node(CPU_SCALING_MAX_FREQ, u32OriCpuFreq);
            }
            u32TempStatus = TEMP_STATUS_NORMAL;
            bNeedReboot = HI_TRUE;
            u8TimeInterval = 100;
        }
        else if ((g_s16TempDown <= s16Temp) && (s16Temp < g_s16TempReboot))
        {
            /* set min freq to max freq */
            if (u32TempStatus != TEMP_STATUS_CONTROL)
            {
                u32OriCpuFreq = read_cpufreq_node(CPU_SCALING_MAX_FREQ);
                write_cpufreq_node(CPU_SCALING_MAX_FREQ, read_cpufreq_node(CPU_SCALING_MIN_FREQ));
            }

            u32TempStatus = TEMP_STATUS_CONTROL;
            bNeedReboot = HI_TRUE;
            u8TimeInterval = 20;
        }
        else if (s16Temp >= g_s16TempReboot)
        {
            if (u32TempStatus == TEMP_STATUS_NORMAL)
            {
                u32OriCpuFreq = read_cpufreq_node(CPU_SCALING_MAX_FREQ);
                write_cpufreq_node(CPU_SCALING_MAX_FREQ, read_cpufreq_node(CPU_SCALING_MIN_FREQ));

                /* in the process of start system, do not suspend system  */
                u32TempStatus = TEMP_STATUS_CONTROL;
                bNeedReboot = HI_FALSE;
                u8TimeInterval = 20;
            }
            else
            {
                if (HI_TRUE == bNeedReboot)
                {
                    HI_ERR_PM("Tsensor is extremly high, suspend system!!\n");

                    c51_loadPara();
                    get_mcu_status(&bStatus);
                    if (HI_FALSE == bStatus)
                    {
                        set_mcu_status(0x1); //start MCU
                    }

                    u32TempStatus = TEMP_STATUS_STANDBY;
                }
            }
        }

        /* save the temp status to 0xf80000b4 to inform other module */
        /* if SC_GENm[13] used as standby flag, don't change it      */
        if (g_pstRegSysCtrl->SC_GENm[13] != WAKE_FROM_DDR)
        {
            g_pstRegSysCtrl->SC_GENm[13] = u32TempStatus;
        }
    }

    return HI_SUCCESS;
}

int hi_temp_init(void)
{
  #ifdef HI_PROC_SUPPORT
    DRV_PROC_ITEM_S *item;

    item = HI_DRV_PROC_AddModule("pm_temp", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = TempProcRead;
    item->write = TempProcWrite;
  #endif

    pstTempCtrlThread = kthread_create(temp_control_thread, NULL, "temperature_control");
    if (IS_ERR(pstTempCtrlThread))
    {
        HI_ERR_PM("create mcu watchdog thread failed.\n");
        return HI_FAILURE;
    }
    wake_up_process(pstTempCtrlThread);

    return HI_SUCCESS;
}

void hi_temp_deinit(void)
{
#ifdef HI_PROC_SUPPORT
    HI_DRV_PROC_RemoveModule("pm_temp");
#endif

    if (pstTempCtrlThread)
    {
        kthread_stop(pstTempCtrlThread);
        pstTempCtrlThread = HI_NULL;
    }

    return;
}

