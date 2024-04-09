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
CFG_CIPHER_MINI_OR_NOT = y

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(MSP_UNF_INCLUDE)            \
                -I$(MSP_DRV_INCLUDE)            \
                -I$(COMMON_UNF_INCLUDE)         \
                -I$(COMMON_DRV_INCLUDE)

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif

ifeq ($(CFG_HI_CPU_ARCH),arm64)
EXTRA_CFLAGS += -DHI_CPU_ARM64
endif

MOD_NAME := hi_cipher
obj-$(HI_DRV_BUILDTYPE) := $(MOD_NAME).o

include $(MSP_DIR)/drv/cipher/build.mak

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -DHI_TEE_SUPPORT
endif

ifeq ($(CFG_HI_DRV_WORK_IN_NON_SECURE_MODE),y)
EXTRA_CFLAGS += -DHI_DRV_WORK_IN_NON_SECURE_MODE
endif

ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    EXTRA_CFLAGS += -DCA_FRAMEWORK_V100_SUPPORT
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    EXTRA_CFLAGS += -DCA_FRAMEWORK_V200_SUPPORT
endif

BUILD_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(CURDIR))

BUILD_DIR_MAKEFILE := $(BUILD_DIR)/Makefile

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR_MAKEFILE)
	@echo $($(MOD_NAME)-y)
	@echo $(EXTRA_CFLAGS)
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
