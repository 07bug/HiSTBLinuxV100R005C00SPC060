#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# png name and version
#===============================================================================
LIBPNG_TAG  := libpng-1.6.32.tar.gz
LIBPNG_NAME := libpng-1.6.32
LIBPNG_PATH_SRC := patch/patch_linux_1.6.32

#===============================================================================
# png patch
#===============================================================================
LIBPNG_PATH_FOR_SRC := patch/patch
LIBPNG_PATH_INCLUDE := include

#===============================================================================
# local variable
#===============================================================================
PNG_OUT_DIR := $(HI_OUT_DIR)/obj/source/component/png
PNG_OUT_DIR64 := $(HI_OUT_DIR)/obj64/source/component/png

INSTALL_DIR := $(PNG_OUT_DIR)/png
INSTALL_DIR64 := $(PNG_OUT_DIR64)/png


ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += libpng
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += libpng64
endif

#=====================================================================================
#export env
#=====================================================================================
ifeq ($(HI_USER_SPACE_LIB),y)
INCLUDES := -I$(INSTALL_DIR)/include
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
INCLUDES := -I$(INSTALL_DIR64)/include
endif

INCLUDES += -I$(COMPONENT_DIR)/png/include          \
            -I$(COMPONENT_DIR)/png/patch/patch      \
            -I$(MSP_DIR)/api/png/include            \
            -I$(MSP_DIR)/api/png/png-hal/src_hard   \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc       \
            -I$(MSP_DIR)/drv/png/include            \
            -I$(COMMON_DIR)/include                 \
            -I$(MSP_DIR)/drv/include                \
            -I$(COMMON_DIR)/api/include             \
            -I$(COMPONENT_DIR)/zlib/include

#===================================================================
#CFLAGS
#==================================================================
#CFLAGS := -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)
CFLAGS := $(subst -Werror,,$(CFG_HI_CFLAGS))

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv310 hi3716mv320 hi3110ev500 hi3716mv430),)
CFLAGS += -DHIPNG_ACCELERATE
else
CFLAGS += -DCONFIG_GFX_PNG_MINI_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv450 hi3716mv430),)
CFLAGS += -DCONFIG_GFX_MEM_ION
else
CFLAGS += -DCONFIG_GFX_MEM_MMZ
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
CFLAGS += -DHI_SMMU_SUPPORT
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_SUPPORT
else
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

ifeq ($(CFG_HI_GFX_DEBUG_LOG_SUPPORT), y)
CFLAGS += -DCFG_HI_GFX_DEBUG_LOG_SUPPORT
endif

ifdef CFG_HI_STATIC_LIB_ONLY
CFLAGS += -fPIC
endif

#self compile selection
ifdef CFG_HI_ADVCA_FUNCTION
#CFLAGS += -fstack-protector --param ssp-buffer-size=4
#CFLAGS += -Wformat -Wformat-security -g0 -s
#CFLAGS += -Wl,-z,relro
endif
ifeq ($(CFG_HI_OPTM_SIZE_SUPPORT),y)
#CFLAGS += -Os -ffunction-sections
endif

CFLAGS += $(INCLUDES)

LDFLAGS := -Wl,-z,relro
LDFLAGS += -Wl,-z,noexecstack

EXT_CFLAGS := --enable-fast-install=no
EXT_CFLAGS += --enable-hardware-optimizations=no
EXT_CFLAGS += --enable-arm-neon=no
EXT_CFLAGS += --enable-mips-msa=no
EXT_CFLAGS += --enable-intel-sse=no
EXT_CFLAGS += --enable-powerpc-vsx=no

#===============================================================================
# api include
#===============================================================================
HEADER_FILES := $(COMPONENT_DIR)/png/include/png.h
HEADER_FILES += $(COMPONENT_DIR)/png/include/pngconf.h
HEADER_FILES += $(COMPONENT_DIR)/png/include/pnglibconf.h
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean libpng libpng64 $(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -rf $(HEADER_FILES) $(HI_INCLUDE_DIR)/
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/lib*png*.so* $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/lib*png*.a*  $(HI_STATIC_LIB_DIR)
	$(AT)cd $(HI_STATIC_LIB_DIR) && ln -sf libpng16.a libpng.a
	$(AT)cd $(HI_SHARED_LIB_DIR) && ln -sf libpng16.so libpng.so
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*png*.so* $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/lib*png*.a*  $(HI_STATIC_LIB64_DIR)
	$(AT)cd $(HI_STATIC_LIB64_DIR) && ln -sf libpng16.a libpng.a
	$(AT)cd $(HI_SHARED_LIB64_DIR) && ln -sf libpng16.so libpng.so
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64)
	$(AT)rm -rf $(PNG_OUT_DIR) $(PNG_OUT_DIR64)
	$(AT)rm -rf $(HI_INCLUDE_DIR)/png.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/pngconf.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/pnglibconf.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/lib*png*.so*
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/lib*png*.a*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/lib*png*.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/lib*png*.a*
	$(AT)rm -rf $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar
	$(AT)rm -rf $(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar

libpng: $(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar
	$(AT)cd $(PNG_OUT_DIR)/$(LIBPNG_NAME) && make install-libLTLIBRARIES

libpng64: $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar
	$(AT)cd $(PNG_OUT_DIR64)/$(LIBPNG_NAME) && make install-libLTLIBRARIES

$(PNG_OUT_DIR)/$(LIBPNG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(PNG_OUT_DIR)/$(LIBPNG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBPNG_TAG) -C $(PNG_OUT_DIR)
	$(AT)cp -rf $(LIBPNG_PATH_INCLUDE)/*        $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH_SRC)/*            $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH_FOR_SRC)/*files*  $(PNG_OUT_DIR)/$(LIBPNG_NAME)/
	$(AT)cd $(PNG_OUT_DIR)/$(LIBPNG_NAME) && sh ./configure --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR) --build=x86 $(EXT_CFLAGS) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

$(PNG_OUT_DIR64)/$(LIBPNG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(PNG_OUT_DIR64)/$(LIBPNG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBPNG_TAG) -C $(PNG_OUT_DIR64)
	$(AT)cp -rf $(LIBPNG_PATH_INCLUDE)/*        $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH_SRC)/*            $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cp -rf $(LIBPNG_PATH_FOR_SRC)/*files*  $(PNG_OUT_DIR64)/$(LIBPNG_NAME)/
	$(AT)cd $(PNG_OUT_DIR64)/$(LIBPNG_NAME) && sh ./configure --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR64) --build=x86 $(EXT_CFLAGS) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS64)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@
