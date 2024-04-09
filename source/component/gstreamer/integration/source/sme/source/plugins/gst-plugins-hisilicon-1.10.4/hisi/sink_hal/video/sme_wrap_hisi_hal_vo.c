/**************************************************************************//**

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

 ******************************************************************************
 * @file    sme_wrap_hisi_hal_vo.cpp
 * @brief   android hisi37xx vdec&vdisppipe
 * @author  lidanjing(l00346954)
 * @date    2015/12/4
 * @version VFP xxxxxxxxx
 * History:
 *
 * Number : V1.00
 * Date   : 2015/12/4
 * Author : lidanjing(l00346954)
 * Desc   : Created file
 *
******************************************************************************/

//lint -e1784
//lint -e717
//lint -e414 //division by 0

#include <math.h>
#include <gst/gst.h>

#ifndef LINUX_OS
#include "hardware.h"
#endif

#include "securec.h"
#include "sme_wrap_hisi_hal_vo.h"

#define VIRTUAL_SCREEN_WIDTH 1280
#define VIRTUAL_SCREEN_HEIGHT 720

#define DEQUEUE_TIMEOUT 3   //ms
#define HI_ERR_VO_BUFQUE_FULL               (HI_S32)(0x80110052)

#ifndef SMEPLAYER_STAT_TAG_TIME
#define SMEPLAYER_STAT_TAG_TIME "PlayerTimeLineTrace"
#endif

#define ICS_FAIL 1
#define ICS_SUCCESS 0

#define M_SME_MS_TO_NS   1000000
#define M_SME_SEC_TO_MS  1000
#define M_SME_MS_TO_US   1000

#define FLOAT_IS_EAQUAL(a,b) ((fabs (a-b) < 0.000001 ) ? 1 : 0)
#define FLOAT_IS_EAQUAL_ZERO(a) ((fabs (a) < 0.000001 ) ? 1 : 0)




SME_HAL_VDISP_PIPE_HDL SME_Hal_VDisp_Create(void)
{
    ST_SME_HAL_HI_VDISP_PIPE * pstPipe;
//lint -e10
    pstPipe = (ST_SME_HAL_HI_VDISP_PIPE*)g_malloc(sizeof(ST_SME_HAL_HI_VDISP_PIPE));
//lint +e10
    if(pstPipe == NULL)
    {
        GST_ERROR("malloc ST_SME_HAL_HI_VDISP_PIPE failed");
        return NULL;
    }
    pstPipe->phVout = HI_INVALID_HANDLE;
    pstPipe->phVoutWindow = HI_INVALID_HANDLE;
    pstPipe->pstVoutDev = NULL;
    //pstPipe->pstVoutDev = (VOUT_DEVICE_S*)malloc(sizeof(VOUT_DEVICE_S));
    //if(pstPipe->pstVoutDev == NULL)
    //{
    //    ICS_LOGE("malloc VOUT_DEVICE_S failed");
    //    free(pstPipe);
    //    return NULL;
    //}

    return (SME_HAL_VDISP_PIPE_HDL)pstPipe;

}

void SME_Hal_VDisp_Destory(IN SME_HAL_VDISP_PIPE_HDL hdlPipe)
{
    ST_SME_HAL_HI_VDISP_PIPE* pstPipe  = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    if(pstPipe == NULL)
        return;

    //if(pstPipe->pstVoutDev != NULL)
    //{
    //    free(pstPipe->pstVoutDev);
    //    pstPipe->pstVoutDev = NULL;
    //}

    g_free(pstPipe);

    return;
}

guint32 SME_Hal_VDisp_Init(IN SME_HAL_VDISP_PIPE_HDL hdlPipe)
{
    guint32 u32Ret                     = ICS_SUCCESS;
    ST_SME_HAL_HI_VDISP_PIPE* pstPipe  = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
#ifndef LINUX_OS
    hw_module_t const* module;
#endif
    S32 s32Ret;
    GST_WARNING("%s:VDisp_Init in...", SMEPLAYER_STAT_TAG_TIME);

    do
    {
        if(NULL == pstPipe)
        {
            GST_ERROR("invalid hdl!");
            return ICS_FAIL;
        }

        HI_SYS_Init();

#ifndef LINUX_OS

        if (hw_get_module(VOUT_HARDWARE_MODULE_ID, &module) != 0)
        {
            GST_ERROR("%s module not found!",  VOUT_HARDWARE_MODULE_ID);
            return ICS_FAIL;
        }

        /* HAL视频输出模块初始化 */
        s32Ret = vout_open(module, &pstPipe->pstVoutDev);
        if(s32Ret != SUCCESS)
        {
            HI_SYS_DeInit();
            GST_ERROR("open VoutDev failed");
            return ICS_FAIL;
        }
#else
        pstPipe->pstVoutDev = getVoutDevice();
        if (NULL == pstPipe->pstVoutDev)
        {
            HI_SYS_DeInit();
            GST_ERROR("open VoutDev failed");
            return ICS_FAIL;
        }
#endif

        /*init video output device. ps:VOUT_INIT_PARAMS_S not used,so set NULL is ok*/
        s32Ret = pstPipe->pstVoutDev->vout_init(pstPipe->pstVoutDev, NULL);
        if(s32Ret != SUCCESS)
        {
#ifndef LINUX_OS
            vout_close(pstPipe->pstVoutDev);
#endif
            HI_SYS_DeInit();
            GST_ERROR("init VoutDev failed");
            return ICS_FAIL;
        }

        /* 打开一个视频输出实例,VOUT_OPEN_PARAMS_S not used ,so set NULL is OK  */
        s32Ret = pstPipe->pstVoutDev->vout_open_channel(pstPipe->pstVoutDev, &pstPipe->phVout, NULL);
        if(s32Ret != SUCCESS)
        {
#ifndef LINUX_OS
            vout_close(pstPipe->pstVoutDev);
#endif
            HI_SYS_DeInit();
            GST_ERROR("open VoutDev instance failed");
            return ICS_FAIL;
        }

        /* 创建一个窗口 */
        s32Ret = pstPipe->pstVoutDev->vout_window_create(pstPipe->pstVoutDev, pstPipe->phVout, &pstPipe->phVoutWindow, NULL);
        if(s32Ret != SUCCESS)
        {
            pstPipe->pstVoutDev->vout_close_channel(pstPipe->pstVoutDev, pstPipe->phVout, NULL);
#ifndef LINUX_OS
            vout_close(pstPipe->pstVoutDev);
#endif
            HI_SYS_DeInit();
            GST_ERROR("create VoutDev windows failed");
            return ICS_FAIL;
        }

#ifndef LINUX_OS
        U32 hSrc = (U32)SME_ID_USER << 16;
        s32Ret = pstPipe->pstVoutDev->vout_window_attach_input(pstPipe->pstVoutDev, pstPipe->phVoutWindow, hSrc);
#else
        /* 将窗口enable */
        s32Ret = pstPipe->pstVoutDev->vout_window_unmute(pstPipe->pstVoutDev, pstPipe->phVoutWindow);
#endif
        if(s32Ret != SUCCESS)
        {
            pstPipe->pstVoutDev->vout_window_destroy(pstPipe->pstVoutDev, pstPipe->phVout, pstPipe->phVoutWindow, NULL);
            pstPipe->pstVoutDev->vout_close_channel(pstPipe->pstVoutDev, pstPipe->phVout, NULL);
#ifndef LINUX_OS
            vout_close(pstPipe->pstVoutDev);
#endif
            HI_SYS_DeInit();
            GST_ERROR("enable VoutDev windows failed");
            return ICS_FAIL;
        }

#ifndef LINUX_OS
        s32Ret = pstPipe->pstVoutDev->vout_window_unmute(pstPipe->pstVoutDev, pstPipe->phVoutWindow);
        if(s32Ret != SUCCESS)
        {
            GST_ERROR("SME_Hal_VDisp_Init vout_window_unmute failed");
        }
#endif

        pstPipe->u64FrameIdx = 0;
        pstPipe->u64DeqFailNum = 0;

    }while(FALSE);

    GST_WARNING("%s:VDisp_Init out(%d)", SMEPLAYER_STAT_TAG_TIME, u32Ret);
    return u32Ret;
}

guint32 SME_Hal_VDisp_DeInit(IN SME_HAL_VDISP_PIPE_HDL hdlPipe)
{
    guint32 u32Ret                     = ICS_SUCCESS;
    ST_SME_HAL_HI_VDISP_PIPE* pstPipe  = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    S32 s32Ret;

    GST_WARNING("%s:VDisp_Init in...", SMEPLAYER_STAT_TAG_TIME);

    if(pstPipe == NULL || pstPipe->pstVoutDev== NULL)
        return u32Ret;

    GST_WARNING("SME_Hal_VDisp_DeInit in...");
    if(pstPipe->phVoutWindow)
    {
        /*disable windows*/
#ifndef LINUX_OS
        U32 hSrc = (U32)SME_ID_USER << 16;
        s32Ret = pstPipe->pstVoutDev->vout_window_detach_input(pstPipe->pstVoutDev, pstPipe->phVoutWindow, hSrc);
        if(s32Ret == FAILURE)
        {
            GST_ERROR("vout_window_detach_input failed");
            //return ICS_FAIL;
        }
#else
        GST_WARNING("disable vout_windows");
        s32Ret = pstPipe->pstVoutDev->vout_window_mute(pstPipe->pstVoutDev, pstPipe->phVoutWindow);
        if(s32Ret == FAILURE)
        {
            GST_ERROR("vout_window_mute failed");
            return ICS_FAIL;
        }
#endif

        GST_WARNING("destory vout_windows");
        /*destory windows*/
        s32Ret = pstPipe->pstVoutDev->vout_window_destroy(pstPipe->pstVoutDev, 0, pstPipe->phVoutWindow, NULL);
        if(s32Ret == FAILURE)
        {
            GST_ERROR("vout_window_destroy failed,maybe not use vout_window_detach_input");
            return ICS_FAIL;
        }
    }

#if 1 //#ifdef LINUX_OS
    GST_WARNING("close channel in");
    if(pstPipe->phVout != (HANDLE)NULL)
    {
        /* close channel */
        GST_ERROR("real close channel in");
        s32Ret = pstPipe->pstVoutDev->vout_close_channel(pstPipe->pstVoutDev, pstPipe->phVout, NULL);
        //s32Ret = pstPipe->pstVoutDev->vout_close_channel(pstPipe->pstVoutDev, NULL, NULL);
        if(s32Ret == FAILURE)
        {
            GST_ERROR("vout_close_channel failed");
            return ICS_FAIL;
        }
    }

#endif
#ifndef LINUX_OS
    GST_WARNING("vout_close in");
    s32Ret = vout_close(pstPipe->pstVoutDev);
    if(s32Ret == FAILURE)
    {
        GST_ERROR("vout_close failed");
        return ICS_FAIL;
    }
#endif

    GST_WARNING("HI_SYS_DeInit in");
    HI_SYS_DeInit();
    GST_WARNING("HI_SYS_DeInit out");

    GST_WARNING("%s:VDisp_Init out(%d)", SMEPLAYER_STAT_TAG_TIME, u32Ret);

    return u32Ret;

}
//lint -e58
guint32 SME_Hal_VDisp_Updata_OutRect(IN SME_HAL_VDISP_PIPE_HDL hdlPipe, const ST_SME_DISP_RECT * pstRect)
{
    ST_SME_HAL_HI_VDISP_PIPE* pstPipe  = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    S32 s32Ret;

	if(NULL == pstPipe
        || (HANDLE)NULL == pstPipe->phVoutWindow
        || (HANDLE)NULL == pstPipe->pstVoutDev || NULL == pstRect)
	{
	    GST_ERROR("invalid hdl!");
        return ICS_FAIL;
	}

    GST_WARNING("%s:set_output_rect begin...:x=%d，y=%d, width =%d, height=%d",
        SMEPLAYER_STAT_TAG_TIME, pstRect->i32StartX, pstRect->i32StartY,
        pstRect->i32Width, pstRect->i32Height);
    s32Ret = pstPipe->pstVoutDev->vout_window_set_output_rect(pstPipe->pstVoutDev, pstPipe->phVoutWindow,
        (guint32)pstRect->i32StartX, (guint32)pstRect->i32StartY, (guint32)pstRect->i32Width, (guint32)pstRect->i32Height);
    GST_WARNING("%s:set_output_rect, end(%x)", SMEPLAYER_STAT_TAG_TIME, s32Ret);

    if(SUCCESS == s32Ret)
    {
        GST_WARNING("set vout_window_set_output_rect:[%d %d %d %d] succeed",pstRect->i32StartX, pstRect->i32StartY,
            pstRect->i32Width, pstRect->i32Height);
        return ICS_SUCCESS;
    }
    else
    {
        GST_WARNING("set vout_window_set_output_rect:[%d %d %d %d] failed,err:%d",pstRect->i32StartX, pstRect->i32StartY,
            pstRect->i32Width, pstRect->i32Height, s32Ret);
        return ICS_FAIL;
    }

}
//lint +e58

static void SME_SetVoutFrameInfoDefaultValue(const ST_SME_HAL_HI_VDISP_PIPE* pstHalPipe,
    VOUT_FRAME_INFO_S* pstFrame, guint32 u32W, guint32 u32H,
    guint32 u32PhyAddr, guint32 u32Duration, IN gboolean bUseTvp)
{
    guint32 u32StrW = (u32W + 0xF) & 0xFFFFFFF0UL;
    gint iMemSecRet;

    iMemSecRet = memset_s(pstFrame, sizeof(VOUT_FRAME_INFO_S), 0, sizeof(VOUT_FRAME_INFO_S));
    if(iMemSecRet != 0){
        GST_ERROR("init pstFrame failed,ret:%d", iMemSecRet);
        return;
    }

    pstFrame->u32FrameIndex                = (U32)pstHalPipe->u64FrameIdx;
    pstFrame->stVideoFrameAddr[0].u32YAddr = u32PhyAddr;
    pstFrame->stVideoFrameAddr[0].u32CAddr = u32PhyAddr + u32StrW * u32H;
    //pstFrame->stVideoFrameAddr[0].u32CrAddr = u32PhyAddr + u32StrW * u32H;

    pstFrame->stVideoFrameAddr[0].u32YStride = u32StrW;
    pstFrame->stVideoFrameAddr[0].u32CStride = u32StrW;
    pstFrame->stVideoFrameAddr[0].u32CrStride = u32StrW;
    pstFrame->u32Width                  = u32W;
    pstFrame->u32Height                 = u32H;
#ifndef LINUX_OS
    pstFrame->u32SrcPts                 = (U32) - 1;
    pstFrame->u32Pts                    = (U32) - 1;
#else
    pstFrame->s64SrcPts                 = - 1;
    pstFrame->s64Pts                    = - 1;
#endif
    pstFrame->u32AspectWidth            = 0;
    pstFrame->u32AspectHeight           = 0;
    if(u32Duration != 0)
    {
        pstFrame->stFrameRate.u32fpsInteger = M_SME_SEC_TO_MS / u32Duration;
        pstFrame->stFrameRate.u32fpsDecimal
            = (M_SME_SEC_TO_MS * M_SME_MS_TO_US ) / u32Duration
            - pstFrame->stFrameRate.u32fpsInteger * M_SME_MS_TO_US;
    }
    else
    {
        pstFrame->stFrameRate.u32fpsInteger = 60;
        pstFrame->stFrameRate.u32fpsDecimal = 0;
        GST_WARNING("use default fps:60.0");
    }
    //ICS_LOGW("use1 fps:%u:%u",
    //    pstFrame->stFrameRate.u32fpsInteger, pstFrame->stFrameRate.u32fpsDecimal);

    //pstFrame->stFrameRate.u32fpsInteger = 50;
    //pstFrame->stFrameRate.u32fpsDecimal = 0;
    //ICS_LOGW("use fps2:%u:%u",
    //    pstFrame->stFrameRate.u32fpsInteger, pstFrame->stFrameRate.u32fpsDecimal);

    //pstFrame->enVideoFormat             = VOUT_FORMAT_YUV_SEMIPLANAR_420;
    pstFrame->enVideoFormat             = VOUT_FORMAT_YUV_SEMIPLANAR_420_UV;

    pstFrame->bProgressive              = FALSE;//HI_TRUE;
    pstFrame->enFieldMode               = VOUT_VIDEO_FIELD_TOP;//HI_UNF_VIDEO_FIELD_BUTT;
    pstFrame->bTopFieldFirst            = FALSE;//HI_TRUE;
    pstFrame->enFramePackingType        = VOUT_FRAME_PACKING_TYPE_NONE;
    pstFrame->u32Circumrotate           = 0;
    pstFrame->bVerticalMirror           = FALSE;
    pstFrame->bHorizontalMirror         = FALSE;

    pstFrame->u32DisplayCenterX         = (U32)(u32W >> 1);
    pstFrame->u32DisplayCenterY         = (U32)(u32H >> 1);
    pstFrame->u32DisplayWidth           = (U32)u32W;
    pstFrame->u32DisplayHeight          = (U32)u32H;
    pstFrame->u32ErrorLevel             = 0;

    if (bUseTvp)
    {
        pstFrame->bSecurityFrame = TRUE;
        GST_DEBUG("set bSecurityFrame to TRUE for tvp");
    }
    else
    {
        pstFrame->bSecurityFrame = FALSE;
    }

    return;
}

void* SME_Hal_Get_VirAddr_From_PhyAddr(void* pVirAddr)
{
    guint32   u32Len       = 0;
    HI_S32    i32GetPhyErr = HI_SUCCESS;
    guint32   u32PhyAddr   = 0;

    if(NULL == pVirAddr)
    {
        GST_ERROR("viraddr is NULL, error!");
        return NULL;
    }
    i32GetPhyErr = HI_MMZ_GetPhyaddr(pVirAddr, &u32PhyAddr, &u32Len);
    if(HI_SUCCESS != i32GetPhyErr)
    {
        GST_ERROR("HI_MMZ_GetPhyaddr failed:pvAddr=%p, u32PhyAddr=%p, u32Len=%u", pVirAddr, u32PhyAddr, u32Len);
        return NULL;
    }
    return (void*)(u32PhyAddr);
}

E_SME_HIVO_ERR SME_Hal_VDisp_QueueFrame(IN SME_HAL_VDISP_PIPE_HDL hdlPipe,
    IN const ST_SME_VIDEO_FRAME* pstVideoFrame,
    IN gboolean bUseTvp)
{
    E_SME_HIVO_ERR                  eRet            = E_SME_HIVO_ERR_NONE;
    ST_SME_HAL_HI_VDISP_PIPE*       pstPipe         = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    guint32                         u32PhyAddr      = 0;
    S32                             s32Err;
    HI_S32                          i32GetPhyErr    = HI_SUCCESS;
    guint32                         u32Len          = 0;
    VOUT_FRAME_INFO_S               stVoutFrame;

	if(NULL == pstPipe || NULL == pstVideoFrame || NULL == pstVideoFrame->pvAddr[0])
	{
	    GST_ERROR("SME_HiVO_QueueFrame:invalid args!");
        return E_SME_HIVO_ERR_INVALID_ARGS;
	}

    if (bUseTvp)
    {
        u32PhyAddr = (guint32)pstVideoFrame->pvAddr[0];
        u32Len = pstVideoFrame->u32Len;
    }
    else
    {
        i32GetPhyErr = HI_MMZ_GetPhyaddr(pstVideoFrame->pvAddr[0], &u32PhyAddr, &u32Len);
    }

    if(HI_SUCCESS != i32GetPhyErr)
    {
        GST_ERROR("HI_MMZ_GetPhyaddr:pvAddr=%p, u32Len=%u", pstVideoFrame->pvAddr[0], u32Len);
        return E_SME_HIVO_ERR_FATAL;
    }

    pstPipe->u64FrameIdx++;

    SME_SetVoutFrameInfoDefaultValue(pstPipe, &stVoutFrame, pstVideoFrame->u32Width,
         pstVideoFrame->u32Height, u32PhyAddr, pstVideoFrame->u32Duration, bUseTvp);

    s32Err = pstPipe->pstVoutDev->vout_window_queue_frame(pstPipe->pstVoutDev, pstPipe->phVoutWindow, &stVoutFrame);

    if (SUCCESS == s32Err)
    {
        eRet = E_SME_HIVO_ERR_NONE;
    }
    else if(HI_ERR_VO_BUFQUE_FULL == s32Err)
    {
        GST_ERROR("buf que full");
        eRet = E_SME_HIVO_ERR_BUF_FULL;
    }
    else
    {
        GST_ERROR("hal queue failed");
        eRet = E_SME_HIVO_ERR_FATAL;
    }

    return eRet;
}

E_SME_HIVO_ERR SME_Hal_VDisp_DeQueueFrame(IN SME_HAL_VDISP_PIPE_HDL hdlPipe,
   OUT ST_SME_VIDEO_FRAME* pstVideoFrame)
{
    E_SME_HIVO_ERR                  eRet          = E_SME_HIVO_ERR_NONE;
    ST_SME_HAL_HI_VDISP_PIPE*       pstPipe        = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    S32                             s32Err;
    VOUT_FRAME_INFO_S               stVoutFrame;
    gint                            iMemSecRet;

    if(NULL == pstPipe || NULL == pstVideoFrame)
    {
        GST_ERROR("SME_HiVO_DeQueueFrame:invalid args!");
        return E_SME_HIVO_ERR_INVALID_ARGS;
    }

    iMemSecRet = memset_s(&stVoutFrame, sizeof(VOUT_FRAME_INFO_S), 0, sizeof(VOUT_FRAME_INFO_S));
    if(iMemSecRet != 0){
        GST_ERROR("init stVoutFrame failed,ret:%d", iMemSecRet);
        return E_SME_HIVO_ERR_FATAL;
    }

    s32Err = pstPipe->pstVoutDev->vout_window_dequeue_frame(pstPipe->pstVoutDev, pstPipe->phVoutWindow, &stVoutFrame, DEQUEUE_TIMEOUT);

    if (SUCCESS == s32Err)
    {
        pstVideoFrame->pvAddr[1] = (void*)stVoutFrame.stVideoFrameAddr[0].u32YAddr;
        eRet = E_SME_HIVO_ERR_NONE;
    }
    else
    {
        pstPipe->u64DeqFailNum++;
        eRet = E_SME_HIVO_ERR_FATAL;
        if((pstPipe->u64DeqFailNum - 1)%100 == 0)
        {
            GST_DEBUG("SME_Hal_VDisp_DeQueueFrame failed, fail number is %lld", pstPipe->u64DeqFailNum);
        }

    }

    return eRet;
}

E_SME_HIVO_ERR SME_Hal_VDisp_GetRenderDelay(IN SME_HAL_VDISP_PIPE_HDL hldPipe, OUT guint64 *delay )
{
    E_SME_HIVO_ERR              eRet                = E_SME_HIVO_ERR_NONE;
    ST_SME_HAL_HI_VDISP_PIPE*   pstPipe             = (ST_SME_HAL_HI_VDISP_PIPE*)hldPipe;
    gint32                      s32Err;
    guint32                     u32DelayTime        = 0;
    guint32                     u32DispRate         = 0;
    guint32                     u32FrameNumInBufQn  = 0;

    if(NULL == pstPipe || NULL == delay)
    {
        GST_ERROR("SME_Hal_VDisp_GetRenderDelay: invalid args!");
        return E_SME_HIVO_ERR_INVALID_ARGS;
    }

#ifdef DEBUG
    GST_ERROR("@cat_clock@video@vsink@vo@in: SME_Hal_VDisp_GetRenderLatency");
#endif

    s32Err = pstPipe->pstVoutDev->vout_window_get_playinfo(
                                                         pstPipe->pstVoutDev,
                                                         pstPipe->phVoutWindow,
                                                        &u32DelayTime,
                                                        &u32DispRate,
                                                        &u32FrameNumInBufQn );
    if ( SUCCESS == s32Err )
    {
        *delay = u32DelayTime * 1000000ULL;
        eRet     = E_SME_HIVO_ERR_NONE;
    }
    else
    {
        eRet     = E_SME_HIVO_ERR_FATAL;
        GST_WARNING("SME_Hal_VDisp_DeQueueFrame failed");
    }

    GST_DEBUG("@-cat_clock@video@vsink@vo@ playinfo : u32DelayTime:%d,"
        "u32DispRate:%u,u32FrameNumInBufQn:%u",
        u32DelayTime, u32DispRate, u32FrameNumInBufQn);

    return eRet;
}

//lint -e58
guint32 SME_Hal_VDisp_Reset(IN SME_HAL_VDISP_PIPE_HDL hdlPipe, IN E_SME_HIVO_SWITCH_TYPE eSwitchMode)
{
    ST_SME_HAL_HI_VDISP_PIPE*       pstPipe        = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    S32                             sRet;
    VOUT_WINDOW_SWITCH_MODE_E       eVoutSwitchMode;
    if(NULL == pstPipe || (HANDLE)NULL == pstPipe->pstVoutDev
        || (HANDLE)NULL == pstPipe->phVoutWindow
        || (eSwitchMode != E_SME_HIVO_SWITCH_TYPE_LAST
            && eSwitchMode != E_SME_HIVO_SWITCH_TYPE_BLACK))
    {
        GST_ERROR("input para is error");
        return ICS_FAIL;
    }

    eVoutSwitchMode = (eSwitchMode == E_SME_HIVO_SWITCH_TYPE_LAST) ? VOUT_WINDOW_SWITCH_MODE_FREEZE : VOUT_WINDOW_SWITCH_MODE_BLACK;
    sRet = pstPipe->pstVoutDev->vout_window_reset(pstPipe->pstVoutDev, pstPipe->phVoutWindow, eVoutSwitchMode);
    if(sRet == SUCCESS)
    {
        GST_ERROR("reset switch mode : %u succeed", eVoutSwitchMode);
        return ICS_SUCCESS;
    }
    else
    {
        GST_ERROR("reset switch mode : %u failed", eVoutSwitchMode);
        return ICS_FAIL;
    }
}
//lint +e58

void SME_Disp_Full(IN const ST_OUT_RECT * pstDispRect, OUT ST_OUT_RECT * pstOutRect)
{
    GST_INFO("full IN pstDispRect(%u,%u,%u,%u)", pstDispRect->u32OutX, pstDispRect->u32OutY, pstDispRect->u32OutWidth, pstDispRect->u32OutHeight);
    pstOutRect->u32OutWidth = (guint32)(pstDispRect->u32OutWidth &~ 15);
    pstOutRect->u32OutHeight = (guint32)(pstDispRect->u32OutHeight &~ 15);
    pstOutRect->u32OutX = (guint32)pstDispRect->u32OutX + (guint32)(pstDispRect->u32OutWidth - (guint32)pstOutRect->u32OutWidth)/2;
    pstOutRect->u32OutY = (guint32)pstDispRect->u32OutY + (guint32)(pstDispRect->u32OutHeight - (guint32)pstOutRect->u32OutHeight)/2;
    GST_INFO("full OUT stOutRect:(%u,%u,%u,%u)",pstOutRect->u32OutX, pstOutRect->u32OutY, pstOutRect->u32OutWidth, pstOutRect->u32OutHeight);

    return ;
}

void SME_Disp_Fitin(SME_HAL_VDISP_PIPE_HDL hdlPipe, const ST_DISP_HAL_RATIO* p_disp_radio, const ST_OUT_RECT* p_win_rect, ST_OUT_RECT* p_disp_win)
{
    ST_DISP_SCREEN stVirScreen;
    SME_Get_Virtual_Screen(hdlPipe, &stVirScreen);

    if(ICS_FAIL == SME_Calcu_Win_Rect(*p_disp_radio, stVirScreen, p_win_rect, p_disp_win))
    {
        /* if calc filed, maybe the input rect is invaild, so we send input rect to HISI directly*/
        GST_WARNING("SME_Calcu_Win_Rect failed");
        p_disp_win->u32OutX = p_win_rect->u32OutX;
        p_disp_win->u32OutY = p_win_rect->u32OutY;
        p_disp_win->u32OutWidth = p_win_rect->u32OutWidth;
        p_disp_win->u32OutHeight = p_win_rect->u32OutHeight;
    }
    return ;
}

//lint -e529
//lint -e438
void SME_Get_Virtual_Screen(IN SME_HAL_VDISP_PIPE_HDL hdlPipe, OUT ST_DISP_SCREEN * pstVirScreen)
{
    ST_SME_HAL_HI_VDISP_PIPE* pstPipe = (ST_SME_HAL_HI_VDISP_PIPE*)hdlPipe;
    HI_S32  i32GetVWinSize = HI_SUCCESS;
    HI_U32  u32VirScreenW = VIRTUAL_SCREEN_WIDTH;
    HI_U32  u32VirScreenH = VIRTUAL_SCREEN_HEIGHT;

    if(NULL == pstPipe || NULL == pstPipe->pstVoutDev)
    {
        GST_ERROR("hdlPipe IS NULL, maybe init Vdisp error, pstPipe:%p, Now, the rect of vdisp may be wrong", pstPipe);
        pstVirScreen->u32DispWidth  = VIRTUAL_SCREEN_WIDTH;
        pstVirScreen->u32DispHeight = VIRTUAL_SCREEN_HEIGHT;
        return;
    }

    if(pstPipe->pstVoutDev->vout_window_get_virtual_size)
    {
        i32GetVWinSize = pstPipe->pstVoutDev->vout_window_get_virtual_size(pstPipe->pstVoutDev, pstPipe->phVoutWindow, &u32VirScreenW, &u32VirScreenH);
    }
    else
    {
        GST_ERROR("pstPipe->pstVoutDev->vout_window_get_virtual_size is NULL ,Now, the rect of vdisp may be wrong");
        pstVirScreen->u32DispWidth  = VIRTUAL_SCREEN_WIDTH;
        pstVirScreen->u32DispHeight = VIRTUAL_SCREEN_HEIGHT;
        return;
    }
    if(i32GetVWinSize == HI_SUCCESS)
    {
        GST_WARNING("get virtual screen succeed is : [%d %d]", u32VirScreenW, u32VirScreenH);
        pstVirScreen->u32DispWidth = u32VirScreenW;
        pstVirScreen->u32DispHeight = u32VirScreenH;
    }
    else
    {
        pstVirScreen->u32DispWidth  = VIRTUAL_SCREEN_WIDTH;
        pstVirScreen->u32DispHeight = VIRTUAL_SCREEN_HEIGHT;
        GST_ERROR("get virtual screen failed, Now, the rect of vdisp may be wrong");
    }

    return;
}
//lint +e529
//lint +e438

//lint -e1746
guint32 SME_Calcu_Win_Rect(IN const ST_DISP_HAL_RATIO stUI, IN  ST_DISP_SCREEN stScreen,
    const ST_OUT_RECT* pstDispRect, ST_OUT_RECT* pOutRect)
{
    //UI 宽高比
    gfloat fUIRatioWidth = (gfloat)stUI.u32DispRatioW;
    gfloat fUIRatioHeight= (gfloat)stUI.u32DispRatioH;
    //虚拟屏幕宽高
    gfloat fVirScreenWidth = (gfloat)stScreen.u32DispWidth;
    gfloat fVirScreenHeight= (gfloat)stScreen.u32DispHeight;

    //小窗位置、大小
    gfloat fWinWidth ;
    gfloat fWinHeight;
    guint32 u32StartX;
    guint32 u32StartY;
    if(pstDispRect != NULL)
    {
        fWinWidth = (gfloat)pstDispRect->u32OutWidth;
        fWinHeight= (gfloat)pstDispRect->u32OutHeight;
        u32StartX = pstDispRect->u32OutX;
        u32StartY = pstDispRect->u32OutY;
    }
    else
    {
        fWinWidth = 0;
        fWinHeight = 0;
        u32StartX = 0;
        u32StartY = 0;
    }

    //小窗显示比例，UI显示比例
    gfloat fWinRatio;
    gfloat fUIRatio;
    ST_OUT_RECT stOutRectTmp;
    gint   iMemSecRet;
    iMemSecRet = memset_s((void*)&stOutRectTmp, sizeof(ST_OUT_RECT), 0x0, sizeof(ST_OUT_RECT));
    if(iMemSecRet != 0){
        GST_ERROR("init stOutRectTmp failed,ret:%d", iMemSecRet);
        return ICS_FAIL;
    }

    if(FLOAT_IS_EAQUAL_ZERO((gdouble)fUIRatioWidth) || FLOAT_IS_EAQUAL_ZERO((gdouble)fUIRatioHeight)
        || FLOAT_IS_EAQUAL_ZERO((gdouble)fVirScreenWidth) || FLOAT_IS_EAQUAL_ZERO((gdouble)fVirScreenHeight))
    {
        GST_WARNING("the resolution of UI , VirScreen or WinScreen contains zero:[%f %f %f %f]",
            fUIRatioWidth, fUIRatioHeight, fVirScreenWidth, fVirScreenHeight);
        return ICS_FAIL;
    }
    if(FLOAT_IS_EAQUAL_ZERO((gdouble)fWinWidth) && FLOAT_IS_EAQUAL_ZERO((gdouble)fWinHeight)){
        fWinWidth = fVirScreenWidth;
        fWinHeight = fVirScreenHeight;
    }
    else if(FLOAT_IS_EAQUAL_ZERO((gdouble)fWinWidth) || FLOAT_IS_EAQUAL_ZERO((gdouble)fWinHeight)){
        GST_WARNING("window size contains zero");
        return ICS_FAIL;
    }

    fWinRatio = fWinWidth / fWinHeight;
    fUIRatio = fUIRatioWidth / fUIRatioHeight;

    /* Caculate the real W&H and the start of X,Y */
    if(fWinRatio > fUIRatio)
    {
        /* 宽加黑边 */
        stOutRectTmp.u32OutHeight = ((guint32)(fWinHeight)) &~ 15;
        stOutRectTmp.u32OutWidth = (guint32)( fUIRatio * fWinHeight);
        /* 16字节对齐 */
        stOutRectTmp.u32OutWidth = (stOutRectTmp.u32OutWidth) &~ 15;
        stOutRectTmp.u32OutX = (guint32)((fWinWidth - stOutRectTmp.u32OutWidth)/2 + u32StartX);
        stOutRectTmp.u32OutY = u32StartY + (guint32)((fWinHeight - stOutRectTmp.u32OutHeight)/2);

    }
    else if(fWinRatio < fUIRatio)
    {
        /* 高加黑边 */
        stOutRectTmp.u32OutHeight = (guint32)(fWinWidth / fUIRatio);
        stOutRectTmp.u32OutWidth = ((guint32)(fWinWidth)) &~ 15;
        /* 16字节对齐 */
        stOutRectTmp.u32OutHeight = (stOutRectTmp.u32OutHeight) &~ 15;
        stOutRectTmp.u32OutX = u32StartX + (guint32)((fWinWidth - stOutRectTmp.u32OutWidth)/2);
        stOutRectTmp.u32OutY = (guint32)((fWinHeight - stOutRectTmp.u32OutHeight)/2 + u32StartY);
    }
    else
    {
        /* ui比例和Screen一致，无需加黑边 */
        stOutRectTmp.u32OutWidth = ((guint32)(fWinWidth)) &~ 15;
        stOutRectTmp.u32OutHeight = ((guint32)(fWinHeight)) &~ 15;
        stOutRectTmp.u32OutX = u32StartX + (guint32)((fWinWidth - stOutRectTmp.u32OutWidth)/2);
        stOutRectTmp.u32OutY = u32StartY + (guint32)((fWinHeight - stOutRectTmp.u32OutHeight)/2);
    }
    if(pstDispRect != NULL)
    {
        GST_WARNING("fitin IN pstDispRect(%u,%u,%u,%u)", pstDispRect->u32OutX, pstDispRect->u32OutY, pstDispRect->u32OutWidth, pstDispRect->u32OutHeight);
    }
    if(pOutRect != NULL)
    {
        pOutRect->u32OutX = stOutRectTmp.u32OutX;
        pOutRect->u32OutY = stOutRectTmp.u32OutY;
        pOutRect->u32OutHeight = stOutRectTmp.u32OutHeight;
        pOutRect->u32OutWidth = stOutRectTmp.u32OutWidth;
        GST_WARNING("fitin OUT stOutRect:(%u,%u,%u,%u)",pOutRect->u32OutX, pOutRect->u32OutY, pOutRect->u32OutWidth, pOutRect->u32OutHeight);
    }

    return ICS_SUCCESS;

}
//lint +e1746
