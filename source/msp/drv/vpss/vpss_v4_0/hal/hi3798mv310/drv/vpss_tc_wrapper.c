#include "vpss_tc_wrapper.h"
#include "vpss_drv_comm.h"
#include <linux/math64.h>

extern MMZ_BUFFER_S gstMmzZmeCoefBuf[XDP_MAX_NODE_NUM][XDP_MAX_ZME_COEF_NUM];
extern HI_BOOL      bPreFrmDeiEn[XDP_MAX_NODE_NUM];

int a0[17][6] =
{
    { -4, 8, 55, 8, -4, 1},
    { -3, 6, 55, 9, -4, 1},
    { -3, 5, 54, 11, -4, 1},
    { -3, 4, 54, 13, -5, 1},
    { -2, 3, 53, 14, -5, 1},
    { -2, 2, 53, 16, -6, 1},
    { -1, -1, 52, 18, -6, 2},
    { -1, -2, 51, 20, -6, 2},
    { -1, -3, 50, 22, -6, 2},
    { 0, -3, 48, 24, -7, 2},
    { 0, -4, 47, 26, -7, 2},
    { 0, -5, 46, 28, -7, 2},
    { 0, -5, 45, 30, -7, 1},
    { 1, -6, 43, 32, -7, 1},
    { 1, -6, 41, 34, -7, 1},
    { 1, -7, 40, 36, -7, 1},
    { 1, -7, 38, 38, -7, 1},
};
int b0[17][4] =
{
    { 12, 43, 13, -4},
    { 11, 43, 14, -4},
    { 10, 43, 15, -4},
    { 9, 42, 17, -4},
    { 8, 42, 18, -4},
    { 7, 42, 19, -4},
    { 6, 41, 21, -4},
    { 5, 41, 22, -4},
    { 4, 41, 23, -4},
    { 4, 39, 25, -4},
    { 3, 39, 26, -4},
    { 2, 38, 27, -3},
    { 1, 38, 28, -3},
    { 0, 37, 30, -3},
    { 0, 35, 31, -2},
    { -1, 35, 32, -2},
    { -1, 33, 33, -1},
};
int a1[17][4] =
{
    { 12, 43, 13, -4},
    { 11, 43, 14, -4},
    { 10, 43, 15, -4},
    { 9, 42, 17, -4},
    { 8, 42, 18, -4},
    { 7, 42, 19, -4},
    { 6, 41, 21, -4},
    { 5, 41, 22, -4},
    { 4, 41, 23, -4},
    { 4, 39, 25, -4},
    { 3, 39, 26, -4},
    { 2, 38, 27, -3},
    { 1, 38, 28, -3},
    { 0, 37, 30, -3},
    { 0, 35, 31, -2},
    { -1, 35, 32, -2},
    { -1, 33, 33, -1},
};
int b1[17][4] =
{
    { 12, 43, 13, -4},
    { 11, 43, 14, -4},
    { 10, 43, 15, -4},
    { 9, 42, 17, -4},
    { 8, 42, 18, -4},
    { 7, 42, 19, -4},
    { 6, 41, 21, -4},
    { 5, 41, 22, -4},
    { 4, 41, 23, -4},
    { 4, 39, 25, -4},
    { 3, 39, 26, -4},
    { 2, 38, 27, -3},
    { 1, 38, 28, -3},
    { 0, 37, 30, -3},
    { 0, 35, 31, -2},
    { -1, 35, 32, -2},
    { -1, 33, 33, -1},
};


#if 1
HI_VOID VPSS_DRV_SetZmeCfg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_ZME_CFG *zme_cfg)
{
    HI_U32 in_width   = zme_cfg->in_width;
    HI_U32 in_height  = zme_cfg->in_height;
    HI_U32 in_yc422   = zme_cfg->in_yc422;
    HI_U32 out_width  = zme_cfg->out_width;
    HI_U32 out_height = zme_cfg->out_height;
    HI_U32 out_yc422  = zme_cfg->out_yc422;
    HI_U32 i          = zme_cfg->i;
    HI_U32 zme_en     = zme_cfg->en;
    HI_U32 para       = zme_cfg->para;

    ///////////// ZME /////////////
    HI_U32 zme_iw  = in_width ;
    HI_U32 zme_ih  = in_height;
    HI_U32 zme_if  = in_yc422;
    HI_U32 zme_ow  = out_width ;
    HI_U32 zme_oh  = out_height;
    HI_U32 zme_of  = out_yc422;

    HI_U32 zme_in_fmt = (zme_if == 0) ? 1 : 0; //YC420
    HI_U32 zme_out_fmt = (zme_of == 0) ? 1 : 0; //YC420

    HI_U32 hlmsc_en     = 1;
    HI_U32 hchmsc_en    = 1;
    HI_U32 vlmsc_en     = 1;
    HI_U32 vchmsc_en    = 1;
    HI_U32 zme_vhd0_en = zme_en;

    HI_U32 hlfir_en  = 1;
    HI_U32 hchfir_en = 1;
    HI_U32 hlmid_en  = 1;
    HI_U32 hchmid_en = 1;

    HI_U32 vlfir_en  = 0;
    HI_U32 vchfir_en = 0;
    HI_U32 vlmid_en  = 0;
    HI_U32 vchmid_en = 0;

    HI_S32 hor_loffset = 0.0 * VPSS_HOR_OFFSET_PRECISION;
    HI_S32 hor_coffset = 0.0 * VPSS_HOR_OFFSET_PRECISION;
    HI_S32 vluma_offset = 0.0 * VPSS_VER_OFFSET_PRECISION;
    HI_S32 vchroma_offset = 0.0 * VPSS_VER_OFFSET_PRECISION;

    //HI_U32 hratio = (zme_iw*VPSS_HOR_ZME_PRECISION)/zme_ow;
    HI_U32 hratio = (HI_U32)div_u64((HI_U64)(zme_iw * VPSS_HOR_ZME_PRECISION), zme_ow);
    HI_U32 vratio = (zme_ih) * VPSS_VER_ZME_PRECISION / zme_oh;

    HI_U32 hfir_order = 0; //0:H-V 1:V-H

    HI_U32  vhd0_zme_oh = zme_oh;
    HI_U32  vhd0_zme_ow = zme_ow;

    if (zme_en == 1)
    {
        if (para == PARA_SET)
        {
            zme_ow  = zme_cfg->out_width ;
            zme_oh  = zme_cfg->out_height;
            zme_of  = zme_cfg->out_yc422;
        }
        else
        {
            XDP_ASSERT(0);
        }
    }

    VPSS_Sys_SetZmeOutFmt(pstVpssRegs, 0 , zme_out_fmt);

    VPSS_Sys_SetZmeVhd0En(pstVpssRegs, 0 , zme_vhd0_en);

    if (zme_in_fmt != zme_out_fmt || zme_oh != zme_ih)
    {
        vlmsc_en  = 1;
        vchmsc_en = 1;
        VPSS_Sys_SetVlmscEn(pstVpssRegs, 0 ,  vlmsc_en);
        VPSS_Sys_SetVchmscEn(pstVpssRegs, 0 ,  vchmsc_en);
    }
    else
    {
        vlmsc_en  = 1;//rand()%2;
        vchmsc_en = vlmsc_en;
        VPSS_Sys_SetVlmscEn(pstVpssRegs, 0 ,  vlmsc_en);
        VPSS_Sys_SetVchmscEn(pstVpssRegs, 0 ,  vchmsc_en);
    }

    if (zme_ow != zme_iw)
    {
        hlmsc_en  = 1;
        hchmsc_en = 1;
        VPSS_Sys_SetHlmscEn(pstVpssRegs, 0 ,  hlmsc_en);
        VPSS_Sys_SetHchmscEn(pstVpssRegs, 0 ,  hchmsc_en);
    }
    else
    {
        hlmsc_en  = 1;//rand()%2;
        hchmsc_en = hlmsc_en;
        VPSS_Sys_SetHlmscEn(pstVpssRegs, 0 ,  hlmsc_en);
        VPSS_Sys_SetHchmscEn(pstVpssRegs, 0 ,  hchmsc_en);
    }

    VPSS_Sys_SetHlmidEn(pstVpssRegs, 0 ,  hlmid_en);
    VPSS_Sys_SetHchmidEn(pstVpssRegs, 0 ,  hchmid_en);
    VPSS_Sys_SetHlfirEn(pstVpssRegs, 0 ,  hlfir_en);
    VPSS_Sys_SetHchfirEn(pstVpssRegs, 0 ,  hchfir_en);

    VPSS_Sys_SetVlmidEn(pstVpssRegs, 0,  vlmid_en);
    VPSS_Sys_SetVchmidEn(pstVpssRegs, 0,  vchmid_en);
    VPSS_Sys_SetVlfirEn(pstVpssRegs, 0,  vlfir_en);
    VPSS_Sys_SetVchfirEn(pstVpssRegs, 0,  vchfir_en);

    //hor_loffset = (rand()%(128*VPSS_HOR_OFFSET_PRECISION+1))-VPSS_HOR_OFFSET_PRECISION;
    VPSS_Sys_SetHorLoffset(pstVpssRegs, 0 , hor_loffset);
    ///////debug start///
    hor_coffset = 0.0 * VPSS_HOR_OFFSET_PRECISION;
    ///////debug end////
    VPSS_Sys_SetHorCoffset(pstVpssRegs, 0,  hor_coffset);
    vluma_offset = (rand() % (1 * VPSS_VER_OFFSET_PRECISION + 1)) - VPSS_VER_OFFSET_PRECISION; //[-1,0]
    vchroma_offset = (rand() % (2 * VPSS_VER_OFFSET_PRECISION + 1)) - 2 * VPSS_VER_OFFSET_PRECISION; //[-2,0]
    ///////debug start///
    vluma_offset   = 0.0 * VPSS_VER_OFFSET_PRECISION;
    vchroma_offset = 0.0 * VPSS_VER_OFFSET_PRECISION;
    ///////debug end////
    VPSS_Sys_SetVlumaOffset(pstVpssRegs, 0 ,  vluma_offset);
    VPSS_Sys_SetVchromaOffset(pstVpssRegs, 0 ,  vchroma_offset);

    VPSS_Sys_SetHratio(pstVpssRegs, 0 , hratio);
    VPSS_Sys_SetVratio(pstVpssRegs, 0 , vratio);

    //if(vhd0_zme_iw>3840)
    {
        hfir_order = 0; //0:H-V 1:V-H
    }
    VPSS_Sys_SetHfirOrder(pstVpssRegs, 0 , hfir_order);

    if (zme_cfg->pro == 0)
    {
        zme_ih = zme_ih / 2;
        zme_oh = zme_oh / 2;
    }

    VPSS_Sys_SetVhd0ZmeOh(pstVpssRegs, 0, vhd0_zme_oh - 1);
    VPSS_Sys_SetVhd0ZmeOw(pstVpssRegs, 0, vhd0_zme_ow - 1);


    VPSS_Sys_SetVhd0SclLh(pstVpssRegs, 0, gstMmzZmeCoefBuf[i][0].u32StartPhyAddr);
    VPSS_Sys_SetVhd0SclLv(pstVpssRegs, 0, gstMmzZmeCoefBuf[i][1].u32StartPhyAddr);
    VPSS_Sys_SetVhd0SclCh(pstVpssRegs, 0, gstMmzZmeCoefBuf[i][2].u32StartPhyAddr);
    VPSS_Sys_SetVhd0SclCv(pstVpssRegs, 0, gstMmzZmeCoefBuf[i][3].u32StartPhyAddr);
    //VPSS_Sys_SetZmeCfgAddr(pstVpssRegs, 0,    zme_cfg_addr);

    vpss_scl6Tapcoef_to_dut(gstMmzZmeCoefBuf[i][0].u32StartVirAddr, a0);//lh
    vpss_scl4Tapcoef_to_dut(gstMmzZmeCoefBuf[i][2].u32StartVirAddr, b0);//ch
    vpss_scl4Tapcoef_to_dut(gstMmzZmeCoefBuf[i][1].u32StartVirAddr, a1);//lv
    vpss_scl4Tapcoef_to_dut(gstMmzZmeCoefBuf[i][3].u32StartVirAddr, b1);//cv
}
#endif

//======== write coef/threath in DDR ===========
HI_VOID vpss_scl8Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][8])           //for 17*8
{
#ifdef VPSS_EDA
    Cell cell;
    Cell *pCell;
    cell.pa_va_flag = VPSS_LIST_ADDR_PA_VA;
#endif

    HI_U32  temp[8] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  i, j, k = 0;

    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 8; j++)
        {
            temp[j % 8] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);
            if (j % 8 == 2)
            {
                u32OutData = (temp[2] << 20) + (temp[1] << 10) + temp[0];
#ifdef VPSS_EDA
                cell.addr = coef_start_addr + k * 4;
                cell.data = u32OutData;
                HiMemWordWr(&cell);
#else
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
#endif
                k++;
            }
            else if (j % 8 == 5)
            {
                u32OutData = (temp[5] << 20) + (temp[4] << 10) + temp[3];
#ifdef VPSS_EDA
                cell.addr = coef_start_addr + k * 4;
                cell.data = u32OutData;
                HiMemWordWr(&cell);
#else
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
#endif
                k++;
            }
            else if (j % 8 == 7)
            {
                u32OutData = (temp[7] << 10) + temp[6];
#ifdef VPSS_EDA
                cell.addr = coef_start_addr + k * 4;
                cell.data = u32OutData;
                HiMemWordWr(&cell);
#else
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
#endif
                k++;
            }
        }
    }
#ifdef VPSS_EDA
#ifdef NO_DUT_SIM
#if (EDA_TO_FPGA)
    {
        char buffer[50];
        char str[800] = "";
        if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_HL_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_lh_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_HC_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_ch_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_VL_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_lv_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_VC_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_cv_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }

        else
        {
            return;
        }
        strcat(str, vpss_emu_attr.emu_tc_dir);
        strcat(str, buffer);
        vpss_emu_attr.fp_y = fopen(str, "wb");
        HI_ASSERT(vpss_emu_attr.fp_y != NULL);
        for (int ii = 0; ii < 51 * 4; ii = ii + 4)
        {
            HI_U32 rdata = 0;
            {
                cell.addr = coef_start_addr - coef_start_addr % 4 + ii ;
                cout << hex << "cell.addr=" << cell.addr << endl;
                pCell = HiMemWordRd(&cell);
                if (pCell == 0)
                {
                    cout << hex << "[VPSS HAL]Error! cell.addr=0x" << cell.addr << dec << ", line " << __LINE__ << endl;
                }
                rdata = pCell->data;
                cout << hex << "rdata=" << rdata << endl;
                if (fwrite(&rdata, sizeof(HI_U32), 1, vpss_emu_attr.fp_y) != 1)
                {
                    cout << "file write error\n" << endl  ;
                }
            }
        }
        fclose(vpss_emu_attr.fp_y);
    }
#endif
#endif
#endif
}

HI_VOID vpss_scl6Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][6])           //for 17*6
{

    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  i, j, k = 0;

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

HI_VOID vpss_scl4Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][4])           //for 17*4
{
#ifdef VPSS_EDA
    Cell cell;
    Cell *pCell;
    cell.pa_va_flag = VPSS_LIST_ADDR_PA_VA;
#endif

    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  i, j, k = 0;

    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 4; j++)
        {
            temp[j % 2] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);
            if (j % 2 == 1)
            {
                u32OutData = (temp[1] << 16) + temp[0];
#ifdef VPSS_EDA
                cell.addr = coef_start_addr + k * 4;
                cell.data = u32OutData;
                HiMemWordWr(&cell);
#else
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
#endif
                k++;
            }
        }
    }
#ifdef VPSS_EDA
#ifdef NO_DUT_SIM
#if (EDA_TO_FPGA)
    {
        char buffer[50];
        char str[800] = "";
        if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_HL_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_lh_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_HC_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_ch_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_VL_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_lv_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else if (coef_start_addr == node_no * VPSS_SCALER_COEF_INTERVAL + VPSS_VHD0_VC_COEF_ADDR)
        {
            sprintf(buffer, "/vhd0_zme_cv_%d_%d.bin", vpss_emu_attr.tc_list_num, node_no);
        }
        else
        {
            return;
        }
        strcat(str, vpss_emu_attr.emu_tc_dir);
        strcat(str, buffer);
        vpss_emu_attr.fp_y = fopen(str, "wb");
        HI_ASSERT(vpss_emu_attr.fp_y != NULL);
        for (int ii = 0; ii < 34 * 4; ii = ii + 4)
        {
            HI_U32 rdata = 0;
            cell.addr = coef_start_addr - coef_start_addr % 4 + ii ;
            //cout << hex << "cell.addr=" << cell.addr << endl;
            pCell = HiMemWordRd(&cell);
            if (pCell == 0)
            {
                cout << hex << "[VPSS HAL]Error! cell.addr=0x" << cell.addr << dec << ", line " << __LINE__ << endl;
            }
            rdata = pCell->data;
            if (fwrite(&rdata, sizeof(HI_U32), 1, vpss_emu_attr.fp_y) != 1)
            {
                cout << "file write error\n" << endl  ;
            }
        }
        fclose(vpss_emu_attr.fp_y);

    }
#endif
#endif
#endif
}

HI_VOID vpss_scl2Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][2])           //for 17*2
{
#ifdef VPSS_EDA
    Cell cell;
    cell.pa_va_flag = VPSS_LIST_ADDR_PA_VA;
#endif

    HI_U32  temp[2] = {0};
    HI_U32  u32OutData = 0;
    HI_U32  i, j, k = 0;

    for (i = 0; i < 17; i++)
    {
        for (j = 0; j < 2; j++)
        {
            temp[j % 2] = VPSS_DRV_Conver_ScaleCoef(arr[i][j]);
            if (j % 2 == 1)
            {
                u32OutData = (temp[1] << 16) + temp[0];
#ifdef VPSS_EDA
                cell.addr = coef_start_addr + k * 4;
                cell.data = u32OutData;
                HiMemWordWr(&cell);
#else
                *(HI_U32 *)(coef_start_addr + k * 4) = u32OutData;
#endif
                k++;
            }
        }
    }
}
HI_U32 VPSS_DRV_Conver_ScaleCoef(HI_S32 s32Value)
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

/////////////////ZME HAL END////////////////]

HI_VOID VPSS_NRRFR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_NRRFR_CFG_S *pstNrRfrCfg, CBB_FRAME_S *pstNrRfr)
{
    HI_S32 s32ReturnVal = 0;
    HI_VOID *pArg       = HI_NULL;

    HI_U32 u32Wth      = pstNrRfrCfg->width;
    HI_U32 u32Hgt      = pstNrRfrCfg->height;
    HI_U32 u32Pro      = pstNrRfrCfg->pro;
    HI_U32 u32bitwth   = pstNrRfrCfg->bitwth;

    HI_U32 u32WthReal  = u32Wth;
    HI_U32 u32HgtReal  = u32Pro == 0 ? u32Hgt >> 1 : u32Hgt;

    pstNrRfr->bEn = pstNrRfrCfg->nrrfr_en;
    pstNrRfr->enBitWidth = u32bitwth;
    pstNrRfr->u32Width   = u32WthReal;
    pstNrRfr->u32Height  = u32HgtReal;
    pstNrRfr->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
    pstNrRfr->stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
    pstNrRfr->stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

    s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *) pstNrRfr, pArg);
    XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

    return ;
}

HI_VOID VPSS_TNR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_TNR_CFG_S *pstTnrCfg, VPSS_TNR_CHN_CFG_S *pstTnrChnCfg)
{
    HI_S32 s32ReturnVal = 0;
    HI_VOID *pArg       = HI_NULL;

    HI_U32 u32Wth    = pstTnrCfg->width;
    HI_U32 u32Hgt    = pstTnrCfg->height;
    HI_U32 u32Pro    = pstTnrCfg->pro;
    HI_U8  u8mamd    = pstTnrCfg->madmode;
    HI_U32 u32bitwth = pstTnrCfg->bitwth;

    //HI_U32 u32Fmt = psTnrCfg->format;
    //HI_U8  u8meds = psTnrCfg->meds_en;

    HI_U32 u32WthMad   = u8mamd == 2 ? ((u32Wth + 7) / 8) * 2 : u32Wth;
    HI_U32 u32HgtMad   = u32Pro == 0 ? u32Hgt >> 1 : u32Hgt;

    HI_U32 u32WthReal  = u32Wth;
    HI_U32 u32HgtReal  = u32Pro == 0 ? u32Hgt >> 1 : u32Hgt;

    HI_U32 u32RgmvNumH = (u32WthReal + 33) / 64 ; //block size 64*8, if bigger than half of block w/h, need upper
    HI_U32 u32RgmvNumV = (u32HgtReal +  5) / 8  ; //

    HI_BOOL bMcnrEn    = pstTnrCfg->mcnr_en;

    if (HI_TRUE == bMcnrEn)
    {
        XDP_ASSERT(HI_TRUE == VPSS_HAL_GetbRgmeEn((S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr));
    }

    if (pstTnrCfg->tnr_en)
    {
        //nr rfr
        pstTnrChnCfg->stNrRfr.bEn = HI_TRUE;
        pstTnrChnCfg->stNrRfr.enBitWidth = u32bitwth;
        pstTnrChnCfg->stNrRfr.u32Width   = u32WthReal;
        pstTnrChnCfg->stNrRfr.u32Height  = u32HgtReal;
        pstTnrChnCfg->stNrRfr.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstTnrChnCfg->stNrRfr.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstTnrChnCfg->stNrRfr.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

        s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_RFR, (HI_VOID *) &pstTnrChnCfg->stNrRfr, pArg);
        XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

        //nr p2
        pstTnrChnCfg->stNrP2.bEn = HI_TRUE;
        pstTnrChnCfg->stNrP2.enBitWidth = u32bitwth;
        pstTnrChnCfg->stNrP2.u32Width   = u32WthReal;
        pstTnrChnCfg->stNrP2.u32Height  = u32HgtReal;
        pstTnrChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstTnrChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstTnrChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

        s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *) &pstTnrChnCfg->stNrP2, pArg);
        XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

        //nr mad
        pstTnrChnCfg->stInfoTnrMad.bEn       = HI_TRUE;
        pstTnrChnCfg->stInfoTnrMad.bSmmu_R   = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
        pstTnrChnCfg->stInfoTnrMad.bSmmu_W   = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
        pstTnrChnCfg->stInfoTnrMad.u32Wth    = u32WthMad;
        pstTnrChnCfg->stInfoTnrMad.u32Hgt    = u32HgtMad;
        pstTnrChnCfg->stInfoTnrMad.u32Stride = ((u32WthMad * 5 + 7) / 8 + 15) / 16 * 16; //ALIGN_ANYBW_16BTYE(u32WthMad,5);

        VPSS_InfoCfg_Tnr_Mad(&pstTnrChnCfg->stInfoTnrMad, stRegAddr);

        //nr rgmv
        //rgmv&mcnr enable judge
        if (HI_TRUE == VPSS_HAL_GetbRgmeEn((S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr) && \
            HI_TRUE == VPSS_HAL_GetbMcnrEn((S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr))
        {
            pstTnrChnCfg->stInfoRgmv.bEn       = HI_TRUE;
            pstTnrChnCfg->stInfoRgmv.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstTnrChnCfg->stInfoRgmv.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstTnrChnCfg->stInfoRgmv.bSmmu_Nx1 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstTnrChnCfg->stInfoRgmv.u32Wth    = u32RgmvNumH;
            pstTnrChnCfg->stInfoRgmv.u32Hgt    = u32RgmvNumV;
            pstTnrChnCfg->stInfoRgmv.u32Stride = ((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Rgmv(&pstTnrChnCfg->stInfoRgmv, stRegAddr);
        }
    }

    return ;
}

HI_VOID VPSS_FUNC_SetTnrMode(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_TNR_MODE_E TnrMode, VPSS_TNR_CFG_S *pstCfg)
{
    //var declare
    HI_U32 width        =  pstCfg->width;
    HI_U32 marketcoor      =  0;
    HI_U32 marketmode      =  0;
    HI_U32 marketmodeen    =  0;
    HI_U32 mcnr_en         =  pstCfg->mcnr_en;
    HI_U32 img_type        = (pstCfg->format == 0) ? 1 : 0;

    //HI_U32 height       =  pstCfg->height;//noused
    //HI_U32 in_fmt          =  pstCfg->in_fmt;
    //HI_U32 mcnr_rgme_mode  =  pstCfg->mcnr_rgme_mode;
    //HI_U32 rgme_en         =  pstCfg->rgme_en;
    //HI_U32 mcnr_meds_en    =  pstCfg->meds_en;

    HI_U32 nren    =   1;//pstCfg->nr_en;
    HI_U32 cnren    =  0;
    HI_U32 ynren    =  0;
    HI_U32 alpha2    =  0;
    HI_U32 alpha1    =  0;
    HI_U32 cmotionlpfmode    =  0;
    HI_U32 ymotionlpfmode    =  0;
    HI_U32 cmotioncalcmode    =  0;
    HI_U32 ymotioncalcmode    =  0;
    HI_U32 meancadjshift    =  0;
    HI_U32 meanyadjshift    =  0;
    HI_U32 mean_cmotion_adj_en    =  0;
    HI_U32 mean_ymotion_adj_en    =  0;
    HI_U32 mdprelpfen    =  0;
    HI_U32 cmdcore    =  0;
    HI_U32 cmdgain    =  0;
    HI_U32 ymdcore    =  0;
    HI_U32 ymdgain    =  0;
    HI_U32 randomctrlmode    =  0;
    HI_U32 blkdiffthd    =  0;
    HI_U32 noisedetecten    =  0;
    HI_U32 flatthdmax    =  0;
    HI_U32 flatthdmed    =  0;
    HI_U32 flatthdmin    =  0;
    HI_U32 smvythd    =  0;
    HI_U32 smvxthd    =  0;
    HI_U32 discardsmvyen    =  0;
    HI_U32 discardsmvxen    =  0;
    HI_U32 gm_adj    =  0;
    HI_U32 mvlpfmode    =  0;
    HI_U32 mvrefmode    =  0;
    HI_U32 motionestimateen    =  0;
    HI_U32 mag_pnl_core_xmv    =  0;
    HI_U32 mag_pnl_gain_xmv    =  0;
    HI_U32 mag_pnl_core_0mv    =  0;
    HI_U32 mag_pnl_gain_0mv    =  0;
    HI_U32 std_pnl_core_xmv    =  0;
    HI_U32 std_pnl_gain_xmv    =  0;
    HI_U32 std_pnl_core_0mv    =  0;
    HI_U32 std_pnl_gain_0mv    =  0;
    HI_U32 std_core_xmv    =  0;
    HI_U32 std_core_0mv    =  0;
    HI_U32 std_pnl_core    =  0;
    HI_U32 std_pnl_gain    =  0;
    HI_U32 adj_xmv_max    =  0;
    HI_U32 adj_0mv_max    =  0;
    HI_U32 adj_xmv_min    =  0;
    HI_U32 adj_0mv_min    =  0;
    HI_U32 adj_mv_min    =  0;
    HI_U32 adj_mv_max    =  0;
    HI_U32 cbcrweight2    =  0;
    HI_U32 cbcrweight1    =  0;
    HI_U32 cbcrupdateen    =  0;
    HI_U32 crend1    =  0;
    HI_U32 cbend1    =  0;
    HI_U32 crbegin1    =  0;
    HI_U32 cbbegin1    =  0;
    HI_U32 crend2    =  0;
    HI_U32 cbend2    =  0;
    HI_U32 crbegin2    =  0;
    HI_U32 cbbegin2    =  0;
    HI_U32 motionmergeratio    =  0;
    HI_U32 premotionalpha    =  0;
    HI_U32 premotionmergemode    =  0;
    HI_U32 cmotioncore    =  0;
    HI_U32 cmotiongain    =  0;
    HI_U32 ymotioncore    =  0;
    HI_U32 ymotiongain    =  0;
    HI_U32 motionmappingen    =  0;
    HI_U32 saltuslevel    =  0;
    HI_U32 saltusdecten    =  0;
    HI_U32 cmclpfmode    =  0;
    HI_U32 ymclpfmode    =  0;
    HI_U32 cmcadjen    =  0;
    HI_U32 ymcadjen    =  0;
    HI_U32 cnonrrange    =  0;
    HI_U32 ynonrrange    =  0;
    HI_U32 cmotionmode    =  0;
    HI_U32 ymotionmode    =  0;
    HI_U32 scenechangeinfo    =  0;
    HI_U32 scenechangeen    =  0;
    HI_U32 cfg_cmdcore    =  0;
    HI_U32 cfg_cmdgain    =  0;
    HI_U32 cfg_ymdcore    =  0;
    HI_U32 cfg_ymdgain    =  0;
    HI_U32 flatinfoymax    =  0;
    HI_U32 flatinfoxmax    =  0;
    HI_U32 flatinfoymin    =  0;
    HI_U32 flatinfoxmin    =  0;
    HI_U32 yblendingymax    =  0;
    HI_U32 yblendingxmax    =  0;
    HI_U32 yblendingymin    =  0;
    HI_U32 yblendingxmin    =  0;
    HI_U32 cblendingymax    =  0;
    HI_U32 cblendingxmax    =  0;
    HI_U32 cblendingymin    =  0;
    HI_U32 cblendingxmin    =  0;
    HI_U32 dtblendingymax    =  0;
    HI_U32 dtblendingxmax    =  0;
    HI_U32 dtblendingymin    =  0;
    HI_U32 dtblendingxmin    =  0;

    HI_U32 mean_motion_ratio3    =  0;
    HI_U32 mean_motion_ratio2    =  0;
    HI_U32 mean_motion_ratio1    =  0;
    HI_U32 mean_motion_ratio0    =  0;
    HI_U32 mean_motion_ratio7    =  0;
    HI_U32 mean_motion_ratio6    =  0;
    HI_U32 mean_motion_ratio5    =  0;
    HI_U32 mean_motion_ratio4    =  0;
    HI_U32 mean_motion_ratio11    =  0;
    HI_U32 mean_motion_ratio10    =  0;
    HI_U32 mean_motion_ratio9    =  0;
    HI_U32 mean_motion_ratio8    =  0;
    HI_U32 mean_motion_ratio15    =  0;
    HI_U32 mean_motion_ratio14    =  0;
    HI_U32 mean_motion_ratio13    =  0;
    HI_U32 mean_motion_ratio12    =  0;
    HI_U32 yblendingalphalut3    =  0;
    HI_U32 yblendingalphalut2    =  0;
    HI_U32 yblendingalphalut1    =  0;
    HI_U32 yblendingalphalut0    =  0;
    HI_U32 yblendingalphalut7    =  0;
    HI_U32 yblendingalphalut6    =  0;
    HI_U32 yblendingalphalut5    =  0;
    HI_U32 yblendingalphalut4    =  0;
    HI_U32 yblendingalphalut11    =  0;
    HI_U32 yblendingalphalut10    =  0;
    HI_U32 yblendingalphalut9    =  0;
    HI_U32 yblendingalphalut8    =  0;
    HI_U32 yblendingalphalut15    =  0;
    HI_U32 yblendingalphalut14    =  0;
    HI_U32 yblendingalphalut13    =  0;
    HI_U32 yblendingalphalut12    =  0;
    HI_U32 yblendingalphalut19    =  0;
    HI_U32 yblendingalphalut18    =  0;
    HI_U32 yblendingalphalut17    =  0;
    HI_U32 yblendingalphalut16    =  0;
    HI_U32 yblendingalphalut23    =  0;
    HI_U32 yblendingalphalut22    =  0;
    HI_U32 yblendingalphalut21    =  0;
    HI_U32 yblendingalphalut20    =  0;
    HI_U32 yblendingalphalut27    =  0;
    HI_U32 yblendingalphalut26    =  0;
    HI_U32 yblendingalphalut25    =  0;
    HI_U32 yblendingalphalut24    =  0;
    HI_U32 yblendingalphalut31    =  0;
    HI_U32 yblendingalphalut30    =  0;
    HI_U32 yblendingalphalut29    =  0;
    HI_U32 yblendingalphalut28    =  0;
    HI_U32 cblendingalphalut3    =  0;
    HI_U32 cblendingalphalut2    =  0;
    HI_U32 cblendingalphalut1    =  0;
    HI_U32 cblendingalphalut0    =  0;
    HI_U32 cblendingalphalut7    =  0;
    HI_U32 cblendingalphalut6    =  0;
    HI_U32 cblendingalphalut5    =  0;
    HI_U32 cblendingalphalut4    =  0;
    HI_U32 cblendingalphalut11    =  0;
    HI_U32 cblendingalphalut10    =  0;
    HI_U32 cblendingalphalut9    =  0;
    HI_U32 cblendingalphalut8    =  0;
    HI_U32 cblendingalphalut15    =  0;
    HI_U32 cblendingalphalut14    =  0;
    HI_U32 cblendingalphalut13    =  0;
    HI_U32 cblendingalphalut12    =  0;
    HI_U32 cblendingalphalut19    =  0;
    HI_U32 cblendingalphalut18    =  0;
    HI_U32 cblendingalphalut17    =  0;
    HI_U32 cblendingalphalut16    =  0;
    HI_U32 cblendingalphalut23    =  0;
    HI_U32 cblendingalphalut22    =  0;
    HI_U32 cblendingalphalut21    =  0;
    HI_U32 cblendingalphalut20    =  0;
    HI_U32 cblendingalphalut27    =  0;
    HI_U32 cblendingalphalut26    =  0;
    HI_U32 cblendingalphalut25    =  0;
    HI_U32 cblendingalphalut24    =  0;
    HI_U32 cblendingalphalut31    =  0;
    HI_U32 cblendingalphalut30    =  0;
    HI_U32 cblendingalphalut29    =  0;
    HI_U32 cblendingalphalut28    =  0;
#if 0
    HI_U32 ymotionstrlut3    =  0;
    HI_U32 ymotionstrlut2    =  0;
    HI_U32 ymotionstrlut1    =  0;
    HI_U32 ymotionstrlut0    =  0;
    HI_U32 ymotionstrlut7    =  0;
    HI_U32 ymotionstrlut6    =  0;
    HI_U32 ymotionstrlut5    =  0;
    HI_U32 ymotionstrlut4    =  0;
    HI_U32 ymotionstrlut11    =  0;
    HI_U32 ymotionstrlut10    =  0;
    HI_U32 ymotionstrlut9    =  0;
    HI_U32 ymotionstrlut8    =  0;
    HI_U32 ymotionstrlut15    =  0;
    HI_U32 ymotionstrlut14    =  0;
    HI_U32 ymotionstrlut13    =  0;
    HI_U32 ymotionstrlut12    =  0;
    HI_U32 ymotionstrlut19    =  0;
    HI_U32 ymotionstrlut18    =  0;
    HI_U32 ymotionstrlut17    =  0;
    HI_U32 ymotionstrlut16    =  0;
    HI_U32 ymotionstrlut23    =  0;
    HI_U32 ymotionstrlut22    =  0;
    HI_U32 ymotionstrlut21    =  0;
    HI_U32 ymotionstrlut20    =  0;
    HI_U32 ymotionstrlut27    =  0;
    HI_U32 ymotionstrlut26    =  0;
    HI_U32 ymotionstrlut25    =  0;
    HI_U32 ymotionstrlut24    =  0;
    HI_U32 ymotionstrlut31    =  0;
    HI_U32 ymotionstrlut30    =  0;
    HI_U32 ymotionstrlut29    =  0;
    HI_U32 ymotionstrlut28    =  0;
    HI_U32 ymotionstrlut35    =  0;
    HI_U32 ymotionstrlut34    =  0;
    HI_U32 ymotionstrlut33    =  0;
    HI_U32 ymotionstrlut32    =  0;
    HI_U32 ymotionstrlut39    =  0;
    HI_U32 ymotionstrlut38    =  0;
    HI_U32 ymotionstrlut37    =  0;
    HI_U32 ymotionstrlut36    =  0;
    HI_U32 ymotionstrlut43    =  0;
    HI_U32 ymotionstrlut42    =  0;
    HI_U32 ymotionstrlut41    =  0;
    HI_U32 ymotionstrlut40    =  0;
    HI_U32 ymotionstrlut47    =  0;
    HI_U32 ymotionstrlut46    =  0;
    HI_U32 ymotionstrlut45    =  0;
    HI_U32 ymotionstrlut44    =  0;
    HI_U32 ymotionstrlut51    =  0;
    HI_U32 ymotionstrlut50    =  0;
    HI_U32 ymotionstrlut49    =  0;
    HI_U32 ymotionstrlut48    =  0;
    HI_U32 ymotionstrlut55    =  0;
    HI_U32 ymotionstrlut54    =  0;
    HI_U32 ymotionstrlut53    =  0;
    HI_U32 ymotionstrlut52    =  0;
    HI_U32 ymotionstrlut59    =  0;
    HI_U32 ymotionstrlut58    =  0;
    HI_U32 ymotionstrlut57    =  0;
    HI_U32 ymotionstrlut56    =  0;
    HI_U32 ymotionstrlut63    =  0;
    HI_U32 ymotionstrlut62    =  0;
    HI_U32 ymotionstrlut61    =  0;
    HI_U32 ymotionstrlut60    =  0;
    HI_U32 ymotionstrlut67    =  0;
    HI_U32 ymotionstrlut66    =  0;
    HI_U32 ymotionstrlut65    =  0;
    HI_U32 ymotionstrlut64    =  0;
    HI_U32 ymotionstrlut71    =  0;
    HI_U32 ymotionstrlut70    =  0;
    HI_U32 ymotionstrlut69    =  0;
    HI_U32 ymotionstrlut68    =  0;
    HI_U32 ymotionstrlut75    =  0;
    HI_U32 ymotionstrlut74    =  0;
    HI_U32 ymotionstrlut73    =  0;
    HI_U32 ymotionstrlut72    =  0;
    HI_U32 ymotionstrlut79    =  0;
    HI_U32 ymotionstrlut78    =  0;
    HI_U32 ymotionstrlut77    =  0;
    HI_U32 ymotionstrlut76    =  0;
    HI_U32 ymotionstrlut83    =  0;
    HI_U32 ymotionstrlut82    =  0;
    HI_U32 ymotionstrlut81    =  0;
    HI_U32 ymotionstrlut80    =  0;
    HI_U32 ymotionstrlut87    =  0;
    HI_U32 ymotionstrlut86    =  0;
    HI_U32 ymotionstrlut85    =  0;
    HI_U32 ymotionstrlut84    =  0;
    HI_U32 ymotionstrlut91    =  0;
    HI_U32 ymotionstrlut90    =  0;
    HI_U32 ymotionstrlut89    =  0;
    HI_U32 ymotionstrlut88    =  0;
    HI_U32 ymotionstrlut95    =  0;
    HI_U32 ymotionstrlut94    =  0;
    HI_U32 ymotionstrlut93    =  0;
    HI_U32 ymotionstrlut92    =  0;
    HI_U32 ymotionstrlut99    =  0;
    HI_U32 ymotionstrlut98    =  0;
    HI_U32 ymotionstrlut97    =  0;
    HI_U32 ymotionstrlut96    =  0;
    HI_U32 ymotionstrlut103    =  0;
    HI_U32 ymotionstrlut102    =  0;
    HI_U32 ymotionstrlut101    =  0;
    HI_U32 ymotionstrlut100    =  0;
    HI_U32 ymotionstrlut107    =  0;
    HI_U32 ymotionstrlut106    =  0;
    HI_U32 ymotionstrlut105    =  0;
    HI_U32 ymotionstrlut104    =  0;
    HI_U32 ymotionstrlut111    =  0;
    HI_U32 ymotionstrlut110    =  0;
    HI_U32 ymotionstrlut109    =  0;
    HI_U32 ymotionstrlut108    =  0;
    HI_U32 ymotionstrlut115    =  0;
    HI_U32 ymotionstrlut114    =  0;
    HI_U32 ymotionstrlut113    =  0;
    HI_U32 ymotionstrlut112    =  0;
    HI_U32 ymotionstrlut119    =  0;
    HI_U32 ymotionstrlut118    =  0;
    HI_U32 ymotionstrlut117    =  0;
    HI_U32 ymotionstrlut116    =  0;
    HI_U32 ymotionstrlut123    =  0;
    HI_U32 ymotionstrlut122    =  0;
    HI_U32 ymotionstrlut121    =  0;
    HI_U32 ymotionstrlut120    =  0;
    HI_U32 ymotionstrlut127    =  0;
    HI_U32 ymotionstrlut126    =  0;
    HI_U32 ymotionstrlut125    =  0;
    HI_U32 ymotionstrlut124    =  0;
    HI_U32 cmotionstrlut3    =  0;
    HI_U32 cmotionstrlut2    =  0;
    HI_U32 cmotionstrlut1    =  0;
    HI_U32 cmotionstrlut0    =  0;
    HI_U32 cmotionstrlut7    =  0;
    HI_U32 cmotionstrlut6    =  0;
    HI_U32 cmotionstrlut5    =  0;
    HI_U32 cmotionstrlut4    =  0;
    HI_U32 cmotionstrlut11    =  0;
    HI_U32 cmotionstrlut10    =  0;
    HI_U32 cmotionstrlut9    =  0;
    HI_U32 cmotionstrlut8    =  0;
    HI_U32 cmotionstrlut15    =  0;
    HI_U32 cmotionstrlut14    =  0;
    HI_U32 cmotionstrlut13    =  0;
    HI_U32 cmotionstrlut12    =  0;
    HI_U32 cmotionstrlut19    =  0;
    HI_U32 cmotionstrlut18    =  0;
    HI_U32 cmotionstrlut17    =  0;
    HI_U32 cmotionstrlut16    =  0;
    HI_U32 cmotionstrlut23    =  0;
    HI_U32 cmotionstrlut22    =  0;
    HI_U32 cmotionstrlut21    =  0;
    HI_U32 cmotionstrlut20    =  0;
    HI_U32 cmotionstrlut27    =  0;
    HI_U32 cmotionstrlut26    =  0;
    HI_U32 cmotionstrlut25    =  0;
    HI_U32 cmotionstrlut24    =  0;
    HI_U32 cmotionstrlut31    =  0;
    HI_U32 cmotionstrlut30    =  0;
    HI_U32 cmotionstrlut29    =  0;
    HI_U32 cmotionstrlut28    =  0;
    HI_U32 cmotionstrlut35    =  0;
    HI_U32 cmotionstrlut34    =  0;
    HI_U32 cmotionstrlut33    =  0;
    HI_U32 cmotionstrlut32    =  0;
    HI_U32 cmotionstrlut39    =  0;
    HI_U32 cmotionstrlut38    =  0;
    HI_U32 cmotionstrlut37    =  0;
    HI_U32 cmotionstrlut36    =  0;
    HI_U32 cmotionstrlut43    =  0;
    HI_U32 cmotionstrlut42    =  0;
    HI_U32 cmotionstrlut41    =  0;
    HI_U32 cmotionstrlut40    =  0;
    HI_U32 cmotionstrlut47    =  0;
    HI_U32 cmotionstrlut46    =  0;
    HI_U32 cmotionstrlut45    =  0;
    HI_U32 cmotionstrlut44    =  0;
    HI_U32 cmotionstrlut51    =  0;
    HI_U32 cmotionstrlut50    =  0;
    HI_U32 cmotionstrlut49    =  0;
    HI_U32 cmotionstrlut48    =  0;
    HI_U32 cmotionstrlut55    =  0;
    HI_U32 cmotionstrlut54    =  0;
    HI_U32 cmotionstrlut53    =  0;
    HI_U32 cmotionstrlut52    =  0;
    HI_U32 cmotionstrlut59    =  0;
    HI_U32 cmotionstrlut58    =  0;
    HI_U32 cmotionstrlut57    =  0;
    HI_U32 cmotionstrlut56    =  0;
    HI_U32 cmotionstrlut63    =  0;
    HI_U32 cmotionstrlut62    =  0;
    HI_U32 cmotionstrlut61    =  0;
    HI_U32 cmotionstrlut60    =  0;
    HI_U32 cmotionstrlut67    =  0;
    HI_U32 cmotionstrlut66    =  0;
    HI_U32 cmotionstrlut65    =  0;
    HI_U32 cmotionstrlut64    =  0;
    HI_U32 cmotionstrlut71    =  0;
    HI_U32 cmotionstrlut70    =  0;
    HI_U32 cmotionstrlut69    =  0;
    HI_U32 cmotionstrlut68    =  0;
    HI_U32 cmotionstrlut75    =  0;
    HI_U32 cmotionstrlut74    =  0;
    HI_U32 cmotionstrlut73    =  0;
    HI_U32 cmotionstrlut72    =  0;
    HI_U32 cmotionstrlut79    =  0;
    HI_U32 cmotionstrlut78    =  0;
    HI_U32 cmotionstrlut77    =  0;
    HI_U32 cmotionstrlut76    =  0;
    HI_U32 cmotionstrlut83    =  0;
    HI_U32 cmotionstrlut82    =  0;
    HI_U32 cmotionstrlut81    =  0;
    HI_U32 cmotionstrlut80    =  0;
    HI_U32 cmotionstrlut87    =  0;
    HI_U32 cmotionstrlut86    =  0;
    HI_U32 cmotionstrlut85    =  0;
    HI_U32 cmotionstrlut84    =  0;
    HI_U32 cmotionstrlut91    =  0;
    HI_U32 cmotionstrlut90    =  0;
    HI_U32 cmotionstrlut89    =  0;
    HI_U32 cmotionstrlut88    =  0;
    HI_U32 cmotionstrlut95    =  0;
    HI_U32 cmotionstrlut94    =  0;
    HI_U32 cmotionstrlut93    =  0;
    HI_U32 cmotionstrlut92    =  0;
    HI_U32 cmotionstrlut99    =  0;
    HI_U32 cmotionstrlut98    =  0;
    HI_U32 cmotionstrlut97    =  0;
    HI_U32 cmotionstrlut96    =  0;
    HI_U32 cmotionstrlut103    =  0;
    HI_U32 cmotionstrlut102    =  0;
    HI_U32 cmotionstrlut101    =  0;
    HI_U32 cmotionstrlut100    =  0;
    HI_U32 cmotionstrlut107    =  0;
    HI_U32 cmotionstrlut106    =  0;
    HI_U32 cmotionstrlut105    =  0;
    HI_U32 cmotionstrlut104    =  0;
    HI_U32 cmotionstrlut111    =  0;
    HI_U32 cmotionstrlut110    =  0;
    HI_U32 cmotionstrlut109    =  0;
    HI_U32 cmotionstrlut108    =  0;
    HI_U32 cmotionstrlut115    =  0;
    HI_U32 cmotionstrlut114    =  0;
    HI_U32 cmotionstrlut113    =  0;
    HI_U32 cmotionstrlut112    =  0;
    HI_U32 cmotionstrlut119    =  0;
    HI_U32 cmotionstrlut118    =  0;
    HI_U32 cmotionstrlut117    =  0;
    HI_U32 cmotionstrlut116    =  0;
    HI_U32 cmotionstrlut123    =  0;
    HI_U32 cmotionstrlut122    =  0;
    HI_U32 cmotionstrlut121    =  0;
    HI_U32 cmotionstrlut120    =  0;
    HI_U32 cmotionstrlut127    =  0;
    HI_U32 cmotionstrlut126    =  0;
    HI_U32 cmotionstrlut125    =  0;
    HI_U32 cmotionstrlut124    =  0;

    ///mc
    HI_U32 k_rgdifycore                  = 0;
    HI_U32 g_rgdifycore                  = 0;
    HI_U32 core_rgdify                   = 0;
    HI_U32 lmt_rgdify                    = 0;
    HI_U32 coef_sadlpf                   = 0;
    HI_U32 kmv_rgsad                     = 0;
    HI_U32 k_tpdif_rgsad                 = 0;
    HI_U32 g_tpdif_rgsad                 = 0;
    HI_U32 thmag_rgmv                    = 0;
    HI_U32 th_saddif_rgmv                = 0;
    HI_U32 th_0mvsad_rgmv                = 0;
    HI_U32 core_mag_rg                   = 0;
    HI_U32 lmt_mag_rg                    = 0;
    HI_U32 core_mv_rgmvls                = 0;
    HI_U32 k_mv_rgmvls                   = 0;
    HI_U32 core_mag_rgmvls               = 0;
    HI_U32 k_mag_rgmvls                  = 0;
    HI_U32 th_mvadj_rgmvls               = 0;
    HI_U32 en_mvadj_rgmvls               = 0;
    HI_U32 k_sad_rgls                    = 0;
    HI_U32 th_mag_rgls                   = 0;
    HI_U32 th_sad_rgls                   = 0;
    HI_U32 k_sadcore_rgmv                = 0;
    HI_U32 force_mven                    = 0;
    HI_U32 force_mvx                     = 0;
    HI_U32 th_blkmvx_mvdlt               = 0;
    HI_U32 th_rgmvx_mvdlt                = 0;
    HI_U32 th_ls_mvdlt                   = 0;
    HI_U32 th_vblkdist_mvdlt             = 0;
    HI_U32 th_hblkdist_mvdlt             = 0;
    HI_U32 k_sadcore_mvdlt               = 0;
    HI_U32 th_mag_mvdlt                  = 0;
    HI_U32 g_mag_mvdlt                   = 0;
    HI_U32 thl_sad_mvdlt                 = 0;
    HI_U32 thh_sad_mvdlt                 = 0;
    HI_U32 k_rglsw                       = 0;
    HI_U32 k_simimvw                     = 0;
    HI_U32 gh_core_simimv                = 0;
    HI_U32 gl_core_simimv                = 0;
    HI_U32 k_core_simimv                 = 0;
    HI_U32 k_core_vsaddif                = 0;
    HI_U32 k_rgsadadj_mcw                = 0;
    HI_U32 core_rgsadadj_mcw             = 0;
    HI_U32 k_mvy_mcw                     = 0;
    HI_U32 core_mvy_mcw                  = 0;
    HI_U32 rgtb_en_mcw                   = 0;
    HI_U32 core_rgmag_mcw                = 0;
    HI_U32 mode_rgysad_mcw               = 0;
    HI_U32 k_vsaddifw                    = 0;
    HI_U32 gh_core_vsad_dif              = 0;
    HI_U32 gl_core_vsaddif               = 0;
    HI_U32 g0_rgmag_mcw                  = 0;
    HI_U32 k0_rgmag_mcw                  = 0;
    HI_U32 x0_rgmag_mcw                  = 0;
    HI_U32 x0_rgsad_mcw                  = 0;
    HI_U32 core_rgsad_mcw                = 0;
    HI_U32 k1_rgmag_mcw                  = 0;
    HI_U32 k1_rgsad_mcw                  = 0;
    HI_U32 g0_rgsad_mcw                  = 0;
    HI_U32 k0_rgsad_mcw                  = 0;
    HI_U32 k_rgsad_mcw                   = 0;
    HI_U32 x_rgsad_mcw                   = 0;
    HI_U32 k0_smrg_mcw                   = 0;
    HI_U32 x0_smrg_mcw                   = 0;
    HI_U32 k1_tpmvdist_mcw               = 0;
    HI_U32 g0_tpmvdist_mcw               = 0;
    HI_U32 k0_tpmvdist_mcw               = 0;
    HI_U32 x0_tpmvdist_mcw               = 0;
    HI_U32 k_core_tpmvdist_mcw           = 0;
    HI_U32 b_core_tpmvdist_mcw           = 0;
    HI_U32 k_avgmvdist_mcw               = 0;
    HI_U32 k_minmvdist_mcw               = 0;
    HI_U32 k_tbdif_mcw                   = 0;
    HI_U32 k0_max_mag_mcw                = 0;
    HI_U32 k1_max_mag_mcw                = 0;
    HI_U32 k_max_dif_mcw                 = 0;
    HI_U32 k_max_core_mcw                = 0;
    HI_U32 k_difvcore_mcw                = 0;
    HI_U32 k_difhcore_mcw                = 0;
    HI_U32 k1_mag_wnd_mcw                = 0;
    HI_U32 g0_mag_wnd_mcw                = 0;
    HI_U32 k0_mag_wnd_mcw                = 0;
    HI_U32 x0_mag_wnd_mcw                = 0;
    HI_U32 k_tbmag_mcw                   = 0;
    HI_U32 g0_sad_wnd_mcw                = 0;
    HI_U32 k0_sad_wnd_mcw                = 0;
    HI_U32 x0_sad_wnd_mcw                = 0;
    HI_U32 g1_mag_wnd_mcw                = 0;
    HI_U32 g1_sad_wnd_mcw                = 0;
    HI_U32 k1_sad_wnd_mcw                = 0;
    HI_U32 b_hvdif_dw                    = 0;
    HI_U32 b_bhvdif_dw                   = 0;
    HI_U32 k_bhvdif_dw                   = 0;
    HI_U32 core_bhvdif_dw                = 0;
    HI_U32 gain_lpf_dw                   = 0;
    HI_U32 k_max_hvdif_dw                = 0;
    HI_U32 b_mv_dw                       = 0;
    HI_U32 core_mv_dw                    = 0;
    HI_U32 k_difv_dw                     = 0;
    HI_U32 core_hvdif_dw                 = 0;
    HI_U32 k1_hvdif_dw                   = 0;
    HI_U32 g0_hvdif_dw                   = 0;
    HI_U32 k0_hvdif_dw                   = 0;
    HI_U32 x0_hvdif_dw                   = 0;
    HI_U32 k1_mv_dw                      = 0;
    HI_U32 g0_mv_dw                      = 0;
    HI_U32 k0_mv_dw                      = 0;
    HI_U32 x0_mv_dw                      = 0;
    HI_U32 k1_mt_dw                      = 0;
    HI_U32 g0_mt_dw                      = 0;
    HI_U32 k0_mt_dw                      = 0;
    HI_U32 x0_mt_dw                      = 0;
    HI_U32 b_mt_dw                       = 0;
    HI_U32 k1_mv_mt                      = 0;
    HI_U32 x0_mv_mt                      = 0;
    HI_U32 g0_mv_mt                      = 0;
    HI_U32 mclpf_mode                    = 0;
    HI_U32 k_pxlmag_mcw                  = 0;
    HI_U32 x_pxlmag_mcw                  = 0;
    HI_U32 rs_pxlmag_mcw                 = 0;
    HI_U32 gain_mclpfh                   = 0;
    HI_U32 gain_dn_mclpfv                = 0;
    HI_U32 gain_up_mclpfv                = 0;
    HI_U32 g_pxlmag_mcw                  = 0;
    HI_U32 k_c_vertw                     = 0;
    HI_U32 k_y_vertw                     = 0;
    HI_U32 k_fstmt_mc                    = 0;
    HI_U32 x_fstmt_mc                    = 0;
    HI_U32 k1_mv_mc                      = 0;
    HI_U32 x0_mv_mc                      = 0;
    HI_U32 bdv_mcpos                     = 0;
    HI_U32 bdh_mcpos                     = 0;
    HI_U32 k_delta                       = 0;
    HI_U32 k_hfcore_mc                   = 0;
    HI_U32 x_hfcore_mc                   = 0;
    HI_U32 g_slmt_mc                     = 0;
    HI_U32 k_slmt_mc                     = 0;
    HI_U32 x_slmt_mc                     = 0;
    HI_U32 g_fstmt_mc                    = 0;
    HI_U32 r0_mc                         = 0;
    HI_U32 c0_mc                         = 0;
    HI_U32 g_hfcore_mc                   = 0;
    HI_U32 mcmvrange                     = 0;
    HI_U32 r1_mc                         = 0;
    HI_U32 c1_mc                         = 0;
    HI_U32 k_frcount_mc                  = 0;
    HI_U32 x_frcount_mc                  = 0;
    HI_U32 scenechange_mc                = 0;
    HI_U32 mcendc                        = 0;
    HI_U32 mcendr                        = 0;
    HI_U32 mcstartc                      = 0;
    HI_U32 mcstartr                      = 0;
    HI_U32 movegain                      = 0;
    HI_U32 movecorig                     = 0;
    HI_U32 movethdl                      = 0;
    HI_U32 movethdh                      = 0;
    HI_U32 mc_numt_blden                 = 0;
    HI_U32 numt_gain                     = 0;
    HI_U32 numt_coring                   = 0;
    HI_U32 numt_lpf_en                   = 0;
    HI_U32 k1_hw                         = 0;
    HI_U32 k0_hw                         = 0;
    HI_U32 core_hfvline                  = 0;
    HI_U32 k1_hfvline                    = 0;
    HI_U32 k0_hfvline                    = 0;
    HI_U32 core_rglsw                    = 0;
    HI_U32 g_difcore_mcw                 = 0;
    HI_U32 subpix_mc_en                  = 0;
    HI_U32 core1_hw                      = 0;
    HI_U32 k_core0_hw                    = 0;
    HI_U32 b_core0_hw                    = 0;
    HI_U32 g_hw                          = 0;
    HI_U32 g0_sadr_wnd_mcw               = 0;
    HI_U32 k0_sadr_wnd_mcw               = 0;
    HI_U32 x0_sadr_wnd_mcw               = 0;
    HI_U32 rp_k1_sad_wnd_mcw             = 0;
    HI_U32 rp_k1_mag_wnd_mcw             = 0;
    HI_U32 th_cur_blksad                 = 0;
    HI_U32 k_mcdifv_mcw                  = 0;
    HI_U32 k_p1cfdifh_mcw                = 0;
    HI_U32 g1_sadr_wnd_mcw               = 0;
    HI_U32 k1_sadr_wnd_mcw               = 0;
    HI_U32 th_cur_blkmotion              = 0;
    HI_U32 thl_neigh_blksad              = 0;
    HI_U32 thh_neigh_blksad              = 0;
    HI_U32 rp_difmvxth_rgmv              = 0;
    HI_U32 rp_mvxth_rgmv                 = 0;
    HI_U32 rpcounterth                   = 0;
    HI_U32 k_rpcounter                   = 0;
    HI_U32 blkmv_update_en               = 0;
    HI_U32 th_rgmv_mag                   = 0;
    HI_U32 rp_magth_rgmv                 = 0;
    HI_U32 rp_sadth_rgmv                 = 0;
    HI_U32 rp_difsadth_rgmv              = 0;
    HI_U32 submv_sadchk_en               = 0;
    HI_U32 rp_en                         = 0;//@@
    HI_U32 difvt_mode                    = 0;//@@
    HI_U32 k1_tpdif_rgsad                = 0;
    HI_U32 rp_difsadth_tb                = 0;
    HI_U32 rp_difmvxth_sp                = 0;
    HI_U32 mcw_blkm_thdh                 = 0;
    HI_U32 mcw_blkm_thdl                 = 0;
    HI_U32 mcw_blkm_coringmove           = 0;
    HI_U32 mcw_blkm_gainmove             = 0;
#endif



    int mean_motion_ratio[16] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
    int yblendingalphalut[32] = {8, 8, 8, 8, 8, 8, 14, 24, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31};
    int cblendingalphalut[32] = {8, 8, 8, 8, 8, 8, 14, 24, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31};
#if 0
    int ymotionstrlut[128] =
    {
        0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
        16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
        32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
        48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
        64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
        80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
        96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127
    };
    int cmotionstrlut[128] =
    {
        0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,
        16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
        32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
        48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
        64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
        80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
        96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
        112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127
    };
#endif
    if (TnrMode == VPSS_TNR_TYP)
    {
        printf("VPSS_FUNC_SetTnrMode enter into typ mode\n");
        //typ mode


        ynren              = 1;//uGetRandEx(0,  1);
        cnren              = 1;//uGetRandEx(0,  1);
        marketmodeen       = 0;
        marketmode         = 0;//uGetRandEx(0,  1);
        ymotionmode        = 1;//uGetRandEx(0,  1);
        cmotionmode        = 0;//uGetRandEx(0,  1);
        ynonrrange         = 0;//uGetRandEx(0, 31);
        cnonrrange         = 0;//uGetRandEx(0, 31);
        scenechangeen      = 1;//uGetRandEx(0,  1);
        scenechangeinfo    = 0;//uGetRandEx(0,255);

        marketcoor         = width / 2;

#if 0
        if (in_width < 256)
        {
            mcnr_meds_en  = 0;
        }
        else if (in_width > 960)
        {
            mcnr_meds_en  = 1;
        }
#endif
        mdprelpfen          =  1;//uGetRandEx(0,1);
        mean_ymotion_adj_en =  0;//uGetRandEx(0,1);
        mean_cmotion_adj_en =  0;//uGetRandEx(0,1);//0~1
        meanyadjshift       =  4;//uGetRandEx(0,6);//0~6
        meancadjshift       =  4;//uGetRandEx(0,6);//0~6
        ymotioncalcmode     =  0;//==0
        cmotioncalcmode     =  0;//==0
        ymotionlpfmode      =  3;//uGetRandEx(0,3);//0~3
        cmotionlpfmode      =  3;//uGetRandEx(0,3);//0~3
        alpha1              =  4;//uGetRandEx(0,4);//0~4
        alpha2              =  2;//uGetRandEx(0,4);//0~4
        ymdgain             = 15;//uGetRandEx(0,63);//0~63
        ymdcore             = -10; //uGetRandEx(-32,31);//-31~31
        cmdgain             = 15;//uGetRandEx(0,63);//0~63
        cmdcore             = -10; //uGetRandEx(-32,31);//-31~31

        noisedetecten      =  1;//uGetRandEx(0,  1);
        if (width > 720)
        {
            noisedetecten   =  0;//uGetRandEx(0,  1);
        }
        blkdiffthd         = 32;//uGetRandEx(0,255);
        randomctrlmode     =  2; //3;//uGetRandEx(0,  3);
        flatthdmin         = 12;//uGetRandEx(0,255);
        flatthdmed         = 20;//uGetRandEx(0,255);
        flatthdmax         = 35;//uGetRandEx(0,255);

        motionestimateen =   1;//uGetRandEx(0,  1);
        mvrefmode        =   0;//uGetRandEx(0,  2);//0~  2
        mvlpfmode        =   1;//uGetRandEx(0,  3);//0~  3
        gm_adj           =   2;//uGetRandEx(0,  4);//0~  4
        discardsmvxen    = uGetRand(0,  1);//0~  1
        discardsmvyen    = uGetRand(0,  1);//0~  1
        smvxthd          = uGetRand(0,  7);//0~  7
        smvythd          = uGetRand(0,  7);//0~  7d
        mag_pnl_gain_0mv = 125;//uGetRandEx(0,255);//0~255
        mag_pnl_core_0mv =  47;//uGetRandEx(0,255);//0~255
        mag_pnl_gain_xmv = 147;//uGetRandEx(0,255);//0~255
        mag_pnl_core_xmv =  63;//uGetRandEx(0,255);//0~255
        std_core_0mv     =  28;//uGetRandEx(0, 31);//0~ 31
        std_core_xmv     =  12;//uGetRandEx(0, 31);//0~ 31
        std_pnl_gain_0mv =  16;//uGetRandEx(0, 16);//0~ 16
        std_pnl_core_0mv =  10;//uGetRandEx(0, 16);//0~ 16
        std_pnl_gain_xmv =  16;//uGetRandEx(0, 16);//0~ 16
        std_pnl_core_xmv =  10;//uGetRandEx(0, 31);//0~ 31
        std_pnl_gain     =  31;//uGetRandEx(0, 31);//0~ 31
        std_pnl_core     =  10;//uGetRandEx(0, 31);//0~ 31
        adj_mv_max       =  16;//uGetRandEx(16,31);//   16~31
        adj_mv_min       =  16;//uGetRandEx(0, 16);//0~ 16
        adj_0mv_min      =   4;//uGetRandEx(0, 16);//0~ 16
        adj_xmv_min      =   4;//uGetRandEx(0, 16);//0~ 16
        adj_0mv_max      =  16;//uGetRandEx(0, 16);//0~ 16
        adj_xmv_max      =  16;//uGetRandEx(0, 16);//0~ 16
        if (width < 128)
        {
            motionestimateen = 0;
        }

        cbcrupdateen       =  0;//uGetRandEx(0, 1);
        cbcrweight1        =  0;//uGetRandEx(0,15);
        cbcrweight2        =  0;//uGetRandEx(0,15);
        cbbegin1           =  0;//uGetRandEx(0,63);
        crbegin1           =  0;//uGetRandEx(0,63);
        cbend1             =  0;//uGetRandEx(cbbegin1,63);
        crend1             =  0;//uGetRandEx(crbegin1,63);
        cbbegin2           =  0;//uGetRandEx(0,63);
        crbegin2           =  0;//uGetRandEx(0,63);
        cbend2             =  0;//uGetRandEx(cbbegin2,63);
        crend2             =  0;//uGetRandEx(crbegin2,63);

        ymcadjen           =  1; // 1;//uGetRandEx(0, 1);
        cmcadjen           =  1; // 1;//uGetRandEx(0, 1);

        motionmappingen    =  0;//uGetRandEx(0, 1);
        ymotiongain        = 15;//uGetRandEx(0,31);
        ymotioncore        =  5;//uGetRandEx(-32,31);
        cmotiongain        = 15;//uGetRandEx(0,31);
        cmotioncore        =  5;//uGetRandEx(-32,31);

        saltusdecten       =  1;//uGetRandEx(0, 1);
        saltuslevel        =  0;//uGetRandEx(0,31);

        premotionmergemode =  1;//uGetRandEx(0, 1);
        premotionalpha     = 26;//uGetRandEx(0,31);
        motionmergeratio   = 24;//uGetRandEx(0,31);

        //scenechangeen
        //scenechangeinfo

        ymclpfmode         =  3;//uGetRandEx(0, 3);
        cmclpfmode         =  3;//uGetRandEx(0, 3);

        //if(img_type ==1)
        //    cbcrupdateen       = 0;

        if (width < 128 || width > 720)
        {
            motionestimateen = 0;
        }

        if (motionestimateen == 0)
        {
            ymcadjen           = 0;
            cmcadjen           = 0;
        }

        if (img_type == 1)
        {
            ymotionmode = 1;
        }

        if (img_type == 1)
        {
            cbcrupdateen = 0;
        }

        mean_motion_ratio3  = mean_motion_ratio[3 ];
        mean_motion_ratio2  = mean_motion_ratio[2 ];
        mean_motion_ratio1  = mean_motion_ratio[1 ];
        mean_motion_ratio0  = mean_motion_ratio[0 ];
        mean_motion_ratio7  = mean_motion_ratio[7 ];
        mean_motion_ratio6  = mean_motion_ratio[6 ];
        mean_motion_ratio5  = mean_motion_ratio[5 ];
        mean_motion_ratio4  = mean_motion_ratio[4 ];
        mean_motion_ratio11 = mean_motion_ratio[11];
        mean_motion_ratio10 = mean_motion_ratio[10];
        mean_motion_ratio9  = mean_motion_ratio[9 ];
        mean_motion_ratio8  = mean_motion_ratio[8 ];
        mean_motion_ratio15 = mean_motion_ratio[15];
        mean_motion_ratio14 = mean_motion_ratio[14];
        mean_motion_ratio13 = mean_motion_ratio[13];
        mean_motion_ratio12 = mean_motion_ratio[12];
        yblendingalphalut3  = yblendingalphalut[3 ];
        yblendingalphalut2  = yblendingalphalut[2 ];
        yblendingalphalut1  = yblendingalphalut[1 ];
        yblendingalphalut0  = yblendingalphalut[0 ];
        yblendingalphalut7  = yblendingalphalut[7 ];
        yblendingalphalut6  = yblendingalphalut[6 ];
        yblendingalphalut5  = yblendingalphalut[5 ];
        yblendingalphalut4  = yblendingalphalut[4 ];
        yblendingalphalut11 = yblendingalphalut[11];
        yblendingalphalut10 = yblendingalphalut[10];
        yblendingalphalut9  = yblendingalphalut[9 ];
        yblendingalphalut8  = yblendingalphalut[8 ];
        yblendingalphalut15 = yblendingalphalut[15];
        yblendingalphalut14 = yblendingalphalut[14];
        yblendingalphalut13 = yblendingalphalut[13];
        yblendingalphalut12 = yblendingalphalut[12];
        yblendingalphalut19 = yblendingalphalut[19];
        yblendingalphalut18 = yblendingalphalut[18];
        yblendingalphalut17 = yblendingalphalut[17];
        yblendingalphalut16 = yblendingalphalut[16];
        yblendingalphalut23 = yblendingalphalut[23];
        yblendingalphalut22 = yblendingalphalut[22];
        yblendingalphalut21 = yblendingalphalut[21];
        yblendingalphalut20 = yblendingalphalut[20];
        yblendingalphalut27 = yblendingalphalut[27];
        yblendingalphalut26 = yblendingalphalut[26];
        yblendingalphalut25 = yblendingalphalut[25];
        yblendingalphalut24 = yblendingalphalut[24];
        yblendingalphalut31 = yblendingalphalut[31];
        yblendingalphalut30 = yblendingalphalut[30];
        yblendingalphalut29 = yblendingalphalut[29];
        yblendingalphalut28 = yblendingalphalut[28];
        cblendingalphalut3  = cblendingalphalut[3 ];
        cblendingalphalut2  = cblendingalphalut[2 ];
        cblendingalphalut1  = cblendingalphalut[1 ];
        cblendingalphalut0  = cblendingalphalut[0 ];
        cblendingalphalut7  = cblendingalphalut[7 ];
        cblendingalphalut6  = cblendingalphalut[6 ];
        cblendingalphalut5  = cblendingalphalut[5 ];
        cblendingalphalut4  = cblendingalphalut[4 ];
        cblendingalphalut11 = cblendingalphalut[11];
        cblendingalphalut10 = cblendingalphalut[10];
        cblendingalphalut9  = cblendingalphalut[9 ];
        cblendingalphalut8  = cblendingalphalut[8 ];
        cblendingalphalut15 = cblendingalphalut[15];
        cblendingalphalut14 = cblendingalphalut[14];
        cblendingalphalut13 = cblendingalphalut[13];
        cblendingalphalut12 = cblendingalphalut[12];
        cblendingalphalut19 = cblendingalphalut[19];
        cblendingalphalut18 = cblendingalphalut[18];
        cblendingalphalut17 = cblendingalphalut[17];
        cblendingalphalut16 = cblendingalphalut[16];
        cblendingalphalut23 = cblendingalphalut[23];
        cblendingalphalut22 = cblendingalphalut[22];
        cblendingalphalut21 = cblendingalphalut[21];
        cblendingalphalut20 = cblendingalphalut[20];
        cblendingalphalut27 = cblendingalphalut[27];
        cblendingalphalut26 = cblendingalphalut[26];
        cblendingalphalut25 = cblendingalphalut[25];
        cblendingalphalut24 = cblendingalphalut[24];
        cblendingalphalut31 = cblendingalphalut[31];
        cblendingalphalut30 = cblendingalphalut[30];
        cblendingalphalut29 = cblendingalphalut[29];
        cblendingalphalut28 = cblendingalphalut[28];
#if 0
        ymotionstrlut3      = ymotionstrlut[3  ];
        ymotionstrlut2      = ymotionstrlut[2  ];
        ymotionstrlut1      = ymotionstrlut[1  ];
        ymotionstrlut0      = ymotionstrlut[0  ];
        ymotionstrlut7      = ymotionstrlut[7  ];
        ymotionstrlut6      = ymotionstrlut[6  ];
        ymotionstrlut5      = ymotionstrlut[5  ];
        ymotionstrlut4      = ymotionstrlut[4  ];
        ymotionstrlut11     = ymotionstrlut[11 ];
        ymotionstrlut10     = ymotionstrlut[10 ];
        ymotionstrlut9      = ymotionstrlut[9  ];
        ymotionstrlut8      = ymotionstrlut[8  ];
        ymotionstrlut15     = ymotionstrlut[15 ];
        ymotionstrlut14     = ymotionstrlut[14 ];
        ymotionstrlut13     = ymotionstrlut[13 ];
        ymotionstrlut12     = ymotionstrlut[12 ];
        ymotionstrlut19     = ymotionstrlut[19 ];
        ymotionstrlut18     = ymotionstrlut[18 ];
        ymotionstrlut17     = ymotionstrlut[17 ];
        ymotionstrlut16     = ymotionstrlut[16 ];
        ymotionstrlut23     = ymotionstrlut[23 ];
        ymotionstrlut22     = ymotionstrlut[22 ];
        ymotionstrlut21     = ymotionstrlut[21 ];
        ymotionstrlut20     = ymotionstrlut[20 ];
        ymotionstrlut27     = ymotionstrlut[27 ];
        ymotionstrlut26     = ymotionstrlut[26 ];
        ymotionstrlut25     = ymotionstrlut[25 ];
        ymotionstrlut24     = ymotionstrlut[24 ];
        ymotionstrlut31     = ymotionstrlut[31 ];
        ymotionstrlut30     = ymotionstrlut[30 ];
        ymotionstrlut29     = ymotionstrlut[29 ];
        ymotionstrlut28     = ymotionstrlut[28 ];
        ymotionstrlut35     = ymotionstrlut[35 ];
        ymotionstrlut34     = ymotionstrlut[34 ];
        ymotionstrlut33     = ymotionstrlut[33 ];
        ymotionstrlut32     = ymotionstrlut[32 ];
        ymotionstrlut39     = ymotionstrlut[39 ];
        ymotionstrlut38     = ymotionstrlut[38 ];
        ymotionstrlut37     = ymotionstrlut[37 ];
        ymotionstrlut36     = ymotionstrlut[36 ];
        ymotionstrlut43     = ymotionstrlut[43 ];
        ymotionstrlut42     = ymotionstrlut[42 ];
        ymotionstrlut41     = ymotionstrlut[41 ];
        ymotionstrlut40     = ymotionstrlut[40 ];
        ymotionstrlut47     = ymotionstrlut[47 ];
        ymotionstrlut46     = ymotionstrlut[46 ];
        ymotionstrlut45     = ymotionstrlut[45 ];
        ymotionstrlut44     = ymotionstrlut[44 ];
        ymotionstrlut51     = ymotionstrlut[51 ];
        ymotionstrlut50     = ymotionstrlut[50 ];
        ymotionstrlut49     = ymotionstrlut[49 ];
        ymotionstrlut48     = ymotionstrlut[48 ];
        ymotionstrlut55     = ymotionstrlut[55 ];
        ymotionstrlut54     = ymotionstrlut[54 ];
        ymotionstrlut53     = ymotionstrlut[53 ];
        ymotionstrlut52     = ymotionstrlut[52 ];
        ymotionstrlut59     = ymotionstrlut[59 ];
        ymotionstrlut58     = ymotionstrlut[58 ];
        ymotionstrlut57     = ymotionstrlut[57 ];
        ymotionstrlut56     = ymotionstrlut[56 ];
        ymotionstrlut63     = ymotionstrlut[63 ];
        ymotionstrlut62     = ymotionstrlut[62 ];
        ymotionstrlut61     = ymotionstrlut[61 ];
        ymotionstrlut60     = ymotionstrlut[60 ];
        ymotionstrlut67     = ymotionstrlut[67 ];
        ymotionstrlut66     = ymotionstrlut[66 ];
        ymotionstrlut65     = ymotionstrlut[65 ];
        ymotionstrlut64     = ymotionstrlut[64 ];
        ymotionstrlut71     = ymotionstrlut[71 ];
        ymotionstrlut70     = ymotionstrlut[70 ];
        ymotionstrlut69     = ymotionstrlut[69 ];
        ymotionstrlut68     = ymotionstrlut[68 ];
        ymotionstrlut75     = ymotionstrlut[75 ];
        ymotionstrlut74     = ymotionstrlut[74 ];
        ymotionstrlut73     = ymotionstrlut[73 ];
        ymotionstrlut72     = ymotionstrlut[72 ];
        ymotionstrlut79     = ymotionstrlut[79 ];
        ymotionstrlut78     = ymotionstrlut[78 ];
        ymotionstrlut77     = ymotionstrlut[77 ];
        ymotionstrlut76     = ymotionstrlut[76 ];
        ymotionstrlut83     = ymotionstrlut[83 ];
        ymotionstrlut82     = ymotionstrlut[82 ];
        ymotionstrlut81     = ymotionstrlut[81 ];
        ymotionstrlut80     = ymotionstrlut[80 ];
        ymotionstrlut87     = ymotionstrlut[87 ];
        ymotionstrlut86     = ymotionstrlut[86 ];
        ymotionstrlut85     = ymotionstrlut[85 ];
        ymotionstrlut84     = ymotionstrlut[84 ];
        ymotionstrlut91     = ymotionstrlut[91 ];
        ymotionstrlut90     = ymotionstrlut[90 ];
        ymotionstrlut89     = ymotionstrlut[89 ];
        ymotionstrlut88     = ymotionstrlut[88 ];
        ymotionstrlut95     = ymotionstrlut[95 ];
        ymotionstrlut94     = ymotionstrlut[94 ];
        ymotionstrlut93     = ymotionstrlut[93 ];
        ymotionstrlut92     = ymotionstrlut[92 ];
        ymotionstrlut99     = ymotionstrlut[99 ];
        ymotionstrlut98     = ymotionstrlut[98 ];
        ymotionstrlut97     = ymotionstrlut[97 ];
        ymotionstrlut96     = ymotionstrlut[96 ];
        ymotionstrlut103    = ymotionstrlut[103];
        ymotionstrlut102    = ymotionstrlut[102];
        ymotionstrlut101    = ymotionstrlut[101];
        ymotionstrlut100    = ymotionstrlut[100];
        ymotionstrlut107    = ymotionstrlut[107];
        ymotionstrlut106    = ymotionstrlut[106];
        ymotionstrlut105    = ymotionstrlut[105];
        ymotionstrlut104    = ymotionstrlut[104];
        ymotionstrlut111    = ymotionstrlut[111];
        ymotionstrlut110    = ymotionstrlut[110];
        ymotionstrlut109    = ymotionstrlut[109];
        ymotionstrlut108    = ymotionstrlut[108];
        ymotionstrlut115    = ymotionstrlut[115];
        ymotionstrlut114    = ymotionstrlut[114];
        ymotionstrlut113    = ymotionstrlut[113];
        ymotionstrlut112    = ymotionstrlut[112];
        ymotionstrlut119    = ymotionstrlut[119];
        ymotionstrlut118    = ymotionstrlut[118];
        ymotionstrlut117    = ymotionstrlut[117];
        ymotionstrlut116    = ymotionstrlut[116];
        ymotionstrlut123    = ymotionstrlut[123];
        ymotionstrlut122    = ymotionstrlut[122];
        ymotionstrlut121    = ymotionstrlut[121];
        ymotionstrlut120    = ymotionstrlut[120];
        ymotionstrlut127    = ymotionstrlut[127];
        ymotionstrlut126    = ymotionstrlut[126];
        ymotionstrlut125    = ymotionstrlut[125];
        ymotionstrlut124    = ymotionstrlut[124];
        cmotionstrlut3      = cmotionstrlut[3  ];
        cmotionstrlut2      = cmotionstrlut[2  ];
        cmotionstrlut1      = cmotionstrlut[1  ];
        cmotionstrlut0      = cmotionstrlut[0  ];
        cmotionstrlut7      = cmotionstrlut[7  ];
        cmotionstrlut6      = cmotionstrlut[6  ];
        cmotionstrlut5      = cmotionstrlut[5  ];
        cmotionstrlut4      = cmotionstrlut[4  ];
        cmotionstrlut11     = cmotionstrlut[11 ];
        cmotionstrlut10     = cmotionstrlut[10 ];
        cmotionstrlut9      = cmotionstrlut[9  ];
        cmotionstrlut8      = cmotionstrlut[8  ];
        cmotionstrlut15     = cmotionstrlut[15 ];
        cmotionstrlut14     = cmotionstrlut[14 ];
        cmotionstrlut13     = cmotionstrlut[13 ];
        cmotionstrlut12     = cmotionstrlut[12 ];
        cmotionstrlut19     = cmotionstrlut[19 ];
        cmotionstrlut18     = cmotionstrlut[18 ];
        cmotionstrlut17     = cmotionstrlut[17 ];
        cmotionstrlut16     = cmotionstrlut[16 ];
        cmotionstrlut23     = cmotionstrlut[23 ];
        cmotionstrlut22     = cmotionstrlut[22 ];
        cmotionstrlut21     = cmotionstrlut[21 ];
        cmotionstrlut20     = cmotionstrlut[20 ];
        cmotionstrlut27     = cmotionstrlut[27 ];
        cmotionstrlut26     = cmotionstrlut[26 ];
        cmotionstrlut25     = cmotionstrlut[25 ];
        cmotionstrlut24     = cmotionstrlut[24 ];
        cmotionstrlut31     = cmotionstrlut[31 ];
        cmotionstrlut30     = cmotionstrlut[30 ];
        cmotionstrlut29     = cmotionstrlut[29 ];
        cmotionstrlut28     = cmotionstrlut[28 ];
        cmotionstrlut35     = cmotionstrlut[35 ];
        cmotionstrlut34     = cmotionstrlut[34 ];
        cmotionstrlut33     = cmotionstrlut[33 ];
        cmotionstrlut32     = cmotionstrlut[32 ];
        cmotionstrlut39     = cmotionstrlut[39 ];
        cmotionstrlut38     = cmotionstrlut[38 ];
        cmotionstrlut37     = cmotionstrlut[37 ];
        cmotionstrlut36     = cmotionstrlut[36 ];
        cmotionstrlut43     = cmotionstrlut[43 ];
        cmotionstrlut42     = cmotionstrlut[42 ];
        cmotionstrlut41     = cmotionstrlut[41 ];
        cmotionstrlut40     = cmotionstrlut[40 ];
        cmotionstrlut47     = cmotionstrlut[47 ];
        cmotionstrlut46     = cmotionstrlut[46 ];
        cmotionstrlut45     = cmotionstrlut[45 ];
        cmotionstrlut44     = cmotionstrlut[44 ];
        cmotionstrlut51     = cmotionstrlut[51 ];
        cmotionstrlut50     = cmotionstrlut[50 ];
        cmotionstrlut49     = cmotionstrlut[49 ];
        cmotionstrlut48     = cmotionstrlut[48 ];
        cmotionstrlut55     = cmotionstrlut[55 ];
        cmotionstrlut54     = cmotionstrlut[54 ];
        cmotionstrlut53     = cmotionstrlut[53 ];
        cmotionstrlut52     = cmotionstrlut[52 ];
        cmotionstrlut59     = cmotionstrlut[59 ];
        cmotionstrlut58     = cmotionstrlut[58 ];
        cmotionstrlut57     = cmotionstrlut[57 ];
        cmotionstrlut56     = cmotionstrlut[56 ];
        cmotionstrlut63     = cmotionstrlut[63 ];
        cmotionstrlut62     = cmotionstrlut[62 ];
        cmotionstrlut61     = cmotionstrlut[61 ];
        cmotionstrlut60     = cmotionstrlut[60 ];
        cmotionstrlut67     = cmotionstrlut[67 ];
        cmotionstrlut66     = cmotionstrlut[66 ];
        cmotionstrlut65     = cmotionstrlut[65 ];
        cmotionstrlut64     = cmotionstrlut[64 ];
        cmotionstrlut71     = cmotionstrlut[71 ];
        cmotionstrlut70     = cmotionstrlut[70 ];
        cmotionstrlut69     = cmotionstrlut[69 ];
        cmotionstrlut68     = cmotionstrlut[68 ];
        cmotionstrlut75     = cmotionstrlut[75 ];
        cmotionstrlut74     = cmotionstrlut[74 ];
        cmotionstrlut73     = cmotionstrlut[73 ];
        cmotionstrlut72     = cmotionstrlut[72 ];
        cmotionstrlut79     = cmotionstrlut[79 ];
        cmotionstrlut78     = cmotionstrlut[78 ];
        cmotionstrlut77     = cmotionstrlut[77 ];
        cmotionstrlut76     = cmotionstrlut[76 ];
        cmotionstrlut83     = cmotionstrlut[83 ];
        cmotionstrlut82     = cmotionstrlut[82 ];
        cmotionstrlut81     = cmotionstrlut[81 ];
        cmotionstrlut80     = cmotionstrlut[80 ];
        cmotionstrlut87     = cmotionstrlut[87 ];
        cmotionstrlut86     = cmotionstrlut[86 ];
        cmotionstrlut85     = cmotionstrlut[85 ];
        cmotionstrlut84     = cmotionstrlut[84 ];
        cmotionstrlut91     = cmotionstrlut[91 ];
        cmotionstrlut90     = cmotionstrlut[90 ];
        cmotionstrlut89     = cmotionstrlut[89 ];
        cmotionstrlut88     = cmotionstrlut[88 ];
        cmotionstrlut95     = cmotionstrlut[95 ];
        cmotionstrlut94     = cmotionstrlut[94 ];
        cmotionstrlut93     = cmotionstrlut[93 ];
        cmotionstrlut92     = cmotionstrlut[92 ];
        cmotionstrlut99     = cmotionstrlut[99 ];
        cmotionstrlut98     = cmotionstrlut[98 ];
        cmotionstrlut97     = cmotionstrlut[97 ];
        cmotionstrlut96     = cmotionstrlut[96 ];
        cmotionstrlut103    = cmotionstrlut[103];
        cmotionstrlut102    = cmotionstrlut[102];
        cmotionstrlut101    = cmotionstrlut[101];
        cmotionstrlut100    = cmotionstrlut[100];
        cmotionstrlut107    = cmotionstrlut[107];
        cmotionstrlut106    = cmotionstrlut[106];
        cmotionstrlut105    = cmotionstrlut[105];
        cmotionstrlut104    = cmotionstrlut[104];
        cmotionstrlut111    = cmotionstrlut[111];
        cmotionstrlut110    = cmotionstrlut[110];
        cmotionstrlut109    = cmotionstrlut[109];
        cmotionstrlut108    = cmotionstrlut[108];
        cmotionstrlut115    = cmotionstrlut[115];
        cmotionstrlut114    = cmotionstrlut[114];
        cmotionstrlut113    = cmotionstrlut[113];
        cmotionstrlut112    = cmotionstrlut[112];
        cmotionstrlut119    = cmotionstrlut[119];
        cmotionstrlut118    = cmotionstrlut[118];
        cmotionstrlut117    = cmotionstrlut[117];
        cmotionstrlut116    = cmotionstrlut[116];
        cmotionstrlut123    = cmotionstrlut[123];
        cmotionstrlut122    = cmotionstrlut[122];
        cmotionstrlut121    = cmotionstrlut[121];
        cmotionstrlut120    = cmotionstrlut[120];
        cmotionstrlut127    = cmotionstrlut[127];
        cmotionstrlut126    = cmotionstrlut[126];
        cmotionstrlut125    = cmotionstrlut[125];
        cmotionstrlut124    = cmotionstrlut[124];

        //mc

        lmt_rgdify                          = 511;
        core_rgdify                         = 7;
        g_rgdifycore                        = 1023;
        k_rgdifycore                        = 2;
        g_tpdif_rgsad                       = 255;
        k_tpdif_rgsad                       = 16;
        kmv_rgsad                           = 32;
        coef_sadlpf                         = 1;
        th_0mvsad_rgmv                      = 512;
        th_saddif_rgmv                      = 256;
        thmag_rgmv                          = 96;
        lmt_mag_rg                          = 255;
        core_mag_rg                         = 3;
        en_mvadj_rgmvls                     = 1;
        th_mvadj_rgmvls                     = 8;
        k_mag_rgmvls                        = 8;

        core_mag_rgmvls                     = 63;
        k_mv_rgmvls                         = 16;
        core_mv_rgmvls                      = 15;

        k_sadcore_rgmv                      = 8;
        th_sad_rgls                         = 8;
        th_mag_rgls                         = 40;
        k_sad_rgls                          = 8;
        force_mvx                           = 0;
        force_mven                          = 0;
        th_hblkdist_mvdlt                   = 4;
        th_vblkdist_mvdlt                   = 1;
        th_ls_mvdlt                         = 8;
        th_rgmvx_mvdlt                      = 4;
        th_blkmvx_mvdlt                     = 6;
        thh_sad_mvdlt                       = 16;
        thl_sad_mvdlt                       = 96;
        g_mag_mvdlt                         = 16;
        th_mag_mvdlt                        = 12;
        k_sadcore_mvdlt                     = 2;
        k_core_simimv                       = 8;
        gl_core_simimv                      = 0;
        gh_core_simimv                      = 15;
        k_simimvw                           = 32;
        k_rglsw                             = 20;
        rgtb_en_mcw                         = 1;
        core_mvy_mcw                        = 3;
        k_mvy_mcw                           = 20;
        core_rgsadadj_mcw                   = 64;
        k_rgsadadj_mcw                      = 8;  //0~15
        k_core_vsaddif                      = 16; //0~31
        gl_core_vsaddif                     = 5; //8;   //0~31
        gh_core_vsad_dif                    = 64; //0~127
        k_vsaddifw                          = 10; //8;   //0~63
        mode_rgysad_mcw                     = 0;  //0~1
        core_rgmag_mcw                      = 24; //0~255
        x0_rgmag_mcw                        = 64; //0~511
        k0_rgmag_mcw                        = 256; //0~511
        g0_rgmag_mcw                        = 64; //0~255
        k1_rgmag_mcw                        = 320; //0~511
        core_rgsad_mcw                      = 96; //0~255
        x0_rgsad_mcw                        = 512; //0~1023
        k0_rgsad_mcw                        = 160; //0~511
        g0_rgsad_mcw                        = 255; //0~255
        k1_rgsad_mcw                        = 128; //0~511
        x0_smrg_mcw                         = 16; //0~255
        k0_smrg_mcw                         = 64; //0~255
        x_rgsad_mcw                         = 112; //0~255
        k_rgsad_mcw                         = 24; //0~63
        x0_tpmvdist_mcw                     = 255; //0~255
        k0_tpmvdist_mcw                     = 64; //0~127
        g0_tpmvdist_mcw                     = 0;  //0~255
        k1_tpmvdist_mcw                     = 32; //0~127
        k_minmvdist_mcw                     = 4;  //0~15
        k_avgmvdist_mcw                     = 4;  //0~15
        b_core_tpmvdist_mcw                 = 2;  //0~7
        k_core_tpmvdist_mcw                 = 2;  //0~7
        k_difhcore_mcw                     = 18; //0~31
        k_difvcore_mcw                     = 32; //0~63
        k_max_core_mcw                     = 8;  //fixed
        k_max_dif_mcw                      = 8;  //fixed
        k1_max_mag_mcw                     = 8;  //fixed
        k0_max_mag_mcw                     = 8;  //fixed
        k_tbdif_mcw                        = 15;  //fixed
        k_tbmag_mcw                        = 0;   //fixed
        x0_mag_wnd_mcw                     = 32; //0~127
        k0_mag_wnd_mcw                     = 6;  //0~15
        g0_mag_wnd_mcw                     = 24; //0~63
        k1_mag_wnd_mcw                     = 6;  //0~15
        g1_mag_wnd_mcw                     = 288; //0~511
        x0_sad_wnd_mcw                     = 8;  //0~127
        k0_sad_wnd_mcw                     = 16; //0~31
        g0_sad_wnd_mcw                     = 16; //0~255
        k1_sad_wnd_mcw                     = 16; //0~31
        g1_sad_wnd_mcw                     = 288; //0~511
        k_max_hvdif_dw                 = 12; //4;   //0~15
        gain_lpf_dw                    = 15; //fixed
        core_bhvdif_dw                 = 5;  //fixed
        k_bhvdif_dw                    = 64; //fixed
        b_bhvdif_dw                    = 0;  //fixed
        b_hvdif_dw                     = 0;  //fixed
        core_hvdif_dw                  = 16; //fixed
        k_difv_dw                      = 20; //0~31
        core_mv_dw                     = -2; //fixed
        b_mv_dw                        = 56; //fixed
        x0_hvdif_dw                    = 256; //0~511
        k0_hvdif_dw                    = 8;  //0~15
        g0_hvdif_dw                    = 128; //0~511
        k1_hvdif_dw                    = 8;  //0~15
        x0_mv_dw                       = 8;  //fixed
        k0_mv_dw                       = 16; //fixed
        g0_mv_dw                       = 32; //fixed
        k1_mv_dw                       = 64; //fixed
        x0_mt_dw                       = 32; //0~127
        k0_mt_dw                       = 32; //0~63
        g0_mt_dw                       = 64; //0~255
        k1_mt_dw                       = 32; //0~63
        g0_mv_mt                       = 31; //0~31
        x0_mv_mt                       = 1;  //0~3
        k1_mv_mt                       = 20; //0~31
        b_mt_dw                        = 0;  //0~255
        gain_up_mclpfv                 = 16; //fixed
        gain_dn_mclpfv                 = 16; //fixed
        gain_mclpfh                    = 16; //fixed
        rs_pxlmag_mcw                  = 0;  //0~1
        x_pxlmag_mcw                   = 2;  //0~7
        k_pxlmag_mcw                   = 8;  //0~31
        mclpf_mode                     = 1;  //0~1
        g_pxlmag_mcw                   = 0;  //fixed
        k_y_vertw                      = 8;  //0~31
        k_c_vertw                      = 7;  //0~127
        k_delta                        = 8;  //0~31
        bdh_mcpos                      = 4;  //0~7
        bdv_mcpos                      = 4; //1;   //0~7
        x0_mv_mc                       = 2;  //0~7
        k1_mv_mc                       = 16; //0~63
        x_fstmt_mc                     = 16; //3;   //0~31
        k_fstmt_mc                     = 8;  //0~31
        g_fstmt_mc                     = 31; //0~31
        x_slmt_mc                      = 2;  //0~31
        k_slmt_mc                      = 16; //0~31
        g_slmt_mc                      = 48; //0~63
        x_hfcore_mc                    = 0; //2;   //0~31
        k_hfcore_mc                    = 31; //24;  //0~31
        g_hfcore_mc                    = 63; //16;  //0~63
        c0_mc                          = 0;  //0~width-1
        r0_mc                          = 0;  //0~height-1
        c1_mc                          = width - 1; //0~width-1
        r1_mc                          = height - 1; //0~height-1
        mcmvrange                      = 32; //0~32
        scenechange_mc                 = 0;  //0~1
        x_frcount_mc                   = 8;  //0~31
        k_frcount_mc                   = 127; //16;  //0~127
        mcstartr                       = 0;  //0~255
        mcstartc                       = 0;  //0~255
        mcendr                         = 0;  //0~255
        mcendc                         = 0;  //0~255

        movethdh                       = 32; //0~32
        movethdl                       = 32; //0~32
        movecorig                      = 0;  //0~32
        movegain                       = 1;  //0~32

        numt_lpf_en                    = 1;
        numt_coring                    = 0;
        numt_gain                      = 0;
        mc_numt_blden                  = 1;
        core_rglsw                     = 0;  //rand()%8;
        k0_hfvline                     = 4;  //rand()%8;
        k1_hfvline                     = 2;  //rand()%8;
        core_hfvline                   = 15; //rand()%64;
        k0_hw                          = 16; //rand()%64;
        k1_hw                          = 32; //rand()%64;
        g_hw                           = 80; //rand()%128;
        b_core0_hw                     = 0;  //rand()%16;
        k_core0_hw                     = 4;  //rand()%16;
        core1_hw                       = 3;  //rand()%16;
        subpix_mc_en                   = 1;  //rand()%16;
        g_difcore_mcw                  = 208;//rand()%512;
        rp_k1_mag_wnd_mcw              = 10; //rand()%16;
        rp_k1_sad_wnd_mcw              = 10; //rand()%32;
        x0_sadr_wnd_mcw                = 8;  //rand()%128;
        k0_sadr_wnd_mcw                = 4;  //rand()%16;
        g0_sadr_wnd_mcw                = 4;  //rand()%256;
        k1_sadr_wnd_mcw                = 4;  //rand()%16;
        g1_sadr_wnd_mcw                = 288;//rand()%512;
        k_p1cfdifh_mcw                 = 6;  //rand()%16;
        k_mcdifv_mcw                   = 12; //rand()%16;
        th_cur_blksad                  = 128;//rand()%512;
        thh_neigh_blksad               = 256;//rand()%512;
        thl_neigh_blksad               = 128;//rand()%512;
        th_cur_blkmotion               = 8;  //rand()%32;
        th_rgmv_mag                    = 512;//rand()%1024;
        blkmv_update_en                = 1;  //rand()%2;
        k_rpcounter                    = 4;//3;  //rand()%8;
        rpcounterth                    = 2;  //rand()%8;
        rp_mvxth_rgmv                  = 3;  //rand()%8;
        rp_difmvxth_rgmv               = 5;  //rand()%16;
        rp_difsadth_rgmv               = 32; //rand()%256;
        rp_sadth_rgmv                  = 125;//rand()%512;
        rp_magth_rgmv                  = 600;//rand()%1024;
        rp_difmvxth_sp                 = 2;  //rand()%8;
        rp_difsadth_tb                 = 428;//rand()%512;
        k1_tpdif_rgsad                 = 80;//63; //rand()%64;
        submv_sadchk_en                = 0;  //fixed
        rp_en                          = 0;  //rand()%2;
        difvt_mode                     = 0;//1;  //rand()%2;

        //96mv200 add
        mcw_blkm_thdh                  = 0;
        mcw_blkm_thdl                  = 0;
        mcw_blkm_coringmove            = 0;
        mcw_blkm_gainmove              = 0;
#endif

    }

    //drv transfer
    VPSS_Sys_SetMarketcoor(pstVpssRegs, 0x0, marketcoor);
    VPSS_Sys_SetMarketmode(pstVpssRegs, 0x0, marketmode);
    VPSS_Sys_SetMarketmodeen(pstVpssRegs, 0x0, marketmodeen);
    //VPSS_Sys_SetMcnrRgmeMode(pstVpssRegs, mcnr_rgme_mode);
    //VPSS_Sys_SetMcnrMedsEn(pstVpssRegs, mcnr_meds_en);
    VPSS_Sys_SetMcnrEn(pstVpssRegs, 0x0, mcnr_en);
    VPSS_Sys_SetCnren(pstVpssRegs, 0x0, cnren);
    VPSS_Sys_SetYnren(pstVpssRegs, 0x0, ynren);
    VPSS_Sys_SetNren(pstVpssRegs, 0x0, nren);
    VPSS_Sys_SetAlpha2(pstVpssRegs, 0x0, alpha2);
    VPSS_Sys_SetAlpha1(pstVpssRegs, 0x0, alpha1);
    VPSS_Sys_SetCmotionlpfmode(pstVpssRegs, 0x0, cmotionlpfmode);
    VPSS_Sys_SetYmotionlpfmode(pstVpssRegs, 0x0, ymotionlpfmode);
    VPSS_Sys_SetCmotioncalcmode(pstVpssRegs, 0x0, cmotioncalcmode);
    VPSS_Sys_SetYmotioncalcmode(pstVpssRegs, 0x0, ymotioncalcmode);
    VPSS_Sys_SetMeancadjshift(pstVpssRegs, 0x0, meancadjshift);
    VPSS_Sys_SetMeanyadjshift(pstVpssRegs, 0x0, meanyadjshift);
    VPSS_Sys_SetMeanCmotionAdjEn(pstVpssRegs, 0x0, mean_cmotion_adj_en);
    VPSS_Sys_SetMeanYmotionAdjEn(pstVpssRegs, 0x0, mean_ymotion_adj_en);
    VPSS_Sys_SetMdprelpfen(pstVpssRegs, 0x0, mdprelpfen);
    VPSS_Sys_SetCmdcore(pstVpssRegs, 0x0, cmdcore);
    VPSS_Sys_SetCmdgain(pstVpssRegs, 0x0, cmdgain);
    VPSS_Sys_SetYmdcore(pstVpssRegs, 0x0, ymdcore);
    VPSS_Sys_SetYmdgain(pstVpssRegs, 0x0, ymdgain);
    VPSS_Sys_SetRandomctrlmode(pstVpssRegs, 0x0, randomctrlmode);
    VPSS_Sys_SetBlkdiffthd(pstVpssRegs, 0x0, blkdiffthd);
    VPSS_Sys_SetNoisedetecten(pstVpssRegs, 0x0, noisedetecten);
    VPSS_Sys_SetFlatthdmax(pstVpssRegs, 0x0, flatthdmax);
    VPSS_Sys_SetFlatthdmed(pstVpssRegs, 0x0, flatthdmed);
    VPSS_Sys_SetFlatthdmin(pstVpssRegs, 0x0, flatthdmin);
    VPSS_Sys_SetSmvythd(pstVpssRegs, 0x0, smvythd);
    VPSS_Sys_SetSmvxthd(pstVpssRegs, 0x0, smvxthd);
    VPSS_Sys_SetDiscardsmvyen(pstVpssRegs, 0x0, discardsmvyen);
    VPSS_Sys_SetDiscardsmvxen(pstVpssRegs, 0x0, discardsmvxen);
    VPSS_Sys_SetGmAdj(pstVpssRegs, 0x0, gm_adj);
    VPSS_Sys_SetMvlpfmode(pstVpssRegs, 0x0, mvlpfmode);
    VPSS_Sys_SetMvrefmode(pstVpssRegs, 0x0, mvrefmode);
    VPSS_Sys_SetMotionestimateen(pstVpssRegs, 0x0, motionestimateen);
    VPSS_Sys_SetMagPnlCoreXmv(pstVpssRegs, 0x0, mag_pnl_core_xmv);
    VPSS_Sys_SetMagPnlGainXmv(pstVpssRegs, 0x0, mag_pnl_gain_xmv);
    VPSS_Sys_SetMagPnlCore0mv(pstVpssRegs, 0x0, mag_pnl_core_0mv);
    VPSS_Sys_SetMagPnlGain0mv(pstVpssRegs, 0x0, mag_pnl_gain_0mv);
    VPSS_Sys_SetStdPnlCoreXmv(pstVpssRegs, 0x0, std_pnl_core_xmv);
    VPSS_Sys_SetStdPnlGainXmv(pstVpssRegs, 0x0, std_pnl_gain_xmv);
    VPSS_Sys_SetStdPnlCore0mv(pstVpssRegs, 0x0, std_pnl_core_0mv);
    VPSS_Sys_SetStdPnlGain0mv(pstVpssRegs, 0x0, std_pnl_gain_0mv);
    VPSS_Sys_SetStdCoreXmv(pstVpssRegs, 0x0, std_core_xmv);
    VPSS_Sys_SetStdCore0mv(pstVpssRegs, 0x0, std_core_0mv);
    VPSS_Sys_SetStdPnlCore(pstVpssRegs, 0x0, std_pnl_core);
    VPSS_Sys_SetStdPnlGain(pstVpssRegs, 0x0, std_pnl_gain);
    VPSS_Sys_SetAdjXmvMax(pstVpssRegs, 0x0, adj_xmv_max);
    VPSS_Sys_SetAdj0mvMax(pstVpssRegs, 0x0, adj_0mv_max);
    VPSS_Sys_SetAdjXmvMin(pstVpssRegs, 0x0, adj_xmv_min);
    VPSS_Sys_SetAdj0mvMin(pstVpssRegs, 0x0, adj_0mv_min);
    VPSS_Sys_SetAdjMvMin(pstVpssRegs, 0x0, adj_mv_min);
    VPSS_Sys_SetAdjMvMax(pstVpssRegs, 0x0, adj_mv_max);
    VPSS_Sys_SetCbcrweight2(pstVpssRegs, 0x0, cbcrweight2);
    VPSS_Sys_SetCbcrweight1(pstVpssRegs, 0x0, cbcrweight1);
    VPSS_Sys_SetCbcrupdateen(pstVpssRegs, 0x0, cbcrupdateen);
    VPSS_Sys_SetCrend1(pstVpssRegs, 0x0, crend1);
    VPSS_Sys_SetCbend1(pstVpssRegs, 0x0, cbend1);
    VPSS_Sys_SetCrbegin1(pstVpssRegs, 0x0, crbegin1);
    VPSS_Sys_SetCbbegin1(pstVpssRegs, 0x0, cbbegin1);
    VPSS_Sys_SetCrend2(pstVpssRegs, 0x0, crend2);
    VPSS_Sys_SetCbend2(pstVpssRegs, 0x0, cbend2);
    VPSS_Sys_SetCrbegin2(pstVpssRegs, 0x0, crbegin2);
    VPSS_Sys_SetCbbegin2(pstVpssRegs, 0x0, cbbegin2);
    VPSS_Sys_SetMotionmergeratio(pstVpssRegs, 0x0, motionmergeratio);
    VPSS_Sys_SetPremotionalpha(pstVpssRegs, 0x0, premotionalpha);
    VPSS_Sys_SetPremotionmergemode(pstVpssRegs, 0x0, premotionmergemode);
    VPSS_Sys_SetCmotioncore(pstVpssRegs, 0x0, cmotioncore);
    VPSS_Sys_SetCmotiongain(pstVpssRegs, 0x0, cmotiongain);
    VPSS_Sys_SetYmotioncore(pstVpssRegs, 0x0, ymotioncore);
    VPSS_Sys_SetYmotiongain(pstVpssRegs, 0x0, ymotiongain);
    VPSS_Sys_SetMotionmappingen(pstVpssRegs, 0x0, motionmappingen);
    VPSS_Sys_SetSaltuslevel(pstVpssRegs, 0x0, saltuslevel);
    VPSS_Sys_SetSaltusdecten(pstVpssRegs, 0x0, saltusdecten);
    VPSS_Sys_SetCmclpfmode(pstVpssRegs, 0x0, cmclpfmode);
    VPSS_Sys_SetYmclpfmode(pstVpssRegs, 0x0, ymclpfmode);
    VPSS_Sys_SetCmcadjen(pstVpssRegs, 0x0, cmcadjen);
    VPSS_Sys_SetYmcadjen(pstVpssRegs, 0x0, ymcadjen);
    VPSS_Sys_SetCnonrrange(pstVpssRegs, 0x0, cnonrrange);
    VPSS_Sys_SetYnonrrange(pstVpssRegs, 0x0, ynonrrange);
    VPSS_Sys_SetCmotionmode(pstVpssRegs, 0x0, cmotionmode);
    VPSS_Sys_SetYmotionmode(pstVpssRegs, 0x0, ymotionmode);
    VPSS_Sys_SetScenechangeinfo(pstVpssRegs, 0x0, scenechangeinfo);
    VPSS_Sys_SetScenechangeen(pstVpssRegs, 0x0, scenechangeen);
    VPSS_Sys_SetCfgCmdcore(pstVpssRegs, 0x0, cfg_cmdcore);
    VPSS_Sys_SetCfgCmdgain(pstVpssRegs, 0x0, cfg_cmdgain);
    VPSS_Sys_SetCfgYmdcore(pstVpssRegs, 0x0, cfg_ymdcore);
    VPSS_Sys_SetCfgYmdgain(pstVpssRegs, 0x0, cfg_ymdgain);
    VPSS_Sys_SetFlatinfoymax(pstVpssRegs, 0x0, flatinfoymax);
    VPSS_Sys_SetFlatinfoxmax(pstVpssRegs, 0x0, flatinfoxmax);
    VPSS_Sys_SetFlatinfoymin(pstVpssRegs, 0x0, flatinfoymin);
    VPSS_Sys_SetFlatinfoxmin(pstVpssRegs, 0x0, flatinfoxmin);
    VPSS_Sys_SetYblendingymax(pstVpssRegs, 0x0, yblendingymax);
    VPSS_Sys_SetYblendingxmax(pstVpssRegs, 0x0, yblendingxmax);
    VPSS_Sys_SetYblendingymin(pstVpssRegs, 0x0, yblendingymin);
    VPSS_Sys_SetYblendingxmin(pstVpssRegs, 0x0, yblendingxmin);
    VPSS_Sys_SetCblendingymax(pstVpssRegs, 0x0, cblendingymax);
    VPSS_Sys_SetCblendingxmax(pstVpssRegs, 0x0, cblendingxmax);
    VPSS_Sys_SetCblendingymin(pstVpssRegs, 0x0, cblendingymin);
    VPSS_Sys_SetCblendingxmin(pstVpssRegs, 0x0, cblendingxmin);
    VPSS_Sys_SetDtblendingymax(pstVpssRegs, 0x0, dtblendingymax);
    VPSS_Sys_SetDtblendingxmax(pstVpssRegs, 0x0, dtblendingxmax);
    VPSS_Sys_SetDtblendingymin(pstVpssRegs, 0x0, dtblendingymin);
    VPSS_Sys_SetDtblendingxmin(pstVpssRegs, 0x0, dtblendingxmin);

    VPSS_Sys_SetMeanMotionRatio3(pstVpssRegs, 0x0, mean_motion_ratio3);
    VPSS_Sys_SetMeanMotionRatio2(pstVpssRegs, 0x0, mean_motion_ratio2);
    VPSS_Sys_SetMeanMotionRatio1(pstVpssRegs, 0x0, mean_motion_ratio1);
    VPSS_Sys_SetMeanMotionRatio0(pstVpssRegs, 0x0, mean_motion_ratio0);
    VPSS_Sys_SetMeanMotionRatio7(pstVpssRegs, 0x0, mean_motion_ratio7);
    VPSS_Sys_SetMeanMotionRatio6(pstVpssRegs, 0x0, mean_motion_ratio6);
    VPSS_Sys_SetMeanMotionRatio5(pstVpssRegs, 0x0, mean_motion_ratio5);
    VPSS_Sys_SetMeanMotionRatio4(pstVpssRegs, 0x0, mean_motion_ratio4);
    VPSS_Sys_SetMeanMotionRatio11(pstVpssRegs, 0x0, mean_motion_ratio11);
    VPSS_Sys_SetMeanMotionRatio10(pstVpssRegs, 0x0, mean_motion_ratio10);
    VPSS_Sys_SetMeanMotionRatio9(pstVpssRegs, 0x0, mean_motion_ratio9);
    VPSS_Sys_SetMeanMotionRatio8(pstVpssRegs, 0x0, mean_motion_ratio8);
    VPSS_Sys_SetMeanMotionRatio15(pstVpssRegs, 0x0, mean_motion_ratio15);
    VPSS_Sys_SetMeanMotionRatio14(pstVpssRegs, 0x0, mean_motion_ratio14);
    VPSS_Sys_SetMeanMotionRatio13(pstVpssRegs, 0x0, mean_motion_ratio13);
    VPSS_Sys_SetMeanMotionRatio12(pstVpssRegs, 0x0, mean_motion_ratio12);
    VPSS_Sys_SetYblendingalphalut3(pstVpssRegs, 0x0, yblendingalphalut3);
    VPSS_Sys_SetYblendingalphalut2(pstVpssRegs, 0x0, yblendingalphalut2);
    VPSS_Sys_SetYblendingalphalut1(pstVpssRegs, 0x0, yblendingalphalut1);
    VPSS_Sys_SetYblendingalphalut0(pstVpssRegs, 0x0, yblendingalphalut0);
    VPSS_Sys_SetYblendingalphalut7(pstVpssRegs, 0x0, yblendingalphalut7);
    VPSS_Sys_SetYblendingalphalut6(pstVpssRegs, 0x0, yblendingalphalut6);
    VPSS_Sys_SetYblendingalphalut5(pstVpssRegs, 0x0, yblendingalphalut5);
    VPSS_Sys_SetYblendingalphalut4(pstVpssRegs, 0x0, yblendingalphalut4);
    VPSS_Sys_SetYblendingalphalut11(pstVpssRegs, 0x0, yblendingalphalut11);
    VPSS_Sys_SetYblendingalphalut10(pstVpssRegs, 0x0, yblendingalphalut10);
    VPSS_Sys_SetYblendingalphalut9(pstVpssRegs, 0x0, yblendingalphalut9);
    VPSS_Sys_SetYblendingalphalut8(pstVpssRegs, 0x0, yblendingalphalut8);
    VPSS_Sys_SetYblendingalphalut15(pstVpssRegs, 0x0, yblendingalphalut15);
    VPSS_Sys_SetYblendingalphalut14(pstVpssRegs, 0x0, yblendingalphalut14);
    VPSS_Sys_SetYblendingalphalut13(pstVpssRegs, 0x0, yblendingalphalut13);
    VPSS_Sys_SetYblendingalphalut12(pstVpssRegs, 0x0, yblendingalphalut12);
    VPSS_Sys_SetYblendingalphalut19(pstVpssRegs, 0x0, yblendingalphalut19);
    VPSS_Sys_SetYblendingalphalut18(pstVpssRegs, 0x0, yblendingalphalut18);
    VPSS_Sys_SetYblendingalphalut17(pstVpssRegs, 0x0, yblendingalphalut17);
    VPSS_Sys_SetYblendingalphalut16(pstVpssRegs, 0x0, yblendingalphalut16);
    VPSS_Sys_SetYblendingalphalut23(pstVpssRegs, 0x0, yblendingalphalut23);
    VPSS_Sys_SetYblendingalphalut22(pstVpssRegs, 0x0, yblendingalphalut22);
    VPSS_Sys_SetYblendingalphalut21(pstVpssRegs, 0x0, yblendingalphalut21);
    VPSS_Sys_SetYblendingalphalut20(pstVpssRegs, 0x0, yblendingalphalut20);
    VPSS_Sys_SetYblendingalphalut27(pstVpssRegs, 0x0, yblendingalphalut27);
    VPSS_Sys_SetYblendingalphalut26(pstVpssRegs, 0x0, yblendingalphalut26);
    VPSS_Sys_SetYblendingalphalut25(pstVpssRegs, 0x0, yblendingalphalut25);
    VPSS_Sys_SetYblendingalphalut24(pstVpssRegs, 0x0, yblendingalphalut24);
    VPSS_Sys_SetYblendingalphalut31(pstVpssRegs, 0x0, yblendingalphalut31);
    VPSS_Sys_SetYblendingalphalut30(pstVpssRegs, 0x0, yblendingalphalut30);
    VPSS_Sys_SetYblendingalphalut29(pstVpssRegs, 0x0, yblendingalphalut29);
    VPSS_Sys_SetYblendingalphalut28(pstVpssRegs, 0x0, yblendingalphalut28);
    VPSS_Sys_SetCblendingalphalut3(pstVpssRegs, 0x0, cblendingalphalut3);
    VPSS_Sys_SetCblendingalphalut2(pstVpssRegs, 0x0, cblendingalphalut2);
    VPSS_Sys_SetCblendingalphalut1(pstVpssRegs, 0x0, cblendingalphalut1);
    VPSS_Sys_SetCblendingalphalut0(pstVpssRegs, 0x0, cblendingalphalut0);
    VPSS_Sys_SetCblendingalphalut7(pstVpssRegs, 0x0, cblendingalphalut7);
    VPSS_Sys_SetCblendingalphalut6(pstVpssRegs, 0x0, cblendingalphalut6);
    VPSS_Sys_SetCblendingalphalut5(pstVpssRegs, 0x0, cblendingalphalut5);
    VPSS_Sys_SetCblendingalphalut4(pstVpssRegs, 0x0, cblendingalphalut4);
    VPSS_Sys_SetCblendingalphalut11(pstVpssRegs, 0x0, cblendingalphalut11);
    VPSS_Sys_SetCblendingalphalut10(pstVpssRegs, 0x0, cblendingalphalut10);
    VPSS_Sys_SetCblendingalphalut9(pstVpssRegs, 0x0, cblendingalphalut9);
    VPSS_Sys_SetCblendingalphalut8(pstVpssRegs, 0x0, cblendingalphalut8);
    VPSS_Sys_SetCblendingalphalut15(pstVpssRegs, 0x0, cblendingalphalut15);
    VPSS_Sys_SetCblendingalphalut14(pstVpssRegs, 0x0, cblendingalphalut14);
    VPSS_Sys_SetCblendingalphalut13(pstVpssRegs, 0x0, cblendingalphalut13);
    VPSS_Sys_SetCblendingalphalut12(pstVpssRegs, 0x0, cblendingalphalut12);
    VPSS_Sys_SetCblendingalphalut19(pstVpssRegs, 0x0, cblendingalphalut19);
    VPSS_Sys_SetCblendingalphalut18(pstVpssRegs, 0x0, cblendingalphalut18);
    VPSS_Sys_SetCblendingalphalut17(pstVpssRegs, 0x0, cblendingalphalut17);
    VPSS_Sys_SetCblendingalphalut16(pstVpssRegs, 0x0, cblendingalphalut16);
    VPSS_Sys_SetCblendingalphalut23(pstVpssRegs, 0x0, cblendingalphalut23);
    VPSS_Sys_SetCblendingalphalut22(pstVpssRegs, 0x0, cblendingalphalut22);
    VPSS_Sys_SetCblendingalphalut21(pstVpssRegs, 0x0, cblendingalphalut21);
    VPSS_Sys_SetCblendingalphalut20(pstVpssRegs, 0x0, cblendingalphalut20);
    VPSS_Sys_SetCblendingalphalut27(pstVpssRegs, 0x0, cblendingalphalut27);
    VPSS_Sys_SetCblendingalphalut26(pstVpssRegs, 0x0, cblendingalphalut26);
    VPSS_Sys_SetCblendingalphalut25(pstVpssRegs, 0x0, cblendingalphalut25);
    VPSS_Sys_SetCblendingalphalut24(pstVpssRegs, 0x0, cblendingalphalut24);
    VPSS_Sys_SetCblendingalphalut31(pstVpssRegs, 0x0, cblendingalphalut31);
    VPSS_Sys_SetCblendingalphalut30(pstVpssRegs, 0x0, cblendingalphalut30);
    VPSS_Sys_SetCblendingalphalut29(pstVpssRegs, 0x0, cblendingalphalut29);
    VPSS_Sys_SetCblendingalphalut28(pstVpssRegs, 0x0, cblendingalphalut28);
#if 0
    VPSS_Sys_SetYmotionstrlut3(pstVpssRegs, ymotionstrlut3);
    VPSS_Sys_SetYmotionstrlut2(pstVpssRegs, ymotionstrlut2);
    VPSS_Sys_SetYmotionstrlut1(pstVpssRegs, ymotionstrlut1);
    VPSS_Sys_SetYmotionstrlut0(pstVpssRegs, ymotionstrlut0);
    VPSS_Sys_SetYmotionstrlut7(pstVpssRegs, ymotionstrlut7);
    VPSS_Sys_SetYmotionstrlut6(pstVpssRegs, ymotionstrlut6);
    VPSS_Sys_SetYmotionstrlut5(pstVpssRegs, ymotionstrlut5);
    VPSS_Sys_SetYmotionstrlut4(pstVpssRegs, ymotionstrlut4);
    VPSS_Sys_SetYmotionstrlut11(pstVpssRegs, ymotionstrlut11);
    VPSS_Sys_SetYmotionstrlut10(pstVpssRegs, ymotionstrlut10);
    VPSS_Sys_SetYmotionstrlut9(pstVpssRegs, ymotionstrlut9);
    VPSS_Sys_SetYmotionstrlut8(pstVpssRegs, ymotionstrlut8);
    VPSS_Sys_SetYmotionstrlut15(pstVpssRegs, ymotionstrlut15);
    VPSS_Sys_SetYmotionstrlut14(pstVpssRegs, ymotionstrlut14);
    VPSS_Sys_SetYmotionstrlut13(pstVpssRegs, ymotionstrlut13);
    VPSS_Sys_SetYmotionstrlut12(pstVpssRegs, ymotionstrlut12);
    VPSS_Sys_SetYmotionstrlut19(pstVpssRegs, ymotionstrlut19);
    VPSS_Sys_SetYmotionstrlut18(pstVpssRegs, ymotionstrlut18);
    VPSS_Sys_SetYmotionstrlut17(pstVpssRegs, ymotionstrlut17);
    VPSS_Sys_SetYmotionstrlut16(pstVpssRegs, ymotionstrlut16);
    VPSS_Sys_SetYmotionstrlut23(pstVpssRegs, ymotionstrlut23);
    VPSS_Sys_SetYmotionstrlut22(pstVpssRegs, ymotionstrlut22);
    VPSS_Sys_SetYmotionstrlut21(pstVpssRegs, ymotionstrlut21);
    VPSS_Sys_SetYmotionstrlut20(pstVpssRegs, ymotionstrlut20);
    VPSS_Sys_SetYmotionstrlut27(pstVpssRegs, ymotionstrlut27);
    VPSS_Sys_SetYmotionstrlut26(pstVpssRegs, ymotionstrlut26);
    VPSS_Sys_SetYmotionstrlut25(pstVpssRegs, ymotionstrlut25);
    VPSS_Sys_SetYmotionstrlut24(pstVpssRegs, ymotionstrlut24);
    VPSS_Sys_SetYmotionstrlut31(pstVpssRegs, ymotionstrlut31);
    VPSS_Sys_SetYmotionstrlut30(pstVpssRegs, ymotionstrlut30);
    VPSS_Sys_SetYmotionstrlut29(pstVpssRegs, ymotionstrlut29);
    VPSS_Sys_SetYmotionstrlut28(pstVpssRegs, ymotionstrlut28);
    VPSS_Sys_SetYmotionstrlut35(pstVpssRegs, ymotionstrlut35);
    VPSS_Sys_SetYmotionstrlut34(pstVpssRegs, ymotionstrlut34);
    VPSS_Sys_SetYmotionstrlut33(pstVpssRegs, ymotionstrlut33);
    VPSS_Sys_SetYmotionstrlut32(pstVpssRegs, ymotionstrlut32);
    VPSS_Sys_SetYmotionstrlut39(pstVpssRegs, ymotionstrlut39);
    VPSS_Sys_SetYmotionstrlut38(pstVpssRegs, ymotionstrlut38);
    VPSS_Sys_SetYmotionstrlut37(pstVpssRegs, ymotionstrlut37);
    VPSS_Sys_SetYmotionstrlut36(pstVpssRegs, ymotionstrlut36);
    VPSS_Sys_SetYmotionstrlut43(pstVpssRegs, ymotionstrlut43);
    VPSS_Sys_SetYmotionstrlut42(pstVpssRegs, ymotionstrlut42);
    VPSS_Sys_SetYmotionstrlut41(pstVpssRegs, ymotionstrlut41);
    VPSS_Sys_SetYmotionstrlut40(pstVpssRegs, ymotionstrlut40);
    VPSS_Sys_SetYmotionstrlut47(pstVpssRegs, ymotionstrlut47);
    VPSS_Sys_SetYmotionstrlut46(pstVpssRegs, ymotionstrlut46);
    VPSS_Sys_SetYmotionstrlut45(pstVpssRegs, ymotionstrlut45);
    VPSS_Sys_SetYmotionstrlut44(pstVpssRegs, ymotionstrlut44);
    VPSS_Sys_SetYmotionstrlut51(pstVpssRegs, ymotionstrlut51);
    VPSS_Sys_SetYmotionstrlut50(pstVpssRegs, ymotionstrlut50);
    VPSS_Sys_SetYmotionstrlut49(pstVpssRegs, ymotionstrlut49);
    VPSS_Sys_SetYmotionstrlut48(pstVpssRegs, ymotionstrlut48);
    VPSS_Sys_SetYmotionstrlut55(pstVpssRegs, ymotionstrlut55);
    VPSS_Sys_SetYmotionstrlut54(pstVpssRegs, ymotionstrlut54);
    VPSS_Sys_SetYmotionstrlut53(pstVpssRegs, ymotionstrlut53);
    VPSS_Sys_SetYmotionstrlut52(pstVpssRegs, ymotionstrlut52);
    VPSS_Sys_SetYmotionstrlut59(pstVpssRegs, ymotionstrlut59);
    VPSS_Sys_SetYmotionstrlut58(pstVpssRegs, ymotionstrlut58);
    VPSS_Sys_SetYmotionstrlut57(pstVpssRegs, ymotionstrlut57);
    VPSS_Sys_SetYmotionstrlut56(pstVpssRegs, ymotionstrlut56);
    VPSS_Sys_SetYmotionstrlut63(pstVpssRegs, ymotionstrlut63);
    VPSS_Sys_SetYmotionstrlut62(pstVpssRegs, ymotionstrlut62);
    VPSS_Sys_SetYmotionstrlut61(pstVpssRegs, ymotionstrlut61);
    VPSS_Sys_SetYmotionstrlut60(pstVpssRegs, ymotionstrlut60);
    VPSS_Sys_SetYmotionstrlut67(pstVpssRegs, ymotionstrlut67);
    VPSS_Sys_SetYmotionstrlut66(pstVpssRegs, ymotionstrlut66);
    VPSS_Sys_SetYmotionstrlut65(pstVpssRegs, ymotionstrlut65);
    VPSS_Sys_SetYmotionstrlut64(pstVpssRegs, ymotionstrlut64);
    VPSS_Sys_SetYmotionstrlut71(pstVpssRegs, ymotionstrlut71);
    VPSS_Sys_SetYmotionstrlut70(pstVpssRegs, ymotionstrlut70);
    VPSS_Sys_SetYmotionstrlut69(pstVpssRegs, ymotionstrlut69);
    VPSS_Sys_SetYmotionstrlut68(pstVpssRegs, ymotionstrlut68);
    VPSS_Sys_SetYmotionstrlut75(pstVpssRegs, ymotionstrlut75);
    VPSS_Sys_SetYmotionstrlut74(pstVpssRegs, ymotionstrlut74);
    VPSS_Sys_SetYmotionstrlut73(pstVpssRegs, ymotionstrlut73);
    VPSS_Sys_SetYmotionstrlut72(pstVpssRegs, ymotionstrlut72);
    VPSS_Sys_SetYmotionstrlut79(pstVpssRegs, ymotionstrlut79);
    VPSS_Sys_SetYmotionstrlut78(pstVpssRegs, ymotionstrlut78);
    VPSS_Sys_SetYmotionstrlut77(pstVpssRegs, ymotionstrlut77);
    VPSS_Sys_SetYmotionstrlut76(pstVpssRegs, ymotionstrlut76);
    VPSS_Sys_SetYmotionstrlut83(pstVpssRegs, ymotionstrlut83);
    VPSS_Sys_SetYmotionstrlut82(pstVpssRegs, ymotionstrlut82);
    VPSS_Sys_SetYmotionstrlut81(pstVpssRegs, ymotionstrlut81);
    VPSS_Sys_SetYmotionstrlut80(pstVpssRegs, ymotionstrlut80);
    VPSS_Sys_SetYmotionstrlut87(pstVpssRegs, ymotionstrlut87);
    VPSS_Sys_SetYmotionstrlut86(pstVpssRegs, ymotionstrlut86);
    VPSS_Sys_SetYmotionstrlut85(pstVpssRegs, ymotionstrlut85);
    VPSS_Sys_SetYmotionstrlut84(pstVpssRegs, ymotionstrlut84);
    VPSS_Sys_SetYmotionstrlut91(pstVpssRegs, ymotionstrlut91);
    VPSS_Sys_SetYmotionstrlut90(pstVpssRegs, ymotionstrlut90);
    VPSS_Sys_SetYmotionstrlut89(pstVpssRegs, ymotionstrlut89);
    VPSS_Sys_SetYmotionstrlut88(pstVpssRegs, ymotionstrlut88);
    VPSS_Sys_SetYmotionstrlut95(pstVpssRegs, ymotionstrlut95);
    VPSS_Sys_SetYmotionstrlut94(pstVpssRegs, ymotionstrlut94);
    VPSS_Sys_SetYmotionstrlut93(pstVpssRegs, ymotionstrlut93);
    VPSS_Sys_SetYmotionstrlut92(pstVpssRegs, ymotionstrlut92);
    VPSS_Sys_SetYmotionstrlut99(pstVpssRegs, ymotionstrlut99);
    VPSS_Sys_SetYmotionstrlut98(pstVpssRegs, ymotionstrlut98);
    VPSS_Sys_SetYmotionstrlut97(pstVpssRegs, ymotionstrlut97);
    VPSS_Sys_SetYmotionstrlut96(pstVpssRegs, ymotionstrlut96);
    VPSS_Sys_SetYmotionstrlut103(pstVpssRegs, ymotionstrlut103);
    VPSS_Sys_SetYmotionstrlut102(pstVpssRegs, ymotionstrlut102);
    VPSS_Sys_SetYmotionstrlut101(pstVpssRegs, ymotionstrlut101);
    VPSS_Sys_SetYmotionstrlut100(pstVpssRegs, ymotionstrlut100);
    VPSS_Sys_SetYmotionstrlut107(pstVpssRegs, ymotionstrlut107);
    VPSS_Sys_SetYmotionstrlut106(pstVpssRegs, ymotionstrlut106);
    VPSS_Sys_SetYmotionstrlut105(pstVpssRegs, ymotionstrlut105);
    VPSS_Sys_SetYmotionstrlut104(pstVpssRegs, ymotionstrlut104);
    VPSS_Sys_SetYmotionstrlut111(pstVpssRegs, ymotionstrlut111);
    VPSS_Sys_SetYmotionstrlut110(pstVpssRegs, ymotionstrlut110);
    VPSS_Sys_SetYmotionstrlut109(pstVpssRegs, ymotionstrlut109);
    VPSS_Sys_SetYmotionstrlut108(pstVpssRegs, ymotionstrlut108);
    VPSS_Sys_SetYmotionstrlut115(pstVpssRegs, ymotionstrlut115);
    VPSS_Sys_SetYmotionstrlut114(pstVpssRegs, ymotionstrlut114);
    VPSS_Sys_SetYmotionstrlut113(pstVpssRegs, ymotionstrlut113);
    VPSS_Sys_SetYmotionstrlut112(pstVpssRegs, ymotionstrlut112);
    VPSS_Sys_SetYmotionstrlut119(pstVpssRegs, ymotionstrlut119);
    VPSS_Sys_SetYmotionstrlut118(pstVpssRegs, ymotionstrlut118);
    VPSS_Sys_SetYmotionstrlut117(pstVpssRegs, ymotionstrlut117);
    VPSS_Sys_SetYmotionstrlut116(pstVpssRegs, ymotionstrlut116);
    VPSS_Sys_SetYmotionstrlut123(pstVpssRegs, ymotionstrlut123);
    VPSS_Sys_SetYmotionstrlut122(pstVpssRegs, ymotionstrlut122);
    VPSS_Sys_SetYmotionstrlut121(pstVpssRegs, ymotionstrlut121);
    VPSS_Sys_SetYmotionstrlut120(pstVpssRegs, ymotionstrlut120);
    VPSS_Sys_SetYmotionstrlut127(pstVpssRegs, ymotionstrlut127);
    VPSS_Sys_SetYmotionstrlut126(pstVpssRegs, ymotionstrlut126);
    VPSS_Sys_SetYmotionstrlut125(pstVpssRegs, ymotionstrlut125);
    VPSS_Sys_SetYmotionstrlut124(pstVpssRegs, ymotionstrlut124);
    VPSS_Sys_SetCmotionstrlut3(pstVpssRegs, cmotionstrlut3);
    VPSS_Sys_SetCmotionstrlut2(pstVpssRegs, cmotionstrlut2);
    VPSS_Sys_SetCmotionstrlut1(pstVpssRegs, cmotionstrlut1);
    VPSS_Sys_SetCmotionstrlut0(pstVpssRegs, cmotionstrlut0);
    VPSS_Sys_SetCmotionstrlut7(pstVpssRegs, cmotionstrlut7);
    VPSS_Sys_SetCmotionstrlut6(pstVpssRegs, cmotionstrlut6);
    VPSS_Sys_SetCmotionstrlut5(pstVpssRegs, cmotionstrlut5);
    VPSS_Sys_SetCmotionstrlut4(pstVpssRegs, cmotionstrlut4);
    VPSS_Sys_SetCmotionstrlut11(pstVpssRegs, cmotionstrlut11);
    VPSS_Sys_SetCmotionstrlut10(pstVpssRegs, cmotionstrlut10);
    VPSS_Sys_SetCmotionstrlut9(pstVpssRegs, cmotionstrlut9);
    VPSS_Sys_SetCmotionstrlut8(pstVpssRegs, cmotionstrlut8);
    VPSS_Sys_SetCmotionstrlut15(pstVpssRegs, cmotionstrlut15);
    VPSS_Sys_SetCmotionstrlut14(pstVpssRegs, cmotionstrlut14);
    VPSS_Sys_SetCmotionstrlut13(pstVpssRegs, cmotionstrlut13);
    VPSS_Sys_SetCmotionstrlut12(pstVpssRegs, cmotionstrlut12);
    VPSS_Sys_SetCmotionstrlut19(pstVpssRegs, cmotionstrlut19);
    VPSS_Sys_SetCmotionstrlut18(pstVpssRegs, cmotionstrlut18);
    VPSS_Sys_SetCmotionstrlut17(pstVpssRegs, cmotionstrlut17);
    VPSS_Sys_SetCmotionstrlut16(pstVpssRegs, cmotionstrlut16);
    VPSS_Sys_SetCmotionstrlut23(pstVpssRegs, cmotionstrlut23);
    VPSS_Sys_SetCmotionstrlut22(pstVpssRegs, cmotionstrlut22);
    VPSS_Sys_SetCmotionstrlut21(pstVpssRegs, cmotionstrlut21);
    VPSS_Sys_SetCmotionstrlut20(pstVpssRegs, cmotionstrlut20);
    VPSS_Sys_SetCmotionstrlut27(pstVpssRegs, cmotionstrlut27);
    VPSS_Sys_SetCmotionstrlut26(pstVpssRegs, cmotionstrlut26);
    VPSS_Sys_SetCmotionstrlut25(pstVpssRegs, cmotionstrlut25);
    VPSS_Sys_SetCmotionstrlut24(pstVpssRegs, cmotionstrlut24);
    VPSS_Sys_SetCmotionstrlut31(pstVpssRegs, cmotionstrlut31);
    VPSS_Sys_SetCmotionstrlut30(pstVpssRegs, cmotionstrlut30);
    VPSS_Sys_SetCmotionstrlut29(pstVpssRegs, cmotionstrlut29);
    VPSS_Sys_SetCmotionstrlut28(pstVpssRegs, cmotionstrlut28);
    VPSS_Sys_SetCmotionstrlut35(pstVpssRegs, cmotionstrlut35);
    VPSS_Sys_SetCmotionstrlut34(pstVpssRegs, cmotionstrlut34);
    VPSS_Sys_SetCmotionstrlut33(pstVpssRegs, cmotionstrlut33);
    VPSS_Sys_SetCmotionstrlut32(pstVpssRegs, cmotionstrlut32);
    VPSS_Sys_SetCmotionstrlut39(pstVpssRegs, cmotionstrlut39);
    VPSS_Sys_SetCmotionstrlut38(pstVpssRegs, cmotionstrlut38);
    VPSS_Sys_SetCmotionstrlut37(pstVpssRegs, cmotionstrlut37);
    VPSS_Sys_SetCmotionstrlut36(pstVpssRegs, cmotionstrlut36);
    VPSS_Sys_SetCmotionstrlut43(pstVpssRegs, cmotionstrlut43);
    VPSS_Sys_SetCmotionstrlut42(pstVpssRegs, cmotionstrlut42);
    VPSS_Sys_SetCmotionstrlut41(pstVpssRegs, cmotionstrlut41);
    VPSS_Sys_SetCmotionstrlut40(pstVpssRegs, cmotionstrlut40);
    VPSS_Sys_SetCmotionstrlut47(pstVpssRegs, cmotionstrlut47);
    VPSS_Sys_SetCmotionstrlut46(pstVpssRegs, cmotionstrlut46);
    VPSS_Sys_SetCmotionstrlut45(pstVpssRegs, cmotionstrlut45);
    VPSS_Sys_SetCmotionstrlut44(pstVpssRegs, cmotionstrlut44);
    VPSS_Sys_SetCmotionstrlut51(pstVpssRegs, cmotionstrlut51);
    VPSS_Sys_SetCmotionstrlut50(pstVpssRegs, cmotionstrlut50);
    VPSS_Sys_SetCmotionstrlut49(pstVpssRegs, cmotionstrlut49);
    VPSS_Sys_SetCmotionstrlut48(pstVpssRegs, cmotionstrlut48);
    VPSS_Sys_SetCmotionstrlut55(pstVpssRegs, cmotionstrlut55);
    VPSS_Sys_SetCmotionstrlut54(pstVpssRegs, cmotionstrlut54);
    VPSS_Sys_SetCmotionstrlut53(pstVpssRegs, cmotionstrlut53);
    VPSS_Sys_SetCmotionstrlut52(pstVpssRegs, cmotionstrlut52);
    VPSS_Sys_SetCmotionstrlut59(pstVpssRegs, cmotionstrlut59);
    VPSS_Sys_SetCmotionstrlut58(pstVpssRegs, cmotionstrlut58);
    VPSS_Sys_SetCmotionstrlut57(pstVpssRegs, cmotionstrlut57);
    VPSS_Sys_SetCmotionstrlut56(pstVpssRegs, cmotionstrlut56);
    VPSS_Sys_SetCmotionstrlut63(pstVpssRegs, cmotionstrlut63);
    VPSS_Sys_SetCmotionstrlut62(pstVpssRegs, cmotionstrlut62);
    VPSS_Sys_SetCmotionstrlut61(pstVpssRegs, cmotionstrlut61);
    VPSS_Sys_SetCmotionstrlut60(pstVpssRegs, cmotionstrlut60);
    VPSS_Sys_SetCmotionstrlut67(pstVpssRegs, cmotionstrlut67);
    VPSS_Sys_SetCmotionstrlut66(pstVpssRegs, cmotionstrlut66);
    VPSS_Sys_SetCmotionstrlut65(pstVpssRegs, cmotionstrlut65);
    VPSS_Sys_SetCmotionstrlut64(pstVpssRegs, cmotionstrlut64);
    VPSS_Sys_SetCmotionstrlut71(pstVpssRegs, cmotionstrlut71);
    VPSS_Sys_SetCmotionstrlut70(pstVpssRegs, cmotionstrlut70);
    VPSS_Sys_SetCmotionstrlut69(pstVpssRegs, cmotionstrlut69);
    VPSS_Sys_SetCmotionstrlut68(pstVpssRegs, cmotionstrlut68);
    VPSS_Sys_SetCmotionstrlut75(pstVpssRegs, cmotionstrlut75);
    VPSS_Sys_SetCmotionstrlut74(pstVpssRegs, cmotionstrlut74);
    VPSS_Sys_SetCmotionstrlut73(pstVpssRegs, cmotionstrlut73);
    VPSS_Sys_SetCmotionstrlut72(pstVpssRegs, cmotionstrlut72);
    VPSS_Sys_SetCmotionstrlut79(pstVpssRegs, cmotionstrlut79);
    VPSS_Sys_SetCmotionstrlut78(pstVpssRegs, cmotionstrlut78);
    VPSS_Sys_SetCmotionstrlut77(pstVpssRegs, cmotionstrlut77);
    VPSS_Sys_SetCmotionstrlut76(pstVpssRegs, cmotionstrlut76);
    VPSS_Sys_SetCmotionstrlut83(pstVpssRegs, cmotionstrlut83);
    VPSS_Sys_SetCmotionstrlut82(pstVpssRegs, cmotionstrlut82);
    VPSS_Sys_SetCmotionstrlut81(pstVpssRegs, cmotionstrlut81);
    VPSS_Sys_SetCmotionstrlut80(pstVpssRegs, cmotionstrlut80);
    VPSS_Sys_SetCmotionstrlut87(pstVpssRegs, cmotionstrlut87);
    VPSS_Sys_SetCmotionstrlut86(pstVpssRegs, cmotionstrlut86);
    VPSS_Sys_SetCmotionstrlut85(pstVpssRegs, cmotionstrlut85);
    VPSS_Sys_SetCmotionstrlut84(pstVpssRegs, cmotionstrlut84);
    VPSS_Sys_SetCmotionstrlut91(pstVpssRegs, cmotionstrlut91);
    VPSS_Sys_SetCmotionstrlut90(pstVpssRegs, cmotionstrlut90);
    VPSS_Sys_SetCmotionstrlut89(pstVpssRegs, cmotionstrlut89);
    VPSS_Sys_SetCmotionstrlut88(pstVpssRegs, cmotionstrlut88);
    VPSS_Sys_SetCmotionstrlut95(pstVpssRegs, cmotionstrlut95);
    VPSS_Sys_SetCmotionstrlut94(pstVpssRegs, cmotionstrlut94);
    VPSS_Sys_SetCmotionstrlut93(pstVpssRegs, cmotionstrlut93);
    VPSS_Sys_SetCmotionstrlut92(pstVpssRegs, cmotionstrlut92);
    VPSS_Sys_SetCmotionstrlut99(pstVpssRegs, cmotionstrlut99);
    VPSS_Sys_SetCmotionstrlut98(pstVpssRegs, cmotionstrlut98);
    VPSS_Sys_SetCmotionstrlut97(pstVpssRegs, cmotionstrlut97);
    VPSS_Sys_SetCmotionstrlut96(pstVpssRegs, cmotionstrlut96);
    VPSS_Sys_SetCmotionstrlut103(pstVpssRegs, cmotionstrlut103);
    VPSS_Sys_SetCmotionstrlut102(pstVpssRegs, cmotionstrlut102);
    VPSS_Sys_SetCmotionstrlut101(pstVpssRegs, cmotionstrlut101);
    VPSS_Sys_SetCmotionstrlut100(pstVpssRegs, cmotionstrlut100);
    VPSS_Sys_SetCmotionstrlut107(pstVpssRegs, cmotionstrlut107);
    VPSS_Sys_SetCmotionstrlut106(pstVpssRegs, cmotionstrlut106);
    VPSS_Sys_SetCmotionstrlut105(pstVpssRegs, cmotionstrlut105);
    VPSS_Sys_SetCmotionstrlut104(pstVpssRegs, cmotionstrlut104);
    VPSS_Sys_SetCmotionstrlut111(pstVpssRegs, cmotionstrlut111);
    VPSS_Sys_SetCmotionstrlut110(pstVpssRegs, cmotionstrlut110);
    VPSS_Sys_SetCmotionstrlut109(pstVpssRegs, cmotionstrlut109);
    VPSS_Sys_SetCmotionstrlut108(pstVpssRegs, cmotionstrlut108);
    VPSS_Sys_SetCmotionstrlut115(pstVpssRegs, cmotionstrlut115);
    VPSS_Sys_SetCmotionstrlut114(pstVpssRegs, cmotionstrlut114);
    VPSS_Sys_SetCmotionstrlut113(pstVpssRegs, cmotionstrlut113);
    VPSS_Sys_SetCmotionstrlut112(pstVpssRegs, cmotionstrlut112);
    VPSS_Sys_SetCmotionstrlut119(pstVpssRegs, cmotionstrlut119);
    VPSS_Sys_SetCmotionstrlut118(pstVpssRegs, cmotionstrlut118);
    VPSS_Sys_SetCmotionstrlut117(pstVpssRegs, cmotionstrlut117);
    VPSS_Sys_SetCmotionstrlut116(pstVpssRegs, cmotionstrlut116);
    VPSS_Sys_SetCmotionstrlut123(pstVpssRegs, cmotionstrlut123);
    VPSS_Sys_SetCmotionstrlut122(pstVpssRegs, cmotionstrlut122);
    VPSS_Sys_SetCmotionstrlut121(pstVpssRegs, cmotionstrlut121);
    VPSS_Sys_SetCmotionstrlut120(pstVpssRegs, cmotionstrlut120);
    VPSS_Sys_SetCmotionstrlut127(pstVpssRegs, cmotionstrlut127);
    VPSS_Sys_SetCmotionstrlut126(pstVpssRegs, cmotionstrlut126);
    VPSS_Sys_SetCmotionstrlut125(pstVpssRegs, cmotionstrlut125);
    VPSS_Sys_SetCmotionstrlut124(pstVpssRegs, cmotionstrlut124);
    ////mc
    VPSS_Die_SetKRgdifycore(pstVpssRegs, k_rgdifycore);
    VPSS_Die_SetGRgdifycore(pstVpssRegs, g_rgdifycore);
    VPSS_Die_SetCoreRgdify(pstVpssRegs, core_rgdify);
    VPSS_Die_SetLmtRgdify(pstVpssRegs, lmt_rgdify);
    VPSS_Die_SetCoefSadlpf(pstVpssRegs, coef_sadlpf);
    VPSS_Die_SetKmvRgsad(pstVpssRegs, kmv_rgsad);
    VPSS_Die_SetKTpdifRgsad(pstVpssRegs, k_tpdif_rgsad);
    VPSS_Die_SetGTpdifRgsad(pstVpssRegs, g_tpdif_rgsad);
    VPSS_Die_SetThmagRgmv(pstVpssRegs, thmag_rgmv);
    VPSS_Die_SetThSaddifRgmv(pstVpssRegs, th_saddif_rgmv);
    VPSS_Die_SetTh0mvsadRgmv(pstVpssRegs, th_0mvsad_rgmv);
    VPSS_Die_SetCoreMagRg(pstVpssRegs, core_mag_rg);
    VPSS_Die_SetLmtMagRg(pstVpssRegs, lmt_mag_rg);
    VPSS_Die_SetCoreMvRgmvls(pstVpssRegs, core_mv_rgmvls);
    VPSS_Die_SetKMvRgmvls(pstVpssRegs, k_mv_rgmvls);
    VPSS_Die_SetCoreMagRgmvls(pstVpssRegs, core_mag_rgmvls);
    VPSS_Die_SetKMagRgmvls(pstVpssRegs, k_mag_rgmvls);
    VPSS_Die_SetThMvadjRgmvls(pstVpssRegs, th_mvadj_rgmvls);
    VPSS_Die_SetEnMvadjRgmvls(pstVpssRegs, en_mvadj_rgmvls);
    VPSS_Die_SetKSadRgls(pstVpssRegs, k_sad_rgls);
    VPSS_Die_SetThMagRgls(pstVpssRegs, th_mag_rgls);
    VPSS_Die_SetThSadRgls(pstVpssRegs, th_sad_rgls);
    VPSS_Die_SetKSadcoreRgmv(pstVpssRegs, k_sadcore_rgmv);
    VPSS_Die_SetForceMven(pstVpssRegs, force_mven);
    VPSS_Die_SetForceMvx(pstVpssRegs, force_mvx);
    VPSS_Die_SetThBlkmvxMvdlt(pstVpssRegs, th_blkmvx_mvdlt);
    VPSS_Die_SetThRgmvxMvdlt(pstVpssRegs, th_rgmvx_mvdlt);
    VPSS_Die_SetThLsMvdlt(pstVpssRegs, th_ls_mvdlt);
    VPSS_Die_SetThVblkdistMvdlt(pstVpssRegs, th_vblkdist_mvdlt);
    VPSS_Die_SetThHblkdistMvdlt(pstVpssRegs, th_hblkdist_mvdlt);
    VPSS_Die_SetKSadcoreMvdlt(pstVpssRegs, k_sadcore_mvdlt);
    VPSS_Die_SetThMagMvdlt(pstVpssRegs, th_mag_mvdlt);
    VPSS_Die_SetGMagMvdlt(pstVpssRegs, g_mag_mvdlt);
    VPSS_Die_SetThlSadMvdlt(pstVpssRegs, thl_sad_mvdlt);
    VPSS_Die_SetThhSadMvdlt(pstVpssRegs, thh_sad_mvdlt);
    VPSS_Die_SetKRglsw(pstVpssRegs, k_rglsw);
    VPSS_Die_SetKSimimvw(pstVpssRegs, k_simimvw);
    VPSS_Die_SetGhCoreSimimv(pstVpssRegs, gh_core_simimv);
    VPSS_Die_SetGlCoreSimimv(pstVpssRegs, gl_core_simimv);
    VPSS_Die_SetKCoreSimimv(pstVpssRegs, k_core_simimv);
    VPSS_Die_SetKCoreVsaddif(pstVpssRegs, k_core_vsaddif);
    VPSS_Die_SetKRgsadadjMcw(pstVpssRegs, k_rgsadadj_mcw);
    VPSS_Die_SetCoreRgsadadjMcw(pstVpssRegs, core_rgsadadj_mcw);
    VPSS_Die_SetKMvyMcw(pstVpssRegs, k_mvy_mcw);
    VPSS_Die_SetCoreMvyMcw(pstVpssRegs, core_mvy_mcw);
    VPSS_Die_SetRgtbEnMcw(pstVpssRegs, rgtb_en_mcw);
    VPSS_Die_SetCoreRgmagMcw(pstVpssRegs, core_rgmag_mcw);
    VPSS_Die_SetModeRgysadMcw(pstVpssRegs, mode_rgysad_mcw);
    VPSS_Die_SetKVsaddifw(pstVpssRegs, k_vsaddifw);
    VPSS_Die_SetGhCoreVsadDif(pstVpssRegs, gh_core_vsad_dif);
    VPSS_Die_SetGlCoreVsaddif(pstVpssRegs, gl_core_vsaddif);
    VPSS_Die_SetG0RgmagMcw(pstVpssRegs, g0_rgmag_mcw);
    VPSS_Die_SetK0RgmagMcw(pstVpssRegs, k0_rgmag_mcw);
    VPSS_Die_SetX0RgmagMcw(pstVpssRegs, x0_rgmag_mcw);
    VPSS_Die_SetX0RgsadMcw(pstVpssRegs, x0_rgsad_mcw);
    VPSS_Die_SetCoreRgsadMcw(pstVpssRegs, core_rgsad_mcw);
    VPSS_Die_SetK1RgmagMcw(pstVpssRegs, k1_rgmag_mcw);
    VPSS_Die_SetK1RgsadMcw(pstVpssRegs, k1_rgsad_mcw);
    VPSS_Die_SetG0RgsadMcw(pstVpssRegs, g0_rgsad_mcw);
    VPSS_Die_SetK0RgsadMcw(pstVpssRegs, k0_rgsad_mcw);
    VPSS_Die_SetKRgsadMcw(pstVpssRegs, k_rgsad_mcw);
    VPSS_Die_SetXRgsadMcw(pstVpssRegs, x_rgsad_mcw);
    VPSS_Die_SetK0SmrgMcw(pstVpssRegs, k0_smrg_mcw);
    VPSS_Die_SetX0SmrgMcw(pstVpssRegs, x0_smrg_mcw);
    VPSS_Die_SetK1TpmvdistMcw(pstVpssRegs, k1_tpmvdist_mcw);
    VPSS_Die_SetG0TpmvdistMcw(pstVpssRegs, g0_tpmvdist_mcw);
    VPSS_Die_SetK0TpmvdistMcw(pstVpssRegs, k0_tpmvdist_mcw);
    VPSS_Die_SetX0TpmvdistMcw(pstVpssRegs, x0_tpmvdist_mcw);
    VPSS_Die_SetKCoreTpmvdistMcw(pstVpssRegs, k_core_tpmvdist_mcw);
    VPSS_Die_SetBCoreTpmvdistMcw(pstVpssRegs, b_core_tpmvdist_mcw);
    VPSS_Die_SetKAvgmvdistMcw(pstVpssRegs, k_avgmvdist_mcw);
    VPSS_Die_SetKMinmvdistMcw(pstVpssRegs, k_minmvdist_mcw);
    VPSS_Die_SetKTbdifMcw(pstVpssRegs, k_tbdif_mcw);
    VPSS_Die_SetK0MaxMagMcw(pstVpssRegs, k0_max_mag_mcw);
    VPSS_Die_SetK1MaxMagMcw(pstVpssRegs, k1_max_mag_mcw);
    VPSS_Die_SetKMaxDifMcw(pstVpssRegs, k_max_dif_mcw);
    VPSS_Die_SetKMaxCoreMcw(pstVpssRegs, k_max_core_mcw);
    VPSS_Die_SetKDifvcoreMcw(pstVpssRegs, k_difvcore_mcw);
    VPSS_Die_SetKDifhcoreMcw(pstVpssRegs, k_difhcore_mcw);
    VPSS_Die_SetK1MagWndMcw(pstVpssRegs, k1_mag_wnd_mcw);
    VPSS_Die_SetG0MagWndMcw(pstVpssRegs, g0_mag_wnd_mcw);
    VPSS_Die_SetK0MagWndMcw(pstVpssRegs, k0_mag_wnd_mcw);
    VPSS_Die_SetX0MagWndMcw(pstVpssRegs, x0_mag_wnd_mcw);
    VPSS_Die_SetKTbmagMcw(pstVpssRegs, k_tbmag_mcw);
    VPSS_Die_SetG0SadWndMcw(pstVpssRegs, g0_sad_wnd_mcw);
    VPSS_Die_SetK0SadWndMcw(pstVpssRegs, k0_sad_wnd_mcw);
    VPSS_Die_SetX0SadWndMcw(pstVpssRegs, x0_sad_wnd_mcw);
    VPSS_Die_SetG1MagWndMcw(pstVpssRegs, g1_mag_wnd_mcw);
    VPSS_Die_SetG1SadWndMcw(pstVpssRegs, g1_sad_wnd_mcw);
    VPSS_Die_SetK1SadWndMcw(pstVpssRegs, k1_sad_wnd_mcw);
    VPSS_Die_SetBHvdifDw(pstVpssRegs, b_hvdif_dw);
    VPSS_Die_SetBBhvdifDw(pstVpssRegs, b_bhvdif_dw);
    VPSS_Die_SetKBhvdifDw(pstVpssRegs, k_bhvdif_dw);
    VPSS_Die_SetCoreBhvdifDw(pstVpssRegs, core_bhvdif_dw);
    VPSS_Die_SetGainLpfDw(pstVpssRegs, gain_lpf_dw);
    VPSS_Die_SetKMaxHvdifDw(pstVpssRegs, k_max_hvdif_dw);
    VPSS_Die_SetBMvDw(pstVpssRegs, b_mv_dw);
    VPSS_Die_SetCoreMvDw(pstVpssRegs, core_mv_dw);
    VPSS_Die_SetKDifvDw(pstVpssRegs, k_difv_dw);
    VPSS_Die_SetCoreHvdifDw(pstVpssRegs, core_hvdif_dw);
    VPSS_Die_SetK1HvdifDw(pstVpssRegs, k1_hvdif_dw);
    VPSS_Die_SetG0HvdifDw(pstVpssRegs, g0_hvdif_dw);
    VPSS_Die_SetK0HvdifDw(pstVpssRegs, k0_hvdif_dw);
    VPSS_Die_SetX0HvdifDw(pstVpssRegs, x0_hvdif_dw);
    VPSS_Die_SetK1MvDw(pstVpssRegs, k1_mv_dw);
    VPSS_Die_SetG0MvDw(pstVpssRegs, g0_mv_dw);
    VPSS_Die_SetK0MvDw(pstVpssRegs, k0_mv_dw);
    VPSS_Die_SetX0MvDw(pstVpssRegs, x0_mv_dw);
    VPSS_Die_SetK1MtDw(pstVpssRegs, k1_mt_dw);
    VPSS_Die_SetG0MtDw(pstVpssRegs, g0_mt_dw);
    VPSS_Die_SetK0MtDw(pstVpssRegs, k0_mt_dw);
    VPSS_Die_SetX0MtDw(pstVpssRegs, x0_mt_dw);
    VPSS_Die_SetBMtDw(pstVpssRegs, b_mt_dw);
    VPSS_Die_SetK1MvMt(pstVpssRegs, k1_mv_mt);
    VPSS_Die_SetX0MvMt(pstVpssRegs, x0_mv_mt);
    VPSS_Die_SetG0MvMt(pstVpssRegs, g0_mv_mt);
    VPSS_Die_SetMclpfMode(pstVpssRegs, mclpf_mode);
    VPSS_Die_SetKPxlmagMcw(pstVpssRegs, k_pxlmag_mcw);
    VPSS_Die_SetXPxlmagMcw(pstVpssRegs, x_pxlmag_mcw);
    VPSS_Die_SetRsPxlmagMcw(pstVpssRegs, rs_pxlmag_mcw);
    VPSS_Die_SetGainMclpfh(pstVpssRegs, gain_mclpfh);
    VPSS_Die_SetGainDnMclpfv(pstVpssRegs, gain_dn_mclpfv);
    VPSS_Die_SetGainUpMclpfv(pstVpssRegs, gain_up_mclpfv);
    VPSS_Die_SetGPxlmagMcw(pstVpssRegs, g_pxlmag_mcw);
    VPSS_Die_SetKCVertw(pstVpssRegs, k_c_vertw);
    VPSS_Die_SetKYVertw(pstVpssRegs, k_y_vertw);
    VPSS_Die_SetKFstmtMc(pstVpssRegs, k_fstmt_mc);
    VPSS_Die_SetXFstmtMc(pstVpssRegs, x_fstmt_mc);
    VPSS_Die_SetK1MvMc(pstVpssRegs, k1_mv_mc);
    VPSS_Die_SetX0MvMc(pstVpssRegs, x0_mv_mc);
    VPSS_Die_SetBdvMcpos(pstVpssRegs, bdv_mcpos);
    VPSS_Die_SetBdhMcpos(pstVpssRegs, bdh_mcpos);
    VPSS_Die_SetKDelta(pstVpssRegs, k_delta);
    VPSS_Die_SetKHfcoreMc(pstVpssRegs, k_hfcore_mc);
    VPSS_Die_SetXHfcoreMc(pstVpssRegs, x_hfcore_mc);
    VPSS_Die_SetGSlmtMc(pstVpssRegs, g_slmt_mc);
    VPSS_Die_SetKSlmtMc(pstVpssRegs, k_slmt_mc);
    VPSS_Die_SetXSlmtMc(pstVpssRegs, x_slmt_mc);
    VPSS_Die_SetGFstmtMc(pstVpssRegs, g_fstmt_mc);
    VPSS_Die_SetR0Mc(pstVpssRegs, r0_mc);
    VPSS_Die_SetC0Mc(pstVpssRegs, c0_mc);
    VPSS_Die_SetGHfcoreMc(pstVpssRegs, g_hfcore_mc);
    VPSS_Die_SetMcmvrange(pstVpssRegs, mcmvrange);
    VPSS_Die_SetR1Mc(pstVpssRegs, r1_mc);
    VPSS_Die_SetC1Mc(pstVpssRegs, c1_mc);
    VPSS_Die_SetKFrcountMc(pstVpssRegs, k_frcount_mc);
    VPSS_Die_SetXFrcountMc(pstVpssRegs, x_frcount_mc);
    VPSS_Die_SetScenechangeMc(pstVpssRegs, scenechange_mc);
    VPSS_Die_SetMcendc(pstVpssRegs, mcendc);
    VPSS_Die_SetMcendr(pstVpssRegs, mcendr);
    VPSS_Die_SetMcstartc(pstVpssRegs, mcstartc);
    VPSS_Die_SetMcstartr(pstVpssRegs, mcstartr);
    VPSS_Die_SetMovegain(pstVpssRegs, movegain);
    VPSS_Die_SetMovecorig(pstVpssRegs, movecorig);
    VPSS_Die_SetMovethdl(pstVpssRegs, movethdl);
    VPSS_Die_SetMovethdh(pstVpssRegs, movethdh);
    VPSS_Die_SetMcNumtBlden(pstVpssRegs, mc_numt_blden);
    VPSS_Die_SetNumtGain(pstVpssRegs, numt_gain);
    VPSS_Die_SetNumtCoring(pstVpssRegs, numt_coring);
    VPSS_Die_SetNumtLpfEn(pstVpssRegs, numt_lpf_en);
    VPSS_Die_SetK1Hw(pstVpssRegs, k1_hw);
    VPSS_Die_SetK0Hw(pstVpssRegs, k0_hw);
    VPSS_Die_SetCoreHfvline(pstVpssRegs, core_hfvline);
    VPSS_Die_SetK1Hfvline(pstVpssRegs, k1_hfvline);
    VPSS_Die_SetK0Hfvline(pstVpssRegs, k0_hfvline);
    VPSS_Die_SetCoreRglsw(pstVpssRegs, core_rglsw);
    VPSS_Die_SetGDifcoreMcw(pstVpssRegs, g_difcore_mcw);
    VPSS_Die_SetSubpixMcEn(pstVpssRegs, subpix_mc_en);
    VPSS_Die_SetCore1Hw(pstVpssRegs, core1_hw);
    VPSS_Die_SetKCore0Hw(pstVpssRegs, k_core0_hw);
    VPSS_Die_SetBCore0Hw(pstVpssRegs, b_core0_hw);
    VPSS_Die_SetGHw(pstVpssRegs, g_hw);
    VPSS_Die_SetG0SadrWndMcw(pstVpssRegs, g0_sadr_wnd_mcw);
    VPSS_Die_SetK0SadrWndMcw(pstVpssRegs, k0_sadr_wnd_mcw);
    VPSS_Die_SetX0SadrWndMcw(pstVpssRegs, x0_sadr_wnd_mcw);
    VPSS_Die_SetRpK1SadWndMcw(pstVpssRegs, rp_k1_sad_wnd_mcw);
    VPSS_Die_SetRpK1MagWndMcw(pstVpssRegs, rp_k1_mag_wnd_mcw);
    VPSS_Die_SetThCurBlksad(pstVpssRegs, th_cur_blksad);
    VPSS_Die_SetKMcdifvMcw(pstVpssRegs, k_mcdifv_mcw);
    VPSS_Die_SetKP1cfdifhMcw(pstVpssRegs, k_p1cfdifh_mcw);
    VPSS_Die_SetG1SadrWndMcw(pstVpssRegs, g1_sadr_wnd_mcw);
    VPSS_Die_SetK1SadrWndMcw(pstVpssRegs, k1_sadr_wnd_mcw);
    VPSS_Die_SetThCurBlkmotion(pstVpssRegs, th_cur_blkmotion);
    VPSS_Die_SetThlNeighBlksad(pstVpssRegs, thl_neigh_blksad);
    VPSS_Die_SetThhNeighBlksad(pstVpssRegs, thh_neigh_blksad);
    VPSS_Die_SetRpDifmvxthRgmv(pstVpssRegs, rp_difmvxth_rgmv);
    VPSS_Die_SetRpMvxthRgmv(pstVpssRegs, rp_mvxth_rgmv);
    VPSS_Die_SetRpcounterth(pstVpssRegs, rpcounterth);
    VPSS_Die_SetKRpcounter(pstVpssRegs, k_rpcounter);
    VPSS_Die_SetBlkmvUpdateEn(pstVpssRegs, blkmv_update_en);
    VPSS_Die_SetThRgmvMag(pstVpssRegs, th_rgmv_mag);
    VPSS_Die_SetRpMagthRgmv(pstVpssRegs, rp_magth_rgmv);
    VPSS_Die_SetRpSadthRgmv(pstVpssRegs, rp_sadth_rgmv);
    VPSS_Die_SetRpDifsadthRgmv(pstVpssRegs, rp_difsadth_rgmv);
    VPSS_Die_SetSubmvSadchkEn(pstVpssRegs, submv_sadchk_en);
    VPSS_Die_SetRpEn(pstVpssRegs, rp_en);
    VPSS_Die_SetDifvtMode(pstVpssRegs, difvt_mode);
    VPSS_Die_SetK1TpdifRgsad(pstVpssRegs, k1_tpdif_rgsad);
    VPSS_Die_SetRpDifsadthTb(pstVpssRegs, rp_difsadth_tb);
    VPSS_Die_SetRpDifmvxthSp(pstVpssRegs, rp_difmvxth_sp);
#endif
    return ;
}

HI_VOID VPSS_SNR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_SNR_CFG_S *pstSnrCfg, VPSS_SNR_CHN_CFG_S *pstSnrChnCfg)
{
    HI_U32  u32Wth = pstSnrCfg->width;
    HI_U32  u32Hgt = pstSnrCfg->height;
    HI_U32  u32Pro = pstSnrCfg->pro;
    //HI_U32 u32Fmt = psSnrCfg->format;


    HI_U32 u32WthMad    = u32Wth;
    HI_U32 u32HgtMad    = u32Pro == 0 ? u32Hgt >> 1 : u32Hgt;

    u32HgtMad   = pstSnrCfg->mad_vfir_en ? u32HgtMad >> 1 : u32HgtMad;

    if (pstSnrCfg->mad_vfir_en == 1)
    {
        XDP_ASSERT(bPreFrmDeiEn[pstSnrCfg->i]);//pre frame dei en judge
    }

    if (pstSnrCfg->snr_en)
    {
        //snr mad
        pstSnrChnCfg->stInfoSnrMad.bEn         = HI_TRUE   ;
        pstSnrChnCfg->stInfoSnrMad.bSmmu_R     = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
        pstSnrChnCfg->stInfoSnrMad.u32Wth      = u32WthMad ;
        pstSnrChnCfg->stInfoSnrMad.u32Hgt      = u32HgtMad ;
        pstSnrChnCfg->stInfoSnrMad.u32Stride   = ((u32WthMad * 5 + 7) / 8 + 15) / 16 * 16 ;

        VPSS_InfoCfg_Snr_Mad(&pstSnrChnCfg->stInfoSnrMad, stRegAddr);
    }

    return ;
}

#if 0
HI_VOID VPSS_FUNC_SetSnrMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_SNR_CFG_S *pstCfg)
{
    HI_U32 in_width  = pstCfg->width;
    //HI_U32 in_height = pstCfg->height;
    //HI_U32 pro =pstCfg->pro;

    //unsigned int dbm_enable = 1;
    //unsigned int dbd_en        = (rand()%5==0)?0:1;
    unsigned int nr_en         = (rand() % 5 == 0) ? 0 : 1;
    unsigned int db_en         = (rand() % 5 == 0) ? 0 : 1;
    unsigned int dm_en         = (rand() % 5 == 0) ? 0 : 1;
    unsigned int db_lum_hor_en = (rand() % 5 == 0) ? 0 : 1;
    unsigned int det_hy_en     = (rand() % 5 == 0) ? 0 : 1;
    unsigned int dbm_demo_en   = (rand() % 5 == 0) ? 0 : 1;
    unsigned int dbm_demo_mode = rand() % 2;
    unsigned int dbm_demo_pos_x = 0;
    unsigned int dbm_out_mode  = rand() % 5; //0:IN; 1:Db; 2:Dm; 3:SNR; 4:All

    unsigned int l_width  = in_width;
    //unsigned int l_height = (pro==1)?in_height:in_height/2 ;

    //unsigned int c_width  = l_width  / 2 ;
    //unsigned int c_height = (pstCfg->format==XDP_PROC_FMT_SP_422) ? l_height : (l_height / 2) ;

    unsigned int l_width_1  = l_width  - 1 ;
    //unsigned int l_height_1 = l_height - 1 ;
    //unsigned int c_width_1  = c_width  - 1 ;
    //unsigned int c_height_1 = c_height - 1 ;

    // DB_BORDER_CFG
    unsigned int l_h_bs   = 4 + rand() % 61;

    unsigned int max_l_h_dist = 0;
    //unsigned int max_c_h_dist = 0;
    unsigned int i = 0;

    unsigned int j = 0;
    unsigned int l_h_blk_num = 0;
    //unsigned int l_v_blk_num = 0;
    //unsigned int c_h_blk_num = 0;
    unsigned int bd_stt = 0;
    unsigned int blk_sel = (rand() % 2);
    unsigned int blk_skip = 2 + (rand() % 6);


    unsigned int DbStr_Delta_LutLumHor[16] =  {rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16, rand() % 16};
    unsigned int DbStrFadLut1[12]          = {rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8, rand() % 8};
    unsigned int DbStrDirLut0[8]           = {rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9};
    unsigned int DbStrDirLut1[16]          = {rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9, rand() % 9};

    unsigned int dbd_det_lut_wgt[16]       = {0, 0, 1, 2, 5, 7, 10, 12, 12, 13, 13, 14, 14, 15, 15, 15};
    unsigned int dbd_hy_rdx8bin_lut[7]     = {16, 48, 80, 112, 144, 176, 208};

    unsigned int DmSwWhtLut[5]             = {rand() % 128, rand() % 128, rand() % 128, rand() % 128, rand() % 128};
    unsigned int DmStrDirGainLut[8]       = {rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9};
    unsigned int DmStrDirLut[16]           = {rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 ,
            rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9 , rand() % 9
                                             };
    unsigned int DmTransBand[31]           = {rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64,
            rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64,
            rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64,
            rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64, rand() % 64
                                             };

    HI_U32 db_lum_hor_delta_lut_p0       = DbStr_Delta_LutLumHor[0 ];
    HI_U32 db_lum_hor_delta_lut_p1       = DbStr_Delta_LutLumHor[1 ];
    HI_U32 db_lum_hor_delta_lut_p2       = DbStr_Delta_LutLumHor[2 ];
    HI_U32 db_lum_hor_delta_lut_p3       = DbStr_Delta_LutLumHor[3 ];
    HI_U32 db_lum_hor_delta_lut_p4       = DbStr_Delta_LutLumHor[4 ];
    HI_U32 db_lum_hor_delta_lut_p5       = DbStr_Delta_LutLumHor[5 ];
    HI_U32 db_lum_hor_delta_lut_p6       = DbStr_Delta_LutLumHor[6 ];
    HI_U32 db_lum_hor_delta_lut_p7       = DbStr_Delta_LutLumHor[7 ];
    HI_U32 db_lum_hor_delta_lut_p8       = DbStr_Delta_LutLumHor[8 ];
    HI_U32 db_lum_hor_delta_lut_p9       = DbStr_Delta_LutLumHor[9 ];
    HI_U32 db_lum_hor_delta_lut_p10      = DbStr_Delta_LutLumHor[10];
    HI_U32 db_lum_hor_delta_lut_p11      = DbStr_Delta_LutLumHor[11];
    HI_U32 db_lum_hor_delta_lut_p12      = DbStr_Delta_LutLumHor[12];
    HI_U32 db_lum_hor_delta_lut_p13      = DbStr_Delta_LutLumHor[13];
    HI_U32 db_lum_hor_delta_lut_p14      = DbStr_Delta_LutLumHor[14];
    HI_U32 db_lum_hor_delta_lut_p15      = DbStr_Delta_LutLumHor[15];
    HI_U32 db_lum_h_str_fade_lut_p0      = DbStrFadLut1[0 ];
    HI_U32 db_lum_h_str_fade_lut_p1      = DbStrFadLut1[1 ];
    HI_U32 db_lum_h_str_fade_lut_p2      = DbStrFadLut1[2 ];
    HI_U32 db_lum_h_str_fade_lut_p3      = DbStrFadLut1[3 ];
    HI_U32 db_lum_h_str_fade_lut_p4      = DbStrFadLut1[4 ];
    HI_U32 db_lum_h_str_fade_lut_p5      = DbStrFadLut1[5 ];
    HI_U32 db_lum_h_str_fade_lut_p6      = DbStrFadLut1[6 ];
    HI_U32 db_lum_h_str_fade_lut_p7      = DbStrFadLut1[7 ];
    HI_U32 db_lum_h_str_fade_lut_p8      = DbStrFadLut1[8 ];
    HI_U32 db_lum_h_str_fade_lut_p9      = DbStrFadLut1[9 ];
    HI_U32 db_lum_h_str_fade_lut_p10     = DbStrFadLut1[10];
    HI_U32 db_lum_h_str_fade_lut_p11     = DbStrFadLut1[11];
    HI_U32 db_dir_str_gain_lut_p0        = DbStrDirLut0[0] ;
    HI_U32 db_dir_str_gain_lut_p1        = DbStrDirLut0[1] ;
    HI_U32 db_dir_str_gain_lut_p2        = DbStrDirLut0[2] ;
    HI_U32 db_dir_str_gain_lut_p3        = DbStrDirLut0[3] ;
    HI_U32 db_dir_str_gain_lut_p4        = DbStrDirLut0[4] ;
    HI_U32 db_dir_str_gain_lut_p5        = DbStrDirLut0[5] ;
    HI_U32 db_dir_str_gain_lut_p6        = DbStrDirLut0[6] ;
    HI_U32 db_dir_str_gain_lut_p7        = DbStrDirLut0[7] ;
    HI_U32 db_dir_str_lut_p0             = DbStrDirLut1[0 ];
    HI_U32 db_dir_str_lut_p1             = DbStrDirLut1[1 ];
    HI_U32 db_dir_str_lut_p2             = DbStrDirLut1[2 ];
    HI_U32 db_dir_str_lut_p3             = DbStrDirLut1[3 ];
    HI_U32 db_dir_str_lut_p4             = DbStrDirLut1[4 ];
    HI_U32 db_dir_str_lut_p5             = DbStrDirLut1[5 ];
    HI_U32 db_dir_str_lut_p6             = DbStrDirLut1[6 ];
    HI_U32 db_dir_str_lut_p7             = DbStrDirLut1[7 ];
    HI_U32 db_dir_str_lut_p8             = DbStrDirLut1[8 ];
    HI_U32 db_dir_str_lut_p9             = DbStrDirLut1[9 ];
    HI_U32 db_dir_str_lut_p10            = DbStrDirLut1[10];
    HI_U32 db_dir_str_lut_p11            = DbStrDirLut1[11];
    HI_U32 db_dir_str_lut_p12            = DbStrDirLut1[12];
    HI_U32 db_dir_str_lut_p13            = DbStrDirLut1[13];
    HI_U32 db_dir_str_lut_p14            = DbStrDirLut1[14];
    HI_U32 db_dir_str_lut_p15            = DbStrDirLut1[15];
    //
    HI_U32 dm_sw_wht_lut_p0              = DmSwWhtLut[0]     ;
    HI_U32 dm_sw_wht_lut_p1              = DmSwWhtLut[1]     ;
    HI_U32 dm_sw_wht_lut_p2              = DmSwWhtLut[2]     ;
    HI_U32 dm_sw_wht_lut_p3              = DmSwWhtLut[3]     ;
    HI_U32 dm_sw_wht_lut_p4              = DmSwWhtLut[4]     ;
    // cas_info.tmu_regs.VPSS_DM_LUT1.bits.dm_limit_t                    = dm_limit_t        ;//rand() % 256 ;
    // cas_info.tmu_regs.VPSS_DM_LUT1.bits.dm_limit_t_10                 = dm_limit_t_10     ;//rand() % 1024;
    HI_U32 dm_dir_str_gain_lut_p0        = DmStrDirGainLut[0];
    HI_U32 dm_dir_str_gain_lut_p1        = DmStrDirGainLut[1];
    HI_U32 dm_dir_str_gain_lut_p2        = DmStrDirGainLut[2];
    HI_U32 dm_dir_str_gain_lut_p3        = DmStrDirGainLut[3];
    HI_U32 dm_dir_str_gain_lut_p4        = DmStrDirGainLut[4];
    HI_U32 dm_dir_str_gain_lut_p5        = DmStrDirGainLut[5];
    HI_U32 dm_dir_str_gain_lut_p6        = DmStrDirGainLut[6];
    HI_U32 dm_dir_str_gain_lut_p7        = DmStrDirGainLut[7];
    HI_U32 dm_dir_str_lut_p0             = DmStrDirLut[0 ]   ;
    HI_U32 dm_dir_str_lut_p1             = DmStrDirLut[1 ]   ;
    HI_U32 dm_dir_str_lut_p2             = DmStrDirLut[2 ]   ;
    HI_U32 dm_dir_str_lut_p3             = DmStrDirLut[3 ]   ;
    HI_U32 dm_dir_str_lut_p4             = DmStrDirLut[4 ]   ;
    HI_U32 dm_dir_str_lut_p5             = DmStrDirLut[5 ]   ;
    HI_U32 dm_dir_str_lut_p6             = DmStrDirLut[6 ]   ;
    HI_U32 dm_dir_str_lut_p7             = DmStrDirLut[7 ]   ;
    HI_U32 dm_dir_str_lut_p8             = DmStrDirLut[8 ]   ;
    HI_U32 dm_dir_str_lut_p9             = DmStrDirLut[9 ]   ;
    HI_U32 dm_dir_str_lut_p10            = DmStrDirLut[10]   ;
    HI_U32 dm_dir_str_lut_p11            = DmStrDirLut[11]   ;
    HI_U32 dm_dir_str_lut_p12            = DmStrDirLut[12]   ;
    HI_U32 dm_dir_str_lut_p13            = DmStrDirLut[13]   ;
    HI_U32 dm_dir_str_lut_p14            = DmStrDirLut[14]   ;
    HI_U32 dm_dir_str_lut_p15            = DmStrDirLut[15]   ;
    HI_U32 dm_trans_band_lut_p0          = DmTransBand[0 ]  ;
    HI_U32 dm_trans_band_lut_p1          = DmTransBand[1 ]  ;
    HI_U32 dm_trans_band_lut_p2          = DmTransBand[2 ]  ;
    HI_U32 dm_trans_band_lut_p3          = DmTransBand[3 ]  ;
    HI_U32 dm_trans_band_lut_p4          = DmTransBand[4 ]  ;
    HI_U32 dm_trans_band_lut_p5          = DmTransBand[5 ]  ;
    HI_U32 dm_trans_band_lut_p6          = DmTransBand[6 ]  ;
    HI_U32 dm_trans_band_lut_p7          = DmTransBand[7 ]  ;
    HI_U32 dm_trans_band_lut_p8          = DmTransBand[8 ]  ;
    HI_U32 dm_trans_band_lut_p9          = DmTransBand[9 ]  ;
    HI_U32 dm_trans_band_lut_p10         = DmTransBand[10]  ;
    HI_U32 dm_trans_band_lut_p11         = DmTransBand[11]  ;
    HI_U32 dm_trans_band_lut_p12         = DmTransBand[12]  ;
    HI_U32 dm_trans_band_lut_p13         = DmTransBand[13]  ;
    HI_U32 dm_trans_band_lut_p14         = DmTransBand[14]  ;
    HI_U32 dm_trans_band_lut_p15         = DmTransBand[15]  ;
    HI_U32 dm_trans_band_lut_p16         = DmTransBand[16]  ;
    HI_U32 dm_trans_band_lut_p17         = DmTransBand[17]  ;
    HI_U32 dm_trans_band_lut_p18         = DmTransBand[18]  ;
    HI_U32 dm_trans_band_lut_p19         = DmTransBand[19]  ;
    HI_U32 dm_trans_band_lut_p20         = DmTransBand[20]  ;
    HI_U32 dm_trans_band_lut_p21         = DmTransBand[21]  ;
    HI_U32 dm_trans_band_lut_p22         = DmTransBand[22]  ;
    HI_U32 dm_trans_band_lut_p23         = DmTransBand[23]  ;
    HI_U32 dm_trans_band_lut_p24         = DmTransBand[24]  ;
    HI_U32 dm_trans_band_lut_p25         = DmTransBand[25]  ;
    HI_U32 dm_trans_band_lut_p26         = DmTransBand[26]  ;
    HI_U32 dm_trans_band_lut_p27         = DmTransBand[27]  ;
    HI_U32 dm_trans_band_lut_p28         = DmTransBand[28]  ;
    HI_U32 dm_trans_band_lut_p29         = DmTransBand[29]  ;
    HI_U32 dm_trans_band_lut_p30         = DmTransBand[30]  ;
    //
    HI_U32 vpss_db_bord_flag_0     = 0;//BordFlag128[0 ] ;
    HI_U32 vpss_db_bord_flag_1     = 0;//BordFlag128[1 ] ;
    HI_U32 vpss_db_bord_flag_2     = 0;//BordFlag128[2 ] ;
    HI_U32 vpss_db_bord_flag_3     = 0;//BordFlag128[3 ] ;
    HI_U32 vpss_db_bord_flag_4     = 0;//BordFlag128[4 ] ;
    HI_U32 vpss_db_bord_flag_5     = 0;//BordFlag128[5 ] ;
    HI_U32 vpss_db_bord_flag_6     = 0;//BordFlag128[6 ] ;
    HI_U32 vpss_db_bord_flag_7     = 0;//BordFlag128[7 ] ;
    HI_U32 vpss_db_bord_flag_8     = 0;//BordFlag128[8 ] ;
    HI_U32 vpss_db_bord_flag_9     = 0;//BordFlag128[9 ] ;
    HI_U32 vpss_db_bord_flag_10    = 0;//BordFlag128[10] ;
    HI_U32 vpss_db_bord_flag_11    = 0;//BordFlag128[11] ;
    HI_U32 vpss_db_bord_flag_12    = 0;//BordFlag128[12] ;
    HI_U32 vpss_db_bord_flag_13    = 0;//BordFlag128[13] ;
    HI_U32 vpss_db_bord_flag_14    = 0;//BordFlag128[14] ;
    HI_U32 vpss_db_bord_flag_15    = 0;//BordFlag128[15] ;
    HI_U32 vpss_db_bord_flag_16    = 0;//BordFlag128[16] ;
    HI_U32 vpss_db_bord_flag_17    = 0;//BordFlag128[17] ;
    HI_U32 vpss_db_bord_flag_18    = 0;//BordFlag128[18] ;
    HI_U32 vpss_db_bord_flag_19    = 0;//BordFlag128[19] ;
    HI_U32 vpss_db_bord_flag_20    = 0;//BordFlag128[20] ;
    HI_U32 vpss_db_bord_flag_21    = 0;//BordFlag128[21] ;
    HI_U32 vpss_db_bord_flag_22    = 0;//BordFlag128[22] ;
    HI_U32 vpss_db_bord_flag_23    = 0;//BordFlag128[23] ;
    HI_U32 vpss_db_bord_flag_24    = 0;//BordFlag128[24] ;
    HI_U32 vpss_db_bord_flag_25    = 0;//BordFlag128[25] ;
    HI_U32 vpss_db_bord_flag_26    = 0;//BordFlag128[26] ;
    HI_U32 vpss_db_bord_flag_27    = 0;//BordFlag128[27] ;
    HI_U32 vpss_db_bord_flag_28    = 0;//BordFlag128[28] ;
    HI_U32 vpss_db_bord_flag_29    = 0;//BordFlag128[29] ;
    HI_U32 vpss_db_bord_flag_30    = 0;//BordFlag128[30] ;
    HI_U32 vpss_db_bord_flag_31    = 0;//BordFlag128[31] ;
    //

    HI_U32 motion_edge_lut00 = 0;//(motion_edge_lut[0] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut01 = 0;//(motion_edge_lut[0] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut02 = 0;//(motion_edge_lut[0] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut03 = 0;//(motion_edge_lut[0] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut04 = 0;//(motion_edge_lut[0] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut05 = 0;//(motion_edge_lut[0] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut06 = 0;//(motion_edge_lut[0] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut07 = 0;//(motion_edge_lut[0] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut08 = 0;//(motion_edge_lut[1] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut09 = 0;//(motion_edge_lut[1] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut0a = 0;//(motion_edge_lut[1] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut0b = 0;//(motion_edge_lut[1] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut0c = 0;//(motion_edge_lut[1] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut0d = 0;//(motion_edge_lut[1] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut0e = 0;//(motion_edge_lut[1] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut0f = 0;//(motion_edge_lut[1] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut10 = 0;//(motion_edge_lut[2] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut11 = 0;//(motion_edge_lut[2] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut12 = 0;//(motion_edge_lut[2] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut13 = 0;//(motion_edge_lut[2] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut14 = 0;//(motion_edge_lut[2] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut15 = 0;//(motion_edge_lut[2] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut16 = 0;//(motion_edge_lut[2] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut17 = 0;//(motion_edge_lut[2] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut18 = 0;//(motion_edge_lut[3] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut19 = 0;//(motion_edge_lut[3] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut1a = 0;//(motion_edge_lut[3] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut1b = 0;//(motion_edge_lut[3] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut1c = 0;//(motion_edge_lut[3] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut1d = 0;//(motion_edge_lut[3] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut1e = 0;//(motion_edge_lut[3] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut1f = 0;//(motion_edge_lut[3] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut20 = 0;//(motion_edge_lut[4] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut21 = 0;//(motion_edge_lut[4] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut22 = 0;//(motion_edge_lut[4] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut23 = 0;//(motion_edge_lut[4] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut24 = 0;//(motion_edge_lut[4] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut25 = 0;//(motion_edge_lut[4] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut26 = 0;//(motion_edge_lut[4] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut27 = 0;//(motion_edge_lut[4] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut28 = 0;//(motion_edge_lut[5] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut29 = 0;//(motion_edge_lut[5] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut2a = 0;//(motion_edge_lut[5] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut2b = 0;//(motion_edge_lut[5] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut2c = 0;//(motion_edge_lut[5] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut2d = 0;//(motion_edge_lut[5] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut2e = 0;//(motion_edge_lut[5] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut2f = 0;//(motion_edge_lut[5] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut30 = 0;//(motion_edge_lut[6] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut31 = 0;//(motion_edge_lut[6] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut32 = 0;//(motion_edge_lut[6] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut33 = 0;//(motion_edge_lut[6] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut34 = 0;//(motion_edge_lut[6] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut35 = 0;//(motion_edge_lut[6] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut36 = 0;//(motion_edge_lut[6] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut37 = 0;//(motion_edge_lut[6] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut38 = 0;//(motion_edge_lut[7] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut39 = 0;//(motion_edge_lut[7] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut3a = 0;//(motion_edge_lut[7] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut3b = 0;//(motion_edge_lut[7] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut3c = 0;//(motion_edge_lut[7] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut3d = 0;//(motion_edge_lut[7] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut3e = 0;//(motion_edge_lut[7] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut3f = 0;//(motion_edge_lut[7] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut40 = 0;//(motion_edge_lut[8] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut41 = 0;//(motion_edge_lut[8] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut42 = 0;//(motion_edge_lut[8] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut43 = 0;//(motion_edge_lut[8] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut44 = 0;//(motion_edge_lut[8] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut45 = 0;//(motion_edge_lut[8] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut46 = 0;//(motion_edge_lut[8] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut47 = 0;//(motion_edge_lut[8] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut48 = 0;//(motion_edge_lut[9] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut49 = 0;//(motion_edge_lut[9] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut4a = 0;//(motion_edge_lut[9] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut4b = 0;//(motion_edge_lut[9] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut4c = 0;//(motion_edge_lut[9] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut4d = 0;//(motion_edge_lut[9] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut4e = 0;//(motion_edge_lut[9] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut4f = 0;//(motion_edge_lut[9] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut50 = 0;//(motion_edge_lut[10] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut51 = 0;//(motion_edge_lut[10] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut52 = 0;//(motion_edge_lut[10] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut53 = 0;//(motion_edge_lut[10] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut54 = 0;//(motion_edge_lut[10] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut55 = 0;//(motion_edge_lut[10] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut56 = 0;//(motion_edge_lut[10] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut57 = 0;//(motion_edge_lut[10] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut58 = 0;//(motion_edge_lut[11] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut59 = 0;//(motion_edge_lut[11] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut5a = 0;//(motion_edge_lut[11] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut5b = 0;//(motion_edge_lut[11] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut5c = 0;//(motion_edge_lut[11] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut5d = 0;//(motion_edge_lut[11] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut5e = 0;//(motion_edge_lut[11] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut5f = 0;//(motion_edge_lut[11] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut60 = 0;//(motion_edge_lut[12] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut61 = 0;//(motion_edge_lut[12] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut62 = 0;//(motion_edge_lut[12] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut63 = 0;//(motion_edge_lut[12] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut64 = 0;//(motion_edge_lut[12] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut65 = 0;//(motion_edge_lut[12] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut66 = 0;//(motion_edge_lut[12] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut67 = 0;//(motion_edge_lut[12] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut68 = 0;//(motion_edge_lut[13] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut69 = 0;//(motion_edge_lut[13] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut6a = 0;//(motion_edge_lut[13] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut6b = 0;//(motion_edge_lut[13] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut6c = 0;//(motion_edge_lut[13] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut6d = 0;//(motion_edge_lut[13] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut6e = 0;//(motion_edge_lut[13] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut6f = 0;//(motion_edge_lut[13] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut70 = 0;//(motion_edge_lut[14] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut71 = 0;//(motion_edge_lut[14] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut72 = 0;//(motion_edge_lut[14] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut73 = 0;//(motion_edge_lut[14] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut74 = 0;//(motion_edge_lut[14] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut75 = 0;//(motion_edge_lut[14] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut76 = 0;//(motion_edge_lut[14] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut77 = 0;//(motion_edge_lut[14] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut78 = 0;//(motion_edge_lut[15] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut79 = 0;//(motion_edge_lut[15] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut7a = 0;//(motion_edge_lut[15] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut7b = 0;//(motion_edge_lut[15] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut7c = 0;//(motion_edge_lut[15] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut7d = 0;//(motion_edge_lut[15] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut7e = 0;//(motion_edge_lut[15] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut7f = 0;//(motion_edge_lut[15] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut80 = 0;//(motion_edge_lut[16] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut81 = 0;//(motion_edge_lut[16] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut82 = 0;//(motion_edge_lut[16] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut83 = 0;//(motion_edge_lut[16] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut84 = 0;//(motion_edge_lut[16] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut85 = 0;//(motion_edge_lut[16] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut86 = 0;//(motion_edge_lut[16] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut87 = 0;//(motion_edge_lut[16] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut88 = 0;//(motion_edge_lut[17] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut89 = 0;//(motion_edge_lut[17] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut8a = 0;//(motion_edge_lut[17] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut8b = 0;//(motion_edge_lut[17] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut8c = 0;//(motion_edge_lut[17] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut8d = 0;//(motion_edge_lut[17] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut8e = 0;//(motion_edge_lut[17] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut8f = 0;//(motion_edge_lut[17] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut90 = 0;//(motion_edge_lut[18] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut91 = 0;//(motion_edge_lut[18] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut92 = 0;//(motion_edge_lut[18] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut93 = 0;//(motion_edge_lut[18] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut94 = 0;//(motion_edge_lut[18] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut95 = 0;//(motion_edge_lut[18] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut96 = 0;//(motion_edge_lut[18] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut97 = 0;//(motion_edge_lut[18] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lut98 = 0;//(motion_edge_lut[19] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lut99 = 0;//(motion_edge_lut[19] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lut9a = 0;//(motion_edge_lut[19] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lut9b = 0;//(motion_edge_lut[19] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lut9c = 0;//(motion_edge_lut[19] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lut9d = 0;//(motion_edge_lut[19] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lut9e = 0;//(motion_edge_lut[19] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lut9f = 0;//(motion_edge_lut[19] & (0xf <<28)) >>28;
    HI_U32 motion_edge_luta0 = 0;//(motion_edge_lut[20] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_luta1 = 0;//(motion_edge_lut[20] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_luta2 = 0;//(motion_edge_lut[20] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_luta3 = 0;//(motion_edge_lut[20] & (0xf <<12)) >>12;
    HI_U32 motion_edge_luta4 = 0;//(motion_edge_lut[20] & (0xf <<16)) >>16;
    HI_U32 motion_edge_luta5 = 0;//(motion_edge_lut[20] & (0xf <<20)) >>20;
    HI_U32 motion_edge_luta6 = 0;//(motion_edge_lut[20] & (0xf <<24)) >>24;
    HI_U32 motion_edge_luta7 = 0;//(motion_edge_lut[20] & (0xf <<28)) >>28;
    HI_U32 motion_edge_luta8 = 0;//(motion_edge_lut[21] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_luta9 = 0;//(motion_edge_lut[21] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutaa = 0;//(motion_edge_lut[21] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutab = 0;//(motion_edge_lut[21] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutac = 0;//(motion_edge_lut[21] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutad = 0;//(motion_edge_lut[21] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutae = 0;//(motion_edge_lut[21] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutaf = 0;//(motion_edge_lut[21] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutb0 = 0;//(motion_edge_lut[22] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutb1 = 0;//(motion_edge_lut[22] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutb2 = 0;//(motion_edge_lut[22] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutb3 = 0;//(motion_edge_lut[22] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutb4 = 0;//(motion_edge_lut[22] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutb5 = 0;//(motion_edge_lut[22] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutb6 = 0;//(motion_edge_lut[22] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutb7 = 0;//(motion_edge_lut[22] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutb8 = 0;//(motion_edge_lut[23] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutb9 = 0;//(motion_edge_lut[23] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutba = 0;//(motion_edge_lut[23] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutbb = 0;//(motion_edge_lut[23] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutbc = 0;//(motion_edge_lut[23] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutbd = 0;//(motion_edge_lut[23] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutbe = 0;//(motion_edge_lut[23] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutbf = 0;//(motion_edge_lut[23] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutc0 = 0;//(motion_edge_lut[24] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutc1 = 0;//(motion_edge_lut[24] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutc2 = 0;//(motion_edge_lut[24] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutc3 = 0;//(motion_edge_lut[24] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutc4 = 0;//(motion_edge_lut[24] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutc5 = 0;//(motion_edge_lut[24] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutc6 = 0;//(motion_edge_lut[24] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutc7 = 0;//(motion_edge_lut[24] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutc8 = 0;//(motion_edge_lut[25] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutc9 = 0;//(motion_edge_lut[25] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutca = 0;//(motion_edge_lut[25] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutcb = 0;//(motion_edge_lut[25] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutcc = 0;//(motion_edge_lut[25] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutcd = 0;//(motion_edge_lut[25] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutce = 0;//(motion_edge_lut[25] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutcf = 0;//(motion_edge_lut[25] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutd0 = 0;//(motion_edge_lut[26] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutd1 = 0;//(motion_edge_lut[26] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutd2 = 0;//(motion_edge_lut[26] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutd3 = 0;//(motion_edge_lut[26] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutd4 = 0;//(motion_edge_lut[26] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutd5 = 0;//(motion_edge_lut[26] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutd6 = 0;//(motion_edge_lut[26] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutd7 = 0;//(motion_edge_lut[26] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutd8 = 0;//(motion_edge_lut[27] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutd9 = 0;//(motion_edge_lut[27] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutda = 0;//(motion_edge_lut[27] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutdb = 0;//(motion_edge_lut[27] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutdc = 0;//(motion_edge_lut[27] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutdd = 0;//(motion_edge_lut[27] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutde = 0;//(motion_edge_lut[27] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutdf = 0;//(motion_edge_lut[27] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lute0 = 0;//(motion_edge_lut[28] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lute1 = 0;//(motion_edge_lut[28] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lute2 = 0;//(motion_edge_lut[28] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lute3 = 0;//(motion_edge_lut[28] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lute4 = 0;//(motion_edge_lut[28] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lute5 = 0;//(motion_edge_lut[28] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lute6 = 0;//(motion_edge_lut[28] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lute7 = 0;//(motion_edge_lut[28] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lute8 = 0;//(motion_edge_lut[29] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lute9 = 0;//(motion_edge_lut[29] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutea = 0;//(motion_edge_lut[29] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_luteb = 0;//(motion_edge_lut[29] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutec = 0;//(motion_edge_lut[29] & (0xf <<16)) >>16;
    HI_U32 motion_edge_luted = 0;//(motion_edge_lut[29] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutee = 0;//(motion_edge_lut[29] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutef = 0;//(motion_edge_lut[29] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutf0 = 0;//(motion_edge_lut[30] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutf1 = 0;//(motion_edge_lut[30] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutf2 = 0;//(motion_edge_lut[30] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutf3 = 0;//(motion_edge_lut[30] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutf4 = 0;//(motion_edge_lut[30] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutf5 = 0;//(motion_edge_lut[30] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutf6 = 0;//(motion_edge_lut[30] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutf7 = 0;//(motion_edge_lut[30] & (0xf <<28)) >>28;
    HI_U32 motion_edge_lutf8 = 0;//(motion_edge_lut[31] & (0xf << 0)) >> 0;
    HI_U32 motion_edge_lutf9 = 0;//(motion_edge_lut[31] & (0xf << 4)) >> 4;
    HI_U32 motion_edge_lutfa = 0;//(motion_edge_lut[31] & (0xf << 8)) >> 8;
    HI_U32 motion_edge_lutfb = 0;//(motion_edge_lut[31] & (0xf <<12)) >>12;
    HI_U32 motion_edge_lutfc = 0;//(motion_edge_lut[31] & (0xf <<16)) >>16;
    HI_U32 motion_edge_lutfd = 0;//(motion_edge_lut[31] & (0xf <<20)) >>20;
    HI_U32 motion_edge_lutfe = 0;//(motion_edge_lut[31] & (0xf <<24)) >>24;
    HI_U32 motion_edge_lutff = 0;//(motion_edge_lut[31] & (0xf <<28)) >>28;


    unsigned int *BordFlag    = (unsigned int *) malloc(sizeof(unsigned int) * 4096);
    unsigned int *BordFlag128 = (unsigned int *) malloc(sizeof(unsigned int) * 32);

    VPSS_TNR_REG_TYPE_S *pstTnrRegType = HI_NULL;
    pstTnrRegType = (VPSS_TNR_REG_TYPE_S *)malloc(sizeof(VPSS_TNR_REG_TYPE_S));
    XDP_CHECK_NULL_PTR(pstTnrRegType);

    for (i = 0; i < 4096; i++)
    {
        BordFlag[i] = 0;
    }

    for (i = 0; i < 32; i++)
    {
        BordFlag128[i] = 0;
    }

    dbm_demo_pos_x     = rand() % (l_width);

    max_l_h_dist = l_h_bs / 2;//(rand() % (l_h_bs / 2));
    if (max_l_h_dist <= 1)
    {
        max_l_h_dist = 2;
    }
    if (max_l_h_dist > 12)
    {
        max_l_h_dist = 12;
    }


    if (blk_sel == 0)
    {
        i = 0;
        j = 0;
        //bd_stt = 1 + rand()%l_h_bs;//(l_h_bs/2 + 1) + (rand() % (l_h_bs - 2));
        l_h_blk_num = 0;

        do
        {
            bd_stt = 1 + rand() % (l_h_bs + l_h_bs / 2);
        }
        while (bd_stt >= l_width_1);


        for (i = bd_stt; i < l_width_1; i = i + l_h_bs)
        {
            //if (j % 5 == 0){
            //    BordFlag[i] = 0;
            //}
            //else{
            BordFlag[i] = 1;
            //}
            j++;
        }
        l_h_blk_num = j + 1;
    }
    else
    {
        j = 0;
        //bd_stt = 1 + rand()%l_h_bs;//(l_h_bs/2 + 1) + (rand() % (l_h_bs - 2));
        l_h_blk_num = 0;

        do
        {
            bd_stt = 1 + rand() % (l_h_bs + l_h_bs / 2);
        }
        while (bd_stt >= l_width_1);

        i = bd_stt;
        while (i < l_width_1)
        {
            BordFlag[i] = 1;
            j++;
            if (j % blk_skip == 0)
            {
                i = i + l_h_bs + 1;
            }
            else
            {
                i = i + l_h_bs;
            }
        }
        l_h_blk_num = j + 1;
    }

    for (i = 0; i < 32; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if (BordFlag[32 * i + j] == 1)
            {
                BordFlag128[i] += (1 << j);
            }
        }
    }

    vpss_db_bord_flag_0    = BordFlag128[0 ] ;
    vpss_db_bord_flag_1    = BordFlag128[1 ] ;
    vpss_db_bord_flag_2    = BordFlag128[2 ] ;
    vpss_db_bord_flag_3    = BordFlag128[3 ] ;
    vpss_db_bord_flag_4    = BordFlag128[4 ] ;
    vpss_db_bord_flag_5    = BordFlag128[5 ] ;
    vpss_db_bord_flag_6    = BordFlag128[6 ] ;
    vpss_db_bord_flag_7    = BordFlag128[7 ] ;
    vpss_db_bord_flag_8    = BordFlag128[8 ] ;
    vpss_db_bord_flag_9    = BordFlag128[9 ] ;
    vpss_db_bord_flag_10   = BordFlag128[10] ;
    vpss_db_bord_flag_11   = BordFlag128[11] ;
    vpss_db_bord_flag_12   = BordFlag128[12] ;
    vpss_db_bord_flag_13   = BordFlag128[13] ;
    vpss_db_bord_flag_14   = BordFlag128[14] ;
    vpss_db_bord_flag_15   = BordFlag128[15] ;
    vpss_db_bord_flag_16   = BordFlag128[16] ;
    vpss_db_bord_flag_17   = BordFlag128[17] ;
    vpss_db_bord_flag_18   = BordFlag128[18] ;
    vpss_db_bord_flag_19   = BordFlag128[19] ;
    vpss_db_bord_flag_20   = BordFlag128[20] ;
    vpss_db_bord_flag_21   = BordFlag128[21] ;
    vpss_db_bord_flag_22   = BordFlag128[22] ;
    vpss_db_bord_flag_23   = BordFlag128[23] ;
    vpss_db_bord_flag_24   = BordFlag128[24] ;
    vpss_db_bord_flag_25   = BordFlag128[25] ;
    vpss_db_bord_flag_26   = BordFlag128[26] ;
    vpss_db_bord_flag_27   = BordFlag128[27] ;
    vpss_db_bord_flag_28   = BordFlag128[28] ;
    vpss_db_bord_flag_29   = BordFlag128[29] ;
    vpss_db_bord_flag_30   = BordFlag128[30] ;
    vpss_db_bord_flag_31   = BordFlag128[31] ;

    pstTnrRegType->db_grad_sub_ratio        = rand() % 32 ;
    pstTnrRegType->db_ctrst_thresh          = rand() % 32 ;
    pstTnrRegType->db_lum_h_blk_size        = l_h_bs      ;
    pstTnrRegType->db_lum_hor_scale_ratio   = rand() % 4  ;
    pstTnrRegType->db_lum_hor_filter_sel    = rand() % 4  ;
    pstTnrRegType->db_global_db_strenth_lum = rand() % 16 ;
    pstTnrRegType->db_lum_hor_txt_win_size  = rand() % 3  ;
    pstTnrRegType->db_lum_hor_hf_diff_core  = rand() % 128;
    pstTnrRegType->db_lum_hor_hf_diff_gain1 = rand() % 16 ;
    pstTnrRegType->db_lum_hor_hf_diff_gain2 = rand() % 16 ;
    pstTnrRegType->db_lum_hor_hf_var_core   = rand() % 128;
    pstTnrRegType->db_lum_hor_hf_var_gain1  = rand() % 16 ;
    pstTnrRegType->db_lum_hor_hf_var_gain2  = rand() % 16 ;
    pstTnrRegType->db_lum_hor_adj_gain      = rand() % 32 ;
    pstTnrRegType->db_lum_hor_bord_adj_gain = rand() % 8  ;
    pstTnrRegType->db_ctrst_adj_core        = rand() % 32 ;
    pstTnrRegType->db_dir_smooth_mode       = rand() % 3  ;
    pstTnrRegType->db_ctrst_adj_gain1       = rand() % 16 ;
    pstTnrRegType->db_ctrst_adj_gain2       = rand() % 16 ;
    pstTnrRegType->db_max_lum_hor_db_dist   = max_l_h_dist;

    pstTnrRegType->dbd_hy_thd_edge     = rand() % 64;
    pstTnrRegType->dbd_hy_thd_txt      = rand() % 64;
    pstTnrRegType->dbd_hy_rtn_bd_txt   = rand() % 32;
    pstTnrRegType->dbd_hy_tst_blk_num  = rand() % 32;
    pstTnrRegType->dbd_min_blk_size    = rand() % 60 + 4;
    pstTnrRegType->dbd_hy_max_blk_size = uGetRand((pstTnrRegType->dbd_min_blk_size < 16 ? 16 : pstTnrRegType->dbd_min_blk_size), 64);
    pstTnrRegType->dbd_thr_flat        = rand() % 17;


    for (i = 0; i < 16; i++)
    {
        dbd_det_lut_wgt[i]        = rand() % 16;
    }

    for (i = 0; i < 7; i++)
    {
        dbd_hy_rdx8bin_lut[i]     = rand() % 2048;
    }

    pstTnrRegType->dm_grad_sub_ratio     = rand() % 32;
    pstTnrRegType->dm_ctrst_thresh       = rand() % 4 ;
    pstTnrRegType->dm_opp_ang_ctrst_t    = rand() % 256 ;
    pstTnrRegType->dm_opp_ang_ctrst_div  = rand() % 3 + 1 ;
    pstTnrRegType->dm_mmf_set            = rand() % 2 ;
    pstTnrRegType->dm_init_val_step      = rand() % 4 ;
    pstTnrRegType->dm_global_str         = rand() % 16;
    pstTnrRegType->dm_mndir_opp_ctrst_t  = rand() % 256 ;
    pstTnrRegType->dm_mmf_limit_en       = rand() % 2   ;
    pstTnrRegType->dm_csw_trsnt_st_10    = rand() % 1024;
    pstTnrRegType->dm_lw_ctrst_t         = rand() % 256 ;
    pstTnrRegType->dm_lw_ctrst_t_10      = rand() % 1024;
    pstTnrRegType->dm_csw_trsnt_st       = rand() % 256 ;
    pstTnrRegType->dm_lsw_ratio          = rand() % 8   ;
    pstTnrRegType->dm_mmf_lr             = rand() % 512  - 256  ;
    pstTnrRegType->dm_mmf_lr_10          = rand() % 2048 - 1024 ;
    pstTnrRegType->dm_csw_trsnt_lt       = rand() % 256  ;
    pstTnrRegType->dm_mmf_sr             = rand() % 512  - 256  ;
    pstTnrRegType->dm_mmf_sr_10          = rand() % 2048 - 1024 ;
    pstTnrRegType->dm_csw_trsnt_lt_10    = rand() % 1024;//
    pstTnrRegType->dm_limit_lsw_ratio    = rand() % 8 ;
    pstTnrRegType->dm_lim_res_blend_str1 = rand() % 9 ;
    pstTnrRegType->dm_lim_res_blend_str2 = rand() % 9 ;
    pstTnrRegType->dm_dir_blend_str      = rand() % 9 ;
    pstTnrRegType->dm_limit_t            = rand() % 256 ;
    pstTnrRegType->dm_limit_t_10         = rand() % 1024;

    pstTnrRegType->ywin_num            = uGetRand(0, 3);
    if (pstTnrRegType->ywin_num == 0)
    {
        pstTnrRegType->yWinRand_Width      = 1;
    }
    else if (pstTnrRegType->ywin_num == 1)
    {
        pstTnrRegType->yWinRand_Width      = 3;
    }
    else if (pstTnrRegType->ywin_num == 2)
    {
        pstTnrRegType->yWinRand_Width      = 5;
    }
    else if (pstTnrRegType->ywin_num == 3)
    {
        pstTnrRegType->yWinRand_Width      = 9;
    }

    pstTnrRegType->ynr2den             = uGetRand(0, 1);
    pstTnrRegType->cnr2den             = uGetRand(0, 1);
    pstTnrRegType->motionedgeweighten  = uGetRand(0, 1);
    pstTnrRegType->colorweighten       = uGetRand(0, 1);
    pstTnrRegType->motionalpha         = uGetRand(0, 63);

    pstTnrRegType->y2dwinwidth         = pstTnrRegType->yWinRand_Width   ;//1,3,5,9
    pstTnrRegType->y2dwinheight        = uGetRand(0, 2) * 2 + 1; //1,3,5
    pstTnrRegType->c2dwinwidth         = uGetRand(0, 2) * 2 + 1; //1,3,5
    pstTnrRegType->c2dwinheight        = uGetRand(0, 1) * 2 + 1; //1,3

    pstTnrRegType->ysnrstr             = uGetRand(0, 255); //24;
    pstTnrRegType->csnrstr             = uGetRand(0, 255); //24;
    pstTnrRegType->stroffset0          = uGetRand(0,  3);// 0;
    pstTnrRegType->stroffset1          = uGetRand(0,  3);// 1;
    pstTnrRegType->stroffset2          = uGetRand(0,  3);// 2;
    pstTnrRegType->stroffset3          = uGetRand(0,  3);// 3;
    pstTnrRegType->ystradjust          = uGetRand(0, 63);//16;
    pstTnrRegType->cstradjust          = uGetRand(0, 63);//16;

    pstTnrRegType->edgeprefilteren     = uGetRand(0,              1);//  1;//
    pstTnrRegType->edgemaxratio        = uGetRand(0,             15);// 15;//
    pstTnrRegType->edgeminratio        = uGetRand(0,   pstTnrRegType->edgemaxratio);//  3;//
    pstTnrRegType->edgeoriratio        = uGetRand(0,             15);//  8;//
    pstTnrRegType->edgemaxstrength     = uGetRand(0,             15);// 15;//
    pstTnrRegType->edgeminstrength     = uGetRand(0, pstTnrRegType->edgemaxstrength); //  0;//
    pstTnrRegType->edgeoristrength     = uGetRand(0,             15);//  0;//
    pstTnrRegType->edgestrth3          = uGetRand(0,           1023);//256;//
    pstTnrRegType->edgestrth2          = uGetRand(0,     pstTnrRegType->edgestrth3);//192;//
    pstTnrRegType->edgestrth1          = uGetRand(0,     pstTnrRegType->edgestrth2);//128;//
    pstTnrRegType->edgestrk3           = uGetRand(0,             63);//  1;//
    pstTnrRegType->edgestrk2           = uGetRand(0,             63);//  3;//
    pstTnrRegType->edgestrk1           = uGetRand(0,             63);//  0;//
    pstTnrRegType->edgemeanth8         = uGetRand(0,           1023);//768;//
    pstTnrRegType->edgemeanth7         = uGetRand(0,    pstTnrRegType->edgemeanth8);//512;//
    pstTnrRegType->edgemeanth6         = uGetRand(0,    pstTnrRegType->edgemeanth7);//300;//
    pstTnrRegType->edgemeanth5         = uGetRand(0,    pstTnrRegType->edgemeanth6);//196;//
    pstTnrRegType->edgemeanth4         = uGetRand(0,    pstTnrRegType->edgemeanth5);//164;//
    pstTnrRegType->edgemeanth3         = uGetRand(0,    pstTnrRegType->edgemeanth4);//128;//
    pstTnrRegType->edgemeanth2         = uGetRand(0,    pstTnrRegType->edgemeanth3);// 90;//
    pstTnrRegType->edgemeanth1         = uGetRand(0,    pstTnrRegType->edgemeanth2);// 64;//
    pstTnrRegType->edgemeank1          = uGetRand(0,             63);//  0;//
    pstTnrRegType->edgemeank2          = uGetRand(0,             63);// 32;//
    pstTnrRegType->edgemeank3          = uGetRand(0,             63);// 20;//
    pstTnrRegType->edgemeank4          = uGetRand(0,             63);// 10;//
    pstTnrRegType->edgemeank5          = uGetRand(0,             63);//  6;//
    pstTnrRegType->edgemeank6          = uGetRand(0,             63);//  4;//
    pstTnrRegType->edgemeank7          = uGetRand(0,             63);//  2;//
    pstTnrRegType->edgemeank8          = uGetRand(0,             63);//  1;//

    pstTnrRegType->edge1               = pstTnrRegType->edgeoristrength + ((pstTnrRegType->edgestrk1 * (pstTnrRegType->edgestrth1             ) + 16) >> 5);
    if (pstTnrRegType->edge1 < 0)
    {
        pstTnrRegType->edge1 =  0;
    }
    else if (pstTnrRegType->edge1 > 15)
    {
        pstTnrRegType->edge1 = 15;
    }
    pstTnrRegType->edge2               = pstTnrRegType->edge1           + ((pstTnrRegType->edgestrk2 * (pstTnrRegType->edgestrth2 - pstTnrRegType->edgestrth1) + 16) >> 5);
    if (pstTnrRegType->edge2 < 0)
    {
        pstTnrRegType->edge2 =  0;
    }
    else if (pstTnrRegType->edge2 > 15)
    {
        pstTnrRegType->edge2 = 15;
    }
    pstTnrRegType->edge3               = pstTnrRegType->edge2           + ((pstTnrRegType->edgestrk3 * (pstTnrRegType->edgestrth3 - pstTnrRegType->edgestrth2) + 16) >> 5);
    if (pstTnrRegType->edge3 < 0)
    {
        pstTnrRegType->edge3 =  0;
    }
    else if (pstTnrRegType->edge3 > 15)
    {
        pstTnrRegType->edge3 = 15;
    }

    pstTnrRegType->ratio1              = pstTnrRegType->edgeoriratio * 2 - ((pstTnrRegType->edgemeank1 * (pstTnrRegType->edgemeanth1              ) + 8) >> 4);
    if (pstTnrRegType->ratio1 < 0)
    {
        pstTnrRegType->ratio1 =  0;
    }
    else if (pstTnrRegType->ratio1 > 31)
    {
        pstTnrRegType->ratio1 = 31;
    }
    pstTnrRegType->ratio2              = pstTnrRegType->ratio1           - ((pstTnrRegType->edgemeank2 * (pstTnrRegType->edgemeanth2 - pstTnrRegType->edgemeanth1) + 8) >> 4);
    if (pstTnrRegType->ratio2 < 0)
    {
        pstTnrRegType->ratio2 =  0;
    }
    else if (pstTnrRegType->ratio2 > 31)
    {
        pstTnrRegType->ratio2 = 31;
    }
    pstTnrRegType->ratio3              = pstTnrRegType->ratio2           - ((pstTnrRegType->edgemeank3 * (pstTnrRegType->edgemeanth3 - pstTnrRegType->edgemeanth2) + 8) >> 4);
    if (pstTnrRegType->ratio3 < 0)
    {
        pstTnrRegType->ratio3 =  0;
    }
    else if (pstTnrRegType->ratio3 > 31)
    {
        pstTnrRegType->ratio3 = 31;
    }
    pstTnrRegType->ratio4              = pstTnrRegType->ratio3           - ((pstTnrRegType->edgemeank4 * (pstTnrRegType->edgemeanth4 - pstTnrRegType->edgemeanth3) + 8) >> 4);
    if (pstTnrRegType->ratio4 < 0)
    {
        pstTnrRegType->ratio4 =  0;
    }
    else if (pstTnrRegType->ratio4 > 31)
    {
        pstTnrRegType->ratio4 = 31;
    }
    pstTnrRegType->ratio5              = pstTnrRegType->ratio4           - ((pstTnrRegType->edgemeank5 * (pstTnrRegType->edgemeanth5 - pstTnrRegType->edgemeanth4) + 8) >> 4);
    if (pstTnrRegType->ratio5 < 0)
    {
        pstTnrRegType->ratio5 =  0;
    }
    else if (pstTnrRegType->ratio5 > 31)
    {
        pstTnrRegType->ratio5 = 31;
    }
    pstTnrRegType->ratio6              = pstTnrRegType->ratio5           - ((pstTnrRegType->edgemeank6 * (pstTnrRegType->edgemeanth6 - pstTnrRegType->edgemeanth5) + 8) >> 4);
    if (pstTnrRegType->ratio6 < 0)
    {
        pstTnrRegType->ratio6 =  0;
    }
    else if (pstTnrRegType->ratio6 > 31)
    {
        pstTnrRegType->ratio6 = 31;
    }
    pstTnrRegType->ratio7              = pstTnrRegType->ratio6           - ((pstTnrRegType->edgemeank7 * (pstTnrRegType->edgemeanth7 - pstTnrRegType->edgemeanth6) + 8) >> 4);
    if (pstTnrRegType->ratio7 < 0)
    {
        pstTnrRegType->ratio7 =  0;
    }
    else if (pstTnrRegType->ratio7 > 31)
    {
        pstTnrRegType->ratio7 = 31;
    }
    pstTnrRegType->ratio8              = pstTnrRegType->ratio7           - ((pstTnrRegType->edgemeank8 * (pstTnrRegType->edgemeanth8 - pstTnrRegType->edgemeanth7) + 8) >> 4);
    if (pstTnrRegType->ratio8 < 0)
    {
        pstTnrRegType->ratio8 =  0;
    }
    else if (pstTnrRegType->ratio8 > 31)
    {
        pstTnrRegType->ratio8 = 31;
    }

    pstTnrRegType->scenechange_en      = 0;
    pstTnrRegType->scenechange_mode1_en = 1;
    pstTnrRegType->scenechange_mode2_en = 1;
    pstTnrRegType->scenechange_bldk    = uGetRand(0, 1023);
    pstTnrRegType->scenechange_bldcore = uGetRand(0, 511);
    pstTnrRegType->scenechangeth       = 0;
    pstTnrRegType->scenechange_info    = uGetRand(0, 255);

    pstTnrRegType->cb_begin1           = uGetRand(0, 63);
    pstTnrRegType->cr_begin1           = uGetRand(0, 63);
    pstTnrRegType->cb_end1             = uGetRand(pstTnrRegType->cb_begin1, 63);
    pstTnrRegType->cr_end1             = uGetRand(pstTnrRegType->cr_begin1, 63);
    pstTnrRegType->cbcr_weight1        = uGetRand(0, 15);
    pstTnrRegType->cb_begin2           = uGetRand(0, 63);
    pstTnrRegType->cr_begin2           = uGetRand(0, 63);
    pstTnrRegType->cb_end2             = uGetRand(pstTnrRegType->cb_begin2, 63);
    pstTnrRegType->cr_end2             = uGetRand(pstTnrRegType->cr_begin2, 63);
    pstTnrRegType->cbcr_weight2        = uGetRand(0, 15);

    pstTnrRegType->test_en             = 0;//==0
    pstTnrRegType->test_color_cb       = 0;//==0
    pstTnrRegType->test_color_cr       = 0;//==0

    for (i = 0; i < 32; i++)
    {
        pstTnrRegType->motion_edge_lut[ i] = (uGetRand(0, 15) << 28) +
                                             (uGetRand(0, 15) << 24) +
                                             (uGetRand(0, 15) << 20) +
                                             (uGetRand(0, 15) << 16) +
                                             (uGetRand(0, 15) << 12) +
                                             (uGetRand(0, 15) <<  8) +
                                             (uGetRand(0, 15) <<  4) +
                                             (uGetRand(0, 15)      ) ;
    }


    vpss_db_bord_flag_0     = BordFlag128[0 ] ;
    vpss_db_bord_flag_1     = BordFlag128[1 ] ;
    vpss_db_bord_flag_2     = BordFlag128[2 ] ;
    vpss_db_bord_flag_3     = BordFlag128[3 ] ;
    vpss_db_bord_flag_4     = BordFlag128[4 ] ;
    vpss_db_bord_flag_5     = BordFlag128[5 ] ;
    vpss_db_bord_flag_6     = BordFlag128[6 ] ;
    vpss_db_bord_flag_7     = BordFlag128[7 ] ;
    vpss_db_bord_flag_8     = BordFlag128[8 ] ;
    vpss_db_bord_flag_9     = BordFlag128[9 ] ;
    vpss_db_bord_flag_10    = BordFlag128[10] ;
    vpss_db_bord_flag_11    = BordFlag128[11] ;
    vpss_db_bord_flag_12    = BordFlag128[12] ;
    vpss_db_bord_flag_13    = BordFlag128[13] ;
    vpss_db_bord_flag_14    = BordFlag128[14] ;
    vpss_db_bord_flag_15    = BordFlag128[15] ;
    vpss_db_bord_flag_16    = BordFlag128[16] ;
    vpss_db_bord_flag_17    = BordFlag128[17] ;
    vpss_db_bord_flag_18    = BordFlag128[18] ;
    vpss_db_bord_flag_19    = BordFlag128[19] ;
    vpss_db_bord_flag_20    = BordFlag128[20] ;
    vpss_db_bord_flag_21    = BordFlag128[21] ;
    vpss_db_bord_flag_22    = BordFlag128[22] ;
    vpss_db_bord_flag_23    = BordFlag128[23] ;
    vpss_db_bord_flag_24    = BordFlag128[24] ;
    vpss_db_bord_flag_25    = BordFlag128[25] ;
    vpss_db_bord_flag_26    = BordFlag128[26] ;
    vpss_db_bord_flag_27    = BordFlag128[27] ;
    vpss_db_bord_flag_28    = BordFlag128[28] ;
    vpss_db_bord_flag_29    = BordFlag128[29] ;
    vpss_db_bord_flag_30    = BordFlag128[30] ;
    vpss_db_bord_flag_31    = BordFlag128[31] ;


    motion_edge_lut00 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 0)) >> 0;
    motion_edge_lut01 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 4)) >> 4;
    motion_edge_lut02 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 8)) >> 8;
    motion_edge_lut03 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 12)) >> 12;
    motion_edge_lut04 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 16)) >> 16;
    motion_edge_lut05 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 20)) >> 20;
    motion_edge_lut06 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 24)) >> 24;
    motion_edge_lut07 = (pstTnrRegType->motion_edge_lut[0] & (0xf << 28)) >> 28;
    motion_edge_lut08 = (pstTnrRegType->motion_edge_lut[1] & (0xf << 0)) >> 0;
    motion_edge_lut09 = (pstTnrRegType->motion_edge_lut[1] & (0xf << 4)) >> 4;
    motion_edge_lut0a = (pstTnrRegType->motion_edge_lut[1] & (0xf << 8)) >> 8;
    motion_edge_lut0b = (pstTnrRegType->motion_edge_lut[1] & (0xf << 12)) >> 12;
    motion_edge_lut0c = (pstTnrRegType->motion_edge_lut[1] & (0xf << 16)) >> 16;
    motion_edge_lut0d = (pstTnrRegType->motion_edge_lut[1] & (0xf << 20)) >> 20;
    motion_edge_lut0e = (pstTnrRegType->motion_edge_lut[1] & (0xf << 24)) >> 24;
    motion_edge_lut0f = (pstTnrRegType->motion_edge_lut[1] & (0xf << 28)) >> 28;
    motion_edge_lut10 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 0)) >> 0;
    motion_edge_lut11 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 4)) >> 4;
    motion_edge_lut12 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 8)) >> 8;
    motion_edge_lut13 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 12)) >> 12;
    motion_edge_lut14 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 16)) >> 16;
    motion_edge_lut15 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 20)) >> 20;
    motion_edge_lut16 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 24)) >> 24;
    motion_edge_lut17 = (pstTnrRegType->motion_edge_lut[2] & (0xf << 28)) >> 28;
    motion_edge_lut18 = (pstTnrRegType->motion_edge_lut[3] & (0xf << 0)) >> 0;
    motion_edge_lut19 = (pstTnrRegType->motion_edge_lut[3] & (0xf << 4)) >> 4;
    motion_edge_lut1a = (pstTnrRegType->motion_edge_lut[3] & (0xf << 8)) >> 8;
    motion_edge_lut1b = (pstTnrRegType->motion_edge_lut[3] & (0xf << 12)) >> 12;
    motion_edge_lut1c = (pstTnrRegType->motion_edge_lut[3] & (0xf << 16)) >> 16;
    motion_edge_lut1d = (pstTnrRegType->motion_edge_lut[3] & (0xf << 20)) >> 20;
    motion_edge_lut1e = (pstTnrRegType->motion_edge_lut[3] & (0xf << 24)) >> 24;
    motion_edge_lut1f = (pstTnrRegType->motion_edge_lut[3] & (0xf << 28)) >> 28;
    motion_edge_lut20 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 0)) >> 0;
    motion_edge_lut21 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 4)) >> 4;
    motion_edge_lut22 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 8)) >> 8;
    motion_edge_lut23 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 12)) >> 12;
    motion_edge_lut24 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 16)) >> 16;
    motion_edge_lut25 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 20)) >> 20;
    motion_edge_lut26 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 24)) >> 24;
    motion_edge_lut27 = (pstTnrRegType->motion_edge_lut[4] & (0xf << 28)) >> 28;
    motion_edge_lut28 = (pstTnrRegType->motion_edge_lut[5] & (0xf << 0)) >> 0;
    motion_edge_lut29 = (pstTnrRegType->motion_edge_lut[5] & (0xf << 4)) >> 4;
    motion_edge_lut2a = (pstTnrRegType->motion_edge_lut[5] & (0xf << 8)) >> 8;
    motion_edge_lut2b = (pstTnrRegType->motion_edge_lut[5] & (0xf << 12)) >> 12;
    motion_edge_lut2c = (pstTnrRegType->motion_edge_lut[5] & (0xf << 16)) >> 16;
    motion_edge_lut2d = (pstTnrRegType->motion_edge_lut[5] & (0xf << 20)) >> 20;
    motion_edge_lut2e = (pstTnrRegType->motion_edge_lut[5] & (0xf << 24)) >> 24;
    motion_edge_lut2f = (pstTnrRegType->motion_edge_lut[5] & (0xf << 28)) >> 28;
    motion_edge_lut30 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 0)) >> 0;
    motion_edge_lut31 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 4)) >> 4;
    motion_edge_lut32 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 8)) >> 8;
    motion_edge_lut33 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 12)) >> 12;
    motion_edge_lut34 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 16)) >> 16;
    motion_edge_lut35 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 20)) >> 20;
    motion_edge_lut36 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 24)) >> 24;
    motion_edge_lut37 = (pstTnrRegType->motion_edge_lut[6] & (0xf << 28)) >> 28;
    motion_edge_lut38 = (pstTnrRegType->motion_edge_lut[7] & (0xf << 0)) >> 0;
    motion_edge_lut39 = (pstTnrRegType->motion_edge_lut[7] & (0xf << 4)) >> 4;
    motion_edge_lut3a = (pstTnrRegType->motion_edge_lut[7] & (0xf << 8)) >> 8;
    motion_edge_lut3b = (pstTnrRegType->motion_edge_lut[7] & (0xf << 12)) >> 12;
    motion_edge_lut3c = (pstTnrRegType->motion_edge_lut[7] & (0xf << 16)) >> 16;
    motion_edge_lut3d = (pstTnrRegType->motion_edge_lut[7] & (0xf << 20)) >> 20;
    motion_edge_lut3e = (pstTnrRegType->motion_edge_lut[7] & (0xf << 24)) >> 24;
    motion_edge_lut3f = (pstTnrRegType->motion_edge_lut[7] & (0xf << 28)) >> 28;
    motion_edge_lut40 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 0)) >> 0;
    motion_edge_lut41 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 4)) >> 4;
    motion_edge_lut42 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 8)) >> 8;
    motion_edge_lut43 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 12)) >> 12;
    motion_edge_lut44 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 16)) >> 16;
    motion_edge_lut45 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 20)) >> 20;
    motion_edge_lut46 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 24)) >> 24;
    motion_edge_lut47 = (pstTnrRegType->motion_edge_lut[8] & (0xf << 28)) >> 28;
    motion_edge_lut48 = (pstTnrRegType->motion_edge_lut[9] & (0xf << 0)) >> 0;
    motion_edge_lut49 = (pstTnrRegType->motion_edge_lut[9] & (0xf << 4)) >> 4;
    motion_edge_lut4a = (pstTnrRegType->motion_edge_lut[9] & (0xf << 8)) >> 8;
    motion_edge_lut4b = (pstTnrRegType->motion_edge_lut[9] & (0xf << 12)) >> 12;
    motion_edge_lut4c = (pstTnrRegType->motion_edge_lut[9] & (0xf << 16)) >> 16;
    motion_edge_lut4d = (pstTnrRegType->motion_edge_lut[9] & (0xf << 20)) >> 20;
    motion_edge_lut4e = (pstTnrRegType->motion_edge_lut[9] & (0xf << 24)) >> 24;
    motion_edge_lut4f = (pstTnrRegType->motion_edge_lut[9] & (0xf << 28)) >> 28;
    motion_edge_lut50 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 0)) >> 0;
    motion_edge_lut51 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 4)) >> 4;
    motion_edge_lut52 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 8)) >> 8;
    motion_edge_lut53 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 12)) >> 12;
    motion_edge_lut54 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 16)) >> 16;
    motion_edge_lut55 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 20)) >> 20;
    motion_edge_lut56 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 24)) >> 24;
    motion_edge_lut57 = (pstTnrRegType->motion_edge_lut[10] & (0xf << 28)) >> 28;
    motion_edge_lut58 = (pstTnrRegType->motion_edge_lut[11] & (0xf << 0)) >> 0;
    motion_edge_lut59 = (pstTnrRegType->motion_edge_lut[11] & (0xf << 4)) >> 4;
    motion_edge_lut5a = (pstTnrRegType->motion_edge_lut[11] & (0xf << 8)) >> 8;
    motion_edge_lut5b = (pstTnrRegType->motion_edge_lut[11] & (0xf << 12)) >> 12;
    motion_edge_lut5c = (pstTnrRegType->motion_edge_lut[11] & (0xf << 16)) >> 16;
    motion_edge_lut5d = (pstTnrRegType->motion_edge_lut[11] & (0xf << 20)) >> 20;
    motion_edge_lut5e = (pstTnrRegType->motion_edge_lut[11] & (0xf << 24)) >> 24;
    motion_edge_lut5f = (pstTnrRegType->motion_edge_lut[11] & (0xf << 28)) >> 28;
    motion_edge_lut60 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 0)) >> 0;
    motion_edge_lut61 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 4)) >> 4;
    motion_edge_lut62 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 8)) >> 8;
    motion_edge_lut63 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 12)) >> 12;
    motion_edge_lut64 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 16)) >> 16;
    motion_edge_lut65 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 20)) >> 20;
    motion_edge_lut66 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 24)) >> 24;
    motion_edge_lut67 = (pstTnrRegType->motion_edge_lut[12] & (0xf << 28)) >> 28;
    motion_edge_lut68 = (pstTnrRegType->motion_edge_lut[13] & (0xf << 0)) >> 0;
    motion_edge_lut69 = (pstTnrRegType->motion_edge_lut[13] & (0xf << 4)) >> 4;
    motion_edge_lut6a = (pstTnrRegType->motion_edge_lut[13] & (0xf << 8)) >> 8;
    motion_edge_lut6b = (pstTnrRegType->motion_edge_lut[13] & (0xf << 12)) >> 12;
    motion_edge_lut6c = (pstTnrRegType->motion_edge_lut[13] & (0xf << 16)) >> 16;
    motion_edge_lut6d = (pstTnrRegType->motion_edge_lut[13] & (0xf << 20)) >> 20;
    motion_edge_lut6e = (pstTnrRegType->motion_edge_lut[13] & (0xf << 24)) >> 24;
    motion_edge_lut6f = (pstTnrRegType->motion_edge_lut[13] & (0xf << 28)) >> 28;
    motion_edge_lut70 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 0)) >> 0;
    motion_edge_lut71 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 4)) >> 4;
    motion_edge_lut72 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 8)) >> 8;
    motion_edge_lut73 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 12)) >> 12;
    motion_edge_lut74 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 16)) >> 16;
    motion_edge_lut75 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 20)) >> 20;
    motion_edge_lut76 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 24)) >> 24;
    motion_edge_lut77 = (pstTnrRegType->motion_edge_lut[14] & (0xf << 28)) >> 28;
    motion_edge_lut78 = (pstTnrRegType->motion_edge_lut[15] & (0xf << 0)) >> 0;
    motion_edge_lut79 = (pstTnrRegType->motion_edge_lut[15] & (0xf << 4)) >> 4;
    motion_edge_lut7a = (pstTnrRegType->motion_edge_lut[15] & (0xf << 8)) >> 8;
    motion_edge_lut7b = (pstTnrRegType->motion_edge_lut[15] & (0xf << 12)) >> 12;
    motion_edge_lut7c = (pstTnrRegType->motion_edge_lut[15] & (0xf << 16)) >> 16;
    motion_edge_lut7d = (pstTnrRegType->motion_edge_lut[15] & (0xf << 20)) >> 20;
    motion_edge_lut7e = (pstTnrRegType->motion_edge_lut[15] & (0xf << 24)) >> 24;
    motion_edge_lut7f = (pstTnrRegType->motion_edge_lut[15] & (0xf << 28)) >> 28;
    motion_edge_lut80 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 0)) >> 0;
    motion_edge_lut81 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 4)) >> 4;
    motion_edge_lut82 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 8)) >> 8;
    motion_edge_lut83 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 12)) >> 12;
    motion_edge_lut84 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 16)) >> 16;
    motion_edge_lut85 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 20)) >> 20;
    motion_edge_lut86 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 24)) >> 24;
    motion_edge_lut87 = (pstTnrRegType->motion_edge_lut[16] & (0xf << 28)) >> 28;
    motion_edge_lut88 = (pstTnrRegType->motion_edge_lut[17] & (0xf << 0)) >> 0;
    motion_edge_lut89 = (pstTnrRegType->motion_edge_lut[17] & (0xf << 4)) >> 4;
    motion_edge_lut8a = (pstTnrRegType->motion_edge_lut[17] & (0xf << 8)) >> 8;
    motion_edge_lut8b = (pstTnrRegType->motion_edge_lut[17] & (0xf << 12)) >> 12;
    motion_edge_lut8c = (pstTnrRegType->motion_edge_lut[17] & (0xf << 16)) >> 16;
    motion_edge_lut8d = (pstTnrRegType->motion_edge_lut[17] & (0xf << 20)) >> 20;
    motion_edge_lut8e = (pstTnrRegType->motion_edge_lut[17] & (0xf << 24)) >> 24;
    motion_edge_lut8f = (pstTnrRegType->motion_edge_lut[17] & (0xf << 28)) >> 28;
    motion_edge_lut90 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 0)) >> 0;
    motion_edge_lut91 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 4)) >> 4;
    motion_edge_lut92 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 8)) >> 8;
    motion_edge_lut93 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 12)) >> 12;
    motion_edge_lut94 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 16)) >> 16;
    motion_edge_lut95 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 20)) >> 20;
    motion_edge_lut96 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 24)) >> 24;
    motion_edge_lut97 = (pstTnrRegType->motion_edge_lut[18] & (0xf << 28)) >> 28;
    motion_edge_lut98 = (pstTnrRegType->motion_edge_lut[19] & (0xf << 0)) >> 0;
    motion_edge_lut99 = (pstTnrRegType->motion_edge_lut[19] & (0xf << 4)) >> 4;
    motion_edge_lut9a = (pstTnrRegType->motion_edge_lut[19] & (0xf << 8)) >> 8;
    motion_edge_lut9b = (pstTnrRegType->motion_edge_lut[19] & (0xf << 12)) >> 12;
    motion_edge_lut9c = (pstTnrRegType->motion_edge_lut[19] & (0xf << 16)) >> 16;
    motion_edge_lut9d = (pstTnrRegType->motion_edge_lut[19] & (0xf << 20)) >> 20;
    motion_edge_lut9e = (pstTnrRegType->motion_edge_lut[19] & (0xf << 24)) >> 24;
    motion_edge_lut9f = (pstTnrRegType->motion_edge_lut[19] & (0xf << 28)) >> 28;
    motion_edge_luta0 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 0)) >> 0;
    motion_edge_luta1 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 4)) >> 4;
    motion_edge_luta2 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 8)) >> 8;
    motion_edge_luta3 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 12)) >> 12;
    motion_edge_luta4 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 16)) >> 16;
    motion_edge_luta5 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 20)) >> 20;
    motion_edge_luta6 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 24)) >> 24;
    motion_edge_luta7 = (pstTnrRegType->motion_edge_lut[20] & (0xf << 28)) >> 28;
    motion_edge_luta8 = (pstTnrRegType->motion_edge_lut[21] & (0xf << 0)) >> 0;
    motion_edge_luta9 = (pstTnrRegType->motion_edge_lut[21] & (0xf << 4)) >> 4;
    motion_edge_lutaa = (pstTnrRegType->motion_edge_lut[21] & (0xf << 8)) >> 8;
    motion_edge_lutab = (pstTnrRegType->motion_edge_lut[21] & (0xf << 12)) >> 12;
    motion_edge_lutac = (pstTnrRegType->motion_edge_lut[21] & (0xf << 16)) >> 16;
    motion_edge_lutad = (pstTnrRegType->motion_edge_lut[21] & (0xf << 20)) >> 20;
    motion_edge_lutae = (pstTnrRegType->motion_edge_lut[21] & (0xf << 24)) >> 24;
    motion_edge_lutaf = (pstTnrRegType->motion_edge_lut[21] & (0xf << 28)) >> 28;
    motion_edge_lutb0 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 0)) >> 0;
    motion_edge_lutb1 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 4)) >> 4;
    motion_edge_lutb2 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 8)) >> 8;
    motion_edge_lutb3 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 12)) >> 12;
    motion_edge_lutb4 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 16)) >> 16;
    motion_edge_lutb5 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 20)) >> 20;
    motion_edge_lutb6 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 24)) >> 24;
    motion_edge_lutb7 = (pstTnrRegType->motion_edge_lut[22] & (0xf << 28)) >> 28;
    motion_edge_lutb8 = (pstTnrRegType->motion_edge_lut[23] & (0xf << 0)) >> 0;
    motion_edge_lutb9 = (pstTnrRegType->motion_edge_lut[23] & (0xf << 4)) >> 4;
    motion_edge_lutba = (pstTnrRegType->motion_edge_lut[23] & (0xf << 8)) >> 8;
    motion_edge_lutbb = (pstTnrRegType->motion_edge_lut[23] & (0xf << 12)) >> 12;
    motion_edge_lutbc = (pstTnrRegType->motion_edge_lut[23] & (0xf << 16)) >> 16;
    motion_edge_lutbd = (pstTnrRegType->motion_edge_lut[23] & (0xf << 20)) >> 20;
    motion_edge_lutbe = (pstTnrRegType->motion_edge_lut[23] & (0xf << 24)) >> 24;
    motion_edge_lutbf = (pstTnrRegType->motion_edge_lut[23] & (0xf << 28)) >> 28;
    motion_edge_lutc0 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 0)) >> 0;
    motion_edge_lutc1 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 4)) >> 4;
    motion_edge_lutc2 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 8)) >> 8;
    motion_edge_lutc3 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 12)) >> 12;
    motion_edge_lutc4 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 16)) >> 16;
    motion_edge_lutc5 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 20)) >> 20;
    motion_edge_lutc6 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 24)) >> 24;
    motion_edge_lutc7 = (pstTnrRegType->motion_edge_lut[24] & (0xf << 28)) >> 28;
    motion_edge_lutc8 = (pstTnrRegType->motion_edge_lut[25] & (0xf << 0)) >> 0;
    motion_edge_lutc9 = (pstTnrRegType->motion_edge_lut[25] & (0xf << 4)) >> 4;
    motion_edge_lutca = (pstTnrRegType->motion_edge_lut[25] & (0xf << 8)) >> 8;
    motion_edge_lutcb = (pstTnrRegType->motion_edge_lut[25] & (0xf << 12)) >> 12;
    motion_edge_lutcc = (pstTnrRegType->motion_edge_lut[25] & (0xf << 16)) >> 16;
    motion_edge_lutcd = (pstTnrRegType->motion_edge_lut[25] & (0xf << 20)) >> 20;
    motion_edge_lutce = (pstTnrRegType->motion_edge_lut[25] & (0xf << 24)) >> 24;
    motion_edge_lutcf = (pstTnrRegType->motion_edge_lut[25] & (0xf << 28)) >> 28;
    motion_edge_lutd0 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 0)) >> 0;
    motion_edge_lutd1 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 4)) >> 4;
    motion_edge_lutd2 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 8)) >> 8;
    motion_edge_lutd3 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 12)) >> 12;
    motion_edge_lutd4 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 16)) >> 16;
    motion_edge_lutd5 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 20)) >> 20;
    motion_edge_lutd6 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 24)) >> 24;
    motion_edge_lutd7 = (pstTnrRegType->motion_edge_lut[26] & (0xf << 28)) >> 28;
    motion_edge_lutd8 = (pstTnrRegType->motion_edge_lut[27] & (0xf << 0)) >> 0;
    motion_edge_lutd9 = (pstTnrRegType->motion_edge_lut[27] & (0xf << 4)) >> 4;
    motion_edge_lutda = (pstTnrRegType->motion_edge_lut[27] & (0xf << 8)) >> 8;
    motion_edge_lutdb = (pstTnrRegType->motion_edge_lut[27] & (0xf << 12)) >> 12;
    motion_edge_lutdc = (pstTnrRegType->motion_edge_lut[27] & (0xf << 16)) >> 16;
    motion_edge_lutdd = (pstTnrRegType->motion_edge_lut[27] & (0xf << 20)) >> 20;
    motion_edge_lutde = (pstTnrRegType->motion_edge_lut[27] & (0xf << 24)) >> 24;
    motion_edge_lutdf = (pstTnrRegType->motion_edge_lut[27] & (0xf << 28)) >> 28;
    motion_edge_lute0 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 0)) >> 0;
    motion_edge_lute1 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 4)) >> 4;
    motion_edge_lute2 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 8)) >> 8;
    motion_edge_lute3 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 12)) >> 12;
    motion_edge_lute4 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 16)) >> 16;
    motion_edge_lute5 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 20)) >> 20;
    motion_edge_lute6 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 24)) >> 24;
    motion_edge_lute7 = (pstTnrRegType->motion_edge_lut[28] & (0xf << 28)) >> 28;
    motion_edge_lute8 = (pstTnrRegType->motion_edge_lut[29] & (0xf << 0)) >> 0;
    motion_edge_lute9 = (pstTnrRegType->motion_edge_lut[29] & (0xf << 4)) >> 4;
    motion_edge_lutea = (pstTnrRegType->motion_edge_lut[29] & (0xf << 8)) >> 8;
    motion_edge_luteb = (pstTnrRegType->motion_edge_lut[29] & (0xf << 12)) >> 12;
    motion_edge_lutec = (pstTnrRegType->motion_edge_lut[29] & (0xf << 16)) >> 16;
    motion_edge_luted = (pstTnrRegType->motion_edge_lut[29] & (0xf << 20)) >> 20;
    motion_edge_lutee = (pstTnrRegType->motion_edge_lut[29] & (0xf << 24)) >> 24;
    motion_edge_lutef = (pstTnrRegType->motion_edge_lut[29] & (0xf << 28)) >> 28;
    motion_edge_lutf0 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 0)) >> 0;
    motion_edge_lutf1 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 4)) >> 4;
    motion_edge_lutf2 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 8)) >> 8;
    motion_edge_lutf3 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 12)) >> 12;
    motion_edge_lutf4 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 16)) >> 16;
    motion_edge_lutf5 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 20)) >> 20;
    motion_edge_lutf6 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 24)) >> 24;
    motion_edge_lutf7 = (pstTnrRegType->motion_edge_lut[30] & (0xf << 28)) >> 28;
    motion_edge_lutf8 = (pstTnrRegType->motion_edge_lut[31] & (0xf << 0)) >> 0;
    motion_edge_lutf9 = (pstTnrRegType->motion_edge_lut[31] & (0xf << 4)) >> 4;
    motion_edge_lutfa = (pstTnrRegType->motion_edge_lut[31] & (0xf << 8)) >> 8;
    motion_edge_lutfb = (pstTnrRegType->motion_edge_lut[31] & (0xf << 12)) >> 12;
    motion_edge_lutfc = (pstTnrRegType->motion_edge_lut[31] & (0xf << 16)) >> 16;
    motion_edge_lutfd = (pstTnrRegType->motion_edge_lut[31] & (0xf << 20)) >> 20;
    motion_edge_lutfe = (pstTnrRegType->motion_edge_lut[31] & (0xf << 24)) >> 24;
    motion_edge_lutff = (pstTnrRegType->motion_edge_lut[31] & (0xf << 28)) >> 28;

    VPSS_Sys_SetDbmOutMode(pstVpssRegs,  u32AddrOffset,  dbm_out_mode);
    VPSS_Sys_SetDetHyEn(pstVpssRegs,  u32AddrOffset,  det_hy_en);
    VPSS_Sys_SetDbmDemoMode(pstVpssRegs,  u32AddrOffset,  dbm_demo_mode);
    VPSS_Sys_SetDbmDemoEn(pstVpssRegs,  u32AddrOffset,  dbm_demo_en);
    VPSS_Sys_SetDbLumHorEn(pstVpssRegs,  u32AddrOffset,  db_lum_hor_en);
    VPSS_Sys_SetNrEn(pstVpssRegs,  u32AddrOffset,  nr_en);
    VPSS_Sys_SetDmEn(pstVpssRegs,  u32AddrOffset,  dm_en);
    VPSS_Sys_SetDbEn(pstVpssRegs,  u32AddrOffset,  db_en);
    VPSS_Sys_SetDbmDemoPosX(pstVpssRegs,  u32AddrOffset,  dbm_demo_pos_x);
    VPSS_Sys_SetDbCtrstThresh(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_ctrst_thresh);
    VPSS_Sys_SetDbGradSubRatio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_grad_sub_ratio);
    VPSS_Sys_SetDbLumHBlkSize(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_h_blk_size);
    VPSS_Sys_SetDbLumHorTxtWinSize(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_txt_win_size);
    VPSS_Sys_SetDbGlobalDbStrenthLum(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_global_db_strenth_lum);
    VPSS_Sys_SetDbLumHorFilterSel(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_filter_sel);
    VPSS_Sys_SetDbLumHorScaleRatio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_scale_ratio);
    VPSS_Sys_SetDbLumHorHfVarGain2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_var_gain2);
    VPSS_Sys_SetDbLumHorHfVarGain1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_var_gain1);
    VPSS_Sys_SetDbLumHorHfVarCore(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_var_core);
    VPSS_Sys_SetDbLumHorHfDiffGain2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_diff_gain2);
    VPSS_Sys_SetDbLumHorHfDiffGain1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_diff_gain1);
    VPSS_Sys_SetDbLumHorHfDiffCore(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_hf_diff_core);
    VPSS_Sys_SetDbLumHorBordAdjGain(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_bord_adj_gain);
    VPSS_Sys_SetDbLumHorAdjGain(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_lum_hor_adj_gain);
    VPSS_Sys_SetDbMaxLumHorDbDist(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_max_lum_hor_db_dist);
    VPSS_Sys_SetDbCtrstAdjGain2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_ctrst_adj_gain2);
    VPSS_Sys_SetDbCtrstAdjGain1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_ctrst_adj_gain1);
    VPSS_Sys_SetDbDirSmoothMode(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_dir_smooth_mode);
    VPSS_Sys_SetDbCtrstAdjCore(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->db_ctrst_adj_core);
    VPSS_Sys_SetDbLumHorDeltaLutP7(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p7);
    VPSS_Sys_SetDbLumHorDeltaLutP6(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p6);
    VPSS_Sys_SetDbLumHorDeltaLutP5(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p5);
    VPSS_Sys_SetDbLumHorDeltaLutP4(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p4);
    VPSS_Sys_SetDbLumHorDeltaLutP3(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p3);
    VPSS_Sys_SetDbLumHorDeltaLutP2(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p2);
    VPSS_Sys_SetDbLumHorDeltaLutP1(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p1);
    VPSS_Sys_SetDbLumHorDeltaLutP0(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p0);
    VPSS_Sys_SetDbLumHorDeltaLutP15(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p15);
    VPSS_Sys_SetDbLumHorDeltaLutP14(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p14);
    VPSS_Sys_SetDbLumHorDeltaLutP13(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p13);
    VPSS_Sys_SetDbLumHorDeltaLutP12(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p12);
    VPSS_Sys_SetDbLumHorDeltaLutP11(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p11);
    VPSS_Sys_SetDbLumHorDeltaLutP10(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p10);
    VPSS_Sys_SetDbLumHorDeltaLutP9(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p9);
    VPSS_Sys_SetDbLumHorDeltaLutP8(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p8);
    VPSS_Sys_SetDbLumHStrFadeLutP9(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p9);
    VPSS_Sys_SetDbLumHStrFadeLutP8(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p8);
    VPSS_Sys_SetDbLumHStrFadeLutP7(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p7);
    VPSS_Sys_SetDbLumHStrFadeLutP6(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p6);
    VPSS_Sys_SetDbLumHStrFadeLutP5(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p5);
    VPSS_Sys_SetDbLumHStrFadeLutP4(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p4);
    VPSS_Sys_SetDbLumHStrFadeLutP3(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p3);
    VPSS_Sys_SetDbLumHStrFadeLutP2(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p2);
    VPSS_Sys_SetDbLumHStrFadeLutP1(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p1);
    VPSS_Sys_SetDbLumHStrFadeLutP0(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p0);
    VPSS_Sys_SetDbLumHStrFadeLutP11(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p11);
    VPSS_Sys_SetDbLumHStrFadeLutP10(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p10);
    VPSS_Sys_SetDbDirStrGainLutP7(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p7);
    VPSS_Sys_SetDbDirStrGainLutP6(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p6);
    VPSS_Sys_SetDbDirStrGainLutP5(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p5);
    VPSS_Sys_SetDbDirStrGainLutP4(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p4);
    VPSS_Sys_SetDbDirStrGainLutP3(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p3);
    VPSS_Sys_SetDbDirStrGainLutP2(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p2);
    VPSS_Sys_SetDbDirStrGainLutP1(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p1);
    VPSS_Sys_SetDbDirStrGainLutP0(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p0);
    VPSS_Sys_SetDbDirStrLutP7(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p7);
    VPSS_Sys_SetDbDirStrLutP6(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p6);
    VPSS_Sys_SetDbDirStrLutP5(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p5);
    VPSS_Sys_SetDbDirStrLutP4(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p4);
    VPSS_Sys_SetDbDirStrLutP3(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p3);
    VPSS_Sys_SetDbDirStrLutP2(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p2);
    VPSS_Sys_SetDbDirStrLutP1(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p1);
    VPSS_Sys_SetDbDirStrLutP0(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p0);
    VPSS_Sys_SetDbDirStrLutP15(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p15);
    VPSS_Sys_SetDbDirStrLutP14(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p14);
    VPSS_Sys_SetDbDirStrLutP13(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p13);
    VPSS_Sys_SetDbDirStrLutP12(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p12);
    VPSS_Sys_SetDbDirStrLutP11(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p11);
    VPSS_Sys_SetDbDirStrLutP10(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p10);
    VPSS_Sys_SetDbDirStrLutP9(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p9);
    VPSS_Sys_SetDbDirStrLutP8(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p8);
    VPSS_Sys_SetDbdHyThdEdge(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_hy_thd_edge);
    VPSS_Sys_SetDbdHyThdTxt(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_hy_thd_txt);
    VPSS_Sys_SetDbdDetLutWgt7(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[7]);
    VPSS_Sys_SetDbdDetLutWgt6(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[6]);
    VPSS_Sys_SetDbdDetLutWgt5(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[5]);
    VPSS_Sys_SetDbdDetLutWgt4(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[4]);
    VPSS_Sys_SetDbdDetLutWgt3(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[3]);
    VPSS_Sys_SetDbdDetLutWgt2(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[2]);
    VPSS_Sys_SetDbdDetLutWgt1(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[1]);
    VPSS_Sys_SetDbdDetLutWgt0(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[0]);
    VPSS_Sys_SetDbdDetLutWgt15(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[15]);
    VPSS_Sys_SetDbdDetLutWgt14(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[14]);
    VPSS_Sys_SetDbdDetLutWgt13(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[13]);
    VPSS_Sys_SetDbdDetLutWgt12(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[12]);
    VPSS_Sys_SetDbdDetLutWgt11(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[11]);
    VPSS_Sys_SetDbdDetLutWgt10(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[10]);
    VPSS_Sys_SetDbdDetLutWgt9(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[9]);
    VPSS_Sys_SetDbdDetLutWgt8(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt[8]);
    VPSS_Sys_SetDbdHyRtnBdTxt(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_hy_rtn_bd_txt);
    VPSS_Sys_SetDbdHyTstBlkNum(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_hy_tst_blk_num);
    VPSS_Sys_SetDbdHyRdx8binLut1(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[1]);
    VPSS_Sys_SetDbdHyRdx8binLut0(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[0]);
    VPSS_Sys_SetDbdHyRdx8binLut3(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[3]);
    VPSS_Sys_SetDbdHyRdx8binLut2(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[2]);
    VPSS_Sys_SetDbdHyRdx8binLut5(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[5]);
    VPSS_Sys_SetDbdHyRdx8binLut4(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[4]);
    VPSS_Sys_SetDbdHyRdx8binLut6(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut[6]);
    VPSS_Sys_SetDbdHyMaxBlkSize(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_hy_max_blk_size);
    VPSS_Sys_SetDbdMinBlkSize(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_min_blk_size);
    VPSS_Sys_SetDbdThrFlat(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dbd_thr_flat);
    VPSS_Sys_SetDmOppAngCtrstDiv(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_opp_ang_ctrst_div);
    VPSS_Sys_SetDmOppAngCtrstT(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_opp_ang_ctrst_t);
    VPSS_Sys_SetDmCtrstThresh(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_ctrst_thresh);
    VPSS_Sys_SetDmGradSubRatio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_grad_sub_ratio);
    VPSS_Sys_SetDmGlobalStr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_global_str);
    VPSS_Sys_SetDmInitValStep(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_init_val_step);
    VPSS_Sys_SetDmMmfSet(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_set);
    VPSS_Sys_SetDmSwWhtLutP3(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p3);
    VPSS_Sys_SetDmSwWhtLutP2(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p2);
    VPSS_Sys_SetDmSwWhtLutP1(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p1);
    VPSS_Sys_SetDmSwWhtLutP0(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p0);
    VPSS_Sys_SetDmLimitT10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_limit_t_10);
    VPSS_Sys_SetDmLimitT(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_limit_t);
    VPSS_Sys_SetDmSwWhtLutP4(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p4);
    VPSS_Sys_SetDmDirStrGainLutP7(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p7);
    VPSS_Sys_SetDmDirStrGainLutP6(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p6);
    VPSS_Sys_SetDmDirStrGainLutP5(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p5);
    VPSS_Sys_SetDmDirStrGainLutP4(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p4);
    VPSS_Sys_SetDmDirStrGainLutP3(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p3);
    VPSS_Sys_SetDmDirStrGainLutP2(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p2);
    VPSS_Sys_SetDmDirStrGainLutP1(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p1);
    VPSS_Sys_SetDmDirStrGainLutP0(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p0);
    VPSS_Sys_SetDmDirStrLutP7(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p7);
    VPSS_Sys_SetDmDirStrLutP6(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p6);
    VPSS_Sys_SetDmDirStrLutP5(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p5);
    VPSS_Sys_SetDmDirStrLutP4(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p4);
    VPSS_Sys_SetDmDirStrLutP3(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p3);
    VPSS_Sys_SetDmDirStrLutP2(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p2);
    VPSS_Sys_SetDmDirStrLutP1(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p1);
    VPSS_Sys_SetDmDirStrLutP0(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p0);
    VPSS_Sys_SetDmDirStrLutP15(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p15);
    VPSS_Sys_SetDmDirStrLutP14(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p14);
    VPSS_Sys_SetDmDirStrLutP13(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p13);
    VPSS_Sys_SetDmDirStrLutP12(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p12);
    VPSS_Sys_SetDmDirStrLutP11(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p11);
    VPSS_Sys_SetDmDirStrLutP10(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p10);
    VPSS_Sys_SetDmDirStrLutP9(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p9);
    VPSS_Sys_SetDmDirStrLutP8(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p8);
    VPSS_Sys_SetDmMmfLimitEn(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_limit_en);
    VPSS_Sys_SetDmMndirOppCtrstT(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mndir_opp_ctrst_t);
    VPSS_Sys_SetDmCswTrsntSt10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_csw_trsnt_st_10);
    VPSS_Sys_SetDmLswRatio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_lsw_ratio);
    VPSS_Sys_SetDmCswTrsntSt(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_csw_trsnt_st);
    VPSS_Sys_SetDmLwCtrstT10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_lw_ctrst_t_10);
    VPSS_Sys_SetDmLwCtrstT(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_lw_ctrst_t);
    VPSS_Sys_SetDmCswTrsntLt(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_csw_trsnt_lt);
    VPSS_Sys_SetDmMmfLr10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_lr_10);
    VPSS_Sys_SetDmMmfLr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_lr);
    VPSS_Sys_SetDmCswTrsntLt10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_csw_trsnt_lt_10);
    VPSS_Sys_SetDmMmfSr10(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_sr_10);
    VPSS_Sys_SetDmMmfSr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_mmf_sr);
    VPSS_Sys_SetDmDirBlendStr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_dir_blend_str);
    VPSS_Sys_SetDmLimResBlendStr2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_lim_res_blend_str2);
    VPSS_Sys_SetDmLimResBlendStr1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_lim_res_blend_str1);
    VPSS_Sys_SetDmLimitLswRatio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->dm_limit_lsw_ratio);
    VPSS_Sys_SetDmTransBandLutP4(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p4);
    VPSS_Sys_SetDmTransBandLutP3(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p3);
    VPSS_Sys_SetDmTransBandLutP2(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p2);
    VPSS_Sys_SetDmTransBandLutP1(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p1);
    VPSS_Sys_SetDmTransBandLutP0(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p0);
    VPSS_Sys_SetDmTransBandLutP9(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p9);
    VPSS_Sys_SetDmTransBandLutP8(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p8);
    VPSS_Sys_SetDmTransBandLutP7(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p7);
    VPSS_Sys_SetDmTransBandLutP6(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p6);
    VPSS_Sys_SetDmTransBandLutP5(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p5);
    VPSS_Sys_SetDmTransBandLutP14(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p14);
    VPSS_Sys_SetDmTransBandLutP13(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p13);
    VPSS_Sys_SetDmTransBandLutP12(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p12);
    VPSS_Sys_SetDmTransBandLutP11(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p11);
    VPSS_Sys_SetDmTransBandLutP10(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p10);
    VPSS_Sys_SetDmTransBandLutP19(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p19);
    VPSS_Sys_SetDmTransBandLutP18(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p18);
    VPSS_Sys_SetDmTransBandLutP17(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p17);
    VPSS_Sys_SetDmTransBandLutP16(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p16);
    VPSS_Sys_SetDmTransBandLutP15(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p15);
    VPSS_Sys_SetDmTransBandLutP24(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p24);
    VPSS_Sys_SetDmTransBandLutP23(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p23);
    VPSS_Sys_SetDmTransBandLutP22(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p22);
    VPSS_Sys_SetDmTransBandLutP21(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p21);
    VPSS_Sys_SetDmTransBandLutP20(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p20);
    VPSS_Sys_SetDmTransBandLutP29(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p29);
    VPSS_Sys_SetDmTransBandLutP28(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p28);
    VPSS_Sys_SetDmTransBandLutP27(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p27);
    VPSS_Sys_SetDmTransBandLutP26(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p26);
    VPSS_Sys_SetDmTransBandLutP25(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p25);
    VPSS_Sys_SetDmTransBandLutP30(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p30);
    VPSS_Sys_SetVpssDbBordFlag0(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_0);
    VPSS_Sys_SetVpssDbBordFlag1(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_1);
    VPSS_Sys_SetVpssDbBordFlag2(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_2);
    VPSS_Sys_SetVpssDbBordFlag3(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_3);
    VPSS_Sys_SetVpssDbBordFlag4(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_4);
    VPSS_Sys_SetVpssDbBordFlag5(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_5);
    VPSS_Sys_SetVpssDbBordFlag6(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_6);
    VPSS_Sys_SetVpssDbBordFlag7(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_7);
    VPSS_Sys_SetVpssDbBordFlag8(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_8);
    VPSS_Sys_SetVpssDbBordFlag9(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_9);
    VPSS_Sys_SetVpssDbBordFlag10(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_10);
    VPSS_Sys_SetVpssDbBordFlag11(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_11);
    VPSS_Sys_SetVpssDbBordFlag12(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_12);
    VPSS_Sys_SetVpssDbBordFlag13(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_13);
    VPSS_Sys_SetVpssDbBordFlag14(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_14);
    VPSS_Sys_SetVpssDbBordFlag15(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_15);
    VPSS_Sys_SetVpssDbBordFlag16(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_16);
    VPSS_Sys_SetVpssDbBordFlag17(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_17);
    VPSS_Sys_SetVpssDbBordFlag18(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_18);
    VPSS_Sys_SetVpssDbBordFlag19(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_19);
    VPSS_Sys_SetVpssDbBordFlag20(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_20);
    VPSS_Sys_SetVpssDbBordFlag21(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_21);
    VPSS_Sys_SetVpssDbBordFlag22(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_22);
    VPSS_Sys_SetVpssDbBordFlag23(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_23);
    VPSS_Sys_SetVpssDbBordFlag24(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_24);
    VPSS_Sys_SetVpssDbBordFlag25(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_25);
    VPSS_Sys_SetVpssDbBordFlag26(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_26);
    VPSS_Sys_SetVpssDbBordFlag27(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_27);
    VPSS_Sys_SetVpssDbBordFlag28(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_28);
    VPSS_Sys_SetVpssDbBordFlag29(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_29);
    VPSS_Sys_SetVpssDbBordFlag30(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_30);
    VPSS_Sys_SetVpssDbBordFlag31(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_31);
    VPSS_Sys_SetTestEn(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->test_en);
    VPSS_Sys_SetEdgeprefilteren(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgeprefilteren);
    VPSS_Sys_SetColorweighten(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->colorweighten);
    VPSS_Sys_SetMotionedgeweighten(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->motionedgeweighten);
    VPSS_Sys_SetCnr2den(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cnr2den);
    VPSS_Sys_SetYnr2den(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ynr2den);
    VPSS_Sys_SetEdgeoriratio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgeoriratio);
    VPSS_Sys_SetEdgeminratio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgeminratio);
    VPSS_Sys_SetEdgemaxratio(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemaxratio);
    VPSS_Sys_SetEdgeoristrength(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgeoristrength);
    VPSS_Sys_SetEdgeminstrength(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgeminstrength);
    VPSS_Sys_SetEdgemaxstrength(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemaxstrength);
    VPSS_Sys_SetEdgestrth3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrth3);
    VPSS_Sys_SetEdgestrth2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrth2);
    VPSS_Sys_SetEdgestrth1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrth1);
    VPSS_Sys_SetEdgestrk3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrk3);
    VPSS_Sys_SetEdgestrk2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrk2);
    VPSS_Sys_SetEdgestrk1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgestrk1);
    VPSS_Sys_SetEdgemeanth3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth3);
    VPSS_Sys_SetEdgemeanth2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth2);
    VPSS_Sys_SetEdgemeanth1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth1);
    VPSS_Sys_SetEdgemeanth6(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth6);
    VPSS_Sys_SetEdgemeanth5(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth5);
    VPSS_Sys_SetEdgemeanth4(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth4);
    VPSS_Sys_SetEdgemeanth8(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth8);
    VPSS_Sys_SetEdgemeanth7(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeanth7);
    VPSS_Sys_SetEdgemeank4(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank4);
    VPSS_Sys_SetEdgemeank3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank3);
    VPSS_Sys_SetEdgemeank2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank2);
    VPSS_Sys_SetEdgemeank1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank1);
    VPSS_Sys_SetEdgemeank8(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank8);
    VPSS_Sys_SetEdgemeank7(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank7);
    VPSS_Sys_SetEdgemeank6(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank6);
    VPSS_Sys_SetEdgemeank5(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edgemeank5);
    VPSS_Sys_SetC2dwinheight(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->c2dwinheight);
    VPSS_Sys_SetC2dwinwidth(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->c2dwinwidth);
    VPSS_Sys_SetY2dwinheight(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->y2dwinheight);
    VPSS_Sys_SetY2dwinwidth(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->y2dwinwidth);
    VPSS_Sys_SetCsnrstr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->csnrstr);
    VPSS_Sys_SetYsnrstr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ysnrstr);
    VPSS_Sys_SetStroffset3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->stroffset3);
    VPSS_Sys_SetStroffset2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->stroffset2);
    VPSS_Sys_SetStroffset1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->stroffset1);
    VPSS_Sys_SetStroffset0(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->stroffset0);
    VPSS_Sys_SetCstradjust(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cstradjust);
    VPSS_Sys_SetYstradjust(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ystradjust);
    VPSS_Sys_SetScenechangeth(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechangeth);
    VPSS_Sys_SetRatio3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio3);
    VPSS_Sys_SetRatio2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio2);
    VPSS_Sys_SetRatio1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio1);
    VPSS_Sys_SetRatio6(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio6);
    VPSS_Sys_SetRatio5(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio5);
    VPSS_Sys_SetRatio4(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio4);
    VPSS_Sys_SetRatio8(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio8);
    VPSS_Sys_SetRatio7(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->ratio7);
    VPSS_Sys_SetEdge3(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edge3);
    VPSS_Sys_SetEdge2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edge2);
    VPSS_Sys_SetEdge1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->edge1);
    VPSS_Sys_SetTestColorCr(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->test_color_cr);
    VPSS_Sys_SetTestColorCb(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->test_color_cb);
    VPSS_Sys_SetScenechangeMode2En(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_mode2_en);
    VPSS_Sys_SetScenechangeBldcore(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_bldcore);
    VPSS_Sys_SetScenechangeBldk(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_bldk);
    VPSS_Sys_SetScenechangeMode1En(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_mode1_en);
    VPSS_Sys_SetScenechangeEn(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_en);
    VPSS_Sys_SetScenechangeInfo(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->scenechange_info);
    VPSS_Sys_SetMotionalpha(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->motionalpha);
    VPSS_Sys_SetCbcrWeight1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cbcr_weight1);
    VPSS_Sys_SetCrEnd1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cr_end1);
    VPSS_Sys_SetCbEnd1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cb_end1);
    VPSS_Sys_SetCrBegin1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cr_begin1);
    VPSS_Sys_SetCbBegin1(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cb_begin1);
    VPSS_Sys_SetCbcrWeight2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cbcr_weight2);
    VPSS_Sys_SetCrEnd2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cr_end2);
    VPSS_Sys_SetCbEnd2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cb_end2);
    VPSS_Sys_SetCrBegin2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cr_begin2);
    VPSS_Sys_SetCbBegin2(pstVpssRegs,  u32AddrOffset,  pstTnrRegType->cb_begin2);
    VPSS_Sys_SetMotionEdgeLut07(pstVpssRegs,  u32AddrOffset,  motion_edge_lut07);
    VPSS_Sys_SetMotionEdgeLut06(pstVpssRegs,  u32AddrOffset,  motion_edge_lut06);
    VPSS_Sys_SetMotionEdgeLut05(pstVpssRegs,  u32AddrOffset,  motion_edge_lut05);
    VPSS_Sys_SetMotionEdgeLut04(pstVpssRegs,  u32AddrOffset,  motion_edge_lut04);
    VPSS_Sys_SetMotionEdgeLut03(pstVpssRegs,  u32AddrOffset,  motion_edge_lut03);
    VPSS_Sys_SetMotionEdgeLut02(pstVpssRegs,  u32AddrOffset,  motion_edge_lut02);
    VPSS_Sys_SetMotionEdgeLut01(pstVpssRegs,  u32AddrOffset,  motion_edge_lut01);
    VPSS_Sys_SetMotionEdgeLut00(pstVpssRegs,  u32AddrOffset,  motion_edge_lut00);
    VPSS_Sys_SetMotionEdgeLut0f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0f);
    VPSS_Sys_SetMotionEdgeLut0e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0e);
    VPSS_Sys_SetMotionEdgeLut0d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0d);
    VPSS_Sys_SetMotionEdgeLut0c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0c);
    VPSS_Sys_SetMotionEdgeLut0b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0b);
    VPSS_Sys_SetMotionEdgeLut0a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0a);
    VPSS_Sys_SetMotionEdgeLut09(pstVpssRegs,  u32AddrOffset,  motion_edge_lut09);
    VPSS_Sys_SetMotionEdgeLut08(pstVpssRegs,  u32AddrOffset,  motion_edge_lut08);
    VPSS_Sys_SetMotionEdgeLut17(pstVpssRegs,  u32AddrOffset,  motion_edge_lut17);
    VPSS_Sys_SetMotionEdgeLut16(pstVpssRegs,  u32AddrOffset,  motion_edge_lut16);
    VPSS_Sys_SetMotionEdgeLut15(pstVpssRegs,  u32AddrOffset,  motion_edge_lut15);
    VPSS_Sys_SetMotionEdgeLut14(pstVpssRegs,  u32AddrOffset,  motion_edge_lut14);
    VPSS_Sys_SetMotionEdgeLut13(pstVpssRegs,  u32AddrOffset,  motion_edge_lut13);
    VPSS_Sys_SetMotionEdgeLut12(pstVpssRegs,  u32AddrOffset,  motion_edge_lut12);
    VPSS_Sys_SetMotionEdgeLut11(pstVpssRegs,  u32AddrOffset,  motion_edge_lut11);
    VPSS_Sys_SetMotionEdgeLut10(pstVpssRegs,  u32AddrOffset,  motion_edge_lut10);
    VPSS_Sys_SetMotionEdgeLut1f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1f);
    VPSS_Sys_SetMotionEdgeLut1e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1e);
    VPSS_Sys_SetMotionEdgeLut1d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1d);
    VPSS_Sys_SetMotionEdgeLut1c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1c);
    VPSS_Sys_SetMotionEdgeLut1b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1b);
    VPSS_Sys_SetMotionEdgeLut1a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1a);
    VPSS_Sys_SetMotionEdgeLut19(pstVpssRegs,  u32AddrOffset,  motion_edge_lut19);
    VPSS_Sys_SetMotionEdgeLut18(pstVpssRegs,  u32AddrOffset,  motion_edge_lut18);
    VPSS_Sys_SetMotionEdgeLut27(pstVpssRegs,  u32AddrOffset,  motion_edge_lut27);
    VPSS_Sys_SetMotionEdgeLut26(pstVpssRegs,  u32AddrOffset,  motion_edge_lut26);
    VPSS_Sys_SetMotionEdgeLut25(pstVpssRegs,  u32AddrOffset,  motion_edge_lut25);
    VPSS_Sys_SetMotionEdgeLut24(pstVpssRegs,  u32AddrOffset,  motion_edge_lut24);
    VPSS_Sys_SetMotionEdgeLut23(pstVpssRegs,  u32AddrOffset,  motion_edge_lut23);
    VPSS_Sys_SetMotionEdgeLut22(pstVpssRegs,  u32AddrOffset,  motion_edge_lut22);
    VPSS_Sys_SetMotionEdgeLut21(pstVpssRegs,  u32AddrOffset,  motion_edge_lut21);
    VPSS_Sys_SetMotionEdgeLut20(pstVpssRegs,  u32AddrOffset,  motion_edge_lut20);
    VPSS_Sys_SetMotionEdgeLut2f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2f);
    VPSS_Sys_SetMotionEdgeLut2e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2e);
    VPSS_Sys_SetMotionEdgeLut2d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2d);
    VPSS_Sys_SetMotionEdgeLut2c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2c);
    VPSS_Sys_SetMotionEdgeLut2b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2b);
    VPSS_Sys_SetMotionEdgeLut2a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2a);
    VPSS_Sys_SetMotionEdgeLut29(pstVpssRegs,  u32AddrOffset,  motion_edge_lut29);
    VPSS_Sys_SetMotionEdgeLut28(pstVpssRegs,  u32AddrOffset,  motion_edge_lut28);
    VPSS_Sys_SetMotionEdgeLut37(pstVpssRegs,  u32AddrOffset,  motion_edge_lut37);
    VPSS_Sys_SetMotionEdgeLut36(pstVpssRegs,  u32AddrOffset,  motion_edge_lut36);
    VPSS_Sys_SetMotionEdgeLut35(pstVpssRegs,  u32AddrOffset,  motion_edge_lut35);
    VPSS_Sys_SetMotionEdgeLut34(pstVpssRegs,  u32AddrOffset,  motion_edge_lut34);
    VPSS_Sys_SetMotionEdgeLut33(pstVpssRegs,  u32AddrOffset,  motion_edge_lut33);
    VPSS_Sys_SetMotionEdgeLut32(pstVpssRegs,  u32AddrOffset,  motion_edge_lut32);
    VPSS_Sys_SetMotionEdgeLut31(pstVpssRegs,  u32AddrOffset,  motion_edge_lut31);
    VPSS_Sys_SetMotionEdgeLut30(pstVpssRegs,  u32AddrOffset,  motion_edge_lut30);
    VPSS_Sys_SetMotionEdgeLut3f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3f);
    VPSS_Sys_SetMotionEdgeLut3e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3e);
    VPSS_Sys_SetMotionEdgeLut3d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3d);
    VPSS_Sys_SetMotionEdgeLut3c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3c);
    VPSS_Sys_SetMotionEdgeLut3b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3b);
    VPSS_Sys_SetMotionEdgeLut3a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3a);
    VPSS_Sys_SetMotionEdgeLut39(pstVpssRegs,  u32AddrOffset,  motion_edge_lut39);
    VPSS_Sys_SetMotionEdgeLut38(pstVpssRegs,  u32AddrOffset,  motion_edge_lut38);
    VPSS_Sys_SetMotionEdgeLut47(pstVpssRegs,  u32AddrOffset,  motion_edge_lut47);
    VPSS_Sys_SetMotionEdgeLut46(pstVpssRegs,  u32AddrOffset,  motion_edge_lut46);
    VPSS_Sys_SetMotionEdgeLut45(pstVpssRegs,  u32AddrOffset,  motion_edge_lut45);
    VPSS_Sys_SetMotionEdgeLut44(pstVpssRegs,  u32AddrOffset,  motion_edge_lut44);
    VPSS_Sys_SetMotionEdgeLut43(pstVpssRegs,  u32AddrOffset,  motion_edge_lut43);
    VPSS_Sys_SetMotionEdgeLut42(pstVpssRegs,  u32AddrOffset,  motion_edge_lut42);
    VPSS_Sys_SetMotionEdgeLut41(pstVpssRegs,  u32AddrOffset,  motion_edge_lut41);
    VPSS_Sys_SetMotionEdgeLut40(pstVpssRegs,  u32AddrOffset,  motion_edge_lut40);
    VPSS_Sys_SetMotionEdgeLut4f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4f);
    VPSS_Sys_SetMotionEdgeLut4e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4e);
    VPSS_Sys_SetMotionEdgeLut4d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4d);
    VPSS_Sys_SetMotionEdgeLut4c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4c);
    VPSS_Sys_SetMotionEdgeLut4b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4b);
    VPSS_Sys_SetMotionEdgeLut4a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4a);
    VPSS_Sys_SetMotionEdgeLut49(pstVpssRegs,  u32AddrOffset,  motion_edge_lut49);
    VPSS_Sys_SetMotionEdgeLut48(pstVpssRegs,  u32AddrOffset,  motion_edge_lut48);
    VPSS_Sys_SetMotionEdgeLut57(pstVpssRegs,  u32AddrOffset,  motion_edge_lut57);
    VPSS_Sys_SetMotionEdgeLut56(pstVpssRegs,  u32AddrOffset,  motion_edge_lut56);
    VPSS_Sys_SetMotionEdgeLut55(pstVpssRegs,  u32AddrOffset,  motion_edge_lut55);
    VPSS_Sys_SetMotionEdgeLut54(pstVpssRegs,  u32AddrOffset,  motion_edge_lut54);
    VPSS_Sys_SetMotionEdgeLut53(pstVpssRegs,  u32AddrOffset,  motion_edge_lut53);
    VPSS_Sys_SetMotionEdgeLut52(pstVpssRegs,  u32AddrOffset,  motion_edge_lut52);
    VPSS_Sys_SetMotionEdgeLut51(pstVpssRegs,  u32AddrOffset,  motion_edge_lut51);
    VPSS_Sys_SetMotionEdgeLut50(pstVpssRegs,  u32AddrOffset,  motion_edge_lut50);
    VPSS_Sys_SetMotionEdgeLut5f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5f);
    VPSS_Sys_SetMotionEdgeLut5e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5e);
    VPSS_Sys_SetMotionEdgeLut5d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5d);
    VPSS_Sys_SetMotionEdgeLut5c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5c);
    VPSS_Sys_SetMotionEdgeLut5b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5b);
    VPSS_Sys_SetMotionEdgeLut5a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5a);
    VPSS_Sys_SetMotionEdgeLut59(pstVpssRegs,  u32AddrOffset,  motion_edge_lut59);
    VPSS_Sys_SetMotionEdgeLut58(pstVpssRegs,  u32AddrOffset,  motion_edge_lut58);
    VPSS_Sys_SetMotionEdgeLut67(pstVpssRegs,  u32AddrOffset,  motion_edge_lut67);
    VPSS_Sys_SetMotionEdgeLut66(pstVpssRegs,  u32AddrOffset,  motion_edge_lut66);
    VPSS_Sys_SetMotionEdgeLut65(pstVpssRegs,  u32AddrOffset,  motion_edge_lut65);
    VPSS_Sys_SetMotionEdgeLut64(pstVpssRegs,  u32AddrOffset,  motion_edge_lut64);
    VPSS_Sys_SetMotionEdgeLut63(pstVpssRegs,  u32AddrOffset,  motion_edge_lut63);
    VPSS_Sys_SetMotionEdgeLut62(pstVpssRegs,  u32AddrOffset,  motion_edge_lut62);
    VPSS_Sys_SetMotionEdgeLut61(pstVpssRegs,  u32AddrOffset,  motion_edge_lut61);
    VPSS_Sys_SetMotionEdgeLut60(pstVpssRegs,  u32AddrOffset,  motion_edge_lut60);
    VPSS_Sys_SetMotionEdgeLut6f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6f);
    VPSS_Sys_SetMotionEdgeLut6e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6e);
    VPSS_Sys_SetMotionEdgeLut6d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6d);
    VPSS_Sys_SetMotionEdgeLut6c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6c);
    VPSS_Sys_SetMotionEdgeLut6b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6b);
    VPSS_Sys_SetMotionEdgeLut6a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6a);
    VPSS_Sys_SetMotionEdgeLut69(pstVpssRegs,  u32AddrOffset,  motion_edge_lut69);
    VPSS_Sys_SetMotionEdgeLut68(pstVpssRegs,  u32AddrOffset,  motion_edge_lut68);
    VPSS_Sys_SetMotionEdgeLut77(pstVpssRegs,  u32AddrOffset,  motion_edge_lut77);
    VPSS_Sys_SetMotionEdgeLut76(pstVpssRegs,  u32AddrOffset,  motion_edge_lut76);
    VPSS_Sys_SetMotionEdgeLut75(pstVpssRegs,  u32AddrOffset,  motion_edge_lut75);
    VPSS_Sys_SetMotionEdgeLut74(pstVpssRegs,  u32AddrOffset,  motion_edge_lut74);
    VPSS_Sys_SetMotionEdgeLut73(pstVpssRegs,  u32AddrOffset,  motion_edge_lut73);
    VPSS_Sys_SetMotionEdgeLut72(pstVpssRegs,  u32AddrOffset,  motion_edge_lut72);
    VPSS_Sys_SetMotionEdgeLut71(pstVpssRegs,  u32AddrOffset,  motion_edge_lut71);
    VPSS_Sys_SetMotionEdgeLut70(pstVpssRegs,  u32AddrOffset,  motion_edge_lut70);
    VPSS_Sys_SetMotionEdgeLut7f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7f);
    VPSS_Sys_SetMotionEdgeLut7e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7e);
    VPSS_Sys_SetMotionEdgeLut7d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7d);
    VPSS_Sys_SetMotionEdgeLut7c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7c);
    VPSS_Sys_SetMotionEdgeLut7b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7b);
    VPSS_Sys_SetMotionEdgeLut7a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7a);
    VPSS_Sys_SetMotionEdgeLut79(pstVpssRegs,  u32AddrOffset,  motion_edge_lut79);
    VPSS_Sys_SetMotionEdgeLut78(pstVpssRegs,  u32AddrOffset,  motion_edge_lut78);
    VPSS_Sys_SetMotionEdgeLut87(pstVpssRegs,  u32AddrOffset,  motion_edge_lut87);
    VPSS_Sys_SetMotionEdgeLut86(pstVpssRegs,  u32AddrOffset,  motion_edge_lut86);
    VPSS_Sys_SetMotionEdgeLut85(pstVpssRegs,  u32AddrOffset,  motion_edge_lut85);
    VPSS_Sys_SetMotionEdgeLut84(pstVpssRegs,  u32AddrOffset,  motion_edge_lut84);
    VPSS_Sys_SetMotionEdgeLut83(pstVpssRegs,  u32AddrOffset,  motion_edge_lut83);
    VPSS_Sys_SetMotionEdgeLut82(pstVpssRegs,  u32AddrOffset,  motion_edge_lut82);
    VPSS_Sys_SetMotionEdgeLut81(pstVpssRegs,  u32AddrOffset,  motion_edge_lut81);
    VPSS_Sys_SetMotionEdgeLut80(pstVpssRegs,  u32AddrOffset,  motion_edge_lut80);
    VPSS_Sys_SetMotionEdgeLut8f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8f);
    VPSS_Sys_SetMotionEdgeLut8e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8e);
    VPSS_Sys_SetMotionEdgeLut8d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8d);
    VPSS_Sys_SetMotionEdgeLut8c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8c);
    VPSS_Sys_SetMotionEdgeLut8b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8b);
    VPSS_Sys_SetMotionEdgeLut8a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8a);
    VPSS_Sys_SetMotionEdgeLut89(pstVpssRegs,  u32AddrOffset,  motion_edge_lut89);
    VPSS_Sys_SetMotionEdgeLut88(pstVpssRegs,  u32AddrOffset,  motion_edge_lut88);
    VPSS_Sys_SetMotionEdgeLut97(pstVpssRegs,  u32AddrOffset,  motion_edge_lut97);
    VPSS_Sys_SetMotionEdgeLut96(pstVpssRegs,  u32AddrOffset,  motion_edge_lut96);
    VPSS_Sys_SetMotionEdgeLut95(pstVpssRegs,  u32AddrOffset,  motion_edge_lut95);
    VPSS_Sys_SetMotionEdgeLut94(pstVpssRegs,  u32AddrOffset,  motion_edge_lut94);
    VPSS_Sys_SetMotionEdgeLut93(pstVpssRegs,  u32AddrOffset,  motion_edge_lut93);
    VPSS_Sys_SetMotionEdgeLut92(pstVpssRegs,  u32AddrOffset,  motion_edge_lut92);
    VPSS_Sys_SetMotionEdgeLut91(pstVpssRegs,  u32AddrOffset,  motion_edge_lut91);
    VPSS_Sys_SetMotionEdgeLut90(pstVpssRegs,  u32AddrOffset,  motion_edge_lut90);
    VPSS_Sys_SetMotionEdgeLut9f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9f);
    VPSS_Sys_SetMotionEdgeLut9e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9e);
    VPSS_Sys_SetMotionEdgeLut9d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9d);
    VPSS_Sys_SetMotionEdgeLut9c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9c);
    VPSS_Sys_SetMotionEdgeLut9b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9b);
    VPSS_Sys_SetMotionEdgeLut9a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9a);
    VPSS_Sys_SetMotionEdgeLut99(pstVpssRegs,  u32AddrOffset,  motion_edge_lut99);
    VPSS_Sys_SetMotionEdgeLut98(pstVpssRegs,  u32AddrOffset,  motion_edge_lut98);
    VPSS_Sys_SetMotionEdgeLuta7(pstVpssRegs,  u32AddrOffset,  motion_edge_luta7);
    VPSS_Sys_SetMotionEdgeLuta6(pstVpssRegs,  u32AddrOffset,  motion_edge_luta6);
    VPSS_Sys_SetMotionEdgeLuta5(pstVpssRegs,  u32AddrOffset,  motion_edge_luta5);
    VPSS_Sys_SetMotionEdgeLuta4(pstVpssRegs,  u32AddrOffset,  motion_edge_luta4);
    VPSS_Sys_SetMotionEdgeLuta3(pstVpssRegs,  u32AddrOffset,  motion_edge_luta3);
    VPSS_Sys_SetMotionEdgeLuta2(pstVpssRegs,  u32AddrOffset,  motion_edge_luta2);
    VPSS_Sys_SetMotionEdgeLuta1(pstVpssRegs,  u32AddrOffset,  motion_edge_luta1);
    VPSS_Sys_SetMotionEdgeLuta0(pstVpssRegs,  u32AddrOffset,  motion_edge_luta0);
    VPSS_Sys_SetMotionEdgeLutaf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutaf);
    VPSS_Sys_SetMotionEdgeLutae(pstVpssRegs,  u32AddrOffset,  motion_edge_lutae);
    VPSS_Sys_SetMotionEdgeLutad(pstVpssRegs,  u32AddrOffset,  motion_edge_lutad);
    VPSS_Sys_SetMotionEdgeLutac(pstVpssRegs,  u32AddrOffset,  motion_edge_lutac);
    VPSS_Sys_SetMotionEdgeLutab(pstVpssRegs,  u32AddrOffset,  motion_edge_lutab);
    VPSS_Sys_SetMotionEdgeLutaa(pstVpssRegs,  u32AddrOffset,  motion_edge_lutaa);
    VPSS_Sys_SetMotionEdgeLuta9(pstVpssRegs,  u32AddrOffset,  motion_edge_luta9);
    VPSS_Sys_SetMotionEdgeLuta8(pstVpssRegs,  u32AddrOffset,  motion_edge_luta8);
    VPSS_Sys_SetMotionEdgeLutb7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb7);
    VPSS_Sys_SetMotionEdgeLutb6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb6);
    VPSS_Sys_SetMotionEdgeLutb5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb5);
    VPSS_Sys_SetMotionEdgeLutb4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb4);
    VPSS_Sys_SetMotionEdgeLutb3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb3);
    VPSS_Sys_SetMotionEdgeLutb2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb2);
    VPSS_Sys_SetMotionEdgeLutb1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb1);
    VPSS_Sys_SetMotionEdgeLutb0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb0);
    VPSS_Sys_SetMotionEdgeLutbf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbf);
    VPSS_Sys_SetMotionEdgeLutbe(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbe);
    VPSS_Sys_SetMotionEdgeLutbd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbd);
    VPSS_Sys_SetMotionEdgeLutbc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbc);
    VPSS_Sys_SetMotionEdgeLutbb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbb);
    VPSS_Sys_SetMotionEdgeLutba(pstVpssRegs,  u32AddrOffset,  motion_edge_lutba);
    VPSS_Sys_SetMotionEdgeLutb9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb9);
    VPSS_Sys_SetMotionEdgeLutb8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb8);
    VPSS_Sys_SetMotionEdgeLutc7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc7);
    VPSS_Sys_SetMotionEdgeLutc6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc6);
    VPSS_Sys_SetMotionEdgeLutc5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc5);
    VPSS_Sys_SetMotionEdgeLutc4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc4);
    VPSS_Sys_SetMotionEdgeLutc3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc3);
    VPSS_Sys_SetMotionEdgeLutc2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc2);
    VPSS_Sys_SetMotionEdgeLutc1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc1);
    VPSS_Sys_SetMotionEdgeLutc0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc0);
    VPSS_Sys_SetMotionEdgeLutcf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcf);
    VPSS_Sys_SetMotionEdgeLutce(pstVpssRegs,  u32AddrOffset,  motion_edge_lutce);
    VPSS_Sys_SetMotionEdgeLutcd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcd);
    VPSS_Sys_SetMotionEdgeLutcc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcc);
    VPSS_Sys_SetMotionEdgeLutcb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcb);
    VPSS_Sys_SetMotionEdgeLutca(pstVpssRegs,  u32AddrOffset,  motion_edge_lutca);
    VPSS_Sys_SetMotionEdgeLutc9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc9);
    VPSS_Sys_SetMotionEdgeLutc8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc8);
    VPSS_Sys_SetMotionEdgeLutd7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd7);
    VPSS_Sys_SetMotionEdgeLutd6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd6);
    VPSS_Sys_SetMotionEdgeLutd5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd5);
    VPSS_Sys_SetMotionEdgeLutd4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd4);
    VPSS_Sys_SetMotionEdgeLutd3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd3);
    VPSS_Sys_SetMotionEdgeLutd2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd2);
    VPSS_Sys_SetMotionEdgeLutd1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd1);
    VPSS_Sys_SetMotionEdgeLutd0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd0);
    VPSS_Sys_SetMotionEdgeLutdf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdf);
    VPSS_Sys_SetMotionEdgeLutde(pstVpssRegs,  u32AddrOffset,  motion_edge_lutde);
    VPSS_Sys_SetMotionEdgeLutdd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdd);
    VPSS_Sys_SetMotionEdgeLutdc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdc);
    VPSS_Sys_SetMotionEdgeLutdb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdb);
    VPSS_Sys_SetMotionEdgeLutda(pstVpssRegs,  u32AddrOffset,  motion_edge_lutda);
    VPSS_Sys_SetMotionEdgeLutd9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd9);
    VPSS_Sys_SetMotionEdgeLutd8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd8);
    VPSS_Sys_SetMotionEdgeLute7(pstVpssRegs,  u32AddrOffset,  motion_edge_lute7);
    VPSS_Sys_SetMotionEdgeLute6(pstVpssRegs,  u32AddrOffset,  motion_edge_lute6);
    VPSS_Sys_SetMotionEdgeLute5(pstVpssRegs,  u32AddrOffset,  motion_edge_lute5);
    VPSS_Sys_SetMotionEdgeLute4(pstVpssRegs,  u32AddrOffset,  motion_edge_lute4);
    VPSS_Sys_SetMotionEdgeLute3(pstVpssRegs,  u32AddrOffset,  motion_edge_lute3);
    VPSS_Sys_SetMotionEdgeLute2(pstVpssRegs,  u32AddrOffset,  motion_edge_lute2);
    VPSS_Sys_SetMotionEdgeLute1(pstVpssRegs,  u32AddrOffset,  motion_edge_lute1);
    VPSS_Sys_SetMotionEdgeLute0(pstVpssRegs,  u32AddrOffset,  motion_edge_lute0);
    VPSS_Sys_SetMotionEdgeLutef(pstVpssRegs,  u32AddrOffset,  motion_edge_lutef);
    VPSS_Sys_SetMotionEdgeLutee(pstVpssRegs,  u32AddrOffset,  motion_edge_lutee);
    VPSS_Sys_SetMotionEdgeLuted(pstVpssRegs,  u32AddrOffset,  motion_edge_luted);
    VPSS_Sys_SetMotionEdgeLutec(pstVpssRegs,  u32AddrOffset,  motion_edge_lutec);
    VPSS_Sys_SetMotionEdgeLuteb(pstVpssRegs,  u32AddrOffset,  motion_edge_luteb);
    VPSS_Sys_SetMotionEdgeLutea(pstVpssRegs,  u32AddrOffset,  motion_edge_lutea);
    VPSS_Sys_SetMotionEdgeLute9(pstVpssRegs,  u32AddrOffset,  motion_edge_lute9);
    VPSS_Sys_SetMotionEdgeLute8(pstVpssRegs,  u32AddrOffset,  motion_edge_lute8);
    VPSS_Sys_SetMotionEdgeLutf7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf7);
    VPSS_Sys_SetMotionEdgeLutf6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf6);
    VPSS_Sys_SetMotionEdgeLutf5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf5);
    VPSS_Sys_SetMotionEdgeLutf4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf4);
    VPSS_Sys_SetMotionEdgeLutf3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf3);
    VPSS_Sys_SetMotionEdgeLutf2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf2);
    VPSS_Sys_SetMotionEdgeLutf1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf1);
    VPSS_Sys_SetMotionEdgeLutf0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf0);
    VPSS_Sys_SetMotionEdgeLutff(pstVpssRegs,  u32AddrOffset,  motion_edge_lutff);
    VPSS_Sys_SetMotionEdgeLutfe(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfe);
    VPSS_Sys_SetMotionEdgeLutfd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfd);
    VPSS_Sys_SetMotionEdgeLutfc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfc);
    VPSS_Sys_SetMotionEdgeLutfb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfb);
    VPSS_Sys_SetMotionEdgeLutfa(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfa);
    VPSS_Sys_SetMotionEdgeLutf9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf9);
    VPSS_Sys_SetMotionEdgeLutf8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf8);

    free(BordFlag);
    free(BordFlag128);
    free(pstTnrRegType);
    return ;
}
#endif

HI_VOID VPSS_FUNC_SetSnrMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_SNR_CFG_S *pstCfg)
{
    //HI_U32 in_width  = pstCfg->width;

    HI_U32  db_en   =   1   ;
    HI_U32  dm_en   =   1   ;
    //HI_U32    snr_en  =   1   ;
    HI_U32  db_lum_hor_en   =   1   ;
    HI_U32  dbm_demo_en =   0   ;
    HI_U32  dbm_demo_mode   =   0   ;
    HI_U32  det_hy_en   =   1   ;
    HI_U32  dbm_out_mode    =   4   ;

    HI_U32  dbm_demo_pos_x  =   0   ;

    HI_U32  db_grad_sub_ratio   =   24  ;
    HI_U32  db_ctrst_thresh =   2   ;

    HI_U32  db_lum_h_blk_size   =   8   ;

    HI_U32  db_lum_hor_scale_ratio  =   1   ;
    HI_U32  db_lum_hor_filter_sel   =   1   ;
    HI_U32  db_global_db_strenth_lum    =   8   ;
    HI_U32  db_lum_hor_txt_win_size =   0   ;

    HI_U32  db_lum_hor_hf_diff_core =   0   ;
    HI_U32  db_lum_hor_hf_diff_gain1    =   0   ;
    HI_U32  db_lum_hor_hf_diff_gain2    =   0   ;
    HI_U32  db_lum_hor_hf_var_core  =   0   ;
    HI_U32  db_lum_hor_hf_var_gain1 =   4   ;
    HI_U32  db_lum_hor_hf_var_gain2 =   8   ;

    HI_U32  db_lum_hor_adj_gain =   4   ;
    HI_U32  db_lum_hor_bord_adj_gain    =   7   ;

    HI_U32  db_ctrst_adj_core   =   0   ;
    HI_U32  db_dir_smooth_mode  =   2   ;
    HI_U32  db_ctrst_adj_gain1  =   0   ;
    HI_U32  db_ctrst_adj_gain2  =   8   ;
    HI_U32  db_max_lum_hor_db_dist  =   4   ;

    HI_U32  db_lum_hor_delta_lut_p0 =   4   ;
    HI_U32  db_lum_hor_delta_lut_p1 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p2 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p3 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p4 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p5 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p6 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p7 =   8   ;

    HI_U32  db_lum_hor_delta_lut_p8 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p9 =   8   ;
    HI_U32  db_lum_hor_delta_lut_p10    =   8   ;
    HI_U32  db_lum_hor_delta_lut_p11    =   6   ;
    HI_U32  db_lum_hor_delta_lut_p12    =   4   ;
    HI_U32  db_lum_hor_delta_lut_p13    =   2   ;
    HI_U32  db_lum_hor_delta_lut_p14    =   0   ;
    HI_U32  db_lum_hor_delta_lut_p15    =   0   ;

    HI_U32  db_lum_h_str_fade_lut_p0    =   4   ;
    HI_U32  db_lum_h_str_fade_lut_p1    =   4   ;
    HI_U32  db_lum_h_str_fade_lut_p2    =   3   ;
    HI_U32  db_lum_h_str_fade_lut_p3    =   3   ;
    HI_U32  db_lum_h_str_fade_lut_p4    =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p5    =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p6    =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p7    =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p8    =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p9    =   0   ;

    HI_U32  db_lum_h_str_fade_lut_p10   =   0   ;
    HI_U32  db_lum_h_str_fade_lut_p11   =   0   ;

    HI_U32  db_dir_str_gain_lut_p0  =   8   ;
    HI_U32  db_dir_str_gain_lut_p1  =   5   ;
    HI_U32  db_dir_str_gain_lut_p2  =   3   ;
    HI_U32  db_dir_str_gain_lut_p3  =   1   ;
    HI_U32  db_dir_str_gain_lut_p4  =   0   ;
    HI_U32  db_dir_str_gain_lut_p5  =   0   ;
    HI_U32  db_dir_str_gain_lut_p6  =   0   ;
    HI_U32  db_dir_str_gain_lut_p7  =   0   ;

    HI_U32  db_dir_str_lut_p0   =   8   ;
    HI_U32  db_dir_str_lut_p1   =   8   ;
    HI_U32  db_dir_str_lut_p2   =   8   ;
    HI_U32  db_dir_str_lut_p3   =   8   ;
    HI_U32  db_dir_str_lut_p4   =   8   ;
    HI_U32  db_dir_str_lut_p5   =   8   ;
    HI_U32  db_dir_str_lut_p6   =   8   ;
    HI_U32  db_dir_str_lut_p7   =   6   ;

    HI_U32  db_dir_str_lut_p8   =   1   ;
    HI_U32  db_dir_str_lut_p9   =   1   ;
    HI_U32  db_dir_str_lut_p10  =   0   ;
    HI_U32  db_dir_str_lut_p11  =   0   ;
    HI_U32  db_dir_str_lut_p12  =   0   ;
    HI_U32  db_dir_str_lut_p13  =   0   ;
    HI_U32  db_dir_str_lut_p14  =   0   ;
    HI_U32  db_dir_str_lut_p15  =   0   ;

    HI_U32  dbd_hy_thd_edge =   32  ;

    HI_U32  dbd_hy_thd_txt  =   16  ;

    HI_U32  dbd_det_lut_wgt0    =   0   ;
    HI_U32  dbd_det_lut_wgt1    =   0   ;
    HI_U32  dbd_det_lut_wgt2    =   1   ;
    HI_U32  dbd_det_lut_wgt3    =   2   ;
    HI_U32  dbd_det_lut_wgt4    =   5   ;
    HI_U32  dbd_det_lut_wgt5    =   7   ;
    HI_U32  dbd_det_lut_wgt6    =   10  ;
    HI_U32  dbd_det_lut_wgt7    =   12  ;

    HI_U32  dbd_det_lut_wgt8    =   12  ;
    HI_U32  dbd_det_lut_wgt9    =   13  ;
    HI_U32  dbd_det_lut_wgt10   =   13  ;
    HI_U32  dbd_det_lut_wgt11   =   14  ;
    HI_U32  dbd_det_lut_wgt12   =   14  ;
    HI_U32  dbd_det_lut_wgt13   =   15  ;
    HI_U32  dbd_det_lut_wgt14   =   15  ;
    HI_U32  dbd_det_lut_wgt15   =   15  ;

    HI_U32  dbd_hy_rtn_bd_txt   =   20  ;

    HI_U32  dbd_hy_tst_blk_num  =   90  ;

    HI_U32  dbd_hy_rdx8bin_lut0 =   16  ;
    HI_U32  dbd_hy_rdx8bin_lut1 =   48  ;

    HI_U32  dbd_hy_rdx8bin_lut2 =   80  ;
    HI_U32  dbd_hy_rdx8bin_lut3 =   112 ;

    HI_U32  dbd_hy_rdx8bin_lut4 =   144 ;
    HI_U32  dbd_hy_rdx8bin_lut5 =   176 ;

    HI_U32  dbd_hy_rdx8bin_lut6 =   208 ;

    HI_U32  dbd_min_blk_size    =   4   ;
    HI_U32  dbd_hy_max_blk_size =   16  ;

    HI_U32  dbd_thr_flat    =   20  ;

    HI_U32  dm_grad_sub_ratio   =   24  ;
    HI_U32  dm_ctrst_thresh =   2   ;
    HI_U32  dm_opp_ang_ctrst_t  =   18  ;
    HI_U32  dm_opp_ang_ctrst_div    =   2   ;

    HI_U32  dm_mmf_set  =   0   ;
    HI_U32  dm_init_val_step    =   1   ;
    HI_U32  dm_global_str   =   8   ;

    HI_U32  dm_sw_wht_lut_p0    =   4   ;
    HI_U32  dm_sw_wht_lut_p1    =   8   ;
    HI_U32  dm_sw_wht_lut_p2    =   16  ;
    HI_U32  dm_sw_wht_lut_p3    =   32  ;

    HI_U32  dm_sw_wht_lut_p4    =   64  ;
    HI_U32  dm_limit_t  =   8   ;
    HI_U32  dm_limit_t_10   =   32  ;

    HI_U32  dm_dir_str_gain_lut_p0  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p1  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p2  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p3  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p4  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p5  =   8   ;
    HI_U32  dm_dir_str_gain_lut_p6  =   6   ;
    HI_U32  dm_dir_str_gain_lut_p7  =   5   ;

    HI_U32  dm_dir_str_lut_p0   =   8   ;
    HI_U32  dm_dir_str_lut_p1   =   8   ;
    HI_U32  dm_dir_str_lut_p2   =   8   ;
    HI_U32  dm_dir_str_lut_p3   =   8   ;
    HI_U32  dm_dir_str_lut_p4   =   8   ;
    HI_U32  dm_dir_str_lut_p5   =   8   ;
    HI_U32  dm_dir_str_lut_p6   =   8   ;
    HI_U32  dm_dir_str_lut_p7   =   6   ;

    HI_U32  dm_dir_str_lut_p8   =   1   ;
    HI_U32  dm_dir_str_lut_p9   =   1   ;
    HI_U32  dm_dir_str_lut_p10  =   0   ;
    HI_U32  dm_dir_str_lut_p11  =   0   ;
    HI_U32  dm_dir_str_lut_p12  =   0   ;
    HI_U32  dm_dir_str_lut_p13  =   0   ;
    HI_U32  dm_dir_str_lut_p14  =   0   ;
    HI_U32  dm_dir_str_lut_p15  =   0   ;

    HI_U32  dm_mndir_opp_ctrst_t    =   15  ;
    HI_U32  dm_mmf_limit_en =   1   ;

    HI_U32  dm_csw_trsnt_st_10  =   0   ;

    HI_U32  dm_lw_ctrst_t   =   30  ;
    HI_U32  dm_lw_ctrst_t_10    =   120 ;
    HI_U32  dm_csw_trsnt_st =   0   ;
    HI_U32  dm_lsw_ratio    =   4   ;

    HI_U32  dm_mmf_lr   =   20  ;
    HI_U32  dm_mmf_lr_10    =   80  ;
    HI_U32  dm_csw_trsnt_lt =   35  ;

    HI_U32  dm_mmf_sr   =   0   ;
    HI_U32  dm_mmf_sr_10    =   0   ;
    HI_U32  dm_csw_trsnt_lt_10  =   140 ;

    HI_U32  dm_limit_lsw_ratio  =   5   ;
    HI_U32  dm_lim_res_blend_str1   =   7   ;
    HI_U32  dm_lim_res_blend_str2   =   7   ;
    HI_U32  dm_dir_blend_str    =   6   ;

    HI_U32  dm_trans_band_lut_p0    =   0   ;
    HI_U32  dm_trans_band_lut_p1    =   1   ;
    HI_U32  dm_trans_band_lut_p2    =   2   ;
    HI_U32  dm_trans_band_lut_p3    =   3   ;
    HI_U32  dm_trans_band_lut_p4    =   4   ;

    HI_U32  dm_trans_band_lut_p5    =   5   ;
    HI_U32  dm_trans_band_lut_p6    =   6   ;
    HI_U32  dm_trans_band_lut_p7    =   7   ;
    HI_U32  dm_trans_band_lut_p8    =   8   ;
    HI_U32  dm_trans_band_lut_p9    =   9   ;

    HI_U32  dm_trans_band_lut_p10   =   10  ;
    HI_U32  dm_trans_band_lut_p11   =   11  ;
    HI_U32  dm_trans_band_lut_p12   =   12  ;
    HI_U32  dm_trans_band_lut_p13   =   13  ;
    HI_U32  dm_trans_band_lut_p14   =   14  ;

    HI_U32  dm_trans_band_lut_p15   =   15  ;
    HI_U32  dm_trans_band_lut_p16   =   16  ;
    HI_U32  dm_trans_band_lut_p17   =   17  ;
    HI_U32  dm_trans_band_lut_p18   =   18  ;
    HI_U32  dm_trans_band_lut_p19   =   19  ;

    HI_U32  dm_trans_band_lut_p20   =   20  ;
    HI_U32  dm_trans_band_lut_p21   =   21  ;
    HI_U32  dm_trans_band_lut_p22   =   22  ;
    HI_U32  dm_trans_band_lut_p23   =   23  ;
    HI_U32  dm_trans_band_lut_p24   =   24  ;

    HI_U32  dm_trans_band_lut_p25   =   25  ;
    HI_U32  dm_trans_band_lut_p26   =   26  ;
    HI_U32  dm_trans_band_lut_p27   =   27  ;
    HI_U32  dm_trans_band_lut_p28   =   28  ;
    HI_U32  dm_trans_band_lut_p29   =   29  ;

    HI_U32  dm_trans_band_lut_p30   =   30  ;

    HI_U32  ynr2den =   1   ;
    HI_U32  cnr2den =   0   ;
    HI_U32  motionedgeweighten  =   1   ;
    HI_U32  colorweighten   =   0   ;
    HI_U32  edgeprefilteren =   1   ;
    HI_U32  test_en =   0   ;

    HI_U32  edgemaxratio    =   15  ;
    HI_U32  edgeminratio    =   1   ;
    HI_U32  edgeoriratio    =   15  ;

    HI_U32  edgemaxstrength =   15  ;
    HI_U32  edgeminstrength =   0   ;
    HI_U32  edgeoristrength =   0   ;

    HI_U32  edgestrth1  =   8   ;
    HI_U32  edgestrth2  =   16  ;
    HI_U32  edgestrth3  =   24  ;

    HI_U32  edgestrk1   =   16  ;
    HI_U32  edgestrk2   =   32  ;
    HI_U32  edgestrk3   =   32  ;

    HI_U32  edgemeanth1 =   64  ;
    HI_U32  edgemeanth2 =   90  ;
    HI_U32  edgemeanth3 =   128 ;

    HI_U32  edgemeanth4 =   164 ;
    HI_U32  edgemeanth5 =   196 ;
    HI_U32  edgemeanth6 =   300 ;

    HI_U32  edgemeanth7 =   512 ;
    HI_U32  edgemeanth8 =   768 ;

    HI_U32  edgemeank1  =   0   ;
    HI_U32  edgemeank2  =   24  ;
    HI_U32  edgemeank3  =   32  ;
    HI_U32  edgemeank4  =   24  ;

    HI_U32  edgemeank5  =   20  ;
    HI_U32  edgemeank6  =   12  ;
    HI_U32  edgemeank7  =   8   ;
    HI_U32  edgemeank8  =   8   ;

    HI_U32  y2dwinwidth =   9   ;
    HI_U32  y2dwinheight    =   5   ;
    HI_U32  c2dwinwidth =   5   ;
    HI_U32  c2dwinheight    =   3   ;

    HI_U32  ysnrstr =   24  ;
    HI_U32  csnrstr =   24  ;

    HI_U32  stroffset0  =   0   ;
    HI_U32  stroffset1  =   1   ;
    HI_U32  stroffset2  =   2   ;
    HI_U32  stroffset3  =   3   ;

    HI_U32  ystradjust  =   16  ;
    HI_U32  cstradjust  =   16  ;

    HI_U32  scenechangeth   =   3   ;

    HI_U32  ratio1  =   30  ;
    HI_U32  ratio2  =   28  ;
    HI_U32  ratio3  =   22  ;

    HI_U32  ratio4  =   19  ;
    HI_U32  ratio5  =   16  ;
    HI_U32  ratio6  =   11  ;

    HI_U32  ratio7  =   4   ;
    HI_U32  ratio8  =   0   ;

    HI_U32  edge1   =   4   ;
    HI_U32  edge2   =   12  ;
    HI_U32  edge3   =   15  ;

    HI_U32  test_color_cb   =   512 ;
    HI_U32  test_color_cr   =   512 ;

    HI_U32  scenechange_info    =   0   ;
    HI_U32  scenechange_en  =   0   ;
    HI_U32  scenechange_mode1_en    =   0   ;
    HI_U32  scenechange_bldk    =   96  ;
    HI_U32  scenechange_bldcore =   0   ;
    HI_U32  scenechange_mode2_en    =   0   ;

    HI_U32  motionalpha =   8   ;

    HI_U32  cb_begin1   =   0   ;
    HI_U32  cr_begin1   =   0   ;
    HI_U32  cb_end1 =   0   ;
    HI_U32  cr_end1 =   0   ;
    HI_U32  cbcr_weight1    =   15  ;

    HI_U32  cb_begin2   =   0   ;
    HI_U32  cr_begin2   =   0   ;
    HI_U32  cb_end2 =   0   ;
    HI_U32  cr_end2 =   0   ;
    HI_U32  cbcr_weight2    =   15  ;

    HI_U32  motion_edge_lut00   =   0   ;
    HI_U32  motion_edge_lut01   =   0   ;
    HI_U32  motion_edge_lut02   =   0   ;
    HI_U32  motion_edge_lut03   =   0   ;
    HI_U32  motion_edge_lut04   =   0   ;
    HI_U32  motion_edge_lut05   =   0   ;
    HI_U32  motion_edge_lut06   =   0   ;
    HI_U32  motion_edge_lut07   =   0   ;

    HI_U32  motion_edge_lut08   =   0   ;
    HI_U32  motion_edge_lut09   =   0   ;
    HI_U32  motion_edge_lut0a   =   1   ;
    HI_U32  motion_edge_lut0b   =   2   ;
    HI_U32  motion_edge_lut0c   =   3   ;
    HI_U32  motion_edge_lut0d   =   4   ;
    HI_U32  motion_edge_lut0e   =   5   ;
    HI_U32  motion_edge_lut0f   =   7   ;

    HI_U32  motion_edge_lut10   =   0   ;
    HI_U32  motion_edge_lut11   =   0   ;
    HI_U32  motion_edge_lut12   =   0   ;
    HI_U32  motion_edge_lut13   =   0   ;
    HI_U32  motion_edge_lut14   =   0   ;
    HI_U32  motion_edge_lut15   =   0   ;
    HI_U32  motion_edge_lut16   =   0   ;
    HI_U32  motion_edge_lut17   =   0   ;

    HI_U32  motion_edge_lut18   =   0   ;
    HI_U32  motion_edge_lut19   =   1   ;
    HI_U32  motion_edge_lut1a   =   2   ;
    HI_U32  motion_edge_lut1b   =   3   ;
    HI_U32  motion_edge_lut1c   =   4   ;
    HI_U32  motion_edge_lut1d   =   5   ;
    HI_U32  motion_edge_lut1e   =   6   ;
    HI_U32  motion_edge_lut1f   =   7   ;

    HI_U32  motion_edge_lut20   =   0   ;
    HI_U32  motion_edge_lut21   =   0   ;
    HI_U32  motion_edge_lut22   =   0   ;
    HI_U32  motion_edge_lut23   =   0   ;
    HI_U32  motion_edge_lut24   =   0   ;
    HI_U32  motion_edge_lut25   =   0   ;
    HI_U32  motion_edge_lut26   =   0   ;
    HI_U32  motion_edge_lut27   =   0   ;

    HI_U32  motion_edge_lut28   =   1   ;
    HI_U32  motion_edge_lut29   =   2   ;
    HI_U32  motion_edge_lut2a   =   3   ;
    HI_U32  motion_edge_lut2b   =   4   ;
    HI_U32  motion_edge_lut2c   =   5   ;
    HI_U32  motion_edge_lut2d   =   6   ;
    HI_U32  motion_edge_lut2e   =   7   ;
    HI_U32  motion_edge_lut2f   =   8   ;

    HI_U32  motion_edge_lut30   =   0   ;
    HI_U32  motion_edge_lut31   =   0   ;
    HI_U32  motion_edge_lut32   =   0   ;
    HI_U32  motion_edge_lut33   =   0   ;
    HI_U32  motion_edge_lut34   =   0   ;
    HI_U32  motion_edge_lut35   =   0   ;
    HI_U32  motion_edge_lut36   =   0   ;
    HI_U32  motion_edge_lut37   =   1   ;

    HI_U32  motion_edge_lut38   =   2   ;
    HI_U32  motion_edge_lut39   =   3   ;
    HI_U32  motion_edge_lut3a   =   4   ;
    HI_U32  motion_edge_lut3b   =   5   ;
    HI_U32  motion_edge_lut3c   =   6   ;
    HI_U32  motion_edge_lut3d   =   7   ;
    HI_U32  motion_edge_lut3e   =   8   ;
    HI_U32  motion_edge_lut3f   =   9   ;

    HI_U32  motion_edge_lut40   =   0   ;
    HI_U32  motion_edge_lut41   =   0   ;
    HI_U32  motion_edge_lut42   =   0   ;
    HI_U32  motion_edge_lut43   =   0   ;
    HI_U32  motion_edge_lut44   =   0   ;
    HI_U32  motion_edge_lut45   =   0   ;
    HI_U32  motion_edge_lut46   =   1   ;
    HI_U32  motion_edge_lut47   =   2   ;

    HI_U32  motion_edge_lut48   =   3   ;
    HI_U32  motion_edge_lut49   =   4   ;
    HI_U32  motion_edge_lut4a   =   5   ;
    HI_U32  motion_edge_lut4b   =   6   ;
    HI_U32  motion_edge_lut4c   =   7   ;
    HI_U32  motion_edge_lut4d   =   8   ;
    HI_U32  motion_edge_lut4e   =   9   ;
    HI_U32  motion_edge_lut4f   =   10  ;

    HI_U32  motion_edge_lut50   =   0   ;
    HI_U32  motion_edge_lut51   =   0   ;
    HI_U32  motion_edge_lut52   =   0   ;
    HI_U32  motion_edge_lut53   =   0   ;
    HI_U32  motion_edge_lut54   =   0   ;
    HI_U32  motion_edge_lut55   =   1   ;
    HI_U32  motion_edge_lut56   =   2   ;
    HI_U32  motion_edge_lut57   =   3   ;

    HI_U32  motion_edge_lut58   =   4   ;
    HI_U32  motion_edge_lut59   =   5   ;
    HI_U32  motion_edge_lut5a   =   6   ;
    HI_U32  motion_edge_lut5b   =   7   ;
    HI_U32  motion_edge_lut5c   =   8   ;
    HI_U32  motion_edge_lut5d   =   9   ;
    HI_U32  motion_edge_lut5e   =   10  ;
    HI_U32  motion_edge_lut5f   =   11  ;

    VPSS_Sys_SetDbmOutMode(pstVpssRegs,  u32AddrOffset,  dbm_out_mode);
    VPSS_Sys_SetDetHyEn(pstVpssRegs,  u32AddrOffset,  det_hy_en);
    VPSS_Sys_SetDbmDemoMode(pstVpssRegs,  u32AddrOffset,  dbm_demo_mode);
    VPSS_Sys_SetDbmDemoEn(pstVpssRegs,  u32AddrOffset,  dbm_demo_en);
    VPSS_Sys_SetDbLumHorEn(pstVpssRegs,  u32AddrOffset,  db_lum_hor_en);
    //VPSS_Sys_SetNrEn(pstVpssRegs,  u32AddrOffset,  nr_en);
    VPSS_Sys_SetDmEn(pstVpssRegs,  u32AddrOffset,  dm_en);
    VPSS_Sys_SetDbEn(pstVpssRegs,  u32AddrOffset,  db_en);
    VPSS_Sys_SetDbmDemoPosX(pstVpssRegs,  u32AddrOffset,  dbm_demo_pos_x);
    VPSS_Sys_SetDbCtrstThresh(pstVpssRegs,  u32AddrOffset,  db_ctrst_thresh);
    VPSS_Sys_SetDbGradSubRatio(pstVpssRegs,  u32AddrOffset,  db_grad_sub_ratio);
    VPSS_Sys_SetDbLumHBlkSize(pstVpssRegs,  u32AddrOffset,  db_lum_h_blk_size);
    VPSS_Sys_SetDbLumHorTxtWinSize(pstVpssRegs,  u32AddrOffset,  db_lum_hor_txt_win_size);
    VPSS_Sys_SetDbGlobalDbStrenthLum(pstVpssRegs,  u32AddrOffset,  db_global_db_strenth_lum);
    VPSS_Sys_SetDbLumHorFilterSel(pstVpssRegs,  u32AddrOffset,  db_lum_hor_filter_sel);
    VPSS_Sys_SetDbLumHorScaleRatio(pstVpssRegs,  u32AddrOffset,  db_lum_hor_scale_ratio);
    VPSS_Sys_SetDbLumHorHfVarGain2(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_var_gain2);
    VPSS_Sys_SetDbLumHorHfVarGain1(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_var_gain1);
    VPSS_Sys_SetDbLumHorHfVarCore(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_var_core);
    VPSS_Sys_SetDbLumHorHfDiffGain2(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_diff_gain2);
    VPSS_Sys_SetDbLumHorHfDiffGain1(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_diff_gain1);
    VPSS_Sys_SetDbLumHorHfDiffCore(pstVpssRegs,  u32AddrOffset,  db_lum_hor_hf_diff_core);
    VPSS_Sys_SetDbLumHorBordAdjGain(pstVpssRegs,  u32AddrOffset,  db_lum_hor_bord_adj_gain);
    VPSS_Sys_SetDbLumHorAdjGain(pstVpssRegs,  u32AddrOffset,  db_lum_hor_adj_gain);
    VPSS_Sys_SetDbMaxLumHorDbDist(pstVpssRegs,  u32AddrOffset,  db_max_lum_hor_db_dist);
    VPSS_Sys_SetDbCtrstAdjGain2(pstVpssRegs,  u32AddrOffset,  db_ctrst_adj_gain2);
    VPSS_Sys_SetDbCtrstAdjGain1(pstVpssRegs,  u32AddrOffset,  db_ctrst_adj_gain1);
    VPSS_Sys_SetDbDirSmoothMode(pstVpssRegs,  u32AddrOffset,  db_dir_smooth_mode);
    VPSS_Sys_SetDbCtrstAdjCore(pstVpssRegs,  u32AddrOffset,  db_ctrst_adj_core);
    VPSS_Sys_SetDbLumHorDeltaLutP7(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p7);
    VPSS_Sys_SetDbLumHorDeltaLutP6(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p6);
    VPSS_Sys_SetDbLumHorDeltaLutP5(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p5);
    VPSS_Sys_SetDbLumHorDeltaLutP4(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p4);
    VPSS_Sys_SetDbLumHorDeltaLutP3(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p3);
    VPSS_Sys_SetDbLumHorDeltaLutP2(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p2);
    VPSS_Sys_SetDbLumHorDeltaLutP1(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p1);
    VPSS_Sys_SetDbLumHorDeltaLutP0(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p0);
    VPSS_Sys_SetDbLumHorDeltaLutP15(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p15);
    VPSS_Sys_SetDbLumHorDeltaLutP14(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p14);
    VPSS_Sys_SetDbLumHorDeltaLutP13(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p13);
    VPSS_Sys_SetDbLumHorDeltaLutP12(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p12);
    VPSS_Sys_SetDbLumHorDeltaLutP11(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p11);
    VPSS_Sys_SetDbLumHorDeltaLutP10(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p10);
    VPSS_Sys_SetDbLumHorDeltaLutP9(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p9);
    VPSS_Sys_SetDbLumHorDeltaLutP8(pstVpssRegs,  u32AddrOffset,  db_lum_hor_delta_lut_p8);
    VPSS_Sys_SetDbLumHStrFadeLutP9(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p9);
    VPSS_Sys_SetDbLumHStrFadeLutP8(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p8);
    VPSS_Sys_SetDbLumHStrFadeLutP7(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p7);
    VPSS_Sys_SetDbLumHStrFadeLutP6(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p6);
    VPSS_Sys_SetDbLumHStrFadeLutP5(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p5);
    VPSS_Sys_SetDbLumHStrFadeLutP4(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p4);
    VPSS_Sys_SetDbLumHStrFadeLutP3(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p3);
    VPSS_Sys_SetDbLumHStrFadeLutP2(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p2);
    VPSS_Sys_SetDbLumHStrFadeLutP1(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p1);
    VPSS_Sys_SetDbLumHStrFadeLutP0(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p0);
    VPSS_Sys_SetDbLumHStrFadeLutP11(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p11);
    VPSS_Sys_SetDbLumHStrFadeLutP10(pstVpssRegs,  u32AddrOffset,  db_lum_h_str_fade_lut_p10);
    VPSS_Sys_SetDbDirStrGainLutP7(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p7);
    VPSS_Sys_SetDbDirStrGainLutP6(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p6);
    VPSS_Sys_SetDbDirStrGainLutP5(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p5);
    VPSS_Sys_SetDbDirStrGainLutP4(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p4);
    VPSS_Sys_SetDbDirStrGainLutP3(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p3);
    VPSS_Sys_SetDbDirStrGainLutP2(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p2);
    VPSS_Sys_SetDbDirStrGainLutP1(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p1);
    VPSS_Sys_SetDbDirStrGainLutP0(pstVpssRegs,  u32AddrOffset,  db_dir_str_gain_lut_p0);
    VPSS_Sys_SetDbDirStrLutP7(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p7);
    VPSS_Sys_SetDbDirStrLutP6(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p6);
    VPSS_Sys_SetDbDirStrLutP5(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p5);
    VPSS_Sys_SetDbDirStrLutP4(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p4);
    VPSS_Sys_SetDbDirStrLutP3(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p3);
    VPSS_Sys_SetDbDirStrLutP2(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p2);
    VPSS_Sys_SetDbDirStrLutP1(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p1);
    VPSS_Sys_SetDbDirStrLutP0(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p0);
    VPSS_Sys_SetDbDirStrLutP15(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p15);
    VPSS_Sys_SetDbDirStrLutP14(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p14);
    VPSS_Sys_SetDbDirStrLutP13(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p13);
    VPSS_Sys_SetDbDirStrLutP12(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p12);
    VPSS_Sys_SetDbDirStrLutP11(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p11);
    VPSS_Sys_SetDbDirStrLutP10(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p10);
    VPSS_Sys_SetDbDirStrLutP9(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p9);
    VPSS_Sys_SetDbDirStrLutP8(pstVpssRegs,  u32AddrOffset,  db_dir_str_lut_p8);
    VPSS_Sys_SetDbdHyThdEdge(pstVpssRegs,  u32AddrOffset,  dbd_hy_thd_edge);
    VPSS_Sys_SetDbdHyThdTxt(pstVpssRegs,  u32AddrOffset,  dbd_hy_thd_txt);
#if 1
    VPSS_Sys_SetDbdDetLutWgt7(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt7);
    VPSS_Sys_SetDbdDetLutWgt6(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt6);
    VPSS_Sys_SetDbdDetLutWgt5(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt5);
    VPSS_Sys_SetDbdDetLutWgt4(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt4);
    VPSS_Sys_SetDbdDetLutWgt3(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt3);
    VPSS_Sys_SetDbdDetLutWgt2(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt2);
    VPSS_Sys_SetDbdDetLutWgt1(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt1);
    VPSS_Sys_SetDbdDetLutWgt0(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt0);
    VPSS_Sys_SetDbdDetLutWgt15(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt15);
    VPSS_Sys_SetDbdDetLutWgt14(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt14);
    VPSS_Sys_SetDbdDetLutWgt13(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt13);
    VPSS_Sys_SetDbdDetLutWgt12(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt12);
    VPSS_Sys_SetDbdDetLutWgt11(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt11);
    VPSS_Sys_SetDbdDetLutWgt10(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt10);
    VPSS_Sys_SetDbdDetLutWgt9(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt9);
    VPSS_Sys_SetDbdDetLutWgt8(pstVpssRegs,  u32AddrOffset,  dbd_det_lut_wgt8);
#endif
    VPSS_Sys_SetDbdHyRtnBdTxt(pstVpssRegs,  u32AddrOffset,  dbd_hy_rtn_bd_txt);
    VPSS_Sys_SetDbdHyTstBlkNum(pstVpssRegs,  u32AddrOffset,  dbd_hy_tst_blk_num);
#if 1
    VPSS_Sys_SetDbdHyRdx8binLut1(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut1);
    VPSS_Sys_SetDbdHyRdx8binLut0(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut0);
    VPSS_Sys_SetDbdHyRdx8binLut3(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut3);
    VPSS_Sys_SetDbdHyRdx8binLut2(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut2);
    VPSS_Sys_SetDbdHyRdx8binLut5(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut5);
    VPSS_Sys_SetDbdHyRdx8binLut4(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut4);
    VPSS_Sys_SetDbdHyRdx8binLut6(pstVpssRegs,  u32AddrOffset,  dbd_hy_rdx8bin_lut6);
#endif
    VPSS_Sys_SetDbdHyMaxBlkSize(pstVpssRegs,  u32AddrOffset,   dbd_hy_max_blk_size);
    VPSS_Sys_SetDbdMinBlkSize(pstVpssRegs,  u32AddrOffset,     dbd_min_blk_size);
    VPSS_Sys_SetDbdThrFlat(pstVpssRegs,  u32AddrOffset,        dbd_thr_flat);
    VPSS_Sys_SetDmOppAngCtrstDiv(pstVpssRegs,  u32AddrOffset,  dm_opp_ang_ctrst_div);
    VPSS_Sys_SetDmOppAngCtrstT(pstVpssRegs,  u32AddrOffset,    dm_opp_ang_ctrst_t);
    VPSS_Sys_SetDmCtrstThresh(pstVpssRegs,  u32AddrOffset,     dm_ctrst_thresh);
    VPSS_Sys_SetDmGradSubRatio(pstVpssRegs,  u32AddrOffset,    dm_grad_sub_ratio);
    VPSS_Sys_SetDmGlobalStr(pstVpssRegs,  u32AddrOffset,       dm_global_str);
    VPSS_Sys_SetDmInitValStep(pstVpssRegs,  u32AddrOffset,     dm_init_val_step);
    VPSS_Sys_SetDmMmfSet(pstVpssRegs,  u32AddrOffset,          dm_mmf_set);
    VPSS_Sys_SetDmSwWhtLutP3(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p3);
    VPSS_Sys_SetDmSwWhtLutP2(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p2);
    VPSS_Sys_SetDmSwWhtLutP1(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p1);
    VPSS_Sys_SetDmSwWhtLutP0(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p0);
    VPSS_Sys_SetDmLimitT10(pstVpssRegs,  u32AddrOffset,  dm_limit_t_10);
    VPSS_Sys_SetDmLimitT(pstVpssRegs,  u32AddrOffset,  dm_limit_t);
    VPSS_Sys_SetDmSwWhtLutP4(pstVpssRegs,  u32AddrOffset,  dm_sw_wht_lut_p4);
    VPSS_Sys_SetDmDirStrGainLutP7(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p7);
    VPSS_Sys_SetDmDirStrGainLutP6(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p6);
    VPSS_Sys_SetDmDirStrGainLutP5(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p5);
    VPSS_Sys_SetDmDirStrGainLutP4(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p4);
    VPSS_Sys_SetDmDirStrGainLutP3(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p3);
    VPSS_Sys_SetDmDirStrGainLutP2(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p2);
    VPSS_Sys_SetDmDirStrGainLutP1(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p1);
    VPSS_Sys_SetDmDirStrGainLutP0(pstVpssRegs,  u32AddrOffset,  dm_dir_str_gain_lut_p0);
    VPSS_Sys_SetDmDirStrLutP7(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p7);
    VPSS_Sys_SetDmDirStrLutP6(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p6);
    VPSS_Sys_SetDmDirStrLutP5(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p5);
    VPSS_Sys_SetDmDirStrLutP4(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p4);
    VPSS_Sys_SetDmDirStrLutP3(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p3);
    VPSS_Sys_SetDmDirStrLutP2(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p2);
    VPSS_Sys_SetDmDirStrLutP1(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p1);
    VPSS_Sys_SetDmDirStrLutP0(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p0);
    VPSS_Sys_SetDmDirStrLutP15(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p15);
    VPSS_Sys_SetDmDirStrLutP14(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p14);
    VPSS_Sys_SetDmDirStrLutP13(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p13);
    VPSS_Sys_SetDmDirStrLutP12(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p12);
    VPSS_Sys_SetDmDirStrLutP11(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p11);
    VPSS_Sys_SetDmDirStrLutP10(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p10);
    VPSS_Sys_SetDmDirStrLutP9(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p9);
    VPSS_Sys_SetDmDirStrLutP8(pstVpssRegs,  u32AddrOffset,  dm_dir_str_lut_p8);
    VPSS_Sys_SetDmMmfLimitEn(pstVpssRegs,  u32AddrOffset,  dm_mmf_limit_en);
    VPSS_Sys_SetDmMndirOppCtrstT(pstVpssRegs,  u32AddrOffset,  dm_mndir_opp_ctrst_t);
    VPSS_Sys_SetDmCswTrsntSt10(pstVpssRegs,  u32AddrOffset,  dm_csw_trsnt_st_10);
    VPSS_Sys_SetDmLswRatio(pstVpssRegs,  u32AddrOffset,  dm_lsw_ratio);
    VPSS_Sys_SetDmCswTrsntSt(pstVpssRegs,  u32AddrOffset,  dm_csw_trsnt_st);
    VPSS_Sys_SetDmLwCtrstT10(pstVpssRegs,  u32AddrOffset,  dm_lw_ctrst_t_10);
    VPSS_Sys_SetDmLwCtrstT(pstVpssRegs,  u32AddrOffset,  dm_lw_ctrst_t);
    VPSS_Sys_SetDmCswTrsntLt(pstVpssRegs,  u32AddrOffset,  dm_csw_trsnt_lt);
    VPSS_Sys_SetDmMmfLr10(pstVpssRegs,  u32AddrOffset,  dm_mmf_lr_10);
    VPSS_Sys_SetDmMmfLr(pstVpssRegs,  u32AddrOffset,  dm_mmf_lr);
    VPSS_Sys_SetDmCswTrsntLt10(pstVpssRegs,  u32AddrOffset,  dm_csw_trsnt_lt_10);
    VPSS_Sys_SetDmMmfSr10(pstVpssRegs,  u32AddrOffset,  dm_mmf_sr_10);
    VPSS_Sys_SetDmMmfSr(pstVpssRegs,  u32AddrOffset,  dm_mmf_sr);
    VPSS_Sys_SetDmDirBlendStr(pstVpssRegs,  u32AddrOffset,  dm_dir_blend_str);
    VPSS_Sys_SetDmLimResBlendStr2(pstVpssRegs,  u32AddrOffset,  dm_lim_res_blend_str2);
    VPSS_Sys_SetDmLimResBlendStr1(pstVpssRegs,  u32AddrOffset,  dm_lim_res_blend_str1);
    VPSS_Sys_SetDmLimitLswRatio(pstVpssRegs,  u32AddrOffset,  dm_limit_lsw_ratio);
    VPSS_Sys_SetDmTransBandLutP4(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p4);
    VPSS_Sys_SetDmTransBandLutP3(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p3);
    VPSS_Sys_SetDmTransBandLutP2(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p2);
    VPSS_Sys_SetDmTransBandLutP1(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p1);
    VPSS_Sys_SetDmTransBandLutP0(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p0);
    VPSS_Sys_SetDmTransBandLutP9(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p9);
    VPSS_Sys_SetDmTransBandLutP8(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p8);
    VPSS_Sys_SetDmTransBandLutP7(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p7);
    VPSS_Sys_SetDmTransBandLutP6(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p6);
    VPSS_Sys_SetDmTransBandLutP5(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p5);
    VPSS_Sys_SetDmTransBandLutP14(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p14);
    VPSS_Sys_SetDmTransBandLutP13(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p13);
    VPSS_Sys_SetDmTransBandLutP12(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p12);
    VPSS_Sys_SetDmTransBandLutP11(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p11);
    VPSS_Sys_SetDmTransBandLutP10(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p10);
    VPSS_Sys_SetDmTransBandLutP19(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p19);
    VPSS_Sys_SetDmTransBandLutP18(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p18);
    VPSS_Sys_SetDmTransBandLutP17(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p17);
    VPSS_Sys_SetDmTransBandLutP16(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p16);
    VPSS_Sys_SetDmTransBandLutP15(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p15);
    VPSS_Sys_SetDmTransBandLutP24(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p24);
    VPSS_Sys_SetDmTransBandLutP23(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p23);
    VPSS_Sys_SetDmTransBandLutP22(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p22);
    VPSS_Sys_SetDmTransBandLutP21(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p21);
    VPSS_Sys_SetDmTransBandLutP20(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p20);
    VPSS_Sys_SetDmTransBandLutP29(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p29);
    VPSS_Sys_SetDmTransBandLutP28(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p28);
    VPSS_Sys_SetDmTransBandLutP27(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p27);
    VPSS_Sys_SetDmTransBandLutP26(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p26);
    VPSS_Sys_SetDmTransBandLutP25(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p25);
    VPSS_Sys_SetDmTransBandLutP30(pstVpssRegs,  u32AddrOffset,  dm_trans_band_lut_p30);
#if 0
    VPSS_Sys_SetVpssDbBordFlag0(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_0);
    VPSS_Sys_SetVpssDbBordFlag1(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_1);
    VPSS_Sys_SetVpssDbBordFlag2(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_2);
    VPSS_Sys_SetVpssDbBordFlag3(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_3);
    VPSS_Sys_SetVpssDbBordFlag4(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_4);
    VPSS_Sys_SetVpssDbBordFlag5(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_5);
    VPSS_Sys_SetVpssDbBordFlag6(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_6);
    VPSS_Sys_SetVpssDbBordFlag7(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_7);
    VPSS_Sys_SetVpssDbBordFlag8(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_8);
    VPSS_Sys_SetVpssDbBordFlag9(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_9);
    VPSS_Sys_SetVpssDbBordFlag10(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_10);
    VPSS_Sys_SetVpssDbBordFlag11(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_11);
    VPSS_Sys_SetVpssDbBordFlag12(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_12);
    VPSS_Sys_SetVpssDbBordFlag13(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_13);
    VPSS_Sys_SetVpssDbBordFlag14(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_14);
    VPSS_Sys_SetVpssDbBordFlag15(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_15);
    VPSS_Sys_SetVpssDbBordFlag16(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_16);
    VPSS_Sys_SetVpssDbBordFlag17(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_17);
    VPSS_Sys_SetVpssDbBordFlag18(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_18);
    VPSS_Sys_SetVpssDbBordFlag19(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_19);
    VPSS_Sys_SetVpssDbBordFlag20(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_20);
    VPSS_Sys_SetVpssDbBordFlag21(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_21);
    VPSS_Sys_SetVpssDbBordFlag22(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_22);
    VPSS_Sys_SetVpssDbBordFlag23(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_23);
    VPSS_Sys_SetVpssDbBordFlag24(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_24);
    VPSS_Sys_SetVpssDbBordFlag25(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_25);
    VPSS_Sys_SetVpssDbBordFlag26(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_26);
    VPSS_Sys_SetVpssDbBordFlag27(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_27);
    VPSS_Sys_SetVpssDbBordFlag28(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_28);
    VPSS_Sys_SetVpssDbBordFlag29(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_29);
    VPSS_Sys_SetVpssDbBordFlag30(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_30);
    VPSS_Sys_SetVpssDbBordFlag31(pstVpssRegs,  u32AddrOffset,  vpss_db_bord_flag_31);
#endif
    VPSS_Sys_SetTestEn(pstVpssRegs,  u32AddrOffset,  test_en);
    VPSS_Sys_SetEdgeprefilteren(pstVpssRegs,  u32AddrOffset,  edgeprefilteren);
    VPSS_Sys_SetColorweighten(pstVpssRegs,  u32AddrOffset,  colorweighten);
    VPSS_Sys_SetMotionedgeweighten(pstVpssRegs,  u32AddrOffset,  motionedgeweighten);
    VPSS_Sys_SetCnr2den(pstVpssRegs,  u32AddrOffset,  cnr2den);
    VPSS_Sys_SetYnr2den(pstVpssRegs,  u32AddrOffset,  ynr2den);
    VPSS_Sys_SetEdgeoriratio(pstVpssRegs,  u32AddrOffset,  edgeoriratio);
    VPSS_Sys_SetEdgeminratio(pstVpssRegs,  u32AddrOffset,  edgeminratio);
    VPSS_Sys_SetEdgemaxratio(pstVpssRegs,  u32AddrOffset,  edgemaxratio);
    VPSS_Sys_SetEdgeoristrength(pstVpssRegs,  u32AddrOffset,  edgeoristrength);
    VPSS_Sys_SetEdgeminstrength(pstVpssRegs,  u32AddrOffset,  edgeminstrength);
    VPSS_Sys_SetEdgemaxstrength(pstVpssRegs,  u32AddrOffset,  edgemaxstrength);
    VPSS_Sys_SetEdgestrth3(pstVpssRegs,  u32AddrOffset,  edgestrth3);
    VPSS_Sys_SetEdgestrth2(pstVpssRegs,  u32AddrOffset,  edgestrth2);
    VPSS_Sys_SetEdgestrth1(pstVpssRegs,  u32AddrOffset,  edgestrth1);
    VPSS_Sys_SetEdgestrk3(pstVpssRegs,  u32AddrOffset,  edgestrk3);
    VPSS_Sys_SetEdgestrk2(pstVpssRegs,  u32AddrOffset,  edgestrk2);
    VPSS_Sys_SetEdgestrk1(pstVpssRegs,  u32AddrOffset,  edgestrk1);
    VPSS_Sys_SetEdgemeanth3(pstVpssRegs,  u32AddrOffset,  edgemeanth3);
    VPSS_Sys_SetEdgemeanth2(pstVpssRegs,  u32AddrOffset,  edgemeanth2);
    VPSS_Sys_SetEdgemeanth1(pstVpssRegs,  u32AddrOffset,  edgemeanth1);
    VPSS_Sys_SetEdgemeanth6(pstVpssRegs,  u32AddrOffset,  edgemeanth6);
    VPSS_Sys_SetEdgemeanth5(pstVpssRegs,  u32AddrOffset,  edgemeanth5);
    VPSS_Sys_SetEdgemeanth4(pstVpssRegs,  u32AddrOffset,  edgemeanth4);
    VPSS_Sys_SetEdgemeanth8(pstVpssRegs,  u32AddrOffset,  edgemeanth8);
    VPSS_Sys_SetEdgemeanth7(pstVpssRegs,  u32AddrOffset,  edgemeanth7);
    VPSS_Sys_SetEdgemeank4(pstVpssRegs,  u32AddrOffset,  edgemeank4);
    VPSS_Sys_SetEdgemeank3(pstVpssRegs,  u32AddrOffset,  edgemeank3);
    VPSS_Sys_SetEdgemeank2(pstVpssRegs,  u32AddrOffset,  edgemeank2);
    VPSS_Sys_SetEdgemeank1(pstVpssRegs,  u32AddrOffset,  edgemeank1);
    VPSS_Sys_SetEdgemeank8(pstVpssRegs,  u32AddrOffset,  edgemeank8);
    VPSS_Sys_SetEdgemeank7(pstVpssRegs,  u32AddrOffset,  edgemeank7);
    VPSS_Sys_SetEdgemeank6(pstVpssRegs,  u32AddrOffset,  edgemeank6);
    VPSS_Sys_SetEdgemeank5(pstVpssRegs,  u32AddrOffset,  edgemeank5);
    VPSS_Sys_SetC2dwinheight(pstVpssRegs,  u32AddrOffset,  c2dwinheight);
    VPSS_Sys_SetC2dwinwidth(pstVpssRegs,  u32AddrOffset,  c2dwinwidth);
    VPSS_Sys_SetY2dwinheight(pstVpssRegs,  u32AddrOffset,  y2dwinheight);
    VPSS_Sys_SetY2dwinwidth(pstVpssRegs,  u32AddrOffset,  y2dwinwidth);
    VPSS_Sys_SetCsnrstr(pstVpssRegs,  u32AddrOffset,  csnrstr);
    VPSS_Sys_SetYsnrstr(pstVpssRegs,  u32AddrOffset,  ysnrstr);
    VPSS_Sys_SetStroffset3(pstVpssRegs,  u32AddrOffset,  stroffset3);
    VPSS_Sys_SetStroffset2(pstVpssRegs,  u32AddrOffset,  stroffset2);
    VPSS_Sys_SetStroffset1(pstVpssRegs,  u32AddrOffset,  stroffset1);
    VPSS_Sys_SetStroffset0(pstVpssRegs,  u32AddrOffset,  stroffset0);
    VPSS_Sys_SetCstradjust(pstVpssRegs,  u32AddrOffset,  cstradjust);
    VPSS_Sys_SetYstradjust(pstVpssRegs,  u32AddrOffset,  ystradjust);
    VPSS_Sys_SetScenechangeth(pstVpssRegs,  u32AddrOffset,  scenechangeth);
    VPSS_Sys_SetRatio3(pstVpssRegs,  u32AddrOffset,  ratio3);
    VPSS_Sys_SetRatio2(pstVpssRegs,  u32AddrOffset,  ratio2);
    VPSS_Sys_SetRatio1(pstVpssRegs,  u32AddrOffset,  ratio1);
    VPSS_Sys_SetRatio6(pstVpssRegs,  u32AddrOffset,  ratio6);
    VPSS_Sys_SetRatio5(pstVpssRegs,  u32AddrOffset,  ratio5);
    VPSS_Sys_SetRatio4(pstVpssRegs,  u32AddrOffset,  ratio4);
    VPSS_Sys_SetRatio8(pstVpssRegs,  u32AddrOffset,  ratio8);
    VPSS_Sys_SetRatio7(pstVpssRegs,  u32AddrOffset,  ratio7);
    VPSS_Sys_SetEdge3(pstVpssRegs,  u32AddrOffset,  edge3);
    VPSS_Sys_SetEdge2(pstVpssRegs,  u32AddrOffset,  edge2);
    VPSS_Sys_SetEdge1(pstVpssRegs,  u32AddrOffset,  edge1);
    VPSS_Sys_SetTestColorCr(pstVpssRegs,  u32AddrOffset,  test_color_cr);
    VPSS_Sys_SetTestColorCb(pstVpssRegs,  u32AddrOffset,  test_color_cb);
    VPSS_Sys_SetScenechangeMode2En(pstVpssRegs,  u32AddrOffset,  scenechange_mode2_en);
    VPSS_Sys_SetScenechangeBldcore(pstVpssRegs,  u32AddrOffset,  scenechange_bldcore);
    VPSS_Sys_SetScenechangeBldk(pstVpssRegs,  u32AddrOffset,  scenechange_bldk);
    VPSS_Sys_SetScenechangeMode1En(pstVpssRegs,  u32AddrOffset,  scenechange_mode1_en);
    VPSS_Sys_SetScenechangeEn(pstVpssRegs,  u32AddrOffset,  scenechange_en);
    VPSS_Sys_SetScenechangeInfo(pstVpssRegs,  u32AddrOffset,  scenechange_info);
    VPSS_Sys_SetMotionalpha(pstVpssRegs,  u32AddrOffset,  motionalpha);
    VPSS_Sys_SetCbcrWeight1(pstVpssRegs,  u32AddrOffset,  cbcr_weight1);
    VPSS_Sys_SetCrEnd1(pstVpssRegs,  u32AddrOffset,  cr_end1);
    VPSS_Sys_SetCbEnd1(pstVpssRegs,  u32AddrOffset,  cb_end1);
    VPSS_Sys_SetCrBegin1(pstVpssRegs,  u32AddrOffset,  cr_begin1);
    VPSS_Sys_SetCbBegin1(pstVpssRegs,  u32AddrOffset,  cb_begin1);
    VPSS_Sys_SetCbcrWeight2(pstVpssRegs,  u32AddrOffset,  cbcr_weight2);
    VPSS_Sys_SetCrEnd2(pstVpssRegs,  u32AddrOffset,  cr_end2);
    VPSS_Sys_SetCbEnd2(pstVpssRegs,  u32AddrOffset,  cb_end2);
    VPSS_Sys_SetCrBegin2(pstVpssRegs,  u32AddrOffset,  cr_begin2);
    VPSS_Sys_SetCbBegin2(pstVpssRegs,  u32AddrOffset,  cb_begin2);
    VPSS_Sys_SetMotionEdgeLut07(pstVpssRegs,  u32AddrOffset,  motion_edge_lut07);
    VPSS_Sys_SetMotionEdgeLut06(pstVpssRegs,  u32AddrOffset,  motion_edge_lut06);
    VPSS_Sys_SetMotionEdgeLut05(pstVpssRegs,  u32AddrOffset,  motion_edge_lut05);
    VPSS_Sys_SetMotionEdgeLut04(pstVpssRegs,  u32AddrOffset,  motion_edge_lut04);
    VPSS_Sys_SetMotionEdgeLut03(pstVpssRegs,  u32AddrOffset,  motion_edge_lut03);
    VPSS_Sys_SetMotionEdgeLut02(pstVpssRegs,  u32AddrOffset,  motion_edge_lut02);
    VPSS_Sys_SetMotionEdgeLut01(pstVpssRegs,  u32AddrOffset,  motion_edge_lut01);
    VPSS_Sys_SetMotionEdgeLut00(pstVpssRegs,  u32AddrOffset,  motion_edge_lut00);
    VPSS_Sys_SetMotionEdgeLut0f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0f);
    VPSS_Sys_SetMotionEdgeLut0e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0e);
    VPSS_Sys_SetMotionEdgeLut0d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0d);
    VPSS_Sys_SetMotionEdgeLut0c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0c);
    VPSS_Sys_SetMotionEdgeLut0b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0b);
    VPSS_Sys_SetMotionEdgeLut0a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut0a);
    VPSS_Sys_SetMotionEdgeLut09(pstVpssRegs,  u32AddrOffset,  motion_edge_lut09);
    VPSS_Sys_SetMotionEdgeLut08(pstVpssRegs,  u32AddrOffset,  motion_edge_lut08);
    VPSS_Sys_SetMotionEdgeLut17(pstVpssRegs,  u32AddrOffset,  motion_edge_lut17);
    VPSS_Sys_SetMotionEdgeLut16(pstVpssRegs,  u32AddrOffset,  motion_edge_lut16);
    VPSS_Sys_SetMotionEdgeLut15(pstVpssRegs,  u32AddrOffset,  motion_edge_lut15);
    VPSS_Sys_SetMotionEdgeLut14(pstVpssRegs,  u32AddrOffset,  motion_edge_lut14);
    VPSS_Sys_SetMotionEdgeLut13(pstVpssRegs,  u32AddrOffset,  motion_edge_lut13);
    VPSS_Sys_SetMotionEdgeLut12(pstVpssRegs,  u32AddrOffset,  motion_edge_lut12);
    VPSS_Sys_SetMotionEdgeLut11(pstVpssRegs,  u32AddrOffset,  motion_edge_lut11);
    VPSS_Sys_SetMotionEdgeLut10(pstVpssRegs,  u32AddrOffset,  motion_edge_lut10);
    VPSS_Sys_SetMotionEdgeLut1f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1f);
    VPSS_Sys_SetMotionEdgeLut1e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1e);
    VPSS_Sys_SetMotionEdgeLut1d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1d);
    VPSS_Sys_SetMotionEdgeLut1c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1c);
    VPSS_Sys_SetMotionEdgeLut1b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1b);
    VPSS_Sys_SetMotionEdgeLut1a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut1a);
    VPSS_Sys_SetMotionEdgeLut19(pstVpssRegs,  u32AddrOffset,  motion_edge_lut19);
    VPSS_Sys_SetMotionEdgeLut18(pstVpssRegs,  u32AddrOffset,  motion_edge_lut18);
    VPSS_Sys_SetMotionEdgeLut27(pstVpssRegs,  u32AddrOffset,  motion_edge_lut27);
    VPSS_Sys_SetMotionEdgeLut26(pstVpssRegs,  u32AddrOffset,  motion_edge_lut26);
    VPSS_Sys_SetMotionEdgeLut25(pstVpssRegs,  u32AddrOffset,  motion_edge_lut25);
    VPSS_Sys_SetMotionEdgeLut24(pstVpssRegs,  u32AddrOffset,  motion_edge_lut24);
    VPSS_Sys_SetMotionEdgeLut23(pstVpssRegs,  u32AddrOffset,  motion_edge_lut23);
    VPSS_Sys_SetMotionEdgeLut22(pstVpssRegs,  u32AddrOffset,  motion_edge_lut22);
    VPSS_Sys_SetMotionEdgeLut21(pstVpssRegs,  u32AddrOffset,  motion_edge_lut21);
    VPSS_Sys_SetMotionEdgeLut20(pstVpssRegs,  u32AddrOffset,  motion_edge_lut20);
    VPSS_Sys_SetMotionEdgeLut2f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2f);
    VPSS_Sys_SetMotionEdgeLut2e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2e);
    VPSS_Sys_SetMotionEdgeLut2d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2d);
    VPSS_Sys_SetMotionEdgeLut2c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2c);
    VPSS_Sys_SetMotionEdgeLut2b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2b);
    VPSS_Sys_SetMotionEdgeLut2a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut2a);
    VPSS_Sys_SetMotionEdgeLut29(pstVpssRegs,  u32AddrOffset,  motion_edge_lut29);
    VPSS_Sys_SetMotionEdgeLut28(pstVpssRegs,  u32AddrOffset,  motion_edge_lut28);
    VPSS_Sys_SetMotionEdgeLut37(pstVpssRegs,  u32AddrOffset,  motion_edge_lut37);
    VPSS_Sys_SetMotionEdgeLut36(pstVpssRegs,  u32AddrOffset,  motion_edge_lut36);
    VPSS_Sys_SetMotionEdgeLut35(pstVpssRegs,  u32AddrOffset,  motion_edge_lut35);
    VPSS_Sys_SetMotionEdgeLut34(pstVpssRegs,  u32AddrOffset,  motion_edge_lut34);
    VPSS_Sys_SetMotionEdgeLut33(pstVpssRegs,  u32AddrOffset,  motion_edge_lut33);
    VPSS_Sys_SetMotionEdgeLut32(pstVpssRegs,  u32AddrOffset,  motion_edge_lut32);
    VPSS_Sys_SetMotionEdgeLut31(pstVpssRegs,  u32AddrOffset,  motion_edge_lut31);
    VPSS_Sys_SetMotionEdgeLut30(pstVpssRegs,  u32AddrOffset,  motion_edge_lut30);
    VPSS_Sys_SetMotionEdgeLut3f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3f);
    VPSS_Sys_SetMotionEdgeLut3e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3e);
    VPSS_Sys_SetMotionEdgeLut3d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3d);
    VPSS_Sys_SetMotionEdgeLut3c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3c);
    VPSS_Sys_SetMotionEdgeLut3b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3b);
    VPSS_Sys_SetMotionEdgeLut3a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut3a);
    VPSS_Sys_SetMotionEdgeLut39(pstVpssRegs,  u32AddrOffset,  motion_edge_lut39);
    VPSS_Sys_SetMotionEdgeLut38(pstVpssRegs,  u32AddrOffset,  motion_edge_lut38);
    VPSS_Sys_SetMotionEdgeLut47(pstVpssRegs,  u32AddrOffset,  motion_edge_lut47);
    VPSS_Sys_SetMotionEdgeLut46(pstVpssRegs,  u32AddrOffset,  motion_edge_lut46);
    VPSS_Sys_SetMotionEdgeLut45(pstVpssRegs,  u32AddrOffset,  motion_edge_lut45);
    VPSS_Sys_SetMotionEdgeLut44(pstVpssRegs,  u32AddrOffset,  motion_edge_lut44);
    VPSS_Sys_SetMotionEdgeLut43(pstVpssRegs,  u32AddrOffset,  motion_edge_lut43);
    VPSS_Sys_SetMotionEdgeLut42(pstVpssRegs,  u32AddrOffset,  motion_edge_lut42);
    VPSS_Sys_SetMotionEdgeLut41(pstVpssRegs,  u32AddrOffset,  motion_edge_lut41);
    VPSS_Sys_SetMotionEdgeLut40(pstVpssRegs,  u32AddrOffset,  motion_edge_lut40);
    VPSS_Sys_SetMotionEdgeLut4f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4f);
    VPSS_Sys_SetMotionEdgeLut4e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4e);
    VPSS_Sys_SetMotionEdgeLut4d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4d);
    VPSS_Sys_SetMotionEdgeLut4c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4c);
    VPSS_Sys_SetMotionEdgeLut4b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4b);
    VPSS_Sys_SetMotionEdgeLut4a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut4a);
    VPSS_Sys_SetMotionEdgeLut49(pstVpssRegs,  u32AddrOffset,  motion_edge_lut49);
    VPSS_Sys_SetMotionEdgeLut48(pstVpssRegs,  u32AddrOffset,  motion_edge_lut48);
    VPSS_Sys_SetMotionEdgeLut57(pstVpssRegs,  u32AddrOffset,  motion_edge_lut57);
    VPSS_Sys_SetMotionEdgeLut56(pstVpssRegs,  u32AddrOffset,  motion_edge_lut56);
    VPSS_Sys_SetMotionEdgeLut55(pstVpssRegs,  u32AddrOffset,  motion_edge_lut55);
    VPSS_Sys_SetMotionEdgeLut54(pstVpssRegs,  u32AddrOffset,  motion_edge_lut54);
    VPSS_Sys_SetMotionEdgeLut53(pstVpssRegs,  u32AddrOffset,  motion_edge_lut53);
    VPSS_Sys_SetMotionEdgeLut52(pstVpssRegs,  u32AddrOffset,  motion_edge_lut52);
    VPSS_Sys_SetMotionEdgeLut51(pstVpssRegs,  u32AddrOffset,  motion_edge_lut51);
    VPSS_Sys_SetMotionEdgeLut50(pstVpssRegs,  u32AddrOffset,  motion_edge_lut50);
    VPSS_Sys_SetMotionEdgeLut5f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5f);
    VPSS_Sys_SetMotionEdgeLut5e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5e);
    VPSS_Sys_SetMotionEdgeLut5d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5d);
    VPSS_Sys_SetMotionEdgeLut5c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5c);
    VPSS_Sys_SetMotionEdgeLut5b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5b);
    VPSS_Sys_SetMotionEdgeLut5a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut5a);
    VPSS_Sys_SetMotionEdgeLut59(pstVpssRegs,  u32AddrOffset,  motion_edge_lut59);
    VPSS_Sys_SetMotionEdgeLut58(pstVpssRegs,  u32AddrOffset,  motion_edge_lut58);
#if 0
    VPSS_Sys_SetMotionEdgeLut67(pstVpssRegs,  u32AddrOffset,  motion_edge_lut67);
    VPSS_Sys_SetMotionEdgeLut66(pstVpssRegs,  u32AddrOffset,  motion_edge_lut66);
    VPSS_Sys_SetMotionEdgeLut65(pstVpssRegs,  u32AddrOffset,  motion_edge_lut65);
    VPSS_Sys_SetMotionEdgeLut64(pstVpssRegs,  u32AddrOffset,  motion_edge_lut64);
    VPSS_Sys_SetMotionEdgeLut63(pstVpssRegs,  u32AddrOffset,  motion_edge_lut63);
    VPSS_Sys_SetMotionEdgeLut62(pstVpssRegs,  u32AddrOffset,  motion_edge_lut62);
    VPSS_Sys_SetMotionEdgeLut61(pstVpssRegs,  u32AddrOffset,  motion_edge_lut61);
    VPSS_Sys_SetMotionEdgeLut60(pstVpssRegs,  u32AddrOffset,  motion_edge_lut60);
    VPSS_Sys_SetMotionEdgeLut6f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6f);
    VPSS_Sys_SetMotionEdgeLut6e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6e);
    VPSS_Sys_SetMotionEdgeLut6d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6d);
    VPSS_Sys_SetMotionEdgeLut6c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6c);
    VPSS_Sys_SetMotionEdgeLut6b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6b);
    VPSS_Sys_SetMotionEdgeLut6a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut6a);
    VPSS_Sys_SetMotionEdgeLut69(pstVpssRegs,  u32AddrOffset,  motion_edge_lut69);
    VPSS_Sys_SetMotionEdgeLut68(pstVpssRegs,  u32AddrOffset,  motion_edge_lut68);
    VPSS_Sys_SetMotionEdgeLut77(pstVpssRegs,  u32AddrOffset,  motion_edge_lut77);
    VPSS_Sys_SetMotionEdgeLut76(pstVpssRegs,  u32AddrOffset,  motion_edge_lut76);
    VPSS_Sys_SetMotionEdgeLut75(pstVpssRegs,  u32AddrOffset,  motion_edge_lut75);
    VPSS_Sys_SetMotionEdgeLut74(pstVpssRegs,  u32AddrOffset,  motion_edge_lut74);
    VPSS_Sys_SetMotionEdgeLut73(pstVpssRegs,  u32AddrOffset,  motion_edge_lut73);
    VPSS_Sys_SetMotionEdgeLut72(pstVpssRegs,  u32AddrOffset,  motion_edge_lut72);
    VPSS_Sys_SetMotionEdgeLut71(pstVpssRegs,  u32AddrOffset,  motion_edge_lut71);
    VPSS_Sys_SetMotionEdgeLut70(pstVpssRegs,  u32AddrOffset,  motion_edge_lut70);
    VPSS_Sys_SetMotionEdgeLut7f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7f);
    VPSS_Sys_SetMotionEdgeLut7e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7e);
    VPSS_Sys_SetMotionEdgeLut7d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7d);
    VPSS_Sys_SetMotionEdgeLut7c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7c);
    VPSS_Sys_SetMotionEdgeLut7b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7b);
    VPSS_Sys_SetMotionEdgeLut7a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut7a);
    VPSS_Sys_SetMotionEdgeLut79(pstVpssRegs,  u32AddrOffset,  motion_edge_lut79);
    VPSS_Sys_SetMotionEdgeLut78(pstVpssRegs,  u32AddrOffset,  motion_edge_lut78);
    VPSS_Sys_SetMotionEdgeLut87(pstVpssRegs,  u32AddrOffset,  motion_edge_lut87);
    VPSS_Sys_SetMotionEdgeLut86(pstVpssRegs,  u32AddrOffset,  motion_edge_lut86);
    VPSS_Sys_SetMotionEdgeLut85(pstVpssRegs,  u32AddrOffset,  motion_edge_lut85);
    VPSS_Sys_SetMotionEdgeLut84(pstVpssRegs,  u32AddrOffset,  motion_edge_lut84);
    VPSS_Sys_SetMotionEdgeLut83(pstVpssRegs,  u32AddrOffset,  motion_edge_lut83);
    VPSS_Sys_SetMotionEdgeLut82(pstVpssRegs,  u32AddrOffset,  motion_edge_lut82);
    VPSS_Sys_SetMotionEdgeLut81(pstVpssRegs,  u32AddrOffset,  motion_edge_lut81);
    VPSS_Sys_SetMotionEdgeLut80(pstVpssRegs,  u32AddrOffset,  motion_edge_lut80);
    VPSS_Sys_SetMotionEdgeLut8f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8f);
    VPSS_Sys_SetMotionEdgeLut8e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8e);
    VPSS_Sys_SetMotionEdgeLut8d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8d);
    VPSS_Sys_SetMotionEdgeLut8c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8c);
    VPSS_Sys_SetMotionEdgeLut8b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8b);
    VPSS_Sys_SetMotionEdgeLut8a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut8a);
    VPSS_Sys_SetMotionEdgeLut89(pstVpssRegs,  u32AddrOffset,  motion_edge_lut89);
    VPSS_Sys_SetMotionEdgeLut88(pstVpssRegs,  u32AddrOffset,  motion_edge_lut88);
    VPSS_Sys_SetMotionEdgeLut97(pstVpssRegs,  u32AddrOffset,  motion_edge_lut97);
    VPSS_Sys_SetMotionEdgeLut96(pstVpssRegs,  u32AddrOffset,  motion_edge_lut96);
    VPSS_Sys_SetMotionEdgeLut95(pstVpssRegs,  u32AddrOffset,  motion_edge_lut95);
    VPSS_Sys_SetMotionEdgeLut94(pstVpssRegs,  u32AddrOffset,  motion_edge_lut94);
    VPSS_Sys_SetMotionEdgeLut93(pstVpssRegs,  u32AddrOffset,  motion_edge_lut93);
    VPSS_Sys_SetMotionEdgeLut92(pstVpssRegs,  u32AddrOffset,  motion_edge_lut92);
    VPSS_Sys_SetMotionEdgeLut91(pstVpssRegs,  u32AddrOffset,  motion_edge_lut91);
    VPSS_Sys_SetMotionEdgeLut90(pstVpssRegs,  u32AddrOffset,  motion_edge_lut90);
    VPSS_Sys_SetMotionEdgeLut9f(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9f);
    VPSS_Sys_SetMotionEdgeLut9e(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9e);
    VPSS_Sys_SetMotionEdgeLut9d(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9d);
    VPSS_Sys_SetMotionEdgeLut9c(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9c);
    VPSS_Sys_SetMotionEdgeLut9b(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9b);
    VPSS_Sys_SetMotionEdgeLut9a(pstVpssRegs,  u32AddrOffset,  motion_edge_lut9a);
    VPSS_Sys_SetMotionEdgeLut99(pstVpssRegs,  u32AddrOffset,  motion_edge_lut99);
    VPSS_Sys_SetMotionEdgeLut98(pstVpssRegs,  u32AddrOffset,  motion_edge_lut98);
    VPSS_Sys_SetMotionEdgeLuta7(pstVpssRegs,  u32AddrOffset,  motion_edge_luta7);
    VPSS_Sys_SetMotionEdgeLuta6(pstVpssRegs,  u32AddrOffset,  motion_edge_luta6);
    VPSS_Sys_SetMotionEdgeLuta5(pstVpssRegs,  u32AddrOffset,  motion_edge_luta5);
    VPSS_Sys_SetMotionEdgeLuta4(pstVpssRegs,  u32AddrOffset,  motion_edge_luta4);
    VPSS_Sys_SetMotionEdgeLuta3(pstVpssRegs,  u32AddrOffset,  motion_edge_luta3);
    VPSS_Sys_SetMotionEdgeLuta2(pstVpssRegs,  u32AddrOffset,  motion_edge_luta2);
    VPSS_Sys_SetMotionEdgeLuta1(pstVpssRegs,  u32AddrOffset,  motion_edge_luta1);
    VPSS_Sys_SetMotionEdgeLuta0(pstVpssRegs,  u32AddrOffset,  motion_edge_luta0);
    VPSS_Sys_SetMotionEdgeLutaf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutaf);
    VPSS_Sys_SetMotionEdgeLutae(pstVpssRegs,  u32AddrOffset,  motion_edge_lutae);
    VPSS_Sys_SetMotionEdgeLutad(pstVpssRegs,  u32AddrOffset,  motion_edge_lutad);
    VPSS_Sys_SetMotionEdgeLutac(pstVpssRegs,  u32AddrOffset,  motion_edge_lutac);
    VPSS_Sys_SetMotionEdgeLutab(pstVpssRegs,  u32AddrOffset,  motion_edge_lutab);
    VPSS_Sys_SetMotionEdgeLutaa(pstVpssRegs,  u32AddrOffset,  motion_edge_lutaa);
    VPSS_Sys_SetMotionEdgeLuta9(pstVpssRegs,  u32AddrOffset,  motion_edge_luta9);
    VPSS_Sys_SetMotionEdgeLuta8(pstVpssRegs,  u32AddrOffset,  motion_edge_luta8);
    VPSS_Sys_SetMotionEdgeLutb7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb7);
    VPSS_Sys_SetMotionEdgeLutb6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb6);
    VPSS_Sys_SetMotionEdgeLutb5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb5);
    VPSS_Sys_SetMotionEdgeLutb4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb4);
    VPSS_Sys_SetMotionEdgeLutb3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb3);
    VPSS_Sys_SetMotionEdgeLutb2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb2);
    VPSS_Sys_SetMotionEdgeLutb1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb1);
    VPSS_Sys_SetMotionEdgeLutb0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb0);
    VPSS_Sys_SetMotionEdgeLutbf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbf);
    VPSS_Sys_SetMotionEdgeLutbe(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbe);
    VPSS_Sys_SetMotionEdgeLutbd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbd);
    VPSS_Sys_SetMotionEdgeLutbc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbc);
    VPSS_Sys_SetMotionEdgeLutbb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutbb);
    VPSS_Sys_SetMotionEdgeLutba(pstVpssRegs,  u32AddrOffset,  motion_edge_lutba);
    VPSS_Sys_SetMotionEdgeLutb9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb9);
    VPSS_Sys_SetMotionEdgeLutb8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutb8);
    VPSS_Sys_SetMotionEdgeLutc7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc7);
    VPSS_Sys_SetMotionEdgeLutc6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc6);
    VPSS_Sys_SetMotionEdgeLutc5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc5);
    VPSS_Sys_SetMotionEdgeLutc4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc4);
    VPSS_Sys_SetMotionEdgeLutc3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc3);
    VPSS_Sys_SetMotionEdgeLutc2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc2);
    VPSS_Sys_SetMotionEdgeLutc1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc1);
    VPSS_Sys_SetMotionEdgeLutc0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc0);
    VPSS_Sys_SetMotionEdgeLutcf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcf);
    VPSS_Sys_SetMotionEdgeLutce(pstVpssRegs,  u32AddrOffset,  motion_edge_lutce);
    VPSS_Sys_SetMotionEdgeLutcd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcd);
    VPSS_Sys_SetMotionEdgeLutcc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcc);
    VPSS_Sys_SetMotionEdgeLutcb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutcb);
    VPSS_Sys_SetMotionEdgeLutca(pstVpssRegs,  u32AddrOffset,  motion_edge_lutca);
    VPSS_Sys_SetMotionEdgeLutc9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc9);
    VPSS_Sys_SetMotionEdgeLutc8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutc8);
    VPSS_Sys_SetMotionEdgeLutd7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd7);
    VPSS_Sys_SetMotionEdgeLutd6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd6);
    VPSS_Sys_SetMotionEdgeLutd5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd5);
    VPSS_Sys_SetMotionEdgeLutd4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd4);
    VPSS_Sys_SetMotionEdgeLutd3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd3);
    VPSS_Sys_SetMotionEdgeLutd2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd2);
    VPSS_Sys_SetMotionEdgeLutd1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd1);
    VPSS_Sys_SetMotionEdgeLutd0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd0);
    VPSS_Sys_SetMotionEdgeLutdf(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdf);
    VPSS_Sys_SetMotionEdgeLutde(pstVpssRegs,  u32AddrOffset,  motion_edge_lutde);
    VPSS_Sys_SetMotionEdgeLutdd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdd);
    VPSS_Sys_SetMotionEdgeLutdc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdc);
    VPSS_Sys_SetMotionEdgeLutdb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutdb);
    VPSS_Sys_SetMotionEdgeLutda(pstVpssRegs,  u32AddrOffset,  motion_edge_lutda);
    VPSS_Sys_SetMotionEdgeLutd9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd9);
    VPSS_Sys_SetMotionEdgeLutd8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutd8);
    VPSS_Sys_SetMotionEdgeLute7(pstVpssRegs,  u32AddrOffset,  motion_edge_lute7);
    VPSS_Sys_SetMotionEdgeLute6(pstVpssRegs,  u32AddrOffset,  motion_edge_lute6);
    VPSS_Sys_SetMotionEdgeLute5(pstVpssRegs,  u32AddrOffset,  motion_edge_lute5);
    VPSS_Sys_SetMotionEdgeLute4(pstVpssRegs,  u32AddrOffset,  motion_edge_lute4);
    VPSS_Sys_SetMotionEdgeLute3(pstVpssRegs,  u32AddrOffset,  motion_edge_lute3);
    VPSS_Sys_SetMotionEdgeLute2(pstVpssRegs,  u32AddrOffset,  motion_edge_lute2);
    VPSS_Sys_SetMotionEdgeLute1(pstVpssRegs,  u32AddrOffset,  motion_edge_lute1);
    VPSS_Sys_SetMotionEdgeLute0(pstVpssRegs,  u32AddrOffset,  motion_edge_lute0);
    VPSS_Sys_SetMotionEdgeLutef(pstVpssRegs,  u32AddrOffset,  motion_edge_lutef);
    VPSS_Sys_SetMotionEdgeLutee(pstVpssRegs,  u32AddrOffset,  motion_edge_lutee);
    VPSS_Sys_SetMotionEdgeLuted(pstVpssRegs,  u32AddrOffset,  motion_edge_luted);
    VPSS_Sys_SetMotionEdgeLutec(pstVpssRegs,  u32AddrOffset,  motion_edge_lutec);
    VPSS_Sys_SetMotionEdgeLuteb(pstVpssRegs,  u32AddrOffset,  motion_edge_luteb);
    VPSS_Sys_SetMotionEdgeLutea(pstVpssRegs,  u32AddrOffset,  motion_edge_lutea);
    VPSS_Sys_SetMotionEdgeLute9(pstVpssRegs,  u32AddrOffset,  motion_edge_lute9);
    VPSS_Sys_SetMotionEdgeLute8(pstVpssRegs,  u32AddrOffset,  motion_edge_lute8);
    VPSS_Sys_SetMotionEdgeLutf7(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf7);
    VPSS_Sys_SetMotionEdgeLutf6(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf6);
    VPSS_Sys_SetMotionEdgeLutf5(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf5);
    VPSS_Sys_SetMotionEdgeLutf4(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf4);
    VPSS_Sys_SetMotionEdgeLutf3(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf3);
    VPSS_Sys_SetMotionEdgeLutf2(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf2);
    VPSS_Sys_SetMotionEdgeLutf1(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf1);
    VPSS_Sys_SetMotionEdgeLutf0(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf0);
    VPSS_Sys_SetMotionEdgeLutff(pstVpssRegs,  u32AddrOffset,  motion_edge_lutff);
    VPSS_Sys_SetMotionEdgeLutfe(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfe);
    VPSS_Sys_SetMotionEdgeLutfd(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfd);
    VPSS_Sys_SetMotionEdgeLutfc(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfc);
    VPSS_Sys_SetMotionEdgeLutfb(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfb);
    VPSS_Sys_SetMotionEdgeLutfa(pstVpssRegs,  u32AddrOffset,  motion_edge_lutfa);
    VPSS_Sys_SetMotionEdgeLutf9(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf9);
    VPSS_Sys_SetMotionEdgeLutf8(pstVpssRegs,  u32AddrOffset,  motion_edge_lutf8);
#endif
    return ;
}


HI_VOID VPSS_RGME_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_RGME_CFG_S *pstRgmeCfg, VPSS_DEI_CHN_CFG_S *pstDeiChnCfg)
{

    HI_U32 u32WthReal   = pstRgmeCfg->width ;
    HI_U32 u32HgtReal   = (pstRgmeCfg->pro) ? pstRgmeCfg->height : pstRgmeCfg->height / 2;

    HI_U32 u32RgmvNumH  = 0;
    HI_U32 u32RgmvNumV  = 0;

    u32RgmvNumH = ( u32WthReal + 33) / 64 ;
    u32RgmvNumV = ( u32HgtReal +  5) / 8 ;

    //rgmv
    pstDeiChnCfg->stInfoRgmv.bEn       = (HI_BOOL)pstRgmeCfg->rgme_en;
    pstDeiChnCfg->stInfoRgmv.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoRgmv.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoRgmv.bSmmu_Nx1 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoRgmv.u32Wth    = u32RgmvNumH;
    pstDeiChnCfg->stInfoRgmv.u32Hgt    = u32RgmvNumV;
    pstDeiChnCfg->stInfoRgmv.u32Stride = ((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16;

    VPSS_InfoCfg_Rgmv(&pstDeiChnCfg->stInfoRgmv, stRegAddr);

    //prjh
    pstDeiChnCfg->stInfoPrjh.bEn       = (HI_BOOL)pstRgmeCfg->rgme_en;
    pstDeiChnCfg->stInfoPrjh.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoPrjh.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoPrjh.u32Wth    = u32RgmvNumH * 128;
    pstDeiChnCfg->stInfoPrjh.u32Hgt    = u32RgmvNumV;
    pstDeiChnCfg->stInfoPrjh.u32Stride = ((pstDeiChnCfg->stInfoPrjh.u32Wth * 16 + 7) / 8 + 15) / 16 * 16;

    VPSS_InfoCfg_Prjh(&pstDeiChnCfg->stInfoPrjh, stRegAddr);

    //prjv
    pstDeiChnCfg->stInfoPrjv.bEn       = (HI_BOOL)pstRgmeCfg->rgme_en;
    pstDeiChnCfg->stInfoPrjv.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoPrjv.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
    pstDeiChnCfg->stInfoPrjv.u32Wth    = u32RgmvNumH * 16;
    pstDeiChnCfg->stInfoPrjv.u32Hgt    = u32RgmvNumV;
    pstDeiChnCfg->stInfoPrjv.u32Stride = ((pstDeiChnCfg->stInfoPrjv.u32Wth * 16 + 7) / 8 + 15) / 16 * 16;

    VPSS_InfoCfg_Prjv(&pstDeiChnCfg->stInfoPrjv, stRegAddr);

    return ;
}


HI_VOID VPSS_DEI_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_DEI_CFG_S *pstDeiCfg, VPSS_DEI_CHN_CFG_S *pstDeiChnCfg)
{
    //HI_U32 u32FrmWth    = pstDeiCfg->width ;
    //HI_U32 u32FrmHgt    = pstDeiCfg->height;
    HI_U32 u32WthReal   = pstDeiCfg->width ;
    HI_U32 u32HgtReal   = pstDeiCfg->height;
    HI_U32 u32bitwth    = pstDeiCfg->bitwth;
    HI_U32 u32RgmvNumH  = 0;
    HI_U32 u32RgmvNumV  = 0;
    HI_S32 s32ReturnVal = 0;
    HI_VOID *pArg       = HI_NULL;

    XDP_DATA_RMODE_E   enRdMode = VPSS_HAL_GetImgProMode((S_VPSS_REGS_TYPE *) stRegAddr.pu8NodeVirAddr);
    //XDP_PROC_FMT_E u32CurFmt   = pstDeiCfg->format;

    if (enRdMode > XDP_RMODE_PROGRESSIVE)
    {
        u32HgtReal = u32HgtReal / 2;
    }

    u32RgmvNumH = ( u32WthReal + 33) / 64 ;
    u32RgmvNumV = ( u32HgtReal +  5) / 8 ;


    if ((pstDeiCfg->dei_en == HI_TRUE) || (pstDeiCfg->rgme_en == HI_TRUE))
    {
        if (pstDeiCfg->dei_en == HI_TRUE)
        {
            XDP_ASSERT(enRdMode > XDP_RMODE_PROGRESSIVE);
            XDP_ASSERT(u32WthReal <= 1920);
            XDP_ASSERT(u32HgtReal <= 544);
        }

        //read p1
        pstDeiChnCfg->stP1.bEn = HI_TRUE;
        pstDeiChnCfg->stP1.enBitWidth = u32bitwth;//base on nr rfr bitwidth
        pstDeiChnCfg->stP1.u32Width   = u32WthReal;
        pstDeiChnCfg->stP1.u32Height  = u32HgtReal;
        pstDeiChnCfg->stP1.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10); //align 8bit/10bit
        pstDeiChnCfg->stP1.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstDeiChnCfg->stP1.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

        s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_NX1, (HI_VOID *) &pstDeiChnCfg->stP1, pArg);
        XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

        //read nr p2
        pstDeiChnCfg->stNrP2.bEn = HI_TRUE;
        pstDeiChnCfg->stNrP2.enBitWidth = u32bitwth;//base on nr rfr bitwidth
        pstDeiChnCfg->stNrP2.u32Width   = u32WthReal;
        pstDeiChnCfg->stNrP2.u32Height  = u32HgtReal;
        pstDeiChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstDeiChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
        pstDeiChnCfg->stNrP2.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

        s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_CUR, (HI_VOID *) &pstDeiChnCfg->stNrP2, pArg);
        XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

        if (pstDeiCfg->dei_en == HI_TRUE)
        {
            //read p3
            pstDeiChnCfg->stP3.bEn = HI_TRUE;
            pstDeiChnCfg->stP3.enBitWidth = u32bitwth;//base on nr rfr bitwidth
            pstDeiChnCfg->stP3.u32Width   = u32WthReal;
            pstDeiChnCfg->stP3.u32Height  = u32HgtReal;
            pstDeiChnCfg->stP3.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
            pstDeiChnCfg->stP3.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = (0 == u32bitwth) ? ALIGN_ANYBW_16BTYE(u32WthReal, 8) : ALIGN_ANYBW_16BTYE(u32WthReal, 10);
            pstDeiChnCfg->stP3.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

            s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REF, (HI_VOID *) &pstDeiChnCfg->stP3, pArg);
            XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

            //read p3i
            pstDeiChnCfg->stP3I.bEn = HI_TRUE;
            pstDeiChnCfg->stP3I.enBitWidth = CBB_BITWIDTH_8BIT;
            pstDeiChnCfg->stP3I.u32Width   = u32WthReal;
            pstDeiChnCfg->stP3I.u32Height  = u32HgtReal;
            pstDeiChnCfg->stP3I.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = ALIGN_8bit_16BTYE(u32WthReal);
            pstDeiChnCfg->stP3I.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = ALIGN_8bit_16BTYE(u32WthReal);
            pstDeiChnCfg->stP3I.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

            s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_READ_REE, (HI_VOID *) &pstDeiChnCfg->stP3I, pArg);
            XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

            //di st
            pstDeiChnCfg->stInfoDiSt.bEn       = HI_TRUE;
            pstDeiChnCfg->stInfoDiSt.bSmmu_R   = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoDiSt.bSmmu_W   = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoDiSt.u32Wth    = (u32WthReal + 2) / 4;
            pstDeiChnCfg->stInfoDiSt.u32Hgt    = u32HgtReal;
            pstDeiChnCfg->stInfoDiSt.u32Stride = ((pstDeiChnCfg->stInfoDiSt.u32Wth * 16 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Dei_ST(&pstDeiChnCfg->stInfoDiSt, stRegAddr);
        }

        if (pstDeiCfg->mcdi_en == HI_TRUE)
        {
            //write di rfr
            pstDeiChnCfg->stDiRfr.bEn = HI_TRUE;
            pstDeiChnCfg->stDiRfr.enBitWidth = CBB_BITWIDTH_8BIT;
            pstDeiChnCfg->stDiRfr.u32Width   = u32WthReal;
            pstDeiChnCfg->stDiRfr.u32Height  = u32HgtReal;
            pstDeiChnCfg->stDiRfr.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_Y = ALIGN_8bit_16BTYE(u32WthReal);
            pstDeiChnCfg->stDiRfr.stAddr[CBB_FREAM_BUF_8BIT].u32Stride_C = ALIGN_8bit_16BTYE(u32WthReal);
            pstDeiChnCfg->stDiRfr.stAddr[CBB_FREAM_BUF_8BIT].bSmmu_Y = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;

            s32ReturnVal = VPSS_CBB_FRAME_SetConfig(stRegAddr, CBB_FRAME_WRITE_CUE, (HI_VOID *) &pstDeiChnCfg->stDiRfr, pArg);
            XDP_ASSERT(s32ReturnVal == HI_SUCCESS);

            //blk mv
            pstDeiChnCfg->stInfoBlkmv.bEn        = HI_TRUE;
            pstDeiChnCfg->stInfoBlkmv.bSmmu_Cur  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoBlkmv.bSmmu_Nx1  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoBlkmv.bSmmu_Ref  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoBlkmv.u32Wth     = (u32WthReal + 7) / 8;
            pstDeiChnCfg->stInfoBlkmv.u32Hgt     = (u32HgtReal + 3) / 4;
            pstDeiChnCfg->stInfoBlkmv.u32Stride    = ((pstDeiChnCfg->stInfoBlkmv.u32Wth * 64 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Blkmv(&pstDeiChnCfg->stInfoBlkmv, stRegAddr);

            if (pstDeiCfg->dei_en == HI_TRUE)
            {
                //blk mt
                pstDeiChnCfg->stInfoBlkmt.bEn        = HI_TRUE;
                pstDeiChnCfg->stInfoBlkmt.bSmmu_Cur  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
                pstDeiChnCfg->stInfoBlkmt.bSmmu_Ref  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
                pstDeiChnCfg->stInfoBlkmt.u32Wth     = (u32WthReal + 7) / 8;
                pstDeiChnCfg->stInfoBlkmt.u32Hgt     = (u32HgtReal + 3) / 4;
                pstDeiChnCfg->stInfoBlkmt.u32Stride    = ((pstDeiChnCfg->stInfoBlkmt.u32Wth * 8 + 7) / 8 + 15) / 16 * 16;

                VPSS_InfoCfg_Blkmt(&pstDeiChnCfg->stInfoBlkmt, stRegAddr);

                //di stcnt
                pstDeiChnCfg->stInfoDiStCnt.bEn      = HI_TRUE;
                pstDeiChnCfg->stInfoDiStCnt.bSmmu_r  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
                pstDeiChnCfg->stInfoDiStCnt.bSmmu_w  = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
                pstDeiChnCfg->stInfoDiStCnt.u32Width     = (u32WthReal + 2) / 4;
                pstDeiChnCfg->stInfoDiStCnt.u32Hight     = u32HgtReal;
                pstDeiChnCfg->stInfoDiStCnt.u32Stride    = ((pstDeiChnCfg->stInfoDiStCnt.u32Width * 8 + 7) / 8 + 15) / 16 * 16;

                VPSS_InfoCfg_Di(&pstDeiChnCfg->stInfoDiStCnt, stRegAddr);
            }
        }

        if (pstDeiCfg->rgme_en == HI_TRUE)
        {
            //rgmv
            pstDeiChnCfg->stInfoRgmv.bEn       = HI_TRUE;
            pstDeiChnCfg->stInfoRgmv.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoRgmv.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoRgmv.bSmmu_Nx1 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoRgmv.u32Wth    = u32RgmvNumH;
            pstDeiChnCfg->stInfoRgmv.u32Hgt    = u32RgmvNumV;
            pstDeiChnCfg->stInfoRgmv.u32Stride = ((u32RgmvNumH * 64 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Rgmv(&pstDeiChnCfg->stInfoRgmv, stRegAddr);

            //prjh
            pstDeiChnCfg->stInfoPrjh.bEn       = HI_TRUE;
            pstDeiChnCfg->stInfoPrjh.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoPrjh.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoPrjh.u32Wth    = u32RgmvNumH * 128;
            pstDeiChnCfg->stInfoPrjh.u32Hgt    = u32RgmvNumV;
            pstDeiChnCfg->stInfoPrjh.u32Stride = ((pstDeiChnCfg->stInfoPrjh.u32Wth * 16 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Prjh(&pstDeiChnCfg->stInfoPrjh, stRegAddr);

            //prjv
            pstDeiChnCfg->stInfoPrjv.bEn       = HI_TRUE;
            pstDeiChnCfg->stInfoPrjv.bSmmu_Cur = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoPrjv.bSmmu_Nx2 = XDP_MMU_TEST ? HI_TRUE : HI_FALSE;
            pstDeiChnCfg->stInfoPrjv.u32Wth    = u32RgmvNumH * 16;
            pstDeiChnCfg->stInfoPrjv.u32Hgt    = u32RgmvNumV;
            pstDeiChnCfg->stInfoPrjv.u32Stride = ((pstDeiChnCfg->stInfoPrjv.u32Wth * 16 + 7) / 8 + 15) / 16 * 16;

            VPSS_InfoCfg_Prjv(&pstDeiChnCfg->stInfoPrjv, stRegAddr);
        }
    }

    return ;
}

#if 0
HI_VOID VPSS_FUNC_SetDeiMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_DEI_CFG_S *pstCfg)
{

    HI_U32 in_width  = pstCfg->width;
    HI_U32 in_height = pstCfg->height;
    HI_U32 pro = pstCfg->pro;

    int width = in_width;
    int height = (pro == 1) ? in_height : in_height / 2 ;
    //int cur_bfield, bt_mode, meds, yuv422, pre_motion_en;
    //int meds=0;
    //int two_four_pxl_share=0;
    //int dei_en=pstCfg->dei_en;
    int mcdi_en = pstCfg->mcdi_en;
    //int rgme_en = pstCfg->rgme_en;
    //int width_me = meds ? width/2 : width;

    //int h_rg_num  = (width_me + 33)/64;
    //int v_rg_num  = (height + 5   )/8 ;
    //int h_blk_num = (width_me + 7 )/8 ;
    //int v_blk_num = (height + 3   )/4 ;

    //int h_rg_offset = (width_me - h_rg_num * 64)/2 > 0 ? (width_me - h_rg_num * 64)/2 : 0;
    //int v_rg_offset = (height   - v_rg_num * 8 )/2 > 0 ? (height   - v_rg_num * 8 )/2 : 0;
    //int h_rg_lst_offset = (h_rg_num * 64 - (width_me - 2*h_rg_offset)) > 0 ? (h_rg_num * 64 - (width_me - 2*h_rg_offset)) : 0;
    //int v_rg_lst_offset = (v_rg_num * 8  - (height   - 2*v_rg_offset)) > 0 ? (v_rg_num * 8  - (height   - 2*v_rg_offset)) : 0;


    // CFG
    // **** PERL_GEN_BEG ****
    HI_U32    lmt_rgdify                          = 511;    //0~1023
    HI_U32    core_rgdify                         = 7;      //0~15
    HI_U32    g_rgdifycore                        = 1023;   //0~1023
    HI_U32    k_rgdifycore                        = 2;      //0~15
    HI_U32    g_tpdif_rgsad                        = 255;    //0~511
    HI_U32    k_tpdif_rgsad                        = 16;     //0~63
    HI_U32    kmv_rgsad                            = 15;     //0~127
    HI_U32    coef_sadlpf                          = 1;      //0~5
    HI_U32    th_0mvsad_rgmv                        = 512;    //0~1023
    HI_U32    th_saddif_rgmv                        = 256;    //0~511
    HI_U32    thmag_rgmv                            = 0 ;     //0~255
    HI_U32    lmt_mag_rg                          = 255;    //0~1023
    HI_U32    core_mag_rg                         = 3;      //0~15
    HI_U32    en_mvadj_rgmvls                     = 1;      //0~1
    HI_U32    th_mvadj_rgmvls                     = 8;      //0~15
    HI_U32    k_mag_rgmvls                        = 8;      //0~15
    //    HI_U32    core_mag_rgmvls                     = 15;     //0~31
    //    HI_U32    core_mag_rgmvls                     = 63;     //0~127
    HI_U32    core_mag_rgmvls                     = (rand() % 128) - 64; //63;     //-64~63
    HI_U32    k_mv_rgmvls                         = 16;     //0~31
    HI_U32    core_mv_rgmvls                      = 15;     //0~31
    HI_U32    k_sadcore_rgmv                        = 8;      //0~15
    HI_U32    th_sad_rgls                           = 8;      //0~31
    HI_U32    th_mag_rgls                           = 40;     //0~63
    HI_U32    k_sad_rgls                            = 8;      //0~15
    //    HI_U32    force_mvx                              = 0;      //-127~127
    HI_U32    force_mvx                              = 0;      //-63~63
    HI_U32    force_mven                             = 0;      //0~1
    HI_U32    th_hblkdist_mvdlt                     = 15; //4;   //0~15
    HI_U32    th_vblkdist_mvdlt                     = 15; //1;   //0~15
    HI_U32    th_ls_mvdlt                           = 0; //8;   //0~15
    HI_U32    th_rgmvx_mvdlt                        = 0; //4;   //0~15
    HI_U32    th_blkmvx_mvdlt                       = 7; //6;   //0~7
    HI_U32    thh_sad_mvdlt                         = 0; //16;  //0~31
    HI_U32    thl_sad_mvdlt                         = 127; //96;  //0~127
    HI_U32    g_mag_mvdlt                           = 16; //0~63
    HI_U32    th_mag_mvdlt                          = 31; //12;  //0~31
    HI_U32    k_sadcore_mvdlt                       = 2;  //0~7
    HI_U32    k_core_simimv                       = 8;  //0~31
    HI_U32    gl_core_simimv                      = 0;  //0~7
    HI_U32    gh_core_simimv                      = 15; //0~63
    HI_U32    k_simimvw                           = 32; //0~63
    HI_U32    k_rglsw                             = 20; //0~31
    HI_U32    rgtb_en_mcw                         = 1;  //0~1
    HI_U32    core_mvy_mcw                        = 3;  //0~7
    HI_U32    k_mvy_mcw                           = 16; //0~63
    HI_U32    core_rgsadadj_mcw                   = 64; //0~511
    HI_U32    k_rgsadadj_mcw                      = 8;  //0~15
    HI_U32    k_core_vsaddif                      = 16; //0~31
    HI_U32    gl_core_vsaddif                     = 8;  //0~31
    HI_U32    gh_core_vsad_dif                    = 64; //0~127
    HI_U32    k_vsaddifw                          = 8;  //0~63
    HI_U32    mode_rgysad_mcw                     = 0;  //0~1
    HI_U32    core_rgmag_mcw                      = 24; //0~255
    HI_U32    x0_rgmag_mcw                        = 64; //0~511
    HI_U32    k0_rgmag_mcw                        = 256; //0~511
    HI_U32    g0_rgmag_mcw                        = 64; //0~255
    HI_U32    k1_rgmag_mcw                        = 320; //0~511
    HI_U32    core_rgsad_mcw                      = 96; //0~255
    HI_U32    x0_rgsad_mcw                        = 512; //0~1023
    HI_U32    k0_rgsad_mcw                        = 160; //0~511
    HI_U32    g0_rgsad_mcw                        = 255; //0~255
    HI_U32    k1_rgsad_mcw                        = 128; //0~511
    HI_U32    x0_smrg_mcw                         = 16; //0~255
    HI_U32    k0_smrg_mcw                         = 64; //0~255
    HI_U32    x_rgsad_mcw                         = 112; //0~255
    HI_U32    k_rgsad_mcw                         = 24; //0~63
    HI_U32    x0_tpmvdist_mcw                     = 255; //0~255
    HI_U32    k0_tpmvdist_mcw                     = 64; //0~127
    HI_U32    g0_tpmvdist_mcw                     = 0;  //0~255
    HI_U32    k1_tpmvdist_mcw                     = 32; //0~127
    HI_U32    k_minmvdist_mcw                     = 4;  //0~15
    HI_U32    k_avgmvdist_mcw                     = 4;  //0~15
    HI_U32    b_core_tpmvdist_mcw                 = 2;  //0~7
    HI_U32    k_core_tpmvdist_mcw                 = 2;  //0~7
    HI_U32    k_difhcore_mcw                     = 18; //0~31
    HI_U32    k_difvcore_mcw                     = 32; //0~63
    HI_U32    k_max_core_mcw                     = 8;  //fixed
    HI_U32    k_max_dif_mcw                      = 8;  //fixed
    HI_U32    k1_max_mag_mcw                     = 8;  //fixed
    HI_U32    k0_max_mag_mcw                     = 8;  //fixed
    HI_U32    k_tbdif_mcw                        = 15;  //fixed
    HI_U32    k_tbmag_mcw                        = 0;   //fixed
    HI_U32    x0_mag_wnd_mcw                     = 32; //0~127
    HI_U32    k0_mag_wnd_mcw                     = 6;  //0~15
    HI_U32    g0_mag_wnd_mcw                     = 24; //0~63
    HI_U32    k1_mag_wnd_mcw                     = 6;  //0~15
    HI_U32    g1_mag_wnd_mcw                     = 288; //0~511
    HI_U32    x0_sad_wnd_mcw                     = 8;  //0~127
    HI_U32    k0_sad_wnd_mcw                     = 16; //0~31
    HI_U32    g0_sad_wnd_mcw                     = 16; //0~255
    HI_U32    k1_sad_wnd_mcw                     = 16; //0~31
    HI_U32    g1_sad_wnd_mcw                     = 288; //0~511
    HI_U32    k_max_hvdif_dw                 = 4;  //0~15
    HI_U32    gain_lpf_dw                    = 15; //fixed
    HI_U32    core_bhvdif_dw                 = 5;  //fixed
    HI_U32    k_bhvdif_dw                    = 64; //fixed
    HI_U32    b_bhvdif_dw                    = 0;  //fixed
    HI_U32    b_hvdif_dw                     = 0;  //fixed
    HI_U32    core_hvdif_dw                  = 16; //fixed
    HI_U32    k_difv_dw                      = 20; //0~31
    HI_U32    core_mv_dw                     = -2; //fixed
    HI_U32    b_mv_dw                        = 56; //fixed
    HI_U32    x0_hvdif_dw                    = 256; //0~511
    HI_U32    k0_hvdif_dw                    = 8;  //0~15
    HI_U32    g0_hvdif_dw                    = 128; //0~511
    HI_U32    k1_hvdif_dw                    = 8;  //0~15
    HI_U32    x0_mv_dw                       = 8;  //fixed
    HI_U32    k0_mv_dw                       = 16; //fixed
    HI_U32    g0_mv_dw                       = 32; //fixed
    HI_U32    k1_mv_dw                       = 64; //fixed
    HI_U32    x0_mt_dw                       = 32; //0~127
    HI_U32    k0_mt_dw                       = 32; //0~63
    HI_U32    g0_mt_dw                       = 64; //0~255
    HI_U32    k1_mt_dw                       = 32; //0~63
    HI_U32    g0_mv_mt                       = 31; //0~31
    HI_U32    x0_mv_mt                       = 1;  //0~3
    HI_U32    k1_mv_mt                       = 20; //0~31
    HI_U32    b_mt_dw                        = 0;  //0~255
    HI_U32    gain_up_mclpfv                         = 16; //fixed
    HI_U32    gain_dn_mclpfv                         = 16; //fixed
    HI_U32    gain_mclpfh                            = 16; //fixed
    HI_U32    rs_pxlmag_mcw                          = 0;  //0~1
    HI_U32    x_pxlmag_mcw                           = 2;  //0~7
    HI_U32    k_pxlmag_mcw                           = 8;  //0~31
    HI_U32    mclpf_mode                             = 1;  //0~1
    HI_U32    g_pxlmag_mcw                           = 0;  //fixed
    HI_U32    k_y_vertw                              = 8;  //0~31
    HI_U32    k_c_vertw                              = 7;  //0~127
    HI_U32    k_delta                                = 8;  //0~31
    HI_U32    bdh_mcpos                              = 4;  //0~7
    HI_U32    bdv_mcpos                              = 1;  //0~7
    HI_U32    x0_mv_mc                               = 2;  //0~7
    HI_U32    k1_mv_mc                               = 16; //0~63
    HI_U32    x_fstmt_mc                             = 3;  //0~31
    HI_U32    k_fstmt_mc                             = 8;  //0~31
    HI_U32    g_fstmt_mc                             = 31; //0~31
    HI_U32    x_slmt_mc                              = 2;  //0~31
    HI_U32    k_slmt_mc                              = 16; //0~31
    HI_U32    g_slmt_mc                              = 48; //0~63
    HI_U32    x_hfcore_mc                            = 2;  //0~31
    HI_U32    k_hfcore_mc                            = 24; //0~31
    HI_U32    g_hfcore_mc                            = 16; //0~63
    HI_U32    c0_mc                                  = 0;  //0~width-1
    HI_U32    r0_mc                                  = 0;  //0~height-1
    HI_U32    c1_mc                                  = width - 1; //0~width-1
    HI_U32    r1_mc                                  = height - 1; //0~height-1
    HI_U32    mcmvrange                              = 32; //0~32
    HI_U32    scenechange_mc                         = 0;  //0~1
    HI_U32    x_frcount_mc                           = 8;  //0~31
    HI_U32    k_frcount_mc                           = 16; //0~127
    HI_U32    mcstartr                          = 0;  //0~255
    HI_U32    mcstartc                          = 0;  //0~255
    HI_U32    mcendr                            = 0;  //0~255
    HI_U32    mcendc                            = 0;  //0~255
    //while( mcstartr +   mcendr > height - 1 ||
    //       mcstartc +   mcendc > width  - 1){
    //    HI_U32    mcstartr                          = rand()%256;//0;   //0~255
    //    HI_U32    mcstartc                          = rand()%256;//0;   //0~255
    //    HI_U32    mcendr                            = rand()%256;//0;   //0~255
    //    HI_U32    mcendc                            = rand()%256;//0;   //0~255
    //}
    HI_U32    movethdh                          = 32; //0~32
    HI_U32    movethdl                          = 32; //0~32
    HI_U32    movecorig                         = 0;  //0~32
    HI_U32    movegain                          = 1;  //0~32
    HI_U32    demo_en                               = rand() % 5 == 0 ? 1 : 0;
    HI_U32    demo_mode_l                           = rand() % 3;
    HI_U32    demo_mode_r                           = rand() % 3;
    HI_U32    demo_border                           = rand() % (width + 1);

    // s3 add
    HI_U32    core_rglsw                          = 0;  //rand()%8;
    HI_U32    k0_hfvline                          = 4;  //rand()%8;
    HI_U32    k1_hfvline                          = 2;  //rand()%8;
    HI_U32    core_hfvline                        = 15; //rand()%64;
    HI_U32    k0_hw                               = 16; //rand()%64;
    HI_U32    k1_hw                               = 32; //rand()%64;
    HI_U32    g_hw                                = 80; //rand()%128;
    HI_U32    b_core0_hw                          = 0;  //rand()%16;
    HI_U32    k_core0_hw                          = 4;  //rand()%16;
    HI_U32    core1_hw                            = 3;  //rand()%16;
    HI_U32    subpix_mc_en                        = 1;  //rand()%16;
    HI_U32    g_difcore_mcw                       = 208;//rand()%512;
    HI_U32    rp_k1_mag_wnd_mcw                   = 10; //rand()%16;
    HI_U32    rp_k1_sad_wnd_mcw                   = 10; //rand()%32;
    HI_U32    x0_sadr_wnd_mcw                     = 8;  //rand()%128;
    HI_U32    k0_sadr_wnd_mcw                     = 4;  //rand()%16;
    HI_U32    g0_sadr_wnd_mcw                     = 4;  //rand()%256;
    HI_U32    k1_sadr_wnd_mcw                     = 4;  //rand()%16;
    HI_U32    g1_sadr_wnd_mcw                     = 288;//rand()%512;
    HI_U32    k_p1cfdifh_mcw                      = 6;  //rand()%16;
    HI_U32    k_mcdifv_mcw                        = 12; //rand()%16;
    HI_U32    th_cur_blksad                       = 128;//rand()%512;
    HI_U32    thh_neigh_blksad                    = 256;//rand()%512;
    HI_U32    thl_neigh_blksad                    = 128;//rand()%512;
    HI_U32    th_cur_blkmotion                    = 8;  //rand()%32;
    HI_U32    th_rgmv_mag                         = 512;//rand()%1024;
    HI_U32    blkmv_update_en                     = 1;  //rand()%2;
    HI_U32    k_rpcounter                         = 3;  //rand()%8;
    HI_U32    rpcounterth                         = 2;  //rand()%8;
    HI_U32    rp_mvxth_rgmv                       = 3;  //rand()%8;
    HI_U32    rp_difmvxth_rgmv                    = 5;  //rand()%16;
    HI_U32    rp_difsadth_rgmv                    = 32; //rand()%256;
    HI_U32    rp_sadth_rgmv                       = 125;//rand()%512;
    HI_U32    rp_magth_rgmv                       = 600;//rand()%1024;
    HI_U32    rp_difmvxth_sp                      = 2;  //rand()%8;
    HI_U32    rp_difsadth_tb                      = 428;//rand()%512;
    HI_U32    k1_tpdif_rgsad                      = 63; //rand()%64;
    HI_U32    submv_sadchk_en                     = 0;  //fixed
    HI_U32    rp_en                               = 0;  //rand()%2;
    HI_U32    difvt_mode                          = 1;  //rand()%2;
    //    HI_U32    mcw_blkm_thdh                         = 32; //no use, in rm and rtl fixed 32
    //    HI_U32    mcw_blkm_thdl                         = 0;  //no use, in rm and rtl fixed 32
    //    HI_U32    mcw_blkm_coringmove                   = 0;  //no use, in rm and rtl fixed 0
    //    HI_U32    mcw_blkm_gainmove                     = 4;  //no use, in rm and rtl fixed 0
    HI_U32    cntlut_0                         = 2;
    HI_U32    cntlut_1                         = 2;
    HI_U32    cntlut_2                         = 1;
    HI_U32    cntlut_3                         = 1;
    HI_U32    cntlut_4                         = -15;
    HI_U32    cntlut_5                         = -15;
    HI_U32    cntlut_6                         = -15;
    HI_U32    cntlut_7                         = -15;
    HI_U32    cntlut_8                         = -15;
    HI_U32    mc_mtshift                       = 0;
    HI_U32    mcw_scnt_en                      = 1;
    HI_U32    mcw_scnt_gain                    = 273;

    //ma cas
    HI_U32    edge_smooth_ratio                       = 128; //rand()%256;
    HI_U32    stinfo_stop                             = 0; // fixed
    HI_U32    die_rst                                 = 0;
    HI_U32    mchdir_c                                = 0; //rand()%2;
    HI_U32    mchdir_l                                = 0; //rand()%2;
    HI_U32    edge_smooth_en                          = 0; //rand()%2;
    HI_U32    ma_only                                 = (rand() % 3 == 0 ? 1 : 0) || ~mcdi_en;
    HI_U32    mc_only                                 = rand() % 2;
    HI_U32    die_c_mode                              = 1;
    HI_U32    die_l_mode                              = 1;
    HI_U32    die_out_sel_c                           = 0; //rand()%5 == 0 ? 1 : 0;
    HI_U32    die_out_sel_l                           = 0; //rand()%5 == 0 ? 1 : 0;
    HI_U32    recmode_frmfld_blend_mode               = 0;  //fixed
    HI_U32    frame_motion_smooth_en                  = 1; //rand()%2;
    HI_U32    luma_scesdf_max                         = 0; //rand()%2;
    HI_U32    motion_iir_en                           = 1; //rand()%2;
    HI_U32    luma_mf_max                             = 0; //rand()%4 == 0 ? 1 : 0; //1: mf==3ff
    HI_U32    chroma_mf_max                           = 0; //rand()%4 == 0 ? 1 : 0; //1: mf==3ff
    HI_U32    rec_mode_en                             = 1; //rand()%2;
    HI_U32    dei_st_rst_value                        = rand() % 65536;
    HI_U32    chroma_mf_offset                        = 8; //rand()%256;
    HI_U32    rec_mode_output_mode                   = 0; //rand()%2;
    HI_U32    rec_mode_set_pre_info_mode             = 0; //rand()%3;
    HI_U32    dir_ratio_north                        = 2; //rand()%16;
    HI_U32    min_north_strength                     = 320; //32767 - rand()%65536;
    HI_U32    range_scale                            = 8; //rand()%256;
    HI_U32    bc1_max_dz                            = 30; //(BITDEPTH == 8) ? rand()%64 : rand()%256;
    HI_U32    bc1_autodz_gain                       = 2; //rand()%16;
    HI_U32    bc1_gain                              = 8; //rand()%16;
    HI_U32    bc2_max_dz                            = 30; //(BITDEPTH == 8) ? rand()%64 : rand()%256;
    HI_U32    bc2_autodz_gain                       = 2; //rand()%16;
    HI_U32    bc2_gain                              = 8; //rand()%16;
    HI_U32    dir0_scale                            = 16; //rand()%64;
    HI_U32    dir1_scale                            = 40; //rand()%64;
    HI_U32    dir2_scale                            = 32; //rand()%64;
    HI_U32    dir3_scale                            = 27; //rand()%64;
    HI_U32    dir4_scale                            = 18; //rand()%64;
    HI_U32    dir5_scale                            = 15; //rand()%64;
    HI_U32    dir6_scale                            = 12; //rand()%64;
    HI_U32    dir7_scale                            = 11; //rand()%64;
    HI_U32    dir8_scale                           = 9; //rand()%64;
    HI_U32    dir9_scale                           = 8; //rand()%64;
    HI_U32    dir10_scale                          = 7; //rand()%64;
    HI_U32    dir11_scale                          = 6; //rand()%64;
    HI_U32    dir12_scale                         = 5; //rand()%64;
    HI_U32    dir13_scale                         = 5; //rand()%64;
    HI_U32    dir14_scale                         = 3; //rand()%64;
    HI_U32    cur_state                                = 0;  //no use
    HI_U32    cur_cstate                               = 0;  //no use
    HI_U32    l_height_cnt                             = 0;  //no use
    HI_U32    c_height_cnt                             = 0;  //no use
    HI_U32    intp_scale_ratio_1                  = 4; //rand()%16;
    HI_U32    intp_scale_ratio_2                  = 5; //rand()%16;
    HI_U32    intp_scale_ratio_3                  = 5; //rand()%16;
    HI_U32    intp_scale_ratio_4                  = 6; //rand()%16;
    HI_U32    intp_scale_ratio_5                  = 6; //rand()%16;
    HI_U32    intp_scale_ratio_6                  = 7; //rand()%16;
    HI_U32    intp_scale_ratio_7                  = 7; //rand()%16;
    HI_U32    intp_scale_ratio_8                  = 8; //rand()%16;
    HI_U32    intp_scale_ratio_9                  = 8; //rand()%16;
    HI_U32    intp_scale_ratio_10                 = 8; //rand()%16;
    HI_U32    intp_scale_ratio_11                 = 8; //rand()%16;
    HI_U32    intp_scale_ratio_12                 = 8; //rand()%16;
    HI_U32    intp_scale_ratio_13                 = 8; //rand()%16;
    HI_U32    intp_scale_ratio_14                 = 8; //rand()%16;
    HI_U32    intp_scale_ratio_15                 = 8; //rand()%16;
    HI_U32    bc_gain                               = 64; //rand()%65;
    HI_U32    dir_thd                               = 0; //rand()%16;
    HI_U32    edge_mode                             = 1; //rand()%2;
    HI_U32    hor_edge_en                           = 0; //rand()%2;
    HI_U32    strength_thd                          = 16383; //rand()%65536;
    HI_U32    jitter_gain                           = 8; //rand()%16;
    HI_U32    jitter_coring                         = 0; //rand()%256;
    HI_U32    fld_motion_coring                     = 0; //rand()%256;
    HI_U32    fld_motion_thd_low                    = 0; //rand()%256;
    HI_U32    fld_motion_thd_high                   = 255; //rand()%256;
    //while(    fld_motion_thd_low >     fld_motion_thd_high){
    //        fld_motion_thd_low                    =rand()%256;
    //        fld_motion_thd_high                   =rand()%256;
    //}
    HI_U32    fld_motion_curve_slope                = -2; //rand()%64 - 32;
    HI_U32    fld_motion_gain                       = 8; //rand()%16;
    HI_U32    fld_motion_wnd_mode                   = 1; //rand()%2 ;
    HI_U32    long_motion_shf                       = 1; //rand()%2 ;
    HI_U32    motion_diff_thd_0                = 16; //rand()%256;
    HI_U32    motion_diff_thd_1                = 144; //rand()%256;
    HI_U32    motion_diff_thd_2                = 208; //rand()%256;
    HI_U32    motion_diff_thd_3                = 255; //rand()%256;
    HI_U32    motion_diff_thd_4                = 255; //rand()%256;
    HI_U32    motion_diff_thd_5                = 255; //rand()%256;
    HI_U32    min_motion_iir_ratio             = 32; //rand()%65 ;
    HI_U32    max_motion_iir_ratio             = 64; //rand()%65 ;
    int motion_iir_curve_slope_0, motion_iir_curve_slope_1, motion_iir_curve_slope_2, motion_iir_curve_slope_3;
    int motion_iir_curve_ratio_0, motion_iir_curve_ratio_1, motion_iir_curve_ratio_2, motion_iir_curve_ratio_3, motion_iir_curve_ratio_4;

    HI_U32    rec_mode_fld_motion_step_0           = 2; //rand()%8;
    HI_U32    rec_mode_fld_motion_step_1           = 2; //rand()%8;
    HI_U32    rec_mode_frm_motion_step_0           = 0; //rand()%4;
    HI_U32    rec_mode_frm_motion_step_1           = 0; //rand()%4;
    HI_U32    ppre_info_en                         = 1; //rand()%2;    //s3: fixed 1
    HI_U32    pre_info_en                          = 0; //rand()%2;    //s3: fixed 0
    HI_U32    his_motion_en                        = 1; //rand()%2;
    HI_U32    his_motion_using_mode                = 1; //rand()%2;
    HI_U32    his_motion_write_mode                = 0; //rand()%2;
    HI_U32    his_motion_info_write_mode           = 0; //rand()%2;
    HI_U32    mor_flt_thd                           = 0; //rand()%256;
    HI_U32    mor_flt_size                          = 0; //rand()%4;
    HI_U32    mor_flt_en                            = 1; //rand()%2;
    HI_U32    med_blend_en                          = 0; //rand()%2;
    HI_U32    comb_chk_min_hthd                   = 255; //rand()%256;
    HI_U32    comb_chk_min_vthd                   = 15; //rand()%256;
    HI_U32    comb_chk_lower_limit                = 10; //rand()%256;
    HI_U32    comb_chk_upper_limit                = 160; //rand()%256;
    HI_U32    comb_chk_edge_thd                   = 64; //rand()%128;
    HI_U32    comb_chk_md_thd                     = 30; //rand()%32;
    HI_U32    comb_chk_en                         = 0; //rand()%2;
    HI_S32    frame_motion_smooth_thd0      = 8; //rand()%256;
    HI_S32    frame_motion_smooth_thd1      = 72; //rand()%256;
    HI_S32    frame_motion_smooth_thd2      = 255; //rand()%256;
    HI_S32    frame_motion_smooth_thd3      = 255; //rand()%256;
    HI_S32    frame_motion_smooth_thd4      = 255; //rand()%256;
    HI_S32    frame_motion_smooth_thd5      = 255; //rand()%256;
    HI_U32    frame_motion_smooth_ratio_min = 0; //rand()%65;
    HI_U32    frame_motion_smooth_ratio_max = 64; //rand()%65;
    // CLIP3
    int frame_motion_smooth_ratio0, frame_motion_smooth_ratio1, frame_motion_smooth_ratio2, frame_motion_smooth_ratio3, frame_motion_smooth_ratio4;
    int frame_motion_smooth_slope0, frame_motion_smooth_slope1, frame_motion_smooth_slope2, frame_motion_smooth_slope3;

    HI_S32    frame_field_blend_thd0       = 8; //rand()%256;
    HI_S32    frame_field_blend_thd1       = 72; //rand()%256;
    HI_S32    frame_field_blend_thd2       = 255; //rand()%256;
    HI_S32    frame_field_blend_thd3       = 255; //rand()%256;
    HI_S32    frame_field_blend_thd4       = 255; //rand()%256;
    HI_S32    frame_field_blend_thd5       = 255; //rand()%256;
    HI_U32    frame_field_blend_ratio_min  = 0;//rand()%65;
    HI_U32    frame_field_blend_ratio_max  = 64;//rand()%65;
    int frame_field_blend_ratio0, frame_field_blend_ratio1, frame_field_blend_ratio2, frame_field_blend_ratio3, frame_field_blend_ratio4;
    int frame_field_blend_slope0, frame_field_blend_slope1, frame_field_blend_slope2, frame_field_blend_slope3;

    HI_U32    motion_adjust_gain                    = 64;//rand()%256;
    HI_U32    motion_adjust_coring                  = 0;//rand()%64;
    HI_U32    motion_adjust_gain_chr                = 64;//rand()%256;
    //    HI_U32    dir0_scale                            =16;//rand()%64;
    //    HI_U32    dir1_scale                            =40;//rand()%64;
    //    HI_U32    dir2_scale                            =32;//rand()%64;
    //    HI_U32    dir3_scale                            =27;//rand()%64;
    //    HI_U32    dir4_scale                            =18;//rand()%64;
    //    HI_U32    dir5_scale                            =15;//rand()%64;
    //    HI_U32    dir6_scale                            =12;//rand()%64;
    //    HI_U32    dir7_scale                            =11;//rand()%64;
    //    HI_U32    dir8_scale                           =9;//rand()%64;
    //    HI_U32    dir9_scale                           =8;//rand()%64;
    //    HI_U32    dir10_scale                          =7;//rand()%64;
    //    HI_U32    dir11_scale                          =6;//rand()%64;
    HI_U32    edge_norm_0                        = 65535 / ( dir0_scale * 2 * 3 * 3); //rand()%4096;
    HI_U32    edge_norm_1                        = 65535 / ( dir1_scale * 4 * 3); //rand()%4096;
    HI_U32    edge_norm_2                        = 65535 / ( dir2_scale * 5 * 3); //rand()%4096;
    HI_U32    edge_norm_3                        = 65535 / ( dir3_scale * 7 * 3); //rand()%4096;
    HI_U32    edge_norm_4                        = 65535 / ( dir4_scale * 9 * 3); //rand()%4096;
    HI_U32    edge_norm_5                        = 65535 / ( dir5_scale * 11 * 3); //rand()%4096;
    HI_U32    mc_strength_k3                     = -8; //0;
    HI_U32    edge_norm_6                        = 65535 / ( dir6_scale * 13 * 3); //rand()%4096;
    HI_U32    edge_norm_7                        = 65535 / ( dir7_scale * 15 * 3); //rand()%4096;
    HI_U32    mc_strength_g3                     = 128; //0;
    HI_U32    edge_norm_8                        = 65535 / ( dir8_scale * 17 * 3); //rand()%4096;
    HI_U32    edge_norm_9                        = 65535 / ( dir9_scale * 19 * 3); //rand()%4096;
    HI_U32    inter_diff_thd0                    = 16; //rand()%256;
    HI_U32    edge_norm_10                       = 65535 / (    dir10_scale * 23 * 3); //rand()%4096;
    HI_U32    edge_norm_11                       = 65535 / (    dir11_scale * 27 * 3); //rand()%4096;
    HI_U32    inter_diff_thd1                    = 80; //rand()%256;
    HI_U32    edge_coring                        = 16; //rand()%1024;
    HI_U32    edge_scale                         = 64; //rand()%1024;
    HI_U32    inter_diff_thd2                    = 128; //rand()%256;
    HI_U32    mc_strength_k0                   = 0; //rand()%256 - 128;
    HI_U32    mc_strength_k1                   = 7; //rand()%256 - 128;
    HI_U32    mc_strength_k2                   = 0; //rand()%256 - 128;
    HI_U32    mc_strength_g0                   = 16; //rand()%256;
    HI_U32    mc_strength_g1                   = 16; //rand()%256;
    HI_U32    mc_strength_g2                   = 128; //rand()%256;
    HI_U32    mc_strength_ming                 = 16; //rand()%256;
    HI_U32    mc_strength_maxg                 = 128; //rand()%256;
    HI_U32    k_y_mcw                              = 64; //rand()%128;
    HI_U32    k_y_mcbld                            = 64; //rand()%128;
    HI_U32    k_c_mcw                              = 32; //rand()%128;
    HI_U32    k_c_mcbld                            = 32; //rand()%128;
    HI_U32    x0_mcw_adj                           = 64; //rand()%256;
    HI_U32    k0_mcw_adj                           = 64; //rand()%256;
    HI_U32    g0_mcw_adj                           = 1023; //rand()%4096;
    HI_U32    k1_mcw_adj                           = 128; //rand()%256;
    HI_U32    x0_mcbld                             = 64; //rand()%256;
    HI_U32    k0_mcbld                             = 64; //rand()%256;
    HI_U32    k1_mcbld                             = 128; //rand()%256;
    HI_U32    g0_mcbld                             = 1023; //rand()%4096;
    HI_U32    k_curw_mcbld                         = 8; //rand()%17;
    HI_U32    mc_lai_bldmode                       = 1; //rand()%2;
    HI_U32    numt_lpf_en                           = 0; //rand()%2;
    HI_U32    numt_coring                           = 0; //rand()%64;
    HI_U32    numt_gain                             = 32; //rand()%256;
    HI_U32    mc_numt_blden                         = 1; //rand()%2;
    HI_U32    ma_gbm_thd1                        = 0;
    HI_U32    ma_gbm_thd0                        = 0;
    HI_U32    ma_gbm_thd3                        = 0;
    HI_U32    ma_gbm_thd2                        = 0;
    HI_U32    mtth0_gmd                         = 0;
    HI_U32    mtth1_gmd                         = 0;
    HI_U32    mtth2_gmd                         = 0;
    HI_U32    mtth3_gmd                         = 0;
    HI_U32    mtfilten_gmd                      = 0;
    HI_U32    k_maxmag_gmd                      = 0;
    HI_U32    k_difh_gmd                        = 0;
    HI_U32    k_mag_gmd                         = 0;
    HI_U32    kmagh_1                                = 31; // rand()%128;
    HI_U32    kmagh_2                                = 31; // rand()%128;
    HI_U32    kmagv_1                                = 8; // rand()%32;
    HI_U32    kmagv_2                                = 2; // rand()%32;
    HI_U32    khoredge                               = 31; // rand()%32;
    HI_U32    scaler_horedge                         = 2; // rand()%8;
    HI_U32    frame_mag_en                           = 1; // rand()%2;
    HI_U32    motion_limt_1                          = 60; // rand()%256;
    HI_U32    motion_limt_2                          = 60; // rand()%256;
    HI_U32    scaler_framemotion                     = 4; // rand()%8;
    HI_U32    dir_ratio_c                           = rand() % 16;
    HI_U32    edge_str_coring_c                     = rand() % 32;

    HI_U32 hist_thd0                         = rand() % 256;
    HI_U32 hist_thd1                         = rand() % 256;
    HI_U32 hist_thd2                         = rand() % 256;
    HI_U32 hist_thd3                         = rand() % 256;
    HI_U32 mov_coring_blk                    = rand() % 256;
    HI_U32 mov_coring_tkr                    = rand() % 256;
    HI_U32 mov_coring_norm                   = rand() % 256;
    HI_U32 bitsmov2r                         = rand() % 8;
    HI_U32 lasi_mode                         = rand() % 2;
    HI_U32 diff_movblk_thd                   = rand() % 256;
    HI_U32 um_thd0                           = rand() % 256;
    HI_U32 um_thd1                           = rand() % 256;
    HI_U32 um_thd2                           = rand() % 256;
    HI_U32 coring_tkr                        = rand() % 256;
    HI_U32 coring_norm                       = rand() % 256;
    HI_U32 coring_blk                        = rand() % 256;
    HI_U32 pcc_hthd                          = rand() % 256;
    HI_U32 pcc_vthd0                         = rand() % 256;
    HI_U32 pcc_vthd1                         = rand() % 256;
    HI_U32 pcc_vthd2                         = rand() % 256;
    HI_U32 pcc_vthd3                         = rand() % 256;
    HI_U32 itdiff_vthd0                      = rand() % 256;
    HI_U32 itdiff_vthd1                      = rand() % 256;
    HI_U32 itdiff_vthd2                      = rand() % 256;
    HI_U32 itdiff_vthd3                      = rand() % 256;
    HI_U32 lasi_coring_thd                   = uGetRandEx(255, 0);
    HI_U32 lasi_edge_thd                     = uGetRandEx(255, 0);
    HI_U32 lasi_mov_thd                      = uGetRandEx(255, 0);
    HI_U32 lasi_txt_alpha                    = uGetRandEx(255, 0);
    HI_U32 lasi_txt_coring                   = uGetRandEx(255, 0);
    HI_U32 lasi_txt_thd0                     = uGetRandEx(255, 0);
    HI_U32 lasi_txt_thd1                     = uGetRandEx(255, 0);
    HI_U32 lasi_txt_thd2                     = uGetRandEx(255, 0);
    HI_U32 lasi_txt_thd3                     = uGetRandEx(255, 0);
    HI_U32 region1_y_stt                     = uGetRandEx(pstCfg->height - 1, 0);
    HI_U32 region1_y_end                     = uGetRandEx(pstCfg->height - 1, region1_y_stt);


    motion_iir_curve_slope_0           = 1; //rand()%64 - 32;
    motion_iir_curve_slope_1           = 2; //rand()%64 - 32;
    motion_iir_curve_slope_2           = 0; //rand()%64 - 32;
    motion_iir_curve_slope_3           = 0; //rand()%64 - 32;


    motion_iir_curve_ratio_0 = 32;//rand()%128;
    motion_iir_curve_ratio_1 = uGetRand(0, 127); //CLIP3(0, 127, motion_iir_curve_ratio_0+((motion_iir_curve_slope_0*(motion_diff_thd_1-motion_diff_thd_0)+HALFVALUE)>>SHIFT));
    motion_iir_curve_ratio_2 = uGetRand(0, 127); //CLIP3(0, 127, motion_iir_curve_ratio_1+((motion_iir_curve_slope_1*(motion_diff_thd_2-motion_diff_thd_1)+HALFVALUE)>>SHIFT));
    motion_iir_curve_ratio_3 = uGetRand(0, 127); //CLIP3(0, 127, motion_iir_curve_ratio_2+((motion_iir_curve_slope_2*(motion_diff_thd_3-motion_diff_thd_2)+HALFVALUE)>>SHIFT));
    motion_iir_curve_ratio_4 = uGetRand(0, 127); //CLIP3(0, 127, motion_iir_curve_ratio_3+((motion_iir_curve_slope_3*(motion_diff_thd_4-motion_diff_thd_3)+HALFVALUE)>>SHIFT));


    frame_motion_smooth_slope0  = 8; //rand()%64 - 32;
    frame_motion_smooth_slope1  = 0; //rand()%64 - 32;
    frame_motion_smooth_slope2  = 0; //rand()%64 - 32;
    frame_motion_smooth_slope3  = 0; //rand()%64 - 32;

    frame_motion_smooth_ratio0 = 0;//rand()%128;
    frame_motion_smooth_ratio1 = uGetRand(0, 127); //CLIP3(0, 127, frame_motion_smooth_ratio0+ ((frame_motion_smooth_slope0*(frame_motion_smooth_thd1-frame_motion_smooth_thd0)+HALFVALUE)>>SHIFT));
    frame_motion_smooth_ratio2 = uGetRand(0, 127); //CLIP3(0, 127, frame_motion_smooth_ratio1+ ((frame_motion_smooth_slope1*(frame_motion_smooth_thd2-frame_motion_smooth_thd1)+HALFVALUE)>>SHIFT));
    frame_motion_smooth_ratio3 = uGetRand(0, 127); //CLIP3(0, 127, frame_motion_smooth_ratio2+ ((frame_motion_smooth_slope2*(frame_motion_smooth_thd3-frame_motion_smooth_thd2)+HALFVALUE)>>SHIFT));
    frame_motion_smooth_ratio4 = uGetRand(0, 127); //CLIP3(0, 127, frame_motion_smooth_ratio3+ ((frame_motion_smooth_slope3*(frame_motion_smooth_thd4-frame_motion_smooth_thd3)+HALFVALUE)>>SHIFT));

    frame_field_blend_slope0      = 8;//rand()%64 - 32;
    frame_field_blend_slope1      = 0;//rand()%64 - 32;
    frame_field_blend_slope2      = 0;//rand()%64 - 32;
    frame_field_blend_slope3      = 0;//rand()%64 - 32;

    frame_field_blend_ratio0 = 0;//rand()%128;
    frame_field_blend_ratio1 = uGetRand(0, 127); //CLIP3(0, 127, frame_field_blend_ratio0+((frame_field_blend_slope0*(frame_field_blend_thd1-frame_field_blend_thd0)+HALFVALUE)>>SHIFT));
    frame_field_blend_ratio2 = uGetRand(0, 127); //CLIP3(0, 127, frame_field_blend_ratio1+((frame_field_blend_slope1*(frame_field_blend_thd2-frame_field_blend_thd1)+HALFVALUE)>>SHIFT));
    frame_field_blend_ratio3 = uGetRand(0, 127); //CLIP3(0, 127, frame_field_blend_ratio2+((frame_field_blend_slope2*(frame_field_blend_thd3-frame_field_blend_thd2)+HALFVALUE)>>SHIFT));
    frame_field_blend_ratio4 = uGetRand(0, 127); //CLIP3(0, 127, frame_field_blend_ratio3+((frame_field_blend_slope3*(frame_field_blend_thd4-frame_field_blend_thd3)+HALFVALUE)>>SHIFT));


    VPSS_Sys_SetDieOutSelL(pstVpssRegs,  u32AddrOffset, die_out_sel_l);
    VPSS_Sys_SetDieOutSelC(pstVpssRegs,  u32AddrOffset, die_out_sel_c);
    VPSS_Sys_SetDieLMode(pstVpssRegs,  u32AddrOffset,  die_l_mode);
    VPSS_Sys_SetDieCMode(pstVpssRegs,  u32AddrOffset,  die_c_mode);
    VPSS_Sys_SetMcOnly(pstVpssRegs,  u32AddrOffset,  mc_only);
    VPSS_Sys_SetMaOnly(pstVpssRegs,  u32AddrOffset,  ma_only);
    VPSS_Sys_SetEdgeSmoothEn(pstVpssRegs,  u32AddrOffset,  edge_smooth_en);
    VPSS_Sys_SetMchdirL(pstVpssRegs,  u32AddrOffset,  mchdir_l);
    VPSS_Sys_SetMchdirC(pstVpssRegs,  u32AddrOffset,  mchdir_c);
    VPSS_Sys_SetDieRst(pstVpssRegs,  u32AddrOffset,  die_rst);
    VPSS_Sys_SetStinfoStop(pstVpssRegs,  u32AddrOffset,  stinfo_stop);
    VPSS_Sys_SetEdgeSmoothRatio(pstVpssRegs,  u32AddrOffset,  edge_smooth_ratio);
    VPSS_Sys_SetChromaMfOffset(pstVpssRegs,  u32AddrOffset,  chroma_mf_offset);
    VPSS_Sys_SetDeiStRstValue(pstVpssRegs,  u32AddrOffset,  dei_st_rst_value);
    VPSS_Sys_SetRecModeEn(pstVpssRegs,  u32AddrOffset,  rec_mode_en);
    VPSS_Sys_SetChromaMfMax(pstVpssRegs,  u32AddrOffset,  chroma_mf_max);
    VPSS_Sys_SetLumaMfMax(pstVpssRegs,  u32AddrOffset,  luma_mf_max);
    VPSS_Sys_SetMotionIirEn(pstVpssRegs,  u32AddrOffset,  motion_iir_en);
    VPSS_Sys_SetLumaScesdfMax(pstVpssRegs,  u32AddrOffset,  luma_scesdf_max);
    VPSS_Sys_SetFrameMotionSmoothEn(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_en);
    VPSS_Sys_SetRecmodeFrmfldBlendMode(pstVpssRegs,  u32AddrOffset,  recmode_frmfld_blend_mode);
    VPSS_Sys_SetMinNorthStrength(pstVpssRegs,  u32AddrOffset,  min_north_strength);
    VPSS_Sys_SetDirRatioNorth(pstVpssRegs,  u32AddrOffset,  dir_ratio_north);
    VPSS_Sys_SetRecModeOutputMode(pstVpssRegs,  u32AddrOffset,  rec_mode_output_mode);
    VPSS_Sys_SetRecModeSetPreInfoMode(pstVpssRegs,  u32AddrOffset,  rec_mode_set_pre_info_mode);
    VPSS_Sys_SetRangeScale(pstVpssRegs,  u32AddrOffset,  range_scale);
    VPSS_Sys_SetBc1Gain(pstVpssRegs,  u32AddrOffset,  bc1_gain);
    VPSS_Sys_SetBc1AutodzGain(pstVpssRegs,  u32AddrOffset,  bc1_autodz_gain);
    VPSS_Sys_SetBc1MaxDz(pstVpssRegs,  u32AddrOffset,  bc1_max_dz);
    VPSS_Sys_SetBc2Gain(pstVpssRegs,  u32AddrOffset,  bc2_gain);
    VPSS_Sys_SetBc2AutodzGain(pstVpssRegs,  u32AddrOffset,  bc2_autodz_gain);
    VPSS_Sys_SetBc2MaxDz(pstVpssRegs,  u32AddrOffset,  bc2_max_dz);
    VPSS_Sys_SetDir3Scale(pstVpssRegs,  u32AddrOffset,  dir3_scale);
    VPSS_Sys_SetDir2Scale(pstVpssRegs,  u32AddrOffset,  dir2_scale);
    VPSS_Sys_SetDir1Scale(pstVpssRegs,  u32AddrOffset,  dir1_scale);
    VPSS_Sys_SetDir0Scale(pstVpssRegs,  u32AddrOffset,  dir0_scale);
    VPSS_Sys_SetDir7Scale(pstVpssRegs,  u32AddrOffset,  dir7_scale);
    VPSS_Sys_SetDir6Scale(pstVpssRegs,  u32AddrOffset,  dir6_scale);
    VPSS_Sys_SetDir5Scale(pstVpssRegs,  u32AddrOffset,  dir5_scale);
    VPSS_Sys_SetDir4Scale(pstVpssRegs,  u32AddrOffset,  dir4_scale);
    VPSS_Sys_SetDir11Scale(pstVpssRegs,  u32AddrOffset,  dir11_scale);
    VPSS_Sys_SetDir10Scale(pstVpssRegs,  u32AddrOffset,  dir10_scale);
    VPSS_Sys_SetDir9Scale(pstVpssRegs,  u32AddrOffset,  dir9_scale);
    VPSS_Sys_SetDir8Scale(pstVpssRegs,  u32AddrOffset,  dir8_scale);
    VPSS_Sys_SetDir14Scale(pstVpssRegs,  u32AddrOffset,  dir14_scale);
    VPSS_Sys_SetDir13Scale(pstVpssRegs,  u32AddrOffset,  dir13_scale);
    VPSS_Sys_SetDir12Scale(pstVpssRegs,  u32AddrOffset,  dir12_scale);
    VPSS_Sys_SetCHeightCnt(pstVpssRegs,  u32AddrOffset,  c_height_cnt);
    VPSS_Sys_SetLHeightCnt(pstVpssRegs,  u32AddrOffset,  l_height_cnt);
    VPSS_Sys_SetCurCstate(pstVpssRegs,  u32AddrOffset,  cur_cstate);
    VPSS_Sys_SetCurState(pstVpssRegs,  u32AddrOffset,  cur_state);
    VPSS_Sys_SetIntpScaleRatio8(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_8);
    VPSS_Sys_SetIntpScaleRatio7(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_7);
    VPSS_Sys_SetIntpScaleRatio6(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_6);
    VPSS_Sys_SetIntpScaleRatio5(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_5);
    VPSS_Sys_SetIntpScaleRatio4(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_4);
    VPSS_Sys_SetIntpScaleRatio3(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_3);
    VPSS_Sys_SetIntpScaleRatio2(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_2);
    VPSS_Sys_SetIntpScaleRatio1(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_1);
    VPSS_Sys_SetIntpScaleRatio15(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_15);
    VPSS_Sys_SetIntpScaleRatio14(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_14);
    VPSS_Sys_SetIntpScaleRatio13(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_13);
    VPSS_Sys_SetIntpScaleRatio12(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_12);
    VPSS_Sys_SetIntpScaleRatio11(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_11);
    VPSS_Sys_SetIntpScaleRatio10(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_10);
    VPSS_Sys_SetIntpScaleRatio9(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_9);
    VPSS_Sys_SetStrengthThd(pstVpssRegs,  u32AddrOffset,  strength_thd);
    VPSS_Sys_SetHorEdgeEn(pstVpssRegs,  u32AddrOffset,  hor_edge_en);
    VPSS_Sys_SetEdgeMode(pstVpssRegs,  u32AddrOffset,  edge_mode);
    VPSS_Sys_SetDirThd(pstVpssRegs,  u32AddrOffset,  dir_thd);
    VPSS_Sys_SetBcGain(pstVpssRegs,  u32AddrOffset,  bc_gain);
    VPSS_Sys_SetFldMotionCoring(pstVpssRegs,  u32AddrOffset,  fld_motion_coring);
    VPSS_Sys_SetJitterCoring(pstVpssRegs,  u32AddrOffset,  jitter_coring);
    VPSS_Sys_SetJitterGain(pstVpssRegs,  u32AddrOffset,  jitter_gain);
    VPSS_Sys_SetLongMotionShf(pstVpssRegs,  u32AddrOffset,  long_motion_shf);
    VPSS_Sys_SetFldMotionWndMode(pstVpssRegs,  u32AddrOffset,  fld_motion_wnd_mode);
    VPSS_Sys_SetFldMotionGain(pstVpssRegs,  u32AddrOffset,  fld_motion_gain);
    VPSS_Sys_SetFldMotionCurveSlope(pstVpssRegs,  u32AddrOffset,  fld_motion_curve_slope);
    VPSS_Sys_SetFldMotionThdHigh(pstVpssRegs,  u32AddrOffset,  fld_motion_thd_high);
    VPSS_Sys_SetFldMotionThdLow(pstVpssRegs,  u32AddrOffset,  fld_motion_thd_low);
    VPSS_Sys_SetMotionDiffThd3(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_3);
    VPSS_Sys_SetMotionDiffThd2(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_2);
    VPSS_Sys_SetMotionDiffThd1(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_1);
    VPSS_Sys_SetMotionDiffThd0(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_0);
    VPSS_Sys_SetMaxMotionIirRatio(pstVpssRegs,  u32AddrOffset,  max_motion_iir_ratio);
    VPSS_Sys_SetMinMotionIirRatio(pstVpssRegs,  u32AddrOffset,  min_motion_iir_ratio);
    VPSS_Sys_SetMotionDiffThd5(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_5);
    VPSS_Sys_SetMotionDiffThd4(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_4);
    VPSS_Sys_SetMotionIirCurveRatio0(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_0);
    VPSS_Sys_SetMotionIirCurveSlope3(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_3);
    VPSS_Sys_SetMotionIirCurveSlope2(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_2);
    VPSS_Sys_SetMotionIirCurveSlope1(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_1);
    VPSS_Sys_SetMotionIirCurveSlope0(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_0);
    VPSS_Sys_SetMotionIirCurveRatio4(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_4);
    VPSS_Sys_SetMotionIirCurveRatio3(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_3);
    VPSS_Sys_SetMotionIirCurveRatio2(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_2);
    VPSS_Sys_SetMotionIirCurveRatio1(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_1);
    VPSS_Sys_SetHisMotionInfoWriteMode(pstVpssRegs,  u32AddrOffset,  his_motion_info_write_mode);
    VPSS_Sys_SetHisMotionWriteMode(pstVpssRegs,  u32AddrOffset,  his_motion_write_mode);
    VPSS_Sys_SetHisMotionUsingMode(pstVpssRegs,  u32AddrOffset,  his_motion_using_mode);
    VPSS_Sys_SetHisMotionEn(pstVpssRegs,  u32AddrOffset,  his_motion_en);
    VPSS_Sys_SetPreInfoEn(pstVpssRegs,  u32AddrOffset,  pre_info_en);
    VPSS_Sys_SetPpreInfoEn(pstVpssRegs,  u32AddrOffset,  ppre_info_en);
    VPSS_Sys_SetRecModeFrmMotionStep1(pstVpssRegs,  u32AddrOffset,  rec_mode_frm_motion_step_1);
    VPSS_Sys_SetRecModeFrmMotionStep0(pstVpssRegs,  u32AddrOffset,  rec_mode_frm_motion_step_0);
    VPSS_Sys_SetRecModeFldMotionStep1(pstVpssRegs,  u32AddrOffset,  rec_mode_fld_motion_step_1);
    VPSS_Sys_SetRecModeFldMotionStep0(pstVpssRegs,  u32AddrOffset,  rec_mode_fld_motion_step_0);
    VPSS_Sys_SetMedBlendEn(pstVpssRegs,  u32AddrOffset,  med_blend_en);
    VPSS_Sys_SetMorFltEn(pstVpssRegs,  u32AddrOffset,  mor_flt_en);
    VPSS_Sys_SetMorFltSize(pstVpssRegs,  u32AddrOffset,  mor_flt_size);
    VPSS_Sys_SetMorFltThd(pstVpssRegs,  u32AddrOffset,  mor_flt_thd);
    VPSS_Sys_SetCombChkUpperLimit(pstVpssRegs,  u32AddrOffset,  comb_chk_upper_limit);
    VPSS_Sys_SetCombChkLowerLimit(pstVpssRegs,  u32AddrOffset,  comb_chk_lower_limit);
    VPSS_Sys_SetCombChkMinVthd(pstVpssRegs,  u32AddrOffset,  comb_chk_min_vthd);
    VPSS_Sys_SetCombChkMinHthd(pstVpssRegs,  u32AddrOffset,  comb_chk_min_hthd);
    VPSS_Sys_SetCombChkEn(pstVpssRegs,  u32AddrOffset,  comb_chk_en);
    VPSS_Sys_SetCombChkMdThd(pstVpssRegs,  u32AddrOffset,  comb_chk_md_thd);
    VPSS_Sys_SetCombChkEdgeThd(pstVpssRegs,  u32AddrOffset,  comb_chk_edge_thd);
    VPSS_Sys_SetFrameMotionSmoothThd3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd3);
    VPSS_Sys_SetFrameMotionSmoothThd2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd2);
    VPSS_Sys_SetFrameMotionSmoothThd1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd1);
    VPSS_Sys_SetFrameMotionSmoothThd0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd0);
    VPSS_Sys_SetFrameMotionSmoothRatioMax(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio_max);
    VPSS_Sys_SetFrameMotionSmoothRatioMin(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio_min);
    VPSS_Sys_SetFrameMotionSmoothThd5(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd5);
    VPSS_Sys_SetFrameMotionSmoothThd4(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd4);
    VPSS_Sys_SetFrameMotionSmoothRatio0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio0);
    VPSS_Sys_SetFrameMotionSmoothSlope3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope3);
    VPSS_Sys_SetFrameMotionSmoothSlope2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope2);
    VPSS_Sys_SetFrameMotionSmoothSlope1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope1);
    VPSS_Sys_SetFrameMotionSmoothSlope0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope0);
    VPSS_Sys_SetFrameMotionSmoothRatio4(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio4);
    VPSS_Sys_SetFrameMotionSmoothRatio3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio3);
    VPSS_Sys_SetFrameMotionSmoothRatio2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio2);
    VPSS_Sys_SetFrameMotionSmoothRatio1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio1);
    VPSS_Sys_SetFrameFieldBlendThd3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd3);
    VPSS_Sys_SetFrameFieldBlendThd2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd2);
    VPSS_Sys_SetFrameFieldBlendThd1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd1);
    VPSS_Sys_SetFrameFieldBlendThd0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd0);
    VPSS_Sys_SetFrameFieldBlendRatioMax(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio_max);
    VPSS_Sys_SetFrameFieldBlendRatioMin(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio_min);
    VPSS_Sys_SetFrameFieldBlendThd5(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd5);
    VPSS_Sys_SetFrameFieldBlendThd4(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd4);
    VPSS_Sys_SetFrameFieldBlendRatio0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio0);
    VPSS_Sys_SetFrameFieldBlendSlope3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope3);
    VPSS_Sys_SetFrameFieldBlendSlope2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope2);
    VPSS_Sys_SetFrameFieldBlendSlope1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope1);
    VPSS_Sys_SetFrameFieldBlendSlope0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope0);
    VPSS_Sys_SetFrameFieldBlendRatio4(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio4);
    VPSS_Sys_SetFrameFieldBlendRatio3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio3);
    VPSS_Sys_SetFrameFieldBlendRatio2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio2);
    VPSS_Sys_SetFrameFieldBlendRatio1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio1);
    VPSS_Sys_SetMotionAdjustGainChr(pstVpssRegs,  u32AddrOffset,  motion_adjust_gain_chr);
    VPSS_Sys_SetMotionAdjustCoring(pstVpssRegs,  u32AddrOffset,  motion_adjust_coring);
    VPSS_Sys_SetMotionAdjustGain(pstVpssRegs,  u32AddrOffset,  motion_adjust_gain);
    VPSS_Sys_SetEdgeNorm1(pstVpssRegs,  u32AddrOffset,  edge_norm_1);
    VPSS_Sys_SetEdgeNorm0(pstVpssRegs,  u32AddrOffset,  edge_norm_0);
    VPSS_Sys_SetEdgeNorm3(pstVpssRegs,  u32AddrOffset,  edge_norm_3);
    VPSS_Sys_SetEdgeNorm2(pstVpssRegs,  u32AddrOffset,  edge_norm_2);
    VPSS_Sys_SetMcStrengthK3(pstVpssRegs,  u32AddrOffset,  mc_strength_k3);
    VPSS_Sys_SetEdgeNorm5(pstVpssRegs,  u32AddrOffset,  edge_norm_5);
    VPSS_Sys_SetEdgeNorm4(pstVpssRegs,  u32AddrOffset,  edge_norm_4);
    VPSS_Sys_SetMcStrengthG3(pstVpssRegs,  u32AddrOffset,  mc_strength_g3);
    VPSS_Sys_SetEdgeNorm7(pstVpssRegs,  u32AddrOffset,  edge_norm_7);
    VPSS_Sys_SetEdgeNorm6(pstVpssRegs,  u32AddrOffset,  edge_norm_6);
    VPSS_Sys_SetInterDiffThd0(pstVpssRegs,  u32AddrOffset,  inter_diff_thd0);
    VPSS_Sys_SetEdgeNorm9(pstVpssRegs,  u32AddrOffset,  edge_norm_9);
    VPSS_Sys_SetEdgeNorm8(pstVpssRegs,  u32AddrOffset,  edge_norm_8);
    VPSS_Sys_SetInterDiffThd1(pstVpssRegs,  u32AddrOffset,  inter_diff_thd1);
    VPSS_Sys_SetEdgeNorm11(pstVpssRegs,  u32AddrOffset,  edge_norm_11);
    VPSS_Sys_SetEdgeNorm10(pstVpssRegs,  u32AddrOffset,  edge_norm_10);
    VPSS_Sys_SetInterDiffThd2(pstVpssRegs,  u32AddrOffset,  inter_diff_thd2);
    VPSS_Sys_SetEdgeScale(pstVpssRegs,  u32AddrOffset,  edge_scale);
    VPSS_Sys_SetEdgeCoring(pstVpssRegs,  u32AddrOffset,  edge_coring);
    VPSS_Sys_SetMcStrengthG0(pstVpssRegs,  u32AddrOffset,  mc_strength_g0);
    VPSS_Sys_SetMcStrengthK2(pstVpssRegs,  u32AddrOffset,  mc_strength_k2);
    VPSS_Sys_SetMcStrengthK1(pstVpssRegs,  u32AddrOffset,  mc_strength_k1);
    VPSS_Sys_SetMcStrengthK0(pstVpssRegs,  u32AddrOffset,  mc_strength_k0);
    VPSS_Sys_SetMcStrengthMaxg(pstVpssRegs,  u32AddrOffset,  mc_strength_maxg);
    VPSS_Sys_SetMcStrengthMing(pstVpssRegs,  u32AddrOffset,  mc_strength_ming);
    VPSS_Sys_SetMcStrengthG2(pstVpssRegs,  u32AddrOffset,  mc_strength_g2);
    VPSS_Sys_SetMcStrengthG1(pstVpssRegs,  u32AddrOffset,  mc_strength_g1);
    VPSS_Sys_SetKCMcbld(pstVpssRegs,  u32AddrOffset,  k_c_mcbld);
    VPSS_Sys_SetKCMcw(pstVpssRegs,  u32AddrOffset,  k_c_mcw);
    VPSS_Sys_SetKYMcbld(pstVpssRegs,  u32AddrOffset,  k_y_mcbld);
    VPSS_Sys_SetKYMcw(pstVpssRegs,  u32AddrOffset,  k_y_mcw);
    VPSS_Sys_SetG0McwAdj(pstVpssRegs,  u32AddrOffset,  g0_mcw_adj);
    VPSS_Sys_SetK0McwAdj(pstVpssRegs,  u32AddrOffset,  k0_mcw_adj);
    VPSS_Sys_SetX0McwAdj(pstVpssRegs,  u32AddrOffset,  x0_mcw_adj);
    VPSS_Sys_SetK1Mcbld(pstVpssRegs,  u32AddrOffset,  k1_mcbld);
    VPSS_Sys_SetK0Mcbld(pstVpssRegs,  u32AddrOffset,  k0_mcbld);
    VPSS_Sys_SetX0Mcbld(pstVpssRegs,  u32AddrOffset,  x0_mcbld);
    VPSS_Sys_SetK1McwAdj(pstVpssRegs,  u32AddrOffset,  k1_mcw_adj);
    VPSS_Sys_SetMcLaiBldmode(pstVpssRegs,  u32AddrOffset,  mc_lai_bldmode);
    VPSS_Sys_SetKCurwMcbld(pstVpssRegs,  u32AddrOffset,  k_curw_mcbld);
    VPSS_Sys_SetG0Mcbld(pstVpssRegs,  u32AddrOffset,  g0_mcbld);
    VPSS_Sys_SetMaGbmThd0(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd0);
    VPSS_Sys_SetMaGbmThd1(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd1);
    VPSS_Sys_SetMaGbmThd2(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd2);
    VPSS_Sys_SetMaGbmThd3(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd3);
    VPSS_Sys_SetMtfiltenGmd(pstVpssRegs,  u32AddrOffset,  mtfilten_gmd);
    VPSS_Sys_SetMtth3Gmd(pstVpssRegs,  u32AddrOffset,  mtth3_gmd);
    VPSS_Sys_SetMtth2Gmd(pstVpssRegs,  u32AddrOffset,  mtth2_gmd);
    VPSS_Sys_SetMtth1Gmd(pstVpssRegs,  u32AddrOffset,  mtth1_gmd);
    VPSS_Sys_SetMtth0Gmd(pstVpssRegs,  u32AddrOffset,  mtth0_gmd);
    VPSS_Sys_SetKMagGmd(pstVpssRegs,  u32AddrOffset,  k_mag_gmd);
    VPSS_Sys_SetKDifhGmd(pstVpssRegs,  u32AddrOffset,  k_difh_gmd);
    VPSS_Sys_SetKMaxmagGmd(pstVpssRegs,  u32AddrOffset,  k_maxmag_gmd);
    VPSS_Sys_SetKhoredge(pstVpssRegs,  u32AddrOffset,  khoredge);
    VPSS_Sys_SetKmagv2(pstVpssRegs,  u32AddrOffset,  kmagv_2);
    VPSS_Sys_SetKmagv1(pstVpssRegs,  u32AddrOffset,  kmagv_1);
    VPSS_Sys_SetKmagh2(pstVpssRegs,  u32AddrOffset,  kmagh_2);
    VPSS_Sys_SetKmagh1(pstVpssRegs,  u32AddrOffset,  kmagh_1);
    VPSS_Sys_SetScalerFramemotion(pstVpssRegs,  u32AddrOffset,  scaler_framemotion);
    VPSS_Sys_SetMotionLimt2(pstVpssRegs,  u32AddrOffset,  motion_limt_2);
    VPSS_Sys_SetMotionLimt1(pstVpssRegs,  u32AddrOffset,  motion_limt_1);
    VPSS_Sys_SetFrameMagEn(pstVpssRegs,  u32AddrOffset,  frame_mag_en);
    VPSS_Sys_SetScalerHoredge(pstVpssRegs,  u32AddrOffset,  scaler_horedge);
    VPSS_Sys_SetEdgeStrCoringC(pstVpssRegs,  u32AddrOffset,  edge_str_coring_c);
    VPSS_Sys_SetDirRatioC(pstVpssRegs,  u32AddrOffset,  dir_ratio_c);
    VPSS_Sys_SetHistThd3(pstVpssRegs,  u32AddrOffset,  hist_thd3);
    VPSS_Sys_SetHistThd2(pstVpssRegs,  u32AddrOffset,  hist_thd2);
    VPSS_Sys_SetHistThd1(pstVpssRegs,  u32AddrOffset,  hist_thd1);
    VPSS_Sys_SetHistThd0(pstVpssRegs,  u32AddrOffset,  hist_thd0);
    VPSS_Sys_SetMovCoringNorm(pstVpssRegs,  u32AddrOffset,  mov_coring_norm);
    VPSS_Sys_SetMovCoringTkr(pstVpssRegs,  u32AddrOffset,  mov_coring_tkr);
    VPSS_Sys_SetMovCoringBlk(pstVpssRegs,  u32AddrOffset,  mov_coring_blk);
    VPSS_Sys_SetLasiMode(pstVpssRegs,  u32AddrOffset,  lasi_mode);
    VPSS_Sys_SetBitsmov2r(pstVpssRegs,  u32AddrOffset,  bitsmov2r);
    VPSS_Sys_SetDiffMovblkThd(pstVpssRegs,  u32AddrOffset,  diff_movblk_thd);
    VPSS_Sys_SetUmThd2(pstVpssRegs,  u32AddrOffset,  um_thd2);
    VPSS_Sys_SetUmThd1(pstVpssRegs,  u32AddrOffset,  um_thd1);
    VPSS_Sys_SetUmThd0(pstVpssRegs,  u32AddrOffset,  um_thd0);
    VPSS_Sys_SetCoringBlk(pstVpssRegs,  u32AddrOffset,  coring_blk);
    VPSS_Sys_SetCoringNorm(pstVpssRegs,  u32AddrOffset,  coring_norm);
    VPSS_Sys_SetCoringTkr(pstVpssRegs,  u32AddrOffset,  coring_tkr);
    VPSS_Sys_SetPccHthd(pstVpssRegs,  u32AddrOffset,  pcc_hthd);
    VPSS_Sys_SetPccVthd3(pstVpssRegs,  u32AddrOffset,  pcc_vthd3);
    VPSS_Sys_SetPccVthd2(pstVpssRegs,  u32AddrOffset,  pcc_vthd2);
    VPSS_Sys_SetPccVthd1(pstVpssRegs,  u32AddrOffset,  pcc_vthd1);
    VPSS_Sys_SetPccVthd0(pstVpssRegs,  u32AddrOffset,  pcc_vthd0);
    VPSS_Sys_SetItdiffVthd3(pstVpssRegs,  u32AddrOffset,  itdiff_vthd3);
    VPSS_Sys_SetItdiffVthd2(pstVpssRegs,  u32AddrOffset,  itdiff_vthd2);
    VPSS_Sys_SetItdiffVthd1(pstVpssRegs,  u32AddrOffset,  itdiff_vthd1);
    VPSS_Sys_SetItdiffVthd0(pstVpssRegs,  u32AddrOffset,  itdiff_vthd0);
    VPSS_Sys_SetLasiMovThd(pstVpssRegs,  u32AddrOffset,  lasi_mov_thd);
    VPSS_Sys_SetLasiEdgeThd(pstVpssRegs,  u32AddrOffset,  lasi_edge_thd);
    VPSS_Sys_SetLasiCoringThd(pstVpssRegs,  u32AddrOffset,  lasi_coring_thd);
    VPSS_Sys_SetLasiTxtCoring(pstVpssRegs,  u32AddrOffset,  lasi_txt_coring);
    VPSS_Sys_SetLasiTxtAlpha(pstVpssRegs,  u32AddrOffset,  lasi_txt_alpha);
    VPSS_Sys_SetLasiTxtThd3(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd3);
    VPSS_Sys_SetLasiTxtThd2(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd2);
    VPSS_Sys_SetLasiTxtThd1(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd1);
    VPSS_Sys_SetLasiTxtThd0(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd0);
    VPSS_Sys_SetRegion1YStt(pstVpssRegs,  u32AddrOffset,  region1_y_stt);
    VPSS_Sys_SetRegion1YEnd(pstVpssRegs,  u32AddrOffset,  region1_y_end);
    VPSS_Sys_SetKRgdifycore(pstVpssRegs,  u32AddrOffset,  k_rgdifycore);
    VPSS_Sys_SetGRgdifycore(pstVpssRegs,  u32AddrOffset,  g_rgdifycore);
    VPSS_Sys_SetCoreRgdify(pstVpssRegs,  u32AddrOffset,  core_rgdify);
    VPSS_Sys_SetLmtRgdify(pstVpssRegs,  u32AddrOffset,  lmt_rgdify);
    VPSS_Sys_SetCoefSadlpf(pstVpssRegs,  u32AddrOffset,  coef_sadlpf);
    VPSS_Sys_SetKmvRgsad(pstVpssRegs,  u32AddrOffset,  kmv_rgsad);
    VPSS_Sys_SetKTpdifRgsad(pstVpssRegs,  u32AddrOffset,  k_tpdif_rgsad);
    VPSS_Sys_SetGTpdifRgsad(pstVpssRegs,  u32AddrOffset,  g_tpdif_rgsad);
    VPSS_Sys_SetThmagRgmv(pstVpssRegs,  u32AddrOffset,  thmag_rgmv);
    VPSS_Sys_SetThSaddifRgmv(pstVpssRegs,  u32AddrOffset,  th_saddif_rgmv);
    VPSS_Sys_SetTh0mvsadRgmv(pstVpssRegs,  u32AddrOffset,  th_0mvsad_rgmv);
    VPSS_Sys_SetCoreMagRg(pstVpssRegs,  u32AddrOffset,  core_mag_rg);
    VPSS_Sys_SetLmtMagRg(pstVpssRegs,  u32AddrOffset,  lmt_mag_rg);
    VPSS_Sys_SetCoreMvRgmvls(pstVpssRegs,  u32AddrOffset,  core_mv_rgmvls);
    VPSS_Sys_SetKMvRgmvls(pstVpssRegs,  u32AddrOffset,  k_mv_rgmvls);
    VPSS_Sys_SetCoreMagRgmvls(pstVpssRegs,  u32AddrOffset,  core_mag_rgmvls);
    VPSS_Sys_SetKMagRgmvls(pstVpssRegs,  u32AddrOffset,  k_mag_rgmvls);
    VPSS_Sys_SetThMvadjRgmvls(pstVpssRegs,  u32AddrOffset,  th_mvadj_rgmvls);
    VPSS_Sys_SetEnMvadjRgmvls(pstVpssRegs,  u32AddrOffset,  en_mvadj_rgmvls);
    VPSS_Sys_SetKSadRgls(pstVpssRegs,  u32AddrOffset,  k_sad_rgls);
    VPSS_Sys_SetThMagRgls(pstVpssRegs,  u32AddrOffset,  th_mag_rgls);
    VPSS_Sys_SetThSadRgls(pstVpssRegs,  u32AddrOffset,  th_sad_rgls);
    VPSS_Sys_SetKSadcoreRgmv(pstVpssRegs,  u32AddrOffset,  k_sadcore_rgmv);
    VPSS_Sys_SetForceMven(pstVpssRegs,  u32AddrOffset,  force_mven);
    VPSS_Sys_SetForceMvx(pstVpssRegs,  u32AddrOffset,  force_mvx);
    VPSS_Sys_SetThBlkmvxMvdlt(pstVpssRegs,  u32AddrOffset,  th_blkmvx_mvdlt);
    VPSS_Sys_SetThRgmvxMvdlt(pstVpssRegs,  u32AddrOffset,  th_rgmvx_mvdlt);
    VPSS_Sys_SetThLsMvdlt(pstVpssRegs,  u32AddrOffset,  th_ls_mvdlt);
    VPSS_Sys_SetThVblkdistMvdlt(pstVpssRegs,  u32AddrOffset,  th_vblkdist_mvdlt);
    VPSS_Sys_SetThHblkdistMvdlt(pstVpssRegs,  u32AddrOffset,  th_hblkdist_mvdlt);
    VPSS_Sys_SetKSadcoreMvdlt(pstVpssRegs,  u32AddrOffset,  k_sadcore_mvdlt);
    VPSS_Sys_SetThMagMvdlt(pstVpssRegs,  u32AddrOffset,  th_mag_mvdlt);
    VPSS_Sys_SetGMagMvdlt(pstVpssRegs,  u32AddrOffset,  g_mag_mvdlt);
    VPSS_Sys_SetThlSadMvdlt(pstVpssRegs,  u32AddrOffset,  thl_sad_mvdlt);
    VPSS_Sys_SetThhSadMvdlt(pstVpssRegs,  u32AddrOffset,  thh_sad_mvdlt);
    VPSS_Sys_SetKRglsw(pstVpssRegs,  u32AddrOffset,  k_rglsw);
    VPSS_Sys_SetKSimimvw(pstVpssRegs,  u32AddrOffset,  k_simimvw);
    VPSS_Sys_SetGhCoreSimimv(pstVpssRegs,  u32AddrOffset,  gh_core_simimv);
    VPSS_Sys_SetGlCoreSimimv(pstVpssRegs,  u32AddrOffset,  gl_core_simimv);
    VPSS_Sys_SetKCoreSimimv(pstVpssRegs,  u32AddrOffset,  k_core_simimv);
    VPSS_Sys_SetKCoreVsaddif(pstVpssRegs,  u32AddrOffset,  k_core_vsaddif);
    VPSS_Sys_SetKRgsadadjMcw(pstVpssRegs,  u32AddrOffset,  k_rgsadadj_mcw);
    VPSS_Sys_SetCoreRgsadadjMcw(pstVpssRegs,  u32AddrOffset,  core_rgsadadj_mcw);
    VPSS_Sys_SetKMvyMcw(pstVpssRegs,  u32AddrOffset,  k_mvy_mcw);
    VPSS_Sys_SetCoreMvyMcw(pstVpssRegs,  u32AddrOffset,  core_mvy_mcw);
    VPSS_Sys_SetRgtbEnMcw(pstVpssRegs,  u32AddrOffset,  rgtb_en_mcw);
    VPSS_Sys_SetCoreRgmagMcw(pstVpssRegs,  u32AddrOffset,  core_rgmag_mcw);
    VPSS_Sys_SetModeRgysadMcw(pstVpssRegs,  u32AddrOffset,  mode_rgysad_mcw);
    VPSS_Sys_SetKVsaddifw(pstVpssRegs,  u32AddrOffset,  k_vsaddifw);
    VPSS_Sys_SetGhCoreVsadDif(pstVpssRegs,  u32AddrOffset,  gh_core_vsad_dif);
    VPSS_Sys_SetGlCoreVsaddif(pstVpssRegs,  u32AddrOffset,  gl_core_vsaddif);
    VPSS_Sys_SetG0RgmagMcw(pstVpssRegs,  u32AddrOffset,  g0_rgmag_mcw);
    VPSS_Sys_SetK0RgmagMcw(pstVpssRegs,  u32AddrOffset,  k0_rgmag_mcw);
    VPSS_Sys_SetX0RgmagMcw(pstVpssRegs,  u32AddrOffset,  x0_rgmag_mcw);
    VPSS_Sys_SetX0RgsadMcw(pstVpssRegs,  u32AddrOffset,  x0_rgsad_mcw);
    VPSS_Sys_SetCoreRgsadMcw(pstVpssRegs,  u32AddrOffset,  core_rgsad_mcw);
    VPSS_Sys_SetK1RgmagMcw(pstVpssRegs,  u32AddrOffset,  k1_rgmag_mcw);
    VPSS_Sys_SetK1RgsadMcw(pstVpssRegs,  u32AddrOffset,  k1_rgsad_mcw);
    VPSS_Sys_SetG0RgsadMcw(pstVpssRegs,  u32AddrOffset,  g0_rgsad_mcw);
    VPSS_Sys_SetK0RgsadMcw(pstVpssRegs,  u32AddrOffset,  k0_rgsad_mcw);
    VPSS_Sys_SetKRgsadMcw(pstVpssRegs,  u32AddrOffset,  k_rgsad_mcw);
    VPSS_Sys_SetXRgsadMcw(pstVpssRegs,  u32AddrOffset,  x_rgsad_mcw);
    VPSS_Sys_SetK0SmrgMcw(pstVpssRegs,  u32AddrOffset,  k0_smrg_mcw);
    VPSS_Sys_SetX0SmrgMcw(pstVpssRegs,  u32AddrOffset,  x0_smrg_mcw);
    VPSS_Sys_SetK1TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k1_tpmvdist_mcw);
    VPSS_Sys_SetG0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  g0_tpmvdist_mcw);
    VPSS_Sys_SetK0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k0_tpmvdist_mcw);
    VPSS_Sys_SetX0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  x0_tpmvdist_mcw);
    VPSS_Sys_SetKCoreTpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_core_tpmvdist_mcw);
    VPSS_Sys_SetBCoreTpmvdistMcw(pstVpssRegs,  u32AddrOffset,  b_core_tpmvdist_mcw);
    VPSS_Sys_SetKAvgmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_avgmvdist_mcw);
    VPSS_Sys_SetKMinmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_minmvdist_mcw);
    VPSS_Sys_SetKTbdifMcw(pstVpssRegs,  u32AddrOffset,  k_tbdif_mcw);
    VPSS_Sys_SetK0MaxMagMcw(pstVpssRegs,  u32AddrOffset,  k0_max_mag_mcw);
    VPSS_Sys_SetK1MaxMagMcw(pstVpssRegs,  u32AddrOffset,  k1_max_mag_mcw);
    VPSS_Sys_SetKMaxDifMcw(pstVpssRegs,  u32AddrOffset,  k_max_dif_mcw);
    VPSS_Sys_SetKMaxCoreMcw(pstVpssRegs,  u32AddrOffset,  k_max_core_mcw);
    VPSS_Sys_SetKDifvcoreMcw(pstVpssRegs,  u32AddrOffset,  k_difvcore_mcw);
    VPSS_Sys_SetKDifhcoreMcw(pstVpssRegs,  u32AddrOffset,  k_difhcore_mcw);
    VPSS_Sys_SetK1MagWndMcw(pstVpssRegs,  u32AddrOffset,  k1_mag_wnd_mcw);
    VPSS_Sys_SetG0MagWndMcw(pstVpssRegs,  u32AddrOffset,  g0_mag_wnd_mcw);
    VPSS_Sys_SetK0MagWndMcw(pstVpssRegs,  u32AddrOffset,  k0_mag_wnd_mcw);
    VPSS_Sys_SetX0MagWndMcw(pstVpssRegs,  u32AddrOffset,  x0_mag_wnd_mcw);
    VPSS_Sys_SetKTbmagMcw(pstVpssRegs,  u32AddrOffset,  k_tbmag_mcw);
    VPSS_Sys_SetG0SadWndMcw(pstVpssRegs,  u32AddrOffset,  g0_sad_wnd_mcw);
    VPSS_Sys_SetK0SadWndMcw(pstVpssRegs,  u32AddrOffset,  k0_sad_wnd_mcw);
    VPSS_Sys_SetX0SadWndMcw(pstVpssRegs,  u32AddrOffset,  x0_sad_wnd_mcw);
    VPSS_Sys_SetG1MagWndMcw(pstVpssRegs,  u32AddrOffset,  g1_mag_wnd_mcw);
    VPSS_Sys_SetG1SadWndMcw(pstVpssRegs,  u32AddrOffset,  g1_sad_wnd_mcw);
    VPSS_Sys_SetK1SadWndMcw(pstVpssRegs,  u32AddrOffset,  k1_sad_wnd_mcw);
    VPSS_Sys_SetBHvdifDw(pstVpssRegs,  u32AddrOffset,  b_hvdif_dw);
    VPSS_Sys_SetBBhvdifDw(pstVpssRegs,  u32AddrOffset,  b_bhvdif_dw);
    VPSS_Sys_SetKBhvdifDw(pstVpssRegs,  u32AddrOffset,  k_bhvdif_dw);
    VPSS_Sys_SetCoreBhvdifDw(pstVpssRegs,  u32AddrOffset,  core_bhvdif_dw);
    VPSS_Sys_SetGainLpfDw(pstVpssRegs,  u32AddrOffset,  gain_lpf_dw);
    VPSS_Sys_SetKMaxHvdifDw(pstVpssRegs,  u32AddrOffset,  k_max_hvdif_dw);
    VPSS_Sys_SetBMvDw(pstVpssRegs,  u32AddrOffset,  b_mv_dw);
    VPSS_Sys_SetCoreMvDw(pstVpssRegs,  u32AddrOffset,  core_mv_dw);
    VPSS_Sys_SetKDifvDw(pstVpssRegs,  u32AddrOffset,  k_difv_dw);
    VPSS_Sys_SetCoreHvdifDw(pstVpssRegs,  u32AddrOffset,  core_hvdif_dw);
    VPSS_Sys_SetK1HvdifDw(pstVpssRegs,  u32AddrOffset,  k1_hvdif_dw);
    VPSS_Sys_SetG0HvdifDw(pstVpssRegs,  u32AddrOffset,  g0_hvdif_dw);
    VPSS_Sys_SetK0HvdifDw(pstVpssRegs,  u32AddrOffset,  k0_hvdif_dw);
    VPSS_Sys_SetX0HvdifDw(pstVpssRegs,  u32AddrOffset,  x0_hvdif_dw);
    VPSS_Sys_SetK1MvDw(pstVpssRegs,  u32AddrOffset,  k1_mv_dw);
    VPSS_Sys_SetG0MvDw(pstVpssRegs,  u32AddrOffset,  g0_mv_dw);
    VPSS_Sys_SetK0MvDw(pstVpssRegs,  u32AddrOffset,  k0_mv_dw);
    VPSS_Sys_SetX0MvDw(pstVpssRegs,  u32AddrOffset,  x0_mv_dw);
    VPSS_Sys_SetK1MtDw(pstVpssRegs,  u32AddrOffset,  k1_mt_dw);
    VPSS_Sys_SetG0MtDw(pstVpssRegs,  u32AddrOffset,  g0_mt_dw);
    VPSS_Sys_SetK0MtDw(pstVpssRegs,  u32AddrOffset,  k0_mt_dw);
    VPSS_Sys_SetX0MtDw(pstVpssRegs,  u32AddrOffset,  x0_mt_dw);
    VPSS_Sys_SetBMtDw(pstVpssRegs,  u32AddrOffset,  b_mt_dw);
    VPSS_Sys_SetK1MvMt(pstVpssRegs,  u32AddrOffset,  k1_mv_mt);
    VPSS_Sys_SetX0MvMt(pstVpssRegs,  u32AddrOffset,  x0_mv_mt);
    VPSS_Sys_SetG0MvMt(pstVpssRegs,  u32AddrOffset,  g0_mv_mt);
    VPSS_Sys_SetMclpfMode(pstVpssRegs,  u32AddrOffset,  mclpf_mode);
    VPSS_Sys_SetKPxlmagMcw(pstVpssRegs,  u32AddrOffset,  k_pxlmag_mcw);
    VPSS_Sys_SetXPxlmagMcw(pstVpssRegs,  u32AddrOffset,  x_pxlmag_mcw);
    VPSS_Sys_SetRsPxlmagMcw(pstVpssRegs,  u32AddrOffset,  rs_pxlmag_mcw);
    VPSS_Sys_SetGainMclpfh(pstVpssRegs,  u32AddrOffset,  gain_mclpfh);
    VPSS_Sys_SetGainDnMclpfv(pstVpssRegs,  u32AddrOffset,  gain_dn_mclpfv);
    VPSS_Sys_SetGainUpMclpfv(pstVpssRegs,  u32AddrOffset,  gain_up_mclpfv);
    VPSS_Sys_SetGPxlmagMcw(pstVpssRegs,  u32AddrOffset,  g_pxlmag_mcw);
    VPSS_Sys_SetKCVertw(pstVpssRegs,  u32AddrOffset,  k_c_vertw);
    VPSS_Sys_SetKYVertw(pstVpssRegs,  u32AddrOffset,  k_y_vertw);
    VPSS_Sys_SetKFstmtMc(pstVpssRegs,  u32AddrOffset,  k_fstmt_mc);
    VPSS_Sys_SetXFstmtMc(pstVpssRegs,  u32AddrOffset,  x_fstmt_mc);
    VPSS_Sys_SetK1MvMc(pstVpssRegs,  u32AddrOffset,  k1_mv_mc);
    VPSS_Sys_SetX0MvMc(pstVpssRegs,  u32AddrOffset,  x0_mv_mc);
    VPSS_Sys_SetBdvMcpos(pstVpssRegs,  u32AddrOffset,  bdv_mcpos);
    VPSS_Sys_SetBdhMcpos(pstVpssRegs,  u32AddrOffset,  bdh_mcpos);
    VPSS_Sys_SetKDelta(pstVpssRegs,  u32AddrOffset,  k_delta);
    VPSS_Sys_SetKHfcoreMc(pstVpssRegs,  u32AddrOffset,  k_hfcore_mc);
    VPSS_Sys_SetXHfcoreMc(pstVpssRegs,  u32AddrOffset,  x_hfcore_mc);
    VPSS_Sys_SetGSlmtMc(pstVpssRegs,  u32AddrOffset,  g_slmt_mc);
    VPSS_Sys_SetKSlmtMc(pstVpssRegs,  u32AddrOffset,  k_slmt_mc);
    VPSS_Sys_SetXSlmtMc(pstVpssRegs,  u32AddrOffset,  x_slmt_mc);
    VPSS_Sys_SetGFstmtMc(pstVpssRegs,  u32AddrOffset,  g_fstmt_mc);
    VPSS_Sys_SetR0Mc(pstVpssRegs,  u32AddrOffset,  r0_mc);
    VPSS_Sys_SetC0Mc(pstVpssRegs,  u32AddrOffset,  c0_mc);
    VPSS_Sys_SetGHfcoreMc(pstVpssRegs,  u32AddrOffset,  g_hfcore_mc);
    VPSS_Sys_SetMcmvrange(pstVpssRegs,  u32AddrOffset,  mcmvrange);
    VPSS_Sys_SetR1Mc(pstVpssRegs,  u32AddrOffset,  r1_mc);
    VPSS_Sys_SetC1Mc(pstVpssRegs,  u32AddrOffset,  c1_mc);
    VPSS_Sys_SetKFrcountMc(pstVpssRegs,  u32AddrOffset,  k_frcount_mc);
    VPSS_Sys_SetXFrcountMc(pstVpssRegs,  u32AddrOffset,  x_frcount_mc);
    VPSS_Sys_SetScenechangeMc(pstVpssRegs,  u32AddrOffset,  scenechange_mc);
    VPSS_Sys_SetMcendc(pstVpssRegs,  u32AddrOffset,  mcendc);
    VPSS_Sys_SetMcendr(pstVpssRegs,  u32AddrOffset,  mcendr);
    VPSS_Sys_SetMcstartc(pstVpssRegs,  u32AddrOffset,  mcstartc);
    VPSS_Sys_SetMcstartr(pstVpssRegs,  u32AddrOffset,  mcstartr);
    VPSS_Sys_SetMovegain(pstVpssRegs,  u32AddrOffset,  movegain);
    VPSS_Sys_SetMovecorig(pstVpssRegs,  u32AddrOffset,  movecorig);
    VPSS_Sys_SetMovethdl(pstVpssRegs,  u32AddrOffset,  movethdl);
    VPSS_Sys_SetMovethdh(pstVpssRegs,  u32AddrOffset,  movethdh);
    VPSS_Sys_SetMcNumtBlden(pstVpssRegs,  u32AddrOffset,  mc_numt_blden);
    VPSS_Sys_SetNumtGain(pstVpssRegs,  u32AddrOffset,  numt_gain);
    VPSS_Sys_SetNumtCoring(pstVpssRegs,  u32AddrOffset,  numt_coring);
    VPSS_Sys_SetNumtLpfEn(pstVpssRegs,  u32AddrOffset,  numt_lpf_en);
    VPSS_Sys_SetK1Hw(pstVpssRegs,  u32AddrOffset,  k1_hw);
    VPSS_Sys_SetK0Hw(pstVpssRegs,  u32AddrOffset,  k0_hw);
    VPSS_Sys_SetCoreHfvline(pstVpssRegs,  u32AddrOffset,  core_hfvline);
    VPSS_Sys_SetK1Hfvline(pstVpssRegs,  u32AddrOffset,  k1_hfvline);
    VPSS_Sys_SetK0Hfvline(pstVpssRegs,  u32AddrOffset,  k0_hfvline);
    VPSS_Sys_SetCoreRglsw(pstVpssRegs,  u32AddrOffset,  core_rglsw);
    VPSS_Sys_SetGDifcoreMcw(pstVpssRegs,  u32AddrOffset,  g_difcore_mcw);
    VPSS_Sys_SetSubpixMcEn(pstVpssRegs,  u32AddrOffset,  subpix_mc_en);
    VPSS_Sys_SetCore1Hw(pstVpssRegs,  u32AddrOffset,  core1_hw);
    VPSS_Sys_SetKCore0Hw(pstVpssRegs,  u32AddrOffset,  k_core0_hw);
    VPSS_Sys_SetBCore0Hw(pstVpssRegs,  u32AddrOffset,  b_core0_hw);
    VPSS_Sys_SetGHw(pstVpssRegs,  u32AddrOffset,  g_hw);
    VPSS_Sys_SetG0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  g0_sadr_wnd_mcw);
    VPSS_Sys_SetK0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  k0_sadr_wnd_mcw);
    VPSS_Sys_SetX0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  x0_sadr_wnd_mcw);
    VPSS_Sys_SetRpK1SadWndMcw(pstVpssRegs,  u32AddrOffset,  rp_k1_sad_wnd_mcw);
    VPSS_Sys_SetRpK1MagWndMcw(pstVpssRegs,  u32AddrOffset,  rp_k1_mag_wnd_mcw);
    VPSS_Sys_SetThCurBlksad(pstVpssRegs,  u32AddrOffset,  th_cur_blksad);
    VPSS_Sys_SetKMcdifvMcw(pstVpssRegs,  u32AddrOffset,  k_mcdifv_mcw);
    VPSS_Sys_SetKP1cfdifhMcw(pstVpssRegs,  u32AddrOffset,  k_p1cfdifh_mcw);
    VPSS_Sys_SetG1SadrWndMcw(pstVpssRegs,  u32AddrOffset,  g1_sadr_wnd_mcw);
    VPSS_Sys_SetK1SadrWndMcw(pstVpssRegs,  u32AddrOffset,  k1_sadr_wnd_mcw);
    VPSS_Sys_SetThCurBlkmotion(pstVpssRegs,  u32AddrOffset,  th_cur_blkmotion);
    VPSS_Sys_SetThlNeighBlksad(pstVpssRegs,  u32AddrOffset,  thl_neigh_blksad);
    VPSS_Sys_SetThhNeighBlksad(pstVpssRegs,  u32AddrOffset,  thh_neigh_blksad);
    VPSS_Sys_SetRpDifmvxthRgmv(pstVpssRegs,  u32AddrOffset,  rp_difmvxth_rgmv);
    VPSS_Sys_SetRpMvxthRgmv(pstVpssRegs,  u32AddrOffset,  rp_mvxth_rgmv);
    VPSS_Sys_SetRpcounterth(pstVpssRegs,  u32AddrOffset,  rpcounterth);
    VPSS_Sys_SetKRpcounter(pstVpssRegs,  u32AddrOffset,  k_rpcounter);
    VPSS_Sys_SetBlkmvUpdateEn(pstVpssRegs,  u32AddrOffset,  blkmv_update_en);
    VPSS_Sys_SetThRgmvMag(pstVpssRegs,  u32AddrOffset,  th_rgmv_mag);
    VPSS_Sys_SetRpMagthRgmv(pstVpssRegs,  u32AddrOffset,  rp_magth_rgmv);
    VPSS_Sys_SetRpSadthRgmv(pstVpssRegs,  u32AddrOffset,  rp_sadth_rgmv);
    VPSS_Sys_SetRpDifsadthRgmv(pstVpssRegs,  u32AddrOffset,  rp_difsadth_rgmv);
    VPSS_Sys_SetDifvtMode(pstVpssRegs,  u32AddrOffset,  difvt_mode);
    VPSS_Sys_SetRpEn(pstVpssRegs,  u32AddrOffset,  rp_en);
    VPSS_Sys_SetSubmvSadchkEn(pstVpssRegs,  u32AddrOffset,  submv_sadchk_en);
    VPSS_Sys_SetK1TpdifRgsad(pstVpssRegs,  u32AddrOffset,  k1_tpdif_rgsad);
    VPSS_Sys_SetRpDifsadthTb(pstVpssRegs,  u32AddrOffset,  rp_difsadth_tb);
    VPSS_Sys_SetRpDifmvxthSp(pstVpssRegs,  u32AddrOffset,  rp_difmvxth_sp);
    VPSS_Sys_SetCntlut5(pstVpssRegs,  u32AddrOffset,  cntlut_5);
    VPSS_Sys_SetCntlut4(pstVpssRegs,  u32AddrOffset,  cntlut_4);
    VPSS_Sys_SetCntlut3(pstVpssRegs,  u32AddrOffset,  cntlut_3);
    VPSS_Sys_SetCntlut2(pstVpssRegs,  u32AddrOffset,  cntlut_2);
    VPSS_Sys_SetCntlut1(pstVpssRegs,  u32AddrOffset,  cntlut_1);
    VPSS_Sys_SetCntlut0(pstVpssRegs,  u32AddrOffset,  cntlut_0);
    VPSS_Sys_SetMcwScntGain(pstVpssRegs,  u32AddrOffset,  mcw_scnt_gain);
    VPSS_Sys_SetMcwScntEn(pstVpssRegs,  u32AddrOffset,  mcw_scnt_en);
    VPSS_Sys_SetMcMtshift(pstVpssRegs,  u32AddrOffset,  mc_mtshift);
    VPSS_Sys_SetCntlut8(pstVpssRegs,  u32AddrOffset,  cntlut_8);
    VPSS_Sys_SetCntlut7(pstVpssRegs,  u32AddrOffset,  cntlut_7);
    VPSS_Sys_SetCntlut6(pstVpssRegs,  u32AddrOffset,  cntlut_6);
    VPSS_Sys_SetDemoBorder(pstVpssRegs,  u32AddrOffset,  demo_border);
    VPSS_Sys_SetDemoModeR(pstVpssRegs,  u32AddrOffset,  demo_mode_r);
    VPSS_Sys_SetDemoModeL(pstVpssRegs,  u32AddrOffset,  demo_mode_l);
    VPSS_Sys_SetDemoEn(pstVpssRegs,  u32AddrOffset,  demo_en);
}
#endif

#if 1
HI_VOID VPSS_FUNC_SetDeiMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_DEI_CFG_S *pstCfg)
{
    HI_U32 in_width  = pstCfg->width;
    HI_U32 in_height = pstCfg->height;
    HI_U32 pro = pstCfg->pro;

    int width = in_width;
    int height = (pro == 1) ? in_height : in_height / 2 ;
    //int mcdi_en = pstCfg->mcdi_en;

    HI_U32  edge_smooth_ratio   =   64  ;
    HI_U32  die_rst =   0   ;
    HI_U32  mchdir_c    =   0   ;
    HI_U32  mchdir_l    =   0   ;
    HI_U32  edge_smooth_en  =   0   ;
    HI_U32  ma_only =   0   ;
    HI_U32  mc_only =   0   ;
    HI_U32  two_four_pxl_share  =   0   ;
    HI_U32  die_c_mode  =   1   ;
    HI_U32  die_l_mode  =   1   ;
    HI_U32  die_out_sel_c   =   0   ;
    HI_U32  die_out_sel_l   =   0   ;
    HI_U32  frame_motion_smooth_en  =   1   ;
    HI_U32  luma_scesdf_max =   0   ;
    HI_U32  motion_iir_en   =   1   ;
    HI_U32  luma_mf_max =   0   ;
    HI_U32  chroma_mf_max   =   0   ;
    HI_U32  rec_mode_en =   1   ;
    HI_U32  dei_st_rst_value    =   0   ;
    HI_U32  chroma_mf_offset    =   8   ;
    HI_U32  rec_mode_set_pre_info_mode  =   0   ;
    HI_U32  rec_mode_output_mode    =   0   ;
    HI_U32  dir_ratio_north =   2   ;
    HI_U32  min_north_strength  =   0   ;
    HI_U32  range_scale =   8   ;
    HI_U32  bc1_max_dz  =   30  ;
    HI_U32  bc1_autodz_gain =   2   ;
    HI_U32  bc1_gain    =   4   ;
    HI_U32  bc2_max_dz  =   30  ;
    HI_U32  bc2_autodz_gain =   2   ;
    HI_U32  bc2_gain    =   4   ;
    HI_U32  dir0_scale  =   16  ;
    HI_U32  dir1_scale  =   16  ;
    HI_U32  dir2_scale  =   16  ;
    HI_U32  dir3_scale  =   16  ;
    HI_U32  dir4_scale  =   16  ;
    HI_U32  dir5_scale  =   16  ;
    HI_U32  dir6_scale  =   16  ;
    HI_U32  dir7_scale  =   16  ;
    HI_U32  dir8_scale  =   16  ;
    HI_U32  dir9_scale  =   16  ;
    HI_U32  dir10_scale =   16  ;
    HI_U32  dir11_scale =   16  ;
    HI_U32  dir12_scale =   0   ;
    HI_U32  dir13_scale =   0   ;
    HI_U32  dir14_scale =   0   ;
    HI_U32  intp_scale_ratio_1  =   6   ;
    HI_U32  intp_scale_ratio_2  =   5   ;
    HI_U32  intp_scale_ratio_3  =   5   ;
    HI_U32  intp_scale_ratio_4  =   6   ;
    HI_U32  intp_scale_ratio_5  =   6   ;
    HI_U32  intp_scale_ratio_6  =   7   ;
    HI_U32  intp_scale_ratio_7  =   8   ;
    HI_U32  intp_scale_ratio_8  =   8   ;
    HI_U32  intp_scale_ratio_9  =   8   ;
    HI_U32  intp_scale_ratio_10 =   8   ;
    HI_U32  intp_scale_ratio_11 =   8   ;
    HI_U32  intp_scale_ratio_12 =   8   ;
    HI_U32  intp_scale_ratio_13 =   8   ;
    HI_U32  intp_scale_ratio_14 =   8   ;
    HI_U32  intp_scale_ratio_15 =   8   ;
    HI_U32  dir_thd =   0   ;
    HI_U32  edge_mode   =   1   ;
    HI_U32  hor_edge_en =   0   ;
    HI_U32  jitter_gain =   8   ;
    HI_U32  jitter_coring   =   0   ;
    HI_U32  fld_motion_coring   =   0   ;
    HI_U32  fld_motion_thd_low  =   0   ;
    HI_U32  fld_motion_thd_high =   255 ;
    HI_S32  fld_motion_curve_slope  =   -2  ;
    HI_U32  fld_motion_gain =   8   ;
    HI_U32  fld_motion_wnd_mode =   1   ;
    HI_U32  long_motion_shf =   0   ;
    HI_U32  motion_diff_thd_0   =   16  ;
    HI_U32  motion_diff_thd_1   =   144 ;
    HI_U32  motion_diff_thd_2   =   208 ;
    HI_U32  motion_diff_thd_3   =   255 ;
    HI_U32  motion_diff_thd_4   =   255 ;
    HI_U32  motion_diff_thd_5   =   255 ;
    HI_U32  min_motion_iir_ratio    =   32  ;
    HI_U32  max_motion_iir_ratio    =   64  ;
    HI_U32  motion_iir_curve_slope_0    =   1   ;
    HI_U32  motion_iir_curve_slope_1    =   2   ;
    HI_U32  motion_iir_curve_slope_2    =   0   ;
    HI_U32  motion_iir_curve_slope_3    =   0   ;
    HI_U32  motion_iir_curve_ratio_0    =   32  ;
    HI_U32  motion_iir_curve_ratio_1    =   64  ;
    HI_U32  motion_iir_curve_ratio_2    =   64  ;
    HI_U32  motion_iir_curve_ratio_3    =   64  ;
    HI_U32  motion_iir_curve_ratio_4    =   64  ;
    HI_U32  rec_mode_fld_motion_step_0  =   2   ;
    HI_U32  rec_mode_fld_motion_step_1  =   2   ;
    HI_U32  rec_mode_frm_motion_step_0  =   0   ;
    HI_U32  rec_mode_frm_motion_step_1  =   0   ;
    HI_U32  ppre_info_en    =   1   ;
    HI_U32  pre_info_en =   0   ;
    HI_U32  his_motion_en   =   1   ;
    HI_U32  his_motion_using_mode   =   1   ;
    HI_U32  his_motion_write_mode   =   0   ;
    HI_U32  his_motion_info_write_mode  =   0   ;
    HI_U32  mor_flt_thd =   0   ;
    HI_U32  mor_flt_size    =   0   ;
    HI_U32  mor_flt_en  =   1   ;
    HI_U32  med_blend_en    =   0   ;
    HI_U32  comb_chk_min_hthd   =   255 ;
    HI_U32  comb_chk_min_vthd   =   15  ;
    HI_U32  comb_chk_lower_limit    =   9   ;
    HI_U32  comb_chk_upper_limit    =   160 ;
    HI_U32  comb_chk_edge_thd   =   16  ;
    HI_U32  comb_chk_md_thd =   20  ;
    HI_U32  comb_chk_en =   0   ;
    HI_U32  frame_motion_smooth_thd0    =   8   ;
    HI_U32  frame_motion_smooth_thd1    =   72  ;
    HI_U32  frame_motion_smooth_thd2    =   255 ;
    HI_U32  frame_motion_smooth_thd3    =   255 ;
    HI_U32  frame_motion_smooth_thd4    =   255 ;
    HI_U32  frame_motion_smooth_thd5    =   255 ;
    HI_U32  frame_motion_smooth_ratio_min   =   0   ;
    HI_U32  frame_motion_smooth_ratio_max   =   64  ;
    HI_U32  frame_motion_smooth_slope0  =   8   ;
    HI_U32  frame_motion_smooth_slope1  =   0   ;
    HI_U32  frame_motion_smooth_slope2  =   0   ;
    HI_U32  frame_motion_smooth_slope3  =   0   ;
    HI_U32  frame_motion_smooth_ratio0  =   0   ;
    HI_U32  frame_motion_smooth_ratio1  =   64  ;
    HI_U32  frame_motion_smooth_ratio2  =   64  ;
    HI_U32  frame_motion_smooth_ratio3  =   64  ;
    HI_U32  frame_motion_smooth_ratio4  =   64  ;
    HI_U32  motion_adjust_gain  =   64  ;
    HI_U32  motion_adjust_coring    =   0   ;
    HI_U32  motion_adjust_gain_chr  =   64  ;
    HI_U32  edge_coring =   0   ;
    HI_U32  edge_scale  =   6   ;
    HI_U32  k_y_mcw =   16  ;
    HI_U32  k_c_mcw =   8   ;
    HI_U32  x0_mcw_adj  =   64  ;
    HI_U32  k0_mcw_adj  =   64  ;
    HI_U32  g0_mcw_adj  =   1023    ;
    HI_U32  k1_mcw_adj  =   128 ;
    HI_U32  mc_lai_bldmode  =   1   ;
    HI_U32  ma_gbm_thd1 =   48  ;
    HI_U32  ma_gbm_thd0 =   16  ;
    HI_U32  ma_gbm_thd3 =   112 ;
    HI_U32  ma_gbm_thd2 =   80  ;
    HI_U32  mtth0_gmd   =   4   ;
    HI_U32  mtth1_gmd   =   12  ;
    HI_U32  mtth2_gmd   =   20  ;
    HI_U32  mtth3_gmd   =   28  ;
    HI_U32  mtfilten_gmd    =   1   ;
    HI_U32  k_maxmag_gmd    =   4   ;
    HI_U32  k_difh_gmd  =   22  ;
    HI_U32  k_mag_gmd   =   96  ;
    HI_U32  kmagh_1 =   31  ;
    HI_U32  kmagh_2 =   31  ;
    HI_U32  kmagv_1 =   8   ;
    HI_U32  kmagv_2 =   2   ;
    HI_U32  khoredge    =   31  ;
    HI_U32  scaler_horedge  =   2   ;
    HI_U32  frame_mag_en    =   0   ;
    HI_U32  motion_limt_1   =   60  ;
    HI_U32  motion_limt_2   =   60  ;
    HI_U32  scaler_framemotion  =   4   ;
    HI_U32  dir_ratio_c =   8   ;
    HI_U32  edge_str_coring_c   =   0   ;
    HI_U32  lmt_rgdify  =   511 ;
    HI_U32  core_rgdify =   5   ;
    HI_U32  g_rgdifycore    =   1023    ;
    HI_U32  k_rgdifycore    =   3   ;
    HI_U32  g_tpdif_rgsad   =   255 ;
    HI_U32  k_tpdif_rgsad   =   63  ;
    HI_U32  kmv_rgsad   =   15  ;
    HI_U32  coef_sadlpf =   1   ;
    HI_U32  th_0mvsad_rgmv  =   256 ;
    HI_U32  th_saddif_rgmv  =   128 ;
    HI_U32  thmag_rgmv  =   0   ;
    HI_U32  lmt_mag_rg  =   255 ;
    HI_U32  core_mag_rg =   3   ;
    HI_U32  en_mvadj_rgmvls =   1   ;
    HI_U32  th_mvadj_rgmvls =   8   ;
    HI_U32  k_mag_rgmvls    =   12  ;
    HI_S32  core_mag_rgmvls =   -64 ;
    HI_U32  k_mv_rgmvls =   16  ;
    HI_U32  core_mv_rgmvls  =   2   ;
    HI_U32  k_sadcore_rgmv  =   8   ;
    HI_U32  th_sad_rgls =   8   ;
    HI_U32  th_mag_rgls =   40  ;
    HI_U32  k_sad_rgls  =   8   ;
    HI_U32  force_mvx   =   0   ;
    HI_U32  force_mven  =   0   ;
    HI_U32  th_hblkdist_mvdlt   =   4   ;
    HI_U32  th_vblkdist_mvdlt   =   1   ;
    HI_U32  th_ls_mvdlt =   8   ;
    HI_U32  th_rgmvx_mvdlt  =   4   ;
    HI_U32  th_blkmvx_mvdlt =   6   ;
    HI_U32  thh_sad_mvdlt   =   16  ;
    HI_U32  thl_sad_mvdlt   =   96  ;
    HI_U32  g_mag_mvdlt =   16  ;
    HI_U32  th_mag_mvdlt    =   12  ;
    HI_U32  k_sadcore_mvdlt =   2   ;
    HI_U32  k_core_simimv   =   8   ;
    HI_U32  gl_core_simimv  =   0   ;
    HI_U32  gh_core_simimv  =   15  ;
    HI_U32  k_simimvw   =   32  ;
    HI_U32  k_rglsw =   20  ;
    HI_U32  rgtb_en_mcw =   1   ;
    HI_U32  core_mvy_mcw    =   3   ;
    HI_U32  k_mvy_mcw   =   20  ;
    HI_U32  core_rgsadadj_mcw   =   64  ;
    HI_U32  k_rgsadadj_mcw  =   8   ;
    HI_U32  k_core_vsaddif  =   16  ;
    HI_U32  gl_core_vsaddif =   5   ;
    HI_U32  gh_core_vsad_dif    =   64  ;
    HI_U32  k_vsaddifw  =   10  ;
    HI_U32  mode_rgysad_mcw =   0   ;
    HI_U32  core_rgmag_mcw  =   24  ;
    HI_U32  x0_rgmag_mcw    =   64  ;
    HI_U32  k0_rgmag_mcw    =   256 ;
    HI_U32  g0_rgmag_mcw    =   64  ;
    HI_U32  k1_rgmag_mcw    =   320 ;
    HI_U32  core_rgsad_mcw  =   96  ;
    HI_U32  x0_rgsad_mcw    =   512 ;
    HI_U32  k0_rgsad_mcw    =   160 ;
    HI_U32  g0_rgsad_mcw    =   255 ;
    HI_U32  k1_rgsad_mcw    =   128 ;
    HI_U32  x0_smrg_mcw =   16  ;
    HI_U32  k0_smrg_mcw =   64  ;
    HI_U32  x_rgsad_mcw =   112 ;
    HI_U32  k_rgsad_mcw =   24  ;
    HI_U32  x0_tpmvdist_mcw =   255 ;
    HI_U32  k0_tpmvdist_mcw =   64  ;
    HI_U32  g0_tpmvdist_mcw =   0   ;
    HI_U32  k1_tpmvdist_mcw =   32  ;
    HI_U32  k_minmvdist_mcw =   4   ;
    HI_U32  k_avgmvdist_mcw =   4   ;
    HI_U32  b_core_tpmvdist_mcw =   2   ;
    HI_U32  k_core_tpmvdist_mcw =   2   ;
    HI_U32  k_difhcore_mcw  =   18  ;
    HI_U32  k_difvcore_mcw  =   32  ;
    HI_U32  k_max_core_mcw  =   8   ;
    HI_U32  k_max_dif_mcw   =   8   ;
    HI_U32  k1_max_mag_mcw  =   8   ;
    HI_U32  k0_max_mag_mcw  =   8   ;
    HI_U32  k_tbdif_mcw =   15  ;
    HI_U32  k_tbmag_mcw =   0   ;
    HI_U32  x0_mag_wnd_mcw  =   32  ;
    HI_U32  k0_mag_wnd_mcw  =   6   ;
    HI_U32  g0_mag_wnd_mcw  =   24  ;
    HI_U32  k1_mag_wnd_mcw  =   6   ;
    HI_U32  g1_mag_wnd_mcw  =   288 ;
    HI_U32  x0_sad_wnd_mcw  =   8   ;
    HI_U32  k0_sad_wnd_mcw  =   16  ;
    HI_U32  g0_sad_wnd_mcw  =   16  ;
    HI_U32  k1_sad_wnd_mcw  =   16  ;
    HI_U32  g1_sad_wnd_mcw  =   288 ;
    HI_U32  k_max_hvdif_dw  =   12  ;
    HI_U32  gain_lpf_dw =   15  ;
    HI_U32  core_bhvdif_dw  =   5   ;
    HI_U32  k_bhvdif_dw =   64  ;
    HI_U32  b_bhvdif_dw =   0   ;
    HI_U32  b_hvdif_dw  =   0   ;
    HI_U32  core_hvdif_dw   =   16  ;
    HI_U32  k_difv_dw   =   20  ;
    HI_S32  core_mv_dw  =   -2  ;
    HI_U32  b_mv_dw =   56  ;
    HI_U32  x0_hvdif_dw =   256 ;
    HI_U32  k0_hvdif_dw =   8   ;
    HI_U32  g0_hvdif_dw =   128 ;
    HI_U32  k1_hvdif_dw =   8   ;
    HI_U32  x0_mv_dw    =   8   ;
    HI_U32  k0_mv_dw    =   16  ;
    HI_U32  g0_mv_dw    =   32  ;
    HI_U32  k1_mv_dw    =   64  ;
    HI_U32  x0_mt_dw    =   32  ;
    HI_U32  k0_mt_dw    =   32  ;
    HI_U32  g0_mt_dw    =   64  ;
    HI_U32  k1_mt_dw    =   32  ;
    HI_U32  g0_mv_mt    =   31  ;
    HI_U32  x0_mv_mt    =   1   ;
    HI_U32  k1_mv_mt    =   20  ;
    HI_U32  b_mt_dw =   0   ;
    HI_U32  gain_up_mclpfv  =   16  ;
    HI_U32  gain_dn_mclpfv  =   16  ;
    HI_U32  gain_mclpfh =   16  ;
    HI_U32  rs_pxlmag_mcw   =   0   ;
    HI_U32  x_pxlmag_mcw    =   2   ;
    HI_U32  k_pxlmag_mcw    =   8   ;
    HI_U32  mclpf_mode  =   1   ;
    HI_U32  g_pxlmag_mcw    =   0   ;
    HI_U32  k_y_vertw   =   8   ;
    HI_U32  k_c_vertw   =   15  ;
    HI_U32  k_delta =   8   ;
    HI_U32  bdh_mcpos   =   4   ;
    HI_U32  bdv_mcpos   =   4   ;
    HI_U32  c0_mc   =   0   ;
    HI_U32  r0_mc   =   0   ;
    HI_U32  c1_mc   =   width - 1 ;
    HI_U32  r1_mc   =   height - 1    ;
    HI_U32  mcmvrange   =   32  ;
    HI_U32  scenechange_mc  =   0   ;
    HI_U32  x_frcount_mc    =   8   ;
    HI_U32  k_frcount_mc    =   48  ;
    HI_U32  numt_lpf_en =   0   ;
    HI_U32  numt_coring =   0   ;
    HI_U32  numt_gain   =   32  ;
    HI_U32  mc_numt_blden   =   1   ;
    HI_U32  core_rglsw  =   0   ;
    HI_U32  th_cur_blksad   =   128 ;
    HI_U32  thh_neigh_blksad    =   256 ;
    HI_U32  thl_neigh_blksad    =   128 ;
    HI_U32  th_cur_blkmotion    =   8   ;
    HI_U32  th_rgmv_mag =   512 ;
    HI_U32  blkmv_update_en =   1   ;
    HI_U32  submv_sadchk_en =   0   ;
    HI_U32  cntlut_0    =   2   ;
    HI_U32  cntlut_1    =   2   ;
    HI_U32  cntlut_2    =   1   ;
    HI_U32  cntlut_3    =   1   ;
    HI_S32  cntlut_4    =   -15 ;
    HI_S32  cntlut_5    =   -15 ;
    HI_S32  cntlut_6    =   -15 ;
    HI_S32  cntlut_7    =   -15 ;
    HI_S32  cntlut_8    =   -15 ;
    HI_U32  mc_mtshift  =   0   ;
    HI_U32  mcw_scnt_en =   1   ;
    HI_U32  mcw_scnt_gain   =   273 ;
    HI_U32  demo_en =   0   ;
    HI_U32  demo_mode_l =   0   ;
    HI_U32  demo_mode_r =   0   ;
    HI_U32  demo_border =   0   ;




    VPSS_Sys_SetDieOutSelL(pstVpssRegs,  u32AddrOffset, die_out_sel_l);
    VPSS_Sys_SetDieOutSelC(pstVpssRegs,  u32AddrOffset, die_out_sel_c);
    VPSS_Sys_SetDieLMode(pstVpssRegs,  u32AddrOffset,  die_l_mode);
    VPSS_Sys_SetDieCMode(pstVpssRegs,  u32AddrOffset,  die_c_mode);
    VPSS_Sys_SetMcOnly(pstVpssRegs,  u32AddrOffset,  mc_only);
    VPSS_Sys_SetMaOnly(pstVpssRegs,  u32AddrOffset,  ma_only);
    VPSS_Sys_SetTwoFourPxlShare(pstVpssRegs,  u32AddrOffset, two_four_pxl_share);
    VPSS_Sys_SetEdgeSmoothEn(pstVpssRegs,  u32AddrOffset,  edge_smooth_en);
    VPSS_Sys_SetMchdirL(pstVpssRegs,  u32AddrOffset,  mchdir_l);
    VPSS_Sys_SetMchdirC(pstVpssRegs,  u32AddrOffset,  mchdir_c);
    VPSS_Sys_SetDieRst(pstVpssRegs,  u32AddrOffset,  die_rst);
    //VPSS_Sys_SetStinfoStop(pstVpssRegs,  u32AddrOffset,  stinfo_stop);
    VPSS_Sys_SetEdgeSmoothRatio(pstVpssRegs,  u32AddrOffset,  edge_smooth_ratio);
    VPSS_Sys_SetChromaMfOffset(pstVpssRegs,  u32AddrOffset,  chroma_mf_offset);
    VPSS_Sys_SetDeiStRstValue(pstVpssRegs,  u32AddrOffset,  dei_st_rst_value);
    VPSS_Sys_SetRecModeEn(pstVpssRegs,  u32AddrOffset,  rec_mode_en);
    VPSS_Sys_SetChromaMfMax(pstVpssRegs,  u32AddrOffset,  chroma_mf_max);
    VPSS_Sys_SetLumaMfMax(pstVpssRegs,  u32AddrOffset,  luma_mf_max);
    VPSS_Sys_SetMotionIirEn(pstVpssRegs,  u32AddrOffset,  motion_iir_en);
    VPSS_Sys_SetLumaScesdfMax(pstVpssRegs,  u32AddrOffset,  luma_scesdf_max);
    VPSS_Sys_SetFrameMotionSmoothEn(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_en);
    //VPSS_Sys_SetRecmodeFrmfldBlendMode(pstVpssRegs,  u32AddrOffset,  recmode_frmfld_blend_mode);
    VPSS_Sys_SetMinNorthStrength(pstVpssRegs,  u32AddrOffset,  min_north_strength);
    VPSS_Sys_SetDirRatioNorth(pstVpssRegs,  u32AddrOffset,  dir_ratio_north);
    VPSS_Sys_SetRecModeOutputMode(pstVpssRegs,  u32AddrOffset,  rec_mode_output_mode);
    VPSS_Sys_SetRecModeSetPreInfoMode(pstVpssRegs,  u32AddrOffset,  rec_mode_set_pre_info_mode);
    VPSS_Sys_SetRangeScale(pstVpssRegs,  u32AddrOffset,  range_scale);
    VPSS_Sys_SetBc1Gain(pstVpssRegs,  u32AddrOffset,  bc1_gain);
    VPSS_Sys_SetBc1AutodzGain(pstVpssRegs,  u32AddrOffset,  bc1_autodz_gain);
    VPSS_Sys_SetBc1MaxDz(pstVpssRegs,  u32AddrOffset,  bc1_max_dz);
    VPSS_Sys_SetBc2Gain(pstVpssRegs,  u32AddrOffset,  bc2_gain);
    VPSS_Sys_SetBc2AutodzGain(pstVpssRegs,  u32AddrOffset,  bc2_autodz_gain);
    VPSS_Sys_SetBc2MaxDz(pstVpssRegs,  u32AddrOffset,  bc2_max_dz);
    VPSS_Sys_SetDir3Scale(pstVpssRegs,  u32AddrOffset,  dir3_scale);
    VPSS_Sys_SetDir2Scale(pstVpssRegs,  u32AddrOffset,  dir2_scale);
    VPSS_Sys_SetDir1Scale(pstVpssRegs,  u32AddrOffset,  dir1_scale);
    VPSS_Sys_SetDir0Scale(pstVpssRegs,  u32AddrOffset,  dir0_scale);
    VPSS_Sys_SetDir7Scale(pstVpssRegs,  u32AddrOffset,  dir7_scale);
    VPSS_Sys_SetDir6Scale(pstVpssRegs,  u32AddrOffset,  dir6_scale);
    VPSS_Sys_SetDir5Scale(pstVpssRegs,  u32AddrOffset,  dir5_scale);
    VPSS_Sys_SetDir4Scale(pstVpssRegs,  u32AddrOffset,  dir4_scale);
    VPSS_Sys_SetDir11Scale(pstVpssRegs,  u32AddrOffset,  dir11_scale);
    VPSS_Sys_SetDir10Scale(pstVpssRegs,  u32AddrOffset,  dir10_scale);
    VPSS_Sys_SetDir9Scale(pstVpssRegs,  u32AddrOffset,  dir9_scale);
    VPSS_Sys_SetDir8Scale(pstVpssRegs,  u32AddrOffset,  dir8_scale);
    VPSS_Sys_SetDir14Scale(pstVpssRegs,  u32AddrOffset,  dir14_scale);
    VPSS_Sys_SetDir13Scale(pstVpssRegs,  u32AddrOffset,  dir13_scale);
    VPSS_Sys_SetDir12Scale(pstVpssRegs,  u32AddrOffset,  dir12_scale);
    //VPSS_Sys_SetCHeightCnt(pstVpssRegs,  u32AddrOffset,  c_height_cnt);
    //VPSS_Sys_SetLHeightCnt(pstVpssRegs,  u32AddrOffset,  l_height_cnt);
    //VPSS_Sys_SetCurCstate(pstVpssRegs,  u32AddrOffset,  cur_cstate);
    //VPSS_Sys_SetCurState(pstVpssRegs,  u32AddrOffset,  cur_state);
    VPSS_Sys_SetIntpScaleRatio8(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_8);
    VPSS_Sys_SetIntpScaleRatio7(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_7);
    VPSS_Sys_SetIntpScaleRatio6(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_6);
    VPSS_Sys_SetIntpScaleRatio5(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_5);
    VPSS_Sys_SetIntpScaleRatio4(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_4);
    VPSS_Sys_SetIntpScaleRatio3(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_3);
    VPSS_Sys_SetIntpScaleRatio2(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_2);
    VPSS_Sys_SetIntpScaleRatio1(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_1);
    VPSS_Sys_SetIntpScaleRatio15(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_15);
    VPSS_Sys_SetIntpScaleRatio14(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_14);
    VPSS_Sys_SetIntpScaleRatio13(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_13);
    VPSS_Sys_SetIntpScaleRatio12(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_12);
    VPSS_Sys_SetIntpScaleRatio11(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_11);
    VPSS_Sys_SetIntpScaleRatio10(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_10);
    VPSS_Sys_SetIntpScaleRatio9(pstVpssRegs,  u32AddrOffset,  intp_scale_ratio_9);
    //VPSS_Sys_SetStrengthThd(pstVpssRegs,  u32AddrOffset,  strength_thd);
    VPSS_Sys_SetHorEdgeEn(pstVpssRegs,  u32AddrOffset,  hor_edge_en);
    VPSS_Sys_SetEdgeMode(pstVpssRegs,  u32AddrOffset,  edge_mode);
    VPSS_Sys_SetDirThd(pstVpssRegs,  u32AddrOffset,  dir_thd);
    //VPSS_Sys_SetBcGain(pstVpssRegs,  u32AddrOffset,  bc_gain);
    VPSS_Sys_SetFldMotionCoring(pstVpssRegs,  u32AddrOffset,  fld_motion_coring);
    VPSS_Sys_SetJitterCoring(pstVpssRegs,  u32AddrOffset,  jitter_coring);
    VPSS_Sys_SetJitterGain(pstVpssRegs,  u32AddrOffset,  jitter_gain);
    VPSS_Sys_SetLongMotionShf(pstVpssRegs,  u32AddrOffset,  long_motion_shf);
    VPSS_Sys_SetFldMotionWndMode(pstVpssRegs,  u32AddrOffset,  fld_motion_wnd_mode);
    VPSS_Sys_SetFldMotionGain(pstVpssRegs,  u32AddrOffset,  fld_motion_gain);
    VPSS_Sys_SetFldMotionCurveSlope(pstVpssRegs,  u32AddrOffset,  fld_motion_curve_slope);
    VPSS_Sys_SetFldMotionThdHigh(pstVpssRegs,  u32AddrOffset,  fld_motion_thd_high);
    VPSS_Sys_SetFldMotionThdLow(pstVpssRegs,  u32AddrOffset,  fld_motion_thd_low);
    VPSS_Sys_SetMotionDiffThd3(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_3);
    VPSS_Sys_SetMotionDiffThd2(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_2);
    VPSS_Sys_SetMotionDiffThd1(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_1);
    VPSS_Sys_SetMotionDiffThd0(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_0);
    VPSS_Sys_SetMaxMotionIirRatio(pstVpssRegs,  u32AddrOffset,  max_motion_iir_ratio);
    VPSS_Sys_SetMinMotionIirRatio(pstVpssRegs,  u32AddrOffset,  min_motion_iir_ratio);
    VPSS_Sys_SetMotionDiffThd5(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_5);
    VPSS_Sys_SetMotionDiffThd4(pstVpssRegs,  u32AddrOffset,  motion_diff_thd_4);
    VPSS_Sys_SetMotionIirCurveRatio0(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_0);
    VPSS_Sys_SetMotionIirCurveSlope3(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_3);
    VPSS_Sys_SetMotionIirCurveSlope2(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_2);
    VPSS_Sys_SetMotionIirCurveSlope1(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_1);
    VPSS_Sys_SetMotionIirCurveSlope0(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_slope_0);
    VPSS_Sys_SetMotionIirCurveRatio4(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_4);
    VPSS_Sys_SetMotionIirCurveRatio3(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_3);
    VPSS_Sys_SetMotionIirCurveRatio2(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_2);
    VPSS_Sys_SetMotionIirCurveRatio1(pstVpssRegs,  u32AddrOffset,  motion_iir_curve_ratio_1);
    VPSS_Sys_SetHisMotionInfoWriteMode(pstVpssRegs,  u32AddrOffset,  his_motion_info_write_mode);
    VPSS_Sys_SetHisMotionWriteMode(pstVpssRegs,  u32AddrOffset,  his_motion_write_mode);
    VPSS_Sys_SetHisMotionUsingMode(pstVpssRegs,  u32AddrOffset,  his_motion_using_mode);
    VPSS_Sys_SetHisMotionEn(pstVpssRegs,  u32AddrOffset,  his_motion_en);
    VPSS_Sys_SetPreInfoEn(pstVpssRegs,  u32AddrOffset,  pre_info_en);
    VPSS_Sys_SetPpreInfoEn(pstVpssRegs,  u32AddrOffset,  ppre_info_en);
    VPSS_Sys_SetRecModeFrmMotionStep1(pstVpssRegs,  u32AddrOffset,  rec_mode_frm_motion_step_1);
    VPSS_Sys_SetRecModeFrmMotionStep0(pstVpssRegs,  u32AddrOffset,  rec_mode_frm_motion_step_0);
    VPSS_Sys_SetRecModeFldMotionStep1(pstVpssRegs,  u32AddrOffset,  rec_mode_fld_motion_step_1);
    VPSS_Sys_SetRecModeFldMotionStep0(pstVpssRegs,  u32AddrOffset,  rec_mode_fld_motion_step_0);
    VPSS_Sys_SetMedBlendEn(pstVpssRegs,  u32AddrOffset,  med_blend_en);
    VPSS_Sys_SetMorFltEn(pstVpssRegs,  u32AddrOffset,  mor_flt_en);
    VPSS_Sys_SetMorFltSize(pstVpssRegs,  u32AddrOffset,  mor_flt_size);
    VPSS_Sys_SetMorFltThd(pstVpssRegs,  u32AddrOffset,  mor_flt_thd);
    VPSS_Sys_SetCombChkUpperLimit(pstVpssRegs,  u32AddrOffset,  comb_chk_upper_limit);
    VPSS_Sys_SetCombChkLowerLimit(pstVpssRegs,  u32AddrOffset,  comb_chk_lower_limit);
    VPSS_Sys_SetCombChkMinVthd(pstVpssRegs,  u32AddrOffset,  comb_chk_min_vthd);
    VPSS_Sys_SetCombChkMinHthd(pstVpssRegs,  u32AddrOffset,  comb_chk_min_hthd);
    VPSS_Sys_SetCombChkEn(pstVpssRegs,  u32AddrOffset,  comb_chk_en);
    VPSS_Sys_SetCombChkMdThd(pstVpssRegs,  u32AddrOffset,  comb_chk_md_thd);
    VPSS_Sys_SetCombChkEdgeThd(pstVpssRegs,  u32AddrOffset,  comb_chk_edge_thd);
    VPSS_Sys_SetFrameMotionSmoothThd3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd3);
    VPSS_Sys_SetFrameMotionSmoothThd2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd2);
    VPSS_Sys_SetFrameMotionSmoothThd1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd1);
    VPSS_Sys_SetFrameMotionSmoothThd0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd0);
    VPSS_Sys_SetFrameMotionSmoothRatioMax(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio_max);
    VPSS_Sys_SetFrameMotionSmoothRatioMin(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio_min);
    VPSS_Sys_SetFrameMotionSmoothThd5(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd5);
    VPSS_Sys_SetFrameMotionSmoothThd4(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_thd4);
    VPSS_Sys_SetFrameMotionSmoothRatio0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio0);
    VPSS_Sys_SetFrameMotionSmoothSlope3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope3);
    VPSS_Sys_SetFrameMotionSmoothSlope2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope2);
    VPSS_Sys_SetFrameMotionSmoothSlope1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope1);
    VPSS_Sys_SetFrameMotionSmoothSlope0(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_slope0);
    VPSS_Sys_SetFrameMotionSmoothRatio4(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio4);
    VPSS_Sys_SetFrameMotionSmoothRatio3(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio3);
    VPSS_Sys_SetFrameMotionSmoothRatio2(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio2);
    VPSS_Sys_SetFrameMotionSmoothRatio1(pstVpssRegs,  u32AddrOffset,  frame_motion_smooth_ratio1);
#if 0
    VPSS_Sys_SetFrameFieldBlendThd3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd3);
    VPSS_Sys_SetFrameFieldBlendThd2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd2);
    VPSS_Sys_SetFrameFieldBlendThd1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd1);
    VPSS_Sys_SetFrameFieldBlendThd0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd0);
    VPSS_Sys_SetFrameFieldBlendRatioMax(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio_max);
    VPSS_Sys_SetFrameFieldBlendRatioMin(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio_min);
    VPSS_Sys_SetFrameFieldBlendThd5(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd5);
    VPSS_Sys_SetFrameFieldBlendThd4(pstVpssRegs,  u32AddrOffset,  frame_field_blend_thd4);
    VPSS_Sys_SetFrameFieldBlendRatio0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio0);
    VPSS_Sys_SetFrameFieldBlendSlope3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope3);
    VPSS_Sys_SetFrameFieldBlendSlope2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope2);
    VPSS_Sys_SetFrameFieldBlendSlope1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope1);
    VPSS_Sys_SetFrameFieldBlendSlope0(pstVpssRegs,  u32AddrOffset,  frame_field_blend_slope0);
    VPSS_Sys_SetFrameFieldBlendRatio4(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio4);
    VPSS_Sys_SetFrameFieldBlendRatio3(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio3);
    VPSS_Sys_SetFrameFieldBlendRatio2(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio2);
    VPSS_Sys_SetFrameFieldBlendRatio1(pstVpssRegs,  u32AddrOffset,  frame_field_blend_ratio1);
#endif
    VPSS_Sys_SetMotionAdjustGainChr(pstVpssRegs,  u32AddrOffset,  motion_adjust_gain_chr);
    VPSS_Sys_SetMotionAdjustCoring(pstVpssRegs,  u32AddrOffset,  motion_adjust_coring);
    VPSS_Sys_SetMotionAdjustGain(pstVpssRegs,  u32AddrOffset,  motion_adjust_gain);
#if 0
    VPSS_Sys_SetEdgeNorm1(pstVpssRegs,  u32AddrOffset,  edge_norm_1);
    VPSS_Sys_SetEdgeNorm0(pstVpssRegs,  u32AddrOffset,  edge_norm_0);
    VPSS_Sys_SetEdgeNorm3(pstVpssRegs,  u32AddrOffset,  edge_norm_3);
    VPSS_Sys_SetEdgeNorm2(pstVpssRegs,  u32AddrOffset,  edge_norm_2);
    VPSS_Sys_SetMcStrengthK3(pstVpssRegs,  u32AddrOffset,  mc_strength_k3);
    VPSS_Sys_SetEdgeNorm5(pstVpssRegs,  u32AddrOffset,  edge_norm_5);
    VPSS_Sys_SetEdgeNorm4(pstVpssRegs,  u32AddrOffset,  edge_norm_4);
    VPSS_Sys_SetMcStrengthG3(pstVpssRegs,  u32AddrOffset,  mc_strength_g3);
    VPSS_Sys_SetEdgeNorm7(pstVpssRegs,  u32AddrOffset,  edge_norm_7);
    VPSS_Sys_SetEdgeNorm6(pstVpssRegs,  u32AddrOffset,  edge_norm_6);
    VPSS_Sys_SetInterDiffThd0(pstVpssRegs,  u32AddrOffset,  inter_diff_thd0);
    VPSS_Sys_SetEdgeNorm9(pstVpssRegs,  u32AddrOffset,  edge_norm_9);
    VPSS_Sys_SetEdgeNorm8(pstVpssRegs,  u32AddrOffset,  edge_norm_8);
    VPSS_Sys_SetInterDiffThd1(pstVpssRegs,  u32AddrOffset,  inter_diff_thd1);
    VPSS_Sys_SetEdgeNorm11(pstVpssRegs,  u32AddrOffset,  edge_norm_11);
    VPSS_Sys_SetEdgeNorm10(pstVpssRegs,  u32AddrOffset,  edge_norm_10);
    VPSS_Sys_SetInterDiffThd2(pstVpssRegs,  u32AddrOffset,  inter_diff_thd2);
    VPSS_Sys_SetMcStrengthG0(pstVpssRegs,  u32AddrOffset,  mc_strength_g0);
    VPSS_Sys_SetMcStrengthK2(pstVpssRegs,  u32AddrOffset,  mc_strength_k2);
    VPSS_Sys_SetMcStrengthK1(pstVpssRegs,  u32AddrOffset,  mc_strength_k1);
    VPSS_Sys_SetMcStrengthK0(pstVpssRegs,  u32AddrOffset,  mc_strength_k0);
    VPSS_Sys_SetMcStrengthMaxg(pstVpssRegs,  u32AddrOffset,  mc_strength_maxg);
    VPSS_Sys_SetMcStrengthMing(pstVpssRegs,  u32AddrOffset,  mc_strength_ming);
    VPSS_Sys_SetMcStrengthG2(pstVpssRegs,  u32AddrOffset,  mc_strength_g2);
    VPSS_Sys_SetMcStrengthG1(pstVpssRegs,  u32AddrOffset,  mc_strength_g1);
#endif
    VPSS_Sys_SetEdgeScale(pstVpssRegs,  u32AddrOffset,  edge_scale);
    VPSS_Sys_SetEdgeCoring(pstVpssRegs,  u32AddrOffset,  edge_coring);
    //VPSS_Sys_SetKCMcbld(pstVpssRegs,  u32AddrOffset,  k_c_mcbld);
    VPSS_Sys_SetKCMcw(pstVpssRegs,  u32AddrOffset,  k_c_mcw);
    //VPSS_Sys_SetKYMcbld(pstVpssRegs,  u32AddrOffset,  k_y_mcbld);
    VPSS_Sys_SetKYMcw(pstVpssRegs,  u32AddrOffset,  k_y_mcw);
    VPSS_Sys_SetG0McwAdj(pstVpssRegs,  u32AddrOffset,  g0_mcw_adj);
    VPSS_Sys_SetK0McwAdj(pstVpssRegs,  u32AddrOffset,  k0_mcw_adj);
    VPSS_Sys_SetX0McwAdj(pstVpssRegs,  u32AddrOffset,  x0_mcw_adj);
    //VPSS_Sys_SetK1Mcbld(pstVpssRegs,  u32AddrOffset,  k1_mcbld);
    //VPSS_Sys_SetK0Mcbld(pstVpssRegs,  u32AddrOffset,  k0_mcbld);
    //VPSS_Sys_SetX0Mcbld(pstVpssRegs,  u32AddrOffset,  x0_mcbld);
    VPSS_Sys_SetK1McwAdj(pstVpssRegs,  u32AddrOffset,  k1_mcw_adj);
    VPSS_Sys_SetMcLaiBldmode(pstVpssRegs,  u32AddrOffset,  mc_lai_bldmode);
    //VPSS_Sys_SetKCurwMcbld(pstVpssRegs,  u32AddrOffset,  k_curw_mcbld);
    //VPSS_Sys_SetG0Mcbld(pstVpssRegs,  u32AddrOffset,  g0_mcbld);
    VPSS_Sys_SetMaGbmThd0(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd0);
    VPSS_Sys_SetMaGbmThd1(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd1);
    VPSS_Sys_SetMaGbmThd2(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd2);
    VPSS_Sys_SetMaGbmThd3(pstVpssRegs,  u32AddrOffset,  ma_gbm_thd3);
    VPSS_Sys_SetMtfiltenGmd(pstVpssRegs,  u32AddrOffset,  mtfilten_gmd);
    VPSS_Sys_SetMtth3Gmd(pstVpssRegs,  u32AddrOffset,  mtth3_gmd);
    VPSS_Sys_SetMtth2Gmd(pstVpssRegs,  u32AddrOffset,  mtth2_gmd);
    VPSS_Sys_SetMtth1Gmd(pstVpssRegs,  u32AddrOffset,  mtth1_gmd);
    VPSS_Sys_SetMtth0Gmd(pstVpssRegs,  u32AddrOffset,  mtth0_gmd);
    VPSS_Sys_SetKMagGmd(pstVpssRegs,  u32AddrOffset,  k_mag_gmd);
    VPSS_Sys_SetKDifhGmd(pstVpssRegs,  u32AddrOffset,  k_difh_gmd);
    VPSS_Sys_SetKMaxmagGmd(pstVpssRegs,  u32AddrOffset,  k_maxmag_gmd);
    VPSS_Sys_SetKhoredge(pstVpssRegs,  u32AddrOffset,  khoredge);
    VPSS_Sys_SetKmagv2(pstVpssRegs,  u32AddrOffset,  kmagv_2);
    VPSS_Sys_SetKmagv1(pstVpssRegs,  u32AddrOffset,  kmagv_1);
    VPSS_Sys_SetKmagh2(pstVpssRegs,  u32AddrOffset,  kmagh_2);
    VPSS_Sys_SetKmagh1(pstVpssRegs,  u32AddrOffset,  kmagh_1);
    VPSS_Sys_SetScalerFramemotion(pstVpssRegs,  u32AddrOffset,  scaler_framemotion);
    VPSS_Sys_SetMotionLimt2(pstVpssRegs,  u32AddrOffset,  motion_limt_2);
    VPSS_Sys_SetMotionLimt1(pstVpssRegs,  u32AddrOffset,  motion_limt_1);
    VPSS_Sys_SetFrameMagEn(pstVpssRegs,  u32AddrOffset,  frame_mag_en);
    VPSS_Sys_SetScalerHoredge(pstVpssRegs,  u32AddrOffset,  scaler_horedge);
    VPSS_Sys_SetEdgeStrCoringC(pstVpssRegs,  u32AddrOffset,  edge_str_coring_c);
    VPSS_Sys_SetDirRatioC(pstVpssRegs,  u32AddrOffset,  dir_ratio_c);
#if 0
    VPSS_Sys_SetHistThd3(pstVpssRegs,  u32AddrOffset,  hist_thd3);
    VPSS_Sys_SetHistThd2(pstVpssRegs,  u32AddrOffset,  hist_thd2);
    VPSS_Sys_SetHistThd1(pstVpssRegs,  u32AddrOffset,  hist_thd1);
    VPSS_Sys_SetHistThd0(pstVpssRegs,  u32AddrOffset,  hist_thd0);
    VPSS_Sys_SetMovCoringNorm(pstVpssRegs,  u32AddrOffset,  mov_coring_norm);
    VPSS_Sys_SetMovCoringTkr(pstVpssRegs,  u32AddrOffset,  mov_coring_tkr);
    VPSS_Sys_SetMovCoringBlk(pstVpssRegs,  u32AddrOffset,  mov_coring_blk);
    VPSS_Sys_SetLasiMode(pstVpssRegs,  u32AddrOffset,  lasi_mode);
    VPSS_Sys_SetBitsmov2r(pstVpssRegs,  u32AddrOffset,  bitsmov2r);
    VPSS_Sys_SetDiffMovblkThd(pstVpssRegs,  u32AddrOffset,  diff_movblk_thd);
    VPSS_Sys_SetUmThd2(pstVpssRegs,  u32AddrOffset,  um_thd2);
    VPSS_Sys_SetUmThd1(pstVpssRegs,  u32AddrOffset,  um_thd1);
    VPSS_Sys_SetUmThd0(pstVpssRegs,  u32AddrOffset,  um_thd0);
    VPSS_Sys_SetCoringBlk(pstVpssRegs,  u32AddrOffset,  coring_blk);
    VPSS_Sys_SetCoringNorm(pstVpssRegs,  u32AddrOffset,  coring_norm);
    VPSS_Sys_SetCoringTkr(pstVpssRegs,  u32AddrOffset,  coring_tkr);
    VPSS_Sys_SetPccHthd(pstVpssRegs,  u32AddrOffset,  pcc_hthd);
    VPSS_Sys_SetPccVthd3(pstVpssRegs,  u32AddrOffset,  pcc_vthd3);
    VPSS_Sys_SetPccVthd2(pstVpssRegs,  u32AddrOffset,  pcc_vthd2);
    VPSS_Sys_SetPccVthd1(pstVpssRegs,  u32AddrOffset,  pcc_vthd1);
    VPSS_Sys_SetPccVthd0(pstVpssRegs,  u32AddrOffset,  pcc_vthd0);
    VPSS_Sys_SetItdiffVthd3(pstVpssRegs,  u32AddrOffset,  itdiff_vthd3);
    VPSS_Sys_SetItdiffVthd2(pstVpssRegs,  u32AddrOffset,  itdiff_vthd2);
    VPSS_Sys_SetItdiffVthd1(pstVpssRegs,  u32AddrOffset,  itdiff_vthd1);
    VPSS_Sys_SetItdiffVthd0(pstVpssRegs,  u32AddrOffset,  itdiff_vthd0);
    VPSS_Sys_SetLasiMovThd(pstVpssRegs,  u32AddrOffset,  lasi_mov_thd);
    VPSS_Sys_SetLasiEdgeThd(pstVpssRegs,  u32AddrOffset,  lasi_edge_thd);
    VPSS_Sys_SetLasiCoringThd(pstVpssRegs,  u32AddrOffset,  lasi_coring_thd);
    VPSS_Sys_SetLasiTxtCoring(pstVpssRegs,  u32AddrOffset,  lasi_txt_coring);
    VPSS_Sys_SetLasiTxtAlpha(pstVpssRegs,  u32AddrOffset,  lasi_txt_alpha);
    VPSS_Sys_SetLasiTxtThd3(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd3);
    VPSS_Sys_SetLasiTxtThd2(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd2);
    VPSS_Sys_SetLasiTxtThd1(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd1);
    VPSS_Sys_SetLasiTxtThd0(pstVpssRegs,  u32AddrOffset,  lasi_txt_thd0);
    VPSS_Sys_SetRegion1YStt(pstVpssRegs,  u32AddrOffset,  region1_y_stt);
    VPSS_Sys_SetRegion1YEnd(pstVpssRegs,  u32AddrOffset,  region1_y_end);
#endif
    VPSS_Sys_SetKRgdifycore(pstVpssRegs,  u32AddrOffset,  k_rgdifycore);
    VPSS_Sys_SetGRgdifycore(pstVpssRegs,  u32AddrOffset,  g_rgdifycore);
    VPSS_Sys_SetCoreRgdify(pstVpssRegs,  u32AddrOffset,  core_rgdify);
    VPSS_Sys_SetLmtRgdify(pstVpssRegs,  u32AddrOffset,  lmt_rgdify);
    VPSS_Sys_SetCoefSadlpf(pstVpssRegs,  u32AddrOffset,  coef_sadlpf);
    VPSS_Sys_SetKmvRgsad(pstVpssRegs,  u32AddrOffset,  kmv_rgsad);
    VPSS_Sys_SetKTpdifRgsad(pstVpssRegs,  u32AddrOffset,  k_tpdif_rgsad);
    VPSS_Sys_SetGTpdifRgsad(pstVpssRegs,  u32AddrOffset,  g_tpdif_rgsad);
    VPSS_Sys_SetThmagRgmv(pstVpssRegs,  u32AddrOffset,  thmag_rgmv);
    VPSS_Sys_SetThSaddifRgmv(pstVpssRegs,  u32AddrOffset,  th_saddif_rgmv);
    VPSS_Sys_SetTh0mvsadRgmv(pstVpssRegs,  u32AddrOffset,  th_0mvsad_rgmv);
    VPSS_Sys_SetCoreMagRg(pstVpssRegs,  u32AddrOffset,  core_mag_rg);
    VPSS_Sys_SetLmtMagRg(pstVpssRegs,  u32AddrOffset,  lmt_mag_rg);
    VPSS_Sys_SetCoreMvRgmvls(pstVpssRegs,  u32AddrOffset,  core_mv_rgmvls);
    VPSS_Sys_SetKMvRgmvls(pstVpssRegs,  u32AddrOffset,  k_mv_rgmvls);
    VPSS_Sys_SetCoreMagRgmvls(pstVpssRegs,  u32AddrOffset,  core_mag_rgmvls);
    VPSS_Sys_SetKMagRgmvls(pstVpssRegs,  u32AddrOffset,  k_mag_rgmvls);
    VPSS_Sys_SetThMvadjRgmvls(pstVpssRegs,  u32AddrOffset,  th_mvadj_rgmvls);
    VPSS_Sys_SetEnMvadjRgmvls(pstVpssRegs,  u32AddrOffset,  en_mvadj_rgmvls);
    VPSS_Sys_SetKSadRgls(pstVpssRegs,  u32AddrOffset,  k_sad_rgls);
    VPSS_Sys_SetThMagRgls(pstVpssRegs,  u32AddrOffset,  th_mag_rgls);
    VPSS_Sys_SetThSadRgls(pstVpssRegs,  u32AddrOffset,  th_sad_rgls);
    VPSS_Sys_SetKSadcoreRgmv(pstVpssRegs,  u32AddrOffset,  k_sadcore_rgmv);
    VPSS_Sys_SetForceMven(pstVpssRegs,  u32AddrOffset,  force_mven);
    VPSS_Sys_SetForceMvx(pstVpssRegs,  u32AddrOffset,  force_mvx);
    VPSS_Sys_SetThBlkmvxMvdlt(pstVpssRegs,  u32AddrOffset,  th_blkmvx_mvdlt);
    VPSS_Sys_SetThRgmvxMvdlt(pstVpssRegs,  u32AddrOffset,  th_rgmvx_mvdlt);
    VPSS_Sys_SetThLsMvdlt(pstVpssRegs,  u32AddrOffset,  th_ls_mvdlt);
    VPSS_Sys_SetThVblkdistMvdlt(pstVpssRegs,  u32AddrOffset,  th_vblkdist_mvdlt);
    VPSS_Sys_SetThHblkdistMvdlt(pstVpssRegs,  u32AddrOffset,  th_hblkdist_mvdlt);
    VPSS_Sys_SetKSadcoreMvdlt(pstVpssRegs,  u32AddrOffset,  k_sadcore_mvdlt);
    VPSS_Sys_SetThMagMvdlt(pstVpssRegs,  u32AddrOffset,  th_mag_mvdlt);
    VPSS_Sys_SetGMagMvdlt(pstVpssRegs,  u32AddrOffset,  g_mag_mvdlt);
    VPSS_Sys_SetThlSadMvdlt(pstVpssRegs,  u32AddrOffset,  thl_sad_mvdlt);
    VPSS_Sys_SetThhSadMvdlt(pstVpssRegs,  u32AddrOffset,  thh_sad_mvdlt);
    VPSS_Sys_SetKRglsw(pstVpssRegs,  u32AddrOffset,  k_rglsw);
    VPSS_Sys_SetKSimimvw(pstVpssRegs,  u32AddrOffset,  k_simimvw);
    VPSS_Sys_SetGhCoreSimimv(pstVpssRegs,  u32AddrOffset,  gh_core_simimv);
    VPSS_Sys_SetGlCoreSimimv(pstVpssRegs,  u32AddrOffset,  gl_core_simimv);
    VPSS_Sys_SetKCoreSimimv(pstVpssRegs,  u32AddrOffset,  k_core_simimv);
    VPSS_Sys_SetKCoreVsaddif(pstVpssRegs,  u32AddrOffset,  k_core_vsaddif);
    VPSS_Sys_SetKRgsadadjMcw(pstVpssRegs,  u32AddrOffset,  k_rgsadadj_mcw);
    VPSS_Sys_SetCoreRgsadadjMcw(pstVpssRegs,  u32AddrOffset,  core_rgsadadj_mcw);
    VPSS_Sys_SetKMvyMcw(pstVpssRegs,  u32AddrOffset,  k_mvy_mcw);
    VPSS_Sys_SetCoreMvyMcw(pstVpssRegs,  u32AddrOffset,  core_mvy_mcw);
    VPSS_Sys_SetRgtbEnMcw(pstVpssRegs,  u32AddrOffset,  rgtb_en_mcw);
    VPSS_Sys_SetCoreRgmagMcw(pstVpssRegs,  u32AddrOffset,  core_rgmag_mcw);
    VPSS_Sys_SetModeRgysadMcw(pstVpssRegs,  u32AddrOffset,  mode_rgysad_mcw);
    VPSS_Sys_SetKVsaddifw(pstVpssRegs,  u32AddrOffset,  k_vsaddifw);
    VPSS_Sys_SetGhCoreVsadDif(pstVpssRegs,  u32AddrOffset,  gh_core_vsad_dif);
    VPSS_Sys_SetGlCoreVsaddif(pstVpssRegs,  u32AddrOffset,  gl_core_vsaddif);
    VPSS_Sys_SetG0RgmagMcw(pstVpssRegs,  u32AddrOffset,  g0_rgmag_mcw);
    VPSS_Sys_SetK0RgmagMcw(pstVpssRegs,  u32AddrOffset,  k0_rgmag_mcw);
    VPSS_Sys_SetX0RgmagMcw(pstVpssRegs,  u32AddrOffset,  x0_rgmag_mcw);
    VPSS_Sys_SetX0RgsadMcw(pstVpssRegs,  u32AddrOffset,  x0_rgsad_mcw);
    VPSS_Sys_SetCoreRgsadMcw(pstVpssRegs,  u32AddrOffset,  core_rgsad_mcw);
    VPSS_Sys_SetK1RgmagMcw(pstVpssRegs,  u32AddrOffset,  k1_rgmag_mcw);
    VPSS_Sys_SetK1RgsadMcw(pstVpssRegs,  u32AddrOffset,  k1_rgsad_mcw);
    VPSS_Sys_SetG0RgsadMcw(pstVpssRegs,  u32AddrOffset,  g0_rgsad_mcw);
    VPSS_Sys_SetK0RgsadMcw(pstVpssRegs,  u32AddrOffset,  k0_rgsad_mcw);
    VPSS_Sys_SetKRgsadMcw(pstVpssRegs,  u32AddrOffset,  k_rgsad_mcw);
    VPSS_Sys_SetXRgsadMcw(pstVpssRegs,  u32AddrOffset,  x_rgsad_mcw);
    VPSS_Sys_SetK0SmrgMcw(pstVpssRegs,  u32AddrOffset,  k0_smrg_mcw);
    VPSS_Sys_SetX0SmrgMcw(pstVpssRegs,  u32AddrOffset,  x0_smrg_mcw);
    VPSS_Sys_SetK1TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k1_tpmvdist_mcw);
    VPSS_Sys_SetG0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  g0_tpmvdist_mcw);
    VPSS_Sys_SetK0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k0_tpmvdist_mcw);
    VPSS_Sys_SetX0TpmvdistMcw(pstVpssRegs,  u32AddrOffset,  x0_tpmvdist_mcw);
    VPSS_Sys_SetKCoreTpmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_core_tpmvdist_mcw);
    VPSS_Sys_SetBCoreTpmvdistMcw(pstVpssRegs,  u32AddrOffset,  b_core_tpmvdist_mcw);
    VPSS_Sys_SetKAvgmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_avgmvdist_mcw);
    VPSS_Sys_SetKMinmvdistMcw(pstVpssRegs,  u32AddrOffset,  k_minmvdist_mcw);
    VPSS_Sys_SetKTbdifMcw(pstVpssRegs,  u32AddrOffset,  k_tbdif_mcw);
    VPSS_Sys_SetK0MaxMagMcw(pstVpssRegs,  u32AddrOffset,  k0_max_mag_mcw);
    VPSS_Sys_SetK1MaxMagMcw(pstVpssRegs,  u32AddrOffset,  k1_max_mag_mcw);
    VPSS_Sys_SetKMaxDifMcw(pstVpssRegs,  u32AddrOffset,  k_max_dif_mcw);
    VPSS_Sys_SetKMaxCoreMcw(pstVpssRegs,  u32AddrOffset,  k_max_core_mcw);
    VPSS_Sys_SetKDifvcoreMcw(pstVpssRegs,  u32AddrOffset,  k_difvcore_mcw);
    VPSS_Sys_SetKDifhcoreMcw(pstVpssRegs,  u32AddrOffset,  k_difhcore_mcw);
    VPSS_Sys_SetK1MagWndMcw(pstVpssRegs,  u32AddrOffset,  k1_mag_wnd_mcw);
    VPSS_Sys_SetG0MagWndMcw(pstVpssRegs,  u32AddrOffset,  g0_mag_wnd_mcw);
    VPSS_Sys_SetK0MagWndMcw(pstVpssRegs,  u32AddrOffset,  k0_mag_wnd_mcw);
    VPSS_Sys_SetX0MagWndMcw(pstVpssRegs,  u32AddrOffset,  x0_mag_wnd_mcw);
    VPSS_Sys_SetKTbmagMcw(pstVpssRegs,  u32AddrOffset,  k_tbmag_mcw);
    VPSS_Sys_SetG0SadWndMcw(pstVpssRegs,  u32AddrOffset,  g0_sad_wnd_mcw);
    VPSS_Sys_SetK0SadWndMcw(pstVpssRegs,  u32AddrOffset,  k0_sad_wnd_mcw);
    VPSS_Sys_SetX0SadWndMcw(pstVpssRegs,  u32AddrOffset,  x0_sad_wnd_mcw);
    VPSS_Sys_SetG1MagWndMcw(pstVpssRegs,  u32AddrOffset,  g1_mag_wnd_mcw);
    VPSS_Sys_SetG1SadWndMcw(pstVpssRegs,  u32AddrOffset,  g1_sad_wnd_mcw);
    VPSS_Sys_SetK1SadWndMcw(pstVpssRegs,  u32AddrOffset,  k1_sad_wnd_mcw);
    VPSS_Sys_SetBHvdifDw(pstVpssRegs,  u32AddrOffset,  b_hvdif_dw);
    VPSS_Sys_SetBBhvdifDw(pstVpssRegs,  u32AddrOffset,  b_bhvdif_dw);
    VPSS_Sys_SetKBhvdifDw(pstVpssRegs,  u32AddrOffset,  k_bhvdif_dw);
    VPSS_Sys_SetCoreBhvdifDw(pstVpssRegs,  u32AddrOffset,  core_bhvdif_dw);
    VPSS_Sys_SetGainLpfDw(pstVpssRegs,  u32AddrOffset,  gain_lpf_dw);
    VPSS_Sys_SetKMaxHvdifDw(pstVpssRegs,  u32AddrOffset,  k_max_hvdif_dw);
    VPSS_Sys_SetBMvDw(pstVpssRegs,  u32AddrOffset,  b_mv_dw);
    VPSS_Sys_SetCoreMvDw(pstVpssRegs,  u32AddrOffset,  core_mv_dw);
    VPSS_Sys_SetKDifvDw(pstVpssRegs,  u32AddrOffset,  k_difv_dw);
    VPSS_Sys_SetCoreHvdifDw(pstVpssRegs,  u32AddrOffset,  core_hvdif_dw);
    VPSS_Sys_SetK1HvdifDw(pstVpssRegs,  u32AddrOffset,  k1_hvdif_dw);
    VPSS_Sys_SetG0HvdifDw(pstVpssRegs,  u32AddrOffset,  g0_hvdif_dw);
    VPSS_Sys_SetK0HvdifDw(pstVpssRegs,  u32AddrOffset,  k0_hvdif_dw);
    VPSS_Sys_SetX0HvdifDw(pstVpssRegs,  u32AddrOffset,  x0_hvdif_dw);
    VPSS_Sys_SetK1MvDw(pstVpssRegs,  u32AddrOffset,  k1_mv_dw);
    VPSS_Sys_SetG0MvDw(pstVpssRegs,  u32AddrOffset,  g0_mv_dw);
    VPSS_Sys_SetK0MvDw(pstVpssRegs,  u32AddrOffset,  k0_mv_dw);
    VPSS_Sys_SetX0MvDw(pstVpssRegs,  u32AddrOffset,  x0_mv_dw);
    VPSS_Sys_SetK1MtDw(pstVpssRegs,  u32AddrOffset,  k1_mt_dw);
    VPSS_Sys_SetG0MtDw(pstVpssRegs,  u32AddrOffset,  g0_mt_dw);
    VPSS_Sys_SetK0MtDw(pstVpssRegs,  u32AddrOffset,  k0_mt_dw);
    VPSS_Sys_SetX0MtDw(pstVpssRegs,  u32AddrOffset,  x0_mt_dw);
    VPSS_Sys_SetBMtDw(pstVpssRegs,  u32AddrOffset,  b_mt_dw);
    VPSS_Sys_SetK1MvMt(pstVpssRegs,  u32AddrOffset,  k1_mv_mt);
    VPSS_Sys_SetX0MvMt(pstVpssRegs,  u32AddrOffset,  x0_mv_mt);
    VPSS_Sys_SetG0MvMt(pstVpssRegs,  u32AddrOffset,  g0_mv_mt);
    VPSS_Sys_SetMclpfMode(pstVpssRegs,  u32AddrOffset,  mclpf_mode);
    VPSS_Sys_SetKPxlmagMcw(pstVpssRegs,  u32AddrOffset,  k_pxlmag_mcw);
    VPSS_Sys_SetXPxlmagMcw(pstVpssRegs,  u32AddrOffset,  x_pxlmag_mcw);
    VPSS_Sys_SetRsPxlmagMcw(pstVpssRegs,  u32AddrOffset,  rs_pxlmag_mcw);
    VPSS_Sys_SetGainMclpfh(pstVpssRegs,  u32AddrOffset,  gain_mclpfh);
    VPSS_Sys_SetGainDnMclpfv(pstVpssRegs,  u32AddrOffset,  gain_dn_mclpfv);
    VPSS_Sys_SetGainUpMclpfv(pstVpssRegs,  u32AddrOffset,  gain_up_mclpfv);
    VPSS_Sys_SetGPxlmagMcw(pstVpssRegs,  u32AddrOffset,  g_pxlmag_mcw);
    VPSS_Sys_SetKCVertw(pstVpssRegs,  u32AddrOffset,  k_c_vertw);
    VPSS_Sys_SetKYVertw(pstVpssRegs,  u32AddrOffset,  k_y_vertw);
    //VPSS_Sys_SetKFstmtMc(pstVpssRegs,  u32AddrOffset,  k_fstmt_mc);
    //VPSS_Sys_SetXFstmtMc(pstVpssRegs,  u32AddrOffset,  x_fstmt_mc);
    //VPSS_Sys_SetK1MvMc(pstVpssRegs,  u32AddrOffset,  k1_mv_mc);
    //VPSS_Sys_SetX0MvMc(pstVpssRegs,  u32AddrOffset,  x0_mv_mc);
    VPSS_Sys_SetBdvMcpos(pstVpssRegs,  u32AddrOffset,  bdv_mcpos);
    VPSS_Sys_SetBdhMcpos(pstVpssRegs,  u32AddrOffset,  bdh_mcpos);
    VPSS_Sys_SetKDelta(pstVpssRegs,  u32AddrOffset,  k_delta);
    //VPSS_Sys_SetKHfcoreMc(pstVpssRegs,  u32AddrOffset,  k_hfcore_mc);
    //VPSS_Sys_SetXHfcoreMc(pstVpssRegs,  u32AddrOffset,  x_hfcore_mc);
    //VPSS_Sys_SetGSlmtMc(pstVpssRegs,  u32AddrOffset,  g_slmt_mc);
    //VPSS_Sys_SetKSlmtMc(pstVpssRegs,  u32AddrOffset,  k_slmt_mc);
    //VPSS_Sys_SetXSlmtMc(pstVpssRegs,  u32AddrOffset,  x_slmt_mc);
    //VPSS_Sys_SetGFstmtMc(pstVpssRegs,  u32AddrOffset,  g_fstmt_mc);
    VPSS_Sys_SetR0Mc(pstVpssRegs,  u32AddrOffset,  r0_mc);
    VPSS_Sys_SetC0Mc(pstVpssRegs,  u32AddrOffset,  c0_mc);
    //VPSS_Sys_SetGHfcoreMc(pstVpssRegs,  u32AddrOffset,  g_hfcore_mc);
    VPSS_Sys_SetMcmvrange(pstVpssRegs,  u32AddrOffset,  mcmvrange);
    VPSS_Sys_SetR1Mc(pstVpssRegs,  u32AddrOffset,  r1_mc);
    VPSS_Sys_SetC1Mc(pstVpssRegs,  u32AddrOffset,  c1_mc);
    VPSS_Sys_SetKFrcountMc(pstVpssRegs,  u32AddrOffset,  k_frcount_mc);
    VPSS_Sys_SetXFrcountMc(pstVpssRegs,  u32AddrOffset,  x_frcount_mc);
    VPSS_Sys_SetScenechangeMc(pstVpssRegs,  u32AddrOffset,  scenechange_mc);
    //VPSS_Sys_SetMcendc(pstVpssRegs,  u32AddrOffset,  mcendc);
    //VPSS_Sys_SetMcendr(pstVpssRegs,  u32AddrOffset,  mcendr);
    //VPSS_Sys_SetMcstartc(pstVpssRegs,  u32AddrOffset,  mcstartc);
    //VPSS_Sys_SetMcstartr(pstVpssRegs,  u32AddrOffset,  mcstartr);
    //VPSS_Sys_SetMovegain(pstVpssRegs,  u32AddrOffset,  movegain);
    //VPSS_Sys_SetMovecorig(pstVpssRegs,  u32AddrOffset,  movecorig);
    //VPSS_Sys_SetMovethdl(pstVpssRegs,  u32AddrOffset,  movethdl);
    //VPSS_Sys_SetMovethdh(pstVpssRegs,  u32AddrOffset,  movethdh);
    VPSS_Sys_SetMcNumtBlden(pstVpssRegs,  u32AddrOffset,  mc_numt_blden);
    VPSS_Sys_SetNumtGain(pstVpssRegs,  u32AddrOffset,  numt_gain);
    VPSS_Sys_SetNumtCoring(pstVpssRegs,  u32AddrOffset,  numt_coring);
    VPSS_Sys_SetNumtLpfEn(pstVpssRegs,  u32AddrOffset,  numt_lpf_en);
    //VPSS_Sys_SetK1Hw(pstVpssRegs,  u32AddrOffset,  k1_hw);
    //VPSS_Sys_SetK0Hw(pstVpssRegs,  u32AddrOffset,  k0_hw);
    //VPSS_Sys_SetCoreHfvline(pstVpssRegs,  u32AddrOffset,  core_hfvline);
    //VPSS_Sys_SetK1Hfvline(pstVpssRegs,  u32AddrOffset,  k1_hfvline);
    //VPSS_Sys_SetK0Hfvline(pstVpssRegs,  u32AddrOffset,  k0_hfvline);
    VPSS_Sys_SetCoreRglsw(pstVpssRegs,  u32AddrOffset,  core_rglsw);
    //VPSS_Sys_SetGDifcoreMcw(pstVpssRegs,  u32AddrOffset,  g_difcore_mcw);
    //VPSS_Sys_SetSubpixMcEn(pstVpssRegs,  u32AddrOffset,  subpix_mc_en);
    //VPSS_Sys_SetCore1Hw(pstVpssRegs,  u32AddrOffset,  core1_hw);
    //VPSS_Sys_SetKCore0Hw(pstVpssRegs,  u32AddrOffset,  k_core0_hw);
    //VPSS_Sys_SetBCore0Hw(pstVpssRegs,  u32AddrOffset,  b_core0_hw);
    //VPSS_Sys_SetGHw(pstVpssRegs,  u32AddrOffset,  g_hw);
    //VPSS_Sys_SetG0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  g0_sadr_wnd_mcw);
    //VPSS_Sys_SetK0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  k0_sadr_wnd_mcw);
    //VPSS_Sys_SetX0SadrWndMcw(pstVpssRegs,  u32AddrOffset,  x0_sadr_wnd_mcw);
    //VPSS_Sys_SetRpK1SadWndMcw(pstVpssRegs,  u32AddrOffset,  rp_k1_sad_wnd_mcw);
    //VPSS_Sys_SetRpK1MagWndMcw(pstVpssRegs,  u32AddrOffset,  rp_k1_mag_wnd_mcw);
    VPSS_Sys_SetThCurBlksad(pstVpssRegs,  u32AddrOffset,  th_cur_blksad);
    //VPSS_Sys_SetKMcdifvMcw(pstVpssRegs,  u32AddrOffset,  k_mcdifv_mcw);
    //VPSS_Sys_SetKP1cfdifhMcw(pstVpssRegs,  u32AddrOffset,  k_p1cfdifh_mcw);
    //VPSS_Sys_SetG1SadrWndMcw(pstVpssRegs,  u32AddrOffset,  g1_sadr_wnd_mcw);
    //VPSS_Sys_SetK1SadrWndMcw(pstVpssRegs,  u32AddrOffset,  k1_sadr_wnd_mcw);
    VPSS_Sys_SetThCurBlkmotion(pstVpssRegs,  u32AddrOffset,  th_cur_blkmotion);
    VPSS_Sys_SetThlNeighBlksad(pstVpssRegs,  u32AddrOffset,  thl_neigh_blksad);
    VPSS_Sys_SetThhNeighBlksad(pstVpssRegs,  u32AddrOffset,  thh_neigh_blksad);
    //VPSS_Sys_SetRpDifmvxthRgmv(pstVpssRegs,  u32AddrOffset,  rp_difmvxth_rgmv);
    //VPSS_Sys_SetRpMvxthRgmv(pstVpssRegs,  u32AddrOffset,  rp_mvxth_rgmv);
    //VPSS_Sys_SetRpcounterth(pstVpssRegs,  u32AddrOffset,  rpcounterth);
    //VPSS_Sys_SetKRpcounter(pstVpssRegs,  u32AddrOffset,  k_rpcounter);
    VPSS_Sys_SetBlkmvUpdateEn(pstVpssRegs,  u32AddrOffset,  blkmv_update_en);
    VPSS_Sys_SetThRgmvMag(pstVpssRegs,  u32AddrOffset,  th_rgmv_mag);
    //VPSS_Sys_SetRpMagthRgmv(pstVpssRegs,  u32AddrOffset,  rp_magth_rgmv);
    //VPSS_Sys_SetRpSadthRgmv(pstVpssRegs,  u32AddrOffset,  rp_sadth_rgmv);
    //VPSS_Sys_SetRpDifsadthRgmv(pstVpssRegs,  u32AddrOffset,  rp_difsadth_rgmv);
    //VPSS_Sys_SetDifvtMode(pstVpssRegs,  u32AddrOffset,  difvt_mode);
    //VPSS_Sys_SetRpEn(pstVpssRegs,  u32AddrOffset,  rp_en);
    VPSS_Sys_SetSubmvSadchkEn(pstVpssRegs,  u32AddrOffset,  submv_sadchk_en);
    //VPSS_Sys_SetK1TpdifRgsad(pstVpssRegs,  u32AddrOffset,  k1_tpdif_rgsad);
    //VPSS_Sys_SetRpDifsadthTb(pstVpssRegs,  u32AddrOffset,  rp_difsadth_tb);
    //VPSS_Sys_SetRpDifmvxthSp(pstVpssRegs,  u32AddrOffset,  rp_difmvxth_sp);
    VPSS_Sys_SetCntlut5(pstVpssRegs,  u32AddrOffset,  cntlut_5);
    VPSS_Sys_SetCntlut4(pstVpssRegs,  u32AddrOffset,  cntlut_4);
    VPSS_Sys_SetCntlut3(pstVpssRegs,  u32AddrOffset,  cntlut_3);
    VPSS_Sys_SetCntlut2(pstVpssRegs,  u32AddrOffset,  cntlut_2);
    VPSS_Sys_SetCntlut1(pstVpssRegs,  u32AddrOffset,  cntlut_1);
    VPSS_Sys_SetCntlut0(pstVpssRegs,  u32AddrOffset,  cntlut_0);
    VPSS_Sys_SetMcwScntGain(pstVpssRegs,  u32AddrOffset,  mcw_scnt_gain);
    VPSS_Sys_SetMcwScntEn(pstVpssRegs,  u32AddrOffset,  mcw_scnt_en);
    VPSS_Sys_SetMcMtshift(pstVpssRegs,  u32AddrOffset,  mc_mtshift);
    VPSS_Sys_SetCntlut8(pstVpssRegs,  u32AddrOffset,  cntlut_8);
    VPSS_Sys_SetCntlut7(pstVpssRegs,  u32AddrOffset,  cntlut_7);
    VPSS_Sys_SetCntlut6(pstVpssRegs,  u32AddrOffset,  cntlut_6);
    VPSS_Sys_SetDemoBorder(pstVpssRegs,  u32AddrOffset,  demo_border);
    VPSS_Sys_SetDemoModeR(pstVpssRegs,  u32AddrOffset,  demo_mode_r);
    VPSS_Sys_SetDemoModeL(pstVpssRegs,  u32AddrOffset,  demo_mode_l);
    VPSS_Sys_SetDemoEn(pstVpssRegs,  u32AddrOffset,  demo_en);
}
#endif

