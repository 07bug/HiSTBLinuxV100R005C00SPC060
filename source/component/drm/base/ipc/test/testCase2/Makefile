ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

DRMENGINE_DIR=$(CURDIR)/../../../..

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

ifeq ($(HI_USER_SPACE_LIB),y)
CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)
DST_SHARED_LIB_DIR := $(HI_SHARED_LIB_DIR)
DST_STATIC_LIB_DIR := $(HI_STATIC_LIB_DIR)
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
CFG_HI_TOOLCHAINS_NAME := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)
DST_SHARED_LIB_DIR := $(HI_SHARED_LIB64_DIR)
DST_STATIC_LIB_DIR := $(HI_STATIC_LIB64_DIR)
endif

DRMENGINE_CC := $(CFG_HI_TOOLCHAINS_NAME)-g++

#### directories
##################################################################################
TEST_SOURCE_DIR   := $(DRMENGINE_DIR)/base/ipc/test/testCase2
DRMENGINE_IPC_INC_DIR   := $(DRMENGINE_DIR)/base/include

TEST_OBJ_DIR      := $(TEST_SOURCE_DIR)/obj_$(CFG_HI_TOOLCHAINS_NAME)
TEST_OUT_DIR      := $(TEST_SOURCE_DIR)/$(CFG_HI_TOOLCHAINS_NAME)/
TEST_OUT_BIN      := $(TEST_OUT_DIR)/ipctest2
TEST_OUT_SERVERBIN      := $(TEST_OUT_DIR)/ipctest2_server


#### open debug
###############################include *h##########################################
CFG_INC := 
CFG_INC += -I$(DRMENGINE_IPC_INC_DIR)
CFG_INC += -I$(DRMENGINE_IPC_INC_DIR)/arch/linux-arm

#### objs
###################################################################################
VPATH := $(TEST_SOURCE_DIR)/testCase1

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC)
EXTRA_CFLAGS += -DBINDER_IPC_32BIT=1
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

LIBPATH := -L$(DST_SHARED_LIB_DIR) -L$(DST_STATIC_LIB_DIR)
LIB := -lbinder_ipc -lcutils -lutils -llog
LIB += -lrt -lpthread -lm

TEST_CPP=test_client_main.cpp IMyTestService.cpp
TEST_OBJS := $(TEST_CPP:%.cpp=$(TEST_OBJ_DIR)/%.o)
TEST_SERVER_CPP= service_main.cpp MyTestService.cpp IMyTestService.cpp
TEST_SERVER_OBJS := $(TEST_SERVER_CPP:%.cpp=$(TEST_OBJ_DIR)/%.o)

$(TEST_OBJ_DIR)/%.o : %.cpp
	@[ -e $(TEST_OBJ_DIR) ] || mkdir $(TEST_OBJ_DIR)
	@$(DRMENGINE_CC) $(EXTRA_CFLAGS) -o "$(TEST_OBJ_DIR)/$(*F).o" "$<"

.PHONY: all test_client test_server test_clean
all:  test_client test_server
clean: test_clean

#********************* Create out dir ***********************
test_client: $(TEST_OBJS)
	@rm -f $(TEST_OUT_BIN)
	@mkdir -p $(TEST_OUT_DIR)
	
	@$(DRMENGINE_CC) -o $(TEST_OUT_BIN) $(TEST_OBJS) $(LIBPATH) $(LIB)

test_server: $(TEST_SERVER_OBJS)
	@rm -f $(TEST_OUT_SERVERBIN)
	@mkdir -p $(TEST_OUT_DIR)
	
	@$(DRMENGINE_CC) -o $(TEST_OUT_SERVERBIN) $(TEST_SERVER_OBJS) $(LIBPATH) $(LIB)

test_clean:
	@rm -rf $(TEST_OBJ_DIR)
	@rm -rf $(TEST_OUT_DIR)