/******************************************************************************
Copyright (C), 2017-2018, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_aiao_log.h
Version       : Initial Draft
Created       : 2017/10/11
Description   : aiao log macro definition
Function List :
******************************************************************************/
#ifndef __HI_AIAO_LOG_H__
#define __HI_AIAO_LOG_H__

//#define __HI_AIAO_DEBUG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_module.h"

#ifdef HI_LOG_SUPPORT
#define HI_AIAO_DEBUG

#ifdef __KERNEL__
    #define HI_PRINT printk
    #define HI_PANIC printk
#else
    #define HI_PRINT printf
    #define HI_PANIC printf
#endif
#else
#undef HI_AIAO_DEBUG

#define HI_PANIC(fmt...)    \
    do { \
    } while (0)

#define HI_PRINT(fmt...)    \
    do { \
    } while (0)
#endif

/* key info print MACO default off */
//#define HI_KEY_PRINT_OUT

/*************************** Structure Definition ****************************/
/** \addtogroup     HI_DEBUG */
/** @{ */  /** <!-- [HI_DEBUG] */


/**Default level of the output debugging information*/
/**CNcomment: Ĭ�ϵĵ�����Ϣ�������*/
#define HI_AIAO_LOG_LEVEL_DEFAULT HI_AIAO_LOG_LEVEL_NOTICE

/**Level of the output debugging information*/
/**CNcomment: ������Ϣ�������*/
typedef enum hiAIAO_LOG_LEVEL_E
{
    HI_AIAO_LOG_LEVEL_FATAL   = 0,     /**<Fatal error. It indicates that a critical problem occurs in the system. Therefore, you must pay attention to it.*/
                                  /**<CNcomment: ��������, ���������Ҫ�ر��ע��һ����ִ���������ϵͳ�������ش����� */
    HI_AIAO_LOG_LEVEL_ERROR   = 1,     /**<Major error. It indicates that a major problem occurs in the system and the system cannot run.*/
                                  /**<CNcomment: һ�����, һ����ִ���������ϵͳ�����˱Ƚϴ�����⣬�������������� */
    HI_AIAO_LOG_LEVEL_WARNING = 2,     /**<Warning. It indicates that a minor problem occurs in the system, but the system still can run properly.*/
                                  /**<CNcomment: �澯��Ϣ, һ����ִ�����Ϣ����ϵͳ���ܳ������⣬���ǻ��ܼ������� */
    HI_AIAO_LOG_LEVEL_NOTICE  = 3,     /**<Notice. It indicates that a normal but significant condition in the system, but the system still can run properly.*/
                                  /**<CNcomment: ��������Ҫ����Ϣ, һ�������ϵͳ�Ĺؼ�·�������� */
    HI_AIAO_LOG_LEVEL_INFO    = 4,     /**<Message. It is used to prompt users. Users can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: ��ʾ��Ϣ, һ����Ϊ�����û���������ڶ�λ�����ʱ����Դ򿪣�һ������½���ر� */
    HI_AIAO_LOG_LEVEL_DBG     = 5,     /**<Debug. It is used to prompt developers. Developers can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: ��ʾ��Ϣ, һ����Ϊ������Ա����������趨�Ĵ�ӡ����һ������½���ر� */
    HI_AIAO_LOG_LEVEL_VERBOSE = 6,     /**<Verbose. It is used to prompt developers. Developers can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: ��ʾ��Ϣ, һ����Ϊ������Ա����������趨�Ĵ�ӡ����һ������½���ر� */

    HI_AIAO_LOG_LEVEL_BUTT
} AIAO_LOG_LEVEL_E;

/** @} */

/**Just only for fatal level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_FATAL    (0)
/**Just only for error level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_ERROR    (1)
/**Just only for warning level print. */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_WARN     (2)
/**Just only for notice level print.  */   /**CNcomment: Ϊ�˴�ӡע����Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_NOTICE   (3)
/**Just only for info level print.    */   /**CNcomment: Ϊ�˴�ӡ��Ϣ������ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_INFO     (4)
/**Just only for debug level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_DBG      (5)
/**Just only for verbose level print. */   /**CNcomment: Ϊ�˴�ӡ�߳��ĵ�����Ϣ���ƶ��ĺ��ӡ���� */
#define HI_AIAO_TRACE_LEVEL_VERBOSE  (6)


/**Just only debug output,MUST BE NOT calling it. */
/**CNcomment: ���������Ϣ�ӿڣ����Ƽ�ֱ�ӵ��ô˽ӿ� */
extern HI_VOID HI_LogOut(HI_U32 u32Level, HI_MOD_ID_E enModId,
            HI_U8 *pFuncName, HI_U32 u32LineNum, const char *format, ...);
extern  HI_U32 LOGGetTimeMs(HI_VOID);

#ifdef HI_AIAO_DEBUG

#ifndef AIAO_LOG_D_MODULE_ID
#define AIAO_LOG_D_MODULE_ID             HI_ID_AO
#endif


#ifndef HI_AIAO_LOG_LEVEL
#define HI_AIAO_LOG_LEVEL          (HI_AIAO_TRACE_LEVEL_DBG)
#endif


#define HI_AIAO_TRACE(level, module_id, fmt...)                      \
    do{                                                         \
        HI_LogOut(level, module_id, (HI_U8*)__FUNCTION__,__LINE__,fmt);  \
    }while(0)


/**Supported for debug output to serial/network/u-disk. */
/**CNcomment: ����ģ����Ҫ�������º�������������Ϣ������������ڡ����ڡ�U�̴洢�� */
/**Just only reserve the fatal level output. */
/**CNcomment: �������������ĵ�����Ϣ */
#if (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_FATAL)
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_NOTICE(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)
/**Just only reserve the fatal/error level output. */
/**CNcomment: �������������ĺʹ��󼶱�ĵ�����Ϣ */
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_ERROR)
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_NOTICE(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)
/**Just only reserve the fatal/error/warning level output. */
/**CNcomment: �������������ġ�����ġ����漶��ĵ�����Ϣ */
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_WARN)
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_WARN,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_NOTICE(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)
/**Just only reserve the fatal/error/warning/note level output. */
/**CNcomment: �������������ġ�����ġ������ע�⼶��ĵ�����Ϣ */
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_NOTICE)
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_WARN,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_NOTICE(fmt...)  HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)
/**Just only reserve the fatal/error/warning/info level output. */
/**CNcomment: �������������ġ�����ġ��������Ϣ����ĵ�����Ϣ */
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_INFO)
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_WARN,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_NOTICE(fmt...)  HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_DBG)
/**Reserve all the levels output. */
/**CNcomment: �������м��������Ϣ */
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_WARN,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_NOTICE(fmt...)  HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_DBG(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_VERBOSE(fmt...)
#elif (HI_AIAO_LOG_LEVEL == HI_AIAO_TRACE_LEVEL_VERBOSE)
/**Reserve all the levels output. */
/**CNcomment: �������м��������Ϣ */
#define HI_LOG_FATAL(fmt...)   HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_FATAL,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_ERR(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_ERROR,    AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_WARN(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_WARN,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_NOTICE(fmt...)  HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_INFO(fmt...)    HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_DBG(fmt...)     HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)
#define HI_LOG_VERBOSE(fmt...) HI_AIAO_TRACE(HI_AIAO_TRACE_LEVEL_INFO,     AIAO_LOG_D_MODULE_ID, fmt)

#endif


#else
#define HI_LOG_FATAL(fmt...)
#define HI_LOG_ERR(fmt...)
#define HI_LOG_WARN(fmt...)
#define HI_LOG_NOTICE(fmt...)
#define HI_LOG_INFO(fmt...)
#define HI_LOG_DBG(fmt...)
#define HI_LOG_VERBOSE(fmt...)

#endif /* endif HI_DEBUG */

/** @} */  /** <!-- ==== Structure Definition End ==== */

#define HI_NOTICE_FuncEnter()              HI_LOG_NOTICE(" ===>[Enter]\n")
#define HI_NOTICE_FuncExit()               HI_LOG_NOTICE(" <===[Exit]\n")
#define HI_NOTICE_FuncTrace()              HI_LOG_NOTICE(" =TRACE=\n")

#define HI_INFO_FuncEnter()                HI_LOG_INFO(" ===>[Enter]\n")
#define HI_INFO_FuncExit()                 HI_LOG_INFO(" <===[Exit]\n")
#define HI_INFO_FuncTrace()                HI_LOG_INFO(" =TRACE=\n")

#define HI_DBG_FuncEnter()                 HI_LOG_DBG(" ===>[Enter]\n")
#define HI_DBG_FuncExit()                  HI_LOG_DBG(" <===[Exit]\n")
#define HI_DBG_FuncTrace()                 HI_LOG_DBG(" =TRACE=\n")

/**Function trace log for user input low frequency counts */
/**CNcomment: �������뽵Ƶ��ӡ�Ĵ��� */

#define HI_DBG_FuncTraceLowFreqCnt(freq)                \
do{\
    static unsigned int freqtimes=0;\
    if(0==(freqtimes%(unsigned int )freq)){\
        HI_LOG_DBG(" =TRACE Freq=%d,freqtimes=%d=\n",freq,freqtimes);\
     }\
    freqtimes++;\
}while(0)

/**Function trace log for user add extra print log as need */
/**CNcomment: �û������������Ӷ���Ĵ�ӡ */
/**Need use HI_FuncTraceLowFreqCntEnd at the same time, to repesent the addtional prints is the end*/
/**CNcomment: ��Ҫͬʱʹ��HI_FuncTraceLowFreqCntEnd�������������ӵĴ�ӡ��ֹ*/

#define HI_FuncTraceLowFreqCntBegin(freq)\
do{\
    static unsigned int freqtimes=0;\
    if(0==(freqtimes%(unsigned int )freq)){\
        do{}while(0)

#define HI_FuncTraceLowFreqCntEnd() \
    }\
    freqtimes++;\
}while(0)

/**Function trace log for user input low frequency time */
/**CNcomment: �������뽵Ƶ��ӡ��ʱ�� */

#define HI_DBG_FuncTraceLowFreqTime(time)                \
do{\
    static HI_U32 u32LastTime= 0; \
    HI_U32        u32CurrTime;    \
    u32CurrTime = LOGGetTimeMs(); \
    if(time <= (u32CurrTime-u32LastTime)){\
        HI_LOG_DBG(" =TRACE Freq=%d,freqtimes=%d=\n",time,u32CurrTime);\
        u32LastTime = u32CurrTime;\
    }\
}while(0)

/**Function trace log for user add extra print log as need */
/**CNcomment: �û������������Ӷ���Ĵ�ӡ */
/**Need use HI_FuncTraceLowFreqTimeEnd at the same time, to repesent the addtional prints is the end*/
/**CNcomment: ��Ҫͬʱʹ��HI_FuncTraceLowFreqTimeEnd�������������ӵĴ�ӡ��ֹ*/

#define HI_FuncTraceLowFreqTimeBegin(time)                \
    do{\
        static HI_U32 u32LastTime= 0; \
        HI_U32        u32CurrTime;    \
        u32CurrTime = LOGGetTimeMs(); \
        if(time <= (u32CurrTime-u32LastTime)){\
            do{}while(0)

#define HI_FuncTraceLowFreqTimeEnd()\
            u32LastTime = u32CurrTime;\
        }\
    }while(0)

/** Function trace log, strictly prohibited to expand */
#define HI_ERR_PrintErrCode(ErrCode)                HI_LOG_ERR("Error Code: [0x%08X]\n", ErrCode)

/** Function trace log, print the called function name when function is error*/
#define HI_ERR_PrintCallFunErr(Func, ErrCode)       HI_LOG_ERR( "Call %s Failed, Error Code: [0x%08X]\n", #Func, ErrCode)

/** Function trace log, print the pointer name when pointer is null*/
#define HI_ERR_PrintNullPointer(val)       HI_LOG_ERR( "%s = %p\n, Null Pointer!\n", #val, val)

/** Used for displaying more detailed error information */
#define HI_ERR_PrintS32(val)                HI_LOG_ERR("%s = %d\n",        #val, val)
#define HI_ERR_PrintU32(val)                HI_LOG_ERR("%s = %u\n",        #val, val)
#define HI_ERR_PrintS64(val)                HI_LOG_ERR("%s = %lld\n",      #val, val)
#define HI_ERR_PrintU64(val)                HI_LOG_ERR("%s = %llu\n",      #val, val)
#define HI_ERR_PrintH32(val)                HI_LOG_ERR("%s = 0x%08X\n",    #val, val)
#define HI_ERR_PrintH64(val)                HI_LOG_ERR("%s = 0x%016llX\n", #val, val)
#define HI_ERR_PrintStr(val)                HI_LOG_ERR("%s = %s\n",        #val, val)
#define HI_ERR_PrintVoid(val)               HI_LOG_ERR("%s = %p\n",        #val, val)
#define HI_ERR_PrintFloat(val)              HI_LOG_ERR("%s = %f\n",        #val, val)
#define HI_ERR_PrintInfo(val)               HI_LOG_ERR("<%s>\n", val)
#define HI_ERR_PrintBool(val)               HI_LOG_ERR("%s = %s\n",        #val, val ? "True":"False")

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
#define HI_WARN_PrintBool(val)              HI_LOG_WARN("%s = %s\n",        #val, val ? "True":"False")

/** Only used for key info, Can be expanded as needed */
#define HI_INFO_PrintS32(val)               HI_LOG_INFO("%s = %d\n",       #val, val)
#define HI_INFO_PrintU32(val)               HI_LOG_INFO("%s = %u\n",       #val, val)
#define HI_INFO_PrintS64(val)               HI_LOG_INFO("%s = %lld\n",     #val, val)
#define HI_INFO_PrintU64(val)               HI_LOG_INFO("%s = %llu\n",     #val, val)
#define HI_INFO_PrintH32(val)               HI_LOG_INFO("%s = 0x%08X\n",   #val, val)
#define HI_INFO_PrintH64(val)               HI_LOG_INFO("%s = 0x%016llX\n",#val, val)
#define HI_INFO_PrintStr(val)               HI_LOG_INFO("%s = %s\n",       #val, val)
#define HI_INFO_PrintVoid(val)              HI_LOG_INFO("%s = %p\n",       #val, val)
#define HI_INFO_PrintFloat(val)             HI_LOG_INFO("%s = %f\n",       #val, val)
#define HI_INFO_PrintInfo(val)              HI_LOG_INFO("<%s>\n", val)
#define HI_INFO_PrintBool(val)              HI_LOG_INFO("%s = %s\n",       #val, val ? "True":"False")

/** Only used for self debug, Can be expanded as needed */
#define HI_DBG_PrintS32(val)                HI_LOG_DBG("%s = %d\n",       #val, val)
#define HI_DBG_PrintU32(val)                HI_LOG_DBG("%s = %u\n",       #val, val)
#define HI_DBG_PrintS64(val)                HI_LOG_DBG("%s = %lld\n",     #val, val)
#define HI_DBG_PrintU64(val)                HI_LOG_DBG("%s = %llu\n",     #val, val)
#define HI_DBG_PrintH32(val)                HI_LOG_DBG("%s = 0x%08X\n",   #val, val)
#define HI_DBG_PrintH64(val)                HI_LOG_DBG("%s = 0x%016llX\n",#val, val)
#define HI_DBG_PrintStr(val)                HI_LOG_DBG("%s = %s\n",       #val, val)
#define HI_DBG_PrintVoid(val)               HI_LOG_DBG("%s = %p\n",       #val, val)
#define HI_DBG_PrintFloat(val)              HI_LOG_DBG("%s = %f\n",       #val, val)
#define HI_DBG_PrintInfo(val)               HI_LOG_DBG("<%s>\n", val)
#define HI_DBG_PrintBool(val)               HI_LOG_DBG("%s = %s\n",       #val, val ? "True":"False")

/** Only used for self debug, Can be expanded as needed */
#define HI_VERBOSE_PrintS32(val)            HI_LOG_VERBOSE("%s = %d\n",       #val, val)
#define HI_VERBOSE_PrintU32(val)            HI_LOG_VERBOSE("%s = %u\n",       #val, val)
#define HI_VERBOSE_PrintS64(val)            HI_LOG_VERBOSE("%s = %lld\n",     #val, val)
#define HI_VERBOSE_PrintU64(val)            HI_LOG_VERBOSE("%s = %llu\n",     #val, val)
#define HI_VERBOSE_PrintH32(val)            HI_LOG_VERBOSE("%s = 0x%08X\n",   #val, val)
#define HI_VERBOSE_PrintH64(val)            HI_LOG_VERBOSE("%s = 0x%016llX\n",#val, val)
#define HI_VERBOSE_PrintStr(val)            HI_LOG_VERBOSE("%s = %s\n",       #val, val)
#define HI_VERBOSE_PrintVoid(val)           HI_LOG_VERBOSE("%s = %p\n",       #val, val)
#define HI_VERBOSE_PrintFloat(val)          HI_LOG_VERBOSE("%s = %f\n",       #val, val)
#define HI_VERBOSE_PrintInfo(val)           HI_LOG_VERBOSE("<%s>\n", val)
#define HI_VERBOSE_PrintBool(val)           HI_LOG_VERBOSE("%s = %s\n",       #val, val ? "True":"False")


#define HI_LOG_PrintBlock(pu8Datablock, u32Length)  \
{  \
    HI_U32 u32ii = 0;  \
    HI_CHAR aciOutStr[64] = {0};  \
    HI_CHAR* pciBuffer = (HI_CHAR*)(pu8Datablock);  \
    HI_PRINT(" %s\n", #pu8Datablock);  \
    for (u32ii = 0; u32ii < (u32Length); u32ii++)  \
    {  \
        if((u32ii % 16 == 0)  \
            && (u32ii != 0))  \
        {  \
            HI_PRINT("%s\n", aciOutStr);  \
            memset(aciOutStr, 0x00, sizeof(aciOutStr));\
        }  \
        snprintf(&aciOutStr[(u32ii % 16) * 3], 4, " %02X", pciBuffer[u32ii]);  \
    }  \
    if((u32ii % 16 != 0)  \
        && (u32ii != 0))  \
    { \
        HI_PRINT("%s\n", aciOutStr);  \
        memset(aciOutStr, 0x00, sizeof(aciOutStr));\
    }\
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_LOG_H__ */

