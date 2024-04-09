#include "vpss_cbb_info.h"
//#include "vpss_cbb_reg.h"

HI_VOID VPSS_InfoCfg_Dei_ST(CBB_INFO_S *pstInfoDeiCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_DI_RST;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_DI_WST;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoDeiCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoDeiCfg->bSmmu_R;
    stRchnCfg.stInRect.u32Wth = pstInfoDeiCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoDeiCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoDeiCfg->u32RPhyAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoDeiCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoDeiCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoDeiCfg->bSmmu_W;
    stWchnCfg.stOutRect.u32Wth = pstInfoDeiCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoDeiCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoDeiCfg->u32WPhyAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoDeiCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}

HI_VOID VPSS_InfoGet_All(S_VPSS_STT_REGS_TYPE *pstSttReg, CBB_INFO_S *pstInfoStt)
{
    //VPSS_SAFE_MEMCPY(pstSttReg, pstInfoStt->pu8RVirAddr, sizeof(S_STT_REGS_TYPE));
}

HI_VOID VPSS_InfoCfg_Prjv(CBB_INFO_PRJV_S *pstInfoPrjvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_RPRJV;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_WPRJV;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoPrjvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoPrjvCfg->bSmmu_Cur;
    stRchnCfg.stInRect.u32Wth = pstInfoPrjvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoPrjvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoPrjvCfg->u32CurReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoPrjvCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoPrjvCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoPrjvCfg->bSmmu_Nx2;
    stWchnCfg.stOutRect.u32Wth = pstInfoPrjvCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoPrjvCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoPrjvCfg->u32Nx2WriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoPrjvCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_Prjh(CBB_INFO_PRJH_S *pstInfoPrjhCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_RPRJH;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_WPRJH;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoPrjhCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoPrjhCfg->bSmmu_Cur;
    stRchnCfg.stInRect.u32Wth = pstInfoPrjhCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoPrjhCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoPrjhCfg->u32CurReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoPrjhCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoPrjhCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoPrjhCfg->bSmmu_Nx2;
    stWchnCfg.stOutRect.u32Wth = pstInfoPrjhCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoPrjhCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoPrjhCfg->u32Nx2WriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoPrjhCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}


HI_VOID VPSS_InfoCfg_Di(CBB_INFO_DI_S *pstInfoDiCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_DI_STCNT;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_DI_STCNT;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoDiCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoDiCfg->bSmmu_r;
    stRchnCfg.stInRect.u32Wth = pstInfoDiCfg->u32Width;
    stRchnCfg.stInRect.u32Hgt = pstInfoDiCfg->u32Hight;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoDiCfg->u32ReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoDiCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoDiCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoDiCfg->bSmmu_w;
    stWchnCfg.stOutRect.u32Wth = pstInfoDiCfg->u32Width;
    stWchnCfg.stOutRect.u32Hgt = pstInfoDiCfg->u32Hight;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoDiCfg->u32WriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoDiCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}


HI_VOID VPSS_InfoCfg_Blkmv(CBB_INFO_BLKMV_S *pstInfoBlkmvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_P2MV;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_CFMV;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoBlkmvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoBlkmvCfg->bSmmu_Cur;
    stRchnCfg.stInRect.u32Wth = pstInfoBlkmvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoBlkmvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoBlkmvCfg->u32CurReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoBlkmvCfg->u32Stride;
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    enVpssMacRchn             = VPSS_MAC_RCHN_P3MV;
    stRchnCfg.bSetFlag        = HI_FALSE;
    stRchnCfg.bEn             = pstInfoBlkmvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoBlkmvCfg->bSmmu_Ref;
    stRchnCfg.stInRect.u32Wth = pstInfoBlkmvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoBlkmvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoBlkmvCfg->u32RefReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoBlkmvCfg->u32Stride;
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoBlkmvCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoBlkmvCfg->bSmmu_Nx1;
    stWchnCfg.stOutRect.u32Wth = pstInfoBlkmvCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoBlkmvCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoBlkmvCfg->u32Nx1WriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoBlkmvCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_Blkmt(CBB_INFO_BLKMT_S *pstInfoBlkmtCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_P3MT;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_P2MT;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoBlkmtCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoBlkmtCfg->bSmmu_Ref;
    stRchnCfg.stInRect.u32Wth = pstInfoBlkmtCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoBlkmtCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoBlkmtCfg->u32RefReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoBlkmtCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoBlkmtCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoBlkmtCfg->bSmmu_Cur;
    stWchnCfg.stOutRect.u32Wth = pstInfoBlkmtCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoBlkmtCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoBlkmtCfg->u32CurWriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoBlkmtCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_Rgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_P1RGMV;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_CFRGMV;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoRgmvCfg->bEn;
    stRchnCfg.bEn1            = pstInfoRgmvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoRgmvCfg->bSmmu_Nx1;
    stRchnCfg.stInRect.u32Wth = pstInfoRgmvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoRgmvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoRgmvCfg->u32Nx1ReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoRgmvCfg->u32Stride;
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    enVpssMacRchn             = VPSS_MAC_RCHN_P2RGMV;
    stRchnCfg.bSetFlag        = HI_FALSE;
    stRchnCfg.bEn             = pstInfoRgmvCfg->bEn;
    stRchnCfg.bEn1            = pstInfoRgmvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoRgmvCfg->bSmmu_Cur;
    stRchnCfg.stInRect.u32Wth = pstInfoRgmvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoRgmvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoRgmvCfg->u32CurReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoRgmvCfg->u32Stride;
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoRgmvCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoRgmvCfg->bSmmu_Nx2;
    stWchnCfg.stOutRect.u32Wth = pstInfoRgmvCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoRgmvCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoRgmvCfg->u32Nx2WriteAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoRgmvCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_TnrRgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_P2RGMV;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoRgmvCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoRgmvCfg->bSmmu_Cur;
    stRchnCfg.stInRect.u32Wth = pstInfoRgmvCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoRgmvCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoRgmvCfg->u32CurReadAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoRgmvCfg->u32Stride;
    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_Snr_Mad(CBB_INFO_S *pstInfoSnrCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_NR_RMAD;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoSnrCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoSnrCfg->bSmmu_R;
    stRchnCfg.stInRect.u32Wth = pstInfoSnrCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoSnrCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoSnrCfg->u32RPhyAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoSnrCfg->u32Stride;

#if 0
    VPSS_DBG_INFO("en:%d bsmmu:%d w h %d %d yadd:%#x, stid:%d\n",
                  stRchnCfg.bEn,
                  stRchnCfg.bMmuBypass,
                  stRchnCfg.stInRect.u32Wth,
                  stRchnCfg.stInRect.u32Hgt,
                  pstInfoSnrCfg->u32RPhyAddr,
                  stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr
                 );
#endif

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    return ;
}

HI_VOID VPSS_InfoCfg_Tnr_Mad(CBB_INFO_S *pstInfoTnrCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    VPSS_MAC_RCHN_CFG_S stRchnCfg = {0};
    VPSS_MAC_WCHN_CFG_S stWchnCfg = {0};
    VPSS_MAC_RCHN_E enVpssMacRchn = VPSS_MAC_RCHN_NR_RMAD;
    VPSS_MAC_WCHN_E enVpssMacWchn = VPSS_MAC_WCHN_NR_WMAD;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //read chn
    stRchnCfg.bEn             = pstInfoTnrCfg->bEn;
    stRchnCfg.bMmuBypass      = !pstInfoTnrCfg->bSmmu_R;
    stRchnCfg.stInRect.u32Wth = pstInfoTnrCfg->u32Wth;
    stRchnCfg.stInRect.u32Hgt = pstInfoTnrCfg->u32Hgt;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoTnrCfg->u32RPhyAddr;
    stRchnCfg.stAddr[VPSS_RCHN_ADDR_DATA].u32YStr  = pstInfoTnrCfg->u32Stride;

    CBB_MAC_SetRchnCfg(pstVpssNode, enVpssMacRchn, &stRchnCfg);

    //write chn
    stWchnCfg.bEn              = pstInfoTnrCfg->bEn;
    stWchnCfg.bMmuBypass       = !pstInfoTnrCfg->bSmmu_W;
    stWchnCfg.stOutRect.u32Wth = pstInfoTnrCfg->u32Wth;
    stWchnCfg.stOutRect.u32Hgt = pstInfoTnrCfg->u32Hgt;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u64YAddr = (HI_U64)pstInfoTnrCfg->u32WPhyAddr;
    stWchnCfg.stAddr[VPSS_WCHN_ADDR_DATA].u32YStr  = pstInfoTnrCfg->u32Stride;

    CBB_MAC_SetWchnCfg(pstVpssNode, enVpssMacWchn, &stWchnCfg);

    return ;
}


HI_VOID VPSS_InfoCfg_SttInfo(CBB_INFO_S *pstInfoStt, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR??????
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstVpssNode->VPSS_STT_W_ADDR_LOW.u32 = pstInfoStt->u32WPhyAddr;

    return ;
}

