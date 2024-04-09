/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_sm4.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_symc.h"

#ifdef SOFT_SM4_SUPPORT

/************************ Internal Structure Definition **********************/
/** \addtogroup      sm3 */
/** @{*/  /** <!-- [sm3]*/

static const u32 FK[4] =
{
    0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc
};

static const u32 CK[] =
{
    0x00070e15, 0x1c232a31, 0x383f464d, 0x545b6269,
    0x70777e85, 0x8c939aa1, 0xa8afb6bd, 0xc4cbd2d9,
    0xe0e7eef5, 0xfc030a11, 0x181f262d, 0x343b4249,
    0x50575e65, 0x6c737a81, 0x888f969d, 0xa4abb2b9,
    0xc0c7ced5, 0xdce3eaf1, 0xf8ff060d, 0x141b2229,
    0x30373e45, 0x4c535a61, 0x686f767d, 0x848b9299,
    0xa0a7aeb5, 0xbcc3cad1, 0xd8dfe6ed, 0xf4fb0209,
    0x10171e25, 0x2c333a41, 0x484f565d, 0x646b7279
};

static const u32 Sbox[16][16] =
{
    {0xd6, 0x90, 0xe9, 0xfe, 0xcc, 0xe1, 0x3d, 0xb7, 0x16, 0xb6, 0x14, 0xc2, 0x28, 0xfb, 0x2c, 0x05},
    {0x2b, 0x67, 0x9a, 0x76, 0x2a, 0xbe, 0x04, 0xc3, 0xaa, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99},
    {0x9c, 0x42, 0x50, 0xf4, 0x91, 0xef, 0x98, 0x7a, 0x33, 0x54, 0x0b, 0x43, 0xed, 0xcf, 0xac, 0x62},
    {0xe4, 0xb3, 0x1c, 0xa9, 0xc9, 0x08, 0xe8, 0x95, 0x80, 0xdf, 0x94, 0xfa, 0x75, 0x8f, 0x3f, 0xa6},
    {0x47, 0x07, 0xa7, 0xfc, 0xf3, 0x73, 0x17, 0xba, 0x83, 0x59, 0x3c, 0x19, 0xe6, 0x85, 0x4f, 0xa8},
    {0x68, 0x6b, 0x81, 0xb2, 0x71, 0x64, 0xda, 0x8b, 0xf8, 0xeb, 0x0f, 0x4b, 0x70, 0x56, 0x9d, 0x35},
    {0x1e, 0x24, 0x0e, 0x5e, 0x63, 0x58, 0xd1, 0xa2, 0x25, 0x22, 0x7c, 0x3b, 0x01, 0x21, 0x78, 0x87},
    {0xd4, 0x00, 0x46, 0x57, 0x9f, 0xd3, 0x27, 0x52, 0x4c, 0x36, 0x02, 0xe7, 0xa0, 0xc4, 0xc8, 0x9e},
    {0xea, 0xbf, 0x8a, 0xd2, 0x40, 0xc7, 0x38, 0xb5, 0xa3, 0xf7, 0xf2, 0xce, 0xf9, 0x61, 0x15, 0xa1},
    {0xe0, 0xae, 0x5d, 0xa4, 0x9b, 0x34, 0x1a, 0x55, 0xad, 0x93, 0x32, 0x30, 0xf5, 0x8c, 0xb1, 0xe3},
    {0x1d, 0xf6, 0xe2, 0x2e, 0x82, 0x66, 0xca, 0x60, 0xc0, 0x29, 0x23, 0xab, 0x0d, 0x53, 0x4e, 0x6f},
    {0xd5, 0xdb, 0x37, 0x45, 0xde, 0xfd, 0x8e, 0x2f, 0x03, 0xff, 0x6a, 0x72, 0x6d, 0x6c, 0x5b, 0x51},
    {0x8d, 0x1b, 0xaf, 0x92, 0xbb, 0xdd, 0xbc, 0x7f, 0x11, 0xd9, 0x5c, 0x41, 0x1f, 0x10, 0x5a, 0xd8},
    {0x0a, 0xc1, 0x31, 0x88, 0xa5, 0xcd, 0x7b, 0xbd, 0x2d, 0x74, 0xd0, 0x12, 0xb8, 0xe5, 0xb4, 0xb0},
    {0x89, 0x69, 0x97, 0x4a, 0x0c, 0x96, 0x77, 0x7e, 0x65, 0xb9, 0xf1, 0x09, 0xc5, 0x6e, 0xc6, 0x84},
    {0x18, 0xf0, 0x7d, 0xec, 0x3a, 0xdc, 0x4d, 0x20, 0x79, 0xee, 0x5f, 0x3e, 0xd7, 0xcb, 0x39, 0x48}
};

#define GETU32(pt) (((u32)(pt)[0] <<24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] << 8) ^ ((u32)(pt)[3]))
#define PUTU32(ct, st) {(ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >> 8); (ct)[3] = (u8)(st);}

#define SM4_BLOCK_SIZE  16
#define KEY_EXT         0
#define CIPHER          1

typedef struct tagSM1_KEY_S {
    u32 rd_key[36];
} SM4_KEY_S;

typedef union {
    u32  i; //i = {c[3], c[2], c[1], c[0]}
    u8 c[4];
} IS4;

typedef union {
    u32 i; //i = {b[31] ... b[0]}
    char         b[32];
} IS32;

typedef struct
{
    u8  key[SM4_KEY_SIZE];      /*!<  sm4 even round keys, default */
    u32 klen;                   /*!<  symc key length */
    u8  iv[AES_IV_SIZE];
    symc_mode mode;
}
ext_sm4_context;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      sm4 */
/** @{*/  /** <!-- [sm4]*/

/* Sbox */
u32 Mix_R(const u32 data_in, const int type)
{
    IS4 temp;
    u32 rep_rsl = 0;
    u8  sbox_tmp[4] = {0};
    u8  sbox_c = 0;
    u8  sbox_r = 0;
    int j;

    for (j = 0; j < 4; j++)
    {
        sbox_tmp[j] = 0;
        sbox_r = ((data_in << (j * 8)) >> 28);
        sbox_c = ((data_in << (j * 8 + 4)) >> 28);
        sbox_tmp[j] = Sbox[sbox_r][sbox_c];
    }
    temp.c[3] = sbox_tmp[0];
    temp.c[2] = sbox_tmp[1];
    temp.c[1] = sbox_tmp[2];
    temp.c[0] = sbox_tmp[3];

    //linearity replace
    if (type == KEY_EXT)
    {
        rep_rsl = temp.i
                  ^ ((temp.i << 13) + ((temp.i >> 19) & 0x00001fff))
                  ^ ((temp.i << 23) + ((temp.i >>  9) & 0x007fffff));
    }
    else
    {
        rep_rsl = temp.i
                  ^ ((temp.i <<  2) + ((temp.i >> 30) & 0x00000003))
                  ^ ((temp.i << 10) + ((temp.i >> 22) & 0x000003ff))
                  ^ ((temp.i << 18) + ((temp.i >> 14) & 0x0003ffff))
                  ^ ((temp.i << 24) + ((temp.i >>  8) & 0x00ffffff));
    }

    return rep_rsl;
}

/* Set key */
void sm4_set_encrypt_key(const u8 *userKey, const int bits, SM4_KEY_S *key)
{
    int i = 0;
    u32 k_temp[4] = {0};
    u32 K[36] = {0};
    u32 temp = 0;

    k_temp[0] = GETU32(userKey);
    k_temp[1] = GETU32(userKey + 4);
    k_temp[2] = GETU32(userKey + 8);
    k_temp[3] = GETU32(userKey + 12);

    for (i = 0; i < 4; i++)
    {
        K[i] = k_temp[i] ^ FK[i];
    }
    i = 0;
    while (1)
    {
        temp = K[i + 1] ^ K[i + 2] ^ K[i + 3] ^ CK[i];
        K[i + 4] = K[i] ^ Mix_R(temp, KEY_EXT);
        key->rd_key[i] = K[i + 4];

        if (++i == 32)
        {
            return;
        }
    }

    return;
}

/* SM4 Encrypt */
void sm4_encrypt(const u8 *in, u8 *out, const SM4_KEY_S *key)
{
    u32 s[36] = {0};
    u32 temp = 0;
    int i;

    s[0] = GETU32(in);
    s[1] = GETU32(in + 4);
    s[2] = GETU32(in + 8);
    s[3] = GETU32(in + 12);

    for (i = 0; i < 32; i++)
    {
        temp = s[i + 1] ^ s[i + 2] ^ s[i + 3] ^ key->rd_key[i];
        s[i + 4] = s[i] ^ Mix_R(temp, CIPHER);
    }
    PUTU32(out     , s[35]);
    PUTU32(out +  4, s[34]);
    PUTU32(out +  8, s[33]);
    PUTU32(out + 12, s[32]);

    return;
}

/* SM4 Decrypt */
void sm4_decrypt(const u8 *in, u8 *out, const SM4_KEY_S *key)
{
    u32 s[36] = {0};
    u32 temp = 0;
    int i;

    s[0] = GETU32(in);
    s[1] = GETU32(in + 4);
    s[2] = GETU32(in + 8);
    s[3] = GETU32(in + 12);

    for (i = 0; i < 32; i++)
    {
        temp = s[i + 1] ^ s[i + 2] ^ s[i + 3] ^ key->rd_key[31 - i];
        s[i + 4] = s[i] ^ Mix_R(temp, CIPHER);
    }
    PUTU32(out     , s[35]);
    PUTU32(out +  4, s[34]);
    PUTU32(out +  8, s[33]);
    PUTU32(out + 12, s[32]);

    return;
}

/* SM4 ECB Crypt */
void sm4_ecb_crypt(const u8 *in, u8 *out, const SM4_KEY_S *key, const int dec)
{
    if (SYMC_OPERATION_ENCRYPT == dec)
    {
        sm4_encrypt(in, out, key);
    }
    else
    {
        sm4_decrypt(in, out, key);
    }
    return;
}

/* SM4 CBC Crypt */
void sm4_cbc_crypt(const u8 *in, u8 *out, const u32 length, const SM4_KEY_S *key, u8 *ivec, const int dec)
{
    u32 n = 0;
    u32 len = length;
    u8 tmp[SM4_BLOCK_SIZE] = {0};

    if (SYMC_OPERATION_ENCRYPT == dec)
    {
        while (len >= SM4_BLOCK_SIZE)
        {
            for (n = 0; n < SM4_BLOCK_SIZE; ++n)
            {
                tmp[n] = in[n] ^ ivec[n];
            }

            sm4_encrypt(tmp, out, key);

            crypto_memcpy((void *)ivec, SM4_BLOCK_SIZE, out, SM4_BLOCK_SIZE);
            len -= SM4_BLOCK_SIZE;
            in  += SM4_BLOCK_SIZE;
            out += SM4_BLOCK_SIZE;
        }
    }
    else
    {
        while (len >= SM4_BLOCK_SIZE)
        {
            crypto_memcpy(tmp, sizeof(tmp), in, SM4_BLOCK_SIZE);
            sm4_decrypt(tmp, out, key);
            for (n = 0; n < SM4_BLOCK_SIZE; ++n)
            {
                out[n] ^= ivec[n];
            }
            crypto_memcpy((void *)ivec, SM4_BLOCK_SIZE, tmp, sizeof(tmp));
            len -= SM4_BLOCK_SIZE;
            in  += SM4_BLOCK_SIZE;
            out += SM4_BLOCK_SIZE;
        }
    }

    return;
}

/* increment counter (128bit int) by 2^64 */
static void sm4_ctr128_inc(u8 *counter)
{
    s32 i;

    for (i = 15; i >= 0; i--)
    {
        counter[i]++;
        if (counter[i] != 0)
        {
            return;
        }
    }
    return;
}

/* SM4 CTR Crypt, CTR mode is big-endian. The rest of SM4 code is endian-neutral */
void sm4_ctr128_crypt(const u8 *in, u8 *out, int length, const SM4_KEY_S *key, u8 counter[SM4_BLOCK_SIZE], u8 ecount_buf[SM4_BLOCK_SIZE], int *num)
{
    int n = 0;
    int l = 0;
    l = length;

    n = *num;
    while (l--)
    {
        if (n == 0)
        {
            sm4_encrypt(counter, ecount_buf, key);
            sm4_ctr128_inc(counter);
        }
        *(out++) = *(in++) ^ ecount_buf[n];
        n = (n + 1) % SM4_BLOCK_SIZE;
    }
    *num = n;

    return;
}

/* SM4 ECB RM */
void sm4_ecb_rm(const u8 *data_in, u8 *data_out, int data_len, const u8 *key, int bit, u32 decrypt)
{
    SM4_KEY_S ctx;

    sm4_set_encrypt_key(key, bit, &ctx);

    while (data_len >= 16)
    {
        sm4_ecb_crypt(data_in, data_out, &ctx, decrypt);
        data_len = data_len - 16;
        data_in  = data_in + 16;
        data_out = data_out + 16;
    }

    return;
}

/* SM4 CBC RM */
void sm4_cbc_rm(const u8 *data_in, u8 *data_out, int data_len,
                        const u8 *key, int bit, u32 decrypt,
                        u8 *iv)
{
    int left_len;
    int valid_data_len;
    SM4_KEY_S ctx;

    sm4_set_encrypt_key(key, bit, &ctx);

    left_len = data_len % SM4_BLOCK_SIZE;
    valid_data_len = data_len - left_len;
    sm4_cbc_crypt(data_in, data_out, valid_data_len, &ctx, iv, decrypt);

    return;
}

/* SM4 CTR RM */
void sm4_ctr_rm(const u8 *data_in, u8 *data_out, int data_len,
                        const u8 *key, int bit, u32 decrypt,
                        const u8 *iv)
{
    int num = 0;
    u32 valid_data_len = 0;
    u8 encrypt_cnt[16] = {0};
    SM4_KEY_S ctx;

    /* The SM4_ctr128_crypt request:
     * The extra state information to record how much of the
     * 128bit block we have used is contained in *num, and the
     * encrypted counter is kept in ecount_buf. Both *num and
     * ecount_buf must be initialized with zeros before the first
     * called to SM4_ctr128_crypt().
     */
    valid_data_len = data_len;

    sm4_set_encrypt_key(key, bit, &ctx);
    sm4_ctr128_crypt(data_in, data_out, valid_data_len, &ctx, (u8*)iv, encrypt_cnt, &num);

    return;
}

void * ext_sm4_create(u32 hard_chn)
{
    ext_sm4_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = crypto_malloc(sizeof(ext_sm4_context));
    if (HI_NULL == ctx)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_NULL;
    }

    HI_LOG_FuncExit();

    return ctx;
}

s32 ext_sm4_destory(void *ctx)
{
    HI_LOG_FuncEnter();

    if (HI_NULL != ctx)
    {
        crypto_free(ctx);
        ctx = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void ext_sm4_setmode(void *ctx, symc_alg alg, symc_mode mode, symc_width width)
{
    ext_sm4_context *symc = ctx;

    HI_LOG_FuncEnter();

    if (HI_NULL == symc)
    {
        HI_LOG_ERROR("ctx is null\n");
        return;
    }

    if (SYMC_DAT_WIDTH_128 != width)
    {
        HI_LOG_ERROR("Invalid width: 0x%x\n", width);
        return;
    }

    switch(mode)
    {
    case SYMC_MODE_ECB:
        symc->mode = SYMC_MODE_ECB;
        break;
    case SYMC_MODE_CBC:
        symc->mode = SYMC_MODE_CBC;
        break;
    case SYMC_MODE_CTR:
        symc->mode = SYMC_MODE_CTR;
        break;
    default:
        HI_LOG_ERROR("unsupport mode %d\n", mode);
        return;
    }

    HI_LOG_FuncExit();
    return;
}

s32 ext_sm4_setiv(void *ctx, const u8 *iv, u32 ivlen, u32 usage)
{
    ext_sm4_context *symc = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == iv);
    HI_LOG_CHECK_PARAM(AES_IV_SIZE != ivlen);

    crypto_memcpy(symc->iv, AES_IV_SIZE, iv, ivlen);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void ext_sm4_getiv(void *ctx, u8 *iv, u32 *ivlen)
{
    ext_sm4_context *symc = ctx;

    HI_LOG_FuncEnter();

    if ((HI_NULL == symc) || (HI_NULL == iv) || (HI_NULL == ivlen))
    {
        return;
    }

    crypto_memcpy(iv, AES_IV_SIZE, symc->iv, AES_IV_SIZE);
    *ivlen = AES_IV_SIZE;

    HI_LOG_FuncExit();

    return;
}

s32 ext_sm4_setkey(void *ctx, const u8 *fkey, const u8 *skey, u32 *hisi_klen)
{
    u32 klen = 0;
    ext_sm4_context *symc = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == fkey);
    HI_LOG_CHECK_PARAM(HI_NULL == hisi_klen);

    switch(*hisi_klen)
    {
        case CRYP_CIPHER_KEY_AES_128BIT:
            klen = AES_KEY_128BIT;
            break;
        default:
            HI_LOG_ERROR("Invalid aes key len: 0x%x\n", klen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
    }
    HI_LOG_INFO("key len %d, type %d\n", klen, hisi_klen);

    crypto_memcpy(symc->key, SYMC_KEY_SIZE, fkey, klen);
    symc->klen = klen;
    *hisi_klen = klen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_sm4_crypto(void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last)
{
    ext_sm4_context *symc = ctx;
    crypto_mem mem_in, mem_out;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == length);
    HI_LOG_CHECK_PARAM(HI_NULL == input);
    HI_LOG_CHECK_PARAM(HI_NULL == output);
    HI_LOG_CHECK_PARAM(HI_NULL == usage_list);
    HI_LOG_CHECK_PARAM(0x01 != pkg_num);

    crypto_memset(&mem_in, sizeof(mem_in), 0, sizeof(mem_in));
    crypto_memset(&mem_out, sizeof(mem_out), 0, sizeof(mem_out));

    ret = crypto_mem_open(&mem_in, input[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of input failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        goto error0;
    }

    ret = crypto_mem_open(&mem_out, output[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of output failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        goto error1;
    }

    switch(symc->mode)
    {
        case SYMC_MODE_ECB:
        {
            sm4_ecb_rm(crypto_mem_virt(&mem_in), crypto_mem_virt(&mem_out),
                length[0], symc->key, symc->klen, operation);
            break;
        }
        case SYMC_MODE_CBC:
        {
            sm4_cbc_rm(crypto_mem_virt(&mem_in), crypto_mem_virt(&mem_out),
                length[0], symc->key, symc->klen, operation, symc->iv);
            break;
        }
        case SYMC_MODE_CTR:
        {
            sm4_ctr_rm(crypto_mem_virt(&mem_in), crypto_mem_virt(&mem_out),
                length[0], symc->key, symc->klen, operation, symc->iv);
            break;
        }
        default:
        {
            HI_PRINT("Err, Invalid mode 0x%x\n", symc->mode);
            ret = HI_ERR_CIPHER_FAILED_MEM;
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        }
    }

    HI_LOG_FuncExit();

    crypto_mem_close(&mem_out);
error1:
    crypto_mem_close(&mem_in);
error0:

    return ret;
}

#endif
/** @}*/  /** <!-- ==== API Code end ====*/
