/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : jpeg_drv_proc.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : release jpeg proc debug
Function List    :

History          :
Date                        Author                     Modification
2018/01/01                   sdk                       Created file
************************************************************************************************/

/*********************************add include here**********************************************/
#include "hi_jpeg_config.h"

#ifdef CONFIG_JPEG_PROC_ENABLE
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include "hi_jpeg_checkpara.h"
#include "hi_drv_jpeg.h"
#include "hi_drv_proc.h"
#include "hi_gfx_comm_k.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition ************************************************/

#define PROC_JPEG_ENTRY_NAME            "jpeg"

/*************************** Structure Definition **********************************************/

/********************** Global Variable declaration ********************************************/

HI_JPEG_PROC_INFO_S *g_stJpegDecProcInfo = NULL;

extern HI_BOOL gs_JpegDebugInterApi;
extern HI_BOOL gs_JpegDebugUnf;

/******************************* API forward declarations **************************************/

/******************************* API realization ***********************************************/
static HI_S32 JPEG_PROC_Read(struct seq_file *p, HI_VOID *v)
{
   DRV_PROC_ITEM_S *item  = NULL;
   HI_JPEG_PROC_INFO_S *procinfo = NULL;
   HI_UNUSED(v);

   HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

   CHECK_JPEG_NULLPOINTER_RETURN_VALUE(p, HI_FAILURE);

   item = (DRV_PROC_ITEM_S *)(p->private);
   CHECK_JPEG_NULLPOINTER_RETURN_VALUE(item, HI_FAILURE);

   procinfo = (HI_JPEG_PROC_INFO_S *)(item->data);
   CHECK_JPEG_NULLPOINTER_RETURN_VALUE(procinfo, HI_FAILURE);

   CHECK_JPEG_NULLPOINTER_RETURN_VALUE(g_stJpegDecProcInfo, HI_FAILURE);

   CHECK_JPEG_UNEQUAL_RETURN(HI_TRUE, g_stJpegDecProcInfo->bProcOn, HI_SUCCESS);

   SEQ_Printf(p, "++++++++++++++++++++++++++++ decode state +++++++++++++++++++++++++\n");
   SEQ_Printf(p, "use proc\t\t:%d\n",            procinfo->bProcOn);
   SEQ_Printf(p, "decode lock times\t:%d\n",     procinfo->DecLockTimes);
   SEQ_Printf(p, "decode pthread nums\t:%u\n",   procinfo->DecPthreadNums);
   SEQ_Printf(p, "continue open times\t:%u\n",   procinfo->OpenDevConTimes);
   SEQ_Printf(p, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

   HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

   return HI_SUCCESS;
}

static HI_S32 JPEG_PROC_Write(struct file * file,const char __user * pBuf,size_t count,loff_t *ppos)
{
   HI_CHAR buf[128] = {'\0'};
   HI_UNUSED(file);
   HI_UNUSED(ppos);

   CHECK_JPEG_NULLPOINTER_RETURN_VALUE(pBuf, 0);

   if (count > sizeof(buf))
   {
      HI_GFX_LOG_PrintErrCode(0);
      return 0;
   }

   if (copy_from_user(buf, pBuf, count))
   {
      HI_GFX_LOG_PrintFuncErr(copy_from_user,0);
      return 0;
   }
   buf[sizeof(buf) - 1] = '\0';

   if (NULL == g_stJpegDecProcInfo)
   {
      HI_GFX_LOG_PrintErrCode(0);
      return count;
   }

   if (strncmp("help", buf, 4) == 0)
   {
       HI_DRV_PROC_EchoHelper("===============================================================\n");
       HI_DRV_PROC_EchoHelper("### jpeg info:\n");
       HI_DRV_PROC_EchoHelper("### ***********************************************************\n");
       HI_DRV_PROC_EchoHelper("### jpeg proc support cmd as follows:\n");
       HI_DRV_PROC_EchoHelper("###     proc on       : open proc\n");
       HI_DRV_PROC_EchoHelper("###     proc off      : close proc\n");
       HI_DRV_PROC_EchoHelper("===============================================================\n");
       return count;
   }

   if (strncmp("proc on", buf, 7) == 0)
   {
      g_stJpegDecProcInfo->bProcOn = HI_TRUE;
      return count;
   }

   if (strncmp("proc off", buf, 8) == 0)
   {
      g_stJpegDecProcInfo->bProcOn = HI_FALSE;
      return count;
   }

   if (strncmp("debug_unf on", buf, 12) == 0)
   {
      gs_JpegDebugUnf = HI_TRUE;
      return count;
   }

   if (strncmp("debug_unf off", buf, 13) == 0)
   {
      gs_JpegDebugUnf = HI_FALSE;
      return count;
   }

   if (strncmp("debug_inter on", buf, 14) == 0)
   {
      gs_JpegDebugInterApi = HI_TRUE;
      return count;
   }

   if (strncmp("debug_inter off", buf, 15) == 0)
   {
      gs_JpegDebugInterApi = HI_FALSE;
      return count;
   }

   return count;
}

/*****************************************************************************
 * Function     : JPEG_PROC_Init
 * Description  :  initial jpeg proc
 * param[in]    : NA
 * retval       : NA
 *****************************************************************************/
HI_S32 JPEG_PROC_Init(HI_VOID)
{
     GFX_PROC_ITEM_S pProcItem = {0};
     HI_CHAR *pEntry_name = PROC_JPEG_ENTRY_NAME;

     HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

     pProcItem.fnRead   = JPEG_PROC_Read;
     pProcItem.fnWrite  = JPEG_PROC_Write;
     pProcItem.fnIoctl  = NULL;

     g_stJpegDecProcInfo = (HI_JPEG_PROC_INFO_S*)vmalloc(sizeof(HI_JPEG_PROC_INFO_S));
     if (NULL == g_stJpegDecProcInfo)
     {
        HI_GFX_LOG_PrintFuncErr(vmalloc,HI_FAILURE);
        return HI_FAILURE;
     }

     HI_GFX_Memset((HI_VOID*)g_stJpegDecProcInfo, 0x0, sizeof(HI_JPEG_PROC_INFO_S));

     HI_GFX_PROC_AddModule(pEntry_name,&pProcItem,(HI_VOID *)g_stJpegDecProcInfo);

     HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);

     return HI_SUCCESS;
}

/*****************************************************************************
 * Function     : JPEG_PROC_DInit
 * Description  :  dinitial jpeg proc
 * param[in]    : NA
 * retval       : NA
*****************************************************************************/
HI_VOID JPEG_PROC_DInit(HI_VOID)
{
    HI_CHAR *pEntry_name = PROC_JPEG_ENTRY_NAME;
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);

    if (NULL != g_stJpegDecProcInfo)
    {
       HI_GFX_PROC_RemoveModule(pEntry_name);
       vfree(g_stJpegDecProcInfo);
       g_stJpegDecProcInfo = NULL;
    }

    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

/*****************************************************************************
 * Function     : JPEG_PROC_SetPthreadNum
 * Description  : set jpeg decode pthread numbers
 * param[in]    : PthreadNums
 * retval       : NA
*****************************************************************************/
HI_VOID JPEG_PROC_SetPthreadNum(HI_U32 PthreadNums)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    if (NULL != g_stJpegDecProcInfo)
    {
       g_stJpegDecProcInfo->DecPthreadNums = PthreadNums;
    }
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

/*****************************************************************************
 * Function     : JPEG_PROC_SetDecLockTimes
 * Description  : set jpeg decode has been lock times
 * param[in]    : PthreadNums
 * retval       : NA
*****************************************************************************/
HI_VOID JPEG_PROC_SetDecLockTimes(HI_U32 LockTimes)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    if (NULL != g_stJpegDecProcInfo)
    {
       g_stJpegDecProcInfo->DecLockTimes = LockTimes;
    }
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

/*****************************************************************************
 * Function     : JPEG_PROC_SetOpenDevCnt
 * Description  : set jpeg decode has been open times
 * param[in]    : PthreadNums
 * retval       : NA
*****************************************************************************/
HI_VOID JPEG_PROC_SetOpenDevCnt(HI_S32 OpenTimes)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    if (NULL != g_stJpegDecProcInfo)
    {
       g_stJpegDecProcInfo->OpenDevConTimes += OpenTimes;
    }
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

#endif/**CONFIG_JPEG_PROC_ENABLE**/
