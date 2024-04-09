
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_NARTCMD_PARM_TEMPLATE)
#define _CMD_NARTCMD_PARM_TEMPLATE

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

//#include "parmBinTemplate.h"

typedef enum {
	_nartCmdParm_code_commandId=0,
	_nartCmdParm_code_param1=1,
	_nartCmdParm_code_param2=2,
	_nartCmdParm_code_param3=3,
	_nartCmdParm_code_data=4,
} CMD_NARTCMD_PARMS_CODE;

typedef struct _nartCmdParm {
	uint32_t  commandId;
	uint32_t  param1;
	uint32_t  param2;
	uint32_t  param3;
	uint8_t   data[ 1024 ];
} __ATTRIB_PACK _CMD_NARTCMD_PARMS;


extern _PARM_BIN_TEMPLATE _nartCmdParm_bin_template[];

#endif // #if !defined(_CMD_NARTCMD_PARM_TEMPLATE)

