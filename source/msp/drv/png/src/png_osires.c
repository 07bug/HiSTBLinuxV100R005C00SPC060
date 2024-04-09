/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name           : png_osires.c
Version             : Initial Draft
Author              :
Created             : 2018/01/01
Description         : PNG osires layer code     CNcomment:PNG osires实现
Function List       :


History             :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
**************************************************************************************************/
#include "hi_drv_mmz.h"
#include "hi_drv_png.h"
#include "hi_png_errcode.h"
#include "png_define.h"
#include "png_osires.h"
#include "hi_gfx_sys_k.h"
#include "hi_png_checkpara.h"


extern HI_BOOL gs_PngDebugInterApi;
extern HI_BOOL gs_PngDebugUnf;

static PNG_INSTANCE_S g_PngInstance[PNG_MAX_HANDLE];

/* handle lock */
HI_DECLARE_MUTEX(g_HandleMutex);

/********************************************************************************************
* func    : handle init
* in      : none
* out     : none
* ret     : 1--32   decoder handle
* ret     : HI_ERR_PNG_NOOPEN   not open devide
* ret     : HI_ERR_PNG_NOHANDLE no decoder resource
* others  : support 32 decoder at most
*********************************************************************************************/
HI_S32 PngOsiResInitHandle(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);
    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);
    return HI_SUCCESS;
}

/********************************************************************************************
* func    : handle deinit
* in      : none
* out     : none
* ret     : none
* others  : support 32 decoder at most
*********************************************************************************************/
HI_VOID PngOsiResDeinitHandle(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);
    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);
    return;
}

/********************************************************************************************
* func    : alloc handle
* in      : none
* out     : none
* ret     : 1--32   decoder handle
* ret     : HI_ERR_PNG_NOHANDLE no handle resource
* others  : Max handle count is 32
            CNcomment:最多支持创建32个handle
*********************************************************************************************/
HI_S32 PngOsiResAllocHandle(HI_PNG_HANDLE *ps32Handle)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);

    if (HI_NULL == ps32Handle)
    {
        HI_GFX_LOG_PrintErrCode(HI_ERR_PNG_NULLPTR);
        return HI_ERR_PNG_NULLPTR;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PNG_DOWN_INTERRUPTIBLE, HI_FAILURE);
        return HI_ERR_PNG_INTERRUPT;
    }

    /* find handle */
    for (i = 0; i < PNG_MAX_HANDLE; i++)
    {
        if (!g_PngInstance[i].bInUse)
        {
            break;
        }
    }

    /* no handle */
    if (PNG_MAX_HANDLE == i)
    {
        PNG_WARNING("No handle!\n");
        PNG_UP(&g_HandleMutex);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_ERR_PNG_NOHANDLE;
    }

    HI_GFX_Memset(&g_PngInstance[i], 0, sizeof(PNG_INSTANCE_S));

    g_PngInstance[i].bInUse = HI_TRUE;
    sema_init(&g_PngInstance[i].stInstanceLock, 1);

    PNG_UP(&g_HandleMutex);

    *ps32Handle = (i + 1);

    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);

    return HI_SUCCESS;
}

/********************************************************************************************
* func     : release handle
* in       : s32Handle   decoder handle
* out      : none
* ret      : HI_SUCCESS  success
* ret      : HI_ERR_PNG_INVALID_HANDLE   invalid handle
* others   :
*********************************************************************************************/
HI_S32 PngOsiResReleaseHandle(HI_PNG_HANDLE s32Handle)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);

    if ((s32Handle <= 0) || (s32Handle > PNG_MAX_HANDLE))
    {
        PNG_ERROR("Invalid handle:%d!\n", s32Handle);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PNG_DOWN_INTERRUPTIBLE, HI_FAILURE);
        return HI_ERR_PNG_INTERRUPT;
    }

    if (!g_PngInstance[s32Handle - 1].bInUse)
    {
        PNG_ERROR("handle %d not in use!\n", s32Handle);
        PNG_UP(&g_HandleMutex);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    /* clear instance*/
    HI_GFX_Memset(&g_PngInstance[s32Handle - 1], 0, sizeof(PNG_INSTANCE_S));
    PNG_UP(&g_HandleMutex);

    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);

    return HI_SUCCESS;
}

/********************************************************************************************
* func    : get handle instance
* in      : s32Handle   decoder handle
* out     : none
* ret     : HI_SUCCESS  success
* ret     : HI_ERR_PNG_INVALID_HANDLE   invalid handle
* others  :
*********************************************************************************************/
HI_S32 PngOsiResGetInstance(HI_PNG_HANDLE s32Handle, PNG_INSTANCE_S **ppstInstance)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);

    if (NULL == ppstInstance)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_ERR_PNG_NULLPTR;
    }

    if ((s32Handle <= 0) || (s32Handle > PNG_MAX_HANDLE))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    PNG_DOWN_INTERRUPTIBLE(&g_HandleMutex, s32Ret);
    if (s32Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(PNG_DOWN_INTERRUPTIBLE, HI_FAILURE);
        return HI_ERR_PNG_INTERRUPT;
    }

    if (!g_PngInstance[s32Handle - 1].bInUse)
    {
        PNG_UP_INT(&g_HandleMutex);
        //HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_ERR_PNG_INVALID_HANDLE;
    }

    *ppstInstance = &g_PngInstance[s32Handle - 1];

    PNG_UP_INT(&g_HandleMutex);

    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);

    return HI_SUCCESS;
}

/********************************************************************************************
* func     : allock mem
* in       : pName mem name
* in       : u32Size mem size
* in       : u32Align align setting
* out      : pu32Phyaddr starting of memory
* ret      : HI_SUCCESS  success
* ret      : HI_ERR_PNG_NOMEM    no memory
* others   :
*********************************************************************************************/
HI_S32 PngOsiResAllocMem(HI_UCHAR *pName, HI_U32 u32Size, HI_U32 u32Align, HI_U32 *pu32Phyaddr)
{
    HI_BOOL bMmu = HI_TRUE;
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);

    if ((NULL == pu32Phyaddr) || (0 == u32Size))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_ERR_PNG_NOMEM;
    }

    *pu32Phyaddr = HI_GFX_AllocMem(pName, "iommu", u32Size, &bMmu);
    if (0 == *pu32Phyaddr)
    {
        HI_GFX_LOG_PrintFuncErr(HI_GFX_AllocMem, HI_FAILURE);
        return HI_ERR_PNG_NOMEM;
    }

    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);

    return HI_SUCCESS;
}

/********************************************************************************************
* func    : release memory
* in      :   u32Phyaddr release physical address
* out     :  none
* ret     :  none
* others  :
*********************************************************************************************/
HI_VOID PngOsiResReleaseMem(HI_U32 u32Phyaddr)
{
    HI_GFX_LOG_FuncEnter(gs_PngDebugInterApi);
    if (u32Phyaddr)
    {
        HI_GFX_FreeMem(u32Phyaddr, HI_TRUE);
    }
    HI_GFX_LOG_FuncExit(gs_PngDebugInterApi);
    return;
}

/* default stream buffer size*/
#define PNG_BUF_DEFAULTSIZE (128 * 1024)

HI_VOID PngOsiShowInstanceState(struct seq_file *p)
{
    HI_U32 i = 0;
    CHECK_PNG_EQUAL_UNRETURN(NULL, p);

    PROC_PRINT(p, "***********png state start******************\n");
    for (i = 0; i < PNG_MAX_HANDLE; i++)
    {
        if (!g_PngInstance[i].bInUse)
        {
            continue;
        }
        PROC_PRINT(p, "handle : %d\n", i);
        PROC_PRINT(p, "state  : %d\n", g_PngInstance[i].eState);
        PROC_PRINT(p, "sync   : %d\n", g_PngInstance[i].bSync);

    }
    PROC_PRINT(p, "***********png state end********************\n");
}
