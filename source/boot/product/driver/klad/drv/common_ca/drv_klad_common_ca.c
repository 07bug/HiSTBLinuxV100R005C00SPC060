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
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_common_ca.h"
#include "hal_klad_basic_reg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

KLAD_DRV_ZONE g_klad_common_ca_drv_zone;
#define DRV_KLAD_MAX_DEMUX_ADDR_CNT  32
#define DRV_KLAD_MAX_CIPHER_ADDR_CNT 8

static HI_S32 DRV_KLAD_COMMON_CA_SetR2RKey(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 addr = 0;
    HI_UNF_KLAD_ALG_TYPE_E alg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    HI_UNF_KLAD_TARGET_ENGINE_E engine = HI_UNF_KLAD_TARGET_ENGINE_BUTT;
    DRV_KLAD_TARGET_E target = DRV_KLAD_TARGET_BUTT;
    HI_UNF_KLAD_LEVEL_E level = HI_UNF_KLAD_LEVEL1;
    HI_U8 index = 0;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (session->attr_flag == HI_FALSE)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    alg = session->attr.alg;

    target = DRV_KLAD_GetTarget(session);
    if (DRV_KLAD_TARGET_MULTI_CIPHER != target)
    {
        HI_ERR_KLAD("invalid target: %d\n", target);
        return HI_ERR_KLAD_INVALID_PARA;
    }

    engine = session->attr.engine;

    addr = HI_HANDLE_GET_CHNID(session->target);
    if (DRV_KLAD_TARGET_DEMUX == target)
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_DEMUX_ADDR_CNT);
    }
    else
    {
        DRV_KLAD_CHECK_TARGET_ADDR(addr, DRV_KLAD_MAX_CIPHER_ADDR_CNT);
    }

    level = HAL_KLAD_COMMON_CA_GetR2RLevel();
    DRV_KLAD_CHECK_LEVEL(level);

    for (index = 0; index < (level - 1); index++)
    {
        if (HI_TRUE != session->session_key_flag[index])
        {
            HI_ERR_KLAD("Not set level%d session key to handle %#x\n", index + 1, session->handle);
            return HI_ERR_KLAD_NOT_SET_ATTR;
        }

        HAL_KLAD_SetDataIn(session->session_key[index].key);
        HAL_KLAD_COMMON_CA_R2RStart(index, (HI_U8)alg, addr, 0, (HI_U8)engine, (HI_U8)target);

        ret = HAL_KLAD_CheckState();
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
    }

    HAL_KLAD_SetDataIn(session->content_key.key);
    HAL_KLAD_COMMON_CA_R2RStart(level - 1, (HI_U8)alg, addr, (HI_U8)session->content_key.odd, (HI_U8)engine, (HI_U8)target);

    ret = HAL_KLAD_CheckState();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


static HI_S32 DRV_KLAD_COMMON_CA_Crypto(HI_HANDLE handle, DRV_KLAD_SESSION* session)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(session);

    if (session->attr_flag == HI_FALSE)
    {
        HI_ERR_KLAD("Not set attr to handle %#x\n", session->handle);
        return HI_ERR_KLAD_NOT_SET_ATTR;
    }

    mutex_lock(&g_klad_mutex);
    switch (session->attr.klad_type)
    {
        case HI_UNF_KLAD_COMMON_CA_TYPE_R2R:
        {
            ret = DRV_KLAD_COMMON_CA_SetR2RKey(handle, session);
            break;
        }
        default:
        {
            ret = HI_ERR_KLAD_NOT_SUPPORT;
            HI_ERR_KLAD("not support klad type %#x\n", session->attr.klad_type);
            break;
        }
    }
    mutex_unlock(&g_klad_mutex);

    KLAD_FUNC_EXIT();
    return ret;
}

static HI_S32 DRV_KLAD_COMMON_CA_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    DRV_KLAD_SESSION* session = HI_NULL;

    KLAD_FUNC_ENTER();

    DRV_KLAD_CHECK_NULL_PTR(arg);

    ret = DRV_KLAD_SetContentKey(arg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_SetContentKey failed. [%x]\n", ret);
        return ret;
    }

    ret = DRV_KLAD_GetSession(*(HI_HANDLE*)arg, &session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_GetSession failed. [%x]\n", ret);
        return ret;
    }

    ret = DRV_KLAD_COMMON_CA_Crypto(*(HI_HANDLE*)arg, session);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("DRV_KLAD_COMMON_CA_Crypto failed. [%x]\n", ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static DRV_KLAD_IOCTL_S g_klad_common_ca_ioctl[] =
{
    {CMD_KLAD_SET_CONTENT_KEY,  DRV_KLAD_COMMON_CA_SetContentKey},
};

static HI_S32 DRV_KLAD_COMMON_CA_Ioctl(HI_U32 cmd, HI_VOID* arg)
{
    HI_U32 cmd_num = 0;
    HI_U32 loop = 0;
    HI_S32 ret = HI_FAILURE;

    DRV_KLAD_CHECK_NULL_PTR(arg);

    cmd_num = sizeof(g_klad_common_ca_ioctl) / sizeof(g_klad_common_ca_ioctl[0]);

    for (loop = 0; loop < cmd_num; loop++)
    {
        if (g_klad_common_ca_ioctl[loop].cmd == cmd)
        {
            ret = g_klad_common_ca_ioctl[loop].f_driver_cmd_process(arg);
            if (HI_SUCCESS != ret)
            {
                return ret;
            }

            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    return HI_ERR_KLAD_NOT_SUPPORT;
}

HI_S32 DRV_KLAD_COMMON_CA_Init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    HI_BOOL bSecure;

    KLAD_FUNC_ENTER();

    ret = HI_DRV_SYS_GetCPUSecureMode(&bSecure);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("HI_DRV_SYS_GetCPUSecureMode failed. [%#x]\n", ret);
    }

    if (bSecure)
    {
        HAL_KLAD_WriteReg(KL_C5_SEC_EN, 0x1f);
    }

    memset(&g_klad_common_ca_drv_zone, 0x0, sizeof (KLAD_DRV_ZONE));

    g_klad_common_ca_drv_zone.ca = CA_ID_COMMON_CA;
    g_klad_common_ca_drv_zone.ioctl = DRV_KLAD_COMMON_CA_Ioctl;

    ret = DRV_KLAD_Register(&g_klad_common_ca_drv_zone);
    if (HI_SUCCESS != ret)
    {
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
        return ret;
    }

    memset(&g_klad_common_ca_drv_zone, 0x00, sizeof (KLAD_DRV_ZONE));

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
