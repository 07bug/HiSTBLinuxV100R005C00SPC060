#===============================================================================
# export variable
#===============================================================================
SDK_DIR ?= $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak

OPEN_SOURCE_DIR := .

#===============================================================================
#need revise
#===============================================================================
SOFT_NAME := dri2proto
SOFT_VERSION := 2.8
SOFT_TAG := tar.gz

CONFIG_FILE := configure

WITH_CFG :=

#===============================================================================
# local variable
#===============================================================================
SOFT_DIR := $(WL_OUT_DIR)/obj/component/$(SOFT_NAME)
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
INCLUDES := -I$(WL_INSTALL_DIR)/include
LDFLAGS  := -L$(WL_INSTALL_DIR)/lib

CFLAGS := $(WL_CFLAGS)
CPPFLAGS := $(INCLUDES)
#CXXFLAGS := -fno-rtti $(CFLAGS)
CXXFLAGS := $(CFLAGS)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(SOFT_NAME) prepare

all: $(TARGETS)

clean:
	$(AT)rm -rf $(SOFT_DIR)

$(SOFT_NAME): $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/tar
	$(AT)cd $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION) && make install

$(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION)/tar:
	$(AT)test -d $(SOFT_DIR) || mkdir -p $(SOFT_DIR)
	$(AT)test -d $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION) || (tar xf $(OPEN_SOURCE_DIR)/$(SOFT_NAME)-$(SOFT_VERSION).$(SOFT_TAG) -C $(SOFT_DIR);\
        cd $(SOFT_DIR)/$(SOFT_NAME)-$(SOFT_VERSION);\
        sh $(CONFIG_FILE) $(STANDARD_CFG) $(WITH_CFG) INCLUDES="$(INCLUDES)" LDFLAGS="$(LDFLAGS)" CFLAGS="$(CFLAGS)" CPPFLAGS="$(CPPFLAGS)" CXXFLAGS="$(CXXFLAGS)" CC=$(CC_ARM_TOOLCHAINS_NAME) CPP=$(CPP_ARM_TOOLCHAINS_NAME) AR=$(AR_ARM_TOOLCHAINS_NAME) AS=$(AS_ARM_TOOLCHAINS_NAME) LD=$(LD_ARM_TOOLCHAINS_NAME) NM=$(NM_ARM_TOOLCHAINS_NAME) STRIP=$(STRIP_ARM_TOOLCHAINS_NAME) OBJDUMP=$(OBJDUMP_ARM_TOOLCHAINS_NAME);)
	$(AT)touch $@
