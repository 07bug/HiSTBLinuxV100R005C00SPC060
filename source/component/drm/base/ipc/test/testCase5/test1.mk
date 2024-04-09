ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := ipctest1

LOCAL_SRC_FILES += test_client_main.cpp \
                   IMyTestService.cpp \
                   IMyTestClient.cpp \
                   MyTestClient.cpp


LOCAL_C_INCLUDES :=  $(FLYFISH_TOP)/base/include

LOCAL_SHARED_LIBRARIES := libbinder_ipc

LOCAL_LDLIBS := -lrt

include $(BUILD_EXECUTABLE)


########## build server bin ######################
include $(CLEAR_VARS)

LOCAL_MODULE := ipctest1_server

LOCAL_SRC_FILES += service_main.cpp \
                   MyTestService.cpp \
                   IMyTestService.cpp \
                   IMyTestClient.cpp

LOCAL_C_INCLUDES := $(FLYFISH_TOP)/base/include

LOCAL_SHARED_LIBRARIES := libbinder_ipc

LOCAL_LDLIBS := -lrt

include $(BUILD_EXECUTABLE)
endif
