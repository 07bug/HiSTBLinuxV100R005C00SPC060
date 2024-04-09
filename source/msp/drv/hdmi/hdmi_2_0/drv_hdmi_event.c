/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_hdmi_event.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/12/10
  Description   :
  History       :
  Date          : 2014/12/10
  Author        : sdk
  Modification  :
*******************************************************************************/
#include <linux/delay.h>
#include "drv_hdmi_event.h"
#include "hdmi_platform.h"



#define EVENT_NULL_CHK(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("null pointer!\n");\
    return HI_FAILURE;}\
}while(0)

#define EVENT_INIT_CHK(pstEvtInfo) do{\
    EVENT_NULL_CHK(pstEvtInfo);\
    if(pstEvtInfo->bInit != HI_TRUE)\
    {HDMI_WARN("event didn't init!\n");\
    return HI_FAILURE;}\
}while(0)

#define EVENT_ID_CHK(enHdmi) do{\
    if (enHdmi >= HDMI_DEVICE_ID_BUTT){\
        return HI_FAILURE;}\
}while(0)


static HDMI_EVENT_INFO_S s_stEventInfo[HDMI_DEVICE_ID_BUTT];

const static HI_CHAR *s_pcEvent[] = {
    "HOTPLUG",                  // HDMI_EVENT_HOTPLUG = 0x10,
    "HOTUNPLUG",                // HDMI_EVENT_HOTUNPLUG,
    "EDID_FAIL",                // HDMI_EVENT_EDID_FAIL,
    "HDCP_FAIL",                // HDMI_EVENT_HDCP_FAIL,
    "HDCP_SUCCESS",             // HDMI_EVENT_HDCP_SUCCESS,
    "RSEN_CONNECT",             // HDMI_EVENT_RSEN_CONNECT,
    "RSEN_DISCONNECT",          // HDMI_EVENT_RSEN_DISCONNECT,
    "HDCP_USERSETTING",         // HDMI_EVENT_HDCP_USERSETTING,
    "HDCP_OFF",                 // HDMI_EVENT_HDCP_OFF,
    "SCRAMBLE_FAIL",            // HDMI_EVENT_SCRAMBLE_FAIL,
    "SCRAMBLE_SUCCESS",         // HDMI_EVENT_SCRAMBLE_SUCCESS,
    "ZERO_DRMIF_TIMEOUT",       // HDMI_EVENT_ZERO_DRMIF_TIMEOUT,
    "SWITCH_TO_HDRMODE_TIMEOUT",// HDMI_EVENT_SWITCH_TO_HDRMODE_TIMEOUT,

};

/*======================== private interface ==============================*/

static HDMI_EVENT_INFO_S *EventInfoPtrGet(HDMI_DEVICE_ID_E enHdmi)
{
    if (enHdmi < HDMI_DEVICE_ID_BUTT)
    {
        return &s_stEventInfo[enHdmi];
    }
    return HI_NULL;
}


static HI_S32 EventTypeCounter(HDMI_EVENT_POOL_S *pstPool,HDMI_EVENT_E enEvent,HI_BOOL bWrite)
{
    EVENT_NULL_CHK(pstPool);

    switch(enEvent)
    {
        case HDMI_EVENT_HOTPLUG:
            bWrite ? pstPool->stRunCnt.u32HPDWrCnt++ : pstPool->stRunCnt.u32HPDRdCnt++;
            break;
        case HDMI_EVENT_HOTUNPLUG:
            bWrite ? pstPool->stRunCnt.u32UnHPDWrCnt++ : pstPool->stRunCnt.u32UnHPDRdCnt++;
            break;

        case HDMI_EVENT_EDID_FAIL:
            bWrite ? pstPool->stRunCnt.u32EdidFailWrCnt++ : pstPool->stRunCnt.u32EdidFailRdCnt++;
            break;

        case HDMI_EVENT_HDCP_FAIL:
            bWrite ? pstPool->stRunCnt.u32HdcpFailWrCnt++ : pstPool->stRunCnt.u32HdcpFailRdCnt++;
            break;

        case HDMI_EVENT_HDCP_SUCCESS:
            bWrite ? pstPool->stRunCnt.u32HdcpSuccWrCnt++ : pstPool->stRunCnt.u32HdcpSuccRdCnt++;
            break;

        case HDMI_EVENT_RSEN_CONNECT:
            bWrite ? pstPool->stRunCnt.u32RsenConWrCnt++ : pstPool->stRunCnt.u32RsenConRdCnt++;
            break;

        case HDMI_EVENT_RSEN_DISCONNECT:
            bWrite ? pstPool->stRunCnt.u32RsenDisWrCnt++ : pstPool->stRunCnt.u32RsenDisRdCnt++;
            break;

        case HDMI_EVENT_HDCP_USERSETTING:
            bWrite ? pstPool->stRunCnt.u32HdcpUserWrCnt++ : pstPool->stRunCnt.u32HdcpUserRdCnt++;
            break;

        case HDMI_EVENT_BUTT:
        default:
            break;
    }

    return HI_SUCCESS;
}

/*======================== public interface ==============================*/

HI_S32 DRV_HDMI_EventInit(HDMI_DEVICE_ID_E enHdmiId)
{
    HDMI_EVENT_INFO_S *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);

    if (pstEvtInfo->bInit != HI_TRUE)
    {
        HDMI_MEMSET(pstEvtInfo,0,sizeof(HDMI_EVENT_INFO_S));
        /* init */
        HDMI_INIT_WAIT_QUEUE(pstEvtInfo->wtQueue);
        HDMI_INIT_MUTEX(pstEvtInfo->eventMutex);
        pstEvtInfo->u32Total        = 0;
        pstEvtInfo->bInit           = HI_TRUE;
        pstEvtInfo->bWakeUpAll      = HI_FALSE;
    }

    return HI_SUCCESS;
}


HI_S32  DRV_HDMI_EventDeInit(HDMI_DEVICE_ID_E enHdmiId)
{
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_INIT_CHK(pstEvtInfo);

    /*wake up all process which is waiting for event */
    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);
    pstEvtInfo->bWakeUpAll = HI_TRUE;
    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    wake_up(&pstEvtInfo->wtQueue);
    msleep(200);

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);
    HDMI_MEMSET(pstEvtInfo->stPool, 0 , HDMI_EVENT_POOL_CNT * sizeof(HDMI_EVENT_POOL_S));
    pstEvtInfo->u32Total    = 0;
    pstEvtInfo->bInit       = HI_FALSE;
    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    return HI_SUCCESS;
}

HI_S32  DRV_HDMI_EventPoolMalloc(HDMI_DEVICE_ID_E enHdmiId, HI_U32* pu32PoolID)
{
    HI_U32              i = 0;
    HDMI_EVENT_POOL_S   *pstTmpPool = HI_NULL;
    HI_U32              u32CurGid = 0;
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_INIT_CHK(pstEvtInfo);

    u32CurGid = (HI_U32)get_current()->tgid;

    /* malloc a new Pool element & init */
    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    /*check ID exist*/
    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if (pstTmpPool->stCtrl.u32PoolID == u32CurGid)
        {
            HDMI_WARN("Proc ID=%u  exist!\n",u32CurGid);
            HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
            return HDMI_EVENT_ID_EXIST;
        }
    }

    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if (!pstTmpPool->stCtrl.u32PoolID)
        {
            break;
        }
    }

    if(i >= HDMI_EVENT_POOL_CNT)
    {
        HDMI_WARN("Proc ID=%u no event sercer,pool max cnt = %u!\n",u32CurGid,i);
        HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
        return HI_FAILURE;
    }

    HDMI_MEMSET(&pstTmpPool->stCtrl , 0 , sizeof(HDMI_EVENT_RUN_CTRL_S));
    HDMI_MEMSET(&pstTmpPool->stRunCnt, 0 , sizeof(HDMI_EVENT_RUN_CNT_S));

    pstTmpPool->stCtrl.u32PoolID = u32CurGid;
    if (pu32PoolID != HI_NULL)
    {
        *pu32PoolID = pstTmpPool->stCtrl.u32PoolID;
    }

    pstTmpPool->stCtrl.bWakeUpFlag = HI_FALSE;

    for (i = 0; i < HDMI_EVENT_POOL_SIZE; i++)
    {
        pstTmpPool->stCtrl.enEventPool[i] = HDMI_EVENT_BUTT;
    }

    pstEvtInfo->u32Total++;

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    return HI_SUCCESS;
}


HI_S32  DRV_HDMI_EventPoolFree(HDMI_DEVICE_ID_E enHdmiId,HI_U32 u32PoolID)
{
    HI_U32              i = 0;
    HDMI_EVENT_POOL_S   *pstTmpPool = HI_NULL;
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_INIT_CHK(pstEvtInfo);

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    /*find a match ID and free it*/
    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if (pstTmpPool->stCtrl.u32PoolID == u32PoolID)
        {
            pstEvtInfo->u32Total--;
            pstTmpPool->stCtrl.bWakeUpFlag = HI_TRUE;
            wake_up(&pstEvtInfo->wtQueue);
            pstTmpPool->stCtrl.u32PoolID = 0;
            HDMI_INFO("Delete proc(%d) node from event pool\n",u32PoolID);
            break;
        }
    }

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    /* can't find a match ID*/
    if (i >= HDMI_EVENT_POOL_CNT)
    {
        HDMI_WARN("Fail, Not find a match proc id(%d) \n", u32PoolID);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_EventPoolWrite(HDMI_DEVICE_ID_E enHdmiId,
                                            HDMI_EVENT_E enEvent,
                                            HI_BOOL bOnlyCurrendId)
{
    HI_U32              i = 0;
    HI_U32              u32CurGid = 0;
    HDMI_EVENT_POOL_S   *pstTmpPool = HI_NULL;
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;
    HI_CHAR             *pcStr = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_INIT_CHK(pstEvtInfo);

    if ((enEvent < HDMI_EVENT_HOTPLUG)
        ||(enEvent > HDMI_EVENT_HDCP_USERSETTING))
    {
        HDMI_WARN("event(0x%x) invalid!\n", enEvent);
        return HI_FAILURE;
    }

    u32CurGid = (HI_U32)get_current()->tgid;

    /* notice: when system suspend excute func switch_set_state, Will be triger wakeup source: NETLINK*/
    if (HDMI_EVENT_HOTPLUG == enEvent)
    {
        HdmiSetAndroidState(STATE_HOTPLUGIN);
    }
    if (HDMI_EVENT_HOTUNPLUG == enEvent)
    {
        HdmiSetAndroidState(STATE_HOTPLUGOUT);
    }

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    if (pstEvtInfo->u32Total == 0)
    {
       HDMI_WARN("pool is empty\n");
       HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
       return HI_SUCCESS;
    }

    /* write event into all event pool in the list*/
    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if ( ((!bOnlyCurrendId) && pstTmpPool->stCtrl.u32PoolID)
            || (bOnlyCurrendId && (pstTmpPool->stCtrl.u32PoolID == u32CurGid)) )
        {
            /* The event pool is overflow*/
            if (  (pstTmpPool->stCtrl.enEventPool[pstTmpPool->stCtrl.u32WritePtr] >= HDMI_EVENT_HOTPLUG)
                &&(pstTmpPool->stCtrl.enEventPool[pstTmpPool->stCtrl.u32WritePtr] <= HDMI_EVENT_HDCP_USERSETTING)  )
            {
                pstTmpPool->stRunCnt.u32ErrWdCnt++;
                pstTmpPool->stCtrl.u32RdAbleCnt--;
                pstTmpPool->stCtrl.u32ReadPtr = ( pstTmpPool->stCtrl.u32WritePtr + 1 ) % HDMI_EVENT_POOL_SIZE;
                HDMI_WARN("pool of proc(%d) overflow\n", pstTmpPool->stCtrl.u32PoolID);
            }

            pstTmpPool->stCtrl.enEventPool[pstTmpPool->stCtrl.u32WritePtr++] = enEvent;
            pstTmpPool->stCtrl.u32WritePtr %= HDMI_EVENT_POOL_SIZE;
            EventTypeCounter(pstTmpPool,enEvent,HI_TRUE);
            pstTmpPool->stCtrl.u32RdAbleCnt++;
            wake_up(&pstEvtInfo->wtQueue);
            pcStr = (HI_CHAR *)s_pcEvent[enEvent - HDMI_EVENT_HOTPLUG];
            HDMI_INFO("event(0x%x, %s) proc(%d) success\n", enEvent, pcStr, pstTmpPool->stCtrl.u32PoolID);

            if (bOnlyCurrendId)
            {
                break;
            }
        }
    }
    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    return HI_SUCCESS;
}



HI_S32  DRV_HDMI_EventPoolRead(HDMI_DEVICE_ID_E enHdmiId,
                                            HI_U32 u32PoolID,
                                            HDMI_EVENT_E *penEvent)
{
    HI_U32              i = 0;
    HI_S32              s32Ret = HI_FAILURE;
    HDMI_EVENT_POOL_S   *pstTmpPool = HI_NULL;
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;
    HI_CHAR             *pcStr = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_NULL_CHK(penEvent);
    EVENT_INIT_CHK(pstEvtInfo);

    *penEvent = HDMI_EVENT_BUTT;

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    if (pstEvtInfo->u32Total == 0)
    {
       HDMI_WARN("pool is empty\n");
       HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
       return HI_SUCCESS;
    }

    /*find a match proc*/
    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if (pstTmpPool->stCtrl.u32PoolID == u32PoolID)
        {
            break;
        }
    }

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    if(i >= HDMI_EVENT_POOL_CNT)
    {
        HDMI_ERR("proc(%d, %s) not in pool\n",u32PoolID, get_current()->comm);
        msleep(500);
        return HI_FAILURE;
    }

    EVENT_NULL_CHK(pstTmpPool);
    wait_event_interruptible(pstEvtInfo->wtQueue, (pstEvtInfo->bWakeUpAll || pstTmpPool->stCtrl.bWakeUpFlag || pstTmpPool->stCtrl.u32RdAbleCnt > 0));

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    if(0 == pstTmpPool->stCtrl.u32RdAbleCnt)
    {
        /* when no event */
        HDMI_INFO("proc(%d, %s) no event\n", u32PoolID, get_current()->comm);
        HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
        return HI_FAILURE;
    }
    else
    {
        *penEvent = pstTmpPool->stCtrl.enEventPool[pstTmpPool->stCtrl.u32ReadPtr];

        pstTmpPool->stCtrl.enEventPool[pstTmpPool->stCtrl.u32ReadPtr] = HDMI_EVENT_BUTT;
        pstTmpPool->stCtrl.u32ReadPtr = ( pstTmpPool->stCtrl.u32ReadPtr + 1 ) % HDMI_EVENT_POOL_SIZE;
        pstTmpPool->stCtrl.bWakeUpFlag = HI_FALSE;

        if (   (*penEvent >= HDMI_EVENT_HOTPLUG)
            && (*penEvent <= HDMI_EVENT_HDCP_USERSETTING)   )
        {
            pstTmpPool->stCtrl.u32RdAbleCnt--;
            EventTypeCounter(pstTmpPool,*penEvent,HI_FALSE);
            s32Ret = HI_SUCCESS;
            pcStr = (HI_CHAR *)s_pcEvent[*penEvent - HDMI_EVENT_HOTPLUG];
            HDMI_INFO(" event(0x%x, %s) proc(%d, %s) success\n", *penEvent, pcStr ,pstTmpPool->stCtrl.u32PoolID, get_current()->comm);
        }
        else
        {
            pstTmpPool->stRunCnt.u32ErrRdCnt++;
            s32Ret = HI_FAILURE;
        }

    }

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    return s32Ret;
}

HI_S32  DRV_HDMI_EventPoolStatusGet(HDMI_DEVICE_ID_E enHdmiId,
                                                  HI_U32 u32PoolNum,
                                                  HDMI_EVENT_RUN_CTRL_S *pstCtrl,
                                                  HDMI_EVENT_RUN_CNT_S *pstCnt)
{
    HI_U32              i = 0,j = 0;
    HDMI_EVENT_POOL_S   *pstTmpPool = HI_NULL;
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_NULL_CHK(pstCtrl);
    EVENT_NULL_CHK(pstCnt);
    EVENT_INIT_CHK(pstEvtInfo);

    HDMI_MEMSET(pstCtrl,0,sizeof(HDMI_EVENT_RUN_CTRL_S));
    HDMI_MEMSET(pstCnt,0,sizeof(HDMI_EVENT_RUN_CNT_S));

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    if (   (u32PoolNum > pstEvtInfo->u32Total)
        || (u32PoolNum == 0) )
    {
        HDMI_WARN("The input pool num(%d) is wrong,event pool range is [1~%d]\n", u32PoolNum, pstEvtInfo->u32Total);
        HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
        return HI_FAILURE;
    }

    if (pstEvtInfo->u32Total == 0)
    {
       HDMI_WARN("event pool is empty\n");
       HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
       return HI_SUCCESS;
    }

    /*find a match ID and copy status*/
    for( i = 0, pstTmpPool = &pstEvtInfo->stPool[0];
        i < HDMI_EVENT_POOL_CNT;
        i++, pstTmpPool++ )
    {
        if(pstTmpPool->stCtrl.u32PoolID)
        {
            j++;
            if (j == u32PoolNum)
            {
                HDMI_MEMCPY(pstCtrl, &pstTmpPool->stCtrl, sizeof(HDMI_EVENT_RUN_CTRL_S));
                HDMI_MEMCPY(pstCnt, &pstTmpPool->stRunCnt, sizeof(HDMI_EVENT_RUN_CNT_S));
            }
        }
    }

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);
    return HI_SUCCESS;
}



HI_S32  DRV_HDMI_EventPoolTotalGet(HDMI_DEVICE_ID_E enHdmiId,
                                                HI_U32 *pu32Total)
{
    HDMI_EVENT_INFO_S   *pstEvtInfo = HI_NULL;

    EVENT_ID_CHK(enHdmiId);
    pstEvtInfo = EventInfoPtrGet(enHdmiId);
    EVENT_NULL_CHK(pstEvtInfo);
    EVENT_NULL_CHK(pu32Total);
    EVENT_INIT_CHK(pstEvtInfo);

    HDMI_MUTEX_LOCK(pstEvtInfo->eventMutex);

    *pu32Total = pstEvtInfo->u32Total;

    HDMI_MUTEX_UNLOCK(pstEvtInfo->eventMutex);

    return HI_SUCCESS;
}

EXPORT_SYMBOL(DRV_HDMI_EventPoolMalloc);
EXPORT_SYMBOL(DRV_HDMI_EventPoolFree);

