
#ifndef __VDP_DM_TYPE_FXPCMN_H__
#define __VDP_DM_TYPE_FXPCMN_H__

#include "vdp_dm_modctrl.h"



#define DEF_L2PQ_LUT_X_SCALE2P      18
#define DEF_L2PQ_LUT_A_SCALE2P      23
#define DEF_L2PQ_LUT_B_SCALE2P      16
#define DEF_L2PQ_LUT_NODES          128


#define DEF_L2G_LUT_X_SCALE2P       18
#define DEF_L2G_LUT_A_SCALE2P       23
#define DEF_L2G_LUT_B_SCALE2P       16
#define DEF_L2G_LUT_NODES           128


#define DEF_PQ2L_LUT_SIZE_1024     (1<<10)
#define DEF_PQ2L_LUT_SIZE_4096     (1<<12)

#if 1
#define DEF_G2L_LUT_SIZE_2P        8
#define DEF_G2L_LUT_SIZE           (1<<DEF_G2L_LUT_SIZE_2P)
#endif


#define DEF_FXP_TM_LUT_SCALE_2P     12

#define DEF_DEGAMMAR_IN_SCALE2P   16
#define DEF_DEGAMMAR_INTERP_BITS   4
#define DEF_DEGAMMAR_LOG_SCALE2P  12
#define DEF_DEGAMMAR_LOG_RATE_SCALE2P 16
#define DEF_DEGAMMAR_LOG_LUT_SIZE (1<<DEF_DEGAMMAR_LOG_SCALE2P)

#define DEF_DEGAMMAR_POWER_IN_BITS  14
#define DEF_DEGAMMAR_POWER_ID_BITS   4
#define DEF_DEGAMMAR_POWER_LUT_NUM   ((1 << DEF_DEGAMMAR_POWER_ID_BITS) - 6)
#define DEF_DEGAMMAR_POWER_LUT_SIZE  (1 << (DEF_DEGAMMAR_POWER_IN_BITS - DEF_DEGAMMAR_POWER_ID_BITS) )

#define DEF_GAMMAR_SCALE2P      14
#define DEF_DEGAMMAR_OUT_SCALE2P  18
#define OPT_2_OPT_SCALE2P     3

#define DM_PQ_SCALE_2P        12
#define DEF_MSWEIGHT_SCALE        12



#define PQ_BIT_WIDTH_12_BITS    1
#if 1
#define PQ_BIT_SHIFT            3
#define PQ_UNSIGNED_BLEND       1
#endif


#define TWO_PWR_N(bits) ((HI_U64)(1) << (bits))


#define DLB_UINT_MAX(bits) (TWO_PWR_N(bits) - 1)

#define MAX2S(a_, b_)  (((a_) >= (b_)) ? (a_) : (b_))
#define MIN2S(a_, b_)  (((a_) <= (b_)) ? (a_) : (b_))
#define CLAMPS(a_, mn_, mx_)  ( ((a_) >= (mn_)) ? ( ((a_) <= (mx_)) ? (a_) : (mx_) ) : (mn_) )


#endif
