/*
* Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
*
* License type: GPLv2
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*
* This program may alternatively be licensed under a proprietary license from
* MaxLinear, Inc.
*
* See terms and conditions defined in file 'LICENSE.txt', which is part of this
* source code package.
*/

#include "MxLWare_HYDRA_OEM_Defines.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Commands.h"
#include "MxLWare_HYDRA_Registers.h"

UINT32 MxL_Get_DiseqcMappingBitMapReverse(MXL_HYDRA_CONTEXT_T * devHandlePtr, UINT32 bitMap)
{
  UINT32 diseqcBitMap = bitMap;

  MXLENTERSTR;
  if(((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542) ||
     (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582C) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C)))
  {
    if (diseqcBitMap & MXL_HYDRA_INTR_DISEQC_2) 
    {
      diseqcBitMap &= ~(MXL_HYDRA_INTR_DISEQC_2);
      diseqcBitMap |= (MXL_HYDRA_INTR_DISEQC_1);
    }
  }
  MXLEXIT(MXL_HYDRA_PRINT("Status reg (0x%x) changed to 0x%x\n", bitMap, diseqcBitMap);); 
  return diseqcBitMap; 
}

static MXL_HYDRA_DISEQC_ID_E MxL_Get_DiseqcMapping(MXL_HYDRA_CONTEXT_T * devHandlePtr, MXL_HYDRA_DISEQC_ID_E diseqcId)
{
  MXL_HYDRA_DISEQC_ID_E newDiseqcId = diseqcId;

  if(((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542) ||
     (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582C) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C)))
  {
    newDiseqcId = (newDiseqcId == MXL_HYDRA_DISEQC_ID_1)?MXL_HYDRA_DISEQC_ID_2:MXL_HYDRA_DISEQC_ID_0;
    MXLEXIT(MXL_HYDRA_PRINT("DiseqId=%d changed to %d\n", diseqcId, newDiseqcId);); 
  }

  return newDiseqcId;
}

static MXL_STATUS_E MxL_Set_DiseqcMode(UINT8 devId, MXL58x_DSQ_OP_MODE_TXRX_T *diseqcMsgPtr)
{
  MXL_STATUS_E status = MXL_SUCCESS;
  UINT8 cmdSize = sizeof(MXL58x_DSQ_OP_MODE_TXRX_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERSTR;
  MXLENTER(MXL_HYDRA_PRINT("diseqcId=%d, opModeTx=%s, invertTx=%d, opModeRx=%s, invertRx=%d, versionIndex=%d, diseqcCarrierFreqIndex=%d\n", 
                            diseqcMsgPtr->diseqcId, diseqcMsgPtr->opModeTx?"tone":"envelope", diseqcMsgPtr->invertTx, diseqcMsgPtr->opModeRx?"tone":"envelope", 
                            diseqcMsgPtr->invertRx, diseqcMsgPtr->version, diseqcMsgPtr->centerFreq););

  BUILD_HYDRA_CMD(MXL_HYDRA_DISEQC_CFG_TXRX_MSG_CMD, MXL_CMD_WRITE, cmdSize, diseqcMsgPtr, cmdBuff);
  status = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  
  MXLEXITSTR(status);
  return status;
}

static MXL_STATUS_E MxL_Set_FskMode(UINT8 devId, MXL_HYDRA_FSK_OP_MODE_E fskType)
{
  MXL_STATUS_E status = MXL_SUCCESS;
  UINT32 fskTypeCmd = (UINT32) fskType;
  UINT8 cmdSize = sizeof(UINT32);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERSTR;
  MXLENTER(MXL_HYDRA_PRINT("fskTypeIndex=%d\n", fskType););

  BUILD_HYDRA_CMD(MXL_HYDRA_FSK_SET_OP_MODE_CMD, MXL_CMD_WRITE, cmdSize, &fskTypeCmd, cmdBuff);
  status = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  
  MXLEXITSTR(status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ResetFsk
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 09/20/2012 Initial release
 *
 * The API is used to reset FSK block.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ResetFsk(UINT8 devId)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("Device ID=%d\n", devId););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    cmdBuff[0] = MXL_HYDRA_PLID_CMD_WRITE;
    cmdBuff[1] = (UINT8)(sizeof(UINT32));
    cmdBuff[2] = (UINT8)0;
    cmdBuff[3] = (UINT8)MXL_HYDRA_FSK_RESET_CMD;
    cmdBuff[4] = 0x00;
    cmdBuff[5] = 0x00;

    // send FSK reset command to the device
    status = MxLWare_HYDRA_SendCommand(devId, (6 * sizeof(UINT8)), &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDiseqcMsgDelays
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId        Diseqc ID
 * @param[in]   msgDelaysPtr    Structure with message delays 
 *
 * @author Mariusz 
 *
 * @date 07/13/2016 Initial release
 *
 * The API is used to configure delays in DiSEqC messages
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcMsgDelays(UINT8 devId, 
        MXL_HYDRA_DISEQC_ID_E diseqcId, 
        MXL_HYDRA_DISEQC_MSG_DELAYS_T * msgDelaysPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(
    MXL_HYDRA_PRINT("diseqcId=%d, ", diseqcId);
    if (msgDelaysPtr)
    {
      MXL_HYDRA_PRINT("newMsgDelayMs=%d, endMsgDelayMs=%d, replyDelayMs=%d, startMsgDelayMs=%d\n",
        msgDelaysPtr->newMsgDelayMs, msgDelaysPtr->endMsgDelayMs, msgDelaysPtr->replyDelayMs,
        msgDelaysPtr->startMsgDelayMs);
    } else MXL_HYDRA_PRINT("msgDelaysPtr=NULL!\n");
  )
  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    if ((msgDelaysPtr != NULL) && (msgDelaysPtr->newMsgDelayMs <= MXL_HYDRA_NEWMSG_DELAY_MAX)
        && (msgDelaysPtr->endMsgDelayMs <= MXL_HYDRA_ENDMSG_DELAY_MAX)
        && (msgDelaysPtr->replyDelayMs <= MXL_HYDRA_REPLYMSG_DELAY_MAX)
        && (msgDelaysPtr->startMsgDelayMs <= MXL_HYDRA_STARTMSG_DELAY_MAX))
    {
      UINT32 regData = 0;
      UINT32 regAddr = 0;

      diseqcId = MxL_Get_DiseqcMapping(devHandlePtr, diseqcId);
      regAddr = (HYDRA_DSQ0_DELAY_REG) + ((UINT32) diseqcId * HYDRA_DSQ_ID_OFFSET);

      regData = ((msgDelaysPtr->newMsgDelayMs & HYDRA_DSQ_NEWMSG_DELAY_MASK) << HYDRA_DSQ_NEWMSG_DELAY_LSBPOS) |
                ((msgDelaysPtr->endMsgDelayMs & HYDRA_DSQ_ENDMSG_DELAY_MASK) << HYDRA_DSQ_ENDMSG_DELAY_LSBPOS) | 
                ((msgDelaysPtr->replyDelayMs & HYDRA_DSQ_REPLY_DELAY_MASK) << HYDRA_DSQ_REPLY_DELAY_LSBPOS) |
                ((msgDelaysPtr->startMsgDelayMs & HYDRA_DSQ_START_DELAY_MASK) << HYDRA_DSQ_START_DELAY_LSBPOS);

      MXLDBG3(MXL_HYDRA_PRINT("Write 0x%08x to reg 0x%08x\n", regAddr, regData););
      status = MxLWare_HYDRA_WriteRegister(devId, regAddr, regData);

    } else status = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, status);
  return status;
}


/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDiseqcOpMode
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[in]   opMode
 * @param[in]   version
 * @param[in]   carrierFreqInHz
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * The API is used to configure DiSEqC interface in Hydra. There are 3 DiSEqC 1.x
 * interfaces and 1 DiSEqC 2.x interface. In case of DiSEqC 2.x interface, host
 * has to configure the appropriate DiSEqC ID based on device configuration.
 * Hydra SOC supports three different frequencies of 22 KHz, 33 KHz & 44 KHz
 * for communicating with DiSEqC slave.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcOpMode(UINT8 devId,
                                               MXL_HYDRA_DISEQC_ID_E diseqcId,
                                               MXL_HYDRA_DISEQC_OPMODE_E opMode,
                                               MXL_HYDRA_DISEQC_VER_E version,
                                               MXL_HYDRA_DISEQC_CARRIER_FREQ_E carrierFreqInHz)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL58x_DSQ_OP_MODE_TXRX_T diseqcMsg;
  
  MXL_HYDRA_DISEQC_OPMODE_E opModeTx = opMode;
  MXL_BOOL_E invertTx = MXL_FALSE;
  MXL_HYDRA_DISEQC_OPMODE_E opModeRx = MXL_HYDRA_DISEQC_TONE_MODE;  //Rx Path is always in Tone Mode under this API
  MXL_BOOL_E invertRx = MXL_FALSE;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId=%d, opMode=%d, versionIndex=%d, diseqcCarrierFreqIndex=%d\n", diseqcId, opMode, version, carrierFreqInHz););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    diseqcMsg.diseqcId = diseqcId;
    diseqcMsg.centerFreq = carrierFreqInHz;
    diseqcMsg.version = version;
    diseqcMsg.opModeTx = opModeTx;
    diseqcMsg.invertTx = invertTx;
    diseqcMsg.opModeRx = opModeRx;
    diseqcMsg.invertRx = invertRx;

    status = MxL_Set_DiseqcMode(devId, &diseqcMsg);
  }
  
  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDiseqcOpModeTxRx
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[in]   toneEnableTx
 * @param[in]   invertTx
 * @param[in]   toneEnableRx
 * @param[in]   invertRx
 * @param[in]   version
 * @param[in]   carrierFreqInHz
 *
 * @author Cres R
 *
 * @date 06/12/2012 Initial release
 *
 * The API is used to configure DiSEqC interface in Hydra. There are 3 DiSEqC 1.x
 * interfaces and 1 DiSEqC 2.x interface. In case of DiSEqC 2.x interface, host
 * has to configure the appropriate DiSEqC ID based on device configuration.
 * Hydra SOC supports three different frequencies of 22 KHz, 33 KHz & 44 KHz
 * for communicating with DiSEqC slave.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcOpModeTxRx(UINT8 devId,
                                                   MXL_HYDRA_DISEQC_ID_E diseqcId,
                                                   MXL_HYDRA_DISEQC_OPMODE_E opModeTx,
                                                   MXL_BOOL_E invertTx,
                                                   MXL_HYDRA_DISEQC_OPMODE_E opModeRx,
                                                   MXL_BOOL_E invertRx,
                                                   MXL_HYDRA_DISEQC_VER_E version,
                                                   MXL_HYDRA_DISEQC_CARRIER_FREQ_E carrierFreqInHz)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL58x_DSQ_OP_MODE_TXRX_T diseqcMsg;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId=%d, opModeTx=%s, invertTx=%d, opModeRx=%s, invertRx=%d, versionIndex=%d, diseqcCarrierFreqIndex=%d\n", 
                               diseqcId, opModeTx?"tone":"envelope", invertTx, opModeRx?"tone":"envelope", invertRx, version, carrierFreqInHz););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    diseqcMsg.diseqcId = diseqcId;
    diseqcMsg.centerFreq = carrierFreqInHz;
    diseqcMsg.version = version;
    diseqcMsg.opModeTx = opModeTx;
    diseqcMsg.invertTx = invertTx;
    diseqcMsg.opModeRx = opModeRx;
    diseqcMsg.invertRx = invertRx;

    status = MxL_Set_DiseqcMode(devId, &diseqcMsg);
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[in]   continuousToneCtrl
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * The API is used to configure DiSEqC interface in Hydra. There are 3 DiSEqC 1.x
 * interfaces and 1 DiSEqC 2.x interface. In case of DiSEqC 2.x interface, host
 * has to configure the appropriate DiSEqC ID based on device configuration.
 * Hydra SOC supports three different frequencies of 22 KHz, 33 KHz & 44 KHz
 * for communicating with DiSEqC slave.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(UINT8 devId,
                                                            MXL_HYDRA_DISEQC_ID_E diseqcId,
                                                            MXL_BOOL_E continuousToneCtrl)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXL_HYDRA_DISEQC_CFG_CONT_TONE_T diseqcContinuousTone;
  UINT8 cmdSize = sizeof(diseqcContinuousTone);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId=%d, continuousToneCtrl=%d\n", diseqcId, continuousToneCtrl););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    diseqcContinuousTone.diseqcId = diseqcId;
    diseqcContinuousTone.contToneFlag = continuousToneCtrl;

    BUILD_HYDRA_CMD(MXL_HYDRA_DISEQC_CONT_TONE_CFG, MXL_CMD_WRITE, cmdSize, &diseqcContinuousTone, cmdBuff);
    status = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDiseqcStatus
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[out]  statusPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API shall be used to retrieves DiSEqC module’s status.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDiseqcStatus(UINT8 devId, MXL_HYDRA_DISEQC_ID_E diseqcId, UINT32 *statusPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  //UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId = %d\n", diseqcId););

  *statusPtr = 0;

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    if (statusPtr)
    {
       diseqcId = MxL_Get_DiseqcMapping(devHandlePtr, diseqcId);
       
       // read diseqc status
       status = MxLWare_HYDRA_ReadRegister(devId,
                                           (DISEQ0_STATUS_REG + (diseqcId * (sizeof(UINT32)))),
                                            statusPtr);

	  // reset diseqc status if diseqc is set
      if ((status == MXL_SUCCESS) && (0 != *statusPtr))
      {
        
        status = MxLWare_HYDRA_WriteRegister(devId,
                                             (DISEQ0_STATUS_REG + (diseqcId * (sizeof(UINT32)))),
                                            0);
      }
    }
    else
      status = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDiseqcRead
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[out]  diseqcMsgPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This function is used to read DiSEqC response message from the
 * external DiSEqC device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDiseqcRead(UINT8 devId, MXL_HYDRA_DISEQC_ID_E diseqcId, MXL_HYDRA_DISEQC_RX_MSG_T *diseqcMsgPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 regData[DISEQC_RX_BLOCK_SIZE];
  UINT32 rxMsgStatus = 0;
  MXL_BOOL_E isDataReady = MXL_FALSE;
  UINT64 startTime = 0;
  UINT64 currTime = 0;
  UINT8 i = 0;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId=%d", diseqcId););

  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (diseqcMsgPtr)
    {
      // set diseqc msg avil to 0
      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId,
                                               DISEQC_RX_MSG_AVIAL_ADDR,
                                               0);

      // send command to read Rx data
      cmdBuff[0] = MXL_HYDRA_PLID_CMD_WRITE;
      cmdBuff[1] = (UINT8)(sizeof(UINT32));
      cmdBuff[2] = (UINT8)0;
      cmdBuff[3] = (UINT8)MXL_HYDRA_DISEQC_COPY_MSG_TO_MAILBOX;
      cmdBuff[4] = 0x00;
      cmdBuff[5] = 0x00;

      // send FSK reset command to the device
      mxlStatus |= MxLWare_HYDRA_SendCommand(devId, (6 * sizeof(UINT8)), &cmdBuff[0]);

      // Get current timestamp
      MxLWare_HYDRA_OEM_GetCurrTimeInMs(&startTime);

      // check if Rx data is ready
      do
      {
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                                  DISEQC_RX_MSG_AVIAL_ADDR,
                                                  &rxMsgStatus);

        if (rxMsgStatus & 0x1)
          isDataReady = MXL_TRUE;

        MxLWare_HYDRA_OEM_GetCurrTimeInMs(&currTime);

      } while ((isDataReady == MXL_FALSE) && ((currTime - startTime) < 200 /*  timeout of 200 ms */) );

      if (isDataReady == MXL_TRUE)
      {
        // read RX message
        mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                     DISEQC_RX_BLOCK_ADDR,
                                                     DISEQC_RX_BLOCK_SIZE,
                                                     &regData[0]);

        diseqcMsgPtr->nbyte = regData[0];

        MXLDBG1(MXL_HYDRA_PRINT("DiSEqC Data : \n"););
        for (i = 0; i < MXL_HYDRA_DISEQC_MAX_PKT_SIZE; i++)
        {
          diseqcMsgPtr->bufMsg[i] = regData[i+4];
          MXLDBG1(MXL_HYDRA_PRINT("0x%0X ", diseqcMsgPtr->bufMsg[i]););
        }
      }
      else
      {
        diseqcMsgPtr->nbyte = 0;
        mxlStatus |= MXL_FAILURE;
      }

      // set diseqc msg avil to 0
      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId,
                                               DISEQC_RX_MSG_AVIAL_ADDR,
                                               0);

    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDiseqcWrite
 *
 * @param[in]   devId           Device ID
 * @param[in]   diseqcId
 * @param[in]   diseqcMsgPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API shall be used to write DiSEqC message to an external LNB device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcWrite(UINT8 devId, MXL_HYDRA_DISEQC_TX_MSG_T *diseqcMsgPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT32 diseqcStatus;

  MXLENTERAPISTR(devId);
  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if ((diseqcMsgPtr) && (diseqcMsgPtr->diseqcId <= MXL_HYDRA_DISEQC_ID_3) && (diseqcMsgPtr->nbyte < MXL_HYDRA_DISEQC_MAX_PKT_SIZE))
    {
      UINT32 diseqcId = diseqcMsgPtr->diseqcId;
      MXL_HYDRA_DISEQC_TX_MSG_CMD_T diseqcMsg;
      UINT32 i  = 0;

      MXLENTERAPI(MXL_HYDRA_PRINT("diseqcId=%d | %d bytes: ", diseqcMsgPtr->diseqcId, diseqcMsgPtr->nbyte););
      for (i = 0; i < diseqcMsgPtr->nbyte; i++)
      {
        MXLENTERAPI(MXL_HYDRA_PRINT("0x%X ", diseqcMsgPtr->bufMsg[i]););
        diseqcMsg.bufMsg[i] = diseqcMsgPtr->bufMsg[i];
      }
      MXLENTERAPI(MXL_HYDRA_PRINT("\n"););

      diseqcId = MxL_Get_DiseqcMapping(devHandlePtr, diseqcId);
	  
      mxlStatus = MxLWare_HYDRA_ReadRegister(devId,
                                           (DISEQ0_STATUS_REG + (diseqcId * (sizeof(UINT32)))),
                                            &diseqcStatus);

      if (mxlStatus == MXL_SUCCESS)
      {
        if(MXL_HYDRA_DISEQC_STATUS_XMITING != diseqcStatus)
        {
          diseqcMsg.diseqcId = diseqcMsgPtr->diseqcId;
          diseqcMsg.nbyte = diseqcMsgPtr->nbyte;
          diseqcMsg.toneBurst = (UINT32) diseqcMsgPtr->toneBurst;   // type-cast from enum

          mxlStatus = MxLWare_HYDRA_WriteRegister(devId,
                                             (DISEQ0_STATUS_REG + (diseqcId * (sizeof(UINT32)))),
                                            0); // reset diseqc status if diseqc is set
          if (mxlStatus == MXL_SUCCESS)
          {
            BUILD_HYDRA_CMD(MXL_HYDRA_DISEQC_MSG_CMD, MXL_CMD_WRITE, sizeof(diseqcMsg), &diseqcMsg, cmdBuff);
            mxlStatus = MxLWare_HYDRA_SendCommand(devId, sizeof(diseqcMsg) + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
          }
        }
        else
        {
          MXLDBG2(MXL_HYDRA_PRINT("Diseqc transmitter is in use\n"););
          mxlStatus = MXL_NOT_READY; 
        }
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgFskOpMode
 *
 * @param[in]   devId           Device ID
 * @param[in]   fskCfgType
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API shall be used to configure FSK controller to FTM
 * or other specific modes supported by the device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgFskOpMode(UINT8 devId, MXL_HYDRA_FSK_OP_MODE_E fskCfgType)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("fskCfgTypeIndex=%d\n", fskCfgType););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Set_FskMode(devId, fskCfgType);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqFskMsgRead
 *
 * @param[in]   devId           Device ID
 * @param[out]  msgPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API shall be used to read message from FSK/SWM controller.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_ReqFskMsgRead(UINT8 devId, MXL_HYDRA_FSK_MSG_T *msgPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (msgPtr)
    {
      // Read data from the device
      if (mxlStatus == MXL_SUCCESS)
      {
        mxlStatus = MxLWare_HYDRA_CheckForCmdResponse(devId, devHandlePtr, MXL_HYDRA_FSK_MSG_CMD);

        if (devHandlePtr->cmdData.dataSize)
        {
          MXLWARE_OSAL_MEMCPY(msgPtr, &devHandlePtr->cmdData.data[4], sizeof(MXL_HYDRA_FSK_MSG_T));

#if !MXL_ENABLE_BIG_ENDIAN
          // only for LE platform
          MxL_CovertDataForEndianness(!(MXL_ENABLE_BIG_ENDIAN), sizeof(UINT32), (UINT8 *)&(msgPtr->msgValidFlag));
          MxL_CovertDataForEndianness(!(MXL_ENABLE_BIG_ENDIAN), sizeof(UINT32), (UINT8 *)&(msgPtr->msgLength));
#endif
          // convert data to componsate for I2C data swapping in FW layer
          MxL_CovertDataForEndianness(1, (sizeof (UINT8) * MXL_HYDRA_FSK_MESG_MAX_LENGTH), (UINT8 *)(&msgPtr->msgBuff[0]));
          MXLDBG2(
          MXL_HYDRA_PRINT("\r\nResp Len %d", msgPtr->msgLength);
          MXL_HYDRA_PRINT("\r\n0x%02X 0x%02X 0x%02X 0x%02X", msgPtr->msgBuff[0],
                                                 msgPtr->msgBuff[1],
                                                 msgPtr->msgBuff[2],
                                                 msgPtr->msgBuff[3]);
          );
        }
        else
        {
          msgPtr->msgValidFlag = 0;
        }
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgFskMsgWrite
 *
 * @param[in]   devId           Device ID
 * @param[in]   msgPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API will write a message to FSK/SWM controller. This message
 * can be a FSK/SWM network message or FSK/SWM controller configuration
 * message.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgFskMsgWrite(UINT8 devId, MXL_HYDRA_FSK_MSG_T *msgPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  UINT8 cmdSize = sizeof(MXL_HYDRA_FSK_MSG_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT32 reqType;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (msgPtr)
    {
      // build command manually instead of macro
      reqType = MXL_CMD_WRITE;
      cmdBuff[0] = ((reqType == MXL_CMD_WRITE) ? MXL_HYDRA_PLID_CMD_WRITE : MXL_HYDRA_PLID_CMD_READ);
      cmdBuff[1] = (cmdSize > 254)? 0xFF : (UINT8)(cmdSize + 4);
      cmdBuff[2] = (UINT8)0;
      cmdBuff[3] = (UINT8)MXL_HYDRA_FSK_MSG_CMD;
      cmdBuff[4] = 0x00;
      cmdBuff[5] = 0x00;

      cmdBuff[6] = GET_BYTE(msgPtr->msgValidFlag, 0);     // reg addr byte
      cmdBuff[7] = GET_BYTE(msgPtr->msgValidFlag, 1);     // reg addr byte
      cmdBuff[8] = GET_BYTE(msgPtr->msgValidFlag, 2);     // reg addr byte
      cmdBuff[9] = GET_BYTE(msgPtr->msgValidFlag, 3);     // reg addr byte

      cmdBuff[10] = GET_BYTE(msgPtr->msgLength, 0);     // reg addr byte
      cmdBuff[11] = GET_BYTE(msgPtr->msgLength, 1);     // reg addr byte
      cmdBuff[12] = GET_BYTE(msgPtr->msgLength, 2);     // reg addr byte
      cmdBuff[13] = GET_BYTE(msgPtr->msgLength, 3);     // reg addr byte

      //Message length is only the LSB 7 bits.
      MXLWARE_OSAL_MEMCPY((void *)&cmdBuff[14], (const void *)&(msgPtr->msgBuff[0]), (msgPtr->msgLength & 0x7F));
      MXLDBG2(
      MXL_HYDRA_PRINT("\r\n Wrt Len %d", cmdBuff[10]);
      MXL_HYDRA_PRINT("\r\n0x%02X 0x%02X 0x%02X 0x%02X", cmdBuff[14], cmdBuff[15], cmdBuff[16], cmdBuff[17]);
      );
	  // In order to increase the processing priority of the FSK Local reset msg, 
	  // we send the reset msg (0x07) as the FSK Reset API and process it as TOP_PRI event
	  if((cmdBuff[10] & 0x80) != 0 ) // Checking if the msg is a local msg
	  {
		  if((cmdBuff[14] & 0xFF) == 0x07) // FSK Local Reset Command
		  {
			  cmdBuff[0] = MXL_HYDRA_PLID_CMD_WRITE;
			  cmdBuff[1] = (UINT8)(sizeof(UINT32));
			  cmdBuff[2] = (UINT8)0;
			  cmdBuff[3] = (UINT8)MXL_HYDRA_FSK_LOCAL_RESET_CMD;
			  cmdBuff[4] = 0x00;
			  cmdBuff[5] = 0x00;
			  mxlStatus = MxLWare_HYDRA_SendCommand(devId, (6 * sizeof(UINT8)), &cmdBuff[0]);
			  MXLEXITAPISTR(devId, mxlStatus);
			  return mxlStatus;
		  }
	  }

      mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgFskFreq
 *
 * @param[in]   devId           Device ID
 * @param[in]   fskFreqMode     FSK Frequency Mode
 * @param[in]   freqHz          Frequency to be configured.
 *
 * @author Sateesh
 *
 * @date 12/12/2013 Initial release
 *
 * This function will allow the host to set the FSK frequency mode
 * into “normal” (2.3MHz) mode or “manual” where the output frequency
 * is specified by the “freq” parameter.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgFskFreq(UINT8 devId, MXL_HYDRA_FSK_CFG_FREQ_MODE_E fskFreqMode, UINT32 freqHz)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  MXL58x_CFG_FSK_FREQ_T fskFreqCmd;
  UINT8 cmdSize = sizeof(MXL58x_CFG_FSK_FREQ_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("fskFreqMode=%d\n", fskFreqMode););
  MXLENTERAPI(MXL_HYDRA_PRINT("freqHz=%dHz\n", freqHz););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (((fskFreqMode == MXL_HYDRA_FSK_CFG_FREQ_MODE_NORMAL) || (fskFreqMode == MXL_HYDRA_FSK_CFG_FREQ_MODE_MANUAL)) && \
        ((freqHz >= 600) && (freqHz <= 9700000)))
    {
        mxlStatus = MxL_Set_FskMode(devId, MXL_HYDRA_FSK_CFG_TYPE_39KPBS);
        if(mxlStatus == MXL_SUCCESS)
      {
        // build Demod Frequency Offset Search command
        fskFreqCmd.fskFreqMode = (UINT32) fskFreqMode;
        fskFreqCmd.freq = freqHz;
        BUILD_HYDRA_CMD(MXL_HYDRA_FSK_CFG_FSK_FREQ_CMD, MXL_CMD_WRITE, cmdSize, &fskFreqCmd, cmdBuff);

        // send command to device
        mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_PowerDownFsk
 *
 * @param[in]   devId           Device ID
 *
 * @author Sateesh
 *
 * @date 01/08/2013 Initial release
 *
 * The API is used to disable and power down FSK block.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_PowerDownFsk(UINT8 devId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  UINT8 cmdSize = 0;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT32 dummy = 0;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    BUILD_HYDRA_CMD(MXL_HYDRA_FSK_POWER_DOWN_CMD, MXL_CMD_WRITE, cmdSize, &dummy, cmdBuff);
    mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
