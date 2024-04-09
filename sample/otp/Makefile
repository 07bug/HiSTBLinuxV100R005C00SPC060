#===============================================================================
# export variable
#===============================================================================
#ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../.. && /bin/pwd)
include $(SDK_DIR)/base.mak
#endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
SAMPLE_IMAGES := sample_otp_mmap \
    sample_otp_test    \
    sample_otp_setcustomerkey \
    sample_otp_setstbrootkey \
    sample_otp_sethdcprootkey \
    sample_otp_getcustomerkey \
    sample_otp_setstbprivatedata \
    sample_otp_gethdcprootkeylockflag \
    sample_otp_getstbprivatedata \
    sample_otp_getstbrootkeylockflag \
    sample_otp_lockhdcprootkey \
    sample_otp_lockstbrootkey \
    sample_otp_lockidword \
    sample_otp_getstbtarootkeylockflag \
    sample_otp_setstbtarootkey \
    sample_otp_setsosmsid \
    sample_otp_getscsstatus \
    sample_otp_setscsenable  \
    sample_otp_set_fuse   \
    sample_otp_get_fuse   \
    sample_otp_longdata


DEPEND_LIBS := $(HI_LIBS)

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
	ifeq ($(CFG_HI_ADVCA_TYPE),NAGRA)
		CFLAGS += -DHI_ADVCA_TYPE_NAGRA
	endif
endif

include $(SAMPLE_DIR)/hi_sample_rules.mak

