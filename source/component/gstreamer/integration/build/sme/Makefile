ifeq ($(ENV_SME_CFG_PATH),)
include cfg.mk
else
$(info, "ENV_SME_CFG_PATH = $(ENV_SME_CFG_PATH)")
include $(ENV_SME_CFG_PATH)
endif

include core/core.mk
