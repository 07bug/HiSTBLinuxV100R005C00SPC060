#===============================================================================
#   export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
#   local variables
#===============================================================================
CFLAGS += -I$(MSP_DIR)/api/adec
CFLAGS += -I$(MSP_DIR)/api/vo
CFLAGS += -I$(MSP_DIR)/api/ao/render
CFLAGS += -I$(MSP_DIR)/../component/ha_codec/include
CFLAGS += -I$(MSP_DIR)/api/higo/include
CFLAGS += -I$(MSP_DIR)/api/tde/include
CFLAGS += -I$(MSP_DIR)/api/jpge/include
CFLAGS += -I$(MSP_DIR)/api/pvr/include

CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600
CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

MSP_OBJ_DIR := $(HI_OUT_DIR)/obj/source/msp/api
MSP_OBJ_DIR64 := $(HI_OUT_DIR)/obj64/source/msp/api

LIB_EXTRACT = $(shell if [ -f $(3) ] ; then \
        mkdir -p $(1) && cd $(1) && $(2)-ar -x $(3); \
    fi)

ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    CFG_HI_CFLAGS += -DCA_FRAMEWORK_V100_SUPPORT
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    CFG_HI_CFLAGS += -DCA_FRAMEWORK_V200_SUPPORT
else
    $(error otp_klad version is error)
endif

#--------------- HDMI ------------------
ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
HDMI_VER := hdmi_1_4
else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
HDMI_VER := hdmi_2_0
CFLAGS   += -DHI_HDMI_SUPPORT_2_0
endif

CFLAGS +=   -I$(MSP_DIR)/drv/hdmi/$(HDMI_VER) \
            -DCONFIG_HDMI_STB_SDK \
            -DDVI_SUPPORT

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
CFLAGS += -DHDMI_HDCP_SUPPORT
endif

ifeq ($(CFG_HI_HDR_SUPPORT),y)
CFLAGS += -DHDMI_HDR_SUPPORT
endif

ifeq ($(CFG_HI_HDMI_CEC_FORCE_RAWDATA),y)
CFLAGS += -DHDMI_FORCE_RAWDATA
endif

SRCS := hdmi/$(HDMI_VER)/mpi_hdmi.c hdmi/$(HDMI_VER)/unf_hdmi.c

#--------------- GPIO ------------------
SRCS += gpio/unf_gpio.c

#--------------- I2C ------------------
SRCS += i2c/unf_i2c.c

#--------------- VO ------------------
ifeq ($(CFG_HI_HDR_SUPPORT),y)
CFLAGS += -I$(MSP_DIR)/api/vo/dolby/include
endif

SRCS += vo/unf_vo.c \
        vo/unf_display.c \
        vo/unf_edid.c \
        vo/mpi_win.c \
        vo/mpi_disp_tran.c \
        vo/mpi_disp.c \
        vo/win_ratio.c \
        vo/mpi_edid.c

ifeq ($(CFG_HI_VDP_VIDEO_LINEDCMP),y)
CFLAGS += -DHI_VDP_VIDEO_LINEDCMP

SRCS += vo/vo_algbase/src/dcmp_implement.c

VO_DCMP_LIB := $(MSP_DIR)/api/vo/vo_algbase/src/line_dcmp/$(CFG_HI_ARM_TOOLCHAINS_NAME)/libdcmp.a

VO_DCMP_OBJS := $(shell $(CFG_HI_ARM_TOOLCHAINS_NAME)-ar -t $(VO_DCMP_LIB))

SRCS += $(addprefix vo/,$(VO_DCMP_OBJS))

$(call LIB_EXTRACT, $(MSP_OBJ_DIR)/vo, $(CFG_HI_ARM_TOOLCHAINS_NAME), $(VO_DCMP_LIB))
endif

#--------------- PDM ------------------
SRCS += pdm/unf_pdm.c pdm/mpi_pdm.c pdm/hi_db.c

#--------------- CIPHER ------------------
include $(MSP_DIR)/api/cipher/build.mak

#--------------- ADVCA ------------------
ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    SRCS += advca/unf_advca.c
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    SRCS += klad/unf_klad.c \
            klad/common_ca/unf_klad_common_ca.c

    ifeq ($(CFG_ADVCA_CONAX),y)
        SRCS += klad/conax/unf_klad_conax.c
    endif

    ifeq ($(CFG_ADVCA_NAGRA),y)
        SRCS += klad/nagra/unf_cert.c
        SRCS += klad/nagra/unf_klad_nagra.c
    endif

    ifeq ($(CFG_ADVCA_DCAS),y)
        CFLAGS += -DHI_ADVCA_DCAS_SUPPORT
        SRCS += klad/dcas/unf_klad_dcas.c
    endif

    ifeq ($(CFG_ADVCA_IRDETO),y)
        SRCS += klad/irdeto/unf_klad_irdeto.c
    endif

    ifeq ($(CFG_ADVCA_VERIMATRIX),y)
        SRCS += klad/verimatrix/unf_klad_verimatrix.c
    endif
endif
#--------------- FRONTEND ------------------
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SRCS += frontend/unf_tuner.c

ifeq ($(CFG_HI_DISEQC_SUPPORT),y)
CFLAGS += -DDISEQC_SUPPORT

SRCS += frontend/unf_diseqc.c frontend/unf_unicable.c

UNICABLE_LIBNAME := libhi_unicable.a

ifeq ($(HI_USER_SPACE_LIB),y)
UNICABLE_LIB := $(MSP_DIR)/api/frontend/lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/$(UNICABLE_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR)/frontend, $(CFG_HI_ARM_TOOLCHAINS_NAME), $(UNICABLE_LIB))
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
UNICABLE64_LIB := $(MSP_DIR)/api/frontend/lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/$(UNICABLE_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR64)/frontend, $(CFG_HI_AARCH64_TOOLCHAINS_NAME), $(UNICABLE64_LIB))
endif

endif
endif

#--------------- SPI ------------------
ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
SRCS += spi/unf_spi.c
endif

#--------------- IR ------------------
ifeq ($(CFG_HI_IR_TYPE_STD),y)
SRCS += ir/unf_ir_std.c
else ifeq ($(CFG_HI_IR_TYPE_S2),y)
SRCS += ir/unf_ir.c
else ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
SRCS += ir/unf_ir_lirc.c
endif

#--------------- DEMUX ------------------
DEMUX_VER := demux_v2

CFLAGS += -I$(MSP_DIR)/drv/demux/$(DEMUX_VER)

SRCS += demux/$(DEMUX_VER)/mpi_demux.c \
        demux/$(DEMUX_VER)/unf_demux.c \
        demux/$(DEMUX_VER)/mpi_descrambler.c \
        demux/$(DEMUX_VER)/unf_descrambler.c

#--------------- TSIO ------------------
ifeq ($(CFG_HI_TSIO_SUPPORT),y)
SRCS += tsio/mpi_tsio.c \
        tsio/unf_tsio.c
endif

#--------------- PLCIPHER ------------------
ifeq ($(CFG_HI_PLCIPHER_SUPPORT),y)
SRCS += plcipher/unf_payloadcipher.c \
        plcipher/mpi_plcipher.c
endif

#--------------- TDE ------------------
SRCS += tde/unf_tde.c

#--------------- HWC ------------------
ifeq ($(CFG_HI_GFX2D_SUPPORT),y)
GFX2D_VERSION:=-DHWC_VERSION=0x100
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3719mv100 hi3718mv100), )
GFX2D_VERSION:=-DHWC_VERSION=0x200
endif
ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200)
GFX2D_VERSION:=-DHWC_VERSION=0x400
endif
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450 hi3798mv310), )
GFX2D_VERSION:=-DHWC_VERSION=0x500
endif
CFLAGS += $(GFX2D_VERSION)
CFLAGS += -I$(MSP_DIR)/api/gfx2d/include
SRCS += gfx2d/hi_gfx2d_api.c
endif

#--------------- JPGE ------------------
SRCS += jpge/unf_jpge.c

#--------------- JPEG ------------------
CFLAGS += -I$(COMPONENT_DIR)/jpeg/include
CFLAGS += -I$(MSP_DIR)/api/jpeg/include             \
          -I$(MSP_DIR)/api/jpeg/grc_cmm_inc         \
          -I$(MSP_DIR)/api/jpeg/jpeg-hal/inc_hard   \
          -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_hard   \
          -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_comm   \
          -I$(MSP_DIR)/api/jpeg/jpeg-hal/src_soft   \
          -I$(MSP_DIR)/drv/jpeg/include             \
          -I$(MSP_DIR)/api/tde/include              \
          -I$(COMMON_DIR)/api/include               \
          -I$(COMMON_DIR)/include

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_PROC_SUPPORT
else
CFLAGS += -DCONFIG_GFX_PROC_UNSUPPORT
endif

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DCONFIG_GFX_MMU_SUPPORT
endif

CFLAGS += -DCONFIG_GFX_ONLY_HARD_DECOMPRESS

SRCS += jpeg/jpeg-hal/src_hard/hi_jpeg_api.c     \
        jpeg/jpeg-hal/src_hard/jpeg_hal_dev.c    \
        jpeg/jpeg-hal/src_hard/jpeg_hal_dec.c

#--------------- PQ ------------------
SRCS += pq/mpi_pq.c pq/unf_pq.c

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
#--------------- OTP ------------------
ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    SRCS += otp/unf_otp.c otp/mpi_otp_v100.c
    CFLAGS += -DOTP_VERSION_V100
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    CFLAGS +=  -I$(MSP_DIR)/api/otp/include
    CFLAGS += -DOTP_VERSION_V200
    SRCS += otp/unf_otp.c otp/mpi_otp_v200.c

    CFLAGS += -DHI_OTP_DEBUG_SUPPORT
    CFLAGS += -DOTP_DATA_FILE_DEBUG=\"./otp/data/otp_data_$(CFG_HI_CHIP_TYPE).txt\"

    ifeq ($(CFG_ADVCA_CONAX),y)
        SRCS += otp/conax/unf_otp_conax.c
        CFLAGS += -DHI_OTP_C3_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_C3=\"./otp/data/otp_data_conax_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_NAGRA),y)
        SRCS += otp/nagra/unf_otp_nagra.c
        CFLAGS += -DHI_OTP_C1_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_C1=\"./otp/data/otp_data_nagra_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_DCAS),y)
        SRCS += otp/dcas/unf_otp_dcas.c
        CFLAGS += -DHI_OTP_DCAS_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_DCAS=\"./otp/data/otp_data_dcas_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_IRDETO),y)
        SRCS += otp/irdeto/unf_otp_irdeto.c
        CFLAGS += -DHI_OTP_C2_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_C2=\"./otp/data/otp_data_irdeto_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_VERIMATRIX),y)
        SRCS += otp/verimatrix/unf_otp_verimatrix.c
        CFLAGS += -DHI_OTP_C6_SUPPORT
        ifeq ($(CFG_ADVCA_VERIMATRIX_ULTRA),y)
        CFLAGS += -DOTP_DATA_FILE_C6=\"./otp/data/otp_data_vmx_ultra_$(CFG_HI_CHIP_TYPE).txt\"
        else
        CFLAGS += -DOTP_DATA_FILE_C6=\"./otp/data/otp_data_vmx_advanced_$(CFG_HI_CHIP_TYPE).txt\"
        endif
    endif

    ifeq ($(CFG_ADVCA_CTI),y)
        SRCS += otp/common_ca/unf_otp_common_ca.c
        CFLAGS += -DHI_OTP_COMMMON_CA_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_COMMMON_CA=\"./otp/data/otp_data_com_ca_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_SUMA),y)
        SRCS += otp/common_ca/unf_otp_common_ca.c
        CFLAGS += -DHI_OTP_COMMMON_CA_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_COMMMON_CA=\"./otp/data/otp_data_com_ca_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_NOVEL),y)
        SRCS += otp/common_ca/unf_otp_common_ca.c
        CFLAGS += -DHI_OTP_COMMMON_CA_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_COMMMON_CA=\"./otp/data/otp_data_com_ca_$(CFG_HI_CHIP_TYPE).txt\"
    endif

    ifeq ($(CFG_ADVCA_PANACCESS),y)
        SRCS += otp/common_ca/unf_otp_common_ca.c
        CFLAGS += -DHI_OTP_COMMMON_CA_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_COMMMON_CA=\"./otp/data/otp_data_com_ca_$(CFG_HI_CHIP_TYPE).txt\"
    endif
    ifeq ($(CFG_ADVCA_OTHER),y)
        SRCS += otp/common_ca/unf_otp_common_ca.c
        CFLAGS += -DHI_OTP_COMMMON_CA_SUPPORT
        CFLAGS += -DOTP_DATA_FILE_COMMMON_CA=\"./otp/data/otp_data_com_ca_$(CFG_HI_CHIP_TYPE).txt\"
    endif
    OTP_DATA_LIBNAME := libhi_otpdata.a
    ifeq ($(HI_USER_SPACE_LIB64),y)
        TOOLCHAINS := $(CFG_HI_AARCH64_TOOLCHAINS_NAME)
        DIR := $(MSP_OBJ_DIR64)
        OTP_DATA_LIB := $(MSP_DIR)/api/otp/lib/$(TOOLCHAINS)/$(OTP_DATA_LIBNAME)
        $(call LIB_EXTRACT, $(DIR)/otp/lib/, $(TOOLCHAINS), $(OTP_DATA_LIB))
    endif
    ifeq ($(HI_USER_SPACE_LIB),y)
        TOOLCHAINS := $(CFG_HI_ARM_TOOLCHAINS_NAME)
        DIR := $(MSP_OBJ_DIR)
        OTP_DATA_LIB := $(MSP_DIR)/api/otp/lib/$(TOOLCHAINS)/$(OTP_DATA_LIBNAME)
        $(call LIB_EXTRACT, $(DIR)/otp/lib/, $(TOOLCHAINS), $(OTP_DATA_LIB))
    endif
    SRCS += otp/lib/otp_data.c otp/lib/otp_drv.c
endif

#--------------- PM ------------------
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLAGS += -DHI_KEYLED_SUPPORT
endif

SRCS += pm/unf_pmoc.c pm/pmoc_usb_wakeup.c

#--------------- AVPLAY ------------------
ifeq ($(CFG_HI_MSP_BUILDIN),y)
CFLAGS += -DHI_MSP_BUILDIN
endif

ifeq ($(CFG_HI_SONIC_SUPPORT),y)
CFLAGS += -DHI_AUD_SONIC_SUPPORT
endif

ifeq ($(CFG_HI_AVPLAY_PLAY_AND_REC_SUPPORT),y)
CFLAGS += -DHI_AVPLAY_PLAY_AND_REC_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420 hi3716mv450),)
CFLAGS += -DHI_AVPLAY_MAX_FULLHD
endif

ifeq ($(CFG_HI_PROC_SUPPORT),y)
CFLAGS += -DHI_AVPLAY_PROC_SUPPORT
endif

SRCS += avplay/mpi_avplay.c \
        avplay/unf_avplay.c \
        avplay/avplay_frc.c \
        avplay/frame_detect.c \
        avplay/bitstream.c

#--------------- SYNC ------------------
SRCS += sync/mpi_sync.c

#--------------- ADEC ------------------
CFLAGS += -DHI_ADEC_OUTPUTBUF_FRAMENUM=$(CFG_HI_ADEC_OUTPUTBUF_FRAMENUM)
CFLAGS += -I$(COMPONENT_DIR)/ha_sound/hi_sonic/include

SRCS += adec/mpi_adec.c \
        adec/mpi_adec_core.c \
        adec/mpi_adec_imple.c \
        adec/mpi_sonic.c

ifeq ($(CFG_HI_ADEC_AUDSPECTRUM_SUPPORT),y)
CFLAGS += -DHI_ADEC_AUDSPECTRUM_SUPPORT
SRCS += adec/mpi_adec_waveform.c
endif

ifdef CFG_HI_ADVCA_FUNCTION
ADEC_IMPLE_LIBNAME := libhi_adecimple_advca.a
else
ADEC_IMPLE_LIBNAME := libhi_adecimple.a
endif

ifeq ($(HI_USER_SPACE_LIB),y)
ADEC_IMPLE_LIB := $(MSP_DIR)/api/adec/lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/$(ADEC_IMPLE_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR)/adec, $(CFG_HI_ARM_TOOLCHAINS_NAME), $(ADEC_IMPLE_LIB))
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
ADEC_IMPLE64_LIB := $(MSP_DIR)/api/adec/lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/$(ADEC_IMPLE_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR64)/adec, $(CFG_HI_AARCH64_TOOLCHAINS_NAME), $(ADEC_IMPLE64_LIB))
endif

CFLAGS += -DHI_LINUX_PRODUCT
#--------------- AO ------------------
CFLAGS += -I$(MSP_DIR)/drv/adsp/adsp_v1_1/include

ifeq ($(CFG_HI_AI_SUPPORT),y)
CFLAGS += -DHI_SOUND_AI_SUPPORT
endif

SRCS += ao/unf_sound.c \
        ao/mpi_ao.c \
        ao/mpi_vir.c \
        ao/mpi_lowlatency.c \
        ao/render/engine_sink.c \
        ao/render/engine_codec.c \
        ao/render/engine_sync.c \
        ao/render/engine_customer.c \
        ao/render/kfifo.c \
        ao/render/pts_queue.c \
        ao/render/render.c \
        ao/render/render_buffer.c \
        ao/render/render_common.c \
        ao/render/render_engine.c \
        ao/render/render_source.c \
        ao/render/engine_policy.c \
        ao/render/ipc_common.o \
        ao/render/ipc_server.o \
        ao/render/ipc_client.o \
        ao/render/ao_isb.o

ifeq ($(CFG_HI_PROC_SUPPORT),y)
SRCS += ao/render/render_proc.c
endif

#--------------- VDEC ------------------
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
VDEC_DRV_VER := vdec_v2.1
VFMW_DRV_VER := vfmw_v5.1
else
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450),)
VDEC_DRV_VER := vdec_v2.0
VFMW_DRV_VER := vfmw_v5.0
else
VDEC_DRV_VER := vdec_v1.0
VFMW_DRV_VER := vfmw_v4.0
endif
endif

CFLAGS +=   -I$(MSP_DIR)/drv/vfmw/$(VFMW_DRV_VER)  \
            -I$(MSP_DIR)/drv/vfmw/$(VFMW_DRV_VER)/adapter  \
            -I$(MSP_DIR)/drv/vdec/$(VDEC_DRV_VER)

ifeq ($(CFG_HI_SMMU_SUPPORT),y)
CFLAGS += -DVFMW_MMU_SUPPORT
endif

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Hi3716MV410 or Hi3716MV420 config start
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC=0
endif

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# Hi3716MV410 or Hi3716MV420 config end
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

#===============================================================================
# 256M ddr memory config flags
#===============================================================================
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P_IN_256),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_256=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_256=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC_IN_256),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_256=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_256=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_2160P_IN_256),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_256=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_256=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_4K_IN_256),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_256=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_256=0
endif

#===============================================================================
# 512M ddr memory config flags
#===============================================================================
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P_IN_512),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_512=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_512=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC_IN_512),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_512=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_512=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_2160P_IN_512),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_512=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_512=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_4K_IN_512),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_512=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_512=0
endif

#===============================================================================
# 768M ddr memory config flags
#===============================================================================
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P_IN_768),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_768=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_768=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC_IN_768),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_768=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_768=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_2160P_IN_768),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_768=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_768=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_4K_IN_768),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_768=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_768=0
endif

#===============================================================================
# 1024M ddr memory config flags
#===============================================================================
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P_IN_1024),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_1024=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_1024=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC_IN_1024),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_1024=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_1024=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_2160P_IN_1024),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_1024=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_1024=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_4K_IN_1024),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_1024=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_1024=0
endif

#===============================================================================
# 2048M ddr memory config flags
#===============================================================================
ifeq ($(CFG_HI_VIDEO_PRE_CAP_1080P_IN_2048),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_2048=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_2048=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_MVC_IN_2048),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_2048=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_2048=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_2160P_IN_2048),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_2048=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_2048=0
endif

ifeq ($(CFG_HI_VIDEO_PRE_CAP_4K_IN_2048),y)
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_2048=1
else
CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_2048=0
endif

#===============================================================================
# memory config end
#===============================================================================
ifeq ($(CFG_HI_VDEC_MJPEG_SUPPORT),y)
CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=1
else
CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=0
endif

CFLAGS += -DHI_VDEC_REG_CODEC_SUPPORT=1

ifeq ($(CFG_HI_VDEC_USERDATA_CC_SUPPORT),y)
CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=1

CFLAGS += -DHI_VDEC_USERDATA_CC_BUFSIZE=$(CFG_HI_VDEC_USERDATA_CC_BUFSIZE)
else
CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=0
endif

CFLAGS += -DHI_VDEC_DFS_SUPPORT=1

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFLAGS += -DHI_TEE_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv310),)
VDEC_API_VER := vdec_v2.1
else
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450),)
VDEC_API_VER := vdec_v2.0
else
VDEC_API_VER := vdec_v1.0
endif
endif

SRCS += vdec/$(VDEC_API_VER)/hi_codec.c \
        vdec/$(VDEC_API_VER)/mpi_vdec_adapter.c \
        vdec/$(VDEC_API_VER)/mpi_vdec.c

ifeq ($(CFG_HI_VDEC_MJPEG_SUPPORT),y)
SRCS += vdec/$(VDEC_API_VER)/mpi_vdec_mjpeg.c
endif

#--------------- WDG ------------------
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
SRCS += wdg/unf_wdg.c
endif

#--------------- MCE ------------------
SRCS += mce/unf_mce.c
endif

#--------------- PVR ------------------
ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_PVR_EXTRA_BUF_SUPPORT),y)
CFLAGS += -DHI_PVR_EXTRA_BUF_SUPPORT
CFLAGS += -DHI_PVR_FIFO_DIO
endif

ifeq ($(CFG_HI_TEE_SUPPORT),y)
CFLAGS += -I$(TEE_API_INCLUDE)
endif

SRCS += pvr/hi_pvr_fifo.c \
        pvr/hi_pvr_buffer.c \
        pvr/hi_pvr_index.c \
        pvr/hi_pvr_intf.c \
        pvr/hi_pvr_play_ctrl.c \
        pvr/hi_pvr_rec_ctrl.c \
        pvr/hi_pvr_index_v0.c \
        pvr/hi_pvr_index_v1.c \
        pvr/unf_pvr.c \
        pvr/hi_pvr_smooth_ctrl.c

ifeq ($(CFG_HI_TEE_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200 hi3798mv200 hi3798mv300 hi3796mv200 hi3716mv450),)
CFLAGS += -DHI_TEE_PVR_SUPPORT
SRCS += pvr/hi_pvr_tee.c
endif
endif

ifdef CFG_HI_ADVCA_FUNCTION
PVR_SMOOTH_LIBNAME := libhi_pvrsmooth_advca.a
else
PVR_SMOOTH_LIBNAME := libhi_pvrsmooth.a
endif

ifeq ($(HI_USER_SPACE_LIB),y)
PVR_SMOOTH_LIB := $(MSP_DIR)/api/pvr/lib/$(CFG_HI_ARM_TOOLCHAINS_NAME)/$(PVR_SMOOTH_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR)/pvr, $(CFG_HI_ARM_TOOLCHAINS_NAME), $(PVR_SMOOTH_LIB))
endif

ifeq ($(HI_USER_SPACE_LIB64),y)
PVR_SMOOTH64_LIB := $(MSP_DIR)/api/pvr/lib/$(CFG_HI_AARCH64_TOOLCHAINS_NAME)/$(PVR_SMOOTH_LIBNAME)

$(call LIB_EXTRACT, $(MSP_OBJ_DIR64)/pvr, $(CFG_HI_AARCH64_TOOLCHAINS_NAME), $(PVR_SMOOTH64_LIB))
endif
else
SRCS += pvr/unf_pvr.c
endif

#--------------- AI ------------------
ifeq ($(CFG_HI_AI_SUPPORT),y)
SRCS += ai/unf_ai.c ai/mpi_ai.c
endif

#--------------- KEYLED ------------------
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
SRCS += keyled/unf_keyled.c
endif

#--------------- AENC ------------------
ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_AI_SUPPORT),y)
CFLAGS += -DHI_AENC_AI_SUPPORT
endif

SRCS += aenc/unf_aenc.c aenc/mpi_aenc.c aenc/mpi_aenc_core.c aenc/mpi_aenc_lsrc.c
endif

#--------------- CI ------------------
ifeq ($(CFG_HI_CI_SUPPORT),y)
SRCS += ci/unf_ci.c ci/mpi_ci.c
endif

#--------------- HDCP ------------------
ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
SRCS += hdcp/unf_hdcp.c
endif

#--------------- SCI ------------------
ifeq ($(CFG_HI_SCI_SUPPORT),y)
SRCS += sci/unf_sci.c
endif

#--------------- VI ------------------
ifeq ($(CFG_HI_VI_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
CFLAGS += -DHI_VI_SD_CREATE_WINDOW
endif

SRCS += vi/mpi_vi.c vi/unf_vi.c
endif

#--------------- VENC ------------------
ifeq ($(CFG_HI_VENC_SUPPORT),y)
SRCS += venc/mpi_venc.c venc/unf_venc.c
endif

#--------------- PWM ------------------
ifeq ($(CFG_HI_PWM_SUPPORT),y)
SRCS += pwm/unf_pwm.c
endif
#-------------------------------------

#--------------- SESSION MANAGE ------------------
ifeq ($(CFG_HI_SM_SUPPORT),y)
SRCS += session_manager/unf_session_manager.c
SRCS += session_manager/mpi_session_manager.c
endif
#-------------------------------------

#--------------- MAILBOX ------------------
ifeq ($(CFG_HI_MAILBOX_SUPPORT),y)
SRCS += mailbox/unf_mailbox.c
SRCS += mailbox/mpi_mailbox.c
endif
#-------------------------------------

LIB_NAME := libhi_msp

HEADER_FILES := $(wildcard $(MSP_UNF_INCLUDE)/*.h)          \
                $(MSP_DIR)/api/tde/include/hi_tde_api.h     \
                $(MSP_DIR)/api/tde/include/hi_tde_errcode.h \
                $(MSP_DIR)/api/tde/include/hi_tde_type.h    \
                $(MSP_DIR)/drv/hifb/include/hifb.h

include $(SDK_DIR)/hi_rules.mak
