#include "vdp_hal_comm.h"
#include "vdp_hal_ip_cycbuf.h"
extern volatile S_VDP_REGS_TYPE* pVdpReg;

HI_VOID VDP_CYCBUF_SetVid0BindEn( HI_U32 offset, HI_U32 vid0_bind_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.vid0_bind_en = vid0_bind_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetVid0SuccEn( HI_U32 offset, HI_U32 vid0_succ_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.vid0_succ_en = vid0_succ_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetVid1BindEn( HI_U32 offset, HI_U32 vid1_bind_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.vid1_bind_en = vid1_bind_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetVid1SuccEn( HI_U32 offset, HI_U32 vid1_succ_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.vid1_succ_en = vid1_succ_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetGfxBindEn( HI_U32 offset, HI_U32 gfx_bind_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.gfx_bind_en = gfx_bind_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetGfxSuccEn( HI_U32 offset, HI_U32 gfx_succ_en)
{
	U_HWLD_TOP_CTRL HWLD_TOP_CTRL;

	HWLD_TOP_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)));
	HWLD_TOP_CTRL.bits.gfx_succ_en = gfx_succ_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_CTRL.u32) + (offset/4)),HWLD_TOP_CTRL.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetRegup( HI_U32 offset, HI_U32 regup)
{
	U_HWLD_TOP_REGUP HWLD_TOP_REGUP;

	HWLD_TOP_REGUP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_REGUP.u32) + (offset/4)));
	HWLD_TOP_REGUP.bits.regup = regup;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_REGUP.u32) + (offset/4)),HWLD_TOP_REGUP.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetSmmuBypass( HI_U32 offset, HI_U32 smmu_bypass)
{
	U_HWLD_TOP_SMMU_BYPASS HWLD_TOP_SMMU_BYPASS;

	HWLD_TOP_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_SMMU_BYPASS.u32) + (offset/4)));
	HWLD_TOP_SMMU_BYPASS.bits.smmu_bypass = smmu_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_SMMU_BYPASS.u32) + (offset/4)),HWLD_TOP_SMMU_BYPASS.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDebugSta0( HI_U32 offset, HI_U32 debug_sta0)
{
	U_HWLD_TOP_DEBUG_STA0 HWLD_TOP_DEBUG_STA0;

	HWLD_TOP_DEBUG_STA0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA0.u32) + (offset/4)));
	HWLD_TOP_DEBUG_STA0.bits.debug_sta0 = debug_sta0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA0.u32) + (offset/4)),HWLD_TOP_DEBUG_STA0.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDebugSta1( HI_U32 offset, HI_U32 debug_sta1)
{
	U_HWLD_TOP_DEBUG_STA1 HWLD_TOP_DEBUG_STA1;

	HWLD_TOP_DEBUG_STA1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA1.u32) + (offset/4)));
	HWLD_TOP_DEBUG_STA1.bits.debug_sta1 = debug_sta1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA1.u32) + (offset/4)),HWLD_TOP_DEBUG_STA1.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDebugSta2( HI_U32 offset, HI_U32 debug_sta2)
{
	U_HWLD_TOP_DEBUG_STA2 HWLD_TOP_DEBUG_STA2;

	HWLD_TOP_DEBUG_STA2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA2.u32) + (offset/4)));
	HWLD_TOP_DEBUG_STA2.bits.debug_sta2 = debug_sta2;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA2.u32) + (offset/4)),HWLD_TOP_DEBUG_STA2.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDebugSta3( HI_U32 offset, HI_U32 debug_sta3)
{
	U_HWLD_TOP_DEBUG_STA3 HWLD_TOP_DEBUG_STA3;

	HWLD_TOP_DEBUG_STA3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA3.u32) + (offset/4)));
	HWLD_TOP_DEBUG_STA3.bits.debug_sta3 = debug_sta3;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->HWLD_TOP_DEBUG_STA3.u32) + (offset/4)),HWLD_TOP_DEBUG_STA3.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetFrmChangeMode( HI_U32 offset, HI_U32 frm_change_mode)
{
	U_VID_DTV_MODE VID_DTV_MODE;

	VID_DTV_MODE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_MODE.u32) + (offset/4)));
	VID_DTV_MODE.bits.frm_change_mode = frm_change_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_MODE.u32) + (offset/4)),VID_DTV_MODE.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvMode( HI_U32 offset, HI_U32 dtv_mode)
{
	U_VID_DTV_MODE VID_DTV_MODE;

	VID_DTV_MODE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_MODE.u32) + (offset/4)));
	VID_DTV_MODE.bits.dtv_mode = dtv_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_MODE.u32) + (offset/4)),VID_DTV_MODE.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetResetMode( HI_U32 offset, HI_U32 reset_mode)
{
	U_VID_DTV_MODE_IMG VID_DTV_MODE_IMG;

	VID_DTV_MODE_IMG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_MODE_IMG.u32) + (offset/4)));
	VID_DTV_MODE_IMG.bits.reset_mode = reset_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_MODE_IMG.u32) + (offset/4)),VID_DTV_MODE_IMG.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetResetEn( HI_U32 offset, HI_U32 reset_en)
{
	U_VID_DTV_MODE_IMG VID_DTV_MODE_IMG;

	VID_DTV_MODE_IMG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_MODE_IMG.u32) + (offset/4)));
	VID_DTV_MODE_IMG.bits.reset_en = reset_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_MODE_IMG.u32) + (offset/4)),VID_DTV_MODE_IMG.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetBurstMask( HI_U32 offset, HI_U32 burst_mask)
{
	U_VID_DTV_GLB_FRM_INFO VID_DTV_GLB_FRM_INFO;

	VID_DTV_GLB_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)));
	VID_DTV_GLB_FRM_INFO.bits.burst_mask = burst_mask;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)),VID_DTV_GLB_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetHburstNum( HI_U32 offset, HI_U32 hburst_num)
{
	U_VID_DTV_GLB_FRM_INFO VID_DTV_GLB_FRM_INFO;

	VID_DTV_GLB_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)));
	VID_DTV_GLB_FRM_INFO.bits.hburst_num = hburst_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)),VID_DTV_GLB_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetLburstNum( HI_U32 offset, HI_U32 lburst_num)
{
	U_VID_DTV_GLB_FRM_INFO VID_DTV_GLB_FRM_INFO;

	VID_DTV_GLB_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)));
	VID_DTV_GLB_FRM_INFO.bits.lburst_num = lburst_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_GLB_FRM_INFO.u32) + (offset/4)),VID_DTV_GLB_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetWriteReady( HI_U32 offset, HI_U32 write_ready)
{
	U_VID_DTV_LOC_FRM_INFO_READY VID_DTV_LOC_FRM_INFO_READY;

	VID_DTV_LOC_FRM_INFO_READY.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO_READY.u32) + (offset/4)));
	VID_DTV_LOC_FRM_INFO_READY.bits.write_ready = write_ready;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO_READY.u32) + (offset/4)),VID_DTV_LOC_FRM_INFO_READY.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetFirstFieldSel( HI_U32 offset, HI_U32 first_field_sel)
{
	U_VID_DTV_LOC_FRM_INFO VID_DTV_LOC_FRM_INFO;

	VID_DTV_LOC_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)));
	VID_DTV_LOC_FRM_INFO.bits.first_field_sel = first_field_sel;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)),VID_DTV_LOC_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetBtmDispNum( HI_U32 offset, HI_U32 btm_disp_num)
{
	U_VID_DTV_LOC_FRM_INFO VID_DTV_LOC_FRM_INFO;

	VID_DTV_LOC_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)));
	VID_DTV_LOC_FRM_INFO.bits.btm_disp_num = btm_disp_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)),VID_DTV_LOC_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetTopDispNum( HI_U32 offset, HI_U32 top_disp_num)
{
	U_VID_DTV_LOC_FRM_INFO VID_DTV_LOC_FRM_INFO;

	VID_DTV_LOC_FRM_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)));
	VID_DTV_LOC_FRM_INFO.bits.top_disp_num = top_disp_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO.u32) + (offset/4)),VID_DTV_LOC_FRM_INFO.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvCfgAddr( HI_U32 offset, HI_U32 dtv_cfg_addr)
{
	U_VID_DTV_LOC_FRM_INFO1 VID_DTV_LOC_FRM_INFO1;

	VID_DTV_LOC_FRM_INFO1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO1.u32) + (offset/4)));
	VID_DTV_LOC_FRM_INFO1.bits.dtv_cfg_addr = dtv_cfg_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_LOC_FRM_INFO1.u32) + (offset/4)),VID_DTV_LOC_FRM_INFO1.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvBackAddr( HI_U32 offset, HI_U32 dtv_back_addr)
{
	U_VID_DTV_BACK_ADDR VID_DTV_BACK_ADDR;

	VID_DTV_BACK_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_ADDR.u32) + (offset/4)));
	VID_DTV_BACK_ADDR.bits.dtv_back_addr = dtv_back_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_ADDR.u32) + (offset/4)),VID_DTV_BACK_ADDR.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvBackPassword( HI_U32 offset, HI_U32 dtv_back_password)
{
	U_VID_DTV_BACK_PSW VID_DTV_BACK_PSW;

	VID_DTV_BACK_PSW.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_PSW.u32) + (offset/4)));
	VID_DTV_BACK_PSW.bits.dtv_back_password = dtv_back_password;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_PSW.u32) + (offset/4)),VID_DTV_BACK_PSW.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetMuteClr( HI_U32 offset, HI_U32 mute_clr)
{
	U_VID_DTV_CFG_READY VID_DTV_CFG_READY;

	VID_DTV_CFG_READY.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_CFG_READY.u32) + (offset/4)));
	VID_DTV_CFG_READY.bits.mute_clr = mute_clr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_CFG_READY.u32) + (offset/4)),VID_DTV_CFG_READY.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetCfgReady( HI_U32 offset, HI_U32 cfg_ready)
{
	U_VID_DTV_CFG_READY VID_DTV_CFG_READY;

	VID_DTV_CFG_READY.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_CFG_READY.u32) + (offset/4)));
	VID_DTV_CFG_READY.bits.cfg_ready = cfg_ready;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_CFG_READY.u32) + (offset/4)),VID_DTV_CFG_READY.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvChangeAddr( HI_U32 offset, HI_U32 dtv_change_addr)
{
	U_VID_DTV_CHANGE_ADDR VID_DTV_CHANGE_ADDR;

	VID_DTV_CHANGE_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_CHANGE_ADDR.u32) + (offset/4)));
	VID_DTV_CHANGE_ADDR.bits.dtv_change_addr = dtv_change_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_CHANGE_ADDR.u32) + (offset/4)),VID_DTV_CHANGE_ADDR.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDtvDispAddr( HI_U32 offset, HI_U32 dtv_disp_addr)
{
	U_VID_DTV_DISP_ADDR VID_DTV_DISP_ADDR;

	VID_DTV_DISP_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DISP_ADDR.u32) + (offset/4)));
	VID_DTV_DISP_ADDR.bits.dtv_disp_addr = dtv_disp_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DISP_ADDR.u32) + (offset/4)),VID_DTV_DISP_ADDR.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetBackNum( HI_U32 offset, HI_U32 back_num)
{
	U_VID_DTV_BACK_NUM VID_DTV_BACK_NUM;

	VID_DTV_BACK_NUM.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_NUM.u32) + (offset/4)));
	VID_DTV_BACK_NUM.bits.back_num = back_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_NUM.u32) + (offset/4)),VID_DTV_BACK_NUM.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetBackErr( HI_U32 offset, HI_U32 back_err)
{
	U_VID_DTV_ERR_STA VID_DTV_ERR_STA;

	VID_DTV_ERR_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)));
	VID_DTV_ERR_STA.bits.back_err = back_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)),VID_DTV_ERR_STA.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetSendErr( HI_U32 offset, HI_U32 send_err)
{
	U_VID_DTV_ERR_STA VID_DTV_ERR_STA;

	VID_DTV_ERR_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)));
	VID_DTV_ERR_STA.bits.send_err = send_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)),VID_DTV_ERR_STA.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDebugClr( HI_U32 offset, HI_U32 debug_clr)
{
	U_VID_DTV_DEBUG_CLR VID_DTV_DEBUG_CLR;

	VID_DTV_DEBUG_CLR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG_CLR.u32) + (offset/4)));
	VID_DTV_DEBUG_CLR.bits.debug_clr = debug_clr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG_CLR.u32) + (offset/4)),VID_DTV_DEBUG_CLR.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDispCnt( HI_U32 offset, HI_U32 disp_cnt)
{
	U_VID_DTV_DEBUG1 VID_DTV_DEBUG1;

	VID_DTV_DEBUG1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG1.u32) + (offset/4)));
	VID_DTV_DEBUG1.bits.disp_cnt = disp_cnt;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG1.u32) + (offset/4)),VID_DTV_DEBUG1.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetBackFifoSta( HI_U32 offset, HI_U32 back_fifo_sta)
{
	U_VID_DTV_DEBUG2 VID_DTV_DEBUG2;

	VID_DTV_DEBUG2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)));
	VID_DTV_DEBUG2.bits.back_fifo_sta = back_fifo_sta;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)),VID_DTV_DEBUG2.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetDispFifoSta( HI_U32 offset, HI_U32 disp_fifo_sta)
{
	U_VID_DTV_DEBUG2 VID_DTV_DEBUG2;

	VID_DTV_DEBUG2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)));
	VID_DTV_DEBUG2.bits.disp_fifo_sta = disp_fifo_sta;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)),VID_DTV_DEBUG2.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetUnderloadSta( HI_U32 offset, HI_U32 underload_sta)
{
	U_VID_DTV_DEBUG3 VID_DTV_DEBUG3;

	VID_DTV_DEBUG3.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG3.u32) + (offset/4)));
	VID_DTV_DEBUG3.bits.underload_sta = underload_sta;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG3.u32) + (offset/4)),VID_DTV_DEBUG3.u32);

	return ;
}


HI_VOID VDP_CYCBUF_SetUnderloadCnt( HI_U32 offset, HI_U32 underload_cnt)
{
	U_VID_DTV_DEBUG4 VID_DTV_DEBUG4;

	VID_DTV_DEBUG4.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG4.u32) + (offset/4)));
	VID_DTV_DEBUG4.bits.underload_cnt = underload_cnt;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG4.u32) + (offset/4)),VID_DTV_DEBUG4.u32);

	return ;
}


HI_U32  VDP_CYCBUF_GetDtvBackAddr( HI_U32 offset)
{
	U_VID_DTV_BACK_ADDR VID_DTV_BACK_ADDR;

	VID_DTV_BACK_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_ADDR.u32) + (offset/4)));
	return VID_DTV_BACK_ADDR.bits.dtv_back_addr;
}


HI_U32  VDP_CYCBUF_GetDtvChangeAddr( HI_U32 offset)
{
	U_VID_DTV_CHANGE_ADDR VID_DTV_CHANGE_ADDR;

	VID_DTV_CHANGE_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_CHANGE_ADDR.u32) + (offset/4)));

	return VID_DTV_CHANGE_ADDR.bits.dtv_change_addr;
}


HI_U32  VDP_CYCBUF_GetDtvDispAddr( HI_U32 offset)
{
	U_VID_DTV_DISP_ADDR VID_DTV_DISP_ADDR;

	VID_DTV_DISP_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DISP_ADDR.u32) + (offset/4)));

	return VID_DTV_DISP_ADDR.bits.dtv_disp_addr;
}


HI_U32  VDP_CYCBUF_GetBackNum( HI_U32 offset)
{
	U_VID_DTV_BACK_NUM VID_DTV_BACK_NUM;

	VID_DTV_BACK_NUM.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_BACK_NUM.u32) + (offset/4)));

	return VID_DTV_BACK_NUM.bits.back_num;
}


HI_U32  VDP_CYCBUF_GetBackErr( HI_U32 offset)
{
	U_VID_DTV_ERR_STA VID_DTV_ERR_STA;

	VID_DTV_ERR_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)));

	return VID_DTV_ERR_STA.bits.back_err;
}


HI_U32  VDP_CYCBUF_GetSendErr( HI_U32 offset)
{
	U_VID_DTV_ERR_STA VID_DTV_ERR_STA;

	VID_DTV_ERR_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_ERR_STA.u32) + (offset/4)));

	return VID_DTV_ERR_STA.bits.send_err;
}


HI_U32  VDP_CYCBUF_GetDispCnt( HI_U32 offset)
{
	U_VID_DTV_DEBUG1 VID_DTV_DEBUG1;

	VID_DTV_DEBUG1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG1.u32) + (offset/4)));

	return VID_DTV_DEBUG1.bits.disp_cnt;
}


HI_U32  VDP_CYCBUF_GetBackFifoSta( HI_U32 offset)
{
	U_VID_DTV_DEBUG2 VID_DTV_DEBUG2;

	VID_DTV_DEBUG2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)));

	return VID_DTV_DEBUG2.bits.back_fifo_sta;
}


HI_U32  VDP_CYCBUF_GetDispFifoSta( HI_U32 offset)
{
	U_VID_DTV_DEBUG2 VID_DTV_DEBUG2;

	VID_DTV_DEBUG2.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DTV_DEBUG2.u32) + (offset/4)));

	return VID_DTV_DEBUG2.bits.disp_fifo_sta;
}


