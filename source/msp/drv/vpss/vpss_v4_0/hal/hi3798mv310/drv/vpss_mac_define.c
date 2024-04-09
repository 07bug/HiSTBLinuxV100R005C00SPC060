#include "hi_type.h"
#include "xdp_define.h"
#include "vpss_define.h"
#include "vpss_mac_define.h"
#if EDA_TEST
#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
#else
#include <linux/string.h>
#include "vpss_common.h"

#endif

//--------------------------------------------
// channel register offset
//--------------------------------------------
const HI_U32 gu32VpssRchnAddr[VPSS_RCHN_MAX] =
{
    (0x0080 / 4), // img  rchn_cf
    (0x0100 / 4), // img  rchn_p1
    (0x0180 / 4), // img  rchn_p2
    (0x0200 / 4), // img  rchn_p3
    (0x0280 / 4), // img  rchn_p3i
    (0x0300 / 4), // solo rchn_rmad
    (0x0320 / 4), // solo rchn_di_rst
    (0x0340 / 4), // solo rchn_di_stcnt
    (0x0360 / 4), // solo rchn_p3mt
    (0x0380 / 4), // solo rchn_p2mv
    (0x03a0 / 4), // solo rchn_p3mv
    (0x03c0 / 4), // solo rchn_p1rgmv
    (0x03e0 / 4), // solo rchn_p2rgmv
    (0x0400 / 4), // solo rchn_rprjh
    (0x0420 / 4), // solo rchn_rprjv
};

const HI_U32 gu32VpssWchnAddr[VPSS_WCHN_MAX] =
{
    (0x0800 / 4), // img  wchn_out0
    (0x0840 / 4), // img  wchn_nr_rfr
    (0x0880 / 4), // img  wchn_di_rfr
    (0x08c0 / 4), // solo wchn_nr_wmad
    (0x08e0 / 4), // solo wchn_di_wst
    (0x0900 / 4), // solo wchn_di_stcnt
    (0x0920 / 4), // solo wchn_p2mt
    (0x0940 / 4), // solo wchn_cfmv
    (0x0960 / 4), // solo wchn_cfrgmv
    (0x0980 / 4), // solo wchn_rfrh
    (0x09a0 / 4)  // solo wchn_rfrv
};

//--------------------------------------------
// channel max reso
//--------------------------------------------
const HI_U32 gu32VpssRchnMaxWth[VPSS_RCHN_MAX] =
{
    4096,   // img  rchn_cf
    4096,   // img  rchn_p1
    4096,   // img  rchn_p2
    4096,   // img  rchn_p3
    4096,   // img  rchn_p3i
    1920,   // solo rchn_nr_rmad
    1920,   // solo rchn_di_rst
    1920,   // solo rchn_di_stcnt
    512,   // solo rchn_p3mt
    512,   // solo rchn_p2mv
    512,   // solo rchn_p3mv
    256,   // solo rchn_p1rgmv
    256,   // solo rchn_p2rgmv
    4096,   // solo rchn_rprjh
    1024    // solo rchn_rprjv
};

const HI_U32 gu32VpssRchnMaxHgt[VPSS_RCHN_MAX] =
{
    2304,   // img  rchn_cf
    2304,   // img  rchn_p1
    2304,   // img  rchn_p2
    2304,   // img  rchn_p3
    2304,   // img  rchn_p3i
    2304,   // solo rchn_nr_rmad
    540,   // solo rchn_di_rst
    540,   // solo rchn_di_stcnt
    512,   // solo rchn_p3mt
    512,   // solo rchn_p2mv
    512,   // solo rchn_p3mv
    256,   // solo rchn_p1rgmv
    256,   // solo rchn_p2rgmv
    256,   // solo rchn_rprjh
    256    // solo rchn_rprjv
};

const HI_U32 gu32VpssWchnMaxWth[VPSS_WCHN_MAX] =
{
    4096,   // img  wchn_out0
    1920,   // img  wchn_nr_rfr
    1920,   // img  wchn_di_rfr
    1920,   // solo wchn_nr_wmad
    1920,   // solo wchn_di_wst
    1920,   // solo wchn_di_stcnt
    512,   // solo wchn_p2mt
    512,   // solo wchn_cfmv
    256,   // solo wchn_cfrgmv
    4096,   // solo wchn_wprjh
    1024,   // solo wchn_wprjv
};

const HI_U32 gu32VpssWchnMaxHgt[VPSS_WCHN_MAX] =
{
    // 2304,   // img  wchn_out0
    4096,   // img  wchn_out0
    1088,   // img  wchn_nr_rfr
    1088,   // img  wchn_di_rfr
    1920,   // solo wchn_nr_wmad
    544,   // solo wchn_di_wst
    544,   // solo wchn_di_stcnt
    512,   // solo wchn_p2mt
    512,   // solo wchn_cfmv
    256,   // solo wchn_cfrgmv
    256,   // solo wchn_wprjh
    256,   // solo wchn_wprjv
};

//--------------------------------------------
// channel name
//--------------------------------------------
HI_VOID VpssGetRchnLayerName(VPSS_MAC_RCHN_E enLayer, HI_CHAR *cChnName)
{
    switch (enLayer)
    {
        case VPSS_MAC_RCHN_CF      : strcpy(cChnName , "rchn_cf"       ); break ;
        case VPSS_MAC_RCHN_P1      : strcpy(cChnName , "rchn_p1"       ); break ;
        case VPSS_MAC_RCHN_P2      : strcpy(cChnName , "rchn_p2"       ); break ;
        case VPSS_MAC_RCHN_P3      : strcpy(cChnName , "rchn_p3"       ); break ;
        case VPSS_MAC_RCHN_P3I     : strcpy(cChnName , "rchn_p3i"      ); break ;
        case VPSS_MAC_RCHN_NR_RMAD : strcpy(cChnName , "rchn_nr_rmad"  ); break ;
        case VPSS_MAC_RCHN_DI_RST  : strcpy(cChnName , "rchn_di_rst"   ); break ;
        case VPSS_MAC_RCHN_DI_STCNT: strcpy(cChnName , "rchn_di_stcnt" ); break ;
        case VPSS_MAC_RCHN_P3MT    : strcpy(cChnName , "rchn_p3mt"     ); break ;
        case VPSS_MAC_RCHN_P2MV    : strcpy(cChnName , "rchn_p2mv"     ); break ;
        case VPSS_MAC_RCHN_P3MV    : strcpy(cChnName , "rchn_p3mv"     ); break ;
        case VPSS_MAC_RCHN_P1RGMV  : strcpy(cChnName , "rchn_p1rgmv"   ); break ;
        case VPSS_MAC_RCHN_P2RGMV  : strcpy(cChnName , "rchn_p2rgmv"   ); break ;
        case VPSS_MAC_RCHN_RPRJH   : strcpy(cChnName , "rchn_rprjh"    ); break ;
        case VPSS_MAC_RCHN_RPRJV   : strcpy(cChnName , "rchn_rprjv"    ); break ;

        default : strcpy(cChnName , "no_name" );
    }
    return;
}

HI_VOID VpssGetWchnLayerName(VPSS_MAC_WCHN_E enLayer, HI_CHAR *cChnName)
{
    switch (enLayer)
    {
        case VPSS_MAC_WCHN_OUT0    : strcpy(cChnName , "wchn_out0"     ); break ;
        case VPSS_MAC_WCHN_NR_RFR  : strcpy(cChnName , "wchn_nr_rfr"   ); break ;
        case VPSS_MAC_WCHN_DI_RFR  : strcpy(cChnName , "wchn_di_rfr"   ); break ;
        case VPSS_MAC_WCHN_NR_WMAD : strcpy(cChnName , "wchn_nr_wmad"  ); break ;
        case VPSS_MAC_WCHN_DI_WST  : strcpy(cChnName , "wchn_di_wst"   ); break ;
        case VPSS_MAC_WCHN_DI_STCNT: strcpy(cChnName , "wchn_di_stcnt" ); break ;
        case VPSS_MAC_WCHN_P2MT    : strcpy(cChnName , "wchn_p2mt"     ); break ;
        case VPSS_MAC_WCHN_CFMV    : strcpy(cChnName , "wchn_cfmv"     ); break ;
        case VPSS_MAC_WCHN_CFRGMV  : strcpy(cChnName , "wchn_cfrgmv"   ); break ;
        case VPSS_MAC_WCHN_WPRJH   : strcpy(cChnName , "wchn_wprjh"    ); break ;
        case VPSS_MAC_WCHN_WPRJV   : strcpy(cChnName , "wchn_wprjv"    ); break ;

        default : strcpy(cChnName , "no_name" );
    }
    return;
}

//--------------------------------------------
// channel data width
//--------------------------------------------
HI_U32 VpssGetRchnDataWidth(VPSS_MAC_RCHN_E enLayer)
{
    HI_U32 u32DataWidth = 8 ;
    switch (enLayer)
    {
        case VPSS_MAC_RCHN_CF       : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_RCHN_P1       : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_RCHN_P2       : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_RCHN_P3       : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_RCHN_P3I      : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_RCHN_NR_RMAD  : u32DataWidth = 5 ; break ;
        case VPSS_MAC_RCHN_DI_RST   : u32DataWidth = 16; break ;
        case VPSS_MAC_RCHN_DI_STCNT : u32DataWidth = 4 ; break ;
        case VPSS_MAC_RCHN_P3MT     : u32DataWidth = 8 ; break ;
        case VPSS_MAC_RCHN_P2MV     : u32DataWidth = 32; break ;
        case VPSS_MAC_RCHN_P3MV     : u32DataWidth = 32; break ;
        case VPSS_MAC_RCHN_P1RGMV   : u32DataWidth = 64; break ;
        case VPSS_MAC_RCHN_P2RGMV   : u32DataWidth = 64; break ;
        case VPSS_MAC_RCHN_RPRJH    : u32DataWidth = 16; break ;
        case VPSS_MAC_RCHN_RPRJV    : u32DataWidth = 16; break ;

        default : XDP_ASSERT(0);
    }
    return u32DataWidth;
}

HI_U32 VpssGetWchnDataWidth(VPSS_MAC_WCHN_E enLayer)
{
    HI_U32 u32DataWidth = 8 ;
    switch (enLayer)
    {
        case VPSS_MAC_WCHN_OUT0    : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_WCHN_NR_RFR  : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_WCHN_DI_RFR  : XDP_ASSERT(0)    ; break ;
        case VPSS_MAC_WCHN_NR_WMAD : u32DataWidth = 5 ; break ;
        case VPSS_MAC_WCHN_DI_WST  : u32DataWidth = 16; break ;
        case VPSS_MAC_WCHN_DI_STCNT: u32DataWidth = 4 ; break ;
        case VPSS_MAC_WCHN_P2MT    : u32DataWidth = 8 ; break ;
        case VPSS_MAC_WCHN_CFMV    : u32DataWidth = 32; break ;
        case VPSS_MAC_WCHN_CFRGMV  : u32DataWidth = 64; break ;
        case VPSS_MAC_WCHN_WPRJH   : u32DataWidth = 16; break ;
        case VPSS_MAC_WCHN_WPRJV   : u32DataWidth = 16; break ;

        default : XDP_ASSERT(0);
    }
    return u32DataWidth;
}

//--------------------------------------------
// channel class type
//--------------------------------------------
HI_BOOL VpssGetRchnClassType(VPSS_MAC_RCHN_E enLayer)
{
    HI_BOOL bIsSoloData = HI_FALSE ;
    switch (enLayer)
    {
        case VPSS_MAC_RCHN_CF      : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_RCHN_P1      : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_RCHN_P2      : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_RCHN_P3      : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_RCHN_P3I     : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_RCHN_NR_RMAD : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_DI_RST  : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_DI_STCNT: bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_P3MT    : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_P2MV    : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_P3MV    : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_P1RGMV  : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_P2RGMV  : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_RPRJH   : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_RCHN_RPRJV   : bIsSoloData = HI_TRUE  ; break ;

        default : bIsSoloData = HI_FALSE;
    }
    return bIsSoloData;
}

HI_BOOL VpssGetWchnClassType(VPSS_MAC_WCHN_E enLayer)
{
    HI_BOOL bIsSoloData = HI_FALSE ;
    switch (enLayer)
    {
        case VPSS_MAC_WCHN_OUT0      : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_WCHN_NR_RFR    : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_WCHN_DI_RFR    : bIsSoloData = HI_FALSE ; break ;
        case VPSS_MAC_WCHN_NR_WMAD   : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_DI_WST    : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_DI_STCNT  : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_P2MT      : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_CFMV      : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_CFRGMV    : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_WPRJH     : bIsSoloData = HI_TRUE  ; break ;
        case VPSS_MAC_WCHN_WPRJV     : bIsSoloData = HI_TRUE  ; break ;

        default : bIsSoloData = HI_FALSE;
    }
    return bIsSoloData;
}


