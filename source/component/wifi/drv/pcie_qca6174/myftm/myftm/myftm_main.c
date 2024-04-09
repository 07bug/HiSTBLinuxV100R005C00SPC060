/*==========================================================================

                     FTM Main Task Source File

Description
  Unit test component file for regsitering the routines to Diag library
  for BT and FTM commands

# Copyright (c) 2012-2015  Qualcomm Technologies, Inc.
# All Rights Reserved.
# Qualcomm Technologies Proprietary and Confidential.

===========================================================================

                         Edit History


when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/18/10   rakeshk  Created a source file to implement routines for
                    registering the callback routines for FM and BT FTM
                    packets
07/06/10   rakeshk  changed the name of FM common header file in inclusion
07/07/10   rakeshk  Removed the sleep and wake in the main thread loop
===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <net/if.h>
#include <stdint.h>
#include <dirent.h>
#include <pwd.h>
//#include <cutils/sched_policy.h>
#include <ctype.h>
#include <getopt.h>

#include "myftm_dbg.h"
#include "myftm_wlan.h"

#ifdef USE_GLIB
#include <glib.h>
#define strlcat g_strlcat
#define strlcpy g_strlcpy

#else
#include <string.h>
#define strlcat strncat
#define strlcpy strncpy
#endif

static char *progname = NULL;
unsigned int g_dbg_level = FTM_DBG_TRACE | FTM_DBG_ERROR;

static void usage(void)
{
    fprintf(stderr, "\nusage: %s [options] \n"
            "   -n, --nodaemon      do not run as a daemon\n"
            "   -d                  show more debug messages (-dd for even more)\n"
#ifdef CONFIG_FTM_BT
            "   -b, --board-type    Board Type\n"
#endif
#ifdef CONFIG_FTM_WLAN
            "   -i <wlan interface>\n"
            "       --interface=<wlan interface>\n"
            "                       wlan adapter name (wlan, eth, etc.) default wlan\n"
#endif
            "       --help          display this help and exit\n"
            , progname);
    exit(EXIT_FAILURE);
}

/*===========================================================================
FUNCTION   main

DESCRIPTION
  Initialises the Diag library and registers the PKT table for FM and BT
  and daemonises

DEPENDENCIES
  NIL

RETURN VALUE
  NIL, Error in the event buffer will mean a NULL App version and Zero HW
  version

SIDE EFFECTS
  None

===========================================================================*/

int main(int argc, char *argv[])
{
    int c;
    static struct option options[] =
    {
        {"help", no_argument, NULL, 'h'},
#ifdef CONFIG_FTM_WLAN
        {"interface", required_argument, NULL, 'i'},
#endif
#ifdef CONFIG_FTM_BT
        {"board-type", required_argument, NULL, 'b'},
#endif
        {"nodaemon", no_argument, NULL, 'n'},
		{"SetWifiEnable", required_argument, NULL, 'e'},
		{"GetWifiEnable", no_argument, NULL, 'E'},
		{"SetWifiMode", required_argument, NULL, 'm'},
		{"SetWlanMode", required_argument, NULL, 'M'},
		{"GetWifiModeSupport", required_argument, NULL, 'S'},
		{"WlanATSetWifiBand", required_argument, NULL, 'w'},
		{"WlanATSetWifiBand", no_argument, NULL, 'W'},
		{"WlanATSetRate", required_argument, NULL, 'r'},
		{"WlanATSetRate", required_argument, NULL, 'R'},
		{"WlanATSetGainIdx", required_argument, NULL, 'G'},
		{"WlanATSetDacGain", required_argument, NULL, 'D'},
		{"WlanATSetPaCfg", required_argument, NULL, 'C'},
		{"WlanATSetNumPkt", required_argument, NULL, 'j'},
		{"WlanATSetAgg", required_argument, NULL, 'k'},
		{"WlanATSetWifiFreq", required_argument, NULL, 'f'},
		{"WlanATGetWifiFreq", no_argument, NULL, 'F'},
             {"WlanATSetWifiTxPower", required_argument,NULL, 'p'},
             {"WlanATGetWifiTxPower", no_argument,NULL, 'P'},
             {"WlanATSetWifiAntenna", required_argument, NULL, 'a'},
             {"WlanATGetWifiAntenna", no_argument, NULL, 'A'},
		{"WlanATSetWifiPktSize", required_argument, NULL, 's'},
		{"WlanATSetWifiTPC", required_argument, NULL, 'c'},
		{"WlanATSetWifiTX", required_argument, NULL, 't'},
		{"WlanATGetWifiTX", no_argument, NULL, 'T'},
		{"WlanATSetWifiRX", required_argument, NULL, 'x'},
		{"WlanATSetStbc", required_argument, NULL, 'y'},
		{"WlanATSetLdpc", required_argument, NULL, 'z'},
		{"WlanATSetLPreamble", no_argument, NULL, 'l'},
        {"unittest", no_argument, NULL, 'u'},
        {0, 0, 0, 0}
    };
    int daemonize = 0;
    int int_parm = 0;
    WLAN_AT_WIFREQ_STRU freq_parm;
    progname = argv[0];

printf("Version Flags: aaa\n");
    WlanATinit();

    while (1)
    {
        c = getopt_long(argc, argv,
	"hdi:nb:e:Em:S:w:Wr:Rg:f:Fp:Pt:Tua:Ax:s:C:c:D:k:G:j:y:z:lM: ", options, NULL);

        if (c < 0)
            break;

        switch (c)
        {
#ifdef CONFIG_FTM_WLAN
        case 'i':
            strlcpy(g_ifname, optarg, IFNAMSIZ);
            break;
#endif
        case 'n':
            daemonize = 0;
            break;
        case 'd':
#ifdef DEBUG
            g_dbg_level = g_dbg_level << 1 | 0x1;
#else
            printf("Debugging disabled, please build with -DDEBUG option\n");
            exit(EXIT_FAILURE);
#endif
            break;
        case 'e':
            fprintf(stderr, "SetWifiEnable using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiEnable(int_parm);
            break;
        case 'E':
            fprintf(stderr, "GetWifiEnable using athtestcmdlib\n");
            int_parm = WlanATGetWifiEnable();
            fprintf(stderr, "WlanATGetWifiEnable return as %d\n", int_parm);
            break;
        case 'm':
            fprintf(stderr, "SetWifiMode using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiMode(int_parm);
            break;
        case 'w':
            fprintf(stderr, "WlanATSetWifiBand using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiBand(int_parm);
            break;
        case 'f':
            fprintf(stderr, "WlanATSetWifiFreq using athtestcmdlib\n");
            int_parm = atoi(optarg);
            freq_parm.value = int_parm;
            freq_parm.offset = 0;
            WlanATSetWifiFreq(&freq_parm);
            break;
	case 'p':
            fprintf(stderr, "WlanATSetWifiTxPower using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiTxPower(int_parm);
            break;
	case 'P':
            fprintf(stderr, "WlanATGetWifiTxPower using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATGetWifiTxPower();
            break;
	 case 'r':
            fprintf(stderr, "WlanATSetRate using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetRate(int_parm);
            break;
	 case 'R':
            fprintf(stderr, "WlanATGetRate using athtestcmdlib\n");

            WlanATGetRate();
            break;
       case 'a':
            fprintf(stderr, "WlanATSetWifiAntenna using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiAntenna(int_parm);
            break;
	 case 'A':
            fprintf(stderr, "WlanATGetWifiAntenna using athtestcmdlib\n");

            WlanATGetWifiAntenna();
            break;

        case 't':
            fprintf(stderr, "WlanATSetWifiTX using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiTX(int_parm);
            exit(EXIT_SUCCESS);
            break;

	 case 'x':
            fprintf(stderr, "WlanATSetWifiRX using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiRX(int_parm);
            exit(EXIT_SUCCESS);
            break;

        case 'u':
            fprintf(stderr, "unittest using athtestcmdlib\n");
            unittest();
            exit(EXIT_SUCCESS);
            break;

        case 's':
            fprintf(stderr, "WlanATSetWifiPktSize using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiPktSize(int_parm);
            break;

        case 'c':
            fprintf(stderr, "WlanATSetWifiTPC using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWifiTPC(int_parm);
            break;

        case 'C':
            fprintf(stderr, "WlanATSetPaCfg using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetPaCfg(int_parm);
            break;

        case 'D':
            fprintf(stderr, "WlanATSetDacGain using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetDacGain(int_parm);
            break;

        case 'G':
            fprintf(stderr, "WlanATSetGainIdx using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetGainIdx(int_parm);
            break;

        case 'j':
            fprintf(stderr, "WlanATSetNumPkt using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetNumPkt(int_parm);
            break;

        case 'k':
            fprintf(stderr, "WlanATSetAgg using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetAgg(int_parm);
            break;

        case 'y':
            fprintf(stderr, "WlanATSetStbc using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetStbc(int_parm);
            break;

        case 'z':
            fprintf(stderr, "WlanATSetLtbc using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetLdpc(int_parm);
            break;

        case 'M':
            fprintf(stderr, "WlanATSetLtbc using athtestcmdlib\n");
            int_parm = atoi(optarg);
            WlanATSetWlanMode(int_parm);
            break;

        case 'l':
            fprintf(stderr, "WlanATSetLPreamble using athtestcmdlib\n");
            WlanATSetLPreamble();
            break;

        case 'h':
            DPRINTF(FTM_DBG_TRACE, "FTM Daemon calling LSM init\n");
        default:
            usage();
            break;
        }
    }

    if (optind < argc)
        usage();

    if (daemonize && daemon(0, 0))
    {
        perror("daemon");
        exit(EXIT_FAILURE);
    }

    DPRINTF(FTM_DBG_TRACE, "FTM Daemon calling LSM init\n");

    exit(EXIT_SUCCESS);
}

