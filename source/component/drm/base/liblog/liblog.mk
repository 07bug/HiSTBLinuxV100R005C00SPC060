LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

liblog_sources := logprint.c \
                  event_tag_map.c \
				  logd_write_kern.c \
				  log_time.cpp

# Shared and static library for target
# ========================================================
include $(CLEAR_VARS)
LOCAL_MODULE := liblog
LOCAL_SRC_FILES := $(liblog_sources)
LOCAL_CFLAGS := -Wall -O2 -g \
                -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                -I$(LOCAL_PATH)/../include/arch/linux-arm \
                -ffunction-sections -fdata-sections -Wl,--gc-sections

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := liblog
LOCAL_SRC_FILES := $(liblog_sources)

LOCAL_CFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                -I$(LOCAL_PATH)/../include/arch/linux-arm  -DHAVE_SYS_UIO_H=1

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

include $(BUILD_SHARED_LIBRARY)
