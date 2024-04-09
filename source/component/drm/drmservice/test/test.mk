LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    HTTPSource.cpp \
    HTTPStream.cpp \
    HTTPUtil.cpp \
    DrmServiceTest.cpp

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
    $(FLYFISH_TOP)/external/openssl/openssl-1.0.2h/include \
    $(FLYFISH_TOP)/framework/drmservice/drm_ipc/server \
    $(LOCAL_PATH)/..

LOCAL_LDLIBS = -ldl -lpthread -lssl -lcrypto

LOCAL_SHARED_LIBRARIES += \
    liblog \
    libdrm \
    libdrm_common \
    libutils \
    libcutils

LOCAL_MODULE := drmservicetest

LOCAL_REQUIRED_MODULES := sdk openssl

# remove USE_SW_DECRYPTION from CLFAGS, when decryption is done in hardware,
# so that we cannot access decrypted stream directly.
LOCAL_CPPFLAGS := -DUSE_SW_DECRYPTION

include $(BUILD_EXECUTABLE)

################################### drmservicetest_st compile #########################
# only for AutoTest
#######################################################################################
include $(CLEAR_VARS)
LOCAL_MODULE := drmservicetest_st

LOCAL_SRC_FILES := \
    st/common_log.cpp \
    st/AutoTest_main.cpp \
    ./HTTPUtil.cpp \
    ./HTTPSource.cpp \
    ./HTTPStream.cpp

LOCAL_C_INCLUDES := \
    $(FLYFISH_TOP)/framework/drmservice/test \
    $(FLYFISH_TOP)/framework/drmservice/test/st \
    $(FLYFISH_TOP)/target/include \
    $(FLYFISH_TOP)/base/include/common \
    $(FLYFISH_TOP)/base/include/arch/linux-arm \
    $(FLYFISH_TOP)/framework/drmservice/drmplugin \
    $(FLYFISH_TOP)/framework/drmservice/include \
    $(FLYFISH_TOP)/framework/drmservice/interface_impl \
    $(FLYFISH_TOP)/framework/drmservice/drm_ipc/client \
    $(FLYFISH_TOP)/framework/drmservice/drmplugin/private \
    $(FLYFISH_TOP)/base/include \
    $(FLYFISH_TOP)/external/openssl/openssl-1.0.2h/include \
    $(FLYFISH_TOP)/framework/drmservice/drm_ipc/server \
    $(LOCAL_PATH)/..

LOCAL_LDLIBS = -lssl -lcrypto -ldl -lpthread

LOCAL_SHARED_LIBRARIES += \
    liblog \
    libdrm \
    libdrm_common \
    libutils \
    libcutils \
    libbinder_ipc

LOCAL_REQUIRED_MODULES := sdk openssl
# remove USE_SW_DECRYPTION from CLFAGS, when decryption is done in hardware,
# so that we cannot access decrypted stream directly.
LOCAL_CPPFLAGS := -DUSE_SW_DECRYPTION
include $(BUILD_EXECUTABLE)