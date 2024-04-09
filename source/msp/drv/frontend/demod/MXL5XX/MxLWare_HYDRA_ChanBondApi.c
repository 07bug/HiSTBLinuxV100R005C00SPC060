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

#include "MxLWare_HYDRA_CommonApi.h"

#ifdef _MXL_HYDRA_CHAN_BOND_
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Registers.h"
#include "MxLWare_HYDRA_Commands.h"
#include "MxLWare_HYDRA_ChanBondApi.h"
#include "MxLWare_HYDRA_OEM_Drv.h"

static MXL_BOOL_E MxL_Ctrl_checkIfBondedGroupIsExclusive(UINT8 devId, MXL_HYDRA_CHANBOND_GROUP_T *cbTuneParamsPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_BOOL_E exclusiveFlag = MXL_TRUE;
  UINT32 i = 0;
  UINT32 j = 0;
  UINT32 k = 0;

  MXLENTERSTR;

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    // Check if demods are part of existing bonded group
    for (i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
    {
      if ( devHandlePtr->cbBondedGroup[i].cbGroupInUse == MXL_TRUE)
      {
        for (j = 0; j < cbTuneParamsPtr->numOfDemodsInCB; j++)
        {
          for( k = 0; k < MXL_HYDRA_CB_DEMODS_MAX; k++)
          {
            if (devHandlePtr->cbBondedGroup[i].cbDemodId[k] == cbTuneParamsPtr->cbDemodId[j])
            {
              exclusiveFlag = MXL_FALSE;
              MXL_HYDRA_PRINT("Demod Break i=%d, j=%d, k=%d\n", i, j, k);
              break;
            }
          }
        }
        for (j = 0; j < cbTuneParamsPtr->numOfTsPorts; j++)
        {
          for( k = 0; k < MXL_HYDRA_CB_TS_PORTS_MAX; k++)
          {
            if (devHandlePtr->cbBondedGroup[i].cbTsOutId[k] == cbTuneParamsPtr->cbTsOutId[j])
            {
              exclusiveFlag = MXL_FALSE;
              MXL_HYDRA_PRINT("TS Out Break i=%d, j=%d, k=%d\n", i, j, k);
              break;
            }
          }
        }
      }
    }
  }
  MXL_HYDRA_PRINT("exclusiveFlag=%d\n", exclusiveFlag);
  MXLEXITSTR( mxlStatus);
  return exclusiveFlag;
}

static MXL_BOOL_E MxL_Ctrl_checkIfBondedGroupIsAvailable(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_BOOL_E availableFlag = MXL_FALSE;
  UINT8 i = 0;

  MXLENTERSTR;

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    // Check if demods are part of existing bonded group
    for (i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
    {
      if ( devHandlePtr->cbBondedGroup[i].cbGroupInUse == MXL_FALSE)
      {
        availableFlag = MXL_TRUE;
        break;
      }
    }
  }
  MXL_HYDRA_PRINT("availableFlag=%d\n", availableFlag);
  MXLEXITSTR( mxlStatus);
  return availableFlag;
}

static MXL_BOOL_E MxL_Ctrl_checkIfDemodIsPartOfBondedGroup(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_BOOL_E partOfBondedGroup = MXL_FALSE;
  UINT32 i = 0;
  UINT32 j = 0;

  MXLENTERSTR;
  MXLENTER(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    // Check if demod is part of existing bonded group
    for (i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
    {
      if ( devHandlePtr->cbBondedGroup[i].cbGroupInUse == MXL_TRUE)
      {
        for (j = 0; j < devHandlePtr->cbBondedGroup[i].numOfDemodsInCB; j++)
        {
          if (devHandlePtr->cbBondedGroup[i].cbDemodId[j] == demodId)
          {
            partOfBondedGroup = MXL_TRUE;
            MXLDBG2(MXL_HYDRA_PRINT("Demod is part of Bond Group %d\n", i););
            break;
          }
        }
      }
    }
  }
  MXLEXIT(MXL_HYDRA_PRINT("Demod: partOfBondedGroup=%d\n", partOfBondedGroup););
  MXLEXITSTR( mxlStatus);
  return partOfBondedGroup;
}

static MXL_BOOL_E MxL_Ctrl_checkIfTSOutIsPartOfBondedGroup(UINT8 devId, MXL_HYDRA_TS_OUT_ID_E tsOutId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_BOOL_E partOfBondedGroup = MXL_FALSE;
  UINT32 i = 0;
  UINT32 j = 0;

  MXLENTERSTR;

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    // Check if demod is part of existing bonded group
    for (i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
    {
      if ( devHandlePtr->cbBondedGroup[i].cbGroupInUse == MXL_TRUE)
      {
        for (j = 0; j < devHandlePtr->cbBondedGroup[i].numOfTsPorts; j++)
        {
          if (devHandlePtr->cbBondedGroup[i].cbTsOutId[j] == tsOutId)
          {
            partOfBondedGroup = MXL_TRUE;
            MXL_HYDRA_PRINT("TS Out is part of Bond Group %d\n", i);
            break;
          }
        }
      }
    }
  }
  MXL_HYDRA_PRINT("TS Out: partOfBondedGroup=%d\n", partOfBondedGroup);
  MXLEXITSTR( mxlStatus);
  return partOfBondedGroup;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqChannelBondId
 *
 * @param[in]   devId               Device ID
 * @param[in]   cbTuneParamsPtr     Pointer to channel Bonding Tune Params
 * @param[out]  bondIdPtr           Pointer to hold Bond ID
 *
 * @author Sateesh
 *
 * @date 04/09/2014
 *
 * This API should be used to request Bond ID based on Demod List and TS Out List
 * so that Bond ID is used in subsequent APIs.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqChannelBondId(UINT8 devId, MXL_HYDRA_CHANBOND_GROUP_T *chanBondGroupPtr, UINT8 *bondIdPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 i = 0;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if ((chanBondGroupPtr) && (bondIdPtr) && \
        (MxL_Ctrl_checkIfBondedGroupIsAvailable(devId) == MXL_TRUE) &&  \
        (MxL_Ctrl_checkIfBondedGroupIsExclusive(devId, chanBondGroupPtr) == MXL_TRUE))
    {
      // Update Demod ID & TS Out ID in bonded Group list
      for ( i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
      {
        if ( devHandlePtr->cbBondedGroup[i].cbGroupInUse == MXL_FALSE)
        {
          MXLWARE_OSAL_MEMCPY(&(devHandlePtr->cbBondedGroup[i]), chanBondGroupPtr, sizeof(MXL_HYDRA_CHANBOND_GROUP_T));
          devHandlePtr->cbBondedGroup[i].cbGroupInUse = MXL_TRUE;
          *bondIdPtr = i;
          MXLDBG2(MXL_HYDRA_PRINT("Bond ID %d\n", *bondIdPtr););
          break;
        }
      }
    }
    else
    {
      mxlStatus |= MXL_INVALID_PARAMETER;
    }
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }
  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgCBTune
 *
 * @param[in]   devId               Device ID
 * @param[in]   tunerId             Tuner ID
 * @param[in]   bondId              Bond ID
 * @param[in]   cbTuneParamsPtr     Pointer to channel Bonding Tune Params
 *
 * @author Mahee
 *
 * @date 10/12/2013
 *
 * This API should be used to configure and tune channel bonded channels.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgCBTune(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT8 bondId, MXL_HYDRA_CHANBOND_TUNE_PARAMS_T *chanBondTunePtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXL_HYDRA_CHANBOND_TUNE_PARAM_T demodChanCfg;
  UINT8 cmdSize = sizeof(demodChanCfg);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT32 i = 0;
  UINT32 j = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d, bond ID %d\n", tunerId, bondId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if ((chanBondTunePtr) && (bondId < MXL_HYDRA_CB_GROUP_MAX) && \
        (devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB <= MXL_HYDRA_CB_DEMODS_MAX) && \
        (devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB > 0) &&
        (devHandlePtr->cbBondedGroup[bondId].numOfTsPorts <= MXL_HYDRA_CB_TS_PORTS_MAX) && 
        (devHandlePtr->cbBondedGroup[bondId].numOfTsPorts > 0) && 
        (chanBondTunePtr->symbolRateKSps >= MXL_HYDRA_SYMBOLRATE_KSPS_MIN))
    {
      // Packing the Channel Bond Tune parameters for Firmware
      demodChanCfg.tunerId = tunerId;
      demodChanCfg.numOfDemods = devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB;
      demodChanCfg.spectrumInversion = chanBondTunePtr->spectrumInfo;
      demodChanCfg.tsOutputMode = devHandlePtr->serialInterface;
      demodChanCfg.rollOff = chanBondTunePtr->rollOff;
      demodChanCfg.symbolRateInHz = chanBondTunePtr->symbolRateKSps * 1000;
      demodChanCfg.pilots = chanBondTunePtr->pilots;
      demodChanCfg.modulationScheme = chanBondTunePtr->modulation;
      demodChanCfg.fecCodeRate = chanBondTunePtr->fec;
      demodChanCfg.dropBondingHeader = chanBondTunePtr->dropBondingHeader;

      for (i = 0; i < devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB; i++)
      {
        // demod list map
        demodChanCfg.tuneCfgParams[i].demodId = (UINT32)chanBondTunePtr->cbDemodList[i].demodId;
        demodChanCfg.tuneCfgParams[i].frequencyInHz = chanBondTunePtr->cbDemodList[i].frequencyInHz;
        demodChanCfg.tuneCfgParams[i].standardMask = chanBondTunePtr->cbDemodList[i].standardMask;
        demodChanCfg.tuneCfgParams[i].scrambleCode = chanBondTunePtr->cbDemodList[i].scrambleCode;

        devHandlePtr->cbBondedGroup[bondId].cbDemodId[i] = (MXL_HYDRA_DEMOD_ID_E)demodChanCfg.tuneCfgParams[i].demodId;

        for (j = 0; j < MXL_DEMOD_SCRAMBLE_SEQ_LEN; j++)
        {
          demodChanCfg.tuneCfgParams[i].scrambleSequence[j] = chanBondTunePtr->cbDemodList[i].scrambleSequence[j];
        }

        // Changing Endianness to offset the endianness change in BUILD_HYDRA_CMD
        MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, MXL_DEMOD_SCRAMBLE_SEQ_LEN, 
                                    &demodChanCfg.tuneCfgParams[i].scrambleSequence[0]);

        if (chanBondTunePtr->cbDemodList[i].freqSearchRangeKHz%1000)
          demodChanCfg.tuneCfgParams[i].freqSearchRangeKHz = (chanBondTunePtr->cbDemodList[i].freqSearchRangeKHz/1000) + 1;
        else
          demodChanCfg.tuneCfgParams[i].freqSearchRangeKHz = (chanBondTunePtr->cbDemodList[i].freqSearchRangeKHz)/1000;

        MXLDBG1(
        MXL_HYDRA_PRINT("Demod: %d\n", chanBondTunePtr->cbDemodList[i].demodId);
        MXL_HYDRA_PRINT("frequencyInHz=%d\n", chanBondTunePtr->cbDemodList[i].frequencyInHz);
        MXL_HYDRA_PRINT("scrambleCode=%d\n", chanBondTunePtr->cbDemodList[i].scrambleCode);
        MXL_HYDRA_PRINT("standardMask=%d\n", chanBondTunePtr->cbDemodList[i].standardMask);
        );
      }

      demodChanCfg.numOfTsPorts = devHandlePtr->cbBondedGroup[bondId].numOfTsPorts;
      for (i = 0; i < demodChanCfg.numOfTsPorts; i++)
      {
        demodChanCfg.tsPortId[i] = devHandlePtr->cbBondedGroup[bondId].cbTsOutId[i];
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, 0x9070000C, demodChanCfg.tsPortId[i], 1, 1);
      }
      
      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, XPU_DBG_CMD_STATS_READ_CTRL_REG, 0);

      // send command to the device
      BUILD_HYDRA_CMD(MXL_XCPU_CHAN_TUNE_CMD, MXL_CMD_WRITE, cmdSize, &demodChanCfg, cmdBuff);
      mxlStatus |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
    }
    else
    {
      mxlStatus |= MXL_INVALID_PARAMETER;
    }
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgCBAbortTune
 *
 * @param[in]   devId               Device ID
 * @param[in]   bondId              Bonded Group ID
 *
 * @author Mahee
 *
 * @date 10/12/2013
 *
 * This API should be called to abort the tuning of bonded channels.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgCBAbortTune(UINT8 devId, UINT8 bondId)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_UNBOND_CFG_T demodList;
  UINT8 cmdSize = sizeof(demodList);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT32 i = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d Bond ID %d\n", devId, bondId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if ((bondId < MXL_HYDRA_CB_GROUP_MAX) && \
        (devHandlePtr->cbBondedGroup[bondId].cbGroupInUse == MXL_TRUE) && \
        (devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB <= MXL_HYDRA_CB_DEMODS_MAX))
    {
      demodList.numOfDemodsInCB = devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB;

      for (i = 0; i < demodList.numOfDemodsInCB; i++)
      {
        demodList.demodId[i] = devHandlePtr->cbBondedGroup[bondId].cbDemodId[i];
      }

      // send command to the device
      BUILD_HYDRA_CMD(MXL_XCPU_ABORT_TUNE_CMD, MXL_CMD_WRITE, cmdSize, &demodList, cmdBuff);
      mxlStatus |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);

      if (mxlStatus == MXL_SUCCESS)
      {
        devHandlePtr->cbBondedGroup[bondId].cbGroupInUse = MXL_FALSE;
        devHandlePtr->cbBondedGroup[bondId].numOfDemodsInCB = 0;
        devHandlePtr->cbBondedGroup[bondId].numOfTsPorts = 0;

        for (i = 0; i < MXL_HYDRA_CB_DEMODS_MAX; i++)
        {
            devHandlePtr->cbBondedGroup[bondId].cbDemodId[i] = MXL_HYDRA_DEMOD_MAX;
        }
        for (i = 0; i < MXL_HYDRA_CB_TS_PORTS_MAX; i++)
        {
            devHandlePtr->cbBondedGroup[bondId].cbTsOutId[i] = MXL_HYDRA_TS_OUT_MAX;
        }
        MXLDBG2(MXL_HYDRA_PRINT("Abort Success\n"););
      }
    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgFilterChanBondHdrs
 *
 * @param[in]   devId               Device ID
 * @param[in]   enable              Enable/Disable
 *
 * @author Mahee
 *
 * @date 10/12/2013
 *
 * This API configures to enable/disable the filtering of channel bonded headers.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgFilterChanBondHdrs(UINT8 devId, MXL_BOOL_E enable)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    // Allow or Drop CB headers
    ; //mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, XCPU_CB_DROP_BH_REG, (UINT32)enable);
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqInputCBStatsEx
 *
 * @param[in]   devId               Device ID
 * @param[in]   demodId             Demod ID
 * @param[out]  inputChanStatsPtr   Pointer to Input channel statistics
 *
 * @author Mahee
 *
 * @date 10/12/2013
 *
 * This API should be called to request statistics on input channel bonding.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqInputCBStatsEx(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_CHANBOND_INPCH_STATS_T *inputChanStatsPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 cbStatsRegAddr = 0;
  MXL_HYDRA_CHANBOND_INPCH_STATS_T tmpStats;
  UINT32 xBarRegData = 0;
  UINT32 xptInputRegData = 0;
  UINT32 i = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if ((inputChanStatsPtr) && (MxL_Ctrl_checkIfDemodIsPartOfBondedGroup(devId, demodId) == MXL_TRUE))
    {
      // read CB Stats address
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, XCPU_CB_INPUT_STATS_ADDR_REG, &cbStatsRegAddr);
      if ((cbStatsRegAddr & 0xFFFF0000) == 0x90760000)
      {
        MXLWARE_OSAL_MEMSET(&tmpStats, 0, (sizeof(XCPU_CB_INPUT_STATS_ADDR_REG)));

        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, XPT_DMD0_BASEADDR, &xBarRegData);
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, XCPU_XPT_CHANNEL_BOND_INPUT, &xptInputRegData);

        for(i = 0; i < MXL_HYDRA_DEMOD_MAX; i++)
        {
          if(xptInputRegData & 0x1)
          {
            if((xBarRegData & 0xF) == demodId)
            {
              break;
            }
          }
          xptInputRegData = xptInputRegData >> 1;
          xBarRegData = xBarRegData >> 4;
        }	

        cbStatsRegAddr = cbStatsRegAddr + (i * sizeof(MXL_HYDRA_CHANBOND_INPCH_STATS_T));

        mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                   cbStatsRegAddr,
                                                   (sizeof(MXL_HYDRA_CHANBOND_INPCH_STATS_T)),
                                                   (UINT8 *)&tmpStats);

        MXLWARE_OSAL_MEMCPY(inputChanStatsPtr, &tmpStats, (sizeof(MXL_HYDRA_CHANBOND_INPCH_STATS_T)));
      }
      else
        mxlStatus = MXL_FAILURE;
    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqOutputCBStatsEx
 *
 * @param[in]   devId               Device ID
 * @param[in]   tsOutId             TS Out ID
 * @param[out]  outputChanStatsPtr  Pointer to Output channel statistics
 *
 * @author Mahee
 *
 * @date 10/12/2013
 *
 * This API should be called to request statistics on output channel bonding.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqOutputCBStatsEx(UINT8 devId, MXL_HYDRA_TS_OUT_ID_E tsOutId, MXL_HYDRA_CHANBOND_OUTCH_STATS_T *outputChanStatsPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 cbStatsRegAddr = 0;
  MXL_HYDRA_CHANBOND_OUTCH_STATS_T tmpStats;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d, tsOutId=%d\n", devId, tsOutId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if ((outputChanStatsPtr) && (MxL_Ctrl_checkIfTSOutIsPartOfBondedGroup(devId, tsOutId) == MXL_TRUE))
    {
      // read CB Stats address
      //mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, (XCPU_CB_OUTPUT_STATS_ADDR_REG + (tsOutId * sizeof(UINT32))), &cbStatsRegAddr);
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, (XCPU_CB_OUTPUT_STATS_ADDR_REG), &cbStatsRegAddr);

      if ((cbStatsRegAddr & 0x90760000) == 0x90760000)
      {
        MXLWARE_OSAL_MEMSET(&tmpStats, 0, (sizeof(MXL_HYDRA_CHANBOND_OUTCH_STATS_T)));

        cbStatsRegAddr = cbStatsRegAddr + (tsOutId * sizeof(MXL_HYDRA_CHANBOND_OUTCH_STATS_T));

        mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                   cbStatsRegAddr,
                                                   (sizeof(MXL_HYDRA_CHANBOND_OUTCH_STATS_T)),
                                                   (UINT8 *)&tmpStats);

        MXLWARE_OSAL_MEMCPY(outputChanStatsPtr, &tmpStats, (sizeof(MXL_HYDRA_CHANBOND_OUTCH_STATS_T)));
      }
      else
        mxlStatus = MXL_FAILURE;
    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}


/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgCBClearIOStats
 *
 * @param[in]   devId               Device ID
 * @param[in]   bondId              Bonded Group ID
 *
 * @author Sateesh
 *
 * @date 04/24/2014
 *
 * This API should be called to reset CB input and output statistics.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgCBClearIOStats(UINT8 devId, MXL_HYDRA_CB_CLEAR_STATS_T *clearIOStatsPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 cmdSize = sizeof(MXL_HYDRA_CB_CLEAR_STATS_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
    if (clearIOStatsPtr)
    {
      UINT32 clearStatsCmd[2];

      clearStatsCmd[0] = (clearIOStatsPtr->clearInputStats == MXL_TRUE)?1:0;
      clearStatsCmd[1] = (clearIOStatsPtr->clearOutputStats == MXL_TRUE)?1:0;
      // send command to the device
      BUILD_HYDRA_CMD(MXL_XCPU_CLEAR_CB_STATS_CMD, MXL_CMD_WRITE, 2*sizeof(UINT32), clearStatsCmd, cmdBuff);
      mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
    }
    else mxlStatus = MXL_INVALID_PARAMETER;
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus = MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgChanBondRestart
 *
 * @param[in]   devId               Device ID
 * @param[in]   restartFlag         Restart Flags configuration
 *
 * @author Sateesh
 *
 * @date 05/19/2014
 *
 * This API should be called to control channel bond restart on error.
 * User can control error condition for which restart should be enabled 
 * or disabled. This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_NOT_SUPPORTED      - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgChanBondRestart(UINT8 devId, UINT32 restartFlag)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {
  
    // configure enable/disable Chan Bond after error
    mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, XCPU_CB_RESTART_CTRL_REG, ((restartFlag == 0)?0:1));

  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus = MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqChanBondLockStatus
 *
 * @param[in]   devId                   Device ID
 * @param[in]   chanBondLockPtr    ChanBond Lock Status
 * @param[in]   bondId                  Bond Id
 *
 * @author Mahee
 *
 * @date 06/24/2014
 *
 * This API should be called to get chanbond lock status and acq time.
 * This API is applicable only for 568 Sku.
 *
 * @retval MXL_SUCCESS              - OK
 * @retval MXL_FAILURE                - Failure
 * @retval MXL_NOT_SUPPORTED    - Channel Bonding not supported
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqChanBondLockStatus(UINT8 devId, UINT8 bondId, MXL_HYDRA_CHANBOND_LOCK_T *chanBondLockPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 cbLockStatus = 0;
  UINT32 lockTime = 0;
  
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) && (devHandlePtr->features.chanBond == MXL_TRUE))
  {

    if ((chanBondLockPtr) && (bondId < MXL_HYDRA_CB_GROUP_MAX))
    {
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, XCPU_CH_BONDING_LOCK_STATUS, &cbLockStatus);
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, XCPU_CB_LOCK_TIME_REG, &lockTime);

      if (mxlStatus == MXL_SUCCESS) 
      {
        chanBondLockPtr->chanBondLockStatus = MXL_FALSE;
        chanBondLockPtr->lockTimeInMsecs = 0;

        // Chan Bond lock status will be true only if all demods in chan bond group is in SYNC state.
        if (cbLockStatus == MXL_TRUE)
        {
          chanBondLockPtr->chanBondLockStatus = MXL_TRUE;

          // divide cycles with 209000 (209 MHz clock) to get lock time in msecs
          chanBondLockPtr->lockTimeInMsecs = (UINT32)(lockTime/209000);

        }

      }

    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
   
  }
  else if (devHandlePtr->features.chanBond != MXL_TRUE)
  {
    mxlStatus |= MXL_NOT_SUPPORTED;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
#endif
