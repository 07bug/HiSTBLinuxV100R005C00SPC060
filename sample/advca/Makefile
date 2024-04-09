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
	$(AT)make -C common
ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
	$(AT)make -C conax
endif
ifeq ($(CFG_HI_ADVCA_TYPE),IRDETO)
	$(AT)make -C irdeto
endif
ifeq ($(CFG_HI_ADVCA_TYPE),NOVEL)
	$(AT)make -C novel
endif
ifeq ($(CFG_HI_ADVCA_TYPE),SUMA)
	$(AT)make -C suma
endif

clean:
	$(AT)make -C common clean
	$(AT)make -C conax clean
	$(AT)make -C irdeto clean
	$(AT)make -C novel clean
	$(AT)make -C suma clean
