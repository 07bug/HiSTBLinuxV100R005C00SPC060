/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_KLAD_H__
#define __DRV_KLAD_H__

#include "hi_common.h"
#include "hi_unf_klad.h"
#include "hi_drv_advca.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_error_mpi.h"
#include "drv_klad_ioctl.h"
#include "hi_drv_klad.h"
#include "drv_klad_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define CA_NAME "HI_CA"
#define DRV_KLAD_MAX_DEMUX_ADDR_CNT  32
#define DRV_KLAD_MAX_CIPHER_ADDR_CNT 8

typedef struct
{
    struct list_head  list;
    struct mutex      lock;
}DRV_KLAD_SESSION_LIST;

extern DRV_KLAD_SESSION_LIST klad_session_list;

extern KLAD_EXPORT_FUNC_S s_KladExportFunctionList;

/** keyladder target */
typedef enum
{
    DRV_KLAD_TARGET_DEMUX          = 0x0, /**<demux*/
    DRV_KLAD_TARGET_MULTI_CIPHER   = 0x1, /**<multicipher*/
    DRV_KLAD_TARGET_PAYLOAD_CIPHER = 0x2,     /**<playload cipher*/
    DRV_KLAD_TARGET_BUTT
} DRV_KLAD_TARGET_E;

/*注意: 此枚举必须和hi_unf_xxx.h中HI_UNF_KLAD_XXX的高位保持一致*/
typedef enum
{
    CA_ID_BASIC        = 0x0,
    CA_ID_NAGRA        = 0x1,
    CA_ID_IRDETO       = 0x2,
    CA_ID_CONAX        = 0x3,
    CA_ID_VERIMATRIX   = 0x7,
    CA_ID_DCAS         = 0xc,
    CA_ID_COMMON_CA    = 0x3f,
    CA_ID_BUTT
} CA_TYPE_E;

typedef struct
{
    HI_U32 cmd;
    HI_S32 (*f_driver_cmd_process)(HI_VOID* arg);
} DRV_KLAD_IOCTL_S;

typedef HI_S32 (* KLAD_IOCTL)(HI_U32 cmd, HI_VOID *arg);
typedef HI_VOID (* KLAD_SETSECEN)(HI_VOID);
typedef HI_S32 (* KLAD_MODULE_OPS)(HI_VOID);

typedef struct
{
    CA_TYPE_E ca;
    struct list_head list;
    KLAD_IOCTL       ioctl;
    KLAD_SETSECEN    setsecen;
} KLAD_DRV_ZONE;

typedef struct
{
    HI_HANDLE handle; /*key, session handle*/
    pid_t    owner;  /**/

    HI_HANDLE target;  /*attach target*/

    HI_BOOL attr_flag;
    DRV_KLAD_ATTR_S attr;

    HI_BOOL session_key_flag[HI_UNF_KLAD_LEVEL_BUTT];
    DRV_KLAD_SESSION_KEY_S session_key[HI_UNF_KLAD_LEVEL_BUTT];

    HI_BOOL content_key_flag;
    DRV_KLAD_CONTENT_KEY_S content_key;

    HI_BOOL content_iv_flag;
    DRV_KLAD_CONTENT_IV_S content_iv;
    DRV_KLAD_DBG_S dbg;

    HI_U8 ta_klad_flag;
} DRV_KLAD_SESSION_INFO;

#define CLEAR_SESSION_INFO(s) \
    do {\
        HI_HANDLE session_handle = s->instance.handle; \
        HI_HANDLE session_target = s->instance.target; \
        pid_t    owner = s->instance.owner;  \
        memset(&(s->instance), 0, sizeof(DRV_KLAD_SESSION_INFO)); \
        s->instance.handle = session_handle; \
        s->instance.target = session_target; \
        s->instance.owner = owner; \
    }while(0);

typedef struct
{
    struct list_head        list;
    DRV_KLAD_SESSION_INFO   instance;
}DRV_KLAD_SESSION;

#ifdef HI_KLAD_TA_SUPPORT
typedef struct
{
    HI_HANDLE handle; /*key, session handle*/

    HI_HANDLE target;  /*attach target*/

    HI_BOOL attr_flag;
    DRV_KLAD_ATTR_S attr;

    HI_BOOL session_key_flag[HI_UNF_KLAD_LEVEL_BUTT];
    DRV_KLAD_SESSION_KEY_S session_key[HI_UNF_KLAD_LEVEL_BUTT];

    HI_BOOL content_key_flag;
    DRV_KLAD_CONTENT_KEY_S content_key;
} DRV_KLAD_TEE_PARA;
#endif

HI_VOID DRV_KLAD_MutexLock(HI_VOID);
HI_VOID DRV_KLAD_MutexUnLock(HI_VOID);
HI_S32 DRV_KLAD_Init(HI_VOID);
HI_S32 DRV_KLAD_Exit(HI_VOID);
HI_S32 DRV_KLAD_Create(HI_VOID* arg);
HI_S32 DRV_KLAD_Destory(HI_VOID* arg);
HI_S32 DRV_KLAD_Release(struct file* filp);
HI_S32 DRV_KLAD_Attach(HI_VOID* arg);
HI_S32 DRV_KLAD_Detach(HI_VOID* arg);
HI_S32 DRV_KLAD_GetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetAttr(HI_VOID* arg);
HI_S32 DRV_KLAD_SetSessionKey(HI_VOID* arg);
HI_S32 DRV_KLAD_SetContentKey(HI_VOID* arg);
HI_S32 DRV_KLAD_GetSession(HI_HANDLE handle, DRV_KLAD_SESSION **session);
DRV_KLAD_TARGET_E DRV_KLAD_GetTarget(DRV_KLAD_SESSION *session);
DRV_KLAD_TARGET_E DRV_KLAD_GetTargetModID(const HI_HANDLE target_handle);
HI_S32 DRV_KLAD_SetSecEN(HI_VOID);
HI_S32 DRV_KLAD_Register(KLAD_DRV_ZONE* zone);
HI_S32 DRV_KLAD_UnRegister(KLAD_DRV_ZONE* zone);
HI_VOID DRV_KLAD_Msleep(HI_U32 time);
HI_S32 DRV_KLAD_Ioctl(struct inode* inode, struct file* file, unsigned int cmd, void* arg);

#ifdef HI_KLAD_TA_SUPPORT
HI_S32 CA_TO_TA_Create(HI_HANDLE handle_ree);
HI_S32 CA_TO_TA_SetContentKey(DRV_KLAD_SESSION *session);
HI_S32 CA_TO_TA_Destroy(HI_HANDLE handle_ree);
#endif
HI_S32 DEV_KLAD_HWEnable(HI_VOID);

#ifdef HI_TEE_SUPPORT
HI_S32 CA_TO_TA_SecEnDisable(HI_U32 klad_type);
HI_S32 CA_TO_TA_SecEnEnable(HI_U32 klad_type);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif  /* __DRV_KLAD_H__ */
