/*==========================================================================

                     FTM WLAN Header File

Description
  The header file includes enums, struct definitions for WLAN FTM packets

# Copyright (c) 2010-2015, 2014 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/

/*===========================================================================

                         Edit History


when       who       what, where, why
--------   ---       ----------------------------------------------------------
07/11/11   karthikm  Created header file to include enums, struct for WLAN FTM
                     for Atheros support
========================================================================*/

#ifndef  FTM_WLAN_H_
#define  FTM_WLAN_H_

#ifdef CONFIG_FTM_WLAN

#include <sys/types.h>
#include <stdint.h>

#define FTM_WLAN_CMD_CODE 22

extern char g_ifname[];

/* Various ERROR CODES supported by the FTM WLAN module*/
typedef enum {
    FTM_ERR_CODE_PASS = 0,
    FTM_ERR_CODE_IOCTL_FAIL,
    FTM_ERR_CODE_SOCK_FAIL,
    FTM_ERR_CODE_UNRECOG_FTM
}FTM_WLAN_ERROR_CODES;


#define CONFIG_HOST_TCMD_SUPPORT  1
#define AR6000_IOCTL_SUPPORTED    1

#define ATH_MAC_LEN               6
typedef char WLAN_AT_BUFFER_STRU;

typedef enum
{
    AT_WIENABLE_OFF  = 0,   /*OFF */
    AT_WIENABLE_ON   = 1,   /*ON signaling mode*/
    AT_WIENABLE_TEST = 2    /*Test mode¡]for WT and MT test¡^default setting after startup*/
}WLAN_AT_WIENABLE_TYPE;

typedef enum
{
    AT_WIMODE_CW      = 0,  /*CW      */
    AT_WIMODE_80211a  = 1,  /*802.11a */
    AT_WIMODE_80211b  = 2,  /*802.11b */
    AT_WIMODE_80211g  = 3,  /*802.11g */
    AT_WIMODE_80211n  = 4,  /*802.11n */
    AT_WIMODE_80211ac = 5,  /*802.11ac*/
}WLAN_AT_WIMODE_TYPE;

typedef enum
{
    AT_WIBAND_20M   = 0,  /* 20MHz*/
    AT_WIBAND_40M   = 1,  /* 40MHz*/
    AT_WIBAND_80M   = 2,  /* 80MHz*/
    AT_WIBAND_160M  = 3,  /*160MHz*/
}WLAN_AT_WIBAND_TYPE;

typedef enum
{
    AT_WIFREQ_24G   = 0,  /*2.4G*/
    AT_WIFREQ_50G   = 1,  /* 5G*/
}WLAN_AT_WIFREQ_TYPE;

typedef struct _WIFREQ_STRU
{
    uint16_t value;   /*frequency unit(MHz)¡Arange( 0¡ã65535)*/
    int16_t offset;  /*offset, unit(KHz)¡Arange(-32768¡ã32767)¡Adefault is 0*/
}WLAN_AT_WIFREQ_STRU;

typedef enum
{
    AT_FEATURE_TYPE_OFF  = 0,   /*OFF */
    AT_FEATURE_TYPE_ON   = 1,   /*ON */
}WLAN_AT_FEATURE_TYPE;

typedef enum
{
	ATH_RATE_1M=1,			//0
	ATH_RATE_2M=2,
	ATH_RATE_5_5M=3,
	ATH_RATE_6M = 4,		//4
	ATH_RATE_9M = 5,
	ATH_RATE_11M = 6,		//3
	ATH_RATE_12M = 7,
	ATH_RATE_18M = 8,
	ATH_RATE_24M = 10,
	ATH_RATE_36M = 12,
	ATH_RATE_48M = 13,
	ATH_RATE_54M = 14,		//11

	ATH_RATE_MCS0 = 15,
	ATH_RATE_MCS1 = 16,
	ATH_RATE_MCS2 = 17,
	ATH_RATE_MCS3 = 18,
	ATH_RATE_MCS4 = 19,
	ATH_RATE_MCS5 = 20,
	ATH_RATE_MCS6 = 21,
	ATH_RATE_MCS7 = 22,
	ATH_RATE_MCS8 = 23,
	ATH_RATE_MCS9 = 24,
	ATH_RATE_MCS10=25,
	ATH_RATE_MCS11=26,
	ATH_RATE_MCS12=27,
	ATH_RATE_MCS13=28,
	ATH_RATE_MCS14=29,
	ATH_RATE_MCS15=30,
}WLAN_AT_RATE_VALUE;

/*Enable WIFI, return value:  success¡G0¡Afail¡G-1*/
int32_t WlanATSetWifiEnable(WLAN_AT_WIENABLE_TYPE onoff);
WLAN_AT_WIENABLE_TYPE WlanATGetWifiEnable(void);

/*set wifi mode, return value:  success¡G0¡Afail¡G-1*/
int32_t WlanATSetWifiMode(WLAN_AT_WIMODE_TYPE mode);
/* Retrieve current mode, output value: (string)the number of mode defined above*/
int32_t WlanATGetWifiMode(WLAN_AT_BUFFER_STRU *strBuf);
/* Retrieve all the mode supported,  output value: string*/
int32_t WlanATGetWifiModeSupport(WLAN_AT_BUFFER_STRU *strBuf);

/*set the bandwidth*/
int32_t WlanATSetWifiBand(WLAN_AT_WIBAND_TYPE width);
/* Retrieve current band width, output value: (string)the number of width defined above */
int32_t WlanATGetWifiBand(WLAN_AT_BUFFER_STRU *strBuf);
/* Retrieve all the band width supported,  output value: string */
int32_t WlanATGetWifiBandSupport(WLAN_AT_BUFFER_STRU *strBuf);

/*set the frequency*/
int32_t WlanATSetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq);
/*Retrieve the current frequency*/
int32_t WlanATGetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq);

/*Set the Tx state*/
int32_t WlanATSetWifiTX(int txType);

/*Set the Rx state*/
int32_t WlanATSetWifiRX(WLAN_AT_FEATURE_TYPE onoff);
/*Get the tx control*/
WLAN_AT_FEATURE_TYPE WlanATGetWifiTX(void);

/*Set the Tx power*/
int WlanATSetWifiTxPower(int powervalue);

/*Get the Tx power*/
int WlanATGetWifiTxPower(void);

int WlanATSetRate(WLAN_AT_RATE_VALUE ratevalue);

int WlanATGetRate(void);

int WlanATSetWifiAntenna(int antenna);

int WlanATGetWifiAntenna(void);
/* for unit test of test usage */
void unittest(void);
int WlanATSetWifiTPC(int pmc);
int WlanATSetWifiPktSize(int size);
void WlanATSetPaCfg(int val);
void WlanATSetDacGain(int val);
void WlanATSetGainIdx(int val);
void WlanATSetNumPkt(int val);
void WlanATSetAgg(int val);
void WlanATSetStbc(int val);
void WlanATSetLdpc(int val);
void WlanATSetWlanMode(int val);
void WlanATSetLPreamble();
void WlanATinit();
#endif /* CONFIG_FTM_WLAN */
#endif /* FTM_WLAN_H_ */
