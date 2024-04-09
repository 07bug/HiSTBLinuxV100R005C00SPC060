SRCS  += $(patsubst %.c,%.o, $(wildcard cipher/*.c))
CFLAGS += -I$(MSP_DIR)/api/cipher
CFLAGS += -DHI_PLATFORM_TYPE_LINUX \
          -DHI_PRODUCT_SHA512_SUPPORT \
          -DHI_PRODUCT_SM2_SUPPORT \
          -DHI_PRODUCT_ECC_SUPPORT \
          -DHI_PRODUCT_DH_SUPPORT  \
          -DHI_PRODUCT_SYMC_CONFIG_EX_SUPPORT \
          -DHI_PRODUCT_AEAD_SUPPORT \
          -DHI_PRODUCT_CENC_SUPPORT