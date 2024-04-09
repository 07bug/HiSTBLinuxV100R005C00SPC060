################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../../..

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/miniboot/include
else ifeq ($(CFG_HI_UBOOT_SUPPORT),y)
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_UBOOT
CFLAGS += -DHI_LOADER_RUNNING_ENVIRONMENT_BOOT
CFLAGS += -I$(BOOT_DIR)/fastboot/include
else 

endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

SSA_DIR := $(PRODUCT_DIR)/ssa

CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -I$(LOGO_DIR)/include
CFLAGS  += -I$(COMPONENT_DIR)/loader/api/include
CFLAGS  += -I$(COMPONENT_DIR)/loader/api/src/harden/general
CFLAGS  += -I$(COMPONENT_DIR)/loader/api/src/harden/include
CFLAGS  += -I$(COMPONENT_DIR)/loader/api/src
CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS	+= -I$(PRODUCT_DIR)/driver/graphic/include
CFLAGS	+= -I$(PRODUCT_DIR)/ssa/general/L2/include

################################################################################


#===============================================================================
# rules
#===============================================================================
source := $(wildcard *.c adp/*.c)

objs=$(patsubst %.c,%.o, $(source))

LIBS := libssa.a

all:$(LIBS)

$(LIBS):$(objs)
	$(AT)$(AR) -rc -o $(SSA_DIR)/$@ $^

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c $^ -o "$(*D)/$(*F).o"


install: all

uninstall:

clean:
	$(AT)$(RM) *.o -rvf
	$(AT)$(RM) -rf $(objs)
	$(AT)$(RM) -f $(SSA_DIR)/$(LIBS)
