#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := \
	sample_ca_crypto  \
	sample_ca_tsplay \
	sample_ca_set_otp_fuse \
	sample_ca_get_otp_fuse \
	sample_ca_blpk \
	sample_ca_writeRSAkey

    
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_IMAGES += sample_ca_dvbplay
endif

COMMON_OBJS := $(filter-out hi_adp_pvr.o,$(COMMON_SRCS:%.c=%.o))

LOCAL_OBJS += parse_config_file.o

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
