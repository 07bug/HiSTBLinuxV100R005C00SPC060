###########################################################
#cfg.mk
#���б�����CFG_��ͷ
#ע����������治���пո�
###########################################################
#for linux
#$(info ### CURDIR ###: $(CURDIR))

ifeq ($(MEDIAOS_DIR_STRUCTURE),y)
    SDK_DIR ?= $(shell cd $(CURDIR)/../../HiSTBLinux/Code/ && /bin/pwd)
else
    SDK_DIR ?= $(shell cd $(CURDIR)/../../../../../ && /bin/pwd)
endif
-include $(SDK_DIR)/base.mak
#$(info ### CFG_HI_CHIP_TYPE ###: $(CFG_HI_CHIP_TYPE))
############ begin define switchs ############################
#���ر�����������Ŀ�Ӿ����������
#if one module or feature defines CFG_XXX item, but not set the CFG_XX item val,
#just as set the val to "n"

#ndk tool cfg item, val below:
#"y":use ndk to build sme,currently used in android
#"n":do not use ndk to build sme
CFG_ENABLE_NDK=n

#huawei secure function cfg item, val below:
#"y":enable
#"n":disable
#"p":prebuilt
CFG_ENABLE_HWSECURE=y

#dra audio decoder cfg item, val below:
#"y":enable
#"n":disable
CFG_ENABLE_DRA_DECODER=n

#gstomx plugin cfg item, val below:
#"y":enable and compile from source code
#"p":enable and compile from prebuilt
#"n":disable
CFG_ENABLE_GSTOMX=y

CFG_ENABLE_GST_PLUGIN_GOOD=y

CFG_ENABLE_GST_PLUGIN_BAD=y

CFG_ENABLE_GST_LIBAV=n

CFG_ENABLE_GST_VALIDATE=y

CFG_ENABLE_GST_EXAMPLE=y

#vpss bypass for 4k video
#"y":enable
#"n":disable
CFG_ENABLE_4KP60=y

#gst-example depends on gst-bad
ifeq ($(CFG_ENABLE_GST_EXAMPLE),y)
CFG_ENABLE_GST_PLUGIN_BAD=y
endif

############ end define switchs ##############################

############ begin define vars ############################
#���붨��
#project name
CFG_PROJECT_NAME=histb.linux.$(CFG_HI_CHIP_TYPE).plugin_only

#toolchain name
CFG_TOOLCHAINS_NAME=$(CFG_HI_ARM_TOOLCHAINS_NAME)
#CFG_TOOLCHAINS_NAME=arm-histbv320-linux

#��Դ�����������������е�ƽ̨
CFG_HOST_TYPE=$(CFG_TOOLCHAINS_NAME)

#toolchain sysroot
#�����ndk��ô����Ҫ����sysroot����config.mk�ж���
ifneq ($(CFG_ENABLE_NDK), y)
CFG_COMPILE_SYSROOT=$(SDK_DIR)/tools/linux/toolchains/$(CFG_TOOLCHAINS_NAME)/target
else
CFG_COMPILE_SYSROOT=
endif

##########begin ���Ŀ¼����###############################
#���������TOPDIR(MediaOS),��CFG_RT��ʼ
#ע����TVOS��Ŀ¼�ṹ��mediaos��Ŀ¼�ṹ���б仯�ģ���envsetup.sh�ж���MEDIAOS_DIR_STRUCTURE=yΪmediaosĿ¼��
ifeq ($(MEDIAOS_DIR_STRUCTURE),y)
    #SME������ƽ̨SDK·�������TOPDIRĿ¼
    CFG_RT_PLATFORM_SDK_DIR=HiSTBLinux
else
    CFG_RT_PLATFORM_SDK_DIR=../../../..
endif

#SME ������hisi SDK��·����
CFG_RT_HI_SDK_DIR=$(CFG_RT_PLATFORM_SDK_DIR)/Code

#SME������ƽ̨SDKͷ�ļ�·�������TOPDIRĿ¼
CFG_RT_PLATFORM_SDK_INC_DIR= \
	$(CFG_RT_HI_SDK_DIR)/source/component/hal/include \
	$(CFG_RT_HI_SDK_DIR)/sample/common \
	$(CFG_RT_HI_SDK_DIR)/source/msp/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/higo/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/tde/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/drv/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/drv/mce \
	$(CFG_RT_HI_SDK_DIR)/source/common/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/api/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/drv/include \
	$(CFG_RT_HI_SDK_DIR)/source/common/api/mmz \
	$(CFG_RT_HI_SDK_DIR)/source/component/zlib/include \
	$(CFG_RT_HI_SDK_DIR)/source/component/ha_codec/include \

#SME������ƽ̨SDK��̬��·�������TOPDIRĿ¼
CFG_RT_PLATFORM_SDK_DYNAMIC_LIB_DIR=$(CFG_RT_PLATFORM_SDK_DIR)/Code/out/$(CFG_HI_CHIP_TYPE)/$(CFG_HI_OUT_DIR)/lib/share/

#SME omx��Դ���������OMXͷ�ļ�Ŀ¼�����TOPDIRĿ¼
CFG_RT_OMX_H_DIR=$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/include
CFG_RT_OMX_PRIVATE_H=$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/base \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/omx_ha/include \
	$(CFG_RT_HI_SDK_DIR)/source/msp/api/omx/omx_audio/common/osal

#audiosink element name
CFG_AUDIOSINK_NAME=smeaudiosink_hihal

#videosink element name
CFG_VIDEOSINK_NAME=smevideosink_hihal

##########end ���Ŀ¼����###############################

#ͨ�ú�
CFG_COMMON_MACRO=-D__LINUX__ -DLINUX_OS
CFG_COMMON_MACRO += -D_LARGEFILE64_SOURCE
ifeq ($(CFG_ENABLE_4KP60), y)
CFG_COMMON_MACRO += -DBYPASS_FOR_4K
endif
############ end define vars ##############################
