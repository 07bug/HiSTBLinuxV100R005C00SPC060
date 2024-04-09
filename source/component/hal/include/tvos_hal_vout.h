/**
 * \file
 * \brief Describes the information about the video output module.
 */

#ifndef __TVOS_HAL_VOUT_H__
#define __TVOS_HAL_VOUT_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"

#ifdef ANDROID_HAL_MODULE_USED
#include <hardware/hardware.h>
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup      HAL_VOUT */
/** @{ */  /** <!-- [HAL_VOUT] */
/*****************************************************************************/

/* for compatibility */
#define VOUT_MODULE_API_VERSION      VOUT_MODULE_API_VERSION_0_1
#define VOUT_DEVICE_API_VERSION      VOUT_DEVICE_API_VERSION_0_1
#define VOUT_API_VERSION             VOUT_DEVICE_API_VERSION

/*****************************************************************************/
/**Defines the video output module name*/
/**CNcomment:定义视频输出 模块名称 */
#define VOUT_HARDWARE_MODULE_ID      "video_output"

/**Defines the video output device name*/
/**CNcomment:定义视频输出 设备名称 */
#define VOUT_HARDWARE_VOUT0          "vout0"

/**Auto set the valid values when the values of alpha, brightness, contrast, saturation, and DOF are unvalid*/
/**CNcomment:如果透明度,亮度,对比度,饱和度,景深等入口参数超出合法范围, 将自动修复为合法范围 */

/**Valid range of alpha: [0,100]*/
/**CNcomment:透明度值[0,100]*/
#define VOUT_ALPHA_MAX               (100)
#define VOUT_ALPHA_MIN               (0)

/**Valid range of brightness: [0,100]*/
/**CNcomment:亮度范围[0,100]*/
#define VOUT_BRIGHTNESS_MAX          (100)
#define VOUT_BRIGHTNESS_MIN          (0)

/**Valid range of contrast: [0,100]*/
/**CNcomment:对比度范围[0,100]*/
#define VOUT_CONTRAST_MAX            (100)
#define VOUT_CONTRAST_MIN            (0)

/**Valid range of saturation: [0,100]*/
/**CNcomment:饱和度范围[0,100]*/
#define VOUT_SATURATION_MAX          (100)
#define VOUT_SATURATION_MIN          (0)

/**Valid range of hue: [0,100]*/
/**CNcomment:色调范围[0,100]*/
#define VOUT_HUE_MAX                 (100)
#define VOUT_HUE_MIN                 (0)

/**Valid range of depth of field: [0,100]*/
/**CNcomment:景深范围[0,100]*/
#define VOUT_DOF_MAX                 (100)
#define VOUT_DOF_MIN                 (0)

/**Defines  display channel number, the number must corespond with the item number of VOUT_DISPLAY_CHANNEL_E*/
/**CNcomment:定义显示通道最大个数，必须与VOUT_DISPLAY_CHANNEL_E结构的条目最大个数一致*/
#define VOUT_DISPLAY_MAX (6)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_VOUT */
/** @{ */  /** <!-- [HAL_VOUT] */

/**Defines the types of display channel*/
/**CNcomment:定义显示通道*/
typedef enum _VOUT_DISPLAY_CHANNEL_E
{
    VOUT_DISPLAY_HD0 = 0x1 << 0,
    VOUT_DISPLAY_HD1 = 0x1 << 1,
    VOUT_DISPLAY_HD2 = 0x1 << 2,
    VOUT_DISPLAY_SD0 = 0x1 << 3,
    VOUT_DISPLAY_SD1 = 0x1 << 4,
    VOUT_DISPLAY_SD2 = 0x1 << 5,
} VOUT_DISPLAY_CHANNEL_E;

/**Defines the event of video output*/
/**CNcomment:定义视频输出相关事件*/
typedef enum _VOUT_EVT_E
{
    VOUT_EVT_BASE        = 0,
    VOUT_HDMI_EVT_BASE   = VOUT_EVT_BASE,
    VOUT_HDMI_EVT_PLUGIN = VOUT_HDMI_EVT_BASE,      /**<HDMI plugin*//**<CNcomment:HDMI 插入*/
    VOUT_HDMI_EVT_UNPLUG,                           /*<HDMI unplugin*//**<CNcomment:HDMI 拔出*/
    VOUT_HDMI_EVT_EDID_FAIL,                        /**<Get EDID fail*//**<CNcomment:获取EDID 失败*/
    VOUT_HDMI_EVT_HDCP_FAIL,                        /**<Set HDCP fail*//**<CNcomment:设置HDCP失败*/
    VOUT_HDMI_EVT_HDCP_SUCCESS,                     /**<Set HDCP success*//**<CNcomment:设置HDCP成功*/
    VOUT_EVT_BUTT,
} VOUT_EVT_E;

/**Defines the types of frame rate:
 1.HDI should auto set the optimal format and frame rate and does not return any error when the format or frame rate is not supported by the HD channel.
 2.HDI should auto set a valid frame rate and does not return any error when the frame rate is unvalid for SD formate.*/
/**CNcomment:定义帧率类型
 1. 高清通道设置不支持的制式或者帧率, HDI负责选择最优的制式和帧率,不做错误返回.
 2. 对于标清制式,如果应用传入错误的帧率,HDI 自动纠正,不做错误返回.*/
typedef enum _VOUT_VID_FRAME_RATE_E
{
    VOUT_VID_FRAME_RATE_UNKNOWN = 0,
    VOUT_VID_FRAME_RATE_AUTO    = 1,
    VOUT_VID_FRAME_RATE_23_976  = 1 << 1,
    VOUT_VID_FRAME_RATE_24      = 1 << 2,
    VOUT_VID_FRAME_RATE_25      = 1 << 3,
    VOUT_VID_FRAME_RATE_29_97   = 1 << 4,
    VOUT_VID_FRAME_RATE_30      = 1 << 5,
    VOUT_VID_FRAME_RATE_50      = 1 << 6,
    VOUT_VID_FRAME_RATE_59_94   = 1 << 7,
    VOUT_VID_FRAME_RATE_60      = 1 << 8
} VOUT_VID_FRAME_RATE_E;

/**Defines the types of format and resolution of HD
 VOUT_FORMAT_E & VOUT_VID_FRAME_RATE_E can be combined into following types:
 VOUT_FORMAT_PAL,
 VOUT_FORMAT_NTSC,
 VOUT_FORMAT_PALN,
 VOUT_FORMAT_PALM,
 VOUT_FORMAT_SECAM,
 VOUT_FORMAT_576P,
 VOUT_FORMAT_HD_720P_24HZ,
 VOUT_FORMAT_HD_720P_30HZ,
 VOUT_FORMAT_HD_720P_50HZ,
 VOUT_FORMAT_HD_720P_60HZ,
 VOUT_FORMAT_HD_1080I_50HZ,
 VOUT_FORMAT_HD_1080I_60HZ,
 VOUT_FORMAT_HD_1080P_24HZ,
 VOUT_FORMAT_HD_1080P_25HZ,
 VOUT_FORMAT_HD_1080P_30HZ,
 VOUT_FORMAT_HD_1080P_50HZ,
 VOUT_FORMAT_HD_1080P_60HZ,
 VOUT_FORMAT_HD_3840X2160_23_976HZ,
 VOUT_FORMAT_HD_3840X2160_24HZ,
 VOUT_FORMAT_HD_3840X2160_25HZ,
 VOUT_FORMAT_HD_3840X2160_29_97HZ,
 VOUT_FORMAT_HD_3840X2160_30HZ,
 VOUT_FORMAT_HD_4096X2160_24HZ,
 1.If set HD format to SD display channel, return FAIL.
 2.To avoid poor image quality, App should not allow to set SD format to HD display channel.
 3.If unspported format or iframe rate was set on the HD display channel, HDI should auto set the best format or iframe rate, do not return fail.
 4.If unspportediframe rate was set on the SD display channel, HDI should auto set the best iframe rate, do not return fail.
 5.VOUT_FORMAT_UNKNOWN means can not get resolution from stream information, APP can not set the type*/
/**CNcomment:电视制式 和高清分辨率
 VOUT_FORMAT_E & VOUT_VID_FRAME_RATE_E 组合成以下类型.
 VOUT_FORMAT_PAL,
 VOUT_FORMAT_NTSC,
 VOUT_FORMAT_PALN,
 VOUT_FORMAT_PALM,
 VOUT_FORMAT_SECAM,
 VOUT_FORMAT_576P,
 VOUT_FORMAT_HD_720P_24HZ,
 VOUT_FORMAT_HD_720P_30HZ,
 VOUT_FORMAT_HD_720P_50HZ,
 VOUT_FORMAT_HD_720P_60HZ,
 VOUT_FORMAT_HD_1080I_50HZ,
 VOUT_FORMAT_HD_1080I_60HZ,
 VOUT_FORMAT_HD_1080P_24HZ,
 VOUT_FORMAT_HD_1080P_25HZ,
 VOUT_FORMAT_HD_1080P_30HZ,
 VOUT_FORMAT_HD_1080P_50HZ,
 VOUT_FORMAT_HD_1080P_60HZ,
 VOUT_FORMAT_HD_3840X2160_23_976HZ,
 VOUT_FORMAT_HD_3840X2160_24HZ,
 VOUT_FORMAT_HD_3840X2160_25HZ,
 VOUT_FORMAT_HD_3840X2160_29_97HZ,
 VOUT_FORMAT_HD_3840X2160_30HZ,
 VOUT_FORMAT_HD_4096X2160_24HZ,

 1. 如果是标清通道设置高清制式,返回失败.
 2. 高清通道可以设置标清制式, 如果平台原因,
     高清通道设置成标清制式,效果不好,图像模糊,
     需要应用在项目设置时候过滤,hdi要提供完整的设置的功能,不做过滤.
 3. 高清通道设置不支持的制式或者帧率,
     HDI负责选择最优的制式和帧率,不做错误返回.
 4. 对于标清制式,如果应用传入错误的帧率,HDI 自动纠正,不做错误返回.
 5. VOUT_FORMAT_UNKNOWN未知分辨率,
     用于获取流状态得到未知分辨率的情况,应用不能设置此分辨率给HDI.*/
typedef enum _VOUT_FORMAT_E
{
    VOUT_FORMAT_AUTO = 0,
    VOUT_FORMAT_PAL,
    VOUT_FORMAT_NTSC,
    VOUT_FORMAT_PALN,
    VOUT_FORMAT_PALM,
    VOUT_FORMAT_SECAM,
    VOUT_FORMAT_480P,
    VOUT_FORMAT_576P,
    VOUT_FORMAT_HD_720P,
    VOUT_FORMAT_HD_1080I,
    VOUT_FORMAT_HD_1080P,
    VOUT_FORMAT_HD_3840X2160,
    VOUT_FORMAT_HD_4096X2160,
    VOUT_FORMAT_480I,
    VOUT_FORMAT_576I,
    VOUT_FORMAT_UNKNOWN,
    VOUT_FORMAT_BUTT
} VOUT_FORMAT_E;

/**Defines the types of aspect ratio of video
VOUT_FORMAT_UNKNOWN means can not get resolution from stream information, APP can not set the type*/
/**CNcomment:视频宽高比
VOUT_ASPECT_RATIO_UNKNOWN未知宽高比. 用于获取流状态得到未知宽高比的情况,应用不能设置此值给HDI.*/
typedef enum _VOUT_ASPECT_RATIO_E
{
    VOUT_ASPECT_RATIO_AUTO = 0,     /**< auto*//**<CNcomment:自动选择*/
    VOUT_ASPECT_RATIO_16TO9,        /**< 16:9*//**<CNcomment:16:9*/
    VOUT_ASPECT_RATIO_4TO3,         /**< 4:3*//**<CNcomment:4:3*/
    VOUT_ASPECT_RATIO_UNKNOWN,
    VOUT_NB_OF_ASPECT_RATIO
} VOUT_ASPECT_RATIO_E;

/**Defines conversion mode of AspectRatio*/
/**CNcomment:视频宽高比自适应模式*/
typedef enum _VOUT_ASPECT_RATIO_CONVERSION_E
{
    VOUT_AR_CONVERSION_PAN_SCAN = 0,      /**< PAN_SCAN*//**<CNcomment: 裁减*/
    VOUT_AR_CONVERSION_LETTER_BOX,        /**< LETTER_BOX*//**<CNcomment: 加黑边*/
    VOUT_AR_CONVERSION_COMBINED,          /**< COMBINED*//**<CNcomment: 加黑边和裁减混合*/
    VOUT_AR_CONVERSION_IGNORE,            /**< IGNORE*//**<CNcomment: 忽略*/
    VOUT_AR_CONVERSION_CUSTOM,            /**< CUSTOM*//**<CNcomment: 用户自定义*/
    VOUT_NB_OF_AR_CONVERSION
} VOUT_ASPECT_RATIO_CONVERSION_E;

/**Video output types, can be combined*/
/**CNcomment:视频输出类型: 输出类型要支持组合方式*/
typedef enum _VOUT_OUTPUT_TYPE_E
{
    VOUT_OUTPUT_TYPE_NONE            = 0x00,
    VOUT_OUTPUT_TYPE_COMPOSITE       = 0x01,                   /**< SD analog cvbs*//**<CNcomment:标清模拟复合 输出*/
    VOUT_OUTPUT_TYPE_YPBPR           = 0x02,                   /**< SD analog YUV.*//**<CNcomment:标清模拟分量 输出*/
    VOUT_OUTPUT_TYPE_SVIDEO          = 0x04,                   /**< SD YC*//**<CNcomment:标清SVIDEO 输出*/
    VOUT_OUTPUT_TYPE_DVI             = 0x08,                   /**< HDMI--auto color space*//**< HDMI*/
    VOUT_OUTPUT_TYPE_HDMI            = VOUT_OUTPUT_TYPE_DVI,   /**< HDMI--auto color space*//**< HDMI*/
    VOUT_OUTPUT_TYPE_SCART           = 0x10,                   /**< scart*//**< CNcomment:scart*/
    VOUT_OUTPUT_TYPE_VGA             = 0x20,                   /**< vga*//**< CNcomment:vga*/
    VOUT_OUTPUT_TYPE_RF              = 0x40,                   /**< rf*//**< CNcomment:rf*/
    VOUT_OUTPUT_TYPE_YCBCR           = 0x80,                   /**< DIGITAL YCbCr COMPONENTS *//**< CNcomment:分量*/
    VOUT_OUTPUT_TYPE_HD_YUV          = 0x100,                  /**< HD analog YUV*//**< CNcomment:YUV*/
    VOUT_OUTPUT_TYPE_HDMI_RGB888     = 0x200,                  /**< hdmi--digital RGB888*//**< CNcomment:HDMI RGB888*/
    VOUT_OUTPUT_TYPE_HDMI_YCBCR444   = 0x400,                  /**< hdmi--digital YCBCR444*//**< CNcomment:HDMI YCBCR444*/
    VOUT_OUTPUT_TYPE_HDMI_YCBCR422   = 0x800,                  /**< hdmi--digital YCBCR422*//**< CNcomment:HDMI YCBCR422*/
    VOUT_OUTPUT_TYPE_RGB             = 0x1000,                 /**< SD analog RGB*/ /**< CNcomment:SD RGB*/
    VOUT_OUTPUT_TYPE_HD_RGB          = 0x2000,                 /**< HD analog RGB*/ /**< CNcomment:HD RGB*/
    VOUT_OUTPUT_TYPE_PANNEL          = 0x4000,                 /**< PANNEL*//**< CNcomment:面板*/
    VOUT_OUTPUT_TYPE_ALL             = (S32)0xffffffff         /**< All type*//**< 所有输出类型*/
} VOUT_OUTPUT_TYPE_E;

/**Type define of alpha, see VOUT_ALPHA_MAX & VOUT_ALPHA_MIN*/
/**CNcomment:透明度，参见VOUT_ALPHA_MAX & VOUT_ALPHA_MIN 定义*/
typedef U8 VOUT_ALPHA_T;

/**Defines of CGMS:Copy Generation Management System*/
/**CNcomment:CGMS*/
typedef enum _VOUT_VBI_CGMS_TYPE_E
{
    VOUT_VBI_CGMS_A = 0,
    VOUT_VBI_CGMS_B = 1,
    VOUT_VBI_CGMS_BUTT
} VOUT_VBI_CGMS_TYPE_E;

/**Defines of CGMS-A permission type*/
/**CNcomment:CGMS-A 许可类型*/
typedef enum _VOUT_VBI_CGMS_A_COPY_E
{
    VOUT_VBI_CGMS_A_COPY_PERMITTED = 0,                     /**< copying is permitted without restriction*//**< CNcomment:无限制拷贝*/
    VOUT_VBI_CGMS_A_COPY_ONE_TIME_BEEN_MADE = 1,            /**< no more copies, one generation copy has been made*//**< CNcomment:已经拷贝一次*/
    VOUT_VBI_CGMS_A_COPY_ONE_TIME  = 2,                     /**< one generation of copied may be made*//**< CNcomment:只能拷贝一次*/
    VOUT_VBI_CGMS_A_COPY_FORBIDDEN = 3,                     /**< no copying is permitted*//**< CNcomment:禁止拷贝*/
    VOUT_VBI_CGMS_A_BUTT
} VOUT_VBI_CGMS_A_COPY_E;

/**Defines of display 3D mode stucture*/
/**CNcomment:定义3D 显示模式*/
typedef enum _VOUT_3D_FORMAT_E
{
    VOUT_3D_FORMAT_2D = 0,
    VOUT_3D_FORMAT_FP,                       /**<3d type:Frame Packing*//**<CNcomment:3d 模式:帧封装*/
    VOUT_3D_FORMAT_SBS,                      /**<3d type:Side by side half*//**<CNcomment:3d 模式:并排式 左右半边*/
    VOUT_3D_FORMAT_TAB,                      /**<3d type:Top and Bottom*//**<CNcomment:3d 模式:上下模式*/
    VOUT_3D_FORMAT_FA,                       /**<3d type:Field alternative*//**<CNcomment:3d 模式:场交错*/
    VOUT_3D_FORMAT_LA,                       /**<3d type:Line alternative*//**<CNcomment:3d 模式:行交错*/
    VOUT_3D_FORMAT_SBS_FULL,                 /**<3d type:Side by side full*//**<CNcomment:3d 模式:并排式 左右全场*/
    VOUT_3D_FORMAT_L_DEPTH,                  /**<3d type:L+depth*//**<CNcomment:3d 模式:L+DEPTH*/
    VOUT_3D_FORMAT_LBL_LR,                   /**<3d type:Line alternative Left Eye Fisrt*//**<CNcomment:3d 模式:行交错,左眼优先*/
    VOUT_3D_FORMAT_LBL_RL,                   /**<3d type:Line alternative Right Eye Fisrt*//**<CNcomment:3d 模式:行交错,右眼优先*/
    VOUT_3D_FORMAT_L_DEPTH_GRAPHISC_DEPTH,   /**<3d type:L+depth+Graphics+Graphics-depth*//**<CNcomment:3d 模式:L+depth+Graphics+Graphics-depth*/
    VOUT_3D_FORMAT_BUTT
} VOUT_3D_FORMAT_E;
/**Defines of video 3d mode enum */
/**CNcomment:定义3D视频播放模式枚举 */
typedef enum _VOUT_3D_MODE_E
{
    VOUT_3D_MODE_2D = 0,  /**<2D mode *//**<CNcomment:2D模式播放 */
    VOUT_3D_MODE_2DTO3D,  /**<2D to 3D mode *//**<CNcomment:2D转3D模式播放 */
    VOUT_3D_MODE_3D,      /**<3D mode *//**<CNcomment:3D模式播放 */
    VOUT_3D_MODE_BUTT,
} VOUT_3D_MODE_E;

/**Defines of window channel type */
/**CNcomment:定义视频通路延时结构体 */
typedef enum VOUT_WINDOW_CHANNEL_E
{
    VOUT_WINDOW_HIGHQUALITY = 0,
    VOUT_WINDOW_LOWQUALITY,
    VOUT_WINDOW_MAX,
} VOUT_WINDOW_CHANNEL_E;

/**Struct of stop mode*/
/**CNcomment:停止模式  */
typedef enum _VOUT_WINDOW_STOP_MODE_E
{
    VOUT_WINDOW_STOP_MODE_BLACK = 0,   /**<Black*//**<CNcomment: 黑屏*/
    VOUT_WINDOW_STOP_MODE_FREEZE       /**<Freeze last picture*//**<CNcomment: 静帧*/
} VOUT_WINDOW_STOP_MODE_E;

/**enum define about Window Type */
/**CNcomment: 定义Window类型枚举*/
typedef enum hiUNF_VO_WIN_TYPE_E
{
    VOUT_WINDOW_TYPE_DEFAULT = 0,   /**<create defalut window*//**<CNcomment: 默认的窗口类型*/
    VOUT_WINDOW_TYPE_AUTO,          /**<create auto window*//**<CNcomment: 创建自动窗口通道*/
    VOUT_WINDOW_TYPE_MAIN,          /**<create main window*//**<CNcomment: 创建主场口通道*/
    VOUT_WINDOW_TYPE_SUB,           /**<create sub window*//**<CNcomment: 创建次窗口通道*/
    VOUT_WINDOW_TYPE_BUTT
} VOUT_WINDOW_TYPE_E;

/**Defines video coordinate */
typedef S32 AV_COORD_T;

/**Struct of default video output settings, SD anf HD can be set independently,  see the define of VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_VID_FRAME_RATE_E*/
/**CNcomment:默认显示设置，高标清要能独立设置，见VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_VID_FRAME_RATE_E*/
typedef struct _VOUT_DEFAULT_DISPSETTING_S
{
    VOUT_FORMAT_E           enDispFmt;                /**<Video output format, do not set auto, auto means no stream now*//**< CNcomment:不要设为自动模式,当av_dispsettings_t::enDispFmt 是AUTO而且刚开机还没有流的时候,HDI应该设置成此格式,以方便APP知道当前状态,另,SD通道的设置是流NTSC,PAL&PALN,PALM&VOUT_FORMAT_SECAM的判断依据.*/
    VOUT_VID_FRAME_RATE_E   enFrameRate;              /**<Frame rate, do not set auto, auto means no stream now*//**< CNcomment:不要设为自动模式,当av_dispsettings_t::enFrameRate 是AUTO而且刚开机还没有流的时候,HDI应该设置成此格,以方便APP知道当前状态*/
    VOUT_ASPECT_RATIO_E     enAspectRatio;            /**<Aspect ratio, do not set auto, auto means no stream now*//**< CNcomment:不要设为自动模式,当av_dispsettings_t::enAspectRatio 是AUTO而且刚开机还没有流的时候,HDI应该设置成此格,以方便APP知道当前状态*/
} VOUT_DEFAULT_DISPSETTING_S;

/**Struct of Rectangle*/
/**CNcomment:矩形结构  */
typedef struct _VOUT_RECT_S
{
    S32 s32XOffset;
    S32 s32YOffset;
    U32 u32Width;
    U32 u32Height;
} VOUT_RECT_S;

/**Struct of Region*/
/**CNcomment:区域结构  */
typedef struct _VOUT_REGION_S
{
    U32 u32Left;
    U32 u32Top;
    U32 u32Right;
    U32 u32Bottom;
} VOUT_REGION_S;

/**Struct of display settings of video output
1.SD or HD can be set independently.
2.Get display param first, and then renew the param, then set.
3.The set operation may be cover the settings set by other task.
4.av_init do not process the values of u8Brightness,u8Contrast,u8Saturation in VOUT_DISPSETTING_S, but av_display_set process.
5.The output type(enOutputType) can be attached and detached dynamically. If unspported type was set on the wrong display channel, HDI ignore it and do not return error.
6.Auto set valid value when brightness,contrast,saturation,alpha,3d_dof are over range.*/
/**CNcomment:显示设置,
1. 高标清要能独立设置.
2. 需要修改这些参数时,请先get出来,修改需要修改的成员再set回去. set函数里面对于没有改变的成员不做修改,
3. 考虑到多任务操作,get出来的参数在set回去之前,别的任务可能已经有set操作. 也就是此时的set有可能会覆盖其他任务set函数的设置
4. brightness,contrast,saturation在有些平台上会影响到视频指标,而且修改以后很难设回默认值
为了不影响到视频指标,av_init()函数对外面传进来的u8Brightness,u8Contrast,u8Saturation,不处理
开机后get出来的是系统的默认值,建议保存给恢复出厂设置用.
av_display_set()函数会处理外面传进来的u8Brightness,u8Contrast,u8Saturation,修改brightness,contrast,saturation.
5. enOutputType::显示绑定的输出设备,支持或操作,可以运行时动态绑定(输出)和解绑定(不输出).
VOUT_OUTPUT_TYPE_NONE 是不输出,VOUT_OUTPUT_TYPE_ALL 是输出到当前设备的所有支持的设备,
如果应用设置了不支持的设备,比如高清通道设置了 VOUT_OUTPUT_TYPE_COMPOSITE(cvbs)
HDI 要自动忽略,不做错误返回.
6. brightness,contrast,saturation,alpha,3d_dof 如果参数超出范围, HDI 需要修正到合理范围.
*@see VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_ASPECT_RATIO_CONVERSION_E, VOUT_OUTPUT_TYPE_E, VOUT_ALPHA_T
*@see VOUT_SATURATION_MAX, VOUT_SATURATION_MIN;VOUT_CONTRAST_MAX,VOUT_CONTRAST_MIN;
*@see VOUT_BRIGHTNESS_MAX, VOUT_BRIGHTNESS_MIN;VOUT_ALPHA_MAX, VOUT_ALPHA_MIN*/
typedef struct _VOUT_DISPSETTING_S
{
    VOUT_FORMAT_E                   enDispFmt;          /**<Display format, default is VOUT_FORMAT_AUTO*//**<CNcomment: 默认为VOUT_FORMAT_AUTO,如果是AUTO,1.刚开机还没有流的时候,应该是av_default_dispsettings_t::enDispFmt,2.如果切台,没有流,应该保持原来的设置不变.*/
    VOUT_VID_FRAME_RATE_E           enFrameRate;        /**<Frame rate , default is VOUT_VID_FRAME_RATE_AUTO*//**<CNcomment: 默认为VOUT_VID_FRAME_RATE_AUTO, 如果是AUTO,1.刚开机还没有流的时候,应该是av_default_dispsettings_t::enFrameRate,2.如果切台,没有流,应该保持原来的设置不变.*/
    VOUT_FORMAT_E                   enAutoDispFmt;      /**<Auto adaption display format, it is depend on device*/ /**<CNcomment: 自适应制式，根据设备而定*/
    VOUT_VID_FRAME_RATE_E           enAutoFrameRate;    /**<Auto adaption frame rate, it is depend on device*/ /**<CNcomment: 自适应帧率，根据设备而定*/
    VOUT_ASPECT_RATIO_E             enAspectRatio;      /**<Aspect ratio , default is VOUT_ASPECT_RATIO_AUTO*//**<CNcomment: 默认为VOUT_ASPECT_RATIO_AUTO,如果是AUTO,1.刚开机还没有流的时候,应该是av_default_dispsettings_t::enAspectRatio,2.如果切台,没有流,应该保持原来的设置不变.*/
    VOUT_ASPECT_RATIO_CONVERSION_E  enAspectRatioConv;  /**<Conversion mode of aspectRatio , default is VOUT_AR_CONVERSION_LETTER_BOX*//**<CNcomment: 默认为VOUT_AR_CONVERSION_LETTER_BOX*/
    VOUT_OUTPUT_TYPE_E              enOutputType;       /**<Video output type, can be attached and detached dynamically*//**<CNcomment: 显示绑定的输出设备(支持或操作,可以动态绑定和解绑定) */
    BOOL                            bOutputEnable;      /**<Video output switch, default is TRUE*//**<CNcomment: 是否有输出,只对当前通道有效, 默认为true.*/
    U8                              u8Hue;              /**<Hue, range is [0, 100]*//**<CNcomment: 色调，范围[0, 100].*/
    U8                              u8Brightness;       /**<To adjust the luminance intensity of the display video image.This value is unsigned and scaled between VOUT_BRIGHTNESS_MIN to VOUT_BRIGHTNESS_MAX.Default value are (VOUT_BRIGHTNESS_MAX/2).*//**<CNcomment: 亮度,范围是[VOUT_BRIGHTNESS_MIN, VOUT_BRIGHTNESS_MAX], 默认为VOUT_BRIGHTNESS_MAX/2.*/
    U8                              u8Contrast;         /**<To adjust the relative difference between higher and lower intensity luminance values of the display image.This value is unsigned and scaled between VOUT_CONTRAST_MIN to VOUT_CONTRAST_MAX.Default value are (VOUT_CONTRAST_MAX/2).*//**<CNcomment: 对比度,范围是[VOUT_CONTRAST_MIN, VOUT_CONTRAST_MAX], 默认为VOUT_CONTRAST_MAX/2.*/
    U8                              u8Saturation;       /**<To adjust the color intensity of the displayed video image.This value is unsigned and scaled between VOUT_SATURATION_MIN to VOUT_SATURATION_MAX.Default value are (VOUT_SATURATION_MAX/2).*//**<CNcomment: 饱和度,范围是[VOUT_SATURATION_MIN, VOUT_SATURATION_MAX], 默认为VOUT_SATURATION/2.*/
    U8                              u83dDof;            /**<Depth of field*//**<CNcomment: 景深值,范围[VOUT_DOF_MIN,VOUT_DOF_MAX]*/
    VOUT_3D_FORMAT_E                en3dFmt;            /**<3D format*/ /**<CNcomment: 3d格式  */
    VOUT_RECT_S                     stOSDVirtualRect;   /**<OSD虚拟分辨率 */
    VOUT_REGION_S                   stDispOutRegion;    /**<OSD显示区域*/
    BOOL                            bClearLogo;         /**<clear logo while starting up*/ /**< CNcomment: 清空开机画面.*/
} VOUT_DISPSETTING_S;

/**Struct of video out init parameters*/
/**CNcomment:视频模块初始化参数 */
typedef struct _VOUT_INIT_PARAMS_S
{
    BOOL                bDispEnable;                        /**<Wether output after init*//**<<CNcomment: ture:初始化同时enable disp输出(av, osd ,still, etc.); false: 初始化后没有输出(av, osd, still, etc.), 就是待机功能, 待机状态下重启没有输出*/
    VOUT_DISPSETTING_S  astDispSettings[VOUT_DISPLAY_MAX];  /**<Video output disp settings, this array index correspond the item index of VOUT_DISPLAY_CHANNEL_E, not the enum value*//**<CNcomment: 视频层参数，这个数组索引值与VOUT_DISPLAY_CHANNEL_E的条目序号对应，不是与枚举值对应*/
    U32                 u32Dummy;                           /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_INIT_PARAMS_S;

/**Struct of color space*/
/**CNcomment:定义显示颜色的结构体 */
typedef struct  _VOUT_BG_COLOR_S
{
    U8 u8Red;               /**<Red *//**<CNcomment:红色分量*/
    U8 u8Green;             /**<Green*//**<CNcomment:绿色分量*/
    U8 u8Blue;              /**<Blue*//**<CNcomment:蓝色分量*/
} VOUT_BG_COLOR_S;

/**Struct of open parameters*/
/**CNcomment:打开一个实例化句柄参数 */
typedef struct _VOUT_OPEN_PARAMS_S
{
    VOUT_DISPLAY_CHANNEL_E enDispChan;      /**<Display channel need to be opened*//**<CNcomment: 需要打开的显示通道 */
    VOUT_OUTPUT_TYPE_E enOutputType;        /**<Video output type*//**<CNcomment:视频输出类型*/
    U32 u32Dummy;                           /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_OPEN_PARAMS_S;

/**Struct of close parameters*/
/**CNcomment:打关闭实例参数  */
typedef struct _VOUT_CLOSE_PARAMS_S
{
    U32 u32Dummy; /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_CLOSE_PARAMS_S;

/**Struct of terminate parameters*/
/**CNcomment:AV模块终止参数   */
typedef struct _VOUT_TERM_PARAM_S
{
    U32 u32Dummy; /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_TERM_PARAM_S;

/**Struct of the display capability of video output */
/**CNcomment:视频输出能力 */
typedef struct _VOUT_DISP_CAPABILITY_S
{
    VOUT_OUTPUT_TYPE_E   enVoutType;                        /**<Video output type*//**<CNcomment:视频输出类型*/
    U32                  au32VidFormat[VOUT_FORMAT_BUTT];   /**<Video format, VOUT_FORMAT_E is index, 0 means do not supported this format*/ /**<CNcomment: 以VOUT_FORMAT_E为索引,其值是支持的VOUT_VID_FRAME_RATE_E变量或出来的值,其值为0.则表示不支持这种分辨率*/
    U32                  u32WindowNum;                      /**<Number of windows can be supportted*//**<CNcomment:  支持的window数目 */
} VOUT_DISP_CAPABILITY_S;

/**Struct of video output capability*/
/**CNcomment:视频输出能力 */
typedef struct _VOUT_CAPABILITY_S
{
    VOUT_DISPLAY_CHANNEL_E  enDisplayChannel;                          /**<Video output display channels*//**<CNcomment:视频输出通道*/
    VOUT_DISP_CAPABILITY_S  astDispCapabilityAttr[VOUT_DISPLAY_MAX];   /**<Capability of Video output display channels, this array index correspond the item index of VOUT_DISPLAY_CHANNEL_E, not the enum value*//**<CNcomment:视频输出通道能力, 这个数组索引值与VOUT_DISPLAY_CHANNEL_E的条目序号对应，不是与枚举值对应*/
} VOUT_CAPABILITY_S;

/**
\brief Video output event callback. CNcomment:vout 事件回调函数类型声明CNend
\attention \n
The function could call the api of VOUT module
CNcomment: 此函数里面可以调用本模块的api, 也就是说驱动在回调本函数时，要同时考虑到重入和死锁两个方面CNend
\param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
\param[in] enEvt VOUT event type.CNcomment:VOUT事件类型 CNend
\param[in] pData The data with event, see VOUT_EVT_E.CNcomment:请参考 VOUT_EVT_E 的说明 CNend
\retval ::SUCCESS CNcomment:成功 CNend
\retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
\see \n
::VOUT_EVT_E
*/
typedef VOID (* VOUT_CALLBACK_PFN)( const HANDLE hVout, const VOUT_EVT_E enEvt, const VOID* const pData);

/**Struct of config parameters of video out event callback, see VOUT_EVT_E, vout_callback_pfn_t*/
/**CNcomment:视频输出回调函数的配置参数, 见VOUT_EVT_E, vout_callback_pfn_t 定义 */
typedef struct _VOUT_EVT_CONFIG_PARAMS_S
{
    VOUT_EVT_E        enEvt;                       /**<The events we want to get by callback*//**<CNcomment: av 事件,表示此配置对哪个事件有效*/
    VOUT_CALLBACK_PFN pfnCallback;                 /**<If pfnCallback is null, unregister the unregistered callback function*//**<CNcomment: 当pfnCallback为空时,如果已经注册了回调函数则移除,取消该注册*/
    BOOL              bEnable;                     /**<Wether enable the callback of enEvt*//**<CNcomment: 表示是否使能该事件回调*/
    U32               u32NotificationsToSkip;      /**<The skip counts before we get the callback of enEvt*//**<CNcomment: 表示在调用注册的回调函数之前,需要跳过几次发生的该事件*/
} VOUT_EVT_CONFIG_PARAMS_S;

/**Strcut of video channel delay */
/**CNcomment:定义视频通路延时结构体 */
typedef struct _VOUT_DELAY_S
{
    U32        u32PanelMemcDelay;
} VOUT_DELAY_S;

/**Struct of create window parameters*/
/**CNcomment:创建窗口参数   */
typedef struct _VOUT_WINDOW_CREATE_PARAMS_S
{
    VOUT_WINDOW_CHANNEL_E enWindowChan;
    BOOL                  bVirtual;          /**<Resvered*//**<CNcomment: create virtual_window */
    VOUT_WINDOW_TYPE_E    enWindowType;      /**<Window type*//**<CNcomment: 创建的窗口类型 */
    U32 u32Dummy;                            /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_WINDOW_CREATE_PARAMS_S;

/**Struct of destroy window parameters*/
/**CNcomment:销毁窗口参数   */
typedef struct _VOUT_WINDOW_DESTROY_PARAM_S
{
    U32 u32Dummy;                            /**<Resvered*//**<CNcomment: 以后扩展用 */
} VOUT_WINDOW_DESTROY_PARAM_S;

/** RGB Color *//**CNcomment:RGB格式 */
typedef struct _VOUT_RGB_COLOR_S
{
    U32 u32Red;
    U32 u32Green;
    U32 u32Blue;
} VOUT_RGB_COLOR_S;

/**Struct of color temperature of window*/
/**CNcomment:色温参数  */
typedef struct _VOUT_WINDOW_COLOR_TEMPERATURE_S
{
    U32 u32RedGain;                  /**<Red gain*//**<CNcomment: 红色增益 */
    U32 u32GreenGain;                /**<Green gain*//**<CNcomment: 绿色增益 */
    U32 u32BlueGain;                 /**<Blue gain*//**<CNcomment: 蓝色增益 */
    U32 u32RedOffset;                /**<Red offset*//**<CNcomment: 红色偏移*/
    U32 u32GreenOffset;              /**<Red offset*//**<CNcomment: 红色偏移*/
    U32 u32BlueOffset;               /**<Red offset*//**<CNcomment: 红色偏移*/
} VOUT_WINDOW_COLOR_TEMPERATURE_S;

/** window status *//**CNcomment:窗口状态 */
typedef struct _VOUT_WINDOW_STATUS_S
{
    U8                              u8WinEnableStatus;        /** if the window is enable. */
    U8                              u8WindowConnected;        /** if the window is connected. */
    BOOL                            bWindowEnableMute;        /** if the window is mute. False;TRUE: the window is muted. */
    U32                             u32ZOrderIndex;           /** zorder set by "vout_set_window_zorder". */
    VOUT_RGB_COLOR_S                stMuteRGBColor;           /** mute color set by "vout_set_window_mute_color". */
    VOUT_WINDOW_COLOR_TEMPERATURE_S stColorTemperature;       /** color temperature set by "vout_set_window_colortemperature". */
} VOUT_WINDOW_STATUS_S;

/**Struct of stop parameters*/
/**CNcomment:停止参数  */
typedef struct _VOUT_WINDOW_STOP_ATTR_S
{
    VOUT_WINDOW_STOP_MODE_E enStopMode;                       /**<Stop mode*//**<CNcomment: 停止模式*/
} VOUT_WINDOW_STOP_ATTR_S;

/**Struct of window attribute of user defined*/
/**CNcomment:用户设定的窗口属性*/
typedef struct _VOUT_WINDOW_USER_DEF_ASPECT_S {
    BOOL      bUserDefAspectRatio;           /**<CNcomment: 是否使用用户设定的宽高比, 为TRUE时，u32UserAspectWidth和u32UserAspectHeight生效 */
    U32       u32UserAspectWidth;            /**<CNcomment: 用户期望显示的视频宽度设置值范围在0~3840之间 0代表使用视频源分辨率 */
    U32       u32UserAspectHeight;           /**<CNcomment: 用户期望显示的视频高度设置值范围需要在0~3840的范围内0代表使用视频源分辨率 */
}VOUT_WINDOW_USER_DEF_ASPECT_S;

/**Struct of setting parameters of window attribute*/
/**CNcomment:窗口属性设置参数*/
typedef struct _VOUT_WINDOW_SETTINGS_S
{
    VOUT_WINDOW_USER_DEF_ASPECT_S   stWindowUserDefAspect;    /**<user define aspcet for width height>*/
    VOUT_ASPECT_RATIO_E             enAspectRatio;            /**<Aspect ratio , default is VOUT_ASPECT_RATIO_AUTO*//**<CNcomment: 默认为VOUT_ASPECT_RATIO_AUTO,如果是AUTO,1.刚开机还没有流的时候,应该是av_default_dispsettings_t::enAspectRatio,2.如果切台,没有流,应该保持原来的设置不变.*/
    VOUT_ASPECT_RATIO_CONVERSION_E  enAspectRatioConv;        /**<Conversion mode of aspectRatio , default is VOUT_AR_CONVERSION_LETTER_BOX*//**<CNcomment: 默认为VOUT_AR_CONVERSION_LETTER_BOX*/
    VOUT_ALPHA_T                    u8Alpha;                  /**<Alpha, range is [VOUT_ALPHA_MIN, VOUT_ALPHA_MAX]*//**<CNcomment: 透明度，范围[VOUT_ALPHA_MIN, VOUT_ALPHA_MAX].*/
    U8                              u8Brightness;             /**<To adjust the luminance intensity of the display video image.This value is unsigned and scaled between VOUT_BRIGHTNESS_MIN to VOUT_BRIGHTNESS_MAX.Default value are (VOUT_BRIGHTNESS_MAX/2).*//**<CNcomment: 亮度,范围是[VOUT_BRIGHTNESS_MIN, VOUT_BRIGHTNESS_MAX], 默认为VOUT_BRIGHTNESS_MAX/2.*/
    U8                              u8Contrast;               /*<To adjust the relative difference between higher and lower intensity luminance values of the display image.This value is unsigned and scaled between VOUT_CONTRAST_MIN to VOUT_CONTRAST_MAX.Default value are (VOUT_CONTRAST_MAX/2).*//**<CNcomment: 对比度,范围是[VOUT_CONTRAST_MIN, VOUT_CONTRAST_MAX], 默认为VOUT_CONTRAST_MAX/2.*/
    U8                              u8Saturation;             /**<To adjust the color intensity of the displayed video image.This value is unsigned and scaled between VOUT_SATURATION_MIN to VOUT_SATURATION_MAX.Default value are (VOUT_SATURATION_MAX/2).*//**<CNcomment: 饱和度,范围是[VOUT_SATURATION_MIN, VOUT_SATURATION_MAX], 默认为VOUT_SATURATION/2.*/
    BOOL                            bVirtual;                 /**<is virtual window*//**<CNcomment: 是否为虚拟window */
} VOUT_WINDOW_SETTINGS_S;

/**frame addr.*//**CNcomment: 帧地址*/
typedef struct _VOUT_FRAME_ADDR_S
{
    U32             u32YAddr;        /**<Address of the Y component in the current frame*/ /**<CNcomment: 当前帧Y分量数据的地址*/
    U32             u32CAddr;        /**<Address of the C component in the current frame*/ /**<CNcomment: 当前帧C分量数据的地址*/
    U32             u32CrAddr;       /**<Address of the Cr component in the current frame*/ /**<CNcomment: 当前帧Cr分量数据的地址*/

    U32             u32YStride;      /**<Stride of the Y component*/ /**<CNcomment: Y分量数据的跨幅*/
    U32             u32CStride;      /**<Stride of the C component*/ /**<CNcomment: C分量数据的跨幅*/
    U32             u32CrStride;     /**<Stride of the Cr component*/ /**<CNcomment: Cr分量数据的跨幅*/
} VOUT_FRAME_ADDR_S;

/**Defines the frame rate of the video stream.*/
/**CNcomment: 定义视频码流帧率结构*/
typedef struct _VOUT_VCODEC_FRMRATE_S
{
    U32 u32fpsInteger;               /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: 码流的帧率的整数部分, fps */
    U32 u32fpsDecimal;               /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*/
                                     /**<CNcomment: 码流的帧率的小数部分（保留3位）, fps */
} VOUT_VCODEC_FRMRATE_S;

/**Defines the video format.*/
/**CNcomment: 定义视频格式枚举*/
typedef enum _VOUT_VIDEO_FORMAT_E
{
    VOUT_FORMAT_YUV_SEMIPLANAR_422 = 0,   /**<The YUV spatial sampling format is 4:2:2.*/ /**<CNcomment: YUV空间采样格式为4:2:2*/
    VOUT_FORMAT_YUV_SEMIPLANAR_420,       /**<The YUV spatial sampling format is 4:2:0, V first.*/ /**<CNcomment: YUV空间采样格式为4:2:0，V在低位*/
    VOUT_FORMAT_YUV_SEMIPLANAR_400,
    VOUT_FORMAT_YUV_SEMIPLANAR_411,
    VOUT_FORMAT_YUV_SEMIPLANAR_422_1X2,
    VOUT_FORMAT_YUV_SEMIPLANAR_444,
    VOUT_FORMAT_YUV_SEMIPLANAR_420_UV,    /**<The YUV spatial sampling format is 4:2:0,U first.*/ /**<CNcomment: YUV空间采样格式为4:2:0, U在低位*/
    VOUT_FORMAT_YUV_PACKAGE_UYVY,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is UYVY.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为UYVY*/
    VOUT_FORMAT_YUV_PACKAGE_YUYV,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YUYV.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为YUYV*/
    VOUT_FORMAT_YUV_PACKAGE_YVYU,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YVYU.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为YVYU*/
    VOUT_FORMAT_YUV_PLANAR_400,
    VOUT_FORMAT_YUV_PLANAR_411,
    VOUT_FORMAT_YUV_PLANAR_420,
    VOUT_FORMAT_YUV_PLANAR_422_1X2,
    VOUT_FORMAT_YUV_PLANAR_422_2X1,
    VOUT_FORMAT_YUV_PLANAR_444,
    VOUT_FORMAT_YUV_PLANAR_410,
    VOUT_FORMAT_YUV_BUTT,
    VOUT_FORMAT_RGB_SEMIPLANAR_444,
    VOUT_FORMAT_RGB_BUTT
} VOUT_VIDEO_FORMAT_E;

/**Defines the video frame/field mode.*/
/**CNcomment: 定义视频帧场模式枚举*/
typedef enum _VOUT_VIDEO_FIELD_MODE_E
{
    VOUT_VIDEO_FIELD_ALL = 0,    /**<Frame mode*/ /**<CNcomment: 帧模式*/
    VOUT_VIDEO_FIELD_TOP,        /**<Top field mode*/ /**<CNcomment: 顶场模式*/
    VOUT_VIDEO_FIELD_BOTTOM,     /**<Bottom field mode*/ /**<CNcomment: 底场模式*/
    VOUT_VIDEO_FIELD_BUTT
} VOUT_VIDEO_FIELD_MODE_E;

/**Defines 3D frame packing type*//**CNcomment: 3D framepacking帧类型*/
typedef enum _VOUT_VIDEO_FRAME_PACKING_TYPE_E
{
    VOUT_FRAME_PACKING_TYPE_NONE = 0,         /**< Normal frame, not a 3D frame */
    VOUT_FRAME_PACKING_TYPE_SIDE_BY_SIDE,     /**< Side by side */
    VOUT_FRAME_PACKING_TYPE_TOP_AND_BOTTOM,   /**< Top and bottom */
    VOUT_FRAME_PACKING_TYPE_TIME_INTERLACED,  /**< Time interlaced: one frame for left eye, the next frame for right eye */
    VOUT_FRAME_PACKING_TYPE_FRAME_PACKING,    /**< frame packing */
    VOUT_FRAME_PACKING_TYPE_3D_TILE,          /**< Tile 3D */
    VOUT_FRAME_PACKING_TYPE_BUTT
} VOUT_VIDEO_FRAME_PACKING_TYPE_E;

/**frame info*//**CNcomment: 帧信息*/
typedef struct _VOUT_FRAME_INFO_S
{
    U32                                       u32FrameIndex;         /**<Frame index ID of a video sequence, for debug*/ /**<CNcomment: 视频序列中的帧索引号，调试用*/
    VOUT_FRAME_ADDR_S                         stVideoFrameAddr[2];   /**<Frame addr info, maybe need two items for 3d*/ /**<CNcomment: 帧地址信息，对3d可能需要两项*/
    U32                                       u32Width;              /**<Width of the source picture*/ /**<CNcomment: 原始图像宽*/
    U32                                       u32Height;             /**<Height of the source picture*/ /**<CNcomment: 原始图像高*/
    S64                                       s64SrcPts;             /**<Original PTS of a video frame*/ /**<CNcomment: 视频帧的原始时间戳*/
    S64                                       s64Pts;                /**<PTS of a video frame*/ /**<CNcomment: 视频帧的时间戳*/
    U32                                       u32AspectWidth;        /**<Aspect width*/ /**<CNcomment: 比例宽度*/
    U32                                       u32AspectHeight;       /**<Aspect height*/ /**<CNcomment: 比例高度*/
    VOUT_VCODEC_FRMRATE_S                     stFrameRate;           /**<Frame rate*/ /**<CNcomment: 帧率*/

    VOUT_VIDEO_FORMAT_E                       enVideoFormat;         /**<Video YUV format*/ /**<CNcomment: 视频YUV格式*/
    BOOL                                      bProgressive;          /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: 采样方式(逐行/隔行) */
    VOUT_VIDEO_FIELD_MODE_E                   enFieldMode;           /**<Frame or field encoding mode*/ /**<CNcomment: 帧或场编码模式*/
    BOOL                                      bTopFieldFirst;        /**<Top field first flag*/ /**<CNcomment: 顶场优先标志*/
    VOUT_VIDEO_FRAME_PACKING_TYPE_E           enFramePackingType;    /**<3D frame packing type*/
    U32                                       u32Circumrotate;       /**<Need circumrotate, 1 need *//**<CNcomment: 旋转标志*/
    BOOL                                      bVerticalMirror;       /**<vertical mirror flag *//**<CNcomment: 垂直镜像标志*/
    BOOL                                      bHorizontalMirror;     /**<horizontal mirror flag *//**<CNcomment: 水平镜像标志*/
    U32                                       u32DisplayWidth;       /**<Width of the displayed picture*/ /**<CNcomment: 显示图像宽*/
    U32                                       u32DisplayHeight;      /**<Height of the displayed picture*/ /**<CNcomment: 显示图像高*/
    U32                                       u32DisplayCenterX;     /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: 显示中心x坐标，原始图像左上角为坐标原点*/
    U32                                       u32DisplayCenterY;     /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: 显示中心y坐标，原始图像左上角为坐标原点*/
    U32                                       u32ErrorLevel;         /**<Error percentage of a decoded picture, ranging from 0% to 100%*/ /**<CNcomment: 一幅解码图像中的错误比例，取值为0～100*/
    BOOL                                      bSecurityFrame;        /**<Security frame flag*/ /**<CNcomment: 安全帧标志*/
    U32                                       u32Private[32];
} VOUT_FRAME_INFO_S;

/**Defines of window switch mode.*//**CNcomment: 定义窗口切换模式*/
typedef enum _VOUT_WINDOW_SWITCH_MODE_E
{
    VOUT_WINDOW_SWITCH_MODE_FREEZE = 0,             /**<Freeze the last frame *//**<CNcomment: 静帧*/
    VOUT_WINDOW_SWITCH_MODE_BLACK,                  /**<Show black screen *//**<CNcomment: 黑屏*/
    VOUT_WINDOW_SWITCH_MODE_BUTT
} VOUT_WINDOW_SWITCH_MODE_E;

#ifdef HAL_HISI_EXTEND_H

/**Defines the type of VOUT invoke.*/
/**CNcomment: 定义VOUT Invoke调用类型的枚举 */
typedef enum _VOUT_INVOKE_E
{
    VOUT_INVOKE_REG_CALLBACK = 0x0,                 /**<Invoke command to register vout callback*//**<CNcomment: 注册vout对外部依赖的回调接口 */

    VOUT_INVOKE_BUTT
} VOUT_INVOKE_E;

#endif

#ifdef ANDROID_HAL_MODULE_USED
/**Video output module structure(Android require)*/
/**CNcomment:视频输出模块结构(Android对接要求) */
typedef struct _VOUT_MODULE_S
{
    struct hw_module_t stCommon;
} VOUT_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_VOUT */
/** @{ */  /** <!-- [HAL_VOUT] */

/**Video output device structure*//** CNcomment:视频输出设备结构 */
typedef struct _VOUT_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief Video output init.CNcomment:视频输出初始化 CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: 在初始化之前, 其他函数都不能正确运行, 重复调用init 接口,返回SUCCESS. CNend
    \param[in] pstInitParams Vout module init param.CNcomment:初始化模块参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_INIT_FAILED  other error.CNcomment:其它错误 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_init)(struct _VOUT_DEVICE_S* pstVoutDev, const VOUT_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief bind one DISP channel to another. CNcomment:将两个DISPLAY通道绑定 CNend
    \attention \n
    Please finish the bind operation before the DISP channel has been open, and currently we only support HD channel attach to SD channel.
    CNcomment: 目前只支持将高清DISP通道绑定到标清DISP通道上，绑定操作必须在DISP通道打开前完成. CNend
    \param[in] enDstDisp Destination DISP channel.CNcomment:目标DISPLAY通道 CNend
    \param[in] enSrcDisp source DISP channel.CNcomment:源DISPLAY通道 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_DISPLAY_CHANNEL_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_channel_bind)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_DISPLAY_CHANNEL_E enDstDisp, VOUT_DISPLAY_CHANNEL_E enSrcDisp);

    /**
    \brief unbind DISP channel. CNcomment:将两个DISPLAY通道解绑定 CNend
    \attention \n
    should close the DISP channels, before do unbind operation.
    CNcomment: 只有在关闭DISP通道后，才能进行解绑定操作. CNend
    \param[in] enDstDisp Destination DISP channel.CNcomment:目标DISPLAY通道 CNend
    \param[in] enSrcDisp source DISP channel.CNcomment:源DISPLAY通道 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_DISPLAY_CHANNEL_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_channel_unbind)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_DISPLAY_CHANNEL_E enDstDisp, VOUT_DISPLAY_CHANNEL_E enSrcDisp);

    /**
    \brief Open a video output instance.CNcomment:打开一个视频输出实例 CNend
    \attention \n
    CNcomment: 无CNend
    \param[in] pstOpenParams Open param.CNcomment:实例打开参数 CNend
    \param[out] phVout Return VOUT handle .CNcomment:返回VOUT句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_VO_OPEN_FAILED  other error.CNcomment:其它错误 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_OPEN_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_open_channel)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE* const phVout, const VOUT_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief Close a video output instance.CNcomment:关闭一个视频输出实例 CNend
    \attention \n
    CNcomment: 无CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstCloseParams Close param.CNcomment:实例关闭参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_CLOSE_FAILED  other error.CNcomment:其它错误 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_CLOSE_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_close_channel)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief Terminate video output module. CNcomment:模块终止 CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: 重复term 返回SUCCESS. CNend
    \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:终止模块参数，为NULL  表示强制终止 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_TERM_FAILED  other error.CNcomment:其它错误 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_TERM_PARAM_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_term)(struct _VOUT_DEVICE_S* pstVoutDev, const VOUT_TERM_PARAM_S* const  pstTermParams);

    /**
    \brief Get the capability of video ouput module. CNcomment:获取模块设备能力 CNend
    \attention \n
    CNcomment: 无CNend
    \param[out] pstCapability Capability param.CNcomment:模块能力参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_CAPABILITY_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_capability)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_CAPABILITY_S* const pstCapability);

    /**
    \brief Config the callback attribute of VOUT event. CNcomment:配置某一VOUT事件的参数 CNend
    \attention \n
    The function can execute regist/remove/disable/enable
    1.Each event can register callback function and set it's config independently.
    2.Callback function bind with VOUT handle.
    3.Only one callback function can be registered for a vout event on the same vout handle, so the callback function will be recovered.
    CNcomment: 通过本函数可以执行的操作有regist/remove/disable/enable
    1. 每个事件都可以独立注册和配置自己的回调函数.
    2. 回调函数和handle绑定.
    3. 同一个handle, 一个事件只能注册一个回调函数,即:后面注册的回调函数会覆盖原有的回调函数.
    CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstCfg Config param.CNcomment:事件配置参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_EVT_CONFIG_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_evt_config)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_EVT_CONFIG_PARAMS_S* const pstCfg);

    /**
    \brief Get the config of a VOUT event. CNcomment:获取某一vout事件的配置参数 CNend
    \attention \n
    CNcomment: 无CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] enEvt VOUT event type.CNcomment:VOUT事件类型 CNend
    \param[in] pstCfg Config param.CNcomment:事件配置参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_EVT_CONFIG_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_evt_config)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_EVT_E enEvt, VOUT_EVT_CONFIG_PARAMS_S*   const pstCfg);

    /**
    \brief Disable video output channel. CNcomment:关闭显示通道 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] enOutChannel Output channel need to be mute.CNcomment:需要关闭输出的通道 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_OUTPUT_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_outputchannel_mute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_OUTPUT_TYPE_E enOutChannel);

    /**
    \brief Enable video output channel. CNcomment:打开显示通道 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] enOutChannel Output channel need to be unmute.CNcomment:需要打开输出的通道 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_OUTPUT_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_outputchannel_unmute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_OUTPUT_TYPE_E enOutChannel);

    /**
    \brief Set display param. CNcomment:设置显示参数 CNend
    \attention \n
    Get display param first, and then renew the param, then set.
    CNcomment: 修改display参数时,请先get出来,修改需要修改的成员再set回去CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstSettings Display param.CNcomment:显示参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_DISPSETTING_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_display_set)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_DISPSETTING_S* const pstSettings);

    /**
    \brief Get display param. CNcomment:获取显示参数 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstSettings Display param.CNcomment:显示参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_TERM_PARAM_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_display_get)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, VOUT_DISPSETTING_S* const pstSettings);

    /**
    \brief Start CGMS. CNcomment:CGMS启动 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] enCgmsType CGMS type.CNcomment:CGMS 类型 CNend
    \param[in] enCopyRight Copy right.CNcomment:拷贝许可 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_VBI_CGMS_TYPE_E, VOUT_VBI_CGMS_A_COPY_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_cgms_start)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout,  VOUT_VBI_CGMS_TYPE_E enCgmsType, VOUT_VBI_CGMS_A_COPY_E enCopyRight);

    /**
    \brief Stop CGMS. CNcomment:CGMS停止 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_cgms_stop)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout);

    /**
    \brief Microvision config CNcomment:Microvision 配置 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pu8MvData Config data.CNcomment:配置数据 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_microvision_setup)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout,  U8* pu8MvData);

    /**
    \brief Microvision enable switch CNcomment:Microvision 打开/关闭 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] bEnable Enable switch.CNcomment:1打开/0关闭CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_microvision_enable)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, BOOL bEnable);

    /**
    \brief Set HDCP params. CNcomment:设置HDCP 参数 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pvData Data.CNcomment:数据 CNend
    \param[in] u32Length Data.CNcomment:数据长度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_hdcp_params)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, void* const pvData, const U32 u32Length);

    /**
    \brief Get status of HDCP. CNcomment:获取HDCP校验状态 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[out] pu32Success HDCP status.CNcomment:HDCP状态 CNend
    0:Default key and app setting key all check failed, or HDMI unconnected.
    1:App setting key check success, do not use default success.
    2::App setting key check failed, use default key.
    3:No HDCP key.
    4:HDCP disabled.
    CNcomment:
    HDCP校验状态
    0:APP设置的KEY和内部默认的KEY都校验失败；或者HDMI没连接
    1:APP设置的KEY校验成功，没有使用默认KEY
    2:APP设置的KEY校验失败，使用默认的KEY校验成功
    3:没有HDCP key
    4:HDCP 功能没有打开.
    CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_hdcp_status)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, U32* pu32Success);

    /**
    \brief Get EDID information. CNcomment:获取EDID原始数据 CNend
    \attention \n
    The buffer allocated externally, buffer size must be 512.
    CNcomment:
    获取原始EDID数据的 buffer, EDID版本不同,读出来的数据也不同.
    最长的数据是512 BYTE,因此buffer 的长度最小是512BYTE,调用者要自己分配
    CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[out] pu8EdidBuf Data buffer.CNcomment:数据缓存CNend
    \param[out] pu32EdidLen Data length.CNcomment:返回原始EDID数据长度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:操作失败。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_edid)(const HANDLE hVout, U8* const pu8EdidBuf, U32* const pu32EdidLen);

    /**
    \brief Set background color of video window. CNcomment:设置视频窗口的背景颜色 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstVoutBgColor Background color info.CNcomment:背景颜色信息 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_BG_COLOR_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_bg_color)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_BG_COLOR_S* pstVoutBgColor);

    /**
    \brief Get background color of video window. CNcomment:获取视频窗口的背景颜色CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[out] pstVoutBgColor Background color info.CNcomment:背景颜色信息 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_bg_color)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_BG_COLOR_S* pstVoutBgColor);

    /**
    \brief Set DISP 3D format. CNcomment:设置3D  模式 CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] en3dMode 3D mode.CNcomment:3D  模式 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_3D_MODE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_3dmode)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_3D_MODE_E en3dMode);

    /**
    \brief Get DISP 3D format. CNcomment:查询DISP的3D制式CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[out] pen3dMode Current 3D mode.CNcomment:当前3D  模式 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_3dmode)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_3D_MODE_E* pen3dMode);

    /**
    \brief Swap left and right eye of 3D output. CNcomment:设置3D输出右互换 CNend
    \attention \n
    Only take effect in 3D output mode. CNcomment: 仅在3D输出时有效 CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[out] u32Switch Right-Eye-First.CNcomment:右眼优先设置 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_3d_lr_switch)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, U32 u32Switch);

    /**
    \brief Auto detect 3d format. CNcomment:自动检测3D 模式CNend
    \attention \n
    This interface maybe cost 1~2 seconds. CNcomment: 这个接口可能需要1~2  秒时间 CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] hVoutWindow VOUT window handle.CNcomment:VOUT 窗口句柄 CNend
    \param[out] pen3dFormat Rturn 3D mode.CNcomment:返回3D 模式 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_autodetect3dformat )(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_3D_FORMAT_E* pen3dFormat);

    /**
    \brief Create a video output window. CNcomment:创建一个显示窗口CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstCreateParams Create param.CNcomment:创建参数 CNend
    \param[out] phVoutWindow Return window handle.CNcomment:返回窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_create)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, HANDLE* const phVoutWindow, const VOUT_WINDOW_CREATE_PARAMS_S* const pstCreateParams);

    /**
    \brief Destroy a video output window. CNcomment:销毁一个显示窗口CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT 句柄 CNend
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:销毁参数 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_destroy)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const HANDLE hVoutWindow, const VOUT_WINDOW_DESTROY_PARAM_S* const pstDestroyParams);

    /**
    \brief Set window param. CNcomment:设置window参数CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] pstSettings Window setting param.CNcomment:设置参数   CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const VOUT_WINDOW_SETTINGS_S* const pstSettings);

    /**
    \brief Get window param. CNcomment:设置window参数CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] pstSettings Return window setting param.CNcomment:设置参数   CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_SETTINGS_S* const pstSettings);

    /**
    \brief Set window input size. CNcomment:设置视频输入窗口的大小CNend
    \attention \n
    Conventions are as follows:
    1.TODO 没有描述中所说的参数.
    2.TODO 没有描述中所说的参数.
    3.TODO?
    4.If u32Width is 0, set full screen width.(HD:1920,SD:720).
    5.If u32Height is 0, set full screen height.(HD:1080,SD:576).
    6.TODO 没有channel 参数
    7.TODO 没有channel 参数
    8.If iframe displayed on the video layer, the parameters are useful for iframe, if iframe displayed on other layer, set parameters to other layer.
    9.The parameters is used to clip video window.
    10.If the parameters are over range, HDI  should auto correct them to valid range.
    CNcomment:对于支持或操作的通道约定如下:
    1. 如果参数为或类型,只要有一个类型是支持的类型,返回成功.
        比如标清平台,当参数是:AV_CHANNEL_HD|AV_CHANNEL_SD 时, 返回成功.
    2. 如果参数不是或类型而且参数和平台支持类型不匹配,返回ERROR_FEATURE_NOT_SUPPORTED.
        比如标清平台,当参数是AV_CHANNEL_HD 时,返回ERROR_FEATURE_NOT_SUPPORTED.CNend
    3. 高清坐标以1080I为准, 标清坐标以PAL制为准.
        如果当前制式HD 不是1080I, SD 不是PAL,那么HDI负责把坐标转换成当前制式的坐标.
    4. 宽度为零则是全屏宽度.(HD:1920,SD:720)
    5. 高度为零则是全屏高度(HD:1080,SD:576)
    6. channel 可以单独操作一个通道,也可以或操作,
    7. 如果channel=AV_CHANNEL_HD |    AV_CHANNEL_SD, 则
        传入的参数是设置高清通道的输入窗口的大小,(以1080I为准).
        标清通道HDI 负责根据当前制式自动按比例调整.
    8. 如果iframe在video层,此函数对iframe同样起作用,对于iframe在其他层的情况，需要对所在进行层操作
    9. 主要用于视频窗口裁减
    10. 如果坐标和窗口大小参数超出范围,HDI自动修正到合理范围.    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] s32Left X coordinate of window top left corner.CNcomment:窗口左上角X坐标 CNend
    \param[in] s32Top Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[in] u32Width Window width.CNcomment:窗口宽度 CNend
    \param[in] u32Height Window height.CNcomment:窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_input_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                      AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get window input size. CNcomment:获取视频输入窗口的大小CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:返回窗口左上角X坐标 CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[out] pu32Width Return window width.CNcomment:返回窗口宽度 CNend
    \param[out] pu32Height Return window height.CNcomment:返回窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_input_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                      AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Set video output window size. CNcomment:设置视频输出窗口的大小CNend
    \attention \n

    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] s32Left Return X coordinate of window top left corner.CNcomment:窗口左上角X坐标 CNend
    \param[in] s32Top Return Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[in] pu32Width Return window width.CNcomment:窗口宽度 CNend
    \param[in] pu32Height Return window height.CNcomment:窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_output_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get vieo output window size. CNcomment:获取视频输出窗口的大小CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:返回窗口左上角X坐标 CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[out] pu32Width Return window width.CNcomment:返回窗口宽度 CNend
    \param[out] pu32Height Return window height.CNcomment:返回窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_output_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Set video content window size. CNcomment:设置视频内容窗口的大小CNend
    \attention \n
    Video content window in the video output window, include video display effective area, does not include the black side,
    in some platform,  video content  window is equivalent to the video output window
    CNcomment: 视频内容窗口指在视频输出窗口内除去黑边外的显示视频有效内容的区域，
                        有些平台视频内容窗口等同于视频输出窗口CNend
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] s32Left Return X coordinate of window top left corner.CNcomment:窗口左上角X坐标 CNend
    \param[in] s32Top Return Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[in] pu32Width Return window width.CNcomment:窗口宽度 CNend
    \param[in] pu32Height Return window height.CNcomment:窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_video_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get window output size. CNcomment:获取视频内容窗口的大小CNend
    \attention \n
    Video content window in the video output window, include video display effective area, does not include the black side,
    in some platform,  video content  window is equivalent to the video output window
    CNcomment: 视频内容窗口指在视频输出窗口内除去黑边外的显示视频有效内容的区域，
                        有些平台视频内容窗口等同于视频输出窗口CNend
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:返回窗口左上角X坐标 CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:窗口左上角Y坐标 CNend
    \param[out] pu32Width Return window width.CNcomment:返回窗口宽度 CNend
    \param[out] pu32Height Return window height.CNcomment:返回窗口高度 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_video_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Get window status. CNcomment:获取视频窗口状态CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] pstStatus Return status of window.CNcomment:返回窗口状态 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_status)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_STATUS_S* const  pstStatus);

    /**
    \brief Freeze the video on a Window. CNcomment:冻结视频CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_freeze)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief UnFreeze the video on a Window. CNcomment:恢复冻结的视频播放CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_unfreeze)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Freeze/unfreeze the video on a window with mode. CNcomment:冻结/解除视频窗口CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] bFreezeEnable whether to freeze window.CNcomment:使能/禁止标志 CNend
    \param[in] enFreezeMode the mode of freeze.CNcomment:冻结的方式 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_freeze_ex)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bFreezeEnable, VOUT_WINDOW_STOP_MODE_E enFreezeMode);

    /**
    \brief pause the video on a window. CNcomment:暂停视频窗口CNend
    \attention \n
    pause与freeze的区别在于:pause暂停屏幕显示和缓存，freeze只冻结屏幕显示。
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] enPauseMode the mode of freeze.CNcomment:暂停的方式 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_pause)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_STOP_MODE_E enPauseMode);

    /**
    \brief resume the video on a window. CNcomment:恢复视频窗口显示CNend
    \attention \n
    vout_window_resume与vout_window_pause配对使用。
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_resume)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Set mute of video window. CNcomment:关闭窗口输出CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_mute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Set unmute of video window. CNcomment:打开窗口输出CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_unmute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Attach the window with video source. CNcomment:将窗口与视频源绑定CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] hSource Video source handle.CNcomment:视频源句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_attach_input)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const HANDLE hSource);

    /**
    \brief Detach the window with video source. CNcomment:将窗口与视频源解绑定CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] hSource Video source handle.CNcomment:视频源句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_detach_input)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const HANDLE hSource);

    /**
    \brief Set backgroud color when window has been muted. CNcomment:设置窗口输出关闭后的背景颜色CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] pstRGBColorpstRGBColor: video mute color of video window.
                   pstRGBColor->u32Blue: actually use BIT[1~0];
                   pstRGBColor->u32Green: actually use BIT[2~0];
                   pstRGBColor->u32Red: actually use BIT[2~0];
                   CNcomment:窗口输出关闭后的背景颜色 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_mute_color)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_RGB_COLOR_S* pstRGBColor);

    /**
    \brief Enabe /disable  Film mode. CNcomment:打开或关闭电影模式CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] bEnable TRUE: enable film mode, FALSE, disable film mode.CNcomment:TRUE: 打开电影模式, FALSE, 关闭电影模式CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_enable_filmmode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bEnable);

    /**
    \brief Set Color temerature of a Window. CNcomment:设置窗口的色温CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] pstColorTemperature Color temerature data.CNcomment:色温数据CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_WIN_NOT_CREATED  Window has not been created.CNcomment:窗口未创建。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_colortemperature)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_COLOR_TEMPERATURE_S* pstColorTemperature);

    /**
    \brief Set zorder of video window. CNcomment:设置窗口的上下顺序CNend
    \attention \n
    if u32ZOrderIndex > current zorder move forward, else zorder move backward。
    CNcomment:如果参数u32ZOrderIndex 大于窗口目前顺序，则窗口忘上移动，否则往下移动 CNend
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] u32ZOrderIndex  ZOrder of video window.CNcomment:窗口的上下顺序CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_zorder)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 u32ZOrderIndex);

    /**
    \brief Set window mode panorama. CNcomment:设置全景模式CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] bEnable: TRUE, enable panorama.  FALSE,not use panorama.CNcomment:TRUE: 使能，FALSE:取消使能CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_enable_panorama)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bEnable);

    /**
    \brief Send video frame to display. CNcomment:视频帧送显示CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] pstFrameInfo: video frame info.CNcomment:视频帧信息CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::ERROR_VO_WIN_BUFQUE_FULL bufque full.CNcomment:帧队列已满。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_queue_frame)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_FRAME_INFO_S *pstFrameInfo);

    /**
    \brief Get back video display frame. CNcomment:回收视频显示帧CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] u32TimeOut: time out.CNcomment:超时值，在超时范围内等待可回收的显示帧CNend
    \param[out] pstFrameInfo: can get back video frame info.CNcomment:可回收的视频帧信息CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error, such as timeout.CNcomment:其它错误，包括超时等 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_dequeue_frame)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_FRAME_INFO_S *pstFrameInfo, U32 u32TimeOut);

    /**
    \brief Window switch mode. CNcomment:窗口切换模式CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] enWindowSwitchMode: window switch mode.CNcomment:窗口切换模式CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_reset)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_SWITCH_MODE_E enWindowSwitchMode);

   /**
    \brief Window switch mode. CNcomment:获取虚拟窗口宽高CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] uVirtualScreenW: window width.CNcomment:窗口宽
    \param[out] uVirtualScreenH: window width.CNcomment:窗口高
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_virtual_size)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 *const uVirtualScreenW, U32 *const uVirtualScreenH);

    /**
    \brief Get current play information of window. CNcomment:获取窗口当前的播放信息
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] u32DelayTime: window width.CNcomment:当前最新一帧还有多久会显示
    \param[out] u32DispRate: window width.CNcomment:显示帧率
    \param[out] u32FrameNumInBufQn: window width.CNcomment:window队列里有几帧
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_playinfo)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 *const u32DelayTime, U32 *const u32DispRate, U32 *const u32FrameNumInBufQn);

    /**
    \brief set the work mode of window: quick output or not. CNcomment:设置窗口是否工作在快速输出模式
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] bQuickOutputEnable whether determine the quick output mode of window.CNcomment:快速输出模式使能/禁止标志 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_quick_output_mode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bQuickOutputEnable);

    /**
    \brief get the work mode of window: quick output or not. CNcomment:获取窗口是否工作在快速输出模式
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[out] pbQuickOutputEnable whether determine the output mode of window.CNcomment:指针类型，指向快速输出模式使能/禁止标志 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_quick_output_mode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL* pbQuickOutputEnable);

    /**
     \brief Get the delay time of current frame, unit: ms.CNcomment:当前最新一帧还有多久会显示，单位: ms
     \attention \n
     \param[in] hVoutWindow window handle.CNcomment:window 句柄 CNend
     \param[out] pu32Latency Return the delay time of current frame.CNcomment:返回当前最新一帧还有多久会显示 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*vout_window_get_latency)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32* pu32Latency);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Window close HDR path. CNcomment:关闭HDR通路
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:窗口句柄 CNend
    \param[in] bCloseHdrPath: close HDR path or not:是否关闭HDR通路
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_close_hdr_path)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bCloseHdrPath);

    /**
    \brief vout invoke function, extend other function by user.
    CNcomment:invoke 扩展接口，用于用户私有功能扩展
    \attention \n
    None
    \param[in] hInvokeHandle the handle of Invoke Command, vout handle or window handle.CNcomment:Invloke命令需要的句柄，vout句柄或窗口句柄 CNend
    \param[in] eCmd Invoke ID, defined is ::VOUT_INVOKE_E.CNcomment:Invoke ID, 定义详见 ::VOUT_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:命令参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::VOUT_INVOKE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_invoke)(struct _VOUT_DEVICE_S* pstDev, const HANDLE hInvokeHandle, VOUT_INVOKE_E eCmd, VOID* pArg);

#endif
} VOUT_DEVICE_S;

/**
\brief direct get vout device api, for linux and android.CNcomment:获取视频输出设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get vout device api，for linux and andorid.
CNcomment:获取视频输出设备接口，linux和android平台都可以使用. CNend
\retval  vout device pointer when success.CNcomment:成功返回vout设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::VOUT_DEVICE_S

\par example
*/
VOUT_DEVICE_S* getVoutDevice();

/**
\brief  Open HAL Video output module device.CNcomment:打开HAL视频输出模块设备CNend
\attention \n
Open HAL Video output module device(for compatible Android HAL).
CNcomment:打开HAL视频输出模块设备(为兼容android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice Video output device structure.CNcomment:视频输出设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other system error.CNcomment:其它视频输出错误 CNend
\see \n
::VOUT_DEVICE_S

\par example
*/
static inline int vout_open(const struct hw_module_t* pstModule, VOUT_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, VOUT_HARDWARE_VOUT0, (struct hw_device_t**) ppstDevice);
#else
   *ppstDevice = getVoutDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL Video output module device.CNcomment:关闭HAL视频输出模块设备 CNend
\attention \n
Close HAL Video output module device(for compatible android HAL).
CNcomment:关闭HAL视频输出模块设备(为兼容android HAL结构). CNend
\param[in] pstDevice Video output device structure.CNcomment:视频输出设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::VOUT_DEVICE_S

\par example
*/
static inline int vout_close(VOUT_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__TVOS_HAL_VOUT_H__*/

