
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_TX_STATUS_H)
#define _CMD_TX_STATUS_H

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

#include "parmBinTemplate.h"

#define MCHAIN_UTF 3

typedef enum {
	_txStatusParm_code_numOfReports=0,
	_txStatusParm_code_totalPackets,
	_txStatusParm_code_goodPackets,
	_txStatusParm_code_underruns,
	_txStatusParm_code_otherError,
	_txStatusParm_code_excessRetries,
	_txStatusParm_code_rateBit,
	_txStatusParm_code_shortRetry,
	_txStatusParm_code_longRetry,
	_txStatusParm_code_startTime,
	_txStatusParm_code_endTime,
	_txStatusParm_code_byteCount,
	_txStatusParm_code_dontCount,
	_txStatusParm_code_rssi,
	_txStatusParm_code_rssic0,
	_txStatusParm_code_rssic1,
	_txStatusParm_code_rssic2,
	_txStatusParm_code_rssie0,
	_txStatusParm_code_rssie1,
	_txStatusParm_code_rssie2,
	_txStatusParm_code_thermCal,
	_txStatusParm_code_pdadc,
	_txStatusParm_code_paCfg,
	_txStatusParm_code_gainIdx,
	_txStatusParm_code_dacGain,
} CMD_TXSTATUS_PARMS_CODE;

typedef struct _txStatusParm {
	uint32_t numOfReports;
	uint32_t totalPackets;
	uint32_t goodPackets;
	uint32_t underruns;
	uint32_t otherError;
	uint32_t excessRetries;
	uint32_t rateBit;
	int32_t shortRetry;
	int32_t longRetry;

	uint32_t startTime;
	uint32_t endTime;
	uint32_t byteCount;
	uint32_t dontCount;

	int32_t rssi;
	int32_t rssic[ 3 ];
	int32_t rssie[ 3 ];

	uint32_t thermCal;
	uint32_t pdadc;
	uint32_t paCfg;
	int32_t  gainIdx;
	int32_t  dacGain;
} __ATTRIB_PACK _CMD_TXSTATUS_PARMS;

extern _PARM_BIN_TEMPLATE _txStatusParm_bin_template[];

#endif // #if !defined(_CMD_TXSTATUS_PARMS_H)

