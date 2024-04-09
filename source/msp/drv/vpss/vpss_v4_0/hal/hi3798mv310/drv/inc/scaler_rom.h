/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
*******************************************************************************
  File Name     :
  Version       : Initial Draft
  Author        :
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "hi_type.h"
#ifndef __HI_SCALER_ROM_H__
#define __HI_SCALER_ROM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define PHASE 32
#define COEFF_BUTT (PHASE / 2 + 1)

#define SCALE_RATIO_BUTT 9
#define SCALE_TAP_BUTT 2

#define STEP_LSHFT 12
#define PHASE_SHFT  5
#define AVG_LSHFT   5

extern const int Blinear_Down2[2];
extern const int Blinear_Down4[4];

typedef struct
{
    const int *ScaleCoeff;
    const int  ScaleTap;
} ScaleInfo;

extern const ScaleInfo ScaleCoef[SCALE_RATIO_BUTT][SCALE_TAP_BUTT];

extern const HI_S16 coef6Tap_66M_a20[COEFF_BUTT][6];
extern const HI_S16 coef6Tap_6M_a25[COEFF_BUTT][6];
extern const HI_S16 coef6Tap_5M_a25[COEFF_BUTT][6];
extern const HI_S16 coef6Tap_4M_a20[COEFF_BUTT][6];
extern const HI_S16 coef6Tap_35M_a18[COEFF_BUTT][6];
extern const HI_S16 coef6Tap_cubic[COEFF_BUTT][6];

extern const HI_S16 coef4Tap_5M_a15[COEFF_BUTT][4];
extern const HI_S16 coef4Tap_4M_a15[COEFF_BUTT][4];
extern const HI_S16 coef4Tap_cubic[COEFF_BUTT][4];

extern const HI_S16 vpss_coef4Tap[COEFF_BUTT][4];
extern const HI_S16 vpss_coef6Tap[COEFF_BUTT][6];


extern const int *pps32OrgZoomCoeff_vpss[7][4];

void Check_Coeff_Norm(int *pCoef, int butt, int tap, int norm);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* End of #ifndef __HI_SCALER_ROM_H__ */

