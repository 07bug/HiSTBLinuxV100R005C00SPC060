#ifndef __SUBTITLE_DEBUG_H__
#define __SUBTITLE_DEBUG_H__


#ifdef __LITEOS__

#include "hi_debug.h"

extern void *hi_malloc(HI_MOD_ID_E ModId, HI_U32 boundary, HI_U32 size, HI_BOOL nocache);
extern void  hi_free(HI_MOD_ID_E ModId, void *ptr, HI_BOOL nocache);
#define HI_MEMSUBT_MALLOC(u32Size)    (hi_malloc(HI_ID_SUBT, 0,(u32Size), HI_FALSE))
#define HI_MEMSUBT_FREE(pvMemAddr)    (hi_free(HI_ID_SUBT, (pvMemAddr), HI_FALSE))

#ifdef HI_FATAL_PRINT
#define HI_FATAL_SUBT(fmt...)      HI_FATAL_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_FATAL_SUBT(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_ERR_PRINT
#define HI_ERR_SUBT(fmt...)        HI_ERR_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_ERR_SUBT(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_WARN_PRINT
#define HI_WARN_SUBT(fmt...)       HI_WARN_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_WARN_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_INFO_PRINT
#define HI_INFO_SUBT(fmt...)       HI_INFO_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_INFO_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_DEBUG_ID_SUBT, fmt)
#endif

#else

#include "hi_unf_version.h"

#define HI_MEMSUBT_MALLOC(u32Size)    (malloc(u32Size))
#define HI_MEMSUBT_FREE(pvMemAddr)    (free(pvMemAddr))

//UNF version 3.5 use hi_log, instead of hi_debug
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 5))

#include "hi_log.h"

#define LOG_D_MODULE_ID HI_ID_SUBT

#ifdef HI_LOG_FATAL
#define HI_FATAL_SUBT(fmt...)      HI_LOG_FATAL(fmt)
#else
#define HI_FATAL_SUBT(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_ID_SUBT, fmt)
#endif

#ifdef HI_LOG_ERR
#define HI_ERR_SUBT(fmt...)        HI_LOG_ERR(fmt)
#else
#define HI_ERR_SUBT(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_SUBT, fmt)
#endif

#ifdef HI_LOG_WARN
#define HI_WARN_SUBT(fmt...)       HI_LOG_WARN(fmt)
#else
#define HI_WARN_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_ID_SUBT, fmt)
#endif

#ifdef HI_LOG_INFO
#define HI_INFO_SUBT(fmt...)       HI_LOG_INFO(fmt)
#else
#define HI_INFO_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_ID_SUBT, fmt)
#endif

#else

#include "hi_debug.h"

#ifdef HI_FATAL_PRINT
#define HI_FATAL_SUBT(fmt...)      HI_FATAL_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_FATAL_SUBT(fmt...)      HI_TRACE(HI_LOG_LEVEL_FATAL, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_ERR_PRINT
#define HI_ERR_SUBT(fmt...)        HI_ERR_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_ERR_SUBT(fmt...)        HI_TRACE(HI_LOG_LEVEL_ERROR, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_WARN_PRINT
#define HI_WARN_SUBT(fmt...)       HI_WARN_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_WARN_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_WARNING, HI_DEBUG_ID_SUBT, fmt)
#endif

#ifdef HI_INFO_PRINT
#define HI_INFO_SUBT(fmt...)       HI_INFO_PRINT(HI_ID_SUBT, fmt)
#else
#define HI_INFO_SUBT(fmt...)       HI_TRACE(HI_LOG_LEVEL_INFO, HI_DEBUG_ID_SUBT, fmt)
#endif

#endif  //(UNF_VERSION_CODE >= UNF_VERSION(3, 5))

#endif  //__LITEOS__


#endif  //__SUBTITLE_DEBUG_H__