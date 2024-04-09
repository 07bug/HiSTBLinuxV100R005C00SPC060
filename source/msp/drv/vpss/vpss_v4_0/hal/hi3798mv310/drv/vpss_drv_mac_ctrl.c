#include "vpss_drv_mac_ctrl.h"
#include "vpss_hal_mac_ctrl.h"
#include "vpss_drv_comm.h"


HI_VOID VPSS_MAC_InitCtrlCfg(VPSS_MAC_CTRL_CFG_S *pstCfg)
{
    memset(pstCfg, 0, sizeof(VPSS_MAC_CTRL_CFG_S));

    pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT    ] = 0x08000000 ;
    pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_RD_TUNL   ] = 0x09000000 ;
    pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_TUNL   ] = 0x0a000000 ;

    pstCfg->bSecEn        = HI_FALSE               ;
    pstCfg->enReqLen      = XDP_REQ_LENGTH_16      ;
    pstCfg->enReqCtrl     = XDP_REQ_CTRL_16BURST_4 ;
    pstCfg->enProcComp    = VPSS_PROC_COMP_YC_BOTH ;
    pstCfg->bDmaEn        = HI_FALSE               ;
    pstCfg->bRotateEn     = HI_FALSE               ;
    pstCfg->enRotateAngle = VPSS_ROTATE_ANGLE_90   ;

    pstCfg->bRdTunlEn           = HI_FALSE;
    pstCfg->bRdTunlMmuBypass    = HI_TRUE;
    pstCfg->u32RdTunlIntval     = 0;

    pstCfg->bWrTunlEn           = HI_FALSE;
    pstCfg->enWTunlMode         = VPSS_TUNL_MODE_2LINE;
    pstCfg->u32WrTunlFinishLine = 0;

    pstCfg->stPatternCfg.bEn                = HI_FALSE;
    pstCfg->stPatternCfg.enAngleMode        = VPSS_PATTERN_MODE_DEGREE_30;
    pstCfg->stPatternCfg.u32LineWidth       = 0x7;
    pstCfg->stPatternCfg.stBkgColor.u32BkgU = 0x7f;
    pstCfg->stPatternCfg.stBkgColor.u32BkgV = 0x7f;
    return;
}


HI_VOID VPSS_MAC_SetCtrlCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_CTRL_CFG_S *pstCfg)
{
#if EDA_TEST
    cout << __FUNCTION__ << "------------------------------------------------------" << endl;
    cout << __FUNCTION__ << "() pstCfg->bSecEn                              = 0x" << hex << pstCfg->bSecEn                              << endl;
    cout << __FUNCTION__ << "() pstCfg->enReqLen                            = 0x" << hex << pstCfg->enReqLen                            << endl;
    cout << __FUNCTION__ << "() pstCfg->enReqCtrl                           = 0x" << hex << pstCfg->enReqCtrl                           << endl;
    cout << __FUNCTION__ << "() pstCfg->enProcComp                          = 0x" << hex << pstCfg->enProcComp                          << endl;
    cout << __FUNCTION__ << "() pstCfg->bDmaEn                              = 0x" << hex << pstCfg->bDmaEn                              << endl;
    cout << __FUNCTION__ << "() pstCfg->bRotateEn                           = 0x" << hex << pstCfg->bRotateEn                           << endl;
    cout << __FUNCTION__ << "() pstCfg->enRotateAngle                       = 0x" << hex << pstCfg->enRotateAngle                       << endl;
    cout << __FUNCTION__ << "() pstCfg->bRdTunlEn                           = 0x" << hex << pstCfg->bRdTunlEn                           << endl;
    cout << __FUNCTION__ << "() pstCfg->bRdTunlMmuBypass                    = 0x" << hex << pstCfg->bRdTunlMmuBypass                    << endl;
    cout << __FUNCTION__ << "() pstCfg->u32RdTunlIntval                     = 0x" << hex << pstCfg->u32RdTunlIntval                     << endl;
    cout << __FUNCTION__ << "() pstCfg->bWrTunlEn                           = 0x" << hex << pstCfg->bWrTunlEn                           << endl;
    cout << __FUNCTION__ << "() pstCfg->enWTunlMode                         = 0x" << hex << pstCfg->enWTunlMode                         << endl;
    cout << __FUNCTION__ << "() pstCfg->u32WrTunlFinishLine                 = 0x" << hex << pstCfg->u32WrTunlFinishLine                 << endl;
    cout << __FUNCTION__ << "() pstCfg->stPatternCfg.bEn                    = 0x" << hex << pstCfg->stPatternCfg.bEn                    << endl;
    cout << __FUNCTION__ << "() pstCfg->stPatternCfg.enAngleMode            = 0x" << hex << pstCfg->stPatternCfg.enAngleMode            << endl;
    cout << __FUNCTION__ << "() pstCfg->stPatternCfg.u32LineWidth           = 0x" << hex << pstCfg->stPatternCfg.u32LineWidth           << endl;
    cout << __FUNCTION__ << "() pstCfg->stPatternCfg.stBkgColor.u32BkgU     = 0x" << hex << pstCfg->stPatternCfg.stBkgColor.u32BkgU     << endl;
    cout << __FUNCTION__ << "() pstCfg->stPatternCfg.stBkgColor.u32BkgV     = 0x" << hex << pstCfg->stPatternCfg.stBkgColor.u32BkgV     << endl;
    cout << __FUNCTION__ << "() pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT ] = 0x" << hex << pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT ] << endl;
    cout << __FUNCTION__ << "() pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_RD_TUNL] = 0x" << hex << pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_RD_TUNL] << endl;
    cout << __FUNCTION__ << "() pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_TUNL] = 0x" << hex << pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_TUNL] << endl;
    cout << endl;
#endif

    if (pstCfg->bSecEn)
    {
        VPSS_MAC_SetProt( pstReg, 0x0 );
    }
    else
    {
        VPSS_MAC_SetProt( pstReg, 0x2 );
    }

    VPSS_MAC_SetMaxReqLen           ( pstReg, pstCfg->enReqLen            );
    VPSS_MAC_SetMaxReqNum           ( pstReg, pstCfg->enReqCtrl           );
    VPSS_MAC_SetImgProMode          ( pstReg, pstCfg->enProcComp          );

    VPSS_MAC_SetDmaEn               ( pstReg, pstCfg->bDmaEn              );
    VPSS_MAC_SetRotateEn            ( pstReg, pstCfg->bRotateEn           );
    VPSS_MAC_SetRotateAngle         ( pstReg, pstCfg->enRotateAngle       );

    VPSS_MAC_SetCfRtunlEn           ( pstReg, pstCfg->bRdTunlEn           );
    VPSS_MAC_SetCfRtunlBypass       ( pstReg, pstCfg->bRdTunlMmuBypass    );
    VPSS_MAC_SetCfRtunlInterval     ( pstReg, pstCfg->u32RdTunlIntval     );

    VPSS_MAC_SetOut0WtunlEn         ( pstReg, pstCfg->bWrTunlEn           );
    VPSS_MAC_SetOut0WtunlMode       ( pstReg, pstCfg->enWTunlMode         );
    VPSS_MAC_SetOut0WtunlFinishLine ( pstReg, pstCfg->u32WrTunlFinishLine );

    VPSS_MAC_SetTestPatEn           ( pstReg, pstCfg->stPatternCfg.bEn                );
    VPSS_MAC_SetPatAngle            ( pstReg, pstCfg->stPatternCfg.enAngleMode        );
    VPSS_MAC_SetPatDisWidth         ( pstReg, pstCfg->stPatternCfg.u32LineWidth       );
    VPSS_MAC_SetPatBkgrndU          ( pstReg, pstCfg->stPatternCfg.stBkgColor.u32BkgU );
    VPSS_MAC_SetPatBkgrndV          ( pstReg, pstCfg->stPatternCfg.stBkgColor.u32BkgV );

    VPSS_MAC_SetSttWAddr            ( pstReg,   pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT ]);
    VPSS_MAC_SetCfRtunlAddr         ( pstReg,   pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_RD_TUNL]);
    VPSS_MAC_SetOut0WtunlAddr       ( pstReg,   pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_TUNL]);

    //---------------------------
    //Assertion
    //---------------------------
    XDP_ASSERT(pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT] < 0x100000000 );
    XDP_ASSERT(pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT] < 0x100000000 );
    XDP_ASSERT(pstCfg->u64Addr[VPSS_MAC_ADDR_CTRL_WR_STT] < 0x100000000 );
    XDP_ASSERT(pstCfg->stPatternCfg.stBkgColor.u32BkgU < 0x100 );
    XDP_ASSERT(pstCfg->stPatternCfg.stBkgColor.u32BkgV < 0x100 );

    return;
}

