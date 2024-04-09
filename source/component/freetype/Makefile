#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
FREETYPE := freetype-2.8

#CFLAGS := -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)
CFLAGS := $(subst -Werror,,$(CFG_HI_CFLAGS))

#self compile selection
ifdef CFG_HI_ADVCA_FUNCTION
#CFLAGS += -fstack-protector --param ssp-buffer-size=4
#CFLAGS += -Wformat -Wformat-security -g0 -s
#CFLAGS += -Wl,-z,relro
endif
ifeq ($(CFG_HI_OPTM_SIZE_SUPPORT),y)
#CFLAGS += -Os -ffunction-sections
endif

##当高安选项打开时，由于高安要求SDK api不编译静态库，所以SDK顶层Makefile中把-fPIC去掉了，但对于字体库来说，希望能使用动态库，所以要编译时要通过此判断增加-fPIC
ifneq ($(findstring -fPIC, $(CFG_HI_CFLAGS)), -fPIC)
CFLAGS += -fPIC
endif

FREETYPE_DIR := $(HI_OUT_DIR)/obj/source/component/freetype
INSTALL_DIR := $(FREETYPE_DIR)/release

FREETYPE_DIR64 := $(HI_OUT_DIR)/obj64/source/component/freetype
INSTALL_DIR64 := $(FREETYPE_DIR64)/release

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += freetype
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += freetype64
endif


FREETYPE_CFG :=

ifeq ($(CFG_HI_FREETYPE_MINI_SUPPORT),y)
FREETYPE_CFG += --disable-option-checking
FREETYPE_CFG += --disable-FEATURE
FREETYPE_CFG += --disable-FEATURE
FREETYPE_CFG += --disable-fast-install
FREETYPE_CFG += --disable-libtool-lock
FREETYPE_CFG += --with-old-mac-fonts=no
FREETYPE_CFG += --with-fsspec=no
FREETYPE_CFG += --with-fsref=no
FREETYPE_CFG += --with-quickdraw-toolbox=no
FREETYPE_CFG += --with-quickdraw-carbon=no
FREETYPE_CFG += --with-ats=no
endif
FREETYPE_CFG += --enable-shared --enable-static
FREETYPE_CFG += --with-zlib=no
FREETYPE_CFG += --with-bzip2==no
FREETYPE_CFG += --with-png=no
FREETYPE_CFG += --with-harfbuzz=no

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean freetype freetype64

all: $(TARGETS)
	$(AT)test -d $(HI_INCLUDE_DIR) || mkdir -p $(HI_INCLUDE_DIR)
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)cp -rf $(INSTALL_DIR)/include/freetype2 $(HI_INCLUDE_DIR)/
else ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)cp -rf $(INSTALL_DIR64)/include/freetype2 $(HI_INCLUDE_DIR)/
endif
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(HI_STATIC_LIB_DIR) || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)test -d $(HI_SHARED_LIB_DIR) || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libfreetype.a $(HI_STATIC_LIB_DIR)/
	$(AT)cp -ralf $(INSTALL_DIR)/lib/libfreetype.so* $(HI_SHARED_LIB_DIR)/
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_STATIC_LIB64_DIR) || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)test -d $(HI_SHARED_LIB64_DIR) || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libfreetype.a $(HI_STATIC_LIB64_DIR)/
	$(AT)cp -ralf $(INSTALL_DIR64)/lib/libfreetype.so* $(HI_SHARED_LIB64_DIR)/
endif

clean:
	$(AT)rm -rf $(INSTALL_DIR) $(INSTALL_DIR64) $(FREETYPE_DIR)/$(FREETYPE) $(FREETYPE_DIR64)/$(FREETYPE)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/libfreetype.a $(HI_SHARED_LIB_DIR)/libfreetype.so*
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/libfreetype.a $(HI_SHARED_LIB64_DIR)/libfreetype.so*

freetype: $(FREETYPE_DIR)/$(FREETYPE)/tar
	$(AT)mkdir -p $(INSTALL_DIR)/include/freetype2/freetype/config
	$(AT)cd $(FREETYPE_DIR)/$(FREETYPE) && make && make install

freetype64: $(FREETYPE_DIR64)/$(FREETYPE)/tar
	$(AT)mkdir -p $(INSTALL_DIR64)/include/freetype2/freetype/config
	$(AT)cd $(FREETYPE_DIR64)/$(FREETYPE) && make && make install

$(FREETYPE_DIR)/$(FREETYPE)/tar:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)test -d $(FREETYPE_DIR)/$(FREETYPE) || tar xf $(OPEN_SOURCE_DIR)/$(FREETYPE).tar.gz -C $(FREETYPE_DIR)
ifeq ($(CFG_HI_FREETYPE_MINI_SUPPORT),y)
	$(AT)cp -rf $(COMPONENT_DIR)/freetype/patch-for-freetype/* $(FREETYPE_DIR)/$(FREETYPE)
endif
	$(AT)cd $(FREETYPE_DIR)/$(FREETYPE) && chmod -R 777 builds/unix && sh ./configure CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump --host=$(CFG_HI_ARM_TOOLCHAINS_NAME) $(FREETYPE_CFG) CFLAGS="$(CFLAGS) -Wno-error" --prefix=$(INSTALL_DIR)
	$(AT)touch $@

$(FREETYPE_DIR64)/$(FREETYPE)/tar:
	$(AT)test -d $(INSTALL_DIR64) || mkdir -p $(INSTALL_DIR64)
	$(AT)test -d $(FREETYPE_DIR64)/$(FREETYPE) || tar xf $(OPEN_SOURCE_DIR)/$(FREETYPE).tar.gz -C $(FREETYPE_DIR64)
ifeq ($(CFG_HI_FREETYPE_MINI_SUPPORT),y)
	$(AT)cp -rf $(COMPONENT_DIR)/freetype/patch-for-freetype/* $(FREETYPE_DIR64)/$(FREETYPE)
endif
	$(AT)cd $(FREETYPE_DIR64)/$(FREETYPE) && chmod -R 777 builds/unix && sh ./configure CC=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-as LD=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-objdump --host=$(CFG_HI_AARCH64_TOOLCHAINS_NAME) $(FREETYPE_CFG) CFLAGS="$(CFLAGS -Wno-error)" --prefix=$(INSTALL_DIR64)
	$(AT)touch $@
