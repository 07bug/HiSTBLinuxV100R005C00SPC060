ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)


ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
	MULTI_PROCESS := y
else
	MULTI_PROCESS := n
endif

CFG_HI_TOOLCHAINS_NAME    := $(CFG_HI_ARM_TOOLCHAINS_NAME)
CFG_HI_TOOLCHAINS_NAME_64 := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)

DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

DRM_CC_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-g++
DRM_AR_64 := $(CFG_HI_TOOLCHAINS_NAME_64)-ar

#####################################################################
#        DIRECTORIES
#####################################################################


DRMENGINE_SRC_DIR    := $(CURDIR)
DRM_DIR              := $(CURDIR)/..
BASE_INC_DIR         := $(DRM_DIR)/base/include
BASE_COMMON_INC_DIR  := $(DRM_DIR)/base/include/common
DRMSERVICE_INC_DIR   := $(DRM_DIR)/drmservice/include

LIB_DRMENGINE_OBJ_DIR   := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMENGINE_SRC_DIR))
LIB_DRMENGINE_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMENGINE_SRC_DIR))

# LIB_DRMENGINE_OUTPUT_DIR   := $(DRMENGINE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/
# LIB_DRMENGINE_OUTPUT_S     := $(LIB_DRMENGINE_OUTPUT_DIR)/libdrmengine.so
# LIB_DRMENGINE_OUTPUT_ROOTFS_DIR   := $(HI_ROOTFS_DIR)/lib
# LIB_DRMENGINE_OUTPUT_ROOTFS_S     := $(LIB_DRMENGINE_OUTPUT_ROOTFS_DIR)/libdrmengine.so

# LIB_DRMENGINE_OUTPUT_DIR_64   := $(DRMENGINE_DIR)/$(CFG_HI_TOOLCHAINS_NAME_64)/
# LIB_DRMENGINE_OUTPUT_S_64     := $(LIB_DRMENGINE_OUTPUT_DIR_64)/libdrmengine.so
# LIB_DRMENGINE_OUTPUT_ROOTFS_DIR_64   := $(HI_ROOTFS_DIR)/lib64
# LIB_DRMENGINE_OUTPUT_ROOTFS_S_64     := $(LIB_DRMENGINE_OUTPUT_ROOTFS_DIR_64)/libdrmengine.so

LIBPATH := -L $(HI_STATIC_LIB_DIR)
LIBPATH += -L $(HI_SHARED_LIB_DIR)

LIBPATH_64 := -L $(HI_STATIC_LIB64_DIR)
LIBPATH_64 += -L $(HI_SHARED_LIB64_DIR)

LIB := -ldrm -llog -lutils -lcutils

LIB_NAME := libdrmengine

#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(DRMENGINE_SRC_DIR)
CFG_INC += -I$(DRM_DIR)
CFG_INC += -I$(BASE_INC_DIR)
CFG_INC += -I$(BASE_COMMON_INC_DIR)
CFG_INC += -I$(DRMSERVICE_INC_DIR)

#CFG_INC += -I$(SDK_DIR)/source/tee/core/trustedcore/libteec/inc 
#### objs
###################################################################################
VPATH := $(DRMENGINE_SRC_DIR)

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


LIB_DRMENGINE_C      = $(DRMENGINE_SRC_DIR)/DrmEngine.c

LIB_DRMENGINE_OBJS   := $(LIB_DRMENGINE_C:%.c=$(LIB_DRMENGINE_OBJ_DIR)/%.o)

LIB_DRMENGINE_OBJS64 := $(LIB_DRMENGINE_C:%.c=$(LIB_DRMENGINE_OBJ64_DIR)/%.o)


#===============================================================================
# rules
#===============================================================================

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += drmengine
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += drmengine64
endif


.PHONY: all drmengine drmengine64 clean

all: $(TARGETS)

clean: drmengine_clean

#********************* Create out dir ***********************
OBJS=$(shell ls $(LIB_DRMENGINE_OBJ_DIR)/*.o)
OBJS_64=$(shell ls $(LIB_DRMENGINE_OBJ64_DIR)/*.o)

drmengine: $(LIB_DRMENGINE_OBJS)

	$(AT)$(DRM_AR) -rs $(LIB_DRMENGINE_OBJ_DIR)/$(LIB_NAME).a $(OBJS)
	$(AT)$(DRM_CC) -shared -o $(LIB_DRMENGINE_OBJ_DIR)/$(LIB_NAME).so $(OBJS)

	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -f $(LIB_DRMENGINE_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(LIB_DRMENGINE_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

drmengine64: $(LIB_DRMENGINE_OBJS64)
	$(AT)$(DRM_AR_64) -rs $(LIB_DRMENGINE_OBJ64_DIR)/$(LIB_NAME).a $(OBJS_64)
	$(AT)$(DRM_CC_64) -shared -o $(LIB_DRMENGINE_OBJ64_DIR)/$(LIB_NAME).so $(OBJS_64)

	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -f $(LIB_DRMENGINE_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(LIB_DRMENGINE_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

drmengine_clean:
	$(AT)rm -rf $(LIB_DRMENGINE_OBJ_DIR) $(LIB_DRMENGINE_OBJ64_DIR)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so


$(LIB_DRMENGINE_OBJ_DIR)/%.o : %.c
	@[ -e $(LIB_DRMENGINE_OBJ_DIR) ] || mkdir -p $(LIB_DRMENGINE_OBJ_DIR)
	@$(DRM_CC) $(EXTRA_CFLAGS) -o "$(LIB_DRMENGINE_OBJ_DIR)/$(*F).o" "$<"


$(LIB_DRMENGINE_OBJ64_DIR)/%.o : %.c
	@[ -e $(LIB_DRMENGINE_OBJ64_DIR) ] || mkdir -p $(LIB_DRMENGINE_OBJ64_DIR)
	@$(DRM_CC_64) $(EXTRA_CFLAGS) -o "$(LIB_DRMENGINE_OBJ64_DIR)/$(*F).o" "$<"

