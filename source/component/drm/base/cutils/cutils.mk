#
# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

commonSources := \
        hashmap.c \
        atomic.c \
        native_handle.c \
        socket_inaddr_any_server_unix.c \
        socket_local_client_unix.c \
        socket_local_server_unix.c \
        socket_loopback_client_unix.c \
        socket_loopback_server_unix.c \
        socket_network_client_unix.c \
        config_utils.c \
        load_file.c \
        strdup16to8.c \
        strdup8to16.c \
        process_name.c \
        properties.c \
        threads.c \
        sched_policy.c \
        ashmem-dev.c \
        memory.c\
        klog.c

include $(CLEAR_VARS)
LOCAL_MODULE := libcutils
LOCAL_SRC_FILES := $(commonSources)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include $(LOCAL_PATH)

LOCAL_CFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                -I$(LOCAL_PATH)/../include/arch -DANDROID_SMP=0

LOCAL_CPPFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                  -I$(LOCAL_PATH)/../include/arch -DANDROID_SMP=0

LOCAL_CFLAGS += ${USER_CFLAGS}
LOCAL_CPPFLAGS += ${USER_CFLAGS}
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcutils
LOCAL_SRC_FILES := $(commonSources)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include $(LOCAL_PATH)

LOCAL_CFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                -I$(LOCAL_PATH)/../include/arch -DANDROID_SMP=0

LOCAL_CPPFLAGS := -include $(LOCAL_PATH)/../include/arch/linux-arm/AndroidConfig.h \
                  -I$(LOCAL_PATH)/../include/arch -DANDROID_SMP=0

LOCAL_CFLAGS += ${USER_CFLAGS}
LOCAL_CPPFLAGS += ${USER_CFLAGS}
include $(BUILD_STATIC_LIBRARY)
