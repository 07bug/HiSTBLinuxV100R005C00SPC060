#ifndef __VDP_COEF_FUNC_H__
#define __VDP_COEF_FUNC_H__


#include "vdp_define.h"
//#include "c_union_define.h"
#include "hi_reg_common.h"
#include "hi_type.h"
#if EDA_TEST
#include "vdp_sti.h"
#include "vdp_env_def.h"
#include "vdp_frw.h"
#endif
#include "vdp_hal_comm.h"
#include "vdp_drv_coef.h"





HI_S32 VDP_FUNC_SendCoef(VDP_COEF_SEND_CFG *stCfg);
HI_S32 VDP_FUNC_Push128(VDP_U128_S *pstData128, HI_U32 coef_data, HI_U32 bit_len);
HI_U32 VDP_FUNC_WriteDDR(STI_FILE_TYPE_E enStiType, FILE *fp_coef , HI_U8  *addr, VDP_U128_S *pstData128 );
HI_U32 VDP_FUNC_FindMax(HI_U32 *u32Array, HI_U32 num);


#endif

