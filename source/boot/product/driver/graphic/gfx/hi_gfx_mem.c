/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_mem.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : memory manage
                     CNcomment: 内存管理 CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                    sdk                        Created file
************************************************************************************************/


/*********************************add include here**********************************************/
#include "hi_gfx_mem.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_sys.h"

#include "hi_common.h"
#include "hi_drv_pdm.h"
/***************************** Macro Definition ************************************************/

#define CONFIG_GFX_RESERVE_SIZE               10
//#define CONFIG_MEM_DEBUG

/*************************** Structure Definition **********************************************/

/********************** Global Variable declaration ********************************************/
static HI_CHAR gs_CmpData[CONFIG_GFX_RESERVE_SIZE] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};

/**********************       API realization       ********************************************/
/*****************************************************************************
* func         : BOOT_GFX_RESERVE_Alloc
* description  : 分配保留内存
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_RESERVE_Alloc(HI_U32 u32Size,HI_CHAR* pModuleName)
{
#ifdef CONFIG_MEM_DEBUG
    HI_S32 Cnt = 0;
    HI_CHAR* TmpBuf = NULL;
#endif
    HI_S32 Ret = HI_SUCCESS;
    MMZ_BUFFER_S stMBuf;
    HI_GFX_LOG_FuncEnter();

    if (0 == u32Size)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return NULL;
    }
    HI_GFX_Memset(&stMBuf,0x0,sizeof(stMBuf));

    Ret = HI_DRV_PDM_AllocReserveMem(pModuleName, (u32Size + CONFIG_GFX_RESERVE_SIZE), &stMBuf.u32StartPhyAddr);
    if ((HI_SUCCESS != Ret) || (0 == stMBuf.u32StartPhyAddr))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return NULL;
    }

    HI_GFX_Memcpy((HI_CHAR*)stMBuf.u32StartPhyAddr,gs_CmpData,CONFIG_GFX_RESERVE_SIZE);
    HI_GFX_Memcpy((HI_CHAR*)(stMBuf.u32StartPhyAddr + u32Size),gs_CmpData,CONFIG_GFX_RESERVE_SIZE);

#ifdef CONFIG_MEM_DEBUG
    TmpBuf = (HI_CHAR*)stMBuf.u32StartPhyAddr;
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInfo("initial first 10bytes data");
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
        HI_GFX_DBG_PrintXInt(TmpBuf[Cnt]);
    }
    HI_GFX_DBG_PrintInfo("============================================================================");

    TmpBuf = (HI_CHAR*)(stMBuf.u32StartPhyAddr + u32Size);
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInfo("initial last 10bytes data");
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
        HI_GFX_DBG_PrintXInt(TmpBuf[Cnt]);
    }
    HI_GFX_DBG_PrintInfo("============================================================================");
#endif

    HI_GFX_LOG_FuncExit();
    return (HI_CHAR*)stMBuf.u32StartPhyAddr;
}

/*****************************************************************************
* func         : BOOT_GFX_MMZ_Alloc
* description  : 分配连续的物理地址，boot下连续地址也可以做虚拟地址，可直接读写
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_MMZ_Alloc(HI_U32 u32Size)
{
#ifdef CONFIG_MEM_DEBUG
    HI_S32 Cnt = 0;
    HI_CHAR* TmpBuf = NULL;
#endif
    HI_S32 s32Ret = HI_SUCCESS;
    MMZ_BUFFER_S stMBuf;
    HI_GFX_LOG_FuncEnter();

    if (0 == u32Size)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return NULL;
    }
    HI_GFX_Memset(&stMBuf,0x0,sizeof(stMBuf));

    s32Ret = HI_MEM_Alloc(&stMBuf.u32StartPhyAddr, (u32Size + CONFIG_GFX_RESERVE_SIZE));
    if ((HI_SUCCESS != s32Ret) || (0 == stMBuf.u32StartPhyAddr))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return NULL;
    }

    HI_GFX_Memcpy((HI_CHAR*)stMBuf.u32StartPhyAddr,gs_CmpData,CONFIG_GFX_RESERVE_SIZE);
    HI_GFX_Memcpy((HI_CHAR*)(stMBuf.u32StartPhyAddr + u32Size),gs_CmpData,CONFIG_GFX_RESERVE_SIZE);

#ifdef CONFIG_MEM_DEBUG
    TmpBuf = (HI_CHAR*)stMBuf.u32StartPhyAddr;
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInfo("initial first 10bytes data");
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
        HI_GFX_DBG_PrintXInt(TmpBuf[Cnt]);
    }
    HI_GFX_DBG_PrintInfo("============================================================================");

    TmpBuf = (HI_CHAR*)(stMBuf.u32StartPhyAddr + u32Size);
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInfo("initial last 10bytes data");
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
        HI_GFX_DBG_PrintXInt(TmpBuf[Cnt]);
    }
    HI_GFX_DBG_PrintInfo("============================================================================");
#endif

    HI_GFX_LOG_FuncExit();
    return (HI_CHAR*)stMBuf.u32StartPhyAddr;
}


/*****************************************************************************
* func         : BOOT_GFX_MMZ_Free
* description  : 释放地址
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_MMZ_Free(HI_CHAR* pPhyAddr)
{
    HI_GFX_LOG_FuncEnter();
    if (NULL != pPhyAddr)
    {
       HI_MEM_Free((HI_VOID*)pPhyAddr);
       pPhyAddr = NULL;
    }
    HI_GFX_LOG_FuncExit();
    return;
}

/*****************************************************************************
* func         : BOOT_GFX_Malloc
* description  : 使用malloc分配内存，使用完释放给其它功能使用,小内存
                 使用该接口比如handle等，减少内存碎片
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_Malloc(HI_U32 u32Size)
{
    HI_GFX_LOG_FuncEnter();
    if (0 == u32Size)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return NULL;
    }
    HI_GFX_LOG_FuncExit();
    return (HI_CHAR*)malloc(u32Size);
}

/*****************************************************************************
* func         : BOOT_GFX_Free
* description  : 释放地址
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Free(HI_CHAR* pVirAddr)
{
    HI_GFX_LOG_FuncEnter();
    if (NULL != pVirAddr)
    {
        free(pVirAddr);
        pVirAddr = NULL;
    }
    HI_GFX_LOG_FuncExit();
    return;
}

/*****************************************************************************
* func         : BOOT_GFX_Memcmp
* description  : 地址内容校验，这里的地址必须是本模块分配的，约定俗成的，会多分配
                 10个字节作为是否内存越界校验
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Memcmp(HI_CHAR* pPhyAddr, HI_U32 Size)
{
    HI_S32 Cnt = 0;
    HI_CHAR* TmpBuf = NULL;
    HI_BOOL MemOk = HI_FALSE;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL_UNRETURN(pPhyAddr);

    if ((0 == Size) || (Size <= CONFIG_GFX_RESERVE_SIZE))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return;
    }

    TmpBuf = pPhyAddr;
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
       if (TmpBuf[Cnt] != gs_CmpData[Cnt])
       {
           MemOk = HI_TRUE;
           break;
       }
    }

    if (HI_FALSE == MemOk)
    {
        HI_GFX_DBG_PrintInfo("============================================================================");
        HI_GFX_DBG_PrintInfo("the memory has not been used");
        HI_GFX_DBG_PrintInfo("============================================================================");
    }

    MemOk = HI_FALSE;
    TmpBuf = pPhyAddr + Size;
    for (Cnt = 0; Cnt < CONFIG_GFX_RESERVE_SIZE; Cnt++)
    {
       if (TmpBuf[Cnt] != gs_CmpData[Cnt])
       {
           MemOk = HI_TRUE;
           break;
       }
    }

    if (HI_TRUE == MemOk)
    {
        HI_GFX_DBG_PrintInfo("============================================================================");
        HI_GFX_DBG_PrintInfo("the memory be write wrong data");
        HI_GFX_DBG_PrintInfo("============================================================================");
    }

    HI_GFX_LOG_FuncExit();
    return;
}
