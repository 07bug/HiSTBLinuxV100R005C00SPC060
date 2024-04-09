#ifndef __VPSS_HAL_MAC_CTRL_H__
#define __VPSS_HAL_MAC_CTRL_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

HI_VOID VPSS_MAC_SetDmaEn               ( S_VPSS_REGS_TYPE *pstReg, HI_U32 dma_en                 );
HI_VOID VPSS_MAC_SetMaxReqLen           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 max_req_len            );
HI_VOID VPSS_MAC_SetMaxReqNum           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 max_req_num            );
HI_VOID VPSS_MAC_SetRotateAngle         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 rotate_angle           );
HI_VOID VPSS_MAC_SetRotateEn            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 rotate_en              );
HI_VOID VPSS_MAC_SetImgProMode          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 img_pro_mode           );
HI_VOID VPSS_MAC_SetProt                ( S_VPSS_REGS_TYPE *pstReg, HI_U32 prot                   );
HI_VOID VPSS_MAC_SetSttWAddr            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 stt_w_addr             );
HI_VOID VPSS_MAC_SetCfRtunlInterval     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_interval      );
HI_VOID VPSS_MAC_SetCfRtunlBypass       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_bypass        );
HI_VOID VPSS_MAC_SetCfRtunlEn           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_en            );
HI_VOID VPSS_MAC_SetCfRtunlAddr         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 cf_rtunl_addr          );
HI_VOID VPSS_MAC_SetOut0WtunlMode       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_mode        );
HI_VOID VPSS_MAC_SetOut0WtunlEn         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_en          );
HI_VOID VPSS_MAC_SetOut0WtunlFinishLine ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_finish_line );
HI_VOID VPSS_MAC_SetOut0WtunlAddr       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_wtunl_addr        );
HI_VOID VPSS_MAC_SetPatBkgrndU          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_bkgrnd_u           );
HI_VOID VPSS_MAC_SetPatBkgrndV          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_bkgrnd_v           );
HI_VOID VPSS_MAC_SetPatDisWidth         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_dis_width          );
HI_VOID VPSS_MAC_SetPatAngle            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 pat_angle              );
HI_VOID VPSS_MAC_SetTestPatEn           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 test_pat_en            );

#endif

