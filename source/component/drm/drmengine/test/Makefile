ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

DRM_DIR=$(CURDIR)/../..
DRMENGINE_DIR=$(CURDIR)/..

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
	MULTI_PROCESS := y
else
	MULTI_PROCESS := n
endif

CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)
DST_SHARED_LIB_DIR := $(HI_SHARED_LIB_DIR)
DST_STATIC_LIB_DIR := $(HI_STATIC_LIB_DIR)


# CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)
# DST_SHARED_LIB_DIR := $(HI_SHARED_LIB64_DIR)
# DST_STATIC_LIB_DIR := $(HI_STATIC_LIB64_DIR)


DRMENGINE_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRMENGINE_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

#### directories
##################################################################################
BASE_INC_DIR  := $(DRM_DIR)/base/include
BASE_COMMON_INC_DIR  := $(DRM_DIR)/base/include/common
DRMSERVICE_INC_DIR      := $(DRM_DIR)/drmservice/include
DRMIPC_CLIENT_INC_DIR   := $(DRM_DIR)/drmservice/drm_ipc/client
DRMIPC_SERVER_INC_DIR   := $(DRM_DIR)/drmservice/drm_ipc/server
DRMPLUGIN_INC_DIR       := $(DRM_DIR)/drmservice/drmplugin
DRMPLUGIN_PRIV_INC_DIR  := $(DRM_DIR)/drmservice/drmplugin/private
INTERFACE_IMPL_INC_DIR  := $(DRM_DIR)/drmservice/interface_impl
DRMENGINE_TEST_INC_DIR := $(DRMENGINE_DIR)/test
DRMENGINE_STTEST_INC_DIR := $(DRMENGINE_DIR)/test/st
OPENSSL_INC_DIR         := $(HI_OUT_DIR)/obj/source/component/openssl/release/include/
DRMENGINE_TEST_OBJ_DIR      := $(DRMENGINE_DIR)/test/obj_$(CFG_HI_TOOLCHAINS_NAME)
DRMENGINE_STTEST_OBJ_DIR    := $(DRMENGINE_DIR)/test/st/obj_$(CFG_HI_TOOLCHAINS_NAME)
DRMENGINE_TEST_OUTPUT_DIR   := $(DRMENGINE_DIR)/test/$(CFG_HI_TOOLCHAINS_NAME)/
DRMENGINE_TEST_OUTPUT_E     := $(DRMENGINE_DIR)/test/$(CFG_HI_TOOLCHAINS_NAME)/drmenginetest
DRMENGINE_STTEST_OUTPUT_E     := $(DRMENGINE_DIR)/test/$(CFG_HI_TOOLCHAINS_NAME)/drmenginetest_st

#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(BASE_INC_DIR)
CFG_INC += -I$(BASE_COMMON_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_PRIV_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_INC_DIR)
CFG_INC += -I$(DRMSERVICE_INC_DIR)
CFG_INC += -I$(OPENSSL_INC_DIR)
CFG_INC += -I$(INTERFACE_IMPL_INC_DIR)
CFG_INC += -I$(DRMIPC_CLIENT_INC_DIR)
CFG_INC += -I$(DRMIPC_SERVER_INC_DIR)
CFG_INC += -I$(DRMENGINE_TEST_INC_DIR)
CFG_INC += -I$(DRMENGINE_STTEST_INC_DIR)
CFG_INC += -I$(DRMENGINE_DIR)

#### objs
###################################################################################
EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) -fpermissive
ifeq ($(MULTI_PROCESS), y)
EXTRA_CFLAGS += -DMULTI_PROCESS
endif
EXTRA_CFLAGS += -DUSE_SW_DECRYPTION
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DLINUX_DEBUGLOG

LIBPATH := -L$(DST_SHARED_LIB_DIR) -L$(DST_STATIC_LIB_DIR)
LIB := -lutils -lcutils -llog -lbinder_ipc -ldrm_common -ldrm -ldrmengine
LIB += -ldl -lpthread -lssl -lcrypto

DRMENGINE_TEST_CPP=$(DRMENGINE_DIR)/test/HTTPSource.cpp
DRMENGINE_TEST_CPP+=$(DRMENGINE_DIR)/test/HTTPStream.cpp
DRMENGINE_TEST_CPP+=$(DRMENGINE_DIR)/test/HTTPUtil.cpp
DRMENGINE_TEST_CPP+=$(DRMENGINE_DIR)/test/DrmEngineTest.cpp
DRMENGINE_TEST_OBJS := $(DRMENGINE_TEST_CPP:%.cpp=$(DRMENGINE_TEST_OBJ_DIR)/%.o)
$(DRMENGINE_TEST_OBJ_DIR)/%.o : %.cpp
	@[ -e $(DRMENGINE_TEST_OBJ_DIR) ] || mkdir -p $(DRMENGINE_TEST_OBJ_DIR)
	@$(DRMENGINE_CC) $(EXTRA_CFLAGS) -o "$(DRMENGINE_TEST_OBJ_DIR)/$(*F).o" "$<"

DRMENGINE_ST_TEST_CPP=$(DRMENGINE_DIR)/test/st/common_log.cpp
DRMENGINE_ST_TEST_CPP+=$(DRMENGINE_DIR)/test/st/AutoTest_main.cpp
DRMENGINE_ST_TEST_CPP+=$(DRMENGINE_DIR)/test/HTTPSource.cpp
DRMENGINE_ST_TEST_CPP+=$(DRMENGINE_DIR)/test/HTTPStream.cpp
DRMENGINE_ST_TEST_CPP+=$(DRMENGINE_DIR)/test/HTTPUtil.cpp
DRMENGINE_ST_TEST_OBJS := $(DRMENGINE_ST_TEST_CPP:%.cpp=$(DRMENGINE_STTEST_OBJ_DIR)/%.o)
$(DRMENGINE_STTEST_OBJ_DIR)/%.o : %.cpp
	@[ -e $(DRMENGINE_STTEST_OBJ_DIR) ] || mkdir -p $(DRMENGINE_STTEST_OBJ_DIR)
	@$(DRMENGINE_CC) $(EXTRA_CFLAGS) -o "$(DRMENGINE_STTEST_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all mkdrmengine_test mkdrmengine_st_test drmenginetest_clean
all:  mkdrmengine_test  mkdrmengine_st_test
clean: drmenginetest_clean

#********************* Create out dir ***********************
OBJS=$(shell ls $(DRMENGINE_TEST_OBJ_DIR)/*.o)

ST_OBJS=$(shell ls $(DRMENGINE_STTEST_OBJ_DIR)/*.o)

mkdrmengine_test: $(DRMENGINE_TEST_OBJS)
	@echo "Enter build drmengine test..."
	@rm -f $(DRMENGINE_TEST_OUTPUT_E)

	@echo "create export dir"
	@[ -e $(DRMENGINE_TEST_OUTPUT_DIR) ] || mkdir -p $(DRMENGINE_TEST_OUTPUT_DIR)

	@echo "create drmengine test output executable"
	@$(DRMENGINE_CC) -o $(DRMENGINE_TEST_OUTPUT_E) $(OBJS) $(LIBPATH) $(LIB)
	@echo "Leave build drmengine test..."

mkdrmengine_st_test: $(DRMENGINE_ST_TEST_OBJS)
	@echo "Enter build drmengine auto test..."
	@rm -f $(DRMENGINE_STTEST_OUTPUT_E)

	@echo "create export dir"
	@[ -e $(DRMENGINE_TEST_OUTPUT_DIR) ] || mkdir -p $(DRMENGINE_TEST_OUTPUT_DIR)

	@echo "create drmengine auto test output executable"
	@$(DRMENGINE_CC) -o $(DRMENGINE_STTEST_OUTPUT_E) $(ST_OBJS) $(LIBPATH) $(LIB)
	@echo "Leave build drmengine auto test..."

drmenginetest_clean:
	@rm -rf $(DRMENGINE_TEST_OBJ_DIR)
	@rm -rf $(DRMENGINE_STTEST_OBJ_DIR)
	@rm -rf $(DRMENGINE_TEST_OUTPUT_DIR)
#	@rm -f $(DST_SHARED_LIB_DIR)/libdrm_common*
