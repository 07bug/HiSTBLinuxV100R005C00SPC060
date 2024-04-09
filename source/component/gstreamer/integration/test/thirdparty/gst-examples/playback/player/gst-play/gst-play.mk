LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := gst-play

ifeq ($(findstring -D__LINUX__, $(CFG_COMMON_MACRO)), -D__LINUX__)
#for linux
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(TOPDIR)/$(CFG_RT_HI_SDK_DIR)
#$(info ### SDK_DIR ###: $(SDK_DIR))
-include $(SDK_DIR)/base.mak
else ifeq ($(CFG_PROJECT_NAME), histb.linux.$(CFG_HI_CHIP_TYPE))
SDK_DIR := $(TOPDIR)/$(CFG_RT_HI_SDK_DIR)
-include $(SDK_DIR)/base.mak
endif
#$(info ### SAMPLE_DIR ###: $(SAMPLE_DIR))
-include $(SAMPLE_DIR)/base.mak

endif

LOCAL_SRC_FILES := gst-play.c \
				   gst-play-kb.c

LOCAL_CFLAGS += $(EXTRA_CFLAGS)


LOCAL_CFLAGS += -Wno-unused-parameter -Wno-unused-function -Wall -Wno-unknown-pragmas \
                  -Wno-write-strings -Wno-address -Wno-write-strings -Wno-shadow        \
                  -Wno-unused-variable -Wno-sign-compare -Wno-unused-but-set-variable   \
                  -Wno-format -Wno-unused-label -Wno-type-limits -Wno-missing-field-initializers \
                  -Wno-strict-prototypes -Wno-missing-prototypes -Wno-empty-body \
                  -Wno-cast-qual

LOCAL_CPPFLAGS += -Wno-unused-parameter -Wno-unused-function -Wall -Wno-unknown-pragmas \
                  -Wno-write-strings -Wno-address -Wno-write-strings -Wno-shadow        \
                  -Wno-unused-variable -Wno-sign-compare -Wno-unused-but-set-variable   \
                  -Wno-format -Wno-unused-label -Wno-type-limits -Wno-missing-field-initializers

LOCAL_CPPFLAGS += $(EXTRA_CXXFLAGS)
LOCAL_LDFLAGS += $(EXTRA_LDFLAGS)

LOCAL_LDLIBS += $(EXTRA_LDLIBS)
LOCAL_LDLIBS += -L$(TOPDIR)/$(RT_THIRDPARTY_OBJ_DIR)/lib \
				-lgstreamer-1.0  -lglib-2.0 -lgobject-2.0 \
				-lgmodule-2.0 -lgio-2.0 -lgstplayer-1.0

LOCAL_SHARED_LIBRARIES :=
LOCAL_REQUIRED_MODULES := pkg_gst_core

ifeq ($(findstring -D__LINUX__, $(CFG_COMMON_MACRO)), -D__LINUX__)
ifneq ($(CFG_PROJECT_NAME), histb.linux.$(CFG_HI_CHIP_TYPE))
HI_SRCS := $(patsubst %.o, %.c, $(COMMON_FILES))
else
HI_SRCS := $(wildcard $(SAMPLE_DIR)/common/*.c)
endif

HI_SRCS := $(patsubst $(TOPDIR)/%, ../../../%, $(HI_SRCS))
#$(info $(HI_SRCS))
HI_SRCS := $(filter-out %/hi_adp_pvr.c, $(HI_SRCS))

ifneq ($(CFG_PROJECT_NAME), histb.linux.$(CFG_HI_CHIP_TYPE))
else
HI_SRCS := $(filter-out %/hi_adp_audio.c, $(HI_SRCS))
endif

#$(info $(HI_SRCS))

LOCAL_SRC_FILES += $(HI_SRCS)

LOCAL_C_INCLUDES += $(SME_THIRDPARTY_MERGE_DIR)/gstreamer-1.10.2 \
					$(THIRDPARTY_OBJ_DIR)/include/gstreamer-1.0 \
					$(THIRDPARTY_OBJ_DIR)/include/gstreamer-1.0/gst \
					$(THIRDPARTY_OBJ_DIR)/include/glib-2.0 \
					$(THIRDPARTY_OBJ_DIR)/include/glib-2.0/glib \
					$(THIRDPARTY_OBJ_DIR)/include/glib-2.0/gio \
					$(THIRDPARTY_OBJ_DIR)/lib/glib-2.0/include \
					$(THIRDPARTY_OBJ_DIR)/include/glib-2.0/glib/gobject


LOCAL_CFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common  $(CFG_HI_SAMPLE_CFLAGS)
LOCAL_CPPFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common  $(CFG_HI_SAMPLE_CFLAGS)
LOCAL_C_INCLUDES += $(foreach h_tmp, $(CFG_RT_PLATFORM_SDK_INC_DIR), $(TOPDIR)/$(h_tmp))
LOCAL_LDFLAGS += -L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)/../extern \
	-L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)/alsa_bluez \
	-Wl,-rpath-link=$(TOPDIR)/$(CFG_RT_LIBHWSECURE_DIR)/out/lib,-rpath-link=$(TARGET_OUT_TO_PREBUILT_DIR)

#$(info COMMON_FILES=$(COMMON_FILES))
#LOCAL_PREBUILT_OBJ_FILES := $(COMMON_FILES)
#$(info HI_LIBS=$(HI_LIBS))
HI_LIBS_MIN=-lhi_common \
	-lharfbuzz \
    -lpng -lhigo -lhigoadp \
    -ljpeg -lhi_msp -lz \
    -lfreetype

LOCAL_LDLIBS += -L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR) $(SYS_LIBS) $(HI_LIBS_MIN)\
	-lOMX.hisi.audio.utils

ifeq ($(CFG_PROJECT_NAME), histb.linux.$(CFG_HI_CHIP_TYPE))
ifeq ($(CFG_HI_64BIT_SYSTEM),y)
LOCAL_LDLIBS += -L$(HI_EXTERN_LIB64_DIR)
else
LOCAL_LDLIBS += -L$(HI_EXTERN_LIB_DIR)
endif
endif

#$(info ##### TARGET_OUTDIR=$(TARGET_OUTDIR))
#$(info ##### ENV_SME_VERSION_TYPE=$(ENV_SME_VERSION_TYPE))
#$(info ##### TARGET_OUT_VERSION_TYPE=$(TARGET_OUT_VERSION_TYPE))

ifneq ($(CFG_PROJECT_NAME), linux_hi3798m_generic)
ifneq ($(CFG_PROJECT_NAME), histb.linux.$(CFG_HI_CHIP_TYPE))
#LOCAL_LDLIBS += -ldirectfb -ldirect -lfusion -llog
endif
endif

endif

include $(BUILD_EXECUTABLE)
