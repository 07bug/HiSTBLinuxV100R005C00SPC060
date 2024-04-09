#ifndef __HIFB_H__
#define __HIFB_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include <linux/fb.h>

#include "hi_type.h"
#include "hi_common.h"

/*************************** Macro Definition ****************************/
/** \addtogroup           HIFB   */
/** @{ */  /** <!-- [HIFB] */
#define IOC_TYPE_HIFB       'F'

/**Obtains the colorkey of a graphics layer.*/
/**CNcomment:��ȡͼ��colorkey��Ϣ */
#define FBIOGET_COLORKEY_HIFB                 _IOR(IOC_TYPE_HIFB, 90, HIFB_COLORKEY_S)

/**Sets the colorkey of a graphics layer.*/
/**CNcomment:����ͼ��colorkey��Ϣ */
#define FBIOPUT_COLORKEY_HIFB                  _IOW(IOC_TYPE_HIFB, 91, HIFB_COLORKEY_S)

/**Obtains the alpha values of a graphics layer, including the pixel alpha and global alpha.*/
/**CNcomment:��ȡͼ��alpha��Ϣ,�������غ�ȫ��alpha */
#define FBIOGET_ALPHA_HIFB                     _IOR(IOC_TYPE_HIFB, 92, HIFB_ALPHA_S)

/**Sets the alpha values of a graphics layer, including the pixel alpha and global alpha.*/
/**CNcomment:����ͼ��alpha��Ϣ,�������غ�ȫ��alpha */
#define FBIOPUT_ALPHA_HIFB                     _IOW(IOC_TYPE_HIFB, 93, HIFB_ALPHA_S)

/**Obtains the origin of a graphics layer.*/
/**CNcomment:��ȡͼ����Ļԭ����Ϣ */
#define FBIOGET_SCREEN_ORIGIN_HIFB             _IOR(IOC_TYPE_HIFB, 94, HIFB_POINT_S)

/**Sets the origin of a graphics layer.*/
/**CNcomment:����ͼ����Ļԭ����Ϣ */
#define FBIOPUT_SCREEN_ORIGIN_HIFB             _IOW(IOC_TYPE_HIFB, 95, HIFB_POINT_S)

/**Obtains the anti-flicker status of a graphics layer.*/
/**CNcomment:��ȡͼ�㿹��˸*/
#define FBIOGET_DEFLICKER_HIFB                 _IOR(IOC_TYPE_HIFB, 98, HIFB_DEFLICKER_S)

/**Sets the anti-flicker status of a graphics layer.*/
/**CNcomment:����ͼ�㿹��˸ */
#define FBIOPUT_DEFLICKER_HIFB                 _IOW(IOC_TYPE_HIFB, 99, HIFB_DEFLICKER_S)

/**Waits for the vertical blanking interrupt of a graphics layer.*/
/**CNcomment:�ȴ�ͼ�㴹ֱˮ���ж� */
#define FBIOGET_VBLANK_HIFB                    _IO(IOC_TYPE_HIFB, 100)

/**Sets to display a graphics layer.*/
/**CNcomment:����ͼ����ʾ */
#define FBIOPUT_SHOW_HIFB                      _IOW(IOC_TYPE_HIFB, 101, HI_BOOL)

/**Obtains the display information about a graphics layer.*/
/**CNcomment:��ȡͼ����ʾ��ʾ��Ϣ */
#define FBIOGET_SHOW_HIFB                      _IOR(IOC_TYPE_HIFB, 102, HI_BOOL)

/**Obtains the capability of a graphics layer.*/
/**CNcomment:��ȡͼ������ */
#define FBIOGET_CAPABILITY_HIFB                _IOR(IOC_TYPE_HIFB, 103, HIFB_CAPABILITY_S)

/**enable the decompress */
/**CNcomment:��ѹʹ�� */
#define FBIOPUT_DECOMPRESS_HIFB                _IOR(IOC_TYPE_HIFB, 104, HI_BOOL)

/**Sets the information about a graphics layer.*/
/**CNcomment:����ͼ����Ϣ */
#define FBIOPUT_LAYER_INFO                     _IOW(IOC_TYPE_HIFB, 120, HIFB_LAYER_INFO_S)

/**Obtains the information about a graphics layer.*/
/**CNcomment:��ȡͼ����Ϣ */
#define FBIOGET_LAYER_INFO                     _IOR(IOC_TYPE_HIFB, 121, HIFB_LAYER_INFO_S)

/**Obtains a canvas buffer.*/
/**CNcomment:��ȡcanvas buf */
#define FBIOGET_CANVAS_BUFFER                  _IOR(IOC_TYPE_HIFB, 123, HIFB_SURFACE_S)

/**Refreshes a graphics layer.*/
/**CNcomment:ˢ��ͼ�� */
#define FBIO_REFRESH                           _IOW(IOC_TYPE_HIFB, 124, HIFB_BUFFER_S)

/**sync refresh*/
#define FBIO_WAITFOR_FREFRESH_DONE             _IO(IOC_TYPE_HIFB, 125)

/** set Encoder picture delivery method*/
#define FBIOPUT_ENCODER_PICTURE_FRAMING        _IOW(IOC_TYPE_HIFB, 126, HIFB_STEREO_MODE_E)

/** get Encoder picture delivery method */
#define FBIOGET_ENCODER_PICTURE_FRAMING        _IOR(IOC_TYPE_HIFB, 127, HIFB_STEREO_MODE_E)

/*set 3D Stereo work mode*/
#define FBIOPUT_STEREO_MODE                    _IOW(IOC_TYPE_HIFB, 128, HIFB_STEREO_WORKMODE_E)

/*get 3D Stereo work mode*/
#define FBIOGET_STEREO_MODE                    _IOW(IOC_TYPE_HIFB, 129, HIFB_STEREO_WORKMODE_E)

/**Sets the output range of the screen.*/
/**CNcomment:������Ļ�����Χ*/
#define FBIOPUT_SCREENSIZE                     _IOW(IOC_TYPE_HIFB, 130, HIFB_SIZE_S)

/**Obtains the output range of the screen.*/
/**CNcomment:��ȡ��Ļ�����Χ*/
#define FBIOGET_SCREENSIZE                     _IOR(IOC_TYPE_HIFB, 131, HIFB_SIZE_S)

/*set compression mode, only support pixel format argb8888, and stereo mode not support top and bottom*/
#define FBIOPUT_COMPRESSION                    _IOW(IOC_TYPE_HIFB, 132, HI_BOOL)

/*get compression mode */
#define FBIOGET_COMPRESSION                    _IOR(IOC_TYPE_HIFB, 133, HI_BOOL)

/**create scroll text*/
#define FBIO_SCROLLTEXT_CREATE                 _IOW(IOC_TYPE_HIFB, 134, HIFB_SCROLLTEXT_CREATE_S)

/**send to scroll text buffer*/
#define FBIO_SCROLLTEXT_FILL                   _IOW(IOC_TYPE_HIFB, 135, HIFB_SCROLLTEXT_DATA_64BITS_S)

/**pause scroll text*/
#define FBIO_SCROLLTEXT_PAUSE                  _IOW(IOC_TYPE_HIFB, 136, HI_U32)

/**resume scroll text*/
#define FBIO_SCROLLTEXT_RESUME                 _IOW(IOC_TYPE_HIFB, 137, HI_U32)

/**destory scroll text*/
#define FBIO_SCROLLTEXT_DESTORY                _IOW(IOC_TYPE_HIFB, 138, HI_U32)

/*set fb stereo depth*/
#define FBIOPUT_STEREO_DEPTH                   _IOW(IOC_TYPE_HIFB, 139, HI_S32)

/*get fb stereo depth*/
#define FBIOGET_STEREO_DEPTH                   _IOR(IOC_TYPE_HIFB, 140, HI_S32)

/**set the priority of layer in gp*/
#define FBIOPUT_ZORDER                         _IOW(IOC_TYPE_HIFB, 141, HIFB_ZORDER_E)

/**gett the priority of layer in gp*/
#define FBIOGET_ZORDER                         _IOW(IOC_TYPE_HIFB, 142, HI_U32)

/**free logo*/
#define FBIO_FREE_LOGO                         _IO(IOC_TYPE_HIFB, 143)

/*set compression update mode*/
#define FBIOPUT_COMPRESSIONMODE                _IOW(IOC_TYPE_HIFB, 144, HIFB_CMP_MODE_E)

/*get compression mode */
#define FBIOGET_COMPRESSIONMODE                _IOR(IOC_TYPE_HIFB, 145, HIFB_CMP_MODE_E)
#define FBIO_HWC_REFRESH                       _IOR(IOC_TYPE_HIFB, 146, HIFB_HWC_LAYERINFO_S)
#define FBIOGET_SMEMSTART_PHY                  _IOW(IOC_TYPE_HIFB, 147, HI_U32)
#define FBIO_HWC_GETLAYERINFO                  _IOR(IOC_TYPE_HIFB, 148, HIFB_HWC_LAYERINFO_S)


#define CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT      17

/** @} */  /** <!-- ==== Macro Definition end ==== */

/*************************** Structure Definition ****************************/
/** \addtogroup     HIFB   */
/** @{ */  /** <!-- [HIFB] */


/**Definition of the range type*/
/**CNcomment:��Χ���Ͷ���*/
typedef struct
{
    HI_U32  u32Width;         /**<Output width of the screen*//**<CNcomment:��Ļ������Ŀ�� */
    HI_U32  u32Height;        /**<Output height of the screen*//**<CNcomment:��Ļ������ĸ߶� */
}HIFB_SIZE_S;

/**layer ID */
/**CNcomment:ͼ��ID����*/
typedef enum
{
    HIFB_LAYER_HD_0 = 0x0,
    HIFB_LAYER_HD_1,
    HIFB_LAYER_HD_2,
    HIFB_LAYER_HD_3,
    HIFB_LAYER_SD_0,
    HIFB_LAYER_SD_1,
    HIFB_LAYER_ID_BUTT
} HIFB_LAYER_ID_E;


/**Obtains the extended 32-bit color value based on color components. The upper bits are padded with lower bits during color extension.*/
/**CNcomment:������ɫ��������ȡ����չ��32λ��ֵ����չ����:��λ�����λ*/
static inline HI_U8  hifb_rgb(const struct fb_bitfield* pBit, HI_S32 color)
{
    return ((HI_U8)((((HI_U32)color)>>pBit->offset) << (8-pBit->length)) +
             ((HI_U8)(((HI_U32)(color)>>pBit->offset) << (8-pBit->length)) >> pBit->length));
}

/**Converts a colorkey to a 32-bit colorkey based on the pixel format. A lower-bit color (such as 16 bits) is extended to an upper-bit color (such as 32 bits) as follows:
   For each chip, upper bits can be padded with lower bits in multiple mode. The padding mode of the chip must be consistent with the preceding extension mode. Otherwise, the colorkey of the graphics layer is invalid.*/
/**CNcomment:�������ظ�ʽ��Ϣ����һ����ɫֵ��ת����һ��32λ����ɫkeyֵ,����ɫ����16bit��չΪ��ɫ����32bit�Ĳ�����:
   ��λ���߼�λ��оƬ�ж��ַ�ʽ��оƬ�ķ�ʽ�����������ʽһ�£�����ͼ��colorkey��Ч*/
static inline HI_S32 hifb_color2key(const struct fb_var_screeninfo* pVar, HI_S32 color)
{
   if (pVar->bits_per_pixel <= 8)
   {
       return color;
   }
   else
   {
      HI_U8 r, g, b;
      r = hifb_rgb(&pVar->red, color);
      g = hifb_rgb(&pVar->green, color);
      b = hifb_rgb(&pVar->blue, color);
      return (r<<16) + (g<<8) + b;
   }
}

typedef struct
{
    HI_BOOL bKeyEnable;         /**<Colorkey enable*//**<CNcomment:colorkey �Ƿ�ʹ�� */
    HI_U32 u32Key;              /**<The value is obtained by calling ::hifb_color2key.*//**<CNcomment:��ֵӦ��ͨ��::hifb_color2key�õ�*/
}HIFB_COLORKEY_S;

/**Rectangle information*/
/**CNcomment:������Ϣ */
typedef struct
{
    HI_S32 x, y;    /**<x: horizontal coordinate of the upper left point of the rectangle; y: vertical coordinate of the upper left point of the rectangle*//**<CNcomment: x:�������ϵ������ y:�������ϵ�������*/
    HI_S32 w, h;    /**< w: rectangle width; h: rectangle height*//**<CNcomment: w:���ο�� h:���θ߶�*/
} HIFB_RECT;

typedef struct
{
    HI_S32 l;
    HI_S32 t;
    HI_S32 r;
    HI_S32 b;
}HIFB_REGION;

/**Coordinate of a point*/
/**CNcomment:��������Ϣ */
typedef struct
{
    HI_S32 s32XPos;         /**<  horizontal position *//**<CNcomment:ˮƽλ�� */
    HI_S32 s32YPos;         /**<  vertical position *//**<CNcomment:��ֱλ�� */
}HIFB_POINT_S;

/**Anti-flicker information*/
/**CNcomment:����˸��Ϣ */
typedef struct hiHIFB_DEFLICKER_S
{
    HI_U32  u32HDfLevel;    /**<  horizontal deflicker level *//**<CNcomment:ˮƽ����˸���� */
    HI_U32  u32VDfLevel;    /**<  vertical deflicker level *//**<CNcomment:��ֱ����˸���� */
    HI_U8   *pu8HDfCoef;    /**<  horizontal deflicker coefficient *//**<CNcomment:ˮƽ����˸ϵ�� */
    HI_U8   *pu8VDfCoef;    /**<  vertical deflicker coefficient *//**<CNcomment:��ֱ����˸ϵ�� */
}HIFB_DEFLICKER_S;

/**Alpha information*/
/**CNcomment:Alpha��Ϣ */
typedef struct
{
    HI_BOOL bAlphaEnable;   /**<  alpha enable flag *//**<CNcomment:alphaʹ�ܱ�ʶ*/
    HI_BOOL bAlphaChannel;  /**<  alpha channel enable flag *//**<CNcomment:alphaͨ��ʹ��*/
    HI_U8 u8Alpha0;         /**<  alpha0 value, used in ARGB1555 *//**CNcomment:alpha0ȡֵ��ARGB1555��ʽʱʹ��*/
    HI_U8 u8Alpha1;         /**<  alpha1 value, used in ARGB1555 *//**CNcomment:alpha1ȡֵ��ARGB1555��ʽʱʹ��*/
    HI_U8 u8GlobalAlpha;    /**<  global alpha value *//**<CNcomment:ȫ��alphaȡֵ*/
    HI_U8 u8Reserved;
}HIFB_ALPHA_S;

/**Pixel format*/
/**CNcomment:���ظ�ʽö�� */
typedef enum
{
    HIFB_FMT_RGB565 = 0,    /**<  RGB565 16bpp */
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
    HIFB_FMT_BGR565,        /**< BGR565 */
    HIFB_FMT_BGR888,        /**< BGR888 */
    HIFB_FMT_ABGR4444,      /**< ABGR4444 */

    HIFB_FMT_ABGR1555,      /**< ABGR1555 */
    HIFB_FMT_ABGR8888,      /**< ABGR8888 */
    HIFB_FMT_ABGR8565,      /**< ABGR8565 */
    HIFB_FMT_KBGR444,       /**< BGR444 16bpp */

    HIFB_FMT_KBGR555,       /**< BGR555 16bpp */
    HIFB_FMT_KBGR888,       /**< BGR888 32bpp */
    HIFB_FMT_1BPP,          /**<  clut1 */
    HIFB_FMT_2BPP,          /**<  clut2 */

    HIFB_FMT_4BPP,          /**<  clut4 */
    HIFB_FMT_8BPP,          /**< clut8 */
    HIFB_FMT_ACLUT44,       /**< AClUT44*/
    HIFB_FMT_ACLUT88,       /**< ACLUT88 */

    HIFB_FMT_PUYVY,         /**< UYVY */
    HIFB_FMT_PYUYV,         /**< YUYV */
    HIFB_FMT_PYVYU,         /**< YVYU */
    HIFB_FMT_YUV888,        /**< YUV888 */

    HIFB_FMT_AYUV8888,      /**< AYUV8888 */
    HIFB_FMT_YUVA8888,      /**< YUVA8888 */

    HIFB_FMT_BUTT
}HIFB_COLOR_FMT_E;

/**HiFB capability set*/
/**CNcomment:hifb������ */
typedef struct
{
    HI_BOOL bKeyAlpha;      /**< whether support colorkey alpha */
    HI_BOOL bGlobalAlpha;   /**< whether support global alpha */
    HI_BOOL bCmap;          /**< whether support color map */
    HI_BOOL bHasCmapReg;    /**< whether has color map register*/
    HI_BOOL bColFmt[HIFB_FMT_BUTT]; /**< support which color format */
    HI_BOOL bVoScale;       /**< support vo scale*/
    HI_BOOL bLayerSupported;    /**< whether support a certain layer, for example:x5 HD support HIFB_SD_0 not support HIFB_SD_1*/
    HI_BOOL bCompression;    /**< whether support compression */
    HI_BOOL bStereo;        /**< whether support 3D Stereo*/
    HI_U32  u32MaxWidth;    /**< the max pixels per line */
    HI_U32  u32MaxHeight;   /**< the max lines */
    HI_U32  u32MinWidth;    /**< the min pixels per line */
    HI_U32  u32MinHeight;   /**< the min lines */
    HI_U32  u32VDefLevel;   /**< vertical deflicker level, 0 means vertical deflicker is unsupported */
    HI_U32  u32HDefLevel;   /**< horizontal deflicker level, 0 means horizontal deflicker is unsupported  */
}HIFB_CAPABILITY_S;

/*refresh mode*/
typedef enum
{
    HIFB_LAYER_BUF_DOUBLE = 0x0,         /**< 2 display buf in fb */
    HIFB_LAYER_BUF_ONE    = 0x1,         /**< 1 display buf in fb */
    HIFB_LAYER_BUF_NONE   = 0x2,         /**< no display buf in fb,the buf user refreshed will be directly set to VO*/
    HIFB_LAYER_BUF_DOUBLE_IMMEDIATE=0x3, /**< 2 display buf in fb, each refresh will be displayed*/
    HIFB_LAYER_BUF_STANDARD = 0x4,       /**< standard refresh*/
    HIFB_LAYER_BUF_BUTT
} HIFB_LAYER_BUF_E;

/* surface info */
typedef struct
{
    HI_U32  u32PhyAddr;     /**<  start physical address */
    HI_U32  u32Width;       /**<  width pixels */
    HI_U32  u32Height;      /**<  height pixels */
    HI_U32  u32Pitch;       /**<  line pixels */
    HIFB_COLOR_FMT_E enFmt; /**<  color format */
}HIFB_SURFACE_S;


/* refresh surface info */
typedef struct
{
    HIFB_SURFACE_S stCanvas;
    HIFB_RECT UpdateRect;       /**< refresh region*/
}HIFB_BUFFER_S;

/* cursor info */
typedef struct
{
    HIFB_SURFACE_S stCursor;
    HIFB_POINT_S stHotPos;
} HIFB_CURSOR_S;

/** Encoder picture delivery method */
typedef enum
{
    HIFB_STEREO_MONO = 0x0,             /**< Normal output to non-stereoscopic (3D) TV. No L/R content provided to TV  */
    HIFB_STEREO_SIDEBYSIDE_HALF,        /**< L/R frames are downscaled horizontally by 2 andpacked side-by-side into a single frame, left on lefthalf of frame */
    HIFB_STEREO_TOPANDBOTTOM,           /**< L/R frames are downscaled vertically by 2 andpacked into a single frame, left on top */
    HIFB_STEREO_FRMPACKING,             /**< one frames are copyed */
    HIFB_STEREO_BUTT
}HIFB_STEREO_MODE_E;

/** 3D stereo mode*/
typedef enum
{
    HIFB_STEREO_WORKMODE_HW_FULL = 0x0,      /**< 3d stereo function use hardware and transfer full frame to vo, note: hardware doesn't support this mode if encoder picture delivery method is top and bottom */
    HIFB_STEREO_WORKMODE_HW_HALF,            /**< 3d stereo function use hardware and transfer half frame to vo*/
    HIFB_STEREO_WORKMODE_SW_EMUL,            /**< 3d stereo function use software emulation */
    HIFB_STEREO_WORKMODE_BUTT
}HIFB_STEREO_WORKMODE_E;

/**antiflicker level*/
/**Auto means fb will choose a appropriate antiflicker level automatically according to the color info of map*/
typedef enum
{
    HIFB_LAYER_ANTIFLICKER_NONE = 0x0,    /**< no antiflicker*/
    HIFB_LAYER_ANTIFLICKER_LOW = 0x1,    /**< low level*/
    HIFB_LAYER_ANTIFLICKER_MIDDLE = 0x2,/**< middle level*/
    HIFB_LAYER_ANTIFLICKER_HIGH = 0x3,  /**< high level*/
    HIFB_LAYER_ANTIFLICKER_AUTO = 0x4,  /**< auto*/
    HIFB_LAYER_ANTIFLICKER_BUTT
}HIFB_LAYER_ANTIFLICKER_LEVEL_E;

/*layer info maskbit*/
typedef enum
{
    HIFB_LAYERMASK_BUFMODE = 0x1,           /**< Whether the buffer mode in HIFB_LAYER_INFO_S is masked when the graphics layer information is set.*//**<CNcomment:����ͼ����Ϣʱ��HIFB_LAYER_INFO_S��bufģʽ�Ƿ���Ч���� */
    HIFB_LAYERMASK_ANTIFLICKER_MODE = 0x2,  /**< Whether the anti-flicker mode is masked.*//**<CNcomment:����˸ģʽ�Ƿ���Ч���� */
    HIFB_LAYERMASK_POS = 0x4,               /**< Whether the graphics layer position is masked.*//**<CNcomment:ͼ��λ���Ƿ���Ч���� */
    HIFB_LAYERMASK_CANVASSIZE = 0x8,        /**< Whether the canvas size is masked.*//**<CNcomment:canvassize�Ƿ���Ч���� */
    HIFB_LAYERMASK_DISPSIZE = 0x10,         /**< Whether the display size is masked.*//**<CNcomment:displaysize�Ƿ���Ч���� */
    HIFB_LAYERMASK_SCREENSIZE = 0x20,       /**< Whether the screen size is masked.*//**<CNcomment:screensize�Ƿ���Ч���� */
    HIFB_LAYERMASK_BMUL = 0x40,             /**< Whether the premultiplexed mode is masked.*//**<CNcomment:�Ƿ�Ԥ���Ƿ���Ч���� */
    HIFB_LAYERMASK_BUTT
}HIFB_LAYER_INFO_MASKBIT;


/**layer info*/
typedef struct
{
    HIFB_LAYER_BUF_E BufMode;
    HIFB_LAYER_ANTIFLICKER_LEVEL_E eAntiflickerLevel;
    HI_S32 s32XPos;               /**<  the x pos of origion point in screen */
    HI_S32 s32YPos;               /**<  the y pos of origion point in screen */
    HI_S32 u32CanvasWidth;        /**<  the width of canvas buffer */
    HI_S32 u32CanvasHeight;       /**<  the height of canvas buffer */
    HI_U32 u32DisplayWidth;       /**<  the width of display buf in fb.for 0 buf ,there is no display buf in fb, so it's effectless*/
    HI_U32 u32DisplayHeight;      /**<  the height of display buf in fb. */
    HI_U32 u32ScreenWidth;        /**<  the width of screen������û���� */
    HI_U32 u32ScreenHeight;       /**<  the height of screen������û���� */
    HI_BOOL bPreMul;              /**<  The data drawed in buf is premul data or not*/
    HI_BOOL bUseNewScreen;        /**<  whether use new screen*/
    HI_U32 u32Mask;               /**<  param modify mask bit*/
}HIFB_LAYER_INFO_S;

/** scrolltext attibute */
/** CNcomment:������Ļ���� */
typedef struct
{
    HIFB_RECT           stRect;        /**< the position you wanted to show on the screen */
    HIFB_COLOR_FMT_E    ePixelFmt;     /**< the color format of scrolltext content */
    HI_U16              u16CacheNum;   /**< The cached buffer number for store scrolltext content */
    HI_U16              u16RefreshFreq;/**< The refresh frequency you wanted */
    HI_BOOL             bDeflicker;    /**< Whether enable antificker */
}HIFB_SCROLLTEXT_ATTR_S;
typedef struct
{
    HIFB_SCROLLTEXT_ATTR_S stAttr; /**< The scrolltext attribution */
    HI_U32  u32Handle;             /**< The output ID for the scrolltext����HIGO�����е�ͼ���Ƶ�������ID */
}HIFB_SCROLLTEXT_CREATE_S;

/** scrolltext data */
/** CNcomment:������Ļ���ݣ���ַ��stride */
typedef struct
{
    HI_U32  u32Handle;     /**< ID of the scrolltext,�����HIGO���˸���� */
    HI_U32  u32PhyAddr;    /**< The physical address of the scrolltext content buffer */
    HI_U8   *pu8VirAddr;   /**< The virtual address of the scrolltext content buffer */
    HI_U32  u32Stride;     /**< The stride of the scrolltext content buffer */
}HIFB_SCROLLTEXT_DATA_S;

/** scrolltext data */
/** CNcomment:������Ļ���ݣ���ַ��stride */
typedef struct
{
    HI_U32  u32Handle;     /**< ID of the scrolltext,�����HIGO���˸���� */
    HI_U32  u32PhyAddr;    /**< The physical address of the scrolltext content buffer */
    HI_U64  u64VirAddr;    /**< The virtual address of the scrolltext content buffer */
    HI_U32  u32Stride;     /**< The stride of the scrolltext content buffer */
}HIFB_SCROLLTEXT_DATA_64BITS_S;


#define GP_LAYER_NUM 4
/*virtual window info*/
typedef enum
{
    HIFB_ZORDER_MOVETOP = 0,  /**< Move to the top*//**<CNcomment:�Ƶ����*/
    HIFB_ZORDER_MOVEUP,       /**< Move upwards*//**<CNcomment:������*/
    HIFB_ZORDER_MOVEBOTTOM,   /**< Move to the bottom*//**<CNcomment:�Ƶ���ײ�*/
    HIFB_ZORDER_MOVEDOWN,     /**< Move downwards*//**<CNcomment:������*/
    HIFB_ZORDER_BUTT
}HIFB_ZORDER_E;

/*compression mode*/
typedef enum
{
    HIFB_CMP_REGION = 0,   /**< fb support region compression, default mode*//**<CNcomment:֧�־ֲ�ѹ��,Ĭ��ģʽ*/
    HIFB_CMP_GLOBAL,       /**< fb support global compression only*//**<CNcomment:��֧��ȫ��ѹ��*/
    HIFB_CMP_BUTT
}HIFB_CMP_MODE_E;



typedef struct hiHI_FB_LOWPOWER_INFO_S
{
    HI_BOOL LowPowerEn;
    HI_U32 LpInfo[CONFIG_HIFB_LOWPOWER_MAX_PARA_CNT];
}HI_FB_LOWPOWER_INFO_S;


#define CONFIG_HIFB_LAYER_BUFFER_NUM_MAX   10

typedef struct
{
    HI_BOOL bPreMul;
    HI_BOOL bDeCompress;
    HI_BOOL bStereo;
    HI_BOOL bDiscardFrame;
    HI_BOOL bOutBufBusy[CONFIG_HIFB_LAYER_BUFFER_NUM_MAX];
    HI_U32 u32LayerAddr;
    HI_U32 u32Stride;
    HI_U32 u32NoCmpStride;
    HI_U32 u32Alpha;
    HI_S32 s32AcquireFenceFd;
    HI_S32 s32ReleaseFenceFd;
    HIFB_RECT stInRect;
    HIFB_POINT_S stPos;
    HIFB_COLOR_FMT_E eFmt;
    HI_FB_LOWPOWER_INFO_S stLowPowerInfo;
}HIFB_HWC_LAYERINFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HIFB_H__ */
