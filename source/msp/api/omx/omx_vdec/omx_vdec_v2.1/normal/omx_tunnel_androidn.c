#include <string.h>

#include "omx_dbg.h"
#include "omx_vdec.h"
#include "omx_tunnel.h"
#include "hi_math.h"
#include "hi_common.h"
#include "hi_drv_stat.h"
#include "hi_mpi_stat.h"
#include "hi_mpi_avplay.h"
#include "hi_unf_avplay.h"
#include "hi_unf_vo.h"
#include "hiavplayer_intf.h"

#ifdef HI_OMX_TEE_SUPPORT
#include "tee_client_api.h"
#include "mpi_mmz.h"

typedef enum
{
    VFMW_CMD_ID_INVALID = 0x0,
    VFMW_CMD_ID_INIT,
    VFMW_CMD_ID_EXIT,
    VFMW_CMD_ID_RESUME,
    VFMW_CMD_ID_SUSPEND,
    VFMW_CMD_ID_CONTROL,
    VFMW_CMD_ID_THREAD,
    VFMW_CMD_ID_GET_IMAGE,
    VFMW_CMD_ID_RELEASE_IMAGE,
    VFMW_CMD_ID_READ_PROC,
    VFMW_CMD_ID_WRITE_PROC,
    VFMW_CMD_ID_PARSE_CSD
} OMX_VFMW_CMD_ID;

#endif

#define OMX_MAX_INSTANCE 7

typedef struct
{
    OMX_COMPONENT_PRIVATE *pComponent;
    HI_U32 hAvplay;
} OMX_ComponentCallbackHandle;

OMX_ComponentCallbackHandle g_ComponentCallbackHandle[OMX_MAX_INSTANCE] =
{
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
    {NULL, 0xffffffff},
};

/*============== INTERNAL FUNCTION =============*/
static HI_S32 omx_callback(HI_HANDLE hAvplay, HI_UNF_AVPLAY_EVENT_E enEvent, HI_VOID *pPara)
{
    HI_S32 i;
    OMX_COMPONENT_PRIVATE *pComponentPrivate = NULL;
    HI_UNF_VIDEO_FRM_DISPLAY_TIME_S *pstFrmInfo = (HI_UNF_VIDEO_FRM_DISPLAY_TIME_S *)pPara;
    OMX_VIDEO_RENDEREVENTTYPE render_event_type;

    if (enEvent != HI_UNF_AVPLAY_EVENT_FRAME_DISPLAY_TIME)
    {
        DEBUG_PRINT_ERROR("Tunnel: omx_callback, not HI_UNF_AVPLAY_EVENT_FRAME_DISPLAY_INFO event!\n");

        return HI_FAILURE;
    }

    for (i = 0; i < OMX_MAX_INSTANCE; i++)
    {
        if ((hAvplay == g_ComponentCallbackHandle[i].hAvplay)
            && (g_ComponentCallbackHandle[i].pComponent != NULL))
        {
            pComponentPrivate = g_ComponentCallbackHandle[i].pComponent;
            break;
        }
    }

    if (i == OMX_MAX_INSTANCE)
    {
        DEBUG_PRINT_ERROR("Tunnel: omx_callback, can't find g_ComponentCallbackHandle!\n");

        return HI_FAILURE;
    }

    render_event_type.nMediaTimeUs = pstFrmInfo->s64PTS * 1000;
    render_event_type.nSystemTimeNs = pstFrmInfo->s64DisplayTime;

#ifdef ANDROID_O
    char value[PROPERTY_VALUE_MAX];

    if (property_get("ro.config.build.name", value, NULL))
    {
        omx_report_event(pComponentPrivate, OMX_EventOutputRendered, 1, 0, &render_event_type);
    }

#endif

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_create_win(HI_HANDLE client_player, HI_HANDLE *hWin)
{
    HI_UNF_WINDOW_ATTR_S WinAttr;
    HI_S32 ret = HI_FAILURE;

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));

    WinAttr.enDisp = HI_UNF_DISPLAY1;
    WinAttr.bVirtual = HI_FALSE;
    WinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr.stWinAspectAttr.u32UserAspectWidth  = 0;
    WinAttr.stWinAspectAttr.u32UserAspectHeight = 0;
    WinAttr.bUseCropRect = HI_FALSE;
    WinAttr.stInputRect.s32X = 0;
    WinAttr.stInputRect.s32Y = 0;
    WinAttr.stInputRect.s32Width = 0;
    WinAttr.stInputRect.s32Height = 0;
    memset(&WinAttr.stOutputRect, 0x0, sizeof(HI_RECT_S));

    ret = HIAVPLAYER_VO_Init(client_player, HI_UNF_VO_DEV_MODE_NORMAL);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: call HI_UNF_VO_Init failed!\n");

        return HI_FAILURE;
    }

    ret = HIAVPLAYER_VO_CreateWindow(client_player, &WinAttr, hWin, sizeof(HI_UNF_WINDOW_ATTR_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: call HI_UNF_VO_CreateWindow failed!\n");
        HI_UNF_VO_DeInit();

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_destroy_win(HI_HANDLE client_player, HI_HANDLE hWin)
{
    HIAVPLAYER_VO_DestroyWindow(client_player, hWin);
    HIAVPLAYER_VO_DeInit(client_player);

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_attach_win(HI_HANDLE client_player, HI_HANDLE hWin, OMX_U32 nAudioHwSync)
{
    HI_S32 ret = HI_FAILURE;

    ret = HIAVPLAYER_VO_AttachWindow(client_player, hWin, nAudioHwSync);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("call HIAVPLAYER_VO_AttachWindow failed.\n");

        return HI_FAILURE;
    }

    ret = HIAVPLAYER_VO_SetWindowEnable(client_player, hWin, HI_TRUE);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("call HIAVPLAYER_VO_SetWindowEnable failed.\n");
        HIAVPLAYER_VO_DetachWindow(client_player, hWin, nAudioHwSync);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_detach_win(HI_HANDLE client_player, HI_HANDLE hWin, OMX_U32 nAudioHwSync)
{
    HIAVPLAYER_VO_SetWindowEnable(client_player, hWin, HI_FALSE);
    HIAVPLAYER_VO_DetachWindow(client_player, hWin, nAudioHwSync);

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_enable_avplay(OMX_TUNNEL_INFO *ptunnel_info, OMXVDEC_DRV_CONTEXT *pdrv_ctx)
{
    HI_S32 ret = HI_FAILURE;
    HI_UNF_AVPLAY_OPEN_OPT_S stOpenOpt;
    HI_UNF_VCODEC_ATTR_S stVdecAttr;
    VDEC_CHAN_CFG_S *pchan_cfg = HI_NULL;
    HI_UNF_AVPLAY_ATTR_S stAvplayAttr;
    OMXVDEC_DRV_CFG *drv_cfg = &pdrv_ctx->drv_cfg;
    OMX_U32 nAudioHwSync = ptunnel_info->config_param.nAudioHwSync;
    HI_HANDLE client_player = ptunnel_info->client_player;

    HIAVPLAYER_SetAttr(client_player, nAudioHwSync, HI_UNF_AVPLAY_ATTR_ID_TVP, &(drv_cfg->is_tvp), sizeof(HI_UNF_AVPLAY_TVP_ATTR_S));

    ret = HIAVPLAYER_RegisterEvent64(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, omx_callback);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: HIAVPLAYER_RegisterEvent64 failed, client_player = %u, nAudioHwSync = %u\n", client_player, nAudioHwSync);

        return HI_FAILURE;
    }

    memset(&stAvplayAttr, 0, sizeof(HI_UNF_AVPLAY_ATTR_S));

    ret = HIAVPLAYER_GetAttr(client_player, nAudioHwSync, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &stAvplayAttr, sizeof(HI_UNF_AVPLAY_ATTR_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: avplay Get VID Stream Mode attr failed!, avplay handle: %ld\n", nAudioHwSync);

        return HI_FAILURE;
    }

    stAvplayAttr.stStreamAttr.enStreamType  = HI_UNF_AVPLAY_STREAM_TYPE_ES;
    stAvplayAttr.stStreamAttr.u32VidBufSize = 0;
    ret = HIAVPLAYER_SetAttr(client_player, nAudioHwSync, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &stAvplayAttr, sizeof(HI_UNF_AVPLAY_ATTR_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: avplay set VID Stream BUF failed!, StreamBufSize: %d, avplay handle: %ld\n", stAvplayAttr.stStreamAttr.u32VidBufSize, nAudioHwSync);

        return HI_FAILURE;
    }

    memset(&stOpenOpt, 0, sizeof(stOpenOpt));

    stOpenOpt.enDecType       = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    stOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;

    if (drv_cfg->cfg_width * drv_cfg->cfg_height >= 1920 * 1088)
    {
        stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_4096x2160;
    }
    else
    {
        stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    }

    ret = HIAVPLAYER_ChnOpen(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stOpenOpt, sizeof(HI_UNF_AVPLAY_OPEN_OPT_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: AVPLAY ChnOpen failed! ret: %d, avplay handle: %ld\n", ret, nAudioHwSync);

        return HI_FAILURE;
    }

    ret = HIAVPLAYER_SetTunnelMode(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, drv_cfg->TunnelModeEnable);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: avplay Set tunnel Mode failed, call avplay chanclose! avplay handle: %ld\n", nAudioHwSync);
        HIAVPLAYER_ChnClose(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

        return HI_FAILURE;
    }

    pchan_cfg = &drv_cfg->chan_cfg;
    OMX_VIDEO_FORMAT_SWITCH(pchan_cfg->eVidStd, stVdecAttr.enType);
    stVdecAttr.enMode         = HI_UNF_VCODEC_MODE_NORMAL;
    stVdecAttr.bOrderOutput   = HI_FALSE;
    stVdecAttr.u32ErrCover    = pchan_cfg->s32ChanErrThr;
    stVdecAttr.u32Priority    = 1;
    stVdecAttr.pCodecContext  = (HI_VOID *)pdrv_ctx->chan_handle;

    ret = HIAVPLAYER_SetAttr(client_player, nAudioHwSync, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr, sizeof(HI_UNF_VCODEC_ATTR_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: avplay set attr fail! avplay handle: %ld, omx handle: %d\n", nAudioHwSync, pdrv_ctx->chan_handle);
        HIAVPLAYER_ChnClose(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

        return HI_FAILURE;
    }

    DEBUG_PRINT_TUNNELED("Tunnel: avplay set attr success! avplay handle: %ld, omx handle: %d\n", nAudioHwSync, pdrv_ctx->chan_handle);

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_disable_avplay(OMX_TUNNEL_INFO *ptunnel_info)
{
    OMX_U32 nAudioHwSync = ptunnel_info->config_param.nAudioHwSync;
    HI_HANDLE client_player = ptunnel_info->client_player;

    HIAVPLAYER_ChnClose(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_open_player(HI_HANDLE *pclient_player)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;

    ret = HIAVPLAYER_Open(pclient_player);

    if (ret != HI_SUCCESS || *pclient_player == NULL)
    {
        return OMX_ErrorNotReady;
    }

    return HI_SUCCESS;
}

static HI_S32 omx_tunnel_close_player(HI_HANDLE client_player)
{
    HIAVPLAYER_Close(client_player);;

    return HI_SUCCESS;
}

/*============== EXTERNAL FUNCTION =============*/

OMX_ERRORTYPE omx_tunnel_init(OMX_COMPONENTTYPE *pcomp, OMX_PTR pInitParam)
{
    HI_S32 i;
    HI_HANDLE hWin;
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    ConfigureVideoTunnelModeParams *pParams = NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;

    if (pcomp == NULL || pInitParam == NULL)
    {
        DEBUG_PRINT_ERROR("omx_tunnel_init failed!\n");

        return OMX_ErrorBadParameter;
    }

    pParams = (ConfigureVideoTunnelModeParams *)pInitParam;
    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;

    if (pParams->nPortIndex != OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("omx_tunnel_init: Bad port index %ud\n", (int)pParams->nPortIndex);

        return OMX_ErrorBadPortIndex;
    }

    if (pParams->nAudioHwSync == HI_INVALID_HANDLE)
    {
        DEBUG_PRINT_ERROR("omx_tunnel_init: Bad Handle %ld\n", pParams->nAudioHwSync);

        return OMX_ErrorBadParameter;
    }

    ret = omx_tunnel_open_player(&(ptunnel_info->client_player));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: open player failed!\n");

        return OMX_ErrorNotReady;
    }

    ret = omx_tunnel_create_win(ptunnel_info->client_player, &hWin);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: Create win failed!\n");

        return OMX_ErrorNotReady;
    }

    ptunnel_info->native_handle.version = sizeof(native_handle_t);
    ptunnel_info->native_handle.numFds  = 0;
    ptunnel_info->native_handle.numInts = 1;
    ptunnel_info->native_handle.data[0] = hWin;

    ptunnel_info->win_handle = hWin;
    ptunnel_info->play_handle = pParams->nAudioHwSync;
    pcomp_priv->drv_ctx.drv_cfg.TunnelModeEnable = 1;

    pParams->pSidebandWindow = &(ptunnel_info->native_handle);

    for (i = 0; i < OMX_MAX_INSTANCE; i++)
    {
        if ((g_ComponentCallbackHandle[i].pComponent == NULL)
            && (g_ComponentCallbackHandle[i].hAvplay == 0xffffffff))
        {
            g_ComponentCallbackHandle[i].pComponent = pcomp_priv;
            g_ComponentCallbackHandle[i].hAvplay = pParams->nAudioHwSync;

            break;
        }
    }

    if (i == OMX_MAX_INSTANCE)
    {
        DEBUG_PRINT_ERROR("omx_tunnel_init: Not found valid g_ComponentCallbackHandle\n");

        omx_tunnel_destroy_win(ptunnel_info->client_player, ptunnel_info->win_handle);
        omx_tunnel_close_player(ptunnel_info->client_player);

        return OMX_ErrorNotReady;
    }

    memcpy(&(ptunnel_info->config_param), pParams, sizeof(ConfigureVideoTunnelModeParams));

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_deinit(OMX_COMPONENTTYPE *pcomp)
{
    HI_S32 i;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;

    for (i = 0; i < OMX_MAX_INSTANCE; i++)
    {
        if ((g_ComponentCallbackHandle[i].hAvplay == ptunnel_info->play_handle)
            && (g_ComponentCallbackHandle[i].pComponent != NULL))
        {
            g_ComponentCallbackHandle[i].pComponent = NULL;
            g_ComponentCallbackHandle[i].hAvplay = 0xffffffff;

            break;
        }
    }

    if (i == OMX_MAX_INSTANCE)
    {
        return OMX_ErrorNotReady;
    }

    omx_tunnel_destroy_win(ptunnel_info->client_player, ptunnel_info->win_handle);
    omx_tunnel_close_player(ptunnel_info->client_player);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_enable(OMX_COMPONENTTYPE *pcomp)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;
    OMXVDEC_DRV_CONTEXT *pdrv_ctx = NULL;
    OMX_U32 nAudioHwSync = 0;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;
    pdrv_ctx = &pcomp_priv->drv_ctx;
    nAudioHwSync = pcomp_priv->tunnel_info.config_param.nAudioHwSync;

    ret = omx_tunnel_enable_avplay(ptunnel_info, pdrv_ctx);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: Enable avplay failed, Destroy win! avplay handle: %ld, win handle: %d, omx handle: %d\n", nAudioHwSync, ptunnel_info->win_handle, pcomp_priv->drv_ctx.chan_handle);
        omx_tunnel_destroy_win(ptunnel_info->client_player, ptunnel_info->win_handle);

        return OMX_ErrorInsufficientResources;
    }

    ret = omx_tunnel_attach_win(ptunnel_info->client_player, ptunnel_info->win_handle, nAudioHwSync);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: Enable avplay failed, disable avplay, destory win!, avplay handle: %ld, win handle: %d, omx handle: %d\n", nAudioHwSync, ptunnel_info->win_handle, pcomp_priv->drv_ctx.chan_handle);
        omx_tunnel_disable_avplay(ptunnel_info);
        omx_tunnel_destroy_win(ptunnel_info->client_player, ptunnel_info->win_handle);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_disable(OMX_COMPONENTTYPE *pcomp)
{
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;

    omx_tunnel_detach_win(ptunnel_info->client_player, ptunnel_info->win_handle, ptunnel_info->config_param.nAudioHwSync);
    omx_tunnel_disable_avplay(ptunnel_info);

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_start(OMX_COMPONENTTYPE *pcomp)
{
    HI_S32 ret = HI_FAILURE;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;
    HI_HANDLE hAvplay = 0;
    HI_HANDLE client_player = 0;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;
    hAvplay = ptunnel_info->play_handle;
    client_player = ptunnel_info->client_player;

    ret = HIAVPLAYER_Start(client_player, hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: Start avplay failed, avplay handle: %d\n", hAvplay);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_stop(OMX_COMPONENTTYPE *pcomp)
{
    HI_S32 ret = HI_FAILURE;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;
    OMX_U32 nAudioHwSync = 0;
    HI_HANDLE hAvplay = 0;
    HI_HANDLE client_player = 0;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;
    nAudioHwSync = ptunnel_info->config_param.nAudioHwSync;
    hAvplay = ptunnel_info->play_handle;
    client_player = ptunnel_info->client_player;

    ret = HIAVPLAYER_Stop(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: Start avplay failed, avplay handle: %d\n", hAvplay);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_flush(OMX_COMPONENTTYPE *pcomp)
{
    HI_S32 ret = HI_FAILURE;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;
    OMX_TUNNEL_INFO *ptunnel_info = NULL;
    OMX_U32 nAudioHwSync = 0;
    HI_HANDLE client_player = 0;

    if (pcomp == NULL)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        return OMX_ErrorBadParameter;
    }

    pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    ptunnel_info = &pcomp_priv->tunnel_info;
    nAudioHwSync = ptunnel_info->config_param.nAudioHwSync;
    client_player = ptunnel_info->client_player;

    ret = HIAVPLAYER_Stop(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: avplay flush Chn Error, avplay stop failed! avplay handle: %ld, omx handle: %d\n", nAudioHwSync, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorInsufficientResources;
    }

    ret = HIAVPLAYER_Start(client_player, nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: avplay flush Chn Error, avplay start failed! avplay handle: %ld, omx handle: %d\n", nAudioHwSync, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_parse_csd(OMXVDEC_BUF_DESC *pBuffer, OMX_TUNNEL_CSD *pcsd)
{
    HI_U32 i = 0;
    HI_U8 *pStream = (HI_U8 *)(pBuffer->bufferaddr + pBuffer->data_offset);
    HI_U8 *pp = NULL;
    HI_U32 stream_length = pBuffer->data_len;

    for (pp = pStream; pp < (pStream + stream_length); pp++)
    {
        if ((*(pp) == 0x00)
            && (*(pp + 1) == 0x00)
            && (*(pp + 2) == 0x00)
            && (*(pp + 3) == 0x01)
            && (*(pp + 4) == 0x7C)
            && (*(pp + 5) == 0x01))
        {
            pcsd->found_dolby_info_start_code = HI_TRUE;
            break;
        }
    }

    if (pcsd->found_dolby_info_start_code)
    {
        pp += 7;
        pcsd->profile = *pp;
        pcsd->level = *(pp + 1);
        pcsd->rpu_assoc_flag = *(pp + 2);
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_config_avlay_dolbyhdr(OMX_COMPONENTTYPE *pcomp, OMXVDEC_BUF_DESC *pBuffer)
{
    OMX_TUNNEL_CSD *pcsd;
    HI_S32 ret = HI_FAILURE;
    HI_UNF_AVPLAY_HDR_ATTR_S dolby_dhr_attr;
    HI_UNF_VCODEC_TYPE_E codec_type;
    OMX_COMPONENT_PRIVATE *pcomp_priv = (OMX_COMPONENT_PRIVATE *)(pcomp->pComponentPrivate);
    OMX_TUNNEL_INFO *ptunnel_info = &(pcomp_priv->tunnel_info);
    OMXVDEC_DRV_CONTEXT *pdrv_ctx = &(pcomp_priv->drv_ctx);

    pcsd = &(pcomp_priv->csd);
    pcsd->dual_layer = HI_FALSE;
    pcsd->found_dolby_info_start_code = HI_FALSE;
    pcsd->profile = OMX_VIDEO_DolbyVisionProfileUnknown;
    pcsd->level = OMX_VIDEO_DolbyVisionLevelUnknown;
    pcsd->rpu_assoc_flag = 0xffffffff;

    if (pdrv_ctx->drv_cfg.is_tvp)
    {
#ifdef HI_OMX_TEE_SUPPORT
        pcsd->phyaddr = pBuffer->phyaddr + pBuffer->data_offset;
        pcsd->length = pBuffer->data_len;
        omx_tunnel_secure_parse_csd(pBuffer, pcsd);
#endif
    }
    else
    {
        omx_tunnel_parse_csd(pBuffer, pcsd);
    }

    switch (pcsd->profile)
    {
        case 0:
        case 1:
        case 9:
        {
            codec_type = HI_UNF_VCODEC_TYPE_H264;
            pdrv_ctx->drv_cfg.chan_cfg.eVidStd = STD_H264;
            break;
        }

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        {
            codec_type = HI_UNF_VCODEC_TYPE_HEVC;
            pdrv_ctx->drv_cfg.chan_cfg.eVidStd = STD_HEVC;
            break;
        }

        default:
            return OMX_ErrorBadParameter;
    }

    switch (pcsd->profile)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        {
            pcsd->dual_layer = 1;
            break;
        }

        case 5:
        case 8:
        case 9:
        {
            pcsd->dual_layer = 0;
            break;
        }

        default:
            return OMX_ErrorBadParameter;
    }

    pcsd->valid = 1;
    ret = omx_tunnel_enable(pcomp);

    if (ret != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("%s: omx_tunnel_enable failed!\n", __func__);

        return ret;
    }

    dolby_dhr_attr.bEnable                      = HI_TRUE;
    dolby_dhr_attr.enHDRStreamType              = pcsd->dual_layer ? HI_UNF_AVPLAY_HDR_STREAM_TYPE_DL_SINGLE_VES : HI_UNF_AVPLAY_HDR_STREAM_TYPE_SL_VES;
    dolby_dhr_attr.enElType                     = codec_type;
    dolby_dhr_attr.stElCodecOpt.enCapLevel      = HI_UNF_VCODEC_CAP_LEVEL_4096x2160;
    dolby_dhr_attr.stElCodecOpt.enDecType       = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    dolby_dhr_attr.stElCodecOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;

    ret = HIAVPLAYER_SetAttr(ptunnel_info->client_player, ptunnel_info->config_param.nAudioHwSync, HI_UNF_AVPLAY_ATTR_ID_HDR, &dolby_dhr_attr, sizeof(HI_UNF_AVPLAY_HDR_ATTR_S));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel: avplay set hdr attr fail! avplay handle: %ld, omx handle: %d\n", ptunnel_info->config_param.nAudioHwSync, pdrv_ctx->chan_handle);
        HIAVPLAYER_ChnClose(ptunnel_info->client_player, ptunnel_info->config_param.nAudioHwSync, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

        return OMX_ErrorInsufficientResources;
    }

    return omx_tunnel_start(pcomp);
}

OMX_ERRORTYPE omx_tunnel_get_hdr_static_info(OMX_COMPONENTTYPE *pcomp, DescribeHDRStaticInfoParams *describe_hdr_static_info)
{
    HI_S32 ret = HI_FAILURE;
    HI_UNF_VIDEO_HDR_INFO_S unf_hdr_info = {0};
    Type1 *ptype1 = HI_NULL;
    HI_UNF_VIDEO_HDR10_INFO_S *phdr10info = HI_NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    OMX_TUNNEL_INFO *ptunnel_info = &(pcomp_priv->tunnel_info);

    ret = HIAVPLAYER_GetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: %s, %d, avplay get hdr static info Error! Avplay handle: %ld, omx handle: %d\n", __func__, __LINE__, ptunnel_info->play_handle, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorNone;
    }

    ptype1 = &(describe_hdr_static_info->sInfo.sType1);
    phdr10info = &(unf_hdr_info.unHdrMetadata.stHdr10Info);

    ptype1->mR.x = phdr10info->stMasteringInfo.u16DisplayPrimaries_x[0];
    ptype1->mR.y = phdr10info->stMasteringInfo.u16DisplayPrimaries_y[0];
    ptype1->mG.x = phdr10info->stMasteringInfo.u16DisplayPrimaries_x[1];
    ptype1->mG.y = phdr10info->stMasteringInfo.u16DisplayPrimaries_y[1];
    ptype1->mB.x = phdr10info->stMasteringInfo.u16DisplayPrimaries_x[2];
    ptype1->mB.y = phdr10info->stMasteringInfo.u16DisplayPrimaries_y[2];
    ptype1->mW.x = phdr10info->stMasteringInfo.u16WhitePoint_x;
    ptype1->mW.y = phdr10info->stMasteringInfo.u16WhitePoint_y;
    ptype1->mMaxDisplayLuminance = phdr10info->stMasteringInfo.u32MaxDisplayMasteringLuminance;
    ptype1->mMinDisplayLuminance = phdr10info->stMasteringInfo.u32MinDisplayMasteringLuminance;
    ptype1->mMaxContentLightLevel = phdr10info->stContentInfo.u32MaxContentLightLevel;
    ptype1->mMaxFrameAverageLightLevel = phdr10info->stContentInfo.u32MaxPicAverageLightLevel;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_set_hdr_static_info(OMX_COMPONENTTYPE *pcomp, DescribeHDRStaticInfoParams *describe_hdr_static_info)
{
    HI_S32 ret = HI_FAILURE;
    HI_UNF_VIDEO_HDR_INFO_S unf_hdr_info = {0};
    Type1 *ptype1 = HI_NULL;
    HI_UNF_VIDEO_HDR10_INFO_S *phdr10info = HI_NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    OMX_TUNNEL_INFO *ptunnel_info = &(pcomp_priv->tunnel_info);

    ret = HIAVPLAYER_GetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info));

    if (ret != HI_SUCCESS)
    {
        unf_hdr_info.enHdrType = HI_UNF_VIDEO_HDR_TYPE_BUTT;
    }

    ptype1 = &(describe_hdr_static_info->sInfo.sType1);
    phdr10info = &(unf_hdr_info.unHdrMetadata.stHdr10Info);

    phdr10info->stMasteringInfo.u16DisplayPrimaries_x[0] = ptype1->mR.x;
    phdr10info->stMasteringInfo.u16DisplayPrimaries_y[0] = ptype1->mR.y;
    phdr10info->stMasteringInfo.u16DisplayPrimaries_x[1] = ptype1->mG.x;
    phdr10info->stMasteringInfo.u16DisplayPrimaries_y[1] = ptype1->mG.y;
    phdr10info->stMasteringInfo.u16DisplayPrimaries_x[2] = ptype1->mB.x;
    phdr10info->stMasteringInfo.u16DisplayPrimaries_y[2] = ptype1->mB.y;
    phdr10info->stMasteringInfo.u16WhitePoint_x = ptype1->mW.x;
    phdr10info->stMasteringInfo.u16WhitePoint_y = ptype1->mW.y;
    phdr10info->stMasteringInfo.u32MaxDisplayMasteringLuminance = ptype1->mMaxDisplayLuminance;
    phdr10info->stMasteringInfo.u32MinDisplayMasteringLuminance = ptype1->mMinDisplayLuminance;
    phdr10info->stContentInfo.u32MaxContentLightLevel = ptype1->mMaxContentLightLevel;
    phdr10info->stContentInfo.u32MaxPicAverageLightLevel = ptype1->mMaxFrameAverageLightLevel;

    ret = HIAVPLAYER_SetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info), HI_TRUE, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: %s, %d, avplay set hdr static info Error! Avplay handle: %ld, omx handle: %d\n", __func__, __LINE__, ptunnel_info->play_handle, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_get_color_aspects(OMX_COMPONENTTYPE *pcomp, DescribeColorAspectsParams *describe_color_aspects_params)
{
    HI_S32 ret = HI_FAILURE;
    Standard standard = 0xff;
    HI_UNF_VIDEO_HDR_INFO_S unf_hdr_info = {0};
    ColorAspects *pcolor_aspects = HI_NULL;
    HI_UNF_VIDEO_HDR10_INFO_S *phdr10info = HI_NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    OMX_TUNNEL_INFO *ptunnel_info = &(pcomp_priv->tunnel_info);

    ret = HIAVPLAYER_GetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info));

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: avplay get hdr static info Error! Avplay handle: %ld, omx handle: %d\n", ptunnel_info->play_handle, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorNone;
    }

    pcolor_aspects = &(describe_color_aspects_params->sAspects);
    phdr10info = &(unf_hdr_info.unHdrMetadata.stHdr10Info);

    pcolor_aspects->mRange = phdr10info->u8FullRangeFlag;

    switch (phdr10info->u8ColourPrimaries)
    {
        case 1:
            pcolor_aspects->mPrimaries = PrimariesBT709_5;
            break;

        case 4:
            pcolor_aspects->mPrimaries = PrimariesBT470_6M;
            break;

        case 5:
            pcolor_aspects->mPrimaries = PrimariesBT601_6_625;
            break;

        case 6:
            pcolor_aspects->mPrimaries = PrimariesBT601_6_525;
            break;

        case 8:
            pcolor_aspects->mPrimaries = PrimariesGenericFilm;
            break;

        case 9:
            pcolor_aspects->mPrimaries = PrimariesBT2020;
            break;

        default:
            pcolor_aspects->mPrimaries = PrimariesOther;
            break;
    }

    switch (phdr10info->u8TransferCharacteristics)
    {
        case 8:
            pcolor_aspects->mTransfer = TransferLinear;
            break;

        case 13:
            pcolor_aspects->mTransfer = TransferSRGB;
            break;

        case 6:
            pcolor_aspects->mTransfer = TransferSMPTE170M;
            break;

        case 4:
            pcolor_aspects->mTransfer = TransferGamma22;
            break;

        case 5:
            pcolor_aspects->mTransfer = TransferGamma28;
            break;

        case 16:
            pcolor_aspects->mTransfer = TransferST2084;
            break;

        case 18:
            pcolor_aspects->mTransfer = TransferHLG;
            break;

        case 7:
            pcolor_aspects->mTransfer = TransferSMPTE240M;
            break;

        case 11:
            pcolor_aspects->mTransfer = TransferXvYCC;
            break;

        case 12:
            pcolor_aspects->mTransfer = TransferBT1361;
            break;

        case 17:
            pcolor_aspects->mTransfer = TransferST428;
            break;

        default:
            pcolor_aspects->mTransfer = TransferOther;
            break;
    }

    switch (phdr10info->u8MatrixCoeffs)
    {
        case 1:
            pcolor_aspects->mMatrixCoeffs = MatrixBT709_5;
            break;

        case 4:
            pcolor_aspects->mMatrixCoeffs = MatrixBT470_6M;
            break;

        case 5:
            pcolor_aspects->mMatrixCoeffs = MatrixBT601_6;
            break;

        case 7:
            pcolor_aspects->mMatrixCoeffs = MatrixSMPTE240M;
            break;

        case 9:
            pcolor_aspects->mMatrixCoeffs = MatrixBT2020;
            break;

        case 10:
            pcolor_aspects->mMatrixCoeffs = MatrixBT2020Constant;
            break;

        default:
            pcolor_aspects->mMatrixCoeffs = MatrixOther;
            break;
    }

    if ((pcolor_aspects->mPrimaries == PrimariesBT709_5)
        && (pcolor_aspects->mMatrixCoeffs == MatrixBT709_5))
    {
        standard = StandardBT709;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT601_6_625)
             && (pcolor_aspects->mMatrixCoeffs == MatrixBT601_6))
    {
        standard = StandardBT601_625;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT601_6_625)
             && (phdr10info->u8MatrixCoeffs == 12 || phdr10info->u8MatrixCoeffs == 13))
    {
        standard = StandardBT601_625_Unadjusted;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT601_6_525)
             && (pcolor_aspects->mMatrixCoeffs == MatrixBT601_6))
    {
        standard = StandardBT601_525;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT601_6_525)
             && (pcolor_aspects->mMatrixCoeffs == MatrixSMPTE240M))
    {
        standard = StandardBT601_525_Unadjusted;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT2020)
             && (pcolor_aspects->mMatrixCoeffs == MatrixBT2020))
    {
        standard = StandardBT2020;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT2020)
             && (pcolor_aspects->mMatrixCoeffs == MatrixBT2020Constant))
    {
        standard = StandardBT2020Constant;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesBT470_6M)
             && (pcolor_aspects->mMatrixCoeffs == MatrixBT470_6M))
    {
        standard = StandardBT470M;
    }
    else if ((pcolor_aspects->mPrimaries == PrimariesGenericFilm)
             && (phdr10info->u8MatrixCoeffs == 12 || phdr10info->u8MatrixCoeffs == 13))
    {
        standard = StandardFilm;
    }
    else
    {
        standard = StandardOther;
    }

    describe_color_aspects_params->nDataSpace.rev = 0;
    describe_color_aspects_params->nDataSpace.range = pcolor_aspects->mRange;
    describe_color_aspects_params->nDataSpace.transfer = pcolor_aspects->mTransfer;
    describe_color_aspects_params->nDataSpace.standard = standard;
    describe_color_aspects_params->nDataSpace.legacy_custom = 0;

    return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_tunnel_set_color_aspects(OMX_COMPONENTTYPE *pcomp, DescribeColorAspectsParams *describe_color_aspects_params)
{
    HI_S32 ret = HI_FAILURE;
    Standard standard = 0xff;
    HI_UNF_VIDEO_HDR_INFO_S unf_hdr_info = {0};
    ColorAspects *pcolor_aspects = HI_NULL;
    HI_UNF_VIDEO_HDR10_INFO_S *phdr10info = HI_NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = (OMX_COMPONENT_PRIVATE *)pcomp->pComponentPrivate;
    OMX_TUNNEL_INFO *ptunnel_info = &(pcomp_priv->tunnel_info);

    pcolor_aspects = &(describe_color_aspects_params->sAspects);

    if ((pcolor_aspects->mTransfer != TransferST2084) && (pcolor_aspects->mTransfer != TransferHLG))
    {
        return OMX_ErrorNone;
    }

    ret = HIAVPLAYER_GetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info));

    phdr10info = &(unf_hdr_info.unHdrMetadata.stHdr10Info);

    phdr10info->u8FullRangeFlag = pcolor_aspects->mRange;

    switch (pcolor_aspects->mPrimaries)
    {
        case PrimariesBT709_5:
            phdr10info->u8ColourPrimaries = 1;
            break;

        case PrimariesBT470_6M:
            phdr10info->u8ColourPrimaries = 4;
            break;

        case PrimariesBT601_6_625:
            phdr10info->u8ColourPrimaries = 5;
            break;

        case PrimariesBT601_6_525:
            phdr10info->u8ColourPrimaries = 6;
            break;

        case PrimariesGenericFilm:
            phdr10info->u8ColourPrimaries = 8;
            break;

        case PrimariesBT2020:
            phdr10info->u8ColourPrimaries = 9;
            break;

        default:
            phdr10info->u8ColourPrimaries = 0xff;
            break;
    }

    switch (pcolor_aspects->mTransfer)
    {
        case TransferLinear:
            phdr10info->u8TransferCharacteristics = 8;
            break;

        case TransferSRGB:
            phdr10info->u8TransferCharacteristics = 13;
            break;

        case TransferSMPTE170M:
            phdr10info->u8TransferCharacteristics = 6;
            break;

        case TransferGamma22:
            phdr10info->u8TransferCharacteristics = 4;
            break;

        case TransferGamma28:
            phdr10info->u8TransferCharacteristics = 5;
            break;

        case TransferST2084:
            phdr10info->u8TransferCharacteristics = 16;
            unf_hdr_info.enHdrType = HI_UNF_VIDEO_HDR_TYPE_HDR10;
            break;

        case TransferHLG:
            phdr10info->u8TransferCharacteristics = 18;
            unf_hdr_info.enHdrType = HI_UNF_VIDEO_HDR_TYPE_HLG;
            break;

        case TransferSMPTE240M:
            phdr10info->u8TransferCharacteristics = 7;
            break;

        case TransferXvYCC:
            phdr10info->u8TransferCharacteristics = 11;
            break;

        case TransferBT1361:
            phdr10info->u8TransferCharacteristics = 12;
            break;

        case TransferST428:
            phdr10info->u8TransferCharacteristics = 17;
            break;

        default:
            phdr10info->u8TransferCharacteristics = 0xff;
            break;
    }

    switch (pcolor_aspects->mMatrixCoeffs)
    {
        case MatrixBT709_5:
            phdr10info->u8MatrixCoeffs = 1;
            break;

        case MatrixBT470_6M:
            phdr10info->u8MatrixCoeffs = 4;
            break;

        case MatrixBT601_6:
            phdr10info->u8MatrixCoeffs = 5;
            break;

        case MatrixSMPTE240M:
            phdr10info->u8MatrixCoeffs = 7;
            break;

        case MatrixBT2020:
            phdr10info->u8MatrixCoeffs = 9;
            break;

        case MatrixBT2020Constant:
            phdr10info->u8MatrixCoeffs = 10;
            break;

        default:
            phdr10info->u8MatrixCoeffs = 0xff;
            break;
    }

    ret = HIAVPLAYER_SetHDRInfo(ptunnel_info->client_player, ptunnel_info->play_handle, &unf_hdr_info, sizeof(unf_hdr_info), HI_TRUE, 0);

    if (ret != HI_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Tunnel:: %s, %d, avplay set color aspects Error! Avplay handle: %ld, omx handle: %d\n", __func__, __LINE__, ptunnel_info->play_handle, pcomp_priv->drv_ctx.chan_handle);

        return OMX_ErrorInsufficientResources;
    }

    return OMX_ErrorNone;
}

#ifdef HI_OMX_TEE_SUPPORT
OMX_ERRORTYPE omx_tunnel_secure_parse_csd(OMXVDEC_BUF_DESC *pBuffer, OMX_TUNNEL_CSD *pcsd)
{
    OMX_S32 ret;
    TEEC_Context omxTeeContext;
    TEEC_Session omxTeeSession;
    TEEC_Result result;
    TEEC_Operation session_operation;
    TEEC_UUID svc_id = {0x3c2bfc84, 0xc03c, 0x11e6, {0xa4, 0xa6, 0xce, 0xc0, 0xc9, 0x32, 0xce, 0x01}};

    result = TEEC_InitializeContext(HI_NULL, &omxTeeContext);

    if (result != TEEC_SUCCESS)
    {
        DEBUG_PRINT_ERROR("%s: %d, TEEC_InitializeContext Failed!\n", __func__, __LINE__);

        return HI_FAILURE;
    }

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.started = 1;
    session_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT);

    result = TEEC_OpenSession(&omxTeeContext, &omxTeeSession, &svc_id, TEEC_LOGIN_IDENTIFY, HI_NULL, &session_operation, HI_NULL);

    if (result != TEEC_SUCCESS)
    {
        DEBUG_PRINT_ERROR("TEEC_OpenSession Failed!\n");
        TEEC_FinalizeContext(&omxTeeContext);

        return HI_FAILURE;
    }

    memset(&session_operation, 0, sizeof(TEEC_Operation));

    session_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    session_operation.started = 1;
    session_operation.params[0].tmpref.buffer = pcsd;
    session_operation.params[0].tmpref.size = sizeof(OMX_TUNNEL_CSD);

    result = TEEC_InvokeCommand(&omxTeeSession, VFMW_CMD_ID_PARSE_CSD, &session_operation, HI_NULL);

    if (result != TEEC_SUCCESS)
    {
        DEBUG_PRINT_ERROR("Invoke command VFMW_CMD_ID_PARSE_CSD failed\n");

        TEEC_CloseSession(&omxTeeSession);
        TEEC_FinalizeContext(&omxTeeContext);

        return HI_FAILURE;
    }

    TEEC_CloseSession(&omxTeeSession);
    TEEC_FinalizeContext(&omxTeeContext);

    return HI_SUCCESS;
}

#endif

