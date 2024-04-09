#ifndef __VPSS_DRV_MAC_CTRL_H__
#define __VPSS_DRV_MAC_CTRL_H__

#include "vpss_define.h"
#include "hi_reg_common.h"
#include "vpss_mac_define.h"

typedef enum
{
    VPSS_TUNL_MODE_2LINE,
    VPSS_TUNL_MODE_4LINE,
    VPSS_TUNL_MODE_8LINE,
    VPSS_TUNL_MODE_16LINE,
    VPSS_TUNL_MODE_BUTT
} VPSS_TUNL_MODE_E;

typedef struct
{
    //cfg
    XDP_REQ_LENGTH_E     enReqLen   ;
    XDP_REQ_CTRL_E       enReqCtrl  ;
    HI_BOOL              bSecEn     ;
    VPSS_PROC_COMP_E     enProcComp ;
    HI_BOOL              bDmaEn     ;
    // check sum
    // rotate
    HI_BOOL              bRotateEn;
    VPSS_ROTATE_ANGLE_E  enRotateAngle;

    // read low delay
    HI_BOOL              bRdTunlEn;
    HI_BOOL              bRdTunlMmuBypass;
    HI_U32               u32RdTunlIntval;

    // write low delay
    HI_BOOL              bWrTunlEn;
    VPSS_TUNL_MODE_E     enWTunlMode;
    HI_U32               u32WrTunlFinishLine;

    // testpattern
    VPSS_PATTERN_CFG_S   stPatternCfg ;

    // address
    HI_U64               u64Addr[VPSS_MAC_ADDR_CTRL_BUTT];

} VPSS_MAC_CTRL_CFG_S;

//function declare
HI_VOID VPSS_MAC_InitCtrlCfg(VPSS_MAC_CTRL_CFG_S *pstCfg);
HI_VOID VPSS_MAC_SetCtrlCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_CTRL_CFG_S *pstCfg);


#endif

