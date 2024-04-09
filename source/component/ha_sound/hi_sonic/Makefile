###################### tool chain #######################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif

#****** ����Ŀ��������Ƶ�  ****************************************************
TARGET = libHA.AUDIO.SONIC

#****** ����Ҫ����Ŀ���ļ��Ĵ��λ�� *******************************************
CUR_DIR  = .
OBJ_DIR  = $(CUR_DIR)/lib/obj
LIB_DIR  = $(CUR_DIR)/lib

SND_EXT_PATH = $(CUR_DIR)/external/sonic

################################################################################
#****** ����Դ���뼰ͷ�ļ���λ�� ***********************************************
INC_DIR = $(CUR_DIR)/include

#****** ����ͷ�ļ�������·�� ***************************************************
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
##���߰�ѡ���ʱ�����ڸ߰�Ҫ��SDK api�����뾲̬�⣬����SDK����Makefile�а�-fPICȥ���ˣ���audioģ�����Ҫʹ��-fPIC�������˴���
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
# ����ļ�����·���������ô���2��Դ�ļ��ļ�����ͬ�ĳ�����
vpath %.c $(C_SRCS) $(SND_EXT_PATH)
#vpath %.cpp 
# vpath %.S $(SRC_DIR)/armgcc
################################################################################
# �����������.o�ļ������ŵ�ָ��Ŀ¼
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
# ����Ŀ�꣬ע�⿼�Ƕ��̱߳���
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