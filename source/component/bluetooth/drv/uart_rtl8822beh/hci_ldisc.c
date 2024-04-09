/*
 *
 *  Bluetooth HCI UART driver
 *
 *  Copyright (C) 2000-2001  Qualcomm Incorporated
 *  Copyright (C) 2002-2003  Maxim Krasnyansky <maxk@qualcomm.com>
 *  Copyright (C) 2004-2005  Marcel Holtmann <marcel@holtmann.org>
 *
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ptrace.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/tty.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/ioctl.h>
#include <linux/skbuff.h>
#include <linux/version.h>

#include <linux/suspend.h>

#include <net/bluetooth/bluetooth.h>
#include <net/bluetooth/hci_core.h>

#include "hci_uart.h"

#ifdef BTCOEX
#include "rtk_coex.h"
#endif

#define VERSION "2.2"

#if HCI_VERSION_CODE > KERNEL_VERSION(3, 4, 0)
#define GET_DRV_DATA(x)		hci_get_drvdata(x)
#else
#define GET_DRV_DATA(x)		(struct hci_uart *)(x->driver_data)
#endif

#if HCI_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
static int reset = 0;
#endif

static struct hci_uart_proto *hup[HCI_UART_MAX_PROTO];

int hci_uart_register_proto(struct hci_uart_proto *p)
{
	if (p->id >= HCI_UART_MAX_PROTO)
		return -EINVAL;

	if (hup[p->id])
		return -EEXIST;

	hup[p->id] = p;

	return 0;
}

int hci_uart_unregister_proto(struct hci_uart_proto *p)
{
	if (p->id >= HCI_UART_MAX_PROTO)
		return -EINVAL;

	if (!hup[p->id])
		return -EINVAL;

	hup[p->id] = NULL;

	return 0;
}

static struct hci_uart_proto *hci_uart_get_proto(unsigned int id)
{
	if (id >= HCI_UART_MAX_PROTO)
		return NULL;

	return hup[id];
}

static inline void hci_uart_tx_complete(struct hci_uart *hu, int pkt_type)
{
	struct hci_dev *hdev = hu->hdev;

	/* Update HCI stat counters */
	switch (pkt_type) {
	case HCI_COMMAND_PKT:
		hdev->stat.cmd_tx++;
		break;

	case HCI_ACLDATA_PKT:
		hdev->stat.acl_tx++;
		break;

	case HCI_SCODATA_PKT:
		hdev->stat.sco_tx++;
		break;
	}
}

static inline struct sk_buff *hci_uart_dequeue(struct hci_uart *hu)
{
	struct sk_buff *skb = hu->tx_skb;

	if (!skb)
		skb = hu->proto->dequeue(hu);
	else
		hu->tx_skb = NULL;

	return skb;
}

int hci_uart_tx_wakeup(struct hci_uart *hu)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 14, 0)
	struct tty_struct *tty = hu->tty;
	struct hci_dev *hdev = hu->hdev;
	struct sk_buff *skb;
#endif

	if (test_and_set_bit(HCI_UART_SENDING, &hu->tx_state)) {
		set_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);
		return 0;
	}

	BT_DBG("");

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0)
	schedule_work(&hu->write_work);
#else
 restart:
	clear_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);

	while ((skb = hci_uart_dequeue(hu))) {
		int len;

		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		len = tty->ops->write(tty, skb->data, skb->len);
		hdev->stat.byte_tx += len;

		skb_pull(skb, len);
		if (skb->len) {
			hu->tx_skb = skb;
			break;
		}

		hci_uart_tx_complete(hu, bt_cb(skb)->pkt_type);
		kfree_skb(skb);
	}

	if (test_bit(HCI_UART_TX_WAKEUP, &hu->tx_state))
		goto restart;

	clear_bit(HCI_UART_SENDING, &hu->tx_state);
#endif

	return 0;
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0)
static void hci_uart_write_work(struct work_struct *work)
{
	struct hci_uart *hu = container_of(work, struct hci_uart, write_work);
	struct tty_struct *tty = hu->tty;
	struct hci_dev *hdev = hu->hdev;
	struct sk_buff *skb;

	/* REVISIT: should we cope with bad skbs or ->write() returning
	 * and error value ?
	 */

 restart:
	clear_bit(HCI_UART_TX_WAKEUP, &hu->tx_state);

	while ((skb = hci_uart_dequeue(hu))) {
		int len;

		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		len = tty->ops->write(tty, skb->data, skb->len);
		hdev->stat.byte_tx += len;

		skb_pull(skb, len);
		if (skb->len) {
			hu->tx_skb = skb;
			break;
		}

		hci_uart_tx_complete(hu, bt_cb(skb)->pkt_type);
		kfree_skb(skb);
	}

	if (test_bit(HCI_UART_TX_WAKEUP, &hu->tx_state))
		goto restart;

	clear_bit(HCI_UART_SENDING, &hu->tx_state);
	return;
}
#endif

/* ------- Interface to HCI layer ------ */
/* Initialize device */
static int hci_uart_open(struct hci_dev *hdev)
{
	BT_DBG("%s %p", hdev->name, hdev);

	/* Nothing to do for UART driver */

#if HCI_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	set_bit(HCI_RUNNING, &hdev->flags);
#endif

#ifdef BTCOEX
	rtk_btcoex_open(hdev);
#endif

	return 0;
}

/* Reset device */
static int hci_uart_flush(struct hci_dev *hdev)
{
	struct hci_uart *hu = GET_DRV_DATA(hdev);	//(struct hci_uart *) hdev->driver_data;
	struct tty_struct *tty = hu->tty;

	BT_DBG("hdev %p tty %p", hdev, tty);

	if (hu->tx_skb) {
		kfree_skb(hu->tx_skb);
		hu->tx_skb = NULL;
	}

	/* Flush any pending characters in the driver and discipline. */
	tty_ldisc_flush(tty);
	tty_driver_flush_buffer(tty);

	if (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hu->proto->flush(hu);

	return 0;
}

/* Close device */
static int hci_uart_close(struct hci_dev *hdev)
{
	BT_DBG("hdev %p", hdev);


	/* When in kernel 4.4.0 and greater, the HCI_RUNNING bit is
	 * cleared in hci_dev_do_close(). */
#if HCI_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	if (!test_and_clear_bit(HCI_RUNNING, &hdev->flags))
		return 0;
#else
	if (test_bit(HCI_RUNNING, &hdev->flags))
		BT_ERR("HCI_RUNNING is not cleared before.");
#endif

	hci_uart_flush(hdev);
	hdev->flush = NULL;

#ifdef BTCOEX
	rtk_btcoex_close();
#endif

	return 0;
}

/* Send frames from HCI layer */
#if HCI_VERSION_CODE < KERNEL_VERSION(3, 13, 0)
int hci_uart_send_frame(struct sk_buff *skb)
#else
int hci_uart_send_frame(struct hci_dev *hdev, struct sk_buff *skb)
#endif
{
#if HCI_VERSION_CODE < KERNEL_VERSION(3, 13, 0)
	struct hci_dev *hdev = (struct hci_dev *)skb->dev;
#endif
	struct hci_uart *hu;

	if (!hdev) {
		BT_ERR("Frame for unknown device (hdev=NULL)");
		return -ENODEV;
	}

#if HCI_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	if (!test_bit(HCI_RUNNING, &hdev->flags))
		return -EBUSY;
#endif

	hu = GET_DRV_DATA(hdev);	//(struct hci_uart *) hdev->driver_data;

	BT_DBG("%s: type %d len %d", hdev->name, bt_cb(skb)->pkt_type,
	       skb->len);

#ifdef BTCOEX
	if (bt_cb(skb)->pkt_type == HCI_COMMAND_PKT)
		rtk_btcoex_parse_cmd(skb->data, skb->len);
	if (bt_cb(skb)->pkt_type == HCI_ACLDATA_PKT)
		rtk_btcoex_parse_l2cap_data_tx(skb->data, skb->len);
#endif

	hu->proto->enqueue(hu, skb);

	hci_uart_tx_wakeup(hu);

	return 0;
}

#if HCI_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
static void hci_uart_destruct(struct hci_dev *hdev)
{
	if (!hdev)
		return;

	BT_DBG("%s", hdev->name);
	kfree(hdev->driver_data);
}
#endif

/* ------ LDISC part ------ */
/* hci_uart_tty_open
 *
 * Called when line discipline changed to HCI_UART.
 *
 * Arguments:
 *     tty    pointer to tty info structure
 * Return Value:
 *     0 if success, otherwise error code
 */
static int hci_uart_tty_open(struct tty_struct *tty)
{
	struct hci_uart *hu = (void *)tty->disc_data;

	BT_DBG("tty %p", tty);

	/* But nothing ensures disc_data to be NULL. And since ld->ops->open
	 * shall be called only once, we do not need the check at all.
	 * So remove it.
	 *
	 * Note that this is not an issue now, but n_tty will start using the
	 * disc_data pointer and this invalid 'if' would trigger then rendering
	 * TTYs over BT unusable.
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 8, 0)
	/* FIXME: This btw is bogus, nothing requires the old ldisc to clear
	 * the pointer
	 */
	if (hu)
		return -EEXIST;
#endif

	/* Error if the tty has no write op instead of leaving an exploitable
	 * hole
	 */
	if (tty->ops->write == NULL)
		return -EOPNOTSUPP;

	if (!(hu = kzalloc(sizeof(struct hci_uart), GFP_KERNEL))) {
		BT_ERR("Can't allocate control structure");
		return -ENFILE;
	}

	tty->disc_data = hu;
	hu->tty = tty;
	tty->receive_room = 65536;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0)
	INIT_WORK(&hu->write_work, hci_uart_write_work);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	spin_lock_init(&hu->rx_lock);
#endif

	/* Flush any pending characters in the driver and line discipline. */

	/* FIXME: why is this needed. Note don't use ldisc_ref here as the
	   open path is before the ldisc is referencable */

	if (tty->ldisc->ops->flush_buffer)
		tty->ldisc->ops->flush_buffer(tty);
	tty_driver_flush_buffer(tty);

	return 0;
}

/* hci_uart_tty_close()
 *
 * Called when the line discipline is changed to something
 * else, the tty is closed, or the tty detects a hangup.
 */
static void hci_uart_tty_close(struct tty_struct *tty)
{
	struct hci_uart *hu = (void *)tty->disc_data;
	struct hci_dev *hdev;

	BT_DBG("tty %p", tty);

	/* Detach from the tty */
	tty->disc_data = NULL;

	if (!hu)
		return;

	hdev = hu->hdev;
	if (hdev)
		hci_uart_close(hdev);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 14, 0)
	cancel_work_sync(&hu->write_work);
#endif

	if (test_and_clear_bit(HCI_UART_PROTO_READY, &hu->flags)) {
		if (hdev) {
			if (test_bit(HCI_UART_REGISTERED, &hu->flags))
				hci_unregister_dev(hdev);
			hci_free_dev(hdev);
		}
		hu->proto->close(hu);
	}
	clear_bit(HCI_UART_PROTO_SET, &hu->flags);
	unregister_pm_notifier(&hu->hci_uart_pm_notif_block);

	kfree(hu);
}

/* hci_uart_tty_wakeup()
 *
 * Callback for transmit wakeup. Called when low level
 * device driver can accept more send data.
 *
 * Arguments:        tty    pointer to associated tty instance data
 * Return Value:    None
 */
static void hci_uart_tty_wakeup(struct tty_struct *tty)
{
	struct hci_uart *hu = (void *)tty->disc_data;

	BT_DBG("");

	if (!hu)
		return;

	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	if (tty != hu->tty)
		return;

	if (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hci_uart_tx_wakeup(hu);
}

/* hci_uart_tty_receive()
 *
 * Called by tty low level driver when receive data is
 * available.
 *
 * Arguments:  tty          pointer to tty isntance data
 *             data         pointer to received data
 *             flags        pointer to flags for data
 *             count        count of received data in bytes
 *
 * Return Value:    None
 */
static void hci_uart_tty_receive(struct tty_struct *tty, const u8 * data,
				 char *flags, int count)
{
	struct hci_uart *hu = (void *)tty->disc_data;

	if (!hu || tty != hu->tty)
		return;

	if (!test_bit(HCI_UART_PROTO_READY, &hu->flags))
		return;

	/* It does not need a lock here as it is already protected by a mutex in
	 * tty caller
	 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	spin_lock(&hu->rx_lock);
#endif

	hu->proto->recv(hu, (void *)data, count);

	if (hu->hdev)
		hu->hdev->stat.byte_rx += count;

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 4, 0)
	spin_unlock(&hu->rx_lock);
#endif

	tty_unthrottle(tty);
}

static int hci_uart_register_dev(struct hci_uart *hu)
{
	struct hci_dev *hdev;

	BT_INFO("hci_uart_register_dev");

	/* Initialize and register HCI device */
	hdev = hci_alloc_dev();
	if (!hdev) {
		BT_ERR("Can't allocate HCI device");
		return -ENOMEM;
	}

	hu->hdev = hdev;

#if HCI_VERSION_CODE > KERNEL_VERSION(2, 6, 33)
	hdev->bus = HCI_UART;
#else
	hdev->type = HCI_UART;
#endif

#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 4, 0)
	hci_set_drvdata(hdev, hu);
#else
	hdev->driver_data = hu;
#endif

	hdev->open = hci_uart_open;
	hdev->close = hci_uart_close;
	hdev->flush = hci_uart_flush;
	hdev->send = hci_uart_send_frame;

	/* NOTE: No hdev->setup setting for Realtek BTUART because
	 * the download procedure is done with rtk_hciattach in userspace
	 * before this function called in hci_uart_set_proto()
	 */

	SET_HCIDEV_DEV(hdev, hu->tty->dev);

#if HCI_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
	hdev->destruct = hci_uart_destruct;
	hdev->owner = THIS_MODULE;
#endif

#if HCI_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
	if (!reset)
		set_bit(HCI_QUIRK_NO_RESET, &hdev->quirks);
#endif

#if HCI_VERSION_CODE >= KERNEL_VERSION(2, 6, 36)
	if (test_bit(HCI_UART_RAW_DEVICE, &hu->hdev_flags))
		set_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks);
#endif

#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
	if (test_bit(HCI_UART_EXT_CONFIG, &hu->hdev_flags))
		set_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks);
#endif

#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 4, 0)
	if (!test_bit(HCI_UART_RESET_ON_INIT, &hu->hdev_flags))
#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 6, 0)
		set_bit(HCI_QUIRK_RESET_ON_CLOSE, &hdev->quirks);
#else
		set_bit(HCI_QUIRK_NO_RESET, &hdev->quirks);
#endif
#endif

#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 4, 0)
	if (test_bit(HCI_UART_CREATE_AMP, &hu->hdev_flags))
		hdev->dev_type = HCI_AMP;
	else
#if HCI_VERSION_CODE < KERNEL_VERSION(4, 8, 0)
		hdev->dev_type = HCI_BREDR;
#else
		hdev->dev_type = HCI_PRIMARY;
#endif
#endif

	if (hci_register_dev(hdev) < 0) {
		BT_ERR("Can't register HCI device");
		hci_free_dev(hdev);
		return -ENODEV;
	}

	set_bit(HCI_UART_REGISTERED, &hu->flags);

#ifdef BTCOEX
	rtk_btcoex_probe(hdev);
#endif

	return 0;
}

static int hci_uart_pm_notif(struct notifier_block *b, unsigned long v, void *d);
static int hci_uart_set_proto(struct hci_uart *hu, int id)
{
	struct hci_uart_proto *p;
	int err;

	p = hci_uart_get_proto(id);
	if (!p)
		return -EPROTONOSUPPORT;

	err = p->open(hu);
	if (err)
		return err;

	hu->proto = p;
	set_bit(HCI_UART_PROTO_READY, &hu->flags);

	/* Initialize and register HCI dev */
	err = hci_uart_register_dev(hu);
	if (err) {
		clear_bit(HCI_UART_PROTO_READY, &hu->flags);
		p->close(hu);
		return err;
	}

	hu->hci_uart_pm_notif_block.notifier_call = hci_uart_pm_notif;
	register_pm_notifier(&hu->hci_uart_pm_notif_block);
	return 0;
}

#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
static int hci_uart_set_flags(struct hci_uart *hu, unsigned long flags)
{
	/* TODO: Add HCI_UART_INIT_PENDING, HCI_UART_VND_DETECT check  */
	unsigned long valid_flags = BIT(HCI_UART_RAW_DEVICE) |
				    BIT(HCI_UART_RESET_ON_INIT) |
				    BIT(HCI_UART_CREATE_AMP) |
				    BIT(HCI_UART_EXT_CONFIG);

	if (flags & ~valid_flags)
		return -EINVAL;

	hu->hdev_flags = flags;

	return 0;
}
#endif

/* hci_uart_tty_ioctl()
 *
 *    Process IOCTL system call for the tty device.
 *
 * Arguments:
 *
 *    tty        pointer to tty instance data
 *    file       pointer to open file object for device
 *    cmd        IOCTL command code
 *    arg        argument for IOCTL call (cmd dependent)
 *
 * Return Value:    Command dependent
 */
static int hci_uart_tty_ioctl(struct tty_struct *tty, struct file *file,
			      unsigned int cmd, unsigned long arg)
{
	struct hci_uart *hu = (void *)tty->disc_data;
	int err = 0;

	BT_DBG("");

	/* Verify the status of the device */
	if (!hu)
		return -EBADF;

	switch (cmd) {
	case HCIUARTSETPROTO:
		if (!test_and_set_bit(HCI_UART_PROTO_SET, &hu->flags)) {
			err = hci_uart_set_proto(hu, arg);
			if (err) {
				clear_bit(HCI_UART_PROTO_SET, &hu->flags);
				return err;
			}
		} else
			return -EBUSY;
		break;

	case HCIUARTGETPROTO:
		if (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			return hu->proto->id;
		return -EUNATCH;

	case HCIUARTGETDEVICE:
		if (test_bit(HCI_UART_REGISTERED, &hu->flags))
			return hu->hdev->id;
		return -EUNATCH;

	case HCIUARTSETFLAGS:
		if (test_bit(HCI_UART_PROTO_SET, &hu->flags))
			return -EBUSY;
#if HCI_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
		err = hci_uart_set_flags(hu, arg);
		if (err)
			return err;
#else
		hu->hdev_flags = arg;
#endif
		break;

	case HCIUARTGETFLAGS:
		return hu->hdev_flags;

	default:
		err = n_tty_ioctl_helper(tty, file, cmd, arg);
		break;
	};

	return err;
}

/*
 * We don't provide read/write/poll interface for user space.
 */
static ssize_t hci_uart_tty_read(struct tty_struct *tty, struct file *file,
				 unsigned char __user * buf, size_t nr)
{
	return 0;
}

static ssize_t hci_uart_tty_write(struct tty_struct *tty, struct file *file,
				  const unsigned char *data, size_t count)
{
	return 0;
}

static unsigned int hci_uart_tty_poll(struct tty_struct *tty,
				      struct file *filp, poll_table * wait)
{
	return 0;
}

#define HCI_OP_SUSPEND 	0xfc28
struct hci_cp_suspend {
	__u8 suspend;
} __attribute__ ((packed));

struct sk_buff *hci_prepare_cmd(struct hci_dev *hdev, u16 opcode, u32 plen,
                                const void *param)
{
        int len = HCI_COMMAND_HDR_SIZE + plen;
        struct hci_command_hdr *hdr;
        struct sk_buff *skb;
        
        skb = bt_skb_alloc(len, GFP_ATOMIC);
        if (!skb)
                return NULL;
        
        hdr = (struct hci_command_hdr *) skb_put(skb, HCI_COMMAND_HDR_SIZE);
        hdr->opcode = cpu_to_le16(opcode);
        hdr->plen   = plen;

        if (plen)
                memcpy(skb_put(skb, plen), param, plen);

        BT_DBG("skb len %d", skb->len);
                
        bt_cb(skb)->pkt_type = HCI_COMMAND_PKT;
        bt_cb(skb)->hci.opcode = opcode;

        return skb;
}


static int hci_uart_pm_notif(struct notifier_block *b, unsigned long v, void *d)
{
	struct sk_buff *skb;
	struct hci_uart *hu = container_of(b, struct hci_uart, hci_uart_pm_notif_block);

	BT_INFO("hci_uart_pm_notif %lu", v);
	
	switch(v) {
	case PM_SUSPEND_PREPARE:
	{
		/* use bt stack utils */
		//skb = hci_cmd_sync(hu->hdev, 0xfc28, 1, &param, HCI_INIT_TIMEOUT);
		//if (IS_ERR(skb)) {
		//	BT_ERR("Realtek Suspend h5-bt failed");
		//	return 1;
		//}
		///* check needed? */
		//kfree_skb(skb); 

		/* use hci_uart_send_frame */
		struct hci_cp_suspend cp;

		memset(&cp, 0, sizeof(cp));
		cp.suspend = 0x01;
		skb = hci_prepare_cmd(hu->hdev, HCI_OP_SUSPEND, sizeof(cp), &cp);
		if (!skb) {
			BT_ERR("%s, no memory for command", hu->hdev->name);
			return -ENOMEM;
		}

		/* Stand-alone HCI commands must be flagged as 
         	 * single-command requests. 
         	 */ 
        	//bt_cb(skb)->hci.req_start = true;		

		BT_INFO("rtk bt suspending");
		hci_uart_send_frame(hu->hdev, skb);

		/* FIXME: How to confirm that HCI command was sent to
		 * BT Controller and h5 ack was received */
		msleep(30);
		return 0;
	}
	default:
		BT_INFO("caught msg other than SUSPEND_PREPARE");
		return 0;
	}

} 

static int __init hci_uart_init(void)
{
	static struct tty_ldisc_ops hci_uart_ldisc;
	int err;

	BT_INFO("HCI UART driver ver %s", VERSION);

	/* Register the tty discipline */

	memset(&hci_uart_ldisc, 0, sizeof(hci_uart_ldisc));
	hci_uart_ldisc.magic = TTY_LDISC_MAGIC;
	hci_uart_ldisc.name = "n_hci";
	hci_uart_ldisc.open = hci_uart_tty_open;
	hci_uart_ldisc.close = hci_uart_tty_close;
	hci_uart_ldisc.read = hci_uart_tty_read;
	hci_uart_ldisc.write = hci_uart_tty_write;
	hci_uart_ldisc.ioctl = hci_uart_tty_ioctl;
	hci_uart_ldisc.poll = hci_uart_tty_poll;
	hci_uart_ldisc.receive_buf = hci_uart_tty_receive;
	hci_uart_ldisc.write_wakeup = hci_uart_tty_wakeup;
	hci_uart_ldisc.owner = THIS_MODULE;

	if ((err = tty_register_ldisc(N_HCI, &hci_uart_ldisc))) {
		BT_ERR("HCI line discipline registration failed. (%d)", err);
		return err;
	}
#ifdef CONFIG_BT_HCIUART_H4
	h4_init();
#endif
	/* Add realtek h5 support */
	h5_init();

#ifdef BTCOEX
	rtk_btcoex_init();
#endif


	return 0;
}

static void __exit hci_uart_exit(void)
{
	int err;

#ifdef CONFIG_BT_HCIUART_H4
	h4_deinit();
#endif
	h5_deinit();

	/* Release tty registration of line discipline */
	if ((err = tty_unregister_ldisc(N_HCI)))
		BT_ERR("Can't unregister HCI line discipline (%d)", err);

#ifdef BTCOEX
	rtk_btcoex_exit();
#endif
	

}

module_init(hci_uart_init);
module_exit(hci_uart_exit);

#if HCI_VERSION_CODE < KERNEL_VERSION(3, 4, 0)
module_param(reset, bool, 0644);
MODULE_PARM_DESC(reset, "Send HCI reset command on initialization");
#endif

MODULE_AUTHOR("Marcel Holtmann <marcel@holtmann.org>");
MODULE_DESCRIPTION("Bluetooth HCI UART driver ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_LDISC(N_HCI);
