/*==========================================================================

  TCMD header File

# Copyright (c) 2014 Qualcomm Technologies, Inc.
# All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/

/*===========================================================================

 */

/*
 * Copyright (c) 2006 Atheros Communications Inc.
 * All rights reserved.
 *
 *
// The software source and binaries included in this development package are
// licensed, not sold. You, or your company, received the package under one
// or more license agreements. The rights granted to you are specifically
// listed in these license agreement(s). All other rights remain with Atheros
// Communications, Inc., its subsidiaries, or the respective owner including
// those listed on the included copyright notices.  Distribution of any
// portion of this package must be in strict compliance with the license
// agreement(s) terms.
// </copyright>
//
//
 *
 */

#ifndef  TESTCMD_H_
#define  TESTCMD_H_

#include <stdint.h>

#if 0
#ifdef AR6002_REV2
#define TCMD_MAX_RATES 12
#else
#define TCMD_MAX_RATES 28
#endif
#else
#define TCMD_MAX_RATES 153
#endif

#define PREPACK
#define POSTPACK __attribute__ ((packed))

#define ATH_MAC_LEN 6
#define TC_CMDS_SIZE_MAX  256

#define DESC_STBC_ENA_MASK          0x00000001
#define DESC_STBC_ENA_SHIFT         0
#define DESC_LDPC_ENA_MASK          0x00000002
#define DESC_LDPC_ENA_SHIFT         1
#define PAPRD_ENA_MASK              0x00000004
#define PAPRD_ENA_SHIFT             2
#define TX_STATUS_PER_RATE_MASK     0x00000008
#define TX_STATUS_PER_RATE_SHIFT    3
#define PROCESS_RATE_IN_ORDER_MASK  0x00000010
#define PROCESS_RATE_IN_ORDER_SHIFT 4
#define RX_STATUS_PER_RATE_MASK     0x00000020
#define RX_STATUS_PER_RATE_SHIFT    5

#define HALF_SPEED_MODE         50
#define QUARTER_SPEED_MODE      51

#define RATE_STR_LEN             30
#define A_RATE_NUM      153
#define G_RATE_NUM      153


typedef enum {
	TPC_TX_PWR = 0,
	TPC_FORCED_GAIN,
	TPC_TGT_PWR,
	TPC_TX_FORCED_GAIN,
	TPC_FORCED_GAINIDX,
	TPC_FORCED_TGTPWR
} TPC_TYPE;

//from dk_cmd.h
typedef	struct TxDataStartParams {
	//TCMD_CONT_TX tCmd;
	uint32_t                testCmdId;
	uint32_t                mode;
	uint32_t                freq;
	uint32_t                dataRate;
	int32_t                 txPwr;
	uint32_t                antenna;
	uint32_t                enANI;
	uint32_t                scramblerOff;
	uint32_t                aifsn;
	uint32_t                pktSz;
	uint32_t                txPattern;
	uint32_t                shortGuard;
	uint32_t                numPackets;
	uint32_t                wlanMode;
	uint32_t                lpreamble;
	uint32_t                txChain;
	uint32_t                miscFlags;

	uint32_t                broadcast;
	u_char                  bssid[ATH_MAC_LEN];
	uint16_t                bandwidth;
	u_char                  txStation[ATH_MAC_LEN];
	u_char                  rxStation[ATH_MAC_LEN];
	uint32_t                tpcm;
	uint32_t                retries;
	uint32_t                agg;
	uint32_t                nPattern;
	u_char                  dataPattern[MPATTERN]; // bytes to be written
	int16_t                 PsatPower2G_t10[2][PSAT_WHAL_NUM_11G_CAL_PIERS_MAX];//12B
	int8_t                  PsatOfdmDelta2G_t10[2][PSAT_WHAL_NUM_11G_CAL_PIERS_MAX];//6B
	int16_t                 PsatPower5G_t10[2][PSAT_WHAL_NUM_11A_CAL_PIERS_MAX]; //32B
	int8_t                  PsatOfdmDelta5G_t10[2][PSAT_WHAL_NUM_11A_CAL_PIERS_MAX];//16B
	uint16_t                unUsed4;
	// The above is exactly the same as TCMD_CONT_TX
	uint16_t                rateMaskBitPosition[RATE_POWER_MAX_INDEX];
	uint16_t                txPower[RATE_POWER_MAX_INDEX];
	uint16_t                pktLength[RATE_POWER_MAX_INDEX];
	//uint8_t                 aggPerRate[RATE_POWER_MAX_INDEX];
	uint32_t                ir;
	uint16_t                gainIdx;
	int16_t                 dacGain;
	uint32_t                forcedGainPad;
	uint32_t                dutycycle;
	uint16_t                paConfig;
} __ATTRIB_PACK TX_DATA_START_PARAMS;

#define TCMD_TXPATTERN_ZERONE                 0x1
#define TCMD_TXPATTERN_ZERONE_DIS_SCRAMBLE    0x2

typedef PREPACK struct {
	uint32_t         testCmdId;
	uint32_t        act;
	uint32_t        enANI;
	PREPACK union {
		struct PREPACK TCMD_CONT_RX_PARA {
			uint32_t    freq;
			uint32_t    antenna;
			uint32_t    wlanMode;
			uint32_t    ack;
			uint32_t    rxChain;
			uint32_t    bc;
			uint32_t    bandwidth;
			uint32_t    lpl;/* low power listen */
			uint8_t    dataCheck;
			uint8_t    unUsed[3];
			uint16_t    spectralScan;
			int16_t     noiseFloor;
		} POSTPACK para;
		struct PREPACK TCMD_CONT_RX_REPORT {
			uint32_t    totalPkt;
			int32_t     rssiInDBm;
			uint32_t    crcErrPkt;
			uint32_t    secErrPkt;
			uint16_t    rateCnt[TCMD_MAX_RATES];
			uint16_t    rateCntShortGuard[TCMD_MAX_RATES];
			uint8_t		ssData[512];
			uint32_t	ssDataLength;
		} POSTPACK report;
		struct PREPACK TCMD_CONT_RX_MAC {
			u_char    addr[ATH_MAC_LEN];
			u_char    bssid[ATH_MAC_LEN];
			u_char    btaddr[ATH_MAC_LEN];
			uint16_t   regDmn[2];
			uint32_t   otpWriteFlag;
		} POSTPACK mac;
		struct PREPACK TCMD_CONT_RX_ANT_SWITCH_TABLE {
			uint32_t                antswitch1;
			uint32_t                antswitch2;
		}POSTPACK antswitchtable;
	} POSTPACK u;
} POSTPACK TCMD_CONT_RX;

//from dk_cmd.h
typedef	struct RxDataStartParams {
	uint32_t freq;
	uint32_t antenna;
	uint32_t                enANI;
	uint32_t                promiscuous;
	uint32_t                wlanMode;
	uint32_t                rxChain;
	uint32_t                broadcast;
	u_char                  bssid[ATH_MAC_LEN];
	uint16_t                bandwidth;
	u_char                  rxStation[ATH_MAC_LEN];
	uint16_t                unUsed2;
	uint32_t                numPackets;
	uint32_t                rateMask[RATE_MASK_ROW_MAX];
	uint8_t                 datacheck;
	uint8_t                 unUsed[3];
} __ATTRIB_PACK RX_DATA_START_PARAMS;

/* Force sleep/wake  test cmd
mode: TCMD_PM_WAKEUP - Wakeup the target
TCMD_PM_SLEEP - Force the target to sleep.
 */
typedef enum {
	TCMD_PM_WAKEUP = 1,	/* be consistent with target */
	TCMD_PM_SLEEP,
	TCMD_PM_DEEPSLEEP
} TCMD_PM_MODE;

typedef enum {
	TC_CMDS_TS =0,
	TC_CMDS_CAL,
	TC_CMDS_TPCCAL = TC_CMDS_CAL,
	TC_CMDS_TPCCAL_WITH_OTPWRITE,
	TC_CMDS_OTPDUMP,
	TC_CMDS_OTPSTREAMWRITE,
	TC_CMDS_EFUSEDUMP,
	TC_CMDS_EFUSEWRITE,
	TC_CMDS_READTHERMAL,
} TC_CMDS_ACT;

typedef PREPACK struct {
	uint32_t   testCmdId;
	uint32_t   act;
	PREPACK union {
		uint32_t  enANI;    // to be identical to CONT_RX struct
		struct PREPACK {
			uint16_t   length;
			uint8_t    version;
			uint8_t    bufLen;
		} POSTPACK parm;
	} POSTPACK u;
} POSTPACK TC_CMDS_HDR;

typedef PREPACK struct {
	TC_CMDS_HDR  hdr;
	char buf[TC_CMDS_SIZE_MAX];
} POSTPACK TC_CMDS;

typedef enum {
	TCMD_CONT_TX_ID,
	TCMD_CONT_RX_ID,
	TCMD_PM_ID,
	TC_CMDS_ID,
	TCMD_SET_REG_ID,
	TC_CMD_TLV_ID,

	/*For synergy purpose we added the following tcmd id but these
	  tcmd's will not go to the firmware instead we will write values
	  to the NV area */

	TCMD_NIC_MAC = 100,
	TCMD_CAL_FILE_INDEX = 101,
} TCMD_ID;


typedef enum {
	TCMD_CAL_RESERVED=0,
	TCMD_CAL_SWEEP,
	TCMD_CAL_VERIFY,
	TCMD_CAL_BY_FORCED_GAIN_IDX,
	TCMD_CAL_BY_TGT_PWR,
} TCMD_CAL_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* TESTCMD_H_ */
