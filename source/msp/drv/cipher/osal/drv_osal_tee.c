/******************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_osal_tee.c
  Version       : Initial Draft
  Created       : 2018
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_tee.h"

#if !defined(TEE_CIPHER_TA_NONSUPPORT) && defined(HI_TEE_SUPPORT) && !defined(CHIP_TRNG_SUPPORT)

#include "teek_client_api.h"

#define TEE_CIPHER_TA_NAME        "hisi_drv_cipher"
#define TEE_CIPHER_TA_UID         0

static u32 s_tee_init = HI_FALSE;

/*! tee mutex */
static crypto_mutex tee_mutex;

#define OSAL_TEE_LOCK()   \
    ret = crypto_mutex_lock(&tee_mutex);  \
    if (HI_SUCCESS != ret)        \
    {\
        HI_LOG_ERROR("error, tee lock failed\n");\
        HI_LOG_FuncExit();\
        return ret;\
    }

#define OSAL_TEE_UNLOCK()   crypto_mutex_unlock(&tee_mutex)

static const TEEC_UUID s_stTeecCipherUUID =
{
    0x04ae2ac0, \
    0x01e8, \
    0x4587, \
    {\
        0xb3, 0xda, 0x38, 0xf5, 0x98, 0x46, 0xbc, 0x57 \
    }\
};

static TEEC_Session    session;
static TEEC_Context    context;
static TEEC_Operation  operation;

s32 drv_osal_tee_open_session(void)
{
    TEEC_Result     teec_result = HI_FAILURE;
    HI_U32          u32RootId = 0;

    HI_LOG_FuncEnter();

    crypto_mutex_init(&tee_mutex);

    memset(&context, 0, sizeof(context));
    memset(&operation, 0, sizeof(operation));
    memset(&session, 0, sizeof(session));

    teec_result = TEEK_InitializeContext(NULL, &context);
    if(teec_result != HI_SUCCESS)
    {
        HI_LOG_PrintFuncErr(TEEK_InitializeContext, teec_result);
        return teec_result;
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
                        TEEC_NONE,
                        TEEC_NONE,
                        TEEC_MEMREF_TEMP_INPUT,
                        TEEC_MEMREF_TEMP_INPUT);

    operation.params[2].tmpref.buffer = (HI_VOID *)(&u32RootId);
    operation.params[2].tmpref.size = sizeof(u32RootId);
    operation.params[3].tmpref.buffer = (HI_VOID *)(TEE_CIPHER_TA_NAME);
    operation.params[3].tmpref.size = strlen(TEE_CIPHER_TA_NAME) + 1;

    teec_result = TEEK_OpenSession(&context, &session, &s_stTeecCipherUUID, TEEC_LOGIN_IDENTIFY, NULL, &operation, NULL);
    if(teec_result != HI_SUCCESS)
    {
        TEEK_FinalizeContext(&context);
        HI_LOG_PrintFuncErr(TEEK_OpenSession, teec_result);
        return teec_result;
    }

    s_tee_init = HI_TRUE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_osal_tee_command(u32 command, void *params, u32 paramsize)
{
    TEEC_Result teec_result = HI_FAILURE;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    if (HI_TRUE != s_tee_init)
    {
        HI_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    OSAL_TEE_LOCK();

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].tmpref.buffer = params;
    operation.params[0].tmpref.size   = paramsize;

    HI_LOG_INFO("send tee command: 0x%x\n", command);
    teec_result = TEEK_InvokeCommand(&session, command, &operation, NULL);
    if(teec_result != HI_SUCCESS)
    {
        HI_LOG_PrintFuncErr(TEEK_InvokeCommand, teec_result);
        OSAL_TEE_UNLOCK();
        return teec_result;
    }

    OSAL_TEE_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_osal_tee_close_session(void)
{
    HI_LOG_FuncEnter();

    if (HI_FALSE == s_tee_init)
    {
        return HI_SUCCESS;
    }

    TEEK_CloseSession(&session);
    TEEK_FinalizeContext(&context);
    crypto_mutex_destroy(&tee_mutex);
    s_tee_init = HI_FALSE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#else

s32 drv_osal_tee_open_session(void)
{
    return HI_SUCCESS;
}

s32 drv_osal_tee_command(u32 command, void *params, u32 paramsize)
{
    HI_LOG_ERROR("Unsupport communication with TEE\n");

    return HI_FAILURE;
}

s32 drv_osal_tee_close_session(void)
{
    return HI_SUCCESS;
}

#endif

