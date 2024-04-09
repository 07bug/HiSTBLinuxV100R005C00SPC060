#include "vpss_hal_comm.h"
#include "vpss_hal_mac_ctrl.h"
#include "vpss_cbb_reg.h"

HI_VOID VPSS_MAC_SetDmaEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 dma_en)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.dma_en = dma_en;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetMaxReqLen(S_VPSS_REGS_TYPE *pstReg, HI_U32 max_req_len)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.max_req_len = max_req_len;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetMaxReqNum(S_VPSS_REGS_TYPE *pstReg, HI_U32 max_req_num)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.max_req_num = max_req_num;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetRotateAngle(S_VPSS_REGS_TYPE *pstReg, HI_U32 rotate_angle)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.rotate_angle = rotate_angle;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetRotateEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 rotate_en)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.rotate_en = rotate_en;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetImgProMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 img_pro_mode)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.img_pro_mode = img_pro_mode;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetProt(S_VPSS_REGS_TYPE *pstReg, HI_U32 prot)
{
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CHN_CFG_CTRL.u32)));
    VPSS_CHN_CFG_CTRL.bits.prot = prot;
    VPSS_RegWrite((&(pstReg->VPSS_CHN_CFG_CTRL.u32)), VPSS_CHN_CFG_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetSttWAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 stt_w_addr)
{
    U_VPSS_STT_W_ADDR_LOW VPSS_STT_W_ADDR_LOW;

    VPSS_STT_W_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_STT_W_ADDR_LOW.u32)));
    VPSS_STT_W_ADDR_LOW.bits.stt_w_addr = stt_w_addr;
    VPSS_RegWrite((&(pstReg->VPSS_STT_W_ADDR_LOW.u32)), VPSS_STT_W_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_MAC_SetCfRtunlInterval(S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_interval)
{
    U_VPSS_CF_RTUNL_CTRL VPSS_CF_RTUNL_CTRL;

    VPSS_CF_RTUNL_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)));
    VPSS_CF_RTUNL_CTRL.bits.cf_rtunl_interval = cf_rtunl_interval;
    VPSS_RegWrite((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)), VPSS_CF_RTUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetCfRtunlBypass(S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_bypass)
{
    U_VPSS_CF_RTUNL_CTRL VPSS_CF_RTUNL_CTRL;

    VPSS_CF_RTUNL_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)));
    VPSS_CF_RTUNL_CTRL.bits.cf_rtunl_bypass = cf_rtunl_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)), VPSS_CF_RTUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetCfRtunlEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_en)
{
    U_VPSS_CF_RTUNL_CTRL VPSS_CF_RTUNL_CTRL;

    VPSS_CF_RTUNL_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)));
    VPSS_CF_RTUNL_CTRL.bits.cf_rtunl_en = cf_rtunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_CF_RTUNL_CTRL.u32)), VPSS_CF_RTUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetCfRtunlAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_addr)
{
    U_VPSS_CF_RTUNL_ADDR_LOW VPSS_CF_RTUNL_ADDR_LOW;

    VPSS_CF_RTUNL_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_RTUNL_ADDR_LOW.u32)));
    VPSS_CF_RTUNL_ADDR_LOW.bits.cf_rtunl_addr = cf_rtunl_addr;
    VPSS_RegWrite((&(pstReg->VPSS_CF_RTUNL_ADDR_LOW.u32)), VPSS_CF_RTUNL_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_MAC_SetOut0WtunlMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_mode)
{
    U_VPSS_OUT0_WTUNL_CTRL VPSS_OUT0_WTUNL_CTRL;

    VPSS_OUT0_WTUNL_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_WTUNL_CTRL.u32)));
    VPSS_OUT0_WTUNL_CTRL.bits.out0_wtunl_mode = out0_wtunl_mode;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_WTUNL_CTRL.u32)), VPSS_OUT0_WTUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetOut0WtunlEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_en)
{
    U_VPSS_OUT0_WTUNL_CTRL VPSS_OUT0_WTUNL_CTRL;

    VPSS_OUT0_WTUNL_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_WTUNL_CTRL.u32)));
    VPSS_OUT0_WTUNL_CTRL.bits.out0_wtunl_en = out0_wtunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_WTUNL_CTRL.u32)), VPSS_OUT0_WTUNL_CTRL.u32);

    return ;
}


HI_VOID VPSS_MAC_SetOut0WtunlFinishLine(S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_finish_line)
{
    U_VPSS_OUT0_WTUNL_THD VPSS_OUT0_WTUNL_THD;

    VPSS_OUT0_WTUNL_THD.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_WTUNL_THD.u32)));
    VPSS_OUT0_WTUNL_THD.bits.out0_wtunl_finish_line = out0_wtunl_finish_line;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_WTUNL_THD.u32)), VPSS_OUT0_WTUNL_THD.u32);

    return ;
}


HI_VOID VPSS_MAC_SetOut0WtunlAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_addr)
{
    U_VPSS_OUT0_WTUNL_ADDR_LOW VPSS_OUT0_WTUNL_ADDR_LOW;

    VPSS_OUT0_WTUNL_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_WTUNL_ADDR_LOW.u32)));
    VPSS_OUT0_WTUNL_ADDR_LOW.bits.out0_wtunl_addr = out0_wtunl_addr;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_WTUNL_ADDR_LOW.u32)), VPSS_OUT0_WTUNL_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_MAC_SetPatBkgrndU(S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_bkgrnd_u)
{
    U_VPSS_TESTPATTERN VPSS_TESTPATTERN;

    VPSS_TESTPATTERN.u32 = VPSS_RegRead((&(pstReg->VPSS_TESTPATTERN.u32)));
    VPSS_TESTPATTERN.bits.pat_bkgrnd_u = pat_bkgrnd_u;
    VPSS_RegWrite((&(pstReg->VPSS_TESTPATTERN.u32)), VPSS_TESTPATTERN.u32);

    return ;
}


HI_VOID VPSS_MAC_SetPatBkgrndV(S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_bkgrnd_v)
{
    U_VPSS_TESTPATTERN VPSS_TESTPATTERN;

    VPSS_TESTPATTERN.u32 = VPSS_RegRead((&(pstReg->VPSS_TESTPATTERN.u32)));
    VPSS_TESTPATTERN.bits.pat_bkgrnd_v = pat_bkgrnd_v;
    VPSS_RegWrite((&(pstReg->VPSS_TESTPATTERN.u32)), VPSS_TESTPATTERN.u32);

    return ;
}


HI_VOID VPSS_MAC_SetPatDisWidth(S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_dis_width)
{
    U_VPSS_TESTPATTERN VPSS_TESTPATTERN;

    VPSS_TESTPATTERN.u32 = VPSS_RegRead((&(pstReg->VPSS_TESTPATTERN.u32)));
    VPSS_TESTPATTERN.bits.pat_dis_width = pat_dis_width;
    VPSS_RegWrite((&(pstReg->VPSS_TESTPATTERN.u32)), VPSS_TESTPATTERN.u32);

    return ;
}


HI_VOID VPSS_MAC_SetPatAngle(S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_angle)
{
    U_VPSS_TESTPATTERN VPSS_TESTPATTERN;

    VPSS_TESTPATTERN.u32 = VPSS_RegRead((&(pstReg->VPSS_TESTPATTERN.u32)));
    VPSS_TESTPATTERN.bits.pat_angle = pat_angle;
    VPSS_RegWrite((&(pstReg->VPSS_TESTPATTERN.u32)), VPSS_TESTPATTERN.u32);

    return ;
}


HI_VOID VPSS_MAC_SetTestPatEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 test_pat_en)
{
    U_VPSS_TESTPATTERN VPSS_TESTPATTERN;

    VPSS_TESTPATTERN.u32 = VPSS_RegRead((&(pstReg->VPSS_TESTPATTERN.u32)));
    VPSS_TESTPATTERN.bits.test_pat_en = test_pat_en;
    VPSS_RegWrite((&(pstReg->VPSS_TESTPATTERN.u32)), VPSS_TESTPATTERN.u32);

    return ;
}



