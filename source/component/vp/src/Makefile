#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)

CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    \
            -I$(COMPONENT_DIR)/vp/include           \
            -I$(COMPONENT_DIR)/vp/rtp               \
            -I$(COMPONENT_DIR)/vp/src/muxer         \
            -I$(COMPONENT_DIR)/vp/src/muxer/include

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DVP_PROC_SUPPORT
endif

LIB_NAME := libhi_vp

SRCS := unf_vp.c
SRCS += muxer/hi_tran_muxer.c
SRCS += muxer/ts/ts_intf.c

HEADER_FILES := $(COMPONENT_DIR)/vp/include/hi_unf_vp.h

include $(SDK_DIR)/hi_rules.mak

