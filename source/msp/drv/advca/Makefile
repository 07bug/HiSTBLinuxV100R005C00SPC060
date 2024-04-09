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
# local variable
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)             \
                -I$(COMMON_API_INCLUDE)             \
                -I$(COMMON_DRV_INCLUDE)             \
                -I$(MSP_UNF_INCLUDE)                \
                -I$(MSP_API_INCLUDE)                \
                -I$(MSP_DRV_INCLUDE)                \
                -I$(MSP_DIR)/drv/advca              \
                -I$(MSP_DIR)/drv/advca/V300         \
                -I$(MSP_DIR)/drv/advca/ca_otp       \
                -I$(MSP_DIR)/drv/advca/ca_otp/ca_otpv200

ifeq ($(CONFIG_TEE_VMX_ULTRA),y)
EXTRA_CFLAGS +=  -I$(KERNEL_SRC_DIR)/drivers/hisilicon/tee/tee_hisi/vmx_tzdriver
else
EXTRA_CFLAGS +=  -I$(TEE_DRV_INCLUDE)
endif

DDR_WAKE_UP_CHECK_BIN = $(MSP_DIR)/drv/advca/ddr_wakeup_check/ddr_wakeup_check.bin
EXTRA_AFLAGS += -DWAKE_UP_BIN=\"$(DDR_WAKE_UP_CHECK_BIN)\"

ifeq ($(CFG_HI_64BIT_SYSTEM),y)
	ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv300),)
	EXTRA_CFLAGS += -DDDR_WAKEUP_SRC=\"ddr_wakeup_check/output_hash256_64.txt\"
	else
	EXTRA_CFLAGS += -DDDR_WAKEUP_SRC=\"ddr_wakeup_check/output_hash1_64.txt\"
	endif
else
	ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv300),)
	EXTRA_CFLAGS += -DDDR_WAKEUP_SRC=\"ddr_wakeup_check/output_hash256_32.txt\"
	else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
	EXTRA_CFLAGS += -DDDR_WAKEUP_SRC=\"ddr_wakeup_check_98mv310/output.txt\"
	else
	EXTRA_CFLAGS += -DDDR_WAKEUP_SRC=\"ddr_wakeup_check/output_hash1_32.txt\"
	endif
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
EXTRA_CFLAGS += -DHI_TEE_SUPPORT
EXTRA_CFLAGS += -I$(TEE_DRV_INCLUDE)
endif

ifeq ($(CFG_HI_DRV_WORK_IN_NON_SECURE_MODE),y)
EXTRA_CFLAGS += -DHI_DRV_WORK_IN_NON_SECURE_MODE
endif

ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
ifeq ($(CFG_HI_DRV_WORK_IN_NON_SECURE_MODE),n)
EXTRA_CFLAGS += -DKLAD_TYPE_TEE_VERIMATRIX_ULTRA
endif
endif
MOD_NAME := hi_advca

obj-$(HI_DRV_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y :=    drv_advca_intf.o \
                    drv_advca.o \
                    drv_advca_common.o \
                    V300/hal_advca_v300.o \
                    V300/drv_advca_v300.o \
                    ca_otp/ca_otpv200/drv_ca_otp_v200.o

ifeq ($(CFG_HI_DRV_WORK_IN_NON_SECURE_MODE),n)
$(MOD_NAME)-y += drv_tee_advca.o
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
$(MOD_NAME)-y += drv_tee_advca_agent.o
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
