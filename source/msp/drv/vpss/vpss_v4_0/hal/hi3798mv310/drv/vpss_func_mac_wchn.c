#include "vpss_func_mac_wchn.h"
#include "vpss_hal_ip_wchn.h"
#include "vpss_drv_comm.h"
#include "vpss_hal_comm.h"
#include "vpss_mac_define.h"
#include "vpss_drv_cmp_frm_nr.h"
#include "vpss_drv_cmp_frm_out0.h"


HI_VOID VPSS_MAC_InitWchnCfg(HI_U32 u32Layer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg)
{
    memset(pstWchnCfg, 0, sizeof(VPSS_MAC_WCHN_CFG_S));

    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = gstVpssAddrCfg.stWchnAddr[u32Layer].u64YAddr;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = gstVpssAddrCfg.stWchnAddr[u32Layer].u64UAddr;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr = gstVpssAddrCfg.stWchnAddr[u32Layer].u64VAddr;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = gstVpssAddrCfg.stWchnAddr[u32Layer].u32YStr ;
    pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = gstVpssAddrCfg.stWchnAddr[u32Layer].u32CStr ;

    pstWchnCfg->bEn                = HI_FALSE               ;
    pstWchnCfg->enDataType         = XDP_DATA_TYPE_SP_LINEAR;
    pstWchnCfg->enDataFmt          = XDP_PROC_FMT_SP_420    ;
    pstWchnCfg->enRdMode           = XDP_RMODE_PROGRESSIVE  ;
    pstWchnCfg->enDataWidth        = XDP_DATA_WTH_8         ;

    pstWchnCfg->stOutRect.u32X     = 0 ;
    pstWchnCfg->stOutRect.u32Y     = 0 ;
    pstWchnCfg->stOutRect.u32Wth   = 128;
    pstWchnCfg->stOutRect.u32Hgt   = 128;

    pstWchnCfg->bFlipEn            = HI_FALSE ;
    pstWchnCfg->bMirrorEn          = HI_FALSE ;
    pstWchnCfg->bUvInvEn           = HI_FALSE ;
    pstWchnCfg->bTunlEn            = HI_FALSE ;
    pstWchnCfg->bMmuBypass         = HI_TRUE  ;
    pstWchnCfg->stDitherCfg.bEn    = HI_FALSE ;
    pstWchnCfg->stDitherCfg.enMode = VPSS_DITHER_MODE_ROUND ;

    pstWchnCfg->enCmpType          = XDP_CMP_TYPE_OFF;

    pstWchnCfg->bSetFlag           = HI_FALSE ;
    pstWchnCfg->bAddrAutoCalcEn    = HI_FALSE  ;
    pstWchnCfg->bAddrRandModeEn    = HI_FALSE ;
    pstWchnCfg->bAddrSafeModeEn    = HI_TRUE ;

    if (u32Layer == VPSS_MAC_WCHN_OUT0)
    {
        pstWchnCfg->bFlipEn              = 0;//(HI_BOOL)uGetRandEx(0,1);
        pstWchnCfg->bMirrorEn            = 0;//(HI_BOOL)uGetRandEx(0,1) ;
        pstWchnCfg->bUvInvEn             = 0;//(HI_BOOL)uGetRandEx(0,1);
        pstWchnCfg->stDitherCfg.bEn      = 0;//(HI_BOOL)uGetRandEx(0,1);
    }

    if (u32Layer == VPSS_MAC_WCHN_NR_RFR)
    {
        pstWchnCfg->stDitherCfg.bEn = 0;//(HI_BOOL)uGetRandEx(0,1);
    }
    pstWchnCfg->bMmuBypass           = HI_FALSE;//(HI_BOOL)uGetRandEx(0,1);
    return;
}

HI_VOID VPSS_MAC_SetWchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg)
{
    HI_U32  u32RealOffset = 0;
    HI_BOOL bIsSoloData   = HI_FALSE;
    HI_S8   cName[80] ;

    memset(cName, 0, sizeof(HI_S8) * 80);
    bIsSoloData  = VpssGetWchnClassType(enLayer);

    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_IMG_START_OFFSET);
    }
    else
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_SOLO_START_OFFSET);
    }
#if EDA_TEST
    cout << "------------------------------------------------------" << endl;
    VpssGetWchnLayerName(enLayer, cName);
    cout << __FUNCTION__ << "() channel name  = "   << cName << endl;
    cout << __FUNCTION__ << "() bIsSoloData   = "   << hex << bIsSoloData     << endl;
    cout << __FUNCTION__ << "() u32RealOffset = 0x" << hex << u32RealOffset * 4 << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bEn                                  = 0x" << hex << pstWchnCfg->bEn                                  << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->enDataType                           = 0x" << hex << pstWchnCfg->enDataType                           << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->enDataWidth                          = 0x" << hex << pstWchnCfg->enDataWidth                          << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stOutRect.u32X                       = "   << dec << pstWchnCfg->stOutRect.u32X                       << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stOutRect.u32Y                       = "   << dec << pstWchnCfg->stOutRect.u32Y                       << endl;
    cout << __FUNCTION__ << "() pstEnvCfg->stOutRect.u32Wth                      = "   << dec << pstWchnCfg->stOutRect.u32Wth                     << endl;
    cout << __FUNCTION__ << "() pstEnvCfg->stOutRect.u32Hgt                      = "   << dec << pstWchnCfg->stOutRect.u32Hgt                     << endl;
    cout << __FUNCTION__ << "() pstEnvCfg->enDataFmt                             = 0x" << hex << pstWchnCfg->enDataFmt                            << endl;
    cout << __FUNCTION__ << "() pstEnvCfg->enRdMode                              = 0x" << hex << pstWchnCfg->enRdMode                             << endl;
    cout << __FUNCTION__ << "() pstEnvCfg->u64Finfo                              = 0x" << hex << pstWchnCfg->u64Finfo                             << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bFlipEn                              = 0x" << hex << pstWchnCfg->bFlipEn                              << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bMirrorEn                            = 0x" << hex << pstWchnCfg->bMirrorEn                            << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bUvInvEn                             = 0x" << hex << pstWchnCfg->bUvInvEn                             << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bTunlEn                              = 0x" << hex << pstWchnCfg->bTunlEn                              << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->bMmuBypass                           = 0x" << hex << pstWchnCfg->bMmuBypass                           << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stDitherCfg.bEn                      = 0x" << hex << pstWchnCfg->stDitherCfg.bEn                      << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stDitherCfg.enMode                   = 0x" << hex << pstWchnCfg->stDitherCfg.enMode                   << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->enCmpType                            = 0x" << hex << pstWchnCfg->enCmpType                            << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  << endl;
    cout << __FUNCTION__ << "() gu64VpssSafeAddr   = 0x" << hex << gu64VpssSafeAddr   << endl;
    cout << __FUNCTION__ << "() gu64VpssUnsafeAddr = 0x" << hex << gu64VpssUnsafeAddr << endl;
    cout << endl;
#if 0
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64YAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64YAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64UAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64UAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64VAddr = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u64VAddr << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u32YStr  = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u32YStr  << endl;
    cout << __FUNCTION__ << "() pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u32CStr  = 0x" << hex << pstWchnCfg->stAddr[VPSS_WCHN_ADDR_HEAD].u32CStr  << endl;
#endif
    cout << endl;
#endif

    if (HI_FALSE == bIsSoloData)
    {
#if EDA_TEST
        if (enLayer == VPSS_MAC_WCHN_OUT0)
        {
            if (pstWchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                pstWchnCfg->stDitherCfg.bEn = HI_FALSE;
            }
        }
        if (enLayer == VPSS_MAC_WCHN_NR_RFR)
        {
            if (pstWchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                pstWchnCfg->stDitherCfg.bEn = HI_FALSE;
            }
        }
#endif
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_IMG_START_OFFSET);
        //---------------------------
        // Cfg
        //---------------------------
        VPSS_WCHN_SetEn            ( pstReg, u32RealOffset, pstWchnCfg->bEn                 );
        VPSS_WCHN_SetBitw          ( pstReg, u32RealOffset, pstWchnCfg->enDataWidth         );
        VPSS_WCHN_SetType          ( pstReg, u32RealOffset, pstWchnCfg->enDataType          );
        VPSS_WCHN_SetFlip          ( pstReg, u32RealOffset, pstWchnCfg->bFlipEn             );
        VPSS_WCHN_SetMirror        ( pstReg, u32RealOffset, pstWchnCfg->bMirrorEn           );
        VPSS_WCHN_SetUvInvert      ( pstReg, u32RealOffset, pstWchnCfg->bUvInvEn            );
        VPSS_WCHN_SetDitherEn      ( pstReg, u32RealOffset, pstWchnCfg->stDitherCfg.bEn     );
        VPSS_WCHN_SetDitherMode    ( pstReg, u32RealOffset, pstWchnCfg->stDitherCfg.enMode  );
        VPSS_WCHN_SetHorOffset     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32X      );
        VPSS_WCHN_SetVerOffset     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Y      );
        VPSS_WCHN_SetTunlEn        ( pstReg, u32RealOffset, pstWchnCfg->bTunlEn              );
        VPSS_WCHN_SetDBypass       ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass           );
        VPSS_WCHN_SetHBypass       ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass           );
        //---------------------------
        // Addr
        //---------------------------
        VPSS_WCHN_SetYAddrH        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr >> 32 ) & 0xffffffff ));
        VPSS_WCHN_SetCAddrH        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr >> 32 ) & 0xffffffff ));
        VPSS_WCHN_SetYAddrL        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff ));
        VPSS_WCHN_SetCAddrL        ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr     ) & 0xffffffff ));
        VPSS_WCHN_SetYStride       ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr                      );
        VPSS_WCHN_SetCStride       ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr                      );
        //---------------------------
        // Cmp
        //---------------------------
        VPSS_WCHN_SetCmpMode       ( pstReg, u32RealOffset, pstWchnCfg->enCmpType );

        //---------------------------
        // Env Reg Setting
        //---------------------------
        VPSS_WCHN_ENV_SetFormat    ( pstReg, u32RealOffset, pstWchnCfg->enDataFmt           );
        VPSS_WCHN_SetLmRmode       ( pstReg, u32RealOffset, pstWchnCfg->enRdMode            );
        VPSS_WCHN_ENV_SetWidth     ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Wth - 1  );
        VPSS_WCHN_ENV_SetHeight    ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Hgt - 1  );
        VPSS_WCHN_ENV_SetFinfoH    ( pstReg, u32RealOffset, ((pstWchnCfg->u64Finfo >> 32 ) & 0xffffffff ));
        VPSS_WCHN_ENV_SetFinfoL    ( pstReg, u32RealOffset, ((pstWchnCfg->u64Finfo     ) & 0xffffffff ));
        //---------------------------
        //Assertion
        //---------------------------
        if (pstWchnCfg->bEn)
        {
            XDP_ASSERT(pstWchnCfg->stOutRect.u32Wth >= 32);
            XDP_ASSERT(pstWchnCfg->stOutRect.u32Hgt >= 8 );
            XDP_ASSERT(pstWchnCfg->enCmpType == XDP_CMP_TYPE_OFF);
        }
    }
    else
    {
        u32RealOffset = (gu32VpssWchnAddr[enLayer] - VPSS_WCHN_SOLO_START_OFFSET);
        //---------------------------
        //Cfg
        //---------------------------
        VPSS_WCHN_SOLO_SetEn         ( pstReg, u32RealOffset, pstWchnCfg->bEn        );
        VPSS_WCHN_SOLO_SetFlip       ( pstReg, u32RealOffset, pstWchnCfg->bFlipEn    );
        VPSS_WCHN_SOLO_SetMirror     ( pstReg, u32RealOffset, pstWchnCfg->bMirrorEn  );
        VPSS_WCHN_SOLO_SetTunlEn     ( pstReg, u32RealOffset, pstWchnCfg->bTunlEn    );
        VPSS_WCHN_SOLO_SetDBypass    ( pstReg, u32RealOffset, pstWchnCfg->bMmuBypass );
        //---------------------------
        // Addr
        //---------------------------
        VPSS_WCHN_SOLO_SetAddrH      ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr >> 32 ) & 0xffffffff ));
        VPSS_WCHN_SOLO_SetAddrL      ( pstReg, u32RealOffset, ((pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff ));
        VPSS_WCHN_SOLO_SetStride     ( pstReg, u32RealOffset,   pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr                      );
        //---------------------------
        // Env Reg Setting
        //---------------------------
        VPSS_WCHN_SOLO_ENV_SetWidth  ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Wth - 1 );
        VPSS_WCHN_SOLO_ENV_SetHeight ( pstReg, u32RealOffset, pstWchnCfg->stOutRect.u32Hgt - 1 );
        //---------------------------
        //Assertion
        //---------------------------
    }


    //---------------------------
    //Assertion
    //---------------------------
    if (pstWchnCfg->bEn)
    {
        XDP_ASSERT(pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr % 16 == 0);
        XDP_ASSERT(pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr % 16 == 0);
        XDP_ASSERT(pstWchnCfg->stOutRect.u32Wth <= gu32VpssWchnMaxWth[enLayer]);
        // XDP_ASSERT(pstWchnCfg->stOutRect.u32Hgt <= gu32VpssWchnMaxHgt[enLayer]);
        if (pstWchnCfg->stDitherCfg.bEn)
        {
            XDP_ASSERT(pstWchnCfg->enDataWidth == XDP_DATA_WTH_8);
        }
    }

    return;
}

HI_U64 VPSS_MAC_WchnCalcAddrStr(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg, HI_U64 u64StartAddr, HI_BOOL bRandModeEn)
{
    HI_BOOL bIsSoloData   = HI_FALSE;
    HI_U32  u32DataWidth  = 0;
    HI_U32  u32DataWidthY = 0;
    HI_U32  u32DataWidthC = 0;

    XDP_SOLO_ADDR_S stAddrTemp;
    XDP_RECT_S stRectY;
    XDP_RECT_S stRectC;

    XDP_ASSERT((u64StartAddr % 16) == 0);
    stAddrTemp.u64Addr = u64StartAddr;

    if (pstWchnCfg->bEn == HI_FALSE)
    {
        pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = u64StartAddr;
        pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = u64StartAddr;
        pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr = u64StartAddr;
        pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = 0 ;
        pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = 0 ;
    }
    else
    {
        bIsSoloData  = VpssGetWchnClassType(enLayer);

        if (HI_FALSE == bIsSoloData)
        {
            // YC data reso
            stRectY.u32Wth = pstWchnCfg->stOutRect.u32X + pstWchnCfg->stOutRect.u32Wth;
            stRectY.u32Hgt = pstWchnCfg->stOutRect.u32Y + pstWchnCfg->stOutRect.u32Hgt;

            if (VPSS_MAC_WCHN_OUT0 != enLayer)
            {
                if (pstWchnCfg->enRdMode != XDP_RMODE_PROGRESSIVE)
                {
                    XDP_ASSERT((stRectY.u32Hgt % 2) == 0);
                    stRectY.u32Hgt /= 2;
                }
            }

            stRectC.u32Wth = VpssCalcChmWth(stRectY.u32Wth, pstWchnCfg->enDataFmt);
            stRectC.u32Hgt = VpssCalcChmHgt(stRectY.u32Hgt, pstWchnCfg->enDataFmt);

            if (pstWchnCfg->enCmpType == XDP_CMP_TYPE_OFF)
            {
                // YC data bitdepth
                switch (pstWchnCfg->enDataWidth)
                {
                    case XDP_DATA_WTH_8 : u32DataWidth = 8 ; break;
                    case XDP_DATA_WTH_10: u32DataWidth = 10; break;
                    case XDP_DATA_WTH_12: u32DataWidth = 12; break;
                    case XDP_DATA_WTH_16: u32DataWidth = 16; break;
                    default: XDP_ASSERT(0);
                }

                switch (pstWchnCfg->enDataType)
                {
                    case XDP_DATA_TYPE_SP_LINEAR:
                    {
                        u32DataWidthY  = u32DataWidth;
                        u32DataWidthC  = u32DataWidth * 2;
                        break;
                    }
                    case XDP_DATA_TYPE_PACKAGE:
                    {
                        u32DataWidthY  = u32DataWidth * 2;
                        u32DataWidthC  = 0;
                        break;
                    }
                    case XDP_DATA_TYPE_PLANAR :
                    case XDP_DATA_TYPE_SP_TILE:
                    {
                        XDP_ASSERT(0); // need modify here
                        break;
                    }
                    default: XDP_ASSERT(0);
                }
                // Y data addr
                pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidthY, bRandModeEn);
                pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = stAddrTemp.u32Str;
                // C data addr
                pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
                pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectC, u32DataWidthC, bRandModeEn);
                pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = stAddrTemp.u32Str;
            }
            else
            {
                XDP_ASSERT(0); // need modify here
            }
        }
        else
        {
            // YC data reso
            stRectY.u32Wth = pstWchnCfg->stOutRect.u32X + pstWchnCfg->stOutRect.u32Wth;
            stRectY.u32Hgt = pstWchnCfg->stOutRect.u32Y + pstWchnCfg->stOutRect.u32Hgt;
            u32DataWidth  = VpssGetWchnDataWidth(enLayer);
            // Y data addr
            pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
            VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidth, bRandModeEn);
            pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = stAddrTemp.u32Str;
            // C data addr
            pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
            pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
            pstWchnCfg->stAddr[VPSS_WCHN_ADDR_DATA].u32CStr  = 0;
        }
    }

    return stAddrTemp.u64Addr;
}

