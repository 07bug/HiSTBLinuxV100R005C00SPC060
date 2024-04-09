/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_ecc.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "mbedtls/ecp.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/ecdsa.h"
#include "mbedtls/rsa.h"

#ifdef SOFT_ECC_SUPPORT

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      ecc */
/** @{*/  /** <!-- [ecc]*/

#define RSA_KEY_EXPONENT_VALUE1 (0X3)
#define RSA_KEY_EXPONENT_VALUE2 (0X10001)

/**
* \brief          print a bignum string of  mbedtls*
*/
void mbedtls_mpi_print(const mbedtls_mpi *X, const char *name);

int mbedtls_get_random(void *param, u8 *rand, size_t size);

#define MPI_PRINT(x) mbedtls_mpi_print(x, #x)

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      ecc drivers*/
/** @{*/  /** <!-- [ecc]*/

s32 ext_rsa_compute_crt(cryp_rsa_key *key)
{
    s32 ret = HI_FAILURE;
    mbedtls_mpi E, D, P, Q, DP, DQ, QP, P1, Q1, H;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key->p);
    HI_LOG_CHECK_PARAM(HI_NULL == key->q);
    HI_LOG_CHECK_PARAM(HI_NULL == key->dP);
    HI_LOG_CHECK_PARAM(HI_NULL == key->dQ);
    HI_LOG_CHECK_PARAM(HI_NULL == key->qP);
    HI_LOG_CHECK_PARAM(0 == key->klen);
    HI_LOG_CHECK_PARAM(0 == key->e);

    if((RSA_KEY_BITWIDTH_1024 != key->klen) && (RSA_KEY_BITWIDTH_2048 != key->klen)
        && (RSA_KEY_BITWIDTH_3072 != key->klen) && (RSA_KEY_BITWIDTH_4096 != key->klen))
    {
        HI_LOG_ERROR("RSA compute crt params, bitnum error\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if((RSA_KEY_EXPONENT_VALUE1 != key->e) && (RSA_KEY_EXPONENT_VALUE2 != key->e))
    {
        HI_LOG_ERROR("RSA compute crt params, e error\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    mbedtls_mpi_init(&E);
    mbedtls_mpi_init(&D);
    mbedtls_mpi_init(&P);
    mbedtls_mpi_init(&Q);
    mbedtls_mpi_init(&DP);
    mbedtls_mpi_init(&DQ);
    mbedtls_mpi_init(&QP);
    mbedtls_mpi_init(&P1);
    mbedtls_mpi_init(&Q1);
    mbedtls_mpi_init(&H);

    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&E, key->e));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&P, key->p, key->klen / 2));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q, key->q, key->klen / 2));

    /* D  = E^-1 mod ((P-1)*(Q-1))
     * DP = D mod (P - 1)
     * DQ = D mod (Q - 1)
     * QP = Q^-1 mod P
     */
    MBEDTLS_MPI_CHK(mbedtls_mpi_sub_int(&P1, &P, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_sub_int(&Q1, &Q, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_mul_mpi(&H, &P1, &Q1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_inv_mod(&D , &E, &H ));
    MBEDTLS_MPI_CHK(mbedtls_mpi_mod_mpi(&DP, &D, &P1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_mod_mpi(&DQ, &D, &Q1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_inv_mod(&QP, &Q, &P));

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&DP, key->dP, key->klen / 2));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&DQ, key->dQ, key->klen / 2));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&QP, key->qP, key->klen / 2));

cleanup:

    mbedtls_mpi_free(&E);
    mbedtls_mpi_free(&D);
    mbedtls_mpi_free(&P);
    mbedtls_mpi_free(&Q);
    mbedtls_mpi_free(&DP);
    mbedtls_mpi_free(&DQ);
    mbedtls_mpi_free(&QP);
    mbedtls_mpi_free(&P1);
    mbedtls_mpi_free(&Q1);
    mbedtls_mpi_free(&H);

    HI_LOG_FuncExit();

    return ret;

}

s32 ext_ecdh_compute_key(ecc_param_t *ecc, u8 *d, u8 *px, u8 *py, u8 *sharekey)
{
    s32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi z;
    mbedtls_mpi md;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ecc);
    HI_LOG_CHECK_PARAM(HI_NULL == d);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);
    HI_LOG_CHECK_PARAM(HI_NULL == sharekey);

    HI_LOG_CHECK_PARAM(HI_NULL == ecc->p);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->a);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->b);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gx);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gy);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->n);

    HI_LOG_CHECK_PARAM(0 == ecc->ksize);

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&z);
    mbedtls_mpi_init(&md);

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.P, ecc->p, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.A, ecc->a, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.B, ecc->b, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.N, ecc->n, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.X, ecc->Gx, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.Y, ecc->Gy, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&grp.G.Z, 1));
    grp.pbits = mbedtls_mpi_bitlen(&grp.P);
    grp.nbits = mbedtls_mpi_bitlen(&grp.N);
    grp.h = ecc->h;

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q.X, px, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q.Y, py, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&Q.Z, 1));

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&md, d, ecc->ksize));

    MBEDTLS_MPI_CHK(mbedtls_ecdh_compute_shared(&grp, &z, &Q, &md, HI_NULL, 0));

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&z, sharekey, ecc->ksize));
cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&z);
    mbedtls_mpi_free(&md);

    HI_LOG_FuncExit();

    return(ret);
}

s32 ext_ecc_gen_key(ecc_param_t *ecc, u8 *inkey, u8 *outkey, u8 *px, u8 *py)
{
    s32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ecc);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);

    HI_LOG_CHECK_PARAM(HI_NULL == ecc->p);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->a);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->b);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gx);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gy);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->n);

    HI_LOG_CHECK_PARAM(0 == ecc->ksize);

    if ((HI_NULL == inkey) && (HI_NULL == outkey))
    {
        HI_LOG_ERROR("Invalid param!");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&d);

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.P, ecc->p, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.A, ecc->a, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.B, ecc->b, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.N, ecc->n, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.X, ecc->Gx, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.Y, ecc->Gy, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&grp.G.Z, 1));
    grp.pbits = mbedtls_mpi_bitlen(&grp.P);
    grp.nbits = mbedtls_mpi_bitlen(&grp.N);
    grp.h = ecc->h;

    if (inkey == HI_NULL)
    {
        MBEDTLS_MPI_CHK(mbedtls_ecdh_gen_public(&grp, &d, &Q, mbedtls_get_random, 0));
        MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&d, outkey, ecc->ksize));
    }
    else
    {
        MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&d, inkey, ecc->ksize));
        if ((mbedtls_mpi_cmp_int(&d, 1) < 0) || (mbedtls_mpi_cmp_mpi(&d, &grp.N) >= 0))
        {
             HI_LOG_ERROR("Invalid private key !!!\n");
                goto cleanup;
        }
        MBEDTLS_MPI_CHK(mbedtls_ecp_mul(&grp, &Q, &d, &grp.G, HI_NULL, 0));
    }

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&Q.X, px, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&Q.Y, py, ecc->ksize));

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&d);

    HI_LOG_FuncExit();

    return(ret);
}

s32 ext_ecdsa_sign_hash(ecc_param_t *ecc, u8 *d, u8 *hash, u32 hlen, u8 *r, u8 *s)
{
    s32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_mpi mr;
    mbedtls_mpi ms;
    mbedtls_mpi md;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ecc);
    HI_LOG_CHECK_PARAM(HI_NULL == d);
    HI_LOG_CHECK_PARAM(HI_NULL == hash);
    HI_LOG_CHECK_PARAM(HI_NULL == r);
    HI_LOG_CHECK_PARAM(HI_NULL == s);

    HI_LOG_CHECK_PARAM(HI_NULL == ecc->p);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->a);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->b);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gx);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gy);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->n);

    HI_LOG_CHECK_PARAM(0 == ecc->ksize);

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_mpi_init(&mr);
    mbedtls_mpi_init(&ms);
    mbedtls_mpi_init(&md);

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.P, ecc->p, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.A, ecc->a, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.B, ecc->b, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.N, ecc->n, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.X, ecc->Gx, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.Y, ecc->Gy, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&grp.G.Z, 1));
    grp.pbits = mbedtls_mpi_bitlen(&grp.P);
    grp.nbits = mbedtls_mpi_bitlen(&grp.N);
    grp.h = ecc->h;

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&md, d, ecc->ksize));

    MBEDTLS_MPI_CHK(mbedtls_ecdsa_sign(&grp, &mr, &ms, &md, hash, hlen, mbedtls_get_random, 0));

    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&mr, r, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(&ms, s, ecc->ksize));

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_mpi_free(&mr);
    mbedtls_mpi_free(&ms);
    mbedtls_mpi_free(&md);

    HI_LOG_FuncExit();

    return(ret);
}

s32 ext_ecdsa_verify_hash(ecc_param_t *ecc, u8 *px, u8 *py, u8 *hash, u32 hlen, u8 *r, u8 *s)
{
    s32 ret = HI_FAILURE;
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi mr;
    mbedtls_mpi ms;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ecc);
    HI_LOG_CHECK_PARAM(HI_NULL == px);
    HI_LOG_CHECK_PARAM(HI_NULL == py);
    HI_LOG_CHECK_PARAM(HI_NULL == hash);
    HI_LOG_CHECK_PARAM(HI_NULL == r);
    HI_LOG_CHECK_PARAM(HI_NULL == s);

    HI_LOG_CHECK_PARAM(HI_NULL == ecc->p);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->a);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->b);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gx);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->Gy);
    HI_LOG_CHECK_PARAM(HI_NULL == ecc->n);

    HI_LOG_CHECK_PARAM(0 == ecc->ksize);

    mbedtls_ecp_group_init(&grp);
    mbedtls_mpi_init(&grp.P);
    mbedtls_mpi_init(&grp.A);
    mbedtls_mpi_init(&grp.B);
    mbedtls_mpi_init(&grp.N);
    mbedtls_ecp_point_init(&grp.G);
    mbedtls_ecp_point_init(&Q);
    mbedtls_mpi_init(&mr);
    mbedtls_mpi_init(&ms);

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.P, ecc->p, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.A, ecc->a, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.B, ecc->b, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.N, ecc->n, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.X, ecc->Gx, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&grp.G.Y, ecc->Gy, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&grp.G.Z, 1));
    grp.pbits = mbedtls_mpi_bitlen(&grp.P);
    grp.nbits = mbedtls_mpi_bitlen(&grp.N);
    grp.h = ecc->h;

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q.X, px, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&Q.Y, py, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_lset(&Q.Z, 1));

    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&mr, r, ecc->ksize));
    MBEDTLS_MPI_CHK(mbedtls_mpi_read_binary(&ms, s, ecc->ksize));

    MBEDTLS_MPI_CHK(mbedtls_ecdsa_verify(&grp, hash, hlen, &Q, &mr, &ms));

cleanup:
    mbedtls_mpi_free(&grp.P);
    mbedtls_mpi_free(&grp.A);
    mbedtls_mpi_free(&grp.B);
    mbedtls_mpi_free(&grp.N);
    mbedtls_ecp_point_free(&grp.G);
    mbedtls_ecp_group_free(&grp);
    mbedtls_ecp_point_free(&Q);
    mbedtls_mpi_free(&mr);
    mbedtls_mpi_free(&ms);

    HI_LOG_FuncExit();

    return(ret);
}

#endif
/** @}*/  /** <!-- ==== API Code end ====*/
