
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_RX_STATUS_H)
#define _CMD_RX_STATUS_H

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

#include "parmBinTemplate.h"

#define MCHAIN_UTF	3
#define MSTREAM_UTF	3

typedef enum {
	_rxStatusParm_code_numOfReports=0,
	_rxStatusParm_code_totalPackets,
	_rxStatusParm_code_goodPackets,
	_rxStatusParm_code_otherError,
	_rxStatusParm_code_crcPackets,
	_rxStatusParm_code_decrypErrors,
	_rxStatusParm_code_rateBit,
	_rxStatusParm_code_startTime,
	_rxStatusParm_code_endTime,
	_rxStatusParm_code_byteCount,
	_rxStatusParm_code_dontCount,
	_rxStatusParm_code_rssi,
	_rxStatusParm_code_rssic0,
	_rxStatusParm_code_rssic1,
	_rxStatusParm_code_rssic2,
	_rxStatusParm_code_rssie0,
	_rxStatusParm_code_rssie1,
	_rxStatusParm_code_rssie2,
	_rxStatusParm_code_evm0,
	_rxStatusParm_code_evm1,
	_rxStatusParm_code_evm2,
	_rxStatusParm_code_badrssi,
	_rxStatusParm_code_badrssic0,
	_rxStatusParm_code_badrssic1,
	_rxStatusParm_code_badrssic2,
	_rxStatusParm_code_badrssie0,
	_rxStatusParm_code_badrssie1,
	_rxStatusParm_code_badrssie2,
	_rxStatusParm_code_badevm0,
	_rxStatusParm_code_badevm1,
	_rxStatusParm_code_badevm2,
} CMD_RXSTATUS_PARMS_CODE;

typedef struct _rxStatusParm {
	uint32_t numOfReports;
	uint32_t totalPackets;
	uint32_t goodPackets;
	uint32_t otherError;
	uint32_t crcPackets;
	uint32_t decrypErrors;
	uint32_t rateBit;

	uint32_t startTime;
	uint32_t endTime;
	uint32_t byteCount;
	uint32_t dontCount;

	int32_t rssi;
	int32_t rssic[ 3];
	int32_t rssie[ 3];

	int32_t evm[ 3];

	int32_t badrssi;
	int32_t badrssic[ 3];
	int32_t badrssie[ 3];

	int32_t badevm[ 3];

} __ATTRIB_PACK _CMD_RXSTATUS_PARMS;

extern _PARM_BIN_TEMPLATE _rxStatusParm_bin_template[];

#endif // #if !defined(_CMD_RXSTATUS_PARMS_H)

