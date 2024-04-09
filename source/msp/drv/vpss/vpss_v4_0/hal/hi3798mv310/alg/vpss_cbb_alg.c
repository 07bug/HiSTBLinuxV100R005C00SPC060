#include "vpss_cbb_alg.h"
#include "vpss_cbb_reg.h"
#include "hi_reg_common.h"
HI_VOID VPSS_AlgCfg_BaseFunc(CBB_REG_ADDR_S stRegAddr, CBB_ALG_E eAlgId, HI_VOID *pArg1, HI_VOID *pArg2)
{
    S_VPSS_REGS_TYPE *pstVpssNode;  //DDR中节点首地址
    pstVpssNode = (S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr;

    switch ( eAlgId )
    {
        case CBB_ALG_DEI:
        {
            CBB_ALG_INFO_S *pstDEIInfo;
            pstDEIInfo = (CBB_ALG_INFO_S *)pArg1;

            VPSS_Sys_SetDeiCfgAddr(pstVpssNode, 0, pstDEIInfo->u32ParaAddr);
            VPSS_Sys_SetDeiEn(pstVpssNode, 0, pstDEIInfo->bEnable);
        }
        break;
        case CBB_ALG_TNR:
        {
            CBB_ALG_INFO_S *pstTNRInfo;
            pstTNRInfo = (CBB_ALG_INFO_S *)pArg1;

            VPSS_Sys_SetTnrCfgAddr(pstVpssNode, 0, pstTNRInfo->u32ParaAddr);


            VPSS_Sys_SetTnrEn(pstVpssNode, 0, pstTNRInfo->bEnable);
        }
        break;
        case CBB_ALG_TNR_MC:
        {
            CBB_ALG_INFO_S      *pstDeiAlgCfg;
            pstDeiAlgCfg = (CBB_ALG_INFO_S *)pArg1;
            VPSS_Sys_SetMcnrEn(pstVpssNode, 0, pstDeiAlgCfg->bEnable);
            VPSS_Sys_SetRgmeEn(pstVpssNode, 0, pstDeiAlgCfg->bEnable);
        }
        break;
        case CBB_ALG_SNR:
        {
            CBB_ALG_INFO_S *pstSnrInfo;
            //            HI_U32 u32SnrCfg;
            pstSnrInfo = (CBB_ALG_INFO_S *)pArg1;
            // u32SnrCfg = *(HI_U32 *)pArg2;
            //db,dm, nr的总开关， SNR包括db,dm,nr
            VPSS_Sys_SetSnrCfgAddr(pstVpssNode, 0, pstSnrInfo->u32ParaAddr);
            VPSS_Sys_SetSnrEn(pstVpssNode, 0, pstSnrInfo->bEnable);
            VPSS_Sys_SetDbEn(pstVpssNode, 0, pstSnrInfo->bEnable);
            VPSS_Sys_SetBlkDetEn(pstVpssNode, 0, pstSnrInfo->bEnable);
            VPSS_Sys_SetMadVfirEn(pstVpssNode, 0, pstSnrInfo->bMad_vfir_en);
        }
        break;
        case CBB_ALG_HDR:
        {
            CBB_ALG_INFO_S *pstHdrInfo;
            HI_BOOL  bHdrIn;
            pstHdrInfo = (CBB_ALG_INFO_S *)pArg1;
            bHdrIn = pstHdrInfo->bEnable;
            VPSS_Sys_SetHdrIn(pstVpssNode, 0, bHdrIn);
            VPSS_Sys_SetHdrCfgAddr(pstVpssNode, 0, pstHdrInfo->u32ParaAddr);
            pstVpssNode->VPSS_LCHDR_CTRL.bits.lchdr_ck_gt_en = pstHdrInfo->bEnable;
            pstVpssNode->VPSS_LCHDR_CTRL.bits.lchdr_en = pstHdrInfo->bEnable;
        }
        break;
        case CBB_ALG_IGBM:
        {
            CBB_ALG_INFO_S *pstAlgInfo;
            pstAlgInfo = (CBB_ALG_INFO_S *)pArg1;
            VPSS_Sys_SetIgbmEn(pstVpssNode, 0, pstAlgInfo->bEnable);
        }
        break;
        case CBB_ALG_IFMD:
        {
            CBB_ALG_INFO_S *pstAlgInfo;
            pstAlgInfo = (CBB_ALG_INFO_S *)pArg1;
            VPSS_Sys_SetIfmdEn(pstVpssNode, 0, pstAlgInfo->bEnable);
        }
        break;
        case CBB_ALG_MCDEI:
        {
            CBB_ALG_INFO_S *pstMcdiInfo;
            HI_BOOL         bEnable;
            pstMcdiInfo = (CBB_ALG_INFO_S *)pArg1;
            if (HI_NULL != pArg2)
            {
                bEnable = *(HI_BOOL *)pArg2;
            }
            else
            {
                bEnable = pstMcdiInfo->bEnable;
            }

            VPSS_Sys_SetMcdiEn(pstVpssNode, 0, pstMcdiInfo->bEnable);
            VPSS_Sys_SetRgmeEn(pstVpssNode, 0, bEnable);
        }
        break;
        default:
            VPSS_ERROR("Unsupport alg type:%d\n", eAlgId);
            break;
    }

}

HI_VOID VPSS_AlgCfg_Zme(CBB_ALG_ZME_S *pstAlgZmeCfg, CBB_REG_ADDR_S stRegAddr)
{
    return;
}

