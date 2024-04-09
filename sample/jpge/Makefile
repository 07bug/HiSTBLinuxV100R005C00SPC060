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
CFLAGS :=  -I$(MSP_DIR)/api/jpge/include
CFLAGS +=  -I$(MSP_DIR)/api/tde/include
CFLAGS +=  -I$(MSP_DIR)/api/jpeg/include
CFLAGS +=  -I$(COMPONENT_DIR)/jpeg/include

CFLAGS += -DCONFIG_LINUX_OS

#CFLAGS += -DCONFIG_DEBUG_MSG

SAMPLE_IMAGES := sample_enc_api

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := $(HI_LIBS)

include $(SAMPLE_DIR)/hi_sample_rules.mak
