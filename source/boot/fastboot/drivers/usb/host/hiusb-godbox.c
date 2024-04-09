#include <asm/io.h>
#include <common.h>

#define PERI_USB0               (0x10200000 + 0x28)
#  define WORDINTERFACE           (1 << 0)
#  define ULPI_BYPASS_EN          (1 << 3)
#  define SS_BURST4_EN            (1 << 7)
#  define SS_BURST8_EN            (1 << 8)
#  define SS_BURST16_EN           (1 << 9)

#define PERI_CRG36              (0x101F5000 + 0xd0)

#define PERI_USB3               (0x10200000 + 0x34)
#define USBPHY0_CLK_TEST        (1 << 24)
#define USBPHY1_CLK_TEST        (1 << 25)


/*****************************for Hi3716x***************************************/
#  define USB_CKEN                (1 << 8)
#  define USB_CTRL_UTMI1_REG      (1 << 6)
#  define USB_CTRL_UTMI0_REG      (1 << 5)
#  define USB_CTRL_HUB_REG        (1 << 4)
#  define USBPHY_PORT1_TREQ       (1 << 3)
#  define USBPHY_PORT0_TREQ       (1 << 2)
#  define USBPHY_REQ              (1 << 1)
#  define USB_AHB_SRST_REQ        (1 << 0)


int usb_cpu_init(int index, unsigned int *addr)
{
	int reg;
	int timeout;

	if (index != 0)
		return -1;

	if (addr)
#ifdef  CONFIG_USB_EHCI
		*addr = REG_BASE_EHCI;
#else
		*addr = REG_BASE_OHCI;
#endif

	reg = readl(PERI_CRG36);

	 if (!(reg & USBPHY_REQ))
		return 0;

	reg |= USB_CKEN;
	reg |= USBPHY_REQ;
	reg &= ~(USBPHY_PORT1_TREQ);
	reg &= ~(USBPHY_PORT0_TREQ);
	reg |= USB_CTRL_UTMI1_REG;
	reg |= USB_CTRL_UTMI0_REG;
	reg |= USB_AHB_SRST_REQ;
	writel(reg, PERI_CRG36);
	udelay(20);

	reg = readl(PERI_USB0);
	reg |= ULPI_BYPASS_EN;
	reg &= ~(WORDINTERFACE);
	reg &= ~(SS_BURST16_EN);
	writel(reg, PERI_USB0);
	udelay(100);

	reg = readl(PERI_CRG36);
	reg &= ~(USBPHY_REQ);
	writel(reg, PERI_CRG36);
	udelay(100);

	reg = readl(PERI_CRG36);
	reg &= ~( USB_CTRL_UTMI1_REG);
	reg &= ~(USB_CTRL_UTMI0_REG);
	reg &= ~(USB_CTRL_HUB_REG);
	reg &= ~(USB_AHB_SRST_REQ);
	writel(reg, PERI_CRG36);
	udelay(10);

	return 0;
}

int usb_cpu_stop(int index)
{
	return 0;
}

int usb_cpu_init_fail(void)
{
	usb_cpu_stop(0);
	return 0;
}
