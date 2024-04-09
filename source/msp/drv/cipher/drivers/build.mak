
CIPHER_CFLAGS += -I$(CIPHER_DIR)/drivers/core/include
CIPHER_CFLAGS += -I$(CIPHER_DIR)/drivers/crypto/include
CIPHER_CFLAGS += -I$(CIPHER_DIR)/drivers/extend
CIPHER_CFLAGS += -I$(CIPHER_DIR)/drivers/extend/include

CIPHER_OBJS +=  drivers/core/drv_symc_v100.o          \
                drivers/core/drv_symc_v200.o          \
                drivers/core/drv_hash_v100.o          \
                drivers/core/drv_hash_v200.o          \
                drivers/core/drv_hdcp_v100.o          \
                drivers/core/drv_hdcp_v200.o          \
                drivers/core/drv_ifep_rsa_v100.o      \
                drivers/core/drv_sm2_v100.o           \
                drivers/core/drv_trng_v100.o          \
                drivers/core/drv_trng_v200.o          \
                drivers/core/drv_lib.o

CIPHER_OBJS += drivers/crypto/cryp_symc.o             \
               drivers/crypto/cryp_hash.o             \
               drivers/crypto/cryp_hdcp.o             \
               drivers/crypto/cryp_trng.o             \
               drivers/crypto/cryp_rsa.o              \
               drivers/crypto/cryp_sm2.o

CIPHER_OBJS += drivers/kapi_symc.o                    \
               drivers/kapi_hash.o                    \
               drivers/kapi_rsa.o                     \
               drivers/kapi_hdcp.o                    \
               drivers/kapi_trng.o                    \
               drivers/kapi_sm2.o                     \
               drivers/kapi_dispatch.o

CIPHER_OBJS += drivers/extend/mbedtls/bignum.o        \
               drivers/extend/mbedtls/ecdh.o          \
               drivers/extend/mbedtls/ecdsa.o         \
               drivers/extend/mbedtls/ecp.o           \
               drivers/extend/mbedtls/ecp_curves.o    \
               drivers/extend/mbedtls/md.o            \
               drivers/extend/mbedtls/rsa.o           \
               drivers/extend/mbedtls/sha1.o          \
               drivers/extend/mbedtls/sha256.o        \
               drivers/extend/mbedtls/sha512.o        \
               drivers/extend/mbedtls/aes.o           \
               drivers/extend/mbedtls/aesni.o         \
               drivers/extend/mbedtls/asn1parse.o     \
               drivers/extend/mbedtls/ccm.o           \
               drivers/extend/mbedtls/cipher.o        \
               drivers/extend/mbedtls/cipher_wrap.o   \
               drivers/extend/mbedtls/des.o           \
               drivers/extend/mbedtls/dhm.o           \
               drivers/extend/mbedtls/error.o         \
               drivers/extend/mbedtls/gcm.o           \
               drivers/extend/mbedtls/md_wrap.o       \
               drivers/extend/mbedtls/oid.o           \
               drivers/extend/mbedtls/asn1write.o     \

CIPHER_OBJS += drivers/extend/ext_cmac.o              \
               drivers/extend/ext_aead.o              \
               drivers/extend/ext_hash.o              \
               drivers/extend/ext_symc.o              \
               drivers/extend/ext_ecc.o               \
               drivers/extend/ext_sm2.o               \
               drivers/extend/ext_sm3.o               \
               drivers/extend/ext_sm4.o