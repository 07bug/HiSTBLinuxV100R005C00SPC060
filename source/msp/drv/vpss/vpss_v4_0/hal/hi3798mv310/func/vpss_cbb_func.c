#include "vpss_cbb_reg.h"
#include "vpss_cbb_func.h"



#define HI_PQ_VPSS_PORT0_LAYER_ZME 0


HI_VOID VPSS_FuncCfg_VC1(CBB_FUNC_VC1_S *pstFuncVC1Cfg, CBB_FRAME_CHANNEL_E enChan, CBB_REG_ADDR_S stRegAddr)
{

    return ;


}

HI_VOID VPSS_FuncCfg_VPZme(CBB_FUNC_VPZME_S *pstFuncVPZmeCfg, CBB_REG_ADDR_S stRegAddr)
{
    return ;

}

HI_VOID VPSS_FuncCfg_Zme(CBB_FUNC_ZME_S *pstFuncZmeCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    U_VPSS_ZME_ADDR VPSS_ZME_ADDR;
    U_VPSS_CTRL3 VPSS_CTRL3;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_ZME_ADDR.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssNode->VPSS_ZME_ADDR.u32));
    VPSS_ZME_ADDR.bits.zme_cfg_addr = pstFuncZmeCfg->u32ParAddr;
    VPSS_RegWrite((HI_U32 *) & (pstVpssNode->VPSS_ZME_ADDR.u32), VPSS_ZME_ADDR.u32);
    VPSS_CTRL3.u32 = VPSS_RegRead((HI_U32 *) & (pstVpssNode->VPSS_CTRL3.u32));
    VPSS_CTRL3.bits.zme_vhd0_en = pstFuncZmeCfg->bEnable;
    VPSS_RegWrite((HI_U32 *) & (pstVpssNode->VPSS_CTRL3.u32), VPSS_CTRL3.u32);

    DRV_PQ_SetVpssZme(HI_PQ_VPSS_PORT0_LAYER_ZME,
                      pstVpssNode,
                      &(pstFuncZmeCfg->stZmeDrvPara),
                      HI_TRUE);
    return ;
}

HI_VOID VPSS_FuncCfg_Crop(CBB_FUNC_CROP_S *pstFuncCropCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Sys_SetVhd0CropEn      (pstVpssNode, 0,  pstFuncCropCfg->bEnable);
    VPSS_DRV_Set_VPSS_VHD0CROP_POS(pstVpssNode, pstFuncCropCfg->stCropCfg.s32Y,
                                   pstFuncCropCfg->stCropCfg.s32X);

    VPSS_DRV_Set_VPSS_VHD0CROP_SIZE(pstVpssNode,
                                    pstFuncCropCfg->stCropCfg.s32Height,
                                    pstFuncCropCfg->stCropCfg.s32Width);
    return;
}

HI_VOID VPSS_FuncCfg_LBox(CBB_FUNC_LBOX_S *pstFuncLBoxCfg, CBB_REG_ADDR_S stRegAddr)
{

    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址

    HI_U32 vhd0_vbk_y    = 0;
    HI_U32 vhd0_vbk_cb   = 0;
    HI_U32 vhd0_vbk_cr   = 0;
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if (pstFuncLBoxCfg->eBGColor >= CBB_COLOR_BUTT)
    {
        return;
    }

    switch (pstFuncLBoxCfg->eBGColor)
    {
        case CBB_COLOR_BLACK:
            vhd0_vbk_y = 0;
            vhd0_vbk_cb = 0x80;
            vhd0_vbk_cr = 0x80;
            break;
        case CBB_COLOR_WHITE:
            vhd0_vbk_y = 0xff;
            vhd0_vbk_cb = 0x80;
            vhd0_vbk_cr = 0x80;
            break;
        case CBB_COLOR_GREEN:
            vhd0_vbk_y = 0xff;
            vhd0_vbk_cb = 0x20;
            vhd0_vbk_cr = 0x20;
            break;
        case CBB_COLOR_BLUE:
            vhd0_vbk_y = 0x0;
            vhd0_vbk_cb = 0xFF;
            vhd0_vbk_cr = 0;
            break;
        case CBB_COLOR_YELLOW:
            vhd0_vbk_y = 0xFF;
            vhd0_vbk_cb = 0x00;
            vhd0_vbk_cr = 0xFF;
            break;
        default://red
            vhd0_vbk_y = 0x0;
            vhd0_vbk_cb = 0x0;
            vhd0_vbk_cr = 0xFF;
            break;
    }

    vhd0_vbk_y = vhd0_vbk_y << 2; //10bit reg
    vhd0_vbk_cb = vhd0_vbk_cb << 2;
    vhd0_vbk_cr = vhd0_vbk_cr << 2;

    VPSS_DRV_Set_VPSS_VHD0LBA_BK(pstVpssNode, vhd0_vbk_y, vhd0_vbk_cb, vhd0_vbk_cr);
    VPSS_DRV_Set_VPSS_VHD0LBA_VFPOS(pstVpssNode, pstFuncLBoxCfg->stLBoxRect.s32Y, pstFuncLBoxCfg->stLBoxRect.s32X);
    VPSS_DRV_Set_VPSS_VHD0LBA_DSIZE(pstVpssNode, pstFuncLBoxCfg->stLBoxRect.s32Height, pstFuncLBoxCfg->stLBoxRect.s32Width);
    VPSS_Sys_SetVhd0LbaEn    (pstVpssNode, 0 , pstFuncLBoxCfg->bEnable);

    return ;
}


HI_VOID VPSS_FuncCfg_Flip(CBB_FUNC_FLIP_S *pstFuncFlipCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_WCHN_SetFlip        ( pstVpssNode, 0x0, pstFuncFlipCfg->bFlipV);
    VPSS_WCHN_SetMirror      ( pstVpssNode, 0x0, pstFuncFlipCfg->bFlipH);
    return ;
}

HI_VOID VPSS_FuncCfg_InUVRevert(CBB_FUNC_UV_S *pstUvInvertCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_RCHN_SetUvInvert    ( pstVpssNode, 0x0, pstUvInvertCfg->bEnable);
    return ;
}

HI_VOID VPSS_FuncCfg_UVRevert(CBB_FUNC_UV_S *pstUvInvertCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_WCHN_SetUvInvert    ( pstVpssNode, 0x0, pstUvInvertCfg->bEnable);
    return ;
}
HI_VOID VPSS_FuncCfg_TunneIn(CBB_FUNC_TUNNELIN_S *pstTunnelInCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstReg = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;
    VPSS_MAC_SetCfRtunlEn(pstReg, pstTunnelInCfg->bEnable);
    VPSS_MAC_SetCfRtunlBypass(pstReg, !pstTunnelInCfg->bSmmu);
    VPSS_MAC_SetCfRtunlInterval(pstReg, pstTunnelInCfg->u32ReadInterval);
    VPSS_MAC_SetCfRtunlAddr(pstReg, pstTunnelInCfg->u32ReadAddr);
#if 0
    VPSS_FATAL("en:%d smmu:%d rdIntv:%d addr:%#x\n",
               pstTunnelInCfg->bEnable,
               pstTunnelInCfg->bSmmu,
               pstTunnelInCfg->u32ReadInterval,
               pstTunnelInCfg->u32ReadAddr
              );
#endif


}

HI_VOID VPSS_FuncCfg_TunneOut(CBB_FUNC_TUNNELOUT_S *pstTunnelOutCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstReg = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_MAC_SetOut0WtunlEn(pstReg, pstTunnelOutCfg->bEnable);
    VPSS_MAC_SetOut0WtunlMode(pstReg, pstTunnelOutCfg->eMode);
    VPSS_MAC_SetOut0WtunlFinishLine(pstReg, pstTunnelOutCfg->u32FinishLine);
    VPSS_MAC_SetOut0WtunlAddr(pstReg, pstTunnelOutCfg->u32WriteAddr);

    return ;
}

HI_VOID VPSS_FuncCfg_Trans(CBB_FUNC_TRANS_S *pstTransCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    HI_U8 *pu8MetaSrcVirAddr = HI_NULL;
    HI_U8 *pu8MetaDstVirAddr = HI_NULL;
    HI_U32 u32MetaSize = 0;

    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    if ((HI_TRUE == pstTransCfg->bEnable) && (HI_TRUE == pstTransCfg->bSecure))
    {
        u32MetaSize = pstTransCfg->u32Size * 256;
        if (u32MetaSize < 256)
        {
            u32MetaSize = 256;
        }
        if (u32MetaSize > 4096)
        {
            u32MetaSize = 4096;
        }

        pu8MetaSrcVirAddr = VPSS_OSAL_MEMMap(HI_FALSE, pstTransCfg->u32SrcAddr);
        if (HI_NULL == pu8MetaSrcVirAddr)
        {
            VPSS_ERROR("VPSS_OSAL_MEMMap err, Metadata src addr:%#\n", pstTransCfg->u32SrcAddr);
            return;
        }

        pu8MetaDstVirAddr = VPSS_OSAL_MEMMap(HI_FALSE, pstTransCfg->u32DstAddr);
        if (HI_NULL == pu8MetaDstVirAddr)
        {
            VPSS_OSAL_MEMUnmap(HI_FALSE, pstTransCfg->u32SrcAddr, pu8MetaSrcVirAddr);
            VPSS_ERROR("VPSS_OSAL_MEMMap err, Metadata dst addr:%#\n", pstTransCfg->u32DstAddr);
            return;
        }

        VPSS_SAFE_MEMCPY(pu8MetaDstVirAddr, pu8MetaSrcVirAddr, u32MetaSize);
        VPSS_OSAL_MEMUnmap(HI_FALSE, pstTransCfg->u32SrcAddr, pu8MetaSrcVirAddr);
        VPSS_OSAL_MEMUnmap(HI_FALSE, pstTransCfg->u32DstAddr, pu8MetaDstVirAddr);
    }
    else
    {
#if 0
        VPSS_ERROR("src %#x dst %#x en %d size%d sec %d smmu %d\n",
                   pstTransCfg->u32SrcAddr,
                   pstTransCfg->u32DstAddr,
                   pstTransCfg->bEnable,
                   pstTransCfg->u32Size,
                   pstTransCfg->bSecure,
                   pstTransCfg->bSmmu
                  );
#endif
        VPSS_DRV_Set_VPSS_TRANS_SRC_ADDR(pstVpssNode, pstTransCfg->u32SrcAddr);
        VPSS_DRV_Set_VPSS_TRANS_DES_ADDR(pstVpssNode, pstTransCfg->u32DstAddr);
        VPSS_DRV_Set_VPSS_TRANS_INFO    (pstVpssNode, pstTransCfg->bEnable, pstTransCfg->u32Size,
                                         !pstTransCfg->bSecure, !pstTransCfg->bSmmu);
    }
}

HI_VOID VPSS_FuncCfg_SMMU(CBB_FUNC_SMMU_S *pstSMMUCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssGloablAddr; //全局地址
    S_VPSS_REGS_TYPE *pstVpssNode; //DDR中节点首地址
    pstVpssGloablAddr = (S_VPSS_REGS_TYPE *)stRegAddr.pu8BaseVirAddr;
    pstVpssNode       = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_MMU_SetGlbBypass    ( pstVpssGloablAddr, 0x0, pstSMMUCfg->bGlobalBypass);
    VPSS_MMU_SetIntEn        ( pstVpssGloablAddr, 0x0, pstSMMUCfg->bIntEnable     );
    VPSS_MMU_SetPtwPf        ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32Ptw_pf    );

    //VPSS_MMU_SetScbTtbr      ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32SCB_TTBR      );
    //VPSS_MMU_SetErrSRdAddr   ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32Err_s_rd_addr );
    //VPSS_MMU_SetErrSWrAddr   ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32Err_s_wr_addr );
    VPSS_MMU_SetCbTtbr       ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32CB_TTBR         );

    VPSS_MMU_SetErrNsRdAddr  ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32Err_ns_rd_addr);
    VPSS_MMU_SetErrNsWrAddr  ( pstVpssGloablAddr, 0x0, pstSMMUCfg->u32Err_ns_wr_addr);

    return ;
}

HI_VOID VPSS_FuncCfg_ROTATIONYC(CBB_FUNC_ROTATION_YC_S *pstRotaCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    //VPSS_FATAL("ROTATIONYC %d %d %d\n", pstRotaCfg->u32Angle, pstRotaCfg->u32ImgProcessMode, pstRotaCfg->bEnable);

    VPSS_MAC_SetRotateEn            ( pstVpssNode, pstRotaCfg->bEnable);
    VPSS_MAC_SetImgProMode          ( pstVpssNode, pstRotaCfg->u32ImgProcessMode);
    VPSS_MAC_SetRotateAngle         ( pstVpssNode, pstRotaCfg->u32Angle);
    return ;
}

HI_VOID VPSS_FuncCfg_4PIXEL(CBB_FUNC_4PIXEL_S *pst4PixelCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    VPSS_Sys_SetFourPixEn(pstVpssNode, 0, pst4PixelCfg->bEnable);
    return ;
}

HI_VOID VPSS_FuncCfg_CTS10BIT(CBB_FUNC_CTS10BIT_S *pstCts10BitCfg, CBB_REG_ADDR_S stRegAddr)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    pstVpssNode->VPSS_OUT0_CTRL.bits.out0_cts_en = pstCts10BitCfg->bEnable;
    pstVpssNode->VPSS_OUT0_CTRL.bits.out0_cts_bit_sel = pstCts10BitCfg->bBitSel_LOW10;
    return ;
}

HI_VOID VPSS_FuncCfg_FDIFRO(CBB_FUNC_FDIFRO_S *pstFdIFrOCfg, CBB_REG_ADDR_S stRegAddr)
{
    return ;
}

