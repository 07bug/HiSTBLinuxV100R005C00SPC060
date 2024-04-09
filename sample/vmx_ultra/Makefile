#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
.PHONY: all clean
#===============================================================================
all:
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
	$(AT)make -C product
endif

clean:
	$(AT)make -C product clean

