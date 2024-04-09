#ifndef __HI_GO_GDEV_H__
#define __HI_GO_GDEV_H__

#include "hi_go_comm.h"
#include "hi_go_surface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_GDEV */
/** @{ */  /** <!-- [HIGO_GDEV] */

/** Definition of the graphics layer ID*/
/** CNcomment:ͼ��ID����*/
typedef enum
{
    HIGO_LAYER_SD_0 = 0,
    HIGO_LAYER_SD_1,
    HIGO_LAYER_HD_0,
    HIGO_LAYER_HD_1,
    HIGO_LAYER_HD_2,
    HIGO_LAYER_HD_3,
    HIGO_LAYER_AD_0,
    HIGO_LAYER_AD_1,
    HIGO_LAYER_BUTT,
}HIGO_LAYER_E;

/**Standard-definition (SD) graphics layer 0*/
/** CNcomment:����ͼ�ε��Ӳ�0 */
#define HIGO_LAYER_RGB0 HIGO_LAYER_SD_0

/**SD graphics layer 1*/
/** CNcomment:����ͼ�ε��Ӳ�1 */
#define HIGO_LAYER_RGB1 HIGO_LAYER_SD_1

#define GRAPHICS_LAYER_MAX_NUM 4
/** The following macro defines the buffer mode of each graphics layer of the HiGo. The canvas buffer is used for drawing,
and the display buffer is used for display output.*/
/** CNcomment:����궨����higo��ÿ��ͼ���bufferģʽ������canvas buffer�ǹ��û����Ƶ�buffer, display buffer��������ʾ�����buffer.*/
#define HIGO_LAYER_BUFFER_SINGLE      0x02 /**<One canvas buffer, and no display buffer*//**<CNcomment:1��canvas buffer, ��display buffer */
#define HIGO_LAYER_BUFFER_DOUBLE      0x04 /**<One canvas buffer, and one display buffer. Dual buffers are supported.*//**<CNcomment:1��canvas buffer, 1��display buffer ֧��˫���� */
#define HIGO_LAYER_BUFFER_TRIPLE      0x08 /**<One canvas buffer, and two display buffers. The flip function is supported.*//**<CNcomment:1��canvas buffer, 2��display buffer ֧��flip,ˢ�µ�ʱ��ȴ�������� */
#define HIGO_LAYER_BUFFER_OVER        0x10 /**<One canvas buffer, and two display buffers. The flip function is supported. If tasks are being performed during refresh, the current frame is discarded.*//**<CNcomment:1��canvas buffer, 2��display buffer ֧��flip,���ˢ�µ�ʱ���������æ��������ǰ֡ */

/**Refresh mode of graphics layers for complying with old definitions. The mode is not recommended.*/
/** CNcomment:Ϊ�����϶��壬ͼ���ˢ�·�ʽ��������ʹ��*/
typedef enum
{
    HIGO_LAYER_FLUSH_FLIP        = HIGO_LAYER_BUFFER_TRIPLE,
    HIGO_LAYER_FLUSH_DOUBBUFER   = HIGO_LAYER_BUFFER_DOUBLE,
    HIGO_LAYER_FLUSH_NORMAL      = HIGO_LAYER_BUFFER_SINGLE,
    HIGO_LAYER_FLUSH_OVER        = HIGO_LAYER_BUFFER_OVER,
    HIGO_LAYER_FLUSH_BUTT
} HIGO_LAYER_FLUSHTYPE_E;

/**Anti-flicker level, ranging from low to high. The higher the level, the better the anti-flicker effect, but the more blurred the picture.*/
/** CNcomment:����˸����ֵΪLOW~HIGH,ֵԽ����˸Ч��Խ�ã���Խģ��*/
typedef enum
{
    HIGO_LAYER_DEFLICKER_NONE = 0,
    HIGO_LAYER_DEFLICKER_LOW,
    HIGO_LAYER_DEFLICKER_MIDDLE,
    HIGO_LAYER_DEFLICKER_HIGH,
    HIGO_LAYER_DEFLICKER_AUTO,
    HIGO_LAYER_DEFLICKER_BUTT
}HIGO_LAYER_DEFLICKER_E;



/**3D STEREO mode*/
/** CNcomment:3D STEREOģʽ*/
typedef enum
{
    HIGO_STEREO_MODE_HW_FULL = 0x0,  /**< 3d stereo function use hardware and transfer full frame to vo, note: hardware doesn't support the mode if encoder picture delivery method is top and bottom */
    HIGO_STEREO_MODE_HW_HALF ,    /**< 3d stereo function use hardware and transfer half frame to vo*/
    HIGO_STEREO_MODE_SW_EMUL,              /**<3d stereo function use software emulation */
    HIGO_STEREO_MODE_BUTT
}HIGO_STEREO_MODE_E;

/**Layer attribute parameters*/
/** CNcomment:ͼ�����Բ���*/
typedef struct
{
    HI_S32                 ScreenWidth;    /**<Height of a graphics layer on the screen. The value must be greater than 0.*//**<CNcomment:ͼ������Ļ����ʾ��ȣ��������0 */
    HI_S32                 ScreenHeight;   /**<Width of a graphics layer on the screen. The value must be greater than 0.*//**<CNcomment:ͼ������Ļ����ʾ�߶ȣ��������0 */
    HI_S32                 CanvasWidth;    /**<Width of the canvas buffer of a graphics layer. If the value is 0, no canvas buffer is created.*//**<CNcomment:ͼ��Ļ���buffer��ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 CanvasHeight;   /**<Height of the canvas buffer of a graphics layer. If the value is 0, no canvas buffer is created.*//**<CNcomment:ͼ��Ļ���buffer�߶ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 DisplayWidth;   /**<Width of the display buffer of a graphics layer. If the value is 0, the value of ScreenWidth is used.*//**<CNcomment:ͼ�����ʾbuffer��ȣ�Ϊ0ʱ����ScreenWidth��ͬ*/
    HI_S32                 DisplayHeight;  /**<Height of the display buffer of a graphics layer. If the value is 0, the value of ScreenHeight is used.*//**<CNcomment:ͼ�����ʾbuffer�߶ȣ�Ϊ0ʱ����ScreenHeight��ͬ*/
    HIGO_LAYER_FLUSHTYPE_E LayerFlushType; /**< Refresh mode of the layer. You can choose the refresh mode based on the actual scenario to improve the refresh efficiency. If the value is 0, the dual-buffer+flip refresh mode is used by default. *//**<CNcomment:ͼ���ˢ�·�ʽ���û��ɸ���ʹ�ó���ѡ��ͬ��ˢ��ģʽ�����ˢ��Ч��,����0ʱĬ��ʹ��˫����+Flipˢ��ģʽ */
    HIGO_LAYER_DEFLICKER_E AntiLevel;      /**<Anti-flicker level of a graphics layer*//**<CNcomment:ͼ�㿹��˸���� */
    HIGO_PF_E              PixelFormat;    /**<Pixel format of a graphics layer. The format must be supported by the hardware layer. You need to choose the pixel format parameters of the layer based on hardware devices.*//**<CNcomment:ͼ������ظ�ʽ���˸�ʽ����ΪӲ��ͼ����֧�ֵĸ�ʽ������ݲ�ͬӲ���豸��ѡ��ͼ������ظ�ʽ���� */
    HIGO_LAYER_E           LayerID;        /**<Hardware ID of a graphics layer. The supported graphics layer depends on the chip platform. For example, the Hi3720 supports an HD graphics layer and an SD graphics layer.*//**<CNcomment:ͼ��Ӳ��ID����֧��ͼ��ȡ����оƬƽ̨��hi3720����֧��һ�������һ������ */
} HIGO_LAYER_INFO_S;

/**Status of a graphics layer*/
/** CNcomment:ͼ��״̬�ṹ */
typedef struct
{
    HI_BOOL bShow;             /**<Whether to display a graphics layer.*//**<CNcomment:ͼ���Ƿ���ʾ */
} HIGO_LAYER_STATUS_S;

typedef struct
{
    HI_COLOR ColorKey;         /**<Transparency of a graphics layer*//**<CNcomment:ͼ���͸��ɫ*/
    HI_BOOL bEnableCK;         /**<Whether the colorkey of a graphics layer is enabled.*//**<CNcomment:ͼ���Ƿ�ʹ��colorkey */
}HIGO_LAYER_KEY_S;

typedef struct
{
    HI_BOOL bAlphaEnable;   /**<Alpha pixel enable flag*//**<CNcomment:alpha����ʹ�ܱ�־ */
    HI_BOOL bAlphaChannel;  /**<Alpha channel enable flag*//**<CNcomment:alphaͨ��ʹ�ܱ�־  */
    HI_U8   Alpha0;         /**<Alpha0 value. It is valid in ARGB1555 format.*//**<CNcomment:alpha0ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   Alpha1;         /**<Alpha1 value. It is valid in ARGB1555 format.*//**<CNcomment:alpha1ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   GlobalAlpha;    /**<Global alpha. This value is valid only when the alpha channel is valid.*//**<CNcomment:ȫ��alpha����ֵֻ����alphaͨ����Ч��ʱ��������� */
}HIGO_LAYER_ALPHA_S;
#if 0
/**Frame encode format*/
/**CNcomment:֡���봫���ʽ*/
typedef enum
{
    HIGO_STEREO_MONO   = 0x0,             /**< Normal display, no 3D TV*//**<CNcomment:�����������3D ����*/
    HIGO_STEREO_SIDEBYSIDE_HALF,          /**< L/R frames are downscaled horizontally by 2 andpacked side-by-side into a single frame, left on lefthalf of frame*//**<CNcomment:��L/R֡ˮƽ���ŵ���֡��*/
    HIGO_STEREO_TOPANDBOTTOM,             /**< L/R frames are downscaled vertically by 2 andpacked into a single frame, left on top*//**<CNcomment:��L/R֡��ֱ���ŵ���֡��*/
    HIGO_STEREO_BUTT
}HIGO_STEREO_MODE_E;
#endif

typedef struct
{
    HI_HANDLE   Layer;          /** The layer the scrolltext want to show */
    HI_RECT       stScrollRect;   /** the position you wanted to show on the layer */
    HIGO_PF_E   ePixelFormat;    /** the color format of scrolltext content */
    HI_U16        u16CacheNum;       /** The cached buffer number for store scrolltext content */
    HI_U16        u16RefreshFreq;    /** The refresh frequency you wanted */
    HI_BOOL     bDeflicker;        /** Whether enable antificker */
} HIGO_SCROLLTEXT_ATTR_S;

typedef struct
{
    HI_U32 u32PhyAddr;  /** The physical address of the scrolltext content buffer */
    HI_U8  *pu8VirAddr;  /** The virtual address of the scrolltext content buffer */
    HI_U32 u32Stride;     /** The stride of the scrolltext content buffer */
} HIGO_SCROLLTEXT_DATA_S;



/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      HIGO_GDEV */
/** @{ */  /** <!--[HIGO_GDEV] */

/**
\brief Initializes a display device. CNcomment:��ʼ����ʾ�豸 CNend
\attention \n
When ::HI_GO_Init is called, this API is also called.
CNcomment: ::HI_GO_Init�Ѱ����˶Ըýӿڵĵ��� CNend
\param N/A. CNcomment:�� CNend

\retval ::HI_FAILURE
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Init \n
::HI_GO_DeinitDisplay
*/
HI_S32 HI_GO_InitDisplay(HI_VOID);

/**
\brief Deinitializes a display device. CNcomment:ȥ��ʼ����ʾ�豸 CNend
\attention \n
When ::HI_GO_Deinit is called, this API is also called.
CNcomment: ::HI_GO_Deinit�Ѱ����˶Ըýӿڵĵ��� CNend
\param N/A. CNcomment:�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Deinit \n
::HI_GO_InitDisplay
*/
HI_S32 HI_GO_DeinitDisplay(HI_VOID);

/**
\brief Obtains the default parameters of an SD or HD graphics layer based on its ID.
If you do not want to use default values, you can set the members of pLayerInfo.
CNcomment:����ͼ��ID��ȡ��Ӧͼ��(SD,HD)����ʱ��Ĭ�ϲ�����
�����Ҫʹ�÷�Ĭ��ֵ������ֱ������pLayerInfo������Ա CNend
\attention \n

\param[in] LayerID Layer ID. CNcomment:ͼ��ID CNend
\param[in]  pLayerInfo Obtained parameters of a graphics layer when it is created. CNcomment:��ȡ���Ĵ������� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPARAM
\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_GetLayerDefaultParam (HIGO_LAYER_E LayerID, HIGO_LAYER_INFO_S *pLayerInfo);


/**
\brief Creates a graphics layer. CNcomment:����ͼ�� CNend
\attention \n
The platform determines whether VO hardware scaling is supported.
If VO hardware scaling is supported, the display size is scaled to fit the screen when the display size is inconsistent with the screen size.
If VO hardware scaling is not supported, the display size and screen size must be the same.
CNcomment:�Ƿ�֧��VOӲ������ȡ����ƽ̨��
���ƽ̨֧��VO Ӳ�����ţ���������displaysize��screensize��һ�µ�����£����ջ����ŵ�screensize�Ĵ�С��
���ƽ̨��֧��VO Ӳ�����ţ���ʹdisplaysize��screensize��һ�£�Ҳ��ǿ��Ҫ��displaysize��screensizeһ�� CNend

\param[in]  pLayerInfo Basic attributes of a graphics layer. The value cannot be empty. CNcomment:ͼ��������ԣ�����Ϊ�� CNend
\param[out] pLayer Pointer to the handle of a graphics layer. The value cannot be empty. CNcomment:ͼ��ľ��ָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVFLUSHTYPE
\retval ::HIGO_ERR_INVANILEVEL
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_ALREADYBIND
\retval ::HIGO_ERR_INVLAYERSURFACE

\see \n
::HI_GO_DestroyLayer
*/
HI_S32 HI_GO_CreateLayer (const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE* pLayer);

/**
\brief Destroys a graphics layer. CNcomment:����ͼ�� CNend
\attention \n
If a graphics layer is in use (for example, the desktop based on the layer is not destroyed), the layer cannot be destroyed.
CNcomment:��ͼ�����ڱ�ʹ��ʱ��������ڴ�ͼ�������δ���٣�����ͼ���޷������� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_CreateLayer
*/
HI_S32 HI_GO_DestroyLayer(HI_HANDLE Layer);


/**
\brief Sets the position of a graphics layer on the screen. CNcomment:����ͼ������Ļ�е�λ�� CNend
\attention \n
The value takes effect at once and you do not need to refresh it. If the start position of a layer exceeds the screen, it is automatically adjusted to the boundary of the screen.
CNcomment:������Ч������ˢ�¡������õ�ͼ�����ʼλ�ó�����Ļ��Χʱ���Զ���������Ļ�ı߽�ֵ CNend
\param[in] Layer  Layer handle. CNcomment:ͼ���� CNend
\param[in] u32StartX Horizontal coordinate of the position where a layer appears on the screen. CNcomment:ͼ������Ļ�ϵ���ʾλ��X���� CNend
\param[in] u32StartY Vertical coordinate of the position where a layer appears on the screen. CNcomment:ͼ������Ļ�ϵ���ʾλ��Y���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERPOS
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerPos
*/
HI_S32 HI_GO_SetLayerPos(HI_HANDLE Layer, HI_U32 u32StartX, HI_U32 u32StartY);

/**
\brief Obtains the position where a layer appears on the screen. CNcomment:��ȡͼ������Ļ�ϵ�λ�� CNend
\attention \n
N/A. CNcomment:�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[out] pStartX Pointer of the horizontal coordinate of the position where a layer appears on the screen. The value cannot be empty. CNcomment:ͼ������Ļ�ϵ���ʾλ��X����ָ�룬����Ϊ�� CNend
\param[out] pStartY Pointer of the vertical coordinate of the position where a layer appears on the screen. The value cannot be empty. CNcomment:ͼ������Ļ�ϵ���ʾλ��Y����ָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetLayerPos
*/
HI_S32 HI_GO_GetLayerPos(HI_HANDLE Layer, HI_U32 *pStartX, HI_U32 *pStartY);


/**
\brief Sets the output height and width of a graphics layer on the display device. CNcomment:�����������ʾ�豸�ϵ�����ĸ߶ȺͿ�� CNend
\attention \n
This API supports zoom in operations. The maximum range is specified when a graphics layer is created.\n
CNcomment:���ڴ�֧�ֵ�ǰ���£��ýӿڿ���֧������ CNend

\param[in]  Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] u32SWidth  Actual output width. CNcomment:ʵ�������� CNend
\param[in] u32SHeight Actual output height. CNcomment:ʵ������߶� CNend
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetScreenSize
*/
HI_S32 HI_GO_SetScreenSize(HI_HANDLE Layer, HI_U32 u32SWidth, HI_U32 u32SHeight);


/**
\brief Obtains the output height and width of a graphics layer on the display device. CNcomment:��ȡ�������ʾ�豸�ϵ�����ĸ߶ȺͿ�ȡ�CNend
\attention \n
N/A. CNcomment:�� CNend
\param[in]  Layer Layer handle. CNcomment:ͼ���� CNend
\param[out] pSWidth  Pointer to the actual output width. CNcomment:ʵ��������ָ�� CNend
\param[out] pSHeight Pointer to the actual output height. CNcomment:ʵ������߶�ָ�� CNend
\retval none
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetScreenSize
*/
HI_S32 HI_GO_GetScreenSize(HI_HANDLE Layer, HI_U32 *pSWidth, HI_U32 *pSHeight);

/**
\brief Sets the global alpha value of a layer surface. CNcomment:����ͼ��surface��ȫ��alphaֵ CNend
\attention \n
The value takes effect at once, and you do not need to refresh it.
CNcomment:������Ч������ˢ�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] Alpha Global alpha value. The value cannot be empty and ranges from 0 to 255. CNcomment:Alpha ȫ��alphaֵ������Ϊ�գ���Χ0-255 CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_SETALPHAFAILED
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerAlpha
*/

HI_S32 HI_GO_SetLayerAlpha(HI_HANDLE Layer, HI_U8 Alpha);

/**
\brief Sets layer premul state. CNcomment:����Ԥ��״̬ CNend
\attention \n
The value takes effect at once, and you do not need to refresh it.
CNcomment:������Ч������ˢ�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] enable or disable layer premu. CNcomment:����Ԥ��״̬CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GO_SetLayerPreMul
*/
HI_S32 HI_GO_SetLayerPreMul(HI_HANDLE Layer, HI_BOOL bPreMul);


/**
\brief Obtains the global alpha value of a layer surface. CNcomment:��ȡͼ��surface��ȫ��alphaֵ CNend
\attention \n
N/A. CNcomment:�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[out] pAlpha Pointer to the global alpha value. CNcomment:ȫ��alphaָ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_SetLayerAlpha
*/
HI_S32 HI_GO_GetLayerAlpha(HI_HANDLE Layer, HI_U8* pAlpha);


/**
\brief Obtains the surface of a graphics layer. CNcomment:��ȡͼ���surface CNend
\attention \n
Surface of a graphics layer. It cannot be released by calling HI_GO_FreeSurface. The surface can be released only when the corresponding layer is destroyed.
After a process is switched, you must obtain the layer surface again by calling HI_S32 HI_GO_GetLayerSurface.
CNcomment:ͼ��surface������ʹ��HI_GO_FreeSurface���ͷš�ֻ��������ͼ���ʱ��Żᱻ�ͷ�
�����л�֮�������øýӿ������»�ȡͼ��surface; CNend
\param[in] Layer handle. CNcomment:Layer ͼ���� CNend
\param[out] pSurface Pointer to the surface handle. The value cannot be empty. CNcomment:surface���ָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_DEPEND_FB

\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_GetLayerSurface(HI_HANDLE Layer, HI_HANDLE *pSurface);

/**
\brief Shows or hides a graphics layer. CNcomment:��ʾ������ͼ�� CNend
\attention \n
The value takes effect at once, and you do not need to refresh it.
CNcomment:������Ч������ˢ�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] bVisbile Show/hide flag. HI_TRUE: show; HI_FALSE: hide. CNcomment:��ʾ���ر�־��HI_TRUE����ʾ��HI_FALSE������ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerStatus
*/
HI_S32 HI_GO_ShowLayer(HI_HANDLE Layer, HI_BOOL bVisbile);

/**
\brief Obtains the current status of a graphics layer. CNcomment:��ȡͼ�㵱ǰ״̬ CNend
\attention \n
N/A. CNcomment:�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[out] pLayerStatus Pointer to the current status of a graphics layer. The value cannot be empty. CNcomment:ͼ�㵱ǰ״̬�ṹָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetLayerStatus(HI_HANDLE Layer, HIGO_LAYER_STATUS_S* pLayerStatus);

/**
\brief Refreshes a graphics layer. CNcomment:ˢ��ͼ�� CNend
\attention \n
1. After drawing, you need to refresh the layer to display the drawing result.
2. There are two display modes after a graphics layer is refreshed. If there is no window, the contents of the layer surface are displayed; if there is a window, its contents are displayed.
CNcomment:1.������ɺ���ˢ��ͼ�������ʾ���ƺ���
2.ˢ��������ģʽ��һ����û���κδ��ڵ�ʱ�����ʾlayersurface�����ݣ�������ʾ�����е����ݡ�CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in]  pRect Rectangle to be refreshed. If the value is NULL, the entire screen is refreshed. CNcomment:ˢ�µľ������������NULL, ��ˢ������ȫ�� CNend
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_EMPTYRECT

\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_RefreshLayer(HI_HANDLE Layer, const HI_RECT* pRect);


/**
\brief Sets the canvas buffer of a graphics layer. CNcomment:���ò��canvas surface. CNend
\attention \n
If the stream sources of the HD and SD graphics layer are the same, the canvas buffer of the SD graphics layer can be shared with the HD graphics layer.
CNcomment:����ͱ���ͬԴʱ�����ǿ����ñ����canvas buffer�����Ĺ���ͬһ��
     Surrface���ڴ����ͱ�����MMZ���͵�. CNend
\param[in] Layer     Layer handle. CNcomment:ͼ���� CNend
\param[in] hSurface  Surface of a graphics layer. If the value is INVALID_HANDLE, there is no user handle. CNcomment:ͼ���surface������ò���ΪINVALID_HANDLE��ʾû���û���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVPARAM

\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_SetLayerSurface(HI_HANDLE Layer, HI_HANDLE hSurface);



/**
\brief Sets the background color of a graphics layer. CNcomment:����ͼ��ı�����ɫ CNend
\attention \n
The background color of a graphics layer takes effect only when widows are overlaid with each other.
CNcomment:ͼ�㱳��ɫ��ֻ���ڵ��Ӵ��ڲ���Ч CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] Color Background color of a graphics layer. CNcomment:ͼ�㱳����ɫ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_SetLayerBGColor(HI_HANDLE Layer, HI_COLOR Color);

/**
\brief Obtains the background color of a graphics layer. CNcomment:��ȡͼ��ı�����ɫ CNend
\attention \n
This API is available only when there are windows on graphics layers. Otherwise, the configured background color does not take effect.
CNcomment:�˽ӿ�ֻ����ͼ�����д��ڵ�ʱ��Ż���Ч���������ɫ������Ч��CNend
\param[in] Layer Layer handle. CNcomment:ͼ���� CNend
\param[in] pColor Used for storing the background color of a graphics layer. CNcomment:�洢ͼ�㱳����ɫ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A. CNcomment:�� CNend
*/
HI_S32 HI_GO_GetLayerBGColor(HI_HANDLE Layer, HI_COLOR* pColor);

/**
\brief Sets the size of a display buffer. CNcomment:������ʾbuffer size CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer      Layer handle. CNcomment:ͼ���� CNend
\param[in] u32DWidth     Pointer to the width. CNcomment:���ָ�� CNend
\param[in] u32DHeight    Pointer to the height. CNcomment:�߶�ָ�� CNend
\param[out] N/A . CNcomment:��  CNend

\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_GetDisplaySize
*/
HI_S32 HI_GO_SetDisplaySize(HI_HANDLE Layer, HI_U32 u32DWidth, HI_U32 u32DHeight);

/**
\brief Obtains the size of a display buffer. CNcomment:��ȡ��ʾbuffer��size CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer      Layer handle. CNcomment:ͼ���� CNend
\param[in] pDWidth    Pointer to the width. The value cannot be empty. CNcomment:���ָ�룬����Ϊ��  CNend
\param[in] pDHeight   Pointer to the height. The value cannot be empty. CNcomment:�߶�ָ�룬����Ϊ�� CNend
\param[out] N/A. CNcomment:�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_SetDisplaySize
*/
HI_S32 HI_GO_GetDisplaySize(HI_HANDLE Layer, HI_U32 *pDWidth, HI_U32 *pDHeight);

/**
\brief Sets the refresh mode. CNcomment:����ˢ������ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer         Layer handle. CNcomment:ͼ���� CNend
\param[in] FlushType     Refresh mode of a graphics layer. CNcomment:ͼ��ˢ������ CNend
\param[out] N/A. CNcomment:�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVFLUSHTYPE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetFlushType
*/
HI_S32 HI_GO_SetFlushType(HI_HANDLE Layer, HIGO_LAYER_FLUSHTYPE_E FlushType);

/**
\brief Obtains the refresh mode. CNcomment:��ȡˢ������ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ����  CNend
\param[in] *pFlushType Refresh mode of a graphics layer. The value cannot be empty. CNcomment:ͼ��ˢ�����ͣ�����Ϊ��  CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetFlushType
*/
HI_S32 HI_GO_GetFlushType(HI_HANDLE Layer, HIGO_LAYER_FLUSHTYPE_E *pFlushType);

/**
\brief Sets the transparency of a graphics layer. CNcomment:����ͼ���͸��ɫ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ����  CNend
\param[in] pKey        Pointer to the transparency information. The value cannot be empty. CNcomment:͸��ɫ��Ϣָ�룬����Ϊ�� CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetLayerColorkey
*/
HI_S32 HI_GO_SetLayerColorkey(HI_HANDLE Layer, const HIGO_LAYER_KEY_S *pKey);

/**
\brief Obtains the transparency information about a graphics layer. CNcomment:��ȡ͸��ɫ��Ϣ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] pKey        Pointer to the transparency information. CNcomment:͸��ɫ��Ϣָ�� CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerColorkey
*/
HI_S32 HI_GO_GetLayerColorkey(HI_HANDLE Layer, HIGO_LAYER_KEY_S *pKey);

/**
\brief Sets the palette of a graphics layer. CNcomment:����ͼ��ĵ�ɫ�� CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] Palette     Palette of a graphics layer. CNcomment:ͼ���ɫ�� CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetLayerPalette
*/
HI_S32 HI_GO_SetLayerPalette(HI_HANDLE Layer, const HI_PALETTE Palette);

/**
\brief Obtains the palette of a graphics layer. CNcomment:��ȡͼ���ɫ�� CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] Palette     Palette of a graphics layer. CNcomment:ͼ���ɫ�� CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerPalette
*/
HI_S32 HI_GO_GetLayerPalette(HI_HANDLE Layer, HI_PALETTE Palette);

/**
\brief Waits for the blanking area. CNcomment:�ȴ������� CNend
\attention \n
N/A
CNcomment:��  CNend
\param[in] Layer       Layer handle. CNcomment:ͼ����  CNend
\param[out] N/A. CNcomment:��  CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerPalette
*/
HI_S32 HI_GO_WaitForBlank(HI_HANDLE Layer);


/**
\brief Configures the alpha information about a graphics layer. This API is an extended API. CNcomment:����ͼ��alpha��Ϣ����չ�ӿ� CNend
\attention \n
The alpha0 and alpha1 of the data structure HIGO_LAYER_ALPHA_S are valid only in ARGB1555 format.
This API is used to implement the translucent effect in ARGB1555 format.
CNcomment:�ýӿ�HIGO_LAYER_ALPHA_S�ṹ���alpha0,alpha1ֻ��ARGB1555��ʽ�²���Ч��
������ARGB1555��ʽ��ʵ�ְ�͸��Ч�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] pAlphaInfo   Alpha information about a graphics layer. The value cannot be empty. CNcomment:ͼ��alpha��Ϣ������Ϊ�� CNend
\param[out] N/A.

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB

\see \n
::HI_GO_GetLayerAlphaEx
*/
HI_S32 HI_GO_SetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);


/**
\brief Obtains the alpha information about a graphics layer. This API is an extended API. CNcomment:��ȡͼ��alpha��Ϣ����չ�ӿ� CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[out] pAlphaInfo  Alpha information about a graphics layer. The value cannot be empty. CNcomment:ͼ��alpha��Ϣ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerAlphaEx
*/
HI_S32 HI_GO_GetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);

/**
\brief set the Z order of graphics layer in the sample display. CNcomment:�ı�ͬһ��ʾ�豸��ͼ�β��Z��CNend
\attention \n
this function make effect imediately. CNcomment:�ù�����ҪӲ��֧��Z����޸ģ�������Ч������ˢ�� CNend
\param[in] Layer Layer handle. CNcomment:ͼ����  CNend
\param[in] ZFlag zorder flag. CNcomment:�޸�Z���־ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVORDERFLAG
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_CANNOTCHANGE

\see \n
::HI_GO_GetLayerZorder
*/
HI_S32 HI_GO_SetLayerZorder(HI_HANDLE Layer, HIGO_ZORDER_E enZOrder);

/**
\brief get the Z order of graphics layer in the sample display. CNcomment:��ȡͬһ��ʾ�豸��ͼ�β��Z��CNend
\attention \n
CNcomment:Z��ԽС��ͼ��Խ���� CNend
\param[in] Layer    Layer handle. CNcomment:ͼ����  CNend
\param[out] pZOrder Z Order Information. CNcomment:ͼ��Z����Ϣ��CNend


\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_ChangeLayerZorder
*/
HI_S32 HI_GO_GetLayerZorder(HI_HANDLE Layer, HI_U32* pu32ZOrder);

/**
\brief Sets frame input encode mode of a graphic layer. CNcomment:����ͼ�β�����3D��ʽ�������ʽ�Զ�����VO�������á�CNend
\attention \n
MONO is the default mode.
CNcomment:Ĭ��ΪMONO��ʽ������ͨ��3D Stereo��ʽ. CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] EncPicFrm  Frame encode mode.The value cannot be empty. CNcomment:ͼ��֡��������ʽ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetStereoMode
*/
HI_S32 HI_GO_SetStereoMode(HI_HANDLE Layer,  HIGO_STEREO_MODE_E InputEnc);



/**
\brief Obtains frame encode mode of a graphic layer. CNcomment:��ȡͼ�β�3D��ʽ��CNend
\attention \n
CNcomment:�� CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[out] pInputEnc  Frame encode mode.The value cannot be empty. CNcomment:ͼ��֡��������ʽ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetStereoMode
*/
HI_S32 HI_GO_GetStereoMode(HI_HANDLE Layer,  HIGO_STEREO_MODE_E *pInputEnc);


/**
\brief set the 3d depth, only support depth in Horizontal . CNcomment:���þ���,ֻ֧��ˮƽ������ CNend
\attention \n
CNcomment:�� CNend

\param[in]  Layer       Layer handle. CNcomment:ͼ���� CNend
\param[out] StereoDepth  3D depth. CNcomment:���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetStereoDepth
*/
HI_S32 HI_GO_SetStereoDepth(HI_HANDLE Layer,  HI_S32  s32StereoDepth);


/**
\brief get the 3d depth, only support depth in Horizontal . CNcomment:��ȡ����,ֻ֧��ˮƽ������ CNend
\attention \n
CNcomment:�� CNend

\param[in]  Layer       Layer handle. CNcomment:ͼ���� CNend
\param[out] pStereoDepth  3D depth. CNcomment:���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetStereoDepth
*/
HI_S32 HI_GO_GetStereoDepth(HI_HANDLE Layer,  HI_S32  *ps32StereoDepth);

/**
\brief Sets compress mode of a graphic layer. CNcomment:����ʹ��ѹ��ģʽ CNend
\attention \n
When compress is enable, only HIGO_PF_8888 is supported;SD layer and  STEREO TOPANDBOTTOM
are also not supported.
CNcomment:ֻ֧�����ظ�ʽΪHIGO_PF_8888����֧�ֱ����3D STEREO TOPANDBOTTOMģʽ CNend

\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[in] StereoMode  Stereo mode, the value cannot be empty. CNcomment:ѹ��ʹ�ܣ�����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_GetStereoMode
*/
HI_S32 HI_GO_SetCompression(HI_HANDLE Layer,  HI_BOOL bEnable);


/**
\brief Sets compress mode of a graphic layer. CNcomment:��ȡѹ��ģʽ�Ƿ�ʹ�� CNend
\attention \n
N/A. CNcomment:�� CNend
\param[in] Layer       Layer handle. CNcomment:ͼ���� CNend
\param[out] pbEnable  Stereo mode, the value cannot be empty. CNcomment:ѹ��ʹ�ܣ�����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetStereoMode
*/
HI_S32 HI_GO_GetCompression(HI_HANDLE Layer,  HI_BOOL* pbEnable);

/**
\brief Create ScrollText. CNcomment:����������Ļ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] pstScrollAttr  ScrollText attribute,the value cannot be empty. CNcomment:������Ļ���� CNend
\param[out] phScrollText  ScrollText handle. CNcomment:������Ļ�������� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_INUSE

\see \n
    ::HI_GO_CreateScrollText
*/
HI_S32 HI_GO_CreateScrollText(HIGO_SCROLLTEXT_ATTR_S * pstScrollAttr, HI_HANDLE * phScrollText);


/**
\brief Fill data to ScrollText cache buffer. CNcomment:�������Ļ�������� CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] hScrollText  ScrollText handle.     CNcomment:������Ļ�ľ�� CNend
\param[out] pstScrollData ScrollText data information. CNcomment:������Ļ��������Ϣ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_FillScrollText
*/
HI_S32 HI_GO_FillScrollText(HI_HANDLE hScrollText, HIGO_SCROLLTEXT_DATA_S * pstScrollData);


/**
\brief Pause the ScrollText. CNcomment:��ͣ������Ļ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] hScrollText  ScrollText handle.   CNcomment:������Ļ�ľ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_PauseScrollText
*/
HI_S32  HI_GO_PauseScrollText(HI_HANDLE hScrollText);


/**
\brief Resume the ScrollText,the ScrollText has Paused. CNcomment:�ָ�����ͣ�Ĺ�����Ļ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] hScrollText  ScrollText handle.  CNcomment:������Ļ�ľ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_ResumeScrollText
*/
HI_S32  HI_GO_ResumeScrollText(HI_HANDLE hScrollText);


/**
\brief Destroy ScrollText. CNcomment:���ٹ�����Ļ CNend
\attention \n
N/A. CNcomment:�� CNend

\param[in] hScrollText ScrollText handle.  CNcomment:������Ļ�ľ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_DestoryScrollText
*/
HI_S32  HI_GO_DestoryScrollText(HI_HANDLE hScrollText);
/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_GO_GDEV_H__ */
