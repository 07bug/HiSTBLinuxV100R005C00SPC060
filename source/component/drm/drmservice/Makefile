#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

LIBDRM_SRC_DIR := drm_ipc
LIBDRM_COMMON_SRC_DIR := drmplugin
SERVICE_DRM_SRC_DIR := drmmain

ifeq ($(CFG_SINGLE_PROCESS_ENABLE), )
	MULTI_PROCESS := y
else
	MULTI_PROCESS := n
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(LIBDRM_COMMON_SRC_DIR) all
	$(AT)make -C $(LIBDRM_SRC_DIR) all
ifeq ($(MULTI_PROCESS),y)
	$(AT)make -C $(SERVICE_DRM_SRC_DIR) all
endif

clean:
	$(AT)make -C $(LIBDRM_COMMON_SRC_DIR) clean
	$(AT)make -C $(LIBDRM_SRC_DIR) clean
ifeq ($(MULTI_PROCESS),y)
	$(AT)make -C $(SERVICE_DRM_SRC_DIR) clean
endif