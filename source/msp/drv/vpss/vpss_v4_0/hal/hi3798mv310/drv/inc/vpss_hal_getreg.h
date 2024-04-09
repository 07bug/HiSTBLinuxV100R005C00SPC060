/******************************************************************************

 Copyright @ Hisilicon Technologies Co., Ltd. 1998-2015. All rights reserved.

 ******************************************************************************
  File Name     : vpss_cfgreg.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/1/25
  Last Modified :
  Description   : vpss_cfgreg.c header file
  Function List :
  History       :
  1.Date        : 2016/1/25
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __VPSS_HAL_GETREG_H__
#define __VPSS_HAL_GETREG_H__

#include "vpss_hal_comm.h"
/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_BOOL VPSS_HAL_Getb3DrsEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_U32 VPSS_HAL_GetMeVersion(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_U32 VPSS_HAL_Get3DrsVersion(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbMeEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbScdEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbDeiEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbCcclEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbCcclRfrEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbRgmeEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbMcnrEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbRotateEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_U32 VPSS_HAL_GetImgProcMode(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbSecEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbTile(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbSegDcmp(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_U32 VPSS_HAl_GetMeVersion(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbRttEn(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_U32 VPSS_HAL_GetImgProMode(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbSnrMadEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbField(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbCurBottom(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgMode(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbMmuGlbBypass(S_VPSS_REGS_TYPE *pstVPSSReg);

HI_BOOL VPSS_HAL_GetbMmuImgBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbMmuSoloBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbMmuOutImgBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbMmuOutSoloBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetGetRawIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs);

HI_U32 VPSS_HAL_GetGetIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs);

HI_U32 VPSS_DRV_GetPfCnt(S_VPSS_REGS_TYPE *pstVpssRegs);

//HI_U32 VPSS_DRV_GetEofCnt(S_VPSS_REGS_TYPE *pstVpssRegs);

HI_U32 VPSS_DRV_GetNodeId(S_VPSS_REGS_TYPE *pstVpssRegs);

HI_BOOL VPSS_DRV_GetbChkSumEn(S_VPSS_REGS_TYPE *pstVpssRegs);

HI_S32 VPSS_DRV_Get_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 *pu32SecureState, HI_U32 *pu32NoSecureState);

//###########IMG RCHN#########
HI_U32 VPSS_HAL_GetImgRChnFormat(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnHorOffset(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnVerOffset(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnYStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnCStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgRChnPixBtW(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbImgRChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

//###########IMG WCHN#########
HI_U32 VPSS_HAL_GetImgWChnFormat(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgWChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgWChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgWChnYStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgWChnCStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetImgWChnPixBtW(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbImgWChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetbFrmCmp(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

//###########SOLO RCHN#########
HI_BOOL VPSS_HAL_GetbSoloRChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloRChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloRChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloRChnStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

//###########SOLO WCHN#########
HI_BOOL VPSS_HAL_GetbSoloWChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloWChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloWChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_U32 VPSS_HAL_GetSoloWChnStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset);

HI_BOOL VPSS_HAL_GetCfCConvert(S_VPSS_REGS_TYPE *pVdpReg);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __VPSS_CFGREG_H__ */

