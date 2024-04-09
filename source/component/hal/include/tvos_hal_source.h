/**
 * \file
 * \brief Describes the information about the source module.
 */

#ifndef __TVOS_HAL_SOURCE_H__
#define __TVOS_HAL_SOURCE_H__

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
/** \addtogroup     HAL_SOURCE */
/** @{ */  /** <!-- [HAL_SOURCE] */

/**Module id define.*//** CNcomment:模块ID 定义 */
#define SOURCE_HARDWARE_MODULE_ID    "source"

/**Device name define .*//** CNcomment:设备名称定义 */
#define SOURCE_HARDWARE_SOURCE0      "source0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SOURCE */
/** @{ */  /** <!-- [HAL_SOURCE] */

/**source init param *//** CNcomment:输入源模块初始化参数 */
typedef struct _SOURCE_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} SOURCE_INIT_PARAMS_S;

/**source id *//** CNcomment:输入源ID */
typedef enum _SOURCE_ID_E
{
    SOURCE_ID_ATV = 0,  /**<ATV *//**<CNcomment:ATV*/

    SOURCE_ID_CVBS1,    /**<CVBS1 *//**<CNcomment:CVBS1*/
    SOURCE_ID_CVBS2,    /**<CVBS2 *//**<CNcomment:CVBS2*/
    SOURCE_ID_CVBS3,    /**<CVBS3 *//**<CNcomment:CVBS3*/

    SOURCE_ID_VGA,      /**<VGA *//**<CNcomment:VGA*/

    SOURCE_ID_YPBPR1,   /**<YPBPR1 *//**<CNcomment:YPBPR1*/
    SOURCE_ID_YPBPR2,   /**<YPBPR2 *//**<CNcomment:YPBPR2*/
    SOURCE_ID_YPBPR3,   /**<YPBPR3 *//**<CNcomment:YPBPR3*/

    SOURCE_ID_HDMI1,    /**<HDMI1 *//**<CNcomment:HDMI1*/
    SOURCE_ID_HDMI2,    /**<HDMI2 *//**<CNcomment:HDMI2*/
    SOURCE_ID_HDMI3,    /**<HDMI3 *//**<CNcomment:HDMI3*/
    SOURCE_ID_HDMI4,    /**<HDMI4 *//**<CNcomment:HDMI4*/

    SOURCE_ID_SCART,    /**<SCART *//**<CNcomment:SCART*/
    SOURCE_ID_DTV,      /**<DTV *//**<CNcomment:DTV*/
    SOURCE_ID_MEDIA,    /**<MEDIA *//**<CNcomment:MEDIA*/
    SOURCE_ID_EXT,      /**<EXT *//**<CNcomment:EXT*/
    SOURCE_ID_BUTT
} SOURCE_ID_E;

/**source create param *//** CNcomment:输入源创建参数 */
typedef struct _SOURCE_CREATE_PARAMS_S
{
    SOURCE_ID_E enSourceId; /**<Source ID *//**<CNcomment:输入源ID*/
} SOURCE_CREATE_PARAMS_S;

/**source destroy param *//** CNcomment:输入源销毁参数 */
typedef struct _SOURCE_DESTORY_PARAMS_S
{
    U32 u32Dummy;           /**<Reserve *//**<CNcomment:保留*/
} SOURCE_DESTORY_PARAMS_S;

/**source capability *//** CNcomment:输入源能力 */
typedef struct _SOURCE_CAPABILITY_S
{
    BOOL abIsSupported[SOURCE_ID_BUTT]; /**<source id support flag *//**<CNcomment:输入源ID支持标志*/
} SOURCE_CAPABILITY_S;

/**source capability *//** CNcomment:输入源能力 */
typedef enum _SOURCE_TVD_WORK_MODE_E
{
    SOURCE_TVD_WORK_MODE_NORMAL = 0,    /**<normal mode *//**<CNcomment: 正常工作模式*/
    SOURCE_TVD_WORK_MODE_CHAN_SCAN,     /**<TV search mode *//**<CNcomment: TV搜台模式*/
    SOURCE_TVD_WORK_MODE_BUTT,
} SOURCE_TVD_WORK_MODE_E;

/**source 3D format *//** CNcomment:3D格式 */
typedef enum _SOURCE_3D_FORMAT_E
{
    SOURCE_3D_FORMAT_OFF = 0,     /**<3D off: 2D *//**<CNcomment:关闭3D，2D模式*/
    SOURCE_3D_FORMAT_2DT3D,       /**<2D to 3D *//**<CNcomment:2D转3D*/
    SOURCE_3D_FORMAT_SBS,         /**<Side By Side *//**<CNcomment:Side By Side*/
    SOURCE_3D_FORMAT_TAB,         /**<Top And Bottom *//**<CNcomment:Top And Bottom*/
    SOURCE_3D_FORMAT_FP,          /**<frame paking: *//**<CNcomment:frame paking:*/
    SOURCE_3D_FORMAT_LI,          /**<Line Interlace *//**<CNcomment:Line Interlace*/
    SOURCE_3D_FORMAT_FA,          /**<frame alternative *//**<CNcomment:frame alternative*/
    SOURCE_3D_FORMAT_AUTO,        /**<Auto *//**<CNcomment自动按检测的模式进行播放*/
    SOURCE_3DMODE_BUTT
} SOURCE_3D_FORMAT_E;

/**display mode *//** CNcomment:显示模式 */
typedef enum _SOURCE_GRAPHIC_MODE_E
{
    SOURCE_GRAPHIC_MODE_PC = 0,   /**<display on graphic mode *//**<CNcomment:图形模式*/
    SOURCE_GRAPHIC_MODE_VIDEO,    /**<display on video mode *//**<CNcomment:视频模式*/
    SOURCE_GRAPHIC_MODE_GAME,     /**<display on game mode *//**<CNcomment:游戏模式*/
    SOURCE_GRAPHIC_MODE_AUTO,     /**<display auto *//**<CNcomment:自动模式*/
    SOURCE_GRAPHIC_MODE_BUTT,
} SOURCE_GRAPHIC_MODE_E;

/**source param *//** CNcomment:输入源参数 */
typedef struct _SOURCE_PARAMS_S
{
    SOURCE_TVD_WORK_MODE_E enTvdWorkMode;           /**<TVD work mode *//**<CNcomment:TVD工作模式*/
    SOURCE_3D_FORMAT_E enSource3dFormat;            /**<3D format *//**<CNcomment:3D格式*/
    SOURCE_GRAPHIC_MODE_E enSourceGraphicMode;      /**<display mode *//**<CNcomment:显示模式*/
} SOURCE_PARAMS_S;

/**source deinit param *//** CNcomment:模块去初始化参数  */
typedef struct _SOURCE_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:保留*/
} SOURCE_TERM_PARAMS_S;

/**source signal status *//** CNcomment:输入源信号状态  */
typedef enum _SOURCE_SIGNAL_STATUS_E
{
    SOURCE_SIGNAL_SUPPORT = 0,      /**<supported signal *//**<CNcomment:正常支持的信号*/
    SOURCE_SIGNAL_NOSIGNAL,         /**<no signal *//**<CNcomment:无信号*/
    SOURCE_SIGNAL_UNSUPPORT,        /**<unsupport signal *//**<CNcomment:不支持的信号*/
    SOURCE_SIGNAL_UNSTABLE,         /**<unstable signal *//**<CNcomment:不稳定的信号*/
    SOURCE_SIGNAL_BUTT,
} SOURCE_SIGNAL_STATUS_E;

/**source color space *//** CNcomment:输入源色彩空间  */
typedef enum _SOURCE_COLOR_SPACE_E
{
    SOURCE_COLOR_SPACE_UNKNOWN             = 0,           /**<unknown *//**<CNcomment:无法确定*/
    SOURCE_COLOR_SPACE_BT601_YUV_LIMITED   = 0x10,        /**<BT.601 YUV_LIMITED *//**<CNcomment:BT601 YUV_LIMITED*/
    SOURCE_COLOR_SPACE_BT601_YUV_FULL,                    /**<BT.601 YUV_FULL *//**<CNcomment:BT601 YUV_FULL*/
    SOURCE_COLOR_SPACE_BT601_RGB_LIMITED,                 /**<BT.601 RGB_LIMITED *//**<CNcomment:BT601 RGB_LIMITED*/
    SOURCE_COLOR_SPACE_BT601_RGB_FULL,                    /**<BT.601 RGB_FULL *//**<CNcomment:BT601 RGB_FULL*/
    SOURCE_COLOR_SPACE_NTSC1953            = 0x20,        /**<NTSC1953 *//**<CNcomment:NTSC1953*/
    SOURCE_COLOR_SPACE_BT470_SYSTEM_M      = 0x30,        /**<BT470 SYSTEM_M*//**<CNcomment:BT470 SYSTEM_M*/
    SOURCE_COLOR_SPACE_BT470_SYSTEM_BG,                   /**<BT470 SYSTEM_BG*//**<CNcomment:BT470 SYSTEM_BG*/
    SOURCE_COLOR_SPACE_BT709_YUV_LIMITED   = 0x40,        /**<BT709 YUV_LIMITED*//**<CNcomment:BT709 YUV_LIMITED*/
    SOURCE_COLOR_SPACE_BT709_YUV_FULL,                    /**<BT709 YUV_FULL*//**<CNcomment:BT709 YUV_FULL*/
    SOURCE_COLOR_SPACE_BT709_RGB_LIMITED,                 /**<BT709 RGB_LIMITED*//**<CNcomment:BT709 RGB_LIMITED*/
    SOURCE_COLOR_SPACE_BT709_RGB_FULL,                    /**<BT709 RGB_FULL*//**<CNcomment:BT709 RGB_FULL*/
    SOURCE_COLOR_SPACE_REC709              = 0x50,        /**<REC709*//**<CNcomment:REC709*/
    SOURCE_COLOR_SPACE_SMPT170M            = 0x60,        /**<SMPT170M*//**<CNcomment:SMPT170M*/
    SOURCE_COLOR_SPACE_SMPT240M,                          /**<SMPT240M*//**<CNcomment:SMPT240M*/
    SOURCE_COLOR_SPACE_BT878               = 0x70,        /**<BT878*//**<CNcomment:BT878*/
    SOURCE_COLOR_SPACE_XVYCC               = 0x80,        /**<XVYCC*//**<CNcomment:XVYCC*/
    SOURCE_COLOR_SPACE_JPEG                = 0x90,        /**<JPEG*//**<CNcomment:JPEG*/
    SOURCE_COLOR_SPACE_RGB                 = 0xa0,        /**<RGB*//**<CNcomment:RGB*/
    SOURCE_COLOR_SPACE_BUTT,
} SOURCE_COLOR_SPACE_E;

/**source 色彩系统 *//** CNcomment:输入源色彩系统  */
typedef enum _SOURCE_COLOR_SYS_E
{
    SOURCE_COLOR_SYS_AUTO = 0,       /**<auto *//**<CNcomment:自动判断*/
    SOURCE_COLOR_SYS_PAL,            /**<PAL *//**<CNcomment:PAL*/
    SOURCE_COLOR_SYS_NTSC,           /**<NTSC *//**<CNcomment:NTSC*/
    SOURCE_COLOR_SYS_SECAM,          /**<SECAM *//**<CNcomment:SECAM*/
    SOURCE_COLOR_SYS_PALM,           /**<PALM *//**<CNcomment:PALM*/
    SOURCE_COLOR_SYS_PALN,           /**<PALN *//**<CNcomment:PALN*/
    SOURCE_COLOR_SYS_PAL60,          /**<PAL60 *//**<CNcomment:PAL60*/
    SOURCE_COLOR_SYS_NTSC443,        /**<NTSC443 *//**<CNcomment:NTSC443*/
    SOURCE_COLOR_SYS_NTSC50,         /**<NTSC50 *//**<CNcomment:NTSC50*/
    SOURCE_COLOR_SYS_BUTT,
} SOURCE_COLOR_SYS_E;

/**source HDMI格式*//** CNcomment:输入源HDMI格式  */
typedef enum _SOURCE_HDMI_FORMAT_E
{
    SOURCE_HDMI_FORMAT_HDMI = 0,     /**<HDMI *//**<CNcomment:HDMI*/
    SOURCE_HDMI_FORMAT_DVI,          /**<DVI *//**<CNcomment:DVI*/
    SOURCE_HDMI_FORMAT_MHL,          /**<MHL *//**<CNcomment:MHL*/
    SOURCE_HDMI_FORMAT_BUTT
} SOURCE_HDMI_FORMAT_E;

/**source timing info*//** CNcomment:输入源timing信息  */
typedef struct _SOURCE_TIMING_INFO_S
{
    U32                   u32TimingIndex;             /**<Timing index *//**<CNcomment:Timing的序号 VGA Atuo adjust*/
    U32                   u32Width;                   /**<Graphic Width *//**<CNcomment:图像宽度*/
    U32                   u32Height;                  /**<Graphic Height *//**<CNcomment:图像高度，P制与I制都为帧图像高度*/
    U32                   u32FrameRate;               /**<frame rate *//**<CNcomment:P制为输入帧频，I制为输入场频*/
    SOURCE_COLOR_SPACE_E  enColorSpace;               /**<color space *//**<CNcomment:色彩空间*/
    BOOL                  bInterlace;                 /**<Whether interlace *//**<CNcomment:是否隔行信号*/
    SOURCE_3D_FORMAT_E    en3dFormat;                 /**<3d format *//**<CNcomment:3D格式*/
    SOURCE_HDMI_FORMAT_E  enFormatHDMI;               /**<HDMI/DVI/MHL  *//**<CNcomment:HDMI/DVI/MHL */
    BOOL                  bGraphicMode;               /**<Whether graphic mode *//**<CNcomment:是否图形模式*/
} SOURCE_TIMING_INFO_S;

/**source calibration status*//** CNcomment:输入源校准状态  */
typedef enum _SOURCE_ADJSTAT_E
{
    SOURCE_ADJSTAT_BEGIN = 0,     /**<adjust state begin *//**<CNcomment:开始校准*/
    SOURCE_ADJSTAT_FINISH,        /**<adjust state finish *//**<CNcomment:校准完成*/
    SOURCE_ADJSTAT_TIMEOUT,       /**<adjust state timeout *//**<CNcomment:校准超时*/
    SOURCE_ADJSTAT_FAIL,          /**<adjust state failure *//**<CNcomment:校准失败*/
    SOURCE_ADJSTAT_BUTT
} SOURCE_ADJSTAT_E;

/**source calibration info*//** CNcomment:输入源校准信息  */
typedef struct _SOURCE_CALIBRATION_INFO_S
{
    U32  u32RedGain;             /**<red gain *//**<CNcomment:红色增益*/
    U32  u32GreenGain;           /**<green gain *//**<CNcomment:绿色增益*/
    U32  u32BlueGain;            /**<blue gain *//**<CNcomment:蓝色增益*/
    U32  u32RedOffset;           /**<red offset *//**<CNcomment:红色偏移*/
    U32  u32GreenOffset;         /**<green offset *//**<CNcomment:绿色偏移*/
    U32  u32BlueOffset;          /**<blue offset *//**<CNcomment:蓝色偏移*/
} SOURCE_CALIBRATION_INFO_S;

/**source HDDEC calibration*//** CNcomment:输入源HDDEC校准*/
typedef enum _SOURCE_HDDEC_ADJUST_E
{
    SOURCE_HDDEC_ADJUST_HPOS = 0,            /**<adjust hpos *//**<CNcomment:手动水平位置调整 */
    SOURCE_HDDEC_ADJUST_VPOS,                /**<adjust vpos *//**<CNcomment:手动垂直位置调整 */
    SOURCE_HDDEC_ADJUST_PHASE,               /**<adjust phase *//**<CNcomment:手动相位调整*/
    SOURCE_HDDEC_ADJUST_CLOCK,               /**<adjust clock *//**<CNcomment:手动时钟调整*/
    SOURCE_HDDEC_ADJUST_BUTT
} SOURCE_HDDEC_ADJUST_E;

/**range*//** CNcomment:范围*/
typedef struct _SOURCE_RANGE_S
{
    U32      u32Min;                         /**<range min *//**<CNcomment:下限*/
    U32      u32Max;                         /**<range max *//**<CNcomment:上限*/
} SOURCE_RANGE_S;

/**HDMI EDID*//** CNcomment:HDMI EDID*/
typedef enum _SOURCE_EDID_E
{
    SOURCE_EDID_HDMI_1_4 = 0,                /**<HDMI 1_4 *//**<CNcomment:HDMI 1_4*/
    SOURCE_EDID_HDMI_2_0,                    /**<HDMI 2_0 *//**<CNcomment:HDMI 2_0*/
    SOURCE_EDID_MHL_2_0,                     /**<MHL 2_0 *//**<CNcomment:MHL 2_0*/
    SOURCE_EDID_VGA,                         /**<VGA *//**<CNcomment:VGA*/
    SOURCE_EDID_BUTT,
} SOURCE_EDID_E;

/**HDCP*//** CNcomment:HDCP*/
typedef enum _SOURCE_HDCP_E
{
    SOURCE_HDCP_1_4 = 0,                     /**<HDCP 1_4 *//**<CNcomment:HDCP 1_4*/
    SOURCE_HDCP_2_0,                         /**<HDCP 2_0 *//**<CNcomment:HDCP 2_0*/
    SOURCE_HDCP_2_2,                         /**<HDCP 2_2 *//**<CNcomment:HDCP 2_2*/
    SOURCE_HDCP_BUTT,
} SOURCE_HDCP_E;

/**HDMI RX MHL RCP Key*//** CNcomment:HDMI RX RCP按键*/
typedef enum _SOURCE_HDMIRX_RCP_KEY_E
{
    SOURCE_HDMIRX_RCP_KEY_SELECT = 0,        /**<HDMI RX RCP KEY SELECT *//**<CNcomment:HDMI RX RCP选择键*/
    SOURCE_HDMIRX_RCP_KEY_UP,                /**<HDMI RX RCP KEY UP *//**<CNcomment:HDMI RX RCP上键*/
    SOURCE_HDMIRX_RCP_KEY_DOWN,              /**<HDMI RX RCP KEY DOWN *//**<CNcomment:HDMI RX RCP下键*/
    SOURCE_HDMIRX_RCP_KEY_LEFT,              /**<HDMI RX RCP KEY LEFT *//**<CNcomment:HDMI RX RCP左键*/
    SOURCE_HDMIRX_RCP_KEY_RIGHT,             /**<HDMI RX RCP KEY RIGHT *//**<CNcomment:HDMI RX RCP右键*/
    SOURCE_HDMIRX_RCP_KEY_ROOT_MENU,         /**<HDMI RX RCP KEY MENU *//**<CNcomment:HDMI RX RCP菜单键*/
    SOURCE_HDMIRX_RCP_KEY_EXIT,              /**<HDMI RX RCP KEY EXIT *//**<CNcomment:HDMI RX RCP退出键*/
    SOURCE_HDMIRX_RCP_KEY_BUTT,
} SOURCE_HDMIRX_RCP_KEY_E;

/**Audio SIF mode*//** CNcomment:音频伴音制式*/
typedef enum _SOURCE_AUDSYS_E
{
    SOURCE_AUDSYS_AUTO = 0x00,               /**<Audio SIF AUTO *//**<CNcomment:音频伴音制式AUTO*/
    SOURCE_AUDSYS_BG,                        /**<Audio SIF BG *//**<CNcomment:音频伴音制式BG*/
    SOURCE_AUDSYS_BG_A2,                     /**<Audio SIF BG A2 *//**<CNcomment:音频伴音制式BG A2*/
    SOURCE_AUDSYS_BG_NICAM,                  /**<Audio SIF BG NICAM*/ /**<CNcomment:音频伴音制式BG NICAM*/
    SOURCE_AUDSYS_I,                         /**<Audio SIF I *//**<CNcomment:音频伴音制式I*/
    SOURCE_AUDSYS_DK,                        /**<Audio SIF DK *//**<CNcomment:音频伴音制式DK*/
    SOURCE_AUDSYS_DK1_A2,                    /**<Audio SIF DK1_A2 *//**<CNcomment:音频伴音制式DK1 A2*/
    SOURCE_AUDSYS_DK2_A2,                    /**<Audio SIF DK2_A2 *//**<CNcomment:音频伴音制式DK2 A2*/
    SOURCE_AUDSYS_DK3_A2,                    /**<Audio SIF DK3_A2 *//**<CNcomment:音频伴音制式DK3 A2*/
    SOURCE_AUDSYS_DK_NICAM,                  /**<Audio SIF DK NICAM */ /**<CNcomment:音频伴音制式DK NICAM*/
    SOURCE_AUDSYS_L,                         /**<Audio SIF L */ /**<CNcomment:音频伴音制式L*/
    SOURCE_AUDSYS_M,                         /**<Audio SIF M*//**<CNcomment:音频伴音制式M*/
    SOURCE_AUDSYS_M_BTSC,                    /**<Audio SIF M_BTSC *//**<CNcomment:音频伴音制式M BTSC*/
    SOURCE_AUDSYS_M_A2,                      /**<Audio SIF M_A2 *//**<CNcomment:音频伴音制式M A2*/
    SOURCE_AUDSYS_M_EIA_J,                   /**<Audio SIF M_EIA_J */ /**<CNcomment:音频伴音制式M EIA J*/
    SOURCE_AUDSYS_BUTT
} SOURCE_AUDSYS_E;

/**SIF control param*//** CNcomment:自动制式检测控制参数*/
typedef enum _SOURCE_SIF_SYSCTL_E
{
    SOURCE_SIF_SYSCTL_BTSC = 0,              /**<SIF control param BTSC *//**<CNcomment: 音频制式检测控制BTSC,America M */
    SOURCE_SIF_SYSCTL_EIAJ,                  /**<SIF control param EIAJ *//**<CNcomment: 音频制式检测控制EIAJ,Japan M */
    SOURCE_SIF_SYSCTL_M_KOREA,               /**<SIF control param M_KOREA *//**<CNcomment: 音频制式检测控制FM Korea,Korea M */
    SOURCE_SIF_SYSCTL_PAL_SUM,               /**<SIF control param PAL_SUM *//**<CNcomment: 音频制式检测控制PAL */
    SOURCE_SIF_SYSCTL_SECAM_L,               /**<SIF control param SECAM_L *//**<CNcomment: 音频制式检测控制L/L' */
    SOURCE_SIF_SYSCTL_FM_US,                 /**<SIF control param FM_US *//**<CNcomment: 音频制式检测控制FM-Stereo Radio US */
    SOURCE_SIF_SYSCTL_FM_EUROPE,             /**<SIF control param FM_EUROPE *//**<CNcomment: 音频制式检测控制FM-Stereo Radio Europe' */
    SOURCE_SIF_SYSCTL_BUTT
} SOURCE_SIF_SYSCTL_E;

/**SIF mode*//** CNcomment:音频伴音模式*/
typedef enum _SOURCE_SIF_OUTMODE_E
{
    SOURCE_SIF_OUTMODE_MONO = 0x00,              /**<SIF Audio Mode MONO*//**<CNcomment:音频伴音模式MONO*/
    SOURCE_SIF_OUTMODE_STEREO,                   /**<SIF Audio Mode G Stereo*//**<CNcomment:音频伴音模式Stereo*/
    SOURCE_SIF_OUTMODE_DUAL_A,                   /**<SIF Audio Mode Dual A*//**<CNcomment:音频伴音模式DUAL_A*/
    SOURCE_SIF_OUTMODE_DUAL_B,                   /**<SIF Audio Mode Dual B*//**<CNcomment:音频伴音模式DUAL_B*/
    SOURCE_SIF_OUTMODE_DUAL_AB,                  /**<SIF Audio Mode Dual AB*//**<CNcomment:音频伴音模式DUAL_AB*/
    SOURCE_SIF_OUTMODE_BTSC_MONO,                /**<SIF Audio Mode BTSC MONO*//**<CNcomment:音频伴音模式BTSC_MONO*/
    SOURCE_SIF_OUTMODE_BTSC_STEREO,              /**<SIF Audio Mode BTSC STEREO*//**<CNcomment:音频伴音模式BTSC_STEREO*/
    SOURCE_SIF_OUTMODE_BTSC_SAP,                 /**<SIF Audio Mode BTSC SAP*//**<CNcomment:音频伴音模式BTSC_SAP*/
    SOURCE_SIF_OUTMODE_NICAM_FORCED_MONO,        /**<SIF Audio Mode NICAM Forced MONO*//**<CNcomment:音频伴音模式NICAM_FORCED_MONO*/
    SOURCE_SIF_OUTMODE_NICAM_MONO,               /**<SIF Audio Mode NICAM MONO*//**<CNcomment:音频伴音模式NICAM_MONO*/
    SOURCE_SIF_OUTMODE_NICAM_STEREO,             /**<SIF Audio Mode NICAM Stereo*//**<CNcomment:音频伴音模式NICAM_STEREO*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_A,             /**<SIF Audio Mode NICAM DUAL A*//**<CNcomment:音频伴音模式NICAM_DUAL_A*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_B,             /**<SIF Audio Mode NICAM DUAL B*//**<CNcomment:音频伴音模式NICAM_DUAL_B*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_AB,            /**<SIF Audio Mode NICAM DUAL AB*//**<CNcomment:音频伴音模式NICAM_DUAL_AB*/
    SOURCE_SIF_OUTMODE_BUTT
} SOURCE_SIF_OUTMODE_E;

/**SIF over devaiton*//** CNcomment:音频伴音过调制*/
typedef enum _SOURCE_SIF_OVER_DEVIATION_E
{
    SOURCE_SIF_OVER_DEVIATION_50K  = 0,          /**<Audio SIF over devaiton 50K */ /**<CNcomment:过调制 50K*/
    SOURCE_SIF_OVER_DEVIATION_100K,              /**<Audio SIF over devaiton 100K */ /**<CNcomment:过调制 100K*/
    SOURCE_SIF_OVER_DEVIATION_200K,              /**<Audio SIF over devaiton 200K */ /**<CNcomment:过调制 200K*/
    SOURCE_SIF_OVER_DEVIATION_384K,              /**<Audio SIF over devaiton 384K */ /**<CNcomment:过调制 384K*/
    SOURCE_SIF_OVER_DEVIATION_540K,              /**<Audio SIF over devaiton 500K */ /**<CNcomment:过调制 500K*/
    SOURCE_SIF_OVER_DEVIATION_BUTT
} SOURCE_SIF_OVER_DEVIATION_E;

#ifdef ANDROID_HAL_MODULE_USED
/**Source module structure(Android require) */
/**CNcomment:输入源模块结构(Android对接要求) */
typedef struct _SOURCE_MODULE_S
{
    struct hw_module_t stCommon;     /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
} SOURCE_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_SOURCE*/
/** @{*/  /** <!-- -[HAL_SOURCE]=*/

/**Source device structure*//** CNcomment:输入源设备结构*/
typedef struct _SOURCE_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif
    /**
    \brief Source  init.CNcomment:输入源模块初始化 CNend
    \attention \n
    Lower layer source module init and alloc necessary resource,  repeat call return success.
    CNcomment:底层输入源模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_SOURCE_INIT_FAILED  Lower layer source module init error.CNcomment:底层输入源模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_INIT_PARAMS_S

    \par example
    \code
    SOURCE_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(SOURCE_INIT_PARAMS_S));
    if (SUCCESS != source_init(pstDev, (const SOURCE_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*source_init)(struct _SOURCE_DEVICE_S* pstDev, const SOURCE_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Source  deinit.CNcomment:输入源模块去初始化 CNend
    \attention \n
    Lower layer source module deinit and release occupied resource,  repeat call return success.
    CNcomment:底层输入源模块去初始化及释放占用的资源, 本函数重复调用返回成功. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:去初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_SOURCE_DEINIT_FAILED  Lower layer source module deinit error.CNcomment:底层输入源模块去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_TERM_PARAMS_S

    \par example
    \code
    SOURCE_TERM_PARAMS_S stDeInitParam;
    memset(&stDeInitParam, 0x0, sizeof(SOURCE_TERM_PARAMS_S));
    if (SUCCESS != source_term(pstDev, (const SOURCE_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*source_term)(struct _SOURCE_DEVICE_S* pstDev, const SOURCE_TERM_PARAMS_S* const  pstTermParams);

    /**
    \brief Create video channel at specify source.CNcomment:基于特定的源创建视频通道 CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:创建参数 CNend
    \param[out] pSourceHandle generated handle.CNcomment:生成的句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_CREATE_PARAMS_S

    \par example
    */
    S32 (* source_create)(struct _SOURCE_DEVICE_S* pstDev, HANDLE* const pSourceHandle, SOURCE_CREATE_PARAMS_S* const pstCreateParams);

    /**
    \brief destory video channel used by input source.CNcomment:基于特定的源销毁视频通道 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] pstDestoryParams destory param.CNcomment:销毁参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_DESTORY_PARAMS_S

    \par example
    */
    S32 (* source_destory)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_DESTORY_PARAMS_S* const pstDestoryParams);

    /**
    \brief Get source module capability.CNcomment: 获取输入源模块设备能力CNend
    \attention \n
    \param[out] pstCapability source module capability.CNcomment:输入源模块设备能力CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_CAPABILITY_S

    \par example
    */
    S32 (* source_get_capability)(struct _SOURCE_DEVICE_S* pstDev, SOURCE_CAPABILITY_S* const pstCapability);

    /**
    \brief Get source params.CNcomment: 获取输入源参数CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] pstCreateParams source params.CNcomment:输入源参数CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_CAPABILITY_S

    \par example
    */
    S32 (* source_getParams)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_PARAMS_S* const pstCreateParams);

    /**
    \brief Set source params.CNcomment:设置输入源参数 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] pstSourceParams source param.CNcomment:输入源参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_PARAMS_S

    \par example
    */
    S32 (* source_setParams)(struct _SOURCE_DEVICE_S* pstDev,  const HANDLE hSource,  const SOURCE_PARAMS_S*   pstSourceParams);

    /**
    \brief video channel start play stream.CNcomment:启动输入源播放 CNend
    \attention \n
    must attach audio&video dest first .
    CNcomment:必须先与音视频目标绑定. CNend
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_start)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief video channel stop play stream.CNcomment:停止输入源播放 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_stop)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get input stream's signal state.CNcomment: 获取输入源信号状态CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] pStatus signal status.CNcomment:信号状态CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_SIGNAL_STATUS_E

    \par example
    */
    S32 (* source_getSignalState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIGNAL_STATUS_E* const pStatus);

    /**
    \brief get source timing infomation.CNcomment: 获取输入源timing信息CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] pstTimingInfo timing info.CNcomment:timing info CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_TIMING_INFO_S

    \par example
    */
    S32 (* source_getVideoInfo)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_TIMING_INFO_S* const pstTimingInfo);

    /**
    \brief set tvd color system.CNcomment:设置tvd色彩系统 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enColorSys tvd color system.CNcomment:tvd色彩系统 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_COLOR_SYS_E

    \par example
    */
    S32 (* source_setColorSys)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, const SOURCE_COLOR_SYS_E enColorSys);

    /**
    \brief get tvd color system.CNcomment:获取tvd色彩系统 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] penColorSys tvd color system.CNcomment:tvd色彩系统 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_COLOR_SYS_E

    \par example
    */
    S32 (* source_getColorSys)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_COLOR_SYS_E* const penColorSys);

    /**
    \brief get tvd  signal locked status.CNcomment:获取tvd信号锁定状态 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] pbSignalLock tvd signal locked status.CNcomment:tvd信号锁定状态 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_getSignalLock)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, BOOL* const pbSignalLock);

    /**
    \brief set sif standard.CNcomment:设置sif伴音制式 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enStandard sif standard.CNcomment:设置sif伴音制式 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_AUDSYS_E

    \par example
    */
    S32 (*source_setStandard)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_AUDSYS_E enStandard);

    /**
    \brief get sif standard.CNcomment:获取sif伴音制式 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] penStandard sif standard.CNcomment:sif伴音制式 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_AUDSYS_E

    \par example
    */
    S32 (*source_getStandard)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_AUDSYS_E* penStandard);

    /**
    \brief set sif mode.CNcomment:设置sif伴音模式 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enOutmode sif mode.CNcomment:设置sif伴音模式  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_SIF_OUTMODE_E

    \par example
    */
    S32 (*source_setSndMode)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIF_OUTMODE_E enOutmode);

    /**
    \brief get sif mode.CNcomment:获取sif伴音模式 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] penOutmode sif mode.CNcomment:sif伴音模式  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_SIF_OUTMODE_E

    \par example
    */
    S32 (*source_getSndMode)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource_handle, SOURCE_SIF_OUTMODE_E* penOutmode);

    /**
    \brief set SIF over devaiton.CNcomment:设置音频过调制参数 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enOverDeviation SIF over devaiton.CNcomment:过调制参数  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_SIF_OVER_DEVIATION_E

    \par example
    */
    S32 (*source_setOverDeviation)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIF_OVER_DEVIATION_E enOverDeviation);

    /**
    \brief set SIF carri shift.CNcomment:设置音频频移 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] u32CarriShift SIF carri shift.CNcomment:音频频移   CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (*source_setCarriShift)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, U32 u32CarriShift);

    /**
    \brief start hddec calibration.CNcomment:启动HDDEC校准 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_startCalib)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get calibration state.CNcomment:获取HDDEC校准状态 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] penCalibrationState calibration state.CNcomment:HDDEC校准状态  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_ADJSTAT_E

    \par example
    */
    S32 (* source_getCalibState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_ADJSTAT_E* penCalibrationState);

    /**
    \brief get calibration result.CNcomment:获取HDDEC校准结果 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] pstCalibrationPara calibration result.CNcomment:HDDEC校准结果  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_CALIBRATION_INFO_S

    \par example
    */
    S32 (* source_getCalibPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_CALIBRATION_INFO_S* pstCalibrationPara);

    /**
    \brief set calibration para.CNcomment:设置HDDEC校准参数 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] stCalibrationPara calibration para.CNcomment:HDDEC校准参数CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_CALIBRATION_INFO_S

    \par example
    */
    S32 (* source_setCalibPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource,  SOURCE_CALIBRATION_INFO_S stCalibrationPara);

    /**
    \brief start vga auto adjust.CNcomment:启动vga自动调整 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_startAdjust)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get adjust state.CNcomment:获取vga调整状态 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[out] penAdjustState adjust state.CNcomment:vga调整状态  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_ADJSTAT_E

    \par example
    */
    S32 (* source_getAdjustState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_ADJSTAT_E* penAdjustState);

    /**
    \brief get vga adjust result .CNcomment:获取vga调整结果 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enAdjustItem adjust item.CNcomment:调整项 CNend
    \param[out] pu32ItemValue adjust value.CNcomment:vga调整值  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_HDDEC_ADJUST_E

    \par example
    */
    S32 (* source_getAdjustPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, U32* pu32ItemValue);

    /**
    \brief set vga adjust para.CNcomment:设置vga调整参数 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enAdjustItem adjust item.CNcomment:调整项 CNend
    \param[in] u32ItemValue adjust value.CNcomment:vga调整值  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_setAdjustPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, U32 u32ItemValue);

    /**
    \brief get vga adjust range.CNcomment:获取vga调整范围 CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enAdjustItem adjust item.CNcomment:调整项 CNend
    \param[out] pstRange adjust range.CNcomment:vga调整范围  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SOURCE_HDDEC_ADJUST_E

    \par example
    */
    S32 (* source_getAdjustRange)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, SOURCE_RANGE_S* pstRange);

    /**
    \brief send MHL RCP Key,only for hdmi.CNcomment:发送MHL RCP Key，仅支持HDMI CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enMhlRcpKey RCP Key value.CNcomment:RCP Key键值 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_sendMhlRcp)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDMIRX_RCP_KEY_E enMhlRcpKey);

    /**
    \brief set edid, only for hdmi & VGA.CNcomment:设置edid，仅支持HDMI和VGA  CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enEdidType Edid type.CNcomment:edid类型 CNend
    \param[in] u32Length Edid info length.CNcomment:edid信息长度 CNend
    \param[in] pData Edid info data.CNcomment:edid信息数据 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_updateEdid)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_EDID_E enEdidType, U32 u32Length, VOID* const pData);

    /**
    \brief set HDCP, only for hdmi.CNcomment:设置HDCP，仅支持HDMI  CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:输入源句柄 CNend
    \param[in] enHdcpType HDCP type.CNcomment:HDCP类型 CNend
    \param[in] u32Length HDCP info length.CNcomment:HDCP信息长度 CNend
    \param[in] pData HDCP info data.CNcomment:HDCP信息数据 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (* source_updateHdcp)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDCP_E enHdcpType, U32 u32Length, VOID* const pData);

} SOURCE_DEVICE_S;

/**
 \brief direct get input source device api, for linux and android.CNcomment:获取输入源设备的接口, Linux和Android平台都可以使用 CNend
 \attention \n
get source device api，for linux and andorid.
CNcomment:获取输入源设备接口，linux和android平台都可以使用. CNend
 \retval  source device pointer when success.CNcomment:成功返回source设备指针。CNend
 \retval ::NULL when failure.CNcomment:失败返回空指针 CNend
 \see \n
::SOURCE_DEVICE_S

 \par example
 */
SOURCE_DEVICE_S* getSourceDevice();

/**
\brief  Open HAL source module device.CNcomment:打开HAL输入源模块设备 CNend
\attention \n
Open HAL source module device(for compatible Android HAL).
CNcomment:打开HAL输入源模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice source device structure.CNcomment:输入源设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SOURCE_DEVICE_S

\par example
*/
static inline int source_open(const struct hw_module_t* pstModule, SOURCE_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SOURCE_HARDWARE_SOURCE0, (hw_device_t** )ppstDevice);
#else
     *ppstDevice = getSourceDevice();
    return SUCCESS;
#endif
}

/**
\brief  Close HAL source module device.CNcomment:关闭HAL输入源模块设备 CNend
\attention \n
Close HAL source module device(for compatible Android HAL).
CNcomment:关闭HAL输入源模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice source device structure.CNcomment:输入源设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SOURCE_DEVICE_S

\par example
*/
static inline int source_close(SOURCE_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_SOURCE_H__ */

/* EOF */

