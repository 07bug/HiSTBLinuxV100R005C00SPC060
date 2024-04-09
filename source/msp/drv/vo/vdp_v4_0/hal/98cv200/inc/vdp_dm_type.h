
#ifndef __VDP_DM_TYPE_H__
#define __VDP_DM_TYPE_H__

#include "vdp_dm_modctrl.h"



#define MS_ROW_FLTR_RADIUS_MAX    5
#define MS_COL_FLTR_RADIUS_MAX    2

typedef unsigned char KDtp_t;
typedef unsigned char KClr_t;
typedef unsigned char KChrm_t;
typedef unsigned char KWeav_t;
typedef unsigned char KEotf_t;
typedef unsigned char KLoc_t;
typedef unsigned char KBdp_t;





#define KDtpU16    ((KDtp_t)0)
#define KDtpU8    ((KDtp_t)1)
#define KDtpF32   ((KDtp_t)2)
#define KDtpNum   ((KDtp_t)3)

#define KClrYuv   ((KClr_t)0)
#define KClrRgb   ((KClr_t)1)
#define KClrRgba  ((KClr_t)2)
#define KClrIpt   ((KClr_t)3)
#define KClrNum   ((KClr_t)4)

#define KChrm420  ((KChrm_t)0)
#define KChrm422  ((KChrm_t)1)
#define KChrm444  ((KChrm_t)2)
#define KChrmNum  ((KChrm_t)3)

#define KWeavPlnr ((KWeav_t)0)
#define KWeavIntl ((KWeav_t)1)
#define KWeavUyVy ((KWeav_t)2)
#define KWeavNum  ((KWeav_t)3)

#define KEotfBt1886   ((KEotf_t)0)
#define KEotfPq       ((KEotf_t)1)
#define KEotfNum      ((KEotf_t)2)

#define KLocHost    ((KLoc_t)0)
#define KLocDev     ((KLoc_t)1)
#define KLocNum     ((KLoc_t)2)


typedef struct tagVDP_DM_FRM_FMT_S
{
    int rowNum, colNum;
    KDtp_t dtp;
    KWeav_t weav;
    KLoc_t loc;

    KBdp_t bdp;
    KChrm_t chrm;
    KClr_t clr;


    int rowPitch;
    int colPitch;

    int rowPitchC;
} VDP_DM_FRM_FMT_S;


typedef struct tagVDP_DM_KSCTRL_S
{
    int mainIn;
#if DM_SEC_INPUT
    int secIn;
#endif

    int prf;
} VDP_DM_KSCTRL_S;

#if 1
typedef enum tagVDP_DM_TCLUTDIR_S
{
    KTcLutDirFwd = 0,
    KTcLutDirBwd,
    KTcLutDirPass,
    KTcLutDirNum
} VDP_DM_TCLUTDIR_S;
#endif
#endif
