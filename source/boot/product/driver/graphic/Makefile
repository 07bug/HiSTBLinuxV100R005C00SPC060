#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

HIGO_DIR = .
HIFB_DIR = hifb

CFLAGS += -DHI_BUILD_IN_BOOT -D__DISP_PLATFORM_BOOT__

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
CFLAGS += -DHI_BUILD_IN_MINI_BOOT
endif

ifeq ($(CFG_HI_LOADER_BOOTLOADER),y)
CFLAGS += -DHI_LOADER_BOOTLOADER
endif

ifeq ($(CFG_HI_LOG_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_LOG_SUPPORT
endif
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv430),)
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif
#CFLAGS += -DCONFIG_GFX_DOUBLE_BUFFER_SUPPORT
CFLAGS += -DCONFIG_GFX_ONLY_HARD_DECOMPRESS

#===============================================================================
#hifb adp olatform
#===============================================================================
HIFB_ALG_DIR  := alg
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310 hi3716mv430),)
HIFB_HAL_DIR  := hal_v2_0
else
HIFB_HAL_DIR  := hal_v1_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv430 hi3716mv450),)
CFLAGS += -DCONFIG_HIFB_VERSION_2_0
else
CFLAGS += -DCONFIG_HIFB_VERSION_1_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3796mv200 hi3716mv450),)
CFLAGS += -DCONFIG_HIFB_SUPPORT_HDR_DEPRE_MIXG
endif

TDE_HAL_DIR  := tde_v1_0

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv430 hi3716mv450),)
TDE_HAL_DIR  := tde_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310 hi3716mv430),)
CFLAGS += -DCONFIG_GFX_TDE_VERSION_3_0
endif

#===============================================================================
#tde include
#===============================================================================
CFLAGS   += -I$(MSP_DIR)/drv/tde/include         \
	    -I$(MSP_DIR)/drv/tde/adp/$(TDE_HAL_DIR) \
            -I$(MSP_DIR)/api/tde/include \
	    -I$(HIGO_DIR)/tde
#===============================================================================
# jpeg include
#===============================================================================
CFLAGS   += -I$(HIGO_DIR)/dec                       \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc       \
            -I$(MSP_DIR)/api/jpeg/include           \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/inc_hard \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_comm \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_hard \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_soft \
	    -I$(MSP_DIR)/drv/jpeg/include           \
            -I$(MSP_DIR)/drv/jpeg/grc_cmm_inc
#===============================================================================
# gfx self include
#===============================================================================
CFLAGS   += -I$(HIGO_DIR)/gfx      \
            -I$(HIGO_DIR)/include

#===============================================================================
# hifb include
#===============================================================================
CFLAGS   += -I$(HIGO_DIR)/hifb                           \
	    -I$(MSP_DIR)/drv/hifb/inc                    \
            -I$(MSP_DIR)/drv/hifb/include                \
            -I$(MSP_DIR)/drv/hifb/adp/inc                \
            -I$(MSP_DIR)/drv/hifb/adp/src                \
            -I$(MSP_DIR)/drv/hifb/adp/${HIFB_ALG_DIR}    \
            -I$(MSP_DIR)/drv/hifb/adp/${HIFB_HAL_DIR}

#===============================================================================
# others include
#===============================================================================
CFLAGS   += -I$(PRODUCT_DIR)/driver/include           \
            -I$(PRODUCT_DIR)/driver/include_inc       \
	    -I$(MSP_DIR)/drv/include

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv430 hi3716mv450),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v4_0/component/
endif

CFLAGS   += -I$(BOOT_DIR)/include
CFLAGS   += -I$(BOOT_DIR)/include/linux/mtd

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv430 hi3716mv450),)
CFLAGS += -DCONFIG_GFX_PQ
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_CLOCK
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
#CFLAGS += -DCONFIG_GFX_SUPPORT_VO_4K
endif

#self compile selection
#CFLAGS += -fstack-protector --param ssp-buffer-size=4
#CFLAGS += -Wformat -Wformat-security -g0 -s
#CFLAGS += -Wl,-z,relro
#CFLAGS += -Os -ffunction-sections
#===============================================================================
#tde src
#===============================================================================
SRC     += $(wildcard $(HIGO_DIR)/msp/drv/tde/*.c)
SRC     += $(wildcard $(HIGO_DIR)/msp/api/tde/*.c)
#===============================================================================
#jpeg src
#===============================================================================
SRC     += $(wildcard $(HIGO_DIR)/dec/*.c)
SRC     += $(wildcard $(HIGO_DIR)/msp/api/jpeg/*.c)
#===============================================================================
#gfx self src
#===============================================================================
SRC     += $(wildcard $(HIGO_DIR)/gfx/*.c)
SRC     += $(wildcard $(HIGO_DIR)/tde/*.c)
#===============================================================================
#hifb src
#===============================================================================
SRC     +=  $(HIGO_DIR)/msp/drv/hifb/adp/src/drv_hifb_wbc.c       \
            $(HIGO_DIR)/msp/drv/hifb/adp/src/drv_hifb_adp.c       \
            $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_HAL_DIR}/drv_hifb_hal.c

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv430 hi3716mv450),)
SRC     +=  $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}/optm_alg_csc.c     \
            $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}/optm_alg_gzme.c    \
            $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}/optm_alg_gsharp.c  \
            $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}/optm_alg_zme_coef.c

endif

#===============================================================================
# obj file
#===============================================================================
OBJS := $(SRC:%.c=%.o)

#===============================================================================
# lib file name
#===============================================================================
LIBS := $(HIGO_DIR)/libgraphic.a

#===============================================================================
# rules
#===============================================================================

.PHONY: all prepare clean install uninstall $(LIBS)


all: $(LIBS)

prepare:
	$(AT)-test -e $(HIGO_DIR)/msp/drv/tde  || mkdir -p $(HIGO_DIR)/msp/drv/tde
	$(AT)-test -e $(HIGO_DIR)/msp/api/tde  || mkdir -p $(HIGO_DIR)/msp/api/tde
	$(AT)-test -e $(HIGO_DIR)/msp/api/jpeg || mkdir -p $(HIGO_DIR)/msp/api/jpeg
	$(AT)-test -e $(HIGO_DIR)/msp/drv/hifb/adp/src              ||  mkdir -p $(HIGO_DIR)/msp/drv/hifb/adp/src
	$(AT)-test -e $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_HAL_DIR}  ||  mkdir -p $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_HAL_DIR}
	$(AT)-test -e $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}  ||  mkdir -p $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}
	$(AT)cp -rf   $(MSP_DIR)/api/jpeg/jpeg-hal/src_hard/hi_jpeg_api.c  $(HIGO_DIR)/msp/api/jpeg
	$(AT)cp -rf   $(MSP_DIR)/api/jpeg/jpeg-hal/src_hard/jpeg_hal_dec.c $(HIGO_DIR)/msp/api/jpeg
	$(AT)cp -rf   $(MSP_DIR)/drv/tde/src/*.c                           $(HIGO_DIR)/msp/drv/tde
	$(AT)cp -rf   $(MSP_DIR)/drv/tde/adp/$(TDE_HAL_DIR)/*.c            $(HIGO_DIR)/msp/drv/tde
	$(AT)cp -rf   $(MSP_DIR)/api/tde/*.c                               $(HIGO_DIR)/msp/api/tde
	$(AT)cp -rf   $(MSP_DIR)/drv/hifb/adp/src/drv_hifb_wbc.c           $(HIGO_DIR)/msp/drv/hifb/adp/src
	$(AT)cp -rf   $(MSP_DIR)/drv/hifb/adp/src/drv_hifb_adp.c           $(HIGO_DIR)/msp/drv/hifb/adp/src
	$(AT)cp -rf   $(MSP_DIR)/drv/hifb/adp/${HIFB_HAL_DIR}/*.c          $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_HAL_DIR}
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450),)
	$(AT)cp -rf   $(MSP_DIR)/drv/hifb/adp/${HIFB_ALG_DIR}/*.c      $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}
endif
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/tde/tde_proc_k.c
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/tde/tde_osr.c
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/tde/tde_osr_k.c
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/tde/*.mod*
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/hifb/adp/src/*.mod*
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_HAL_DIR}/*.mod*
	$(AT)rm -rf   $(HIGO_DIR)/msp/drv/hifb/adp/${HIFB_ALG_DIR}/*.mod*

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf $(HIGO_DIR)/msp

install: all

uninstall:

$(LIBS):$(OBJS)
	$(AR) -rc $@ $^
	$(AT)rm -rf $(OBJS)

%.o:%.c
	$(AT)$(CC) $(CFLAGS) -c $^ -o $@
