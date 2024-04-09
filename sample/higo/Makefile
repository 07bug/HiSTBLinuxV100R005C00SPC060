#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_animation \
    sample_bitmapfont   \
    sample_dec          \
    sample_encoder      \
    sample_fillrect     \
    sample_gdev         \
    sample_logo         \
    sample_performance  \
    sample_surface      \
    sample_wm           \
    sample_multi_wm

SAMPLE_IMAGES += sample_effect

ifeq ($(CFG_HIFB_SCROLLTEXT_SUPPORT),y)
SAMPLE_IMAGES += sample_scrolltext
endif

ifeq ($(CFG_HIFB_STEREO3D_SUPPORT),y)
SAMPLE_IMAGES += sample_stereo
endif

SAMPLE_IMAGES += sample_text

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

CFLAGS := -I$(MSP_DIR)/api/higo/include

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_SUPPORT
else
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

DEPEND_LIBS := $(HI_LIBS) -leffect
 
include $(SAMPLE_DIR)/hi_sample_rules.mak
