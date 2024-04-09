LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libhwsecurec

CUR_DIR := $(TOPDIR)/platform/libhwsecurec

LOCAL_SRC_FILES := src/secureinput_a.c  \
	src/fscanf_s.c  \
	src/snprintf_s.c  \
	src/wcscat_s.c  \
	src/gets_s.c  \
	src/vsprintf_s.c  \
	src/strcpy_s.c  \
	src/swprintf_s.c  \
	src/memset_s.c  \
	src/strcat_s.c  \
	src/vscanf_s.c  \
	src/wmemmove_s.c  \
	src/sscanf_s.c  \
	src/strncat_s.c  \
	src/wscanf_s.c  \
	src/securecutil.c  \
	src/wmemcpy_s.c  \
	src/secureprintoutput_a.c  \
	src/sprintf_s.c  \
	src/memmove_s.c  \
	src/vsnprintf_s.c  \
	src/wcsncat_s.c  \
	src/wcstok_s.c  \
	src/memcpy_s.c  \
	src/swscanf_s.c  \
	src/wcsncpy_s.c  \
	src/vwscanf_s.c  \
	src/wcscpy_s.c  \
	src/vsscanf_s.c  \
	src/vfscanf_s.c  \
	src/secureinput_w.c  \
	src/vswprintf_s.c  \
	src/strtok_s.c  \
	src/vswscanf_s.c  \
	src/fwscanf_s.c  \
	src/strncpy_s.c  \
	src/scanf_s.c  \
	src/secureprintoutput_w.c  \
	src/vfwscanf_s.c

LOCAL_CFLAGS += $(EXTRA_CFLAGS)
LOCAL_CPPFLAGS += $(EXTRA_CXXFLAGS)

LOCAL_C_INCLUDES := $(foreach h_tmp, $(CFG_RT_PLATFORM_SDK_INC_DIR), $(TOPDIR)/$(h_tmp))

LOCAL_C_INCLUDES += $(CUR_DIR)/include \
        $(CUR_DIR)/src

ifeq ($(CFG_ENABLE_NDK),y)
LOCAL_C_INCLUDES += $(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DIR)/platform/android/bionic/libc/include \
	$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DIR)/platform/android/bionic/libm/include
endif

LOCAL_LDLIBS += $(EXTRA_LDLIBS)
LOCAL_LDLIBS += $(EXTRA_LDFLAGS)

ifneq ($(CFG_ENABLE_NDK), y)
#LOCAL_LDLIBS += -lpthread
else
LOCAL_LDFLAGS += $(foreach h_tmp, $(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR), -L$(TOPDIR)/$(h_tmp))
LOCAL_LDLIBS += -lm
endif

LOCAL_SHARED_LIBRARIES :=

#LOCAL_MODULE_PATH := $(CUR_DIR)/out/lib

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_EXECUTABLE)
