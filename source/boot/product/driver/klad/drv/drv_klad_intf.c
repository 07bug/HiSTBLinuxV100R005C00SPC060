/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_intf.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_drv_klad.h"
#include "drv_klad.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "drv_klad_basic.h"
#include "drv_klad_common_ca.h"
#ifdef HI_ADVCA_C1_SUPPORT
#include "drv_klad_nagra.h"
#endif
#ifdef HI_ADVCA_C2_SUPPORT
#include "drv_klad_irdeto.h"
#endif
#ifdef HI_ADVCA_C3_SUPPORT
#include "drv_klad_conax.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


HI_S32 BOOT_KLAD_Ioctl(HI_U32 cmd, HI_VOID *argp)
{
    return DRV_KLAD_Ioctl(cmd, argp);
}


/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode init.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_S32 KLAD_ModInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_Init();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_KLAD("klad module init error\n");
        KLAD_FUNC_EXIT();
        goto out;
    }

    ret = DRV_KLAD_BASIC_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_BASIC_Init failed\n");
        KLAD_FUNC_EXIT();
        goto err_Bsc;
    }

    ret = DRV_KLAD_COMMON_CA_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_COMMON_CA_Init failed\n");
        KLAD_FUNC_EXIT();
        goto err_common_ca;
    }

#ifdef HI_ADVCA_C1_SUPPORT
    ret = DRV_KLAD_C1_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C1_Init failed\n");
        KLAD_FUNC_EXIT();
        goto err_C1;
    }
#endif

#ifdef HI_ADVCA_C2_SUPPORT
    ret = DRV_KLAD_C2_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C2_Init failed\n");
        KLAD_FUNC_EXIT();
        goto err_C2;
    }
#endif

#ifdef HI_ADVCA_C3_SUPPORT
    ret = DRV_KLAD_C3_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C3_Init failed\n");
        goto err_C3;
    }
#endif

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;

#ifdef HI_ADVCA_C3_SUPPORT
err_C3:
    DRV_KLAD_C3_Exit();
#endif
#ifdef HI_ADVCA_C2_SUPPORT
err_C2:
    DRV_KLAD_C2_Exit();
#endif

#ifdef HI_ADVCA_C1_SUPPORT
err_C1:
    DRV_KLAD_C1_Exit();
#endif

err_common_ca:
    DRV_KLAD_COMMON_CA_Exit();

err_Bsc:
    DRV_KLAD_BASIC_Exit();
out:
    DRV_KLAD_Exit();
    KLAD_FUNC_EXIT();
    return HI_FAILURE;
}

/*****************************************************************************
 Prototype    :
 Description  : Keyladder mode exit.
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
HI_VOID KLAD_ModExit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    ret = DRV_KLAD_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_Exit failed\n");
    }

    ret = DRV_KLAD_BASIC_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_BASIC_Exit failed\n");
    }

    ret = DRV_KLAD_COMMON_CA_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_COMMON_CA_Exit failed\n");
    }

#ifdef HI_ADVCA_C1_SUPPORT
    ret = DRV_KLAD_C1_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C1_Exit failed\n");
    }
#endif

#ifdef HI_ADVCA_C2_SUPPORT
    ret = DRV_KLAD_C2_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C2_Exit failed\n");
    }
#endif

#ifdef HI_ADVCA_C3_SUPPORT
    ret = DRV_KLAD_C3_Exit();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_KLAD("DRV_KLAD_C3_Exit failed\n");
    }
#endif

    DRV_KLAD_Exit();
    KLAD_FUNC_EXIT();
    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
