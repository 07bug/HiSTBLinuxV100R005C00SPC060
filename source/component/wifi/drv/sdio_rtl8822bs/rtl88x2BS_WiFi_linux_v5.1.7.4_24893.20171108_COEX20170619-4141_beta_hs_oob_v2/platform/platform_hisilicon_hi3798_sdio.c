/******************************************************************************
 *
 * Copyright(c) 2017 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#include <linux/delay.h>		/* mdelay() */
#include <linux/gpio.h>			/* gpio_to_irq() and etc */
#include <mach/hardware.h>		/* __io_address(), readl(), writel() */
#include "platform_hisilicon_hi3798_sdio.h"	/* HI_S32() and etc. */

typedef enum hi_GPIO_DIR_E {
	HI_DIR_OUT = 0,
	HI_DIR_IN  = 1,
} HI_GPIO_DIR_E;

#define RTL_REG_ON_GPIO		(4*8 + 3)	/* modify by hcm (7*8 + 3) */

//#define RTL_OOB_INT_GPIO	40		/* WL_HOST_WAKE gpio */
#ifndef RTL_OOB_INT_GPIO
#ifdef CONFIG_RTW_SDIO_OOB_INT
#error "RTL_OOB_INT_GPIO not defined"
#endif /* CONFIG_RTW_SDIO_OOB_INT */
#endif

#define REG_BASE_CTRL		__io_address(0xf8a20008)

int gpio_wlan_reg_on = RTL_REG_ON_GPIO;
#if 0
module_param(gpio_wlan_reg_on, uint, 0644);
MODULE_PARM_DESC(gpio_wlan_reg_on, "wlan reg_on gpio num (default:gpio7_3)");
#endif

int oob_int_irq = 0;

static void himm(u32 addr, u32 val)
{
	u32 regval;


	regval = readl(__io_address(addr));
	if (regval != val) {
		writel(val, __io_address(addr));
		pr_info("0x%08x: 0x%08x --> 0x%08x\n", addr, regval, val);

		regval = readl(__io_address(addr));
	}

	pr_info("0x%08x = 0x%08x\n", addr, regval);
}

static int hi_gpio_set_value(u32 gpio, u32 value)
{
	HI_S32 s32Status;

	s32Status = HI_DRV_GPIO_SetDirBit(gpio, HI_DIR_OUT);
	if (s32Status != HI_SUCCESS) {
		pr_err("gpio(%d) HI_DRV_GPIO_SetDirBit HI_DIR_OUT failed\n",
			gpio);
		return -1;
	}

	s32Status = HI_DRV_GPIO_WriteBit(gpio, value);
	if (s32Status != HI_SUCCESS) {
		pr_err("gpio(%d) HI_DRV_GPIO_WriteBit value(%d) failed\n",
			gpio, value);
		return -1;
	}

	return 0;
}

static int hisi_wlan_set_oob(bool present, unsigned gpio)
{
	if (!present)
		return 0;

	/* GPIO3_6, gpio=30 */
	/* himm 0xf8a21078 0x130 */
	if (gpio == 30)
		himm(0xf8a21078, 0x130);

	return 0;
}

static int hisi_wlan_get_oob_irq(unsigned gpio)
{
	int host_oob_irq = 0;
	int err = 0;


	err = gpio_request(gpio, "oob irq");
	if (err) {
		pr_err("%s: gpio-%d gpio_request failed(%d)\n",
		       __FUNCTION__, gpio, err);
		return 0;
	}

	err = gpio_direction_input(gpio);
	if (err) {
		pr_err("%s: gpio-%d gpio_direction_input failed(%d)\n",
		       __FUNCTION__, gpio, err);
		gpio_free(gpio);
		return 0;
	}

	host_oob_irq = gpio_to_irq(gpio);
	pr_info("%s: GPIO(%u) IRQ(%d)\n",
		__FUNCTION__, gpio, host_oob_irq);

	return host_oob_irq;
}

static void hisi_wlan_free_oob_gpio(unsigned gpio)
{
	pr_info("%s: gpio_free(%u)\n", __FUNCTION__, gpio);
	gpio_free(gpio);
}

static void hisi_wlan_set_sdio_driving(void)
{
	/*
	 * Set Host SD_CLK Driving to 15mA
	 * himm 0xf8a21098 0x131
	 */
//	himm(0xf8a21098, 0x131);

	/*
	 * Set Host SD_CMD Driving to 16mA
	 * himm 0xf8a2109c 0x111
	 */
//	himm(0xf8a2109c, 0x111);

	/*
	 * Set Host SD_DATA Driving to 16mA
	 * D3: himm 0xf8a210A0 0x111
	 * D2: himm 0xf8a210A4 0x111
	 * D1: himm 0xf8a21090 0x111
	 * D0: himm 0xf8a21094 0x111
	 */
//	himm(0xf8a210A0, 0x111);
//	himm(0xf8a210A4, 0x111);
//	himm(0xf8a21090, 0x111);
//	himm(0xf8a21094, 0x111);
}

static int hisi_wlan_set_carddetect(bool present)
{
	u32 regval;

	if (present) {
		pr_info("======== Card detection to detect SDIO card! ========\n");
		/* set card_detect low to detect card */
		regval = readl(REG_BASE_CTRL);
		regval |= 0x1;
		writel(regval, REG_BASE_CTRL);
	} else {
		pr_info("======== Card detection to remove SDIO card! ========\n");
		/* set card_detect high to remove card */
		regval = readl(REG_BASE_CTRL);
		regval &= ~(0x1);
		writel(regval, REG_BASE_CTRL);
	}

	return 0;
}

/*
 * Return:
 *	0:	power on successfully
 *	others: power on failed
 */
int platform_wifi_power_on(void)
{
	int ret = 0;


#ifdef CONFIG_RTW_SDIO_OOB_INT
	hisi_wlan_set_oob(1, RTL_OOB_INT_GPIO);
	oob_int_irq = hisi_wlan_get_oob_irq(RTL_OOB_INT_GPIO);
#endif
        return ret;
	hi_gpio_set_value(gpio_wlan_reg_on, 1);
	mdelay(100);
#ifdef CONFIG_HISI_RISE_SDIO_DRIVING
	hisi_wlan_set_sdio_driving();
#endif
	hisi_wlan_set_carddetect(1);
	mdelay(2000);
	pr_info("======== set_carddetect delay 2s! ========\n");

	return ret;
}

void platform_wifi_power_off(void)
{
#ifdef CONFIG_RTW_SDIO_OOB_INT
	hisi_wlan_free_oob_gpio(RTL_OOB_INT_GPIO);
	oob_int_irq = 0;
//	hisi_wlan_set_oob(0, RTL_OOB_INT_GPIO);
#endif
        return;
	hisi_wlan_set_carddetect(0);
	mdelay(100);
	hi_gpio_set_value(gpio_wlan_reg_on, 0);
}

int platform_wifi_get_oob_irq(void)
{
	int irq = 0;


	irq = oob_int_irq;

	return irq;
}

