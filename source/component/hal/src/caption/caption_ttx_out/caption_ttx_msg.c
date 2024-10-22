#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "caption_ttx_msg.h"

#define MIN_GAP (64) /* 64 Bytes*/

static MSG_QUEUE_S s_stMsgQueue = {0};

static HI_S32 IsEmptyQueue(MSG_QUEUE_S* pstMsgQueue)
{
    if (pstMsgQueue->pstMsgRear == pstMsgQueue->pstMsgFront)
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_S32 IsFullQueue(MSG_QUEUE_S* pstMsgQueue)
{
    HI_U32 u32Step = sizeof(MESSAGE_S) + pstMsgQueue->pstMsgRear->u16MsgLength;

    HI_U32 u32RemainSpace = 0;

    if (pstMsgQueue->pstMsgRear >= pstMsgQueue->pstMsgFront)
    {
        u32RemainSpace = (pstMsgQueue->pu8BaseAddr + pstMsgQueue->u32MaxLen) - (HI_U8*)pstMsgQueue->pstMsgRear;

        if ((HI_U8*)pstMsgQueue->pstMsgFront > pstMsgQueue->pu8BaseAddr)
        {
            u32RemainSpace += ((HI_U8*)pstMsgQueue->pstMsgFront - MIN_GAP - pstMsgQueue->pu8BaseAddr);
        }
        else
        {
            u32RemainSpace -= MIN_GAP;
        }
    }
    else
    {
        u32RemainSpace = (HI_U8*)pstMsgQueue->pstMsgFront - MIN_GAP - (HI_U8*)pstMsgQueue->pstMsgRear;
    }

    if (u32Step > u32RemainSpace)
    {
        /* Queue  full*/
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 MsgQueue_Init(HI_VOID)
{
    HI_U8* pszBufAddr = HI_NULL;
    HI_U32 u32BufLen = 1024;

    pszBufAddr = (HI_U8*) malloc(u32BufLen * sizeof(HI_U8));

    if (pszBufAddr == HI_NULL)
    {
        return HI_FAILURE;
    }

    if (0 != pthread_mutex_init(&s_stMsgQueue.Queue_lock, NULL))
    {}

    s_stMsgQueue.pu8BaseAddr = pszBufAddr;
    s_stMsgQueue.u32MaxLen = u32BufLen;

    s_stMsgQueue.pstMsgFront = (MESSAGE_S*)pszBufAddr;
    s_stMsgQueue.pstMsgFront->pu8MsgData = HI_NULL;
    s_stMsgQueue.pstMsgFront->pstNext = HI_NULL;

    s_stMsgQueue.pstMsgRear = (MESSAGE_S*)pszBufAddr;
    s_stMsgQueue.pstMsgRear->pu8MsgData = HI_NULL;
    s_stMsgQueue.pstMsgRear->pstNext = HI_NULL;

    return HI_SUCCESS;
}

HI_S32  MsgQueue_DeInit(HI_VOID)
{
    if (0 != pthread_mutex_destroy(&(s_stMsgQueue.Queue_lock)))
    {}

    if (s_stMsgQueue.pu8BaseAddr != HI_NULL)
    {
        free(s_stMsgQueue.pu8BaseAddr);
    }

    s_stMsgQueue.pu8BaseAddr = HI_NULL;
    s_stMsgQueue.u32MaxLen   = 0;
    s_stMsgQueue.pstMsgFront = HI_NULL;
    s_stMsgQueue.pstMsgRear  = HI_NULL;

    return HI_SUCCESS;
}

static HI_S32  MsgQueueEn(MESSAGE_S* pstMsg)
{
    HI_U32 u32DataTypeSize = sizeof(MESSAGE_S);
    HI_U32 u32ItemSize = 0;
    MESSAGE_S* pstNextMsgAddr = HI_NULL;

    if ((pstMsg == HI_NULL) || (s_stMsgQueue.pu8BaseAddr == HI_NULL))
    {
        return HI_FAILURE;
    }

    s_stMsgQueue.pstMsgRear->u16MsgLength = pstMsg->u16MsgLength;

    if (IsFullQueue(&s_stMsgQueue ) == HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    u32ItemSize = u32DataTypeSize + pstMsg->u16MsgLength;

    if (((HI_U8*)s_stMsgQueue.pstMsgRear + u32ItemSize) > ((HI_U8*)s_stMsgQueue.pu8BaseAddr + s_stMsgQueue.u32MaxLen))
    {
        s_stMsgQueue.pstMsgRear->pu8MsgData = (HI_U8*)s_stMsgQueue.pu8BaseAddr + u32DataTypeSize;
    }
    else
    {
        s_stMsgQueue.pstMsgRear->pu8MsgData = (HI_U8*)s_stMsgQueue.pstMsgRear + u32DataTypeSize;
    }

    s_stMsgQueue.pstMsgRear->u16MsgLength = pstMsg->u16MsgLength;
    memcpy(s_stMsgQueue.pstMsgRear->pu8MsgData, pstMsg->pu8MsgData, pstMsg->u16MsgLength);

    pstNextMsgAddr = (MESSAGE_S*)((HI_U8*)s_stMsgQueue.pstMsgRear + u32ItemSize);

    if (((HI_U8*)pstNextMsgAddr + u32DataTypeSize) > ((HI_U8*)s_stMsgQueue.pu8BaseAddr + s_stMsgQueue.u32MaxLen))
    {
        pstNextMsgAddr = (MESSAGE_S*)(HI_VOID*)s_stMsgQueue.pu8BaseAddr;
    }

    pstNextMsgAddr->pu8MsgData = HI_NULL;
    pstNextMsgAddr->pstNext = HI_NULL;
    s_stMsgQueue.pstMsgRear->pstNext = pstNextMsgAddr;
    s_stMsgQueue.pstMsgRear = pstNextMsgAddr;
    s_stMsgQueue.pstMsgRear->u16MsgLength = 0;

    if (IsFullQueue(&s_stMsgQueue) == HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 MsgQueue_En(MESSAGE_S* pstMsg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if ((pstMsg == HI_NULL) || (s_stMsgQueue.pu8BaseAddr == HI_NULL))
    {
        return HI_FAILURE;
    }

    (HI_VOID)pthread_mutex_lock(&s_stMsgQueue.Queue_lock);
    s32Ret = MsgQueueEn(pstMsg);
    (HI_VOID)pthread_mutex_unlock(&s_stMsgQueue.Queue_lock);

    return s32Ret;
}

static HI_S32  MsgQueueDe(MESSAGE_S* pstMsg)
{
    if ((pstMsg == HI_NULL))
    {
        return HI_FAILURE;
    }

    if (IsEmptyQueue(&s_stMsgQueue) == HI_SUCCESS)
    {
        return HI_FAILURE;
    }

    pstMsg->u16MsgLength = s_stMsgQueue.pstMsgFront->u16MsgLength;
    pstMsg->pu8MsgData = s_stMsgQueue.pstMsgFront->pu8MsgData;
    pstMsg->pstNext = HI_NULL;
    s_stMsgQueue.pstMsgFront = s_stMsgQueue.pstMsgFront->pstNext;

    return HI_SUCCESS;
}

HI_S32 MsgQueue_De(MESSAGE_S* pstMsg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (pstMsg == HI_NULL)
    {
        return HI_FAILURE;
    }

    (HI_VOID)pthread_mutex_lock(&s_stMsgQueue.Queue_lock);
    s32Ret = MsgQueueDe(pstMsg);
    (HI_VOID)pthread_mutex_unlock(&s_stMsgQueue.Queue_lock);

    return s32Ret;
}
