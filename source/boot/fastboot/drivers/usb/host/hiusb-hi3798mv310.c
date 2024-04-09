#include <asm/io.h>
#include <common.h>

/******************************************************************************/
#define USB2_2P_SS_WORD_IF_I            (1<<0)
#define USB2_2P_SS_ENA_INCR16_I         (1<<9)
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

#define REG_PHY_CLK                    (0x18)
#define PHY_CLK_VALUE                  (0x5)

extern void udelay(unsigned long usec);

/******************************************************************************/

static void inno_phy_config(void)
{
	/* config phy clk output */
	writel(PHY_CLK_VALUE, REG_BASE_USB2_PHY01 + REG_PHY_CLK);

	/*HS eye height tuning 0x02[6:4]
	*3'b101:425mV
	*/
	writel(0x5c, REG_BASE_USB2_PHY01 + 0x08);
	writel(0x5c, REG_BASE_USB2_PHY01 + 0x408);
	udelay(20);

	/*pre-emphasis tuning 0x00[2:0]
	*3'b100:enable pre-emphasis in non-chirp state
	*/
	writel(0x1c, REG_BASE_USB2_PHY01 + 0x0);
	writel(0x1c, REG_BASE_USB2_PHY01 + 0x400);
	udelay(20);

	/*Tx HS pre_emphasize strength configure 0x05[4:2]
	*3'b001
	*/
	writel(0x84, REG_BASE_USB2_PHY01 + 0x14);
	writel(0x84, REG_BASE_USB2_PHY01 + 0x414);
	udelay(20);

	/*HOST disconnects detection trigger point 0x04[7:4]
	4'b1101:625mV
	*/
	writel(0xd7, REG_BASE_USB2_PHY01 + 0x10);
	writel(0xd7, REG_BASE_USB2_PHY01 + 0x410);
	udelay(20);

	/*HS chirp mode amplitude increasing register 0x1f[6]
	*1'b1
	*/
	writel(0x68, REG_BASE_USB2_PHY01 + 0x7c);
	writel(0x68, REG_BASE_USB2_PHY01 + 0x47c);
	udelay(20);

	/* config phy clk output */
	writel(PHY_CLK_VALUE, REG_BASE_USB2_PHY2 + REG_PHY_CLK);

	writel(0x5c, REG_BASE_USB2_PHY2 + 0x08);
	udelay(20);

	writel(0x1c, REG_BASE_USB2_PHY2 + 0x0);
	udelay(20);

	writel(0x84, REG_BASE_USB2_PHY2 + 0x14);
	udelay(20);

	writel(0xd7, REG_BASE_USB2_PHY2 + 0x10);
	udelay(20);

	writel(0xe8, REG_BASE_USB2_PHY2 + 0x7c);
	udelay(20);
}
/******************************************************************************/

int usb_cpu_init(int index, unsigned int *addr)
{
	int reg;

	if (index != 0)
		return -1;

	if (addr) {
#ifdef  CONFIG_USB_EHCI
		*addr = REG_BASE_EHCI;
#else
		*addr = REG_BASE_OHCI;
#endif
	}

	/* reset controller bus/utmi/roothub  */
	reg = readl(PERI_CRG46_USB2CTRL);
	reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_UTMI2_SRST_REQ
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SYST_REQ);
	writel(reg, PERI_CRG46_USB2CTRL);
	udelay(200);

	/* reset phy por/utmi */
	reg = readl(PERI_CRG47_USB2PHY);
	reg |= (USB2_PHY01_SRST_REQ
		| USB2_PHY01_SRST_TREQ0
		| USB2_PHY01_SRST_TREQ1
		| USB2_PHY2_SRST_REQ
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
	udelay(2000);

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
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SYST_REQ);
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
/******************************************************************************/

int usb_cpu_init_fail(void)
{
	return usb_cpu_stop(0);
}
