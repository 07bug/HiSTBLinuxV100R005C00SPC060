#include "outer_depend.h"

#include "vdp_hal_comm.h"
#include "vdp_hal_gfx.h"

#include "vdp_drv_func.h"
extern S_VDP_REGS_TYPE *pVdpReg;


extern HI_S32 sGetRandEx(HI_S32 max, HI_S32 min);

HI_VOID VDP_GFX_SetPreMultEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    U_G0_CBMPARA G0_CBMPARA;
    if (u32Data >= GFX_MAX)
    {
        VDP_PRINT("Error,VDP_SetGfxPreMultEnable() Select Wrong Graph Layer ID\n");
        return ;
    }
    G0_CBMPARA.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->G0_CBMPARA.u32) + u32Data * GFX_OFFSET));
    G0_CBMPARA.bits.premult_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->G0_CBMPARA.u32) + u32Data * GFX_OFFSET), G0_CBMPARA.u32);
}

#if GP0_EN


HI_VOID  VDP_GP_SetRegUp  (HI_U32 u32Data)
{
    U_GP0_UPD GP0_UPD;

    /* GP layer register update */
    if (u32Data >= GP_MAX)
    {
        VDP_PRINT("Error,VDP_GP_SetRegUp() Select Wrong GP Layer ID\n");
        return ;
    }

    GP0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_UPD.u32) + u32Data * GP_OFFSET), GP0_UPD.u32);

    return ;
}

HI_VOID VDP_GP_SetDePreMultEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    U_GP0_CTRL GP0_CTRL;
    if (u32Data >= GP_MAX)
    {
        VDP_PRINT("Error,VDP_GP_SetDePreMultEnable  Select Wrong Graph Layer ID\n");
        return ;
    }

    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->GP0_CTRL.u32) + u32Data * GP_OFFSET));
    GP0_CTRL.bits.depremult_en = bEnable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->GP0_CTRL.u32) + u32Data * GP_OFFSET), GP0_CTRL.u32);
}

HI_VOID  VDP_GP_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    U_GP0_CSC_IDC  GP0_CSC_IDC;
    U_GP0_CSC_ODC  GP0_CSC_ODC;
    U_GP0_CSC_IODC GP0_CSC_IODC;

    if(u32Data >= GP_MAX)
    {
        VDP_PRINT("Error,VDP_GP_SetCscDcCoef() Select Wrong GPeo Layer ID\n");
        return ;
    }

    GP0_CSC_IDC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_IDC.u32) + u32Data * GP_OFFSET));
    GP0_CSC_IDC.bits.cscidc1  = pstCscCoef.csc_in_dc1;
    GP0_CSC_IDC.bits.cscidc0  = pstCscCoef.csc_in_dc0;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_IDC.u32) + u32Data * GP_OFFSET), GP0_CSC_IDC.u32);

    GP0_CSC_ODC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_ODC.u32) + u32Data * GP_OFFSET));
    GP0_CSC_ODC.bits.cscodc1 = pstCscCoef.csc_out_dc1;
    GP0_CSC_ODC.bits.cscodc0 = pstCscCoef.csc_out_dc0;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_ODC.u32) + u32Data * GP_OFFSET), GP0_CSC_ODC.u32);

    GP0_CSC_IODC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_IODC.u32) + u32Data * GP_OFFSET));
    GP0_CSC_IODC.bits.cscodc2 = pstCscCoef.csc_out_dc2;
    GP0_CSC_IODC.bits.cscidc2 = pstCscCoef.csc_in_dc2;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_IODC.u32) + u32Data * GP_OFFSET), GP0_CSC_IODC.u32);

    return ;
}

HI_VOID   VDP_GP_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    U_GP0_CSC_P0 GP0_CSC_P0;
    U_GP0_CSC_P1 GP0_CSC_P1;
    U_GP0_CSC_P2 GP0_CSC_P2;
    U_GP0_CSC_P3 GP0_CSC_P3;
    U_GP0_CSC_P4 GP0_CSC_P4;
    if(u32Data >= GP_MAX)
    {
        VDP_PRINT("Error,VDP_GP_SetCscCoef Select Wrong GPeo ID\n");
        return ;
    }


    GP0_CSC_P0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_P0.u32)+u32Data*GP_OFFSET));
    GP0_CSC_P0.bits.cscp00 = stCscCoef.csc_coef00;
    GP0_CSC_P0.bits.cscp01 = stCscCoef.csc_coef01;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_P0.u32)+u32Data*GP_OFFSET), GP0_CSC_P0.u32);

    GP0_CSC_P1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_P1.u32)+u32Data*GP_OFFSET));
    GP0_CSC_P1.bits.cscp02 = stCscCoef.csc_coef02;
    GP0_CSC_P1.bits.cscp10 = stCscCoef.csc_coef10;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_P1.u32)+u32Data*GP_OFFSET), GP0_CSC_P1.u32);

    GP0_CSC_P2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_P2.u32)+u32Data*GP_OFFSET));
    GP0_CSC_P2.bits.cscp11 = stCscCoef.csc_coef11;
    GP0_CSC_P2.bits.cscp12 = stCscCoef.csc_coef12;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_P2.u32)+u32Data*GP_OFFSET), GP0_CSC_P2.u32);

    GP0_CSC_P3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_P3.u32)+u32Data*GP_OFFSET));
    GP0_CSC_P3.bits.cscp20 = stCscCoef.csc_coef20;
    GP0_CSC_P3.bits.cscp21 = stCscCoef.csc_coef21;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_P3.u32)+u32Data*GP_OFFSET), GP0_CSC_P3.u32);

    GP0_CSC_P4.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CSC_P4.u32)+u32Data*GP_OFFSET));
    GP0_CSC_P4.bits.cscp22 = stCscCoef.csc_coef22;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CSC_P4.u32)+u32Data*GP_OFFSET), GP0_CSC_P4.u32);

}


#endif //end of GP0_EN

HI_VOID VDP_GFX_MixvBypassEn (HI_U32 u32En)
{
    U_MIXG0_MIX_BYPASS MIXG0_MIX_BYPASS;

    MIXG0_MIX_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)));
    MIXG0_MIX_BYPASS.bits.layer0_bypass_en = u32En ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)), MIXG0_MIX_BYPASS.u32);
}

HI_VOID VDP_GFX_MixvPremultEn (HI_U32 u32En)
{
    U_MIXG0_MIX_BYPASS MIXG0_MIX_BYPASS;

    MIXG0_MIX_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)));
    MIXG0_MIX_BYPASS.bits.layer0_premulti = u32En ;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)), MIXG0_MIX_BYPASS.u32);
}

HI_VOID VDP_GFX_MixvBypassMode (HI_U32 u32Mode)
{
    U_MIXG0_MIX_BYPASS MIXG0_MIX_BYPASS;

    MIXG0_MIX_BYPASS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)));
    MIXG0_MIX_BYPASS.bits.mix1_bypass_mode =  u32Mode;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->MIXG0_MIX_BYPASS.u32)), MIXG0_MIX_BYPASS.u32);
}


HI_VOID VDP_DRV_CalculateTotalGfxPixel(HI_U32 *pu32TotalGfxPixel)
{
    volatile U_GP0_IRESO GP0_IRESO;
    GP0_IRESO.u32    = VDP_RegRead(((HI_ULONG)(&(pVdpReg->GP0_IRESO.u32)) + VDP_LAYER_GFX0 * GP_OFFSET));
    *pu32TotalGfxPixel = (GP0_IRESO.bits.iw + 1) * (GP0_IRESO.bits.ih + 1);
    return;
}

HI_VOID VDP_DRV_GetZeroAlphaSum(HI_U32 *pu32ZeroAlphaSum)
{
    volatile U_GP0_GALPHA_SUM GP0_GALPHA_SUM;
    GP0_GALPHA_SUM.u32 = VDP_RegRead((HI_ULONG)(&(pVdpReg->GP0_GALPHA_SUM.u32)));
    *pu32ZeroAlphaSum = GP0_GALPHA_SUM.u32;
    return;
}

HI_VOID VDP_DRV_GetGfxState(HI_BOOL *pbNeedProcessGfx)
{
    volatile U_G0_CTRL G0_CTRL;
    HI_U32 u32TotalPixels = 0;
    HI_U32 u32SumZeroAlpha = 0;

    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->G0_CTRL.u32) + VDP_LAYER_GFX0 * GFX_OFFSET));

    if (HI_FALSE == G0_CTRL.bits.surface_en)
    {
        *pbNeedProcessGfx = HI_FALSE;
        return;
    }

    if (VDP_GFX_IFMT_ARGB_8888 != G0_CTRL.bits.ifmt)
    {
        *pbNeedProcessGfx = HI_FALSE;
        return;
    }

    VDP_DRV_CalculateTotalGfxPixel(&u32TotalPixels);
    VDP_DRV_GetZeroAlphaSum(&u32SumZeroAlpha);

    if (u32TotalPixels == u32SumZeroAlpha)
    {
        *pbNeedProcessGfx = HI_FALSE;
        return;
    }

    *pbNeedProcessGfx = HI_TRUE;
    return;
}

