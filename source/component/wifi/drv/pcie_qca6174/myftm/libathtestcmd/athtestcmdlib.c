/*
 * Copyright (c) 2014-2015 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

/*
 * Copyright (c) 2006 Atheros Communications Inc.
 * All rights reserved.
 *
 *
// The software source and binaries included in this development package are
// licensed, not sold. You, or your company, received the package under one
// or more license agreements. The rights granted to you are specifically
// listed in these license agreement(s). All other rights remain with
// Atheros
// Communications, Inc., its subsidiaries, or the respective owner including
// those listed on the included copyright notices.  Distribution of any
// portion of this package must be in strict compliance with the license
// agreement(s) terms.
// </copyright>
//
// <summary>
// Wifi driver for AR6002
// </summary>
//
 *
 */
/*
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <net/if.h>
#include <linux/wireless.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <setjmp.h>
#include <stdio.h>
#include <time.h>
*/
#include <ctype.h>
#include "art_utf_common.h"

#include "libtcmd.h"
#include "testcmd.h"

#include "cmdAllParms.h"
#include "cmdOpcodes.h"

#include "tcmdHostInternal.h"
#include "maskRateCommon.h"

#include "cmdAllParms.h"
#include "cmdOpcodes.h"
#include "genTxBinCmdTlv.h"
#include "parseRxBinCmdTlv.h"
#include "CliTlvCmd_if.h"

#include "resp_api.h"
#include "testcmd6174.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if defined(ANDROID)
#define ALOGE printf
#include "hex_dump.h"
#else
#define LOG_TAG "testcmd6174"
#define ALOGE printf
//#include <cutils/log.h>
static void print_hex_dump(const unsigned char *array, int len)
{
	int i;
	char buf[1024 * 3];
	char *cp = buf;

	for (i = 0; i < len; i++) {
		cp += snprintf(cp, 3, "%02x ", array[i]);

		if (!((i+1)%16)) {
			ALOGE("%s", &buf[((i/16)*3*16)]);
		}
	}
	ALOGE("%s", &buf[((i/16)*3*16)]);
}
#endif

#ifdef ANDROID
#include <cutils/properties.h>
#endif

#define BIT(n) (1 << (n))

#define DEFAULT_TX_BSSID       "50:55:55:55:55:05"
#define DEFAULT_TX_TXSTATION   "20:22:22:22:22:02"
#define DEFAULT_TX_RXSTATION   "ff:ff:ff:ff:ff:ff"

#define DEFAULT_RX_BSSID       "01:00:00:c0:ff:ee"
#define DEFAULT_RX_ADDR        "01:00:00:c0:ff:ee"

void testcmd_error(int code, const char *fmt, ...);


_CMD_PARM gCmd;

const RATE_STR bgRateStrTbl[G_RATE_NUM] = {
	{ "1   Mb" },
	{ "2   Mb" },
	{ "5.5 Mb" },
	{ "11  Mb" },
	{ "6   Mb" },
	{ "9   Mb" },
	{ "12  Mb" },
	{ "18  Mb" },
	{ "24  Mb" },
	{ "36  Mb" },
	{ "48  Mb" },
	{ "54  Mb" },
	{ "HT20 MCS0 6.5   Mb" },
	{ "HT20 MCS1 13    Mb" },
	{ "HT20 MCS2 19.5  Mb" },
	{ "HT20 MCS3 26    Mb" },
	{ "HT20 MCS4 39    Mb" },
	{ "HT20 MCS5 52    Mb" },
	{ "HT20 MCS6 58.5  Mb" },
	{ "HT20 MCS7 65    Mb" },
	{ "HT20 MCS8 13    Mb" },
	{ "HT20 MCS9 26    Mb" },
	{ "HT20 MCS10 39   Mb" },
	{ "HT20 MCS11 52   Mb" },
	{ "HT20 MCS12 78   Mb" },
	{ "HT20 MCS13 104  Mb" },
	{ "HT20 MCS14 117  Mb" },
	{ "HT20 MCS15 130  Mb" },
	{ "HT20 MCS16 19.5 Mb" },
	{ "HT20 MCS17 39   Mb" },
	{ "HT20 MCS18 58.5 Mb" },
	{ "HT20 MCS19 78   Mb" },
	{ "HT20 MCS20 117  Mb" },
	{ "HT20 MCS21 156  Mb" },
	{ "HT20 MCS22 175.5  Mb" },
	{ "HT20 MCS23 195    Mb" },
	{ "HT40 MCS0 13.5    Mb" },
	{ "HT40 MCS1 27.0    Mb" },
	{ "HT40 MCS2 40.5    Mb" },
	{ "HT40 MCS3 54      Mb" },
	{ "HT40 MCS4 81      Mb" },
	{ "HT40 MCS5 108     Mb" },
	{ "HT40 MCS6 121.5   Mb" },
	{ "HT40 MCS7 135     Mb" },
	{ "HT40 MCS8 27      Mb" },
	{ "HT40 MCS9 54      Mb" },
	{ "HT40 MCS10 81     Mb" },
	{ "HT40 MCS11 108    Mb" },
	{ "HT40 MCS12 162    Mb" },
	{ "HT40 MCS13 216    Mb" },
	{ "HT40 MCS14 243    Mb" },
	{ "HT40 MCS15 270    Mb" },
	{ "HT40 MCS16 40.5   Mb" },
	{ "HT40 MCS17 81     Mb" },
	{ "HT40 MCS18 121.5  Mb" },
	{ "HT40 MCS19 162    Mb" },
	{ "HT40 MCS20 243    Mb" },
	{ "HT40 MCS21 324    Mb" },
	{ "HT40 MCS22 364.5  Mb" },
	{ "HT40 MCS23 405    Mb" },
	{ "VHT20 MCS0 S1 6.5 Mb" }, //60
	{ "VHT20 MCS1 S1 13 Mb" },
	{ "VHT20 MCS2 S1 19.5 Mb" },
	{ "VHT20 MCS3 S1 26 Mb" }, //63
	{ "VHT20 MCS4 S1 39 Mb" },
	{ "VHT20 MCS5 S1 52 Mb" },
	{ "VHT20 MCS6 S1 58.5 Mb" },
	{ "VHT20 MCS7 S1 65 Mb" },
	{ "VHT20 MCS8 S1 78 Mb" },
	{ "VHT20 MCS9 S1 86 Mb" },
	{ "VHT20 MCS0 S2 13 Mb" },
	{ "VHT20 MCS1 S2 26 Mb" },
	{ "VHT20 MCS2 S2 39 Mb" },
	{ "VHT20 MCS3 S2 52 Mb" },
	{ "VHT20 MCS4 S2 78 Mb" },
	{ "VHT20 MCS5 S2 104 Mb" },
	{ "VHT20 MCS6 S2 117 Mb" },
	{ "VHT20 MCS7 S2 130 Mb" },
	{ "VHT20 MCS8 S2 156 Mb" },
	{ "VHT20 MCS9 S2 173" },
	{ "VHT20 MCS0 S3 19.5 Mb" },
	{ "VHT20 MCS1 S3 39 Mb" },
	{ "VHT20 MCS2 S3 58.5 Mb" },
	{ "VHT20 MCS3 S3 78 Mb" },
	{ "VHT20 MCS4 S3 117 Mb" },
	{ "VHT20 MCS5 S3 156 Mb" },
	{ "VHT20 MCS6 S3 175.5 Mb" },
	{ "VHT20 MCS7 S3 195 Mb" },
	{ "VHT20 MCS8 S3 234 Mb" },
	{ "VHT20 MCS9 S3 260 Mb" },
	{ "VHT40 MCS0 S1 13.5 Mb" },
	{ "VHT40 MCS1 S1 27 Mb" },
	{ "VHT40 MCS2 S1 40.5 Mb" },
	{ "VHT40 MCS3 S1 54 Mb" },
	{ "VHT40 MCS4 S1 81 Mb" },
	{ "VHT40 MCS5 S1 108 Mb" },
	{ "VHT40 MCS6 S1 121.5 Mb" },
	{ "VHT40 MCS7 S1 135 Mb" },
	{ "VHT40 MCS8 S1 162 Mb" },
	{ "VHT40 MCS9 S1 180 Mb" },
	{ "VHT40 MCS0 S2 27 Mb" },
	{ "VHT40 MCS1 S2 54 Mb" },
	{ "VHT40 MCS2 S2 81 Mb" },
	{ "VHT40 MCS3 S2 108 Mb" },
	{ "VHT40 MCS4 S2 162 Mb" },
	{ "VHT40 MCS5 S2 216 Mb" },
	{ "VHT40 MCS6 S2 243 Mb" },
	{ "VHT40 MCS7 S2 270 Mb" },
	{ "VHT40 MCS8 S2 324 Mb" },
	{ "VHT40 MCS9 S2 360 Mb" },
	{ "VHT40 MCS0 S3 40.5 Mb" },
	{ "VHT40 MCS1 S3 81 Mb" },
	{ "VHT40 MCS2 S3 121.5 Mb" },
	{ "VHT40 MCS3 S3 162 Mb" },
	{ "VHT40 MCS4 S3 243 Mb" },
	{ "VHT40 MCS5 S3 324 Mb" },
	{ "VHT40 MCS6 S3 364.5 Mb" },
	{ "VHT40 MCS7 S3 405 Mb" },
	{ "VHT40 MCS8 S3 486 Mb" },
	{ "VHT40 MCS9 S3 540 Mb" },
	{ "VHT80 MCS0 S1 29.3 Mb" },
	{ "VHT80 MCS1 S1 58.5 Mb" },
	{ "VHT80 MCS2 S1 87.8 Mb" },
	{ "VHT80 MCS3 S1 117 Mb" },
	{ "VHT80 MCS4 S1 175.5 Mb" },
	{ "VHT80 MCS5 S1 234 Mb" },
	{ "VHT80 MCS6 S1 263.3 Mb" },
	{ "VHT80 MCS7 S1 292.5 Mb" },
	{ "VHT80 MCS8 S1 351 Mb" },
	{ "VHT80 MCS9 S1 390 Mb" },
	{ "VHT80 MCS0 S2 58.5 Mb" },
	{ "VHT80 MCS1 S2 117 Mb" },
	{ "VHT80 MCS2 S2 175.5 Mb" },
	{ "VHT80 MCS3 S2 234 Mb" },
	{ "VHT80 MCS4 S2 351 Mb" },
	{ "VHT80 MCS5 S2 468 Mb" },
	{ "VHT80 MCS6 S2 526.5 Mb" },
	{ "VHT80 MCS7 S2 585 Mb" },
	{ "VHT80 MCS8 S2 702 Mb" },
	{ "VHT80 MCS9 S2 780 Mb" },
	{ "VHT80 MCS0 S3 87.8 Mb" },
	{ "VHT80 MCS1 S3 175.5 Mb" },
	{ "VHT80 MCS2 S3 263.3 Mb" },
	{ "VHT80 MCS3 S3 351 Mb" },
	{ "VHT80 MCS4 S3 526.5 Mb" },
	{ "VHT80 MCS5 S3 702 Mb" },
	{ "VHT80 MCS6 S3 789.8 Mb" },
	{ "VHT80 MCS7 S3 877.5 Mb" },
	{ "VHT80 MCS8 S3 1053 Mb" },
	{ "VHT80 MCS9 S3 1170 Mb" },
	/* below portion(CCK short preamble rates) should always be placed to the end */
	{ "2(S)   Mb" },
	{ "5.5(S) Mb" },
	{ "11(S)  Mb" }
};

int g_tx_init = false;

/*------------------------------------------------------------------*/
/*
 * Input an Ethernet address and convert to binary.
 */
static int ath_ether_aton(const char *orig, uint8_t *eth)
{
	int mac[6];
	if (sscanf(orig, "%02x:%02x:%02X:%02X:%02X:%02X",
				&mac[0], &mac[1], &mac[2],
				&mac[3], &mac[4], &mac[5])==6) {
		int i;
#ifdef TCMD_LIB_DEBUG
		if (*(orig+12+5) !=0) {
			fprintf(stderr, "%s: trailing junk '%s'!\n", __func__, orig);
			testcmd_error(-1, "trailing junk");
			return -1;
		}
#endif
		for (i=0; i<6; ++i)
			eth[i] = mac[i] & 0xff;
		return 0;
	}
	else {
		testcmd_error(-1, "Invalid mac address format");
	}

	return -1;
}

static inline int is_zero_ether_addr(const uint8_t *a)
{
	return !(a[0] | a[1] | a[2] | a[3] | a[4] | a[5]);
}

static inline int is_broadcast_ether_addr(const uint8_t *a)
{
	return (a[0] & a[1] & a[2] & a[3] & a[4] & a[5]) == 0xff;
}

uint32_t channel_to_freq(uint32_t channel)
{
	if (channel >= 1 && channel <= 13)
		return 2407 + 5 * channel;
	else if (channel == 14)
		return 2484 + 5;
	else
		return 5000 + 5 * channel;
}

uint32_t freq_to_channel(unsigned int freq)
{
	if (freq >= 2412 && freq <= 2472)
		return (freq - 2407) / 5;
	else if (freq == 2484)
		return 14;
	else if (freq >= 5180 && freq <= 5240)
		return (freq - 5000) / 5;
	else
		return 0;
}

static void getIfName(char *ifname)
{
#ifdef ANDROID
	char ifprop[PROPERTY_VALUE_MAX];
#endif
	char *src;
	char defIfname[IFNAMSIZ];
	char linebuf[1024];
	FILE *f = fopen("/proc/net/wireless", "r");
	if (f) {
		while (fgets(linebuf, sizeof(linebuf)-1, f)) {
			if (strchr(linebuf, ':')) {
				char *dest = defIfname;
				char *p = linebuf;
				while (*p && isspace(*p)) ++p;
				while (*p && *p != ':')
					*dest++ = *p++;
				*dest = '\0';
				break;
			}
		}
		fclose(f);
	} else {
		defIfname[0] = '\0';
	}

	src = defIfname;
#ifdef ANDROID
	if (property_get("wifi.interface", ifprop, defIfname)) {
		src = ifprop;
	}
#endif
	memcpy(ifname, src, IFNAMSIZ);
}

static int isResponseNeeded(void *buf)
{
	int respNeeded = 0;
	TCMD_ID tcmd = TCMD_CONT_RX_ID;
	uint32_t mode = 0;

	tcmd = * ((uint32_t *) buf);
	mode = * ((uint32_t *) buf + 1);

	/// Insert commands which need response
	switch (tcmd)
	{
		case TC_CMD_TLV_ID:
			respNeeded = 1;
			break;
		case TCMD_CONT_RX_ID:
			switch (mode)
			{
				case TCMD_CONT_RX_REPORT:
				case TCMD_CONT_RX_GETMAC:
					respNeeded = 1;
					break;
			}
			break;
		case TC_CMDS_ID:
			switch (mode)
			{
				case TC_CMDS_READTHERMAL:
				case TC_CMDS_EFUSEDUMP:
				case TC_CMDS_EFUSEWRITE:
				case TC_CMDS_OTPSTREAMWRITE:
				case TC_CMDS_OTPDUMP:
					respNeeded = 1; //TC_CMDS_EFUSEDUMP, TC_CMDS_EFUSEWRITE, TC_CMDS_OTPSTREAMWRITE, TC_CMDS_OTPDUMP, TC_CMDS_READTHERMAL
					break;
			}
			break;
		default:
			break;
	}

	if (respNeeded)
	{
		ALOGE("cmdID %d response needed\n", tcmd);
	}
	else
	{
		ALOGE("cmdID %d response not needed\n", tcmd);
	}

	return respNeeded;
}

void parseGenericResponse(void)
{
	int ret = TRUE;
	uint8_t *data;
	uint32_t status,len;

	ret = getParams((uint8_t*)"status", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&status,data,len);
		ALOGE("Response status %d\n",status);
	}
	else
		printf("In parseResponse status not found\n");
}

/* need to verify */
void parseTLVSubmitReport(void)
{
	int ret = TRUE;
	uint8_t *data;
	uint32_t value,totalpkt,len,i,k;
	int32_t rssi;
	uint8_t rateCntBuf[25];
	uint32_t rateMask,rateMaskCnt[2],shortGuard,dataRate,index=0;
	uint32_t rate11ACMaskCnt[4];
	uint32_t bit0 = 0x00000001;

	ret = getParams((uint8_t*)"totalpkt", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&totalpkt,data,len);
		printf("totalpkt %d\n",totalpkt);
	}

	ret = getParams((uint8_t*)"rssiInDBm", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&rssi,data,len);

		if(totalpkt)
			printf("rssiInDBm %d\n",rssi/(int32_t)totalpkt);
		else
			printf("rssiInDBm %d\n",rssi);
	}

	ret = getParams((uint8_t*)"crcErrPkt", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&value,data,len);
		printf("crcErrPkt %d\n",value);
	}

	ret = getParams((uint8_t*)"secErrPkt", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&value,data,len);
		printf("secErrPkt %d\n",value);
	}

	for(i=0;i<2;i++)
	{
		memset(rateCntBuf,0,sizeof(rateCntBuf));
		snprintf((char*)rateCntBuf,25,"%s%d","rcMask",i);
		ret = getParams((uint8_t*)rateCntBuf,&data,&len);

		if ( ret == TRUE )
		{
			memcpy(&rateMaskCnt[i],data,len);
			//printf("%s %x\n",rateCntBuf,rateMaskCnt[i]);
		}
		else
		{
			rateMaskCnt[i] = 0;
		}
	}

	for(i=0;i<4;i++)
	{
		memset(rateCntBuf,0,sizeof(rateCntBuf));
		snprintf((char*)rateCntBuf,25,"%s%d","rcMask11ac",i);
		ret = getParams((uint8_t*)rateCntBuf,&data,&len);

		if ( ret == TRUE )
		{
			memcpy(&rate11ACMaskCnt[i],data,len);
			//printf("%s %x\n",rateCntBuf,rate11ACMaskCnt[i]);
		}
		else
		{
			rate11ACMaskCnt[i] = 0;
		}
	}

	ret = getParams((uint8_t*)"shortGuard", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&shortGuard,data,len);

		if ( shortGuard )
			printf("<<<<SGI set >>>>\n");
	}

	//11n and below rates..
	for (k=0;k<2;k++)
	{
		rateMask = rateMaskCnt[k];
		i=0; bit0=0x00000001;
		while (rateMask)
		{
			if (bit0 & rateMask)
			{
				rateMask &= ~bit0;
				dataRate = Mask2Rate[k][i];

				if (dataRate == ATH_RATE_2M || dataRate == ATH_RATE_5_5M || dataRate == ATH_RATE_11M){ /* CCK rates */
					if (!(i&1)) /* even number indicates short preamble, see Mask2Rate array for details */
						dataRate += (TCMD_MAX_RATES - 4);/* use last three rates in the rate table for shortPreamble */
				}

				//printf("RateCnt bit set %d dataRate %d %s\n",(k*32+i),dataRate,bgRateStrTbl[dataRate]);
				printf("%s .. ", bgRateStrTbl[dataRate]);

				index = (k*32+i)/2;

				memset(rateCntBuf,0,sizeof(rateCntBuf));
				snprintf((char*)rateCntBuf,25,"%s%d","rateCnt",index);
				ret = getParams((uint8_t*)rateCntBuf,&data,&len);

				if ( ret == TRUE )
				{
					memcpy(&value,data,len);

					if (i && !(i&1))
						printf("rateCnt %d\n",(value & 0xFFFF));
					else {
						if (i && (i&1)) {
							printf("rateCnt %d\n",(value >>16) & 0xFFFF);
						}
						else{
							printf("rateCnt %d\n",(value & 0xFFFF));
						}
					}
				}
				else {
					printf("rateCnt ..%d\n",0);
				}
			}

			bit0 = bit0 << 1;i++;
		}
	}

	//11ac rates..
	for (k=0;k<4;k++)
	{
		rateMask = rate11ACMaskCnt[k];
		i=0; bit0=0x00000001;
		while (rateMask)
		{
			if (bit0 & rateMask)
			{
				rateMask &= ~bit0;
				index = k + 2;
				dataRate = Mask2Rate[index][i];
				//printf("11ac RateCnt bit set %d dataRate %d %s\n",(k*32+i),dataRate,bgRateStrTbl[dataRate]);
				printf("%s .. ",bgRateStrTbl[dataRate]);

				index = (k*32+i)/2;

				memset(rateCntBuf,0,sizeof(rateCntBuf));
				snprintf((char*)rateCntBuf,25,"%s%d","rateCnt11ac",index);
				ret = getParams((uint8_t*)rateCntBuf,&data,&len);

				if ( ret == TRUE )
				{
					memcpy(&value,data,len);

					if (i && !(i&1))
						printf("rateCnt %d\n",(value & 0xFFFF));
					else {
						if (i && (i&1)) {
							printf("rateCnt %d\n",(value >>16) & 0xFFFF);
						}
						else{
							printf("rateCnt %d\n",(value & 0xFFFF));
						}
					}
				}
			}

			bit0 = bit0 << 1;i++;
		}
	}
}

/* need to verify */
void parseResNart(void)
{
	int ret = TRUE;
	uint8_t *data;
	uint32_t status, commandId, len;
	uint8_t  buf[512];
	uint32_t i;

	ret = getParams((uint8_t*)"commandId", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&commandId,data,len);
		printf("Response commandId %d, len %d\n",commandId, len);
	}
	else
		printf("In parseResNart commandId not found\n");

	ret = getParams((uint8_t*)"status", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(&status,data,len);
		printf("Response status %d\n",status);
	}
	else
		printf("In parseResNart status not found\n");

	ret = getParams((uint8_t*)"data", &data, &len);

	if ( ret == TRUE )
	{
		memcpy(buf,data,len);
		printf("Response buf len %d\n",len);
		for (i = 0; i <len; i++) {
			printf("0x%2x ",buf[i]);
			if (((i+1)%16) == 0) printf("\n");
		}
		printf("\n");
	}
	else
		printf("In parseResNart buf not found\n");

}

/* need to verify */
void parseResTxStatus(void)
{
	int ret = TRUE;
	uint8_t *data;
	uint32_t pdadc, paCfg, len;
	int32_t  gainIdx, dacGain;
	uint32_t thermCal;
	//    uint8_t  buf[512];
	//    uint32_t i;
	ret = getParams((uint8_t*)"thermCal", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&thermCal,data,len);
		printf("Response thermCal0 %d, lthermCal1 %d, len %d\n", thermCal&0xff, (thermCal)>>8, len);
	}
	else
		printf("In parseResTxStatus thermal not found\n");

	ret = getParams((uint8_t*)"pdadc", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&pdadc,data,len);
		printf("Response pdadc0 %d, pdadc1 %d len %d\n", pdadc&0xff, (pdadc)>>8 , len);
	}
	else
		printf("In parseResTxStatus pdadc not found\n");

	ret = getParams((uint8_t*)"paCfg", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&paCfg,data,len);
		printf("Response paCfg %d, len %d\n", paCfg, len);
	}
	else
		printf("In parseResTxStatus paCfg not found\n");

	ret = getParams((uint8_t*)"gainIdx", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&gainIdx,data,len);
		printf("Response gainIdx %d, len %d\n", gainIdx, len);
	}
	else
		printf("In parseResTxStatus gainIdx not found\n");

	ret = getParams((uint8_t*)"dacGain", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&dacGain,data,len);
		printf("Response dacGain %d, len %d\n", dacGain, len);
	}
	else
		printf("In parseResTxStatus dacGain not found\n");

}

void parseResRxStatus(void)
{
	int ret = TRUE;
	uint8_t *data;
	uint32_t len;
	uint32_t totalPackets, goodPackets;
	uint32_t otherError, crcPackets;
	int32_t rssi;
	int32_t evm0;

	ret = getParams((uint8_t*)"totalPackets", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&totalPackets,data,len);
		printf("Response totalPackets %d\n", totalPackets);
	}
	else
		printf("In %s totalPackets not found\n", __func__);

	ret = getParams((uint8_t*)"goodPackets", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&goodPackets,data,len);
		printf("Response goodPackets %d\n", goodPackets);
	}
	else
		printf("In %s goodPackets not found\n", __func__);

	ret = getParams((uint8_t*)"otherError", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&otherError,data,len);
		printf("Response otherError %d\n", otherError);
	}
	else
		printf("In %s otherError not found\n", __func__);

	ret = getParams((uint8_t*)"crcPackets", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&crcPackets,data,len);
		printf("Response crcPackets %d\n", crcPackets);
	}
	else
		printf("In %s crcPackets not found\n", __func__);

	ret = getParams((uint8_t*)"rssi", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&rssi,data,len);
		printf("Response rssi %d\n", rssi);
	}
	else
		printf("In %s rssi not found\n", __func__);

	ret = getParams((uint8_t*)"evm0", &data, &len);
	if ( ret == TRUE )
	{
		memcpy(&evm0,data,len);
		printf("Response evm0 %d\n", evm0);
	}
	else
		printf("In %s evm0 not found\n", __func__);

#if 0 /* 20140311 Matt */
	gCmd.rxPkt = totalPackets;
#else
	gCmd.rxPkt = totalPackets - crcPackets; /* Rx packet should be a good packet */
#endif /* 20140311 Matt */
	gCmd.rxRssi = rssi;
	gCmd.rxCrcError = crcPackets;
	gCmd.rxSecError = 0;

	ALOGE("====RX report====");
	ALOGE("gCmd.rxPkt      = %d", gCmd.rxPkt);
	ALOGE("gCmd.rxRssi     = %d", gCmd.rxRssi);
	ALOGE("gCmd.rxCrcError = %d", gCmd.rxCrcError);
	ALOGE("gCmd.rxSecError = %d", gCmd.rxSecError);
}

void parseResponse(void *buf, int len)
{
	uint8_t *reply = (uint8_t*)buf;
	uint8_t responseOpCode = _OP_GENERIC_RSP;
	int ret = FALSE;

	addParameterToCommandWithRawdata(buf, len, 1);

	ALOGE("%s() TLV length got %d\n", __func__, len);
	print_hex_dump(buf, len);

	ret = initResponse((uint8_t*)&reply[0], len, &responseOpCode);

	if ( ret == FALSE )
	{
		printf("Error in init Response\n");
		return;
	}

	ALOGE("response code got %d\n", responseOpCode);

	if ( responseOpCode == _OP_SUBMIT_REPORT_RSP )
		parseTLVSubmitReport();
	else if ( responseOpCode == _OP_GENERIC_RSP )
		parseGenericResponse();
	else if ( responseOpCode == _OP_GENERIC_NART_RSP )
		parseResNart();
	else if ( responseOpCode == _OP_TX_STATUS )
		parseResTxStatus();
	else if ( responseOpCode == _OP_RX_STATUS )
		parseResRxStatus();
	else {
		testcmd_error(-1, "Nothing to do with this response\n");
	}

	return;
}

static int doCommand(uint8_t *rCmdStream, uint32_t cmdStreamLen)
{
	int resp = 0;
	char ifname[IFNAMSIZ];

	getIfName(ifname);

	gCmd.errCode = 0;
	gCmd.errString[0] = '\0';
	ALOGE("%s() cmdStreamLen %d\n", __func__, cmdStreamLen);

	if (g_tx_init == false) {
		if (tcmd_tx_init(ifname, parseResponse)) {
			testcmd_error(-1, "fail to tx_init");
			return -1;
		}
		g_tx_init = true;
	}

	resp = isResponseNeeded( (void*)rCmdStream);

	if (tcmd_tx(rCmdStream, cmdStreamLen, resp))
	{
		testcmd_error(-1, "fail to tcmd_tx");
		return -1;
	}

	return 0;
}

int getOffsetFromBitmap(int bitmap) {
	int i;
	for (i=0; i<32; i++) {
		if (bitmap == BIT(i))
			return i;
	}
	return -1;
}

int getMcsDataRate(int wlanMode)
{
	int dataRate;
	int rateOffset = 0;

#define INDEX_OF_MCS0			15
	switch (wlanMode)
	{
		case TCMD_WLAN_MODE_HT20 :
			rateOffset = ATH_RATE_6_5M;
			break;
		case TCMD_WLAN_MODE_HT40PLUS :
		case TCMD_WLAN_MODE_HT40MINUS :
			rateOffset = ATH_RATE_HT40_13_5M;
			break;
		case TCMD_WLAN_MODE_VHT20 :
			if (gCmd.chain == 1 || gCmd.chain == 2)
				rateOffset = ATH_RATE_VHT20_NSS1_MCS0;
			else
				rateOffset = ATH_RATE_VHT20_NSS2_MCS0;
			break;
		case TCMD_WLAN_MODE_VHT40PLUS :
		case TCMD_WLAN_MODE_VHT40MINUS :
			if (gCmd.chain == 1 || gCmd.chain == 2)
				rateOffset = ATH_RATE_VHT40_NSS1_MCS0;
			else
				rateOffset = ATH_RATE_VHT40_NSS2_MCS0;
			break;
		case TCMD_WLAN_MODE_VHT80_0 :
		case TCMD_WLAN_MODE_VHT80_1 :
		case TCMD_WLAN_MODE_VHT80_2 :
		case TCMD_WLAN_MODE_VHT80_3 :
			if (gCmd.chain == 1 || gCmd.chain == 2)
				rateOffset = ATH_RATE_VHT80_NSS1_MCS0;
			else
				rateOffset = ATH_RATE_VHT80_NSS2_MCS0;
			break;
		default :
			ALOGE("Wrong wlanMode %d value", wlanMode);
			break;
	}

	dataRate = rateOffset + gCmd.rate - INDEX_OF_MCS0;

	return dataRate;
}

int getMcsWlanMode(void)
{
	int wlanMode = 0;

	if (gCmd.wmode != TCMD_WLAN_MODE_MAX)
		return gCmd.wmode;

	switch (gCmd.bandWidth)
	{
		case 0:
			wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 1 :
			wlanMode = TCMD_WLAN_MODE_HT20;
			break;
		case 2 :
			wlanMode = TCMD_WLAN_MODE_HT40PLUS;
			break;
		case 3 :
			wlanMode = TCMD_WLAN_MODE_VHT80_0;
			break;
		case 4 :
			wlanMode = TCMD_WLAN_MODE_VHT20;
			break;
		case 5 :
			wlanMode = TCMD_WLAN_MODE_VHT40PLUS;
			break;
		default :
			ALOGE("Wrong bandwidth %d value", gCmd.bandWidth);
			break;
	}
	return wlanMode;
}

void getDataRateAndWlanMode(uint32_t *dataRate, uint32_t *wlanMode)
{
	switch (gCmd.rate)
	{
		// CCK
		case 1 : // 1Mbps
			*dataRate = ATH_RATE_1M;
			*wlanMode = TCMD_WLAN_MODE_CCK;
			break;
		case 2 : // 2Mbps
			*dataRate = ATH_RATE_2M;
			if (!gCmd.longpreamble)
				*dataRate += (TCMD_MAX_RATES - 4);/* use last three rates in the rate table for shortPreamble */
			*wlanMode = TCMD_WLAN_MODE_CCK;
			break;
		case 3 : // 5.5Mbps
			*dataRate = ATH_RATE_5_5M;
			if (!gCmd.longpreamble)
				*dataRate += (TCMD_MAX_RATES - 4);/* use last three rates in the rate table for shortPreamble */
			*wlanMode = TCMD_WLAN_MODE_CCK;
			break;
		case 6 : // 11Mbps
			*dataRate = ATH_RATE_11M;
			if (!gCmd.longpreamble)
				*dataRate += (TCMD_MAX_RATES - 4);/* use last three rates in the rate table for shortPreamble */
			*wlanMode = TCMD_WLAN_MODE_CCK;
			break;

		// NOHT
		case 4 : // 6Mbps
			*dataRate = ATH_RATE_6M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 5 : // 9Mbps
			*dataRate = ATH_RATE_9M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 7 : // 12Mbps
			*dataRate = ATH_RATE_12M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 8 : // 18Mbps
			*dataRate = ATH_RATE_18M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 10 : // 24Mbps
			*dataRate = ATH_RATE_24M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 12 : // 36Mbps
			*dataRate = ATH_RATE_36M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 13 : // 48Mbps
			*dataRate = ATH_RATE_48M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;
		case 14 : // 54Mbps
			*dataRate = ATH_RATE_54M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
			break;

		// MCS 0~9
		case 15 : // MCS0
		case 16 : // MCS1
		case 17 : // MCS2
		case 18 : // MCS3
		case 19 : // MCS4
		case 20 : // MCS5
		case 21 : // MCS6
		case 22 : // MCS7
		case 23 : // MCS8
		case 24 : // MCS9
		case 25 : // MCS10
		case 26 : // MCS11
		case 27 : // MCS12
		case 28 : // MCS13
		case 29 : // MCS14
		case 30 : // MCS15
			*wlanMode = getMcsWlanMode();
			*dataRate = getMcsDataRate(*wlanMode);
			break;
		default:
			//  0: not used
			//  9: 22Mbps (not supported)
			// 11: 33Mbps (not supported)
#if 1 /* Use 54Mbps for default since Agilent N4010 doesn't support Rate Set command for Rx start */
			*dataRate = ATH_RATE_54M;
			*wlanMode = TCMD_WLAN_MODE_NOHT;
#endif
			break;
	}

	return;
}

int findCenterFreq(int wlanMode)
{
	int freq = 0;
	switch (wlanMode)
	{
		case TCMD_WLAN_MODE_NOHT:
		case TCMD_WLAN_MODE_HT20:
		case TCMD_WLAN_MODE_CCK:
		case TCMD_WLAN_MODE_VHT20:
			freq = gCmd.freq;
			ALOGE("%s() no need to switch to bonding channel", __func__);
			break;
		case TCMD_WLAN_MODE_HT40PLUS:
		case TCMD_WLAN_MODE_HT40MINUS:
		case TCMD_WLAN_MODE_VHT40PLUS:
		case TCMD_WLAN_MODE_VHT40MINUS:
			if (gCmd.freq == 5180 || gCmd.freq == 5200) {
				freq = 5190;
			} else if (gCmd.freq == 5220 || gCmd.freq == 5240) {
				freq = 5230;
			} else if (gCmd.freq == 5260 || gCmd.freq == 5280) {
				freq = 5270;
			} else if (gCmd.freq == 5300 || gCmd.freq == 5320) {
				freq = 5310;
			} else if (gCmd.freq == 5500 || gCmd.freq == 5520) {
				freq = 5510;
			} else if (gCmd.freq == 5540 || gCmd.freq == 5560) {
				freq = 5550;
			} else if (gCmd.freq == 5580 || gCmd.freq == 5600) {
				freq = 5590;
			} else if (gCmd.freq == 5620 || gCmd.freq == 5640) {
				freq = 5630;
			} else if (gCmd.freq == 5660 || gCmd.freq == 5680) {
				freq = 5670;
			} else if (gCmd.freq == 5700 || gCmd.freq == 5720) {
				freq = 5710;
			} else if (gCmd.freq == 5745 || gCmd.freq == 5765) {
				freq = 5755;
			} else if (gCmd.freq == 5785 || gCmd.freq == 5805) {
				freq = 5795;
			} else {
				ALOGE("%s() freq %d doesn't in wlan mode %d.", __func__, gCmd.freq, wlanMode);
				freq = gCmd.freq;
				break;
			}
			ALOGE("%s() changed freq from %d to %d", __func__, gCmd.freq, freq);
			break;
		case TCMD_WLAN_MODE_VHT80_0:
		case TCMD_WLAN_MODE_VHT80_1:
		case TCMD_WLAN_MODE_VHT80_2:
		case TCMD_WLAN_MODE_VHT80_3:
			if (gCmd.freq == 5180 || gCmd.freq == 5200 || gCmd.freq == 5220 || gCmd.freq == 5240) {
				freq = 5210;
			} else if (gCmd.freq == 5260 || gCmd.freq == 5280 || gCmd.freq == 5300 || gCmd.freq == 5320) {
				freq = 5290;
			} else if (gCmd.freq == 5500 || gCmd.freq == 5520 || gCmd.freq == 5540 || gCmd.freq == 5560) {
				freq = 5530;
			} else if (gCmd.freq == 5580 || gCmd.freq == 5600 || gCmd.freq == 5620 || gCmd.freq == 5640) {
				freq = 5610;
			} else if (gCmd.freq == 5660 || gCmd.freq == 5680 || gCmd.freq == 5700 || gCmd.freq == 5720) {
				freq = 5690;
			} else if (gCmd.freq == 5745 || gCmd.freq == 5765 || gCmd.freq == 5785 || gCmd.freq == 5805) {
				freq = 5775;
			} else {
				ALOGE("%s() freq %d doesn't in wlan mode %d.", __func__, gCmd.freq, wlanMode);
				freq = gCmd.freq;
				break;
			}
			ALOGE("%s() changed freq from %d to %d", __func__, gCmd.freq, freq);
			break;
		default:
			freq = gCmd.freq;
			ALOGE("%s() wlanMode %d is not supported!!", __func__, wlanMode);
			break;
	}
	return freq;
}

void rateIndexToArrayMapping(uint32_t rateIndex, uint32_t *rowIndex, uint32_t *bitmask, int *is11AcRate )
{
	*is11AcRate = FALSE;

	if ((rateIndex == 150) || (rateIndex==151) || (rateIndex==152) ) {
		*is11AcRate = FALSE;
	}
	else if (rateIndex >= 60)
		*is11AcRate = TRUE;
#ifdef TCMD_LIB_DEBUG
	printf("%d %s Is11AcRate %d\n", rateIndex, bgRateStrTbl[rateIndex], *is11AcRate);
#endif
	ALOGE("%s() %d %s Is11AcRate %d\n", __func__, rateIndex, bgRateStrTbl[rateIndex], *is11AcRate);
	switch(rateIndex)
	{
		case 0: // 1 Mb
			*rowIndex = 0;
			*bitmask = 0x00000001; // set Bit 0
			break;
		case 1: // 2 Mb Long CCK
			*rowIndex = 0;
			*bitmask = 0x00000002; // set Bit 1
			break;
		case 150: // 2 Mb Short CCK
			*rowIndex = 0;
			*bitmask = 0x00000004; // set Bit 2 (SHORT CCK)
			break;
		case 2: // 5.5 Mb Long CCK
			*rowIndex = 0;
			*bitmask = 0x00000008; // set Bit 3
			break;
		case 151: // 5.5 Mb Short CCK
			*rowIndex = 0;
			*bitmask = 0x00000010; // set Bit 4 (SHORT CCK)
			break;
		case 3: // 11 Mb Long CCK
			*rowIndex = 0;
			*bitmask = 0x00000020; // set Bit 5
			break;
		case 152: // 11 Mb Short CCK
			*rowIndex = 0;
			*bitmask = 0x00000040; // set Bit 6 (SHORT CCK)
			break;

		case 4: // 6 Mb
			*rowIndex = 0;
			*bitmask = 0x00000100;
			break;
		case 5: // 9 Mb
			*rowIndex = 0;
			*bitmask = 0x00000200;
			break;
		case 6: // 12 Mb
			*rowIndex = 0;
			*bitmask = 0x00000400;
			break;
		case 7: // 18 Mb
			*rowIndex = 0;
			*bitmask = 0x00000800;
			break;
		case 8: // 24 Mb
			*rowIndex = 0;
			*bitmask = 0x00001000;
			break;
		case 9: // 36 Mb
			*rowIndex = 0;
			*bitmask = 0x00002000;
			break;
		case 10: // 48 Mb
			*rowIndex = 0;
			*bitmask = 0x00004000;
			break;
		case 11: // 54 Mb
			*rowIndex = 0;
			*bitmask = 0x00008000;
			break;

		case 12: // HT20 MCS0
			*rowIndex = 0;
			*bitmask = 0x00010000;
			break;
		case 13: // HT20 MCS1
			*rowIndex = 0;
			*bitmask = 0x00020000;
			break;
		case 14: // HT20 MCS2
			*rowIndex = 0;
			*bitmask = 0x00040000;
			break;
		case 15: // HT20 MCS3
			*rowIndex = 0;
			*bitmask = 0x00080000;
			break;
		case 16: // HT20 MCS4
			*rowIndex = 0;
			*bitmask = 0x00100000;
			break;
		case 17: // HT20 MCS5
			*rowIndex = 0;
			*bitmask = 0x00200000;
			break;
		case 18: // HT20 MCS6
			*rowIndex = 0;
			*bitmask = 0x00400000;
			break;
		case 19: // HT20 MCS7
			*rowIndex = 0;
			*bitmask = 0x00800000;
			break;

		case 20: // HT20 MCS8
			*rowIndex = 1;
			*bitmask = 0x00000001;
			break;
		case 21: // HT20 MCS9
			*rowIndex = 1;
			*bitmask = 0x00000002;
			break;
		case 22: // HT20 MCS10
			*rowIndex = 1;
			*bitmask = 0x00000004;
			break;
		case 23: // HT20 MCS11
			*rowIndex = 1;
			*bitmask = 0x00000008;
			break;
		case 24: // HT20 MCS12
			*rowIndex = 1;
			*bitmask = 0x00000010;
			break;
		case 25: // HT20 MCS13
			*rowIndex = 1;
			*bitmask = 0x00000020;
			break;
		case 26: // HT20 MCS14
			*rowIndex = 1;
			*bitmask = 0x00000040;
			break;
		case 27: // HT20 MCS15
			*rowIndex = 1;
			*bitmask = 0x00000080;
			break;

		case 28: // HT20 MCS16
			*rowIndex = 1;
			*bitmask = 0x00010000;
			break;
		case 29: // HT20 MCS17
			*rowIndex = 1;
			*bitmask = 0x00020000;
			break;
		case 30: // HT20 MCS18
			*rowIndex = 1;
			*bitmask = 0x00040000;
			break;
		case 31: // HT20 MCS19
			*rowIndex = 1;
			*bitmask = 0x00080000;
			break;
		case 32: // HT20 MCS20
			*rowIndex = 1;
			*bitmask = 0x00100000;
			break;
		case 33: // HT20 MCS21
			*rowIndex = 1;
			*bitmask = 0x00200000;
			break;
		case 34: // HT20 MCS22
			*rowIndex = 1;
			*bitmask = 0x00400000;
			break;
		case 35: // HT20 MCS23
			*rowIndex = 1;
			*bitmask = 0x00800000;
			break;

		case 36: // HT40 MCS0
			*rowIndex = 0;
			*bitmask = 0x01000000;
			break;
		case 37: // HT40 MCS1
			*rowIndex = 0;
			*bitmask = 0x02000000;
			break;
		case 38: // HT40 MCS2
			*rowIndex = 0;
			*bitmask = 0x04000000;
			break;
		case 39: // HT40 MCS3
			*rowIndex = 0;
			*bitmask = 0x08000000;
			break;
		case 40: // HT40 MCS4
			*rowIndex = 0;
			*bitmask = 0x10000000;
			break;
		case 41: // HT40 MCS5
			*rowIndex = 0;
			*bitmask = 0x20000000;
			break;
		case 42: // HT40 MCS6
			*rowIndex = 0;
			*bitmask = 0x40000000;
			break;
		case 43: // HT40 MCS7 135
			*rowIndex = 0;
			*bitmask = 0x80000000;
			break;

		case 44: // HT40 MCS8
			*rowIndex = 1;
			*bitmask = 0x00000100;
			break;
		case 45: // HT40 MCS9
			*rowIndex = 1;
			*bitmask = 0x00000200;
			break;
		case 46: // HT40 MCS10
			*rowIndex = 1;
			*bitmask = 0x00000400;
			break;
		case 47: // HT40 MCS11
			*rowIndex = 1;
			*bitmask = 0x00000800;
			break;
		case 48: // HT40 MCS12
			*rowIndex = 1;
			*bitmask = 0x00001000;
			break;
		case 49: // HT40 MCS13
			*rowIndex = 1;
			*bitmask = 0x00002000;
			break;
		case 50: // HT40 MCS14
			*rowIndex = 1;
			*bitmask = 0x00004000;
			break;
		case 51: // HT40 MCS15
			*rowIndex = 1;
			*bitmask = 0x00008000;
			break;

		case 52: // HT40 MCS16
			*rowIndex = 1;
			*bitmask = 0x01000000;
			break;
		case 53: // HT40 MCS17
			*rowIndex = 1;
			*bitmask = 0x02000000;
			break;
		case 54: // HT40 MCS18
			*rowIndex = 1;
			*bitmask = 0x04000000;
			break;
		case 55: // HT40 MCS19
			*rowIndex = 1;
			*bitmask = 0x08000000;
			break;
		case 56: // HT40 MCS20
			*rowIndex = 1;
			*bitmask = 0x10000000;
			break;
		case 57: // HT40 MCS21
			*rowIndex = 1;
			*bitmask = 0x20000000;
			break;
		case 58: // HT40 MCS22
			*rowIndex = 1;
			*bitmask = 0x40000000;
			break;
		case 59: // HT40 MCS23
			*rowIndex = 1;
			*bitmask = 0x80000000;
			break;

		case 60: // VHT20 MCS0 S1
			*rowIndex = 2;
			*bitmask = 0x00000001;
			break;
		case 61: // VHT20 MCS1 S1
			*rowIndex = 2;
			*bitmask = 0x00000002;
			break;
		case 62: // VHT20 MCS2 S1
			*rowIndex = 2;
			*bitmask = 0x00000004;
			break;
		case 63: // VHT20 MCS3 S1
			*rowIndex = 2;
			*bitmask = 0x00000008;
			break;
		case 64: // VHT20 MCS4 S1
			*rowIndex = 2;
			*bitmask = 0x00000010;
			break;
		case 65: // VHT20 MCS5 S1
			*rowIndex = 2;
			*bitmask = 0x00000020;
			break;
		case 66: // VHT20 MCS6 S1
			*rowIndex = 2;
			*bitmask = 0x00000040;
			break;
		case 67: // VHT20 MCS7 S1
			*rowIndex = 2;
			*bitmask = 0x00000080;
			break;
		case 68: // VHT20 MCS8 S1
			*rowIndex = 2;
			*bitmask = 0x00000100;
			break;
		case 69: // VHT20 MCS9 S1
			*rowIndex = 0;
			*bitmask = 0x00000200;
			break;

		case 70: // VHT20 MCS0 S2
			*rowIndex = 3;
			*bitmask = 0x00000010;
			break;
		case 71: // VHT20 MCS1 S2
			*rowIndex = 3;
			*bitmask = 0x00000020;
			break;
		case 72: // VHT20 MCS2 S2
			*rowIndex = 3;
			*bitmask = 0x00000040;
			break;
		case 73: // VHT20 MCS3 S2
			*rowIndex = 3;
			*bitmask = 0x00000080;
			break;
		case 74: // VHT20 MCS4 S2
			*rowIndex = 3;
			*bitmask = 0x00000100;
			break;
		case 75: // VHT20 MCS5 S2
			*rowIndex = 3;
			*bitmask = 0x00000200;
			break;
		case 76: // VHT20 MCS6 S2
			*rowIndex = 3;
			*bitmask = 0x00000400;
			break;
		case 77: // VHT20 MCS7 S2
			*rowIndex = 3;
			*bitmask = 0x00000800;
			break;
		case 78: // VHT20 MCS8 S2
			*rowIndex = 3;
			*bitmask = 0x00001000;
			break;
		case 79: // VHT20 MCS9 S2
			*rowIndex = 3;
			*bitmask = 0x00002000;
			break;

		case 80: // VHT20 MCS0 S3
			*rowIndex = 4;
			*bitmask = 0x00000100;
			break;
		case 81: // VHT20 MCS1 S3
			*rowIndex = 4;
			*bitmask = 0x00000200;
			break;
		case 82: // VHT20 MCS2 S3
			*rowIndex = 4;
			*bitmask = 0x00000400;
			break;
		case 83: // VHT20 MCS3 S3
			*rowIndex = 4;
			*bitmask = 0x00000800;
			break;
		case 84: // VHT20 MCS4 S3
			*rowIndex = 4;
			*bitmask = 0x00001000;
			break;
		case 85: // VHT20 MCS5 S3
			*rowIndex = 4;
			*bitmask = 0x00002000;
			break;
		case 86: // VHT20 MCS6 S3
			*rowIndex = 4;
			*bitmask = 0x00004000;
			break;
		case 87: // VHT20 MCS7 S3
			*rowIndex = 4;
			*bitmask = 0x00008000;
			break;
		case 88: // VHT20 MCS8 S3
			*rowIndex = 4;
			*bitmask = 0x00010000;
			break;
		case 89: // VHT20 MCS9 S3
			*rowIndex = 4;
			*bitmask = 0x00020000;
			break;

		case 90: // VHT40 MCS0 S1
			*rowIndex = 2;
			*bitmask = 0x00001000;
			break;
		case 91: // VHT40 MCS1 S1
			*rowIndex = 2;
			*bitmask = 0x00002000;
			break;
		case 92: // VHT40 MCS2 S1
			*rowIndex = 2;
			*bitmask = 0x00004000;
			break;
		case 93: // VHT40 MCS3 S1
			*rowIndex = 2;
			*bitmask = 0x00008000;
			break;
		case 94: // VHT40 MCS4 S1
			*rowIndex = 2;
			*bitmask = 0x00010000;
			break;
		case 95: // VHT40 MCS5 S1
			*rowIndex = 2;
			*bitmask = 0x00020000;
			break;
		case 96: // VHT40 MCS6 S1
			*rowIndex = 2;
			*bitmask = 0x00040000;
			break;
		case 97: // VHT40 MCS7 S1
			*rowIndex = 2;
			*bitmask = 0x00080000;
			break;
		case 98: // VHT40 MCS8 S1
			*rowIndex = 2;
			*bitmask = 0x00100000;
			break;
		case 99: // VHT40 MCS9 S1
			*rowIndex = 2;
			*bitmask = 0x00200000;
			break;

		case 100: // VHT40 MCS0 S2
			*rowIndex = 3;
			*bitmask = 0x00010000;
			break;
		case 101: // VHT40 MCS1 S2
			*rowIndex = 3;
			*bitmask = 0x00020000;
			break;
		case 102: // VHT40 MCS2 S2
			*rowIndex = 3;
			*bitmask = 0x00040000;
			break;
		case 103: // VHT40 MCS3 S2
			*rowIndex = 3;
			*bitmask = 0x00080000;
			break;
		case 104: // VHT40 MCS4 S2
			*rowIndex = 3;
			*bitmask = 0x00100000;
			break;
		case 105: // VHT40 MCS5 S2
			*rowIndex = 3;
			*bitmask = 0x00200000;
			break;
		case 106: // VHT40 MCS6 S2
			*rowIndex = 3;
			*bitmask = 0x00400000;
			break;
		case 107: // VHT40 MCS7 S2
			*rowIndex = 3;
			*bitmask = 0x00800000;
			break;
		case 108: // VHT40 MCS8 S2
			*rowIndex = 3;
			*bitmask = 0x01000000;
			break;
		case 109: // VHT40 MCS9 S2
			*rowIndex = 3;
			*bitmask = 0x02000000;
			break;

		case 110: // VHT40 MCS0 S3
			*rowIndex = 4;
			*bitmask = 0x00100000;
			break;
		case 111: // VHT40 MCS1 S3
			*rowIndex = 4;
			*bitmask = 0x00200000;
			break;
		case 112: // VHT40 MCS2 S3
			*rowIndex = 4;
			*bitmask = 0x00400000;
			break;
		case 113: // VHT40 MCS3 S3
			*rowIndex = 4;
			*bitmask = 0x00800000;
			break;
		case 114: // VHT40 MCS4 S3
			*rowIndex = 4;
			*bitmask = 0x01000000;
			break;
		case 115: // VHT40 MCS5 S3
			*rowIndex = 4;
			*bitmask = 0x02000000;
			break;
		case 116: // VHT40 MCS6 S3
			*rowIndex = 4;
			*bitmask = 0x04000000;
			break;
		case 117: // VHT40 MCS7 S3
			*rowIndex = 4;
			*bitmask = 0x08000000;
			break;
		case 118: // VHT40 MCS8 S3
			*rowIndex = 4;
			*bitmask = 0x10000000;
			break;
		case 119: // VHT40 MCS9 S3
			*rowIndex = 4;
			*bitmask = 0x20000000;
			break;

		case 120: // VHT80 MCS0 S0
			*rowIndex = 2;
			*bitmask = 0x01000000;
			break;
		case 121: // VHT80 MCS1 S0
			*rowIndex = 2;
			*bitmask = 0x02000000;
			break;
		case 122: // VHT80 MCS2 S0
			*rowIndex = 2;
			*bitmask = 0x04000000;
			break;
		case 123: // VHT80 MCS3 S0
			*rowIndex = 2;
			*bitmask = 0x08000000;
			break;
		case 124: // VHT80 MCS4 S0
			*rowIndex = 2;
			*bitmask = 0x10000000;
			break;
		case 125: // VHT80 MCS5 S0
			*rowIndex = 2;
			*bitmask = 0x20000000;
			break;
		case 126: // VHT80 MCS6 S0
			*rowIndex = 2;
			*bitmask = 0x40000000;
			break;
		case 127: // VHT80 MCS7 S0
			*rowIndex = 2;
			*bitmask = 0x80000000;
			break;
		case 128: // VHT80 MCS8 S0
			*rowIndex = 3;
			*bitmask = 0x00000001;
			break;
		case 129: // VHT80 MCS9 S0
			*rowIndex = 3;
			*bitmask = 0x00000002;
			break;

		case 130: // VHT80 MCS0 S1
			*rowIndex = 3;
			*bitmask = 0x10000000;
			break;
		case 131: // VHT80 MCS1 S1
			*rowIndex = 3;
			*bitmask = 0x20000000;
			break;
		case 132: // VHT80 MCS2 S1
			*rowIndex = 3;
			*bitmask = 0x40000000;
			break;
		case 133: // VHT80 MCS3 S1
			*rowIndex = 3;
			*bitmask = 0x80000000;
			break;
		case 134: // VHT80 MCS4 S1
			*rowIndex = 4;
			*bitmask = 0x00000001;
			break;
		case 135: // VHT80 MCS5 S1
			*rowIndex = 4;
			*bitmask = 0x00000002;
			break;
		case 136: // VHT80 MCS6 S1
			*rowIndex = 4;
			*bitmask = 0x00000004;
			break;
		case 137: // VHT80 MCS7 S1
			*rowIndex = 4;
			*bitmask = 0x00000008;
			break;
		case 138: // VHT80 MCS8 S1
			*rowIndex = 4;
			*bitmask = 0x00000010;
			break;
		case 139: // VHT80 MCS9 S1
			*rowIndex = 4;
			*bitmask = 0x00000020;
			break;

		case 140: // VHT80 MCS0 S3
			*rowIndex = 5;
			*bitmask = 0x00000001;
			break;
		case 141: // VHT80 MCS1 S3
			*rowIndex = 5;
			*bitmask = 0x00000002;
			break;
		case 142: // VHT80 MCS2 S3
			*rowIndex = 5;
			*bitmask = 0x00000004;
			break;
		case 143: // VHT80 MCS3 S3
			*rowIndex = 5;
			*bitmask = 0x00000008;
			break;
		case 144: // VHT80 MCS4 S3
			*rowIndex = 5;
			*bitmask = 0x00000010;
			break;
		case 145: // VHT80 MCS5 S3
			*rowIndex = 5;
			*bitmask = 0x00000020;
			break;
		case 146: // VHT80 MCS6 S3
			*rowIndex = 5;
			*bitmask = 0x00000040;
			break;
		case 147: // VHT80 MCS7 S3
			*rowIndex = 5;
			*bitmask = 0x00000080;
			break;
		case 148: // VHT80 MCS8 S3
			*rowIndex = 5;
			*bitmask = 0x00000100;
			break;
		case 149: // VHT80 MCS9 S3
			*rowIndex = 5;
			*bitmask = 0x00000200;
			break;
	}
}

//
// PUBLIC FUNCTIONS
//
void qca6174Check(void)
{
	if (gCmd.freq == 0 ) {
		gCmd.freq = 2412;
	}
	qca6174TxStop();
	qca6174RxPacketStop();
}

void testcmd_error(int code, const char *fmt, ...)
{
	gCmd.errCode = code;
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(gCmd.errString, sizeof(gCmd.errString)-1, fmt, ap);
	va_end(ap);

	ALOGE("%s", gCmd.errString);
}

int qca6174ApiInit(void)
{
	memset(&gCmd, 0, sizeof(gCmd));

	gCmd.txPwr = 0;
	gCmd.pktLen0 = 1500;
	gCmd.aifs = 1;

//	optarg = NULL;
//	optind = opterr = 1;
//	optopt = '?';
	return 0;
}

void qca6174ApiCleanup(void)
{
	qca6174Check();
	memset(&gCmd, 0, sizeof(gCmd));
}

void qca6174ChannelSet(int channel)
{
	gCmd.freq = channel_to_freq(channel);
}

void qca6174FreqSet(uint32_t freq)
{
	gCmd.freq = freq;
}

void qca6174ShortGuardSet(int enable)
{
	gCmd.shortguard = enable ? 1 : 0;
}

void qca6174RateSet(int rate)
{
	gCmd.rate = rate;
}

void qca6174TxPowerSet(int txpwr)
{
	gCmd.txPwr = txpwr;
}

void qca6174TxPcmSet(int txpwr)
{
	gCmd.tpcm = txpwr;
}

void qca6174TxPacketSizeSet(int size)
{
	gCmd.pktLen0 = size;
}

void qca6174SetPaCfg(int val)
{
	gCmd.paConfig = val;
}

void qca6174SetDacGain(int val)
{
	gCmd.dacGain = val;
}

void qca6174SetGainIdx(int val)
{
	gCmd.gainIdx = val;
}

void qca6174SetNumPkt(int val)
{
	gCmd.numPkt = val;
}

void qca6174SetAgg(int val)
{
	gCmd.agg = val;
}

void qca6174SetStbc(int val)
{
	gCmd.stbc = val;
}

void qca6174SetLdpc(int val)
{
	gCmd.ldpc = val;
}

void qca6174SetWlanMode(int val)
{
	gCmd.wmode = val;
}

void qca6174SetLPreamble()
{
	gCmd.longpreamble = true;
}

void qca6174init()
{
	gCmd.wmode = TCMD_WLAN_MODE_MAX;
}

#ifdef NOT_USE_CLITLVCMD_IF_MODULE
int qca6174TxCommand(const char *txtype)
{
	uint8_t *rCmdStream = NULL;
	uint32_t cmdStreamLen = 0;
	uint32_t miscFlags = PROCESS_RATE_IN_ORDER_MASK | TX_STATUS_PER_RATE_MASK;
	uint32_t txMode, value;
	uint8_t mac[ATH_MAC_LEN];
	uint32_t rowIndex = 0, rateBitMask = 0;
	int is11ACRate = FALSE;
	uint32_t dataRate = 0, wlanMode = 0;


	getDataRateAndWlanMode(&dataRate, &wlanMode);

	if (gCmd.freq == 0) {
		gCmd.freq = 2412;
	}

	createCommand(_OP_TX);
	ALOGE("%s() opcode _OP_TX", __func__);

	if (gCmd.broadcast != 1){
		addParameterToCommand((uint8_t *)"broadcast",(uint8_t *)&gCmd.broadcast);
		ALOGE("\n%s() adding command(broadcast, %d)\n", __func__, gCmd.broadcast);
	}


	if (is_zero_ether_addr(gCmd.bssid)) {
		ath_ether_aton(DEFAULT_TX_BSSID, mac);
		addParameterToCommand((uint8_t *)"bssid",(uint8_t *)mac);
		ALOGE("\n%s() adding command(bssid, %x:%x:%x:%x:%x:%x)\n", __func__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	}
	else {
		addParameterToCommand((uint8_t *)"bssid",(uint8_t *)gCmd.bssid);
		ALOGE("\n%s() adding command(bssid, %x:%x:%x:%x:%x:%x)\n", __func__, gCmd.bssid[0], gCmd.bssid[1], gCmd.bssid[2], gCmd.bssid[3], gCmd.bssid[4], gCmd.bssid[5]);
	}

	if (is_zero_ether_addr(gCmd.txStation)) {
		ath_ether_aton(DEFAULT_TX_TXSTATION, mac);
		addParameterToCommand((uint8_t *)"txStation",(uint8_t *)mac);
		ALOGE("\n%s() adding command(txStation, %x:%x:%x:%x:%x:%x)\n", __func__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	}
	else{
		addParameterToCommand((uint8_t *)"txStation",(uint8_t *)gCmd.txStation);
		ALOGE("\n%s() adding command(txStation, %x:%x:%x:%x:%x:%x)\n", __func__, gCmd.txStation[0], gCmd.txStation[1], gCmd.txStation[2], gCmd.txStation[3], gCmd.txStation[4], gCmd.txStation[5]);

	}

	if (is_zero_ether_addr(gCmd.rxStation)) {
		ath_ether_aton(DEFAULT_TX_RXSTATION, mac);
		addParameterToCommand((uint8_t *)"rxStation",(uint8_t *)mac);
		ALOGE("\n%s() adding command(rxStation, %x:%x:%x:%x:%x:%x)\n", __func__, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	}
	else{
		addParameterToCommand((uint8_t *)"rxStation",(uint8_t *)gCmd.rxStation);
		ALOGE("\n%s() adding command(rxStation, %x:%x:%x:%x:%x:%x)\n", __func__, gCmd.rxStation[0], gCmd.rxStation[1], gCmd.rxStation[2], gCmd.rxStation[3], gCmd.rxStation[4], gCmd.rxStation[5]);
	}

//	addParameterToCommand((uint8_t *)"tpcm",(uint8_t *)&gCmd.tpcm);
	addParameterToCommand((uint8_t *)"flags",(uint8_t *)&miscFlags);
      ALOGE("\n%s() adding command(flags, %d)\n", __func__, miscFlags);

	if (wlanMode != TCMD_WLAN_MODE_HT20){
		addParameterToCommand((uint8_t *)"wlanMode",(uint8_t *)&wlanMode);
		ALOGE("\n%s() adding command(wlanMode, %d)\n", __func__, wlanMode);
	}

	if (!strcmp(txtype, "sine")) {
		txMode = TCMD_CONT_TX_SINE;
	} else if (!strcmp(txtype, "frame")) {
		txMode = TCMD_CONT_TX_FRAME;
	} else if (!strcmp(txtype, "tx99")) {
		txMode = TCMD_CONT_TX_TX99;
	} else if (!strcmp(txtype, "tx100")) {
		txMode = TCMD_CONT_TX_TX100;
	} else if (!strcmp(txtype, "cwtone")) {
		txMode = TCMD_CONT_TX_CWTONE;
	} else if (!strcmp(txtype, "clpcpkt")) {
		txMode = TCMD_CONT_TX_CLPCPKT;
	} else if (!strcmp(txtype, "off")) {
		txMode = TCMD_CONT_TX_OFF;
	} else {
		ALOGE("%s():%d Error wrong txMode %s\n", __func__, __LINE__, txtype);
	}

	addParameterToCommand((uint8_t *)"txMode",(uint8_t *)&txMode);
	ALOGE("\n%s() adding command(txMode, %d)\n", __func__, txMode);

	value = PN9_PATTERN;
	addParameterToCommand((uint8_t *)"txPattern",(uint8_t *)&value);
	ALOGE("\n%s() adding command(txPattern, %d)\n", __func__, value);

	if (gCmd.aifs){
		addParameterToCommand((uint8_t *)"aifsn",(uint8_t *)&gCmd.aifs);
		ALOGE("\n%s() adding command(aifsn, %d)\n", __func__, gCmd.aifs);
	}

	rateIndexToArrayMapping(dataRate, &rowIndex, &rateBitMask, &is11ACRate);
	value = rowIndex*32 + getOffsetFromBitmap(rateBitMask);
#ifdef TCMD_LIB_DEBUG
	printf("dataRate %d rateIndex %d \n", dataRate, value);
#endif
	addParameterToCommand((uint8_t *)"rateBitIndex0",(uint8_t *)&value);
      printf("dataRate %d rateIndex %d \n", dataRate, value);

	if (gCmd.shortguard) {
		value = 1;
		addParameterToCommand((uint8_t *)"shortGuard",(uint8_t *)&value);
		ALOGE("\n%s() adding command(shortGuard, %d)\n", __func__, value);
	}

	if (!gCmd.pktLen0)
		gCmd.pktLen0 = 1500;
	addParameterToCommand((uint8_t *)"pktLen0",(uint8_t *)&gCmd.pktLen0);
	ALOGE("\n%s() adding command(pktLen0, %d)\n", __func__, gCmd.pktLen0);
	addParameterToCommand((uint8_t *)"txChain0",(uint8_t *)&gCmd.chain);
	ALOGE("\n%s() adding command(txChain0, %d)\n", __func__, gCmd.chain);

	value = 1;
	addParameterToCommand((uint8_t *)"ir",(uint8_t *)&value);
	ALOGE("\n%s() adding command(ir, %d)\n", __func__, value);

	value = gCmd.txPwr * 2;
	addParameterToCommand((uint8_t *)"txPower0",(uint8_t *)&value);
	ALOGE("\n%s() adding command(txPower0, %d)\n", __func__, value);

	value = 0;
	addParameterToCommand((uint8_t *)"paConfig",(uint8_t *)&value);
	ALOGE("\n%s() adding command(paConfig, %d)\n", __func__, value);

	commandComplete(&rCmdStream, &cmdStreamLen);
	print_hex_dump(rCmdStream, cmdStreamLen);

	doCommand(rCmdStream, cmdStreamLen);

	if (gCmd.errCode == 0) {
		gCmd.isTxStart = 1;

	}
	else {
		ALOGE("\n%s() error = %d\n", __func__, gCmd.errCode);
	}

	return (gCmd.errCode == 0) ? 0 : -1;
}
#else
int qca6174TxCommand(const char *txtype)
{
	TX_DATA_START_PARAMS *Params;
	uint8_t *rCmdStream = NULL;
	uint32_t cmdStreamLen = 0;
	uint32_t rowIndex = 0, rateBitMask = 0;
	int is11ACRate = FALSE;
	uint32_t dataRate = 0, wlanMode = 0;
	int16_t tx_power = 0;
	int isPowerChanged = 0;
	int i;

	Params = malloc(sizeof(TX_DATA_START_PARAMS));

	if (gCmd.freq == 0) {
		gCmd.freq = 2412;
	}

	if (!strcmp(txtype, "sine")) {
		Params->mode = TCMD_CONT_TX_SINE;
	} else if (!strcmp(txtype, "frame")) {
		Params->mode = TCMD_CONT_TX_FRAME;
	} else if (!strcmp(txtype, "tx99")) {
		Params->mode = TCMD_CONT_TX_TX99;
	} else if (!strcmp(txtype, "tx100")) {
		Params->mode = TCMD_CONT_TX_TX100;
	} else if (!strcmp(txtype, "cwtone")) {
		Params->mode = TCMD_CONT_TX_CWTONE;
	} else if (!strcmp(txtype, "clpcpkt")) {
		Params->mode = TCMD_CONT_TX_CLPCPKT;
	} else if (!strcmp(txtype, "off")) {
		Params->mode = TCMD_CONT_TX_OFF;
	} else {
		ALOGE("%s():%d Error wrong txMode %s\n", __func__, __LINE__, txtype);
	}

	Params->antenna = 0;
	Params->enANI = gCmd.ani;
	Params->scramblerOff = 0;
	Params->aifsn = gCmd.aifs;
	Params->txPattern = ZEROES_PATTERN;
	Params->shortGuard = gCmd.shortguard;
	Params->numPackets = gCmd.numPkt;
	/* Use chain 3 for default since Agilent N4010 doesn't support 2 chains */
        ALOGE("-------------------------%s():%d gCmd.chain = %d\n", __func__, __LINE__, gCmd.chain);
	if (gCmd.chain) {
		Params->txChain = gCmd.chain;
	} else
		Params->txChain = 1;

	Params->miscFlags = PROCESS_RATE_IN_ORDER_MASK | TX_STATUS_PER_RATE_MASK;
	if (gCmd.stbc)
		Params->miscFlags |= DESC_STBC_ENA_MASK;

	if (gCmd.ldpc)
		Params->miscFlags |= DESC_LDPC_ENA_MASK;

	Params->broadcast = 0;

	if (is_zero_ether_addr(gCmd.bssid))
		ath_ether_aton(DEFAULT_TX_BSSID, Params->bssid);
	else
		memcpy(Params->bssid, gCmd.bssid, ATH_MAC_LEN);

	Params->bandwidth = gCmd.bandWidth;

	if (is_zero_ether_addr(gCmd.txStation))
		ath_ether_aton(DEFAULT_TX_TXSTATION, Params->txStation);
	else
		memcpy(Params->txStation, gCmd.txStation, ATH_MAC_LEN);

	if (is_zero_ether_addr(gCmd.rxStation))
		ath_ether_aton(DEFAULT_TX_RXSTATION, Params->rxStation);
	else
		memcpy(Params->rxStation, gCmd.rxStation, ATH_MAC_LEN);

	if (!gCmd.tpcm)
		Params->tpcm = TPC_TX_PWR;
	else
		Params->tpcm = gCmd.tpcm;

	Params->agg = gCmd.agg;

	getDataRateAndWlanMode(&dataRate, &wlanMode);
	if (gCmd.wmode != TCMD_WLAN_MODE_MAX)
		Params->wlanMode = gCmd.wmode;
	else
		Params->wlanMode = wlanMode;

	Params->freq = findCenterFreq(Params->wlanMode);
	rateIndexToArrayMapping(dataRate, &rowIndex, &rateBitMask, &is11ACRate);
	for (i=0; i<RATE_POWER_MAX_INDEX; i++)
		Params->rateMaskBitPosition[i] = 0xff;
	Params->rateMaskBitPosition[0] = (rowIndex << 5) + getOffsetFromBitmap(rateBitMask);
#ifdef TCMD_LIB_DEBUG
	printf("dataRate %d rateIndex %d \n", dataRate, Params->rateMaskBitPosition[0]);
#endif
	for (i=0; i<RATE_POWER_MAX_INDEX; i++)
		Params->txPower[i] = 0xff;
	printf("dataRate %d rateIndex %d \n", dataRate,	Params->rateMaskBitPosition[0]);
#if 0 /* SS HW and QCA HW required */
	if (gCmd.txPwr) {
		if ((Params->freq >= 2412 && Params->freq <= 2472) || Params->freq == 2484) {
			switch (wlanMode) {
				case TCMD_WLAN_MODE_NOHT:
					tx_power = gCmd.txPwr - 2;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_HT20:
				case TCMD_WLAN_MODE_HT40PLUS:
				case TCMD_WLAN_MODE_HT40MINUS:
					break;
				case TCMD_WLAN_MODE_CCK:
					tx_power = gCmd.txPwr - 3;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_VHT20:
				case TCMD_WLAN_MODE_VHT40PLUS:
				case TCMD_WLAN_MODE_VHT40MINUS:
				case TCMD_WLAN_MODE_VHT80_0:
				case TCMD_WLAN_MODE_VHT80_1:
				case TCMD_WLAN_MODE_VHT80_2:
				case TCMD_WLAN_MODE_VHT80_3:
					break;
				default:
					break;
			}
		}
	} else {
		if ((Params->freq >= 2412 && Params->freq <= 2472) || Params->freq == 2484) {
			switch (wlanMode) {
				case TCMD_WLAN_MODE_NOHT:
					tx_power = 14;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_HT20:
				case TCMD_WLAN_MODE_HT40PLUS:
				case TCMD_WLAN_MODE_HT40MINUS:
					tx_power = 12;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_CCK:
					tx_power = 17;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_VHT20:
				case TCMD_WLAN_MODE_VHT40PLUS:
				case TCMD_WLAN_MODE_VHT40MINUS:
				case TCMD_WLAN_MODE_VHT80_0:
				case TCMD_WLAN_MODE_VHT80_1:
				case TCMD_WLAN_MODE_VHT80_2:
				case TCMD_WLAN_MODE_VHT80_3:
					ALOGE("%s ERROR: not available! freq: %d, wlanMode %d", __func__, Params->freq, wlanMode);
					break;
				default:
					break;
			}
		} else {
			switch (wlanMode) {
				case TCMD_WLAN_MODE_NOHT:
					tx_power = 10;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_HT20:
				case TCMD_WLAN_MODE_HT40PLUS:
				case TCMD_WLAN_MODE_HT40MINUS:
					tx_power = 9;
					isPowerChanged = 1;
					break;
				case TCMD_WLAN_MODE_CCK:
					ALOGE("%s ERROR: not available! freq: %d, wlanMode %d", __func__, Params->freq, wlanMode);
					break;
				case TCMD_WLAN_MODE_VHT20:
				case TCMD_WLAN_MODE_VHT40PLUS:
				case TCMD_WLAN_MODE_VHT40MINUS:
				case TCMD_WLAN_MODE_VHT80_0:
				case TCMD_WLAN_MODE_VHT80_1:
				case TCMD_WLAN_MODE_VHT80_2:
				case TCMD_WLAN_MODE_VHT80_3:
					tx_power = 9;
					isPowerChanged = 1;
					break;
				default:
					break;
			}
		}
	}
#endif

	if (tx_power < 0)
		tx_power = 0;
	if (gCmd.txPwr < 0)
		gCmd.txPwr = 0;

	if (isPowerChanged) {
		Params->txPower[0] = tx_power * 2;
	} else {
		Params->txPower[0] = gCmd.txPwr * 2;
	}
	ALOGE("%s - input pwr %d output pwr %d", __func__, gCmd.txPwr, tx_power);

	for (i=0; i<RATE_POWER_MAX_INDEX; i++)
		Params->pktLength[i] = 0x0;

	if (!gCmd.pktLen0)
		gCmd.pktLen0 = 1500;

	Params->pktLength[0] = gCmd.pktLen0;

	Params->ir = 1;
	Params->dutycycle = 0;
	Params->paConfig = gCmd.paConfig;
	Params->gainIdx = gCmd.gainIdx;
	Params->dacGain = gCmd.dacGain;

	createCommand(_OP_TX);
	ALOGE("%s() opcode _OP_TX", __func__);

	addTxParameters(Params);

	commandComplete(&rCmdStream, &cmdStreamLen);
	print_hex_dump(rCmdStream, cmdStreamLen);

	doCommand(rCmdStream, cmdStreamLen);

	if (gCmd.errCode == 0) {
		gCmd.isTxStart = 1;

	}
	else {
		ALOGE("\n%s() error = %d\n", __func__, gCmd.errCode);
	}

	return (gCmd.errCode == 0) ? 0 : -1;
}
#endif

int qca6174TxSineStart(void)
{
	return qca6174TxCommand("sine");
}

int qca6174Tx99Start(void)
{
	return qca6174TxCommand("tx99");
}

int qca6174TxFrameStart(void)
{
	return qca6174TxCommand("frame");
}

int qca6174TxCWStart(void)
{
    return qca6174TxCommand("cwtone");
}

int qca6174TxStop(void)
{
	int ret;
	if (1 || gCmd.isTxStart) {
		ret = qca6174TxCommand("off");
		if (!ret)
			gCmd.isTxStart = 0;
		return ret;
	}
	return 0;
}

void addRateMaskToCommand(int dataRate)
{
	uint32_t rowIndex = 0, rateBitMask = 0;
	int is11ACRate = FALSE;
	uint8_t rateMask[25];
	uint32_t value = 0;

	/* let user input index of rateTable instead of string parse */
	if ( dataRate > 154 ) {
		ALOGE("%s() Invalid Index\n", __func__);
		return;
	}

	if ( dataRate == 153 ) // Sweep all rates
	{
#if 0
		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask",0);
		rateBitMask = 0xFFFFFF00;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask",1);
		rateBitMask = 0xFFFFFFFF;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask11AC",0);
		rateBitMask = 0xFF3FF1FF;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask11AC",1);
		rateBitMask = 0xF3FF1FF3;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask11AC",2);
		rateBitMask = 0x3FF3FF3F;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		memset(rateMask,0,sizeof(rateMask));
		snprintf((char*)rateMask,25,"%s%d","rateMask11AC",3);
		rateBitMask = 0x3BF;
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);
#else
		ALOGE("%s() Sweep all rates is not verified.\n", __func__);
		return;
#endif
	}
	else {
		// Map ratemask to the bitmask value..
		rateIndexToArrayMapping (dataRate, &rowIndex, &rateBitMask, &is11ACRate);

		printf("rowIndex %d bitMask %8x\n",rowIndex,rateBitMask);

		memset(rateMask,0,sizeof(rateMask));

		snprintf((char*)rateMask,25,"%s%d","rateMask",rowIndex);
		addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&rateBitMask);

		if ( rowIndex != 0 ) {
			//NOTE: This is required as on the firmware default rateMask0 is set to rate 11
			memset(rateMask,0,sizeof(rateMask));
			snprintf((char*)rateMask,25,"%s%d","rateMask",0);
			value = 0;
			addParameterToCommand((uint8_t *)rateMask,(uint8_t *)&value);
		}
	}
}

#ifdef NOT_USE_CLITLVCMD_IF_MODULE
int qca6174RxPacketStart(void)
{
	uint8_t *rCmdStream = NULL;
	uint32_t cmdStreamLen = 0;
	uint32_t miscFlags = PROCESS_RATE_IN_ORDER_MASK | RX_STATUS_PER_RATE_MASK;
	uint8_t mac[ATH_MAC_LEN];
	uint32_t dataRate = 0, wlanMode = 0;
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 300000;  /* 300 usec */

	gCmd.rxPkt = gCmd.rxRssi = gCmd.rxCrcError = gCmd.rxSecError = 0;

	getDataRateAndWlanMode(&dataRate, &wlanMode);
	if (gCmd.freq == 0) {
		gCmd.freq = 2412;
	}

	createCommand(_OP_RX);
	ALOGE("%s() opcode _OP_RX", __func__);

	if (gCmd.freq != 2412)
		addParameterToCommand((uint8_t *)"channel",(uint8_t *)&gCmd.freq);

	if (gCmd.antenna != 0)
		addParameterToCommand((uint8_t *)"antenna",(uint8_t *)&gCmd.antenna);

	if (gCmd.ani != 0)
		addParameterToCommand((uint8_t *)"enANI",(uint8_t *)&gCmd.ani);

	addParameterToCommand((uint8_t *)"wlanMode",(uint8_t *)&wlanMode);
	addParameterToCommand((uint8_t *)"rxChain",(uint8_t *)&gCmd.chain);

	if (is_zero_ether_addr(gCmd.bssid)) {
		ath_ether_aton(DEFAULT_RX_BSSID, mac);
		addParameterToCommand((uint8_t *)"bssid",(uint8_t *)mac);
	}
	else
		addParameterToCommand((uint8_t *)"bssid",(uint8_t *)gCmd.bssid);

	if (is_zero_ether_addr(gCmd.addr)) {
		ath_ether_aton(DEFAULT_RX_ADDR, mac);
		addParameterToCommand((uint8_t *)"addr",(uint8_t *)mac);
	}
	else
		addParameterToCommand((uint8_t *)"addr",(uint8_t *)gCmd.addr);

	addParameterToCommand((uint8_t *)"expectedPkts",(uint8_t *)&gCmd.expectedPkts);
	addParameterToCommand((uint8_t *)"flags",(uint8_t *)&miscFlags);

	addRateMaskToCommand(dataRate);

	commandComplete(&rCmdStream, &cmdStreamLen);
	print_hex_dump(rCmdStream, cmdStreamLen);

	doCommand(rCmdStream, cmdStreamLen);

	if (gCmd.errCode == 0) {
		gCmd.isRxStart = 1;
	} else {
		ALOGE("\n%s() error = %d\n", __func__, gCmd.errCode);
	}
	nanosleep (&ts, NULL); /* delay here */
	return (gCmd.errCode == 0) ? 0 : -1;
}
#else
int qca6174RxPacketStart(void)
{
	RX_DATA_START_PARAMS *Params;
	uint8_t *rCmdStream = NULL;
	uint32_t cmdStreamLen = 0;
	uint32_t rowIndex = 0, rateBitMask = 0;
	int is11ACRate = FALSE;
	uint32_t dataRate = 0, wlanMode = 0;
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 300000;  /* 300 usec */
	int i;

	if (gCmd.freq == 0) {
		gCmd.freq = 2412;
	}

	Params = malloc(sizeof(RX_DATA_START_PARAMS));

	gCmd.rxPkt = gCmd.rxRssi = gCmd.rxCrcError = gCmd.rxSecError = 0;

	getDataRateAndWlanMode(&dataRate, &wlanMode);
	if (gCmd.wmode != TCMD_WLAN_MODE_MAX)
		Params->wlanMode = gCmd.wmode;
	else
		Params->wlanMode = wlanMode;

	Params->freq = findCenterFreq(Params->wlanMode);
	Params->antenna = 0;
	Params->enANI = gCmd.ani;
	Params->promiscuous = 1;
	ALOGE("\n%s() freq = %d\n", __func__, Params->freq);
	ALOGE("\n%s() antenna = %d\n", __func__, Params->antenna);
	ALOGE("\n%s() enANI = %d\n", __func__, Params->enANI);
	ALOGE("\n%s() wlanMode = %d\n", __func__, Params->wlanMode);

	/* Use chain 3 for default since Agilent N4010 doesn't support 2 chains */
	if (gCmd.chain) {
		Params->rxChain = gCmd.chain;
	} else
		Params->rxChain = 3;
	Params->broadcast = 1;

	ALOGE("\n%s() broadcast = %d\n", __func__, Params->broadcast);
	ALOGE("\n%s() rxChain = %d\n", __func__, Params->rxChain);

	if (is_zero_ether_addr(gCmd.bssid))
		ath_ether_aton(DEFAULT_RX_BSSID, Params->bssid);
	else
		memcpy(Params->bssid, gCmd.bssid, ATH_MAC_LEN);
	ALOGE("\n%s() bssid = ", __func__);
      print_hex_dump(Params->bssid,6);
	Params->bandwidth = gCmd.bandWidth;
	ALOGE("\n%s() bandwidth = %d\n", __func__, Params->bandwidth);
	if (is_zero_ether_addr(gCmd.addr))
		ath_ether_aton(DEFAULT_RX_ADDR, Params->rxStation);
	else
		memcpy(Params->rxStation, gCmd.addr, ATH_MAC_LEN);

      ALOGE("\n%s() rxStation = ", __func__);
      print_hex_dump(Params->rxStation,6);

	Params->numPackets = 0;

	for (i=0; i<RATE_MASK_ROW_MAX; i++)
		Params->rateMask[i] = 0;
	// Map ratemask to the bitmask value..
	rateIndexToArrayMapping(dataRate, &rowIndex, &rateBitMask, &is11ACRate);
	Params->rateMask[rowIndex] = rateBitMask;
	if ( rowIndex != 0 ) {
		//NOTE: This is required as on the firmware default rateMask0 is set to rate 11
		Params->rateMask[0] = 0;
	}

	createCommand(_OP_RX);
	ALOGE("%s() opcode _OP_RX", __func__);

	addRxParameters(Params);

	commandComplete(&rCmdStream, &cmdStreamLen);
	print_hex_dump(rCmdStream, cmdStreamLen);

	doCommand(rCmdStream, cmdStreamLen);

	if (gCmd.errCode == 0) {
		gCmd.isRxStart = 1;
		ALOGE("\n%s() success = %d\n", __func__, gCmd.errCode);
	} else {
		ALOGE("\n%s() error = %d\n", __func__, gCmd.errCode);
	}
	nanosleep (&ts, NULL); /* delay here */
	return (gCmd.errCode == 0) ? 0 : -1;
}
#endif

int qca6174RxPacketStop(void)
{
      ALOGE("\n%s() isRxStart = %d\n", __func__, gCmd.isRxStart);
	if (1 || gCmd.isRxStart)
	{
		uint8_t *rCmdStream = NULL;
		uint32_t cmdStreamLen = 0;
		uint32_t value;

		createCommand(_OP_GENERIC_NART_CMD);
		ALOGE("%s() opcode _OP_GENERIC_NART_CMD", __func__);

		/* What is meaning of that value? */
		value = 0xb7;
		addParameterToCommand((uint8_t *)"commandId",(uint8_t *)&value);

		value = 1;
		addParameterToCommand((uint8_t *)"param1",(uint8_t *)&value);

		commandComplete(&rCmdStream, &cmdStreamLen);
		print_hex_dump(rCmdStream, cmdStreamLen);

		doCommand(rCmdStream, cmdStreamLen);

		if (gCmd.errCode == 0) {
			gCmd.isRxStart = 0;
		} else {
			ALOGE("\n%s() error = %d\n", __func__, gCmd.errCode);
		}
		return (gCmd.errCode == 0) ? 0 : -1;
	}

	return 0;
}

void qca6174SetLongPreamble(int enable)
{
	gCmd.longpreamble = enable;
}

void qca6174SetAifsNum(int slot)
{
	gCmd.aifs = slot;
}

void qca6174SetAntenna(int antenna)
{
//	gCmd.antenna = antenna;
	gCmd.chain = antenna;
ALOGE("\n-----------------%s() gCmd.chain = %d\n", __func__, gCmd.chain);
}

void qca6174SetAni(int ani)
{
	gCmd.ani = ani;
}

void qca6174SetBssid(char *mac)
{
	if (ath_ether_aton(mac, gCmd.bssid) != 0) {
		ALOGE("Invalid bssid address format! \n");
	}
}

void qca6174SetTxStation(char *mac)
{
	if (ath_ether_aton(mac, gCmd.txStation) != 0) {
		ALOGE("Invalid bssid address format! \n");
	}
}

void qca6174SetRxStation(char *mac)
{
	if (ath_ether_aton(mac, gCmd.rxStation) != 0) {
		ALOGE("Invalid bssid address format! \n");
	}
}

void qca6174SetAddr(char *mac)
{
	if (ath_ether_aton(mac, gCmd.addr) != 0) {
		ALOGE("Invalid addr address format! \n");
	}
}

/*
 * assumption is that the number of total packets is always 1000.
 */
#define RX_TOTAL_PACKET_COUNT           1000

static uint32_t rx_good_packets = RX_TOTAL_PACKET_COUNT;
static uint32_t rx_error_packets = 0;

uint32_t qca6174RxGetErrorFrameNum(void)
{
	rx_error_packets = RX_TOTAL_PACKET_COUNT - gCmd.rxPkt;

	return rx_error_packets;
}

uint32_t qca6174RxGetGoodFrameNum(void)
{
	rx_good_packets = gCmd.rxPkt;

	return rx_good_packets;
}

const char *qca6174GetErrorString(void)
{
	return gCmd.errString;
}

void qca6174SetBandWidth(int width)
{
	gCmd.bandWidth = width;
}
