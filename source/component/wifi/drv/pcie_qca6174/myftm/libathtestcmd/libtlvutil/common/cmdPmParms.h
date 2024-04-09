
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_PM_PARM_TEMPLATE)
#define _CMD_PM_PARM_TEMPLATE

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

//#include "parmBinTemplate.h"

typedef enum {
	_setRegParm_code_mode=0,
} CMD_PM_PARMS_CODE;

typedef struct _pmParm {
	uint32_t  mode;
} __ATTRIB_PACK _CMD_PM_PARMS;


extern _PARM_BIN_TEMPLATE _pmParm_bin_template[];

#endif // #if !defined(_CMD_PM_PARM_TEMPLATE)

