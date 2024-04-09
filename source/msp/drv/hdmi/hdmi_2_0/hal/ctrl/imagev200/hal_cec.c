#ifdef HDMI_CEC_SUPPORT
#include "si_datatypes.h"
#include "si_drv_cpi_api.h"
//#include "si_cec_enums.h"
#include "si_lib_malloc_api.h"
#include "si_lib_obj_api.h"
#include "si_lib_log_api.h"
#include "si_lib_time_api.h"
#include "sii_time.h"
#include "hal_cec.h"
#include "drv_hdmi_compatibility.h"


#define HDMI_CEC_PING_TIMEOUT       10//1s
#define HDMI_CEC_PING_ENABLE        0x01

static HI_VOID SiiCecCallBack(SiiInst_t inst, HI_VOID* data);


//static HI_CHAR l_cecTxOsdNameString [] = "HISI";
//static HI_U8 CecVendorID[3] = {'H','I','S'}; //should be HISI vendor ID
static SiiInst_t sCpiInst = HI_NULL;
static HI_U32 s_u32CecPingCount = 0;


static HI_U8 l_devTypes [16] =
{
    CEC_LOGADDR_TV,
    CEC_LOGADDR_RECDEV1,
    CEC_LOGADDR_RECDEV1,
    CEC_LOGADDR_TUNER1,
    CEC_LOGADDR_PLAYBACK1,
    CEC_LOGADDR_AUDSYS,
    CEC_LOGADDR_PURE_SWITCH,
    CEC_LOGADDR_VIDEO_PROCESSOR,
    CEC_LOGADDR_PLAYBACK1,
    CEC_LOGADDR_RECDEV1,
    CEC_LOGADDR_TUNER1,
    CEC_LOGADDR_PLAYBACK1,
    CEC_LOGADDR_RECDEV2,
    CEC_LOGADDR_RECDEV2,
    CEC_LOGADDR_TV,
    CEC_LOGADDR_TV
};


HI_VOID SiiCecEnable(HDMI_HAL_CEC_S* pstCec, HI_BOOL bEnable)
{
    if (bEnable)
    {
       pstCec->bWakeUpFlag = HI_FALSE;
       SiiDrvCpiEnable(sCpiInst);
    }
    else
    {
        pstCec->bWakeUpFlag = HI_TRUE;
        wake_up(&pstCec->msgQueue.msgWaitQueue);
        SiiDrvCpiDisable(sCpiInst);
    }

    pstCec->bEnable = bEnable;
    pstCec->isActiveSource = bEnable;
}

HI_VOID SiiCecAutoPingEnable(HDMI_HAL_CEC_S* pstCec)
{
    if (pstCec == HI_NULL)
    {
        return;
    }
    pstCec->enPingStatus = SiiTX_WAITCMD;
    SiiDrvCpiAPingTimerStart(sCpiInst);
    return;
}

static void SiiCecReset( HDMI_HAL_CEC_S* pstCec )
{
    HI_U16 i = 0;

#ifdef HDMI_PRIORITY_PLAYBACK
    pstCec->logicalAddr = CEC_LOGADDR_PLAYBACK1;
    SiiCecDeviceTypeSet(pstCec,HI_FALSE);
#else
    pstCec->logicalAddr = CEC_LOGADDR_TUNER1;
    SiiCecDeviceTypeSet(pstCec,HI_TRUE);

#endif
    pstCec->powerState = CEC_POWERSTATUS_STANDBY;
    pstCec->sourcePowerStatus = CEC_POWERSTATUS_STANDBY;

    for ( i = 0; i <= CEC_LOGADDR_UNREGORBC; i++ )
    {
        pstCec->logicalDeviceInfo[i].devPA = 0;
        pstCec->logicalDeviceInfo[i].devLA = 0;
        pstCec->logicalDeviceInfo[i].deviceType = 0;
    }
}

static HI_S32 SiiCecSendReportPhysicalAddress (HDMI_HAL_CEC_S* pstCec)
{
    SiiCpiData_t cecFrame;

    cecFrame.opcode         = CECOP_REPORT_PHYSICAL_ADDRESS;
    cecFrame.srcDestAddr    = MAKE_SRCDEST( pstCec->logicalAddr, CEC_LOGADDR_UNREGORBC );
    cecFrame.args[0]        = pstCec->physicalAddr >> 8;           // [Physical Address] High
    cecFrame.args[1]        = pstCec->physicalAddr & 0xFF;         // [Physical Address] Low
    cecFrame.args[2]        = l_devTypes[pstCec->logicalAddr];    // [Device Type]
    cecFrame.argCount       = 3;

    return( SiiDrvCpiWrite( sCpiInst, &cecFrame ));
}

HI_VOID CecStatusResume(HDMI_HAL_CEC_S *pstCec)
{
    if(HI_TRUE == pstCec->bEnable && HI_TRUE == pstCec->bNetValid)
    {
        SiiDrvCpiEnable(sCpiInst);
        // set capture addr
        SiiDrvCpiSetLogicalAddr(sCpiInst, pstCec->logicalAddr);
        // report logic addr
        //SiiCecSendReportPhysicalAddress(pstCec);
    }

    return;
}

HI_S32 SiiCecDeviceTypeSet(HDMI_HAL_CEC_S* pstCec, HI_BOOL bIsTuner)
{
    if (pstCec == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstCec->bIsTuner = bIsTuner;

    return HI_SUCCESS;
}

HI_VOID SiiCecAPingCallBack(SiiInst_t inst, HI_VOID* data)
{
    SiiCpiTxState_t enStatus = SiiTX_SENDING;
    HDMI_HAL_CEC_S* pstCec   = (HDMI_HAL_CEC_S *)(data);

    if (pstCec == HI_NULL)
    {
        return;
    }

    if (pstCec->u8PingIndex < pstCec->u8PingTotalCnt)
    {
        if (pstCec->enPingStatus == SiiTX_WAITCMD)
        {
            if (pstCec->u8PingIndex == 0)
            {
                HDMI_INFO("cec ping start! Ms=%d\n", HDMI_OSAL_GetTimeInMs());
            }
            SiiDrvCpiPingStatusGetAndClear(sCpiInst, &enStatus);
            SiiDrvCpiSendPing(sCpiInst, pstCec->logicalAddr, pstCec->enPingAddrSequence[pstCec->u8PingIndex]);
            pstCec->enPingStatus = SiiTX_SENDING;
            s_u32CecPingCount = 0;
        }
        else
        {
            SiiDrvCpiPingStatusGetAndClear(sCpiInst, &enStatus);
            switch (enStatus)
            {
                case SiiTX_SENDACKED:
                    HDMI_INFO("Polling DestAddr=0x%X, return ACK.\n", pstCec->enPingAddrSequence[pstCec->u8PingIndex]);
                    pstCec->network[pstCec->enPingAddrSequence[pstCec->u8PingIndex]] = HI_TRUE;
                    pstCec->enPingStatus = SiiTX_WAITCMD;
                    pstCec->u8PingIndex++;//ping next
                    break;
                case SiiTX_SENDFAILED:
                    HDMI_INFO("Polling DestAddr=0x%X, return NAK.\n", pstCec->enPingAddrSequence[pstCec->u8PingIndex]);
                    if (  (pstCec->enPingAddrSequence[pstCec->u8PingIndex] == CEC_LOGADDR_TV)
                        ||(pstCec->enPingAddrSequence[pstCec->u8PingIndex] == CEC_LOGADDR_AUDSYS))
                    {
                        pstCec->enPingStatus = SiiTX_WAITCMD;
                    }
                    else
                    {
                        pstCec->bNetValid     = HI_TRUE;
                        pstCec->logicalAddr = pstCec->enPingAddrSequence[pstCec->u8PingIndex];
                        pstCec->enPingStatus = SiiTX_IDLE;//ping end
                    }
                    pstCec->u8PingIndex++;//ping next
                    break;
                default:
                    s_u32CecPingCount++;
                    if ( s_u32CecPingCount > HDMI_CEC_PING_TIMEOUT )
                    {
                        HDMI_INFO("Polling DestAddr=0x%X, timeout.\n", pstCec->enPingAddrSequence[pstCec->u8PingIndex]);
                        pstCec->enPingStatus = SiiTX_WAITCMD;
                        pstCec->u8PingIndex++;
                    }
                    pstCec->enPingStatus = SiiTX_SENDING;//do nothing,wait ACK,NAK or timeout
                    break;
            }
        }
    }
    else
    {
        HDMI_ERR("Error u8PingIndex = %d\n", pstCec->u8PingIndex);
        pstCec->enPingStatus = SiiTX_IDLE;
    }

    /*ping ended, report the logical address*/
    if ( (pstCec->enPingStatus == SiiTX_IDLE)
        ||(pstCec->u8PingIndex >= pstCec->u8PingTotalCnt))
    {
        pstCec->enPingStatus = SiiTX_IDLE;
        SiiDrvCpiAPingTimerStop(sCpiInst);
        SiiDrvCpiSetLogicalAddr(sCpiInst, pstCec->logicalAddr);
        SiiCecSendReportPhysicalAddress(pstCec);
        HDMI_INFO("cec ping done! Ms=%d\n", HDMI_OSAL_GetTimeInMs());
    }
    return ;
}

HI_S32 SiiCecMsgSend(HDMI_HAL_CEC_S* pstCec, SiiCpiData_t* cecFrame)
{
    return( SiiDrvCpiWrite( sCpiInst, cecFrame ));
}

HI_S32 SiiCecMsgRead(HDMI_HAL_CEC_S* pstCec, HDMI_CEC_MSG_S* msg)
{
    HI_S32 s32Ret;

    s32Ret = wait_event_interruptible(pstCec->msgQueue.msgWaitQueue, (pstCec->msgQueue.msgValidNum > 0 || pstCec->bWakeUpFlag));
    if((s32Ret <= 0) && (0 == pstCec->msgQueue.msgValidNum))
    {
        /* When recived unhpd event, stop cec and set bWakeUpFlag is TRUE,
           the condition of wait_event_interruptible are always true. So the value shold be set FALSE. */
        pstCec->bWakeUpFlag = HI_FALSE;
        return HI_FAILURE;
    }

    if (down_interruptible(&pstCec->msgQueue.msgMutex))
       return -ERESTARTSYS;

    if (pstCec->msgQueue.msgValidNum > 0)
    {
        memcpy(msg, &pstCec->msgQueue.cecMsgPool[pstCec->msgQueue.msgReadPtr++], sizeof(HDMI_CEC_MSG_S));
        pstCec->msgQueue.msgReadPtr = (pstCec->msgQueue.msgReadPtr == CEC_MSG_POOL_SIZE) ? 0 : pstCec->msgQueue.msgReadPtr;

        if (pstCec->msgQueue.msgWritePtr == pstCec->msgQueue.msgReadPtr)
        {
            pstCec->msgQueue.msgValidNum = 0;
        }
        else if (pstCec->msgQueue.msgWritePtr > pstCec->msgQueue.msgReadPtr)
        {
            pstCec->msgQueue.msgValidNum = pstCec->msgQueue.msgWritePtr - pstCec->msgQueue.msgReadPtr;
        }
        else
        {
            pstCec->msgQueue.msgValidNum = CEC_MSG_POOL_SIZE - (pstCec->msgQueue.msgReadPtr - pstCec->msgQueue.msgWritePtr);
        }
        pstCec->bWakeUpFlag = HI_FALSE;
    }

    up(&pstCec->msgQueue.msgMutex);

    return HI_SUCCESS;
}

static HI_S32 CecMsgWrite(HDMI_HAL_CEC_S* pstCec, SiiCpiData_t* cecFrame)
{
    HDMI_CEC_MSG_S msg;

    memset(&msg, 0, sizeof(HDMI_CEC_MSG_S));
    msg.srcDestAddr = cecFrame->srcDestAddr;
    msg.opcode      = cecFrame->opcode;
    msg.argCount    = cecFrame->argCount;
    memcpy(msg.args, cecFrame->args, msg.argCount);

    if (down_interruptible(&pstCec->msgQueue.msgMutex))
       return -ERESTARTSYS;

    memcpy(&pstCec->msgQueue.cecMsgPool[pstCec->msgQueue.msgWritePtr++], &msg, sizeof(HDMI_CEC_MSG_S));

    pstCec->msgQueue.msgWritePtr = (pstCec->msgQueue.msgWritePtr == CEC_MSG_POOL_SIZE) ? 0 : pstCec->msgQueue.msgWritePtr;

    if (pstCec->msgQueue.msgWritePtr > pstCec->msgQueue.msgReadPtr)
    {
        pstCec->msgQueue.msgValidNum = pstCec->msgQueue.msgWritePtr - pstCec->msgQueue.msgReadPtr;
    }
    else if (pstCec->msgQueue.msgWritePtr < pstCec->msgQueue.msgReadPtr)
    {
        pstCec->msgQueue.msgValidNum = CEC_MSG_POOL_SIZE - (pstCec->msgQueue.msgReadPtr - pstCec->msgQueue.msgWritePtr);
    }
    else
    {
        pstCec->msgQueue.msgValidNum = CEC_MSG_POOL_SIZE;
    }

    up(&pstCec->msgQueue.msgMutex);

    if (pstCec->msgQueue.msgValidNum > 0)
    {
        wake_up(&pstCec->msgQueue.msgWaitQueue);
    }

    return HI_SUCCESS;
}

HDMI_HAL_CEC_S* SiiCecDeviceCreate(SiiInst_t inst, HI_U16 cpiBaseAddr )
{
    HDMI_HAL_CEC_S* pstCec = HI_NULL;
    pstCec = (HDMI_HAL_CEC_S *) SiiLibMallocCreate(sizeof(HDMI_HAL_CEC_S));
    if (pstCec == HI_NULL)
    {
         return HI_NULL;
    }

    HDMI_INIT_WAIT_QUEUE(pstCec->msgQueue.msgWaitQueue);
    HDMI_INIT_MUTEX(pstCec->msgQueue.msgMutex);

    SiiCecReset (pstCec);

    sCpiInst = SiiDrvCpiCreate(inst, cpiBaseAddr, SiiCecCallBack, SiiCecAPingCallBack, pstCec);
    if (sCpiInst == HI_NULL)
    {
        SiiLibMallocDelete(pstCec);
        return HI_NULL;
    }

    return pstCec;
}

void SiiCecDeviceDelete(HDMI_HAL_CEC_S* pstCec)
{
    if (pstCec)
    {
        pstCec->bWakeUpFlag = HI_TRUE;
        wake_up(&pstCec->msgQueue.msgWaitQueue);
        msleep(200);
        SiiDrvCpiDelete(sCpiInst);
        SiiLibMallocDelete(pstCec);
    }

}

//------------------------------------------------------------------------------
//! @brief  Send an ACTIVE SOURCE message.  Does not wait for a reply.
//! @param[in]  - logicalAddr   Logical device going active
//! @param[in]  - physicalAddr  Physical address of device
//------------------------------------------------------------------------------
void SiiCecSendActiveSource ( HI_U8 logicalAddr, HI_U16 physicalAddr )
{
    SiiCpiData_t cecFrame;

    cecFrame.opcode         = CECOP_ACTIVE_SOURCE;
    cecFrame.srcDestAddr    = MAKE_SRCDEST( logicalAddr, CEC_LOGADDR_UNREGORBC );
    cecFrame.args[0]        = physicalAddr >> 8;        // [Physical Address] High
    cecFrame.args[1]        = physicalAddr & 0xFF;      // [Physical Address] Low
    cecFrame.argCount       = 2;

    SiiDrvCpiWrite( sCpiInst, &cecFrame );
}


static HI_VOID SiiCecCallBack(SiiInst_t inst, HI_VOID* data)
{
//  HI_BOOL          processedMsg;
    SiiCpiStatus_t  cecStatus;
    SiiCpiData_t    cecFrame;
    uint_t          frameCount;
    HDMI_HAL_CEC_S * pstCec = (HDMI_HAL_CEC_S*)data;
    //sCpiInst = inst;

    if(pstCec->bEnable)
    {
        SiiDrvCpiServiceWriteQueue(inst);               // Send any pending messages
        SiiDrvCpiHwStatusGet(inst, &cecStatus );        // Get the CEC transceiver status

        if(cecStatus.rxState)
        {
            for(;;)
            {
                frameCount = SiiDrvCpiFrameCount(inst);
                if ( frameCount == 0 )
                {
                    break;
                }
                if ( !SiiDrvCpiRead(inst, &cecFrame ))
                {
                    SII_LIB_LOG_DEBUG2("Error in Rx Fifo\n" );
                    break;
                }

                CecMsgWrite(pstCec, &cecFrame);
            }

        }

    }


}
#endif
