/*
 * Copyright (C) 2005-2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// C/C++ logging functions.  See the logging documentation for API details.
//
// We'd like these to be available from C code (in case we import some from
// somewhere), so this has a C interface.
//
// The output will be correct when the log file is shared between multiple
// threads and/or multiple processes so long as the operating system
// supports O_APPEND.  These calls have mutex-protected data structures
// and so are NOT reentrant.  Do not use LOG in a signal handler.
//
#ifndef _LIBS_LOG_LOG_H
#define _LIBS_LOG_LOG_H

#include <sys/types.h>
#ifdef HAVE_PTHREADS
#include <pthread.h>
#endif
#include <stdarg.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <cutils/logd.h>
#include <cutils/uio.h>

#ifdef __cplusplus
extern "C" {
#endif

// ---------------------------------------------------------------------

/*
 * Normally we strip ALOGV (VERBOSE messages) from release builds.
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
#define WAR_TAG "[WARNING]"
#define VERBOSE_TAG "[VERBOSE]"

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

// ---------------------------------------------------------------------

/*
 * Simplified macro to send a verbose log message using the current LOG_TAG.
 */
#ifndef ALOGV
#if LOG_LINUX
#define __ALOGV(fmt, args...) printf("%s %s, %d:" fmt "\n", VERBOSE_TAG, __FUNCTION__, __LINE__, ## args)
#else
#define __ALOGV(...) ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#endif
#if LOG_NDEBUG
#define ALOGV(...) do { if (0) { __ALOGV(__VA_ARGS__); } } while (0)
#else
#define ALOGV(...) __ALOGV(__VA_ARGS__)
#endif
#endif

#define CONDITION(cond)     (__builtin_expect((cond)!=0, 0))

#ifndef ALOGV_IF
#if LOG_NDEBUG
#define ALOGV_IF(cond, ...)   ((void)0)
#else
#define ALOGV_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG(LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif
#endif

/*
 * Simplified macro to send a debug log message using the current LOG_TAG.
 */
#ifndef ALOGD
#if LOG_LINUX
#define ALOGD(fmt, args...) printf("%s %s, %d:" fmt "\n", DEBUG_TAG, __FUNCTION__, __LINE__, ## args)
#else
#define ALOGD(...) ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGD_IF
#define ALOGD_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG(LOG_DEBUG, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an info log message using the current LOG_TAG.
 */
#ifndef ALOGI
#if LOG_LINUX
#define ALOGI(fmt, args...) printf("%s %s, %d:" fmt "\n", INFO_TAG, __FUNCTION__, __LINE__, ## args)
#else
#define ALOGI(...) ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGI_IF
#define ALOGI_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG(LOG_INFO, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send a warning log message using the current LOG_TAG.
 */
#ifndef ALOGW
#if LOG_LINUX
#define ALOGW(fmt, args...) printf("%s %s, %d:" fmt "\n", WAR_TAG, __FUNCTION__, __LINE__, ## args)
#else
#define ALOGW(...) ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGW_IF
#define ALOGW_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG(LOG_WARN, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an error log message using the current LOG_TAG.
 */
#ifndef ALOGE
#if LOG_LINUX
#define ALOGE(fmt, args...) printf("%s %s, %d:" fmt "\n", ERROR_TAG, __FUNCTION__, __LINE__, ## args)
#else
#define ALOGE(...) ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif
#endif

#ifndef ALOGE_IF
#define ALOGE_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)ALOG(LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

// ---------------------------------------------------------------------

/*
 * Conditional based on whether the current LOG_TAG is enabled at
 * verbose priority.
 */
#ifndef IF_ALOGV
#if LOG_NDEBUG
#define IF_ALOGV() if (false)
#else
#define IF_ALOGV() IF_ALOG(LOG_VERBOSE, LOG_TAG)
#endif
#endif

/*
 * Conditional based on whether the current LOG_TAG is enabled at
 * debug priority.
 */
#ifndef IF_ALOGD
#define IF_ALOGD() IF_ALOG(LOG_DEBUG, LOG_TAG)
#endif

/*
 * Conditional based on whether the current LOG_TAG is enabled at
 * info priority.
 */
#ifndef IF_ALOGI
#define IF_ALOGI() IF_ALOG(LOG_INFO, LOG_TAG)
#endif

/*
 * Conditional based on whether the current LOG_TAG is enabled at
 * warn priority.
 */
#ifndef IF_ALOGW
#define IF_ALOGW() IF_ALOG(LOG_WARN, LOG_TAG)
#endif

/*
 * Conditional based on whether the current LOG_TAG is enabled at
 * error priority.
 */
#ifndef IF_ALOGE
#define IF_ALOGE() IF_ALOG(LOG_ERROR, LOG_TAG)
#endif

// ---------------------------------------------------------------------

/*
 * Simplified macro to send a verbose system log message using the current LOG_TAG.
 */
#ifndef SLOGV
#define __SLOGV(...) ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#if LOG_NDEBUG
#define SLOGV(...) do { if (0) { __SLOGV(__VA_ARGS__); } } while (0)
#else
#define SLOGV(...) __SLOGV(__VA_ARGS__)
#endif
#endif

#define CONDITION(cond)     (__builtin_expect((cond)!=0, 0))

#ifndef SLOGV_IF
#if LOG_NDEBUG
#define SLOGV_IF(cond, ...)   ((void)0)
#else
#define SLOGV_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif
#endif

/*
 * Simplified macro to send a debug system log message using the current LOG_TAG.
 */
#ifndef SLOGD
#define SLOGD(...) ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif

#ifndef SLOGD_IF
#define SLOGD_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an info system log message using the current LOG_TAG.
 */
#ifndef SLOGI
#define SLOGI(...) ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif

#ifndef SLOGI_IF
#define SLOGI_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send a warning system log message using the current LOG_TAG.
 */
#ifndef SLOGW
#define SLOGW(...) ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif

#ifndef SLOGW_IF
#define SLOGW_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an error system log message using the current LOG_TAG.
 */
#ifndef SLOGE
#define SLOGE(...) ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif

#ifndef SLOGE_IF
#define SLOGE_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_SYSTEM, ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

// ---------------------------------------------------------------------

/*
 * Simplified macro to send a verbose radio log message using the current LOG_TAG.
 */
#ifndef RLOGV
#define __RLOGV(...) ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__))
#if LOG_NDEBUG
#define RLOGV(...) do { if (0) { __RLOGV(__VA_ARGS__); } } while (0)
#else
#define RLOGV(...) __RLOGV(__VA_ARGS__)
#endif
#endif

#define CONDITION(cond)     (__builtin_expect((cond)!=0, 0))

#ifndef RLOGV_IF
#if LOG_NDEBUG
#define RLOGV_IF(cond, ...)   ((void)0)
#else
#define RLOGV_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif
#endif

/*
 * Simplified macro to send a debug radio log message using the current LOG_TAG.
 */
#ifndef RLOGD
#define RLOGD(...) ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#endif

#ifndef RLOGD_IF
#define RLOGD_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an info radio log message using the current LOG_TAG.
 */
#ifndef RLOGI
#define RLOGI(...) ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#endif

#ifndef RLOGI_IF
#define RLOGI_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send a warning radio log message using the current LOG_TAG.
 */
#ifndef RLOGW
#define RLOGW(...) ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
#endif

#ifndef RLOGW_IF
#define RLOGW_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

/*
 * Simplified macro to send an error radio log message using the current LOG_TAG.
 */
#ifndef RLOGE
#define RLOGE(...) ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
#endif

#ifndef RLOGE_IF
#define RLOGE_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)__android_log_buf_print(LOG_ID_RADIO, ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)) \
    : (void)0 )
#endif

// ---------------------------------------------------------------------

/*
 * Log a fatal error.  If the given condition fails, this stops program
 * execution like a normal assertion, but also generating the given message.
 * It is NOT stripped from release builds.  Note that the condition test
 * is -inverted- from the normal assert() semantics.
 */
#ifndef LOG_ALWAYS_FATAL_IF
#define LOG_ALWAYS_FATAL_IF(cond, ...) \
    ( (CONDITION(cond)) \
    ? ((void)android_printAssert(#cond, LOG_TAG, ## __VA_ARGS__)) \
    : (void)0 )
#endif

#ifndef LOG_ALWAYS_FATAL
#define LOG_ALWAYS_FATAL(...) \
    ( ((void)android_printAssert(NULL, LOG_TAG, ## __VA_ARGS__)) )
#endif

/*
 * Versions of LOG_ALWAYS_FATAL_IF and LOG_ALWAYS_FATAL that
 * are stripped out of release builds.
 */
#if LOG_NDEBUG

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) ((void)0)
#endif
#ifndef LOG_FATAL
#define LOG_FATAL(...) ((void)0)
#endif

#else

#ifndef LOG_FATAL_IF
#define LOG_FATAL_IF(cond, ...) LOG_ALWAYS_FATAL_IF(cond, ## __VA_ARGS__)
#endif
#ifndef LOG_FATAL
#define LOG_FATAL(...) LOG_ALWAYS_FATAL(__VA_ARGS__)
#endif

#endif

/*
 * Assertion that generates a log message when the assertion fails.
 * Stripped out of release builds.  Uses the current LOG_TAG.
 */
#ifndef ALOG_ASSERT
#define ALOG_ASSERT(cond, ...) LOG_FATAL_IF(!(cond), ## __VA_ARGS__)
//#define ALOG_ASSERT(cond) LOG_FATAL_IF(!(cond), "Assertion failed: " #cond)
#endif

// ---------------------------------------------------------------------

/*
 * Basic log message macro.
 *
 * Example:
 *  ALOG(LOG_WARN, NULL, "Failed with error %d", errno);
 *
 * The second argument may be NULL or "" to indicate the "global" tag.
 */
#ifndef ALOG
#define ALOG(priority, tag, ...) \
    LOG_PRI(ANDROID_##priority, tag, __VA_ARGS__)
#endif

/*
 * Log macro that allows you to specify a number for the priority.
 */
#ifndef LOG_PRI
#define LOG_PRI(priority, tag, ...) \
    android_printLog(priority, tag, __VA_ARGS__)
#endif

/*
 * Log macro that allows you to pass in a varargs ("args" is a va_list).
 */
#ifndef LOG_PRI_VA
#define LOG_PRI_VA(priority, tag, fmt, args) \
    android_vprintLog(priority, NULL, tag, fmt, args)
#endif

/*
 * Conditional given a desired logging priority and tag.
 */
#ifndef IF_ALOG
#define IF_ALOG(priority, tag) \
    if (android_testLog(ANDROID_##priority, tag))
#endif

// ---------------------------------------------------------------------

/*
 * Event logging.
 */

/*
 * Event log entry types.  These must match up with the declarations in
 * java/android/android/util/EventLog.java.
 */
typedef enum {
    EVENT_TYPE_INT      = 0,
    EVENT_TYPE_LONG     = 1,
    EVENT_TYPE_STRING   = 2,
    EVENT_TYPE_LIST     = 3,
} AndroidEventLogType;
#define sizeof_AndroidEventLogType sizeof(typeof_AndroidEventLogType)
#define typeof_AndroidEventLogType unsigned char

#ifndef LOG_EVENT_INT
#define LOG_EVENT_INT(_tag, _value) {                                       \
        int intBuf = _value;                                                \
        (void) android_btWriteLog(_tag, EVENT_TYPE_INT, &intBuf,            \
            sizeof(intBuf));                                                \
    }
#endif
#ifndef LOG_EVENT_LONG
#define LOG_EVENT_LONG(_tag, _value) {                                      \
        long long longBuf = _value;                                         \
        (void) android_btWriteLog(_tag, EVENT_TYPE_LONG, &longBuf,          \
            sizeof(longBuf));                                               \
    }
#endif
#ifndef LOG_EVENT_STRING
#define LOG_EVENT_STRING(_tag, _value)                                      \
        (void) __android_log_bswrite(_tag, _value);
#endif
/* TODO: something for LIST */

/*
 * ===========================================================================
 *
 * The stuff in the rest of this file should not be used directly.
 */

#define android_printLog(prio, tag, fmt...) \
    __android_log_print(prio, tag, fmt)

#define android_vprintLog(prio, cond, tag, fmt...) \
    __android_log_vprint(prio, tag, fmt)

/* XXX Macros to work around syntax errors in places where format string
 * arg is not passed to ALOG_ASSERT, LOG_ALWAYS_FATAL or LOG_ALWAYS_FATAL_IF
 * (happens only in debug builds).
 */

/* Returns 2nd arg.  Used to substitute default value if caller's vararg list
 * is empty.
 */
#define __android_second(dummy, second, ...)     second

/* If passed multiple args, returns ',' followed by all but 1st arg, otherwise
 * returns nothing.
 */
#define __android_rest(first, ...)               , ## __VA_ARGS__

#define android_printAssert(cond, tag, fmt...) \
    __android_log_assert(cond, tag, \
        __android_second(0, ## fmt, NULL) __android_rest(fmt))

#define android_writeLog(prio, tag, text) \
    __android_log_write(prio, tag, text)

#define android_bWriteLog(tag, payload, len) \
    __android_log_bwrite(tag, payload, len)
#define android_btWriteLog(tag, type, payload, len) \
    __android_log_btwrite(tag, type, payload, len)

// TODO: remove these prototypes and their users
#define android_testLog(prio, tag) (1)
#define android_writevLog(vec,num) do{}while(0)
#define android_write1Log(str,len) do{}while (0)
#define android_setMinPriority(tag, prio) do{}while(0)
//#define android_logToCallback(func) do{}while(0)
#define android_logToFile(tag, file) (0)
#define android_logToFd(tag, fd) (0)

typedef enum log_id {
    LOG_ID_MIN = 0,

    LOG_ID_MAIN = 0,
    LOG_ID_RADIO = 1,
    LOG_ID_EVENTS = 2,
    LOG_ID_SYSTEM = 3,
    LOG_ID_CRASH = 4,

    LOG_ID_MAX
} log_id_t;
#define sizeof_log_id_t sizeof(typeof_log_id_t)
#define typeof_log_id_t unsigned char

/*
 * Send a simple string to the log.
 */
int __android_log_buf_write(int bufID, int prio, const char *tag, const char *text);
int __android_log_buf_print(int bufID, int prio, const char *tag, const char *fmt, ...)
#if defined(__GNUC__)
    __attribute__((__format__(printf, 4, 5)))
#endif
    ;

#ifndef TEMP_FAILURE_RETRY
/* Used to retry syscalls that can return EINTR. */
#define TEMP_FAILURE_RETRY(exp) ({         \
    typeof (exp) _rc;                      \
    do {                                   \
        _rc = (exp);                       \
    } while (_rc == -1 && errno == EINTR); \
    _rc; })
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

#ifdef ALOGE
#undef ALOGE
#endif

#ifdef ALOGW
#undef ALOGW
#endif

#ifdef ALOGI
#undef ALOGI
#endif

#ifdef ALOGD
#undef ALOGD
#endif

#ifdef ALOGV
#undef ALOGV
#endif

#define ALOGE(fmt, args...)  HI_LOGE(fmt, ##args)
#define ALOGW(fmt, args...)  HI_LOGW(fmt, ##args)
#define ALOGI(fmt, args...)  HI_LOGI(fmt, ##args)
#define ALOGD(fmt, args...)  HI_LOGD(fmt, ##args)
#define ALOGV(fmt, args...)  HI_LOGV(fmt, ##args)

#endif

#ifdef __cplusplus
}
#endif

#endif /* _LIBS_LOG_LOG_H */
