plugin_LTLIBRARIES = libsme_gstplg_asink_hihal.la

libsme_gstplg_asink_hihal_la_SOURCES = gsthalaudiosink.c
libsme_gstplg_asink_hihal_la_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_BASE_CFLAGS) $(GST_CFLAGS) $(LIBPNG_CFLAGS)
libsme_gstplg_asink_hihal_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) \
        -lgstaudio-$(GST_API_VERSION) -lhal -lhi_msp -lhi_common -ljpeg \
	$(GST_BASE_LIBS) $(GST_LIBS) $(LIBPNG_LIBS)
libsme_gstplg_asink_hihal_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libsme_gstplg_asink_hihal_la_LIBTOOLFLAGS = $(GST_PLUGIN_LIBTOOLFLAGS)

noinst_HEADERS = gsthalaudiosink.h
