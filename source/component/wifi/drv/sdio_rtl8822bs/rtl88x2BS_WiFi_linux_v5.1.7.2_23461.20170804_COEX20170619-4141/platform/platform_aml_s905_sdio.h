/******************************************************************************
 *
 * Copyright(c) 2016 - 2017 Realtek Corporation. All rights reserved.
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
#ifndef __PLATFORM_AML_S905_SDIO_H__
#define __PLATFORM_AML_S905_SDIO_H__

#include <linux/version.h>	/* Linux vresion */

extern void sdio_reinit(void);
extern void extern_wifi_set_enable(int is_on);

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 0))
extern void wifi_teardown_dt(void);
extern int wifi_setup_dt(void);
#endif /* kernel < 3.14.0 */

#endif /* __PLATFORM_AML_S905_SDIO_H__ */
