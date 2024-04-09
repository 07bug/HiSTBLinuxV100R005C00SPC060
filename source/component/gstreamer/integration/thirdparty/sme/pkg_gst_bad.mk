LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := pkg_gst_bad

#EXT_TYPE_GZ := tar.gz
EXT_TYPE_XZ := tar.xz
PKG_GST_BAD_NAME := gst-plugins-bad-1.10.4

LOCAL_INTERMEDIATE_TARGETS := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE) \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_prepare \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_configure \
	$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_make \
	$(LOCAL_MODULE)-clean

PRIVATE_PKG_GST_BAD_NAME_PREPARE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_prepare
PRIVATE_PKG_GST_BAD_NAME_CONFIGURE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_configure
PRIVATE_PKG_GST_BAD_NAME_MAKE := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_make
PRIVATE_PKG_GST_BAD_NAME_INSTALL := $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)_install
ifeq ($(ENV_SME_VERSION_TYPE), rls)
$(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE): PRIVATE_PKG_GST_BAD_DBG_FLG := --disable-debug
else
$(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE): PRIVATE_PKG_GST_BAD_DBG_FLG := --enable-debug
endif

PRIVATE_PKG_GST_BAD_DEPS := pkg_gst_base-deps pkg_gnutls

$(LOCAL_MODULE)-deps: $(PRIVATE_PKG_GST_BAD_DEPS) $(LOCAL_MODULE)

$(LOCAL_MODULE): $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE)

$(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/.$(LOCAL_MODULE):$(PRIVATE_PKG_GST_BAD_NAME_INSTALL)

$(PRIVATE_PKG_GST_BAD_NAME_INSTALL):$(PRIVATE_PKG_GST_BAD_NAME_MAKE)
	$(NS)echo "begin INSTALL $(PKG_GST_BAD_NAME)!"
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstadaptivedemux-1.0.so $(TARGET_OUT_LIB_DIR)/libgstadaptivedemux-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstadaptivedemux-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstadaptivedemux-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadaudio-1.0.so $(TARGET_OUT_LIB_DIR)/libgstbadaudio-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadaudio-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstbadaudio-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadbase-1.0.so $(TARGET_OUT_LIB_DIR)/libgstbadbase-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadbase-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstbadbase-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadvideo-1.0.so $(TARGET_OUT_LIB_DIR)/libgstbadvideo-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbadvideo-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstbadvideo-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbasecamerabinsrc-1.0.so $(TARGET_OUT_LIB_DIR)/libgstbasecamerabinsrc-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstbasecamerabinsrc-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstbasecamerabinsrc-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstcodecparsers-1.0.so $(TARGET_OUT_LIB_DIR)/libgstcodecparsers-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstcodecparsers-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstcodecparsers-1.0.so
endif
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstgl-1.0.so $(TARGET_OUT_LIB_DIR)/libgstgl-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstgl-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(NC)$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstgl-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstinsertbin-1.0.so $(TARGET_OUT_LIB_DIR)/libgstinsertbin-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstinsertbin-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstinsertbin-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstmpegts-1.0.so $(TARGET_OUT_LIB_DIR)/libgstmpegts-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstmpegts-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstmpegts-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstphotography-1.0.so $(TARGET_OUT_LIB_DIR)/libgstphotography-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstphotography-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstphotography-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstplayer-1.0.so $(TARGET_OUT_LIB_DIR)/libgstplayer-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgstplayer-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgstplayer-1.0.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgsturidownloader-1.0.so $(TARGET_OUT_LIB_DIR)/libgsturidownloader-1.0.so
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/libgsturidownloader-1.0.so*.0 $(TARGET_OUT_LIB_DIR)/
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_LIB_DIR)/libgsturidownloader-1.0.so
endif
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/gstreamer-1.0/libgstdashdemux.so $(TARGET_OUT_PLUGIN_DIR)/libgstdashdemux.so
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_PLUGIN_DIR)/libgstdashdemux.so
endif
	$(NC)cp -af $(THIRDPARTY_OBJ_DIR)/lib/gstreamer-1.0/libgsthls.so $(TARGET_OUT_PLUGIN_DIR)/libgsthls.so
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_PLUGIN_DIR)/libgsthls.so
endif
	cp -af $(THIRDPARTY_OBJ_DIR)/lib/gstreamer-1.0/libgstmpegtsdemux.so $(TARGET_OUT_PLUGIN_DIR)/libgstmpegtsdemux.so
ifeq ($(STRIP_IN_RELEASE_VERSION), y)
	$(TARGET_STRIP) $(TARGET_OUT_PLUGIN_DIR)/libgstmpegtsdemux.so
endif
	$(NS)echo "end INSTALL $(PKG_GST_BAD_NAME)!"

$(PRIVATE_PKG_GST_BAD_NAME_MAKE):$(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE)
	$(NS)echo "begin make $(PKG_GST_BAD_NAME)!"
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME) $(MAKE_PARALLEL)
	make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME) install $(MAKE_PARALLEL)
	$(NS)echo "end make $(PKG_GST_BAD_NAME)!"


ifeq ($(CFG_ENABLE_NDK), y)
GST_BAD_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(CFG_COMPILE_SYSROOT)/usr/lib -L$(THIRDPARTY_OBJ_DIR)/lib
else
GST_BAD_LDFLAGS:=$(OPENSOURCE_LDFLAGS) -L$(TOPDIR)/$(CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR)
endif

$(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE):$(PRIVATE_PKG_GST_BAD_NAME_PREPARE)
	$(NS)echo "begin configure $(PKG_GST_BAD_NAME)..."
	chmod 777 $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)/configure
	cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME);ac_cv_path_install="/usr/bin/install -cp" ./configure --prefix="${THIRDPARTY_OBJ_DIR}" \
		--host=$(CFG_HOST_TYPE) \
		CFLAGS="$(OPENSOURCE_CFLAGS) --sysroot=$(CFG_COMPILE_SYSROOT)" \
		CXXFLAGS="$(OPENSOURCE_CXXFLAGS)" \
		--disable-static --enable-shared --disable-static-plugins \
		--disable-orc --disable-examples \
		$(PRIVATE_PKG_GST_BAD_DBG_FLG) --disable-benchmarks\
		--disable-accurip --disable-adpcmdec --disable-adpcmenc --disable-aiff -disable-videoframe_audiolevel \
		--disable-asfmux --disable-audiofxbad --disable-audiomixer --disable-compositor --disable-audiovisualizers \
		--disable-autoconvert --disable-bayer --disable-camerabin2 --disable-cdxaparse --disable-coloreffects \
		--disable-dataurisrc --disable-dccp --disable-debugutils --disable-dvbsuboverlay --disable-dvdspu \
		--disable-faceoverlay --disable-festival --disable-fieldanalysis --disable-freeverb --disable-frei0r \
		--disable-gaudieffects --disable-geometrictransform --disable-gdp --disable-hdvparse --disable-id3tag \
		--disable-inter --disable-interlace --disable-ivfparse --disable-ivtc --disable-jp2kdecimator --disable-jpegformat \
		--disable-librfb --disable-midi --disable-mpegdemux --disable-mpegtsmux --disable-mpegpsmux \
		--disable-mve --disable-mxf --disable-netsim --disable-nuvdemux --disable-onvif --disable-patchdetect --disable-pcapparse \
		--disable-pnm --disable-rawparse --disable-removesilence --disable-sdi --disable-sdp --disable-segmentclip --disable-siren \
		--disable-smooth --disable-speed --disable-subenc --disable-stereo --disable-timecode --disable-tta --disable-videofilters \
		--disable-videomeasure --disable-videoparsers --disable-videosignal --disable-vmnc --disable-y4m --disable-yadif --disable-opengl \
		--disable-wgl --disable-glx --disable-cocoa --disable-x11 --disable-wayland --disable-dispmanx \
		--disable-directsound --disable-wasapi --disable-direct3d --disable-winscreencap --disable-winks --disable-android_media \
		--disable-apple_media --disable-bluez --disable-avc --disable-shm --disable-vcd --disable-opensles --disable-uvch264 \
		--disable-nvenc --disable-tinyalsa --disable-assrender --disable-voamrwbenc --disable-voaacenc --disable-apexsink --disable-bs2b \
		--disable-bz2 --disable-chromaprint --disable-curl --disable-dc1394 --disable-decklink --disable-directfb --disable-wayland \
		--disable-webp --disable-daala --disable-dts --disable-resindvd --disable-faac --disable-faad --disable-fbdev --disable-fdk_aac \
		--disable-flite --disable-gsm --disable-fluidsynth --disable-kate --disable-kms --disable-ladspa --disable-lv2 --disable-libde265 \
		--disable-libmms --disable-srtp --disable-dtls --disable-linsys --disable-modplug --disable-mimic --disable-mpeg2enc --disable-mplex \
		--disable-musepack --disable-nas --disable-neon --disable-ofa --disable-openal --disable-opencv --disable-openexr --disable-openh264 \
		--disable-openjpeg --disable-openni2 --disable-opus --disable-pvr --disable-rsvg --disable-gl --disable-gtk3 --disable-qt --disable-vulkan \
		--disable-libvisual --disable-timidity --disable-teletextdec --disable-wildmidi --disable-sdl --disable-sdltest --disable-smoothstreaming \
		--disable-sndfile --disable-soundtouch --disable-spc --disable-gme --disable-xvid --disable-dvb --disable-wininet --disable-acm \
		--disable-vdpau --disable-sbc --disable-schro --disable-zbar --disable-rtmp --disable-spandsp --disable-sndio --disable-x265 --disable-webrtcdsp \
		$(PRIVATE_PKG_HLS_CONFIG_FLG) \
		$(PRIVATE_PKG_DASH_CONFIG_FLG) \
		ZLIB_CFLAGS="$(CFG_ZLIB_CFLAGS)" ZLIB_LIBS="$(CFG_ZLIBS)" \
		LDFLAGS="$(GST_BAD_LDFLAGS) -Wl,-rpath-link=$(THIRDPARTY_OBJ_DIR)/lib" LIBS="-lz" \
		--with-pkg-config-path=$(THIRDPARTY_PKG_CONFIG_DIR) \
		CXX=$(TARGET_CXX) CC=$(TARGET_CC)
	-$(NS)cd $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME);sed -i 's/m4 common docs tests po tools/m4 common/g' `grep 'm4 common docs tests po tools' -rl Makefile`
	$(NS)touch $@
	$(NS)echo "end configure $(PKG_GST_BAD_NAME)..."

$(PRIVATE_PKG_GST_BAD_NAME_PREPARE):
	$(NS)echo "begin prepare $(PKG_GST_BAD_NAME)..."
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)
	$(NC)mkdir -p $(SME_THIRDPARTY_MERGE_DIR)
	tar -xf $(SME_THIRDPARTY_ORG_DIR)/../../../../../../third_party/open_source/$(PKG_GST_BAD_NAME).$(EXT_TYPE_XZ) -C $(SME_THIRDPARTY_MERGE_DIR)
	$(NC)cp -af $(SME_THIRDPARTY_PATCH_DIR)/$(PKG_GST_BAD_NAME) $(SME_THIRDPARTY_MERGE_DIR)/
	$(NS)touch $@
	$(NS)echo "end prepare $(PKG_GST_BAD_NAME)!"

$(LOCAL_MODULE)-clean:
	$(NS)echo "begin make clean $(PKG_GST_BAD_NAME) ..."
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstadaptivedemux-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstbadaudio-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstbadbase-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstbadvideo-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstbasecamerabinsrc-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstcodecparsers-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstgl-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstinsertbin-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstmpegts-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstphotography-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgstplayer-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_LIB_DIR)/libgsturidownloader-1.0.so*
	$(NC)rm -rf $(TARGET_OUT_PLUGIN_DIR)/libgstdashdemux.so
	$(NC)rm -rf $(TARGET_OUT_PLUGIN_DIR)/libgsthls.so
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME) uninstall $(MAKE_PARALLEL)
	$(NC)make -C $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME) clean $(MAKE_PARALLEL)
	$(NS)echo "end make clean $(PKG_GST_BAD_NAME)"

$(LOCAL_MODULE)-cfg-clean:
	$(NS)echo "begin make clean $(PKG_GST_BAD_NAME)-cfg ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE)
	$(NS)echo "end make clean $(PKG_GST_BAD_NAME)-cfg ..."

$(LOCAL_MODULE)-prepare-clean:$(LOCAL_MODULE)-clean
	$(NS)echo "begin make clean $(PKG_GST_BAD_NAME)-prepare ..."
	$(NC)rm -rf $(PRIVATE_PKG_GST_BAD_NAME_CONFIGURE)
	$(NC)rm -rf $(PRIVATE_PKG_GST_BAD_NAME_PREPARE)
	$(NC)rm -rf $(SME_THIRDPARTY_MERGE_DIR)/$(PKG_GST_BAD_NAME)
	$(NS)echo "end make clean $(PKG_GST_BAD_NAME)-prepare ..."

include $(BUILD_OPENSOURCE_PKG)
