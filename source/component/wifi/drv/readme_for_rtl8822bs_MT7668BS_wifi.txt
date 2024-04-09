------------------------注意事项------------------------------------------------------------------------------------------------------

1.如果BoardConfig.mk中选中编译RTL8822BS或者MT7668BS，单板务必贴上对应模组。

2.RTL8822BS，SDIO1,98MV300单板，请配置SDIO1时钟180MHz;MT7668BS，SDIO1,98MV300单板，请配置SDIO1时钟200MHz

----------------------修改开始----------------------------------------------------------------------------------------
RTL8822BS & MT7668BS WiFi和BT功能请根据硬件设计进行客制化修改，具体修改点如下：

WiFi功能：

RTL8822BS & 7668BS 非OOB模式（默认模式）：

文件1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//根据硬件设计使用的WL_EN GPIO管脚号，修改对应器件的BOARD_GPIO_WL_EN，版本中98MV300默认为GPIO4_3(4*8+3=35=0x23)
BOARD_SDIO_WIFI_SUPPORT := y
BOARD_GPIO_WL_EN=0x23

文件2 device/hisilicon/bigfish/bluetooth/sdio_detect/hi_sdio_detect.c

//根据硬件设计使用的WL_EN GPIO管脚号修改，版本中默认为GPIO4_3(4*8+3)
 #define RTL_REG_ON_GPIO     (4*8 + 3)

//根据硬件设计选用的SDIO口修改，版本中默认为SDIO1，
//如果使用SDIO0，需修改如下注释部分，0x1改为0x2
 int hisi_wlan_set_carddetect(bool present)
{
        u32 regval;

        if (present) {
                printk("======== Card detection to detect SDIO card! ========\n");
                /*set card_detect low to detect card*/
                regval = readl(REG_BASE_CTRL);
                regval |= 0x1;//如果使用SDIO0，改为0x2
                writel(regval, REG_BASE_CTRL);
        }
        else {
                printk("======== Card detection to remove SDIO card! ========\n");
                 /*set card_detect high to remove card*/
                regval = readl(REG_BASE_CTRL);
                regval &= ~(0x1);//如果使用SDIO0，改为0x2
                writel(regval, REG_BASE_CTRL);
        }
}

RTL8822BS OOB模式（MT7668BS无OOB模式）：

文件1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//根据硬件设计使用的WL_EN GPIO管脚号，修改对应器件的BOARD_GPIO_WL_EN，版本中98MV300默认为GPIO4_3(4*8+3=35=0x23)
BOARD_SDIO_WIFI_SUPPORT := y
BOARD_GPIO_WL_EN=0x23

文件2 device/hisilicon/bigfish/sdk/source/component/wifi/drv/sdio_rtl8822bs/Makefile

OOB模式应改为如下：
#obj-y += rtl88x2BS_WiFi_linux_v5.2.21.2_27038.20180312_COEX20180112-5959/
#obj-y += rtl88x2BS_WiFi_linux_v5.1.7.2_23461.20170804_COEX20170619-4141/
obj-y += rtl88x2BS_WiFi_linux_v5.1.7.4_24893.20171108_COEX20170619-4141_beta_hs_oob_v2/

文件3 device/hisilicon/bigfish/bluetooth/sdio_detect/hi_sdio_detect.c

//根据硬件设计使用的WL_EN GPIO管脚号修改，版本中默认为GPIO4_3(4*8+3)
#define RTL_REG_ON_GPIO         (4*8 + 3)

//根据硬件设计选用的SDIO口修改，版本中默认为SDIO1，
//如果使用SDIO0，需修改如下注释部分，0x1改为0x2.同时需注意:移动单板需要将SDIO0_CARD_DETECT改为GPIO复用
static int hisi_wlan_set_carddetect(bool present)
{
        u32 regval;

        if (present) {
                pr_info("======== Card detection to detect SDIO card! ========\n");
                /* set card_detect low to detect card */
                regval = readl(REG_BASE_CTRL);
                regval |= 0x1; //如果使用SDIO0，改为0x2
                writel(regval, REG_BASE_CTRL);
        } else {
                pr_info("======== Card detection to remove SDIO card! ========\n");
                /* set card_detect high to remove card */
                regval = readl(REG_BASE_CTRL);
                regval &= ~(0x1);//如果使用SDIO0，改为0x2
                writel(regval, REG_BASE_CTRL);
        }

        return 0;
}

文件3 device/hisilicon/bigfish/sdk/source/component/wifi/drv/sdio_rtl8822bs/rtl88x2BS_WiFi_linux_v5.1.7.4_24893.20171108_COEX20170619-4141_beta_hs_oob_v2/Makefile

//根据硬件设计使用的OOB GPIO管脚号修改，版本中默认为GPIO3_5(3*8+5=29)
EXTRA_CFLAGS += -DRTL_OOB_INT_GPIO=29

蓝牙功能：

RTL8822BS：

文件1 device/hisilicon/bigfish/bluetooth/realtek8xxx/rtk_rfkill/rtk_rfkill.c

//根据硬件设计使用的BT_EN GPIO管脚号修改，版本中默认为GPIO4_2(4*8+2=34)
bt_reset = 34 ; //GPIO4_2 = 4*8+2 = 34

文件2 device/hisilicon/Hi3798MV300/BoardConfig.mk

//根据硬件设计使用的BT_WAKE_HOST GPIO管脚号修改，版本中98MV300默认为GPIO5_3(5*8+3=43=0x2b)
ifeq ($(BOARD_GPIO_BT_NUM),y)
BOARD_GPIO_BLUETOOTH_SUSPEND := 0x2b
endif

MT7668BS：

文件1 device/hisilicon/Hi3798MV300/BoardConfig.mk

//根据硬件设计使用的BT_WAKE_HOST GPIO管脚号修改，版本中98MV300默认为GPIO5_3(5*8+3=43=0x2b)
ifeq ($(BOARD_GPIO_BT_NUM),y)
BOARD_GPIO_BLUETOOTH_SUSPEND := 0x2b
endif

文件2 device/hisilicon/bigfish/bluetooth/Android.mk

//如果MT7668BS蓝牙协议栈有私有修改，请将Android.mk中MT7668BS蓝牙协议栈打开编译，并将新生成的协议栈库拷贝到device/hisilicon/bigfish/bluetooth/mt7668bs/bluedroid-lib下
//应改为如下：
ifeq ($(BOARD_BLUETOOTH_WIFI_DEVICE_MT7668BS),y)
include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/lib/Android.mk
#include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/bluedroid-lib/Android.mk
#include $(HISI_PLATFORM_PATH)/bluetooth/mt7668bs/bluedroid-conf/Android.mk
endif


------------------------修改结束------------------------------------------------------------------------------------------------------

------------------------常见问题定为方法----------------------------------------------------------------------------------------------

1、移动单板WiFi接在SDIO1口，打开WiFi时无法识别SDIO设备

查看SDIO0_CARD_DETECT是否复用为GPIO，如果没有，将SDIO0_CARD_DETECT复用为GPIO

2、WiFi性能低

请用如下方法确认SDIO INT模式、时钟频率配置是否正确：

如果使用SDIO0接WiFi，确认如下部分：

文件1 device/hisilicon/bigfish/sdk/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv200.dts

                sd:himciv200.SD@0xf9820000 {
                        compatible = "hi3798mv200,himciv200";
                        reg = <0xf9820000 0x1000>,<0xF8A210C0 0x40>;
                        interrupts = <0 34 4>;

                        clocks = <&hisilicon_clock PERI_CRG39_SDIO0>;
                        clock-names = "clk";

                        ldo-addr  = <0xf8a2011c>;
                        ldo-shift = <0>;

                        caps = <0x8007000f>;//0x8007000f 对应INT模式，如果不是，配置为0x8007000f
                        caps2 = <0x4000>;
                        max-frequency = <50000000>;
                        status = "okay";
                };

如果使用SDIO1接WiFi，确认如下部分

文件1 device/hisilicon/bigfish/sdk/source/kernel/linux-3.18.y/arch/arm/boot/dts/hi3798mv200.dts

                sdio:himciv200.SD@0xf9c40000 {
                        compatible = "hi3798mv200,himciv200";
                        reg = <0xf9c40000 0x1000>,<0xF8A21090 0x20>,<0xF8A20008 0x20>;
                        interrupts = <0 86 4>;

                        clocks = <&hisilicon_clock PERI_CRG163_SDIO2>;
                        clock-names = "clk";

                        caps = <0x8007000f>;//0x8007000f 对应INT模式，如果不是，配置为0x8007000f
                        caps2 = <0x4000>;
                        max-frequency = <50000000>;
                        status = "okay";
                };

确认SDIO时钟频率：

方法一：
    使用示波器测量SDIO_CLK管脚

方法二;
    使用himm工具读取0xf8a2203c寄存器的值

    SDIO0:
    读出的尾数为20B4，则SDIO0时钟频率为135MHz
    读出的尾数为20C8，则SDIO0时钟频率为150MHz

    SDIO1:
    读出的尾数为20B4，则SDIO1时钟频率为180MHz
    读出的尾数为20C8，则SDIO1时钟频率为200MHz