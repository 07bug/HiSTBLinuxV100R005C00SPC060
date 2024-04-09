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
/**CNcomment:������Ƶ��� ģ������ */
#define VOUT_HARDWARE_MODULE_ID      "video_output"

/**Defines the video output device name*/
/**CNcomment:������Ƶ��� �豸���� */
#define VOUT_HARDWARE_VOUT0          "vout0"

/**Auto set the valid values when the values of alpha, brightness, contrast, saturation, and DOF are unvalid*/
/**CNcomment:���͸����,����,�Աȶ�,���Ͷ�,�������ڲ��������Ϸ���Χ, ���Զ��޸�Ϊ�Ϸ���Χ */

/**Valid range of alpha: [0,100]*/
/**CNcomment:͸����ֵ[0,100]*/
#define VOUT_ALPHA_MAX               (100)
#define VOUT_ALPHA_MIN               (0)

/**Valid range of brightness: [0,100]*/
/**CNcomment:���ȷ�Χ[0,100]*/
#define VOUT_BRIGHTNESS_MAX          (100)
#define VOUT_BRIGHTNESS_MIN          (0)

/**Valid range of contrast: [0,100]*/
/**CNcomment:�Աȶȷ�Χ[0,100]*/
#define VOUT_CONTRAST_MAX            (100)
#define VOUT_CONTRAST_MIN            (0)

/**Valid range of saturation: [0,100]*/
/**CNcomment:���Ͷȷ�Χ[0,100]*/
#define VOUT_SATURATION_MAX          (100)
#define VOUT_SATURATION_MIN          (0)

/**Valid range of hue: [0,100]*/
/**CNcomment:ɫ����Χ[0,100]*/
#define VOUT_HUE_MAX                 (100)
#define VOUT_HUE_MIN                 (0)

/**Valid range of depth of field: [0,100]*/
/**CNcomment:���Χ[0,100]*/
#define VOUT_DOF_MAX                 (100)
#define VOUT_DOF_MIN                 (0)

/**Defines  display channel number, the number must corespond with the item number of VOUT_DISPLAY_CHANNEL_E*/
/**CNcomment:������ʾͨ����������������VOUT_DISPLAY_CHANNEL_E�ṹ����Ŀ������һ��*/
#define VOUT_DISPLAY_MAX (6)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_VOUT */
/** @{ */  /** <!-- [HAL_VOUT] */

/**Defines the types of display channel*/
/**CNcomment:������ʾͨ��*/
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
/**CNcomment:������Ƶ�������¼�*/
typedef enum _VOUT_EVT_E
{
    VOUT_EVT_BASE        = 0,
    VOUT_HDMI_EVT_BASE   = VOUT_EVT_BASE,
    VOUT_HDMI_EVT_PLUGIN = VOUT_HDMI_EVT_BASE,      /**<HDMI plugin*//**<CNcomment:HDMI ����*/
    VOUT_HDMI_EVT_UNPLUG,                           /*<HDMI unplugin*//**<CNcomment:HDMI �γ�*/
    VOUT_HDMI_EVT_EDID_FAIL,                        /**<Get EDID fail*//**<CNcomment:��ȡEDID ʧ��*/
    VOUT_HDMI_EVT_HDCP_FAIL,                        /**<Set HDCP fail*//**<CNcomment:����HDCPʧ��*/
    VOUT_HDMI_EVT_HDCP_SUCCESS,                     /**<Set HDCP success*//**<CNcomment:����HDCP�ɹ�*/
    VOUT_EVT_BUTT,
} VOUT_EVT_E;

/**Defines the types of frame rate:
 1.HDI should auto set the optimal format and frame rate and does not return any error when the format or frame rate is not supported by the HD channel.
 2.HDI should auto set a valid frame rate and does not return any error when the frame rate is unvalid for SD formate.*/
/**CNcomment:����֡������
 1. ����ͨ�����ò�֧�ֵ���ʽ����֡��, HDI����ѡ�����ŵ���ʽ��֡��,�������󷵻�.
 2. ���ڱ�����ʽ,���Ӧ�ô�������֡��,HDI �Զ�����,�������󷵻�.*/
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
/**CNcomment:������ʽ �͸���ֱ���
 VOUT_FORMAT_E & VOUT_VID_FRAME_RATE_E ��ϳ���������.
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

 1. ����Ǳ���ͨ�����ø�����ʽ,����ʧ��.
 2. ����ͨ���������ñ�����ʽ, ���ƽ̨ԭ��,
     ����ͨ�����óɱ�����ʽ,Ч������,ͼ��ģ��,
     ��ҪӦ������Ŀ����ʱ�����,hdiҪ�ṩ���������õĹ���,��������.
 3. ����ͨ�����ò�֧�ֵ���ʽ����֡��,
     HDI����ѡ�����ŵ���ʽ��֡��,�������󷵻�.
 4. ���ڱ�����ʽ,���Ӧ�ô�������֡��,HDI �Զ�����,�������󷵻�.
 5. VOUT_FORMAT_UNKNOWNδ֪�ֱ���,
     ���ڻ�ȡ��״̬�õ�δ֪�ֱ��ʵ����,Ӧ�ò������ô˷ֱ��ʸ�HDI.*/
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
/**CNcomment:��Ƶ��߱�
VOUT_ASPECT_RATIO_UNKNOWNδ֪��߱�. ���ڻ�ȡ��״̬�õ�δ֪��߱ȵ����,Ӧ�ò������ô�ֵ��HDI.*/
typedef enum _VOUT_ASPECT_RATIO_E
{
    VOUT_ASPECT_RATIO_AUTO = 0,     /**< auto*//**<CNcomment:�Զ�ѡ��*/
    VOUT_ASPECT_RATIO_16TO9,        /**< 16:9*//**<CNcomment:16:9*/
    VOUT_ASPECT_RATIO_4TO3,         /**< 4:3*//**<CNcomment:4:3*/
    VOUT_ASPECT_RATIO_UNKNOWN,
    VOUT_NB_OF_ASPECT_RATIO
} VOUT_ASPECT_RATIO_E;

/**Defines conversion mode of AspectRatio*/
/**CNcomment:��Ƶ��߱�����Ӧģʽ*/
typedef enum _VOUT_ASPECT_RATIO_CONVERSION_E
{
    VOUT_AR_CONVERSION_PAN_SCAN = 0,      /**< PAN_SCAN*//**<CNcomment: �ü�*/
    VOUT_AR_CONVERSION_LETTER_BOX,        /**< LETTER_BOX*//**<CNcomment: �Ӻڱ�*/
    VOUT_AR_CONVERSION_COMBINED,          /**< COMBINED*//**<CNcomment: �ӺڱߺͲü����*/
    VOUT_AR_CONVERSION_IGNORE,            /**< IGNORE*//**<CNcomment: ����*/
    VOUT_AR_CONVERSION_CUSTOM,            /**< CUSTOM*//**<CNcomment: �û��Զ���*/
    VOUT_NB_OF_AR_CONVERSION
} VOUT_ASPECT_RATIO_CONVERSION_E;

/**Video output types, can be combined*/
/**CNcomment:��Ƶ�������: �������Ҫ֧����Ϸ�ʽ*/
typedef enum _VOUT_OUTPUT_TYPE_E
{
    VOUT_OUTPUT_TYPE_NONE            = 0x00,
    VOUT_OUTPUT_TYPE_COMPOSITE       = 0x01,                   /**< SD analog cvbs*//**<CNcomment:����ģ�⸴�� ���*/
    VOUT_OUTPUT_TYPE_YPBPR           = 0x02,                   /**< SD analog YUV.*//**<CNcomment:����ģ����� ���*/
    VOUT_OUTPUT_TYPE_SVIDEO          = 0x04,                   /**< SD YC*//**<CNcomment:����SVIDEO ���*/
    VOUT_OUTPUT_TYPE_DVI             = 0x08,                   /**< HDMI--auto color space*//**< HDMI*/
    VOUT_OUTPUT_TYPE_HDMI            = VOUT_OUTPUT_TYPE_DVI,   /**< HDMI--auto color space*//**< HDMI*/
    VOUT_OUTPUT_TYPE_SCART           = 0x10,                   /**< scart*//**< CNcomment:scart*/
    VOUT_OUTPUT_TYPE_VGA             = 0x20,                   /**< vga*//**< CNcomment:vga*/
    VOUT_OUTPUT_TYPE_RF              = 0x40,                   /**< rf*//**< CNcomment:rf*/
    VOUT_OUTPUT_TYPE_YCBCR           = 0x80,                   /**< DIGITAL YCbCr COMPONENTS *//**< CNcomment:����*/
    VOUT_OUTPUT_TYPE_HD_YUV          = 0x100,                  /**< HD analog YUV*//**< CNcomment:YUV*/
    VOUT_OUTPUT_TYPE_HDMI_RGB888     = 0x200,                  /**< hdmi--digital RGB888*//**< CNcomment:HDMI RGB888*/
    VOUT_OUTPUT_TYPE_HDMI_YCBCR444   = 0x400,                  /**< hdmi--digital YCBCR444*//**< CNcomment:HDMI YCBCR444*/
    VOUT_OUTPUT_TYPE_HDMI_YCBCR422   = 0x800,                  /**< hdmi--digital YCBCR422*//**< CNcomment:HDMI YCBCR422*/
    VOUT_OUTPUT_TYPE_RGB             = 0x1000,                 /**< SD analog RGB*/ /**< CNcomment:SD RGB*/
    VOUT_OUTPUT_TYPE_HD_RGB          = 0x2000,                 /**< HD analog RGB*/ /**< CNcomment:HD RGB*/
    VOUT_OUTPUT_TYPE_PANNEL          = 0x4000,                 /**< PANNEL*//**< CNcomment:���*/
    VOUT_OUTPUT_TYPE_ALL             = (S32)0xffffffff         /**< All type*//**< �����������*/
} VOUT_OUTPUT_TYPE_E;

/**Type define of alpha, see VOUT_ALPHA_MAX & VOUT_ALPHA_MIN*/
/**CNcomment:͸���ȣ��μ�VOUT_ALPHA_MAX & VOUT_ALPHA_MIN ����*/
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
/**CNcomment:CGMS-A �������*/
typedef enum _VOUT_VBI_CGMS_A_COPY_E
{
    VOUT_VBI_CGMS_A_COPY_PERMITTED = 0,                     /**< copying is permitted without restriction*//**< CNcomment:�����ƿ���*/
    VOUT_VBI_CGMS_A_COPY_ONE_TIME_BEEN_MADE = 1,            /**< no more copies, one generation copy has been made*//**< CNcomment:�Ѿ�����һ��*/
    VOUT_VBI_CGMS_A_COPY_ONE_TIME  = 2,                     /**< one generation of copied may be made*//**< CNcomment:ֻ�ܿ���һ��*/
    VOUT_VBI_CGMS_A_COPY_FORBIDDEN = 3,                     /**< no copying is permitted*//**< CNcomment:��ֹ����*/
    VOUT_VBI_CGMS_A_BUTT
} VOUT_VBI_CGMS_A_COPY_E;

/**Defines of display 3D mode stucture*/
/**CNcomment:����3D ��ʾģʽ*/
typedef enum _VOUT_3D_FORMAT_E
{
    VOUT_3D_FORMAT_2D = 0,
    VOUT_3D_FORMAT_FP,                       /**<3d type:Frame Packing*//**<CNcomment:3d ģʽ:֡��װ*/
    VOUT_3D_FORMAT_SBS,                      /**<3d type:Side by side half*//**<CNcomment:3d ģʽ:����ʽ ���Ұ��*/
    VOUT_3D_FORMAT_TAB,                      /**<3d type:Top and Bottom*//**<CNcomment:3d ģʽ:����ģʽ*/
    VOUT_3D_FORMAT_FA,                       /**<3d type:Field alternative*//**<CNcomment:3d ģʽ:������*/
    VOUT_3D_FORMAT_LA,                       /**<3d type:Line alternative*//**<CNcomment:3d ģʽ:�н���*/
    VOUT_3D_FORMAT_SBS_FULL,                 /**<3d type:Side by side full*//**<CNcomment:3d ģʽ:����ʽ ����ȫ��*/
    VOUT_3D_FORMAT_L_DEPTH,                  /**<3d type:L+depth*//**<CNcomment:3d ģʽ:L+DEPTH*/
    VOUT_3D_FORMAT_LBL_LR,                   /**<3d type:Line alternative Left Eye Fisrt*//**<CNcomment:3d ģʽ:�н���,��������*/
    VOUT_3D_FORMAT_LBL_RL,                   /**<3d type:Line alternative Right Eye Fisrt*//**<CNcomment:3d ģʽ:�н���,��������*/
    VOUT_3D_FORMAT_L_DEPTH_GRAPHISC_DEPTH,   /**<3d type:L+depth+Graphics+Graphics-depth*//**<CNcomment:3d ģʽ:L+depth+Graphics+Graphics-depth*/
    VOUT_3D_FORMAT_BUTT
} VOUT_3D_FORMAT_E;
/**Defines of video 3d mode enum */
/**CNcomment:����3D��Ƶ����ģʽö�� */
typedef enum _VOUT_3D_MODE_E
{
    VOUT_3D_MODE_2D = 0,  /**<2D mode *//**<CNcomment:2Dģʽ���� */
    VOUT_3D_MODE_2DTO3D,  /**<2D to 3D mode *//**<CNcomment:2Dת3Dģʽ���� */
    VOUT_3D_MODE_3D,      /**<3D mode *//**<CNcomment:3Dģʽ���� */
    VOUT_3D_MODE_BUTT,
} VOUT_3D_MODE_E;

/**Defines of window channel type */
/**CNcomment:������Ƶͨ·��ʱ�ṹ�� */
typedef enum VOUT_WINDOW_CHANNEL_E
{
    VOUT_WINDOW_HIGHQUALITY = 0,
    VOUT_WINDOW_LOWQUALITY,
    VOUT_WINDOW_MAX,
} VOUT_WINDOW_CHANNEL_E;

/**Struct of stop mode*/
/**CNcomment:ֹͣģʽ  */
typedef enum _VOUT_WINDOW_STOP_MODE_E
{
    VOUT_WINDOW_STOP_MODE_BLACK = 0,   /**<Black*//**<CNcomment: ����*/
    VOUT_WINDOW_STOP_MODE_FREEZE       /**<Freeze last picture*//**<CNcomment: ��֡*/
} VOUT_WINDOW_STOP_MODE_E;

/**enum define about Window Type */
/**CNcomment: ����Window����ö��*/
typedef enum hiUNF_VO_WIN_TYPE_E
{
    VOUT_WINDOW_TYPE_DEFAULT = 0,   /**<create defalut window*//**<CNcomment: Ĭ�ϵĴ�������*/
    VOUT_WINDOW_TYPE_AUTO,          /**<create auto window*//**<CNcomment: �����Զ�����ͨ��*/
    VOUT_WINDOW_TYPE_MAIN,          /**<create main window*//**<CNcomment: ����������ͨ��*/
    VOUT_WINDOW_TYPE_SUB,           /**<create sub window*//**<CNcomment: �����δ���ͨ��*/
    VOUT_WINDOW_TYPE_BUTT
} VOUT_WINDOW_TYPE_E;

/**Defines video coordinate */
typedef S32 AV_COORD_T;

/**Struct of default video output settings, SD anf HD can be set independently,  see the define of VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_VID_FRAME_RATE_E*/
/**CNcomment:Ĭ����ʾ���ã��߱���Ҫ�ܶ������ã���VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_VID_FRAME_RATE_E*/
typedef struct _VOUT_DEFAULT_DISPSETTING_S
{
    VOUT_FORMAT_E           enDispFmt;                /**<Video output format, do not set auto, auto means no stream now*//**< CNcomment:��Ҫ��Ϊ�Զ�ģʽ,��av_dispsettings_t::enDispFmt ��AUTO���Ҹտ�����û������ʱ��,HDIӦ�����óɴ˸�ʽ,�Է���APP֪����ǰ״̬,��,SDͨ������������NTSC,PAL&PALN,PALM&VOUT_FORMAT_SECAM���ж�����.*/
    VOUT_VID_FRAME_RATE_E   enFrameRate;              /**<Frame rate, do not set auto, auto means no stream now*//**< CNcomment:��Ҫ��Ϊ�Զ�ģʽ,��av_dispsettings_t::enFrameRate ��AUTO���Ҹտ�����û������ʱ��,HDIӦ�����óɴ˸�,�Է���APP֪����ǰ״̬*/
    VOUT_ASPECT_RATIO_E     enAspectRatio;            /**<Aspect ratio, do not set auto, auto means no stream now*//**< CNcomment:��Ҫ��Ϊ�Զ�ģʽ,��av_dispsettings_t::enAspectRatio ��AUTO���Ҹտ�����û������ʱ��,HDIӦ�����óɴ˸�,�Է���APP֪����ǰ״̬*/
} VOUT_DEFAULT_DISPSETTING_S;

/**Struct of Rectangle*/
/**CNcomment:���νṹ  */
typedef struct _VOUT_RECT_S
{
    S32 s32XOffset;
    S32 s32YOffset;
    U32 u32Width;
    U32 u32Height;
} VOUT_RECT_S;

/**Struct of Region*/
/**CNcomment:����ṹ  */
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
/**CNcomment:��ʾ����,
1. �߱���Ҫ�ܶ�������.
2. ��Ҫ�޸���Щ����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥ. set�����������û�иı�ĳ�Ա�����޸�,
3. ���ǵ����������,get�����Ĳ�����set��ȥ֮ǰ,�����������Ѿ���set����. Ҳ���Ǵ�ʱ��set�п��ܻḲ����������set����������
4. brightness,contrast,saturation����Щƽ̨�ϻ�Ӱ�쵽��Ƶָ��,�����޸��Ժ�������Ĭ��ֵ
Ϊ�˲�Ӱ�쵽��Ƶָ��,av_init()���������洫������u8Brightness,u8Contrast,u8Saturation,������
������get��������ϵͳ��Ĭ��ֵ,���鱣����ָ�����������.
av_display_set()�����ᴦ�����洫������u8Brightness,u8Contrast,u8Saturation,�޸�brightness,contrast,saturation.
5. enOutputType::��ʾ�󶨵�����豸,֧�ֻ����,��������ʱ��̬��(���)�ͽ��(�����).
VOUT_OUTPUT_TYPE_NONE �ǲ����,VOUT_OUTPUT_TYPE_ALL ���������ǰ�豸������֧�ֵ��豸,
���Ӧ�������˲�֧�ֵ��豸,�������ͨ�������� VOUT_OUTPUT_TYPE_COMPOSITE(cvbs)
HDI Ҫ�Զ�����,�������󷵻�.
6. brightness,contrast,saturation,alpha,3d_dof �������������Χ, HDI ��Ҫ����������Χ.
*@see VOUT_FORMAT_E, VOUT_ASPECT_RATIO_E, VOUT_ASPECT_RATIO_CONVERSION_E, VOUT_OUTPUT_TYPE_E, VOUT_ALPHA_T
*@see VOUT_SATURATION_MAX, VOUT_SATURATION_MIN;VOUT_CONTRAST_MAX,VOUT_CONTRAST_MIN;
*@see VOUT_BRIGHTNESS_MAX, VOUT_BRIGHTNESS_MIN;VOUT_ALPHA_MAX, VOUT_ALPHA_MIN*/
typedef struct _VOUT_DISPSETTING_S
{
    VOUT_FORMAT_E                   enDispFmt;          /**<Display format, default is VOUT_FORMAT_AUTO*//**<CNcomment: Ĭ��ΪVOUT_FORMAT_AUTO,�����AUTO,1.�տ�����û������ʱ��,Ӧ����av_default_dispsettings_t::enDispFmt,2.�����̨,û����,Ӧ�ñ���ԭ�������ò���.*/
    VOUT_VID_FRAME_RATE_E           enFrameRate;        /**<Frame rate , default is VOUT_VID_FRAME_RATE_AUTO*//**<CNcomment: Ĭ��ΪVOUT_VID_FRAME_RATE_AUTO, �����AUTO,1.�տ�����û������ʱ��,Ӧ����av_default_dispsettings_t::enFrameRate,2.�����̨,û����,Ӧ�ñ���ԭ�������ò���.*/
    VOUT_FORMAT_E                   enAutoDispFmt;      /**<Auto adaption display format, it is depend on device*/ /**<CNcomment: ����Ӧ��ʽ�������豸����*/
    VOUT_VID_FRAME_RATE_E           enAutoFrameRate;    /**<Auto adaption frame rate, it is depend on device*/ /**<CNcomment: ����Ӧ֡�ʣ������豸����*/
    VOUT_ASPECT_RATIO_E             enAspectRatio;      /**<Aspect ratio , default is VOUT_ASPECT_RATIO_AUTO*//**<CNcomment: Ĭ��ΪVOUT_ASPECT_RATIO_AUTO,�����AUTO,1.�տ�����û������ʱ��,Ӧ����av_default_dispsettings_t::enAspectRatio,2.�����̨,û����,Ӧ�ñ���ԭ�������ò���.*/
    VOUT_ASPECT_RATIO_CONVERSION_E  enAspectRatioConv;  /**<Conversion mode of aspectRatio , default is VOUT_AR_CONVERSION_LETTER_BOX*//**<CNcomment: Ĭ��ΪVOUT_AR_CONVERSION_LETTER_BOX*/
    VOUT_OUTPUT_TYPE_E              enOutputType;       /**<Video output type, can be attached and detached dynamically*//**<CNcomment: ��ʾ�󶨵�����豸(֧�ֻ����,���Զ�̬�󶨺ͽ��) */
    BOOL                            bOutputEnable;      /**<Video output switch, default is TRUE*//**<CNcomment: �Ƿ������,ֻ�Ե�ǰͨ����Ч, Ĭ��Ϊtrue.*/
    U8                              u8Hue;              /**<Hue, range is [0, 100]*//**<CNcomment: ɫ������Χ[0, 100].*/
    U8                              u8Brightness;       /**<To adjust the luminance intensity of the display video image.This value is unsigned and scaled between VOUT_BRIGHTNESS_MIN to VOUT_BRIGHTNESS_MAX.Default value are (VOUT_BRIGHTNESS_MAX/2).*//**<CNcomment: ����,��Χ��[VOUT_BRIGHTNESS_MIN, VOUT_BRIGHTNESS_MAX], Ĭ��ΪVOUT_BRIGHTNESS_MAX/2.*/
    U8                              u8Contrast;         /**<To adjust the relative difference between higher and lower intensity luminance values of the display image.This value is unsigned and scaled between VOUT_CONTRAST_MIN to VOUT_CONTRAST_MAX.Default value are (VOUT_CONTRAST_MAX/2).*//**<CNcomment: �Աȶ�,��Χ��[VOUT_CONTRAST_MIN, VOUT_CONTRAST_MAX], Ĭ��ΪVOUT_CONTRAST_MAX/2.*/
    U8                              u8Saturation;       /**<To adjust the color intensity of the displayed video image.This value is unsigned and scaled between VOUT_SATURATION_MIN to VOUT_SATURATION_MAX.Default value are (VOUT_SATURATION_MAX/2).*//**<CNcomment: ���Ͷ�,��Χ��[VOUT_SATURATION_MIN, VOUT_SATURATION_MAX], Ĭ��ΪVOUT_SATURATION/2.*/
    U8                              u83dDof;            /**<Depth of field*//**<CNcomment: ����ֵ,��Χ[VOUT_DOF_MIN,VOUT_DOF_MAX]*/
    VOUT_3D_FORMAT_E                en3dFmt;            /**<3D format*/ /**<CNcomment: 3d��ʽ  */
    VOUT_RECT_S                     stOSDVirtualRect;   /**<OSD����ֱ��� */
    VOUT_REGION_S                   stDispOutRegion;    /**<OSD��ʾ����*/
    BOOL                            bClearLogo;         /**<clear logo while starting up*/ /**< CNcomment: ��տ�������.*/
} VOUT_DISPSETTING_S;

/**Struct of video out init parameters*/
/**CNcomment:��Ƶģ���ʼ������ */
typedef struct _VOUT_INIT_PARAMS_S
{
    BOOL                bDispEnable;                        /**<Wether output after init*//**<<CNcomment: ture:��ʼ��ͬʱenable disp���(av, osd ,still, etc.); false: ��ʼ����û�����(av, osd, still, etc.), ���Ǵ�������, ����״̬������û�����*/
    VOUT_DISPSETTING_S  astDispSettings[VOUT_DISPLAY_MAX];  /**<Video output disp settings, this array index correspond the item index of VOUT_DISPLAY_CHANNEL_E, not the enum value*//**<CNcomment: ��Ƶ������������������ֵ��VOUT_DISPLAY_CHANNEL_E����Ŀ��Ŷ�Ӧ��������ö��ֵ��Ӧ*/
    U32                 u32Dummy;                           /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_INIT_PARAMS_S;

/**Struct of color space*/
/**CNcomment:������ʾ��ɫ�Ľṹ�� */
typedef struct  _VOUT_BG_COLOR_S
{
    U8 u8Red;               /**<Red *//**<CNcomment:��ɫ����*/
    U8 u8Green;             /**<Green*//**<CNcomment:��ɫ����*/
    U8 u8Blue;              /**<Blue*//**<CNcomment:��ɫ����*/
} VOUT_BG_COLOR_S;

/**Struct of open parameters*/
/**CNcomment:��һ��ʵ����������� */
typedef struct _VOUT_OPEN_PARAMS_S
{
    VOUT_DISPLAY_CHANNEL_E enDispChan;      /**<Display channel need to be opened*//**<CNcomment: ��Ҫ�򿪵���ʾͨ�� */
    VOUT_OUTPUT_TYPE_E enOutputType;        /**<Video output type*//**<CNcomment:��Ƶ�������*/
    U32 u32Dummy;                           /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_OPEN_PARAMS_S;

/**Struct of close parameters*/
/**CNcomment:��ر�ʵ������  */
typedef struct _VOUT_CLOSE_PARAMS_S
{
    U32 u32Dummy; /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_CLOSE_PARAMS_S;

/**Struct of terminate parameters*/
/**CNcomment:AVģ����ֹ����   */
typedef struct _VOUT_TERM_PARAM_S
{
    U32 u32Dummy; /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_TERM_PARAM_S;

/**Struct of the display capability of video output */
/**CNcomment:��Ƶ������� */
typedef struct _VOUT_DISP_CAPABILITY_S
{
    VOUT_OUTPUT_TYPE_E   enVoutType;                        /**<Video output type*//**<CNcomment:��Ƶ�������*/
    U32                  au32VidFormat[VOUT_FORMAT_BUTT];   /**<Video format, VOUT_FORMAT_E is index, 0 means do not supported this format*/ /**<CNcomment: ��VOUT_FORMAT_EΪ����,��ֵ��֧�ֵ�VOUT_VID_FRAME_RATE_E�����������ֵ,��ֵΪ0.���ʾ��֧�����ֱַ���*/
    U32                  u32WindowNum;                      /**<Number of windows can be supportted*//**<CNcomment:  ֧�ֵ�window��Ŀ */
} VOUT_DISP_CAPABILITY_S;

/**Struct of video output capability*/
/**CNcomment:��Ƶ������� */
typedef struct _VOUT_CAPABILITY_S
{
    VOUT_DISPLAY_CHANNEL_E  enDisplayChannel;                          /**<Video output display channels*//**<CNcomment:��Ƶ���ͨ��*/
    VOUT_DISP_CAPABILITY_S  astDispCapabilityAttr[VOUT_DISPLAY_MAX];   /**<Capability of Video output display channels, this array index correspond the item index of VOUT_DISPLAY_CHANNEL_E, not the enum value*//**<CNcomment:��Ƶ���ͨ������, �����������ֵ��VOUT_DISPLAY_CHANNEL_E����Ŀ��Ŷ�Ӧ��������ö��ֵ��Ӧ*/
} VOUT_CAPABILITY_S;

/**
\brief Video output event callback. CNcomment:vout �¼��ص�������������CNend
\attention \n
The function could call the api of VOUT module
CNcomment: �˺���������Ե��ñ�ģ���api, Ҳ����˵�����ڻص�������ʱ��Ҫͬʱ���ǵ������������������CNend
\param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
\param[in] enEvt VOUT event type.CNcomment:VOUT�¼����� CNend
\param[in] pData The data with event, see VOUT_EVT_E.CNcomment:��ο� VOUT_EVT_E ��˵�� CNend
\retval ::SUCCESS CNcomment:�ɹ� CNend
\retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
\see \n
::VOUT_EVT_E
*/
typedef VOID (* VOUT_CALLBACK_PFN)( const HANDLE hVout, const VOUT_EVT_E enEvt, const VOID* const pData);

/**Struct of config parameters of video out event callback, see VOUT_EVT_E, vout_callback_pfn_t*/
/**CNcomment:��Ƶ����ص����������ò���, ��VOUT_EVT_E, vout_callback_pfn_t ���� */
typedef struct _VOUT_EVT_CONFIG_PARAMS_S
{
    VOUT_EVT_E        enEvt;                       /**<The events we want to get by callback*//**<CNcomment: av �¼�,��ʾ�����ö��ĸ��¼���Ч*/
    VOUT_CALLBACK_PFN pfnCallback;                 /**<If pfnCallback is null, unregister the unregistered callback function*//**<CNcomment: ��pfnCallbackΪ��ʱ,����Ѿ�ע���˻ص��������Ƴ�,ȡ����ע��*/
    BOOL              bEnable;                     /**<Wether enable the callback of enEvt*//**<CNcomment: ��ʾ�Ƿ�ʹ�ܸ��¼��ص�*/
    U32               u32NotificationsToSkip;      /**<The skip counts before we get the callback of enEvt*//**<CNcomment: ��ʾ�ڵ���ע��Ļص�����֮ǰ,��Ҫ�������η����ĸ��¼�*/
} VOUT_EVT_CONFIG_PARAMS_S;

/**Strcut of video channel delay */
/**CNcomment:������Ƶͨ·��ʱ�ṹ�� */
typedef struct _VOUT_DELAY_S
{
    U32        u32PanelMemcDelay;
} VOUT_DELAY_S;

/**Struct of create window parameters*/
/**CNcomment:�������ڲ���   */
typedef struct _VOUT_WINDOW_CREATE_PARAMS_S
{
    VOUT_WINDOW_CHANNEL_E enWindowChan;
    BOOL                  bVirtual;          /**<Resvered*//**<CNcomment: create virtual_window */
    VOUT_WINDOW_TYPE_E    enWindowType;      /**<Window type*//**<CNcomment: �����Ĵ������� */
    U32 u32Dummy;                            /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_WINDOW_CREATE_PARAMS_S;

/**Struct of destroy window parameters*/
/**CNcomment:���ٴ��ڲ���   */
typedef struct _VOUT_WINDOW_DESTROY_PARAM_S
{
    U32 u32Dummy;                            /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} VOUT_WINDOW_DESTROY_PARAM_S;

/** RGB Color *//**CNcomment:RGB��ʽ */
typedef struct _VOUT_RGB_COLOR_S
{
    U32 u32Red;
    U32 u32Green;
    U32 u32Blue;
} VOUT_RGB_COLOR_S;

/**Struct of color temperature of window*/
/**CNcomment:ɫ�²���  */
typedef struct _VOUT_WINDOW_COLOR_TEMPERATURE_S
{
    U32 u32RedGain;                  /**<Red gain*//**<CNcomment: ��ɫ���� */
    U32 u32GreenGain;                /**<Green gain*//**<CNcomment: ��ɫ���� */
    U32 u32BlueGain;                 /**<Blue gain*//**<CNcomment: ��ɫ���� */
    U32 u32RedOffset;                /**<Red offset*//**<CNcomment: ��ɫƫ��*/
    U32 u32GreenOffset;              /**<Red offset*//**<CNcomment: ��ɫƫ��*/
    U32 u32BlueOffset;               /**<Red offset*//**<CNcomment: ��ɫƫ��*/
} VOUT_WINDOW_COLOR_TEMPERATURE_S;

/** window status *//**CNcomment:����״̬ */
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
/**CNcomment:ֹͣ����  */
typedef struct _VOUT_WINDOW_STOP_ATTR_S
{
    VOUT_WINDOW_STOP_MODE_E enStopMode;                       /**<Stop mode*//**<CNcomment: ֹͣģʽ*/
} VOUT_WINDOW_STOP_ATTR_S;

/**Struct of window attribute of user defined*/
/**CNcomment:�û��趨�Ĵ�������*/
typedef struct _VOUT_WINDOW_USER_DEF_ASPECT_S {
    BOOL      bUserDefAspectRatio;           /**<CNcomment: �Ƿ�ʹ���û��趨�Ŀ�߱�, ΪTRUEʱ��u32UserAspectWidth��u32UserAspectHeight��Ч */
    U32       u32UserAspectWidth;            /**<CNcomment: �û�������ʾ����Ƶ�������ֵ��Χ��0~3840֮�� 0����ʹ����ƵԴ�ֱ��� */
    U32       u32UserAspectHeight;           /**<CNcomment: �û�������ʾ����Ƶ�߶�����ֵ��Χ��Ҫ��0~3840�ķ�Χ��0����ʹ����ƵԴ�ֱ��� */
}VOUT_WINDOW_USER_DEF_ASPECT_S;

/**Struct of setting parameters of window attribute*/
/**CNcomment:�����������ò���*/
typedef struct _VOUT_WINDOW_SETTINGS_S
{
    VOUT_WINDOW_USER_DEF_ASPECT_S   stWindowUserDefAspect;    /**<user define aspcet for width height>*/
    VOUT_ASPECT_RATIO_E             enAspectRatio;            /**<Aspect ratio , default is VOUT_ASPECT_RATIO_AUTO*//**<CNcomment: Ĭ��ΪVOUT_ASPECT_RATIO_AUTO,�����AUTO,1.�տ�����û������ʱ��,Ӧ����av_default_dispsettings_t::enAspectRatio,2.�����̨,û����,Ӧ�ñ���ԭ�������ò���.*/
    VOUT_ASPECT_RATIO_CONVERSION_E  enAspectRatioConv;        /**<Conversion mode of aspectRatio , default is VOUT_AR_CONVERSION_LETTER_BOX*//**<CNcomment: Ĭ��ΪVOUT_AR_CONVERSION_LETTER_BOX*/
    VOUT_ALPHA_T                    u8Alpha;                  /**<Alpha, range is [VOUT_ALPHA_MIN, VOUT_ALPHA_MAX]*//**<CNcomment: ͸���ȣ���Χ[VOUT_ALPHA_MIN, VOUT_ALPHA_MAX].*/
    U8                              u8Brightness;             /**<To adjust the luminance intensity of the display video image.This value is unsigned and scaled between VOUT_BRIGHTNESS_MIN to VOUT_BRIGHTNESS_MAX.Default value are (VOUT_BRIGHTNESS_MAX/2).*//**<CNcomment: ����,��Χ��[VOUT_BRIGHTNESS_MIN, VOUT_BRIGHTNESS_MAX], Ĭ��ΪVOUT_BRIGHTNESS_MAX/2.*/
    U8                              u8Contrast;               /*<To adjust the relative difference between higher and lower intensity luminance values of the display image.This value is unsigned and scaled between VOUT_CONTRAST_MIN to VOUT_CONTRAST_MAX.Default value are (VOUT_CONTRAST_MAX/2).*//**<CNcomment: �Աȶ�,��Χ��[VOUT_CONTRAST_MIN, VOUT_CONTRAST_MAX], Ĭ��ΪVOUT_CONTRAST_MAX/2.*/
    U8                              u8Saturation;             /**<To adjust the color intensity of the displayed video image.This value is unsigned and scaled between VOUT_SATURATION_MIN to VOUT_SATURATION_MAX.Default value are (VOUT_SATURATION_MAX/2).*//**<CNcomment: ���Ͷ�,��Χ��[VOUT_SATURATION_MIN, VOUT_SATURATION_MAX], Ĭ��ΪVOUT_SATURATION/2.*/
    BOOL                            bVirtual;                 /**<is virtual window*//**<CNcomment: �Ƿ�Ϊ����window */
} VOUT_WINDOW_SETTINGS_S;

/**frame addr.*//**CNcomment: ֡��ַ*/
typedef struct _VOUT_FRAME_ADDR_S
{
    U32             u32YAddr;        /**<Address of the Y component in the current frame*/ /**<CNcomment: ��ǰ֡Y�������ݵĵ�ַ*/
    U32             u32CAddr;        /**<Address of the C component in the current frame*/ /**<CNcomment: ��ǰ֡C�������ݵĵ�ַ*/
    U32             u32CrAddr;       /**<Address of the Cr component in the current frame*/ /**<CNcomment: ��ǰ֡Cr�������ݵĵ�ַ*/

    U32             u32YStride;      /**<Stride of the Y component*/ /**<CNcomment: Y�������ݵĿ��*/
    U32             u32CStride;      /**<Stride of the C component*/ /**<CNcomment: C�������ݵĿ��*/
    U32             u32CrStride;     /**<Stride of the Cr component*/ /**<CNcomment: Cr�������ݵĿ��*/
} VOUT_FRAME_ADDR_S;

/**Defines the frame rate of the video stream.*/
/**CNcomment: ������Ƶ����֡�ʽṹ*/
typedef struct _VOUT_VCODEC_FRMRATE_S
{
    U32 u32fpsInteger;               /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ���������, fps */
    U32 u32fpsDecimal;               /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*/
                                     /**<CNcomment: ������֡�ʵ�С�����֣�����3λ��, fps */
} VOUT_VCODEC_FRMRATE_S;

/**Defines the video format.*/
/**CNcomment: ������Ƶ��ʽö��*/
typedef enum _VOUT_VIDEO_FORMAT_E
{
    VOUT_FORMAT_YUV_SEMIPLANAR_422 = 0,   /**<The YUV spatial sampling format is 4:2:2.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:2*/
    VOUT_FORMAT_YUV_SEMIPLANAR_420,       /**<The YUV spatial sampling format is 4:2:0, V first.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:0��V�ڵ�λ*/
    VOUT_FORMAT_YUV_SEMIPLANAR_400,
    VOUT_FORMAT_YUV_SEMIPLANAR_411,
    VOUT_FORMAT_YUV_SEMIPLANAR_422_1X2,
    VOUT_FORMAT_YUV_SEMIPLANAR_444,
    VOUT_FORMAT_YUV_SEMIPLANAR_420_UV,    /**<The YUV spatial sampling format is 4:2:0,U first.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:0, U�ڵ�λ*/
    VOUT_FORMAT_YUV_PACKAGE_UYVY,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is UYVY.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪUYVY*/
    VOUT_FORMAT_YUV_PACKAGE_YUYV,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YUYV.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYUYV*/
    VOUT_FORMAT_YUV_PACKAGE_YVYU,         /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YVYU.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYVYU*/
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
/**CNcomment: ������Ƶ֡��ģʽö��*/
typedef enum _VOUT_VIDEO_FIELD_MODE_E
{
    VOUT_VIDEO_FIELD_ALL = 0,    /**<Frame mode*/ /**<CNcomment: ֡ģʽ*/
    VOUT_VIDEO_FIELD_TOP,        /**<Top field mode*/ /**<CNcomment: ����ģʽ*/
    VOUT_VIDEO_FIELD_BOTTOM,     /**<Bottom field mode*/ /**<CNcomment: �׳�ģʽ*/
    VOUT_VIDEO_FIELD_BUTT
} VOUT_VIDEO_FIELD_MODE_E;

/**Defines 3D frame packing type*//**CNcomment: 3D framepacking֡����*/
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

/**frame info*//**CNcomment: ֡��Ϣ*/
typedef struct _VOUT_FRAME_INFO_S
{
    U32                                       u32FrameIndex;         /**<Frame index ID of a video sequence, for debug*/ /**<CNcomment: ��Ƶ�����е�֡�����ţ�������*/
    VOUT_FRAME_ADDR_S                         stVideoFrameAddr[2];   /**<Frame addr info, maybe need two items for 3d*/ /**<CNcomment: ֡��ַ��Ϣ����3d������Ҫ����*/
    U32                                       u32Width;              /**<Width of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    U32                                       u32Height;             /**<Height of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    S64                                       s64SrcPts;             /**<Original PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ԭʼʱ���*/
    S64                                       s64Pts;                /**<PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ʱ���*/
    U32                                       u32AspectWidth;        /**<Aspect width*/ /**<CNcomment: �������*/
    U32                                       u32AspectHeight;       /**<Aspect height*/ /**<CNcomment: �����߶�*/
    VOUT_VCODEC_FRMRATE_S                     stFrameRate;           /**<Frame rate*/ /**<CNcomment: ֡��*/

    VOUT_VIDEO_FORMAT_E                       enVideoFormat;         /**<Video YUV format*/ /**<CNcomment: ��ƵYUV��ʽ*/
    BOOL                                      bProgressive;          /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: ������ʽ(����/����) */
    VOUT_VIDEO_FIELD_MODE_E                   enFieldMode;           /**<Frame or field encoding mode*/ /**<CNcomment: ֡�򳡱���ģʽ*/
    BOOL                                      bTopFieldFirst;        /**<Top field first flag*/ /**<CNcomment: �������ȱ�־*/
    VOUT_VIDEO_FRAME_PACKING_TYPE_E           enFramePackingType;    /**<3D frame packing type*/
    U32                                       u32Circumrotate;       /**<Need circumrotate, 1 need *//**<CNcomment: ��ת��־*/
    BOOL                                      bVerticalMirror;       /**<vertical mirror flag *//**<CNcomment: ��ֱ�����־*/
    BOOL                                      bHorizontalMirror;     /**<horizontal mirror flag *//**<CNcomment: ˮƽ�����־*/
    U32                                       u32DisplayWidth;       /**<Width of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    U32                                       u32DisplayHeight;      /**<Height of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    U32                                       u32DisplayCenterX;     /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����x���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    U32                                       u32DisplayCenterY;     /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����y���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    U32                                       u32ErrorLevel;         /**<Error percentage of a decoded picture, ranging from 0% to 100%*/ /**<CNcomment: һ������ͼ���еĴ��������ȡֵΪ0��100*/
    BOOL                                      bSecurityFrame;        /**<Security frame flag*/ /**<CNcomment: ��ȫ֡��־*/
    U32                                       u32Private[32];
} VOUT_FRAME_INFO_S;

/**Defines of window switch mode.*//**CNcomment: ���崰���л�ģʽ*/
typedef enum _VOUT_WINDOW_SWITCH_MODE_E
{
    VOUT_WINDOW_SWITCH_MODE_FREEZE = 0,             /**<Freeze the last frame *//**<CNcomment: ��֡*/
    VOUT_WINDOW_SWITCH_MODE_BLACK,                  /**<Show black screen *//**<CNcomment: ����*/
    VOUT_WINDOW_SWITCH_MODE_BUTT
} VOUT_WINDOW_SWITCH_MODE_E;

#ifdef HAL_HISI_EXTEND_H

/**Defines the type of VOUT invoke.*/
/**CNcomment: ����VOUT Invoke�������͵�ö�� */
typedef enum _VOUT_INVOKE_E
{
    VOUT_INVOKE_REG_CALLBACK = 0x0,                 /**<Invoke command to register vout callback*//**<CNcomment: ע��vout���ⲿ�����Ļص��ӿ� */

    VOUT_INVOKE_BUTT
} VOUT_INVOKE_E;

#endif

#ifdef ANDROID_HAL_MODULE_USED
/**Video output module structure(Android require)*/
/**CNcomment:��Ƶ���ģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _VOUT_MODULE_S
{
    struct hw_module_t stCommon;
} VOUT_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_VOUT */
/** @{ */  /** <!-- [HAL_VOUT] */

/**Video output device structure*//** CNcomment:��Ƶ����豸�ṹ */
typedef struct _VOUT_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief Video output init.CNcomment:��Ƶ�����ʼ�� CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: �ڳ�ʼ��֮ǰ, ����������������ȷ����, �ظ�����init �ӿ�,����SUCCESS. CNend
    \param[in] pstInitParams Vout module init param.CNcomment:��ʼ��ģ����� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_INIT_FAILED  other error.CNcomment:�������� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_init)(struct _VOUT_DEVICE_S* pstVoutDev, const VOUT_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief bind one DISP channel to another. CNcomment:������DISPLAYͨ���� CNend
    \attention \n
    Please finish the bind operation before the DISP channel has been open, and currently we only support HD channel attach to SD channel.
    CNcomment: Ŀǰֻ֧�ֽ�����DISPͨ���󶨵�����DISPͨ���ϣ��󶨲���������DISPͨ����ǰ���. CNend
    \param[in] enDstDisp Destination DISP channel.CNcomment:Ŀ��DISPLAYͨ�� CNend
    \param[in] enSrcDisp source DISP channel.CNcomment:ԴDISPLAYͨ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_DISPLAY_CHANNEL_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_channel_bind)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_DISPLAY_CHANNEL_E enDstDisp, VOUT_DISPLAY_CHANNEL_E enSrcDisp);

    /**
    \brief unbind DISP channel. CNcomment:������DISPLAYͨ����� CNend
    \attention \n
    should close the DISP channels, before do unbind operation.
    CNcomment: ֻ���ڹر�DISPͨ���󣬲��ܽ��н�󶨲���. CNend
    \param[in] enDstDisp Destination DISP channel.CNcomment:Ŀ��DISPLAYͨ�� CNend
    \param[in] enSrcDisp source DISP channel.CNcomment:ԴDISPLAYͨ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_DISPLAY_CHANNEL_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_channel_unbind)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_DISPLAY_CHANNEL_E enDstDisp, VOUT_DISPLAY_CHANNEL_E enSrcDisp);

    /**
    \brief Open a video output instance.CNcomment:��һ����Ƶ���ʵ�� CNend
    \attention \n
    CNcomment: ��CNend
    \param[in] pstOpenParams Open param.CNcomment:ʵ���򿪲��� CNend
    \param[out] phVout Return VOUT handle .CNcomment:����VOUT��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_VO_OPEN_FAILED  other error.CNcomment:�������� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_OPEN_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_open_channel)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE* const phVout, const VOUT_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief Close a video output instance.CNcomment:�ر�һ����Ƶ���ʵ�� CNend
    \attention \n
    CNcomment: ��CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstCloseParams Close param.CNcomment:ʵ���رղ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_CLOSE_FAILED  other error.CNcomment:�������� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_CLOSE_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_close_channel)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief Terminate video output module. CNcomment:ģ����ֹ CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: �ظ�term ����SUCCESS. CNend
    \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:��ֹģ�������ΪNULL  ��ʾǿ����ֹ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_TERM_FAILED  other error.CNcomment:�������� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_TERM_PARAM_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_term)(struct _VOUT_DEVICE_S* pstVoutDev, const VOUT_TERM_PARAM_S* const  pstTermParams);

    /**
    \brief Get the capability of video ouput module. CNcomment:��ȡģ���豸���� CNend
    \attention \n
    CNcomment: ��CNend
    \param[out] pstCapability Capability param.CNcomment:ģ���������� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_CAPABILITY_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_capability)(struct _VOUT_DEVICE_S* pstVoutDev, VOUT_CAPABILITY_S* const pstCapability);

    /**
    \brief Config the callback attribute of VOUT event. CNcomment:����ĳһVOUT�¼��Ĳ��� CNend
    \attention \n
    The function can execute regist/remove/disable/enable
    1.Each event can register callback function and set it's config independently.
    2.Callback function bind with VOUT handle.
    3.Only one callback function can be registered for a vout event on the same vout handle, so the callback function will be recovered.
    CNcomment: ͨ������������ִ�еĲ�����regist/remove/disable/enable
    1. ÿ���¼������Զ���ע��������Լ��Ļص�����.
    2. �ص�������handle��.
    3. ͬһ��handle, һ���¼�ֻ��ע��һ���ص�����,��:����ע��Ļص������Ḳ��ԭ�еĻص�����.
    CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstCfg Config param.CNcomment:�¼����ò��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_EVT_CONFIG_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_evt_config)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_EVT_CONFIG_PARAMS_S* const pstCfg);

    /**
    \brief Get the config of a VOUT event. CNcomment:��ȡĳһvout�¼������ò��� CNend
    \attention \n
    CNcomment: ��CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] enEvt VOUT event type.CNcomment:VOUT�¼����� CNend
    \param[in] pstCfg Config param.CNcomment:�¼����ò��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_EVT_CONFIG_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_evt_config)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_EVT_E enEvt, VOUT_EVT_CONFIG_PARAMS_S*   const pstCfg);

    /**
    \brief Disable video output channel. CNcomment:�ر���ʾͨ�� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] enOutChannel Output channel need to be mute.CNcomment:��Ҫ�ر������ͨ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_OUTPUT_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_outputchannel_mute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_OUTPUT_TYPE_E enOutChannel);

    /**
    \brief Enable video output channel. CNcomment:����ʾͨ�� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] enOutChannel Output channel need to be unmute.CNcomment:��Ҫ�������ͨ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_OUTPUT_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_outputchannel_unmute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_OUTPUT_TYPE_E enOutChannel);

    /**
    \brief Set display param. CNcomment:������ʾ���� CNend
    \attention \n
    Get display param first, and then renew the param, then set.
    CNcomment: �޸�display����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥCNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstSettings Display param.CNcomment:��ʾ���� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_DISPSETTING_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_display_set)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const VOUT_DISPSETTING_S* const pstSettings);

    /**
    \brief Get display param. CNcomment:��ȡ��ʾ���� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstSettings Display param.CNcomment:��ʾ���� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_TERM_PARAM_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_display_get)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, VOUT_DISPSETTING_S* const pstSettings);

    /**
    \brief Start CGMS. CNcomment:CGMS���� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] enCgmsType CGMS type.CNcomment:CGMS ���� CNend
    \param[in] enCopyRight Copy right.CNcomment:������� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_VBI_CGMS_TYPE_E, VOUT_VBI_CGMS_A_COPY_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_cgms_start)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout,  VOUT_VBI_CGMS_TYPE_E enCgmsType, VOUT_VBI_CGMS_A_COPY_E enCopyRight);

    /**
    \brief Stop CGMS. CNcomment:CGMSֹͣ CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_cgms_stop)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout);

    /**
    \brief Microvision config CNcomment:Microvision ���� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pu8MvData Config data.CNcomment:�������� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_microvision_setup)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout,  U8* pu8MvData);

    /**
    \brief Microvision enable switch CNcomment:Microvision ��/�ر� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] bEnable Enable switch.CNcomment:1��/0�ر�CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_vbi_microvision_enable)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, BOOL bEnable);

    /**
    \brief Set HDCP params. CNcomment:����HDCP ���� CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pvData Data.CNcomment:���� CNend
    \param[in] u32Length Data.CNcomment:���ݳ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_hdcp_params)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, void* const pvData, const U32 u32Length);

    /**
    \brief Get status of HDCP. CNcomment:��ȡHDCPУ��״̬ CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[out] pu32Success HDCP status.CNcomment:HDCP״̬ CNend
    0:Default key and app setting key all check failed, or HDMI unconnected.
    1:App setting key check success, do not use default success.
    2::App setting key check failed, use default key.
    3:No HDCP key.
    4:HDCP disabled.
    CNcomment:
    HDCPУ��״̬
    0:APP���õ�KEY���ڲ�Ĭ�ϵ�KEY��У��ʧ�ܣ�����HDMIû����
    1:APP���õ�KEYУ��ɹ���û��ʹ��Ĭ��KEY
    2:APP���õ�KEYУ��ʧ�ܣ�ʹ��Ĭ�ϵ�KEYУ��ɹ�
    3:û��HDCP key
    4:HDCP ����û�д�.
    CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_hdcp_status)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, U32* pu32Success);

    /**
    \brief Get EDID information. CNcomment:��ȡEDIDԭʼ���� CNend
    \attention \n
    The buffer allocated externally, buffer size must be 512.
    CNcomment:
    ��ȡԭʼEDID���ݵ� buffer, EDID�汾��ͬ,������������Ҳ��ͬ.
    ���������512 BYTE,���buffer �ĳ�����С��512BYTE,������Ҫ�Լ�����
    CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[out] pu8EdidBuf Data buffer.CNcomment:���ݻ���CNend
    \param[out] pu32EdidLen Data length.CNcomment:����ԭʼEDID���ݳ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_VO_OP_FAILED  Operation fail.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_edid)(const HANDLE hVout, U8* const pu8EdidBuf, U32* const pu32EdidLen);

    /**
    \brief Set background color of video window. CNcomment:������Ƶ���ڵı�����ɫ CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstVoutBgColor Background color info.CNcomment:������ɫ��Ϣ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_BG_COLOR_S

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_bg_color)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_BG_COLOR_S* pstVoutBgColor);

    /**
    \brief Get background color of video window. CNcomment:��ȡ��Ƶ���ڵı�����ɫCNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[out] pstVoutBgColor Background color info.CNcomment:������ɫ��Ϣ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_bg_color)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_BG_COLOR_S* pstVoutBgColor);

    /**
    \brief Set DISP 3D format. CNcomment:����3D  ģʽ CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] en3dMode 3D mode.CNcomment:3D  ģʽ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::VOUT_3D_MODE_E

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_3dmode)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_3D_MODE_E en3dMode);

    /**
    \brief Get DISP 3D format. CNcomment:��ѯDISP��3D��ʽCNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[out] pen3dMode Current 3D mode.CNcomment:��ǰ3D  ģʽ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_get_3dmode)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, VOUT_3D_MODE_E* pen3dMode);

    /**
    \brief Swap left and right eye of 3D output. CNcomment:����3D����һ��� CNend
    \attention \n
    Only take effect in 3D output mode. CNcomment: ����3D���ʱ��Ч CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[out] u32Switch Right-Eye-First.CNcomment:������������ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_set_3d_lr_switch)(struct _VOUT_DEVICE_S* pstVoutDev, HANDLE hVout, U32 u32Switch);

    /**
    \brief Auto detect 3d format. CNcomment:�Զ����3D ģʽCNend
    \attention \n
    This interface maybe cost 1~2 seconds. CNcomment: ����ӿڿ�����Ҫ1~2  ��ʱ�� CNend
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] hVoutWindow VOUT window handle.CNcomment:VOUT ���ھ�� CNend
    \param[out] pen3dFormat Rturn 3D mode.CNcomment:����3D ģʽ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_autodetect3dformat )(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_3D_FORMAT_E* pen3dFormat);

    /**
    \brief Create a video output window. CNcomment:����һ����ʾ����CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] pstCreateParams Create param.CNcomment:�������� CNend
    \param[out] phVoutWindow Return window handle.CNcomment:���ش��ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_create)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, HANDLE* const phVoutWindow, const VOUT_WINDOW_CREATE_PARAMS_S* const pstCreateParams);

    /**
    \brief Destroy a video output window. CNcomment:����һ����ʾ����CNend
    \attention \n
    \param[in] hVout VOUT handle.CNcomment:VOUT ��� CNend
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:���ٲ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_destroy)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVout, const HANDLE hVoutWindow, const VOUT_WINDOW_DESTROY_PARAM_S* const pstDestroyParams);

    /**
    \brief Set window param. CNcomment:����window����CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] pstSettings Window setting param.CNcomment:���ò���   CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const VOUT_WINDOW_SETTINGS_S* const pstSettings);

    /**
    \brief Get window param. CNcomment:����window����CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] pstSettings Return window setting param.CNcomment:���ò���   CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_SETTINGS_S* const pstSettings);

    /**
    \brief Set window input size. CNcomment:������Ƶ���봰�ڵĴ�СCNend
    \attention \n
    Conventions are as follows:
    1.TODO û����������˵�Ĳ���.
    2.TODO û����������˵�Ĳ���.
    3.TODO?
    4.If u32Width is 0, set full screen width.(HD:1920,SD:720).
    5.If u32Height is 0, set full screen height.(HD:1080,SD:576).
    6.TODO û��channel ����
    7.TODO û��channel ����
    8.If iframe displayed on the video layer, the parameters are useful for iframe, if iframe displayed on other layer, set parameters to other layer.
    9.The parameters is used to clip video window.
    10.If the parameters are over range, HDI  should auto correct them to valid range.
    CNcomment:����֧�ֻ������ͨ��Լ������:
    1. �������Ϊ������,ֻҪ��һ��������֧�ֵ�����,���سɹ�.
        �������ƽ̨,��������:AV_CHANNEL_HD|AV_CHANNEL_SD ʱ, ���سɹ�.
    2. ����������ǻ����Ͷ��Ҳ�����ƽ̨֧�����Ͳ�ƥ��,����ERROR_FEATURE_NOT_SUPPORTED.
        �������ƽ̨,��������AV_CHANNEL_HD ʱ,����ERROR_FEATURE_NOT_SUPPORTED.CNend
    3. ����������1080IΪ׼, ����������PAL��Ϊ׼.
        �����ǰ��ʽHD ����1080I, SD ����PAL,��ôHDI���������ת���ɵ�ǰ��ʽ������.
    4. ���Ϊ������ȫ�����.(HD:1920,SD:720)
    5. �߶�Ϊ������ȫ���߶�(HD:1080,SD:576)
    6. channel ���Ե�������һ��ͨ��,Ҳ���Ի����,
    7. ���channel=AV_CHANNEL_HD |    AV_CHANNEL_SD, ��
        ����Ĳ��������ø���ͨ�������봰�ڵĴ�С,(��1080IΪ׼).
        ����ͨ��HDI ������ݵ�ǰ��ʽ�Զ�����������.
    8. ���iframe��video��,�˺�����iframeͬ��������,����iframe����������������Ҫ�����ڽ��в����
    9. ��Ҫ������Ƶ���ڲü�
    10. �������ʹ��ڴ�С����������Χ,HDI�Զ�����������Χ.    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] s32Left X coordinate of window top left corner.CNcomment:�������Ͻ�X���� CNend
    \param[in] s32Top Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[in] u32Width Window width.CNcomment:���ڿ�� CNend
    \param[in] u32Height Window height.CNcomment:���ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_input_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                      AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get window input size. CNcomment:��ȡ��Ƶ���봰�ڵĴ�СCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:���ش������Ͻ�X���� CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[out] pu32Width Return window width.CNcomment:���ش��ڿ�� CNend
    \param[out] pu32Height Return window height.CNcomment:���ش��ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_input_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                      AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Set video output window size. CNcomment:������Ƶ������ڵĴ�СCNend
    \attention \n

    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] s32Left Return X coordinate of window top left corner.CNcomment:�������Ͻ�X���� CNend
    \param[in] s32Top Return Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[in] pu32Width Return window width.CNcomment:���ڿ�� CNend
    \param[in] pu32Height Return window height.CNcomment:���ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_output_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get vieo output window size. CNcomment:��ȡ��Ƶ������ڵĴ�СCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:���ش������Ͻ�X���� CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[out] pu32Width Return window width.CNcomment:���ش��ڿ�� CNend
    \param[out] pu32Height Return window height.CNcomment:���ش��ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_output_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Set video content window size. CNcomment:������Ƶ���ݴ��ڵĴ�СCNend
    \attention \n
    Video content window in the video output window, include video display effective area, does not include the black side,
    in some platform,  video content  window is equivalent to the video output window
    CNcomment: ��Ƶ���ݴ���ָ����Ƶ��������ڳ�ȥ�ڱ������ʾ��Ƶ��Ч���ݵ�����
                        ��Щƽ̨��Ƶ���ݴ��ڵ�ͬ����Ƶ�������CNend
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] s32Left Return X coordinate of window top left corner.CNcomment:�������Ͻ�X���� CNend
    \param[in] s32Top Return Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[in] pu32Width Return window width.CNcomment:���ڿ�� CNend
    \param[in] pu32Height Return window height.CNcomment:���ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_video_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T s32Left, AV_COORD_T s32Top, U32 u32Width, U32 u32Height);

    /**
    \brief Get window output size. CNcomment:��ȡ��Ƶ���ݴ��ڵĴ�СCNend
    \attention \n
    Video content window in the video output window, include video display effective area, does not include the black side,
    in some platform,  video content  window is equivalent to the video output window
    CNcomment: ��Ƶ���ݴ���ָ����Ƶ��������ڳ�ȥ�ڱ������ʾ��Ƶ��Ч���ݵ�����
                        ��Щƽ̨��Ƶ���ݴ��ڵ�ͬ����Ƶ�������CNend
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] ps32Left Return X coordinate of window top left corner.CNcomment:���ش������Ͻ�X���� CNend
    \param[out] ps32Top Return Y coordinate of window top left corner.CNcomment:�������Ͻ�Y���� CNend
    \param[out] pu32Width Return window width.CNcomment:���ش��ڿ�� CNend
    \param[out] pu32Height Return window height.CNcomment:���ش��ڸ߶� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_video_rect)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow,
                                       AV_COORD_T* const ps32Left, AV_COORD_T* const ps32Top, U32* const pu32Width, U32* const pu32Height);

    /**
    \brief Get window status. CNcomment:��ȡ��Ƶ����״̬CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] pstStatus Return status of window.CNcomment:���ش���״̬ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_status)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_STATUS_S* const  pstStatus);

    /**
    \brief Freeze the video on a Window. CNcomment:������ƵCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_freeze)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief UnFreeze the video on a Window. CNcomment:�ָ��������Ƶ����CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_unfreeze)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Freeze/unfreeze the video on a window with mode. CNcomment:����/�����Ƶ����CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] bFreezeEnable whether to freeze window.CNcomment:ʹ��/��ֹ��־ CNend
    \param[in] enFreezeMode the mode of freeze.CNcomment:����ķ�ʽ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_freeze_ex)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bFreezeEnable, VOUT_WINDOW_STOP_MODE_E enFreezeMode);

    /**
    \brief pause the video on a window. CNcomment:��ͣ��Ƶ����CNend
    \attention \n
    pause��freeze����������:pause��ͣ��Ļ��ʾ�ͻ��棬freezeֻ������Ļ��ʾ��
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] enPauseMode the mode of freeze.CNcomment:��ͣ�ķ�ʽ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_pause)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_STOP_MODE_E enPauseMode);

    /**
    \brief resume the video on a window. CNcomment:�ָ���Ƶ������ʾCNend
    \attention \n
    vout_window_resume��vout_window_pause���ʹ�á�
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_resume)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Set mute of video window. CNcomment:�رմ������CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_mute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Set unmute of video window. CNcomment:�򿪴������CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_unmute)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow);

    /**
    \brief Attach the window with video source. CNcomment:����������ƵԴ��CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] hSource Video source handle.CNcomment:��ƵԴ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_attach_input)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const HANDLE hSource);

    /**
    \brief Detach the window with video source. CNcomment:����������ƵԴ���CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] hSource Video source handle.CNcomment:��ƵԴ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_detach_input)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, const HANDLE hSource);

    /**
    \brief Set backgroud color when window has been muted. CNcomment:���ô�������رպ�ı�����ɫCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] pstRGBColorpstRGBColor: video mute color of video window.
                   pstRGBColor->u32Blue: actually use BIT[1~0];
                   pstRGBColor->u32Green: actually use BIT[2~0];
                   pstRGBColor->u32Red: actually use BIT[2~0];
                   CNcomment:��������رպ�ı�����ɫ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_mute_color)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_RGB_COLOR_S* pstRGBColor);

    /**
    \brief Enabe /disable  Film mode. CNcomment:�򿪻�رյ�ӰģʽCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] bEnable TRUE: enable film mode, FALSE, disable film mode.CNcomment:TRUE: �򿪵�Ӱģʽ, FALSE, �رյ�ӰģʽCNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_enable_filmmode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bEnable);

    /**
    \brief Set Color temerature of a Window. CNcomment:���ô��ڵ�ɫ��CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] pstColorTemperature Color temerature data.CNcomment:ɫ������CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_WIN_NOT_CREATED  Window has not been created.CNcomment:����δ������CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_colortemperature)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_COLOR_TEMPERATURE_S* pstColorTemperature);

    /**
    \brief Set zorder of video window. CNcomment:���ô��ڵ�����˳��CNend
    \attention \n
    if u32ZOrderIndex > current zorder move forward, else zorder move backward��
    CNcomment:�������u32ZOrderIndex ���ڴ���Ŀǰ˳���򴰿������ƶ������������ƶ� CNend
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] u32ZOrderIndex  ZOrder of video window.CNcomment:���ڵ�����˳��CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_zorder)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 u32ZOrderIndex);

    /**
    \brief Set window mode panorama. CNcomment:����ȫ��ģʽCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] bEnable: TRUE, enable panorama.  FALSE,not use panorama.CNcomment:TRUE: ʹ�ܣ�FALSE:ȡ��ʹ��CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_enable_panorama)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bEnable);

    /**
    \brief Send video frame to display. CNcomment:��Ƶ֡����ʾCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] pstFrameInfo: video frame info.CNcomment:��Ƶ֡��ϢCNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::ERROR_VO_WIN_BUFQUE_FULL bufque full.CNcomment:֡����������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_queue_frame)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_FRAME_INFO_S *pstFrameInfo);

    /**
    \brief Get back video display frame. CNcomment:������Ƶ��ʾ֡CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] u32TimeOut: time out.CNcomment:��ʱֵ���ڳ�ʱ��Χ�ڵȴ��ɻ��յ���ʾ֡CNend
    \param[out] pstFrameInfo: can get back video frame info.CNcomment:�ɻ��յ���Ƶ֡��ϢCNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error, such as timeout.CNcomment:�������󣬰�����ʱ�� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_dequeue_frame)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_FRAME_INFO_S *pstFrameInfo, U32 u32TimeOut);

    /**
    \brief Window switch mode. CNcomment:�����л�ģʽCNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] enWindowSwitchMode: window switch mode.CNcomment:�����л�ģʽCNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_reset)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, VOUT_WINDOW_SWITCH_MODE_E enWindowSwitchMode);

   /**
    \brief Window switch mode. CNcomment:��ȡ���ⴰ�ڿ��CNend
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] uVirtualScreenW: window width.CNcomment:���ڿ�
    \param[out] uVirtualScreenH: window width.CNcomment:���ڸ�
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_virtual_size)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 *const uVirtualScreenW, U32 *const uVirtualScreenH);

    /**
    \brief Get current play information of window. CNcomment:��ȡ���ڵ�ǰ�Ĳ�����Ϣ
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] u32DelayTime: window width.CNcomment:��ǰ����һ֡���ж�û���ʾ
    \param[out] u32DispRate: window width.CNcomment:��ʾ֡��
    \param[out] u32FrameNumInBufQn: window width.CNcomment:window�������м�֡
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_playinfo)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32 *const u32DelayTime, U32 *const u32DispRate, U32 *const u32FrameNumInBufQn);

    /**
    \brief set the work mode of window: quick output or not. CNcomment:���ô����Ƿ����ڿ������ģʽ
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] bQuickOutputEnable whether determine the quick output mode of window.CNcomment:�������ģʽʹ��/��ֹ��־ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_set_quick_output_mode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bQuickOutputEnable);

    /**
    \brief get the work mode of window: quick output or not. CNcomment:��ȡ�����Ƿ����ڿ������ģʽ
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[out] pbQuickOutputEnable whether determine the output mode of window.CNcomment:ָ�����ͣ�ָ��������ģʽʹ��/��ֹ��־ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_get_quick_output_mode)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL* pbQuickOutputEnable);

    /**
     \brief Get the delay time of current frame, unit: ms.CNcomment:��ǰ����һ֡���ж�û���ʾ����λ: ms
     \attention \n
     \param[in] hVoutWindow window handle.CNcomment:window ��� CNend
     \param[out] pu32Latency Return the delay time of current frame.CNcomment:���ص�ǰ����һ֡���ж�û���ʾ CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*vout_window_get_latency)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, U32* pu32Latency);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Window close HDR path. CNcomment:�ر�HDRͨ·
    \attention \n
    \param[in] hVoutWindow Window handle.CNcomment:���ھ�� CNend
    \param[in] bCloseHdrPath: close HDR path or not:�Ƿ�ر�HDRͨ·
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_VO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*vout_window_close_hdr_path)(struct _VOUT_DEVICE_S* pstVoutDev, const HANDLE hVoutWindow, BOOL bCloseHdrPath);

    /**
    \brief vout invoke function, extend other function by user.
    CNcomment:invoke ��չ�ӿڣ������û�˽�й�����չ
    \attention \n
    None
    \param[in] hInvokeHandle the handle of Invoke Command, vout handle or window handle.CNcomment:Invloke������Ҫ�ľ����vout����򴰿ھ�� CNend
    \param[in] eCmd Invoke ID, defined is ::VOUT_INVOKE_E.CNcomment:Invoke ID, ������� ::VOUT_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
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
\brief direct get vout device api, for linux and android.CNcomment:��ȡ��Ƶ����豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get vout device api��for linux and andorid.
CNcomment:��ȡ��Ƶ����豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  vout device pointer when success.CNcomment:�ɹ�����vout�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::VOUT_DEVICE_S

\par example
*/
VOUT_DEVICE_S* getVoutDevice();

/**
\brief  Open HAL Video output module device.CNcomment:��HAL��Ƶ���ģ���豸CNend
\attention \n
Open HAL Video output module device(for compatible Android HAL).
CNcomment:��HAL��Ƶ���ģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice Video output device structure.CNcomment:��Ƶ����豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other system error.CNcomment:������Ƶ������� CNend
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
\brief Close HAL Video output module device.CNcomment:�ر�HAL��Ƶ���ģ���豸 CNend
\attention \n
Close HAL Video output module device(for compatible android HAL).
CNcomment:�ر�HAL��Ƶ���ģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstDevice Video output device structure.CNcomment:��Ƶ����豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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

