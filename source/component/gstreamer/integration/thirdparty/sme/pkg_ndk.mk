LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)


ifeq ($(CFG_ENABLE_TOOLCHAIN), y)
SME_TOOLCHAIN_VERSION := arm-linux-androideabi-4.8
else
SME_TOOLCHAIN_VERSION := arm-linux-androideabi-4.6
endif


LOCAL_MODULE := pkg_ndk
ifeq ($(CFG_NDK_VERSION), android_ndk_r9)
EXT_TYPE_BZ2 := tar.bz2
PKG_NDK_NAME := android-ndk-r9d

LOCAL_INTERMEDIATE_TARGETS := $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE) \
	$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)_install \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_NDK_NAME_INSTALL := $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)_install

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)

$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_NDK_NAME_INSTALL)

$(LOCAL_MODULE)-clean:
$(LOCAL_MODULE)-cfg-clean:$(LOCAL_MODULE)-prepare-clean

$(PRIVATE_PKG_NDK_NAME_INSTALL):
	$(NS)echo "begin INSTALL $(PKG_NDK_NAME)..."
	$(NC)rm -rf $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)
	$(NC)mkdir -p $(TOOLCHAIN_EXTRACT_DIR)
	tar -xf $(TOPDIR)/tool/sme/android/$(PKG_NDK_NAME)-linux-x86_64.$(EXT_TYPE_BZ2) -C $(TOOLCHAIN_EXTRACT_DIR)
	$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/build/tools/make-standalone-toolchain.sh --platform=android-14 \
		--toolchain=$(SME_TOOLCHAIN_VERSION) \
		--install-dir=$(TOOLCHAIN_INSTALL_DIR)
	$(NS)touch $@
	$(NS)echo "end INSTALL $(PKG_NDK_NAME)!"

$(LOCAL_MODULE)-prepare-clean:
	$(NS)echo "begin make clean $(PKG_NDK_NAME) ..."
	$(NC)rm -rf $(PRIVATE_PKG_NDK_NAME_INSTALL)
	$(NC)rm -rf $(TOOLCHAIN_EXTRACT_DIR)
	$(NS)echo "end make clean $(PKG_NDK_NAME)"

else

EXT_TYPE_ZIP := zip
PKG_NDK_NAME := android-ndk-r11

#globle
TOOLCHAIN_STL_DIR := $(TOOLCHAIN_INSTALL_DIR)/include/c++/4.9/

LOCAL_INTERMEDIATE_TARGETS := $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE) \
	$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)_install \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_NDK_NAME_INSTALL := $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)_install

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE)

$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_NDK_NAME_INSTALL)

$(LOCAL_MODULE)-clean:
$(LOCAL_MODULE)-cfg-clean:$(LOCAL_MODULE)-prepare-clean

$(PRIVATE_PKG_NDK_NAME_INSTALL):
	$(NS)echo "begin INSTALL $(PKG_NDK_NAME)..."
	$(NC)rm -rf $(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)
	$(NC)mkdir -p $(TOOLCHAIN_EXTRACT_DIR)
	unzip -q $(TOPDIR)/tool/sme/android/$(PKG_NDK_NAME)-linux-x86_64.$(EXT_TYPE_ZIP) -d $(TOOLCHAIN_EXTRACT_DIR)
	$(TOOLCHAIN_EXTRACT_DIR)/$(PKG_NDK_NAME)/build/tools/make-standalone-toolchain.sh --platform=android-21 \
		--toolchain=arm-linux-androideabi-4.9 \
		--install-dir=$(TOOLCHAIN_INSTALL_DIR)
	-cd $(TOOLCHAIN_INSTALL_DIR)/lib/gcc/arm-linux-androideabi/4.9/include; mv stdatomic.h stdatomic.h.bak
	$(NS)touch $@
	$(NS)echo "end INSTALL $(PKG_NDK_NAME)!"

$(LOCAL_MODULE)-prepare-clean:
	$(NS)echo "begin make clean $(PKG_NDK_NAME) ..."
	$(NC)rm -rf $(PRIVATE_PKG_NDK_NAME_INSTALL)
	$(NC)rm -rf $(TOOLCHAIN_EXTRACT_DIR)
	$(NS)echo "end make clean $(PKG_NDK_NAME)"

endif

include $(BUILD_OPENSOURCE_PKG)
