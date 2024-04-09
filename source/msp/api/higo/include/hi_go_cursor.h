#ifndef _HI_GO_CURSOR_H
#define _HI_GO_CURSOR_H

#include "hi_go_comm.h"
#include "hi_go_gdev.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_CURSOR */
/** @{ */  /** <!-- [HIGO_CURSOR] */

typedef struct
{
    HI_HANDLE hCursor;    /**<The maximum resolution is 128x128, and the minimum resolution is 16x16 for the cursor picture. Both pixel alpha and colorkey are supported.*/
    				      /**<CNcomment: ���ͼƬ���128*128,��С16*16����, ֧������alpha��colorkey */
    HI_U32    HotspotX;   /**<Horizontal coordinate of the cursor hot spot relative to the cursor picture*//**<CNcomment: ����ȵ�X���꣬�����ͼƬ */
    HI_U32    HotspotY;   /**<Vertical coordinate of the cursor+ hot spot relative to the cursor picture*//**<CNcomment: ����ȵ�Y���꣬�����ͼƬ */
} HIGO_CURSOR_INFO_S;

/**Status of the cursor layer*//** CNcomment: ����״̬�ṹ */
typedef struct
{
    HI_BOOL bShow;             /**<Whether to display the cursor layer.*//**<CNcomment: �����Ƿ���ʾ */
} HIGO_CURSOR_STATUS_S;
/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HIGO_CURSOR */
/** @{ */  /** <!-- [HIGO_CURSOR] */

/**
\brief Initializes the cursor module.CNcomment:����ʼ�� CNend
\attention \n

\param N/A.CNcomment:�� CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment: ��ʾʧ�� CNend
\retval ::HIGO_ERR_INITFAILED
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_DeinitCursor
*/

HI_S32 HI_GO_InitCursor();

/**
\brief Deinitializes the cursor module.CNcomment:ȥ��ʼ������ʼ�� CNend
\attention \n

\param N/A.CNcomment:�� CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_InitCursor
*/

HI_S32 HI_GO_DeinitCursor();

/**
\brief  Displays the cursor layer.CNcomment:��ʾ��� CNend
\attention \n
1. The cursor of the output layer is located in the middle of the screen by default.CNcomment:1 �����Ĺ��λ��Ĭ������Ļ�м� CNend
2. You need set the cursor information before the cursor layer is displayed.CNcomment:2.show����ʱ����Ҫ�������ù�����Ϣ��CNend
\param[in] bVisible Visible status of the cursor layer. HI_TRUE: visible; HI_FASLE: invisible.CNcomment:����ɼ�״̬�� HI_TRUE:�ɼ��� HI_FASLE:���㲻�ɼ���CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NOCURSORINF
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_GetCursorStatus
::HI_GO_SetCursorInfo
*/
HI_S32 HI_GO_ShowCursor(HI_BOOL bVisible);

/**
\brief Obtains the current status of the cursor layer.CNcomment:��ȡ���㵱ǰ״̬ CNend
\attention \n
N/A.CNcomment:�� CNend

\param[out] pCursorStatus Pointer to the current status of the cursor layer. The value cannot be empty.CNcomment:���㵱ǰ״̬�ṹָ�룬����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetCursorStatus( HIGO_CURSOR_STATUS_S* pCursorStatus);

/**
\brief Moves the cursor to a specified position on a specified screen.CNcomment:�ƶ���굽ָ����Ļָ��λ�� CNend
\attention \n
The cursor position can be changed only when the cursor status is show.CNcomment:������cursorΪshow������²��ܸı���λ�� CNend

\param[in] x Horizontal coordinate (in pixel) of the cursor on the screen relative to the canvas surface of a
graphics layer.CNcomment: ��ĻX����,��λ����, �����ͼ��canvas surface CNend
\param[in] y Vertical coordinate (in pixel) of the cursor on the screen relative to the canvas surface of a graphics
layer.CNcomment:��ĻY����,��λ����, �����ͼ��canvas surface CNend

\retval ::HIGO_ERR_NOTINIT
\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorPos(HI_S32 x, HI_S32 y);

/**
\brief Obtains the coordinates of the cursor on the screen.CNcomment:ȡ�ù�����Ļ���� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[out] pX Horizontal coordinate (in pixel) of the cursor on the screen.CNcomment:������ĻX����,��λ���� CNend
\param[out] pY Vertical coordinate (in pixel) of the cursor on the screen.CNcomment:������ĻY����,��λ���� CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorPos(HI_S32* pX, HI_S32* pY);

/**
\brief Sets the hot spot of the displayed cursor picture.CNcomment:���ù�����ʾͼƬ���ȵ� CNend
\attention \n
The minimum resolution is 16x16, and the maximum resolution is 128x128 for the cursor picture. Both colorkey and
alpha are supported. CNcomment:ͼƬ��С16x16,���128x128���أ�֧��colorkey, alpha�� CNend
\param[in] pCursorInfo Information about the cursor picture and coordinates of the hot spot.CNcomment:���ͼƬ���ȵ�������Ϣ CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVSURFACESIZE
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INVHOTSPOT
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_SetCursorInfo(const HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief Obtains the information about the displayed cursor picture.CNcomment:��ȡ������ʾͼƬ��Ϣ CNend
\attention \n
\param[in] pCursorInfo Information about the cursor picture and coordinates of the hot spot.CNcomment:���ͼƬ���ȵ�������Ϣ CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32 HI_GO_GetCursorInfo(HIGO_CURSOR_INFO_S* pCursorInfo);

/**
\brief Attaches the cursor to one or more graphics layers.CNcomment:�����󶨵�ͼ���ϣ�֧��һ�����󶨵����ͼ���� CNend
\attention \n
The graphics layers to which the cursor is attached must be opened.CNcomment:���뽫���󶨵�һ���Ѿ�open��ͼ���ϡ�CNend
\param[in] hLayer CNcomment:ͼ��ID CNend

\retval ::HI_SUCCESS Layer ID.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Success.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NOTOPEN
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_AttchCursorToLayer(HI_HANDLE hLayer);

/**
\brief Detaches the cursor from graphics layers.CNcomment:�������ͼ�� CNend
\attention \n
\param[in] hLayer Layer ID.CNcomment:ͼ��ID CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HI_FAILURE The display fails.CNcomment:��ʾʧ�� CNend
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_DEPEND_CURSOR

\see \n
*/
HI_S32  HI_GO_DetachCursorFromLayer(HI_HANDLE hLayer);
/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif
