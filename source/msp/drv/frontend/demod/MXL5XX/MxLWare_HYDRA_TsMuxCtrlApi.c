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
#include "MxLWare_HYDRA_Registers.h"
#include "MxLWare_HYDRA_TsMuxCtrlApi.h"

static MXL_STATUS_E MxLWare_HYDRA_CfgXPTXBar(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_ID_E tsOutId);

void MxL_Ctrl_Set_MuxMode_54x(UINT8 devId, MXL_HYDRA_TS_MUX_TYPE_E tsMuxType)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  if(MXL_HYDRA_TS_MUX_4_TO_1 == tsMuxType)
  {
    /* setting up Mux mode for both slice 0 & 1
        For 54x devices in 4:1 mux mode, move physical demods 4 & 5 from slice 1 to slice 0 becasue mux-ing across 
        slices is not possible. So we need to write xbar register with 0x77775432. Function MxLWare_HYDRA_CfgXPTXBar() 
        has the second argument demod ID (logical) and TS ID (logical) and these logical IDs will be mapped to 
        physical IDs in firmware. If user doesn't want to get either demod ID/TS ID to be mapped in firmware, 
        MXL_LOGICAL_TO_PHYSICAL_BYPASS() has to be used instead sothat firmware skips the mapping.
    */

    mxlStatus = MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_0, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_0));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_1, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_1));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_2, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_2));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_3, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_3));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_7), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_4));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_7), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_5));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_7), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_6));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_7), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_7));

    // Enable all outputs
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT0, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT1, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT2, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT3, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT4, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT5, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT6, 1);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT7, 1);
  }
  else
  {
    // Resetting the xbar with default settings, i.e., 0x76543210 for non-mux case
    mxlStatus = MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_0, MXL_HYDRA_TS_ID_0);
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_1, MXL_HYDRA_TS_ID_1);
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_2, MXL_HYDRA_TS_ID_2);
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_HYDRA_DEMOD_ID_3, MXL_HYDRA_TS_ID_3);
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_0), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_0));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_1), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_1));
    mxlStatus |= MxLWare_HYDRA_CfgXPTXBar(devId, MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_DEMOD_ID_6), MXL_LOGICAL_TO_PHYSICAL_BYPASS(MXL_HYDRA_TS_ID_6));
  }
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSMuxMode
 *
 * @param[in]   devId           Device ID
 * @param[in]   tsMuxType       TS MUX type
 *
 * @author Mahee
 *
 * @date 01/24/2013
 *
 * This API will configure TS mux of the device
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTSMuxMode(UINT8 devId, MXL_HYDRA_TS_MUX_TYPE_E tsMuxType)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 streamMuxType = 0;
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tsMuxType = %d\n", tsMuxType););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    switch(tsMuxType)
    {
      case MXL_HYDRA_TS_MUX_DISABLE:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_DISABLE\n");
        devHandlePtr->tsMuxModeSlice0 = MXL_HYDRA_TS_MUX_DISABLE;
        devHandlePtr->tsMuxModeSlice1 = MXL_HYDRA_TS_MUX_DISABLE;
        streamMuxType = 1;
        break;

      case MXL_HYDRA_TS_MUX_2_TO_1:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_2_TO_1\n");
        devHandlePtr->tsMuxModeSlice0 = MXL_HYDRA_TS_MUX_2_TO_1;
        devHandlePtr->tsMuxModeSlice1 = MXL_HYDRA_TS_MUX_2_TO_1;
        streamMuxType = 2;
        break;

      case MXL_HYDRA_TS_MUX_4_TO_1:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_4_TO_1\n");
        devHandlePtr->tsMuxModeSlice0 = MXL_HYDRA_TS_MUX_4_TO_1;
        devHandlePtr->tsMuxModeSlice1 = MXL_HYDRA_TS_MUX_4_TO_1;
        streamMuxType = 3;
        break;
    }
    if (MXL_HYDRA_SKU_54X == devHandlePtr->skuFamily)
    {
      MxL_Ctrl_Set_MuxMode_54x(devId, tsMuxType);
    }

    // No MUX for regular pids - slice 0 & 1
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE0, streamMuxType);

    // No MUX for Known pids - slice 1
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE1, streamMuxType);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSMixMuxMode
 *
 * @param[in]   devId        Device ID
 * @param[in]   tsGroupType  TS group type
 * @param[in]   tsMuxType    TS MUX type
 *
 * @author Mahee
 *
 * @date 01/24/2013
 *
 * This API will configure TS mux of the device
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTSMixMuxMode(UINT8 devId, MXL_HYDRA_TS_GROUP_E tsGroupType, MXL_HYDRA_TS_MUX_TYPE_E tsMuxType)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 streamMuxType = 0;
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tsMuxType = %d\n", tsMuxType););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    switch(tsMuxType)
    {
      case MXL_HYDRA_TS_MUX_DISABLE:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_DISABLE\n");
        streamMuxType = 1;
        break;

      case MXL_HYDRA_TS_MUX_2_TO_1:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_2_TO_1\n");
        streamMuxType = 2;

        break;

      case MXL_HYDRA_TS_MUX_4_TO_1:
        MXL_HYDRA_PRINT("tsMuxType = MXL_HYDRA_TS_MUX_4_TO_1\n");
        streamMuxType = 3;
        break;
    }
    if (MXL_HYDRA_SKU_54X == devHandlePtr->skuFamily)
    {
      MxL_Ctrl_Set_MuxMode_54x(devId, tsMuxType);
    }

    if (tsGroupType == MXL_HYDRA_TS_GROUP_0_3)
    {
      // update device extention for mux mode group 0
      devHandlePtr->tsMuxModeSlice0 = tsMuxType;

      // Configure MUX mode for slice 0 (TS0, TS1, TS2 & TS3)
      MXL_HYDRA_PRINT("TS0 - TS3 : %d\n", streamMuxType);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE0, streamMuxType);
    }
    else if (tsGroupType == MXL_HYDRA_TS_GROUP_4_7)
    {
      // update device extention for mux mode group 1
      devHandlePtr->tsMuxModeSlice1 = tsMuxType;

      // Configure MUX mode for slice 1 (TS4, TS5, TS6 & TS7)
      MXL_HYDRA_PRINT("TS4 - TS7 : %d \n", streamMuxType);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE1, streamMuxType);
    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}



/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSErrorIndicationCtrl
 *
 * @param[in]   devId             Device ID
 * @param[in]   teiCtrl           Enable or Disable TEI (Transport Error Indicator) 
 *
 * @author Aman
 *
 * @date 08/25/2014
 *
 * This API will enable or disable TEI (Transport Error Indicator) 
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSErrorIndicationCtrl(UINT8 devId, MXL_BOOL_E teiCtrl)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("teiCtrl = %d\n", teiCtrl););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus |= SET_REG_FIELD_DATA(devId, DMD_TEI_ENA , teiCtrl);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}


/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSTimeMuxOutput
 *
 * @param[in]   devId             Device ID
 * @param[in]   tsGroupType       TS group type
 * @param[in]   tsTimeMuxCtrl     Enable or Disable Time MUX mode
 *
 * @author Mahee
 *
 * @date 01/24/2013
 *
 * This API will configure TS mux of the device
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTSTimeMuxOutput(UINT8 devId, MXL_BOOL_E tsTimeMuxCtrl)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tsTimeMuxCtrl = %d\n", tsTimeMuxCtrl););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING0, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING1, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING2, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING3, tsTimeMuxCtrl);

    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING4, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING5, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING6, tsTimeMuxCtrl);
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_OUTPUT_MODE_MUXGATING7, tsTimeMuxCtrl);

    // configure time-mux mode
    if (tsTimeMuxCtrl == MXL_TRUE)
    {
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT0, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT1, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT2, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT3, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT4, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT5, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT6, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_OUTPUT7, 1);

      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_PID_MUX_SELECT0, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_KNOWN_PID_MUX_SELECT0, 1);

      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_PID_MUX_SELECT1, 1);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_KNOWN_PID_MUX_SELECT1, 1);

      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE1, 3);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_STREAM_MUXMODE0, 3);
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

// function to update software pid filter bank context in the device
static MXL_STATUS_E MxL_HYDRA_CfgChangePidFilterBankContext(UINT8 devId, MXL_HYDRA_TS_ID_E tsId, MXL_HYDRA_TS_MUX_TYPE_E muxType)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;
  UINT32 mask = 0;

  // determine which slice to update
  if (tsId < MXL_HYDRA_TS_ID_4)
  {
    // get current bank context
    mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, 0x90700190, &regData);

    switch(muxType)
    {
      default:
      case MXL_HYDRA_TS_MUX_DISABLE: mask = 0x00000FF0; break;
      case MXL_HYDRA_TS_MUX_2_TO_1: mask = 0x00000550; break;
      case MXL_HYDRA_TS_MUX_4_TO_1: mask = 0x00000110; break;
    }

    if ((regData & 0x03) == 0x03)
    {
      regData &= (UINT32)(~0x00000003);
      regData |= mask;
    }
    else
    {
      regData |= (UINT32)0x00000003;
      regData &= ~(mask);
    }

    // flip bank context
    // SW can update pid filter table - at this point HW will be using different bank context
    mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, 0x90700190, regData);
  }
  else
  {
    // get current bank context
    mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, 0x907001B0, &regData);

    switch(muxType)
    {
      default:
      case MXL_HYDRA_TS_MUX_DISABLE: mask = 0x000000F0; break;
      case MXL_HYDRA_TS_MUX_2_TO_1: mask = 0x00000050; break;
      case MXL_HYDRA_TS_MUX_4_TO_1: mask = 0x00000010; break;
    }

    if ((regData & 0x03) == 0x03)
    {
      regData &= (UINT32)(~0x00000003);
      regData |= mask;
    }
    else
    {
      regData |= (UINT32)0x00000003;
      regData &= ~(mask);
    }

    // flip bank context
    // SW can update pid filter table - at this point HW will be using different bank context
    mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, 0x907001B0, regData);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSPidFilterCtrl
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodID      Demod ID
 * @param[in]   tsFiltCtrl        Allow or Drop all PID's for the demod mentioned above
 *
 * @author Mahee
 *
 * @date 01/24/2013
 *
 * This API will allow or drop all pids for a particular demod
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTSPidFilterCtrl(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_PID_FLT_CTRL_E tsFiltCtrl)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_TS_MUX_TYPE_E muxType;

  // zero array - array big to accomodate 2 32-bit registers used for shared pid table
  //UINT8 data[(MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT * (2 * sizeof(UINT32)))];
  const UINT8 data[250] = {0,};  // initialize the constant data array here to make sure it is always set to all zeros

  UINT16 bytesLeft = 0, bytesToSend = 0, offset = 0;
  UINT8 j = 0, iter = 0;
  MXL_HYDRA_TS_ID_E tsId = MXL_HYDRA_TS_MAX;
  MXL_HYDRA_TS_ID_E listTsId[MXL_HYDRA_TS_MAX] = {0, };

  // Array to get register address of known PID filter
  UINT32 knownPidregAddr[MXL_HYDRA_DEMOD_MAX] = {(XPT_KNOWN_PID_BASEADDR), (XPT_KNOWN_PID_BASEADDR + (1 * 0x80)),
                                         (XPT_KNOWN_PID_BASEADDR + (2 * 0x80)), (XPT_KNOWN_PID_BASEADDR + (3 * 0x80)),
                                         (XPT_KNOWN_PID_BASEADDR1), (XPT_KNOWN_PID_BASEADDR1 + (1 * 0x80)),
                                         (XPT_KNOWN_PID_BASEADDR1 + (2 * 0x80)), (XPT_KNOWN_PID_BASEADDR1 + (3 * 0x80))};

  // Array to get register address of shared PID filter
  UINT32 sharedPidregAddr[MXL_HYDRA_DEMOD_MAX] = {(XPT_PID_BASEADDR), (XPT_PID_BASEADDR + (1 * 0x200)),
                                         (XPT_PID_BASEADDR + (2 * 0x200)), (XPT_PID_BASEADDR + (3 * 0x200)),
                                         (XPT_PID_BASEADDR1), (XPT_PID_BASEADDR1 + (1 * 0x200)),
                                         (XPT_PID_BASEADDR1 + (2 * 0x200)), (XPT_PID_BASEADDR1 + (3 * 0x200))};

  MXL_REG_FIELD_T xpt_pid_filt_ctrl[MXL_HYDRA_DEMOD_MAX] = {
                                                             {XPT_PID_DEFAULT_DROP0},
                                                             {XPT_PID_DEFAULT_DROP1},
                                                             {XPT_PID_DEFAULT_DROP2},
                                                             {XPT_PID_DEFAULT_DROP3},
                                                             {XPT_PID_DEFAULT_DROP4},
                                                             {XPT_PID_DEFAULT_DROP5},
                                                             {XPT_PID_DEFAULT_DROP6},
                                                             {XPT_PID_DEFAULT_DROP7}};

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodID = %d PID filter type = %d\n", demodId, tsFiltCtrl););

  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    mxlStatus = MxL_Ctrl_GetPhyTsID(devId, demodId, listTsId);
    if (mxlStatus == MXL_SUCCESS)
    {
      for (iter = 0; iter < listTsId[0]; iter++)
      {
        tsId = listTsId[iter+1];
        MXL_HYDRA_PRINT("after map demodID = %d PID filter type = %d\n", demodId, tsFiltCtrl);
        MXL_HYDRA_PRINT("fix pids: %d reg pids: %d\n", devHandlePtr->maxFixPidEntries, devHandlePtr->maxRegPidEntries);

        if (tsFiltCtrl < MXL_HYDRA_TS_INVALIDATE_PID_FILTER)
        {
          // configure PID control - drop or allow all
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xpt_pid_filt_ctrl[tsId].regAddr,    // Reg Addr
                                                xpt_pid_filt_ctrl[tsId].lsbPos,     // LSB pos
                                                xpt_pid_filt_ctrl[tsId].numOfBits,  // Num of bits
                                                tsFiltCtrl);                           // Allow or Drop all PIDS
        }
        else
        {
          // Invalidate PID filter table in the MxLWare and in device
          if (tsId <= MXL_HYDRA_TS_ID_3) muxType = devHandlePtr->tsMuxModeSlice0;
          else muxType = devHandlePtr->tsMuxModeSlice1;

          // Update pid filter bank context
          mxlStatus |= MxL_HYDRA_CfgChangePidFilterBankContext(devId, tsId, muxType);

          if (devHandlePtr->maxFixPidEntries > 0)
          {
            // Invalidate FIXED PID table
            mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                     knownPidregAddr[tsId],
                                                     ((devHandlePtr->maxFixPidEntries) * sizeof(UINT32)),
                                                     (UINT8*)&data[0]);
          }

#if 0
        // Invalidate Shared PID Table - has to use 2 block writes as size of
        // block write is limited to 250 bytes
        mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                   sharedPidregAddr[demodId],
                                                   (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   &data[0]);

        mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                   sharedPidregAddr[demodId] + (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   &data[0]);
#else
          // Invalidate Shared PID Table - has to use 2 block writes as size of
          // block write is limited to 250 bytes

          bytesLeft = devHandlePtr->maxRegPidEntries * (2 * sizeof(UINT32));
          offset = 0;
          while (bytesLeft != 0)
          {
            bytesToSend = (bytesLeft > 250) ? 250: bytesLeft;
            mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                     sharedPidregAddr[tsId] + offset,
                                                     bytesToSend,
                                                     (UINT8*)&data[0]);
            bytesLeft -= bytesToSend;
            offset += bytesToSend;
          }
#endif

          // Update pid filter bank context
          mxlStatus |= MxL_HYDRA_CfgChangePidFilterBankContext(devId, tsId, muxType);

          if (devHandlePtr->maxFixPidEntries > 0)
          {
            // Invalidate FIXED PID table
            mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                     knownPidregAddr[tsId],
                                                     ((devHandlePtr->maxFixPidEntries) * sizeof(UINT32)),
                                                     (UINT8*)&data[0]);
          }

#if 0
          // Invalidate Shared PID Table - has to use 2 block writes as size of
          // block write is limited to 250 bytes
        mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                   sharedPidregAddr[demodId],
                                                   (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   &data[0]);

        mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                   sharedPidregAddr[demodId] + (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   (MXL_HYDRA_SHARED_PID_FILT_SIZE_DEFAULT * (sizeof(UINT32))),
                                                   &data[0]);
#else
          // Invalidate Shared PID Table - has to use 2 block writes as size of
          // block write is limited to 250 bytes
          bytesLeft = devHandlePtr->maxRegPidEntries * (2 * sizeof(UINT32));
          offset = 0;
          while (bytesLeft != 0)
          {
            bytesToSend = (bytesLeft > 250) ? 250: bytesLeft;
            mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                     sharedPidregAddr[tsId] + offset,
                                                     bytesToSend,
                                                     (UINT8*)&data[0]);
            bytesLeft -= bytesToSend;
            offset += bytesToSend;
          }
#endif


          // clear MxLWare PID filter table
          // Init pid filters
          MXLWARE_OSAL_MEMSET(devHandlePtr->fixedPidFilt[tsId], 0, (devHandlePtr->maxFixPidEntries * sizeof(MXL_HYDRA_PID_T)));
          MXLWARE_OSAL_MEMSET(devHandlePtr->regPidFilt[tsId], 0, (devHandlePtr->maxRegPidEntries * sizeof(MXL_HYDRA_PID_T)));

          if (tsId < MXL_HYDRA_TS_ID_4)
          {
            // update register address for slice 0
            for (j = 0; j < devHandlePtr->maxRegPidEntries; j++)
            {
              // register address - (based Addr) + (demodID offset) + (pid filter item's offset)
              if (j < devHandlePtr->maxFixPidEntries)
                devHandlePtr->fixedPidFilt[tsId][j].regAddr = XPT_KNOWN_PID_BASEADDR + ((tsId % MXL_HYDRA_TS_ID_4) * 0x80) + (j * 4);

              devHandlePtr->regPidFilt[tsId][j].regAddr = XPT_PID_BASEADDR + ((tsId % MXL_HYDRA_TS_ID_4) * 0x200) + (j * 8);
            }
          }
          else
          {
            // update register address for slice 1
            for (j = 0; j < devHandlePtr->maxRegPidEntries; j++)
            {
              // register address - (based Addr) + (demodID offset) + (pid filter item's offset)
              if (j < devHandlePtr->maxFixPidEntries)
                devHandlePtr->fixedPidFilt[tsId][j].regAddr = XPT_KNOWN_PID_BASEADDR1 + ((tsId % MXL_HYDRA_TS_ID_4) * 0x80) + (j * 4);

              devHandlePtr->regPidFilt[tsId][j].regAddr = XPT_PID_BASEADDR1 + ((tsId % MXL_HYDRA_TS_ID_4) * 0x200) + (j * 8);
            }
          }
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
 * @brief MxL_HYDRA_CfgTSPadMux
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId
 * @param[in]   mpegOutParamPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API configures MPEG OUT parameters for each demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
static MXL_STATUS_E MxL_HYDRA_CfgTSPadMux(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_MPEG_MODE_E mpegMode)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T *devHandlePtr = NULL;
  UINT32 padMuxValue = 0, regData=0;
  MXL_REG_FIELD_T *mxl5xx_xpt_ts = NULL;
  UINT8 tsEnable = 0x0, tsDisable = 0x5;

  static MXL_REG_FIELD_T mxl561_568_xpt_ts[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_XPT_TS_MAX] = {
    // Data                          // Clock                       // Sync                        // Valid
    {{PAD_MUX_DIGIO_23_PINMUX_SEL},  {PAD_MUX_DIGIO_24_PINMUX_SEL}, {PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_26_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_22_PINMUX_SEL},  {PAD_MUX_DIGIO_21_PINMUX_SEL}, {PAD_MUX_DIGIO_20_PINMUX_SEL}, {PAD_MUX_DIGIO_19_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_14_PINMUX_SEL},  {PAD_MUX_DIGIO_16_PINMUX_SEL}, {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_18_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_13_PINMUX_SEL},  {PAD_MUX_DIGIO_12_PINMUX_SEL}, {PAD_MUX_DIGIO_11_PINMUX_SEL}, {PAD_MUX_DIGIO_10_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_06_PINMUX_SEL},  {PAD_MUX_DIGIO_07_PINMUX_SEL}, {PAD_MUX_DIGIO_08_PINMUX_SEL}, {PAD_MUX_DIGIO_09_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_05_PINMUX_SEL},  {PAD_MUX_DIGIO_04_PINMUX_SEL}, {PAD_MUX_DIGIO_03_PINMUX_SEL}, {PAD_MUX_DIGIO_02_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_15_PINMUX_SEL},  {PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL}},
    {{PAD_MUX_DIGIO_15_PINMUX_SEL},  {PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL}},

  };

  static MXL_REG_FIELD_T mxl541_581_xpt_ts[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_XPT_TS_MAX] = {
    // Data                         // Clock                       // Sync                        // Valid
    {{PAD_MUX_DIGIO_32_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_33_PINMUX_SEL}, {PAD_MUX_DIGIO_34_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_29_PINMUX_SEL}, {PAD_MUX_DIGIO_30_PINMUX_SEL}, {PAD_MUX_DIGIO_28_PINMUX_SEL}, {PAD_MUX_DIGIO_27_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_24_PINMUX_SEL}, {PAD_MUX_DIGIO_23_PINMUX_SEL}, {PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_26_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_21_PINMUX_SEL}, {PAD_MUX_DIGIO_22_PINMUX_SEL}, {PAD_MUX_DIGIO_20_PINMUX_SEL}, {PAD_MUX_DIGIO_19_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_16_PINMUX_SEL}, {PAD_MUX_DIGIO_14_PINMUX_SEL}, {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_18_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_12_PINMUX_SEL}, {PAD_MUX_DIGIO_13_PINMUX_SEL}, {PAD_MUX_DIGIO_11_PINMUX_SEL}, {PAD_MUX_DIGIO_10_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_07_PINMUX_SEL}, {PAD_MUX_DIGIO_06_PINMUX_SEL}, {PAD_MUX_DIGIO_08_PINMUX_SEL}, {PAD_MUX_DIGIO_09_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_04_PINMUX_SEL}, {PAD_MUX_DIGIO_05_PINMUX_SEL}, {PAD_MUX_DIGIO_03_PINMUX_SEL}, {PAD_MUX_DIGIO_02_PINMUX_SEL}}
  };

  static MXL_REG_FIELD_T mxl582_584_xpt_ts[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_XPT_TS_MAX] = {
    // Data                         // Clock                       // Sync                        // Valid
    {{PAD_MUX_DIGIO_32_PINMUX_SEL}, {PAD_MUX_DIGIO_30_PINMUX_SEL}, {PAD_MUX_DIGIO_33_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_28_PINMUX_SEL}, {PAD_MUX_DIGIO_29_PINMUX_SEL}, {PAD_MUX_DIGIO_27_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_24_PINMUX_SEL}, {PAD_MUX_DIGIO_26_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_22_PINMUX_SEL}, {PAD_MUX_DIGIO_23_PINMUX_SEL}, {PAD_MUX_DIGIO_21_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_19_PINMUX_SEL}, {PAD_MUX_DIGIO_18_PINMUX_SEL}, {PAD_MUX_DIGIO_20_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_16_PINMUX_SEL}, {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_13_PINMUX_SEL}, {PAD_MUX_DIGIO_12_PINMUX_SEL}, {PAD_MUX_DIGIO_14_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_10_PINMUX_SEL}, {PAD_MUX_DIGIO_11_PINMUX_SEL}, {PAD_MUX_DIGIO_09_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}
};

  static MXL_REG_FIELD_T mxl544_xpt_ts[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_XPT_TS_MAX] = {
    // Data                         // Clock                       // Sync                        // Valid
    {{PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_26_PINMUX_SEL}, {PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_27_PINMUX_SEL}, {PAD_MUX_DIGIO_28_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_23_PINMUX_SEL}, {PAD_MUX_DIGIO_24_PINMUX_SEL}, {PAD_MUX_DIGIO_22_PINMUX_SEL}, {PAD_MUX_DIGIO_21_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_18_PINMUX_SEL}, {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_19_PINMUX_SEL}, {PAD_MUX_DIGIO_20_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_15_PINMUX_SEL}, {PAD_MUX_DIGIO_16_PINMUX_SEL}, {PAD_MUX_DIGIO_14_PINMUX_SEL}, {PAD_MUX_DIGIO_13_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}, 
    {{PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}}
};

  static MXL_REG_FIELD_T xpt_demod_sel[MXL_HYDRA_DEMOD_MAX] = {
                                                        {XPT_DMD0_SEL},
                                                        {XPT_DMD1_SEL},
                                                        {XPT_DMD2_SEL},
                                                        {XPT_DMD3_SEL},
                                                        {XPT_DMD4_SEL},
                                                        {XPT_DMD5_SEL},
                                                        {XPT_DMD6_SEL},
                                                        {XPT_DMD7_SEL}};


  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (mpegMode == MXL_HYDRA_MPEG_MODE_PARALLEL)
    {
      devHandlePtr->serialInterface = MXL_FALSE;
      if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581) || \
          (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581S) || \
          (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581C))
      {
        padMuxValue = 2;
      }
      else
      {
        padMuxValue = 3;
      }

      switch( devHandlePtr->deviceType)
      {
        case MXL_HYDRA_DEVICE_541:
        case MXL_HYDRA_DEVICE_561:
        case MXL_HYDRA_DEVICE_581:
        case MXL_HYDRA_DEVICE_568:
        case MXL_HYDRA_DEVICE_541S:
        case MXL_HYDRA_DEVICE_561S:
        case MXL_HYDRA_DEVICE_581S:
        case MXL_HYDRA_DEVICE_541C:
        case MXL_HYDRA_DEVICE_581C:
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_14_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_16_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_17_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_18_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_19_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_20_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_21_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_22_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_23_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_24_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_25_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_26_PINMUX_SEL, padMuxValue);
          break;

        case MXL_HYDRA_DEVICE_542:
        case MXL_HYDRA_DEVICE_542C:
        case MXL_HYDRA_DEVICE_544:
        case MXL_HYDRA_DEVICE_584:
        case MXL_HYDRA_DEVICE_582:
        case MXL_HYDRA_DEVICE_582C:
        default:
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_09_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_10_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_11_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_12_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_13_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_14_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_15_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_16_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_17_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_18_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_19_PINMUX_SEL, padMuxValue);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_20_PINMUX_SEL, padMuxValue);
          break;
      }
    }
    else  // Serial
    {
      devHandlePtr->serialInterface = MXL_TRUE;
      switch (devHandlePtr->deviceType)
      {
        default:
        case MXL_HYDRA_DEVICE_561:
        case MXL_HYDRA_DEVICE_561S:
        case MXL_HYDRA_DEVICE_568:
          mxl5xx_xpt_ts = mxl561_568_xpt_ts[demodId];
          break;

        case MXL_HYDRA_DEVICE_542:
        case MXL_HYDRA_DEVICE_544:
        case MXL_HYDRA_DEVICE_582:
        case MXL_HYDRA_DEVICE_584:
        case MXL_HYDRA_DEVICE_542C:
        case MXL_HYDRA_DEVICE_582C:
          if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (mpegMode == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
          {
            mxl5xx_xpt_ts = mxl544_xpt_ts[demodId];
          }
          else
          {
            if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542) || \
                (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544))
            {
              tsEnable = 0x2;
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_13_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_14_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_27_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_28_PINMUX_SEL, tsDisable);
            }
            else if (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C)
            {
              tsEnable = 0x0;
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_09_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_10_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_11_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_12_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_13_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_14_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_27_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_28_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_29_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_30_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_32_PINMUX_SEL, tsDisable);
              mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_33_PINMUX_SEL, tsDisable);
            }
            mxl5xx_xpt_ts = mxl582_584_xpt_ts[demodId];
          }
          break;

        case MXL_HYDRA_DEVICE_541:
        case MXL_HYDRA_DEVICE_541S:
        case MXL_HYDRA_DEVICE_541C:
        case MXL_HYDRA_DEVICE_581:
        case MXL_HYDRA_DEVICE_581S:
        case MXL_HYDRA_DEVICE_581C:
          if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541) || \
              (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541S) || \
              (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541C))
          {
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_02_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_03_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_04_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_05_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_06_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_07_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_08_PINMUX_SEL, tsDisable);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_DIGIO_09_PINMUX_SEL, tsDisable);
            tsEnable = 0x2;
          }
          mxl5xx_xpt_ts = mxl541_581_xpt_ts[demodId];
          break;
      }

      if (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544)
      {
        if (mpegMode != MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE)
        {
          // Changing the default value
          mxlStatus |= MxLWare_Hydra_ReadByMnemonic(devId,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].regAddr,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].lsbPos,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].numOfBits,
                                            &regData);

          if (regData == demodId)
          {
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].regAddr,
                                              xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].lsbPos,
                                              xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].numOfBits,
                                              0x7);
          }

          mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_demod_sel[demodId].regAddr,
                                            xpt_demod_sel[demodId].lsbPos,
                                            xpt_demod_sel[demodId].numOfBits,
                                            demodId);
        }
        else
        {
          /* For 544 SKU in 4-wire mode, Demod 2, 3, 4, 5 should be mapped to TS 0, 1, 2, 3 respectively.
             Please check JIRA Scorpius-356 */
          // Changing the default value
          mxlStatus |= MxLWare_Hydra_ReadByMnemonic(devId,
                                            xpt_demod_sel[demodId].regAddr,
                                            xpt_demod_sel[demodId].lsbPos,
                                            xpt_demod_sel[demodId].numOfBits,
                                            &regData);

          if (regData == demodId)
          {
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_demod_sel[demodId].regAddr,
                                              xpt_demod_sel[demodId].lsbPos,
                                              xpt_demod_sel[demodId].numOfBits,
                                              0x7);
          }

          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].regAddr,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].lsbPos,
                                            xpt_demod_sel[demodId-MXL_HYDRA_DEMOD_ID_2].numOfBits,
                                            demodId);
        }
      }
      // Enable Data & Clocks by default.
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_DATA].regAddr,         // Reg Addr
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_DATA].lsbPos,          // LSB pos
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_DATA].numOfBits,       // Num of bits
                                  tsEnable);              // Data

      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_CLOCK].regAddr,         // Reg Addr
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_CLOCK].lsbPos,          // LSB pos
                                  mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_CLOCK].numOfBits,       // Num of bits
                                  tsEnable);              // Clock

      if (mpegMode == MXL_HYDRA_MPEG_MODE_SERIAL_2_WIRE)
      {
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].regAddr,         // Reg Addr
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].lsbPos,          // LSB pos
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].numOfBits,       // Num of bits
                                    tsDisable);              // Sync

        if ((devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_584) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_544) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542C) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582C))
        {
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].regAddr,         // Reg Addr
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].lsbPos,          // LSB pos
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].numOfBits,       // Num of bits
                                      tsDisable);              // Valid
        }
      }
      else if (mpegMode == MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE)
      {
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].regAddr,         // Reg Addr
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].lsbPos,          // LSB pos
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].numOfBits,       // Num of bits
                                    tsEnable);              // Sync
                      
        if ((devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_584) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_544) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542C) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582C))
        {
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].regAddr,         // Reg Addr
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].lsbPos,          // LSB pos
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].numOfBits,       // Num of bits
                                      tsDisable);              // Valid
        }
      }
      else if (mpegMode == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE)
      {
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].regAddr,         // Reg Addr
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].lsbPos,          // LSB pos
                                    mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_SYNC].numOfBits,       // Num of bits
                                    tsEnable);              // Sync

        if ((devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_584) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542) && (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_542C) && \
            (devHandlePtr->deviceType != MXL_HYDRA_DEVICE_582C))
        {
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].regAddr,         // Reg Addr
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].lsbPos,          // LSB pos
                                      mxl5xx_xpt_ts[MXL_HYDRA_XPT_TS_VALID].numOfBits,       // Num of bits
                                      tsEnable);              // Valid
        }
        else
          MXL_HYDRA_PRINT("MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE not supported\n");
      }
    }
  }
  return mxlStatus;
}

MXL_STATUS_E MxLWare_HYDRA_API_CfgMpegOutParams(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_MPEGOUT_PARAM_T* mpegOutParamPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr = (MXL_HYDRA_CONTEXT_T *)0;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 i = 0;
  UINT32 ncoCountMin = 0;
  UINT32 clkType = 0;

  MXL_REG_FIELD_T xpt_sync_polarity[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_SYNC_POLARITY0},
                                                                  {XPT_SYNC_POLARITY1},
                                                                  {XPT_SYNC_POLARITY2},
                                                                  {XPT_SYNC_POLARITY3},
                                                                  {XPT_SYNC_POLARITY4},
                                                                  {XPT_SYNC_POLARITY5},
                                                                  {XPT_SYNC_POLARITY6},
                                                                  {XPT_SYNC_POLARITY7}};

  MXL_REG_FIELD_T xpt_clock_polarity[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_CLOCK_POLARITY0},
                                                                  {XPT_CLOCK_POLARITY1},
                                                                  {XPT_CLOCK_POLARITY2},
                                                                  {XPT_CLOCK_POLARITY3},
                                                                  {XPT_CLOCK_POLARITY4},
                                                                  {XPT_CLOCK_POLARITY5},
                                                                  {XPT_CLOCK_POLARITY6},
                                                                  {XPT_CLOCK_POLARITY7}};

  MXL_REG_FIELD_T xpt_valid_polarity[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_VALID_POLARITY0},
                                                                  {XPT_VALID_POLARITY1},
                                                                  {XPT_VALID_POLARITY2},
                                                                  {XPT_VALID_POLARITY3},
                                                                  {XPT_VALID_POLARITY4},
                                                                  {XPT_VALID_POLARITY5},
                                                                  {XPT_VALID_POLARITY6},
                                                                  {XPT_VALID_POLARITY7}};

  MXL_REG_FIELD_T xpt_ts_clock_phase[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_TS_CLK_PHASE0},
                                                                  {XPT_TS_CLK_PHASE1},
                                                                  {XPT_TS_CLK_PHASE2},
                                                                  {XPT_TS_CLK_PHASE3},
                                                                  {XPT_TS_CLK_PHASE4},
                                                                  {XPT_TS_CLK_PHASE5},
                                                                  {XPT_TS_CLK_PHASE6},
                                                                  {XPT_TS_CLK_PHASE7}};

  MXL_REG_FIELD_T xpt_lsb_first[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_LSB_FIRST0},
                                                                  {XPT_LSB_FIRST1},
                                                                  {XPT_LSB_FIRST2},
                                                                  {XPT_LSB_FIRST3},
                                                                  {XPT_LSB_FIRST4},
                                                                  {XPT_LSB_FIRST5},
                                                                  {XPT_LSB_FIRST6},
                                                                  {XPT_LSB_FIRST7}};

  MXL_REG_FIELD_T xpt_sync_byte[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_SYNC_FULL_BYTE0},
                                                                  {XPT_SYNC_FULL_BYTE1},
                                                                  {XPT_SYNC_FULL_BYTE2},
                                                                  {XPT_SYNC_FULL_BYTE3},
                                                                  {XPT_SYNC_FULL_BYTE4},
                                                                  {XPT_SYNC_FULL_BYTE5},
                                                                  {XPT_SYNC_FULL_BYTE6},
                                                                  {XPT_SYNC_FULL_BYTE7}};

  MXL_REG_FIELD_T xpt_enable_output[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_ENABLE_OUTPUT0},
                                                                  {XPT_ENABLE_OUTPUT1},
                                                                  {XPT_ENABLE_OUTPUT2},
                                                                  {XPT_ENABLE_OUTPUT3},
                                                                  {XPT_ENABLE_OUTPUT4},
                                                                  {XPT_ENABLE_OUTPUT5},
                                                                  {XPT_ENABLE_OUTPUT6},
                                                                  {XPT_ENABLE_OUTPUT7}};

  MXL_REG_FIELD_T xpt_enable_input[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_ENABLE_INPUT0},
                                                                  {XPT_ENABLE_INPUT1},
                                                                  {XPT_ENABLE_INPUT2},
                                                                  {XPT_ENABLE_INPUT3},
                                                                  {XPT_ENABLE_INPUT4},
                                                                  {XPT_ENABLE_INPUT5},
                                                                  {XPT_ENABLE_INPUT6},
                                                                  {XPT_ENABLE_INPUT7}};

  MXL_REG_FIELD_T xpt_err_replace_sync[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_ERROR_REPLACE_SYNC0},
                                                                  {XPT_ERROR_REPLACE_SYNC1},
                                                                  {XPT_ERROR_REPLACE_SYNC2},
                                                                  {XPT_ERROR_REPLACE_SYNC3},
                                                                  {XPT_ERROR_REPLACE_SYNC4},
                                                                  {XPT_ERROR_REPLACE_SYNC5},
                                                                  {XPT_ERROR_REPLACE_SYNC6},
                                                                  {XPT_ERROR_REPLACE_SYNC7}};

  MXL_REG_FIELD_T xpt_err_replace_valid[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_ERROR_REPLACE_VALID0},
                                                                  {XPT_ERROR_REPLACE_VALID1},
                                                                  {XPT_ERROR_REPLACE_VALID2},
                                                                  {XPT_ERROR_REPLACE_VALID3},
                                                                  {XPT_ERROR_REPLACE_VALID4},
                                                                  {XPT_ERROR_REPLACE_VALID5},
                                                                  {XPT_ERROR_REPLACE_VALID6},
                                                                  {XPT_ERROR_REPLACE_VALID7}};

  MXL_REG_FIELD_T xpt_continuous_clock[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_TS_CLK_OUT_EN0},
                                                                  {XPT_TS_CLK_OUT_EN1},
                                                                  {XPT_TS_CLK_OUT_EN2},
                                                                  {XPT_TS_CLK_OUT_EN3},
                                                                  {XPT_TS_CLK_OUT_EN4},
                                                                  {XPT_TS_CLK_OUT_EN5},
                                                                  {XPT_TS_CLK_OUT_EN6},
                                                                  {XPT_TS_CLK_OUT_EN7}};

MXL_REG_FIELD_T xpt_nco_clock_rate[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_NCO_COUNT_MIN0},
                                                                  {XPT_NCO_COUNT_MIN1},
                                                                  {XPT_NCO_COUNT_MIN2},
                                                                  {XPT_NCO_COUNT_MIN3},
                                                                  {XPT_NCO_COUNT_MIN4},
                                                                  {XPT_NCO_COUNT_MIN5},
                                                                  {XPT_NCO_COUNT_MIN6},
                                                                  {XPT_NCO_COUNT_MIN7}};


  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d\n", demodId););

  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if ((mxlStatus == MXL_SUCCESS) && (mpegOutParamPtr))
    {
      MXL_HYDRA_PRINT("after map demodId = %d\n", demodId);
      MXL_HYDRA_PRINT("Enable/Disable = %d\n", mpegOutParamPtr->enable);
      MXL_HYDRA_PRINT("MPEG Mode      = %d\n", mpegOutParamPtr->mpegMode);

      // if MPEG OUT is enabled then program all the required settings else just disable mpegout function
      if (MXL_ENABLE == mpegOutParamPtr->enable)
      {
        devHandlePtr->mpegMode[demodId] = mpegOutParamPtr->mpegMode;


        if (mpegOutParamPtr->mpegMode == MXL_HYDRA_MPEG_MODE_PARALLEL)
        {
          // demod id will be irrelevent for parallel mode configuration.
          // demod should be 0 for parallel mode configuration

          MXL_HYDRA_PRINT("Parallel = %d\n", mpegOutParamPtr->mpegMode);

          for (i = MXL_HYDRA_DEMOD_ID_0; i < MXL_HYDRA_DEMOD_MAX; i++)
          {
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                          xpt_enable_output[i].regAddr,
                                          xpt_enable_output[i].lsbPos,
                                          xpt_enable_output[i].numOfBits,
                                          0);

          }

          demodId = MXL_HYDRA_DEMOD_ID_0;

          // configure PAD mux for PARALLEL interface
          mxlStatus |= MxL_HYDRA_CfgTSPadMux(devId, demodId, mpegOutParamPtr->mpegMode);

          mpegOutParamPtr->lsbOrMsbFirst = MXL_HYDRA_MPEG_SERIAL_MSB_1ST;
          mpegOutParamPtr->mpegSyncPulseWidth = MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE;

          // remove output FIFO
          mxlStatus |= SET_REG_FIELD_DATA(devId, PRCM_PRCM_XPT_PARALLEL_FIFO_RST_N, 0);
          mxlStatus |= SET_REG_FIELD_DATA(devId, PRCM_PRCM_XPT_PARALLEL_FIFO_RST_N, 1);

          // Enable parallel mode
          mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_PARALLEL_OUTPUT, MXL_TRUE);
        }
        else // Serial
        {
          // Disable parallel interface
          mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_PARALLEL_OUTPUT, MXL_FALSE);

          // configure PAD mux for SERIAL interface
          mxlStatus |= MxL_HYDRA_CfgTSPadMux(devId, demodId, mpegOutParamPtr->mpegMode);
        }

        // check if mpeg clock is non-zero
        if ((mpegOutParamPtr->maxMpegClkRate) && (mpegOutParamPtr->maxMpegClkRate <= MXL_HYDRA_MAX_TS_CLOCK))
        {
          // config NCO for mpeg clock
          MXL_HYDRA_PRINT("maxMpegClkRate = %d\n", mpegOutParamPtr->maxMpegClkRate);
          ncoCountMin = (UINT32)(MXL_HYDRA_NCO_CLK/mpegOutParamPtr->maxMpegClkRate);

          if(devHandlePtr->chipVersion >= 2)
          {
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_nco_clock_rate[demodId].regAddr,         // Reg Addr
                                            xpt_nco_clock_rate[demodId].lsbPos,          // LSB pos
                                            xpt_nco_clock_rate[demodId].numOfBits,       // Num of bits
                                            ncoCountMin);              // Data
          }
          else
          {
            mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_NCO_COUNT_MIN, ncoCountMin);
          }
        }
        else
          mxlStatus |= MXL_INVALID_PARAMETER;

        // configure gapped or contineous clock
        MXL_HYDRA_PRINT("mpegClkType = %d\n",mpegOutParamPtr->mpegClkType);

        if (mpegOutParamPtr->mpegClkType == MXL_HYDRA_MPEG_CLK_CONTINUOUS) clkType = 1;

        if (mpegOutParamPtr->mpegMode < MXL_HYDRA_MPEG_MODE_PARALLEL)
        {
          // Continuous or fixed mpeg clock type for SERIAL mode
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_continuous_clock[demodId].regAddr,          // Reg Addr
                                              xpt_continuous_clock[demodId].lsbPos,           // LSB pos
                                              xpt_continuous_clock[demodId].numOfBits,        // Num of bits
                                              clkType);                                       // Data
        }
        else
        {
          // Continuous or fixed mpeg clock type for PARALLEL mode
          mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_TS_CLK_OUT_EN_PARALLEL, clkType);
        }
        // Config mpeg sync polarity
        MXL_HYDRA_PRINT("mpegSyncPol = %d\n",mpegOutParamPtr->mpegSyncPol);
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_sync_polarity[demodId].regAddr,         // Reg Addr
                                                  xpt_sync_polarity[demodId].lsbPos,          // LSB pos
                                                  xpt_sync_polarity[demodId].numOfBits,       // Num of bits
                                                  mpegOutParamPtr->mpegSyncPol);              // Data

        // Config mpeg valid polarity
        MXL_HYDRA_PRINT("mpegValidPol = %d\n", mpegOutParamPtr->mpegValidPol);
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_valid_polarity[demodId].regAddr,
                                                  xpt_valid_polarity[demodId].lsbPos,
                                                  xpt_valid_polarity[demodId].numOfBits,
                                                  mpegOutParamPtr->mpegValidPol);

        // Config mpeg clock polarity
        MXL_HYDRA_PRINT("mpegClkPol = %d\n", mpegOutParamPtr->mpegClkPol);
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_clock_polarity[demodId].regAddr,
                                                  xpt_clock_polarity[demodId].lsbPos,
                                                  xpt_clock_polarity[demodId].numOfBits,
                                                  mpegOutParamPtr->mpegClkPol);

        // Config mpeg sync pulse width
        MXL_HYDRA_PRINT("mpegSyncPulseWidth = %d\n",mpegOutParamPtr->mpegSyncPulseWidth);
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_sync_byte[demodId].regAddr,
                                                  xpt_sync_byte[demodId].lsbPos,
                                                  xpt_sync_byte[demodId].numOfBits,
                                                  mpegOutParamPtr->mpegSyncPulseWidth);

        // Config mpeg clock phase
        MXL_HYDRA_PRINT("mpegClkPhase = %d\n",mpegOutParamPtr->mpegClkPhase);
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_ts_clock_phase[demodId].regAddr,
                                                  xpt_ts_clock_phase[demodId].lsbPos,
                                                  xpt_ts_clock_phase[demodId].numOfBits,
                                                  mpegOutParamPtr->mpegClkPhase);

        MXL_HYDRA_PRINT ("LSB/MSB = %d", mpegOutParamPtr->lsbOrMsbFirst);

        // Config lsb/msb first
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_lsb_first[demodId].regAddr,
                                                  xpt_lsb_first[demodId].lsbPos,
                                                  xpt_lsb_first[demodId].numOfBits,
                                                  mpegOutParamPtr->lsbOrMsbFirst);

        switch(mpegOutParamPtr->mpegErrorIndication)
        {
          case MXL_HYDRA_MPEG_ERR_REPLACE_SYNC:
            // Enable Error indication instead of sync
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_sync[demodId].regAddr,
                                            xpt_err_replace_sync[demodId].lsbPos,
                                            xpt_err_replace_sync[demodId].numOfBits,
                                            MXL_TRUE);

            // Disable Error indication instead of valid
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_valid[demodId].regAddr,
                                            xpt_err_replace_valid[demodId].lsbPos,
                                            xpt_err_replace_valid[demodId].numOfBits,
                                            MXL_FALSE);
            break;

          case MXL_HYDRA_MPEG_ERR_REPLACE_VALID:

            // Disable Error indication instead of sync
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_sync[demodId].regAddr,
                                            xpt_err_replace_sync[demodId].lsbPos,
                                            xpt_err_replace_sync[demodId].numOfBits,
                                            MXL_FALSE);

            // Enable Error indication instead of valid
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_valid[demodId].regAddr,
                                            xpt_err_replace_valid[demodId].lsbPos,
                                            xpt_err_replace_valid[demodId].numOfBits,
                                            MXL_TRUE);
            break;

          case MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED:
          default:
            // Disable Error indication instead of sync
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_sync[demodId].regAddr,
                                            xpt_err_replace_sync[demodId].lsbPos,
                                            xpt_err_replace_sync[demodId].numOfBits,
                                            MXL_FALSE);

            // Disable Error indication instead of valid
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xpt_err_replace_valid[demodId].regAddr,
                                            xpt_err_replace_valid[demodId].lsbPos,
                                            xpt_err_replace_valid[demodId].numOfBits,
                                            MXL_FALSE);

            break;
        }
      }
      if (mpegOutParamPtr->mpegMode != MXL_HYDRA_MPEG_MODE_PARALLEL)
      {
        MXL_HYDRA_PRINT ("Serial mode Enable/Disable TS out = %d", mpegOutParamPtr->enable);

        /* For 544 SKU in 4-wire mode, Demod 2, 3, 4, 5 should be mapped to TS 0, 1, 2, 3 respectively.
            Please check JIRA Scorpius-356 */
        if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (mpegOutParamPtr->mpegMode == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
        {
          // Enable or Disable TS in
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xpt_enable_input[demodId-MXL_HYDRA_DEMOD_ID_2].regAddr,
                                                xpt_enable_input[demodId-MXL_HYDRA_DEMOD_ID_2].lsbPos,
                                                xpt_enable_input[demodId-MXL_HYDRA_DEMOD_ID_2].numOfBits,
                                                0x1);

          // Enable or Disable TS out
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xpt_enable_output[demodId-MXL_HYDRA_DEMOD_ID_2].regAddr,
                                                xpt_enable_output[demodId-MXL_HYDRA_DEMOD_ID_2].lsbPos,
                                                xpt_enable_output[demodId-MXL_HYDRA_DEMOD_ID_2].numOfBits,
                                                mpegOutParamPtr->enable);
        }
        else
        {
          // Enable or Disable TS in
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xpt_enable_input[demodId].regAddr,
                                                xpt_enable_input[demodId].lsbPos,
                                                xpt_enable_input[demodId].numOfBits,
                                                0x1);

          // Enable or Disable TS out
          mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xpt_enable_output[demodId].regAddr,
                                                xpt_enable_output[demodId].lsbPos,
                                                xpt_enable_output[demodId].numOfBits,
                                                mpegOutParamPtr->enable);
        }
      }
      if ((MXL_HYDRA_MPEG_MODE_PARALLEL == mpegOutParamPtr->mpegMode) && (MXL_DISABLE == mpegOutParamPtr->enable))
      {
         //Disable Parallel TS output case
         MXLDBG1(MXL_HYDRA_PRINT ("Parallel mode Disable TS out = %d\n", mpegOutParamPtr->enable));
         //Disable parallel interface
         mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_PARALLEL_OUTPUT, 0);
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }
  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

// function to search if pid is already part PID filter
static SINT16 MxL_HYDRA_SearchPidFilter(MXL_HYDRA_CONTEXT_T * devHandlePtr, MXL_HYDRA_TS_ID_E sharedDemodId, MXL_HYDRA_DEMOD_ID_E orgDemoId, UINT16 pid)
{
  SINT16 pidFilterIndex = -1;
  UINT16 i = 0;
  MXL_HYDRA_PID_T *pidFilterPtr;

  // tmp pointer for PID table entry
  pidFilterPtr = &devHandlePtr->regPidFilt[sharedDemodId][0];

  // serach in the regular pid table
  while ((i < devHandlePtr->maxRegPidEntries) && (pidFilterIndex < 0))
  {
    if (pidFilterPtr[i].pidNum)
      MXL_HYDRA_PRINT("(%d) PID = %d demodId %d", i, pidFilterPtr[i].pidNum, orgDemoId);

    if (pidFilterPtr[i].pidNum == pid)
    {
      // check if the demod is also same
      if (pidFilterPtr[i].demodID == orgDemoId)
      {
        // if PID entry is found then update index & found flag
        pidFilterIndex = (SINT16)i;
        continue;
      }
    }

    i++;
  }

  // return index of PID entry in the table pointed by *updateDemodIdPtr
  // if not founf then -1 will be returned
  return pidFilterIndex;
}

// function to search for unused pid location in pif filter table
static SINT16 MxL_HYDRA_GetUnusedLocationIndex(MXL_HYDRA_CONTEXT_T * devHandlePtr, MXL_HYDRA_DEMOD_ID_E demodId)
{
  SINT16 unusedLoc = -1;
  UINT16 i = 0;
  MXL_HYDRA_PID_T *pidFilterPtr = &devHandlePtr->regPidFilt[demodId][0];

  for (i = 0; i < devHandlePtr->maxRegPidEntries; i++)
  {
    // check for inUse flag, if MXL_FALSE pid entry is free
    if (pidFilterPtr[i].inUse == MXL_FALSE)
    {
      unusedLoc = (SINT16)i;
      break;
    }

  }

  return unusedLoc;
}

// function to update internal pid filter table
static MXL_STATUS_E MxL_HYDRA_UpdateInternalPidFilter(MXL_HYDRA_CONTEXT_T * devHandlePtr,
                                                      MXL_HYDRA_DEMOD_ID_E demodId,
                                                      MXL_HYDRA_TS_ID_E tsId,
                                                      MXL_HYDRA_TS_PID_T *pidsPtr, UINT8 numPids)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 i = 0;
  UINT32 pidMask = 0xFFF8;
  SINT16 regTableIndex = 0;
  UINT8 sharedDemodId = 0;
  MXL_HYDRA_DEMOD_ID_E startId = MXL_HYDRA_DEMOD_ID_0;
  MXL_HYDRA_DEMOD_ID_E endId = MXL_HYDRA_DEMOD_ID_0;
  UINT32 tmpId = 0;
  MXL_HYDRA_TS_MUX_TYPE_E muxType = MXL_HYDRA_TS_MUX_DISABLE;
  MXL_HYDRA_TS_PID_T *tmpPidPtr = (MXL_HYDRA_TS_PID_T *)0;

  // validate input pointers
  if ((devHandlePtr) && (pidsPtr))
  {
    MXL_HYDRA_PRINT(" PID = %d", pidsPtr->originalPid);
    MXL_HYDRA_PRINT(" Demod ID = %d", demodId);

    // iterate throught all the input pid filter entries
    for (i = 0; i < numPids; i++)
    {
      // Search if pidNum is already present in the table
      // from application
      tmpPidPtr = &pidsPtr[i];

      // Check if pid number is fixed or regular
      // input pid
      if ((tmpPidPtr->originalPid < devHandlePtr->maxFixPidEntries) && (devHandlePtr->dss2dvbEnacapMode[demodId] == MXL_FALSE))
      {
        // update known pid filter table - each demod will have a dedicated pid filter table
        // for known pid numbers.

        // Known pid entries will have a dedicated location in the PID filter table.
        // We can use the pid number as index to get the pid filter record from the table.

        // just 1 32-bit register per pid entry has to be programmed.
        devHandlePtr->fixedPidFilt[demodId][tmpPidPtr->originalPid].numOfBytes = 4;

        // update dirty flag, dirty flag will indicate if the pid entry has been updated or not.
        // if dirtyflag is MXL_FALSE, then the pid entry will not be updated in the device
        devHandlePtr->fixedPidFilt[demodId][tmpPidPtr->originalPid].dirtyFlag = MXL_TRUE;

        // assign actual pid number
        devHandlePtr->fixedPidFilt[demodId][tmpPidPtr->originalPid].pidNum = tmpPidPtr->originalPid;

        // assign actual pid number
        devHandlePtr->fixedPidFilt[demodId][tmpPidPtr->originalPid].demodID = demodId;

        // build 32-bit register data which can be used to write the register.
        // update .ocal copy of the pid filter table
        devHandlePtr->fixedPidFilt[demodId][tmpPidPtr->originalPid].data[0] = FIXED_PID_DATA(tmpPidPtr->enable, ((tmpPidPtr->allowOrDrop == MXL_TRUE) ? 0 : 1), tmpPidPtr->enablePidRemap, tmpPidPtr->remappedPid);

      }
      else
      {
        // get the TS mux mode for each demod
        if (tsId <= MXL_HYDRA_TS_ID_3) muxType = devHandlePtr->tsMuxModeSlice0;
        else muxType = devHandlePtr->tsMuxModeSlice1;

        // based on mux mode update start and end id's of pid fileters to search for given pid
        switch(muxType)
        {
          // no mux - start & end will be same
          default:
          case MXL_HYDRA_TS_MUX_DISABLE:
            startId = tsId;
            endId = tsId;

            MXL_HYDRA_PRINT("\n%s: startId = %d. endId = %d\n", __FUNCTION__, startId, endId);

            break;

          // for 2 to 1 Mux
          case MXL_HYDRA_TS_MUX_2_TO_1:
            if ((tsId == MXL_HYDRA_TS_ID_0) || (tsId == MXL_HYDRA_TS_ID_1))
            {
              startId = MXL_HYDRA_TS_ID_0;
              endId = MXL_HYDRA_TS_ID_1;
            }
            else if ((tsId == MXL_HYDRA_TS_ID_2) || (tsId == MXL_HYDRA_TS_ID_3))
            {
              startId = MXL_HYDRA_TS_ID_2;
              endId = MXL_HYDRA_TS_ID_3;
            }
            else if ((tsId == MXL_HYDRA_TS_ID_4) || (tsId == MXL_HYDRA_TS_ID_5))
            {
              startId = MXL_HYDRA_TS_ID_4;
              endId = MXL_HYDRA_TS_ID_5;
            }
            else
            {
              startId = MXL_HYDRA_TS_ID_6;
              endId = MXL_HYDRA_TS_ID_7;
            }
            break;

          // for 4 to 1 Mux
          case MXL_HYDRA_TS_MUX_4_TO_1:
            if (tsId < MXL_HYDRA_TS_ID_4)
            {
              startId = MXL_HYDRA_TS_ID_0;
              endId = MXL_HYDRA_TS_ID_3;
            }
            else
            {
              startId = MXL_HYDRA_TS_ID_4;
              endId = MXL_HYDRA_TS_ID_7;
            }
            break;
        }

        // search for pid entry in table
        tmpId = startId;
        regTableIndex = -1;
        sharedDemodId = tmpId;

        MXL_HYDRA_PRINT("%s: startId = %d. endId = %d\n", __FUNCTION__, startId, endId);

        while((tmpId <= (UINT32)endId) && (regTableIndex == -1))
        {
          regTableIndex = MxL_HYDRA_SearchPidFilter(devHandlePtr, (MXL_HYDRA_TS_ID_E)tmpId, demodId, tmpPidPtr->originalPid);
          if (regTableIndex < 0)
          {
            sharedDemodId = tmpId;
            tmpId++;
          }
        }

        MXL_HYDRA_PRINT("%s: regTableIndex %d\n", __FUNCTION__, regTableIndex);

        // if pid entry cant be found then find an unused location for the pid
        if ( regTableIndex < 0)
        {
          // find unused location in table
          tmpId = startId;
          regTableIndex = -1;
          sharedDemodId = tmpId;

          while((tmpId <= (UINT32)endId) && (regTableIndex == -1))
          {
            regTableIndex = MxL_HYDRA_GetUnusedLocationIndex(devHandlePtr, (MXL_HYDRA_DEMOD_ID_E)tmpId);
            if (regTableIndex < 0)
            {
              sharedDemodId = tmpId;
              tmpId++;
            }
          }

        }

        if ((regTableIndex >= 0) && (regTableIndex < devHandlePtr->maxRegPidEntries))
        {
          MXL_HYDRA_PRINT("%s: tmpId %d regTableIndex %d\n", __FUNCTION__, sharedDemodId, regTableIndex);

          // update pid filter table
          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].numOfBytes = 8;
          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].dirtyFlag = MXL_TRUE;
          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].inUse = tmpPidPtr->enable;
          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].pidNum = tmpPidPtr->originalPid;
          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].demodID = demodId;

          if (devHandlePtr->dss2dvbEnacapMode[demodId] == MXL_TRUE)
            pidMask = 0x0FFF;
          else
            pidMask = 0x1FFF;

          MXL_HYDRA_PRINT("Enable = %d",tmpPidPtr->enable);
          MXL_HYDRA_PRINT("allowOrDrop = %d",tmpPidPtr->allowOrDrop);
          MXL_HYDRA_PRINT("enablePidRemap = %d",tmpPidPtr->enablePidRemap);
          MXL_HYDRA_PRINT("originalPid = %d",tmpPidPtr->originalPid);
          MXL_HYDRA_PRINT("remappedPid = %d",tmpPidPtr->remappedPid);
          MXL_HYDRA_PRINT("tsId = %d",tsId);

          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].data[0] = REGULAR_PID_DATA_0(tmpPidPtr->enable, ((tmpPidPtr->allowOrDrop == MXL_TRUE) ? 0 : 1), tmpPidPtr->enablePidRemap, tmpPidPtr->originalPid, pidMask);

          devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].data[1] = REGULAR_PID_DATA_1(tmpPidPtr->remappedPid, tsId);

          MXL_HYDRA_PRINT("sharedDemodId = %d, regTableIndex = %d dirtyFlag = %d inUse = %d\n", sharedDemodId, regTableIndex, devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].dirtyFlag, devHandlePtr->regPidFilt[sharedDemodId][regTableIndex].inUse);
        }
        else
        {
          MXL_HYDRA_PRINT("MXL_INVALID_PARAMETER: regTableIndex: %d, max regpidentries: %d\n", regTableIndex, devHandlePtr->maxRegPidEntries);
          mxlStatus |= MXL_INVALID_PARAMETER;
        }
      }
    }
  }
  else
  {
    MXL_HYDRA_PRINT("%s: Invalid Parameters!\n", __FUNCTION__);
    mxlStatus |= MXL_INVALID_PARAMETER;
  }

  return mxlStatus;
}

// function to update pid filter table in the device
static MXL_STATUS_E MxL_HYDRA_CfgUpdatePidFilterTable(UINT8 devId, MXL_HYDRA_CONTEXT_T *devHandlePtr, MXL_HYDRA_TS_ID_E tsId, MXL_BOOL_E updateDirtyFlag)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 i = 0;
  UINT8 sharedFiltId = 0;
  MXL_HYDRA_DEMOD_ID_E mappedSharedFiltId;
  MXL_HYDRA_TS_ID_E listTsId[MXL_HYDRA_TS_MAX] = {0, };

  MXLENTERAPI(MXL_HYDRA_PRINT("tsId = %d\n", tsId););

  // update fixed pid filter table
  for (i = 0; i < devHandlePtr->maxFixPidEntries; i++)
  {
    if (devHandlePtr->fixedPidFilt[tsId][i].dirtyFlag == MXL_TRUE)
    {
      MXL_HYDRA_PRINT("tsId = %d, i = %d\n", tsId, i);

      mxlStatus |= MxLWare_HYDRA_WriteRegister(devId,
                                               devHandlePtr->fixedPidFilt[tsId][i].regAddr,
                                               devHandlePtr->fixedPidFilt[tsId][i].data[0]);

      // update dirty flag
      if (updateDirtyFlag == MXL_TRUE)
        devHandlePtr->fixedPidFilt[tsId][i].dirtyFlag = MXL_FALSE;
    }

  }
  for (sharedFiltId = 0; ((sharedFiltId < devHandlePtr->features.demodsCnt) && (mxlStatus == MXL_SUCCESS)); sharedFiltId++)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, (MXL_HYDRA_DEMOD_ID_E)sharedFiltId, &mappedSharedFiltId);
	mxlStatus |= MxL_Ctrl_GetPhyTsID(devId, mappedSharedFiltId, listTsId);
    if(mxlStatus == MXL_SUCCESS)
    {
      // update regular pid filter table
      for (i = 0; i < devHandlePtr->maxRegPidEntries; i++)
      {
        if (devHandlePtr->regPidFilt[listTsId[1]][i].dirtyFlag == MXL_TRUE)
        {
          MXL_HYDRA_PRINT("tsId = %d, sharedFiltId  = %d, TS ID = %d, i = %d\n", tsId, sharedFiltId, listTsId[1], i);

          MXL_HYDRA_PRINT("regAddr = 0x%X, Size  = %d Data 0 = 0x%08X, Data 1 = 0x%08X\n",
                    devHandlePtr->regPidFilt[listTsId[1]][i].regAddr,
                    devHandlePtr->regPidFilt[listTsId[1]][i].numOfBytes,
                    devHandlePtr->regPidFilt[listTsId[1]][i].data[0],
                    devHandlePtr->regPidFilt[listTsId[1]][i].data[1]);

          mxlStatus |= MxLWare_HYDRA_WriteRegisterBlock(devId,
                                                      devHandlePtr->regPidFilt[listTsId[1]][i].regAddr,
                                                      devHandlePtr->regPidFilt[listTsId[1]][i].numOfBytes,
                                                      (UINT8 *)&devHandlePtr->regPidFilt[listTsId[1]][i].data[0]);

          // update dirty flag
          if (updateDirtyFlag == MXL_TRUE)
            devHandlePtr->regPidFilt[listTsId[1]][i].dirtyFlag = MXL_FALSE;
        }
      }
    }
    else
      mxlStatus |= MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgPidFilterTbl
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId         Demod ID
 * @param[in]   pidsPtr         TS PID structure pointer
 * @param[in]   numPids         Number of PIDS to configure
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API adds PIDs to the filter table of the specified demod
 * that needs to be delivered to backend host.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgPidFilterTbl(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId,
                                               MXL_HYDRA_TS_PID_T *pidsPtr,
                                               UINT8 numPids)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_TS_MUX_TYPE_E muxType;

  MXL_HYDRA_PID_FILTER_TBL_T pidFilterTblCmd;
  UINT16 cmdSize = sizeof(MXL_HYDRA_PID_FILTER_TBL_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  UINT8 i = 0, j = 0, iter = 0;
  UINT32 dbgPidSliceMap0 = 0;
  UINT32 dbgPidSliceMap1 = 0;
  UINT32 pidCount = 0;
  MXL_BOOL_E cbMode = MXL_FALSE;
  MXL_HYDRA_TS_ID_E tsId = 0;
  MXL_HYDRA_TS_ID_E listTsId[MXL_HYDRA_TS_MAX] = {0, };

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d, numPids = %d \n", demodId, numPids););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if ((pidsPtr) && (numPids) && ((MXL_FALSE == devHandlePtr->features.chanBond) || (pidsPtr[0].bondId < MXL_HYDRA_CB_GROUP_MAX)))
    {
      if(MXL_TRUE == devHandlePtr->features.chanBond)
      {
        /* if chan bond is not active then normal pid filter table should be configured */
        if (devHandlePtr->cbBondedGroup[pidsPtr[0].bondId].cbGroupInUse == MXL_FALSE)
          cbMode = MXL_FALSE;
        else
        {
          /* if chan bond is active and pid filter then program chan bond pid filter only if
             demod id belogs to chan bond group */
          for (i = 0; i < devHandlePtr->cbBondedGroup[pidsPtr[0].bondId].numOfDemodsInCB; i++)
          {
            if (devHandlePtr->cbBondedGroup[pidsPtr[0].bondId].cbDemodId[i] == demodId)
            {
              cbMode = MXL_TRUE;
              break;
            }
          }
        }
      }

      if (cbMode == MXL_FALSE)
      {
        mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
        mxlStatus = MxL_Ctrl_GetPhyTsID(devId, demodId, listTsId);
        if (mxlStatus == MXL_SUCCESS)
        {
          for (iter = 0; iter < listTsId[0]; iter++)
          {
            tsId = listTsId[iter+1];
            MXL_HYDRA_PRINT("after map demodId = %d, numPids = %d TS ID: %d \n", demodId, numPids, tsId);

          // Update internal pid filter
          mxlStatus |= MxL_HYDRA_UpdateInternalPidFilter(devHandlePtr, demodId, tsId, pidsPtr, numPids);

          if (mxlStatus == MXL_SUCCESS)
          {
            if (tsId <= MXL_HYDRA_TS_ID_3) 
            {
              muxType = devHandlePtr->tsMuxModeSlice0;
              if (devHandlePtr->maxRegPidEntries == MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT)
                mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_PIDFILT_MUXMODE0, 0x1);
            }
            else 
            {
              muxType = devHandlePtr->tsMuxModeSlice1;
              if (devHandlePtr->maxRegPidEntries == MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT)
                mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_PIDFILT_MUXMODE1, 0x1);
            }

            // Update pid filter bank context
            mxlStatus |= MxL_HYDRA_CfgChangePidFilterBankContext(devId, tsId, muxType);

            // update pid filter table onto device without updating dirty flag
            mxlStatus |= MxL_HYDRA_CfgUpdatePidFilterTable(devId, devHandlePtr, tsId, MXL_FALSE);

            // flip active bank (inactive to active)
            mxlStatus |= MxL_HYDRA_CfgChangePidFilterBankContext(devId, tsId, muxType);

            // update pid filter table onto device - inactive bank context and update dirty flag
            mxlStatus |= MxL_HYDRA_CfgUpdatePidFilterTable(devId, devHandlePtr, tsId, MXL_TRUE);
          }
        } // for (iter = 0;
        }
      }
      
#ifdef _MXL_HYDRA_CHAN_BOND_
      MXL_HYDRA_PRINT(" %s: devHandlePtr->features.chanBond : %d \n", __FUNCTION__, devHandlePtr->features.chanBond);

      //if (devHandlePtr->features.chanBond == MXL_TRUE)
      if (cbMode == MXL_TRUE)
      {
        mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);

        MXL_HYDRA_PRINT(" %s: ChanBond PID filter ++ : \n", __FUNCTION__);

        MXLWARE_OSAL_MEMSET(&pidFilterTblCmd, 0, sizeof(MXL_HYDRA_PID_FILTER_TBL_T));
        do
        {
          pidFilterTblCmd.numPids = ((numPids > MXL_HYDRA_CB_PID_NUM_MAX) ? MXL_HYDRA_CB_PID_NUM_MAX : numPids);
          pidFilterTblCmd.demodMap = 0;
          pidCount = pidFilterTblCmd.numPids;

          // PID filter config for A0 only
          /* A0 Code only  */
          for (j = 0; j < devHandlePtr->cbBondedGroup[0].numOfDemodsInCB; j++)
          {
            if ( devHandlePtr->cbBondedGroup[0].cbDemodId[j] <= MXL_HYDRA_DEMOD_ID_3)
              dbgPidSliceMap0++;
            else
              dbgPidSliceMap1++;
          }

          if ((devHandlePtr->cbBondedGroup[0].numOfDemodsInCB == dbgPidSliceMap0) && (dbgPidSliceMap1 == 0))
          {
            pidFilterTblCmd.demodMap = 0xFFFF;
          }
          else if ((devHandlePtr->cbBondedGroup[0].numOfDemodsInCB == dbgPidSliceMap1) && (dbgPidSliceMap0 == 0))
          {
            pidFilterTblCmd.demodMap = 0xFFFF0000;
          }

          MXL_HYDRA_PRINT("\n %s: after map demodId = %d, numPids = %d \n", __FUNCTION__, demodId, pidFilterTblCmd.numPids);

          /* End of A0 code only */
          for(i = 0; i < pidFilterTblCmd.numPids; i++)
          {
            pidFilterTblCmd.pidValue[i] = 0;
            pidFilterTblCmd.pidValue[i] |= (1 << (24+pidsPtr[i].destId));
            pidFilterTblCmd.pidValue[i] |= (pidsPtr[i].originalPid & 0x1FFF);
            pidFilterTblCmd.pidValue[i] |= ((pidsPtr[i].bondId & 0x3) << 16);

            MXL_HYDRA_PRINT(" pid id = 0x%X \n", pidsPtr[i].originalPid);
            MXL_HYDRA_PRINT(" DestTag id = 0x%X \n", pidsPtr[i].destId);
            MXL_HYDRA_PRINT(" chan bond pid = 0x%X \n", pidFilterTblCmd.pidValue[i]);
          }

          // send command to the device
          BUILD_HYDRA_CMD(MXL_XCPU_PID_FLT_CFG_CMD, MXL_CMD_WRITE, cmdSize, &pidFilterTblCmd, cmdBuff);
          mxlStatus |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
          numPids -= pidCount;
        } while (numPids > 0);
      }
#endif
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
 * @brief MxLWare_HYDRA_API_ReqPidFilterTbl
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId         Demod ID
 * @param[out]  pidsValPtr      Pointer to hold PID values
 * @param[out]  numPidsPtr      Pointer to hold number of PIDs
 *
 * @author Sateesh
 *
 * @date 08/12/2014 Initial release
 *
 * This API reads PIDs from the filter table of the specified demod
 * that needs to be delivered to backend host.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqPidFilterTbl(UINT8 devId,
                                               MXL_HYDRA_DEMOD_ID_E demodId,
                                               MXL_HYDRA_TS_PID_T *pidsInfoPtr,
                                               UINT8 *numPidsPtr)
{
  MXL_HYDRA_CONTEXT_T *devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 loopCount = 0, pidCount = 0;
  UINT8 tsIndex, tsCount;
  UINT32 regReadData[2*MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT];
  MXL_HYDRA_DEMOD_ID_E physicalDemodId;
  MXL_HYDRA_TS_ID_E tsId = MXL_HYDRA_TS_MAX;
  MXL_HYDRA_TS_ID_E listTsId[MXL_HYDRA_TS_MAX] = {0, };

  UINT8 maxNumPids = 4 * MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT;  // 160 maximum

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if((MXL_SUCCESS == mxlStatus) && (pidsInfoPtr) && (numPidsPtr))
  {
    if((*numPidsPtr <= maxNumPids) && (*numPidsPtr > 0))
    {
      maxNumPids = *numPidsPtr;  // set maxNumPids according to passed-in value if reasonable
    }
    else
    {
      mxlStatus = MXL_INVALID_PARAMETER;
    }
  }

  if(MXL_SUCCESS == mxlStatus)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &physicalDemodId);

    mxlStatus |= MxL_Ctrl_GetPhyTsID(devId, physicalDemodId, listTsId);

    if(MXL_SUCCESS == mxlStatus)
    {
      tsId = listTsId[1];
      tsCount = MXL_HYDRA_TS_OUT_MAX;  // go through all eight TS regardless of SKU

      for(tsIndex = 0; (tsIndex < tsCount) && (pidCount < maxNumPids); tsIndex++)
      {
        // Clear regReadData before filling it
        MXLWARE_OSAL_MEMSET(regReadData, 0, sizeof(regReadData));

        // Shared/Regular PID Retrieval
        mxlStatus = MxLWare_HYDRA_ReadRegisterBlock(devId, devHandlePtr->regPidFilt[tsIndex][0].regAddr, 
                              (2*sizeof(UINT32)*devHandlePtr->maxRegPidEntries), (UINT8 *)regReadData);

        for (loopCount = 0; (loopCount < devHandlePtr->maxRegPidEntries*2) && (pidCount < maxNumPids); loopCount+=2)
        {
          if ((mxlStatus == MXL_SUCCESS) && ((regReadData[loopCount] & 0x1) == 0x1) && (tsId == ((regReadData[loopCount+1]>>16)&0x07)))
          {
            pidsInfoPtr[pidCount].originalPid = (regReadData[loopCount] >> 4) & 0x1FFF;
            pidsInfoPtr[pidCount].remappedPid = (regReadData[loopCount+1]) & 0x1FFF;
            pidsInfoPtr[pidCount].destId = ((regReadData[loopCount+1]) >> 16) & 0x7;
            pidsInfoPtr[pidCount].enable = MXL_TRUE;
            pidsInfoPtr[pidCount].allowOrDrop = (MXL_BOOL_E)((regReadData[loopCount] >> 1) & 0x1);
            pidsInfoPtr[pidCount].enablePidRemap = (MXL_BOOL_E)((regReadData[loopCount] >> 2) & 0x1);
            pidCount++;
          }
        }
      }

      *numPidsPtr = pidCount;
      MXL_HYDRA_DEBUG("Total number of pids: %d\n", pidCount);
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
 * @brief MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId
 * @param[in]   prefixHeaderPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API will be used to prefix extra bytes to TS packet to
 * distinguish the same TS packets from each demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_MUX_PREFIX_HEADER_T * prefixHeaderPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 data = 0, i = 0; // default will be disable TS header
  UINT32 tsHeader0 = 0;
  UINT32 tsHeader1 = 0;
  UINT32 tsHeader2 = 0;
  MXL_HYDRA_TS_ID_E tsId = MXL_HYDRA_TS_MAX;
  MXL_HYDRA_TS_ID_E listTsId[MXL_HYDRA_TS_MAX] = {0, };

  MXL_REG_FIELD_T xpt_ts_header_0[MXL_HYDRA_DEMOD_MAX] = {
                                                            {XPT_INP0_MERGE_HDR0},
                                                            {XPT_INP1_MERGE_HDR0},
                                                            {XPT_INP2_MERGE_HDR0},
                                                            {XPT_INP3_MERGE_HDR0},
                                                            {XPT_INP4_MERGE_HDR0},
                                                            {XPT_INP5_MERGE_HDR0},
                                                            {XPT_INP6_MERGE_HDR0},
                                                            {XPT_INP7_MERGE_HDR0}};

  MXL_REG_FIELD_T xpt_ts_header_1[MXL_HYDRA_DEMOD_MAX] = {
                                                            {XPT_INP0_MERGE_HDR1},
                                                            {XPT_INP1_MERGE_HDR1},
                                                            {XPT_INP2_MERGE_HDR1},
                                                            {XPT_INP3_MERGE_HDR1},
                                                            {XPT_INP4_MERGE_HDR1},
                                                            {XPT_INP5_MERGE_HDR1},
                                                            {XPT_INP6_MERGE_HDR1},
                                                            {XPT_INP7_MERGE_HDR1}};

  MXL_REG_FIELD_T xpt_ts_header_2[MXL_HYDRA_DEMOD_MAX] = {
                                                            {XPT_INP0_MERGE_HDR2},
                                                            {XPT_INP1_MERGE_HDR2},
                                                            {XPT_INP2_MERGE_HDR2},
                                                            {XPT_INP3_MERGE_HDR2},
                                                            {XPT_INP4_MERGE_HDR2},
                                                            {XPT_INP5_MERGE_HDR2},
                                                            {XPT_INP6_MERGE_HDR2},
                                                            {XPT_INP7_MERGE_HDR2}};

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d\n", demodId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    mxlStatus |= MxL_Ctrl_GetPhyTsID(devId, demodId, listTsId);

    if ((mxlStatus == MXL_SUCCESS) && (prefixHeaderPtr))
    {
      for (i = 0; i < listTsId[0] && i < MXL_HYDRA_TS_MAX; i++)
      {
        tsId = listTsId[i+1];
        MXLDBG1(MXL_HYDRA_PRINT("Remapped TS ID from MxL_Ctrl_GetPhyTsID is = %d\n", tsId));

        // enable TS header
        if (prefixHeaderPtr->enable == MXL_TRUE)
        {
          switch(prefixHeaderPtr->numByte)
          {
            case 4:
              data = 1;

              tsHeader0 = prefixHeaderPtr->header[0];
              tsHeader0 |= (prefixHeaderPtr->header[1] << 8);
              tsHeader0 |= (prefixHeaderPtr->header[2] << 16);
              tsHeader0 |= (prefixHeaderPtr->header[3] << 24);

              break;   // 4 Bytes header

            case 8:
              data = 2;

              tsHeader0 = prefixHeaderPtr->header[0];
              tsHeader0 |= (prefixHeaderPtr->header[1] << 8);
              tsHeader0 |= (prefixHeaderPtr->header[2] << 16);
              tsHeader0 |= (prefixHeaderPtr->header[3] << 24);

              tsHeader1 = prefixHeaderPtr->header[4];
              tsHeader1 |= (prefixHeaderPtr->header[5] << 8);
              tsHeader1 |= (prefixHeaderPtr->header[6] << 16);
              tsHeader1 |= (prefixHeaderPtr->header[7] << 24);

              break;   // 8 Bytes header

            case 12:
              data = 3;

              tsHeader0 = prefixHeaderPtr->header[0];
              tsHeader0 |= (prefixHeaderPtr->header[1] << 8);
              tsHeader0 |= (prefixHeaderPtr->header[2] << 16);
              tsHeader0 |= (prefixHeaderPtr->header[3] << 24);

              tsHeader1 = prefixHeaderPtr->header[4];
              tsHeader1 |= (prefixHeaderPtr->header[5] << 8);
              tsHeader1 |= (prefixHeaderPtr->header[6] << 16);
              tsHeader1 |= (prefixHeaderPtr->header[7] << 24);

              tsHeader2 = prefixHeaderPtr->header[8];
              tsHeader2 |= (prefixHeaderPtr->header[9] << 8);
              tsHeader2 |= (prefixHeaderPtr->header[10] << 16);
              tsHeader2 |= (prefixHeaderPtr->header[11] << 24);

              break;  // 12 Bytes header

            default:
              // only 4/8/12 Bytes headers are supported.
              mxlStatus |= MXL_INVALID_PARAMETER;
              break;
          }
        }

        if (mxlStatus == MXL_SUCCESS)
        {
          if (prefixHeaderPtr->enable == MXL_TRUE)
          {
            // program TS header
            // First 4 Bytes
            mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_ts_header_0[tsId].regAddr,         // Reg Addr
                                              xpt_ts_header_0[tsId].lsbPos,          // LSB pos
                                              xpt_ts_header_0[tsId].numOfBits,       // Num of bits
                                              tsHeader0);                               // Data
            // Second 4 Bytes
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_ts_header_1[tsId].regAddr,         // Reg Addr
                                              xpt_ts_header_1[tsId].lsbPos,          // LSB pos
                                              xpt_ts_header_1[tsId].numOfBits,       // Num of bits
                                              tsHeader1);                               // Data
            // Third 4 Bytes
            mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                              xpt_ts_header_2[tsId].regAddr,         // Reg Addr
                                              xpt_ts_header_2[tsId].lsbPos,          // LSB pos
                                              xpt_ts_header_2[tsId].numOfBits,       // Num of bits
                                              tsHeader2);                               // Data
          }

          // enable or disable header insertion
          if (tsId <= MXL_HYDRA_TS_ID_3)
          {
            mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_APPEND_BYTES0, data);
          }
          else
          {
            mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_APPEND_BYTES1, data);
          }
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
 * @brief MxLWare_HYDRA_API_CfgEncapsulateDSSIntoDVB
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId
 * @param[in]   enableDssEncapsulation
 * @param[in]   dssPktPid
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API will enable or disable encapsulation of DSS TS packet of
 * 130 bytes into DVB TS packet of 188 bytes. Hydra can encapsulate DSS
 * (legacy) TS packets into a DVB TS packet. Hydra will create 6 bytes TS
 * header with the PID provided by the host.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgEncapsulateDSSIntoDVB(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_BOOL_E enableDssEncapsulation, MXL_BOOL_E enablePFBitToggling)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXL_REG_FIELD_T xpt_dss_dvb_encap[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_DSS_DVB_ENCAP_EN0},
                                                                  {XPT_DSS_DVB_ENCAP_EN1},
                                                                  {XPT_DSS_DVB_ENCAP_EN2},
                                                                  {XPT_DSS_DVB_ENCAP_EN3},
                                                                  {XPT_DSS_DVB_ENCAP_EN4},
                                                                  {XPT_DSS_DVB_ENCAP_EN5},
                                                                  {XPT_DSS_DVB_ENCAP_EN6},
                                                                  {XPT_DSS_DVB_ENCAP_EN7}};

  MXL_REG_FIELD_T xpt_enable_dss_input[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_INP_MODE_DSS0},
                                                                  {XPT_INP_MODE_DSS1},
                                                                  {XPT_INP_MODE_DSS2},
                                                                  {XPT_INP_MODE_DSS3},
                                                                  {XPT_INP_MODE_DSS4},
                                                                  {XPT_INP_MODE_DSS5},
                                                                  {XPT_INP_MODE_DSS6},
                                                                  {XPT_INP_MODE_DSS7}};

  MXL_REG_FIELD_T xpt_enable_dss_output[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_OUTPUT_MODE_DSS0},
                                                                  {XPT_OUTPUT_MODE_DSS1},
                                                                  {XPT_OUTPUT_MODE_DSS2},
                                                                  {XPT_OUTPUT_MODE_DSS3},
                                                                  {XPT_OUTPUT_MODE_DSS4},
                                                                  {XPT_OUTPUT_MODE_DSS5},
                                                                  {XPT_OUTPUT_MODE_DSS6},
                                                                  {XPT_OUTPUT_MODE_DSS7}};

  MXL_REG_FIELD_T xpt_enable_dvb_input[MXL_HYDRA_DEMOD_MAX] = {
                                                                  {XPT_ENABLE_INPUT0},
                                                                  {XPT_ENABLE_INPUT1},
                                                                  {XPT_ENABLE_INPUT2},
                                                                  {XPT_ENABLE_INPUT3},
                                                                  {XPT_ENABLE_INPUT4},
                                                                  {XPT_ENABLE_INPUT5},
                                                                  {XPT_ENABLE_INPUT6},
                                                                  {XPT_ENABLE_INPUT7}};

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d, enableDssEncapsulation=%d enablePFBitToggling=%d\n", demodId, enableDssEncapsulation, enablePFBitToggling););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if (mxlStatus == MXL_SUCCESS)
    {
      // enable of disable header insertion
      MXL_HYDRA_PRINT("Append 52 bytes of data to TS packets");
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ZERO_FILL_COUNT, 52);

      // Enable DVB input if DSS input is disabled else other way around
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_enable_dvb_input[demodId].regAddr,
                                                  xpt_enable_dvb_input[demodId].lsbPos,
                                                  xpt_enable_dvb_input[demodId].numOfBits,
                                                  (MXL_TRUE)); // invert DSS enable or disable

      // Enable or Disable DSS input
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_enable_dss_input[demodId].regAddr,
                                                  xpt_enable_dss_input[demodId].lsbPos,
                                                  xpt_enable_dss_input[demodId].numOfBits,
                                                  MXL_TRUE);

      if (enableDssEncapsulation == MXL_TRUE)
      {
        // Enable or Disable PF Bit Toggling
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                    xpt_enable_dss_output[demodId].regAddr,
                                                    xpt_enable_dss_output[demodId].lsbPos,
                                                    xpt_enable_dss_output[demodId].numOfBits,
                                                    enablePFBitToggling);
      }
      else
      {
        // Disable PF Bit Toggling if DSS-DVB encapsulation is disabled
        mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                    xpt_enable_dss_output[demodId].regAddr,
                                                    xpt_enable_dss_output[demodId].lsbPos,
                                                    xpt_enable_dss_output[demodId].numOfBits,
                                                    MXL_FALSE);
      }

      // Enable or Disable DSS-DVB encapsulation
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                  xpt_dss_dvb_encap[demodId].regAddr,
                                                  xpt_dss_dvb_encap[demodId].lsbPos,
                                                  xpt_dss_dvb_encap[demodId].numOfBits,
                                                  enableDssEncapsulation);

      // Update MxLWare driver context
      devHandlePtr->dss2dvbEnacapMode[demodId]  = enableDssEncapsulation;
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgExternalTSInput
 *
 * @param[in]   devId           Device ID
 * @param[in]   extTSIFId
 * @param[in]   enable
 *
 * @author Mahee
 *
 * @date 09/25/2012 Initial release
 *
 * This API retrieves the current header information for TS mux of the
 * specified demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgExternalTSInput(UINT8 devId, MXL_BOOL_E enable)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("Configure external TS = %d\n", enable););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // set 90000018 to 0 to select from which external pins ISDB-T are routed (0 means DIGIO 27-34)
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS0_IN_CLK_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS0_IN_DATA_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS1_IN_CLK_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS1_IN_DATA_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS2_IN_CLK_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS2_IN_DATA_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS3_IN_CLK_PINMUX_SEL, 0);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_TS3_IN_DATA_PINMUX_SEL, 0);

    if (enable == MXL_TRUE)
    {
      // XPT_SYNC_LOCK_THRESHOLD = 8
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_SYNC_LOCK_THRESHOLD, 8);

      // XPT_SYNC_MISS_THRESHOLD = 4
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_SYNC_MISS_THRESHOLD, 4);

      // XPT_DVB_MATCH_BYTE = 0x47
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_MATCH_BYTE, 0x47);

      // XPT_DVB_PACKET_SIZE0 = 188
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE0, 187);

      // XPT_DVB_PACKET_SIZE1 = 188
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE1, 187);

      // XPT_DVB_PACKET_SIZE2 = 188
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE2, 187);

      // XPT_DVB_PACKET_SIZE3 = 188
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE3, 187);
    }
    else
    {
      // XPT_SYNC_LOCK_THRESHOLD = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_SYNC_LOCK_THRESHOLD, 0);

      // XPT_SYNC_MISS_THRESHOLD = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_SYNC_MISS_THRESHOLD, 0);

      // XPT_DVB_MATCH_BYTE = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_MATCH_BYTE, 0);

      // XPT_DVB_PACKET_SIZE0 = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE0, 0);

      // XPT_DVB_PACKET_SIZE1 = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE1, 0);

      // XPT_DVB_PACKET_SIZE2 = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE2, 0);

      // XPT_DVB_PACKET_SIZE3 = 0
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_DVB_PACKET_SIZE3, 0);

      // Disable external DVB inputs
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_DVB_INPUT0, 0);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_DVB_INPUT1, 0);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_DVB_INPUT2, 0);
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_DVB_INPUT3, 0);
    }
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgMapExtTSInToTsOut
 *
 * @param[in]   devId           Device ID
 * @param[in]   extTSIFId
 * @param[in]   tsOutId
 * @param[in]   enable
 *
 * @author Mahee
 *
 * @date 09/25/2012 Initial release
 *
 * This API retrieves the current header information for TS mux of the
 * specified demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgMapExtTSInputToTSOutput(UINT8 devId,
                                                          MXL_HYDRA_EXT_TS_IN_ID_E mxlExtTSInputId,
                                                          MXL_HYDRA_TS_OUT_ID_E tsOutId,
                                                          MXL_BOOL_E enable)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXL_REG_FIELD_T xptDVBInputPortReg[MXL_HYDRA_EXT_TS_IN_MAX] = {
                                                                  {XPT_ENABLE_DVB_INPUT0},
                                                                  {XPT_ENABLE_DVB_INPUT1},
                                                                  {XPT_ENABLE_DVB_INPUT2},
                                                                  {XPT_ENABLE_DVB_INPUT3}};

  MXL_REG_FIELD_T xptOutputPortReg[MXL_HYDRA_TS_OUT_MAX] = {
                                                                  {XPT_OUTPUT_MUXSELECT0},
                                                                  {XPT_OUTPUT_MUXSELECT1},
                                                                  {XPT_OUTPUT_MUXSELECT2},
                                                                  {XPT_OUTPUT_MUXSELECT3},
                                                                  {XPT_OUTPUT_MUXSELECT4},
                                                                  {XPT_OUTPUT_MUXSELECT5}};

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("External TS ID = %d\t TS out port = %d\n", mxlExtTSInputId, tsOutId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // Enable or Disable DVB input
    mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                                xptDVBInputPortReg[mxlExtTSInputId].regAddr,
                                                xptDVBInputPortReg[mxlExtTSInputId].lsbPos,
                                                xptDVBInputPortReg[mxlExtTSInputId].numOfBits,
                                                enable);

    // enable mapping
    mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId,
                                            xptOutputPortReg[tsOutId].regAddr,
                                            xptOutputPortReg[tsOutId].lsbPos,
                                            xptOutputPortReg[tsOutId].numOfBits,
                                            (enable == MXL_TRUE) ? (mxlExtTSInputId+1) : MXL_FALSE);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgEnablePCRCorrection
 *
 * @param[in]   devId           Device ID
 * @param[in]   enablePCRCorrection
 *
 * @author Mahee
 *
 * @date 09/25/2012 Initial release
 *
 * This API retrieves the current header information for TS mux of the
 * specified demod.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgEnablePCRCorrection(UINT8 devId, MXL_BOOL_E enablePCRCorrection)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("enablePCRCorrection = %d\n", enablePCRCorrection););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // XPT_ENABLE_PCR_COUNT = 1;
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_ENABLE_PCR_COUNT, enablePCRCorrection);

    // if 27 MHz then XPT_MODE_27MHZ = 1 else 0;
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_MODE_27MHZ, devHandlePtr->xtalFreq);

    // XPT_PCR_RTS_CORRECTION_ENABLE = 1;
    mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_PCR_RTS_CORRECTION_ENABLE, enablePCRCorrection);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgTSOutDriveStrength
 *
 * @param[in]   devId           Device ID
 * @param[in]   tsDriveStrength
 *
 * @author Mahee
 *
 * @date 03/18/2013 Initial release
 *
 * This API will configure TS drive strength of Hydra SoC.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgTSOutDriveStrength(UINT8 devId, MXL_HYDRA_TS_DRIVE_STRENGTH_E tsDriveStrength)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tsDriveStrength = %d\n", tsDriveStrength););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_00, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_05, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_06, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_11, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_12, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_13, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_14, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_16, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_17, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_18, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_22, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_23, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_24, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_25, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_29, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_30, tsDriveStrength);
    mxlStatus |= SET_REG_FIELD_DATA(devId, PAD_MUX_PAD_DRV_DIGIO_31, tsDriveStrength);
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgXPTXBar
 *
 * @param[in]   devId           Device ID
 * @param[in]   demodId         Demod ID
 * @param[in]   tsOutId         TS Out
 *
 * @author Sateesh
 *
 * @date 13/02/2014 Initial release
 *
 * This API will configure Demod to TS cross bar selection.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgXPTXBar(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_ID_E tsOutId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
 
  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d tsOutId = %d\n", demodId, tsOutId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxLWare_HYDRA_CfgXPTXBar(devId, demodId, tsOutId); 
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

MXL_STATUS_E MxLWare_HYDRA_CfgXPTXBar(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_ID_E tsOutId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  MXLENTERSTR;
  MXLENTER(MXL_HYDRA_PRINT("demodId = %d, tsOutId = %d\n", demodId, tsOutId););

  if ((MXL_LOGICAL_TO_PHYSICAL_BYPASS_NOT(demodId) < MXL_HYDRA_DEMOD_MAX) && (MXL_LOGICAL_TO_PHYSICAL_BYPASS_NOT(tsOutId) < MXL_HYDRA_TS_MAX))
  {
    UINT32 xbarCfg;
    UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
    UINT8 cmdSize = sizeof(xbarCfg);
    xbarCfg = (demodId << 16 | (tsOutId & 0xFFFF));
    BUILD_HYDRA_CMD(MXL_HYDRA_XPT_CHANNEL_UPDATE_CMD, MXL_CMD_WRITE, cmdSize, &xbarCfg, cmdBuff);
    mxlStatus |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }
  else
  {
    mxlStatus = MXL_INVALID_PARAMETER;
  }
  MXLEXITSTR(mxlStatus);
  return mxlStatus;
}
