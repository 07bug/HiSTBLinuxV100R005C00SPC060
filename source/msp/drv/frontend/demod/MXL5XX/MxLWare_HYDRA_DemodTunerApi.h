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

#ifndef __MXL_HDR_TUNER_DEMOD_API__
#define __MXL_HDR_TUNER_DEMOD_API__

//#include "MxLWare_HYDRA_Commands.h"
#include "MaxLinearDataTypes.h"
#include "MxLWare_HYDRA_SkuFeatures.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MXL_DEMOD_SCRAMBLE_SEQ_LEN  12

#define MAX_STEP_SIZE_24_XTAL_102_05_KHZ  195
#define MAX_STEP_SIZE_24_XTAL_204_10_KHZ  215
#define MAX_STEP_SIZE_24_XTAL_306_15_KHZ  203
#define MAX_STEP_SIZE_24_XTAL_408_20_KHZ  177

#define MAX_STEP_SIZE_27_XTAL_102_05_KHZ  195
#define MAX_STEP_SIZE_27_XTAL_204_10_KHZ  215
#define MAX_STEP_SIZE_27_XTAL_306_15_KHZ  203
#define MAX_STEP_SIZE_27_XTAL_408_20_KHZ  177

#define MXL_HYDRA_SPECTRUM_MIN_FREQ_KHZ  250000
#define MXL_HYDRA_SPECTRUM_MAX_FREQ_KHZ 2350000

#define MXL_HYDRA_TONE_THRESHOLD_LEVEL (-55)
#define MXL_HYDRA_FREQ_102_05_STEP_SIZE 102050
#define MXL_HYDRA_FREQ_204_10_STEP_SIZE 204100
#define MXL_HYDRA_FREQ_306_15_STEP_SIZE 306150
#define MXL_HYDRA_FREQ_408_20_STEP_SIZE 408200

#define MXL_HYDRA_RSSI_MONITOR_MIN_THRESHOLD (-60)
#define MXL_HYDRA_RSSI_MONITOR_MAX_THRESHOLD (0)

#define MXL_HYDRA_SYMBOLRATE_KSPS_MIN 1000

typedef struct
{
  SINT16 signalLevel;
  UINT32 frequency;
} TONE_DETECTION_INFO_T;

typedef enum
{
  DMD_STANDARD_ADDR = 0,
  DMD_SPECTRUM_INVERSION_ADDR,
  DMD_SPECTRUM_ROLL_OFF_ADDR,
  DMD_SYMBOL_RATE_ADDR,
  DMD_MODULATION_SCHEME_ADDR,
  DMD_FEC_CODE_RATE_ADDR,
  DMD_SNR_ADDR,
  DMD_FREQ_OFFSET_ADDR,
  DMD_CTL_FREQ_OFFSET_ADDR,
  DMD_STR_FREQ_OFFSET_ADDR,
  DMD_FTL_FREQ_OFFSET_ADDR,
  DMD_STR_NBC_SYNC_LOCK_ADDR,
  DMD_CYCLE_SLIP_COUNT_ADDR,
  DMD_DISPLAY_IQ_ADDR,
  DMD_DVBS2_CRC_ERRORS_ADDR,
  DMD_DVBS2_PER_COUNT_ADDR,
  DMD_DVBS2_PER_WINDOW_ADDR,
  DMD_DVBS_CORR_RS_ERRORS_ADDR,
  DMD_DVBS_UNCORR_RS_ERRORS_ADDR,
  DMD_DVBS_BER_COUNT_ADDR,
  DMD_DVBS_BER_WINDOW_ADDR,
  DMD_TUNER_ID_ADDR,
  DMD_DVBS2_PILOT_ON_OFF_ADDR,
  DMD_FREQ_SEARCH_RANGE_IN_KHZ_ADDR,

  MXL_DEMOD_CHAN_PARAMS_BUFF_SIZE,
} MXL_DEMOD_CHAN_PARAMS_OFFSET_E;

typedef enum
{
  MXL_HYDRA_TUNER_ID_0 = 0,
  MXL_HYDRA_TUNER_ID_1,
  MXL_HYDRA_TUNER_ID_2,
  MXL_HYDRA_TUNER_ID_3,
  MXL_HYDRA_TUNER_MAX
} MXL_HYDRA_TUNER_ID_E;

typedef  enum
{
  MXL_HYDRA_DEMOD_ID_0 = 0,
  MXL_HYDRA_DEMOD_ID_1,
  MXL_HYDRA_DEMOD_ID_2,
  MXL_HYDRA_DEMOD_ID_3,
  MXL_HYDRA_DEMOD_ID_4,
  MXL_HYDRA_DEMOD_ID_5,
  MXL_HYDRA_DEMOD_ID_6,
  MXL_HYDRA_DEMOD_ID_7,
  MXL_HYDRA_DEMOD_MAX
} MXL_HYDRA_DEMOD_ID_E;

typedef enum
{
  MXL_HYDRA_TS_ID_0 = 0,
  MXL_HYDRA_TS_ID_1,
  MXL_HYDRA_TS_ID_2,
  MXL_HYDRA_TS_ID_3,
  MXL_HYDRA_TS_ID_4,
  MXL_HYDRA_TS_ID_5,
  MXL_HYDRA_TS_ID_6,
  MXL_HYDRA_TS_ID_7,
  MXL_HYDRA_TS_MAX
} MXL_HYDRA_TS_ID_E;

typedef enum
{
  MXL_HYDRA_DSS = 0,
  MXL_HYDRA_DVBS,
  MXL_HYDRA_DVBS2,
} MXL_HYDRA_BCAST_STD_E;

typedef enum
{
  MXL_HYDRA_FEC_AUTO = 0,
  MXL_HYDRA_FEC_1_2,
  MXL_HYDRA_FEC_3_5,
  MXL_HYDRA_FEC_2_3,
  MXL_HYDRA_FEC_3_4,
  MXL_HYDRA_FEC_4_5,
  MXL_HYDRA_FEC_5_6,
  MXL_HYDRA_FEC_6_7,
  MXL_HYDRA_FEC_7_8,
  MXL_HYDRA_FEC_8_9,
  MXL_HYDRA_FEC_9_10,
} MXL_HYDRA_FEC_E;

typedef enum
{
  MXL_HYDRA_MOD_AUTO = 0,
  MXL_HYDRA_MOD_QPSK,
  MXL_HYDRA_MOD_8PSK
} MXL_HYDRA_MODULATION_E;

typedef enum
{
  MXL_HYDRA_SPECTRUM_AUTO = 0,
  MXL_HYDRA_SPECTRUM_INVERTED,
  MXL_HYDRA_SPECTRUM_NON_INVERTED,
} MXL_HYDRA_SPECTRUM_E;

typedef enum
{
  MXL_HYDRA_ROLLOFF_AUTO = 0,
  MXL_HYDRA_ROLLOFF_0_20,
  MXL_HYDRA_ROLLOFF_0_25,
  MXL_HYDRA_ROLLOFF_0_35
} MXL_HYDRA_ROLLOFF_E;

typedef enum
{
  MXL_HYDRA_PILOTS_OFF = 0,
  MXL_HYDRA_PILOTS_ON,
  MXL_HYDRA_PILOTS_AUTO
} MXL_HYDRA_PILOTS_E;

typedef struct
{
  MXL_HYDRA_FEC_E fec;                 // FEC information
  MXL_HYDRA_MODULATION_E modulation;   // Modulation scheme
  MXL_HYDRA_ROLLOFF_E rollOff;         // Signal rolloff
} MXL_HYDRA_TUNE_PARAMS_DVBS_T;

typedef struct
{
  MXL_HYDRA_FEC_E fec;                 // FEC information
  MXL_HYDRA_MODULATION_E modulation;   // Modulation scheme
  MXL_HYDRA_PILOTS_E pilots;           // Pilots Auto, on or Off
  MXL_HYDRA_ROLLOFF_E rollOff;         // Signal rolloff
} MXL_HYDRA_TUNE_PARAMS_DVBS2_T;

typedef struct
{
  MXL_HYDRA_FEC_E fec;     // FEC information
  MXL_HYDRA_ROLLOFF_E rollOff;         // Signal rolloff
} MXL_HYDRA_TUNE_PARAMS_DSS_T;

typedef struct
{
  MXL_HYDRA_BCAST_STD_E standardMask;  // Standard DVB-S, DVB-S2 or DSS
  UINT32 frequencyInHz;                // Channel frequency in Hz
  UINT32 freqSearchRangeKHz;            // Offset frequency search range
  UINT32 symbolRateKSps;               // Symbol rate in KSps
  MXL_HYDRA_SPECTRUM_E spectrumInfo;   // Auto, Inverted or Non-Inverted signal spectrum

  union
  {
    MXL_HYDRA_TUNE_PARAMS_DVBS_T paramsS;      // DVB-S tune parameters
    MXL_HYDRA_TUNE_PARAMS_DVBS2_T paramsS2;    // DVB-S2 tune parameters
    MXL_HYDRA_TUNE_PARAMS_DSS_T paramsDSS;     // DSS tune parameters
  } params;

} MXL_HYDRA_TUNE_PARAMS_T;

typedef enum
{
  MXL_HYDRA_FORMATTER = 0,
  MXL_HYDRA_LEGACY_FEC,
  MXL_HYDRA_FREQ_RECOVERY,
  MXL_HYDRA_NBC,
  MXL_HYDRA_CTL,
  MXL_HYDRA_EQ,
} MXL_HYDRA_CONSTELLATION_SRC_E;

typedef struct
{
  MXL_BOOL_E agcLock;     // AGC lock info
  MXL_BOOL_E fecLock;     // Demod FEC block lock info
} MXL_HYDRA_DEMOD_LOCK_T;

typedef struct
{
  UINT32 corrRsErrors;      // Corrected Error Counter;
  UINT32 rsErrors;          // RS decoder err counter
  UINT32 berWindow;         // Ber Windows
  UINT32 berCount;          // BER count
  UINT32 corrRsErrors1;     // Corrected Error Counter 1st iteration;
  UINT32 rsErrors1;         // RS decoder err counter 1st iteration
  UINT32 berWindow_Iter1;   // Ber Windows - post viterbi 1st iteration
  UINT32 berCount_Iter1;    // BER count - post viterbi 1st iteration
} MXL_HYDRA_DEMOD_STATUS_DVBS_T;

typedef struct
{
  UINT32 corrRsErrors;      // Corrected Error Counter;
  UINT32 rsErrors;          // RS decoder err counter
  UINT32 berWindow;         // Ber Windows
  UINT32 berCount;          // BER count
  UINT32 corrRsErrors1;     // Corrected Error Counter 1st iteration;
  UINT32 rsErrors1;         // RS decoder err counter 1st iteration
  UINT32 berWindow_Iter1;   // Ber Windows - post viterbi 1st iteration
  UINT32 berCount_Iter1;    // BER count - post viterbi 1st iteration
} MXL_HYDRA_DEMOD_STATUS_DSS_T;

typedef struct
{
  UINT32 crcErrors;         // CRC error counter
  UINT32 packetErrorCount;  // Number of packet errors
  UINT32 totalPackets;      // Total packets
} MXL_HYDRA_DEMOD_STATUS_DVBS2_T;

typedef struct
{
  MXL_HYDRA_BCAST_STD_E standardMask;                // Standard DVB-S, DVB-S2 or DSS

  union
  {
    MXL_HYDRA_DEMOD_STATUS_DVBS_T demodStatus_DVBS;    // DVB-S demod status
    MXL_HYDRA_DEMOD_STATUS_DVBS2_T demodStatus_DVBS2;  // DVB-S2 demod status
    MXL_HYDRA_DEMOD_STATUS_DSS_T demodStatus_DSS;      // DSS demod status
  } u;

} MXL_HYDRA_DEMOD_STATUS_T;

typedef struct
{
    UINT32 scaledBerIter1;
    UINT32 scaledBerIter2;
} MXL_HYDRA_DEMOD_SCALED_BER_T;

typedef struct
{
  SINT32 carrierOffsetInHz;       // CRL offset info
  SINT32 symbolOffsetInSymbol;    // SRL offset info
} MXL_HYDRA_DEMOD_SIG_OFFSET_INFO_T;


typedef struct
{
  UINT8 scrambleSequence[MXL_DEMOD_SCRAMBLE_SEQ_LEN];   // scramble sequence
  UINT32 scrambleCode;                                  // scramble gold code
} MXL_HYDRA_DEMOD_SCRAMBLE_INFO_T;

typedef enum
{
  MXL_HYDRA_STEP_SIZE_24_XTAL_102_05KHZ = 0,  // 102.05 KHz for 24 MHz XTAL
  MXL_HYDRA_STEP_SIZE_24_XTAL_204_10KHZ,  // 204.10 KHz for 24 MHz XTAL
  MXL_HYDRA_STEP_SIZE_24_XTAL_306_15KHZ,  // 306.15 KHz for 24 MHz XTAL
  MXL_HYDRA_STEP_SIZE_24_XTAL_408_20KHZ,  // 408.20 KHz for 24 MHz XTAL

  MXL_HYDRA_STEP_SIZE_27_XTAL_102_05KHZ,  // 102.05 KHz for 27 MHz XTAL
  MXL_HYDRA_STEP_SIZE_27_XTAL_204_35KHZ,  // 204.35 KHz for 27 MHz XTAL
  MXL_HYDRA_STEP_SIZE_27_XTAL_306_52KHZ,  // 306.52 KHz for 27 MHz XTAL
  MXL_HYDRA_STEP_SIZE_27_XTAL_408_69KHZ,  // 408.69 KHz for 27 MHz XTAL

} MXL_HYDRA_SPECTRUM_STEP_SIZE_E;

typedef enum
{
  MXL_HYDRA_SPECTRUM_RESOLUTION_00_1_DB = 0, // 0.1 dB
  MXL_HYDRA_SPECTRUM_RESOLUTION_01_0_DB, // 1.0 dB
  MXL_HYDRA_SPECTRUM_RESOLUTION_05_0_DB, // 5.0 dB
  MXL_HYDRA_SPECTRUM_RESOLUTION_10_0_DB, // 10 dB
} MXL_HYDRA_SPECTRUM_RESOLUTION_E;

typedef enum
{
  MXL_SPECTRUM_NO_ERROR = 0,
  MXL_SPECTRUM_INVALID_PARAMETER,
  MXL_SPECTRUM_INVALID_STEP_SIZE,
  MXL_SPECTRUM_BW_CANNOT_BE_COVERED,
  MXL_SPECTRUM_DEMOD_BUSY,
  MXL_SPECTRUM_TUNER_NOT_ENABLED,
} MXL_HYDRA_SPECTRUM_ERROR_CODE_E;

typedef struct
{
  UINT32 tunerIndex;        // TUNER Ctrl: one of MXL58x_TUNER_ID_E
  UINT32 demodIndex;        // DEMOD Ctrl: one of MXL58x_DEMOD_ID_E
  UINT32 stepSizeInKHz;     // MXL_HYDRA_SPECTRUM_STEP_SIZE_E
  UINT32 startingFreqInkHz;
  UINT32 totalSteps;
} MXL_HYDRA_SPECTRUM_REQ_T;

typedef enum
{
  MXL_HYDRA_SEARCH_MAX_OFFSET = 0, // DMD searches for max freq offset (i.e. 5MHz)
  MXL_HYDRA_SEARCH_BW_PLUS_ROLLOFF, // DMD searches for BW + ROLLOFF/2
} MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E;

typedef struct
{
  UINT32 demodIndex;
  UINT32 searchType;       // MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E
} MXL58x_CFG_FREQ_OFF_SEARCH_RANGE_T;

// Demod Para for Channel Tune
typedef struct
{
  UINT32 tunerIndex;

  UINT32 demodIndex;

  UINT32 frequencyInHz;     // Frequency

  UINT32 standard;          // one of MXL_HYDRA_BCAST_STD_E
  UINT32 spectrumInversion; // Input : Spectrum inversion.
  UINT32 rollOff;           /* rollOff (alpha) factor */
  UINT32 symbolRateInHz;    /* Symbol rate */
  UINT32 pilots;            /* TRUE = pilots enabled */
  UINT32 modulationScheme;  // Input : Modulation Scheme is one of MXL_HYDRA_MODULATION_E
  UINT32 fecCodeRate;       // Input : Forward error correction rate. Is one of MXL_HYDRA_FEC_E

  UINT32 maxCarrierOffsetInMHz; // Maximum carrier freq offset in MHz. Same as freqSearchRangeKHz, but in unit of MHz.

} MXL_HYDRA_DEMOD_PARAM_T;


MXL_STATUS_E MxLWare_HYDRA_API_CfgTunerEnable(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_BOOL_E enable);

MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerEnableStatus(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_BOOL_E *tunerEnablePtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodDisable(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId);

MXL_STATUS_E MxLWare_HYDRA_HelperFn_CfgDemodChanTuneParamSetUp(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_PARAM_T * demodChanCfgPtr, MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodChanTune(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodConstellationSource(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_CONSTELLATION_SRC_E source);

#ifdef MXL_ENABLE_SPECTRUM_RB
MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerPowerSpectrum(UINT8 devId,
                                                      MXL_HYDRA_TUNER_ID_E tunerId,
                                                      MXL_HYDRA_DEMOD_ID_E demodId,
                                                      UINT32 freqStartInKHz,
                                                      UINT32 numOfFreqSteps,
                                                      SINT16 * powerBufPtr,
                                                      MXL_HYDRA_SPECTRUM_ERROR_CODE_E *spectrumReadbackStatusPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqToneFrequency(UINT8 devId,
                                                MXL_HYDRA_TUNER_ID_E tunerId,
                                                MXL_HYDRA_DEMOD_ID_E demodId,
                                                UINT32 startFrequencyInKhz,
                                                UINT32 endFrequencyInKhz,
                                                SINT16 thresholdLevel,
                                                UINT8  *numOfTones,
                                                TONE_DETECTION_INFO_T *toneInfoPtr);

#endif //MXL_ENABLE_SPECTRUM_RB
MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodConstellationData(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT16 *iSamplePtr, SINT16 *qSamplePtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodLockStatus(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_LOCK_T *demodLockPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqAllDemodLockStatus(UINT8 devId, UINT8 *allDemodLockPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodSNR(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT16 *snrPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodChanParams(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TUNE_PARAMS_T *demodTuneParamsPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodRxPowerLevel(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, SINT32 *inputPwrLevelPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodErrorCounters(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_STATUS_T *demodStatusPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodScaledBER(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SCALED_BER_T *scaledBer);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDemodSignalOffsetInfo(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SIG_OFFSET_INFO_T *demodSigOffsetInfoPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodAbortTune(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodScrambleCode (UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_DEMOD_SCRAMBLE_INFO_T *demodScrambleInfoPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgClearDemodErrorCounters(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDemodSearchFreqOffset(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_SEARCH_FREQ_OFFSET_TYPE_E searchFreqType);

MXL_STATUS_E MxLWare_HYDRA_API_GainStepControl(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT8 gainState);

MXL_STATUS_E MxLWare_HYDRA_API_ReqAdcRssiPower(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, SINT32 *adcRssiPwr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqTunerSplitterAttenuation(UINT8 devId, UINT32 * splitterAttnPtr);

MXL_BOOL_E MxLWare_HYDRA_API_IsFscTunerDone(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId);

MXL_STATUS_E MxLWare_HYDRA_API_CfgRssiMonitor(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, SINT32 adcRssiThreshold, MXL_BOOL_E enable);

MXL_STATUS_E MxLWare_HYDRA_API_ReqRssiMonitorInterruptStatus(UINT8 devId, UINT32 * rssiInterruptStatusMaskPtr);

#ifdef __cplusplus
}
#endif

#endif
