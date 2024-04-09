/*
  * Copyright (c) 2016 MediaTek Inc.  All rights reserved.
  *
  * This software is available to you under a choice of one of two
  * licenses.  You may choose to be licensed under the terms of the GNU
  * General Public License (GPL) Version 2, available from the file
  * COPYING in the main directory of this source tree, or the
  * BSD license below:
  *
  *     Redistribution and use in source and binary forms, with or
  *     without modification, are permitted provided that the following
  *     conditions are met:
  *
  *      - Redistributions of source code must retain the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer.
  *
  *      - Redistributions in binary form must reproduce the above
  *        copyright notice, this list of conditions and the following
  *        disclaimer in the documentation and/or other materials
  *        provided with the distribution.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  * SOFTWARE.
  */


#define RTMP_MODULE_OS

/*#include <rt_config.h> */
#include "rtmp_comm.h"
#include "rt_os_util.h"
#include "rt_os_net.h"
#include <linux/pci.h>

IRQ_HANDLE_TYPE
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 19))
rt2860_interrupt(int irq, void *dev_instance);
#else
rt2860_interrupt(int irq, void *dev_instance, struct pt_regs *regs);
#endif /* endif */

/***************************************************************************
  *
  *	interrupt handler related procedures.
  *
  **************************************************************************/
/*int print_int_count; */

IRQ_HANDLE_TYPE
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 19))
rt2860_interrupt(int irq, void *dev_instance)
#else
rt2860_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
#endif				/* endif */
{
	struct net_device *net_dev = (struct net_device *)dev_instance;
	VOID *pAd = NULL;
#ifdef MULTI_CORE_SUPPORT
	unsigned long flags = 0;
#endif /* MULTI_CORE_SUPPORT */

	GET_PAD_FROM_NET_DEV(pAd, net_dev);

	RTMPHandleInterrupt(pAd);

	return IRQ_HANDLED;

}
