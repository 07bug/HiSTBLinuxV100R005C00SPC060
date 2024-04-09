CFG_HI_SDK_VERSION="HiSTBLinuxV100R005C00SPC060_20180714"

ifeq ($(SDK_CFGFILE),)
SDK_CFGFILE=cfg.mak
endif

include $(SDK_DIR)/$(SDK_CFGFILE)


ifeq ($(VERSION_CFGFLIE),)
VERSION_CFGFILE=version.mak
endif

include $(SDK_DIR)/$(VERSION_CFGFILE)

ifeq ($(CFG_PRODUCT_TYPE),linux)
ifneq ($(HISI_LINUX_ENV),ok)
$(error "Please run 'source ./env.sh' before building!")
endif
endif

#=============SDK_DIR======================================================================

HI_CONFIGS_DIR := $(SDK_DIR)/configs
HI_SCRIPTS_DIR := $(SDK_DIR)/scripts

HI_HAL_DIR := $(SDK_DIR)/source/component/hal

HI_TOOLS_DIR := $(SDK_DIR)/tools/linux/utils

ifneq ($(ANDROID_BUILD),y)
OPEN_SOURCE_DIR=$(SDK_DIR)/third_party/open_source
PLATFORM_DIR=$(SDK_DIR)/platform
HIDOLPHIN_DIR=$(PLATFORM_DIR)/hidolphin
endif

ifneq ($(CFG_HI_OUT_DIR),)
HI_OUT_DIR := $(SDK_DIR)/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)

saved-output := $(HI_OUT_DIR)

$(shell [ -d $(HI_OUT_DIR) ] || mkdir -p $(HI_OUT_DIR))

HI_OUT_DIR := $(shell cd $(HI_OUT_DIR) && /bin/pwd)
$(if $(HI_OUT_DIR),,$(error output directory "$(saved-output)" does not exist))
endif

#=============SRC_DIR======================================================================
SOURCE_DIR      := $(SDK_DIR)/source
COMMON_DIR      := $(SOURCE_DIR)/common
MSP_DIR         := $(SOURCE_DIR)/msp
COMPONENT_DIR   := $(SOURCE_DIR)/component
SAMPLE_DIR      := $(SDK_DIR)/sample
KERNEL_SRC_DIR  := $(SOURCE_DIR)/kernel/$(CFG_HI_KERNEL_VERSION)

ifneq ($(ANDROID_BUILD),y)
PLUGIN_DIR      := $(SOURCE_DIR)/plugin
ROOTFS_SRC_DIR  := $(SOURCE_DIR)/rootfs
BOOT_DIR        := $(SOURCE_DIR)/boot
KERNEL_DIR      := $(SOURCE_DIR)/kernel

ifeq ($(CFG_HI_CPU_ARCH),arm64)
OBJ_NAME := obj64
else
OBJ_NAME := obj
endif

ifeq ($(CFG_HI_USER_SPACE_ALL_LIB),y)
HI_USER_SPACE_LIB := y
HI_USER_SPACE_LIB64 := y
else ifeq ($(CFG_HI_USER_SPACE_LIB64),y)
HI_USER_SPACE_LIB64 := y
else
HI_USER_SPACE_LIB := y
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
ifneq ($(findstring $(CFG_HI_ADVCA_TYPE), NAGRA IRDETO VERIMATRIX_ULTRA),)
HI_ADVANCED_CHIP := y
endif
ifeq ($(CFG_HI_TEE_SUPPORT),y)
HI_SMMZ2_SUPPORT := y
HI_TEE_SMMZ2_SUPPORT := y
endif
endif

ifeq ($(HI_OUT_DIR),)
LINUX_DIR := $(KERNEL_SRC_DIR)
FIP_OUT_DIR := $(KERNEL_DIR)/arm-trusted-firmware
HI_INCLUDE_DIR := $(SDK_DIR)/pub/include
HI_INSTALL_DIR := $(SDK_DIR)/pub
else
LINUX_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(KERNEL_SRC_DIR))
FIP_OUT_DIR := $(HI_OUT_DIR)/$(OBJ_NAME)/$(subst $(SDK_DIR)/,,$(KERNEL_DIR)/arm-trusted-firmware)
HI_INCLUDE_DIR := $(HI_OUT_DIR)/include
HI_INSTALL_DIR := $(HI_OUT_DIR)
HI_ROOTFS_DIR := $(HI_OUT_DIR)/obj/rootfs
endif
endif

#=============INCLUDE_DIR==================================================================
MSP_UNF_INCLUDE         := $(MSP_DIR)/include
MSP_API_INCLUDE         := $(MSP_DIR)/api/include
MSP_DRV_INCLUDE         := $(MSP_DIR)/drv/include
COMMON_UNF_INCLUDE      := $(COMMON_DIR)/include
COMMON_API_INCLUDE      := $(COMMON_DIR)/api/include
COMMON_DRV_INCLUDE      := $(COMMON_DIR)/drv/include

#=============HI_OUT_DIR======================================================================
HI_PREBUILTS_DIR        := $(HI_CONFIGS_DIR)/$(CFG_HI_CHIP_TYPE)/prebuilts
HI_IMAGE_DIR            := $(HI_INSTALL_DIR)/image
HI_SPI_IMAGE_DIR        := $(HI_IMAGE_DIR)/spi_image
HI_NAND_IMAGE_DIR       := $(HI_IMAGE_DIR)/nand_image
HI_EMMC_IMAGE_DIR       := $(HI_IMAGE_DIR)/emmc_image
HI_SPI_EMMC_IMAGE_DIR   := $(HI_IMAGE_DIR)/spi_emmc_image
HI_SPI_NAND_IMAGE_DIR   := $(HI_IMAGE_DIR)/spi_nand_image
HI_MODULE_DIR           := $(HI_INSTALL_DIR)/kmod
HI_ROOTBOX_DIR          := $(HI_INSTALL_DIR)/rootbox

HI_LIB_DIR              := $(HI_INSTALL_DIR)/lib
HI_STATIC_LIB_DIR       := $(HI_LIB_DIR)/static
HI_SHARED_LIB_DIR       := $(HI_LIB_DIR)/share
HI_EXTERN_LIB_DIR       := $(HI_LIB_DIR)/extern

HI_LIB64_DIR            := $(HI_INSTALL_DIR)/lib64
HI_STATIC_LIB64_DIR     := $(HI_LIB64_DIR)/static
HI_SHARED_LIB64_DIR     := $(HI_LIB64_DIR)/share
HI_EXTERN_LIB64_DIR     := $(HI_LIB64_DIR)/extern

#=============TEE_DIR==================================================================
HI_TEE_API_DIR          := $(SDK_DIR)/source/tee/api
HI_TEE_DRV_DIR          := $(SDK_DIR)/source/tee/drv
HI_TEE_TA_DIR           := $(SDK_DIR)/source/tee/ta
HI_TEE_COMPONENT_DIR    := $(SDK_DIR)/source/tee/ta/component

ifeq ($(CFG_HI_OPTEE_SUPPORT), y)
HI_TEE_OS_DIR           := $(SDK_DIR)/source/tee/core/optee
TEE_API_INCLUDE         := $(HI_TEE_OS_DIR)/ca_dev_dir/include
TEE_DRV_INCLUDE         := $(KERNEL_SRC_DIR)/drivers/tee/optee
else
HI_TEE_OS_DIR           := $(SDK_DIR)/source/tee/core/trustedcore
TEE_API_INCLUDE         := $(HI_TEE_OS_DIR)/libteec/inc
TEE_DRV_INCLUDE         := $(KERNEL_SRC_DIR)/drivers/hisilicon/tee/tee_hisi/tzdriver
endif

HI_TA_IMAGE_DIR         := $(HI_INSTALL_DIR)/ta_image

#=============TEE cfg===================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450),)
CFG_HI_TEE_RESERVED_MEM=y
# Reserve TEE memory, 64K gap + 152M TEE memory + 64K gap
CFG_HI_TEE_RESERVED_MEM_ADDR=0x7FF0000
ifeq ($(CFG_HI_OPTEE_SUPPORT), y)
# optee will take extra 4M reserved share memory
CFG_HI_TEE_RESERVED_MEM_SIZE=0x9c20000
else

ifeq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX_ULTRA)
CFG_HI_TEE_RESERVED_MEM_SIZE=0xB020000
else
CFG_HI_TEE_RESERVED_MEM_SIZE=0x9820000
endif

endif
CFG_HI_BL31_SIZE=2097152
endif


ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
CFG_HI_TEE_RESERVED_MEM=y
CFG_HI_TEE_RESERVED_MEM_ADDR=0x7FF0000
CFG_HI_TEE_RESERVED_MEM_SIZE=0x5120000
CFG_HI_BL31_SIZE=2097152
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv300h)
CFG_HI_TEE_RESERVED_MEM=y
CFG_HI_TEE_RESERVED_MEM_ADDR=0x7FF0000
CFG_HI_TEE_RESERVED_MEM_SIZE=0x5120000
CFG_HI_BL31_SIZE=2097152
endif

#=============ATF cfg===================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796mv200 hi3716mv450), )
ifeq ($(CFG_HI_CPU_ARCH), arm64)
CFG_HI_TEE_ATF_SUPPORT=y
endif
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
CFG_HI_TEE_ATF_SUPPORT=y
CFG_HI_ARM32_ATF_SUPPORT=y
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv300h)
CFG_HI_TEE_ATF_SUPPORT=y
CFG_HI_ARM32_ATF_SUPPORT=y
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3798cv200),)
ifeq ($(CFG_HI_TEE_SUPPORT),y)
ifneq ($(CFG_HI_CHIP_TYPE)_$(CFG_HI_ADVCA_TYPE),hi3798mv200_VERIMATRIX_ULTRA)
CFG_HI_ARM32_ATF_SUPPORT=y
CFG_HI_TEE_ATF_SUPPORT=y
CFG_HI_BL31_SIZE=2097152
endif
endif
endif

#=============TOOL CHAINS===================================================================
HI_TOOLCHAINS_DIR := $(SDK_DIR)/tools/linux/toolchains
ifeq ($(CFG_HI_ARM_TOOLCHAINS_NAME),arm-histbv300-linux)
CFG_HI_ARM_TOOLCHAINS_NAME := arm-histbv310-linux
endif
ifeq ($(CFG_HI_64BIT_SYSTEM),y)
HI_KERNEL_TOOLCHAINS_NAME := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)
else
HI_KERNEL_TOOLCHAINS_NAME := $(CFG_HI_ARM_TOOLCHAINS_NAME)
endif

ifneq ($(ANDROID_BUILD),y)
ifeq ($(KERNELRELEASE),)
AR=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ar
AS=$(CFG_HI_ARM_TOOLCHAINS_NAME)-as
LD=$(CFG_HI_ARM_TOOLCHAINS_NAME)-ld
CPP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-cpp
CC=$(CFG_HI_ARM_TOOLCHAINS_NAME)-gcc
NM=$(CFG_HI_ARM_TOOLCHAINS_NAME)-nm
STRIP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-strip
OBJCOPY=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objcopy
OBJDUMP=$(CFG_HI_ARM_TOOLCHAINS_NAME)-objdump
CFG_HI_BASE_ENV+=" AR AS LD CPP CC NM STRIP OBJCOPY OBJDUMP "
endif
endif

#=============SERVER_UNTILS=================================================================
ifneq ($(ANDROID_BUILD),y)
MKIMAGE := mkimage
MKBOOTARGS := mkbootargs
MKBOOTIMG := mkbootimg
MKCRAMFS := mkfs.cramfs
MKEXT4FS := make_ext4fs
MKSQUASHFS := mksquashfs
MKJFFS2 := mkfs.jffs2
MKYAFFS := mkyaffs
MKUBIIMG := mkubiimg.sh
FILECAP := filecap
CFG_HI_BASE_ENV+=" MKIMAGE MKBOOTIMG MKCRAMFS MKSQUASHFS MKJFFS2 FILECAP"
endif

#==============LIB COMPILE OPTIONS================================================================
AT := @

ifeq ($(CFG_HI_ARM_TOOLCHAINS_NAME),arm-histbv320-linux)
FLOAT_OPTIONS := -mfloat-abi=hard -mfpu=vfpv3-d16
else ifeq ($(CFG_HI_ARM_TOOLCHAINS_NAME),arm-histbv310-linux)
FLOAT_OPTIONS := -mfloat-abi=softfp -mfpu=vfpv3-d16
else ifeq ($(CFG_HI_ARM_TOOLCHAINS_NAME),arm-histbv300-linux)
FLOAT_OPTIONS := -mfloat-abi=softfp -mfpu=vfpv3-d16
else
FLOAT_OPTIONS :=
endif

CFG_HI_CFLAGS :=

ifeq ($(CFG_HI_NVR_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_NVR_SUPPORT
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_SMMU_SUPPORT
endif

ifeq ($(CFG_HI_HDR_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_HDR_SUPPORT

ifeq ($(CFG_HI_HDR_DOLBYVISION_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_HDR_DOLBYVISION_SUPPORT
endif
endif

ifneq ($(ANDROID_BUILD),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
CFG_HI_CFLAGS += -mcpu=cortex-a7
else ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3798mv300h hi3798mv310 hi3796mv200 hi3716mv450),)
CFG_HI_CFLAGS += -mcpu=cortex-a53
else
CFG_HI_CFLAGS += -mcpu=cortex-a9
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
    ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
        CFG_HI_CFLAGS += -DNOCS3_0_SUPPORT
    endif
endif

ifndef CFG_HI_ADVCA_FUNCTION
    RULEFILE=$(ROOTFS_SRC_DIR)/scripts/attr_rule/rulelist_noca.txt
else
    ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
        CFG_HI_CFLAGS += -fstack-protector-all
    endif

    CFG_HI_CFLAGS += --param ssp-buffer-size=4
    CFG_HI_CFLAGS += -Wl,-z,relro -g0 -s -Wformat
    CFG_HI_CFLAGS += -Wformat-security -D_FORTIFY_SOURCE=2
    CFG_HI_CFLAGS += -fno-delete-null-pointer-checks -Wformat-y2k

    ifeq ($(CFG_HI_ADVCA_SANDBOX_SUPPORT),y)
        SANDBOX_TYPE := $(shell echo $(CFG_HI_ADVCA_SANDBOX_TYPE) | tr "[A-Z]" "[a-z]")
    endif

    ifeq ($(CFG_HI_LOADER_APPLOADER),y)
        RULEFILE=$(ROOTFS_SRC_DIR)/scripts/attr_rule/rulelist_ca_apploader_$(SANDBOX_TYPE).txt
    else
        ifeq ($(CFG_HI_ADVCA_TYPE),CONAX)
            RULEFILE=$(ROOTFS_SRC_DIR)/scripts/attr_rule/rulelist_ca_system_lxc_advance.txt
        else
            RULEFILE=$(ROOTFS_SRC_DIR)/scripts/attr_rule/rulelist_ca_system_$(SANDBOX_TYPE).txt
        endif
    endif
endif

RULEDBG=0

CFG_HI_CFLAGS += -Werror -Wall -D_GNU_SOURCE -D_XOPEN_SOURCE=600

ifeq ($(CFG_HI_OPTM_SIZE_SUPPORT),y)
CFG_HI_CFLAGS += -Os -ffunction-sections
else
CFG_HI_CFLAGS += -O2
endif

ifndef CFG_HI_STATIC_LIB_ONLY
CFG_HI_CFLAGS += -fPIC
endif

ifeq ($(CFG_HI_MSP_BUILDIN),y)
HI_DRV_BUILDTYPE := y
else
HI_DRV_BUILDTYPE := m
endif
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3798mv300h)
CFG_HI_CHIP_TYPE := hi3798mv310
endif
CFG_HI_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)

CFG_HI_CFLAGS += -DSDK_VERSION=$(CFG_HI_SDK_VERSION) -DFBL_VERSION=$(FBL_VERSION) -DSOS_VERSION=$(SOS_VERSION) -DSOS_MSID=$(SOS_MSID)

## common and other modules will use hi_debug.h, which refers to the HI_LOG_LEVEL
ifeq ($(CFG_HI_LOG_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_LOG_SUPPORT=1

CFG_HI_CFLAGS += -DHI_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)

ifeq ($(CFG_HI_LOG_NETWORK_SUPPORT),y)
CFG_HI_CFLAGS += -DLOG_NETWORK_SUPPORT
endif

ifeq ($(CFG_HI_LOG_UDISK_SUPPORT),y)
CFG_HI_CFLAGS += -DLOG_UDISK_SUPPORT
endif
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_PROC_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
CFG_HI_CFLAGS += -DHI_HDMI_SUPPORT_1_4
else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
CFG_HI_CFLAGS += -DHI_HDMI_SUPPORT_2_0
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_PVR_SUPPORT
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_VI_SUPPORT
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_VENC_SUPPORT
endif

ifeq ($(CFG_HI_PQ_V3_0),y)
CFG_HI_CFLAGS += -DHI_PQ_V3_0
endif

ifeq ($(CFG_HI_PQ_V4_0),y)
CFG_HI_CFLAGS += -DHI_PQ_V4_0
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
    CFG_HI_CFLAGS += -DHI_ADVCA_SUPPORT
    CFG_HI_CFLAGS += -DHI_ADVCA_TYPE_$(CFG_HI_ADVCA_TYPE)

    ifdef CFG_HI_ADVCA_FUNCTION
            CFG_HI_CFLAGS += -DHI_ADVCA_FUNCTION_$(CFG_HI_ADVCA_FUNCTION)
        ifeq ($(CFG_HI_ADVCA_VMX3RD_SUPPORT),y)
            CFG_HI_CFLAGS += -DHI_ADVCA_VMX3RD_SUPPORT
        endif
    endif

    ifeq ($(CFG_HI_ADVCA_VERIFY_ENABLE),y)
        CFG_HI_CFLAGS += -DHI_ADVCA_VERIFY_ENABLE
    endif

    ifeq ($(CFG_HI_ADVCA_USE_EXT1_RSA_KEY),y)
        CFG_HI_CFLAGS += -DHI_ADVCA_USE_EXT1_RSA_KEY
    endif
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFG_HI_CFLAGS += -DHI_TEE_SUPPORT
endif

#=============KERNEL MODULE COMPILE OPTIONS=====================================================
CFG_HI_KMOD_CFLAGS := -Werror

CFG_HI_KMOD_CFLAGS += -DCHIP_TYPE_$(CFG_HI_CHIP_TYPE)

CFG_HI_KMOD_CFLAGS += -DSDK_VERSION=$(CFG_HI_SDK_VERSION)

ifdef CFG_HI_ADVCA_FUNCTION
    CFG_HI_KMOD_CFLAGS += -Wformat --param ssp-buffer-size=4
    CFG_HI_KMOD_CFLAGS += -Wformat-security -g0 -s
    CFG_HI_KMOD_CFLAGS += -Wl,-z,relro -Wformat-y2k
    CFG_HI_KMOD_CFLAGS += -D_FORTIFY_SOURCE=2
    CFG_HI_KMOD_CFLAGS += -fno-delete-null-pointer-checks
endif

ifeq ($(CFG_HI_NVR_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_NVR_SUPPORT
endif

ifeq ($(findstring fpga, $(CFG_HI_BOOT_REG_NAME)), fpga)
CFG_HI_KMOD_CFLAGS += -DHI_FPGA_SUPPORT
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_SMMU_SUPPORT
endif

ifeq ($(CFG_HI_HDR_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_HDR_SUPPORT

ifeq ($(CFG_HI_HDR_DOLBYVISION_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_HDR_DOLBYVISION_SUPPORT
endif
endif

ifeq ($(CFG_HI_KEYLED_CT1642_KERNEL_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_KEYLED_CT1642_KERNEL_SUPPORT
endif

ifeq ($(CFG_HI_MCE_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_MCE_SUPPORT
endif

ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_GPIOI2C_SUPPORT
endif

## common and other modules will use hi_debug.h, which refers to the HI_LOG_LEVEL
ifeq ($(CFG_HI_LOG_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_LOG_SUPPORT=1

CFG_HI_KMOD_CFLAGS += -DHI_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_PROC_SUPPORT
endif

ifeq ($(CFG_HI_DEMUX_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_DEMUX_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
CFG_HI_KMOD_CFLAGS += -DHI_HDMI_SUPPORT_1_4
else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
CFG_HI_KMOD_CFLAGS += -DHI_HDMI_SUPPORT_2_0
endif

ifeq ($(CFG_HI_GFX2D_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_GFX2D_SUPPORT
endif

ifeq ($(CFG_HI_LOADER_APPLOADER),y)
CFG_HI_KMOD_CFLAGS += -DHI_LOADER_APPLOADER
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_KEYLED_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
CFG_HI_KMOD_CFLAGS += -DHI_HDCP_SUPPORT
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_SCI_SUPPORT
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_PVR_SUPPORT
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_VI_SUPPORT
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_VENC_SUPPORT
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_AENC_SUPPORT
endif

ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_ADAC_SLIC_SUPPORT
endif

ifeq ($(CFG_HI_PQ_V3_0),y)
CFG_HI_KMOD_CFLAGS += -DHI_PQ_V3_0
endif

ifeq ($(CFG_HI_PQ_V4_0),y)
CFG_HI_KMOD_CFLAGS += -DHI_PQ_V4_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
    ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
        CFG_HI_KMOD_CFLAGS += -DNOCS3_0_SUPPORT
    endif
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
    CFG_HI_KMOD_CFLAGS += -DHI_ADVCA_SUPPORT
    CFG_HI_KMOD_CFLAGS += -DHI_ADVCA_TYPE_$(CFG_HI_ADVCA_TYPE)

    ifdef CFG_HI_ADVCA_FUNCTION
            CFG_HI_KMOD_CFLAGS += -DHI_ADVCA_FUNCTION_$(CFG_HI_ADVCA_FUNCTION)
        ifeq ($(CFG_HI_ADVCA_VMX3RD_SUPPORT),y)
            CFG_HI_KMOD_CFLAGS += -DHI_ADVCA_VMX3RD_SUPPORT
        endif
    endif

endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFG_HI_KMOD_CFLAGS += -DHI_TEE_SUPPORT
endif

#=============BOARD CONFIGURATION OPTIONS=====================================================
CFG_HI_BOARD_CONFIGS :=

ifneq ($(CFG_HI_DAC_CVBS),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_CVBS=$(CFG_HI_DAC_CVBS)
endif

ifneq ($(CFG_HI_DAC_YPBPR_Y),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_YPBPR_Y=$(CFG_HI_DAC_YPBPR_Y)
endif

ifneq ($(CFG_HI_DAC_YPBPR_PB),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_YPBPR_PB=$(CFG_HI_DAC_YPBPR_PB)
endif

ifneq ($(CFG_HI_DAC_YPBPR_PR),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_YPBPR_PR=$(CFG_HI_DAC_YPBPR_PR)
endif

ifneq ($(CFG_HI_DAC_VGA_R),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_VGA_R=$(CFG_HI_DAC_VGA_R)
endif

ifneq ($(CFG_HI_DAC_VGA_G),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_VGA_G=$(CFG_HI_DAC_VGA_G)
endif

ifneq ($(CFG_HI_DAC_VGA_B),)
CFG_HI_BOARD_CONFIGS += -DHI_DAC_VGA_B=$(CFG_HI_DAC_VGA_B)
endif

ifneq ($(CFG_HI_SND_MUTECTL_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_SND_MUTECTL_GPIO=$(CFG_HI_DAC_SVIDEO_C)
else
CFG_HI_BOARD_CONFIGS += -DHI_SND_MUTECTL_GPIO=0x39
endif

#=============SCI CONFIGURATION OPTIONS===================
ifeq ($(CFG_HI_SCI_CLK_MODE_CMOS),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_CLK_MODE=0
endif
ifeq ($(CFG_HI_SCI_CLK_MODE_OD),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_CLK_MODE=1
endif

ifeq ($(CFG_HI_SCI_VCCEN_MODE_CMOS),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_VCCEN_MODE=0
endif
ifeq ($(CFG_HI_SCI_VCCEN_MODE_OD),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_VCCEN_MODE=1
endif

ifeq ($(CFG_HI_SCI_RESET_MODE_CMOS),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_RESET_MODE=0
endif
ifeq ($(CFG_HI_SCI_RESET_MODE_OD),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_RESET_MODE=1
endif

ifeq ($(CFG_HI_SCI_VCCEN_LOW),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_VCCEN_LEVEL=0
endif
ifeq ($(CFG_HI_SCI_VCCEN_HIGH),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_VCCEN_LEVEL=1
endif

ifeq ($(CFG_HI_SCI_DETECT_LOW),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_DETECT_LEVEL=0
endif
ifeq ($(CFG_HI_SCI_DETECT_HIGH),y)
CFG_HI_BOARD_CONFIGS += -DHI_SCI_DETECT_LEVEL=1
endif


#===============================================DEMUX  PORT  CONFIG==========================================
CFG_HI_BOARD_CONFIGS += -DHI_TSI_port_NUMBER=$(CFG_HI_TSI_NUMBER)
CFG_HI_BOARD_CONFIGS += -DHI_TSO_PORT_NUMBER=$(CFG_HI_TSO_NUMBER)

#=============DEMUX  IF0 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_IF_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=0
endif
ifeq ($(CFG_HI_IF_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=1
endif
ifeq ($(CFG_HI_IF_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=2
endif
ifeq ($(CFG_HI_IF_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=3
endif
ifeq ($(CFG_HI_IF_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=4
endif
ifeq ($(CFG_HI_IF_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=5
endif
ifeq ($(CFG_HI_IF_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=7
endif
ifeq ($(CFG_HI_IF_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=8
endif
ifeq ($(CFG_HI_IF_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_TYPE=9
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_IF_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_IF_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_IF0_BIT_SELECTOR=1
endif

#=============DEMUX  TSI0 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI0_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=0
endif
ifeq ($(CFG_HI_TSI0_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=1
endif
ifeq ($(CFG_HI_TSI0_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=2
endif
ifeq ($(CFG_HI_TSI0_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=3
endif
ifeq ($(CFG_HI_TSI0_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=4
endif
ifeq ($(CFG_HI_TSI0_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=5
endif
ifeq ($(CFG_HI_TSI0_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=7
endif
ifeq ($(CFG_HI_TSI0_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=8
endif
ifeq ($(CFG_HI_TSI0_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_TYPE=9
endif
#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI0_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI0_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI0_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI0_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI0_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI0_SERIAL_SHARE_CLK=0x25
endif

#=============DEMUX  TSI10 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI1_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=0
endif
ifeq ($(CFG_HI_TSI1_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=1
endif
ifeq ($(CFG_HI_TSI1_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=2
endif
ifeq ($(CFG_HI_TSI1_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=3
endif
ifeq ($(CFG_HI_TSI1_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=4
endif
ifeq ($(CFG_HI_TSI1_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=5
endif
ifeq ($(CFG_HI_TSI1_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=7
endif
ifeq ($(CFG_HI_TSI1_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=8
endif
ifeq ($(CFG_HI_TSI1_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_TYPE=9
endif
#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI1_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI1_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI1_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI1_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI1_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI1_SERIAL_SHARE_CLK=0x25
endif
#=============DEMUX  TSI2 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI2_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=0
endif
ifeq ($(CFG_HI_TSI2_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=1
endif
ifeq ($(CFG_HI_TSI2_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=2
endif
ifeq ($(CFG_HI_TSI2_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=3
endif
ifeq ($(CFG_HI_TSI2_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=4
endif
ifeq ($(CFG_HI_TSI2_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=5
endif
ifeq ($(CFG_HI_TSI2_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=7
endif
ifeq ($(CFG_HI_TSI2_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=8
endif
ifeq ($(CFG_HI_TSI2_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_TYPE=9
endif
#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI2_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI2_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI2_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI2_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI2_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI2_SERIAL_SHARE_CLK=0x25
endif

#=============DEMUX  TSI3 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI3_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=0
endif
ifeq ($(CFG_HI_TSI3_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=1
endif
ifeq ($(CFG_HI_TSI3_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=2
endif
ifeq ($(CFG_HI_TSI3_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=3
endif
ifeq ($(CFG_HI_TSI3_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=4
endif
ifeq ($(CFG_HI_TSI3_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=5
endif
ifeq ($(CFG_HI_TSI3_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=7
endif
ifeq ($(CFG_HI_TSI3_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=8
endif
ifeq ($(CFG_HI_TSI3_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_TYPE=9
endif
#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI3_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI3_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI3_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI3_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI3_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI3_SERIAL_SHARE_CLK=0x25
endif

#=============DEMUX  TSI4 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI4_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=0
endif
ifeq ($(CFG_HI_TSI4_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=1
endif
ifeq ($(CFG_HI_TSI4_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=2
endif
ifeq ($(CFG_HI_TSI4_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=3
endif
ifeq ($(CFG_HI_TSI4_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=4
endif
ifeq ($(CFG_HI_TSI4_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=5
endif
ifeq ($(CFG_HI_TSI4_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=7
endif
ifeq ($(CFG_HI_TSI4_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=8
endif
ifeq ($(CFG_HI_TSI4_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_TYPE=9
endif
#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI4_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI4_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI4_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI4_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI4_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI4_SERIAL_SHARE_CLK=0x25
endif

#=============DEMUX  TSI5 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI5_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=0
endif
ifeq ($(CFG_HI_TSI5_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=1
endif
ifeq ($(CFG_HI_TSI5_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=2
endif
ifeq ($(CFG_HI_TSI5_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=3
endif
ifeq ($(CFG_HI_TSI5_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=4
endif
ifeq ($(CFG_HI_TSI5_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=5
endif
ifeq ($(CFG_HI_TSI5_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=7
endif
ifeq ($(CFG_HI_TSI5_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=8
endif
ifeq ($(CFG_HI_TSI5_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_TYPE=9
endif

#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI5_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI5_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI5_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI5_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI5_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI5_SERIAL_SHARE_CLK=0x25
endif


#=============DEMUX  TSI6 PORT  CONFIG===================
#--------------Port type-------------------
ifeq ($(CFG_HI_TSI6_TYPE),parallel_burst)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=0
endif
ifeq ($(CFG_HI_TSI6_TYPE),parallel_valid)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=1
endif
ifeq ($(CFG_HI_TSI6_TYPE),parallel_nosync_188)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=2
endif
ifeq ($(CFG_HI_TSI6_TYPE),parallel_nosync_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=3
endif
ifeq ($(CFG_HI_TSI6_TYPE),parallel_nosync_188_204)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=4
endif
ifeq ($(CFG_HI_TSI6_TYPE),serial)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=5
endif
ifeq ($(CFG_HI_TSI6_TYPE),serial2bit)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=7
endif
ifeq ($(CFG_HI_TSI6_TYPE),serial_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=8
endif
ifeq ($(CFG_HI_TSI6_TYPE),serial2bit_nosync)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_TYPE=9
endif

#--------------CLK Phase-------------------
ifeq ($(CFG_HI_TSI6_CLK_PHASE_REVERSE),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_CLK_PHASE_REVERSE=0
endif
ifeq ($(CFG_HI_TSI6_CLK_PHASE_REVERSE),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_CLK_PHASE_REVERSE=1
endif
#-------------Bit Selector-------------------
ifeq ($(CFG_HI_TSI6_BIT_SELECTOR),0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSI6_BIT_SELECTOR),1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_BIT_SELECTOR=1
endif
#-------------Clock Use-------------------
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi0)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x20
endif
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi1)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x21
endif
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi2)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x22
endif
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi3)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x23
endif
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi4)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x24
endif
ifeq ($(CFG_HI_TSI6_SERIAL_SHARE_CLK),tsi5)
CFG_HI_BOARD_CONFIGS += -DHI_TSI6_SERIAL_SHARE_CLK=0x25
endif

#=============DEMUX  TSO0 PORT  CONFIG===================
#--------------clk frequency-------------------
ifeq ($(CFG_HI_TSO0_CLK_100M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK=0
endif
ifeq ($(CFG_HI_TSO0_CLK_150M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK=1
endif
ifeq ($(CFG_HI_TSO0_CLK_1200M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK=3
endif
ifeq ($(CFG_HI_TSO0_CLK_1500M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK=4
endif
#--------------clk mode-------------------
ifeq ($(CFG_HI_TSO0_CLK_MODE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK_MODE=0
endif
ifeq ($(HI_TSO0_CLK_MODE_JITTER),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_CLK_MODE=1
endif
#----------------------valid------------------
ifeq ($(CFG_HI_TSO0_VALID_ACTIVE_OUTPUT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_VALID_MODE=0
endif
ifeq ($(HI_TSO0_VALID_ACTIVE_HIGH),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_VALID_MODE=1
endif
#-----------serial or parallel------------------
ifeq ($(CFG_HI_TSO0_PARALLEL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_SERIAL=0
endif
ifeq ($(CFG_HI_TSO0_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_SERIAL=1
endif
#----------------------bit selector--------------
ifeq ($(CFG_HI_TSO0_SERIAL_BIT_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSO0_SERIAL_BIT_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO0_BIT_SELECTOR=7
endif

#=============DEMUX  TSO1 PORT  CONFIG===================
#--------------clk frequency-------------------
ifeq ($(CFG_HI_TSO1_CLK_100M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK=0
endif
ifeq ($(CFG_HI_TSO1_CLK_150M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK=1
endif
ifeq ($(CFG_HI_TSO1_CLK_1200M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK=3
endif
ifeq ($(CFG_HI_TSO1_CLK_1500M),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK=4
endif
#--------------clk mode-------------------
ifeq ($(CFG_HI_TSO1_CLK_MODE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK_MODE=0
endif
ifeq ($(CFG_HI_TSO1_CLK_MODE_JITTER),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_CLK_MODE=1
endif
#----------------------valid------------------
ifeq ($(CFG_HI_TSO1_VALID_ACTIVE_OUTPUT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_VALID_MODE=0
endif
ifeq ($(CFG_HI_TSO1_VALID_ACTIVE_HIGH),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_VALID_MODE=1
endif
#-----------serial or parallel------------------
ifeq ($(CFG_HI_TSO1_PARALLEL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_SERIAL=0
endif
ifeq ($(CFG_HI_TSO1_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_SERIAL=1
endif
#----------------------bit selector--------------
ifeq ($(CFG_HI_TSO1_SERIAL_BIT_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_BIT_SELECTOR=0
endif
ifeq ($(CFG_HI_TSO1_SERIAL_BIT_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TSO1_BIT_SELECTOR=7
endif


#=============TUNER BASIC ATTRIBUTE OPTIONS===================
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_NUMBER=$(CFG_HI_TUNER_NUMBER)

#=============TUNER 0 BASIC ATTRIBUTE OPTIONS=======

CFG_HI_BOARD_CONFIGS += -DHI_TUNER0_ID=0

ifeq ($(CFG_HI_TUNER_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=4
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=8
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=9
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=10
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=13
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=17
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=19
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=20
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=21
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=22
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=23
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=24
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=25
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=26
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=27
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=28
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=29
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=30
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=32
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=33
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=34
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=35
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=36
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=37
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=38
endif
ifeq ($(CFG_HI_TUNER_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TYPE=39
endif

ifneq ($(CFG_HI_TUNER_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_DEV_ADDR=$(CFG_HI_TUNER_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_DEV_ADDR=$(CFG_HI_DEMOD_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_USE_I2C -DHI_DEMOD_I2C_CHANNEL=$(CFG_HI_DEMOD_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_GPIO_SDA=$(CFG_HI_DEMOD_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_GPIO_SCL=$(CFG_HI_DEMOD_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_RESET_GPIO=$(CFG_HI_DEMOD_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX_PORT=$(CFG_HI_DEMUX_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX_PORT=0
endif

#=============TUNER0 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_REF_CLOCK=$(CFG_HI_DEMOD_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_MAX_LPF=$(CFG_HI_TUNER_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_I2C_CLOCK=$(CFG_HI_TUNER_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_ADDR=$(CFG_HI_LNBCTRL_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL_DEV_ADDR=0x0
endif

#=============TUNER0 Terrestrial ATTRIBUTE OPTIONS===================
ifneq ($(CFG_TER_HI_DEMOD_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD_REF_CLOCK=$(CFG_HI_TER_DEMOD_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TER_TUNER_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_MAX_LPF=$(CFG_HI_TER_TUNER_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_MAX_LPF=34
endif

ifneq ($(CFG_HI_TER_TUNER_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_I2C_CLOCK=$(CFG_HI_TER_TUNER_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TER_TUNER_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_RFAGC=0
endif
ifeq ($(CFG_HI_TER_TUNER_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_RFAGC=1
endif

ifeq ($(CFG_HI_TER_TUNER_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TER_TUNER_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TER_TUNER_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TER_TUNER_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TER_TUNER_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TER_TUNER_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TER_TUNER_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TER_TUNER_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TER_TUNER_TS_SYNC_HEAD_AUTO),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_SYNC_HEAD=0
endif
ifeq ($(CFG_HI_TER_TUNER_TS_SYNC_HEAD_8BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER_TS_SYNC_HEAD=1
endif

#=============TUNER Cable ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD_CAB_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_DEMOD_REF_CLOCK=$(CFG_HI_DEMOD_CAB_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_CAB_DEMOD_REF_CLOCK=24000
endif

ifeq ($(CFG_HI_TUNER_CAB_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_TUNER_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER_CAB_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_TUNER_TS_SERIAL_PIN=1
endif

#=============TUNER0 TSOUT OPTIONS===================
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN0_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN0=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN1_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN1=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN2_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN2=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN3_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN3=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN4_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN4=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN5_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN5=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN6_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN6=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN7_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN7=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN8_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN8=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN9_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN9=10
endif

ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=0
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=1
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=2
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=3
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=4
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=5
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=6
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=7
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=8
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=9
endif
ifeq ($(CFG_HI_TUNER_OUTPUT_PIN10_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER_OUTPUT_PIN10=10
endif

#=============TUNER 1 BASIC ATTRIBUTE OPTIONS=======

CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_ID=1

ifeq ($(CFG_HI_TUNER1_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER1_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER1_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=4
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=8
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=9
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=10
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=13
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=17
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=19
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=20
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=21
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=22
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=23
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=24
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=25
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=26
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=27
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=28
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=29
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=30
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=32
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=34
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=35
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=36
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=37
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=38
endif
ifeq ($(CFG_HI_TUNER1_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TYPE=39
endif

ifneq ($(CFG_HI_TUNER1_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_DEV_ADDR=$(CFG_HI_TUNER1_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD1_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD1_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_DEV_ADDR=$(CFG_HI_DEMOD1_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD1_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD1_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD1_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD1_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD1_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD1_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD1_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_USE_I2C -DHI_DEMOD1_I2C_CHANNEL=$(CFG_HI_DEMOD1_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD1_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_GPIO_SDA=$(CFG_HI_DEMOD1_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_GPIO_SCL=$(CFG_HI_DEMOD1_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD1_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_RESET_GPIO=$(CFG_HI_DEMOD1_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX1_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX1_PORT=$(CFG_HI_DEMUX1_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX1_PORT=0
endif

#=============TUNER1 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD1_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_REF_CLOCK=$(CFG_HI_DEMOD1_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD1_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER1_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_MAX_LPF=$(CFG_HI_TUNER1_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER1_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_I2C_CLOCK=$(CFG_HI_TUNER1_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER1_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER1_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER1_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER1_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER1_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER1_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER1_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER1_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER1_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER1_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER1_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER1_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL1_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL1_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL1_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL1_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL1_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL1_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_ADDR=$(CFG_HI_LNBCTRL1_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL1_DEV_ADDR=0x0
endif

#=============TUNER1 Terrestrial ATTRIBUTE OPTIONS===================
ifneq ($(CFG_TER_HI_DEMOD1_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD1_REF_CLOCK=$(CFG_HI_TER_DEMOD1_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD1_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TER_TUNER1_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_MAX_LPF=$(CFG_HI_TER_TUNER1_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_MAX_LPF=34
endif

ifneq ($(CFG_HI_TER_TUNER1_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_I2C_CLOCK=$(CFG_HI_TER_TUNER1_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TER_TUNER1_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_RFAGC=0
endif
ifeq ($(CFG_HI_TER_TUNER1_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_RFAGC=1
endif

ifeq ($(CFG_HI_TER_TUNER1_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TER_TUNER1_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TER_TUNER1_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TER_TUNER1_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TER_TUNER1_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TER_TUNER1_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TER_TUNER1_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TER_TUNER1_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TER_TUNER1_TS_SYNC_HEAD_AUTO),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_SYNC_HEAD=0
endif
ifeq ($(CFG_HI_TER_TUNER1_TS_SYNC_HEAD_8BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER1_TS_SYNC_HEAD=1
endif
#=============TUNER1 Cable ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD1_CAB_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_DEMOD1_REF_CLOCK=$(CFG_HI_DEMOD1_CAB_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_CAB_DEMOD1_REF_CLOCK=24000
endif

ifeq ($(CFG_HI_TUNER1_CAB_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_TUNER1_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER1_CAB_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_CAB_TUNER1_TS_SERIAL_PIN=1
endif

#=============TUNER1 TSOUT OPTIONS===================
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN0_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN0=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN1_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN1=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN2_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN2=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN3_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN3=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN4_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN4=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN5_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN5=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN6_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN6=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN7_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN7=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN8_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN8=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN9_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN9=10
endif

ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=0
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=1
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=2
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=3
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=4
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=5
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=6
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=7
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=8
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=9
endif
ifeq ($(CFG_HI_TUNER1_OUTPUT_PIN10_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER1_OUTPUT_PIN10=10
endif

#=============TUNER2 BASIC ATTRIBUTE OPTIONS=======

CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_ID=2

ifeq ($(CFG_HI_TUNER2_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER2_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER2_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=4
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=8
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=9
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=10
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=13
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=17
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=19
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=20
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=21
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=22
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=23
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=24
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=25
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=26
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=27
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=28
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=29
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=30
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=32
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=34
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=35
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=36
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=37
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=38
endif
ifeq ($(CFG_HI_TUNER2_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TYPE=39
endif

ifneq ($(CFG_HI_TUNER2_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_DEV_ADDR=$(CFG_HI_TUNER2_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD2_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD2_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_DEV_ADDR=$(CFG_HI_DEMOD2_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD2_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD2_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD2_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD2_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD2_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD2_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD2_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_USE_I2C -DHI_DEMOD2_I2C_CHANNEL=$(CFG_HI_DEMOD2_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD2_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_GPIO_SDA=$(CFG_HI_DEMOD2_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_GPIO_SCL=$(CFG_HI_DEMOD2_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD2_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_RESET_GPIO=$(CFG_HI_DEMOD2_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX2_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX2_PORT=$(CFG_HI_DEMUX2_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX2_PORT=0
endif

#=============TUNER2 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD2_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_REF_CLOCK=$(CFG_HI_DEMOD2_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD2_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER2_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_MAX_LPF=$(CFG_HI_TUNER2_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER2_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_I2C_CLOCK=$(CFG_HI_TUNER2_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER2_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER2_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER2_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER2_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER2_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER2_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER2_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER2_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER2_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER2_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER2_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER2_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL2_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL2_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL2_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL2_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL2_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL2_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_ADDR=$(CFG_HI_LNBCTRL2_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL2_DEV_ADDR=0x0
endif

#=============TUNER2 Terrestrial ATTRIBUTE OPTIONS===================
ifneq ($(CFG_TER_HI_DEMOD2_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD2_REF_CLOCK=$(CFG_HI_TER_DEMOD2_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD2_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TER_TUNER2_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_MAX_LPF=$(CFG_HI_TER_TUNER2_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_MAX_LPF=34
endif

ifneq ($(CFG_HI_TER_TUNER2_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_I2C_CLOCK=$(CFG_HI_TER_TUNER2_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TER_TUNER2_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_RFAGC=0
endif
ifeq ($(CFG_HI_TER_TUNER2_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_RFAGC=1
endif

ifeq ($(CFG_HI_TER_TUNER2_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TER_TUNER2_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TER_TUNER2_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TER_TUNER2_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TER_TUNER2_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TER_TUNER2_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TER_TUNER2_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TER_TUNER2_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TER_TUNER2_TS_SYNC_HEAD_AUTO),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_SYNC_HEAD=0
endif
ifeq ($(CFG_HI_TER_TUNER2_TS_SYNC_HEAD_8BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER2_TS_SYNC_HEAD=1
endif

#=============TUNER2 TSOUT OPTIONS===================
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN0_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN0=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN1_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN1=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN2_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN2=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN3_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN3=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN4_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN4=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN5_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN5=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN6_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN6=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN7_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN7=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN8_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN8=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN9_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN9=10
endif

ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=0
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=1
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=2
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=3
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=4
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=5
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=6
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=7
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=8
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=9
endif
ifeq ($(CFG_HI_TUNER2_OUTPUT_PIN10_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER2_OUTPUT_PIN10=10
endif

#=============TUNER 3 BASIC ATTRIBUTE OPTIONS=======

CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_ID=3

ifeq ($(CFG_HI_TUNER3_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER3_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER3_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=4
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=8
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=9
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=10
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=13
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=17
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=19
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=20
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=21
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=22
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=23
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=24
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=25
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=26
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=27
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=28
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=29
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=30
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=32
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=34
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=35
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=36
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=37
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=38
endif
ifeq ($(CFG_HI_TUNER3_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TYPE=39
endif

ifneq ($(CFG_HI_TUNER3_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_DEV_ADDR=$(CFG_HI_TUNER3_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD3_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD3_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_DEV_ADDR=$(CFG_HI_DEMOD3_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD3_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD3_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD3_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD3_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD3_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD3_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD3_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_USE_I2C -DHI_DEMOD3_I2C_CHANNEL=$(CFG_HI_DEMOD3_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD3_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_GPIO_SDA=$(CFG_HI_DEMOD3_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_GPIO_SCL=$(CFG_HI_DEMOD3_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD3_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_RESET_GPIO=$(CFG_HI_DEMOD3_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX3_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX3_PORT=$(CFG_HI_DEMUX3_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX3_PORT=0
endif

#=============TUNER3 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD3_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_REF_CLOCK=$(CFG_HI_DEMOD3_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD3_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER3_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_MAX_LPF=$(CFG_HI_TUNER3_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER3_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_I2C_CLOCK=$(CFG_HI_TUNER3_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER3_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER3_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER3_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER3_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER3_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER3_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER3_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER3_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER3_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER3_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER3_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER3_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL3_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL3_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL3_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL3_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL3_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL3_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_ADDR=$(CFG_HI_LNBCTRL3_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL3_DEV_ADDR=0x0
endif

#=============TUNER3 Terrestrial ATTRIBUTE OPTIONS===================
ifneq ($(CFG_TER_HI_DEMOD3_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD3_REF_CLOCK=$(CFG_HI_TER_DEMOD3_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_DEMOD3_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TER_TUNER3_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_MAX_LPF=$(CFG_HI_TER_TUNER3_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_MAX_LPF=34
endif

ifneq ($(CFG_HI_TER_TUNER3_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_I2C_CLOCK=$(CFG_HI_TER_TUNER3_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TER_TUNER3_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_RFAGC=0
endif
ifeq ($(CFG_HI_TER_TUNER3_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_RFAGC=1
endif

ifeq ($(CFG_HI_TER_TUNER3_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TER_TUNER3_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TER_TUNER3_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TER_TUNER3_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TER_TUNER3_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TER_TUNER3_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TER_TUNER3_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TER_TUNER3_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TER_TUNER3_TS_SYNC_HEAD_AUTO),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_SYNC_HEAD=0
endif
ifeq ($(CFG_HI_TER_TUNER3_TS_SYNC_HEAD_8BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TER_TUNER3_TS_SYNC_HEAD=1
endif

#=============TUNER3 TSOUT OPTIONS===================
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN0_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN0=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN1_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN1=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN2_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN2=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN3_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN3=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN4_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN4=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN5_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN5=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN6_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN6=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN7_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN7=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN8_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN8=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN9_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN9=10
endif

ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=0
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT1),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=1
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=2
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT3),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=3
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT4),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=4
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT5),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=5
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT6),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=6
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSDAT7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=7
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSSYNC),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=8
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSVLD),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=9
endif
ifeq ($(CFG_HI_TUNER3_OUTPUT_PIN10_TSERR),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER3_OUTPUT_PIN10=10
endif

#=============TUNER 4 BASIC ATTRIBUTE OPTIONS=======

CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_ID=4

ifeq ($(CFG_HI_TUNER4_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER4_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER4_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=4
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=8
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=9
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=10
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=13
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=17
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=19
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=20
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=21
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=22
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=23
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=24
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=25
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=26
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=27
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=28
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=29
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=30
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=32
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=34
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=35
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=36
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=37
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=38
endif
ifeq ($(CFG_HI_TUNER4_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TYPE=39
endif

ifneq ($(CFG_HI_TUNER4_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_DEV_ADDR=$(CFG_HI_TUNER4_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD4_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD4_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_DEV_ADDR=$(CFG_HI_DEMOD4_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD4_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD4_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD4_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD4_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD4_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD4_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD4_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_USE_I2C -DHI_DEMOD4_I2C_CHANNEL=$(CFG_HI_DEMOD4_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD4_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_GPIO_SDA=$(CFG_HI_DEMOD4_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_GPIO_SCL=$(CFG_HI_DEMOD4_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD4_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_RESET_GPIO=$(CFG_HI_DEMOD4_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX4_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX4_PORT=$(CFG_HI_DEMUX4_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX4_PORT=0
endif

#=============TUNER4 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD4_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_REF_CLOCK=$(CFG_HI_DEMOD4_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD4_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER4_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_MAX_LPF=$(CFG_HI_TUNER4_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER4_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_I2C_CLOCK=$(CFG_HI_TUNER4_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER4_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER4_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER4_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER4_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER4_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER4_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER4_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER4_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER4_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER4_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER4_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER4_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER4_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL4_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL4_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL4_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL4_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL4_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL4_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_ADDR=$(CFG_HI_LNBCTRL4_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL4_DEV_ADDR=0x0
endif

#=============TUNER 5 BASIC ATTRIBUTE OPTIONS=======
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_ID=4

ifeq ($(CFG_HI_TUNER5_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER5_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER5_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=4
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=8
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=9
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=10
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=13
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=17
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=19
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=20
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=21
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=22
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=23
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=24
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=25
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=26
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=27
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=28
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=29
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=30
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=32
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=34
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=35
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=36
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=37
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=38
endif
ifeq ($(CFG_HI_TUNER5_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TYPE=39
endif

ifneq ($(CFG_HI_TUNER5_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_DEV_ADDR=$(CFG_HI_TUNER5_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD5_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD5_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_DEV_ADDR=$(CFG_HI_DEMOD5_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD5_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD5_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD5_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD5_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD5_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD5_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD5_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_USE_I2C -DHI_DEMOD5_I2C_CHANNEL=$(CFG_HI_DEMOD5_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD5_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_GPIO_SDA=$(CFG_HI_DEMOD5_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_GPIO_SCL=$(CFG_HI_DEMOD5_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD5_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_RESET_GPIO=$(CFG_HI_DEMOD5_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX5_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX5_PORT=$(CFG_HI_DEMUX5_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX5_PORT=0
endif

#=============TUNER5 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD5_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_REF_CLOCK=$(CFG_HI_DEMOD5_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD5_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER5_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_MAX_LPF=$(CFG_HI_TUNER5_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER5_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_I2C_CLOCK=$(CFG_HI_TUNER5_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER5_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER5_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER5_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER5_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER5_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER5_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER5_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER5_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER5_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER5_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER5_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER5_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER5_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL5_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL5_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL5_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL5_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL5_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL5_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_ADDR=$(CFG_HI_LNBCTRL5_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL5_DEV_ADDR=0x0
endif

#=============TUNER6 BASIC ATTRIBUTE OPTIONS=======
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_ID=4

ifeq ($(CFG_HI_TUNER6_SIGNAL_CAB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=1
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_SAT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=2
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_DVB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=4
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_DVB_T2),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=8
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_ISDB_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=16
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_ATSC_T),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=32
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_DTMB),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=64
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=128
endif
ifeq ($(CFG_HI_TUNER6_SIGNAL_ABSS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_SIGNAL_TYPE=256
endif

ifeq ($(CFG_HI_TUNER6_DEV_TYPE_TDA18250),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=4
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_R820C),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=8
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL203),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=9
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_AV2011),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=10
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL603),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=13
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_TDA18250B),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=17
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_RDA5815),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=19
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=20
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_CXD2861),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=21
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_SI2147),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=22
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_RAFAEL836),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=23
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL608),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=24
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=25
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=26
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_TDA182I5A),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=27
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_SI2144),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=28
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_AV2018),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=29
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=30
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL601),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=32
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL683),y)
 CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=33
 endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_AV2026),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=34
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_R850),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=35
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_R858),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=36
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=37
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=38
endif
ifeq ($(CFG_HI_TUNER6_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TYPE=39
endif

ifneq ($(CFG_HI_TUNER6_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_DEV_ADDR=$(CFG_HI_TUNER6_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_DEV_ADDR=0xc6
endif

ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=0
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3130I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=256
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3130E),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=257
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_J83B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=258
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_AVL6211),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=259
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MN88472),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=261
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3136),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=264
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3136I),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=265
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL254),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=266
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3137),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=268
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL214),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=269
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_TDA18280),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=270
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL251),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=273
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_3138),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=274
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_ATBM888X),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=275
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MN88473),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=276
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL683),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=277
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_TP5001),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=278
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_HD2501),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=279
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_AVL6381),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=280
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL541),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=281
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL581),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=282
endif
ifeq ($(CFG_HI_DEMOD6_DEV_TYPE_MXL582),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TYPE=283
endif

ifneq ($(CFG_HI_DEMOD6_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_DEV_ADDR=$(CFG_HI_DEMOD6_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_DEV_ADDR=0xb6
endif

ifeq ($(CFG_HI_DEMOD6_TS_DEFAULT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=0
endif
ifeq ($(CFG_HI_DEMOD6_TS_PARALLEL_MODE_A),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=1
endif
ifeq ($(CFG_HI_DEMOD6_TS_PARALLEL_MODE_B),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=2
endif
ifeq ($(CFG_HI_DEMOD6_TS_SERIAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=3
endif
ifeq ($(CFG_HI_DEMOD6_TS_SERIAL_50),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=4
endif
ifeq ($(CFG_HI_DEMOD6_TS_SERIAL_2BIT),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_TS_MODE=5
endif

ifeq ($(CFG_HI_DEMOD6_I2C),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_USE_I2C -DHI_DEMOD6_I2C_CHANNEL=$(CFG_HI_DEMOD6_I2C_CHANNEL)
endif

ifeq ($(CFG_HI_DEMOD6_GPIO),y)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_USE_GPIO
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_GPIO_SDA=$(CFG_HI_DEMOD6_GPIO_SDA)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_GPIO_SCL=$(CFG_HI_DEMOD6_GPIO_SCL)
endif

ifneq ($(CFG_HI_DEMOD6_RESET_GPIO),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_RESET_GPIO=$(CFG_HI_DEMOD6_RESET_GPIO)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_RESET_GPIO=0
endif

ifneq ($(CFG_HI_DEMUX6_PORT),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX6_PORT=$(CFG_HI_DEMUX6_PORT)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMUX6_PORT=0
endif

#=============TUNER6 SATELLITE ATTRIBUTE OPTIONS===================
ifneq ($(CFG_HI_DEMOD6_REF_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_REF_CLOCK=$(CFG_HI_DEMOD6_REF_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_DEMOD6_REF_CLOCK=24000
endif

ifneq ($(CFG_HI_TUNER6_MAX_LPF),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_MAX_LPF=$(CFG_HI_TUNER6_MAX_LPF)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_MAX_LPF=34
endif

ifneq ($(CFG_HI_TUNER6_I2C_CLOCK),)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_I2C_CLOCK=$(CFG_HI_TUNER6_I2C_CLOCK)
else
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_I2C_CLOCK=400
endif

ifeq ($(CFG_HI_TUNER6_RFAGC_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_RFAGC=0
endif
ifeq ($(CFG_HI_TUNER6_RFAGC_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_RFAGC=1
endif

ifeq ($(CFG_HI_TUNER6_IQSPECTRUM_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_IQSPECTRUM=0
endif
ifeq ($(CFG_HI_TUNER6_IQSPECTRUM_INVERT),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_IQSPECTRUM=1
endif

ifeq ($(CFG_HI_TUNER6_TSCLK_POLAR_FALLING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TSCLK_POLAR=0
endif
ifeq ($(CFG_HI_TUNER6_TSCLK_POLAR_RISING),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TSCLK_POLAR=1
endif

ifeq ($(CFG_HI_TUNER6_TS_FORMAT_TS),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TS_FORMAT=0
endif
ifeq ($(CFG_HI_TUNER6_TS_FORMAT_TSP),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TS_FORMAT=1
endif

ifeq ($(CFG_HI_TUNER6_TS_SERIAL_PIN_0),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TS_SERIAL_PIN=0
endif
ifeq ($(CFG_HI_TUNER6_TS_SERIAL_PIN_7),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_TS_SERIAL_PIN=1
endif

ifeq ($(CFG_HI_TUNER6_DISEQCWAVE_NORMAL),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_DISEQCWAVE=0
endif
ifeq ($(CFG_HI_TUNER6_DISEQCWAVE_ENVELOPE),y)
CFG_HI_BOARD_CONFIGS += -DHI_TUNER6_DISEQCWAVE=1
endif

ifeq ($(CFG_HI_LNBCTRL6_DEV_TYPE_NONE),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_TYPE=0
endif
ifeq ($(CFG_HI_LNBCTRL6_DEV_TYPE_MPS8125),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_TYPE=1
endif
ifeq ($(CFG_HI_LNBCTRL6_DEV_TYPE_ISL9492),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_TYPE=2
endif
ifeq ($(CFG_HI_LNBCTRL6_DEV_TYPE_A8300),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_TYPE=3
endif
ifeq ($(CFG_HI_LNBCTRL6_DEV_TYPE_A8297),y)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_TYPE=4
endif

ifneq ($(CFG_HI_LNBCTRL6_DEV_ADDR),)
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_ADDR=$(CFG_HI_LNBCTRL6_DEV_ADDR)
else
CFG_HI_BOARD_CONFIGS += -DHI_LNBCTRL6_DEV_ADDR=0x0
endif

ifeq ($(CFG_HI_CPU_ARCH),arm64)
CFG_HI_CFLAGS += -DCONFIG_ARCH_LP64_MODE
CFG_HI_KMOD_CFLAGS += -DCONFIG_ARCH_LP64_MODE
CFG_HI_BOARD_CONFIGS += -DCONFIG_ARCH_LP64_MODE
endif

