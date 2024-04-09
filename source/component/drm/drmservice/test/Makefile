ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

DRM_DIR=$(CURDIR)/../..
DRMSERVICE_SOURCE_DIR=$(CURDIR)/..

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


DRM_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++
DRM_AR := $(CFG_HI_TOOLCHAINS_NAME)-ar

#### directories
##################################################################################
BASE_INC_DIR  := $(DRM_DIR)/base/include
DRMSERVICE_INC_DIR      := $(DRMSERVICE_SOURCE_DIR)/include
DRMIPC_CLIENT_INC_DIR   := $(DRMSERVICE_SOURCE_DIR)/drm_ipc/client
DRMIPC_SERVER_INC_DIR   := $(DRMSERVICE_SOURCE_DIR)/drm_ipc/server
DRMPLUGIN_INC_DIR       := $(DRMSERVICE_SOURCE_DIR)/drmplugin
DRMPLUGIN_PRIV_INC_DIR  := $(DRMSERVICE_SOURCE_DIR)/drmplugin/private
INTERFACE_IMPL_INC_DIR  := $(DRMSERVICE_SOURCE_DIR)/interface_impl
DRMSERVICE_TEST_INC_DIR := $(DRMSERVICE_SOURCE_DIR)/test
DRMSERVICE_STTEST_INC_DIR := $(DRMSERVICE_SOURCE_DIR)/test/st
OPENSSL_INC_DIR         := $(HI_OUT_DIR)/obj/source/component/openssl/release/include
SERVICE_TEST_OBJ_DIR      := $(DRMSERVICE_SOURCE_DIR)/test/obj_$(CFG_HI_TOOLCHAINS_NAME)
SERVICE_STTEST_OBJ_DIR    := $(DRMSERVICE_SOURCE_DIR)/test/st/obj_$(CFG_HI_TOOLCHAINS_NAME)
SERVICE_TEST_OUTPUT_DIR   := $(DRMSERVICE_SOURCE_DIR)/test/$(CFG_HI_TOOLCHAINS_NAME)
SERVICE_TEST_OUTPUT_E     := $(SERVICE_TEST_OUTPUT_DIR)/drmservicetest
SERVICE_STTEST_OUTPUT_E   := $(SERVICE_TEST_OUTPUT_DIR)/drmservicetest_st

#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(BASE_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_PRIV_INC_DIR)
CFG_INC += -I$(DRMPLUGIN_INC_DIR)
CFG_INC += -I$(DRMSERVICE_INC_DIR)
CFG_INC += -I$(OPENSSL_INC_DIR)
CFG_INC += -I$(INTERFACE_IMPL_INC_DIR)
CFG_INC += -I$(DRMIPC_CLIENT_INC_DIR)
CFG_INC += -I$(DRMIPC_SERVER_INC_DIR)
CFG_INC += -I$(DRMSERVICE_TEST_INC_DIR)
CFG_INC += -I$(DRMSERVICE_STTEST_INC_DIR)

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
LIB := -lutils -lcutils -llog -lbinder_ipc -ldrm_common -ldrm
LIB += -lpthread -ldl -lssl -lcrypto

SERVICE_TEST_CPP=$(DRMSERVICE_SOURCE_DIR)/test/HTTPSource.cpp
SERVICE_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/HTTPStream.cpp
SERVICE_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/HTTPUtil.cpp
SERVICE_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/DrmServiceTest.cpp
SERVICE_TEST_OBJS := $(SERVICE_TEST_CPP:%.cpp=$(SERVICE_TEST_OBJ_DIR)/%.o)
$(SERVICE_TEST_OBJ_DIR)/%.o : %.cpp
	@[ -e $(SERVICE_TEST_OBJ_DIR) ] || mkdir -p $(SERVICE_TEST_OBJ_DIR)
	@$(DRM_CC) $(EXTRA_CFLAGS) -o "$(SERVICE_TEST_OBJ_DIR)/$(*F).o" "$<"

SERVICE_ST_TEST_CPP=$(DRMSERVICE_SOURCE_DIR)/test/st/common_log.cpp
SERVICE_ST_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/st/AutoTest_main.cpp
SERVICE_ST_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/HTTPSource.cpp
SERVICE_ST_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/HTTPStream.cpp
SERVICE_ST_TEST_CPP+=$(DRMSERVICE_SOURCE_DIR)/test/HTTPUtil.cpp
SERVICE_ST_TEST_OBJS := $(SERVICE_ST_TEST_CPP:%.cpp=$(SERVICE_STTEST_OBJ_DIR)/%.o)
$(SERVICE_STTEST_OBJ_DIR)/%.o : %.cpp
	@[ -e $(SERVICE_STTEST_OBJ_DIR) ] || mkdir -p $(SERVICE_STTEST_OBJ_DIR)
	@$(DRM_CC) $(EXTRA_CFLAGS) -o "$(SERVICE_STTEST_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all mkdrm_test mkdrm_st_test drmtest_clean
all:  mkdrm_test  mkdrm_st_test
clean: drmtest_clean

#********************* Create out dir ***********************
OBJS=$(shell ls $(SERVICE_TEST_OBJ_DIR)/*.o)

ST_OBJS=$(shell ls $(SERVICE_STTEST_OBJ_DIR)/*.o)
mkdrm_test: $(SERVICE_TEST_OBJS)
	@echo "Enter build drm service test..."
	@rm -f $(SERVICE_TEST_OUTPUT_E)

	@echo "create export dir"
	@[ -e $(SERVICE_TEST_OUTPUT_DIR) ] || mkdir -p $(SERVICE_TEST_OUTPUT_DIR)
	@echo "create drm service test output executable"
	@$(DRM_CC) -o $(SERVICE_TEST_OUTPUT_E) $(OBJS) $(LIBPATH) $(LIB)
	@echo "Leave build drm service test..."

mkdrm_st_test: $(SERVICE_ST_TEST_OBJS)
	@echo "Enter build drm service auto test..."
	@rm -f $(SERVICE_STTEST_OUTPUT_E)

	@echo "create export dir"
	@[ -e $(SERVICE_TEST_OUTPUT_DIR) ] || mkdir -p $(SERVICE_TEST_OUTPUT_DIR)

	@echo "create drm service auto test output executable"
	@$(DRM_CC) -o $(SERVICE_STTEST_OUTPUT_E) $(ST_OBJS) $(LIBPATH) $(LIB)
	@echo "Leave build drm service auto test..."

drmtest_clean:
	@rm -rf $(SERVICE_TEST_OBJ_DIR)
	@rm -rf $(SERVICE_STTEST_OBJ_DIR)
	@rm -rf $(SERVICE_TEST_OUTPUT_DIR)
