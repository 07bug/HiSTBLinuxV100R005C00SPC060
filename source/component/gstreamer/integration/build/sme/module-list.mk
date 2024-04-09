ifneq ($(findstring y, $(self-rd)_$(demo)_$(ut)), y)
#install ndk
ifeq ($(CFG_ENABLE_NDK), y)
-include $(TOPDIR)/thirdparty/sme/pkg_ndk.mk
endif

############################## begin compile opensource #####################
#glib及其依赖包
include $(TOPDIR)/thirdparty/sme/pkg_iconv.mk
include $(TOPDIR)/thirdparty/sme/pkg_gettext.mk
include $(TOPDIR)/thirdparty/sme/pkg_ffi.mk
include $(TOPDIR)/thirdparty/sme/pkg_glib.mk
include $(TOPDIR)/thirdparty/sme/pkg_glib_all.mk

#gstreamer core
include $(TOPDIR)/thirdparty/sme/pkg_gst_core.mk

#gstreamer base插件包
include $(TOPDIR)/thirdparty/sme/pkg_gst_base.mk

ifeq ($(CFG_ENABLE_GST_PLUGIN_GOOD), y)
include $(TOPDIR)/thirdparty/sme/pkg_xml2.mk
include $(TOPDIR)/thirdparty/sme/pkg_sqlite3.mk
include $(TOPDIR)/thirdparty/sme/pkg_soup.mk
#include $(TOPDIR)/thirdparty/sme/pkg_gst_good_all.mk
include $(TOPDIR)/thirdparty/sme/pkg_gst_good_plugin_only.mk
endif


ifeq ($(CFG_ENABLE_GST_LIBAV), y)
include $(TOPDIR)/thirdparty/sme/pkg_gst_libav_plugin_only.mk
endif

ifeq ($(CFG_ENABLE_GST_VALIDATE), y)
include $(TOPDIR)/thirdparty/sme/pkg_json_glib.mk
include $(TOPDIR)/thirdparty/sme/pkg_gst_validate.mk
endif

ifeq ($(CFG_ENABLE_GST_PLUGIN_BAD), y)
include $(TOPDIR)/thirdparty/sme/pkg_gmp.mk
include $(TOPDIR)/thirdparty/sme/pkg_nettle.mk
ifeq ($(CFG_ENABLE_GST_PLUGIN_GOOD), n)
include $(TOPDIR)/thirdparty/sme/pkg_xml2.mk
endif
include $(TOPDIR)/thirdparty/sme/pkg_gst_bad.mk
include $(TOPDIR)/thirdparty/sme/pkg_gst_bad_all.mk
endif

ifeq ($(CFG_ENABLE_GST_EXAMPLE), y)
include $(TOPDIR)/test/thirdparty/gst-examples/playback/player/gst-play/gst-play.mk
endif

#gst-omx插件包
ifeq ($(CFG_ENABLE_GSTOMX),y)
-include $(TOPDIR)/thirdparty/sme/pkg_gst_omx_plugin_only.mk
endif

#all pkg
include $(TOPDIR)/thirdparty/sme/pkg_opensource_all.mk

ifeq ($(CFG_ENABLE_HWSECURE), y)
-include $(TOPDIR)/platform/libhwsecurec/libhwsecurec.mk
endif

include $(SMEDIR)/source/plugins/pkg_gst_hisi.mk

endif
############################## end compile opensource ########################

############################## begin sme self-RD compile  #########################

ifneq ($(findstring y, $(demo)_$(ut)), y)
#sme-prebuilt
-include $(TOPDIR)/source/sme/prebuilt/sme_prebuilt.mk
endif

############################## end sme self-RD compile #########################
