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

#define PWM_CPU PERI_PMC6
#define PWM_CORE PERI_PMC8

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 10 /*ms*/

extern HI_U32 g_bEneterLowTemp;
unsigned int cur_cpu_volt  = 1300;
unsigned int cur_core_volt = 1150;
unsigned int init_core_volt = 1150;
unsigned int cur_cpu_hpm;
unsigned int cur_cpu_vmin;
unsigned int cur_cpu_vmax;

HI_U32 g_corner_type = 0;
HI_U8 g_u8CpuHpmOffset = 0;
static HI_U8 g_TmpHpmOffset = 0;
static HI_U32 g_corner_hpm = 0;
static HI_U32 cpu_avs_enable = HI_FALSE;
static HI_U8 g_u8CpuOtpAddHPM = 0;

#if defined(CHIP_TYPE_hi3798mv310)
static unsigned char g_OTP_add_volt_800M = 0;
static unsigned char g_OTP_add_volt_1200M = 0;
static unsigned int g_k_800M;
static unsigned int g_b_800M;
static unsigned int g_max_volt_800M;
static unsigned int g_k_1200M;
static unsigned int g_b_1200M;
static unsigned int g_max_volt_1200M;
#endif

int core_volt_scale(unsigned int volt);

extern int hisi_regulator_set_voltage(int type, int volt);
extern HI_U8 HAL_OTP_V200_ReadByte(HI_U32 addr);

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

CPU_VF_S cpu_freq_hpm_table[MAX_FREQ_NUM] =
{
    { 400000, HI_VDD_MPU_OPP1_HPM, HI_VDD_MPU_OPP1_VMIN, HI_VDD_MPU_OPP1_UV},
    { 600000, HI_VDD_MPU_OPP2_HPM, HI_VDD_MPU_OPP2_VMIN, HI_VDD_MPU_OPP2_UV},
    { 800000, HI_VDD_MPU_OPP3_HPM, HI_VDD_MPU_OPP3_VMIN, HI_VDD_MPU_OPP3_UV},
    {1200000, HI_VDD_MPU_OPP5_HPM, HI_VDD_MPU_OPP5_VMIN, HI_VDD_MPU_OPP5_UV},
    {1600000, HI_VDD_MPU_OPP7_HPM, HI_VDD_MPU_OPP7_VMIN, HI_VDD_MPU_OPP7_UV},
};

#define HI_CPU_OTP_ADJUST_ENABLE (0x440)
#define HI_CPU_400M_OTP (0x441)
#define HI_CPU_600M_OTP (0x442)
#define HI_CPU_800M_OTP (0x443)
#define HI_CPU_1000M_OTP (0x444)
#define HI_CPU_1200M_OTP (0x445)
#define HI_CPU_1300M_OTP (0x446)
#define HI_CPU_1400M_OTP (0x447)
#define HI_CPU_1500M_OTP (0x448)
#define HI_CPU_1600M_OTP (0x449)
#define HI_CPU_1700M_OTP (0x44a)
#define HI_CPU_1800M_OTP (0x44b)

#define HI_CPU_1200M_DMS_OTP (0x44c)
#define HI_CPU_1000M_DMS_OTP (0x44d)
#define HI_CPU_800M_DMS_OTP (0x44e)

#if defined(CHIP_TYPE_hi3798mv300)

#define CPU_FREQ_SVB_CNT 5

typedef struct hiCPU_OTP_S
{
    unsigned int freq;          /* unit: kHz */
    unsigned int otp_addr;   /* the otp address of added value */
} CPU_OTP_S;

static unsigned int cpu_volt_svb_default[CPU_FREQ_SVB_CNT][4] = {
    {1600000, 1100, 1160, 1250},
    {1200000, 960, 1030, 1090},
    {800000, 850, 900, 950},
    {600000, 850, 900, 950},
    {400000, 850, 900, 950}
};

CPU_OTP_S cpu_otp_table[MAX_FREQ_NUM] =
{
    {400000, HI_CPU_400M_OTP},
    {600000, HI_CPU_600M_OTP},
    {800000, HI_CPU_800M_OTP},
    {1200000, HI_CPU_1200M_OTP},
    {1600000, HI_CPU_1600M_OTP},
};

CPU_OTP_S cpu_otp_table_dms[MAX_FREQ_NUM] =
{
    {400000, HI_CPU_800M_DMS_OTP},
    {600000, HI_CPU_800M_DMS_OTP},
    {800000, HI_CPU_800M_DMS_OTP},
    {1000000, HI_CPU_1000M_DMS_OTP},
    {1200000, HI_CPU_1200M_DMS_OTP},
};

/* read added volt from otp of one given freq*/
static unsigned int cpu_volt_otp_adjust(unsigned int freq)
{
    unsigned int i, regval, otp_addr, otp_volt;

    /* read enable flag to see whether to do adjust */
    regval = HAL_OTP_V200_ReadByte(HI_CPU_OTP_ADJUST_ENABLE);
    if (0 == (regval & 0x80))
    {
        return 0;
    }

    /* clear the added hpm */
    g_u8CpuOtpAddHPM = 0;

    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (freq == cpu_otp_table[i].freq)
        {
            otp_addr = cpu_otp_table[i].otp_addr;
            break;
        }
    }

    if (MAX_FREQ_NUM == i)
    {
        HI_ERR_PM("Not find this cpu frequency .\n");
        return 0;
    }

    /* read enable flag from one freq */
    regval = HAL_OTP_V200_ReadByte(otp_addr);
    if (0 == (regval & 0x80))
    {
        return 0;
    }

    /* determine add pwm volt or hpm value */
    if (0 == (regval & 0x40))
    {
        otp_volt = (regval & 0xf) * 10;
        HI_INFO_PM("otp_volt = 0x%x .\n", otp_volt);
    }
    else
    {
        g_u8CpuOtpAddHPM = (regval & 0xf) * 5;
        HI_INFO_PM("g_u8CpuOtpAddHPM = 0x%x .\n", g_u8CpuOtpAddHPM);
        otp_volt = 0;
    }

    return otp_volt;
}

static unsigned int cpu_volt_otp_adjust_dms(unsigned int freq)
{
    unsigned int i, regval, otp_addr, otp_volt;

    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (freq == cpu_otp_table_dms[i].freq)
        {
            otp_addr = cpu_otp_table_dms[i].otp_addr;
            break;
        }
    }

    if (MAX_FREQ_NUM == i)
    {
        HI_ERR_PM("Not find this cpu frequency .\n");
        return 0;
    }

    /* read enable flag from one freq */
    regval = HAL_OTP_V200_ReadByte(otp_addr);
    if (0 == (regval & 0x80))
    {
        return 0;
    }

    otp_volt = (regval & 0xf) * 10;
    HI_INFO_PM("otp_volt = 0x%x .\n", otp_volt);

    return otp_volt;
}

unsigned int cpu_get_svb_volt(unsigned int freq)
{
    unsigned int i;
    unsigned int volt;

    if (1200000 == freq)
    {
        volt = (1590564 - (1435 * g_corner_hpm)) * 9 /10000;
        if (volt > 1090)
        {
            volt = 1090;
        }

        HI_INFO_PM(" set volt = %d \n", volt);
        return volt;
    }
    else
    {
        for (i = 0; i < CPU_FREQ_SVB_CNT; i++)
        {
            if (freq == cpu_volt_svb_default[i][0])
            {
                return cpu_volt_svb_default[i][g_corner_type];
            }
        }
    }

    HI_ERR_PM(" can't find freq %d in dms table\n", freq);

    return cpu_volt_svb_default[1][g_corner_type];
}

unsigned int cpu_get_volt_from_chip(unsigned int freq, unsigned int dvfs_volt)
{
    unsigned int volt_otp_added = 0;
    unsigned int volt;

    if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //dms board
    {
        volt = cpu_get_svb_volt(freq);

        /* add dms otp adjust */
        volt_otp_added = cpu_volt_otp_adjust_dms(freq);
        volt += volt_otp_added;

        /* dms low tmp compensation */
        if ((freq <= 800000) && (HI_TRUE == g_bEneterLowTemp))
        {
            volt += 30;
        }

        return volt;
    }
    else
    {
        if ((freq <= 800000) && (HI_TRUE == g_bEneterLowTemp))
        {
            dvfs_volt = 930;
            g_TmpHpmOffset = 0x0f;
        }
        else
        {
            g_TmpHpmOffset = 0x0;
        }

        volt_otp_added = cpu_volt_otp_adjust(freq);
        dvfs_volt += volt_otp_added;
    }

    return dvfs_volt;
}
#endif

#if defined(CHIP_TYPE_hi3798mv310)
static void cpu_volt_get_otp_adjust(void)
{
    unsigned int regval = 0;

    /* read enable flag from one freq */
    regval = HAL_OTP_V200_ReadByte(HI_CPU_1000M_DMS_OTP);
    if (0 != (regval & 0x80))
    {
        g_pstRegSysCtrl->SC_GENy[7] |= (regval & 0xf) * 10;
    }

    regval = HAL_OTP_V200_ReadByte(HI_CPU_800M_DMS_OTP);
    if (0 != (regval & 0x80))
    {
        g_OTP_add_volt_800M = (regval & 0xf) * 10;
    }

    regval = HAL_OTP_V200_ReadByte(HI_CPU_1200M_DMS_OTP);
    if (0 != (regval & 0x80))
    {
        g_OTP_add_volt_1200M = (regval & 0xf) * 10;
    }

    g_k_800M = (g_pstRegSysCtrl->SC_GENy[3] >> 16) & 0xffff;
    g_b_800M = g_pstRegSysCtrl->SC_GENy[3] & 0xffff;
    g_max_volt_800M = (g_pstRegSysCtrl->SC_GENm[17] >> 16) & 0xffff;
    g_k_1200M = (g_pstRegSysCtrl->SC_GENm[18] >> 16) & 0xffff;
    g_b_1200M = g_pstRegSysCtrl->SC_GENm[18] & 0xffff;
    g_max_volt_1200M = (g_pstRegSysCtrl->SC_GENm[6] >> 16) & 0xffff;

    return;
}
#endif

static int cpu_init_hpm(unsigned int rate, unsigned int offset)
{
    unsigned int regval, div;

    unsigned int i;

    div = (rate / 50000) - 1;

    if (div > 31)
    {
        HI_ERR_PM("\n Rate value is out of range \n");
        return -1;
    }

    /* hpm 2             */
    /* set time division */
    HI_REG_READ32(PERI_PMC30, regval);
    regval &= 0xffffffc0;
    regval |= div;
    HI_REG_WRITE32(PERI_PMC30, regval);

    /* set monitor period to 2ms */
    HI_REG_READ32(PERI_PMC33, regval);
    regval &= 0x00ffffff;
    regval |= (1 << 24);
    HI_REG_WRITE32(PERI_PMC33, regval);

    /* hpm enable */
    HI_REG_READ32(PERI_PMC30, regval);
    regval |= (1 << 24);
    HI_REG_WRITE32(PERI_PMC30, regval);

    /* hpm monitor enable */
    HI_REG_READ32(PERI_PMC30, regval);
    regval |= (1 << 26);
    HI_REG_WRITE32(PERI_PMC30, regval);

    /* init hardware hpm */
    HI_REG_READ32(PERI_PMC218, regval);
    regval &= 0x1;
    regval |= 0x02028000;
    HI_REG_WRITE32(PERI_PMC218, regval);

    /* get default hpm record */
    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (rate == cpu_freq_hpm_table[i].freq)
        {
            cur_cpu_hpm = cpu_freq_hpm_table[i].hpmrecord + g_u8CpuHpmOffset + g_u8CpuOtpAddHPM + offset;

            /* set hardware hpm target */
            HI_REG_READ32(PERI_PMC33, regval);
            regval &= 0xffc00c00;
            regval |= cur_cpu_hpm + 0x6;
            regval |= (cur_cpu_hpm << 12);
            HI_REG_WRITE32(PERI_PMC33, regval);

   #if defined(CHIP_TYPE_hi3798mv300)
            /* set up limit and down limit */
            regval = ((((CPU_VMAX - cpu_freq_hpm_table[i].vmin) * PWM_CLASS) / PWM_STEP) + 1) << 16;

            if ((CPU_VMAX - cpu_freq_hpm_table[i].vsetting) > (g_u8CpuOtpAddHPM / 5))
            {
                regval |= (((CPU_VMAX - cpu_freq_hpm_table[i].vsetting - (g_u8CpuOtpAddHPM / 5)) * PWM_CLASS) / PWM_STEP) + 1;
            }
            HI_REG_WRITE32(PERI_PMC220, regval);
   #endif
            break;
        }
    }

    return 0;
}

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

#if defined(CHIP_TYPE_hi3798mv300)
    if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/dms board
    {
        /* The dms board cpu volt use core pwm*/
        pwm_reg = PERI_PMC7;
    }
#endif

#if defined(CHIP_TYPE_hi3798mv310)
    pwm_reg = PERI_PMC7;
#endif

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
#if defined(CHIP_TYPE_hi3798mv310)
    int real_volt;
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

#if defined(CHIP_TYPE_hi3798mv310)
    real_volt = hisi_regulator_set_voltage(1, volt);
    volt = real_volt;
#else
    device_volt_scale(CPU_DEVICE, volt);
#endif

    cur_cpu_volt = volt;

#if defined(CHIP_TYPE_hi3798mv300)
    if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/  dms board
    {
        cur_core_volt = volt;
    }
#endif

#if defined(CHIP_TYPE_hi3798mv310)
    cur_core_volt = volt;
#endif

    return 0;
}

unsigned int CPU_AVS_GetStatus(void)
{
    return cpu_avs_enable;
}

void CPU_AVS_Enable(unsigned int enable)
{
    HI_U32 u32RegVal;

    if (HI_TRUE == enable)
    {
#if defined(CHIP_TYPE_hi3798mv310)
        /* 98mv310 don't enable avs */
        return;
#endif

#if defined(CHIP_TYPE_hi3798mv300)
        if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/dms board
        {
            /* The dms board does not enable avs*/
            return;
        }
#endif
    }

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

    /* set pwm0 duty limit enable */
    HI_REG_READ32(PERI_PMC223, u32RegVal);
    if (HI_TRUE == enable)
    {
        u32RegVal |= 0x1;
    }
    else
    {
        u32RegVal &= 0xfffffffe;
    }
    HI_REG_WRITE32(PERI_PMC223, u32RegVal);

    cpu_avs_enable = enable;

    HI_INFO_PM("\n CPU_AVS_Enable = %d \n", enable);
}

unsigned int mpu_get_volt(void)
{
    unsigned int v;

    HI_REG_READ32(PWM_CPU, v);

#if defined(CHIP_TYPE_hi3798mv300)
    if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/dms board
    {
        /* The dms board core volt use core pwm*/
        HI_REG_READ32(PERI_PMC7, v);
    }
#endif

#if defined(CHIP_TYPE_hi3798mv310)
    HI_REG_READ32(PERI_PMC7, v);
#endif

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
    g_corner_hpm = (g_pstRegSysCtrl->SC_GENm[6] & 0x3ff);
    g_corner_type = (g_pstRegSysCtrl->SC_GENm[17] >> 24) & 0xff;
    if ((g_corner_type > CHIP_TYPE_SS) || (g_corner_type < CHIP_TYPE_FF))
    {
        g_corner_type = CHIP_TYPE_SS;
    }

#if defined(CHIP_TYPE_hi3798mv310)
    g_pstRegSysCtrl->SC_GENy[7] |= (g_corner_hpm << 16);
    cpu_volt_get_otp_adjust();
#endif

    return;
}

void mpu_deinit_volt(void)
{
    return;
}

int core_volt_scale(unsigned int volt)
{
#if defined(CHIP_TYPE_hi3798mv310)
    HI_INFO_PM("Don't suppurt adjust core volt! \n");
    return 0;
#endif

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

#if defined(CHIP_TYPE_hi3798mv300)
    if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/dms board
    {
        /* The dms board core volt use core pwm*/
        HI_REG_READ32(PERI_PMC7, v);
    }
#endif

#if defined(CHIP_TYPE_hi3798mv310)
    HI_REG_READ32(PERI_PMC7, v);
#endif

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
    int ret, avs_status;

    HI_INFO_PM("%s rate=%ld\n", __FUNCTION__, tdvfs_info->new_freq);

    if (tdvfs_info->new_freq >= 1600000)
    {
        HI_INFO_PM("This freq %d is not support.\n", tdvfs_info->new_freq);
        return 0;
    }

    clk = &mpu_ck;
    avs_status = CPU_AVS_GetStatus();
    CPU_AVS_Enable(HI_FALSE);

    /* In  changing clock, we need to reinitialize hpm */
    cpu_init_hpm(tdvfs_info->new_freq, g_TmpHpmOffset);

    if (tdvfs_info->new_freq == tdvfs_info->old_freq)
    {
         HI_INFO_PM("[%s,%d] set same volt:%d \n",__func__,__LINE__,tdvfs_info->volt);
         cpu_volt_scale(tdvfs_info->volt);
         CPU_AVS_Enable(avs_status);
        return 0;
    }
    else if (tdvfs_info->new_freq > tdvfs_info->old_freq)
    {
        cpu_volt_scale(tdvfs_info->volt);

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
        ret = hi_clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("scale freq to %ld falt\n", tdvfs_info->new_freq);
            return ret;
        }

        msleep(1);
        cpu_volt_scale(tdvfs_info->volt);
        msleep(9);

    }

#if defined(CHIP_TYPE_hi3798mv310)
        /* 98mv310 don't enable avs */
        return 0;
#endif

#if defined(CHIP_TYPE_hi3798mv300)
        if (((g_pstRegSysCtrl->SC_GENm[5] >> 29) & 0x07) == 0x2) //bit[31:29]: 0b010/dms board
        {
            /* The dms board does not enable avs*/
            return 0;
        }
#endif

    if (tdvfs_info->new_freq > 600000)
    {
        /* wait for hpm test */
        msleep(8);
        CPU_AVS_Enable(HI_TRUE);
    }

    return ret;
}

#if defined(CHIP_TYPE_hi3798mv310)
unsigned int cpu_get_volt_from_chip(unsigned int freq, unsigned int dvfs_volt)
{
    unsigned int volt;

    if (freq <= 800000)
    {
        volt = g_b_800M - (g_k_800M * g_corner_hpm) / 1000;
        if (volt > g_max_volt_800M)
        {
            volt = g_max_volt_800M;
        }

        volt += g_OTP_add_volt_800M;

        if (HI_TRUE == g_bEneterLowTemp)
        {
            volt += 50;
        }
    }
    else //freq 1200000
    {
        volt = g_b_1200M - (g_k_1200M * g_corner_hpm) / 1000;
        if (volt > g_max_volt_1200M)
        {
            volt = g_max_volt_1200M;
        }

        volt += g_OTP_add_volt_1200M;
        if (HI_TRUE == g_bEneterLowTemp)
        {
            volt += 30;
        }
    }

    return volt;
}
#endif

void set_temp_ctrl_status(void)
{
    HI_S16 s16Temp;

    mpu_get_temp(&s16Temp);
    if (s16Temp <= TEMP_LOW)
    {
        g_bEneterLowTemp = HI_TRUE;
    }
    else
    {
        g_bEneterLowTemp = HI_FALSE;
    }

    return;
}

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
int hi_device_scale(struct device *target_dev, unsigned int old_freq, unsigned int new_freq)
{
    struct opp *opp;
    unsigned long volt, freq = new_freq;
    struct hi_dvfs_info dvfs_info;

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

    set_temp_ctrl_status();

    /* get volt according to chip condition */
    volt = cpu_get_volt_from_chip(freq, dvfs_info.volt);
    if (volt)
    {
        dvfs_info.volt = volt;
    }

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
