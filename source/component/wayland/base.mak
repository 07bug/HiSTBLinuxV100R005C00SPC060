#===============================================================================
#want to product c and h file from xml, and product wayland-scanner
#===============================================================================
# WL_PRODUCT_FILE := y


#===============================================================================
# sdk dir
#===============================================================================
ifeq ($(SDK_DIR),)
SDK_DIR := /home/y00181162/007-STB-SDK/SDK_SVN_V1R2/trunk/BBIT-Test/Code
endif

#===============================================================================
# wayland dir
#===============================================================================
ifeq ($(WL_DIR),)
WL_DIR := /home/y00181162/007-STB-SDK/SDK_SVN_V1R2/trunk/BBIT-Test/Code/source/component/wayland
endif

#===============================================================================
# toolchains
#===============================================================================
WL_ARM_TOOLCHAINS_NAME := arm-histbv320-linux

#===============================================================================
# out dir
#===============================================================================
WL_OUT_DIR := ${WL_DIR}/out

#===============================================================================
# install dir
#===============================================================================
WL_INSTALL_DIR := ${WL_OUT_DIR}/weston

#===============================================================================
# display
#===============================================================================
AT := @

#===============================================================================
#cflags
#===============================================================================
WL_CFLAGS := -DHI_SMMU_SUPPORT

ifeq ($(WL_ARM_TOOLCHAINS_NAME),arm-histbv310-linux)
WL_CFLAGS += -mcpu=cortex-a9
else ifeq ($(WL_ARM_TOOLCHAINS_NAME),arm-histbv320-linux)
WL_CFLAGS += -mcpu=cortex-a9
else ifeq ($(WL_ARM_TOOLCHAINS_NAME),aarch64-histbv100-linux)
WL_CFLAGS += -mcpu=cortex-a53
endif

ifeq ($(WL_ARM_TOOLCHAINS_NAME),arm-histbv320-linux)
WL_CFLAGS += -mfloat-abi=hard -mfpu=vfpv3-d16
else
WL_CFLAGS += -mfloat-abi=softfp -mfpu=vfpv3-d16
endif

ifeq ($(WL_PRODUCT_FILE),y)
WL_CFLAGS :=
endif
