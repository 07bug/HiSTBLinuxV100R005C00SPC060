#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <semaphore.h>
#include <errno.h>

#include "hi_math.h"
#include "omx_drv_ctx.h"
#include "omx_vdec.h"
#include "omx_dbg.h"

OMX_S32 channel_create(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMX_S32 *chan_handle = NULL;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }
    chan_handle = malloc(sizeof(OMX_S32));
    if ( NULL == chan_handle)
    {
        DEBUG_PRINT_ERROR("%s() malloc failed\n", __func__);
        return -1;
    }
    msg.chan_num = -1;
    msg.in       = (HI_SIZE_T)&drv_ctx->drv_cfg;
    msg.out      = (HI_SIZE_T)chan_handle;

    vdec_fd = drv_ctx->video_driver_fd;
    if (ioctl(vdec_fd, VDEC_IOCTL_CHAN_CREATE, &msg) < 0)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);

        free(chan_handle);
        return -1;
    }

    drv_ctx->chan_handle = *chan_handle;
    if ( NULL != chan_handle)
    {
        free(chan_handle);
    }

    return 0;
}

OMX_S32 channel_release(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    if (ioctl(vdec_fd, VDEC_IOCTL_CHAN_RELEASE, &msg) < 0)
    {
        DEBUG_PRINT_ERROR("%s ioctl failed\n", __func__);
        return -1;
    }

    drv_ctx->chan_handle = -1;

    return 0;
}

OMX_S32 channel_start(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_START, &msg);
}

OMX_S32 channel_stop(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_STOP, &msg);
}

OMX_S32 channel_pause(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx ||  (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_PAUSE, &msg);
}

OMX_S32 channel_resume(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_RESUME, &msg);
}

OMX_S32 channel_flush_port(OMXVDEC_DRV_CONTEXT *drv_ctx, OMX_U32 flush_dir)
{
    OMX_S32 dir;
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    dir          = flush_dir;
    msg.in       = (HI_SIZE_T)(&dir);
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_FLUSH_PORT, (void *)&msg);
}

OMX_S32 channel_get_msg(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_MSG_INFO *msginfo)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == msginfo)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    if (drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s chan_handle(%d) invalid!", __func__, drv_ctx->chan_handle);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.out      = (HI_SIZE_T)msginfo;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_GET_MSG, (void *)&msg);
}

OMX_S32 channel_stop_msg(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_STOP_MSG, (void *)&msg);
}

OMX_S32 channel_submit_stream(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_EMPTY_INPUT_STREAM, (void *)&msg);
}

OMX_S32 channel_submit_frame(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_FILL_OUTPUT_FRAME, (void *)&msg);
}

OMX_S32 channel_bind_buffer(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_BUF_DESC *pbuf_desc = puser_buf;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == pbuf_desc || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)pbuf_desc;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_BIND_BUFFER, (void *)&msg);
}

OMX_S32 channel_port_enable(OMXVDEC_DRV_CONTEXT* drv_ctx, OMX_BOOL bEnable)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};
    OMX_BOOL bPortEnable = bEnable;

    if (NULL == drv_ctx ||  (drv_ctx->chan_handle < 0))
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)&bPortEnable;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_PORT_ENABLE, &msg);
}

OMX_S32 channel_unbind_buffer(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_UNBIND_BUFFER, (void *)&msg);
}

OMX_S32 channel_alloc_buffer(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 ret = 0;
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = (HI_SIZE_T)puser_buf;

    ret = ioctl(vdec_fd, VDEC_IOCTL_CHAN_ALLOC_BUF, (void *)&msg);
    if (ret < 0)
    {
        DEBUG_PRINT_ERROR("alloc buffer failed\n");
        return ret;
    }

    return ret;
}

void channel_release_buffer(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};
    OMX_S32 ret = 0;

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    ret = ioctl(vdec_fd, VDEC_IOCTL_CHAN_RELEASE_BUF, (void *)&msg);
    if (ret < 0)
    {
        DEBUG_PRINT_ERROR("release buffer failed\n");
        return;
    }
}

void vdec_deinit_drv_context(OMXVDEC_DRV_CONTEXT  *drv_ctx)
{
    OMX_S32 ret;

    if (NULL == drv_ctx)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return;
    }

    if (drv_ctx->chan_handle >= 0)
    {
        ret = channel_release(drv_ctx);
        if (ret != 0)
        {
            DEBUG_PRINT_ERROR("%s: %d channel_release handle(%d) return error\n", __func__, __LINE__, drv_ctx->chan_handle);
        }
    }

    if (drv_ctx->video_driver_fd >= 0)
    {
        close(drv_ctx->video_driver_fd);
        drv_ctx->video_driver_fd = -1;
    }

    if (drv_ctx->yuv_fp != NULL)
    {
        fclose(drv_ctx->yuv_fp);
        drv_ctx->yuv_fp = NULL;
    }

    if (drv_ctx->chrom_l != NULL)
    {
        free(drv_ctx->chrom_l);
        drv_ctx->chrom_l = NULL;
        drv_ctx->chrom_l_size = 0;
    }

    return;
}

OMX_S32 vdec_init_drv_context(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    VDEC_CHAN_CFG_S *pchan_cfg = HI_NULL;

    if (!drv_ctx)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    drv_ctx->video_driver_fd = open(DRIVER_PATH, O_RDWR);
    if (drv_ctx->video_driver_fd < 0)
    {
        DEBUG_PRINT_ERROR("%s open %s failed\n", __func__, DRIVER_PATH);
        return -1;
    }

    drv_ctx->chan_handle                  = -1;

    memset(&drv_ctx->drv_cfg, 0, sizeof(drv_ctx->drv_cfg));
#ifdef HI_OMX_TEE_SUPPORT
    drv_ctx->drv_cfg.is_tvp           = HI_TRUE;
#else
    drv_ctx->drv_cfg.is_tvp           = HI_FALSE;
#endif
    drv_ctx->drv_cfg.cfg_width        = DEFAULT_FRAME_WIDTH;
    drv_ctx->drv_cfg.cfg_height       = DEFAULT_FRAME_HEIGHT;
    drv_ctx->drv_cfg.cfg_stride       = HI_SYS_GET_STRIDE(DEFAULT_FRAME_WIDTH);
    drv_ctx->drv_cfg.cfg_inbuf_num    = MAX_IN_BUF_SLOT_NUM_ON_LIVE;
    drv_ctx->drv_cfg.cfg_outbuf_num   = MAX_OUT_BUF_SLOT_NUM;
    drv_ctx->drv_cfg.cfg_color_format = HI_DRV_PIX_FMT_NV21;

    pchan_cfg = &(drv_ctx->drv_cfg.chan_cfg);
    memset(pchan_cfg, 0, sizeof(VDEC_CHAN_CFG_S));

    pchan_cfg->s32ChanPriority     = 1;
    pchan_cfg->s32ChanErrThr       = 100;
    pchan_cfg->s32DecMode          = IPB_MODE;
    pchan_cfg->s32DecOrderOutput   = 0;
    pchan_cfg->s32ChanStrmOFThr    = 0;
    pchan_cfg->s32VcmpEn           = 0;
    pchan_cfg->s32VcmpWmStartLine  = 0;
    pchan_cfg->s32WmEn             = 0;
    pchan_cfg->s32VcmpWmEndLine    = 0;
    pchan_cfg->s32IsOmxPath        = 1;
    pchan_cfg->s32MaxRawPacketNum  = DEF_MAX_IN_BUF_CNT_ON_LIVE;
    pchan_cfg->s32MaxRawPacketSize = DEFAULT_IN_BUF_SIZE_ON_LIVE;

    return 0;
}

#ifdef VFMW_VPSS_BYPASS_EN
OMX_S32 channel_release_frame_inter(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_RELEASE_FRAME, (void *)&msg);
}

OMX_S32 channel_record_occupied_info(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = 0;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_RECORD_OCCUPIED_FRAME, (void *)&msg);
}

OMX_S32 channel_getVpssBypassInfo(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMX_BOOL VpssBypass = 0;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)&drv_ctx->drv_cfg;
    msg.out      = (HI_SIZE_T)&VpssBypass;

    vdec_fd = drv_ctx->video_driver_fd;
    if (ioctl(vdec_fd, VDEC_IOCTL_CHAN_GET_BYPASS_INFO, &msg) < 0)
    {
        DEBUG_PRINT_ERROR("%s failed! w= %d,h= %d\n", __func__,drv_ctx->drv_cfg.cfg_width,drv_ctx->drv_cfg.cfg_height);
        return -1;
    }

    drv_ctx->drv_cfg.bVpssBypass = (VpssBypass == 1)? 1 : 0;

    return 0;
}

OMX_S32 channel_setVpssBypassInfo(OMXVDEC_DRV_CONTEXT *drv_ctx)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)&drv_ctx->drv_cfg;
    msg.out      = 0;

    vdec_fd = drv_ctx->video_driver_fd;
    if (ioctl(vdec_fd, VDEC_IOCTL_CHAN_SET_BYPASS_INFO, &msg) < 0)
    {
        DEBUG_PRINT_ERROR("%s failed\n", __func__);
        return -1;
    }

    return 0;
}

#ifdef HI_TVOS_SUPPORT
OMX_S32 channel_global_release_frame(OMXVDEC_DRV_CONTEXT *drv_ctx, OMXVDEC_BUF_DESC *puser_buf)
{
    OMX_S32 vdec_fd = -1;
    OMXVDEC_IOCTL_MSG msg = {0, 0, 0};

    if (NULL == drv_ctx || NULL == puser_buf || drv_ctx->chan_handle < 0)
    {
        DEBUG_PRINT_ERROR("%s param invalid!\n", __func__);
        return -1;
    }

    vdec_fd      = drv_ctx->video_driver_fd;
    msg.chan_num = drv_ctx->chan_handle;
    msg.in       = (HI_SIZE_T)puser_buf;
    msg.out      = 0;

    return ioctl(vdec_fd, VDEC_IOCTL_CHAN_GLOBAL_RELEASE_FRAME, (void *)&msg);
}
#endif

#endif

