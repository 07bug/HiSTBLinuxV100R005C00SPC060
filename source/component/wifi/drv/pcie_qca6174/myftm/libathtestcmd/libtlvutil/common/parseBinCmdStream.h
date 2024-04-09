
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_PARSE_BIN_CMD_STREAM_H)
#define  _PARSE_BIN_CMD_STREAM_H

#define AVERAGE_NUM_CMD_PARMS   10
#define CMD_QUEUE_AVERAGE  (CMD_PAYLOAD_LEN_MAX / (AVERAGE_NUM_CMD_PARMS * sizeof(_PARM_ONEOF)))
#define CMD_QUEUE_MAX      ((CMD_QUEUE_AVERAGE > 256) ? (256) : (CMD_QUEUE_AVERAGE))

#define CMDPROC_QUEUE_ABSOLUTE_BEGIN 0

typedef struct _cmdQueue {
	uint16_t  opCode;
	uint16_t  numOfParms;
	uint8_t   *cmdParmBuf;
} __ATTRIB_PACK _CMD_QUEUE;

typedef struct _parsedBinCmdStreamInfo {
	uint16_t     header;
	uint16_t     numOfCmds;
	uint16_t     headerDepValue;
	uint16_t     padding;
	uint32_t     headerExtended;
	uint16_t     curQBegin;
	uint16_t     curQEnd;
	uint16_t     doneQBegin;
	uint16_t     doneQEnd;
	_CMD_QUEUE   curCmdQueue[CMD_QUEUE_MAX];
	_CMD_QUEUE   doneCmdQueue[CMD_QUEUE_MAX];
} __ATTRIB_PACK _PARSED_BIN_CMD_STREAM_INFO;


extern _PARSED_BIN_CMD_STREAM_INFO CmdStreamInfo;
extern int parseBinCmdStream(uint8_t *stream, uint32_t readStreamLen, uint8_t **pPayload, uint16_t *payloadLen);
extern int readBinStreamFile(char *fileName, uint8_t **pReadCmdStream, uint32_t *readStreamLen);

#endif // #if !defined(_PARSE_BIN_CMD_STREAM_H)

