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
#define USB2_PORT1_REGBASE               0x400
/******************************************************************************/

static void inno_phy_config_2p(void)
{
	u64 chipid = get_chipid();

	if (_HI3798M_V200 == chipid) {
		asm volatile ("dsb");
		mdelay(2);
		writel(0x4, USB2_PHY01_REGBASE + 0x18);
		asm volatile ("dsb");
		mdelay(2);

		writel(0x1c, USB2_PHY01_REGBASE);
		asm volatile ("dsb");
		udelay(20);
		writel(0x14, USB2_PHY01_REGBASE + 0x78);
		asm volatile ("dsb");
		udelay(20);
		writel(0x1b, USB2_PHY01_REGBASE + 0x28);
		asm volatile ("dsb");
		udelay(20);
		writel(0x7, USB2_PHY01_REGBASE + 0x18);
		asm volatile ("dsb");
		udelay(20);
		writel(0x92, USB2_PHY01_REGBASE + 0x14);
		asm volatile ("dsb");
		udelay(20);

		writel(0x1c, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE);
		asm volatile ("dsb");
		udelay(20);
		writel(0x1b, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE + 0x28);
		asm volatile ("dsb");
		udelay(20);
	}else if (_HI3798M_V300 == chipid) {
		mdelay(2);
		writel(0x4, USB2_PHY01_REGBASE + 0x18);
		mdelay(2);
		
		/* eye height 450mv */
		writel(0x6c, USB2_PHY01_REGBASE + 0x08);
		writel(0x6c, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE + 0x08);
		mdelay(2);

		/* pre-emphasis */
		writel(0x18, USB2_PHY01_REGBASE);
		writel(0x18, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE);
		udelay(20);

		/* disconnects detection trigger 562.5mv */
		writel(0xd7, USB2_PHY01_REGBASE + 0x10);
		writel(0xd7, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE + 0x10);
		udelay(20);

		/* HS driver slew rate tunning */
		writel(0x1e, USB2_PHY01_REGBASE + 0x74);
		writel(0x1e, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE + 0x74);
		udelay(20);

		/* Second handshake */
		writel(0x6e, USB2_PHY01_REGBASE + 0x7c);
		writel(0x6e, USB2_PHY01_REGBASE + USB2_PORT1_REGBASE + 0x7c);
		udelay(20);
	}
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
		| USB2_PHY0_SRST_TREQ
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
	reg &= ~(USB2_PHY01_SRST_REQ);
	writel(reg, PERI_CRG47);
	udelay(500);

	inno_phy_config_2p();

	/* cancel port reset 
	 * delay 10ms for waiting comp circuit stable
	*/
	reg = readl(PERI_CRG47);
	reg &= ~(USB2_PHY0_SRST_TREQ | USB2_PHY1_SRST_TREQ);
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
