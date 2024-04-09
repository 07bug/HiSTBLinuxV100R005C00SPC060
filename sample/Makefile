#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS += -I$(HI_INCLUDE_DIR) -I$(SAMPLE_DIR)/common

objects :=  esplay audiocast tsplay es_ts_switch ipplay mosaic pip log userproc cgms \
            fb tde \
            gpio pmoc ir e2prom i2c register \
            otp flash uart network fs cipher pq test/hdmi_tsplay test/video_test omxvdec rawplay ms12_ipc_mp

ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += capture 3dtv mce ao snapshot deviceinfo
endif

ifeq ($(CFG_HI_KEYPROVISION_SUPPORT),y)
objects += keyprovision
endif

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
objects += jpeg png
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += higo
endif
endif

ifneq ($(CFG_HI_ADVCA_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200),)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += test/ddr_test
endif
endif
endif

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_DIRECTFB_SUPPORT),y)
objects += directfb
endif
endif

ifeq ($(CFG_HI_PWM_SUPPORT),y)
objects += pwm
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
objects += tuner demux dvbplay fullband test/sync_test test/hdmi_dvbplay
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += iframe_dec test/dolby  test/ms12
endif
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += factory_detect
endif
endif

ifeq ($(CFG_HI_PLCIPHER_SUPPORT),y)
objects += plcipher
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv450),)
objects += tee
endif
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += pvr
endif
endif
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
objects += keyled
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
objects += ci
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
objects += hdcpkey
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
objects += aenc
endif

ifeq ($(CFG_HI_AI_SUPPORT),y)
objects += ai
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
objects += karaoke
endif

ifeq ($(CFG_HI_OMX_SUPPORT),y)
objects += omxadec
objects += omxaenc
endif

ifeq ($(CFG_HI_LOADER_SUPPORT),y)
objects += loader
endif

ifeq ($(CFG_HI_WIFI_SUPPORT),y)
objects += wifi
endif

ifeq ($(CFG_HI_GPU_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += gpu
endif
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
objects += sci
endif

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
objects += wdg
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_VENC_SUPPORT),y)
objects += transcode
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += avcast
endif
endif
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
CFLAGS += -I$(MSP_DIR)/drv/include
ifeq ($(CFG_HI_VENC_SUPPORT),y)
ifneq ($(CFG_HI_VO_SINGLE_VIDEO_SUPPORT),y)
objects += vi_venc
ifeq ($(CFG_HI_VP_SUPPORT),y)
objects += vp
endif
endif
endif
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
objects += venc
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += localplay
endif
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += cc
endif
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += teletext
endif
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
ifeq ($(CFG_HI_HIGO_SUPPORT),y)
objects += subtitle
endif
endif

ifeq ($(CFG_HI_OPENSSL_SUPPORT),y)
objects += openssl
endif

ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
    objects += nagra
else ifeq ($(CFG_HI_ADVCA_TYPE), CONAX)
    ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
        objects += advca
    else
        objects += conax
    endif
else ifeq ($(CFG_HI_ADVCA_TYPE), IRDETO)
    ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv200)
        objects += advca
    else
        objects += irdeto
    endif
else ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
    objects += vmx_ultra
else
    ifeq ($(CFG_HI_OTP_KLAD_V100),y)
        objects += advca
    endif
endif

ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    objects += klad
endif

ifeq ($(CFG_HI_DLNA_SUPPORT),y)
objects += hidlna
endif

#ifeq ($(CFG_HI_BLUETOOTH_SUPPORT),y)
#objects += bluetooth
#ifeq ($(CFG_HI_AUDIO_RESAMPLER_SUPPORT),y)
#objects += castbluetooth
#endif
#endif

ifeq ($(CFG_HI_TRANSCODER_SUPPORT),y)
objects += hitranscoder
endif

ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
objects += playready
endif

ifeq ($(CFG_HI_WIDEVINE_SUPPORT),y)
objects += widevine
endif

ifeq ($(CFG_HI_MARLIN_SUPPORT),y)
objects += marlin
endif

ifeq ($(CFG_HI_ADVCA_SANDBOX_TYPE),LXC)
ifneq ($(wildcard lxc_ipc),)
objects += lxc_ipc
endif
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300),)
objects += tee
endif
endif

objects_clean := $(addsuffix _clean, $(objects))

SAMPLE_RES := $(HI_OUT_DIR)/obj/sample
SAMPLE_RES64 := $(HI_OUT_DIR)/obj64/sample

SAMPLE_INSTALL_DIR := $(HI_ROOTBOX_DIR)/usr/local

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv310 hi3796mv200 hi3716mv450 hi3798mv100 hi3796mv100),)
CFG_HI_SAMPLE_INSTALL=y
else
CFG_HI_SAMPLE_INSTALL=n
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
CFG_HI_SAMPLE_INSTALL=n
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean image $(objects) $(objects_clean) prepare sample_common sample_common_clean

all: $(objects)

clean: $(objects_clean)

image: all
ifeq ($(CFG_HI_SAMPLE_INSTALL),y)
ifneq ($(CFG_HI_STATIC_LIB_ONLY),y)
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)mkdir -p $(SAMPLE_INSTALL_DIR)/sample
	$(AT)test -d $(HI_OUT_DIR)/obj/sample && cp -drf $(HI_OUT_DIR)/obj/sample $(SAMPLE_INSTALL_DIR)
	$(AT)rm -rf $(SAMPLE_INSTALL_DIR)/sample/common $(SAMPLE_INSTALL_DIR)/sample/gpu/common $(SAMPLE_INSTALL_DIR)/sample/test/ddr_test/base
	$(AT)rm -rf $(SAMPLE_INSTALL_DIR)/sample/directfb $(SAMPLE_INSTALL_DIR)/sample/openssl $(SAMPLE_INSTALL_DIR)/sample/factory_detect
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)mkdir -p $(SAMPLE_INSTALL_DIR)/sample64
	$(AT)test -d $(HI_OUT_DIR)/obj64/sample && cp -drf $(HI_OUT_DIR)/obj64/sample/* $(SAMPLE_INSTALL_DIR)/sample64
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)rm -rf $(SAMPLE_INSTALL_DIR)/sample64/res
	$(AT)ln -s ../sample/res $(SAMPLE_INSTALL_DIR)/sample64/res
endif
	$(AT)rm -rf $(SAMPLE_INSTALL_DIR)/sample64/common $(SAMPLE_INSTALL_DIR)/sample64/gpu/common $(SAMPLE_INSTALL_DIR)/sample64/test/ddr_test/base
	$(AT)rm -rf $(SAMPLE_INSTALL_DIR)/sample64/directfb $(SAMPLE_INSTALL_DIR)/sample64/openssl $(SAMPLE_INSTALL_DIR)/sample64/factory_detect
endif

	$(AT)find $(SAMPLE_INSTALL_DIR) -name "*.o" | xargs rm -rf
endif
endif
	$(AT)echo "" > /dev/null

$(objects): sample_common
	$(AT)make -C $@

$(objects_clean): sample_common_clean
	$(AT)make -C $(patsubst %_clean, %, $@) clean

sample_common: prepare
	$(AT)make -C common

sample_common_clean:
	$(AT)make -C common clean

prepare:
ifeq ($(HI_USER_SPACE_LIB),y)
	$(AT)test -d $(SAMPLE_RES) || mkdir -p $(SAMPLE_RES)
	$(AT)test -d $(SAMPLE_RES)/res || cp -rf $(SAMPLE_DIR)/res $(SAMPLE_RES)/
endif
ifeq ($(HI_USER_SPACE_LIB64),y)
	$(AT)test -d $(SAMPLE_RES64) || mkdir -p $(SAMPLE_RES64)
	$(AT)test -d $(SAMPLE_RES64)/res || cp -rf $(SAMPLE_DIR)/res $(SAMPLE_RES64)/
endif
