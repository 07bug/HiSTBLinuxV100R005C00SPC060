
//drv_func.h begin
#ifndef __VPSS_DRV_IP_VC1_H__
#define __VPSS_DRV_IP_VC1_H__

#include "vpss_drv_comm.h"
#include "vpss_hal_ip_vc1.h"

typedef enum
{
    VPSS_VC1_TYP = 0,
    VPSS_VC1_TYP1 ,
    VPSS_VC1_RAND ,
    VPSS_VC1_MAX ,
    VPSS_VC1_MIN ,
    VPSS_VC1_ZERO ,
    VPSS_VC1_BUTT
} VPSS_VC1_MODE_E;

typedef struct
{
    HI_U32 vc1_en ;
} VPSS_VC1_CFG_S;

typedef struct
{
    HI_U32 vc1_mapc;
    HI_U32 vc1_mapy;
    HI_U32 vc1_mapcflg;
    HI_U32 vc1_mapyflg;
    HI_U32 vc1_rangedfrm;
    HI_U32 vc1_profile;
} VPSS_VC1_REG_TYPE_S;

//function declare

HI_VOID VPSS_FUNC_SetVc1Mode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, VPSS_VC1_MODE_E Vc1Mode, VPSS_VC1_CFG_S *pstCfg);

#endif
