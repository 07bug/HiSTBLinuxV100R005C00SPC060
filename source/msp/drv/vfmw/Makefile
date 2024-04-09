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
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
VFMW_MAKE_DIR = vfmw_v5.1/product/make_stb
else
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450),)
VFMW_MAKE_DIR = vfmw_v5.0/product/make_stb
else
VFMW_MAKE_DIR = vfmw_v4.0
endif
endif

obj-y += $(VFMW_MAKE_DIR)/

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(VFMW_MAKE_DIR)/ all

clean:
	$(AT)make -C $(VFMW_MAKE_DIR)/ clean

