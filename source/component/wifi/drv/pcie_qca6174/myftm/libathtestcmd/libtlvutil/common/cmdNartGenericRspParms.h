
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_NARTRSP_PARM_TEMPLATE)
#define _CMD_NARTRSP_PARM_TEMPLATE

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

//#include "parmBinTemplate.h"

typedef enum {
	_nartRspParm_code_commandId=0,
	_nartRspParm_code_status=1,
	_nartRspParm_code_length=2,
	_nartRspParm_code_data=3,
} CMD_NARTRSP_PARMS_CODE;

typedef struct _nartRspParm {
	uint32_t  commandId;
	uint32_t  status;
	uint32_t  length;
	uint8_t   data[ 1024 ];
} __ATTRIB_PACK _CMD_NARTRSP_PARMS;


extern _PARM_BIN_TEMPLATE _nartRspParm_bin_template[];

#endif // #if !defined(_CMD_NARTRSP_PARM_TEMPLATE)

