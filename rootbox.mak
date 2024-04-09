#===============================================================================
# local variables
#===============================================================================
ifeq ($(CFG_HI_LOG_SUPPORT),)
OUTPUT_FILE := > /dev/null 2>&1
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFG_HI_TEE_TA_LOAD_PATH ?= /usr/lib/ta
endif

ifeq ($(CFG_HI_ADVCA_SANDBOX_SUPPORT),y)
SANDBOX_TYPE := $(shell echo $(CFG_HI_ADVCA_SANDBOX_TYPE) | tr "[A-Z]" "[a-z]")
ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
CA_ROOTBOX_BUILD := $(ROOTFS_SRC_DIR)/scripts/hica_build/lxc_advance
else
CA_ROOTBOX_BUILD := $(ROOTFS_SRC_DIR)/scripts/hica_build/$(SANDBOX_TYPE)
endif
CA_ROOTBOX_LOADER_BUILD := $(ROOTFS_SRC_DIR)/scripts/hica_build/$(SANDBOX_TYPE)

ifdef CFG_HI_ADVCA_FUNCTION
CA_ROOTBOX_MODE := $(CFG_HI_ADVCA_FUNCTION)
else
CA_ROOTBOX_MODE := DEBUG
endif
endif

ifeq ($(CFG_HI_ROOTFS_STRIP),y)
SANDBOX_STRIP_SUPPORT := STRIP_OPEN
else
SANDBOX_STRIP_SUPPORT := STRIP_CLOSE
endif

#===============================================================================
# rule
#===============================================================================
.PHONY: rootbox_compose

rootbox_compose:
	$(AT)make -C $(HI_SCRIPTS_DIR) all
	$(AT)rm -rf $(HI_ROOTBOX_DIR)
	$(AT)cp -arf $(HI_ROOTFS_DIR) $(HI_ROOTBOX_DIR)
	$(AT)cp -arf $(HI_MODULE_DIR) $(HI_ROOTBOX_DIR)
ifeq ($(CFG_HI_ROOTFS_INSTALL_SHARED_LIBS),y)
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)cp -arf $(HI_SHARED_LIB_DIR)/*.so* $(HI_ROOTBOX_DIR)/usr/lib
	$(AT)-cp -arf $(HI_EXTERN_LIB_DIR)/* $(HI_ROOTBOX_DIR)/usr/lib/
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(HI_ROOTBOX_DIR)/usr/lib64 || mkdir -p $(HI_ROOTBOX_DIR)/usr/lib64
	$(AT)cp -arf $(HI_SHARED_LIB64_DIR)/*.so* $(HI_ROOTBOX_DIR)/usr/lib64/
	$(AT)-cp -arf $(HI_EXTERN_LIB64_DIR)/* $(HI_ROOTBOX_DIR)/usr/lib64/
endif
endif
ifeq ($(CFG_HI_TEE_SUPPORT),y)
	$(AT)if [[ -d $(HI_TA_IMAGE_DIR) ]] ; then \
		for file in `ls $(HI_TA_IMAGE_DIR)` ; do ( \
			mkdir -p $(HI_ROOTBOX_DIR)/$(CFG_HI_TEE_TA_LOAD_PATH) && cp -arf $(HI_TA_IMAGE_DIR)/$${file} $(HI_ROOTBOX_DIR)/$(CFG_HI_TEE_TA_LOAD_PATH); \
		) done ; \
	fi
endif
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(HI_USER_SPACE_LIB),y)
	-$(AT)cp -arf $(HI_INSTALL_DIR)/obj/source/component/loader/app/release/*   $(HI_ROOTBOX_DIR)/home
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	-$(AT)cp -arf $(HI_INSTALL_DIR)/obj64/source/component/loader/app/release/*   $(HI_ROOTBOX_DIR)/home
endif
	$(AT)if [ -f $(HI_ROOTBOX_DIR)/etc/profile ]; then \
		echo "sleep 3" >> $(HI_ROOTBOX_DIR)/etc/profile; \
		echo "cd /home && ./loader $(OUTPUT_FILE)" >> $(HI_ROOTBOX_DIR)/etc/profile; \
		echo "reboot $(OUTPUT_FILE)" >> $(HI_ROOTBOX_DIR)/etc/profile; \
	fi
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
ifeq ($(CFG_HI_LOG_SUPPORT),y)
	sed -i 's/^::respawn:-\/bin\/sh/::respawn:\/sbin\/getty -L ttyS000 115200 vt100 -n root -a -I "Auto login as root ..."/g' $(HI_ROOTBOX_DIR)/etc/inittab
endif
endif
else
	-$(AT)mknod $(HI_ROOTBOX_DIR)/dev/console c 5 1
	-$(AT)mknod $(HI_ROOTBOX_DIR)/dev/ttyAMA0 c 204 64
	-$(AT)mknod $(HI_ROOTBOX_DIR)/dev/ttyAMA1 c 204 65
	-$(AT)mknod $(HI_ROOTBOX_DIR)/dev/ttyS000 c 204 64
endif
else
ifeq ($(HI_USER_SPACE_LIB),y) 
	$(AT)cp -arf $(HI_SHARED_LIB_DIR)/*freetype.so* $(HI_ROOTBOX_DIR)/usr/lib
	$(AT)cp -arf $(HI_SHARED_LIB_DIR)/libz.so* $(HI_ROOTBOX_DIR)/usr/lib
	$(AT)cp -arf $(HI_EXTERN_LIB_DIR)/*AUDIO* $(HI_ROOTBOX_DIR)/usr/lib/
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
	$(AT)cp -arf $(HI_EXTERN_LIB_DIR)/higo-adp $(HI_ROOTBOX_DIR)/usr/lib/
endif
endif
endif

ifeq ($(CFG_HI_ADVCA_SANDBOX_SUPPORT),y)
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)test -d $(CA_ROOTBOX_LOADER_BUILD)/loader_build || tar xzf $(CA_ROOTBOX_LOADER_BUILD)/loader_build.tar.gz -C $(CA_ROOTBOX_LOADER_BUILD)/
	$(AT)$(CA_ROOTBOX_LOADER_BUILD)/loader_build/MakeCALoaderRootBox.sh $(HI_ROOTBOX_DIR) $(CA_ROOTBOX_MODE) $(CFG_HI_ARM_TOOLCHAINS_NAME)
else
	$(AT)test -d $(CA_ROOTBOX_BUILD)/system_build || tar xzf $(CA_ROOTBOX_BUILD)/system_build.tar.gz -C $(CA_ROOTBOX_BUILD)/
	$(AT)$(CA_ROOTBOX_BUILD)/system_build/MakeCASystemRootBox.sh $(HI_ROOTBOX_DIR) $(CA_ROOTBOX_MODE) $(CFG_HI_ARM_TOOLCHAINS_NAME) $(SANDBOX_STRIP_SUPPORT) $(if $(strip $(findstring y,$(CFG_HI_ETH_SUPPORT))),,no)
endif ####ifeq ($(CFG_HI_LOADER_APPLOADER),y)
endif
ifeq ($(CFG_HI_ROOTFS_STRIP), y)
	-$(AT)find $(HI_ROOTBOX_DIR)/bin/ $(HI_ROOTBOX_DIR)/lib/ $(HI_ROOTBOX_DIR)/sbin/ $(HI_ROOTBOX_DIR)/usr/ | xargs $(STRIP) 2> /dev/null
	-$(AT)find $(HI_ROOTBOX_DIR)/bin/ $(HI_ROOTBOX_DIR)/lib/ $(HI_ROOTBOX_DIR)/sbin/ $(HI_ROOTBOX_DIR)/usr/ | xargs $(STRIP) -R .note -R .comment 2> /dev/null
ifeq ($(HI_USER_SPACE_LIB64),y)
	-$(AT)find $(HI_ROOTBOX_DIR)/bin/ $(HI_ROOTBOX_DIR)/lib/ $(HI_ROOTBOX_DIR)/sbin/ $(HI_ROOTBOX_DIR)/usr/ | xargs $(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip 2> /dev/null
	-$(AT)find $(HI_ROOTBOX_DIR)/bin/ $(HI_ROOTBOX_DIR)/lib/ $(HI_ROOTBOX_DIR)/sbin/ $(HI_ROOTBOX_DIR)/usr/ | xargs $(CFG_HI_AARCH64_TOOLCHAINS_NAME)-strip -R .note -R .comment 2> /dev/null
endif
endif
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)rm -rf $(HI_ROOTBOX_DIR)/opt
	$(AT)rm -rf $(HI_ROOTBOX_DIR)/share
endif
ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
    ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420 hi3716mv450 hi3796mv200),)
		$(AT)mkdir -p $(HI_ROOTBOX_DIR)/mnt/app
		$(AT)mkdir -p $(HI_ROOTBOX_DIR)/mnt/data
    endif
endif
