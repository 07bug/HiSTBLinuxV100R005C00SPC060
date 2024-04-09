/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_OPCODE_TEMPLATE_H)
#define  _CMD_OPCODE_TEMPLATE_H

typedef struct _cmdOpCodeHandlers {
	_PARM_BIN_TEMPLATE * (*_CmdOpCodeTemplate)();
} __ATTRIB_PACK _CMD_OPCODE_HANDLERS;

uint8_t getCmdOpCodeTemplateSize();

#endif

