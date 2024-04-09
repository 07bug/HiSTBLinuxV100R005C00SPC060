
LOCAL_PATH := $(my-dir)

#build binder
include $(CLEAR_VARS)

LOCAL_MODULE := libbinder_ipc

LOCAL_SRC_FILES := $(addprefix binder/,$(notdir $(foreach dir, $(LOCAL_PATH)/binder, $(wildcard $(dir)/*.cpp))))

LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include

LOCAL_CFLAGS := -include $(FLYFISH_TOP)/base/include/arch/linux-arm/AndroidConfig.h \
                -I $(FLYFISH_TOP)/base/include/arch  -DBINDER_IPC_32BIT=1

LOCAL_CPPFLAGS := -include $(FLYFISH_TOP)/base/include/arch/linux-arm/AndroidConfig.h \
                  -I $(FLYFISH_TOP)/base/include/arch  -DBINDER_IPC_32BIT=1

LOCAL_SHARED_LIBRARIES := libutils liblog libcutils
include $(BUILD_SHARED_LIBRARY)
