LOCAL_PATH := $(my-dir)
################################### libdrm_single compile #########################
include $(CLEAR_VARS)

LOCAL_MODULE := libdrm_single

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
LOCAL_SRC_FILES := drm_ipc/client/IDrm.cpp \
                   drm_ipc/client/DrmClient.cpp \
                   drm_ipc/client/ICrypto.cpp \
                   drm_ipc/client/CryptoClient.cpp \
                   drm_ipc/client/IDrmClient.cpp \
                   drm_ipc/client/IDrmService.cpp

LOCAL_SRC_FILES += drm_ipc/server/SharedLibrary.cpp \
                   drm_ipc/server/DrmSessionManager.cpp \
                   drm_ipc/server/Drm.cpp \
                   drm_ipc/server/Crypto.cpp \
                   drm_ipc/server/DrmService.cpp

LOCAL_SRC_FILES += interface_impl/ModularDrmInterfaceImpl.cpp \
                   interface_impl/CryptoInterfaceImpl.cpp
endif


LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/drm_ipc/client \
                    $(LOCAL_PATH)/drmplugin \
                    $(LOCAL_PATH)/drmplugin/private \
                    $(LOCAL_PATH)/drm_ipc/server

#LOCAL_C_INCLUDES += target/include

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/appmanager/include

LOCAL_SHARED_LIBRARIES := libbinder_ipc liblog libcutils libdrm_common
LOCAL_REQUIRED_MODULES := sdk
include $(BUILD_SHARED_LIBRARY)

################################### libdrm_multi compile #########################
include $(CLEAR_VARS)

LOCAL_MODULE := libdrm

LOCAL_CPPFLAGS := -DMULTI_PROCESS
ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
LOCAL_SRC_FILES := drm_ipc/client/IDrm.cpp \
                   drm_ipc/client/DrmClient.cpp \
                   drm_ipc/client/ICrypto.cpp \
                   drm_ipc/client/CryptoClient.cpp \
                   drm_ipc/client/IDrmClient.cpp \
                   drm_ipc/client/IDrmService.cpp

LOCAL_SRC_FILES += drm_ipc/server/SharedLibrary.cpp \
                   drm_ipc/server/DrmSessionManager.cpp \
                   drm_ipc/server/Drm.cpp \
                   drm_ipc/server/Crypto.cpp \
                   drm_ipc/server/DrmService.cpp

LOCAL_SRC_FILES += interface_impl/ModularDrmInterfaceImpl.cpp \
                   interface_impl/CryptoInterfaceImpl.cpp
endif


LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/drm_ipc/client \
                    $(LOCAL_PATH)/drmplugin \
                    $(LOCAL_PATH)/drmplugin/private \
                    $(LOCAL_PATH)/drm_ipc/server

#LOCAL_C_INCLUDES += target/include

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/appmanager/include

LOCAL_SHARED_LIBRARIES := libbinder_ipc liblog libcutils libdrm_common
ifeq ($(CFG_SDK_TYPE),dpt_sdk_master)
LOCAL_LDLIBS += -lc_sec
endif
LOCAL_REQUIRED_MODULES := sdk
include $(BUILD_SHARED_LIBRARY)

################################### libdrm_common compile #########################
include $(CLEAR_VARS)

LOCAL_MODULE := libdrm_common

LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include \
                    $(LOCAL_PATH)/drmplugin/private

LOCAL_SRC_FILES += drmplugin/private/AString.cpp \
                   drmplugin/private/ABuffer.cpp \
                   drmplugin/private/ALooper.cpp \
                   drmplugin/private/AMessage.cpp \
                   drmplugin/private/AHandler.cpp \
                   drmplugin/private/base64.cpp \
                   drmplugin/private/AAtomizer.cpp \
                   drmplugin/private/hexdump.cpp \
                   drmplugin/private/ALooperRoster.cpp

include $(BUILD_SHARED_LIBRARY)

################################### service_drm compile #########################

# servie_media only build for multiprocess mode

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
include $(CLEAR_VARS)
LOCAL_MODULE := service_drm

LOCAL_SRC_FILES := drmmain/main.cpp

LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include \
                    $(LOCAL_PATH)/drm_ipc/client \
                    $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/drm_ipc/server

LOCAL_C_INCLUDES += $(LOCAL_PATH)/drmplugin \
                    $(LOCAL_PATH)/drmplugin/private

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/target/include

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/appmanager/include \
                    $(FLYFISH_TOP)/framework/resmanager/include

LOCAL_SHARED_LIBRARIES := libAPM libdrm libbinder_ipc libcommon libutils libcutils
LOCAL_LDLIBS := -ldirect -lfusion -lpng -ldirectfb -lhigo -lhigoadp -ljpeg -lsawman
LOCAL_REQUIRED_MODULES := sdk
include $(BUILD_EXECUTABLE)

endif

