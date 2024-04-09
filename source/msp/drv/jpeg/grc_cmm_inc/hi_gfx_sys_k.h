/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : hi_gfx_sys_k.h
Version          : version 1.0
Author           :
Created          : 2018/01/01
Description      : define system function
Function List    :

History          :
Date               Author                Modification
2018/01/01          sdk
***********************************************************************************************/
#ifndef  _HI_GFX_SYS_K_H_
#define  _HI_GFX_SYS_K_H_


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

/*********************************add include here*********************************************/
#ifndef HI_BUILD_IN_BOOT
#include <linux/ctype.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/delay.h>
#endif

#ifdef HI_BUILD_IN_BOOT
#define USHRT_MAX       ((u16)(~0U))
#define SHRT_MAX        ((s16)(USHRT_MAX>>1))
#define SHRT_MIN        ((s16)(-SHRT_MAX - 1))
#define INT_MAX         ((int)(~0U>>1))
#define INT_MIN         (-INT_MAX - 1)
#define UINT_MAX        (~0U)
#define LONG_MAX        ((long)(~0UL>>1))
#define LONG_MIN        (-LONG_MAX - 1)
#define ULONG_MAX       (~0UL)
#define LLONG_MAX       ((long long)(~0ULL>>1))
#define LLONG_MIN       (-LLONG_MAX - 1)
#define ULLONG_MAX      (~0ULL)
#define SIZE_MAX        (~(size_t)0)
#endif

/***************************** Macro Definition ***********************************************/
#define HI_GFX_Memcpy(dst,src,size)                          memcpy(dst, src, size);
#define HI_GFX_Memset(dst,value,size)                        memset(dst, value, size);

/*************************** Enum Definition **************************************************/

/*************************** Structure Definition *********************************************/


/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/

/**===============================================================================================
 ** 确保运算不出现反转
 **==============================================================================================**/
#define HI_GFX_CHECK_U64_ADDITION_REVERSAL_UNRETURN(left_value, right_value) do{\
                            if ((0 == (left_value)) || ((left_value) > (ULONG_MAX - (right_value)))) {\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return;}\
                            }while(0)

#define HI_GFX_CHECK_U64_ADDITION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                            if ((0 == (left_value)) || ((left_value) > (ULONG_MAX - (right_value)))) {\
                                  HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                  return ret;}\
                            }while(0)

/** addition by unsigned int, maybe equal to 0 **/
#define HI_GFX_CHECK_UINT_ADDITION_REVERSAL_UNRETURN(left_value, right_value) do{\
                            if ((0 == (left_value)) || ((left_value) > (UINT_MAX - (right_value)))) {\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return;}\
                            }while(0)

#define HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                            if ((0 == (left_value)) || ((left_value) > (UINT_MAX - (right_value)))) {\
                                 return ret;}\
                            }while(0)

/** addition by unsigned int, maybe equal to 0 **/
#define HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_UNRETURN(left_value, right_value) do{\
                            unsigned long tmp_value = (unsigned long)(left_value) * (unsigned long)(right_value);\
                            if ((0 == tmp_value) || (tmp_value > UINT_MAX)) {\
                                 HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                 return;}\
                            }while(0)

#define HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                            unsigned long tmp_value = (unsigned long)(left_value) * (unsigned long)(right_value);\
                            if ((0 == tmp_value) || (tmp_value > UINT_MAX)) {\
                                 HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                 return ret;}\
                            }while(0)


/** addition by int, maybe equal to 0 **/
#define HI_GFX_CHECK_INT_ADDITION_REVERSAL_UNRETURN(left_value, right_value) do{\
                            if (((left_value) <= 0) || ((left_value) > (INT_MAX - (right_value)))) {\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return;}\
                            }while(0)

#define HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                            if (((left_value) <= 0) || ((left_value) > (INT_MAX - (right_value)))) {\
                               HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return ret;}\
                            }while(0)

/** addition by char, maybe equal to -128 **/
#define HI_GFX_CHECK_CHAR_ADDITION_REVERSAL_UNRETURN(left_value, right_value) do{\
                            if (((left_value) <= 0) || ((right_value) < 0) || ((left_value) > (SCHAR_MAX - (right_value)))) {\
                               HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                               return;}\
                            }while(0)

#define HI_GFX_CHECK_CHAR_ADDITION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                            if (((left_value) <= 0) || ((right_value) < 0) || ((left_value) > (SCHAR_MAX - (right_value)))) {\
                               HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                               return ret;}\
                            }while(0)


/**===============================================================================================
 ** 确保整型转换时不会出现截断错误
 **==============================================================================================**/
/** long to char **/
#define HI_GFX_CHECK_SLONG_TO_CHAR_REVERSAL_UNRETURN(right_value) do{\
                            if (((right_value) < SCHAR_MIN) || ((right_value) > SCHAR_MAX)) {\
                               HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                               return;}\
                            }while(0)

#define HI_GFX_CHECK_SLONG_TO_CHAR_REVERSAL_RETURN(right_value, ret) do{\
                            if (((right_value) < SCHAR_MIN) || ((right_value) > SCHAR_MAX)){\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return ret;}\
                            }while(0)

/** unsigned long to unsigned int **/
#define HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_UNRETURN(right_value) do{\
                            if ((right_value) > UINT_MAX) {\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return;}\
                            }while(0)

#define HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN(right_value, ret) do{\
                            if ((right_value) > UINT_MAX){\
                                HI_PRINT("++++++func %s line %d failure\n",__FUNCTION__,__LINE__);\
                                return ret;}\
                            }while(0)



/**===============================================================================================
** DFX
**==============================================================================================**/
#ifdef CONFIG_GFX_DFX_ENABLE
/** only used for unf interface **/
#define HI_GFX_UNF_FuncBeg()   HI_PRINT("\n[module-gfx-beg] :==========================================================\n");
#define HI_GFX_UNF_FuncEnd()   HI_PRINT("[module-gfx-end] :==========================================================\n");
#define HI_GFX_UNF_FuncEnter(debug) if (HI_TRUE == debug){HI_PRINT("[module-gfx] : %s[%d] : >>>>>>>>>>>>>>>>[enter]\n",__FUNCTION__,__LINE__);}
#define HI_GFX_UNF_FuncExit(debug)  if (HI_TRUE == debug){HI_PRINT("[module-gfx] : %s[%d] : >>>>>>>>>>>>>>>>[exit]\n", __FUNCTION__,__LINE__);}

/** used for all interface except unf **/
#define HI_GFX_LOG_FuncBeg()   HI_PRINT("\n[module-gfx-beg] :==========================================================\n");
#define HI_GFX_LOG_FuncEnd()   HI_PRINT("[module-gfx-end] :==========================================================\n");
#define HI_GFX_LOG_FuncEnter(debug) if (HI_TRUE == debug){HI_PRINT("[module-gfx] : %s[%d] : ===============>[enter]\n",__FUNCTION__,__LINE__);}
#define HI_GFX_LOG_FuncExit(debug)  if (HI_TRUE == debug){HI_PRINT("[module-gfx] : %s[%d] : ===============>[exit]\n", __FUNCTION__,__LINE__);}

/** call func error **/
#define HI_GFX_LOG_PrintFuncErr(func,err_code) HI_PRINT("[module-gfx] : call %s[%d] return [0x%08x]\n",#func,__LINE__,err_code);

/** run func error **/
#define HI_GFX_LOG_PrintErrCode(err_code)      HI_PRINT("[module-gfx] : %s[%d] : error code [0x%08x]\n",__FUNCTION__,__LINE__,err_code);

#else
#define HI_GFX_UNF_FuncBeg()
#define HI_GFX_UNF_FuncEnd()
#define HI_GFX_UNF_FuncEnter(debug)
#define HI_GFX_UNF_FuncExit(debug)
#define HI_GFX_LOG_FuncBeg()
#define HI_GFX_LOG_FuncEnd()
#define HI_GFX_LOG_FuncEnter(debug)
#define HI_GFX_LOG_FuncExit(debug)
#define HI_GFX_LOG_PrintFuncErr(func,err_code)
#define HI_GFX_LOG_PrintErrCode(err_code)
#endif

#ifdef CONFIG_GFX_DBG_ENABLE
#define HI_GFX_DBG_PrintInt(val)    HI_PRINT("[module-gfx] : %s[%d] : %s = %d\n",   __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintUInt(val)   HI_PRINT("[module-gfx] : %s[%d] : %s = %u\n",   __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintLong(val)   HI_PRINT("[module-gfx] : %s[%d] : %s = %lld\n", __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintULong(val)  HI_PRINT("[module-gfx] : %s[%d] : %s = %llu\n", __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintStr(val)    HI_PRINT("[module-gfx] : %s[%d] : %s = %s\n",   __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintVoid(val)   HI_PRINT("[module-gfx] : %s[%d] : %s = %p\n",   __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintFloat(val)  HI_PRINT("[module-gfx] : %s[%d] : %s = %f\n",   __FUNCTION__,__LINE__,#val,val);
#define HI_GFX_DBG_PrintInfo(val)   HI_PRINT("[module-gfx] : %s[%d] : <%s>\n",      __FUNCTION__,__LINE__,val);
#else
#define HI_GFX_DBG_PrintInt(val)
#define HI_GFX_DBG_PrintUInt(val)
#define HI_GFX_DBG_PrintLong(val)
#define HI_GFX_DBG_PrintULong(val)
#define HI_GFX_DBG_PrintStr(val)
#define HI_GFX_DBG_PrintVoid(val)
#define HI_GFX_DBG_PrintFloat(val)
#define HI_GFX_DBG_PrintInfo(val)
#endif

/**===============================================================================================
** 时间函数封装
**==============================================================================================**/
#ifndef HI_BUILD_IN_BOOT
#define HI_GFX_TINIT()    struct timeval tv_cur
#define HI_GFX_TSTART(StartTimes)  do_gettimeofday(&tv_cur); StartTimes = tv_cur.tv_sec * 1000 + tv_cur.tv_usec / 1000
#define HI_GFX_TEND(EndTimes)      do_gettimeofday(&tv_cur); EndTimes   = tv_cur.tv_sec * 1000 + tv_cur.tv_usec / 1000
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */
#endif /*_HI_GFX_SYS_K_H_ */
