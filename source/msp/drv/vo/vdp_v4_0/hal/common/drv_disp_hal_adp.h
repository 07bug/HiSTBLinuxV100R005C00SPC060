#ifndef __DISP_HAL_ADP_H
#define __DISP_HAL_ADP_H
HI_S32 Get_FormatCfgPara(HI_U32 index, DISP_FMT_CFG_S *pstDispFormatParam);
#ifndef __DISP_PLATFORM_BOOT__
#include "drv_pq_ext.h"

HI_S32 Chip_Specific_WbcZmeFunc(HI_PQ_ZME_LAYER_E u32LayerId,
                                HI_PQ_ZME_PARA_IN_S *pstZmeI,
                                HI_U32     bFirlterEnable);
ISOGENY_MODE_E Chip_Specific_GetIsogenyMode(HI_VOID);
HI_VOID Chip_Specific_GetPixelRepeatTimesAccordingFmt(HI_DRV_DISPLAY_E enDisp,
        HI_DRV_DISP_FMT_E eFmt,
        HI_U32 *pu32PixelRepeatTimes);

#endif
HI_S32 Chip_Specific_Set3DMode(HI_DRV_DISPLAY_E eChn, HI_U32 u32DispId, DISP_FMT_CFG_S *pstCfg);
HI_S32 Chip_Specific_SetWbc3DInfo(DISP_WBC_E eWbc, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_RECT_S *in, HI_RECT_S *out);
HI_S32 Chip_Specific_ReviseWbcZmeInput(DISP_WBC_E eWbc, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_U32 *u32Width, HI_U32 *u32Height);
HI_S32 Chip_Specific_DispSetMSChnEnable(HI_U32 u32DispIdM, HI_U32 u32DispIdS, HI_U32 u32DelayMs, HI_BOOL bEnalbe);
HI_S32 Chip_Specific_SelectChannelPllSource(HI_DRV_DISPLAY_E eChn, HI_U32 uPllIndex);
HI_VOID Chip_Specific_GetHdmiVbiPolarity(HI_BOOL *pbVsyncPolarityInvert,
        HI_BOOL *pbHsyncPolarityInvert);
HI_VOID Chip_Specific_SetSyncInv(HI_U32 u32hd_id, VDP_DISP_INTF_E enIntf, VDP_DISP_SYNCINV_S enInv);

HI_VOID  Chip_Specific_DispSetPll(DISP_PLL_SOURCE_E enPllIndex, HI_U32 u32PllxReg0, HI_U32 u32PllxReg1);
HI_S32 Chip_Specific_CBM_MovTOP(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_LAYER_E enLayer);
HI_VOID Chip_Specific_DispSetChanClk(HI_DRV_DISPLAY_E eChn, DISP_FMT_CFG_S *pstCfg);
HI_S32 Chip_Specific_SetMixerBgColor(HI_DRV_DISPLAY_E eChn, VDP_BKG_S stBkg);
HI_VOID Chip_Specific_GetVersion(HI_DRV_DISP_VERSION_S *pVersion);

HI_S32 Chip_Specific_DISP_OpenClock(HI_VOID);
HI_S32 Chip_Specific_DISP_CloseClock(HI_VOID);
HI_S32 Chip_Specific_DISP_ConfigP2I(HI_U32 u32DispId, HI_BOOL bProgressive);

HI_S32 DISP_UpdateCustomFormatParam(const HI_DRV_DISP_TIMING_S *pstTiming, const REG_PARA_S* pstRegPara);
HI_S32 DISP_TimingFixSpreadSpectrum(HI_U32 u32PixClk, HI_U32 *pu32FixPixelDiv);

HI_S32 DISP_HAL_GetPortIntValidAndWbcLineNum(HI_BOOL *pbInterruptValid, HI_U32 *pu32WbcLineNum);

#endif
