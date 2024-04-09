/******************************************************************************
 Copyright (C), 20016-2026, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hdmi_test_cec.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2010/07/08
Last Modified :
Description   : HDMI TEST CEC interface
Function List :
History       :
******************************************************************************/
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "hi_adp.h"
#include "hi_adp_hdmi.h"
#include "hdmi_test_cec.h"

/******************************************************************************/
/* Macro define                                                               */
/******************************************************************************/
#define CEC_MESSAGE_RETURN_OK_WITH_RESPONES     0x01
#define CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES  0x02
#define CEC_MESSAGE_RETURN_ERROR_NOSUPPORT      0x03
#define CEC_MESSAGE_RETURN_BUTT                 0x04

//cec power status
#define CEC_POWER_STATUS_ON                     0x00
#define CEC_POWER_STATUS_STANDBY                0x01
#define CEC_POWER_STATUS_STANDBY2ON             0x02
#define CEC_POWER_STATUS_ON2STANDBY             0x03

#define CEC_READY_TIME                          1000

#define HDMI_TEST_CEC_LOG(fmt...) \
do { \
    if(HI_TRUE == s_stCecCtx.bLogView) \
    { \
        printf(fmt); \
    } \
}while(0);
/******************************************************************************/
/* Global Data                                                                */
/******************************************************************************/
static HI_S32      g_cecCmdId = 1;
static HI_U8       g_cecPowerStatus = CEC_POWER_STATUS_ON;

static HDMI_TEST_CEC_S s_stCecCtx;


/******************************************************************************/
/* Public Interface                                                           */
/******************************************************************************/
HI_VOID HDMI_CEC_LogSet(HI_BOOL bLogView)
{
    s_stCecCtx.bLogView = bLogView;

    return;
}

/*
**  Print CEC cmd
*/
HI_VOID HDMI_CEC_PrintCmd(HI_UNF_HDMI_CEC_CMD_S *pstCECCmd)
{
    HI_U32 i;

    HDMI_TEST_CEC_LOG("\n==============================================================================\n");
    HDMI_TEST_CEC_LOG("Cec Cmd Index: %d \n", g_cecCmdId++);
    HDMI_TEST_CEC_LOG("SrcAddr :0x%x  ", pstCECCmd->enSrcAdd);
    HDMI_TEST_CEC_LOG("DstAddr :0x%x\n", pstCECCmd->enDstAdd);
    HDMI_TEST_CEC_LOG("OpCode  :0x%x\n", pstCECCmd->u8Opcode);
#if !defined (HDMI_FORCE_RAWDATA)
    if (CEC_OPCODE_USER_CONTROL_PRESSED == pstCECCmd->u8Opcode)
    {
        HDMI_TEST_CEC_LOG("UICommand:0x%x\n", pstCECCmd->unOperand.stUIOpcode);
    }
    else
#endif
    {
        HDMI_TEST_CEC_LOG("cmd len :0x%x\nOpData  :", pstCECCmd->unOperand.stRawData.u8Length);
        for(i = 0;i < pstCECCmd->unOperand.stRawData.u8Length; i++)
        {
            HDMI_TEST_CEC_LOG("0x%x ", pstCECCmd->unOperand.stRawData.u8Data[i]);
        }
        HDMI_TEST_CEC_LOG("\n");
    }

    return ;
}

/*
**  Parse CEC message
*/
HI_U32 HDMI_CEC_MsgParse(HI_UNF_HDMI_CEC_CMD_S *pCECCmdGet,HI_UNF_HDMI_CEC_CMD_S *pCECCmdSet)
{
    //Default Return is Error NoSupprot!
    HI_U32 Ret = CEC_MESSAGE_RETURN_ERROR_NOSUPPORT;
    HI_U32 Rec;
    HI_UNF_HDMI_CEC_STATUS_S  stCECStatus;
    HI_U8  Init, Dest, opcode, OperandLength;
    HI_U8  *pOperand;
    HI_U8  u8Phy1,u8Phy2;

    Rec = HI_UNF_HDMI_CECStatus(HI_UNF_HDMI_ID_0, &stCECStatus);
    if(Rec != HI_SUCCESS)
    {
        HDMI_TEST_CEC_LOG("Get CEC Status Fail! return \n");
        return Ret;
    }

    if(stCECStatus.bEnable != HI_TRUE)
    {
        HDMI_TEST_CEC_LOG("CEC Disable! return \n");
        return Ret;
    }

    //add by sample
    Init = pCECCmdGet->enSrcAdd;
    Dest = pCECCmdGet->enDstAdd;
    opcode = pCECCmdGet->u8Opcode;
#if !defined (HDMI_FORCE_RAWDATA)
    if (CEC_OPCODE_USER_CONTROL_PRESSED == opcode)
    {
        pOperand = (HI_U8 *)&(pCECCmdGet->unOperand.stUIOpcode);
        OperandLength = 1;
    }
    else
#endif
    {
        pOperand = pCECCmdGet->unOperand.stRawData.u8Data;
        OperandLength = pCECCmdGet->unOperand.stRawData.u8Length;
    }

    pCECCmdSet->enSrcAdd = stCECStatus.u8LogicalAddr;
    u8Phy1 = ((stCECStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
    u8Phy2 = ((stCECStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCECStatus.u8PhysicalAddr[3] & 0x0f); // [Physical Address(A.B.C.D):C D]

    switch(opcode)
    {
        /*General Protocol messages*/
        case CEC_OPCODE_FEATURE_ABORT:                   //0X00
            HDMI_TEST_CEC_LOG("FEATURE ABORT Init:%d, Dest:%d, opcode:0x%x\n", Init, Dest, opcode);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES; //need not response
            break;
        case CEC_OPCODE_ABORT_MESSAGE:                   //0XFF
            HDMI_TEST_CEC_LOG("ABORT MESSAGE\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES; //need not response
            break;

        /*One Touch Play Feature*/
        case CEC_OPCODE_ACTIVE_SOURCE:                   //0X82
            HDMI_TEST_CEC_LOG("ACTIVE_SOURCE, source cmd ignored\n");
            if ( (pOperand[0] != u8Phy1) || (pOperand[1] != u8Phy2) )
            {
                g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;
                HDMI_TEST_CEC_LOG("change to other output port,hdmi standby\n");
            }
            else
            {
                g_cecPowerStatus = CEC_POWER_STATUS_ON;
            }
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_IMAGE_VIEW_ON:                   //0X04
            HDMI_TEST_CEC_LOG("IMAGE_VIEW_ON, source cmd ignored\n");
            g_cecPowerStatus = CEC_POWER_STATUS_ON;
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_TEXT_VIEW_ON:                    //0X0D
            HDMI_TEST_CEC_LOG("TEXT_VIEW_ON, source cmd ignored\n");
            g_cecPowerStatus = CEC_POWER_STATUS_ON;
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Routing Control Feature*/
        case CEC_OPCODE_INACTIVE_SOURCE:                 //0X9D
            HDMI_TEST_CEC_LOG("INACTIVE_SOURCE\n");
            if ( (pOperand[0] != u8Phy1) || (pOperand[1] != u8Phy2) )
            {
                g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;
            }
            Ret = CEC_MESSAGE_RETURN_ERROR_NOSUPPORT;
            break;
        case CEC_OPCODE_REQUEST_ACTIVE_SOURCE:           //0X85
            //When a device(TV) comes out of the standy state, it maybe broacast a
            //<Request Active Source> message to discover active source.
            HDMI_TEST_CEC_LOG("REQUEST_ACTIVE_SOURCE, ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST == Dest)
            {
                HDMI_TEST_CEC_LOG("Broadcast msg response ACTIVE_SOURCE\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_ACTIVE_SOURCE;
                pCECCmdSet->enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                pCECCmdSet->unOperand.stRawData.u8Length  = 2;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = u8Phy1;
                pCECCmdSet->unOperand.stRawData.u8Data[1] = u8Phy2;
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Dirctly msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_ROUTING_CHANGE:                  //0X80
            HDMI_TEST_CEC_LOG("ROUTING_CHANGE, it should be brocast message\n");
            g_cecPowerStatus = CEC_POWER_STATUS_ON;
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_ROUTING_INFORMATION:             //0X81
            HDMI_TEST_CEC_LOG("ROUTING_INFORMATION, it should be brocast message\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_SET_STREAM_PATH:                 //0X86
            //the <Set Stream Path> is sent by the TV to the source device
            //to request it to broacst its path using an <Active Source> message.
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Standby Feature*/
        case CEC_OPCODE_STANDBY:                         //0X36
            HDMI_TEST_CEC_LOG("STANDBY, It should be brocast message\n");
            g_cecPowerStatus = CEC_POWER_STATUS_STANDBY;
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*One Touch Record Feature*/
        case CEC_OPCODE_RECORD_OFF:                      //0X0B
        case CEC_OPCODE_RECORD_ON:                       //0X09
        case CEC_OPCODE_RECORD_STATUS:                   //0X0A
        case CEC_OPCODE_RECORD_TV_SCREEN:                //0X0F
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Timer Programming Feature*/
        case CEC_OPCODE_CLEAR_ANALOGUE_TIMER:            //0X33
        case CEC_OPCODE_CLEAR_DIGITAL_TIMER:             //0X99
        case CEC_OPCODE_CLEAR_EXTERNAL_TIMER:            //0XA1
        case CEC_OPCODE_SET_ANALOGUE_TIMER:              //0X34
        case CEC_OPCODE_SET_DIGITAL_TIMER:               //0X97
        case CEC_OPCODE_SET_EXTERNAL_TIMER:              //0XA2
        case CEC_OPCODE_SET_TIMER_PROGRAM_TITLE:         //0X67
        case CEC_OPCODE_TIMER_CLEARED_STATUS:            //0X43
        case CEC_OPCODE_TIMER_STATUS:                    //0X35
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*System Information Feature*/
        case CEC_OPCODE_CEC_VERSION:                     //0X9E
            HDMI_TEST_CEC_LOG("CEC_VERSION: ");
            switch (pOperand[0])
            {
                case 0x04 :
                    HDMI_TEST_CEC_LOG("1.3a\n");
                    break;
                case 0x05 :
                    HDMI_TEST_CEC_LOG("1.4 or 1.4a or 1.4b\n");
                    break;
                default:
                    HDMI_TEST_CEC_LOG("unknown\n");
            }
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GET_CEC_VERSION:                 //0X9F
            HDMI_TEST_CEC_LOG("GET_CEC_VERSION, ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest) // mustbe directly
            {
                HDMI_TEST_CEC_LOG("directly msg Response CEC_VERSION\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_CEC_VERSION;
                pCECCmdSet->enDstAdd = Init;
                pCECCmdSet->unOperand.stRawData.u8Length  = 1;
                // hdmi spec1.4b cec spec page.108
                // 0x04 cec 1.3a   0x05 cec 1.4/1.4a/1.4b
                pCECCmdSet->unOperand.stRawData.u8Data[0] = 0x05;
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("broadcast msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_GIVE_PHYSICAL_ADDRESS:           //0X83
            HDMI_TEST_CEC_LOG("GIVE_PHYSICAL_ADDRESS, ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest)
            {
                HDMI_TEST_CEC_LOG("Directly msg Response REPORT_PHYSICAL_ADDRESS\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_REPORT_PHYSICAL_ADDRESS;
                pCECCmdSet->enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                pCECCmdSet->unOperand.stRawData.u8Length  = 3;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = u8Phy1;
                pCECCmdSet->unOperand.stRawData.u8Data[1] = u8Phy2;
                pCECCmdSet->unOperand.stRawData.u8Data[2] = stCECStatus.u8LogicalAddr;
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Broadcast msg ignored\n");
                 Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_REPORT_PHYSICAL_ADDRESS:
            HDMI_TEST_CEC_LOG("REPORT_PHYSICAL_ADDRESS\n");
            if (3 != OperandLength)
            {
                HDMI_TEST_CEC_LOG("Error oprand length:%d\n", OperandLength);
            }
            HDMI_TEST_CEC_LOG("PhysicalAddr:%01d.%01d.%01d.%01d, LogicalAddr:%d\n", (pOperand[0] & 0xf0) >> 4, (pOperand[0] & 0x0f), \
                (pOperand[1] & 0xf0) >> 4, (pOperand[1] & 0x0f), pOperand[2]);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GET_MENU_LANGUAGE:               //0X91
            HDMI_TEST_CEC_LOG("GET_MENU_LANGUAGE, just aimed at PhysicalAddr(TV)\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_SET_MENU_LANGUAGE:               //0X32
            HDMI_TEST_CEC_LOG("SET_MENU_LANGUAGE: ");
            {
                HI_U8 index;
                for (index = 0; index < OperandLength; index++)
                {
                    if ( ((pOperand[index] >= 'a') && (pOperand[index] <= 'z'))
                        || ((pOperand[index] >= 'A') && (pOperand[index] <= 'Z')) )
                    {
                        HDMI_TEST_CEC_LOG("%c", pOperand[index]);
                    }
                    else
                    {
                        HDMI_TEST_CEC_LOG("%02x", pOperand[index]);
                    }
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Deck Control Feature*/
        case CEC_OPCODE_DECK_CONTROL:                    //0X42
            HDMI_TEST_CEC_LOG("DECK_CONTROL\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_DECK_STATUS:                     //0X1B
            HDMI_TEST_CEC_LOG("DECK_STATUS\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GIVE_DECK_STATUS:                //0X1A
            HDMI_TEST_CEC_LOG("GIVE_DECK_STATUS\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_PLAY:                            //0X41
            HDMI_TEST_CEC_LOG("PLAY\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Tuner Control Feature*/
        case CEC_OPCODE_GIVE_TUNER_DEVICE_STATUS:        //0X08
        case CEC_OPCODE_SELECT_ANALOGUE_SERVICE:         //0X92
        case CEC_OPCODE_SELECT_DIGITAL_SERVICE:          //0X93
        case CEC_OPCODE_TUNER_DEVICE_STATUS:             //0X07
        case CEC_OPCODE_TUNER_STEP_DECREMENT:            //0X06
        case CEC_OPCODE_TUNER_STEP_INCREMENT:            //0X05
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Vendor Specific Command*/
        case CEC_OPCODE_DEVICE_VENDOR_ID:                //0X87
            HDMI_TEST_CEC_LOG("DEVICE_VENDOR_ID:");
            {
                HI_U8 index;
                for (index = 0; index < OperandLength; index++)
                {
                    HDMI_TEST_CEC_LOG("%02x ", pOperand[index]);
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GIVE_DEVICE_VENDOR_ID:           //0X8C
            HDMI_TEST_CEC_LOG("GIVE_DEVICE_VENDOR_ID, ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest)
            {
                HDMI_TEST_CEC_LOG("Directly msg Response GIVE_DEVICE_VENDOR_ID\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_DEVICE_VENDOR_ID;
                pCECCmdSet->enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                pCECCmdSet->unOperand.stRawData.u8Length  = 3;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = 'h';
                pCECCmdSet->unOperand.stRawData.u8Data[1] = 'i';
                pCECCmdSet->unOperand.stRawData.u8Data[2] = 's';
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Broadcast msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_VENDOR_COMMAND:                  //0X89
        case CEC_OPCODE_VENDOR_COMMAND_WITH_ID:          //0XA0
        case CEC_OPCODE_VENDOR_REMOTE_BUTTON_DOWN:       //0X8A
        case CEC_OPCODE_VENDOR_REMOTE_BUTTON_UP:         //0X8B
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*OSD Display Feature*/
        case CEC_OPCODE_SET_OSD_STRING:                  //0X64
            HDMI_TEST_CEC_LOG("SET_OSD_NAME:%s\n", pOperand);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GIVE_OSD_NAME:                   //0X46
            HDMI_TEST_CEC_LOG("CEC_OPCODE_GIVE_OSD_NAME, ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest)
            {
                HDMI_TEST_CEC_LOG("Directly msg Response CEC_OPCODE_GIVE_OSD_NAME\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_SET_OSD_NAME;
                pCECCmdSet->enDstAdd = Init;
                pCECCmdSet->unOperand.stRawData.u8Length  = 3;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = 'h';
                pCECCmdSet->unOperand.stRawData.u8Data[1] = 'i' ;
                pCECCmdSet->unOperand.stRawData.u8Data[2] = 's' ;
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Broadcast msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_SET_OSD_NAME:                    //0X47
            HDMI_TEST_CEC_LOG("SET_OSD_NAME:");
            {
                HI_U8 index;
                for (index = 0; index < OperandLength; index++)
                {
                    if ( ((pOperand[index] >= 'a') && (pOperand[index] <= 'z'))
                        || ((pOperand[index] >= 'A') && (pOperand[index] <= 'Z')) )
                    {
                        HDMI_TEST_CEC_LOG("%c", pOperand[index]);
                    }
                    else
                    {
                        HDMI_TEST_CEC_LOG("%02x", pOperand[index]);
                    }
                }
            }
            HDMI_TEST_CEC_LOG("\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Device Menu Control Feature*/
        case CEC_OPCODE_MENU_REQUEST:                    //0X8D
            HDMI_TEST_CEC_LOG("MENU_REQUEST: ");
            if ( (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest)
                && (HI_UNF_CEC_LOGICALADD_BROADCAST != Init) )
            {
                if( 1 != OperandLength)
                {
                    Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
                    HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                    break;
                }

                HDMI_TEST_CEC_LOG("Directly msg Response MENU_STATUS\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_MENU_STATUS;
                pCECCmdSet->enDstAdd = Init;
                pCECCmdSet->unOperand.stRawData.u8Length      = 1;

                if (pOperand[0] == 0x00)
                {
                    HDMI_TEST_CEC_LOG("Active\n");
                    pCECCmdSet->unOperand.stRawData.u8Data[0] = 0X00;//Active
                }
                else if (pOperand[0] == 0x01)
                {
                    HDMI_TEST_CEC_LOG("Deactive\n");
                    pCECCmdSet->unOperand.stRawData.u8Data[0] = 0X00;//Deactive t should be 1, 0 for cts test
                }
                else if (pOperand[0] == 0x02)
                {
                    HDMI_TEST_CEC_LOG("Query\n");
                    pCECCmdSet->unOperand.stRawData.u8Data[0] = 0X01;
                }
                else
                {
                    HDMI_TEST_CEC_LOG("Unknown, pOperand[0]:0x%x\n", pOperand[0]);
                    break;
                }
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Broadcast msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_MENU_STATUS:                     //0X8E
            HDMI_TEST_CEC_LOG("MENU_STATUS: ");
            if (OperandLength < 1)
            {
                HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                break;
            }
            if (pOperand[0] == 0x00)
            {
                HDMI_TEST_CEC_LOG("Active\n");
            }
            else if (pOperand[0] == 0x01)
            {
                HDMI_TEST_CEC_LOG("Deactive\n");
            }
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_USER_CONTROL_PRESSED:            //0X44
            HDMI_TEST_CEC_LOG("USER_CONTROL_PRESSED, ");
            HDMI_TEST_CEC_LOG("RC: 0x%02x\n", pOperand[0]);
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_USER_CONTROL_RELEASED:           //0X45
            HDMI_TEST_CEC_LOG("USER_CONTROL_RELEASED\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Power Status Feature*/
        case CEC_OPCODE_GIVE_DEVICE_POWER_STATUS:        //0X8F
            HDMI_TEST_CEC_LOG("GIVE_DEVICE_POWER_STATUS: ");
            if (HI_UNF_CEC_LOGICALADD_BROADCAST != Dest)
            {
                HDMI_TEST_CEC_LOG("Directly msg Response REPORT_POWER_STATUS\n");
                pCECCmdSet->u8Opcode = CEC_OPCODE_REPORT_POWER_STATUS;
                pCECCmdSet->enDstAdd = Init;
                pCECCmdSet->unOperand.stRawData.u8Length  = 1;
                pCECCmdSet->unOperand.stRawData.u8Data[0] = g_cecPowerStatus;//Power on
                Ret = CEC_MESSAGE_RETURN_OK_WITH_RESPONES;
            }
            else
            {
                HDMI_TEST_CEC_LOG("Broadcast msg ignored\n");
                Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            }
            break;
        case CEC_OPCODE_REPORT_POWER_STATUS:             //0X90
            HDMI_TEST_CEC_LOG("REPORT_POWER_STATUS: ");
            if (OperandLength < 1)
            {
                HDMI_TEST_CEC_LOG("Invalid OperandLength:%d\n", OperandLength);
                break;
            }
            if (pOperand[0] == 0x00)
            {
                HDMI_TEST_CEC_LOG("Power On\n");
            }
            else if (pOperand[0] == 0x01)
            {
                HDMI_TEST_CEC_LOG("Stand By\n");
            }
            else
            {
                HDMI_TEST_CEC_LOG("Unknown, pOperand[0]:0x%x\n", pOperand[0]);
            }
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*System Audio Control Feature*/
        case CEC_OPCODE_GIVE_AUDIO_STATUS:               //0X71
            HDMI_TEST_CEC_LOG("GIVE_AUDIO_STATUS\n");
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;
        case CEC_OPCODE_GIVE_SYSTEM_AUDIO_MODE_STATUS:   //0x7D
        case CEC_OPCODE_REPORT_AUDIO_STATUS:             //0X7A
        case CEC_OPCODE_SET_SYSTEM_AUDIO_MODE:           //0X72
        case CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST:       //0X70
        case CEC_OPCODE_SYSTEM_AUDIO_MODE_STATUS:        //0X7E
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        /*Audio Rate Control Feature*/
        case CEC_OPCODE_SET_AUDIO_RATE:                  //0X9A
            Ret = CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES;
            break;

        default:
            break;;
    }

    return Ret;
}

/*
**  CEC callback
*/
HI_VOID HDMI_CEC_Proc(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_CEC_CMD_S *pstCECCmd, HI_VOID *pData)
{
    HI_UNF_HDMI_CEC_CMD_S stReplyCmd;
    int ret;

    HDMI_CEC_PrintCmd(pstCECCmd);
    memset(&stReplyCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));

    ret = HDMI_CEC_MsgParse(pstCECCmd,&stReplyCmd);

    if (ret == CEC_MESSAGE_RETURN_OK_WITH_RESPONES)
    {
        HDMI_TEST_CEC_LOG("response \n");
        HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_0, &stReplyCmd);
        return ;
    }
    else if (ret == CEC_MESSAGE_RETURN_OK_WITHOUT_RESPONES)
    {
        HDMI_TEST_CEC_LOG("not need response \n");
        return ;//direct return!
    }
    else if (ret == CEC_MESSAGE_RETURN_ERROR_NOSUPPORT)
    {
        HDMI_TEST_CEC_LOG("unsupport cec cmd \n");
        //return ;
    }

    // Deal with Unsupport Message!    //
    // Do not reply to Broadcast msgs, otherwise send Feature Abort
    // for all unsupported features.
    if ( (pstCECCmd->enDstAdd & 0x0F) != 0x0F)
    {
        HI_U32 Rec;
        HI_UNF_HDMI_CEC_STATUS_S  stCECStatus;

        Rec = HI_UNF_HDMI_CECStatus(HI_UNF_HDMI_ID_0, &stCECStatus);
        if (Rec != HI_SUCCESS)
        {
            HDMI_TEST_CEC_LOG("Get CEC Status Fail! return \n");
            return ;
        }

        /*All devices shall support the message <Feature Abort>.
          It is used to allow devices to indicate if they do not support an opcode that has been
          sent to them, if it is unable to deal with this message.
          <Feature Abort> has 2 parameters: opcode and the reason of its reject of the frame.
          <Feature Abort> is used as a response to any failure!
        */
        // Unsupported opcode; send feature abort
        //<Feature Abort>has 2 parameters, the opcode and a reason for its rejection of the frame.
        memset(&stReplyCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
        stReplyCmd.u8Opcode = CEC_OPCODE_FEATURE_ABORT;//0x00;
        stReplyCmd.enSrcAdd = stCECStatus.u8LogicalAddr;// our logical Addr
        stReplyCmd.enDstAdd = pstCECCmd->enSrcAdd; //(sii_cec->bDestOrRXHeader & 0xf0) >> 4 ;
        stReplyCmd.unOperand.stRawData.u8Data[0] = pstCECCmd->u8Opcode;
        stReplyCmd.unOperand.stRawData.u8Data[1] = 0x00; //Unrecognized opcode:0x00
        stReplyCmd.unOperand.stRawData.u8Length  = 2;

        HDMI_CEC_PrintCmd(&stReplyCmd);
        HI_UNF_HDMI_SetCECCommand(HI_UNF_HDMI_ID_0,&stReplyCmd);
        HDMI_TEST_CEC_LOG("\n!Unsupported bOpcode:0x%x Feature!\n", pstCECCmd->u8Opcode);
    }
    else
    {
        // Unsupported Broadcast Msg
        HDMI_TEST_CEC_LOG("\n! Unsupported Brocast Msg!\n");
    }

    return;
}

/*
**  CEC enable
*/
HI_S32 hdmi_test_cec_enable(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_S32 s32Ret = 0;


    s32Ret |= HI_UNF_HDMI_RegCECCallBackFunc(HI_UNF_HDMI_ID_0, HDMI_CEC_Proc);

    s32Ret |= HI_UNF_HDMI_CEC_Enable(enHdmi);

    return s32Ret;
}

/*
**  CEC disable
*/
HI_S32 hdmi_test_cec_disable(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_S32 s32Ret = 0;

    s32Ret |= HI_UNF_HDMI_UnRegCECCallBackFunc(HI_UNF_HDMI_ID_0, HDMI_CEC_Proc);
    s32Ret |= HI_UNF_HDMI_CEC_Disable(enHdmi);

    return s32Ret;
}

/*
**  Send CEC cmd
*/
HI_U32 hdmi_test_cec_setcmd(HI_UNF_HDMI_ID_E enHdmi, HDMI_TEST_CEC_CMD_S *pstCecCmd)
{
    HI_U32                   i;
    HI_U32                   u32RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S    stCmd;
    HI_UNF_HDMI_CEC_STATUS_S stCecStatus;
    HI_U8 u8Phy1, u8Phy2;

    if (HI_NULL == pstCecCmd)
    {
        printf("input param is null!\n");
        return HI_FAILURE;
    }

    printf("CEC hdmi_cec_cmd, cmd: %d, destAddr:0x%x, u8Opcode:0x%x, Datalength:0x%x\n",
            pstCecCmd->enCmd, pstCecCmd->u8DestAddr, pstCecCmd->u8Opcode, pstCecCmd->u8Len);

    memset(&stCecStatus, 0, sizeof(HI_UNF_HDMI_CEC_STATUS_S));
    memset(&stCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));

    HI_UNF_HDMI_CECStatus(enHdmi, &stCecStatus);
    if (HI_TRUE != stCecStatus.bEnable)
    {
        printf("CEC Line does not enable\n");
    }

    stCmd.enSrcAdd = stCecStatus.u8LogicalAddr;
    u8Phy1 = ((stCecStatus.u8PhysicalAddr[0] << 4) & 0xf0) | (stCecStatus.u8PhysicalAddr[1] & 0x0f); // [Physical Address(A.B.C.D):A B]
    u8Phy2 = ((stCecStatus.u8PhysicalAddr[2] << 4) & 0xf0) | (stCecStatus.u8PhysicalAddr[3] & 0x0f); // [Physical Address(A.B.C.D):C D]

    for (i = 0; i<HI_UNF_CEC_LOGICALADD_BUTT; i++)
    {
        if (stCecStatus.u8Network[i])
        {
            stCmd.enDstAdd = i;
        }
        else
        {
            continue;
        }

        switch(pstCecCmd->enCmd)
        {
            case HDMI_TEST_CEC_STANDBY:
                stCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                stCmd.u8Opcode = CEC_OPCODE_STANDBY;
                break;
            case HDMI_TEST_CEC_IMAMGE_VIEW_ON:
                stCmd.u8Opcode = CEC_OPCODE_IMAGE_VIEW_ON;
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);
                break;
            case HDMI_TEST_CEC_TEXT_VIEW_ON:
                stCmd.u8Opcode = CEC_OPCODE_TEXT_VIEW_ON;
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);
                break;
            case HDMI_TEST_CEC_ACTIVE_SOURCE:
                stCmd.u8Opcode = CEC_OPCODE_IMAGE_VIEW_ON;  // image view on
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

                stCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                stCmd.u8Opcode = CEC_OPCODE_ACTIVE_SOURCE;  // active source
                stCmd.unOperand.stRawData.u8Length  = 0x02;
                stCmd.unOperand.stRawData.u8Data[0] = u8Phy1;
                stCmd.unOperand.stRawData.u8Data[1] = u8Phy2;
                break;
            case HDMI_TEST_CEC_GET_CEC_VERSION:
                stCmd.u8Opcode = CEC_OPCODE_GET_CEC_VERSION;
                break;
            case HDMI_TEST_CEC_CEC_VERSION:
                stCmd.u8Opcode = CEC_OPCODE_CEC_VERSION;
                stCmd.unOperand.stRawData.u8Length  = 0x01;
                stCmd.unOperand.stRawData.u8Data[0] = 0x05;  // CEC verison 1.4
                break;
            case HDMI_TEST_CEC_GET_MENU_LAN:
                stCmd.u8Opcode = CEC_OPCODE_GET_MENU_LANGUAGE;
                break;
            case HDMI_TEST_CEC_GET_PHY_ADDR:
                stCmd.u8Opcode = CEC_OPCODE_GIVE_PHYSICAL_ADDRESS;
                break;
            case HDMI_TEST_CEC_GET_DEV_VENDOR_ID:
                stCmd.u8Opcode = CEC_OPCODE_GIVE_DEVICE_VENDOR_ID;
                break;
            case HDMI_TEST_CEC_DEV_VENDOR_ID:
                stCmd.u8Opcode = CEC_OPCODE_DEVICE_VENDOR_ID;
                stCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_BROADCAST;
                stCmd.unOperand.stRawData.u8Length  = 3;
                stCmd.unOperand.stRawData.u8Data[0] = 'h';
                stCmd.unOperand.stRawData.u8Data[1] = 'i' ;
                stCmd.unOperand.stRawData.u8Data[2] = 's' ;
                break;
            case HDMI_TEST_CEC_GET_OSD_NAME:
                stCmd.u8Opcode = CEC_OPCODE_GIVE_OSD_NAME;
                break;
            case HDMI_TEST_CEC_SET_OSD_STRING:
                stCmd.u8Opcode = CEC_OPCODE_SET_OSD_STRING;
                stCmd.unOperand.stRawData.u8Length  = 0x04;
                stCmd.unOperand.stRawData.u8Data[0] = 0;
                stCmd.unOperand.stRawData.u8Data[1] = 0x68;
                stCmd.unOperand.stRawData.u8Data[2] = 0x69;
                stCmd.unOperand.stRawData.u8Data[3] = 0x73;
                break;
            case HDMI_TEST_CEC_GET_POWER_STATUS:
                stCmd.u8Opcode = CEC_OPCODE_GIVE_DEVICE_POWER_STATUS;
                break;
            case HDMI_TEST_CEC_MENU_ACTIVE:
                stCmd.u8Opcode = CEC_OPCODE_MENU_STATUS;
                stCmd.unOperand.stRawData.u8Length  = 0x01;
                stCmd.unOperand.stRawData.u8Data[0] = 0;    // 0: activated  1: Deactivated
                break;
            case HDMI_TEST_CEC_SET_VOLUME_UP:
                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_PRESSED;
                #if defined (HDMI_FORCE_RAWDATA)
                stCmd.unOperand.stRawData.u8Length  = 1;
                stCmd.unOperand.stRawData.u8Data[0] = HI_UNF_CEC_UICMD_VOLUME_UP;
                #else
                stCmd.unOperand.stUIOpcode = HI_UNF_CEC_UICMD_VOLUME_UP;
                #endif
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_RELEASED;
                stCmd.unOperand.stRawData.u8Length  = 0;
                break;
            case HDMI_TEST_CEC_SET_VOLUME_DOWN:
                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_PRESSED;
                #if defined (HDMI_FORCE_RAWDATA)
                stCmd.unOperand.stRawData.u8Length  = 1;
                stCmd.unOperand.stRawData.u8Data[0] = HI_UNF_CEC_UICMD_VOLUME_DOWN;
                #else
                stCmd.unOperand.stUIOpcode = HI_UNF_CEC_UICMD_VOLUME_DOWN;
                #endif
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_RELEASED;
                stCmd.unOperand.stRawData.u8Length  = 0;
                break;
            case HDMI_TEST_CEC_SET_VOLUME_MUTE:
                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_PRESSED;
                #if defined (HDMI_FORCE_RAWDATA)
                stCmd.unOperand.stRawData.u8Length  = 1;
                stCmd.unOperand.stRawData.u8Data[0] = HI_UNF_CEC_UICMD_MUTE;
                #else
                stCmd.unOperand.stUIOpcode = HI_UNF_CEC_UICMD_MUTE;
                #endif
                HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);

                stCmd.u8Opcode = CEC_OPCODE_USER_CONTROL_RELEASED;
                stCmd.unOperand.stRawData.u8Length  = 0;
                break;
            case HDMI_TEST_CEC_SYSTEM_AUDIO_MODE_REQUEST:
                stCmd.u8Opcode = CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST;
                stCmd.unOperand.stRawData.u8Length  = 0x02;
                stCmd.unOperand.stRawData.u8Data[0] = u8Phy1;
                stCmd.unOperand.stRawData.u8Data[1] = u8Phy2;
                break;
            case HDMI_TEST_CEC_USER_DEFINE:
                stCmd.enDstAdd = pstCecCmd->u8DestAddr;  // HI_UNF_CEC_LOGICALADD_TV;
                stCmd.u8Opcode = pstCecCmd->u8Opcode;
                stCmd.unOperand.stRawData.u8Length = pstCecCmd->u8Len;
                memcpy(&(stCmd.unOperand.stRawData.u8Data), pstCecCmd->u8Data, pstCecCmd->u8Len);
                break;
            default:
                printf("cmd error, do not support now!\n");
                u32RetError = HI_FAILURE;
                break;
        }

        if(HI_SUCCESS != u32RetError)
        {
            return u32RetError;
        }

        HI_UNF_HDMI_SetCECCommand(enHdmi, &stCmd);
    }

    return u32RetError;
}

/*
**  CEC auto ping
*/
HI_S32 hdmi_test_cec_autoping(HI_UNF_HDMI_ID_E enHdmi)
{
    HI_U32                 u32RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S  CECCmd;

    printf("CEC Auto Ping\n");
    memset(&CECCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
    CECCmd.enSrcAdd = HI_UNF_CEC_LOGICALADD_TUNER_1;
    CECCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_TV;
    CECCmd.u8Opcode = CEC_OPCODE_POLLING_MESSAGE;

    HI_UNF_HDMI_SetCECCommand(enHdmi, &CECCmd);

    return u32RetError;
}

