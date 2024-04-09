#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS := -I$(CURDIR)/include
CFLAGS += -DLINUX_OS -DSTB_AOUT_SUPPORT=1 -DHAL_HISI_EXTEND_H -Wno-unused-parameter -Wno-unused-function -Wno-unused-value

LIB_NAME := libhal

SRCS := $(patsubst %.c,%.o,$(wildcard src/aout/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/vout/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/system/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/av/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/dmx/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/mem/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/hardware/**/*.c))

CFLAGS += -I$(CURDIR)/include
CFLAGS += -I$(CURDIR)/src/common
CFLAGS += -I$(CURDIR)/src
CFLAGS += -I$(MSP_DIR)/include
CFLAGS += -I$(MSP_DIR)/api/include
CFLAGS += -I$(MSP_DIR)/api/higo/include
CFLAGS += -I$(MSP_DIR)/drv/include
CFLAGS += -I$(COMMON_DIR)/include
CFLAGS += -I$(COMPONENT_DIR)/ha_codec/include
CFLAGS += -I$(COMPONENT_DIR)/subtitle/include
CFLAGS += -I$(COMPONENT_DIR)/subtoutput/include
CFLAGS += -I$(COMPONENT_DIR)/teletext/include
CFLAGS += -I$(COMPONENT_DIR)/cc/include
CFLAGS += -I$(COMPONENT_DIR)/hal/src/caption/caption_cc_out
CFLAGS += -I$(COMPONENT_DIR)/hal/src/caption/caption_subt_out
CFLAGS += -I$(COMPONENT_DIR)/hal/src/caption/caption_ttx_out
CFLAGS += -I$(COMPONENT_DIR)/hal/src/caption/caption_out_common

ifeq ($(CFG_HI_SM_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/sm/*.c))
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_PVR_EXTRA_BUF_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/pvr/*.c))
endif
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/smc/*.c))
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_VENC_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/enc/*.c))
endif
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
ifeq ($(CFG_HI_CAPTION_SO_SUPPORT),y)
ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/caption/*.c))
SRCS += $(patsubst %.c,%.o,$(wildcard src/caption/**/*.c))
endif
endif
endif
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SRCS += $(patsubst %.c,%.o,$(wildcard src/frontend/*.c))
endif

ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    CFLAGS += -DCA_FRAMEWORK_V100_SUPPORT
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    CFLAGS += -DCA_FRAMEWORK_V200_SUPPORT
else
    $(error otp_klad version is error)
endif

ifeq ($(CFG_HI_DISEQC_SUPPORT),y)
CFLAGS += -DDISEQC_SUPPORT
endif

ifeq ($(CFG_HI_SM_SUPPORT),y)
CFLAGS += -DSM_SUPPORT
endif

include $(SDK_DIR)/hi_rules.mak
