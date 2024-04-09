/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_mailbox_debug.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_MAILBOX_DEBUG_H__
#define __DRV_MAILBOX_DEBUG_H__

#include "drv_mailbox.h"

#include "hi_error_mpi.h"
#include "hi_type.h"
#include "hi_debug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

//#define MAILBOX_DEBUG

#define HI_DEBUG_MAILBOX(fmt...)           HI_DBG_PRINT(HI_ID_MAILBOX,   fmt)
#define HI_FATAL_MAILBOX(fmt...)           HI_FATAL_PRINT(HI_ID_MAILBOX, fmt)
#define HI_ERR_MAILBOX(fmt...)             HI_ERR_PRINT(HI_ID_MAILBOX,   fmt)
#define HI_WARN_MAILBOX(fmt...)            HI_WARN_PRINT(HI_ID_MAILBOX,  fmt)
#define HI_INFO_MAILBOX(fmt...)            HI_INFO_PRINT(HI_ID_MAILBOX,  fmt)


#define MAILBOX_DBG_PrintHex(val)          HI_DEBUG_MAILBOX("%s = 0x%08X\n",#val, val)
#define MAILBOX_DBG_PrintInfo(val)         HI_DEBUG_MAILBOX("%s\n", val)
#define MAILBOX_DBG_PrintPoint(val)        HI_DEBUG_MAILBOX("%s = %p\n",    #val, val)

#define MAILBOX_ERR_PrintHex(val)          HI_ERR_MAILBOX("%s = 0x%08X\n",#val, val)
#define MAILBOX_ERR_PrintInfo(val)         HI_ERR_MAILBOX("%s\n", val)
#define MAILBOX_ERR_PrintPoint(val)        HI_ERR_MAILBOX("%s = %p\n",    #val, val)


#define MAILBOX_PrintErrorCode(errCode)       HI_ERR_MAILBOX("return [0x%08x]\n", errCode)
#define MAILBOX_PrintErrorFunc(func,errCode)  HI_ERR_MAILBOX("Call [%s] return [0x%08x]\n", #func, errCode)

#define MAILBOX_FUNC_ENTER()               HI_DBG_PRINT(HI_ID_MAILBOX, "[ENTER]:%s\n", __FUNCTION__)
#define MAILBOX_FUNC_EXIT()                HI_DBG_PRINT(HI_ID_MAILBOX, "[EXIT] :%s\n", __FUNCTION__)


#ifdef MAILBOX_DEBUG
#define MAILBOX_DBG_DUMP(string, ptr, len) \
    do {\
        HI_U32 i; \
        MAILBOX_DBG_PrintInfo(string);\
        for (i = 0; i < len ;i++) \
        { \
            if ((i != 0) && ((i % 16) == 0)) \
            {\
                HI_PRINT("\n");\
            }\
            HI_PRINT("%x ", ((HI_U8 *)ptr)[i]); \
        }\
        HI_PRINT("\n");\
    } while (0)
#else
#define MAILBOX_DBG_DUMP(string, ptr, len)
#endif

#define MAILBOX_CHECK_FLAG(flag) \
    do {\
        if (((flag) != 0) && ((flag) != 1)) \
        {\
            MAILBOX_ERR_PrintHex(flag); \
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_FLAG); \
            return HI_ERR_MAILBOX_INVALID_FLAG;\
        }\
    } while(0)


#define MAILBOX_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_PTR); \
            return HI_ERR_MAILBOX_INVALID_PTR; \
        } \
    } while (0)


#define MAILBOX_CHECK_HANDLE(handle) \
    do{ \
        if ((handle >> 16) != HI_ID_MAILBOX)\
        {\
            MAILBOX_ERR_PrintHex(handle); \
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_HANDLE); \
            return HI_ERR_MAILBOX_INVALID_HANDLE;\
        }\
    }while(0)


#define MAILBOX_CHECK_RECEIVER(receiver) \
    do{ \
        if ((receiver != MID_SCPU_COMMON) && (receiver != MID_SCPU_CAS) && (receiver != MID_SMCU_SCS) \
            && (receiver != MID_SMCU_KEY_PROVISION) && (receiver != MID_SMCU_KEY_PROVISION) \
            && (receiver != MID_SMCU_SEC_STANDBY) && (receiver != MID_SMCU_RUNTIME_CHECK) && (receiver != MID_SMCU_RUNTIME_CHECK_FS))\
        {\
            MAILBOX_ERR_PrintHex(receiver); \
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_RECEIVER); \
            return HI_ERR_MAILBOX_INVALID_RECEIVER;\
        }\
    }while(0)


#define MAILBOX_CHECK_PARAM(value) \
    do{ \
        if ((value) != HI_TRUE) \
        {\
            MAILBOX_ERR_PrintInfo((value)); \
            return HI_ERR_MAILBOX_INVALID_PARA;\
        }\
    }while(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_MAILBOX_DEBUG_H__ */
