/******************************************************************************
 *    NAND Flash Controller V610 Device Driver
 *    Copyright (c) 2009-2010 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Czyong.
 *
******************************************************************************/
#include <asm/io.h>

#include "hinfc610.h"

/*****************************************************************************/

static int hinfc610_toggle_enable_sync(struct hinfc_host *host)
{
	unsigned char toshiba_sync_param[4] = {
		0x00, 0x00, 0x00, 0x00,
	};

	host->set_ecc_randomizer(host, DISABLE, DISABLE);

	hinfc_write(host, 1, HINFC610_DATA_NUM);
	hinfc_write(host, 0xEF, HINFC610_CMD);
	hinfc_write(host, 0x80, HINFC610_ADDRL);
	writel(toshiba_sync_param[0], host->iobase);
	hinfc_write(host, HINFC610_WRITE_1CMD_1ADD_DATA, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	writel(toshiba_sync_param[1], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	writel(toshiba_sync_param[2], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	/* need to config WAIT_READY_EN. */
	writel(toshiba_sync_param[3], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA_WAIT_READY, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	host->set_ecc_randomizer(host, ENABLE, ENABLE);

	return 0;
}
/*****************************************************************************/

static int hinfc610_toggle_disable_sync(struct hinfc_host *host)
{
	unsigned char toshiba_sync_param[4] = {
		0x01, 0x00, 0x00, 0x00,
	};

	host->set_ecc_randomizer(host, DISABLE, DISABLE);

	hinfc_write(host, 1, HINFC610_DATA_NUM);
	hinfc_write(host, 0xEF, HINFC610_CMD);
	hinfc_write(host, 0x80, HINFC610_ADDRL);
	writel(toshiba_sync_param[0], host->iobase);
	hinfc_write(host, HINFC610_WRITE_1CMD_1ADD_DATA_SYNC, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	writel(toshiba_sync_param[1], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA_SYNC, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	writel(toshiba_sync_param[2], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA_SYNC, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	/* need to config WAIT_READY_EN */
	writel(toshiba_sync_param[3], host->iobase);
	hinfc_write(host, HINFC610_WRITE_0CMD_1ADD_DATA_SYNC_WAIT_READY, HINFC610_OP);
	WAIT_CONTROLLER_FINISH();

	host->set_ecc_randomizer(host, ENABLE, ENABLE);

	return 0;
}
/*****************************************************************************/

struct nand_sync hinfc610_sync_toggle_10 = {
	.type    = NAND_TYPE_TOGGLE_10,
	.enable  = hinfc610_toggle_enable_sync,
	.disable = hinfc610_toggle_disable_sync,
};
