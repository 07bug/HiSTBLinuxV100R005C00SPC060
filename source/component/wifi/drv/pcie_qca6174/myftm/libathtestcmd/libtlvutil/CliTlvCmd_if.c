/* tlvCmd_if.c -  contains the ART wrapper functions */
/*
 * Copyright (c) 2014-2015 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

/* Copyright (c) 2000 Atheros Communications, Inc., All Rights Reserved */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "wlantype.h"

#include "art_utf_common.h"
#include "genTxBinCmdTlv.h"
#include "parseRxBinCmdTlv.h"

#include "tlv_rxParmDef.h"
#include "tlv_txParmDef.h"
#include "testcmd.h"

#include "CliTlvCmd_if.h"

#ifdef USE_GLIB
#include <glib.h>
#define strlcat g_strlcat
#define strlcpy g_strlcpy

#else
#include <string.h>
#define strlcat strncat
#define strlcpy strncpy

#endif
#define ALOGE printf
typedef struct _TlvParamDefault
{
	unsigned char *key;
	unsigned char data[6];
} TLV_PARAM_DEFAULT;

static TLV_PARAM_DEFAULT TlvTxParamDefaultTbl[] =
{
	{(unsigned char *)TLV_TXPARM_KEY_CHANNEL, TLV_TXPARM_DEFAULT_CHANNEL},
	{(unsigned char *)TLV_TXPARM_KEY_TXMODE, TLV_TXPARM_DEFAULT_TXMODE},
#if 0
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK0, TLV_TXPARM_DEFAULT_RATEMASK0},
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK1, TLV_TXPARM_DEFAULT_RATEMASK1},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART0, TLV_TXPARM_DEFAULT_PWRGAINSTART0},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART1, TLV_TXPARM_DEFAULT_PWRGAINSTART1},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART2, TLV_TXPARM_DEFAULT_PWRGAINSTART2},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART3, TLV_TXPARM_DEFAULT_PWRGAINSTART3},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART4, TLV_TXPARM_DEFAULT_PWRGAINSTART4},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART5, TLV_TXPARM_DEFAULT_PWRGAINSTART5},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART6, TLV_TXPARM_DEFAULT_PWRGAINSTART6},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART7, TLV_TXPARM_DEFAULT_PWRGAINSTART7},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART8, TLV_TXPARM_DEFAULT_PWRGAINSTART8},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART9, TLV_TXPARM_DEFAULT_PWRGAINSTART9},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART10, TLV_TXPARM_DEFAULT_PWRGAINSTART10},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART11, TLV_TXPARM_DEFAULT_PWRGAINSTART11},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART12, TLV_TXPARM_DEFAULT_PWRGAINSTART12},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART13, TLV_TXPARM_DEFAULT_PWRGAINSTART13},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART14, TLV_TXPARM_DEFAULT_PWRGAINSTART14},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTART15, TLV_TXPARM_DEFAULT_PWRGAINSTART15},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND0, TLV_TXPARM_DEFAULT_PWRGAINEND0},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND1, TLV_TXPARM_DEFAULT_PWRGAINEND1},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND2, TLV_TXPARM_DEFAULT_PWRGAINEND2},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND3, TLV_TXPARM_DEFAULT_PWRGAINEND3},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND4, TLV_TXPARM_DEFAULT_PWRGAINEND4},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND5, TLV_TXPARM_DEFAULT_PWRGAINEND5},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND6, TLV_TXPARM_DEFAULT_PWRGAINEND6},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND7, TLV_TXPARM_DEFAULT_PWRGAINEND7},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND8, TLV_TXPARM_DEFAULT_PWRGAINEND8},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND9, TLV_TXPARM_DEFAULT_PWRGAINEND9},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND10, TLV_TXPARM_DEFAULT_PWRGAINEND10},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND11, TLV_TXPARM_DEFAULT_PWRGAINEND11},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND12, TLV_TXPARM_DEFAULT_PWRGAINEND12},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND13, TLV_TXPARM_DEFAULT_PWRGAINEND13},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND14, TLV_TXPARM_DEFAULT_PWRGAINEND14},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINEND15, TLV_TXPARM_DEFAULT_PWRGAINEND15},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP0, TLV_TXPARM_DEFAULT_PWRGAINSTEP0},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP1, TLV_TXPARM_DEFAULT_PWRGAINSTEP1},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP2, TLV_TXPARM_DEFAULT_PWRGAINSTEP2},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP3, TLV_TXPARM_DEFAULT_PWRGAINSTEP3},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP4, TLV_TXPARM_DEFAULT_PWRGAINSTEP4},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP5, TLV_TXPARM_DEFAULT_PWRGAINSTEP5},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP6, TLV_TXPARM_DEFAULT_PWRGAINSTEP6},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP7, TLV_TXPARM_DEFAULT_PWRGAINSTEP7},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP8, TLV_TXPARM_DEFAULT_PWRGAINSTEP8},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP9, TLV_TXPARM_DEFAULT_PWRGAINSTEP9},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP10, TLV_TXPARM_DEFAULT_PWRGAINSTEP10},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP11, TLV_TXPARM_DEFAULT_PWRGAINSTEP11},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP12, TLV_TXPARM_DEFAULT_PWRGAINSTEP12},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP13, TLV_TXPARM_DEFAULT_PWRGAINSTEP13},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP14, TLV_TXPARM_DEFAULT_PWRGAINSTEP14},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAINSTEP15, TLV_TXPARM_DEFAULT_PWRGAINSTEP15},
#endif //0
	{(unsigned char *)TLV_TXPARM_KEY_ANTENNA, TLV_TXPARM_DEFAULT_ANTENNA},
	{(unsigned char *)TLV_TXPARM_KEY_ENANI, TLV_TXPARM_DEFAULT_ENANI},
	{(unsigned char *)TLV_TXPARM_KEY_SCRAMBLEROFF, TLV_TXPARM_DEFAULT_SCRAMBLEROFF},
	{(unsigned char *)TLV_TXPARM_KEY_AIFSN, TLV_TXPARM_DEFAULT_AIFSN},
	{(unsigned char *)TLV_TXPARM_KEY_PKTSZ, TLV_TXPARM_DEFAULT_PKTSZ},
	{(unsigned char *)TLV_TXPARM_KEY_TXPATTERN, TLV_TXPARM_DEFAULT_TXPATTERN},
	{(unsigned char *)TLV_TXPARM_KEY_SHORTGUARD, TLV_TXPARM_DEFAULT_SHORTGUARD},
	{(unsigned char *)TLV_TXPARM_KEY_NUMPACKETS, TLV_TXPARM_DEFAULT_NUMPACKETS},
	{(unsigned char *)TLV_TXPARM_KEY_WLANMODE, TLV_TXPARM_DEFAULT_WLANMODE},
	{(unsigned char *)TLV_TXPARM_KEY_TXCHAIN0, TLV_TXPARM_DEFAULT_TXCHAIN0},
	{(unsigned char *)TLV_TXPARM_KEY_TXCHAIN1, TLV_TXPARM_DEFAULT_TXCHAIN1},
	{(unsigned char *)TLV_TXPARM_KEY_TXCHAIN2, TLV_TXPARM_DEFAULT_TXCHAIN2},
	{(unsigned char *)TLV_TXPARM_KEY_TXCHAIN3, TLV_TXPARM_DEFAULT_TXCHAIN3},
	{(unsigned char *)TLV_TXPARM_KEY_TPCM, TLV_TXPARM_DEFAULT_TPCM},
	{(unsigned char *)TLV_TXPARM_KEY_FLAGS, TLV_TXPARM_DEFAULT_FLAGS},
	{(unsigned char *)TLV_TXPARM_KEY_AGG, TLV_TXPARM_DEFAULT_AGG},
	{(unsigned char *)TLV_TXPARM_KEY_BROADCAST, TLV_TXPARM_DEFAULT_BROADCAST},
	{(unsigned char *)TLV_TXPARM_KEY_BANDWIDTH, TLV_TXPARM_DEFAULT_BANDWIDTH},
	{(unsigned char *)TLV_TXPARM_KEY_BSSID, TLV_TXPARM_DEFAULT_BSSID},
	{(unsigned char *)TLV_TXPARM_KEY_TXSTATION, TLV_TXPARM_DEFAULT_TXSTATION},
	{(unsigned char *)TLV_TXPARM_KEY_RXSTATION, TLV_TXPARM_DEFAULT_RXSTATION},
	{(unsigned char *)TLV_TXPARM_KEY_RESERVED, TLV_TXPARM_DEFAULT_RESERVED},
	{(unsigned char *)TLV_TXPARM_KEY_DUTYCYCLE, TLV_TXPARM_DEFAULT_DUTYCYCLE},
	{(unsigned char *)TLV_TXPARM_KEY_NPATTERN, TLV_TXPARM_DEFAULT_NPATTERN},
	{(unsigned char *)TLV_TXPARM_KEY_RESERVED1, TLV_TXPARM_DEFAULT_RESERVED1},
	{(unsigned char *)TLV_TXPARM_KEY_DATAPATTERN, TLV_TXPARM_DEFAULT_DATAPATTERN},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX0, TLV_TXPARM_DEFAULT_RATEBITINDEX0},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX1, TLV_TXPARM_DEFAULT_RATEBITINDEX1},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX2, TLV_TXPARM_DEFAULT_RATEBITINDEX2},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX3, TLV_TXPARM_DEFAULT_RATEBITINDEX3},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX4, TLV_TXPARM_DEFAULT_RATEBITINDEX4},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX5, TLV_TXPARM_DEFAULT_RATEBITINDEX5},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX6, TLV_TXPARM_DEFAULT_RATEBITINDEX6},
	{(unsigned char *)TLV_TXPARM_KEY_RATEBITINDEX7, TLV_TXPARM_DEFAULT_RATEBITINDEX7},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER0, TLV_TXPARM_DEFAULT_TXPOWER0},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER1, TLV_TXPARM_DEFAULT_TXPOWER1},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER2, TLV_TXPARM_DEFAULT_TXPOWER2},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER3, TLV_TXPARM_DEFAULT_TXPOWER3},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER4, TLV_TXPARM_DEFAULT_TXPOWER4},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER5, TLV_TXPARM_DEFAULT_TXPOWER5},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER6, TLV_TXPARM_DEFAULT_TXPOWER6},
	{(unsigned char *)TLV_TXPARM_KEY_TXPOWER7, TLV_TXPARM_DEFAULT_TXPOWER7},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN0, TLV_TXPARM_DEFAULT_PKTLEN0},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN1, TLV_TXPARM_DEFAULT_PKTLEN1},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN2, TLV_TXPARM_DEFAULT_PKTLEN2},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN3, TLV_TXPARM_DEFAULT_PKTLEN3},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN4, TLV_TXPARM_DEFAULT_PKTLEN4},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN5, TLV_TXPARM_DEFAULT_PKTLEN5},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN6, TLV_TXPARM_DEFAULT_PKTLEN6},
	{(unsigned char *)TLV_TXPARM_KEY_PKTLEN7, TLV_TXPARM_DEFAULT_PKTLEN7},
#if 0
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE0, TLV_TXPARM_DEFAULT_AGGPERRATE0},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE1, TLV_TXPARM_DEFAULT_AGGPERRATE1},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE2, TLV_TXPARM_DEFAULT_AGGPERRATE2},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE3, TLV_TXPARM_DEFAULT_AGGPERRATE3},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE4, TLV_TXPARM_DEFAULT_AGGPERRATE4},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE5, TLV_TXPARM_DEFAULT_AGGPERRATE5},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE6, TLV_TXPARM_DEFAULT_AGGPERRATE6},
	{(unsigned char *)TLV_TXPARM_KEY_AGGPERRATE7, TLV_TXPARM_DEFAULT_AGGPERRATE7},
#endif //0
	{(unsigned char *)TLV_TXPARM_KEY_IR, TLV_TXPARM_DEFAULT_IR},
#if 0
	{(unsigned char *)TLV_TXPARM_KEY_GAINSTART, TLV_TXPARM_DEFAULT_GAINSTART},
	{(unsigned char *)TLV_TXPARM_KEY_GAINSTEP, TLV_TXPARM_DEFAULT_GAINSTEP},
	{(unsigned char *)TLV_TXPARM_KEY_GAINEND, TLV_TXPARM_DEFAULT_GAINEND},
	{(unsigned char *)TLV_TXPARM_KEY_RESERVED2, TLV_TXPARM_DEFAULT_RESERVED2},
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK11AC0, TLV_TXPARM_DEFAULT_RATEMASK11AC0},
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK11AC1, TLV_TXPARM_DEFAULT_RATEMASK11AC1},
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK11AC2, TLV_TXPARM_DEFAULT_RATEMASK11AC2},
	{(unsigned char *)TLV_TXPARM_KEY_RATEMASK11AC3, TLV_TXPARM_DEFAULT_RATEMASK11AC3},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC0, TLV_TXPARM_DEFAULT_PWRGAIN11AC0},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC1, TLV_TXPARM_DEFAULT_PWRGAIN11AC1},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC2, TLV_TXPARM_DEFAULT_PWRGAIN11AC2},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC3, TLV_TXPARM_DEFAULT_PWRGAIN11AC3},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC4, TLV_TXPARM_DEFAULT_PWRGAIN11AC4},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC5, TLV_TXPARM_DEFAULT_PWRGAIN11AC5},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC6, TLV_TXPARM_DEFAULT_PWRGAIN11AC6},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC7, TLV_TXPARM_DEFAULT_PWRGAIN11AC7},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC8, TLV_TXPARM_DEFAULT_PWRGAIN11AC8},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC9, TLV_TXPARM_DEFAULT_PWRGAIN11AC9},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC10, TLV_TXPARM_DEFAULT_PWRGAIN11AC10},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC11, TLV_TXPARM_DEFAULT_PWRGAIN11AC11},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC12, TLV_TXPARM_DEFAULT_PWRGAIN11AC12},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC13, TLV_TXPARM_DEFAULT_PWRGAIN11AC13},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC14, TLV_TXPARM_DEFAULT_PWRGAIN11AC14},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC15, TLV_TXPARM_DEFAULT_PWRGAIN11AC15},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC16, TLV_TXPARM_DEFAULT_PWRGAIN11AC16},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC17, TLV_TXPARM_DEFAULT_PWRGAIN11AC17},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC18, TLV_TXPARM_DEFAULT_PWRGAIN11AC18},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC19, TLV_TXPARM_DEFAULT_PWRGAIN11AC19},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC20, TLV_TXPARM_DEFAULT_PWRGAIN11AC20},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC21, TLV_TXPARM_DEFAULT_PWRGAIN11AC21},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC22, TLV_TXPARM_DEFAULT_PWRGAIN11AC22},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC23, TLV_TXPARM_DEFAULT_PWRGAIN11AC23},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC24, TLV_TXPARM_DEFAULT_PWRGAIN11AC24},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC25, TLV_TXPARM_DEFAULT_PWRGAIN11AC25},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC26, TLV_TXPARM_DEFAULT_PWRGAIN11AC26},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC27, TLV_TXPARM_DEFAULT_PWRGAIN11AC27},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC28, TLV_TXPARM_DEFAULT_PWRGAIN11AC28},
	{(unsigned char *)TLV_TXPARM_KEY_PWRGAIN11AC29, TLV_TXPARM_DEFAULT_PWRGAIN11AC29},
#endif //0
	{(unsigned char *)TLV_TXPARM_KEY_GAINIDX, TLV_TXPARM_DEFAULT_GAINIDX},
	{(unsigned char *)TLV_TXPARM_KEY_DACGAIN, TLV_TXPARM_DEFAULT_DACGAIN},
	{(unsigned char *)TLV_TXPARM_KEY_PACONFIG, TLV_TXPARM_DEFAULT_PACONFIG},
};

static TLV_PARAM_DEFAULT TlvRxParamDefaultTbl[] =
{
	{(unsigned char *)TLV_RXPARM_KEY_CHANNEL, TLV_RXPARM_DEFAULT_CHANNEL},
	{(unsigned char *)TLV_RXPARM_KEY_RXMODE, TLV_RXPARM_DEFAULT_RXMODE},
	{(unsigned char *)TLV_RXPARM_KEY_ENANI, TLV_RXPARM_DEFAULT_ENANI},
	{(unsigned char *)TLV_RXPARM_KEY_ANTENNA, TLV_RXPARM_DEFAULT_ANTENNA},
	{(unsigned char *)TLV_RXPARM_KEY_WLANMODE, TLV_RXPARM_DEFAULT_WLANMODE},
	{(unsigned char *)TLV_RXPARM_KEY_RXCHAIN, TLV_RXPARM_DEFAULT_RXCHAIN},
	{(unsigned char *)TLV_RXPARM_KEY_EXPECTEDPACKETS, TLV_RXPARM_DEFAULT_EXPECTEDPACKETS},
	{(unsigned char *)TLV_RXPARM_KEY_ACK, TLV_RXPARM_DEFAULT_ACK},
	{(unsigned char *)TLV_RXPARM_KEY_BROARDCAST, TLV_RXPARM_DEFAULT_BROARDCAST},
	{(unsigned char *)TLV_RXPARM_KEY_BANDWIDTH, TLV_RXPARM_DEFAULT_BANDWIDTH},
	{(unsigned char *)TLV_RXPARM_KEY_LPL, TLV_RXPARM_DEFAULT_LPL},
	{(unsigned char *)TLV_RXPARM_KEY_ANTSWITCH1, TLV_RXPARM_DEFAULT_ANTSWITCH1},
	{(unsigned char *)TLV_RXPARM_KEY_ANTSWITCH2, TLV_RXPARM_DEFAULT_ANTSWITCH2},
	{(unsigned char *)TLV_RXPARM_KEY_ADDR, TLV_RXPARM_DEFAULT_ADDR},
	{(unsigned char *)TLV_RXPARM_KEY_BSSID, TLV_RXPARM_DEFAULT_BSSID},
	{(unsigned char *)TLV_RXPARM_KEY_BTADDR, TLV_RXPARM_DEFAULT_BTADDR},
	{(unsigned char *)TLV_RXPARM_KEY_RESERVED, TLV_RXPARM_DEFAULT_RESERVED},
	{(unsigned char *)TLV_RXPARM_KEY_REGDMN0, TLV_RXPARM_DEFAULT_REGDMN0},
	{(unsigned char *)TLV_RXPARM_KEY_REGDMN1, TLV_RXPARM_DEFAULT_REGDMN1},
	{(unsigned char *)TLV_RXPARM_KEY_OTPWRITEFLAG, TLV_RXPARM_DEFAULT_OTPWRITEFLAG},
	{(unsigned char *)TLV_RXPARM_KEY_FLAGS, TLV_RXPARM_DEFAULT_FLAGS},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK0, TLV_RXPARM_DEFAULT_RATEMASK0},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK1, TLV_RXPARM_DEFAULT_RATEMASK1},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK2, TLV_RXPARM_DEFAULT_RATEMASK2},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK3, TLV_RXPARM_DEFAULT_RATEMASK3},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK4, TLV_RXPARM_DEFAULT_RATEMASK4},
	{(unsigned char *)TLV_RXPARM_KEY_RATEMASK5, TLV_RXPARM_DEFAULT_RATEMASK5},
};

void addParameterIfNeeded (TLV_PARAM_DEFAULT *pTlvParamDefaultTbl, uint32_t tblSize, uint8_t *key, uint8_t *pData, uint32_t size)
{
	uint8_t data[40];
	uint32_t i, j;

	for (i = 0; i < tblSize; ++i)
	{
		if (strcmp(key, pTlvParamDefaultTbl[i].key) == 0)
		{
			// add only if the value is different from default
			for (j = 0;j < size; ++j)
			{
				if (pData[j] != pTlvParamDefaultTbl[i].data[j])
				{
					// copy to local in case type of pData defined in TX_DATA_START_PARAMS is different from the one defined in cmdTxParms
					memset (data, 0, sizeof(data));
					memcpy (data, pData, size);

					printf("TLV - addParameterToCommand(%s) {", key);
					for (j = 0; j < size; ++j)
					{
						printf("0x%02x,", data[j]);
					}
					printf("}\n");

					addParameterToCommand(key, data);
					break;
				}
			}
			break;
		}
	}
}

void addParameterSequenceIfNeeded (TLV_PARAM_DEFAULT *pTlvParamDefaultTbl, uint32_t tblSize, uint8_t *firstKey, uint8_t *pData, uint32_t size, uint32_t sequenceSize)
{
	uint8_t key[30], indexStr[4], data[4];
	uint32_t i, j, k, n, keyLen;

	if (size > 4)
	{
		printf("addTxParameterSequenceIfNeeded - WARNING parameter size > 4\n");
		size = 4;
	}
	//search the firstKey from the table
	for (i = 0; i < tblSize; ++i)
	{
		if (strcmp (firstKey, pTlvParamDefaultTbl[i].key) == 0)
		{
			//found
			keyLen =  strlen(firstKey);
			// chop the key index
			memcpy (key, firstKey, keyLen-1);
			for (j = i, k = 0; k < (int)sequenceSize; ++j, ++k)
			{
				// get data
				memset (data, 0, sizeof(data));
				memcpy (data, pData+(k*size), size);
				key[keyLen-1] = '\0';
				// concatenate the index
				snprintf (indexStr, 4, "%d", k);
				strlcat (key, indexStr, sizeof(key));

				printf("TLV - addParameterToCommand(%s) {", key);
				for (n = 0; n < size; ++n)
				{
					printf("0x%02x,", data[n]);
				}
				printf("}\n");

				// add only if the value is different from default
				addParameterToCommand(key, data);
			}
			break;
		}
	}
}

void addTxParameterIfNeeded (uint8_t *key, uint8_t *pData, uint32_t size)
{
	addParameterIfNeeded (TlvTxParamDefaultTbl, sizeof(TlvTxParamDefaultTbl)/sizeof(TLV_PARAM_DEFAULT), key, pData, size);
}

void addTxParameterSequenceIfNeeded (uint8_t *firstKey, uint8_t *pData, uint32_t size, uint32_t sequenceSize)
{
	addParameterSequenceIfNeeded (TlvTxParamDefaultTbl, sizeof(TlvTxParamDefaultTbl)/sizeof(TLV_PARAM_DEFAULT), firstKey, pData, size, sequenceSize);
}

void addTxParameters (TX_DATA_START_PARAMS *Params)
{
	//uint32_t txChain[MAX_TX_CHAIN];
	//int i;

	addTxParameterIfNeeded(TLV_TXPARM_KEY_CHANNEL, (uint8_t *)&Params->freq, sizeof(Params->freq));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_CHANNEL, %d)\n", __func__, Params->freq);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_ANTENNA, (uint8_t *)&Params->antenna, sizeof(Params->antenna));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_ANTENNA, %d)\n", __func__, Params->antenna);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_ENANI, (uint8_t *)&Params->enANI, sizeof(Params->enANI));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_ENANI, %d)\n", __func__, Params->enANI);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_SCRAMBLEROFF, (uint8_t *)&Params->scramblerOff, sizeof(Params->scramblerOff));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_SCRAMBLEROFF, %d)\n", __func__, Params->scramblerOff);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_SHORTGUARD, (uint8_t *)&Params->shortGuard, sizeof(Params->shortGuard));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_SHORTGUARD, %d)\n", __func__, Params->shortGuard);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_NUMPACKETS, (uint8_t *)&Params->numPackets, sizeof(Params->numPackets));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_NUMPACKETS, %d)\n", __func__, Params->numPackets);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BROADCAST, (uint8_t *)&Params->broadcast, sizeof(Params->broadcast));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_BROADCAST, %d)\n", __func__, Params->broadcast);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BSSID, (uint8_t *)&Params->bssid, sizeof(Params->bssid));

	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXSTATION, (uint8_t *)&Params->txStation, sizeof(Params->txStation));

	addTxParameterIfNeeded(TLV_TXPARM_KEY_RXSTATION, (uint8_t *)&Params->rxStation, sizeof(Params->rxStation));

	addTxParameterIfNeeded(TLV_TXPARM_KEY_TPCM, (uint8_t *)&Params->tpcm, sizeof(Params->tpcm));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_TPCM, %d)\n", __func__, Params->tpcm);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_FLAGS, (uint8_t *)&Params->miscFlags, sizeof(Params->miscFlags));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_FLAGS, %d)\n", __func__, Params->miscFlags);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BANDWIDTH, (uint8_t *)&Params->bandwidth, sizeof(Params->bandwidth));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_BANDWIDTH, %d)\n", __func__, Params->bandwidth);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_WLANMODE, (uint8_t *)&Params->wlanMode, sizeof(Params->wlanMode));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_WLANMODE, %d)\n", __func__, Params->wlanMode);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXMODE, (uint8_t *)&Params->mode, sizeof(Params->mode));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_TXMODE, %d)\n", __func__, Params->mode);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXPATTERN, (uint8_t *)&Params->txPattern, sizeof(Params->txPattern));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_TXPATTERN, %d)\n", __func__, Params->txPattern);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_DUTYCYCLE, (uint8_t *)&Params->dutycycle, sizeof(Params->dutycycle));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_DUTYCYCLE, %d)\n", __func__, Params->dutycycle);
	if (Params->txPattern == USER_DEFINED_PATTERN)
	{
		addTxParameterIfNeeded(TLV_TXPARM_KEY_NPATTERN, (uint8_t *)&Params->nPattern, sizeof(Params->nPattern));
		ALOGE("\n%s() adding command(TLV_TXPARM_KEY_NPATTERN, %d)\n", __func__, Params->nPattern);
		addTxParameterIfNeeded(TLV_TXPARM_KEY_DATAPATTERN, (uint8_t *)&Params->dataPattern, sizeof(Params->dataPattern));

	}
	addTxParameterIfNeeded(TLV_TXPARM_KEY_AIFSN, (uint8_t *)&Params->aifsn, sizeof(Params->aifsn));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_AIFSN, %d)\n", __func__, Params->aifsn);
	addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_RATEBITINDEX0, (uint8_t *)&Params->rateMaskBitPosition,
			sizeof(Params->rateMaskBitPosition)/RATE_POWER_MAX_INDEX, RATE_POWER_MAX_INDEX);

	addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_PKTLEN0, (uint8_t *)&Params->pktLength,
			sizeof(Params->pktLength)/RATE_POWER_MAX_INDEX, RATE_POWER_MAX_INDEX);

	//memset (txChain, 0, sizeof(txChain));
	//for (i = 0; i < MAX_TX_CHAIN; ++i)
	//{
	//	if ((Params->txChain >> i) & 1)
	//	{
	//		txChain[i] = 1;
	//	}
	//}
	//addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_TXCHAIN0, (uint8_t *)txChain, sizeof(txChain)/MAX_TX_CHAIN, MAX_TX_CHAIN);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXCHAIN0, (uint8_t *)&Params->txChain, sizeof(Params->txChain));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_TXCHAIN0, %d)\n", __func__, Params->txChain);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_AGG, (uint8_t *)&Params->agg, sizeof(Params->agg));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_AGG, %d)\n", __func__, Params->agg);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_IR, (uint8_t *)&Params->ir, sizeof(Params->ir));
	ALOGE("\n%s() adding command(TLV_TXPARM_KEY_IR, %d)\n", __func__, Params->ir);
	if (Params->tpcm == TPC_FORCED_GAINIDX)
	{
		if (Params->gainIdx == 0xff)
		{
			Params->gainIdx = 15;
		}
		addTxParameterIfNeeded(TLV_TXPARM_KEY_GAINIDX, (uint8_t *)&Params->gainIdx, sizeof(Params->gainIdx));
		ALOGE("\n%s() adding command(TLV_TXPARM_KEY_GAINIDX, %d)\n", __func__, Params->gainIdx);
		addTxParameterIfNeeded(TLV_TXPARM_KEY_DACGAIN, (uint8_t *)&Params->dacGain, sizeof(Params->dacGain));
		ALOGE("\n%s() adding command(TLV_TXPARM_KEY_DACGAIN, %d)\n", __func__, Params->dacGain);
	}
	else
	{
		addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_TXPOWER0, (uint8_t *)&Params->txPower,
				sizeof(Params->txPower)/RATE_POWER_MAX_INDEX, RATE_POWER_MAX_INDEX);
		ALOGE("\n%s() adding command(TLV_TXPARM_KEY_TXPOWER0, %d)\n",
		__func__, Params->txPower[0]);
	}
	addTxParameterIfNeeded(TLV_TXPARM_KEY_PACONFIG, (uint8_t *)&Params->paConfig, sizeof(Params->paConfig));
}

void addTxParameters2 (uint32_t freq, uint32_t antenna, uint32_t enANI, uint32_t scramblerOff, uint32_t shortGuard,
		uint32_t broadcast, uint8_t *bssid, uint8_t *txStation, uint8_t *rxStation,
		uint32_t tpcm, uint16_t gainIdx, uint16_t dacGain, uint16_t *txPower,
		uint16_t *rateMaskBitPosition, uint32_t txChain, uint32_t agg, uint32_t ir,
		uint32_t miscFlags, uint32_t bandwidth, uint32_t wlanMode, uint32_t mode,
		uint32_t dutycycle, uint32_t aifsn,
		uint32_t txPattern, uint32_t nPattern, uint8_t *dataPattern,
		uint16_t *pktLength, uint32_t numPackets)
{
	addTxParameterIfNeeded(TLV_TXPARM_KEY_CHANNEL, (uint8_t *)&freq, sizeof(freq));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_ANTENNA, (uint8_t *)&antenna, sizeof(antenna));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_ENANI, (uint8_t *)&enANI, sizeof(enANI));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_SCRAMBLEROFF, (uint8_t *)&scramblerOff, sizeof(scramblerOff));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_SHORTGUARD, (uint8_t *)&shortGuard, sizeof(shortGuard));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BROADCAST, (uint8_t *)&broadcast, sizeof(broadcast));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BSSID, bssid, ATH_MAC_LEN);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXSTATION, txStation, ATH_MAC_LEN);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_RXSTATION, rxStation, ATH_MAC_LEN);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TPCM, (uint8_t *)&tpcm, sizeof(tpcm));
	if (tpcm == TPC_FORCED_GAINIDX)
	{
		if (gainIdx == 0xff)
		{
			gainIdx = 15;
		}
		addTxParameterIfNeeded(TLV_TXPARM_KEY_GAINIDX, (uint8_t *)&gainIdx, sizeof(gainIdx));
		addTxParameterIfNeeded(TLV_TXPARM_KEY_DACGAIN, (uint8_t *)&dacGain, sizeof(dacGain));
	}
	else
	{
		addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_TXPOWER0, (uint8_t *)txPower,
				sizeof(uint16_t), RATE_POWER_MAX_INDEX);
	}
	addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_RATEBITINDEX0, (uint8_t *)rateMaskBitPosition,
			sizeof(uint16_t), RATE_POWER_MAX_INDEX);
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXCHAIN0, (uint8_t *)&txChain, sizeof(txChain));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_AGG, (uint8_t *)&agg, sizeof(agg));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_IR, (uint8_t *)&ir, sizeof(ir));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_FLAGS, (uint8_t *)&miscFlags, sizeof(miscFlags));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_BANDWIDTH, (uint8_t *)&bandwidth, sizeof(bandwidth));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_WLANMODE, (uint8_t *)&wlanMode, sizeof(wlanMode));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXMODE, (uint8_t *)&mode, sizeof(mode));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_DUTYCYCLE, (uint8_t *)&dutycycle, sizeof(dutycycle));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_AIFSN, (uint8_t *)&aifsn, sizeof(aifsn));
	addTxParameterIfNeeded(TLV_TXPARM_KEY_TXPATTERN, (uint8_t *)&txPattern, sizeof(txPattern));
	if (txPattern == USER_DEFINED_PATTERN)
	{
		addTxParameterIfNeeded(TLV_TXPARM_KEY_NPATTERN, (uint8_t *)&nPattern, sizeof(nPattern));
		addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_DATAPATTERN, (uint8_t *)dataPattern, sizeof(uint8_t), nPattern);
	}
	addTxParameterSequenceIfNeeded(TLV_TXPARM_KEY_PKTLEN0, (uint8_t *)pktLength,
			sizeof(uint16_t), RATE_POWER_MAX_INDEX);

	addTxParameterIfNeeded(TLV_TXPARM_KEY_NUMPACKETS, (uint8_t *)&numPackets, sizeof(numPackets));
}

void addRxParameterIfNeeded (uint8_t *key, uint8_t *pData, uint32_t size)
{
	addParameterIfNeeded (TlvRxParamDefaultTbl, sizeof(TlvRxParamDefaultTbl)/sizeof(TLV_PARAM_DEFAULT), key, pData, size);
}

void addRxParameterSequenceIfNeeded (uint8_t *firstKey, uint8_t *pData, uint32_t size, uint32_t sequenceSize)
{
	addParameterSequenceIfNeeded (TlvRxParamDefaultTbl, sizeof(TlvRxParamDefaultTbl)/sizeof(TLV_PARAM_DEFAULT), firstKey, pData, size, sequenceSize);
}

void addRxParameters (RX_DATA_START_PARAMS *Params)
{
	uint32_t  value;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_CHANNEL, (uint8_t *)&Params->freq, sizeof(Params->freq));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ANTENNA, (uint8_t *)&Params->antenna, sizeof(Params->antenna));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ENANI, (uint8_t *)&Params->enANI, sizeof(Params->enANI));

	value = (Params->promiscuous) ? TCMD_CONT_RX_PROMIS : TCMD_CONT_RX_FILTER;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_RXMODE, (uint8_t *)&value, sizeof(value));

	addRxParameterIfNeeded(TLV_RXPARM_KEY_WLANMODE, (uint8_t *)&Params->wlanMode, sizeof(Params->wlanMode));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_RXCHAIN, (uint8_t *)&Params->rxChain, sizeof(Params->rxChain));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BROARDCAST, (uint8_t *)&Params->broadcast, sizeof(Params->broadcast));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BANDWIDTH, (uint8_t *)&Params->bandwidth, sizeof(Params->bandwidth));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BSSID, (uint8_t *)&Params->bssid, sizeof(Params->bssid));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ADDR, (uint8_t *)&Params->rxStation, sizeof(Params->rxStation));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_EXPECTEDPACKETS, (uint8_t *)&Params->numPackets, sizeof(Params->numPackets));

	value = RX_STATUS_PER_RATE_MASK | PROCESS_RATE_IN_ORDER_MASK;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_FLAGS, (uint8_t *)&value, sizeof(value));

	addRxParameterSequenceIfNeeded(TLV_RXPARM_KEY_RATEMASK0, (uint8_t *)&Params->rateMask,
			sizeof(Params->rateMask)/RATE_MASK_ROW_MAX, RATE_MASK_ROW_MAX);
}

void addRxParameters2 (uint32_t freq, uint32_t antenna, uint32_t enANI, uint32_t promiscuous,
		uint32_t wlanMode, uint32_t rxChain, uint32_t broadcast,
		uint8_t *bssid, uint8_t *rxStation,
		uint32_t *rateMask, uint32_t bandwidth, uint32_t numPackets)
{
	uint32_t  value;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_CHANNEL, (uint8_t *)&freq, sizeof(freq));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ANTENNA, (uint8_t *)&antenna, sizeof(antenna));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ENANI, (uint8_t *)&enANI, sizeof(enANI));

	value = (promiscuous) ? TCMD_CONT_RX_PROMIS : TCMD_CONT_RX_FILTER;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_RXMODE, (uint8_t *)&value, sizeof(value));

	addRxParameterIfNeeded(TLV_RXPARM_KEY_WLANMODE, (uint8_t *)&wlanMode, sizeof(wlanMode));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_RXCHAIN, (uint8_t *)&rxChain, sizeof(rxChain));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BROARDCAST, (uint8_t *)&broadcast, sizeof(broadcast));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BSSID, bssid, ATH_MAC_LEN);
	addRxParameterIfNeeded(TLV_RXPARM_KEY_ADDR, rxStation, ATH_MAC_LEN);
	addRxParameterIfNeeded(TLV_RXPARM_KEY_BANDWIDTH, (uint8_t *)&bandwidth, sizeof(bandwidth));
	addRxParameterIfNeeded(TLV_RXPARM_KEY_EXPECTEDPACKETS, (uint8_t *)&numPackets, sizeof(numPackets));

	value = RX_STATUS_PER_RATE_MASK | PROCESS_RATE_IN_ORDER_MASK;
	addRxParameterIfNeeded(TLV_RXPARM_KEY_FLAGS, (uint8_t *)&value, sizeof(value));

	addRxParameterSequenceIfNeeded(TLV_RXPARM_KEY_RATEMASK0, (uint8_t *)rateMask,
			sizeof(uint32_t), RATE_MASK_ROW_MAX);
}

