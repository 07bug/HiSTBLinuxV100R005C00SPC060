ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

#####################################################################
#        DIRECTORIES
#####################################################################

DRMENGINE_IPC_SOURCE_DIR := $(CURDIR)
DRMENGINE_IPC_INC_DIR := $(CURDIR)/../include

###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(DRMENGINE_IPC_INC_DIR)
CFG_INC += -I$(DRMENGINE_IPC_SOURCE_DIR)
CFG_INC += -I$(DRMENGINE_IPC_INC_DIR)/arch/linux-arm

#### objs
###################################################################################
VPATH := $(DRMENGINE_IPC_SOURCE_DIR)/binder

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) -fPIC
EXTRA_CFLAGS += -DBINDER_IPC_32BIT=1
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

LIB := -lcutils -lutils -llog

DRMENGINE_IPC=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))

DRMENGINE_IPC_OBJ_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMENGINE_IPC_SOURCE_DIR))
DRMENGINE_IPC_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMENGINE_IPC_SOURCE_DIR))

DRMENGINE_IPC_OBJS := $(DRMENGINE_IPC:%.cpp=$(DRMENGINE_IPC_OBJ_DIR)/%.o)
DRMENGINE_IPC_OBJS64 := $(DRMENGINE_IPC:%.cpp=$(DRMENGINE_IPC_OBJ64_DIR)/%.o)

LIB_NAME := libbinder_ipc

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += ipc
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += ipc64
endif

.PHONY: all ipc ipc64 ipc_clean

all: $(TARGETS)

clean: ipc_clean

ipc: $(DRMENGINE_IPC_OBJS)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_IPC_OBJ_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ -shared -o $(DRMENGINE_IPC_OBJ_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_IPC_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_IPC_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

ipc64: $(DRMENGINE_IPC_OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_IPC_OBJ64_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ -shared -o $(DRMENGINE_IPC_OBJ64_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_IPC_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_IPC_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

ipc_clean:
	$(AT)rm -rf $(DRMENGINE_IPC_OBJ_DIR) $(DRMENGINE_IPC_OBJ64_DIR)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so

$(DRMENGINE_IPC_OBJ_DIR)/%.o : %.cpp
	$(AT)[ -e $(DRMENGINE_IPC_OBJ_DIR) ] || mkdir -p $(DRMENGINE_IPC_OBJ_DIR)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) -o "$(DRMENGINE_IPC_OBJ_DIR)/$(*F).o" "$<"

$(DRMENGINE_IPC_OBJ64_DIR)/%.o : %.cpp
	$(AT)[ -e $(DRMENGINE_IPC_OBJ64_DIR) ] || mkdir -p $(DRMENGINE_IPC_OBJ64_DIR)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) --std=c++11 -o "$(DRMENGINE_IPC_OBJ64_DIR)/$(*F).o" "$<"


