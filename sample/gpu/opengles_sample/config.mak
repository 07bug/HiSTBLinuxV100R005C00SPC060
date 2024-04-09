
SDK_DIR := ${PWD}/../../../

include $(SDK_DIR)/base.mak
include $(SAMPLE_DIR)/base.mak

SAMPLE_SRC = $(wildcard *.c)

ifeq ($(CFG_HI_EGL_TYPE), directfb)
EGL_PLATFORM = DIRECTFB
else ifeq ($(CFG_HI_EGL_TYPE), wayland)
EGL_PLATFORM = WAYLAND
else
EGL_PLATFORM = FBDEV
endif

ifeq ($(CFG_HI_GPU_MALI700_SUPPORT), y)
MALI_PLATFORM = MIDGARD
LIB_NAME=mali
else
MALI_PLATFORM = UTGARD
LIB_NAME=Mali
endif

EGL_API_$(EGL_PLATFORM)=1
EGL_API_$(MALI_PLATFORM)=1

COMMON_SRC := ../es20_common/es20_common.c

INC_DIR := -I$(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/include \
           -I$(SDK_DIR)/source/common/api/include -I../es20_common

LIB_DIR := -L$(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/lib/share

MACRO := -DEGL_EGLEXT_PROTOTYPES -DGL_GLEXT_PROTOTYPES \
         -DEGL_API_$(EGL_PLATFORM)=1 -DEGL_API_$(MALI_PLATFORM)=1

LIBS := -l$(LIB_NAME) -lhi_common -lstdc++

ifeq ($(CFG_HI_SMMU_SUPPORT), y)
MACRO += -DHI_SMMU_SUPPORT
endif

CFG_FRAMEBUFFER_DEVICE_OPEN = y

ifeq ($(EGL_API_DIRECTFB), 1)
INC_DIR += -I$(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/obj/source/component/directfb/directfb/usr/include/directfb
LIB_DIR += -L$(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/obj/source/component/directfb/directfb/usr/lib
LIBS += -ldirectfb -ldirect -lfusion -ljpeg -lhi_msp -lpthread
endif

ifeq ($(EGL_API_WAYLAND), 1)
INC_DIR += -I$(SDK_DIR)/source/component/wayland/out/weston/include
LIB_DIR += -L$(SDK_DIR)/source/component/wayland/out/weston/lib
LIBS += -lwayland-client -lwayland-server -lffi -lpthread
endif

ifeq ($(CFG_FRAMEBUFFER_DEVICE_OPEN), y)
ADP_SRC := $(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/obj/sample/common/hi_adp_mpi.o \
           $(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/obj/sample/common/hi_adp_hdmi.o

INC_DIR += -I$(SAMPLE_DIR)/common

MACRO += -DFRAMEBUFFER_DEVICE_OPEN

LIBS += -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

endif
