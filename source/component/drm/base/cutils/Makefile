ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

#####################################################################
#        DIRECTORIES
#####################################################################

DRM_CUTIL_SOURCE_DIR := $(CURDIR)
DRM_CUTIL_INC_DIR := $(CURDIR)/../include

CFG_HI_TOOLCHAINS_NAME    := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CFG_HI_TOOLCHAINS_NAME_64 := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)

DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

DRM_CC_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-g++
DRM_AR_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-ar
###############################include *h##########################################
CFG_INC := -I$(DRM_CUTIL_INC_DIR)
CFG_INC += -I$(DRM_CUTIL_SOURCE_DIR)
CFG_INC += -I$(DRM_CUTIL_INC_DIR)/arch/linux-arm
#********************* Define the objs *********************
EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) $(CFG_DEBUG) -fPIC -DUSE_AEC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DANDROID_SMP=0

DRM_CUTIL :=
DRM_CUTIL += hashmap.c
DRM_CUTIL += native_handle.c
DRM_CUTIL += socket_inaddr_any_server_unix.c
DRM_CUTIL += socket_local_client_unix.c
DRM_CUTIL += socket_local_server_unix.c
DRM_CUTIL += socket_loopback_client_unix.c
DRM_CUTIL += socket_loopback_server_unix.c
DRM_CUTIL += socket_network_client_unix.c
DRM_CUTIL += config_utils.c
DRM_CUTIL += load_file.c
DRM_CUTIL += strdup16to8.c
DRM_CUTIL += strdup8to16.c
DRM_CUTIL += process_name.c
DRM_CUTIL += properties.c
DRM_CUTIL += threads.c
DRM_CUTIL += sched_policy.c
DRM_CUTIL += ashmem-dev.c
DRM_CUTIL += memory.c
DRM_CUTIL += klog.c
DRM_CUTIL += atomic.c

DRM_CUTIL_OBJ_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRM_CUTIL_SOURCE_DIR))
DRM_CUTIL_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRM_CUTIL_SOURCE_DIR))

DRM_CUTIL_OBJS := $(DRM_CUTIL:%.c=$(DRM_CUTIL_OBJ_DIR)/%.o)
DRM_CUTIL_OBJS64 := $(DRM_CUTIL:%.c=$(DRM_CUTIL_OBJ64_DIR)/%.o)

LIB_NAME := libcutils

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += cutils
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += cutils64
endif

.PHONY: all cutils cutils64 cutils_clean

all: $(TARGETS)

clean: cutils_clean

cutils: $(DRM_CUTIL_OBJS)
	$(AT)$(DRM_AR) -rsv $(DRM_CUTIL_OBJ_DIR)/$(LIB_NAME).a $^
	$(AT)$(DRM_CC) -shared -o $(DRM_CUTIL_OBJ_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -f $(DRM_CUTIL_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(DRM_CUTIL_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

cutils64: $(DRM_CUTIL_OBJS64)
	$(AT)$(DRM_AR_64) -rsv $(DRM_CUTIL_OBJ64_DIR)/$(LIB_NAME).a $^
	$(AT)$(DRM_CC_64) -shared -o $(DRM_CUTIL_OBJ64_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -f $(DRM_CUTIL_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(DRM_CUTIL_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

cutils_clean:
	$(AT)rm -rf $(DRM_CUTIL_OBJ_DIR) $(DRM_CUTIL_OBJ64_DIR)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so

$(DRM_CUTIL_OBJ_DIR)/%.o : %.c
	$(AT)[ -e $(DRM_CUTIL_OBJ_DIR) ] || mkdir -p $(DRM_CUTIL_OBJ_DIR)
	$(AT)$(DRM_CC) $(EXTRA_CFLAGS) -o "$(DRM_CUTIL_OBJ_DIR)/$(*F).o" "$<"

$(DRM_CUTIL_OBJ64_DIR)/%.o : %.c
	$(AT)[ -e $(DRM_CUTIL_OBJ64_DIR) ] || mkdir -p $(DRM_CUTIL_OBJ64_DIR)
	$(AT)$(DRM_CC_64) $(EXTRA_CFLAGS) --std=c++11 -o "$(DRM_CUTIL_OBJ64_DIR)/$(*F).o" "$<"
