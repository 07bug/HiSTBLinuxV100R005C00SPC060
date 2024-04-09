#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===================================================================
#DirectFB Version
#==================================================================
DIRECTFB_VER := 1.7.7
FUSION_VER   := 9.0.2
PATCH_DIR    := patch-directfb
DFB_ADP_LIB_VER := directfb-1.7-7

DFB_CFG :=
#DFB_CFG := --enable-png=no --enable-zlib=no --enable-jpeg=no --enable-freetype=no
DFB_CFG += --enable-fbdev=no
DFB_CFG += --with-gfxdrivers=hisi_gfx2d
DFB_CFG += --with-inputdrivers=hisi_linux_input,hisi_lirc,hisi_ps2mouse

DIRECTFB := DirectFB-$(DIRECTFB_VER)
FUSION   := linux-fusion-$(FUSION_VER)

ifeq ($(CFG_HI_DIRECTFB_MULTI_SUPPORT),y)
protype=enable
else
protype=disable
endif

ifeq ($(CFG_HI_DIRECTFB_DEBUG_SUPPORT),y)
comtype=enable
else
comtype=disable
endif

DFB_CFG += --$(protype)-multi --$(comtype)-debug

DFB_CFG += --disable-drmkms --disable-tiff --without-setsockopt --without-tools --without-tests --disable-osx --disable-x11 --disable-x11vdpau --disable-mmx --disable-sse --disable-vnc --disable-mesa --disable-devmem  --disable-pnm --disable-imlib2 --disable-mpeg2 --disable-bmp --disable-jpeg2000 --disable-video4linux --disable-linotype --disable-svg

#DFB_CFG += --with-tests

#====================================================================
#jpeg
#====================================================================
INCLUDES := -I$(COMPONENT_DIR)/jpeg/include
LIBJPEG=libjpeg

#====================================================================
#png
#====================================================================
LIBPNG_CFLAGS=-I$(COMPONENT_DIR)/png/include
LIBPNG_LIBS=-lpng

#====================================================================
#freetype
#====================================================================
FREETYPE_CFLAGS=-I$(COMPONENT_DIR)/freetype/include/freetype2
FREETYPE_LIBS=-lfreetype

#===============================================================================
# local variable
#===============================================================================
DIRECTFB_OUT_DIR := $(HI_OUT_DIR)/obj/source/component/directfb
DIRECTFB_OUT_DIR64 := $(HI_OUT_DIR)/obj64/source/component/directfb

INSTALL_DIR := $(DIRECTFB_OUT_DIR)/directfb
INSTALL_DIR64 := $(DIRECTFB_OUT_DIR64)/directfb

ifeq ($(CFG_HI_CPU_ARCH),arm)
FUSION_OUT_DIR := $(DIRECTFB_OUT_DIR)
else
FUSION_OUT_DIR := $(DIRECTFB_OUT_DIR64)
endif

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += directfb
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += directfb64
endif

ifeq ($(CFG_HI_DIRECTFB_MULTI_SUPPORT),y)
TARGETS += fusion
endif

#=====================================================================================
#export env
#=====================================================================================
INCLUDES += -I$(INSTALL_DIR)/include                                      \
            -I$(COMPONENT_DIR)/directfb/OpenSource/include                \
            -I$(COMPONENT_DIR)/directfb/OpenSource/include/fusion         \
            -I$(HI_INCLUDE_DIR)

ifeq ($(HI_USER_SPACE_LIB),y)
INCLUDES += -I$(INSTALL_DIR)/depend_include
LDFLAGS := -L$(INSTALL_DIR)/lib -L$(HI_SHARED_LIB_DIR) -lstdc++
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
INCLUDES += -I$(INSTALL_DIR64)/depend_include
LDFLAGS64 := -L$(INSTALL_DIR64)/lib -L$(HI_SHARED_LIB64_DIR) -lstdc++
endif

CPPFLAGS := $(INCLUDES)

#===================================================================
#CFLAGS
#==================================================================
ifeq ($(CFG_HI_DIRECTFB_CA_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

#CFLAGS += -DCONFIG_HISI_MEM_SUPPORT
CFLAGS += -DCONFIG_HISI_MEMPOOL_SIZE=0x0
#CFLAGS += -DCONFIG_HISI_MEMPOOL_SIZE=0x1900000

CFLAGS += -DCONFIG_DFB_SUPPORT_REGIONUPDATA

CFLAGS += -DCONFIG_DFB_SUPPORT_FENCE
#CFLAGS += -DCONFIG_DFB_DISCARD_FRAME

ifeq ($(CFG_HI_OPENTV5_SUPPORT),y)
   CFLAGS += -DCONFIG_GFX_DFB_OPTV5_SUPPORT

   ifneq ($(CFG_HI_DAC_CVBS),)
   CFLAGS += -DHI_DAC_CVBS=$(CFG_HI_DAC_CVBS)
   endif

   ifneq ($(CFG_HI_DAC_YPBPR_Y),)
   CFLAGS += -DHI_DAC_YPBPR_Y=$(CFG_HI_DAC_YPBPR_Y)
   endif

   ifneq ($(CFG_HI_DAC_YPBPR_PB),)
   CFLAGS += -DHI_DAC_YPBPR_PB=$(CFG_HI_DAC_YPBPR_PB)
   endif

  ifneq ($(CFG_HI_DAC_YPBPR_PR),)
  CFLAGS += -DHI_DAC_YPBPR_PR=$(CFG_HI_DAC_YPBPR_PR)
  endif
endif

#CXXFLAGS := -fno-rtti $(CFLAGS)
CXXFLAGS := $(CFLAGS)
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean directfb directfb64 fusion fusion_clean

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)cp -rf  $(INSTALL_DIR)/usr/include/directfb $(HI_INCLUDE_DIR)/
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)test -d $(HI_EXTERN_LIB_DIR) || mkdir -p $(HI_EXTERN_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/usr/lib/lib*.so*  $(HI_SHARED_LIB_DIR)/
	$(AT)rm -rf $(INSTALL_DIR)/usr/lib/$(DFB_ADP_LIB_VER)/systems/libdirectfb_dummy*
	$(AT)cp -rf $(INSTALL_DIR)/usr/lib/$(DFB_ADP_LIB_VER) $(HI_EXTERN_LIB_DIR)
	$(AT)find $(HI_EXTERN_LIB_DIR)/$(DFB_ADP_LIB_VER)/ -name *.la | xargs rm -rf
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)cp -rf  $(INSTALL_DIR64)/usr/include/directfb $(HI_INCLUDE_DIR)/
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)test -d $(HI_EXTERN_LIB64_DIR) || mkdir -p $(HI_EXTERN_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/usr/lib/lib*.so*  $(HI_SHARED_LIB64_DIR)/
	$(AT)rm -rf $(INSTALL_DIR64)/usr/lib/$(DFB_ADP_LIB_VER)/systems/libdirectfb_dummy*
	$(AT)cp -rf $(INSTALL_DIR64)/usr/lib/$(DFB_ADP_LIB_VER)  $(HI_EXTERN_LIB64_DIR)
	$(AT)find $(HI_EXTERN_LIB64_DIR)/$(DFB_ADP_LIB_VER)/ -name *.la | xargs rm -rf
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64)
	$(AT)rm -rf $(DIRECTFB_OUT_DIR) $(DIRECTFB_OUT_DIR64)
	$(AT)rm -rf $(HI_INCLUDE_DIR)/directfb
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libdirect*.so*
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libfusion*.so*
	$(AT)rm -rf $(HI_EXTERN_LIB_DIR)/directfb-1.6-0
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libdirect*.so*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libfusion*.so*
	$(AT)rm -rf $(HI_EXTERN_LIB64_DIR)/directfb-1.6-0

directfb: $(DIRECTFB_OUT_DIR)/$(DIRECTFB)/tar
	$(AT)cd $(DIRECTFB_OUT_DIR)/$(DIRECTFB) && make DESTDIR=$(INSTALL_DIR) install

directfb64: $(DIRECTFB_OUT_DIR64)/$(DIRECTFB)/tar
	$(AT)cd $(DIRECTFB_OUT_DIR64)/$(DIRECTFB) && make DESTDIR=$(INSTALL_DIR64) install

$(DIRECTFB_OUT_DIR)/$(DIRECTFB)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(INSTALL_DIR)/depend_include || mkdir -p $(INSTALL_DIR)/depend_include
	$(AT)test -d $(DIRECTFB_OUT_DIR)/$(DIRECTFB) || tar xf $(OPEN_SOURCE_DIR)/$(DIRECTFB).tar.gz -C $(DIRECTFB_OUT_DIR)
#	$(AT)cp -rf $(MSP_DIR)/drv/hifb/include/hifb.h     OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_type.h        OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_common.h      OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_debug.h       OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_module.h      OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_ecs.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_error_mpi.h      OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_frontend.h   OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_frontend.h   OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_i2c.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_gpio.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_ir.h         OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_pmoc.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_keyled.h     OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_wdg.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_otp.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_type.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_errcode.h    OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_api.h        OpenSource/include
#	$(AT)cp -rf OpenSource/include/*.h $(INSTALL_DIR)/depend_include
	$(AT)cp -rf OpenSource/$(PATCH_DIR)/* $(DIRECTFB_OUT_DIR)/$(DIRECTFB)/
	$(AT)cd $(DIRECTFB_OUT_DIR)/$(DIRECTFB) && sh ./configure --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --prefix=/usr --build=x86 $(DFB_CFG) CFLAGS="$(CFLAGS)" LIBJPEG="$(LIBJPEG)" LIBPNG_CFLAGS="$(LIBPNG_CFLAGS)" LIBPNG_LIBS="$(LIBPNG_LIBS)" FREETYPE_CFLAGS="$(FREETYPE_CFLAGS)" FREETYPE_LIBS="$(FREETYPE_LIBS)" INCLUDES="$(INCLUDES)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CXXFLAGS="$(CXXFLAGS)" CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

$(DIRECTFB_OUT_DIR64)/$(DIRECTFB)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(INSTALL_DIR64)/depend_include || mkdir -p $(INSTALL_DIR64)/depend_include
	$(AT)test -d $(DIRECTFB_OUT_DIR64)/$(DIRECTFB) || tar xf $(OPEN_SOURCE_DIR)/$(DIRECTFB).tar.gz -C $(DIRECTFB_OUT_DIR64)
#	$(AT)cp -rf $(MSP_DIR)/drv/hifb/include/hifb.h     OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_type.h        OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_common.h      OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_debug.h       OpenSource/include
#	$(AT)cp -rf $(COMMON_DIR)/include/hi_module.h      OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_ecs.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_error_mpi.h      OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_frontend.h   OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_frontend.h   OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_i2c.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_gpio.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_ir.h         OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_pmoc.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_keyled.h     OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_wdg.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/include/hi_unf_otp.h        OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_type.h       OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_errcode.h    OpenSource/include
#	$(AT)cp -rf $(MSP_DIR)/api/tde/include/hi_tde_api.h        OpenSource/include
#	$(AT)cp -rf OpenSource/include/*.h $(INSTALL_DIR64)/depend_include
	$(AT)cp -rf OpenSource/$(PATCH_DIR)/* $(DIRECTFB_OUT_DIR64)/$(DIRECTFB)/
	$(AT)cd $(DIRECTFB_OUT_DIR64)/$(DIRECTFB) && sh ./configure --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --prefix=/usr --build=x86 $(DFB_CFG) CFLAGS="$(CFLAGS)" LIBJPEG="$(LIBJPEG)" LIBPNG_CFLAGS="$(LIBPNG_CFLAGS)" LIBPNG_LIBS="$(LIBPNG_LIBS)" FREETYPE_CFLAGS="$(FREETYPE_CFLAGS)" FREETYPE_LIBS="$(FREETYPE_LIBS)" INCLUDES="$(INCLUDES)" LDFLAGS="$(LDFLAGS64)" CPPFLAGS="$(CPPFLAGS)" CXXFLAGS="$(CXXFLAGS)" CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

fusion: $(FUSION_OUT_DIR)/$(FUSION)/tar
	$(AT)make -C $(FUSION_OUT_DIR)/$(FUSION) SDK_DIR=$(SDK_DIR) FUSION_DIR=$(FUSION_OUT_DIR)/$(FUSION)

$(FUSION_OUT_DIR)/$(FUSION)/tar:
	$(AT)test -d $(FUSION_OUT_DIR) || mkdir -p $(FUSION_OUT_DIR)
	$(AT)test -d $(FUSION_OUT_DIR)/$(FUSION) || tar xf $(OPEN_SOURCE_DIR)/$(FUSION).tar.gz -C $(FUSION_OUT_DIR)
	$(AT)cp -rf  OpenSource/patch-fusion/*    $(FUSION_OUT_DIR)/$(FUSION)/
	$(AT)cp fusion.mak $(FUSION_OUT_DIR)/$(FUSION)/Makefile
	$(AT)cp -rf $(FUSION_OUT_DIR)/$(FUSION)/linux/drivers/char/fusion/debug.h $(FUSION_OUT_DIR)/$(FUSION)/linux/drivers/char/fusion/single
	$(AT)touch $@

fusion_clean:
	$(AT)rm -rf $(FUSION_OUT_DIR)/$(FUSION)
