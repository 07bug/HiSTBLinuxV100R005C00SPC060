/***********************************************************************************
*              Copyright 2015 - 2025, skyworth . Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tvos_hal_sm.c
* Description:
*
* History:
* Version   Date               Author     DefectNum    Description
* main\1    2018-05-30         hhc        NULL         Create this file.
***********************************************************************************/

#define LOG_TAG "sm"

#include "tvos_hal_sm.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_common.h"

#include "hi_type.h"
#include "hi_unf_session_manager.h"

#ifndef __unused
#define __unused
#endif

#define SM_HEADER_VERSION       (1)
#define SM_DEVICE_API_VERSION_1_0 HARDWARE_DEVICE_API_VERSION_2(1, 0, SM_HEADER_VERSION)

/*****************************************************************************/
extern S32 av_get_sdk_avplay_hdl(const HANDLE hAvHandle, HANDLE* phSdkAvPlayHdl);
static S32 getSDKResource(SM_MODULE_TYPE_E enModuleType, const SM_MODULE_RESOURCE_S* pstResource, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S* pstSM)
{
    S32 s32Ret = SUCCESS;
    HANDLE hSdkAvPlayHdl;
    HAL_CHK_RETURN((NULL == pstResource) || (NULL == pstSM), ERROR_NULL_PTR, "parameter is NULL.");

    if (SM_MODULE_AV == enModuleType)
    {
        enModID = HI_UNF_SM_MODULE_AVPLAY;
        memset(pstSM, 0, sizeof(HI_UNF_SM_MODULE_S));
        s32Ret = av_get_sdk_avplay_hdl(pstResource->hHandle, &hSdkAvPlayHdl);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("av_get_sdk_avplay_hdl failed(0x%x)", s32Ret);
            return FAILURE;
        }

        pstSM->hHandle = (HI_HANDLE)hSdkAvPlayHdl;
    }
    else
    {
        HAL_ERROR("enModuleType not support, return failure");
        return FAILURE;
    }

    return SUCCESS;
}

static S32 sm_init(struct _SM_DEVICE_S* pstDev __unused, const SM_INIT_PARAMS_S* pstInitParams __unused)
{
    return (S32)HI_UNF_SM_Init();
}

static S32 sm_term(struct _SM_DEVICE_S* pstDev __unused, const SM_TERM_PARAMS_S* pstTermParams __unused)
{
    return (S32)HI_UNF_SM_DeInit();
}

static S32 sm_create(struct _SM_DEVICE_S* pstDev __unused, HANDLE* phSM, const SM_CREATE_PARAMS_S* pstCreateParams)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hUNFSMHandle;
    HI_UNF_SM_ATTR_S stSMAttr;

    HAL_CHK_RETURN(((NULL == pstCreateParams) || (NULL == phSM)), ERROR_NULL_PTR, "parameter is NULL.");

    stSMAttr.u32SessionID = (HI_U32)(pstCreateParams->u32SessionID);
    s32Ret = HI_UNF_SM_Create(&hUNFSMHandle, &stSMAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "HI_UNF_SM_Create failed(0x%x)", s32Ret);

    *phSM = (HANDLE)hUNFSMHandle;
    return SUCCESS;
}

static S32 sm_destroy(struct _SM_DEVICE_S* pstDev __unused, const HANDLE hSM, const SM_DESTROY_PARAMS_S* pstDestroyParams __unused)
{
    HI_HANDLE hUNFSMHandle = (HI_HANDLE)hSM;

    return (S32)HI_UNF_SM_Destroy(hUNFSMHandle);
}

static S32 sm_add_resource(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource)
{
    HI_UNF_SM_MODULE_E enModID = HI_UNF_SM_MODULE_AVPLAY;
    HI_UNF_SM_MODULE_S stSM;
    S32 s32Ret = getSDKResource(enModuleType, pstResource, enModID, &stSM);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "getSDKResource fail");

    return (S32)HI_UNF_SM_AddResource((HI_HANDLE)hSM, enModID, &stSM);
}

static S32 sm_del_resource(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource)
{
    HI_UNF_SM_MODULE_E enModID = HI_UNF_SM_MODULE_AVPLAY;
    HI_UNF_SM_MODULE_S stSM;
    S32 s32Ret = getSDKResource(enModuleType, pstResource, enModID, &stSM);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "getSDKResource fail");

    return (S32)HI_UNF_SM_DelResource((HI_HANDLE)hSM, enModID, &stSM);
}

static S32 sm_get_handle_by_sid(struct _SM_DEVICE_S* pstDev, HANDLE* phSM, U32 u32SessionID)
{
    HI_HANDLE hUNFSMHandle;
    S32 s32Ret = HI_UNF_SM_GetSMHandleBySID(u32SessionID, &hUNFSMHandle);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "HI_UNF_SM_GetSMHandleBySID fail");

    *phSM = (HANDLE)hUNFSMHandle;
    return SUCCESS;
}

#ifdef TVOS_PLATFORM
static int sm_dev_close(struct hw_device_t *pstDevice)
{
    SM_DEVICE_S* pCtx = (SM_DEVICE_S *)pstDevice;
    if (pCtx)
    {
        free(pCtx);
        pCtx = NULL;
    }
    return SUCCESS;
}

static int sm_dev_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device)
{
    if (strcmp(name, SM_HARDWARE_SM0) != 0)
    {
        return FAILURE;
    }

    if (NULL == device)
    {
        return FAILURE;
    }

    SM_DEVICE_S *pstDev = (SM_DEVICE_S *)malloc(sizeof(SM_DEVICE_S));
    if (NULL == pstDev)
    {
        printf("%s,%d malloc memory failed!\n", __func__, __LINE__);
        return FAILURE;
    }

    memset(pstDev, 0, sizeof(SM_DEVICE_S));

    pstDev->stCommon.tag = HARDWARE_DEVICE_TAG;
    pstDev->stCommon.version = SM_DEVICE_API_VERSION_1_0;
    pstDev->stCommon.module = (hw_module_t*)module;
    pstDev->stCommon.close = sm_dev_close;

    pstDev->sm_init         = sm_init;
    pstDev->sm_term         = sm_term;
    pstDev->sm_create       = sm_create;
    pstDev->sm_destroy      = sm_destroy;

    pstDev->sm_add_resource  = sm_add_resource;
    pstDev->sm_del_resource  = sm_del_resource;
    pstDev->sm_get_handle_by_sid  = sm_get_handle_by_sid;

    *device = &pstDev->stCommon;
    return SUCCESS;
}

static struct hw_module_methods_t sm_module_methods = {
    .open = sm_dev_open,
};

SM_MODULE_S HAL_MODULE_INFO_SYM = {
    .stCommon= {
        .tag= HARDWARE_MODULE_TAG,
        .version_major= 1,
        .version_minor= 0,
        .id= SM_HARDWARE_MODULE_ID,
        .name= "Session manager module",
        .author= "The Android Open Source Project",
        .methods= &sm_module_methods,
        .dso= NULL,
    }
};
#endif

static SM_DEVICE_S s_stDevice_sm =
{
    .sm_init         = sm_init,
    .sm_term         = sm_term,
    .sm_create       = sm_create,
    .sm_destroy      = sm_destroy,

    .sm_add_resource  = sm_add_resource,
    .sm_del_resource  = sm_del_resource,
    .sm_get_handle_by_sid  = sm_get_handle_by_sid,

};

SM_DEVICE_S* getSMDevice()
{
    return &s_stDevice_sm;
}

