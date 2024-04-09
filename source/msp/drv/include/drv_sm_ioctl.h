/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_sm_ioctl.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-08-11
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_SM_IOCTL_H__
#define __DRV_SM_IOCTL_H__

#include "hi_unf_session_manager.h"
#include "hi_mpi_session_manager.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

#define MAX_RESOURCE_NUM     (0x10)

typedef struct
{
    HI_HANDLE hCreate;
    HI_UNF_SM_ATTR_S stSMAttr;
} SM_CTL_CREATE_S;

typedef struct
{
    HI_HANDLE hSM;
    HI_UNF_SM_MODULE_E enModule;
    HI_UNF_SM_MODULE_S stModule;
} SM_CTL_ADD_S;

typedef struct
{
    HI_HANDLE hSM;
    HI_UNF_SM_MODULE_E enModule;
    HI_UNF_SM_MODULE_S stModule;
} SM_CTL_DEL_S;

typedef struct
{
    HI_HANDLE hSM;
} SM_CTL_DESTROY_S;

typedef struct
{
    HI_HANDLE hSM;
    HI_UNF_SM_INTENT_E enIntent;
} SM_CTL_INTENT_S;

typedef struct
{
    HI_UNF_SM_MODULE_E enSrcModule;
    HI_HANDLE hSrcHandle;
    HI_UNF_SM_MODULE_E enModule;
    HI_UNF_SM_MODULE_S stModule[MAX_RESOURCE_NUM];
    HI_U32 u32ModuleNum;
} SM_CTL_MODULE_S;

typedef struct
{
    HI_U32 u32SessionID;
    HI_HANDLE hHandle;
} SM_CTL_SMHANDLE_S;

typedef struct
{
    HI_HANDLE hSM;
    HI_UNF_SM_MODULE_E enModule;
    HI_UNF_SM_MODULE_S stModule[MAX_RESOURCE_NUM];
    HI_U32 u32ModuleNum;
} SM_CTL_MODULEBYSM_S;


#define CMD_SM_CREATE                       _IOWR (HI_ID_SM, 0x1, SM_CTL_CREATE_S)
#define CMD_SM_DESTORY                      _IOWR (HI_ID_SM, 0x2, SM_CTL_DESTROY_S)
#define CMD_SM_ADD_RESOURCE                 _IOWR (HI_ID_SM, 0x3, SM_CTL_ADD_S)
#define CMD_SM_DEL_RESOURCE                 _IOWR (HI_ID_SM, 0x4, SM_CTL_DEL_S)
#define CMD_SM_SET_INTENT                   _IOWR (HI_ID_SM, 0x5, SM_CTL_INTENT_S)
#define CMD_SM_GET_RESOURCE                 _IOWR (HI_ID_SM, 0x6, SM_CTL_MODULE_S)
#define CMD_SM_GET_SMHANDLE                 _IOWR (HI_ID_SM, 0x7, SM_CTL_SMHANDLE_S)
#define CMD_SM_GET_INTENT                   _IOWR (HI_ID_SM, 0x8, SM_CTL_INTENT_S)
#define CMD_SM_GET_RESOURCE_BYSM            _IOWR (HI_ID_SM, 0x9, SM_CTL_MODULEBYSM_S)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_SM_IOCTL_H__ */
