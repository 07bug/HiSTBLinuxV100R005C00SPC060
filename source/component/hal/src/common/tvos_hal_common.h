/**
 * \file hal_common.h
 * \brief hal common micro define.
*/

#ifndef __HAL_COMMON_H__
#define __HAL_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tvos_hal_type.h"
#ifndef LINUX_OS

#include "utils/Log.h"
#else
#define ALOGE printf
#define ALOGD
#define ALOGV
#define ALOGW printf
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define HAL_DEBUG_ENTER()
    //HAL_DEBUG("%s,%d enter...", __func__, __LINE__)
#define HAL_DEBUG_EXIT()
    //HAL_DEBUG("%s,%d exit.", __func__, __LINE__)

#define HAL_NDEBUG  0

#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

/** Defines the type of log level *//** CNcomment:定义日志优先级 */
typedef enum _HAL_LOGLEVEL_E {
    HAL_LOG_UNKNOWN = 0,
    HAL_LOG_DEFAULT,     /* only for SetMinPriority() */
    HAL_LOG_VERBOSE,     /**<lowest priority *//**<CNcomment:最低优先级 */
    HAL_LOG_DEBUG,       /**<debug priority *//**<CNcomment:打印debug信息 */
    HAL_LOG_INFO,        /**<info priority *//**<CNcomment:打印info信息 */
    HAL_LOG_WARN,        /**<warnning priority *//**<CNcomment:打印warnning信息 */
    HAL_LOG_ERROR,       /**<error priority *//**<CNcomment:打印error信息 */
    HAL_LOG_FATAL,       /**<fatal priority *//**<CNcomment:打印fatal信息 */
    HAL_LOG_SILENT,      /* only for SetMinPriority(); must be last */
} HAL_LOGLEVEL_E;

#ifndef LOGGER
#define LOGGER(priority, tag, ...) \
    LOG_PRIORITY(priority, tag, __VA_ARGS__)
#endif

#ifndef LOG_PRIORITY
#define LOG_PRIORITY(prio, tag, fmt...) \
    __android_log_print(prio, tag, fmt)
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef HAL_DEBUG
#if HAL_NDEBUG
#define HAL_DEBUG(...) ((void)0)
#else
//#define HAL_DEBUG HI_LOGD
#define HAL_DEBUG ALOGD
#endif
#endif

/*
 * Simplified macro to send an error log message using the current LOG_TAG.
 */
#ifndef HAL_ERROR
#if HAL_NDEBUG
#define HAL_ERROR(...) ((void)0)
#else
//#define HAL_ERROR HI_LOGE
#define HAL_ERROR ALOGE
#endif
#endif

#ifndef HAL_CHK_GOTO
#define HAL_CHK_GOTO(val, label, ...) \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR(__VA_ARGS__); \
            goto label; \
        } \
    } while (0)
#endif

#ifndef HAL_CHK_PRINTF
#define HAL_CHK_PRINTF(val, ...) /*lint -save -e506 -e774*/ \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR(__VA_ARGS__); \
        } \
    } while (0) /*lint -restore */
#endif

#ifndef HAL_CHK_RETURN
#define HAL_CHK_RETURN(val, ret, ...) /*lint -save -e64*/ \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR(__VA_ARGS__); \
            return (ret); \
        } \
    } while (0) /*lint -restore */
#endif

#ifndef HAL_CHK_RETURN_VOID
#define HAL_CHK_RETURN_VOID(val, ...) /*lint -save -e64*/ \
    do \
    { \
        if ((val)) \
        { \
            HAL_ERROR(__VA_ARGS__); \
            return; \
        } \
    } while (0) /*lint -restore */
#endif

#ifndef HAL_CHK_RETURN_NO_PRINT
#define HAL_CHK_RETURN_NO_PRINT(val, ret) /*lint -save -e64*/ \
    do \
    { \
        if ((val)) \
        { \
            return (ret); \
        } \
    } while (0) /*lint -restore */
#endif

#ifndef HAL_CHK_CALL_RETURN
#define HAL_CHK_CALL_RETURN(val, ret, fun, ...) /*lint -save -e64*/ \
    do \
    { \
        if ((val)) \
        { \
            fun;\
            HAL_ERROR(__VA_ARGS__); \
            return (ret); \
        } \
    } while (0) /*lint -restore */
#endif

#ifndef HAL_MEMSET
#define HAL_MEMSET(ptr, val, size) \
    do \
    { \
        /*lint -save -e774 -e506*/ \
        if (NULL != (ptr)) \
        { \
            memset((ptr), (val), (size)); \
        } \
        /*lint -restore*/ \
    } while (0)
#endif

#ifndef HAL_MEMSET_NO_VERIFY
#define HAL_MEMSET_NO_VERIFY(ptr, val, size) \
    do \
    { \
        memset((ptr), (val), (size)); \
    } while (0)
#endif

#ifndef HAL_MEMMOVE
#define HAL_MEMMOVE(ptrdst, ptrsrc, size) /*lint -save -e774 -e944*/ \
    do \
    { \
        if (NULL != (ptrdst) && NULL != (ptrsrc)) \
        { \
            memmove((ptrdst), (ptrsrc), (size)); \
        } \
    } while (0) /*lint -restore*/
#endif

#ifndef HAL_MEMCPY
#define HAL_MEMCPY(ptrdst, ptrsrc, size) /*lint -save -e774 -e944 -e506*/ \
    do \
    { \
        if (NULL != (ptrdst) && NULL != (ptrsrc)) \
        { \
            memcpy((ptrdst), (ptrsrc), (size)); \
        } \
    } while (0) /*lint -restore*/
#endif

#ifndef HAL_MEMCPY_NO_VERIFY
#define HAL_MEMCPY_NO_VERIFY(ptrdst, ptrsrc, size) /*lint -save -e774 -e944 -e506*/ \
    do \
    { \
        memcpy((ptrdst), (ptrsrc), (size)); \
    } while (0) /*lint -restore*/
#endif

#ifndef HAL_MEMCMP
#define HAL_MEMCMP      memcmp
#endif

#ifndef HAL_MALLOC
#define HAL_MALLOC      malloc
#endif

#ifndef HAL_REALLOC
#define HAL_REALLOC     realloc
#endif

#ifndef HAL_FREE
#define HAL_FREE        free
#endif

#ifndef HAL_USLEEP
#define HAL_USLEEP(ms)  usleep(ms)
#endif

S32 disable_display_output(VOID);
S32 enable_display_output(VOID);
S32 disable_audio_output(VOID);
S32 restore_audio_output(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HAL_COMMON_H__ */
