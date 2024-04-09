/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name          : hifb_debug.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : CNcomment: fb��Ҫʹ�õĽӿ�ʵ�֣����ִ����ͳһ��CNend\n
Function List      :
History            :
Date                           Author                       Modification
2018/01/01                     sdk                          Created file
***************************************************************************************************/
#ifndef __HIFB_DEBUG_H__
#define __HIFB_DEBUG_H__

/*********************************add include here*************************************************/
#include "hi_type.h"
#include "uboot.h"
#include "hi_drv_pdm.h"


/***************************** Macro Definition ***************************************************/
#define DISPLAY_BUFFER_HD       "HIFB_DispBuf_HD"
#define DISPLAY_BUFFER_SD       "HIFB_DispBuf_SD"
#define OPTM_GFX_WBC2_BUFFER    "HIFB_GfxWbc2"
#define HIFB_ZME_COEF_BUFFER    "HIFB_ZmeCoef"

#define HZ 1
#define init_waitqueue_head(...)                         do { } while (0)
#define wait_event_interruptible_timeout(...)            0
#define wake_up_interruptible(...)                       do { } while (0)
#define create_workqueue(...)                            do { } while (0)
#define INIT_WORK(...)                                   do { } while (0)
#define queue_work(...)                                  do { } while (0)
#define destroy_workqueue(...)                           do { } while (0)
typedef int wait_queue_head_t;

/*************************** Structure Definition *************************************************/
typedef enum
{
    HIFB_LAYER_HD_0 = 0x0,
    HIFB_LAYER_HD_1,
    HIFB_LAYER_HD_2,
    HIFB_LAYER_HD_3,
    HIFB_LAYER_SD_0,
    HIFB_LAYER_SD_1,
    HIFB_LAYER_ID_BUTT
}HIFB_LAYER_ID_E;

typedef enum
{
    HIFB_FMT_RGB565 = 0,
    HIFB_FMT_RGB888,        /**<  RGB888 24bpp */

    HIFB_FMT_KRGB444,       /**<  RGB444 16bpp */
    HIFB_FMT_KRGB555,       /**<  RGB555 16bpp */
    HIFB_FMT_KRGB888,       /**<  RGB888 32bpp */

    HIFB_FMT_ARGB4444,      /**< ARGB4444 */
    HIFB_FMT_ARGB1555,      /**< ARGB1555 */
    HIFB_FMT_ARGB8888,      /**< ARGB8888 */
    HIFB_FMT_ARGB8565,      /**< ARGB8565 */

    HIFB_FMT_RGBA4444,      /**< ARGB4444 */
    HIFB_FMT_RGBA5551,      /**< RGBA5551 */
    HIFB_FMT_RGBA5658,      /**< RGBA5658 */
    HIFB_FMT_RGBA8888,      /**< RGBA8888 */

    HIFB_FMT_BGR565,        /**< BGR565   */
    HIFB_FMT_BGR888,        /**< BGR888   */
    HIFB_FMT_ABGR4444,      /**< ABGR4444 */
    HIFB_FMT_ABGR1555,      /**< ABGR1555 */
    HIFB_FMT_ABGR8888,      /**< ABGR8888 */
    HIFB_FMT_ABGR8565,      /**< ABGR8565 */
    HIFB_FMT_KBGR444,       /**< BGR444 16bpp */
    HIFB_FMT_KBGR555,       /**< BGR555 16bpp */
    HIFB_FMT_KBGR888,       /**< BGR888 32bpp */

    HIFB_FMT_1BPP,          /**<  clut1   */
    HIFB_FMT_2BPP,          /**<  clut2   */
    HIFB_FMT_4BPP,          /**<  clut4   */
    HIFB_FMT_8BPP,          /**< clut8    */
    HIFB_FMT_ACLUT44,       /**< AClUT44  */
    HIFB_FMT_ACLUT88,       /**< ACLUT88  */
    HIFB_FMT_PUYVY,         /**< UYVY     */
    HIFB_FMT_PYUYV,         /**< YUYV     */
    HIFB_FMT_PYVYU,         /**< YVYU     */
    HIFB_FMT_YUV888,        /**< YUV888   */
    HIFB_FMT_AYUV8888,      /**< AYUV8888 */
    HIFB_FMT_YUVA8888,      /**< YUVA8888 */
    HIFB_FMT_BUTT
}HIFB_COLOR_FMT_E;


typedef struct hiHIFB_DEFLICKER_S
{
    HI_U32  u32HDfLevel;    /**<  horizontal deflicker level *//**<CNcomment:ˮƽ����˸���� */
    HI_U32  u32VDfLevel;    /**<  vertical deflicker level *//**<CNcomment:��ֱ����˸���� */
    HI_U8   *pu8HDfCoef;    /**<  horizontal deflicker coefficient *//**<CNcomment:ˮƽ����˸ϵ�� */
    HI_U8   *pu8VDfCoef;    /**<  vertical deflicker coefficient *//**<CNcomment:��ֱ����˸ϵ�� */
}HIFB_DEFLICKER_S;

typedef struct
{
    HI_BOOL bAlphaEnable;   /**<  alpha enable flag *//**<CNcomment:alphaʹ�ܱ�ʶ*/
    HI_BOOL bAlphaChannel;  /**<  alpha channel enable flag *//**<CNcomment:alphaͨ��ʹ��*/
    HI_U8 u8Alpha0;         /**<  alpha0 value, used in ARGB1555 *//**CNcomment:alpha0ȡֵ��ARGB1555��ʽʱʹ��*/
    HI_U8 u8Alpha1;         /**<  alpha1 value, used in ARGB1555 *//**CNcomment:alpha1ȡֵ��ARGB1555��ʽʱʹ��*/
    HI_U8 u8GlobalAlpha;    /**<  global alpha value *//**<CNcomment:ȫ��alphaȡֵ*/
    HI_U8 u8Reserved;
}HIFB_ALPHA_S;

typedef struct
{
    HI_BOOL bKeyEnable;
    HI_BOOL bMaskEnable;
    HI_U32 u32Key;
    HI_U8 u8RedMask;
    HI_U8 u8GreenMask;
    HI_U8 u8BlueMask;
    HI_U8 u8Reserved;
    HI_U32 u32KeyMode;
    HI_U8 u8RedMax;
    HI_U8 u8GreenMax;
    HI_U8 u8BlueMax;
    HI_U8 u8Reserved1;
    HI_U8 u8RedMin;
    HI_U8 u8GreenMin;
    HI_U8 u8BlueMin;
    HI_U8 u8Reserved2;
}HIFB_COLORKEYEX_S;


typedef struct
{
    HI_S32 s32XPos;         /**<  horizontal position *//**<CNcommnet:ˮƽλ�� */
    HI_S32 s32YPos;         /**<  vertical position *//**<CNcomment:��ֱλ�� */
}HIFB_POINT_S;

typedef struct
{
    HI_BOOL bKeyEnable;         /**<Colorkey enable*//**<CNcomment:colorkey �Ƿ�ʹ�� */
    HI_U32 u32Key;              /**<The value is obtained by calling ::hifb_color2key.*//**<CNcomment:��ֵӦ��ͨ��::hifb_color2key�õ�*/
}HIFB_COLORKEY_S;


typedef struct
{
    HI_S32 x, y;    /**<x: horizontal coordinate of the upper left point of the rectangle; y: vertical coordinate of the upper left point of the rectangle*//**<CNcomment: x:�������ϵ������ y:�������ϵ�������*/
    HI_S32 w, h;    /**< w: rectangle width; h: rectangle height*//**<CNcomment: w:���ο�� h:���θ߶�*/
} HIFB_RECT;


typedef enum
{
    HIFB_STEREO_MONO   = 0x0,             /**< Normal output to non-stereoscopic (3D) TV. No L/R content provided to TV*/
    HIFB_STEREO_SIDEBYSIDE_HALF,          /**< L/R frames are downscaled horizontally by 2 andpacked side-by-side into a single frame, left on lefthalf of frame*/
    HIFB_STEREO_TOPANDBOTTOM,             /**< L/R frames are downscaled vertically by 2 andpacked into a single frame, left on top*/
    HIFB_STEREO_FRMPACKING,               /**< one frames are copyed */
    HIFB_STEREO_BUTT
}HIFB_STEREO_MODE_E;


typedef enum
{
    HIFB_STEREO_WORKMODE_HW_FULL = 0x0,      /**< 3d stereo function use hardware and transfer full frame to vo, note: hardware doesn't support this mode if encoder picture delivery method is top and bottom */
    HIFB_STEREO_WORKMODE_HW_HALF,            /**< 3d stereo function use hardware and transfer half frame to vo*/
    HIFB_STEREO_WORKMODE_SW_EMUL,            /**< 3d stereo function use software emulation */
    HIFB_STEREO_WORKMODE_BUTT
}HIFB_STEREO_WORKMODE_E;

typedef enum
{
    HIFB_ZORDER_MOVETOP = 0,  /**< Move to the top*//**<CNcomment:�Ƶ����*/
    HIFB_ZORDER_MOVEUP,       /**< Move upwards*//**<CNcomment:������*/
    HIFB_ZORDER_MOVEBOTTOM,   /**< Move to the bottom*//**<CNcomment:�Ƶ���ײ�*/
    HIFB_ZORDER_MOVEDOWN,     /**< Move downwards*//**<CNcomment:������*/
    HIFB_ZORDER_BUTT
}HIFB_ZORDER_E;

typedef struct
{
    HI_BOOL bKeyAlpha;      /**< whether support colorkey alpha */
    HI_BOOL bGlobalAlpha;   /**< whether support global alpha   */
    HI_BOOL bCmap;          /**< whether support color map      */
    HI_BOOL bHasCmapReg;    /**< whether has color map register */
    HI_BOOL bColFmt[HIFB_FMT_BUTT]; /**< support which color format */
    HI_BOOL bVoScale;       /**< support vo scale*/
    HI_BOOL bLayerSupported;/**< whether support a certain layer, for example:x5 HD support HIFB_SD_0 not support HIFB_SD_1*/
    HI_BOOL bCompression;   /**< whether support compression */
    HI_BOOL bStereo;        /**< whether support 3D Stereo*/
    HI_U32  u32MaxWidth;    /**< the max pixels per line */
    HI_U32  u32MaxHeight;   /**< the max lines */
    HI_U32  u32MinWidth;    /**< the min pixels per line */
    HI_U32  u32MinHeight;   /**< the min lines */
    HI_U32  u32VDefLevel;   /**< vertical deflicker level, 0 means vertical deflicker is unsupported */
    HI_U32  u32HDefLevel;   /**< horizontal deflicker level, 0 means horizontal deflicker is unsupported  */
}HIFB_CAPABILITY_S;


typedef enum
{
    HIFB_SCANMODE_P,
    HIFB_SCANMODE_I,
    HIFB_SCANMODE_BUTT,
}HIFB_SCAN_MODE_E;

typedef enum
{
    HIFB_LAYER_STATE_ENABLE = 0x0,
    HIFB_LAYER_STATE_DISABLE,
    HIFB_LAYER_STATE_INVALID,
    HIFB_LAYER_STATE_BUTT
} HIFB_LAYER_STATE_E;


typedef enum
{
    HIFB_CALLBACK_TYPE_VO         = 0x1,
    HIFB_CALLBACK_TYPE_3DMode_CHG = 0x2,
    HIFB_CALLBACK_TYPE_REGUP      = 0x4,
    HIFB_CALLBACK_TYPE_BUTT,
}HIFB_CALLBACK_TPYE_E;


typedef enum tagHIFB_GFX_MODE_EN
{
    HIFB_GFX_MODE_NORMAL = 0,
    HIFB_GFX_MODE_HD_WBC,
    HIFB_GFX_MODE_BUTT
}HIFB_GFX_MODE_EN;


/********************** Global Variable declaration ***********************************************/


/******************************* API declaration **************************************************/
typedef HI_S32 (* IntCallBack)(HI_VOID *pParaml, HI_VOID *pParamr);


#endif/**__HIFB_DEBUG_H__**/
