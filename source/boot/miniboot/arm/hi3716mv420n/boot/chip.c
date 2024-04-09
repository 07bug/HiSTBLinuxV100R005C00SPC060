/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <config.h>
#include <stdio.h>

#define readl(_a)        (*(volatile unsigned int *)(_a))
#define writel(_v, _a)   (*(volatile unsigned int *)(_a) = (_v))

extern char _sys_srst_startup[];
extern char _sys_srst_end[];
void sys_srst(void);
#include "early_timer.c"
/******************************************************************************/

static inline void delay(unsigned int cnt)
{
	while (cnt--)
		__asm__ __volatile__("nop");
}

/******************************************************************************/
#if defined(CONFIG_AVS_SUPPORT) && !defined(CONFIG_PMU_DEVICE)
void set_core_voltage(void)
{
	unsigned int regval, hpm_code, hpm_code_average, cpu_volt_reg_val, core_volt_reg_val, corner_type;
	unsigned int max_threshold =readl(REG_BASE_SCTL+REG_SC_GEN6) >>16;
	unsigned int min_threshold = readl(REG_BASE_SCTL+REG_SC_GEN6) & 0xffff;
	unsigned int max_core_volt = (readl(REG_BASE_SCTL+REG_SC_GEN17) >> 16) & 0xff;
	unsigned int mid_core_volt = (readl(REG_BASE_SCTL+REG_SC_GEN17) >> 8) & 0xff;
	unsigned int min_core_volt = readl(REG_BASE_SCTL+REG_SC_GEN17) & 0xff;
	unsigned int max_cpu_volt = (readl(REG_BASE_SCTL+REG_SC_GEN18) >> 16) & 0xff;
	unsigned int mid_cpu_volt = (readl(REG_BASE_SCTL+REG_SC_GEN18) >> 8) & 0xff;
	unsigned int min_cpu_volt = readl(REG_BASE_SCTL+REG_SC_GEN18) & 0xff;
	//unsigned int chipid = readl(REG_BASE_SCTL + REG_SC_SYSID0);

	/* hpm 0             */
	/* clock is 200M, set time division to (200/50 - 1) */
	regval = readl(0xf8a23058);
	regval &= 0xffffffc0;
	regval |= 3;
	writel(regval, 0xf8a23058);

	regval = readl(0xf8a23064);
	regval &= 0x00ffffff;
	regval |= (1 << 24);
	writel(regval, 0xf8a23064);

	/* hpm enable */
	regval = readl(0xf8a23058);
	regval |= (1 << 24);
	writel(regval, 0xf8a23058);

	/* hpm monitor enable */
	regval = readl(0xf8a23058);
	regval |= (1 << 26);
	writel(regval, 0xf8a23058);

	delay(6000000);

	regval = readl(0xf8a2305c);
	hpm_code = (regval & 0x3ff);
	hpm_code_average = hpm_code;
	hpm_code = ((regval >> 12) & 0x3ff);
	hpm_code_average += hpm_code;

	regval = readl(0xf8a23060);
	hpm_code = (regval & 0x3ff);
	hpm_code_average += hpm_code;
	hpm_code = ((regval >> 12) & 0x3ff);
	hpm_code_average += hpm_code;

	hpm_code_average = (hpm_code_average>>2);

	core_volt_reg_val = readl(0xf8a23018);
	cpu_volt_reg_val = readl(0xf8a2301c);
	core_volt_reg_val &= 0xffff;
	cpu_volt_reg_val &= 0xffff;
	if (hpm_code_average >= max_threshold) {
		core_volt_reg_val |= max_core_volt<<16; /* ff chip */
		cpu_volt_reg_val |= max_cpu_volt<<16; /* ff chip */
		corner_type = 1;
	} else if (hpm_code_average < min_threshold) {
		core_volt_reg_val |= min_core_volt<<16; /* ss chip */
		cpu_volt_reg_val |= min_cpu_volt<<16; /* ss chip */
		corner_type = 3;
	} else {
		core_volt_reg_val |= mid_core_volt<<16; /* tt chip */
		cpu_volt_reg_val |= mid_cpu_volt<<16; /* tt chip */
		corner_type = 2;
	}
	writel(core_volt_reg_val, 0xf8a23018);
	writel(cpu_volt_reg_val, 0xf8a2301c);

	regval = readl(REG_BASE_SCTL+REG_SC_GEN17);
	regval &= 0xffffff;
	regval |= (corner_type << 24);
	writel(regval, REG_BASE_SCTL+REG_SC_GEN17);

	delay(8000000);

	return;
}
#endif
/******************************************************************************/

long long get_chipid_reg(void)
{
	long long chipid = 0;
	long long val = 0;

	chipid = (long long)readl(REG_BASE_SCTL + REG_SC_SYSID0);
	val = (long long)readl(REG_BASE_PERI_CTRL + REG_PERI_SOC_FUSE);
	chipid = ((val & (0x1F << 16)) << 16) | (chipid & 0xFFFFFFFF);

	return chipid;
}

/******************************************************************************/

unsigned int get_ca_vendor_reg(void)
{
	unsigned long ca_vendor = 0;

	// TODO: XXXX

	return ca_vendor;
}

/******************************************************************************/
void reset_by_wdg(void)
{
	unsigned int val;

	early_puts("*** CPU will be reset by WDG0 now............\r\n\r\n");

	/* enable the wdg0 crg clock */
	val = readl(REG_BASE_CRG + REG_PERI_CRG94);
	val &= ~(1<<4);
	val |= 1;
	writel(val, REG_BASE_CRG + REG_PERI_CRG94);
	delay(1000);

	/* unclock wdg */
	writel(0x1ACCE551, REG_BASE_WDG0 + 0x0C00);
	/* wdg load value */
	writel(0x00000001, REG_BASE_WDG0 + 0x0000);
	/* bit0: int enable bit1: reboot enable */
	writel(0x00000003, REG_BASE_WDG0 + 0x0008);
	while (1);
}

/******************************************************************************/
/*
 * flag: 0 -- soft reset
 *       1 -- reset by watchdog
 */
void reset_cpu(unsigned long flag)
{
#ifdef CONFIG_SYS_SRST_SUPPORT
	if (!flag) {
		sys_srst();
	} else {
		reset_by_wdg();
	}
#else
	reset_by_wdg();
#endif
	while (1);
}

/******************************************************************************/
#ifdef CONFIG_SYS_SRST_SUPPORT
void sys_srst(void)
{
	char *src = _sys_srst_startup;
	char *dst = (char *)(SYS_SRST_SRAM_BASE);
	void (*entry)(void) = (void *)dst;

	if ((_sys_srst_end - _sys_srst_startup) > SYS_SRST_MAX_SIZE) {
		early_puts("ERROR: System soft reset code too large, reset fail\n");
		while(1);
	}

try_again:
	do {
		*dst = *src;
		src++;
		dst++;
	} while(src < _sys_srst_end);

	early_puts("*** CPU will be reset by soft reset now............\r\n\r\n");

	entry();
	goto try_again;
}
#endif


bool is_tee_type(void)
{
	return 1;
}

void check_jtag_flag(void)
{
	if (0xdeadbeef == readl(REG_BASE_SCTL + REG_SC_GEN30))
		early_udelay(5000000);
}
/******************************************************************************/
