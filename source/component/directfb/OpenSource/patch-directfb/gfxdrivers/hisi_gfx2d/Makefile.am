## Makefile.am for DirectFB/src/core/gfxcards/hisi_gfx2d

INCLUDES = \
	-I$(top_builddir)/include  \
	-I$(top_builddir)/lib	   \
	-I$(top_srcdir)/include	   \
	-I$(top_srcdir)/lib	   \
	-I$(top_srcdir)/src	   \
	-I$(top_srcdir)/systems    \
	-I$(top_srcdir)/gfxdrivers

gfx2d_LTLIBRARIES = libdirectfb_hisi_gfx2d.la

if BUILD_STATIC
gfx2d_DATA = $(gfx2d_LTLIBRARIES:.la=.o)
endif

gfx2ddir = $(MODULEDIR)/gfxdrivers

libdirectfb_hisi_gfx2d_la_SOURCES =	\
	tde_2d.c	\
	tde_2d.h	\
	tde_gfxdriver.c	\
	tde_gfxdriver.h \
        tde_driver.c    \
	tde_driver.h    \
	hi_primary.c

libdirectfb_hisi_gfx2d_la_LDFLAGS = \
	-export-dynamic          \
	-avoid-version           \
	$(DFB_LDFLAGS) -lm -ldl

libdirectfb_hisi_gfx2d_la_LIBADD = \
	$(top_builddir)/src/libdirectfb.la

include $(top_srcdir)/rules/libobject.make
