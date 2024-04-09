###########################################################
# Copyright (C) 2016-2026 2012 Euler SME.
# config.mk
###########################################################

ifeq ($(ENV_SME_VERSION_TYPE), rls)
TARGET_OUT_VERSION_TYPE  := rls
else
TARGET_OUT_VERSION_TYPE  := dbg
endif

#define build parameter
MAKE_PARAMETER := -j

#define multithread
#for opensource will use this default
MAKE_PARALLEL := -j7

#define build varibales
TOPDIR        := $(TOP)
SMEDIR        := $(TOPDIR)/source/sme
BUILD_SYSTEM  := $(TOPDIR)/build/sme/core
OUTDIR        := $(TOPDIR)/out
TARGET_OUTDIR := $(OUTDIR)/$(CFG_PROJECT_NAME)/$(TARGET_OUT_VERSION_TYPE)
HOST_OUTDIR   := $(OUTDIR)/host
SME_PLATFORM_DIR  := $(TOPDIR)/platform

#SME��ԭʼ�����������Դ���⼰.h��Ŀ¼�����TOPDIRĿ¼
CFG_RT_SME_THIRDPARTY_ORG_DIR=thirdparty/sme

#SME����Ŀ¼
CFG_RT_TEST_DIR=test/sme

#SME�Ŀ�Դ���patchĿ¼�����TOPDIRĿ¼
CFG_RT_SME_THIRDPARTY_PATCH_DIR=thirdparty/sme/patches
#SME�Ŀ�Դ���patchĿ¼
SME_THIRDPARTY_PATCH_DIR=$(TOPDIR)/$(CFG_RT_SME_THIRDPARTY_PATCH_DIR)

#SME ����HW�İ�ȫ������Ŀ¼�����TOPDIRĿ¼
CFG_RT_LIBHWSECURE_DIR=platform/libhwsecurec

####new add begin####
#SME��ԭʼ�����������Դ���⼰.h��Ŀ¼��
SME_THIRDPARTY_ORG_DIR=$(TOPDIR)/$(CFG_RT_SME_THIRDPARTY_ORG_DIR)

#MediaOSĿ¼
MEDIAOSDIR=$(TOPDIR)

##########################################################
# define build template variable
##########################################################
BUILD_STATIC_LIBRARY      := $(BUILD_SYSTEM)/static_library.mk
BUILD_SHARED_LIBRARY      := $(BUILD_SYSTEM)/shared_library.mk
BUILD_EXECUTABLE          := $(BUILD_SYSTEM)/executable.mk
BUILD_HOST_EXECUTABLE     := $(BUILD_SYSTEM)/host_executable.mk
BUILD_HOST_SHARED_LIBRARY := $(BUILD_SYSTEM)/host_shared_library.mk
BUILD_HOST_STATIC_LIBRARY := $(BUILD_SYSTEM)/host_static_library.mk
BUILD_OPENSOURCE_PKG      := $(BUILD_SYSTEM)/opensource_pkg.mk
BUILD_SELFDEFINE_PKG      := $(BUILD_SYSTEM)/selfdefine_pkg.mk
CLEAR_VARS                := $(BUILD_SYSTEM)/clear_vars.mk

##########################################################
# build toolchain config
# varibale CROSS value depend on user config from menuconfig
##########################################################
#ndk Ŀ¼
ifeq ($(CFG_ENABLE_NDK), y)
TOOLCHAIN_EXTRACT_DIR := $(TARGET_OUTDIR)/toolchain
TOOLCHAIN_INSTALL_DIR := $(TOOLCHAIN_EXTRACT_DIR)/sme
export CROSS:=$(TOOLCHAIN_INSTALL_DIR)/bin/$(CFG_TOOLCHAINS_NAME)
CFG_COMPILE_SYSROOT:=$(TOOLCHAIN_INSTALL_DIR)/sysroot/
else
export CROSS:=$(TOPDIR)/HiSTBLinux/Code/tools/linux/toolchains/$(CFG_TOOLCHAINS_NAME)/bin/$(CFG_TOOLCHAINS_NAME)
endif

ifeq ($(CFG_ENABLE_DRA_DECODER), y)
    CFG_COMMON_MACRO += -DGST_OMX_DRA_DEC_ENABLE
endif

ifeq ($(ENV_SME_VERSION_TYPE), rls)
    STRIP_IN_RELEASE_VERSION=y
#release version
    GNC_CFLAGS = -fPIC -fPIE -O2 -Wall -Wextra \
        -Wformat -fstack-protector -FORTIRY_SOURCE \
        -Wfloat-equal -Warray-bounds -Wformat \
        -Wpointer-arith -Wcast-qual -fvisibility=default \
        -Wl,-z,noexecstack \
        -Wstrict-overflow=2 -DSME_RLS

ifeq ($(CFG_ENABLE_NDK), y)
    GNC_CFLAGS += -D_FORTIFY_SOURCE=2
    GNC_CFLAGS += -pie -s
endif
    OPENSOURCE_CFLAGS = $(GNC_CFLAGS) \
        -Wstrict-prototypes -Wmissing-prototypes $(CFG_COMMON_MACRO)
    OPENSOURCE_CXXFLAGS =  $(GNC_CFLAGS) \
        -Wshadow $(CFG_COMMON_MACRO)
    OPENSOURCE_LDFLAGS = -pie
ifeq ($(CFG_ENABLE_NDK), y)
    OPENSOURCE_LDFLAGS += -s
endif
    EXTRA_CFLAGS = $(OPENSOURCE_CFLAGS)
    EXTRA_CXXFLAGS = $(OPENSOURCE_CXXFLAGS)
    EXTRA_LDFLAGS = -Wl,-z,relro,-z,now -Wl,-z,noexecstack
    EXTRA_LDLIBS =
else
#debug version
    GNC_CFLAGS = -fPIC -fPIE -g -O1 -Wall -Wstrict-overflow=2 --stack-check
    OPENSOURCE_CFLAGS = $(GNC_CFLAGS) $(CFG_COMMON_MACRO)
    OPENSOURCE_CXXFLAGS = $(GNC_CFLAGS) -Wshadow $(CFG_COMMON_MACRO)
    OPENSOURCE_LDFLAGS = -pie
    EXTRA_CFLAGS = $(OPENSOURCE_CFLAGS)
    EXTRA_CXXFLAGS = $(OPENSOURCE_CXXFLAGS)
    EXTRA_LDFLAGS =
    EXTRA_LDLIBS =
ifeq ($(ENV_SME_VERSION_TYPE), lcov)
    EXTRA_CFLAGS += -fprofile-arcs -ftest-coverage
    EXTRA_CXXFLAGS += -fprofile-arcs -ftest-coverage
    EXTRA_LDFLAGS += -lgcc -lgcov
    EXTRA_LDLIBS += --coverage
endif
endif

ifeq ($(CFG_ENABLE_MULTI_AUDIO_TRACK), y)
    EXTRA_CFLAGS += -DSME_MULTI_AUDIO_TRACK
    EXTRA_CXXFLAGS += -DSME_MULTI_AUDIO_TRACK
endif

ifeq ($(CFG_ENABLE_MULTI_SUBTITLE_TRACK), y)
    EXTRA_CFLAGS += -DSME_MULTI_SUBTITLE_TRACK
    EXTRA_CXXFLAGS += -DSME_MULTI_SUBTITLE_TRACK
endif

#comile cmd for target machine

TARGET_AR      := $(CROSS)-ar
TARGET_AS      := $(CROSS)-as
TARGET_LD      := $(CROSS)-ld
TARGET_CXX     := $(CROSS)-g++
TARGET_CC      := $(CROSS)-gcc
TARGET_NM      := $(CROSS)-nm
TARGET_STRIP   := $(CROSS)-strip
TARGET_OBJCOPY := $(CROSS)-objcopy
TARGET_OBJDUMP := $(CROSS)-objdump
TARGET_RANLIB  := $(CROSS)-ranlib

TARGET_GLOBLE_CFLAGS     :=
TARGET_GLOBLE_CPPFLAGS   :=
TARGET_GLOBLE_LDFLAGS    :=
TARGET_GLOBLE_ARFLAGS    := rcs
TARGET_RELEASE_CPPFLAGS  :=

TARGET_C_INCLUDES        :=
TARGET_DEFAULT_SYSTEM_SHARED_LIBRARIES :=

TARGET_EXECUTABLE_SUFFIX :=
TARGET_SHAREDLIB_SUFFIX  :=.so
TARGET_STATICLIB_SUFFIX  :=.a


#compile cmd for host machine

HOST_AR      := ar
HOST_AS      := as
HOST_LD      := ld
HOST_CXX     := g++
HOST_CC      := gcc
HOST_NM      := nm
HOST_STRIP   := strip
HOST_OBJCOPY := objcopy
HOST_OBJDUMP := objdump
HOST_RANLIB  := ranlib

HOST_GLOBLE_CFLAGS     := -fPIC
HOST_GLOBLE_CPPFLAGS   := -fPIC
HOST_GLOBLE_LDFLAGS    :=
HOST_GLOBLE_ARFLAGS    := rcs
HOST_EXECUTABLE_SUFFIX :=
HOST_SHAREDLIB_SUFFIX  :=.so
HOST_STATICLIB_SUFFIX  :=.a

#####################################################
# target output dirs
#####################################################
TARGET_OUT_INCLUDE_DIR := $(TARGET_OUTDIR)/include
TARGET_OUT_LIB_DIR     := $(TARGET_OUTDIR)/lib
TARGET_OUT_BIN_DIR     := $(TARGET_OUTDIR)/bin
TARGET_OUT_CONFIG_DIR  := $(TARGET_OUTDIR)/config
#TARGET_OUT_OBJ_DIR    := $(TARGET_OUTDIR)/obj
TARGET_OUT_OBJ_DIR     := $(TARGET_OUTDIR)/intermediate
THIRDPARTY_OBJ_DIR     := $(TARGET_OUTDIR)/intermediate/thirdparty
#���mediaosĿ¼
RT_THIRDPARTY_OBJ_DIR  := $(patsubst $(TOPDIR)/%,%, $(THIRDPARTY_OBJ_DIR))
#�����Դ����ĳЩ��Դ������Դ����Ʒ�������������������ô��Դ���Ķ���ͷ�ļ���������Ŀ¼�����SMEĿ¼
RT_3RD_INC_DIR         := source/sme/thirdparty/inc

#ffmpeg��Դ������
#PKG_FFMPEG_NAME        := ffmpeg-2.2.4
PKG_FFMPEG_NAME        := ffmpeg_v2.8

PKG_GSTREAMER_NAME		:= gstreamer-1.10.4

ifeq ($(CFG_ENABLE_NDK), y)
CFG_ZLIB_CFLAGS:=-I$(CFG_COMPILE_SYSROOT)/usr/include
CFG_ZLIBS:=-L$(CFG_COMPILE_SYSROOT)/usr/lib
else
CFG_ZLIB_CFLAGS:=$(foreach inc_tmp, $(CFG_RT_PLATFORM_SDK_INC_DIR), -I$(TOPDIR)/$(inc_tmp))
CFG_ZLIBS:=-L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)
endif

THIRDPARTY_PKG_CONFIG_DIR:= $(TARGET_OUTDIR)/intermediate/thirdparty/lib/pkgconfig
TARGET_OUT_PLUGIN_DIR    := $(TARGET_OUT_LIB_DIR)/gstplugins

#SME�Ŀ�Դ���mergeĿ¼�����TOPDIRĿ¼���м�Ŀ¼
CFG_RT_SME_THIRDPARTY_MERGE_DIR=$(RT_THIRDPARTY_OBJ_DIR)/merge
#SME�Ŀ�Դ���mergeĿ¼
SME_THIRDPARTY_MERGE_DIR=$(TOPDIR)/$(CFG_RT_SME_THIRDPARTY_MERGE_DIR)

TARGET_OUT_TO_PREBUILT_PLUGIN_DIR := $(SMEDIR)/prebuilt/$(CFG_PROJECT_NAME)/$(TARGET_OUT_VERSION_TYPE)/lib/gstplugins
TARGET_OUT_TO_PREBUILT_DIR        := $(SMEDIR)/prebuilt/$(CFG_PROJECT_NAME)/$(TARGET_OUT_VERSION_TYPE)/lib

HOST_BIN_DIR := $(HOST_OUTDIR)/bin
HOST_LIB_DIR := $(HOST_OUTDIR)/lib
HOST_INCLUDE := $(HOST_OUTDIR)/include
HOST_OBJ_DIR := $(HOST_OUTDIR)/obj

#####################################################
# target link dirs
#####################################################
TARGET_GLOBAL_LD_DIRS        :=$(TARGET_OUT_LIB_DIR)
TARGET_GLOBAL_LD_SHARED_DIRS :=$(TARGET_OUT_LIB_DIR)
TARGET_GLOBAL_LD_STATIC_DIRS :=$(TARGET_OUT_LIB_DIR)
TARGET_GLOBAL_LD_EXTERN_DIRS :=$(TARGET_OUT_LIB_DIR)

HOST_GLOBAL_LD_DIRS          :=$(HOST_LIB_DIR)
HOST_GLOBAL_LD_SHARED_DIRS   :=$(HOST_LIB_DIR)/share
HOST_GLOBAL_LD_STATIC_DIRS   :=$(HOST_LIB_DIR)/static
HOST_GLOBAL_LD_EXTERN_DIRS   :=$(HOST_LIB_DIR)/extern

TARGET_C_INCLUDES :=
TARGET_BIN_DIR    :=$(TARGET_OUT_BIN_DIR)
TARGET_CONFIG_DIR :=$(TARGET_OUT_CONFIG_DIR)

####################################################
# common shell cmds
####################################################
MKDIR :=mkdir
CP :=cp
RM :=rm
TOUCH := touch
$(shell mkdir -p $(TARGET_OUT_INCLUDE_DIR))
$(shell mkdir -p $(TARGET_OUT_LIB_DIR))
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR))
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR)/lib)
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR)/include)
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR)/bin)
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR)/share)
$(shell mkdir -p $(THIRDPARTY_OBJ_DIR)/libexec)
$(shell mkdir -p $(THIRDPARTY_PKG_CONFIG_DIR))
$(shell mkdir -p $(TARGET_OUT_CONFIG_DIR))
$(shell mkdir -p $(TARGET_OUT_PLUGIN_DIR))
$(shell mkdir -p $(TARGET_OUT_BIN_DIR))
ifeq ($(CFG_ENABLE_NDK), y)
$(shell mkdir -p $(TOOLCHAIN_INSTALL_DIR))
endif
