/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
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
#ifdef CONFIG_PLATFORM_HISILICON
#include "mach/io.h"
#include <linux/mmc/host.h>
 //#define __io_address(n) IOMEM(n)
#include "include/hi_drv_gpio.h"
#include "mach/hardware.h"
#include <linux/gpio.h>
#include <linux/delay.h>

typedef enum hi_GPIO_DIR_E
 {
         HI_DIR_OUT = 0,
         HI_DIR_IN  = 1,
 } HI_GPIO_DIR_E;
 
 #define RTL_REG_ON_GPIO     (4*8 + 3) //modify by hcm (7*8 + 3)     
 #define RTL_OOB_INT_GPIO    (3*8 + 5)     //WL_HOST_WAKE gpio

#define REG_BASE_LDO               __io_address(0xf8a2011c)
#define REG_BASE_CTRL              __io_address(0xf8a20008)

 int gpio_wlan_reg_on = RTL_REG_ON_GPIO;
// module_param(gpio_wlan_reg_on, uint, 0644);
// MODULE_PARM_DESC(gpio_wlan_reg_on, "wlan reg_on gpio num (default:gpio7_3))");
 
 int gpio_wlan_wake_host = RTL_OOB_INT_GPIO;
 module_param(gpio_wlan_wake_host, uint, 0644);
 MODULE_PARM_DESC(gpio_wlan_wake_host, "wlan wake host gpio num (default:gpio6_4))");

#ifdef CONFIG_PLATFORM_HISILICON
static HI_S32 hi_gpio_set_value(HI_U32 gpio, HI_U32 value)
{
        HI_S32  s32Status;

        s32Status = HI_DRV_GPIO_SetDirBit(gpio, HI_DIR_OUT);
        if ( s32Status!= HI_SUCCESS )
        {
                printk("BCMDHD:gpio(%d) HI_DRV_GPIO_SetDirBit HI_DIR_OUT failed \n", gpio);
                return s32Status;
        }

        s32Status = HI_DRV_GPIO_WriteBit(gpio, value);
        if ( s32Status!= HI_SUCCESS )
        {
                printk("BCMDHD:gpio(%d) HI_DRV_GPIO_WriteBit value(%d) failed \n", gpio, value);
                return s32Status;
        }

        return HI_SUCCESS;
}

#endif
#if 0
#ifdef CONFIG_PLATFORM_HISILICON
uint hisi_wlan_get_oob_irq(void)
{
	uint host_oob_irq = 0;

        if (gpio_request(RTL_OOB_INT_GPIO, "oob irq") < 0){
		printf("%s: gpio_request failed\n", __FUNCTION__);
	}
      //  host_oob_irq = gpio_to_irq(RTL_OOB_INT_GPIO);        
        //if (gpio_direction_input(RTL_OOB_INT_GPIO) < 0) {
	//	printf("%s: gpio_direction_input failed\n", __FUNCTION__);
//	}
	printf("host_oob_irq: %d\n", host_oob_irq);

	return host_oob_irq;
    
}
#if 0
void hisi_wlan_free_oob_gpio(uint irq_num)
{
	if (irq_num) {
		printf("%s: gpio_free(%d)\n", __FUNCTION__, RTL_OOB_INT_GPIO);
         		gpio_free(RTL_OOB_INT_GPIO);
	}
}
#endif
#endif
#endif
#endif

#ifdef CONFIG_PLATFORM_HISILICON
int hisi_wlan_set_carddetect(bool present)
{
	u32 regval;
           
	if (present) {
		printk("======== Card detection to detect SDIO card! ========\n");
                /*set card_detect low to detect card*/
              	regval = readl(REG_BASE_CTRL);
                regval |= 0x1;
                writel(regval, REG_BASE_CTRL);
        }  
        else {
                printk("======== Card detection to remove SDIO card! ========\n");
                 /*set card_detect high to remove card*/
              	regval = readl(REG_BASE_CTRL);
                regval &= ~(0x1);
                writel(regval, REG_BASE_CTRL);
	}
}
#endif

#ifndef CONFIG_PLATFORM_OPS
/*
 * Return:
 *	0:	power on successfully
 *	others: power on failed
 */
int platform_wifi_power_on(void)
{
	int ret = 0;
        return ret;
#ifdef CONFIG_PLATFORM_HISILICON
  //      hisi_wlan_get_oob_irq();
 //       if (gpio_request(RTL_OOB_INT_GPIO, "oob irq") < 0){
   //             printk("%s: gpio_request failed\n", __FUNCTION__);
     //   }
        hi_gpio_set_value(gpio_wlan_reg_on, 1);
	mdelay(100);
        hisi_wlan_set_carddetect(1);
	mdelay(2000);
	printk("======== set_carddetect delay 2s! ========\n");
#endif
	return ret;
}

void platform_wifi_power_off(void)
{
       return;
#ifdef CONFIG_PLATFORM_HISILICON
    //   hisi_wlan_free_oob_gpio();
       hisi_wlan_set_carddetect(0);
       mdelay(100);
       hi_gpio_set_value(gpio_wlan_reg_on, 0);
#endif
}
#endif /* !CONFIG_PLATFORM_OPS */
