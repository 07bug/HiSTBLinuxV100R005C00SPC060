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
CFLAGS := -I$(SDK_DIR)/source/component/loader/api/include
CFLAGS += -I$(SDK_DIR)/source/component/loader/api/src

ifeq ($(CFG_HI_APPLOADER_SUPPORT),y)
CFLAGS += -DHI_LOADER_APPLOADER
endif

SAMPLE_IMAGES := sample_loader

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
ifneq ($(findstring $(CFG_HI_ADVCA_TYPE), NAGRA VERIMATRIX_ULTRA),)
SAMPLE_IMAGES += sample_backup
endif
endif

DEPEND_LIBS := -lhi_common -lhi_msp -ljpeg -lhiloader

ifeq ($(CFG_HI_TEE_SUPPORT),y)
DEPEND_LIBS += -lteec
endif

include $(SAMPLE_DIR)/hi_sample_rules.mak
