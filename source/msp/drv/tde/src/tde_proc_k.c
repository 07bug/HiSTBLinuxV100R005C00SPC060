/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_proc_k.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/

/*********************************add include here**********************************************/

#include "tde_proc.h"
#include "tde_config.h"
#include "hi_gfx_sys_k.h"
#include "tde_check_para.h"


/***************************** Macro Definition ********************************************/

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/
#ifndef CONFIG_TDE_PROC_DISABLE
typedef struct _hiTDE_PROCINFO_S
{
    HI_U32          u32CurNode;
    TDE_HWNode_S    stTdeHwNode[TDE_MAX_PROC_NUM];
    HI_BOOL         bProcEnable;
} TDE_PROCINFO_S;

TDE_PROCINFO_S *g_pstTdeProcInfo = NULL;

extern HI_BOOL gs_TdeDebugUnf;
extern HI_BOOL gs_TdeDebugInterApi;

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/
HI_VOID TDEProcRecordNode(TDE_HWNode_S *pHWNode)
{
    if ((!g_pstTdeProcInfo->bProcEnable) || (HI_NULL == pHWNode))
    {
        return;
    }

    TDE_CHECK_ARRAY_OVER_RETURN_NOVALUE(g_pstTdeProcInfo->u32CurNode, TDE_MAX_PROC_NUM);

    HI_GFX_Memcpy(&g_pstTdeProcInfo->stTdeHwNode[g_pstTdeProcInfo->u32CurNode], pHWNode, sizeof(TDE_HWNode_S));

    g_pstTdeProcInfo->u32CurNode++;
    g_pstTdeProcInfo->u32CurNode = (g_pstTdeProcInfo->u32CurNode) % TDE_MAX_PROC_NUM;

    return;
}

HI_S32 tde_write_proc(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    HI_CHAR TmpBuf[128] = {'\0'};
    HI_UNUSED(file);
    HI_UNUSED(ppos);
    TDE_CHECK_NULLPOINTER_RETURN_VALUE(buf, 0);

    if (count > sizeof(TmpBuf))
    {
        return 0;
    }

    if (copy_from_user(TmpBuf, buf, count))
    {
        return 0;
    }
    TmpBuf[sizeof(TmpBuf) - 1] = '\0';

    if (strncmp("debug_unf on", TmpBuf, 12) == 0)
    {
       gs_TdeDebugUnf = HI_TRUE;
       return count;
    }

    if (strncmp("debug_unf off", TmpBuf, 13) == 0)
    {
       gs_TdeDebugUnf = HI_FALSE;
       return count;
    }

    if (strncmp("debug_inter on", TmpBuf, 14) == 0)
    {
       gs_TdeDebugInterApi = HI_TRUE;
       return count;
    }

    if (strncmp("debug_inter off", TmpBuf, 15) == 0)
    {
       gs_TdeDebugInterApi = HI_FALSE;
       return count;
    }

    return count;
}

HI_S32 tde_read_proc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 j = 0;
    HI_U32 *pu32Cur = NULL;
    TDE_HWNode_S *pstHwNode = NULL;
    HI_UNUSED(v);

    if (NULL == p)
    {
        return 0;
    }

    pstHwNode = g_pstTdeProcInfo->stTdeHwNode;
    p = wprintinfo(p);

    for (j = 0 ; (j < g_pstTdeProcInfo->u32CurNode) && (j < TDE_MAX_PROC_NUM); j++)
    {
        pu32Cur = (HI_U32 *)&pstHwNode[j];
        TdeHalNodePrintInfo(p, pu32Cur);
    }

    return 0;
}

HI_S32 tde_proc_init(HI_VOID)
{
    g_pstTdeProcInfo = (TDE_PROCINFO_S*)HI_GFX_VMALLOC(HIGFX_TDE_ID, sizeof(TDE_PROCINFO_S));
    if (NULL == g_pstTdeProcInfo)
    {
       return HI_FAILURE;
    }

    HI_GFX_Memset(g_pstTdeProcInfo, 0, sizeof(TDE_PROCINFO_S));

    g_pstTdeProcInfo->u32CurNode  = 0;
    g_pstTdeProcInfo->bProcEnable = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID tde_proc_dinit(HI_VOID)
{
    if (NULL != g_pstTdeProcInfo)
    {
       HI_GFX_VFREE(HIGFX_TDE_ID, (HI_VOID*)g_pstTdeProcInfo);
    }

    g_pstTdeProcInfo = NULL;

    return;
}
#endif
