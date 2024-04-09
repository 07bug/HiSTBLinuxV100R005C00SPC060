#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS := -I$(MSP_API_INCLUDE)

SAMPLE_IMAGES := launch_app
SAMPLE_IMAGES += msg_snd_lxc1
SAMPLE_IMAGES += msg_rcv_lxc2
SAMPLE_IMAGES += shm_write_lxc1
SAMPLE_IMAGES += shm_read_lxc2
SAMPLE_IMAGES += sem_lxc1
SAMPLE_IMAGES += sem_lxc2
SAMPLE_IMAGES += ipc_client_test
SAMPLE_IMAGES += ipc_server_test
SAMPLE_IMAGES += socket_server
SAMPLE_IMAGES += socket_client
SAMPLE_IMAGES += socket_server_lxc1
SAMPLE_IMAGES += socket_client_lxc1
SAMPLE_IMAGES += socket_server_lxc2
SAMPLE_IMAGES += socket_client_lxc2

SAMPLE_IMAGES += lxc_capset
SAMPLE_IMAGES += lxc_mount

COMMON_OBJS := $(COMMON_SRCS:%.c=%.o)

DEPEND_LIBS := -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -lcap -L $(HI_ROOTFS_DIR)/usr/lib/ -L $(HI_ROOTFS_DIR)/usr/lib64/ -Wl,--end-group

include $(SAMPLE_DIR)/hi_sample_rules.mak


