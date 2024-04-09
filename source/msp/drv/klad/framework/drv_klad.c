/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <asm/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include "hi_drv_reg.h"
#include "hi_drv_mem.h"
#include "hi_drv_module.h"
#include "hal_klad.h"
#include "drv_klad.h"
#include "drv_klad_basic.h"
#include "hi_drv_descrambler.h"
#include "drv_demux_ext.h"
#include "drv_cipher_ext.h"
#include "drv_plcipher_ext.h"
#ifdef HI_TEE_SUPPORT
#include "drv_tee_klad.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

LIST_HEAD(ca_list);

DRV_KLAD_SESSION_LIST klad_session_list;
DRV_KLAD_SESSION_LIST klad_free_session_list;

struct mutex g_klad_mutex;

#ifdef HI_CAS_OPTIMIZE_REPEAT_SET
struct mutex g_key_mutex;
DRV_KLAD_SESSION g_klad_key;
#endif

static HI_VOID klad_mutex_lock(struct mutex *lock)
{
    mutex_lock(lock);
}

static HI_VOID klad_mutex_unlock(struct mutex *lock)
{
    mutex_unlock(lock);
}

static DRV_KLAD_SESSION* klad_session_list_malloc(HI_VOID)
{
    DRV_KLAD_SESSION *p = HI_NULL;
    DRV_KLAD_SESSION *tmp = HI_NULL;

    klad_mutex_lock(&klad_free_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_free_session_list.list, list)
    {
        if ((HI_NULL != p) && (p->instance.handle == 0x0))
        {
            list_del(&p->list);
            klad_mutex_unlock(&klad_free_session_list.lock);
            return p;
        }
    }
    klad_mutex_unlock(&klad_free_session_list.lock);

    return HI_NULL_PTR;
}

static HI_VOID klad_session_list_free(DRV_KLAD_SESSION *session)
{
    klad_mutex_lock(&klad_free_session_list.lock);

    list_del(&session->list);
    memset(&session->instance, 0x00, sizeof(DRV_KLAD_SESSION_INFO));

    list_add(&session->list, &klad_free_session_list.list);

    klad_mutex_unlock(&klad_free_session_list.lock);
}

HI_VOID DRV_KLAD_MutexLock(HI_VOID)
{
    klad_mutex_lock(&g_klad_mutex);
}

HI_VOID DRV_KLAD_MutexUnLock(HI_VOID)
{
    klad_mutex_unlock(&g_klad_mutex);
}

HI_S32 DRV_KLAD_Init(HI_VOID)
{
    KLAD_FUNC_ENTER();

    mutex_init(&g_klad_mutex);
    INIT_LIST_HEAD(&ca_list);

    INIT_LIST_HEAD(&klad_session_list.list);
    mutex_init(&klad_session_list.lock);

    INIT_LIST_HEAD(&klad_free_session_list.list);
    mutex_init(&klad_free_session_list.lock);

#ifdef HI_CAS_OPTIMIZE_REPEAT_SET
    mutex_init(&g_key_mutex);
    memset(&g_klad_key, 0, sizeof(DRV_KLAD_SESSION));
#endif
    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Exit(HI_VOID)
{
    DRV_KLAD_SESSION *tmp = HI_NULL;
    DRV_KLAD_SESSION* session_loop = HI_NULL;
    DRV_KLAD_SESSION* free_session_loop = HI_NULL;
    DRV_KLAD_SESSION* ca_loop = HI_NULL;

    KLAD_FUNC_ENTER();

    list_for_each_entry_safe(free_session_loop, tmp, &klad_free_session_list.list, list)
    {
        list_del(&free_session_loop->list);
        HI_KFREE(HI_ID_CA,free_session_loop);
        free_session_loop = HI_NULL;
    }
    mutex_destroy(&klad_free_session_list.lock);

    list_for_each_entry_safe(session_loop, tmp, &klad_session_list.list, list)
    {
        list_del(&session_loop->list);
        HI_KFREE(HI_ID_CA,session_loop);
        session_loop = HI_NULL;
    }
    mutex_destroy(&klad_session_list.lock);

    list_for_each_entry_safe(ca_loop, tmp, &ca_list, list)
    {
        list_del(&ca_loop->list);
    }

    mutex_destroy(&g_klad_mutex);

#ifdef HI_CAS_OPTIMIZE_REPEAT_SET
    mutex_destroy(&g_key_mutex);
#endif

    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_SESSION_Create(HI_HANDLE* create_handle)
{
    HI_BOOL found = HI_FALSE;
    DRV_KLAD_SESSION *session = HI_NULL;
    DRV_KLAD_SESSION *p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;
    HI_U32 i = 0, j = 0;
    HI_HANDLE create;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(create_handle);

    for (i = 0; i < HI_KLAD_MAX_SESSION; i++)
    {
        found = HI_FALSE;
        create = HI_KLAD_MAKEHANDLE(HI_ID_CA, i);

        klad_mutex_lock(&klad_session_list.lock);
        list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
        {
            if (p && (p->instance.handle == create))
            {
                found = HI_TRUE;
                break;
            }
        }

        if (found == HI_FALSE)
        {
            session = klad_session_list_malloc();
            if(HI_NULL_PTR == session)
            {
                session = (DRV_KLAD_SESSION *) HI_KMALLOC(HI_ID_CA, sizeof (DRV_KLAD_SESSION), GFP_KERNEL);
                if (HI_NULL == session)
                {
                    klad_mutex_unlock(&klad_session_list.lock);
                    KLAD_PrintErrorCode(HI_ERR_KLAD_NO_MEMORY);
                    return HI_ERR_KLAD_NO_MEMORY;
                }
            }
            memset(session, 0x0, sizeof (DRV_KLAD_SESSION));
            session->instance.handle = create;
            session->instance.target = HI_INVALID_HANDLE;
            session->instance.attr_flag = HI_FALSE;

            for (j = 0; j < HI_UNF_KLAD_LEVEL_BUTT; j++)
            {
                session->instance.session_key_flag[j] = HI_FALSE;
            }

            session->instance.content_key_flag = HI_FALSE;
            session->instance.owner= task_tgid_nr(current);
            list_add(&session->list, &klad_session_list.list);
            *create_handle = session->instance.handle;

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
        klad_mutex_unlock(&klad_session_list.lock);
    }

    *create_handle = HI_INVALID_HANDLE;
    KLAD_PrintErrorCode(HI_ERR_KLAD_NO_RESOURCE);
    return HI_ERR_KLAD_NO_RESOURCE;
}

static HI_S32 DRV_KLAD_SESSION_Destory(HI_HANDLE handle)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            klad_session_list_free(p);

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetAttr(HI_HANDLE handle, DRV_KLAD_ATTR_S* attr)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(attr);

    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);
            if ((HI_TRUE == p->instance.attr_flag) && (attr->klad_type != p->instance.attr.klad_type))
            {
                CLEAR_SESSION_INFO(p);
            }
            memcpy(&p->instance.attr, attr, sizeof(DRV_KLAD_ATTR_S));
            p->instance.attr_flag = HI_TRUE;

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_GetAttr(HI_HANDLE handle, DRV_KLAD_ATTR_S* attr)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(attr);

    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);
            if (p->instance.attr_flag == HI_FALSE)
            {
                klad_mutex_unlock(&klad_session_list.lock);
                KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_ATTR);
                KLAD_FUNC_EXIT();
                return HI_ERR_KLAD_NOT_SET_ATTR;
            }

            memcpy(attr, &p->instance.attr, sizeof(DRV_KLAD_ATTR_S));

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_Attach(HI_HANDLE handle, HI_HANDLE target)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);

            if (p->instance.target == HI_INVALID_HANDLE)
            {
                p->instance.target = target;
            }
            else
            {
                klad_mutex_unlock(&klad_session_list.lock);
                KLAD_PrintErrorCode(HI_ERR_KLAD_ALREADY_SETTARGET);
                return HI_ERR_KLAD_ALREADY_SETTARGET;
            }
            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_Detach(HI_HANDLE handle, HI_HANDLE target)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);

            if (p->instance.target == HI_INVALID_HANDLE)
            {
                klad_mutex_unlock(&klad_session_list.lock);
                KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SETTARGET);
                return HI_ERR_KLAD_NOT_SETTARGET;
            }
            else if (p->instance.target != target)
            {
                klad_mutex_unlock(&klad_session_list.lock);
                KLAD_PrintErrorCode(HI_ERR_KLAD_DETACH_ERRTARGET);
                return HI_ERR_KLAD_DETACH_ERRTARGET;
            }
            else
            {
                p->instance.target = HI_INVALID_HANDLE;
            }

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetSessionKey(HI_HANDLE handle, DRV_KLAD_SESSION_KEY_S* session_key)
{
    DRV_KLAD_SESSION *p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;
    HI_U32 id = 0;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(session_key);

    id = session_key->level;

    KLAD_CHECK_LEVEL(id);
    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);

            memcpy(&p->instance.session_key[id], session_key, sizeof(DRV_KLAD_SESSION_KEY_S));
            p->instance.session_key_flag[id] = HI_TRUE;

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_SetContentKey(HI_HANDLE handle, DRV_KLAD_CONTENT_KEY_S* content_key)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(content_key);

    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);

            memcpy(&p->instance.content_key, content_key, sizeof(DRV_KLAD_CONTENT_KEY_S));
            p->instance.content_key_flag = HI_TRUE;

            klad_mutex_unlock(&klad_session_list.lock);
            KLAD_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

static HI_S32 DRV_KLAD_SESSION_GetParaNode(HI_HANDLE handle, DRV_KLAD_SESSION **session)
{
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if (p && p->instance.handle == handle)
        {
            KLAD_CHECK_TASK_ID(p);

            *session = p;
            klad_mutex_unlock(&klad_session_list.lock);
            return HI_SUCCESS;
        }
    }

    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_FIND_SESSION);
    return HI_ERR_KLAD_NOT_FIND_SESSION;
}

#ifdef HI_KLAD_TA_SUPPORT
HI_S32 CA_TO_TA_Create(HI_HANDLE handle_ree)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;

    KLAD_FUNC_ENTER();

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = handle_ree;

    HI_ERR_KLAD("call DEV_KLAD_SendCmdToTA  cmdid = %d\n", TEEC_CMD_KLAD_CREAT);
    ret = DEV_KLAD_SendCmdToTA(TEEC_CMD_KLAD_CREAT, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_SendCmdToTA,ret);
        ret = HI_FAILURE;
    }

    KLAD_FUNC_EXIT();

    return ret;
}

HI_S32 CA_TO_TA_Destroy(HI_HANDLE handle_ree)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;

    KLAD_FUNC_ENTER();

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = handle_ree;
    HI_ERR_KLAD("call DEV_KLAD_SendCmdToTA  cmdid = %d\n", TEEC_CMD_KLAD_DESTORY);

    ret = DEV_KLAD_SendCmdToTA(TEEC_CMD_KLAD_DESTORY, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_SendCmdToTA,ret);
        ret = HI_FAILURE;
    }

    KLAD_FUNC_EXIT();

    return ret;
}

HI_S32 CA_TO_TA_SetContentKey(DRV_KLAD_SESSION *session)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;
    DRV_KLAD_TEE_PARA para = {0};

    KLAD_CHECK_POINTER(session);

    para.handle = session->instance.handle;
    para.target = session->instance.target;
    para.attr_flag = session->instance.attr_flag;
    memcpy(&para.attr,&session->instance.attr,sizeof(DRV_KLAD_ATTR_S));
    memcpy(para.session_key_flag,session->instance.sessiong_key_flag,sizeof(HI_BOOL)*HI_UNF_KLAD_LEVEL_BUTT);
    memcpy(para.session_key,session->instance.session_key,sizeof(DRV_KLAD_SESSION_KEY_S)*HI_UNF_KLAD_LEVEL_BUTT);
    para.content_key_flag = session->instance.content_key_flag;
    memcpy(&para.content_key,&session->instance.content_key,sizeof(DRV_KLAD_CONTENT_KEY_S));

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].tmpref.buffer = (void *)(&para);
    operation.params[0].tmpref.size = sizeof(DRV_KLAD_TEE_PARA);

    HI_ERR_KLAD("call DEV_KLAD_SendCmdToTA  cmdid = %d\n", TEEC_CMD_KLAD_SET_CONTENT_KEY);
    ret = DEV_KLAD_SendCmdToTA(TEEC_CMD_KLAD_SET_CONTENT_KEY, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_SendCmdToTA,ret);
    }

    return ret;
}

#endif

#ifdef HI_TEE_SUPPORT
HI_S32 CA_TO_TA_SecEnDisable(HI_U32 klad_type)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = klad_type;
    operation.params[0].value.b = 1;

    ret = DEV_KLAD_SendCmdToTA(TEEC_CMD_KLAD_DISABLESECEN, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_SendCmdToTA,ret);
    }

    return ret;
}

HI_S32 CA_TO_TA_SecEnEnable(HI_U32 klad_type)
{
    HI_S32 ret = HI_FAILURE;
    TEEC_Operation operation;

    memset(&operation, 0x0, sizeof(TEEC_Operation));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = klad_type;
    operation.params[0].value.b = 0;

    ret = DEV_KLAD_SendCmdToTA(TEEC_CMD_KLAD_ENABLESECEN, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_SendCmdToTA,ret);
    }

    return ret;
}
#endif

HI_S32 DEV_KLAD_HWEnable(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    ret = HAL_KLAD_HWEnable();
    if(HI_ERR_KLAD_SECURE_ATTR_UINIT == ret)
    {
        DRV_KLAD_SetSecEN();
    }
    else if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(HAL_KLAD_HWEnable,ret);
        return ret;
    }
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Create(HI_VOID* arg)
{
    HI_HANDLE create_handle = 0;
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_HANDLE_S* ctl_handle = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);
    ctl_handle = (KLAD_CTL_HANDLE_S*)arg;

    ret = DRV_KLAD_SESSION_Create(&create_handle);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_Create,ret);
    }

    ctl_handle->create_handle = create_handle;
    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Destory(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ret = DRV_KLAD_SESSION_Destory(*(HI_HANDLE *)arg);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_Destory,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Release(struct file* filp)
{
    pid_t pid, curr;
    DRV_KLAD_SESSION* p = HI_NULL;
    DRV_KLAD_SESSION* tmp = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(filp);

    pid = (pid_t)(unsigned long)(filp->private_data);
    curr = task_tgid_nr(current);

    if (pid != curr)
    {
        KLAD_PrintErrorCode(HI_ERR_KLAD_TASK_ID_MISMATCH);
        return HI_ERR_KLAD_TASK_ID_MISMATCH;
    }

    klad_mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(p, tmp, &klad_session_list.list, list)
    {
        if ((HI_NULL != p) && (p->instance.owner == curr))
        {
            list_del(&p->list);
            HI_KFREE(HI_ID_CA, p);
            p = HI_NULL;
        }
    }
    klad_mutex_unlock(&klad_session_list.lock);
    KLAD_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Attach(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S* ctl_target = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ctl_target = (KLAD_CTL_TARGET_S*)arg;
    ret = DRV_KLAD_SESSION_Attach(ctl_target->handle, ctl_target->target);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_Attach,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_Detach(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_TARGET_S* ctl_target = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ctl_target = (KLAD_CTL_TARGET_S*)arg;
    ret = DRV_KLAD_SESSION_Detach(ctl_target->handle, ctl_target->target);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_Detach,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_GetAttr(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S* ctl_attr = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ctl_attr = (KLAD_CTL_ATTR_S*)arg;
    ret = DRV_KLAD_SESSION_GetAttr(ctl_attr->handle, &ctl_attr->attr);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_GetAttr,ret);
    }

    return ret;
}
HI_S32 DRV_KLAD_SetAttr(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_ATTR_S* ctl_attr = HI_NULL;

    KLAD_FUNC_ENTER();
    KLAD_CHECK_POINTER(arg);

    ctl_attr = (KLAD_CTL_ATTR_S*)arg;
    ret = DRV_KLAD_SESSION_SetAttr(ctl_attr->handle, &ctl_attr->attr);
    if (ret != HI_SUCCESS)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_SetAttr,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_SetSessionKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_SESSION_KEY_S* ctl_key = HI_NULL;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(arg);

    ctl_key = (KLAD_CTL_SESSION_KEY_S*)(arg);

    ret = DRV_KLAD_SESSION_SetSessionKey(ctl_key->handle, &ctl_key->session_key);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_SetSessionKey,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_SetContentKey(HI_VOID* arg)
{
    HI_S32 ret = HI_FAILURE;
    KLAD_CTL_CONTENT_KEY_S* ctl_key = HI_NULL;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(arg);

    ctl_key = (KLAD_CTL_CONTENT_KEY_S*)(arg);

    ret = DRV_KLAD_SESSION_SetContentKey(ctl_key->handle, &ctl_key->content_key);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_SESSION_SetContentKey,ret);
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_GetSession(HI_HANDLE handle, DRV_KLAD_SESSION **session)
{
    KLAD_CHECK_POINTER(session);

    return DRV_KLAD_SESSION_GetParaNode(handle, session);
}

DRV_KLAD_TARGET_E DRV_KLAD_GetTargetModID(const HI_HANDLE target_handle)
{
    DRV_KLAD_TARGET_E modid = DRV_KLAD_TARGET_BUTT;

    if (HI_ID_DEMUX == (target_handle >> 24))
    {
        modid = DRV_KLAD_TARGET_DEMUX;
    }
    else if (HI_ID_CIPHER == (target_handle >> 16))
    {
        modid = DRV_KLAD_TARGET_MULTI_CIPHER;
    }
    else if (HI_ID_PLCIPHER == (target_handle >> 16))
    {
        modid = DRV_KLAD_TARGET_PAYLOAD_CIPHER;
    }
    else
    {
        modid = DRV_KLAD_TARGET_BUTT;
    }

    return modid;
}

DRV_KLAD_TARGET_E DRV_KLAD_GetTarget(DRV_KLAD_SESSION *session)
{
    KLAD_CHECK_POINTER(session);

    if (HI_ID_DEMUX == ((session->instance.target >> 24) & 0xff))
    {
        return DRV_KLAD_TARGET_DEMUX;
    }
    else if (HI_ID_PLCIPHER == ((session->instance.target >> 16) & 0xff))
    {
        return DRV_KLAD_TARGET_PAYLOAD_CIPHER;
    }
    else if (HI_ID_CIPHER == ((session->instance.target >> 16) & 0xff))
    {
        return DRV_KLAD_TARGET_MULTI_CIPHER;
    }
    else
    {
        return DRV_KLAD_TARGET_BUTT;
    }
}

HI_S32 DRV_KLAD_SetSecEN(HI_VOID)
{
    KLAD_DRV_ZONE* p = HI_NULL;
    KLAD_DRV_ZONE* tmp = HI_NULL;

    list_for_each_entry_safe(p, tmp, &ca_list, list)
    {
        if (HI_NULL != p)
        {
            p->setsecen();
            p = HI_NULL;
        }
    }
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_Register(KLAD_DRV_ZONE * zone)
{
    KLAD_CHECK_POINTER(zone);

    list_add(&zone->list, &ca_list);

    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_UnRegister(KLAD_DRV_ZONE* zone)
{
    KLAD_CHECK_POINTER(zone);

    list_del(&zone->list);

    return HI_SUCCESS;
}

HI_VOID DRV_KLAD_Msleep(HI_U32 time)
{
    msleep(time);
    return;
}

#ifdef HI_CAS_OPTIMIZE_REPEAT_SET
HI_S32 DRV_KLAD_KeyStore(DRV_KLAD_SESSION* klad_session)
{
    KLAD_CHECK_POINTER(klad_session);
    klad_mutex_lock(&g_key_mutex);
    memcpy(&g_klad_key, klad_session, sizeof(DRV_KLAD_SESSION));
    klad_mutex_unlock(&g_key_mutex);
    return HI_SUCCESS;
}
#endif

static HI_S32 DRV_KLAD_RunCACallBack(unsigned int cmd, void* arg)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE handle = 0;
    DRV_KLAD_SESSION *pSession = HI_NULL;
    KLAD_DRV_ZONE* p = HI_NULL;
    KLAD_DRV_ZONE* tmp = HI_NULL;
    HI_U32 ca_type = 0;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER(arg);

    handle = *(HI_U32 *)arg;

    ret = DRV_KLAD_GetSession(handle, &pSession);
    if (HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DRV_KLAD_GetSession,ret);
        return ret;
    }

    KLAD_CHECK_TASK_ID(pSession);
    KLAD_CHECK_ATTR_FLAG(pSession);
    ca_type = HI_KLAD_GET_CATYPE(pSession->instance.attr.klad_type);

    list_for_each_entry_safe(p, tmp, &ca_list, list)
    {
        if (p->ca == ca_type)
        {
            ret = p->ioctl(cmd, arg);
#ifdef HI_CAS_OPTIMIZE_REPEAT_SET
            if(ret == HI_SUCCESS && cmd == CMD_KLAD_SET_CONTENT_KEY)
            {
                DRV_KLAD_KeyStore(pSession);
            }
#endif
            KLAD_FUNC_EXIT();
            return ret;
        }
    }

    return HI_ERR_KLAD_NOT_FIND_KLAD;
}

HI_S32 DRV_KLAD_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, void* arg)
{

    HI_S32 ret = HI_FAILURE;

    KLAD_FUNC_ENTER();

    KLAD_CHECK_POINTER((HI_VOID *)arg);

    ret = DEV_KLAD_HWEnable();
    if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_HWEnable,ret);
        return ret;
    }

    switch (cmd)
    {
        case CMD_KLAD_CREATE:
            ret = DRV_KLAD_Create(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_Create,ret);
            }
            #ifdef HI_KLAD_TA_SUPPORT
            ret = CA_TO_TA_Create(*(HI_HANDLE*)arg);
            #endif
            break;
        case CMD_KLAD_DESTORY:
            #ifdef HI_KLAD_TA_SUPPORT
            ret = CA_TO_TA_Destroy(*(HI_HANDLE*)arg);
            #endif
            ret = DRV_KLAD_Destory(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_Destory,ret);
            }
            break;
        case CMD_KLAD_ATTACH:
            ret = DRV_KLAD_Attach(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_Attach,ret);
            }
            break;
        case CMD_KLAD_DETACH:
            ret = DRV_KLAD_Detach(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_Detach,ret);
            }
            break;
        case CMD_KLAD_GET_ATTR:
            ret = DRV_KLAD_GetAttr(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_GetAttr,ret);
            }
            break;
        case CMD_KLAD_SET_ATTR:
            ret = DRV_KLAD_SetAttr(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_SetAttr,ret);
            }
            break;
        case CMD_KLAD_SET_SESSION_KEY:
            ret = DRV_KLAD_SetSessionKey(arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_PrintErrorFunc(DRV_KLAD_SetSessionKey,ret);
            }
            break;
        default:
            ret = DRV_KLAD_RunCACallBack(cmd, arg);
            if(HI_SUCCESS != ret)
            {
                KLAD_ERR_PrintHex(cmd);
                KLAD_PrintErrorFunc(DRV_KLAD_RunCACallBack,ret);
            }
            break;
    }

    KLAD_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_KLAD_SetClearKey(EXT_CLEAR_CW_KLAD_PARA_S *stClearKey)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    HI_S32  ret = HI_SUCCESS;
    KLAD_CHECK_POINTER(stClearKey);

    ret = DEV_KLAD_HWEnable();
    if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(DEV_KLAD_HWEnable,ret);
        return ret;
    }

    ret = EXT_DRV_KLAD_BASIC_SetClearCWKey(stClearKey);
    if(HI_SUCCESS != ret)
    {
        KLAD_PrintErrorFunc(EXT_DRV_KLAD_BASIC_SetClearCWKey,ret);
    }

    return ret;
#else
    return HI_SUCCESS;
#endif
}

KLAD_EXPORT_FUNC_S s_KladExportFunctionList =
{
    .pSetClearkey = DRV_KLAD_SetClearKey,
};

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
