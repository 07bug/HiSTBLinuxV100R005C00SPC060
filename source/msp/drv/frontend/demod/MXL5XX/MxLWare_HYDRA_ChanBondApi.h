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

#ifndef __MXL_HDR_CHAN_BOND_API__
#define __MXL_HDR_CHAN_BOND_API__

#include "MaxLinearDataTypes.h"
#include "MxLWare_HYDRA_SkuFeatures.h"
#include "MxLWare_HYDRA_DemodTunerApi.h"
#include "MxLWare_HYDRA_TsMuxCtrlApi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MXL_HYDRA_CB_DEMODS_MAX                5  // MAX of 5 Demods can be used for Chan Bond
#define MXL_HYDRA_CB_TS_PORTS_MAX              5  // MAX of 5 TS Ports can be used for Chan Bond
#define MXL_HYDRA_CB_GROUP_MAX                 3  // Max of channel bonding groups

#define MXL_HYDRA_CB_RESTART_PKT_IDX_ERROR              0x01
#define MXL_HYDRA_CB_RESTART_SEQ_NUM_ERROR              0x02
#define MXL_HYDRA_CB_RESTART_BOND_HDR_ERROR             0x04
#define MXL_HYDRA_CB_RESTART_CHUNK_SIZE_INVALID         0x08
#define MXL_HYDRA_CB_RESTART_NUM_CHANNELS_INVALID       0x10
#define MXL_HYDRA_CB_RESTART_DATA_FIELD_TAG_INVALID     0x20
#define MXL_HYDRA_CB_RESTART_PKT_TIME_ERROR             0x40
#define MXL_HYDRA_CB_RESTART_BOND_HDR_TIMEOUT_ERROR     0x80

typedef struct
{
  MXL_HYDRA_BCAST_STD_E standardMask;  // Standard DVB-S, DVB-S2 or DSS
  MXL_HYDRA_DEMOD_ID_E demodId;        // Demod ID
  UINT32 frequencyInHz;                // Channel frequency in Hz
  UINT32 freqSearchRangeKHz;           // Offset frequency search range
  UINT8 scrambleSequence[MXL_DEMOD_SCRAMBLE_SEQ_LEN];   // scramble sequence
  UINT32 scrambleCode;                                  // scramble gold code
} MXL_HYDRA_CHANBOND_CFG_T;

typedef struct
{
  MXL_BOOL_E cbGroupInUse;
  UINT8 numOfDemodsInCB;
  UINT8 numOfTsPorts;
  MXL_HYDRA_DEMOD_ID_E cbDemodId[MXL_HYDRA_CB_DEMODS_MAX];
  MXL_HYDRA_TS_OUT_ID_E cbTsOutId[MXL_HYDRA_CB_TS_PORTS_MAX];
} MXL_HYDRA_CHANBOND_GROUP_T;

typedef struct
{
  UINT32 symbolRateKSps;                                      // Symbol rate in KSps
  MXL_HYDRA_SPECTRUM_E spectrumInfo;                          // Auto, Inverted or Non-Inverted signal spectrum
  MXL_HYDRA_FEC_E fec;                                        // FEC information
  MXL_HYDRA_MODULATION_E modulation;                          // Modulation scheme
  MXL_HYDRA_PILOTS_E pilots;                                  // Pilots Auto, on or Off  // Only for DVB-S2
  MXL_HYDRA_ROLLOFF_E rollOff;                                // Signal rolloff
  UINT32 dropBondingHeader;                                   // drop bonding header
  MXL_HYDRA_CHANBOND_CFG_T cbDemodList[MXL_HYDRA_CB_DEMODS_MAX];  // List of demods & centre freq's
} MXL_HYDRA_CHANBOND_TUNE_PARAMS_T;

// Unbond
typedef struct
{
  UINT32 numOfDemodsInCB; // Number of demods in below mentioned chan bond config
  UINT32 demodId[MXL_HYDRA_CB_DEMODS_MAX]; // List of Demods used in the channel bond
} MXL_HYDRA_UNBOND_CFG_T;

typedef struct
{
  UINT32 standardMask;                  // Standard DVB-S, DVB-S2 or DSS
  UINT32 demodId;                       // Demod ID
  UINT32 frequencyInHz;                 // Channel frequency in Hz
  UINT32 freqSearchRangeKHz;            // Offset frequency search range
  UINT8 scrambleSequence[MXL_DEMOD_SCRAMBLE_SEQ_LEN];   // scramble sequence
  UINT32 scrambleCode;                  // scramble gold code
} MXL_HYDRA_TUNE_CFG_T;

typedef struct
{
  UINT32 tunerId;
  UINT32 numOfDemods;
  MXL_HYDRA_TUNE_CFG_T tuneCfgParams[MXL_HYDRA_CB_DEMODS_MAX];
  UINT32 spectrumInversion;     // Input : Spectrum inversion.
  UINT32 tsOutputMode;          // Serial or parallel
  UINT32 rollOff;               /* rollOff (alpha) factor */
  UINT32 symbolRateInHz;        /* Symbol rate */
  UINT32 pilots;                /* TRUE = pilots enabled */
  UINT32 modulationScheme;      // Input : Modulation Scheme is one of MXL_HYDRA_MODULATION_E
  UINT32 fecCodeRate;           // Input : Forward error correction rate. Is one of MXL_HYDRA_FEC_E
  UINT32 dropBondingHeader;
  UINT32 numOfTsPorts;
  UINT32 tsPortId[MXL_HYDRA_CB_TS_PORTS_MAX];
} MXL_HYDRA_CHANBOND_TUNE_PARAM_T;

///  Stats ////////

/* Channel bonding state */
typedef enum
{
  MXL_HYDRA_CHANBOND_STATE_INACTIVE = 0,
  MXL_HYDRA_CHANBOND_STATE_NO_SYNC,
  MXL_HYDRA_CHANBOND_STATE_SYNC,
  MXL_HYDRA_CHANBOND_STATE_RESTART,
  MXL_HYDRA_CHANBOND_STATE_MAX,
} MXL_HYDRA_CHANBOND_STATE_E;

/* Input channel based CB status definition */
typedef struct
{
  /* Bonding state */
  MXL_HYDRA_CHANBOND_STATE_E  bondingState;

  /* Bonding RESTART error conditions */
  UINT32 bondingRestartError;

  /* Input counters */
  UINT32 numInpPktsLo;
  UINT32 numInpPktsHi;
  UINT32 numBondingHdrLo;
  UINT32 numBondingHdrHi;
  UINT32 numSyncBondingHdr;

  /* PKT_IDX values*/
  UINT32 lastPktIdx;
  UINT32 lastBHdrPktIdx;
  UINT32 expectedBHdrPktIdx;

  /* PKT_TIME values */
  UINT32 lastPktTime;
  UINT32 lastBHdrPktTime;
  UINT32 expectedBHdrPktTime; /* PKT_TIME + (NUM_CODEWORDS_PER_CHUNK) * CODEWORD_TIME */

  /* CHUNK size values */
  UINT32 last4ChunkSizes;
  UINT32 minChunkSize;
  UINT32 maxChunkSize;
  UINT32 avgChunkSize;

  /* SKEW time values */
  UINT32 lastSkewTime;
  UINT32 minSkewTime;
  UINT32 maxSkewTime;
  UINT32 avgSkewTime;

  /* Counters for error conditions */
  UINT32 streamAlignmentErrorCount;
  UINT32 seqNumErrorCount;
  UINT32 chunkSizeInvalidCount;
  UINT32 dataFieldTagInvalidCount;
  UINT32 pktTimeErrorCount;
  UINT32 restartCount;
} MXL_HYDRA_CHANBOND_INPCH_STATS_T;

/* Add the CB stats per output TSport based on new definintion */
typedef struct
{
  UINT32 numOutPktsLo;
  UINT32 numOutPktsHi;
  UINT32 numOutBHdrPktsLo;
  UINT32 numOutBHdrPktsHi;
  UINT32 startTimeStamp;
  UINT32 currTimeStamp;
} MXL_HYDRA_CHANBOND_OUTCH_STATS_T;

typedef struct
{
  MXL_BOOL_E clearInputStats;   // 1 – clear input stats , 0 – don’t clear
  MXL_BOOL_E clearOutputStats;  // 1 – Clear output stats, 0 – don’t clear
} MXL_HYDRA_CB_CLEAR_STATS_T;

typedef struct
{
  UINT32 restartFlags;   // Each error condition is a bit filed.
                         // 0: No restart when associated error condition is detected.
                         // 1: Restart
} MXL_HYDRA_CHANBOND_RESTART_FLAGS_T;

typedef struct
{
  MXL_BOOL_E chanBondLockStatus;     // Demod FEC block lock info
  UINT32 lockTimeInMsecs;
} MXL_HYDRA_CHANBOND_LOCK_T;

#define XCPU_DRAM_BASE_ADDR           0x90760000

#define XCPU_DRAM_SPARE_REG           (0x9076B100)
#define XCPU_DRAM_CMD_REG             (0x9076B300)
#define XCPU_DRAM_STATS_REG           (0x9076B340)

#define XCPU_CMD_FROM_MCPU                (XCPU_DRAM_CMD_REG + 0x0000)    //0x3FFEA80C
#define XCPU_CMD_DBG_HALT                 (XCPU_DRAM_CMD_REG + 0x0004)    //0x3FFEA83C
#define XCPU_CB_CFG_TEST_MODE_REG         (XCPU_DRAM_CMD_REG + 0x0014)    // Drop or Allow CB headers
#define XCPU_CB_RESTART_CTRL_REG          (XCPU_DRAM_CMD_REG + 0x0018)    // Enable or Disable CB Re-Start on error
#define XCPU_CB_PKT_METERING_CTRL         (XCPU_DRAM_CMD_REG + 0x001C)    // Enable or Disable pkt_metering - default disabled
#define XPU_DBG_CMD_STATS_READ_CTRL_REG   (XCPU_DRAM_CMD_REG + 0x0020)

#define XCPU_HEART_BEAT                   (XCPU_DRAM_STATS_REG + 0x0008)  //0x3FFEA800
#define XCPU_FW_VER                       (XCPU_DRAM_STATS_REG + 0x000C)  //0x3FFEA80C
#define XCPU_SHMEM_TEST_STATUS            (XCPU_DRAM_STATS_REG + 0x0010)  //0x3FFEA808

#define XCPU_CB_INPUT_STATS_ADDR_REG      (XCPU_DRAM_STATS_REG + 0x0014)   // Input stats for Channel 0
#define XCPU_CB_OUTPUT_STATS_ADDR_REG     (XCPU_DRAM_STATS_REG + 0x0018)   // Input stats for Channel 0
#define XCPU_CB_SYNC_TIME_REG             (XCPU_DRAM_STATS_REG + 0x001C)   // CB SYNCk time in cycles
#define XCPU_CB_LOCK_TIME_REG             (XCPU_DRAM_STATS_REG + 0x0020)   // CB Lock time in cycles
#define XCPU_CH_BONDING_LOCK_STATUS       (XCPU_DRAM_STATS_REG + 0x0024)   // ChanBond Lock status
#define XCPU_CB_STATE_ADDR_REG            (XCPU_DRAM_STATS_REG + 0x0028)   // CB FW state

#define XCPU_XPT_CHANNEL_BOND_INPUT       (XCPU_DRAM_BASE_ADDR + 0xB460)   // XPT Input Mapping
#define XCPU_XPT_CHANNEL_BOND_OUTPUT      (XCPU_DRAM_BASE_ADDR + 0xB464)   // XPT Output Mapping


MXL_STATUS_E MxLWare_HYDRA_API_ReqChannelBondId(UINT8 devId, MXL_HYDRA_CHANBOND_GROUP_T *chanBondGroupPtr, UINT8 *bondIdPtr);
MXL_STATUS_E MxLWare_HYDRA_API_CfgCBTune(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT8 bondId, MXL_HYDRA_CHANBOND_TUNE_PARAMS_T *cbTuneParamsPtr);
MXL_STATUS_E MxLWare_HYDRA_API_CfgCBAbortTune(UINT8 devId, UINT8 bondId);
MXL_STATUS_E MxLWare_HYDRA_API_CfgFilterChanBondHdrs(UINT8 devId, MXL_BOOL_E enable);


MXL_STATUS_E MxLWare_HYDRA_API_ReqInputCBStatsEx(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_CHANBOND_INPCH_STATS_T * inputChanStatsPtr);
MXL_STATUS_E MxLWare_HYDRA_API_ReqOutputCBStatsEx(UINT8 devId, MXL_HYDRA_TS_OUT_ID_E tsOutId, MXL_HYDRA_CHANBOND_OUTCH_STATS_T * outputChanStatsPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgCBClearIOStats(UINT8 devId, MXL_HYDRA_CB_CLEAR_STATS_T *clearIOStatsPtr);
MXL_STATUS_E MxLWare_HYDRA_API_CfgChanBondRestart(UINT8 devId, UINT32 restartFlag);
MXL_STATUS_E MxLWare_HYDRA_API_ReqChanBondLockStatus(UINT8 devId, UINT8 bondId, MXL_HYDRA_CHANBOND_LOCK_T *chanBondLockPtr);



#ifdef __cplusplus
}
#endif

#endif
