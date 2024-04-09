/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if defined(_HOST_SIM_TESTING)
#include "otaHostCommon.h"
#else
#include "osapi.h"
#endif
#include "wlantype.h"
#ifdef USE_GLIB
#include <glib.h>
#define strlcat g_strlcat
#define strlcpy g_strlcpy
#endif

int verifyChecksum(uint16_t* stream, uint32_t len)
{
	uint16_t i,sum=0;
	for (i=0;i<len;i++) { sum ^= *stream++; }
	if (0xffff != sum) return 0;
	return 1;
}

uint16_t computeChecksumOnly(uint16_t *pHalf, uint16_t length)
{
	uint16_t sum = 0, i;
	for (i = 0; i < length; i++) { sum ^= *pHalf++; }
	return(sum);
}

