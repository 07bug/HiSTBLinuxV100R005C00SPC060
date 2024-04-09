ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)

#####################################################################
#        DIRECTORIES
#####################################################################

DRMENGINE_UTIL_SOURCE_DIR := $(CURDIR)
DRMENGINE_UTIL_INC_DIR := $(CURDIR)/../include

###############################include *h##########################################

CFG_INC := -I$(DRMENGINE_UTIL_INC_DIR)
CFG_INC += -I$(DRMENGINE_UTIL_SOURCE_DIR)
CFG_INC += -I$(DRMENGINE_UTIL_INC_DIR)/arch/linux-arm

#********************* Define the objs *********************

EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall -std=c++11 $(CFG_INC) $(CFG_DEBUG) -fPIC -fpermissive
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64




LIB :=
LIB += -lcutils -lpthread -lm -lc

DRMENGINE_UTIL=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))

DRMENGINE_UTIL_OBJ_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMENGINE_UTIL_SOURCE_DIR))
DRMENGINE_UTIL_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMENGINE_UTIL_SOURCE_DIR))

DRMENGINE_UTIL_OBJS := $(DRMENGINE_UTIL:%.cpp=$(DRMENGINE_UTIL_OBJ_DIR)/%.o)
DRMENGINE_UTIL_OBJS64 := $(DRMENGINE_UTIL:%.cpp=$(DRMENGINE_UTIL_OBJ64_DIR)/%.o)


LIB_NAME := libutils

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += utils
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += utils64
endif

.PHONY: all utils utils64 utils_clean

all: $(TARGETS)

clean: utils_clean


utils: $(DRMENGINE_UTIL_OBJS)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_UTIL_OBJ_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ -shared -o $(DRMENGINE_UTIL_OBJ_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_UTIL_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_UTIL_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

utils64: $(DRMENGINE_UTIL_OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_UTIL_OBJ64_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ -shared -o $(DRMENGINE_UTIL_OBJ64_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_UTIL_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_UTIL_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

utils_clean:
	$(AT)rm -rf $(DRMENGINE_UTIL_OBJ_DIR) $(DRMENGINE_UTIL_OBJ64_DIR)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so

$(DRMENGINE_UTIL_OBJ_DIR)/%.o : %.cpp
	$(AT)[ -e $(DRMENGINE_UTIL_OBJ_DIR) ] || mkdir -p $(DRMENGINE_UTIL_OBJ_DIR)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) -o "$(DRMENGINE_UTIL_OBJ_DIR)/$(*F).o" "$<"

$(DRMENGINE_UTIL_OBJ64_DIR)/%.o : %.cpp
	$(AT)[ -e $(DRMENGINE_UTIL_OBJ64_DIR) ] || mkdir -p $(DRMENGINE_UTIL_OBJ64_DIR)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) --std=c++11 -o "$(DRMENGINE_UTIL_OBJ64_DIR)/$(*F).o" "$<"