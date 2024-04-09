/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#ifndef _RESP_API_H
#define _RESP_API_H

#ifdef __cplusplus
extern "C" {
#endif

void parseGenericResponse(void);
void parseTLVSubmitReport(void);
void parseResNart(void);
void parseResTxStatus(void);
void parseResRxStatus(void);
void parseResponse(void *buf, int len);
void rateIndexToArrayMapping (uint32_t rateIndex, uint32_t *rowIndex, uint32_t *bitmask, int *is11AcRate );

typedef const char RATE_STR[RATE_STR_LEN];
extern RATE_STR bgRateStrTbl[G_RATE_NUM];
extern _AthDataRate Mask2Rate[RATE_MASK_ROW_MAX][RATE_MASK_BIT_MAX];

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif

