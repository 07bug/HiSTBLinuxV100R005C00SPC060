

/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : aio_cb.h
  Version       : Initial Draft
  Author        : Hisilicon tv software group
  Created       : 2011/09/28
  Description   :
  History       :
  1.Date        : 2011/09/28
    Modification: Created file(modify other's core(simple_cb.h))
******************************************************************************/
#ifndef __CIRC_BUF_H__
#define __CIRC_BUF_H__

#ifndef HI_AIAO_CBB
#include <asm/uaccess.h>
#endif

#include <linux/string.h>

#include "hi_type.h"
#include "hi_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define SIMPLE_CB_GAP 32

typedef struct hiCIRC_BUF_S
{
    volatile HI_U32      *pu32Write;  //��Ŷ�ָ��ƫ������ַ
    volatile HI_U32      *pu32Read;   //���дָ��ƫ������ַ
    volatile HI_U8       *pu8Data;   //DDR������ʼ��ַ(�����ַ)
    HI_U32               u32Lenght;   //ѭ��buffer����
} CIRC_BUF_S;

static inline HI_VOID CIRC_BUF_Init(CIRC_BUF_S *pstCb,
                        HI_VOID *pu32Write,
                        HI_VOID *pu32Read,
                        HI_VOID *pu8Data,
                        HI_U32  u32Len)
{
    pstCb->pu32Write  = pu32Write;
    pstCb->pu32Read   = pu32Read;
    pstCb->pu8Data    = pu8Data;
    pstCb->u32Lenght  = u32Len;

    *pstCb->pu32Write     = 0;
    *pstCb->pu32Read      = 0;

}

static inline HI_VOID CIRC_BUF_DeInit(CIRC_BUF_S *pstCb)
{
    return;
}

static inline HI_U32 CIRC_BUF_QueryBusy_ProvideRptr(CIRC_BUF_S *pstCb, HI_U32 *pu32Rptr)
{
    HI_U32  u32ReadPos, u32WritePos, u32BusyLen=0;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);         //ȡ���Ĵ�����ַ���������
    u32WritePos = *(pstCb->pu32Write);

    u32ReadPos = *pu32Rptr;

    if (u32WritePos >= u32ReadPos)
    {
        u32BusyLen = u32WritePos - u32ReadPos;
    }
    else
    {
        u32BusyLen = pstCb->u32Lenght - (u32ReadPos - u32WritePos);
    }

    return u32BusyLen;
}

static inline HI_U32 CIRC_BUF_QueryBusy(CIRC_BUF_S *pstCb)
{
    HI_U32  u32ReadPos, u32WritePos, u32BusyLen=0;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);         //ȡ���Ĵ�����ַ���������
    u32WritePos = *(pstCb->pu32Write);

    if (u32WritePos >= u32ReadPos)
    {
        u32BusyLen = u32WritePos - u32ReadPos;
    }
    else
    {
        u32BusyLen = pstCb->u32Lenght - (u32ReadPos - u32WritePos);
    }

    return u32BusyLen;
}

static inline HI_U32 CIRC_BUF_QueryFree(CIRC_BUF_S *pstCb)
{
    HI_U32  u32ReadPos, u32WritePos, u32FreeLen=0;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    if (u32WritePos >= u32ReadPos)
    {
        u32FreeLen = (pstCb->u32Lenght - (u32WritePos - u32ReadPos));
    }
    else
    {
        u32FreeLen = (u32ReadPos - u32WritePos);
    }

    u32FreeLen = (u32FreeLen <= SIMPLE_CB_GAP) ? 0 : u32FreeLen - SIMPLE_CB_GAP;
    /* ѭ��Buffer����д���������������ΪBufferΪ�� */
    if(u32FreeLen>0)
        u32FreeLen -= 1;
    return u32FreeLen;
}

static inline HI_U32 CIRC_BUF_QueryReadPos(CIRC_BUF_S *pstCb)
{
    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    return *(pstCb->pu32Read);
}

/*****************************************************************************
 Prototype       : CIRC_BUF_Read_NotUpRptr
 Description     : �ӹ���CB�ж�ȡָ�����ȵ�����
 Input           : pstCb     ** CB�Ĺ���ṹ
                   pu32DataOffset   ** ��ȡ���ݵ�ƫ��
                   u32Len  ** ϣ����ȡ�����ݳ���
 Output          : None
 Return Value    : ���سɹ���ȡ�������ݳ���
*****************************************************************************/

static inline HI_U32 CIRC_BUF_Read_NotUpRptr(CIRC_BUF_S *pstCb, HI_U8 *pDest, HI_U32 u32Len, HI_U32 *pu32Rptr, HI_U32 *pu32Wptr)
{
    HI_U8  *pVirAddr   = NULL;
    HI_U32  u32RdLen[2]={0,0}, u32RdPos[2]={0,0}, i;
    HI_U32  u32ReadPos, u32WritePos;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);
    //HI_ASSERT(NULL != pDest);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pu32Rptr);
    u32WritePos = *(pstCb->pu32Write);

    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            /* ���ʣ�����ݽ϶࣬��ֻ��ȡһ���� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* ���ʣ�����ݲ��㣬��ȫ������ */
            u32RdLen[0] = u32WritePos - u32ReadPos;
        }
    }
    else
    {
        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            /* �������Ҫ�۷�����ֱ�Ӷ�ȡ��������� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* �����Ҫ�۷������ȶ�ȡβ�������� */
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;

            /* �����۷���ͷ����ȡʣ��Ĳ������� */
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                /* ���ʣ�����ݲ��㣬���ȡȫ������ */
                u32RdLen[1] = u32WritePos;
            }
        }
    }

    for (i=0; ( i < 2 ) && (u32RdLen[i] != 0); i++)
    {
        pVirAddr = (HI_U8*)(pstCb->pu8Data + u32RdPos[i]);

        memcpy(pDest, pVirAddr, u32RdLen[i]);

        pDest += u32RdLen[i];

        u32ReadPos = u32RdPos[i] + u32RdLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32ReadPos == pstCb->u32Lenght) u32ReadPos = 0;

    //not update Rptr
    //*(pstCb->pu32Read) = u32ReadPos;

    *pu32Wptr= u32WritePos;
    *pu32Rptr = u32ReadPos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32RdLen[0] + u32RdLen[1];
}

/*****************************************************************************
 Prototype       : CIRC_BUF_Read
 Description     : �ӹ���CB�ж�ȡָ�����ȵ�����
 Input           : pstCb     ** CB�Ĺ���ṹ
                   pDest   ** �û��ռ������ڴ�������ַ(�ļ�)
                   u32Len  ** ϣ����ȡ�����ݳ���
 Output          : None
 Return Value    : ���سɹ���ȡ�������ݳ���
*****************************************************************************/
static inline HI_U32 CIRC_BUF_Read(CIRC_BUF_S *pstCb, HI_U8 *pDest, HI_U32 u32Len)
{
    HI_U8  *pVirAddr   = NULL;
    HI_U32  u32RdLen[2]={0,0}, u32RdPos[2]={0,0}, i;
    HI_U32  u32ReadPos, u32WritePos;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);
    //HI_ASSERT(NULL != pDest);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            /* ���ʣ�����ݽ϶࣬��ֻ��ȡһ���� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* ���ʣ�����ݲ��㣬��ȫ������ */
            u32RdLen[0] = u32WritePos - u32ReadPos;
        }
    }
    else
    {
        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            /* �������Ҫ�۷�����ֱ�Ӷ�ȡ��������� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* �����Ҫ�۷������ȶ�ȡβ�������� */
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;

            /* �����۷���ͷ����ȡʣ��Ĳ������� */
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                /* ���ʣ�����ݲ��㣬���ȡȫ������ */
                u32RdLen[1] = u32WritePos;
            }
        }
    }

    for (i=0; ( i < 2 ) && (u32RdLen[i] != 0); i++)
    {
        pVirAddr = (HI_U8*)(pstCb->pu8Data + u32RdPos[i]);

        memcpy(pDest, pVirAddr, u32RdLen[i]);

        pDest += u32RdLen[i];

        u32ReadPos = u32RdPos[i] + u32RdLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32ReadPos == pstCb->u32Lenght) u32ReadPos = 0;

    *(pstCb->pu32Read) = u32ReadPos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32RdLen[0] + u32RdLen[1];
}

/*****************************************************************************
 Prototype       : CIRC_BUF_CastRead
 Description     : �ӹ���CB�ж�ȡָ�����ȵ�����
 Input           : pstCb     ** CB�Ĺ���ṹ
                   pu32DataOffset   ** ��ȡ���ݵ�ƫ��
                   u32Len  ** ϣ����ȡ�����ݳ���
 Output          : None
 Return Value    : ���سɹ���ȡ�������ݳ���
*****************************************************************************/
static inline HI_U32 CIRC_BUF_CastRead(CIRC_BUF_S *pstCb, HI_U32 *pu32DataOffset, HI_U32 u32Len)
{
    HI_U32  u32RdLen[2]={0,0}, u32RdPos[2]={0,0};
    HI_U32  u32ReadPos, u32WritePos;

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            /* ���ʣ�����ݽ϶࣬��ֻ��ȡһ���� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            *pu32DataOffset = 0;
            return  0;
        }
    }
    else
    {
        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            /* �������Ҫ�۷�����ֱ�Ӷ�ȡ��������� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* �����Ҫ�۷������ȶ�ȡβ�������� */
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;

            /* �����۷���ͷ����ȡʣ��Ĳ������� */
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                /* ���ʣ�����ݲ��㣬���ȡȫ������ */
                *pu32DataOffset = 0;
                return 0;
            }
        }
    }

    *pu32DataOffset = u32RdPos[0];
    return u32RdLen[0] + u32RdLen[1];
}

/*****************************************************************************
 Prototype       : CIRC_BUF_CastRelese
 Description     : �ӹ���CB���ͷ�ָ�����ȵ�����
 Input           : pstCb     ** CB�Ĺ���ṹ
                   u32Len  ** ϣ���ͷŵ����ݳ���
 Output          : None
 Return Value    : ���سɹ��ͷŵ������ݳ���
*****************************************************************************/
static inline HI_U32 CIRC_BUF_CastRelese(CIRC_BUF_S *pstCb, HI_U32 u32Len)
{
    HI_U32  u32RdLen[2]={0,0}, u32RdPos[2]={0,0}, i;
    HI_U32  u32ReadPos, u32WritePos;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);
    //HI_ASSERT(NULL != pDest);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);
    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            /* ���ʣ�����ݽ϶࣬��ֻ��ȡһ���� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* ���ʣ�����ݲ��㣬��ȫ������ */
            u32RdLen[0] = u32WritePos - u32ReadPos;
        }
    }
    else
    {

        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            /* �������Ҫ�۷�����ֱ�Ӷ�ȡ��������� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* �����Ҫ�۷������ȶ�ȡβ�������� */
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;
            /* �����۷���ͷ����ȡʣ��Ĳ������� */
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                /* ���ʣ�����ݲ��㣬���ȡȫ������ */
                u32RdLen[1] = u32WritePos;
            }
        }
    }

    for (i=0; ( i < 2 ) && (u32RdLen[i] != 0); i++)
    {
        //pVirAddr = (HI_U8*)(pstCb->pu8Data + u32RdPos[i]);
        //memcpy(pDest, pVirAddr, u32RdLen[i]);
        //pDest += u32RdLen[i];
        u32ReadPos = u32RdPos[i] + u32RdLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32ReadPos == pstCb->u32Lenght) u32ReadPos = 0;

    *(pstCb->pu32Read) = u32ReadPos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32RdLen[0] + u32RdLen[1];
}

static inline HI_U32 CIRC_BUF_Write(CIRC_BUF_S *pstCb, HI_U8 *pDest, HI_U32 u32Len, HI_BOOL bDataFromKernel)
{
    HI_U32* pVirAddr = HI_NULL;

    HI_U32  u32WtLen[2]={0,0};
    HI_U32  u32WtPos[2]={0,0};
    HI_U32  i;
    HI_U32  u32ReadPos, u32WritePos;

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    u32WtPos[0] = u32WritePos;
    if (u32WritePos >= u32ReadPos)
    {
        if (pstCb->u32Lenght >= (u32WritePos + u32Len))
        {
            u32WtLen[0] = u32Len;
        }
        else
        {
            u32WtLen[0] = pstCb->u32Lenght - u32WritePos;
            u32WtLen[1] = u32Len - u32WtLen[0];

            u32WtPos[1] = 0;
        }
    }
    else
    {
        u32WtLen[0] = u32Len;
    }

    for (i = 0; ( i < 2 ) && (u32WtLen[i] != 0); i++)
    {
        pVirAddr = (HI_U32*)((HI_VOID*)pstCb->pu8Data + u32WtPos[i]);
        if (pDest)
        {
            if (HI_FALSE == bDataFromKernel)
            {

#ifndef HI_AIAO_CBB
                if (copy_from_user(pVirAddr, pDest, u32WtLen[i]))
                {
                    return 0;
                }
                else
#else
                memcpy(pVirAddr, pDest, u32WtLen[i]);
#endif
                {
                    pDest = pDest + u32WtLen[i];
                }
            }
            else
            {
                memcpy(pVirAddr, pDest, u32WtLen[i]);
                pDest = pDest+ u32WtLen[i];
            }
        }
        else //only passthrouth send 0
        {
            memset(pVirAddr, 0, u32WtLen[i]);
        }
        u32WritePos = u32WtPos[i] + u32WtLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32WritePos == pstCb->u32Lenght) u32WritePos = 0;
    *(pstCb->pu32Write) = u32WritePos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32WtLen[0] + u32WtLen[1];
}

static inline HI_VOID CIRC_BUF_Flush(CIRC_BUF_S *pstCb)
{
    *pstCb->pu32Write     = 0;
    *pstCb->pu32Read      = 0;
}


static inline HI_U32 CIRC_BUF_UpdateRptr(CIRC_BUF_S *pstCb, HI_U8 *pDest, HI_U32 u32Len)
{
    HI_U32  u32RdLen[2]={0,0}, u32RdPos[2]={0,0}, i;
    HI_U32  u32ReadPos, u32WritePos;


    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            /* ���ʣ�����ݽ϶࣬��ֻ��ȡһ���� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* ���ʣ�����ݲ��㣬��ȫ������ */
            u32RdLen[0] = u32WritePos - u32ReadPos;
        }
    }
    else
    {
        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            /* �������Ҫ�۷�����ֱ�Ӷ�ȡ��������� */
            u32RdLen[0] = u32Len;
        }
        else
        {
            /* �����Ҫ�۷������ȶ�ȡβ�������� */
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;

            /* �����۷���ͷ����ȡʣ��Ĳ������� */
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                /* ���ʣ�����ݲ��㣬���ȡȫ������ */
                u32RdLen[1] = u32WritePos;
            }
        }
    }

    for (i=0; ( i < 2 ) && (u32RdLen[i] != 0); i++)
    {
        u32ReadPos = u32RdPos[i] + u32RdLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32ReadPos == pstCb->u32Lenght) u32ReadPos = 0;

    *(pstCb->pu32Read) = u32ReadPos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32RdLen[0] + u32RdLen[1];
}

static inline HI_U32 CIRC_BUF_UpdateWptr(CIRC_BUF_S *pstCb, HI_U8 *pDest, HI_U32 u32Len)
{
    HI_U32  u32WtLen[2]={0,0};
    HI_U32  u32WtPos[2]={0,0};
    HI_U32  i;
    HI_U32  u32ReadPos, u32WritePos;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    u32WtPos[0] = u32WritePos;
    if (u32WritePos >= u32ReadPos)
    {
        if (pstCb->u32Lenght >= (u32WritePos + u32Len))
        {
            u32WtLen[0] = u32Len;
        }
        else
        {
            u32WtLen[0] = pstCb->u32Lenght - u32WritePos;
            u32WtLen[1] = u32Len - u32WtLen[0];

            u32WtPos[1] = 0;
        }
    }
    else
    {
        u32WtLen[0] = u32Len;
    }

    for (i=0; ( i < 2 ) && (u32WtLen[i] != 0); i++)
    {
        u32WritePos = u32WtPos[i] + u32WtLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32WritePos == pstCb->u32Lenght) u32WritePos = 0;
    *(pstCb->pu32Write) = u32WritePos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32WtLen[0] + u32WtLen[1];
}


static inline HI_U32 CIRC_BUF_ALSA_UpdateWptr(CIRC_BUF_S *pstCb, HI_U32 u32Len)
{
    HI_U32  u32WtLen[2]={0,0};
#if 0
    HI_U32  u32WtPos[2]={0,0};
    HI_U32  i;
#endif
    HI_U32  u32WritePos;

    //TODO++++++++++++++
    //HI_ASSERT(NULL != pstCb);

    /* �ȴӹ����ڴ���ȡ��ͷ��Ϣ������ʹ�ù����з����仯 */
    u32WritePos = *(pstCb->pu32Write);
 #if 1
    u32WritePos += u32Len;

    if (u32WritePos > pstCb->u32Lenght)
        u32WritePos -= pstCb->u32Lenght;
#else

    u32WtPos[0] = u32WritePos;
    if (u32WritePos >= u32ReadPos)
    {
        if (pstCb->u32Lenght >= (u32WritePos + u32Len))
        {
            u32WtLen[0] = u32Len;
        }
        else
        {
            u32WtLen[0] = pstCb->u32Lenght - u32WritePos;
            u32WtLen[1] = u32Len - u32WtLen[0];

            u32WtPos[1] = 0;
        }
    }
    else
    {
        u32WtLen[0] = u32Len;
    }

    for (i=0; ( i < 2 ) && (u32WtLen[i] != 0); i++)
    {
        u32WritePos = u32WtPos[i] + u32WtLen[i];
    }

    /* ����ָ��д��Bufferͷ */
    if (u32WritePos == pstCb->u32Lenght) u32WritePos = 0;
#endif
    *(pstCb->pu32Write) = u32WritePos;

    /* ����ʵ�ʶ�ȡ�ĳ��� */
    return u32WtLen[0] + u32WtLen[1];
}

//ͨ���ƶ���ָ�룬��aip Buffer��ǰ����Ӿ���֡��
//ʣ��ռ�С����Ҫ��Ӿ���֡ʱ����������
static inline HI_U32 CIRC_BUF_ChangeRptr(CIRC_BUF_S *pstCb, HI_U32 u32Len)
{
    HI_U32  u32ReadPos, u32WritePos;
    HI_U32  u32BufferFree;

    u32ReadPos  = *(pstCb->pu32Read);
    u32WritePos = *(pstCb->pu32Write);

    if (u32WritePos >= u32ReadPos)
    {
        if (u32ReadPos >=  u32Len)
        {
           u32ReadPos = u32ReadPos - u32Len;
           memset((HI_U8*)(pstCb->pu8Data + u32ReadPos), 0, u32Len);
        }
        else
        {
            u32BufferFree = (pstCb->u32Lenght - u32WritePos) + u32ReadPos;
            if(u32BufferFree >= u32Len)
            {
                memset((HI_U8*)pstCb->pu8Data, 0, u32ReadPos);

                u32ReadPos = pstCb->u32Lenght + u32ReadPos - u32Len;
                memset((HI_U8*)(pstCb->pu8Data + u32ReadPos), 0, pstCb->u32Lenght - u32ReadPos);
            }
        }
    }
    else
    {
        u32BufferFree = u32ReadPos - u32WritePos;
        if(u32BufferFree > u32Len)
        {
            u32ReadPos = u32ReadPos - u32Len;
            memset((HI_U8*)(pstCb->pu8Data + u32ReadPos), 0, u32Len);
        }
    }

    if (u32ReadPos >= pstCb->u32Lenght)
    {
        u32ReadPos = 0;
    }

    *(pstCb->pu32Read) = u32ReadPos;
    return HI_TRUE;
}

static inline HI_U32 CIRC_BUF_ALSA_UpdateRptr(CIRC_BUF_S *pstCb, HI_U32 u32Len)
{
    HI_U32  u32ReadPos;
    u32ReadPos  = *(pstCb->pu32Read);
#if 1
    u32ReadPos += u32Len;
    if (u32ReadPos > pstCb->u32Lenght)
        u32ReadPos -= pstCb->u32Lenght;
#else
    u32RdPos[0] = u32ReadPos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32WritePos >= u32ReadPos + u32Len)
        {
            u32RdLen[0] = u32Len;
        }
        else
        {
            u32RdLen[0] = u32WritePos - u32ReadPos;
        }
    }
    else
    {
        if ( u32ReadPos + u32Len <= pstCb->u32Lenght)
        {
            u32RdLen[0] = u32Len;
        }
        else
        {
            u32RdLen[0] = pstCb->u32Lenght - u32ReadPos;
            u32RdPos[1] = 0;
            u32RdLen[1] = u32Len - u32RdLen[0];
            if(u32WritePos < u32RdLen[1])
            {
                u32RdLen[1] = u32WritePos;
            }
        }
    }
    for (i=0; ( i < 2 ) && (u32RdLen[i] != 0); i++)
    {
        u32ReadPos = u32RdPos[i] + u32RdLen[i];
    }
    if (u32ReadPos == pstCb->u32Lenght) u32ReadPos = 0;
   #endif
    *(pstCb->pu32Read) = u32ReadPos;
    return HI_TRUE;
}

#ifdef HI_ALSA_AI_SUPPORT
static inline HI_VOID CIRC_BUF_ALSA_Flush(CIRC_BUF_S *pstCb)
{
    *pstCb->pu32Write     = 0;
    *pstCb->pu32Read      = 0;
}

static inline HI_U32 CIRC_BUF_ALSA_QueryWritePos(CIRC_BUF_S *pstCb)
{
    return *(pstCb->pu32Write);
}

static inline HI_U32 CIRC_BUF_ALSA_QueryReadPos(CIRC_BUF_S *pstCb)
{
    return *(pstCb->pu32Read);
}

#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
#endif /* End of #ifndef __SIMPLE_CB_H__*/
