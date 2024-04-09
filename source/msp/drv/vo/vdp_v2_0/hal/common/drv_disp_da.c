
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_da.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "drv_disp_com.h"
#include "drv_disp_da.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

//static DISP_ALG_VERSION_S s_stAlgCscVersion = {0};
HI_BOOL g_bDAInitFlag = HI_FALSE;
DISP_DA_FUNCTION_S g_stDAFuntion;

HI_S32 DISP_DA_Init(HI_DRV_DISP_VERSION_S* pstVersion)
{
    if (!pstVersion)
    {
        DISP_ERROR("FUNC(%s) Error! Invalid input parameters!\n", __FUNCTION__);
        return HI_FAILURE;
    }

    if (g_bDAInitFlag)
    {
        DISP_INFO("FUNC(%s) inited!\n", __FUNCTION__);
        return HI_SUCCESS;
    }

    DISP_MEMSET(&g_stDAFuntion, 0, sizeof(g_stDAFuntion));
    if (   (pstVersion->u32VersionPartH == DISP_CV200_ES_VERSION_H)
        && (pstVersion->u32VersionPartL == DISP_CV200_ES_VERSION_L)
        )
    {
        g_stDAFuntion.PFCscRgb2Yuv   = DISP_ALG_CscRgb2Yuv;
    }
    else
    {
        DISP_ERROR("FUNC(%s) Error! Invalid display version!", __FUNCTION__);
        return HI_FAILURE;
    }

    g_bDAInitFlag = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 DISP_DA_DeInit(HI_VOID)
{
    if (g_bDAInitFlag)
    {
        DISP_MEMSET(&g_stDAFuntion, 0, sizeof(g_stDAFuntion));
        g_bDAInitFlag = HI_FALSE;
    }


    return HI_SUCCESS;
}

DISP_DA_FUNCTION_S * DISP_DA_GetFunction(HI_VOID)
{
    if (g_bDAInitFlag)
    {
        return &g_stDAFuntion;
    }
    else
    {
        DISP_FATAL("UA is not inited! DISP_UA_GetFunction return NULL!\n");
        return HI_NULL;
    }
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */









