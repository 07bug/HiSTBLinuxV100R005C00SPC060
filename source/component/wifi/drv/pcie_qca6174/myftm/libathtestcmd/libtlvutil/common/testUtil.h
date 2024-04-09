
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_TEST_UTIL_H)
#define _TEST_UTIL_H

int verifyChecksum(uint16_t* stream, uint32_t len);
uint16_t computeChecksumOnly(uint16_t *pHalf, uint16_t length);

#endif // _TEST_UTIL_H

