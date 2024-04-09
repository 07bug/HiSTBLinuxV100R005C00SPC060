/******************************************************************************
 Copyright (C), 2015-2025, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : Logger.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2015/7/14
Last Modified :
Description   : Logger module.
                CNcomment: Loggerģ��CNend
Function List :
History       :
******************************************************************************/
#ifndef DFX_LOGGER_H_
#define DFX_LOGGER_H_

#include <cutils/logd.h>

/*************************** Structure Definition ****************************/
/** \addtogroup      LOGGER */
/** @{ */  /** <!-- [LOGGER]*/

/*
 * Normally we strip HI_LOGV (VERBOSE messages) from release builds.
 * You can modify this (for example with "#define LOG_NDEBUG 0"
 * at the top of your source file) to change that behavior.
 */
#ifndef LOG_NDEBUG
#ifdef NDEBUG
#define LOG_NDEBUG 1
#else
#define LOG_NDEBUG 0
#endif
#endif

#ifdef LINUX_DEBUGLOG
#define LOG_LINUX 1
#define ERROR_TAG "[ERROR]"
#define INFO_TAG  "[INFO]"
#define DEBUG_TAG "[DEBUG]"
#define WARN_TAG  "[WARNING]"
#define VRBOSE_TAG "[VERBOSE]"

#define ERROR_LEVEL   (1)
#define WARNING_LEVEL (2)
#define INFO_LEVEL    (3)
#define DEBUG_LEVEL   (4)
#define VERBOSE_LEVEL (5)

#define DRM_LOG_LEVEL ERROR_LEVEL

#else
#define LOG_LINUX 0
#endif

/*
 * This is the local tag used for the following simplified
 * logging macros.  You can change this preprocessor definition
 * before using the other macros to change the tag.
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

/** Defines the type of log level *//** CNcomment:������־���ȼ� */
typedef enum hiLOGGERLEVEL_E {
    HI_LOGGER_UNKNOWN = 0,
    HI_LOGGER_DEFAULT,     /* only for SetMinPriority() */
    HI_LOGGER_VERBOSE,     /**<lowest priority *//**<CNcomment:������ȼ� */
    HI_LOGGER_DEBUG,       /**<debug priority *//**<CNcomment:��ӡdebug��Ϣ */
    HI_LOGGER_INFO,        /**<info priority *//**<CNcomment:��ӡinfo��Ϣ */
    HI_LOGGER_WARN,        /**<warnning priority *//**<CNcomment:��ӡwarnning��Ϣ */
    HI_LOGGER_ERROR,       /**<error priority *//**<CNcomment:��ӡerror��Ϣ */
    HI_LOGGER_FATAL,       /**<fatal priority *//**<CNcomment:��ӡfatal��Ϣ */
    HI_LOGGER_SILENT,      /* only for SetMinPriority(); must be last */
} HI_LOGGERLEVEL_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      LOGGER */
/** @{ */  /** <!-- [LOGGER]*/

/*
 * Basic log message macro.
 *
 * Example:
 *  LOGGER(HI_LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef LOGGER
#define LOGGER(priority, tag, file, line, ...) \
    LOG_PRIORITY(priority, tag, file, line, __VA_ARGS__)
#endif

#if 1
#define LOG_PRIORITY(prio, tag, file, line, fmt...) \
    __android_log_print_ex(prio, tag, file, line, fmt)
#else
#define LOG_PRIORITY(prio, tag, file, line, fmt...) \
     __android_log_print(prio, tag, fmt)
#endif

/*
 * Simplified macro to send a verbose log message using the current LOG_TAG.
 */
#ifndef HI_LOGV
#if LOG_LINUX
#define HI_LOGV(fmt, args...) printf("%s %s, %d:" fmt "\n", VERBOSE_TAG,  __FUNCTION__, __LINE__, ## args)
#else
#if LOG_NDEBUG
#define HI_LOGV(...) ((void)0)
#else
#define HI_LOGV(...) ((void)LOGGER(HI_LOGGER_VERBOSE, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef HI_LOGD
#if LOG_LINUX
#define HI_LOGD(fmt, args...) printf("%s %s, %d:" fmt "\n", DEBUG_TAG, __FUNCTION__, __LINE__, ## args)
#else
#if LOG_NDEBUG
#define HI_LOGD(...) ((void)0)
#else
#define HI_LOGD(...) ((void)LOGGER(HI_LOGGER_DEBUG, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif
#endif

/*
 * Simplified macro to send an info log message using the current LOG_TAG.
 */
#ifndef HI_LOGI
#if LOG_LINUX
#define HI_LOGI(fmt, args...) printf("%s %s, %d:" fmt "\n", INFO_TAG,  __FUNCTION__, __LINE__, ## args)
#else
#if LOG_NDEBUG
#define HI_LOGI(...) ((void)0)
#else
#define HI_LOGI(...) ((void)LOGGER(HI_LOGGER_INFO, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif
#endif

/*
 * Simplified macro to send a warning log message using the current LOG_TAG.
 */
#ifndef HI_LOGW
#if LOG_LINUX
#define HI_LOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WARN_TAG,  __FUNCTION__, __LINE__, ## args)
#else
#if LOG_NDEBUG
#define HI_LOGW(...) ((void)0)
#else
#define HI_LOGW(...) ((void)LOGGER(HI_LOGGER_WARN, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif
#endif

/*
 * Simplified macro to send an error log message using the current LOG_TAG.
 */
#ifndef HI_LOGE
#if LOG_LINUX
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#else
#if LOG_NDEBUG
#define HI_LOGE(...) ((void)0)
#else
#define HI_LOGE(...) ((void)LOGGER(HI_LOGGER_ERROR, LOG_TAG, __FILE__, __LINE__, __VA_ARGS__))
#endif
#endif
#endif

#if LOG_LINUX

#ifdef HI_LOGE
#undef HI_LOGE
#endif

#ifdef HI_LOGW
#undef HI_LOGW
#endif

#ifdef HI_LOGI
#undef HI_LOGI
#endif

#ifdef HI_LOGD
#undef HI_LOGD
#endif

#ifdef HI_LOGV
#undef HI_LOGV
#endif

#if (DRM_LOG_LEVEL == ERROR_LEVEL)
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...)
#define HI_LOGI(fmt, args...)
#define HI_LOGD(fmt, args...)
#define HI_LOGV(fmt, args...)
#elif (DRM_LOG_LEVEL == WARNING_LEVEL)
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WAR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGI(fmt, args...)
#define HI_LOGD(fmt, args...)
#define HI_LOGV(fmt, args...)
#elif (DRM_LOG_LEVEL == INFO_LEVEL)
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WAR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGI(fmt, args...) printf("%s %s, %d:" fmt "\n", INFO_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGD(fmt, args...)
#define HI_LOGV(fmt, args...)
#elif (DRM_LOG_LEVEL == DEBUG_LEVEL)
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WAR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGI(fmt, args...) printf("%s %s, %d:" fmt "\n", INFO_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGD(fmt, args...) printf("%s %s, %d:" fmt "\n", DEBUG_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGV(fmt, args...)
#elif (DRM_LOG_LEVEL == VERBOSE_LEVEL)
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WAR_TAG,  __FUNCTION__, __LINE__, ## args)
#define HI_LOGI(fmt, args...) printf("%s %s, %d:" fmt "\n", INFO_TAG,  __FUNCTION__, __LINE__, ## args)
#define HI_LOGD(fmt, args...) printf("%s %s, %d:" fmt "\n", DEBUG_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGV(fmt, args...) printf("%s %s, %d:" fmt "\n", VERBOSE_TAG,  __FUNCTION__, __LINE__, ## args)
#else
#define HI_LOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#define HI_LOGW(fmt, args...)
#define HI_LOGI(fmt, args...)
#define HI_LOGD(fmt, args...)
#define HI_LOGV(fmt, args...)
#endif
#endif


/** @} */  /** <!-- ==== API declaration end ==== */

#endif /* DFX_LOGGER_H_ */
