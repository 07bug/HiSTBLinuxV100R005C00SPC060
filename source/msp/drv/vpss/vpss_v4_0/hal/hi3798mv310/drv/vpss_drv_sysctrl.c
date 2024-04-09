#include "vpss_drv_sysctrl.h"
#include "vpss_hal_reg.h"
#include "vpss_drv_ip_master.h"
#include "vpss_drv_ip_mmu.h"
#include "vpss_drv_mac_ctrl.h"
#include "vpss_hal_mac_ctrl.h"
#include "vpss_mac_define.h"

#if EDA_TEST
#include "xdp_mmu.h"
#endif


HI_VOID VPSS_FUNC_SetListComm(S_VPSS_REGS_TYPE *pVpssReg)
{
#if 0
    VPSS_MASTER_CFG_S stMasterCfg;
#if EDA_TEST
    XDP_MMU_CFG_S stMmuCfg;
    XDP_MMU_INFO_S stMmuInfo;
#endif

    VPSS_Sys_SetIntMask(pVpssReg, 0x0, 0x1ff);
    VPSS_Sys_SetInitTimer(pVpssReg, 0, 50);

    VPSS_Master_InitCfg(&stMasterCfg);
    stMasterCfg.bMidEn                                = HI_TRUE;//can not switch in one tc
#ifdef MST_MID_OFF
    stMasterCfg.bMidEn                                = HI_FALSE;
#endif
    stMasterCfg.bArbEn                                = (HI_BOOL)uGetRandEx(0, 1);
    stMasterCfg.enSplitMode                           = (VPSS_AXI_EDGE_MODE_E)uGetRandEx(1, 4);
    stMasterCfg.u32RdOutstd[VPSS_MASTER_SEL_0]        = uGetRandEx(0, 15);
    stMasterCfg.u32WrOutstd[VPSS_MASTER_SEL_0]        = uGetRandEx(0, 7);

#ifdef DEF_ST_TEST
    stMasterCfg.bMidEn                                = HI_TRUE;//can not switch in one tc
    stMasterCfg.bArbEn                                = HI_TRUE;
    stMasterCfg.enSplitMode                           = VPSS_AXI_EDGE_MODE_256;
    stMasterCfg.u32RdOutstd[VPSS_MASTER_SEL_0]        = 15;
    stMasterCfg.u32WrOutstd[VPSS_MASTER_SEL_0]        = 7;
#endif
    VPSS_Master_SetCfg(pVpssReg, &stMasterCfg);

#if EDA_TEST
    VPSS_MMU_InitCfg(&stMmuCfg);

    stMmuCfg.bSmmuEn                         = (HI_BOOL)uGetRandEx(0, 1);
    stMmuCfg.bCkGtEn                         = (HI_BOOL)uGetRandEx(0, 1);
    stMmuCfg.bIntEn                          = HI_TRUE;
    stMmuCfg.u32PtwOutstd                    = uGetRandEx(0, 15);

#ifdef VPSS_IT_MMU_ON
    stMmuCfg.bSmmuEn                         = HI_TRUE;
#endif
#ifdef VPSS_IT_MMU_OFF
    stMmuCfg.bSmmuEn                         = HI_FALSE;
#endif

#ifdef DEF_ST_TEST
    stMmuCfg.bSmmuEn                         = HI_FALSE;
    stMmuCfg.bCkGtEn                         = HI_TRUE;
    stMmuCfg.bIntEn                          = HI_TRUE;
    stMmuCfg.u32PtwOutstd                    = 15;
#endif

#ifdef VPSS_IT_PQ_CFG
    stMmuCfg.bSmmuEn                         = HI_FALSE;
#endif

    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr  = 0x108000f40;
    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64RdErrAddr = 0x100001f00;
    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64WrErrAddr = 0x100000f00;
    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64PageAddr  = 0x008000f40;
    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64RdErrAddr = 0x000011f00;
    stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_SAFE  ].u64WrErrAddr = 0x000010f00;
    // VPSS_MMU_SetCfg(pVpssReg, 0, &stMmuCfg);

    //--------------------------------------------
    stMmuInfo.enTestMode = XDP_MMU_TEST_MODE_SEC;
    stMmuInfo.enPageMode = XDP_MMU_PAGE_MODE_RAND;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64PageAddr = stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_UNSAFE].u64PageAddr;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64VirAddrS = 0x110000000;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64VirAddrE = 0x17fffffff;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64PhyAddrS = stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64VirAddrS + 0x080000000;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64PhyAddrE = stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_UNSAFE].u64VirAddrE + 0x080000000;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64PageAddr = stMmuCfg.stAddr[XDP_MMU_SECURE_MODE_SAFE].u64PageAddr;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64VirAddrS = 0x010000000;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64VirAddrE = 0x07fffffff;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64PhyAddrS = stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64VirAddrS + 0x080000000;
    stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64PhyAddrE = stMmuInfo.stAddr[XDP_MMU_ADDR_MODE_SAFE  ].u64VirAddrE + 0x080000000;
    // XdpMmuPageGen(&stMmuInfo);
    //--------------------------------------------
#endif
#endif
}

HI_VOID VPSS_FUNC_SetNodeComm(S_VPSS_REGS_TYPE *pVpssReg)
{
    VPSS_MAC_CTRL_CFG_S stCfg;
    //HI_U32 ii;

    VPSS_MAC_InitCtrlCfg(&stCfg);

    stCfg.enReqLen      = (XDP_REQ_LENGTH_E)uGetRandEx(0, 1);
    stCfg.enReqCtrl     = (XDP_REQ_CTRL_E)uGetRandEx(0, 2);
    stCfg.bSecEn        = (HI_BOOL)uGetRandEx(0, 1);

#ifdef VPSS_IT_PQ_CFG
    stCfg.bSecEn        = HI_FALSE;
#endif

#if EDA_TEST
    VPSS_MAC_SetSttWAddr(pVpssReg, VPSS_STT_WADDR);
#endif

    VPSS_MAC_SetCfRtunlAddr(pVpssReg, 0x90000000);

    VPSS_MAC_SetOut0WtunlAddr(pVpssReg, 0x91000000);

    // VPSS_MAC_SetCtrlCfg(pVpssReg, &stCfg);

    VPSS_AddrInit(&gstVpssAddrCfg, 0x20000000);
}

