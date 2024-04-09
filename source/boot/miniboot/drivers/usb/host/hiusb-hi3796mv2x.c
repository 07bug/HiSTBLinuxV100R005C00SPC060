#include <delay.h>
#include <asm/io.h>
#include <cpuinfo.h>

#define PERI_USB3                       (0xF8A20000 + 0x12c)
#define USB2_2P_SS_WORD_IF_I            (1 << 0)
#define USB2_2P_SS_ENA_INCR16_I         (1 << 9)
#define TEST_WRDATA                     (0xc)
#define TEST_ADDR                       (0x6 << 8)
#define TEST_WREN                       (1 << 13)
#define TEST_CLK                        (1 << 14)
#define TEST_RSTN                       (1 << 15)

#define PERI_CRG46                      (0xF8A22000 + 0xb8)
#define USB2_BUS_CKEN                   (1<<0)
#define USB2_OHCI48M_CKEN               (1<<1)
#define USB2_OHCI12M_CKEN               (1<<2)
#define USB2_OTG_UTMI_CKEN              (1<<3)
#define USB2_HST_PHY_CKEN               (1<<4)
#define USB2_UTMI0_CKEN                 (1<<5)
#define USB2_UTMI1_CKEN                 (1<<6)
#define USB2_PHY0_SRST_TREQ             (1<<8)
#define USB2_PHY1_SRST_TREQ             (1<<9)
#define USB2_BUS_SRST_REQ               (1<<12)
#define USB2_UTMI0_SRST_REQ             (1<<13)
#define USB2_UTMI1_SRST_REQ             (1<<14)
#define USB2_HST_PHY_SYST_REQ           (1<<16)
#define USB2_OTG_PHY_SYST_REQ           (1<<17)
#define USB2_CLK48_SEL                  (1<<20)

#define PERI_CRG47                      (0xF8A22000 + 0xbc)
#define USB2_PHY01_REF_CKEN              (1 << 0)
#define USB2_PHY2_REF_CKEN               (1 << 2)
#define USB2_PHY01_SRST_REQ              (1 << 4)
#define USB2_PHY2_SRST_REQ               (1 << 6)
#define USB2_PHY2_SRST_TREQ              (1 << 10)
#define USB2_PHY01_REFCLK_SEL            (1 << 12)
#define USB2_PHY2_REFCLK_SEL             (1 << 14)
#define USB2_PHY2_TEST_SRST_REQ          (1 << 15)
#define USB2_PHY01_TEST_SRST_REQ         (1 << 16)

#define USB2_PHY01_REGBASE               0xf9865000
#define USB2_1PORT_PHY_REGBASE           0xf9960000
/******************************************************************************/

static void inno_phy_config_1p_0(void)
{
	//eye diagram
	writel(0x6c, USB2_1PORT_PHY_REGBASE + 0x008);
	mdelay(2);
	//slew rate
	writel(0x1e, USB2_1PORT_PHY_REGBASE + 0x074);
	mdelay(2);
	//EOP pre-emph off
	writel(0x1c, USB2_1PORT_PHY_REGBASE + 0x000);
	mdelay(2);
	//disconnect =625
	writel(0xd7, USB2_1PORT_PHY_REGBASE + 0x010);
	mdelay(2);
	//second handshake
	writel(0x0e, USB2_1PORT_PHY_REGBASE + 0x07c);
	mdelay(2);
}

static void inno_phy_config_2p_1(void)
{
	writel(0x4, USB2_PHY01_REGBASE + 0x18);
	mdelay(2);

	//eye diagram
	writel(0x6c, USB2_PHY01_REGBASE + 0x408);
	mdelay(2);
	//slew rate
	writel(0x1e, USB2_PHY01_REGBASE + 0x474);
	mdelay(2);
	//EOP pre-emph off
	writel(0x1c, USB2_PHY01_REGBASE + 0x400);
	mdelay(2);
	//disconnect =625
	writel(0xd7, USB2_PHY01_REGBASE + 0x410);
	mdelay(2);
	//second handshake
	writel(0x0e, USB2_PHY01_REGBASE + 0x47c);
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
	reg = readl(PERI_CRG46);
	reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SYST_REQ);
	writel(reg, PERI_CRG46);
	udelay(200);

	/* reset phy por/utmi */
	reg = readl(PERI_CRG47);
	reg |= (USB2_PHY01_SRST_REQ
		| USB2_PHY2_SRST_REQ
		| USB2_PHY2_SRST_TREQ
		| USB2_PHY1_SRST_TREQ
		| USB2_PHY01_TEST_SRST_REQ
		| USB2_PHY2_TEST_SRST_REQ);
	writel(reg, PERI_CRG47);
	udelay(200);

	/* write default value. */
	reg = readl(PERI_USB3);
	reg &= ~(USB2_2P_SS_WORD_IF_I);      /* 8bit */
	reg &= ~(USB2_2P_SS_ENA_INCR16_I);      /* 16 bit burst disable */
	writel(reg, PERI_USB3);
	udelay(100);

	/* open ref clk */
	reg = readl(PERI_CRG47);
	reg |= (USB2_PHY01_REF_CKEN);
	writel(reg, PERI_CRG47);
	udelay(300);


	reg = readl(PERI_CRG47);
	reg &= ~(USB2_PHY01_TEST_SRST_REQ | USB2_PHY2_TEST_SRST_REQ);
	writel(reg, PERI_CRG47);
	udelay(200);

	/* cancel power on reset */
	reg = readl(PERI_CRG47);
	reg &= ~(USB2_PHY01_SRST_REQ | USB2_PHY2_SRST_REQ);
	writel(reg, PERI_CRG47);
	udelay(500);

	inno_phy_config_2p_1();
	inno_phy_config_1p_0();

	/* cancel port reset 
	 * delay 10ms for waiting comp circuit stable
	*/
	reg = readl(PERI_CRG47);
	reg &= ~(USB2_PHY1_SRST_TREQ | USB2_PHY2_SRST_TREQ);
	writel(reg, PERI_CRG47);
	udelay(300);

	/* open controller clk */
	reg = readl(PERI_CRG46);
	reg |= (USB2_BUS_CKEN
		| USB2_OHCI48M_CKEN
		| USB2_OHCI12M_CKEN
		| USB2_OTG_UTMI_CKEN
		| USB2_HST_PHY_CKEN
		| USB2_UTMI0_CKEN
		| USB2_UTMI1_CKEN);
	writel(reg, PERI_CRG46);
	udelay(200);

	/* cancel control reset */
	reg = readl(PERI_CRG46);
	reg &= ~(USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_HST_PHY_SYST_REQ
		| USB2_OTG_PHY_SYST_REQ);
	writel(reg, PERI_CRG46);
	udelay(200);

	return 0;
}
/******************************************************************************/

int usb_cpu_stop(int index)
{
	int reg;

	if (index != 0)
		return -1;

	reg = readl(PERI_CRG46);
	reg |= (USB2_BUS_SRST_REQ
		| USB2_UTMI0_SRST_REQ
		| USB2_UTMI1_SRST_REQ
		| USB2_HST_PHY_SYST_REQ);
	writel(reg, PERI_CRG46);

	udelay(200);

	reg = readl(PERI_CRG47);
	reg |= (USB2_PHY01_SRST_REQ
		| USB2_PHY0_SRST_TREQ
		| USB2_PHY1_SRST_TREQ);
	writel(reg, PERI_CRG47);

	udelay(100);

	return 0;
}
