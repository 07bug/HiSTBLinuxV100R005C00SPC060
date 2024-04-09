#ifndef __HI_GO_WINC_H__
#define __HI_GO_WINC_H__

#include "hi_type.h"
#include "hi_go_comm.h"
#include "hi_go_surface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_WINC */
/** @{ */  /** <!��[HIGO_WINC]  */



/**Number of buffers used by the window*//** CNcomment:windowʹ��buffer�ķ�ʽ*/
typedef enum
{
    HIGO_BUFFER_SINGLE = 0,  /**<The window uses a buffer.*//**<CNcomment:windowʹ�õ�buffer*/
    HIGO_BUFFER_DOUBLE,     /**<The window uses dual buffers.*/ /**<CNcomment:windowʹ��˫buffer*/
    HIGO_BUFFER_BUTT
}HIGO_BUFFERTYPE_E;

/**Maximum number of window layers*//** CNcomment: ��󴰿ڲ��� */
#define HIGO_WINTREE_NUM 16

typedef struct
{
    HI_HANDLE hLayer; /**<Graphics layer on which a window is displayed*//**<CNcomment:������ʾ��ͼ��*/
    HI_RECT rect;     /**<Window range*//**<CNcomment:���ڵķ�Χ*/
    HI_U32 LayerNum;     /**<Display level of a window, ranging from 0 to 15. The greater the number, the upper the position of the window.*//**<CNcomment:������ʾ�ļ���,���Ϊ0-15������Խ��Ĵ���Խ������*/
    HIGO_PF_E PixelFormat;/**<Pixel format of a window*//**<CNcomment:���ڵ����ظ�ʽ*/
    HIGO_BUFFERTYPE_E BufferType; /**<Number of surface buffers required by a window*/ /**<CNcomment:������Ҫ��surface buffer����������*/
    HI_BOOL bPubPallette;    /**<Window surface use single Palette or not*//**<CNcomment:���ڵ�surface�Ƿ�ʹ�õ�����Palette;ֻ�е�����
                                            ���ڴ�ģʽΪ�����ڴ�ʱ�ñ�־����Ч*/
} HIGO_WNDINFO_S;
/** @} */  /*! <!-- Structure Definition end */

typedef enum
{
     HIGO_WNDMEM_SHARED = 0,  /**<All windows share memory*//**<CNcomment:����window�����ڴ�*/
     HIGO_WNDMEM_SEP,          /**<Window uses it's own memory*//**<CNcomment:����ʹ��һ���ڴ�*/
    HIGO_WNDMEM_BUTT,
}HIGO_WNDMEM_E;

typedef struct tag_HIGO_INVRGNLIST_S
{
    HI_HANDLE hWindow;
    HI_REGION InvRgn;
}HIGO_INVRGN_S;
/******************************* API declaration *****************************/
/** \addtogroup      HIGO_WINC */
/** @{ */  /** <!��[HIGO_WINC] */

/**
\brief Creates a window on a specified graphics layer and sets the pixel format of a window.CNcomment:��ָ��ͼ���ϴ������� CNend
\attention \n
The new window is always located on the top of a specified graphics layer. The parts of the canvas surface that
exceed the graphics layer are cropped.CNcomment:�´����Ĵ���ʼ����ָ�����������, ����ʾʱ������ͼ��canvas surface��Χ���ֻᱻ���е���CNend
\param[in] pInfo Information for creating a window. Only the following pixel formats are supported:CNcomment:���ڴ�������Ϣ���������ظ�ʽֻ֧���������е����ظ�ʽ:
    HIGO_PF_CLUT8
    HIGO_PF_4444
    HIGO_PF_0444
    HIGO_PF_1555
    HIGO_PF_0555
    HIGO_PF_565
    HIGO_PF_8565
    HIGO_PF_8888
    HIGO_PF_0888 CNend
    The number of the layer where a window is located must range from 0 to 15. The greater the ID, the upper the
position of the window.CNcomment:���д��ڲ��ֻ����0��15�ķ�Χ��(����0��15)����Ŵ�Ĵ�����Զ��ͼ���С������ CNend

\param[out] pWindow  Address for storing window handles. The value cannot be empty.CNcomment:�洢���ھ���ĵ�ַ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPF

\see \n
::HI_GO_DestroyWindow
*/
HI_S32 HI_GO_CreateWindowEx(const HIGO_WNDINFO_S* pInfo, HI_HANDLE* pWindow);

/**
\brief Creates a window on a specified graphics layer.CNcomment:��ָ��ͼ���ϴ������� CNend
\attention \n
If the pixel format of a graphics layer contains pixel alpha, you can choose whether to use pixel alpha for the
surface of the window.
CNcomment:��ͼ������ظ�ʽ��������alphaʱ�����ڵ�surface����ѡ���Ƿ�ʹ������alpha CNend
\param[in] hLayer  Handle of the graphics layer.CNcomment:ͼ���� CNend
\param[in] pRect Rectangle window region. If the value is empty, it indicates the entire desktop region.CNcomment:���δ�������Ϊ�ձ�ʾ������������ CNend
\param[in] LayerNum Number of the layer where a window is located. The number ranges from 0 to 15.CNcomment:���������Ĳ��,���Ϊ0-15��CNend
\param[in] bHasPixelAlpha Whether a window contains pixel alpha.CNcomment:�����Ƿ������alpha CNend
\param[out] pWindow  Address for storing window handles. The value cannot be empty.CNcomment:�洢���ھ���ĵ�ַ������Ϊ�� CNend
\param[out] eBufferType Type of the surface buffer used by a window.CNcomment:windwoʹ��surface buffer������ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_DestroyWindow
*/
HI_S32 HI_GO_CreateWindow(HI_HANDLE hLayer, const HI_RECT* pRect,
                          HI_U32 LayerNum, HI_BOOL bHasPixelAlpha,
                          HI_HANDLE* pWindow,HIGO_BUFFERTYPE_E eBufferType);

/**
\brief Destroys a window.CNcomment:���ٴ��� CNend
\attention \n
\param[in] Window Window handle to be destroyed.CNcomment:�����ٴ��ھ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVPARAM

\see \n
::HI_GO_CreateWindow
*/
HI_S32 HI_GO_DestroyWindow(HI_HANDLE Window);

/**
\brief Obtains a window rectangle.CNcomment:��ȡ���ھ��� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[out] pRect Window rectangle address. The value cannot be empty.CNcomment:���ھ��ε�ַ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_SetWindowPos \n
::HI_GO_ResizeWindow
*/
HI_S32 HI_GO_GetWindowRect(HI_HANDLE Window, HI_RECT* pRect);

/**
\brief Sets the start position of a window on the attached layer.CNcomment:���ô����ڰ󶨲��ϵ���ʼλ�� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] StartX Horizontal coordinate.CNcomment:X���� CNend
\param[in] StartY Vertical coordinate.CNcomment:Y���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetWindowRect
*/
HI_S32 HI_GO_SetWindowPos(HI_HANDLE Window, HI_S32 StartX, HI_S32 StartY);

/**
\brief Changes the window size.CNcomment:�ı䴰�ڴ�С CNend
\attention \n
After the window size is changed, you need to redraw the window.CNcomment:�ı䴰�ڴ�С�󣬴�����Ҫ�ػ� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] Width Window width.CNcomment:���ڿ�� CNend
\param[in] Height Window height.CNcomment: ���ڸ߶� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVSURFACEPF
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_GetWindowRect
*/
HI_S32 HI_GO_ResizeWindow(HI_HANDLE Window, HI_S32 Width, HI_S32 Height);

/**
\brief Obtains the z-order of a window. The smaller the z-order, the lower the position of the window.CNcomment:��ȡ����Z��z��ֵС�Ĵ��ڱ�ֵ�󴰿ڸ��ǡ�CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[out] pZOrder Address for storing the window Z-order. The value cannot be empty.CNcomment:�洢����Z��ĵ�ַ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_ChangeWindowZOrder
*/
HI_S32 HI_GO_GetWindowZOrder(HI_HANDLE Window, HI_U32* pZOrder);


/**
\brief Changes the z-order of a window.CNcomment:���Ĵ���Z�� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] EnType Window z-order adjustment mode.CNcomment:����Z�������ʽ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVZORDERTYPE
\retval ::HIGO_ERR_LOCKED

\see \n
::HI_GO_GetWindowZOrder
*/
HI_S32 HI_GO_ChangeWindowZOrder(HI_HANDLE Window, HIGO_ZORDER_E EnType);

/**
\brief Obtains the window transparency.CNcomment:��ȡ���ڿɼ��� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[out] pOpacity Address for storing the information about window transparency. The value cannot be empty.CNcomment:�洢���ڲ�͸���ȵĵ�ַ������Ϊ�գ�255Ϊ��͸�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_SetWindowOpacity
*/
HI_S32 HI_GO_GetWindowOpacity(HI_HANDLE Window, HI_U8* pOpacity);

/**
\brief Sets the window transparency.CNcomment:���ô��ڲ�͸���� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] Opacity Window transparency, ranging from 0 to 255. 0: opaque, 255: full transparent.CNcomment:���ڲ�͸���ȣ���ΧΪ0~255, ��Ϊ0ʱ���ô��ڲ��ɼ���255ʱ��������ȫ�ɼ� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetWindowOpacity
*/
HI_S32 HI_GO_SetWindowOpacity(HI_HANDLE Window, HI_U8 Opacity);

/**
\brief Sets the window colorkey.CNcomment:���ô��ڵ�colorkey CNend
\attention \n
\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] ColorKey Colorkey value.CNcomment:Colorkeyֵ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_LOCKED

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetWindowColorkey(HI_HANDLE Window, HI_COLOR ColorKey);

/**
\brief Obtains the surface handle of a window.CNcomment:��ȡ���ڵ�surface��� CNend
\attention \n
If the window has dual buffers and you have called HI_GO_FlipWindowSurface, you need to call HI_GO_GetWindowSurface
again to obtain another buffer for drawing.
CNcomment:�����˫buffer��window��HI_GO_FlipWindowSurface֮����Ҫ���µ��øýӿڣ��Ӷ���ȡ����һ��buffer���л��� CNend

\param[in] Window   Window handle.CNcomment:���ھ�� CNend
\param[in] pSurface Address for storing window surfaces. The value cannot be empty.CNcomment:�洢����surface����ĵ�ַ������Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_FlipWindowSurface \n
*/
HI_S32 HI_GO_GetWindowSurface(HI_HANDLE Window, HI_HANDLE* pSurface);

/**
\brief Refreshes a window.CNcomment:ˢ�´��� CNend
\attention \n
After changing the window surface contents, you need to call the API for the changes to take effect.
CNcomment:���´���surface����֮����Ҫ���ô˽ӿڲ�����Ч CNend

\param[in] Window Window handle.CNcomment:���ھ�� CNend
\param[in] pRect Updated window region.CNcomment:���µĴ������� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_UpdateWindow(HI_HANDLE Window, const HI_RECT* pRect);

/**
\brief Changes the graphics layer to which a window belongs and retains the window.CNcomment:�޸Ĵ�������ͼ�㣬��ɾ������ CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] hWindow Window handle.CNcomment: ���ھ�� CNend
\param[in] hNewLayer  Handle of the new layer.CNcomment:��ͼ���� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_ChangeWindowLayer(HI_HANDLE hWindow, HI_HANDLE hNewLayer);

/**
\brief Switches the surface of a window. This function is valid only for the window that has double surfaces.CNcomment:�л�window ��surface������double surface��window��Ч CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] hWindow Window handle.CNcomment: ���ھ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/

HI_S32 HI_GO_FlipWindowSurface(HI_HANDLE hWindow);

/**
\brief Set window memory mode. CNcomment:���ô��ڵ��ڴ�ģʽ CNend
\attention \n
Must set the mode before Window create,Default mode is HIGO_WNDMEM_SEP.
CNcomment:�����ڴ�������ǰָ���ڴ�ģʽ,Ĭ��Ϊ��ռ�ڴ�ģʽ.��֧��
��ռ�ڴ洰�ں͹����ڴ洰��ͬʱ����. CNend
\param[in] Window memory mode. CNcomment:�����ڴ�ģʽ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetWindowMode(HIGO_WNDMEM_E enMode);

/**
\brief Get window memory mode. CNcomment:��ȡ���ڵ��ڴ�ģʽ CNend
\attention \n
\param[in]
\param[out]  Window memory mode. CNcomment:�����ڴ�ģʽ CNend
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_GetWindowMode(HIGO_WNDMEM_E *penMode);

/**
\brief Get clip region of window. CNcomment:��ȡ���ڵļ����� CNend
\attention \n
In HIGO_WNDMEM_SHARED mode, Can use this API to get window clip region, and to draw.
CNcomment:�ڴ��ڹ����ڴ�ģʽ��,ʹ�øýӿڿ��Ի�ȡ���ڵļ�����,
���л���. CNend
\param[in] window handle. CNcomment:���ھ�� CNend
\param[out]  window clip region. CNcomment:���ڼ����� CNend
\param[out]  number of clip region. CNcomment:��������� CNend
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_GetWindowClipRgn(HI_HANDLE hWindow,  HI_REGION **ppClipRgn,
    HI_U32 *pu32Num);

/**
\brief Get window invalid region. CNcomment:��ȡ���ھ������Ч�� CNend
\attention \n
CNcomment:�ýӿڿ��Ի�ȡhWindow����ͼ������д��ڵ���Ч��(����е�
��).ÿ�����ڵ���Ч��Ϊһ������,�þ���ֻ����Ч��İ���,��Ҫ
�ʹ��ڼ����������к����,���ܱ�֤��ʾ����ȷ.
���޸Ĵ��ڵ�͸����(�����ڴ�ģʽ��ֻ��͸���Ͳ�͸,��֧��
��͸,���а�͸��͸������)/�ƶ�����ʱ,����ʹ�øýӿڻ�ȡ
�ɴ˲�����������Ч��,Ȼ����»���. CNend
\param[in] window handle. CNcomment:���ھ�� CNend
\param[out]  window invalid region. CNcomment:������Ч�� CNend
\param[out]  number of invalid region. CNcomment:��Ч����� CNend
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_GetWindowInvRgn(HI_HANDLE hWindow, HIGO_INVRGN_S **ppInvRgn,HI_U32 *pu32Num);
/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_GO_WINC_H__ */
