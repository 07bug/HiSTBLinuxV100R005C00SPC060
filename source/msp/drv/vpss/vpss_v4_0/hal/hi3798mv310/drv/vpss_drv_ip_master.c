#if 0

#include "vpss_drv_ip_master.h"
#include "vpss_hal_ip_master.h"
#include "vpss_drv_comm.h"


HI_VOID VPSS_Master_InitCfg(VPSS_MASTER_CFG_S *pstMasterCfg)
{
    HI_U32 ii = 0;
    memset(pstMasterCfg, 0, sizeof(VPSS_MASTER_CFG_S));

    pstMasterCfg->bMidEn                                = HI_TRUE;
    pstMasterCfg->bArbEn                                = HI_FALSE;
    pstMasterCfg->enSplitMode                           = VPSS_AXI_EDGE_MODE_256;
    pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0]         = 15;
    pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0]         = 7;
    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        pstMasterCfg->u32RchnPrio[ii] = 0;//uGetRandEx(0,1);
        pstMasterCfg->enRchnSel[ii]   = VPSS_MASTER_SEL_0;
    }
    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        pstMasterCfg->u32WchnPrio[ii] = 0;//uGetRandEx(0,1);
        pstMasterCfg->enWchnSel[ii]   = VPSS_MASTER_SEL_0;
    }
    return;
}


HI_VOID VPSS_Master_SetCfg( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg)
{
    HI_U32 ii = 0;
#if EDA_TEST
#ifdef MAC_DRV_DEBUG
    cout << "[drv] pstMasterCfg->bMidEn                        = 0x" << hex << pstMasterCfg->bMidEn                         << endl;
    cout << "[drv] pstMasterCfg->bArbEn                        = 0x" << hex << pstMasterCfg->bArbEn                         << endl;
    cout << "[drv] pstMasterCfg->enSplitMode                   = 0x" << hex << pstMasterCfg->enSplitMode                    << endl;
    cout << "[drv] pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0]= 0x" << hex << pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0] << endl;
    cout << "[drv] pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0]= 0x" << hex << pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0] << endl;
    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->u32RchnPrio[" << ii << "] = 0x" << hex << pstMasterCfg->u32RchnPrio[ii] << endl;
        cout << "[drv] pstMasterCfg->enRchnSel  [" << ii << "] = 0x" << hex << pstMasterCfg->enRchnSel[ii]   << endl;
    }
    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->u32WchnPrio[" << ii << "] = 0x" << hex << pstMasterCfg->u32WchnPrio[ii] << endl;
        cout << "[drv] pstMasterCfg->enWchnSel  [" << ii << "] = 0x" << hex << pstMasterCfg->enWchnSel[ii]   << endl;
    }
#endif
#endif
    VPSS_MASTER_SetMidEnable         (pstReg, pstMasterCfg->bMidEn                         );
    VPSS_MASTER_SetArbMode           (pstReg, pstMasterCfg->bArbEn                         );
    VPSS_MASTER_SetSplitMode         (pstReg, pstMasterCfg->enSplitMode                    );
    VPSS_MASTER_SetMstr0Routstanding (pstReg, pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0] );
    VPSS_MASTER_SetMstr0Woutstanding (pstReg, pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0] );

    for (ii = 0; ii < 64 ; ii = ii + 1)
    {
        VPSS_MASTER_SetRchnPrio(pstReg, ii, pstMasterCfg->u32RchnPrio[ii]);
        VPSS_MASTER_SetRchnSel (pstReg, ii, pstMasterCfg->enRchnSel[ii]  );
    }

    for (ii = 0; ii < 64 ; ii = ii + 1)
    {
        VPSS_MASTER_SetWchnPrio(pstReg, ii, pstMasterCfg->u32WchnPrio[ii]);
        VPSS_MASTER_SetWchnSel (pstReg, ii, pstMasterCfg->enWchnSel[ii]  );
    }

    XDP_ASSERT(pstMasterCfg->enSplitMode != VPSS_AXI_EDGE_MODE_128);

    return;
}

HI_VOID VPSS_Master_SetStaticCfg( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg)
{
    HI_U32 ii = 0;
#if EDA_TEST
#ifdef MAC_DRV_DEBUG
    cout << "[drv] pstMasterCfg->bMidEn       = 0x" << hex << pstMasterCfg->bMidEn                                 << endl;
    cout << "[drv] pstMasterCfg->enSplitMode  = 0x" << hex << pstMasterCfg->enSplitMode                            << endl;
    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->enRchnSel  [" << ii << "] = 0x" << hex << pstMasterCfg->enRchnSel[ii]   << endl;
    }
    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->enWchnSel  [" << ii << "] = 0x" << hex << pstMasterCfg->enWchnSel[ii]   << endl;
    }
#endif
#endif
    VPSS_MASTER_SetMidEnable         (pstReg, pstMasterCfg->bMidEn                         );
    VPSS_MASTER_SetSplitMode         (pstReg, pstMasterCfg->enSplitMode                    );

    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        VPSS_MASTER_SetRchnSel (pstReg, ii, pstMasterCfg->enRchnSel[ii]  );
    }

    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        VPSS_MASTER_SetWchnSel (pstReg, ii, pstMasterCfg->enWchnSel[ii]  );
    }

    return;
}

HI_VOID VPSS_Master_SetDynamicCfg( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg)
{
    HI_U32 ii = 0;
#if EDA_TEST
#ifdef MAC_DRV_DEBUG
    cout << "[drv] pstMasterCfg->bArbEn                                 = 0x" << hex << pstMasterCfg->bArbEn                                 << endl;
    cout << "[drv] pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0]          = 0x" << hex << pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0]          << endl;
    cout << "[drv] pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0]          = 0x" << hex << pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0]          << endl;
    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->u32RchnPrio[" << ii << "] = 0x" << hex << pstMasterCfg->u32RchnPrio[ii] << endl;
    }
    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        cout << "[drv] pstMasterCfg->u32WchnPrio[" << ii << "] = 0x" << hex << pstMasterCfg->u32WchnPrio[ii] << endl;
    }
#endif
#endif
    VPSS_MASTER_SetArbMode           (pstReg, pstMasterCfg->bArbEn                         );
    VPSS_MASTER_SetMstr0Routstanding (pstReg, pstMasterCfg->u32RdOutstd[VPSS_MASTER_SEL_0] );
    VPSS_MASTER_SetMstr0Woutstanding (pstReg, pstMasterCfg->u32WrOutstd[VPSS_MASTER_SEL_0] );

    for (ii = 0; ii < VPSS_RCHN_MAX ; ii = ii + 1)
    {
        VPSS_MASTER_SetRchnPrio(pstReg, ii, pstMasterCfg->u32RchnPrio[ii]);
    }

    for (ii = 0; ii < VPSS_WCHN_MAX ; ii = ii + 1)
    {
        VPSS_MASTER_SetWchnPrio(pstReg, ii, pstMasterCfg->u32WchnPrio[ii]);
    }

    return;
}

#endif

