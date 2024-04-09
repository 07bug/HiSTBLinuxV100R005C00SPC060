ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)

CFG_HI_TOOLCHAINS_NAME_64 := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
	MULTI_PROCESS := y
else
	MULTI_PROCESS := n
endif

DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

DRM_CC_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-gcc
DRM_AR_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-ar

#### directories
##################################################################################


DRMIPC_SRC_DIR=$(CURDIR)/
DRMSERVICE_SOURCE_DIR=$(CURDIR)/..
DRM_DIR = $(CURDIR)/../..

DRMIPC_CLIENT_SRC_DIR := $(CURDIR)/client
DRMIPC_SERVER_SRC_DIR := $(CURDIR)/server
INTERFACE_IMPL_SRC_DIR := $(DRMSERVICE_SOURCE_DIR)/interface_impl

BASE_INC_DIR := $(DRM_DIR)/base/include

DRMSERVICE_INC_DIR := $(DRMSERVICE_SOURCE_DIR)/include
DRMPLUGIN_INC_DIR := $(DRMSERVICE_SOURCE_DIR)/drmplugin
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
CFG_INC += -I$(DRMIPC_CLIENT_SRC_DIR)
CFG_INC += -I$(DRMIPC_SERVER_SRC_DIR)
CFG_INC += -I$(INTERFACE_IMPL_SRC_DIR)

#### objs
###################################################################################
VPATH := $(DRMIPC_CLIENT_SRC_DIR)
VPATH += $(DRMIPC_SERVER_SRC_DIR)
VPATH += $(INTERFACE_IMPL_SRC_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) -fpermissive -fPIC
ifeq ($(MULTI_PROCESS), y)
EXTRA_CFLAGS += -DMULTI_PROCESS
endif
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DLINUX_DEBUGLOG

LIB := -lcutils -llog -lbinder_ipc -ldrm_common
ifeq ($(CFG_SDK_TYPE),dpt_sdk)
LIB += -lc_sec
endif

LIBDRM_CPP=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))

LIBDRM_OBJ_DIR   := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMIPC_SRC_DIR))
LIBDRM_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMIPC_SRC_DIR))

LIBDRM_OBJS   := $(LIBDRM_CPP:%.cpp=$(LIBDRM_OBJ_DIR)/%.o)
LIBDRM_OBJS64 := $(LIBDRM_CPP:%.cpp=$(LIBDRM_OBJ64_DIR)/%.o)

LIB_NAME := libdrm

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += libdrm
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += libdrm64
endif

.PHONY: all libdrm libdrm64 libdrm_clean 

all: $(TARGETS)

clean: libdrm_clean

libdrm: $(LIBDRM_OBJS)
#	$(AT)$(DRM_AR) -rsv $(LIBDRM_OBJ_DIR)/$(LIB_NAME).a $^
	$(AT)$(DRM_CC) -shared -o $(LIBDRM_OBJ_DIR)/$(LIB_NAME).so $^

#	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
#	$(AT)cp -f $(LIBDRM_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(LIBDRM_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

libdrm64: $(LIBDRM_OBJS64)
#	$(AT)$(DRM_AR_64) -rsv $(LIBDRM_OBJ64_DIR)/$(LIB_NAME).a $^
	$(AT)$(DRM_CC_64) -shared -o $(LIBDRM_OBJ64_DIR)/$(LIB_NAME).so $^

#	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
#	$(AT)cp -f $(LIBDRM_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(LIBDRM_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

libdrm_clean:
	$(AT)rm -rf $(LIBDRM_OBJ_DIR) $(LIBDRM_COMMON_OBJ64_DIR)
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so
#	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a 

$(LIBDRM_OBJ_DIR)/%.o : %.cpp
	$(AT)[ -e $(LIBDRM_OBJ_DIR) ] || mkdir -p $(LIBDRM_OBJ_DIR)
	$(AT)$(DRM_CC) $(EXTRA_CFLAGS) -o "$(LIBDRM_OBJ_DIR)/$(*F).o" "$<"

$(LIBDRM_OBJ64_DIR)/%.o : %.cpp
	$(AT)[ -e $(LIBDRM_OBJ64_DIR) ] || mkdir -p $(LIBDRM_OBJ64_DIR)
	$(AT)$(DRM_CC_64) $(EXTRA_CFLAGS) -o "$(LIBDRM_OBJ64_DIR)/$(*F).o" "$<"