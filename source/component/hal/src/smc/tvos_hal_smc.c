/***********************************************************************************
*              Copyright 2015 - 2025, skyworth . Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tvos_hal_smc.c
* Description:
*
* History:
* Version   Date               Author     DefectNum    Description
* main\1    2015-09-23         hhc        NULL         Create this file.
***********************************************************************************/

#define LOG_TAG "smc"

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#ifdef ANDROID_OS
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#include <hardware/hardware.h>
#endif

#include "tvos_hal_smc.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_common.h"

#include "hi_type.h"
#include "hi_unf_sci.h"
#include "hi_unf_ecs.h"

#ifndef __unused
#define __unused
#endif

/*****************************************************************************/
#define  SMC_MODE_ID                    (0x1f02)

#define  SMC_DEVICE_NUM                 (2)
#define  SMC_DEVICE_STATUS_RETRY_TIMES  (5)
#define  SMC_SRRETRY_TIMES              (3)
#define  SMC_MAX_RESP_LENGTH             256     /* max response length */

/*通讯超时时间*/
#define  SMC_SR_TIMEOUT                 1500 //750

#define SMC_CMD_HEAD_LENGTH     5
#define SMC_CLA_OFFSET          0
#define SMC_INS_OFFSET          1
#define SMC_P1_OFFSET           2
#define SMC_P2_OFFSET           3
#define SMC_P3_OFFSET           4

#define SMC_CHECK_PTR(ptr)\
    do{\
        if (NULL == ptr)\
        {\
            HAL_ERROR("ERROR_NULL_PTR");\
            return ERROR_NULL_PTR;\
        }\
    }while(0)

#define SMC_CHECK_INIT()\
    do{\
        if (FALSE == s_smc_init)\
        {\
            HAL_ERROR("ERROR_NOT_INITED");\
            return ERROR_NOT_INITED;\
        }\
    }while(0)

#define HAL_SMC_PORT_TO_SDK(hal_port, sdk_port) \
    do { \
        switch ((hal_port)) \
        { \
            case SMC_PORT0: \
                (sdk_port) = HI_UNF_SCI_PORT0; \
                break; \
            case SMC_PORT1: \
                (sdk_port) = HI_UNF_SCI_PORT1; \
                break; \
            default: \
                (sdk_port) = HI_UNF_SCI_PORT0; \
                break; \
        } \
    } while (0)

#define SMC_SET_RETURN(code) {ret = code;}

#define SMC_LOCK()    pthread_mutex_lock(&s_smc_mutex)
#define SMC_UNLOCK()  pthread_mutex_unlock(&s_smc_mutex)

/*****************************************************************************/

struct smc_context_t
{
    SMC_DEVICE_S device;
    /* our private state goes below here */
};

typedef struct SMC_DEV_INFO_S
{
    HANDLE                      m_handle;
    SMC_INIT_PARA_S*            m_pinit_para;
    SMC_OPEN_PARA_S             m_open_para;
    SMC_STANDARD_E              m_enStandard;
    SMC_PROTOCOL_E              m_enProtocol;
    SMC_STATUS_E                m_smc_state;
    BOOL                        m_smc_open;
    BOOL                        m_smc_reset;
    smc_status_callback_pfn     m_smc_callback;
    pthread_t                   m_task_id;
    U8                          m_atr[256];
    U32                         m_atr_len;
} SMC_DEV_INFO_T;

#ifndef LINUX_OS
static SMC_DEVICE_S*    module_device = NULL;
#endif

static pthread_mutex_t s_smc_mutex    = PTHREAD_MUTEX_INITIALIZER;
static SMC_INIT_PARA_S s_smc_para;
static BOOL            s_smc_init     = FALSE;
static SMC_DEV_INFO_T  s_smc_info[SMC_DEVICE_NUM];

static void _smc_protocol_check(SMC_PROTOCOL_E protocol, HI_UNF_SCI_PROTOCOL_E* p_protocol, HI_U32* p_freq)
{
    switch (protocol)
    {
        case SMC_PROTOCOL_T0:
            *p_freq     = 3570;
            *p_protocol = HI_UNF_SCI_PROTOCOL_T0;
            break;

        case SMC_PROTOCOL_T1:
            *p_freq     = 3570;
            *p_protocol = HI_UNF_SCI_PROTOCOL_T1;
            break;

        case SMC_PROTOCOL_T14:
            *p_freq     = 6000;
            *p_protocol = HI_UNF_SCI_PROTOCOL_T14;
            break;

        default:
            *p_freq     = 4500;
            *p_protocol = HI_UNF_SCI_PROTOCOL_T0;
            break;
    }
}
static HI_UNF_SCI_PROTOCOL_E _smc_protocol_convert(SMC_PROTOCOL_E protocol)
{
    HI_UNF_SCI_PROTOCOL_E hi_protocol;

    switch (protocol)
    {
        case SMC_PROTOCOL_T0:
            hi_protocol = HI_UNF_SCI_PROTOCOL_T0;
            break;

        case SMC_PROTOCOL_T1:

            hi_protocol = HI_UNF_SCI_PROTOCOL_T1;
            break;

        case SMC_PROTOCOL_T14:

            hi_protocol = HI_UNF_SCI_PROTOCOL_T14;
            break;

        default:
            hi_protocol = HI_UNF_SCI_PROTOCOL_T0;
            break;
    }

    return hi_protocol;
}

static BOOL _smc_check_card_is_ird(SMC_DEV_INFO_T* p_info)
{
    if ((p_info->m_atr[4] == 'I') && (p_info->m_atr[5] == 'R') && (p_info->m_atr[6] == 'D')
        && (p_info->m_atr[7] == 'E') && (p_info->m_atr[8] == 'T') && (p_info->m_atr[9] == 'O')) /*check ird card*/
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL _smc_check_card_is_st(SMC_DEV_INFO_T* p_info)
{
    if ((p_info->m_atr[2] == 0x00) && (p_info->m_atr[3] == 0x00) && (p_info->m_atr[4] == 0x81)
        && (p_info->m_atr[5] == 0x31) && (p_info->m_atr[6] == 0xc3) && (p_info->m_atr[7] == 0x45)
        && (p_info->m_atr[8] == 0x99) && (p_info->m_atr[9] == 0x63) && (p_info->m_atr[10] == 0x74)
        && (p_info->m_atr[11] == 0x69) && (p_info->m_atr[12] == 0x19) && (p_info->m_atr[13] == 0x99))
    {
        return TRUE;
    }

    return FALSE;
}

static S32 _smc_check_card_type_td1_by_protocol(SMC_DEV_INFO_T* p_info)
{
    S32 s32Ret = 0;

    if (p_info->m_enProtocol == SMC_PROTOCOL_T14) /*if t14 card, need to check ird or cti or...*/
    {
        /*再判断是不是ird */
        if (_smc_check_card_is_ird(p_info))
        {
            p_info->m_enStandard = SMC_IRD;
        }
        else
        {
            p_info->m_enStandard = SMC_ISO;

        }
    }
    else if (p_info->m_enProtocol == SMC_PROTOCOL_T0)
    {
        /*再判断是不是ird */
        if (_smc_check_card_is_ird(p_info))
        {
            p_info->m_enStandard = SMC_IRD;
        }
        else
        {
            p_info->m_enStandard = SMC_TF;
        }
    }
    else if (p_info->m_enProtocol == SMC_PROTOCOL_T1) /*T1 card*/
    {
        p_info->m_enStandard = SMC_ISO;
    }
    else
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }

    return s32Ret;
}

static S32 _smc_check_card_type_td1(SMC_DEV_INFO_T* p_info, U8 atr_get_t)
{
    S32 s32Ret = 0;

    switch (atr_get_t)
    {
        case 0:
            if ((p_info->m_atr[2] & 0x0f) == p_info->m_enProtocol)
            {
                ;
            }
            else
            {
                s32Ret = ERROR_NOT_SUPPORTED;
            }
            break;
        case 1:
        case 2:
        case 4:
            if ((p_info->m_atr[3] & 0x0f) == p_info->m_enProtocol) /*card protocol is correct*/
            {
                s32Ret = _smc_check_card_type_td1_by_protocol(p_info);
            }
            else
            {
                s32Ret = ERROR_NOT_SUPPORTED;
            }
            break;
        case 3:
        case 6:
            if ((p_info->m_atr[4] & 0x0f) == p_info->m_enProtocol)
            {
                ;
            }
            else
            {
                s32Ret = ERROR_NOT_SUPPORTED;
            }
            break;
        case 7:
            if ((p_info->m_atr[5] & 0x0f) == p_info->m_enProtocol)
            {
                ;
            }
            else
            {
                s32Ret = ERROR_NOT_SUPPORTED;
            }
            break;

        default:
            s32Ret = ERROR_NOT_SUPPORTED;
            break;
    }

    return s32Ret;
}

static S32 _smc_check_card_type(SMC_DEV_INFO_T* p_info)
{
    U8              atr_get_t;
    S32             ret = 0;

    if (!(p_info->m_atr[1] & 0x80))  //TD1 not exist
    {
        p_info->m_enProtocol = SMC_PROTOCOL_T0;
        if ((p_info->m_atr[5] == 'D') && (p_info->m_atr[6] == 'V') && (p_info->m_atr[7] == 'N'))
        {
            p_info->m_enStandard = SMC_DVN;
            //do samething
            HAL_DEBUG("m_enStandard = SMC_DVN");
            return 0;
        }

        if ((p_info->m_atr[0] == 0x3b) && (0x60 == (p_info->m_atr[1] & 0xf0)))
        {
            p_info->m_enStandard = SMC_TF;
            HAL_DEBUG("m_enStandard = SMC_TF");
            return 0;
        }

        p_info->m_enStandard = SMC_ISO;

        HAL_DEBUG(" unkown smart card standard");

        ret = 0;/* 部分卡未能检测出卡定义，这里返回成功不关注卡定义，避免卡复位返回失败 */
    }
    else //  TD1 exist
    {
        atr_get_t = (p_info->m_atr[1] & 0x70) >> 4;
        ret = _smc_check_card_type_td1(p_info, atr_get_t);
    }

    /*判断是不是 算通的卡*/
    if (_smc_check_card_is_st(p_info))
    {
        p_info->m_enProtocol = SMC_PROTOCOL_T14;
        p_info->m_enStandard = SMC_ISO;
        HAL_DEBUG("m_enStandard SMC_ISO");
        return 0;
    }

    HAL_DEBUG("m_enStandard %d, sk_ret 0x%x", (int)p_info->m_enStandard, ret);

    return ret;
}

S32 _smc_card_status(SMC_DEV_INFO_T* pdevinfo, SMC_STATUS_E* p_status)
{
    HI_S32 ret = 0;;
    HI_UNF_SCI_PORT_E   enSciPort = HI_UNF_SCI_PORT0;
    HI_UNF_SCI_STATUS_E SciStatus = HI_UNF_SCI_STATUS_NOCARD;

    HAL_SMC_PORT_TO_SDK((pdevinfo->m_open_para.enSmcPort), enSciPort);

    ret = HI_UNF_SCI_GetCardStatus(enSciPort, &SciStatus);
    switch (SciStatus)
    {
        case  HI_UNF_SCI_STATUS_UNINIT:          /**< SCI未初始化 */
        case  HI_UNF_SCI_STATUS_FIRSTINIT:       /**< SCI初始化过程中*/
        case  HI_UNF_SCI_STATUS_NOCARD:          /**< 无卡 */
            *p_status = SMC_REMOVED;
            break;
        case  HI_UNF_SCI_STATUS_INACTIVECARD:     /**<卡未完成激活（卡无效） */
        case  HI_UNF_SCI_STATUS_WAITATR:          /**<等待ATR*/
        case  HI_UNF_SCI_STATUS_READATR:          /**<正在接收ATR*/
        case  HI_UNF_SCI_STATUS_READY:            /**<卡可以使用（卡激活） */
        case  HI_UNF_SCI_STATUS_RX:               /**<卡忙（接收数据中） */
        case  HI_UNF_SCI_STATUS_TX:               /**<卡忙（发送数据中） */
            *p_status = SMC_INSERTED;
            break;
        case  HI_UNF_SCI_STATUS_ATR_ERROR:
            *p_status = SMC_UNKNOW_ERROR;
            break;
    }
    return ret;
}

static HI_S32 _smc_send(HI_U8 u8SCIPortNo, HI_U8* pSCISendBuf, HI_U32 u32SendLength)
{
    HI_S32 s32Return = HI_FAILURE;
    HI_U8* pu8Buf = pSCISendBuf;
    HI_U32 u32Actual = 0, u32BufLength = u32SendLength;
    HI_S32 s32Retry;

    for (s32Retry = 0; s32Retry < SMC_SRRETRY_TIMES; ++s32Retry)
    {
        s32Return = HI_UNF_SCI_Send((HI_UNF_SCI_PORT_E)u8SCIPortNo, pu8Buf, u32BufLength, &u32Actual, SMC_SR_TIMEOUT);
        HAL_CHK_RETURN_NO_PRINT((HI_SUCCESS == s32Return), HI_SUCCESS);
        HAL_CHK_RETURN((u32Actual > u32BufLength), HI_FAILURE, "sci send over flow!");

        pu8Buf += u32Actual;
        u32BufLength -= u32Actual;
    }

    HAL_ERROR("sci send over flow!");

    return HI_FAILURE;
}

static HI_S32 _smc_receive (HI_U8 u8SCIPortNo, HI_U8* pSCIReceiveBuf,
                            HI_U32 u32ReceiveLength, HI_U32* pu32ActualLength)
{
    HI_S32 s32Return = HI_FAILURE;
    HI_U8* pu8Buf    = pSCIReceiveBuf;
    HI_U32 u32Actual, u32BufLength = u32ReceiveLength;
    HI_S32 s32Retry;

    memset(pSCIReceiveBuf, 0, u32ReceiveLength);
    *pu32ActualLength = 0;

    for (s32Retry = 0; s32Retry < SMC_SRRETRY_TIMES && u32BufLength > 0; ++s32Retry)
    {
        s32Return = HI_UNF_SCI_Receive((HI_UNF_SCI_PORT_E)u8SCIPortNo, pu8Buf, u32BufLength, &u32Actual, SMC_SR_TIMEOUT);
        *pu32ActualLength += u32Actual;
        HAL_CHK_RETURN_NO_PRINT((HI_SUCCESS == s32Return), HI_SUCCESS);

        HAL_ERROR("sci receive error\n");
        HAL_CHK_RETURN((*pu32ActualLength > SMC_MAX_RESP_LENGTH), HI_FAILURE, "sci receive over flow");

        pu8Buf += u32Actual;
        u32BufLength -= u32Actual;
    }

    HAL_ERROR("sci receive over flow\n");

    return HI_FAILURE;
}

static HI_S32 _smc_process_bytes(HI_UNF_SCI_PORT_E enSciPort, HI_U8 u8Ins,
                                 HI_U32* pu32TransNum, HI_U8* pu8SWBuffer)
{
    HI_S32 s32Return;
    HI_U8 u8Buff;
    HI_U32 u32Len, u32TransNum = 0;
    do
    {
        s32Return = _smc_receive( enSciPort, &u8Buff, 1, &u32Len);
        HAL_CHK_RETURN(((s32Return != HI_SUCCESS) || (u32Len != 1)), s32Return, "sci read error!");

        /*NULL : (=0x60) This byte is sent by the card to restart the working
          time, end to anticipate a subsequent procedure byte. It requests no
          further action neither on VPP nor on Data*/
        if (u8Buff == 0x60)
        {
            continue;
        }

        /*SW1 (= 0x6x or 0x9x, expect 0x60); waits for a SW2 byte to complete
          the command. We do not deal with SW, just pass them to the up layer*/
        if ((u8Buff & 0xF0) == 0x60 || (u8Buff & 0xF0) == 0x90)
        {
            pu8SWBuffer[0] = u8Buff;
            s32Return = _smc_receive( enSciPort, &u8Buff, 1, &u32Len);
            HAL_CHK_RETURN(((s32Return != HI_SUCCESS) || (u32Len != 1)), s32Return, "sci read error!");

            pu8SWBuffer[1] = u8Buff;
            *pu32TransNum = 0;
            return HI_SUCCESS;
        }

        /*notes: VPP active means programming the card, our chip don't
          supplied this function*/
        if ((u8Buff ^ u8Ins) == 0) /* ACK == INS*/
        {
            /*Vpp is idle. All remaining bytes are transfered subsequently.*/
            u32TransNum = *pu32TransNum;
        }
        else if ((u8Buff ^ u8Ins) == 0xFF) /* ACK == ~INS*/
        {
            /*Vpp is idle. Next byte is transfered subsequently.*/
            u32TransNum = (*pu32TransNum == 0) ? 0 : 1;
        }
        else if ((u8Buff ^ u8Ins) == 0x01) /* ACK == INS+1*/
        {
            /*Vpp is active. All remaining bytes are transfered subsequently.*/
            u32TransNum = *pu32TransNum;
        }
        else if ((u8Buff ^ u8Ins) == 0xFE) /* ACK == ~(INS+1)*/
        {
            /*Vpp is active. Next bytes is transfered subsequently.*/
            u32TransNum = (*pu32TransNum == 0) ? 0 : 1;
        }
        else
        {
            HAL_ERROR("cannot handle procedure!\n");
            return HI_FAILURE;
        }
    }
    while (u32TransNum == 0);

    *pu32TransNum = u32TransNum;

    return HI_SUCCESS;
}

static HI_S32 _smc_transfer_t0(SMC_DEV_INFO_T* pdevinfo __unused, HI_UNF_SCI_PORT_E enSciPort, const HI_U8* pu8Command,
                               HI_U32 u32CommandLen, HI_U8* pu8Reply,  HI_U32* pu32ReplyLen)
{
    HI_U8 bWrite;
    HI_U32 u32TransLen, u32NextTransLen, u32ActualLen;
    HI_U8 au8SWBuff[2], au8Buff[SMC_MAX_RESP_LENGTH];
    HI_S32 s32Return;
    HI_U8 u8Ins;

    HAL_CHK_RETURN(((pu8Command[SMC_CLA_OFFSET] == 0xFF)
                    || ((pu8Command[SMC_INS_OFFSET] & 0xF0) == 0x60)
                    || ((pu8Command[SMC_INS_OFFSET] & 0xF0) == 0x90)), HI_FAILURE, "unsupported command");

    u32TransLen = pu8Command[SMC_P3_OFFSET];

    if (u32CommandLen > SMC_CMD_HEAD_LENGTH)
    {
        bWrite = 1;
    }
    else
    {
        //read from sci card
        bWrite = 0;
        if (u32TransLen == 0)
        {
            //according to the iso7816 protocol
            u32TransLen = 256;
        }
    }

    u8Ins           = pu8Command[SMC_INS_OFFSET];
    u32TransLen     += SMC_CMD_HEAD_LENGTH;
    u32NextTransLen = SMC_CMD_HEAD_LENGTH;  //send cmd header frist
    *pu32ReplyLen   = 0;

    memset(au8SWBuff, 0, sizeof(au8SWBuff));
    memset(au8Buff, 0, sizeof(au8Buff));

    do
    {
        s32Return = _smc_send( enSciPort, (HI_U8*)pu8Command, u32NextTransLen);
        HAL_CHK_RETURN((HI_SUCCESS != s32Return), HI_FAILURE, "sci send error!");

        pu8Command  += u32NextTransLen;
        u32TransLen -= u32NextTransLen;
        u32NextTransLen = u32TransLen;

        s32Return = _smc_process_bytes(enSciPort, u8Ins, &u32NextTransLen, au8SWBuff);
        HAL_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Return), s32Return);

        if (u32NextTransLen == 0)
        {
            memcpy( pu8Reply, au8SWBuff, 2);
            *pu32ReplyLen = 2;

            return HI_SUCCESS;
        }
    }
    while (bWrite);

    do
    {
        s32Return = _smc_receive( enSciPort, au8Buff, u32NextTransLen, &u32ActualLen);

        //for u32NextTransLen was readed from the card by SCI_ProcessProcedureBytes
        //function, u32ActualLen must equal to u32NextTransLen, otherwise
        //there is an error we can't handle.
        HAL_CHK_RETURN(((s32Return != HI_SUCCESS) || (u32ActualLen != u32NextTransLen)), HI_FAILURE, "sci send error!");

        memcpy((pu8Reply + *pu32ReplyLen), au8Buff, u32ActualLen);
        *pu32ReplyLen += u32ActualLen;

        u32TransLen -= u32NextTransLen;
        u32NextTransLen = u32TransLen;

        s32Return = _smc_process_bytes(enSciPort, u8Ins, &u32NextTransLen, au8SWBuff);
        HAL_CHK_RETURN_NO_PRINT((HI_SUCCESS != s32Return), s32Return);

        if (u32NextTransLen == 0)
        {
            if (u32TransLen == 0)
            {
                memcpy( (pu8Reply + *pu32ReplyLen) , au8SWBuff, 2);
                *pu32ReplyLen += 2;

                return HI_SUCCESS;
            }
            else
            {
                return HI_FAILURE;
            }
        }
    }
    while (u32TransLen > 0);

    return HI_FAILURE;
}

static HI_S32 _smc_transfer_t1(SMC_DEV_INFO_T* pdevinfo __unused, HI_UNF_SCI_PORT_E enSciPort, U8* pu8Command,
                               U32 u32CommandLen, U8* pu8Reply, U32* pu32ReplyLen)
{
    HI_S32  s32Ret;
    HI_U32  u32ActLen = 0;
    HI_U32  u32TotalReadLen = 0;
    HI_U8   RecBuff[SMC_MAX_RESP_LENGTH];

    s32Ret = _smc_send(enSciPort , pu8Command, u32CommandLen);
    HAL_CHK_RETURN_NO_PRINT((s32Ret != HI_SUCCESS), s32Ret);

    memset(RecBuff, 0x00, SMC_MAX_RESP_LENGTH);

    u32TotalReadLen = 0;
    while (u32TotalReadLen < *pu32ReplyLen)
    {
        if (SMC_MAX_RESP_LENGTH <= u32TotalReadLen)
        {
            break;
        }

        s32Ret = _smc_receive(enSciPort, &RecBuff[u32TotalReadLen], 1, &u32ActLen);
        HAL_CHK_RETURN_NO_PRINT((s32Ret != HI_SUCCESS), s32Ret);

        if (0x60 == RecBuff[u32TotalReadLen])
        {
            //printf("drop 0x60\n");
            continue;
        }

        u32TotalReadLen++;
    }

    memcpy(pu8Reply, RecBuff, u32TotalReadLen);
    *pu32ReplyLen = u32TotalReadLen;

    return s32Ret;
}

static HI_S32 _smc_transfer_t14(SMC_DEV_INFO_T* pdevinfo, HI_UNF_SCI_PORT_E enSciPort, U8* pu8Command,
                                U32 u32CommandLen, U8* pu8Reply, U32* pu32ReplyLen)
{
    HI_S32  s32Ret;
    HI_U32  u32ActLen = 0;
    HI_U8   RecBuff[SMC_MAX_RESP_LENGTH];
    HI_U32  TotalRead;
    HI_U32  NextReadSize = 0;
    HI_U8   u8T14SciFirstReadSize      = 9;
    HI_U8   u8T14SciSecondReadSizeAddr = 7;

    if (pdevinfo->m_enStandard == SMC_IRD && pdevinfo->m_enProtocol == SMC_PROTOCOL_T14)
    {
        u8T14SciFirstReadSize        = 9;
        u8T14SciSecondReadSizeAddr   = 7;
    }
    else
    {
        u8T14SciFirstReadSize      = 4;
        u8T14SciSecondReadSizeAddr = 2;
    }

    s32Ret = _smc_send(enSciPort , pu8Command, u32CommandLen);
    HAL_CHK_RETURN_NO_PRINT((s32Ret != HI_SUCCESS), s32Ret);

    TotalRead = 0;
    u32ActLen = 0;

    //开始读前4个字节
    s32Ret = _smc_receive(enSciPort, RecBuff, u8T14SciFirstReadSize, &u32ActLen);
    HAL_CHK_RETURN_NO_PRINT((s32Ret != HI_SUCCESS), s32Ret);

    TotalRead += u32ActLen;

    NextReadSize = RecBuff[u8T14SciSecondReadSizeAddr];
    if (NextReadSize != 0) /*不为零才需要第二次读取*/
    {
        //再读后lc个字节
        s32Ret = _smc_receive(enSciPort, RecBuff + u8T14SciFirstReadSize, NextReadSize, &u32ActLen);
        HAL_CHK_RETURN_NO_PRINT((s32Ret != HI_SUCCESS), s32Ret);

        TotalRead += u32ActLen;
    }

    *pu32ReplyLen = TotalRead;
    memcpy(pu8Reply, RecBuff, TotalRead);

    return HI_SUCCESS;
}

static void _event_smc_task(void* ptr)
{
    S32             ret;
    SMC_STATUS_E    status;
    SMC_STATUS_E    last_status = SMC_TERM;
    SMC_DEV_INFO_T* pdevinfo = (SMC_DEV_INFO_T*)ptr;
    unsigned int    cnt    = 0;

    while (pdevinfo->m_smc_open)
    {
        ret = _smc_card_status(pdevinfo, &status);
        if ((0 != ret) || (status == last_status))
        {
            usleep(50 * 1000);
            cnt = 0;
            continue;
        }

        if ((pdevinfo->m_smc_callback) && (cnt >= 3))
        {
            pdevinfo->m_smc_callback(pdevinfo->m_handle, status);

            SMC_LOCK();
            pdevinfo->m_smc_state = status;
            SMC_UNLOCK();

            last_status = status;
            cnt = 0;

            if (status == SMC_INSERTED)
            {
                HAL_DEBUG(("callback smc inserted"));
            }
            else
            {
                HAL_DEBUG(("callback smc removed"));
            }
        }

        cnt++;
        usleep(50 * 1000);
    }

    pthread_detach(pthread_self());

    return;
}

static S32 sk_hdi_smc_init(struct _SMC_DEVICE_S* pstDev, const SMC_INIT_PARA_S* const pstInitPara)
{
    S32          ret = 0;
    HI_S32       hi_ret;
    S32          i = 0;

    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pstInitPara);

    SMC_LOCK();

    do
    {
        if (s_smc_init)
        {
            HAL_DEBUG("already init");
            SMC_SET_RETURN(0);
            break;
        }

        memcpy(&s_smc_para, pstInitPara, sizeof(SMC_INIT_PARA_S));
        hi_ret = HI_UNF_SCI_Init();

        if (hi_ret != HI_SUCCESS)
        {
            HAL_ERROR("HI_UNF_SCI_Init fail 0x%x", hi_ret);
            SMC_SET_RETURN(-ENXIO);
            break;
        }

        memset(s_smc_info, 0, sizeof(SMC_DEV_INFO_T)*SMC_DEVICE_NUM);

        for (i = 0; i < SMC_DEVICE_NUM; i++)
        {
            s_smc_info[i].m_smc_open   = FALSE;
            s_smc_info[i].m_pinit_para = &s_smc_para;
        }

        s_smc_init = TRUE;
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32 smc_get_index(HANDLE handle, U32* ptindex)
{
    U32 index = 0;

    if (NULL == ptindex)
    {
        HAL_ERROR("smc ptindex is null\n");
        return FAILURE;
    }

    if (SMC_MODE_ID != (handle >> 16))
    {
        HAL_ERROR("smc handle is invalid\n");
        return FAILURE;
    }

    index = (handle & 0xffff);
    if (index >= SMC_DEVICE_NUM)
    {
        HAL_ERROR("smc handle is invalid\n");
        return FAILURE;
    }

    *ptindex = index;
    return SUCCESS;
}

static S32 _smc_open(struct _SMC_DEVICE_S* pstDev, HANDLE* const  pHandle,
                     const SMC_OPEN_PARA_S* const pstOpenPara)

{
    S32                   ret = 0;
    HI_S32                hi_ret;
    SMC_DEV_INFO_T*        pdevinfo = NULL;
    //HI_UNF_SCI_PORT_E     enSciPort;
    HI_UNF_SCI_PROTOCOL_E enSciProtocol;
    HI_U32                u32Frequency = 0;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pHandle);
    SMC_CHECK_PTR(pstOpenPara);

    SMC_LOCK();

    do
    {
        if ((U32)(pstOpenPara->enSmcPort) >= SMC_DEVICE_NUM)
        {
            HAL_ERROR("enSmcPort %d", pstOpenPara->enSmcPort);
            SMC_SET_RETURN(ERROR_INVALID_PARAM);
            break;
        }

        pdevinfo = &s_smc_info[pstOpenPara->enSmcPort];

        if (pdevinfo->m_smc_open)
        {
            HAL_DEBUG("enSmcPort %d already open", pstOpenPara->enSmcPort);
            SMC_SET_RETURN(0);
            break;
        }

        _smc_protocol_check(pdevinfo->m_pinit_para->enProtocol, &enSciProtocol, &u32Frequency);

        HAL_DEBUG("enSciProtoco %d u32freq    %d", enSciProtocol, u32Frequency);
        HAL_DEBUG("u32SmcClk %d u32SmcEtu %d u32SmcBaud %d", pdevinfo->m_pinit_para->u32SmcClk,
                  pdevinfo->m_pinit_para->u32SmcEtu,
                  pdevinfo->m_pinit_para->u32SmcBaud);

        hi_ret = HI_UNF_SCI_Open((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort, enSciProtocol, u32Frequency);
        if (hi_ret != HI_SUCCESS)
        {
            HAL_ERROR("HI_UNF_SCI_Open fail 0x%x", hi_ret);
            SMC_SET_RETURN(-ENXIO);
            break;
        }

        (void)HI_UNF_SCI_ConfigVccEn((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort, (HI_UNF_SCI_LEVEL_E)pdevinfo->m_pinit_para->enSmcVcc);//LOW
        (void)HI_UNF_SCI_ConfigDetect((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort, (HI_UNF_SCI_LEVEL_E)pdevinfo->m_pinit_para->enSmcDetect); //HIGH
        (void)HI_UNF_SCI_ConfigClkMode((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort,   HI_UNF_SCI_MODE_CMOS);
        (void)HI_UNF_SCI_ConfigVccEnMode((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort, HI_UNF_SCI_MODE_CMOS);
        (void)HI_UNF_SCI_ConfigResetMode((HI_UNF_SCI_PORT_E)pstOpenPara->enSmcPort, HI_UNF_SCI_MODE_CMOS);

        HAL_DEBUG("VccEn %d Detect %d", pdevinfo->m_pinit_para->enSmcVcc, pdevinfo->m_pinit_para->enSmcDetect);

        pdevinfo->m_open_para.enSmcPort = pstOpenPara->enSmcPort;
        pdevinfo->m_smc_state           = SMC_TERM;
        pdevinfo->m_smc_open            = TRUE;
        pdevinfo->m_smc_reset           = FALSE;
        pdevinfo->m_enProtocol          = pdevinfo->m_pinit_para->enProtocol;
        pdevinfo->m_enStandard          = pdevinfo->m_pinit_para->enStandard;
        pdevinfo->m_handle              = ((SMC_MODE_ID << 16) | (pstOpenPara->enSmcPort));
        *pHandle                        = pdevinfo->m_handle;

        pthread_create(&pdevinfo->m_task_id , NULL, (HI_VOID*)_event_smc_task, (void*)pdevinfo);
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32 _smc_close(struct _SMC_DEVICE_S* pstDev, const HANDLE handle)

{
    S32                   ret = 0;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (FAILURE == ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        if (pdevinfo->m_smc_open == FALSE)
        {
            HAL_DEBUG("enSmcPort %d already close", pdevinfo->m_open_para.enSmcPort);
            SMC_SET_RETURN(0);
            break;
        }

        pdevinfo->m_smc_open      = FALSE;
        pdevinfo->m_smc_callback  = NULL;
        pdevinfo->m_smc_state     = SMC_TERM;
        pdevinfo->m_smc_reset     = FALSE;
        usleep(100 * 1000);
        (VOID)HI_UNF_SCI_Close((HI_UNF_SCI_PORT_E)(pdevinfo->m_open_para.enSmcPort));
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32 smc_term(struct _SMC_DEVICE_S* pstDev, const SMC_TERM_PARAMS_S* const  pstTermParams __unused)
{
    S32          ret = 0;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    do
    {
        if (s_smc_init)
        {
            s_smc_init = FALSE;
            memset(s_smc_info, 0, sizeof(SMC_DEV_INFO_T)*SMC_DEVICE_NUM);
            HI_UNF_SCI_DeInit();
        }
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32 smc_get_info(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, SMC_INFO_S* pstSmcInfo)
{
    S32                   ret = 0;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pstSmcInfo);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (FAILURE == ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        pstSmcInfo->enStandard = pdevinfo->m_enStandard;
        pstSmcInfo->enProtocol = pdevinfo->m_enProtocol;
        pstSmcInfo->enStatus   = pdevinfo->m_smc_state;
        pstSmcInfo->u32SmcBaud = pdevinfo->m_pinit_para->u32SmcBaud;
        pstSmcInfo->u32SmcEtu  = pdevinfo->m_pinit_para->u32SmcEtu;
        pstSmcInfo->u32SmcClk  = pdevinfo->m_pinit_para->u32SmcClk;

    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32 smc_status_register_callback(struct _SMC_DEVICE_S* pstDev, const HANDLE   handle,
                                        const smc_status_callback_pfn pfnCallBack)

{
    S32                   ret = 0;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (FAILURE == ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        pdevinfo->m_smc_callback = pfnCallBack;
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32  smc_reset_card(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, const SMC_PROTOCOL_E enProtocol)
{
    S32                    ret = 0;
    HI_S32                 hi_ret;
    U32                    index = 0;
    SMC_DEV_INFO_T*        pdevinfo = NULL;
    HI_U32                 u32Frequency;
    HI_S32                 s32Times = 0;
    HI_UNF_SCI_PORT_E      enSciPort;
    HI_UNF_SCI_STATUS_E    u32Status;
    HI_UNF_SCI_PROTOCOL_E  enSciProtocol;
    HI_UNF_SCI_STATUS_E    u32CardStatus;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (FAILURE == ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        HAL_SMC_PORT_TO_SDK((pdevinfo->m_open_para.enSmcPort), enSciPort);
        hi_ret = HI_UNF_SCI_GetCardStatus(enSciPort, &u32Status);

        if (hi_ret != HI_SUCCESS)
        {
            HAL_ERROR("HI_UNF_SCI_GetCardStatus fail 0x%x", hi_ret);
            SMC_SET_RETURN(-EBUSY);
            break;
        }

        if ((HI_UNF_SCI_STATUS_UNINIT == u32Status) ||
            (HI_UNF_SCI_STATUS_NOCARD == u32Status))
        {
            HAL_ERROR("NO CARD IN");
            SMC_SET_RETURN(-ENXIO);
            break;
        }

        if (pdevinfo->m_enProtocol != enProtocol)
        {
            _smc_protocol_check(enProtocol, &enSciProtocol, &u32Frequency);

            HAL_DEBUG("enSciPort %d enSciProtoco %d u32freq %d", enSciPort, enSciProtocol, u32Frequency);
            HI_UNF_SCI_Close(enSciPort);
            hi_ret = HI_UNF_SCI_Open(enSciPort, enSciProtocol, u32Frequency);

            if (hi_ret != HI_SUCCESS)
            {
                HAL_ERROR("HI_UNF_SCI_Open fail 0x%x", hi_ret);
                SMC_SET_RETURN(-ENXIO);
                break;
            }

            pdevinfo->m_enProtocol = enProtocol;
            usleep(50 * 1000);
        }

        hi_ret = HI_UNF_SCI_ResetCard(enSciPort, HI_FALSE);

        if (hi_ret != HI_SUCCESS)
        {
            HAL_ERROR("HI_UNF_SCI_ResetCard fail 0x%x", hi_ret);
            SMC_SET_RETURN(-EAGAIN);
            break;
        }

        while (s32Times++ < SMC_DEVICE_STATUS_RETRY_TIMES) //wait 2.5s
        {
            (VOID)HI_UNF_SCI_GetCardStatus(enSciPort, &u32CardStatus);

            if (u32CardStatus >= HI_UNF_SCI_STATUS_READY)
            {
                break;
            }

            usleep(500 * 1000);
        }

        if (s32Times == SMC_DEVICE_STATUS_RETRY_TIMES)
        {
            HAL_ERROR("reset card failed");
            SMC_SET_RETURN(-EAGAIN);
            break;
        }

        s32Times = 0;

        do
        {
            hi_ret = HI_UNF_SCI_GetATR(enSciPort, pdevinfo->m_atr, 255, (HI_U8*)&pdevinfo->m_atr_len);

            if (hi_ret != HI_SUCCESS)
            {
                usleep(500 * 1000);
                s32Times++;
            }
        }
        while (hi_ret != HI_SUCCESS && s32Times <= 8 /*waiting 4s*/);

        if (hi_ret != HI_SUCCESS)
        {
            HAL_ERROR("HI_UNF_SCI_GetATR fail ret 0x%x", (int)hi_ret);
            SMC_SET_RETURN(-EAGAIN);
            break;
        }

        _smc_check_card_type(pdevinfo);
        pdevinfo->m_smc_state = SMC_RESET_COMPLETE;
        pdevinfo->m_smc_reset = TRUE;

        HAL_DEBUG("------>reset card ok s32Times(%d)", s32Times);
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32 smc_send(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32len, U8* pu8Buf,
                    U32* pu32SendLen, U32 u32Timeout __unused)

{
    S32                   ret = 0;
    HI_S32                s32Ret;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;
    HI_UNF_SCI_STATUS_E   u32CardStatus;
    HI_UNF_SCI_PORT_E     enSciPort;
    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pu8Buf);
    SMC_CHECK_PTR(pu32SendLen);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (FAILURE == ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        HAL_SMC_PORT_TO_SDK((pdevinfo->m_open_para.enSmcPort), enSciPort);

        s32Ret = HI_UNF_SCI_GetCardStatus(enSciPort, &u32CardStatus);
        if (s32Ret != HI_SUCCESS || u32CardStatus < HI_UNF_SCI_STATUS_READY)
        {
            HAL_ERROR("HI_UNF_SCI_GetCardStatus s32Ret = 0x%x", s32Ret);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

        s32Ret = _smc_send(enSciPort, pu8Buf , u32len);
        if (s32Ret != HI_SUCCESS)
        {
            HAL_ERROR("_smc_send s32Ret = 0x%x", s32Ret);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

        *pu32SendLen = u32len;
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32 smc_receive(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32Len, U8* pu8Buf,
                       U32* pu32ReceiveLen, U32 u32Timeout __unused)
{
    S32                   ret = 0;
    HI_S32                s32Ret;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;
    HI_UNF_SCI_STATUS_E   u32CardStatus;
    HI_UNF_SCI_PORT_E     enSciPort;
    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pu8Buf);
    SMC_CHECK_PTR(pu32ReceiveLen);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (SUCCESS != ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        HAL_SMC_PORT_TO_SDK((pdevinfo->m_open_para.enSmcPort), enSciPort);

        s32Ret = HI_UNF_SCI_GetCardStatus(enSciPort, &u32CardStatus);
        if (s32Ret != HI_SUCCESS || u32CardStatus < HI_UNF_SCI_STATUS_READY)
        {
            HAL_ERROR("HI_UNF_SCI_GetCardStatus s32Ret = 0x%x", s32Ret);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

        s32Ret = _smc_receive(enSciPort, pu8Buf, u32Len, (HI_U32*)pu32ReceiveLen);
        if (s32Ret != HI_SUCCESS)
        {
            HAL_ERROR("_smc_receive s32Ret = 0x%x", s32Ret);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32  smc_transfer(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32SendLen, U8* pu8SendBuf,
                         U32* pu32ReceiveLen, U8* pu8ReceiveBuf, U32 u32Timeout __unused)
{
    S32                   ret = 0;
    HI_S32                s32Ret;
    U32                   index = 0;
    SMC_DEV_INFO_T*       pdevinfo = NULL;
    HI_UNF_SCI_STATUS_E   u32CardStatus;
    HI_UNF_SCI_PORT_E     enSciPort;
    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pu8SendBuf);
    SMC_CHECK_PTR(pu32ReceiveLen);
    SMC_CHECK_PTR(pu8ReceiveBuf);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (SUCCESS != ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        HAL_SMC_PORT_TO_SDK((pdevinfo->m_open_para.enSmcPort), enSciPort);

        s32Ret = HI_UNF_SCI_GetCardStatus(enSciPort, &u32CardStatus);
        if (s32Ret != HI_SUCCESS || u32CardStatus < HI_UNF_SCI_STATUS_READY)
        {
            HAL_ERROR("HI_UNF_SCI_GetCardStatus s32Ret = 0x%x", s32Ret);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

        switch (pdevinfo->m_enProtocol)
        {
            case SMC_PROTOCOL_T1:
            {
                /* T1协议处理 */
                s32Ret = _smc_transfer_t1(pdevinfo, enSciPort,
                                          pu8SendBuf, u32SendLen,
                                          pu8ReceiveBuf,  pu32ReceiveLen);
            }
            break;

            case SMC_PROTOCOL_T14:
            {
                /* T14协议处理 */
                s32Ret = _smc_transfer_t14(pdevinfo, enSciPort,
                                           pu8SendBuf, u32SendLen,
                                           pu8ReceiveBuf,  pu32ReceiveLen);
            }
            break;

            case SMC_PROTOCOL_T0:
            default:
            {
                /* T0协议处理 */
                s32Ret = _smc_transfer_t0(pdevinfo, enSciPort,
                                          pu8SendBuf, u32SendLen,
                                          pu8ReceiveBuf, (HI_U32*)pu32ReceiveLen);
            }
            break;
        }

        if (s32Ret != HI_SUCCESS)
        {
            HAL_ERROR("smc_transfer failed");
            SMC_SET_RETURN(-ENOSYS);
        }
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32  smc_get_atr(struct _SMC_DEVICE_S* pstDev, const HANDLE handle,
                        U8* pu8Len, U8* pu8Buf, U32 u32Timeout __unused)
{
    S32                    ret = 0;
    U32                    index = 0;
    SMC_DEV_INFO_T*        pdevinfo = NULL;
    SMC_STATUS_E           status;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pu8Len);
    SMC_CHECK_PTR(pu8Buf);

    SMC_LOCK();

    ret = smc_get_index(handle, &index);
    if (SUCCESS != ret)
    {
        SMC_UNLOCK();
        return ret;
    }

    pdevinfo = &s_smc_info[index];

    do
    {
        if (pdevinfo->m_smc_reset && pdevinfo->m_smc_state >= SMC_RESET_COMPLETE)
        {
            memcpy(pu8Buf, pdevinfo->m_atr, pdevinfo->m_atr_len);
            *pu8Len  =  pdevinfo->m_atr_len;
        }
        else
        {
            _smc_card_status(pdevinfo, &status);
            if (status == SMC_INSERTED)
            {
                pdevinfo->m_smc_state = SMC_UNKNOW_ERROR;
            }
            else
            {
                pdevinfo->m_smc_state = SMC_REMOVED;
            }

            HAL_ERROR("smc_get_atr fail");
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

        HAL_DEBUG("------>smc_get_atr  ok");

    }
    while (0);

    SMC_UNLOCK();

    return ret;
}
static S32  smc_set_para_from_atr(struct _SMC_DEVICE_S* pstDev, const HANDLE handle __unused,
                                  U8* pu8Buf __unused, U32 u32Len __unused)
{
    S32          ret = 0;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    do
    {
        ret = ERROR_NOT_SUPPORTED;
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32  smc_get_active(struct _SMC_DEVICE_S* pstDev, HANDLE* const pHandle, SMC_PORT_E enSmcPort)
{
    S32              ret = 0;
    SMC_DEV_INFO_T*  pdevinfo;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);
    SMC_CHECK_PTR(pHandle);

    SMC_LOCK();

    do
    {
        if (((U32)enSmcPort) >= SMC_DEVICE_NUM)
        {
            HAL_ERROR("enSmcPort %d", enSmcPort);
            SMC_SET_RETURN(ERROR_INVALID_PARAM);
            break;
        }

        pdevinfo = &s_smc_info[enSmcPort];

        if (pdevinfo->m_smc_open)
        {
            *pHandle = pdevinfo->m_handle;
        }
        else
        {
            HAL_ERROR("enSmcPort %d not open", enSmcPort);
            SMC_SET_RETURN(-ENOSYS);
            break;
        }

    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

static S32  smc_flush(struct _SMC_DEVICE_S* pstDev, const HANDLE handle __unused)
{
    S32          ret = 0;

    SMC_CHECK_INIT();
    SMC_CHECK_PTR(pstDev);

    SMC_LOCK();

    do
    {
        ret = ERROR_NOT_SUPPORTED;
    }
    while (0);

    SMC_UNLOCK();

    return ret;
}

#ifdef TVOS_PLATFORM
static int smc_device_close(struct hw_device_t* dev)
{
    struct smc_context_t* ctx = (struct smc_context_t*)dev;
    if (ctx)
    {
        free(ctx);
    }

    module_device = NULL;

    return 0;
}

/*****************************************************************************/

static int smc_device_open(const struct hw_module_t* module, const char* name,
                           struct hw_device_t** device)
{
    int status = -EINVAL;

    if (!strcmp(name, SMC_HARDWARE_SMC0))
    {

        struct smc_context_t* dev = NULL;

        if (NULL == device)
        {
            return FAILURE;
        }

        if (module_device != NULL)
        {
            *device = (hw_device_t*)module_device;
            return 0;
        }

        dev = (struct smc_context_t*)malloc(sizeof(*dev));
        if (NULL == dev)
        {
            return FAILURE;
        }

        /* initialize our state here */
        memset(dev, 0, sizeof(*dev));

        /* initialize the procs */
        dev->device.stCommon.tag     = HARDWARE_DEVICE_TAG;
        dev->device.stCommon.version = 1;
        dev->device.stCommon.module  = (hw_module_t*)(module);
        dev->device.stCommon.close   = smc_device_close;

        dev->device.sk_hdi_smc_init         = sk_hdi_smc_init;
        dev->device.smc_open                = _smc_open;
        dev->device.smc_close               = _smc_close;
        dev->device.smc_term                = smc_term;
        dev->device.smc_get_info            = smc_get_info;
        dev->device.smc_status_register_callback  = smc_status_register_callback;
        dev->device.smc_reset_card          = smc_reset_card;
        dev->device.smc_send                = smc_send;
        dev->device.smc_receive             = smc_receive;
        dev->device.smc_transfer            = smc_transfer;
        dev->device.smc_get_atr             = smc_get_atr;
        dev->device.smc_set_para_from_atr   = smc_set_para_from_atr;
        dev->device.smc_get_active          = smc_get_active;
        dev->device.smc_flush               = smc_flush;

        *device = &dev->device.stCommon;

        module_device = (SMC_DEVICE_S*)&dev->device.stCommon;;

        status = 0;
    }

    return status;
}

static struct hw_module_methods_t smc_module_methods =
{
open:
    smc_device_open
};

SMC_MODULE_S HAL_MODULE_INFO_SYM =
{
common:
    {
    tag:
        HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
    id:
        SMC_HARDWARE_MODULE_ID,
    name: "The smc module"
        ,
    author: "The Skyworth' hhc"
        ,
    methods:
        & smc_module_methods,
    }
};
#endif

static SMC_DEVICE_S s_stDevice_smc =
{
    .sk_hdi_smc_init         = sk_hdi_smc_init,
    .smc_open                = _smc_open,
    .smc_close               = _smc_close,
    .smc_term                = smc_term,
    .smc_get_info            = smc_get_info,
    .smc_status_register_callback  = smc_status_register_callback,
    .smc_reset_card          = smc_reset_card,
    .smc_send                = smc_send,
    .smc_receive             = smc_receive,
    .smc_transfer            = smc_transfer,
    .smc_get_atr             = smc_get_atr,
    .smc_set_para_from_atr   = smc_set_para_from_atr,
    .smc_get_active          = smc_get_active,
    .smc_flush               = smc_flush,
};

SMC_DEVICE_S* getSmcDevice()
{
    return &s_stDevice_smc;
}

