#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../..
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

KLAD_VERSION :=v200

ifneq ($(CFG_HI_MINIBOOT_SUPPORT), y)
CFLAGS  += -DKLAD_CMD_TEST
endif

KLAD_API    := $(PRODUCT_DIR)/driver/klad/api
KLAD_DRV    := $(PRODUCT_DIR)/driver/klad/drv

CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -I$(BOOT_DIR)/include/linux
CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc

CFLAGS += -I$(KLAD_DRV)
CFLAGS += -I$(KLAD_DRV)/include
CFLAGS += -I$(KLAD_DRV)/basic/include
CFLAGS += -I$(KLAD_DRV)/basic/$(KLAD_VERSION)
CFLAGS += -I$(KLAD_DRV)/framework

LIBS    := libklad.a

OBJS    := $(KLAD_API)/unf_klad.o
OBJS    += $(KLAD_DRV)/drv_klad_intf.o
OBJS    += $(KLAD_DRV)/basic/drv_klad_basic.o
OBJS    += $(KLAD_DRV)/basic/$(KLAD_VERSION)/hal_klad.o
OBJS    += $(KLAD_DRV)/basic/$(KLAD_VERSION)/hal_klad_basic.o
OBJS    += $(KLAD_DRV)/framework/drv_klad.o

CFLAGS  += -I$(KLAD_DRV)/common_ca/include
CFLAGS  += -I$(KLAD_DRV)/common_ca/$(KLAD_VERSION)
OBJS    += $(KLAD_API)/common_ca/unf_klad_common_ca.o
OBJS    += $(KLAD_DRV)/common_ca/drv_klad_common_ca.o
OBJS    += $(KLAD_DRV)/common_ca/$(KLAD_VERSION)/hal_klad_common_ca.o

ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
CFLAGS   += -DHI_ADVCA_C1_SUPPORT
#CFLAGS  += -DHI_CAS_OPTIMIZE_REPEAT_SET
CFLAGS   += -I$(KLAD_DRV)/nagra/include
CFLAGS   += -I$(KLAD_DRV)/nagra/cert

OBJS    += $(KLAD_API)/nagra/unf_klad_nagra.o
OBJS    += $(KLAD_API)/nagra/unf_cert.o

OBJS    += $(KLAD_DRV)/nagra/drv_klad_nagra.o
OBJS    += $(KLAD_DRV)/nagra/$(KLAD_VERSION)/hal_klad_nagra.o

OBJS    += $(KLAD_DRV)/nagra/cert/drv_cert.o
OBJS    += $(KLAD_DRV)/nagra/cert/drv_cert_intf.o
OBJS    += $(KLAD_DRV)/nagra/cert/hal_cert.o
ifeq ($(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_nagra.c, $(wildcard $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_nagra.c))
OBJS    += $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_nagra.o
endif
endif

ifeq ($(CFG_HI_ADVCA_TYPE),IRDETO)
CFLAGS   += -DHI_ADVCA_C2_SUPPORT
CFLAGS   += -I$(KLAD_DRV)/irdeto/include

OBJS    += $(KLAD_API)/irdeto/unf_klad_irdeto.o

OBJS    += $(KLAD_DRV)/irdeto/drv_klad_irdeto.o
OBJS    += $(KLAD_DRV)/irdeto/$(KLAD_VERSION)/hal_klad_irdeto.o

ifeq ($(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_irdeto.c, $(wildcard $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_irdeto.c))
OBJS    += $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_irdeto.o
endif
endif

ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
CFLAGS   += -DHI_ADVCA_C3_SUPPORT
CFLAGS   += -I$(KLAD_DRV)/conax/include

OBJS    += $(KLAD_API)/conax/unf_klad_conax.o

OBJS    += $(KLAD_DRV)/conax/drv_klad_conax.o
OBJS    += $(KLAD_DRV)/conax/$(KLAD_VERSION)/hal_klad_conax.o

ifeq ($(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_conax.c, $(wildcard $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_conax.c))
OBJS    += $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_conax.o
endif
endif

OBJS    += $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_basic.o
OBJS    += $(PRODUCT_DIR)/driver/klad/cmd/cmd_klad_common_ca.o

#===============================================================================
# rules
#===============================================================================

.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)

install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
