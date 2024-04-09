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
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += $(CFG_HI_BOARD_CONFIGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(COMMON_DIR)/drv/sys                 \
                -I$(COMMON_DIR)/drv/mmz                 \
                -I$(MSP_DIR)/drv/mailbox                \
                -I$(MSP_DIR)/drv/runtime_check


MOD_NAME := hi_runtime

obj-m += $(MOD_NAME).o

ifeq ($(CFG_HI_ROOTFS_RUNTIME_CHECK_ENABLE),y)
    EXTRA_CFLAGS += -DHI_ROOTFS_RUNTIME_CHECK_ENABLE
    EXTRA_CFLAGS += -DHI_ROOTFS_CALCULATE_DELAY_TIME=$(CFG_HI_ROOTFS_CALCULATE_DELAY_TIME)
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
    EXTRA_CFLAGS += -DHI_TEE_SUPPORT
endif

$(MOD_NAME)-y   :=  drv_runtime_check_intf.o

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
$(MOD_NAME)-y   +=  drv_runtime_check_v2.o
else
$(MOD_NAME)-y   +=  drv_runtime_check.o
$(MOD_NAME)-y   +=  drv_runtime_check_sha1.o
endif

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

