/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_drv_klad.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_DRV_KLAD_H__
#define __HI_DRV_KLAD_H__

#include "hi_type.h"
#include "hi_error_mpi.h"
#include "hi_unf_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define HI_KLAD_MAX_SESSION  32 /*5bit*/
#define HI_KLAD_KEY_LENGTH   16
/*|-------------------------handle----------------------------|
  |         module:16bit       |        session:16bit         |
  |-----------------------------------------------------------|*/
#define HI_KLAD_MAKEHANDLE(mod, session)  \
    (HI_HANDLE)( (((mod)& 0xffff) << 16) | ((session) & 0xffff))
#define HI_KLAD_GET_MODID(handle)     (((handle) >> 16) & 0xffff)

#define HI_KLAD_GET_CATYPE(klad_type)    (((klad_type) >> 8) & 0xff)

#define HI_DEBUG_KLAD(fmt...)           HI_DBG_PRINT(HI_ID_CA,   fmt)
#define HI_FATAL_KLAD(fmt...)           HI_FATAL_PRINT(HI_ID_CA, fmt)
#define HI_ERR_KLAD(fmt...)             HI_ERR_PRINT(HI_ID_CA,   fmt)
#define HI_WARN_KLAD(fmt...)            HI_WARN_PRINT(HI_ID_CA,  fmt)
#define HI_INFO_KLAD(fmt...)            HI_INFO_PRINT(HI_ID_CA,  fmt)

#define KLAD_ERR_PrintHex(val)          HI_ERR_KLAD("%s = 0x%08X\n",#val, val)
#define KLAD_ERR_PrintInfo(val)         HI_ERR_KLAD("%s\n", val)
#define KLAD_ERR_PrintPoint(val)        HI_ERR_KLAD("%s = %p\n",    #val, val)


#define KLAD_PrintErrorCode(errCode)  HI_ERR_KLAD("return [0x%08x]\n", errCode)
#define KLAD_PrintErrorFunc(func,errCode)  HI_ERR_KLAD("Call [%s] return [0x%08x]\n", #func, errCode)

#define KLAD_FUNC_ENTER()  HI_DBG_PRINT(HI_ID_CA, "[ENTER]:%s\n", __FUNCTION__)
#define KLAD_FUNC_EXIT()   HI_DBG_PRINT(HI_ID_CA, "[EXIT] :%s\n", __FUNCTION__)

#define KLAD_CHECK_ALG(alg,high) \
    do {\
        if ((alg) > high) \
        {\
            KLAD_ERR_PrintHex(alg); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_ALG); \
            return HI_ERR_KLAD_INVALID_ALG;\
        }\
    } while(0)

#define KLAD_CHECK_TARGET_MOD(mod) \
    do {\
        if ((mod) >= (DRV_KLAD_TARGET_BUTT)) \
        {\
            KLAD_ERR_PrintHex(mod); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGET); \
            return HI_ERR_KLAD_INVALID_TARGET;\
        }\
    } while(0)

#define KLAD_CHECK_TARGET(handle) \
    do{ \
        if ((HI_HANDLE_GET_MODID(handle) != HI_ID_PLCIPHER) && \
            (HI_HANDLE_GET_MODID(handle) != HI_ID_CIPHER) && \
            (HI_HANDLE_GET_MODID(handle) >> 8 != HI_ID_DEMUX)) \
        {\
            KLAD_ERR_PrintHex(handle); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGET); \
            return HI_ERR_KLAD_INVALID_TARGET;\
        }\
    }while(0)

#define KLAD_CHECK_TARGET_ADDR(addr, high) \
    do {\
        if ((addr) >= (high)) \
        {\
            KLAD_ERR_PrintHex(addr); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_TARGETADDR); \
            return HI_ERR_KLAD_INVALID_TARGETADDR;\
        }\
    } while(0)

#define KLAD_CHECK_LEVEL(level) \
    do {\
        if ((level) >= (HI_UNF_KLAD_LEVEL_BUTT)) \
        {\
            KLAD_ERR_PrintHex(level); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_LEVEL); \
            return HI_ERR_KLAD_INVALID_LEVEL;\
        }\
    } while(0)

#define KLAD_CHECK_ENGINE(engine) \
    do{ \
        if (engine >= HI_UNF_KLAD_TARGET_ENGINE_BUTT)\
        {\
            KLAD_ERR_PrintHex(engine); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_ENGINE); \
            return HI_ERR_KLAD_INVALID_ENGINE;\
        }\
    }while(0)


#define KLAD_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            KLAD_ERR_PrintPoint(p); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_NULL_PTR); \
            return HI_ERR_KLAD_NULL_PTR; \
        } \
    } while (0)

#define KLAD_CHECK_INIT(init) \
    do{ \
        if (init <= 0)\
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_INIT); \
            return HI_ERR_KLAD_NOT_INIT;\
        }\
    }while(0)

#define KLAD_CHECK_HANDLE(handle) \
    do{ \
        if (HI_KLAD_GET_MODID(handle) != HI_ID_CA)\
        {\
            KLAD_ERR_PrintHex(handle); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_HANDLE); \
            return HI_ERR_KLAD_INVALID_HANDLE;\
        }\
    }while(0)


#define KLAD_CHECK_EVENORODD(even) \
    do{ \
        if ((HI_TRUE != even) && (HI_FALSE != even)) \
        {\
            KLAD_ERR_PrintHex(even); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_EVENORODD); \
            return HI_ERR_KLAD_INVALID_EVENORODD;\
        }\
    }while(0)


#define KLAD_CHECK_BOOL(b) \
    do{ \
        if ((HI_TRUE != b) && (HI_FALSE != b)) \
        {\
            KLAD_ERR_PrintHex(b); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_PARAM); \
            return HI_ERR_KLAD_INVALID_PARAM;\
        }\
    }while(0)

#define KLAD_CHECK_IV(iv, len) \
    do{ \
        if (iv > len) \
        {\
            KLAD_ERR_PrintHex(iv); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_IVLENGTH); \
            return HI_ERR_KLAD_INVALID_IVLENGTH;\
        }\
    }while(0)

#define KLAD_CHECK_PARAM(val) \
    do{ \
        if (val) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_INVALID_PARAM); \
            return HI_ERR_KLAD_INVALID_PARAM;\
        }\
    }while(0)

#define KLAD_CHECK_ATTR_FLAG(session) \
    do{ \
        if (HI_TRUE != session->instance.attr_flag) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_ATTR); \
            return HI_ERR_KLAD_NOT_SET_ATTR; \
        }\
    }while(0)

#define KLAD_CHECK_SESSION_KEY_FLAG(session,index) \
    do{ \
        if (HI_TRUE != session->instance.session_key_flag[index]) \
        {\
            KLAD_ERR_PrintHex(index); \
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_SESSIONKEY); \
            return HI_ERR_KLAD_NOT_SET_SESSIONKEY; \
        }\
    }while(0)

#define KLAD_CHECK_CONTENT_KEY_FLAG(session) \
    do{ \
        if (HI_TRUE != session->instance.content_key_flag) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_NOT_SET_CONTENTKEY); \
            return HI_ERR_KLAD_NOT_SET_CONTENTKEY; \
        }\
    }while(0)

#define KLAD_CHECK_TASK_ID(session) \
    do{ \
        if (session->instance.owner != task_tgid_nr(current)) \
        {\
            KLAD_PrintErrorCode(HI_ERR_KLAD_TASK_ID_MISMATCH); \
            return HI_ERR_KLAD_TASK_ID_MISMATCH; \
        }\
    }while(0)



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __HI_DRV_KLAD_H__ */
