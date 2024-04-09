/******************************************************************************

  Copyright (C), 2016-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_hal_cec.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#include <linux/jiffies.h>
#include <linux/delay.h>

#include "hdmi_hal_cec.h"
#include "hdmi_hal_intf.h"

#include "hdmi_reg_cec.h"
#include "hdmi_reg_aon.h"
#include "drv_hdmi_compatibility.h"

typedef union
{
    struct{
        HI_U16      bit01_tv            : 1     ; /* 00 */
        HI_U16      bit01_record_dev1   : 1     ; /* 01 */
        HI_U16      bit01_record_dev2   : 1     ; /* 02 */
        HI_U16      bit01_tuner1        : 1     ; /* 03 */
        HI_U16      bit01_playback_dev1 : 1     ; /* 04 */
        HI_U16      bit01_audio_sys     : 1     ; /* 05 */
        HI_U16      bit01_tuner2        : 1     ; /* 06 */
        HI_U16      bit01_tuner3        : 1     ; /* 07 */
        HI_U16      bit01_playback_dev2 : 1     ; /* 08 */
        HI_U16      bit01_record_dev3   : 1     ; /* 09 */
        HI_U16      bit01_tuner4        : 1     ; /* 10 */
        HI_U16      bit01_playback_dev3 : 1     ; /* 11 */
        HI_U16      bit01_reserved1     : 1     ; /* 12 */
        HI_U16      bit01_reserved2     : 1     ; /* 13 */
        HI_U16      bit01_specific_use  : 1     ; /* 14 */
        HI_U16      bit01_broadcast     : 1     ; /* 15 */
    }bits;

    HI_U16 u16;
}CEC_LOGIC_ADDR_U;


#define CEC_ADDR_MASK       0xf
#define CEC_ADDR_TX         0x8     /* tunner 1 */


#define CEC_NULL_CHK(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("%s is null pointer!return fail.\n",#p);\
    return HI_FAILURE;}\
}while(0)

#define CEC_NULL_CHK_NORET(p) do{\
    if(HI_NULL == p)\
    {HDMI_WARN("%s is null pointer!\n",#p);\
    return ;}\
}while(0)
#define CEC_INIT_CHK(pstCecInfo) do{\
    CEC_NULL_CHK(pstCecInfo);\
    if(pstCecInfo->bInit != HI_TRUE)\
    {HDMI_WARN("cec module didn't init!\n");\
    return HI_FAILURE;}\
}while(0)


#if 0
typedef enum
{

    CEC_INTR_tx_fifo_full,
    CEC_INTR_start_odd_bit,
    CEC_INTR_short_pulse_detect,
    CEC_INTR_rx_fifo_overrun,
    CEC_INTR_rx_cmd_set,
    CEC_INTR_tx_fifo_empty,
    CEC_INTR_tx_ff_cstate_set,
    CEC_INTR_rx_fifo_nempty,
    CEC_INTR_low_min_err,
    CEC_INTR_BUTT,

}CEC_INTR_E;
#endif

#define CEC_AUTOPING_TIMEOUT    500
#define CEC_RX_READ_TIMEOUT     200
#define CEC_TX_WRITE_TIMEOUT    6000


static CEC_INFO_S s_stCecInfo[HDMI_DEVICE_ID_BUTT];

static CEC_INFO_S *CecInfoPtrGet(HDMI_DEVICE_ID_E enHdmi)
{
    if (enHdmi < HDMI_DEVICE_ID_BUTT)
    {
        return &s_stCecInfo[enHdmi];
    }
    return HI_NULL;
}


/************************ private interface ********************************/

static HI_VOID CecHwEnable(HI_BOOL bEnable)
{
    HDMI_CEC_TX_CTRL_cec_reg_i2c_cec_passthruSet(!bEnable);
    //HDMI_CEC_TX_CTRL_cec_reg_force_non_calibSet(!bEnable);

    /* 20170204 Importan NOTE: when disable cec ,must set 1 in bit cec_reg_nack_hdr,
       or it will  disturb other device cec communication.such as ONKYU TX-RZ800 & Samsung UA55HU6000JXXZ;
       when enable cec ,set 0 in bit cec_reg_nack_hdr, and it must clear cec rx-fifo whenever recieve an message.*/
    HDMI_CEC_TX_CTRL_cec_reg_nack_hdrSet(!bEnable);
    if(!bEnable)
    {
        /* Clear Rx fifo All */
        HDMI_CEC_TX_CTRL_cec_reg_rx_clr_allSet(HI_TRUE);
        HDMI_CEC_TX_CTRL_manual_cmd_setSet(HI_FALSE);

         /* irq mask  */
        HDMI_TX_AON_INTR_MASK_aon_intr_mask4Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask5Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask6Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask7Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask8Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask9Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask10Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask11Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask12Set(HI_TRUE);
        HDMI_TX_AON_INTR_MASK_aon_intr_mask13Set(HI_TRUE);

        /* clr irq state */
        HDMI_TX_AON_INTR_STATE_aon_intr_stat4Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat5Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat7Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat8Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat9Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat10Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat12Set(HI_TRUE);
        HDMI_TX_AON_INTR_STATE_aon_intr_stat13Set(HI_TRUE);

    }

    return ;
}

static HI_S32 CecOperationCodeSet(HI_U8 *pu8Data)
{

    HI_U8       *pu8Tmp = HI_NULL;

    for(pu8Tmp = pu8Data; pu8Tmp < pu8Data + CEC_MAX_RAW_SIZE ; pu8Tmp++)
    {
        CEC_NULL_CHK(pu8Tmp);
    }

    HDMI_TX_CEC_CMD0_tx_cec_operand0Set(pu8Data[0]);
    HDMI_TX_CEC_CMD0_tx_cec_operand1Set(pu8Data[1]);
    HDMI_TX_CEC_CMD0_tx_cec_operand2Set(pu8Data[2]);
    HDMI_TX_CEC_CMD1_tx_cec_operand3Set(pu8Data[3]);
    HDMI_TX_CEC_CMD1_tx_cec_operand4Set(pu8Data[4]);
    HDMI_TX_CEC_CMD1_tx_cec_operand5Set(pu8Data[5]);
    HDMI_TX_CEC_CMD1_tx_cec_operand6Set(pu8Data[6]);
    HDMI_TX_CEC_CMD2_tx_cec_operand7Set(pu8Data[7]);
    HDMI_TX_CEC_CMD2_tx_cec_operand8Set(pu8Data[8]);
    HDMI_TX_CEC_CMD2_tx_cec_operand9Set(pu8Data[9]);
    HDMI_TX_CEC_CMD2_tx_cec_operand10Set(pu8Data[10]);
    HDMI_TX_CEC_CMD3_tx_cec_operand11Set(pu8Data[11]);
    HDMI_TX_CEC_CMD3_tx_cec_operand12Set(pu8Data[12]);
    HDMI_TX_CEC_CMD3_tx_cec_operand13Set(pu8Data[13]);
    HDMI_TX_CEC_CMD3_tx_cec_operand14Set(pu8Data[14]);

    return HI_SUCCESS;
}

static HI_S32 CecOperationCodeGet(HI_U8 *pu8Data)
{
    HI_U8       *pu8Tmp = HI_NULL;

    for(pu8Tmp = pu8Data; pu8Tmp < pu8Data + CEC_MAX_RAW_SIZE ; pu8Tmp++)
    {
        CEC_NULL_CHK(pu8Tmp);
    }

    pu8Data[0] = HDMI_RX_CEC_CMD0_rx_cec_operand0Get();
    pu8Data[1] = HDMI_RX_CEC_CMD0_rx_cec_operand1Get();
    pu8Data[2] = HDMI_RX_CEC_CMD0_rx_cec_operand2Get();
    pu8Data[3] = HDMI_RX_CEC_CMD1_rx_cec_operand3Get();
    pu8Data[4] = HDMI_RX_CEC_CMD1_rx_cec_operand4Get();
    pu8Data[5] = HDMI_RX_CEC_CMD1_rx_cec_operand5Get();
    pu8Data[6] = HDMI_RX_CEC_CMD1_rx_cec_operand6Get();
    pu8Data[7] = HDMI_RX_CEC_CMD2_rx_cec_operand7Get();
    pu8Data[8] = HDMI_RX_CEC_CMD2_rx_cec_operand8Get();
    pu8Data[9] = HDMI_RX_CEC_CMD2_rx_cec_operand9Get();
    pu8Data[10] = HDMI_RX_CEC_CMD2_rx_cec_operand10Get();
    pu8Data[11] = HDMI_RX_CEC_CMD3_rx_cec_operand11Get();
    pu8Data[12] = HDMI_RX_CEC_CMD3_rx_cec_operand12Get();
    pu8Data[13] = HDMI_RX_CEC_CMD3_rx_cec_operand13Get();
    pu8Data[14] = HDMI_RX_CEC_CMD3_rx_cec_operand14Get();

    return HI_SUCCESS;
}

static HI_VOID CecManualCmdSet(HI_VOID)
{
    HDMI_CEC_TX_CTRL_manual_cmd_setSet(HI_TRUE);
    udelay(10);
    HDMI_CEC_TX_CTRL_manual_cmd_setSet(HI_FALSE);
    return;
}

static HI_VOID CecFlushTxFifo(HI_VOID)
{
    HDMI_CEC_TX_CTRL_cec_reg_flush_tx_ffSet(HI_TRUE);
    udelay(10);
    HDMI_CEC_TX_CTRL_cec_reg_flush_tx_ffSet(HI_FALSE);
    return;
}

static HI_S32 CecMsgRx(CEC_MSG_S *pstMsg)
{
    HI_S32      s32Ret = HI_SUCCESS;

    CEC_NULL_CHK(pstMsg);

    pstMsg->stOperand.stRawData.u8Length = HDMI_CEC_RX_STATE_cec_reg_rx_cmd_byte_cntGet();
    pstMsg->enSrcAddr   = HDMI_CEC_RX_STATE_cec_rx_init_cmd_headerGet();
    pstMsg->enDestAddr  = HDMI_CEC_RX_STATE_cec_rx_dest_cmd_headerGet();
    pstMsg->u8Opcode    = HDMI_RX_CEC_CMD0_rx_cec_commandGet();
    s32Ret = CecOperationCodeGet(pstMsg->stOperand.stRawData.u8Data);

    HDMI_CEC_TX_CTRL_cec_reg_rx_clr_cur_setSet(HI_TRUE);
#if 0
    HDMI_ERR("\n"
                    "stMsg.enDestAddr            =0x%02x\n"
                    "stMsg.enSrcAddr             =0x%02x\n"
                    "stMsg.u8Opcode              =0x%02x\n"
                    "stMsg.stOperand.u8Length    =0x%02x\n",
                    pstMsg->enDestAddr,
                    pstMsg->enSrcAddr,
                    pstMsg->u8Opcode,
                    pstMsg->stOperand.stRawData.u8Length);
#endif

    return s32Ret;

}

static HI_S32 CecMsgTx(CEC_MSG_S *pstMsg)
{
    CEC_NULL_CHK(pstMsg);
#if 0
    if(pstMsg->stOperand.enUIOpcode == 0x100)//sent ping
    {
        HDMI_CEC_TX_DEST_cec_tx_dest_idSet(pstMsg->enDestAddr);
        HDMI_CEC_TX_DEST_cec_reg_sd_poll_internSet(HI_TRUE);
    }
    else
#endif
    {
        HDMI_CEC_TX_DEST_cec_tx_dest_idSet(pstMsg->enDestAddr);
        //HDMI_CEC_TX_INIT_cec_tx_init_idSet(pstMsg->enSrcAddr);
        HDMI_TX_CEC_CMD0_tx_cec_commandSet(pstMsg->u8Opcode);
        HDMI_CEC_TX_CTRL_cec_reg_tx_cmd_cntSet(pstMsg->stOperand.stRawData.u8Length);
        CecOperationCodeSet(pstMsg->stOperand.stRawData.u8Data);
        /* clear txDone Intr */
        HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(HI_TRUE);
        /* transimit lunch */
        CecManualCmdSet();
    }
#if 0
    HDMI_ERR("\n"
            "stMsg.enDestAddr            =0x%02x\n"
            "stMsg.enSrcAddr             =0x%02x\n"
            "stMsg.u8Opcode              =0x%02x\n"
            "stMsg.stOperand.u8Length    =0x%02x\n",
            pstMsg->enDestAddr,
            pstMsg->enSrcAddr,
            pstMsg->u8Opcode,
            pstMsg->stOperand.stRawData.u8Length);
#endif
    return HI_SUCCESS;
}


static HI_U32 CecRxErrCheck(HI_VOID)
{
    HI_S32      s32Ret = 0;
    HI_U32      u32ErrorCode = 0;

    /* cec_rx_fifo_overrun,>2 fifo */
    s32Ret = HDMI_TX_AON_INTR_STATE_aon_intr_stat8Get();
    if(s32Ret)
    {
        u32ErrorCode |= s32Ret<<8;
        HDMI_TX_AON_INTR_STATE_aon_intr_stat8Set(HI_TRUE);
    }

    /*  cec_short_pulse_detect */
    s32Ret = HDMI_TX_AON_INTR_STATE_aon_intr_stat7Get();
    if(s32Ret)
    {
        u32ErrorCode |= s32Ret<<7;
        HDMI_TX_AON_INTR_STATE_aon_intr_stat7Set(HI_TRUE);
    }


    /*cec_start_odd_bit,start bit is 0 < 3.45ms */
    s32Ret = HDMI_TX_AON_INTR_STATE_aon_intr_stat5Get();
    if(s32Ret)
    {
        u32ErrorCode |= s32Ret<<5;
        HDMI_TX_AON_INTR_STATE_aon_intr_stat5Set(HI_TRUE);
    }

    if(HDMI_CEC_RX_STATE_cec_rx_errorGet())
    {
        HDMI_WARN("REG_404c_bit[7]=true!\n");
    }

    return u32ErrorCode;

}

static HI_U32 CecTxErrCheck(HI_VOID)
{
    HI_S32      s32Ret = 0;
    HI_U32      u32ErrorCode = 0;

    /* retry cnt timeout */
    s32Ret = HDMI_TX_AON_INTR_STATE_aon_intr_stat6Get();
    if(s32Ret)
    {
        u32ErrorCode |= s32Ret<<6;
        HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(HI_TRUE);
        /* solve problem of CEC CTS 9.3-3 tx many times REPORT_PHY_ADDR */
        HDMI_CEC_TX_CTRL_manual_cmd_setSet(HI_FALSE);
        CecFlushTxFifo();
    }

    return u32ErrorCode;
}


static HI_BOOL CecTxWriteDoneCheck(HI_VOID)
{
    if (HDMI_TX_AON_INTR_STATE_aon_intr_stat11Get())
    {
        HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(HI_TRUE);
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static HI_BOOL  CecRxStartCheck(HI_VOID)
{
    if( HDMI_TX_AON_INTR_STATE_aon_intr_stat9Get() )
    {
        /* clr int */
        HDMI_TX_AON_INTR_STATE_aon_intr_stat9Set(HI_TRUE) ;
        //return HI_TRUE;
        return HI_FALSE;
    }
    else if(HDMI_TX_AON_INTR_STATE_aon_intr_stat12Get())
    {
        /* no need to clr */
        return HI_TRUE;
    }
    else if(HDMI_CEC_RX_STATE_cec_reg_rx_ff_wr_selGet())
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}


static HI_BOOL  CecRxDoneCheck(HI_VOID)
{
    if(HDMI_TX_AON_INTR_STATE_aon_intr_stat12Get())
    {
        HDMI_TX_AON_INTR_STATE_aon_intr_stat12Set(HI_TRUE);
        return HI_TRUE;
    }
    else if(HDMI_CEC_RX_STATE_cec_reg_rx_ff_wr_selGet())
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static HI_BOOL  CecTxStartCheck(CEC_INFO_S *pstCecInfo)
{
    HI_BOOL bStart = HI_FALSE;

    if(HDMI_TX_AON_INTR_STATE_aon_intr_stat4Get())
    {
        HDMI_TX_AON_INTR_STATE_aon_intr_stat4Set(HI_TRUE);
    }

    if(pstCecInfo->u32TxPoolRdAbleCnt)
    {
       if(!HDMI_TX_AON_INTR_STATE_aon_intr_stat4Get())
       {
            bStart = HI_TRUE;
       }
       else
       {
            bStart = HI_FALSE;
            CecManualCmdSet();
            HDMI_WARN("cec tx fifo full,can't send,TxPoolRdAbleCnt=%u\n",pstCecInfo->u32TxPoolRdAbleCnt);
       }
    }
    return bStart;
}

static HI_S32 CecLogicAddrSet(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_U32              u32CapId = 0;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);

    HDMI_CEC_TX_INIT_cec_tx_init_idSet(pstCecInfo->stDrvInfo.u8LogicalAddr);
    u32CapId = 1<< pstCecInfo->stDrvInfo.u8LogicalAddr ;
    HDMI_CEC_CAPTUTR_ID_cec_capture_idSet(u32CapId);

    return HI_SUCCESS;
}

HI_S32 CecBroadAddr(HDMI_DEVICE_ID_E enHdmiId)
{
    CEC_MSG_S   stMsg;
    CEC_INFO_S  *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);

    /* report my phy addr */
    HDMI_MEMSET(&stMsg , 0 ,sizeof(CEC_MSG_S));
    stMsg.enSrcAddr                     = pstCecInfo->stDrvInfo.u8LogicalAddr;
    stMsg.enDestAddr                    = CEC_LOGICALADD_BROADCAST;
    stMsg.u8Opcode                      = CEC_UICMD_REPORT_PHYADDR; //report phyaddr & logic_addr
    stMsg.stOperand.stRawData.u8Data[0] = ((pstCecInfo->stDrvInfo.au8PhysicalAddr[0] << 4) & 0xf0) | (pstCecInfo->stDrvInfo.au8PhysicalAddr[1] & 0x0f);
    stMsg.stOperand.stRawData.u8Data[1] = ((pstCecInfo->stDrvInfo.au8PhysicalAddr[2] << 4) & 0xf0) | (pstCecInfo->stDrvInfo.au8PhysicalAddr[3] & 0x0f);
    stMsg.stOperand.stRawData.u8Data[2] = pstCecInfo->stDrvInfo.u8LogicalAddr;
    stMsg.stOperand.stRawData.u8Length  = 3;

    return HAL_HDMI_CecMsgTx(enHdmiId,&stMsg);

}

static HI_BOOL CecPingStartCheck(CEC_INFO_S *pstCecInfo)
{
    if ( pstCecInfo
        && (pstCecInfo->u32MaxPingTime)
        && (pstCecInfo->enPingProcess != CEC_PROCESS_OK) )
    {
        pstCecInfo->u32MaxPingTime--;
        HDMI_INFO("cec ping start! Ms=%lld\n", HAL_HDMI_MachMsGet());
        return HI_TRUE;
    }

    return HI_FALSE;
}

/* clear pool queue must be stop machine before */
static HI_VOID CecClearPool(CEC_INFO_S *pstCecInfo)
{
    CEC_NULL_CHK_NORET(pstCecInfo);

    pstCecInfo->enMachStatus       = CEC_MACH_IDLE;
    //pstCecInfo->enPingProcess      = CEC_PROCESS_UNDO;
    /* clear tx pool */
    pstCecInfo->enTxProcess        = CEC_PROCESS_UNDO;
    pstCecInfo->u32TxPoolWtPtr     = 0;
    pstCecInfo->u32TxPoolRdPtr     = 0;
    pstCecInfo->u32TxPoolRdAbleCnt = 0;
    HDMI_MEMSET(&pstCecInfo->stTxPool, 0, sizeof(pstCecInfo->stTxPool));
    /* clear rx pool */
    pstCecInfo->enRxProcess        = CEC_PROCESS_UNDO;
    pstCecInfo->u32RxPoolWtPtr     = 0;
    pstCecInfo->u32RxPoolRdPtr     = 0;
    pstCecInfo->u32RxPoolRdAbleCnt = 0;
    HDMI_MEMSET(&pstCecInfo->stRxPool, 0, sizeof(pstCecInfo->stRxPool));

    return ;
}

static HI_S32 CecTxRecord(CEC_INFO_S *pstCecInfo)
{
    CEC_MSG_ELEM_S      *pstSrcElem = HI_NULL;
    CEC_MSG_ELEM_S      *pstDestElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);


    HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);
    pstSrcElem = &pstCecInfo->stTxPool[pstCecInfo->u32TxPoolRdPtr];
    pstDestElem = &pstCecInfo->stTxRecord[pstCecInfo->u32TxRecordWtPtr];

    if (pstSrcElem->u64TimeStamp!=0 && pstCecInfo->u32TxPoolRdAbleCnt)
    {
        pstDestElem->bCecEnable      = pstSrcElem->bCecEnable;
        pstDestElem->enProcess       = pstCecInfo->enTxProcess;
        pstDestElem->u64TimeStamp    = HAL_HDMI_MachMsGet();
        HDMI_MEMCPY(&pstDestElem->stMsg,&pstSrcElem->stMsg,sizeof(CEC_MSG_S));
        HDMI_MEMSET(pstSrcElem,0,sizeof(CEC_MSG_ELEM_S));

        pstCecInfo->u32TxRecordWtPtr = (pstCecInfo->u32TxRecordWtPtr+1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32TxPoolRdPtr = (pstCecInfo->u32TxPoolRdPtr+1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32TxPoolRdAbleCnt--;
        pstCecInfo->u32TxMsgCnt++;

    }

    HDMI_MUTEX_UNLOCK(pstCecInfo->stTxMute);

    return HI_SUCCESS;
}


static HI_S32 CecTxPoolRead(CEC_INFO_S *pstCecInfo,CEC_MSG_S *pstMsg)
{
    HI_S32              s32Ret  = HI_SUCCESS;
    CEC_MSG_ELEM_S      *pstTmpElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pstMsg);

    HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);

    pstTmpElem = &pstCecInfo->stTxPool[pstCecInfo->u32TxPoolRdPtr];

    /* when the elem is not full,it will cover the first-comein element in the tx pool. */
    if (pstTmpElem->u64TimeStamp != 0 && pstCecInfo->u32TxPoolRdAbleCnt)
    {
        HDMI_MEMCPY(pstMsg,&pstTmpElem->stMsg,sizeof(CEC_MSG_S));
        pstMsg->enSrcAddr = pstCecInfo->stDrvInfo.u8LogicalAddr;
        s32Ret  = HI_SUCCESS;
    }
    else
    {
        s32Ret  = HI_FAILURE;
    }

    HDMI_MUTEX_UNLOCK(pstCecInfo->stTxMute);

    return s32Ret;

}

static HI_S32 CecTxPoolWrite(CEC_INFO_S *pstCecInfo,CEC_MSG_S *pstMsg)
{

    CEC_MSG_ELEM_S      *pstTmpElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pstMsg);

    HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);

    pstTmpElem = &pstCecInfo->stTxPool[pstCecInfo->u32TxPoolWtPtr];

    /* when the elem is not full,it will cover the first-comein element in the tx pool. */
    if (pstTmpElem->u64TimeStamp != 0)
    {
        pstCecInfo->u32TxPoolRdPtr = (pstCecInfo->u32TxPoolWtPtr + 1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32TxPoolRdAbleCnt--;
    }

    /* pool buf */
    pstTmpElem->bCecEnable      = pstCecInfo->stDrvInfo.bCecEnable;
    pstTmpElem->u64TimeStamp    = HAL_HDMI_MachMsGet();
    HDMI_MEMCPY(&pstTmpElem->stMsg,pstMsg,sizeof(CEC_MSG_S));
    pstCecInfo->u32TxPoolRdAbleCnt++;
    pstCecInfo->u32TxPoolWtPtr = (pstCecInfo->u32TxPoolWtPtr + 1) % CEC_MAX_MSG_NUM;

    HDMI_MUTEX_UNLOCK(pstCecInfo->stTxMute);

    /* suspend have the highest priority fo transimit */
    if (CEC_OPCODE_STANDBY == pstMsg->u8Opcode)
    {
        //HAL_HDMI_MachStop(pstCecInfo->u32MachId);
        CecClearPool(pstCecInfo);
        CecFlushTxFifo();
        CecMsgTx(pstMsg);
        //resume Func Open will start Mach
        //HAL_HDMI_MachStart(pstCecInfo->u32MachId);
    }

    return HI_SUCCESS;

}


static HI_S32 CecRxRecord(CEC_INFO_S *pstCecInfo)
{
    CEC_MSG_ELEM_S      *pstSrcElem = HI_NULL;
    CEC_MSG_ELEM_S      *pstDestElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);


    HDMI_MUTEX_LOCK(pstCecInfo->stRxMute);
    pstSrcElem  = &pstCecInfo->stRxPool[pstCecInfo->u32RxPoolRdPtr];
    pstDestElem = &pstCecInfo->stRxRecord[pstCecInfo->u32RxRecordWtPtr];
    if (pstSrcElem->u64TimeStamp!=0 && pstCecInfo->u32RxPoolRdAbleCnt)
    {
        pstDestElem->bCecEnable      = pstSrcElem->bCecEnable;
        pstDestElem->enProcess       = pstCecInfo->enRxProcess;
        pstDestElem->u64TimeStamp    = HAL_HDMI_MachMsGet();
        HDMI_MEMCPY(&pstDestElem->stMsg,&pstSrcElem->stMsg,sizeof(CEC_MSG_S));
        HDMI_MEMSET(pstSrcElem,0,sizeof(CEC_MSG_ELEM_S));

        pstCecInfo->u32RxRecordWtPtr = (pstCecInfo->u32RxRecordWtPtr+1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32RxPoolRdPtr = (pstCecInfo->u32RxPoolRdPtr + 1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32RxPoolRdAbleCnt--;
        pstCecInfo->u32RxMsgCnt++;
    }

    HDMI_MUTEX_UNLOCK(pstCecInfo->stRxMute);

    return HI_SUCCESS;
}

static HI_S32 CecRxPoolRead(CEC_INFO_S *pstCecInfo,CEC_MSG_S *pstMsg)
{
    HI_S32              s32Ret = HI_FAILURE;
    CEC_MSG_ELEM_S      *pstTmpElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pstMsg);

    HDMI_MUTEX_LOCK(pstCecInfo->stRxMute);

    pstTmpElem = &pstCecInfo->stRxPool[pstCecInfo->u32RxPoolRdPtr];
    if (pstTmpElem->u64TimeStamp != 0 && pstCecInfo->u32RxPoolRdAbleCnt)
    {
        HDMI_MEMCPY(pstMsg,&pstTmpElem->stMsg,sizeof(CEC_MSG_S));
        s32Ret = HI_SUCCESS;
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    HDMI_MUTEX_UNLOCK(pstCecInfo->stRxMute);

    return s32Ret;
}

static HI_S32 CecRxPoolWrite(CEC_INFO_S *pstCecInfo,CEC_MSG_S *pstMsg)
{
    CEC_MSG_ELEM_S      *pstTmpElem = HI_NULL;

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pstMsg);

    HDMI_MUTEX_LOCK(pstCecInfo->stRxMute);

    pstTmpElem = &pstCecInfo->stRxPool[pstCecInfo->u32RxPoolWtPtr];

    /* when the elem is not full,it will cover the first-comein element in the record buffer. */
    if (pstTmpElem->u64TimeStamp != 0)
    {
        pstCecInfo->u32RxPoolRdPtr = (pstCecInfo->u32RxPoolWtPtr + 1) % CEC_MAX_MSG_NUM;
        pstCecInfo->u32RxPoolRdAbleCnt--;
    }

    /* pool buf */
    pstTmpElem->bCecEnable      = pstCecInfo->stDrvInfo.bCecEnable;
    pstTmpElem->enProcess       = pstCecInfo->enRxProcess;
    pstTmpElem->u64TimeStamp    = HAL_HDMI_MachMsGet();
    HDMI_MEMCPY(&pstTmpElem->stMsg,pstMsg,sizeof(CEC_MSG_S));
    pstCecInfo->u32RxPoolRdAbleCnt++;
    pstCecInfo->u32RxPoolWtPtr = (pstCecInfo->u32RxPoolWtPtr + 1) % CEC_MAX_MSG_NUM;

    wake_up(&pstCecInfo->stRxWaitQueue);

    HDMI_MUTEX_UNLOCK(pstCecInfo->stRxMute);

    return HI_SUCCESS;
}

static HI_S32 CecGetPingstatus(CEC_INFO_S *pstCecInfo, HI_U32 *pu32PingStatus)
{
    HI_U64 u64TimeOut = 0;

    CEC_NULL_CHK(pu32PingStatus);
    CEC_NULL_CHK(pstCecInfo);
    *pu32PingStatus = CEC_PING_WAIT_ACK;

    if (HDMI_TX_AON_INTR_STATE_aon_intr_stat11Get())//Ack
    {
        HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(HI_TRUE);
        *pu32PingStatus = CEC_PING_ACK;
    }
    else if (HDMI_TX_AON_INTR_STATE_aon_intr_stat6Get())//Nack
    {
        HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(HI_TRUE);
        *pu32PingStatus = CEC_PING_NAK;
    }
    else
    {
        u64TimeOut = HAL_HDMI_MachMsGet() - pstCecInfo->u64MachStamp;
        if ( u64TimeOut > CEC_AUTOPING_TIMEOUT )
        {
            *pu32PingStatus = CEC_PING_TIMEOUT;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 CecPingSend(CEC_LOGICALADD_E enDestAddr)
{
    HDMI_TX_AON_INTR_STATE_aon_intr_stat11Set(HI_TRUE);
    HDMI_TX_AON_INTR_STATE_aon_intr_stat6Set(HI_TRUE);
    HDMI_CEC_TX_DEST_cec_tx_dest_idSet(enDestAddr);
    HDMI_CEC_TX_DEST_cec_reg_sd_poll_internSet(HI_TRUE);
    udelay(100);
    HDMI_CEC_TX_DEST_cec_reg_sd_poll_internSet(HI_FALSE);

    return HI_SUCCESS;
}

static HI_S32 CecPingCheck(CEC_INFO_S *pstCecInfo, CEC_MACH_STATUS_E *penMachStatus)
{
    HI_U32 u32PingStatus = CEC_PING_WAIT_ACK;

    CEC_NULL_CHK(penMachStatus);
    CEC_NULL_CHK(pstCecInfo);

    if (pstCecInfo->u8PingIndex < pstCecInfo->u8PingTotalCnt)
    {
        CecGetPingstatus(pstCecInfo, &u32PingStatus);
        switch (u32PingStatus)
        {
            case CEC_PING_ACK:
                HDMI_INFO("Polling DestAddr=0x%X, return ACK.\n", pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex]);
                pstCecInfo->stDrvInfo.au8Network[pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex]] = HI_TRUE;
                *penMachStatus = CEC_MACH_PING_START;
                pstCecInfo->u8PingIndex++;//ping next
                break;
            case CEC_PING_NAK:
                HDMI_INFO("Polling DestAddr=0x%X, return NAK.\n", pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex]);
                if (  (pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex] == CEC_LOGICALADD_TV)
                    ||(pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex] == CEC_LOGICALADD_AUDIOSYSTEM))
                {
                    *penMachStatus = CEC_MACH_PING_START;
                }
                else
                {
                    pstCecInfo->stDrvInfo.bNetValid     = HI_TRUE;
                    pstCecInfo->stDrvInfo.u8LogicalAddr = pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex];
                    *penMachStatus = CEC_MACH_IDLE;//ping end
                }
                pstCecInfo->u8PingIndex++;//ping next
                break;
            case CEC_PING_TIMEOUT:
                HDMI_INFO("Polling DestAddr=0x%X, timeout.\n", pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex]);

                *penMachStatus = CEC_MACH_PING_START;
                pstCecInfo->u8PingIndex++;
                break;
            default:
                *penMachStatus = CEC_MACH_PING_WAIT_DONE;//do nothing,wait ACK,NAK or timeout
                break;
        }
    }
    else
    {
        HDMI_ERR("Error u8PingIndex = %d\n", pstCecInfo->u8PingIndex);
        *penMachStatus = CEC_MACH_IDLE;
    }

    /*ping ended, report the logical address*/
    if ( (*penMachStatus == CEC_MACH_IDLE)
        ||(pstCecInfo->u8PingIndex >= pstCecInfo->u8PingTotalCnt))
    {
        *penMachStatus = CEC_MACH_IDLE;
        pstCecInfo->enPingProcess   = CEC_PROCESS_OK;
        CecLogicAddrSet(pstCecInfo->enHdmiId);
        CecBroadAddr(pstCecInfo->enHdmiId);
        HDMI_INFO("cec ping done! Ms=%lld\n", HAL_HDMI_MachMsGet());
    }

    return HI_SUCCESS;
}

HI_VOID CecMachCallBack(HI_VOID *pData)
{
    HI_U32      u32ErrIntCode = 0;
    HI_U64      u64TimeOut = 0;
    CEC_MACH_STATUS_E enMachStatus;
    CEC_INFO_S *pstCecInfo = (CEC_INFO_S *)pData;
    static CEC_MSG_S   stMsg = {0};

    if (pstCecInfo==HI_NULL || (!pstCecInfo->bInit))
    {
        HDMI_WARN("cec pstCecInfo null or module not init!\n");
        return ;
    }

    if (pstCecInfo->u64StopStamp)
    {
        if(HAL_HDMI_MachMsGet() - pstCecInfo->u64StopStamp >= 3000)
        {
            HAL_HDMI_CecReset(pstCecInfo->enHdmiId);
            return ;
        }
    }

    switch(pstCecInfo->enMachStatus)
    {

        case CEC_MACH_IDLE:
            /* task priority: ping > rx > tx */
            if ( CecPingStartCheck(pstCecInfo) )
            {
                pstCecInfo->enMachStatus    = CEC_MACH_PING_START;
            }
            else if ( CecRxStartCheck() )
            {
                pstCecInfo->enRxProcess     = CEC_PROCESS_UNDO;
                pstCecInfo->u64MachStamp    = HAL_HDMI_MachMsGet();
                pstCecInfo->enMachStatus    = CEC_MACH_RX_WAIT_DONE;
            }
            else if ( CecTxStartCheck(pstCecInfo) )
            {
                pstCecInfo->enTxProcess     = CEC_PROCESS_UNDO;
                pstCecInfo->enMachStatus    = CEC_MACH_TX_START;
            }
            break;

        case CEC_MACH_PING_START:
            if (pstCecInfo->u8PingIndex < pstCecInfo->u8PingTotalCnt)
            {
                CecPingSend(pstCecInfo->enPingAddrSequence[pstCecInfo->u8PingIndex]);
                pstCecInfo->u64MachStamp    = HAL_HDMI_MachMsGet();
                pstCecInfo->enMachStatus    = CEC_MACH_PING_WAIT_DONE;
                pstCecInfo->enPingProcess   = CEC_PROCESS_ING;
                break;
            }
            /*if pstCecInfo->u8PingIndex >= pstCecInfo->u8PingTotalCnt, then continue execute case CEC_MACH_PING_WAIT_DONE*/
        case CEC_MACH_PING_WAIT_DONE:
            enMachStatus = CEC_MACH_PING_WAIT_DONE;
            CecPingCheck(pstCecInfo, &enMachStatus);
            pstCecInfo->enMachStatus = enMachStatus;//enMachStatus change in CecPingCheck()
            break;

        case CEC_MACH_RX_WAIT_DONE:
            pstCecInfo->enRxProcess = CEC_PROCESS_ING;
            if (!CecRxDoneCheck())
            {
                u64TimeOut = HAL_HDMI_MachMsGet() - pstCecInfo->u64MachStamp;
                u32ErrIntCode = CecRxErrCheck();
                if ( (u64TimeOut > CEC_RX_READ_TIMEOUT) || u32ErrIntCode)
                {
                    pstCecInfo->enRxProcess = CEC_PROCESS_FAIL;
                    HDMI_WARN("cec rx wait timeout=%llu(>%u),u32ErrIntCode=0x%x!\n",u64TimeOut,CEC_RX_READ_TIMEOUT,u32ErrIntCode);

                }
            }
            else
            {
                CecMsgRx(&stMsg);
                pstCecInfo->enRxProcess = CEC_PROCESS_OK;
            }
            break;

        case CEC_MACH_TX_START:
            CecTxPoolRead(pstCecInfo,&stMsg);
            CecMsgTx(&stMsg);
            pstCecInfo->u64MachStamp    = HAL_HDMI_MachMsGet();
            pstCecInfo->enMachStatus    = CEC_MACH_TX_WAIT_DONE;
            break;

        case CEC_MACH_TX_WAIT_DONE:
            if (CecTxWriteDoneCheck())
            {
                pstCecInfo->enTxProcess = CEC_PROCESS_OK;
            }
            else
            {
                u64TimeOut = HAL_HDMI_MachMsGet() - pstCecInfo->u64MachStamp;
                u32ErrIntCode = CecTxErrCheck();
                if ( (u64TimeOut > CEC_TX_WRITE_TIMEOUT) || u32ErrIntCode)
                {
                    pstCecInfo->enTxProcess = CEC_PROCESS_FAIL;
                    HDMI_WARN("cec tx wait Opcode=0x%02x,timeout=%llu(>%u),u32ErrIntCode=0x%x!\n",stMsg.u8Opcode,u64TimeOut,CEC_TX_WRITE_TIMEOUT,u32ErrIntCode);
                }
            }
            break;

        default:
            HDMI_ERR("cec unknown enMachStatus!\n");
            break;
    }

    if ( (pstCecInfo->enRxProcess == CEC_PROCESS_FAIL)
        || (pstCecInfo->enRxProcess == CEC_PROCESS_OK) )
    {
        CecRxPoolWrite(pstCecInfo,&stMsg);
        pstCecInfo->enMachStatus = CEC_MACH_IDLE;
        pstCecInfo->enRxProcess  = CEC_PROCESS_UNDO;
        HDMI_MEMSET(&stMsg,0,sizeof(stMsg));
    }

    if ( (pstCecInfo->enTxProcess == CEC_PROCESS_FAIL)
        || (pstCecInfo->enTxProcess == CEC_PROCESS_OK) )
    {
        CecTxRecord(pstCecInfo);
        pstCecInfo->enMachStatus = CEC_MACH_IDLE;
        pstCecInfo->enTxProcess  = CEC_PROCESS_UNDO;
        HDMI_MEMSET(&stMsg,0,sizeof(stMsg));
    }


/* ----for debug start -----

    HDMI_ERR("\n"
            "stMsg.enDestAddr            =0x%02x\n"
            "stMsg.enSrcAddr             =0x%02x\n"
            "stMsg.u8Opcode              =0x%02x\n"
            "stMsg.stOperand.enUIOpcode  =0x%02x\n"
            "stMsg.stOperand.u8Length    =0x%02x\n",
            stMsg.enDestAddr,
            stMsg.enSrcAddr,
            stMsg.u8Opcode,
            stMsg.stOperand.enUIOpcode,
            stMsg.stOperand.stRawData.u8Length);

    static HI_U64 u64dddd = 0;
    if (HAL_HDMI_MachMsGet() - u64dddd > 2000)
    {
        HDMI_ERR("0 WtPtr=%d,RdPtr=%d,RdAbleCnt=%d,enMachStatus=%d\n",
            pstCecInfo->u32RxPoolWtPtr,pstCecInfo->u32RxPoolRdPtr,pstCecInfo->u32RxPoolRdAbleCnt,pstCecInfo->enMachStatus);
        HDMI_ERR("0 WtPtr=%d,RdPtr=%d,RdAbleCnt=%d,enMachStatus=%d\n",
            pstCecInfo->u32TxPoolWtPtr,pstCecInfo->u32TxPoolRdPtr,pstCecInfo->u32TxPoolRdAbleCnt,pstCecInfo->enMachStatus);
        u64dddd = HAL_HDMI_MachMsGet();
    }
----for debug end -----*/

    return ;
}

/************************ public interface ********************************/

HI_S32 HAL_HDMI_CecInit(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_S32              s32Ret = HI_SUCCESS;
    HDMI_MACH_CTRL_S    stMachCtrl = {0};
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);

    s32Ret |= HDMI_TX_S_tx_cec_reg_REGS_TYPE_Init();

    CecHwEnable(HI_FALSE);

    if (!pstCecInfo->bInit)
    {
        HDMI_MEMSET(pstCecInfo,0,sizeof(CEC_INFO_S));
        HDMI_INIT_WAIT_QUEUE(pstCecInfo->stRxWaitQueue);
        HDMI_INIT_MUTEX(pstCecInfo->stRxMute);
        HDMI_INIT_MUTEX(pstCecInfo->stTxMute);
        pstCecInfo->bInit       = HI_TRUE;
        pstCecInfo->enHdmiId    = enHdmiId;
#ifdef HDMI_PRIORITY_PLAYBACK
        pstCecInfo->stDrvInfo.u8LogicalAddr = CEC_LOGICALADD_PLAYDEV_1;
        HAL_HDMI_CecDeviceTypeSet(enHdmiId, HI_FALSE);
#else
        pstCecInfo->stDrvInfo.u8LogicalAddr = CEC_LOGICALADD_TUNER_1;
        HAL_HDMI_CecDeviceTypeSet(enHdmiId, HI_TRUE);
#endif
        // call by open; make sure first ping SrcAddr isn't TV(0)
        HDMI_CEC_TX_INIT_cec_tx_init_idSet(pstCecInfo->stDrvInfo.u8LogicalAddr);
        stMachCtrl.pCbData      = pstCecInfo;
        stMachCtrl.pfnCallBack  = CecMachCallBack;
        stMachCtrl.u64Interval  = CEC_DEFAULT_MACH_INTERVAL;
        stMachCtrl.pu8Name      = "CEC";
        s32Ret |= HAL_HDMI_MachRegister(&stMachCtrl,&pstCecInfo->u32MachId);
    }

    return s32Ret;
}

HI_S32 HAL_HDMI_CecDeInit(HDMI_DEVICE_ID_E enHdmiId)
{
    HI_S32              s32Ret = HI_SUCCESS;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);

    s32Ret |= HAL_HDMI_MachUnRegister(pstCecInfo->u32MachId);
    HAL_HDMI_CecReset(enHdmiId);
    wake_up(&pstCecInfo->stRxWaitQueue);
    msleep(100);

    HDMI_MEMSET(pstCecInfo,0,sizeof(CEC_INFO_S));
    pstCecInfo->bInit = HI_FALSE;

    s32Ret |= HDMI_TX_S_tx_cec_reg_REGS_TYPE_DeInit();

    return  s32Ret;
}

HI_S32 HAL_HDMI_CecReset(HDMI_DEVICE_ID_E enHdmiId)
{
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);

    CecHwEnable(HI_FALSE);
    HAL_HDMI_MachStop(pstCecInfo->u32MachId);
    HDMI_INFO("cec machine stop!\n");

    //HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);
    //HDMI_MEMSET(&pstCecInfo->stDrvInfo,0,sizeof(HDMI_CEC_INFO_S));
    pstCecInfo->stDrvInfo.bCecEnable= HI_FALSE;
    pstCecInfo->enPingProcess       = CEC_PROCESS_UNDO;
    pstCecInfo->u64MachStamp        = 0;
    pstCecInfo->enMachStatus        = CEC_MACH_IDLE;

    pstCecInfo->u32TxMsgCnt         = 0;
    pstCecInfo->u32TxRecordWtPtr    = 0;
    pstCecInfo->enTxProcess         = CEC_PROCESS_UNDO;

    pstCecInfo->u32TxPoolWtPtr      = 0;
    pstCecInfo->u32TxPoolRdPtr      = 0;
    pstCecInfo->u32TxPoolRdAbleCnt  = 0;


    HDMI_MEMSET(&pstCecInfo->stTxRecord,0,sizeof(pstCecInfo->stTxRecord));
    HDMI_MEMSET(&pstCecInfo->stTxPool  ,0,sizeof(pstCecInfo->stTxPool));
    //HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);

    //HDMI_MUTEX_LOCK(pstCecInfo->stRxMute);
    pstCecInfo->u32RxMsgCnt         = 0;
    pstCecInfo->u32RxRecordWtPtr    = 0;

    pstCecInfo->u32RxPoolWtPtr      = 0;
    pstCecInfo->u32RxPoolRdPtr      = 0;
    pstCecInfo->u32RxPoolRdAbleCnt  = 0;

    HDMI_MEMSET(&pstCecInfo->stRxRecord,0,sizeof(pstCecInfo->stRxRecord));
    HDMI_MEMSET(&pstCecInfo->stRxPool  ,0,sizeof(pstCecInfo->stRxPool));
    pstCecInfo->bRxWakeUpFlag       = HI_TRUE;
    wake_up(&pstCecInfo->stRxWaitQueue);
    //HDMI_MUTEX_UNLOCK(pstCecInfo->stRxMute);

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_CecNetGet(HDMI_DEVICE_ID_E enHdmiId,HI_U8 *pu8PhyAddr)
{
    HI_S32              s32Ret = HI_SUCCESS;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pu8PhyAddr);

    HDMI_MEMCPY(pstCecInfo->stDrvInfo.au8PhysicalAddr, pu8PhyAddr, 4);
    HDMI_MEMSET(pstCecInfo->enPingAddrSequence, CEC_LOGICALADD_BUTT, CEC_LOGICALADD_BUTT);
    HDMI_MEMSET(pstCecInfo->stDrvInfo.au8Network, HI_FALSE, CEC_LOGICALADD_BUTT);

    pstCecInfo->u8PingIndex           = 0;
    pstCecInfo->enPingAddrSequence[0] = CEC_LOGICALADD_TV;
    pstCecInfo->enPingAddrSequence[1] = CEC_LOGICALADD_AUDIOSYSTEM;

    if (pstCecInfo->bIsTuner)
    {
        pstCecInfo->enPingAddrSequence[2] = CEC_LOGICALADD_TUNER_1;
        pstCecInfo->enPingAddrSequence[3] = CEC_LOGICALADD_TUNER_2;
        pstCecInfo->enPingAddrSequence[4] = CEC_LOGICALADD_TUNER_3;
        pstCecInfo->enPingAddrSequence[5] = CEC_LOGICALADD_TUNER_4;
        pstCecInfo->u8PingTotalCnt        = 6;
    }
    else
    {
        pstCecInfo->enPingAddrSequence[2] = CEC_LOGICALADD_PLAYDEV_1;
        pstCecInfo->enPingAddrSequence[3] = CEC_LOGICALADD_PLAYDEV_2;
        pstCecInfo->enPingAddrSequence[4] = CEC_LOGICALADD_PLAYDEV_3;
        pstCecInfo->u8PingTotalCnt        = 5;
    }

    pstCecInfo->u32MaxPingTime            = 1;
    pstCecInfo->enPingProcess             = CEC_PROCESS_UNDO;
    pstCecInfo->stDrvInfo.bNetValid       = HI_FALSE;          /* u8LogicalAddr & au8Network valid flag  */
    pstCecInfo->stDrvInfo.u8LogicalAddr   = CEC_LOGICALADD_BROADCAST;

    if ((pu8PhyAddr[0] == 0xf)
        &&(pu8PhyAddr[1] == 0xf)
        &&(pu8PhyAddr[2] == 0xf)
        &&(pu8PhyAddr[3] == 0xf))
    {
        pstCecInfo->u8PingTotalCnt = 2;//only polling TV and audio system
    }

    CecHwEnable(HI_TRUE);
    s32Ret = HAL_HDMI_MachStart(pstCecInfo->u32MachId);

    return s32Ret;
}

HI_S32 HAL_HDMI_CecEnable(HDMI_DEVICE_ID_E enHdmiId,HI_BOOL bEnable)
{
    HI_S32              s32Ret = HI_SUCCESS;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);

    CecHwEnable(bEnable);

    if (bEnable )
    {
        pstCecInfo->u64StopStamp = 0;
        pstCecInfo->stDrvInfo.bCecEnable    = HI_TRUE;
        pstCecInfo->bRxWakeUpFlag           = HI_FALSE;
        HDMI_CEC_TX_INIT_cec_tx_init_idSet(pstCecInfo->stDrvInfo.u8LogicalAddr);
        HDMI_CEC_CAPTUTR_ID_cec_capture_idSet(1<< pstCecInfo->stDrvInfo.u8LogicalAddr);
        s32Ret = HAL_HDMI_MachStart(pstCecInfo->u32MachId);
    }
    else
    {
        if(pstCecInfo->u32TxPoolRdAbleCnt)
        {
            pstCecInfo->u64StopStamp    = HAL_HDMI_MachMsGet();
            pstCecInfo->bRxWakeUpFlag   = HI_TRUE;
            wake_up(&pstCecInfo->stRxWaitQueue);
        }
        else
        {
            s32Ret = HAL_HDMI_CecReset(enHdmiId);
        }
    }
    HDMI_INFO("cec bEanble=%d!\n",bEnable);

    return s32Ret;
}

HI_S32 HAL_HDMI_CecInfoGet(HDMI_DEVICE_ID_E enHdmiId,HDMI_CEC_INFO_S *pstDrvInfo)
{
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_NULL_CHK(pstDrvInfo);
    CEC_INIT_CHK(pstCecInfo);

    HDMI_MEMCPY(pstDrvInfo,&pstCecInfo->stDrvInfo,sizeof(HDMI_CEC_INFO_S));
    pstDrvInfo->u32RecieveCnt = pstCecInfo->u32RxPoolRdAbleCnt;

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_CecMsgTx(HDMI_DEVICE_ID_E enHdmiId,CEC_MSG_S *pstMsg)
{
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);

    return CecTxPoolWrite(pstCecInfo,pstMsg);;
}

HI_S32 HAL_HDMI_CecMsgRx(HDMI_DEVICE_ID_E enHdmiId,CEC_MSG_S *pstMsg)
{
    HI_S32              s32Ret = HI_SUCCESS;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstMsg);
    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);


    if (pstCecInfo->u32RxPoolRdAbleCnt == 0)
    {
        wait_event_interruptible(pstCecInfo->stRxWaitQueue,
            ( (pstCecInfo->bRxWakeUpFlag == HI_TRUE)||(pstCecInfo->u32RxPoolRdAbleCnt > 0) ) );
    }
    //HDMI_ERR("flag=%d,rxcnt=%d\n",pstCecInfo->bRxWakeUpFlag,pstCecInfo->u32RxPoolRdAbleCnt);
    if (pstCecInfo->u32RxPoolRdAbleCnt > 0)
    {
        s32Ret |= CecRxPoolRead(pstCecInfo,pstMsg);
        s32Ret |= CecRxRecord(pstCecInfo);
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 HAL_HDMI_CecStatGet(HDMI_DEVICE_ID_E enHdmiId,CEC_STATUS_S *pstStatus)
{
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstStatus);
    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);


//    HDMI_MUTEX_LOCK(pstCecInfo->stTxMute);
    HAL_HDMI_CecInfoGet(enHdmiId, &pstStatus->stDrvInfo);
    pstStatus->bInit                = pstCecInfo->bInit ;
    pstStatus->u32MachId            = pstCecInfo->u32MachId;
    pstStatus->enPingProcess        = pstCecInfo->enPingProcess;
    pstStatus->enMachStatus         = pstCecInfo->enMachStatus;

    /* tx */
    pstStatus->u32TxMsgCnt          = pstCecInfo->u32TxMsgCnt;
    pstStatus->u32TxRecordWtPtr     = pstCecInfo->u32TxRecordWtPtr;

    pstStatus->u32TxPoolWtPtr       = pstCecInfo->u32TxPoolWtPtr;
    pstStatus->u32TxPoolRdPtr       = pstCecInfo->u32TxPoolRdPtr;
    pstStatus->u32TxPoolRdAbleCnt   = pstCecInfo->u32TxPoolRdAbleCnt;
//    HDMI_MUTEX_UNLOCK(pstCecInfo->stTxMute);
//    HDMI_MUTEX_LOCK(pstCecInfo->stRxMute);
    /* rx */
    pstStatus->u32RxMsgCnt          = pstCecInfo->u32RxMsgCnt;
    pstStatus->u32RxRecordWtPtr     = pstCecInfo->u32RxRecordWtPtr;

    pstStatus->u32RxPoolWtPtr       = pstCecInfo->u32RxPoolWtPtr;
    pstStatus->u32RxPoolRdPtr       = pstCecInfo->u32RxPoolRdPtr;
    pstStatus->u32RxPoolRdAbleCnt   = pstCecInfo->u32RxPoolRdAbleCnt;

//    HDMI_MUTEX_UNLOCK(pstCecInfo->stRxMute);

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_CecRecordMsgGet(HDMI_DEVICE_ID_E enHdmiId,CEC_ELEM_IDX_S *pstIdx,CEC_MSG_ELEM_S *pstElem)
{
    HI_U32              u32TmpIdx = 0;
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstIdx);
    CEC_NULL_CHK(pstElem);
    CEC_NULL_CHK(pstCecInfo);
    CEC_INIT_CHK(pstCecInfo);

    pstIdx->u32Idx %= CEC_MAX_MSG_NUM;
    if (pstIdx->enType == CEC_MSG_TYPE_SENT)
    {
        if (pstIdx->u32Idx > pstCecInfo->u32TxMsgCnt)
        {
            HDMI_WARN("cec idx > sentcnt,fail!\n");
            return HI_FAILURE;
        }
        else
        {
            if (pstCecInfo->u32TxMsgCnt <= CEC_MAX_MSG_NUM)
            {
                u32TmpIdx = pstIdx->u32Idx;
            }
            else
            {
                u32TmpIdx = (pstCecInfo->u32TxRecordWtPtr + pstIdx->u32Idx ) % CEC_MAX_MSG_NUM;
            }
        }
        HDMI_MEMCPY(pstElem,&pstCecInfo->stTxRecord[u32TmpIdx],sizeof(CEC_MSG_ELEM_S));

    }
    else if (pstIdx->enType == CEC_MSG_TYPE_RECV)
    {
        if (pstIdx->u32Idx > pstCecInfo->u32RxMsgCnt)
        {
            HDMI_WARN("cec idx > rx cnt,fail!\n");
            return HI_FAILURE;
        }
        else
        {
            if (pstCecInfo->u32RxMsgCnt <= CEC_MAX_MSG_NUM)
            {
                u32TmpIdx = pstIdx->u32Idx;
            }
            else
            {
                u32TmpIdx = (pstCecInfo->u32RxRecordWtPtr + pstIdx->u32Idx ) % CEC_MAX_MSG_NUM;
            }
        }
        HDMI_MEMCPY(pstElem,&pstCecInfo->stRxRecord[u32TmpIdx],sizeof(CEC_MSG_ELEM_S));

    }
    else
    {
        HDMI_WARN("cec unknow msg type %u,fail\n",pstIdx->enType);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_HDMI_CecDeviceTypeSet(HDMI_DEVICE_ID_E enHdmiId, HI_BOOL bIsTuner)
{
    CEC_INFO_S          *pstCecInfo = CecInfoPtrGet(enHdmiId);

    CEC_NULL_CHK(pstCecInfo);
    pstCecInfo->bIsTuner = bIsTuner;

    return HI_SUCCESS;
}


