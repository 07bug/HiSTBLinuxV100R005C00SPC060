#===============================================================================
# export variable
#===============================================================================
WAYLAND_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(WAYLAND_DIR)/base.mak

#===============================================================================
# sdk dir
#===============================================================================
include $(SDK_DIR)/base.mak

path_ver := patch/patch-for-weston-3.0.0
#===============================================================================
# compile weston dir
#===============================================================================
WESTON_DIR := $(WL_OUT_DIR)/obj/weston/weston-3.0.0

#===============================================================================
# local variable
#===============================================================================
CFLAGS := $(WL_CFLAGS)

CFLAGS += -I$(WESTON_DIR)                                \
          -I$(WESTON_DIR)/libweston                      \
          -I$(WESTON_DIR)/protocol                       \
          -I$(WESTON_DIR)/shared

CFLAGS += -I$(WL_INSTALL_DIR)/include                    \
          -I$(WL_INSTALL_DIR)/include/pixman-1           \
          -I$(WL_INSTALL_DIR)/include/libweston-3

CFLAGS += -I$(WAYLAND_DIR)/weston/$(path_ver)/libweston

CFLAGS += -I$(HI_INCLUDE_DIR)

DEPEND_LIBS := -lpthread -lrt -lm -ldl -lstdc++ -lhi_msp -lhi_common -ljpeg -lEGL -lGLESv2

LDFLAGS32 := -L$(HI_SHARED_LIB_DIR) $(DEPEND_LIBS)
LDFLAGS64 := -L$(HI_SHARED_LIB64_DIR) $(DEPEND_LIBS)

#===============================================================================
# complie
#===============================================================================
LIB_NAME := pixman-renderer

#===============================================================================
#compile decode lib src
#===============================================================================
CPP_SRCS :=
ASM_SRCS :=

SRCS_DIR := libweston
SRCS := $(SRCS_DIR)/pixman-renderer.c

#===============================================================================
#compile decode lib objects
#===============================================================================
OBJS := $(SRCS:%.c=%.o) $(CPP_SRCS:%.cpp=%.o) $(ASM_SRCS:%.S=%.o)

OBJ_DIR32 := $(WL_OUT_DIR)/obj/weston/patch/pixman-render
OBJ_DIR64 := $(WL_OUT_DIR)/obj64/weston/patch/pixman-render

OBJS32 += $(addprefix $(OBJ_DIR32)/,$(OBJS))
OBJS64 += $(addprefix $(OBJ_DIR64)/,$(OBJS))

TARGETS :=

ifeq ($(HI_USER_SPACE_LIB),y)
TARGETS += $(OBJ_DIR32)/$(LIB_NAME)
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
TARGETS += $(OBJ_DIR64)/$(LIB_NAME)
endif
#===============================================================================
#begin complie
#===============================================================================
.PHONY: all clean

all : $(TARGETS)

clean :
	$(AT)rm -rf $(OBJ_DIR32)
	$(AT)rm -rf $(OBJ_DIR64)

$(OBJ_DIR32)/%.o : $(if $(SRC_DIR),$(SRC_DIR)/%.c,%.c)
	$(AT)test -d $(dir $@) || mkdir -p $(dir $@)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ -c $^

$(OBJ_DIR64)/%.o : $(if $(SRC_DIR),$(SRC_DIR)/%.c,%.c)
	$(AT)test -d $(dir $@) || mkdir -p $(dir $@)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ -c $^

$(OBJ_DIR32)/$(LIB_NAME): $(OBJS32)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -rcs $@.a $(OBJS32)
	$(AT)$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc -shared -o $@.so $(OBJS32) $(LDFLAGS32)

$(OBJ_DIR64)/$(LIB_NAME): $(OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-ar -rcs $@.a $(OBJS64)
	$(AT)$(CFG_HI_AARCH64_TOOLCHAINS_NAME)-gcc -shared -o $@.so $(OBJS64) $(LDFLAGS64)
