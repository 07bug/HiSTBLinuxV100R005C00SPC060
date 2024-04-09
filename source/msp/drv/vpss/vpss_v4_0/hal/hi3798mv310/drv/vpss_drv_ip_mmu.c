#include "vpss_drv_ip_mmu.h"
#include "vpss_hal_ip_mmu.h"
#include "vpss_drv_comm.h"

HI_VOID VPSS_MMU_InitCfg(XDP_MMU_CFG_S *pstMmuCfg)
{
    pstMmuCfg->bSmmuEn                         = HI_FALSE;
    pstMmuCfg->bCkGtEn                         = HI_FALSE;
    pstMmuCfg->bIntEn                          = HI_FALSE;
    pstMmuCfg->u32PtwOutstd                    = 15;

    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr  = 0x0f8000000;
    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr = 0x000011f00;
    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr = 0x000010f00;
    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr  = 0x0f8000000;
    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr = 0x000001f00;
    pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr = 0x000000f00;
}


HI_VOID VPSS_MMU_SetCfg(S_VPSS_REGS_TYPE *pstReg, HI_U32 u32Layer, XDP_MMU_CFG_S *pstMmuCfg)
{

#if EDA_TEST
    cout << "[drv] pstMmuCfg->bSmmuEn                              = 0x" << hex << pstMmuCfg->bSmmuEn                                         << endl;
    cout << "[drv] pstMmuCfg->bCkGtEn                              = 0x" << hex << pstMmuCfg->bCkGtEn                                         << endl;
    cout << "[drv] pstMmuCfg->bIntEn                               = 0x" << hex << pstMmuCfg->bIntEn                                          << endl;
    cout << "[drv] pstMmuCfg->u32PtwOutstd                         = 0x" << hex << pstMmuCfg->u32PtwOutstd                                    << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr  = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr  << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr  = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr  << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr << endl;
    cout << "[drv] stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr = 0x" << hex << pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr << endl;
#endif

    VPSS_MMU_SetGlbBypass    ( pstReg, u32Layer, !(pstMmuCfg->bSmmuEn)   ) ;
    VPSS_MMU_SetAutoClkGtEn  ( pstReg, u32Layer, pstMmuCfg->bCkGtEn      ) ;
    VPSS_MMU_SetIntEn        ( pstReg, u32Layer, pstMmuCfg->bIntEn       ) ;
    VPSS_MMU_SetPtwPf        ( pstReg, u32Layer, pstMmuCfg->u32PtwOutstd ) ;

    // VPSS_MMU_SetScbTtbrH     ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr  >>32 ) & 0xffffffff) );
    // VPSS_MMU_SetErrSRdAddrH  ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr >>32 ) & 0xffffffff) );
    // VPSS_MMU_SetErrSWrAddrH  ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr >>32 ) & 0xffffffff) );
    // VPSS_MMU_SetCbTtbrH      ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr  >>32 ) & 0xffffffff) );
    // VPSS_MMU_SetErrNsRdAddrH ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr >>32 ) & 0xffffffff) );
    // VPSS_MMU_SetErrNsWrAddrH ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr >>32 ) & 0xffffffff) );

    VPSS_MMU_SetScbTtbr      ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr       ) & 0xffffffff) );
    VPSS_MMU_SetErrSRdAddr   ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr      ) & 0xffffffff) );
    VPSS_MMU_SetErrSWrAddr   ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr      ) & 0xffffffff) );
    VPSS_MMU_SetCbTtbr       ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr       ) & 0xffffffff) );
    VPSS_MMU_SetErrNsRdAddr  ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr      ) & 0xffffffff) );
    VPSS_MMU_SetErrNsWrAddr  ( pstReg, u32Layer, ((pstMmuCfg->stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr      ) & 0xffffffff) );

    return;
}

