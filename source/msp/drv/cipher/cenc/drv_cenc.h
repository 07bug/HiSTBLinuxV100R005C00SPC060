/******************************************************************************
 *
 * Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_cenc.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-03-25
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __TEE_CENC_H__
#define __TEE_CENC_H__

#include "hi_unf_cipher.h"

#define CENC_ODDKEY_SUPPORT                 (0x80000000)
#define CENC_KEY_SIZE                       16
#define CENC_IV_SIZE                        16

s32 cenc_decrypt(u32 id,
                u8 *key,
                u8 *iv,
                u32 oddkey,
                u32 inputphy,
                u32 outputphy,
                u32 bytelength,
                u32 firstoffset,
                void *subsample,
                u32 number);

#endif /* __DRV_CIPHER_INTF_H__ */
