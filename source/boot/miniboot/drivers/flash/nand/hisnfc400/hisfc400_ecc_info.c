/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-05
 *
******************************************************************************/
#include <stddef.h>
#include <nand_ctrl.h>

#include "hisfc400.h"
#include "hisfc400_gen.h"

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But...
 */
static struct nand_ctrl_oob_t nand_ecc_default =
{
	2, 30
};

#ifndef CONFIG_YAFFS2_SUPPORT
static struct nand_ctrl_oob_t nand_ecc_2k16bit =
{
	2, 6
};
#endif

#ifndef CONFIG_YAFFS2_SUPPORT
static struct nand_ctrl_oob_t nand_ecc_4k16bit =
{
	2, 14
};
#endif
/*****************************************************************************/

static inline int nandpage_type2size(int type)
{
	return (1 << (NAND_PAGE_SHIFT + type));
}
/*****************************************************************************/

static struct nand_ctrl_info_t hisfc400_hw_config_table[] =
{
	{_4K, NAND_ECC_24BIT, 200 /*200*/,  &nand_ecc_default},
#ifndef CONFIG_YAFFS2_SUPPORT
	{_4K, NAND_ECC_16BIT, 128 /*128*/,  &nand_ecc_4k16bit},
#endif
	{_4K, NAND_ECC_8BIT,  88  /*88*/,   &nand_ecc_default},
	{_4K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{_2K, NAND_ECC_24BIT, 116 /*116*/,  &nand_ecc_default},
#ifndef CONFIG_YAFFS2_SUPPORT
	{_2K, NAND_ECC_16BIT, 64  /*64*/,   &nand_ecc_2k16bit},
#endif
	{_2K, NAND_ECC_8BIT,  60  /*60*/,   &nand_ecc_default},
	{_2K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{0,0,0,NULL},
};

/*****************************************************************************/
/* used the best correct arithmetic. */
struct nand_ctrl_info_t *hisfc400_get_best_ecc(struct spi_nand_chip_info_t *nand_info)
{
	struct nand_ctrl_info_t *best = NULL;
	struct nand_ctrl_info_t *config = hisfc400_hw_config_table;

	for (; config->layout; config++) {
		if (config->pagesize != nand_info->pagesize)
			continue;

		if (nand_info->oobsize < config->oobsize)
			continue;

		if (!best || (best->ecctype < config->ecctype))
			best = config;
	}

	if (!best)
		DBG_BUG(ERSTR_DRIVER "Driver does not support the pagesize(%d) and oobsize(%d).\n",
			     nand_info->pagesize, nand_info->oobsize);

	return best;
}
/*****************************************************************************/
/* force the pagesize and ecctype */
struct nand_ctrl_info_t *hisfc400_force_ecc(struct spi_nand_chip_info_t *nand_info, 
					    int pagetype, int ecctype, 
					    char *cfgmsg, int allow_pagediv)
{
	int pagesize;
	struct nand_ctrl_info_t *fit = NULL;
	struct nand_ctrl_info_t *config = NULL; 

	config = hisfc400_hw_config_table;

	pagesize = nandpage_type2size(pagetype);

	for (; config->layout; config++) {
		if (config->pagesize == pagesize
			&& config->ecctype == ecctype) {
			fit = config;
			break;
		}
	}

	if (!fit) {
		DBG_BUG("Driver(%s mode) does not support this Nand Flash pagesize:%d, ecctype:%s\n",
			     cfgmsg, pagesize, nand_ecc_name(ecctype));
		return NULL;
	}

	if ((pagesize != nand_info->pagesize)
		&& (pagesize > nand_info->pagesize || !allow_pagediv)) {
		DBG_BUG("Hardware (%s mode) configure pagesize %d, but the Nand Flash pageszie is %d\n",
			     cfgmsg, pagesize, nand_info->pagesize);
		return NULL;
	}

	if (fit->oobsize > nand_info->oobsize) {
		DBG_BUG("(%s mode) The Nand Flash offer space area is %d bytes, but the controller request %d bytes in ecc %s. "
			     "Please make sure the hardware ECC configuration is correct.",
			     cfgmsg, nand_info->oobsize, fit->oobsize,
			     nand_ecc_name(ecctype));
		return NULL;
	}

	return fit;
}
