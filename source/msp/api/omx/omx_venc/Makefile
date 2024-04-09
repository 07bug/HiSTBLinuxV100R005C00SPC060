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
CFLAGS  +=  -I$(MSP_DIR)/api/omx/include    \
            -I$(MSP_DIR)/drv/venc

SRCS := omx_allocator.c omx_venc_queue.c omx_venc.c omx_venc_drv.c omx_venc_buf_mng.c


CFLAGS += -DOMXVENC_SUPPORT_1080P
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv450),)
CFLAGS += -DOMXVENC_SUPPORT_HEVC
endif

LIB_NAME := libOMX.hisi.video.encoder

include $(SDK_DIR)/hi_rules.mak
