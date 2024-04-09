#include <hinfc_gen.h>
#include <linux/mtd/nand.h>
#include <common.h>

#include "hiflash.h"
#include "nand_sync.h"

/******************************************************************************/
int enable_sync_toggle_v10(struct flash_regop *regop)
{
	/* B0: 0x1->SDR, 0x0->toggle ddr1.0 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u32 status = 0x0;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x80;
	regop_info.addr_cycle = 1;
	regop_info.buf = (u8 *)&status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/******************************************************************************/
int disable_sync_toggle_v10(struct flash_regop *regop)
{
	/* B0: 0x1->SDR, 0x0->toggle ddr1.0 
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u32 status = 0x1;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x80;
	regop_info.addr_cycle = 1;
	regop_info.buf = (u8 *)&status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/******************************************************************************/

int enable_sync_toggle_v20(struct flash_regop *regop)
{
	/* B0: 0 0 0 0 rsv RE DQSN Verf 
	 * for toggle 2.0, enable Vref only.
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u32 status = 0x00;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x80;
	regop_info.addr_cycle = 1;
	regop_info.buf = (u8 *)&status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/******************************************************************************/

int disable_sync_toggle_v20(struct flash_regop *regop)
{
	/* B0: 0 0 0 0 rsv RE DQSN Verf 
	 * for toggle 2.0, enable Vref only.
	 * B1: 0
	 * B2: 0
	 * B3: 0
	 */
	u32 status = 0x01;
	struct flash_regop_info regop_info = {0};

	/* set feature. */
	regop_info.priv = regop->priv;
	regop_info.cmd = 0xEF;
	regop_info.nr_cmd = 1;
	regop_info.addrl = 0x80;
	regop_info.addr_cycle = 1;
	regop_info.buf = (u8 *)&status;
	regop_info.sz_buf = 4;
	regop_info.wait_ready = true;

	regop->write_reg(&regop_info);

	return 0;
}
/******************************************************************************/


struct nand_sync_t nand_sync_toggle_v10 = {
	.type         = NAND_MODE_SYNC_TOGGLE10,
	.enable       = enable_sync_toggle_v10,
	.disable      = disable_sync_toggle_v10,
};
/******************************************************************************/

struct nand_sync_t nand_sync_toggle_v20 = {
	.type         = NAND_MODE_SYNC_TOGGLE20,
	.enable       = enable_sync_toggle_v20,
	.disable      = disable_sync_toggle_v20,
};
