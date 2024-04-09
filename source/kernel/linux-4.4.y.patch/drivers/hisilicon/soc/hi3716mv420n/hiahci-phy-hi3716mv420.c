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
 * Create By Cai Zhiyong 2015.6.17
 *
******************************************************************************/

#define DRVNAME    "hiahci-phy-hi3716mv420"
#define pr_fmt(fmt) DRVNAME ": " fmt

#include <linux/io.h>
#include <linux/mfd/syscon.h>
#include <linux/module.h>
#include <linux/phy/phy.h>
#include <linux/platform_device.h>

#include <linux/delay.h>

#define HISATA_DEBUG        0
#define hisata_read(addr)  ({ \
	unsigned int reg = readl(addr); \
	if (HISATA_DEBUG) { \
		pr_info("readl(0x%08X) = 0x%08X\n", (unsigned int)addr, reg); \
	} \
	reg; \
})

#define hisata_write(v, addr)  do { \
	writel(v, addr); \
	msleep(10); \
	if (HISATA_DEBUG) { \
		pr_info("writel(0x%08X) = 0x%08X\n", (unsigned int)addr, v); \
	} \
} while (0)

#define HI_SATA_PORT0_OFF          0x100
#define SATA_PORT_PHYCTL1          0x48
/* 00 PCIE,01 USB3.0,10 SATA */
#define PCIE_USB3_SATA3_SEL        (BIT(12) | BIT(11))

#define PERI_COMBPHY1_CFG          0x858
#define NANO_BYPASS_CODEC          (0x1<<31)
#define NANO_BUFFER_MODE           (0x3<<28)
#define NANO_TEST_WRITE            (0x1<<24)
#define NANO_TEST_DATA             (0xf<<20)
#define NANO_TEST_ADDR             (0x1f<<12)
#define NANO_RX_STANDBY            (0x1<<11)
#define NANO_TX_PATTERN            (0x3<<2)
#define CLKREF_OUT_OEN             (0x1<<0)

#define PERI_COMBPHY1_STATE        0x85C
#define NANO_TEST_O                (0xf<<8)
#define NANO_DATA_BUS_WIDTH        (0x3<<4)
#define NANO_RX_DATA_VALID         (0x1<<2)
#define NANO_RX_STANDBY_STATUS     (0x1<<1)
#define NANO_ALIGN_DETECT          (0x1<<0)

/******************************************************************************/

struct hiahci_phy_priv {
	void __iomem *iobase;
	void __iomem *peri_ctrl_base;
};
/******************************************************************************/
#if 0
static u32 nano_reg_read(struct hiahci_phy_priv *priv, u32 nano_testread_addr)
{
	unsigned int tmp_val;

	tmp_val = hisata_read(priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
	tmp_val &= ~NANO_TEST_WRITE;
	tmp_val &= ~NANO_TEST_ADDR;
	tmp_val |= (nano_testread_addr << 12);
	hisata_write(tmp_val, priv->peri_ctrl_base + PERI_COMBPHY1_CFG);

	tmp_val = hisata_read(priv->peri_ctrl_base + PERI_COMBPHY1_STATE);
	tmp_val = (tmp_val&NANO_TEST_O) >> 8;
	if (HISATA_DEBUG)
		pr_info("Nano ComboPHY read:addr(%#x),value(%#x)\n", nano_testread_addr, tmp_val);

	return tmp_val;
}
#endif
/******************************************************************************/

static void nano_reg_write(struct hiahci_phy_priv *priv, u32 nano_testwrite_addr, u32 nano_testwrite_value)
{
	unsigned int tmp_val;

	tmp_val = hisata_read(priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
	tmp_val &= ~NANO_TEST_ADDR;
	tmp_val &= ~NANO_TEST_DATA;
	tmp_val |= (nano_testwrite_addr << 12);
	tmp_val |= (nano_testwrite_value << 20);
	hisata_write(tmp_val, priv->peri_ctrl_base + PERI_COMBPHY1_CFG);

	tmp_val = readl(priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
	tmp_val |= NANO_TEST_WRITE;
	hisata_write(tmp_val, priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
	if (HISATA_DEBUG)
		pr_info("Nano ComboPHY write:addr(%#x),value(%#x)\n", nano_testwrite_addr, nano_testwrite_value);

	tmp_val = hisata_read(priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
	tmp_val &= ~NANO_TEST_WRITE;
	hisata_write(tmp_val, priv->peri_ctrl_base + PERI_COMBPHY1_CFG);
}
/******************************************************************************/

static void nano_tx_margin_sata(struct hiahci_phy_priv *priv, u32 margin_value)
{
	unsigned int val;

	val = hisata_read(priv->iobase + HI_SATA_PORT0_OFF + SATA_PORT_PHYCTL1);
	val &= ~(0x3 << 4);
	val |= (margin_value << 4);
	hisata_write(val, priv->iobase + HI_SATA_PORT0_OFF + SATA_PORT_PHYCTL1);
}
/******************************************************************************/

static void nano_tx_deemp_sata(struct hiahci_phy_priv *priv, u32 deemp_value)
{
	unsigned int val;

	val = hisata_read(priv->iobase + HI_SATA_PORT0_OFF + SATA_PORT_PHYCTL1);
	val &= ~(0x3 << 2);
	val |= (deemp_value << 2);
	hisata_write(val, priv->iobase + HI_SATA_PORT0_OFF + SATA_PORT_PHYCTL1);
}
/******************************************************************************/

static int hiahci_phy_init(struct phy *phy)
{
	unsigned int val;
	struct hiahci_phy_priv *priv = phy_get_drvdata(phy);

	/* Config ComboPHY to SATA Mode */
	val = hisata_read(priv->peri_ctrl_base + 0x8);
	val &= ~(PCIE_USB3_SATA3_SEL);
	val |= 0x2<<11;
	hisata_write(val, priv->peri_ctrl_base + 0x8);

	/* Config Nano De-emphasis */
	nano_tx_deemp_sata(priv, 0x2); /* 0x0,-6dB;0x1,-3.5dB;0x2,0dB;0x3,-5.5dB */
	nano_tx_margin_sata(priv, 0x1);/* 0x0,1000mV;0x1,1100mV;0x2,900mV;0x3,700mV;0x4,600mV;0x5,500mV;0x6,400mV;0x7,300mV */

	/* Nano PHY Internal Config */
	/* SSC On,SSC Reduce */
	nano_reg_write(priv, 0x2, 0x4);/* 0 to -4500ppm */

	/* TXPLL_TRIM_LBW 2'b01 */
	nano_reg_write(priv, 0xd, 0x1);

	/* Data invert between phy and sata controller */
	hisata_write(0x8, priv->iobase+0xA4);

	/* Config Spin-up */
	hisata_write(0x600000, priv->iobase + HI_SATA_PORT0_OFF + 0x18);
	hisata_write(0x600002, priv->iobase + HI_SATA_PORT0_OFF + 0x18);

	/* Config SATA Port0 phy controller */
	hisata_write(0xE400000, priv->iobase + HI_SATA_PORT0_OFF + 0x74);/* 6Gbps */

	return 0;
}
/******************************************************************************/

static int hiahci_phy_power_on(struct phy *phy)
{
	u32 regval;
	struct hiahci_phy_priv *priv = phy_get_drvdata(phy);

	/* Power on SATA disk */
	regval = readl(priv->peri_ctrl_base + 0x08);
	regval |= BIT(10);
	writel(regval, priv->peri_ctrl_base + 0x08);

	return 0;
}
/******************************************************************************/

static int hiahci_phy_power_off(struct phy *phy)
{
	u32 regval;
	struct hiahci_phy_priv *priv = phy_get_drvdata(phy);

	/* Power off SATA disk */
	regval = readl(priv->peri_ctrl_base + 0x08);
	regval &= ~BIT(10);
	writel(regval, priv->peri_ctrl_base + 0x08);

	return 0;
}
/******************************************************************************/

static struct phy_ops hiahci_phy_ops = {
	.init = hiahci_phy_init,
	.power_on = hiahci_phy_power_on,
	.power_off = hiahci_phy_power_off,
	.owner = THIS_MODULE,
};
/******************************************************************************/
static struct phy *phy_hisi_sata_phy_xlate(struct device *dev,
					     struct of_phandle_args *args)
{
	struct phy *phy = dev_get_drvdata(dev);

	if (NULL == phy || IS_ERR(phy))
		return ERR_PTR(-ENODEV);

	return phy;
}
/******************************************************************************/
static int hiahci_phy_probe(struct platform_device *pdev)
{
	struct phy *phy;
	struct resource *res;
	struct phy_provider *phy_provider;
	struct hiahci_phy_priv *priv;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->iobase = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (IS_ERR_OR_NULL(priv->iobase)) {
		pr_err("%s: iobase ioremap fail.\n", __func__);
		return PTR_ERR(priv->iobase);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->peri_ctrl_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if (IS_ERR_OR_NULL(priv->peri_ctrl_base)) {
		pr_err("%s: peri_ctrl_base ioremap fail.\n", __func__);
		return PTR_ERR(priv->peri_ctrl_base);
	}

	phy = devm_phy_create(&pdev->dev, NULL, &hiahci_phy_ops);
	if (IS_ERR_OR_NULL(phy)) {
		pr_err("failed to create PHY, %ld\n", PTR_ERR(phy));
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, priv);
	dev_set_drvdata(&pdev->dev, phy);
	phy_provider = devm_of_phy_provider_register(&pdev->dev,
		phy_hisi_sata_phy_xlate);
	if (IS_ERR_OR_NULL(phy_provider)) {
		pr_err("failed to register phy provider, %ld\n", PTR_ERR(phy_provider));
		return PTR_ERR(phy_provider);
	}

	return 0;
}
/******************************************************************************/

static const struct of_device_id hiahci_phy_of_match[] = {
	{.compatible = "hi3716mv420.hiahci-phy",},
	{ },
};
MODULE_DEVICE_TABLE(of, hiahci_phy_of_match);

static struct platform_driver hiahci_phy_driver = {
	.probe  = hiahci_phy_probe,
	.driver = {
		.name = DRVNAME,
		.of_match_table = hiahci_phy_of_match,
	}
};
/*****************************************************************************/

static int __init hiahci_phy_module_init(void)
{
	pr_info("registered new sata phy driver\n");
	return platform_driver_register(&hiahci_phy_driver);
}
module_init(hiahci_phy_module_init);
/*****************************************************************************/

static void __exit hiahci_phy_module_exit(void)
{
	platform_driver_unregister(&hiahci_phy_driver);
}
module_exit(hiahci_phy_module_exit);

MODULE_AUTHOR("Cai Zhiyong");
MODULE_DESCRIPTION("Hisilicon hi3716mv420 sata phy driver");
MODULE_LICENSE("GPL v2");
