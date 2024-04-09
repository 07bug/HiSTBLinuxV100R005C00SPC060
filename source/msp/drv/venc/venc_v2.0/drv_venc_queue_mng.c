/*
 * Copyright (c) (2011 - ...) digital media project platform development dept,
 * Hisilicon. All rights reserved.
 *
 * File: queue.c
 *
 * Purpose: vdec omx adaptor layer
 *
 * Author: sdk
 *
 * Date: 26, Dec, 2011
 *
 */
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/delay.h>

/* add include here */
#include <linux/version.h>

#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/vmalloc.h>
//#include <linux/config.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
//#include <linux/devfs_fs_kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>
#include <linux/seq_file.h>
#include <linux/list.h>

#include <asm/uaccess.h>
//#include <asm/hardware.h>
#include <asm/io.h>
//#include <asm/system.h>

#include <linux/ioport.h>
#include <linux/string.h>

#include "drv_venc_queue_mng.h"
#include "hi_drv_venc.h"
#include "hi_error_mpi.h"
#include "hi_drv_mem.h"
#define MAX_QUEUE_DEPTH    200

static void VENC_DRV_MngQueueStop(queue_info_s *queue)
{
    unsigned long flags;
    struct list_head *pos, *n;

    HI_INFO_VENC("msg prepare to stop!\n");

    /* flush msg list */
    spin_lock_irqsave(&queue->msg_lock, flags);
    queue->stop = 1;
    if (!list_empty(&queue->head))
    {
        HI_INFO_VENC("msg queue not empty, flush it!\n");
        list_for_each_safe(pos, n, &queue->head)        //== for (pos = (head)->next,n = pos->next; pos != (head);pos = n, n = pos->next)
        {
            list_del(pos);
            list_add_tail(pos, &queue->free);
        }
    }
    spin_unlock_irqrestore(&queue->msg_lock, flags);
    if (queue->bBlockWait)
    {
       wake_up(&queue->wait);
    }
    HI_INFO_VENC("Queue Stop ok!\n");
    return;
}

queue_info_s* VENC_DRV_MngQueueInit(HI_U32 depth, HI_BOOL bOMX, HI_BOOL bBlock)
{
    queue_info_s  *queue;
    queue_data_s  *data;
    HI_U32         num;

    if ((depth > MAX_QUEUE_DEPTH) || (depth == 0))
    {
        HI_ERR_VENC("Invalid Param!\n");
        return NULL;
    }
    num   = depth;
    queue = (queue_info_s*)HI_VMALLOC(HI_ID_VENC, sizeof(queue_info_s));
    if (!queue)
    {
        HI_ERR_VENC("Get MEM Failed\n");
        return NULL;
    }
    memset(queue, 0 , sizeof(queue_info_s));

    spin_lock_init(&queue->msg_lock);
    INIT_LIST_HEAD(&queue->head);
    INIT_LIST_HEAD(&queue->free);

    if (bBlock)
    {
       init_waitqueue_head(&queue->wait);       // just for omxvenc
    }

    queue->stop = 0;

    /* alloc element for seg stream */
    data  = (queue_data_s *)HI_VMALLOC(HI_ID_VENC, sizeof(queue_data_s) * num);
    if (!data)
    {
        HI_ERR_VENC("Get MEM Failed\n");
        HI_VFREE(HI_ID_VENC, queue);
        return NULL;
    }
    memset(data, 0 , sizeof(queue_data_s) * num);

    queue->alloc_data = data;
    for (; num; data++, num--)
    {
        list_add(&data->list, &queue->free);
    }

    queue->queue_num = depth;
    queue->bOMX      = bOMX;
    queue->bBlockWait= bBlock;
    queue->bSleep    = 0;
    queue->bStrmLock = 0;
    return queue;
}

HI_S32 VENC_DRV_MngQueueDeinit(queue_info_s *queue)
{
    HI_U32 timeCnt = 0;
    if (!queue)
    {
        HI_ERR_VENC("Invalid Param!\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    while((queue->bSleep)&& (timeCnt < 1000))
    {
       timeCnt++;
       msleep(10);
    }

    if (timeCnt == 1000)
    {
        HI_ERR_VENC("wait MngQueueDeinit time out!!Force to stop the channel\n");
    }

    VENC_DRV_MngQueueStop(queue);

    HI_VFREE(HI_ID_VENC,queue->alloc_data);
    HI_VFREE(HI_ID_VENC,queue);

    return 0;
}

HI_S32 VENC_DRV_MngQueueEmpty(queue_info_s *queue)
{
    if (!queue)
    {
        return 1;
    }

    return list_empty(&queue->head);
}

HI_S32 VENC_DRV_MngQueueFull(queue_info_s *queue)
{
    if (!queue)
    {
        return 1;
    }

    return list_empty(&queue->free);
}

static HI_S32 VENC_DRV_MngQueuePending(queue_info_s *queue)
{
    HI_U32 has_msg = 0;
    HI_U32 stopped = 0;
    unsigned long flags;

    if (!queue)
    { return 1; }

    spin_lock_irqsave(&queue->msg_lock, flags);
    has_msg = !list_empty(&queue->head);
    stopped = queue->stop;

    spin_unlock_irqrestore(&queue->msg_lock, flags);

    return has_msg || stopped;
}

HI_S32 VENC_DRV_MngDequeue(queue_info_s *queue, queue_data_s *pQueue_data)
{
    unsigned long flags;
    queue_data_s *msg = NULL;
    HI_S32 ret;

    if (!queue || !pQueue_data)
    {
        HI_ERR_VENC("Invalid Param\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    if (queue->bBlockWait)
    {
        queue->bSleep = 1;
        ret = wait_event_interruptible_timeout(queue->wait, VENC_DRV_MngQueuePending(queue),msecs_to_jiffies(30));   // msg_pending(queue)Ϊ�����˳������ĵȴ�!
        queue->bSleep = 0;
        if (ret <= 0)   /*ret >0 is success*/
        {
            //HI_ERR_VENC("dequeue timeout, failed, ret = %d\n", ret);
            return HI_FAILURE;
        }
        spin_lock_irqsave(&queue->msg_lock, flags);
        if (queue->stop)
        {
            HI_INFO_VENC("msg queue stoped\n");
            spin_unlock_irqrestore(&queue->msg_lock, flags);
            return HI_FAILURE;
        }

        if (list_empty(&queue->head))
        {
            HI_INFO_VENC("no free msg dequeue!\n");
            spin_unlock_irqrestore(&queue->msg_lock, flags);
            return HI_FAILURE;
        }

        msg = list_first_entry(&queue->head, queue_data_s, list);
        list_del(&msg->list);
        memcpy(&pQueue_data->unFrmInfo.msg_info_omx, &msg->unFrmInfo.msg_info_omx,sizeof(venc_msginfo));
        pQueue_data->bToOMX = msg->bToOMX;
        list_add(&msg->list, &queue->free);
        spin_unlock_irqrestore(&queue->msg_lock, flags);
    }
    else
    {
        spin_lock_irqsave(&queue->msg_lock, flags);
        if (queue->stop)
        {
            HI_INFO_VENC("msg queue stopped!\n");
            spin_unlock_irqrestore(&queue->msg_lock, flags);
            return HI_FAILURE;
        }

        if (list_empty(&queue->head))
        {
            HI_INFO_VENC("no free msg dequeue!\n");
            spin_unlock_irqrestore(&queue->msg_lock, flags);
            return HI_FAILURE;
        }
        msg = list_first_entry(&queue->head, queue_data_s, list);
        list_del(&msg->list);
        memcpy(&pQueue_data->unFrmInfo.queue_info, &msg->unFrmInfo.queue_info,sizeof(HI_DRV_VIDEO_FRAME_S));
        pQueue_data->bToOMX = msg->bToOMX;
        list_add(&msg->list, &queue->free);
        spin_unlock_irqrestore(&queue->msg_lock, flags);
    }
    return HI_SUCCESS;
}


HI_S32 VENC_DRV_MngQueue(queue_info_s *queue,queue_data_s *pQueue_data,HI_U32 msgcode, HI_U32 status)
{
    unsigned long flags;
    queue_data_s *msg = NULL;
    if (!queue)
    {
        HI_ERR_VENC("Invalid Param\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    if(!pQueue_data)
    {
        HI_ERR_VENC("invalid param of parm!\n");
        return HI_ERR_VENC_NULL_PTR;
    }

    spin_lock_irqsave(&queue->msg_lock, flags);
    if (queue->stop)
    {
        HI_INFO_VENC("msg queue stopped!\n");
        spin_unlock_irqrestore(&queue->msg_lock, flags);
        return HI_FAILURE;
    }
    if (VENC_DRV_MngQueueFull(queue))
    {
        HI_INFO_VENC("no free msg left!\n");
        spin_unlock_irqrestore(&queue->msg_lock, flags);

        return HI_FAILURE;
    }

    msg = list_first_entry(&queue->free, queue_data_s, list);

    list_del(&msg->list);

    if (queue->bOMX)
    {
        msg->unFrmInfo.msg_info_omx.status_code = status;
        msg->unFrmInfo.msg_info_omx.msgcode     = msgcode;
        if((VENC_MSG_RESP_INPUT_DONE == msgcode) || (VENC_MSG_RESP_OUTPUT_DONE == msgcode))
        {
             if (!pQueue_data->bToOMX)
             {
                 HI_ERR_VENC("not for omx!\n");
                 return HI_ERR_VENC_CHN_INVALID_STAT;
             }
             memcpy(&msg->unFrmInfo.msg_info_omx.buf, &pQueue_data->unFrmInfo.msg_info_omx.buf, sizeof(venc_user_buf));
        }
    }
    else
    {
       if (pQueue_data->bToOMX)
       {
           HI_ERR_VENC("not for venc!\n");
             return HI_ERR_VENC_CHN_INVALID_STAT;
       }
       memcpy(&msg->unFrmInfo.queue_info, &pQueue_data->unFrmInfo.queue_info, sizeof(HI_DRV_VIDEO_FRAME_S));
    }

    msg->bToOMX = pQueue_data->bToOMX;

    list_add_tail(&msg->list, &queue->head);
    spin_unlock_irqrestore(&queue->msg_lock, flags);

    if (queue->bBlockWait)
    {
       wake_up_interruptible(&queue->wait);
    }
    return HI_SUCCESS;
}

HI_VOID VENC_DRV_MngMoveQueueToDequeue(queue_info_s *queue, queue_info_s *dequeue)
{
    HI_U32 Cnt = 0;
    queue_data_s msg_queue;

    while ((!VENC_DRV_MngQueueEmpty(queue)) && (Cnt < 100))
    {
        Cnt++;
        if (VENC_DRV_MngDequeue(queue, &msg_queue) != HI_SUCCESS)
        {
            HI_ERR_VENC("Mng Dequeue is err!\n");
        }
        if (VENC_DRV_MngQueue(dequeue, &msg_queue, 0, 0) != HI_SUCCESS)
        {
            HI_ERR_VENC("Mng queue is err!\n");
        }
    }
}

