#===============================================================================
# export variable
#===============================================================================
AT = 

ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

ifneq ($(HI_OUT_DIR),)
BUILD_DIR := $(HI_OUT_DIR)/obj/source/rootfs/sandbox/
else
BUILD_DIR := $(CURDIR)
endif


#===============================================================================
# local variable
#===============================================================================

SANDBOX := sandbox

OBJS := sandbox.o  \
        userspec.o \
        common.o   \

OBJS := $(addprefix $(BUILD_DIR), $(OBJS))

CFLAGS := -Werror -Wall -D_GNU_SOURCE -O2

LIB = -L$(HI_SHARED_LIB_DIR)

CFLAGS := $(LIB) $(CFLAGS) -I ./include/

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all: $(BUILD_DIR)$(SANDBOX)
	test -d $(HI_ROOTFS_DIR)/bin || mkdir -p $(HI_ROOTFS_DIR)/bin
	cp $(BUILD_DIR)$(SANDBOX) $(HI_ROOTFS_DIR)/bin/

clean:
	rm -rf $(BUILD_DIR)* $(HI_ROOTFS_DIR)/bin/$(SANDBOX)

$(BUILD_DIR)$(SANDBOX): $(OBJS)
	$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ $^ 

$(BUILD_DIR)%.o : %.c
	test -d $(dir $@) || mkdir -p $(dir $@)
	$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc $(CFLAGS) -o $@ -c $^

