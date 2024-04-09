#include "hi_kernel_adapt.h"
#include "vpss_ctrl.h"
#include "vpss_common.h"
#include "hi_drv_proc.h"
#include "vpss_alg_buf.h"
#ifdef VPSS_HAL_WITH_CBB
#include "vpss_cbb_common.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_intf.h"
#include "vpss_cbb_hal.h"
#include "vpss_cbb_alg.h"
#include "vpss_cbb_reg.h"
#include "vpss_cbb_common.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

static VPSS_CTRL_S g_stVpssCtrl[VPSS_IP_BUTT] =
{
    {
        .bIPVaild = HI_FALSE,
        .enIP     = VPSS_IP_0,
        .u32VpssIrqNum = VPSS0_IRQ_NUM,
        .pVpssIntService = VPSS0_CTRL_IntService,
        .isr_name = "vpss0",
        .s32IsVPSSOpen = 0,
    },

    {
        .bIPVaild = HI_TRUE,
        .enIP     = VPSS_IP_1,
        .u32VpssIrqNum = VPSS1_IRQ_NUM,
        .pVpssIntService = VPSS1_CTRL_IntService,
        .isr_name = "vpss1",
        .s32IsVPSSOpen = 0,
    }
};

HI_VOID VPSS_CTRL_InitInstList(VPSS_IP_E enIp)
{
    HI_U32 u32Count;
    VPSS_INST_CTRL_S *pstInsList;

    pstInsList = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    rwlock_init(&(pstInsList->stListLock));
    pstInsList->u32InstanceNum = 0;

    for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count ++)
    {
        pstInsList->pstInstPool[u32Count] = HI_NULL;
    }

}

HI_S32 VPSS_CTRL_RegistISR(VPSS_IP_E enIp)
{
    if (osal_request_irq(g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].pVpssIntService,
                         IRQF_SHARED, g_stVpssCtrl[enIp].isr_name, &(g_stVpssCtrl[enIp].hVpssIRQ)))
    {
        VPSS_FATAL("VPSS%d registe IRQ failed!\n", (HI_U32)enIp);
        return HI_FAILURE;
    }
    else
    {
        if (HI_SUCCESS != HI_DRV_SYS_SetIrqAffinity(HI_ID_VPSS, g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].isr_name))
        {
            VPSS_ERROR("Set Vpss Irq Affinity Failed.\n");
        }

        return HI_SUCCESS;
    }
}

HI_S32 VPSS_CTRL_UnRegistISR(VPSS_IP_E enIp)
{
    osal_free_irq(g_stVpssCtrl[enIp].u32VpssIrqNum, g_stVpssCtrl[enIp].isr_name, &(g_stVpssCtrl[enIp].hVpssIRQ));
    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_GetDistributeIP(VPSS_IP_E *penVpssIp)
{
    HI_U32 u32MinInstCount = VPSS_INSTANCE_MAX_NUMB;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if ((HI_TRUE == g_stVpssCtrl[i].bIPVaild) && (u32MinInstCount > g_stVpssCtrl[i].stInstCtrlInfo.u32InstanceNum))
        {
            u32MinInstCount = g_stVpssCtrl[i].stInstCtrlInfo.u32InstanceNum;
            *penVpssIp = i;
            s32Ret = HI_SUCCESS;
        }
    }

    return s32Ret;
}


HI_S32 VPSS_CTRL_SyncDistributeIP(VPSS_INSTANCE_S *pstInstance, HI_DRV_VPSS_IPMODE_E enIpmode)
{
    HI_U32 i;
    VPSS_IP_E enDstVpssIp;
    VPSS_IP_E enSrcVpssIp;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long u32LockFlag;
    VPSS_INSTANCE_S *pstChgInst = HI_NULL;

    //step1:get instance real ip
    //step2:change instance to new ip
    //step2.1:if the new ip has instance ,change it together
    if (HI_DRV_VPSS_IPMODE_BUTT <= enIpmode)
    {
        VPSS_FATAL("Invalid Ipmode %d.", enIpmode);
        return HI_FAILURE;
    }

    if ((HI_FALSE == g_stVpssCtrl[VPSS_IP_0].bIPVaild)
        || (HI_FALSE == g_stVpssCtrl[VPSS_IP_1].bIPVaild))
    {
        VPSS_ERROR("Can not change IP %d,single ctrl", enIpmode);
        return HI_FAILURE;
    }

    if (HI_DRV_VPSS_IPMODE_IP0 == enIpmode)
    {
        enDstVpssIp = VPSS_IP_0;
    }
    else
    {
        enDstVpssIp = VPSS_IP_1;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);
    if (enDstVpssIp == pstInstance->CtrlID)
    {
        return HI_SUCCESS;
    }

    enSrcVpssIp = pstInstance->CtrlID;

    //we need exchange instance to keep balance
    if (0 < pstInstCtrlInfo->u32InstanceNum)
    {
        pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (HI_NULL != pstInstCtrlInfo->pstInstPool[i])
            {
                pstChgInst = pstInstCtrlInfo->pstInstPool[i];
                pstInstCtrlInfo->pstInstPool[i] = pstInstance;
                pstInstance->CtrlID = enDstVpssIp;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if (HI_NULL == pstChgInst)
        {
            VPSS_ERROR("Can't get DstInst\n");
            return HI_FAILURE;
        }

        pstInstCtrlInfo = &(g_stVpssCtrl[enSrcVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstance == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = pstChgInst;
                pstChgInst->CtrlID = enSrcVpssIp;
                break;
            }
        }
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }
    else
    {
        pstInstCtrlInfo = &(g_stVpssCtrl[enSrcVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstance == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = HI_NULL;
                pstInstCtrlInfo->u32InstanceNum--;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        pstInstCtrlInfo = &(g_stVpssCtrl[enDstVpssIp].stInstCtrlInfo);

        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (HI_NULL == pstInstCtrlInfo->pstInstPool[i])
            {
                pstInstCtrlInfo->pstInstPool[i] = pstInstance;
                pstInstance->CtrlID = enDstVpssIp;
                pstInstCtrlInfo->u32InstanceNum++;
                break;
            }
        }

        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_CheckIstanceReady(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32CheckRet;

    pstInstance->u32CheckCnt++;
    if (jiffies - pstInstance->ulLastCheckTime > HZ)
    {
        pstInstance->u32CheckRate = pstInstance->u32CheckCnt;
        pstInstance->u32CheckSucRate = pstInstance->u32CheckSucCnt;
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->u32BufRate =  pstInstance->u32BufCnt - pstInstance->u32LastBufCnt;
        pstInstance->u32BufSucRate = pstInstance->u32BufSucCnt - pstInstance->u32BufLastSucCnt;
#else
        pstInstance->u32BufRate = pstInstance->u32BufCnt;
        pstInstance->u32BufSucRate = pstInstance->u32BufSucCnt;
#endif
        pstInstance->u32CheckCnt = 0;
        pstInstance->u32CheckSucCnt = 0;
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->u32LastBufCnt = pstInstance->u32BufCnt;
        pstInstance->u32BufLastSucCnt = pstInstance->u32BufSucCnt;
#else
        pstInstance->u32BufCnt = 0;
        pstInstance->u32BufSucCnt = 0;
#endif
        pstInstance->u32ImgRate
            = pstInstance->u32ImgCnt - pstInstance->u32ImgLastCnt;
        pstInstance->u32ImgSucRate
            = pstInstance->u32ImgSucCnt - pstInstance->u32ImgLastSucCnt;
        pstInstance->u32ImgLastCnt = pstInstance->u32ImgCnt;
        pstInstance->u32ImgLastSucCnt = pstInstance->u32ImgSucCnt;
        pstInstance->ulLastCheckTime = jiffies;
    }


    (HI_VOID)VPSS_INST_SyncUsrCfg(pstInstance);

    VPSS_INST_SyncTvpCfg(pstInstance);

    s32CheckRet = VPSS_INST_CheckInstAvailable(pstInstance);
    if (s32CheckRet == HI_SUCCESS)
    {
        (HI_VOID)VPSS_INST_RevisePortOutBitWidth(pstInstance);
#ifdef VPSS_ZME_WIDTH_MAX_FHD
        (HI_VOID)VPSS_INST_RevisePortOutImageWidth(pstInstance);
        (HI_VOID)VPSS_INST_ELFrameResoAndBitwidthAdjust(pstInstance);
        VPSS_INST_RevisePortOutRect(pstInstance);
#else
        (HI_VOID)VPSS_INST_ELFrameResoAndBitwidthAdjust(pstInstance);
#endif

#if defined(CHIP_TYPE_hi3798cv200)
        /* Revise outframe resolution to FHD , when 3D mode is on and frame resolution is bigger than FHD*/
        VPSS_INST_RevisePortOutRect_3d(pstInstance);
        /* In the scence that display fmt is 4K and video is 90_rotation or 270_rotation,
           port outputheight can not be greater than 2048*/
        VPSS_INST_RevisePortOutRect_Rotation(pstInstance);
#endif
        pstInstance->u32CheckSucCnt++;
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulCreatTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_FAILURE;
}

HI_S32 VPSS_CTRL_FixTask(VPSS_IP_E enIp, HI_DRV_BUF_ADDR_E enLR, VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 i;
#ifndef VPSS_ZME_SUPPORT_10BIT
#ifndef VPSS_SUPPORT_10BIT_DITHER
    HI_S32 j;
#endif
#endif
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;

    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_FB_NODE_S *pstFrmNode = HI_NULL;
    VPSS_IN_INTF_S stInIntf;


    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    pstHalInfo->pstPqCfg = &pstInstance->stPqRegData;
#ifdef VPSS_HAL_WITH_CBB
    pstHalInfo->enSceneMode = pstInstance->stUsrInstCfg.enSceneMode;
#endif
    pstHalInfo->s32InstanceID = pstInstance->ID;

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    if (HI_DRV_BUF_ADDR_MAX <= enLR)
    {
        VPSS_ERROR("Invalid Para enLR %d\n", enLR);
        return HI_FAILURE;
    }

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    /* INInfo */
    s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }
#if !defined(HI_NVR_SUPPORT)

#ifdef VPSS_HAL_WITH_CBB
    if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_SD_FIRST)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_SD_SECOND)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP2_DEI)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD))
#else
    if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DETILE_STEP1)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE)
        || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_H265_STEP2_DEI))
#endif
    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;
        HI_PQ_WBC_INFO_S stVpssWbcInfo;
        HI_PQ_CFG_INFO_S stVpssCfgInfo;

        stVpssWbcInfo.u32HandleNo = pstInstance->ID;
        stVpssWbcInfo.u32Width = pstCur->u32Width;
        stVpssWbcInfo.u32Height = pstCur->u32Height;
        stVpssWbcInfo.bProgressive = pstCur->bProgressive;
        stVpssWbcInfo.pstVPSSWbcReg = &(pstInstance->stPqWbcReg[0]);

        stVpssWbcInfo.s32FieldOrder = !pstCur->bTopFieldFirst;

        stVpssWbcInfo.stOriCoordinate.s32X = 0;
        stVpssWbcInfo.stOriCoordinate.s32Y = 0;
        stVpssWbcInfo.stOriCoordinate.s32Width = 0;
        stVpssWbcInfo.stOriCoordinate.s32Height = 0;
        stVpssWbcInfo.stCropCoordinate = stVpssWbcInfo.stOriCoordinate;
        stVpssWbcInfo.u32StreamId = pstInstance->stRwzbInfo.u32Rwzb;
        stVpssWbcInfo.u32FrameIndex = pstInstance->stVpssHalInfo.u32DetileFieldIdx;


        if (pstCur->enFieldMode == HI_DRV_FIELD_TOP)
        {
            stVpssWbcInfo.s32FieldMode = 0;
        }
        else if (pstCur->enFieldMode == HI_DRV_FIELD_BOTTOM)
        {
            stVpssWbcInfo.s32FieldMode = 1;
        }
        else
        {
            VPSS_ERROR("Dei Error.\n");
            stVpssWbcInfo.s32FieldMode = 0;
        }
        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;

        stVpssWbcInfo.u32FrameRate = pstCur->u32FrameRate;
        stVpssWbcInfo.bPreInfo = HI_FALSE;

        stVpssWbcInfo.stVdecInfo.IsProgressiveFrm = pstPriv->ePictureMode;
        stVpssWbcInfo.stVdecInfo.IsProgressiveSeq = pstPriv->eSampleType;
        stVpssWbcInfo.stVdecInfo.RealFrmRate = 2500;
        {
            HI_DRV_VIDEO_PRIVATE_S *pstPriv;
            HI_DRV_DNR_INFO_S *pstDnrInfo;

            pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;
            pstDnrInfo = &pstPriv->stDNRInfo;
            stVpssWbcInfo.bCropBeforeDB = HI_FALSE;
            stVpssWbcInfo.u32SingleModeFlag = 1;
            stVpssWbcInfo.u32Protocol = 1;
            stVpssWbcInfo.u32ImageAvgQP = pstDnrInfo->u32ImageAvgQP;
            stVpssWbcInfo.u32VdhInfoAddr = pstDnrInfo->u32VdhInfoAddr;
            stVpssWbcInfo.u32VdhInfoStride = pstDnrInfo->u32VdhInfoStride;
            stVpssWbcInfo.u32ImageStruct = 0; //pstDnrInfo->u32Size;
        }
        stVpssWbcInfo.enSplitMode = (HI_TRUE == pstInstance->bSplitEnable)
                                    ? HI_DRV_PQ_MCDI_SPLIT_MODE_5 : HI_DRV_PQ_MCDI_SPLIT_MODE_0;

        DRV_PQ_SetAlgCalcCfg(&stVpssWbcInfo, &stVpssCfgInfo);

        /* open set filed order of alg detection sdk */
        if (stVpssCfgInfo.s32FieldOrder != 2)
        {
            if (pstInstance->stInEntity.stStreamInfo.u32RealTopFirst == HI_FALSE)
            {
                if (pstCur->enFieldMode == HI_DRV_FIELD_TOP
                    && pstCur->enBufValidMode != HI_DRV_FIELD_ALL)
                {
                    HI_BOOL bTopFirst;
                    bTopFirst = !stVpssCfgInfo.s32FieldOrder;
                    stInIntf.pfnGetInfo(&pstInstance->stInEntity,
                                        VPSS_IN_INFO_CORRECT_FIELD,
                                        HI_DRV_BUF_ADDR_MAX,
                                        &bTopFirst);
                }
            }
            else if (pstInstance->stInEntity.stStreamInfo.u32RealTopFirst == HI_TRUE)
            {
                if (pstCur->enFieldMode == HI_DRV_FIELD_BOTTOM
                    && pstCur->enBufValidMode != HI_DRV_FIELD_ALL)

                {
                    HI_BOOL bTopFirst;
                    bTopFirst = !stVpssCfgInfo.s32FieldOrder;
                    stInIntf.pfnGetInfo(&pstInstance->stInEntity,
                                        VPSS_IN_INFO_CORRECT_FIELD,
                                        HI_DRV_BUF_ADDR_MAX,
                                        &bTopFirst);
                }
            }
            else
            {

            }
        }
    }
    else
    {
        HI_PQ_WBC_INFO_S stVpssWbcInfo;
        HI_PQ_CFG_INFO_S stVpssCfgInfo;

        memset(&stVpssWbcInfo, 0, sizeof(HI_PQ_WBC_INFO_S));
        memset(&stVpssCfgInfo, 0, sizeof(HI_PQ_CFG_INFO_S));

        stVpssWbcInfo.u32HandleNo = pstInstance->ID;
        stVpssWbcInfo.u32Width = pstCur->u32Width;
        stVpssWbcInfo.u32Height = pstCur->u32Height;
        stVpssWbcInfo.bProgressive = pstCur->bProgressive;
        stVpssWbcInfo.pstVPSSWbcReg = &(pstInstance->stPqWbcReg[0]);

        DRV_PQ_SetAlgCalcCfg(&stVpssWbcInfo, &stVpssCfgInfo);
    }

#endif


#if defined(CHIP_TYPE_hi3798cv200)
    if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R
        || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
    {
        VPSS_INST_SetHalFrameInfo(pstCur,
                                  &pstHalInfo->stInInfo,
                                  HI_DRV_BUF_ADDR_LEFT);
    }
    else
#endif
    {
        VPSS_INST_SetHalFrameInfo(pstCur,
                                  &pstHalInfo->stInInfo,
                                  enLR);

        pstHalInfo->stInInfo.u32TunnelAddr = pstCur->u32TunnelPhyAddr;
    }

#if !defined(HI_NVR_SUPPORT)
    {
        HI_S32          s32SrcId;
        s32SrcId = (pstInstance->hDst & 0x00ff0000) >> 16;
        //vi donot need rwzb, vi cannot give viraddr which rwzb needs.
        if ((s32SrcId != HI_ID_VI) && (pstHalInfo->stInInfo.u32Width <= VPSS_FHD_WIDTH)
            && (!pstHalInfo->stInInfo.bSecure))
        {
            VPSS_RWZB_IMG_S stRwzbImage;

            /*RWZB*/
            if (pstHalInfo->stInInfo.enFieldMode == HI_DRV_FIELD_BOTTOM
                || pstHalInfo->stInInfo.bProgressive == HI_TRUE)
            {
                VPSS_RWZB_GetRwzbData(&(pstInstance->stRwzbInfo), &pstHalInfo->stRwzbInfo);
            }

            stRwzbImage.bProgressive = pstHalInfo->stInInfo.bProgressive;
            stRwzbImage.enFieldMode = pstHalInfo->stInInfo.enFieldMode;
            stRwzbImage.u32Height = pstHalInfo->stInInfo.u32Height;
            stRwzbImage.u32Width = pstHalInfo->stInInfo.u32Width;
#ifdef VPSS_HAL_WITH_CBB
            if ((pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD)
                || (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_DEI_LAST_2FIELD_VIRTUAL))
            {
                pstHalInfo->stRwzbInfo.u32EnRwzb = HI_FALSE;
            }
            else
#endif
            {
                VPSS_RWZB_GetRwzbInfo(&(pstInstance->stRwzbInfo), &pstHalInfo->stRwzbInfo, &stRwzbImage);
            }
        }
        else
        {
            pstHalInfo->stRwzbInfo.u32EnRwzb = HI_FALSE;
        }
    }
#endif

    /*****************************DEI or TNR cfg*******************************/
    VPSS_CHECK_NULL(stInIntf.pfnSetInfo);

    stInIntf.pfnSetInfo(&(pstInstance->stInEntity), VPSS_SET_INFO_INPUT_CFG, enLR, pstHalInfo);

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
#if defined(CHIP_TYPE_hi3798cv200)
        if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L
            || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_R)
        {
            pstFrmNode = pstInstance->pstFrmNode[i * 2];
        }
        else
#endif
        {
            pstFrmNode = pstInstance->pstFrmNode[i * 2 + enLR];
        }

#ifdef ZME_2L_TEST
#ifndef VPSS_HAL_WITH_CBB
        if ( HI_TRUE == pstInstance->stPort[i].bNeedRotate)
        {
            pstFrmNode = pstInstance->pstFrmNodeRoBuf[i];
        }
        else if ( HI_TRUE == pstInstance->stPort[i].bNeedZME2L)
#else
        if ( HI_TRUE == pstInstance->stPort[i].bNeedZME2L)
#endif
        {
            pstFrmNode = pstInstance->pstFrmNodeZME1L;
        }
#endif

#ifdef VPSS_HAL_WITH_CBB
        VPSS_INST_GetRotate(pstInstance, i, &pstHalInfo->astPortInfo[i], pstCur);
#endif
        if (pstFrmNode != HI_NULL)
        {
            pstHalInfo->astPortInfo[i].bEnable = HI_TRUE;
            pstHalInfo->astPortInfo[i].bConfig = HI_FALSE;
#if defined(CHIP_TYPE_hi3798cv200)
            pstHalInfo->astPortInfo[i].bCmpLoss = VPSS_ISLOSS_CMP;
#endif
            pstHalInfo->astPortInfo[i].eLetterBoxColor = pstInstance->stPort[i].eLetterBoxColor;

#ifdef VPSS_SUPPORT_OUT_TUNNEL
            pstHalInfo->astPortInfo[i].bOutLowDelay = pstInstance->bOutLowDelay;
#endif
            if ((pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV16_2X1
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE
                 || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV12_TILE_CMP)
                && (pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV21_CMP
                    || pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV21
                    || pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV61_2X1))
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else if ((pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV61_2X1
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE
                      || pstCur->ePixFormat == HI_DRV_PIX_FMT_NV21_TILE_CMP)
                     && (pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV12
                         || pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV12_CMP
                         || pstInstance->stPort[i].eFormat == HI_DRV_PIX_FMT_NV16_2X1))
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else if (pstInstance->stPort[i].bUVInver) //dbg cmd
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_TRUE;
            }
            else
            {
                pstHalInfo->astPortInfo[i].stOutInfo.bUVInver = HI_FALSE;
            }

#ifdef ZME_2L_TEST
            VPSS_INST_SetOutFrameInfo(pstInstance, i,
                                      &pstFrmNode->stBuffer, &pstFrmNode->stOutFrame, enLR);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
            if (pstHalInfo->astPortInfo[i].bOutLowDelay)
            {
                pstFrmNode->stOutFrame.u32TunnelPhyAddr = VPSS_HAL_TunnelOut_GetBufAddr(enIp, pstHalInfo, i);
            }
            else
            {
                pstFrmNode->stOutFrame.u32TunnelPhyAddr = HI_NULL;
            }
#endif
#else
            //如果开启了旋转，使用旋转BUFFER
#ifndef VPSS_HAL_WITH_CBB
            if ((HI_DRV_VPSS_ROTATION_90 == pstInstance->stPort[i].enRotation)
                || (HI_DRV_VPSS_ROTATION_270 == pstInstance->stPort[i].enRotation))
#else
            if (0)
#endif
            {
                VPSS_INST_SetOutFrameInfo(pstInstance, i,
                                          &g_stVpssCtrl[enIp].stRoBuf[i], &pstFrmNode->stOutFrame, enLR);
            }
            else
            {
                VPSS_INST_SetOutFrameInfo(pstInstance, i,
                                          &pstFrmNode->stBuffer, &pstFrmNode->stOutFrame, enLR);
            }
#endif

            VPSS_INST_SetHalFrameInfo(&pstFrmNode->stOutFrame,
                                      &pstHalInfo->astPortInfo[i].stOutInfo, enLR);

#ifndef VPSS_ZME_SUPPORT_10BIT
#ifndef VPSS_SUPPORT_10BIT_DITHER
            /* when vpss is working at :10bit src input , 8bit output with ZME,CROP eanble.
              Cfg the input src as 8bit, because ZME,CROP do not support 10bit */
            if ((HI_DRV_PIXEL_BITWIDTH_10BIT == pstCur->enBitWidth)
                && (HI_DRV_PIXEL_BITWIDTH_8BIT == pstHalInfo->astPortInfo[i].stOutInfo.enBitWidth))
            {
                pstHalInfo->stInInfo.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                for (j = 0; j < i; j++)
                {
                    pstHalInfo->astPortInfo[j].stOutInfo.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                    pstInstance->pstFrmNode[j * 2]->stOutFrame.enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
                }
            }
#endif
#endif
            VPSS_INST_GetInCrop(pstInstance, i, &pstHalInfo->astPortInfo[i].stInCropRect);
            if (HI_DRV_FT_TAB == pstCur->eFrmType)
            {
                if (VPSS_HAL_NODE_3D_FRAME_R == pstHalInfo->enNodeType)
                {
                    pstHalInfo->astPortInfo[i].stInCropRect.s32Y
                    += (pstCur->u32Height / 2);
                    pstHalInfo->astPortInfo[i].stInCropRect.s32Y
                    &= VPSS_HEIGHT_ALIGN;
                }
                pstHalInfo->astPortInfo[i].stInCropRect.s32Height
                -= (pstCur->u32Height / 2);
                pstHalInfo->astPortInfo[i].stInCropRect.s32Height
                &= VPSS_HEIGHT_ALIGN;
            }
            else if (HI_DRV_FT_SBS == pstCur->eFrmType)
            {
                if (VPSS_HAL_NODE_3D_FRAME_R == pstHalInfo->enNodeType)
                {
                    pstHalInfo->astPortInfo[i].stInCropRect.s32X
                    += (pstCur->u32Width / 2);
                    pstHalInfo->astPortInfo[i].stInCropRect.s32X
                    &= VPSS_WIDTH_ALIGN;
                }
                pstHalInfo->astPortInfo[i].stInCropRect.s32Width
                -= (pstCur->u32Width / 2);
                pstHalInfo->astPortInfo[i].stInCropRect.s32Width
                &= VPSS_WIDTH_ALIGN;
            }
            else
            {
                /*do nothing!!*/
            }

            VPSS_INST_GetVideoRect(pstInstance, i, &pstHalInfo->astPortInfo[i].stInCropRect,
                                   &pstHalInfo->astPortInfo[i].stVideoRect,
                                   &pstHalInfo->astPortInfo[i].stOutCropRect);

            VPSS_DBG_INFO("Incrop W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stInCropRect.s32Width,
                          pstHalInfo->astPortInfo[i].stInCropRect.s32Height);
            VPSS_DBG_INFO("VRect W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stVideoRect.s32Width,
                          pstHalInfo->astPortInfo[i].stVideoRect.s32Height);
            VPSS_DBG_INFO("ORect W H %d %d\n",
                          pstHalInfo->astPortInfo[i].stOutCropRect.s32Width,
                          pstHalInfo->astPortInfo[i].stOutCropRect.s32Height);

            VPSS_SAFE_MEMCPY(&(pstFrmNode->stOutFrame.stLbxInfo),
                             &(pstHalInfo->astPortInfo[i].stVideoRect),
                             sizeof(HI_RECT_S));
#ifndef VPSS_HAL_WITH_CBB
            VPSS_INST_GetRotate(pstInstance, i, &pstHalInfo->astPortInfo[i], pstCur);
#endif
        }
        else
        {
            pstHalInfo->astPortInfo[i].bEnable = HI_FALSE;
        }
    }

    return HI_SUCCESS;

}

HI_BOOL VPSS_CTRL_VirtualPortLowQulity(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_BOOL bStart = HI_FALSE;
    HI_U32 u32Cnt;
    VPSS_HAL_INFO_S *pstHalInfo;

    VPSS_HAL_PORT_INFO_S *pstPortInfo;
    VPSS_PORT_S         *pstPortCfg;



    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    for (u32Cnt = 0 ; u32Cnt < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Cnt ++)
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[u32Cnt]);
        pstPortCfg  = &(pstInstance->stPort[u32Cnt]);
        if (pstPortInfo->bEnable == HI_TRUE
            && pstPortInfo->bConfig == HI_FALSE)
        {
            if ((pstPortCfg->u32MaxFrameRate < 50)
                && (HI_FALSE == pstHalInfo->stInInfo.bProgressive))
            {
                bStart = HI_TRUE;
            }
        }
    }
    return bStart;
}


#ifndef VPSS_HAL_WITH_CBB
HI_BOOL VPSS_CTRL_CheckVirtualStart(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_BOOL bStart = HI_FALSE;

    HI_U32 u32Cnt;

    VPSS_HAL_INFO_S *pstHalInfo;

    VPSS_HAL_PORT_INFO_S *pstPortInfo;


    pstHalInfo  = &(pstInstance->stVpssHalInfo);


    for (u32Cnt = 0 ; u32Cnt < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Cnt ++)
    {
        pstPortInfo = &(pstHalInfo->astPortInfo[u32Cnt]);

        if (pstPortInfo->bEnable == HI_TRUE
            && pstPortInfo->bConfig == HI_FALSE)
        {
            bStart = HI_TRUE;
        }
    }

    return bStart;
}
#endif

HI_S32 VPSS_CTRL_Start2DTask_First3Field(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{

#ifdef VPSS_HAL_WITH_CBB
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;

    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    pstHalInfo->enNodeType = VPSS_HAL_TASK_DETILE_FIRST3FIELD;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);

    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_DETILE_FIRST3FIELD,
                         pstInstance->abNodeVaild);
#endif
#else
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;

    pstHalInfo = &pstInstance->stVpssHalInfo;
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_DETILE_STEP1;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_DETILE_STEP1] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_DETILE_STEP1);

    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_DETILE_STEP2;
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_DETILE_STEP2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_DETILE_STEP2);
#endif
    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_GetFieldIdx(VPSS_INSTANCE_S *pstInstance)
{
    VPSS_IN_ENTITY_S *pstEntity = &(pstInstance->stInEntity);
    HI_DRV_BUF_ADDR_E enLR = HI_DRV_BUF_ADDR_LEFT;
    HI_S32 idx;
    HI_U32 u32FieldIdx;
    HI_DRV_VIDEO_FRAME_S *pstRef[4] = {HI_NULL, HI_NULL, HI_NULL, HI_NULL};
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret;

    s32Ret = VPSS_IN_GetIntf(pstEntity, &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    stInIntf.pfnGetInfo( pstEntity,
                         VPSS_IN_INFO_REF,
                         enLR,
                         (HI_VOID *)pstRef);

    u32FieldIdx = 0;
    for (idx = 2; idx >= 0; idx--) //field 0,1,2
    {
        if (pstRef[idx] != HI_NULL)
        {
            u32FieldIdx++;
        }
    }

    return u32FieldIdx;
}

HI_BOOL VPSS_CTRL_Check2DDetileStart(VPSS_INSTANCE_S *pstInstance)
{

    VPSS_IN_ENTITY_S *pstEntity;
    HI_S32 s32FieldIdx;


    pstEntity = &(pstInstance->stInEntity);


    if (pstEntity->stStreamInfo.u32StreamProg)
    {
        return HI_FALSE;
    }

    s32FieldIdx = VPSS_CTRL_GetFieldIdx(pstInstance);
    if ((0 <= s32FieldIdx) && (s32FieldIdx < 3))//field 0,1,2
    {
        pstInstance->stVpssHalInfo.u32DetileFieldIdx = s32FieldIdx;
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_VOID VPSS_CTRL_UpdateFrameIndex(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32FieldIdx;
    VPSS_IN_ENTITY_S *pstEntity = &(pstInstance->stInEntity);

    if (pstEntity->stStreamInfo.u32StreamProg)
    {
        return ;
    }

    s32FieldIdx = VPSS_CTRL_GetFieldIdx(pstInstance);
    if ((0 <= s32FieldIdx) && (s32FieldIdx < 3))//field 0,1,2
    {
        pstInstance->stVpssHalInfo.u32DetileFieldIdx = s32FieldIdx;
    }
    else if (HI_TRUE == pstEntity->stSrc.bEnding)
    {
        if (2 == pstEntity->stSrc.bEndingCompleteCnt)
        {
            pstInstance->stVpssHalInfo.u32DetileFieldIdx = VPSS_FRAME_NO_LAST2;
        }
        else if (1 == pstEntity->stSrc.bEndingCompleteCnt)
        {
            pstInstance->stVpssHalInfo.u32DetileFieldIdx = VPSS_FRAME_NO_LAST1;
        }
        else
        {
            pstInstance->stVpssHalInfo.u32DetileFieldIdx = VPSS_FRAME_NO_NORMAL;
        }
    }
    else
    {
        pstInstance->stVpssHalInfo.u32DetileFieldIdx = VPSS_FRAME_NO_NORMAL;
    }

    return ;
}
HI_VOID VPSS_CTRL_CopyWBCStatistic(VPSS_INSTANCE_S *pstInstance)
{
#ifdef VPSS_HAL_WITH_CBB
    HI_U32 u32Idx;

    if (HI_NULL != pstInstance->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr)
    {
        for (u32Idx = 0; u32Idx < VPSS_SPLIT_MAX_NODE; u32Idx++)
        {
            VPSS_SAFE_MEMCPY(&(pstInstance->stPqWbcReg[u32Idx]),
                             (HI_VOID *)
                             ((HI_ULONG)pstInstance->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr + (VPSS_WBCREG_SIZE * u32Idx)),
                             sizeof(pstInstance->stPqWbcReg[u32Idx]));
        }
    }
#else
    if (HI_NULL != pstInstance->stVpssHalInfo.pu8stt_w_vir_addr)
    {
        VPSS_SAFE_MEMCPY(&(pstInstance->stPqWbcReg),
                         (PQ_VPSS_WBC_REG_S *)pstInstance->stVpssHalInfo.pu8stt_w_vir_addr,
                         sizeof(PQ_VPSS_WBC_REG_S));
    }
#endif

    return;
}

HI_S32 VPSS_CTRL_Start2DTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;

#ifdef VPSS_HAL_WITH_CBB
    VPSS_FB_NODE_S *pstOutputInfo;
    HI_U32 PortId;
#endif



    pstHalInfo  = &(pstInstance->stVpssHalInfo);


    pstHalInfo->enNodeType = VPSS_INST_Check2DNodeType(pstInstance);

    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);

#ifdef VPSS_HAL_WITH_CBB
    for (PortId = 0; PortId < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; PortId++)
    {
        pstOutputInfo = pstInstance->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];

        if (pstInstance->stPort[PortId].bNeedRotate)
        {
            //set rotation output frame info
            if (HI_NULL != pstOutputInfo)
            {
                VPSS_INST_SetRotationOutFrameInfo(pstInstance, PortId,
                                                  &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);
            }
            else
            {
                VPSS_FATAL("pstOutputInfo is NULL! PortId:%d\n", PortId);
                // return HI_FAILURE;
            }
        }
    }

    if (VPSS_CTRL_VirtualPortLowQulity(enIp, pstInstance))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_LOWQUALITY, pstInstance->abNodeVaild);
    }
    else if ((VPSS_HAL_NODE_2D_FRAME == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_UHD == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_UHD_VIRTUAL == pstHalInfo->enNodeType))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FRAME, pstInstance->abNodeVaild);
    }
    else if ((VPSS_HAL_NODE_2D_DEI == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_SD_FIRST == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_FIELD == pstHalInfo->enNodeType)
             || (VPSS_HAL_NODE_2D_SD_SECOND == pstHalInfo->enNodeType))
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD, pstInstance->abNodeVaild);
    }
    else if (VPSS_HAL_NODE_2D_DEI_LAST_2FIELD == pstHalInfo->enNodeType)
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_LAST2FIELD, pstInstance->abNodeVaild);
    }
    else if (VPSS_HAL_NODE_HDR_DETILE_NOALG == pstHalInfo->enNodeType)
    {
        VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_HDR, pstInstance->abNodeVaild);
    }
#else
    if (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_Field)
    {
        pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD] = HI_TRUE;
        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstInstance))
        {
            pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL]
                = HI_TRUE;
            VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL);
        }
    }
    else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_FRAME
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_HIGH_SPEED
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD
             || pstHalInfo->enNodeType == VPSS_HAL_NODE_HDR_DETILE_NOALG)
    {
        pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D] = HI_TRUE;

        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstInstance))
        {
            if ((VPSS_CTRL_VirtualPortLowQulity(enIp, pstInstance))
                && (pstHalInfo->enNodeType == VPSS_HAL_NODE_2D_5Field))
            {
                pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_Field;
                pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL] = HI_TRUE;
                VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_FIELD_VIRTUAL);
            }
            else
            {
                pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_VIRTUAL] = HI_TRUE;
                VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_VIRTUAL);
            }
        }
    }
    else if (pstHalInfo->enNodeType == VPSS_HAL_NODE_UHD_SPLIT_L)
    {
        pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_SPLIT_L] = HI_TRUE;

        VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_SPLIT_L);

        if (VPSS_CTRL_CheckVirtualStart(enIp, pstInstance))
        {
            pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_FRAME;

            pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_VIRTUAL]
                = HI_TRUE;

            VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_VIRTUAL);
        }
    }

    else
    {
        VPSS_ERROR("Invalid Node Type %d\n", pstHalInfo->enNodeType);
    }
#endif

    return HI_SUCCESS;
}

HI_BOOL VPSS_CTRL_Check2DStart(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 i;




    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (pstInstance->pstFrmNode[i * 2] != HI_NULL)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}
#ifndef VPSS_HAL_WITH_CBB
HI_BOOL VPSS_CTRL_CheckRotateStart(VPSS_INSTANCE_S *pstInstance, HI_U32 PortId)
{
    VPSS_PORT_S *pstPort;
    pstPort = &(pstInstance->stPort[PortId]);

    if ((HI_DRV_VPSS_ROTATION_DISABLE == pstPort->enRotation)
        || (HI_DRV_VPSS_ROTATION_180 == pstPort->enRotation)
        || (HI_FALSE == pstPort->bEnble))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_BOOL VPSS_CTRL_CheckZME1LStart(VPSS_INSTANCE_S *pstInstance, HI_U32 PortId)
{
    VPSS_PORT_S *pstPort;
    pstPort = &(pstInstance->stPort[PortId]);

    if ((HI_TRUE == pstInstance->bZME2lTaskNeed[PortId])
        && (HI_TRUE == pstPort->bEnble)
        && (HI_NULL != pstInstance->pstFrmNodeZME1L))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

#ifdef ZME_2L_TEST
/******************************************************************************
brief      : CNcomment :  check rotate and ZME_2L task
           :  本函数功能:
              1  根据输入图像信息(解码图像)检测与判定是否需要做二级缩放及旋转操作。并记录每个port相关标志。
              2  如果需要做二级缩放(旋转)，则分配所需要的缓存图像buffer。
attention  :
param[in]  : enIp      :  vpss ID
             pstTask   :
retval     : HI_S32
see        :
author     :sdk
******************************************************************************/

HI_S32 VPSS_CTRL_Zme2lAndRotateCfg(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32  i = 0, u32DstW = 0, u32DstH = 0 , u32RotateNeed = 0;

    HI_S32 s32Ret                = HI_FAILURE;
    HI_DRV_VIDEO_FRAME_S *pstCur = HI_NULL;
    VPSS_IN_INTF_S stInIntf;

    HI_U32 u32BufSize            = 0;
    HI_U32 u32BufStride          = 0;
    HI_DRV_VIDEO_FRAME_S *pstFrm = HI_NULL;
    VPSS_BUFFER_S        *pstBuf = HI_NULL;

    VPSS_PORT_S          *pstPort[DEF_HI_DRV_VPSS_PORT_MAX_NUMBER] = {HI_NULL, HI_NULL, HI_NULL};
    HI_PQ_ZME_WIN_S      stZmeWin;

    HI_DRV_VIDEO_PRIVATE_S *pPriInfo;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;



    memset(pstInstance->bZME2lTaskNeed, 0, sizeof(HI_BOOL)*DEF_HI_DRV_VPSS_PORT_MAX_NUMBER);

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
    s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("VPSS_SRC_GetProcessImage failed!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        pstPort[i]  = &pstInstance->stPort[i];

        if ( HI_TRUE == pstPort[i]->bEnble && VPSS_INVALID_HANDLE != pstPort[i]->s32PortId )
        {
            /*  如果需要做旋转操作，则记录当前port旋转标志 并 申请相应的缓存buffer*/
            if (VPSS_CTRL_CheckRotateStart(pstInstance, i))
            {
                pstPort[i]->bNeedRotate = HI_TRUE;
                u32RotateNeed++;
                if ( HI_NULL == pstInstance->pstFrmNodeRoBuf[i])  //只分配一次缓存帧存
                {
                    pstInstance->pstFrmNodeRoBuf[i] = (VPSS_FB_NODE_S *)VPSS_VMALLOC(sizeof(VPSS_FB_NODE_S));

                    if (HI_NULL != pstInstance->pstFrmNodeRoBuf[i])
                    {
                        memset(pstInstance->pstFrmNodeRoBuf[i], 0x0, sizeof(VPSS_FB_NODE_S));
                    }
                    else
                    {
                        VPSS_ERROR("Malloc Rota FB fail\n");
                        continue;
                    }
                }

                if (HI_NULL != pstInstance->pstFrmNodeRoBuf[i])
                {
                    pstFrm = &pstInstance->pstFrmNodeRoBuf[i]->stOutFrame;
                    pstBuf = &pstInstance->pstFrmNodeRoBuf[i]->stBuffer;

                    if (pstPort[i]->s32OutputWidth != 0 && pstPort[i]->s32OutputHeight != 0)
                    {
                        pstFrm->u32Width  = pstPort[i]->s32OutputHeight;
                        pstFrm->u32Height = pstPort[i]->s32OutputWidth;
                    }
                    else
                    {
                        pPriInfo = (HI_DRV_VIDEO_PRIVATE_S *) &pstCur->u32Priv[0];
                        pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pPriInfo->u32Reserve[0]);
                        if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype  || HI_UNF_VCODEC_TYPE_AVS2 == pstVdecPriv->entype)
                            && (pstCur->enFieldMode != HI_DRV_FIELD_ALL)
                            && (pstCur->enBufValidMode == HI_DRV_FIELD_ALL))
                        {
                            pstFrm->u32Width = pstCur->u32Height * 2;
                            pstFrm->u32Height = pstCur->u32Width;
                        }
                        else
                        {
                            pstFrm->u32Width = pstCur->u32Height;
                            pstFrm->u32Height = pstCur->u32Width;
                        }
                    }

                    VPSS_OSAL_CalBufSize(&u32BufSize,
                                         &u32BufStride,
                                         pstFrm->u32Height,
                                         pstFrm->u32Width,
                                         pstPort[i]->eFormat,
                                         pstPort[i]->enOutBitWidth);

                    if ((pstBuf->stMemBuf.u32Size != u32BufSize)
                        || (pstBuf->u32Stride != u32BufStride))
                    {
                        if (pstBuf->stMemBuf.u32Size != 0)
                        {
                            VPSS_OSAL_FreeMem(&(pstBuf->stMemBuf));
                        }

                        if (!pstInstance->bSecure)
                        {
                            s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL, u32BufSize,
                                                           HI_NULL,
                                                           "VPSS_RoBuf",
                                                           &(pstBuf->stMemBuf));
                        }
                        else
                        {
                            s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_SECURE, u32BufSize,
                                                           HI_NULL,
                                                           "VPSS_RoBuf",
                                                           &(pstBuf->stMemBuf));
                        }
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_FATAL("Alloc RoBuf Failed\n");
                        }

                        pstBuf->u32Stride = u32BufStride;
                    }
                }
            }

            else
            {
                if (HI_NULL != pstInstance->pstFrmNodeRoBuf[i])
                {
                    //释放旋转内存，节省SDK空间占用
                    if (0 != pstInstance->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf.u32Size)
                    {
                        VPSS_OSAL_FreeMem(&(pstInstance->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf));
                        pstInstance->pstFrmNodeRoBuf[i]->stBuffer.stMemBuf.u32Size = 0;
                        pstInstance->pstFrmNodeRoBuf[i]->stBuffer.u32Stride = 0;
                    }

                    VPSS_VFREE(pstInstance->pstFrmNodeRoBuf[i]);
                    pstInstance->pstFrmNodeRoBuf[i] = HI_NULL;
                }
            }
        }
    }

    if ( u32RotateNeed > 0) //如果有旋转任务，则不再做二级缩放
    {
        return HI_SUCCESS;
    }

    stZmeWin.stPort0Win.u32Width = pstPort[0]->s32OutputWidth;
    stZmeWin.stPort0Win.u32Height = pstPort[0]->s32OutputHeight;

    stZmeWin.stPort1Win.u32Width = pstPort[1]->s32OutputWidth;
    stZmeWin.stPort1Win.u32Height = pstPort[1]->s32OutputHeight;

    if (  0 != u32DstW && 0 != u32DstH) //只分配一次缓存帧存

    {
        if (HI_NULL == pstInstance->pstFrmNodeZME1L) //只分配一次缓存帧存
        {
            pstInstance->pstFrmNodeZME1L = (VPSS_FB_NODE_S *)VPSS_VMALLOC(sizeof(VPSS_FB_NODE_S));
            if (HI_NULL != pstInstance->pstFrmNodeZME1L)
            {
                memset(pstInstance->pstFrmNodeZME1L, 0x0, sizeof(VPSS_FB_NODE_S));
            }
            else
            {
                VPSS_ERROR("Malloc ZME1L FB fail\n");
                return HI_FAILURE;
            }
        }

        if ( HI_NULL != pstInstance->pstFrmNodeZME1L)
        {
            pstFrm = &pstInstance->pstFrmNodeZME1L->stOutFrame;
            pstBuf = &pstInstance->pstFrmNodeZME1L->stBuffer;

            pstFrm->u32Width    = u32DstW;
            pstFrm->u32Height   = u32DstH;

            VPSS_OSAL_CalBufSize(&u32BufSize,
                                 &u32BufStride,
                                 pstFrm->u32Height,
                                 pstFrm->u32Width,
                                 HI_DRV_PIX_FMT_NV21,
                                 HI_DRV_PIXEL_BITWIDTH_10BIT);

            if ((pstBuf->stMemBuf.u32Size != u32BufSize)
                || (pstBuf->u32Stride != u32BufStride))
            {
                if (pstBuf->stMemBuf.u32Size != 0)
                {
                    VPSS_OSAL_FreeMem(&(pstBuf->stMemBuf));
                }
                if (!pstInstance->bSecure)
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_NORMAL, u32BufSize,
                                                   "VPSS_ZME1LBuf",
                                                   HI_NULL,
                                                   &(pstBuf->stMemBuf));
                }
                else
                {
                    s32Ret = VPSS_OSAL_AllocateMem(VPSS_MEM_FLAG_SECURE, u32BufSize,
                                                   "VPSS_ZME1LBuf",
                                                   HI_NULL,
                                                   &(pstBuf->stMemBuf));
                }
                if (s32Ret != HI_SUCCESS)
                {
                    VPSS_FATAL("Alloc ZME1LBuf Failed\n");
                }

                pstBuf->u32Stride = u32BufStride;
            }
        }
    }
    else
    {
        if ( HI_NULL != pstInstance->pstFrmNodeZME1L)
        {
            //释放二级缩放内存，节省SDK空间占用
            if (0 != pstInstance->pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size)
            {
                VPSS_OSAL_FreeMem(&(pstInstance->pstFrmNodeZME1L->stBuffer.stMemBuf));
                pstInstance->pstFrmNodeZME1L->stBuffer.stMemBuf.u32Size = 0;
                pstInstance->pstFrmNodeZME1L->stBuffer.u32Stride = 0;

                VPSS_VFREE(pstInstance->pstFrmNodeZME1L);
                pstInstance->pstFrmNodeZME1L = HI_NULL;
            }
        }
    }

    return s32Ret;
}


HI_S32 VPSS_CTRL_StartZME2LTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance, HI_U32 PortId)
{
    VPSS_HAL_INFO_S *pstHalInfo;

    HI_DRV_VIDEO_FRAME_S *pstInputFrame;
    VPSS_FB_NODE_S *pstOutputInfo;


    pstHalInfo  = &(pstInstance->stVpssHalInfo);


    //set ZME_2L input frame info
    pstInputFrame = &(pstInstance->pstFrmNodeZME1L->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);

    //set ZME_2L output frame info
    pstOutputInfo = pstInstance->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];
    VPSS_INST_SetOutFrameInfo(pstInstance, PortId, &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);
    VPSS_INST_SetHalFrameInfo(&pstOutputInfo->stOutFrame, &pstHalInfo->astPortInfo[PortId].stOutInfo, HI_DRV_BUF_ADDR_LEFT);

    VPSS_INST_GetInCrop(pstInstance, PortId, &pstHalInfo->astPortInfo[PortId].stInCropRect);

    VPSS_INST_GetVideoRect(pstInstance, PortId, &pstHalInfo->astPortInfo[PortId].stInCropRect,
                           &pstHalInfo->astPortInfo[PortId].stVideoRect,
                           &pstHalInfo->astPortInfo[PortId].stOutCropRect);

    pstHalInfo->enNodeType = VPSS_HAL_NODE_ZME_2L;
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_P0_ZME_L2 + PortId] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_ZME_L2 + PortId);
    return HI_SUCCESS;
}
#endif

HI_S32 VPSS_CTRL_StartRotateTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance, HI_U32 PortId)
{
    VPSS_HAL_INFO_S *pstHalInfo;

    HI_DRV_VIDEO_FRAME_S *pstInputFrame;
    VPSS_FB_NODE_S *pstOutputInfo;


    pstHalInfo  = &(pstInstance->stVpssHalInfo);


#ifdef ZME_2L_TEST
    //set rotation input frame info
    pstInputFrame = &(pstInstance->pstFrmNodeRoBuf[PortId]->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);
#else
    //set rotation input frame info
    pstInputFrame = &(pstInstance->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT]->stOutFrame);
    VPSS_INST_SetHalFrameInfo(pstInputFrame, &pstHalInfo->stInInfo, HI_DRV_BUF_ADDR_LEFT);

#endif

    //set rotation output frame info
    pstOutputInfo = pstInstance->pstFrmNode[PortId * 2 + HI_DRV_BUF_ADDR_LEFT];
    VPSS_INST_SetRotationOutFrameInfo(pstInstance, PortId,
                                      &pstOutputInfo->stBuffer, &pstOutputInfo->stOutFrame, HI_DRV_BUF_ADDR_LEFT);

    if ((HI_DRV_VPSS_ROTATION_90 == pstInstance->stPort[PortId].enRotation)
        || (HI_DRV_VPSS_ROTATION_270 == pstInstance->stPort[PortId].enRotation))
    {
        pstOutputInfo->stOutFrame.stLbxInfo.s32X =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Y;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Y =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32X;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Width =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Height;
        pstOutputInfo->stOutFrame.stLbxInfo.s32Height =
            pstHalInfo->astPortInfo[PortId].stVideoRect.s32Width;
    }
    else
    {
        memcpy(&(pstOutputInfo->stOutFrame.stLbxInfo),
               &(pstHalInfo->astPortInfo[PortId].stVideoRect),
               sizeof(HI_RECT_S));
    }

    VPSS_INST_SetHalFrameInfo(&pstOutputInfo->stOutFrame,
                              &pstHalInfo->astPortInfo[PortId].stOutInfo, HI_DRV_BUF_ADDR_LEFT);

    //rotation Y
    pstHalInfo->enNodeType = VPSS_HAL_NODE_ROTATION_Y;
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_P0_RO_Y + PortId * 2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_RO_Y + PortId * 2);

    //rotation C
    pstHalInfo->enNodeType = VPSS_HAL_NODE_ROTATION_C;
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_P0_RO_C + PortId * 2] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_P0_RO_C + PortId * 2);

    return HI_SUCCESS;
}

#endif
HI_S32 VPSS_CTRL_Start3DTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;



    pstHalInfo  = &(pstInstance->stVpssHalInfo);


    pstHalInfo->enNodeType = VPSS_INST_Check3DNodeType(pstInstance);

    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_RIGHT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);

#ifndef VPSS_HAL_WITH_CBB
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_3D_R] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_3D_R);
#else
    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_3D, pstInstance->abNodeVaild);
#endif
    return HI_SUCCESS;
}

HI_BOOL VPSS_CTRL_Check3DStart(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 i;

    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (pstInstance->pstFrmNode[i * 2 + 1] != HI_NULL)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

HI_S32 VPSS_CTRL_GetOutBufferRect(HI_RECT_S stOriRect, HI_RECT_S *pstRevisedRect)
{
    HI_U32 u32OriW = 0, u32OriH = 0;
    HI_U32 u32DstW = 0, u32DstH = 0;
    HI_U32 u32RatioW;
    HI_U32 u32RatioH;
    HI_U32 u32TmpH;
    HI_U32 u32TmpW;
    HI_U32 u32WidthLevel;
    HI_U32 u32HeightLevel;

    u32WidthLevel = 3840;
    u32HeightLevel = 2160;

    u32OriW = stOriRect.s32Width;
    u32OriH = stOriRect.s32Height;

    if (u32OriW < u32WidthLevel && u32OriH < u32HeightLevel)
    {
        u32DstW = u32OriW;
        u32DstH = u32OriH;
    }
    else if (u32OriW >= u32WidthLevel && u32OriH >= u32HeightLevel)
    {
        u32DstW = u32WidthLevel;
        u32DstH = u32HeightLevel;
    }
    else
    {
        u32RatioW = u32OriW * 2048 / u32WidthLevel;
        u32RatioH = u32OriH * 2048 / u32HeightLevel;

        VPSS_CHECK_ZERO_RETURN_FAILURE(u32RatioW);
        VPSS_CHECK_ZERO_RETURN_FAILURE(u32RatioH);

        if (u32RatioW > u32RatioH)
        {
            u32TmpW = u32OriW * 2048 / u32RatioW;
            u32TmpH = u32OriH * 2048 / u32RatioW;
        }
        else
        {
            u32TmpW = u32OriW * 2048 / u32RatioH;
            u32TmpH = u32OriH * 2048 / u32RatioH;
        }

        VPSS_PIXLE_DOWNALIGN_W(u32TmpW, HI_FALSE);
        VPSS_PIXLE_DOWNALIGN_H(u32TmpH, HI_FALSE);

        u32DstW = u32TmpW;
        u32DstH = u32TmpH;
    }

    pstRevisedRect->s32Width = u32DstW;
    pstRevisedRect->s32Height = u32DstH;

    return HI_SUCCESS;
}

#ifdef VPSS_SUPPORT_OUT_TUNNEL
HI_VOID VPSS_CTRL_UpdateLowDelayFlag(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_BOOL bLowDelayTask = HI_FALSE;
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage = HI_NULL;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_U32 u32EnablePort = 0;
    HI_BOOL bRotation = HI_FALSE;

    //pstInstance is not null certainly

    (HI_VOID)VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);

    if (HI_NULL == stInIntf.pfnGetProcessImage)
    {
        return;
    }
    (HI_VOID)stInIntf.pfnGetProcessImage(&(pstInstance->stInEntity),
                                         &pstImage);
    if (HI_NULL == pstImage)
    {
        return;
    }

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstInstance)->stPort[u32Count]);
        if (pstPort->bEnble)
        {
            u32EnablePort++;

            if ((pstPort->enRotation != HI_DRV_VPSS_ROTATION_DISABLE)
                || (pstPort->bHoriFlip == HI_TRUE)
                || (pstPort->bVertFlip == HI_TRUE))
            {
                bRotation = HI_TRUE;
            }

            if (pstPort->bTunnelEnable)
            {
                bLowDelayTask = HI_TRUE;
            }
        }
    }

    if (pstImage->u32Width > 1920)
    {
        bLowDelayTask = HI_FALSE;
    }

    if (pstImage->bSecure)
    {
        bLowDelayTask = HI_FALSE;
    }

    if (pstImage->eFrmType != HI_DRV_FT_NOT_STEREO)
    {
        bLowDelayTask = HI_FALSE;
    }

    if (pstImage->u32Circumrotate != 0)
    {
        bLowDelayTask = HI_FALSE;
    }

    if (u32EnablePort > 1 || bRotation == HI_TRUE)
    {
        bLowDelayTask = HI_FALSE;
    }

    pstInstance->bOutLowDelay = bLowDelayTask;

    return;
}
#endif

HI_S32 VPSS_CTRL_GetOutBuffer(VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32StoreH;
    HI_U32 u32StoreW;
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VPSS_BUFLIST_CFG_S  *pstBufListCfg;
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage = HI_NULL;
    HI_U32 u32ExtBufSize;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;


    /*
        get the image info to  inform user out buffer size
    */
    (HI_VOID)VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    (HI_VOID)stInIntf.pfnGetProcessImage(&(pstInstance->stInEntity),
                                         &pstImage);
    if (HI_NULL == pstImage)
    {
        VPSS_FATAL("Get image fail!!!\n");
        return HI_FAILURE;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    /***********config out buffer************************/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstInstance)->stPort[u32Count]);
        pstBufListCfg = &(pstPort->stFrmInfo.stBufListCfg);

        if (pstPort->s32PortId != VPSS_INVALID_HANDLE &&
            pstPort->bEnble == HI_TRUE)
        {
            if (pstPort->s32OutputHeight == 0 && pstPort->s32OutputWidth == 0)
            {
                HI_RECT_S stInRect;
                VPSS_INST_GetInCrop(pstInstance, u32Count, &stInRect);
                u32StoreW = (HI_U32)stInRect.s32Width;
                u32StoreH = (HI_U32)stInRect.s32Height;

                //u32StoreH = pstStreamInfo->u32StreamH;
                //u32StoreW = pstStreamInfo->u32StreamW;
            }
            else
            {
                if (pstBufListCfg->eBufType != HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
                {
                    u32StoreH = pstPort->s32OutputHeight;
                    u32StoreW = pstPort->s32OutputWidth;
                }
                else
                {
                    HI_RECT_S stInRect;
                    HI_RECT_S stBufferRect;
                    VPSS_INST_GetInCrop(pstInstance, u32Count, &stInRect);

                    VPSS_CTRL_GetOutBufferRect(stInRect, &stBufferRect);

                    u32StoreW = (HI_U32)stBufferRect.s32Width;
                    u32StoreH = (HI_U32)stBufferRect.s32Height;
                }
            }

            if (VPSS_HDR_TYPE_NEED_TRANS_METADATA(pstImage->enSrcFrameType))
            {
                u32ExtBufSize = 4096;//pstImage->unHDRInfo.stDolbyInfo.stMetadata.u32Length;
            }
            else
            {
                u32ExtBufSize = 0;
            }

            if (pstPriv->u32LastFlag == DEF_HI_DRV_VPSS_LAST_FRAME_FLAG)
            {
                pstPort->bCurDropped = HI_FALSE;
            }
            else
            {
                pstPort->bCurDropped = VPSS_INST_CheckIsDropped(pstInstance,
                                       pstPort->u32MaxFrameRate,
                                       pstPort->u32OutCount);
            }
            if (pstPort->bCurDropped == HI_FALSE)
            {
                /*2D image -> 1 outFrame 1 buffer*/
                if (pstImage->eFrmType == HI_DRV_FT_NOT_STEREO
                    || pstPort->b3Dsupport == HI_FALSE)
                {
                    pstInstance->pstFrmNode[u32Count * 2] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstInstance->bSecure,
                                               u32ExtBufSize);
                    pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
                }
                /*3D image -> 1 outFrame 2 buffer*/
                else
                {
                    pstInstance->pstFrmNode[u32Count * 2] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstInstance->bSecure,
                                               u32ExtBufSize);
                    pstInstance->pstFrmNode[u32Count * 2 + 1] =
                        VPSS_FB_GetEmptyFrmBuf(&(pstPort->stFrmInfo),
                                               u32StoreH, u32StoreW,
                                               pstPort->eFormat,
                                               pstPort->enOutBitWidth,
                                               pstInstance->bSecure,
                                               u32ExtBufSize);
                    if (pstInstance->pstFrmNode[u32Count * 2] == HI_NULL
                        || pstInstance->pstFrmNode[u32Count * 2 + 1] == HI_NULL)
                    {

                        if (pstInstance->pstFrmNode[u32Count * 2] != HI_NULL)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstInstance->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                        }

                        if (pstInstance->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstInstance->pstFrmNode[u32Count * 2 + 1],
                                                   VPSS_FB_TYPE_NORMAL);
                        }
                        pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
                        pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
                    }
                }


                if (pstBufListCfg->eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
                {
                    /*************************/

                    if (pstPort->eFormat == HI_DRV_PIX_FMT_NV12
                        || pstPort->eFormat == HI_DRV_PIX_FMT_NV21)
                    {
                        pstBufListCfg->u32BufStride = (u32StoreW + 0xf) & 0xfffffff0 ;
                        pstBufListCfg->u32BufSize =
                            pstBufListCfg->u32BufStride * u32StoreH * 3 / 2;
                    }
                    else if (pstPort->eFormat == HI_DRV_PIX_FMT_NV16_2X1
                             || pstPort->eFormat == HI_DRV_PIX_FMT_NV61_2X1)
                    {
                        pstBufListCfg->u32BufStride =  (u32StoreW + 0xf) & 0xfffffff0 ;
                        pstBufListCfg->u32BufSize =
                            pstBufListCfg->u32BufStride * u32StoreH * 2;
                    }
                    else
                    {
                        VPSS_FATAL("Port %x OutFormat%d isn't supported.\n",
                                   pstPort->s32PortId, pstPort->eFormat);
                    }
                    /*************************/
                    if (pstInstance->pstFrmNode[u32Count * 2] != HI_NULL)
                    {
                        s32Ret = VPSS_INST_GetFrmBuffer(pstInstance, pstPort->s32PortId, pstBufListCfg,
                                                        &(pstInstance->pstFrmNode[u32Count * 2]->stBuffer), u32StoreH, u32StoreW);
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_WARN("VPSS_INST_GetFrmBuffer fail\n");
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstInstance->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                            if (pstInstance->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                            {
                                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                       pstInstance->pstFrmNode[u32Count * 2 + 1],
                                                       VPSS_FB_TYPE_NORMAL);
                            }
                            pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
                            pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
                            return HI_FAILURE;
                        }
                    }

                    if (pstInstance->pstFrmNode[u32Count * 2 + 1] != HI_NULL)
                    {
                        s32Ret = VPSS_INST_GetFrmBuffer(pstInstance, pstPort->s32PortId, pstBufListCfg,
                                                        &(pstInstance->pstFrmNode[u32Count * 2 + 1]->stBuffer), u32StoreH, u32StoreW);
                        if (s32Ret != HI_SUCCESS)
                        {
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstInstance->pstFrmNode[u32Count * 2],
                                                   VPSS_FB_TYPE_NORMAL);
                            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                                   pstInstance->pstFrmNode[u32Count * 2 + 1],
                                                   VPSS_FB_TYPE_NORMAL);
                            pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
                            pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;

                            return HI_FAILURE;
                        }
                    }
                }
                else
                {

                }
            }
            else
            {
                pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
                pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
            }
        }
        else
        {
            pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
            pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
        }
    }

    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER * 2; u32Count++)
    {
        if (pstInstance->pstFrmNode[u32Count] != HI_NULL)
        {
            s32Ret = HI_SUCCESS;
            break;
        }
    }

    if (s32Ret == HI_SUCCESS)
    {
        for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
        {
            pstPort = &(pstInstance->stPort[u32Count]);
            if (pstPort->bEnble == HI_TRUE)
            {
                pstPort->u32OutCount++;
            }
        }
    }

    return s32Ret;

}

HI_S32 VPSS_CTRL_TaskFlag(VPSS_IP_E enIp, VPSS_INSTANCE_STATE_E enState)
{
    HI_S32 s32Index;
    VPSS_INST_CTRL_S  *pstInstCtrlInfo;
    unsigned long  u32LockFlag;
    VPSS_INSTANCE_S *pstInstance;

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);

    for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
    {
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if (HI_NULL == pstInstance)
        {
            continue;
        }

        VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
        if ((pstInstance->enState >= INSTANCE_STATE_RUNNING) && (pstInstance->enState < INSTANCE_STATE_END))
        {
            if (INSTANCE_STATE_END == enState)
            {
                if (pstInstance->bOutLowDelay)
                {
                    if (INSTANCE_STATE_WAITEND == pstInstance->enState)
                    {
                        pstInstance->bNeedSendOutFrame = HI_FALSE;
                    }
                    if (INSTANCE_STATE_TUNNELOUT == pstInstance->enState)
                    {
                        pstInstance->bNeedSendOutFrame = HI_TRUE;
                    }
                }
                else
                {
                    pstInstance->bNeedSendOutFrame = HI_TRUE;
                }
                VPSS_NEXT_STATE(pstInstance, enState);
            }
            else
            {
                VPSS_NEXT_STATE(pstInstance, enState);
            }
            VPSS_TUNNEL_DBG_INFO("set inst %d state %d\n", pstInstance->ID, enState);
        }
        VPSS_OSAL_UpLock(&(pstInstance->stInstLock));

    }

    return HI_SUCCESS;
}

#ifdef VPSS_SUPPORT_OUT_TUNNEL
HI_S32 VPSS_CTRL_TaskFlagTunnel(VPSS_IP_E enIp, VPSS_INSTANCE_STATE_E enState)
{
    HI_S32 s32Index;
    VPSS_INST_CTRL_S  *pstInstCtrlInfo;
    unsigned long  u32LockFlag;
    VPSS_INSTANCE_S *pstInstance;

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);

    for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
    {
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        //high No. inst will tunnelout firstly
        pstInstance = pstInstCtrlInfo->pstInstPool[VPSS_INSTANCE_MAX_NUMB - s32Index - 1];
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if (HI_NULL == pstInstance)
        {
            continue;
        }

        VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
        if ((pstInstance->enState == INSTANCE_STATE_RUNNING) && (HI_TRUE == pstInstance->bOutLowDelay))
        {
            VPSS_NEXT_STATE(pstInstance, enState);
            pstInstance->bNeedSendOutFrame = HI_TRUE;
            VPSS_TUNNEL_DBG_INFO("(T)set inst %d state %d\n", pstInstance->ID, enState);
            VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
            break;
        }
        VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
    }

    return HI_SUCCESS;
}
#endif


HI_BOOL VPSS_CTRL_Check2DH265InterlaceStart(VPSS_INSTANCE_S *pstInstance)
{
    VPSS_IN_INTF_S stInIntf = {0};
    HI_DRV_VIDEO_FRAME_S *pstImage;
    HI_DRV_VIDEO_PRIVATE_S *pPriInfo;
    HI_VDEC_PRIV_FRAMEINFO_S *pstVdecPriv;
    VPSS_HAL_INFO_S *pstHalInfo;



    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    VPSS_CHECK_NULL(pstInstance);

    (HI_VOID)VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);

    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    (HI_VOID)stInIntf.pfnGetProcessImage(&(pstInstance->stInEntity),
                                         &pstImage);

    pPriInfo = (HI_DRV_VIDEO_PRIVATE_S *) & (pstImage->u32Priv[0]);
    pstVdecPriv = (HI_VDEC_PRIV_FRAMEINFO_S *) & (pPriInfo->u32Reserve[0]);
    if ((HI_UNF_VCODEC_TYPE_HEVC == pstVdecPriv->entype  || HI_UNF_VCODEC_TYPE_AVS2 == pstVdecPriv->entype)
        && (!pstImage->bProgressive)
        && pstImage->enBufValidMode == HI_DRV_FIELD_ALL)
    {
        VPSS_DBG_INFO("Start H265Interlace task...\n");
        return HI_TRUE;
    }
    else
    {
        pstInstance->stVpssHalInfo.pstH265RefList = HI_NULL;
        VPSS_HAL_H265RefListDeInit(&pstInstance->stH265RefList);
        return HI_FALSE;
    }
}
HI_S32 VPSS_CTRL_Start2DTask_H265(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;



    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    pstHalInfo->pstH265RefList = &pstInstance->stH265RefList;
    if ((pstInstance->stInEntity.stStreamInfo.u32IsNewImage) || (!pstHalInfo->pstH265RefList->bRefListValid))
    {
        pstHalInfo->pstH265RefList = &pstInstance->stH265RefList;
        VPSS_HAL_H265RefListInit(pstHalInfo->pstH265RefList,
                                 pstInstance->stInEntity.stStreamInfo.u32StreamW,
                                 pstInstance->stInEntity.stStreamInfo.u32StreamH,
                                 pstInstance->stPort[0].eFormat,
                                 pstInstance->bSecure);
    }
#ifdef VPSS_HAL_WITH_CBB
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);

    VPSS_HAL_SetTaskInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_H265_DEI, pstInstance->abNodeVaild);

#else
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP1_INTERLACE;
    s32Ret = VPSS_CTRL_FixTask(enIp, HI_DRV_BUF_ADDR_LEFT, pstInstance);
    HI_ASSERT(s32Ret != HI_FAILURE);
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_H265_STEP1_INTERLACE] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_H265_STEP1_INTERLACE);
    pstHalInfo->enNodeType = VPSS_HAL_NODE_2D_H265_STEP2_DEI;
    pstInstance->abNodeVaild[VPSS_HAL_TASK_NODE_2D_H265_STEP2_DEI] = HI_TRUE;
    VPSS_HAL_SetNodeInfo(enIp, pstHalInfo, VPSS_HAL_TASK_NODE_2D_H265_STEP2_DEI);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_CfgTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 i;
    HI_BOOL bStart2D = HI_TRUE;
    HI_BOOL bStart3D = HI_FALSE;
    HI_S32 s32Ret = HI_SUCCESS;

    /* 所有节点都置为HI_FALSE */
#ifdef VPSS_HAL_WITH_CBB
    for (i = 0; i < VPSS_HAL_NODE_BUTT; i++)
    {
        pstInstance->abNodeVaild[i] = HI_FALSE;
    }
#else
    for (i = 0; i < VPSS_HAL_TASK_NODE_BUTT; i++)
    {
        pstInstance->abNodeVaild[i] = HI_FALSE;
    }
#endif

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->u32LogicTimeoutCnt++;
#endif
#if defined(CHIP_TYPE_hi3798cv200)
#ifdef ZME_2L_TEST
    s32Ret = VPSS_CTRL_Zme2lAndRotateCfg(enIp, pstInstance);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Check ZME_2L Failed\n");
        return s32Ret;
    }
#endif
#endif

    if (VPSS_CTRL_Check2DH265InterlaceStart(pstInstance))
    {
        s32Ret = VPSS_CTRL_Start2DTask_H265(enIp, pstInstance);
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_ERROR("Start VPSS_CTRL_Start2DTask_H265 Task Failed\n");
            return s32Ret;
        }
    }
#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    else if (VPSS_CTRL_Check2DDetileStart(pstInstance))
    {
        s32Ret = VPSS_CTRL_Start2DTask_First3Field(enIp, pstInstance);
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_ERROR("Start VPSS_CTRL_Start2DTask_First3Field Task Failed\n");
            return s32Ret;
        }
    }
#endif
    else
    {
        bStart2D = VPSS_CTRL_Check2DStart(pstInstance);
        if (bStart2D)
        {
            VPSS_CTRL_UpdateFrameIndex(pstInstance);
            s32Ret = VPSS_CTRL_Start2DTask(enIp, pstInstance);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_ERROR("Start 2D Task Failed\n");
                return s32Ret;
            }
        }
    }
#if defined(CHIP_TYPE_hi3798cv200)
#ifdef ZME_2L_TEST
    //ZME_2L
    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if ( VPSS_CTRL_CheckRotateStart(pstInstance, i) )
        {
            VPSS_CTRL_StartRotateTask(enIp, pstInstance, i);
        }
        else  if ( VPSS_CTRL_CheckZME1LStart(pstInstance, i) )
        {
            VPSS_CTRL_StartZME2LTask(enIp, pstInstance, i);
        }
        else
        {
        }
    }
#else
    //rotate
    for (i = 0; i < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; i++)
    {
        if (VPSS_CTRL_CheckRotateStart(pstInstance, i))
        {
            VPSS_CTRL_StartRotateTask(enIp, pstInstance, i);
        }
        else
        {
            //释放旋转内存，节省SDK空间占用
            if (0 != g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf.u32Size)
            {
                VPSS_OSAL_FreeMem(&(g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf));
                g_stVpssCtrl[enIp].stRoBuf[i].stMemBuf.u32Size = 0;
            }
        }
    }
#endif
#endif
    bStart3D = VPSS_CTRL_Check3DStart(pstInstance);
    if (bStart3D)
    {
        (HI_VOID)VPSS_CTRL_Start3DTask(enIp, pstInstance);
    }

    return s32Ret;

}


HI_S32 VPSS_CTRL_StartTask(VPSS_IP_E enIp)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 enId = 0;
    HI_U32 i = 0;
    S_VPSS_REGS_TYPE *pstVpssNode = HI_NULL;  //DDR中节点首地址
    S_VPSS_REGS_TYPE *pstVpssLogic = HI_NULL;      //逻辑虚拟基地址
    VPSS_INSTANCE_S *pstInstance = HI_NULL;
    VPSS_HAL_INFO_S *pstVpssHalInfo = HI_NULL;
    HI_S32 s32Index = 0;
    VPSS_INST_CTRL_S  *pstInstCtrlInfo = HI_NULL;
    unsigned long  u32LockFlag;
    VPSS_HAL_CTX_S *pstHalCtx = HI_NULL;
    HI_U32 *pu32HeaderNodePhyAddr = HI_NULL;
    HI_U32 *pu32PreNodePhyAddr = HI_NULL;
    HI_BOOL bReadyRun = HI_FALSE;
    HI_BOOL bResetEveryFrame = HI_TRUE;
    VPSS_CTRL_S *pstVpssCtrl = HI_NULL;

    pstVpssCtrl = &(g_stVpssCtrl[enIp]);
    pstVpssCtrl->s32RunInstCnt = 0;
    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    pu32PreNodePhyAddr = 0x0;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    pstVpssCtrl->s32OutTunelInstanceCnt = 0;
#endif


    for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
    {
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

        if ((pstInstance == HI_NULL) || (pstInstance->enState != INSTANCE_STATE_READY))
        {
            if (pstInstance != HI_NULL)
            {
                //any one of insts disable reset-perframe, logic reset will be disabled.
                if (HI_FALSE == pstInstance->stDbgCtrl.stInstDbg.bResetPerFrame)
                {
                    bResetEveryFrame = HI_FALSE;
                }
            }
            continue;
        }
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->aulLogicStartTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif

        //each instance
        pstHalCtx = &stHalCtx[enIp][s32Index];
        pstVpssHalInfo = &(pstInstance->stVpssHalInfo);

        if (pstVpssHalInfo->u32NodeCount < 1)
        {
            VPSS_ERROR("Invalid node count! Inst:%d count:%d\n",
                       pstInstance->ID, pstVpssHalInfo->u32NodeCount);
            VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_FAIL);
            continue;
        }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
        if (pstInstance->bOutLowDelay)
        {
            pstVpssCtrl->s32OutTunelInstanceCnt++;
        }
#endif

        for (i = 0; i < pstVpssHalInfo->u32NodeCount; i++)
        {
            enId = pstVpssHalInfo->u32NodeCount - 1 - i;
            if (HI_NULL != pstVpssHalInfo->stNodeList[enId].pu8AppVir)
            {
                pstVpssNode = (S_VPSS_REGS_TYPE *)pstVpssHalInfo->stNodeList[enId].pu8AppVir;
                VPSS_DRV_Set_VPSS_PNEXT(pstVpssNode, pu32PreNodePhyAddr);
                pu32HeaderNodePhyAddr = (HI_U32 *)((unsigned long)(pstVpssHalInfo->stNodeList[enId].u32AppPhy));
                pu32PreNodePhyAddr = (HI_U32 *)((unsigned long)(pstVpssHalInfo->stNodeList[enId].u32AppPhy));

                bReadyRun = HI_TRUE;
            }
        }
        pstInstance->bNeedSendOutFrame = HI_FALSE;
        VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_RUNNING);
        pstVpssCtrl->s32RunInstCnt++;
        pstInstance->au32RunOrder[pstInstance->u32TimeStampIndex] = pstVpssCtrl->s32RunInstCnt;
    }


    if (HI_TRUE == bReadyRun)
    {
#ifdef VPSS_SUPPORT_OUT_TUNNEL
        pstVpssCtrl->bLogicDone = HI_FALSE;
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
        pstVpssCtrl->s32OutTunnelCntDbg = 0;
        pstVpssCtrl->s32OutTunnelIntCntDbg = 0;
        pstVpssCtrl->s32OutTunelEvtCreateCntDbg = 0;
        pstVpssCtrl->s32OutTunelEvtDoneCntDbg = 0;
        pstVpssCtrl->s32OutTunelEvtResetCntDbg = 0;
#endif
        {
            unsigned long flags;
            VPSS_OSAL_DownSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);
            pstVpssCtrl->s32OutTunnelInterruptCnt = 0;
            VPSS_OSAL_UpSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);
        }
#endif
        VPSS_HAL_SetClockEn(enIp, HI_TRUE);

        s32Ret = VPSS_HAL_CfgAXI(enIp);
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_FATAL("VPSS_HAL_CfgAXI fail, ret:%d\n", s32Ret);
            return s32Ret;
        }

        pstVpssLogic = (S_VPSS_REGS_TYPE *)pstHalCtx->pu8BaseRegVir;
        VPSS_DRV_Set_VPSS_PNEXT(pstVpssLogic, pu32HeaderNodePhyAddr);
        VPSS_DRV_Set_VPSS_START(pstVpssLogic);


        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

            if ((pstInstance == HI_NULL) || (pstInstance->enState != INSTANCE_STATE_RUNNING))
            {
                continue;
            }

            pstVpssHalInfo = &(pstInstance->stVpssHalInfo);

            for (enId = pstVpssHalInfo->u32NodeCount; enId < VPSS_HAL_NODE_BUTT; enId++)
            {
                if ((0x0 != pstVpssHalInfo->stNodeList[enId].u32AppPhy)
                    && (HI_NULL != pstVpssHalInfo->stNodeList[enId].pu8AppVir))
                {
                    VPSS_INFO("Free node: inst:%d nodeidx:%d phy:%#x vir:%p\n",
                              pstVpssHalInfo->s32InstanceID,
                              enId,
                              pstVpssHalInfo->stNodeList[enId].u32AppPhy,
                              pstVpssHalInfo->stNodeList[enId].pu8AppVir);

                    HI_DRV_MMZ_UnmapAndRelease(&(pstVpssHalInfo->stNodeList[enId].stRegBuf));
                    memset(&(pstVpssHalInfo->stNodeList[enId].stRegBuf), 0, sizeof(MMZ_BUFFER_S));
                    pstVpssHalInfo->stNodeList[enId].u32AppPhy = 0x0;
                    pstVpssHalInfo->stNodeList[enId].pu8AppVir = HI_NULL;
                    pstVpssHalInfo->stNodeList[enId].u32NodeId = VPSS_HAL_NODE_BUTT;
                }
                else if ((0x0 == pstVpssHalInfo->stNodeList[enId].u32AppPhy)
                         && (HI_NULL == pstVpssHalInfo->stNodeList[enId].pu8AppVir))
                {
                }
                else
                {
                    VPSS_ERROR("Invalid addr phy:%#x vir:%p\n",
                               pstVpssHalInfo->stNodeList[enId].u32AppPhy,
                               pstVpssHalInfo->stNodeList[enId].pu8AppVir);
                }
            }

            pstVpssHalInfo->u32NodeCount = 0;
            s32Ret = HI_SUCCESS;
        }
    }
    else
    {
        if (HI_TRUE == bResetEveryFrame)
        {
            VPSS_HAL_SetClockEn(enIp, HI_FALSE);
        }

        s32Ret = HI_FAILURE;
    }
    return s32Ret;
}


HI_S32 VPSS_CTRL_GetRwzbData(VPSS_IP_E enIP, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_RWZB_S *pstRwzb;
    VPSS_HAL_INFO_S *pstHalInfo;

    pstHalInfo  = &(pstInstance->stVpssHalInfo);

    pstRwzb = &(pstInstance->stRwzbInfo);

    for (u32Count = 0; u32Count < 6 ; u32Count ++)
    {
#ifndef VPSS_HAL_WITH_CBB
        /*pu8stt_w_vir_addr not malloc when 4K*/
        if ((pstHalInfo->stInInfo.u32Width <= VPSS_FHD_WIDTH)
            && (HI_NULL != pstHalInfo->pu8stt_w_vir_addr))
        {
            VPSS_HAL_GetDetPixel((HI_U32 *)pstHalInfo->pu8stt_w_vir_addr, u32Count, &(pstRwzb->u8RwzbData[u32Count][0]));
        }
#else
        VPSS_HAL_GetDetPixel(&(pstRwzb->u8RwzbData[u32Count][0]), &(pstHalInfo->stRwzbInfo.u8Data[u32Count][0]));
#endif
    }

    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_UpdatePqWbcData(VPSS_INSTANCE_S *pstInstance, PQ_VPSS_WBC_REG_S *pstLocalWbcReg)
{
    HI_PQ_WBC_INFO_S stPqWbcInfo;
    HI_S32 s32Ret = HI_FAILURE;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_IN_ENTITY_S *pstEntity;
    VPSS_SRC_S *pstSrc;
    VPSS_IN_STREAM_INFO_S *pstStreamInfo;

    VPSS_IN_INTF_S stInIntf;
#if defined(CHIP_TYPE_hi3798cv200)
    HI_U32 u32BaseRegPhyAddr;
    HI_U8 *pu8BaseRegVirAddr;
#endif

    if ( HI_NULL == pstLocalWbcReg)
    {
        //    VPSS_ERROR("Get pstLocalWbcReg is null!!!\n");
        return HI_FAILURE;
    }
    pstEntity = &pstInstance->stInEntity;
    pstSrc = &pstEntity->stSrc;
    pstStreamInfo = &pstEntity->stStreamInfo;

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }
    VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);

    s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
    if ((HI_SUCCESS != s32Ret) || (HI_NULL == pstCur))
    {
        VPSS_ERROR("GetProcessImage Failed\n");
        return s32Ret;
    }

    stPqWbcInfo.u32Width = pstCur->u32Width;
    /* H265Interlace码流，最后两帧传给PQ的图像高度是原图像高度的两倍，需要除2还原 */
    if (pstSrc->bEnding == HI_TRUE && pstStreamInfo->bH265Interlace == HI_TRUE)
    {
        stPqWbcInfo.u32Height = pstCur->u32Height / 2;
    }
    else
    {
        stPqWbcInfo.u32Height = pstCur->u32Height;
    }
    stPqWbcInfo.bProgressive = pstCur->bProgressive;
    stPqWbcInfo.u32HandleNo = pstInstance->ID ;
    stPqWbcInfo.pstVPSSWbcReg = &pstInstance->stPqWbcReg[0];
    stPqWbcInfo.stOriCoordinate.s32X = 0;
    stPqWbcInfo.stOriCoordinate.s32Y = 0;
    stPqWbcInfo.stOriCoordinate.s32Width = 0;
    stPqWbcInfo.stOriCoordinate.s32Height = 0;
    stPqWbcInfo.stCropCoordinate = stPqWbcInfo.stOriCoordinate;
#ifdef VPSS_SUPPORT_ALG_MCNR
    if (VPSS_ALG_IS_MCNR_ENABLE(pstCur->u32Width, pstCur->u32Height)
        || (HI_TRUE == pstInstance->bSplitEnable))
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_TRUE;
    }
    else
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_FALSE;
    }

    if ((pstInstance->stRwzbInfo.stDetInfo.isRWZB > 0)
        || VPSS_NOT_SUPPORT_MCNR_FMT(pstCur->ePixFormat))
    {
        stPqWbcInfo.bMcnrEnableFlag = HI_FALSE;
    }
#endif
    if (pstCur->bProgressive == HI_FALSE)
    {
        VPSS_ST_RGME_CFG_S stStRgmeCfg;
        stInIntf.pfnGetInfo(&(pstInstance->stInEntity), VPSS_IN_INFO_RGME, HI_DRV_BUF_ADDR_LEFT, &stStRgmeCfg);

        stPqWbcInfo.pRGMV = (HI_VOID *)(stStRgmeCfg.pu8Nx2WriteAddr);

        stPqWbcInfo.stride = stStRgmeCfg.u32Stride;
        stPqWbcInfo.u32DeiEnFlag = HI_TRUE;
    }
    else
    {
#ifdef VPSS_SUPPORT_ALG_MCNR
        //逐行 mctnr 开的时候，也要配置 pRGMV
        if (HI_TRUE == stPqWbcInfo.bMcnrEnableFlag)
        {
            VPSS_ST_RGME_CFG_S stStRgmeCfg;
            stInIntf.pfnGetInfo(&(pstInstance->stInEntity), VPSS_IN_INFO_RGME, HI_DRV_BUF_ADDR_LEFT, &stStRgmeCfg);
            stPqWbcInfo.pRGMV = (HI_VOID *)(stStRgmeCfg.pu8Nx2WriteAddr);
            stPqWbcInfo.stride = stStRgmeCfg.u32Stride;
        }
        else
        {
            stPqWbcInfo.pRGMV = HI_NULL;
            stPqWbcInfo.stride = 0;
        }
#endif
        stPqWbcInfo.u32DeiEnFlag = HI_FALSE;
    }

    {
        HI_DRV_VIDEO_PRIVATE_S *pstPriv;
        HI_DRV_DNR_INFO_S *pstDnrInfo;

        pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstCur->u32Priv;
        pstDnrInfo = &pstPriv->stDNRInfo;
        stPqWbcInfo.bCropBeforeDB = HI_FALSE;
        stPqWbcInfo.u32SingleModeFlag = 1;
        stPqWbcInfo.u32Protocol = 1;
        stPqWbcInfo.u32ImageAvgQP = pstDnrInfo->u32ImageAvgQP;
        stPqWbcInfo.u32VdhInfoAddr = pstDnrInfo->u32VdhInfoAddr;
        stPqWbcInfo.u32VdhInfoStride = pstDnrInfo->u32VdhInfoStride;
        stPqWbcInfo.u32ImageStruct = 0; //pstDnrInfo->u32Size;
    }
#if defined(CHIP_TYPE_hi3798cv200)
    (HI_VOID)VPSS_HAL_GetBaseRegAddr(VPSS_IP_0,
                                     &u32BaseRegPhyAddr,
                                     &pu8BaseRegVirAddr);
#endif

    stPqWbcInfo.enSplitMode = (HI_TRUE == pstInstance->bSplitEnable) ?
                              pstInstance->enSplitMode : HI_DRV_PQ_MCDI_SPLIT_MODE_0;

    DRV_PQ_GetWbcInfo(&stPqWbcInfo);

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_StorePrivData(VPSS_BUFFER_S *pstVpssBuf, HI_DRV_VIDEO_FRAME_S *pstPrivFrmData)
{
    HI_DRV_VIDEO_FRAME_S *pstPrivFrame;
    VPSS_MEM_S *pstPrivDataBuf;

#ifdef HI_VPSS_SMMU_SUPPORT
#else
    HI_S32 s32Ret;
    MMZ_BUFFER_S stMMZBuf;
#endif

    pstPrivDataBuf = &(pstVpssBuf->stPrivDataBuf);

#ifdef HI_VPSS_SMMU_SUPPORT
    pstPrivFrame = (HI_DRV_VIDEO_FRAME_S *)pstPrivDataBuf->pu8StartVirAddr;
    if (HI_NULL != pstPrivFrame)
    {
        VPSS_SAFE_MEMCPY(pstPrivFrame, pstPrivFrmData, sizeof(HI_DRV_VIDEO_FRAME_S));
    }
#else
    stMMZBuf.u32StartPhyAddr = pstPrivDataBuf->u32StartPhyAddr;
    stMMZBuf.u32Size = pstPrivDataBuf->u32Size;
    s32Ret = HI_DRV_MMZ_Map(&stMMZBuf);
    if ((HI_SUCCESS == s32Ret) && (HI_NULL != stMMZBuf.pu8StartVirAddr))
    {
        pstPrivFrame = (HI_DRV_VIDEO_FRAME_S *)stMMZBuf.pu8StartVirAddr;

        VPSS_SAFE_MEMCPY(pstPrivFrame, pstPrivFrmData, sizeof(HI_DRV_VIDEO_FRAME_S));
    }
    else
    {
        VPSS_ERROR("Get PrivDataBuf Failed,PhyAddr=%#x\n",
                   pstPrivDataBuf->u32StartPhyAddr);
    }
#endif

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_CompleteTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    HI_DRV_VIDEO_FRAME_S *pstCur;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_HAL_INFO_S *pstHalInfo;

    pstHalInfo  = &(pstInstance->stVpssHalInfo);

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulThreadWakeUpAll[pstInstance->u32TimeStampIndex] = jiffies;
#if 0
    VPSS_HAL_GetSystemTickCounter(enIp,
                                  &(pstInstance->u32LogicTick[pstInstance->u32TimeStampIndex]),
                                  &(pstInstance->u32LogicClock));
#endif
    pstInstance->u32LogicTimeoutCnt--;
#endif
    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    //correct src info ,because rotation change it

    /*step 0.0:get  info from pq module*/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
#ifdef VPSS_HAL_WITH_CBB
        if ((HI_TRUE == pstPort->bEnble) && pstPort->bNeedRotate)
#else
        if ((HI_TRUE == pstPort->bEnble) &&
            ((HI_DRV_VPSS_ROTATION_90 == pstPort->enRotation)
             || (HI_DRV_VPSS_ROTATION_270 == pstPort->enRotation)))
#endif
        {
            VPSS_CHECK_NULL(stInIntf.pfnGetProcessImage);
            s32Ret = stInIntf.pfnGetProcessImage(&pstInstance->stInEntity, &pstCur);
            if ((HI_SUCCESS != s32Ret) || (HI_NULL == pstCur))
            {
                VPSS_FATAL("GetProcessImage failed!\n");
                return HI_FAILURE;
            }

            pstHalInfo->stInInfo.u32Width = pstCur->u32Width;
            pstHalInfo->stInInfo.u32Height = pstCur->u32Height;
            pstHalInfo->stInInfo.bProgressive = pstCur->bProgressive;
            pstHalInfo->stInInfo.enFieldMode = pstCur->enFieldMode;
            break;
        }
    }

#if !defined(HI_NVR_SUPPORT)
    //Get lasi statistic data here, to Ensure lasi data has been truely created(after tunnel interrupt and complete Interrupt).
    VPSS_CTRL_CopyWBCStatistic(pstInstance);

    VPSS_CTRL_GetRwzbData(enIp, pstInstance);
#endif


#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulPQAlgStartTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif

#if !defined(HI_NVR_SUPPORT)
#ifdef VPSS_HAL_WITH_CBB
    VPSS_CTRL_UpdatePqWbcData(pstInstance, (PQ_VPSS_WBC_REG_S *)pstInstance->stVpssHalInfo.stSttAddr.pu8stt_w_vir_addr);
#else
    VPSS_CTRL_UpdatePqWbcData(pstInstance, (PQ_VPSS_WBC_REG_S *)pstInstance->stVpssHalInfo.pu8stt_w_vir_addr);
#endif
#endif


#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulPQAlgEndTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif


    /*step 1.0 :release done image*/
    VPSS_INST_CompleteImage(pstInstance);

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulFinishTime[pstInstance->u32TimeStampIndex] = jiffies;
    pstInstance->u32TimeStampIndex = (pstInstance->u32TimeStampIndex + 1) % VPSS_PROC_TIMESTAMP_MAXCNT;
#endif
    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_SendOutFrame(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;

    VPSS_FB_NODE_S *pstLeftFbNode;
    VPSS_FB_NODE_S *pstRightFbNode;
    HI_BOOL bDropped;
    HI_DRV_VIDEO_FRAME_S *pstTmpFrame = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv;
    HI_DRV_VPSS_BUFFER_TYPE_E ePortType = HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret = HI_FAILURE;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulThreadWakeUpTunnel[pstInstance->u32TimeStampIndex] = jiffies;
    if (HI_FALSE == pstInstance->bOutLowDelay)
    {
        pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFE;
    }
#endif

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    pstTmpFrame = VPSS_VMALLOC(sizeof(HI_DRV_VIDEO_FRAME_S));
    if (HI_NULL == pstTmpFrame)
    {
        VPSS_ERROR("Malloc tmp frame fail!\n");
        return HI_FAILURE;
    }

    /*step 2:add outframe to outPort list*/
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &(pstInstance->stPort[u32Count]);
        if (pstPort->s32PortId == VPSS_INVALID_HANDLE)
        {
            continue;
        }
        pstLeftFbNode = pstInstance->pstFrmNode[u32Count * 2];
        pstRightFbNode = pstInstance->pstFrmNode[u32Count * 2 + 1];

        bDropped = HI_FALSE;
        if (pstLeftFbNode != HI_NULL || pstRightFbNode != HI_NULL)
        {
            /* for interlace stream, send out first frame, drop second and third frame
                 to decrease the time cost of first frame which is sent out */
            if (HI_FALSE == pstInstance->stInEntity.stStreamInfo.u32StreamProg)
            {
#ifdef HI_VPSS_VER_YDJC
                if (((pstInstance->stInEntity.stStreamInfo.u32StreamW == 720)
                     && (pstInstance->stInEntity.stStreamInfo.u32StreamH <= 576))
                    && (0 == pstInstance->stInEntity.stWbcInfo[0].u32CompleteCount)
                   )
                {
                    bDropped = HI_TRUE; //drop 1st sd frame when seek.
                }
#endif
                if ((1 == pstInstance->stInEntity.stWbcInfo[0].u32CompleteCount)
                    || (2 == pstInstance->stInEntity.stWbcInfo[0].u32CompleteCount))
                {
                    bDropped = HI_TRUE;
                }
            }
        }

        if (pstLeftFbNode != HI_NULL )
        {
            VPSS_SAFE_MEMCPY(pstTmpFrame,
                             &(pstLeftFbNode->stOutFrame),
                             sizeof(HI_DRV_VIDEO_FRAME_S));

            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                /*Revise the Port Type to HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE
                    *in order to decide whether report newframe
                    */
                ePortType = HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE;

                if (pstInstance->bStorePrivData)
                {
#ifdef VPSS_SUPPORT_OUT_TUNNEL
                    memset(&(pstLeftFbNode->stOutFrame.stLowdelayStat), 0x0, sizeof(HI_DRV_LOWDELAY_STAT_INFO_S));
                    // record report done time for overlay lowdelay
                    (HI_VOID)HI_DRV_SYS_GetTimeStampMs(&(pstLeftFbNode->stOutFrame.stLowdelayStat.u32OmxReportDoneTime));
#endif
                    (HI_VOID)VPSS_CTRL_StorePrivData(&(pstLeftFbNode->stBuffer),
                                                     &(pstLeftFbNode->stOutFrame));
                }

                if (HI_FALSE == bDropped)
                {
                    if (u32Count == 0)
                    {
                        HI_LD_Event_S evt;
                        HI_U32 TmpTime = 0;
                        HI_DRV_SYS_GetTimeStampMs(&TmpTime);
                        evt.evt_id = EVENT_VPSS_FRM_OUT;
                        evt.frame = pstLeftFbNode->stOutFrame.u32FrameIndex;
                        evt.handle = pstLeftFbNode->stOutFrame.hTunnelSrc;
                        evt.time = TmpTime;
                        HI_DRV_LD_Notify_Event(&evt);
                    }

                    VPSS_INST_ReportNewFrm(pstInstance,
                                           pstPort->s32PortId,
                                           &(pstLeftFbNode->stOutFrame));
                }
                else
                {
                    VPSS_INST_RelFrmBuffer(pstInstance, pstPort->s32PortId,
                                           &(pstPort->stFrmInfo.stBufListCfg),
                                           &(pstLeftFbNode->stBuffer.stMemBuf));
                }


                memset(&(pstInstance->pstFrmNode[u32Count]->stBuffer), 0x0,
                       sizeof(pstInstance->pstFrmNode[u32Count]->stBuffer));

                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                       pstInstance->pstFrmNode[u32Count],
                                       VPSS_FB_TYPE_NORMAL);
            }
            else
            {
                if (HI_FALSE == bDropped)
                {
                    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstLeftFbNode->stOutFrame.u32Priv[0]);
                    pstPriv->u32FrmCnt = pstPort->u32OutCount;
                    if ((pstInstance->stInEntity.stStreamInfo.u32InRate > pstPort->u32MaxFrameRate)
                        && (pstPort->u32MaxFrameRate != 0))
                    {
                        pstLeftFbNode->stOutFrame.u32FrameRate
                            = pstInstance->stInEntity.stStreamInfo.u32InRate / 2 * 1000;
                    }

                    if (u32Count == 0)
                    {
                        HI_LD_Event_S evt;
                        HI_U32 TmpTime = 0;
                        HI_DRV_SYS_GetTimeStampMs(&TmpTime);
                        evt.evt_id = EVENT_VPSS_FRM_OUT;
                        evt.frame = pstLeftFbNode->stOutFrame.u32FrameIndex;
                        evt.handle = pstLeftFbNode->stOutFrame.hTunnelSrc;
                        evt.time = TmpTime;
                        HI_DRV_LD_Notify_Event(&evt);
                    }
                    VPSS_FB_AddFulFrmBuf(&(pstPort->stFrmInfo), pstLeftFbNode);
                }
                else
                {

                    VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                           pstLeftFbNode,
                                           VPSS_FB_TYPE_NORMAL);
                }
            }
        }

        if (pstRightFbNode != HI_NULL)
        {
            VPSS_SAFE_MEMCPY(&(pstRightFbNode->stOutFrame.stBufAddr[0]),
                             &(pstTmpFrame->stBufAddr[0]),
                             sizeof(HI_DRV_VID_FRAME_ADDR_S));
            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                if (HI_FALSE == bDropped)
                {
                    VPSS_INST_ReportNewFrm(pstInstance,
                                           pstPort->s32PortId,
                                           &(pstRightFbNode->stOutFrame));
                }
                else
                {
                    VPSS_INST_RelFrmBuffer(pstInstance, pstPort->s32PortId,
                                           &(pstPort->stFrmInfo.stBufListCfg),
                                           &(pstRightFbNode->stBuffer.stMemBuf));
                }

                VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                       pstInstance->pstFrmNode[u32Count],
                                       VPSS_FB_TYPE_NORMAL);
            }
            else
            {

                if (HI_FALSE == bDropped)
                {
                    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstRightFbNode->stOutFrame.u32Priv[0]);
                    pstPriv->u32FrmCnt = pstPort->u32OutCount;
                    VPSS_FB_AddFulFrmBuf(&(pstPort->stFrmInfo), pstRightFbNode);
                }
                else
                {
                    VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                           pstRightFbNode,
                                           VPSS_FB_TYPE_NORMAL);
                }
            }
        }

        pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
        pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;

    }
    if (ePortType == HI_DRV_VPSS_BUF_VPSS_ALLOC_MANAGE)
    {
        if (pstInstance->pfUserCallBack != HI_NULL)
        {
            pstInstance->pfUserCallBack(pstInstance->hDst, VPSS_EVENT_NEW_FRAME, HI_NULL);
        }
        else
        {
            VPSS_FATAL("Can't report VPSS_EVENT_NEW_FRAME,pfUserCallBack is NULL");
        }

        VPSS_INST_ReportCompleteEvent(pstInstance);
    }

    VPSS_VFREE(pstTmpFrame);

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_ClearTask(VPSS_IP_E enIp, VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32Count;
    VPSS_PORT_S *pstPort;
    VPSS_FB_NODE_S *pstFbNode;
    VPSS_IN_INTF_S stInIntf;
    HI_S32 s32Ret = HI_FAILURE;

#ifdef VPSS_SUPPORT_PROC_V2
    pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulThreadWakeUpTunnel[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulThreadWakeUpAll[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulPQAlgStartTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulPQAlgEndTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->aulFinishTime[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->u32LogicTick[pstInstance->u32TimeStampIndex] = 0xFFFFFFFF;
    pstInstance->u32TimeStampIndex = (pstInstance->u32TimeStampIndex + 1) % VPSS_PROC_TIMESTAMP_MAXCNT;
#endif

    s32Ret = VPSS_IN_GetIntf(&(pstInstance->stInEntity), &stInIntf);
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("Get Interface Failed\n");
        return HI_FAILURE;
    }

    //step1:release src buffer
    s32Ret = stInIntf.pfnCompleteImage(&(pstInstance->stInEntity));
    if (HI_SUCCESS != s32Ret)
    {
        VPSS_FATAL("pfnCompleteImage failed!\n");
        return HI_FAILURE;
    }

    //step2:release port buffer
    for (u32Count = 0; u32Count < DEF_HI_DRV_VPSS_PORT_MAX_NUMBER; u32Count++)
    {
        pstPort = &((pstInstance)->stPort[u32Count]);
        pstFbNode = pstInstance->pstFrmNode[u32Count * 2];
        if (pstFbNode != HI_NULL)
        {
            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                VPSS_INST_RelFrmBuffer(pstInstance, pstPort->s32PortId,
                                       &(pstPort->stFrmInfo.stBufListCfg),
                                       &(pstFbNode->stBuffer.stMemBuf));
            }
            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                   pstFbNode,
                                   VPSS_FB_TYPE_NORMAL);
        }

        pstFbNode = pstInstance->pstFrmNode[u32Count * 2 + 1];
        if (pstFbNode != HI_NULL)
        {

            if (pstPort->stFrmInfo.stBufListCfg.eBufType == HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE)
            {
                VPSS_INST_RelFrmBuffer(pstInstance, pstPort->s32PortId,
                                       &(pstPort->stFrmInfo.stBufListCfg),
                                       &(pstFbNode->stBuffer.stMemBuf));
            }
            VPSS_FB_AddEmptyFrmBuf(&(pstPort->stFrmInfo),
                                   pstFbNode,
                                   VPSS_FB_TYPE_NORMAL);
        }

        pstInstance->pstFrmNode[u32Count * 2] = HI_NULL;
        pstInstance->pstFrmNode[u32Count * 2 + 1] = HI_NULL;
    }


    return HI_SUCCESS;

}

HI_S32 VPSS_CTRL_TaskLogic(HI_VOID *pArg)
{
    VPSS_IP_E enIp;
    HI_S32 s32WaitRet     = HI_FAILURE;
    HI_S32 s32StartRet    = HI_FAILURE;
    VPSS_CTRL_S *pstVpssCtrl = HI_NULL;


    enIp = (VPSS_IP_E)pArg;

    VPSS_CHECK_ENUM(enIp, VPSS_IP_0, VPSS_IP_BUTT);
    pstVpssCtrl = &(g_stVpssCtrl[enIp]);

    pstVpssCtrl->logic.u32Position = 0;

    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stEventLogicDone), EVENT_UNDO, EVENT_UNDO);
    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stEventInstanceListReady), EVENT_UNDO, EVENT_UNDO);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stEventOutTunnel), EVENT_UNDO, EVENT_UNDO);
    VPSS_OSAL_InitSpin(&(pstVpssCtrl->stOutTunnelSpin));
#endif
    pstVpssCtrl->stTask.u32LastTotal = 0;
    pstVpssCtrl->stTask.u32SuccessTotal = 0;
    pstVpssCtrl->stTask.u32Create = 0;
    pstVpssCtrl->stTask.u32Fail = 0;
    pstVpssCtrl->stTask.u32TimeOut = 0;

    while (!kthread_should_stop())
    {
        if (pstVpssCtrl->logic.u32NeedSleep == 1)
        {
            goto LOGIC_TASK_IDLE;
        }
        pstVpssCtrl->logic.u32Position = 1;
        pstVpssCtrl->stTask.u32Create++;

#ifdef VPSS_SUPPORT_OUT_TUNNEL
        VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventOutTunnel), EVENT_UNDO, EVENT_UNDO);
#endif
        s32StartRet = HI_FAILURE;
        VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventLogicDone), EVENT_UNDO, EVENT_UNDO);
        s32StartRet = VPSS_CTRL_StartTask(enIp);

#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
        pstVpssCtrl->s32OutTunnelCntDbg = pstVpssCtrl->s32OutTunelInstanceCnt;
#endif
        if (s32StartRet == HI_SUCCESS)
        {
#ifdef VPSS_SUPPORT_OUT_TUNNEL
        LOGIC_TASK_TUNNEL:
            if (pstVpssCtrl->s32OutTunelInstanceCnt > 0)
            {
                unsigned long flags;

                if (HI_TRUE == pstVpssCtrl->bLogicDone)
                {
                    pstVpssCtrl->s32OutTunnelInterruptCnt = pstVpssCtrl->s32OutTunelInstanceCnt;
                }

                if (pstVpssCtrl->s32OutTunnelInterruptCnt > 0)
                {
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
                    pstVpssCtrl->s32OutTunnelIntCntDbg += pstVpssCtrl->s32OutTunnelInterruptCnt;
#endif
                    while (pstVpssCtrl->s32OutTunnelInterruptCnt > 0)
                    {
                        VPSS_CTRL_TaskFlagTunnel(enIp, INSTANCE_STATE_TUNNELOUT);
                        VPSS_OSAL_GiveEvent(&(pstVpssCtrl->stEventInstanceListDone), 1, 0);

                        VPSS_OSAL_DownSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);
                        pstVpssCtrl->s32OutTunnelInterruptCnt--;
                        VPSS_OSAL_UpSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);

                        pstVpssCtrl->s32OutTunelInstanceCnt--;
                        VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventOutTunnel), EVENT_UNDO, EVENT_UNDO);
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
                        pstVpssCtrl->s32OutTunelEvtResetCntDbg++;
#endif

                    }
                }
                else
                {
                    s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stEventOutTunnel), HZ);
                    if (s32WaitRet == HI_SUCCESS)
                    {
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
                        pstVpssCtrl->s32OutTunelEvtDoneCntDbg++;
#endif
                        VPSS_CTRL_TaskFlagTunnel(enIp, INSTANCE_STATE_TUNNELOUT);
                        VPSS_OSAL_DownSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);
                        pstVpssCtrl->s32OutTunnelInterruptCnt--;
                        VPSS_OSAL_UpSpin(&(pstVpssCtrl->stOutTunnelSpin), &flags);
                    }
                    else
                    {
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
                        VPSS_ERROR("wait LowDelay timeout RunInst %d\n"
                                   "Total %d left %d Intcnt %d int-now %d , evt create %d done %d reset %d LogicDone %d\n",
                                   pstVpssCtrl->s32RunInstCnt,
                                   pstVpssCtrl->s32OutTunnelCntDbg,
                                   pstVpssCtrl->s32OutTunelInstanceCnt,
                                   pstVpssCtrl->s32OutTunnelIntCntDbg,
                                   pstVpssCtrl->s32OutTunnelInterruptCnt,
                                   pstVpssCtrl->s32OutTunelEvtCreateCntDbg,
                                   pstVpssCtrl->s32OutTunelEvtDoneCntDbg,
                                   pstVpssCtrl->s32OutTunelEvtResetCntDbg,
                                   pstVpssCtrl->bLogicDone
                                  );
#endif
                        VPSS_CTRL_TaskFlagTunnel(enIp, INSTANCE_STATE_FAIL);
                    }

                    VPSS_OSAL_GiveEvent(&(pstVpssCtrl->stEventInstanceListDone), 1, 0);
                    pstVpssCtrl->s32OutTunelInstanceCnt--;
                    VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventOutTunnel), EVENT_UNDO, EVENT_UNDO);
                }

                goto LOGIC_TASK_TUNNEL;
            }
#endif
            s32WaitRet = VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stEventLogicDone), HZ);
            if (s32WaitRet == HI_SUCCESS)
            {
                pstVpssCtrl->logic.u32Position = 2;
                pstVpssCtrl->stTask.u32SuccessTotal++;
                VPSS_CTRL_TaskFlag(enIp, INSTANCE_STATE_END);
                VPSS_OSAL_GiveEvent(&(pstVpssCtrl->stEventInstanceListDone), 1, 0);
            }
            else
            {
                pstVpssCtrl->logic.u32Position = 3;
                VPSS_WARN("wait EventLogicDone timeout\n");
                VPSS_CTRL_TaskFlag(enIp, INSTANCE_STATE_FAIL);
            }
        }
        else
        {
            /* 创建Task成功之后，start必须成功 */
            pstVpssCtrl->logic.u32Position = 4;
            goto LOGIC_TASK_IDLE;
        }

        continue;

    LOGIC_TASK_IDLE:
        pstVpssCtrl->logic.u32Position = 5;
        VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stEventInstanceListReady), 5);
        VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventInstanceListReady), EVENT_UNDO, EVENT_UNDO);
    }

    pstVpssCtrl->logic.u32Position = 6;

    return HI_SUCCESS;
}


HI_S32 VPSS_CTRL_TaskSoftware(HI_VOID *pArg)
{
    HI_S32 s32Ret = HI_FAILURE;
    VPSS_INSTANCE_S *pstInstance;
    HI_S32 s32Index;
    VPSS_INST_CTRL_S  *pstInstCtrlInfo;
    unsigned long  u32LockFlag;
    VPSS_CTRL_S *pstVpssCtrl = HI_NULL;
    VPSS_IP_E enIp;
    volatile HI_S32  s32UnfinishJobCount;
    HI_BOOL bLoopSwitch;
    HI_S32  s32LoopStartIndex;

    enIp = (VPSS_IP_E)pArg;
    VPSS_CHECK_ENUM(enIp, VPSS_IP_0, VPSS_IP_BUTT);
    pstVpssCtrl = &(g_stVpssCtrl[enIp]);

    pstVpssCtrl->software.u32Position = 0;
    s32UnfinishJobCount = 0;
    bLoopSwitch = HI_FALSE;
    s32LoopStartIndex = 0;
    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    VPSS_OSAL_IntfTime_Init(); //初始化计时结构体g_astVPSS_Intf_Time
#if defined(ALGBUF_MANAGE_MODE1)
    VPSS_AlgBuf_Init(&g_VpssAlgBuf, 0);
#elif (defined(ALGBUF_MANAGE_MODE2))
    {
        HI_U32 index;
        for (index = 0; index < VPSS_INSTANCE_ALGFIXSIZE_NUM; index++)
        {
            VPSS_AlgBuf_Init(&g_VpssAlgBuf[index], index);
            VPSS_AlgBuf_Malloc(&g_VpssAlgBuf[index]);
        }
    }
#endif

    VPSS_OSAL_InitEvent(&(pstVpssCtrl->stEventInstanceListDone), EVENT_UNDO, EVENT_UNDO);

    while (!kthread_should_stop())
    {
        if (pstVpssCtrl->software.u32NeedSleep == 1)
        {
            goto SOFTWARE_TASK_IDLE;
        }

        pstVpssCtrl->software.u32Position = 1;
        /*
            Traversal instance list to find a Available inst
            available means two requirement:
            1.one undo image
            2.at least two writting space
         */

        /*
                for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
                {
                    if (s32LoopStartIndex >= VPSS_INSTANCE_MAX_NUMB)
                    {
                        s32LoopStartIndex = 0;
                    }

                    read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
                    pstInstance = pstInstCtrlInfo->pstInstPool[s32LoopStartIndex++];
                    read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        */

        bLoopSwitch = !bLoopSwitch;
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
            if (HI_TRUE == bLoopSwitch)
            {
                pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            }
            else
            {
                pstInstance = pstInstCtrlInfo->pstInstPool[VPSS_INSTANCE_MAX_NUMB -
                              s32Index - 1];
            }
            read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

            if (pstInstance == HI_NULL)
            {
                continue;
            }

            if (pstInstance->eNextState == INSTANCE_STATE_STOP)
            {
                if (pstInstance->enState == INSTANCE_STATE_IDLE)
                {
                    VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_STOP);
                    pstInstance->eNextState = INSTANCE_STATE_BUTT;
                    VPSS_OSAL_GiveEvent(&(pstInstance->stEventInstanceStop), EVENT_DONE, EVENT_UNDO);
                }
                continue;
            }

            if (pstInstance->eNextState == INSTANCE_STATE_IDLE)
            {
                VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_IDLE);
                pstInstance->eNextState = INSTANCE_STATE_BUTT;
            }

            if (pstInstance->enState != INSTANCE_STATE_IDLE)
            {
                continue;
            }
#ifdef VPSS_SUPPORT_PROC_V2
            pstInstance->aulBeginTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif

            s32Ret = VPSS_CTRL_CheckIstanceReady(enIp, pstInstance); //include check fb state
            if (HI_SUCCESS != s32Ret)
            {
                continue;
            }

            VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_PREPARE);

#ifdef VPSS_SUPPORT_OUT_TUNNEL
            VPSS_CTRL_UpdateLowDelayFlag(enIp, pstInstance);
#endif

            s32Ret = VPSS_CTRL_GetOutBuffer(pstInstance);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_IDLE);
                continue;//when resolution changes, omx return fail.
            }

            s32Ret = VPSS_CTRL_CfgTask(enIp, pstInstance);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_FAIL);
                VPSS_FATAL("VPSS_CTRL_CfgTask fail\n");
                continue;
            }
            else
            {
                smp_wmb();
                VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_READY);
#ifdef VPSS_SUPPORT_PROC_V2
                pstInstance->aulReadyTime[pstInstance->u32TimeStampIndex] = jiffies;
#endif
                pstInstance->u32RunCycle = 0;
                s32UnfinishJobCount++;
            }
        }

        pstVpssCtrl->software.u32Position = 2;
        if (s32UnfinishJobCount > 0)
        {
            VPSS_OSAL_GiveEvent(&(pstVpssCtrl->stEventInstanceListReady), 1, 0);
        }

    SOFTWARE_TASK_POST:
        pstVpssCtrl->software.u32Position = 3;
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

            if ((pstInstance == HI_NULL) || (pstInstance->enState <= INSTANCE_STATE_IDLE))
            {
                continue;
            }

            if (pstInstance->enState < INSTANCE_STATE_END)
            {
                pstInstance->u32RunCycle++;
#if defined(HI_NVR_SUPPORT)
                if (pstInstance->u32RunCycle > ((HZ / 10) * 2))
#else
                if (pstInstance->u32RunCycle > ((HZ / 5) * 2))
#endif
                {
                    VPSS_WARN("inst%d timeout retry %d state:%d\n",
                              pstInstance->ID, pstInstance->u32RunCycle, pstInstance->enState);
                    VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_FAIL);
                }
                else
                {
                    if (pstInstance->enState < INSTANCE_STATE_TUNNELOUT)
                    {
                        continue;
                    }
                }
            }

            if (INSTANCE_STATE_FAIL == pstInstance->enState)
            {
                VPSS_WARN("inst%d process fail retry %d\n", pstInstance->ID, pstInstance->u32RunCycle);
#ifdef VPSS_SUPPORT_PROC_V2
                if (pstInstance->stDbgCtrl.stInstDbg.eProcPrintLevel > PROC_PRINT_LEVEL_ORI)
                {
                    VPSS_HAL_DumpReg(enIp, HI_NULL); //print phyreg value;
                }
#endif
                VPSS_CTRL_ClearTask(enIp, pstInstance);
                VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_IDLE);
                s32UnfinishJobCount--;

                continue;
            }

            if (pstInstance->enState < INSTANCE_STATE_TUNNELOUT)
            {
                VPSS_FATAL("inst%d invalid state %d\n", pstInstance->ID, pstInstance->enState);
            }

            pstVpssCtrl->software.u32Position = 7;

            if (pstInstance->bNeedSendOutFrame)
            {
                VPSS_TUNNEL_DBG_INFO("inst %d sendframe enState:%d\n", pstInstance->ID, pstInstance->enState);
                pstInstance->bNeedSendOutFrame = HI_FALSE;
                s32Ret = VPSS_CTRL_SendOutFrame(enIp, pstInstance);
                if (HI_SUCCESS != s32Ret)
                {
                    VPSS_FATAL("VPSS_CTRL_SendOutFrame fail ret:%#x\n", s32Ret);
                }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
                VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
                if (INSTANCE_STATE_TUNNELOUT == pstInstance->enState)
                {
                    VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_WAITEND);
                    VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
                    continue;
                }
                VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
#endif
            }

            if (INSTANCE_STATE_END != pstInstance->enState)
            {
                continue;
            }

            VPSS_TUNNEL_DBG_INFO("inst %d complt enState:%d\n", pstInstance->ID, pstInstance->enState);

            s32Ret = VPSS_CTRL_CompleteTask(enIp, pstInstance);
            if (HI_SUCCESS != s32Ret)
            {
                VPSS_FATAL("VPSS_CTRL_CompleteTask fail ret:%#x\n", s32Ret);
            }

            s32UnfinishJobCount--;
            pstVpssCtrl->software.u32Position = 8;
            VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
            VPSS_NEXT_STATE(pstInstance, INSTANCE_STATE_IDLE);
            VPSS_OSAL_UpLock(&(pstInstance->stInstLock));
            if (s32UnfinishJobCount == 0)
            {
                pstVpssCtrl->software.u32Position = 5;
                goto SOFTWARE_TASK_END;
            }
        }

    SOFTWARE_TASK_IDLE:
        if ((pstVpssCtrl->software.u32NeedSleep == 1) && (s32UnfinishJobCount > 0))
        {
            pstVpssCtrl->software.u32Position = 4;
            msleep(10);
            goto SOFTWARE_TASK_POST;
        }
        else if (s32UnfinishJobCount == 0)
        {
            pstVpssCtrl->software.u32Position = 5;
        }

#if defined(HI_NVR_SUPPORT)
        VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stEventInstanceListDone), 10);
#else
        VPSS_OSAL_WaitEvent(&(pstVpssCtrl->stEventInstanceListDone), 5);
#endif
        VPSS_OSAL_ResetEvent(&(pstVpssCtrl->stEventInstanceListDone), EVENT_UNDO, EVENT_UNDO);
    SOFTWARE_TASK_END:

        s32LoopStartIndex = 0;
    }

    pstVpssCtrl->software.u32Position = 6;

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_CreateThread(VPSS_IP_E enIp)
{
    struct sched_param param;

    g_stVpssCtrl[enIp].logic.u32NeedSleep = 0;
    g_stVpssCtrl[enIp].software.u32NeedSleep = 0;

    g_stVpssCtrl[enIp].logic.hThread =
        kthread_create(VPSS_CTRL_TaskLogic, (HI_VOID *)enIp, "HI_VPSS_Logic");
    msleep(10);
    g_stVpssCtrl[enIp].software.hThread =
        kthread_create(VPSS_CTRL_TaskSoftware, (HI_VOID *)enIp, "HI_VPSS_Software");

    if ( IS_ERR(g_stVpssCtrl[enIp].logic.hThread) || IS_ERR(g_stVpssCtrl[enIp].software.hThread) )
    {
        VPSS_FATAL("Can not create thread.\n");
        return HI_FAILURE;
    }

    param.sched_priority = 99;
    sched_setscheduler(g_stVpssCtrl[enIp].logic.hThread, SCHED_RR, &param);
    sched_setscheduler(g_stVpssCtrl[enIp].software.hThread, SCHED_RR, &param);

    //  kthread_bind(g_stVpssCtrl[enIp].logic.hThread, 3);
    //  kthread_bind(g_stVpssCtrl[enIp].software.hThread, 3);


#ifndef HI_TEE_SUPPORT
    //kthread_bind(g_stVpssCtrl[enIp].hThread, 3);
    //kthread_bind(g_stVpssCtrl[enIp].hThread, 0);
#endif


#if defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
#ifdef HI_FPGA_SUPPORT
    /* TO avoid VPSS's reg r/w operation collision with VDH. (they are both on FPGA4) */
    if (num_online_cpus() > 2)
    {
        if (cpu_online(VPSS_CPU_INDEX))
        {
            kthread_bind(g_stVpssCtrl[enIp].logic.hThread, VPSS_CPU_INDEX);

            //VPSS_FATAL("bind vpss thread to cpu %d!\n", VPSS_CPU_INDEX);
        }
        else
        {
            VPSS_FATAL("kthread_bind fail, cpu %d is not online!\n", VPSS_CPU_INDEX);
        }
    }
#endif
#endif
    wake_up_process(g_stVpssCtrl[enIp].logic.hThread);
    wake_up_process(g_stVpssCtrl[enIp].software.hThread);

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_DestoryThread(VPSS_IP_E enIp)
{
    HI_S32 s32Ret;

    s32Ret = kthread_stop(g_stVpssCtrl[enIp].logic.hThread);
    s32Ret |= kthread_stop(g_stVpssCtrl[enIp].software.hThread);

    if (s32Ret != HI_SUCCESS)
    {
        VPSS_FATAL("Destory Thread Error.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_CreateInstProc(VPSS_HANDLE hVPSS)
{
    HI_CHAR           ProcName[20] = {0};
    DRV_PROC_ITEM_S  *pProcItem;

    HI_OSAL_Snprintf(ProcName, 20, "vpss%02x", hVPSS);

    pProcItem = HI_DRV_PROC_AddModule(ProcName, HI_NULL, HI_NULL);

    if (!pProcItem)
    {
        VPSS_FATAL("Vpss add proc failed!\n");
        return HI_FAILURE;
    }

    pProcItem->data  = (HI_VOID *)(unsigned long)hVPSS;
    pProcItem->read  = VPSS_CTRL_ProcRead;
    pProcItem->write = VPSS_CTRL_ProcWrite;

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_DestoryInstProc(VPSS_HANDLE hVPSS)
{
    HI_CHAR           ProcName[20] = {0};
    HI_OSAL_Snprintf(ProcName, 20, "vpss%02x", (HI_U32)(hVPSS));
    HI_DRV_PROC_RemoveModule(ProcName);
    return HI_SUCCESS;
}

HI_U32 VPSS_CTRL_MallocInstanceId(HI_VOID)
{
    HI_U32 i;
    HI_U32 u32InstCount;
    HI_BOOL bFindVpss;
    HI_U32 u32VpssId;
    VPSS_IP_E enVpssIp;
    unsigned long  u32LockFlag;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;

    u32InstCount = 0;

    for (u32VpssId = 0; u32VpssId < VPSS_IP_BUTT * VPSS_INSTANCE_MAX_NUMB; u32VpssId++)
    {
        bFindVpss = HI_FALSE;

        for (enVpssIp = VPSS_IP_0; enVpssIp < VPSS_IP_BUTT; enVpssIp++)
        {
            pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIp].stInstCtrlInfo);
            read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
            for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
            {
                if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
                {
                    if (u32VpssId == pstInstCtrlInfo->pstInstPool[i]->ID)
                    {
                        bFindVpss = HI_TRUE;
                        u32InstCount++;
                        break;
                    }
                }
            }
            read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        }

        if (!bFindVpss)
        {
            break;
        }
    }

    if (u32InstCount == 0)
    {
        return 0;
    }
    else
    {
        return u32VpssId;
    }
}

VPSS_HANDLE VPSS_CTRL_AddInstance(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 u32VpssId = 0;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    HI_U32 u32Count;
    unsigned long  u32LockFlag;
    VPSS_IP_E enVpssIp;


    enVpssIp = pstInstance->CtrlID;

    if (enVpssIp >= VPSS_IP_BUTT)
    {
        VPSS_FATAL("Invalid enVpssIp:%d\n", enVpssIp);
        return VPSS_INVALID_HANDLE;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIp].stInstCtrlInfo);
    //u32VpssId = VPSS_CTRL_MallocInstanceId();
    write_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count++)
    {
        if (pstInstCtrlInfo->pstInstPool[u32Count] == HI_NULL)
        {
            pstInstCtrlInfo->pstInstPool[u32Count] = pstInstance;
            u32VpssId = u32Count;
            break;
        }
    }
    write_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    if (u32Count == VPSS_INSTANCE_MAX_NUMB)
    {
        VPSS_FATAL("Instance Number is Max.\n");

        return VPSS_INVALID_HANDLE;
    }
    else
    {
        pstInstance->ID = u32VpssId;
        pstInstCtrlInfo->u32InstanceNum++;
        return pstInstance->ID;
    }
}

HI_S32 VPSS_CTRL_DelInstance(VPSS_INSTANCE_S *pstInstance)
{
    HI_U32 i;
    VPSS_IP_E enVpssIP;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long  u32LockFlag;

    VPSS_CHECK_NULL(pstInstance);

    enVpssIP = pstInstance->CtrlID;
    pstInstCtrlInfo = &(g_stVpssCtrl[enVpssIP].stInstCtrlInfo);

    write_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] == pstInstance)
        {
            pstInstCtrlInfo->pstInstPool[i] = HI_NULL;
            break;
        }
    }
    write_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    return HI_SUCCESS;
}



HI_S32 VPSS_CTRL_Init(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 i, j;

    g_stVpssCtrl[0].bIPVaild = HI_TRUE;
    g_stVpssCtrl[1].bIPVaild = HI_FALSE;


    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if (HI_TRUE != g_stVpssCtrl[i].bIPVaild)
        {
            continue;
        }

        if (0 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            s32Ret = VPSS_CTRL_RegistISR((VPSS_IP_E)i);

            if (HI_SUCCESS != s32Ret)
            {
                goto VPSS_IP_DEL_INT;
            }

            VPSS_CTRL_InitInstList((VPSS_IP_E)i);

            s32Ret = VPSS_HAL_Init((VPSS_IP_E)i);
            if (HI_SUCCESS != s32Ret)
            {
                goto VPSS_IP_UnRegist_IRQ;
            }

            s32Ret = VPSS_CTRL_CreateThread((VPSS_IP_E)i);
            if (s32Ret != HI_SUCCESS)
            {
                VPSS_FATAL("VPSS_CTRL_CreateThread Failed\n");
                goto VPSS_IP_HAL_DEL_INIT;
            }
        }

        g_stVpssCtrl[i].s32IsVPSSOpen++;

    }

    return HI_SUCCESS;
#ifdef VPSS_HAL_WITH_CBB
VPSS_IP_HAL_DEL_INIT:
    (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)i);
VPSS_IP_UnRegist_IRQ:
    (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);

VPSS_IP_DEL_INT:
    for (j = 0; j < i; j++)
    {
        if (HI_TRUE == g_stVpssCtrl[j].bIPVaild)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)j);
            (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)j);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)j);
        }
    }
#else

VPSS_IP_HAL_DEL_INIT:
    (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)i);
VPSS_IP_UnRegist_IRQ:
    (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);

VPSS_IP_DEL_INT:
    for (j = 0; j < i; j++)
    {
        if (HI_TRUE == g_stVpssCtrl[j].bIPVaild)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)j);
            (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)j);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)j);
        }
    }
#endif
    return HI_FAILURE;
}

HI_S32 VPSS_CTRL_DelInit(HI_VOID)
{
    HI_U32 i;
    HI_U32 u32Count;
    //    VPSS_BUFFER_S *pstVpssBuf;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        if (HI_TRUE != g_stVpssCtrl[i].bIPVaild)
        {
            continue;
        }

        if (1 > g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            VPSS_FATAL("CTRL_DelInit Error,vpss hasn't initted.\n");
            return HI_FAILURE;
        }

        g_stVpssCtrl[i].s32IsVPSSOpen--;
        if (1 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            for (u32Count = 0; u32Count < VPSS_INSTANCE_MAX_NUMB; u32Count ++)
            {
                if (HI_NULL != g_stVpssCtrl[i].stInstCtrlInfo.pstInstPool[u32Count])
                {
                    VPSS_FATAL("CTRL_DelInit Error,destroy instance first.\n");
                    g_stVpssCtrl[i].s32IsVPSSOpen++;
                    return HI_FAILURE;
                }
            }
            //add for low power
            VPSS_HAL_SetClockEn(i, HI_FALSE);
        }

        if (0 == g_stVpssCtrl[i].s32IsVPSSOpen)
        {
            (HI_VOID)VPSS_CTRL_UnRegistISR((VPSS_IP_E)i);
            (HI_VOID)VPSS_CTRL_DestoryThread((VPSS_IP_E)i);

#ifdef VPSS_HAL_WITH_CBB
            (HI_VOID)VPSS_HAL_DeInit((VPSS_IP_E)i);
#else
            (HI_VOID)VPSS_HAL_DelInit((VPSS_IP_E)i);
#endif
        }
    }

    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_SetMceFlag(HI_BOOL bInMCE)
{
    HI_U32 i;

    for (i = 0; i < VPSS_IP_BUTT; i++)
    {
        g_stVpssCtrl[i].bInMCE = bInMCE;
    }

    return HI_SUCCESS;
}

VPSS_HANDLE VPSS_CTRL_CreateInstance(HI_DRV_VPSS_CFG_S *pstVpssCfg)
{
    HI_S32 s32Ret;
    HI_S32 s32InstHandle = VPSS_INVALID_HANDLE;
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;

    s32Ret = VPSS_CTRL_GetDistributeIP(&enVpssIp);
    if ((HI_SUCCESS != s32Ret) || (enVpssIp == VPSS_IP_BUTT))
    {
        VPSS_FATAL("vpss ctrl isn't enable\n");
        return s32InstHandle;
    }

    if (1 >= g_stVpssCtrl[enVpssIp].s32IsVPSSOpen)
    {
        VPSS_FATAL("vpss ctrl isn't opened\n");
        return s32InstHandle;
    }

    pstInstance = (VPSS_INSTANCE_S *)VPSS_VMALLOC(sizeof(VPSS_INSTANCE_S));
    if (pstInstance != HI_NULL)
    {
        if (pstVpssCfg)
        {
            s32Ret = VPSS_INST_Init(pstInstance, pstVpssCfg);
        }
        else
        {
            HI_DRV_VPSS_CFG_S stDefCfg;
            VPSS_INST_GetDefInstCfg(&stDefCfg);
            s32Ret = VPSS_INST_Init(pstInstance, &stDefCfg);
        }
        if (HI_SUCCESS != s32Ret)
        {
            VPSS_VFREE(pstInstance);
            return s32InstHandle;
        }

        pstInstance->CtrlID = enVpssIp;
#ifdef VPSS_SUPPORT_PROC_V2
        pstInstance->u32LogicTimeoutCnt = 0;
#endif
        s32InstHandle = VPSS_CTRL_AddInstance(pstInstance);
        if (s32InstHandle != VPSS_INVALID_HANDLE)
        {
            pstInstance->stInEntity.u32InstanceId = pstInstance->ID;
            if (g_stVpssCtrl[enVpssIp].bInMCE == HI_FALSE)
            {
                (HI_VOID)VPSS_CTRL_CreateInstProc(pstInstance->ID);
            }
        }
        else
        {
            VPSS_VFREE(pstInstance);
        }

        return s32InstHandle;
    }
    else
    {
        VPSS_FATAL("vmalloc instance node failed \n");
        return s32InstHandle;
    }

}

HI_S32 VPSS_CTRL_DestoryInstance(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    HI_S32 s32Ret;
#else
    HI_S32 s32RetryCnt;
#endif
    pstInstance = VPSS_CTRL_GetInstance(hVPSS);
    if (pstInstance == HI_NULL)
    {
        VPSS_FATAL("hVPSS(%d) is Not be Vaild Or Created\n", hVPSS);
        return HI_FAILURE;
    }

    /*
      *  when deletting instance
      *  must get lock first to ensure that it isn't being served
     */
    enVpssIp = pstInstance->CtrlID;

#ifdef VPSS_SUPPORT_OUT_TUNNEL
    s32Ret = VPSS_CTRL_Pause(hVPSS);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }
#else
    g_stVpssCtrl[enVpssIp].software.u32NeedSleep = 1;
    s32RetryCnt = 0;
    while ((g_stVpssCtrl[enVpssIp].software.u32Position != 5)
           && (s32RetryCnt++ < 200))
    {
        msleep(10);
    }

    if (s32RetryCnt >= 200)
    {
        VPSS_FATAL("wait software thread sleep fail, position:%d retry:%d\n",
                   g_stVpssCtrl[enVpssIp].software.u32Position, s32RetryCnt);
        return HI_FAILURE;
    }

    g_stVpssCtrl[enVpssIp].logic.u32NeedSleep = 1;
    s32RetryCnt = 0;
    while ((g_stVpssCtrl[enVpssIp].logic.u32Position != 5)
           && (s32RetryCnt++ < 200))
    {
        msleep(10);
    }

    if (s32RetryCnt >= 200)
    {
        VPSS_FATAL("wait logic thread sleep fail, position:%d\n", g_stVpssCtrl[enVpssIp].logic.u32Position, s32RetryCnt);
        return HI_FAILURE;
    }
#endif

    if (pstInstance->enState > INSTANCE_STATE_IDLE)
    {
        VPSS_FATAL("Instance %#x is still working(state:%d), please stop it first\n",
                   pstInstance->ID, pstInstance->enState);
        return HI_FAILURE;
    }


    if (g_stVpssCtrl[enVpssIp].bInMCE == HI_FALSE)
    {
        VPSS_CTRL_DestoryInstProc(hVPSS);
    }

    g_stVpssCtrl[enVpssIp].stInstCtrlInfo.u32InstanceNum--;
    VPSS_HAL_H265RefListDeInit(&pstInstance->stH265RefList);
    VPSS_CTRL_DelInstance(pstInstance);
    (HI_VOID)VPSS_INST_DelInit(pstInstance);
    VPSS_VFREE(pstInstance);

#ifndef VPSS_SUPPORT_OUT_TUNNEL
    g_stVpssCtrl[enVpssIp].logic.u32NeedSleep = 0;
    g_stVpssCtrl[enVpssIp].software.u32NeedSleep = 0;
    VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[enVpssIp].stEventInstanceListDone), 1, 0);
    VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[enVpssIp].stEventInstanceListReady), 1, 0);
#endif
    return HI_SUCCESS;

}
HI_S32 VPSS_CTRL_GetInstanceNumber(VPSS_IP_E enIp, HI_U32 *pu32Number)
{
    HI_U32 i;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    unsigned long u32LockFlag;
    HI_U32 u32Cnt = 0;

    VPSS_CHECK_NULL(pu32Number);

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);
    read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
        {
            u32Cnt ++;
        }
    }
    read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    *pu32Number = u32Cnt;

    return HI_SUCCESS;
}

VPSS_INSTANCE_S *VPSS_CTRL_GetOnlyInstance(VPSS_IP_E enIp)
{
    HI_U32 u32InstNumber;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    VPSS_INSTANCE_S *pstRetPtr = HI_NULL;
    unsigned long u32LockFlag;
    HI_U32 i;

    VPSS_CTRL_GetInstanceNumber(VPSS_IP_0, &u32InstNumber);

    if (u32InstNumber != 1)
    {
        return HI_NULL;
    }

    if (1 > g_stVpssCtrl[enIp].s32IsVPSSOpen)
    {
        return HI_NULL;
    }

    pstInstCtrlInfo = &(g_stVpssCtrl[enIp].stInstCtrlInfo);

    read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
    {
        if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
        {
            pstRetPtr = pstInstCtrlInfo->pstInstPool[i];
        }
    }

    read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    return pstRetPtr;
}

VPSS_INSTANCE_S *VPSS_CTRL_GetInstance(VPSS_HANDLE hVPSS)
{
    HI_U32 i;
    HI_U32 u32IpPos;
    VPSS_INST_CTRL_S *pstInstCtrlInfo;
    VPSS_INSTANCE_S *pstRetPtr = HI_NULL;
    unsigned long u32LockFlag;


    if ((hVPSS < 0) || (hVPSS >= VPSS_INSTANCE_MAX_NUMB * VPSS_IP_BUTT))
    {
        VPSS_FATAL("Invalid VPSS HANDLE %x.\n", hVPSS);
        return HI_NULL;
    }

    for (u32IpPos = VPSS_IP_0; u32IpPos < VPSS_IP_BUTT; u32IpPos++)
    {
        if (1 > g_stVpssCtrl[u32IpPos].s32IsVPSSOpen)
        {
            continue;
        }

        pstInstCtrlInfo = &(g_stVpssCtrl[u32IpPos].stInstCtrlInfo);
        read_lock_irqsave(&(pstInstCtrlInfo->stListLock), u32LockFlag);
        for (i = 0; i < VPSS_INSTANCE_MAX_NUMB; i++)
        {
            if (pstInstCtrlInfo->pstInstPool[i] != HI_NULL )
            {
                if (hVPSS == pstInstCtrlInfo->pstInstPool[i]->ID)
                {
                    pstRetPtr = pstInstCtrlInfo->pstInstPool[i];
                    break;
                }
            }
        }
        read_unlock_irqrestore(&(pstInstCtrlInfo->stListLock), u32LockFlag);

    }

    return pstRetPtr;
}

HI_S32 VPSS_CTRL_WakeUpThread(HI_VOID)
{
    if (g_stVpssCtrl[VPSS_IP_0].s32IsVPSSOpen >= 1)
    {
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventInstanceListDone), 1, 0);
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventInstanceListReady), 1, 0);
    }

    if (g_stVpssCtrl[VPSS_IP_1].s32IsVPSSOpen >= 1)
    {
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventInstanceListDone), 1, 0);
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventInstanceListReady), 1, 0);
    }

    return HI_SUCCESS;
}

#ifdef VPSS_SUPPORT_OUT_TUNNEL
extern HI_S32 VPSS_INST_SetState(VPSS_INSTANCE_S *pstInstance, VPSS_INSTANCE_STATE_E enState);

HI_S32 VPSS_CTRL_Pause(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;
    HI_U32 u32SleepNumb = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    VPSS_OSAL_IntfTime_Start(VPSS_INTF_PAUSE);

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    VPSS_CHECK_NULL(pstInstance);

    enVpssIp = pstInstance->CtrlID;

    VPSS_CHECK_ENUM(enVpssIp, VPSS_IP_0, VPSS_IP_BUTT);

    VPSS_OSAL_ResetEvent(&(pstInstance->stEventInstanceStop), EVENT_UNDO, EVENT_UNDO);
    VPSS_OSAL_DownLock(&(pstInstance->stInstLock));
    pstInstance->enLastState = pstInstance->enState;
    VPSS_OSAL_UpLock(&(pstInstance->stInstLock));

    VPSS_INST_SetState(pstInstance, INSTANCE_STATE_STOP);

    if (pstInstance->enState != INSTANCE_STATE_STOP)
    {
        s32Ret = VPSS_OSAL_WaitEvent(&(pstInstance->stEventInstanceStop), 20000);
    }

    if (HI_SUCCESS != s32Ret)
    {
        VPSS_ERROR("inst stop fail state %d retry %d\n", pstInstance->enState, u32SleepNumb);
        HI_UNUSED(u32SleepNumb);//kill compile warning for nagra cfg
        return HI_FAILURE;
    }
    VPSS_OSAL_IntfTime_Stop(VPSS_INTF_PAUSE);

    return HI_SUCCESS;
}

#else

HI_S32 VPSS_CTRL_Pause(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;
    HI_U32 u32SleepNumb = 0;
    VPSS_OSAL_IntfTime_Start(VPSS_INTF_PAUSE);

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    VPSS_CHECK_NULL(pstInstance);

    enVpssIp = pstInstance->CtrlID;

    VPSS_CHECK_ENUM(enVpssIp, VPSS_IP_0, VPSS_IP_BUTT);

    g_stVpssCtrl[enVpssIp].software.u32NeedSleep = 1;

    u32SleepNumb = 0;
    while ((g_stVpssCtrl[enVpssIp].software.u32Position != 5) && (u32SleepNumb < 200))
    {
        msleep(10);
        u32SleepNumb++;
    }

    if (u32SleepNumb >= 200)
    {
        VPSS_ERROR("software thread sleep failed pos %d retry %d\n",
                   g_stVpssCtrl[enVpssIp].software.u32Position, u32SleepNumb);
        return HI_FAILURE;
    }

    g_stVpssCtrl[enVpssIp].logic.u32NeedSleep = 1;
    u32SleepNumb = 0;
    while ((g_stVpssCtrl[enVpssIp].logic.u32Position != 5) && (u32SleepNumb < 200))
    {
        msleep(10);
        u32SleepNumb++;
    }

    if (u32SleepNumb >= 200)
    {
        VPSS_ERROR("logic thread sleep failed pos %d retry %d\n",
                   g_stVpssCtrl[enVpssIp].logic.u32Position, u32SleepNumb);
        return HI_FAILURE;
    }

    VPSS_OSAL_IntfTime_Stop(VPSS_INTF_PAUSE);
    return HI_SUCCESS;
}
#endif
HI_S32 VPSS_CTRL_Resume(VPSS_HANDLE hVPSS)
{
    VPSS_IP_E enVpssIp = VPSS_IP_BUTT;
    VPSS_INSTANCE_S *pstInstance;

    pstInstance = VPSS_CTRL_GetInstance(hVPSS);

    VPSS_CHECK_NULL(pstInstance);

    enVpssIp = pstInstance->CtrlID;
    VPSS_CHECK_ENUM(enVpssIp, VPSS_IP_0, VPSS_IP_BUTT);

#ifndef VPSS_SUPPORT_OUT_TUNNEL
    g_stVpssCtrl[enVpssIp].logic.u32NeedSleep = 0;
    g_stVpssCtrl[enVpssIp].software.u32NeedSleep = 0;
    VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[enVpssIp].stEventInstanceListDone), 1, 0);
    VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[enVpssIp].stEventInstanceListReady), 1, 0);
#else
    VPSS_INST_SetState(pstInstance, pstInstance->enLastState);
#endif
    return HI_SUCCESS;
}

HI_S32 VPSS_CTRL_GetInstanceCnt(VPSS_IP_E enIp)
{
    VPSS_CTRL_S *pstVpssCtrl = &(g_stVpssCtrl[enIp]);
    return pstVpssCtrl->s32RunInstCnt;
}

#ifndef VPSS_HAL_WITH_CBB
irqreturn_t VPSS0_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_U32 u32State = 0;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INST_CTRL_S *pstInstCtrlInfo = &(g_stVpssCtrl[0].stInstCtrlInfo);
    VPSS_INSTANCE_S *pstInstance;
    HI_S32 s32Index;
#endif

    (HI_VOID)VPSS_HAL_GetIntState(VPSS_IP_0, &u32State);

    if (u32State & 0x20)
    {
        VPSS_ERROR("IRQ DCMP ERR    state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x20);
    }

    if (u32State & 0x4)
    {
        VPSS_ERROR("IRQ BUS ERR  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x4);
    }

    if (u32State & 0x2)
    {
        VPSS_ERROR("TIMEOUT  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x2);
    }

    if (u32State & 0x60) //   0xf ---> 0xff open tunl mask and dcmp err mask
    {
        VPSS_ERROR(" Tunnel = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x60);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (u32State & 0x10)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x10);
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
                break;
            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report tunel int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventOutTunnel), EVENT_DONE, EVENT_UNDO);
    }
#endif
    if (u32State & 0x1)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x1);
    }

    if (u32State & 0x88)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_0, 0x88);
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState == INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report Done int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventLogicDone), EVENT_DONE, EVENT_UNDO);
    }
    return IRQ_HANDLED;
}


irqreturn_t VPSS1_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_U32 u32State = 0;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INST_CTRL_S *pstInstCtrlInfo = &(g_stVpssCtrl[0].stInstCtrlInfo);
    VPSS_INSTANCE_S *pstInstance;
    HI_S32 s32Index;
#endif

    (HI_VOID)VPSS_HAL_GetIntState(VPSS_IP_1, &u32State);

    if (u32State & 0x20)
    {
        VPSS_ERROR("IRQ DCMP ERR    state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x20);
    }

    if (u32State & 0x4)
    {
        VPSS_ERROR("IRQ BUS ERR  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x4);
    }

    if (u32State & 0x2)
    {
        VPSS_ERROR("TIMEOUT  state = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x2);
    }

    if (u32State & 0x60) //   0xf ---> 0xff open tunl mask and dcmp err mask
    {
        VPSS_ERROR(" Tunnel = %x \n", u32State);
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x60);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (u32State & 0x10)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x10);
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
                break;
            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report tunel int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventOutTunnel), EVENT_DONE, EVENT_UNDO);
    }
#endif
    if (u32State & 0x1)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x1);
    }

    if (u32State & 0x88)
    {
        VPSS_HAL_ClearIntState(VPSS_IP_1, 0x88);
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState ==
                                             INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;
            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report Done int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventLogicDone), EVENT_DONE, EVENT_UNDO);
    }
    return IRQ_HANDLED;
}

#else  //98mv200
irqreturn_t VPSS0_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_BOOL abISRStat[CBB_ISR_BUTT] = {0};
    HI_BOOL abISRStatMask[CBB_ISR_BUTT] = {0};
    CBB_REG_ADDR_S stRegAddr = {0};
    HI_U32 u32IntState;
    HI_U32 u32IntStateSMMU;

#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INST_CTRL_S *pstInstCtrlInfo = &(g_stVpssCtrl[VPSS_IP_0].stInstCtrlInfo);
    VPSS_INSTANCE_S *pstInstance;
    //unsigned long u32LockFlag;
    HI_S32 s32Index;
#endif
    stRegAddr.pu8BaseVirAddr = stHalCtx[VPSS_IP_0][0].pu8BaseRegVir;
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_GET_ISR_STAT, abISRStat, HI_NULL);

    VPSS_SAFE_MEMCPY(abISRStatMask, abISRStat, sizeof(abISRStatMask));
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_CLR_ISR_STAT, abISRStatMask, HI_NULL);

    u32IntState = ((abISRStat[CBB_ISR_NODE_COMPLETE]    << CBB_ISR_NODE_COMPLETE)
                   | (abISRStat[CBB_ISR_LIST_COMPLETE] << CBB_ISR_LIST_COMPLETE)
                   | (abISRStat[CBB_ISR_BUS_READ_ERR]  << CBB_ISR_BUS_READ_ERR )
                   | (abISRStat[CBB_ISR_BUS_WRITE_ERR] << CBB_ISR_BUS_WRITE_ERR)
                   | (abISRStat[CBB_ISR_DCMP_ERR]      << CBB_ISR_DCMP_ERR     )
                   | (abISRStat[CBB_ISR_VHD0_TUNNEL]   << CBB_ISR_VHD0_TUNNEL )
                  );

    //VPSS_FATAL("VPSS IP0 int (0x%X) ...\n", u32IntState);

    if (abISRStat[CBB_ISR_SMMU_S_TLBMISS] || abISRStat[CBB_ISR_SMMU_S_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_S_TLBMISS] << (CBB_ISR_SMMU_S_TLBMISS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_PTW_TRANS] << (CBB_ISR_SMMU_S_PTW_TRANS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] << (CBB_ISR_SMMU_S_TLBINVALID_RD - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR] << (CBB_ISR_SMMU_S_TLBINVALID_WR - CBB_ISR_SMMU_S_MIN));

        VPSS_WARN("IRQ SMMU-S ERR state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] || abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] << (CBB_ISR_SMMU_NS_TLBMISS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS] << (CBB_ISR_SMMU_NS_PTW_TRANS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] << (CBB_ISR_SMMU_NS_TLBINVALID_RD - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR] << (CBB_ISR_SMMU_NS_TLBINVALID_WR - CBB_ISR_SMMU_NS_MIN));

        VPSS_WARN("IRQ SMMU-NS ERR  state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_BUS_WRITE_ERR] || abISRStat[CBB_ISR_BUS_READ_ERR])
    {
        VPSS_WARN("IRQ BUS W/R ERR  state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_TIMEOUT])
    {
        VPSS_WARN("IRQ TIMEOUT state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_DCMP_ERR])
    {
        VPSS_WARN("IRQ  DCMP ERR state = %x \n", u32IntState);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (abISRStat[CBB_ISR_VHD0_TUNNEL])
    {
        unsigned long flags;
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
                break;
            }
        }
#endif
        VPSS_OSAL_DownSpin(&(g_stVpssCtrl[VPSS_IP_0].stOutTunnelSpin), &flags);
        g_stVpssCtrl[VPSS_IP_0].s32OutTunnelInterruptCnt++;
        VPSS_OSAL_UpSpin(&(g_stVpssCtrl[VPSS_IP_0].stOutTunnelSpin), &flags);

        VPSS_TUNNEL_DBG_INFO("Report tunel int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventOutTunnel), EVENT_DONE, EVENT_UNDO);
#ifdef VPSS_SUPPORT_OUT_TUNNEL_DBG
        g_stVpssCtrl[VPSS_IP_0].s32OutTunelEvtCreateCntDbg++;
#endif
    }
#endif

    if (abISRStat[CBB_ISR_LIST_COMPLETE])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;

                VPSS_HAL_GetSystemTickCounter(VPSS_IP_0,
                                              &(pstInstance->u32LogicTick[pstInstance->u32TimeStampIndex]),
                                              &(pstInstance->u32LogicClock));

            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report Done int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventLogicDone), EVENT_DONE, EVENT_UNDO);
#ifdef VPSS_SUPPORT_OUT_TUNNEL
        g_stVpssCtrl[VPSS_IP_0].bLogicDone = HI_TRUE;
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_0].stEventOutTunnel), EVENT_DONE, EVENT_UNDO);
#endif
    }

    return IRQ_HANDLED;
}

irqreturn_t VPSS1_CTRL_IntService(HI_S32 irq, HI_VOID *dev_id)
{
    HI_BOOL abISRStat[CBB_ISR_BUTT] = {0};
    HI_BOOL abISRStatMask[CBB_ISR_BUTT] = {0};
    CBB_REG_ADDR_S stRegAddr = {0};
    HI_U32 u32IntState;
    HI_U32 u32IntStateSMMU;
#ifdef VPSS_SUPPORT_PROC_V2
    VPSS_INST_CTRL_S *pstInstCtrlInfo = &(g_stVpssCtrl[VPSS_IP_1].stInstCtrlInfo);
    VPSS_INSTANCE_S *pstInstance;
    //unsigned long u32LockFlag;
    HI_S32 s32Index;
#endif
    stRegAddr.pu8BaseVirAddr = stHalCtx[VPSS_IP_1][0].pu8BaseRegVir;
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_GET_ISR_STAT, abISRStat, HI_NULL);

    VPSS_SAFE_MEMCPY(abISRStatMask, abISRStat, sizeof(abISRStatMask));
    VPSS_CBB_BASE_Operating(stRegAddr, CBB_BASEOPT_CLR_ISR_STAT, abISRStatMask, HI_NULL);

    u32IntState = ((abISRStat[CBB_ISR_NODE_COMPLETE]    << CBB_ISR_NODE_COMPLETE)
                   | (abISRStat[CBB_ISR_LIST_COMPLETE] << CBB_ISR_LIST_COMPLETE)
                   | (abISRStat[CBB_ISR_BUS_READ_ERR]  << CBB_ISR_BUS_READ_ERR )
                   | (abISRStat[CBB_ISR_BUS_WRITE_ERR] << CBB_ISR_BUS_WRITE_ERR)
                   | (abISRStat[CBB_ISR_DCMP_ERR]      << CBB_ISR_DCMP_ERR     )
                   | (abISRStat[CBB_ISR_VHD0_TUNNEL]   << CBB_ISR_VHD0_TUNNEL )
                  );

    //VPSS_FATAL("VPSS IP0 int (0x%X) ...\n", u32IntState);

    if (abISRStat[CBB_ISR_SMMU_S_TLBMISS] || abISRStat[CBB_ISR_SMMU_S_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_S_TLBMISS] << (CBB_ISR_SMMU_S_TLBMISS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_PTW_TRANS] << (CBB_ISR_SMMU_S_PTW_TRANS - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_RD] << (CBB_ISR_SMMU_S_TLBINVALID_RD - CBB_ISR_SMMU_S_MIN))
                          + (abISRStat[CBB_ISR_SMMU_S_TLBINVALID_WR] << (CBB_ISR_SMMU_S_TLBINVALID_WR - CBB_ISR_SMMU_S_MIN));

        VPSS_WARN("IRQ SMMU-S ERR state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] || abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS]
        || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] || abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR])
    {
        u32IntStateSMMU = (abISRStat[CBB_ISR_SMMU_NS_TLBMISS] << (CBB_ISR_SMMU_NS_TLBMISS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_PTW_TRANS] << (CBB_ISR_SMMU_NS_PTW_TRANS - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_RD] << (CBB_ISR_SMMU_NS_TLBINVALID_RD - CBB_ISR_SMMU_NS_MIN))
                          + (abISRStat[CBB_ISR_SMMU_NS_TLBINVALID_WR] << (CBB_ISR_SMMU_NS_TLBINVALID_WR - CBB_ISR_SMMU_NS_MIN));

        VPSS_WARN("IRQ SMMU-NS ERR  state = %x \n", u32IntStateSMMU);
    }

    if (abISRStat[CBB_ISR_BUS_WRITE_ERR] || abISRStat[CBB_ISR_BUS_READ_ERR])
    {
        VPSS_WARN("IRQ BUS W/R ERR  state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_TIMEOUT])
    {
        VPSS_WARN("IRQ TIMEOUT state = %x \n", u32IntState);
    }

    if (abISRStat[CBB_ISR_DCMP_ERR])
    {
        VPSS_WARN("IRQ  DCMP ERR state = %x \n", u32IntState);
    }
#ifdef VPSS_SUPPORT_OUT_TUNNEL
    if (abISRStat[CBB_ISR_VHD0_TUNNEL])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulTunnelOutTime[pstInstance->u32TimeStampIndex] = jiffies;
                break;
            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report tunel int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventOutTunnel), EVENT_DONE, EVENT_UNDO);
    }
#endif

    if (abISRStat[CBB_ISR_LIST_COMPLETE])
    {
#ifdef VPSS_SUPPORT_PROC_V2
        for (s32Index = 0; s32Index < VPSS_INSTANCE_MAX_NUMB; s32Index++)
        {
            pstInstance = pstInstCtrlInfo->pstInstPool[s32Index];
            if ((HI_NULL != pstInstance) && (pstInstance->enState >= INSTANCE_STATE_RUNNING))
            {
                pstInstance->aulLogicEndTime[pstInstance->u32TimeStampIndex] = jiffies;

                VPSS_HAL_GetSystemTickCounter(VPSS_IP_1,
                                              &(pstInstance->u32LogicTick[pstInstance->u32TimeStampIndex]),
                                              &(pstInstance->u32LogicClock));

            }
        }
#endif
        VPSS_TUNNEL_DBG_INFO("Report Done int\n");
        VPSS_OSAL_GiveEvent(&(g_stVpssCtrl[VPSS_IP_1].stEventLogicDone), EVENT_DONE, EVENT_UNDO);
    }

    return IRQ_HANDLED;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

