#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#       variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects := freetype
objects += harfbuzz
objects += zlib

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
objects += jpeg
endif

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
objects += png
endif

ifeq ($(CFG_GSTREAMER_SUPPORT),y)
objects += hal
endif

ifeq ($(CFG_HI_HACODEC_SUPPORT),y)
objects += ha_codec
endif

ifeq ($(CFG_HI_SONIC_SUPPORT),y)
objects += ha_sound
endif

ifeq ($(CFG_HI_BLUETOOTH_SUPPORT),y)
objects += bluetooth
endif

ifeq ($(CFG_HI_ALSA_LIB_SUPPORT),y)
objects += alsa
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
objects += advca
endif
endif

ifeq ($(CFG_HI_CURL_SUPPORT),y)
objects += curl
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
objects += subtitle
endif

ifeq ($(CFG_HI_CAPTION_SO_SUPPORT),y)
objects += subtoutput
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
objects += teletext
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
objects += cc
endif

ifeq ($(CFG_HI_WIFI_SUPPORT),y)
objects += wifi
endif

ifeq ($(CFG_HI_NTFS_SUPPORT),y)
objects += ntfs
endif

ifeq ($(CFG_HI_VP_SUPPORT),y)
objects += vp
endif

ifeq ($(CFG_HI_EXFAT_SUPPORT),y)
objects += exfat
endif

ifeq ($(CFG_HI_OPENSSL_SUPPORT),y)
objects += openssl
endif

ifeq ($(CFG_HI_DRM_SUPPORT),y)
    objects += drm

    ifeq ($(CFG_HI_WIDEVINE_SUPPORT),y)
        objects += drm/widevine
    endif

    ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
        objects += drm/playready
    endif

    ifeq ($(CFG_HI_MARLIN_SUPPORT),y)
        objects += drm/marlin
    endif

else ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
    objects += drm
endif

objects_clean := $(addsuffix _clean,$(objects))

depends += $(objects)

ifeq ($(CFG_HI_LOADER_SUPPORT),y)
depends += loader
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
depends += hiplayer
endif

ifeq ($(CFG_GSTREAMER_SUPPORT),y)
depends += gstreamer
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
depends += karaoke
endif

ifeq ($(CFG_HI_AUDIO_RESAMPLER_SUPPORT),y)
depends += resampler
endif

depends_clean := $(addsuffix _clean,$(depends))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean

all: $(depends)

clean: $(depends_clean)

#==================================================================
#                          modules
#==================================================================
.PHONY: $(depends) $(objects_clean)

$(objects):
	$(AT)make -C $@ all

$(objects_clean):
	$(AT)make -C $(patsubst %_clean,%,$@) clean

loader: freetype harfbuzz $(if $(findstring $(CFG_HI_CURL_SUPPORT),y),curl,)
	$(AT)make -C loader all

loader_clean:
	$(AT)make -C loader clean

hiplayer:
	$(AT)test ! -d hiplayer || make -C hiplayer all

hiplayer_clean:
	$(AT)test ! -d hiplayer || make -C hiplayer clean

gstreamer:
	$(AT)test ! -d gstreamer/integration || make -C gstreamer/integration all

gstreamer_clean:
	$(AT)test ! -d gstreamer/integration || make -C gstreamer/integration clean

karaoke: alsa
	$(AT)test -d karaoke && make -C karaoke all

karaoke_clean:
	$(AT)test -d karaoke && make -C karaoke clean

resampler:
	$(AT)test ! -d resampler || make -C resampler all

resampler_clean:
	$(AT)test ! -d resampler || make -C resampler clean
