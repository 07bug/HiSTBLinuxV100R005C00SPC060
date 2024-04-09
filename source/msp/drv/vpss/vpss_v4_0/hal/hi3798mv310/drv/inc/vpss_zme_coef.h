
//drv_func.h begin
#ifndef __VPSS_DRV_IP_ZME_H__
#define __VPSS_DRV_IP_ZME_H__

#include "vpss_cbb_common.h"
//#include <stdio.h>

#define VPSS_MULTI1 4096
#define VPSS_MULTI 1048576

typedef enum
{
    VPSS_ZME_TYP = 0,
    VPSS_ZME_TYP1 ,
    VPSS_ZME_RAND ,
    VPSS_ZME_MAX ,
    VPSS_ZME_MIN ,
    VPSS_ZME_ZERO ,
    VPSS_ZME_BUTT
} VPSS_ZME_MODE_E;

typedef struct
{
    HI_BOOL        bEnable;
    HI_U32         para_type;

    HI_S32         iw;
    HI_S32         ih;
    HI_S32         ow;
    HI_S32         oh;
    HI_S32         in_fmt;
    HI_S32         out_fmt;

    HI_S32         hchfir_en;
    HI_S32         hlfir_en;
    HI_S32         hchmid_en;
    HI_S32         hlmid_en;
    HI_S32         hchmsc_en;
    HI_S32         hlmsc_en;

    HI_S32         vchfir_en;
    HI_S32         vlfir_en;
    HI_S32         vchmid_en;
    HI_S32         vlmid_en;
    HI_S32         vchmsc_en;
    HI_S32         vlmsc_en;

    HI_S32         hor_loffset;
    HI_S32         hor_coffset;
    HI_S32         vluma_offset;
    HI_S32         vchroma_offset;

    HI_U32         lhaddr;
    HI_U32         lvaddr;
    HI_U32         chaddr;
    HI_U32         cvaddr;

    HI_U8         *vir_lhaddr;
    HI_U8         *vir_lvaddr;
    HI_U8         *vir_chaddr;
    HI_U8         *vir_cvaddr;

} VPSS_ZME_CFG_S;

//function declare
HI_S32  VPSS_zmecoef_to_dut(VPSS_ZME_CFG_S *pstCfg);
//HI_VOID VPSS_FUNC_SetZmeMode(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_ZME_MODE_E ZmeMode,VPSS_ZME_CFG_S * pstCfg);

#endif



