LOCAL_PATH := $(my-dir)

#########################
ifeq ($(CFG_ENABLE_HWSECURE), p)

include $(CLEAR_VARS)

LOCAL_MODULE := libhwsecurec

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):
	$(NC) cp -af $(TARGET_OUT_TO_PREBUILT_DIR)/libhwsecurec.so $(TARGET_OUT_LIB_DIR)/libhwsecurec.so

$(LOCAL_MODULE)-cfg-clean:$(LOCAL_MODULE)-clean
$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
$(LOCAL_MODULE)-clean:
	$(NC) rm -rf $(TARGET_OUT_LIB_DIR)/libhwsecurec.so


include $(BUILD_OPENSOURCE_PKG)

endif
#########################
ifeq ($(CFG_ENABLE_GSTOMX), p)

include $(CLEAR_VARS)

LOCAL_MODULE := libgstomx

$(LOCAL_MODULE)-deps:$(LOCAL_MODULE)
$(LOCAL_MODULE):
	cp -af $(TARGET_OUT_TO_PREBUILT_PLUGIN_DIR)/gstomx.conf $(TARGET_OUT_CONFIG_DIR)/gstomx.conf
	cp -af $(TARGET_OUT_TO_PREBUILT_PLUGIN_DIR)/libgstomx.so $(TARGET_OUT_PLUGIN_DIR)/libgstomx.so

$(LOCAL_MODULE)-cfg-clean:$(LOCAL_MODULE)-clean
$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
$(LOCAL_MODULE)-clean:
	$(NC) rm -rf $(TARGET_OUT_CONFIG_DIR)/gstomx.conf
	$(NC) rm -rf $(TARGET_OUT_PLUGIN_DIR)/libgstomx.so

include $(BUILD_OPENSOURCE_PKG)

endif
#########################
