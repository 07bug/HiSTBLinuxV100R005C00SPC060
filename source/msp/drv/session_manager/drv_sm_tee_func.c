/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sm_tee_func.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "session_manager_debug.h"
#include "drv_sm_tee_func.h"
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/errno.h>
#include "tee_client_api.h"
#include "teek_client_api.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


typedef enum
{
    HI_SM_CREATE = 0,
    HI_SM_DESTROY,
    HI_SM_ADD_RESOURCE,
    HI_SM_DEL_RESOURCE,
    HI_SM_GET_SMHANDLE,
    HI_SM_SET_INTENT,
    HI_SM_GET_RESOURCE,
    HI_SM_PRINT_PROC,
    HI_SM_GET_INTENT,
    HI_SM_GET_RESOURCE_BYSM,
} SESSION_MANAGE_COMMANDID;

#define SM_TA_NAME   "session_manager_client"

static TEEC_Context s_TeeContext;
static TEEC_Session s_TeeSession;

HI_S32 SM_TEEC_Init(HI_VOID)
{
    TEEC_Result ret;
    TEEC_Operation operation;
    HI_U32 root_id = 0;

    TEEC_UUID sm_uuid =
    { \
         0x90ae48e5, \
         0xc757, \
         0x44a7, \
         { \
             0xb5, 0x13, 0xde, 0x4b, 0x2b, 0x14, 0xa0, 0x7c \
         } \
    };

    ret = TEEK_InitializeContext(HI_NULL, &s_TeeContext);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InitializeContext, ret);
        return ret;
    }

    memset(&operation, 0x00, sizeof (TEEC_Operation));
    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&root_id);
    operation.params[2].tmpref.size = sizeof(root_id);
    operation.params[3].tmpref.buffer = (void *)(SM_TA_NAME);
    operation.params[3].tmpref.size = strlen(SM_TA_NAME) + 1;

    ret = (HI_S32)TEEK_OpenSession(&s_TeeContext, &s_TeeSession, &sm_uuid, TEEC_LOGIN_IDENTIFY, NULL, &operation, NULL);
    if (HI_SUCCESS != ret)
    {
        TEEK_FinalizeContext(&s_TeeContext);
        SM_PrintErrorFunc(TEEK_OpenSession, ret);
        return ret;
    }

    return HI_SUCCESS;

}

HI_S32 SM_TEEC_DeInit(HI_VOID)
{

    TEEK_CloseSession(&s_TeeSession);
    TEEK_FinalizeContext(&s_TeeContext);

    return HI_SUCCESS;
}


HI_S32 SM_TEEC_Create(HI_HANDLE *pHandle, HI_UNF_SM_ATTR_S *pstAttr)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_POINTER(pHandle);
    SM_CHECK_POINTER(pstAttr);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = pstAttr->u32SessionID;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_CREATE, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    *pHandle = operation.params[0].value.b;
    return HI_SUCCESS;
}

HI_S32 SM_TEEC_Destroy(HI_HANDLE handle)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_SMHANDLE(handle);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = handle;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_DESTROY, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    return HI_SUCCESS;
}


HI_S32 SM_TEEC_Add(HI_HANDLE sm_handle, HI_UNF_SM_MODULE_E module, HI_UNF_SM_MODULE_S *pstModule)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_SMHANDLE(sm_handle);
    SM_CHECK_MODULEID(module);
    SM_CHECK_POINTER(pstModule);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = sm_handle;
    operation.params[0].value.b = 1;
    operation.params[1].value.a = module;
    operation.params[2].tmpref.buffer = (HI_VOID *) pstModule;
    operation.params[2].tmpref.size   = sizeof (HI_UNF_SM_MODULE_S);
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_ADD_RESOURCE, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 SM_TEEC_Del(HI_HANDLE sm_handle, HI_UNF_SM_MODULE_E module, HI_UNF_SM_MODULE_S *pstModule)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_SMHANDLE(sm_handle);
    SM_CHECK_MODULEID(module);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = sm_handle;
    operation.params[0].value.b = 1;
    operation.params[1].value.a = module;
    operation.params[2].tmpref.buffer = (HI_VOID *) pstModule;
    operation.params[2].tmpref.size   = sizeof (HI_UNF_SM_MODULE_S);

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_DEL_RESOURCE, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    return HI_SUCCESS;
}


HI_S32 SM_TEEC_SetIntent(HI_HANDLE sm_handle, HI_UNF_SM_INTENT_E intent)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_SMHANDLE(sm_handle);
    SM_CHECK_INTENT(intent);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = sm_handle;
    operation.params[0].value.b = intent;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_SET_INTENT, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 SM_TEEC_GetResource(HI_UNF_SM_MODULE_E src_mod, HI_HANDLE src_handle, HI_UNF_SM_MODULE_E des_mod, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;
    HI_UNF_SM_MODULE_S stModule[16];
    HI_S32 i;

    SM_CHECK_MODULEID(src_mod);
    SM_CHECK_MODULEID(des_mod);
    SM_CHECK_POINTER(pstModule);
    SM_CHECK_POINTER(pu32ModNum);

    memset(&stModule, 0x0, sizeof (stModule));
    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = src_mod;
    operation.params[0].value.b = src_handle;
    operation.params[1].value.a = des_mod;
    operation.params[2].tmpref.buffer = (HI_VOID *) &stModule;
    operation.params[2].tmpref.size   = sizeof (stModule);
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_OUTPUT, TEEC_VALUE_OUTPUT);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_GET_RESOURCE, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    for (i = 0; i < operation.params[3].value.a; i++)
    {
        memcpy(pstModule + i, &stModule[i], sizeof (HI_UNF_SM_MODULE_S));
    }

    *pu32ModNum = operation.params[3].value.a;

    return HI_SUCCESS;
}


HI_S32 SM_TEEC_GetResourceBySM(HI_HANDLE hSM, HI_UNF_SM_MODULE_E des_mod, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;
    HI_UNF_SM_MODULE_S stModule[16];
    HI_S32 i;

    SM_CHECK_SMHANDLE(hSM);
    SM_CHECK_MODULEID(des_mod);
    SM_CHECK_POINTER(pstModule);
    SM_CHECK_POINTER(pu32ModNum);

    memset(&stModule, 0x0, sizeof (stModule));
    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = hSM;
    operation.params[1].value.a = des_mod;
    operation.params[2].tmpref.buffer = (HI_VOID *) &stModule;
    operation.params[2].tmpref.size   = sizeof (stModule);
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_OUTPUT, TEEC_VALUE_OUTPUT);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_GET_RESOURCE_BYSM, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    for (i = 0; i < operation.params[3].value.a; i++)
    {
        memcpy(pstModule + i, &stModule[i], sizeof (HI_UNF_SM_MODULE_S));
    }

    *pu32ModNum = operation.params[3].value.a;

    return HI_SUCCESS;

}

HI_S32 SM_TEEC_PrintProc(HI_VOID)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_PRINT_PROC, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 SM_TEEC_GetSMHandle(HI_U32 u32SessionID, HI_HANDLE *phSM)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_POINTER(phSM);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = u32SessionID;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_GET_SMHANDLE, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    *phSM = operation.params[0].value.b;
    return HI_SUCCESS;
}

HI_S32 SM_TEEC_GetIntent(HI_HANDLE sm_handle, HI_UNF_SM_INTENT_E *pIntent)
{
    TEEC_Operation operation;
    TEEC_Result ret;
    HI_U32 origin;

    SM_CHECK_SMHANDLE(sm_handle);
    SM_CHECK_POINTER(pIntent);

    memset(&operation, 0x0, sizeof (operation));
    operation.started = 1;
    operation.params[0].value.a = sm_handle;

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE);

    ret = TEEK_InvokeCommand(&s_TeeSession, (HI_U32)HI_SM_GET_INTENT, &operation, &origin);
    if (HI_SUCCESS != ret)
    {
        SM_PrintErrorFunc(TEEK_InvokeCommand, ret);
        return ret;
    }

    *pIntent = operation.params[1].value.a;

    return HI_SUCCESS;
}





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

