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
	$(AT)make -C product
ifeq ($(CFG_HI_TSIO_SUPPORT),y)
	$(AT)make -C tsio
endif

clean:
	$(AT)make -C product clean
	$(AT)make -C tsio clean

