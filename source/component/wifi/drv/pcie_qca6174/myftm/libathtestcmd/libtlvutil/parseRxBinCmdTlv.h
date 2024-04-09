/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_PARSE_RXBIN_CMDTLV_H)
#define  _PARSE_RXBIN_CMDTLV_H

// exposed API for host/target
int initResponse (u_char *stream, uint32_t len, u_char *opCode);
int getParams(u_char *key, u_char **data, uint32_t *len);

#endif
