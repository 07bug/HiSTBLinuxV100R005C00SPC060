#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# jpeg name and version
#===============================================================================
#LIBJPEG_TAG  := jpegsrc.v6b.tar.gz
#LIBJPEG_NAME := jpeg-6b
#LIBJPEG_PATH_SRC := patch/patch_linux_6b

#===============================================================================
# jpeg name and version
#===============================================================================
LIBJPEG_TAG  := libjpeg-turbo-1.5.2.tar.gz
LIBJPEG_NAME := libjpeg-turbo-1.5.2
LIBJPEG_PATH_SRC := patch/patch_turbo_1.5.2

CFG_TURBO_LIB_SUPPORT := y
#===============================================================================
# jpeg patch
#===============================================================================
LIBJPEG_PATH_FOR_SRC := patch/patch
LIBJPEG_PATH_INCLUDE := include

#===============================================================================
# local variable
#===============================================================================
JPEG_OUT_DIR := $(HI_OUT_DIR)/obj/source/component/jpeg
JPEG_OUT_DIR64 := $(HI_OUT_DIR)/obj64/source/component/jpeg

INSTALL_DIR := $(JPEG_OUT_DIR)/jpeg
INSTALL_DIR64 := $(JPEG_OUT_DIR64)/jpeg

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += libjpeg
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += libjpeg64
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

INCLUDES += -I$(COMPONENT_DIR)/jpeg/include          \
            -I$(COMPONENT_DIR)/jpeg/patch/patch      \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/inc_hard  \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_comm  \
            -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_soft  \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc        \
            -I$(MSP_DIR)/api/jpeg/include            \
            -I$(MSP_DIR)/drv/jpeg/include            \
            -I$(MSP_DIR)/api/tde/include             \
            -I$(MSP_DIR)/drv/include                 \
            -I$(COMMON_DIR)/include                  \
            -I$(COMMON_DIR)/api/include

#===================================================================
#CFLAGS
#==================================================================
#CFLAGS := -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)
CFLAGS := $(subst -Werror,,$(CFG_HI_CFLAGS))

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_SUPPORT
else
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

ifeq ($(CFG_HI_JPEG_MINI_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_JPEG_MINI_SUPPROT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450 hi3716mv430 hi3798mv310),)
CFLAGS += -DCONFIG_GFX_MEM_ION
else
CFLAGS += -DCONFIG_GFX_MEM_MMZ
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
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

ifdef CFG_HI_STATIC_LIB_ONLY
#directfb needed
CFLAGS += -fPIC
endif

CFLAGS += $(INCLUDES)

EXT_CFLAGS := --without-arith-enc --without-arith-dec
EXT_CFLAGS += --with-12bit=no
EXT_CFLAGS += --without-simd
ifneq ($(CFG_TURBO_LIB_SUPPORT),y)
EXT_CFLAGS += --without-turbojpeg
endif

#self compile selection
LDFLAGS := -Wl,-z,relro
LDFLAGS += -Wl,-z,noexecstack

#===============================================================================
# api include
#===============================================================================
HEADER_FILES := $(COMPONENT_DIR)/jpeg/include/jpeglib.h
HEADER_FILES += $(COMPONENT_DIR)/jpeg/include/jmorecfg.h
HEADER_FILES += $(COMPONENT_DIR)/jpeg/include/jerror.h
HEADER_FILES += $(COMPONENT_DIR)/jpeg/include/jconfig.h
#HEADER_FILES += $(COMPONENT_DIR)/jpeg/include/turbojpeg.h
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean libjpeg libjpeg64 $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/tar $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/tar

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
	$(AT)cp -rf $(HEADER_FILES) $(HI_INCLUDE_DIR)/
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libjpeg*.so* $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libjpeg*.a*  $(HI_STATIC_LIB_DIR)
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libjpeg.so*  $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libjpeg.a*   $(HI_STATIC_LIB64_DIR)
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR)  $(INSTALL_DIR64)
	$(AT)rm -rf $(JPEG_OUT_DIR) $(JPEG_OUT_DIR64)
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jpeglib.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jmorecfg.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jerror.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/jconfig.h
	$(AT)rm -rf $(HI_INCLUDE_DIR)/turbojpeg.h
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libjpeg*.so*
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/libturbo*.so*
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libjpeg*.a*
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libturbo*.a*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libjpeg*.so*
	$(AT)rm -rf $(HI_SHARED_LIB64_DIR)/libbturbo*.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libjpeg*.a*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libturbo*.a*
	$(AT)rm -rf $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/tar
	$(AT)rm -rf $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/tar

libjpeg: $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/tar
	$(AT)cd $(JPEG_OUT_DIR)/$(LIBJPEG_NAME) && make && make install

libjpeg64: $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/tar
	$(AT)cd $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME) && make && make install

$(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(JPEG_OUT_DIR)/$(LIBJPEG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBJPEG_TAG) -C $(JPEG_OUT_DIR)
	$(AT)cp -rf $(LIBJPEG_PATH_SRC)/*            $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/
	$(AT)cp -rf $(LIBJPEG_PATH_FOR_SRC)/*files*  $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/
	$(AT)cp -rf $(LIBJPEG_PATH_INCLUDE)/*        $(JPEG_OUT_DIR)/$(LIBJPEG_NAME)/
	$(AT)cd $(JPEG_OUT_DIR)/$(LIBJPEG_NAME) && sh ./configure --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR) --build=x86 $(EXT_CFLAGS) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@

$(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME) || tar xf $(OPEN_SOURCE_DIR)/$(LIBJPEG_TAG) -C $(JPEG_OUT_DIR64)
	$(AT)cp -rf $(LIBJPEG_PATH_SRC)/*            $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/
	$(AT)cp -rf $(LIBJPEG_PATH_FOR_SRC)/*files*  $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/
	$(AT)cp -rf $(LIBJPEG_PATH_INCLUDE)/*        $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME)/
	$(AT)cd $(JPEG_OUT_DIR64)/$(LIBJPEG_NAME) && sh ./configure --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR64) --build=x86 $(EXT_CFLAGS) CFLAGS="$(CFLAGS)" LDFLAGS="$(LDFLAGS64)" CPPFLAGS="$(CPPFLAGS)" CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump
	$(AT)touch $@
