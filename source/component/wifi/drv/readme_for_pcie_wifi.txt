���Լ����

./device/hisilicon/Hi3798MV200/BoardConfig.mk��ʹ�� WiFi+Bluetooth combo moduleʱ��
���±��뿪��ֻ׼��һ������Ϊy�������������Ϊn
# RTL8723BU
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8723BU := n
# RTL8822BU
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8822BU := n
# RTL8822BEH
BOARD_BLUETOOTH_WIFI_DEVICE_RTL8822BEH := n
# MT7662TU
BOARD_BLUETOOTH_WIFI_DEVICE_MT7662TU := n
# MT7662TE
BOARD_BLUETOOTH_WIFI_DEVICE_MT7662TE := y
# AP6356S
BOARD_BLUETOOTH_WIFI_DEVICE_AP6356S := n
# QCA6174
BOARD_BLUETOOTH_WIFI_DEVICE_QCA6174 := n

Ӳ��Լ����

1��boot��combo phy��ΪPCIE��������ΪUART

2������PCIE Reset�ܽ�ѡ���GPIO�ӿڣ��޸�.\device\hisilicon\bigfish\sdk\source\kernel\linux-3.18.y\drivers\hisilicon\clk\hi3798mv2x\clk-hipcie.c
   ��������õ�gpio��Ϊgpio4_3��ͬ��˼DMP������ͬ������Ҫ���ģ�

#ifdef TESTBOARD
        /* PCIe reset and release,use GPIO4_3 */
        if (!pcie_host0_regbase) {
                pcie_host0_regbase = ioremap_nocache(GPIO4_BASE + 0x400, 0x20);
                if (!pcie_host0_regbase) {
                        printk("ioremap xhci host0 failed.\n");
                        return -1;
                }
        }
        reg=readl(pcie_host0_regbase);
        reg |= 0x1<<3;
        writel(reg, pcie_host0_regbase);//Set GPIO4_3 to output mode
        mdelay(10);

        if (pcie_host0_regbase) {
                iounmap(pcie_host0_regbase);
                pcie_host0_regbase = NULL;
        }

        if (!pcie_host0_regbase) {
                pcie_host0_regbase = ioremap_nocache(GPIO4_BASE + 0x20, 0x20);
                if (!pcie_host0_regbase) {
                        printk("ioremap xhci host0 failed.\n");
                        return -1;
                }
        }

        writel(0x00, pcie_host0_regbase);//Set GPIO4_3 output low to reset PCIe EP
        mdelay(10);

        writel(0x08, pcie_host0_regbase);//Set GPIO4_3 output High to release reset
        mdelay(10);

        if (pcie_host0_regbase) {
                iounmap(pcie_host0_regbase);
                pcie_host0_regbase = NULL;
        }
#endif

3�������BT_EN�ܽ�ѡ���GPIO�ӿ��޸����GPIO�ӿڿ��ƴ���
   ����������õ�gpio��Ϊgpio5_4��ͬ��˼DMP������ͬ������Ҫ���ģ���

a��RTL8822BEH�޸����²��֣�

.\device\hisilicon\bigfish\bluetooth\rtkbt\rtk_rfkill\rtk_rfkill.c�����²��֣�

	bt_reset = of_get_gpio_flags(rtk119x_bt_node, 0, NULL); 	// get gpio number from device tree
	//����ѡ���GPIO���޸ģ�Ĭ��ʹ�õ�ΪGPIO5_4
	bt_reset = 44 ; //GPIO5_4 = 5*8+4 = 44

b��QCA6174�޸����²��֣�

.\device\hisilicon\bigfish\bluetooth\qca6174\libbtvendor\libbt-vendor\src\bt_vendor_qcom.c

#define QCA6174_BT_EN 5*8+4  //����ѡ���GPIO���޸ģ�Ĭ��ʹ�õ�ΪGPIO5_4

c��MT7662TE����Ҫ�޸�

4�����������ӵĴ��ںţ��޸Ĵ��ڽڵ㣨Ĭ��ttyAMA1��UART2��

a��RTL8822BEH�޸����²��֣�

//���ʹ��UART3���������ttyAMA1��ΪttyAMA2
.\device\hisilicon\bigfish\bluetooth\rtkbt\system\etc\bluetooth\uart\rtkbt.conf��
#Indicate USB or UART driver bluetooth
BtDeviceNode=/dev/ttyAMA1
\device\hisilicon\bigfish\bluetooth\qca6174\libbtvendor\libbt-vendor\include\vnd_generic.txt��
BLUETOOTH_UART_DEVICE_PORT = "/dev/ttyAMA1"

b��QCA6174�޸����²��֣�

//���ʹ��UART3���������ttyAMA1��ΪttyAMA2
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_uart.h:25:#define BLUETOOTH_UART_DEVICE_PORT "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_smd.h:30:#define APPS_RIVA_BT_ACL_CH  "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/hci_smd.h:31:#define APPS_RIVA_BT_CMD_CH  "/dev/ttyAMA1"
./device/hisilicon/bigfish/bluetooth/qca6174/libbtvendor/libbt-vendor/include/vnd_generic.txt:1:BLUETOOTH_UART_DEVICE_PORT = "/dev/ttyAMA1"

c��MT7662TE����ΪUSB�ӿڣ�����Ҫ�޸�

5���޸Ĵ���Ȩ�ޣ�

�޸������ļ���Ӧ���ڽڵ�Ȩ��
//���ʹ��UART3���������ttyAMA1��ΪttyAMA2
.\device\hisilicon\bigfish\etc\ueventd.bigfish.telecom.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack

.\device\hisilicon\bigfish\etc\ueventd.bigfish.default.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack

.\device\hisilicon\bigfish\etc\ueventd.bigfish.rc
#for UART Bluetooth
/dev/ttyAMA1 0660 bluetooth net_bt_stack
