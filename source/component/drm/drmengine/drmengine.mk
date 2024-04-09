LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libdrmengine

LOCAL_SRC_FILES := DrmEngine.c

LOCAL_CC := $(TARGET_CXX)

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/base/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/base/include/common
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/base/include/utils
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/target/include

LOCAL_SHARED_LIBRARIES := libdrm liblog  libutils libcutils
#libhi_common libcommon


include $(BUILD_SHARED_LIBRARY)

