#ifndef __VDEC_FIRMWARE_H__
#define __VDEC_FIRMWARE_H__
#if defined(VFMW_EXTRA_TYPE_DEFINE)
#include "hi_type.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define VFMW_VPSS_BYPASS_EN

#define VFMW_MAX_RESERVE_NUM  (32)

#if defined(VFMW_EXTRA_TYPE_DEFINE)
#define UINT64 HI_U64
#define SINT64 HI_S64
#define UINT32 HI_U32
#define SINT32 HI_S32
#define UINT16 HI_U16
#define SINT16 HI_S16
#define UINT8  HI_U8
#define SINT8  HI_S8
#define VOID   HI_VOID
#define UADDR  HI_U32
#define ULONG  HI_SIZE_T
typedef  const void                    CONSTVOID;
typedef  unsigned                      USIGN;

#else
typedef  unsigned long long        UINT64;
typedef  long long                 SINT64;
typedef  unsigned int              UINT32;
typedef  int                       SINT32;
typedef  unsigned short            UINT16;
typedef  short                     SINT16;
typedef  char                      SINT8;
typedef  unsigned char             UINT8;
typedef  unsigned int              UADDR;
typedef  const void                CONSTVOID;
typedef  unsigned                  USIGN;
typedef  unsigned long             ULONG;
#ifndef VOID
typedef  void                      VOID;
#endif
#endif

#ifdef NULL
#undef NULL
#define NULL                0L
#endif

#if !defined(ENV_SOS_KERNEL)
#define COMMAND_LINE_EXTRA 1
#endif

#define SCD_INPUT_SMMU    1
#define SCD_INPUT_MMZ     0

/***********************************************************************
      constants
 ***********************************************************************/
/* chip type definition. */
/* STB */
#define  VFMW_CHIP_TYPE_Hi3720         0
#define  VFMW_CHIP_TYPE_Hi3716C        1
#define  VFMW_CHIP_TYPE_Hi3716H        2
#define  VFMW_CHIP_TYPE_Hi3716M        3
#define  VFMW_CHIP_TYPE_Hi3716L        4
#define  VFMW_CHIP_TYPE_Hi3716MV300    5
#define  VFMW_CHIP_TYPE_Hi3712V100     6
#define  VFMW_CHIP_TYPE_Hi3715V100     7
#define  VFMW_CHIP_TYPE_Hi3716CV200ES  8
#define  VFMW_CHIP_TYPE_Hi3716CV200    9
#define  VFMW_CHIP_TYPE_Hi3798MV100    10
#define  VFMW_CHIP_TYPE_Hi3798CV200_A  11
#define  VFMW_CHIP_TYPE_Hi3716MV410    12
#define  VFMW_CHIP_TYPE_Hi3798CV200    13
#define  VFMW_CHIP_TYPE_Hi3798MV200    14
#define  VFMW_CHIP_TYPE_HI3798MV200_A  15
#define  VFMW_CHIP_TYPE_Hi3796MV200    16

/* BVT */
#define  VFMW_CHIP_TYPE_Hi3531         50
#define  VFMW_CHIP_TYPE_Hi3535         51
#define  VFMW_CHIP_TYPE_Hi3536         52

/* DPT */
#define  VFMW_CHIP_TYPE_HiS5V100       100
#define  VFMW_CHIP_TYPE_HiS5V600       101
#define  VFMW_CHIP_TYPE_HiS5LV500      102
#define  VFMW_CHIP_TYPE_HiS5V500       103
#define  VFMW_CHIP_TYPE_HiS5V620       104

/* VFMW API return value */
#define  VDEC_OK                 0
#define  VDEC_ERR               -1
#define  VDEC_ERR_WRONG_PARAM   -2
#define  VDEC_ERR_NO_MEM        -3
#define  VDEC_ERR_VDEC_BUSY     -4
#define  VDEC_ERR_CHAN_FULL     -5
#define  VDEC_ERR_CHAN_RUN      -6
#define  VDEC_ERR_CHAN_STOP     -7
#define  VDEC_ERR_UNSUPPORT     -8

/* formal definition, to be removed later */
#define  VF_OK                   1
#define  VF_NO_MEM              -1
#define  VF_ERR_PARAM           -2
#define  VF_TIME_OUT            -3
#define  VF_VDM_ERR             -4
#define  VF_FORCE_STOP          -5
#define  VF_ERR_SYS             -20
#define  VF_ERR_SPS             -21
#define  VF_ERR_PPS             -22
#define  VF_ERR_SLICE           -23

#ifdef CFG_MAX_CHAN_NUM
#define MAX_CHAN_NUM CFG_MAX_CHAN_NUM
#else
#define MAX_CHAN_NUM 32
#endif

#ifdef HI_TEE_SUPPORT
#ifdef ENV_SOS_KERNEL
#define FIRST_CHAN_NUM         (MAX(0, MAX_CHAN_NUM / 2))
#define LAST_CHAN_NUM          (MAX_CHAN_NUM)
#else
#define FIRST_CHAN_NUM         (0)
#define LAST_CHAN_NUM          (MAX(FIRST_CHAN_NUM, MAX_CHAN_NUM / 2))
#endif
#else
#define FIRST_CHAN_NUM         (0)
#define LAST_CHAN_NUM          (MAX_CHAN_NUM)
#endif

#define PROTECTED_SPACE (4 * 1024)

/* extream value */
#define MAX_USRDAT_SIZE        (1024)

/* MUST be multiple of 2 */
#define MAX_QUEUE_IMAGE_NUM    (64)

/* bool definition */
typedef enum
{
    VDEC_FALSE = 0,
    VDEC_TRUE  = 1,
} VBOOL;

/* DAR(Display Aspect Ratio) */
typedef enum
{
    DAR_UNKNOWN = 0,
    DAR_4_3,
    DAR_16_9,
    DAR_221_100,
    DAR_235_100,
    DAR_IMG_SIZE,
    DAR_END_RESERVED
} VDEC_DAR_E;

#define PLUS_FS_NUM  3

#define MIN_USERDEC_FRAME_NUM 3

#define PTS_NO_USE (UINT64)(-1)

#define MAX_HDR_METADATA_SIZE          1 * 1024 /**< HDR metadata size*/

#define DOLBY_VISION_HDR_SUPPORT //for metadata 2015-07-21
#ifdef DOLBY_VISION_HDR_SUPPORT
#define HIGH_PROFILE_MAX_BITSTREAM_SIZE          64 * 1024 /**< HDR metadata size*/
#define MAIN_PROFILE_MAX_BITSTREAM_SIZE          16 * 1024 /**< HDR metadata size*/
#define BASE_PROFILE_MAX_BITSTREAM_SIZE           1 * 1024 /**< HDR metadata size*/
//#define DFS_OFF_TEST_SUPPORT //for metadata 2015-07-31

//for metadata 2015-08-07

/*! Dolby Vision elementary stream codec capacity*/
typedef enum
{
    DV_BL_DECODING_SUPPORT = 0,       /**<support decoding BL elementary stream only*/
    DV_EL_DECODING_SUPPORT,           /**<support decoding EL elementary stream only*/
    DV_DECODING_BUTT,
} DV_CODEC_CAP_E_;


/*!  Dolby Vision elementary stream codec type*/
typedef enum
{
    DV_AVC_CODEC = 0,                 /**< AVC/H.264 elementary stream */
    DV_HEVC_CODEC,                    /**<HEVC/H.265 elementary stream */
    DV_METADATA_CODEC,                /**< DV Metadata elementary stream */
    DV_MAX_CODEC
} DV_ES_CODEC_E_;


/*!  Dolby Vision elementary stream type*/
typedef enum
{
    DV_BASE_LAYER_ES,           /**<base layer elementary stream */
    DV_ENHANCEMENT_LAYER_ES,    /**<enhancement layer elementary stream */
    DV_METADATA_ES,             /**<metadata elementary stream */
    DV_MAX_ES
} DV_ES_E_;


/*!  Dolby Vision VES implementation type*/
typedef enum
{
    DV_SINGLE_VES_IMP = 1,     /**<single VES implementation*/
    DV_DUAL_VES_IMP,           /**<dual VES implementation*/
    DV_MAX_VES_IMP
} DV_VES_IMP_E_;

/*! Dolby Vision layer implementation type*/
typedef enum
{
    DV_SINGLE_LAYER_IMP = 1,     /*single VES implementation */
    DV_DUAL_LAYER_IMP,           /*dual VES implementation */
    DV_MAX_LAYER_IMP
} DV_LAYER_IMP_E_;
#endif

// standard type
typedef enum
{
    VFMW_START_RESERVED = 0,
    VFMW_H264 = 0,
    VFMW_VC1,
    VFMW_MPEG4,
    VFMW_MPEG2,
    VFMW_H263,
    VFMW_DIVX3,
    VFMW_AVS,
    VFMW_JPEG,
    VFMW_REAL8 = 8,
    VFMW_REAL9 = 9,
    VFMW_VP6   = 10,
    VFMW_VP6F,
    VFMW_VP6A,
    VFMW_VP8,
    VFMW_SORENSON,
    VFMW_MVC,
    VFMW_HEVC,
    VFMW_VP9,
    VFMW_AVS2,
    VFMW_RAW,
    VFMW_USER,           /*## vfmw simply provide frame path. for external decoder, eg. mjpeg ##*/
    VFMW_Dolby_Vision,
    VFMW_END_RESERVED
} VID_STD_E;

#define STD_START_RESERVED VFMW_START_RESERVED
#define STD_H264           VFMW_H264
#define STD_VC1            VFMW_VC1
#define STD_MPEG4          VFMW_MPEG4
#define STD_MPEG2          VFMW_MPEG2
#define STD_H263           VFMW_H263
#define STD_DIVX3          VFMW_DIVX3
#define STD_AVS            VFMW_AVS
#define STD_AVS2           VFMW_AVS2
#define STD_JPEG           VFMW_JPEG
#define STD_REAL8          VFMW_REAL8
#define STD_REAL9          VFMW_REAL9
#define STD_VP6            VFMW_VP6
#define STD_VP6F           VFMW_VP6F
#define STD_VP6A           VFMW_VP6A
#define STD_VP8            VFMW_VP8
#define STD_SORENSON       VFMW_SORENSON
#define STD_MVC            VFMW_MVC
#define STD_HEVC           VFMW_HEVC
#define STD_VP9            VFMW_VP9
#define STD_RAW            VFMW_RAW
#define STD_USER           VFMW_USER
#define STD_Dolby_Vision   VFMW_Dolby_Vision
#define STD_END_RESERVED   VFMW_END_RESERVED

/* buffer flags bits masks omx buffer flag. */
#define VDEC_BUFFERFLAG_EOS               (0x00000001)
#define VDEC_BUFFERFLAG_STARTTIME         (0x00000002)
#define VDEC_BUFFERFLAG_DECODEONLY        (0x00000004)
#define VDEC_BUFFERFLAG_DATACORRUPT       (0x00000008)
#define VDEC_BUFFERFLAG_ENDOFFRAME        (0x00000010)
#define VDEC_BUFFERFLAG_SYNCFRAME         (0x00000020)
#define VDEC_BUFFERFLAG_EXTRADATA         (0x00000040)
#define VDEC_BUFFERFLAG_CODECCONFIG       (0x00000080)

/* channel capacity level */
typedef enum hiCAP_LEVEL_E
{
    CAP_LEVEL_MPEG_QCIF = 0,
    CAP_LEVEL_MPEG_CIF,
    CAP_LEVEL_MPEG_D1,
    CAP_LEVEL_MPEG_720,
    CAP_LEVEL_MPEG_FHD,
    CAP_LEVEL_H264_QCIF,
    CAP_LEVEL_H264_CIF,
    CAP_LEVEL_H264_D1,
    CAP_LEVEL_H264_720,
    CAP_LEVEL_H264_FHD,
    CAP_LEVEL_H264_BYDHD,

    CAP_LEVEL_1280x800,
    CAP_LEVEL_800x1280,
    CAP_LEVEL_1488x1280,
    CAP_LEVEL_1280x1488,
    CAP_LEVEL_2160x1280,
    CAP_LEVEL_1280x2160,
    CAP_LEVEL_2160x2160,
    CAP_LEVEL_4096x2160,
    CAP_LEVEL_2160x4096,
    CAP_LEVEL_4096x4096,
    CAP_LEVEL_8192x4096,
    CAP_LEVEL_4096x8192,
    CAP_LEVEL_8192x8192,

    CAP_LEVEL_SINGLE_IFRAME_FHD,

    CAP_LEVEL_MVC_FHD,
    CAP_LEVEL_HEVC_QCIF,
    CAP_LEVEL_HEVC_CIF,
    CAP_LEVEL_HEVC_D1,
    CAP_LEVEL_HEVC_720,
    CAP_LEVEL_HEVC_FHD,
    CAP_LEVEL_HEVC_UHD,

    CAP_LEVEL_BUTT
} VDEC_CHAN_CAP_LEVEL_E;

/* VDEC control command id, different function have different CID. */
typedef enum hiVDEC_CID_E
{
    VDEC_CID_GET_CAPABILITY,                       /* get the capacity of the decoder */
    VDEC_CID_CREATE_CHAN,                          /* create channel */
    VDEC_CID_DESTROY_CHAN,                         /* destroy channel */
    VDEC_CID_GET_CHAN_CFG,                         /* get the configuration of the decode channel */
    VDEC_CID_CFG_CHAN,                             /* config the decode channel */
    VDEC_CID_GET_CHAN_STATE,                       /* get the state of the decode channel */
    VDEC_CID_START_CHAN,                           /* start channel */
    VDEC_CID_STOP_CHAN,                            /* stop channel */
    VDEC_CID_RESET_CHAN,                           /* reset channel */
    VDEC_CID_SET_STREAM_INTF,                      /* set the stream access interface for the decode channel */
    VDEC_CID_GET_STREAM_SIZE = 10,                 /* get the stream size(in byte) held by vfmw */
    VDEC_CID_GET_CHAN_MEMSIZE,                     /* get the memory budget for the specified channel capacity level */
    VDEC_CID_RELEASE_STREAM,                       /* reset scd to release stream buffers */
    VDEC_CID_RESET_CHAN_WITH_OPTION,               /* reset channel with options to keep some characters of the channel */
    VDEC_CID_SET_FRAME_INTF,                       /* bvt set get frame interface */
    VDEC_CID_GET_USRDEC_FRAME,                     /* for VFMW_USER channel, get a frame block from vfmw */
    VDEC_CID_PUT_USRDEC_FRAME,                     /* for VFMW_USER channel, push a frame(info) into vfmw */
    VDEC_CID_SET_DISCARDPICS_PARAM,                /* get discard pictures parameters*/
    VDEC_CID_EXTRA_WAKEUP_THREAD,                  /* bvt set wake up vfmw thread */
    VDEC_CID_SET_DBG_OPTION = 20,                  /* set debug options */
    VDEC_CID_SET_PTS_TO_SEEK,                      /* set pts to be seeked by vfmw */
    VDEC_CID_SET_TRICK_MODE,                       /* set fast forward or backword speed */
    VDEC_CID_SET_CTRL_INFO,                        /* set pvr fast forward or backword stream info and control info */
    VDEC_CID_START_LOWDLAY_CALC,
    VDEC_CID_STOP_LOWDLAY_CALC,
    VDEC_CID_ALLOC_MEM_TO_CHANNEL,
    VDEC_CID_ALLOC_MEM_TO_DECODER,
    VDEC_CID_SET_FRAME_BUFFER_NUM,
    VDEC_CID_GET_OUTPUT_FORMAT,
    VDEC_CID_REPORT_DEMUX_RELEASE = 30,
    VDEC_CID_SET_FRAME_RATE_TYPE,
    VDEC_CID_GET_FRAME_RATE_TYPE,
    VDEC_CID_BIND_MEM,
    VDEC_CID_SET_FRAME_BUFFER_MODE,
    VDEC_CID_BIND_EXTERN_BUFFER,
    VDEC_CID_UNBIND_EXTERN_BUFFER,
    VDEC_CID_RESUME_PROCESS,
    VDEC_CID_PAUSE_PROCESS,

    VDEC_CID_BUTT,
} VDEC_CID_E;

/* decode mode */
typedef enum
{
    IPB_MODE = 0,
    IP_MODE,
    I_MODE,
    DISCARD_MODE,
    DISCARD_B_BF_P_MODE    /* discard B before get first P */
} DEC_MODE_E;

/* output mode */
typedef enum
{
    DISP_ORDER = 0,
    DEC_ORDER,
    DEC_ORDER_SIMPLE_DPB,
    DEC_ORDER_SKYPLAY,
    DISP_ORDER_BASE_LAYER,      // output base layer only (shvc etc), same as DISP_ORDER
    DISP_ORDER_ENHANCED_LAYER,  // output enhanced layer only (shvc etc)
    DISP_ORDER_ALL_LAYERS,      // output all layers (mv-hevc/shvc etc)
    OUTPUT_ORDER_BUTT,
} OUTPUT_ORDER_E;

/* user data source */
typedef enum
{
    USD_INVALID = 0,
    USD_MP2SEQ,
    USD_MP2GOP,
    USD_MP2PIC,
    USD_MP4VSOS,
    USD_MP4VSO,
    USD_MP4VOL,
    USD_MP4GOP,
    USD_H264_REG,
    USD_H264_UNREG,
    USD_AVSSEQ,
    USD_AVSPIC
} VDEC_USD_TYPE_E;

/* event type */
typedef enum
{
    EVNT_DISP_EREA = 0,
    EVNT_IMG_SIZE_CHANGE,
    EVNT_FRMRATE_CHANGE,
    EVNT_SCAN_CHANGE,
    EVNT_NEW_IMAGE,
    EVNT_USRDAT,
    EVNT_ASPR_CHANGE,
    EVNT_OUTPUT_IMG_SIZE_CHANGE,
    EVNT_FIND_IFRAME,
    EVNT_STREAM_ERR,
    EVNT_VDM_ERR = 20,
    EVNT_UNSUPPORT,
    EVNT_SE_ERR,
    EVNT_OVER_REFTHR,
    EVNT_OVER_OUTTHR,
    EVNT_REF_NUM_OVER,
    EVNT_SIZE_OVER,
    EVNT_SLICE_NUM_OVER,
    EVNT_SPS_NUM_OVER,
    EVNT_PPS_NUM_OVER,
    EVNT_IFRAME_ERR = 40,
    EVNT_MEET_NEWFRM,
    EVNT_DECSYNTAX_ERR,
    EVNT_RATIO_NOTZERO,
    EVNT_LAST_FRAME,
    EVNT_RESOLUTION_CHANGE,
    EVNT_STREAM_END_SYNTAX,
    EVNT_UNSUPPORT_SPEC,
    EVNT_FAKE_FRAME,
    EVNT_VIDSTD_ERROR,
    EVNT_ERR_FRAME = 60,
    EVNT_ALLOC_MEM,
    EVNT_RELEASE_MEM,
    EVNT_RELEASE_BURST_MEM,
    EVNT_CANCEL_ALLOC,

    EVNT_BUTT,
} VDEC_EVNT_TYPE_E;

typedef enum
{
    COLOR_FMT_400,       /*YUV400*/
    COLOR_FMT_420,       /*YUV420*/
    COLOR_FMT_422_2x1,   /*YUV 422 2x1*/
    COLOR_FMT_422_1x2,   /*YUV 422 1x2*/
    COLOR_FMT_444,       /*YUV 444*/
    COLOR_FMT_410,       /*YUV 410*/
    COLOR_FMT_411,       /*YUV 411*/
    COLOR_FMT_BUTT       /*other unsupported format*/
} COLOR_FMT_E;

/* unsupport specification */
typedef enum
{
    SPEC_BIT_DEPTH,    // unsupport bit depth
    SPEC_BUTT
} UNSUPPORT_SPEC_E;

/*adapter type*/
typedef enum
{
    ADAPTER_TYPE_VDEC = 0,
    ADAPTER_TYPE_OMXVDEC,
    TYPE_BUTT
} VDEC_ADAPTER_TYPE_E;

/*channel purpose*/
typedef enum
{
    PURPOSE_DECODE = 1,
    PURPOSE_FRAME_PATH_ONLY,
    PURPOSE_BUTT
} VDEC_CHAN_PURPOSE_E;

/*channel memory allocation type*/
typedef enum
{
    MODE_ALL_BY_SDK = 1,
    MODE_ALL_BY_MYSELF,
    MODE_PART_BY_SDK,
    MODE_BUTT
} VDEC_CHAN_MEM_ALLOC_MODE_E;

typedef enum
{
    PTS_FRMRATE_TYPE_PTS,         /* <Use the frame rate calculates from PTS */
    PTS_FRMRATE_TYPE_STREAM,      /* <Use the frame rate comes from stream */
    PTS_FRMRATE_TYPE_USER,        /* <Use the frame rate set by user */
    PTS_FRMRATE_TYPE_USER_PTS,    /* <Use the frame rate set by user until the 2nd I frame comes, then use the frame rate calculates from PTS */
    PTS_FRMRATE_TYPE_BUTT,

} PTS_FRMRATE_TYPE_E;

typedef enum
{
    STATUS_IDLE = 0,
    STATUS_QUEUE,
    STATUS_USING,
    STATUS_BUTT
} FRAMEBUFFER_STATE_E;

typedef enum
{
    INNER_ALLOC = 0,
    EXTERN_ALLOC,
    ALLOC_TYPE_BUTT
} FRAMEBUFFER_ALLOC_TYPE_E;

/***********************************************************************
      structures
 ***********************************************************************/
typedef struct
{
    UINT32 FpsInteger;        /* <Integral part of the frame rate (in frame/s) */
    UINT32 FpsDecimal;        /* <Fractional part (calculated to three decimal places) of the frame rate (in frame/s) */

} PTS_FRMRATE_VALUE_S;

typedef struct
{
    PTS_FRMRATE_TYPE_E     enFrmRateType;  /* <The source of frame rate */
    PTS_FRMRATE_VALUE_S    stSetFrmRate;   /* <Setting frame rate */

} PTS_FRMRATE_S;

/* VDEC capacity */
typedef struct hiVDEC_CAP_S
{
    SINT32    s32MaxChanNum;
    SINT32    s32MaxBitRate;
    SINT32    s32MaxFrameWidth;
    SINT32    s32MaxFrameHeight;
    SINT32    s32MaxPixelPerSec;
    VID_STD_E SupportedStd[32];
} VDEC_CAP_S;

typedef union
{
    struct
    {
        SINT32 IsAdvProfile;
        SINT32 CodecVersion;
    } Vc1Ext;

    struct
    {
        SINT32 bReversed;   /**<if the image need to be reversed, set to 1, otherwise set to 0 */
        UINT32 u32DispWidth;
        UINT32 u32DispHeight;
    } Vp6Ext;

    struct
    {
        VBOOL bMjpeg;
    } UserExt;

} STD_EXTENSION_U;

typedef enum hiBIT_DEPTH_ATTR_E
{
    BIT_DEPTH_NORMAL = 0,
    BIT_DEPTH_8BIT_ONLY,
    BIT_DEPTH_16BIT_EXPANDED,
    BIT_DEPTH_BUTT
} BIT_DEPTH_ATTR_E;

typedef enum hiVDEC_COMPRESS_E
{
    VDEC_COMPRESS_ADJUST = 0,
    VDEC_FORCE_COMPRESS,
    VDEC_FORCE_NO_COMPRESS,
    VDEC_COMPRESS_BUTT
} VDEC_COMPRESS_E;

typedef enum hiVDEC_SOURCE_E
{
    VDEC_SOURCE_MEDIA = 0,
    VDEC_SOURCE_DTV,
    VDEC_SOURCE_NETWORK,
    VDEC_SOURCE_BUTT
} VDEC_SOURCE_E;

/* channel config info */
typedef struct hiCHAN_CFG_S
{
    SINT8            s8BeHDRChan;        /* 0:not hdr chan, 1:hdr chan */
    SINT8            isMiracastChan;
    UINT8            bCompatible;        /* <Dolby frame is compatible or not. */
    VBOOL            bSampleFRDEnable;   /* 0:disable sample frd. 1:enable sample frd. */
    SINT32           eVidStd;            /* video compressing standard */
    STD_EXTENSION_U  StdExt;             /* extended info, for VC1 indicate AP or not, and other version info */
    SINT32           s32ChanPriority;    /* channel priority */
    SINT32           s32ChanErrThr;      /* channel error torlerance threshold. 0: zero torlerance; 100: display no matter how many error occured */
    SINT32           s32ChanStrmOFThr;   /* stream overflow control threshold, must >= 0, 0 means do not enable overflow control */
    DEC_MODE_E       s32DecMode;         /* decode mode 0: IPB, 1: IP, 2: I */
    OUTPUT_ORDER_E   s32DecOrderOutput;  /* 0: output by display order, 1: output by decode order */
    SINT32           s32CrcMode;         /* CRC MODE SELECT */
    SINT32           s32LowdlyEnable;    /* lowdly enable */
    SINT32           s32SedOnlyEnable;   /* sedonly enable */
    VDEC_COMPRESS_E  enCompress;
    BIT_DEPTH_ATTR_E enBitDepthCfg;
    SINT32           s32WmEn;            /* water marker enable */
    SINT32           s32VcmpWmStartLine; /* water marker start line number */
    SINT32           s32VcmpWmEndLine;   /* water marker end line number */
    SINT32           s32SupportAllP;     /* support stream of all p frames */
    SINT32           s32ModuleLowlyEnable;
    SINT32           s32ChanLowlyEnable;
    SINT32           s32IsOmxPath;       /* specify for omx path */
    SINT32           s32IsTunneledPath;
    SINT32           s32MaxRawPacketNum;
    SINT32           s32MaxRawPacketSize;
    SINT32           s32ExtraFrameStoreNum;
    SINT32           s32MaxWidth;
    SINT32           s32MaxHeight;
#ifdef DOLBY_VISION_HDR_SUPPORT
    DV_CODEC_CAP_E_  dv_codec_capacity;  /* only s8BeHDRChan==1 useful*/
    DV_VES_IMP_E_    ves_imp;            /* only s8BeHDRChan==1 useful*/
    DV_LAYER_IMP_E_  layer_imp;          /* only s8BeHDRChan==1 useful*/
#endif
    UINT32           s32YCompRatio;
    UINT32           s32UVCompRatio;
    VBOOL            AndroidTest;
    VBOOL            bUVMOSEnable;
    VDEC_SOURCE_E    enSource;
    UINT32           hVdecHandle;
} VDEC_CHAN_CFG_S;

typedef struct hiDISPIC_PARAM_S
{
    SINT32   s32Mode;   /*discard picture mode, 0: discard zero pictures, 1: discard pictures until s32Mode = 0, 2: discard s32DisNums pictures*/
    SINT32   s32DisNums;
} VDEC_DISPIC_PARAM_S;

/* userdata desc. */
typedef struct
{
    UINT8   data[MAX_USRDAT_SIZE]; /* USRDAT data entity */
    UINT8   pic_coding_type;
    UINT8   top_field_first;
    /* for CC, valid when IsRegistered=1 */
    SINT8   IsRegistered;
    UINT8   itu_t_t35_country_code;
    UINT8   itu_t_t35_country_code_extension_byte;
    UINT16  itu_t_t35_provider_code;
    UINT32  pic_num_count;
    UINT32  dnr_used_flag;         /* internal used only, ignore */
    VDEC_USD_TYPE_E  from;         /* USRDAT source */
    UINT32  seq_cnt;               /** to be removed later */
    UINT32  seq_img_cnt;
    SINT32  data_size;             /* USRDAT size, in byte */
    UINT64  PTS;                   /* pts of the frame containning the userdata */
} VDEC_USRDAT_S, USRDAT;

typedef struct
{
    UINT8  bottom_Range_mapy_flag;
    UINT8  bottom_Range_mapy;
    UINT8  bottom_Range_mapuv_flag;
    UINT8  bottom_Range_mapuv;
    UINT8  pic_structure;       // 0: frame, 1: top, 2: bottom, 3: mbaff, 4: field pair
    UINT8  Range_mapy_flag;
    UINT8  Range_mapy;
    UINT8  Range_mapuv_flag;
    UINT8  Range_mapuv;
    UINT8  chroma_format_idc;   // 0: yuv400 , 1: yuv420
    UINT8  vc1_profile;
    SINT8  use_pic_qp_en;
    SINT8  s32WmEn;             /* water marker enable */
    VID_STD_E video_standard;

    SINT32 QP_Y;
    SINT32 QP_U;
    SINT32 QP_V;

    SINT32 Rangedfrm;
    SINT32 s32VcmpWmStartLine;  /* water marker start line number */
    SINT32 s32VcmpWmEndLine;    /* water marker end line number */
    SINT32 s32VcmpFrameWidth;   /* DNR output frame lines, = image_width up aligned to multiple of 16 */
    SINT32 s32VcmpFrameHeight;  /* DNR output frame lines, = image_height up aligned to multiple of 16 */
} IMAGE_DNR_S;

/* BEGIN: Added 2010/8/19 */
typedef struct
{
    VBOOL  bMjpeg;
    SINT32 IsProgressiveSeq;
    SINT32 IsProgressiveFrm;
    SINT32 RealFrmRate;
    SINT32 MatrixCoef;
    UINT32 Rwzb;
} VDEC_OPTMALG_INFO_S;
/* END:   Added 2010/8/19 */

typedef enum
{
    FRAME_PACKING_TYPE_NONE,             /* normal frame, not a 3D frame */
    FRAME_PACKING_TYPE_SIDE_BY_SIDE,     /* side by side */
    FRAME_PACKING_TYPE_TOP_BOTTOM,       /* top bottom */
    FRAME_PACKING_TYPE_TIME_INTERLACED,  /* time interlaced: one frame for left eye, the next frame for right eye */
    FRAME_PACKING_TYPE_BUTT
} FRAME_PACKING_TYPE_E;

typedef enum YUV_FORMAT_E
{
    //Semi-Planner
    SPYCbCr400 = 0,
    SPYCbCr411,
    SPYCbCr420,
    SPYCbCr422_1X2,
    SPYCbCr422_2X1,
    SPYCbCr444,

    //Planner
    PLNYCbCr400,
    PLNYCbCr411,
    PLNYCbCr420,
    PLNYCbCr422_1X2,
    PLNYCbCr422_2X1,
    PLNYCbCr444,
    PLNYCbCr410,
    YCbCrBUTT
} YUV_FORMAT_E;
typedef struct hiIMAGE_BTL_S
{
    UINT32 u32Is1D;
    SINT32 btl_imageid;
    UINT32 u32IsCompress;
    UINT32 u32HeadStride;  //YC head info stride when compress is used
    UINT32 u32HeadOffset;
    UADDR  u32YHeadAddr;
    UADDR  u32CHeadAddr;

    UINT32 u32CrStride;
    UINT32 u32CStride;
    UADDR  u32CrAddr;

    UINT32 u32DNROpen;
    UADDR  u32DNRInfoAddr;
    UINT32 u32DNRInfoStride;
    UINT32 u32Reversed;
    YUV_FORMAT_E YUVFormat;
} IMAGE_BTL_S;

typedef enum
{
    DSP_REQUIRE_NONE = 0,
    DSP_REQUIRE_AVS,
    DSP_REQUIRE_LOWDLY,
} DSP_REQUIRE_E;

/* BEGIN: Added for HDR */
/* decoded Colour description info */
typedef struct
{
    UINT8 FullRangeFlag;
    UINT8 ColourPrimaries;
    UINT8 MatrixCoeffs;
    UINT32 TransferCharacteristics;
} COLOUR_DESCRIPTION_INFO_S;

typedef struct
{
    UINT16 DisplayPrimaries_x[3];
    UINT16 DisplayPrimaries_y[3];
    UINT16 WhitePoint_x;
    UINT16 WhitePoint_y;
    UINT32 MaxDisplayMasteringLuminance;
    UINT32 MinDisplayMasteringLuminance;
} MASTERING_DISPLAY_COLOUR_VOLUME_S;

typedef struct
{
    UINT32 MaxContentLightLevel;
    UINT32 MaxPicAverageLightLevel;
} CONTENT_LIGHT_LEVEL_INFO_S;

typedef struct
{
    UINT8 HDRTransferCharacteristicIdc;
} HLG_COMPATIBLE_INFO_S;

typedef struct
{
    UINT8 TmInputSignalBlackLevelOffset;
    UINT8 TmInputSignalWhiteLevelOffset;
    UINT8 ShadowGain;
    UINT8 HighlightGain;
    UINT8 MidToneWidthAdjFactor;
    UINT8 TmOutputFineTuningNumVal; //0~10
    UINT8 TmOutputFineTuningX[10];
    UINT8 TmOutputFineTuningY[10];
    UINT8 SaturationGainNumVal;   //0~6
    UINT8 SaturationGainX[6];
    UINT8 SaturationGainY[6];
} SL_HDR1_METADATA_VARIABLES;

typedef struct
{
    UINT8  LuminanceMappingNumVal; //0~33
    UINT16 LuminanceMappingX[34];
    UINT16 LuminanceMappingY[34];
    UINT8  ColourCorrectionNumVal;  //0~33
    UINT16 ColourCorrectionX[34];
    UINT16 ColourCorrectionY[34];
    UINT16 ChromaToLumaInjectionMuA;
    UINT16 ChromaToLumaInjectionMuB;
} SL_HDR1_METADATA_TABLES;

typedef struct
{
    UINT8 SpecVersion;
    UINT8 PayloadMode;
    UINT8 HdrPicColourSpace;
    UINT8 HdrMasterDisplayColourSpace;
    UINT16 HdrMasterDisplayMaxLuminance;
    UINT16 HdrMasterDisplayMinLuminance;
    UINT8 SdrPicColourSpace;
    UINT8 SdrMasterDisplayColourSpace;
    union
    {
        SL_HDR1_METADATA_VARIABLES Variables;
        SL_HDR1_METADATA_TABLES Tables;
    } Metadata;
} SL_HDR1_METADATA;
/* END: Added  for HDR */

typedef struct
{
    UINT8 MasteringAvailable;
    UINT8 ContentAvailable;
    UINT8 SlHDR1MetadataAvailable;
    UINT8 IsBackwardsCompatible;

    UINT32 HDR_Metadata_size;
    UINT32 HDR_Metadata_phy_addr;
    UINT64 HDR_Metadata_vir_addr;

    COLOUR_DESCRIPTION_INFO_S ColourInfo;
    MASTERING_DISPLAY_COLOUR_VOLUME_S MasteringDisplayColourVolume;
    CONTENT_LIGHT_LEVEL_INFO_S ContentLightLevel;
    HLG_COMPATIBLE_INFO_S ComapitibilityInfo;

    UINT8            BeDVHDRChan;
    UINT8            bDVCompatible;
#ifdef DOLBY_VISION_HDR_SUPPORT
    DV_VES_IMP_E_    VesImp;
    DV_LAYER_IMP_E_  LayerImp;
    DV_CODEC_CAP_E_  DVCapacity;
#endif
} HDR_INPUT_S;

/***************************************************************************************************************************/
/* IMAGE_FORMAT bits introduce:                                                                                              */
/* [1:0] frame_type: 00(I), 01(P), 10(B), 11(Reserved)                                                                     */
/* [4:2] sample_type: 000(YUV:4:2:0), 001(YUV:4:0:0), 010~111(Reserved)                                                    */
/* [7:5] norm_type: 000(component), 001(PLA), 010(NTSC), 011(SECAM), 100(MAC),                                             */
/*                  101(Unspecified Video Format), 110~111(Reserved)                                                       */
/* [9:8] source_format: 00(progressive), 01(interlaced), 10(infered_progressive), 11(infered_interlaced)                   */
/* [11:10] field_valid_flag: 00(top_field invalid, bottom_field invalid), 01(top_field valid, bottom_field invalid),       */
/*                           10(top_field invalid, bottom_field valid), 11(top_field valid, bottom_field valid)            */
/* [13:12]top_field_first: 00(bottom field first), 01(top field first), 10(un-know), 11(Reserved)                          */
/* [16:14] aspect_ratio: 000(unspecified), 001(4:3), 010(16:9), 011(2.21:1),100(2.35:1),                                   */
/*                       101(origin width and height), 111(Reserved)                                                       */
/* [17]    linear_en: 0: 1d ; 1: 2d                                                                                        */
/* [18]    pts_unit : 0: ms ; 1: us                                                                                        */
/* [31:19] Reserved                                                                                                        */
/***************************************************************************************************************************/
typedef struct
{
    UINT32 frame_type          :               2;    /*[1:0]*/
    UINT32 sample_type         :               3;    /*[4:2]*/
    UINT32 video_format        :               3;    /*[7:5]*/
    UINT32 source_format       :               2;    /*[9:8]*/
    UINT32 field_valid_flag    :               2;    /*[11:10]*/
    UINT32 top_field_first     :               2;    /*[13:12]*/
    UINT32 aspect_ratio        :               3;    /*[16:14]*/
    UINT32 linear_en           :               1;    /*[17]*/
    UINT32 pts_unit            :               1;    /*[18]*/
    UINT32 no_gap              :               1;    /*[19]*/
    UINT32 reserved            :               12;
} IMAGE_FORMAT;

typedef struct
{
    UINT32 ActualCRC_8bit[2];
    UINT32 ActualCRC_2bit[2];
    UINT32 ActualCRC_8bit_1[2];
} IMAGE_CRC_S;

typedef struct
{
    UINT8  linear_en;
    UINT8  compress_en;
    UINT32 y_stride;
    UINT32 uv_stride;
    UINT32 head_stride;
    UINT32 head_info_size;
    UINT32 stride_2bit;
    UINT32 bit_depth_luma;
    UINT32 bit_depth_chroma;
    UADDR  luma_phy_addr;
    UADDR  chrom_phy_addr;
    UADDR  luma_phy_addr_2bit;
    UADDR  chrom_phy_addr_2bit;
} IMAGE_DEC_S;

typedef struct
{
    UINT8  compress_en;
    UINT32 y_stride;
    UINT32 uv_stride;
    UINT32 head_stride;
    UINT32 head_info_size;
    UINT32 stride_2bit;
    UADDR  luma_phy_addr;
    UADDR  chrom_phy_addr;
    UADDR  luma_phy_addr_1;
    UADDR  chrom_phy_addr_1;
    UADDR  luma_phy_addr_2bit;
    UADDR  chrom_phy_addr_2bit;
} IMAGE_DISP_S;

typedef struct
{
    UADDR  AttachedPhyAddr;
    UINT64 AttachedVirAddr;
    UINT32 AttachedSize;
} IMAGE_ATTACHED_S;

typedef struct
{
    UINT32 AvgQp;
    UINT32 FrameStreamSize;
    UINT32 MaxMV;
    UINT32 MinMV;
    UINT32 AvgMV;
    UINT32 SkipRatio;
    VID_STD_E VidStd;
} UvMOSParam;

typedef struct
{
    UINT32 DispEnableFlag;
    UINT32 DispFrameDistance;
    UINT32 DistanceBeforeFirstFrame;
    UINT32 GopNum;
    UINT32 u32RepeatCnt;
    UINT32 is_fld_save;
    UINT32 top_fld_type;
    UINT32 bottom_fld_type;
    UINT32 image_width;
    UINT32 image_height;
    UINT32 disp_width;
    UINT32 disp_height;
    UINT32 disp_center_x;
    UINT32 disp_center_y;
    UINT32 u32AspectWidth;
    UINT32 u32AspectHeight;
    UINT32 frame_rate;
    UINT32 CompressEn;
    UINT32 LossCompressEn;
    UINT32 bit_depth;
    UINT32 y_comp_ratio;
    UINT32 uv_comp_ratio;
    UINT32 image_id;
    SINT32 image_id_1;
    UINT32 error_level;
    UINT32 seq_cnt;
    UINT32 seq_img_cnt;
    SINT32 last_frame;
    SINT32 view_id;
    UINT32 is_3D;
    UINT32 left_offset;
    UINT32 right_offset;
    UINT32 top_offset;
    UINT32 bottom_offset;
    UINT32 is_SecureFrame;
    SINT32 InterPtsDelta;
    UADDR  line_num_phy_addr;

    VID_STD_E eVidStd;
    FRAME_PACKING_TYPE_E eFramePackingType;
    IMAGE_FORMAT format;

    UINT64 pOutFrame;
    UINT64 p_usrdat[4];
    UINT64 SrcPts;
    UINT64 PTS;
    UINT64 Usertag;
    UINT64 DispTime;

    UvMOSParam uvmosParam;

    IMAGE_DNR_S  ImageDnr;
    IMAGE_BTL_S  BTLInfo;
    HDR_INPUT_S  stHDRInput;
    IMAGE_CRC_S  stCRCInfo;
    IMAGE_DEC_S  stDecInfo;
    IMAGE_DISP_S stDispInfo;
    IMAGE_ATTACHED_S stAttachedInfo;
    VDEC_OPTMALG_INFO_S optm_inf;
    UINT8       DVDualLayer;
} IMAGE;

#define UINT64_PTR(ptr) ((VOID *)(ULONG)(ptr))
#define PTR_UINT64(ptr) ((UINT64 )(ULONG)(ptr))

/* frame desc for VFMW_USER */
typedef struct
{
    COLOR_FMT_E         enFmt;           /* color format */

    SINT32              s32IsFrameValid; /* 1: frame valid, to be output to vo;  0: frame invalid, just free the frame-store */
    SINT32              s32IsSemiPlanar;
    SINT32              s32YWidth;
    SINT32              s32YHeight;
    SINT32              s32FrameSize;
    UADDR               s32LineNumPhyAddr;
    UADDR               s32LumaPhyAddr;
    SINT32              s32LumaStride;
    UADDR               s32CbPhyAddr;    /* if semi-planar stand for the interlaced chrom addr; if planar stand for the Cb addr */
    UADDR               s32CrPhyAddr;
    SINT32              s32ChromStride;
    SINT32              s32ChromCrStride;
    UINT64              Pts;
} USRDEC_FRAME_DESC_S;

/* global config */
typedef struct
{
    SINT32      reserved;
} VDEC_GLOBAL_CFG_S;

/* global state */
typedef struct
{
    UINT32  VFMW_version_number;
    SINT32  total_chan_num;
    SINT32  active_chan_num;
    SINT32  print_device;
    SINT32  print_enable;
    SINT8   *vfmw_version_desc;
} VDEC_GLOBAL_STATE_S;

/* channel state */
typedef struct
{

    UINT32  image_width;
    UINT32  image_height;
    UINT32  aspect_ratio;
    UINT32  scan_type;
    UINT32  video_format;
    UINT32  frame_rate;
    UINT32  bit_rate;
    UINT32  sub_video_standard;
    UINT32  profile;
    UINT32  level;
    SINT32  total_frame_num;
    SINT32  error_frame_num;
    SINT32  decoded_1d_frame_num;   /* decoded, but not ready to display. generally refer to the decoded 1D frames */
    SINT32  buffered_stream_size;   /* the un-decoded stream seg produced by SCD */
    SINT32  buffered_stream_num;   /* the un-decoded stream seg num produced by SCD */

    UADDR   chan_mem_address;
    SINT32  chan_mem_size;
    SINT32  total_fstore_num;
    SINT32  total_pmv_num;
    SINT32  voque_detail;

    UINT32  stream_not_enough;
    UINT32  wait_disp_frame_num;
    UINT32  mpeg4_shorthead;      /* mpeg4 short head info, 1: sh 2:not sh  0:not mpeg4 stream */
    UINT32  total_disp_frame_num; /* total display num ( plus extra_disp ) */
    UINT32  is_field_flg; /* 0:frame 1:field */
} VDEC_CHAN_STATE_S;

typedef struct hiVDEC_CHAN_FRMSTATUSINFO_S
{
    UINT32  u32DecodedFrmNum;  /* decoded, but not ready to display.*/
    UINT32  u32StrmSize;       /* the un-decoded stream seg produced by SCD */
    UINT32  u32StrmInBps;      /*average Bps */
    UINT32  u32OutBufFrmNum;   /*decoded, and ready to display*/
} VDEC_CHAN_FRMSTATUSINFO_S;

/* image accessing interface */
typedef struct hiIMAGE_INTF_S
{
    SINT32  image_provider_inst_id;
    SINT32(*read_image)(SINT32 InstID, VOID *pFrame);
    SINT32(*release_image)(SINT32 InstID, VOID *pFrame);
    SINT32(*global_release_image)(VOID *pFrame);
} IMAGE_INTF_S;

typedef struct hiOUTPUT_FORMAT_S
{
    VID_STD_E VideoStandard;
    UINT32 Width;
    UINT32 Height;
    UINT32 IsTile;
} OUTPUT_FORMAT_S;

typedef struct hiRAW_EXTENSION_S
{
    UINT8   IsSeekPending;
    UINT32  Flags;
    UINT32  BufLen;
    UINT32  CfgWidth;
    UINT32  CfgHeight;
} RAW_EXTENSION_S;

/* stream packet struct */
typedef struct hiSTREAM_PACKET_S
{
    UINT8       is_not_last_packet_flag;
    UINT8       is_stream_end_flag;
    UINT8       is_extern_eop_flag;
    UADDR       PhyAddr;
    SINT32      Length;
    UINT32      Index;
    UINT32      discontinue_count;
    UINT32      DispFrameDistance;
    UINT32      DistanceBeforeFirstFrame;
    UINT32      GopNum;
    UINT32      DispEnableFlag;
    UINT64      VirAddr;
    UINT64      UserTag;
    UINT64      DispTime;
    UINT64      Pts;
    RAW_EXTENSION_S RawExt;               // omx raw buffer extension
    UINT8       DVDualLayer; //0: SL 1:DL
} STREAM_DATA_S;

typedef struct hiVFMW_CONTROLINFO_S
{
    UINT32  u32IDRFlag;               /*IDR frame Flag, 1 means IDR frame.*/
    UINT32  u32BFrmRefFlag;           /*whether B frame is refer frame, 1 means B frame is refer frame.*/
    UINT32  u32ContinuousFlag;        /*whether send frame is continusous. 1 means continusous*/
    UINT32  u32BackwardOptimizeFlag;  /*Backward optimize flag, 1 means optimize the backward fast play performance*/
    UINT32  u32DispOptimizeFlag;      /*Display optimize flag, 1 means optimize the VO display performance*/
    UINT32  u32LastGopNum;
} VFMW_CONTROLINFO_S;

/* stream accessing interface */
typedef struct hiSTREAM_INTF_S
{
    SINT32  stream_provider_inst_id;
    SINT32(*read_stream)(SINT32 InstID, STREAM_DATA_S *pPacket);
    SINT32(*release_stream)(SINT32 InstID, STREAM_DATA_S *pPacket);
} STREAM_INTF_S;

/* memory budget for a decode channel */
typedef struct hiCHAN_MEM_BUDGET
{
    SINT32  MinMemSize;
    SINT32  NormalMemSize;
    SINT32  FluentMemSize;
} CHAN_MEM_BUDGET_S;

typedef enum
{
    MEM_CMA_CMA = 0,
    MEM_CMA_MMU,
    MEM_MMU_CMA,
    MEM_MMU_MMU,
} MEM_MODE_E;

typedef enum
{
    BUF_STATUS_INVALID = 0,
    BUF_STATUS_AVAILABLE,
    BUF_STATUS_UNAVAILABLE,
} EXTERN_BUF_STATUS_E;

/* memroy description */
typedef struct hiMEM_DESC_S
{
    UADDR  PhyAddr;
    UADDR  MmuAddr;
    UINT64 VirAddr;
    SINT32  Length;
    MEM_MODE_E eMode;
} MEM_DESC_S;

/* detailed channel memory desc. */
typedef struct
{
    MEM_DESC_S  ChanMemVdh;
    MEM_DESC_S  ChanMemScd;
    MEM_DESC_S  ChanMemCtx;
    MEM_DESC_S  ChanMemRpu; //for Dolby Vision HDR metadata
} VDEC_CHAN_MEM_DETAIL_S;

/* user defined channel option*/
typedef struct
{
    VDEC_ADAPTER_TYPE_E eAdapterType;          /* channel type vdec/omxvdec */
    VDEC_CHAN_PURPOSE_E Purpose;               /* channel purpose, indicate if this channel is used for decoding or frame path only*/
    VDEC_CHAN_MEM_ALLOC_MODE_E MemAllocMode;   /* who alloc memory for the channel */
    SINT32 s32MaxSliceNum;                     /* for H264,H265 max slice number */
    SINT32 s32MaxVpsNum;                       /* for H264,H265 max vps number */
    SINT32 s32MaxSpsNum;                       /* for H264,H265 max sps number */
    SINT32 s32MaxPpsNum;                       /* for H264,H265 max pps number */
    SINT32 s32MaxRefFrameNum;                  /* max reference frame num*/
    SINT32 s32SupportBFrame;                   /* if support B frame. 1: yes, 0: no */
    SINT32 s32SupportH264;                     /* if this channel support H.264 decoding. */
    SINT32 s32ReRangeEn;                       /* when resolution change, if the framestore be re-partitioned according to the new resolution. */
    /* 1:yes. can decode smaller(but more ref) stream, but one or more frame may be discarded */
    /* 0:no.  no frame discarded, but the stream with more ref can not dec, even if the total memory is enough */
    SINT32 s32SCDBufSize;                      /* SCD buf size */
    SINT32 s32DisplayFrameNum;                 /* user defined display frame num */
    SINT32 s32SlotWidth;                       /*if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store width*/
    SINT32 s32SlotHeight;                      /*if Purpose==PURPOSE_FRAME_PATH_ONLY, frame store height*/
    VDEC_CHAN_MEM_DETAIL_S MemDetail;
    UINT32 u32DFSEn;
    UINT32 u32MaxMemUse;
    SINT32 s32IsSecMode;                       /*add sec mode*/
    SINT32 s32ScdMmuEn;
    SINT32 s32VdhMmuEn;
    SINT32 s32ScdInputMmuEn;
} VDEC_CHAN_OPTION_S;

/* user defined channel reset option*/
typedef struct
{
    SINT32 s32KeepBS;                          /* keep bs in the scd buffer */
    SINT32 s32KeepSPSPPS;                      /* keep global info in ctx for seek reset, default 0 */
    SINT32 s32KeepFSP;                      /* keep fsp info for seek reset, default 0 */
} VDEC_CHAN_RESET_OPTION_S;

typedef struct
{
    SINT32  VdhDetailMem;
    SINT32  ScdDetailMem;
    SINT32  ChanCtxDetailMem;
} DETAIL_MEM_SIZE;

typedef struct
{
    UINT8  hal_disable;
    UINT32 sec_print_word;
    UADDR  share_mem_addr;
    UADDR  common_context;
} VDH_SHARE_DATA_S;

/* external specified operations(method) */
typedef struct
{
    UINT8 is_secure;
    VDEC_ADAPTER_TYPE_E eAdapterType;
    MEM_DESC_S stExtHalMem;
    VDH_SHARE_DATA_S ShareData;
    SINT32(*VdecCallback)(SINT32 ChanID, SINT32 type, VOID *p_args);
    MEM_DESC_S(*mem_malloc)(UINT8 *MemName, UINT32 len, UINT32 align);
    VOID (*mem_free)(MEM_DESC_S mem);
} VDEC_OPERATION_S;

/* decode parameter, usally for the external accelerator(VEDU eg.) */
typedef struct hiDECPARAM_INF_S
{
    SINT32      ChanID;            /*chan ID*/
    VID_STD_E   VidStd;            /*video standard*/
    VOID       *pDecParam;         /*pointer to the dec param */
} DECPARAM_INF_S;

typedef struct
{
    UINT8      *VirAddr;
    UADDR       PhyAddr;
    SINT32      Length;
    UINT8      *PrivateVirAddr;
    UADDR       PrivatePhyAddr;
    SINT32      PrivateLength;
} EXTERNAL_FRAME_STORE_S;

#define REPORT_MAX_NAME_LEN            (16)

typedef struct
{
    SINT8  BufName[REPORT_MAX_NAME_LEN];
    UADDR  PhyAddr;
    UINT64 VirAddr;
    VBOOL  IsMap;
    VBOOL  IsCache;
    UINT32 Size;
    SINT64 UniqueID;
} MEM_REPORT_S;

typedef struct
{
    MEM_REPORT_S ExternFrameBuffer;
    MEM_REPORT_S ExternAttachedBuffer;
    EXTERN_BUF_STATUS_E Status;
} EXTERN_BUFFER_S;

typedef struct
{
    UINT32 phyaddr;
    UINT32 length;
    UINT32 profile;
    UINT32 level;
    UINT32 dual_layer;
    UINT32 found_dolby_info_start_code;
    UINT32 rpu_assoc_flag;
    UINT32 valid;
} OMX_TUNNEL_CSD;

/***********************************************************************
      functions
 ***********************************************************************/
VOID   VDEC_OpenModule(VOID);
VOID   VDEC_ExitModule(VOID);
SINT32 VDEC_Init(VDEC_OPERATION_S *pArgs);
SINT32 VDEC_Control(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs);
SINT32 VDEC_Exit(VOID);
SINT32 VDEC_Suspend(VOID);
SINT32 VDEC_Resume(VOID);
SINT32 VDEC_GetImage(SINT32 ChanID, IMAGE *pImage);
SINT32 VDEC_ReleaseImage(SINT32 ChanID, IMAGE *pImage);

#ifdef __cplusplus
}
#endif

#endif  // __VDEC_FIRMWARE_H__
