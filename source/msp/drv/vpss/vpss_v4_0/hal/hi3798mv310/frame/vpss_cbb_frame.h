#ifndef __VPSS_CBB_FRAME_H__
#define __VPSS_CBB_FRAME_H__

#include "vpss_cbb_common.h"
#include "vpss_cbb_component.h"


typedef struct
{
    HI_U32              u32Width;
    HI_U32              u32Height;
    HI_RECT_S           stOffset;
    CBB_FRAME_ADDR_S    stAddr[CBB_FREAM_BUF_CNT];// ��������ַʹ��bit�������
    CBB_BITWIDTH_E      enBitWidth;
    HI_DRV_PIX_FORMAT_E     enPixelFmt;
    HI_BOOL             bSecure;
    HI_BOOL             bCompress;
    HI_BOOL             bProgressive;
    HI_BOOL             bTopFirst;
    HI_BOOL             bTop;
    HI_BOOL             bSpecialTile;
    HI_BOOL             bEn;
    //VC_1    stVcInfo;
} CBB_FRAME_S;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
HI_S32 CBB_CfgFrm_ReadChn(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, CBB_FRAME_CHANNEL_E enFrameChan);
HI_S32 CBB_CfgFrm_WriteChn(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, CBB_FRAME_CHANNEL_E enFrameChan);
HI_VOID CBB_MAC_SetRchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg);
HI_VOID CBB_MAC_SetWchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg);

extern HI_S32 CBB_CfgFrm_ReadCur(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadNx1(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadNx2(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadRee(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_ReadRef(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_WriteCue(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_S32 CBB_CfgFrm_WriteRfr(CBB_FRAME_S *pstFrmCfg, CBB_REG_ADDR_S stRegAddr, HI_BOOL bEnable);
extern HI_S32 CBB_CfgFrm_WriteVhd0(CBB_FRAME_S *pstFrmCfg, HI_VOID *pArgs, CBB_REG_ADDR_S stRegAddr);
extern HI_U32 CBB_FrameFmtTrans( HI_DRV_PIX_FORMAT_E    enPixelFmt );

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif

