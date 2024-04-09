/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_HOST_SIM_TESTING)
#include "otaHostCommon.h"
#else
#include "osapi.h"
#endif
#include "parmTxtTemplate.h"
#include "cmdOpcodes.h"
#include "cmdStream.h"
#include "cmd2ParmTemplate.h"
#include "cmdParmsTemplate.h"

#include "genTxBinCmdTlv.h"
#include "testcmd.h"

#include "hex_dump.h"

#define SWAP32(_x) ((uint32_t)(                       \
			(((const uint8_t *)(&_x))[0]) |        \
			(((const uint8_t *)(&_x))[1]<< 8) |    \
			(((const uint8_t *)(&_x))[2]<<16) |    \
			(((const uint8_t *)(&_x))[3]<<24)))

typedef enum {
	TESTFLOW_CMD=0,
	TESTFLOW_PARM,
	TESTFLOW_CONFIG,
	TESTFLOW_DONE,
} TESTFLOW_PARSER_STATE;

extern _TESTFLOW_CMD_PARM_TEMPLATE TestFlowCmd2ParmTemplate[];
extern uint16_t computeChecksumOnly(uint16_t *pHalf, uint16_t length);

int searchTestFlowParmTemplate(char *key, _TESTFLOW_TXT_PARM_TEMPLATE *parmTemplate, uint32_t numOfTemplateParms, uint32_t *parmCode, uint32_t *parmType, uint32_t *parmSize)
{
	uint32_t i;
	for (i=0;i<numOfTemplateParms;i++) {
		if (0 == strcmp(key, parmTemplate[i].parm)) {
			*parmCode=i;
			*parmType = parmTemplate[i].parmType;
			*parmSize = parmTemplate[i].len;
			return(TRUE);
		}
	}
	return(FALSE);
}

// Read test flow file
static  _TESTFLOW_CMD_STREAM testCmdStream;
static int32_t cmdStreamPos=0;
static uint8_t curCmdOpcode;
static TESTFLOW_PARSER_STATE parserState;
_TESTFLOW_TXT_PARM_TEMPLATE *parmTemplate;
static uint32_t numOfTemplateParms,parmIdx;
static uint8_t *cmdStream;
static int commandCreated = FALSE;

int addCommand(uint8_t opCode);

int getParmElement(uint8_t *key, uint32_t *parmCode, uint32_t *parmType, uint32_t *parmSize) {
	return searchTestFlowParmTemplate((char*)key, parmTemplate, numOfTemplateParms, parmCode, parmType, parmSize);
}

int createCommand(uint8_t opCode)
{
	int ret = TRUE;

	if (_OP_TEST_CONFIG != opCode && opCode >= _OP_MAX) {
		printf("Error, opcode out of range %d\n", opCode);
		return FALSE;
	}

	if (commandCreated == TRUE)
	{
		printf("Error: command opCode not completed\n");
		return FALSE;
	}

	memset((void*)&testCmdStream, 0, sizeof(testCmdStream));

	testCmdStream.cmdStreamHeader.cmdId = TC_CMD_TLV_ID;
	testCmdStream.cmdStreamHeader.version = CMD_STREAM_VER1;
	testCmdStream.cmdStreamHeader.header = 0;
	testCmdStream.cmdStreamHeader.headerDepValue = 0;
	testCmdStream.cmdStreamHeader.headerExtended  = 0;
	testCmdStream.cmdStreamHeader.checkSum = 0;

	cmdStreamPos = sizeof(_ONE_CMD_HEADER);
	curCmdOpcode = _OP_TEST_CONFIG;
	parmIdx =0;
	parserState = TESTFLOW_CMD;
	parmTemplate = NULL;
	numOfTemplateParms = 0;
	commandCreated = TRUE;

	ret = addCommand(opCode);

	return ret;
}

int addCommand(uint8_t opCode)
{
	if ( commandCreated == FALSE )
	{
		printf("Error: Command NOT created\n");
		return FALSE;
	}

	if (_OP_TEST_CONFIG != opCode && opCode >= _OP_MAX) {
		printf("Error, opcode out of range %d\n", opCode);
		return FALSE;
	}

	curCmdOpcode = (uint8_t)opCode;

	printf("curCmdOpcode %d parserState %d\n", curCmdOpcode, parserState);

	// special handling of test config
	//
	if (_OP_TEST_CONFIG == curCmdOpcode) {
		// finish all config settings until next "op"
		parserState = TESTFLOW_CONFIG;
	}
	else {
		if (TESTFLOW_CONFIG == parserState) {
			parserState = TESTFLOW_CMD;
			// no current or last command to complete, simply
			// flow to cmd state
		}

		// catch above two cases, during state transition ...
		if (TESTFLOW_CMD == parserState) {
			// beginning of a test flow command
			parmTemplate         = TestFlowCmd2ParmTemplate[curCmdOpcode].parmTemplate;
			numOfTemplateParms   = TestFlowCmd2ParmTemplate[curCmdOpcode].numParms;
			parmIdx = 0;
			// moving to
			parserState = TESTFLOW_PARM;

		}
	}
	return TRUE;
}

int addParameterToCommand(uint8_t *key, uint8_t *value)
{
	return (addParameterToCommandWithLen(key,value,0));
}

int addParameterToCommandWithRawdata(uint8_t *rawData, uint32_t len, int isHeader)
{
	int32_t RawDataPos = 0;
	uint32_t parmLen;
	uint32_t remainbytes;
	uint32_t numOfParmFromRawData=0;
	_PARM_ONEOF parmOne;
	uint32_t dataLen;
	uint32_t i;

	if (isHeader) {
		//uint8_t *cmd = (uint8_t*)rawData;
		//uint8_t opCode = _OP_GENERIC_RSP;
		_ONE_CMD_HEADER cmdHeader;
		//int ret = FALSE;

		memcpy((void*)&(cmdHeader), (void*)&rawData[sizeof(_TESTFLOW_CMD_STREAM_HEADER)], sizeof(_ONE_CMD_HEADER));
		printf("cmd code got %d\n", cmdHeader.opCode);

		createCommand(cmdHeader.opCode);

		rawData += (sizeof(_TESTFLOW_CMD_STREAM_HEADER) + sizeof(_ONE_CMD_HEADER));
		parmLen = len - (sizeof(_TESTFLOW_CMD_STREAM_HEADER) + sizeof(_ONE_CMD_HEADER));
	}
	else {
		parmLen = len;
	}

	while (1) {
		uint32_t parmSize;

		if ( commandCreated == FALSE )
		{
			printf("Error: Command NOT created\n");
			return FALSE;
		}

		remainbytes = parmLen - RawDataPos;
		if (remainbytes < sizeof(_PARM_ONEOF))
			break;

		memset(&parmOne, 0, sizeof(_PARM_ONEOF));
		memcpy((void*)&(parmOne), (void*)&rawData[RawDataPos], sizeof(_PARM_ONEOF));

		if (parmOne.parmCode >= numOfTemplateParms) {
			printf("%s():%d Error! Invalid raw data.\n", __func__, __LINE__);
			printf("parmOne.parmCode %d numOfTemplateParms %d\n", parmOne.parmCode, numOfTemplateParms);
			return FALSE;
		}

		parmSize = parmTemplate[parmOne.parmCode].len;
		printf("key %s Type %d\n", parmTemplate[parmOne.parmCode].parm, parmOne.parmType);
		print_hex_dump((void *)&rawData[RawDataPos], sizeof(_PARM_ONEOF));

		memcpy((void*)&(testCmdStream.payload[cmdStreamPos]), (void*)&rawData[RawDataPos], sizeof(_PARM_ONEOF));
		cmdStreamPos = cmdStreamPos + sizeof(_PARM_ONEOF);
		RawDataPos = RawDataPos + sizeof(_PARM_ONEOF);

		if (_PARM_DATA == parmOne.parmType) {
			if (parmSize > MAX_NUM_VALUES) {
				dataLen = parmOne.parmValue.value.val16;
				for (i=0; i<dataLen; i++) {
					testCmdStream.payload[cmdStreamPos+i] = (uint8_t)rawData[RawDataPos+i];
				}
				print_hex_dump((void *)&rawData[RawDataPos], i);
				cmdStreamPos = cmdStreamPos + dataLen;
				RawDataPos = RawDataPos + dataLen;
			}
		}

		numOfParmFromRawData++;
	}

	parmIdx += numOfParmFromRawData;

	if (isHeader) {
		uint8_t *rCmdStream = NULL;
		uint32_t cmdStreamLen = 0;

		commandComplete(&rCmdStream, &cmdStreamLen);
	}

	return TRUE;
}

int addParameterToCommandWithLen(uint8_t *key, uint8_t *value, uint16_t dataLen)
{
	uint32_t parmCode, parmType, parmSize;
	uint32_t i=0,j,len,padCount=0;
	int32_t tmpcmdStreamPos = cmdStreamPos;
	_PARM_ONEOF parmOne;

	memset(&parmOne, 0, sizeof(_PARM_ONEOF));
	if ( commandCreated == FALSE )
	{
		printf("Error: Command NOT created\n");
		return FALSE;
	}

	if (TESTFLOW_CONFIG == parserState) {
		if (0 == strcmp((char*)key, "header")) {
			testCmdStream.cmdStreamHeader.header = (uint8_t)value[0];
		}
		else if (0 == strcmp((char*)key, "headerDepValue")) {
			memcpy(&testCmdStream.cmdStreamHeader.headerDepValue,value,sizeof(uint16_t));
		}
		else if (0 == strcmp((char*)key, "headerExtended")) {
			memcpy(&testCmdStream.cmdStreamHeader.headerExtended,value,sizeof(uint32_t));
		}
		else {
			printf("Error reading test config %s\n", key);
		}
	}
	else if (TESTFLOW_PARM == parserState) {
		if (searchTestFlowParmTemplate((char*)key, parmTemplate, numOfTemplateParms, &parmCode, &parmType, &parmSize)) {
			parmOne.parmCode  = (uint32_t)parmCode;
			parmOne.parmType  = (uint32_t)parmType;

			if (_PARM_U8 == parmType || _PARM_S8 == parmType ) {
				if ( parmSize <= MAX_NUM_VALUES ) {
					for (i=0;i<parmSize;i++) {
						parmOne.parmValue.addr[i] = (uint8_t)value[i];
					}

					padCount = 0;
					if((parmSize%4) != 0)
					{
						padCount=4-(parmSize%4);
						for (j=0;j<padCount;j++)
						{
							parmOne.parmValue.addr[parmSize+j] = 0;
						}
					}
					padCount = 0;

#ifdef ARCH_BIG_ENDIAN
					// Swap payload here based on 32bit boundary
					{
						uint32_t byte4, swappedByte4;
						for(i=0; i<(parmSize+padCount)/4; i++)
						{
							byte4 = *((uint32_t *)&parmOne.parmValue.addr[i*4]);
							swappedByte4=SWAP32(byte4);
							*((uint32_t *)&parmOne.parmValue.addr[i*4]) = swappedByte4;
						}
					}
#endif

				}
				else {
					if ( dataLen ) {
						if ( dataLen > parmSize ) {
							printf("Given dataLen %d is greater than parmSize %d\n",(int)dataLen,(int)parmSize);
							return FALSE;
						}
					}
					else {
						dataLen = parmSize;
					}

					parmOne.parmType = _PARM_DATA;
					parmOne.parmValue.value.val16 = dataLen;
					parmOne.parmValue.value.val32 = 0;
				}
			}
			else if (_PARM_U16 == parmType) {
				uint32_t temp;
				uint16_t t1;
				memcpy(&t1, value, 2);
				temp=(uint32_t)t1;
				memcpy(&parmOne.parmValue.value.val16,&temp,sizeof(uint32_t));
			}
			else if (_PARM_S16 == parmType ) {
				int32_t temp;
				int16_t t1;
				memcpy(&t1, value, 2);
				temp=(int32_t)t1;
				memcpy(&parmOne.parmValue.value.val16,&temp,sizeof(int32_t));
			}
			else if (_PARM_U32 == parmType || _PARM_S32 == parmType ) {
				memcpy(&parmOne.parmValue.value.val32,value,sizeof(uint32_t));
			}
			else {
				printf("Unknown parm type %d\n", parmType);
				return FALSE;
			}

			if ( parmOne.parmType == _PARM_DATA )
				len = cmdStreamPos + sizeof(_PARM_ONEOF) + dataLen;
			else
				len = cmdStreamPos + sizeof(_PARM_ONEOF);

			if (len > CMD_PAYLOAD_LEN_MAX) {
				printf("len is greater than CMD PAYLOAD MAX %d\n",(int)len);
				return FALSE;
			}

			memcpy((void*)&(testCmdStream.payload[cmdStreamPos]), (void*)&parmOne,sizeof(_PARM_ONEOF));
			cmdStreamPos = cmdStreamPos + sizeof(_PARM_ONEOF);

			if ( parmOne.parmType == _PARM_DATA ) {

				for (i=0;i<dataLen;i++) {
					testCmdStream.payload[cmdStreamPos + i] = (uint8_t)value[i];
				}
				padCount = 0;
				if((dataLen%4) != 0)
				{
					//padding of zero is required
					padCount = 4-(dataLen%4);
					for(j=0; j<padCount; j++)
						testCmdStream.payload[cmdStreamPos+dataLen+j] = 0x0;
				}

#ifdef ARCH_BIG_ENDIAN
				// Swap payload here based on 32bit boundary
				{
					uint32_t byte4, swappedByte4;
					for(i=cmdStreamPos/4; i<(cmdStreamPos+dataLen+padCount)/4; i++)
					{
						byte4 = *((uint32_t *)&testCmdStream.payload[i*4]);
						swappedByte4=SWAP32(byte4);
						*((uint32_t *)&testCmdStream.payload[i*4]) = swappedByte4;
					}
				}
#endif

				cmdStreamPos = cmdStreamPos + dataLen + padCount;
			}

			parmIdx++;
		}
		else {
			printf("Error: cannot find key \"%s\" from the templete\n", key);
			return FALSE;
		}
	}
	else {
		printf("Error: encounter parm while not in parm parsing state, %s %d\n", key, parserState);
		return FALSE;
	}

	printf("%s():%d key %s length %d\n", __func__, __LINE__, key, sizeof(_PARM_ONEOF) + dataLen + padCount);
	print_hex_dump((void*)&(testCmdStream.payload[tmpcmdStreamPos]), sizeof(_PARM_ONEOF) + dataLen + padCount);

	return TRUE;
}

int commandComplete(uint8_t **rCmdStream, uint32_t *cmdStreamLen )
{
	uint16_t sum;
	int ret = TRUE;
	_ONE_CMD_HEADER cmdHeader;
	//uint32_t i=0;

	cmdHeader.opCode = curCmdOpcode;
	cmdHeader.numOfParms = parmIdx;

	memcpy((void*)&(testCmdStream.payload[0]), (void*)&cmdHeader, sizeof(_ONE_CMD_HEADER));

	// flows to
	parserState = TESTFLOW_DONE;

	// get the whole cmd stream ready.
	// either pass the whole stream down the host/dut interface, or write to a binary file
	cmdStream = (uint8_t *)&testCmdStream;
	testCmdStream.cmdStreamHeader.length = cmdStreamPos;
	*cmdStreamLen = testCmdStream.cmdStreamHeader.length + sizeof(_TESTFLOW_CMD_STREAM_HEADER);

	// computer checksum
	sum = computeChecksumOnly((uint16_t*)cmdStream, (*cmdStreamLen)/2);
	testCmdStream.cmdStreamHeader.checkSum = 0xFFFF ^ sum;

	printf("TESTFLOW_CMD_STREAM_HEADER & ONE_CMD_HEADER\n");
	print_hex_dump((void *)&testCmdStream.cmdStreamHeader, sizeof(_TESTFLOW_CMD_STREAM_HEADER) + sizeof(_ONE_CMD_HEADER));

	commandCreated = FALSE;

	*rCmdStream = cmdStream;

	return ret;
}

void parseCommand(uint8_t *buf, uint32_t len)
{
	addParameterToCommandWithRawdata(buf, len, 1);
}
