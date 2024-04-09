#include "vpss_func_mac_rchn.h"
#include "vpss_hal_ip_rchn.h"
#include "vpss_drv_comm.h"
#include "vpss_hal_comm.h"
#include "vpss_mac_define.h"
#include "vpss_drv_cmp_frm_nr.h"


HI_VOID VPSS_MAC_InitRchnCfg(HI_U32 u32Layer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg)
{
    HI_U64 u32MaxWth  = 4096  ;
    memset(pstRchnCfg, 0, sizeof(VPSS_MAC_RCHN_CFG_S));

    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = gstVpssAddrCfg.stRchnAddr[u32Layer].u64YAddr;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = gstVpssAddrCfg.stRchnAddr[u32Layer].u64UAddr;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = gstVpssAddrCfg.stRchnAddr[u32Layer].u64VAddr;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = gstVpssAddrCfg.stRchnAddr[u32Layer].u32YStr ;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = gstVpssAddrCfg.stRchnAddr[u32Layer].u32CStr ;

    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = 0x80000000;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = 0x82000000;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = u32MaxWth;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = u32MaxWth;

    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = 0x84000000;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = 0x86000000;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = u32MaxWth;
    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = u32MaxWth;

    pstRchnCfg->bEn                  = HI_FALSE                ;
    pstRchnCfg->bEn1                 = HI_FALSE                ;
    pstRchnCfg->enDataType           = XDP_DATA_TYPE_SP_LINEAR ;
    pstRchnCfg->enDataFmt            = XDP_PROC_FMT_SP_420     ;
    pstRchnCfg->enPkgFmt             = XDP_PKG_FMT_YUYV        ;
    pstRchnCfg->enRdMode             = XDP_RMODE_PROGRESSIVE   ;
    pstRchnCfg->enDataWidth          = XDP_DATA_WTH_8          ;

    pstRchnCfg->stInRect.u32X        = 0 ;
    pstRchnCfg->stInRect.u32Y        = 0 ;
    pstRchnCfg->stInRect.u32Wth      = 0 ;
    pstRchnCfg->stInRect.u32Hgt      = 0 ;

    pstRchnCfg->bFlipEn              = HI_FALSE ;
    pstRchnCfg->bMirrorEn            = HI_FALSE ;
    pstRchnCfg->bUvInvEn             = HI_FALSE ;
    pstRchnCfg->bTunlEn              = HI_FALSE ;
    pstRchnCfg->bMmuBypass           = HI_TRUE  ;
    pstRchnCfg->stMuteCfg.bMuteEn    = HI_FALSE ;
    pstRchnCfg->stMuteCfg.u32MuteY   = 0xff ;
    pstRchnCfg->stMuteCfg.u32MuteC   = 0xff ;

    pstRchnCfg->stDcmpCfg.enCmpType    = XDP_CMP_TYPE_OFF;

    pstRchnCfg->bSetFlag        = HI_FALSE ;
    pstRchnCfg->bAddrAutoCalcEn = HI_FALSE  ;
    pstRchnCfg->bAddrRandModeEn = HI_FALSE ;
    pstRchnCfg->bAddrSafeModeEn = HI_TRUE ;

    pstRchnCfg->bMmuBypass           = HI_TRUE;//(HI_BOOL)uGetRand(0,1);
#ifdef DEF_ST_TEST
    pstRchnCfg->bMmuBypass           = HI_FALSE;
#endif
    return;
}

HI_VOID VPSS_MAC_SetRchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg)
{
    HI_U32  u32RealOffset = 0;
    HI_BOOL bIsSoloData   = HI_FALSE;
    HI_S8   cName[80] ;

    if (pstRchnCfg->bSetFlag == HI_TRUE )
    {
        return;
    }
    else
    {
        pstRchnCfg->bSetFlag = HI_TRUE;
    }

    memset(cName, 0, sizeof(HI_S8) * 80);
    bIsSoloData  = VpssGetRchnClassType(enLayer);

    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_IMG_START_OFFSET);
    }
    else
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_SOLO_START_OFFSET);
    }

#if EDA_TEST
    cout << "------------------------------------------------------" << endl;
    VpssGetRchnLayerName(enLayer, cName);
    cout << __FUNCTION__ << "() channel name  = "   << cName << endl;
    cout << __FUNCTION__ << "() bIsSoloData   = "   << hex << bIsSoloData     << endl;
    cout << __FUNCTION__ << "() u32RealOffset = 0x" << hex << u32RealOffset * 4 << endl;

    cout << __FUNCTION__ << "() pstRchnCfg->bEn                                      = 0x" << hex << pstRchnCfg->bEn                                      << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bEn1                                     = 0x" << hex << pstRchnCfg->bEn1                                     << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->enDataType                               = 0x" << hex << pstRchnCfg->enDataType                               << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->enDataFmt                                = 0x" << hex << pstRchnCfg->enDataFmt                                << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->enPkgFmt                                 = 0x" << hex << pstRchnCfg->enPkgFmt                                 << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->enRdMode                                 = 0x" << hex << pstRchnCfg->enRdMode                                 << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->enDataWidth                              = 0x" << hex << pstRchnCfg->enDataWidth                              << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stInRect.u32Wth                          = "   << dec << pstRchnCfg->stInRect.u32Wth                          << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stInRect.u32Hgt                          = "   << dec << pstRchnCfg->stInRect.u32Hgt                          << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stInRect.u32X                            = "   << dec << pstRchnCfg->stInRect.u32X                            << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stInRect.u32Y                            = "   << dec << pstRchnCfg->stInRect.u32Y                            << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bFlipEn                                  = 0x" << hex << pstRchnCfg->bFlipEn                                  << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bMirrorEn                                = 0x" << hex << pstRchnCfg->bMirrorEn                                << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bUvInvEn                                 = 0x" << hex << pstRchnCfg->bUvInvEn                                 << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bMmuBypass                               = 0x" << hex << pstRchnCfg->bMmuBypass                               << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bTunlEn                                  = 0x" << hex << pstRchnCfg->bTunlEn                                  << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stMuteCfg.bMuteEn                        = 0x" << hex << pstRchnCfg->stMuteCfg.bMuteEn                        << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stMuteCfg.u32MuteY                       = 0x" << hex << pstRchnCfg->stMuteCfg.u32MuteY                       << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stMuteCfg.u32MuteC                       = 0x" << hex << pstRchnCfg->stMuteCfg.u32MuteC                       << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stDcmpCfg.enCmpType                      = 0x" << hex << pstRchnCfg->stDcmpCfg.enCmpType                      << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bAddrAutoCalcEn                          = 0x" << hex << pstRchnCfg->bAddrAutoCalcEn                          << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bAddrRandModeEn                          = 0x" << hex << pstRchnCfg->bAddrRandModeEn                          << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->bAddrSafeModeEn                          = 0x" << hex << pstRchnCfg->bAddrSafeModeEn                          << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr     = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr     << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr     = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr     << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr      = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr      << endl;
    cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr      = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr      << endl;
    if (enLayer == VPSS_MAC_RCHN_CF)
    {
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64VAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64VAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64VAddr = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64VAddr << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32YStr  = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32YStr  << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32CStr  = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32CStr  << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr       = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr       << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr       = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr       << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr       = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr       << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr        = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr        << endl;
        cout << __FUNCTION__ << "() pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr        = 0x" << hex << pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr        << endl;
    }
    cout << __FUNCTION__ << "() gu64VpssSafeAddr   = 0x" << hex << gu64VpssSafeAddr   << endl;
    cout << __FUNCTION__ << "() gu64VpssUnsafeAddr = 0x" << hex << gu64VpssUnsafeAddr << endl;
    cout << endl;
#endif
    if (HI_FALSE == bIsSoloData)
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_IMG_START_OFFSET);
        //---------------------------
        // Cfg
        //---------------------------
        VPSS_RCHN_SetEn         ( pstReg, u32RealOffset, pstRchnCfg->bEn                 );
        VPSS_RCHN_SetType       ( pstReg, u32RealOffset, pstRchnCfg->enDataType          );
        VPSS_RCHN_SetFormat     ( pstReg, u32RealOffset, pstRchnCfg->enDataFmt           );
        VPSS_RCHN_SetOrder      ( pstReg, u32RealOffset, pstRchnCfg->enPkgFmt            );
        VPSS_RCHN_SetLmRmode    ( pstReg, u32RealOffset, pstRchnCfg->enRdMode            );
        VPSS_RCHN_SetBitw       ( pstReg, u32RealOffset, pstRchnCfg->enDataWidth         );
        VPSS_RCHN_SetWidth      ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Wth - 1 );
        VPSS_RCHN_SetHeight     ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Hgt - 1 );
        VPSS_RCHN_SetHorOffset  ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32X       );
        VPSS_RCHN_SetVerOffset  ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Y       );
        VPSS_RCHN_SetFlip       ( pstReg, u32RealOffset, pstRchnCfg->bFlipEn             );
        VPSS_RCHN_SetMirror     ( pstReg, u32RealOffset, pstRchnCfg->bMirrorEn           );
        VPSS_RCHN_SetUvInvert   ( pstReg, u32RealOffset, pstRchnCfg->bUvInvEn            );
        VPSS_RCHN_SetTunlEn     ( pstReg, u32RealOffset, pstRchnCfg->bTunlEn             );
        VPSS_RCHN_SetDBypass    ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass          );
        VPSS_RCHN_SetHBypass    ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass          );
        VPSS_RCHN_Set2bBypass   ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass          );
        VPSS_RCHN_SetMuteEn     ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.bMuteEn   );
        VPSS_RCHN_SetCMuteVal   ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.u32MuteY  );
        VPSS_RCHN_SetYMuteVal   ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.u32MuteC  );
        //---------------------------
        // Addr
        //---------------------------
        VPSS_RCHN_SetYAddrH       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetCAddrH       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetCrAddrH      ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetYAddrL       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCAddrL       ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCrAddrL      ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetYStride      ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr );
        VPSS_RCHN_SetCStride      ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr );
        VPSS_RCHN_SetYTopHeadAddrH( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetCTopHeadAddrH( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetYTopHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCTopHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetYBotHeadAddrH( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetCBotHeadAddrH( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetYBotHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetCBotHeadAddrL( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetYHeadStride  ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr );
        VPSS_RCHN_SetCHeadStride  ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr );
        VPSS_RCHN_SetY2bAddrH     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetC2bAddrH     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SetY2bAddrL     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetC2bAddrL     ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr     ) & 0xffffffff) );
        VPSS_RCHN_SetY2bStride    ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr );
        VPSS_RCHN_SetC2bStride    ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr );
        //---------------------------
        // Dcmp
        //---------------------------
        VPSS_RCHN_SetDcmpMode         ( pstReg, u32RealOffset, pstRchnCfg->stDcmpCfg.enCmpType );

        //---------------------------
        //Assertion
        //---------------------------
        if (pstRchnCfg->bEn)
        {
            if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PACKAGE)
            {
                XDP_ASSERT(pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422);
            }
            else if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PLANAR)
            {
                XDP_ASSERT((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400));
            }

            XDP_ASSERT( pstRchnCfg->stInRect.u32Wth >= 31 );
            XDP_ASSERT( pstRchnCfg->stInRect.u32Hgt >= 16 );

            if (pstRchnCfg->bMirrorEn)
            {
                XDP_ASSERT(pstRchnCfg->stInRect.u32X == 0);
                XDP_ASSERT(pstRchnCfg->stInRect.u32Y == 0);
            }

            if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_8)
            {
                if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PACKAGE)
                {
                    XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr >= (pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) * 2 );
                }
                else if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR)
                {
                    XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr >= (pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) );
                    if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422))
                    {
                        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr >= (pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) );
                    }
                }
            }
            else if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_10)
            {
                if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR)
                {
                    XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr >= ((pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) * 10 + 7) / 8 );
                    if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_422))
                    {
                        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr >= ((pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) * 10 + 7) / 8 );
                    }
                }
            }

            if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_8)
            {
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteY <= 0xff);
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteC <= 0xff);
            }
            else
            {
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteY <= 0x3ff);
                XDP_ASSERT(pstRchnCfg->stMuteCfg.u32MuteC <= 0x3ff);
            }

            if ((VPSS_MAC_RCHN_CF != enLayer) && (VPSS_MAC_RCHN_P2 != enLayer) && (VPSS_MAC_RCHN_P1 != enLayer) && (VPSS_MAC_RCHN_P3 != enLayer))
            {
                XDP_ASSERT(pstRchnCfg->enDataWidth == XDP_DATA_WTH_8);
            }

            XDP_ASSERT(pstRchnCfg->enDataType != XDP_DATA_TYPE_PLANAR);

            if (VPSS_MAC_RCHN_CF != enLayer)
            {
                XDP_ASSERT(pstRchnCfg->bUvInvEn   == HI_FALSE);
                XDP_ASSERT(pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_LINEAR);
                XDP_ASSERT(pstRchnCfg->enDataFmt  != XDP_PROC_FMT_SP_400);
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_TOP   );
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_BOTTOM);
                XDP_ASSERT(pstRchnCfg->stInRect.u32X == 0);
                XDP_ASSERT(pstRchnCfg->stInRect.u32Y == 0);
            }

            if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_SEG)
            {
                XDP_ASSERT((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420));
                XDP_ASSERT(pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_TILE);
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_TOP   );
                XDP_ASSERT(pstRchnCfg->enRdMode != XDP_RMODE_BOTTOM);
            }
            else
            {
                XDP_ASSERT(pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF);
            }

            if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_TILE)
            {
                if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF)
                {
                    XDP_ASSERT(pstRchnCfg->enDataWidth == XDP_DATA_WTH_8);
                }
                XDP_ASSERT((pstRchnCfg->stInRect.u32Wth + pstRchnCfg->stInRect.u32X) <= 4096);
            }

            if ((pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_400) || (pstRchnCfg->enDataFmt == XDP_PROC_FMT_SP_420))
            {
                if (pstRchnCfg->enRdMode != XDP_RMODE_PROGRESSIVE)
                {
                    XDP_ASSERT((pstRchnCfg->stInRect.u32Y  % 4) == 0);
                    XDP_ASSERT((pstRchnCfg->stInRect.u32Hgt % 4) == 0);
                }
            }

        }
    }
    else
    {
        u32RealOffset = (gu32VpssRchnAddr[enLayer] - VPSS_RCHN_SOLO_START_OFFSET);
        //---------------------------
        //Cfg reso
        //---------------------------
        VPSS_RCHN_SOLO_SetEn           ( pstReg, u32RealOffset, pstRchnCfg->bEn                 );
        VPSS_RCHN_SOLO_SetEn1          ( pstReg, u32RealOffset, pstRchnCfg->bEn1                );
        VPSS_RCHN_SOLO_SetWidth        ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Wth - 1 );
        VPSS_RCHN_SOLO_SetHeight       ( pstReg, u32RealOffset, pstRchnCfg->stInRect.u32Hgt - 1 );
        VPSS_RCHN_SOLO_SetMuteEn       ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.bMuteEn   );
        VPSS_RCHN_SOLO_SetMuteVal0     ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.u32MuteY  );
        VPSS_RCHN_SOLO_SetMuteVal1     ( pstReg, u32RealOffset, pstRchnCfg->stMuteCfg.u32MuteC  );
        VPSS_RCHN_SOLO_SetTunleEn      ( pstReg, u32RealOffset, pstRchnCfg->bTunlEn             );
        VPSS_RCHN_SOLO_SetDBypass      ( pstReg, u32RealOffset, pstRchnCfg->bMmuBypass          );
        VPSS_RCHN_SOLO_SetFlip         ( pstReg, u32RealOffset, pstRchnCfg->bFlipEn             );
        VPSS_RCHN_SOLO_SetMirror       ( pstReg, u32RealOffset, pstRchnCfg->bMirrorEn           );
        //---------------------------
        // Addr
        //---------------------------
        VPSS_RCHN_SOLO_SetAddrH        ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr >> 32 ) & 0xffffffff) );
        VPSS_RCHN_SOLO_SetAddrL        ( pstReg, u32RealOffset, ((pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr     ) & 0xffffffff) );
        VPSS_RCHN_SOLO_SetStride       ( pstReg, u32RealOffset,   pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr                      );
        //---------------------------
        //Assertion
        //---------------------------
        if (pstRchnCfg->bEn)
        {
            // XDP_ASSERT(pstRchnCfg->enRdMode == XDP_RMODE_PROGRESSIVE);
            XDP_ASSERT(pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF);
        }
    }


    //---------------------------
    //Assertion
    //---------------------------
    if (pstRchnCfg->bEn)
    {
        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr % 16 == 0);
        XDP_ASSERT(pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr % 16 == 0);
        XDP_ASSERT(pstRchnCfg->stInRect.u32Wth <= gu32VpssRchnMaxWth[enLayer]);
        //  XDP_ASSERT(pstRchnCfg->stInRect.u32Hgt <= gu32VpssRchnMaxHgt[enLayer]);
    }

    if ((VPSS_MAC_RCHN_P1RGMV != enLayer) && (VPSS_MAC_RCHN_P2RGMV != enLayer))
    {
        XDP_ASSERT(pstRchnCfg->bEn1 == HI_FALSE);
    }

    return;
}

HI_U64 VPSS_MAC_RchnCalcAddrStr(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg, HI_U64 u64StartAddr, HI_BOOL bRandModeEn)
{
    HI_U32 u32SrcWth = 0;
    HI_U32 u32SrcHgt = 0;

    HI_BOOL bIsSoloData   = HI_FALSE;

    HI_U32  u32DataWidth  = 0;
    HI_U32  u32DataWidthY = 0;
    HI_U32  u32DataWidthC = 0;
    HI_U32  u32DataWidthHead = 4;
    HI_U32  u32DataWidthSeg  = 64 * 8;
    HI_U32  u32DataWidthExt  = 64 * 2;

    XDP_SOLO_ADDR_S stAddrTemp;
    XDP_RECT_S stRectY;
    XDP_RECT_S stRectC;

    XDP_ASSERT((u64StartAddr % 16) == 0);
    stAddrTemp.u64Addr = u64StartAddr;

    if ((pstRchnCfg->bEn == HI_FALSE) && (pstRchnCfg->bEn1 == HI_FALSE))
    {
        pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
        pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
        pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
        pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = 0 ;
        pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = 0 ;
    }
    else
    {
        u32SrcWth = pstRchnCfg->stInRect.u32X + pstRchnCfg->stInRect.u32Wth;
        u32SrcHgt = pstRchnCfg->stInRect.u32Y + pstRchnCfg->stInRect.u32Hgt;

        bIsSoloData  = VpssGetRchnClassType(enLayer);

        if (HI_FALSE == bIsSoloData)
        {
            // YC data reso
            stRectY.u32Wth = pstRchnCfg->stInRect.u32X + pstRchnCfg->stInRect.u32Wth;
            stRectY.u32Hgt = pstRchnCfg->stInRect.u32Y + pstRchnCfg->stInRect.u32Hgt;
            if (pstRchnCfg->enDataType == XDP_DATA_TYPE_SP_TILE)
            {
                stRectY.u32Wth = VpssUpAlign(stRectY.u32Wth, 64);
                stRectY.u32Hgt = VpssUpAlign(stRectY.u32Hgt, 16);
            }
            // need modify here
            //if((pstRchnCfg->enRdMode == VDP_RMODE_PRO_TOP)||(pstRchnCfg->enRdMode == VDP_RMODE_PRO_BOTTOM))
            //{
            //    XDP_ASSERT((stRectY.u32Hgt%2) == 0);
            //    stRectY.u32Hgt /= 2;
            //}
            stRectC.u32Wth = VpssCalcChmWth(stRectY.u32Wth, pstRchnCfg->enDataFmt);
            stRectC.u32Hgt = VpssCalcChmHgt(stRectY.u32Hgt, pstRchnCfg->enDataFmt);

            if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_OFF)
            {
                // YC data bitdepth
                switch (pstRchnCfg->enDataWidth)
                {
                    case XDP_DATA_WTH_8 : u32DataWidth = 8 ; break;
                    case XDP_DATA_WTH_10: u32DataWidth = 10; break;
                    case XDP_DATA_WTH_12: u32DataWidth = 12; break;
                    case XDP_DATA_WTH_16: u32DataWidth = 16; break;
                    default: XDP_ASSERT(0);
                }

                switch (pstRchnCfg->enDataType)
                {
                    case XDP_DATA_TYPE_SP_LINEAR:
                    case XDP_DATA_TYPE_SP_TILE:
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
                    case XDP_DATA_TYPE_PLANAR:
                    {
                        u32DataWidthY  = u32DataWidth;
                        u32DataWidthC  = u32DataWidth;
                    }
                    default: XDP_ASSERT(0);
                }
                // Y data addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidthY, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = stAddrTemp.u32Str;
                // C data addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectC, u32DataWidthC, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = stAddrTemp.u32Str;
                if (pstRchnCfg->enDataType == XDP_DATA_TYPE_PLANAR)
                {
                    stAddrTemp.u64Addr = stAddrTemp.u64Addr + stAddrTemp.u32Str * stRectC.u32Hgt;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
                }
                else
                {
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
                }
                // no used addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64VAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64VAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32YStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32CStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = 0;
            }
            else if (pstRchnCfg->stDcmpCfg.enCmpType == XDP_CMP_TYPE_SEG)
            {
                // YC seg reso
                XDP_ASSERT((stRectY.u32Wth % 64    ) == 0);
                XDP_ASSERT((stRectY.u32Hgt % 2     ) == 0);
                XDP_ASSERT(((stRectC.u32Wth * 2) % 64) == 0);
                XDP_ASSERT((stRectC.u32Hgt % 2     ) == 0);
                stRectY.u32Wth = stRectY.u32Wth / 64     ;
                stRectY.u32Hgt = stRectY.u32Hgt        ;
                stRectC.u32Wth = (stRectC.u32Wth * 2) / 64 ;
                stRectC.u32Hgt = stRectC.u32Hgt        ;

                // Y data addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidthSeg, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = stAddrTemp.u32Str;
                // C data addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectC, u32DataWidthSeg, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = stAddrTemp.u32Str;

                if (pstRchnCfg->enDataWidth == XDP_DATA_WTH_10)
                {
                    // Y extend addr
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = stAddrTemp.u64Addr;
                    VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidthExt, bRandModeEn);
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = stAddrTemp.u32Str;
                    // C extend addr
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = stAddrTemp.u64Addr;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr = stAddrTemp.u64Addr;
                    VPSS_CalcAddrStr(&stAddrTemp, &stRectC, u32DataWidthExt, bRandModeEn);
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = stAddrTemp.u32Str;
                }
                else
                {
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = stAddrTemp.u64Addr;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = stAddrTemp.u64Addr;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr = stAddrTemp.u64Addr;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = 0;
                    pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = 0;
                }
                stRectY.u32Hgt = stRectY.u32Hgt / 2;
                stRectC.u32Hgt = stRectC.u32Hgt / 2;

                // Y head addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidthHead, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = stAddrTemp.u32Str;
                // C head addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64VAddr = stAddrTemp.u64Addr;
                VPSS_CalcAddrStr(&stAddrTemp, &stRectC, u32DataWidthHead, bRandModeEn);
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = stAddrTemp.u32Str;

                // no used addr
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64VAddr = stAddrTemp.u64Addr;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32YStr  = 0;
                pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32CStr  = 0;
            }
            else
            {
                XDP_ASSERT(0);
            }
        }
        else
        {
            // YC data reso
            stRectY.u32Wth = pstRchnCfg->stInRect.u32X + pstRchnCfg->stInRect.u32Wth;
            stRectY.u32Hgt = pstRchnCfg->stInRect.u32Y + pstRchnCfg->stInRect.u32Hgt;
            u32DataWidth  = VpssGetRchnDataWidth(enLayer);
            // Y data addr
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = stAddrTemp.u64Addr;
            VPSS_CalcAddrStr(&stAddrTemp, &stRectY, u32DataWidth, bRandModeEn);
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = stAddrTemp.u32Str;
            // C data addr
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64UAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u64VAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_DATA].u32CStr  = 0;
            // no used addr
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64YAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64UAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u64VAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32YStr  = 0;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_TOP].u32CStr  = 0;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64YAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64UAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u64VAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32YStr  = 0;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_HEAD_BOT].u32CStr  = 0;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64YAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64UAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u64VAddr = stAddrTemp.u64Addr;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32YStr  = 0;
            pstRchnCfg->stAddr[VPSS_RCHN_ADDR_2B].u32CStr  = 0;
        }
    }

    return stAddrTemp.u64Addr;
}

