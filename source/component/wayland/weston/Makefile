#===============================================================================
# export variable
#===============================================================================
WAYLAND_DIR ?= $(shell cd $(CURDIR)/.. && /bin/pwd)
include $(WAYLAND_DIR)/base.mak

#===============================================================================
# sdk dir
#===============================================================================
include $(SDK_DIR)/base.mak

path_ver := patch/patch-for-weston-3.0.0
WESTON_DIR := $(WL_OUT_DIR)/obj/weston/weston-3.0.0

#===============================================================================
# objects
#===============================================================================
objects :=
objects += weston
objects += patch/hwc-render
objects += patch/pixman-render
objects += patch/gl-render
objects += patch/fbdev-backend

objects_clean := $(addsuffix _clean, $(objects))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#     rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PHONY := all clean

all:${objects}
	$(AT)test -d $(WL_INSTALL_DIR)/.libs || mkdir -p $(WL_INSTALL_DIR)/.libs
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/hwc-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/pixman-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/gl-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/fbdev-backend/libweston/*
	$(AT)cp -rf $(WL_OUT_DIR)/obj/weston/patch/hwc-render/hwc-renderer.so                $(WL_OUT_DIR)/weston/.libs
	$(AT)cp -rf $(WL_OUT_DIR)/obj/weston/patch/pixman-render/pixman-renderer.so          $(WL_OUT_DIR)/weston/.libs
	$(AT)cp -rf $(WL_OUT_DIR)/obj/weston/patch/gl-render/gl-renderer.so                  $(WL_OUT_DIR)/weston/.libs
	$(AT)cp -rf $(WL_OUT_DIR)/obj/weston/patch/fbdev-backend/fbdev-backend.so            $(WL_OUT_DIR)/weston/.libs

clean:${objects_clean}
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/hwc-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/pixman-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/gl-render/libweston/*
	$(AT)rm -rf $(WAYLAND_DIR)/weston/patch/fbdev-backend/libweston/*
	$(AT)rm -rf $(WL_OUT_DIR)/weston/.libs/hwc-renderer.so
	$(AT)rm -rf $(WL_OUT_DIR)/weston/.libs/gl-renderer.so
	$(AT)rm -rf $(WL_OUT_DIR)/weston/.libs/fbdev-backend.so

#==================================================================
#    modules
#==================================================================
.PHONY: ${objects} ${objects_clean} prepare

$(objects):prepare
	$(AT)make -C $@

$(objects_clean):
	$(AT)make -C $(patsubst %_clean,%,$@) clean

prepare:
	$(AT)cp -rf $(WL_OUT_DIR)/bin/wayland-scanner $(WL_INSTALL_DIR)/bin
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/hwc-renderer.c      $(WAYLAND_DIR)/weston/patch/hwc-render/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/gl-hwc-renderer.c   $(WAYLAND_DIR)/weston/patch/hwc-render/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/pixman-renderer.c   $(WAYLAND_DIR)/weston/patch/pixman-render/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/gl-renderer.c       $(WAYLAND_DIR)/weston/patch/gl-render/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/vertex-clipping.c   $(WAYLAND_DIR)/weston/patch/gl-render/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/compositor-fbdev.c  $(WAYLAND_DIR)/weston/patch/fbdev-backend/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/libinput-device.c   $(WAYLAND_DIR)/weston/patch/fbdev-backend/libweston
	$(AT)cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/libweston/libinput-seat.c     $(WAYLAND_DIR)/weston/patch/fbdev-backend/libweston
