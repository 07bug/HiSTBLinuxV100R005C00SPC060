#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

################################################################################
all:
all %: FORCE
	$(MAKE) -f arch32Makefile $(@) $(MKFLAGS)
ifeq ($(CFG_HI_64BIT_SYSTEM),y)
	$(MAKE) -f arch64Makefile $(@) $(MKFLAGS)
endif

FORCE:;
.PHONY: FORCE
