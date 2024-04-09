/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : session_manager_debug.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-08-11
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __SESSION_MANAGER_DEBUG_H__
#define __SESSION_MANAGER_DEBUG_H__

#include "hi_debug.h"
#include "hi_type.h"
#include "hi_error_mpi.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     SESSION_MANAGER_DEBUG */
/** @{ */  /** <!-- SESSION_MANAGER_DEBUG */


#define KLAD_MOD_VALUE       (HI_ID_CA)
#define CIPHER_MOD_VALUE_REE (HI_ID_CIPHER)
#define CIPHER_MOD_VALUE_TEE (0x4d)
#define DEMUX_MOD_VALUE      (HI_ID_DEMUX)
#define PLCIPHER_MOD_VALUE   (HI_ID_PLCIPHER)
#define VDEC_MOD_VALUE       (HI_ID_VDEC)
#define DSC_MOD_VALUE        (HI_ID_DEMUX)
#define AVPLAY_MOD_VALUE     (HI_ID_AVPLAY)

#define HI_DEBUG_SM(fmt...)              HI_DBG_PRINT   (HI_ID_SM, fmt)
#define HI_FATAL_SM(fmt...)              HI_FATAL_PRINT (HI_ID_SM, fmt)
#define HI_ERR_SM(fmt...)                HI_ERR_PRINT   (HI_ID_SM, fmt)
#define HI_WARN_SM(fmt...)               HI_WARN_PRINT  (HI_ID_SM, fmt)
#define HI_INFO_SM(fmt...)               HI_INFO_PRINT  (HI_ID_SM, fmt)


#define SM_ERR_PrintHex(val)             HI_ERR_SM("%s = 0x%08X\n",#val, val)
#define SM_ERR_PrintInfo(val)            HI_ERR_SM("%s\n", val)
#define SM_ERR_PrintPoint(val)           HI_ERR_SM("%s = %p\n",    #val, val)

#define SM_PrintInfoCode(errCode)        HI_INFO_SM("at [%s][%04d] return [%x]\n", __FUNCTION__, __LINE__, errCode)
#define SM_PrintErrorCode(errCode)       HI_ERR_SM("at [%s][%04d] return [%x]\n", __FUNCTION__, __LINE__, errCode)
#define SM_PrintErrorFunc(func,errCode)  HI_ERR_SM("Call [%s]return [%x]\n", #func, errCode)

#define SM_FUNC_ENTER()                  HI_DBG_PRINT(HI_ID_SM, "[ENTER]:%s\n", __FUNCTION__)
#define SM_FUNC_EXIT()                   HI_DBG_PRINT(HI_ID_SM, "[EXIT] :%s\n", __FUNCTION__)

#define CHECK_HANDLE(handle, id, shift) \
    do {\
        if ((handle >> shift) != id) \
        { \
            SM_ERR_PrintHex(handle); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_HANDLE); \
            return HI_ERR_SM_INVALID_HANDLE;\
        } \
    } while (0)

#define CHECK_CIPHER_HANDLE(handle) \
    do { \
        if (((handle >> 16) != CIPHER_MOD_VALUE_REE) && ((handle >> 16) != CIPHER_MOD_VALUE_TEE)) \
        { \
            SM_ERR_PrintHex(handle); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_HANDLE); \
            return HI_ERR_SM_INVALID_HANDLE; \
        } \
    } while (0)


#define CHECK_DEMUX_HANDLE(handle) \
    do { \
        if (((handle >> 24) != DEMUX_MOD_VALUE) && ((handle >> 28) != DEMUX_MOD_VALUE)) \
        { \
            SM_ERR_PrintHex(handle); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_HANDLE); \
            return HI_ERR_SM_INVALID_HANDLE; \
        } \
    } while (0)


#define SM_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            SM_PrintErrorCode(HI_ERR_SM_NULL_PTR); \
            return HI_ERR_SM_NULL_PTR; \
        } \
    } while (0)

#define SM_CHECK_INTENT(intent) \
    do { \
        if (intent >= HI_UNF_SM_INTENT_BUTT) \
        { \
            SM_ERR_PrintHex(intent); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_INTENT); \
            return HI_ERR_SM_INVALID_INTENT; \
        } \
    } while (0)

#define SM_CHECK_SMHANDLE(handle) \
    do { \
        if (handle == HI_INVALID_HANDLE) \
        { \
            SM_ERR_PrintHex(handle); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_HANDLE); \
            return HI_ERR_SM_INVALID_HANDLE; \
        } \
    } while (0)

#define SM_CHECK_RESOURCE_NUM(num) \
    do {  \
        if (num <= 0 || num > 16) \
        {\
            SM_PrintErrorCode(HI_ERR_SM_INVALID_RESOURCE_NUM);\
            return HI_ERR_SM_INVALID_RESOURCE_NUM;\
        }\
    } while (0)


#define SM_CHECK_MODULEID(id) \
    do {  \
        if ( (HI_UNF_SM_MODULE_VDEC   != id) \
          && (HI_UNF_SM_MODULE_CIPHER != id) \
          && (HI_UNF_SM_MODULE_DEMUX  != id) \
          && (HI_UNF_SM_MODULE_DESCRAMBLER != id) \
          && (HI_UNF_SM_MODULE_KEYLADDER   != id) \
          && (HI_UNF_SM_MODULE_PLCIPHER    != id) \
          && (HI_UNF_SM_MODULE_AVPLAY      != id) \
          && (HI_UNF_SM_MODULE_PVR         != id)) \
        {\
            SM_ERR_PrintHex(id); \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_MODULEID);\
            return HI_ERR_SM_INVALID_MODULEID;\
        }\
    } while (0)


#define SM_CHECK_MODULEHANDLE(id, handle) \
    do { \
        if (HI_UNF_SM_MODULE_DEMUX == id) \
        { \
            CHECK_DEMUX_HANDLE(handle); \
        } \
        else if (HI_UNF_SM_MODULE_DESCRAMBLER == id) \
        { \
            CHECK_HANDLE(handle, DEMUX_MOD_VALUE, 24); \
        } \
        else if (HI_UNF_SM_MODULE_CIPHER == id) \
        { \
            CHECK_CIPHER_HANDLE(handle); \
        } \
        else if (HI_UNF_SM_MODULE_KEYLADDER == id) \
        { \
            CHECK_HANDLE(handle, KLAD_MOD_VALUE, 16); \
        } \
        else if (HI_UNF_SM_MODULE_PLCIPHER == id) \
        { \
            CHECK_HANDLE(handle, PLCIPHER_MOD_VALUE, 16); \
        } \
        else if (HI_UNF_SM_MODULE_VDEC == id) \
        { \
            CHECK_HANDLE(handle, VDEC_MOD_VALUE, 16); \
        } \
        else if (HI_UNF_SM_MODULE_PVR == id) \
        { \
          \
        } \
        else if (HI_UNF_SM_MODULE_AVPLAY == id) \
        { \
           CHECK_HANDLE(handle, AVPLAY_MOD_VALUE, 16); \
        } \
        else \
        { \
            SM_PrintErrorCode(HI_ERR_SM_INVALID_HANDLE); \
            return HI_ERR_SM_INVALID_HANDLE; \
        } \
    } while (0)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef SESSION_MANAGER_DEBUG*/
