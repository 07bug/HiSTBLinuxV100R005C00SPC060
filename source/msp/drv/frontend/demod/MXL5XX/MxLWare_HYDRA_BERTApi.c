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
#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_BERTApi.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Registers.h"

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgInitBERT
 *
 * @param[in]   devId                Device ID
 * @param[in]   demodId           Demod ID
 * @param[in]   bertSeqType      BERT sequence type
 * @param[in]   bertPktLen         BERT packet length
 * @param[in]   bertPktHdrSize   BERT packet header size
 *
 * @author Mahee
 *
 * @date 10/02/2012
 *
 * This API should be used to configure internal BERT module of HYDRA SoC.,
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgInitBERT(UINT8 devId,
                                           MXL_HYDRA_DEMOD_ID_E demodId,
                                           MXL_BERT_SEQUENCE_E bertSeqType,
                                           MXL_BERT_PKT_LEN_E bertPktLen,
                                           MXL_BERT_PKT_HDR_E bertPktHdrSize,
                                           MXL_BOOL_E invertBertData,
                                           MXL_BOOL_E invertSequencePolarity,
                                           MXL_BOOL_E invertOutputPolarity)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_HYDRA_TS_OUT_ID_E tsId;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId=%d, bertSeqType=%d, bertPktLen=%d, bertPktHdrSize=%d, invertBertData=%d, invertSequencePolarity=%d, invertOutputPolarity=%d\n",
                    demodId, bertSeqType, bertPktLen, bertPktHdrSize, invertBertData, invertSequencePolarity, invertOutputPolarity););
  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if (mxlStatus == MXL_SUCCESS)
  {
    UINT32 xpt_reg_addr;
    UINT8 xpt_lsb_pos;
    UINT8 xpt_width;

    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if (mxlStatus == MXL_SUCCESS)
    {
      tsId = demodId;
      if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (devHandlePtr->mpegMode[demodId] == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
        tsId = tsId - MXL_HYDRA_TS_OUT_2;

      MXL_HYDRA_PRINT("DemodId %d TsID %d\n", demodId, tsId);

      // XPT_BERT_LOCK_THRESHOLD = 0x05
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_BERT_LOCK_THRESHOLD, 0x05);

      // XPT_BERT_LOCK_WINDOW = 0xC8
      mxlStatus |= SET_REG_FIELD_DATA(devId, XPT_BERT_LOCK_WINDOW, 0xC8);

      // Select PN23 or PN15
      // XPT_BERT_SEQUENCE_PN23_x
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_SEQUENCE_PN23_0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, (bertSeqType == MXL_BERT_SEQ_PN23)?1:0);

      // XPT_BERT_HEADER_MODEx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_HEADER_MODE0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, (UINT32) bertPktHdrSize);

      // XPT_BERT_ENABLEx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_ENABLE0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, 1);

      // XPT_LOCK_RESYNCx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_LOCK_RESYNC0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, 1);

#ifdef __HYDRA_FPGA__
	  //Jira Scorpius 297. XPT enable should not be done as past of Bert settings
      // XPT_ENABLE_INPUTx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_ENABLE_INPUT0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, 1);
#endif
      // XPT_BERT_INVERT_DATAx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_INVERT_DATA0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, (invertBertData == MXL_TRUE)?1:0);

      // XPT_BERT_INVERT_SEQUENCEx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_INVERT_SEQUENCE0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, (invertSequencePolarity == MXL_TRUE)?1:0);

      // XPT_BERT_OUTPUT_POLARITYx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_OUTPUT_POLARITY0, &xpt_reg_addr, &xpt_lsb_pos, &xpt_width);
      xpt_lsb_pos += (((UINT8) tsId) * xpt_width);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_reg_addr, xpt_lsb_pos, xpt_width, (invertOutputPolarity == MXL_TRUE)?0:1);
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
 * @brief MxLWare_HYDRA_API_ReqBERTLockStatus
 *
 * @param[in]   devId                    Device ID
 * @param[in]   demodId               Demod ID
 * @param[out]   berkLockStatusPtr  BERT module's lock status
 *
 * @author Mahee
 *
 * @date 10/02/2012
 *
 * This API should be used to retrieve internal BERT module's lock status.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqBERTLockStatus(UINT8 devId,
                                                 MXL_HYDRA_DEMOD_ID_E demodId,
                                                 MXL_BOOL_E *berkLockStatusPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  UINT32 regData = 0;
  MXL_HYDRA_TS_OUT_ID_E tsId;

  UINT32 xpt_bert_locked_addr;
  UINT8 xpt_bert_locked_lsb_pos;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d\n", demodId););
  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if ((mxlStatus == MXL_SUCCESS) && (berkLockStatusPtr))
    {
      tsId = demodId;
      if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (devHandlePtr->mpegMode[demodId] == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
        tsId = tsId - MXL_HYDRA_TS_OUT_2;

      MXL_HYDRA_PRINT("DemodId %d TsID %d\n", demodId, tsId);
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_LOCKED0, &xpt_bert_locked_addr, &xpt_bert_locked_lsb_pos, NULL);
      xpt_bert_locked_lsb_pos += (UINT8) tsId;

      mxlStatus = MxLWare_Hydra_ReadByMnemonic(devId, xpt_bert_locked_addr, xpt_bert_locked_lsb_pos, 1, &regData);

      if (mxlStatus == MXL_SUCCESS)
        *berkLockStatusPtr = (regData == 1) ? MXL_TRUE : MXL_FALSE;
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
 * @brief MxLWare_HYDRA_API_ReqBERTStats
 *
 * @param[in]   devId                    Device ID
 * @param[in]   demodId               Demod ID
 * @param[out]   totalbitCountPtr   Total bit count
 * @param[out]   totalbitErrorPtr    Total error bits detected
 * @param[out]   bitCountSaturationFlagPtr   Bit count stauration flag - total bit count
 *                                                              doesnt increment if this flag is set.
 *
 * @author Mahee
 *
 * @date 10/02/2012
 *
 * This API should be used to retrieve internal BERT module's statistics.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_ReqBERTStats(UINT8 devId,
                                            MXL_HYDRA_DEMOD_ID_E demodId,
                                            UINT64 *totalbitCountPtr,
                                            UINT64 *totalbitErrorPtr,
                                            MXL_BOOL_E *bitCountSaturationFlagPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  UINT32 regData = 0;
  UINT32 buffer[2];
  UINT64 totalbitCountAlt = 0;
  UINT32 xpt_reg_address;
  UINT8  xpt_lsb_pos;
  UINT8  xpt_bit_width;
  MXL_HYDRA_TS_OUT_ID_E tsId;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d\n", demodId););
  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if ((mxlStatus == MXL_SUCCESS) && (totalbitCountPtr) && (totalbitErrorPtr) && (bitCountSaturationFlagPtr))
    {
      tsId = demodId;
      if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (devHandlePtr->mpegMode[demodId] == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
        tsId = tsId - MXL_HYDRA_TS_OUT_2;

      MXL_HYDRA_PRINT("DemodId %d TsID %d\n", demodId, tsId);
      // XPT_BERT_BIT_COUNT_SATx
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_BERT_BIT_COUNT_SAT0, &xpt_reg_address, &xpt_lsb_pos, &xpt_bit_width);
      xpt_lsb_pos += (UINT8) tsId;
      mxlStatus = MxLWare_Hydra_ReadByMnemonic(devId, xpt_reg_address, xpt_lsb_pos, xpt_bit_width, &regData);
      *bitCountSaturationFlagPtr = (regData) ? MXL_TRUE : MXL_FALSE;

      xpt_reg_address = XPT_BERT_BIT_COUNT0_BASEADDR;
      xpt_reg_address += ((XPT_BERT_BIT_COUNT1_BASEADDR - XPT_BERT_BIT_COUNT0_BASEADDR) * (UINT32) tsId);
      mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId, xpt_reg_address, 2 * 4, (UINT8 *) buffer);
      totalbitCountAlt = ((UINT64) buffer[1] << 32) | (UINT64) buffer[0];
      *totalbitCountPtr = totalbitCountAlt;

      xpt_reg_address = XPT_BERT_ERR_COUNT0_BASEADDR;
      xpt_reg_address += ((XPT_BERT_ERR_COUNT1_BASEADDR - XPT_BERT_ERR_COUNT0_BASEADDR) * (UINT32) tsId);
      mxlStatus |= MxLWare_HYDRA_ReadRegisterBlock(devId, xpt_reg_address, 2 * 4, (UINT8 *) buffer);
      totalbitCountAlt = ((UINT64) buffer[1] << 32) | (UINT64) buffer[0];
      *totalbitErrorPtr = totalbitCountAlt;

      MXLEXITAPI(MXL_HYDRA_PRINT("bitCountSaturationFlag:%d, totalbitError:%llu, totalbitCount:%llu\n",
                                                            *bitCountSaturationFlagPtr,
                                                            (unsigned long long int)*totalbitErrorPtr,
                                                            (unsigned long long int)*totalbitCountPtr););
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
 * @brief MxLWare_HYDRA_API_CfgResetBERTStats
 *
 * @param[in]   devId                    Device ID
 * @param[in]   demodId               Demod ID
 *
 * @author Mahee
 *
 * @date 10/02/2012
 *
 * This API should be used to reset BERT statistics.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgResetBERTStats(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  UINT32 xpt_lock_resync_addr;
  UINT8 xpt_lock_resync_lsb_pos;
  MXL_HYDRA_TS_OUT_ID_E tsId;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("demodId = %d\n", demodId););
  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    mxlStatus = MxL_Ctrl_GetTsID(devHandlePtr, demodId, &demodId);
    if (mxlStatus == MXL_SUCCESS)
    {
      tsId = demodId;
      if ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) && (devHandlePtr->mpegMode[demodId] == MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE))
        tsId = tsId - MXL_HYDRA_TS_OUT_2;
      MXL_HYDRA_PRINT("DemodId %d TsID %d\n", demodId, tsId);
      MxLWare_HYDRA_ExtractFromMnemonic(XPT_LOCK_RESYNC0, &xpt_lock_resync_addr, &xpt_lock_resync_lsb_pos, NULL);
      xpt_lock_resync_lsb_pos += (UINT8) tsId;

      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_lock_resync_addr, xpt_lock_resync_lsb_pos, 1, 0);
      mxlStatus |= MxLWare_Hydra_UpdateByMnemonic(devId, xpt_lock_resync_addr, xpt_lock_resync_lsb_pos, 1, 1);

    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}