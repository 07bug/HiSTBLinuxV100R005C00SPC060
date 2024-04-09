/******************************************************************************
          Copyright (C), 2017-2018, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : hi_log_aorender.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-29
 Description     : All functions and macros, not begin with HI_, prohibited to use
 Function List   :
 ******************************************************************************/

#ifndef __HI_LOG_AORENDER_H__
#define __HI_LOG_AORENDER_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_common.h"
#include "hi_module.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     HI_LOG */
/** @{ */  /** <!-- [HI_LOG] */

/****** Macro switch definition ***********/

/**< defined by menuconfig, Modules are not allowed to modify */
#if defined (HI_LOG_SUPPORT)
#define LOG_D_ENABLE                (1)
#define LOG_D_LEVEL                 (3)
#else
#define LOG_D_ENABLE                (0)
#define LOG_D_LEVEL                 (0)
#endif

/**< allow modules to modify, If the related module does not define it, no information output */
#ifndef LOG_D_FUNCTRACE
#define LOG_D_FUNCTRACE             (1)
#endif

#define HI_LOG_RUNNING_EVIRONMENT_SYSTEM

/****** Macro constants definition ********/
#if defined (HI_LOG_RUNNING_EVIRONMENT_MINIBOOT)
#define LOG_D_ENVIRONMENT           (0x01)
#elif defined (HI_LOG_RUNNING_EVIRONMENT_UBOOT)
#define LOG_D_ENVIRONMENT           (0x02)
#elif defined (HI_LOG_RUNNING_EVIRONMENT_SYSTEM)
#define LOG_D_ENVIRONMENT           (0x03)
#else
#define LOG_D_ENVIRONMENT           (0x04)
#endif

/**< allow modules to modify, default value is HI_ID_STB, the general module id*/
#ifndef LOG_D_MODULE_ID
#define LOG_D_MODULE_ID             HI_ID_AO
#endif

/****** Macro constants definition ********/

/**< allow modules to define internel error code*/
#define LOG_ERRCODE_DEF(errid)      (HI_S32)(((LOG_D_MODULE_ID) << 16) | ((LOG_D_ENVIRONMENT) << 8) | (errid))

/**< General Error Code, All modules can extend according to the rule*/
#define HI_LOG_ERR_MEM              LOG_ERRCODE_DEF(0x01)      /**< Memory Operation Error */
#define HI_LOG_ERR_SEM              LOG_ERRCODE_DEF(0x02)      /**< Semaphore Operation Error */
#define HI_LOG_ERR_FILE             LOG_ERRCODE_DEF(0x03)      /**< File Operation Error */
#define HI_LOG_ERR_LOCK             LOG_ERRCODE_DEF(0x04)      /**< Lock Operation Error */
#define HI_LOG_ERR_PARAM            LOG_ERRCODE_DEF(0x05)      /**< Invalid Parameter */
#define HI_LOG_ERR_TIMER            LOG_ERRCODE_DEF(0x06)      /**< Timer error */
#define HI_LOG_ERR_THREAD           LOG_ERRCODE_DEF(0x07)      /**< Thread Operation Error */
#define HI_LOG_ERR_TIMEOUT          LOG_ERRCODE_DEF(0x08)      /**< Time Out Error */
#define HI_LOG_ERR_DEVICE           LOG_ERRCODE_DEF(0x09)      /**< Device Operation Error */
#define HI_LOG_ERR_STATUS           LOG_ERRCODE_DEF(0x10)      /**< Status Error */
#define HI_LOG_ERR_IOCTRL           LOG_ERRCODE_DEF(0x11)      /**< IO Operation Error */
#define HI_LOG_ERR_INUSE            LOG_ERRCODE_DEF(0x12)      /**< In use */
#define HI_LOG_ERR_EXIST            LOG_ERRCODE_DEF(0x13)      /**< Have exist */
#define HI_LOG_ERR_NOEXIST          LOG_ERRCODE_DEF(0x14)      /**< no exist */
#define HI_LOG_ERR_UNSUPPORTED      LOG_ERRCODE_DEF(0x15)      /**< Unsupported */
#define HI_LOG_ERR_UNAVAILABLE      LOG_ERRCODE_DEF(0x16)      /**< Unavailable */
#define HI_LOG_ERR_UNINITED         LOG_ERRCODE_DEF(0x17)      /**< Uninited */
#define HI_LOG_ERR_DATABASE         LOG_ERRCODE_DEF(0x18)      /**< Database Operation Error */
#define HI_LOG_ERR_OVERFLOW         LOG_ERRCODE_DEF(0x19)      /**< Overflow */
#define HI_LOG_ERR_EXTERNAL         LOG_ERRCODE_DEF(0x20)      /**< External Error */
#define HI_LOG_ERR_UNKNOWNED        LOG_ERRCODE_DEF(0x21)      /**< Unknow Error */
#define HI_LOG_ERR_FLASH            LOG_ERRCODE_DEF(0x22)      /**< Flash Operation Error*/
#define HI_LOG_ERR_ILLEGAL_IMAGE    LOG_ERRCODE_DEF(0x23)      /**< Illegal Image */

/****** Macro Functions definition ********/

#if LOG_D_ENABLE

#if (LOG_D_ENVIRONMENT == 0x03)

#define HI_LOG_FATAL(fmt...)        HI_FATAL_PRINT(LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)          HI_ERR_PRINT(LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)         HI_WARN_PRINT(LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)         HI_INFO_PRINT(LOG_D_MODULE_ID, fmt)
#define HI_LOG_DBG(fmt...)          HI_DBG_PRINT(LOG_D_MODULE_ID, fmt)

#else

#define LOG_TRACE(level, fmt...)    printf("[%04X][%s]:[%s][%u]", LOG_D_MODULE_ID, level, __FUNCTION__, __LINE__);printf(fmt);

#if (LOG_D_LEVEL == 0)
#define HI_LOG_FATAL(fmt...)        LOG_TRACE("FATAL", fmt)
#define HI_LOG_ERR(fmt...)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#elif (LOG_D_LEVEL == 1)
#define HI_LOG_FATAL(fmt...)        LOG_TRACE("FATAL", fmt)
#define HI_LOG_ERR(fmt...)          LOG_TRACE("ERROR", fmt)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#elif (LOG_D_LEVEL == 2)
#define HI_LOG_FATAL(fmt...)        LOG_TRACE("FATAL", fmt)
#define HI_LOG_ERR(fmt...)          LOG_TRACE("ERROR", fmt)
#define HI_LOG_WARN(fmt...)         LOG_TRACE("WARN", fmt)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#elif (LOG_D_LEVEL == 3)
#define HI_LOG_FATAL(fmt...)        LOG_TRACE("FATAL", fmt)
#define HI_LOG_ERR(fmt...)          LOG_TRACE("ERROR", fmt)
#define HI_LOG_WARN(fmt...)         LOG_TRACE("WARN",  fmt)
#define HI_LOG_INFO(fmt...)         LOG_TRACE("INFO",  fmt)
#define HI_LOG_DBG(fmt...)
#else
#define HI_LOG_FATAL(fmt...)        LOG_TRACE("FATAL", fmt)
#define HI_LOG_ERR(fmt...)          LOG_TRACE("ERROR", fmt)
#define HI_LOG_WARN(fmt...)         LOG_TRACE("WARN",  fmt)
#define HI_LOG_INFO(fmt...)         LOG_TRACE("INFO",  fmt)
#define HI_LOG_DBG(fmt...)          LOG_TRACE("DEBUG", fmt)
#endif
#endif

#define HI_LOG_PrintBlock(pu8Datablock, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR aciOutStr[64] = {0};  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Datablock);  \
    HI_LOG_DBG(" %s\n", #pu8Datablock);  \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        if((u32ii % 16 == 0)  \
            && (u32ii != 0))  \
        {  \
            HI_LOG_DBG("%s\n", aciOutStr);  \
            memset(aciOutStr, 0x00, sizeof(aciOutStr));\
        }  \
        snprintf(&aciOutStr[(u32ii % 16) * 3], 4, " %02X", pciBuffer[u32ii]);  \
    }  \
    if((u32ii % 16 != 0)  \
        && (u32ii != 0))  \
    { \
        HI_LOG_DBG("%s\n", aciOutStr);  \
        memset(aciOutStr, 0x00, sizeof(aciOutStr));\
    }\
}

#else

#define HI_LOG_DBG(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_ERR(fmt...)
#define HI_LOG_FATAL(fmt...)
#define HI_LOG_PrintBlock(pcNotice, pu8Datablock, u32Length)

#endif

/** Function trace log, strictly prohibited to expand */
#define HI_LOG_PrintFuncErr(Func, ErrCode)  HI_LOG_ERR("Call [%s] return [0x%08X]\n", #Func, ErrCode);
#define HI_LOG_PrintErrCode(ErrCode)        HI_LOG_ERR("Error Code: [0x%08X]\n", ErrCode);
#define HI_LOG_PrintFuncWarn(Func, ErrCode) HI_LOG_WARN("Call [%s] return [0x%08X]\n", #Func, ErrCode);
#define HI_LOG_PrintWarnCode(ErrCode)       HI_LOG_WARN("Error Code: [0x%08X]\n", ErrCode);

#define HI_LOG_FuncEnter()                  HI_LOG_WARN(" =====>[Enter]\n")
#define HI_LOG_FuncExit()                   HI_LOG_WARN(" =====>[Exit]\n")


/** Used for displaying more detailed error information */
#define HI_ERR_PrintS32(val)                HI_LOG_ERR("%s = %d\n",         #val, val)
#define HI_ERR_PrintU32(val)                HI_LOG_ERR("%s = %u\n",         #val, val)
#define HI_ERR_PrintS64(val)                HI_LOG_ERR("%s = %lld\n",       #val, val)
#define HI_ERR_PrintU64(val)                HI_LOG_ERR("%s = %llu\n",       #val, val)
#define HI_ERR_PrintH32(val)                HI_LOG_ERR("%s = 0x%08X\n",     #val, val)
#define HI_ERR_PrintH64(val)                HI_LOG_ERR("%s = 0x%016llX\n",  #val, val)
#define HI_ERR_PrintStr(val)                HI_LOG_ERR("%s = %s\n",         #val, val)
#define HI_ERR_PrintVoid(val)               HI_LOG_ERR("%s = %p\n",         #val, val)
#define HI_ERR_PrintFloat(val)              HI_LOG_ERR("%s = %f\n",         #val, val)
#define HI_ERR_PrintInfo(val)               HI_LOG_ERR("<%s>\n", val)

/** Used for displaying more detailed warning information */
#define HI_WARN_PrintS32(val)               HI_LOG_WARN("%s = %d\n",        #val, val)
#define HI_WARN_PrintU32(val)               HI_LOG_WARN("%s = %u\n",        #val, val)
#define HI_WARN_PrintS64(val)               HI_LOG_WARN("%s = %lld\n",      #val, val)
#define HI_WARN_PrintU64(val)               HI_LOG_WARN("%s = %llu\n",      #val, val)
#define HI_WARN_PrintH32(val)               HI_LOG_WARN("%s = 0x%08X\n",    #val, val)
#define HI_WARN_PrintH64(val)               HI_LOG_WARN("%s = 0x%016llX\n", #val, val)
#define HI_WARN_PrintStr(val)               HI_LOG_WARN("%s = %s\n",        #val, val)
#define HI_WARN_PrintVoid(val)              HI_LOG_WARN("%s = %p\n",        #val, val)
#define HI_WARN_PrintFloat(val)             HI_LOG_WARN("%s = %f\n",        #val, val)
#define HI_WARN_PrintInfo(val)              HI_LOG_WARN("<%s>\n", val)

/** Used for displaying more detailed info information */
#define HI_INFO_PrintS32(val)               HI_LOG_INFO("%s = %d\n",        #val, val)
#define HI_INFO_PrintU32(val)               HI_LOG_INFO("%s = %u\n",        #val, val)
#define HI_INFO_PrintS64(val)               HI_LOG_INFO("%s = %lld\n",      #val, val)
#define HI_INFO_PrintU64(val)               HI_LOG_INFO("%s = %llu\n",      #val, val)
#define HI_INFO_PrintH32(val)               HI_LOG_INFO("%s = 0x%08X\n",    #val, val)
#define HI_INFO_PrintH64(val)               HI_LOG_INFO("%s = 0x%016llX\n", #val, val)
#define HI_INFO_PrintStr(val)               HI_LOG_INFO("%s = %s\n",        #val, val)
#define HI_INFO_PrintVoid(val)              HI_LOG_INFO("%s = %p\n",        #val, val)
#define HI_INFO_PrintFloat(val)             HI_LOG_INFO("%s = %f\n",        #val, val)
#define HI_INFO_PrintInfo(val)              HI_LOG_INFO("<%s>\n", val)

/** Only used for self debug, Can be expanded as needed */
#define HI_DBG_PrintS32(val)                HI_LOG_DBG("%s = %d\n",         #val, val)
#define HI_DBG_PrintU32(val)                HI_LOG_DBG("%s = %u\n",         #val, val)
#define HI_DBG_PrintS64(val)                HI_LOG_DBG("%s = %lld\n",       #val, val)
#define HI_DBG_PrintU64(val)                HI_LOG_DBG("%s = %llu\n",       #val, val)
#define HI_DBG_PrintH32(val)                HI_LOG_DBG("%s = 0x%08X\n",     #val, val)
#define HI_DBG_PrintH64(val)                HI_LOG_DBG("%s = 0x%016llX\n"  ,#val, val)
#define HI_DBG_PrintStr(val)                HI_LOG_DBG("%s = %s\n",         #val, val)
#define HI_DBG_PrintVoid(val)               HI_LOG_DBG("%s = %p\n",         #val, val)
#define HI_DBG_PrintFloat(val)              HI_LOG_DBG("%s = %f\n",         #val, val)
#define HI_DBG_PrintInfo(val)               HI_LOG_DBG("<%s>\n", val)


#define HI_INFO_FuncEnter()                 HI_LOG_INFO(" =====>[Enter]\n")
#define HI_INFO_FuncExit()                  HI_LOG_INFO(" =====>[Exit]\n")

#if LOG_D_FUNCTRACE
#define HI_DBG_FuncEnter()                  HI_LOG_DBG(" =====>[Enter]\n")
#define HI_DBG_FuncExit()                   HI_LOG_DBG(" =====>[Exit]\n")
#else
#define HI_DBG_FuncEnter()
#define HI_DBG_FuncExit()
#endif

#define HI_LOG_CHECK(fnFunc)                            \
{                                                       \
    HI_S32 s32iErrCode = fnFunc;                        \
    if (HI_SUCCESS != s32iErrCode)                      \
    {                                                   \
        HI_LOG_PrintFuncErr(#fnFunc, s32iErrCode);      \
    }                                                   \
}


#define HI_LOG_CHECK_PARAM(bVal)                        \
{                                                       \
    if (bVal)                                           \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_PARAM);          \
        return HI_LOG_ERR_PARAM;                        \
    }                                                   \
}


#define HI_LOG_CHECK_INITED(u32InitCount)               \
{                                                       \
    if (0 == u32InitCount)                              \
    {                                                   \
        HI_LOG_PrintErrCode(HI_LOG_ERR_UNINITED);       \
        return HI_LOG_ERR_UNINITED;                     \
    }                                                   \
}



/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     HI_LOG */
/** @{ */  /** <!-- [HI_LOG] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     HI_LOG */
/** @{ */  /** <!-- [HI_LOG] */


/** @}*/  /** <!-- ==== API Declaration End ====*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif  /* __HI_LOG_AORENDER_H__ */

