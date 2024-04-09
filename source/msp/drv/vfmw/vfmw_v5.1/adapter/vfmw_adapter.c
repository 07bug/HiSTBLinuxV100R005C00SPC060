#include "public.h"
#include "vfmw_debug.h"
#include "vfmw_adapter.h"
#include "vfmw_osal_ext.h"
#include "vfmw_img_info.h"
#include "pts_info.h"
#include "vfmw_dump_file.h"
#include "vmm.h"
#include "hi_drv_video.h"

#ifdef HI_TEE_SUPPORT
#include "vfmw_tee_client.h"
#endif
#ifdef VFMW_CRC_SUPPORT
#include "crc.h"
#endif
#ifdef VFMW_VPP_SUPPORT
#include "virtual_pp.h"
#endif

/*======================================================================*/
/*   Type definition                                                        */
/*======================================================================*/
typedef struct
{
    UINT8 IsSec;
    UINT8 IsExternBuffer;
} GLB_CHAN_INFO;


/*======================================================================*/
/*   Internal data                                                      */
/*======================================================================*/
static GLB_CHAN_INFO g_ChanInfo[MAX_CHAN_NUM];


/*======================================================================*/
/*   Internal interface                                                 */
/*======================================================================*/
static UINT8 VFMW_GetTVPFlag(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT64 *p64 = NULL;
    UINT8 SecFlag = 0;

    if (ChanID >= 0 && ChanID < MAX_CHAN_NUM)
    {
        SecFlag = g_ChanInfo[ChanID].IsSec;
    }
    else
    {
        if (VDEC_CID_CREATE_CHAN == eCmdID || VDEC_CID_GET_CHAN_MEMSIZE == eCmdID)
        {
            p64 = (SINT64 *)pArgs;
            SecFlag = ((VDEC_CHAN_OPTION_S *)UINT64_PTR(p64[1]))->s32IsSecMode;
        }
    }

    return SecFlag;
}

static VOID VFMW_BeforeCfgChan(SINT32 ChanID, VOID *pArgs)
{
    VDEC_CHAN_CFG_S *pCfg = (VDEC_CHAN_CFG_S *)pArgs;

    VFMW_ASSERT(pCfg != NULL);

    if (pCfg->bSampleFRDEnable == VDEC_TRUE)
    {
        PTS_Info_EnableSampleFRD(ChanID);
    }
    else
    {
        PTS_Info_DisableSampleFRD(ChanID);
    }

#ifdef VFMW_CRC_SUPPORT
    CRC_SetConfig(ChanID, pCfg);
#endif

    return;
}

static VOID VFMW_BeforeDestroyChan(SINT32 ChanID, VOID *pArgs)
{
    PTS_Info_Free(ChanID);

#ifdef VFMW_CRC_SUPPORT

    if (CRC_DestroyInst(ChanID) != VDEC_OK)
    {
        dprint(PRN_ERROR, "Destroy CRC inst %d failed!\n", ChanID);
    }

#endif

#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Destroy(ChanID);
#endif

    return;
}

static VOID VFMW_AfterCreateChan(SINT32 ChanID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    SINT32 *p32 = NULL;
    UINT64 *p64 = NULL;

    if (Result != VDEC_OK)
    {
        return;
    }

    p32 = (SINT32 *)pArgs;
    p64 = (UINT64 *)pArgs;

    ChanID = p32[0];

    if (ChanID < 0 || ChanID >= MAX_CHAN_NUM)
    {
        dprint(PRN_ERROR, "%s: ChanID %d invalid!\n", __func__, ChanID);
        return;
    }

    PTS_Info_Alloc(ChanID);

#ifdef VFMW_CRC_SUPPORT

    if (CRC_CreateInst(ChanID) != VDEC_OK)
    {
        dprint(PRN_ERROR, "Create CRC inst %d failed!\n", ChanID);
    }

#endif

#ifdef VFMW_VPP_SUPPORT
    {
        VIR_PP_WORKMODE_E enWorkMode = QUERY_MODE;
        VDEC_CHAN_OPTION_S *pChanOption = NULL;

        pChanOption = UINT64_PTR(p64[1]);

        if (pChanOption != NULL)
        {
            enWorkMode = (pChanOption->eAdapterType == ADAPTER_TYPE_VDEC) ? QUERY_MODE : REPORT_MODE;
        }

        VIR_PP_Create(ChanID, enWorkMode);
    }
#endif

    g_ChanInfo[ChanID].IsSec = (IsSec) ? 1 : 0;

    return;
}


static VOID VFMW_AfterStartChan(SINT32 ChanID, SINT32 Result)
{
    if (Result != VDEC_OK)
    {
        return;
    }

#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Start(ChanID);
#endif

    return;
}

static VOID VFMW_AfterStopChan(SINT32 ChanID, SINT32 Result)
{
    if (Result != VDEC_OK)
    {
        return;
    }

#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Stop(ChanID);
#endif

    return;
}

static VOID VFMW_AfterResetChan(SINT32 ChanID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    PTS_Info_Reset(ChanID);

#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Reset(ChanID);
#endif

    return;
}

static VOID VFMW_AfterSetFrameBufferMode(SINT32 ChanID)
{
    g_ChanInfo[ChanID].IsExternBuffer = 1;

    return;
}

static VOID VFMW_AfterResumeProcess(SINT32 ChanID)
{
#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Start(ChanID);
#endif
    return;
}

static VOID VFMW_AfterPauseProcess(SINT32 ChanID)
{
#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Stop(ChanID);
#endif

    return;
}

static VOID VFMW_AfterConfigProcess(SINT32 ChanID, VOID *pArgs)
{
#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Config(ChanID, pArgs);
#endif

    return;
}

static VOID VFMW_BeforeControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    switch (eCmdID)
    {
        case VDEC_CID_CFG_CHAN:
            VFMW_BeforeCfgChan(ChanID, pArgs);
            break;

        case VDEC_CID_DESTROY_CHAN:
            VFMW_BeforeDestroyChan(ChanID, pArgs);
            break;

        default:
            break;
    }

    return;
}

static VOID VFMW_AfterControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT8 IsSec, SINT32 Result)
{
    switch (eCmdID)
    {
        case VDEC_CID_CREATE_CHAN:
            VFMW_AfterCreateChan(ChanID, pArgs, IsSec, Result);
            break;

        case VDEC_CID_START_CHAN:
            VFMW_AfterStartChan(ChanID, Result);
            break;

        case VDEC_CID_STOP_CHAN:
            VFMW_AfterStopChan(ChanID, Result);
            break;

        case VDEC_CID_RESET_CHAN:
        case VDEC_CID_RESET_CHAN_WITH_OPTION:
            VFMW_AfterResetChan(ChanID, pArgs, IsSec, Result);
            break;

        case VDEC_CID_SET_FRAME_BUFFER_MODE:
            VFMW_AfterSetFrameBufferMode(ChanID);
            break;

        case VDEC_CID_RESUME_PROCESS:
            VFMW_AfterResumeProcess(ChanID);
            break;

        case VDEC_CID_PAUSE_PROCESS:
            VFMW_AfterPauseProcess(ChanID);
            break;

        case VDEC_CID_CFG_CHAN:
            VFMW_AfterConfigProcess(ChanID, pArgs);
            break;

        default:
            break;
    }

    return;
}

static SINT32 VFMW_AdapterControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT8 *pIsAdapterCase)
{
    SINT32 Ret = VDEC_ERR;

    *pIsAdapterCase = 1;

    switch (eCmdID)
    {
        case VDEC_CID_SET_FRAME_RATE_TYPE:
        {
            PTS_FRMRATE_S *pstFrmRate = (PTS_FRMRATE_S *)pArgs;

            Ret = PTS_Info_SetFrmRate(ChanID, pstFrmRate);
            break;
        }

        case VDEC_CID_GET_FRAME_RATE_TYPE:
        {
            PTS_FRMRATE_S *pstFrmRate = (PTS_FRMRATE_S *)pArgs;

            Ret = PTS_Info_GetFrmRate(ChanID, pstFrmRate);
            break;
        }

        default:
        {
            *pIsAdapterCase = 0;
            break;
        }
    }

    return Ret;
}

static VOID VFMW_ImageDebug(SINT32 ChanID, IMAGE *pImage)
{
    if (YUV_IsDumpEnable(ChanID) == VDEC_TRUE)
    {
        YUV_DumpImage(ChanID, pImage);
    }

#ifdef VFMW_CRC_SUPPORT

    if (CRC_IsInWorkMode(ChanID) == VDEC_TRUE)
    {
        CRC_PutImage(ChanID, pImage);
    }

#endif

    return;
}

static SINT32 VFMW_VMM_CB_Alloc(VOID *pParamOut, SINT32 RetVal)
{
    SINT32 Ret = VDEC_ERR;
    SINT32 ChanID;
    VMM_BUFFER_S *pVmmBuf;
    MEM_REPORT_S stMemReport;

    VFMW_ASSERT_RETURN(pParamOut != NULL, VMM_FAILURE);

    pVmmBuf = (VMM_BUFFER_S *)pParamOut;

    if (RetVal != VMM_SUCCESS)
    {
        dprint(PRN_ERROR, "%s name %s failed with RetVal %x\n", __func__, pVmmBuf->BufName, RetVal);
        return VMM_FAILURE;
    }

    OSAL_FP_memset(&stMemReport, 0, sizeof(MEM_REPORT_S));

    OSAL_FP_snprintf(stMemReport.BufName, REPORT_MAX_NAME_LEN, "%s", pVmmBuf->BufName);
    stMemReport.BufName[sizeof(stMemReport.BufName) - 1] = '\0';
    stMemReport.IsMap    = pVmmBuf->Map;
    stMemReport.IsCache  = pVmmBuf->Cache;
    stMemReport.Size     = pVmmBuf->Size;
    stMemReport.UniqueID = pVmmBuf->PrivID;
    stMemReport.PhyAddr  = pVmmBuf->StartPhyAddr;
    stMemReport.VirAddr  = pVmmBuf->pStartVirAddr;

    ChanID = (SINT32)GET_CHAN_ID_BY_UID(stMemReport.UniqueID);

    Ret = VFMW_Control(ChanID, VDEC_CID_BIND_MEM, &stMemReport, sizeof(MEM_REPORT_S));

    return (Ret == VDEC_OK) ? VMM_SUCCESS : VMM_FAILURE;
}

static SINT32 VFMW_VMM_CB_Release(VOID *pParamOut, SINT32 RetVal)
{
    VMM_BUFFER_S *pVmmBuf;

    VFMW_ASSERT_RETURN(pParamOut != NULL, VMM_FAILURE);

    pVmmBuf = (VMM_BUFFER_S *)pParamOut;

    if (RetVal != VMM_SUCCESS)
    {
        dprint(PRN_ERROR, "%s name %s failed with RetVal %x\n", __func__, pVmmBuf->BufName, RetVal);
        return VMM_FAILURE;
    }

    return VMM_SUCCESS;
}

static SINT32 VFMW_VMM_CB_ReleaseBurst(VOID *pParamOut, SINT32 RetVal)
{
    SINT64 *pPrivID;

    VFMW_ASSERT_RETURN(pParamOut != NULL, VMM_FAILURE);

    pPrivID = (SINT64 *)pParamOut;

    if (RetVal != VMM_SUCCESS)
    {
        dprint(PRN_ERROR, "%s PrivID 0x%lld failed with RetVal %x\n", __func__, pPrivID, RetVal);
        return VMM_FAILURE;
    }

    return VMM_SUCCESS;
}

SINT32 VFMW_VMM_CallBack(VMM_CMD_TYPE_E CmdID, VOID *pParamOut, SINT32 RetVal)
{
    SINT32 ret = VMM_FAILURE;

    switch (CmdID)
    {
        case VMM_CMD_Alloc:
            ret = VFMW_VMM_CB_Alloc(pParamOut, RetVal);
            break;

        case VMM_CMD_Release:
            ret = VFMW_VMM_CB_Release(pParamOut, RetVal);
            break;

        case VMM_CMD_ReleaseBurst:
            ret = VFMW_VMM_CB_ReleaseBurst(pParamOut, RetVal);
            break;

        default:
            dprint(PRN_ERROR, "%s unsupport CmdID %d\n", __func__, CmdID);
            break;
    }

    return ret;
}

static SINT32 VFMW_VMM_SetImageOut(IMAGE *pImage)
{
    SINT32 ret;
    VMM_ATTR_S stLocation = {0};
    HI_DRV_VIDEO_FRAME_S *pFrame = (HI_DRV_VIDEO_FRAME_S *)(ULONG)(pImage->pOutFrame);

    stLocation.Location = VMM_LOCATION_OUTSIDE;
    stLocation.PhyAddr = pImage->stDispInfo.luma_phy_addr;
    ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

    if (ret != VMM_SUCCESS)
    {
        dprint(PRN_ERROR, "Set image phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
        goto ERROR_EXIT_0;
    }

    dprint(PRN_DBG, "stLocation.Location = %d, stLocation.PhyAddr = 0x%x\n", stLocation.Location, stLocation.PhyAddr);

    if ((pFrame->enSrcFrameType == HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL || pFrame->enSrcFrameType == HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL)
        && (pImage->stHDRInput.HDR_Metadata_phy_addr != 0))
    {
        stLocation.Location = VMM_LOCATION_OUTSIDE;
        stLocation.PhyAddr = pImage->stHDRInput.HDR_Metadata_phy_addr;
        ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

        if (ret != VMM_SUCCESS)
        {
            dprint(PRN_ERROR, "Set image metadata phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
            goto ERROR_EXIT_1;
        }
    }

    if (pImage->image_id_1 != -1 && pImage->stDispInfo.luma_phy_addr_1 != 0)
    {
        stLocation.Location = VMM_LOCATION_OUTSIDE;
        stLocation.PhyAddr = pImage->stDispInfo.luma_phy_addr_1;
        ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

        if (ret != VMM_SUCCESS)
        {
            dprint(PRN_ERROR, "Set image view 1 phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
            goto ERROR_EXIT_2;
        }
    }

    return VDEC_OK;

ERROR_EXIT_2:

    if (pImage->stHDRInput.HDR_Metadata_phy_addr != 0)
    {
        stLocation.Location = VMM_LOCATION_INSIDE;
        stLocation.PhyAddr = pImage->stHDRInput.HDR_Metadata_phy_addr;
        (VOID)VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);
    }

ERROR_EXIT_1:
    stLocation.Location = VMM_LOCATION_INSIDE;
    stLocation.PhyAddr = pImage->stDispInfo.luma_phy_addr;
    (VOID)VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

ERROR_EXIT_0:

    return VDEC_ERR;
}

SINT32 VFMW_VMM_SetImageIn(IMAGE *pImage)
{
    SINT32 ret;
    VMM_ATTR_S stLocation = {0};

    if (pImage->stDispInfo.luma_phy_addr != 0)
    {
        stLocation.Location = VMM_LOCATION_INSIDE;
        stLocation.PhyAddr = pImage->stDispInfo.luma_phy_addr;
        ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

        if (ret != VMM_SUCCESS)
        {
            dprint(PRN_ERROR, "Set image phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
        }
    }

    dprint(PRN_DBG, "stLocation.Location = %d, stLocation.PhyAddr = 0x%x\n", stLocation.Location, stLocation.PhyAddr);

    if (pImage->stHDRInput.HDR_Metadata_phy_addr != 0)
    {
        stLocation.Location = VMM_LOCATION_INSIDE;
        stLocation.PhyAddr = pImage->stHDRInput.HDR_Metadata_phy_addr;
        ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

        if (ret != VMM_SUCCESS)
        {
            dprint(PRN_ERROR, "Set image metadata phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
        }
    }

    if (pImage->image_id_1 != -1 && pImage->stDispInfo.luma_phy_addr_1 != 0)
    {
        stLocation.Location = VMM_LOCATION_INSIDE;
        stLocation.PhyAddr = pImage->stDispInfo.luma_phy_addr_1;
        ret = VMM_SendCommandBlock(VMM_CMD_BLK_SetLocation, &stLocation);

        if (ret != VMM_SUCCESS)
        {
            dprint(PRN_ERROR, "Set image view 1 phy 0x%x location %d failed.\n", stLocation.PhyAddr, stLocation.Location);
        }
    }

    return VDEC_OK;
}

/*======================================================================*/
/*   External interface                                                 */
/*======================================================================*/
VOID VFMW_OpenModule(VOID)
{
    VDEC_OpenModule();

    OSAL_FP_proc_init();

#ifdef HI_TEE_SUPPORT
    TVP_VDEC_OpenModule();
#endif

    VMM_ModuleInit(VFMW_VMM_CallBack);

#ifdef VDH_DISTRIBUTOR_ENABLE
    VDH_Init_Proc();
#endif

    IMG_Info_Init();

#ifdef VFMW_CRC_SUPPORT
    CRC_Init();
#endif

#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Init();
#endif

    OSAL_FP_memset(&g_ChanInfo, 0, MAX_CHAN_NUM * sizeof(GLB_CHAN_INFO));

    return;
}

VOID VFMW_ExitModule(VOID)
{
#ifdef VFMW_VPP_SUPPORT
    VIR_PP_Deinit();
#endif

#ifdef VFMW_CRC_SUPPORT
    CRC_Exit();
#endif

    IMG_Info_Exit();

#ifdef VDH_DISTRIBUTOR_ENABLE
    VDH_Exit_Proc();
#endif

    VMM_ModuleDeInit();

#ifdef HI_TEE_SUPPORT
    TVP_VDEC_ExitModule();
#endif

    OSAL_FP_proc_exit();

    VDEC_ExitModule();

    return;
}

SINT32 VFMW_Init(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret = VDEC_ERR;

    if (NULL == pArgs)
    {
        dprint(PRN_ERROR, "%s pArgs = NULL\n", __func__);

        return HI_FAILURE;
    }

    if (pArgs->is_secure)
    {
#ifdef HI_TEE_SUPPORT
        ret = TVP_VDEC_TrustDecoderInit(pArgs);
#endif
    }
    else
    {
        ret = VDEC_Init(pArgs);
    }

    return (ret == VDEC_OK) ? HI_SUCCESS : HI_FAILURE;
}

SINT32 VFMW_Exit(UINT8 IsSec)
{
    SINT32 ret = VDEC_ERR;

    if (IsSec)
    {
#ifdef HI_TEE_SUPPORT
        ret = TVP_VDEC_TrustDecoderExit();
#endif
    }
    else
    {
        ret = VDEC_Exit();
    }

    return (ret == VDEC_OK) ? HI_SUCCESS : HI_FAILURE;
}

SINT32 VFMW_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, UINT32 ParamLength)
{
    SINT32 Ret;
    UINT8 IsAdapterCase = 0;
    UINT8 IsSec = 0;

    Ret = VFMW_AdapterControl(ChanID, eCmdID, pArgs, &IsAdapterCase);

    if (IsAdapterCase == 0)
    {
        VFMW_BeforeControl(ChanID, eCmdID, pArgs);

        IsSec = VFMW_GetTVPFlag(ChanID, eCmdID, pArgs);

        if (IsSec)
        {
#ifdef HI_TEE_SUPPORT
            Ret = TVP_VDEC_Control(ChanID, eCmdID, pArgs, ParamLength);
#endif
        }
        else
        {
            Ret = VDEC_Control(ChanID, eCmdID, pArgs);
        }

        VFMW_AfterControl(ChanID, eCmdID, pArgs, IsSec, Ret);
    }

    return (Ret == VDEC_OK) ? HI_SUCCESS : HI_FAILURE;
}

SINT32 VFMW_Suspend(VOID)
{
    SINT32 ret;

    ret = VDEC_Suspend();

    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call VDEC_Suspend Failed!\n", __func__);
    }

#ifdef HI_TEE_SUPPORT
    ret = TVP_VDEC_Suspend();

    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call TVP_VDEC_Suspend Failed!\n", __func__);
    }

#endif

#ifdef VDH_DISTRIBUTOR_ENABLE

    if (g_HalDisable != 1)
    {
        VDH_Suspend();
    }

#endif

    return VDEC_OK;
}

SINT32 VFMW_Resume(VOID)
{
    SINT32 ret;

#ifdef VDH_DISTRIBUTOR_ENABLE

    if (g_HalDisable != 1)
    {
        VDH_Resume();
    }

#endif

    ret = VDEC_Resume();

    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call VDEC_Resume Failed!\n", __func__);
    }

#ifdef HI_TEE_SUPPORT
    ret = TVP_VDEC_Resume();

    if (ret != VDEC_OK)
    {
        HI_FATAL_VFMW("%s Call TVP_VDEC_Resume Failed!\n", __func__);
    }

#endif

    return VDEC_OK;
}

SINT32 VFMW_GetImage(SINT32 ChanID, VOID *pFrame)
{
    SINT32 Result = VDEC_ERR;
    SINT32 ret;
    IMAGE *pImage = (IMAGE *)pFrame;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);

#ifdef HI_TEE_SUPPORT

    if (g_ChanInfo[ChanID].IsSec)
    {
        Result = TVP_VDEC_GetImage(ChanID, pImage);
    }
    else
#endif
    {
        Result = VDEC_GetImage(ChanID, pImage);
    }

    if (Result == VDEC_OK)
    {
        IMG_Info_Convert(ChanID, pImage);

        if (g_ChanInfo[ChanID].IsExternBuffer == 0)
        {
            ret = VFMW_VMM_SetImageOut(pImage);

            if (ret != VDEC_OK)
            {
                dprint(PRN_ERROR, "Set image out failed, ignor this image.\n");
                VFMW_ReleaseImage(ChanID, pImage);

                return VDEC_ERR;
            }
        }

        VFMW_ImageDebug(ChanID, pImage);

        dprint(PRN_FRAME, "=======> %s,%d Phyaddr = 0x%x\n",__func__,__LINE__,pImage->stDispInfo.luma_phy_addr);
    }

    return Result;
}

SINT32 VFMW_ReleaseImage(SINT32 ChanID, VOID *pFrame)
{
    SINT32 Result = VDEC_ERR;
    IMAGE *pImage = (IMAGE *)pFrame;

    VFMW_ASSERT_RETURN(ChanID >= 0 && ChanID < MAX_CHAN_NUM, VDEC_ERR);
    VFMW_ASSERT_RETURN(pImage != NULL, VDEC_ERR);

    dprint(PRN_FRAME, "=======> %s,%d Phyaddr = 0x%x\n",__func__,__LINE__,pImage->stDispInfo.luma_phy_addr);

#ifdef HI_TEE_SUPPORT

    if (g_ChanInfo[ChanID].IsSec)
    {
        Result = TVP_VDEC_ReleaseImage(ChanID, pImage);
    }
    else
#endif
    {
        Result = VDEC_ReleaseImage(ChanID, pImage);
    }

    if (Result == VDEC_OK)
    {
        if (g_ChanInfo[ChanID].IsExternBuffer == 0)
        {
            VFMW_VMM_SetImageIn(pImage);
        }
    }

    return Result;
}

SINT32 VFMW_GlobalReleaseImage(VOID *pFrame)
{
    IMAGE *pImage = (IMAGE *)pFrame;

    dprint(PRN_FRAME, "=======> %s,%d Phyaddr = 0x%x\n",__func__,__LINE__,pImage->stDispInfo.luma_phy_addr);
    return VFMW_VMM_SetImageIn(pImage);
}

