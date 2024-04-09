
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_TEST_CMD_PARMS_TXT_TEMPLATE)
#define _TEST_CMD_PARMS_TXT_TEMPLATE

#include <string.h>
#include <stdint.h>

#if defined(_HOST_SIM_TESTING)
#include "otaHostCommon.h"
#else
#include "osapi.h"
#define KEY_SIZE_MAX 16
#endif
#include "wlantype.h"
#include "art_utf_common.h"

typedef struct _testFlowTxtParmTemplate {
	char     parm[KEY_SIZE_MAX];
	uint32_t parmType;
	uint32_t offset;
	size_t   len;
} __ATTRIB_PACK _TESTFLOW_TXT_PARM_TEMPLATE;

#endif // #if !defined(_TEST_CMD_PARMS_TXT_TEMPLATE)

