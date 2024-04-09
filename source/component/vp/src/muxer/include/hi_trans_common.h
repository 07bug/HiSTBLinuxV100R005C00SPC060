#ifndef __HI_TRANS_COMMON_H__
#define __HI_TRANS_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


#ifndef Printf
#ifdef SOFT_BOARD_VERSION_ANDROID

#include <utils/Log.h>
#ifdef ALOGV
#define TRANS_LOGOUT(fmt...) \
    do{\
        ALOGE("[%s,%s, %d]",__FILE__,__FUNCTION__,__LINE__);\
        ALOGE(fmt);\
    }while(0)
#else
#define TRANS_LOGOUT(fmt...) \
    do{\
        LOGE("[%s,%s, %d]",__FILE__,__FUNCTION__,__LINE__);\
        LOGE(fmt);\
    }while(0)
#endif

#else
#define TRANS_LOGOUT(fmt...)\
    do{\
        printf("[%s,%s, %d]",__FILE__,__FUNCTION__,__LINE__);\
        printf(fmt);\
    }while(0)
#endif

#endif

#ifndef ABS
#define ABS(a,b) ((a) < (b)? ((b) - (a)) : ((a) - (b)))
#endif

#ifndef TRANS_CHK_PRINT
#define TRANS_CHK_PRINT(val, ...) \
    do \
    { \
        if ((val)) \
        { \
            TRANS_LOGOUT(__VA_ARGS__); \
        } \
    } while (0)
#endif

#ifndef TRANS_CHK_RETURN_NO_PRINT
#define TRANS_CHK_RETURN_NO_PRINT(val, s32Ret) \
    do \
    { \
        if ((val)) \
        { \
            return (s32Ret); \
        } \
    } while (0)
#endif

#ifndef TRANS_CHK_RETURN_PRINT
#define TRANS_CHK_RETURN_PRINT(val, s32Ret, ...) \
    do \
    { \
        if ((val)) \
        { \
            TRANS_LOGOUT(__VA_ARGS__); \
            return (s32Ret); \
        } \
    } while (0)
#endif

#ifndef TRANS_GOTO_LAB_PRINT
#define TRANS_GOTO_LAB_PRINT(val, lab, ...) \
    do \
    { \
        if ((val)) \
        { \
            TRANS_LOGOUT(__VA_ARGS__); \
            goto lab; \
        } \
    } while (0)
#endif

#define CHECK_NULL_PTR_RETURN(p) \
    do{\
        if(HI_NULL == p)\
        {\
            TRANS_LOGOUT("NULL pointer error\n"); \
            return HI_FAILURE;\
        }\
    }while(0)

#define POINTER_FREE(ptr) \
    do \
    { \
        if(HI_NULL != ptr) \
        { \
            free((HI_VOID *)ptr); \
            (ptr) = HI_NULL; \
        } \
    }while(0)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
