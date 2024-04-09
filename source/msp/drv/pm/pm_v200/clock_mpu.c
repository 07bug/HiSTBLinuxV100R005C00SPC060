/*
 * hisilicon mpu clock management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/clk.h>

#include <linux/clkdev.h>
#include <asm/clkdev.h>

#include <linux/device.h>
#include "clock.h"
#include "hi_reg_common.h"
#include "hi_drv_reg.h"
#include "hi_drv_pmoc.h"
#include "hi_dvfs.h"
#include "hi_drv_sys.h"

struct device mpu_dev;

static DEFINE_SPINLOCK(mpu_clock_lock);

#if defined(HI_DONGLE_MODE_CRITICAL)
#define MAX_FREQ 800000
#elif defined(HI_DONGLE_MODE_LOW)
#define MAX_FREQ 1000000
#else
#define MAX_FREQ 1600000
#endif // end of defined(HI_DONGLE_MODE_CRITICAL)

#define MIN_FREQ 400000

#define CLOCK_24M (24 * 1000) //KHz

#define MAX_CLOCK_SW_COUNT (10000)

extern HI_U32 g_corner_type;

struct clk mpu_ck = {
    .name   = "mpu_ck",
    .parent = NULL,
};

static unsigned int g_postdiv1;
static unsigned int g_postdiv2;
static unsigned int g_refdiv;
extern HI_U32 g_bEneterLowTemp;
static int mpu_clk_set_rate(struct clk *clk, unsigned int rate)
{
    unsigned int fbdiv;
    unsigned long flag;
    unsigned int i;

    U_PERI_CRG_PLL0 unTmpValuePLL0;
    U_PERI_CRG_PLL1 unTmpValuePLL1;

    /* use apll */
    U_PERI_CRG105 unTmpValueCRG105;
    U_PERI_CRG106 unTmpValueCRG106;
    U_PERI_CRG107 unTmpValueCRG107;
    U_PERI_CRG108 unTmpValueCRG108;
    U_PERI_CRG109 unTmpValueCRG109;

    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (rate == cpu_freq_hpm_table[i].freq)
        {
            break;
        }
    }

    if (i == MAX_FREQ_NUM)
    {
        HI_ERR_PM("mpu_clk_set_rate %dk not support\n", rate);
        return -1;
    }

    unTmpValuePLL0.u32 = g_pstRegCrg->PERI_CRG_PLL0.u32;
    g_postdiv1 = (unTmpValuePLL0.bits.cpu_pll_cfg0_apb >> 24) & 0x7; //bit[26:24]
    g_postdiv2 = (unTmpValuePLL0.bits.cpu_pll_cfg0_apb >> 28) & 0x7; //bit[30:28]

    unTmpValuePLL1.u32 = g_pstRegCrg->PERI_CRG_PLL1.u32;
    g_refdiv = (unTmpValuePLL1.bits.cpu_pll_cfg1_apb >> 12) & 0x3f; //bit[17:12]

    /* do not set frac */
    fbdiv = (rate * g_postdiv1 * g_postdiv2 * g_refdiv) / CLOCK_24M;

    /* set fbdiv of target apll */
    unTmpValueCRG105.u32 = g_pstRegCrg->PERI_CRG105.u32;
    unTmpValueCRG105.bits.apll_tune_int_cfg = fbdiv;
    g_pstRegCrg->PERI_CRG105.u32 = unTmpValueCRG105.u32;

    /* set frac of target apll to 0 */
    unTmpValueCRG106.u32 = g_pstRegCrg->PERI_CRG106.u32;
    unTmpValueCRG106.bits.apll_tune_frac_cfg = 0;
    g_pstRegCrg->PERI_CRG106.u32 = unTmpValueCRG106.u32;

    /* set integer of tune step */
    unTmpValueCRG107.u32 = g_pstRegCrg->PERI_CRG107.u32;
    unTmpValueCRG107.bits.apll_tune_step_int = 1;
    g_pstRegCrg->PERI_CRG107.u32 = unTmpValueCRG107.u32;

    /* set fraction of tune setp */
    unTmpValueCRG108.u32 = g_pstRegCrg->PERI_CRG108.u32;
    unTmpValueCRG108.bits.apll_tune_step_frac = 0;
    g_pstRegCrg->PERI_CRG108.u32 = unTmpValueCRG108.u32;

    /* enter ssmod */
    unTmpValueCRG109.u32 = g_pstRegCrg->PERI_CRG109.u32;
    unTmpValueCRG109.bits.apll_tune_mode = 0x1;
    g_pstRegCrg->PERI_CRG109.u32 = unTmpValueCRG109.u32;

    /* begin one tune process */
    unTmpValueCRG109.u32 = g_pstRegCrg->PERI_CRG109.u32;
    unTmpValueCRG109.bits.apll_tune_en = 0x0;
    g_pstRegCrg->PERI_CRG109.u32 = unTmpValueCRG109.u32;

    unTmpValueCRG109.u32 = g_pstRegCrg->PERI_CRG109.u32;
    unTmpValueCRG109.bits.apll_tune_en = 0x1;
    g_pstRegCrg->PERI_CRG109.u32 = unTmpValueCRG109.u32;

    /* check whether pll switch is over */
    i = 0;
    while (i++ < MAX_CLOCK_SW_COUNT)
    {
        if (0x0 == g_pstRegCrg->PERI_CRG165.bits.apll_tune_busy)
        {
            break;
        }

        udelay(10);
    }

    spin_lock_irqsave(&mpu_ck.spinlock, flag);
    clk->rate = rate;
    g_pstRegSysCtrl->SC_GENx[2] = rate;
    spin_unlock_irqrestore(&mpu_ck.spinlock, flag);

    return 0;
}

static unsigned int find_clk_in_table(unsigned int rate)
{
    unsigned int i, clk_in_table;

    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (rate >= cpu_freq_hpm_table[i].freq)
        {
            if ((rate - cpu_freq_hpm_table[i].freq) < 10000) // 10M
            {
                break;
            }
        }
        else
        {
            if ((cpu_freq_hpm_table[i].freq - rate) < 10000)
            {
                break;
            }
        }
    }

    if (i >= MAX_FREQ_NUM)
    {
        HI_ERR_PM("cannot find clk=%d in freq table, return default \n", rate);
        return DEFAULT_INIT_FREQ;
    }

    clk_in_table = cpu_freq_hpm_table[i].freq;

    return clk_in_table;
}

static unsigned int mpu_clk_get_rate(void)
{
    unsigned int rate, fbdiv, reg_clk;

    reg_clk = g_pstRegCrg->PERI_CRG18.bits.cpu_freq_sel_cfg_crg;

    switch (reg_clk)
    {
    case 0:
    {
        g_postdiv1 = (g_pstRegCrg->PERI_CRG_PLL0.bits.cpu_pll_cfg0_apb >> 24) & 0x7;     //bit[26:24]
        g_postdiv2 = (g_pstRegCrg->PERI_CRG_PLL0.bits.cpu_pll_cfg0_apb >> 28) & 0x7;     //bit[30:28]
        g_refdiv = (g_pstRegCrg->PERI_CRG_PLL1.bits.cpu_pll_cfg1_apb >> 12) & 0x3f;     //bit[17:12]

        if (g_pstRegCrg->PERI_CRG165.bits.apll_tune_int)
        {
            fbdiv = g_pstRegCrg->PERI_CRG165.bits.apll_tune_int;
        }
        else
        {
            fbdiv = g_pstRegCrg->PERI_CRG_PLL1.bits.cpu_pll_cfg1_apb & 0xfff;
        }

        rate = (fbdiv * CLOCK_24M) / (g_postdiv1 * g_postdiv2 * g_refdiv);
        rate = find_clk_in_table(rate);
        break;
    }
    case 1:
        rate = 200000;
        break;
    case 2:
        rate = 800000;
        break;
    case 3:
        rate = 1350000;
        break;
    case 4:
        rate = 24000;
        break;
    case 5:
        rate = 1200000;
        break;
    case 6:
        rate = 400000;
        break;
    case 7:
        rate = 600000;
        break;
    default:
        HI_ERR_PM("mpu_clk_get_rate %dk not support\n", reg_clk);
        return 0;
    }

    return rate;
}

static void mpu_clk_init(struct clk *clk)
{
    U_PERI_CRG18 unTmpValue;

    /* set cpu switch by software register */
    unTmpValue.u32 = g_pstRegCrg->PERI_CRG18.u32;
    unTmpValue.bits.cpu_begin_cfg_bypass = 0x1;
    g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

    return;
}

static struct clk_ops mpu_clock_ops = {
    .set_rate = mpu_clk_set_rate,
    .init     = mpu_clk_init,
};

void  mpu_init_clocks(void)
{
    HI_INFO_PM("Enter %s\n", __FUNCTION__);
    mpu_ck.rate = mpu_clk_get_rate();
    if (0 == mpu_ck.rate)
    {
        mpu_ck.rate = DEFAULT_INIT_FREQ;
    }

    mpu_ck.ops = &mpu_clock_ops;
    mpu_ck.max_rate = MAX_FREQ;
    mpu_ck.min_rate = MIN_FREQ;

    mpu_ck.spinlock = mpu_clock_lock;
    hi_clk_init(&mpu_ck);

    mpu_clk_set_rate(&mpu_ck, mpu_ck.rate);

    return;
}

void  mpu_resume_clocks(void)
{
    mpu_ck.rate = mpu_clk_get_rate();
    if (0 == mpu_ck.rate)
    {
        mpu_ck.rate = DEFAULT_INIT_FREQ;
    }

    mpu_clk_set_rate(&mpu_ck, mpu_ck.rate);

    return;
}

void  mpu_exit_clocks(void)
{
    hi_clk_exit(&mpu_ck);
}
