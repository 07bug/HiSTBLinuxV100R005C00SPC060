/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifndef _TLVCMD_IF_H_
#define _TLVCMD_IF_H_

void addTxParameters (TX_DATA_START_PARAMS *Params);
void addTxParameters2 (uint32_t freq, uint32_t antenna, uint32_t enANI, uint32_t scramblerOff, uint32_t shortGuard,
		uint32_t broadcast, uint8_t *bssid, uint8_t *txStation, uint8_t *rxStation,
		uint32_t tpcm, uint16_t gainIdx, uint16_t dacGain, uint16_t *txPower,
		uint16_t *rateMaskBitPosition, uint32_t txChain, uint32_t agg, uint32_t ir,
		uint32_t miscFlags, uint32_t bandwidth, uint32_t wlanMode, uint32_t mode,
		uint32_t dutycycle, uint32_t aifsn,
		uint32_t txPattern, uint32_t nPattern, uint8_t *dataPattern,
		uint16_t *pktLength, uint32_t numPackets);

void addRxParameters (RX_DATA_START_PARAMS *Params);
void addRxParameters2 (uint32_t freq, uint32_t antenna, uint32_t enANI, uint32_t promiscuous,
		uint32_t wlanMode, uint32_t rxChain, uint32_t broadcast,
		uint8_t *bssid, uint8_t *rxStation,
		uint32_t *rateMask, uint32_t bandwidth, uint32_t numPackets);

#endif //_TLVCMD_IF_H_
