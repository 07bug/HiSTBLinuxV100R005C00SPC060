/******************************************************************************
 *  Copyright (C) 2015 Hisilicon Technologies CO.,LTD.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiyong 2015.6.25
 *
******************************************************************************/

#define DEVNAME  "hifmc100"
#define pr_fmt(fmt) DEVNAME": " fmt

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <malloc.h>
#include <match_table.h>
#include <asm/arch/platform.h>
#include <linux/mtd/nand.h>
#include <hinfc_gen.h>
#include <hinfc_gen.h>

#include "hifmc100_reg.h"
#include "hifmc100_host.h"

/******************************************************************************/

struct hifmc_host *host;
/******************************************************************************/
#if 0
static void nand_register_dump(void)
{
	int ix;
	u32 regbase = CONFIG_HIFMC100_REG_BASE_ADDRESS;

	printf("Register dump:");
	for (ix = 0; ix <= 0xDC; ix += 0x04) {
		if (!(ix & 0x0F))
			printf("\n0x%08X: ", (regbase + ix));
		printf("%08X ", readl(regbase + ix));
	}
	printf("\n");
}
#endif
/******************************************************************************/

static void hifmc100_set_ifmode(struct hifmc_host *host, int ifmode)
{
	u32 regval;

	if (host->ifmode == HIFMC_IFMODE_INVALID || host->ifmode == ifmode)
		return;

	host->ifmode = ifmode;

	regval = hifmc_read(host, HIFMC100_CFG);
	regval &= ~HIFMC100_CFG_FLASH_SEL_MASK;

	switch (ifmode) {
	case HIFMC_IFMODE_SPINOR:
		regval |= HIFMC100_CFG_FLASH_SEL_SPINOR;
		/* dynamic clock, in every read/write/erase operation */
		break;
	case HIFMC_IFMODE_NAND:
		regval |= HIFMC100_CFG_FLASH_SEL_NAND;
		host->set_clock(host, host->nand->clk_rate, ENABLE);
		break;
	case HIFMC_IFMODE_SPINAND:
		regval |= HIFMC100_CFG_FLASH_SEL_SPINAND;
		host->set_clock(host, host->spinand->clk_rate, ENABLE);
		break;
	default:
		BUG_ON(1);
	}

	/* change to normal mode. */
	regval |= HIFMC100_CFG_OP_MODE_NORMAL;

	hifmc_write(host, regval, HIFMC100_CFG);

	/* delay 1ms, change ifmode need delay. */
	udelay(1000);
}
/******************************************************************************/

static void hifmc100_irq_enable(struct hifmc_host *host)
{
	/* clear all interrupt */
	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	/* only enable dma done interrupt. */
	hifmc_write(host, HIFMC100_INT_EN_OP_DONE, HIFMC100_INT_EN);
}

/******************************************************************************/

static int hifmc100_wait_host_ready(struct hifmc_host *host)
{
	u32 regval;
	ulong deadline = 10000000;

	do {
		regval = hifmc_read(host, HIFMC100_OP);
		if (!(regval & HIFMC100_OP_REG_OP_START))
			return 0;
	} while (deadline--);

	PR_BUG("wait host ready timeout, hifmc100 register:\n");

	return -1;
}
/******************************************************************************/

int hifmc100_write_reg(struct flash_regop_info *info)
{
	u32 regval;
	u32 cfg_val;
	u32 global_cfg_val;
	struct hifmc_host *hifmc = (struct hifmc_host *)info->priv;

	BUG_ON(!(hifmc->chipselect == 0 || hifmc->chipselect == 1));

	/* set chip select and address number */
	regval = 0;
	if (hifmc->chipselect)
		regval |= HIFMC100_OP_CFG_FM_CS;
	regval |= HIFMC100_OP_CFG_ADDR_NUM(info->addr_cycle);
	regval |= HIFMC100_OP_CFG_DUMMY_NUM(info->dummy);
	hifmc_write(hifmc, regval, HIFMC100_OP_CFG);

	/* disable ecc */
	regval = cfg_val = hifmc_read(hifmc, HIFMC100_CFG);
	regval &= ~HIFMC100_CFG_ECC_TYPE_MASK;
	hifmc_write(hifmc, regval, HIFMC100_CFG);

	hifmc_write(hifmc, 0, HIFMC100_OP_PARA);

	/* disable randomizer */
	regval = global_cfg_val = hifmc_read(hifmc, HIFMC100_GLOBAL_CFG);
	regval &= ~HIFMC100_GLOBAL_CFG_RANDOMIZER_EN;
	hifmc_write(hifmc, regval, HIFMC100_GLOBAL_CFG);

	/* set command */
	hifmc_write(hifmc, (u32)info->cmd, HIFMC100_CMD);

	/* set address */
	if (info->addr_cycle > 0) {
		if (info->addr_cycle > 4)
			hifmc_write(hifmc, info->addrh, HIFMC100_ADDRH);
		else
			hifmc_write(hifmc, 0, HIFMC100_ADDRH);

		hifmc_write(hifmc, info->addrl, HIFMC100_ADDRL);
	} else {
		/* no address parameter */
		hifmc_write(hifmc, 0, HIFMC100_ADDRH);
		hifmc_write(hifmc, 0, HIFMC100_ADDRL);
	}

	regval = HIFMC100_OP_REG_OP_START | HIFMC100_OP_RW_REG;

	if (info->dummy)
		regval |= HIFMC100_OP_DUMMY_EN;

	/* only nand have wait ready feature, spinand/spinor not support */
	if (info->wait_ready)
		regval |= HIFMC100_OP_WAIT_READY_EN;

	if (info->nr_cmd >= 1) {
		regval |= HIFMC100_OP_CMD1_EN;
		if (info->nr_cmd >= 2)
			regval |= HIFMC100_OP_CMD2_EN;
	}

	/* set data */
	if (info->sz_buf) {
		if (info->sz_buf > hifmc->sz_iobase)
			info->sz_buf = hifmc->sz_iobase;
		regval |= HIFMC100_OP_WRITE_DATA_EN;
		if (info->buf)
			memcpy(hifmc->iobase, info->buf, info->sz_buf);
	}

	hifmc_write(hifmc, HIFMC100_DATA_NUM_CNT(info->sz_buf),
		HIFMC100_DATA_NUM);

	if (info->addr_cycle)
		regval |= HIFMC100_OP_ADDR_EN;

	hifmc_write(hifmc, regval, HIFMC100_OP);

	hifmc100_wait_host_ready(hifmc);

	/* restore ecc configure for debug */
	hifmc_write(hifmc, cfg_val, HIFMC100_CFG);
	/* restore randomizer config for debug */
	hifmc_write(hifmc, global_cfg_val, HIFMC100_GLOBAL_CFG);

	return 0;
}
/******************************************************************************/

int hifmc100_read_reg(struct flash_regop_info *info)
{
	u32 regval;
	u32 cfg_val;
	u32 global_cfg_val;
	struct hifmc_host *hifmc = (struct hifmc_host *)info->priv;

	BUG_ON(!(hifmc->chipselect == 0 || hifmc->chipselect == 1));

	/* set chip select, address number, dummy */
	regval = 0;
	if (hifmc->chipselect)
		regval |= HIFMC100_OP_CFG_FM_CS;
	regval |= HIFMC100_OP_CFG_ADDR_NUM(info->addr_cycle);
	regval |= HIFMC100_OP_CFG_DUMMY_NUM(info->dummy);
	hifmc_write(hifmc, regval, HIFMC100_OP_CFG);

	/* disable ecc */
	regval = cfg_val = hifmc_read(hifmc, HIFMC100_CFG);
	regval &= ~HIFMC100_CFG_ECC_TYPE_MASK;
	hifmc_write(hifmc, regval, HIFMC100_CFG);

	hifmc_write(hifmc, 0, HIFMC100_OP_PARA);

	/* disable randomizer */
	regval = global_cfg_val = hifmc_read(hifmc, HIFMC100_GLOBAL_CFG);
	regval &= ~HIFMC100_GLOBAL_CFG_RANDOMIZER_EN;
	hifmc_write(hifmc, regval, HIFMC100_GLOBAL_CFG);

	/* set command */
	hifmc_write(hifmc, (u32)info->cmd, HIFMC100_CMD);

	/* set address */
	if (info->addr_cycle > 0) {
		if (info->addr_cycle > 4)
			hifmc_write(hifmc, info->addrh, HIFMC100_ADDRH);
		else
			hifmc_write(hifmc, 0, HIFMC100_ADDRH);

		hifmc_write(hifmc, info->addrl, HIFMC100_ADDRL);
	} else {
		hifmc_write(hifmc, 0, HIFMC100_ADDRH);
		hifmc_write(hifmc, 0, HIFMC100_ADDRL);
	}

	/* set data length */
	if (info->sz_buf > hifmc->sz_iobase)
		info->sz_buf = hifmc->sz_iobase;

	hifmc_write(hifmc, HIFMC100_DATA_NUM_CNT(info->sz_buf),
		HIFMC100_DATA_NUM);

	/* for syncmode, need to config HIFMC100_OP_RW_REG.
	 * for asyncmode, do not care this bit.
	 */
	regval = HIFMC100_OP_REG_OP_START | HIFMC100_OP_RW_REG;

	if (info->dummy)
		regval |= HIFMC100_OP_DUMMY_EN;

	/* only nand have wait ready feature, spinand/spinor not support */
	if (info->wait_ready)
		regval |= HIFMC100_OP_WAIT_READY_EN;

	if (info->nr_cmd >= 1) {
		regval |= HIFMC100_OP_CMD1_EN;
		if (info->nr_cmd >= 2)
			regval |= HIFMC100_OP_CMD2_EN;
	}

	if (info->sz_buf)
		regval |= HIFMC100_OP_READ_DATA_EN;

	if (info->addr_cycle)
		regval |= HIFMC100_OP_ADDR_EN;

	/* for syncmode, need to config HIFMC100_OP_RW_REG,
	 * for asyncmode, do not care this bit.
	 */
	if (info->cmd == NAND_CMD_READID)
		regval |= HIFMC100_OP_READID;

	hifmc_write(hifmc, regval, HIFMC100_OP);

	hifmc100_wait_host_ready(hifmc);

	if (info->sz_buf && info->buf)
		memcpy(info->buf, hifmc->iobase, info->sz_buf);

	/* restore ecc configure for debug */
	hifmc_write(hifmc, cfg_val, HIFMC100_CFG);
	/* restore randomizer config for debug */
	hifmc_write(hifmc, global_cfg_val, HIFMC100_GLOBAL_CFG);

	return 0;
}
/******************************************************************************/

int hifmc100_host_init(void)
{
	u32 regval;
	struct nand_sync_timing nand_sync_timing;

	if (host)
		return 0;

	host = kmalloc(sizeof(struct hifmc_host), GFP_KERNEL);
	if (!host) {
		printf("failed to allocate host structure.\n");
		return -1;
	}

	memset(host, 0x00, sizeof(struct hifmc_host));

	host->regbase = (void __iomem *)CONFIG_HIFMC100_REG_BASE_ADDRESS;
	host->iobase = (void __iomem*)CONFIG_HIFMC100_BUFFER_BASE_ADDRESS;
	host->sz_iobase = CONFIG_HIFMC100_BUFFER_SIZE;

#if defined(CONFIG_ARCH_HI3798MV2X) || defined(CONFIG_ARCH_HI3798MV310) || defined(CONFIG_ARCH_HI3796MV2X)
	host->caps |= NAND_MODE_SYNC;
#endif

#ifdef CONFIG_ARCH_HI3798MV310
	host->caps |= HW_READRETRY;
#endif

	hifmc100_set_system_clock(host, 0, ENABLE);

	regval = hifmc_read(host, HIFMC100_VERSION);
	if (regval != HIFMC100_VERSION_VALUE)
		return -ENODEV;

	printf("Found flash memory controller hifmc100.\n");

	/* disable all interrupt */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval &= ~HIFMC100_INT_EN_ALL;
	hifmc_write(host, regval, HIFMC100_INT_EN);

#ifdef HIFMC100_LP_CTRL_SUPPORT
	/* enable low power control. */
	regval = hifmc_read(host, HIFMC100_LP_CTRL);
	regval |= HIFMC100_LP_CTRL_CLK_GATE_EN;
	hifmc_write(host, regval, HIFMC100_LP_CTRL);
#endif

	/* clean all interrupt */
	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	/* configure dma burst width */
	hifmc_write(host, 0xF, HIFMC100_DMA_AHB_CTRL);

	regval = hifmc_read(host, HIFMC100_GLOBAL_CFG);
	if (regval & HIFMC100_GLOBAL_CFG_RANDOMIZER_EN)
		host->flags |= NAND_RANDOMIZER;

	/* check if start from sync mode.
	 * case "powerup/reset/selfboot":
	 * 1. MUST read from fmc buffer
	 * 2. check HIFMC100_CFG regval[15:13]:
	 *    000: async mode.
	 *    100: sync mode(toggle 2.0).
	 * case "tftp->go":
	 * check HIFMC100_CFG register
	 */
#ifdef CONFIG_HIFMC100_NAND_SUPPORT
	if ((host->caps)&NAND_MODE_SYNC) {
		regval = hifmc_read(host, HIFMC100_CFG);
		if (!(regval & HIFMC100_CFG_OP_MODE_NORMAL)) {
			readl(host->iobase);
			regval = hifmc_read(host, HIFMC100_CFG);
			regval &= HIFMC100_CFG_NFMODE_MASK;
			if (regval) {
				host->flags |= hifmc100_syncmode_reg(regval, 0);
				nand_sync_timing.syncmode =  hifmc100_syncmode_reg(regval, 0);
				hifmc100_set_sync_timing(&nand_sync_timing);

			}
		} else if (regval & HIFMC100_CFG_NFMODE_MASK) {
			regval &= HIFMC100_CFG_NFMODE_MASK;
			host->flags |= hifmc100_syncmode_reg(regval, 0);
			nand_sync_timing.syncmode =  hifmc100_syncmode_reg(regval, 0);
			hifmc100_set_sync_timing(&nand_sync_timing);
		}
	}
#endif

	hifmc_write(host, 0, HIFMC100_DMA_SADDR_OOB);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D0);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D1);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D2);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D3);

	host->ifmode = -1;
	host->set_ifmode = hifmc100_set_ifmode;
	host->irq_enable = hifmc100_irq_enable;
	host->wait_host_ready = hifmc100_wait_host_ready;
	host->set_clock       = hifmc100_set_system_clock;

	/*
	 * get ecctype and pagesize from controller,
	 * controller should not reset after boot.
	 */
	regval = hifmc_read(host, HIFMC100_CFG);
	host->reg.fmc_cfg_ecc_type = HIFMC100_CFG_ECC_TYPE_MASK & regval;
	host->reg.fmc_cfg_page_size = HIFMC100_CFG_PAGE_SIZE_MASK & regval;

	return 0;
}

