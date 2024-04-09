#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
endif
ifneq ($(HI_OUT_DIR),)
BUILD_DIR := $(HI_OUT_DIR)/obj/source/rootfs/mii-tool/
else
BUILD_DIR := $(CURDIR)
endif

#===============================================================================
# local variables
#===============================================================================
PROGS := mii-tool
OBJS  := mii-tool.o
OBJS  := $(addprefix $(BUILD_DIR), $(OBJS))
CFLAGS += -I$(COMMON_UNF_INCLUDE)
CFLAGS	+= $(COPTS) -I. -idirafter ./include/


################################################################################
.PHONY: all clean

all: $(BUILD_DIR)$(PROGS)
	echo $(CURDIR)
	test -f $(BUILD_DIR)$(PROGS).c || cp $(CURDIR)/$(PROGS).c $(BUILD_DIR)$(PROGS).c
	test -d $(HI_ROOTFS_DIR)/bin || mkdir -p $(HI_ROOTFS_DIR)/bin
	cp $(BUILD_DIR)$(PROGS) $(HI_ROOTFS_DIR)/bin/
	
	
clean:
	rm -rf $(BUILD_DIR)* $(HI_ROOTFS_DIR)/bin/$(PROGS)

$(BUILD_DIR)$(PROGS): $(OBJS)
	$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ $^ 

$(BUILD_DIR)%.o : %.c
	test -d $(dir $@) || mkdir -p $(dir $@)
	$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ -c $^


################################################################################
