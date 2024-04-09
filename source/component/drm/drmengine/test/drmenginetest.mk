LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    HTTPSource.cpp \
    HTTPStream.cpp \
    HTTPUtil.cpp \
    DrmEngineTest.cpp

LOCAL_C_INCLUDES := \
    $(FLYFISH_TOP)/framework/drmservice/test \
    $(FLYFISH_TOP)/target/include \
    $(FLYFISH_TOP)/base/include/common \
    $(FLYFISH_TOP)/base/include/arch/linux-arm \
    $(FLYFISH_TOP)/framework/drmservice/drmplugin \
    $(FLYFISH_TOP)/framework/drmservice/include \
    $(FLYFISH_TOP)/framework/drmservice/interface_impl \
    $(FLYFISH_TOP)/framework/drmservice/drm_ipc/client \
    $(FLYFISH_TOP)/framework/drmservice/drmplugin/private \
    $(FLYFISH_TOP)/base/include \
    $(FLYFISH_TOP)/external/openssl/openssl-1.0.2k/include \
    $(FLYFISH_TOP)/framework/drmservice/drm_ipc/server \
    $(FLYFISH_TOP)/component/drmengine \
    $(LOCAL_PATH)/..

LOCAL_LDLIBS = -ldl -lpthread -ldirect -lfusion -lpng -ldirectfb -lsawman

LOCAL_SHARED_LIBRARIES += \
    liblog \
    libdrm \
    libdrm_common \
    libutils \
    libcutils \
    libdrmengine

LOCAL_STATIC_LIBRARIES := libssl libcrypto

LOCAL_MODULE := drmenginetest

# remove USE_SW_DECRYPTION from CLFAGS, when decryption is done in hardware,
# so that we cannot access decrypted stream directly.
LOCAL_CPPFLAGS := -DUSE_SW_DECRYPTION

include $(BUILD_EXECUTABLE)

