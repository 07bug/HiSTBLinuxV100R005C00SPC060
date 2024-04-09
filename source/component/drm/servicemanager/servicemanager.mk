# Copyright 2006 The Android Open Source Project
ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= binder.c \
                  main.cpp

LOCAL_SHARED_LIBRARIES := libbinder_ipc liblog libcutils

LOCAL_MODULE:= service_manager

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../base/include/

LOCAL_LDLIBS += -lpthread

include $(BUILD_EXECUTABLE)
endif  #multi process
