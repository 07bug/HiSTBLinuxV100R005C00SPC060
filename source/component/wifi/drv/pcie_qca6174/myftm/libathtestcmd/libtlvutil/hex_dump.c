/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#include "wlantype.h"

#ifdef USE_GLIB
#include <glib.h>
#define strlcat g_strlcat
#define strlcpy g_strlcpy
#endif

void print_hex_dump(void *buf, size_t len)
{
	uint8_t *ptr = buf;
	uint32_t i;

	for (i = 0; i < len; i ++) {
		printf("%.2x ", *ptr++);
		if ((i+1)%16) ;
		else
			printf("\n");
	}
	printf("\n");
}


