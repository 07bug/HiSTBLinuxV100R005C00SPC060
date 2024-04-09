#ifndef __OMX_VDEC_H__
#define __OMX_VDEC_H__

//khrons standard head file
#include <pthread.h>
#include <semaphore.h>

#include "OMX_Component.h"
#include "OMX_Video.h"
#include "OMX_VideoExt.h"
#include "OMX_IndexExt.h"
#include "OMX_RoleNames.h"

#include "drv_omxvdec.h"
#include "omx_event_queue.h"
#include "omx_drv_ctx.h"

#ifdef ANDROID
#include "omx_tunnel.h"
#endif

#define MAX_PORT_NUM                       (2)

#define DEFAULT_FPS                        (30 * 1000)
#define MAX_FRAME_RATE                     (120 * 1000)
#define DEFAULT_ALIGN_SIZE                 (4096)

#define DEFAULT_IN_BUF_SIZE                (5 * 1024 * 1024)
#define DEFAULT_IN_BUF_SIZE_ON_LIVE        (32 * 1024)//(64 * 1024)

/***********************************************************************
   NOTICE!!
   IN_BUF_CNT & OUT_BUF_CNT should be no more than MIN(MAX_BUFF_NUM,32),
   MAX_BUFF_NUM is defined in channel.h
***********************************************************************/

#define DEF_MAX_IN_BUF_CNT_ON_LIVE         (320)

#define MAX_IN_BUF_SLOT_NUM                (4)
#define MAX_IN_BUF_SLOT_NUM_ON_LIVE        (400)

//the max num can be recorded by component, default DEF_MAX_OUT_BUF_CNT + 2, can be changed if needed
#define MAX_OUT_BUF_SLOT_NUM               (8)

#define BITS_PER_LONG                      (32)

#define COUNTOF(x)                         (sizeof(x)/sizeof(x[0]))

#define OMX_CHECK_ARG(x) \
    if ((x)) \
    {\
        DEBUG_PRINT_ERROR("[%s]"#x"\n", __func__);\
        return;\
    }

#define OMX_CHECK_ARG_RETURN(x) \
    if ((x)) \
    {\
        DEBUG_PRINT_ERROR("[%s]"#x"\n", __func__);\
        return OMX_ErrorBadParameter;\
    }

#define ALIGN_UP(val, align)               (((val) + ((align)-1)) & ~((align)-1))

#define OMX_VIDEO_FORMAT_SWITCH(source, dest) \
    do { \
        switch ((source)) \
        { \
            case STD_MPEG2: \
                (dest) = HI_UNF_VCODEC_TYPE_MPEG2; \
                break; \
            case STD_MPEG4: \
                (dest) = HI_UNF_VCODEC_TYPE_MPEG4; \
                break; \
            case STD_AVS: \
                (dest) = HI_UNF_VCODEC_TYPE_AVS; \
                break; \
            case STD_AVS2: \
                (dest) = HI_UNF_VCODEC_TYPE_AVS2; \
                break; \
            case STD_H263: \
                (dest) = HI_UNF_VCODEC_TYPE_H263; \
                break; \
            case STD_H264: \
                (dest) = HI_UNF_VCODEC_TYPE_H264; \
                break; \
            case STD_REAL8: \
                (dest) = HI_UNF_VCODEC_TYPE_REAL8; \
                break; \
            case STD_REAL9: \
                (dest) = HI_UNF_VCODEC_TYPE_REAL9; \
                break; \
            case STD_VC1: \
                (dest) = HI_UNF_VCODEC_TYPE_VC1; \
                break; \
            case STD_VP6: \
                (dest) = HI_UNF_VCODEC_TYPE_VP6; \
                break; \
            case STD_VP6F: \
                (dest) = HI_UNF_VCODEC_TYPE_VP6F; \
                break; \
            case STD_VP6A: \
                (dest) = HI_UNF_VCODEC_TYPE_VP6A; \
                break; \
            case STD_DIVX3: \
                (dest) = HI_UNF_VCODEC_TYPE_DIVX3; \
                break; \
            case STD_RAW: \
                (dest) = HI_UNF_VCODEC_TYPE_RAW; \
                break; \
            case STD_JPEG: \
                (dest) = HI_UNF_VCODEC_TYPE_JPEG; \
                break; \
            case STD_VP8: \
                (dest) = HI_UNF_VCODEC_TYPE_VP8; \
                break; \
            case STD_HEVC: \
                (dest) = HI_UNF_VCODEC_TYPE_HEVC; \
                break; \
            case STD_VP9: \
                (dest) = HI_UNF_VCODEC_TYPE_VP9; \
                break; \
            default: \
                (dest) = HI_UNF_VCODEC_TYPE_BUTT; \
                break; \
        } \
    } while (0)

// state transactions pending bits
enum flags_bit_positions
{
    OMX_STATE_IDLE_PENDING               = 0x1,
    OMX_STATE_LOADING_PENDING            = 0x2,
    OMX_STATE_INPUT_ENABLE_PENDING       = 0x3,
    OMX_STATE_OUTPUT_ENABLE_PENDING      = 0x4,
    OMX_STATE_OUTPUT_DISABLE_PENDING     = 0x5,
    OMX_STATE_INPUT_DISABLE_PENDING      = 0x6,
    OMX_STATE_OUTPUT_FLUSH_PENDING       = 0x7,
    OMX_STATE_INPUT_FLUSH_PENDING        = 0x8,
    OMX_STATE_PAUSE_PENDING              = 0x9,
    OMX_STATE_EXECUTE_PENDING            = 0xA,
};

// Deferred callback identifiers
enum
{
    OMX_GENERATE_COMMAND_DONE           = 0x1,
    OMX_GENERATE_FTB                    = 0x2,
    OMX_GENERATE_ETB                    = 0x3,
    OMX_GENERATE_COMMAND                = 0x4,
    OMX_GENERATE_EBD                    = 0x5,
    OMX_GENERATE_FBD                    = 0x6,
    OMX_GENERATE_FLUSH_INPUT_DONE       = 0x7,
    OMX_GENERATE_FLUSH_OUTPUT_DONE      = 0x8,
    OMX_GENERATE_START_DONE             = 0x9,
    OMX_GENERATE_PAUSE_DONE             = 0xA,
    OMX_GENERATE_RESUME_DONE            = 0xB,
    OMX_GENERATE_STOP_DONE              = 0xC,
    OMX_GENERATE_EOS_DONE               = 0xD,
    OMX_GENERATE_HARDWARE_ERROR         = 0xE,
    OMX_GENERATE_IMAGE_SIZE_CHANGE      = 0xF,
    OMX_GENERATE_DYNAMIC_ALLOC_ERROR    = 0x10,
    OMX_GENERATE_UNUSED                 = 0x11,
};

enum
{
    INPUT_PORT_INDEX    = 0,
    OUTPUT_PORT_INDEX   = 1,
};

struct port_property
{
    OMX_U32 port_dir;
    OMX_U32 min_count;
    OMX_U32 max_count;
    OMX_U32 buffer_size;
    OMX_U32 alignment;
};

struct omx_hisi_extern_index
{
    OMX_S8 index_name[OMX_MAX_STRINGNAME_SIZE];
    OMX_HISI_EXTERN_INDEXTYPE index_type;
};

struct codec_info
{
    const OMX_STRING role_name;
    OMX_S32 compress_fmt;
    VDEC_CODEC_TYPE codec_type;
};

struct codec_profile_level
{
    OMX_S32 profile;
    OMX_S32 level;
};

struct frame_info
{
    OMX_U32 frame_width;
    OMX_U32 frame_height;
    OMX_U32 max_frame_width;
    OMX_U32 max_frame_height;
    OMX_U32 stride;
    OMX_U32 scan_lines;
};

struct omx_vdec_time_info
{
    OMX_U32 etb_lasttime;
    OMX_U32 ebd_lasttime;
    OMX_U32 ftb_lasttime;
    OMX_U32 fbd_lasttime;
};

// port private for omx
typedef struct OMX_PORT_PRIVATE
{
    OMX_BUFFERHEADERTYPE **m_omx_bufhead;
    struct port_property port_pro;

    OMX_U32 m_port_index;

    OMX_U32 m_cur_buf_num;

    OMX_BOOL m_port_enabled;
    OMX_BOOL m_port_populated;

    OMX_BOOL m_port_reconfig;
    OMX_BOOL m_port_flushing;
} OMX_PORT_PRIVATE;


// Decode Protocal Parameter
typedef union
{
    OMX_VIDEO_PARAM_AVCTYPE avc;
    OMX_VIDEO_PARAM_VC1TYPE vc1;
    OMX_VIDEO_PARAM_MPEG2TYPE mpeg2;
    OMX_VIDEO_PARAM_MPEG4TYPE mpeg4;
    OMX_VIDEO_PARAM_H263TYPE h263;
    OMX_VIDEO_PARAM_VP6TYPE vp6;
    OMX_VIDEO_PARAM_VP8TYPE vp8;
    OMX_VIDEO_PARAM_WMVTYPE wmv;
    OMX_VIDEO_PARAM_RVTYPE rv;
    OMX_VIDEO_PARAM_HEVCTYPE hevc;
} CodecParam;

//component private for omx
typedef struct OMX_COMPONENT_PRIVATE
{
    pthread_mutex_t m_lock;
    OMX_COMPONENTTYPE *m_pcomp;
    OMX_STATETYPE m_state;
    OMX_U32 m_flags;

    CodecParam m_codec_param;

    OMX_VIDEO_CODINGTYPE m_dec_fmt;
    OMX_U8 m_role[OMX_MAX_STRINGNAME_SIZE];

    OMX_PTR m_app_data;
    OMX_CALLBACKTYPE m_cb;

    OMX_U32 m_frame_rate;
    OMX_TICKS m_pre_timestamp;

    OMX_PORT_PRIVATE m_port[MAX_PORT_NUM];
    //OMX_BOOL m_use_native_buf;
    OMX_BOOL m_input_use_native_buf;
    OMX_BOOL m_output_use_native_buf;
    OMX_BOOL is_adaptive;
    pthread_t msg_thread_id;
    pthread_t event_thread_id;

    OMX_BOOL event_thread_exit;
    OMX_BOOL msg_thread_exit;

    OMXVDEC_DRV_CONTEXT drv_ctx;
    OMX_TUNNEL_CSD csd;
    struct frame_info pic_info;

    int m_pipe_in;
    int m_pipe_out;

    sem_t m_cmd_lock;

    int m_async_pipe[2];

    omx_event_queue m_ftb_q;
    omx_event_queue m_cmd_q;
    omx_event_queue m_etb_q;

    struct omx_vdec_time_info time_info;
#ifdef ANDROID
    OMX_TUNNEL_INFO tunnel_info;
#endif
} OMX_COMPONENT_PRIVATE;

typedef struct
{
    OMX_U32 frame_addr;
    OMX_U32 metadata_addr;
} private_handle_gst;

/*========================= bit operation functions =================================*/
static inline void bit_set(OMX_U32 *addr, OMX_U32 nr)
{
    addr[nr / BITS_PER_LONG] |= (1 << (nr % BITS_PER_LONG));
}

static inline void bit_clear(OMX_U32 *addr, OMX_U32 nr)
{
    addr[nr / BITS_PER_LONG] &= ~((OMX_U32)(1 << (nr % BITS_PER_LONG)));
}

static inline OMX_S32 bit_present(const OMX_U32 *addr, OMX_U32 nr)
{
    return ((1 << (nr % BITS_PER_LONG)) & (((OMX_U32 *)addr)[nr / BITS_PER_LONG])) != 0;
}

static inline OMX_S32 bit_absent(const OMX_U32 *addr, OMX_U32 nr)
{
    return !bit_present(addr, nr);
}

OMX_ERRORTYPE omx_report_event(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_IN OMX_EVENTTYPE event_type, OMX_IN OMX_U32 param1, OMX_IN OMX_U32 param2, OMX_IN OMX_PTR pdata);

#endif // __OMX_VDEC_H__
