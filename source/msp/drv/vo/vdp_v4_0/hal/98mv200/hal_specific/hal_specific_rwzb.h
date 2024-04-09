#ifndef __VDP_RWZB_H_
#define __VDP_RWZB_H_

#include "drv_disp_com.h"

#ifdef HI_VO_VDAC_LC_CIRCUIT
#define  VDAC_DEFAULT_GAIN_TINYADJUST_MASK     0x1
#define     SCH_PHASE 0xba
#define     C_GAIN 0
#else

#define  VDAC_DEFAULT_GAIN_TINYADJUST_MASK  0x1
#define     SCH_PHASE 0xba
#define     C_GAIN 0
#endif

#define  VO_DAC_CTRL1_OTP_RESISTANCE   0x00004080
HI_U32 *VDP_Get_HDateSrc13Coef( HI_U32 u32Fmt);
HI_U32 *VDP_Get_SDateSrcCoef( HI_U32 Index);
HI_VOID VDP_Set_VDAC_GAIN(HI_U32 uVdac);
HI_VOID VDP_VDAC_SetCvbsAndYpbprDriveMode(HI_VOID);

#endif
