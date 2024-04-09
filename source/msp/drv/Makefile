#=======================================
#   export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(srctree),)
        KERNEL_DIR := $(srctree)

        SDK_DIR := $(shell cd $(KERNEL_DIR)/../../.. && /bin/pwd)
    else
        SDK_DIR := $(shell cd $(CURDIR)/../../.. && /bin/pwd)
    endif

    include $(SDK_DIR)/base.mak
endif

#=======================================
#   local variable
#======================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv430),)
PNG_SUPPORT := n
else
PNG_SUPPORT := y
endif
#=======================================
#   local variable
#======================================
ifeq ($(CFG_HI_OTP_KLAD_V100),y)
    CFG_HI_KMOD_CFLAGS += -DCA_FRAMEWORK_V100_SUPPORT
else ifeq ($(CFG_HI_OTP_KLAD_V200),y)
    CFG_HI_KMOD_CFLAGS += -DCA_FRAMEWORK_V200_SUPPORT
else
    $(error otp_klad version is error)
endif

ifeq ($(CFG_HI_LOADER_APPLOADER),y)
    objects := gpio ir i2c pm pdm pq hdmi vo hifb tde cipher otp

    ifeq ($(CFG_HI_OTP_KLAD_V100),y)
        objects += advca
    else
        objects += klad
    endif

    ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
        objects += frontend
    endif

    ifeq ($(CFG_HI_DEMUX_SUPPORT),y)
        objects += demux
    endif

    ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
        objects += keyled
    endif

    ifeq ($(CFG_HI_ADVCA_RUNTIME_CHECK_ENABLE),y)
        objects += runtime_check
    endif
else ifeq ($(CFG_HI_RECOVERY_SUPPORT),y)
    objects := gpio ir pdm pq hdmi vo hifb tde jpeg cipher otp

    ifeq ($(CFG_HI_OTP_KLAD_V100),y)
        objects += advca
    else
        objects += klad
    endif
    
    ifeq ($(PNG_SUPPORT),y)
        objects += png
    endif

    ifeq ($(CFG_HI_GFX2D_SUPPORT),y)
        objects += gfx2d
    endif

    ifeq ($(CFG_HI_GPU_SUPPORT),y)
        objects += gpu dbe
    endif

    ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
        objects += keyled
    endif
else
    objects := gpio ir i2c pm pdm pq hdmi vo hifb tde jpeg cipher otp ddr sync adsp aiao adec vfmw vdec vpss mce omxvdec

    ifeq ($(CFG_HI_LOAD_CAS_IMAGE),y)
        objects += cas_image_load
    endif

    ifeq ($(CFG_HI_OTP_KLAD_V100),y)
        objects += advca
    else
        objects += klad

        ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
            objects += klad/nagra/cert
        endif
    endif

    ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
        objects += frontend
    endif

    ifeq ($(CFG_HI_DEMUX_SUPPORT),y)
        objects += demux
    endif

    ifeq ($(CFG_HI_SM_SUPPORT),y)
        objects += session_manager
    endif

    ifeq ($(CFG_HI_MAILBOX_SUPPORT),y)
        objects += mailbox
    endif

    ifeq ($(CFG_HI_PWM_SUPPORT),y)
        objects += pwm
    endif

    ifeq ($(CFG_HI_JPGE_SUPPORT),y)
        objects += jpge
    endif

    ifeq ($(PNG_SUPPORT),y)
        objects += png
    endif

    ifeq ($(CFG_HI_GFX2D_SUPPORT),y)
        objects += gfx2d
    endif

    ifeq ($(CFG_HI_PVR_SUPPORT),y)
        objects += pvr
    endif

    ifeq ($(CFG_HI_GPU_SUPPORT),y)
        objects += gpu dbe
    endif

    ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
        objects += keyled
    endif

    ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
        objects += spi
    endif

    ifeq ($(CFG_HI_SCI_SUPPORT),y)
        objects += sci
    endif

    ifeq ($(CFG_HI_AENC_SUPPORT),y)
        objects += aenc
    endif

    ifeq ($(CFG_HI_VENC_SUPPORT),y)
        objects += venc
    endif

    ifeq ($(CFG_HI_CI_SUPPORT),y)
        objects += ci

        ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
            objects += cimaxplus
        endif
    endif

    ifeq ($(CFG_HI_VI_SUPPORT),y)
        objects += vi
    endif

    ifeq ($(CFG_HI_ADAC_SUPPORT),y)
        objects += adac
    endif

    ifeq ($(CFG_HI_TSIO_SUPPORT),y)
        objects += tsio
    endif

    ifeq ($(CFG_HI_PLCIPHER_SUPPORT),y)
        objects += plcipher
    endif

    ifeq ($(CFG_HI_ADVCA_RUNTIME_CHECK_ENABLE),y)
        objects += runtime_check
    endif
endif

ifeq ($(HI_DRV_BUILDTYPE),y)
    objects += base
endif

obj-y += ${addsuffix /,${objects}}

