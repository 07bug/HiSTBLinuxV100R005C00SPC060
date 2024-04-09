/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_advca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_drv_struct.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "hi_unf_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 g_klad_fd = -1;
HI_S32 g_klad_init_nm = -1;

HI_S32 HI_UNF_KLAD_Init(HI_VOID)
{
    HI_S32 dev_fd = 0;

    KLAD_FUNC_ENTER();

    if (g_klad_init_nm > 0)
    {
        g_klad_init_nm++;
        KLAD_FUNC_EXIT();
        return HI_SUCCESS;
    }

    dev_fd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR, 0);
    if (dev_fd < 0)
    {
        KLAD_PrintErrorCode(HI_ERR_KLAD_OPEN_ERR);
        KLAD_FUNC_EXIT();
        return HI_ERR_KLAD_OPEN_ERR;
    }

    g_klad_init_nm = 1;
    g_klad_fd = dev_fd;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_DeInit(HI_VOID)
{
    KLAD_FUNC_ENTER();

    if (g_klad_init_nm > 0)
    {
        g_klad_init_nm--;
    }

    if (g_klad_init_nm != 0)
    {
        KLAD_FUNC_EXIT();
        return HI_SUCCESS;
    }

    close(g_klad_fd);
    g_klad_fd   = -1;
    g_klad_init_nm = -1;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Create(HI_HANDLE* phKlad)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_HANDLE_S ctl_handle;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(phKlad);

    memset(&ctl_handle, 0x00, sizeof(KLAD_CTL_HANDLE_S));

    ret = ioctl(g_klad_fd, CMD_KLAD_CREATE, &ctl_handle);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    *phKlad = ctl_handle.create_handle;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Destroy(HI_HANDLE hKlad)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);

    KLAD_CHECK_HANDLE(hKlad);

    ret = ioctl(g_klad_fd, CMD_KLAD_DESTORY, &hKlad);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Attach(HI_HANDLE hKlad, HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);

    memset(&target, 0x00, sizeof(KLAD_CTL_TARGET_S));
    target.handle = hKlad;
    target.target = hTarget;
    KLAD_CHECK_HANDLE(target.handle);
    KLAD_CHECK_TARGET(target.target);

    ret = ioctl(g_klad_fd, CMD_KLAD_ATTACH, &target);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_Detach(HI_HANDLE hKlad, HI_HANDLE hTarget)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S target;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);

    memset(&target, 0x00, sizeof(KLAD_CTL_TARGET_S));
    target.handle = hKlad;
    target.target = hTarget;
    KLAD_CHECK_HANDLE(target.handle);
    KLAD_CHECK_TARGET(target.target);

    ret = ioctl(g_klad_fd, CMD_KLAD_DETACH, &target);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstAttr);

    memset(&attr, 0x00, sizeof(KLAD_CTL_ATTR_S));
    attr.handle = hKlad;
    attr.attr.klad_type = pstAttr->u32KladType;
    attr.attr.alg = pstAttr->enAlg;
    attr.attr.engine = pstAttr->enEngine;

    KLAD_CHECK_HANDLE(attr.handle);
    KLAD_CHECK_ALG(attr.attr.alg,HI_UNF_KLAD_ALG_TYPE_BUTT);
    KLAD_CHECK_ENGINE(attr.attr.engine);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GetAttr(HI_HANDLE hKlad, HI_UNF_KLAD_ATTR_S* pstAttr)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S attr;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstAttr);

    memset(&attr, 0x00, sizeof(KLAD_CTL_ATTR_S));
    attr.handle = hKlad;
    KLAD_CHECK_HANDLE(attr.handle);

    ret = ioctl(g_klad_fd, CMD_KLAD_GET_ATTR, &attr);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    pstAttr->enAlg = attr.attr.alg;
    pstAttr->enEngine = attr.attr.engine;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SetSessionKey(HI_HANDLE hKlad, HI_UNF_KLAD_SESSION_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_SESSION_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstKey);

    memset(&key, 0x00, sizeof(KLAD_CTL_SESSION_KEY_S));
    key.handle = hKlad;
    key.session_key.level = pstKey->enLevel;
    memcpy(key.session_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECK_HANDLE(key.handle);
    KLAD_CHECK_LEVEL(key.session_key.level);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_SESSION_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}


HI_S32 HI_UNF_KLAD_SetContentKey(HI_HANDLE hKlad, HI_UNF_KLAD_CONTENT_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstKey);

    memset(&key, 0x00, sizeof(KLAD_CTL_CONTENT_KEY_S));
    key.handle = hKlad;
    key.content_key.odd = pstKey->bOdd;
    memcpy(key.content_key.key, pstKey->au8Key, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECK_HANDLE(key.handle);
    KLAD_CHECK_EVENORODD(key.content_key.odd);

    ret = ioctl(g_klad_fd, CMD_KLAD_SET_CONTENT_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_GenerateEncKey(HI_HANDLE hKlad, HI_UNF_KLAD_ENC_KEY_S* pstKey)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ENC_CLEAR_KEY_S key;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pstKey);

    memset(&key, 0x00, sizeof(KLAD_CTL_ENC_CLEAR_KEY_S));
    key.handle = hKlad;
    memcpy(key.key.clear_key, pstKey->au8ClearKey, HI_UNF_KLAD_MAX_KEY_LEN);
    KLAD_CHECK_HANDLE(key.handle);

    ret = ioctl(g_klad_fd, CMD_KLAD_GEN_ENC_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    memcpy(pstKey->au8EncKey, &key.key.enc_key, HI_UNF_KLAD_MAX_KEY_LEN);

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HI_UNF_KLAD_SendSTBRootkeyToCipher(HI_HANDLE hKlad)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_INIT(g_klad_init_nm);

    KLAD_CHECK_HANDLE(hKlad);
    ret = ioctl(g_klad_fd, CMD_KLAD_STBROOTKEY2CIPHER, &hKlad);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

#if 0 // 2017/02/13 - 14:24:57,
HI_S32 HI_UNF_KLAD_WIDEVINEGetDecFlag(HI_HANDLE hKlad, HI_U32 *pu32Flag)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_WIDEVINE_DEC_FLAG_S ctl_handle;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_INIT(g_klad_init_nm);
    KLAD_CHECK_POINTER(pu32Flag);

    memset(&ctl_handle, 0x00, sizeof(KLAD_CTL_WIDEVINE_DEC_FLAG_S));
    ctl_handle.handle = hKlad;

    ret = ioctl(g_klad_fd, CMD_KLAD_WIDEVINE_GET_DEC_FLAG, &ctl_handle);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(ioctl,ret);
        return ret;
    }

    *pu32Flag = ctl_handle.flag;

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
