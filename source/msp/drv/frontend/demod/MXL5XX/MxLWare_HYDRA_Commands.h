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

#ifndef __MXL_HDR_CMDS_H__
#define __MXL_HDR_CMDS_H__

#include "MaxLinearDataTypes.h"
#include "MxLWare_HYDRA_DeviceApi.h"
#include "MxLWare_HYDRA_DiseqcFskApi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************
    Macros
*****************************************************************************************/
#define MXL_HYDRA_MIN_BUFF_REQUIRED    128
#define MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN ((MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH) > (MXL_HYDRA_MIN_BUFF_REQUIRED) ? (MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH):(MXL_HYDRA_MIN_BUFF_REQUIRED))
#define MXL_HYDRA_MIN_TIME_IN_SECS 0
#define MXL_HYDRA_MAX_TIME_IN_SECS 65535 /*0xFFFF*/
#define MXL_HYDRA_MIN_PID 0
#define MXL_HYDRA_MAX_PID 8190 /*Ox1FFE*/

/************************************************************************************
       Enums
 ************************************************************************************/

// Firmware-Host Command IDs
typedef enum
{
  //--Device command IDs--
  MXL_HYDRA_DEV_NO_OP_CMD = 0, //No OP

  MXL_HYDRA_DEV_SET_POWER_MODE_CMD = 1,
  MXL_HYDRA_DEV_SET_OVERWRITE_DEF_CMD = 2,

  // Host-used CMD, not used by firmware
  MXL_HYDRA_DEV_FIRMWARE_DOWNLOAD_CMD = 3,

  // Additional CONTROL types from DTV
  MXL_HYDRA_DEV_SET_BROADCAST_PID_STB_ID_CMD = 4,
  MXL_HYDRA_DEV_GET_PMM_SLEEP_CMD = 5,

  //--Tuner command IDs--
  MXL_HYDRA_TUNER_TUNE_CMD = 6,
  MXL_HYDRA_TUNER_GET_STATUS_CMD = 7,

  //--Demod command IDs--
  MXL_HYDRA_DEMOD_SET_PARAM_CMD = 8,
  MXL_HYDRA_DEMOD_GET_STATUS_CMD = 9,

  MXL_HYDRA_DEMOD_RESET_FEC_COUNTER_CMD = 10,

  MXL_HYDRA_DEMOD_SET_PKT_NUM_CMD = 11,

  MXL_HYDRA_DEMOD_SET_IQ_SOURCE_CMD = 12,
  MXL_HYDRA_DEMOD_GET_IQ_DATA_CMD = 13,

  MXL_HYDRA_DEMOD_GET_M68HC05_VER_CMD = 14,

  MXL_HYDRA_DEMOD_SET_ERROR_COUNTER_MODE_CMD = 15,

  //--- ABORT channel tune
  MXL_HYDRA_ABORT_TUNE_CMD = 16, // Abort current tune command.

  //--SWM/FSK command IDs--
  MXL_HYDRA_FSK_RESET_CMD = 17,
  MXL_HYDRA_FSK_MSG_CMD = 18,
  MXL_HYDRA_FSK_SET_OP_MODE_CMD = 19,

  //--DiSeqC command IDs--
  MXL_HYDRA_DISEQC_MSG_CMD = 20,
  MXL_HYDRA_DISEQC_COPY_MSG_TO_MAILBOX = 21,
  MXL_HYDRA_DISEQC_CFG_MSG_CMD = 22,

  //--- FFT Debug Command IDs--
  MXL_HYDRA_REQ_FFT_SPECTRUM_CMD = 23,

  // -- Demod scramblle code
  MXL_HYDRA_DEMOD_SCRAMBLE_CODE_CMD = 24,

  //---For host to know how many commands in total---
  MXL_HYDRA_LAST_HOST_CMD = 25,

  MXL_HYDRA_DEMOD_INTR_TYPE_CMD = 47,
  MXL_HYDRA_DEV_INTR_CLEAR_CMD = 48,
  MXL_HYDRA_TUNER_SPECTRUM_REQ_CMD = 53,
  MXL_HYDRA_TUNER_ACTIVATE_CMD = 55,
  MXL_HYDRA_DEV_CFG_POWER_MODE_CMD = 56,
  MXL_HYDRA_DEV_XTAL_CAP_CMD = 57,
  MXL_HYDRA_DEV_CFG_SKU_CMD = 58,
  MXL_HYDRA_TUNER_SPECTRUM_MIN_GAIN_CMD = 59,
  MXL_HYDRA_DISEQC_CONT_TONE_CFG = 60,
  MXL_HYDRA_DEV_RF_WAKE_UP_CMD = 61,
  MXL_HYDRA_DEMOD_CFG_EQ_CTRL_PARAM_CMD = 62,
  MXL_HYDRA_DEMOD_FREQ_OFFSET_SEARCH_RANGE_CMD = 63,
  MXL_HYDRA_DEV_REQ_PWR_FROM_ADCRSSI_CMD = 64,

  MXL_XCPU_PID_FLT_CFG_CMD = 65,
  MXL_XCPU_SHMEM_TEST_CMD = 66,
  MXL_XCPU_ABORT_TUNE_CMD = 67,
  MXL_XCPU_CHAN_TUNE_CMD = 68,
  MXL_XCPU_CFG_TEST_CONDITIONS_CMD = 69,

  MXL_HYDRA_DEV_BROADCAST_WAKE_UP_CMD = 70,
  MXL_HYDRA_FSK_CFG_FSK_FREQ_CMD = 71,
  MXL_HYDRA_FSK_POWER_DOWN_CMD = 72,
  MXL_XCPU_CLEAR_CB_STATS_CMD = 73,
  MXL_XCPU_CHAN_BOND_RESTART_CMD = 74,
  MXL_XCPU_XPT_FAILSAFE_CMD = 75,

  MXL_HYDRA_FSK_LOCAL_RESET_CMD = 76,
  MXL_XCPU_DBG_CHAN_TUNE_CMD = 77,
  MXL_HYDRA_XPT_CHANNEL_UPDATE_CMD = 78, 
  MXL_HYDRA_RSSI_MONITOR_CMD = 79,

  // -- New DISEQC command
  MXL_HYDRA_DISEQC_CFG_TXRX_MSG_CMD = 80,

  MXL_HYDRA_LAST_FW_CMD    

} MXL_HYDRA_HOST_CMD_ID_E;


// Demod IQ data
typedef struct
{
  UINT32 demodId;
  UINT32 sourceOfIQ;                  // ==0, it means I/Q comes from Formatter
                                      // ==1, Legacy FEC
                                      // ==2, Frequency Recovery
                                      // ==3, NBC
                                      // ==4, CTL
                                      // ==5, EQ
                                      // ==6, FPGA
} MXL_HYDRA_DEMOD_IQ_SRC_T;

typedef struct
{
  UINT32 demodId;
} MXL_HYDRA_DEMOD_ABORT_TUNE_T;

typedef struct
{
  UINT8 tunerId;
  UINT8 enable;
} MxL_HYDRA_TUNER_CMD;

typedef struct
{
  UINT32 demodIndex;
  UINT8 scrambleSequence[12];       // scramble sequence
  UINT32 scrambleCode;              // scramble gold code
} MXL_HYDRA_DEMOD_SCRAMBLE_CODE_T;

typedef struct
{
  UINT32  intrType;
  UINT32  intrDurationInNanoSecs;
  UINT32  intrMask;
} MXL_INTR_CFG_T;

typedef struct
{
   UINT8 powerMode;       // enumeration values are defined in MXL_HYDRA_PWR_MODE_E (device API.h)
} MxL_HYDRA_POWER_MODE_CMD;

typedef enum
{
  MXL_HYDRA_SKU_TYPE_MIN = 0x00,
  MXL_HYDRA_SKU_TYPE_581 = 0x00,
  MXL_HYDRA_SKU_TYPE_584 = 0x01,
  MXL_HYDRA_SKU_TYPE_585 = 0x02,
  MXL_HYDRA_SKU_TYPE_544 = 0x03,
  MXL_HYDRA_SKU_TYPE_561 = 0x04,
  MXL_HYDRA_SKU_TYPE_5xx = 0x05,
  MXL_HYDRA_SKU_TYPE_5yy = 0x06,
  MXL_HYDRA_SKU_TYPE_511 = 0x07,
  MXL_HYDRA_SKU_TYPE_561_DE = 0x08,
  MXL_HYDRA_SKU_TYPE_582 = 0x09,
  MXL_HYDRA_SKU_TYPE_541 = 0x0A,
  MXL_HYDRA_SKU_TYPE_568 = 0x0B,
  MXL_HYDRA_SKU_TYPE_542 = 0x0C,
  MXL_HYDRA_SKU_TYPE_MAX = 0x0D,
} MXL_HYDRA_SKU_TYPE_E;

typedef struct
{
  UINT32 skuType;           // MXL_HYDRA_SKU_TYPE_E
} MXL_HYDRA_SKU_COMMAND_T;

typedef struct
{
  UINT32  timeIntervalInSeconds; // in seconds
  UINT32  tunerIndex;
  SINT32  rssiThreshold;

} MXL_HYDRA_RF_WAKEUP_PARAM_T;

typedef struct
{
  UINT32  tunerCount;
  MXL_HYDRA_RF_WAKEUP_PARAM_T params;
} MXL_HYDRA_RF_WAKEUP_CFG_T;

typedef struct
{
  UINT32 diseqcId;
  UINT32 nbyte;
  UINT8  bufMsg[MXL_HYDRA_DISEQC_MAX_PKT_SIZE];
  UINT32 toneBurst;
} MXL_HYDRA_DISEQC_TX_MSG_CMD_T;

typedef struct
{
  UINT32 tunerId;         // MXL_HYDRA_TUNER_ID_E
  UINT32 enable;          // MXL_BOOL_E
  SINT32 adcRssiThreshold;
} MXL_HYDRA_RSSI_MONITOR_INFO_T;

typedef struct
{
  MXL_HYDRA_DEMOD_PARAM_T demodChanCfg;
  UINT32 interruptLockFail;  // MXL_BOOL_E
  UINT32 awakeTimeInSeconds;
  UINT32 sleepTimeInSeconds;
  UINT32 magicPid;
} MXL_HYDRA_BROADCAST_WAKEUP_CFG_T;

#ifdef __cplusplus
}
#endif

#endif //__MXL_HDR_CMDS_H__
