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

/**Module id define.*//** CNcomment:ģ��ID ���� */
#define SOURCE_HARDWARE_MODULE_ID    "source"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define SOURCE_HARDWARE_SOURCE0      "source0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SOURCE */
/** @{ */  /** <!-- [HAL_SOURCE] */

/**source init param *//** CNcomment:����Դģ���ʼ������ */
typedef struct _SOURCE_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} SOURCE_INIT_PARAMS_S;

/**source id *//** CNcomment:����ԴID */
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

/**source create param *//** CNcomment:����Դ�������� */
typedef struct _SOURCE_CREATE_PARAMS_S
{
    SOURCE_ID_E enSourceId; /**<Source ID *//**<CNcomment:����ԴID*/
} SOURCE_CREATE_PARAMS_S;

/**source destroy param *//** CNcomment:����Դ���ٲ��� */
typedef struct _SOURCE_DESTORY_PARAMS_S
{
    U32 u32Dummy;           /**<Reserve *//**<CNcomment:����*/
} SOURCE_DESTORY_PARAMS_S;

/**source capability *//** CNcomment:����Դ���� */
typedef struct _SOURCE_CAPABILITY_S
{
    BOOL abIsSupported[SOURCE_ID_BUTT]; /**<source id support flag *//**<CNcomment:����ԴID֧�ֱ�־*/
} SOURCE_CAPABILITY_S;

/**source capability *//** CNcomment:����Դ���� */
typedef enum _SOURCE_TVD_WORK_MODE_E
{
    SOURCE_TVD_WORK_MODE_NORMAL = 0,    /**<normal mode *//**<CNcomment: ��������ģʽ*/
    SOURCE_TVD_WORK_MODE_CHAN_SCAN,     /**<TV search mode *//**<CNcomment: TV��̨ģʽ*/
    SOURCE_TVD_WORK_MODE_BUTT,
} SOURCE_TVD_WORK_MODE_E;

/**source 3D format *//** CNcomment:3D��ʽ */
typedef enum _SOURCE_3D_FORMAT_E
{
    SOURCE_3D_FORMAT_OFF = 0,     /**<3D off: 2D *//**<CNcomment:�ر�3D��2Dģʽ*/
    SOURCE_3D_FORMAT_2DT3D,       /**<2D to 3D *//**<CNcomment:2Dת3D*/
    SOURCE_3D_FORMAT_SBS,         /**<Side By Side *//**<CNcomment:Side By Side*/
    SOURCE_3D_FORMAT_TAB,         /**<Top And Bottom *//**<CNcomment:Top And Bottom*/
    SOURCE_3D_FORMAT_FP,          /**<frame paking: *//**<CNcomment:frame paking:*/
    SOURCE_3D_FORMAT_LI,          /**<Line Interlace *//**<CNcomment:Line Interlace*/
    SOURCE_3D_FORMAT_FA,          /**<frame alternative *//**<CNcomment:frame alternative*/
    SOURCE_3D_FORMAT_AUTO,        /**<Auto *//**<CNcomment�Զ�������ģʽ���в���*/
    SOURCE_3DMODE_BUTT
} SOURCE_3D_FORMAT_E;

/**display mode *//** CNcomment:��ʾģʽ */
typedef enum _SOURCE_GRAPHIC_MODE_E
{
    SOURCE_GRAPHIC_MODE_PC = 0,   /**<display on graphic mode *//**<CNcomment:ͼ��ģʽ*/
    SOURCE_GRAPHIC_MODE_VIDEO,    /**<display on video mode *//**<CNcomment:��Ƶģʽ*/
    SOURCE_GRAPHIC_MODE_GAME,     /**<display on game mode *//**<CNcomment:��Ϸģʽ*/
    SOURCE_GRAPHIC_MODE_AUTO,     /**<display auto *//**<CNcomment:�Զ�ģʽ*/
    SOURCE_GRAPHIC_MODE_BUTT,
} SOURCE_GRAPHIC_MODE_E;

/**source param *//** CNcomment:����Դ���� */
typedef struct _SOURCE_PARAMS_S
{
    SOURCE_TVD_WORK_MODE_E enTvdWorkMode;           /**<TVD work mode *//**<CNcomment:TVD����ģʽ*/
    SOURCE_3D_FORMAT_E enSource3dFormat;            /**<3D format *//**<CNcomment:3D��ʽ*/
    SOURCE_GRAPHIC_MODE_E enSourceGraphicMode;      /**<display mode *//**<CNcomment:��ʾģʽ*/
} SOURCE_PARAMS_S;

/**source deinit param *//** CNcomment:ģ��ȥ��ʼ������  */
typedef struct _SOURCE_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:����*/
} SOURCE_TERM_PARAMS_S;

/**source signal status *//** CNcomment:����Դ�ź�״̬  */
typedef enum _SOURCE_SIGNAL_STATUS_E
{
    SOURCE_SIGNAL_SUPPORT = 0,      /**<supported signal *//**<CNcomment:����֧�ֵ��ź�*/
    SOURCE_SIGNAL_NOSIGNAL,         /**<no signal *//**<CNcomment:���ź�*/
    SOURCE_SIGNAL_UNSUPPORT,        /**<unsupport signal *//**<CNcomment:��֧�ֵ��ź�*/
    SOURCE_SIGNAL_UNSTABLE,         /**<unstable signal *//**<CNcomment:���ȶ����ź�*/
    SOURCE_SIGNAL_BUTT,
} SOURCE_SIGNAL_STATUS_E;

/**source color space *//** CNcomment:����Դɫ�ʿռ�  */
typedef enum _SOURCE_COLOR_SPACE_E
{
    SOURCE_COLOR_SPACE_UNKNOWN             = 0,           /**<unknown *//**<CNcomment:�޷�ȷ��*/
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

/**source ɫ��ϵͳ *//** CNcomment:����Դɫ��ϵͳ  */
typedef enum _SOURCE_COLOR_SYS_E
{
    SOURCE_COLOR_SYS_AUTO = 0,       /**<auto *//**<CNcomment:�Զ��ж�*/
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

/**source HDMI��ʽ*//** CNcomment:����ԴHDMI��ʽ  */
typedef enum _SOURCE_HDMI_FORMAT_E
{
    SOURCE_HDMI_FORMAT_HDMI = 0,     /**<HDMI *//**<CNcomment:HDMI*/
    SOURCE_HDMI_FORMAT_DVI,          /**<DVI *//**<CNcomment:DVI*/
    SOURCE_HDMI_FORMAT_MHL,          /**<MHL *//**<CNcomment:MHL*/
    SOURCE_HDMI_FORMAT_BUTT
} SOURCE_HDMI_FORMAT_E;

/**source timing info*//** CNcomment:����Դtiming��Ϣ  */
typedef struct _SOURCE_TIMING_INFO_S
{
    U32                   u32TimingIndex;             /**<Timing index *//**<CNcomment:Timing����� VGA Atuo adjust*/
    U32                   u32Width;                   /**<Graphic Width *//**<CNcomment:ͼ����*/
    U32                   u32Height;                  /**<Graphic Height *//**<CNcomment:ͼ��߶ȣ�P����I�ƶ�Ϊ֡ͼ��߶�*/
    U32                   u32FrameRate;               /**<frame rate *//**<CNcomment:P��Ϊ����֡Ƶ��I��Ϊ���볡Ƶ*/
    SOURCE_COLOR_SPACE_E  enColorSpace;               /**<color space *//**<CNcomment:ɫ�ʿռ�*/
    BOOL                  bInterlace;                 /**<Whether interlace *//**<CNcomment:�Ƿ�����ź�*/
    SOURCE_3D_FORMAT_E    en3dFormat;                 /**<3d format *//**<CNcomment:3D��ʽ*/
    SOURCE_HDMI_FORMAT_E  enFormatHDMI;               /**<HDMI/DVI/MHL  *//**<CNcomment:HDMI/DVI/MHL */
    BOOL                  bGraphicMode;               /**<Whether graphic mode *//**<CNcomment:�Ƿ�ͼ��ģʽ*/
} SOURCE_TIMING_INFO_S;

/**source calibration status*//** CNcomment:����ԴУ׼״̬  */
typedef enum _SOURCE_ADJSTAT_E
{
    SOURCE_ADJSTAT_BEGIN = 0,     /**<adjust state begin *//**<CNcomment:��ʼУ׼*/
    SOURCE_ADJSTAT_FINISH,        /**<adjust state finish *//**<CNcomment:У׼���*/
    SOURCE_ADJSTAT_TIMEOUT,       /**<adjust state timeout *//**<CNcomment:У׼��ʱ*/
    SOURCE_ADJSTAT_FAIL,          /**<adjust state failure *//**<CNcomment:У׼ʧ��*/
    SOURCE_ADJSTAT_BUTT
} SOURCE_ADJSTAT_E;

/**source calibration info*//** CNcomment:����ԴУ׼��Ϣ  */
typedef struct _SOURCE_CALIBRATION_INFO_S
{
    U32  u32RedGain;             /**<red gain *//**<CNcomment:��ɫ����*/
    U32  u32GreenGain;           /**<green gain *//**<CNcomment:��ɫ����*/
    U32  u32BlueGain;            /**<blue gain *//**<CNcomment:��ɫ����*/
    U32  u32RedOffset;           /**<red offset *//**<CNcomment:��ɫƫ��*/
    U32  u32GreenOffset;         /**<green offset *//**<CNcomment:��ɫƫ��*/
    U32  u32BlueOffset;          /**<blue offset *//**<CNcomment:��ɫƫ��*/
} SOURCE_CALIBRATION_INFO_S;

/**source HDDEC calibration*//** CNcomment:����ԴHDDECУ׼*/
typedef enum _SOURCE_HDDEC_ADJUST_E
{
    SOURCE_HDDEC_ADJUST_HPOS = 0,            /**<adjust hpos *//**<CNcomment:�ֶ�ˮƽλ�õ��� */
    SOURCE_HDDEC_ADJUST_VPOS,                /**<adjust vpos *//**<CNcomment:�ֶ���ֱλ�õ��� */
    SOURCE_HDDEC_ADJUST_PHASE,               /**<adjust phase *//**<CNcomment:�ֶ���λ����*/
    SOURCE_HDDEC_ADJUST_CLOCK,               /**<adjust clock *//**<CNcomment:�ֶ�ʱ�ӵ���*/
    SOURCE_HDDEC_ADJUST_BUTT
} SOURCE_HDDEC_ADJUST_E;

/**range*//** CNcomment:��Χ*/
typedef struct _SOURCE_RANGE_S
{
    U32      u32Min;                         /**<range min *//**<CNcomment:����*/
    U32      u32Max;                         /**<range max *//**<CNcomment:����*/
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

/**HDMI RX MHL RCP Key*//** CNcomment:HDMI RX RCP����*/
typedef enum _SOURCE_HDMIRX_RCP_KEY_E
{
    SOURCE_HDMIRX_RCP_KEY_SELECT = 0,        /**<HDMI RX RCP KEY SELECT *//**<CNcomment:HDMI RX RCPѡ���*/
    SOURCE_HDMIRX_RCP_KEY_UP,                /**<HDMI RX RCP KEY UP *//**<CNcomment:HDMI RX RCP�ϼ�*/
    SOURCE_HDMIRX_RCP_KEY_DOWN,              /**<HDMI RX RCP KEY DOWN *//**<CNcomment:HDMI RX RCP�¼�*/
    SOURCE_HDMIRX_RCP_KEY_LEFT,              /**<HDMI RX RCP KEY LEFT *//**<CNcomment:HDMI RX RCP���*/
    SOURCE_HDMIRX_RCP_KEY_RIGHT,             /**<HDMI RX RCP KEY RIGHT *//**<CNcomment:HDMI RX RCP�Ҽ�*/
    SOURCE_HDMIRX_RCP_KEY_ROOT_MENU,         /**<HDMI RX RCP KEY MENU *//**<CNcomment:HDMI RX RCP�˵���*/
    SOURCE_HDMIRX_RCP_KEY_EXIT,              /**<HDMI RX RCP KEY EXIT *//**<CNcomment:HDMI RX RCP�˳���*/
    SOURCE_HDMIRX_RCP_KEY_BUTT,
} SOURCE_HDMIRX_RCP_KEY_E;

/**Audio SIF mode*//** CNcomment:��Ƶ������ʽ*/
typedef enum _SOURCE_AUDSYS_E
{
    SOURCE_AUDSYS_AUTO = 0x00,               /**<Audio SIF AUTO *//**<CNcomment:��Ƶ������ʽAUTO*/
    SOURCE_AUDSYS_BG,                        /**<Audio SIF BG *//**<CNcomment:��Ƶ������ʽBG*/
    SOURCE_AUDSYS_BG_A2,                     /**<Audio SIF BG A2 *//**<CNcomment:��Ƶ������ʽBG A2*/
    SOURCE_AUDSYS_BG_NICAM,                  /**<Audio SIF BG NICAM*/ /**<CNcomment:��Ƶ������ʽBG NICAM*/
    SOURCE_AUDSYS_I,                         /**<Audio SIF I *//**<CNcomment:��Ƶ������ʽI*/
    SOURCE_AUDSYS_DK,                        /**<Audio SIF DK *//**<CNcomment:��Ƶ������ʽDK*/
    SOURCE_AUDSYS_DK1_A2,                    /**<Audio SIF DK1_A2 *//**<CNcomment:��Ƶ������ʽDK1 A2*/
    SOURCE_AUDSYS_DK2_A2,                    /**<Audio SIF DK2_A2 *//**<CNcomment:��Ƶ������ʽDK2 A2*/
    SOURCE_AUDSYS_DK3_A2,                    /**<Audio SIF DK3_A2 *//**<CNcomment:��Ƶ������ʽDK3 A2*/
    SOURCE_AUDSYS_DK_NICAM,                  /**<Audio SIF DK NICAM */ /**<CNcomment:��Ƶ������ʽDK NICAM*/
    SOURCE_AUDSYS_L,                         /**<Audio SIF L */ /**<CNcomment:��Ƶ������ʽL*/
    SOURCE_AUDSYS_M,                         /**<Audio SIF M*//**<CNcomment:��Ƶ������ʽM*/
    SOURCE_AUDSYS_M_BTSC,                    /**<Audio SIF M_BTSC *//**<CNcomment:��Ƶ������ʽM BTSC*/
    SOURCE_AUDSYS_M_A2,                      /**<Audio SIF M_A2 *//**<CNcomment:��Ƶ������ʽM A2*/
    SOURCE_AUDSYS_M_EIA_J,                   /**<Audio SIF M_EIA_J */ /**<CNcomment:��Ƶ������ʽM EIA J*/
    SOURCE_AUDSYS_BUTT
} SOURCE_AUDSYS_E;

/**SIF control param*//** CNcomment:�Զ���ʽ�����Ʋ���*/
typedef enum _SOURCE_SIF_SYSCTL_E
{
    SOURCE_SIF_SYSCTL_BTSC = 0,              /**<SIF control param BTSC *//**<CNcomment: ��Ƶ��ʽ������BTSC,America M */
    SOURCE_SIF_SYSCTL_EIAJ,                  /**<SIF control param EIAJ *//**<CNcomment: ��Ƶ��ʽ������EIAJ,Japan M */
    SOURCE_SIF_SYSCTL_M_KOREA,               /**<SIF control param M_KOREA *//**<CNcomment: ��Ƶ��ʽ������FM Korea,Korea M */
    SOURCE_SIF_SYSCTL_PAL_SUM,               /**<SIF control param PAL_SUM *//**<CNcomment: ��Ƶ��ʽ������PAL */
    SOURCE_SIF_SYSCTL_SECAM_L,               /**<SIF control param SECAM_L *//**<CNcomment: ��Ƶ��ʽ������L/L' */
    SOURCE_SIF_SYSCTL_FM_US,                 /**<SIF control param FM_US *//**<CNcomment: ��Ƶ��ʽ������FM-Stereo Radio US */
    SOURCE_SIF_SYSCTL_FM_EUROPE,             /**<SIF control param FM_EUROPE *//**<CNcomment: ��Ƶ��ʽ������FM-Stereo Radio Europe' */
    SOURCE_SIF_SYSCTL_BUTT
} SOURCE_SIF_SYSCTL_E;

/**SIF mode*//** CNcomment:��Ƶ����ģʽ*/
typedef enum _SOURCE_SIF_OUTMODE_E
{
    SOURCE_SIF_OUTMODE_MONO = 0x00,              /**<SIF Audio Mode MONO*//**<CNcomment:��Ƶ����ģʽMONO*/
    SOURCE_SIF_OUTMODE_STEREO,                   /**<SIF Audio Mode G Stereo*//**<CNcomment:��Ƶ����ģʽStereo*/
    SOURCE_SIF_OUTMODE_DUAL_A,                   /**<SIF Audio Mode Dual A*//**<CNcomment:��Ƶ����ģʽDUAL_A*/
    SOURCE_SIF_OUTMODE_DUAL_B,                   /**<SIF Audio Mode Dual B*//**<CNcomment:��Ƶ����ģʽDUAL_B*/
    SOURCE_SIF_OUTMODE_DUAL_AB,                  /**<SIF Audio Mode Dual AB*//**<CNcomment:��Ƶ����ģʽDUAL_AB*/
    SOURCE_SIF_OUTMODE_BTSC_MONO,                /**<SIF Audio Mode BTSC MONO*//**<CNcomment:��Ƶ����ģʽBTSC_MONO*/
    SOURCE_SIF_OUTMODE_BTSC_STEREO,              /**<SIF Audio Mode BTSC STEREO*//**<CNcomment:��Ƶ����ģʽBTSC_STEREO*/
    SOURCE_SIF_OUTMODE_BTSC_SAP,                 /**<SIF Audio Mode BTSC SAP*//**<CNcomment:��Ƶ����ģʽBTSC_SAP*/
    SOURCE_SIF_OUTMODE_NICAM_FORCED_MONO,        /**<SIF Audio Mode NICAM Forced MONO*//**<CNcomment:��Ƶ����ģʽNICAM_FORCED_MONO*/
    SOURCE_SIF_OUTMODE_NICAM_MONO,               /**<SIF Audio Mode NICAM MONO*//**<CNcomment:��Ƶ����ģʽNICAM_MONO*/
    SOURCE_SIF_OUTMODE_NICAM_STEREO,             /**<SIF Audio Mode NICAM Stereo*//**<CNcomment:��Ƶ����ģʽNICAM_STEREO*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_A,             /**<SIF Audio Mode NICAM DUAL A*//**<CNcomment:��Ƶ����ģʽNICAM_DUAL_A*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_B,             /**<SIF Audio Mode NICAM DUAL B*//**<CNcomment:��Ƶ����ģʽNICAM_DUAL_B*/
    SOURCE_SIF_OUTMODE_NICAM_DUAL_AB,            /**<SIF Audio Mode NICAM DUAL AB*//**<CNcomment:��Ƶ����ģʽNICAM_DUAL_AB*/
    SOURCE_SIF_OUTMODE_BUTT
} SOURCE_SIF_OUTMODE_E;

/**SIF over devaiton*//** CNcomment:��Ƶ����������*/
typedef enum _SOURCE_SIF_OVER_DEVIATION_E
{
    SOURCE_SIF_OVER_DEVIATION_50K  = 0,          /**<Audio SIF over devaiton 50K */ /**<CNcomment:������ 50K*/
    SOURCE_SIF_OVER_DEVIATION_100K,              /**<Audio SIF over devaiton 100K */ /**<CNcomment:������ 100K*/
    SOURCE_SIF_OVER_DEVIATION_200K,              /**<Audio SIF over devaiton 200K */ /**<CNcomment:������ 200K*/
    SOURCE_SIF_OVER_DEVIATION_384K,              /**<Audio SIF over devaiton 384K */ /**<CNcomment:������ 384K*/
    SOURCE_SIF_OVER_DEVIATION_540K,              /**<Audio SIF over devaiton 500K */ /**<CNcomment:������ 500K*/
    SOURCE_SIF_OVER_DEVIATION_BUTT
} SOURCE_SIF_OVER_DEVIATION_E;

#ifdef ANDROID_HAL_MODULE_USED
/**Source module structure(Android require) */
/**CNcomment:����Դģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _SOURCE_MODULE_S
{
    struct hw_module_t stCommon;     /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
} SOURCE_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_SOURCE*/
/** @{*/  /** <!-- -[HAL_SOURCE]=*/

/**Source device structure*//** CNcomment:����Դ�豸�ṹ*/
typedef struct _SOURCE_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif
    /**
    \brief Source  init.CNcomment:����Դģ���ʼ�� CNend
    \attention \n
    Lower layer source module init and alloc necessary resource,  repeat call return success.
    CNcomment:�ײ�����Դģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SOURCE_INIT_FAILED  Lower layer source module init error.CNcomment:�ײ�����Դģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief Source  deinit.CNcomment:����Դģ��ȥ��ʼ�� CNend
    \attention \n
    Lower layer source module deinit and release occupied resource,  repeat call return success.
    CNcomment:�ײ�����Դģ��ȥ��ʼ�����ͷ�ռ�õ���Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:ȥ��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_SOURCE_DEINIT_FAILED  Lower layer source module deinit error.CNcomment:�ײ�����Դģ��ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief Create video channel at specify source.CNcomment:�����ض���Դ������Ƶͨ�� CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:�������� CNend
    \param[out] pSourceHandle generated handle.CNcomment:���ɵľ�� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_CREATE_PARAMS_S

    \par example
    */
    S32 (* source_create)(struct _SOURCE_DEVICE_S* pstDev, HANDLE* const pSourceHandle, SOURCE_CREATE_PARAMS_S* const pstCreateParams);

    /**
    \brief destory video channel used by input source.CNcomment:�����ض���Դ������Ƶͨ�� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] pstDestoryParams destory param.CNcomment:���ٲ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_DESTORY_PARAMS_S

    \par example
    */
    S32 (* source_destory)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_DESTORY_PARAMS_S* const pstDestoryParams);

    /**
    \brief Get source module capability.CNcomment: ��ȡ����Դģ���豸����CNend
    \attention \n
    \param[out] pstCapability source module capability.CNcomment:����Դģ���豸����CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_CAPABILITY_S

    \par example
    */
    S32 (* source_get_capability)(struct _SOURCE_DEVICE_S* pstDev, SOURCE_CAPABILITY_S* const pstCapability);

    /**
    \brief Get source params.CNcomment: ��ȡ����Դ����CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] pstCreateParams source params.CNcomment:����Դ����CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_CAPABILITY_S

    \par example
    */
    S32 (* source_getParams)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_PARAMS_S* const pstCreateParams);

    /**
    \brief Set source params.CNcomment:��������Դ���� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] pstSourceParams source param.CNcomment:����Դ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_PARAMS_S

    \par example
    */
    S32 (* source_setParams)(struct _SOURCE_DEVICE_S* pstDev,  const HANDLE hSource,  const SOURCE_PARAMS_S*   pstSourceParams);

    /**
    \brief video channel start play stream.CNcomment:��������Դ���� CNend
    \attention \n
    must attach audio&video dest first .
    CNcomment:������������ƵĿ���. CNend
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_start)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief video channel stop play stream.CNcomment:ֹͣ����Դ���� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_stop)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get input stream's signal state.CNcomment: ��ȡ����Դ�ź�״̬CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] pStatus signal status.CNcomment:�ź�״̬CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_SIGNAL_STATUS_E

    \par example
    */
    S32 (* source_getSignalState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIGNAL_STATUS_E* const pStatus);

    /**
    \brief get source timing infomation.CNcomment: ��ȡ����Դtiming��ϢCNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] pstTimingInfo timing info.CNcomment:timing info CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_TIMING_INFO_S

    \par example
    */
    S32 (* source_getVideoInfo)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_TIMING_INFO_S* const pstTimingInfo);

    /**
    \brief set tvd color system.CNcomment:����tvdɫ��ϵͳ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enColorSys tvd color system.CNcomment:tvdɫ��ϵͳ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_COLOR_SYS_E

    \par example
    */
    S32 (* source_setColorSys)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, const SOURCE_COLOR_SYS_E enColorSys);

    /**
    \brief get tvd color system.CNcomment:��ȡtvdɫ��ϵͳ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] penColorSys tvd color system.CNcomment:tvdɫ��ϵͳ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_COLOR_SYS_E

    \par example
    */
    S32 (* source_getColorSys)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_COLOR_SYS_E* const penColorSys);

    /**
    \brief get tvd  signal locked status.CNcomment:��ȡtvd�ź�����״̬ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] pbSignalLock tvd signal locked status.CNcomment:tvd�ź�����״̬ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_getSignalLock)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, BOOL* const pbSignalLock);

    /**
    \brief set sif standard.CNcomment:����sif������ʽ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enStandard sif standard.CNcomment:����sif������ʽ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_AUDSYS_E

    \par example
    */
    S32 (*source_setStandard)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_AUDSYS_E enStandard);

    /**
    \brief get sif standard.CNcomment:��ȡsif������ʽ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] penStandard sif standard.CNcomment:sif������ʽ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_AUDSYS_E

    \par example
    */
    S32 (*source_getStandard)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_AUDSYS_E* penStandard);

    /**
    \brief set sif mode.CNcomment:����sif����ģʽ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enOutmode sif mode.CNcomment:����sif����ģʽ  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_SIF_OUTMODE_E

    \par example
    */
    S32 (*source_setSndMode)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIF_OUTMODE_E enOutmode);

    /**
    \brief get sif mode.CNcomment:��ȡsif����ģʽ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] penOutmode sif mode.CNcomment:sif����ģʽ  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_SIF_OUTMODE_E

    \par example
    */
    S32 (*source_getSndMode)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource_handle, SOURCE_SIF_OUTMODE_E* penOutmode);

    /**
    \brief set SIF over devaiton.CNcomment:������Ƶ�����Ʋ��� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enOverDeviation SIF over devaiton.CNcomment:�����Ʋ���  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_SIF_OVER_DEVIATION_E

    \par example
    */
    S32 (*source_setOverDeviation)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_SIF_OVER_DEVIATION_E enOverDeviation);

    /**
    \brief set SIF carri shift.CNcomment:������ƵƵ�� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] u32CarriShift SIF carri shift.CNcomment:��ƵƵ��   CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (*source_setCarriShift)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, U32 u32CarriShift);

    /**
    \brief start hddec calibration.CNcomment:����HDDECУ׼ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_startCalib)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get calibration state.CNcomment:��ȡHDDECУ׼״̬ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] penCalibrationState calibration state.CNcomment:HDDECУ׼״̬  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_ADJSTAT_E

    \par example
    */
    S32 (* source_getCalibState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_ADJSTAT_E* penCalibrationState);

    /**
    \brief get calibration result.CNcomment:��ȡHDDECУ׼��� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] pstCalibrationPara calibration result.CNcomment:HDDECУ׼���  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_CALIBRATION_INFO_S

    \par example
    */
    S32 (* source_getCalibPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_CALIBRATION_INFO_S* pstCalibrationPara);

    /**
    \brief set calibration para.CNcomment:����HDDECУ׼���� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] stCalibrationPara calibration para.CNcomment:HDDECУ׼����CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_CALIBRATION_INFO_S

    \par example
    */
    S32 (* source_setCalibPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource,  SOURCE_CALIBRATION_INFO_S stCalibrationPara);

    /**
    \brief start vga auto adjust.CNcomment:����vga�Զ����� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_startAdjust)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource);

    /**
    \brief get adjust state.CNcomment:��ȡvga����״̬ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[out] penAdjustState adjust state.CNcomment:vga����״̬  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_ADJSTAT_E

    \par example
    */
    S32 (* source_getAdjustState)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_ADJSTAT_E* penAdjustState);

    /**
    \brief get vga adjust result .CNcomment:��ȡvga������� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enAdjustItem adjust item.CNcomment:������ CNend
    \param[out] pu32ItemValue adjust value.CNcomment:vga����ֵ  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_HDDEC_ADJUST_E

    \par example
    */
    S32 (* source_getAdjustPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, U32* pu32ItemValue);

    /**
    \brief set vga adjust para.CNcomment:����vga�������� CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enAdjustItem adjust item.CNcomment:������ CNend
    \param[in] u32ItemValue adjust value.CNcomment:vga����ֵ  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_setAdjustPara)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, U32 u32ItemValue);

    /**
    \brief get vga adjust range.CNcomment:��ȡvga������Χ CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enAdjustItem adjust item.CNcomment:������ CNend
    \param[out] pstRange adjust range.CNcomment:vga������Χ  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SOURCE_HDDEC_ADJUST_E

    \par example
    */
    S32 (* source_getAdjustRange)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDDEC_ADJUST_E enAdjustItem, SOURCE_RANGE_S* pstRange);

    /**
    \brief send MHL RCP Key,only for hdmi.CNcomment:����MHL RCP Key����֧��HDMI CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enMhlRcpKey RCP Key value.CNcomment:RCP Key��ֵ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_sendMhlRcp)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDMIRX_RCP_KEY_E enMhlRcpKey);

    /**
    \brief set edid, only for hdmi & VGA.CNcomment:����edid����֧��HDMI��VGA  CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enEdidType Edid type.CNcomment:edid���� CNend
    \param[in] u32Length Edid info length.CNcomment:edid��Ϣ���� CNend
    \param[in] pData Edid info data.CNcomment:edid��Ϣ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_updateEdid)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_EDID_E enEdidType, U32 u32Length, VOID* const pData);

    /**
    \brief set HDCP, only for hdmi.CNcomment:����HDCP����֧��HDMI  CNend
    \attention \n
    \param[in] hSource source handle.CNcomment:����Դ��� CNend
    \param[in] enHdcpType HDCP type.CNcomment:HDCP���� CNend
    \param[in] u32Length HDCP info length.CNcomment:HDCP��Ϣ���� CNend
    \param[in] pData HDCP info data.CNcomment:HDCP��Ϣ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_SOURCE_OP_FAILED source operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (* source_updateHdcp)(struct _SOURCE_DEVICE_S* pstDev, const HANDLE hSource, SOURCE_HDCP_E enHdcpType, U32 u32Length, VOID* const pData);

} SOURCE_DEVICE_S;

/**
 \brief direct get input source device api, for linux and android.CNcomment:��ȡ����Դ�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
 \attention \n
get source device api��for linux and andorid.
CNcomment:��ȡ����Դ�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
 \retval  source device pointer when success.CNcomment:�ɹ�����source�豸ָ�롣CNend
 \retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
 \see \n
::SOURCE_DEVICE_S

 \par example
 */
SOURCE_DEVICE_S* getSourceDevice();

/**
\brief  Open HAL source module device.CNcomment:��HAL����Դģ���豸 CNend
\attention \n
Open HAL source module device(for compatible Android HAL).
CNcomment:��HAL����Դģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice source device structure.CNcomment:����Դ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
\brief  Close HAL source module device.CNcomment:�ر�HAL����Դģ���豸 CNend
\attention \n
Close HAL source module device(for compatible Android HAL).
CNcomment:�ر�HAL����Դģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice source device structure.CNcomment:����Դ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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

