###################### tool chain #######################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif

#****** 定义目标输出名称的  ****************************************************
TARGET = libHA.AUDIO.SONIC

#****** 定义要编译目标文件的存放位置 *******************************************
CUR_DIR  = .
OBJ_DIR  = $(CUR_DIR)/lib/obj
LIB_DIR  = $(CUR_DIR)/lib

SND_EXT_PATH = $(CUR_DIR)/external/sonic

################################################################################
#****** 定义源代码及头文件的位置 ***********************************************
INC_DIR = $(CUR_DIR)/include

#****** 定义头文件的搜索路径 ***************************************************
CFG_INC += \
	-I$(CUR_DIR)/include \
	-I$(SND_EXT_PATH)

CFG_INC += \
	-I$(SDK_DIR)/source/msp/include \
	-I$(SDK_DIR)/source/common/include
################################################################################
#
# compiler flags
#
CFLAGS += $(CFG_INC)
CFLAGS += $(subst -Werror,,$(CFG_HI_CFLAGS))
CFLAGS += $(AUDIO_ADVCA_CFLAGS)
################################################################################
##当高安选项打开时，由于高安要求SDK api不编译静态库，所以SDK顶层Makefile中把-fPIC去掉了，但audio模块必须要使用-fPIC，故做此处理
ifneq ($(findstring -fPIC, $(CFG_HI_CFLAGS)), -fPIC)
CFLAGS += -fPIC
endif
################################################################################
TARGET_LIB := $(LIB_DIR)/$(TARGET).so

################################################################################



################################################################################
# source files
C_SRCS := \
	$(wildcard $(CUR_DIR)/*.c)
	 
C_SRCS += $(SND_EXT_PATH)/sonic.c
CPP_SRCS := 

ASM_SRCS :=

# ALL_SRC := $(CPP_SRCS) $(C_SRCS) $(ASM_SRCS)
################################################################################
# object files
OBJS := $(patsubst %.c,%.o,$(C_SRCS))
OBJS += $(patsubst %.cpp,%.o,$(CPP_SRCS))
OBJS += $(patsubst %.S,%.o,$(ASM_SRCS))

ALL_OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJS)))
################################################################################
# 添加文件搜索路径，不适用存在2个源文件文件名相同的场景下
vpath %.c $(C_SRCS) $(SND_EXT_PATH)
#vpath %.cpp 
# vpath %.S $(SRC_DIR)/armgcc
################################################################################
# 编译规则，所有.o文件都被放到指定目录
$(OBJ_DIR)/%.o: %.c
	$(AT)echo "  CC      $<"
	$(AT)$(CC) -c $(CFLAGS) $< -o $@
$(OBJ_DIR)/%.o: %.S
	$(AT)echo "  CC      $<"
	$(AT)$(CC) -c $(CFLAGS) $< -o $@
$(OBJ_DIR)/%.o: %.cpp
	$(AT)echo "  CC      $<"
	$(AT)$(CC) -c $(CFLAGS) $< -o $@
################################################################################
.PHONY: prepare all clean install uninstall

################################################################################
# 编译目标，注意考虑多线程编译
all: install

prepare:
	$(AT)mkdir -p $(LIB_DIR) $(OBJ_DIR) 

$(ALL_OBJS): prepare

target: $(ALL_OBJS)
	$(AT)$(CC) -o $(TARGET_LIB) -shared $(ALL_OBJS)

clean:
	$(AT)rm -rf $(OBJ_DIR)/*.o
	$(AT)rm -rf $(LIB_DIR)/*.so
	$(AT)rm -rf $(HI_EXTERN_LIB_DIR)/libHA.AUDIO.SONIC.so
	$(AT)rm -rf $(HI_INCLUDE_DIR)/HA.AUDIO.SONIC.h

install: target
	$(AT)mkdir -p $(CUR_DIR)/lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)
	$(AT)cp -f $(TARGET_LIB) $(HI_EXTERN_LIB_DIR)
	$(AT)cp -f $(CUR_DIR)/include/*.h $(HI_INCLUDE_DIR)

uninstall: clean

################################################################################