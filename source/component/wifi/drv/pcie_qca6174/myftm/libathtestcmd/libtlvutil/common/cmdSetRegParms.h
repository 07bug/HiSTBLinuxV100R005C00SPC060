
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_SETREG_PARM_TEMPLATE)
#define _CMD_SETREG_PARM_TEMPLATE

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

//#include "parmBinTemplate.h"

typedef enum {
	_setRegParm_code_regAddr=0,
	_setRegParm_code_value,
	_setRegParm_code_flag,
} CMD_SETREG_PARMS_CODE;

typedef struct _setRegParm {
	uint32_t  regAddr;
	uint32_t  value;
	uint16_t  flag;
} __ATTRIB_PACK _CMD_SETREG_PARMS;


extern _PARM_BIN_TEMPLATE _setRegParm_bin_template[];

#endif // #if !defined(_CMD_SETREG_PARM_TEMPLATE)

