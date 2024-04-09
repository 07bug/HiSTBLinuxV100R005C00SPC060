/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_CIPHER_IOCTL_H__
#define __DRV_CIPHER_IOCTL_H__

#include "drv_cipher_osal.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define HASH_BLOCK_SIZE            (64)

#define CRYPTO_IOC_NA           0U
#define CRYPTO_IOC_W            1U
#define CRYPTO_IOC_R            2U
#define CRYPTO_IOC_RW           3U

/* Ioctl definitions */
#define CIPHER_NAME "HI_CIPHER"

#define CRYPTO_IOC(dir,type,nr,size) (((dir) << 30)|((size) << 16)|((type) << 8)|((nr) << 0))
#define CRYPTO_IOR(nr,size)    CRYPTO_IOC(CRYPTO_IOC_R, HI_ID_CIPHER,(nr), size)
#define CRYPTO_IOW(nr,size)    CRYPTO_IOC(CRYPTO_IOC_W, HI_ID_CIPHER,(nr), size)
#define CRYPTO_IOWR(nr,size)   CRYPTO_IOC(CRYPTO_IOC_RW, HI_ID_CIPHER,(nr),size)

#define CRYPTO_IOC_DIR(cmd)       (((cmd) >> 30) & 0x03)
#define CRYPTO_IOC_TYPE(cmd)      (((cmd) >> 8) & 0xFF)
#define CRYPTO_IOC_NR(cmd)        (((cmd) >> 0) & 0xFF)
#define CRYPTO_IOC_SIZE(cmd)      (((cmd) >> 16) & 0x3FFF)

#define CRYPTO_CMD_SYMC_CREATEHANDLE      CRYPTO_IOWR(0x00, sizeof(symc_create_t))
#define CRYPTO_CMD_SYMC_DESTROYHANDLE     CRYPTO_IOW (0x01, sizeof(symc_destroy_t))
#define CRYPTO_CMD_SYMC_CONFIGHANDLE      CRYPTO_IOW (0x02, sizeof(symc_config_t))
#define CRYPTO_CMD_SYMC_ENCRYPT           CRYPTO_IOW (0x03, sizeof(symc_encrypt_t))
#define CRYPTO_CMD_SYMC_ENCRYPTMULTI      CRYPTO_IOW (0x04, sizeof(symc_encrypt_multi_t))
#define CRYPTO_CMD_SYMC_CMAC              CRYPTO_IOWR(0x05, sizeof(symc_cmac_t))
#define CRYPTO_CMD_SYMC_GETTAG            CRYPTO_IOWR(0x06, sizeof(aead_tag_t))
#define CRYPTO_CMD_CENC                   CRYPTO_IOW (0x07, sizeof(cenc_info_t))
#define CRYPTO_CMD_HASH_START             CRYPTO_IOWR(0x08, sizeof(hash_start_t))
#define CRYPTO_CMD_HASH_UPDATE            CRYPTO_IOW (0x09, sizeof(hash_update_t))
#define CRYPTO_CMD_HASH_FINISH            CRYPTO_IOWR(0x0a, sizeof(hash_finish_t))
#define CRYPTO_CMD_RSA_ENC                CRYPTO_IOWR(0x0b, sizeof(rsa_info_t))
#define CRYPTO_CMD_RSA_DEC                CRYPTO_IOWR(0x0c, sizeof(rsa_info_t))
#define CRYPTO_CMD_RSA_SIGN               CRYPTO_IOWR(0x0d, sizeof(rsa_info_t))
#define CRYPTO_CMD_RSA_VERIFY             CRYPTO_IOWR(0x0e, sizeof(rsa_info_t))
#define CRYPTO_CMD_RSA_COMPUTE_CRT        CRYPTO_IOWR(0x0f, sizeof(rsa_info_t))
#define CRYPTO_CMD_RSA_GEN_KEY            CRYPTO_IOWR(0x10, sizeof(rsa_info_t))
#define CRYPTO_CMD_HDCP_ENCRYPT           CRYPTO_IOW (0x11, sizeof(hdcp_key_t))
#define CRYPTO_CMD_TRNG                   CRYPTO_IOW (0x12, sizeof(trng_t))
#define CRYPTO_CMD_SM2_SIGN               CRYPTO_IOWR(0x13, sizeof(sm2_sign_t))
#define CRYPTO_CMD_SM2_VERIFY             CRYPTO_IOWR(0x14, sizeof(sm2_verify_t))
#define CRYPTO_CMD_SM2_ENCRYPT            CRYPTO_IOWR(0x15, sizeof(sm2_encrypt_t))
#define CRYPTO_CMD_SM2_DECRYPT            CRYPTO_IOWR(0x16, sizeof(sm2_decrypt_t))
#define CRYPTO_CMD_SM2_GEN_KEY            CRYPTO_IOWR(0x17, sizeof(sm2_key_t))
#define CRYPTO_CMD_ECDH_COMPUTE_KEY       CRYPTO_IOWR(0x18, sizeof(ecc_info_t))
#define CRYPTO_CMD_ECC_GEN_KEY            CRYPTO_IOWR(0x19, sizeof(ecc_info_t))
#define CRYPTO_CMD_ECDSA_SIGN             CRYPTO_IOW (0x1a, sizeof(ecc_info_t))
#define CRYPTO_CMD_ECDSA_VERIFY           CRYPTO_IOW (0x1b, sizeof(ecc_info_t))
#define CRYPTO_CMD_SYMC_GET_CONFIG        CRYPTO_IOWR(0x1c, sizeof(symc_get_config_t))
#define CRYPTO_CMD_CENC_EX                CRYPTO_IOW (0x1d, sizeof(cenc_info_t))
#define CRYPTO_CMD_COUNT                  0x1E

HI_S32 TEE_CIPHER_Ioctl(HI_U32 cmd, HI_VOID *argp);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__*/
