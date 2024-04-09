/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cryp_sm2.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_sm2.h"
#include "cryp_sm2.h"
#include "cryp_trng.h"
#include "ext_alg.h"

/********************** Internal Structure Definition ************************/
/** \addtogroup      sm2 */
/** @{*/  /** <!-- [sm2]*/

#define HI_LOG_DEBUG_MSG(a, b, c)  //HI_PRINT_HEX(a, b, c)
#define SM2_SIGN_BUF_CNT           (18)
#define SM2_GET_RANDNUM_WAITDONE   (0x1000)

/*! Define the constant value */
const u32 sm2p[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF};
const u32 sm2a[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0xFCFFFFFF};
const u32 sm2b[SM2_LEN_IN_WROD] =  {0x9EFAE928, 0x345E9F9D, 0x4B9E5A4D, 0xA70965CF, 0xF58997F3, 0x928FAB15, 0x41BDBCDD, 0x930E944D};
const u32 sm2n[SM2_LEN_IN_WROD] =  {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2341D539};
const u32 sm2n1[SM2_LEN_IN_WROD] = {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2241D539};
const u32 sm2n2[SM2_LEN_IN_WROD] = {0xFEFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x6BDF0372, 0x2B05C621, 0x09F4BB53, 0x2141D539};
const u32 sm2Gx[SM2_LEN_IN_WROD] = {0x2CAEC432, 0x1981191F, 0x4604995F, 0x94C9396A, 0xBF0BE38F, 0xE10B66F2, 0x89455A71, 0xC7744C33};
const u32 sm2Gy[SM2_LEN_IN_WROD] = {0xA23637BC, 0x9C77F6F4, 0xE3CEBD59, 0x5321696B, 0x7C87A9D0, 0x40472AC6, 0xE532DF02, 0xA0F03921};
const u32 sm2P[SM2_LEN_IN_WROD] =  {0x04000000, 0x02000000, 0x01000000, 0x01000000, 0x02000000, 0xFFFFFFFF, 0x02000000, 0x03000000};

/* sm2 function list */
sm2_func sm2_descriptor;

/*! rsa mutex */
static crypto_mutex sm2_mutex;

#define KAPI_SM2_LOCK()\
    ret = crypto_mutex_lock(&sm2_mutex);  \
    if (HI_SUCCESS != ret)        \
    {\
        HI_LOG_ERROR("error, sm2 lock failed\n");\
        HI_LOG_FuncExit();\
        return ret;\
    }

#define KAPI_SM2_UNLOCK()   crypto_mutex_unlock(&sm2_mutex)

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      sm2 drivers*/
/** @{*/  /** <!-- [sm2]*/

s32 cryp_sm2_get_randnum(u32 randnum[SM2_LEN_IN_WROD], const u32 max[SM2_LEN_IN_WROD])
{
    u32 i = 0,j = 0;

    while((i < SM2_LEN_IN_WROD && j < SM2_GET_RANDNUM_WAITDONE))
    {
        cryp_trng_get_random(&randnum[i], -1);
        if (randnum[i] <= max[i])
        {
            i++;
            j = 0;
        }
        j++;
    }
    if (SM2_GET_RANDNUM_WAITDONE <= j)
    {
        HI_LOG_ERROR("Error! SM2 get random number failed!\n");
        return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    }

    return HI_SUCCESS;
}

#ifdef CHIP_SM2_SUPPORT

/*check val whether zero or not*/
static u32 cryp_sm2_is_zero(const u32 val[SM2_LEN_IN_WROD])
{
    u32 i = 0;

    for (i=0; i < SM2_LEN_IN_WROD; i++)
    {
        if (val[i] != 0x00)
        {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

/*compare 2 val*/
static u32 cryp_sm2_cmp(const u32 val1[SM2_LEN_IN_WROD], const u32 val2[SM2_LEN_IN_WROD])
{
    u32 i = 0;
    u32 cmp = 0;

    for (i=0; i < SM2_LEN_IN_WROD; i++)
    {
        cmp |= val1[i] ^ val2[i];
    }

    return cmp;
}

/*check val whether less than sm2n1 or not*/
static s32 cryp_sm2_rang_check(const u32 val[SM2_LEN_IN_WROD])
{
    u32 i = 0;
    const u8 *pu8Val = HI_NULL;
    const u8 *pu8n1 = HI_NULL;

    if (cryp_sm2_is_zero(val))
    {
        return HI_ERR_CIPHER_ILLEGAL_DATA;
    }

    pu8Val = (u8 *)val;
    pu8n1 = (u8 *)sm2n1;

    for (i=0; i < SM2_LEN_IN_BYTE; i++)
    {
        if (pu8Val[i] < pu8n1[i])
        {
            return HI_SUCCESS;
        }
        else if (pu8Val[i] > pu8n1[i])
        {
            return HI_ERR_CIPHER_ILLEGAL_DATA;
        }
    }

    return HI_SUCCESS;
}

/***************************************
  1. generate a randnum k, k¡Ê[1,n-1],
  2. (x1,y1)=[k]G,
  3. r=(e+x1)mod n, if r=0 or r+k=n, return step 1
  4. s=((1+dA)^-1 ¡¤(k-r¡¤dA))mod n
****************************************/
s32 cryp_sm2_sign(u32 e[SM2_LEN_IN_WROD], u32 d[SM2_LEN_IN_WROD],
                  u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD])
{
    s32 ret = HI_SUCCESS;
    u32 *buf = HI_NULL;
    u32 *k = HI_NULL;
    u32 *Rx = HI_NULL;
    u32 *Ry = HI_NULL;
    u32 *ee = HI_NULL;
    u32 *rk = HI_NULL;
    u32 *my = HI_NULL;
    u32 *mr = HI_NULL;
    u32 *mk = HI_NULL;
    u32 *mrk = HI_NULL;
    u32 *mrky = HI_NULL;
    u32 *TA = HI_NULL;
    u32 *mTA = HI_NULL;
    u32 *mTy = HI_NULL;
    u32 *minv = HI_NULL;
    u32 *mrk1 = HI_NULL;
    u32 *mrky1 = HI_NULL;
    u32 *mTz = HI_NULL;
    u32 *ms = HI_NULL;
    u32 u32ReTry = 0;
    u32 id  = 0;
    u32 i = 0, j = 0;

    HI_LOG_FuncEnter();

    KAPI_SM2_LOCK();

    buf = (u32 *)crypto_calloc(1, SM2_LEN_IN_BYTE * SM2_SIGN_BUF_CNT);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("Error! Malloc memory failed!\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        KAPI_SM2_UNLOCK();
        return HI_FAILURE;
    }

    CHECK_EXIT(drv_sm2_resume());

    Rx   = buf + SM2_LEN_IN_WROD * id++ ;
    Ry   = buf + SM2_LEN_IN_WROD * id++ ;
    ee   = buf + SM2_LEN_IN_WROD * id++ ;
    rk   = buf + SM2_LEN_IN_WROD * id++ ;
    my   = buf + SM2_LEN_IN_WROD * id++ ;
    mr   = buf + SM2_LEN_IN_WROD * id++ ;
    mk   = buf + SM2_LEN_IN_WROD * id++ ;
    mrk  = buf + SM2_LEN_IN_WROD * id++ ;
    mrky = buf + SM2_LEN_IN_WROD * id++ ;
    TA   = buf + SM2_LEN_IN_WROD * id++ ;
    mTA  = buf + SM2_LEN_IN_WROD * id++ ;
    mTy  = buf + SM2_LEN_IN_WROD * id++ ;
    minv = buf + SM2_LEN_IN_WROD * id++ ;
    mrk1 = buf + SM2_LEN_IN_WROD * id++ ;
    mrky1= buf + SM2_LEN_IN_WROD * id++ ;
    mTz  = buf + SM2_LEN_IN_WROD * id++ ;
    ms   = buf + SM2_LEN_IN_WROD * id++ ;
    k    = buf + SM2_LEN_IN_WROD * id++ ;

    while(1)
    {
        if (u32ReTry++ > 10)
        {
            HI_LOG_ERROR("Error! K is Invalid!\n");
            ret = HI_FAILURE;
            goto exit__;
        }

        /************Step 1  ******************/
        HI_LOG_INFO("1. generate randnum k\n");
        for (i=0; i<SM2_TRY_CNT; i++)
        {
            CHECK_EXIT(cryp_sm2_get_randnum(buf + SM2_LEN_IN_WROD* i, sm2n1));
        }
        cryp_trng_get_random(&j, -1);
        j %= SM2_TRY_CNT;
        crypto_memcpy(k, SM2_LEN_IN_BYTE, buf + SM2_LEN_IN_WROD * j, SM2_LEN_IN_BYTE);
        HI_LOG_DEBUG_MSG("k", k, SM2_LEN_IN_BYTE);

        /************Step 2 - 7 **************/
        HI_LOG_INFO("2. R=k*G\n");
        HI_LOG_DEBUG_MSG("Gx", sm2Gx, SM2_LEN_IN_BYTE);
        HI_LOG_DEBUG_MSG("Gy", sm2Gy, SM2_LEN_IN_BYTE);
        CHECK_EXIT(drv_sm2_mul_dot(k, sm2Gx, sm2Gy, Rx, Ry, HI_TRUE));
        HI_LOG_DEBUG_MSG("Rx", Rx, SM2_LEN_IN_BYTE);
        HI_LOG_DEBUG_MSG("Ry", Ry, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("3. e`=e+0 mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(e, sm20, sm2n, ee));
        HI_LOG_DEBUG_MSG("e`", ee, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("4. r=e`+Rx mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(ee, Rx, sm2n, r));
        HI_LOG_DEBUG_MSG("r", r, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("5. r ?=0\n");
        if (cryp_sm2_is_zero(r))
        {
            continue;
        }
        HI_LOG_INFO("6. rk= r+k mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(r, k, sm2n, rk));
        HI_LOG_DEBUG_MSG("rk", rk, SM2_LEN_IN_BYTE);
        HI_LOG_INFO("7. rk ?=0\n");
        if (cryp_sm2_is_zero(rk))
        {
            continue;
        }

        /************Step 8 - 13 **************/
        HI_LOG_INFO("8. generate randnum my\n");
        CHECK_EXIT(cryp_sm2_get_randnum(my, sm2n1));
        HI_LOG_DEBUG_MSG("my", my, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("9. mr=r*N mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(r, sm2N, mr, HI_FALSE));
        HI_LOG_DEBUG_MSG("mr", mr, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("10. mk=k*N mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(k, sm2N, mk, HI_FALSE));
        HI_LOG_DEBUG_MSG("mk", mk, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("11. mrk = (mr + mk) mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(mr, mk, sm2n, mrk));
        HI_LOG_DEBUG_MSG("mrk", mrk, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("12. mrky = (mrk * my) mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(mrk, my, mrky, HI_FALSE));
        HI_LOG_DEBUG_MSG("mrky", mrky, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("13. TA= dA*my mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(my, d, TA, HI_TRUE));
        HI_LOG_DEBUG_MSG("TA", TA, SM2_LEN_IN_BYTE);

        /************Step 14 - 19 **************/
        HI_LOG_INFO("14. mTA = TA*N mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(TA, sm2N, mTA, HI_FALSE));
        HI_LOG_DEBUG_MSG("mTA", mTA, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("15. mTy = (mTA + my) mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(mTA, my, sm2n, mTy));
        HI_LOG_DEBUG_MSG("mTy", mTy, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("16. minv = mTy^-1 mod n\n");
        CHECK_EXIT(drv_sm2_inv_mod(mTy, sm2n, minv));
        HI_LOG_DEBUG_MSG("minv", minv, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("17. mrk1 = (mr + mk) mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(mr, mk, sm2n, mrk1));
        HI_LOG_DEBUG_MSG("mrk1", mrk1, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("18. mrky1 = (mrk1 * my) mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(mrk1, my, mrky1, HI_FALSE));
        HI_LOG_DEBUG_MSG("mrky1", mrky1, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("19. mrky1 ?= mrky\n");
        if (cryp_sm2_cmp(mrky1, mrky) != 0)
        {
            HI_LOG_ERROR("Error! mrky1 != mrky!\n");
            ret = HI_FAILURE;
            goto exit__;
        }

        /************Step 20 - 25 **************/
        HI_LOG_INFO("20. mTz = (mrky * minv) mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(mrky, minv, mTz, HI_FALSE));
        HI_LOG_DEBUG_MSG("mTz", mTz, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("21. ms = (mTz - mr) mod n\n");
        CHECK_EXIT(drv_sm2_sub_mod(mTz, mr, sm2n, ms));
        HI_LOG_DEBUG_MSG("ms", ms, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("22. ms ?=0\n");
        if (cryp_sm2_is_zero(ms))
        {
            continue;
        }
        HI_LOG_INFO("23. s=ms*1 mod n\n");
        CHECK_EXIT(drv_sm2_mul_modn(ms, sm21, s, HI_FALSE));
        HI_LOG_DEBUG_MSG("s", s, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("24. rk= r+k mod n\n");
        CHECK_EXIT(drv_sm2_add_mod(r, k, sm2n, rk));
        HI_LOG_DEBUG_MSG("rk", rk, SM2_LEN_IN_BYTE);

        HI_LOG_INFO("25. rk ?=0\n");
        if (cryp_sm2_is_zero(rk))
        {
            continue;
        }

        break;
    }

exit__:
    drv_sm2_clean_ram();
    drv_sm2_suspend();
    crypto_memset(buf, SM2_LEN_IN_BYTE * SM2_SIGN_BUF_CNT, 0, SM2_LEN_IN_BYTE * SM2_SIGN_BUF_CNT);

    KAPI_SM2_UNLOCK();

    crypto_free(buf);
    buf = HI_NULL;

    HI_LOG_FuncExit();

    return ret;
}

/***************************************
  1. t=(r+s)mod n, if t==0, return fail
  2. (x1,y1)=[s]G+tP,
  3. r=(e+x1)mod n, if r==R, return pass
****************************************/
s32 cryp_sm2_verify(u32 e[SM2_LEN_IN_WROD],
                    u32 px[SM2_LEN_IN_WROD],u32 py[SM2_LEN_IN_WROD],
                    u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 t[SM2_LEN_IN_WROD]    = {0};
    u32 sgx[SM2_LEN_IN_WROD]  = {0};
    u32 sgy[SM2_LEN_IN_WROD]  = {0};
    u32 tpax[SM2_LEN_IN_WROD] = {0};
    u32 tpay[SM2_LEN_IN_WROD] = {0};
    u32 rx[SM2_LEN_IN_WROD]   = {0};
    u32 ry[SM2_LEN_IN_WROD]   = {0};
    u32 ee[SM2_LEN_IN_WROD]   = {0};
    u32 v[SM2_LEN_IN_WROD]    = {0};

    HI_LOG_FuncEnter();

    KAPI_SM2_LOCK();

    CHECK_EXIT(drv_sm2_resume());

    /* t = r + s mod n */
    CHECK_EXIT(cryp_sm2_rang_check(r)); /*1<=r<=n-1*/
    CHECK_EXIT(cryp_sm2_rang_check(s)); /*1<=s<=n-1*/
    CHECK_EXIT(drv_sm2_add_mod(r, s, sm2n, t));

    /*t = 0 ?*/
    if (cryp_sm2_is_zero(t))
    {
        HI_LOG_ERROR("Error! t is zero!\n");
        ret = HI_FAILURE;
        HI_LOG_PrintFuncErr(cryp_sm2_is_zero, HI_TRUE);
        goto exit__;
    }

    HI_LOG_INFO("sG = s * G\n");
    CHECK_EXIT(drv_sm2_mul_dot(s, sm2Gx, sm2Gy, sgx, sgy, HI_FALSE));
    HI_LOG_DEBUG_MSG("sGx", sgx, SM2_LEN_IN_BYTE);
    HI_LOG_DEBUG_MSG("sGy", sgy, SM2_LEN_IN_BYTE);

    HI_LOG_INFO("tPA = t * PA\n");
    CHECK_EXIT(drv_sm2_mul_dot(t, px, py, tpax, tpay, HI_FALSE));
    HI_LOG_DEBUG_MSG("tPAx", tpax, SM2_LEN_IN_BYTE);
    HI_LOG_DEBUG_MSG("tPAy", tpay, SM2_LEN_IN_BYTE);

    HI_LOG_INFO("R = sG + tPA\n");
    CHECK_EXIT(drv_sm2_add_dot(sgx, sgy, tpax, tpay, rx, ry));
    HI_LOG_DEBUG_MSG("Rx", rx, SM2_LEN_IN_BYTE);
    HI_LOG_DEBUG_MSG("Ry", ry, SM2_LEN_IN_BYTE);

    HI_LOG_INFO("e` = e + 0 mod n\n");
    CHECK_EXIT(drv_sm2_add_mod(e, sm20, sm2n, ee));
    HI_LOG_DEBUG_MSG("e", e, SM2_LEN_IN_BYTE);
    HI_LOG_DEBUG_MSG("e`", ee, SM2_LEN_IN_BYTE);

    HI_LOG_INFO("v = e` + Rx mod n\n");
    CHECK_EXIT(drv_sm2_add_mod(ee, rx, sm2n, v));

    HI_LOG_DEBUG_MSG("r", r, SM2_LEN_IN_BYTE);
    HI_LOG_DEBUG_MSG("v", v, SM2_LEN_IN_BYTE);

    HI_LOG_INFO("v = r ?\n");
    if (cryp_sm2_cmp(r, v) == 0)
    {
        ret = HI_SUCCESS;
    }
    else
    {
        HI_LOG_ERROR("Error! r != v!\n");
        HI_LOG_PrintErrCode(HI_FAILURE);
        ret = HI_FAILURE;
    }

exit__:
    drv_sm2_clean_ram();
    drv_sm2_suspend();

    KAPI_SM2_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

/* Compute C1(x, y) = k * G(x, y), XY = k * P(x, y)*/
s32 cryp_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                     u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 u32k[SM2_LEN_IN_WROD]= {0};
    u32 u32ReTry = 0;

    HI_LOG_FuncEnter();

    /*t = 0 ?*/
    if (cryp_sm2_is_zero(px) || cryp_sm2_is_zero(py))
    {
        HI_LOG_ERROR("Error! PB is zero!\n");
        HI_LOG_PrintFuncErr(cryp_sm2_is_zero, HI_TRUE);
        return HI_FAILURE;
    }

    KAPI_SM2_LOCK();

    CHECK_EXIT(drv_sm2_resume());

    while(1)
    {
        if (SM2_TRY_CNT < u32ReTry++)
        {
            HI_LOG_ERROR("Error! K is Invalid!\n");
            ret =  HI_FAILURE;
            goto exit__;
        }

        /*generate randnum k, 1<=k<=n-1*/
        CHECK_EXIT(cryp_sm2_get_randnum(u32k, sm2n1));

        /*C1=k*G*/
        CHECK_EXIT(drv_sm2_mul_dot(u32k, sm2Gx, sm2Gy, c1x, c1y, HI_FALSE));

        /*c1 = 0 ?*/
        if (cryp_sm2_is_zero(c1x) || cryp_sm2_is_zero(c1y))
        {
            continue;
        }

        /* kPB = k * PB */
        CHECK_EXIT(drv_sm2_mul_dot(u32k, px, py, x2, y2, HI_FALSE));

        /* xy = 0 ?*/
        if (cryp_sm2_is_zero(x2) || cryp_sm2_is_zero(y2))
        {
            continue;
        }
        break;
    }

exit__:

    drv_sm2_clean_ram();
    drv_sm2_suspend();

    KAPI_SM2_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

/*check y^2=x^3+ax+b ? */
static s32 cryp_sm2_dot_check(u32 x[SM2_LEN_IN_WROD], u32 y[SM2_LEN_IN_WROD], u32 check)
{
    s32 ret = HI_FAILURE;
    u32 mx[SM2_LEN_IN_WROD]  = {0};
    u32 my[SM2_LEN_IN_WROD]  = {0};
    u32 mx2[SM2_LEN_IN_WROD] = {0};
    u32 mx3[SM2_LEN_IN_WROD] = {0};
    u32 max[SM2_LEN_IN_WROD] = {0};
    u32 mt[SM2_LEN_IN_WROD]  = {0};
    u32 ms[SM2_LEN_IN_WROD]  = {0};
    u32 my2[SM2_LEN_IN_WROD] = {0};

    HI_LOG_FuncEnter();

    /* xy = 0 ? */
    if (cryp_sm2_is_zero(x) || cryp_sm2_is_zero(y))
    {
        HI_LOG_ERROR("Error! X or Y is zero!\n");
        HI_LOG_PrintFuncErr(cryp_sm2_is_zero, HI_TRUE);
        return HI_FAILURE;
    }

    HI_LOG_INFO("1. ma = a*P mod p\n");
    HI_LOG_INFO("2. mb = b*P mod p\n");
    HI_LOG_INFO("3. mx=C1x*P mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(x, sm2P, mx, HI_FALSE));
    HI_LOG_INFO("4. my=C1y*P mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(y, sm2P, my, HI_FALSE));
    HI_LOG_INFO("5. mx2=mx* mx mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(mx, mx, mx2, HI_FALSE));
    HI_LOG_INFO("6. mx3=mx2* mx mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(mx2, mx, mx3, HI_FALSE));
    HI_LOG_INFO("7. max=ma*mx mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(sm2ma, mx, max, HI_FALSE));
    HI_LOG_INFO("8. mt= mx3+max mod p\n");
    CHECK_EXIT(drv_sm2_add_mod(mx3, max, sm2p, mt));
    HI_LOG_INFO("9. ms= mt+mb mod p\n");
    CHECK_EXIT(drv_sm2_add_mod(mt, sm2mb, sm2p, ms));
    HI_LOG_INFO("10. my2=my*my mod p\n");
    CHECK_EXIT(drv_sm2_mul_modp(my, my, my2, HI_FALSE));
    HI_LOG_INFO("11. my2 ?= ms\n");
    if (cryp_sm2_cmp(ms, my2) != 0)
    {
        HI_LOG_ERROR("Error! my2 != s!\n");
        ret =  HI_FAILURE;
        goto exit__;
    }

    if (check)
    {
        HI_LOG_INFO("12. S= h * C1\n");
        CHECK_EXIT(drv_sm2_mul_dot(sm21, x, y, mx, my, HI_FALSE));
    }
exit__:

    drv_sm2_clean_ram();

    HI_LOG_FuncExit();

    return ret;
}

/*Compute XY(x, y) = C1(x, y) * d*/
s32 cryp_sm2_decrypt(u32 d[SM2_LEN_IN_WROD],
                     u32 c1x[SM2_LEN_IN_WROD], u32 c1y[SM2_LEN_IN_WROD],
                     u32 x2[SM2_LEN_IN_WROD], u32 y2[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 mx[SM2_LEN_IN_WROD] = {0};
    u32 my[SM2_LEN_IN_WROD] = {0};

    HI_LOG_FuncEnter();

    /* c1 = 0 ? */
    if (cryp_sm2_is_zero(c1x) || cryp_sm2_is_zero(c1y))
    {
        HI_LOG_ERROR("Error! C1 is zero!\n");
        HI_LOG_PrintFuncErr(cryp_sm2_is_zero, HI_TRUE);
        return HI_FAILURE;
    }

    KAPI_SM2_LOCK();

    CHECK_EXIT(drv_sm2_resume());

    /*check C1y^2=C1x^3+aC1x+b ? */
    CHECK_EXIT(cryp_sm2_dot_check(c1x, c1y, HI_TRUE));

    /*Compute M(x,y)*/
    CHECK_EXIT(drv_sm2_mul_dot(d, c1x, c1y, mx, my, HI_TRUE));

//    HI_PRINT_HEX ("Mx", mx, 32);
//    HI_PRINT_HEX ("My", my, 32);

    /*check C1y^2=C1x^3+aC1x+b ? */
    CHECK_EXIT(cryp_sm2_dot_check(c1x, c1y, HI_TRUE));

    /*check My^2=Mx^3+aMx+b ? */
    CHECK_EXIT(cryp_sm2_dot_check(mx, my, HI_FALSE));

    crypto_memcpy(x2, SM2_LEN_IN_BYTE, mx, SM2_LEN_IN_BYTE);
    crypto_memcpy(y2, SM2_LEN_IN_BYTE, my, SM2_LEN_IN_BYTE);

exit__:

    crypto_memset(mx, sizeof(mx), 0, SM2_LEN_IN_BYTE);
    crypto_memset(my, sizeof(my), 0, SM2_LEN_IN_BYTE);
    drv_sm2_clean_ram();
    drv_sm2_suspend();

    KAPI_SM2_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

/* Compute P(x,y) = d * G(x,y) */
s32 cryp_sm2_gen_key(u32 d[SM2_LEN_IN_WROD], u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    u32 i = 0, j = 0;
    u32 randnum[8][SM2_LEN_IN_WROD];

    HI_LOG_FuncEnter();

    KAPI_SM2_LOCK();

    CHECK_EXIT(drv_sm2_resume());

    crypto_memset(randnum, sizeof(randnum), 0, sizeof(randnum));

    HI_LOG_INFO ("Step 1. generate randnum d, 1<=k<=n-2");
    for (i=0; i<SM2_TRY_CNT; i++)
    {
        CHECK_EXIT(cryp_sm2_get_randnum(randnum[i], sm2n1));
    }
    cryp_trng_get_random(&j, -1);
    j %= SM2_TRY_CNT;
    crypto_memcpy(d, SM2_LEN_IN_BYTE, randnum[j], SM2_LEN_IN_BYTE);

    HI_LOG_INFO ("Step 2. PA=dA*G");

    /* P = d * G */
    CHECK_EXIT(drv_sm2_mul_dot(d, sm2Gx, sm2Gy, px, py, HI_TRUE));

exit__:

    drv_sm2_clean_ram();
    drv_sm2_suspend();

    KAPI_SM2_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}
#endif

int cryp_sm2_init(void)
{
    sm2_capacity capacity;

    HI_LOG_FuncEnter();

    crypto_mutex_init(&sm2_mutex);

    crypto_memset(&sm2_descriptor, sizeof(sm2_descriptor), 0, sizeof(sm2_descriptor));
    crypto_memset(&capacity, sizeof(capacity), 0, sizeof(capacity));

#ifdef CHIP_SM2_SUPPORT
    drv_sm2_get_capacity(&capacity);

    /* replace the sm2 function of tomcrypt */
    if (capacity.sm2)
    {
        if (HI_SUCCESS != drv_sm2_init())
        {
            return HI_FAILURE;
        }
        sm2_descriptor.sign    = cryp_sm2_sign;
        sm2_descriptor.verify  = cryp_sm2_verify;
        sm2_descriptor.encrypt = cryp_sm2_encrypt;
        sm2_descriptor.decrypt = cryp_sm2_decrypt;
        sm2_descriptor.genkey  = cryp_sm2_gen_key;

    }
    else
#endif
#ifdef SOFT_SM2_SUPPORT
    {
        sm2_descriptor.sign    = mbedtls_sm2_sign;
        sm2_descriptor.verify  = mbedtls_sm2_verify;
        sm2_descriptor.encrypt = mbedtls_sm2_encrypt;
        sm2_descriptor.decrypt = mbedtls_sm2_decrypt;
        sm2_descriptor.genkey  = mbedtls_sm2_gen_key;
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void cryp_sm2_deinit(void)
{
#ifdef CHIP_SM2_SUPPORT
    sm2_capacity capacity;

    drv_sm2_get_capacity(&capacity);

    /* recovery the sm2 function of mbedtls */
    if (capacity.sm2)
    {
        drv_sm2_deinit();
    }
#endif
    crypto_mutex_destroy(&sm2_mutex);
}

sm2_func * cryp_get_sm2_op(void)
{
    return &sm2_descriptor;
}

/** @}*/  /** <!-- ==== API Code end ====*/
