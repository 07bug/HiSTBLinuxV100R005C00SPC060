/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : user_osal_lib.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __USER_OSAL_LIB_H__
#define __USER_OSAL_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_struct.h"
#include "hi_unf_cipher.h"
#include "drv_cipher_kapi.h"
#include "drv_cipher_ioctl.h"
#include "hi_error_mpi.h"
#include "mpi_cipher.h"

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/*! \****************************** API Declaration *****************************/
/*! \addtogroup    osal lib */
/** @{ */  /** <!--[osal]*/

#ifndef HI_PRINT
#define HI_PRINT                    printf
#endif

#define crypto_malloc(x)            malloc(x)
#define crypto_free(x)              free(x)

#define crypto_mutex                pthread_mutex_t
#define crypto_mutex_init(x)        (void)pthread_mutex_init(x, NULL)
#define crypto_mutex_lock(x)        (void)pthread_mutex_lock(x)
#define crypto_mutex_unlock(x)      (void)pthread_mutex_unlock(x)
#define crypto_mutex_destroy(x)     pthread_mutex_destroy(x)

#define crypto_open(a, b, c)        open(a, b, c)
#define crypto_close(x)             close(x)

extern HI_S32 g_CipherDevFd;
#define CRYPTO_IOCTL(cmd, argp)     ioctl(g_CipherDevFd, cmd, argp)

void crypto_memset(void *s, int sn, int val, int n);
void crypto_memcpy(void* s, int sn, const void* c, int n);

void print_string(const char*name, u8 *string, u32 size);

/**< allow modules to modify, default value is HI_ID_STB, the general module id*/
#define LOG_D_MODULE_ID             HI_ID_CIPHER
#define LOG_D_FUNCTRACE             (0)
#define LOG_D_UNFTRACE              (0)

/**< allow modules to define internel error code, from 0x1000*/
#define LOG_ERRCODE_DEF(errid)      (HI_U32)(((LOG_D_MODULE_ID) << 16)  | (errid))

/**< General Error Code, All modules can extend according to the rule */
#define HI_LOG_ERR_MEM              LOG_ERRCODE_DEF(0x0001)      /**< Memory Operation Error */
#define HI_LOG_ERR_SEM              LOG_ERRCODE_DEF(0x0002)      /**< Semaphore Operation Error */
#define HI_LOG_ERR_FILE             LOG_ERRCODE_DEF(0x0003)      /**< File Operation Error */
#define HI_LOG_ERR_LOCK             LOG_ERRCODE_DEF(0x0004)      /**< Lock Operation Error */
#define HI_LOG_ERR_PARAM            LOG_ERRCODE_DEF(0x0005)      /**< Invalid Parameter */
#define HI_LOG_ERR_TIMER            LOG_ERRCODE_DEF(0x0006)      /**< Timer error */
#define HI_LOG_ERR_THREAD           LOG_ERRCODE_DEF(0x0007)      /**< Thread Operation Error */
#define HI_LOG_ERR_TIMEOUT          LOG_ERRCODE_DEF(0x0008)      /**< Time Out Error */
#define HI_LOG_ERR_DEVICE           LOG_ERRCODE_DEF(0x0009)      /**< Device Operation Error */
#define HI_LOG_ERR_STATUS           LOG_ERRCODE_DEF(0x0010)      /**< Status Error */
#define HI_LOG_ERR_IOCTRL           LOG_ERRCODE_DEF(0x0011)      /**< IO Operation Error */
#define HI_LOG_ERR_INUSE            LOG_ERRCODE_DEF(0x0012)      /**< In use */
#define HI_LOG_ERR_EXIST            LOG_ERRCODE_DEF(0x0013)      /**< Have exist */
#define HI_LOG_ERR_NOEXIST          LOG_ERRCODE_DEF(0x0014)      /**< no exist */
#define HI_LOG_ERR_UNSUPPORTED      LOG_ERRCODE_DEF(0x0015)      /**< Unsupported */
#define HI_LOG_ERR_UNAVAILABLE      LOG_ERRCODE_DEF(0x0016)      /**< Unavailable */
#define HI_LOG_ERR_UNINITED         LOG_ERRCODE_DEF(0x0017)      /**< Uninited */
#define HI_LOG_ERR_DATABASE         LOG_ERRCODE_DEF(0x0018)      /**< Database Operation Error */
#define HI_LOG_ERR_OVERFLOW         LOG_ERRCODE_DEF(0x0019)      /**< Overflow */
#define HI_LOG_ERR_EXTERNAL         LOG_ERRCODE_DEF(0x0020)      /**< External Error */
#define HI_LOG_ERR_UNKNOWNED        LOG_ERRCODE_DEF(0x0021)      /**< Unknow Error */
#define HI_LOG_ERR_FLASH            LOG_ERRCODE_DEF(0x0022)      /**< Flash Operation Error*/
#define HI_LOG_ERR_ILLEGAL_IMAGE    LOG_ERRCODE_DEF(0x0023)      /**< Illegal Image */
#define HI_LOG_ERR_ILLEGAL_UUID     LOG_ERRCODE_DEF(0x0023)      /**< Illegal UUID */
#define HI_LOG_ERR_NOPERMISSION     LOG_ERRCODE_DEF(0x0023)      /**< No Permission */

#define HI_LOG_FATAL(fmt...)        HI_FATAL_PRINT(HI_ID_CIPHER, fmt)
#define HI_LOG_ERROR(fmt...)        HI_ERR_PRINT(HI_ID_CIPHER, fmt)
#define HI_LOG_WARN(fmt...)         HI_WARN_PRINT(HI_ID_CIPHER,  fmt)
#define HI_LOG_INFO(fmt...)         HI_INFO_PRINT(HI_ID_CIPHER,  fmt)
#define HI_LOG_DEBUG(fmt...)        HI_DBG_PRINT(HI_ID_CIPHER, fmt)

/**< Function trace log, strictly prohibited to expand */
#define HI_LOG_PrintFuncWar(Func, ErrCode)  HI_LOG_WARN("Call %s return [0x%08X]\n", #Func, ErrCode)
#define HI_LOG_PrintFuncErr(Func, ErrCode)  HI_LOG_ERROR("Call %s return [0x%08X]\n", #Func, ErrCode)
#define HI_LOG_PrintErrCode(ErrCode)        HI_LOG_ERROR("Error Code: [0x%08X]\n", ErrCode)

/**< Used for displaying more detailed error information */
#define HI_LOG_PrintS32(val)                HI_LOG_WARN("%s = %d\n",        #val, val)
#define HI_LOG_PrintU32(val)                HI_LOG_WARN("%s = %u\n",        #val, val)
#define HI_LOG_PrintS64(val)                HI_LOG_WARN("%s = %lld\n",      #val, val)
#define HI_LOG_PrintU64(val)                HI_LOG_WARN("%s = %llu\n",      #val, val)
#define HI_LOG_PrintH32(val)                HI_LOG_WARN("%s = 0x%08X\n",    #val, val)
#define HI_LOG_PrintH64(val)                HI_LOG_WARN("%s = 0x%016llX\n", #val, val)
#define HI_LOG_PrintStr(val)                HI_LOG_WARN("%s = %s\n",        #val, val)
#define HI_LOG_PrintVoid(val)               HI_LOG_WARN("%s = %p\n",        #val, val)
#define HI_LOG_PrintFloat(val)              HI_LOG_WARN("%s = %f\n",        #val, val)
#define HI_LOG_PrintInfo(val)               HI_LOG_WARN("<%s>\n", val)

/**< Only used for self debug, Can be expanded as needed */
#define HI_DBG_PrintS32(val)                HI_LOG_DEBUG("%s = %d\n",       #val, val)
#define HI_DBG_PrintU32(val)                HI_LOG_DEBUG("%s = %u\n",       #val, val)
#define HI_DBG_PrintS64(val)                HI_LOG_DEBUG("%s = %lld\n",     #val, val)
#define HI_DBG_PrintU64(val)                HI_LOG_DEBUG("%s = %llu\n",     #val, val)
#define HI_DBG_PrintH32(val)                HI_LOG_DEBUG("%s = 0x%08X\n",   #val, val)
#define HI_DBG_PrintH64(val)                HI_LOG_DEBUG("%s = 0x%016llX\n",#val, val)
#define HI_DBG_PrintStr(val)                HI_LOG_DEBUG("%s = %s\n",       #val, val)
#define HI_DBG_PrintVoid(val)               HI_LOG_DEBUG("%s = %p\n",       #val, val)
#define HI_DBG_PrintFloat(val)              HI_LOG_DEBUG("%s = %f\n",       #val, val)
#define HI_DBG_PrintInfo(val)               HI_LOG_DEBUG("<%s>\n", val)

#if (LOG_D_FUNCTRACE == 1) || (LOG_D_UNFTRACE == 1)
#define HI_UNF_FuncEnter()                  HI_LOG_DEBUG(" >>>>>>[Enter]\n")    /**< Only used for unf interface */
#define HI_UNF_FuncExit()                   HI_LOG_DEBUG(" <<<<<<[Exit]\n")     /**< Only used for unf interface */
#else
#define HI_UNF_FuncEnter()
#define HI_UNF_FuncExit()
#endif

#if LOG_D_FUNCTRACE
#define HI_LOG_FuncEnter()                  HI_LOG_DEBUG(" =====>[Enter]\n")    /**< Used for all interface except unf */
#define HI_LOG_FuncExit()                   HI_LOG_DEBUG(" =====>[Exit]\n")     /**< Used for all interface except unf */
#else
#define HI_LOG_FuncEnter()
#define HI_LOG_FuncExit()
#endif

#define HI_LOG_CHECK(fnFunc)                            \
do                                                      \
{                                                       \
    HI_S32 s32iErrCode = fnFunc;                        \
    if (HI_SUCCESS != s32iErrCode)                      \
    {                                                   \
        HI_LOG_PrintFuncErr(#fnFunc, s32iErrCode);      \
    }                                                   \
} while (0)


#define HI_LOG_CHECK_PARAM(bVal)                        \
do                                                      \
{                                                       \
    if (bVal)                                           \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_PARAM);          \
        return HI_LOG_ERR_PARAM;                        \
    }                                                   \
} while (0)


#define HI_LOG_CHECK_INITED(u32InitCount)               \
do                                                      \
{                                                       \
    if (0 == u32InitCount)                              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_UNINITED);       \
        return HI_LOG_ERR_UNINITED;                     \
    }                                                   \
} while (0)


#define HI_LOG_PrintBlock(data, length)

#endif  /* End of #ifndef __HI_DRV_CIPHER_H__*/
