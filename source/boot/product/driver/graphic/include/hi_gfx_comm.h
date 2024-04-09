/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_comm.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : common used
                     CNcomment: 公共使用的接口 CNend\n
Function List      :
History            :
Date                            Author                     Modification
2018/01/01                      sdk                        Created file
************************************************************************************************/
#ifndef  __HI_GFX_COMM_H__
#define  __HI_GFX_COMM_H__


/*********************************add include here**********************************************/
#include "hi_type.h"
#ifndef CONFIG_GFX_LOGO_KERNEL
#include "exports.h"
#endif

/***************************** Macro Definition ************************************************/
#define HI_GFX_INVALID_HANDLE       0

#define CONFIG_GFX_MINWIDTH         32
#define CONFIG_GFX_MINHEIGHT        32
#define CONFIG_GFX_MINSTRIDE        32
#define CONFIG_GFX_MAXWIDTH         8192
#define CONFIG_GFX_MAXHEIGHT        8192
#define CONFIG_GFX_MAXSTRIDE        65536
#define CONFIG_GFX_BITSPERPIX       32

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

#define HI_GFX_CHECK_ULONG_TO_UINT_REVERSAL_RETURN(right_value,ret) do{\
                       if ((right_value) > UINT_MAX) {\
                           return ret;}\
                       }while(0)

#define HI_GFX_CHECK_UINT_ADDITION_REVERSAL_UNRETURN(left_value, right_value) do{\
                       if ((0 == (left_value)) || ((left_value) > (UINT_MAX - (right_value)))) {\
                           return;}\
                       }while(0)

#define HI_GFX_CHECK_UINT_ADDITION_REVERSAL_RETURN(left_value, right_value, ret) do{\
                       if ((0 == (left_value)) || ((left_value) > (UINT_MAX - (right_value)))) {\
                            return ret;}\
                       }while(0)


#ifdef CONFIG_GFX_LOG_SUPPORT
#define HI_GFX_Print   printf
#else
#define HI_GFX_Print   {do{}while(0);}
#endif
/**==================================================================================================
**定义打印级别
**==================================================================================================**/
extern HI_U32 gfx_log_level;
/**==================================================================================================
**设置级别1
**==================================================================================================**/
#if !defined(CONFIG_GFX_PROC_UNSUPPORT) && defined(CONFIG_GFX_LOG_SUPPORT)
#define HI_GFX_LOG_PrintFuncErr(func,err_code) if (1 == gfx_log_level){HI_GFX_Print("[module-gfx] : call %s[%d] return [0x%08x]\n",#func,__LINE__,err_code);}
#define HI_GFX_LOG_PrintErrCode(err_code)      if (1 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : error code [0x%08x]\n",__FUNCTION__,__LINE__,err_code);}
#else
#define HI_GFX_LOG_PrintFuncErr(func,err_code)
#define HI_GFX_LOG_PrintErrCode(err_code)
#endif

/**==================================================================================================
 **设置级别2
 **==================================================================================================**/
#if !defined(CONFIG_GFX_PROC_UNSUPPORT) && defined(CONFIG_GFX_LOG_SUPPORT)
#define HI_GFX_UNF_FuncBeg()                   if (2 == gfx_log_level){HI_GFX_Print("\n[module-gfx-beg] :==========================================================\n");}
#define HI_GFX_UNF_FuncEnd()                   if (2 == gfx_log_level){HI_GFX_Print("[module-gfx-end] :==========================================================\n");}
#define HI_GFX_UNF_FuncEnter()                 if (2 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : >>>>>>>>>>>>>>>>[enter]\n",__FUNCTION__,__LINE__);}
#define HI_GFX_UNF_FuncExit()                  if (2 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : >>>>>>>>>>>>>>>>[exit]\n", __FUNCTION__,__LINE__);}
#define HI_GFX_LOG_FuncEnter()                 if (2 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : ===============>[enter]\n",__FUNCTION__,__LINE__);}
#define HI_GFX_LOG_FuncExit()                  if (2 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : ===============>[exit]\n", __FUNCTION__,__LINE__);}
#else
#define HI_GFX_UNF_FuncBeg()
#define HI_GFX_UNF_FuncEnd()
#define HI_GFX_UNF_FuncEnter()
#define HI_GFX_UNF_FuncExit()
#define HI_GFX_LOG_FuncEnter()
#define HI_GFX_LOG_FuncExit()
#endif

/**==================================================================================================
 **设置级别3
 **==================================================================================================**/
#if !defined(CONFIG_GFX_PROC_UNSUPPORT) && defined(CONFIG_GFX_LOG_SUPPORT)
#define HI_GFX_DBG_PrintInt(val)    if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %d\n",   __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintUInt(val)   if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %u\n",   __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintXInt(val)   if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = 0x%x\n", __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintLong(val)   if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %lld\n", __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintULong(val)  if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %llu\n", __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintStr(val)    if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %s\n",   __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintVoid(val)   if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = 0x%p\n", __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintFloat(val)  if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : %s = %f\n",   __FUNCTION__,__LINE__,#val,val);}
#define HI_GFX_DBG_PrintInfo(val)   if (3 == gfx_log_level){HI_GFX_Print("[module-gfx] : %s[%d] : <%s>\n",      __FUNCTION__,__LINE__,val);}
#else
#define HI_GFX_DBG_PrintInt(val)
#define HI_GFX_DBG_PrintUInt(val)
#define HI_GFX_DBG_PrintXInt(val)
#define HI_GFX_DBG_PrintLong(val)
#define HI_GFX_DBG_PrintULong(val)
#define HI_GFX_DBG_PrintStr(val)
#define HI_GFX_DBG_PrintVoid(val)
#define HI_GFX_DBG_PrintFloat(val)
#define HI_GFX_DBG_PrintInfo(val)
#endif

/**==================================================================================================
 **参数检查
 **==================================================================================================**/
#define CHECK_POINT_NULL(para)\
do{\
    if (NULL == para)\
    {\
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);\
        return HI_FAILURE;\
    }\
}while(0)

#define CHECK_POINT_NULL_UNRETURN(para)\
    do{\
        if (NULL == para)\
        {\
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);\
            return;\
        }\
    }while(0)

#define CHECK_PARA_ZERO(para)\
    do{\
        if (0 == para)\
        {\
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);\
            return HI_FAILURE;\
        }\
    }while(0)
/*************************** Structure Definition **********************************************/
typedef struct hiGfxRectS
{
    HI_U32 x;
    HI_U32 y;
    HI_U32 w;
    HI_U32 h;
}HI_GFX_RECT_S;

typedef enum hiGfxLayerIdE
{
    HI_GFX_LAYER_HD_0         = 0,
    HI_GFX_LAYER_HD_1         = 1,
    HI_GFX_LAYER_HD_2         = 2,
    HI_GFX_LAYER_HD_3,
    HI_GFX_LAYER_SD_0,
    HI_GFX_LAYER_SD_1,
    HI_GFX_LAYER_ID_BUTT
}HI_GFX_LAYER_ID_E;

/********************** Global Variable declaration ********************************************/

typedef HI_GFX_RECT_S HI_RECT;

/******************************* API declaration ***********************************************/

#endif /*__HI_GFX_COMM_H__ */
