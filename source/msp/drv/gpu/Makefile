#===============================================================================
#   export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
        KERNEL_DIR := $(srctree)

        SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
        SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
    version := utgard
else ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
    version := utgard
else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
    version := midgard
else
    $(error error: mali unknown)
endif

ifeq ($(version),utgard)
    ifeq ($(CFG_PRODUCT_TYPE),linux)
        version := utgard/r8p0-01rel0
    else
        ifeq ($(CFG_HI_KERNEL_VERSION),linux-3.18.y)
            version := utgard/r7p0-00rel0
        else ifeq ($(CFG_HI_KERNEL_VERSION),linux-4.4.y)
            version := utgard/r7p0-00rel0
        else ifeq ($(CFG_HI_KERNEL_VERSION),linux-4.9.y)
            version := utgard/r8p0-01rel0
        endif
    endif
endif

obj-y += $(version)/

#=================================================================
#   rules
#=================================================================
.PHONY: all clean

all:
	$(AT)make -C $(version)

clean:
	$(AT)make -C $(version) clean
