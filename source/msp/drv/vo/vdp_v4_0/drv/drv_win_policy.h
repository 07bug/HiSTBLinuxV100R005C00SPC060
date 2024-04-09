#ifndef __WIN_POLICY_H_
#define __WIN_POLICY_H_

#include "drv_display.h"

#include "drv_window.h"
#include "drv_win_policy.h"
#include "drv_win_priv.h"
#include "hi_drv_sys.h"
#include "hi_drv_stat.h"
#include "drv_vdec_ext.h"
#include "drv_disp_hal.h"
#include "drv_disp_alg_service.h"
#include "hi_drv_module.h"
#include "drv_pq_ext.h"

#define IGNORE_INTERMEDIARect   0x0
#define INVALID_INTERMEDIARect  0xFFFF
#define MUTE_INTERMEDIARect     0xFFFE

typedef struct  hiOutAlign
{
    HI_U16 u16WinOutRectXAlign;
    HI_U16 u16WinOutRectYAlign;
    HI_U16 u16WinOutRectWAlign;
    HI_U16 u16WinOutRectHAlign;
}HI_OUT_ALIGN_S;

HI_BOOL  Win_CheckTnrLocateOnVdp(WINDOW_S *pstWin,
                                 HI_RECT_S *pstFrameSize);

HI_S32 Win_Revise_OutOfScreenWin_OutRect(HI_RECT_S *pstInRect,
                        HI_RECT_S *pstVideoRect, HI_RECT_S *pstDispRect,
                        HI_RECT_S *pstScreen,
                        HI_DRV_DISP_OFFSET_S *pstOffsetRect,
                        WIN_HAL_PARA_S *pstLayerPara);



HI_VOID WinOutRectAlign(HI_RECT_S *pstRectAlign);
HI_VOID WinInRectAlign(HI_RECT_S *pstRectAlign,HI_U32 u32LayerNO);
HI_S32 WinParamAlignDown(HI_S32 s32X, HI_U32 u32A);
HI_S32 WinParamAlignUp(HI_S32 s32X, HI_U32 u32A);
HI_VOID Win_Policy_GetPQDegradingConfigFromTEE(HI_BOOL bTEEMode,
                                                                HI_RECT_S *pstInRect,
                                                                HI_RECT_S *pstOutRect,
                                                                HI_U32    u32VideoLayer,
                                                                HI_RECT_S *pstFrameIntermediateRect,
                                                                HI_BOOL   *pbHdcpDegradePQ,
                                                                HI_RECT_S *pstHdcpIntermediateRect);

HI_S32 WIN_POLICY_GetOutputTypeAndEngine(HI_HANDLE hWin,
                                         HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                                      HI_DRV_DISP_OUT_TYPE_E    *penOutputType,
                                                      HI_DRV_DISP_XDR_ENGINE_E  *penXdrEngine);

HI_S32 WIN_POLICY_MixStreamProcess(WIN_XDR_FRAME_S *pstXdrFrame,
                               HI_DRV_COLOR_SPACE_E enInColorSpace,
                               HI_DRV_COLOR_SPACE_E *penOutColorSpace);

//98cv200 capture scene, hdr frame need vpss processed as sdr frame.
HI_VOID WIN_POLICY_ReviseFrameHdrType(HI_DRV_VIDEO_FRAME_S *pu8TempMem);

HI_VOID WIN_POLICY_RwzbProcess(HI_U32 u32Fidelity,HI_BOOL *bRWZB);

#endif




