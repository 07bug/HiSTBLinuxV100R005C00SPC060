/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_GEN_TXBIN_CMDTLV_H)
#define  _GEN_TXBIN_CMDTLV_H

// exposed API for host/target
int createCommand(uint8_t opCode);
int addParameterToCommand(uint8_t *key, uint8_t *data);
int addParameterToCommandWithRawdata(uint8_t *rawData, uint32_t len, int isHeader);
int addParameterToCommandWithLen(uint8_t *key, uint8_t *data, uint16_t dataLen);
int commandComplete(uint8_t **rCmdStream, uint32_t *len );
int getParmElement(uint8_t *key, uint32_t *parmCode, uint32_t *parmType, uint32_t *parm_Size);
void parseCommand(uint8_t *buf, uint32_t len);

#endif

