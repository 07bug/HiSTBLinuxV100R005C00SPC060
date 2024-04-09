/**************************************************************************//**

  Copyright (C), 2001-2012, Huawei Tech. Co., Ltd.

 ******************************************************************************
 * @file    gstsmevideosink_hihal.h
 * @brief   android hisi37xx vdec&vdisppipe
 * @author  XXX
 * @date    2015/12/4
 * @version VFP xxxxxxxxx
 * History:
 *
 * Number : V1.00
 * Date   : 2015/12/4
 * Author : XXX
 * Desc   : Created file
 *
******************************************************************************/
#ifndef __GST_SME_VIDEO_SINK_HIHAL_H__
#define __GST_SME_VIDEO_SINK_HIHAL_H__


#include <sys/time.h>
#include "sme_wrap_hisi_hal_vo.h"

#ifdef SME_TVP_SMMU_SUPPORT
#define HI_SMMU_SUPPORT //use by hisi SDK, this macro enable HISI SMMU.
#include "mpi_mmz.h"
#endif

#include <gst/gst.h>
#include <gst/video/video.h>



#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

#define GST_TYPE_SME_VIDEOSINK_HIHAL (gst_smevideosink_hihal_get_type())
#define GST_SME_VIDEOSINK_HIHAL(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_SME_VIDEOSINK_HIHAL, GstSmeVideoSinkHiHal))
#define GST_SME_VIDEOSINK_HIHAL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_SME_VIDEOSINK_HIHAL, GstSmeVideoSinkHiHal))
#define GST_IS_SME_VIDEOSINK_HIHAL(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SME_VIDEOSINK_HIHAL))
#define GST_IS_SME_VIDEOSINK_HIHAL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SME_VIDEOSINK_HIHAL))

typedef struct _GstSmeVideoSinkHiHal GstSmeVideoSinkHiHal;
typedef struct _GstSmeVideoSinkHiHalClass GstSmeVideoSinkHiHalClass;

typedef struct _GstVideoFrameMap
{
    gpointer pvAddr;
    GstBuffer* gstvbuf;
    gpointer pvPhyAddr;

}GstVideoFrameMap;

typedef struct _GstMmzInfo
{
    HI_MMZ_BUF_S stMmzBuf;
    gpointer pVirAddr;
    gpointer pPhyAddr;
    gboolean mmz_is_vo;
}GstMmzInfo;

#ifdef ENABLE_SECURE_PATH
typedef struct _GstSecMemInfo
{
#ifdef SME_TVP_SMMU_SUPPORT // TVP_SMMU for 3751v620
    HI_MPI_SMMU_SEC_BUF_S sec_buf_s;
#endif
    gpointer pPhyAddr;
    gboolean mmz_is_vo;
}GstSecMemInfo;
#endif

typedef struct _GstCapsResolution
{
    gint Width;
    gint Height;
}GstCapsResolution;

typedef enum __tagSmeDisPlayMode
{
    E_SME_DIS_MODE_FULL = 0,
    E_SME_DIS_MODE_FITIN,
    E_SME_DIS_MODE_FITOUT,
    E_SME_DIS_MODE_FITCENTER,
    E_SME_DIS_MODE_DEFAULT,
    E_SME_DIS_MODE_NONE,
    E_SME_DIS_MODE_BUTT,
}E_SME_DISPLAY_MODE;

typedef struct
{
    /* 应用设置的宽高比 */
    guint32 u32DispRatioW;
    guint32 u32DispRatioH;
}ST_DISP_RATIO;

typedef enum __tagSmeSwitchChannelMode
{
    E_SME_SWITCH_CHANNEL_MODE_BLACK = 0, //black
    E_SME_SWITCH_CHANNEL_MODE_LAST,//static frame
    E_SME_SWITCH_CHANNEL_MODE_BUTT,
} E_SME_SWITCH_CHANNEL_MODE;

struct _GstSmeVideoSinkHiHal
{
    GstBaseSink             element;

    ST_SME_DISP_RECT        st_vdisp_rect;       //视频显示范围
    SME_HAL_VDISP_PIPE_HDL  hdl_sme_pipe_hihal;
    gboolean                recieve_eos;
    void*                   android_surface;

    //ST_SME_VIDEOINFO        stVideoInfo;
    GstCapsResolution       resolution_from_caps;
    GThread*                dequeue_thd;
    gboolean                is_dequeue_thd_exit;
    GMutex                  rendered_buf_muxtex;
    GQueue                  q_rendered_buf;
    GQueue                  q_to_be_Free;
    GQueue                  q_mmz_is_vo;
    GMutex                  mmz_is_vo_muxtex;
#ifdef USE_DUMP_DECED_DATA
    FILE*                   dump_deced_data;
#endif


    /* BEGIN:for display setting */
    E_SME_DISPLAY_MODE e_disp_mode;
    ST_DISP_RATIO st_disp_ratio;
    ST_OUT_RECT st_win_rect;

    E_SME_DISPLAY_MODE e_old_disp_mode;
    ST_DISP_RATIO st_old_disp_ratio;
    ST_OUT_RECT st_old_win_rect;
    gboolean first_frame_flag;
    /* END:for display setting */
    struct timeval          current_play_timeUs;

    //refresh
    gboolean                needs_refresh;

    gboolean                is_flushing;
    E_SME_SWITCH_CHANNEL_MODE switch_channel_mode;
    gboolean                dump_raw_switch;
    FILE                    *dump_raw_loca;
    guint32                 u32_late_count;
    guint32                 u32_drop_interleave;
    E_SME_SWITCH_CHANNEL_MODE freeze_mode;
    gboolean                is_first_frame;
    gboolean                is_first_render;
    gboolean                use_tvp;
};

struct _GstSmeVideoSinkHiHalClass
{
    GstBaseSinkClass parent_class;
};


gboolean
gst_smevideosink_hihal_register (GstPlugin * plugin);
GType gst_smevideosink_hihal_get_type (void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif//__GST_SME_VIDEO_SINK_HIHAL_H__
