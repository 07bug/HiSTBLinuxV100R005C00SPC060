plugin_LTLIBRARIES = libsme_gstplg_vsink_hihal.la

libsme_gstplg_vsink_hihal_la_SOURCES = sme_wrap_hisi_hal_vo.c gstsmevideosink_hihal.c gstsmevideosink_hihal_allcator.c gstsmeplugin_hisihal.c
libsme_gstplg_vsink_hihal_la_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CFLAGS) $(LIBPNG_CFLAGS)
libsme_gstplg_vsink_hihal_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) \
        -lhal -lhi_msp -lhi_common -ljpeg \
        -lgstreamer-1.0 \
        -lglib-2.0 -lgobject-2.0 \
        -lgmodule-2.0 -lgio-2.0 \
        -lgstvideo-1.0  \
	$(GST_BASE_LIBS) $(GST_LIBS) $(LIBPNG_LIBS)
libsme_gstplg_vsink_hihal_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libsme_gstplg_vsink_hihal_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

noinst_HEADERS = sme_wrap_hisi_hal_vo.h gstsmevideosink_hihal.h gstsmevideosink_hihal_allcator.h
