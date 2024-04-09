/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name      : drv_window.h
Version          : Initial Draft
Author          : Hisilicon multimedia software group
Created          : 2012/12/30
Last Modified :
Description   :
Function List :
History          :
******************************************************************************/
#include "drv_win_common.h"
#include "drv_display.h"
#include "drv_window.h"
#include "drv_win_frc.h"
#include "drv_win_policy.h"
#include "drv_win_priv.h"
#include "hi_drv_sys.h"
#include "hi_drv_stat.h"
#include "drv_vdec_ext.h"
#include "drv_disp_hal.h"
#include "drv_disp_alg_service.h"
#include "hi_drv_module.h"
#include "drv_pq_ext.h"
#include "drv_win_alg_ratio.h"

#include "drv_win_hdr.h"
#include "drv_win_share.h"

#include "drv_disp_osal.h"
#include "drv_low_power.h"
#include "drv_async.h"

#include "drv_xdr_adapter.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_HANDLE g_hSlaveWin = 0;

DEFINE_SPINLOCK(g_threadIsr_Lock);


/******************************************************************************
    global object
******************************************************************************/
volatile HI_S32 s_s32WindowGlobalFlag = WIN_DEVICE_STATE_CLOSE;
static DISPLAY_WINDOW_S stDispWindow;
static VIRTUAL_WINDOW_S stVirWindow;

static HI_S32 WIN_QUEUE_Init(DISP_OSAL_LIST *pListHead)
{
    INIT_LIST_HEAD(pListHead);
    return HI_SUCCESS;
}

HI_S32 WIN_QUEUE_DeInit(DISP_OSAL_LIST *pListHead, DISP_OSAL_SPIN *pSpin)
{
    struct list_head    *pos    = HI_NULL;
    struct list_head    *n      = HI_NULL;
    WIN_QUEUE_NODE_S    *pNode  = HI_NULL;
    unsigned long ulflags = 0;

    DISP_OSAL_DownSpin(pSpin, &ulflags);

    if (list_empty(pListHead))
    {
        DISP_OSAL_UpSpin(pSpin, &ulflags);
        return HI_SUCCESS;
    }

    /* Release all node memery in the queue */
    list_for_each_safe(pos, n, pListHead)
    {
        if (pos != pListHead)
        {
            pNode = list_entry(pos, WIN_QUEUE_NODE_S, stNode);
            if (HI_NULL == pNode)
            {
                WIN_ERROR(" null cmd node\n");
                DISP_OSAL_UpSpin(pSpin, &ulflags);
                return HI_FAILURE;
            }
            list_del_init(pos);

            /* Free the memery, include the list_head info, so must delete node from the list first */
            HI_KFREE(HI_ID_VO, pNode);
        }
    }

    DISP_OSAL_UpSpin(pSpin, &ulflags);

    return HI_SUCCESS;
}

static HI_S32  WIN_QUEUE_AddCMD(DISP_OSAL_LIST *pListHead, DISP_OSAL_SPIN *pSpin, WIN_CMD_PARA_S *pstWinCMDPara)
{
    WIN_QUEUE_NODE_S *pNode = HI_NULL;
    unsigned long ulflags = 0;
    pNode = HI_KMALLOC(HI_ID_VO, sizeof(WIN_QUEUE_NODE_S), GFP_ATOMIC);

    if (HI_NULL == pNode)
    {
        WIN_ERROR(" null cmd node\n");
        return HI_FAILURE;
    }
    memset(pNode, 0x00, sizeof(WIN_QUEUE_NODE_S));
    memcpy(&pNode->stWinCMDPara, pstWinCMDPara, sizeof(WIN_CMD_PARA_S));

    DISP_OSAL_DownSpin(pSpin, &ulflags);
    list_add_tail(&(pNode->stNode), pListHead);
    DISP_OSAL_UpSpin(pSpin, &ulflags);

    return HI_SUCCESS;
}


HI_VOID ISR_WinStateTransfer(WINDOW_S *pstWin)
{
    if (pstWin->enState == WIN_STATE_WORK)
    {
        switch (pstWin->enStateNew)
        {
            case WIN_STATE_PAUSE:
            case WIN_STATE_FREEZE:
            {
                pstWin->enState = pstWin->enStateNew;
                pstWin->bUpState = HI_FALSE;
                break;
            }
            case WIN_STATE_WORK:
            case WIN_STATE_RESUME:
            case WIN_STATE_UNFREEZE:
            default :
                pstWin->bUpState = HI_FALSE;
                break;
        }
    }
    else if (pstWin->enState == WIN_STATE_PAUSE)
    {
        switch (pstWin->enStateNew)
        {
            case WIN_STATE_RESUME:
            case WIN_STATE_FREEZE:
            {
                pstWin->enState = pstWin->enStateNew;
                pstWin->bUpState = HI_FALSE;
                break;
            }
            case WIN_STATE_PAUSE:
            case WIN_STATE_WORK:
            case WIN_STATE_UNFREEZE:
            default :
                pstWin->bUpState = HI_FALSE;
                break;
        }
    }
    else if (pstWin->enState == WIN_STATE_FREEZE)
    {
        switch (pstWin->enStateNew)
        {
            case WIN_STATE_UNFREEZE:
            {
                pstWin->enState = pstWin->enStateNew;
                pstWin->bUpState = HI_FALSE;
                break;
            }
            case WIN_STATE_PAUSE:
            case WIN_STATE_FREEZE:
            case WIN_STATE_WORK:
            case WIN_STATE_RESUME:
            default :
                pstWin->bUpState = HI_FALSE;
                break;
        }
    }

    if ((WIN_STATE_RESUME == pstWin->enState)
        || (WIN_STATE_UNFREEZE == pstWin->enState))
    {
        /*no break, enter case 'WIN_STATE_WORK'*/
        pstWin->enState = WIN_STATE_WORK;
    }

    pstWin->bUpState = HI_FALSE;
    //DISP_OSAL_SendEvent(&pstWin->stWinQueueEvent,EVENT_WIN_STATE_UP_COMPLET);

    return;
}

HI_VOID ISR_WinStatePolicy(WINDOW_S *pstWin, WIN_CMD_PARA_S *pstWinCMDPara)
{

    //printk("cmd %d,(%d,%d)\n",pstWinCMDPara->enWinCMD,pstWinCMDPara->u32Args[0],pstWinCMDPara->u32Args[1]);

    if (DRV_WIN_CMD_FREEZE == pstWinCMDPara->enWinCMD)
    {
        pstWin->bUpState = HI_TRUE;
        pstWin->enStateNew = (WIN_STATE_E)pstWinCMDPara->u32Args[0];
        pstWin->stFrz.enFreezeMode = (WIN_STATE_E)pstWinCMDPara->u32Args[1];
    }
    else if (DRV_WIN_CMD_PAUSE == pstWinCMDPara->enWinCMD)
    {
        pstWin->bUpState = HI_TRUE;
        pstWin->enStateNew = (WIN_STATE_E)pstWinCMDPara->u32Args[0];
    }

    else if (DRV_WIN_CMD_RESET == pstWinCMDPara->enWinCMD)
    {
        pstWin->bUpState = HI_TRUE;
        pstWin->bReset = HI_TRUE;
        pstWin->stRst.enResetMode = (HI_DRV_WIN_SWITCH_E)pstWinCMDPara->u32Args[0];
        pstWin->enState = WIN_STATE_WORK;
        pstWin->enStateNew = WIN_STATE_WORK;

    }
    else
    {
        WIN_ERROR("process err cmd %d\n", pstWinCMDPara->enWinCMD);
    }
    ISR_WinStateTransfer(pstWin);

    return;
}


HI_S32 WIN_QUEUE_ProcessCMD( WINDOW_S *pstWin)
{
    struct list_head    *pos    = HI_NULL;
    struct list_head    *n      = HI_NULL;
    WIN_QUEUE_NODE_S    *pNode  = HI_NULL;
    unsigned long ulflags = 0;

    DISP_OSAL_DownSpin(&pstWin->Spin, &ulflags);

    /* Rerurn if no msg */
    if (list_empty(&pstWin->ListHead))
    {
        DISP_OSAL_UpSpin(&pstWin->Spin, &ulflags);

        return HI_SUCCESS;
    }

    /* Check time condition of all messages */
    list_for_each_safe(pos, n, &pstWin->ListHead)
    {
        pNode = list_entry(pos, WIN_QUEUE_NODE_S, stNode);

        if (HI_NULL == pNode)
        {
            DISP_OSAL_UpSpin(&pstWin->Spin, &ulflags);
            return HI_FAILURE;
        }

        ISR_WinStatePolicy(pstWin, &pNode->stWinCMDPara);

        list_del_init(pos);

        /* Free the node memery */
        HI_KFREE(HI_ID_VO, pNode);

    }
    DISP_OSAL_UpSpin(&pstWin->Spin, &ulflags);

    return HI_SUCCESS;
}
static HI_VOID WinDebug_SetDataFlowPath(HI_WIN_RROC_FOR_DEVELOPER_S *pstWinInfoForDeveloper,
                                        HI_DRV_WIN_DATA_FLOW_E eWinDataFlow)
{
    pstWinInfoForDeveloper->eWinDataFlow = eWinDataFlow;
}

static HI_VOID WinTransferConfigInfoToWinShareInfo(WINDOW_S *pstWin,
        WIN_HAL_PARA_S *pstWinPara,
        WIN_INFO_S     *pstWinInfo)
{
    DISP_BUF_NODE_S     *pstDispBufNode = HI_NULL;

    if ((HI_NULL == pstWinPara)
        || (HI_NULL == pstWinInfo)
        || (HI_NULL == pstWin))
    {
        HI_ERR_WIN("NULL pointer para.\n");
        return;
    }

    pstWinInfo->hWinHandle    = pstWin->u32Index;
    pstWinInfo->bWinEnable    = pstWinPara->bRegionEnable;//pstWin->bEnable;
    pstWinInfo->bCloseHdr     = pstWin->stUsingAttr.bCloseHdrPath;

    pstWinInfo->u32LayerId    = pstWinPara->u32LayerNO;
    pstWinInfo->u32RegionNo   = pstWinPara->u32RegionNum;
    pstWinInfo->bRegionEnable = pstWinPara->bRegionEnable;
    pstWinInfo->bRegionMute   = pstWinPara->bRegionMute;
    pstWinInfo->bFlipEn       = pstWinPara->bFlipEn;
    pstWinInfo->bTnrOnVdp     = pstWinPara->bTnrOnVdp;
    pstWinInfo->stLayerAlgMmz = pstWinPara->stLayerAlgMmz;
    pstWinInfo->stIn          = pstWinPara->stIn;
    pstWinInfo->u32Alpha      = pstWinPara->u32Alpha;
    pstWinInfo->u32AllAlpha   = pstWinPara->u32AllAlpha;
    pstWinInfo->u32Zorder   = pstWin->u32Zorder;
    pstWinInfo->bCloseY2R   = pstWinPara->bCloseY2R;

    WIN_SHARE_GetFrameColorSpace(pstWinPara->pstFrame, &pstWinInfo->enInCsc);
    pstWinInfo->pCurrentFrame = pstWinPara->pstFrame;
    pstWinInfo->pNextFrame = WinBuf_GetNextCfgFrm(&pstWin->stBuffer.stWinBP);

    if (HI_NULL != pstWinInfo->pCurrentFrame)
    {
        pstDispBufNode = container_of((HI_U32 *)pstWinInfo->pCurrentFrame, DISP_BUF_NODE_S, u32Data[0]);
        pstWinInfo->enOutCsc = pstDispBufNode->enOutCs;
        pstWinInfo->enOutType = pstDispBufNode->stHdrInfo.enDispOutType;
    }
    else
    {
        pstWinInfo->enOutCsc  = pstWinPara->pstDispInfo->eColorSpace;
        pstWinInfo->enOutType = HI_DRV_DISP_TYPE_NORMAL;//pstWinPara->pstDispInfo->stDispHDRAttr.enDispType;
    }

    pstWinInfo->pstDispInfo   = pstWinPara->pstDispInfo;
    pstWinInfo->stDisp        = pstWinPara->stDisp;
    pstWinInfo->stVideo       = pstWinPara->stVideo;

    pstWinInfo->bHdcpDegradePQ         = pstWinPara->bHdcpDegradePQ;
    pstWinInfo->stHdcpIntermediateRect = pstWinPara->stHdcpIntermediateRect;
    pstWinInfo->enLayerFrostMode       = (HI_DRV_WINDOW_FROST_E)pstWinPara->enLayerFrostMode;

    return;
}

HI_U32 WinGetHDWinNum(HI_VOID)
{
    return stDispWindow.u32WinNumber[HI_DRV_DISPLAY_1];
}

HI_BOOL WinCheckWhetherWbcIsogenyMode(HI_VOID)
{
    if ((stDispWindow.eIsogeny_mode == ISOGENY_WBC_MODE)
        && (stDispWindow.bIsogeny == HI_TRUE))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

HI_BOOL WinCheckWhetherCanToCreate(HI_HANDLE hWin)
{
    WINDOW_S *pstWin =  HI_NULL;
    HI_BOOL bVirtual = HI_FALSE;

    bVirtual = WinCheckVirtual(hWin);
    if (HI_FALSE == bVirtual)
    {
        pstWin = WinGetWindow(hWin);
        if (HI_NULL == pstWin)
        {
            WIN_WARN("WIN is not exist! %#x\n", hWin);
            return HI_FALSE;
        }

        /*in isogeny wbc mode, the sd window is a singleton mode.*/
        if (WinCheckWhetherWbcIsogenyMode()
            && (stDispWindow.u32CurrentHdWindowCounts > 1)
            && (pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE))
        {
            return  HI_FALSE;
        }
    }

    return HI_TRUE;
}



HI_BOOL WinCheckProcCanBeRemoved(HI_HANDLE hWin)
{
    WINDOW_S *pstWin =  HI_NULL;
    HI_BOOL bVirtual = HI_FALSE;

    bVirtual = WinCheckVirtual(hWin);
    if (HI_FALSE == bVirtual)
    {
        pstWin = WinGetWindow(hWin);

        /*when remove slave window from proc, there exists one hd window.
                 since remove proc infor should go first.*/
        if ((HI_NULL != pstWin)
            && WinCheckWhetherWbcIsogenyMode()
            && (stDispWindow.u32CurrentHdWindowCounts != 1)
            && (pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE))
        {
            return HI_FALSE;
        }
        else
        {
            return HI_TRUE;
        }
    }

    return HI_TRUE;
}

HI_BOOL WinCheckWhetherCanToDestroy(HI_HANDLE hWin)
{
    WINDOW_S *pstWin =  HI_NULL;
    HI_BOOL bVirtual = HI_FALSE;

    bVirtual = WinCheckVirtual(hWin);
    if (HI_FALSE == bVirtual)
    {
        pstWin = WinGetWindow(hWin);
        if (HI_NULL == pstWin)
        {
            return HI_FALSE;
        }

        /*only when  the last master win destroyed, the  slave window can be destroyed.*/
        if (WinCheckWhetherWbcIsogenyMode()
            && (stDispWindow.u32CurrentHdWindowCounts != 0)
            && (pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE))
        {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

HI_BOOL   WinGetRegWinManageStatus(HI_VOID)
{
    return stDispWindow.bWinManageStatus;
}

HI_VOID WinSetRegWinManageStatus(HI_BOOL bRegStatus)
{
    stDispWindow.bWinManageStatus = bRegStatus;
    return ;
}

/*
  * when UNF DEQUEUE func works, this func should be called, retrieve the frames.
  */
HI_S32 Win_Dequeue_DisplayedFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrm)
{
    HI_S32 nRet = 0;
    WINDOW_S *pstWin = HI_NULL;

    WinCheckWindow(hWin, pstWin);
    nRet = WinBufferGetULSFrame(&pstWin->stBuffer, pstFrm);

    return nRet;
}
VIRTUAL_S *WinGetVirWindow(HI_U32 u32WinIndex)
{

    if (!stVirWindow.u32WinNumber)
    {
        WIN_ERROR("Not found this window!\n");
        return HI_NULL;
    }

    if (WinGetPrefix(u32WinIndex) != WIN_INDEX_PREFIX)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    if (WinGetDispId(u32WinIndex) != WIN_INDEX_VIRTUAL_CHANNEL)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    if ( WinGetId(u32WinIndex) >= WINDOW_MAX_NUMBER)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    return stVirWindow.pstWinArray[WinGetId(u32WinIndex)];
}

HI_VOID ISR_CallbackForDispModeChange(HI_HANDLE hDst, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo);
HI_VOID ISR_CallbackForWinProcess(HI_VOID *hDst, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo);
HI_VOID WinUpdateDispInfo(WINDOW_S *pstWin, HI_DISP_DISPLAY_INFO_S *pstDsipInfo);

HI_VOID Win_UpdateHdFramInfo(WIN_HAL_PARA_S *pstLayerPara, WIN_CONFIG_S *pstCfg, HI_BOOL bSecure);

HI_VOID WinDisableSingleLayerRegion(WINDOW_S *pstWin, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    WIN_HAL_PARA_S stParam;
    WIN_INFO_S stWinInfo = {0};

    memset(&stParam, 0, sizeof(WIN_HAL_PARA_S));

    if (HI_NULL == pstWin || HI_NULL == pstInfo)
    {
        return;
    }

    if (pstWin->u32VideoLayer != VDP_LAYER_VID_BUTT)
    {
        stParam.bRegionEnable = HI_FALSE;
        stParam.u32LayerNO    = pstWin->u32VideoLayer;
        stParam.u32RegionNum  = pstWin->u32VideoRegionNo;
        stParam.pstDispInfo   = (HI_DISP_DISPLAY_INFO_S *) & (pstInfo->stDispInfo);
        stParam.eOutPutColorSpace = pstInfo->stDispInfo.eColorSpace;

        stParam.stIn = pstInfo->stDispInfo.stFmtResolution;
        stParam.stDisp  = pstInfo->stDispInfo.stFmtResolution;
        stParam.stVideo = pstInfo->stDispInfo.stFmtResolution;
        stParam.u32Alpha = pstWin->stCfg.u32Alpha;
        stParam.u32AllAlpha = pstInfo->stDispInfo.u32Alpha;

        Win_UpdateHdFramInfo(&stParam, &pstWin->stCfg, HI_FALSE);

        WinTransferConfigInfoToWinShareInfo(pstWin, &stParam, &stWinInfo);

        if (VDP_LAYER_VID3 == pstWin->u32VideoLayer)
        {
            pstWin->stVLayerFunc.PF_SetSdLayerCfg(stWinInfo.u32LayerId, &stWinInfo);
        }
        else if ((VDP_LAYER_VID0 == pstWin->u32VideoLayer)
                 || (VDP_LAYER_VID1 == pstWin->u32VideoLayer))
        {
            WIN_SHARE_SetWinInfo(&stWinInfo);
        }
    }

    return;
}

HI_S32 Win_WaitForLayerClosed(WINDOW_S *pstWin)
{
    HI_U32 u32LeftTime = 0,  u32CircleTime = 0;
    HI_DRV_DISP_CALLBACK_INFO_S stInfo;
    HI_SIZE_T irqflag = 0;

    if ((HI_NULL == pstWin) )
    {
        WIN_ERROR("pstWin NULL\n");
        return HI_ERR_VO_NULL_PTR;
    }

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    /*Config regitster to close  hd layer.*/
    memset((HI_VOID *)&stInfo, 0, sizeof(stInfo));
    (HI_VOID)DISP_GetDisplayInfo(pstWin->enDisp, &stInfo.stDispInfo);

    WinDisableSingleLayerRegion(pstWin, &stInfo);
    pstWin->u32VideoLayer = VDP_LAYER_VID_BUTT;

#ifdef HI_VDP_VER_YDJC

    ADAPTER_CloseV0V1Layer();
    (HI_VOID)DISP_GetVbiTimeInfo(pstWin->enDisp, &u32CircleTime, &u32LeftTime);
    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);

    msleep(u32LeftTime);

#else

    (HI_VOID)DISP_GetVbiTimeInfo(pstWin->enDisp, &u32CircleTime, &u32LeftTime);
    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);

    msleep(u32CircleTime + u32LeftTime);
#endif
    return  HI_SUCCESS;
}



HI_VOID WinDisableAllLayerRegion(HI_DRV_DISPLAY_E enDisp, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_U32 i = 0;
    WINDOW_S *pstWin = HI_NULL;

    /*because video-window remmaping, so make a status resetting.*/
    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        pstWin = stDispWindow.pstWinArray[enDisp][i];
        if (pstWin)
        {
            WinDisableSingleLayerRegion(pstWin, pstInfo);
            pstWin->u32VideoLayer = VDP_LAYER_VID_BUTT;
        }
    }

    return;
}

HI_VOID WinLoadNewMapping(HI_DRV_DISPLAY_E enDisp)
{
    HI_U32 i = 0;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stDispWindow.pstWinArray[enDisp][i]
            && (stDispWindow.pstWinArray[enDisp][i]->bEnable))
        {
            stDispWindow.pstWinArray[enDisp][i]->u32VideoLayer
                = stDispWindow.pstWinArray[enDisp][i]->u32VideoLayerNew;

            stDispWindow.pstWinArray[enDisp][i]->u32VideoRegionNo
                = stDispWindow.pstWinArray[enDisp][i]->u32VideoRegionNoNew;
        }
        else if (stDispWindow.pstWinArray[enDisp][i]
                 && (!stDispWindow.pstWinArray[enDisp][i]->bEnable))
        {
            stDispWindow.pstWinArray[enDisp][i]->u32VideoLayer
                = VDP_LAYER_VID_BUTT;
            stDispWindow.pstWinArray[enDisp][i]->u32VideoRegionNo
                = VDP_LAYER_VID_BUTT;
        }

        if (stDispWindow.pstWinArray[enDisp][i])
        {
            stDispWindow.pstWinArray[enDisp][i]->bEnable_Using = stDispWindow.pstWinArray[enDisp][i]->bEnable;
        }
    }

    return ;
}

HI_VOID Win_UpdateVideoLayerSetting(HI_DRV_DISPLAY_E enDstDisp,
                                    const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_U32 i = 0;
    HI_U32 u32LayerEnRecorder = 0;
    WINDOW_S *pWin = HI_NULL;

    /*judge whether the internal hareware-cfg is changed*/
    if (atomic_read(&stDispWindow.bWindowSytemUpdate[enDstDisp]))
    {
        /*video-window remmaping may occurs, so make a status resetting.
                 *and load new mapping.*/
        WinDisableAllLayerRegion(enDstDisp, pstInfo);
        WinLoadNewMapping(enDstDisp);

        /*to adjust the order, becasue win-layermapping changed.*/
        for (i = 0; i < WINDOW_MAX_NUMBER; i++)
        {
            /*check wether the layer is set  or not.*/
            pWin = stDispWindow.pstWinArray[enDstDisp][i];
            if (HI_NULL == pWin)
            {
                continue;
            }

            atomic_set(&pWin->stCfg.bNewAttrFlag, 1);
            pWin->bDispInfoChange = HI_TRUE;

            if (pWin->u32VideoLayer == VDP_LAYER_VID_BUTT)
            {
                continue;
            }

            if (!pWin->stVLayerFunc.PF_CheckLayerInit(pWin->u32VideoLayer))
            {
                (HI_VOID)pWin->stVLayerFunc.PF_InitialLayer(pWin->u32VideoLayer);
            }

            if ((pWin->stWinLayerOpt.bEffective)
                && (pWin->stWinLayerOpt.layerOptType == LAYER_OPT_ZORDER_ADJUST))
            {
                if (((HI_U32)pWin->stWinLayerOpt.enLayerOpt) == HI_DRV_DISP_ZORDER_MOVETOP)
                {
                    pWin->stVLayerFunc.PF_MovTop(pWin->u32VideoLayer);
                }
                else if (((HI_U32)pWin->stWinLayerOpt.enLayerOpt) == HI_DRV_DISP_ZORDER_MOVEBOTTOM)
                {
                    pWin->stVLayerFunc.PF_MovBottom(pWin->u32VideoLayer);
                }

                /*clear the flag, to avoid taking effect next period.*/
                pWin->stWinLayerOpt.bEffective = HI_FALSE;
                pWin->stWinLayerOpt.layerOptType = LAYER_OPT_BUTT;
                pWin->stWinLayerOpt.enLayerOpt = HI_DRV_DISP_ZORDER_BUTT;
            }

            u32LayerEnRecorder |= (1 << (pWin->u32VideoLayer));

            /* Low power strategy: Dolby hdr win mode,will occupy two video layers. */
            if (HI_DRV_WINDOW_MODE_DOLBY == pWin->enWinMode)
            {
                u32LayerEnRecorder |= (1 << VDP_LAYER_VID0);
                u32LayerEnRecorder |= (1 << VDP_LAYER_VID1);
            }
        }

        atomic_set(&stDispWindow.bWindowSytemUpdate[enDstDisp], 0);
        DISP_OSAL_SendEvent(&stDispWindow.stWinSytemQueueEvent, EVENT_WIN_SYSTEM_UP_COMPLET);

        /* Update low power PIP strategy */
        (HI_VOID)LowPower_OperatePipLayer(u32LayerEnRecorder);
    }

    return ;
}


HI_VOID ISR_CallbackForWinManage(HI_VOID *hDst, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_DISPLAY_E enDstDisp = (HI_DRV_DISPLAY_E)hDst;
    HI_SIZE_T irqflag = 0;

    HI_PQ_ACC_HISTGRAM_S stACCHistGram;
    memset(&stACCHistGram, 0, sizeof(HI_PQ_ACC_HISTGRAM_S));
    DRV_PQ_GetACCHistGram(&stACCHistGram);
    DRV_PQ_UpdateACCHistGram(&stACCHistGram);
    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    Win_UpdateVideoLayerSetting(enDstDisp, pstInfo);
    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    return ;
}

HI_S32 WinRegWinManageCallback(HI_DRV_DISPLAY_E enDisp)
{
    HI_DRV_DISP_CALLBACK_S stCB;
    HI_S32 nRet = HI_SUCCESS;

    DispCheckID(enDisp);

    stCB.hDst  = (HI_VOID *)(unsigned long)enDisp;
    stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_HIGH;
    stCB.pfDISP_Callback = ISR_CallbackForWinManage;

    nRet = DISP_RegCallback(enDisp, HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);
    if (nRet)
    {
        WIN_ERROR("WIN register callback failed !\n");
    }

    return nRet;
}

HI_S32 WinUnRegWinManageCallback(HI_DRV_DISPLAY_E enDisp)
{
    HI_DRV_DISP_CALLBACK_S stCB;
    HI_S32 nRet = HI_SUCCESS;

    DispCheckID(enDisp);

    stCB.hDst  = (HI_VOID *)(unsigned long)enDisp;
    stCB.pfDISP_Callback = ISR_CallbackForWinManage;
    stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_HIGH;

    nRet = DISP_UnRegCallback(enDisp, HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);
    if (nRet)
    {
        WIN_ERROR("WIN unregister callback failed!\n");
    }

    return nRet;
}

HI_S32 WIN_DestroyStillFrame(HI_DRV_VIDEO_FRAME_S *pstReleaseFrame)
{
    HI_U32 i;
    WIN_RELEASE_FRM_S *pstWinRelFrame = &stDispWindow.stWinRelFrame;

    for (i = 0; i < MAX_RELEASE_NO; i++)
    {
        if (!pstWinRelFrame->pstNeedRelFrmNode[i] )
        {
            pstWinRelFrame->pstNeedRelFrmNode[i] = pstReleaseFrame;
            pstWinRelFrame->enThreadEvent = EVENT_RELEASE;
            wake_up(&pstWinRelFrame->stWaitQueHead);
            return HI_SUCCESS;
        }
    }

    WIN_ERROR("Release still frame failed ,buff is full!\n");
    return HI_FAILURE;
}

HI_S32 WinReleaseFrameThreadProcess(HI_VOID *pArg)
{
    HI_U32 i;
    WIN_RELEASE_FRM_S *pstWinRelFrame = pArg;

    /*if stop refush release frame buffer*/
    while (!kthread_should_stop() )
    {
        for ( i = 0; i < MAX_RELEASE_NO; i++)
        {
            if (pstWinRelFrame->pstNeedRelFrmNode[i])
            {
                if (HI_DRV_FRAME_VDP_ALLOCATE_STILL == pstWinRelFrame->pstNeedRelFrmNode[i]->u32StillFrame)
                {
                    DestroyStillFrame(pstWinRelFrame->pstNeedRelFrmNode[i]);
                    pstWinRelFrame->pstNeedRelFrmNode[i] = HI_NULL;
                }
            }
        }

        WinBuf_RetAllMemRefCnts();

        pstWinRelFrame->enThreadEvent = EVENT_BUTT;
        wait_event_timeout(pstWinRelFrame->stWaitQueHead, (EVENT_RELEASE == pstWinRelFrame->enThreadEvent), 5);
    }

    WinBuf_RetAllMemRefCnts();
    return HI_SUCCESS;
}

HI_S32 WinCreatReleaseFrameThread(HI_VOID )
{
    WIN_RELEASE_FRM_S *pstWinRelFrame = &stDispWindow.stWinRelFrame;

    memset(pstWinRelFrame, 0, sizeof(WIN_RELEASE_FRM_S));
    pstWinRelFrame->hThread =
        kthread_create(WinReleaseFrameThreadProcess, (HI_VOID *)(&stDispWindow.stWinRelFrame), "HI_WIN_ReleaseFrameProcess");

    init_waitqueue_head( &(pstWinRelFrame->stWaitQueHead) );
    if (IS_ERR(pstWinRelFrame->hThread))
    {
        WIN_FATAL("Can not create thread.\n");
        return HI_ERR_VO_CREATE_ERR;
    }

    wake_up_process(pstWinRelFrame->hThread);
    return HI_SUCCESS;
}

HI_S32 WinDestroyReleaseFrameThread(HI_VOID )
{
    HI_S32 s32Ret;
    HI_S32 s32Times = 0;
    WIN_RELEASE_FRM_S *pstWinRelFrame = &stDispWindow.stWinRelFrame;

    /*reflush release buffer */
    pstWinRelFrame->enThreadEvent = EVENT_RELEASE;
    wake_up(&pstWinRelFrame->stWaitQueHead);

    for (s32Times = 0 ; s32Times < 100; s32Times++)
    {
        if (EVENT_BUTT == pstWinRelFrame->enThreadEvent)
        {
            pstWinRelFrame->enThreadEvent = EVENT_RELEASE;
            s32Ret = kthread_stop(pstWinRelFrame->hThread);

            if (s32Ret != HI_SUCCESS)
            {
                WIN_FATAL("Destory Thread Error.\n");
            }
            return HI_SUCCESS;
        }
        msleep(10);
    }

    return HI_FAILURE;
}

HI_S32 WIN_Init(HI_VOID)
{
    HI_BOOL bDispInitFlag;
    HI_S32 s32Ret;
    DISP_INTF_OPERATION_S stFunction = {0};

    if (WIN_DEVICE_STATE_CLOSE != s_s32WindowGlobalFlag)
    {
        WIN_INFO("VO has been inited!\n");
        return HI_SUCCESS;
    }

    DISP_GetInitFlag(&bDispInitFlag);
    if (HI_TRUE != bDispInitFlag)
    {
        WIN_ERROR("Display is not inited!\n");
        return HI_ERR_VO_DEPEND_DEVICE_NOT_READY;
    }

    if (HI_SUCCESS != BP_CreateBlackFrame())
    {
        WIN_ERROR("Create Black Frame failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    DISP_MEMSET(&stDispWindow, 0, sizeof(DISPLAY_WINDOW_S));
    VideoLayer_Init();

    (HI_VOID)DISP_HAL_GetOperation(&stFunction);
    if (HI_NULL == stFunction.PF_GetIsogenyMode)
    {
        WIN_ERROR("PF_GetIsogenyMode is NULL!\n");
        return HI_ERR_VO_NULL_PTR;
    }
    (HI_VOID)stFunction.PF_GetIsogenyMode(&stDispWindow.eIsogeny_mode);

    /*first, judge whether iso-geny or not.*/
    if (DISP_IsFollowed(HI_DRV_DISPLAY_0)
        || DISP_IsFollowed(HI_DRV_DISPLAY_1))
    {
        stDispWindow.bIsogeny = HI_TRUE;
    }
    else
    {
        stDispWindow.bIsogeny = HI_FALSE;
    }
    DISP_OSAL_InitEvent(&stDispWindow.stWinSytemQueueEvent, EVENT_WIN_NOTHING);
#ifdef VDP_ISOGENY_SUPPORT
    if ( HI_TRUE == WinCheckWhetherWbcIsogenyMode())
    {
        s32Ret = ISOGBNY_Init();
        if ( HI_SUCCESS != s32Ret )
        {
            WIN_ERROR("WIN ISOGBNY_Init failed in %s!\n", __FUNCTION__);
            return HI_ERR_VO_CREATE_ERR;
        }
    }
#endif

    DISP_MEMSET(&stVirWindow, 0, sizeof(VIRTUAL_WINDOW_S));
    s32Ret = WinCreatReleaseFrameThread();
    if (HI_SUCCESS != s32Ret)
    {
        WIN_ERROR("win Create Release Frame Thread failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }


    /* Low power init */
    if (HI_SUCCESS != LowPower_Init())
    {
        WIN_ERROR("Low power is not inited!\n");
        return HI_ERR_VO_DEPEND_DEVICE_NOT_READY;
    }

    s_s32WindowGlobalFlag = WIN_DEVICE_STATE_OPEN;

    return HI_SUCCESS;
}

HI_S32 WIN_DeInit(HI_VOID)
{
    HI_S32 i, j, s32Ret;

    if (WIN_DEVICE_STATE_CLOSE == s_s32WindowGlobalFlag)
    {
        WIN_INFO("VO is not inited!\n");
        return HI_SUCCESS;
    }

    /*close all the windows, since slave channel is not visible to  upper level
        * all the things done by lower driver.
        */
    for (i = HI_DRV_DISPLAY_1; i < HI_DRV_DISPLAY_BUTT; i++)
    {
        stDispWindow.u32WinNumber[i] = 0;

        for (j = 0; j < WINDOW_MAX_NUMBER; j++)
        {
            if (stDispWindow.pstWinArray[i][j])
            {
                (HI_VOID)WIN_Destroy(stDispWindow.pstWinArray[i][j]->u32Index);
                stDispWindow.pstWinArray[i][j] = HI_NULL;
            }
        }
    }

    /*close all the virtual windows.*/
    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stVirWindow.pstWinArray[i])
        {
            WIN_VIR_Destroy(stVirWindow.pstWinArray[i]);
            stVirWindow.pstWinArray[i] = HI_NULL;
        }
    }

    stVirWindow.u32WinNumber = 0;

    if (WinGetRegWinManageStatus())
    {
        WinUnRegWinManageCallback(HI_DRV_DISPLAY_1);
        WinUnRegWinManageCallback(HI_DRV_DISPLAY_0);
        WinSetRegWinManageStatus(HI_FALSE);
    }

    s32Ret = WinDestroyReleaseFrameThread();
    if (HI_SUCCESS != s32Ret)
    {
        WIN_ERROR("win Destroy Release Frame Thread failed!\n");
    }

#ifdef VDP_ISOGENY_SUPPORT

    if ( HI_TRUE == WinCheckWhetherWbcIsogenyMode())
    {
        s32Ret = ISOGBNY_DeInit();
        if ( HI_SUCCESS != s32Ret )
        {
            WIN_ERROR("WIN ISOGBNY_DeInit failed in %s!\n", __FUNCTION__);
            return HI_ERR_VO_CREATE_ERR;
        }
    }

#endif

    VideoLayer_DeInit();
    BP_DestroyBlackFrame();

    /* Low power deinit */
    if (HI_SUCCESS != LowPower_DeInit())
    {
        return HI_FAILURE;
    }
    VDP_ASYNC_DeInit();

    s_s32WindowGlobalFlag = WIN_DEVICE_STATE_CLOSE;

    WIN_INFO("VO has been DEinited!\n");
    return HI_SUCCESS;
}

WINDOW_S *WinGetWindow(HI_U32 u32WinIndex);

HI_S32 WIN_Suspend(HI_VOID)
{
    if (WIN_DEVICE_STATE_OPEN != s_s32WindowGlobalFlag)
    {
        WIN_WARN("WIN is not inited or suspended in %s!\n", __FUNCTION__);
        return HI_ERR_VO_NO_INIT;
    }

    s_s32WindowGlobalFlag = WIN_DEVICE_STATE_SUSPEND;

    return HI_SUCCESS;
}

HI_S32 WIN_Resume(HI_VOID)
{
    if (s_s32WindowGlobalFlag == WIN_DEVICE_STATE_SUSPEND)
    {
        VIDEO_LAYER_FUNCTIONG_S *pF = VideoLayer_GetFunctionPtr();

        s_s32WindowGlobalFlag = WIN_DEVICE_STATE_OPEN;
        if (pF)
        {
            pF->PF_SetAllLayerDefault();
        }
    }

    return HI_SUCCESS;
}


HI_BOOL WinCheckDolbyMode(HI_VOID)
{
    HI_S32 s32Index = 0;
    HI_U32 u32HdWinNum = 0;
    HI_BOOL bExistDolbyMode = HI_FALSE;
    WINDOW_S *pstWin = HI_NULL;

    u32HdWinNum = WinGetHDWinNum();

    if (u32HdWinNum != 1)
    {
        bExistDolbyMode = HI_FALSE;
    }
    else
    {
        for (s32Index = 0; s32Index < WINDOW_MAX_NUMBER; s32Index++)
        {
            pstWin = stDispWindow.pstWinArray[HI_DRV_DISPLAY_1][s32Index];
            if ((HI_NULL != pstWin)
                && (HI_DRV_WINDOW_MODE_DOLBY == pstWin->enWinMode))
            {
                bExistDolbyMode = HI_TRUE;
                break;
            }
        }
    }

    return bExistDolbyMode;
}

HI_S32 WinTestAddWindow(HI_DRV_DISPLAY_E  enDisp)
{
    HI_U32 u32WinNumber = 0;

    if (enDisp >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_ERROR("Invalid Disp = 0x%x\n", enDisp);
        return HI_ERR_VO_INVALID_PARA;
    }
    if (WinCheckDolbyMode())
    {
        HI_ERR_WIN("Exist HDR mode window!Can not create new window anymore!\n");
        return HI_ERR_VO_CREATE_ERR;
    }

#ifdef HI_GFX_USE_G3
    if (!DISP_IsSameSource(enDisp) && HI_DRV_DISPLAY_0 == enDisp)
    {
        if (stDispWindow.u32WinNumber[HI_DRV_DISPLAY_0] >= 1)
        {
            return HI_ERR_VO_WIN_UNSUPPORT;
        }
    }
#endif

    if (stDispWindow.eIsogeny_mode == ISOGENY_WBC_MODE)
    {
        u32WinNumber = (enDisp == HI_DRV_DISPLAY_1) ? WINDOW_MAX_NUMBER : 1;
    }
    else
    {
        u32WinNumber = WINDOW_MAX_NUMBER;
    }

    if ( stDispWindow.u32WinNumber[enDisp] < u32WinNumber)
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_ERR_VO_INVALID_OPT;
    }
}

HI_U32 WinGetPrefix(HI_U32 u32WinIndex)
{
    return (HI_U32)(u32WinIndex & WIN_INDEX_PREFIX_MASK);
}

HI_U32 WinGetDispId(HI_U32 u32WinIndex)
{
    return (HI_U32)((u32WinIndex >> WIN_INDEX_DISPID_SHIFT_NUMBER) & WIN_INDEX_DISPID_MASK);
}

HI_U32 WinGetId(HI_U32 u32WinIndex)
{
    return (HI_U32)(u32WinIndex & WINDOW_INDEX_NUMBER_MASK);
}

HI_U32 WinMakeVirIndex(HI_U32 u32WinIndex)
{
    /*
     *    0x12               34                         56                78
     *         WIN_INDEX_PREFIX  WIN_INDEX_VIRTUAL_CHANNEL   u32WinIndex
     *
     */
    return (HI_U32)(   WIN_INDEX_PREFIX
                       | ( ( WIN_INDEX_VIRTUAL_CHANNEL & WIN_INDEX_DISPID_MASK) \
                           << WIN_INDEX_DISPID_SHIFT_NUMBER
                         )
                       | (u32WinIndex & WINDOW_INDEX_NUMBER_MASK)
                   );
}

HI_U32 WinMakeIndex(HI_DRV_DISPLAY_E enDisp, HI_U32 u32WinIndex)
{
    return (HI_U32)(   (WIN_INDEX_PREFIX)
                       | ( ( (HI_U32)enDisp & WIN_INDEX_DISPID_MASK) \
                           << WIN_INDEX_DISPID_SHIFT_NUMBER
                         )
                       | (u32WinIndex & WINDOW_INDEX_NUMBER_MASK)
                   );
}

HI_U32 WinGetIndex(HI_HANDLE hWin, HI_DRV_DISPLAY_E *enDisp, HI_U32 *u32WinIndex)
{

    *enDisp = (hWin & 0xff00) >> WIN_INDEX_DISPID_SHIFT_NUMBER;
    *u32WinIndex = hWin & 0xff;

    return HI_SUCCESS;
}

HI_S32 WinAddVirWindow(VIRTUAL_S *pstWin)
{
    HI_S32 i;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (!stVirWindow.pstWinArray[i])
        {
            pstWin->u32Index =    WinMakeVirIndex((HI_U32)i);
            stVirWindow.pstWinArray[i] = pstWin;
            stVirWindow.u32WinNumber++;

            return HI_SUCCESS;
        }
    }
    return HI_ERR_VO_CREATE_ERR;
}
HI_S32 WinDelVirWindow(HI_U32 u32WinIndex)
{
    if ( WinGetPrefix(u32WinIndex) != WIN_INDEX_PREFIX)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_FAILURE;
    }

    if ( WinGetDispId(u32WinIndex) != WIN_INDEX_VIRTUAL_CHANNEL)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_FAILURE;
    }

    if ( WinGetId(u32WinIndex) >= WINDOW_MAX_NUMBER)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_FAILURE;
    }

    if (!stVirWindow.u32WinNumber)
    {
        WIN_ERROR("Not found this window!\n");
        return HI_FAILURE;
    }

    if (stVirWindow.pstWinArray[WinGetId(u32WinIndex)])
    {
        stVirWindow.pstWinArray[WinGetId(u32WinIndex)] = HI_NULL;
        stVirWindow.u32WinNumber--;
    }
    else
    {
        WIN_ERROR("Not found this window!\n");
    }

    return HI_SUCCESS;
}


HI_S32 WinAddWindow(HI_DRV_DISPLAY_E enDisp, WINDOW_S *pstWin)
{
    HI_S32 i;

    if (enDisp >= HI_DRV_DISPLAY_BUTT)
    {
        return HI_ERR_VO_CREATE_ERR;
    }

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (!stDispWindow.pstWinArray[(HI_U32)enDisp][i])
        {
            pstWin->u32Index =    WinMakeIndex(enDisp, (HI_U32)i);

            stDispWindow.pstWinArray[(HI_U32)enDisp][i] = pstWin;
            stDispWindow.u32WinNumber[(HI_U32)enDisp]++;

            return HI_SUCCESS;
        }
    }

    return HI_ERR_VO_CREATE_ERR;
}



HI_S32 WinDelWindow(HI_U32 u32WinIndex)
{
    if ( WinGetPrefix(u32WinIndex) != WIN_INDEX_PREFIX)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_ERR_VO_WIN_NOT_EXIST;
    }

    if (  WinGetDispId(u32WinIndex) >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_ERR_VO_WIN_NOT_EXIST;
    }

    if ( WinGetId(u32WinIndex) >= WINDOW_MAX_NUMBER)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_ERR_VO_WIN_NOT_EXIST;
    }

    if (!stDispWindow.u32WinNumber[WinGetDispId(u32WinIndex)])
    {
        WIN_ERROR("Not found this window!\n");
        return HI_ERR_VO_WIN_NOT_EXIST;
    }

    if (stDispWindow.pstWinArray[WinGetDispId(u32WinIndex)][WinGetId(u32WinIndex)])
    {
        stDispWindow.pstWinArray[WinGetDispId(u32WinIndex)][WinGetId(u32WinIndex)] = HI_NULL;
        stDispWindow.u32WinNumber[WinGetDispId(u32WinIndex)]--;
    }
    else
    {
        WIN_ERROR("Not found this window!\n");
    }

    return HI_SUCCESS;
}

WINDOW_S *WinGetWindow(HI_U32 u32WinIndex)
{
    if ( WinGetPrefix(u32WinIndex) != WIN_INDEX_PREFIX)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    if (  WinGetDispId(u32WinIndex) >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_WARN("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    if (!stDispWindow.u32WinNumber[WinGetDispId(u32WinIndex)])
    {
        WIN_WARN("Not found this window!\n");
        return HI_NULL;
    }
    if ( WinGetId(u32WinIndex) >= WINDOW_MAX_NUMBER)
    {
        WIN_ERROR("Invalid window index = 0x%x\n", u32WinIndex);
        return HI_NULL;
    }

    return stDispWindow.pstWinArray[WinGetDispId(u32WinIndex)][WinGetId(u32WinIndex)];
}



/******************************************************************************
    internal function
******************************************************************************/

HI_VOID window_revise(HI_RECT_S *pstToBeRevisedRect_tmp,
                      const HI_RECT_S *ptmp_virtscreen)
{
    /*give a basic    process of width and height.*/
    if (pstToBeRevisedRect_tmp->s32Width < WIN_OUTRECT_MIN_WIDTH)
    {
        pstToBeRevisedRect_tmp->s32Width = WIN_OUTRECT_MIN_WIDTH;
    }

    /*here we delete the width max branch, because we support tc 2-screen,
        *even 3-screen display.
        * here we do not make a limit,  all the behavior depends on the zme performance.
        */

    if (pstToBeRevisedRect_tmp->s32Height < WIN_OUTRECT_MIN_HEIGHT)
    {
        pstToBeRevisedRect_tmp->s32Height = WIN_OUTRECT_MIN_HEIGHT;
    }

    return ;
}

/*previously, we do division first, then do multiplication
 *so we lose precision. now we invert the  order.
 */
static HI_S32 Win_Caculate(HI_S32 ratioA, HI_S32 ratioB, HI_S32 virtualValue, HI_S32 *s32CalcReult)
{
    if (ratioB)
    {
        *s32CalcReult = ((virtualValue * ratioA) * 100) / ratioB;
        return HI_SUCCESS;
    }
    else
    {
        WIN_ERROR("denominator is zero\n");
        return HI_FAILURE;
    }
}

/*this func is for both graphics and video    virtual screen deal, it's a common function.*/
HI_S32 WinOutRectSizeConversion(const HI_RECT_S *pstCanvas,
                                const HI_DRV_DISP_OFFSET_S *pstOffsetInfo,
                                const HI_RECT_S *pstFmtResolution,
                                HI_RECT_S *pstToBeRevisedRect,
                                HI_RECT_S *pstRevisedRect)
{
    HI_U32 zmeDestWidth = 0, zmeDestHeight = 0;
    HI_DRV_DISP_OFFSET_S tmp_offsetInfo = {0};
    HI_S32 Ret = HI_FAILURE;
    HI_S32 s32CalcResult = 0;
    HI_RECT_S stToBeRevisedRect_tmp = *pstToBeRevisedRect;

    tmp_offsetInfo = *pstOffsetInfo;

    /*for browse mode, revise in virt screen .*/
    window_revise(&stToBeRevisedRect_tmp, pstCanvas);

    zmeDestWidth = (pstFmtResolution->s32Width - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    zmeDestHeight = (pstFmtResolution->s32Height - tmp_offsetInfo.u32Top - tmp_offsetInfo.u32Bottom);

    if (pstCanvas->s32Width != stToBeRevisedRect_tmp.s32Width)
    {
        Ret = Win_Caculate(zmeDestWidth,
                           pstCanvas->s32Width,
                           stToBeRevisedRect_tmp.s32Width,
                           &s32CalcResult);
        if (Ret != HI_SUCCESS)
        {
            return Ret;
        }

        pstRevisedRect->s32Width = s32CalcResult / 100;
    }
    else
    {
        pstRevisedRect->s32Width = zmeDestWidth;
    }

    if (pstCanvas->s32Height != stToBeRevisedRect_tmp.s32Height)
    {
        Ret = Win_Caculate(zmeDestHeight,
                           pstCanvas->s32Height,
                           stToBeRevisedRect_tmp.s32Height,
                           &s32CalcResult);

        if (Ret != HI_SUCCESS)
        {
            return Ret;
        }

        pstRevisedRect->s32Height = s32CalcResult / 100;
    }
    else
    {
        pstRevisedRect->s32Height = zmeDestHeight;
    }


    Ret = Win_Caculate(zmeDestWidth,
                       pstCanvas->s32Width,
                       stToBeRevisedRect_tmp.s32X,
                       &s32CalcResult);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    pstRevisedRect->s32X = s32CalcResult / 100 + tmp_offsetInfo.u32Left;

    Ret = Win_Caculate(zmeDestHeight,
                       pstCanvas->s32Height,
                       stToBeRevisedRect_tmp.s32Y,
                       &s32CalcResult);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    pstRevisedRect->s32Y = s32CalcResult / 100 + tmp_offsetInfo.u32Top;
    WinOutRectAlign(pstRevisedRect);

    /*for browse mode, revise in virt screen .*/
    window_revise(pstRevisedRect, pstFmtResolution);
    return HI_SUCCESS;
}

HI_S32 WinOutRectSizeConversionByType(const HI_DISP_DISPLAY_INFO_S  *pstInfo,
                                      HI_RECT_S *pstRevisedRect,
                                      WINDOW_S *pstWin)
{
    HI_RECT_S stCanvas = {0}, stOutRectOrigin = {0};
    HI_DRV_DISP_OFFSET_S stOffsetInfo = {0};

    memset((void *)&stCanvas, 0, sizeof(HI_RECT_S));
    memset((void *)&stOffsetInfo, 0, sizeof(HI_DRV_DISP_OFFSET_S));

    stOutRectOrigin = pstWin->stCfg.stAttrBuf.stOutRect;

    if (!stOutRectOrigin.s32Width || !stOutRectOrigin.s32Height)
    {
        if (pstWin->bVirtScreenMode)
        {
            stOutRectOrigin = pstInfo->stVirtaulScreen;
        }
        else
        {
            stOutRectOrigin = pstInfo->stFmtResolution;
        }
    }

    if (pstWin->bVirtScreenMode)
    {
        (HI_VOID)DISP_GetVirtScreen(pstWin->enDisp, &stCanvas);
        stOffsetInfo = pstInfo->stOffsetInfo;

#ifndef HI_VO_OFFSET_EFFECTIVE_WHEN_WIN_FULL
        if (((pstWin->stCfg.stAttrBuf.stOutRect.s32Width == 0)
             || (pstWin->stCfg.stAttrBuf.stOutRect.s32Height == 0))
            || ((pstWin->stCfg.stAttrBuf.stOutRect.s32Width == stCanvas.s32Width)
                && (pstWin->stCfg.stAttrBuf.stOutRect.s32Height == stCanvas.s32Height))
           )
        {
            memset((void *)&stOffsetInfo, 0, sizeof(HI_DRV_DISP_OFFSET_S));
        }
#endif
    }
    else
    {
        stOffsetInfo.u32Left = 0;
        stOffsetInfo.u32Top = 0;
        stOffsetInfo.u32Right = 0;
        stOffsetInfo.u32Bottom = 0;
        stCanvas = pstWin->stDispInfo.stWinCurrentFmt;
    }

    (HI_VOID)WinOutRectSizeConversion(&stCanvas,
                                      &stOffsetInfo,
                                      &pstInfo->stFmtResolution,
                                      &stOutRectOrigin,
                                      pstRevisedRect);

    return HI_SUCCESS;
}


HI_S32 WindowRedistributeProcess(WINDOW_S *tmpWindow);
HI_S32 WindowRedistributeProcess_Wait(WINDOW_S *tmpWindow, HI_BOOL bWait);

static HI_VOID WinZorderSave(HI_U32 *pU32Array, HI_DRV_DISPLAY_E enDisp)
{
    HI_U32 u32Cnt = 0, i = 0;

    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if (stDispWindow.pstWinArray[enDisp][u32Cnt])
        {
            i++;
        }
    }

    for (u32Cnt = 0; u32Cnt < i; u32Cnt++)
    {
        if (stDispWindow.pstWinArray[enDisp][u32Cnt])
        {
            pU32Array[u32Cnt] = stDispWindow.pstWinArray[enDisp][u32Cnt]->u32Zorder;
        }
    }

    return ;
}

static HI_VOID WinZorderRestore(HI_U32 *pU32Array, HI_DRV_DISPLAY_E enDisp)
{
    HI_U32 u32Cnt = 0, i = 0;

    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if (stDispWindow.pstWinArray[enDisp][u32Cnt])
        {
            i++;
        }
    }

    for (u32Cnt = 0; u32Cnt < i; u32Cnt++)
    {
        if ((stDispWindow.pstWinArray[enDisp][u32Cnt]))
        {
            stDispWindow.pstWinArray[enDisp][u32Cnt]->u32Zorder = pU32Array[u32Cnt];
        }
    }

    return;
}

static HI_S32 WinZorderDelete(WINDOW_S *pstWin)
{
    HI_U32 u32Cnt = 0;

    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if ((stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
            && (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder > pstWin->u32Zorder))
        {
            stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder --;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 WinZorderMoveTop(WINDOW_S *pstWin)
{
    HI_U32 u32Cnt = 0, i = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ZorderBak[WINDOW_MAX_NUMBER] = {0};
    HI_SIZE_T irqflag = 0;

    WinZorderSave(u32ZorderBak, pstWin->enDisp);

    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
        {
            i++;
        }
    }

    /*for existing window's move top.*/
    if (pstWin->u32Index)
    {
        for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
        {
            if ((stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
                && (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder > pstWin->u32Zorder))
            {
                stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder --;
            }
        }

        pstWin->u32Zorder = i - 1;
    }
    else
    {
        /*for new window's move top.*/
        pstWin->u32Zorder = i;
    }

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    ret = WindowRedistributeProcess(pstWin);
    if (ret)
    {
        WinZorderRestore(u32ZorderBak, pstWin->enDisp);
    }

    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_FALSE);

    return ret;
}

static HI_S32 WinZorderMoveBottom(WINDOW_S *pstWin)
{
    HI_U32 u32Cnt = 0, i = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ZorderBak[WINDOW_MAX_NUMBER] = {0};
    HI_SIZE_T irqflag = 0;

    WinZorderSave(u32ZorderBak, pstWin->enDisp);
    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
        {
            i++;
        }
    }

    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if ((stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
            && (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder < pstWin->u32Zorder))
        {
            stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder ++;
        }
    }

    pstWin->u32Zorder = 0;

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    ret =  WindowRedistributeProcess(pstWin);
    if (ret)
    {
        WinZorderRestore(u32ZorderBak, pstWin->enDisp);
    }

    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_FALSE);

    return ret;
}

static HI_S32 WinZorderMoveUp(WINDOW_S *pstWin)
{
    HI_U32 u32Cnt = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ZorderBak[WINDOW_MAX_NUMBER] = {0};
    HI_SIZE_T irqflag = 0;

    WinZorderSave(u32ZorderBak, pstWin->enDisp);
    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if ((stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
            && (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder == (pstWin->u32Zorder + 1)))
        {
            pstWin->u32Zorder ++;
            stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder --;
            break;
        }
    }

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);

    ret =  WindowRedistributeProcess(pstWin);
    if (ret)
    {
        WinZorderRestore(u32ZorderBak, pstWin->enDisp);
    }

    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_FALSE);

    return ret;
}

static HI_S32 WinZorderMoveDown(WINDOW_S *pstWin)
{
    HI_U32 u32Cnt = 0;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ZorderBak[WINDOW_MAX_NUMBER] = {0};
    HI_SIZE_T irqflag = 0;

    if (pstWin->u32Zorder == 0)
    {
        return HI_SUCCESS;
    }

    WinZorderSave(u32ZorderBak, pstWin->enDisp);
    for (u32Cnt = 0; u32Cnt < WINDOW_MAX_NUMBER; u32Cnt++)
    {
        if ((stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt])
            && (stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder == (pstWin->u32Zorder - 1)))
        {
            pstWin->u32Zorder --;
            stDispWindow.pstWinArray[pstWin->enDisp][u32Cnt]->u32Zorder ++;
            break;
        }
    }

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    ret = WindowRedistributeProcess(pstWin);
    if (ret)
    {
        WinZorderRestore(u32ZorderBak, pstWin->enDisp);
    }

    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_FALSE);


    return ret;
}

/*check whether the layout is valid.*/
HI_VOID WinSetLocationInfor(WINDOW_S **pstWin,
                            WindowInfor_S *pstWinInfo,
                            HI_U32 numofWindow)
{
    HI_U32 i = 0;
    HI_RECT_S stCanvas = {0}, stTmpRect = {0};
    HI_DISP_DISPLAY_INFO_S stDispInfo = {0};

    memset(&stCanvas, 0x0, sizeof(HI_RECT_S));
    memset(&stTmpRect, 0x0, sizeof(HI_RECT_S));
    memset(&stDispInfo, 0x0, sizeof(HI_DISP_DISPLAY_INFO_S));

    for (i = 0; i < numofWindow; i++)
    {
        stCanvas = pstWin[i]->stDispInfo.stWinCurrentFmt;

        (HI_VOID)DISP_GetDisplayInfo(pstWin[i]->enDisp, &stDispInfo);
        WinOutRectSizeConversionByType(&stDispInfo, &stTmpRect, pstWin[i]);

        /*if the window 's outrect is zero, just set it to vscreen size.*/
        if (!stTmpRect.s32Width || !stTmpRect.s32Height)
        {
            stTmpRect.s32Width  =  stCanvas.s32Width;
            stTmpRect.s32Height =  stCanvas.s32Height;
        }

        pstWinInfo[i].x_start = stTmpRect.s32X;

        /*if window is outof screen, just pull it in.*/
        if (pstWinInfo[i].x_start >  stCanvas.s32Width)
        {
            pstWinInfo[i].x_start = stCanvas.s32Width;
        }

        /*compare x_end.*/
        pstWinInfo[i].x_end = stTmpRect.s32X +  stTmpRect.s32Width;
        if (pstWinInfo[i].x_end > stCanvas.s32Width)
        {
            pstWinInfo[i].x_end = stCanvas.s32Width;
        }

        /*compare y_start*/
        pstWinInfo[i].y_start = stTmpRect.s32Y;
        if (pstWinInfo[i].y_start >  stCanvas.s32Height)
        {
            pstWinInfo[i].y_start = stCanvas.s32Height;
        }

        /*compare y_end.*/
        pstWinInfo[i].y_end = stTmpRect.s32Y  +  stTmpRect.s32Height;
        if (pstWinInfo[i].y_end > stCanvas.s32Height)
        {
            pstWinInfo[i].y_end = stCanvas.s32Height;
        }

        /*set the window zorder.*/
        pstWinInfo[i].zorder = pstWin[i]->u32Zorder;
    }

    return ;
}

HI_VOID Win_GetAllEnabledWindows(WINDOW_S **ppstWin, HI_U32 *WinNum, WINDOW_S *tmpWindow)
{
    HI_U32 k = 0, i = 0;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stDispWindow.pstWinArray[tmpWindow->enDisp][i])
        {
            if ((stDispWindow.pstWinArray[tmpWindow->enDisp][i]->u32Index
                 != tmpWindow->u32Index)
                && (stDispWindow.pstWinArray[tmpWindow->enDisp][i]->bEnable == HI_TRUE))
            {
                ppstWin[k] = stDispWindow.pstWinArray[tmpWindow->enDisp][i];
                k++;
            }
        }
    }

    *WinNum = k;
    return ;
}

HI_VOID Win_InsertNodeIntoEnabledWindows(WINDOW_S **ppstWin, HI_U32 *WinNum, WINDOW_S *tmpWindow)
{
    HI_U32 i = 0;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stDispWindow.pstWinArray[tmpWindow->enDisp][i])
        {
            /*select enabled window which does not equal to tmpWindow
                         and insert them to the window ptr array.*/
            if ((stDispWindow.pstWinArray[tmpWindow->enDisp][i]->u32Index
                 == tmpWindow->u32Index)
                && (tmpWindow->bEnable == HI_TRUE))
            {
                ppstWin[*WinNum] = tmpWindow;
                *WinNum = *WinNum + 1;
            }
        }
    }

    return ;
}

/*update the new layer and region number to window.*/
HI_S32 WinUpdateMappingInfor(WINDOW_S *pstWin, WindowMappingResult_S *pstWinMapResult, HI_DRV_DISPLAY_E enDisp)
{
    HI_U32 i = 0;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if ((stDispWindow.pstWinArray[pstWin->enDisp][i])
            && (stDispWindow.pstWinArray[pstWin->enDisp][i]->u32Index
                == pstWin->u32Index))
        {
            if (enDisp == HI_DRV_DISPLAY_1)
            {
                stDispWindow.pstWinArray[pstWin->enDisp][i]->u32VideoLayerNew = pstWinMapResult->videoLayer;
            }
            else if (enDisp == HI_DRV_DISPLAY_0)
            {
                /*the sd channel is v3/v4*/
                stDispWindow.pstWinArray[pstWin->enDisp][i]->u32VideoLayerNew = pstWinMapResult->videoLayer + 3;
            }

            stDispWindow.pstWinArray[pstWin->enDisp][i]->u32VideoRegionNoNew = pstWinMapResult->regionNo;

        }
    }

    if (enDisp == HI_DRV_DISPLAY_1)
    {
        pstWin->u32VideoLayerNew = pstWinMapResult->videoLayer;
    }
    else if (enDisp == HI_DRV_DISPLAY_0)
        /*the sd channel is v3/v4*/
    {
        pstWin->u32VideoLayerNew = pstWinMapResult->videoLayer + 3;
    }

    pstWin->u32VideoRegionNoNew = pstWinMapResult->regionNo;
    return HI_SUCCESS;
}

static HI_VOID UpdateWinZorderAjustInfor(HI_DRV_DISPLAY_E eDisp,
        HI_DRV_DISP_ZORDER_E eZorderOpt)
{
    HI_U32 i = 0;
    WINDOW_S *pstWinTmp = HI_NULL;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        pstWinTmp  = stDispWindow.pstWinArray[eDisp][i];

        if (HI_NULL == pstWinTmp)
        {
            continue;
        }

        pstWinTmp->stWinLayerOpt.layerOptType = LAYER_OPT_BUTT;
        pstWinTmp->stWinLayerOpt.bEffective = HI_FALSE;
        pstWinTmp->stWinLayerOpt.enLayerOpt = HI_DRV_DISP_ZORDER_BUTT;

        if ((pstWinTmp->u32VideoLayerNew == VDP_RM_LAYER_VID3)
            || (pstWinTmp->u32VideoLayerNew == VDP_RM_LAYER_VID0))
        {
            pstWinTmp->stWinLayerOpt.layerOptType = LAYER_OPT_ZORDER_ADJUST;

            if (HI_DRV_DISP_ZORDER_BUTT == eZorderOpt)
            {
                pstWinTmp->stWinLayerOpt.bEffective = HI_FALSE;
            }
            else
            {
                pstWinTmp->stWinLayerOpt.bEffective = HI_TRUE;
            }

            pstWinTmp->stWinLayerOpt.enLayerOpt = eZorderOpt;
        }

    }

    return;
}

/*window adjust, move/zme/create/destroy may cause the layout
 *change. because the  adjust in thread-suituation may be half complete,
 *and then interruptted by isr, so the change should be located in    isr func.
*/
HI_S32 WindowRedistributeProcess(WINDOW_S *tmpWindow)
{
    WINDOW_S *pstWin[WINDOW_MAX_NUMBER] = {HI_NULL};
    WindowInfor_S         *pstInputWinCoordinateInfor = HI_NULL;
    WindowMappingResult_S *pstWinMappingResult = HI_NULL;
    WindowZorderInfor_S   *pstInputWinZorderInfor = HI_NULL;
    HI_U32   numofWindow = 0, i = 0, u32OverlapWinIndex = 0;
    HI_U32   u32V0V3LayerIndex = 0;
    HI_S32                ret = HI_SUCCESS;
    HI_DRV_DISPLAY_E      enDisp  = HI_DRV_DISPLAY_BUTT;
    WinMap2LayerInfor_S   *pstWin2LayerInfor = HI_NULL;

    /*first,get all the enabled window ptrs.*/
    Win_GetAllEnabledWindows(pstWin, &numofWindow, tmpWindow);
    Win_InsertNodeIntoEnabledWindows(pstWin, &numofWindow, tmpWindow);

    if (0 == numofWindow)
    {
        DISP_WARN("No enabled window exist.\n");
        return HI_SUCCESS;
    }

    if (WINDOW_MAX_NUMBER < numofWindow)
    {
        DISP_WARN("Enabled window num is not correct.\n");
        return HI_FAILURE;
    }

    pstWin2LayerInfor = HI_KMALLOC(HI_ID_VO, sizeof(WinMap2LayerInfor_S), GFP_ATOMIC);
    if (HI_NULL == pstWin2LayerInfor)
    {
        WIN_ERROR("kmalloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    memset(pstWin2LayerInfor, 0, sizeof(WinMap2LayerInfor_S));
    pstInputWinCoordinateInfor = pstWin2LayerInfor->stInputWinCoordinateInfor;
    pstInputWinZorderInfor     = pstWin2LayerInfor->stInputWinZorderInfor;
    pstWinMappingResult        = pstWin2LayerInfor->stWinMappingResult;

    /*Second,  set the coordinate and locations value from windows.*/
    WinSetLocationInfor(pstWin, pstInputWinCoordinateInfor, numofWindow);

    /*third:  generate win-layer remapping.*/
    ret =  WindowAndLayerMapping(pstInputWinCoordinateInfor, pstWinMappingResult, numofWindow);
    if (ret)
    {
        WIN_ERROR("UI disobey the windows strict, the coordinate is as follows:!\n");
        for (i = 0; i < numofWindow; i++)
        {
            WIN_ERROR("win x:%d, y:%d, x_end:%d, y_end:%d, zorder %d !\n",
                      pstInputWinCoordinateInfor[i].x_start,
                      pstInputWinCoordinateInfor[i].y_start,
                      pstInputWinCoordinateInfor[i].x_end,
                      pstInputWinCoordinateInfor[i].y_end,
                      pstInputWinCoordinateInfor[i].zorder);
        }

        ret =  HI_ERR_VO_OPERATION_DENIED;
        goto __WINMAPPING2LAYER;
    }

    /*update new window-layer mapping.*/
    enDisp = tmpWindow->enDisp;
    for (i = 0 ; i < numofWindow; i++)
    {
        WinUpdateMappingInfor(pstWin[i], &pstWinMappingResult[i], enDisp);
    }

    for (i = 0; i < numofWindow; i++)
    {
        if (pstWinMappingResult[i].u32OverlapCnt)
        {
            pstInputWinZorderInfor[u32OverlapWinIndex].layerNumber = pstWin[i]->u32VideoLayerNew;
            pstInputWinZorderInfor[u32OverlapWinIndex].winZorder =    pstWin[i]->u32Zorder;

            if ((VDP_RM_LAYER_VID0 == pstInputWinZorderInfor[u32OverlapWinIndex].layerNumber)
                || (VDP_RM_LAYER_VID3 == pstInputWinZorderInfor[u32OverlapWinIndex].layerNumber))
            {
                u32V0V3LayerIndex = u32OverlapWinIndex;
            }

            (HI_VOID)pstWin[i]->stVLayerFunc.PF_GetZorder(pstWin[i]->u32VideoLayerNew,
                    &pstInputWinZorderInfor[u32OverlapWinIndex].layerZorder);

            u32OverlapWinIndex ++;
        }
    }

    /*check wether the window's order matches the layer's order.*/
    ret = layerZorderMatch(pstInputWinZorderInfor, u32OverlapWinIndex);
    if (ret)
    {
        WIN_ERROR("Win zorder not right, can't allocate layers.!\n");
        for (i = 0; i < u32OverlapWinIndex; i++)
        {
            WIN_ERROR("win zorder:%d, layerorder:%d, allocated layer:%d !\n",
                      pstInputWinZorderInfor[i].winZorder,
                      pstInputWinZorderInfor[i].layerZorder,
                      pstInputWinZorderInfor[i].layerNumber);
        }

        ret = HI_ERR_VO_OPERATION_DENIED;
        goto __WINMAPPING2LAYER;
    }

    /*update window zorder adjustinfor  for following whole window updating.*/
    (HI_VOID)UpdateWinZorderAjustInfor(tmpWindow->enDisp,
                                       pstInputWinZorderInfor[u32V0V3LayerIndex].matchOperation);

__WINMAPPING2LAYER:

    HI_KFREE(HI_ID_VO, pstWin2LayerInfor);
    pstWin2LayerInfor = HI_NULL;

    return ret;
}

HI_S32 WindowRedistributeProcess_Wait(WINDOW_S *tmpWindow, HI_BOOL bWait)
{
    //unsigned int t = 0;
    HI_S32 s32Ret = HI_FAILURE;
    atomic_set(&stDispWindow.bWindowSytemUpdate[tmpWindow->enDisp], 1);

    if (HI_TRUE == bWait)
    {
        s32Ret = DISP_OSAL_WaitEvent(&stDispWindow.stWinSytemQueueEvent, EVENT_WIN_SYSTEM_UP_COMPLET, 50);
        DISP_OSAL_ResetEvent(&stDispWindow.stWinSytemQueueEvent, EVENT_WIN_NOTHING);

        if (HI_SUCCESS != s32Ret)
        {
            WIN_WARN("wait for redistribtue end time out!\n");
            return HI_ERR_VO_TIMEOUT;
        }
    }

    return HI_SUCCESS;
}

HI_VOID ISR_WinReleaseUSLFrame(WINDOW_S *pstWin);

HI_S32 WinCreateDisplayWindow(HI_DRV_WIN_ATTR_S *pWinAttr, WINDOW_S **ppstWin, HI_U32 u32BufNum)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 nRet = HI_FAILURE;
    HIDRV_DISP_NODE_DELAYTIME   *pstDispNodeDelayTime   = HI_NULL;

    if (WinTestAddWindow(pWinAttr->enDisp))
    {
        WIN_ERROR("Reach max window number,can not create!\n");
        return HI_ERR_VO_CREATE_ERR;
    }

    pstWin = (WINDOW_S *)DISP_MALLOC(sizeof(WINDOW_S));
    if (!pstWin)
    {
        WIN_ERROR("Malloc WINDOW_S failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    DISP_MEMSET(pstWin, 0, sizeof(WINDOW_S));

    /* attribute */
    pstWin->bEnable = HI_FALSE;
    pstWin->bEnable_Using = HI_FALSE;
    pstWin->bMasked = HI_FALSE;

    pstWin->enState = WIN_STATE_WORK;
    pstWin->bUpState      = HI_FALSE;

    DISP_OSAL_InitEvent(&pstWin->stWinQueueEvent, EVENT_WIN_NOTHING);
    WIN_QUEUE_Init(&( pstWin->ListHead));
    DISP_OSAL_InitSpin(&(pstWin->Spin));

    pstWin->enDisp = pWinAttr->enDisp;
    pstWin->enType = HI_DRV_WIN_ACTIVE_SINGLE;

    /* pay attention: when virtualscreen,it is the use's settting.
      *if non-virt mode ,it is physical cooridinate.
      */
    pstWin->stCfg.stAttrBuf = *pWinAttr;
    pstWin->stCfg.stAttr    = *pWinAttr;
    pstWin->stCfg.u32Alpha = WINDOW_MAX_ALPHA;

    atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);

    pstWin->stCfg.enFrameCS = HI_DRV_CS_UNKNOWN;
    pstWin->stCfg.u32Fidelity = 0;
    pstWin->stCfg.enOutCS    = HI_DRV_CS_UNKNOWN;

    /* initial first frame output status. */
    pstWin->stCfg.stFirstFrmStatus.bSenceChange = HI_FALSE;
    pstWin->stCfg.stFirstFrmStatus.enDispOutType = HI_DRV_DISP_TYPE_NORMAL;
    pstWin->stCfg.stFirstFrmStatus.enOutColorSpace = HI_DRV_CS_UNKNOWN;

    pstWin->stCfg.stSource.hSrc = HI_INVALID_HANDLE;
    pstWin->stCfg.stSource.hSecondSrc = HI_INVALID_HANDLE;
    pstWin->stCfg.stSource.pfAcqFrame = HI_NULL;
    pstWin->stCfg.stSource.pfRlsFrame = HI_NULL;
    pstWin->stCfg.stSource.pfSendWinInfo = HI_NULL;
    nRet = VideoLayer_GetFunction(&pstWin->stVLayerFunc);
    if (nRet)
    {
        WIN_ERROR("VideoLayer_GetFunction failed!\n");
        goto __ERR_GET_FUNC__;
    }

    pstWin->u32VideoLayer = VDP_LAYER_VID_BUTT;
    pstWin->u32VideoLayerNew = VDP_LAYER_VID_BUTT;

    pstWin->u32VideoRegionNo    = 0xffffffff;
    pstWin->u32VideoRegionNoNew = 0xffffffff;

    pstWin->u32LastInLowDelayIdx = 0xffffffff;
    pstWin->u32LastOutLowDelayIdx = 0xffffffff;

    /*Pay attention please: here  the  func of zorder adjust should be modified.
        * do not forget it.
        */
    WinZorderMoveTop(pstWin);

    nRet = WinBuf_Create(u32BufNum, WIN_BUF_MEM_SRC_SUPPLY, HI_NULL, &pstWin->stBuffer.stWinBP);
    if (nRet)
    {
        WIN_ERROR("Create buffer pool failed\n");
        goto __ERR_GET_FUNC__;
    }

    spin_lock_init(&(pstWin->stBuffer.stUselessBuf.stUlsLock));

    DRV_WIN_FRC_Create(&pstWin->hFrc);

    // initial reset
    pstWin->bReset = HI_FALSE;
    pstWin->bConfigedBlackFrame = HI_FALSE;

    // initial quickmode
    pstWin->bQuickMode = HI_FALSE;

    // initial stepmode flag
    pstWin->bStepMode = HI_FALSE;

    //init delay info
    pstWin->stDelayInfo.u32DispRate = 5000;
    pstWin->stDelayInfo.bTBMatch = HI_TRUE;
    pstWin->stDelayInfo.u32DisplayTime = 20;
    pstWin->bInInterrupt = HI_FALSE;

    //init rotation
    pstWin->enRotation = HI_DRV_ROT_ANGLE_0;
    //init flip
    pstWin->bVertFlip = HI_FALSE;
    pstWin->bHoriFlip = HI_FALSE;

    //init Node time from add full list to del full list
    pstDispNodeDelayTime = &(pstWin->stBuffer.stWinBP.stBuffer.stDispNodeDelayTime);

    memset(pstDispNodeDelayTime, 0, sizeof(HIDRV_DISP_NODE_DELAYTIME));

    pstDispNodeDelayTime->u16UnRecordNodeNum = UNRECORD_FRAME_NUM;

    *ppstWin = pstWin;

    return HI_SUCCESS;


__ERR_GET_FUNC__:

    DISP_FREE(pstWin);

    return nRet;
}

HI_S32 WinDestroyDisplayWindow(WINDOW_S *pstWin)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;
    WIN_CHECK_NULL_RETURN(pstWin);

    (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
    ISR_WinReleaseUSLFrame(pstWin);

    // flush frame in full buffer pool
    pstFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);
    if (HI_NULL != pstFrame)
    {
        WinBuf_FlushWaitingFrame(&pstWin->stBuffer.stWinBP, pstFrame);
        WinBuf_ForceReleaseFrame(&pstWin->stBuffer.stWinBP, pstFrame);
    }

    WinBuf_CheckMemRefCntReset(pstWin->u32Index, &pstWin->stBuffer.stWinBP);

    // s1 derstoy buffer
    (HI_VOID)WinBuf_Destroy(&pstWin->stBuffer.stWinBP);

    /*when delete the win, adjust the zorder.*/
    (HI_VOID)WinZorderDelete(pstWin);

    (HI_VOID)DRV_WIN_FRC_Destroy(pstWin->hFrc);

    DISP_FREE(pstWin);
    pstWin = HI_NULL;

    return HI_SUCCESS;
}

HI_S32 WinRegCallback(WINDOW_S *pstWin)
{
    HI_DRV_DISP_CALLBACK_S stCB = {0};
    HI_S32 nRet = HI_SUCCESS;

    if (WinGetDispID(pstWin) >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_ERROR("WIN register callback failed!\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    /*only hd register win process.*/
    if (WinGetDispID(pstWin) == HI_DRV_DISPLAY_1)
    {
        stCB.hDst  = (HI_VOID *)pstWin;
        stCB.pfDISP_Callback = ISR_CallbackForWinProcess;
        stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_MIDDLE;

        nRet = DISP_RegCallback(WinGetDispID(pstWin), HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);
        if (nRet)
        {
            WIN_ERROR("WIN register callback failed.\n");
            return nRet;
        }
    }
    else
    {
        if (!WinCheckWhetherWbcIsogenyMode())
        {
            stCB.hDst  = (HI_VOID *)pstWin;
            stCB.pfDISP_Callback = ISR_CallbackForWinProcess;
            stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_MIDDLE;

            nRet = DISP_RegCallback(WinGetDispID(pstWin), HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);
            if (nRet)
            {
                WIN_ERROR("WIN register callback failed.\n");
                return nRet;
            }
        }

    }

    return HI_SUCCESS;
}

HI_S32 WinUnRegCallback(WINDOW_S *pstWin)
{
    HI_DRV_DISP_CALLBACK_S stCB = {0};
    HI_S32 nRet = HI_SUCCESS;

    if (WinGetDispID(pstWin) >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_ERROR("WIN register callback failed!\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (WinGetDispID(pstWin) == HI_DRV_DISPLAY_1)
    {
        stCB.hDst  = (HI_VOID *)pstWin;
        stCB.pfDISP_Callback = ISR_CallbackForWinProcess;
        stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_MIDDLE;
        nRet = DISP_UnRegCallback(WinGetDispID(pstWin), HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);

        if ( nRet != HI_SUCCESS)
        {
            WIN_ERROR("WIN unregister callback failed!\n");
            return nRet;
        }
    }
    else
    {
        if (!WinCheckWhetherWbcIsogenyMode())
        {
            stCB.hDst  = (HI_VOID *)pstWin;
            stCB.eCallBackPrior  =  HI_DRV_DISP_CALLBACK_PRIORTY_MIDDLE;
            stCB.pfDISP_Callback = ISR_CallbackForWinProcess;
            nRet = DISP_UnRegCallback(WinGetDispID(pstWin), HI_DRV_DISP_C_INTPOS_0_PERCENT, &stCB);
            if (nRet)
            {
                WIN_ERROR("WIN unregister callback failed.\n");
                return nRet;
            }
        }
    }

    return HI_SUCCESS;
}


HI_VOID WinSetBlackFrameFlag(WINDOW_S *pstWin)
{
    if (pstWin)
    {
        pstWin->bConfigedBlackFrame = HI_TRUE;
    }
}

HI_VOID WinClearBlackFrameFlag(WINDOW_S *pstWin)
{
    if (pstWin)
    {
        pstWin->bConfigedBlackFrame = HI_FALSE;
    }
}

HI_BOOL WinTestBlackFrameFlag(WINDOW_S *pstWin)
{
    if (pstWin)
    {
        return pstWin->bConfigedBlackFrame;
    }

    return HI_FALSE;
}

HI_S32 WinCheckFixedAttr(HI_DRV_WIN_ATTR_S *pOldAttr, HI_DRV_WIN_ATTR_S *pNewAttr)
{
    if ((pNewAttr->enDisp >=  HI_DRV_DISPLAY_BUTT)
        || (pNewAttr->enARCvrs >=  HI_DRV_ASP_RAT_MODE_BUTT)
        || (pNewAttr->enDataFormat >=  HI_DRV_PIX_BUTT))
    {
        WIN_ERROR("Input param is invalid!\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ( (pOldAttr->enDisp != pNewAttr->enDisp)
         || (pOldAttr->bVirtual != pNewAttr->bVirtual)
       )
    {
        WIN_ERROR("the fixed attr is not right.!\n");
        return HI_ERR_VO_OPERATION_DENIED;
    }

    if (pOldAttr->bVirtual)
    {
        if ((pOldAttr->bUserAllocBuffer != pNewAttr->bUserAllocBuffer)
            || (pOldAttr->u32BufNumber != pNewAttr->u32BufNumber)
           )
        {
            WIN_ERROR("the fixed attr of virtual window error!\n");
            return HI_ERR_VO_OPERATION_DENIED;
        }
    }

    return HI_SUCCESS;
}


HI_BOOL WinCheckAttrChange(HI_DRV_WIN_ATTR_S *pstOriAttr, HI_DRV_WIN_ATTR_S *pstNewAttr)
{
    if (0 == memcmp(pstOriAttr, pstNewAttr, sizeof(HI_DRV_WIN_ATTR_S)))
    {
        /*no change*/
        return HI_FALSE;
    }
    else
    {
        return HI_TRUE;
    }
}

HI_S32 WinCheckAttr(HI_DRV_WIN_ATTR_S *pstAttr, HI_BOOL bVirtScreen)
{
    HI_RECT_S drv_resolution;
    HI_S32 ret = 0;
    HI_DISP_DISPLAY_INFO_S  stInfo;

    if ((pstAttr->enDisp > HI_DRV_DISPLAY_1)
        || (pstAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
        || (pstAttr->enDataFormat >= HI_DRV_PIX_BUTT))
    {
        WIN_FATAL("Invalid enum.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    memset((void *)&drv_resolution, 0, sizeof(drv_resolution));
    memset((void *)&stInfo, 0, sizeof(stInfo));

    if (bVirtScreen)
    {
        ret = DISP_GetVirtScreen(pstAttr->enDisp, &drv_resolution);
    }
    else
    {
        ret = DISP_GetDisplayInfo(pstAttr->enDisp, &stInfo);
        drv_resolution = stInfo.stFmtResolution;
    }

    if (HI_SUCCESS != ret)
    {
        HI_ERR_WIN("Get Virtual SCREEN error!\n");
        return ret;
    }

    if ( ((pstAttr->stOutRect.s32Height == 0)
          && (pstAttr->stOutRect.s32Width != 0))
         || ((pstAttr->stOutRect.s32Height != 0)
             && (pstAttr->stOutRect.s32Width == 0)))
    {
        HI_ERR_WIN("win outrect error, one of w/h is zero.!\n");
        return HI_ERR_VO_INVALID_PARA;
    }
    else if ((!(pstAttr->stOutRect.s32Height | pstAttr->stOutRect.s32Width))
             && (pstAttr->stOutRect.s32X | pstAttr->stOutRect.s32Y))
    {
        HI_ERR_WIN("when w/h is zero, x/y should be zero too.!\n");
        return HI_ERR_VO_INVALID_PARA;
    }
    else if ((pstAttr->stOutRect.s32Height | pstAttr->stOutRect.s32Width)
             && ((pstAttr->stOutRect.s32Width   < WIN_OUTRECT_MIN_WIDTH)
                 || (pstAttr->stOutRect.s32Height  < WIN_OUTRECT_MIN_HEIGHT))
            )
    {
        WIN_FATAL("The Min WIN OutRect supported is 64*64 !\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (   ( pstAttr->stCustmAR.u32ARw > (pstAttr->stCustmAR.u32ARh * WIN_MAX_ASPECT_RATIO) )
           || ( (pstAttr->stCustmAR.u32ARw * WIN_MAX_ASPECT_RATIO) < pstAttr->stCustmAR.u32ARh)
       )
    {
        HI_ERR_WIN("bUserDefAspectRatio  error!\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if ( pstAttr->bUseCropRect)
    {
        if (    (pstAttr->stCropRect.u32TopOffset    > WIN_CROPRECT_MAX_OFFSET_TOP)
                || (pstAttr->stCropRect.u32LeftOffset    > WIN_CROPRECT_MAX_OFFSET_LEFT)
                || (pstAttr->stCropRect.u32BottomOffset > WIN_CROPRECT_MAX_OFFSET_BOTTOM)
                || (pstAttr->stCropRect.u32RightOffset    > WIN_CROPRECT_MAX_OFFSET_RIGHT)
           )
        {
            WIN_FATAL("WIN CropRec support less than 128!\n");
            return HI_ERR_VO_INVALID_PARA;
        }
    }
    else
    {
        if ( !pstAttr->stInRect.s32Height || !pstAttr->stInRect.s32Width)
        {
            DISP_MEMSET(&pstAttr->stInRect, 0, sizeof(HI_RECT_S));
        }
        else if (   (pstAttr->stInRect.s32Width     < WIN_FRAME_MIN_WIDTH)
                    || (pstAttr->stInRect.s32Height  < WIN_FRAME_MIN_HEIGHT)
                    || (pstAttr->stInRect.s32Width     > WIN_FRAME_MAX_WIDTH)
                    || (pstAttr->stInRect.s32Height  > WIN_FRAME_MAX_HEIGHT)
                )
        {
            WIN_FATAL("WIN InRect support 64*64 ~ 2560*1600!\n");
            return HI_ERR_VO_INVALID_PARA;
        }
        else if ( (pstAttr->stInRect.s32X  < 0) || (pstAttr->stInRect.s32Y  < 0))
        {
            WIN_FATAL("WIN InRect  invalid para!\n");
            return HI_ERR_VO_INVALID_PARA;
        }
    }

    return HI_SUCCESS;
}

HI_VOID WinReviseOutRectByCapability(const HI_RECT_S *pstLayerCapabilitySize,
                                     HI_RECT_S *pstWinOutRect)
{
    if (pstWinOutRect->s32Width > pstLayerCapabilitySize->s32Width)
    {
        pstWinOutRect->s32Width = pstLayerCapabilitySize->s32Width;
    }

    if (pstWinOutRect->s32Height > pstLayerCapabilitySize->s32Height)
    {
        pstWinOutRect->s32Height = pstLayerCapabilitySize->s32Height;
    }

    return ;
}

static HI_S32 WinCalDobySourceInfo(WINDOW_S *pstWin, HI_U32 u32VideoLayer, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_DRV_WIN_PRIV_INFO_S *pstInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_DRV_WIN_ATTR_S          *pstAttr = HI_NULL;

    memset(&stVideoLayerCap, 0x0, sizeof(stVideoLayerCap));
    pstAttr = &pstWin->stUsingAttr;

    pstInfo->ePixFmt        = HI_DRV_PIX_FMT_NV21;
    pstInfo->bUseCropRect   = HI_FALSE;

    pstInfo->stInRect.s32Width = 0;
    pstInfo->stInRect.s32Height = 0;
    pstInfo->stInRect.s32X = 0;
    pstInfo->stInRect.s32Y = 0;

    pstInfo->stCropRect.u32LeftOffset = 0;
    pstInfo->stCropRect.u32TopOffset = 0;
    pstInfo->stCropRect.u32RightOffset = 0;
    pstInfo->stCropRect.u32BottomOffset = 0;


    if (!pstAttr->stOutRect.s32Width || !pstAttr->stOutRect.s32Height)
    {
        pstInfo->stOutRect = pstDispInfo->stFmtResolution;
    }
    else
    {
        pstInfo->stOutRect = pstAttr->stOutRect;
    }

    pstInfo->stScreenAR   = pstDispInfo->stAR;
    pstInfo->stCustmAR    = pstAttr->stCustmAR;
    pstInfo->enARCvrs     = HI_DRV_ASP_RAT_MODE_FULL;
    pstInfo->bUseExtBuf   = pstAttr->bUserAllocBuffer;
    pstInfo->u32MaxRate   = (pstDispInfo->u32RefreshRate > WIN_TRANSFER_CODE_MAX_FRAME_RATE) ?
                            (pstDispInfo->u32RefreshRate / 2 ) : pstDispInfo->u32RefreshRate;

    pstInfo->bInterlaced = HI_TRUE;
    pstInfo->enRotation  = HI_DRV_ROT_ANGLE_0;
    pstInfo->bHoriFlip   = HI_FALSE;
    pstInfo->bVertFlip   = HI_FALSE;

    pstInfo->stScreen = pstDispInfo->stFmtResolution;
    pstInfo->bIn3DMode = HI_FALSE;
    /*displaying window does not support tunnel mode.*/
    pstInfo->bTunnelSupport = HI_TRUE;


    if (!pstWin->stVLayerFunc.PF_GetCapability)
    {
        WIN_FATAL("PF_GetCapability is null\n");
        return HI_SUCCESS;//here should return failure NOT success!
    }

    if ((s32Ret = pstWin->stVLayerFunc.PF_GetCapability(u32VideoLayer, &stVideoLayerCap)))
    {
        return s32Ret;
    }

    /*in most condition, v1 will be set to mutilarea mode except in dolby mode,
      *under which v1 will be set single mode.  v1 only support 8 bit in multiarea
      * mode and 10 bit in singlearea mode.
      *  so when the layer support 10bit or the window in dolby mode , we acquire 10 bit from vpss.
      *  VPSS will give a result according the stream source.
      */
    if ((stVideoLayerCap.u32BitWidth == 10)
        || (pstWin->enWinMode == HI_DRV_WINDOW_MODE_DOLBY))
    {
        pstInfo->enBitWidth = HI_DRV_PIXEL_BITWIDTH_10BIT;
    }
    else
    {
        pstInfo->enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    }


    /*as a result of winlayermapping, we switch vpss  compress on or off according
        the layer capability.*/
    if (stVideoLayerCap.bDcmp == HI_TRUE)
    {
        pstInfo->ePixFmt = HI_DRV_PIX_FMT_NV21_CMP;
    }
    else
    {
        pstInfo->ePixFmt = HI_DRV_PIX_FMT_NV21;
    }

    /*if the layer has zme,it can bypass vpss*/
    if (stVideoLayerCap.bZme == HI_TRUE)
    {
        pstInfo->bPassThrough = HI_TRUE;
        memset( &pstInfo->stOutRect, 0, sizeof(HI_RECT_S));
    }
    else
    {
        WinReviseOutRectByCapability(&stVideoLayerCap.stVideoReadSize, &pstInfo->stOutRect);
        pstInfo->bPassThrough = HI_FALSE;
    }

    DISP_PRINT(">>>>>>>>>>>>>>>>>>>>>>>>>>>will send info to source .............\n");

    //pro info below need to modify when it comes to Dolby frame. currently just mantain it.
    pstWin->stWinInfoForDeveloper.u32WinNum = stDispWindow.u32WinNumber[pstWin->enDisp];
    pstWin->stWinInfoForDeveloper.bIn3DMode = pstInfo->bIn3DMode;

    pstWin->stWinInfoForDeveloper.bHorSrOpenInPreProcess = HI_FALSE;
    pstWin->stWinInfoForDeveloper.bVerSrOpenInPreProcess = HI_FALSE;

    pstWin->stWinInfoForDeveloper.stVdpRequire = pstInfo->stOutRect;
    pstWin->stWinInfoForDeveloper.eCurrentFmt = pstDispInfo->stFmtResolution;
    pstWin->stWinInfoForDeveloper.stFinalWinOutputSize = pstInfo->stOutRect;


    return s32Ret;

}


static HI_S32 WinCalcuInfo(WINDOW_S *pstWin, HI_U32 u32VideoLayer, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_DRV_WIN_PRIV_INFO_S *pstInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap = {0};
    HI_BOOL bHorSrEnable = HI_FALSE;
    HI_BOOL bVerSrEnable = HI_FALSE;
    HI_DRV_WIN_ATTR_S          *pstAttr = HI_NULL;

    pstAttr = &pstWin->stUsingAttr;

    pstInfo->ePixFmt        = HI_DRV_PIX_FMT_NV21;
    pstInfo->stScreenAR   = pstDispInfo->stAR;
    pstInfo->stCustmAR    = pstAttr->stCustmAR;
    pstInfo->enARCvrs     = pstAttr->enARCvrs;
    pstInfo->bUseExtBuf   = pstAttr->bUserAllocBuffer;
    pstInfo->u32MaxRate   = (pstDispInfo->u32RefreshRate > WIN_TRANSFER_CODE_MAX_FRAME_RATE) ?
                            (pstDispInfo->u32RefreshRate / 2 ) : pstDispInfo->u32RefreshRate;

    pstInfo->bInterlaced = pstDispInfo->bInterlace;
    pstInfo->enRotation  = pstWin->enRotation;
    pstInfo->bHoriFlip   = pstWin->bHoriFlip;
    pstInfo->bVertFlip   = pstWin->bVertFlip;

    if ((pstDispInfo->eDispMode != DISP_STEREO_NONE)
        && (pstDispInfo->eDispMode < DISP_STEREO_BUTT))
    {
        pstInfo->bIn3DMode = HI_TRUE;
    }
    else
    {
        pstInfo->bIn3DMode = HI_FALSE;
    }

    /*displaying window does not support tunnel mode.*/
    pstInfo->bTunnelSupport = HI_TRUE;

    pstInfo->stScreen = pstDispInfo->stFmtResolution;

    pstWin->stWinInfoForDeveloper.stFinalWinOutputSize = pstInfo->stOutRect;

    if (!pstWin->stVLayerFunc.PF_GetCapability)
    {
        WIN_FATAL("PF_GetCapability is null\n");
        return HI_SUCCESS;//here should return failure NOT success!
    }

    if ((s32Ret = pstWin->stVLayerFunc.PF_GetCapability(u32VideoLayer, &stVideoLayerCap)))
    {
        return s32Ret;
    }

    pstInfo->bUseCropRect   = pstAttr->bUseCropRect;
    pstInfo->stInRect        = pstAttr->stInRect;
    pstInfo->stCropRect  = pstAttr->stCropRect;

    if (!pstAttr->stOutRect.s32Width || !pstAttr->stOutRect.s32Height)
    {
        pstInfo->stOutRect = pstDispInfo->stFmtResolution;
    }
    else
    {
        pstInfo->stOutRect = pstAttr->stOutRect;
    }

    /*in most condition, v1 will be set to mutilarea mode except in dolby mode,
      *under which v1 will be set single mode.  v1 only support 8 bit in multiarea
      * mode and 10 bit in singlearea mode.
      *  so when the layer support 10bit or the window in dolby mode , we acquire 10 bit from vpss.
      *  VPSS will give a result according the stream source.
      */
    if ((stVideoLayerCap.u32BitWidth == 10)
        || (pstWin->enWinMode == HI_DRV_WINDOW_MODE_DOLBY))
    {
        pstInfo->enBitWidth = HI_DRV_PIXEL_BITWIDTH_10BIT;
    }
    else
    {
        pstInfo->enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    }

    if (pstWin->bMCE && (pstDispInfo->stFmtResolution.s32Width <= FHD_WIDTH_VALUE))
    {
        stVideoLayerCap.bZme = HI_FALSE;
        pstInfo->enBitWidth = HI_DRV_PIXEL_BITWIDTH_8BIT;
    }

    /*  Window  process in VDP */
    if ((stVideoLayerCap.bZmePrior == HI_TRUE)
        && (stVideoLayerCap.bZme == HI_TRUE)
        && (pstInfo->enRotation == HI_DRV_ROT_ANGLE_0)
        && (!pstInfo->bIn3DMode)
#if defined(HI_NVR_SUPPORT)
        && (pstInfo->stOutRect.s32Width > FHD_WIDTH_VALUE )
#endif
       )
    {
        pstInfo->enARCvrs  = HI_DRV_ASP_RAT_MODE_FULL;

        pstInfo->bPassThrough = HI_TRUE;
        memset(&pstInfo->stOutRect, 0, sizeof(pstInfo->stOutRect));

        pstInfo->bUseCropRect = HI_FALSE;
        DISP_MEMSET(&pstInfo->stCropRect, 0, sizeof(pstInfo->stCropRect));
        DISP_MEMSET(&pstInfo->stInRect, 0, sizeof(pstInfo->stInRect));
    }
    else
    {
        pstInfo->enARCvrs  = pstAttr->enARCvrs;
        pstInfo->bPassThrough = HI_FALSE;
        WinReviseOutRectByCapability(&stVideoLayerCap.stVideoReadSize, &pstInfo->stOutRect);
    }

    /*as a result of winlayermapping, we switch vpss  compress on or off according
        the layer capability.*/
    if (stVideoLayerCap.bDcmp == HI_TRUE)
    {
        pstInfo->ePixFmt = HI_DRV_PIX_FMT_NV21_CMP;
    }
    else
    {
        pstInfo->ePixFmt = HI_DRV_PIX_FMT_NV21;
    }

    pstWin->stWinInfoForDeveloper.u32WinNum = stDispWindow.u32WinNumber[pstWin->enDisp];
    pstWin->stWinInfoForDeveloper.bIn3DMode = pstInfo->bIn3DMode;

    pstWin->stWinInfoForDeveloper.bHorSrOpenInPreProcess = bHorSrEnable;
    pstWin->stWinInfoForDeveloper.bVerSrOpenInPreProcess = bVerSrEnable;

    pstWin->stWinInfoForDeveloper.stVdpRequire = pstInfo->stOutRect;
    pstWin->stWinInfoForDeveloper.eCurrentFmt = pstDispInfo->stFmtResolution;

    return s32Ret;

}

HI_S32 WinSendAttrToSource(WINDOW_S *pstWin, HI_DISP_DISPLAY_INFO_S *pstDispInfo)
{
    HI_DRV_WIN_PRIV_INFO_S      stInfo = {0};
    PFN_GET_WIN_INFO_CALLBACK   pfTmpSendWinInfo = HI_NULL;

    DISP_MEMSET(&stInfo, 0, sizeof(stInfo));

    if (HI_NULL == pstWin->stCfg.stSource.pfSendWinInfo)
    {
        return HI_FAILURE;
    }

    pfTmpSendWinInfo = pstWin->stCfg.stSource.pfSendWinInfo;

    /* hSrc valid and hSecondSrc invalid,there's ONLY one VPSS:normal frame or
        * (BL+metadata)Dolby frame will enter this branch.
        */
    if ((pstWin->stCfg.stSource.hSrc != HI_INVALID_HANDLE) &&
        (pstWin->stCfg.stSource.hSecondSrc == HI_INVALID_HANDLE))
    {
        (HI_VOID)WinCalcuInfo(pstWin, pstWin->u32VideoLayer, pstDispInfo, &stInfo);
        (pfTmpSendWinInfo)(pstWin->stCfg.stSource.hSrc, &stInfo);

    }

    /* Both hSrc and hSecondSrc are valid indicate there're two VPSSes:
        * BL+(EL+metadata)Dolby frame will enter this branch.
        */
    else if ((pstWin->stCfg.stSource.hSrc != HI_INVALID_HANDLE) &&
             (pstWin->stCfg.stSource.hSecondSrc != HI_INVALID_HANDLE))
    {
        /*set the first VPSS output attributes.Calculate V0 videoLayer's info.*/
        (HI_VOID)WinCalDobySourceInfo(pstWin, VDP_LAYER_VID0, pstDispInfo, &stInfo);
        (pfTmpSendWinInfo)(pstWin->stCfg.stSource.hSrc, &stInfo);

        /*set the second VPSS output attributes.Calulate V1 videoLayer's info.*/
        DISP_MEMSET(&stInfo, 0, sizeof(stInfo));
        (HI_VOID)WinCalDobySourceInfo(pstWin, VDP_LAYER_VID1, pstDispInfo, &stInfo);
        (pfTmpSendWinInfo)(pstWin->stCfg.stSource.hSecondSrc, &stInfo);
    }
    else
    {
        HI_ERR_WIN("hSrc is invalid!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 WinGetSlaveWinAttr(HI_DRV_WIN_ATTR_S *pWinAttr,
                          HI_DRV_WIN_ATTR_S *pSlvWinAttr,
                          HI_BOOL bVirtScreen)
{
    HI_S32 nRet = HI_FAILURE;
    HI_DISP_DISPLAY_INFO_S stDispInfo, stSlaveDispInfo;
    HI_RECT_S stCanvas = {0};
    HI_RECT_S stMastOutRect = {0};
    HI_DRV_DISP_OFFSET_S stOffsetInfo = {0};

    DISP_MEMSET(pSlvWinAttr, 0, sizeof(HI_DRV_WIN_ATTR_S));
    DISP_MEMSET((void *)&stDispInfo, 0, sizeof(stDispInfo));
    DISP_MEMSET((void *)&stSlaveDispInfo, 0, sizeof(stSlaveDispInfo));

    // s1 get slave display
    nRet = DISP_GetSlave(pWinAttr->enDisp, &pSlvWinAttr->enDisp);
    if (nRet)
    {
        WIN_ERROR("Get slave Display failed\n");
        return nRet;
    }

    if (!DISP_IsOpened(pSlvWinAttr->enDisp) )
    {
        WIN_ERROR("Slave Display is not open\n");
        return HI_ERR_DISP_NOT_OPEN;
    }

    // s2 get master and slave display info
    pSlvWinAttr->bVirtual = HI_FALSE;

    /* may change when window lives */
    pSlvWinAttr->stCustmAR = pWinAttr->stCustmAR;
    pSlvWinAttr->enARCvrs  = pWinAttr->enARCvrs;

    /*now sd's crop is done by hd(vpss cropped),
       so in isogeny-wbc mode, sd's inrect and croprect should  re-calculated.
      */
    pSlvWinAttr->bUseCropRect = pWinAttr->bUseCropRect;
    pSlvWinAttr->stInRect    = pWinAttr->stInRect;
    pSlvWinAttr->stCropRect = pWinAttr->stCropRect;

    if (!bVirtScreen)
    {
        (HI_VOID)DISP_GetDisplayInfo(pWinAttr->enDisp, &stDispInfo);
        (HI_VOID)DISP_GetDisplayInfo(pSlvWinAttr->enDisp, &stSlaveDispInfo);

        stCanvas = stDispInfo.stFmtResolution;
        stOffsetInfo.u32Left = 0;
        stOffsetInfo.u32Top  = 0;
        stOffsetInfo.u32Right = 0;
        stOffsetInfo.u32Bottom = 0;

        stMastOutRect = pWinAttr->stOutRect;
        if ((stMastOutRect.s32Width == 0) || (stMastOutRect.s32Height == 0))
        {
            stMastOutRect.s32Width  = stCanvas.s32Width;
            stMastOutRect.s32Height = stCanvas.s32Height;
        }

        (HI_VOID)WinOutRectSizeConversion(&stCanvas,
                                          &stOffsetInfo,
                                          &stSlaveDispInfo.stFmtResolution,
                                          &stMastOutRect,
                                          &pSlvWinAttr->stOutRect);
    }
    else
    {
        pSlvWinAttr->stOutRect    = pWinAttr->stOutRect;
    }

    return HI_SUCCESS;
}

HI_S32 WinGetSlaveWinAttr2(WINDOW_S *pstWin,
                           HI_DRV_WIN_ATTR_S *pWinAttr,
                           HI_DRV_WIN_ATTR_S *pSlvWinAttr)
{
    HI_DISP_DISPLAY_INFO_S stDispInfo, stSlaveDispInfo;
    HI_RECT_S stCanvas = {0};
    HI_RECT_S stMastOutRect = {0};
    HI_DRV_DISP_OFFSET_S stOffsetInfo = {0};

    memset((void *)&stDispInfo, 0, sizeof(stDispInfo));
    memset((void *)&stSlaveDispInfo, 0, sizeof(stSlaveDispInfo));

    /* may change when window lives */
    pSlvWinAttr->stCustmAR = pWinAttr->stCustmAR;
    pSlvWinAttr->enARCvrs  = pWinAttr->enARCvrs;

    pSlvWinAttr->bUseCropRect = pWinAttr->bUseCropRect;
    pSlvWinAttr->stInRect    = pWinAttr->stInRect;
    pSlvWinAttr->stCropRect = pWinAttr->stCropRect;

    if (pstWin->bVirtScreenMode)
    {
        pSlvWinAttr->stOutRect  = pWinAttr->stOutRect;
    }
    else
    {
        (HI_VOID)DISP_GetDisplayInfo(pWinAttr->enDisp, &stDispInfo);
        (HI_VOID)DISP_GetDisplayInfo(pSlvWinAttr->enDisp, &stSlaveDispInfo);

        stCanvas = stDispInfo.stFmtResolution;
        stOffsetInfo.u32Left = 0;
        stOffsetInfo.u32Top  = 0;
        stOffsetInfo.u32Right = 0;
        stOffsetInfo.u32Bottom = 0;

        stMastOutRect = pWinAttr->stOutRect;
        if ((stMastOutRect.s32Width == 0) || (stMastOutRect.s32Height == 0))
        {
            stMastOutRect.s32Width  = stCanvas.s32Width;
            stMastOutRect.s32Height = stCanvas.s32Height;
        }

        (HI_VOID)WinOutRectSizeConversion(&stCanvas,
                                          &stOffsetInfo,
                                          &stSlaveDispInfo.stFmtResolution,
                                          &stMastOutRect,
                                          &pSlvWinAttr->stOutRect);
    }

    return HI_SUCCESS;
}

HI_S32 WinCheckFrame(HI_DRV_VIDEO_FRAME_S *pFrameInfo)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pFrameInfo->u32Priv[0]);

    pstPriv->u32PlayTime = 1;

    if ((pFrameInfo->eFrmType < HI_DRV_FT_NOT_STEREO)
        || (pFrameInfo->eFrmType >=  HI_DRV_FT_BUTT))
    {
        WIN_FATAL("Q Frame eFrmType error : %d, HI_DRV_FT_BUTT is %d.\n",
                  pFrameInfo->eFrmType, HI_DRV_FT_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((pFrameInfo->enSrcFrameType < HI_DRV_VIDEO_FRAME_TYPE_SDR)
        || (pFrameInfo->enSrcFrameType >=  HI_DRV_VIDEO_FRAME_TYPE_BUTT))
    {
        WIN_FATAL("Q Frame enSrcFrameType error : %d, HI_DRV_VIDEO_FRAME_TYPE_BUTT is %d.\n",
                  pFrameInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pFrameInfo->enSrcFrameType == HI_DRV_VIDEO_FRAME_TYPE_SDR)
    {
        HI_DRV_COLOR_SPACE_E  enInColorSpace = HI_DRV_CS_UNKNOWN;
        enInColorSpace = ((HI_DRV_VIDEO_PRIVATE_S *)&pFrameInfo->u32Priv[0])->eColorSpace;

        if ((HI_DRV_CS_DEFAULT >= enInColorSpace)
            || (HI_DRV_CS_BUTT <= enInColorSpace))
        {
            WIN_FATAL("Q Frame enInColorSpace error : %d.\n", enInColorSpace);
            return HI_ERR_VO_INVALID_PARA;
        }
    }

    if ((pFrameInfo->enFieldMode < HI_DRV_FIELD_TOP)
        || (pFrameInfo->enFieldMode >=  HI_DRV_FIELD_BUTT))
    {
        WIN_FATAL("Q Frame enFieldMode error : %d, HI_DRV_FIELD_BUTT is %d.\n",
                  pFrameInfo->enFieldMode, HI_DRV_FIELD_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }
    if ((pFrameInfo->enBufValidMode < HI_DRV_FIELD_TOP)
        || (pFrameInfo->enBufValidMode >=  HI_DRV_FIELD_BUTT))
    {
        WIN_FATAL("Q Frame enBufValidMode error : %d, HI_DRV_FIELD_BUTT is %d.\n",
                  pFrameInfo->enBufValidMode, HI_DRV_FIELD_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((pFrameInfo->enBitWidth < HI_DRV_PIXEL_BITWIDTH_8BIT)
        || (pFrameInfo->enBitWidth >=  HI_DRV_PIXEL_BITWIDTH_BUTT))
    {
        WIN_FATAL("Q Frame enBitWidth error : %d, HI_DRV_PIXEL_BITWIDTH_BUTT is %d.\n",
                  pFrameInfo->enBitWidth, HI_DRV_PIXEL_BITWIDTH_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((pFrameInfo->enTBAdjust < HI_DRV_VIDEO_TB_PLAY)
        || (pFrameInfo->enTBAdjust >=  HI_DRV_VIDEO_TB_BUTT))
    {
        WIN_FATAL("Q Frame enTBAdjust error : %d, HI_DRV_VIDEO_TB_BUTT is %d.\n",
                  pFrameInfo->enTBAdjust, HI_DRV_VIDEO_TB_BUTT);
        return HI_ERR_VO_INVALID_PARA;
    }


    if ((pFrameInfo->enCodecType < HI_DRV_STD_START_RESERVED)
        || (pFrameInfo->enCodecType >=  HI_DRV_STD_END_RESERVED))
    {
        WIN_FATAL("Q Frame enCodecType error : %d, HI_DRV_STD_END_RESERVED is %d.\n",
                  pFrameInfo->enCodecType, HI_DRV_STD_END_RESERVED);
        return HI_ERR_VO_INVALID_PARA;
    }

    if (!( (HI_DRV_PIX_FMT_NV12 == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV21 == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV21_CMP  == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV21_TILE == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV21_TILE_CMP == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV61_2X1 == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_NV42 == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_RGB24 == pFrameInfo->ePixFormat)
           || (HI_DRV_PIX_FMT_ARGB8888 == pFrameInfo->ePixFormat)
         )
       )
    {
        WIN_FATAL("Q Frame pixformat error : %d\n", pFrameInfo->ePixFormat);
        return HI_ERR_VO_INVALID_PARA;
    }

    if ( (pFrameInfo->u32Width < WIN_FRAME_MIN_WIDTH)
         || (pFrameInfo->u32Width > WIN_FRAME_MAX_WIDTH)
         || (pFrameInfo->u32Height < WIN_FRAME_MIN_HEIGHT)
         || (pFrameInfo->u32Height > WIN_FRAME_MAX_HEIGHT)
       )
    {
        WIN_FATAL("Q Frame resolution error : w=%d,h=%d\n",
                  pFrameInfo->u32Width, pFrameInfo->u32Height);
        return HI_ERR_VO_INVALID_PARA;
    }

    pFrameInfo->stDispRect.s32X = 0;
    pFrameInfo->stDispRect.s32Y = 0;
    pFrameInfo->stDispRect.s32Width  = pFrameInfo->u32Width;
    pFrameInfo->stDispRect.s32Height = pFrameInfo->u32Height;

    if ((pFrameInfo->u32FrameRate > WIN_MAX_FRAME_RATE)
        || (0 == pFrameInfo->u32FrameRate))
    {
        WIN_ERROR("Q Frame u32FrameRate error:%d, max frame rate is %d.\n",
                  pFrameInfo->u32FrameRate, WIN_MAX_FRAME_RATE);
        return HI_ERR_VO_INVALID_PARA;
    }

    if ((0 == pFrameInfo->stBufAddr[0].u32PhyAddr_Y)
        && (0 == pFrameInfo->stBufAddr[0].u32PhyAddr_YHead))
    {
        WIN_ERROR("Invalid addr:%x,%x!\n", pFrameInfo->stBufAddr[0].u32PhyAddr_Y, pFrameInfo->stBufAddr[0].u32PhyAddr_YHead);
        return HI_ERR_VO_INVALID_PARA;
    }


    return HI_SUCCESS;
}

HI_S32 WinAttachDefaultSource(WINDOW_S *pstWin)
{
    WB_SOURCE_INFO_S stSrc2Buf;
    HI_S32 nRet = HI_SUCCESS;

    memset(&stSrc2Buf, 0x0, sizeof(stSrc2Buf));
    /*when create window, default set the attach obj to vo it self.*/
    pstWin->stCfg.stSource.hSrc = pstWin->u32Index;
    pstWin->stCfg.stSource.pfAcqFrame = HI_NULL;
    pstWin->stCfg.stSource.pfRlsFrame = Win_ReleaseDisplayedFrame_ForDequeue;
    pstWin->stCfg.stSource.pfSendWinInfo = HI_NULL;
    pstWin->stCfg.stSource.hSecondSrc = HI_INVALID_HANDLE;

    /*and set the window's buffer  attach source.*/
    stSrc2Buf.hSrc = pstWin->u32Index;
    stSrc2Buf.hSecondSrc = HI_INVALID_HANDLE;
    stSrc2Buf.pfAcqFrame = HI_NULL;
    stSrc2Buf.pfRlsFrame = Win_ReleaseDisplayedFrame_ForDequeue;
    nRet =  WinBuf_SetSource(&pstWin->stBuffer.stWinBP, &stSrc2Buf);

    return nRet;
}

static HI_S32 WIN_Create_Seperate(HI_DRV_WIN_ATTR_S *pWinAttr,
                                  HI_HANDLE phWin,
                                  HI_U32    u32BufNum,
                                  WINDOW_S **pWindowReturn)
{
    WINDOW_S *pWindow = HI_NULL;
    HI_S32 nRet = HI_SUCCESS;
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    HI_U32 i = 0;

    if (DISP_IsOpened(pWinAttr->enDisp) != HI_TRUE)
    {
        WIN_ERROR("DISP is not opened!\n");
        return HI_ERR_DISP_NOT_EXIST;
    }

    nRet = WinCreateDisplayWindow(pWinAttr, &pWindow, u32BufNum);
    if (nRet)
    {
        return nRet;
    }

    (HI_VOID)DISP_GetDisplayInfo(pWinAttr->enDisp, &stDispInfo);
    WinUpdateDispInfo(pWindow, &stDispInfo);

    for (i = 0; i < WIN_ALG_MMZ_NUM; i++)
    {
        nRet = DISP_OS_MMZ_AllocAndMap((const char *)"VDP_DBM_MEM",
                                       VDP_MEM_TYPE_PHY,
                                       WIN_ALG_MMZ_SIZE,
                                       VDP_MEM_ALIGN,
                                       &pWindow->stWinAlgMMZ[i].stVideoAlgMmz);
        if (nRet)
        {
            goto __ERR_RET_DESTROY__;
        }

        pWindow->stWinAlgMMZ[i].bReady = HI_TRUE;
    }

    /*before regcallback, create wbc first.*/
    nRet = WinRegCallback(pWindow);
    if (nRet)
    {
        goto __ERR_RET_DESTROY__;
    }

    nRet = WinAddWindow(pWindow->enDisp, pWindow);
    if (nRet)
    {
        goto __ERR_RET_UNREG_;
    }

    nRet = WinAttachDefaultSource(pWindow);
    if (nRet)
    {
        goto __ERR_RET_DELWIN;
    }

    /*this branch is for  main window,  only create wbc in  the first main window.*/
    if ((stDispWindow.eIsogeny_mode == ISOGENY_WBC_MODE)
        && DISP_IsFollowed(pWindow->enDisp))
    {
        stDispWindow.u32CurrentHdWindowCounts ++;
    }

    *pWindowReturn  = pWindow;
    return HI_SUCCESS;

__ERR_RET_DELWIN:
    WinDelWindow(pWindow->u32Index);

__ERR_RET_UNREG_:
    WinUnRegCallback(pWindow);

__ERR_RET_DESTROY__:

    for (i = 0; i < WIN_ALG_MMZ_NUM; i++)
    {
        if ((HI_TRUE == pWindow->stWinAlgMMZ[i].bReady)
            && (0 != pWindow->stWinAlgMMZ[i].stVideoAlgMmz.pu8StartVirAddr)
            && (0 != pWindow->stWinAlgMMZ[i].stVideoAlgMmz.u32StartPhyAddr))
        {
            DISP_OS_MMZ_UnmapAndRelease(&pWindow->stWinAlgMMZ[i].stVideoAlgMmz);
        }

        pWindow->stWinAlgMMZ[i].bReady = HI_FALSE;
    }

    WinDestroyDisplayWindow(pWindow);
    return nRet;
}

HI_S32 WIN_Sync_DeInit(WINDOW_S *pstWindow);

HI_S32 WIN_Destroy_Seperate(HI_HANDLE hWin)
{
    WINDOW_S *pstWin =  HI_NULL;
    HI_S32 nRet = HI_SUCCESS;
    HI_U32 i = 0;
    WinCheckWindow(hWin, pstWin);

    /*check whether slave window can be destroy.*/
    if (HI_FALSE == WinCheckWhetherCanToDestroy(hWin))
    {
        return HI_SUCCESS;
    }

    /*disable  hardware first, after that  the software can be released.*/
    if (pstWin->bEnable == HI_TRUE)
    {
        (HI_VOID)WIN_SetEnable(hWin, HI_FALSE);
    }

    /* stop isr secondly.*/
    (HI_VOID)WinUnRegCallback(pstWin);

#ifdef HI_VO_WIN_SYNC_SUPPORT
    (HI_VOID)WIN_Sync_DeInit(pstWin);
#endif

    WinDelWindow(pstWin->u32Index);

    for (i = 0; i < WIN_ALG_MMZ_NUM; i++)
    {
        if ((0 != pstWin->stWinAlgMMZ[i].stVideoAlgMmz.pu8StartVirAddr)
            && (0 != pstWin->stWinAlgMMZ[i].stVideoAlgMmz.u32StartPhyAddr))
        {
            DISP_OS_MMZ_UnmapAndRelease(&pstWin->stWinAlgMMZ[i].stVideoAlgMmz);
        }
        else
        {
            WIN_ERROR("Null addr when unmap and release.\n");
        }

        pstWin->stWinAlgMMZ[i].bReady = HI_FALSE;
    }

    if (WinCheckWhetherWbcIsogenyMode()
        && (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE))
    {
        stDispWindow.u32CurrentHdWindowCounts --;
    }

    (HI_VOID)WinDestroyDisplayWindow(pstWin);

    return nRet;
}

HI_S32 WIN_Sync_Init(WINDOW_S *pstWindow)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    WIN_SYNC_INFO_S *pstSyncInfo = HI_NULL;
    HI_U32 u32Index = 0;
    HI_S32 nRet = 0;

    if (pstWindow->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE)
    {
        pstSyncInfo = &(pstWindow->stSyncInfo);
        u32Index = pstWindow->u32Index;
    }
    else if (pstWindow->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        pstSyncInfo = &(pstWindow->stSyncInfo);
        u32Index = pstWindow->u32Index;
    }
    else
    {
        return HI_SUCCESS;
    }

    nRet = DRV_SYNC_Init(pstSyncInfo, u32Index);
    if (nRet)
    {
        WIN_ERROR("win %#x Sync Init Failed\n", u32Index);
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

HI_S32 WIN_Sync_DeInit(WINDOW_S *pstWindow)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    WIN_SYNC_INFO_S *pstSyncInfo = HI_NULL;
    HI_S32 nRet = 0;

    if (pstWindow->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE)
    {
        pstSyncInfo = &(pstWindow->stSyncInfo);
    }
    else if (pstWindow->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        pstSyncInfo = &(pstWindow->stSyncInfo);
    }
    else
    {
        return HI_SUCCESS;
    }

    nRet = DRV_SYNC_DeInit(pstSyncInfo);
    if (nRet)
    {
        WIN_ERROR("win %#x Sync DeInit Failed\n", pstWindow->u32Index);
        return HI_FAILURE;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 WinQueueFrame(HI_HANDLE hWin, WIN_XDR_FRAME_S *pstWinXdrFrm);
HI_S32 WIN_Sync_QueueFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo, HI_U32 *pu32FenceFd)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 s32Ret = HI_SUCCESS;
    WIN_XDR_FRAME_S *pstWinXdrFrm = HI_NULL;

    WinCheckWindow(hWin, pstWin);
    WinCheckNullPointer(pFrameInfo);

    if ((pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE)
        || (pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE))
    {
        /* malloc buff to load frame. */
        pstWinXdrFrm = (WIN_XDR_FRAME_S *)HI_KMALLOC(HI_ID_VO, sizeof(WIN_XDR_FRAME_S), GFP_KERNEL);
        if (HI_NULL == pstWinXdrFrm)
        {
            HI_ERR_WIN("Malloc pstWinXdrFrm failed.\n");
            return HI_ERR_VO_MALLOC_FAILED;
        }

        pstWinXdrFrm->hWindow = hWin;
        pstWinXdrFrm->stBaseFrm = *pFrameInfo;
        /* get disp output type and xdrEngine. */
        s32Ret = WIN_POLICY_GetOutputTypeAndEngine(hWin,
                 pFrameInfo->enSrcFrameType,
                 &pstWinXdrFrm->enDispOutType,
                 &pstWinXdrFrm->enXdrEngine);
        if (s32Ret != HI_SUCCESS)
        {
            WIN_ERROR("Get output type fail.\n");
            HI_KFREE(HI_ID_VO, pstWinXdrFrm);
            return s32Ret;
        }

        s32Ret = WinQueueFrame(hWin, pstWinXdrFrm);
        if (s32Ret != HI_SUCCESS)
        {
            WIN_ERROR("win %#x QueueFrame Failed\n", hWin);
            HI_KFREE(HI_ID_VO, pstWinXdrFrm);
            return HI_FAILURE;
        }

        if (*pu32FenceFd != 0x0)
        {
            *pu32FenceFd = DRV_SYNC_CreateFence(&pstWin->stSyncInfo,
                                                pFrameInfo->u32FrameIndex,
                                                pFrameInfo->stBufAddr[0].u32PhyAddr_Y);
        }
        else
        {
            DRV_SYNC_AddData(&pstWin->stSyncInfo,
                             pFrameInfo->u32FrameIndex,
                             pFrameInfo->stBufAddr[0].u32PhyAddr_Y);
        }

        WinDebug_SetDataFlowPath(&pstWin->stWinInfoForDeveloper, HI_DATA_FLOW_QUEUE_FENCE);

        HI_KFREE(HI_ID_VO, pstWinXdrFrm);
    }
    else
    {
        WIN_ERROR("slave window does not support queue in wbc-isogeny mode.\n", hWin);
        return HI_FAILURE;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 WIN_Sync_Reset(HI_HANDLE hWin, HI_DRV_WIN_SWITCH_E enRst, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    WINDOW_S *pstWin = HI_NULL;
    WIN_SYNC_INFO_S *pstSyncInfo;

    WinCheckDeviceOpen();
    WinCheckWindow(hWin, pstWin);

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE
        || pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        pstSyncInfo = &(pstWin->stSyncInfo);
    }
    else
    {
        return HI_SUCCESS;
    }

    if (enRst == HI_DRV_WIN_SWITCH_BLACK)
    {
        DRV_SYNC_Flush(pstSyncInfo);
    }
    else if (enRst == HI_DRV_WIN_SWITCH_LAST)
    {
        if (pstFrame)
        {
            DRV_SYNC_Signal(pstSyncInfo,
                            pstFrame->u32FrameIndex,
                            pstFrame->stBufAddr[0].u32PhyAddr_Y);
        }
        else
        {
            DRV_SYNC_Flush(pstSyncInfo);
        }
    }
#endif
    return HI_SUCCESS;
}

HI_S32 WIN_Sync_Flush(WINDOW_S *pstWin)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT
    WIN_SYNC_INFO_S *pstSyncInfo = HI_NULL;

    WinCheckDeviceOpen();

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE
        || pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        pstSyncInfo = &(pstWin->stSyncInfo);
    }
    else
    {
        return HI_SUCCESS;
    }

    DRV_SYNC_Flush(pstSyncInfo);
#endif
    return HI_SUCCESS;
}

HI_S32 WIN_Sync_Signal(WINDOW_S *pstWin, HI_U32 u32Index, HI_U32 u32Addr)
{
#ifdef HI_VO_WIN_SYNC_SUPPORT

    WIN_SYNC_INFO_S *pstSyncInfo;
    WinCheckDeviceOpen();

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE
        || pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        pstSyncInfo = &(pstWin->stSyncInfo);
    }
    else
    {
        return HI_SUCCESS;
    }

    (HI_VOID)DRV_SYNC_Signal(pstSyncInfo, u32Index, u32Addr);
#endif
    return HI_SUCCESS;
}

HI_S32 WIN_Create_SlaveWin(HI_DRV_WIN_ATTR_S *pWinAttr,
                           HI_BOOL bVirtScreen,
                           HI_HANDLE *phSlvWin,
                           HI_VOID *pstMasterWin)
{
    HI_DRV_WIN_ATTR_S stSlvWinAttr;
    WINDOW_S *pSlaveWindow = HI_NULL;
    HI_U32 phWin = 0;
    HI_S32 nRet = 0;

    /*in isogeny wbc mode, the sd window is a singleton mode.*/
    if ((stDispWindow.eIsogeny_mode == ISOGENY_WBC_MODE)
        && (stDispWindow.u32CurrentHdWindowCounts > 1))
    {
        *phSlvWin = g_hSlaveWin;
        return  HI_SUCCESS;
    }

    /*in fact, in isogeny-wbc mode,  slave's winattr partly is generated
      * according to the wbc's output.
      */
    nRet = WinGetSlaveWinAttr(pWinAttr, &stSlvWinAttr, bVirtScreen);
    if (nRet)
    {
        WIN_ERROR("Get Slave WinAttr is invalid!\n");
        return HI_FAILURE;
    }

    nRet = WIN_Create_Seperate(&stSlvWinAttr,
                               phWin,
                               WIN_IN_FB_DEFAULT_NUMBER,
                               &pSlaveWindow);
    if (nRet)
    {
        WIN_ERROR("Creat slave window failed!\n");
        return HI_FAILURE;
    }

    /*pointer to each other.*/
    *phSlvWin    =  (HI_HANDLE)(pSlaveWindow->u32Index);
    g_hSlaveWin  =  (HI_HANDLE)(pSlaveWindow->u32Index);

    pSlaveWindow->pstMstWin = (HI_VOID *)pstMasterWin;
    pSlaveWindow->enType = HI_DRV_WIN_ACTIVE_SLAVE ;
    pSlaveWindow->bVirtScreenMode = bVirtScreen;

    /*in this func,  means this is  iso-geny already.*/
    if (stDispWindow.eIsogeny_mode != ISOGENY_WBC_MODE)
    {
#ifdef HI_VO_WIN_SYNC_SUPPORT
        /*in isogeny mode,  the sync mode  is not neccesary.*/
        (HI_VOID)WIN_Sync_Init(pSlaveWindow);
#endif
    }

    return HI_SUCCESS;
}


/******************************************************************************
    apply function
******************************************************************************/
HI_S32 WIN_Create_MCE(HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWin, HI_BOOL bVirtScreen)
{

    WINDOW_S *pstWin = HI_NULL;
    HI_S32 nRet = HI_SUCCESS;

    nRet = WIN_Create(pWinAttr, phWin, bVirtScreen);

    if (HI_SUCCESS == nRet)
    {
        WinCheckWindow(*phWin, pstWin);
        pstWin->bMCE = HI_TRUE;
    }

    return nRet;
}
HI_S32 WIN_Create(HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWin, HI_BOOL bVirtScreen)
{
    HI_S32 nRet = HI_SUCCESS;
    WINDOW_S *pWindow = HI_NULL;
    HI_HANDLE hSlaveWin = 0;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pWinAttr);
    WinCheckNullPointer(phWin);
    DispCheckID(pWinAttr->enDisp);

    // s1 check attribute
    nRet = WinCheckAttr(pWinAttr, bVirtScreen);
    if (nRet)
    {
        WIN_ERROR("WinAttr is invalid!\n");
        return nRet;
    }

    if (!WinGetRegWinManageStatus())
    {
        WinRegWinManageCallback(HI_DRV_DISPLAY_0);
        WinRegWinManageCallback(HI_DRV_DISPLAY_1);
        WinSetRegWinManageStatus(HI_TRUE);
    }

    if (pWinAttr->bVirtual != HI_TRUE)
    {
        nRet = WIN_Create_Seperate(pWinAttr, *phWin, WIN_IN_FB_DEFAULT_NUMBER, &pWindow);
        if (nRet)
        {
            return nRet;
        }

        pWindow->bVirtScreenMode = bVirtScreen;
        *phWin = (HI_HANDLE)(pWindow->u32Index);

        /*if master mode, create the slave window.*/
        if (DISP_IsFollowed(pWinAttr->enDisp) && ( HI_TRUE != WinCheckWhetherWbcIsogenyMode()))
        {
            nRet = WIN_Create_SlaveWin(pWinAttr,
                                       bVirtScreen,
                                       &hSlaveWin,
                                       pWindow);
            if (nRet)
            {
                goto __ERR_RET_UNREG_CB__;
            }

            pWindow->enType = HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE;
            pWindow->hSlvWin = hSlaveWin;

        }
        else
        {
            pWindow->enType = HI_DRV_WIN_ACTIVE_SINGLE;
        }

#ifdef HI_VO_WIN_SYNC_SUPPORT
        (HI_VOID)WIN_Sync_Init(pWindow);
#endif
        return HI_SUCCESS;

    __ERR_RET_UNREG_CB__:
        WIN_Destroy_Seperate(pWindow->u32Index);
        return nRet;
    }
    else
    {
        VIRTUAL_S *pstVirWindow = HI_NULL;
        nRet = WIN_VIR_Create(pWinAttr, &pstVirWindow);
        if (nRet)
        {
            return nRet;
        }

        pstVirWindow->enType = HI_DRV_WIN_VITUAL_SINGLE;

        // add to virtual window array, if win_deinit, auto destory it
        nRet = WinAddVirWindow(pstVirWindow);
        if (nRet)
        {
            WIN_VIR_Destroy(pstVirWindow);
            return nRet;
        }
        else
        {
            *phWin = (HI_HANDLE)(pstVirWindow->u32Index);
            return HI_SUCCESS;
        }
    }

    return HI_SUCCESS;
}


/*slave's  enable and create/destroy opts , are invisible above.**/
HI_S32 WIN_Destroy(HI_HANDLE hWin)
{
    WINDOW_S *pstWin;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;
    HI_HANDLE hSlaveWin = HI_INVALID_HANDLE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        if (pstWin->hSlvWin)
        {
            hSlaveWin = pstWin->hSlvWin;
        }

        nRet = WIN_Destroy_Seperate(hWin);
        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }

        /*destroy slave window first, then wbc.  because  if wbc destroyed first
          *, mem released either. slave window will have no mem to use.*/
        if (HI_INVALID_HANDLE != hSlaveWin)
        {
            nRet = WIN_Destroy_Seperate(hSlaveWin);
            if (HI_SUCCESS != nRet)
            {
                return nRet;
            }
        }
    }
    else
    {
        VIRTUAL_S *pstVirWin = HI_NULL;

        WinCheckVirWindow(hWin, pstVirWin);
        WinDelVirWindow(hWin);
        nRet = WIN_VIR_Destroy(pstVirWin);
        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_CheckAttachState(HI_HANDLE hWin, HI_BOOL *pbSrcAttached, HI_BOOL *pbSinkAttached)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WINDOW_S *pstWin;

        WinCheckWindow(hWin, pstWin);

        if ((pstWin->stCfg.stSource.hSrc == HI_INVALID_HANDLE)
            || (pstWin->stCfg.stSource.hSrc == hWin))
        {
            *pbSrcAttached = HI_FALSE;
        }
        else
        {
            *pbSrcAttached = HI_TRUE;
        }

        *pbSinkAttached = HI_FALSE;
    }
    else
    {
        VIRTUAL_S *pstVirWin;
        WinCheckVirWindow(hWin, pstVirWin);

        if (pstVirWin->hSink == HI_INVALID_HANDLE)
        {
            *pbSinkAttached = HI_FALSE;
        }
        else
        {
            *pbSinkAttached = HI_TRUE;
        }

        if (pstVirWin->stSrcInfo.hSrc == HI_INVALID_HANDLE)
        {
            *pbSrcAttached = HI_FALSE;
        }
        else
        {
            *pbSrcAttached = HI_TRUE;
        }
    }

    return HI_SUCCESS;
}

/*get current number.*/
HI_U32 WIN_GetDisp1CurrentWinCnt(HI_VOID)
{
    return  stDispWindow.u32WinNumber[HI_DRV_DISPLAY_1];
}

HI_S32 WIN_SetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    WINDOW_S *pstWin;
    HI_DRV_WIN_ATTR_S stSlvWinAttr;
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;
    WINDOW_S *pstWinTmp = HI_NULL;
    //    HI_U32  u32Wait = 0;
    HI_SIZE_T irqflag = 0;
    HI_BOOL bCloseHdr = HI_FALSE;
    WinCheckDeviceOpen();
    WinCheckNullPointer(pWinAttr);

    memset((void *)&stSlvWinAttr, 0, sizeof(HI_DRV_WIN_ATTR_S));
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        nRet = WinCheckFixedAttr(&pstWin->stCfg.stAttrBuf, pWinAttr);
        if (nRet)
        {
            return nRet;
        }

        nRet = WinCheckAttr(pWinAttr, pstWin->bVirtScreenMode);
        if (nRet)
        {
            return nRet;
        }
        if (HI_TRUE != WinCheckAttrChange(pWinAttr, &pstWin->stCfg.stAttrBuf))
        {
            WIN_WARN("set same attr!\n");
            return HI_SUCCESS;
        }

        nRet = DISP_GetDisplayInfo(pstWin->enDisp, &stDispInfo);
        if (nRet)
        {
            WIN_ERROR("DISP_GetDisplayInfo failed in %s!\n", __FUNCTION__);
            return HI_ERR_VO_CREATE_ERR;
        }

        pstWinTmp = (WINDOW_S *) DISP_MALLOC(sizeof(WINDOW_S));
        if (!pstWinTmp)
        {
            return HI_ERR_VO_MALLOC_FAILED;
        }

        *pstWinTmp = *pstWin;
        bCloseHdr = pstWinTmp->stCfg.stAttrBuf.bCloseHdrPath;
        pstWinTmp->stCfg.stAttrBuf = *pWinAttr;
        pstWinTmp->stCfg.stAttrBuf.bCloseHdrPath = bCloseHdr;
        WinUpdateDispInfo(pstWinTmp, &stDispInfo);

        /*to judge the layout valid or not.*/
        spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
        nRet =    WindowRedistributeProcess(pstWinTmp);
        if (nRet)
        {
            spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
            DISP_FREE(pstWinTmp);
            WIN_ERROR("reallocate video layer failed in %s!\n", __FUNCTION__);
            return nRet;
        }

        spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);

        /*update the formal window's initial fmt.*/
        WinUpdateDispInfo(pstWin, &stDispInfo);

        bCloseHdr = pstWin->stCfg.stAttrBuf.bCloseHdrPath;
        pstWin->stCfg.stAttrBuf = *pWinAttr;
        pstWin->stCfg.stAttrBuf.bCloseHdrPath = bCloseHdr;
        atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);

        /*wait for the hal resources:such as physical layers, zorder to take effect.*/
        if (pstWin->bEnable)
        {
            (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_TRUE);
            /* WIN_SetAttr and Win's interrupt process function may run in
                    * different core, when interrupt process run after WIN_SetAttr,it will cause TIME-OUT.
                    * therefore,add atomic_read NewAttrFlag here to avoid this problem.
                    * Testing result shows that it takes about 1ms to run over all interrupt process functions
                    * in DISP1(0% location),here max sleep 5ms to ensure Win's interrupt function be processed.
                    */

            nRet = DISP_OSAL_WaitEvent(&pstWin->stWinQueueEvent, EVENT_WIN_ATTR_UP_COMPLET, 50);
            DISP_OSAL_ResetEvent(&pstWin->stWinQueueEvent, EVENT_WIN_NOTHING);

            if (HI_SUCCESS != nRet)
            {
                DISP_WARN("############ freeze TIMEOUT#########\n");
                return HI_ERR_VO_TIMEOUT;
            }
        }
        else
        {
            (HI_VOID)WindowRedistributeProcess_Wait(pstWin, HI_FALSE);
        }

        if (pstWin->hSlvWin)
        {
            /*only non-wbc mode , or 1 window in wbc-mode, can slave's attr be set. */
            if ((stDispWindow.eIsogeny_mode != ISOGENY_WBC_MODE) ||  (WIN_GetDisp1CurrentWinCnt() == 1))
            {
                WIN_GetAttr(pstWin->hSlvWin, &stSlvWinAttr);
                WinGetSlaveWinAttr2(pstWin, pWinAttr, &stSlvWinAttr);
                nRet = WIN_SetAttr(pstWin->hSlvWin, &stSlvWinAttr);
            }
        }

        DISP_FREE(pstWinTmp);
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        WinCheckVirWindow(hWin, pstVirWindow);
        nRet = WIN_VIR_SetAttr(pstVirWindow, pWinAttr);

        return nRet;
    }

    return nRet;
}



HI_S32 WIN_GetAttr(HI_HANDLE hWin, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pWinAttr);
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WINDOW_S *pstWin;

        WinCheckWindow(hWin, pstWin);
        *pWinAttr = pstWin->stCfg.stAttrBuf;
    }
    else
    {
        VIRTUAL_S *pstVirWindow;

        WinCheckVirWindow(hWin, pstVirWindow);
        *pWinAttr = pstVirWindow->stAttrBuf;
    }

    return HI_SUCCESS;
}


//get info for source
HI_S32 WIN_GetInfo(HI_HANDLE hWin, HI_DRV_WIN_INFO_S *pstInfo)
{
    WINDOW_S *pstWin;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstInfo);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        pstInfo->eType = WinGetType(pstWin);
        pstInfo->hPrim = (HI_HANDLE)(pstWin->u32Index);
        pstInfo->hSec  = (HI_HANDLE)(pstWin->hSlvWin);
    }
    else
    {
        VIRTUAL_S *pstVirWin;
        WinCheckVirWindow(hWin, pstVirWin);

        pstInfo->eType = pstVirWin->enType;
        pstInfo->hPrim = (HI_HANDLE)(pstVirWin->u32Index);
        pstInfo->hSec  = HI_INVALID_HANDLE;
    }

    return HI_SUCCESS;
}

static HI_S32 WIN_ResetWithBlkFrm(HI_HANDLE hWin, HI_BOOL *pbEnable)
{
    HI_S32  nRet = HI_SUCCESS;

    (HI_VOID)WIN_GetEnable(hWin, pbEnable);
    if (HI_TRUE == *pbEnable)
    {
        nRet = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST);
    }
    else
    {
        nRet = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_BLACK);
    }

    return nRet;
}

HI_S32 WIN_SetSdrSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{
    HI_DISP_DISPLAY_INFO_S stDispInfo = {0};
    WB_SOURCE_INFO_S stSrc2Buf = {0};
    WINDOW_S *pstWin = HI_NULL;
    HI_BOOL bVirtual = HI_FALSE;

    HI_S32 nRet = HI_SUCCESS;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstSrc);

    if (pstSrc->hSrc == HI_INVALID_HANDLE)
    {
        HI_BOOL bEnable = HI_FALSE;
        (HI_VOID)WIN_GetEnable(hWin, &bEnable);

        if (HI_TRUE == bEnable)
        {
            WIN_WARN("Reset Window HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST\n");
            nRet = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST);
        }
        else
        {
            nRet = WIN_Reset(hWin, HI_DRV_WIN_SWITCH_BLACK);
        }

        if (HI_SUCCESS != nRet)
        {
            DISP_ERROR("Reset Window Failed\n");
            return nRet;
        }
    }

    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        nRet = DISP_GetDisplayInfo(WinGetDispID(pstWin), &stDispInfo);
        if (nRet)
        {
            return nRet;
        }

        if (pstWin->stCfg.stSource.hSrc == pstSrc->hSrc)
        {
            if (pstSrc->hSrc)
            {
                WIN_ERROR("Attach repeately!\n");
            }
            else
            {
                WIN_ERROR("Detach repeately!\n");
            }

            return HI_ERR_VO_OPERATION_DENIED;
        }

        pstWin->stCfg.stSource = *pstSrc;

        stSrc2Buf.hSrc = pstSrc->hSrc;
        stSrc2Buf.pfAcqFrame = pstSrc->pfAcqFrame;
        stSrc2Buf.pfRlsFrame = pstSrc->pfRlsFrame;
        nRet =  WinBuf_SetSource(&pstWin->stBuffer.stWinBP, &stSrc2Buf);

        if (nRet)
        {
            return nRet;
        }

        // send attr to source
        WinSendAttrToSource(pstWin, &stDispInfo);
    }
    else
    {
        WIN_ERROR("Virtual Window doesn't support SDR/HDR mode\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_SetHdrSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    WB_SOURCE_INFO_S stSrc2Buf;
    WINDOW_S *pstWin;
    HI_BOOL bEnable = HI_FALSE;
    HI_BOOL bVirtual;
    HI_S32 nRet = HI_SUCCESS;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstSrc);

    if ((HI_INVALID_HANDLE == pstSrc->hSrc) &&
        (pstSrc->hSecondSrc != HI_INVALID_HANDLE))
    {
        WIN_ERROR("Not support,BL is invalid while EL is valid!\n");
        return HI_ERR_VO_INVALID_OPT;
    }

    if ((HI_INVALID_HANDLE == pstSrc->hSrc) &&
        (HI_INVALID_HANDLE == pstSrc->hSecondSrc))
    {
        nRet = WIN_ResetWithBlkFrm(hWin, &bEnable);
        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }
    }

    if ((HI_INVALID_HANDLE != pstSrc->hSrc) &&
        (HI_INVALID_HANDLE == pstSrc->hSecondSrc))
    {
        nRet = WIN_ResetWithBlkFrm(hWin, &bEnable);
        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }
    }

    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        nRet = DISP_GetDisplayInfo(WinGetDispID(pstWin), &stDispInfo);
        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }
        if (HI_INVALID_HANDLE == pstSrc->hSrc)
        {
            if ((pstWin->stCfg.stSource.hSrc == pstSrc->hSrc) &&
                (pstWin->stCfg.stSource.hSecondSrc == pstSrc->hSecondSrc))
            {
                WIN_ERROR("Detach repeately!\n");
                return HI_ERR_VO_OPERATION_DENIED;
            }
        }
        else
        {
            if ((pstWin->stCfg.stSource.hSrc == pstSrc->hSrc) &&
                (pstWin->stCfg.stSource.hSecondSrc == pstSrc->hSecondSrc))
            {
                WIN_ERROR("Attach repeately!\n");
                return HI_ERR_VO_OPERATION_DENIED;
            }
        }
        pstWin->stCfg.stSource = *pstSrc;

        stSrc2Buf.hSrc = pstSrc->hSrc;
        stSrc2Buf.hSecondSrc = pstSrc->hSecondSrc;
        stSrc2Buf.pfAcqFrame = pstSrc->pfAcqFrame;
        stSrc2Buf.pfRlsFrame = pstSrc->pfRlsFrame;
        nRet =  WinBuf_SetSource(&pstWin->stBuffer.stWinBP, &stSrc2Buf);

        if (HI_SUCCESS != nRet)
        {
            return nRet;
        }

        // send attr to source
        WinSendAttrToSource(pstWin, &stDispInfo);

    }
    else
    {
        VIRTUAL_S *pstVirWin;
        WinCheckVirWindow(hWin, pstVirWin);

        if (pstVirWin->stSrcInfo.hSrc == pstSrc->hSrc)
        {
            if (pstSrc->hSrc)
            {
                WIN_ERROR("Attach repeately!\n");
            }
            else
            {
                WIN_ERROR("Detach repeately!\n");
            }

            return HI_ERR_VO_OPERATION_DENIED;
        }

        pstVirWin->stSrcInfo = *pstSrc;

        WIN_VIR_SendAttrToSource(pstVirWin);
    }
    return HI_SUCCESS;
}

HI_S32 WIN_SetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{
    HI_S32    s32Ret;
    WINDOW_S *pstWin;
    HI_BOOL bVirtual;

    if ((pstSrc->hSrc == HI_INVALID_HANDLE) && (pstSrc->hSecondSrc != HI_INVALID_HANDLE))
    {
        WIN_ERROR("Invalid hsrc number:%x,%x\n", pstSrc->hSrc, pstSrc->hSecondSrc);
        return HI_ERR_VO_INVALID_PARA;
    }

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        DispCheckID(pstWin->enDisp);

        if ((HI_DRV_WINDOW_MODE_NORMAL == pstWin->enWinMode)
            || (HI_DRV_WINDOW_MODE_HDR == pstWin->enWinMode))
        {
            pstSrc->hSecondSrc = HI_INVALID_HANDLE;
            s32Ret = WIN_SetSdrSource(hWin, pstSrc);
            if (HI_SUCCESS != s32Ret)
            {
                WIN_ERROR("set sdrsource failed\n");
                return  s32Ret;
            }
        }
        else if (HI_DRV_WINDOW_MODE_DOLBY == pstWin->enWinMode)
        {
            s32Ret = WIN_SetHdrSource(hWin, pstSrc);
            if (HI_SUCCESS != s32Ret)
            {
                WIN_ERROR("set dolbysource failed\n");
                return  s32Ret;
            }
        }
        else
        {
            return HI_ERR_VO_WIN_UNSUPPORT;
        }

        if (HI_INVALID_HANDLE == pstSrc->hSrc)
        {
            WinDebug_SetDataFlowPath(&pstWin->stWinInfoForDeveloper, HI_DATA_FLOW_QUEUE_DEQUEUE);
        }
        else
        {
            WinDebug_SetDataFlowPath(&pstWin->stWinInfoForDeveloper, HI_DATA_FLOW_QUEUE_ISRRELEASE);
        }
    }
    else
    {
        VIRTUAL_S *pstVirWin;
        WinCheckVirWindow(hWin, pstVirWin);

        if (pstVirWin->stSrcInfo.hSrc == pstSrc->hSrc)
        {
            if (pstSrc->hSrc)
            {
                WIN_ERROR("Attach repeately!\n");
            }
            else
            {
                WIN_ERROR("Detach repeately!\n");
            }

            return HI_ERR_VO_OPERATION_DENIED;
        }

        pstVirWin->stSrcInfo = *pstSrc;

        s32Ret = WIN_VIR_SendAttrToSource(pstVirWin);
    }

    return s32Ret;
}
HI_S32 WIN_GetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{
    WINDOW_S *pstWin;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstSrc);
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        *pstSrc = pstWin->stCfg.stSource;
    }
    else
    {
        VIRTUAL_S *pstVirWin;
        WinCheckVirWindow(hWin, pstVirWin);
        *pstSrc = pstVirWin->stSrcInfo;
    }


    return HI_SUCCESS;
}

/*
1) whether salve;
2) now window's num;
3) wbc mode or not?
3) enable or not.
4) if enable == pstwin's enable status, return;
   output: whether allow to set enable or not.
*/
HI_BOOL WIN_Judge_WhetherCanSetEnable(WINDOW_S *pstWin, HI_BOOL bEnable)
{
    HI_U32 i = 0, u32WinEnableNum = 0;

    /*if  flag is the same with previous setting, do nothing.*/
    if (bEnable == pstWin->bEnable)
    {
        WIN_WARN("Set the same enable Flag.!\n");
        return HI_FALSE;
    }

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stDispWindow.pstWinArray[HI_DRV_DISPLAY_1][i]
            && (stDispWindow.pstWinArray[HI_DRV_DISPLAY_1][i]->bEnable))
        {
            u32WinEnableNum ++;
        }
    }

    if (HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == WinGetType(pstWin)
        || HI_DRV_WIN_ACTIVE_SINGLE == WinGetType(pstWin)
        || HI_DRV_WIN_VITUAL_SINGLE == WinGetType(pstWin))
    {
        /*if master,  do not  make limit.*/
        return HI_TRUE;
    }
    else
    {
        /*only  slave window not in wbc mode can do freeze.*/
        if (stDispWindow.eIsogeny_mode != ISOGENY_WBC_MODE)
        {
            /*if non-wbc isogeny mode, enable  do not make limit.*/
            return HI_TRUE;
        }
        else
        {
            if ((bEnable) && (u32WinEnableNum > 0))
            {
                /*if enable, only in condition:  more than 1 window enabled. */
                return HI_TRUE;
            }
            else if ((!bEnable) && (u32WinEnableNum == 0))
            {
                /*if disabled, only in condition:  all the window disabled. */
                return HI_TRUE;
            }

            return HI_FALSE;
        }
    }

}

HI_S32 WIN_SetEnable_Seperate(WINDOW_S *pstWin, HI_BOOL bEnable)
{
    HI_S32 ret = HI_SUCCESS;
    WINDOW_S *pstWinTmp = HI_NULL;
    HI_DISP_DISPLAY_INFO_S stDispInfo;
    HI_SIZE_T irqflag = 0;

    /*if isogeny wbc mode, and slave window, we should give a refcnt increase.*/
    if (HI_FALSE == WIN_Judge_WhetherCanSetEnable(pstWin, bEnable))
    {
        return HI_SUCCESS;
    }

    memset((void *)&stDispInfo, 0, sizeof(HI_DISP_DISPLAY_INFO_S));
    pstWinTmp = (WINDOW_S *) DISP_MALLOC(sizeof(WINDOW_S));
    if (!pstWinTmp)
    {
        WIN_ERROR("malloc failed\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    *pstWinTmp = *pstWin;
    pstWinTmp->bEnable =  bEnable;

    ret = DISP_GetDisplayInfo(pstWin->enDisp, &stDispInfo);
    if (ret)
    {
        stDispInfo.stFmtResolution.s32X = 0;
        stDispInfo.stFmtResolution.s32Y = 0;
        stDispInfo.stFmtResolution.s32Width = 1280;
        stDispInfo.stFmtResolution.s32Height = 720;
        memset((void *)&stDispInfo.stOffsetInfo, 0, sizeof(HI_DRV_DISP_OFFSET_S));
        WIN_WARN("when call set_enable, may ctrl+c, display closed\n");
    }

    /* when enable,may cause win-layer remapping.*/
    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);
    ret =  WindowRedistributeProcess(pstWinTmp);
    if (ret)
    {
        spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
        DISP_FREE(pstWinTmp);
        return ret;
    }

    pstWin->bEnable = bEnable;
    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);

    (HI_VOID)WindowRedistributeProcess_Wait(pstWinTmp, HI_FALSE);

    DISP_FREE(pstWinTmp);
    return HI_SUCCESS;
}

HI_S32 WIN_SetEnable(HI_HANDLE hWin, HI_BOOL bEnable)
{
    WINDOW_S *pstWin = HI_NULL, *pstSlvWin = HI_NULL;
    HI_BOOL bVirtual;
    HI_S32 ret = HI_SUCCESS;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        /*if window has opened, return hi_success.*/
        if (pstWin->bEnable == bEnable)
        {
            return HI_SUCCESS;
        }

        if ((ret = WIN_SetEnable_Seperate(pstWin, bEnable)))
        {
            WIN_ERROR("main window enable error:%x\n", ret);
            return ret;
        }

        if ((HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == WinGetType(pstWin))
            && (pstWin->hSlvWin))
        {
            WinCheckWindow(pstWin->hSlvWin, pstSlvWin);
            if ((ret = WIN_SetEnable_Seperate(pstSlvWin, bEnable)))
            {
                WIN_ERROR("slave window enable error:%x\n", ret);
                return ret;
            }
        }

        /*wait for v0/v3/wbc closed indeed.*/
        if (bEnable == HI_FALSE)
        {
            (HI_VOID)Win_WaitForLayerClosed(pstWin);
            /* wait status of win change,otherwise may cause green screen issue when quit sample. */
        }
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        WinCheckVirWindow(hWin, pstVirWindow);
        pstVirWindow->bEnable = bEnable;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_GetEnable(HI_HANDLE hWin, HI_BOOL *pbEnable)
{
    WINDOW_S *pstWin;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pbEnable);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        *pbEnable = pstWin->bEnable;
    }
    else
    {
        VIRTUAL_S *pstVirWindow;

        WinCheckVirWindow(hWin, pstVirWindow);

        *pbEnable = pstVirWindow->bEnable;

    }
    return HI_SUCCESS;
}



#define WIN_PROCESS_CALC_TIME_THRESHOLD 10
#define WIN_DELAY_TIME_MAX_CIRCLE 50
HI_S32 WIN_CalcDelayTime(WINDOW_S *pstWin, HI_U32 *pu32BufNum, HI_U32 *pu32DelayMs)
{
    HI_U32 u32Num, u32NumNew, T, Dt, Ct, LstCt, Delay;
    HI_U32 L = 0;

__WIN_CALC_DELAY__:
    L++;
    if (L > WIN_PROCESS_CALC_TIME_THRESHOLD)
    {
        goto __WIN_CALC_DELAY_ERROR__;
    }

    LstCt = pstWin->stDelayInfo.u32CfgTime;
    T = pstWin->stDelayInfo.T;

    WinBuf_GetFullBufNum(&pstWin->stBuffer.stWinBP, &u32Num);
    Dt = pstWin->stDelayInfo.u32DisplayTime;

    if (HI_DRV_SYS_GetTimeStampMs(&Ct))
    {
        DISP_ERROR("get sys time failed, not init.\n");
        return HI_FAILURE;
    }

    if (Ct >= LstCt)
    {
        Delay = Ct - LstCt;
    }
    else
    {
        // circle happen, Ct across zero
        Delay = 0xFFFFFFFFul - LstCt + Ct;
    }

    if (T <= (Dt + Delay))
    {
        if (((u32Num + 1) * T) < (Dt + Delay - T))
        {
            /*when fmt changed, may come into this branch .
              *since  isr func not executed, the delay time may be too long.
              * so we just give a basic value,  not  accurate.
              */
            Delay = (u32Num + 1) * T;
        }
        else
        {
            Delay = (u32Num + 1) * T - (Dt + Delay - T) ;
        }
    }
    else
    {
        Delay = T - Dt - Delay;
        Delay = (u32Num + 1) * T + Delay;
    }


    WinBuf_GetFullBufNum(&pstWin->stBuffer.stWinBP, &u32NumNew);
    if (  (LstCt != pstWin->stDelayInfo.u32CfgTime)
          || (u32NumNew != u32Num)
          || (HI_TRUE == pstWin->bInInterrupt)
       )
    {
        udelay(100);
        goto __WIN_CALC_DELAY__;
    }

    if (Delay > (T * WIN_DELAY_TIME_MAX_CIRCLE))
    {
        //DISP_ASSERT(!Delay);
        goto __WIN_CALC_DELAY_ERROR__;
    }

    *pu32BufNum = u32Num;
    *pu32DelayMs = Delay;
    return HI_SUCCESS;

__WIN_CALC_DELAY_ERROR__:

    *pu32BufNum = 0;
    *pu32DelayMs = 0;

    return HI_SUCCESS;
}

HI_S32 WIN_GetPlayInfo(HI_HANDLE hWin, HI_DRV_WIN_PLAY_INFO_S *pstInfo)
{
    WINDOW_S *pstWin;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstInfo);
    WinCheckWindow(hWin, pstWin);

    if (!pstWin->bEnable || !pstWin->stDelayInfo.u32DispRate)
    {
        WIN_WARN("window is not ready! state:%d dispRate:%d\n",
                 pstWin->bEnable,
                 pstWin->stDelayInfo.u32DispRate);
        return HI_ERR_VO_INVALID_OPT;
    }


    WIN_CalcDelayTime(pstWin, &(pstInfo->u32FrameNumInBufQn), &(pstInfo->u32DelayTime));
    pstInfo->u32DispRate = pstWin->stDelayInfo.u32DispRate;
    pstInfo->u32UnderLoad = pstWin->stBuffer.u32UnderLoad;

    return HI_SUCCESS;
}

HI_S32 WinPutNewFrameIntoBufNode(WB_POOL_S *pstWinBP,
                                 WIN_XDR_FRAME_S *pstWinXdrFrm,
                                 HI_U32  u32PlayCnt)
{
    HI_S32  nRet = HI_SUCCESS;

    WinCheckNullPointer(pstWinBP);
    WinCheckNullPointer(pstWinXdrFrm);

    nRet = WinBuf_PutNewHdrFrame(pstWinBP, pstWinXdrFrm, u32PlayCnt);

    return nRet;
}

HI_S32 WinStatisticLowdelayTimeInfor(HI_HANDLE hWin,
                                     HI_DRV_VIDEO_FRAME_S *pFrameInfo,
                                     HI_LD_Event_ID_E eLDEventId)
{
    WINDOW_S *pstWin = HI_NULL;

    WinCheckWindow(hWin, pstWin);

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE
        || pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        HI_LD_Event_S evt = {0};
        HI_U32 TmpTime = 0;

        if (((EVENT_VO_FRM_IN == eLDEventId) && (pFrameInfo->u32FrameIndex == pstWin->u32LastInLowDelayIdx))
            ||  ((EVENT_VO_FRM_OUT == eLDEventId) && (pFrameInfo->u32FrameIndex == pstWin->u32LastOutLowDelayIdx)))
        {
            return HI_SUCCESS;
        }

        if (HI_DRV_SYS_GetTimeStampMs(&TmpTime))
        {
            DISP_ERROR("get sys time defeated, not init.\n");
            return HI_FAILURE;
        }

        evt.evt_id = eLDEventId;
        evt.frame = pFrameInfo->u32FrameIndex;
        evt.handle = pFrameInfo->hTunnelSrc;
        evt.time = TmpTime;
        HI_DRV_LD_Notify_Event(&evt);

        if (EVENT_VO_FRM_IN == eLDEventId)
        {
            pstWin->u32LastInLowDelayIdx = pFrameInfo->u32FrameIndex;
        }
        else if (EVENT_VO_FRM_OUT == eLDEventId)
        {
            pstWin->u32LastOutLowDelayIdx = pFrameInfo->u32FrameIndex;
        }

    }

    return HI_SUCCESS;
}

HI_S32 WinQueueFrame(HI_HANDLE hWin, WIN_XDR_FRAME_S *pstWinXdrFrm)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;
    HI_DRV_VIDEO_FRAME_S *pFrameInfo = HI_NULL;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstWinXdrFrm);

    pFrameInfo = &pstWinXdrFrm->stBaseFrm;
    if (HI_DRV_VIDEO_FRAME_TYPE_BUTT <= pFrameInfo->enSrcFrameType)
    {
        WIN_ERROR("Invalid Frame Type!\n");
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    nRet = WinCheckFrame(pFrameInfo);
    if (nRet)
    {
        WIN_ERROR("win frame parameters invalid\n");
        return HI_ERR_VO_FRAME_INFO_ERROR;
    }

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        /*statistics the frame input time */
        if (HI_SUCCESS != WinStatisticLowdelayTimeInfor(hWin, pFrameInfo, EVENT_VO_FRM_IN))
        {
            WIN_ERROR("Update Window lowdelay time failed\n");
        }

        if (HI_DRV_SYS_GetTimeStampMs(&(pFrameInfo->stLowdelayStat.u32WinGetFrameTime)))
        {
            DISP_ERROR("get sys time failed, not init.\n");
            return HI_FAILURE;
        }

        pFrameInfo->stLowdelayStat.u32WinConfigTime = 0;

        if (pstWin->bEnable == HI_TRUE)
        {
            HI_U32 u32PlayCnt = 0;

            DRV_WIN_GetFramePlayCounts(pstWin->bQuickMode,
                                       pstWin->hFrc,
                                       pFrameInfo->u32FrameRate / 10,
                                       pstWin->stDispInfo.u32RefreshRate,
                                       &u32PlayCnt,
                                       &pstWin->stWinDebugInfo.stFRC);

            if (pFrameInfo->u32FrameRate / 10 != pstWin->stDispInfo.u32RefreshRate)
            {
                pFrameInfo->u32OriFrameRate = pFrameInfo->u32FrameRate;
                pFrameInfo->u32FrameRate = pstWin->stDispInfo.u32RefreshRate * 10;
            }

            if (u32PlayCnt)
            {
                nRet = WinPutNewFrameIntoBufNode(&pstWin->stBuffer.stWinBP,
                                                 pstWinXdrFrm,
                                                 u32PlayCnt);
            }
            else
            {
                nRet = WinBufferPutULSFrame(&pstWin->stBuffer, pFrameInfo);
            }

            if (nRet)
            {
                return HI_ERR_VO_BUFQUE_FULL;
            }
        }
        else
        {
            WIN_WARN("Window is disabled\n");
            return HI_ERR_VO_WIN_NOT_ENABLE;
        }
    }
    else
    {
        VIRTUAL_S *pstVirWin = HI_NULL;
        WinCheckVirWindow(hWin, pstVirWin);

        // update sink acquire frame count
        pstVirWin->stFrameStat.u32SrcQTry++;

        nRet = WIN_VIR_AddNewFrm(pstVirWin, pFrameInfo);
        if (nRet)
        {
            return HI_ERR_VO_BUFQUE_FULL;
        }

        pstVirWin->stFrameStat.u32SrcQOK++;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_QueueFrame(HI_HANDLE hWin, WIN_XDR_FRAME_S *pstWinXdrFrm)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    WinCheckNullPointer(pstWinXdrFrm);
    pstWinXdrFrm->stBaseFrm.u32StillFrame = HI_DRV_FRAME_NORMAL;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)&pstWinXdrFrm->stBaseFrm.u32Priv[0];
    /*if come into this func , means non-fence mode.*/
    pstPriv->bForFenceUse = HI_FALSE;

    return WinQueueFrame(hWin, pstWinXdrFrm);
}

HI_S32 WIN_QueueSyncFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo, HI_U32 *pu32FenceFd)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    WinCheckNullPointer(pFrameInfo);
    WinCheckNullPointer(pu32FenceFd);

    pFrameInfo->u32StillFrame =  HI_DRV_FRAME_NORMAL;
    pFrameInfo->enFieldMode = HI_DRV_FIELD_ALL;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pFrameInfo->u32Priv;
    pstPriv->eOriginField = HI_DRV_FIELD_ALL;
    pstPriv->bForFenceUse = HI_TRUE;

    if (HI_DRV_SYS_GetTimeStampMs(&(pFrameInfo->stLowdelayStat.u32WinGetFrameTime)))
    {
        DISP_ERROR("get sys time failed, not init.\n");
        return HI_FAILURE;
    }

#ifdef HI_VO_WIN_SYNC_SUPPORT
    s32Ret = WIN_Sync_QueueFrame(hWin, pFrameInfo, pu32FenceFd);
#endif

    return s32Ret;
}

HI_S32 WIN_QueueUselessFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pFrameInfo);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        nRet = WinCheckFrame(pFrameInfo);
        if (nRet)
        {
            WIN_ERROR("win frame parameters invalid\n");
            return HI_ERR_VO_FRAME_INFO_ERROR;
        }

        if (pstWin->bEnable == HI_TRUE)
        {
            nRet = WinBufferPutULSFrame(&pstWin->stBuffer, pFrameInfo);
            if (nRet)
            {
                WIN_WARN("quls failed\n");
                return HI_ERR_VO_BUFQUE_FULL;
            }
        }
        else
        {
            WIN_ERROR("Window is disabled\n");
            return HI_ERR_VO_INVALID_OPT;
        }
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        WinCheckVirWindow(hWin, pstVirWindow);

        nRet = WinCheckFrame(pFrameInfo);
        if (nRet)
        {
            WIN_ERROR("win frame parameters invalid\n");
            return HI_ERR_VO_FRAME_INFO_ERROR;
        }

        nRet = WIN_VIR_AddUlsFrm(pstVirWindow, pFrameInfo);
        if (nRet)
        {
            WIN_WARN("quls failed\n");
            return HI_ERR_VO_BUFQUE_FULL;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_DequeueFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo)
{
    HI_S32 nRet = HI_FAILURE;
    WINDOW_S *pstWin;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pFrameInfo);
    WinCheckWindow(hWin, pstWin);

    nRet = Win_Dequeue_DisplayedFrame(hWin, pFrameInfo);

    return nRet;
}

HI_S32 WIN_SetZorder(HI_HANDLE hWin, HI_DRV_DISP_ZORDER_E enZFlag)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();

    if (enZFlag >= HI_DRV_DISP_ZORDER_BUTT)
    {
        WIN_FATAL("HI_DRV_DISP_ZORDER_E invalid!\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);
        DispCheckID(pstWin->enDisp);

        switch (enZFlag)
        {
            case HI_DRV_DISP_ZORDER_MOVETOP:
                nRet = WinZorderMoveTop(pstWin);
                break;
            case HI_DRV_DISP_ZORDER_MOVEUP:
                nRet = WinZorderMoveUp(pstWin);
                break;
            case HI_DRV_DISP_ZORDER_MOVEBOTTOM:
                nRet = WinZorderMoveBottom(pstWin);
                break;
            case HI_DRV_DISP_ZORDER_MOVEDOWN:
                nRet = WinZorderMoveDown(pstWin);
                break;
            default :
                nRet = HI_ERR_VO_INVALID_OPT;
                break;
        }
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return nRet;
}

HI_S32 WIN_GetZorder(HI_HANDLE hWin, HI_U32 *pu32Zorder)
{
    WINDOW_S *pstWin;
    HI_S32 nRet = HI_SUCCESS;
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    WinCheckNullPointer(pu32Zorder);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        *pu32Zorder = pstWin->u32Zorder;
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return nRet;
}
HI_S32 WIN_Freeze(HI_HANDLE hWin, HI_BOOL bEnable, HI_DRV_WIN_SWITCH_E enFrz)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_BOOL bVirtual;
    HI_S32 s32Ret = HI_FAILURE;
    WIN_CMD_PARA_S stWinCMDPara;
    WIN_STATE_E enState = WIN_STATE_WORK;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);

        if (enFrz >= HI_DRV_WIN_SWITCH_BUTT)
        {
            WIN_ERROR("Freeze mode is invalid!\n");
            return HI_ERR_VO_INVALID_PARA;
        }

        if (bEnable)
        {
            pstWin->stFrz.enFreezeMode = enFrz;
        }
        else
        {
            pstWin->stFrz.enFreezeMode = HI_DRV_WIN_SWITCH_BUTT;
        }

        memset(&stWinCMDPara, 0x0, sizeof(WIN_CMD_PARA_S));
        enState =  bEnable ? WIN_STATE_FREEZE : WIN_STATE_UNFREEZE;
        stWinCMDPara.enWinCMD = DRV_WIN_CMD_FREEZE;
        stWinCMDPara.u32Args[0] = (HI_U32)enState;
        stWinCMDPara.u32Args[1] = (HI_U32)enFrz;
        s32Ret = WIN_QUEUE_AddCMD(&pstWin->ListHead, &pstWin->Spin, &stWinCMDPara);
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return s32Ret;
}

HI_S32 WIN_GetFreezeStatus(HI_HANDLE hWin, HI_BOOL *pbEnable, HI_DRV_WIN_SWITCH_E *penFrz)
{
    WINDOW_S *pstWin;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();
    WinCheckNullPointer(penFrz);
    WinCheckNullPointer(pbEnable);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        *pbEnable = (pstWin->enStateNew == WIN_STATE_FREEZE) ? HI_TRUE : HI_FALSE;
        *penFrz = pstWin->stFrz.enFreezeMode;
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return HI_SUCCESS;
}


HI_S32 WIN_ResetSeperate(HI_HANDLE hWin, HI_DRV_WIN_SWITCH_E enRst)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;
    HI_BOOL bVirtual;
    WIN_CMD_PARA_S stWinCMDPara;
    HI_S32  s32Ret = HI_SUCCESS;

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        /*in wbc mode, the slave window does not need to be reset.*/
        if ((pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE)
            && (stDispWindow.eIsogeny_mode == ISOGENY_WBC_MODE))
        {
            return HI_SUCCESS;
        }

        if ((HI_FALSE == pstWin->bEnable) && (HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST == pstWin->stRst.enResetMode))
        {
            WIN_ERROR("Invalid opt, can't display still frame when window disabled.\n");
            return HI_ERR_VO_INVALID_OPT;
        }

        if (pstWin->bEnable)
        {
            pstWin->stRst.enResetMode = enRst;
            //pstWin->bReset = HI_TRUE;
            memset(&stWinCMDPara, 0x0, sizeof(WIN_CMD_PARA_S));
            stWinCMDPara.enWinCMD = DRV_WIN_CMD_RESET;
            stWinCMDPara.u32Args[0] = (HI_U32)enRst;
            s32Ret = WIN_QUEUE_AddCMD(&pstWin->ListHead, &pstWin->Spin, &stWinCMDPara);

            /*just for  test, when upload to git repo, just rebuild it.*/
            if (HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST == pstWin->stRst.enResetMode)
            {
                msleep(40);
            }
        }
        else
        {
            (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
            ISR_WinReleaseUSLFrame(pstWin);
            (HI_VOID)WinBuf_DiscardDisplayedFrame(&pstWin->stBuffer.stWinBP);

            /* flush frame in full buffer pool */
            pstFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);

#ifdef HI_VO_WIN_SYNC_SUPPORT
            (HI_VOID)WIN_Sync_Reset(hWin, enRst, pstFrame);
#endif

            WinBuf_FlushWaitingFrame(&pstWin->stBuffer.stWinBP, pstFrame);
            pstWin->bReset = HI_FALSE;
            pstWin->enStateNew = WIN_STATE_WORK;
            pstWin->enState = WIN_STATE_WORK;

            WinBuf_RetAllMemRefCnts();
        }
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        HI_S32 s32Ret;

        WinCheckVirWindow(hWin, pstVirWindow);

        s32Ret = WIN_VIR_Reset(pstVirWindow);
        if (HI_SUCCESS != s32Ret)
        {
            WIN_ERROR("Reset Virtual Window Failed\n");
            return s32Ret;
        }
    }
    return HI_SUCCESS;
}


HI_S32 WIN_Reset(HI_HANDLE hWin, HI_DRV_WIN_SWITCH_E enRst)
{
    WINDOW_S *pstWin = HI_NULL, *pstWinSlv = HI_NULL;
    HI_BOOL bVirtual;
    HI_S32  ret = 0;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);
        if (enRst >= HI_DRV_WIN_SWITCH_BUTT)
        {
            WIN_ERROR("Reset mode is invalid!\n");
            return HI_ERR_VO_INVALID_PARA;
        }

        if (HI_SUCCESS != (ret = WIN_ResetSeperate(hWin, enRst)))
        {
            return ret;
        }

        /*now we do main and slave window reset in drv, not in mpi/unf level.*/
        if (pstWin->hSlvWin)
        {
            WinCheckWindow(pstWin->hSlvWin, pstWinSlv);

            if ((ret = WIN_ResetSeperate(pstWin->hSlvWin, enRst)))
            {
                return ret;
            }
        }
    }
    else
    {
        return WIN_ResetSeperate(hWin, enRst);
    }

    return HI_SUCCESS;
}


HI_S32 WIN_Pause(HI_HANDLE hWin, HI_BOOL bEnable)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_BOOL bVirtual;
    WIN_STATE_E enState = WIN_STATE_WORK;
    HI_S32 s32Ret = HI_FAILURE;
    WIN_CMD_PARA_S stWinCMDPara;
    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);

        memset(&stWinCMDPara, 0x0, sizeof(WIN_CMD_PARA_S));
        enState = bEnable ? WIN_STATE_PAUSE : WIN_STATE_RESUME;
        stWinCMDPara.enWinCMD = DRV_WIN_CMD_PAUSE;
        stWinCMDPara.u32Args[0] = (HI_U32)enState;
        s32Ret = WIN_QUEUE_AddCMD(&pstWin->ListHead, &pstWin->Spin, &stWinCMDPara);
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return s32Ret;
}

HI_S32 WIN_SetStepMode(HI_HANDLE hWin, HI_BOOL bStepMode)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);

        // s2 set enable
        if (pstWin->bUpState && pstWin->bEnable)
        {
            WIN_ERROR("Window is changing, can't set pause now!\n");
            return HI_ERR_VO_INVALID_OPT;
        }

        // set stepmode flag
        pstWin->bStepMode = bStepMode;
    }
    else
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_SetStepPlay(HI_HANDLE hWin)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_BOOL bVirtual;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);
        pstWin->bStepPlayNext = HI_TRUE;
    }
    else
    {
        WIN_ERROR("StepPlay Unsupport virtual window!\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_SetQuick(HI_HANDLE hWin, HI_BOOL bEnable)
{
    WINDOW_S *pstWin;
    HI_BOOL bVirtual = HI_FALSE;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        // s1 ������Ϸ���
        WinCheckWindow(hWin, pstWin);

        // initial quickmode
        pstWin->bQuickMode = bEnable;
    }
    else
    {
        WIN_ERROR("SetQuick unsupported for virtual window!\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return HI_SUCCESS;
}

HI_S32 WIN_GetQuick(HI_HANDLE hWin, HI_BOOL *pbEnable)
{
    WINDOW_S *pstWin;
    HI_BOOL  bVirtual = HI_FALSE;

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckDeviceOpen();
        WinCheckWindow(hWin, pstWin);

        // initial quickmode
        *pbEnable = pstWin->bQuickMode;
    }
    else
    {
        WIN_ERROR("GetQuick unsupported for virtual window!\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    return HI_SUCCESS;
}

/* only for virtual window */
HI_S32 WIN_SetExtBuffer(HI_HANDLE hWin, HI_DRV_VIDEO_BUFFER_POOL_S *pstBuf)
{
    return HI_ERR_VO_WIN_UNSUPPORT;
}

HI_S32 WIN_AttachSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    VIRTUAL_S *pstVirWin;
    HI_S32 s32Ret;

    WinCheckVirWindow(hWin, pstVirWin);

    s32Ret = WIN_VIR_AttachSink(pstVirWin, hSink);

    return s32Ret;
}

HI_S32 WIN_DetachSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    VIRTUAL_S *pstVirWin;
    HI_S32 s32Ret;

    WinCheckVirWindow(hWin, pstVirWin);

    s32Ret = WIN_VIR_DetachSink(pstVirWin, hSink);

    return s32Ret;
}

HI_S32 WIN_SetVirtualAttr(HI_HANDLE hWin,
                          HI_U32 u32Width,
                          HI_U32 u32Height,
                          HI_U32 u32FrmRate)
{
    VIRTUAL_S *pstVirWin;
    HI_S32 s32Ret;

    WinCheckVirWindow(hWin, pstVirWin);

    s32Ret = WIN_VIR_SetSize(pstVirWin, u32Width, u32Height);
    if (HI_SUCCESS != s32Ret)
    {
        WIN_ERROR("Invalid setting size of virtual window.!\n");
        return s32Ret;
    }

    s32Ret = WIN_VIR_SetFrmRate(pstVirWin, u32FrmRate);
    if (HI_SUCCESS != s32Ret)
    {
        WIN_ERROR("Invalid setting size of virtual window.!\n");
    }

    return s32Ret;
}

HI_S32 WIN_AcquireFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    VIRTUAL_S *pstVirWin;
    HI_S32 s32Ret;

    WinCheckVirWindow(hWin, pstVirWin);

    s32Ret = WIN_VIR_GetFrm(pstVirWin, pFrameinfo);
    // update sink acquire frame count
    pstVirWin->stFrameStat.u32SinkAcqTry++;
    if (s32Ret == HI_SUCCESS)
    {
        pstVirWin->stFrameStat.u32SinkAcqOK++;
    }

    return s32Ret;
}

HI_S32 WIN_ReleaseFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    VIRTUAL_S *pstVirWin;
    HI_S32 s32Ret;

    WinCheckVirWindow(hWin, pstVirWin);
    WinCheckNullPointer(pFrameinfo);

    s32Ret = WIN_VIR_RelFrm(pstVirWin, pFrameinfo);

    //update sink release frame count
    pstVirWin->stFrameStat.u32SinkRlsTry++;
    if (s32Ret == HI_SUCCESS)
    {
        pstVirWin->stFrameStat.u32SinkRlsOK++;
    }

    return s32Ret;
}

HI_S32 WIN_CreatStillFrame(HI_DRV_VIDEO_FRAME_S *pFrameinfo, HI_DRV_VIDEO_FRAME_S *pStillFrameInfo)
{
    HI_VDEC_PRIV_FRAMEINFO_S *pstPrivInfo = HI_NULL;
    HI_U32 datalen = 0, y_stride = 0, height = 0 ;
    DISP_MMZ_BUF_S    stMMZ_StillFrame;
    DISP_MMZ_BUF_S    stMMZ_Frame;
    HI_S32            nRet = 0;
    HI_BOOL  bUvorder = HI_FALSE;
    HI_BOOL  bCmpFmt = HI_FALSE;
    HI_BOOL  bLostCmp = HI_FALSE;

    pstPrivInfo = (HI_VDEC_PRIV_FRAMEINFO_S *)(pFrameinfo->u32Priv);

    memset(&stMMZ_StillFrame, 0, sizeof(stMMZ_StillFrame));
    memset(&stMMZ_Frame, 0, sizeof(stMMZ_Frame));

    /*1:calculate alloc mem*/
    y_stride = pFrameinfo->stBufAddr[0].u32Stride_Y;
    height     = (HI_TRUE == pstPrivInfo->stCompressInfo.u32CompressFlag)
                 ? pstPrivInfo->stCompressInfo.s32CompFrameHeight : pFrameinfo->u32Height;

    if ( HI_DRV_PIX_FMT_NV21 == pFrameinfo->ePixFormat)
    {
        datalen = height * y_stride * 3 / 2 ;
    }
    else
    {
        datalen = height * y_stride * 2 ;
    }


    if (HI_SUCCESS != DISP_OS_MMZ_Alloc("VDP_StillFrame", VDP_MEM_TYPE_MMZ, datalen, VDP_MEM_ALIGN, &stMMZ_StillFrame))
    {
        WIN_ERROR(" Alloc StillFrame  failid(%x)\n", datalen);
        return HI_ERR_VO_MALLOC_FAILED;
    }

    /*2: creat still frame*/
    /*not support  Compress info*/
    stMMZ_Frame.u32StartPhyAddr = pFrameinfo->stBufAddr[0].u32PhyAddr_Y;

#ifdef  CFG_VDP_MMU_SUPPORT
    stMMZ_Frame.bSmmu = HI_TRUE;
#else
    stMMZ_Frame.bSmmu = HI_FALSE;
#endif
    stMMZ_Frame.u32Size = datalen;

#ifdef  CFG_VDP_MMU_SUPPORT
    stMMZ_StillFrame.bSmmu = HI_TRUE;
#else
    stMMZ_StillFrame.bSmmu = HI_FALSE;
#endif

    stMMZ_StillFrame.u32Size = datalen;

    nRet = DISP_OS_MMZ_Map(&stMMZ_StillFrame);
    if (HI_SUCCESS != nRet)
    {
        goto __FAILURE_RELEASE;
    }

    nRet = DISP_OS_MMZ_Map(&stMMZ_Frame);
    if (HI_SUCCESS != nRet)
    {
        goto __EXIT_UNMAP;
    }


    memcpy(pStillFrameInfo, pFrameinfo, sizeof(HI_DRV_VIDEO_FRAME_S));
    memcpy((void *)stMMZ_StillFrame.pu8StartVirAddr, (void *)stMMZ_Frame.pu8StartVirAddr, datalen);

    JudgeCmpAndUvorderByPixFormat(pFrameinfo->ePixFormat, &bUvorder, &bCmpFmt, &bLostCmp);

    /*3: calculate still frame addr*/
    if (HI_FALSE == bCmpFmt)
    {
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_YHead = HI_NULL;
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_Y = stMMZ_StillFrame.u32StartPhyAddr;
        pStillFrameInfo->stBufAddr[0].u32Stride_Y =  pFrameinfo->stBufAddr[0].u32Stride_Y;
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_C = stMMZ_StillFrame.u32StartPhyAddr + (pStillFrameInfo->u32Height * pStillFrameInfo->stBufAddr[0].u32Stride_Y);
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_CrHead = stMMZ_StillFrame.u32StartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_CrHead - stMMZ_Frame.u32StartPhyAddr);
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_Cr = stMMZ_StillFrame.u32StartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_Cr - stMMZ_Frame.u32StartPhyAddr );
        pStillFrameInfo->stBufAddr[0].u32Stride_Cr = pFrameinfo->stBufAddr[0].u32Stride_Cr;
    }
    else
    {
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_YHead = stMMZ_StillFrame.u32StartPhyAddr;
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_Y = HI_NULL;
        pStillFrameInfo->stBufAddr[0].u32Stride_Y =  pFrameinfo->stBufAddr[0].u32Stride_Y;
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_C = stMMZ_StillFrame.u32StartPhyAddr + (pStillFrameInfo->u32Height * pStillFrameInfo->stBufAddr[0].u32Stride_Y);
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_CrHead = stMMZ_StillFrame.u32StartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_CrHead - stMMZ_Frame.u32StartPhyAddr);
        pStillFrameInfo->stBufAddr[0].u32PhyAddr_Cr = stMMZ_StillFrame.u32StartPhyAddr + ( pFrameinfo->stBufAddr[0].u32PhyAddr_Cr - stMMZ_Frame.u32StartPhyAddr );
        pStillFrameInfo->stBufAddr[0].u32Stride_Cr = pFrameinfo->stBufAddr[0].u32Stride_Cr;
    }

    pStillFrameInfo->u32StillFrame = HI_DRV_FRAME_VDP_ALLOCATE_STILL;

    DISP_OS_MMZ_UnMap(&stMMZ_StillFrame);
    DISP_OS_MMZ_UnMap(&stMMZ_Frame);

    return HI_SUCCESS;

__EXIT_UNMAP:
    DISP_OS_MMZ_UnMap(&stMMZ_StillFrame);

__FAILURE_RELEASE:
    DISP_OS_MMZ_Release(&stMMZ_StillFrame);
    return nRet;
}

HI_S32 DestroyStillFrame(HI_DRV_VIDEO_FRAME_S *pStillFrameInfo)
{
    DISP_MMZ_BUF_S    stMMZ_StillFrame = {0};
    HI_BOOL  bUvorder = HI_FALSE;
    HI_BOOL  bCmpFmt = HI_FALSE;
    HI_BOOL  bLostCmp = HI_FALSE;

    WinCheckNullPointer(pStillFrameInfo);

    if (HI_DRV_FRAME_VDP_ALLOCATE_STILL == pStillFrameInfo->u32StillFrame)
    {
        memset((void *)&stMMZ_StillFrame, 0, sizeof(stMMZ_StillFrame));

        JudgeCmpAndUvorderByPixFormat(pStillFrameInfo->ePixFormat, &bUvorder, &bCmpFmt, &bLostCmp);
        if (HI_TRUE == bCmpFmt)
        {
            stMMZ_StillFrame.u32StartPhyAddr = pStillFrameInfo->stBufAddr[0].u32PhyAddr_YHead;
        }
        else
        {
            stMMZ_StillFrame.u32StartPhyAddr = pStillFrameInfo->stBufAddr[0].u32PhyAddr_Y;
        }

#ifdef  CFG_VDP_MMU_SUPPORT
        stMMZ_StillFrame.bSmmu = HI_TRUE;
#else
        stMMZ_StillFrame.bSmmu = HI_FALSE;
#endif

        stMMZ_StillFrame.bSecure = pStillFrameInfo->bSecure;
        DISP_OS_MMZ_Release(&stMMZ_StillFrame);
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 WIN_SendFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    WIN_XDR_FRAME_S *pstWinXdrFrm = HI_NULL;

    WinCheckNullPointer(pFrameInfo);

    /* malloc buff to load frame. */
    pstWinXdrFrm = (WIN_XDR_FRAME_S *)HI_KMALLOC(HI_ID_VO, sizeof(WIN_XDR_FRAME_S), GFP_KERNEL);
    if (HI_NULL == pstWinXdrFrm)
    {
        HI_ERR_WIN("Malloc pstWinXdrFrm failed.\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    s32Ret = WIN_CreatStillFrame(pFrameInfo, &pstWinXdrFrm->stBaseFrm);
    if ( HI_SUCCESS != s32Ret )
    {
        WIN_ERROR(" WIN_CreatStillFrame  failid(%x)\n", s32Ret);
        HI_KFREE(HI_ID_VO, pstWinXdrFrm);
        return s32Ret;
    }

    pstWinXdrFrm->hWindow = hWin;
    pstWinXdrFrm->enXdrEngine = DRV_XDR_ENGINE_SDR;

    s32Ret = WIN_POLICY_GetOutputTypeAndEngine(hWin,
             pFrameInfo->enSrcFrameType,
             &pstWinXdrFrm->enDispOutType,
             &pstWinXdrFrm->enXdrEngine);

    if (s32Ret != HI_SUCCESS)
    {
        WIN_ERROR("Get output type fail.\n");
        HI_KFREE(HI_ID_VO, pstWinXdrFrm);
        return s32Ret;
    }

    s32Ret = WinQueueFrame(hWin, pstWinXdrFrm);

    HI_KFREE(HI_ID_VO, pstWinXdrFrm);

    return s32Ret;
}

HI_S32 Win_DebugGetHandle(HI_DRV_DISPLAY_E enDisp, WIN_HANDLE_ARRAY_S *pstWin)
{
    HI_S32 i;

    WinCheckDeviceOpen();

    // s1 ������Ϸ���
    WinCheckNullPointer(pstWin);

    if (enDisp >= HI_DRV_DISPLAY_BUTT)
    {
        WIN_ERROR("enDisp out of range\n");
        return HI_FAILURE;
    }

    DISP_MEMSET(pstWin, 0, sizeof(WIN_HANDLE_ARRAY_S));

    pstWin->u32WinNumber = 0;

    for (i = 0; i < WINDOW_MAX_NUMBER; i++)
    {
        if (stDispWindow.pstWinArray[(HI_U32)enDisp][i])
        {
            pstWin->ahWinHandle[pstWin->u32WinNumber] = (HI_HANDLE)(stDispWindow.pstWinArray[(HI_U32)enDisp][i]->u32Index);
            pstWin->u32WinNumber++;
        }
    }

    return HI_SUCCESS;
}

HI_VOID ISR_WinReleaseUSLFrame(WINDOW_S *pstWin)
{
    HI_DRV_WIN_SRC_INFO_S *pstSource = &pstWin->stCfg.stSource;
    HI_DRV_VIDEO_FRAME_S stRlsFrm = {0};
    HI_S32 nRet;

    if (pstWin->stCfg.stSource.hSrc == (HI_HANDLE)pstWin->u32Index)
    {
        return;
    }

    memset(&stRlsFrm, 0, sizeof(stRlsFrm));
    /* release useless frame */
    nRet = WinBufferGetULSFrame(&pstWin->stBuffer, &stRlsFrm);
    while (HI_SUCCESS == nRet)
    {
        if (HI_DRV_FRAME_VDP_ALLOCATE_STILL == stRlsFrm.u32StillFrame)
        {
            (HI_VOID)WIN_DestroyStillFrame(&stRlsFrm);
        }
        else if (pstSource->pfRlsFrame)
        {
            if ((pstSource->hSecondSrc != HI_INVALID_HANDLE)
                && (HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL == stRlsFrm.enSrcFrameType))
            {
                pstSource->pfRlsFrame(pstSource->hSecondSrc, &stRlsFrm);
            }
            else if (pstSource->hSrc != HI_INVALID_HANDLE)
            {
                pstSource->pfRlsFrame(pstSource->hSrc, &stRlsFrm);
            }
            else
            {
                WIN_ERROR("Cannot Release USL frame,invalid hSrc or FrameType! FrameType %d hSrc %#x\n",
                          stRlsFrm.enSrcFrameType,
                          pstSource->hSrc);
            }
        }

        nRet = WinBufferGetULSFrame(&pstWin->stBuffer, &stRlsFrm);
    }

    return;
}

HI_DRV_VIDEO_FRAME_S *ISR_SlaveWinGetConfigFrame(WINDOW_S *pstWin)
{
    WIN_ERROR("Invalid Code branch\n");

    return HI_NULL;
}


HI_VOID WinUpdateDispInfo(WINDOW_S *pstWin, HI_DISP_DISPLAY_INFO_S *pstDsipInfo)
{
    pstWin->stDispInfo.u32RefreshRate = pstDsipInfo->u32RefreshRate;
    pstWin->stDispInfo.bIsInterlace   = pstDsipInfo->bInterlace;
    pstWin->stDispInfo.bIsBtm          = pstDsipInfo->bIsBottomField;
    pstWin->stDispInfo.stWinCurrentFmt = pstDsipInfo->stFmtResolution;

    return;
}

WIN_DISP_INFO_S *WinGetDispInfoByHandle(HI_HANDLE hWin)
{
    WINDOW_S *pstWin;

    pstWin = WinGetWindow(hWin);

    if (pstWin)
    {
        return &pstWin->stDispInfo;
    }

    return HI_NULL;
}

HI_VOID WinTestFrameMatch(WINDOW_S *pstWin, HI_DRV_VIDEO_FRAME_S *pstFrame, HI_DISP_DISPLAY_INFO_S *pstDsipInfo)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = (HI_DRV_VIDEO_PRIVATE_S *) & (pstFrame->u32Priv[0]);

    if (pstDsipInfo->bInterlace == HI_TRUE)
    {
        if ( ((pstPriv->eOriginField == HI_DRV_FIELD_TOP)
              && (pstDsipInfo->bIsBottomField == HI_FALSE) )
             || ((pstPriv->eOriginField == HI_DRV_FIELD_BOTTOM)
                 && (pstDsipInfo->bIsBottomField == HI_TRUE) )
           )
        {
            pstWin->u32TBNotMatchCount++;
        }
    }

    return;
}
HI_VOID Win_UpdateHdFramInfo(WIN_HAL_PARA_S *pstLayerPara, WIN_CONFIG_S *pstCfg, HI_BOOL bSecure)
{
#ifdef VDP_ISOGENY_SUPPORT
    WBC_HD_WIN_INFOR_S  stHDWinInfo = {0};

    memset((HI_VOID *)&stHDWinInfo, 0, sizeof(stHDWinInfo));

    if ( VDP_LAYER_VID0 == pstLayerPara->u32LayerNO )
    {
        stHDWinInfo.bV0Secure = bSecure;
        stHDWinInfo.bV0Mute = pstLayerPara->bRegionMute;
        stHDWinInfo.bV0RegionEnable = pstLayerPara->bRegionEnable;
        stHDWinInfo.stV0DispRect = pstLayerPara->stDisp;
        stHDWinInfo.stV0VideoRect = pstLayerPara->stVideo;
        stHDWinInfo.stV0InRect = pstLayerPara->stIn;

        stHDWinInfo.enV0WinSrcColorSpace = pstCfg->enFrameCS;
        stHDWinInfo.enV0WinDestColorSpace =  pstCfg->enOutCS;
    }
    else if ( VDP_LAYER_VID1 == pstLayerPara->u32LayerNO )
    {
        stHDWinInfo.bV1Secure = bSecure;
        stHDWinInfo.bV1Mute = pstLayerPara->bRegionMute;
        stHDWinInfo.bV1RegionEnable = pstLayerPara->bRegionEnable;
    }
    else
    {
        /*do nothing\n*/
    }
    stHDWinInfo.u32WinNum = WinGetHDWinNum();

    ISOGENY_UpDateHDWinFramInfo(&stHDWinInfo, pstLayerPara->u32LayerNO);
#endif
    return;
}


HI_VOID WinGetActualOffsetAccordingUserSetting(HI_DRV_DISPLAY_E enDisp,
        HI_DRV_DISP_OFFSET_S  *pstUserSettingOffset,
        HI_DRV_DISP_OFFSET_S  *pstActualOffset,
        HI_RECT_S *pstOutRect)
{
#ifndef HI_VO_OFFSET_EFFECTIVE_WHEN_WIN_FULL
    HI_RECT_S  stCanvas = {0};

    (HI_VOID)DISP_GetVirtScreen(enDisp, &stCanvas);

    if (((pstOutRect->s32Width == 0)
         || (pstOutRect->s32Height == 0))
        || ((pstOutRect->s32Width == stCanvas.s32Width)
            && (pstOutRect->s32Height == stCanvas.s32Height)))
    {
        memset((void *)pstActualOffset, 0, sizeof(HI_DRV_DISP_OFFSET_S));
    }
    else
    {
        *pstActualOffset = *pstUserSettingOffset;
    }

#else
    *pstActualOffset = *pstUserSettingOffset;
#endif

    return;
}

HI_VOID ISR_WinConfigFrameMute(WINDOW_S *pstWin, HI_DRV_VIDEO_FRAME_S *pstFrame, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_WIN_ATTR_S *pstAttr = &pstWin->stUsingAttr;
    WIN_HAL_PARA_S stLayerPara = {0};
    HI_DRV_DISP_OFFSET_S stOffsetRect = {0};
    WIN_INFO_S stWinInfo = {0};
    HI_RECT_S  stFrameIntermediaRect = {0};
    HI_BOOL bSdrChoice = HI_FALSE;

    memset((void *)&stLayerPara, 0, sizeof(stLayerPara));

    stLayerPara.en3Dmode = pstInfo->stDispInfo.eDispMode;
    stLayerPara.bRightEyeFirst = pstInfo->stDispInfo.bRightEyeFirst;

    memset((HI_VOID *)&stLayerPara.stHdcpIntermediateRect, 0, sizeof(HI_RECT_S));
    stLayerPara.bHdcpDegradePQ = HI_FALSE;

    pstWin->stCfg.enOutCS = pstInfo->stDispInfo.eColorSpace;
    stLayerPara.eOutPutColorSpace = pstWin->stCfg.enOutCS;

    /*stOutRect may equal to stIn in most situation.*/
    stLayerPara.stDisp    = pstAttr->stOutRect;
    stLayerPara.stVideo = pstAttr->stOutRect;

    stLayerPara.stIn.s32Width = stLayerPara.stVideo.s32Width;
    stLayerPara.stIn.s32Height = stLayerPara.stVideo.s32Height;

    stLayerPara.pstDispInfo = (HI_DISP_DISPLAY_INFO_S *) & (pstInfo->stDispInfo);
    stLayerPara.u32RegionNum =    pstWin->u32VideoRegionNo;
    stLayerPara.bRegionMute = HI_TRUE;
    stLayerPara.u32LayerNO =    pstWin->u32VideoLayer;
    stLayerPara.bRegionEnable = HI_TRUE;
    stLayerPara.pstDispInfo = (HI_DISP_DISPLAY_INFO_S *) & (pstInfo->stDispInfo);
    stLayerPara.u32Alpha = pstWin->stCfg.u32Alpha;
    stLayerPara.u32AllAlpha = pstInfo->stDispInfo.u32Alpha;


    if (pstWin->bVirtScreenMode == HI_TRUE)
    {
        WinGetActualOffsetAccordingUserSetting(pstWin->enDisp,
                                               &stLayerPara.pstDispInfo->stOffsetInfo,
                                               &stOffsetRect,
                                               &pstWin->stCfg.stAttrBuf.stOutRect);
    }
    else
    {
        memset((void *)&stOffsetRect, 0, sizeof(HI_DRV_DISP_OFFSET_S));
    }


    /*deal with out of  screen scene.*/
    (HI_VOID)Win_Revise_OutOfScreenWin_OutRect(&stLayerPara.stIn,
            &stLayerPara.stVideo,
            &stLayerPara.stDisp,
            &stLayerPara.pstDispInfo->stFmtResolution,
            &stOffsetRect,
            &stLayerPara);

    stFrameIntermediaRect = stLayerPara.stIn;
    /*get intermediate Rect to degrade the PQ  as a matter of TEE monitor.*/
    Win_Policy_GetPQDegradingConfigFromTEE(HI_FALSE,
                                           &stLayerPara.stIn,
                                           &stLayerPara.stVideo,
                                           pstWin->u32VideoLayer,
                                           &stFrameIntermediaRect,
                                           &stLayerPara.bHdcpDegradePQ,
                                           &stLayerPara.stHdcpIntermediateRect);

    stLayerPara.enLayerFrostMode = pstWin->enWinFrostMode;

    if (pstInfo->stDispInfo.enDispProcessMode == HI_DRV_DISP_PROCESS_MODE_SDR)
    {
        /* when last work mode is HDR,go through HDR mute path; otherwise,just go through normal mute path.*/
        bSdrChoice = HI_TRUE;
    }

    Win_PqProcess(pstWin, pstFrame, &stLayerPara.stVideo, &pstInfo->stDispInfo, !bSdrChoice);

    WinTransferConfigInfoToWinShareInfo(pstWin, &stLayerPara, &stWinInfo);

    WIN_SHARE_SetWinInfo(&stWinInfo);

    Win_UpdateHdFramInfo(&stLayerPara, &pstWin->stCfg, HI_FALSE);
    Win_UpWinPosionDebugInfo(pstWin, &stLayerPara);

    return;
}

HI_S32  RWZB_GetDATEParaIndex(HI_S32 u32RwzbType)
{
    HI_U32 u32Index;

    switch (u32RwzbType)
    {
        case FIDELITY_480I_YPBPR:
        case FIDELITY_576I_YPBPR:
            u32Index = 1;
            break;

        case FIDELITY_SKN:
        case FIDELITY_ZDN:
            u32Index = 2;
            break;
        case FIDELITY_MOTO_CVBS:
            u32Index = 3;
            break;
        case FIDELITY_033:
            u32Index = 4;
            break;
        case FIDELITY_MATRIX525:
            u32Index = 5;
            break;


        default:
            u32Index = 0;
            break;
    }
    return u32Index;
}

extern HI_BOOL DISP_IsFollowed(HI_DRV_DISPLAY_E enDisp);

HI_VOID Win_ReviseInRect(HI_RECT_S *pstDstRect, HI_RECT_S *pstSrctRect)
{
    if ((0 == pstDstRect->s32Width) || (0 == pstDstRect->s32Height))
    {
        pstDstRect->s32Width = pstSrctRect->s32Width;
        pstDstRect->s32Height = pstSrctRect->s32Height;
    }

    if ( pstDstRect->s32Width > pstSrctRect->s32Width)
    {
        pstDstRect->s32Width =  pstSrctRect->s32Width;
        //WIN_ERROR("inrect s32Width outof srource rect!");
    }

    if ( pstDstRect->s32Height > pstSrctRect->s32Height)
    {
        pstDstRect->s32Height =  pstSrctRect->s32Height;
        //WIN_ERROR("inrect s32Height outof srource rect!");
    }

    if ( pstDstRect->s32Y > pstSrctRect->s32Height - 64 )
    {
        pstDstRect->s32Y =    pstSrctRect->s32Height - 64;

    }
    if ( pstDstRect->s32X > pstSrctRect->s32Width - 64 )
    {
        pstDstRect->s32X =  pstSrctRect->s32Width - 64;

    }

    if ( (pstDstRect->s32Y + pstDstRect->s32Height) > pstSrctRect->s32Height )
    {
        pstDstRect->s32Height = pstSrctRect->s32Height - pstDstRect->s32Y;
    }

    if ( (pstDstRect->s32X + pstDstRect->s32Width) > pstSrctRect->s32Width )
    {
        pstDstRect->s32Width = pstSrctRect->s32Width - pstDstRect->s32X;
    }

    if ( pstDstRect->s32Width < 64)
    {
        pstDstRect->s32Width = 64;
    }

    if ( pstDstRect->s32Height < 64)
    {
        pstDstRect->s32Height = 64;
    }
}

HI_VOID Win_AspRatioProcess(VDP_ALG_RATIO_DRV_PARA_S *pstAspDrvPara, VDP_ALG_RATIO_OUT_PARA_S *pstAspCfg)
{

    VDP_ALG_RATIO_DRV_PARA_S  stAspCalPara = *pstAspDrvPara;
    HI_S32 sr_w, sr_h;
    HI_S32 in_w, in_h;
    HI_S32 out_x, out_y;

    out_x = pstAspDrvPara->stOutWnd.s32X;
    out_y = pstAspDrvPara->stOutWnd.s32Y;

    pstAspDrvPara->stOutWnd.s32Y = 0;
    pstAspDrvPara->stOutWnd.s32X = 0;

    if (HI_TRUE == pstAspDrvPara->stUsrAsp.bUserDefAspectRatio)
    {
        sr_w = pstAspDrvPara->stUsrAsp.u32UserAspectWidth;
        sr_h = pstAspDrvPara->stUsrAsp.u32UserAspectHeight;
    }
    else
    {
        sr_w = stAspCalPara.AspectWidth;
        sr_h = stAspCalPara.AspectHeight;
    }

    if (0 == pstAspDrvPara->stSrcRect.s32Height || 0 == pstAspDrvPara->stSrcRect.s32Width)
    {
        DISP_ERROR("Denominator may be zero !\n");
        return;
    }

    in_h =  (pstAspDrvPara->stInWnd.s32Height * sr_h) / pstAspDrvPara->stSrcRect.s32Height;
    in_w =  (pstAspDrvPara->stInWnd.s32Width * sr_w) / pstAspDrvPara->stSrcRect.s32Width;

    /*cal src crop rect aspratio!*/
    stAspCalPara.AspectWidth = in_w ;
    stAspCalPara.AspectHeight = in_h;

    VDP_ALG_RATIO_RatioProcess(pstAspDrvPara, pstAspCfg);

    if (pstAspCfg->bEnCrop)
    {
        /*cal inRect */
        pstAspDrvPara->stInWnd.s32X = (pstAspCfg->stCropWnd.s32X * pstAspDrvPara->stSrcRect.s32Width / pstAspCfg->u32ZmeW);
        pstAspDrvPara->stInWnd.s32Width = (pstAspCfg->stCropWnd.s32Width * pstAspDrvPara->stSrcRect.s32Width / pstAspCfg->u32ZmeW);
        pstAspDrvPara->stInWnd.s32Y = (pstAspCfg->stCropWnd.s32Y * pstAspDrvPara->stSrcRect.s32Height / pstAspCfg->u32ZmeH);
        pstAspDrvPara->stInWnd.s32Height = (pstAspCfg->stCropWnd.s32Height * pstAspDrvPara->stSrcRect.s32Height / pstAspCfg->u32ZmeH);

    }

    pstAspCfg->stOutWnd.s32X += out_x;
    pstAspCfg->stOutWnd.s32Y += out_y;

}

extern  S_VDP_REGS_TYPE *g_pstVdpBaseAddr;

HI_S32 Win_PqHdrCfgProcess(WINDOW_S *pstWin,
                           HI_DRV_VIDEO_FRAME_S *pstFrame,
                           const HI_DISP_DISPLAY_INFO_S *pstDispInfo)
{
    HI_PQ_XDR_FRAME_INFO    stPqWinHdrMetaInfo;
    DISP_BUF_NODE_S         *pstConfig = HI_NULL;
    HI_S32                  nRet = HI_SUCCESS;

    if (HI_NULL == pstFrame)
    {
        return HI_SUCCESS;
    }
#ifdef  CFG_HI3798CV200
    if (HI_DRV_VIDEO_FRAME_TYPE_SDR == pstFrame->enSrcFrameType)
    {
        return HI_SUCCESS;
    }
#endif

    if (HI_NULL == pstWin->stBuffer.stWinBP.pstConfig)
    {
        return HI_SUCCESS;
    }

    pstConfig = pstWin->stBuffer.stWinBP.pstConfig;

    memcpy(&stPqWinHdrMetaInfo, pstConfig->u8Pqdata, sizeof(stPqWinHdrMetaInfo));
    stPqWinHdrMetaInfo.stLayerRegionInfo.enPqXdrLayerId = pstWin->u32VideoLayer;
    stPqWinHdrMetaInfo.stLayerRegionInfo.u32WindowNum = WinGetHDWinNum();

    nRet = DRV_PQ_GetHdrCfg(&stPqWinHdrMetaInfo,
                            (HI_PQ_HDR_CFG *)pstConfig->u8Metadata);
    if (nRet != HI_SUCCESS)
    {
        HI_ERR_WIN("Get Hdr config from PQ fail.FrmType->%d,OutType->%d,Ret->%d\n",
                   pstFrame->enSrcFrameType, pstConfig->stHdrInfo.enDispOutType, nRet);
        return nRet;
    }

    return HI_SUCCESS;
}

HI_VOID Win_PqProcess(WINDOW_S *pstWin,
                      HI_DRV_VIDEO_FRAME_S *pstFrame,
                      HI_RECT_S *pstVideoRect,
                      const HI_DISP_DISPLAY_INFO_S *pstDispInfo,
                      HI_BOOL bHdrMode)
{
    HI_VDP_PQ_INFO_S stTimingInfo;
    HI_DRV_WIN_ATTR_S *pstAttr = &pstWin->stUsingAttr;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    DISP_INTF_OPERATION_S stFunction = {0};
    HI_U32 u32PixelRepeateTimes = 0;

#ifdef  CHIP_TYPE_hi3798mv310
    Win_PqHdrCfgProcess(pstWin, pstFrame, pstDispInfo);
#endif
    (HI_VOID)pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer, &stVideoLayerCap);

    /*this is the current value.*/
    stTimingInfo.enLayerId  = pstWin->u32VideoLayer;
    if (HI_NULL == pstFrame)
    {
        stTimingInfo.u32Width = pstVideoRect->s32Width;
        stTimingInfo.u32Height = pstVideoRect->s32Height;
    }
    else
    {
        stTimingInfo.u32Width = ((HI_DRV_VIDEO_PRIVATE_S *)&pstFrame->u32Priv[0])->stVideoOriginalInfo.u32Width;
        stTimingInfo.u32Height = ((HI_DRV_VIDEO_PRIVATE_S *)&pstFrame->u32Priv[0])->stVideoOriginalInfo.u32Height;
        if (stTimingInfo.u32Width == 0 || stTimingInfo.u32Height == 0)
        {
            stTimingInfo.u32Width = pstFrame->u32Width;
            stTimingInfo.u32Height = pstFrame->u32Height;
        }

    }
    stTimingInfo.bSRState     = pstWin->stMiscInfor.bWinSrEnableCurrent;
    stTimingInfo.bPartUpdate = HI_TRUE;

    stTimingInfo.bIsogenyMode = DISP_Check_IsogenyMode();
    stTimingInfo.bHdrMode     = bHdrMode;

    stTimingInfo.stChannelTiming[(HI_PQ_DISPLAY_E)pstWin->enDisp].stFmtRect = pstDispInfo->stFmtResolution;
    stTimingInfo.stChannelTiming[(HI_PQ_DISPLAY_E)pstWin->enDisp].u32RefreshRate = pstDispInfo->u32RefreshRate;
    stTimingInfo.stChannelTiming[(HI_PQ_DISPLAY_E)pstWin->enDisp].bProgressive = pstDispInfo->bInterlace ? HI_FALSE : HI_TRUE;
    stTimingInfo.stChannelTiming[(HI_PQ_DISPLAY_E)pstWin->enDisp].enOutColorSpace = pstDispInfo->eColorSpace;

    (HI_VOID)DISP_HAL_GetOperation(&stFunction);

    if (HI_NULL != stFunction.PF_GetPixelRepeatTimesAccordingFmt)
    {
        stFunction.PF_GetPixelRepeatTimesAccordingFmt(pstWin->enDisp,
                pstDispInfo->eFmt,
                &u32PixelRepeateTimes);
    }
    else
    {
        WIN_FATAL("Get ops function failed!\n");
    }

    stTimingInfo.stVideo.s32X      = pstVideoRect->s32X * u32PixelRepeateTimes;
    stTimingInfo.stVideo.s32Y      = pstVideoRect->s32Y;
    stTimingInfo.stVideo.s32Width  = pstVideoRect->s32Width * u32PixelRepeateTimes;
    stTimingInfo.stVideo.s32Height = pstVideoRect->s32Height;

    stTimingInfo.stChannelTiming[(HI_PQ_DISPLAY_E)pstWin->enDisp].stFmtRect.s32Width *= u32PixelRepeateTimes;

    if (DISP_STEREO_NONE == pstDispInfo->eDispMode)
    {
        stTimingInfo.b3dType = HI_FALSE;
    }
    else
    {
        stTimingInfo.b3dType = HI_TRUE;
    }

    DRV_PQ_UpdateVdpPQ((HI_PQ_DISPLAY_E)pstWin->enDisp, &stTimingInfo, (S_VDP_REGS_TYPE *)g_pstVdpBaseAddr);

    /*save the value ,for next judgement.*/
    pstWin->stMiscInfor.stFrameOriginalRect.s32Width  = stTimingInfo.u32Width;
    pstWin->stMiscInfor.stFrameOriginalRect.s32Height  = stTimingInfo.u32Height;
    pstWin->stMiscInfor.stWinOutRect.s32Width  =  pstAttr->stOutRect.s32Width;
    pstWin->stMiscInfor.stWinOutRect.s32Height = pstAttr->stOutRect.s32Height;
    pstWin->stMiscInfor.bWinSrEnableLast       =  stTimingInfo.bSRState;

    return;
}


HI_VOID WinCropRect2InRect (HI_DRV_CROP_RECT_S *pstCropRect, HI_RECT_S *pstInRect, HI_U32 u32SrcW , HI_U32 u32SrcH)
{
    if ((0 == u32SrcW) || (0 == u32SrcH))
    {
        return ;
    }

    if (((pstCropRect->u32LeftOffset + pstCropRect->u32RightOffset) + WIN_FRAME_MIN_WIDTH > u32SrcW)
        || ((pstCropRect->u32TopOffset + pstCropRect->u32BottomOffset)  + WIN_FRAME_MIN_HEIGHT > u32SrcH))
    {
        WIN_ERROR("u32LeftOffset(%d) add u32RightOffset(%d) is too large(%d)\n"
                  "Or TopOffset(%d) add u32BottomOffset(%d) is too large(%d)\n",
                  pstCropRect->u32LeftOffset, pstCropRect->u32RightOffset, u32SrcW,
                  pstCropRect->u32TopOffset, pstCropRect->u32BottomOffset, u32SrcH);
        return;
    }

    pstInRect->s32X = pstCropRect->u32LeftOffset;
    pstInRect->s32Y = pstCropRect->u32TopOffset;
    pstInRect->s32Width  = u32SrcW - (pstCropRect->u32LeftOffset + pstCropRect->u32RightOffset);
    pstInRect->s32Height = u32SrcH - (pstCropRect->u32TopOffset + pstCropRect->u32BottomOffset);

    return;
}

static HI_BOOL WinRectVpssProcessed(WINDOW_S *pstWin,
                                    HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;
    HI_BOOL bVpssProcessed = HI_FALSE;

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstFrame->u32Priv;

    if ((pstPriv->stVideoOriginalInfo.u32Width != pstFrame->u32Width )
        || (pstPriv->stVideoOriginalInfo.u32Height != pstFrame->u32Height )
       )
    {
        bVpssProcessed = HI_TRUE;
    }
    else if ((VDP_LAYER_VID1 == pstWin->u32VideoLayer)
        && (HI_TRUE == pstWin->stUsingAttr.bUseCropRect))
    {
        /* indicate vpss processed even when oriRect==frameRect. */
        bVpssProcessed = HI_TRUE;
    }
    else
    {
        bVpssProcessed = HI_FALSE;
    }

    return bVpssProcessed;

}

static HI_VOID WinConfigInrect(WINDOW_S *pstWin, WIN_HAL_PARA_S *pstLayerPara,
                               HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    if (HI_NULL == pstWin || HI_NULL == pstLayerPara || HI_NULL == pstFrame)
    {
        return;
    }

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstFrame->u32Priv;

    if (WinRectVpssProcessed(pstWin, pstFrame))
    {
        /*means vpss processed */
        pstLayerPara->stIn = pstFrame->stDispRect;
    }
    else
    {
        if (HI_TRUE == pstWin->stUsingAttr.bUseCropRect)
        {
            WinCropRect2InRect( &pstWin->stUsingAttr.stCropRect, &pstLayerPara->stIn, pstFrame->u32Width, pstFrame->u32Height);
        }
        else
        {
            pstLayerPara->stIn = pstWin->stUsingAttr.stInRect;
            Win_ReviseInRect(&pstLayerPara->stIn, &pstFrame->stDispRect);
        }
    }
}

HI_VOID Win_GenerateConfigInfo(WINDOW_S *pstWin,
                               HI_DRV_VIDEO_FRAME_S *pstFrame,
                               const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo,
                               WIN_HAL_PARA_S *pstLayerPara)
{
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap = {0};

    HI_RECT_S stFrameIntermediaRect = {0};
    DISP_INTF_OPERATION_S stFunction = {0};
    HI_BOOL bHdInterfaceInterleave = HI_FALSE;
    HI_BOOL bBtm  =    HI_FALSE;
    HI_U32  u32Vcnt = 0;
    HI_RECT_S  stFinalVideoPosition;/*out out video Rect*/
    HI_RECT_S  stFinalDisPosition;/*out out win Rect*/

    VDP_ALG_RATIO_DRV_PARA_S  stDrvPara;
    VDP_ALG_RATIO_OUT_PARA_S  stOutPara;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;

    HI_DRV_DISP_OFFSET_S  stOffsetTmp = {0};
    HI_RECT_S stFmtResolution = {0};

    memset(&stDrvPara, 0, sizeof(VDP_ALG_RATIO_DRV_PARA_S));
    memset(&stOutPara, 0, sizeof(VDP_ALG_RATIO_OUT_PARA_S));
    memset(&stFinalDisPosition, 0, sizeof(HI_RECT_S));
    memset(&stFinalVideoPosition, 0, sizeof(HI_RECT_S));

    (HI_VOID)pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer, &stVideoLayerCap);

    /* first  get the basic setting of layerparam. */
    memset(pstLayerPara, 0x0, sizeof(WIN_HAL_PARA_S));

    /*tnr alg need 2 buffers, we make a alternating use.*/
    pstLayerPara->bTnrOnVdp = Win_CheckTnrLocateOnVdp(pstWin, &pstFrame->stDispRect);
    if (pstWin->stWinAlgMMZ[0].bReady == HI_TRUE)
    {
        pstLayerPara->stLayerAlgMmz = pstWin->stWinAlgMMZ[0].stVideoAlgMmz;
        pstWin->stWinAlgMMZ[0].bReady = HI_FALSE;
    }
    else
    {
        pstLayerPara->stLayerAlgMmz = pstWin->stWinAlgMMZ[1].stVideoAlgMmz;
        pstWin->stWinAlgMMZ[0].bReady = HI_TRUE;
    }

    pstLayerPara->bDolbyMode = (pstWin->enWinMode == HI_DRV_WINDOW_MODE_DOLBY) ? HI_TRUE : HI_FALSE;
    pstLayerPara->en3Dmode = pstInfo->stDispInfo.eDispMode;
    pstLayerPara->bRightEyeFirst = pstInfo->stDispInfo.bRightEyeFirst;
    pstLayerPara->pstFrame = pstFrame;

    /*stOutRect may equal to stIn in most situation.*/
    pstLayerPara->pstDispInfo = (HI_DISP_DISPLAY_INFO_S *) & (pstInfo->stDispInfo);

    pstLayerPara->u32RegionNum =    pstWin->u32VideoRegionNo;
    pstLayerPara->u32LayerNO =    pstWin->u32VideoLayer;
    pstLayerPara->bRegionMute  = 0;
    pstLayerPara->bRegionEnable = HI_TRUE;

    WinConfigInrect(pstWin, pstLayerPara, pstFrame);

    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)pstFrame->u32Priv;

    if ((!pstPriv->bAspectProcessed) && ( stVideoLayerCap.bZme))
    {
        /*window phy OutRect*/
        stFinalDisPosition = pstWin->stUsingAttr.stOutRect;

        /*need VDP AspRatio process*/
        /*out out win Rect*/
        stDrvPara.AspectWidth = pstFrame->u32AspectWidth;
        stDrvPara.AspectHeight = pstFrame->u32AspectHeight;
        stDrvPara.DeviceHeight = pstInfo->stDispInfo.stAR.u32ARh;
        stDrvPara.DeviceWidth = pstInfo->stDispInfo.stAR.u32ARw;
        stDrvPara.eAspMode = pstWin->stUsingAttr.enARCvrs;

        if ((!pstWin->stUsingAttr.stCustmAR.u32ARw ) || (!pstWin->stUsingAttr.stCustmAR.u32ARh))
        {
            stDrvPara.stUsrAsp.bUserDefAspectRatio = HI_FALSE;
        }
        else
        {
            stDrvPara.stUsrAsp.bUserDefAspectRatio = HI_TRUE;
        }

        stDrvPara.stUsrAsp.u32UserAspectWidth = pstWin->stUsingAttr.stCustmAR.u32ARw;
        stDrvPara.stUsrAsp.u32UserAspectHeight = pstWin->stUsingAttr.stCustmAR.u32ARh;

        stDrvPara.stSrcRect = pstFrame->stDispRect;
        stDrvPara.stInWnd = pstLayerPara->stIn;
        stDrvPara.stOutWnd = stFinalDisPosition;
        stDrvPara.stScreen = pstInfo->stDispInfo.stFmtResolution;

        if ((0 == stDrvPara.stOutWnd.s32Width) || (0 == stDrvPara.stOutWnd.s32Height))
        {
            stDrvPara.stOutWnd.s32Width = stDrvPara.stScreen.s32Width;
            stDrvPara.stOutWnd.s32Height = stDrvPara.stScreen.s32Height;
        }

        if ((stDrvPara.eAspMode == HI_DRV_ASP_RAT_MODE_FULL
             || stDrvPara.eAspMode == HI_DRV_ASP_RAT_MODE_BUTT)
            && stDrvPara.stOutWnd.s32Width == 720
            && stDrvPara.stInWnd.s32Width == 704
            && (stDrvPara.stInWnd.s32Height == 576
                || stDrvPara.stInWnd.s32Height == 480)
            && stDrvPara.stInWnd.s32Height
            == stDrvPara.stOutWnd.s32Height)
        {
            stOutPara.stOutWnd.s32X = 8;
            stOutPara.stOutWnd.s32Y = 0;
            stOutPara.stOutWnd.s32Width = stDrvPara.stInWnd.s32Width;
            stOutPara.stOutWnd.s32Height = stDrvPara.stInWnd.s32Height;
        }
        else
        {
            Win_AspRatioProcess(&stDrvPara, &stOutPara);
        }

        stFinalVideoPosition = stOutPara.stOutWnd;
        pstLayerPara->stIn = stDrvPara.stInWnd;
    }
    else
    {
        if ( VDP_LAYER_VID3 == pstWin->u32VideoLayer)
        {
            HI_DRV_VIDEO_PRIVATE_S *pstFramePrivate = (HI_DRV_VIDEO_PRIVATE_S *)(&(pstFrame->u32Priv[0]));

            stFinalDisPosition = pstFramePrivate->stWBC2SDDispRect;
        }
        else
        {
            stFinalDisPosition = pstWin->stUsingAttr.stOutRect;
        }

        stFinalVideoPosition = stFinalDisPosition;

    }

    pstLayerPara->stDisp   = stFinalDisPosition;
    pstLayerPara->stVideo  = stFinalVideoPosition;

    {
        pstLayerPara->stOriRect.s32Width = pstPriv->stVideoOriginalInfo.u32Width;
        pstLayerPara->stOriRect.s32Height = pstPriv->stVideoOriginalInfo.u32Height;
        pstLayerPara->u32Fidelity = pstPriv->u32Fidelity;
    }

    /*get current hd's p/I  attribution.*/
    bHdInterfaceInterleave = pstInfo->stDispInfo.bInterlace;

    (HI_VOID)DISP_HAL_GetOperation(&stFunction);
    if (HI_NULL == stFunction.FP_GetChnBottomFlag)
    {
        WIN_INFO("stFunction.FP_GetChnBottomFlag is NULL!\n");
        return ;
    }
    stFunction.FP_GetChnBottomFlag(pstWin->enDisp, &bBtm, &u32Vcnt);

    if (pstWin->bVirtScreenMode == HI_TRUE)
    {
        WinGetActualOffsetAccordingUserSetting(pstWin->enDisp,
                                               &pstLayerPara->pstDispInfo->stOffsetInfo,
                                               &stOffsetTmp,
                                               &pstWin->stCfg.stAttrBuf.stOutRect);
    }
    else
    {
        memset((void *)&stOffsetTmp, 0, sizeof(stOffsetTmp));
    }

    stFmtResolution = pstLayerPara->pstDispInfo->stFmtResolution;

    if ((pstLayerPara->stIn.s32Width != pstLayerPara->stVideo.s32Width)
        || (pstLayerPara->stIn.s32Height != pstLayerPara->stVideo.s32Height))
    {
        if (!stVideoLayerCap.bZme)
        {
            /*we must confirm that v1, should not configure the zme,
                        but the ifir is needed ,so we have to configure it or not? */
            pstLayerPara->bRegionMute = HI_TRUE;
            WIN_WARN("stIn[w %d, h %d]  stVideo[w %d, h %d]\n",
                pstLayerPara->stIn.s32Width,
                pstLayerPara->stIn.s32Height,
                pstLayerPara->stVideo.s32Width,
                pstLayerPara->stVideo.s32Height);
        }
    }
    /*
        *since we support picture moved out of screen, so we should give a revise to the window ,
        *both inrect and outrect.
        */
    (HI_VOID)Win_Revise_OutOfScreenWin_OutRect(&pstLayerPara->stIn, &pstLayerPara->stVideo, &pstLayerPara->stDisp,
            &stFmtResolution,
            &stOffsetTmp,
            pstLayerPara);

    if (((pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV12_CMP)
         || (pstFrame->ePixFormat == HI_DRV_PIX_FMT_NV21_CMP))
        && (stVideoLayerCap.bDcmp != HI_TRUE))
    {
        /*frame is compressed but the layer has no capability*/
        pstLayerPara->bRegionMute = 1;
    }

    if (pstLayerPara->bRegionMute)
    {


        pstLayerPara->stIn.s32Width = pstLayerPara->stDisp.s32Width;
        pstLayerPara->stIn.s32Height = pstLayerPara->stDisp.s32Height;
        pstLayerPara->stVideo.s32Width = pstLayerPara->stDisp.s32Width;
        pstLayerPara->stVideo.s32Height = pstLayerPara->stDisp.s32Height;
    }

    stFrameIntermediaRect.s32X      = 0;
    stFrameIntermediaRect.s32Y      = 0;
    stFrameIntermediaRect.s32Width  = pstFrame->DispCtrlWidth;
    stFrameIntermediaRect.s32Height = pstFrame->DispCtrlHeight;
    /*get intermediate Rect to degrade the PQ  as a matter of TEE monitor.*/
    Win_Policy_GetPQDegradingConfigFromTEE(pstFrame->bSecure,
                                           &pstLayerPara->stIn,
                                           &pstLayerPara->stVideo,
                                           pstWin->u32VideoLayer,
                                           &stFrameIntermediaRect,
                                           &pstLayerPara->bHdcpDegradePQ,
                                           &pstLayerPara->stHdcpIntermediateRect);

    pstLayerPara->enLayerFrostMode = pstWin->enWinFrostMode;
    return;
}

HI_VOID Win_UpWinPosionDebugInfo(HI_VOID *hDst, WIN_HAL_PARA_S *pstLayerPara)
{
    WINDOW_S *pstWin;
    HI_DISP_DISPLAY_INFO_S stDispInfo = {0};

    pstWin = (WINDOW_S *)hDst;
    (HI_VOID)DISP_GetDisplayInfo(pstWin->enDisp, &stDispInfo);

    pstWin->stWinDebugInfo.stWinUseInfo.u32OffsetLeft = stDispInfo.stOffsetInfo.u32Left;
    pstWin->stWinDebugInfo.stWinUseInfo.u32OffsetRight = stDispInfo.stOffsetInfo.u32Top;
    pstWin->stWinDebugInfo.stWinUseInfo.u32OffsetTop = stDispInfo.stOffsetInfo.u32Right;
    pstWin->stWinDebugInfo.stWinUseInfo.u32OffsetButtom = stDispInfo.stOffsetInfo.u32Bottom;

    pstWin->stWinDebugInfo.stWinUseInfo.stVirInRect = pstWin->stCfg.stAttr.stInRect;
    pstWin->stWinDebugInfo.stWinUseInfo.stVirOutRect = pstWin->stCfg.stAttr.stOutRect;

    pstWin->stWinDebugInfo.stWinUseInfo.stPhyInRect = pstWin->stUsingAttr.stInRect;
    pstWin->stWinDebugInfo.stWinUseInfo.stPhyOutRect = pstWin->stUsingAttr.stOutRect;

    if (HI_NULL != pstLayerPara->pstFrame)
    {
        pstWin->stWinDebugInfo.stWinHalInfo.stSrcRect.s32X = 0;
        pstWin->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Y = 0;
        pstWin->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Width = pstLayerPara->pstFrame->u32Width;
        pstWin->stWinDebugInfo.stWinHalInfo.stSrcRect.s32Height = pstLayerPara->pstFrame->u32Height;
    }

    pstWin->stWinDebugInfo.stWinHalInfo.stIn = pstLayerPara->stIn;
    pstWin->stWinDebugInfo.stWinHalInfo.stVideo = pstLayerPara->stVideo;
    pstWin->stWinDebugInfo.stWinHalInfo.stDisp = pstLayerPara->stDisp;

    return;
}

HI_VOID ISR_WinConfigFrameNormal(WINDOW_S *pstWin, HI_DRV_VIDEO_FRAME_S *pstFrame, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    WIN_HAL_PARA_S stLayerPara = {0};
    HI_DRV_DISP_COLOR_SETTING_S stColor;
    HI_U32 u32Fidelity = 0;
    DISP_INTF_OPERATION_S *pstDispOpt = HI_NULL;
    HI_RECT_S stCanvas;
    HIDRV_DISP_NODE_DELAYTIME   *pstDispNodedelayTime = HI_NULL;
    HI_BOOL  bSdrChoice = HI_FALSE, bHdrFrame = HI_FALSE;
    WIN_INFO_S stWinInfo = {0};

    memset(&stCanvas, 0, sizeof(stCanvas));
    memset(&stColor, 0, sizeof(stColor));

    pstDispOpt = DISP_HAL_GetOperationPtr();

    pstWin->stCfg.eDispMode = pstInfo->stDispInfo.eDispMode;
    pstWin->stCfg.bRightEyeFirst = pstInfo->stDispInfo.bRightEyeFirst;

    (HI_VOID) Win_GenerateConfigInfo(pstWin, pstFrame, pstInfo, &stLayerPara);

    WIN_SHARE_GetFrameColorSpace(pstFrame, &stColor.enInCS);
    stColor.enOutCS = pstInfo->stDispInfo.eColorSpace;
    u32Fidelity     = ((HI_DRV_VIDEO_PRIVATE_S *)&pstFrame->u32Priv[0])->u32Fidelity;

    if (stColor.enInCS == HI_DRV_CS_UNKNOWN)
    {
        stColor.enInCS = HI_DRV_CS_BT709_YUV_LIMITED;
    }

    if (stColor.enOutCS == HI_DRV_CS_UNKNOWN)
    {
        stColor.enOutCS = HI_DRV_CS_BT709_YUV_LIMITED;
    }

    pstWin->stCfg.enFrameCS = stColor.enInCS;
    pstWin->stCfg.enOutCS    = stColor.enOutCS;
    pstWin->stCfg.u32Fidelity = u32Fidelity;

    if (pstWin->bDispInfoChange)
    {
        pstWin->bDispInfoChange = HI_FALSE;
    }

    /* here we delete all the rwzb content, just rebuild it  in 98cv200 .*/

    if (pstWin->enDisp == HI_DRV_DISPLAY_1)
    {
        if ((HI_NULL != pstDispOpt)
            && (HI_NULL != pstDispOpt->PF_DATE_SetCoef)
            && (HI_NULL != pstDispOpt->PF_DATE_SetIRE))
        {
            (HI_VOID)pstDispOpt->PF_DATE_SetCoef(HI_DRV_DISPLAY_0, RWZB_GetDATEParaIndex(u32Fidelity));
            (HI_VOID)pstDispOpt->PF_DATE_SetIRE(pstWin->enDisp, 0);
        }

        if ( VDP_LAYER_VID0 == stLayerPara.u32LayerNO )
        {
            HI_BOOL bRwzbProcess = HI_FALSE;

            WIN_POLICY_RwzbProcess(u32Fidelity, &bRwzbProcess);

            if ((HI_TRUE == bRwzbProcess) && (pstFrame->u32Height == stLayerPara.stVideo.s32Height))
            {
                (HI_VOID)DRV_PQ_SetDefaultParam(HI_TRUE);
                if (( 1 == WinGetHDWinNum()) && ( pstInfo->stDispInfo.bAttachCVBS))
                {
                    stLayerPara.bCloseY2R = HI_TRUE;
                }
            }
            else if ((HI_DRV_PIX_FMT_NV61_2X1 == pstFrame->ePixFormat) && (pstFrame->u32Height >= UHD_2160P_HEIGHT))
            {
                (HI_VOID)DRV_PQ_SetDefaultParam(HI_FALSE);
                stLayerPara.bCloseY2R = HI_TRUE;
            }
            else
            {
                (HI_VOID)DRV_PQ_SetDefaultParam(HI_FALSE);
                stLayerPara.bCloseY2R = HI_FALSE;
            }
        }
    }

    stLayerPara.u32Alpha = pstWin->stCfg.u32Alpha;
    stLayerPara.u32AllAlpha = pstInfo->stDispInfo.u32Alpha;
    stLayerPara.eOutPutColorSpace = pstWin->stCfg.enOutCS;
    stLayerPara.pstDispInfo = (HI_DISP_DISPLAY_INFO_S *) & (pstInfo->stDispInfo);

    WIN_JudgeHdrFrame(pstFrame->enSrcFrameType, &bHdrFrame);
    if ((HI_FALSE == bHdrFrame) || (pstWin->stUsingAttr.bCloseHdrPath))
    {
        bSdrChoice = HI_TRUE;
    }
    else
    {
#ifndef VDP_DOLBY_HDR_SUPPORT
        bSdrChoice = HI_TRUE;
#else
        bSdrChoice = HI_FALSE;
#endif
    }

    Win_PqProcess(pstWin, pstFrame, &stLayerPara.stVideo, &pstInfo->stDispInfo, !bSdrChoice);

    WinTransferConfigInfoToWinShareInfo(pstWin, &stLayerPara, &stWinInfo);

    WIN_SHARE_SetWinInfo(&stWinInfo);
    Win_UpdateHdFramInfo(&stLayerPara, &pstWin->stCfg, pstFrame->bSecure);
    WinTestFrameMatch(pstWin, pstFrame, (HI_DISP_DISPLAY_INFO_S *)&pstInfo->stDispInfo);

    pstDispNodedelayTime    =   &(pstWin->stBuffer.stWinBP.stBuffer.stDispNodeDelayTime);

    if (pstDispNodedelayTime)
    {
        (HI_VOID)DISP_GetVbiTimeInfo(pstWin->enDisp, HI_NULL, &(pstDispNodedelayTime->u32NodeConfigLeftTime));
    }

    Win_UpWinPosionDebugInfo(pstWin, &stLayerPara);

    return;
}

HI_VOID ISR_WinConfigFrame(WINDOW_S *pstWin,
                           HI_DRV_VIDEO_FRAME_S *pstFrame,
                           const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    if (HI_NULL == pstFrame)
    {
        ISR_WinConfigFrameMute(pstWin, pstFrame, pstInfo);
    }
    else
    {
        if ((MUTE_INTERMEDIARect == pstFrame->DispCtrlWidth)
            || (MUTE_INTERMEDIARect == pstFrame->DispCtrlHeight))
        {
            ISR_WinConfigFrameMute(pstWin, pstFrame, pstInfo);
        }
        else
        {
            ISR_WinConfigFrameNormal(pstWin, pstFrame, pstInfo);
        }
    }

    if (pstFrame)
    {
        if (0 == pstFrame->stLowdelayStat.u32WinConfigTime)
        {
            if (HI_DRV_SYS_GetTimeStampMs(&(pstFrame->stLowdelayStat.u32WinConfigTime)))
            {
                DISP_ERROR("get sys time failed, not init.\n");
                return ;
            }
        }

        memcpy(&pstWin->stLowdelayStat, &pstFrame->stLowdelayStat, sizeof(HI_DRV_LOWDELAY_STAT_INFO_S));
    }

    WinUpdateDispInfo(pstWin, (HI_DISP_DISPLAY_INFO_S *)&pstInfo->stDispInfo);
    return ;
}

HI_VOID ISR_WinUpdatePlayInfo(WINDOW_S *pstWin, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    // calc delay time in buffer queue
    HI_U32 T = 0;

    if ((0 == pstInfo->stDispInfo.u32RefreshRate)
        || (0 == pstInfo->stDispInfo.stFmtResolution.s32Height)
        || (0 == pstInfo->stDispInfo.stPixelFmtResolution.s32Height))
    {
        WIN_ERROR("Invalid display fresh rate!\n");
        return;
    }

    pstWin->stDelayInfo.u32DispRate = pstInfo->stDispInfo.u32RefreshRate;
    pstWin->stDelayInfo.T = (1 * 1000 * 100) / pstInfo->stDispInfo.u32RefreshRate;

    pstWin->stDelayInfo.bInterlace = pstInfo->stDispInfo.bInterlace;
    T = pstWin->stDelayInfo.T;

    if (pstInfo->stDispInfo.bInterlace)
    {
        pstWin->stDelayInfo.u32DisplayTime = (pstInfo->stDispInfo.u32Vline * 2 * T) / pstInfo->stDispInfo.stPixelFmtResolution.s32Height;
    }
    else
    {
        pstWin->stDelayInfo.u32DisplayTime = (pstInfo->stDispInfo.u32Vline * T) / pstInfo->stDispInfo.stPixelFmtResolution.s32Height;
    }

    if (HI_DRV_SYS_GetTimeStampMs((HI_U32 *)&pstWin->stDelayInfo.u32CfgTime))
    {
        DISP_ERROR("get sys time failed, not init.\n");
        return ;
    }

    return;
}


HI_DRV_VIDEO_FRAME_S *WinSearchMatchFrame(WINDOW_S *pstWin)
{
    WIN_DISP_INFO_S *pstDispInfo;
    HI_DRV_FIELD_MODE_E enDstField;
    HI_DRV_VIDEO_FRAME_S *pstDispFrame, *pstNewFrame;

    // if display work at interlace mode
    pstDispInfo = &pstWin->stDispInfo;

    if (pstDispInfo->bIsInterlace != HI_TRUE)
    {
        // if master window output progressive frame, get slave window info
        if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE)
        {
            WIN_DISP_INFO_S *pstSlvDispInfo = HI_NULL;

            pstSlvDispInfo = WinGetDispInfoByHandle(pstWin->hSlvWin);
            if (pstSlvDispInfo)
            {
                if ((pstSlvDispInfo->bIsInterlace == HI_TRUE)
                    && (pstDispInfo->u32RefreshRate == pstSlvDispInfo->u32RefreshRate)
                   )
                {
                    pstDispInfo = pstSlvDispInfo;
                }
            }
        }
    }

    if (pstDispInfo->bIsInterlace != HI_TRUE)
    {
        /*if output progressive picture, need not to search top/bottom field*/
        return WinBuf_GetConfigFrame(&pstWin->stBuffer.stWinBP);
    }

    /* dectect whether top-field video frame output at top-field time*/
    pstDispFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);
    enDstField = pstDispInfo->bIsBtm ? HI_DRV_FIELD_BOTTOM : HI_DRV_FIELD_TOP;


    pstNewFrame = WinBuf_GetFrameByDisplayInfo(&pstWin->stBuffer.stWinBP,
                  pstDispFrame,
                  pstDispInfo->u32RefreshRate,
                  enDstField);
    return pstNewFrame;
}


HI_DRV_VIDEO_FRAME_S *WinGetFrameToConfig(WINDOW_S *pstWin, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE)
    {
        pstFrame = ISR_SlaveWinGetConfigFrame(pstWin);
        if (pstFrame == HI_NULL && pstWin->bQuickMode)
        {
            HI_DRV_VIDEO_FRAME_S *pstDispFrame = HI_NULL;

            pstDispFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);

            WinBuf_FlushWaitingFrame(&pstWin->stBuffer.stWinBP, pstDispFrame);
        }
    }
    else
    {
        if (pstWin->bQuickMode)
        {
            HI_DRV_VIDEO_FRAME_S *pstDispFrame = HI_NULL;

            pstDispFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);
            pstFrame = WinBuf_GetNewestFrame(&pstWin->stBuffer.stWinBP, pstDispFrame);
        }
        else
        {
            if (!pstWin->bStepMode)
            {
                pstFrame = WinSearchMatchFrame(pstWin);
            }
            else
            {
                if (pstWin->bStepPlayNext)
                {
                    pstFrame = WinSearchMatchFrame(pstWin);
                }
            }
        }
    }


    if (!pstFrame)
    {
        /*if not  receive frame*/
        pstWin->stBuffer.u32UnderLoad++;

        if (WinTestBlackFrameFlag(pstWin) != HI_TRUE)
        {
            /*
                    1 :  if first config frame ,config nothing.
                    2 :  if last config is not black frame, repeat last config frame*/
            WinBuf_RepeatDisplayedFrame(&pstWin->stBuffer.stWinBP);
            pstFrame = WinBuf_GetConfigedFrame(&pstWin->stBuffer.stWinBP);
        }
        else
        {
            /*if last config is black frame, repeat black frame*/
            WinSetBlackFrameFlag(pstWin);
        }
    }
    else
    {
        /*if received frame*/
        WinClearBlackFrameFlag(pstWin);
        //wait for next frame to play.
        pstWin->bStepPlayNext = HI_FALSE;
    }

    return pstFrame;
}

HI_VOID WinGetHDDispInfo(HI_DRV_DISPLAY_E enDisp, HI_BOOL *pb3Dmode, HI_BOOL *pbSDFmt, HI_BOOL *pbHDInterlace)
{
    HI_DISP_DISPLAY_INFO_S stDispInfo = {0};

    (HI_VOID)DISP_GetDisplayInfo(enDisp, &stDispInfo);

    if (DISP_STEREO_NONE != stDispInfo.eDispMode)
    {
        *pb3Dmode =  HI_TRUE;
    }
    else
    {
        *pb3Dmode =  HI_FALSE;
    }

    *pbHDInterlace = stDispInfo.bInterlace;

    if ((HI_DRV_DISP_FMT_PAL <= stDispInfo.eFmt ) && (HI_DRV_DISP_FMT_1440x480i_60 >= stDispInfo.eFmt ))
    {
        *pbSDFmt  =  HI_TRUE;
    }
    else
    {
        *pbSDFmt =  HI_FALSE;
    }
    return;
}

HI_S32 WinUpdateWinAttr(WINDOW_S *pstWin, const HI_DISP_DISPLAY_INFO_S *pstDispInfo)
{
    HI_RECT_S stOutRectRevised = {0};

    WinCheckNullPointer(pstWin);
    WinCheckNullPointer(pstDispInfo);

    memset((void *)&stOutRectRevised, 0, sizeof(stOutRectRevised));

    /*give a size conversion from:
         * 1) user setting(virtscreen)-----> virtual screen---->actual format;
         * 2) user setting(physical coordinate)--------> actual format
       * in fact, you can choose only one through the flag pstWin->bVirtScreenMode.
         */

    pstWin->stUsingAttr  = pstWin->stCfg.stAttrBuf;

    WinOutRectSizeConversionByType(pstDispInfo, &stOutRectRevised, pstWin);
    pstWin->stUsingAttr.stOutRect = stOutRectRevised;

    WinInRectAlign(&pstWin->stUsingAttr.stInRect, pstWin->u32VideoLayer);

    pstWin->stUsingAttr.stCropRect.u32LeftOffset  = WinParamAlignUp(pstWin->stUsingAttr.stCropRect.u32LeftOffset, HI_WIN_IN_RECT_WIDTH_ALIGN);
    pstWin->stUsingAttr.stCropRect.u32RightOffset = WinParamAlignUp(pstWin->stUsingAttr.stCropRect.u32RightOffset, HI_WIN_IN_RECT_WIDTH_ALIGN);
    pstWin->stUsingAttr.stCropRect.u32TopOffset  =  WinParamAlignUp(pstWin->stUsingAttr.stCropRect.u32TopOffset, HI_WIN_IN_RECT_HEIGHT_ALIGN);
    pstWin->stUsingAttr.stCropRect.u32BottomOffset = WinParamAlignUp(pstWin->stUsingAttr.stCropRect.u32BottomOffset, HI_WIN_IN_RECT_HEIGHT_ALIGN);

    /*when not virtual screen mode, the cfg's attr must be the actual physical fmt.*/
    pstWin->stCfg.stAttr = pstWin->stCfg.stAttrBuf;
    if (!pstWin->bVirtScreenMode)
    {
        pstWin->stCfg.stAttr.stOutRect =  pstWin->stUsingAttr.stOutRect;
    }

    return HI_SUCCESS;
}

static HI_VOID Local_SetFrameStillFlag(WINDOW_S *pstWin,
                                       HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    /*means VDP can  hold the frame, even after switch programs, just free the frame, do not return
        * to back module.
        */
    if (HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST == pstWin->stRst.enResetMode)
    {
        pstFrame->u32StillFrame = HI_DRV_FRAME_SWITCH_PROGRAM_STILL;
    }
    else
    {
        pstFrame->u32StillFrame = HI_DRV_FRAME_NORMAL;
    }

    return;
}

static HI_VOID WinResetBuffer(WINDOW_S *pstWin,
                              const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;

    (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
    ISR_WinReleaseUSLFrame(pstWin);

    pstFrame = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);
    (HI_VOID)WinBuf_FlushWaitingFrame(&pstWin->stBuffer.stWinBP, pstFrame);

    switch (pstWin->stRst.enResetMode)
    {
        case HI_DRV_WIN_SWITCH_BLACK:
            /*do not use blackframe,just set the flag and mute the layer.*/
            WinSetBlackFrameFlag(pstWin);

            /*pass NULL frame-ptr into the func, just mute it internally.*/
            ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);

#ifdef HI_VO_WIN_SYNC_SUPPORT
            (HI_VOID)WIN_Sync_Flush(pstWin);
#endif

            break;
        case HI_DRV_WIN_SWITCH_LAST:
        case HI_DRV_WIN_SWITCH_DEATTACHMODE_LAST:

            WinBuf_RepeatDisplayedFrame(&pstWin->stBuffer.stWinBP);
            pstFrame = WinBuf_GetConfigedFrame(&pstWin->stBuffer.stWinBP);

            if (HI_NULL == pstFrame)
            {
                /*no frame to display, mute it.*/
                WinSetBlackFrameFlag(pstWin);
                ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
            }
            else
            {
                Local_SetFrameStillFlag(pstWin, pstFrame);

                ISR_WinConfigFrame(pstWin, pstFrame, pstInfo);
                WinClearBlackFrameFlag(pstWin);

#ifdef HI_VO_WIN_SYNC_SUPPORT
                WIN_Sync_Signal(pstWin,
                                pstFrame->u32FrameIndex,
                                pstFrame->stBufAddr[0].u32PhyAddr_Y);
#endif
            }
            break;
        default:
            break;
    }

    pstWin->enState = WIN_STATE_WORK;
    pstWin->bReset  = HI_FALSE;
    pstWin->stRst.enResetMode  = HI_DRV_WIN_SWITCH_BUTT;

    return;
}

static HI_VOID WinPauseBuffer(WINDOW_S *pstWin,
                              const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;

    (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
    ISR_WinReleaseUSLFrame(pstWin);

    (HI_VOID)WinBuf_RepeatDisplayedFrame(&pstWin->stBuffer.stWinBP);

    pstFrame = WinBuf_GetConfigedFrame(&pstWin->stBuffer.stWinBP);
    if (!pstFrame)
    {
        WinSetBlackFrameFlag(pstWin);
        ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
    }
    else if (pstFrame)
    {
        ISR_WinConfigFrame(pstWin, pstFrame, pstInfo);
        WinClearBlackFrameFlag(pstWin);
    }

    return;
}


static HI_VOID WinFreezeBuffer(WINDOW_S *pstWin,
                               const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;
    HI_S32 nRet = HI_FAILURE;

    (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
    ISR_WinReleaseUSLFrame(pstWin);

    /*freeze mode, the buffer should flows as normal,  so we should let the buffer rounds.*/
    (HI_VOID)WinBuf_RepeatDisplayedFrame(&pstWin->stBuffer.stWinBP);
    pstFrame = WinBuf_GetConfigedFrame(&pstWin->stBuffer.stWinBP);

    nRet = WinBuf_ReleaseOneFrame(&pstWin->stBuffer.stWinBP, pstFrame);
    if (nRet != HI_SUCCESS)
    {
        /*u32UnderLoad happened */
        pstWin->stBuffer.u32UnderLoad++;
    }

    if (pstWin->stFrz.enFreezeMode == HI_DRV_WIN_SWITCH_BLACK)
    {
        WinSetBlackFrameFlag(pstWin);
        ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
    }
    else if (pstFrame)
    {
        ISR_WinConfigFrame(pstWin, pstFrame, pstInfo);
        WinClearBlackFrameFlag(pstWin);
    }
    else
    {
        ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
    }

    return;
}


static HI_VOID WinPlayBuffer(WINDOW_S *pstWin,
                             const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    HI_DRV_VIDEO_FRAME_S *pstFrame = HI_NULL;

    (HI_VOID)WinBuf_RlsAndUpdateUsingFrame(&pstWin->stBuffer.stWinBP);
    ISR_WinReleaseUSLFrame(pstWin);

    pstFrame = WinGetFrameToConfig(pstWin, pstInfo);
    if (pstFrame)
    {
        if (HI_SUCCESS != WinStatisticLowdelayTimeInfor(pstWin->u32Index, pstFrame, EVENT_VO_FRM_OUT))
        {
            WIN_ERROR("Update Window lowdelay time failed\n");
        }

        ISR_WinConfigFrame(pstWin, pstFrame, pstInfo);
        WinClearBlackFrameFlag(pstWin);

#ifdef HI_VO_WIN_SYNC_SUPPORT
        (HI_VOID)WIN_Sync_Signal(pstWin,
                                 pstFrame->u32FrameIndex,
                                 pstFrame->stBufAddr[0].u32PhyAddr_Y);
#endif

    }
    else if (WinTestBlackFrameFlag(pstWin) == HI_TRUE)
    {
        /*no frame to display, just mute the layer.*/
        ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
    }
    else
    {
        ISR_WinConfigFrame(pstWin, HI_NULL, pstInfo);
    }

    /* last branch , no frame and it's the start of playing, just return. */
    return;
}

HI_VOID ISR_CallbackForWinProcess(HI_VOID *hDst, const HI_DRV_DISP_CALLBACK_INFO_S *pstInfo)
{
    WINDOW_S *pstWin;
    HI_BOOL bUpDispInfo = HI_FALSE;
    HI_BOOL bUpWinAttr = HI_FALSE;
    HI_SIZE_T irqflag = 0;

    if (!hDst || !pstInfo )
    {
        WIN_ERROR("Input null pointer\n");
        return;
    }

    spin_lock_irqsave(&g_threadIsr_Lock, irqflag);

    pstWin = (WINDOW_S *)hDst;

    if (pstInfo->eEventType != HI_DRV_DISP_C_VT_INT)
    {
        DISP_PRINT("DISP HI_DRV_DISP_C_event= %d, disp=%d\n", pstInfo->eEventType, pstWin->enDisp);
    }

    if ((WIN_DEVICE_STATE_SUSPEND == s_s32WindowGlobalFlag)
        || (pstInfo->eEventType == HI_DRV_DISP_C_PREPARE_CLOSE)
        || (pstInfo->eEventType == HI_DRV_DISP_C_PREPARE_TO_PEND)
       )
    {
        DISP_PRINT(">>>>>>>>> mask\n");
        pstWin->bMasked = HI_TRUE;
    }
    else
    {
        pstWin->bMasked = HI_FALSE;
    }

    if ( (pstInfo->eEventType == HI_DRV_DISP_C_DISPLAY_SETTING_CHANGE)
         || (pstInfo->eEventType == HI_DRV_DISP_C_OPEN)
         || (pstInfo->eEventType == HI_DRV_DISP_C_RESUME))
    {
        pstWin->bDispInfoChange = HI_TRUE;
        bUpDispInfo = HI_TRUE;
    }

    /*judge whether the window cfg is changed.
         * and reload the attr buffer to the buffer using.*/
    if (atomic_read(&pstWin->stCfg.bNewAttrFlag))
    {
        atomic_set(&pstWin->stCfg.bNewAttrFlag, 0);
        DISP_OSAL_SendEvent(&pstWin->stWinQueueEvent, EVENT_WIN_ATTR_UP_COMPLET);
        bUpWinAttr = HI_TRUE;
        pstWin->bDispInfoChange = HI_TRUE;
    }

    if (bUpDispInfo || bUpWinAttr)
    {
        (HI_VOID)WinUpdateWinAttr(pstWin, &pstInfo->stDispInfo);
    }

    (HI_VOID)WinSendAttrToSource(pstWin, (HI_DISP_DISPLAY_INFO_S *)&pstInfo->stDispInfo);

    DISP_PRINT("Display info>> M=%d,S=%d,att=%d, 3d=%d, R=%d, I=%d, w=%d, h=%d, %dvs%d, rate=%d, cs=%d\n",
               pstInfo->stDispInfo.bIsMaster,
               pstInfo->stDispInfo.bIsSlave,
               pstInfo->stDispInfo.enAttachedDisp,
               pstInfo->stDispInfo.eDispMode,
               pstInfo->stDispInfo.bRightEyeFirst,
               pstInfo->stDispInfo.bInterlace,
               pstInfo->stDispInfo.stPixelFmtResolution.s32Width,
               pstInfo->stDispInfo.stPixelFmtResolution.s32Height,
               pstInfo->stDispInfo.stAR.u32ARw,
               pstInfo->stDispInfo.stAR.u32ARh,
               pstInfo->stDispInfo.u32RefreshRate,
               pstInfo->stDispInfo.eColorSpace);

    if (HI_FALSE == pstWin->bEnable_Using || pstWin->bMasked)
    {
        WinDisableSingleLayerRegion(pstWin, pstInfo);

        spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
        return;
    }

    pstWin->bInInterrupt = HI_TRUE;

    if ((HI_DRV_DISP_C_VT_INT != pstInfo->eEventType)
        && (HI_DRV_DISP_C_DISPLAY_SETTING_CHANGE != pstInfo->eEventType))
    {
        goto __WIN_PROCESS_EXIT;
    }

    WIN_QUEUE_ProcessCMD(pstWin);

    if (pstWin->bReset)
    {
        WinResetBuffer(pstWin, pstInfo);
        goto __WIN_PROCESS_EXIT;
    }

    // window state transfer
    if (pstWin->bUpState)
    {
        ISR_WinStateTransfer(pstWin);
    }

    switch (pstWin->enState)
    {
        case WIN_STATE_WORK:
        {
            WinPlayBuffer(pstWin, pstInfo);
            break;
        }
        case WIN_STATE_PAUSE:
        {
            WinPauseBuffer(pstWin, pstInfo);
            break;
        }
        case WIN_STATE_FREEZE:
        {
            WinFreezeBuffer(pstWin, pstInfo);
            break;
        }
        default:
            break;
    }

__WIN_PROCESS_EXIT:

    ISR_WinUpdatePlayInfo(pstWin, pstInfo);

    /* Call async mseeage processor once */
    (HI_VOID)VDP_ASYNC_ProcessMsgOnce(0);
    pstWin->bInInterrupt = HI_FALSE;

    spin_unlock_irqrestore(&g_threadIsr_Lock, irqflag);
    return;
}


HI_S32 WinGetProcIndex(HI_HANDLE hWin, HI_U32 *p32Index)
{
    WINDOW_S *pstWin = HI_NULL;

    WinCheckDeviceOpen();
    WinCheckNullPointer(p32Index);

    pstWin = WinGetWindow(hWin);
    if (pstWin)
    {
        *p32Index = pstWin->u32Index;
    }
    else
    {
        VIRTUAL_S *pstVirWin = HI_NULL;

        pstVirWin = WinGetVirWindow(hWin);
        if (pstVirWin)
        {
            *p32Index = pstVirWin->u32Index;
        }
        else
        {
            return HI_ERR_VO_WIN_NOT_EXIST;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WinGetProcInfo(HI_HANDLE hWin, WIN_PROC_INFO_S *pstInfo)
{
    WINDOW_S *pstWin;

    WinCheckDeviceOpen();

    WinCheckNullPointer(pstInfo);

    DISP_MEMSET(pstInfo, 0, sizeof(WIN_PROC_INFO_S));

    // s1 get active window pointer
    pstWin = WinGetWindow(hWin);
    if (pstWin)
    {
        // get window proc info
        pstInfo->enType        = pstWin->enType;
        pstInfo->u32Index    = pstWin->u32Index;

        pstInfo->u32LayerId = (HI_U32)pstWin->u32VideoLayer;
        pstInfo->u32LayerRegionNo  = (HI_U32)pstWin->u32VideoRegionNo;

        pstInfo->u32Zorder  = pstWin->u32Zorder;
        pstInfo->bEnable   =  (HI_U32)pstWin->bEnable;
        pstInfo->bMasked   =  (HI_U32)pstWin->bMasked;
        pstInfo->u32WinState = (HI_U32)pstWin->enState;

        pstInfo->bReset = pstWin->bReset;
        pstInfo->enResetMode = pstWin->stRst.enResetMode;
        pstInfo->enFreezeMode = pstWin->stFrz.enFreezeMode;

        pstInfo->bQuickMode = pstWin->bQuickMode;
        pstInfo->bStepMode    = pstWin->bStepMode;
        pstInfo->bVirtualCoordinate = pstWin->bVirtScreenMode;

        pstInfo->hSrc           = (HI_U32)pstWin->stCfg.stSource.hSrc;
        pstInfo->hSecondSrc    = (HI_U32)pstWin->stCfg.stSource.hSecondSrc;
        pstInfo->pfAcqFrame    = (HI_VOID *)pstWin->stCfg.stSource.pfAcqFrame;
        pstInfo->pfRlsFrame    = (HI_VOID *)pstWin->stCfg.stSource.pfRlsFrame;
        pstInfo->pfSendWinInfo = (HI_VOID *)pstWin->stCfg.stSource.pfSendWinInfo;

        pstInfo->stAttr  = pstWin->stCfg.stAttr;
        pstInfo->u32Alpha = pstWin->stCfg.u32Alpha,

                 pstInfo->u32TBNotMatchCount = pstWin->u32TBNotMatchCount;

        pstInfo->eDispMode = pstWin->stCfg.eDispMode;
        pstInfo->bRightEyeFirst = pstWin->stCfg.bRightEyeFirst;

        pstInfo->hSlvWin  = (HI_U32)pstWin->hSlvWin;
        pstInfo->bDebugEn = (HI_U32)pstWin->bDebugEn;

        pstInfo->u32ULSIn  = pstWin->stBuffer.stUselessBuf.u32ULSIn;
        pstInfo->u32ULSOut = pstWin->stBuffer.stUselessBuf.u32ULSOut;
        pstInfo->u32UnderLoad = pstWin->stBuffer.u32UnderLoad;

        pstInfo->stWinInfoForDeveloper  = pstWin->stWinInfoForDeveloper;
#ifdef VDP_ISOGENY_SUPPORT
        WIN_GetIsogenyPocInfor(&pstInfo->stIsogenyProcInfo);
#endif
        WinBuf_GetStateInfo(&pstWin->stBuffer.stWinBP, &(pstInfo->stBufState));
        pstInfo->stWinDebugInfo = pstWin->stWinDebugInfo;
        pstInfo->enWinMode  = pstWin->enWinMode;
        memcpy(&pstInfo->stLowdelayStat, &pstWin->stLowdelayStat, sizeof(HI_DRV_LOWDELAY_STAT_INFO_S));
        pstInfo->stFirstFrmStatus = pstWin->stCfg.stFirstFrmStatus;
    }
    else
    {
        VIRTUAL_S *pstVirWin;

        pstVirWin = WinGetVirWindow(hWin);
        if (pstVirWin)
        {
            // get virtual proc info
            pstInfo->enType        = pstVirWin->enType;
            pstInfo->u32Index    = pstVirWin->u32Index;
            pstInfo->u32LayerId = 0xFFFFul;  // not use video layer
            pstInfo->bEnable   = (HI_U32)pstVirWin->bEnable;
            pstInfo->bMasked   = (HI_U32)pstVirWin->bMasked;
            pstInfo->u32WinState = 0;  // 0 means work

            pstInfo->hSrc          = (HI_U32)pstVirWin->stSrcInfo.hSrc;
            pstInfo->pfAcqFrame    = (HI_VOID *)pstVirWin->stSrcInfo.pfAcqFrame;
            pstInfo->pfRlsFrame    = (HI_VOID *)pstVirWin->stSrcInfo.pfRlsFrame;
            pstInfo->pfSendWinInfo = (HI_VOID *)pstVirWin->stSrcInfo.pfSendWinInfo;

            pstInfo->stAttr = pstVirWin->stAttrBuf;


            pstInfo->stBufState.stRecord.u32TryQueueFrame = pstVirWin->stFrameStat.u32SrcQTry;
            pstInfo->stBufState.stRecord.u32QueueFrame      = pstVirWin->stFrameStat.u32SrcQOK;

            pstInfo->stBufState.stRecord.u32Release = pstVirWin->stFrameStat.u32SinkRlsOK;
        }
        else
        {
            WIN_ERROR("WIN is not exist!\n");
            return HI_ERR_VO_WIN_NOT_EXIST;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WinGetCurrentImg(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    WINDOW_S *pstWin;
    HI_DRV_VIDEO_FRAME_S *pstFrmTmp = NULL;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstFrame);
    WinCheckWindow(hWin, pstWin);
    DISP_MEMSET(pstFrame, 0, sizeof(HI_DRV_VIDEO_FRAME_S));

    pstFrmTmp = WinBuf_GetDisplayedFrame(&pstWin->stBuffer.stWinBP);
    if (NULL == pstFrmTmp)
    {
        if (pstWin->latest_display_frame_valid)
        {
            *pstFrame = pstWin->latest_display_frame;
        }
        else
        {
            return HI_FAILURE;
        }
    }
    else
    {
        *pstFrame = *(pstFrmTmp);
        pstWin->latest_display_frame = *(pstFrmTmp);
        pstWin->latest_display_frame_valid = 1;
    }

    return HI_SUCCESS;
}

HI_S32 WinProcessFrameToSP420(HI_DRV_VIDEO_FRAME_S *pstFrame, HI_U32 u32DstSmmuAddr, WIN_EXTERN_S *pstExtern)
{
    HI_S32 s32Ret = HI_FAILURE;

    WIN_AcqCaptureFrame( pstFrame, u32DstSmmuAddr, pstFrame->stBufAddr[0].u32Stride_Y, pstFrame->u32Width, pstFrame->u32Height);
    WIN_EXTERN_Init(pstExtern);
    WIN_EXTERN_SetAttr(pstExtern, pstFrame->u32Width, pstFrame->u32Height);
    WIN_EXTERN_VPSS_Start(pstExtern);
    s32Ret = WIN_EXTERN_WaitForFinish(100);

    WIN_EXTERN_DeInit(pstExtern);
    return s32Ret;
}

HI_VOID WinTransforOneLineU10To8Bit(HI_U8 *pInAddr, HI_U32 u32Width, HI_U8 *pOutAddr, HI_U8  *pu8TempBuffer)
{
    HI_U32 i = 0, j = 0, u32Cnt = 0;
    HI_U8  *pTmpMem = HI_NULL;

    pTmpMem = pInAddr;
    u32Cnt = HICEILING(u32Width, 4);

    for (i = 0; i < u32Cnt; i++)
    {
        for (j = 0; j < 5; j++)
        {
            pu8TempBuffer[j] = *(pTmpMem + i * 5 + j);
        }
        *pOutAddr = ((pu8TempBuffer[2] << 4) & 0xf0) | ((pu8TempBuffer[1] >> 4) & 0x0f);
        pOutAddr++;
        *pOutAddr = pu8TempBuffer[4] & 0xff;
        pOutAddr++;
    }

    return ;
}

HI_VOID WinTransforOneLineV10To8Bit( HI_U8 *pInAddr, HI_U32 u32Width, HI_U8 *pOutAddr, HI_U8  *pu8TempBuffer)
{
    HI_U32 i = 0, j = 0, u32Cnt = 0;
    HI_U8  *pTmpMem = HI_NULL;

    pTmpMem = pInAddr;
    u32Cnt = HICEILING(u32Width, 4);

    for (i = 0; i < u32Cnt; i++)
    {
        for (j = 0; j < 5; j++)
        {
            pu8TempBuffer[j] = *(pTmpMem + i * 5 + j);
        }
        *pOutAddr = ((pu8TempBuffer[1] << 6) & 0xc0) | ((pu8TempBuffer[0] >> 2) & 0x3f);
        pOutAddr++;
        *pOutAddr = ((pu8TempBuffer[3] << 2) & 0xfc) | ((pu8TempBuffer[2] >> 6) & 0x03);
        pOutAddr++;
    }

    return ;
}

HI_VOID WinTransforOneLineY10bitToY8bit(HI_U8 *pu8InY10data,  HI_U8 *pu8OutY8data, HI_U32 u32Stride,  HI_U32 u32Width, HI_U8 *pTempBuffer)
{
    HI_U32 i = 0, j = 0, u32Temp = 0;

    for (i = 0; i < u32Stride; i++)
    {
        for (j = 0; j < 8; j++)
        {
            pTempBuffer[i * 8 + j] = (pu8InY10data[i] >> j) & 0x1;
        }
    }
    for (i = 0; i < u32Width; i++)
    {
        u32Temp = 0;
        for (j = 0; j < 8; j++)
        {
            u32Temp |= pTempBuffer[i * 10 + j + 2] << j;
        }
        pu8OutY8data[i] = u32Temp;
    }

    return ;
}

HI_VOID  WinWriteuv420ToBuffer(HI_U8 *pu8bufferAddress, HI_U8 *pu8VAddress, HI_U8 *pu8UAddress, HI_U32 u32DataLen)
{
    HI_U32 i = 0;
    HI_U32 j = 0;

    for (i = 0; i < u32DataLen; i++)
    {
        pu8bufferAddress[j] = pu8VAddress[i];
        j++;
        pu8bufferAddress[j] = pu8UAddress[i];
        j++;
    }

    return ;
}

HI_S32 WinCapture420Frame10bitTransforTo8bit(HI_DRV_VIDEO_FRAME_S *pstFrame, DISP_MMZ_BUF_S *pstSrcmem)
{
    HI_U32  u32Ystride = 0, u32Cstride = 0, u32Height = 0, u32Width = 0, i = 0, u32Datalen = 0;
    HI_U8  *pYStartAddress = HI_NULL;
    DISP_MMZ_BUF_S        stWinCaptureMMZ = {0};
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 *pu8TempAddr = HI_NULL;

    if (pstFrame->ePixFormat != HI_DRV_PIX_FMT_NV21)
    {
        WIN_ERROR("ePixFormat not support\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    u32Height =  pstFrame->u32Height;
    u32Width = pstFrame->u32Width;
    u32Ystride = pstFrame->stBufAddr[0].u32Stride_Y;
    u32Cstride = pstFrame->stBufAddr[0].u32Stride_C;
    u32Datalen =  u32Width + 10 * u32Ystride;
    stWinCaptureMMZ.u32Size = u32Datalen + BUFFER_LEN_4K;

    if (HI_SUCCESS != DISP_OS_MMZ_Alloc("VDP_Cpefun", VDP_MEM_TYPE_MMZ, u32Datalen, VDP_MEM_ALIGN, &stWinCaptureMMZ))
    {
        WIN_ERROR("Malloc mem failed!\n");
        return HI_ERR_VO_MALLOC_FAILED;
    }

    s32Ret = DISP_OS_MMZ_Map(&stWinCaptureMMZ);
    if (s32Ret != HI_SUCCESS)
    {
        DISP_OS_MMZ_Release(&stWinCaptureMMZ);
        WIN_ERROR("Map VDP_Cpefun Failed\n");
        return s32Ret;
    }

    pYStartAddress = pstSrcmem->pu8StartVirAddr;
    pu8TempAddr = stWinCaptureMMZ.pu8StartVirAddr;

    for (i = 0; i < u32Height; i++)
    {
        WinTransforOneLineY10bitToY8bit(pYStartAddress , pYStartAddress/*pu8TempAddr*/, u32Ystride, u32Width, pu8TempAddr + u32Width);
        pYStartAddress += u32Ystride;
    }

    for (i = 0; i < u32Height / 2; i++)
    {
        WinTransforOneLineV10To8Bit(pYStartAddress, u32Width , pu8TempAddr, pu8TempAddr + u32Datalen);
        WinTransforOneLineU10To8Bit(pYStartAddress, u32Width, pu8TempAddr + u32Width / 2, pu8TempAddr + u32Datalen);
        WinWriteuv420ToBuffer(pYStartAddress, pu8TempAddr,  pu8TempAddr + u32Width / 2, u32Width / 2);
        pYStartAddress += u32Ystride;
    }

    DISP_OS_MMZ_UnMap(&stWinCaptureMMZ);
    DISP_OS_MMZ_Release(&stWinCaptureMMZ);

    return HI_SUCCESS;
}

HI_S32 WinGetOutputCaptureFrame(HI_DRV_VIDEO_FRAME_S *pstFrame, DISP_MMZ_BUF_S *pstDstMem)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32   u32Ystride = 0,  u32Height = 0;
    HI_DRV_VIDEO_PRIVATE_S *pstPrivInfo = HI_NULL;

    u32Ystride = pstFrame->stBufAddr[0].u32Stride_Y;
    u32Height   = pstFrame->u32Height;

    s32Ret = DISP_OS_MMZ_Map(pstDstMem);
    if (s32Ret != HI_SUCCESS)
    {
        WIN_ERROR("Map VDP_Cpefun Failed\n");
        return s32Ret;
    }

    if ((HI_DRV_PIXEL_BITWIDTH_10BIT == pstFrame->enBitWidth ) &&
        ( (HI_DRV_PIX_FMT_NV21 == pstFrame->ePixFormat) || (HI_DRV_PIX_FMT_NV12 == pstFrame->ePixFormat)))
    {
        DISP_MMZ_BUF_S stSrcMem = {0};
        stSrcMem.bSecure = HI_FALSE;
        stSrcMem.pu8StartVirAddr = 0;
        stSrcMem.u32StartPhyAddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;
        stSrcMem.u32Size = u32Height * u32Ystride * 3 / 2;

#ifdef CFG_VDP_MMU_SUPPORT
        stSrcMem.bSmmu = HI_TRUE;
#else
        stSrcMem.bSmmu = HI_FALSE;
#endif
        s32Ret = DISP_OS_MMZ_Map(&stSrcMem);
        if (s32Ret != HI_SUCCESS)
        {
            WIN_ERROR("Map Src Buffer Failed\n");
            DISP_OS_MMZ_UnMap(pstDstMem);
            return s32Ret;
        }

        memcpy(pstDstMem->pu8StartVirAddr,
               stSrcMem.pu8StartVirAddr,
               u32Height * u32Ystride * 3 / 2);

        s32Ret = WinCapture420Frame10bitTransforTo8bit(pstFrame, pstDstMem);
        DISP_OS_MMZ_UnMap(&stSrcMem);
    }
    else   if ((HI_DRV_PIXEL_BITWIDTH_8BIT == pstFrame->enBitWidth ) &&
               ( (HI_DRV_PIX_FMT_NV21 == pstFrame->ePixFormat) || (HI_DRV_PIX_FMT_NV12 == pstFrame->ePixFormat)))
    {
        DISP_MMZ_BUF_S stSrcMem = {0};

        stSrcMem.bSecure = HI_FALSE;
        stSrcMem.pu8StartVirAddr = 0;
        stSrcMem.u32StartPhyAddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;
        stSrcMem.u32Size = u32Height * u32Ystride * 3 / 2;
#ifdef CFG_VDP_MMU_SUPPORT
        stSrcMem.bSmmu = HI_TRUE;
#else
        stSrcMem.bSmmu = HI_FALSE;
#endif
        s32Ret = DISP_OS_MMZ_Map(&stSrcMem);
        if (s32Ret != HI_SUCCESS)
        {
            WIN_ERROR("Map Src Buffer Failed\n");
            DISP_OS_MMZ_UnMap(pstDstMem);

            return s32Ret;
        }

        memcpy(pstDstMem->pu8StartVirAddr,
               stSrcMem.pu8StartVirAddr,
               u32Height * u32Ystride * 3 / 2);
        DISP_OS_MMZ_UnMap(&stSrcMem);
    }
    else
    {
        HI_U8 *pu8TempMem =  HI_NULL;

        pu8TempMem = HI_KMALLOC(HI_ID_VO, sizeof(HI_DRV_VIDEO_FRAME_S) + sizeof(WIN_EXTERN_S), GFP_KERNEL);
        if (HI_NULL == pu8TempMem)
        {
            DISP_OS_MMZ_UnMap(pstDstMem);
            WIN_ERROR("Kmalloc frame struct failed!\n");
            return HI_ERR_VO_MALLOC_FAILED;
        }
        memset(pu8TempMem, 0x00, sizeof(HI_DRV_VIDEO_FRAME_S) + sizeof(WIN_EXTERN_S));
        pstPrivInfo = (HI_DRV_VIDEO_PRIVATE_S *)(pstFrame->u32Priv);
        pstPrivInfo->eColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
        memcpy(pu8TempMem, pstFrame, sizeof(HI_DRV_VIDEO_FRAME_S));

        /* hdr frame need vpss process as sdr frame. */
        WIN_POLICY_ReviseFrameHdrType((HI_DRV_VIDEO_FRAME_S *)pu8TempMem);
        s32Ret = WinProcessFrameToSP420((HI_DRV_VIDEO_FRAME_S *)pu8TempMem, pstDstMem->u32StartPhyAddr, (WIN_EXTERN_S *)(pu8TempMem + sizeof(HI_DRV_VIDEO_FRAME_S)));
        HI_KFREE(HI_ID_VO, pu8TempMem);
    }

    DISP_OS_MMZ_UnMap(pstDstMem);

    return s32Ret;
}

HI_S32 WinCaptureFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame, HI_U32 *stMMZPhyAddr, HI_U32 *stMMZlen)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_DRV_VIDEO_FRAME_S *pstFrm = HI_NULL;
    HI_U32 u32Datalen = 0;
    DISP_MMZ_BUF_S stDstMem = {0};
    HI_S32 s32Ret = HI_FAILURE;

    HI_U32 u32RetSize = 0;
    HI_DRV_PIXEL_BITWIDTH_E     enBitWidth;

    HI_U32 u32Height = 0;
    HI_U32 u32Width_Stride = 0;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstFrame);
    WinCheckNullPointer(stMMZPhyAddr);
    WinCheckNullPointer(stMMZlen);
    WinCheckWindow(hWin, pstWin);
    DISP_MEMSET(pstFrame, 0, sizeof(HI_DRV_VIDEO_FRAME_S));

    if (pstWin->enType == HI_DRV_WIN_VITUAL_SINGLE)
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    if (pstWin->u32WinCapMMZvalid )
    {
        WIN_FATAL("do not support continous capturing.\n");
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    if ( ((WIN_STATE_FREEZE == pstWin->enState)
          && (HI_DRV_WIN_SWITCH_BLACK == pstWin->stFrz.enFreezeMode))
         || ((HI_TRUE == pstWin->bReset)
             && (HI_DRV_WIN_SWITCH_BLACK == pstWin->stRst.enResetMode)))
    {
        pstFrm = BP_GetBlackFrameInfo();
    }
    else
    {
        s32Ret = WinBuf_SetCaptureFrame(&pstWin->stBuffer.stWinBP);
        if (HI_SUCCESS != s32Ret)
        {
            WIN_ERROR("get frame err\n");
            return s32Ret;
        }

        pstFrm = WinBuf_GetCapturedFrame(&pstWin->stBuffer.stWinBP);
        if (HI_NULL == pstFrm)
        {
            pstFrm = BP_GetBlackFrameInfo();
        }
    }

    if (HI_NULL == pstFrm)
    {
        WIN_ERROR("get null frame ptr\n");
        return HI_ERR_VO_BUFQUE_EMPTY;
    }

    *pstFrame = *(pstFrm);

    u32Height   = pstFrame->u32Height;
    enBitWidth  = pstFrame->enBitWidth;
    u32Width_Stride = pstFrame->stBufAddr[0].u32Stride_Y;

    if ((HI_DRV_PIXEL_BITWIDTH_8BIT != enBitWidth)
        && (HI_DRV_PIXEL_BITWIDTH_10BIT != enBitWidth))
    {
        WIN_ERROR("Unsupport BitWidth %d.\n", enBitWidth);
        return HI_FAILURE;
    }

    switch (pstFrame->ePixFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        {
            u32RetSize = u32Height * u32Width_Stride * 3 / 2;
            break;
        }

        case HI_DRV_PIX_FMT_NV61_2X1:
        {
            u32RetSize = u32Height * u32Width_Stride * 2;
            break;
        }

        case HI_DRV_PIX_FMT_NV21_CMP:
        {
            u32RetSize = u32Height * u32Width_Stride * 3 / 2 + 16 * u32Height * 3 / 2;
            break;
        }

        default:
        {
            WIN_ERROR("Unsupport BitWidth %d.\n", enBitWidth);
            return HI_FAILURE;
        }
    }

    u32Datalen = u32RetSize;

    if (HI_SUCCESS != DISP_OS_MMZ_Alloc("VDP_Cpefun", VDP_MEM_TYPE_MMZ, u32Datalen, VDP_MEM_ALIGN, &pstWin->stWinCaptureMMZ))
    {
        WinBuf_ReleaseCaptureFrame(&pstWin->stBuffer.stWinBP, pstFrame, HI_FALSE);
        return HI_ERR_VO_MALLOC_FAILED;
    }

    pstWin->u32WinCapMMZvalid  = 1;
    *stMMZPhyAddr = pstWin->stWinCaptureMMZ.u32StartPhyAddr;
    *stMMZlen      = pstWin->stWinCaptureMMZ.u32Size;
    stDstMem.bSecure = pstWin->stWinCaptureMMZ.bSecure;
    stDstMem.bSmmu = pstWin->stWinCaptureMMZ.bSmmu;
    stDstMem.u32Size = pstWin->stWinCaptureMMZ.u32Size;
    stDstMem.u32StartPhyAddr = pstWin->stWinCaptureMMZ.u32StartPhyAddr;
    stDstMem.pu8StartVirAddr = 0;

    s32Ret = WinGetOutputCaptureFrame(pstFrame, &stDstMem);
    if (s32Ret != HI_SUCCESS)
    {
        WinBuf_ReleaseCaptureFrame(&pstWin->stBuffer.stWinBP, pstFrame, pstWin->u32WinCapMMZvalid);
        DISP_OS_MMZ_Release(&pstWin->stWinCaptureMMZ);
        WIN_ERROR("Get Output  Capture Frame Failed\n");
    }

    return s32Ret;

}

HI_S32 WinReleaseCaptureFrame(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 Ret = HI_FAILURE;

    WinCheckDeviceOpen();
    WinCheckNullPointer(pstFrame);
    WinCheckWindow(hWin, pstWin);

    if (pstWin->enType == HI_DRV_WIN_VITUAL_SINGLE)
    {
        return HI_ERR_VO_WIN_UNSUPPORT;
    }

    Ret = WinBuf_ReleaseCaptureFrame(&pstWin->stBuffer.stWinBP, pstFrame, pstWin->u32WinCapMMZvalid);

    return Ret;
}

HI_S32 WinFreeCaptureMMZ(WINDOW_S *pstWin)
{
    if (pstWin->u32WinCapMMZvalid == 1)
    {
        DISP_OS_MMZ_Release(&pstWin->stWinCaptureMMZ);
        pstWin->stWinCaptureMMZ.u32StartPhyAddr = 0;
        pstWin->u32WinCapMMZvalid = 0;
    }
    else
    {
        WIN_ERROR("warning: when free mmz, null refcnt occurs.!\n");
        return HI_ERR_VO_INVALID_OPT;
    }

    return HI_SUCCESS;
}

HI_S32 WinFreeCaptureMMZBuf(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S *cap_frame)
{
    WINDOW_S *pstWin;

    WinCheckDeviceOpen();
    WinCheckWindow(hWin, pstWin);

    if (cap_frame->stBufAddr[0].u32PhyAddr_Y
        != pstWin->stWinCaptureMMZ.u32StartPhyAddr)
    {
        WIN_ERROR("capture release addr:%x,%x!\n", cap_frame->stBufAddr[0].u32PhyAddr_Y,
                  pstWin->stWinCaptureMMZ.u32StartPhyAddr);
        return HI_ERR_VO_INVALID_OPT;
    }

    return WinFreeCaptureMMZ(pstWin);

}

HI_S32 WinForceClearCapture(HI_HANDLE hWin)
{
    HI_DRV_VIDEO_FRAME_S *pstFrmTmp = NULL;
    WINDOW_S *pstWin = HI_NULL;
    HI_S32 Ret = HI_FAILURE;

    WinCheckDeviceOpen();
    WinCheckWindow(hWin, pstWin);

    pstFrmTmp = WinBuf_GetCapturedFrame(&pstWin->stBuffer.stWinBP);
    if (NULL != pstFrmTmp)
    {
        Ret = WinBuf_ReleaseCaptureFrame(&pstWin->stBuffer.stWinBP, pstFrmTmp, pstWin->u32WinCapMMZvalid);
        if (HI_SUCCESS != Ret)
        {
            return Ret;
        }
    }

    Ret = WinFreeCaptureMMZ(pstWin);

    return Ret;
}

HI_S32 WinCapturePause(HI_HANDLE hWin, HI_BOOL bCaptureStart)
{
    WINDOW_S *pstWin = HI_NULL, *pstWinAttach = HI_NULL;
    HI_S32 Ret = 0;
    HI_HANDLE  attach_handle = 0;

    WinCheckWindow(hWin, pstWin);

    if (bCaptureStart && ((pstWin->enState == WIN_STATE_PAUSE)
                          || (pstWin->enState == WIN_STATE_FREEZE)))
    {
        pstWin->bRestoreFlag = 0;
        return HI_SUCCESS;
    }

    if (pstWin->enType == HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE)
    {
        /*attach mode , need  pasue salve window too*/
        attach_handle = pstWin->hSlvWin;
        pstWinAttach = WinGetWindow(attach_handle);

        if (!pstWinAttach)
        {
            attach_handle = 0;
        }
    }
    else if (pstWin->enType == HI_DRV_WIN_ACTIVE_SINGLE)
    {
        /*not attach mode only need  pasue self window*/
        attach_handle = 0;
    }
    else if (pstWin->enType == HI_DRV_WIN_ACTIVE_SLAVE)
    {
        /*attach mode only    mce capture slave window*/
        attach_handle = 0;
    }

    if (bCaptureStart)
    {
        Ret = WIN_Pause(hWin, bCaptureStart);
        if (Ret != HI_SUCCESS)
        {
            return Ret;
        }

        if (attach_handle)
        {
            Ret = WIN_Pause(attach_handle, bCaptureStart);
            if (Ret != HI_SUCCESS)
            {
                (HI_VOID)WIN_Pause(hWin, !bCaptureStart);
                return Ret;
            }
        }

        pstWin->bRestoreFlag = 1;
    }
    else
    {
        if (pstWin->bRestoreFlag)
        {

            Ret = WIN_Pause(hWin, 0);
            if (attach_handle)
            {
                (HI_VOID)WIN_Pause(attach_handle, 0);
            }

            pstWin->bRestoreFlag = 0;

            if (Ret != HI_SUCCESS)
            {
                return Ret;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_SetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E enRotation)
{
    WINDOW_S *pstWin;
    HI_S32 t = 0;
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        pstWin->enRotation = enRotation;
        atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);

        while ( atomic_read(&pstWin->stCfg.bNewAttrFlag) )
        {
            DISP_MSLEEP(5);
            t++;
            if (t > 10)
            {
                break;
            }
        }

        if (atomic_read(&pstWin->stCfg.bNewAttrFlag) )
        {
            WIN_ERROR("WIN Set Attr timeout in %s\n", __FUNCTION__);
            return HI_ERR_VO_TIMEOUT;
        }
    }
    else
    {
        VIRTUAL_S *pstVirWindow;

        WinCheckVirWindow(hWin, pstVirWindow);

        pstVirWindow->enRotation = enRotation;

        WIN_VIR_SendAttrToSource(pstVirWindow);

    }

    return HI_SUCCESS;
}

HI_S32 WIN_GetRotation(HI_HANDLE hWin, HI_DRV_ROT_ANGLE_E *penRotation)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    WinCheckNullPointer(penRotation);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        *penRotation = pstWin->enRotation;
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        WinCheckVirWindow(hWin, pstVirWindow);
        *penRotation = pstVirWindow->enRotation;
    }
    return HI_SUCCESS;
}

HI_S32 WIN_SetFlip(HI_HANDLE hWin, HI_BOOL bHoriFlip, HI_BOOL bVertFlip)
{
    WINDOW_S *pstWin;
    HI_S32 t = 0;
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WinCheckWindow(hWin, pstWin);

        pstWin->bHoriFlip = bHoriFlip;
        pstWin->bVertFlip = bVertFlip;

        atomic_set(&pstWin->stCfg.bNewAttrFlag, 1);
        while ( atomic_read(&pstWin->stCfg.bNewAttrFlag) )
        {
            DISP_MSLEEP(5);
            t++;
            if (t > 10)
            {
                break;
            }
        }

        if (atomic_read(&pstWin->stCfg.bNewAttrFlag) )
        {
            WIN_ERROR("WIN Set Attr timeout in %s\n", __FUNCTION__);
            return HI_ERR_VO_TIMEOUT;
        }
    }
    else
    {
        VIRTUAL_S *pstVirWindow;

        WinCheckVirWindow(hWin, pstVirWindow);

        pstVirWindow->bHoriFlip = bHoriFlip;
        pstVirWindow->bVertFlip = bVertFlip;

        WIN_VIR_SendAttrToSource(pstVirWindow);
    }
    return HI_SUCCESS;
}

HI_S32 WIN_GetFlip(HI_HANDLE hWin, HI_BOOL *pbHoriFlip, HI_BOOL *pbVertFlip)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();

    WinCheckNullPointer(pbHoriFlip);
    WinCheckNullPointer(pbVertFlip);

    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        *pbHoriFlip = pstWin->bHoriFlip;
        *pbVertFlip = pstWin->bVertFlip;
    }
    else
    {
        VIRTUAL_S *pstVirWindow;
        WinCheckVirWindow(hWin, pstVirWindow);
        *pbHoriFlip = pstVirWindow->bHoriFlip;
        *pbVertFlip = pstVirWindow->bVertFlip;
    }
    return HI_SUCCESS;
}

HI_S32 WIN_SetFrostMode(HI_HANDLE hWin, HI_DRV_WINDOW_FROST_E eWinFrostMode)
{
    HI_BOOL bVirtual;
    WINDOW_S *pstWin = HI_NULL;

    WinCheckDeviceOpen();

    bVirtual = WinCheckVirtual(hWin);
    if (HI_TRUE == bVirtual)
    {
        return HI_ERR_VO_INVALID_OPT;
    }

    WinCheckWindow(hWin, pstWin);

    if (HI_DRV_DISPLAY_0 == pstWin->enDisp)
    {
        pstWin->enWinFrostMode = HI_DRV_WINDOW_FROST_CLOSE;
    }
    else
    {
        pstWin->enWinFrostMode = eWinFrostMode;

        if ((HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == WinGetType(pstWin))
            && (pstWin->hSlvWin))
        {
            WINDOW_S *pstSlaveWin = HI_NULL;
            WinCheckWindow(pstWin->hSlvWin, pstSlaveWin);
            pstSlaveWin->enWinFrostMode = HI_DRV_WINDOW_FROST_CLOSE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 WIN_GetFrostMode(HI_HANDLE hWin, HI_DRV_WINDOW_FROST_E *peWinFrostMode)
{
    HI_BOOL bVirtual;
    WINDOW_S *pstWin = HI_NULL;

    WinCheckDeviceOpen();
    WinCheckNullPointer(peWinFrostMode);

    bVirtual = WinCheckVirtual(hWin);
    if (HI_TRUE == bVirtual)
    {
        return HI_ERR_VO_INVALID_OPT;
    }

    WinCheckWindow(hWin, pstWin);
    *peWinFrostMode = pstWin->enWinFrostMode;

    return HI_SUCCESS;
}

HI_S32 WIN_GetUnload(HI_HANDLE hWin, HI_U32 *pu32Times)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();

    WinCheckNullPointer(pu32Times);
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        *pu32Times = pstWin->stBuffer.u32UnderLoad;
    }
    else
    {
        *pu32Times = 0;
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return HI_SUCCESS;
}

HI_S32 WIN_SetWindowAlpha(HI_HANDLE hWin, HI_U32 u32Alpha)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        pstWin->stCfg.u32Alpha = u32Alpha;
    }

    return HI_SUCCESS;
}


HI_S32 WIN_GetWindowAlpha(HI_HANDLE hWin, HI_U32 *pu32Alpha)
{
    HI_BOOL bVirtual;
    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        *pu32Alpha = pstWin->stCfg.u32Alpha;
    }
    else
    {
        *pu32Alpha = 0;
        return HI_ERR_VO_WIN_UNSUPPORT;
    }
    return HI_SUCCESS;
}
HI_S32 WinDebugCmdProcess(WIN_DEBUG_CMD_AND_ARGS_S *pstDebugCmd)
{
    HI_S32 s32Ret = HI_SUCCESS;

    WinCheckNullPointer(pstDebugCmd);
#ifdef VDP_DOLBY_HDR_SUPPORT
    switch (pstDebugCmd->enDebugCmd)
    {
        case WIN_DEBUG_SET_HISI_HDR_PATH:
        {
            HI_BOOL  *pbEnable = (HI_BOOL *)pstDebugCmd->u8Args;
            s32Ret = WIN_SetHisiPath(pstDebugCmd->hWindow, *pbEnable);
            break;
        }
        default:
        {
            s32Ret = HI_ERR_VO_WIN_UNSUPPORT;
            break;
        }
    }
#endif
    return s32Ret;
}

HI_S32 WinSetFirstFrmOutStatus(HI_HANDLE hWin, WIN_FIRST_FRAME_STATUS_S *pstFirstFrmStatus)
{
    HI_BOOL bVirtual = HI_FALSE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    WinCheckNullPointer(pstFirstFrmStatus);

    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        pstWin->stCfg.stFirstFrmStatus.bSenceChange = pstFirstFrmStatus->bSenceChange;
        pstWin->stCfg.stFirstFrmStatus.enDispOutType = pstFirstFrmStatus->enDispOutType;
        pstWin->stCfg.stFirstFrmStatus.enOutColorSpace = pstFirstFrmStatus->enOutColorSpace;
    }
    /* not support virtual window currently. */

    return HI_SUCCESS;
}

HI_S32 WinGetFirstFrmOutStatus(HI_HANDLE hWin, WIN_FIRST_FRAME_STATUS_S *pstFirstFrmStatus)
{
    HI_BOOL bVirtual = HI_FALSE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);
    WinCheckNullPointer(pstFirstFrmStatus);

    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        pstFirstFrmStatus->bSenceChange = pstWin->stCfg.stFirstFrmStatus.bSenceChange;
        pstFirstFrmStatus->enDispOutType = pstWin->stCfg.stFirstFrmStatus.enDispOutType;
        pstFirstFrmStatus->enOutColorSpace = pstWin->stCfg.stFirstFrmStatus.enOutColorSpace;
    }

    /* not support virtual window currently. */
    return HI_SUCCESS;

}

HI_S32 WinResetFirstFrameStatus(HI_HANDLE hWin)
{
    HI_BOOL bVirtual = HI_FALSE;

    WinCheckDeviceOpen();
    bVirtual = WinCheckVirtual(hWin);

    if (!bVirtual)
    {
        WINDOW_S *pstWin;
        WinCheckWindow(hWin, pstWin);
        pstWin->stCfg.stFirstFrmStatus.bSenceChange = HI_FALSE;
        pstWin->stCfg.stFirstFrmStatus.enDispOutType = HI_DRV_DISP_TYPE_NORMAL;
        pstWin->stCfg.stFirstFrmStatus.enOutColorSpace = HI_DRV_CS_UNKNOWN;
    }

    /* not support virtual window currently. */
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */




