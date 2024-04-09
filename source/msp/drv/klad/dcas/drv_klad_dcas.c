/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_dcas.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-03-21
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad_dcas.h"
#include "hal_klad.h"
#include "hal_klad_dcas.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_dcas.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static KLAD_DRV_ZONE g_klad_dcas_drv_zone;

static HI_VOID DRV_KLAD_DCAS_SetKladSecEN(HI_VOID)
{
    return;
}

static HI_S32 DRV_KLAD_DCAS_CheckHalError(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0;

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        state = HAL_KLAD_DCAS_GetState();
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState,ret);
        KLAD_PrintErrorFunc(HAL_KLAD_DCAS_GetState,state);
    }

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_SetRkdKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_CHECK_POINTER(session);

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_DCAS_RKDStart();

    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_DCAS_CheckHalError,ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_DCAS_SetK30Key(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    HI_UNF_KLAD_TARGET_ENGINE_E engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;

    KLAD_CHECK_POINTER(session);

    KLAD_CHECK_ATTR_FLAG(session);
    alg = session->instance.attr.alg;
    KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    target = DRV_KLAD_GetTarget(session);
    KLAD_CHECK_TARGET_MOD(target);

    engine = session->instance.attr.engine;
    KLAD_CHECK_ENGINE(engine);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }

    level = HAL_KLAD_DCAS_K30GetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);
        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_DCAS_K30Start(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);

        ret = DRV_KLAD_DCAS_CheckHalError();
        if (ret != HI_SUCCESS)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_DCAS_CheckHalError,ret);
            return ret;
        }
    }

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_DCAS_K30Start(index, (HI_U8)alg, addr, (HI_U8)session->instance.content_key.odd, (HI_U8)engine, (HI_U8)target);

    ret = DRV_KLAD_DCAS_CheckHalError();

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_CHECK_POINTER(session);

    DRV_KLAD_MutexLock();

    switch (session->instance.attr.klad_type)
    {
        case HI_UNF_KLAD_DCAS_TYPE_RKD:
        {
            ret = DRV_KLAD_DCAS_SetRkdKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_DCAS_SetRkdKey,ret);
            }
            break;
        }
        case HI_UNF_KLAD_DCAS_TYPE_K30:
        {
            ret = DRV_KLAD_DCAS_SetK30Key(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_DCAS_SetK30Key,ret);
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

    return ret;
}

static HI_S32 DRV_KLAD_DCAS_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_CHECK_POINTER(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (HI_SUCCESS != ret)
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

    ret = DRV_KLAD_DCAS_Crypto(*(HI_HANDLE *)arg, session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_DCAS_Crypto,ret);
        return ret;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_DCAS_K30GenDaNonce(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_DA_NONCE_S *da_nonce;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    DRV_KLAD_SESSION *session = HI_NULL;
    HI_U32 state = 0;

    KLAD_CHECK_POINTER(arg);

    da_nonce = (KLAD_CTL_DA_NONCE_S*)arg;

    ret = DRV_KLAD_GetSession(da_nonce->handle, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        return ret;
    }

    KLAD_CHECK_ATTR_FLAG(session);
    alg = session->instance.attr.alg;
    KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    KLAD_CHECK_SESSION_KEY_FLAG(session,HI_UNF_KLAD_LEVEL1);
    HAL_KLAD_SetDataIn(session->instance.session_key[HI_UNF_KLAD_LEVEL1].key);
    HAL_KLAD_DCAS_K30Start((HI_U8)HI_UNF_KLAD_LEVEL1, (HI_U8)alg, 0, 0, 0, 0);
    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_DCAS_CheckHalError,ret);
        return ret;
    }

    HAL_KLAD_SetDataIn(da_nonce->nonce);
    HAL_KLAD_DCAS_K30Start((HI_U8)HI_UNF_KLAD_LEVEL4, (HI_U8)alg, 0, 0, 0, 0);

    ret = DRV_KLAD_DCAS_CheckHalError();
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_DCAS_CheckHalError,ret);
        return ret;
    }

    state = HAL_KLAD_DCAS_K30GetDaNonceState();
    if (state != 0x1)
    {
        KLAD_PrintErrorFunc(HAL_KLAD_DCAS_K30GetDaNonceState,state);
        KLAD_PrintErrorCode(HI_ERR_KLAD_KEY_NOT_READY);
        return HI_ERR_KLAD_KEY_NOT_READY;
    }

    HAL_KLAD_DCAS_K30GetDaNonce(da_nonce->da_nonce);

    return HI_SUCCESS;
}

static DRV_KLAD_IOCTL_S g_klad_dcas_ioctl[] =
{
    {CMD_KLAD_SET_CONTENT_KEY,  DRV_KLAD_DCAS_SetContentKey},
    {CMD_KLAD_GEN_K30_DA_NONCE, DRV_KLAD_DCAS_K30GenDaNonce},
};

static HI_S32 DRV_KLAD_DCAS_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    cmd_num = sizeof(g_klad_dcas_ioctl) / sizeof(g_klad_dcas_ioctl[0]);
    for (loop=0; loop<cmd_num; loop++)
    {
        if (g_klad_dcas_ioctl[loop].cmd == cmd)
        {
            ret = g_klad_dcas_ioctl[loop].f_driver_cmd_process(arg);
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

    KLAD_ERR_PrintHex(cmd);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SUPPORT);
    KLAD_FUNC_EXIT();
    return HI_ERR_KLAD_NOT_SUPPORT;
}

HI_S32 DRV_KLAD_DCAS_FuncInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    memset(&g_klad_dcas_drv_zone, 0x00, sizeof(KLAD_DRV_ZONE));

    g_klad_dcas_drv_zone.ca = CA_ID_DCAS;
    g_klad_dcas_drv_zone.ioctl = DRV_KLAD_DCAS_Ioctl;
    g_klad_dcas_drv_zone.setsecen = DRV_KLAD_DCAS_SetKladSecEN;

    ret = DRV_KLAD_Register(&g_klad_dcas_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_Register,ret);
        return ret;
    }

    DRV_KLAD_DCAS_SetKladSecEN();

    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_DCAS_FuncExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_KLAD_UnRegister(&g_klad_dcas_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_UnRegister,ret);
        return ret;
    }

    memset(&g_klad_dcas_drv_zone, 0x00, sizeof(KLAD_DRV_ZONE));

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
