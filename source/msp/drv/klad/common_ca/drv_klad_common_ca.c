/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_common_ca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_module.h"
#include "hi_unf_klad_common_ca.h"
#include "hal_klad.h"
#include "hal_klad_common_ca.h"
#include "hal_klad_basic_reg.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_common_ca.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

KLAD_DRV_ZONE g_klad_common_ca_drv_zone;


static HI_S32 DRV_KLAD_COMMON_CA_CheckHalError(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 state = 0;

    ret = HAL_KLAD_CheckState();
    if (ret != HI_SUCCESS)
    {
        state = HAL_KLAD_COMMON_CA_GetState();
        KLAD_PrintErrorFunc(HAL_KLAD_CheckState,ret);
        KLAD_PrintErrorFunc(HAL_KLAD_COMMON_CA_GetState,state);
    }

    return ret;
}

static HI_S32 DRV_KLAD_COMMON_CA_SetCSA2Key(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;

    KLAD_CHECK_POINTER(session);

    KLAD_CHECK_ATTR_FLAG(session);

    alg = session->instance.attr.alg;
    KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);

    level = HAL_KLAD_COMMON_CA_CSA2GetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);
        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_COMMON_CA_CSA2Start(index, (HI_U8)alg, addr, 0);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_CheckHalError,ret);
            return ret;
        }
    }

    KLAD_CHECK_CONTENT_KEY_FLAG(session);

    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_COMMON_CA_CSA2Start(level - 1, alg, addr, (HI_U8)session->instance.content_key.odd);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetCSA3Key(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
    HI_U8 level = 0;
    HI_U8 index = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;

    KLAD_CHECK_POINTER(session);

    KLAD_CHECK_ATTR_FLAG(session);

    alg = session->instance.attr.alg;
    KLAD_CHECK_ALG(alg, HI_UNF_KLAD_ALG_TYPE_BUTT);

    addr = HI_HANDLE_GET_CHNID(session->instance.target);
    KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);

    level = HAL_KLAD_COMMON_CA_CSA3GetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);

        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_COMMON_CA_CSA3Start(index, (HI_U8)alg, addr, 0);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_CheckHalError,ret);
            return ret;
        }
    }

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_COMMON_CA_CSA3Start(level-1, alg, addr, (HI_U8)session->instance.content_key.odd);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetSPKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_SPGetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);

        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_COMMON_CA_SPStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);
        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_CheckHalError,ret);
            return ret;
        }
    }

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_COMMON_CA_SPStart(level - 1, (HI_U8)alg, addr, (HI_U8)session->instance.content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetR2RKey(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_R2RGetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);
        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_COMMON_CA_R2RStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);
        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (ret != HI_SUCCESS)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_CheckHalError,ret);
            return ret;
        }
    }

    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_COMMON_CA_R2RStart(level - 1, (HI_U8)alg, addr, (HI_U8)session->instance.content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_SetMISCKey(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0x0;
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

    level = HAL_KLAD_COMMON_CA_MISCGetLevel();
    KLAD_CHECK_LEVEL(level);

    for (index = 0; index < level - 1; index++)
    {
        KLAD_CHECK_SESSION_KEY_FLAG(session,index);
        HAL_KLAD_SetDataIn(session->instance.session_key[index].key);
        HAL_KLAD_COMMON_CA_MISCStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);

        ret = DRV_KLAD_COMMON_CA_CheckHalError();
        if (HI_SUCCESS != ret)
        {
            KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_CheckHalError,ret);
            return ret;
        }
    }
    KLAD_CHECK_CONTENT_KEY_FLAG(session);
    HAL_KLAD_SetDataIn(session->instance.content_key.key);
    HAL_KLAD_COMMON_CA_MISCStart(level - 1, (HI_U8)alg, addr, (HI_U8)session->instance.content_key.odd, (HI_U8)engine, (HI_U8)target);

    return DRV_KLAD_COMMON_CA_CheckHalError();
}

static HI_S32 DRV_KLAD_COMMON_CA_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(session);

    DRV_KLAD_MutexLock();

    switch (session->instance.attr.klad_type)
    {
        case HI_UNF_KLAD_COMMON_CA_TYPE_CSA2:
        {
            ret = DRV_KLAD_COMMON_CA_SetCSA2Key(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_SetCSA2Key,ret);
            }
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_CSA3:
        {
            ret = DRV_KLAD_COMMON_CA_SetCSA3Key(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_SetCSA3Key,ret);
            }
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_SP:
        {
            ret = DRV_KLAD_COMMON_CA_SetSPKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_SetSPKey,ret);
            }
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_R2R:
        {
            ret = DRV_KLAD_COMMON_CA_SetR2RKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_SetR2RKey,ret);
            }
            break;
        }

        case HI_UNF_KLAD_COMMON_CA_TYPE_MISC:
        {
            ret = DRV_KLAD_COMMON_CA_SetMISCKey(handle, session);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_SetMISCKey,ret);
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

static HI_S32 DRV_KLAD_COMMON_CA_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION *session = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SetContentKey,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    ret = DRV_KLAD_GetSession(*(HI_HANDLE *)arg, &session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    ret = DRV_KLAD_COMMON_CA_Crypto(*(HI_HANDLE *)arg, session);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_COMMON_CA_Crypto,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static DRV_KLAD_IOCTL_S s_klad_IO_ctl[] =
{
    {CMD_KLAD_SET_CONTENT_KEY,  DRV_KLAD_COMMON_CA_SetContentKey},
};

static HI_S32 DRV_KLAD_COMMON_CA_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    cmd_num = sizeof(s_klad_IO_ctl) / sizeof(s_klad_IO_ctl[0]);
    for (loop=0; loop<cmd_num; loop++)
    {
        if (s_klad_IO_ctl[loop].cmd == cmd)
        {
            ret = s_klad_IO_ctl[loop].f_driver_cmd_process(arg);
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


HI_S32 DRV_KLAD_COMMON_CA_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    DRV_KLAD_COMMON_CA_SetKladSecEN();

    memset(&g_klad_common_ca_drv_zone, 0x0, sizeof (KLAD_DRV_ZONE));

    g_klad_common_ca_drv_zone.ca = CA_ID_COMMON_CA;
    g_klad_common_ca_drv_zone.ioctl = DRV_KLAD_COMMON_CA_Ioctl;
    g_klad_common_ca_drv_zone.setsecen = DRV_KLAD_COMMON_CA_SetKladSecEN;

    ret = DRV_KLAD_Register(&g_klad_common_ca_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_Register,ret);
        KLAD_FUNC_EXIT();
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_COMMON_CA_Exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    ret = DRV_KLAD_UnRegister(&g_klad_common_ca_drv_zone);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_UnRegister,ret);
        return ret;
    }

    memset(&g_klad_common_ca_drv_zone, 0x0, sizeof (KLAD_DRV_ZONE));

    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
