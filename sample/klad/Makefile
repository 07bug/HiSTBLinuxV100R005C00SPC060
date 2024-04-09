#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := \
    sample_klad_tsplay  \
    sample_klad_crypto  \
    sample_klad_swpk


ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_IMAGES += sample_klad_dvbplay
endif

COMMON_OBJS := $(filter-out hi_adp_pvr.o,$(COMMON_SRCS:%.c=%.o))

LOCAL_OBJS += parse_config_file.o

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
