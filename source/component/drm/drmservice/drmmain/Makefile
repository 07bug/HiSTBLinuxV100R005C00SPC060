ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
	MULTI_PROCESS := y
else
	MULTI_PROCESS := n
endif

CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CFG_HI_TOOLCHAINS_NAME_64 := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)

DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

DRM_CC_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-g++
DRM_AR_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-ar
#### directories
##################################################################################
SERVICE_DRM_SRC_DIR=$(CURDIR)
DRM_DIR=$(CURDIR)/../..
DRMSERVICE_SOURCE_DIR=$(CURDIR)/..

BASE_INC_DIR := $(DRM_DIR)/base/include
DRMSERVICE_INC_DIR     := $(DRMSERVICE_SOURCE_DIR)/include
DRMIPC_CLIENT_INC_DIR  := $(DRMSERVICE_SOURCE_DIR)/drm_ipc/client
DRMIPC_SERVER_INC_DIR  := $(DRMSERVICE_SOURCE_DIR)/drm_ipc/server
DRMPLUGIN_INC_DIR      := $(DRMSERVICE_SOURCE_DIR)/drmplugin
DRMPLUGIN_PRIV_INC_DIR := $(DRMSERVICE_SOURCE_DIR)/drmplugin/private

LIBPATH := -L $(HI_SHARED_LIB_DIR)
#LIBPATH += -L $(HI_STATIC_LIB_DIR)

LIBPATH_64 := -L $(HI_SHARED_LIB64_DIR)
#LIBPATH_64 += -L $(HI_STATIC_LIB64_DIR)

#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(BASE_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_PRIV_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_INC_DIR)
CFG_INC += -I$(DRMSERVICE_INC_DIR)
CFG_INC += -I$(DRMIPC_CLIENT_INC_DIR)
CFG_INC += -I$(DRMIPC_SERVER_INC_DIR)
CFG_INC += -I$(INTERFACE_IMPL_INC_DIR)

#### objs
###################################################################################
VPATH := $(SERVICE_DRM_SRC_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) -fpermissive -fPIC
ifeq ($(MULTI_PROCESS), y)
EXTRA_CFLAGS += -DMULTI_PROCESS
endif
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

LIB := -lutils -lcutils -llog -lbinder_ipc -ldrm -ldrm_common
LIB += -lpthread -ldl #-lz

BIN_NAME    := service_drm
BIN_NAME_64 := service_drm_64

SERVICE_DRM_CPP := main.cpp

SERVICE_DRM_OBJ_DIR   := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(SERVICE_DRM_SRC_DIR))
SERVICE_DRM_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(SERVICE_DRM_SRC_DIR))

SERVICE_DRM_BIN_DIR    := $(SERVICE_DRM_OBJ_DIR)/bin
SERVICE_DRM_OUTPUT_BIN := $(SERVICE_DRM_BIN_DIR)/$(BIN_NAME)

SERVICE_DRM_ROOTFS_DIR        := $(HI_ROOTFS_DIR)/usr/bin
SERVICE_DRM_OUTPUT_ROOTFS_BIN := $(SERVICE_DRM_ROOTFS_DIR)/$(BIN_NAME)

SERVICE_DRM_BIN_DIR_64    := $(SERVICE_DRM_OBJ64_DIR)/bin
SERVICE_DRM_OUTPUT_BIN_64 := $(SERVICE_DRM_BIN_DIR_64)/$(BIN_NAME_64)

SERVICE_DRM_ROOTFS_DIR_64        :=$(HI_ROOTFS_DIR)/usr/bin
SERVICE_DRM_OUTPUT_ROOTFS_BIN_64 := $(SERVICE_DRM_ROOTFS_DIR_64)/$(BIN_NAME_64)

SERVICE_DRM_OBJS := $(SERVICE_DRM_CPP:%.cpp=$(SERVICE_DRM_OBJ_DIR)/%.o)

SERVICE_DRM_OBJS64 := $(SERVICE_DRM_CPP:%.cpp=$(SERVICE_DRM_OBJ64_DIR)/%.o)


TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += drm_service
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += drm_service64
endif
.PHONY: all drm_service drm_service64 drmservice_clean 

all: $(TARGETS)

clean: drmservice_clean

#********************* Create out dir ***********************

drm_service: $(SERVICE_DRM_OBJS)
	$(AT)[ -e $(SERVICE_DRM_BIN_DIR) ] || mkdir -p $(SERVICE_DRM_BIN_DIR)
	$(AT)$(DRM_CC) -o $(SERVICE_DRM_OUTPUT_BIN) $(SERVICE_DRM_OBJS) $(LIBPATH) $(LIB)

	$(AT)[ -e $(SERVICE_DRM_ROOTFS_DIR) ] || mkdir -p $(SERVICE_DRM__ROOTFS_DIR)
	$(AT)cp -f $(SERVICE_DRM_OUTPUT_BIN) $(SERVICE_DRM_ROOTFS_DIR)

drm_service64: $(SERVICE_DRM_OBJS64)
	$(AT)[ -e $(SERVICE_DRM_BIN_DIR_64) ] || mkdir -p $(SERVICE_DRM_BIN_DIR_64)
#	$(AT)$(DRM_CC_64) -o $(SERVICE_DRM_OUTPUT_BIN_64) $(SERVICE_DRM_OBJ64)  $(LIBPATH_64) $(LIB)

#	$(AT)[ -e $(SERVICE_DRM_ROOTFS_DIR_64) ] || mkdir -p $(SERVICE_DRM_ROOTFS_DIR_64)
#	$(AT)cp -f $(SERVICE_DRM_OUTPUT_BIN_64) $(SERVICE_DRM_ROOTFS_DIR_64)

drmservice_clean:
	$(AT)rm -rf $(SERVICE_DRM_OBJ_DIR) $(SERVICE_DRM_OBJ64_DIR)
	$(AT)rm -rf $(SERVICE_DRM_OUTPUT_BIN) $(SERVICE_DRM_OUTPUT_BIN_64)
	$(AT)rm -rf $(SERVICE_DRM_BIN_DIR) $(SERVICE_DRM_BIN_DIR_64)
	$(AT)rm -rf $(SERVICE_DRM_OUTPUT_ROOTFS_BIN) $(SERVICE_DRM_OUTPUT_ROOTFS_BIN_64)

$(SERVICE_DRM_OBJ_DIR)/%.o : %.cpp
	$(AT)[ -e $(SERVICE_DRM_OBJ_DIR) ] || mkdir -p $(SERVICE_DRM_OBJ_DIR)
	$(AT)$(DRM_CC) $(EXTRA_CFLAGS) -o "$(SERVICE_DRM_OBJ_DIR)/$(*F).o" "$<"
	
$(SERVICE_DRM_OBJ64_DIR)/%.o : %.cpp
	$(AT)[ -e $(SERVICE_DRM_OBJ64_DIR) ] || mkdir -p $(SERVICE_DRM_OBJ64_DIR)
	$(AT)$(DRM_CC_64) $(EXTRA_CFLAGS) -o "$(SERVICE_DRM_OBJ64_DIR)/$(*F).o" "$<"
