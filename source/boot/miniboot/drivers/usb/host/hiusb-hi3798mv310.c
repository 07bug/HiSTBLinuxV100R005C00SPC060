#include <delay.h>
#include <asm/io.h>
#include <cpuinfo.h>

#define USB2_BUS_CKEN                   (1<<0)
#define USB2_OHCI48M_CKEN               (1<<1)
#define USB2_OHCI12M_CKEN               (1<<2)
#define USB2_OTG_UTMI_CKEN              (1<<3)
#define USB2_HST_PHY_CKEN               (1<<4)
#define USB2_UTMI0_CKEN                 (1<<5)
#define USB2_UTMI1_CKEN                 (1<<6)
#define USB2_UTMI2_CKEN                 (1<<7)
#define USB2_BUS_SRST_REQ               (1<<12)
#define USB2_UTMI0_SRST_REQ             (1<<13)
#define USB2_UTMI1_SRST_REQ             (1<<14)
#define USB2_UTMI2_SRST_REQ             (1<<15)
#define USB2_HST_PHY_SYST_REQ           (1<<16)
#define USB2_OTG_PHY_SYST_REQ           (1<<17)
#define USB2_PHY01_CLK_SEL              (1<<19)


#define USB2_PHY01_REF_CKEN             (1 << 0)
#define USB2_PHY2_REF_CKEN              (1 << 2)
#define USB2_PHY01_SRST_REQ             (1 << 4)
#define USB2_PHY2_SRST_REQ              (1 << 6)
#define USB2_PHY01_SRST_TREQ0           (1 << 8)
#define USB2_PHY01_SRST_TREQ1           (1 << 9)
#define USB2_PHY2_SRST_TREQ             (1 << 10)
#define USB2_PHY01_REFCLK_SEL           (1 << 12)
#define USB2_PHY2_REFCLK_SEL            (1 << 14)
#define USB2_PHY01_TEST_SRST_REQ        (1 << 15)
#define USB2_PHY2_TEST_SRST_REQ         (1 << 16)


#define USB2_2P_SS_WORD_IF_I            (1 << 0)
#define USB2_2P_SS_ENA_INCR16_I         (1 << 9)

#define REG_PHY_CLK          (0x18)
#define PHY_CLK_VALUE        (0x5)

#define USB2_PORT1_REGBASE               (0x400)
/******************************************************************************/

static void inno_phy_config(void)
{

	/* config phy clk output */
	writel(PHY_CLK_VALUE, REG_BASE_USB2_PHY01 + REG_PHY_CLK);
	writel(PHY_CLK_VALUE, REG_BASE_USB2_PHY2 + REG_PHY_CLK);
	mdelay(2);
}
/******************************************************************************/

int usb_host_init(int index, unsigned int *addr)
{
	int reg;

	if (index != 0)
		return -1;

	if (addr) {
		*addr = REG_BASE_EHCI;
	}

	/* reset controller bus/utmi/roothub  */
	reg = readl(PERI_CRG46_USB2CTRL);
	reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ);
	writel(reg, PERI_CRG46_USB2CTRL);
	udelay(200);

	/* reset phy por/utmi */
	reg = readl(PERI_CRG47_USB2PHY);
	reg |= (USB2_PHY01_SRST_REQ
		| USB2_PHY2_SRST_REQ
		| USB2_PHY01_SRST_TREQ0
		| USB2_PHY01_SRST_TREQ1
		| USB2_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47_USB2PHY);
	udelay(200);

	/* 8bit/16 bit burst disable */
	reg = readl(PERI_USB3_UTMI);
	reg &= ~(USB2_2P_SS_WORD_IF_I);
	reg &= ~(USB2_2P_SS_ENA_INCR16_I);
	writel(reg, PERI_USB3_UTMI);
	udelay(100);


	/* open ref clk */
	reg = readl(PERI_CRG47_USB2PHY);
		reg |= (USB2_PHY01_REF_CKEN
		| USB2_PHY2_REF_CKEN);
	writel(reg, PERI_CRG47_USB2PHY);
	udelay(300);

	/* cancel power on reset */
	reg = readl(PERI_CRG47_USB2PHY);
		reg &= ~(USB2_PHY01_SRST_REQ
		| USB2_PHY2_SRST_REQ);
	writel(reg, PERI_CRG47_USB2PHY);
	udelay(500);

	reg = readl(PERI_CRG47_USB2PHY);
	reg &= ~(USB2_PHY01_TEST_SRST_REQ
		| USB2_PHY2_TEST_SRST_REQ);
	writel(reg, PERI_CRG47_USB2PHY);
	udelay(200);

	inno_phy_config();

	/* cancel port reset
	 * delay 10ms for waiting comp circuit stable
	*/
	reg = readl(PERI_CRG47_USB2PHY);
		reg &= ~(USB2_PHY01_SRST_TREQ0
		| USB2_PHY01_SRST_TREQ1
		| USB2_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47_USB2PHY);
	udelay(300);

	/* open controller clk */
	reg = readl(PERI_CRG46_USB2CTRL);
	reg |= (USB2_BUS_CKEN
		| USB2_OHCI48M_CKEN
		| USB2_OHCI12M_CKEN
		| USB2_OTG_UTMI_CKEN
		| USB2_HST_PHY_CKEN
		| USB2_UTMI0_CKEN
		| USB2_UTMI1_CKEN
		| USB2_UTMI2_CKEN);
	writel(reg, PERI_CRG46_USB2CTRL);
	udelay(200);

	/* cancel control reset */
	reg = readl(PERI_CRG46_USB2CTRL);
		reg &= ~(USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ);
	writel(reg, PERI_CRG46_USB2CTRL);
	udelay(200);

	return 0;
}
/******************************************************************************/

int usb_cpu_stop(int index)
{
	int reg;

	if (index != 0)
		return -1;

	reg = readl(PERI_CRG46_USB2CTRL);
		reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ);
	writel(reg, PERI_CRG46_USB2CTRL);

	udelay(200);

	reg = readl(PERI_CRG47_USB2PHY);
	reg |= (USB2_PHY01_SRST_REQ
		| USB2_PHY2_SRST_REQ
		| USB2_PHY01_SRST_TREQ1
		| USB2_PHY01_SRST_TREQ0
		| USB2_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47_USB2PHY);

	udelay(100);

	return 0;
}
