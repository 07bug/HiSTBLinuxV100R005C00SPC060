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

#ifndef __MXL_HDR_DISEQC_FSK_API__
#define __MXL_HDR_DISEQC_FSK_API__

#ifdef __cplusplus
extern "C" {
#endif

#define MXL_HYDRA_DISEQC_MAX_PKT_SIZE   (32)
#define MXL_HYDRA_FSK_MESG_MAX_LENGTH   (64)

#define DISEQC_RX_BLOCK_SIZE           (36) // 4 bytes to indicate nbytes. 32 bytes of data
#define DISEQC_RX_MSG_AVIAL_ADDR       0x3FFFCFF0
#define DISEQC_RX_BLOCK_ADDR           0x3FFFCFF4

#define DISEQ0_STATUS_REG              0x3FFFD018
#define DISEQ1_STATUS_REG              0x3FFFD01C
#define DISEQ2_STATUS_REG              0x3FFFD020
#define DISEQ3_STATUS_REG              0x3FFFD024

#define MXL_HYDRA_DISEQC_STATUS_IDLE                (1 << 0) // diseqc idle
#define MXL_HYDRA_DISEQC_STATUS_XMITING             (1 << 1) // TX in process
#define MXL_HYDRA_DISEQC_STATUS_TX_ERROR            (1 << 2) // TX error
#define MXL_HYDRA_DISEQC_STATUS_TX_DONE             (1 << 3) // TX done - success
#define MXL_HYDRA_DISEQC_STATUS_RX_DATA_NOT_AVAIL   (1 << 4) // No RX data
#define MXL_HYDRA_DISEQC_STATUS_RX_DATA_AVAIL       (1 << 5) // RX data available

typedef enum
{
  MXL_HYDRA_DISEQC_ID_0 = 0,
  MXL_HYDRA_DISEQC_ID_1,
  MXL_HYDRA_DISEQC_ID_2,
  MXL_HYDRA_DISEQC_ID_3
} MXL_HYDRA_DISEQC_ID_E;

typedef enum
{
  MXL_HYDRA_DISEQC_ENVELOPE_MODE = 0,
  MXL_HYDRA_DISEQC_TONE_MODE,
} MXL_HYDRA_DISEQC_OPMODE_E;

typedef enum
{
  MXL_HYDRA_DISEQC_1_X = 0,    // Config DiSEqC 1.x mode
  MXL_HYDRA_DISEQC_2_X,        // Config DiSEqC 2.x mode
  MXL_HYDRA_DISEQC_DISABLE     // Disable DiSEqC
} MXL_HYDRA_DISEQC_VER_E;

typedef enum
{
  MXL_HYDRA_DISEQC_CARRIER_FREQ_22KHZ= 0,   // DiSEqC signal frequency of 22 KHz
  MXL_HYDRA_DISEQC_CARRIER_FREQ_33KHZ,      // DiSEqC signal frequency of 33 KHz
  MXL_HYDRA_DISEQC_CARRIER_FREQ_44KHZ       // DiSEqC signal frequency of 44 KHz
} MXL_HYDRA_DISEQC_CARRIER_FREQ_E;

typedef struct
{
  UINT8 nbyte;
  UINT8 bufMsg[MXL_HYDRA_DISEQC_MAX_PKT_SIZE];
} MXL_HYDRA_DISEQC_RX_MSG_T;

typedef enum
{
  MXL_HYDRA_DISEQC_TONE_NONE = 0,
  MXL_HYDRA_DISEQC_TONE_SA,
  MXL_HYDRA_DISEQC_TONE_SB
} MXL_HYDRA_DISEQC_TONE_CTRL_E;

typedef struct
{
  UINT32 diseqcId;
  UINT32 nbyte;
  UINT8 bufMsg[MXL_HYDRA_DISEQC_MAX_PKT_SIZE];
  MXL_HYDRA_DISEQC_TONE_CTRL_E toneBurst;
} MXL_HYDRA_DISEQC_TX_MSG_T;

typedef enum
{
  MXL_HYDRA_FSK_CFG_TYPE_39KPBS = 0,    // 39.0kbps
  MXL_HYDRA_FSK_CFG_TYPE_39_017KPBS,    // 39.017kbps
  MXL_HYDRA_FSK_CFG_TYPE_115_2KPBS      // 115.2kbps
} MXL_HYDRA_FSK_OP_MODE_E;

typedef enum
{
  MXL_HYDRA_FSK_CFG_FREQ_MODE_NORMAL = 0,  // Normal Frequency Mode
  MXL_HYDRA_FSK_CFG_FREQ_MODE_MANUAL       // Manual Frequency Mode
} MXL_HYDRA_FSK_CFG_FREQ_MODE_E;

typedef struct
{
  UINT32 msgValidFlag; // 0 - invalid message, 1 - for valid message
  UINT32 msgLength;
  UINT8 msgBuff [MXL_HYDRA_FSK_MESG_MAX_LENGTH];
} MXL_HYDRA_FSK_MSG_T;

typedef struct
{
  UINT32 fskFreqMode;      // MXL_HYDRA_FSK_CFG_FREQ_MODE_E
  UINT32 freq;
} MXL58x_CFG_FSK_FREQ_T;


typedef enum
{
  MXL_HYDRA_AUX_CTRL_MODE_FSK = 0,  // Select FSK controller
  MXL_HYDRA_AUX_CTRL_MODE_DISEQC,   // Select DiSEqC controller
} MXL_HYDRA_AUX_CTRL_MODE_E;

typedef struct
{
  UINT32 diseqcId;  // DSQ 0, 1, 2 or 3
  UINT32 opMode;   // Envelope mode (0) or internal tone mode (1)
  UINT32 version;   // 0: 1.0 , 1: 1.1 , 2: Disable
  UINT32 centerFreq; // 0: 22KHz, 1: 33KHz and 2: 44 KHz
} MXL58x_DSQ_OP_MODE_T;

typedef struct
{
  UINT32 diseqcId;     // DSQ 0, 1, 2 or 3
  UINT32 opModeTx;     //Enable Tx Tone mode (1) or Tx Envelop mode (0)
  UINT32 invertTx;     //Invert Tx path (1)
  UINT32 opModeRx;     //Enable Rx Tone mode (1) or Rx Envelop mode (0)
  UINT32 invertRx;     //Invert Rx path (1)
  UINT32 version;      // 0: 1.0 , 1: 1.1 , 2: Disable
  UINT32 centerFreq;   // 0: 22KHz, 1: 33KHz and 2: 44 KHz
} MXL58x_DSQ_OP_MODE_TXRX_T;

typedef struct
{
  UINT32 diseqcId;
  UINT32 contToneFlag;  // 1: Enable , 0: Disable
} MXL_HYDRA_DISEQC_CFG_CONT_TONE_T;

#define MXL_HYDRA_NEWMSG_DELAY_MAX 63
#define MXL_HYDRA_ENDMSG_DELAY_MAX 63
#define MXL_HYDRA_STARTMSG_DELAY_MAX 255
#define MXL_HYDRA_REPLYMSG_DELAY_MAX 1023
typedef struct
{
    UINT16 newMsgDelayMs;   //  default: 0ms
    UINT16 endMsgDelayMs;   //  default: 14ms
    UINT16 replyDelayMs;    //  default: 0ms
    UINT16 startMsgDelayMs; //  default: 17ms
} MXL_HYDRA_DISEQC_MSG_DELAYS_T;

MXL_STATUS_E MxLWare_HYDRA_API_ResetFsk(UINT8 devId);

MXL_STATUS_E  MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode(UINT8 devId, MXL_HYDRA_AUX_CTRL_MODE_E devAuxCtrlMode);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcOpMode(UINT8 devId,
                                               MXL_HYDRA_DISEQC_ID_E diseqcId,
                                               MXL_HYDRA_DISEQC_OPMODE_E opMode,
                                               MXL_HYDRA_DISEQC_VER_E version,
                                               MXL_HYDRA_DISEQC_CARRIER_FREQ_E carrierFreqInHz);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcMsgDelays(UINT8 devId, 
                      MXL_HYDRA_DISEQC_ID_E diseqcId,
                      MXL_HYDRA_DISEQC_MSG_DELAYS_T * msgDelaysPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcOpModeTxRx(UINT8 devId,
                                                   MXL_HYDRA_DISEQC_ID_E diseqcId,
                                                   MXL_HYDRA_DISEQC_OPMODE_E opModeTx,
                                                   MXL_BOOL_E invertTx,
                                                   MXL_HYDRA_DISEQC_OPMODE_E opModeRx,
                                                   MXL_BOOL_E invertRx,
                                                   MXL_HYDRA_DISEQC_VER_E version,
                                                   MXL_HYDRA_DISEQC_CARRIER_FREQ_E carrierFreqInHz);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDiseqcStatus(UINT8 devId, MXL_HYDRA_DISEQC_ID_E diseqcId, UINT32 *statusPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDiseqcRead(UINT8 devId, MXL_HYDRA_DISEQC_ID_E diseqcId, MXL_HYDRA_DISEQC_RX_MSG_T *diseqcMsgPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcWrite(UINT8 devId, MXL_HYDRA_DISEQC_TX_MSG_T *diseqcMsgPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDiseqcContinuousToneCtrl(UINT8 devId,
                                                            MXL_HYDRA_DISEQC_ID_E diseqcId,
                                                            MXL_BOOL_E continuousToneCtrl);

MXL_STATUS_E MxLWare_HYDRA_API_CfgFskOpMode(UINT8 devId, MXL_HYDRA_FSK_OP_MODE_E fskCfgType);

MXL_STATUS_E MxLWare_HYDRA_API_ReqFskMsgRead(UINT8 devId, MXL_HYDRA_FSK_MSG_T *msgPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgFskMsgWrite(UINT8 devId, MXL_HYDRA_FSK_MSG_T *msgPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgFskFreq(UINT8 devId, MXL_HYDRA_FSK_CFG_FREQ_MODE_E fskFreqMode, UINT32 freqHz);

MXL_STATUS_E MxLWare_HYDRA_API_PowerDownFsk(UINT8 devId);

#ifdef __cplusplus
}
#endif

#endif
