
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_HOST_COMMMON_H)
#define _HOST_COMMMON_H

#define LINEBUF_SIZE 256
#define KEY_SIZE_MAX 72
#define FILENAME_SIZE 64

#define FALSE 0
#define TRUE  1

#if defined(_HOST_SIM_TESTING)
#define A_PRINTF printf
#define ATH_MAC_LEN  6
#endif

#endif //#if !defined(_HOST_COMMMON_H)
