#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  -I$(CURDIR)/../include/

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
CFLAGS  += -DHI_ADVCA_FUNCTION_RELEASE
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv450),)
CFLAGS += -DOMXVENC_SUPPORT_HEVC
endif

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv300),)
CFLAGS += -DVP9_SUPPORT
CFLAGS += -DVP8_SUPPORT
endif

SRCS := omx_core.c

LIB_NAME := libOMX_Core

include $(SDK_DIR)/hi_rules.mak
