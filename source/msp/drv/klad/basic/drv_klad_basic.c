/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_basic.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad.h"
#include "hal_klad.h"
#include "drv_klad.h"
#include "hal_klad_basic.h"
#include "drv_klad_ioctl.h"
#include "drv_klad_basic.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static KLAD_DRV_ZONE s_klad_basic_drv_zone;

static HI_S32 DRV_KLAD_BASIC_SetBOOTKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32      ret = HI_FAILURE;
    HI_U32      state = 0x0;
    HI_U8       addr = 0x0;
    HI_U8       decrypt = 0x1;
    HI_UNF_KLAD_ALG_TYPE_E  alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    DRV_KLAD_TARGET_E       target = DRV_KLAD_TARGET_BUTT;

    KLAD_CHECK_POINTER(session);

    KLAD_CHECK_ATTR_FLAG(session);
    alg = session->instance.attr.alg;

    target = DRV_KLAD_GetTarget(session);
    KLAD_CHECK_PARAM(DRV_KLAD_TARGET_MULTI_CIPHER != target);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    KLAD_CHECK_CONTENT_KEY_FLAG(session);

    HAL_KLAD_SetDataIn(session->instance.content_key.key);

    HAL_KLAD_BOOTStart((HI_U8)alg, decrypt, addr, (HI_U8)target);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_BOOTGetState();
        KLAD_PrintErrorFunc(HAL_KLAD_BOOTGetState, state);
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState, ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SetSWKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32  ret = HI_FAILURE;
    HI_U32  state = 0x0;
    HI_U8   addr = 0x0;
    HI_U8   decrypt = 0x1;

    KLAD_CHECK_POINTER(session);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_SWStart(decrypt, addr);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_SWGetState();
        KLAD_PrintErrorFunc(HAL_KLAD_SWGetState, state);
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState, ret);
        return ret;
    }

    return HI_SUCCESS;
}
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
HI_S32 EXT_DRV_KLAD_BASIC_SetClearCWKey(EXT_CLEAR_CW_KLAD_PARA_S *stClearKey)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_TARGET_E  target = DRV_KLAD_TARGET_BUTT;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(stClearKey);
    KLAD_CHECK_EVENORODD(stClearKey->bOdd);
    KLAD_CHECK_ENGINE(stClearKey->enEngine);
    target = DRV_KLAD_GetTargetModID(stClearKey->handle);

    KLAD_CHECK_TARGET_MOD(target);

    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        KLAD_CHECK_TARGET_ADDR((HI_U8)HI_HANDLE_GET_CHNID(stClearKey->handle), DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        KLAD_CHECK_TARGET_ADDR((HI_U8)HI_HANDLE_GET_CHNID(stClearKey->handle), DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }
    DRV_KLAD_MutexLock();
#ifdef HI_TEE_SUPPORT
    ret = CA_TO_TA_SecEnDisable(HI_UNF_KLAD_TYPE_CLEARCW);
    if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(CA_TO_TA_SecEnEnable,ret);
    }
#endif
    HAL_KLAD_LockClearCw();
    HAL_KLAD_SetClearCwDataIn(stClearKey->u8Key);
    HAL_KLAD_CLEAR_CWStart((HI_U8)HI_HANDLE_GET_CHNID(stClearKey->handle), (HI_U8)stClearKey->bOdd,
                                (HI_U8)stClearKey->enEngine, target);
    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState, ret);
    }
    HAL_KLAD_UnLockClearCw();
#ifdef HI_TEE_SUPPORT
    ret = CA_TO_TA_SecEnEnable(HI_UNF_KLAD_TYPE_CLEARCW);
    if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(CA_TO_TA_SecEnDisable,ret);
    }
#endif
    DRV_KLAD_MutexUnLock();
    return ret;
}

static HI_S32 DRV_KLAD_BASIC_SetCLEARCWKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32                      ret = HI_FAILURE;
    HI_U8                       addr = 0x0;
    DRV_KLAD_TARGET_E           target = DRV_KLAD_TARGET_BUTT;
    HI_UNF_KLAD_TARGET_ENGINE_E engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;

    KLAD_CHECK_POINTER(session);

    target = DRV_KLAD_GetTarget(session);
    KLAD_CHECK_TARGET_MOD(target);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }

    KLAD_CHECK_ATTR_FLAG(session);
    engine = session->instance.attr.engine;
    KLAD_CHECK_ENGINE(engine);

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetClearCwDataIn(session->instance.content_key.key);
    HAL_KLAD_CLEAR_CWStart(addr, (HI_U8)session->instance.content_key.odd, (HI_U8)engine, (HI_U8)target);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState, ret);
        return ret;
    }

    return HI_SUCCESS;
}
#endif

static HI_S32 DRV_KLAD_BASIC_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32  ret = HI_FAILURE;

    KLAD_CHECK_POINTER(session);

    DRV_KLAD_MutexLock();
    switch (session->instance.attr.klad_type)
    {
        case HI_UNF_KLAD_TYPE_BLPK:
        {
            ret = DRV_KLAD_BASIC_SetBOOTKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_BASIC_SetBOOTKey,ret);
            }
            break;
        }

        case HI_UNF_KLAD_TYPE_SWPK:
        {
            ret = DRV_KLAD_BASIC_SetSWKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_BASIC_SetSWKey,ret);
            }
            break;
        }

        #if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
        case HI_UNF_KLAD_TYPE_CLEARCW:
        {
            #ifdef HI_TEE_SUPPORT
            ret = CA_TO_TA_SecEnDisable(session->instance.attr.klad_type);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(CA_TO_TA_SecEnEnable,ret);
            }
            #endif
            if (HI_SUCCESS == HAL_KLAD_LockClearCw())
            {
                ret = DRV_KLAD_BASIC_SetCLEARCWKey(handle, session);
                if(HI_SUCCESS != ret)
                {
                    KLAD_PrintErrorFunc(DRV_KLAD_BASIC_SetBOOTKey,ret);
                }
                HAL_KLAD_UnLockClearCw();
            }
            #ifdef HI_TEE_SUPPORT
            ret = CA_TO_TA_SecEnEnable(session->instance.attr.klad_type);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(CA_TO_TA_SecEnDisable,ret);
            }
            #endif
            break;
        }
        #endif
        default:
        {
            ret = HI_ERR_KLAD_NOT_SUPPORT;
            HI_ERR_KLAD("not support klad type %#x\n", session->instance.attr.klad_type);
            break;
        }
    }
    DRV_KLAD_MutexUnLock();

    return ret;
}

static HI_S32 DRV_KLAD_BASIC_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_CHECK_POINTER(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SetContentKey,ret);
        return ret;
    }

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        return ret;
    }

    ret = DRV_KLAD_BASIC_Crypto(session->instance.handle, session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_BASIC_Crypto,ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_BOOTGenEncKey(HI_VOID* arg)
{
    HI_S32                      ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S    *enc_key = HI_NULL;
    DRV_KLAD_SESSION            *session = HI_NULL;
    HI_UNF_KLAD_ALG_TYPE_E      alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    HI_U8                       decrypt = 0x0;
    HI_U32                      state = 0;

    KLAD_CHECK_POINTER(arg);

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        return ret;
    }

    KLAD_CHECK_ATTR_FLAG(session);
    alg = session->instance.attr.alg;
    KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    enc_key = (KLAD_CTL_ENC_CLEAR_KEY_S*)arg;
    HAL_KLAD_SetDataIn(enc_key->key.clear_key);
    HAL_KLAD_BOOTStart((HI_U8)alg, decrypt, 0, 0);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_BOOTGetState();
        KLAD_PrintErrorFunc(HAL_KLAD_BOOTGetState,state);
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState,ret);
        return ret;
    }

    HAL_KLAD_BOOTGetEncRslt(enc_key->key.enc_key);

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_SWGenEncKey(HI_VOID* arg)
{
    HI_S32                      ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S    *enc_key = HI_NULL;
    HI_U8                       decrypt = 0x0;
    HI_U32                      state = 0;

    KLAD_CHECK_POINTER(arg);

    enc_key = (KLAD_CTL_ENC_CLEAR_KEY_S*)arg;
    HAL_KLAD_SetDataIn(enc_key->key.clear_key);
    HAL_KLAD_SWStart(decrypt, 0);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_SWGetState();
        KLAD_PrintErrorFunc(HAL_KLAD_SWGetState,state);
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState,ret);
        return ret;
    }

    HAL_KLAD_SWGetEncRslt(enc_key->key.enc_key);

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_GenEncKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE klad_handle = HI_INVALID_HANDLE;
    KLAD_CTL_ENC_CLEAR_KEY_S *key = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    key = (KLAD_CTL_ENC_CLEAR_KEY_S *) arg;

    klad_handle = key->handle;

    ret = DRV_KLAD_GetSession(klad_handle, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    memcpy(session->instance.content_key.key, key->key.clear_key, HI_KLAD_KEY_LENGTH);
    session->instance.content_key_flag = HI_TRUE;

    DRV_KLAD_MutexLock();

    switch (session->instance.attr.klad_type)
    {
        case HI_UNF_KLAD_TYPE_BLPK:
        {
            ret = DRV_KLAD_BASIC_BOOTGenEncKey(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_BASIC_BOOTGenEncKey,ret);
            }
            break;
        }

        case HI_UNF_KLAD_TYPE_SWPK:
        {
            ret = DRV_KLAD_BASIC_SWGenEncKey(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_BASIC_SWGenEncKey,ret);
            }
            break;
        }

        default:
        {
            ret = HI_ERR_KLAD_NOT_SUPPORT;
            KLAD_ERR_PrintHex(session->instance.attr.klad_type);
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SUPPORT);
            break;
        }
    }

    DRV_KLAD_MutexUnLock();

    KLAD_FUNC_EXIT();
    return ret;
}

static HI_S32 DRV_KLAD_BASIC_WIDEVINEGetDecFlag(HI_VOID* arg)
{
    KLAD_CTL_WIDEVINE_DEC_FLAG_S *ctl_handle;

    KLAD_CHECK_POINTER(arg);

    ctl_handle = (KLAD_CTL_WIDEVINE_DEC_FLAG_S*)arg;
    ctl_handle->flag = HAL_KLAD_WIDEVINEGetDecFlag();

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_BASIC_STBROOTKEYSendToCipher(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    DRV_KLAD_TARGET_E target = 0;
    HI_HANDLE *klad_handle = HI_NULL;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(arg);

    klad_handle = (HI_HANDLE *)arg;

    ret = DRV_KLAD_GetSession(*klad_handle, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);

    target = DRV_KLAD_GetTarget(session);
    KLAD_CHECK_PARAM(target != DRV_KLAD_TARGET_MULTI_CIPHER);

    HAL_KLAD_STB_ROOTKEYStart(addr);
    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return ret;
}

static DRV_KLAD_IOCTL_S s_klad_basic_ioctl[] =
{
    {CMD_KLAD_SET_CONTENT_KEY,       DRV_KLAD_BASIC_SetContentKey},
    {CMD_KLAD_GEN_ENC_KEY,           DRV_KLAD_BASIC_GenEncKey},
    {CMD_KLAD_WIDEVINE_GET_DEC_FLAG, DRV_KLAD_BASIC_WIDEVINEGetDecFlag},
    {CMD_KLAD_STBROOTKEY2CIPHER,     DRV_KLAD_BASIC_STBROOTKEYSendToCipher},
};

static HI_S32 DRV_KLAD_BASIC_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(arg);

    cmd_num = sizeof(s_klad_basic_ioctl) / sizeof(s_klad_basic_ioctl[0]);
    for (loop = 0; loop < cmd_num; loop++)
    {
        if (s_klad_basic_ioctl[loop].cmd == cmd)
        {
            ret = s_klad_basic_ioctl[loop].f_driver_cmd_process(arg);
            if (HI_SUCCESS != ret)
            {
                KLAD_ERR_PrintHex(cmd);
                KLAD_PrintErrorCode(ret);
                KLAD_FUNC_EXIT();
                return ret;
            }

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SUPPORT);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_SUPPORT;
}

HI_S32 DRV_KLAD_BASIC_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    memset(&s_klad_basic_drv_zone, 0, sizeof(KLAD_DRV_ZONE));

    s_klad_basic_drv_zone.ca = CA_ID_BASIC;
    s_klad_basic_drv_zone.ioctl = DRV_KLAD_BASIC_Ioctl;
    s_klad_basic_drv_zone.setsecen = HAL_KLAD_BASIC_SetBasicKladSecen;

    ret = DRV_KLAD_Register(&s_klad_basic_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    HAL_KLAD_BASIC_SetBasicKladSecen();

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_BASIC_Exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_UnRegister(&s_klad_basic_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_FUNC_EXIT();
        return ret;
    }

    memset(&s_klad_basic_drv_zone, 0, sizeof(KLAD_DRV_ZONE));

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
