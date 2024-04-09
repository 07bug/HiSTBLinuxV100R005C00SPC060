/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : common_log.h
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2016年2月27日
  最近修改   :
  功能描述   : 终端软件方案平台测试部定义的公共头文件
  函数列表   : 无
  修改历史   : 无
  1.日    期   : 2016年2月27日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "hi_type.h"
//#include <utils/Logger.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define HITEST_ADD_TESTCASE(x) { x, #x }
#define HITEST_STRESS_TIMES   (100)

/** 检验: api == HI_SUCCESS */
#define HITEST_CHECK_SUCCESS(api)\
    do{\
        HI_S32 s32ApiRet = (api);\
        if (s32ApiRet != HI_SUCCESS)\
        {\
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__,s32ApiRet, __LINE__);\
            printf("<%s,%d>:%s failed(is NOT expectant HI_SUCCESS)\n", __FUNCTION__, __LINE__, (# api)); \
        } \
    }while (0)

/** 检验: api != HI_SUCCESS */
#define HITEST_CHECK_FAIL(api)\
    do{\
        HI_S32 s32ApiRet = (api);\
        if (s32ApiRet == HI_SUCCESS)\
        {\
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__,s32ApiRet, __LINE__);\
            printf("<%s,%d>:%s failed(is NOT expectant HI_FAIL)\n", __FUNCTION__, __LINE__, (# api)); \
        } \
    }while (0)

/** 检验: api == HI_NULL */
#define HITEST_CHECK_NULL(api)\
    do{\
        if (HI_NULL == (api))\
        {\
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__);\
            printf("<%s,%d>:%s failed! Ret = HI_NULL\n", __FUNCTION__, __LINE__, (# api)); \
        } \
    }while (0)

/** 检验: api结果与rtn相同 */
#define HITEST_ASSERT_EQUAL(api, rtn) \
    do {\
        HI_S32 s32ApiRet = (api); \
        if (((HI_S32)rtn) != s32ApiRet) \
        { \
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__, s32ApiRet, __LINE__); \
            printf("<%s,%d>:%s failed(is NOT expectant(%s))! Ret=0x%x\n", __FUNCTION__, __LINE__, (# api), (# rtn), s32ApiRet); \
        } \
    } while (0)

/** 检验: api结果与rtn相同 ,HI_U32类型*/
#define HITEST_ASSERT_U32EQUAL(api, rtn) \
    do {\
        HI_U32 s32ApiRet = (api); \
        if (((HI_U32)rtn) != s32ApiRet) \
        { \
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__, s32ApiRet, __LINE__); \
            printf("<%s,%d>:%s failed(is NOT expectant(%s))! Ret=0x%x\n", __FUNCTION__, __LINE__, (# api), (# rtn), s32ApiRet); \
        } \
    } while (0)

/** 检验: api结果与rtn不同 */
#define HITEST_ASSERT_NOT_EQUAL(api, expected) \
    do\
    {\
        HI_S32 s32ApiRet =(api);  \
        if((s32ApiRet) == ((HI_S32)expected))\
        {\
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__, s32ApiRet, __LINE__);\
            printf("actualValue is not expectedValue,actualValue = %x,expectedValue=%x\n",s32ApiRet, expected);\
        }\
    }while(0)

/** 检验:不满足条件打印错误 */
#define HITEST_ASSERT_CONDITION_ERR(ret) \
    do                                                  \
    {                                                   \
        if (!(ret))                                     \
        {                                               \
            HITEST_FailPrint((HI_CHAR *)__FUNCTION__,HI_FAILURE, __LINE__); \
        }                                               \
    } while (0)

/** 打印Error级别信息 */
#define HITEST_LOGE(pszFormat...) \
    do\
    {\
        if((HITEST_LOG_LEVEL_ERROR <= HITEST_GetLogLevel()) && (HITEST_LOG_LEVEL_CLOSE > HITEST_GetLogLevel()))\
        {\
            printf("[file=%s],[func=%s],[line=%d]",__FILE__,__FUNCTION__,__LINE__); \
            printf(pszFormat); \
            printf("\n");\
        }\
    }while(0)

/** 打印Warning以上级别信息 */
#define HITEST_LOGW(pszFormat...) \
    do\
    {\
        if((HITEST_LOG_LEVEL_WARNING <= HITEST_GetLogLevel()) && (HITEST_LOG_LEVEL_CLOSE > HITEST_GetLogLevel()))\
        {\
            printf("[file=%s],[func=%s],[line=%d]",__FILE__,__FUNCTION__,__LINE__); \
            printf(pszFormat); \
            printf("\n");\
        }\
    }while(0)

/** 打印Info以上级别信息 */
#define HITEST_LOGI(pszFormat...) \
    do\
    {\
        if((HITEST_LOG_LEVEL_INFO <= HITEST_GetLogLevel()) && (HITEST_LOG_LEVEL_CLOSE > HITEST_GetLogLevel()))\
        {\
            printf("[file=%s],[func=%s],[line=%d]",__FILE__,__FUNCTION__,__LINE__); \
            printf(pszFormat); \
            printf("\n");\
        }\
    }while(0)

/** 打印Debug以上级别信息 */
#define HITEST_LOGD(pszFormat...) \
    do\
    {\
        if((HITEST_LOG_LEVEL_DEBUG <= HITEST_GetLogLevel()) && (HITEST_LOG_LEVEL_CLOSE > HITEST_GetLogLevel()))\
        {\
            printf("[file=%s],[func=%s],[line=%d]",__FILE__,__FUNCTION__,__LINE__); \
            printf(pszFormat); \
            printf("\n");\
        }\
    }while(0)

/** 打印所有级别信息 */
#define HITEST_LOGV(pszFormat...) \
    do\
    {\
        if((HITEST_LOG_LEVEL_V <= HITEST_GetLogLevel()) && (HITEST_LOG_LEVEL_CLOSE > HITEST_GetLogLevel()))\
        {\
            printf("[file=%s],[func=%s],[line=%d]",__FILE__,__FUNCTION__,__LINE__); \
            printf(pszFormat); \
            printf("\n");\
        }\
    }while(0)

typedef HI_S32 (*HITEST_PFN)();

/*存放函数及函数名*/
typedef struct hiTest_func_s
{
    HITEST_PFN   hiTest_FUN_pfn;
    const HI_CHAR* pFunName;
} HITEST_FUNC_S;

/*计时*/
typedef enum hiTest_Timing_e
{
    HITEST_TIMING_START,      /**开始计时 */
    HITEST_TIMING_END,        /**结束计时 */
    HITEST_TIMING_BUTT
} HITEST_TIMING_E;

/*计时器序号*/
typedef enum hiTest_TimerOrder_e
{
    HITEST_TIMER_ONE,
    HITEST_TIMER_TWO,
    HITEST_TIMER_THREE,
    HITEST_TIMER_FOUR,
    HITEST_TIMER_FIVE,
    HITEST_TIMER_BUTT
} HITEST_TIMER_ORDER_E;

/*Log打印级别*/
typedef enum _HITEST_LOG_LEVEL_E
{
    HITEST_LOG_LEVEL_ERROR,
    HITEST_LOG_LEVEL_WARNING,
    HITEST_LOG_LEVEL_INFO,
    HITEST_LOG_LEVEL_DEBUG,
    HITEST_LOG_LEVEL_V,
    HITEST_LOG_LEVEL_CLOSE,
    HITEST_LOG_LEVEL_BUTT
} HITEST_LOG_LEVEL_E;

HI_VOID HITEST_InitResultFlag(HI_VOID);
HI_BOOL HITEST_GetResultFlag(HI_VOID);
HI_VOID HITEST_SetResultFlag(HI_BOOL flag);
HI_VOID HITEST_FailPrint(HI_CHAR* pFunc, HI_S32 s32Ret, HI_S32 s32Line);
HI_VOID HITEST_FinalResult(HI_CHAR* pFunc, HI_S32 s32Line);
HI_VOID HITEST_TimeStamps(HITEST_TIMER_ORDER_E s32TimerID, HITEST_TIMING_E eTimingFlg);
HI_S32 TEST_Entry(HI_S32 argc, HI_CHAR* argv[], HITEST_FUNC_S HITEST_List[], HI_S32 s32ListLen);
HI_VOID HITEST_InitLogLevel(HITEST_LOG_LEVEL_E eLogLevel);
HITEST_LOG_LEVEL_E HITEST_GetLogLevel();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
