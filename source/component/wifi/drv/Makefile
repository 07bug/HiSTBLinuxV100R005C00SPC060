#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects :=

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8188CUS),y)
objects += usb_rtl8188cu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8192CU),y)
objects += usb_rtl8188cu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8188EUS),y)
objects += usb_rtl8188eu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8192EU),y)
objects += usb_rtl8192eu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8192DU),y)
objects += usb_rtl8192du
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8812AU),y)
objects += usb_rtl8812au
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8812AE),y)
objects += pcie_rtl8812ae
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8822BU),y)
objects += usb_rtl8822bu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8723BU),y)
objects += usb_rtl8723bu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8821AU),y)
objects += usb_rtl8821au
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8192EE),y)
objects += pcie_rtl8192ee
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8822BEH),y)
objects += pcie_rtl8822beh
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8188FU),y)
objects += usb_rtl8188fu
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RT5370),y)
objects += usb_rt5370
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RT5572),y)
objects += usb_rt5572
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT7601U),y)
objects += usb_mt7601u
endif

ifeq ($(CFG_HI_WIFI_DEVICE_AR9271),y)
objects += usb_ar9271
endif

ifeq ($(CFG_HI_WIFI_DEVICE_AR9374),y)
objects += usb_ar9374
endif

ifeq ($(CFG_HI_WIFI_DEVICE_QCA1021G),y)
objects += usb_ar9374
endif

ifeq ($(CFG_HI_WIFI_DEVICE_QCA1021X),y)
objects += usb_ar9374
endif

ifeq ($(CFG_HI_WIFI_DEVICE_BCM43236),y)
objects += usb_bcm43xx
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8812AR),y)
objects += pcie_rtl8812ar
endif

ifeq ($(CFG_HI_WIFI_DEVICE_RTL8822BS),y)
objects += sdio_rtl8822bs
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT7668BS),y)
objects += sdio_mt7668bs
endif

ifeq ($(CFG_HI_WIFI_DEVICE_AP6356P),y)
objects += pcie_ap6xxx
endif

ifeq ($(CFG_HI_WIFI_DEVICE_AP6356S),y)
objects += sdio_ap6xxx
BIN_DIR_AP6356S := $(HI_ROOTFS_DIR)/lib/firmware
BIN_SRC_AP6356S := $(COMPONENT_DIR)/wifi/drv/sdio_ap6xxx/AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag.bin \
                   $(COMPONENT_DIR)/wifi/drv/sdio_ap6xxx/AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag_apsta.bin \
                   $(COMPONENT_DIR)/wifi/drv/sdio_ap6xxx/AP6356S_4.2/Wi-Fi/fw_bcm4356a2_ag_p2p.bin \
                   $(COMPONENT_DIR)/wifi/drv/sdio_ap6xxx/AP6356S_4.2/Wi-Fi/nvram_ap6356s.txt \
                   $(COMPONENT_DIR)/wifi/drv/sdio_ap6xxx/AP6356S_4.2/Wi-Fi/config.txt
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT76X2U),y)
objects += usb_mt76x2u
BIN_DIR_MT76X2U := $(HI_ROOTFS_DIR)/etc/Wireless/RT2870STA
FW_DIR_MT76X2U := $(HI_ROOTFS_DIR)/lib/firmware
BIN_SRC_MT76X2U := $(COMPONENT_DIR)/wifi/drv/usb_mt76x2u/JEDI.MP2.mt76x2u.wifi.v3.3.2/conf/MT76x2STA.dat
FW_SRC_MT76X2U := $(COMPONENT_DIR)/wifi/drv/usb_mt76x2u/JEDI.MP2.mt76x2u.wifi.v3.3.2/mcu/bin/mt7662_firmware_e3_tvbox.bin \
                  $(COMPONENT_DIR)/wifi/drv/usb_mt76x2u/JEDI.MP2.mt76x2u.wifi.v3.3.2/mcu/bin/mt7662_patch_e3_hdr.bin \
                  $(COMPONENT_DIR)/wifi/drv/usb_mt76x2u/JEDI.MP2.mt76x2u.wifi.v3.3.2/mcu/bin/mt7662t_firmware_e1.bin \
                  $(COMPONENT_DIR)/wifi/drv/usb_mt76x2u/JEDI.MP2.mt76x2u.wifi.v3.3.2/mcu/bin/mt7662t_patch_e1_hdr.bin
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT7662TE),y)
objects += pcie_mt76x2te
BIN_DIR_MT7662TE := $(HI_ROOTFS_DIR)/etc/Wireless/RT2870STA
FW_DIR_MT7662TE := $(HI_ROOTFS_DIR)/lib/firmware
BIN_SRC_MT7662TE := $(COMPONENT_DIR)/wifi/drv/pcie_mt76x2te/JEDI.MT76x2_WLDRV.MP2-PCIe/conf/MT76x2STA.dat
FW_SRC_MT7662TE := $(COMPONENT_DIR)/wifi/drv/pcie_mt76x2te/JEDI.MT76x2_WLDRV.MP2-PCIe/mcu/bin/mt7662_firmware_e3_tvbox.bin \
                   $(COMPONENT_DIR)/wifi/drv/pcie_mt76x2te/JEDI.MT76x2_WLDRV.MP2-PCIe/mcu/bin/mt7662_patch_e3_hdr.bin \
                   $(COMPONENT_DIR)/wifi/drv/pcie_mt76x2te/JEDI.MT76x2_WLDRV.MP2-PCIe/mcu/bin/mt7662t_firmware_e1.bin \
                   $(COMPONENT_DIR)/wifi/drv/pcie_mt76x2te/JEDI.MT76x2_WLDRV.MP2-PCIe/mcu/bin/mt7662t_patch_e1_hdr.bin
endif

ifeq ($(CFG_HI_WIFI_DEVICE_QCA6174),y)
objects += pcie_qca6174
BIN_DIR_QCA6174 := $(HI_ROOTFS_DIR)/lib/firmware/wlan
FW_DIR_QCA6174 := $(HI_ROOTFS_DIR)/lib/firmware
BIN_SRC_QCA6174 := $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/wlan/cfg.dat \
                   $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/wlan/qcom_cfg.ini
FW_SRC_QCA6174 := $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/athwlan.bin \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/btfw32.tlv \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/btnv32.bin \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/fakeboar.bin \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/fakeboar_big.bin \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/otp.bin \
                  $(COMPONENT_DIR)/wifi/drv/pcie_qca6174/firmware/utf.bin
endif

ifeq ($(CFG_HI_WIFI_DEVICE_QCA6174_SDIO),y)
objects += sdio_qca6174a
endif

ifeq ($(CFG_HI_WIFI_DEVICE_HI1131C),y)
objects += sdio_hi1131c
endif

obj-y += $(addsuffix /,$(objects))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean

all:
ifeq ($(CFG_HI_WIFI_DEVICE_QCA6174),y)
#	$(AT)make -C pcie_qca6174
	@test -d $(BIN_DIR_QCA6174) || mkdir -p $(BIN_DIR_QCA6174)
	@cp -v $(BIN_SRC_QCA6174) $(BIN_DIR_QCA6174)/
	@test -d $(FW_DIR_QCA6174) || mkdir -p $(FW_DIR_QCA6174)
	@cp -v $(FW_SRC_QCA6174) $(FW_DIR_QCA6174)/
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT76X2U),y)
	@test -d $(BIN_DIR_MT76X2U) || mkdir -p $(BIN_DIR_MT76X2U)
	@cp -v $(BIN_SRC_MT76X2U) $(BIN_DIR_MT76X2U)/
	@test -d $(FW_DIR_MT76X2U) || mkdir -p $(FW_DIR_MT76X2U)
	@cp -v $(FW_SRC_MT76X2U) $(FW_DIR_MT76X2U)/
endif

ifeq ($(CFG_HI_WIFI_DEVICE_MT7662TE),y)
	@test -d $(BIN_DIR_MT7662TE) || mkdir -p $(BIN_DIR_MT7662TE)
	@cp -v $(BIN_SRC_MT7662TE) $(BIN_DIR_MT7662TE)/
	@test -d $(FW_DIR_MT7662TE) || mkdir -p $(FW_DIR_MT7662TE)
	@cp -v $(FW_SRC_MT7662TE) $(FW_DIR_MT7662TE)/
endif

ifeq ($(CFG_HI_WIFI_DEVICE_AP6356S),y)
	@test -d $(BIN_DIR_AP6356S) || mkdir -p $(BIN_DIR_AP6356S)
	@cp -v $(BIN_SRC_AP6356S) $(BIN_DIR_AP6356S)/
endif

clean:
ifeq ($(CFG_HI_WIFI_DEVICE_QCA6174),y)
#	$(AT)make -C pcie_qca6174 clean
endif
