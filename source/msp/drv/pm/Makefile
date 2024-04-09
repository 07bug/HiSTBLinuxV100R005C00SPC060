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

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/drv/adsp/adsp_v1_1/include \
                -I$(MSP_DIR)/api/jpge/include           \
                -I$(MSP_DIR)/api/tde/include            \
                -I$(MSP_DIR)/drv/pm

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
    EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_96mv200
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200),)
    ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv200_ultra
        EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
    else
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51
    endif
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200),)
    ifeq ($(CFG_HI_ADVCA_TYPE),VERIMATRIX_ULTRA)
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv200_ultra
        EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
    else ifeq ($(CFG_HI_ADVCA_TYPE),IRDETO)
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv200_irdeto
    else
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv200
    endif
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv300),)
    EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv300
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
    EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51_98mv310
else
    EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/c51
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
    ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
        EXTRA_CFLAGS += -I$(COMPONENT_DIR)/pm/ddr_wakeup_check
    endif
endif

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    EXTRA_CFLAGS += -DCA_FRAMEWORK_V100_SUPPORT
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    EXTRA_CFLAGS += -DCA_FRAMEWORK_V200_SUPPORT
else
    $(error otp_klad version is error)
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
EXTRA_CFLAGS += -DHI_VENC_SUPPORT
endif

ifeq ($(CFG_HI_JPGE_SUPPORT),y)
EXTRA_CFLAGS += -DHI_JPGE_SUPPORT
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
EXTRA_CFLAGS += -DHI_KEYLED_SUPPORT
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifeq ($(CFG_ADVCA_IRDETO),y)
EXTRA_CFLAGS += -DHI_ADVCA_IRDETO_SUPPORT
endif
endif

ifeq ($(CFG_PRODUCT_TYPE),android)
EXTRA_CFLAGS += -DANDROID
endif

MOD_NAME := hi_pmoc

$(MOD_NAME)-y   :=  drv_pmoc_intf.o drv_pmoc_smartstandby.o

ifeq ($(CFG_HI_DVFS_CPU_SUPPORT),y)
EXTRA_CFLAGS += -DHI_DVFS_CPU_SUPPORT

PM_DIR_VER := pm_v100
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv300 hi3798mv310),)
PM_DIR_VER := pm_v200
endif

$(MOD_NAME)-y   +=  $(PM_DIR_VER)/clock_mpu.o   \
                    hi_opp_data.o               \
                    opp.o                       \
                    $(PM_DIR_VER)/hi_dvfs.o     \
                    $(PM_DIR_VER)/hi_temp.o     \
                    clock.o                     \
                    hi_cpufreq.o
endif

ifeq ($(CFG_HI_PMU_DEVICE_SELECT),y)
EXTRA_CFLAGS += -DHI_PMU_DEVICE_SELECT
endif

ifeq ($(CFG_HI_DONGLE_MODE_NORMAL),y)
EXTRA_CFLAGS += -DHI_DONGLE_MODE_NORMAL
endif

ifeq ($(CFG_HI_DONGLE_MODE_LOW),y)
EXTRA_CFLAGS += -DHI_DONGLE_MODE_LOW
endif

ifeq ($(CFG_HI_DONGLE_MODE_CRITICAL),y)
EXTRA_CFLAGS += -DHI_DONGLE_MODE_CRITICAL
endif

ifeq ($(CFG_HI_AI_SUPPORT),y)
EXTRA_CFLAGS += -DHI_AUDIO_AI_SUPPORT
endif

ifeq ($(CFG_HI_PM_START_MCU_RUNNING), y)
EXTRA_CFLAGS += -DHI_PM_START_MCU_RUNNING
endif

ifeq ($(CFG_HI_GPIO_LIGHT_SUPPORT), y)
    EXTRA_CFLAGS += -DHI_GPIO_LIGHT_SUPPORT
    EXTRA_CFLAGS += -DHI_POSITIVE_GPIO_LIGHT_NUMBER=$(CFG_HI_POSITIVE_GPIO_LIGHT_NUMBER)
    EXTRA_CFLAGS += -DHI_NEGATIVE_GPIO_LIGHT_NUMBER=$(CFG_HI_NEGATIVE_GPIO_LIGHT_NUMBER)

    ifeq ($(CFG_HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP),)
        EXTRA_CFLAGS += -DHI_POSITIVE_GPIO_LIGHT_NUMBER_QFP=0x2A
    else
        EXTRA_CFLAGS += -DHI_POSITIVE_GPIO_LIGHT_NUMBER_QFP=$(CFG_HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP)
    endif
endif

ifeq ($(CFG_HI_PM_POWERUP_MODE1_SUPPORT),y)
    EXTRA_CFLAGS += -DHI_PM_POWERUP_MODE1_SUPPORT
endif

ifeq ($(CFG_HI_DVFS_CPU_SUPPORT), y)
    EXTRA_CFLAGS += -DHI_TEMP_CTRL_DOWN_THRESHOLD=$(CFG_HI_TEMP_CTRL_DOWN_THRESHOLD)
    EXTRA_CFLAGS += -DHI_TEMP_CTRL_UP_THRESHOLD=$(CFG_HI_TEMP_CTRL_UP_THRESHOLD)
    EXTRA_CFLAGS += -DHI_TEMP_CTRL_REBOOT_THRESHOLD=$(CFG_HI_TEMP_CTRL_REBOOT_THRESHOLD)
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798cv200),)
    ifeq ($(CFG_HI_ADVCA_TYPE)_$(CFG_HI_TEE_SUPPORT),VERIMATRIX_ULTRA_y)
        EXTRA_CFLAGS += -DHI_TEE_MCU_SUPPORT
    endif
endif

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) modules
	$(AT)test -d $(HI_MODULE_DIR) || mkdir -p $(HI_MODULE_DIR)
	$(AT)cp -f $(BUILD_DIR)/$(MOD_NAME).ko $(HI_MODULE_DIR)/

clean:
	$(AT)make -C $(LINUX_DIR) ARCH=$(CFG_HI_CPU_ARCH) CROSS_COMPILE=$(HI_KERNEL_TOOLCHAINS_NAME)- M=$(BUILD_DIR) src=$(CURDIR) clean
	$(AT)rm -rf $(HI_MODULE_DIR)/$(MOD_NAME).ko

$(BUILD_DIR_MAKEFILE): $(BUILD_DIR)
	$(AT)touch $@

$(BUILD_DIR):
	$(AT)mkdir -p $@

