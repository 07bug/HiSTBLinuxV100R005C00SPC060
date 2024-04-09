/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(_HOST_SIM_TESTING)
#include "otaHostCommon.h"
#else
#include "osapi.h"
#endif
#include "wlantype.h"
#include "cmdStream.h"
#include "parmBinTemplate.h"
#include "parseBinCmdStream.h"
#include "testUtil.h"
#include "cmdStream.h"
#include "cmdAllParms.h"
#include "cmdProcessingSM.h"
#include "cmd2ParmTemplate.h"
#include "cmdOpCodeTemplate.h"
#include "parseRxBinCmdTlv.h"

#include "hex_dump.h"

extern _TESTFLOW_CMD_PARM_TEMPLATE TestFlowCmd2ParmTemplate[];
extern int searchTestFlowParmTemplate(char *key, _TESTFLOW_TXT_PARM_TEMPLATE *parmTemplate, uint32_t numOfTemplateParms, uint32_t *parmCode, uint32_t *parmType, uint32_t *parmSize);

extern _CMD_OPCODE_HANDLERS CmdOpCodeTemplate[];
static uint8_t numOfParms=0;
static uint8_t opCodeTLV=0;
static _TESTFLOW_CMD_STREAM *cmdStream;

static int binCmdStreamParser_Ver1(uint8_t *stream, uint32_t readStreamLen)
{
	int rc=TRUE;
	uint16_t *pHalf=(uint16_t*)stream;
	uint16_t streamLen;
	//uint16_t payloadPos, cmdIdx;
	//uint8_t *payload;
	_ONE_CMD_HEADER *oneCmdHeader;

	// checkSum verification
	cmdStream=(_TESTFLOW_CMD_STREAM *)stream;
	streamLen = sizeof(_TESTFLOW_CMD_STREAM_HEADER) + cmdStream->cmdStreamHeader.length;

	if (readStreamLen != streamLen) {
		printf("Incorrect stream length %d, should be %d\n", readStreamLen, streamLen);
		return(FALSE);
	}

	if (!verifyChecksum(pHalf, streamLen/2)) {
		printf("Incorrect checksum\n");
		return(FALSE);
	}

	// bypass cmd processing for legacy suport, e.g. ART
	if (( cmdStream->cmdStreamHeader.header & CMD_STERAM_HEADER_EXTENDED_RESERVED) &&
			( cmdStream->cmdStreamHeader.headerExtended & CMD_STREAM_HEADER_EXTENDED_BYTESTREAM_BYPASS)) {
		return(TRUE);
	}

	oneCmdHeader = (_ONE_CMD_HEADER*) &cmdStream->payload[0];

	opCodeTLV = oneCmdHeader->opCode;
	numOfParms = oneCmdHeader->numOfParms;

	return(rc);
}

typedef int (*pBinCmdStreamParser)(uint8_t *stream, uint32_t readStreamLen);
pBinCmdStreamParser binCmdStreamParserTLV[] = {
	NULL,                         // version 0, not used, 0 is difficult to tell
	binCmdStreamParser_Ver1,      // version 1
};

static int parseBinCmdStreamTLV(uint8_t *stream, uint32_t readStreamLen)
{
	int rc=TRUE;
	_TESTFLOW_CMD_STREAM_HEADER *pCmdStreamHeader = (_TESTFLOW_CMD_STREAM_HEADER *)&(stream[0]);

	// check the binary cmd stream version
	if (pCmdStreamHeader->version > CMD_STREAM_VER_LATEST) {
		printf("unsupported cmd stream version %d\n", pCmdStreamHeader->version);
		return(FALSE);
	}

	if (NULL != binCmdStreamParserTLV[pCmdStreamHeader->version]) {
		rc = (binCmdStreamParserTLV[pCmdStreamHeader->version])(stream, readStreamLen);
	}

	return(rc);
}

static int cmdParmsParser(_PARM_BIN_TEMPLATE *_parm_bin_template,
		uint32_t parmCode_tlv, uint32_t parmType_tlv, uint32_t parmSize_tlv, uint8_t **data, uint32_t *len)
{
	_PARM_ONEOF   *oneParm;
	uint32_t pos, offset;
	size_t   size;
	uint32_t  parmCode, parmType,parmModType;
	int32_t  i;
	uint8_t *parmBuf = (uint8_t*)cmdStream;

	pos=sizeof(_ONE_CMD_HEADER)+sizeof(_TESTFLOW_CMD_STREAM_HEADER);

	for (i=0;i<numOfParms;i++) {
		oneParm = (_PARM_ONEOF *)(&parmBuf[pos]);
		parmCode = oneParm->parmCode;
		parmModType = parmType = oneParm->parmType;

		if(parmModType == _PARM_DATA) {
			parmModType = _PARM_U8;
		}

		size   = _parm_bin_template[parmCode].len;
		offset = 0;

		if ( (parmCode == parmCode_tlv) && (parmModType == parmType_tlv) && (size == parmSize_tlv)) {
			if ((uint8_t)_PARM_U8 == parmType || _PARM_S8 == parmType)
				*data = (uint8_t *)&(oneParm->parmValue.addr[0]);
			else if ((uint8_t)_PARM_DATA == parmType) {
				*data = (uint8_t *)&parmBuf[pos + sizeof(_PARM_ONEOF) ];
				size = offset = oneParm->parmValue.value.val16;
			}
			else if ((uint8_t)_PARM_U16 == parmType || _PARM_S16 == parmType) {
				printf("Got U16 %d\n",oneParm->parmValue.value.val16);
				*data = (uint8_t *)&(oneParm->parmValue.value.val16);
			}
			else {
				*data = (uint8_t *)&(oneParm->parmValue.value.val32);
			}

			*len = size;

			return TRUE;
		}

		pos += sizeof(_PARM_ONEOF);
		pos += offset;
	}

	return(FALSE);
}

int getParams(uint8_t *key, uint8_t **data, uint32_t *len)
{
	_TESTFLOW_TXT_PARM_TEMPLATE *parmTemplate;
	uint32_t numOfTemplateParms;
	uint32_t parmCode, parmType, parmSize;
	//uint8_t *cmdParmBuf;
	_PARM_BIN_TEMPLATE *parmBinTemplate;
	int rc = TRUE;
	uint8_t opCodeLenHandled=0;

	if ( (opCodeTLV == 0) || (numOfParms ==0) ) {
		printf("Response not initialized...\n");
		return FALSE;
	}

	parmTemplate         = TestFlowCmd2ParmTemplate[opCodeTLV].parmTemplate;
	numOfTemplateParms   = TestFlowCmd2ParmTemplate[opCodeTLV].numParms;

	if (searchTestFlowParmTemplate((char*)key, parmTemplate, numOfTemplateParms, &parmCode, &parmType, &parmSize)) {
		opCodeLenHandled = getCmdOpCodeTemplateSize();
		if ( opCodeTLV <= opCodeLenHandled ) {
			parmBinTemplate = (CmdOpCodeTemplate[opCodeTLV]._CmdOpCodeTemplate)();
			rc = cmdParmsParser(parmBinTemplate, parmCode, parmType, parmSize, data, len);
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}

	return rc;
}

int initResponse(uint8_t *stream, uint32_t len, uint8_t *opCode)
{
	int ret = TRUE;

	opCodeTLV = 0;
	ret = parseBinCmdStreamTLV(stream,len);
	*opCode = opCodeTLV;

	return ret;
}

