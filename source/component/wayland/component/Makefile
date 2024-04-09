#===============================================================================
# export variable
#===============================================================================
WAYLAND_DIR ?= $(shell cd $(CURDIR)/.. && /bin/pwd)
include $(WAYLAND_DIR)/base.mak

#===============================================================================
# sdk dir
#===============================================================================
include $(SDK_DIR)/base.mak

#===============================================================================
# export variable
#===============================================================================
BIN_DIR := $(WL_OUT_DIR)/bin

#===============================================================================
# objects
#===============================================================================
objects :=
objects += libffi
objects += expat
objects += libxml2
#objects += xz
objects += wayland

ifneq ($(WL_PRODUCT_FILE),y)
objects += wayland-protocols
endif

ifneq ($(WL_PRODUCT_FILE),y)
objects += libevdev
objects += kmod
objects += ncurses
objects += util-linux
objects += pcre
objects += zlib
#objects += freetype
objects += glib
objects += udev
objects += mtdev
objects += libinput
endif

ifneq ($(WL_PRODUCT_FILE),y)
objects += pciaccess
objects += libdrm
endif

ifneq ($(WL_PRODUCT_FILE),y)
#objects += xporto
#objects += xtrans
#objects += xcb-proto
#objects += libxau
#objects += pthread-stubs
#objects += libxcb
#objects += xextproto
#objects += libx11
#objects += libxext
#objects += damageproto
#objects += fixesproto
#objects += libxfixes
#objects += libxdamage
#objects += util-macros
#objects += xf86vidmodeproto
#objects += libxxf86vm
#objects += dri2proto
#objects += glproto
#objects += mesa
endif

ifneq ($(WL_PRODUCT_FILE),y)
objects += linux-pam
objects += libxkbcommon
objects += libpng
objects += pixman
objects += cairo
objects += dbus
endif

ifneq ($(WL_PRODUCT_FILE),y)
#objects += renderproto
#objects += libxrender
#objects += libxcursor
endif

ifneq ($(WL_PRODUCT_FILE),y)
#objects += fontconfig
#objects += pango
endif

objects_clean := $(addsuffix _clean, $(objects))

depends:=$(objects)
depends_clean:=$(addsuffix _clean,${depends})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#     rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PHONY := all clean

all:${depends}
ifeq ($(WL_PRODUCT_FILE),y)
	$(AT)test -d $(BIN_DIR) || mkdir -p $(BIN_DIR)/protocol
	$(AT)cp -rf $(WAYLAND_DIR)/component/glib/arm-linux.cache    $(BIN_DIR)
	$(AT)cp -rf $(WL_INSTALL_DIR)/bin/wayland-scanner            $(BIN_DIR)
	$(AT)cp -rf $(WL_OUT_DIR)/obj/component/wayland/wayland-1.14.0/protocol/*.h       $(BIN_DIR)/protocol
	$(AT)cp -rf $(WL_OUT_DIR)/obj/component/wayland/wayland-1.14.0/protocol/*.c       $(BIN_DIR)/protocol
endif

clean:${depends_clean}

#==================================================================
#                          modules
#==================================================================
.PHONY: ${objects} ${objects_clean}

$(objects):
	$(AT)make -C $@

$(objects_clean):
	$(AT)make -C $(patsubst %_clean,%,$@) clean
