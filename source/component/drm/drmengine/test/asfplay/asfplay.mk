LOCAL_PATH := $(call my-dir)

playready_dir := $(FLYFISH_TOP)/component/playready/playready30/src/public/

sample_c_include := $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/common/include      \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/common/api/include  \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/common/drv/include  \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/msp/include         \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/msp/api/include     \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/source/msp/drv/include     \
                    $(FLYFISH_TOP)/platform/$(CFG_SDK_TYPE)/sample/common              \
		    $(FLYFISH_TOP)/platform/HiSTBSDKV1R5-A/source/component/ha_codec/include \
		    $(FLYFISH_TOP)/platform/HiSTBSDKV1R5-A/source/component/curl/include \
                    $(playready_dir)/include      \
                    $(FLYFISH_TOP)/target/include/curl \
                    $(FLYFISH_TOP)/base/include

#
# build sample_playready_play
#
include $(CLEAR_VARS)

LOCAL_MODULE := test_playready_play

LOCAL_CC := $(TARGET_CXX)

LOCAL_SRC_FILES := playready_play.c \
                   asf_parser.c


LOCAL_CFLAGS := -Wno-unused-function -Wno-unused-variable -Wno-unused-value \
                -Wno-unused-but-set-variable -Wno-implicit-function-declaration \
                -Wno-enum-compare -Wno-format -Wno-switch -fpermissive

LOCAL_CPPFLAGS := -Wno-unused-function -Wno-unused-variable -Wno-unused-value \
                -Wno-unused-but-set-variable -Wno-implicit-function-declaration \
                -Wno-enum-compare -Wno-format -Wno-switch -fpermissive

#LOCAL_CFLAGS := -fpermissive -Wunused-but-set-variable

LOCAL_C_INCLUDES += $(sample_c_include)

LOCAL_C_INCLUDES += $(FLYFISH_TOP)/framework/drmservice/include

LOCAL_SHARED_LIBRARIES := libutils libcutils liblog \
                          libhi_common libhi_playready

LOCAL_LDLIBS := -lm -lhi_msp -ldirect -lfusion -lpng \
                -ldirectfb -lhigo -lhigoadp \
                -ljpeg -lsawman -lpthread \
                -lhi_common -lhi_sample_common

LOCAL_SHARED_LIBRARIES := libutils libcutils liblog  \
                          libhi_playready libdrm

LOCAL_LDLIBS += -lcurl

include $(BUILD_EXECUTABLE)
