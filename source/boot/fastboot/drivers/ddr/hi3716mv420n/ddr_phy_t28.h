/**
 * ddr_phy_s40.h
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR PHY register offset address, mask, bit.
 */

/* register offset address */
/* base address: DDR_REG_BASE_PHY0 DDR_REG_BASE_PHY1 */
/* control the initialization of the PHY */
#define DDR_PHY_PHYINITCTRL	0x4
#define DDR_PHY_PHYINITSTATUS	0x8	/* Read Data Eye Calibration Error*/
#define DDR_PHY_DRAMCFG		0x2c    /* DRAM config register */
#define DDR_PHY_MODEREG01	0x64	/* Extend Mode Register 01 */
#define DDR_PHY_MODEREG23	0x68	/* Extend Mode Register 23 */
/* update delay setting in registers to PHY */
#define DDR_PHY_MISC		0x70
#define DDR_PHY_SWTMODE		0xa0	/* S/W training mode */
/* issue one DQS pulse from PHY to DRAM */
#define DDR_PHY_SWTWLDQS	0xa4
#define DDR_PHY_SWTRLT		0xa8	/* S/W training result*/
/* Host vref. [5:0]range [17:12]refsel */
#define DDR_PHY_IOCTL2		0xB4
#define DDR_PHY_DVRFTCTRL	0xC4    /* DRAM VREF Training */
/* AC command bit delay line setting */
#define DDR_PHY_ACCMDBDL2		0x1040
#define DDR_PHY_ACPHYCTL4	0x1064  /* AC block PHY control register*/
/* AC block PHY control register */
#define DDR_PHY_ACPHYCTL7		0x1070
/* WR DQ0-DQ3 [6:0] [14:8] [22:16] [30:24] delay value of the bit delay line
on write path */
#define DDR_PHY_DXNWDQNBDL0(n)	(0x210 + ((n) << 7))
/* WR DQ4-DQ7 [6:0] [14:8] [22:16] [30:24] */
#define DDR_PHY_DXNWDQNBDL1(n)	(0x214 + ((n) << 7))
/* WR DM [6:0] the delay value of the bit delay line on DQM */
#define DDR_PHY_DXNWDQNBDL2(n)	(0x218 + ((n) << 7))
/* RD DQ0-DQ3 [6:0] [14:8] [22:16] [30:24] delay value of the bit delay line
 on read path */
#define DDR_PHY_DXNRDQNBDL0(n)	(0x21C + ((n) << 7))
/* RD DQ4-DQ7 [6:0] [14:8] [22:16] [30:24] delay value of the bit delay line
 on read path */
#define DDR_PHY_DXNRDQNBDL1(n)	(0x220 + ((n) << 7))
/* [6:0]RD DM*/
#define DDR_PHY_DXNRDQNBDL2(n)	(0x224 + ((n) << 7))
/* [CUSTOM] */
#define DDR_PHY_DXNOEBDL(n)	(0x228 + ((n) << 7))
/* [8:0] rdqs_bdl [24:16]rdqs_cyc.
phase shift of the Read DQS to create 90 degree delays*/
#define DDR_PHY_DXNRDQSDLY(n)	(0x22C + ((n) << 7))
/* [6:0] the delay value of delay applied on WDQS for write leveling */
#define DDR_PHY_DXWDQSDLY(n)	(0x230 + ((n) << 7))
/* WR DQ phase BIT 12:8 */
#define DDR_PHY_DXNWDQDLY(n)	(0x234 + ((n) << 7))
/* [CUSTOM] rddqs gating*/
#define DDR_PHY_DXNRDQSGDLY(n)	(0x240 + ((n) << 7))
/* read boundary  right 8:0 left 24:16 */
#define DDR_PHY_DXNRDBOUND(n)	(0x250 + ((n) << 7))
/* write boundary  right 4:0 left 20:16 */
#define DDR_PHY_DXNWDBOUND(n)	(0x254 + ((n) << 7))
/* [5:0] DRAM VREF(DQ) training result */
#define DDR_PHY_DVREFT_STATUS(n)	(0x270 + ((n) << 7))
/* [4:0] Host PHY VREF(DQ) training result */
#define DDR_PHY_HVREFT_STATUS(n)	(0x274 + ((n) << 7))

/* register mask */
#define PHY_BDL_MASK			0x7f	/* [6:0] */
#define PHY_WDQS_PHASE_MASK		0xf
#define PHY_RDQS_BDL_MASK		0x1ff	/* [CUSTOM] [8:0] rdqsbdl*/
#define PHY_RDQSG_PHASE_MASK		0x3f	/* [14:9] rdqsgtxbdl */
/* hardware gate training result */
#define PHY_INITSTATUS_GT_MASK		0x20
#define PHY_SWTRLT_WL_MASK		0xf
#define PHY_SWTRLT_GATE_MASK	0xf
#define PHY_WDQ_PHASE_MASK		0x1f
#define PHY_PHYINITCTRL_MASK		0xffff	/* [15:0] all stat */
/* Read Data Eye Calibration Error */
#define PHY_PHYINITSTATUS_RDET_ERR	0x100
#define PHY_VRFTRES_DVREF_MASK	0x3f /* [5:0] */
#define PHY_VRFTRES_HVREF_MASK	0x1f /* [4:0] */

/* register bit */
#define PHY_MISC_UPDATE_BIT	19	/* [CUSTOM] delay config update bit */
#define PHY_PHYCONN_RST_BIT	15	/* issue reset signal to PHY counter */
#define PHY_RDQSG_PHASE_BIT	9	/* [CUSTOM] */
#define PHY_RDQSG_TX_BDL_BIT	16	/* [22:16] rdqsgtxbdl */
#define PHY_WDQS_PHASE_BIT	8
#define PHY_WDQ_PHASE_BIT	8
/* [22:16] Write DQS Output Enable Delay Control */
#define PHY_WDQSOE_BDL_BIT	16
/* Mode Register 1. Defines the MR3/MR9 of the mode register */
#define PHY_MODEREG01_MR1_BIT	16
/* Bit delay line setting of CS1 */
#define PHY_ACCMD_CS1_BIT		16
#define PHY_ACPHY_DCLK0_BIT		6	/* [8:6] cp1p_dclk0 */
#define PHY_ACPHY_DCLK1_BIT		9	/* [11:9] ck2p_dclk1 */
#define PHY_ACPHY_DRAMCLK0_BIT		25	/* [25] halft_dramclk0 */
#define PHY_ACPHY_DRAMCLK1_BIT		24	/* [24] halft_dramclk1 */
#define PHY_ACPHY_DRAMCLK_EXT_BIT	3 /* [3] halft_dramclk0 */
#define PHY_SWTMODE_SW_GTMODE_BIT	1 /* [1] SW gate training */

/* value */
#define PHY_PHYINITCTRL_DVREFT_SYNC	0x40000 /* DRAM VREF Synchronize */
/* Read Data Eye Training Enable. */
#define PHY_PHYINITCTRL_RDET_EN		0x100
#define PHY_PHYINITCTRL_DLYMEAS_EN	0x4	/* Delay Measurement Enable */
/* PHY Initialization Enable. */
#define PHY_PHYINITCTRL_INIT_EN		0x1
/* RDQS range[0, 0x7f], middle value is 0x40, but it affected by
   temperature, so middle value change to 0x30 */
#define PHY_RDQS_MIDDLE_VAL		0x30
/* DQ range[0, 0x7f],  middle value is 0x40, but it affected by
   temperature, so middle value change to 0x30 */
#define PHY_DQ_MIDDLE_VAL		0x30303030
#define PHY_MISC_SCRAMB_DIS		0xfffeffff	/* scrambler disable */
#define PHY_GATE_BDL_MAX        0xfe /* [6:0]rdqsg_bdl + [22:16]rdqsgtxbdl */
#define PHY_DVRFTCTRL_PDAEN_EN	0x80000000 /* pda enable */
/* [5] two cycle on address or command.(2T timing) */
#define PHY_DRAMCFG_MA2T		0x20

/* other */
#define PHY_RDQSG_PHASE_STEP		2       /* gate training phase step. */
#define PHY_GATE_PHASE_MARGIN		8       /* gate phase margin */
#define PHY_DQ_BDL_LEVEL		128     /* [CUSTOM] DQ BDL range */
#define PHY_DQ_BDL_MIDDLE		48 /* special middle DQ BDL value */
#define PHY_RDQSG_PHASE_MAX		0x3c    /* RDQSG phase max value */
#define PHY_ACPHY_CLK_MAX	0xf /* halft_dramclk0 + cp1p_dclk0 */
/**
 * DDR_BDL_PHASE_REL Calculation Method:
 * 1. Calculation How many picosecond to one phase.
 *    PICOSECOND : 1 second is (1000 * 1000 * 1000) picosecond
 *    WAVE       : 1 cycle is 2
 *    RATE       : DDR rate is 1600 Mbps, is (1600 * 1000) bps
 *    PHASE      : 1 wave is 12 phase
 *    phase = (((PICOSECOND * WAVE) / RATE) / PHASE)
 *          = (((1000 * 1000 * 1000 * 2) / (1600 * 1000)) / 12)
 *          = 104.17 ps.
 * 2. Calculation How many bdl to one phase.
 *    one BDL is 6 ps.
 *    result = phase/bdl = 104.17 / 6 = 17.36 approximately equal to 17 ~= 16
 * 3. 16 = 1 << 4, so the relation is 4.
 */
#ifndef DDR_BDL_PHASE_TRANSFORM
/* [CUSTOM] one Phase equal how much BDL. 1 phase = 16 bdl */
#define DDR_BDL_PHASE_TRANSFORM		16
#endif
#ifndef DDR_BDL_PHASE_REL
/* [CUSTOM] relation between BDL and Phase. 1 phase = 16 bdl, 16 = 1 << 4 */
#define DDR_BDL_PHASE_REL		4
#endif

/* PHY t28 all byte use a same value */
#define DDR_PHY_VREF_HOST_SET(base_phy, val, bytenum) \
	do { \
		int i = 0; \
		unsigned int hvreft; \
		for (i = 0; i < bytenum; i++) { \
			hvreft = REG_READ(base_phy + DDR_PHY_HVREFT_STATUS(i)) \
				& (~PHY_VRFTRES_HVREF_MASK); \
			REG_WRITE(hvreft | val, \
			base_phy + DDR_PHY_HVREFT_STATUS(i)); \
		} \
	} while (0)

#define DDR_PHY_VREF_HOST_GET(base_phy, val) \
	{ \
		val = REG_READ(base_phy + DDR_PHY_HVREFT_STATUS(0)) \
			& PHY_VRFTRES_HVREF_MASK; \
	}

#define DDR_PHY_VREF_HOST_DISPLAY(base_phy, ddr_reg, index, byte_num) \
	do { \
		for (i = 0; i < byte_num; i++) { \
			snprintf(ddr_reg->reg[index].name, DDR_REG_NAME_MAX, \
				"Host Vref Byte%d", i); \
			ddr_reg->reg[index++].addr = \
				base_phy + DDR_PHY_HVREFT_STATUS(i); \
		} \
	} while (0)

#define DDR_PHY_VREF_HOST_DISPLAY_CMD(base_phy, byte_num) \
	do { \
		for (i = 0; i < byte_num; i++) { \
			DDR_INFO("[%x = %x] Host Vref Byte(%x)", \
				base_phy + DDR_PHY_HVREFT_STATUS(i), \
				REG_READ(base_phy \
				+ DDR_PHY_HVREFT_STATUS(i)), i); \
		} \
	} while (0)

/* DRAM vref operations */
#define DDR_PHY_VREF_DRAM_SET(base_phy, val, byte_index) \
	do { \
		unsigned int dvrftctrl = \
			REG_READ(base_phy + DDR_PHY_DVRFTCTRL); \
		unsigned int dvreft = REG_READ(base_phy \
			+ DDR_PHY_DVREFT_STATUS(byte_index)) \
			& (~PHY_VRFTRES_DVREF_MASK); \
		REG_WRITE(dvrftctrl | PHY_DVRFTCTRL_PDAEN_EN, \
			base_phy + DDR_PHY_DVRFTCTRL); \
		REG_WRITE(dvreft | val, \
			base_phy + DDR_PHY_DVREFT_STATUS(byte_index)); \
		REG_WRITE(PHY_PHYINITCTRL_DVREFT_SYNC \
			| PHY_PHYINITCTRL_INIT_EN, \
			base_phy + DDR_PHY_PHYINITCTRL); \
		while (1) { \
			if (!(REG_READ(base_phy + DDR_PHY_PHYINITCTRL) \
				& PHY_PHYINITCTRL_INIT_EN)) \
				break; \
		} \
		REG_WRITE(dvrftctrl & (~PHY_DVRFTCTRL_PDAEN_EN), \
			base_phy + DDR_PHY_DVRFTCTRL); \
	} while (0)

#define DDR_PHY_VREF_DRAM_GET(base_phy, val, byte_index) \
	{ \
		val = REG_READ(base_phy + DDR_PHY_DVREFT_STATUS(byte_index)) \
			& PHY_VRFTRES_DVREF_MASK; \
	}

#define DDR_PHY_VREF_DRAM_DISPLAY(base_phy, ddr_reg, index, byte_num) \
	do { \
		for (i = 0; i < byte_num; i++) { \
			snprintf(ddr_reg->reg[index].name, DDR_REG_NAME_MAX, \
				"DRAM Vref Byte%d", i); \
			ddr_reg->reg[index++].addr = \
				base_phy + DDR_PHY_DVREFT_STATUS(i); \
		} \
	} while (0)

#define DDR_PHY_VREF_DRAM_DISPLAY_CMD(base_phy, byte_num) \
	do { \
		for (i = 0; i < byte_num; i++) { \
			DDR_INFO("[%x = %x] DRAM Vref Byte(%x)", \
				base_phy + DDR_PHY_DVREFT_STATUS(i), \
				REG_READ(base_phy \
				+ DDR_PHY_DVREFT_STATUS(i)), i); \
		} \
	} while (0)
