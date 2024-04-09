#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

CFLAGS := -I$(SDK_DIR)/source/common/api/include

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_keyprovison


DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
