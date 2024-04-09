/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_sm2.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_sm2.h"

/************************* Internal Structure Definition *********************/
/** \addtogroup      sm2 */
/** @{*/  /** <!-- [sm2]*/

/* max length of SM2 ID */
#define SM2_ID_MAX_LEN          0x1FFF

/* SM2 PC of uncompress */
#define SM2_PC_UNCOMPRESS       0x04

/* SM2 encrypt try count */
#define SM2_ENCRYPT_TRY_CNT     10

#define BYTE_BITS               8

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      sm2 */
/** @{*/  /** <!-- [kapi]*/

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_sm2_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_sm2_init, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief   Kapi Deinitialize.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_deinit(void)
{
    HI_LOG_FuncEnter();

    cryp_sm2_deinit();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 sm2_kdf(u32 x[SM2_LEN_IN_WROD], u32 y[SM2_LEN_IN_WROD], u8* k, u32 klen)
{
    s32 ret = HI_FAILURE;
    u32 sm3id = 0;
    u32 u32ct = 0;
    u8 h[SM2_LEN_IN_BYTE];
    u32 i;
    u32 block = 0;
    u32 hashlen = 0;

    HI_LOG_FuncEnter();

    if (0 == klen)
    {
        return HI_SUCCESS;
    }

    crypto_memset(h, sizeof(h), 0, SM2_LEN_IN_BYTE);
    block = (klen + SM2_LEN_IN_BYTE - 1) / SM2_LEN_IN_BYTE;

    for (i=0; i<block; i++)
    {
        u32ct = CPU_TO_BE32(i + 1);

        /* H = SM3(X || Y || CT)*/
        CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)x, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)y, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)&u32ct, sizeof(u32ct), HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_finish(sm3id, h, &hashlen));
        if (i == (block - 1))
        {
            crypto_memcpy(k+i*SM2_LEN_IN_BYTE, SM2_LEN_IN_BYTE,
                h, klen - i * SM2_LEN_IN_BYTE);
        }
        else
        {
            crypto_memcpy(k+i*SM2_LEN_IN_BYTE, SM2_LEN_IN_BYTE, h, sizeof(h));
        }
    }

    /*check k != 0*/
    for (i=0; i<klen; i++)
    {
        if (k[i] != 0)
        {
            break;
        }
    }
    if (i >= klen)
    {
        HI_LOG_ERROR("Invalid key.\n");
        return HI_ERR_CIPHER_ILLEGAL_KEY;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:

    return ret;
}

s32 kapi_sm2_sign(u32 d[SM2_LEN_IN_WROD],
                  u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                  u8 *id, u16 idlen,
                  u8 *msg, u32 msglen, hash_chunk_src src,
                  u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 sm3id = 0;
    u8 entla[2];
    u8 ZA[SM2_LEN_IN_BYTE];
    u32 e[SM2_LEN_IN_WROD];
    u32 hashlen = 0;
    sm2_func *func = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(SM2_ID_MAX_LEN < idlen);
    HI_LOG_CHECK_PARAM(HI_NULL == d);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);
    HI_LOG_CHECK_PARAM(HI_NULL == id);
    HI_LOG_CHECK_PARAM(HI_NULL == msg);
    HI_LOG_CHECK_PARAM(HI_NULL == r);
    HI_LOG_CHECK_PARAM(HI_NULL == s);

    func = cryp_get_sm2_op();
    HI_LOG_CHECK_PARAM(HI_NULL == func);
    HI_LOG_CHECK_PARAM(HI_NULL == func->sign);

    /* msg is the result of sm3 ? */
    if ( (SM3_RESULT_SIZE == idlen) && (0x00 == msglen))
    {
        /* id is the sm3 result when msglen = 0 and idlen = 32*/
        crypto_memcpy(e, sizeof(e), id, SM3_RESULT_SIZE);
    }
    else
    {
        /* compute e */
        crypto_memset(ZA, sizeof(ZA), 0, SM2_LEN_IN_BYTE);
        crypto_memset(e, sizeof(e), 0, SM2_LEN_IN_BYTE);

        entla[0] = (u8)((idlen * BYTE_BITS) >> BYTE_BITS);
        entla[1] = (u8)((idlen * BYTE_BITS));

        /*ZA=H256(ENTLA||IDA||a||b||xG||yG||xA||yA)*/
        /*SM2 and sm3 use two different lock, so have to use SM3 Instead of MPI*/
        CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
        CHECK_EXIT(kapi_hash_update(sm3id, entla,  sizeof(entla), HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, id, idlen, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2a, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2b, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2Gx, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2Gy, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)px, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)py, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_finish(sm3id, ZA, &hashlen));
    //    HI_PRINT_HEX("ZA", ZA, SM2_LEN_IN_BYTE);

        /*e=H256(ZA||M)*/
        CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
        CHECK_EXIT(kapi_hash_update(sm3id, ZA, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, msg, msglen, src));
        CHECK_EXIT(kapi_hash_finish(sm3id, (u8*)e, &hashlen));

        HI_LOG_DEBUG("msg 0x%p, msglen %d\n", msg, msglen);
    //    HI_PRINT_HEX("e", e, SM2_LEN_IN_BYTE);
    }

    /***************************************
      1. generate a randnum k, k?¨º[1,n-1],
      2. (x1,y1)=[k]G,
      3. r=(e+x1)mod n, if r=0 or r+k=n, return step 1
      4. s=((1+dA)^-1 ?¡è(k-r?¡èdA))mod n
    ****************************************/
    ret = func->sign(e, d, r, s);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(func->sign, ret);
        return ret;
    }

 exit__:
    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_sm2_verify(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                    u8 *id, u16 idlen, u8 *msg, u32 msglen, hash_chunk_src src,
                    u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 sm3id;
    u8 entla[2] = {0};
    u8 ZA[SM2_LEN_IN_BYTE];
    u32 e[SM2_LEN_IN_WROD];
    u32 hashlen = 0;
    sm2_func *func = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(SM2_ID_MAX_LEN < idlen);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);
    HI_LOG_CHECK_PARAM(HI_NULL == id);
    HI_LOG_CHECK_PARAM(HI_NULL == msg);
    HI_LOG_CHECK_PARAM(HI_NULL == r);
    HI_LOG_CHECK_PARAM(HI_NULL == s);

    func = cryp_get_sm2_op();
    HI_LOG_CHECK_PARAM(HI_NULL == func);
    HI_LOG_CHECK_PARAM(HI_NULL == func->verify);

    /* msg is the result of sm3 ? */
    if ( (SM3_RESULT_SIZE == idlen) && (0x00 == msglen))
    {
        /* id is the sm3 result when msglen = 0 and idlen = 32*/
        crypto_memcpy(e, sizeof(e), id, idlen);
    }
    else
    {
        /* compute e */
        crypto_memset(entla, sizeof(entla), 0, sizeof(entla));
        crypto_memset(ZA, sizeof(ZA), 0, sizeof(ZA));
        crypto_memset(e, sizeof(e), 0, sizeof(e));

        entla[0] = (u8)((idlen * BYTE_BITS) >> BYTE_BITS);
        entla[1] = (u8)((idlen * BYTE_BITS));

        /*ZA=H256(ENTLA||IDA||a||b||xG||yG||xA||yA)*/
        CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
        CHECK_EXIT(kapi_hash_update(sm3id, entla, sizeof(entla), HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, id, idlen, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2a, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2b, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2Gx, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)sm2Gy, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)px, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, (u8*)py, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_finish(sm3id, ZA, &hashlen));

    //    HI_PRINT_HEX("ZA", ZA, SM2_LEN_IN_BYTE);

        /*e=H256(ZA||M)*/
        CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
        CHECK_EXIT(kapi_hash_update(sm3id, ZA, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
        CHECK_EXIT(kapi_hash_update(sm3id, msg, msglen, src));
        CHECK_EXIT(kapi_hash_finish(sm3id, (u8*)e, &hashlen));

        HI_LOG_DEBUG("msg 0x%p, msglen %d\n", msg, msglen);
    //    HI_PRINT_HEX("e", e, SM2_LEN_IN_BYTE);
    }

    /***************************************
      1. t=(r+s)mod n, if t==0, return fail
      2. (x1,y1)=[s]G+tP,
      3. r=(e+x1)mod n, if r==R, return pass
    ****************************************/
    ret = func->verify(e, px, py, r, s);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(func->verify, ret);
        return ret;
    }

 exit__:
    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u8 *msg, u32 msglen, u8 *enc, u32 *enclen)
{
    s32 ret = HI_FAILURE;
    u32 sm3id = 0;
    u32 u32Index = 0;
    u32 i;
    u32 c1x [ SM2_LEN_IN_WROD ];
    u32 c1y [ SM2_LEN_IN_WROD ];
    u32 x2 [ SM2_LEN_IN_WROD ];
    u32 y2 [ SM2_LEN_IN_WROD ];
    u32 hashlen = 0;
    u32 trycnt = 0;
    sm2_func *func = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);
    HI_LOG_CHECK_PARAM(HI_NULL == msg);
    HI_LOG_CHECK_PARAM(HI_NULL == enc);
    HI_LOG_CHECK_PARAM(HI_NULL == enclen);

    func = cryp_get_sm2_op();
    HI_LOG_CHECK_PARAM(HI_NULL == func);
    HI_LOG_CHECK_PARAM(HI_NULL == func->encrypt);

    /* C1 = k * G */
    while(SM2_ENCRYPT_TRY_CNT > trycnt++)
    {
        /* C1(x, y) = k * G(x, y), XY = k * P(x, y)*/
        ret = func->encrypt(px, py, c1x, c1y, x2, y2);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(func->encrypt, ret);
            return ret;
        }
        //HI_PRINT_HEX("C1x", (u8*)c1x, SM2_LEN_IN_BYTE);
        //HI_PRINT_HEX("C1y", (u8*)c1y, SM2_LEN_IN_BYTE);
        //HI_PRINT_HEX("X2", (u8*)x2, SM2_LEN_IN_BYTE);
        //HI_PRINT_HEX("Y2", (u8*)y2, SM2_LEN_IN_BYTE);

        /* the key consist of PC||x1||y1, PC = 4 when uncompress*/
        u32Index = 0;
        crypto_memcpy(&enc[u32Index], SM2_LEN_IN_BYTE, c1x, SM2_LEN_IN_BYTE);
        u32Index+=SM2_LEN_IN_BYTE;
        crypto_memcpy(&enc[u32Index], SM2_LEN_IN_BYTE, c1y, SM2_LEN_IN_BYTE);
        u32Index+=SM2_LEN_IN_BYTE;
//        HI_PRINT_HEX("C1", &enc[0], SM2_LEN_IN_BYTE*2);

        /*gen mask for msg encrypt*/
        ret = sm2_kdf(x2, y2, &enc[u32Index], msglen);
        if (HI_SUCCESS == ret)
        {
            break;
        }
    }

    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("sm2 encrypt failed\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_ENCRYPT);
        ret =  HI_ERR_CIPHER_FAILED_ENCRYPT;
        goto exit__;
    }

    /*C2=M ^ k*/
    for (i=0; i<msglen; i++)
    {
        enc[u32Index++] ^= msg[i];
    }
//    HI_PRINT_HEX("C2", &enc[SM2_LEN_IN_BYTE*2], msglen);

    /*C3 =Hash(x2||M||y2)*/
    CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
    CHECK_EXIT(kapi_hash_update(sm3id, (u8*)x2, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_update(sm3id, msg, msglen, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_update(sm3id, (u8*)y2, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_finish(sm3id, &enc[u32Index], &hashlen));
    u32Index+=SM2_LEN_IN_BYTE;
//    HI_PRINT_HEX("C3", &enc[SM2_LEN_IN_BYTE*2+1+msglen], SM2_LEN_IN_BYTE);

    *enclen = u32Index;

 exit__:
    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_sm2_decrypt(u32 d[SM2_LEN_IN_WROD], u8 *enc,
                     u32 enclen, u8 *msg, u32 *msglen)
{
    s32 ret = HI_FAILURE;
    u8 h[SM2_LEN_IN_BYTE];
    u32 sm3id = 0;
    u32 u32Index = 0;
    u32 u32Mlen = 0;
    u32 c1x [ SM2_LEN_IN_WROD ];
    u32 c1y [ SM2_LEN_IN_WROD ];
    u32 x2 [ SM2_LEN_IN_WROD ];
    u32 y2 [ SM2_LEN_IN_WROD ];
    u32 hashlen = 0;
    u32 i;
    sm2_func *func = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == d);
    HI_LOG_CHECK_PARAM(HI_NULL == enc);
    HI_LOG_CHECK_PARAM(HI_NULL == msg);
    HI_LOG_CHECK_PARAM(HI_NULL == msglen);
    HI_LOG_CHECK_PARAM(SM2_LEN_IN_BYTE*3 > enclen);

    func = cryp_get_sm2_op();
    HI_LOG_CHECK_PARAM(HI_NULL == func);
    HI_LOG_CHECK_PARAM(HI_NULL == func->decrypt);

    crypto_memset(h, sizeof(h), 0, SM2_LEN_IN_BYTE);
    u32Index = 0;
    u32Mlen = enclen - (SM2_LEN_IN_BYTE*2) - SM2_LEN_IN_BYTE; //C2 = C - C1 -C3

    /* C1 */
    crypto_memcpy(c1x, sizeof(c1x), &enc[u32Index], SM2_LEN_IN_BYTE);
    u32Index+=SM2_LEN_IN_BYTE;
    crypto_memcpy(c1y, sizeof(c1y), &enc[u32Index], SM2_LEN_IN_BYTE);
    u32Index+=SM2_LEN_IN_BYTE;

    /*Compute M(x, y) = C1(x, y) * d*/
    ret = func->decrypt(d, c1x, c1y, x2, y2);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(func->decrypt, ret);
        return ret;
    }

//    HI_PRINT_HEX("X2", (u8*)x2, SM2_LEN_IN_BYTE);
//    HI_PRINT_HEX("Y2", (u8*)y2, SM2_LEN_IN_BYTE);

    /*Compute mask for msg*/
    ret = sm2_kdf(x2, y2, msg, u32Mlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(sm2_kdf, ret);
        return ret;
    }
    //    HI_PRINT_HEX("kdf", msg, u32Mlen);

    /*Get clear msg from C2*/
    for (i=0; i<u32Mlen; i++)
    {
        msg[i] ^= enc[u32Index++];
    }
//    HI_PRINT_HEX("msg", msg, u32Mlen);

    /*Check C3*/
    CHECK_EXIT(kapi_hash_start(&sm3id, CRYP_CIPHER_HASH_TYPE_SM3, HI_NULL, 0));
    CHECK_EXIT(kapi_hash_update(sm3id, (u8*)x2, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_update(sm3id, msg, u32Mlen, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_update(sm3id, (u8*)y2, SM2_LEN_IN_BYTE, HASH_CHUNCK_SRC_LOCAL));
    CHECK_EXIT(kapi_hash_finish(sm3id, h, &hashlen));

//    HI_PRINT_HEX("H", h, SM2_LEN_IN_BYTE);

    if (memcmp(&enc[u32Index], h, SM2_LEN_IN_BYTE)!=0)
    {
        HI_LOG_ERROR("Err, SM2 decrypt failed, invalid C3\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_DECRYPT);
        ret =  HI_ERR_CIPHER_FAILED_DECRYPT;
        goto exit__;
    }
    u32Index += SM2_LEN_IN_BYTE;

    *msglen = u32Mlen;

 exit__:
    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_sm2_gen_key(u32 d[SM2_LEN_IN_WROD], u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    sm2_func *func = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == d);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);

    func = cryp_get_sm2_op();
    HI_LOG_CHECK_PARAM(HI_NULL == func);
    HI_LOG_CHECK_PARAM(HI_NULL == func->genkey);

    /* d is randnum, P(x,y) =d * G(x,y) */
    ret = func->genkey(d, px, py);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(func->genkey, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/
