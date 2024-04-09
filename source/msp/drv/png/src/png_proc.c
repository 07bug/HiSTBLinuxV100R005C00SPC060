/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name           : png_proc.c
Version             : Initial Draft
Author              :
Created             : 2018/01/01
Description         : png proc infomation
Function List       :


History             :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
**************************************************************************************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

#include "hi_drv_proc.h"

#include "png_proc.h"
#include "png_define.h"

#ifndef CONFIG_GFX_PROC_UNSUPPORT

PNG_PROC_INFO_S gs_stPngProcInfo = {0};

static HI_BOOL gs_bPngProcOn = HI_FALSE;

extern HI_BOOL gs_PngDebugInterApi;
extern HI_BOOL gs_PngDebugUnf;

static HI_CHAR *gs_decstate[HI_PNG_STATE_BUTT + 1] =
{
    "Nostart",
    "Decoding",
    "Finish",
    "Err",
    "Unknown"
};

static HI_CHAR *gs_decfmt[] =
{
    "Gray",
    "Unknown",
    "RGB",
    "Clut",
    "AGray",
    "Unknown",
    "ARGB"
};

extern HI_VOID PngOsiShowInstanceState(struct seq_file *p);

HI_S32 PNG_Read_Proc(struct seq_file *p, HI_VOID *v)
{
    DRV_PROC_ITEM_S *item = NULL;
    PNG_PROC_INFO_S *procinfo = NULL;

    HI_UNUSED(v);

    if (NULL == p)
    {
        return HI_FAILURE;
    }

    item = (DRV_PROC_ITEM_S *)(p->private);
    if (NULL == item)
    {
        return HI_FAILURE;
    }

    procinfo = (PNG_PROC_INFO_S *)(item->data);
    if (NULL == procinfo)
    {
        return HI_FAILURE;
    }

    PROC_PRINT(p, "width\t\t:%u\n",  procinfo->u32Width);
    PROC_PRINT(p, "height\t\t:%u\n", procinfo->u32Height);
    if (procinfo->eColorFmt < sizeof(gs_decfmt)/sizeof(gs_decfmt[0]))
    {
        PROC_PRINT(p, "fmt\t\t:%s\n", gs_decfmt[procinfo->eColorFmt]);
    }
    PROC_PRINT(p, "bitdepth\t:%d\n",    procinfo->u8BitDepth);
    PROC_PRINT(p, "transform\t:0x%x\n", procinfo->u32Transform);
    PROC_PRINT(p, "sync\t\t:%s\n", procinfo->bSync ? ("YES") : ("NO"));
    if (procinfo->eState < (HI_PNG_STATE_BUTT + 1))
    {
        PROC_PRINT(p, "state\t\t:%s\n", gs_decstate[procinfo->eState]);
    }
    PROC_PRINT(p, "filter buf addr\t:0x%x\n", procinfo->u32FlterPhyaddr);
    PROC_PRINT(p, "filter buf size\t:0x%x\n", procinfo->u32Size);
    PROC_PRINT(p, "stream buf addr\t:0x%x\n", procinfo->u32StreamBufPhyaddr);
    PROC_PRINT(p, "dst addr\t:0x%x\n",        procinfo->u32ImagePhyaddr);
    PROC_PRINT(p, "dst stride\t:0x%x\n",      procinfo->u32Stride);
    PROC_PRINT(p, "transcolor\t:0x%x%x%x\n",  procinfo->u16TrnsColorRed, procinfo->u16TrnsColorGreen, procinfo->u16TrnsColorBlue);
    PROC_PRINT(p, "filler\t\t:0x%x\n",        procinfo->u16Filler);

    PngOsiShowInstanceState(p);

    return HI_SUCCESS;
}

HI_S32 PNG_Write_Proc(struct file *file, const char __user *pBuf, size_t count, loff_t *ppos)
{
    HI_CHAR TmpBuf[128] = {'\0'};

    HI_UNUSED(file);
    HI_UNUSED(ppos);

    if (NULL == pBuf)
    {
        return 0;
    }

    if (count > sizeof(TmpBuf))
    {
        return 0;
    }

    if (copy_from_user(TmpBuf, pBuf, count))
    {
        return 0;
    }
    TmpBuf[sizeof(TmpBuf) - 1] = '\0';

     if (strncmp("debug_unf on", TmpBuf, 12) == 0)
   {
      gs_PngDebugUnf = HI_TRUE;
      return count;
   }

   if (strncmp("debug_unf off", TmpBuf, 13) == 0)
   {
      gs_PngDebugUnf = HI_FALSE;
      return count;
   }

   if (strncmp("debug_inter on", TmpBuf, 14) == 0)
   {
      gs_PngDebugInterApi = HI_TRUE;
      return count;
   }

   if (strncmp("debug_inter off", TmpBuf, 15) == 0)
   {
      gs_PngDebugInterApi = HI_FALSE;
      return count;
   }
    return 0;
}

HI_VOID PNG_ProcInit(HI_VOID)
{
    GFX_PROC_ITEM_S pProcItem = {PNG_Read_Proc, PNG_Write_Proc, NULL};
    HI_GFX_PROC_AddModule("png", &pProcItem, &gs_stPngProcInfo);
    return;
}

HI_VOID PNG_ProcCleanup(HI_VOID)
{
    HI_GFX_PROC_RemoveModule("png");
    return;
}

HI_BOOL PNG_IsProcOn(HI_VOID)
{
    return gs_bPngProcOn;
}

#endif
