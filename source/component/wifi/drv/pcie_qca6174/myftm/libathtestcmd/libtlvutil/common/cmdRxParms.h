
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_RX_PARM_TEMPLATE)
#define _CMD_RX_PARM_TEMPLATE

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

#include "parmBinTemplate.h"
#include "art_utf_common.h"

typedef enum {
	_rxParm_code_channel=0,
	_rxParm_code_act,
	_rxParm_code_enANI,
	_rxParm_code_antenna,
	_rxParm_code_wlanMode,
	_rxParm_code_rxChain,
	_rxParm_expectedPkts,
	_rxParm_code_ack,
	_rxParm_code_bc,
	_rxParm_code_bandwidth,
	_rxParm_code_lpl,
	_rxParm_code_antswitch1,
	_rxParm_code_antswitch2,
	_rxParm_code_addr,
	_rxParm_code_bssid,
	_rxParm_code_btaddr,
	_rxParm_code_reserved,
	_rxParm_code_regDmn0,
	_rxParm_code_regDmn1,
	_rxParm_code_otpWriteFlag,
	_rxParm_code_flags,
	_rxParm_code_rateMask,
	_rxParm_code_spectralScan,
	_rxParm_code_noiseFloor,
} CMD_RX_PARMS_CODE;

#if defined(_HOST_SIM_TESTING)
#define ATH_MAC_LEN  6
#endif

typedef struct _rxParm {
	uint32_t  channel;
	uint32_t  rxMode;// uint32_t  act;
	uint32_t  enANI;
	uint32_t  antenna;
	uint32_t  wlanMode;
	uint32_t  rxChain;
	uint32_t  expectedPkts;
	uint32_t  ack;
	uint32_t  bc;
	uint32_t  bandwidth;
	uint32_t  lpl;
	uint32_t  antswitch1;
	uint32_t  antswitch2;
	u_char   addr[ATH_MAC_LEN/*6*/];
	u_char   bssid[ATH_MAC_LEN/*6*/];
	u_char   btaddr[ATH_MAC_LEN/*6*/];
	u_char   reserved[ 2 ]; // reserved to align 4B
	uint16_t  regDmn[ 2 ];
	uint32_t  otpWriteFlag;

	uint32_t  flags;
	uint32_t  rateMask[RATE_MASK_ROW_MAX/*6*/];
	uint16_t  spectralScan;
	int16_t   noiseFloor;
} __ATTRIB_PACK _CMD_RX_PARMS;


extern _PARM_BIN_TEMPLATE _rxParm_bin_template[];

#endif // #if !defined(_CMD_RX_PARM_TEMPLATE)

