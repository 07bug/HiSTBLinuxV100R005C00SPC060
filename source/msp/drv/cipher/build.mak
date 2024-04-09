CIPHER_DIR := $(MSP_DIR)/drv/cipher
CIPHER_CFLAGS += -DHI_PLATFORM_TYPE_LINUX \
                -DHI_PRODUCT_SHA512_SUPPORT \
                -DHI_PRODUCT_SM14_SUPPORT \
                -DHI_PRODUCT_AEAD_SUPPORT \
                -DHI_PRODUCT_DMA_SUPPORT \
                -DHI_PRODUCT_SM2_SUPPORT \
                -DHI_PRODUCT_CENC_SUPPORT \
                -DHI_PRODUCT_ODD_KEY_SUPPORT

include $(CIPHER_DIR)/drivers/build.mak
include $(CIPHER_DIR)/osal/build.mak
include $(CIPHER_DIR)/compat/build.mak

CIPHER_CFLAGS += -I$(CIPHER_DIR)/cenc
$(MOD_NAME)-y  += cenc/drv_cenc.o

EXTRA_CFLAGS  += $(CIPHER_CFLAGS)
$(MOD_NAME)-y += $(CIPHER_OBJS)
