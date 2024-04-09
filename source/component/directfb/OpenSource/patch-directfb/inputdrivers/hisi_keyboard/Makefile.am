## Makefile.am for DirectFB/inputdrivers/hisi_keyboard

INCLUDES = \
	-I$(top_builddir)/include	\
	-I$(top_builddir)/lib	\
	-I$(top_srcdir)/include	\
	-I$(top_srcdir)/lib	\
	-I$(top_srcdir)/src	\
	-I$(top_srcdir)/systems

keyboard_LTLIBRARIES = libdirectfb_hisi_keyboard.la

if BUILD_STATIC
keyboard_DATA = $(keyboard_LTLIBRARIES:.la=.o)
endif

keyboarddir = $(MODULEDIR)/inputdrivers

libdirectfb_hisi_keyboard_la_SOURCES =	\
	keyboard.c

libdirectfb_hisi_keyboard_la_LDFLAGS = \
	-module			\
	-avoid-version		\
	$(DFB_LDFLAGS)

libdirectfb_hisi_keyboard_la_LIBADD = \
	$(top_builddir)/lib/direct/libdirect.la \
	$(top_builddir)/src/libdirectfb.la


include $(top_srcdir)/rules/libobject.make

