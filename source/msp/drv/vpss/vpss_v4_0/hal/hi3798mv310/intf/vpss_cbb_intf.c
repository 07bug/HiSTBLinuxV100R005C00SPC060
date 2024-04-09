#include "vpss_cbb_base.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_info.h"
#include "vpss_cbb_func.h"
#include "vpss_cbb_frame.h"
#include "vpss_cbb_alg.h"
#include "vpss_cbb_intf.h"


HI_S32 VPSS_CBB_BASE_Operating(CBB_REG_ADDR_S stRegAddr,
                               CBB_BASEOPT_E enAlg,
                               HI_VOID *pArg1,
                               HI_VOID *pArg2)
{
    HI_S32 s32RetCode = HI_SUCCESS;

    switch (enAlg)
    {
        case CBB_BASEOPT_START_LOGIC:
        {
            CBB_START_CFG_S *pstStartCfg;
            pstStartCfg = (CBB_START_CFG_S *)pArg1;
            VPSS_BaseOpt_CreateListandStart(pstStartCfg, stRegAddr);
        }
        break;
        case CBB_BASEOPT_GET_ISR_STAT:
        {
            HI_BOOL *pbIsrState;
            pbIsrState = (HI_BOOL *)pArg1;
            VPSS_BaseOpt_GetMaskInt(pbIsrState, stRegAddr);
        }
        break;
        case CBB_BASEOPT_CLR_ISR_STAT:
        {
            HI_BOOL *pbIsrState;
            pbIsrState = (HI_BOOL *)pArg1;
            VPSS_BaseOpt_ClrInt(pbIsrState, stRegAddr);
        }
        break;
        /*
        case CBB_BASEOPT_SET_ISR_MASK:
            {
                HI_BOOL *pbIsrMask;
                pbIsrMask = (HI_BOOL *)pArg1;
                VPSS_BaseOpt_SetIntMask(pbIsrMask, stRegAddr);
            }
            break;
        */
        case CBB_BASEOPT_CONFIG_AXI:
        {
            CBB_OUTSTANDING_S *pOutStd;

            pOutStd = (CBB_OUTSTANDING_S *)pArg1;
            VPSS_BaseOpt_SetOutStd(pOutStd, stRegAddr);
        }
        break;
        /*
        case CBB_BASEOPT_CONFIG_CLOCK:
                {
                    HI_BOOL *pbClkEnable;
                    VPSS_IP_E *peIP;
                    peIP        = (VPSS_IP_E *)pArg1;
                    pbClkEnable = (HI_BOOL *)pArg2;
                    VPSS_HAL_SetClockEn(*peIP, *pbClkEnable);
                }
                break;
        */
        {
            //HI_BOOL *pbClkEnable;
        }
        break;
        case CBB_BASEOPT_CONFIG_BUS:
        {
            CBB_BUS_CTRL_S *pBusCtrl;
            pBusCtrl = (CBB_BUS_CTRL_S *)pArg1;
            VPSS_BaseOpt_SetBusCtrl(pBusCtrl, stRegAddr);
        }
        default:
            s32RetCode = HI_FAILURE;
            break;
    }

    return s32RetCode;
}
HI_S32 VPSS_CBB_FRAME_SetConfig(CBB_REG_ADDR_S stRegAddr,
                                CBB_FRAME_CHANNEL_E enFrameChan,
                                HI_VOID *pArg1,
                                HI_VOID *pArg2)
{
    HI_S32 s32RetCode = 0;

    CBB_FRAME_S *pstFrmCfg;
    pstFrmCfg = (CBB_FRAME_S *)pArg1;

    //flush_cache_all();
    if (CBB_FRAME_READ_NX2 == enFrameChan)
    {
        VPSS_Sys_SetBfieldFirst((S_VPSS_REGS_TYPE *)stRegAddr.pu8NodeVirAddr, 0, !pstFrmCfg->bTopFirst);
    }

    if (enFrameChan <= CBB_FRAME_READ_REE)
    {
        s32RetCode = CBB_CfgFrm_ReadChn(pstFrmCfg, stRegAddr, enFrameChan);
    }
    else if (enFrameChan <= CBB_FRAME_WRITE_CUE)

    {
        s32RetCode = CBB_CfgFrm_WriteChn(pstFrmCfg, stRegAddr, enFrameChan);
    }
    else
    {
        VPSS_FATAL("Error enFrameChan[%d]!\n", enFrameChan);
    }

    //printk("s32RetCode : %d, pstFrmCfg : %p,pArg2 : %p.\n",s32RetCode,pstFrmCfg,pArg2);

    return s32RetCode;
}

HI_S32 VPSS_CBB_INFO_SetConfig(CBB_REG_ADDR_S stRegAddr,
                               CBB_INFO_CHANNEL_E enInfoChan,
                               HI_VOID *pArg1,
                               HI_VOID *pArg2)
{
    switch (enInfoChan)
    {
        case CBB_INFO_DEI_ST:
        {
            CBB_INFO_S *pstInfoDeiCfg;
            pstInfoDeiCfg = (CBB_INFO_S *)pArg1;
            VPSS_InfoCfg_Dei_ST(pstInfoDeiCfg, stRegAddr);
        }
        break;

        case CBB_INFO_TNR_MAD:
        {
            CBB_INFO_S *pstInfoTnrCfg;
            pstInfoTnrCfg = (CBB_INFO_S *)pArg1;
            VPSS_InfoCfg_Tnr_Mad(pstInfoTnrCfg, stRegAddr);
        }
        break;

        case CBB_INFO_SNR_MAD:
        {
            CBB_INFO_S *pstInfoSnrCfg;
            pstInfoSnrCfg = (CBB_INFO_S *)pArg1;
            VPSS_InfoCfg_Snr_Mad(pstInfoSnrCfg, stRegAddr);
        }
        break;

        case CBB_INFO_PRJ_V:
        {
            CBB_INFO_PRJV_S *pstInfoPRJ_VCfg;
            pstInfoPRJ_VCfg = (CBB_INFO_PRJV_S *)pArg1;
            VPSS_InfoCfg_Prjv(pstInfoPRJ_VCfg, stRegAddr);
        }
        break;

        case CBB_INFO_PRJ_H:
        {
            CBB_INFO_PRJH_S *pstInfoPRJ_HCfg;
            pstInfoPRJ_HCfg = (CBB_INFO_PRJH_S *)pArg1;
            VPSS_InfoCfg_Prjh(pstInfoPRJ_HCfg, stRegAddr);
        }
        break;
        case CBB_INFO_DI:
        {
            CBB_INFO_DI_S *pstInfoDiCfg;
            pstInfoDiCfg = (CBB_INFO_DI_S *)pArg1;
            VPSS_InfoCfg_Di(pstInfoDiCfg, stRegAddr);
        }
        break;

        case CBB_INFO_BLKMV:
        {
            CBB_INFO_BLKMV_S *pstInfoBlkmvCfg;
            pstInfoBlkmvCfg = (CBB_INFO_BLKMV_S *)pArg1;
            VPSS_InfoCfg_Blkmv(pstInfoBlkmvCfg, stRegAddr);
        }
        break;

        case CBB_INFO_RGMV:
        {
            CBB_INFO_RGMV_S *pstInfoRgmvCfg;
            pstInfoRgmvCfg = (CBB_INFO_RGMV_S *)pArg1;
            VPSS_InfoCfg_Rgmv(pstInfoRgmvCfg, stRegAddr);
        }
        break;

        case CBB_INFO_BLKMT:
        {
            CBB_INFO_BLKMT_S *pstInfoBlkmtCfg;
            pstInfoBlkmtCfg = (CBB_INFO_BLKMT_S *)pArg1;
            VPSS_InfoCfg_Blkmt(pstInfoBlkmtCfg, stRegAddr);
        }
        break;
        case CBB_INFO_STT:
        {
            CBB_INFO_S *pstSttInfo;
            pstSttInfo = (CBB_INFO_S *)pArg1;
            VPSS_InfoCfg_SttInfo(pstSttInfo, stRegAddr);
        }
        break;

        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CBB_INFO_GetInfo(CBB_REG_ADDR_S stRegAddr,
                             CBB_CALC_INFO_E enInfoChan,
                             HI_VOID *pArg1,
                             HI_VOID *pArg2)
{
    switch (enInfoChan)
    {
        case CBB_INFO_WBC_ALL:
        {
#if 0
            S_STT_REGS_TYPE *pstSttReg;
            CBB_INFO_S *pstInfoStt;

            pstSttReg = (S_STT_REGS_TYPE *)pArg1;
            pstInfoStt = (CBB_INFO_S *)pArg2;
            VPSS_InfoGet_All(pstSttReg, pstInfoStt);
#endif
        }
        break;
        case CBB_INFO_WBC_RWZB:    //�������
        {

        }
        break;
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CBB_FUNC_SetConfig(CBB_REG_ADDR_S stRegAddr,
                               CBB_FUNC_E enFunction,
                               HI_VOID *pArg1,
                               HI_VOID *pArg2)
{
    switch (enFunction)
    {
        case CBB_FUNC_VC1:
        {
            CBB_FUNC_VC1_S *pstFuncVC1Cfg;
            CBB_FRAME_CHANNEL_E *penChan;

            pstFuncVC1Cfg = (CBB_FUNC_VC1_S *)pArg1;
            penChan       = (CBB_FRAME_CHANNEL_E *)pArg2;
            VPSS_FuncCfg_VC1(pstFuncVC1Cfg, (*(penChan)), stRegAddr);
        }
        break;
        case CBB_FUNC_VHD0_ZME:
        {
            CBB_FUNC_ZME_S *pstFuncZmeCfg;
            pstFuncZmeCfg = (CBB_FUNC_ZME_S *)pArg1;
            VPSS_FuncCfg_Zme(pstFuncZmeCfg, stRegAddr);
        }
        break;
        case CBB_FUNC_VHD0_CROP:
        {
            CBB_FUNC_CROP_S *pstFuncCropCfg;
            pstFuncCropCfg = (CBB_FUNC_CROP_S *)pArg1;
            VPSS_FuncCfg_Crop(pstFuncCropCfg, stRegAddr);
        }
        break;
        case CBB_FUNC_VHD0_LBOX:
        {
            CBB_FUNC_LBOX_S *pstFuncLBoxCfg;
            pstFuncLBoxCfg = (CBB_FUNC_LBOX_S *)pArg1;
            VPSS_FuncCfg_LBox(pstFuncLBoxCfg, stRegAddr);
        }
        break;
        case CBB_FUNC_VHD0_VPZME:
        {
            CBB_FUNC_VPZME_S *pstFuncVPZmeCfg;
            pstFuncVPZmeCfg = (CBB_FUNC_VPZME_S *)pArg1;
            VPSS_FuncCfg_VPZme(pstFuncVPZmeCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_VHD0_FLIP:
        {
            CBB_FUNC_FLIP_S *pstFuncFlipCfg;
            pstFuncFlipCfg = (CBB_FUNC_FLIP_S *)pArg1;
            VPSS_FuncCfg_Flip(pstFuncFlipCfg, stRegAddr);
        }
        break;
        case CBB_FUNC_VHD0_UV:
        {
            CBB_FUNC_UV_S *pstFuncUvInvertCfg;
            pstFuncUvInvertCfg = (CBB_FUNC_UV_S *)pArg1;
            VPSS_FuncCfg_UVRevert(pstFuncUvInvertCfg, stRegAddr);
        }
        break;
        case CBB_FUNC_TUNNEL_IN:
        {
            CBB_FUNC_TUNNELIN_S *pstFuncTunnelInCfg;
            pstFuncTunnelInCfg = (CBB_FUNC_TUNNELIN_S *)pArg1;
            VPSS_FuncCfg_TunneIn(pstFuncTunnelInCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_TUNNEL_OUT:
        {
            CBB_FUNC_TUNNELOUT_S *pstFuncTunnelOutCfg;
            pstFuncTunnelOutCfg = (CBB_FUNC_TUNNELOUT_S *)pArg1;
            VPSS_FuncCfg_TunneOut(pstFuncTunnelOutCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_TRANS:
        {
            CBB_FUNC_TRANS_S *pstFuncTransCfg;
            pstFuncTransCfg = (CBB_FUNC_TRANS_S *)pArg1;
            VPSS_FuncCfg_Trans(pstFuncTransCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_SMMU:
        {
            CBB_FUNC_SMMU_S *pstFuncSMMUCfg;
            pstFuncSMMUCfg = (CBB_FUNC_SMMU_S *)pArg1;
            VPSS_FuncCfg_SMMU(pstFuncSMMUCfg, stRegAddr);
        }
        break;

        //Y,C enter the same brunch.
        case CBB_FUNC_ROTATION_Y:
        case CBB_FUNC_ROTATION_C:
        {
            CBB_FUNC_ROTATION_YC_S *pstFuncRotatYCCfg;
            pstFuncRotatYCCfg = (CBB_FUNC_ROTATION_YC_S *)pArg1;
            VPSS_FuncCfg_ROTATIONYC(pstFuncRotatYCCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_SPEED_UP_4PIXEL:
        {
            CBB_FUNC_4PIXEL_S *pstFunc4PixelCfg;
            pstFunc4PixelCfg = (CBB_FUNC_4PIXEL_S *)pArg1;
            VPSS_FuncCfg_4PIXEL(pstFunc4PixelCfg, stRegAddr);
        }
        break;

        case CBB_FUNC_CTS10BIT:
        {
            CBB_FUNC_CTS10BIT_S *pstFuncCTS10bitCfg;
            pstFuncCTS10bitCfg = (CBB_FUNC_CTS10BIT_S *)pArg1;
            VPSS_FuncCfg_CTS10BIT(pstFuncCTS10bitCfg, stRegAddr);
        }
        break;

#if 1
        case CBB_FUNC_FDIFRO:
        {
            CBB_FUNC_FDIFRO_S *pstFuncFdIFdOCfg;
            pstFuncFdIFdOCfg = (CBB_FUNC_FDIFRO_S *)pArg1;
            VPSS_FuncCfg_FDIFRO(pstFuncFdIFdOCfg, stRegAddr);
        }
        break;
#endif
        default:
            break;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CBB_ALG_SetConfig(CBB_REG_ADDR_S stRegAddr,
                              CBB_ALG_E enAlg,
                              HI_VOID *pArg1,
                              HI_VOID *pArg2)
{
    switch (enAlg)
    {
        case CBB_ALG_ZME:
        {
            CBB_ALG_ZME_S *pstAlgZmeCfg;
            pstAlgZmeCfg = (CBB_ALG_ZME_S *)pArg1;
            VPSS_AlgCfg_Zme(pstAlgZmeCfg, stRegAddr);
        }
        break;

        case CBB_ALG_DEI:
        {

        }
        break;

        case CBB_ALG_TNR:

        {
        }
        break;

        case CBB_ALG_SNR:
        {
        }
        break;
        default:
            break;
    }

    return HI_SUCCESS;

}

