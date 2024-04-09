/*==========================================================================

                     FTM WLAN Source File

# Copyright (c) 2011, 2013-2015 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

===========================================================================*/

/*===========================================================================

                         Edit History


when       who       what, where, why
--------   ---       ----------------------------------------------------------
07/11/11   karthikm  Wrapper that contains routines for directing FTM commands
                     sent from host to the IOCTL calls of Atheros driver.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/limits.h>

//#include "comdef.h"

#include "testcmd6174.h"
#include "libtcmd.h"
#include "myftm_wlan.h"
#include "myftm_dbg.h"

#define INVALID_FREQ    0
#define A_RATE_NUM      28
#define G_RATE_NUM      28
#define RATE_STR_LEN    20

#ifdef CONFIG_FTM_WLAN_AUTOLOAD
#define MODULE_FILE             "/proc/modules"
#define DRIVER_MODULE_TAG       "wlan"
#define WLAN_CFG_FILE           "/persist/wlan_mac.bin"
/* Offset for set mac address cmd */
#define MAIN_CMD_OFFSET         16
#define SUB_CMD_OFFSET          24
#define LENGTH_OFFSET           32
#define NMAC_OFFSET             48
#define PMAC_OFFSET             49

#if defined(ANDROID)
#if defined(BOARD_HAS_ATH_WLAN_AR6320)
#if BOARD_HAS_ATH_WLAN_AR6320
#define FTM_WLAN_LOAD_CMD       "/system/bin/insmod " \
                                "/system/lib/modules/wlan.ko con_mode=5"
#define FTM_WLAN_UNLOAD_CMD     "/system/bin/rmmod wlan"
#endif
#endif
#elif defined(MDM9635_LE)
#define FTM_WLAN_LOAD_CMD       "/etc/init.d/wlan start_ftm"
#define FTM_WLAN_UNLOAD_CMD     "/etc/init.d/wlan stop"
#else
#if defined(BOARD_HAS_ATH_WLAN_AR6320)
#define FTM_WLAN_LOAD_CMD       "/sbin/insmod " \
                                "/lib/modules/wlan.ko con_mode=5"
#define FTM_WLAN_UNLOAD_CMD     "/sbin/rmmod wlan"

#else
#warning "Load and Unload driver may not work!"
#endif
#endif

typedef enum {
    SUBCMD_DRIVER_LOAD      = 'L',
    SUBCMD_DRIVER_UNLOAD    = 'U',
    SUBCMD_DRIVER_AUTO_MODE = 'A',
} sub_cmds;

extern _CMD_PARM gCmd;

static int load_wifi_driver_testmode(void);
static int unload_wifi_driver(void);
static bool is_wifi_driver_loaded(char *mod_tag);
static bool flag_driver_auto_load = false;
#endif /* CONFIG_FTM_WLAN_AUTOLOAD */

bool ifs_init[32]  = {false};
char g_ifname[IFNAMSIZ] = "wlan";

typedef enum {
    TCMD_CONT_TX_OFF = 0,
    TCMD_CONT_TX_SINE,
    TCMD_CONT_TX_FRAME,
    TCMD_CONT_TX_TX99,
    TCMD_CONT_TX_TX100,
    TCMD_CONT_TX_OFFSETTONE,
    TCMD_CONT_TX_PSAT_CAL,
    TCMD_CONT_TX_CWTONE,
    TCMD_CONT_TX_CLPCPKT,
} TCMD_CONT_TX_MODE;
int gTxType = TCMD_CONT_TX_TX99;
int gWifiMode = AT_WIMODE_80211a;

void print_uchar_array(uint8_t *addr, int len)
{
   int i;
   for (i = 0;i< len; i++)
      DPRINTF(FTM_DBG_TRACE, "%02X ", addr[i]);
   DPRINTF(FTM_DBG_TRACE, "\n");
}

void print_uint16_array(uint16_t *addr, int len)
{
   int i;
   for (i = 0;i< len; i++)
      DPRINTF(FTM_DBG_TRACE, "%02X %02X ", addr[i]>>8, addr[i]&0xFF);
   DPRINTF(FTM_DBG_TRACE, "\n");
}

#ifdef CONFIG_FTM_WLAN_AUTOLOAD
/*===========================================================================
FUNCTION
  load_wifi_driver_testmode

DESCRIPTION
  Use system call to load driver

DEPENDENCIES
  NIL

RETURN VALUE
  NONE

SIDE EFFECTS
  NONE
===========================================================================*/

static int load_wifi_driver_testmode(void)
{
    int ret = 0;

    /* clean-up the driver state */
    if ((ret = unload_wifi_driver())) {
        DPRINTF(FTM_DBG_ERROR, "%s: Unload driver failed: %d\n", __func__, ret);
        return ret;
    }

#ifdef FTM_WLAN_LOAD_CMD
    if ((ret = system(FTM_WLAN_LOAD_CMD))) {
        DPRINTF(FTM_DBG_ERROR, "WLAN driver load failed!\n");
        return ret;
    }
#else
#error "FTM_WLAN_LOAD_CMD is not defined!"
#endif

    DPRINTF(FTM_DBG_TRACE, "WLAN driver loaded in FTM mode successfully!\n");

    return ret;
}
/*===========================================================================
FUNCTION
  Unload_wifi_driver if the drvier is detected existing already

DESCRIPTION
  Use system call to unload driver

DEPENDENCIES
  NIL

RETURN VALUE
  NONE

SIDE EFFECTS
  NONE
===========================================================================*/
static int unload_wifi_driver(void)
{
    int ret = 0;

    if (is_wifi_driver_loaded(DRIVER_MODULE_TAG)) {
#ifdef FTM_WLAN_UNLOAD_CMD
        if ((ret = system(FTM_WLAN_UNLOAD_CMD))) {
            DPRINTF(FTM_DBG_ERROR, "WLAN driver unload failed!\n");
            return ret;
        }
#else
#error "FTM_WLAN_UNLOAD_CMD is not defined!"
#endif
    }

    DPRINTF(FTM_DBG_TRACE, "WLAN driver unloaded successfully!\n");

    return ret;
}

/*===========================================================================
FUNCTION
  is_wifi_driver_loaded

DESCRIPTION
  Check if WLAN driver is loaded or not

DEPENDENCIES
  NIL

RETURN VALUE
  Returns true if driver already loaded, false if driver not loaded

SIDE EFFECTS
  NONE
===========================================================================*/
static bool is_wifi_driver_loaded(char *mod_tag)
{
    FILE *proc = NULL;
    char cmd[NAME_MAX + 64]; /* File name max + room for command */
    bool ret = false;

    snprintf(cmd, sizeof(cmd), "cat /proc/modules | grep %s", mod_tag);

    proc = popen(cmd, "r");

    if (proc == NULL) {
        DPRINTF(FTM_DBG_ERROR, "%s failed!\n", __func__);
        return ret;
    }

    if (fread (cmd, 1, sizeof(cmd), proc) > 0)
        ret = true;

    fclose(proc);

    return ret;
}
#endif /* CONFIG_FTM_WLAN_AUTOLOAD */

int32_t WlanATSetWifiEnable(WLAN_AT_WIENABLE_TYPE onoff)
{
    int ret = 0;

    DPRINTF(FTM_DBG_TRACE, "%s: onoff parameter is %d\n", __func__, onoff);

    if (AT_WIENABLE_TEST == onoff) {
        ret = load_wifi_driver_testmode();
DPRINTF(FTM_DBG_TRACE, "%s:******************* load_wifi_driver_testmode %d\n", __func__, ret);
        if (0 == ret)
        { // success and giving initial values
            qca6174ApiInit();
            qca6174SetBssid("50:55:55:55:55:05");
            qca6174SetTxStation("20:22:22:22:22:02");
            qca6174SetRxStation("ff:ff:ff:ff:ff:ff");
            qca6174ChannelSet(11);

	      WlanATSetWifiMode(AT_WIMODE_80211b);
	      WlanATSetWifiBand(AT_WIBAND_20M);//ignored for not 11n/11ac mode
	      WlanATSetRate(11);//ATH_RATE_54M
            qca6174TxPowerSet(20);
            qca6174SetAntenna(1);
            qca6174TxPacketSizeSet(1200);
        }

qca6174SetAntenna(1);
    }
    else if (AT_WIENABLE_OFF == onoff) {
        ret = unload_wifi_driver();
        if (0 == ret) { //success
            qca6174ApiCleanup();
        }
    }
    else {
        DPRINTF(FTM_DBG_ERROR, "%s failed, invalid command!\n", __func__);
        ret = -1;
    }

    return ret;
}

WLAN_AT_WIENABLE_TYPE WlanATGetWifiEnable(void)
{
    bool bLoaded;
    int ret = AT_WIENABLE_OFF;
    bLoaded = is_wifi_driver_loaded(DRIVER_MODULE_TAG);
    switch (bLoaded)
    {
        case true:
            ret = AT_WIENABLE_TEST;
        break;
        case false:
        default:
            ret = AT_WIENABLE_OFF;
        break;
    }
    DPRINTF(FTM_DBG_TRACE, "%s: return as %d\n", __func__, ret);
    return ret;
}

/*set wifi mode, return value:  success 0 fail -1
  wlan_mode is converted from getDataRateAndWlanMode given the rate
 */
int32_t WlanATSetWifiMode(WLAN_AT_WIMODE_TYPE mode)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: mode parameter as %d\n", __func__, mode);
    gWifiMode = mode;    // set in global variable so that it can be shared with bandwidth setting and other parameters/functions
    if (AT_WIMODE_CW == mode) {
        qca6174RateSet(1);    // give a fake rate
        qca6174SetBandWidth(0);
    }
    else if (AT_WIMODE_80211a == mode) {
        qca6174RateSet(4);    // give 6Mbps as default rate
        qca6174SetBandWidth(0);
    }
    else if (AT_WIMODE_80211b == mode) {
        qca6174RateSet(1);    // give 1Mbps as default rate
        qca6174SetBandWidth(0);
    }
    else if (AT_WIMODE_80211g == mode) {
        qca6174RateSet(4);    // give 6Mbps as default rate
        qca6174SetBandWidth(0);
    }
    else if (AT_WIMODE_80211n == mode) {
        qca6174RateSet(15);    // give MCS0 as default rate
        qca6174SetBandWidth(1);    // give HT20 as default rate
    }
    else if (AT_WIMODE_80211ac == mode) {
        qca6174RateSet(15);    // give MCS0 as default rate
        qca6174SetBandWidth(4);    // give VHT20 as default rate
    }
    else {
        DPRINTF(FTM_DBG_ERROR, "%s failed, invalid command!\n", __func__);
        ret = -1;
    }
    return ret;
}

/* Retrieve current mode, output value: (string)the number of mode defined above*/
int32_t WlanATGetWifiMode(WLAN_AT_BUFFER_STRU *strBuf)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: return as %s\n", __func__, strBuf);
    return ret;
}

/* Retrieve all the mode supported,  output value: string*/
int32_t WlanATGetWifiModeSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    int ret = 0;
    return ret;
}

/*set the bandwidth, look at values defined in getMcsWlanMode*/
int32_t WlanATSetWifiBand(WLAN_AT_WIBAND_TYPE width)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: bandwidth parameter as %d\n", __func__, width);
    if (AT_WIBAND_20M == width) {
        if (AT_WIMODE_80211n == gWifiMode)
            qca6174SetBandWidth(1);
        else if (AT_WIMODE_80211ac == gWifiMode)
            qca6174SetBandWidth(4);
    }
    else if (AT_WIBAND_40M == width) {
        if (AT_WIMODE_80211n == gWifiMode)
            qca6174SetBandWidth(2);
        else if (AT_WIMODE_80211ac == gWifiMode)
            qca6174SetBandWidth(5);
    }
    else if (AT_WIBAND_80M == width) {
        qca6174SetBandWidth(3);
    }
    else if (AT_WIBAND_160M == width) {
        DPRINTF(FTM_DBG_ERROR, "%s failed, not supported bandwidth (%d)\n", __func__, width);
        ret = -1;
    }
    else {
        DPRINTF(FTM_DBG_ERROR, "%s failed, invalid command!\n", __func__);
        ret = -1;
    }
    return ret;
}

/* Retrieve current band width, output value: (string)the number of width defined above */
int32_t WlanATGetWifiBand(WLAN_AT_BUFFER_STRU *strBuf)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: return as %s\n", __func__, strBuf);
    return ret;
}

/* Retrieve all the band width supported,  output value: string */
int32_t WlanATGetWifiBandSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: return as %s\n", __func__, strBuf);
    return ret;
}

/*set the frequency*/
int32_t WlanATSetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: freq parameter as value (%u), offset (%d)\n", __func__, pFreq->value, pFreq->offset);
    qca6174FreqSet(pFreq->value);
    return ret;
}

/*Retrieve the current frequency*/
int32_t WlanATGetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: return as %u\n", __func__, pFreq->value);
    return ret;
}

/*Set the Tx state*/
int32_t WlanATSetWifiTX(int txType)
{
    int ret = 0;

    DPRINTF(FTM_DBG_INFO, "%s: tx type is %d \n", __func__, txType);
    gTxType = txType;
    if (TCMD_CONT_TX_OFF == txType)
        qca6174TxStop();
    else if (TCMD_CONT_TX_SINE == txType)
	qca6174TxSineStart();
    else if (TCMD_CONT_TX_FRAME == txType)
	qca6174TxFrameStart();
    else if (TCMD_CONT_TX_TX99 == txType)
        qca6174Tx99Start();
    else
        DPRINTF(FTM_DBG_ERROR, "%s: tx type:%d not supported!\n", __func__, txType);

    return ret;
}
/*Set the Rx state*/
int32_t WlanATSetWifiRX(WLAN_AT_FEATURE_TYPE onoff)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: onoff parameter as (%d)\n", __func__, onoff);
    if (AT_FEATURE_TYPE_ON == onoff) {
        qca6174RxPacketStart();
    }else if(AT_FEATURE_TYPE_OFF == onoff) {
        qca6174RxPacketStop();
    }
    return ret;
}

/*Get the tx control*/
WLAN_AT_FEATURE_TYPE WlanATGetWifiTX(void)
{
    int ret = 0;
    DPRINTF(FTM_DBG_TRACE, "%s: return as %u\n", __func__, ret);
    return ret;
}
/*Set the Tx power*/
int WlanATSetWifiTxPower(int powervalue)
{
    int ret = 1;
    DPRINTF(FTM_DBG_TRACE, "%s: Set tx power parameter as (%d)\n", __func__, powervalue);
    qca6174TxPowerSet(powervalue);
    return ret;
}

int WlanATSetWifiTPC(int pmc)
{
    int ret = 1;
    DPRINTF(FTM_DBG_TRACE, "%s: Set tx power control parameter as (%d)\n",
                 __func__, pmc);
    qca6174TxPcmSet(pmc);
    return ret;
}
/*Get the tx power*/
int WlanATGetWifiTxPower(void)
{

  //  DPRINTF(FTM_DBG_TRACE, "%s: return tx power as %d\n", __func__, gCmd.txPwr);
    return 0;
}

/*Set the Tx rate*/
int WlanATSetRate(WLAN_AT_RATE_VALUE ratevalue)
{
    int ret = 1;
    DPRINTF(FTM_DBG_TRACE, "%s: Set rate as (%d)\n", __func__, ratevalue);

    qca6174RateSet(ratevalue);
    return ret;
}

/*Get the tx rate*/
int WlanATGetRate(void)
{

    DPRINTF(FTM_DBG_TRACE, "%s: return rate as %d\n", __func__, gCmd.rate);
    return 0;
}

/*Set the tx antenna*/
int WlanATSetWifiAntenna(int antenna)
{

    int ret = 1;
    DPRINTF(FTM_DBG_TRACE, "%s: Set antenna as (%d)\n", __func__, antenna);

    qca6174SetAntenna(antenna);
    return ret;
}
/*Get the tx antenna*/
int WlanATGetWifiAntenna(void)
{

   // DPRINTF(FTM_DBG_TRACE, "%s: return rate as %d\n", __func__, gCmd.rate);
    return 0;
}

int WlanATSetWifiPktSize(int size)
{
    int ret = 1;
    DPRINTF(FTM_DBG_TRACE, "%s: Set packet size as (%d)\n", __func__, size);

    qca6174TxPacketSizeSet(size);
    return ret;
}

void WlanATSetPaCfg(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set packet PaCfg (%d)\n", __func__, val);
    qca6174SetPaCfg(val);
}

void WlanATSetDacGain(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set DacGain as (%d)\n", __func__, val);
    qca6174SetDacGain(val);
}

void WlanATSetGainIdx(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set GainIdx as (%d)\n", __func__, val);
    qca6174SetGainIdx(val);
}

void WlanATSetNumPkt(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set NumPkt as (%d)\n", __func__, val);
    qca6174SetNumPkt(val);
}

void WlanATSetAgg(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set aggregation as (%d)\n", __func__, val);
    qca6174SetAgg(val);
}

void WlanATSetStbc(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set STBC as (%d)\n", __func__, val);
    qca6174SetStbc(val);
}

void WlanATSetLdpc(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set LDPC as (%d)\n", __func__, val);
    qca6174SetLdpc(val);
}

void WlanATSetWlanMode(int val)
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set LDPC as (%d)\n", __func__, val);
    qca6174SetWlanMode(val);
}

void WlanATSetLPreamble()
{
    DPRINTF(FTM_DBG_TRACE, "%s: Set preamble as L\n", __func__);
    qca6174SetLPreamble();
}

void WlanATinit()
{
    qca6174init();
}

void unittest(void)
{
    qca6174ApiInit();

	qca6174SetBssid("50:55:55:55:55:05");
	qca6174SetTxStation("20:22:22:22:22:02");
	qca6174SetRxStation("ff:ff:ff:ff:ff:ff");

	qca6174ChannelSet(11);
	qca6174RateSet(13);
	qca6174TxPowerSet(20);
	qca6174SetAntenna(1);
	qca6174TxPacketSizeSet(1200);

	//qca6174TxFrameStart();
	//qca6174TxSineStart();
	qca6174Tx99Start();
	//qca6174TxStop();

	//qca6174ChannelSet(6);
	//qca6174RateSet(ATH_RATE_6M);
	//qca6174SetChain(1);

	//qca6174SetAntenna(1);
	//qca6174SetBssid("01:00:00:c0:ff:ee");
	//qca6174SetAddr("01:00:00:c0:ff:ee");

	//qca6174RxPacketStart();
	//sleep(1);
	//qca6174RxPacketStop();

//	qca6174ApiCleanup();
}
