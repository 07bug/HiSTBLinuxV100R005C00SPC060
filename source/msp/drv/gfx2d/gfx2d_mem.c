/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : gfx2d_mem.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                  Author                Modification
2018/01/01            sdk                   Created file
**************************************************************************************************/

/*********************************add include here************************************************/
#include <linux/fs.h>

#include "hi_gfx2d_type.h"
#include "hi_gfx_comm_k.h"
#include "gfx2d_mem.h"
#include "hi_gfx_sys_k.h"
#include "gfx2d_checkpara.h"

/***************************** Macro Definition **************************************************/
#define GFX2D_PROC           1
#define RegisterMaxTimes     16       /*内存块注册最多次数*/

/*************************** Structure Definition ************************************************/

typedef struct
{
    HI_U32          nSize;                  /*内存块大小*/
    HI_U16          nFree;                  /*空闲内存单元个数*/
    HI_U16          nFirst;                 /* 首个空闲内存单元标识*/
    HI_U32          nUnitSize;              /* 内存单元大小 */
    HI_VOID        *pStartAddr;             /*内存块起始地址*/
    HI_U16          nMaxUsed;               /*最大使用个数*/
    HI_U16          nUnitNum;               /*内存单元总个数*/
    HI_U16          nBeUsed;                /*历史申请次数*/
    spinlock_t      lock;                   /*spinlock标识*/
} MemoryBlock;

/********************** Global Variable declaration **********************************************/

static HI_U32 g_u32MemPoolPhyAddr = 0;        /*内存池物理地址*/
static HI_VOID *g_pMemPoolVrtAddr = HI_NULL;  /*内存池虚拟地址*/
static HI_U32 g_u32MemPoolSize    = 0;        /*内存池大小*/

static HI_U32 g_uRegisterCount = 0;           /*内存块已注册次数*/

static MemoryBlock g_struMemBlock[RegisterMaxTimes] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}\
    , {0}, {0}, {0}, {0}, {0}, {0}
};


/******************************* API forward declarations ****************************************/


/******************************* API realization *************************************************/
void GFX2D_MEM_Lock (spinlock_t *lock, unsigned long *lockflags)
{
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(lock);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(lockflags);
    spin_lock_irqsave(lock, *lockflags);
}

void GFX2D_MEM_Unlock (spinlock_t *lock, unsigned long *lockflags)
{
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(lock);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(lockflags);
    spin_unlock_irqrestore(lock, *lockflags);
}


HI_S32 GFX2D_MEM_Init(const HI_U32 u32Size)
{
    HI_BOOL bMmu = HI_FALSE;

    if (0 == u32Size)
    {
        return HI_FAILURE;
    }

    g_u32MemPoolPhyAddr = HI_GFX_AllocMem("GFX2D_MemPool", NULL, u32Size, &bMmu);
    if (0 == g_u32MemPoolPhyAddr)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "malloc mempool buffer failed!MemPoolSize = 0x%x\n", u32Size);
        return HI_FAILURE;
    }

    g_pMemPoolVrtAddr = HI_GFX_Map(g_u32MemPoolPhyAddr, 0, bMmu);
    if (HI_NULL == g_pMemPoolVrtAddr)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "mempoolphyaddr map failed!\n");
        HI_GFX_FreeMem(g_u32MemPoolPhyAddr, bMmu);
        return HI_FAILURE;
    }

    g_u32MemPoolSize = u32Size;

    return HI_SUCCESS;
}

HI_VOID GFX2D_MEM_Deinit(HI_VOID)
{
    HI_U16 i = 0;

    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (g_struMemBlock[i].nFree != g_struMemBlock[i].nUnitNum)
        {
            HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "some buffer in use\n");
        }
    }

    if (NULL !=  g_pMemPoolVrtAddr)
    {
       HI_GFX_Unmap (g_pMemPoolVrtAddr, HI_FALSE);
    }

    if (0 !=  g_u32MemPoolPhyAddr)
    {
       HI_GFX_FreeMem( g_u32MemPoolPhyAddr, HI_FALSE);
    }

    g_u32MemPoolPhyAddr = 0;
    g_pMemPoolVrtAddr = HI_NULL;
    g_u32MemPoolSize = 0;

    return;
}

HI_S32 GFX2D_MEM_Open(HI_VOID)
{
    return HI_SUCCESS;
}

HI_VOID GFX2D_MEM_Close(HI_VOID)
{
    return;
}

HI_S32 GFX2D_MEM_Register(const HI_U32 u32BlockSize, const HI_U32 u32BlockNum)
{
    HI_U16 i = 0, j = 0;
    HI_U32 u32TotalSize = 0;
    HI_U32 u32Size = 0;
    HI_U8 *pData   = NULL;
    MemoryBlock TempMemBlock = {0};
    HI_U32 u32MemSize = u32BlockSize * u32BlockNum;

    if (  ((HI_U64)u32BlockSize * u32BlockNum > 0xffffffffU)
        ||((HI_U64)u32BlockSize * u32BlockNum == 0))
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "u32MemSize too large or too small!u32MemSize = %d,u32BlockSize=%d\n", u32MemSize, u32BlockSize);
        return HI_FAILURE;
    }

    if (0 == g_u32MemPoolSize)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "The memory pool is not initial!\n");
        return HI_FAILURE;
    }

    /*内存块大小范围不在内存单元与内存池之间*/
    if (u32MemSize > g_u32MemPoolSize)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "u32MemSize too large or too small!u32MemSize = %d,u32BlockSize=%d\n", u32MemSize, u32BlockSize);
        return HI_FAILURE;
    }

    /*判断注册次数是否超过规定次数*/
    if (g_uRegisterCount >= RegisterMaxTimes)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the times of register is more than the max times \n");
        return HI_FAILURE;
    }

    /*判断是否存在相同内存单元的内存块*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32BlockSize == g_struMemBlock [i].nUnitSize)
        {
            HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "already  register memory block of the same size \n");
            return HI_FAILURE;
        }
    }

    /*判断内存块总大小是否超出内存池大小*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        u32Size += g_struMemBlock[i].nSize;
        u32TotalSize = u32Size + u32MemSize;
        if (u32TotalSize > g_u32MemPoolSize)
        {
            HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the registered memory size is larger than the memory pool size\n");
            return HI_FAILURE;
        }
    }

    /*更新内存管理信息*/
    if (0 == u32BlockSize)
    {
       return HI_FAILURE;
    }

    g_struMemBlock [g_uRegisterCount].nFree      = u32MemSize / u32BlockSize; /*空闲单元个数*/
    g_struMemBlock [g_uRegisterCount].nSize      = u32MemSize;                /*内存块大小*/
    g_struMemBlock [g_uRegisterCount].nFirst     = 0;                         /*初始化首个空闲单元标识*/
    g_struMemBlock [g_uRegisterCount].nUnitSize  = u32BlockSize;              /*内存单元大小*/
    g_struMemBlock [g_uRegisterCount].nUnitNum   = u32BlockNum;               /*内存单元个数*/
    g_struMemBlock [g_uRegisterCount].pStartAddr = (HI_U8 *)(g_pMemPoolVrtAddr + u32Size); /*  内存块起始地址*/

    pData = g_struMemBlock[g_uRegisterCount].pStartAddr;

    spin_lock_init(&(g_struMemBlock [g_uRegisterCount].lock));

    /*初始化每个内存单元的标识*/
    for (i = 1; i < g_struMemBlock [g_uRegisterCount].nUnitNum; i++)
    {
        /* 最后一个unit不做标记，分配到最后一个unit了就说明
           所有的unit都分配光了，因而没有下个可分配unit指示 */
        *(HI_U16 *)pData = i;
        pData += g_struMemBlock[g_uRegisterCount].nUnitSize;

    }

    TempMemBlock = g_struMemBlock[g_uRegisterCount];

    /*将注册的内存块递增排列*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (g_struMemBlock[g_uRegisterCount].nUnitSize < g_struMemBlock[i].nUnitSize)
        {
            for (j = g_uRegisterCount; j > i; j--)
            {
                g_struMemBlock[j] = g_struMemBlock[j - 1];
            }

            g_struMemBlock[j] = TempMemBlock;

        }
    }

    /*注册次数加1*/
    g_uRegisterCount++;

    return HI_SUCCESS;
}

/*注销固定大小的内存块*/
HI_VOID GFX2D_Mem_UnRegister(const HI_U32 u32BlockSize)
{
    HI_U16 i = 0, pos = 0;
    MemoryBlock *pBlock = NULL;

    GFX2D_CHECK_ARRAY_OVER_RETURN_NOVALUE(g_uRegisterCount, RegisterMaxTimes);

    /*找出对应的内存块*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32BlockSize == g_struMemBlock[i].nUnitSize)
        {
            pBlock = &g_struMemBlock[i];
            /*记录数组位置*/
            pos = i;
            break;
        }
    }

    /*没有找到对应的内存块*/
    if (pBlock == NULL)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "There is no such memory block!\n");
        return;
    }

    /*存在未释放的内存*/
    if (g_struMemBlock[i].nFree != g_struMemBlock[i].nUnitNum)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "some memory is not free!\n");
        return;
    }

    /*更新全局内存管理数组信息*/
    for (i = pos; i < g_uRegisterCount - 1; i++)
    {
        g_struMemBlock[i] = g_struMemBlock[i + 1]; /*调整数组位置*/
    }

    HI_GFX_Memset(&g_struMemBlock[i], 0, sizeof(MemoryBlock));

    /*内存块个数-1*/
    g_uRegisterCount--;

    return;
}

/*分配内存*/
HI_VOID *GFX2D_MEM_Alloc(const HI_U32 u32Size)
{
    HI_U16 i = 0;
    unsigned long lockflags = 0;
    HI_U8 *pFree = NULL;
    MemoryBlock *pBlock = NULL;

    /*申请的内存大小为0*/
    if (0 == u32Size)
    {
        /*打印warning信息*/
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the alloc memory size can't be 0!\n");
        return NULL;
    }

    GFX2D_CHECK_ARRAY_OVER_RETURN_VALUE(g_uRegisterCount, RegisterMaxTimes, NULL);
    /*找出申请的内存所在的内存块*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32Size <= g_struMemBlock[i].nUnitSize)
        {
            pBlock = &g_struMemBlock[i];
            break;
        }
    }

    /*没有找到内存块*/
    if (pBlock == NULL)
    {
        /*打印warning信息*/
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the memory block is not registered!\n");
        return NULL;
    }

    /*获取自旋锁*/
    GFX2D_MEM_Lock(&g_struMemBlock[i].lock, &lockflags);

    /*无空闲内存单元*/
    if (!pBlock->nFree)
    {
        GFX2D_MEM_Unlock(&g_struMemBlock[i].lock, &lockflags);
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "There is no free unit !\n");
        return NULL;
    }

    /*由首个空闲单元的标识计算出空闲内存单元地址*/
    pFree = pBlock->pStartAddr + pBlock->nFirst * pBlock->nUnitSize;
    /*修改首个空闲单元的标识*/
    pBlock->nFirst = *(HI_U16 *)pFree;
    /*空闲内存单元数减1*/
    pBlock->nFree--;
    /*内存块申请次数+1*/
    pBlock ->nBeUsed++;
    /*释放自旋锁*/
    GFX2D_MEM_Unlock(&g_struMemBlock[i].lock, &lockflags);

    return pFree;
}

HI_S32 GFX2D_MEM_Unit_Free(HI_U32 i, HI_VOID *pBuf)
{
    MemoryBlock *pBlock = NULL;
    unsigned long lockflags = 0;
    GFX2D_CHECK_ARRAY_OVER_RETURN_VALUE(i, RegisterMaxTimes, HI_FAILURE);
    GFX2D_CHECK_NULLPOINTER_RETURN_VALUE(pBuf, HI_FAILURE);

    pBlock = &g_struMemBlock[i];
    /*获取自旋锁*/
    GFX2D_MEM_Lock(&g_struMemBlock[i].lock, &lockflags);
    /*空闲单元数+1*/
    pBlock->nFree++;
    /*将申请释放的内存单元的标识指向下一个可以分配的单元*/
    *(HI_U16 *) pBuf = pBlock->nFirst;

    /*将申请释放的内存单元作为首个空闲内存单元*/
    GFX2D_CHECK_EQUAL_RETURN_VALUE(0, pBlock->nUnitSize, HI_FAILURE);
    pBlock->nFirst = (pBuf - pBlock->pStartAddr) / pBlock->nUnitSize;
    /*释放自旋锁*/

    pBlock->nMaxUsed++;
    GFX2D_MEM_Unlock(&g_struMemBlock[i].lock, &lockflags);
    return HI_SUCCESS;
}

/*释放内存*/
HI_S32 GFX2D_MEM_Free(HI_VOID *pBuf)
{
    HI_U16 i = 0;
    /*空指针检测*/
    if (NULL == pBuf)
    {
        return HI_FAILURE;
    }

    if ((pBuf < g_pMemPoolVrtAddr) || (pBuf >= (g_pMemPoolVrtAddr + g_u32MemPoolSize)))
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the addr is out of the range of the memory pool !\n");
        return HI_FAILURE;
    }

    /*由地址计算出对应的内存块*/
    GFX2D_CHECK_ARRAY_OVER_RETURN_VALUE(g_uRegisterCount, RegisterMaxTimes, HI_FAILURE);
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if ((pBuf < g_struMemBlock[i].pStartAddr) || (pBuf >= (g_struMemBlock[i].pStartAddr + g_struMemBlock[i].nSize)))
        {
            continue;
        }

        if (HI_SUCCESS == GFX2D_MEM_Unit_Free(i, pBuf))
        {
            return HI_SUCCESS;
        }
    }

    HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the addr is not the right addr of memory !\n");

    return HI_FAILURE;

}

/*获取内存物理地址*/
HI_U32 GFX2D_MEM_GetPhyaddr(HI_VOID *pBuf)
{
    /*地址不在内存池范围内*/
    if ((NULL == pBuf) || (pBuf < g_pMemPoolVrtAddr) || (pBuf >= (g_pMemPoolVrtAddr + g_u32MemPoolSize)))
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the addr is out of the range of the memory pool ! 0x%x, %d\n", g_pMemPoolVrtAddr, g_u32MemPoolSize);
        return 0;
    }
    /*返回pBuf  对应的物理地址*/
    return (g_u32MemPoolPhyAddr + (pBuf - g_pMemPoolVrtAddr));
}

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_MEM_ReadProc(struct seq_file *p, HI_VOID *v)
{
    HI_U16 i = 0;
    HI_UNUSED(v);
    GFX2D_CHECK_NULLPOINTER_RETURN_NOVALUE(p);

    SEQ_Printf(p, "--------- Hisilicon TDE Memory Pool Info ---------\n");
    SEQ_Printf(p, "     MemPoolSize   MemBlockNum       \n");
    SEQ_Printf(p, " %8u   %8u\n", g_u32MemPoolSize, g_uRegisterCount);
    SEQ_Printf(p, " BlockSize   UnitSize   UnitNum    UnitFreeNum    FirstFreePos    AllocTimes    MaxUsed       \n");

    GFX2D_CHECK_ARRAY_OVER_RETURN_NOVALUE(g_uRegisterCount, RegisterMaxTimes);
    for (i = 0; i < g_uRegisterCount; i++)
    {
        SEQ_Printf(p, "%8u   %8u  %8u   %8u       %8u        %8u      %8u\n",
                      g_struMemBlock[i].nSize,
                      g_struMemBlock[i].nUnitSize,
                      g_struMemBlock[i].nUnitNum,
                      g_struMemBlock[i].nFree,
                      g_struMemBlock[i].nFirst,
                      g_struMemBlock[i].nBeUsed,
                      g_struMemBlock[i].nMaxUsed);
    }

    return;
}

HI_VOID GFX2D_MEM_WriteProc(struct file *file, const char __user *buf, \
                           size_t count, loff_t *ppos)
{
    HI_UNUSED(file);
    HI_UNUSED(buf);
    HI_UNUSED(ppos);
    return;
}
#endif
