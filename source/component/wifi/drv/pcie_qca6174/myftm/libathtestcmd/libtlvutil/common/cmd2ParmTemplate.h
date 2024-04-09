
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_2_PARM_TEMPLATE_H)
#define _CMD_2_PARM_TEMPLATE_H

#include "parmTxtTemplate.h"

typedef struct _testFlowCmdParmTemplate {
	uint32_t                     numParms;
	_TESTFLOW_TXT_PARM_TEMPLATE *parmTemplate;
} __ATTRIB_PACK _TESTFLOW_CMD_PARM_TEMPLATE;

#endif // #if !defined(_CMD_2_PARM_TEMPLATE_H)

