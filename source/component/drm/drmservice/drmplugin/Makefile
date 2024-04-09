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

DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

#### directories
##################################################################################
DRMPLUGIN_SRC_DIR := $(CURDIR)/private
DRMPLUGIN_INC_DIR := $(CURDIR)/../../base/include

DRMPLUGIN_PRIV_INC_DIR := $(CURDIR)/private

LIBDRM_COMMON_OBJ_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMPLUGIN_SRC_DIR))
LIBDRM_COMMON_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMPLUGIN_SRC_DIR))

#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(DRMPLUGIN_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_SRC_DIR)
CFG_INC += -I$(DRMPLUGIN_PRIV_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_INC_DIR)/arch/linux-arm

#### objs
###################################################################################
VPATH := $(DRMIPC_CLIENT_SRC_DIR)
VPATH += $(DRMIPC_SERVER_SRC_DIR)
VPATH += $(INTERFACE_IMPL_SRC_DIR)

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) -fPIC -fpermissive
ifeq ($(MULTI_PROCESS), y)
EXTRA_CFLAGS += -DMULTI_PROCESS
endif
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DLINUX_DEBUGLOG


LIBDRM_COMMON_CPP :=
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/AString.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/ABuffer.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/ALooper.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/AMessage.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/AHandler.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/base64.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/AAtomizer.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/hexdump.cpp
LIBDRM_COMMON_CPP += $(DRMPLUGIN_SRC_DIR)/ALooperRoster.cpp

LIBDRM_COMMON_OBJS := $(LIBDRM_COMMON_CPP:%.cpp=$(LIBDRM_COMMON_OBJ_DIR)/%.o)

LIBDRM_COMMON_OBJS64 := $(LIBDRM_COMMON_CPP:%.cpp=$(LIBDRM_COMMON_OBJ64_DIR)/%.o)

LIB_NAME := libdrm_common

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += libdrm_common
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += libdrm_common64
endif

.PHONY: all libdrm_common  libdrm_common64 drmcommon_clean 

all: $(TARGETS)

clean: drmcommon_clean

#********************* Create out dir ***********************
DRMCOMMON_OBJS=$(shell ls $(LIBDRM_COMMON_OBJ_DIR)/*.o)
DRMCOMMON_OBJS64=$(shell ls $(LIBDRM_COMMON_OBJ64_DIR)/*.o)

libdrm_common: $(LIBDRM_COMMON_OBJS)
#	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -rsv $(LIBDRM_COMMON_OBJ_DIR)/$(LIB_NAME).a $(DRMCOMMON_OBJS)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ -shared -o $(LIBDRM_COMMON_OBJ_DIR)/$(LIB_NAME).so $(DRMCOMMON_OBJS)

#	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
#	$(AT)cp -f $(LIBDRM_COMMON_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(LIBDRM_COMMON_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

libdrm_common64: $(LIBDRM_COMMON_OBJS64)
#	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar -rsv $(LIBDRM_COMMON_OBJ64_DIR)/$(LIB_NAME).a $(DRMCOMMON_OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ -shared -o $(LIBDRM_COMMON_OBJ64_DIR)/$(LIB_NAME).so $(DRMCOMMON_OBJS64)

#	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
#	$(AT)cp -f $(LIBDRM_COMMON_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(LIBDRM_COMMON_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

drmcommon_clean:
	$(AT)rm -rf $(LIBDRM_COMMON_OBJ_DIR) $(LIBDRM_COMMON_OBJ64_DIR)
	$(AT)rm -rf $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so
#	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a 

$(LIBDRM_COMMON_OBJ_DIR)/%.o : %.cpp
	$(AT)[ -e $(LIBDRM_COMMON_OBJ_DIR) ] || mkdir -p $(LIBDRM_COMMON_OBJ_DIR)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) -o "$(LIBDRM_COMMON_OBJ_DIR)/$(*F).o" "$<"

$(LIBDRM_COMMON_OBJ64_DIR)/%.o : %.cpp
	$(AT)[ -e $(LIBDRM_COMMON_OBJ64_DIR) ] || mkdir -p $(LIBDRM_COMMON_OBJ64_DIR)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) -o "$(LIBDRM_COMMON_OBJ64_DIR)/$(*F).o" "$<"