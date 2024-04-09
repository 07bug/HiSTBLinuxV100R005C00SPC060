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
CFLAGS  :=  -I$(MSP_DIR)/api/jpeg/include             \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc         \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/inc_hard   \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_hard   \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_comm   \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_soft   \
            -I$(MSP_DIR)/drv/jpeg/include             \
            -I$(MSP_DIR)/api/tde/include              \
            -I$(COMMON_DIR)/api/include               \
            -I$(COMMON_DIR)/include

#===============================================================================
# local define
#===============================================================================
ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_SUPPORT
else
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
endif

CFLAGS += -DCONFIG_GFX_ONLY_HARD_DECOMPRESS

#===============================================================================
# src
#===============================================================================
SRCS := jpeg-hal/src_hard/hi_jpeg_api.c     \
        jpeg-hal/src_hard/jpeg_hal_dev.c    \
        jpeg-hal/src_hard/jpeg_hal_dec.c

#===============================================================================
# include
#===============================================================================
#HEADER_FILES := $(MSP_DIR)/api/jpeg/include/hi_jpeg_api.h

#===============================================================================
# lib name
#===============================================================================
LIB_NAME := libhi_jpeg

#===============================================================================
# compile
#===============================================================================
include $(SDK_DIR)/hi_rules.mak
