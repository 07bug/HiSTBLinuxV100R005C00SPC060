#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

all: rtk_hciattach

rtk_hciattach: hciattach.c hciattach_rtk.o
	$(CC) -o rtk_hciattach hciattach.c hciattach_rtk.o

hciattach_rtk.o:hciattach_rtk.c
	$(CC) -c hciattach_rtk.c
install:
	cp rtk_hciattach $(HI_ROOTFS_DIR)/usr/bin
clean:
	rm -f *.o  rtk_hciattach tags cscope.*

tags: FORCE
	ctags -R
	find ./ -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.cpp" > cscope.files
	cscope -bkq -i cscope.files
PHONY += FORCE
FORCE:
