#===============================================================================
# export variable
#===============================================================================
WAYLAND_DIR ?= $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(WAYLAND_DIR)/base.mak

#===============================================================================
# sdk dir
#===============================================================================
include $(SDK_DIR)/base.mak

path_ver := patch/patch-for-weston-3.0.0

#===============================================================================
# sdk resource
#===============================================================================
#revise sdk/cfg.mak egl type with wayland and to api/gpu make clean;make
DEPEND_LIBS := -L$(HI_SHARED_LIB_DIR) -lpthread -lrt -lm -ldl -lstdc++ -lEGL -lGLESv2 -lwayland-egl
DEPEND_LIBS += -L$(WL_INSTALL_DIR)/lib/ -lwayland-server -lwayland-client -lwayland-cursor -lffi

DEPEND_INCLUDE := -I$(HI_INCLUDE_DIR)
DEPEND_INCLUDE += -I$(WAYLAND_DIR)/weston/$(path_ver)/libweston

#===============================================================================
# export variable
#===============================================================================
OPEN_SOURCE_DIR := .

#===============================================================================
#need revise
#===============================================================================
SOFT_NAME := weston
MAJO_SOFT_VERSON := libweston-3
SOFT_VERSION := 3.0.0
SOFT_TAG := tar.xz

CONFIG_FILE := configure

WITH_CFG := --enable-static --enable-dbus --disable-devdocs --disable-setuid-install --disable-systemd-notify --disable-systemd-login --with-sysroot=$(WL_INSTALL_DIR)

WITH_CFG += --enable-xwayland=no
WITH_CFG += --enable-xwayland-test=no
WITH_CFG += --disable-ivi-shell

WITH_CFG += --disable-simple-dmabuf-drm-client
WITH_CFG += --disable-simple-dmabuf-v4l-client

WITH_CFG += --enable-x11-compositor=no
WITH_CFG += --enable-drm-compositor=no
WITH_CFG += --enable-wayland-compositor=no
WITH_CFG += --enable-headless-compositor=no
WITH_CFG += --enable-rdp-compositor=no

WITH_CFG += --enable-fbdev-compositor=no

#WITH_CFG += --disable-simple-clientt
#WITH_CFG += --disable-simple-egl-clients
#===============================================================================
# local variable
#===============================================================================
SOFT_DIR := $(WL_OUT_DIR)/obj/$(SOFT_NAME)
TARGETS  := $(SOFT_NAME)
PKG_CONFIG_PATH := $(WL_INSTALL_DIR)/lib/pkgconfig

#=====================================================================================
#toolchains
#=====================================================================================
ARM_TOOLCHAINS_NAME := $(WL_ARM_TOOLCHAINS_NAME)-
STANDARD_CFG := --host=$(WL_ARM_TOOLCHAINS_NAME) --prefix=$(WL_INSTALL_DIR) --build=x86 PKG_CONFIG_PATH=$(PKG_CONFIG_PATH)

CC_ARM_TOOLCHAINS_NAME  := $(ARM_TOOLCHAINS_NAME)gcc
CPP_ARM_TOOLCHAINS_NAME := $(ARM_TOOLCHAINS_NAME)cpp
AR_ARM_TOOLCHAINS_NAME  := $(ARM_TOOLCHAINS_NAME)ar
AS_ARM_TOOLCHAINS_NAME  := $(ARM_TOOLCHAINS_NAME)as
LD_ARM_TOOLCHAINS_NAME  := $(ARM_TOOLCHAINS_NAME)ld
NM_ARM_TOOLCHAINS_NAME  := $(ARM_TOOLCHAINS_NAME)nm
STRIP_ARM_TOOLCHAINS_NAME   := $(ARM_TOOLCHAINS_NAME)strip
OBJDUMP_ARM_TOOLCHAINS_NAME := $(ARM_TOOLCHAINS_NAME)objdump

#=====================================================================================
#export env
#=====================================================================================
INCLUDES := -I$(WL_INSTALL_DIR)/include $(DEPEND_INCLUDE)
LDFLAGS  := -L$(WL_INSTALL_DIR)/lib $(DEPEND_LIBS)

CFLAGS := $(WL_CFLAGS)
CPPFLAGS := $(INCLUDES)
#CXXFLAGS := -fno-rtti $(CFLAGS)
CXXFLAGS := $(CFLAGS)

#=====================================================================================
#add egl
#=====================================================================================
EGL_CFLAGS := $(DEPEND_INCLUDE)
EGL_LIBS := $(DEPEND_LIBS)

EGL_TESTS_CFLAGS := $(DEPEND_INCLUDE)
EGL_TESTS_LIBS := $(DEPEND_LIBS)

SIMPLE_EGL_CLIENT_CFLAGS := $(DEPEND_INCLUDE)
SIMPLE_EGL_CLIENT_LIBS := $(DEPEND_LIBS)
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(SOFT_NAME) prepare

all: $(TARGETS)
	$(AT)test -d $(WL_INSTALL_DIR)/.libs || mkdir -p $(WL_INSTALL_DIR)/.libs
	$(AT)cp -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/.libs/*             $(WL_INSTALL_DIR)/.libs
	$(AT)cp -rf $(WL_INSTALL_DIR)/libexec/weston-desktop-shell               $(WL_INSTALL_DIR)
clean:
	$(AT)rm -rf $(SOFT_DIR)

$(SOFT_NAME): $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/tar
	$(AT)cd $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION) && make install

$(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/tar:
	$(AT)test -d $(SOFT_DIR) || mkdir -p $(SOFT_DIR)
	$(AT)test -d $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION) || (tar xf $(OPEN_SOURCE_DIR)/$(SOFT_NAME)-$(SOFT_VERSION).$(SOFT_TAG) -C $(SOFT_DIR);\
        cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/Makefile.am          $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION);\
        cp -rf $(WAYLAND_DIR)/weston/$(path_ver)/compositor/*         $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/compositor;\
	rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/pixman-renderer.c;\
	rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/pixman-renderer.h;\
        rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/gl-renderer.c;\
        rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/gl-renderer.h;\
        rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/compositor-fbdev.c;\
        rm -rf $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/libweston/compositor-fbdev.h;\
        cd $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION);aclocal;libtoolize;autoheader;autoconf;automake --add-missing;\
        sh $(CONFIG_FILE) $(STANDARD_CFG) $(WITH_CFG) EGL_TESTS_CFLAGS="$(EGL_TESTS_CFLAGS)" EGL_TESTS_LIBS="$(EGL_TESTS_LIBS)" SIMPLE_EGL_CLIENT_CFLAGS="$(SIMPLE_EGL_CLIENT_CFLAGS)" SIMPLE_EGL_CLIENT_LIBS="$(SIMPLE_EGL_CLIENT_LIBS)" EGL_CFLAGS="$(EGL_CFLAGS)" EGL_LIBS="$(EGL_LIBS)" INCLUDES="$(INCLUDES)" LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" CXXFLAGS="$(CXXFLAGS)" CC=$(CC_ARM_TOOLCHAINS_NAME) CPP=$(CPP_ARM_TOOLCHAINS_NAME) AR=$(AR_ARM_TOOLCHAINS_NAME) AS=$(AS_ARM_TOOLCHAINS_NAME) LD=$(LD_ARM_TOOLCHAINS_NAME) NM=$(NM_ARM_TOOLCHAINS_NAME) STRIP=$(STRIP_ARM_TOOLCHAINS_NAME) OBJDUMP=$(OBJDUMP_ARM_TOOLCHAINS_NAME);)
	$(AT)touch $@
