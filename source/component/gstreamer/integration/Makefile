#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

ifndef GST_DIR
#export GST_DIR := $(PWD)
export GST_DIR := $(COMPONENT_DIR)/gstreamer/integration
endif

OUT_DIR := $(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)
ROOT_FS_DIR := $(OUT_DIR)/obj/rootfs

# temp variable ,build release version
gst_build_type := rls
#gst_build_type := dbg
gst_prebuild := false

all: install
	mkdir -p $(OUT_DIR)/include/gstreamer/
	mkdir -p $(OUT_DIR)/lib/share/
	cp -rf $(GST_DIR)/prebuild/lib/* $(OUT_DIR)/lib/share/
	mkdir -p $(ROOT_FS_DIR)/usr/lib
	cp -rf $(GST_DIR)/prebuild/lib/* $(ROOT_FS_DIR)/usr/lib/
	mkdir -p $(ROOT_FS_DIR)/usr/bin/
	cp -rf $(GST_DIR)/prebuild/bin/* $(ROOT_FS_DIR)/usr/bin/
	mkdir -p $(ROOT_FS_DIR)/usr/data/
	cp -rf $(GST_DIR)/prebuild/config/gstomx.conf $(ROOT_FS_DIR)/usr/data/
	mkdir -p $(ROOT_FS_DIR)/data/
	cp -rf $(GST_DIR)/prebuild/config/scenarios $(ROOT_FS_DIR)/data/

	@echo "============ gstreamer all success ============"

gstreamer:
	@echo "============  start complie gstreamer ============ "
ifeq ($(gst_prebuild),false)
	cd $(GST_DIR)/;ln -s ../../../../../ HiSTBLinux; \
	cd $(GST_DIR)/build/sme;pwd; \
	source ./envsetup.sh ./project/histb.linux/plugin_only.cfg.mk $(gst_build_type); \
	make all;
endif

	@echo "============= gstreamer complie success ============"
install: gstreamer
ifeq ($(gst_prebuild),false)
	mkdir -p $(GST_DIR)/prebuild
	mkdir -p $(GST_DIR)/prebuild/lib
	mkdir -p $(GST_DIR)/prebuild/config
	mkdir -p $(GST_DIR)/prebuild/include
	mkdir -p $(GST_DIR)/prebuild/bin
	cp $(GST_DIR)/out/histb.linux.$(CFG_HI_CHIP_TYPE).plugin_only/$(gst_build_type)/lib/* $(GST_DIR)/prebuild/lib -rf
	cp $(GST_DIR)/out/histb.linux.$(CFG_HI_CHIP_TYPE).plugin_only/$(gst_build_type)/config/* $(GST_DIR)/prebuild/config -rf
	cp $(GST_DIR)/out/histb.linux.$(CFG_HI_CHIP_TYPE).plugin_only/$(gst_build_type)/bin/* $(GST_DIR)/prebuild/bin -rf

endif

	@echo "============= gstreamer install success ============"

uninstall: clean
	cd $(GST_DIR); \
	rm -rf prebuild;
	@echo "============ gstreamer uninstall success ============"

clean:
	@echo "============ gstreamer clean start============"
	cd $(GST_DIR); \
	rm -rf out;
	rm HiSTBLinux;
	@echo "============ gstreamer clean success ============"

