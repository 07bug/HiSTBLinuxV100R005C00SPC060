------------------------ע������------------------------------------------------------------------------------------------------------

1.���BoardConfig.mk��ѡ�б���RTL8822BS����MT7668BS������������϶�Ӧģ�顣

2.RTL8822BS��SDIO1,98MV300���壬������SDIO1ʱ��180MHz;MT7668BS��SDIO1,98MV300���壬������SDIO1ʱ��200MHz

----------------------�޸Ŀ�ʼ----------------------------------------------------------------------------------------
RTL8822BS & MT7668BS WiFi��BT���������Ӳ����ƽ��п��ƻ��޸ģ������޸ĵ����£�

WiFi���ܣ�

RTL8822BS & 7668BS ��OOBģʽ��Ĭ��ģʽ����

�ļ�1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//����Ӳ�����ʹ�õ�WL_EN GPIO�ܽźţ��޸Ķ�Ӧ������BOARD_GPIO_WL_EN���汾��98MV300Ĭ��ΪGPIO4_3(4*8+3=35=0x23)
BOARD_SDIO_WIFI_SUPPORT := y
BOARD_GPIO_WL_EN=0x23

�ļ�2 device/hisilicon/bigfish/bluetooth/sdio_detect/hi_sdio_detect.c

//����Ӳ�����ʹ�õ�WL_EN GPIO�ܽź��޸ģ��汾��Ĭ��ΪGPIO4_3(4*8+3)
 #define RTL_REG_ON_GPIO     (4*8 + 3)

//����Ӳ�����ѡ�õ�SDIO���޸ģ��汾��Ĭ��ΪSDIO1��
//���ʹ��SDIO0�����޸�����ע�Ͳ��֣�0x1��Ϊ0x2
 int hisi_wlan_set_carddetect(bool present)
{
        u32 regval;

        if (present) {
                printk("======== Card detection to detect SDIO card! ========\n");
                /*set card_detect low to detect card*/
                regval = readl(REG_BASE_CTRL);
                regval |= 0x1;//���ʹ��SDIO0����Ϊ0x2
                writel(regval, REG_BASE_CTRL);
        }
        else {
                printk("======== Card detection to remove SDIO card! ========\n");
                 /*set card_detect high to remove card*/
                regval = readl(REG_BASE_CTRL);
                regval &= ~(0x1);//���ʹ��SDIO0����Ϊ0x2
                writel(regval, REG_BASE_CTRL);
        }
}

RTL8822BS OOBģʽ��MT7668BS��OOBģʽ����

�ļ�1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//����Ӳ�����ʹ�õ�WL_EN GPIO�ܽźţ��޸Ķ�Ӧ������BOARD_GPIO_WL_EN���汾��98MV300Ĭ��ΪGPIO4_3(4*8+3=35=0x23)
BOARD_SDIO_WIFI_SUPPORT := y
BOARD_GPIO_WL_EN=0x23

�ļ�2 device/hisilicon/bigfish/sdk/source/component/wifi/drv/sdio_rtl8822bs/Makefile

OOBģʽӦ��Ϊ���£�
#obj-y += rtl88x2BS_WiFi_linux_v5.2.21.2_27038.20180312_COEX20180112-5959/
#obj-y += rtl88x2BS_WiFi_linux_v5.1.7.2_23461.20170804_COEX20170619-4141/
obj-y += rtl88x2BS_WiFi_linux_v5.1.7.4_24893.20171108_COEX20170619-4141_beta_hs_oob_v2/

�ļ�3 device/hisilicon/bigfish/bluetooth/sdio_detect/hi_sdio_detect.c

//����Ӳ�����ʹ�õ�WL_EN GPIO�ܽź��޸ģ��汾��Ĭ��ΪGPIO4_3(4*8+3)
#define RTL_REG_ON_GPIO         (4*8 + 3)

//����Ӳ�����ѡ�õ�SDIO���޸ģ��汾��Ĭ��ΪSDIO1��
//���ʹ��SDIO0�����޸�����ע�Ͳ��֣�0x1��Ϊ0x2.ͬʱ��ע��:�ƶ�������Ҫ��SDIO0_CARD_DETECT��ΪGPIO����
static int hisi_wlan_set_carddetect(bool present)
{
        u32 regval;

        if (present) {
                pr_info("======== Card detection to detect SDIO card! ========\n");
                /* set card_detect low to detect card */
                regval = readl(REG_BASE_CTRL);
                regval |= 0x1; //���ʹ��SDIO0����Ϊ0x2
                writel(regval, REG_BASE_CTRL);
        } else {
                pr_info("======== Card detection to remove SDIO card! ========\n");
                /* set card_detect high to remove card */
                regval = readl(REG_BASE_CTRL);
                regval &= ~(0x1);//���ʹ��SDIO0����Ϊ0x2
                writel(regval, REG_BASE_CTRL);
        }

        return 0;
}

�ļ�3 device/hisilicon/bigfish/sdk/source/component/wifi/drv/sdio_rtl8822bs/rtl88x2BS_WiFi_linux_v5.1.7.4_24893.20171108_COEX20170619-4141_beta_hs_oob_v2/Makefile

//����Ӳ�����ʹ�õ�OOB GPIO�ܽź��޸ģ��汾��Ĭ��ΪGPIO3_5(3*8+5=29)
EXTRA_CFLAGS += -DRTL_OOB_INT_GPIO=29

�������ܣ�

RTL8822BS��

�ļ�1 device/hisilicon/bigfish/bluetooth/realtek8xxx/rtk_rfkill/rtk_rfkill.c

//����Ӳ�����ʹ�õ�BT_EN GPIO�ܽź��޸ģ��汾��Ĭ��ΪGPIO4_2(4*8+2=34)
bt_reset = 34 ; //GPIO4_2 = 4*8+2 = 34

�ļ�2 device/hisilicon/Hi3798MV300/BoardConfig.mk

//����Ӳ�����ʹ�õ�BT_WAKE_HOST GPIO�ܽź��޸ģ��汾��98MV300Ĭ��ΪGPIO5_3(5*8+3=43=0x2b)
ifeq ($(BOARD_GPIO_BT_NUM),y)
BOARD_GPIO_BLUETOOTH_SUSPEND := 0x2b
endif

MT7668BS��

�ļ�1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//����Ӳ�����ʹ�õ�BT_WAKE_HOST GPIO�ܽź��޸ģ��汾��98MV300Ĭ��ΪGPIO5_3(5*8+3=43=0x2b)
ifeq ($(BOARD_GPIO_BT_NUM),y)
BOARD_GPIO_BLUETOOTH_SUSPEND := 0x2b
endif

�ļ�2 device/hisilicon/bigfish/bluetooth/Android.mk

//���MT7668BS����Э��ջ��˽���޸ģ��뽫Android.mk��MT7668BS����Э��ջ�򿪱��룬���������ɵ�Э��ջ�⿽����device/hisilicon/bigfish/bluetooth/mt7668bs/bluedroid-lib��
//Ӧ��Ϊ���£�
ifeq ($(BOARD_BLUETOOTH_WIFI_DEVICE_MT7668BS),y)
include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/lib/Android.mk
#include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/bluedroid-lib/Android.mk
#include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/bluedroid-conf/Android.mk
endif


------------------------�޸Ľ���------------------------------------------------------------------------------------------------------

------------------------�������ⶨΪ����----------------------------------------------------------------------------------------------

1���ƶ�����WiFi����SDIO1�ڣ���WiFiʱ�޷�ʶ��SDIO�豸

�鿴SDIO0_CARD_DETECT�Ƿ���ΪGPIO�����û�У���SDIO0_CARD_DETECT����ΪGPIO

2��WiFi���ܵ�

�������·���ȷ��SDIO INTģʽ��ʱ��Ƶ�������Ƿ���ȷ��

���ʹ��SDIO0��WiFi��ȷ�����²��֣�

�ļ�1 device/hisilicon/bigfish/sdk/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv200.dts

                sd:himciv200.SD@0xf9820000 {
                        compatible = "hi3798mv200,himciv200";
                        reg = <0xf9820000 0x1000>,<0xF8A210C0 0x40>;
                        interrupts = <0 34 4>;

                        clocks = <&hisilicon_clock PERI_CRG39_SDIO0>;
                        clock-names = "clk";

                        ldo-addr  = <0xf8a2011c>;
                        ldo-shift = <0>;

                        caps = <0x8007000f>;//0x8007000f ��ӦINTģʽ��������ǣ�����Ϊ0x8007000f
                        caps2 = <0x4000>;
                        max-frequency = <50000000>;
                        status = "okay";
                };

���ʹ��SDIO1��WiFi��ȷ�����²���

�ļ�1 device/hisilicon/bigfish/sdk/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv200.dts

                sdio:himciv200.SD@0xf9c40000 {
                        compatible = "hi3798mv200,himciv200";
                        reg = <0xf9c40000 0x1000>,<0xF8A21090 0x20>,<0xF8A20008 0x20>;
                        interrupts = <0 86 4>;

                        clocks = <&hisilicon_clock PERI_CRG163_SDIO2>;
                        clock-names = "clk";

                        caps = <0x8007000f>;//0x8007000f ��ӦINTģʽ��������ǣ�����Ϊ0x8007000f
                        caps2 = <0x4000>;
                        max-frequency = <50000000>;
                        status = "okay";
                };

ȷ��SDIOʱ��Ƶ�ʣ�

����һ��
    ʹ��ʾ��������SDIO_CLK�ܽ�

������;
    ʹ��himm���߶�ȡ0xf8a2203c�Ĵ�����ֵ

    SDIO0:
    ������β��Ϊ20B4����SDIO0ʱ��Ƶ��Ϊ135MHz
    ������β��Ϊ20C8����SDIO0ʱ��Ƶ��Ϊ150MHz

    SDIO1:
    ������β��Ϊ20B4����SDIO1ʱ��Ƶ��Ϊ180MHz
    ������β��Ϊ20C8����SDIO1ʱ��Ƶ��Ϊ200MHz