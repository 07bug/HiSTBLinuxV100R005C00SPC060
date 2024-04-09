/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_klad.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#include "drv_klad.h"
#include "drv_tee_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


typedef struct hiKlad_Teec_S
{
    TEEC_Context    context;
    TEEC_Session    session;
    HI_BOOL         connected;
    struct mutex    lock;
}Klad_Teec_S;

Klad_Teec_S     g_klad_teec;

static HI_S32 DEV_KLAD_OpenTeec(Klad_Teec_S *teec)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 sec_id = 0;
    TEEC_Operation operation;
    HI_CHAR session_name[] = "tee_keyladder_session";

    TEEC_UUID klad_task_uuid =
    {
        0xc9cf6b2a,
        0x4b60,
        0x11e7,
        {0xa9, 0x19, 0x92, 0xeb, 0xcb, 0x67, 0xfe, 0x33 }
    };
    mutex_lock(&teec->lock);
    if (unlikely(HI_TRUE == teec->connected))
    {
        ret = HI_SUCCESS;
        goto out0;
    }

    ret = TEEK_InitializeContext(NULL, &teec->context);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Initialise klad teec context failed(0x%x)\n", ret);
        goto out1;
    }

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.cancel_flag = 0;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);
    operation.params[2].tmpref.buffer = (void *)(&sec_id);
    operation.params[2].tmpref.size = sizeof(sec_id);
    operation.params[3].tmpref.buffer = (void *)(session_name);
    operation.params[3].tmpref.size = strlen(session_name) + 1;

    ret = TEEK_OpenSession(&teec->context, &teec->session, &klad_task_uuid, TEEC_LOGIN_IDENTIFY, NULL, &operation, NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("open klad teec session failed(0x%x)\n", ret);
        goto out2;
    }
    teec->connected = HI_TRUE;
    mutex_unlock(&teec->lock);
    return HI_SUCCESS;

out2:
    TEEK_FinalizeContext(&teec->context);
out1:
    teec->connected = HI_FALSE;
out0:
    mutex_unlock(&teec->lock);
    return ret;
}

static HI_VOID DEV_ADVCA_CloseTeec(Klad_Teec_S *teec)
{
    mutex_lock(&teec->lock);

    if (HI_TRUE == teec->connected)
    {
        teec->connected = HI_FALSE;

        TEEK_CloseSession(&teec->session);
        TEEK_FinalizeContext(&teec->context);
    }
    mutex_unlock(&teec->lock);
    return;
}

HI_S32 DEV_KLAD_SendCmdToTA(HI_U32 cmd_id, TEEC_Operation *operation, HI_U32 *ret_origin)
{
    HI_S32      ret = HI_FAILURE;
    Klad_Teec_S *teec = &g_klad_teec;

    if (unlikely(HI_FALSE == teec->connected))
    {
        ret = DEV_KLAD_OpenTeec(teec);
        if (HI_SUCCESS != ret)
        {
            goto out;
        }
    }
    ret = TEEK_InvokeCommand(&teec->session, cmd_id, operation, ret_origin);
out:
    return ret;
}

HI_S32 DEV_KLAD_InitTeec(HI_VOID)
{
    memset(&g_klad_teec, 0, sizeof(Klad_Teec_S));
    mutex_init(&g_klad_teec.lock);
    return DEV_KLAD_OpenTeec(&g_klad_teec);
}

HI_S32 DEV_KLAD_DeInitTeec(HI_VOID)
{
    DEV_ADVCA_CloseTeec(&g_klad_teec);
    memset(&g_klad_teec, 0, sizeof(Klad_Teec_S));
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
