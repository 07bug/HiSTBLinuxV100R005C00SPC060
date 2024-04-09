#=======================================
#   export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
    SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    OTP_DIR := v100
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    OTP_DIR := v200
else
    $(error otp_klad version is error)
endif

obj-y += $(OTP_DIR)/

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(OTP_DIR) all

clean:
	$(AT)make -C $(OTP_DIR) clean
