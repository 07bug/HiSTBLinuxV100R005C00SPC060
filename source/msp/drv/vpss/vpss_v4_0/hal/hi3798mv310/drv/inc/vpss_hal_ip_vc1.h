
//vpss_hal_ip_vc1.h begin

#ifndef __VPSS_HAL_IP_VC1_H__
#define __VPSS_HAL_IP_VC1_H__

#include "hi_reg_common.h"
#include "vpss_define.h"


HI_VOID VPSS_Vc1_SetVc1Mapc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_mapc);
HI_VOID VPSS_Vc1_SetVc1Mapy(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_mapy);
HI_VOID VPSS_Vc1_SetVc1Mapcflg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_mapcflg);
HI_VOID VPSS_Vc1_SetVc1Mapyflg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_mapyflg);
HI_VOID VPSS_Vc1_SetVc1Rangedfrm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_rangedfrm);
HI_VOID VPSS_Vc1_SetVc1Profile(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_profile);

#endif
