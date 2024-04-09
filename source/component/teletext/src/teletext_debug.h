#ifndef __TELETEXT_DEBUG_H__
#define __TELETEXT_DEBUG_H__

#define TTX_SLEEP(ms)  \
    do{\
        struct timespec  _ts;\
        _ts.tv_sec = (ms) >= 1000 ? (ms)/1000 : 0;\
        _ts.tv_nsec =  (_ts.tv_sec > 0) ? ((ms)%1000)*1000000LL : (ms) * 1000000LL;\
        (HI_VOID)nanosleep(&_ts, NULL);\
    }while (0)

#ifndef __LITEOS__

#include "hi_unf_version.h"

//UNF version 3.5 use hi_log, instead of hi_debug
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 5))

#define LOG_D_MODULE_ID HI_ID_TTX

#include "hi_log.h"
#include "hi_mpi_mem.h"

#ifndef HI_MALLOC
#define HI_MALLOC malloc
#endif
#ifndef HI_FREE
#define HI_FREE free
#endif
#define HI_MEMTTX_MALLOC(u32Size)    (HI_MALLOC(u32Size))
#define HI_MEMTTX_FREE(pvMemAddr)    (HI_FREE(pvMemAddr))

#ifdef HI_LOG_FATAL
#define HI_FATAL_TTX(fmt...)      HI_LOG_FATAL(fmt)
#else
#define HI_FATAL_TTX(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_TTX, fmt)
#endif

#ifdef HI_LOG_ERR
#define HI_ERR_TTX(fmt...)        HI_LOG_ERR(fmt)
#else
#define HI_ERR_TTX(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_TTX, fmt)
#endif

#ifdef HI_LOG_WARN
#define HI_WARN_TTX(fmt...)       HI_LOG_WARN(fmt)
#else
#define HI_WARN_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_TTX, fmt)
#endif

#ifdef HI_LOG_INFO
#define HI_INFO_TTX(fmt...)       HI_LOG_INFO(fmt)
#else
#define HI_INFO_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_TTX, fmt)
#endif

#else

#include "hi_debug.h"

#define HI_MEMTTX_MALLOC(u32Size)    (malloc(u32Size))
#define HI_MEMTTX_FREE(pvMemAddr)    (free(pvMemAddr))

#ifdef HI_FATAL_PRINT
#define HI_FATAL_TTX(fmt...)      HI_FATAL_PRINT(HI_ID_TTX, fmt)
#else
#define HI_FATAL_TTX(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_ERR_PRINT
#define HI_ERR_TTX(fmt...)        HI_ERR_PRINT(HI_ID_TTX, fmt)
#else
#define HI_ERR_TTX(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_WARN_PRINT
#define HI_WARN_TTX(fmt...)       HI_WARN_PRINT(HI_ID_TTX, fmt)
#else
#define HI_WARN_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_INFO_PRINT
#define HI_INFO_TTX(fmt...)       HI_INFO_PRINT(HI_ID_TTX, fmt)
#else
#define HI_INFO_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_DEBUG_ID_TTX, fmt)
#endif

#endif  //#if (UNF_VERSION_CODE >= UNF_VERSION(3, 5))

#else

#include "hi_debug.h"
#ifdef HI_FATAL_PRINT
#define HI_FATAL_TTX(fmt...)      HI_FATAL_PRINT(HI_ID_TTX, fmt)
#else
#define HI_FATAL_TTX(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_ERR_PRINT
#define HI_ERR_TTX(fmt...)        HI_ERR_PRINT(HI_ID_TTX, fmt)
#else
#define HI_ERR_TTX(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_WARN_PRINT
#define HI_WARN_TTX(fmt...)       HI_WARN_PRINT(HI_ID_TTX, fmt)
#else
#define HI_WARN_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_DEBUG_ID_TTX, fmt)
#endif

#ifdef HI_INFO_PRINT
#define HI_INFO_TTX(fmt...)       HI_INFO_PRINT(HI_ID_TTX, fmt)
#else
#define HI_INFO_TTX(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_DEBUG_ID_TTX, fmt)
#endif

#endif  //#ifndef __LITEOS__

#endif  //#ifndef __TELETEXT_DEBUG_H__