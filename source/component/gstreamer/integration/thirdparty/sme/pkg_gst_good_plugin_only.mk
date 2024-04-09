LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pkg_gst_good

#EXT_TYPE_GZ := tar.gz
EXT_TYPE_XZ := tar.xz
PKG_GST_GOOD_NAME := gst-plugins-good-1.10.4

LOCAL_INTERMEDIATE_TARGETS := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE) \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_prepare \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_configure \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_make \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_GST_GOOD_NAME_PREPARE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_prepare
PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_configure
PRIVATE_PKG_GST_GOOD_NAME_MAKE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_make
PRIVATE_PKG_GST_GOOD_NAME_INSTALL := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)_install
ifeq ($(ENV_SME_VERSION_TYPE), rls)
$(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE): PRIVATE_PKG_GST_GOOD_DBG_FLG := --disable-debug
else
$(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE): PRIVATE_PKG_GST_GOOD_DBG_FLG := --enable-debug
endif

PRIVATE_PKG_GST_GOOD_DEPS := pkg_gst_base-deps pkg_gnutls

$(LOCAL_MODULE)-deps: $(PRIVATE_PKG_GST_GOOD_DEPS) $(LOCAL_MODULE)

$(LOCAL_MODULE): $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE)

$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_GST_GOOD_NAME_INSTALL)

$(PRIVATE_PKG_GST_GOOD_NAME_INSTALL):$(PRIVATE_PKG_GST_GOOD_NAME_MAKE)
	$(NS)echo "begin INSTALL $(PKG_GST_GOOD_NAME)!"
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/gstreamer-1.0/libgst*.so $(TARGET_OUT_PLUGIN_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	#$(TARGET_STRIP) $(TARGET_OUT_PLUGIN_DIR)/libgstdashdemux.so
endif
	$(NS)echo "end INSTALL $(PKG_GST_GOOD_NAME)!"

$(PRIVATE_PKG_GST_GOOD_NAME_MAKE):$(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE)
	$(NS)echo "begin make $(PKG_GST_GOOD_NAME)!"
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME) $(MAKE_PARALLEL)
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME) install $(MAKE_PARALLEL)
	$(NS)echo "end make $(PKG_GST_GOOD_NAME)!"


ifeq ($(CFG_ENABLE_NDK), y)
GST_GOOD_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(CFG_COMPILE_SYSROOT)/usr/lib -L$(THIRDPARTY_OBJ_DIR)/lib
else
GST_GOOD_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)
endif

$(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE):$(PRIVATE_PKG_GST_GOOD_NAME_PREPARE)
	$(NS)echo "begin configure $(PKG_GST_GOOD_NAME)..."
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)/configure
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME);ac_cv_path_install="/usr/bin/install -cp" ./configure --prefix="${THIRDPARTY_OBJ_DIR}" \
		--host=$(CFG_HOST_TYPE) \
		CFLAGS="$(OPENSOURCE_CFLAGS) --sysroot=$(CFG_COMPILE_SYSROOT)" \
		CXXFLAGS="$(OPENSOURCE_CXXFLAGS)" \
		--disable-static --enable-shared --disable-static-plugins \
		--disable-orc --disable-examples \
		$(PRIVATE_PKG_GST_GOOD_DBG_FLG) --disable-benchmarks\
		--disable-multifile --disable-gst_v4l2 --disable-x --disable-jpeg \
		--disable-png --disable-cairo \
		--disable-libpng --disable-libcaca --disable-gdk_pixbuf \
		$(PRIVATE_PKG_HLS_CONFIG_FLG) \
		$(PRIVATE_PKG_DASH_CONFIG_FLG) \
		ZLIB_CFLAGS="$(CFG_ZLIB_CFLAGS)" ZLIB_LIBS="$(CFG_ZLIBS)" \
		LDFLAGS="$(GST_GOOD_LDFLAGS) -Wl,-rpath-link=$(THIRDPARTY_OBJ_DIR)/lib" LIBS="-lz" \
		--with-pkg-config-path=$(THIRDPARTY_PKG_CONFIG_DIR) \
		CXX=$(TARGET_CXX) CC=$(TARGET_CC)
	-$(NS)cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME);sed -i 's/m4 common docs tests po tools/m4 common/g' `grep 'm4 common docs tests po tools' -rl Makefile`
	$(NS)touch $@
	$(NS)echo "end configure $(PKG_GST_GOOD_NAME)..."

$(PRIVATE_PKG_GST_GOOD_NAME_PREPARE):
	$(NS)echo "begin prepare $(PKG_GST_GOOD_NAME)..."
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)
	$(NC)mkdir -p $(SME_THIRDPARTY_MERGE_DIR)
	tar -xf $(SME_THIRDPARTY_ORG_DIR)/../../../../../../third_party/open_source/$(PKG_GST_GOOD_NAME).$(EXT_TYPE_XZ) -C $(SME_THIRDPARTY_MERGE_DIR)
	$(NC)cp -af $(SME_THIRDPARTY_PATCH_DIR)/$(PKG_GST_GOOD_NAME) $(SME_THIRDPARTY_MERGE_DIR)/
	$(NS)touch $@
	$(NS)echo "end prepare $(PKG_GST_GOOD_NAME)!"

$(LOCAL_MODULE)-clean:
	$(NS)echo "begin make clean $(PKG_GST_GOOD_NAME) ..."
	#$(NC)rm -rf $(TARGET_OUT_PLUGIN_DIR)/libgst.so
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME) uninstall $(MAKE_PARALLEL)
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME) clean $(MAKE_PARALLEL)
	$(NS)echo "end make clean $(PKG_GST_GOOD_NAME)"

$(LOCAL_MODULE)-cfg-clean:
	$(NS)echo "begin make clean $(PKG_GST_GOOD_NAME)-cfg ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE)
	$(NS)echo "end make clean $(PKG_GST_GOOD_NAME)-cfg ..."

$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
	$(NS)echo "begin make clean $(PKG_GST_GOOD_NAME)-prepare ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_GOOD_NAME_CONFIGURE)
	$(NC)rm -rf $(PRIVATE_PKG_GST_GOOD_NAME_PREPARE)
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_GOOD_NAME)
	$(NS)echo "end make clean $(PKG_GST_GOOD_NAME)-prepare ..."

include $(BUILD_OPENSOURCE_PKG)
