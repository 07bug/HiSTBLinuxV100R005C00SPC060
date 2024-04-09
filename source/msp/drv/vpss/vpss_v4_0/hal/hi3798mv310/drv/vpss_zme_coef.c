
//drv_func.cpp begin
#include "vpss_zme_coef.h"
#include "scaler_rom.h"

//#include <stdio.h>
#if 0
inline HI_U32 VPSS_DRV_Conver_ScaleCoef(HI_S32 s32Value)
{
    HI_U32 temp = 0;

    if (s32Value >= 0)
    {
        return s32Value;
    }
    else
    {
        temp = (-1) * s32Value;
        return ( ((~temp) + 1) & 0x3FF);
    }
}
#endif

HI_VOID vpss_sclhorlumacoef_to_dut(HI_U32 coef_start_addr, const HI_S16 arr[17][6])          //for 17*6
{

    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  k = 0;
    HI_U32  i, j;
    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 6; j++)
        {
            temp[j % 2] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);

            if (j % 2 == 1)
            {
                u32OutData = (temp[1] << 16) + temp[0];
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
                k++;
            }
        }
    }
}

HI_VOID vpss_sclverlumacoef_to_dut(HI_U32 coef_start_addr, const HI_S16 arr[17][4])           //for 17*4
{

    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  k = 0;
    HI_U32  i, j;
    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[j % 2] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);

            if (j % 2 == 1)
            {
                u32OutData = (temp[1] << 16) + temp[0];
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
                k++;
            }
        }
    }
}

HI_VOID vpss_sclchromacoef_to_dut(HI_U32 coef_start_addr, const HI_S16 arr[17][4])           //for 17*4
{
    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  k = 0;
    HI_U32  i, j;
    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[j % 2] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);
            if (j % 2 == 1)
            {
                u32OutData = (temp[1] << 16) + temp[0];
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
                k++;
            }
        }
    }
}

HI_S32  VPSS_zmecoef_to_dut(VPSS_ZME_CFG_S *pstCfg)
{
    HI_U32 HYRatio, VYRatio, HCRatio, VCRatio;
    HI_U32 vir_addr;
    HI_U32  y_in_w, y_in_h, y_out_w, y_out_h;
    HI_U32  c_in_w, c_in_h, c_out_w, c_out_h;
    int cur_b420;

    cur_b420 = pstCfg->in_fmt;

    y_in_w  = pstCfg->iw;
    y_in_h  = pstCfg->ih;
    c_in_w  = pstCfg->iw >> 1;
    c_in_h  = pstCfg->ih >> (cur_b420 == 1);

    y_out_w = pstCfg->ow;
    y_out_h = pstCfg->oh;
    c_out_w = pstCfg->ow >> 1;
    c_out_h = pstCfg->oh >> (cur_b420 == 1);

    //HYRatio = (VPSS_MULTI*(HI_U64)y_out_w)/y_in_w;
    //VYRatio = (VPSS_MULTI1*(HI_U64)y_out_h)/y_in_h;
    //HCRatio = (VPSS_MULTI*(HI_U64)c_out_w)/c_in_w;
    //VCRatio = (VPSS_MULTI1*(HI_U64)c_out_h)/c_in_h;

    HYRatio = (VPSS_MULTI * y_out_w) / y_in_w;
    VYRatio = (VPSS_MULTI1 * y_out_h) / y_in_h;
    HCRatio = (VPSS_MULTI * c_out_w) / c_in_w;
    VCRatio = (VPSS_MULTI1 * c_out_h) / c_in_h;
    // printf("HYRatio = %d,VYRatio = %d,HCRatio = %d,VCRatio = %d\n",HYRatio,VYRatio,HCRatio,VCRatio);
    //水平亮度缩放系数
    vir_addr = (HI_U32)pstCfg->vir_lhaddr;
    if (HYRatio > VPSS_MULTI)         //HYRatio 输出/输入
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_66M_a20);
    }
    else if (HYRatio == VPSS_MULTI)
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_cubic);
    }
    else if (HYRatio >= VPSS_MULTI * 3 / 4)
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_6M_a25);
    }
    else if (HYRatio >= VPSS_MULTI / 2)
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_5M_a25);

    }
    else if (HYRatio >= VPSS_MULTI / 3)
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_4M_a20);

    }
    else if (HYRatio >= VPSS_MULTI / 4)
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_35M_a18);

    }
    else
    {
        vpss_sclhorlumacoef_to_dut(vir_addr, vpss_coef6Tap); //coef6Tap_35M_a18);

    }

    //垂直亮度缩放系数
    vir_addr = (HI_U32)pstCfg->vir_lvaddr;

    if (VYRatio > VPSS_MULTI1)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VYRatio == VPSS_MULTI1)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_cubic);
    }
    else if (VYRatio >= VPSS_MULTI1 * 3 / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VYRatio >= VPSS_MULTI1 / 2)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VYRatio >= VPSS_MULTI1 / 3)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else if (VYRatio >= VPSS_MULTI1 / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }

    //水平色度缩放系数  //s5v100 改成8阶
    vir_addr = (HI_U32)pstCfg->vir_chaddr;

    if (HCRatio > VPSS_MULTI)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (HCRatio == VPSS_MULTI)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_cubic);
    }
    else if (HCRatio >= VPSS_MULTI * 3 / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (HCRatio >= VPSS_MULTI / 2)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (HCRatio >= VPSS_MULTI / 3)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else if (HCRatio >= VPSS_MULTI / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }

    //垂直色度缩放系数 //
    vir_addr = (HI_U32)pstCfg->vir_cvaddr;
    if (VCRatio > VPSS_MULTI1)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VCRatio == VPSS_MULTI1)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_cubic);
    }
    else if (VCRatio >= VPSS_MULTI1 * 3 / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VCRatio >= VPSS_MULTI1 / 2)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_5M_a15);
    }
    else if (VCRatio >= VPSS_MULTI1 / 3)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else if (VCRatio >= VPSS_MULTI1 / 4)
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    else
    {
        vpss_sclverlumacoef_to_dut(vir_addr, vpss_coef4Tap); //coef4Tap_4M_a15);
    }
    return 0;
}
#if 0
HI_VOID VPSS_FUNC_SetZmeMode(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_ZME_MODE_E ZmeMode, VPSS_ZME_CFG_S *pstCfg)
{
    {
        HI_U32         hratio   = 0;
        HI_U32         vratio   = 0;
        HI_U32         out_fmt  ;
        HI_S32         hchfir_en;
        HI_S32         hlfir_en;
        HI_S32         hchmid_en;
        HI_S32         hlmid_en;
        HI_S32         hchmsc_en;
        HI_S32         hlmsc_en;

        HI_S32         vchfir_en;
        HI_S32         vlfir_en;
        HI_S32         vchmid_en;
        HI_S32         vlmid_en;
        HI_S32         vchmsc_en;
        HI_S32         vlmsc_en;


        HI_S32         hor_coffset;
        HI_S32         vchroma_offset;
        HI_S32         vluma_offset;

        HI_U32         scl_lh;
        HI_U32         scl_lv;
        HI_U32         scl_ch;
        HI_U32         scl_cv;

        scl_lh            = pstCfg->lhaddr;
        scl_lv            = pstCfg->lvaddr;
        scl_ch            = pstCfg->chaddr;
        scl_cv            = pstCfg->cvaddr;

        out_fmt           = pstCfg->out_fmt;

        hratio            = (VPSS_MULTI * (HI_U64)pstCfg->iw) / pstCfg->ow;
        vratio            = (VPSS_MULTI1 * (HI_U64)pstCfg->ih) / pstCfg->oh;


        hchfir_en   = pstCfg->hchfir_en;
        hlfir_en    = pstCfg->hlfir_en;
        hchmid_en   = pstCfg->hchmid_en;
        hlmid_en    = pstCfg->hlmid_en;
        hchmsc_en   = pstCfg->hchmsc_en;
        hlmsc_en    = pstCfg->hlmsc_en;

        vchfir_en   = pstCfg->vchfir_en;
        vlfir_en    = pstCfg->vlfir_en;
        vchmid_en   = pstCfg->vchmid_en;
        vlmid_en    = pstCfg->vlmid_en;
        vchmsc_en   = pstCfg->vchmsc_en;
        vlmsc_en    = pstCfg->vlmsc_en;

        hor_coffset   = pstCfg->hor_coffset;
        vchroma_offset = pstCfg->vchroma_offset;
        vluma_offset  = pstCfg->vluma_offset;

        VPSS_Zme_Set_VPSS_VHD0_ZMEORESO(pstVpssRegs, pstCfg->oh, pstCfg->ow);
        VPSS_Zme_Set_VPSS_VHD0_ZME_LHADDR(pstVpssRegs, scl_lh);
        VPSS_Zme_Set_VPSS_VHD0_ZME_LVADDR(pstVpssRegs, scl_lv);
        VPSS_Zme_Set_VPSS_VHD0_ZME_CHADDR(pstVpssRegs, scl_ch);
        VPSS_Zme_Set_VPSS_VHD0_ZME_CVADDR(pstVpssRegs, scl_cv);
        VPSS_Zme_Set_VPSS_VHD0_HSP(pstVpssRegs, hlmsc_en, hchmsc_en, hlmid_en, hchmid_en, hlfir_en, hchfir_en, 0, hratio);
        VPSS_Zme_Set_VPSS_VHD0_HLOFFSET(pstVpssRegs, 0);
        VPSS_Zme_Set_VPSS_VHD0_HCOFFSET(pstVpssRegs, hor_coffset);
        VPSS_Zme_Set_VPSS_VHD0_VSP(pstVpssRegs, vlmsc_en, vchmsc_en, vlmid_en, vchmid_en, vlfir_en, vchfir_en, out_fmt);
        VPSS_Zme_Set_VPSS_VHD0_VSR(pstVpssRegs, vratio);
        VPSS_Zme_Set_VPSS_VHD0_VOFFSET(pstVpssRegs, vluma_offset, vchroma_offset);
        VPSS_zmecoef_to_dut(pstCfg);
    }
}
#endif
