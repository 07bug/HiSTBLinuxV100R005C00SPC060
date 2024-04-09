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
#define RegisterMaxTimes     16       /*�ڴ��ע��������*/

/*************************** Structure Definition ************************************************/

typedef struct
{
    HI_U32          nSize;                  /*�ڴ���С*/
    HI_U16          nFree;                  /*�����ڴ浥Ԫ����*/
    HI_U16          nFirst;                 /* �׸������ڴ浥Ԫ��ʶ*/
    HI_U32          nUnitSize;              /* �ڴ浥Ԫ��С */
    HI_VOID        *pStartAddr;             /*�ڴ����ʼ��ַ*/
    HI_U16          nMaxUsed;               /*���ʹ�ø���*/
    HI_U16          nUnitNum;               /*�ڴ浥Ԫ�ܸ���*/
    HI_U16          nBeUsed;                /*��ʷ�������*/
    spinlock_t      lock;                   /*spinlock��ʶ*/
} MemoryBlock;

/********************** Global Variable declaration **********************************************/

static HI_U32 g_u32MemPoolPhyAddr = 0;        /*�ڴ�������ַ*/
static HI_VOID *g_pMemPoolVrtAddr = HI_NULL;  /*�ڴ�������ַ*/
static HI_U32 g_u32MemPoolSize    = 0;        /*�ڴ�ش�С*/

static HI_U32 g_uRegisterCount = 0;           /*�ڴ����ע�����*/

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

    /*�ڴ���С��Χ�����ڴ浥Ԫ���ڴ��֮��*/
    if (u32MemSize > g_u32MemPoolSize)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "u32MemSize too large or too small!u32MemSize = %d,u32BlockSize=%d\n", u32MemSize, u32BlockSize);
        return HI_FAILURE;
    }

    /*�ж�ע������Ƿ񳬹��涨����*/
    if (g_uRegisterCount >= RegisterMaxTimes)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the times of register is more than the max times \n");
        return HI_FAILURE;
    }

    /*�ж��Ƿ������ͬ�ڴ浥Ԫ���ڴ��*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32BlockSize == g_struMemBlock [i].nUnitSize)
        {
            HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "already  register memory block of the same size \n");
            return HI_FAILURE;
        }
    }

    /*�ж��ڴ���ܴ�С�Ƿ񳬳��ڴ�ش�С*/
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

    /*�����ڴ������Ϣ*/
    if (0 == u32BlockSize)
    {
       return HI_FAILURE;
    }

    g_struMemBlock [g_uRegisterCount].nFree      = u32MemSize / u32BlockSize; /*���е�Ԫ����*/
    g_struMemBlock [g_uRegisterCount].nSize      = u32MemSize;                /*�ڴ���С*/
    g_struMemBlock [g_uRegisterCount].nFirst     = 0;                         /*��ʼ���׸����е�Ԫ��ʶ*/
    g_struMemBlock [g_uRegisterCount].nUnitSize  = u32BlockSize;              /*�ڴ浥Ԫ��С*/
    g_struMemBlock [g_uRegisterCount].nUnitNum   = u32BlockNum;               /*�ڴ浥Ԫ����*/
    g_struMemBlock [g_uRegisterCount].pStartAddr = (HI_U8 *)(g_pMemPoolVrtAddr + u32Size); /*  �ڴ����ʼ��ַ*/

    pData = g_struMemBlock[g_uRegisterCount].pStartAddr;

    spin_lock_init(&(g_struMemBlock [g_uRegisterCount].lock));

    /*��ʼ��ÿ���ڴ浥Ԫ�ı�ʶ*/
    for (i = 1; i < g_struMemBlock [g_uRegisterCount].nUnitNum; i++)
    {
        /* ���һ��unit������ǣ����䵽���һ��unit�˾�˵��
           ���е�unit��������ˣ����û���¸��ɷ���unitָʾ */
        *(HI_U16 *)pData = i;
        pData += g_struMemBlock[g_uRegisterCount].nUnitSize;

    }

    TempMemBlock = g_struMemBlock[g_uRegisterCount];

    /*��ע����ڴ���������*/
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

    /*ע�������1*/
    g_uRegisterCount++;

    return HI_SUCCESS;
}

/*ע���̶���С���ڴ��*/
HI_VOID GFX2D_Mem_UnRegister(const HI_U32 u32BlockSize)
{
    HI_U16 i = 0, pos = 0;
    MemoryBlock *pBlock = NULL;

    GFX2D_CHECK_ARRAY_OVER_RETURN_NOVALUE(g_uRegisterCount, RegisterMaxTimes);

    /*�ҳ���Ӧ���ڴ��*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32BlockSize == g_struMemBlock[i].nUnitSize)
        {
            pBlock = &g_struMemBlock[i];
            /*��¼����λ��*/
            pos = i;
            break;
        }
    }

    /*û���ҵ���Ӧ���ڴ��*/
    if (pBlock == NULL)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "There is no such memory block!\n");
        return;
    }

    /*����δ�ͷŵ��ڴ�*/
    if (g_struMemBlock[i].nFree != g_struMemBlock[i].nUnitNum)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "some memory is not free!\n");
        return;
    }

    /*����ȫ���ڴ����������Ϣ*/
    for (i = pos; i < g_uRegisterCount - 1; i++)
    {
        g_struMemBlock[i] = g_struMemBlock[i + 1]; /*��������λ��*/
    }

    HI_GFX_Memset(&g_struMemBlock[i], 0, sizeof(MemoryBlock));

    /*�ڴ�����-1*/
    g_uRegisterCount--;

    return;
}

/*�����ڴ�*/
HI_VOID *GFX2D_MEM_Alloc(const HI_U32 u32Size)
{
    HI_U16 i = 0;
    unsigned long lockflags = 0;
    HI_U8 *pFree = NULL;
    MemoryBlock *pBlock = NULL;

    /*������ڴ��СΪ0*/
    if (0 == u32Size)
    {
        /*��ӡwarning��Ϣ*/
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the alloc memory size can't be 0!\n");
        return NULL;
    }

    GFX2D_CHECK_ARRAY_OVER_RETURN_VALUE(g_uRegisterCount, RegisterMaxTimes, NULL);
    /*�ҳ�������ڴ����ڵ��ڴ��*/
    for (i = 0; i < g_uRegisterCount; i++)
    {
        if (u32Size <= g_struMemBlock[i].nUnitSize)
        {
            pBlock = &g_struMemBlock[i];
            break;
        }
    }

    /*û���ҵ��ڴ��*/
    if (pBlock == NULL)
    {
        /*��ӡwarning��Ϣ*/
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the memory block is not registered!\n");
        return NULL;
    }

    /*��ȡ������*/
    GFX2D_MEM_Lock(&g_struMemBlock[i].lock, &lockflags);

    /*�޿����ڴ浥Ԫ*/
    if (!pBlock->nFree)
    {
        GFX2D_MEM_Unlock(&g_struMemBlock[i].lock, &lockflags);
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "There is no free unit !\n");
        return NULL;
    }

    /*���׸����е�Ԫ�ı�ʶ����������ڴ浥Ԫ��ַ*/
    pFree = pBlock->pStartAddr + pBlock->nFirst * pBlock->nUnitSize;
    /*�޸��׸����е�Ԫ�ı�ʶ*/
    pBlock->nFirst = *(HI_U16 *)pFree;
    /*�����ڴ浥Ԫ����1*/
    pBlock->nFree--;
    /*�ڴ���������+1*/
    pBlock ->nBeUsed++;
    /*�ͷ�������*/
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
    /*��ȡ������*/
    GFX2D_MEM_Lock(&g_struMemBlock[i].lock, &lockflags);
    /*���е�Ԫ��+1*/
    pBlock->nFree++;
    /*�������ͷŵ��ڴ浥Ԫ�ı�ʶָ����һ�����Է���ĵ�Ԫ*/
    *(HI_U16 *) pBuf = pBlock->nFirst;

    /*�������ͷŵ��ڴ浥Ԫ��Ϊ�׸������ڴ浥Ԫ*/
    GFX2D_CHECK_EQUAL_RETURN_VALUE(0, pBlock->nUnitSize, HI_FAILURE);
    pBlock->nFirst = (pBuf - pBlock->pStartAddr) / pBlock->nUnitSize;
    /*�ͷ�������*/

    pBlock->nMaxUsed++;
    GFX2D_MEM_Unlock(&g_struMemBlock[i].lock, &lockflags);
    return HI_SUCCESS;
}

/*�ͷ��ڴ�*/
HI_S32 GFX2D_MEM_Free(HI_VOID *pBuf)
{
    HI_U16 i = 0;
    /*��ָ����*/
    if (NULL == pBuf)
    {
        return HI_FAILURE;
    }

    if ((pBuf < g_pMemPoolVrtAddr) || (pBuf >= (g_pMemPoolVrtAddr + g_u32MemPoolSize)))
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the addr is out of the range of the memory pool !\n");
        return HI_FAILURE;
    }

    /*�ɵ�ַ�������Ӧ���ڴ��*/
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

/*��ȡ�ڴ������ַ*/
HI_U32 GFX2D_MEM_GetPhyaddr(HI_VOID *pBuf)
{
    /*��ַ�����ڴ�ط�Χ��*/
    if ((NULL == pBuf) || (pBuf < g_pMemPoolVrtAddr) || (pBuf >= (g_pMemPoolVrtAddr + g_u32MemPoolSize)))
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "the addr is out of the range of the memory pool ! 0x%x, %d\n", g_pMemPoolVrtAddr, g_u32MemPoolSize);
        return 0;
    }
    /*����pBuf  ��Ӧ�������ַ*/
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
