ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

C_DEFINES+=-D_DRMENGINE_M_IX86 $(_DRM_C_DEFINES)
#####################################################################
#        DIRECTORIES
#####################################################################

DRMENGINE_LOG_SOURCE_DIR := $(CURDIR)
DRMENGINE_LOG_INC_DIR := $(CURDIR)/../include

###############################include *h##########################################
CFG_INC := -I$(DRMENGINE_LOG_INC_DIR)
CFG_INC += -I$(DRMENGINE_LOG_SOURCE_DIR)
CFG_INC += -I$(DRMENGINE_LOG_INC_DIR)/arch/linux-arm
#********************* Define the objs *********************
EXTRA_CFLAGS :=
EXTRA_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE) -DBOARD_TYPE_$(CFG_BOARD_TYPE) -DSDK_VERSION=$(CFG_SDK_VERSION)
EXTRA_CFLAGS += $(C_DEFINES)
EXTRA_CFLAGS += -c -O2 -Wall $(CFG_INC) $(CFG_DEBUG) -fPIC
EXTRA_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600 
EXTRA_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
EXTRA_CFLAGS += -DHAVE_SYS_UIO_H=1
#EXTRA_CFLAGS += -DANDROID_SMP=0

# DRMENGINE_LOG_C :=
# DRMENGINE_LOG_C += event_tag_map.c
# DRMENGINE_LOG_C += logd_write_kern.c
# DRMENGINE_LOG_C += logprint.c

# DRMENGINE_LOG_CPP :=
# DRMENGINE_LOG_CPP += log_time.cpp

DRMENGINE_LOG_CPP=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.cpp"))
DRMENGINE_LOG_C=$(notdir $(shell find $(VPATH) -maxdepth 1 -name "*.c"))


DRMENGINE_LOG_OBJ_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(DRMENGINE_LOG_SOURCE_DIR))
DRMENGINE_LOG_OBJ64_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(DRMENGINE_LOG_SOURCE_DIR))

DRMENGINE_LOG_OBJS := $(DRMENGINE_LOG_C:%.c=$(DRMENGINE_LOG_OBJ_DIR)/%.o)
DRMENGINE_LOG_OBJS += $(DRMENGINE_LOG_CPP:%.cpp=$(DRMENGINE_LOG_OBJ_DIR)/%.o)

DRMENGINE_LOG_OBJS64 := $(DRMENGINE_LOG_C:%.c=$(DRMENGINE_LOG_OBJ64_DIR)/%.o)
DRMENGINE_LOG_OBJS64 += $(DRMENGINE_LOG_CPP:%.cpp=$(DRMENGINE_LOG_OBJ64_DIR)/%.o)

LIB_NAME := liblog

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += log
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += log64
endif

.PHONY: all log log64 log_clean
all: $(TARGETS)
clean: log_clean

#********************* Create out dir ***********************
log: $(DRMENGINE_LOG_OBJS)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_LOG_OBJ_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc -shared -o $(DRMENGINE_LOG_OBJ_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB_DIR) ] || mkdir -p $(HI_STATIC_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_LOG_OBJ_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB_DIR) ] || mkdir -p $(HI_SHARED_LIB_DIR)
	$(AT)cp -f $(DRMENGINE_LOG_OBJ_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB_DIR)/

log64: $(DRMENGINE_LOG_OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar -rsv $(DRMENGINE_LOG_OBJ64_DIR)/$(LIB_NAME).a $^
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ -shared -o $(DRMENGINE_LOG_OBJ64_DIR)/$(LIB_NAME).so $^

	$(AT)[ -e $(HI_STATIC_LIB64_DIR) ] || mkdir -p $(HI_STATIC_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_LOG_OBJ64_DIR)/$(LIB_NAME).a $(HI_STATIC_LIB64_DIR)/

	$(AT)[ -e $(HI_SHARED_LIB64_DIR) ] || mkdir -p $(HI_SHARED_LIB64_DIR)
	$(AT)cp -f $(DRMENGINE_LOG_OBJ64_DIR)/$(LIB_NAME).so $(HI_SHARED_LIB64_DIR)/

log_clean:
	$(AT)rm -rf $(DRMENGINE_LOG_OBJ_DIR) $(DRMENGINE_LOG_OBJ64_DIR)
	$(AT)rm -rf $(HI_STATIC_LIB_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB_DIR)/$(LIB_NAME).so
	$(AT)rm -rf $(HI_STATIC_LIB64_DIR)/$(LIB_NAME).a $(HI_SHARED_LIB64_DIR)/$(LIB_NAME).so

$(DRMENGINE_LOG_OBJ_DIR)/%.o : %.c*
	$(AT)[ -e $(DRMENGINE_LOG_OBJ_DIR) ] || mkdir -p $(DRMENGINE_LOG_OBJ_DIR)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(EXTRA_CFLAGS) -o "$(DRMENGINE_LOG_OBJ_DIR)/$(*F).o" "$<"


$(DRMENGINE_LOG_OBJ64_DIR)/%.o : %.c*
	$(AT)[ -e $(DRMENGINE_LOG_OBJ64_DIR) ] || mkdir -p $(DRMENGINE_LOG_OBJ64_DIR)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-g++ $(EXTRA_CFLAGS) --std=c++11 -o "$(DRMENGINE_LOG_OBJ64_DIR)/$(*F).o" "$<"
