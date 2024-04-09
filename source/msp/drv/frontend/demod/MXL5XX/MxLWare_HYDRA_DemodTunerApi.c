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

/**
 * @defgroup Tuner_and_Demodulator_APIs
 **/

#include "MxLWare_HYDRA_OEM_Defines.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Registers.h"
#include "MxLWare_HYDRA_Commands.h"


/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 *
 * @brief MxLWare_HYDRA_API_CfgTunerEnable
 *
 * @param[in]   devId        Device ID
 * @param[in]   tunerId
 * @param[in]   enable
 *
 * @author Mahee
 *
 * @date 11/14/2012 Initial release
 *
 * @detail This API should be used to enable or disable tuner.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 * @usage After the firmware download, use this API to enable or disable the Hydra tuner. Before performing the first
 * tune, call this API to enable the required tuner. For the:
 * +  MxL561 and MxL581 = There is only one tuner, and this API should be called before calling the first
 * channel tune API.
 * +  MxL582 = There are two tuners (MXL_HYDRA_TUNER_ID_0 and MXL_HYDRA_TUNER_ID_1), and
 * one splitter output (MXL_HYDRA_TUNER_ID_2). To enable the splitter output, call this API with
 * MXL_HYDRA_TUNER_ID_2. Ensure that MXL_HYDRA_TUNER_ID_1 is enabled before enabling the
 * splitter (MXL_HYDRA_TUNER_ID_2).
 * +  Tuner Enable = Takes up to 600ms per tuner to complete. This wait time must be factored in before
 * using MxLWare_HYDRA_API_CfgDemodChanTune.

 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTunerEnable(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_BOOL_E enable)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  MxL_HYDRA_TUNER_CMD ctrlTunerCmd;
  UINT8 cmdSize = sizeof(ctrlTunerCmd);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId = %d %d\n", tunerId, devHandlePtr->deviceType));
  if (mxlStatus == MXL_SUCCESS)
  {
    if (tunerId < devHandlePtr->features.tunersCnt)
    {
      ctrlTunerCmd.tunerId = tunerId;
      ctrlTunerCmd.enable = enable;
      BUILD_HYDRA_CMD(MXL_HYDRA_TUNER_ACTIVATE_CMD, MXL_CMD_WRITE, cmdSize, &ctrlTunerCmd, cmdBuff);

      // send command to device
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
 * @ingroup Tuner_and_Demodulator_APIs
 *
 * @brief MxLWare_HYDRA_API_ReqTunerEnableStatus
 *
 * @param[in]   devId        Device ID
 * @param[in]   tunerId
 * @param[out]  tunerEnablePtr
 *
 * @author Sateesh
 *
 * @date 03/30/2015 Initial release
 *
 * @detail This API should be used to request the tuner enable status.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 * @usage After the firmware download, 
 *  use this API to check the status of Hydra tuner. 
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerEnableStatus(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_BOOL_E *tunerEnablePtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId = %d %d\n", tunerId, devHandlePtr->deviceType));
  if (mxlStatus == MXL_SUCCESS)
  {
    if (tunerId < devHandlePtr->features.tunersCnt)
    {
      mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_TUNER_ENABLE_COMPLETE, &regData);
      if (mxlStatus == MXL_SUCCESS)
      {
        if (((regData >> tunerId) & 0x1) == 0x1)
          *tunerEnablePtr = MXL_ENABLE;
        else
          *tunerEnablePtr = MXL_DISABLE;
      }
      MXL_HYDRA_DEBUG("Tuner %d Status: %d\n", tunerId, *tunerEnablePtr);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgDemodAbortTune
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API should be used to abort tune.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodAbortTune(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  MXL_HYDRA_DEMOD_ABORT_TUNE_T abortTuneCmd;
  UINT8 cmdSize = sizeof(abortTuneCmd);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // build abort tune command
    abortTuneCmd.demodId = demodId;
    BUILD_HYDRA_CMD(MXL_HYDRA_ABORT_TUNE_CMD, MXL_CMD_WRITE, cmdSize, &abortTuneCmd, cmdBuff);

    // send command to device
    mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgDemodDisable
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to disable Hydra Demod module.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodDisable(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("DemodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // Abort tune before disabling demod
    mxlStatus = MxLWare_HYDRA_API_CfgDemodAbortTune(devId, demodId);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_HelperFn_CfgDemodChanTuneParamSetUp
 *
 * @param[in]   devId        Device ID
 * @param[in]   devHandlePtr
 * @param[in]   tunerId      Tuner ID
 * @param[in]   demodId    Demod ID
 * @param[in]   demodChanCfgPtr   Demod config parameters
 * @param[in]   chanTuneParamsPtr   Channel tune parameters
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This Helper Function is used to set-up the demod and channel tune parameters.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_HelperFn_CfgDemodChanTuneParamSetUp(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_PARAM_T * demodChanCfgPtr, MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if((MXL_SUCCESS == mxlStatus) && (devHandlePtr))
  {
    if ((chanTuneParamsPtr) && (demodChanCfgPtr) && (devHandlePtr))
    {
    // Validate input parameters
    switch (chanTuneParamsPtr->standardMask)
    {
      case MXL_HYDRA_DSS:
        demodChanCfgPtr->fecCodeRate = chanTuneParamsPtr->params.paramsDSS.fec;
        if (chanTuneParamsPtr->params.paramsDSS.rollOff > MXL_HYDRA_ROLLOFF_0_35)
        {
          mxlStatus |= MXL_INVALID_PARAMETER;
        }
        break;

      case MXL_HYDRA_DVBS:
        // Validate rolloff
        if (chanTuneParamsPtr->params.paramsS.rollOff > MXL_HYDRA_ROLLOFF_0_35)
        {
          mxlStatus |= MXL_INVALID_PARAMETER;
        }

        // Validate modulation
        if ((chanTuneParamsPtr->params.paramsS.modulation != MXL_HYDRA_MOD_QPSK) && \
              (chanTuneParamsPtr->params.paramsS.modulation != MXL_HYDRA_MOD_AUTO))
        {
          mxlStatus |= MXL_INVALID_PARAMETER;
        }
        else if (chanTuneParamsPtr->params.paramsS.modulation == MXL_HYDRA_MOD_AUTO)
        {
          chanTuneParamsPtr->params.paramsS.modulation = MXL_HYDRA_MOD_QPSK;
        }
        break;

      case MXL_HYDRA_DVBS2:
        // Validate rolloff
        if (chanTuneParamsPtr->params.paramsS2.rollOff > MXL_HYDRA_ROLLOFF_0_35)
        {
          mxlStatus |= MXL_INVALID_PARAMETER;
        }

        // Validate modulation
        if (chanTuneParamsPtr->params.paramsS2.modulation > MXL_HYDRA_MOD_8PSK)
        {
          mxlStatus |= MXL_INVALID_PARAMETER;
        }

        break;

      default:
        mxlStatus |= MXL_INVALID_PARAMETER;
    }
  }
  else
    mxlStatus |= MXL_INVALID_PARAMETER;

  if ((mxlStatus == MXL_SUCCESS) && (chanTuneParamsPtr))
  {
    // Abort tune first
    //MxLWare_HYDRA_API_CfgDemodAbortTune(devId, demodId);

    // Configure channel settings & perform chan tune
    demodChanCfgPtr->tunerIndex = (UINT32)tunerId;
    demodChanCfgPtr->demodIndex = (UINT32)demodId;
    demodChanCfgPtr->frequencyInHz = chanTuneParamsPtr->frequencyInHz;
    demodChanCfgPtr->symbolRateInHz = (chanTuneParamsPtr->symbolRateKSps * 1000);
    if(chanTuneParamsPtr->symbolRateKSps < MXL_HYDRA_SYMBOLRATE_KSPS_MIN)
    {
      mxlStatus |= MXL_INVALID_PARAMETER;
    }

    if ((chanTuneParamsPtr->freqSearchRangeKHz%1000))
        demodChanCfgPtr->maxCarrierOffsetInMHz = (chanTuneParamsPtr->freqSearchRangeKHz/1000) + 1;
    else
        demodChanCfgPtr->maxCarrierOffsetInMHz = (chanTuneParamsPtr->freqSearchRangeKHz)/1000;

    demodChanCfgPtr->spectrumInversion = (UINT32)chanTuneParamsPtr->spectrumInfo;
    demodChanCfgPtr->standard = (UINT32)chanTuneParamsPtr->standardMask;

    // update device context
    devHandlePtr->bcastStd[demodId] = chanTuneParamsPtr->standardMask;

    MXLDBG1(
    MXL_HYDRA_PRINT(" tunerIndex : %d\n", demodChanCfgPtr->tunerIndex);
    MXL_HYDRA_PRINT(" demodIndex : %d\n", demodChanCfgPtr->demodIndex);
    MXL_HYDRA_PRINT(" frequencyInHz : %d\n", demodChanCfgPtr->frequencyInHz);
    MXL_HYDRA_PRINT(" symbolRateInHz : %d\n", demodChanCfgPtr->symbolRateInHz);
    MXL_HYDRA_PRINT(" maxCarrierOffsetInMHz : %d\n", demodChanCfgPtr->maxCarrierOffsetInMHz);
    MXL_HYDRA_PRINT(" spectrumInversion : %d\n", demodChanCfgPtr->spectrumInversion);
    );

    // get standard specific tunning parameters
    switch (chanTuneParamsPtr->standardMask)
    {
      case MXL_HYDRA_DSS:
        demodChanCfgPtr->fecCodeRate = chanTuneParamsPtr->params.paramsDSS.fec;
        demodChanCfgPtr->rollOff = chanTuneParamsPtr->params.paramsDSS.rollOff;

        MXLDBG1(
        MXL_HYDRA_PRINT(" fecCodeRate : %d\n", demodChanCfgPtr->fecCodeRate);
        MXL_HYDRA_PRINT(" rollOff : %d\n", demodChanCfgPtr->rollOff);
        );
        break;

      case MXL_HYDRA_DVBS:
        demodChanCfgPtr->rollOff = chanTuneParamsPtr->params.paramsS.rollOff;
        demodChanCfgPtr->modulationScheme = chanTuneParamsPtr->params.paramsS.modulation;
        demodChanCfgPtr->fecCodeRate = chanTuneParamsPtr->params.paramsS.fec;

        MXLDBG1(
        MXL_HYDRA_PRINT(" fecCodeRate : %d\n", demodChanCfgPtr->fecCodeRate);
        MXL_HYDRA_PRINT(" modulationScheme : %d\n", demodChanCfgPtr->modulationScheme);
        MXL_HYDRA_PRINT(" rollOff : %d\n", demodChanCfgPtr->rollOff);
        );
        break;

      case MXL_HYDRA_DVBS2:
        demodChanCfgPtr->rollOff = chanTuneParamsPtr->params.paramsS2.rollOff;
        demodChanCfgPtr->modulationScheme = chanTuneParamsPtr->params.paramsS2.modulation;
        demodChanCfgPtr->fecCodeRate = chanTuneParamsPtr->params.paramsS2.fec;
        demodChanCfgPtr->pilots = chanTuneParamsPtr->params.paramsS2.pilots;

        MXLDBG1(
        MXL_HYDRA_PRINT(" fecCodeRate : %d\n", demodChanCfgPtr->fecCodeRate);
        MXL_HYDRA_PRINT(" modulationScheme : %d\n", demodChanCfgPtr->modulationScheme);
        MXL_HYDRA_PRINT(" rollOff : %d\n", demodChanCfgPtr->rollOff);
        );
        break;

      default:
        mxlStatus |= MXL_INVALID_PARAMETER;
        break;
      }
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}


/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgDemodChanTune
 *
 * @param[in]   devId        Device ID
 * @param[in]   tunerId      Tuner ID
 * @param[in]   demodId    Demod ID
 * @param[in]   chanTuneParamsPtr   Channel tune parameters
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used when tuning for a channel.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodChanTune(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_HYDRA_DEMOD_PARAM_T demodChanCfg;
  UINT8 cmdSize = sizeof(demodChanCfg);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if((MXL_SUCCESS == mxlStatus) && (devHandlePtr))
    mxlStatus |= MxLWare_HYDRA_HelperFn_CfgDemodChanTuneParamSetUp(devId, tunerId, demodId, &demodChanCfg, chanTuneParamsPtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    // send command to the device
    BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_SET_PARAM_CMD, MXL_CMD_WRITE, cmdSize, &demodChanCfg, cmdBuff);
    mxlStatus |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgDemodConstellationSource
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId   Demod ID
 * @param[in]   source      Constellation source
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to set source of constellation data retrieved
 * by API function MxLWare_HYDRA_ReqDemodConstellationData.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodConstellationSource(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_CONSTELLATION_SRC_E source)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_DEMOD_IQ_SRC_T iqSrc;
  UINT8 cmdSize = sizeof(iqSrc);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d, source=%d\n", demodId, source););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // build FW command
    iqSrc.demodId = demodId;
    iqSrc.sourceOfIQ = source;

    BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_SET_IQ_SOURCE_CMD, MXL_CMD_WRITE, cmdSize, &iqSrc, cmdBuff);

    // send command to device
    mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);

  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

#ifdef MXL_ENABLE_SPECTRUM_RB
UINT16 maxNumOfSteps[] = { MAX_STEP_SIZE_24_XTAL_102_05_KHZ,
                           MAX_STEP_SIZE_24_XTAL_204_10_KHZ,
                           MAX_STEP_SIZE_24_XTAL_306_15_KHZ,
                           MAX_STEP_SIZE_24_XTAL_408_20_KHZ,
                           MAX_STEP_SIZE_27_XTAL_102_05_KHZ,
                           MAX_STEP_SIZE_27_XTAL_204_10_KHZ,
                           MAX_STEP_SIZE_27_XTAL_306_15_KHZ,
                           MAX_STEP_SIZE_27_XTAL_408_20_KHZ};

UINT32 freqStep[] = { 102050, 204100, 306150, 408200,
                      102050, 204100, 306150, 408200};

MXL_STATUS_E MxL_Ctrl_TunerPowerSpectrum(UINT8 devId,
                                       MXL_HYDRA_TUNER_ID_E tunerId,
                                       MXL_HYDRA_DEMOD_ID_E demodId,
                                       UINT32 freqStartInKHz,
                                       UINT32 numOfFreqSteps,
                                       SINT16 *powerBufPtr,
                                       MXL_HYDRA_SPECTRUM_ERROR_CODE_E *spectrumReadbackStatusPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL_BOOL_E spectrumReadyFlag = MXL_FALSE;
  UINT32 totalSize = 0;
  UINT64 startTime = 0;
  UINT64 currTime = 0;
  UINT32 startFreq = 0;
  UINT32 endFreq = 0;
  UINT32 regData = 0;
  UINT32 tmpNumOfSteps = 0;
  UINT32 index = 0;
  UINT32 spectrumDataAddr[2];
  SINT16 spectrumData[MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH/sizeof(SINT16)];
  UINT32 numOfBinsInBytes = 0;

  MXL_HYDRA_SPECTRUM_REQ_T pwrSpectrum;
  MXL_HYDRA_SPECTRUM_REQ_T minAgc;

  UINT8 cmdSize = sizeof(pwrSpectrum);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    UINT32 errCode;

    // send command to calculate min AGC
    minAgc.demodIndex = demodId;
    minAgc.tunerIndex = tunerId;
    minAgc.startingFreqInkHz = freqStartInKHz;
    minAgc.stepSizeInKHz = (UINT32) MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ;
    minAgc.totalSteps = numOfFreqSteps;

    // build command
    BUILD_HYDRA_CMD(MXL_HYDRA_TUNER_SPECTRUM_MIN_GAIN_CMD, MXL_CMD_WRITE, cmdSize, &minAgc, cmdBuff);

    // send command to device
    status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);

    MxLWare_HYDRA_OEM_GetCurrTimeInMs(&startTime);

    do
    {
      // check status for min agc command -DMD0_SPECTRUM_MIN_GAIN_STATUS
      status |= MxLWare_HYDRA_ReadRegister(devId,
                            (DMD0_SPECTRUM_MIN_GAIN_STATUS + HYDRA_DMD_STATUS_OFFSET(demodId)),
                            &regData);

      MXLDBG3(MXL_HYDRA_PRINT("Spectrum Status RegAddr = 0x%08X, Data = 0x%08X\n", (DMD0_SPECTRUM_MIN_GAIN_STATUS + HYDRA_DMD_STATUS_OFFSET(demodId)), regData););

      MxLWare_HYDRA_OEM_GetCurrTimeInMs(&currTime);

    } while (((currTime - startTime) < 20000 /*  timeout of 20 secs */) && ((regData & 0xFFFFFFFF) == 0x0));

    errCode = regData & 0xffff;
    if ((errCode == 0x1) || (errCode == 0x2))
      status = MXL_INVALID_PARAMETER;
    else if ((errCode == 0x3) || (errCode == 0x4) || (errCode == 0x5))
      status = MXL_FAILURE;

    MXLERR(
      if (errCode) 
      {
        MXL_HYDRA_PRINT("Error. gain status = %d\n", regData);
      }
    );

    *spectrumReadbackStatusPtr = (MXL_HYDRA_SPECTRUM_ERROR_CODE_E)(errCode);

    // if regData <31:16> = 1 then spectrm agc data is ready
    if ((status == MXL_SUCCESS) && ((regData & 0xFFFF0000) == 0x10000))
    {
      MXLDBG1(MXL_HYDRA_PRINT("Spectrum data available\n"););
      // Calculate end frequency
      endFreq = (freqStartInKHz * 1000) + (freqStep[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ] * numOfFreqSteps);
      tmpNumOfSteps = numOfFreqSteps;

      // loop entire spectrum
      for (startFreq = (freqStartInKHz * 1000);  startFreq < endFreq; startFreq += (freqStep[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ] * maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ]))
      {
        tmpNumOfSteps -= totalSize;
        index += totalSize;

        MXLDBG2(MXL_HYDRA_PRINT("Spectrum Loop. startFreq=%d, endFreq=%d\n", startFreq, endFreq););

        // if num of steps is not less than max allowed then step size should be valid max num of steps
        if (tmpNumOfSteps < maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ])
          totalSize = tmpNumOfSteps;
        else
          totalSize = maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ];

        if (status == MXL_SUCCESS)
        {
          // Delay of 50 msecs
          MxLWare_HYDRA_OEM_SleepInMs(50);

          // build FW command
          pwrSpectrum.demodIndex = demodId;
          pwrSpectrum.tunerIndex = tunerId;
          pwrSpectrum.stepSizeInKHz = (UINT32) MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ;
          pwrSpectrum.totalSteps = totalSize;
          pwrSpectrum.startingFreqInkHz = (UINT32)(startFreq/1000);

          MXLDBG2(MXL_HYDRA_PRINT("tunerId = %d, demodId = %d freqStartInKHz = %d, numOfFreqSteps = %d\n",
                                            tunerId, demodId,
                                            pwrSpectrum.startingFreqInkHz,
                                            pwrSpectrum.totalSteps););

          // build command
          BUILD_HYDRA_CMD(MXL_HYDRA_TUNER_SPECTRUM_REQ_CMD, MXL_CMD_WRITE, cmdSize, &pwrSpectrum, cmdBuff);

          // send command to device
          status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
        }

        // if command is sent successfully to device
        if (status == MXL_SUCCESS)
        {
          // Get current timestamp
          MxLWare_HYDRA_OEM_GetCurrTimeInMs(&startTime);

          do
          {
            // Read status of the spectrum readback command
            status |= MxLWare_HYDRA_ReadRegister(devId,
                                        (HYDRA_TUNER_SPECTRUM_STATUS_OFFSET + HYDRA_TUNER_STATUS_OFFSET(tunerId)),
                                        &regData);

            MXLDBG3(MXL_HYDRA_PRINT("Spectrum Status RegAddr = 0x%08X, Data = 0x%08X\n", (HYDRA_TUNER_SPECTRUM_STATUS_OFFSET + HYDRA_TUNER_STATUS_OFFSET(tunerId)), regData););

            spectrumReadyFlag = MXL_FALSE;

            if (((regData & 0xFFFF) == 0x1) || ((regData & 0xFFFF) == 0x2))
            {
              status = MXL_INVALID_PARAMETER;
            }
            else if (((regData & 0xFFFF) == 0x3) || ((regData & 0xFFFF) == 0x4) || ((regData & 0xFFFF) == 0x5))
            {
              status = MXL_FAILURE;
            }
            else
              spectrumReadyFlag = MXL_TRUE;

            *spectrumReadbackStatusPtr = (MXL_HYDRA_SPECTRUM_ERROR_CODE_E)(regData & 0xFFFF);

            // if regData <31:16> = 1 then spectrm data is ready
            if ((status == MXL_SUCCESS) && ((regData & 0xFFFF0000) == 0x10000) && (spectrumReadyFlag == MXL_TRUE))
            {
              // Get number of bins to read data from and readback data buffer address
              status |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                            (HYDRA_TUNER_SPECTRUM_BIN_SIZE_OFFSET + HYDRA_TUNER_STATUS_OFFSET(tunerId)),
                                            (2 * 4), // 2 * 4 bytes - 2 32-bit registers
                                            (UINT8 *)&spectrumDataAddr[0]);

              MXLDBG3(MXL_HYDRA_PRINT("RegAddr = 0x%08X, Data = 0x%08X Data = 0x%08X\n",
                                        (HYDRA_TUNER_SPECTRUM_BIN_SIZE_OFFSET + HYDRA_TUNER_STATUS_OFFSET(tunerId)),
                                        spectrumDataAddr[0], // Num of bins to read
                                        spectrumDataAddr[1]);) // Address

              // # bins should be greater than zero
              if (spectrumDataAddr[1])
              {
                // validate num of bins - if the bin size is greater than MAX then limit the bin
                // size to MAX
                if (spectrumDataAddr[0] > maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ])
                  spectrumDataAddr[0] = maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ];

                // Calculate num of bins in bytes
                numOfBinsInBytes = (spectrumDataAddr[0] * 2);

                // Num of Bytes to read should be multiple of 4
                if (numOfBinsInBytes % 4)
                  numOfBinsInBytes += (numOfBinsInBytes % 4);

                // Read Spectrum data
                status |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                        (spectrumDataAddr[1]),  // starting address
                                                        (numOfBinsInBytes), // # of bins * 2 bytes
                                                        (UINT8 *)&spectrumData[0]);

                MXLDBG2(MXL_HYDRA_PRINT("Spectrum Data - Start\n"););

                // each spectrum value is 16 bits so the loop increment is +2
                for (regData = 0; regData < totalSize; regData += 2)
                {
                  powerBufPtr[index+regData] = spectrumData[regData+1];
                  MXLDBG3(MXL_HYDRA_PRINT("%d    %d", (regData), powerBufPtr[index+regData]););

                  /* check is the last reacod should be read or not
                     need this check because we read number of bytes as a factor of 4
                     due to 32-bit register read. We always round number of bytes to read to the next highest factor of 4. */
                  if ((regData+1) < totalSize)
                  {
                    powerBufPtr[index+(regData+1)] = spectrumData[regData];
                    MXLDBG3(MXL_HYDRA_PRINT("%d    %d", (regData+1), powerBufPtr[index+(regData+1)]););
                  }
                }
                MXLDBG2(MXL_HYDRA_PRINT("Spectrum Data - Done\n"););
              }
              else
              {
                spectrumReadyFlag = MXL_FALSE;
              }
            }
            else
            {
              spectrumReadyFlag = MXL_FALSE;
            }
            MxLWare_HYDRA_OEM_GetCurrTimeInMs(&currTime);

            // loop with timeout value of 500 ms & spectrum data is not ready
          } while (((currTime - startTime) < 500 /*  timeout of 500 ms */) && (spectrumReadyFlag == MXL_FALSE));
        }
      }
    }
  }
  return status;
}
/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqTunerPowerSpectrum
 *
 * @param[in]   devId        Device ID
 * @param[in]   tunerId
 * @param[in]   demodId
 * @param[in]   freqStartInKHz
 * @param[in]   numOfFreqSteps
 * @param[out]  powerBufPtr
 * @param[out]  spectrumReadbackStatusPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API retrieves power spectrum data in specified frequency range
 * for a specified tuner.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerPowerSpectrum(UINT8 devId,
                                                      MXL_HYDRA_TUNER_ID_E tunerId,
                                                      MXL_HYDRA_DEMOD_ID_E demodId,
                                                      UINT32 freqStartInKHz,
                                                      UINT32 numOfFreqSteps,
                                                      SINT16 * powerBufPtr,
                                                      MXL_HYDRA_SPECTRUM_ERROR_CODE_E *spectrumReadbackStatusPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d, freqStartInKHz=%d, freqStepInHz=%d, numOfFreqSteps=%d\n", tunerId, freqStartInKHz, freqStep[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ], numOfFreqSteps););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    // validate input parameter
    // validate spectrum step size - 24 XTAL is supported for now 01/03/2013
    if ((powerBufPtr) && (spectrumReadbackStatusPtr) && (freqStartInKHz >= MXL_HYDRA_SPECTRUM_MIN_FREQ_KHZ) \
        && (freqStartInKHz*1000UL + numOfFreqSteps*freqStep[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ] <= MXL_HYDRA_SPECTRUM_MAX_FREQ_KHZ*1000UL) \
        && (maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ]*sizeof(SINT16) <= MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH))
    {
      status = MxL_Ctrl_TunerPowerSpectrum(devId, tunerId, demodId, freqStartInKHz, numOfFreqSteps, powerBufPtr, spectrumReadbackStatusPtr);
    }
    else
    {
      MXLERR(
      if (maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ]*sizeof(SINT16) > MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH)
      {
        MXL_HYDRA_PRINT("Cannot be executed due to memory limitation. Increase MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH if possible\n");
      }
      else
      {
        MXL_HYDRA_PRINT(" Invalid Parameter!");
      }
      );
      status = MXL_INVALID_PARAMETER;
    }
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqToneFrequency
 *
 * @param[in]   devId               Device ID
 * @param[in]   tunerId             Tuner ID
 * @param[in]   demodId             Demod ID
 * @param[in]   startFrequencyInKhz Start Frequency in KHz 
 * @param[in]   endFrequencyInKhz   End Frequency in KHz 
 * @param[in]   thresholdLevel      Threshold Level
 * @param[in/out]  numOfTones       Total Number of tones
 * @param[out]  toneInfoPtr         Pointer to [Frequency, Power] of tones
 *
 * @author Sateesh
 *
 * @date 12/01/2015 Initial release
 *
 * @detail This API retrieves tone frequency in specified frequency range
 * for a specified tuner.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqToneFrequency(UINT8 devId,
                                                MXL_HYDRA_TUNER_ID_E tunerId,
                                                MXL_HYDRA_DEMOD_ID_E demodId,
                                                UINT32 startFrequencyInKhz,
                                                UINT32 endFrequencyInKhz,
                                                SINT16 thresholdLevel,
                                                UINT8  *numOfTones,
                                                TONE_DETECTION_INFO_T *toneInfoPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_SPECTRUM_ERROR_CODE_E spectrumReadbackStatus;
  SINT16 *powerBuff = NULL;
  UINT16 numOfFreqSteps = 0, equalCount=0, totalCount = 0;
  UINT32 frequency = 0, peakFrequency = 0;
  SINT16 prevValue = 0, peakPower = 0;
  UINT32 freqStepSize = MXL_HYDRA_FREQ_408_20_STEP_SIZE;  // 408.20KHz frequency step size;
  MXL_BOOL_E risingEdge = MXL_FALSE;
  UINT8 maxTonesAllowed = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d, demodId=%d, startFrequencyInKhz=%d\n", tunerId, demodId, startFrequencyInKhz););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // validate input parameter
    if ((toneInfoPtr) && (numOfTones) && (*numOfTones) && ((startFrequencyInKhz >= MXL_HYDRA_SPECTRUM_MIN_FREQ_KHZ) && (startFrequencyInKhz < MXL_HYDRA_SPECTRUM_MAX_FREQ_KHZ)) \
        && ((endFrequencyInKhz > MXL_HYDRA_SPECTRUM_MIN_FREQ_KHZ) && (endFrequencyInKhz <= MXL_HYDRA_SPECTRUM_MAX_FREQ_KHZ)) \
        && (maxNumOfSteps[MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ]*sizeof(SINT16) <= MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH))
    {
      startFrequencyInKhz = ((startFrequencyInKhz*1000/freqStepSize)*freqStepSize)/1000;
      frequency = startFrequencyInKhz*1000;
      MXL_HYDRA_PRINT("StartFrequency: %d\n", startFrequencyInKhz);
      numOfFreqSteps = (endFrequencyInKhz - startFrequencyInKhz)*1000/freqStepSize; // Frequency band and 408.20KHz is step size.
      maxTonesAllowed = *numOfTones;

      powerBuff = (SINT16 *)MxLWare_HYDRA_OEM_MemAlloc(numOfFreqSteps*sizeof(SINT16));

      if (powerBuff)
      {
        mxlStatus = MxL_Ctrl_TunerPowerSpectrum(devId, tunerId, demodId, startFrequencyInKhz, numOfFreqSteps, powerBuff, &spectrumReadbackStatus);

        MXL_HYDRA_PRINT("numOfFreqSteps: %d spectrumReadbackStatus: %d\n", numOfFreqSteps, spectrumReadbackStatus);

        if ((mxlStatus == MXL_SUCCESS) && (spectrumReadbackStatus == MXL_SPECTRUM_NO_ERROR))
        {
          prevValue = powerBuff[0];
          peakPower = powerBuff[0];
          for (totalCount = 1, *numOfTones = 0; (totalCount < numOfFreqSteps) && (*numOfTones < maxTonesAllowed); totalCount++)
          {
            if (powerBuff[totalCount] >= thresholdLevel)
            {
              if (powerBuff[totalCount] > prevValue) // Rising
              {
                peakPower = powerBuff[totalCount];
                peakFrequency = frequency;
                risingEdge = MXL_TRUE;
              }
              else if ((powerBuff[totalCount] == prevValue) && (risingEdge == MXL_TRUE)) // Same Level
              {
                peakFrequency = frequency;
                equalCount++;
              }
              else   // Falling   
                risingEdge = MXL_FALSE;
            }
            if ((peakPower >= thresholdLevel) && (peakPower - powerBuff[totalCount] >= 3))  // Power level should be half to treat it as a tone
            {
              toneInfoPtr[*numOfTones].frequency = peakFrequency - ((equalCount+1)/2)*freqStepSize;
              toneInfoPtr[*numOfTones].signalLevel = peakPower;
              peakPower = 2*thresholdLevel;
              equalCount = 0;
              (*numOfTones)++;
            }
            prevValue = powerBuff[totalCount];
            frequency = frequency + freqStepSize; // 408.20KHz frequency step size;
          }
          MXL_HYDRA_PRINT("Total Tones: %d\n", *numOfTones);
        }
        MxLWare_HYDRA_OEM_MemFree((void *)powerBuff);
      }
      else
        mxlStatus = MXL_FAILURE;
        if (powerBuff == NULL)
          MXL_HYDRA_PRINT("Memory allocation failed\n");
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }
  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
#endif //MXL_ENABLE_SPECTRUM_RB

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodConstellationData
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  iSamplePtr
 * @param[out]  qSamplePtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to retrieve constellation data from given demodulator.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodConstellationData(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT16 *iSamplePtr, SINT16 *qSamplePtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if ((mxlStatus == MXL_SUCCESS) &&((iSamplePtr) && (qSamplePtr)))
  {
    // Lock demod status
    mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

    mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                           (HYDRA_DMD_DISPLAY_I_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                           &regData);

    *iSamplePtr = (SINT16)((regData >> 16) & 0xFFFF);
    *qSamplePtr = (SINT16)(regData & 0xFFFF);

    // Unlock demod status
    mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);
  }
  else
    mxlStatus = MXL_INVALID_PARAMETER;

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodLockStatus
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  demodLockPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used retrieve demod lock information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodLockStatus(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_LOCK_T *demodLockPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (demodLockPtr)
    {
      // Lock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read demod lock status
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                             (HYDRA_DMD_LOCK_STATUS_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                             &regData);
      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);

      demodLockPtr->fecLock = (regData == 1) ? MXL_TRUE : MXL_FALSE;

      if (demodLockPtr->fecLock == MXL_TRUE)
        MXL_HYDRA_PRINT("Demod Lock");
      else
        MXL_HYDRA_PRINT("Demod UNLOCK");
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqAllDemodLockStatus
 *
 * @param[in]   devId        Device ID
 * @param[out]  allDemodLockPtr
 *
 * @author Sateesh
 *
 * @date 03/30/2015 Initial release
 *
 * @detail This API shall be used retrieve lock status of all demods.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqAllDemodLockStatus(UINT8 devId, UINT8 *allDemodLockPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;
  UINT8 demodId = 0;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  MXL_HYDRA_DEBUG("Device Type = %d\n", devHandlePtr->deviceType);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (allDemodLockPtr)
    {
      *allDemodLockPtr = 0x0;
      for (demodId = MXL_HYDRA_DEMOD_ID_0; demodId < devHandlePtr->features.demodsCnt; demodId++)
      {
        MXL_HYDRA_DEBUG("Demod %d\n", demodId);
        // Lock demod status
        mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId, demodId);

        // read demod lock status
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                               (HYDRA_DMD_LOCK_STATUS_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                               &regData);
        // Unlock demod status
        mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId, demodId);

        if ((mxlStatus == MXL_SUCCESS) && (regData & 0x1) == 0x1)
        {
          *allDemodLockPtr |= (1 << demodId);
        }
        regData = 0x0;
      }
      MXL_HYDRA_DEBUG("All Demod Lock Status: 0x%x\n", *allDemodLockPtr);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodSNR
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  snrPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used retrieve demod SNR (Signal to Noise Ratio)
 * value in 100x dB.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodSNR(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT16 *snrPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (snrPtr)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read SNR from device
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                           (HYDRA_DMD_SNR_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                           &regData);
      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);

      *snrPtr = (SINT16)(regData & 0xFFFF);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodChanParams
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  demodTuneParamsPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used retrieve demod channel signal information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodChanParams(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TUNE_PARAMS_T *demodTuneParamsPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData[MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (demodTuneParamsPtr)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read demod channel parameters
      mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                  (HYDRA_DMD_STANDARD_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                  (MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE * 4), // 25 * 4 bytes
                                                  (UINT8 *)&regData[0]);

      demodTuneParamsPtr->standardMask = (MXL_HYDRA_BCAST_STD_E )regData[DMD_STANDARD_ADDR];
      demodTuneParamsPtr->spectrumInfo = (MXL_HYDRA_SPECTRUM_E )regData[DMD_SPECTRUM_INVERSION_ADDR];
      demodTuneParamsPtr->symbolRateKSps = (regData[DMD_SYMBOL_RATE_ADDR]/1000);
      demodTuneParamsPtr->freqSearchRangeKHz = (regData[DMD_FREQ_SEARCH_RANGE_IN_KHZ_ADDR]);

      switch(demodTuneParamsPtr->standardMask)
      {
        case MXL_HYDRA_DSS:
          demodTuneParamsPtr->params.paramsDSS.fec = (MXL_HYDRA_FEC_E)regData[DMD_FEC_CODE_RATE_ADDR];
          break;

        case MXL_HYDRA_DVBS:
          demodTuneParamsPtr->params.paramsS.fec = (MXL_HYDRA_FEC_E)regData[DMD_FEC_CODE_RATE_ADDR];
          demodTuneParamsPtr->params.paramsS.modulation = (MXL_HYDRA_MODULATION_E )regData[DMD_MODULATION_SCHEME_ADDR];
          demodTuneParamsPtr->params.paramsS.rollOff = (MXL_HYDRA_ROLLOFF_E)regData[DMD_SPECTRUM_ROLL_OFF_ADDR];
          break;

        case MXL_HYDRA_DVBS2:
          demodTuneParamsPtr->params.paramsS2.fec = (MXL_HYDRA_FEC_E)regData[DMD_FEC_CODE_RATE_ADDR];
          demodTuneParamsPtr->params.paramsS2.modulation = (MXL_HYDRA_MODULATION_E )regData[DMD_MODULATION_SCHEME_ADDR];
          demodTuneParamsPtr->params.paramsS2.pilots = (MXL_HYDRA_PILOTS_E )regData[DMD_DVBS2_PILOT_ON_OFF_ADDR];
          demodTuneParamsPtr->params.paramsS2.rollOff = (MXL_HYDRA_ROLLOFF_E)regData[DMD_SPECTRUM_ROLL_OFF_ADDR];
          break;
      }

      // read demod channel parameters
      mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                  (HYDRA_DMD_STATUS_CENTER_FREQ_IN_KHZ_ADDR + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                  (4), // 4 bytes
                                                  (UINT8 *)&regData[0]);

      demodTuneParamsPtr->frequencyInHz = (regData[0] * 1000);

      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);

    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodRxPowerLevel
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  inputPwrLevelPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to read RF input power in 10x dBm units of a
 * specific demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodRxPowerLevel(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT32 *inputPwrLevelPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (inputPwrLevelPtr)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // lock tuner status
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                        (HYDRA_DMD_STATUS_INPUT_POWER_ADDR + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                        &regData);

      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);

      *inputPwrLevelPtr = (SINT16)(regData & 0xFFFF);

    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqDemodErrorCounters
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  demodStatusPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to retrieve Demod signal information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodErrorCounters(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_STATUS_T *demodStatusPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData[8];
  UINT32 bcastStd = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (demodStatusPtr)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read demod error stats
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                        (HYDRA_DMD_STANDARD_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                        &bcastStd);

      demodStatusPtr->standardMask = (MXL_HYDRA_BCAST_STD_E )bcastStd;

      mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                  (HYDRA_DMD_DVBS2_CRC_ERRORS_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                  (7 * sizeof(UINT32)),
                                                  (UINT8 *)&regData[0]);

      MXL_HYDRA_PRINT("Standard  = %d\n", demodStatusPtr->standardMask);

      switch(demodStatusPtr->standardMask)
      {
        case MXL_HYDRA_DSS:
          demodStatusPtr->u.demodStatus_DSS.corrRsErrors = regData[3]; // uncorrected RS errors
          demodStatusPtr->u.demodStatus_DSS.rsErrors = regData[4]; // uncorrected RS errors
          demodStatusPtr->u.demodStatus_DSS.berCount = regData[5];
          demodStatusPtr->u.demodStatus_DSS.berWindow = regData[6];

          // for DSS read 1st iter BER values
          mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                  (HYDRA_DMD_DVBS_1ST_CORR_RS_ERRORS_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                  (4 * sizeof(UINT32)),
                                                  (UINT8 *)&regData[0]);

          demodStatusPtr->u.demodStatus_DSS.corrRsErrors1 = regData[0];
          demodStatusPtr->u.demodStatus_DSS.rsErrors1 = regData[1];
          demodStatusPtr->u.demodStatus_DSS.berCount_Iter1 = regData[2];
          demodStatusPtr->u.demodStatus_DSS.berWindow_Iter1 = regData[3];

          break;

        case MXL_HYDRA_DVBS:
          demodStatusPtr->u.demodStatus_DVBS.corrRsErrors = regData[3]; // uncorrected RS errors
          demodStatusPtr->u.demodStatus_DVBS.rsErrors = regData[4]; // uncorrected RS errors
          demodStatusPtr->u.demodStatus_DVBS.berCount = regData[5];
          demodStatusPtr->u.demodStatus_DVBS.berWindow = regData[6];

          // for DVB-S read 1st iter BER values
          mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                  (HYDRA_DMD_DVBS_1ST_CORR_RS_ERRORS_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                  (4 * sizeof(UINT32)),
                                                  (UINT8 *)&regData[0]);

          demodStatusPtr->u.demodStatus_DVBS.corrRsErrors1 = regData[0];
          demodStatusPtr->u.demodStatus_DVBS.rsErrors1 = regData[1];
          demodStatusPtr->u.demodStatus_DVBS.berCount_Iter1 = regData[2];
          demodStatusPtr->u.demodStatus_DVBS.berWindow_Iter1 = regData[3];

          break;

        case MXL_HYDRA_DVBS2:
          demodStatusPtr->u.demodStatus_DVBS2.crcErrors = regData[0];
          demodStatusPtr->u.demodStatus_DVBS2.packetErrorCount = regData[1];
          demodStatusPtr->u.demodStatus_DVBS2.totalPackets = regData[2];

          break;
      }

      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);
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
 * @brief MxLWare_HYDRA_API_ReqDemodScaledBER
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]
 *
 * @author Sateesh
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to retrieve Demod signal information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodScaledBER(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SCALED_BER_T *scaledBer)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData[2];
  UINT32 bcastStd = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (scaledBer)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read bcast standard
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                        (HYDRA_DMD_STANDARD_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                        &bcastStd);

      if (( bcastStd == MXL_HYDRA_DSS) || ( bcastStd == MXL_HYDRA_DVBS))
      {
        mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId,
                                                      (DMD0_STATUS_DVBS_1ST_SCALED_BER_COUNT_ADDR + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                                      (2 * sizeof(UINT32)),
                                                      (UINT8 *)&regData[0]);

        scaledBer->scaledBerIter1 = regData[0];
        scaledBer->scaledBerIter2 = regData[1];
      }

      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgRssiMonitor
 *
 * @param[in]  devId            Device ID
 * @param[in]  tunerId          Tuner ID
 * @param[in]  adcRssiThreshold defined ADC RSSI threshold (dBm) / valid range (-60 <= threshold <=0)
 * @param[in]  enable           enable/disable RSSI Monitoring
 *
 * @author Aman Garcha
 *
 * @date 04/20/2015 Initial release
 *
 * @detail This API should be used to enable or disable ADC RSSI Monitoring.
 * Allows for RSSI interrupt monitoring, where the a host interrupt will be 
 * issued if the defined threshold is crossed.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 * @usage 
 * + Bit 16 of the interrupt mask must be enabled for the RSSI Monitor interrupt
 * + RSSI Monitoring API requires that a tune must be initiated first.
 * + Defined threshold must be between -60dBm and 0dBm (-60dBm <= threshold <= 0dBm)
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgRssiMonitor(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, SINT32 adcRssiThreshold, MXL_BOOL_E enable)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  MXL_HYDRA_RSSI_MONITOR_INFO_T monitorRssiParams;

  MXLENTERAPISTR(devId);


  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    if (((MXL_HYDRA_RSSI_MONITOR_MIN_THRESHOLD <= adcRssiThreshold) && (adcRssiThreshold <= MXL_HYDRA_RSSI_MONITOR_MAX_THRESHOLD)) \
         && (tunerId < devHandlePtr->features.tunersCnt))
    {

      //convert rssi to raw value
      monitorRssiParams.adcRssiThreshold = adcRssiThreshold;
      monitorRssiParams.enable = (UINT32) enable;
      monitorRssiParams.tunerId = (UINT32) tunerId;
      MXLDBG2(MXL_HYDRA_DEBUG("Tuner %d RSSI Monitor threshold: %d\n", tunerId, adcRssiThreshold););
      BUILD_HYDRA_CMD(MXL_HYDRA_RSSI_MONITOR_CMD, MXL_CMD_WRITE, sizeof(MXL_HYDRA_RSSI_MONITOR_INFO_T), &monitorRssiParams, cmdBuff);

      // send command to device
  	  mxlStatus = MxLWare_HYDRA_SendCommand(devId, sizeof(MXL_HYDRA_RSSI_MONITOR_INFO_T) + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
    }
    else
    {
      // adcRssiThreshold not within valid range or Tuner is beyond tuners count.
  	  mxlStatus = MXL_INVALID_PARAMETER;
  	  MXLERR(MXL_HYDRA_DEBUG("Tuner %d RSSI Monitor threshold is out of bounds: %d\n", tunerId, adcRssiThreshold););
    }
  }
  

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqRssiMonitorInterruptStatus
 *
 * @param[in]  devId                       Device ID
 * @param[in]  rssiInterruptStatusMaskPtr  Rssi Interrupt Status return pointer (Tuner0 = LSB)
 *
 * @author Aman Garcha
 *
 * @date 04/20/2015 Initial release
 *
 * @detail This API should be used to obtain the RSSI Monitor interrupt Status
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 * @usage Requires RSSI Monitoring to be enabled via MxLWare_HYDRA_API_CfgRssiMonitor()
 * + Bit 16 of the interrupt mask must be enabled for the RSSI Monitor interrupt
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqRssiMonitorInterruptStatus(UINT8 devId, UINT32 * rssiInterruptStatusMaskPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);


  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    if (rssiInterruptStatusMaskPtr)
    {
      //read rssi monitor status for host return
      mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_RSSI_MONITOR_STATUS_READBACK, (UINT32 *) rssiInterruptStatusMaskPtr);

	   if (mxlStatus == MXL_SUCCESS)
       {
         //clear status
         mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, HYDRA_RSSI_MONITOR_STATUS_READBACK, 0);
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
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqAdcRssiPower
 *
 * @param[in]   devId           Device ID
 * @param[in]   tunerId         Tuner ID
 * @param[out]  adcRssiPwr      ADC RSSI Power
 *
 * @author Sateesh
 *
 * @date 10/21/2013 Initial release
 *
 * @detail This API should be used to read the ADC RSSI power.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqAdcRssiPower(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, SINT32 *adcRssiPwr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (adcRssiPwr)
    {
      UINT32 tunId;

      tunId = (UINT32) tunerId;
      BUILD_HYDRA_CMD(MXL_HYDRA_DEV_REQ_PWR_FROM_ADCRSSI_CMD, MXL_CMD_WRITE, sizeof(UINT32), &tunId, cmdBuff);

      // send command to device
      mxlStatus = MxLWare_HYDRA_SendCommand(devId, sizeof(MXL_HYDRA_TUNER_ID_E) + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);

      MxLWare_HYDRA_OEM_SleepInMs(50);

      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, POWER_FROM_ADCRSSI_READBACK, (UINT32 *) adcRssiPwr);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_ReqTunerSplitterAttenuation
 *
 * @param[in]   devId            Device ID
 * @param[out]  splitterAttnPtr  Splitter Attenuation Return Pointer
 *
 * @author Cres R
 *
 * @date 03/08/2016 Initial release
 *
 * @detail This API should be used to calculate the splitter attenuation in dB.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerSplitterAttenuation(UINT8 devId, UINT32 * splitterAttnPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 afe_data = 0;
  UINT32 wb_data = 0;
  UINT32 rf1_msb;
  UINT32 lna_msb;
  UINT32 rf1;
  UINT32 lna;

  MXLENTERAPISTR(devId);

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (splitterAttnPtr)
    {
 
      mxlStatus = MxLWare_HYDRA_ReadRegister(devId, AFE_REG_D2A_TA_RFFE_LNA_BO_1P8_BASEADDR, &afe_data);
      rf1_msb = afe_data & 0x00000020;   //Bit 5 of AFE Reg
      lna_msb = afe_data & 0x00000010;   //Bit 4 of AFE Reg
      
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, WB_DFE2_DFE_FB_LNA_BO_BASEADDR, &wb_data);
      rf1 = wb_data & 0x00000007;       //Bits 0-2 of WB Reg
      lna = wb_data & 0x00000300;       //Bits 8-9 of WB Reg

      //Join the bit fields and add up the Back off steps
      //Each Back off step represents 2 dB so multiply total by 2
      *splitterAttnPtr = 2 * (((rf1_msb >> 2) | rf1) + ((lna_msb >> 2) | (lna >> 8)));
      MXLDBG1(MXL_HYDRA_PRINT("Splitter attenuation calculated (in dB) is = %d\n", *splitterAttnPtr));
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
 * @brief MxLWare_HYDRA_API_CfgClearDemodErrorCounters
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to retrieve Demod signal information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgClearDemodErrorCounters(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  UINT32 demodIndex = (UINT32)demodId;
  UINT8 cmdSize = sizeof(UINT32);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_RESET_FEC_COUNTER_CMD, MXL_CMD_WRITE, cmdSize, &demodIndex, cmdBuff);
    mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDemodSignalOffsetInfo
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[out]  demodSigOffsetInfoPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * @detail This API shall be used to retrieve carrier offset & symbol offset
 * frequency information.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodSignalOffsetInfo(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SIG_OFFSET_INFO_T *demodSigOffsetInfoPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (demodSigOffsetInfoPtr)
    {
      // Lock demod status
      mxlStatus = HYDRA_DEMOD_STATUS_LOCK(devId,demodId);

      // read demod signal offset info
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                            (HYDRA_DMD_FREQ_OFFSET_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                            &regData);

      demodSigOffsetInfoPtr->carrierOffsetInHz = (SINT32)regData;

      // read demod signal offset info
      mxlStatus |= MxLWare_HYDRA_ReadRegister(devId,
                                            (HYDRA_DMD_STR_FREQ_OFFSET_ADDR_OFFSET + HYDRA_DMD_STATUS_OFFSET(demodId)),
                                            &regData);

      demodSigOffsetInfoPtr->symbolOffsetInSymbol = (SINT32)regData;
      MXL_HYDRA_PRINT("symbolOffsetInSymbol = %d\n", demodSigOffsetInfoPtr->symbolOffsetInSymbol);

      // Unlock demod status
      mxlStatus |= HYDRA_DEMOD_STATUS_UNLOCK(devId,demodId);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 * @ingroup Tuner_and_Demodulator_APIs
 * @brief MxLWare_HYDRA_API_CfgDemodScrambleCode
 *
 * @param[in]   devId        Device ID
 * @param[in]   demodId
 * @param[in]   demodScrambleInfoPtr
 *
 * @author Mahee
 *
 * @date 09/21/2012 Initial release
 *
 * @detail This API shall be used when tuning for a channel.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodScrambleCode (UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SCRAMBLE_INFO_T *demodScrambleInfoPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_DEMOD_SCRAMBLE_CODE_T hydraScrambleCode;

  UINT8 cmdSize = sizeof(hydraScrambleCode);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT8 reqType;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (demodScrambleInfoPtr)
    {
      // send demod scramble code to the device
      hydraScrambleCode.demodIndex = (UINT32)demodId;
      MXLWARE_OSAL_MEMCPY(hydraScrambleCode.scrambleSequence, demodScrambleInfoPtr->scrambleSequence, (MXL_DEMOD_SCRAMBLE_SEQ_LEN * sizeof(UINT8)));
      hydraScrambleCode.scrambleCode = demodScrambleInfoPtr->scrambleCode;

      // build command manually instead of macro
      reqType = MXL_CMD_WRITE;
      cmdBuff[0] = ((reqType == MXL_CMD_WRITE) ? MXL_HYDRA_PLID_CMD_WRITE : MXL_HYDRA_PLID_CMD_READ);
      cmdBuff[1] = (cmdSize > 254)? 0xFF : (UINT8)(cmdSize + 4);
      cmdBuff[2] = (UINT8)0;
      cmdBuff[3] = (UINT8)MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD;
      cmdBuff[4] = 0x00;
      cmdBuff[5] = 0x00;
      cmdSize += 6;

      cmdBuff[6] = GET_BYTE(hydraScrambleCode.demodIndex, 0);     // reg addr byte
      cmdBuff[7] = GET_BYTE(hydraScrambleCode.demodIndex, 1);     // reg addr byte
      cmdBuff[8] = GET_BYTE(hydraScrambleCode.demodIndex, 2);     // reg addr byte
      cmdBuff[9] = GET_BYTE(hydraScrambleCode.demodIndex, 3);     // reg addr byte

      MXLWARE_OSAL_MEMCPY((void *)&cmdBuff[10], (const void *)&(demodScrambleInfoPtr->scrambleSequence[0]), (MXL_DEMOD_SCRAMBLE_SEQ_LEN * sizeof(UINT8)));

      cmdBuff[22] = GET_BYTE(hydraScrambleCode.scrambleCode, 0);   // reg addr byte
      cmdBuff[23] = GET_BYTE(hydraScrambleCode.scrambleCode, 1);   // reg addr byte
      cmdBuff[24] = GET_BYTE(hydraScrambleCode.scrambleCode, 2);   // reg addr byte
      cmdBuff[25] = GET_BYTE(hydraScrambleCode.scrambleCode, 3);   // reg addr byte

      mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize, &cmdBuff[0]);
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
 * @brief MxLWare_HYDRA_API_CfgDemodSearchFreqOffset
 *
 * @param[in] devId           Device ID
 * @param[in] demodId         Demod Id
 * @param[in] searchFreqType  Demod Frequency Offset Search Range
 *
 * @author Sateesh
 *
 * @date 07/02/2013 Initial release
 *
 * @detail This API should be used to configure Demod Frequency Offset Search
 * Range demod Equalizers.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E searchFreqType)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  MXL58x_CFG_FREQ_OFF_SEARCH_RANGE_T searchFreqRangeCmd;
  UINT8 cmdSize = sizeof(searchFreqRangeCmd);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););
  MXLENTERAPI(MXL_HYDRA_PRINT("searchFreqType=%d\n", searchFreqType););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // build Demod Frequency Offset Search command
    searchFreqRangeCmd.demodIndex = demodId;
    searchFreqRangeCmd.searchType = (UINT32) searchFreqType;
    BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_FREQ_OFFSET_SEARCH_RANGE_CMD, MXL_CMD_WRITE, cmdSize, &searchFreqRangeCmd, cmdBuff);

    // send command to device
    mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_GainStepControl
 *
 * @param[in] devId         - Device ID
 * @param[in] tunerId       - Tuner Id
 * @param[in] gainState     - Gain state (0-8)
 *
 * @author Sateesh
 *
 * @date 07/02/2013 Initial release
 *
 * @detail This API should be used to freeze the AGC and control gain.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_GainStepControl(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT8 gainState)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  UINT32 lnaBo1P8 = 0;
  UINT32 rf1Bo1P8 = 0;
  UINT32 data = 0;

  UINT8 rficState = 2*gainState;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d\n", tunerId););
  MXLENTERAPI(MXL_HYDRA_PRINT("state=%d\n", gainState););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    /* This is done to make a tuner ID swap for 5x2 SKUs 
       in order to meet the Data sheet requirements. 
       Look at Jira HYDRA-1925 for more details. */
    if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582) || \
        (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582C) || \
        (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542) || \
        (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C))
    {
      if (tunerId == MXL_HYDRA_TUNER_ID_0)
        tunerId = MXL_HYDRA_TUNER_ID_2;
      else if (tunerId == MXL_HYDRA_TUNER_ID_1)
        tunerId = MXL_HYDRA_TUNER_ID_0;
    }
    if ((gainState <= 8) && (tunerId < devHandlePtr->features.tunersCnt))
    {
      // Freeze AGC in Firmware
      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, DBG_ENABLE_DISABLE_AGC, 0x3);

      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, WB_DFE0_DFE_FB_AGC_BASEADDR + tunerId * 0x100000, 0);

      if (mxlStatus == MXL_SUCCESS)
      {
        // d2a_rffe_lna_bo_1p8
        lnaBo1P8 = (rficState < 6) ? rficState : 6;

        // d2a_rffe_rf1_bo_1p8
        rf1Bo1P8 = (rficState < 6) ? 0 : (rficState-6);

        // d2a_tX_rffe_rf1_bo_1p8 <3> && d2a_tX_rffe_lna_bo_1p8<2>
        data = (((rf1Bo1P8 >> 3) & 0x1) << 1) | ((lnaBo1P8 >> 2) & 0x1);
        mxlStatus = MxLWare_HYDRA_WriteRegister(devId, AFE_REG_D2A_TA_RFFE_LNA_BO_1P8_BASEADDR, ((data & 0x3) << (tunerId << 1)));

        data = 0;
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, WB_DFE0_DFE_FB_RF1_BASEADDR + tunerId * 0x100000, &data);

        if (mxlStatus == MXL_SUCCESS)
        {
          data = (data >> 10) << 10;
          data |= (((lnaBo1P8 & 0x3) << 8) | (0xBUL << 0x4) | (rf1Bo1P8 & 0x7));
          mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, WB_DFE0_DFE_FB_RF1_BASEADDR + tunerId * 0x100000, data);

          mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, WB_DFE0_DFE_FB_AGC_BASEADDR + tunerId * 0x100000, 1);

          // d2a_rffe_rf1_cap_1p8
          switch (tunerId)
          {
            case MXL_HYDRA_TUNER_ID_0:
              mxlStatus |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_TA_RFFE_RF1_CAP_1P8, 0);
              break;
            case MXL_HYDRA_TUNER_ID_1:
              mxlStatus |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_TB_RFFE_RF1_CAP_1P8, 0);
              break;
            case MXL_HYDRA_TUNER_ID_2:
              mxlStatus |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_TC_RFFE_RF1_CAP_1P8, 0);
              break;
            case MXL_HYDRA_TUNER_ID_3:
              mxlStatus |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_TD_RFFE_RF1_CAP_1P8, 0);
              break;
            default:
              break;
          }
        }
      }
    }
    else
    {
      mxlStatus = MXL_INVALID_PARAMETER;
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_IsFscTunerDone
 *
 * @param[in] devId         - Device ID
 * @param[in] tunerId        - Tuner Id
 *
 * @author Sateesh
 *
 * @date 12/02/2013 Initial release
 *
 * @detail This API should be used to check if FSC is complete.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_BOOL_E MxLWare_HYDRA_API_IsFscTunerDone(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_INVALID_PARAMETER;
  MXL_BOOL_E tunerDone = MXL_FALSE;
  UINT32 data = 0;
  UINT32 count = 100;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d\n", tunerId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (tunerId < devHandlePtr->features.tunersCnt)
    {
      mxlStatus = MXL_FAILURE;
      while ((tunerDone != MXL_TRUE) && (count--))
      {
        mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_TUNER_ENABLE_COMPLETE, &data);
        if ((mxlStatus == MXL_SUCCESS) && (((data>>tunerId) & 0x1)))
        {
          tunerDone = MXL_TRUE;
          break;
        }
        MxLWare_HYDRA_OEM_SleepInMs(10);
      }
    }
    else
    {
      mxlStatus = MXL_INVALID_PARAMETER;
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return tunerDone;
}
