
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#if !defined(_CMD_CAL_DONE_PARMS_H)
#define _CMD_CAL_DONE_PARMS_H

// ---------------------------
// Important: There can ONLY be one typedef struct per each cmd parameter structure
//    Parser is not intelligent enough and needs this guarantee.
//

//#include "parmBinTemplate.h"

typedef struct _calDoneParm {
	uint32_t   futureData;
} __ATTRIB_PACK _CMD_CAL_DONE_PARMS;

extern _PARM_BIN_TEMPLATE _calDoneParm_bin_template[];

#endif // #if !defined(_CMD_CAL_DONE_PARMS_H)

