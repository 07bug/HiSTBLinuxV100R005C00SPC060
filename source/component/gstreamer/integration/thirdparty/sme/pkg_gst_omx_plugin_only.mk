LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pkg_gst_omx

#EXT_TYPE_GZ := tar.gz
EXT_TYPE_XZ := tar.xz
PKG_GST_OMX_NAME := gst-omx-1.10.4

ifeq ($(CFG_ENABLE_NDK), y)
GST_OMX_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(CFG_COMPILE_SYSROOT)/usr/lib -L$(THIRDPARTY_OBJ_DIR)/lib
else
GST_OMX_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)
endif

LOCAL_INTERMEDIATE_TARGETS := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE) \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_prepare \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_configure \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_make \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_GST_OMX_NAME_PREPARE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_prepare
PRIVATE_PKG_GST_OMX_NAME_CONFIGURE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_configure
PRIVATE_PKG_GST_OMX_NAME_MAKE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_make
PRIVATE_PKG_GST_OMX_NAME_INSTALL := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)_install
ifeq ($(ENV_SME_VERSION_TYPE), rls)
$(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE): PRIVATE_PKG_GST_OMX_DBG_FLG := --disable-debug
else
$(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE): PRIVATE_PKG_GST_OMX_DBG_FLG := --enable-debug
endif

PRIVATE_PKG_GST_OMX_DEPS := pkg_gst_base-deps

$(LOCAL_MODULE)-deps: $(PRIVATE_PKG_GST_OMX_DEPS) $(LOCAL_MODULE)

$(LOCAL_MODULE): $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE)

$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_GST_OMX_NAME_INSTALL)

$(PRIVATE_PKG_GST_OMX_NAME_INSTALL):$(PRIVATE_PKG_GST_OMX_NAME_MAKE)
	$(NS)echo "begin INSTALL $(PKG_GST_OMX_NAME)!"
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/gstreamer-1.0/libgstomx.so $(TARGET_OUT_PLUGIN_DIR)/libgstomx.so
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_PLUGIN_DIR)/libgstomx.so
endif
	cp -af $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/config/$(CFG_PROJECT_NAME)/gstomx.conf $(TARGET_OUT_CONFIG_DIR)/gstomx.conf
	$(NS)echo "end INSTALL $(PKG_GST_OMX_NAME)!"

$(PRIVATE_PKG_GST_OMX_NAME_MAKE):$(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE)
	$(NS)echo "begin make $(PKG_GST_OMX_NAME)!"
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME) $(MAKE_PARALLEL)
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME) install $(MAKE_PARALLEL)
	$(NS)echo "end make $(PKG_GST_OMX_NAME)!"

$(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE):$(PRIVATE_PKG_GST_OMX_NAME_PREPARE)
	$(NS)echo "begin configure $(PKG_GST_OMX_NAME)..."
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/autogen.sh
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME); ./autogen.sh --noconfigure
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)/configure
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME);ac_cv_path_install="/usr/bin/install -cp" ./configure --prefix="${THIRDPARTY_OBJ_DIR}" \
		--host=$(CFG_HOST_TYPE) \
		CFLAGS="$(OPENSOURCE_CFLAGS) -DCOMPUTE_OUT_PTS -DFIX_ADD_HEADER -DSME_GST_OMX -DGST_OMX_DDP_DEC_ENABLE -DHACK_CONFIG_DIR --sysroot=$(CFG_COMPILE_SYSROOT) $(PRIVATE_PKG_GST_OMX_CFLAGS) $(foreach h_tmp, $(CFG_RT_OMX_PRIVATE_H) $(CFG_RT_PLATFORM_SDK_INC_DIR), -I$(TOPDIR)/$(h_tmp))" \
		CPPFLAGS="$(OPENSOURCE_CXXFLAGS) $(PRIVATE_PKG_GST_CORE_CXXFLAGS)" \
		LDFLAGS="$(GST_OMX_LDFLAGS) -Wl,-rpath-link=$(THIRDPARTY_OBJ_DIR)/lib" \
		LIBS="-lOMX.hisi.audio.utils -lOMX.hisi.audio.mp3dec -lOMX.hisi.audio.aacdec -lOMX.hisi.audio.ddpdec -lfreetype -lharfbuzz -lhigoadp -lhi_so -lhi_ttx -lhi_subtitle -lhi_msp -lhi_common -lm -lrt -lhi_cc -lhigo -ljpeg -ldl -lpthread -lOMX.hisi.video.decoder -lhal" \
		--disable-static --enable-shared \
		--with-omx-target=generic --disable-valgrind --disable-examples \
		--disable-omx --with-omx-header-path=$(TOPDIR)/$(CFG_RT_OMX_H_DIR) \
		--with-pkg-config-path=$(THIRDPARTY_PKG_CONFIG_DIR) $(PRIVATE_PKG_GST_OMX_DBG_FLG) \
		CXX=$(TARGET_CXX) CC=$(TARGET_CC)
	$(NS)touch $@
	$(NS)echo "end configure $(PKG_GST_OMX_NAME)..."

$(PRIVATE_PKG_GST_OMX_NAME_PREPARE):
	$(NS)echo "begin prepare $(PKG_GST_OMX_NAME)..."
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)
	$(NC)mkdir -p $(SME_THIRDPARTY_MERGE_DIR)
	tar -xf $(SME_THIRDPARTY_ORG_DIR)/../../../../../../third_party/open_source/$(PKG_GST_OMX_NAME).$(EXT_TYPE_XZ) -C $(SME_THIRDPARTY_MERGE_DIR)
	$(NC)cp -af $(SME_THIRDPARTY_PATCH_DIR)/$(PKG_GST_OMX_NAME) $(SME_THIRDPARTY_MERGE_DIR)/
	$(NS)touch $@
	$(NS)echo "end prepare $(PKG_GST_OMX_NAME)!"

$(LOCAL_MODULE)-clean:
	$(NS)echo "begin make clean $(PKG_GST_OMX_NAME) ..."
	$(NC)rm -rf $(TARGET_OUT_PLUGIN_DIR)/libgstomx.so
	$(NC)rm -rf $(TARGET_OUT_CONFIG_DIR)/gstomx.conf
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME) uninstall $(MAKE_PARALLEL)
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME) clean $(MAKE_PARALLEL)
	$(NS)echo "end make clean $(PKG_GST_OMX_NAME)"

$(LOCAL_MODULE)-cfg-clean:
	$(NS)echo "begin make clean $(PKG_GST_OMX_NAME)-cfg ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE)
	$(NS)echo "end make clean $(PKG_GST_OMX_NAME)-cfg ..."

$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
	$(NS)echo "begin make clean $(PKG_GST_OMX_NAME)-prepare ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_OMX_NAME_CONFIGURE)
	$(NC)rm -rf $(PRIVATE_PKG_GST_OMX_NAME_PREPARE)
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_OMX_NAME)
	$(NS)echo "end make clean $(PKG_GST_OMX_NAME)-prepare ..."

include $(BUILD_OPENSOURCE_PKG)
