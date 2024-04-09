
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_TEST_CMD_PARMS_BIN_TEMPLATE)
#define _TEST_CMD_PARMS_BIN_TEMPLATE

#include <stdint.h>
#include "art_utf_common.h"

typedef struct _parmBinTemplate {
	uint32_t offset;
	uint32_t len;
} __ATTRIB_PACK _PARM_BIN_TEMPLATE;

#endif // #if !defined(_TEST_CMD_PARMS_BIN_TEMPLATE)

