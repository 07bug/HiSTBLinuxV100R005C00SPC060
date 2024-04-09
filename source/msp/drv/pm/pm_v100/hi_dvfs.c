/*
 * hisilicon DVFS Management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
 */

#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/plist.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/kthread.h>

#include "clock.h"
#include "opp.h"
#include "hi_reg_common.h"
#include "hi_drv_reg.h"
#include "hi_drv_sys.h"
#include "hi_dvfs.h"
#include "hi_drv_pmoc.h"
#include "drv_i2c_ext.h"
#include "hi_drv_module.h"
#include "hi_kernel_adapt.h"

extern struct clk mpu_ck;

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#define PWM_CPU PERI_PMC7
#else
#define PWM_CPU PERI_PMC6
#endif

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200)
#define PWM_CORE PERI_PMC8
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#define PWM_CORE PERI_PMC6
#else
#define PWM_CORE PERI_PMC7
#endif

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 10 /*ms*/

extern HI_CHIP_TYPE_E g_enChipType;
extern HI_CHIP_VERSION_E g_enChipID;
extern unsigned int cpu_dvfs_enable;
unsigned int cur_cpu_volt  = 1300;
unsigned int cur_core_volt = 1150;
unsigned int init_core_volt = 1150;

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#define CPU_FREQ_SVB_CNT 6
/* BGA 15*15 */
static unsigned int cpu_volt_svb_package1[CPU_FREQ_SVB_CNT][4] = {
    {1600000, 1100, 1160, 1250},
    {1500000, 1040, 1110, 1170},
    {800000, 800, 890, 930},
    {600000, 800, 890, 930},
    {400000, 800, 890, 930}
};

static unsigned int cpu_volt_svb_default[CPU_FREQ_SVB_CNT][4] = {
    {1600000, 1080, 1150, 1210},
    {1500000, 1020, 1090, 1140},
    {1450000, 980, 1050, 1110},
    {800000, 800, 840, 880},
    {600000, 800, 840, 880},
    {400000, 800, 840, 880}
};
#endif

HI_U32 g_corner_type = 0;

#ifndef HI_AVS_HARDWARE
static struct task_struct *pstAVSThread = HI_NULL;
#endif

HI_DECLARE_MUTEX(g_CPUAVSMutex);
static unsigned int cpu_avs_enable = HI_FALSE;

int core_volt_scale(unsigned int volt);

DEFINE_MUTEX(hi_dvfs_lock);

/**
 * struct hi_dvfs_info - The per vdd dvfs info
 * @user_lock:  spinlock for plist operations
 *
 * This is a fundamental structure used to store all the required
 * DVFS related information for a vdd.
 */
struct hi_dvfs_info
{
    unsigned int volt;
    unsigned int new_freq;
    unsigned int old_freq;
};

static void device_volt_scale(unsigned char device, unsigned int volt)
{
    unsigned int * pwm_reg;
    unsigned int period, duty, v, tmp;
    unsigned int vmax, vmin, pwc, pws;

    if (CPU_DEVICE == device)
    {
        pwm_reg = PWM_CPU;
        vmax = CPU_VMAX;
        vmin = CPU_VMIN;
    }
    else if (CORE_DEVICE == device)
    {
        pwm_reg = PWM_CORE;
        vmax = CORE_VMAX;
        vmin = CORE_VMIN;
    }
    else
    {
        HI_ERR_PM("Not supprot this device .\n");
        return;
    }

    pwc = PWM_CLASS;
    pws = PWM_STEP;

    period = (((vmax - vmin) * pwc) / pws) + 1;
    duty = (((vmax - volt) * pwc) / pws) + 1;

    HI_REG_READ32(pwm_reg, v);
    tmp = PWM_PERIOD_MASK;
    v &= ~tmp;
    v |= period;

    tmp = PWM_DUTY_MASK;
    v &= ~tmp;
    v |= duty << 16;
    HI_REG_WRITE32(pwm_reg, v);

    return;
}

int cpu_volt_scale(unsigned int volt)
{
#if defined(CHIP_TYPE_hi3716mv410)
    return 0;
#endif

    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);

    if (volt > CPU_VMAX)
    {
        HI_ERR_PM("volt %d is out of range! Force it to vmax\n", volt);
        volt = CPU_VMAX;
    }
    else if (volt < CPU_VMIN)
    {
        HI_ERR_PM("volt %d is out of range! Do not change volt \n", volt);
        return 0;
    }

    device_volt_scale(CPU_DEVICE, volt);

    cur_cpu_volt = volt;

    return 0;
}

unsigned int CPU_AVS_GetStatus(void)
{
    return cpu_avs_enable;
}

void CPU_AVS_Enable(unsigned int enable)
{
#ifdef HI_AVS_HARDWARE
    HI_U32 u32RegVal;
#endif

#ifdef HI_AVS_HARDWARE
    HI_REG_READ32(PERI_PMC218, u32RegVal);
    if (HI_TRUE == enable)
    {
        u32RegVal |= 0x1;
    }
    else
    {
        u32RegVal &= 0xfffffffe;
    }
    HI_REG_WRITE32(PERI_PMC218, u32RegVal);
#endif

    cpu_avs_enable = enable;

    HI_INFO_PM("\n CPU_AVS_Enable = %d \n", enable);
}

extern unsigned int cur_cpu_hpm;
extern unsigned int cur_cpu_vmin;
extern unsigned int cur_cpu_vmax;
HI_S32 cpu_avs_thread(void *Arg)
{
    HI_U32 u32HpmCode, u32HpmCodeAverage;
    HI_U32 u32RegVal;
    HI_U8 i;
    HI_S32 ret;

    while (!kthread_should_stop())
    {
        msleep(AVS_INTERVAL);

        if ((!CPU_AVS_GetStatus()) || (!cpu_dvfs_enable))
        {
            continue;
        }

        /* read current code */
        u32HpmCodeAverage = 0;
        for (i = 0; i < 2; i++)
        {
            HI_REG_READ32(PERI_PMC31, u32RegVal);
            u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u32HpmCodeAverage += u32HpmCode;
            u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u32HpmCodeAverage += u32HpmCode;

            HI_REG_READ32(PERI_PMC32, u32RegVal);
            u32HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u32HpmCodeAverage += u32HpmCode;
            u32HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u32HpmCodeAverage += u32HpmCode;

            msleep(4);
        }

        u32HpmCodeAverage = u32HpmCodeAverage / (i * 4);

        HI_INFO_PM("\n show u32HpmCodeAverage = 0x%x target hpm = 0x%x \n", u32HpmCodeAverage, cur_cpu_hpm);

        /* compare code value */
        if (u32HpmCodeAverage <= cur_cpu_hpm)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /* up 10mv */
            if (cur_cpu_volt < cur_cpu_vmax)
            {
                cpu_volt_scale(cur_cpu_volt + AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else if ((u32HpmCodeAverage - cur_cpu_hpm) >= 0xa)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /*down 10mv */
            if (cur_cpu_volt > cur_cpu_vmin)
            {
                cpu_volt_scale(cur_cpu_volt - AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else
        {
            msleep(10 * AVS_INTERVAL);
        }
    }

    return HI_SUCCESS;
}

unsigned int mpu_get_volt(void)
{
    unsigned int v;

    HI_REG_READ32(PWM_CPU, v);

    v = (v | 0xffff) >> 16;
    if (v == 0)
    {
        return CPU_VMAX;
    }
    v = CPU_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;

    return v;
}

void mpu_init_volt(void)
{
    /* get cpu volt set in boot */
    cur_cpu_volt = mpu_get_volt();

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    g_corner_type = (g_pstRegSysCtrl->SC_GENm[17] >> 24) & 0xff;
#else
    g_corner_type = (g_pstRegSysCtrl->SC_GEN17 >> 24) & 0xff;
#endif
    if ((g_corner_type > CHIP_TYPE_SS) || (g_corner_type < CHIP_TYPE_FF))
    {
        g_corner_type = CHIP_TYPE_SS;
    }

 #ifndef HI_AVS_HARDWARE
    pstAVSThread = kthread_create(cpu_avs_thread, NULL, "cpu_avs");
    if (IS_ERR(pstAVSThread))
    {
        HI_ERR_PM("create avs thread failed.\n");
        return;
    }
    wake_up_process(pstAVSThread);
 #endif

    return;
}

void mpu_deinit_volt(void)
{
#ifndef HI_AVS_HARDWARE
    if (pstAVSThread)
    {
        kthread_stop(pstAVSThread);
        pstAVSThread = HI_NULL;
    }
#endif
}

int core_volt_scale(unsigned int volt)
{
    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);
    if (volt > CORE_VMAX)
    {
        HI_ERR_PM("volt %d is out of range! Force it to vmax\n", volt);
        volt = CORE_VMAX;
    }
    else if (volt < CORE_VMIN)
    {
        HI_ERR_PM("volt %d is out of range! Do not change volt \n", volt);
        return 0;
    }
    device_volt_scale(CORE_DEVICE, volt);

    cur_core_volt = volt;

    return 0;
}

unsigned int core_get_volt(void)
{
    unsigned int v;

    /* get core volt set in boot */
    HI_REG_READ32(PWM_CORE, v);

    v = (v | 0xffff) >> 16;
    if (v == 0)
    {
        return CORE_VMAX;
    }
    v = CORE_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;

    return v;
}

void core_init_volt(void)
{
    cur_core_volt = core_get_volt();
    init_core_volt = cur_core_volt;

    return;
}

/**
 * _dvfs_scale() : Scale the devices associated with a voltage domain
 *
 * Returns 0 on success else the error value.
 */
static int _dvfs_scale(struct device *target_dev, struct hi_dvfs_info *tdvfs_info)
{
    struct clk * clk;
    int ret;

    HI_INFO_PM("%s rate=%ld\n", __FUNCTION__, tdvfs_info->new_freq);

    clk = &mpu_ck;
    if (tdvfs_info->new_freq == tdvfs_info->old_freq)
    {
#if defined(CHIP_TYPE_hi3798cv200)
         HI_INFO_PM("[%s,%d] set same volt:%d \n",__func__,__LINE__,tdvfs_info->volt);
         cpu_volt_scale(tdvfs_info->volt);
#endif
        return 0;
    }
    else if (tdvfs_info->new_freq > tdvfs_info->old_freq)
    {
        CPU_AVS_Enable(HI_FALSE);
        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }

        cpu_volt_scale(tdvfs_info->volt);

        up(&g_CPUAVSMutex);

        msleep(10);
        ret = hi_clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("scale freq to %ld falt\n", tdvfs_info->new_freq);
            return ret;
        }
    }
    else
    {
        CPU_AVS_Enable(HI_FALSE);

        ret = hi_clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("scale freq to %ld falt\n", tdvfs_info->new_freq);
            return ret;
        }

        msleep(10);

        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }

        cpu_volt_scale(tdvfs_info->volt);

        up(&g_CPUAVSMutex);
    }

#if defined(CHIP_TYPE_hi3798cv200)
    if (tdvfs_info->new_freq > 600000)
#elif defined(CHIP_TYPE_hi3798mv200)
    if (tdvfs_info->new_freq > 800000)
#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    if ((tdvfs_info->new_freq > 800000) && (tdvfs_info->new_freq < 1450000))
#else
    if ((tdvfs_info->new_freq > 400000) && (tdvfs_info->new_freq < 1500000))
#endif
    {
        /* wait for hpm test */
        msleep(8);
        CPU_AVS_Enable(HI_TRUE);
    }

    return ret;
}

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
unsigned int cpu_get_svb_volt(unsigned freq)
{
    unsigned int i;
    HI_CHIP_PACKAGE_TYPE_E packageType = HI_CHIP_PACKAGE_TYPE_BUTT;
    int ret = 0;

    ret = HI_DRV_SYS_GetChipPackageType(&packageType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PM("get chip package type failed\n");
        packageType = HI_CHIP_PACKAGE_TYPE_BGA_21_21;/* when got chip package type failed, choose default type 21*21 */
    }

    for (i = 0; i < CPU_FREQ_SVB_CNT; i++)
    {
        if (HI_CHIP_PACKAGE_TYPE_BGA_21_21 == packageType)
        {
            if (freq == cpu_volt_svb_default[i][0])
            {
                return cpu_volt_svb_default[i][g_corner_type];
            }
        }
        else
        {
            if (freq == cpu_volt_svb_package1[i][0])
            {
                return cpu_volt_svb_package1[i][g_corner_type];
            }
        }
    }

    return 0;
}
#endif

/**
 * hi_device_scale() - Set a new rate at which the devices is to operate
 * @rate:   the rnew rate for the device.
 *
 * This API gets the device opp table associated with this device and
 * tries putting the device to the requested rate and the voltage domain
 * associated with the device to the voltage corresponding to the
 * requested rate. Since multiple devices can be assocciated with a
 * voltage domain this API finds out the possible voltage the
 * voltage domain can enter and then decides on the final device
 * rate.
 *
 * Return 0 on success else the error value
 */
extern HI_U32 g_bEneterLowTemp;
int hi_device_scale(struct device *target_dev, unsigned int old_freq, unsigned int new_freq)
{
    struct opp *opp;
    unsigned long volt, freq = new_freq;
    struct hi_dvfs_info dvfs_info;

#if defined(CHIP_TYPE_hi3798cv200)
    HI_S16 s16Temp;
#endif

    int ret = 0;

    HI_INFO_PM("hi_device_scale,oldfreq = %d,newfreq = %ld\n", old_freq, new_freq);

    /* Lock me to ensure cross domain scaling is secure */
    mutex_lock(&hi_dvfs_lock);
    rcu_read_lock();

    opp = opp_find_freq_ceil(target_dev, &freq);

    /* If we dont find a max, try a floor at least */
    if (IS_ERR(opp))
    {
        opp = opp_find_freq_floor(target_dev, &freq);
    }

    if (IS_ERR(opp))
    {
        rcu_read_unlock();
        HI_ERR_PM("Unable to find OPP for freq %ld\n", freq);
        ret = -ENODEV;
        goto out;
    }

    volt = opp_get_voltage(opp);

    rcu_read_unlock();

    dvfs_info.old_freq = old_freq;

    dvfs_info.new_freq = (unsigned int)freq;

    dvfs_info.volt = (unsigned int)volt;


    /* in low temp. add cpu volt */
#if defined(CHIP_TYPE_hi3798cv200)
    if (freq <= 800000)
    {
        mpu_get_temp(&s16Temp);
        if (s16Temp <= TEMP_LOW)
        {
            dvfs_info.volt += 50;
            g_bEneterLowTemp = HI_TRUE;
        }
        else
        {
            g_bEneterLowTemp = HI_FALSE;
        }
    }
#endif

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    volt = cpu_get_svb_volt(freq);
    if (volt)
    {
        dvfs_info.volt = volt;
    }
#endif

    /* Do the actual scaling */
    ret = _dvfs_scale( target_dev, &dvfs_info);
    if (ret)
    {
        HI_ERR_PM("scale failed %d[f=%ld, v=%ld]\n", ret, freq, volt);
    }

    /* Fall through */
out:
    mutex_unlock(&hi_dvfs_lock);
    return ret;
}
