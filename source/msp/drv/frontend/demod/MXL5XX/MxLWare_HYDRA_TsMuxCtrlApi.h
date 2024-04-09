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

#ifndef __MXL_HDR_TSMUX_API__
#define __MXL_HDR_TSMUX_API__

#include "MxLWare_HYDRA_DemodTunerApi.h"

#ifdef __cplusplus
extern "C" {
#endif

// there are two slices
// slice0 - TS0, TS1, TS2 & TS3
// slice1 - TS4, TS5, TS6 & TS7
#define MXL_HYDRA_TS_SLICE_MAX                    2

#define MAX_FIXED_PID_NUM                        32

#define MXL_HYDRA_NCO_CLK                       418 // 418 MHz

#define MXL_HYDRA_MAX_TS_CLOCK                   139 // 139 MHz

#define MXL_HYDRA_TS_FIXED_PID_FILT_SIZE          32

#define MXL_HYDRA_CB_PID_NUM_MAX                  60  // Max number of PIDs for Channel Bonding

#define MXL_HYDRA_SHARED_PID_FILT_SIZE_HYDRA_DEFAULT     33   // Shared PID filter size in 1-1 mux mode
#define MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT  40   // Shared PID filter size in 1-1 mux mode
#define MXL_HYDRA_SHARED_PID_FILT_SIZE_2_TO_1            66   // Shared PID filter size in 2-1 mux mode
#define MXL_HYDRA_SHARED_PID_FILT_SIZE_4_TO_1           132  // Shared PID filter size in 4-1 mux mode

#define MXL_LOGICAL_TO_PHYSICAL_BYPASS(x) ((x)|(1<<15))         //adds bypass bit
#define MXL_LOGICAL_TO_PHYSICAL_BYPASS_NOT(x) ((x)&(~(1<<15)))  //remove bypass bit

typedef enum
{
  MXL_HYDRA_SOFTWARE_PID_BANK = 0,
  MXL_HYDRA_HARDWARE_PID_BANK,
} MXL_HYDRA_PID_BANK_TYPE_E;

typedef enum
{
  MXL_HYDRA_TS_MUX_PID_REMAP = 0,
  MXL_HYDRA_TS_MUX_PREFIX_EXTRA_HEADER = 1,
} MXL_HYDRA_TS_MUX_MODE_E;

typedef enum
{
  MXL_HYDRA_TS_MUX_DISABLE = 0,  // No Mux ( 1 TSIF to 1 TSIF)
  MXL_HYDRA_TS_MUX_2_TO_1,       // Mux 2 TSIF to 1 TSIF
  MXL_HYDRA_TS_MUX_4_TO_1,       // Mux 4 TSIF to 1 TSIF
} MXL_HYDRA_TS_MUX_TYPE_E;

typedef enum
{
  MXL_HYDRA_TS_GROUP_0_3 = 0,     // TS group 0 to 3 (TS0, TS1, TS2 & TS3)
  MXL_HYDRA_TS_GROUP_4_7,         // TS group 0 to 3 (TS4, TS5, TS6 & TS7)
} MXL_HYDRA_TS_GROUP_E;

typedef enum
{
  MXL_HYDRA_TS_PIDS_ALLOW_ALL = 0,    // Allow all pids
  MXL_HYDRA_TS_PIDS_DROP_ALL,         // Drop all pids
  MXL_HYDRA_TS_INVALIDATE_PID_FILTER, // Delete current PD filter in the device

} MXL_HYDRA_TS_PID_FLT_CTRL_E;

typedef enum
{
  MXL_HYDRA_TS_PID_FIXED = 0,
  MXL_HYDRA_TS_PID_REGULAR,
} MXL_HYDRA_TS_PID_TYPE_E;

typedef struct
{
  UINT16 originalPid;           // pid from TS
  UINT16 remappedPid;           // remapped pid
  MXL_BOOL_E enable;            // enable or disable pid
  MXL_BOOL_E allowOrDrop;       // allow or drop pid
  MXL_BOOL_E enablePidRemap;    // enable or disable pid remap
  UINT8 bondId;                 // Bond ID in A0 always 0 - Only for 568 Sku
  UINT8 destId;                 // Output port ID for the PID - Only for 568 Sku
} MXL_HYDRA_TS_PID_T;

typedef struct
{
  MXL_BOOL_E enable;
  UINT8 numByte;
  UINT8 header[12];
} MXL_HYDRA_TS_MUX_PREFIX_HEADER_T;

typedef enum
{
  MXL_HYDRA_PID_BANK_A = 0,
  MXL_HYDRA_PID_BANK_B,
} MXL_HYDRA_PID_FILTER_BANK_E;

typedef enum
{
  MXL_HYDRA_MPEG_SERIAL_MSB_1ST = 0,
  MXL_HYDRA_MPEG_SERIAL_LSB_1ST,

  MXL_HYDRA_MPEG_SYNC_WIDTH_BIT = 0,
  MXL_HYDRA_MPEG_SYNC_WIDTH_BYTE
} MXL_HYDRA_MPEG_DATA_FMT_E;

typedef enum
{
  MXL_HYDRA_MPEG_MODE_SERIAL_4_WIRE = 0,   // MPEG 4 Wire serial mode
  MXL_HYDRA_MPEG_MODE_SERIAL_3_WIRE,       // MPEG 3 Wire serial mode
  MXL_HYDRA_MPEG_MODE_SERIAL_2_WIRE,       // MPEG 2 Wire serial mode
  MXL_HYDRA_MPEG_MODE_PARALLEL             // MPEG parallel mode - valid only for MxL581
} MXL_HYDRA_MPEG_MODE_E;

typedef enum
{
  MXL_HYDRA_XPT_TS_DATA = 0,    // TS Data
  MXL_HYDRA_XPT_TS_CLOCK,       // TS Clock
  MXL_HYDRA_XPT_TS_SYNC,        // TS Sync
  MXL_HYDRA_XPT_TS_VALID,       // TS Valid
  MXL_HYDRA_XPT_TS_MAX
} MXL_HYDRA_XPT_TS_E;

typedef enum
{
  MXL_HYDRA_MPEG_CLK_CONTINUOUS = 0,  // Continuous MPEG clock
  MXL_HYDRA_MPEG_CLK_GAPPED,          // Gapped (gated) MPEG clock
} MXL_HYDRA_MPEG_CLK_TYPE_E;

typedef enum
{
  MXL_HYDRA_MPEG_ACTIVE_LOW = 0,
  MXL_HYDRA_MPEG_ACTIVE_HIGH,

  MXL_HYDRA_MPEG_CLK_NEGATIVE = 0,
  MXL_HYDRA_MPEG_CLK_POSITIVE,

  MXL_HYDRA_MPEG_CLK_IN_PHASE = 0,
  MXL_HYDRA_MPEG_CLK_INVERTED,
} MXL_HYDRA_MPEG_CLK_FMT_E;

typedef enum
{
  MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_0_DEG = 0,
  MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_90_DEG,
  MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_180_DEG,
  MXL_HYDRA_MPEG_CLK_PHASE_SHIFT_270_DEG
} MXL_HYDRA_MPEG_CLK_PHASE_E;

typedef enum
{
  MXL_HYDRA_MPEG_ERR_REPLACE_SYNC = 0,
  MXL_HYDRA_MPEG_ERR_REPLACE_VALID,
  MXL_HYDRA_MPEG_ERR_INDICATION_DISABLED
} MXL_HYDRA_MPEG_ERR_INDICATION_E;

typedef struct
{
  MXL_BOOL_E                        enable;               // Enable or Disable MPEG OUT
  MXL_HYDRA_MPEG_CLK_TYPE_E         mpegClkType;          // Continuous or gapped
  MXL_HYDRA_MPEG_CLK_FMT_E          mpegClkPol;           // MPEG Clk polarity
  UINT8                             maxMpegClkRate;       // Max MPEG Clk rate (0 – 104 MHz, 139 MHz)
  MXL_HYDRA_MPEG_CLK_PHASE_E        mpegClkPhase;         // MPEG Clk phase
  MXL_HYDRA_MPEG_DATA_FMT_E         lsbOrMsbFirst;        // LSB first or MSB first in TS transmission
  MXL_HYDRA_MPEG_DATA_FMT_E         mpegSyncPulseWidth;   // MPEG SYNC pulse width (1-bit or 1-byte)
  MXL_HYDRA_MPEG_CLK_FMT_E          mpegValidPol;         // MPEG VALID polarity
  MXL_HYDRA_MPEG_CLK_FMT_E          mpegSyncPol;          // MPEG SYNC polarity
  MXL_HYDRA_MPEG_MODE_E             mpegMode;             // config 4/3/2-wire serial or parallel TS out
  MXL_HYDRA_MPEG_ERR_INDICATION_E   mpegErrorIndication;  // Enable or Disable MPEG error indication
} MXL_HYDRA_MPEGOUT_PARAM_T;

typedef enum
{
  MXL_HYDRA_EXT_TS_IN_0 = 0,
  MXL_HYDRA_EXT_TS_IN_1,
  MXL_HYDRA_EXT_TS_IN_2,
  MXL_HYDRA_EXT_TS_IN_3,
  MXL_HYDRA_EXT_TS_IN_MAX

} MXL_HYDRA_EXT_TS_IN_ID_E;

typedef  enum
{
  MXL_HYDRA_TS_OUT_0 = 0,
  MXL_HYDRA_TS_OUT_1,
  MXL_HYDRA_TS_OUT_2,
  MXL_HYDRA_TS_OUT_3,
  MXL_HYDRA_TS_OUT_4,
  MXL_HYDRA_TS_OUT_5,
  MXL_HYDRA_TS_OUT_6,
  MXL_HYDRA_TS_OUT_7,
  MXL_HYDRA_TS_OUT_MAX

} MXL_HYDRA_TS_OUT_ID_E;

typedef  enum
{
  MXL_HYDRA_TS_DRIVE_STRENGTH_1x = 0,
  MXL_HYDRA_TS_DRIVE_STRENGTH_2x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_3x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_4x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_5x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_6x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_7x,
  MXL_HYDRA_TS_DRIVE_STRENGTH_8x

} MXL_HYDRA_TS_DRIVE_STRENGTH_E;

typedef struct
{
  UINT32 regAddr;
  UINT32 data[2];
  UINT16 pidNum;
  MXL_BOOL_E  dirtyFlag;
  MXL_BOOL_E  inUse;
  UINT8 numOfBytes;
  MXL_HYDRA_DEMOD_ID_E demodID;  // demodId
} MXL_HYDRA_PID_T;

typedef struct
{
  UINT32 numPids;         /* Number of pid entries in array */
  UINT32 addOrDeletePids; /* Add or Delete pid entries from pid table */
  UINT32 demodMap;        /* Valid Only for A0 */
  UINT32 pidValue[MXL_HYDRA_CB_PID_NUM_MAX]; /* Pid entry */
  /*
   * <12:0>   pid entry 13-bits
   * <17:16>  Bond Id 2-bits
   * <31:24>  Destination Tag
   */
} MXL_HYDRA_PID_FILTER_TBL_T;

#define FIXED_PID_DATA(valid,drop,remapEnable,remapPid) ( (0x00000000 | (UINT32)valid) |                  \
                                                          (0x00000000 | ((UINT32)drop << 1)) |            \
                                                          (0x00000000 | (UINT32)(remapEnable << 2)) |     \
                                                          (0x00000000 | (UINT32)(remapPid << 16)))

#define REGULAR_PID_DATA_0(valid,drop,remapEnable,pid,msk) ( (0x00000000 | (UINT32)(valid & 0x1)) |               \
                                                             (0x00000000 | (((UINT32)drop & 0x1) << 1)) |         \
                                                             (0x00000000 | (((UINT32)remapEnable & 0x1) << 2)) |  \
                                                             (0x00000000 | (UINT32)((pid & 0x1FFF) << 4)) |       \
                                                             (0x00000000 | (((UINT32)msk & 0x1FFF) << 19)) )

#define REGULAR_PID_DATA_1(remapPid,portId) ( (0x00000000 | (UINT32)remapPid) |  (0x00000000 | (UINT32)(((UINT32)portId & 0x7) << 16)))


MXL_STATUS_E MxLWare_HYDRA_API_CfgMpegOutParams(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_MPEGOUT_PARAM_T* mpegOutParamPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSMuxMode(UINT8 devId, MXL_HYDRA_TS_MUX_TYPE_E tsMuxType);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSPidFilterCtrl(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_PID_FLT_CTRL_E tsFiltCtrl);

MXL_STATUS_E MxLWare_HYDRA_API_CfgPidFilterTbl(UINT8 devId,
                                               MXL_HYDRA_DEMOD_ID_E demodId,
                                               MXL_HYDRA_TS_PID_T * pidsPtr,
                                               UINT8 numPids);

MXL_STATUS_E MxLWare_HYDRA_API_ReqPidFilterTbl(UINT8 devId,
                                               MXL_HYDRA_DEMOD_ID_E demodId,
                                               MXL_HYDRA_TS_PID_T *pidsInfoPtr,
                                               UINT8 *numPidsPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSMixMuxMode(UINT8 devId, MXL_HYDRA_TS_GROUP_E tsGroupType, MXL_HYDRA_TS_MUX_TYPE_E tsMuxType);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSErrorIndicationCtrl(UINT8 devId, MXL_BOOL_E teiCtrl);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSTimeMuxOutput(UINT8 devId, MXL_BOOL_E tsTimeMuxCtrl);

MXL_STATUS_E MxLWare_HYDRA_API_CfgInjectPsiPackets(UINT8 devId, UINT8  tsifId, UINT16 pid, UINT16 packetLenInByte, UINT8 *packetPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTsMuxPrefixExtraTsHeader(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_MUX_PREFIX_HEADER_T * prefixHeaderPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqCurrTsMuxPrefixHeader(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_MUX_PREFIX_HEADER_T *prefixHeadPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgEncapsulateDSSIntoDVB(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_BOOL_E enableDssEncapsulation, MXL_BOOL_E enablePFBitToggling);

MXL_STATUS_E MxLWare_HYDRA_API_CfgEnablePCRCorrection(UINT8 devId, MXL_BOOL_E enablePCRCorrection);

MXL_STATUS_E MxLWare_HYDRA_API_CfgExternalTSInput(UINT8 devId, MXL_BOOL_E enable);

MXL_STATUS_E MxLWare_HYDRA_API_CfgMapExtTSInputToTSOutput(UINT8 devId,
                                                          MXL_HYDRA_EXT_TS_IN_ID_E mxlExtTSInputId,
                                                          MXL_HYDRA_TS_OUT_ID_E tsOutId,
                                                          MXL_BOOL_E enable);

MXL_STATUS_E MxLWare_HYDRA_API_CfgTSOutDriveStrength(UINT8 devId, MXL_HYDRA_TS_DRIVE_STRENGTH_E tsDriveStrength);

MXL_STATUS_E MxLWare_HYDRA_API_CfgXPTXBar(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId, MXL_HYDRA_TS_ID_E tsOutId);

#ifdef __cplusplus
}
#endif

#endif
