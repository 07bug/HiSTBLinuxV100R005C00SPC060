LOCAL_PATH := $(call my-dir)

########################make mediaServcice agent######################
include $(CLEAR_VARS)
LOCAL_MODULE := DrmServiceAgent

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/component/player/include

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/base/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/base/include/common
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/target/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/mediaservice/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/project/cpp/poco/Foundation/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/project/cpp/poco/JSON/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/project/cpp/poco/Net/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/project/cpp/poco/Util/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/drmplugin/private
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/drmplugin
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/include
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/interface_impl
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/drm_ipc/client
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/drm_ipc/server
LOCAL_C_INCLUDES += $(FLYFISH_TOP)/component/playready/playready30/modulardrmplugin

#cp -rf $(LOCAL_PATH)/poco/lib/Linux/x86_64/* $(FLYFISH_TOP)/target/lib/share/

LOCAL_SRC_FILES := DrmServiceAgent.cpp

LOCAL_CC := $(TARGET_CXX)

ifeq ($(CFG_SDK_TYPE),dpt_sdk)
LOCAL_LDLIBS := -lhi_aef_sws -lhi_aef_srs -ldirect -lfusion -lpng -ldirectfb -lhigo -lhigoadp -ljpeg -lsawman -lPocoFoundation -lPocoJSON -lPocoNet -lPocoUtil -lPocoXML
else
LOCAL_LDLIBS := -ldirect -lfusion -lpng -ldirectfb -lhigo -lhigoadp -ljpeg -lsawman -lPocoFoundation -lPocoJSON -lPocoNet -lPocoUtil -lPocoXML
endif

LOCAL_SHARED_LIBRARIES := libcommon liblog libdrm libutils

include $(BUILD_EXECUTABLE)
