#ifndef __VPSS_ASSERT_TNR_H__
#define __VPSS_ASSERT_TNR_H__
#include "vpss_define.h"
#include "hi_reg_common.h"
#include "vpss_drv_comm.h"
#include "vpss_cbb_assert.h"

#if EDA_TEST
#include <stdlib.h>
#include <iostream>
using namespace std;
#endif

HI_U32 VPSS_TNR_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_U32 u32Data, VPSS_CFG_INFO_S *pstCfgInfo, HI_U32 u32ExtInfo);
#endif
