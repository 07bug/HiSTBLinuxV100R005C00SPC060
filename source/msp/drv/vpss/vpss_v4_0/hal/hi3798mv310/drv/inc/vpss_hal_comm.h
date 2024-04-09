#ifndef __VPSS_HAL_COMM_H__
#define __VPSS_HAL_COMM_H__

/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         ·ð×æ±£ÓÓ       ÓÀÎÞBUG
*/



//===========================
// include head
//===========================
#include "hi_type.h"
#include "hi_reg_common.h"
#include "vpss_common.h"


//#include "xdp_component.h"

//==========================
// macro define
//==========================
#define IMGRCHN_ADDR_OFFSET             0x80
#define IMGWCHN_ADDR_OFFSET             0x40
#define SOLORCHN_ADDR_OFFSET            0x20
#define SOLOWCHN_ADDR_OFFSET            0x20

//==========================
// type define
//==========================
#if 0
#define VPSS_REG_SIZE_CALC(start, end)\
    (offsetof(S_VPSS_REGS_TYPE, end)  -\
     offsetof(S_VPSS_REGS_TYPE, start))
#endif
//==========================
//extern global var declare
//==========================



//=========================
//function declare
//=========================


S_VPSS_REGS_TYPE *VPSS_HAL_GetVpssNode(HI_U32 u32HandleNo);

HI_S32 VPSS_HAL_SetVpssNode(HI_U8 *pu8VirAddr);

S_VPSS_REGS_TYPE *VPSS_HAL_GetLocalVpssReg(HI_VOID);

HI_S32 VPSS_HAL_SetLocalVpssReg(S_VPSS_REGS_TYPE *pstVpssReg);

HI_U32 VPSS_HAL_GetVpssNodePhyAddr(HI_U32 u32HandleNo);

HI_VOID VPSS_HAL_SetVpssNodePhyAddr(HI_U32 u32PhyAddr);

#endif


