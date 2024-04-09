/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_symc.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_symc.h"
#include "drv_cenc.h"

/* max number of nodes */
#define MAX_PKG_NUMBER              (100000)

/* max length of CCM/GCM AAD */
#define MAX_AEAD_A_LEN              (0x100000)

typedef struct
{
    u32 open   : 1;                  /*!<  open or close */
    u32 config : 1;                  /*!<  aleardy config or not */
    symc_func *func;
    void *cryp_ctx;                  /*!<  Context of cryp instance */
    crypto_owner owner;              /*!<  user ID */
    CRYP_CIPHER_CTRL_S  ctrl;        /*!<  control infomation */
}kapi_symc_ctx;

/*! Context of cipher */
static kapi_symc_ctx *kapi_ctx = HI_NULL;

/* symc mutex */
static crypto_mutex symc_mutex;

#define KAPI_SYMC_CHECK_HANDLE(handle)   \
do \
{ \
    if((HI_ID_CIPHER != HI_HANDLE_GET_MODID(handle)) \
        || (0 != HI_HANDLE_GET_PriDATA(handle))) \
    { \
        HI_LOG_ERROR("Invalid handle 0x%x!\n", handle); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (CRYPTO_HARD_CHANNEL_MAX <= HI_HANDLE_GET_CHNID(handle)) \
    { \
        HI_LOG_ERROR("chan %d is too large, max: %d\n", HI_HANDLE_GET_CHNID(handle), CRYPTO_HARD_CHANNEL_MAX); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (HI_FALSE == kapi_ctx[HI_HANDLE_GET_CHNID(handle)].open) \
    { \
        HI_LOG_ERROR("chan %d is not open\n", HI_HANDLE_GET_CHNID(handle)); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
} while (0)

#define KAPI_SYMC_LOCK()   \
    ret = crypto_mutex_lock(&symc_mutex);  \
    if (HI_SUCCESS != ret)        \
    {\
        HI_LOG_ERROR("error, symc lock failed\n");\
        HI_LOG_PrintFuncErr(crypto_mutex_lock, ret);\
        return ret;\
    }

#define KAPI_SYMC_UNLOCK()   crypto_mutex_unlock(&symc_mutex)
#define AES_CCM_MIN_TAG_LEN     (4)
#define AES_CCM_MAX_TAG_LEN     (16)
#define AES_GCM_MIN_TAG_LEN     (1)
#define AES_GCM_MAX_TAG_LEN     (16)

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      symc */
/** @{*/  /** <!-- [kapi]*/

s32 kapi_symc_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_INFO("kapi_symc_init()\n");

    HI_LOG_FuncEnter();

    crypto_mutex_init(&symc_mutex);

    kapi_ctx = crypto_calloc(sizeof(kapi_symc_ctx), CRYPTO_HARD_CHANNEL_MAX);
    if (HI_NULL == kapi_ctx)
    {
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    ret = cryp_symc_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_symc_init, ret);
        crypto_free(kapi_ctx);
        kapi_ctx = HI_NULL;
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_deinit(void)
{
    HI_LOG_INFO("kapi_symc_deinit()\n");

    HI_LOG_FuncEnter();

    cryp_symc_deinit();

    crypto_mutex_destroy(&symc_mutex);
    crypto_free(kapi_ctx);
    kapi_ctx = HI_NULL;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_release(void)
{
    u32 i = 0, chn = 0;
    s32 ret = HI_FAILURE;
    kapi_symc_ctx *ctx = HI_NULL;
    crypto_owner owner;

    HI_LOG_FuncEnter();

    crypto_get_owner(&owner);

    HI_LOG_INFO("symc release owner 0x%x\n", owner);

    /* destroy the channel which are created by current user */
    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        ctx = &kapi_ctx[i];
        if (HI_TRUE == ctx->open)
        {
            if (0 == memcmp(&owner, &ctx->owner, sizeof(owner)))
            {
                chn = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, i);
                HI_LOG_INFO("symc release chn %d\n", chn);
                ret = kapi_symc_destroy(chn);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(kapi_symc_destroy, ret);
                    return ret;
                }
            }
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_create(u32 *id, CRYP_CIPHER_TYPE_E type)
{
    s32 ret = HI_FAILURE;
    u32 chn = 0;
    kapi_symc_ctx *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == id);

    KAPI_SYMC_LOCK();

    /* allocate a aes soft channel for hard channel allocted */
    ret = cryp_symc_alloc_chn(&chn, type);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, allocate symc channel failed\n");
        HI_LOG_PrintFuncErr(cryp_symc_alloc_chn, ret);
        KAPI_SYMC_UNLOCK();
        return ret;
    }
    ctx = &kapi_ctx[chn];

    crypto_memset(ctx, sizeof(kapi_symc_ctx), 0, sizeof(kapi_symc_ctx));
    crypto_get_owner(&ctx->owner);

    *id = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, chn);
    ctx->open = HI_TRUE;
    ctx->config = HI_FALSE;

    HI_LOG_INFO("kapi_symc_create()- chn %d\n", chn);

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_destroy(u32 id)
{
    s32 ret = HI_FAILURE;
    kapi_symc_ctx *ctx = HI_NULL;
    u32 softId = 0;

    HI_LOG_FuncEnter();

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);

    KAPI_SYMC_LOCK();

    cryp_symc_free_chn(softId);

    /* Destroy the attached instance of Symmetric cipher engine */
    if ((HI_NULL != ctx->func) && (HI_NULL != ctx->func->destroy))
    {
        ret = ctx->func->destroy(ctx->cryp_ctx);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("error, cryp_symc_destory failed\n");
            KAPI_SYMC_UNLOCK();
            return ret;
        }
        ctx->cryp_ctx = HI_NULL;
    }

    ctx->open = HI_FALSE;

    HI_LOG_INFO("kapi_symc_destroy()- chn 0x%x\n", id);

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_symc_width_check(CRYP_CIPHER_ALG_E enAlg, CRYP_CIPHER_WORK_MODE_E mode, u32 width, u32 round)
{
   /* the bit width depend on alg and mode, which limit to hardware
    * des/3des with cfb/ofb support bit1, bit8, bit 64.
    * aes with cfb/ofb only support bit128.
    * sm1 with ofb only support bit128, cfb support bit1, bit8, bit 64.
    */

    HI_LOG_FuncEnter();

    if ((enAlg == CRYP_CIPHER_ALG_3DES) || (enAlg == CRYP_CIPHER_ALG_DES))
    {
        if (mode > CRYP_CIPHER_WORK_MODE_OFB)
        {
            HI_LOG_ERROR("Invalid enAlg %d and mode %d\n",enAlg, mode);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if((mode == CRYP_CIPHER_WORK_MODE_CFB) || (mode == CRYP_CIPHER_WORK_MODE_OFB))
        {
            if ((width != SYMC_DAT_WIDTH_64)
                 && (width != SYMC_DAT_WIDTH_8)
                 && (width != SYMC_DAT_WIDTH_1))
            {
                HI_LOG_ERROR("Invalid mode %d and bit width %d\n",mode, width);
                HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                return HI_ERR_CIPHER_INVALID_PARA;
            }
        }
    }

    if (enAlg == CRYP_CIPHER_ALG_AES)
    {
        if (mode > CRYP_CIPHER_WORK_MODE_BUTT)
        {
            HI_LOG_ERROR("Invalid enAlg %d and mode %d\n",enAlg, mode);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if ((mode == CRYP_CIPHER_WORK_MODE_CFB)
             && (width != SYMC_DAT_WIDTH_1)
             && (width != SYMC_DAT_WIDTH_8)
             && (width != SYMC_DAT_WIDTH_128))
        {
            HI_LOG_ERROR("Invalid enAlg %d mode %d and width %d\n", enAlg, mode, width);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if ((mode == CRYP_CIPHER_WORK_MODE_OFB)
            && (width != SYMC_DAT_WIDTH_128))
        {
            HI_LOG_ERROR("Invalid enAlg %d mode %d and width %d\n", enAlg, mode, width);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

#ifdef HI_PRODUCT_SM14_SUPPORT
    if (enAlg == CRYP_CIPHER_ALG_SM1)
    {
        if (mode > CRYP_CIPHER_WORK_MODE_OFB)
        {
            HI_LOG_ERROR("Invalid enAlg %d and mode %d\n",enAlg, mode);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if ((mode == CRYP_CIPHER_WORK_MODE_OFB)
            && (width != SYMC_DAT_WIDTH_128))
        {
            HI_LOG_ERROR("Invalid enAlg %d mode %d and width %d\n", enAlg, mode, width);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if ((mode == CRYP_CIPHER_WORK_MODE_CFB)
            && (width >= SYMC_DAT_WIDTH_COUNT))
        {
            HI_LOG_ERROR("Invalid enAlg %d mode %d and width %d\n", enAlg, mode, width);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    if ((enAlg == CRYP_CIPHER_ALG_SM4)
        && (mode != CRYP_CIPHER_WORK_MODE_ECB)
        && (mode != CRYP_CIPHER_WORK_MODE_CBC)
        && (mode != CRYP_CIPHER_WORK_MODE_CTR))
    {
        HI_LOG_ERROR("Invalid enAlg %d and mode %d\n",enAlg, mode);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((enAlg == CRYP_CIPHER_ALG_SM1) && (round >= CRYP_CIPHER_SM1_ROUND_BUTT))
    {
        HI_LOG_ERROR("Invalid enAlg %d and Sm1Round %d\n",enAlg, round);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
#endif

    if (enAlg >= CRYP_CIPHER_ALG_BUTT)
    {
        HI_LOG_ERROR("Invalid enAlg %d .\n",enAlg);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (width >= SYMC_DAT_WIDTH_COUNT)
    {
        HI_LOG_ERROR("Invalid mode %d\n",width);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_symc_match_width(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                 CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                                 symc_width *width)
{
    HI_LOG_FuncEnter();

    /* set the bit width which depend on alg and mode */
    if ((CRYP_CIPHER_WORK_MODE_CFB == enWorkMode)
        || (CRYP_CIPHER_WORK_MODE_OFB == enWorkMode))
    {
        switch(enBitWidth)
        {
            case CRYP_CIPHER_BIT_WIDTH_64BIT:
            {
                *width = SYMC_DAT_WIDTH_64;
                break;
            }
            case CRYP_CIPHER_BIT_WIDTH_8BIT:
            {
                *width = SYMC_DAT_WIDTH_8;
                break;
            }
            case CRYP_CIPHER_BIT_WIDTH_1BIT:
            {
                *width = SYMC_DAT_WIDTH_1;
                break;
            }
            case CRYP_CIPHER_BIT_WIDTH_128BIT:
            {
                *width = SYMC_DAT_WIDTH_128;
                break;
            }
            default:
            {
                HI_LOG_ERROR("Invalid width: 0x%x, mode 0x%x\n",
                    enBitWidth, enWorkMode);
                HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                return HI_ERR_CIPHER_INVALID_PARA;
            }
        }
    }
    else
    {
        *width = SYMC_DAT_WIDTH_128;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_symc_check_param(u32 hard_key, u32 iv_usage,
                                 CRYP_CIPHER_ALG_E enAlg,
                                 CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                 CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                                 CRYP_CIPHER_KEY_LENGTH_E enKeyLen,
                                 CRYP_CIPHER_SM1_ROUND_E sm1_round_num,
                                 symc_width *width)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    if ((HI_TRUE != hard_key)  && (HI_FALSE != hard_key))
    {
        HI_LOG_ERROR("Invalid hard_key: 0x%x\n", hard_key);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* set the bit width which depend on alg and mode */
    ret = kapi_symc_match_width(enWorkMode, enBitWidth, width);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintU32(enWorkMode);
        HI_LOG_PrintU32(enBitWidth);
        HI_LOG_PrintU32(*width);
        HI_LOG_PrintFuncErr(kapi_symc_match_width, ret);
        return ret;
    }

    ret = kapi_symc_width_check(enAlg, enWorkMode, *width, sm1_round_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintU32(enAlg);
        HI_LOG_PrintU32(enWorkMode);
        HI_LOG_PrintU32(*width);
        HI_LOG_PrintU32(sm1_round_num);
        HI_LOG_PrintFuncErr(kapi_symc_width_check, ret);
        return ret;
    }

    if (CIPHER_IV_CHANGE_ALL_PKG < iv_usage)
    {
        HI_LOG_ERROR("Invalid IV Change Flags: 0x%x\n", iv_usage);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

#ifdef HI_PRODUCT_AEAD_SUPPORT
    if ((CIPHER_IV_CHANGE_ALL_PKG == iv_usage)
        && ((CRYP_CIPHER_WORK_MODE_CCM == enWorkMode)
            || (CRYP_CIPHER_WORK_MODE_GCM == enWorkMode))
            )
    {
        HI_LOG_ERROR("Invalid IV Change Flags: 0x%x\n", iv_usage);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_symc_load_hard_key(u32 handle, u32 catype, u8 *key)
{
#if defined(ADVCA_FUNC_SUPPORT)
    s32 ret = HI_FAILURE;
    DRV_ADVCA_EXTFUNC_PARAM_S stADVCAFuncParam = {0};
    ADVCA_EXPORT_FUNC_S  *s_pAdvcaFunc = HI_NULL;

    crypto_memset(&stADVCAFuncParam, sizeof(stADVCAFuncParam), 0, sizeof(stADVCAFuncParam));
    stADVCAFuncParam.enCAType = catype;
    stADVCAFuncParam.AddrID = handle;
    /* Ignore evenOrOdd value here */
    stADVCAFuncParam.EvenOrOdd = 0;
    stADVCAFuncParam.pu8Data = key;
    stADVCAFuncParam.bIsDeCrypt = HI_TRUE;
    stADVCAFuncParam.enTarget = HI_UNF_ADVCA_CA_TARGET_MULTICIPHER;

    ret = HI_DRV_MODULE_GetFunction(HI_ID_CA, (HI_VOID**)&s_pAdvcaFunc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(HI_DRV_MODULE_GetFunction, ret);
        return ret;
    }
    if ((NULL == s_pAdvcaFunc) || (NULL == s_pAdvcaFunc->pfnAdvcaCrypto))
    {
        HI_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    ret = (s_pAdvcaFunc->pfnAdvcaCrypto)(stADVCAFuncParam);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(s_pAdvcaFunc->pfnAdvcaCrypto, ret);
        return ret;
    }

#endif
    return HI_SUCCESS;
}
static s32 kapi_symc_check_ccm_gcm_taglen(CRYP_CIPHER_ALG_E enAlg, CRYP_CIPHER_WORK_MODE_E enWorkMode, u32 tlen)
{
    HI_LOG_CHECK_PARAM(CRYP_CIPHER_ALG_AES != enAlg);

    if (CRYP_CIPHER_WORK_MODE_CCM == enWorkMode)
    {
        /* the parameter t denotes the octet length of T(tag)
         * t is an element of  { 4, 6, 8, 10, 12, 14, 16}
         * here t is pConfig->u32TagLen
         */
        if ((tlen & 0x01)
            || (AES_CCM_MIN_TAG_LEN > tlen)
            || (AES_CCM_MAX_TAG_LEN < tlen))
        {
            HI_LOG_ERROR("Invalid ccm tag len, tlen = 0x%x.\n", tlen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    else if (CRYP_CIPHER_WORK_MODE_GCM == enWorkMode)
    {
        if ((AES_GCM_MIN_TAG_LEN > tlen) || (AES_GCM_MAX_TAG_LEN < tlen))
        {
            HI_LOG_ERROR("Invalid gcm tag len, tlen = 0x%x.\n", tlen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    else
    {
            HI_LOG_ERROR("Aes with invalid work mode 0x%x for check tag lenth.\n", enWorkMode);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

s32 kapi_symc_config(u32 id,
                    u32 hard_key,
                    CRYP_CIPHER_ALG_E enAlg,
                    CRYP_CIPHER_WORK_MODE_E enWorkMode,
                    CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                    CRYP_CIPHER_KEY_LENGTH_E enKeyLen,
                    CRYP_CIPHER_SM1_ROUND_E sm1_round_num,
                    u8 *fkey, u8 *skey,
                    u8 *iv, u32 ivlen, u32 iv_usage,
                    compat_addr aad, u32 alen, u32 tlen)
{
    s32 ret = HI_FAILURE;
    kapi_symc_ctx *ctx = HI_NULL;
    symc_width width = SYMC_DAT_WIDTH_COUNT;
    u32 softId = 0;
    u32 byca = HI_FALSE;
    u32 catype = 0;
    u32 klen = enKeyLen;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == fkey);
    HI_LOG_CHECK_PARAM(MAX_AEAD_A_LEN < alen);
    HI_LOG_CHECK_PARAM(ADDR_L32(aad) + alen < alen);

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);

    /***
    hard_key: bit[0~7]  flag of hard key or not
              bit[8~31] ca type
    */
    byca = hard_key & 0xFF;
    catype = hard_key >> BITS_IN_BYTE;

    ret = kapi_symc_check_param(byca, iv_usage, enAlg, enWorkMode,
        enBitWidth, enKeyLen, sm1_round_num, &width);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("enAlg 0x%x, enWorkMode 0x%x\n", enAlg, enWorkMode);
        HI_LOG_PrintFuncErr(kapi_symc_check_param, ret);
        return ret;
    }

    KAPI_SYMC_LOCK();

    /* Destroy the last attached instance of Symmetric cipher engine */
    if ((HI_NULL != ctx->func) && (HI_NULL != ctx->func->destroy))
    {
        (void)ctx->func->destroy(ctx->cryp_ctx);
    }
    ctx->cryp_ctx = HI_NULL;

    /* Clone the function from template of symc engine*/
    ctx->func = cryp_get_symc_op(enAlg, enWorkMode);
    if (HI_NULL == ctx->func)
    {
        HI_LOG_ERROR("error, get symc function failed, enAlg %d, enWorkMode %d\n",
            enAlg, enWorkMode);
        HI_LOG_PrintFuncErr(cryp_get_symc_op, ret);
        KAPI_SYMC_UNLOCK();
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* null means can ignore the function */
    if (ctx->func->create)
    {
        /* Create a instance from template of engine */
        ctx->cryp_ctx = ctx->func->create(softId);
        if (HI_NULL == ctx->cryp_ctx)
        {
            KAPI_SYMC_UNLOCK();
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    /* set mode and alg */
    if (ctx->func->setmode)
    {
        ctx->func->setmode(ctx->cryp_ctx, ctx->func->alg, ctx->func->mode, width);
    }

    /* Set even key, may be also need set odd key */
    if (ctx->func->setkey)
    {
        if (HI_TRUE == byca)
        {
            CHECK_EXIT(ctx->func->setkey(ctx->cryp_ctx, HI_NULL, HI_NULL, &klen));
            CHECK_EXIT(kapi_symc_load_hard_key(id, catype, fkey));
        }
        else
        {
            CHECK_EXIT(ctx->func->setkey(ctx->cryp_ctx, fkey, skey, &klen));
        }
    }

    /* Set IV */
    if (ctx->func->setiv)
    {
        CHECK_EXIT(ctx->func->setiv(ctx->cryp_ctx, iv, ivlen, iv_usage));
    }

    /* set sm1 round num */
    if (ctx->func->setround)
    {
        CHECK_EXIT(ctx->func->setround(ctx->cryp_ctx, sm1_round_num));
    }

    /* Set AAD */
    if (ctx->func->setadd)
    {
        HI_LOG_INFO("set add, phy 0x%x, alen %d, tlen %d\n", ADDR_L32(aad), alen, tlen);
        CHECK_EXIT(kapi_symc_check_ccm_gcm_taglen(enAlg, enWorkMode, tlen));
        CHECK_EXIT(ctx->func->setadd(ctx->cryp_ctx, aad, alen, tlen));
    }

    /* save crtl */
    crypto_memset(&ctx->ctrl, sizeof(CRYP_CIPHER_CTRL_S), 0, sizeof(CRYP_CIPHER_CTRL_S));
    ctx->ctrl.bKeyByCA = byca;
    ctx->ctrl.enAlg = enAlg;
    ctx->ctrl.enBitWidth = enBitWidth;
    ctx->ctrl.enCaType = catype;
    ctx->ctrl.enKeyLen = enKeyLen;
    ctx->ctrl.enWorkMode = enWorkMode;
    ctx->ctrl.stChangeFlags.bit1IV = iv_usage;

    if (HI_NULL != iv)
    {
        if (AES_IV_SIZE < ivlen)
        {
            HI_LOG_ERROR("error, invalid iv len(0x%x).\n", ivlen);
            KAPI_SYMC_UNLOCK();
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        crypto_memcpy(ctx->ctrl.u32IV, AES_IV_SIZE, iv, ivlen);
    }
    if (HI_NULL != fkey)
    {
        if (AES_KEY_256BIT < klen)
        {
            HI_LOG_ERROR("error, invalid key len(0x%x).\n", klen);
            KAPI_SYMC_UNLOCK();
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        crypto_memcpy(ctx->ctrl.u32Key, AES_KEY_256BIT, fkey, klen);
    }

    ctx->config = HI_TRUE;

exit__:
    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_symc_unlock_get_config(u32 id, CRYP_CIPHER_CTRL_S *ctrl)
{
    kapi_symc_ctx *ctx = HI_NULL;
    u32 softId = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ctrl);

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);
    HI_LOG_CHECK_PARAM(HI_TRUE != ctx->config);

    crypto_memcpy(ctrl, sizeof(CRYP_CIPHER_CTRL_S), &ctx->ctrl, sizeof(CRYP_CIPHER_CTRL_S));

    HI_LOG_FuncExit();

    return HI_SUCCESS;
}

s32 kapi_symc_get_config(u32 id, CRYP_CIPHER_CTRL_S *ctrl)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    KAPI_SYMC_LOCK();

    ret = kapi_symc_unlock_get_config(id, ctrl);

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_symc_crypto(u32 id, compat_addr input,
                     compat_addr output, u32 length,
                     u32 operation, u32 oddkey, u32 last)
{
    s32 ret = HI_FAILURE;
    symc_node_usage usage;
    kapi_symc_ctx *ctx = HI_NULL;
    u32 softId = 0;

    HI_LOG_FuncEnter();

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);
    HI_LOG_CHECK_PARAM(ADDR_U64(input) + length < length);
    HI_LOG_CHECK_PARAM(ADDR_U64(output) + length < length);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func->crypto);
    HI_LOG_CHECK_PARAM(HI_TRUE != ctx->config);
    HI_LOG_CHECK_PARAM((0x00 != operation)&&(0x01 != operation));

    usage = SYMC_NODE_USAGE_NORMAL;

    KAPI_SYMC_LOCK();

    ret = ctx->func->crypto(ctx->cryp_ctx, operation, &input,
            &output, &length, &usage, 1, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ctx->func->crypto, ret);
        KAPI_SYMC_UNLOCK();
        return ret;
    }

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_symc_crypto_multi_start(kapi_symc_ctx *ctx, void *pkg, u32 pkg_num, u32 operation, u32 wait)
{
    s32 ret = HI_FAILURE;
    void *buf = HI_NULL, *temp = HI_NULL;
    compat_addr *input = HI_NULL;
    compat_addr *output = HI_NULL;
    symc_node_usage *usage = HI_NULL;
    CRYP_CIPHER_DATA_S pkg_tmp;
    u32 *length = HI_NULL;
    u32 size = 0;
    u32 i;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func->crypto);
    HI_LOG_CHECK_PARAM(HI_NULL == pkg);
    HI_LOG_CHECK_PARAM(MAX_PKG_NUMBER < pkg_num);
    HI_LOG_CHECK_PARAM(0x00 == pkg_num);

    /* size of input:output:usage:length */
    size = (sizeof(compat_addr) + sizeof(compat_addr) + sizeof(u32) + sizeof(u32)) * pkg_num;

    buf = crypto_malloc(size);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("Malloc for pkg failed.\n");
        HI_LOG_PrintFuncErr(crypto_malloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    temp = buf;
    input = (compat_addr *)temp;
    temp = (u8*)temp + sizeof(compat_addr) * pkg_num; /*buf + input*/
    output = (compat_addr *)temp;
    temp = (u8*)temp + sizeof(compat_addr) * pkg_num; /*buf + input + output*/
    usage = temp;
    temp = (u8*)temp + sizeof(u32) * pkg_num; /*buf + input + output + usage*/
    length = temp;

    /*Compute and check the nodes length*/
    for (i=0; i<pkg_num; i++)
    {
        /*copy node list from user space to kernel*/
        ret = crypto_copy_from_user(&pkg_tmp, (u8*)pkg + sizeof(CRYP_CIPHER_DATA_S) * i,
                sizeof(CRYP_CIPHER_DATA_S));
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("copy data from user fail!\n");
            HI_LOG_PrintFuncErr(crypto_copy_from_user, ret);
            crypto_free(buf);
            buf = HI_NULL;
            return ret;
        }

        if (pkg_tmp.u32SrcPhyAddr + pkg_tmp.u32ByteLength < pkg_tmp.u32ByteLength)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            crypto_free(buf);
            buf = HI_NULL;
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        if (pkg_tmp.u32DestPhyAddr + pkg_tmp.u32ByteLength < pkg_tmp.u32ByteLength)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            crypto_free(buf);
            buf = HI_NULL;
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        ADDR_U64(input[i]) = pkg_tmp.u32SrcPhyAddr;
        ADDR_U64(output[i]) = pkg_tmp.u32DestPhyAddr;
        length[i] = pkg_tmp.u32ByteLength;

#ifdef HI_PRODUCT_ODD_KEY_SUPPORT
#ifdef CHIP_SYMC_ODD_KEY_SUPPORT
        usage[i] = pkg_tmp.bOddKey ? SYMC_NODE_USAGE_ODD_KEY : SYMC_NODE_USAGE_EVEN_KEY;
#else
        if (HI_TRUE == pkg_tmp.bOddKey)
        {
            HI_LOG_ERROR("symc nonsupport odd key!\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            crypto_free(buf);
            buf = HI_NULL;
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        usage[i] = SYMC_NODE_USAGE_EVEN_KEY;
#endif
#endif
        HI_LOG_DEBUG("pkg %d, in 0x%x, out 0x%x, length 0x%x, usage 0x%x\n", i,
            ADDR_L32(input[i]), ADDR_L32(output[i]), length[i], usage[i]);
    }

    ret = ctx->func->crypto(ctx->cryp_ctx, operation, input,
            output, length, usage, pkg_num, wait);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_symc_crypto, ret);
        crypto_free(buf);
        buf = HI_NULL;
        return ret;
    }

    crypto_free(buf);
    buf = HI_NULL;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_crypto_multi(u32 id, void *pkg, u32 pkg_num, u32 operation, u32 last)
{
    s32 ret = HI_FAILURE;
    kapi_symc_ctx *ctx = HI_NULL;
    u32 softId = 0;

    HI_LOG_FuncEnter();

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_TRUE != ctx->config);
    HI_LOG_CHECK_PARAM((0x00 != operation) && (0x01 != operation));

    KAPI_SYMC_LOCK();

    ret = kapi_symc_crypto_multi_start(ctx, pkg, pkg_num, operation, HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_crypto_multi_start, ret);
        KAPI_SYMC_UNLOCK();
        return ret;
    }

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_aead_get_tag(u32 id, u32 tag[AEAD_TAG_SIZE_IN_WORD], u32 *taglen)
{
    s32 ret = HI_FAILURE;
    kapi_symc_ctx *ctx = HI_NULL;
    u32 softId = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == tag);
    HI_LOG_CHECK_PARAM(HI_NULL == taglen);
    HI_LOG_CHECK_PARAM(AES_CCM_MAX_TAG_LEN != *taglen);

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);

    KAPI_SYMC_LOCK();

    if (ctx->func->gettag)
    {
        ret = ctx->func->gettag(ctx->cryp_ctx, tag, taglen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cryp_aead_get_tag, ret);
            KAPI_SYMC_UNLOCK();
            return ret;
        }
    }

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*This function will be called by KLAD*/
s32 kapi_symc_setiv(u32 id, u8 *iv, u32 ivlen)
{
    s32 ret = HI_FAILURE;
    u32 softId = 0;
    kapi_symc_ctx *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == iv);
    HI_LOG_CHECK_PARAM(AES_IV_SIZE < ivlen);

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);

    KAPI_SYMC_LOCK();

    if ((HI_NULL != ctx->func) && (HI_NULL != ctx->func->setiv))
    {
        ret = ctx->func->setiv(ctx->cryp_ctx, iv, ivlen, CIPHER_IV_CHANGE_ONE_PKG);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintH32(ivlen);
            KAPI_SYMC_UNLOCK();
            return ret;
        }
    }

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_getiv(u32 id, u8 *iv, u32 *ivlen)
{
    s32 ret = HI_FAILURE;
    u32 softId = 0;
    kapi_symc_ctx *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == iv);
    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func->getiv);

    KAPI_SYMC_LOCK();

    ctx->func->getiv(ctx->cryp_ctx, iv, ivlen);

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_symc_cenc_decrypt(u32 id,
                    u8 *key,
                    u8 *iv,
                    u32 oddkey,
                    u32 inputphy,
                    u32 outputphy,
                    u32 bytelength,
                    u32 firstoffset,
                    void *subsample,
                    u32 number)
{
    s32 ret = HI_FAILURE;
    u32 softId = 0;
    kapi_symc_ctx *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    KAPI_SYMC_CHECK_HANDLE(id);
    softId = HI_HANDLE_GET_CHNID(id);
    ctx = &kapi_ctx[softId];
    CHECK_OWNER(&ctx->owner);

    KAPI_SYMC_LOCK();

    ret = cenc_decrypt(id, key, iv, oddkey, inputphy, outputphy,
                    bytelength, firstoffset, subsample, number);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_decrypt, ret);
        KAPI_SYMC_UNLOCK();
        return ret;
    }

    KAPI_SYMC_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/
