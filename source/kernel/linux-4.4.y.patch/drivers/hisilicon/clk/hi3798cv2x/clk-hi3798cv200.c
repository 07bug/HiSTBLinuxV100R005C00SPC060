/******************************************************************************
 *  Copyright (C) 2014 Hisilicon Technologies CO.,LTD.
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
 * Create By Cai Zhiyong 2014.12.22
 *
******************************************************************************/
#define DRVNAME "hiclk"
#define pr_fmt(fmt) DRVNAME ": " fmt

#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/hisilicon/freq.h>
#include <dt-bindings/clock/hi3798cv200-clock.h>
#include "clk-hisi.h"

#define CLK(_id, _mask, _value, _rstbit, _rate, _ops) \
	{.id = _id,         \
	 .name = #_id,      \
	 .offset = _id,     \
	 .mask = _mask,     \
	 .value = _value,   \
	 .rstbit = _rstbit, \
	 .rate = _rate,     \
	 .ops = _ops,}

#define CLK_SHARED(_id, _off, _mask, _value, _rstbit, _rate, _ops) \
	{.id = _id,         \
	.name = #_id,      \
	.offset = _off,     \
	.mask = _mask,     \
	.value = _value,   \
	.rstbit = _rstbit, \
	.rate = _rate,     \
	.ops = _ops,}

#define SDIO_SAP_PS_SHIFT_BIT              (12)
#define SDIO_SAP_PS_MASK                   (0x7 << 12)
#define SDIO_DRV_PS_MASK                   (0x7 << 16)
/******************************************************************************/

extern struct clk_ops clk_ops_hiusb2;
extern struct clk_ops clk_ops_hiusb3_host0;
extern struct clk_ops clk_ops_hiusb3_host1;
extern struct clk_ops clk_ops_higpu;
extern struct clk_ops clk_ops_hipcie;
extern struct clk_ops clk_ops_hiahci;
extern struct clk_ops clk_ops_hifmc100;
extern struct clk_ops clk_ops_hiir;

static struct hiclk_hw hiclks_hw[] = {
	CLK(PERI_CRG224_FMC,       0x0,     0x0,     0, 0, &clk_ops_hifmc100),
	CLK(PERI_CRG39_SDIO0, 0x77703, 0x32103,   BIT(4), 0, NULL),
	CLK(PERI_CRG40_SDIO1, 0x77703, 0x41003, BIT(4), 0, NULL),
	CLK(PERI_CRG163_SDIO2, 0x77703, 0x32103, BIT(4), 0, NULL),
	CLK(PERI_CRG46_USB2CTRL, 0x0,  0x0,   0x0, 0, &clk_ops_hiusb2),
	CLK(PERI_CRG44_USB3CTRL, 0x0,  0x0,   0x0, 0, &clk_ops_hiusb3_host0),
	CLK(PERI_CRG47_USB2PHY,  0x0,  0x0,   0x0, 0, &clk_ops_hiusb3_host1),
	CLK(PERI_CRG73_GPU_LP,  0x0,  0x0,   0x0, 0, &clk_ops_higpu),
	CLK_SHARED(HIGMAC_MAC0_CLK, PERI_CRG51_GSF, 0xA, 0xA, 0, 0, NULL),
	CLK_SHARED(HIGMAC_MAC1_CLK, PERI_CRG51_GSF, 0x14, 0x14, 0, 0, NULL),
	CLK_SHARED(HIGMAC_MAC_IF0_CLK, PERI_CRG51_GSF, 0x1000000, 0x1000000, 0, 0, NULL),
	CLK_SHARED(HIGMAC_MAC_IF1_CLK, PERI_CRG51_GSF, 0x2000000, 0x2000000, 0, 0, NULL),
	CLK(PERI_CRG99_PCIECTRL, 0x0, 0x0, 0x0, 0, &clk_ops_hipcie),
	CLK(PERI_CRG42_SATA3CTRL, 0x0, 0x0, 0x0, 0, &clk_ops_hiahci),
	CLK_SHARED(HII2C_I2C0_CLK, PERI_CRG27_I2C, 0x10, 0x10, BIT(5), _100MHz, NULL),
	CLK_SHARED(HII2C_I2C1_CLK, PERI_CRG27_I2C, 0x100, 0x100, BIT(9), _100MHz, NULL),
	CLK_SHARED(HII2C_I2C2_CLK, PERI_CRG27_I2C, 0x1000, 0x1000, BIT(13), _100MHz, NULL),
	CLK_SHARED(HII2C_I2C3_CLK, PERI_CRG27_I2C, 0x10000, 0x10000, BIT(17), _100MHz, NULL),
	CLK_SHARED(HII2C_I2C4_CLK, PERI_CRG27_I2C, 0x100000, 0x100000, BIT(21), _100MHz, NULL),
	CLK(PERI_CRG28_SSP, 0x1, 0x1, BIT(1), _100MHz, NULL),
	CLK(HIIR_CLK, 0x0, 0x0, 0, _24MHz, &clk_ops_hiir),
};
/******************************************************************************/

static unsigned long hiclk_recalc_rate_hi3798cv200(struct clk_hw *hw,
						   unsigned long parent_rate)
{
	u32 val;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	val = readl(clk->peri_crgx);

	switch (clk->id) {
	case PERI_CRG39_SDIO0:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _150MHz, _166dot5MHz};

		val = (val >> 8) & 0x7;
		if (val >= ARRAY_SIZE(rate))
			panic("register value out of range.\n");

		clk->rate = rate[val];
		break;
	}
	case PERI_CRG40_SDIO1:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _25MHz, _200MHz, _300MHz, _337dot5MHz, _150MHz};

		val = (val >> 8) & 0x7;
		if (val >= ARRAY_SIZE(rate))
			panic("register value out of range.\n");

		clk->rate = rate[val];
		break;
	}
	case PERI_CRG163_SDIO2:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _150MHz, _166dot5MHz};

		val = (val >> 8) & 0x7;
		if (val >= ARRAY_SIZE(rate))
			panic("register value out of range.\n");

		clk->rate = rate[val];
		break;
	}
	case PERI_CRG224_FMC: {
		unsigned long rate[] = {
			_200MHz, _100MHz, _125MHz,_12MHz,
			_12MHz, _62dot5MHz, _75MHz, _37dot5MHz};
		val = (val >> 5) & 0x7;
		clk->rate = rate[val];
		break;
	}
	default:
		break;
	}

	return clk->rate;
}
/******************************************************************************/

static int hiclk_set_rate_hi3798cv200(struct clk_hw *hw, unsigned long drate,
				unsigned long parent_rate)
{
	u32 val, ix;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	val = readl(clk->peri_crgx);

	switch (clk->id) {
	case PERI_CRG39_SDIO0:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _150MHz, _166dot5MHz};

		for (ix = 0; ix < ARRAY_SIZE(rate); ix++) {
			if (drate == rate[ix]) {
				val &= ~(0x7 << 8);
				val |= (ix << 8);
				writel(val, clk->peri_crgx);
			}
		}

		break;
	}
	case PERI_CRG40_SDIO1:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _25MHz, _200MHz, _300MHz, _337dot5MHz, _150MHz};

		for (ix = 0; ix < ARRAY_SIZE(rate); ix++) {
			if (drate == rate[ix]) {
				val &= ~(0x7 << 8);
				val |= (ix << 8);
				writel(val, clk->peri_crgx);
			}
		}

		break;
	}
	case PERI_CRG163_SDIO2:{
		unsigned long rate[] = {
			_100MHz, _50MHz, _150MHz, _166dot5MHz};

		for (ix = 0; ix < ARRAY_SIZE(rate); ix++) {
			if (drate == rate[ix]) {
				val &= ~(0x7 << 8);
				val |= (ix << 8);
				writel(val, clk->peri_crgx);
			}
		}

		break;
	}
	default:
		break;
	}

	return 0;

}
/******************************************************************************/

static int hiclk_get_phase_hi3798cv200(struct clk_hw *hw)
{
	u32 val = 0;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	switch (clk->id) {
	case PERI_CRG39_SDIO0:
	case PERI_CRG40_SDIO1:
	case PERI_CRG163_SDIO2:{
		val = readl(clk->peri_crgx);
		/* send drive and sample phase together, so shift 12bit for sum < 360 */
		val &= (SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		val = val >> SDIO_SAP_PS_SHIFT_BIT;
		break;
	}
	default:
		break;
	}

	return (int)val;
}
/******************************************************************************/

static int hiclk_set_phase_hi3798cv200(struct clk_hw *hw, int degrees)
{
	u32 val;
	struct hiclk_hw *clk = to_hiclk_hw(hw);

	switch (clk->id) {
	case PERI_CRG39_SDIO0:
	case PERI_CRG40_SDIO1:
	case PERI_CRG163_SDIO2:{
		val = readl(clk->peri_crgx);
		val &= ~(SDIO_SAP_PS_MASK | SDIO_DRV_PS_MASK);
		val |= (((u32)degrees) << SDIO_SAP_PS_SHIFT_BIT);
		writel(val, clk->peri_crgx);
		break;
	}
	default:
		break;
	}

	return 0;
}

/******************************************************************************/

static int hiclk_enable_hi3798cv200(struct clk_hw *hw)
{
	hiclk_enable(hw);
	hiclk_recalc_rate_hi3798cv200(hw, 0);
	return 0;
}
/******************************************************************************/

static struct clk_ops clk_ops_hi3798cv200 = {
	.enable = hiclk_enable_hi3798cv200,
	.recalc_rate = hiclk_recalc_rate_hi3798cv200,
	.set_rate = hiclk_set_rate_hi3798cv200,
	.get_phase = hiclk_get_phase_hi3798cv200,
	.set_phase = hiclk_set_phase_hi3798cv200,
};
/******************************************************************************/

static void __init hi3798cv200_clocks_init(struct device_node *np)
{
	int ix;

	for (ix = 0; ix < ARRAY_SIZE(hiclks_hw); ix++) {
		struct hiclk_hw *hihw = &hiclks_hw[ix];
		struct clk_ops *ops = hihw->ops;

		if (!ops)
			continue;

		if (!ops->enable)
			ops->enable = hiclk_enable_hi3798cv200;
		if (!ops->recalc_rate)
			ops->recalc_rate = hiclk_recalc_rate_hi3798cv200;
	}

	hiclk_clocks_init(np, hiclks_hw, ARRAY_SIZE(hiclks_hw),
		CLK_MAX >> 2, &clk_ops_hi3798cv200);
}
CLK_OF_DECLARE(fixed_clock, "hi3798cv200.clock", hi3798cv200_clocks_init);
