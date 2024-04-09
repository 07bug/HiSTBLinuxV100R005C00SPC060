/**
 \file
 \brief Subtitle output Module
 \author Shenzhen Hisilicon Co., Ltd.
 \version 1.0
 \author
 \date 2010-03-10
 */

#ifndef __HI_UNF_SO_H__
#define __HI_UNF_SO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup     SUBTITLEOUT */
/** @{ */  /** <!-- ��SUBTITLEOUT�� */

/** Number of palette *//** CNcomment:��ɫ����ɫ���� */
#define HI_UNF_SO_PALETTE_ENTRY (256)

/** Invalid pts value *//** CNcomment:��Ч��PTSֵ */
#define HI_UNF_SO_NO_PTS        (-1)

/** The max node in SO *//** CNcomment:SO�ܻ�������ڵ��� */
#define HI_UNF_SO_MAX_NODE_NUM  (20)

/** The max buffer size *//** CNcomment:SO���Ļ��泤�� */
#define HI_UNF_SO_MAX_BUFFER_SIZE (0x200000)


/** Subtitle type *//** CNcomment:��Ļ���� */
typedef enum hiUNF_SO_SUBTITLE_TYPE_E
{
    HI_UNF_SUBTITLE_BITMAP = 0x0,  /**<Bmp subtitle *//**<CNcomment:ͼ����Ļ */
    HI_UNF_SUBTITLE_TEXT,          /**<Text subtitle *//**<CNcomment:string��Ļ */
    HI_UNF_SUBTITLE_ASS,           /**<Ass/ssa sbutitle *//**<CNcomment:ass��Ļ */
    HI_UNF_SUBTITLE_BUTT
} HI_UNF_SO_SUBTITLE_TYPE_E;

/** Message type of subtitle *//** CNcomment:��ʾ��Ϣ������teltext������ʾ�Ͳ���������Ϣ */
typedef enum hiUNF_SO_DISP_MSG_TYPE_E
{
    HI_UNF_SO_DISP_MSG_NORM  = 0x0,     /**<Draw the subtitle *//**<CNcomment:������ʾ���� */
    HI_UNF_SO_DISP_MSG_ERASE,           /**<Clear the subtitle *//**<CNcomment:���� */
    HI_UNF_SO_DISP_MSG_END              /**<Message of drawing a page *//**<CNcomment:��ҳ��ʾ���� */
} HI_UNF_SO_DISP_MSG_TYPE_E;

/** The parameter of clear region *//** CNcomment:�������� */
typedef struct hiUNF_SO_CLEAR_PARAM_S
{
    HI_U32 x, y, w, h;     /**<Postion of clearing *//**<CNcomment:����λ�ú͸߿���Ϣ */
    HI_S64 s64ClearTime;   /**<Clear operation time,larger than or equal to s64NodePts+u32Duration*//**<CNcomment:��������������ʱ��,���ڵ���s64NodePts+u32Duration */
    HI_S64 s64NodePts;     /**<the present pts of sub *//**<CNcomment:��Ļ��ʾʱ��� */
    HI_U32 u32Duration;    /**<the present duration of sub *//**<CNcomment:��Ļ��ʾʱ�䳤�� */
} HI_UNF_SO_CLEAR_PARAM_S;

/** Color components  *//** CNcomment:��ɫ�ṹ */
typedef struct hiUNF_SO_COLOR_S
{
    HI_U8 u8Red;      /**<Red component *//**<CNcomment:R������ɫֵ */
    HI_U8 u8Green;    /**<Green component *//**<CNcomment:G������ɫֵ */
    HI_U8 u8Blue;     /**<Blue component *//**<CNcomment:B������ɫֵ */
    HI_U8 u8Alpha;    /**<Alpha component *//**<CNcomment:͸���ȣ�ֵΪ0Ϊ͸����0xFFΪ��͸�� */
} HI_UNF_SO_COLOR_S;

/** Information of bitmap subtitle *//** CNcomment:ͼ����Ļ��Ϣ */
typedef struct hiUNF_SO_GFX_S
{
    HI_S64 s64Pts;         /**<Start a display time, unit is Millisecond *//**<CNcomment:��ʾʱ�������λms */
    HI_U32 u32Duration;    /**<Duration of displaying, unit is Millisecond *//**<CNcomment:��ʾʱ������λms */
    HI_U32 u32Len;         /**<Bytes of subtitle data *//**<CNcomment:���ݳ��ȣ���λ�ֽ� */
    HI_U8  *pu8PixData;    /**<Data of subtitle *//**<CNcomment:ͼ������ */

    HI_UNF_SO_DISP_MSG_TYPE_E enMsgType;                   /**<Type of display message *//**<CNcomment:��ʾ��Ϣ���� */
    HI_UNF_SO_COLOR_S stPalette[HI_UNF_SO_PALETTE_ENTRY];  /**<Palette *//**<CNcomment:��ɫ�壬ARGB8888 */
    HI_S32 s32BitWidth;    /**<Bits of Pix *//**<CNcomment:����λ�� , ����Ϊ 2,4,8λ*/
    HI_U32 x, y, w, h;     /**<Position of display subtitle *//**<CNcomment:��ʾλ�ú͸߿���Ϣ */
    HI_U32 u32CanvasWidth;   /**<Display canvas width *//**<CNcomment:��ʾ�����Ŀ����Ϣ */
    HI_U32 u32CanvasHeight;  /**<Display canvas height *//**<CNcomment:��ʾ�����ĸ߶���Ϣ */
} HI_UNF_SO_GFX_S;

/** Infomation of text subtitle *//** CNcomment:�ı���Ļ��Ϣ */
typedef struct hiUNF_SO_TEXT_S
{
    HI_S64 s64Pts;              /**<Start a display time, unit is Millisecond *//**<CNcomment:��ʾʱ�������λms */
    HI_U32 u32Duration;         /**<Duration of displaying, unit is Millisecond *//**<CNcomment:��ʾʱ������λms */
    HI_U32 u32Len;              /**<Bytes of subtitle data *//**<CNcomment:��Ļ���ݳ��ȣ���λ�ֽ� */
    HI_U8 *pu8Data;             /**<Data of subtitle *//**<CNcomment:��Ļ���� */

    HI_U32 x, y, w, h;          /**<Position of display subtitle *//**<CNcomment:��ʾλ�ú͸߿���Ϣ */
} HI_UNF_SO_TEXT_S;

/** Infomation of ass/ssa subtitle *//** CNcomment:ass��Ļ��Ϣ */
typedef struct hiUNF_SO_ASS_S
{
    HI_S64 s64Pts;                /**<Start a display time, unit is Millisecond *//**<CNcomment:��ʾʱ�������λms */
    HI_U32 u32Duration;           /**<Duration of displaying, unit is Millisecond *//**<CNcomment:��ʾʱ������λms */
    HI_U32 u32FrameLen;           /**<Bytes of subtitle data *//**<CNcomment:֡���ȣ���λ�ֽ� */
    HI_U8  *pu8EventData;         /**<Data of subtitle *//**<CNcomment:֡���� */
    HI_U32 u32ExtradataSize;      /**<Length of extra data *//**<CNcomment:��չ���ݳ��ȣ���λ�ֽ� */
    HI_U8  *pu8Extradata;         /**<Extra data *//**<CNcomment:��չ���� */
} HI_UNF_SO_ASS_S;

/** Infomation of subtitle *//** CNcomment:��Ļ��Ϣ */
typedef struct hiUNF_SO_SUBTITLE_INFO_S
{
    HI_UNF_SO_SUBTITLE_TYPE_E eType; /**<type *//**<CNcomment:��Ļ���� */

    union
    {
        HI_UNF_SO_GFX_S  stGfx;      /**<Gfx subtitle *//**<CNcomment:ͼ����Ļ */
        HI_UNF_SO_TEXT_S stText;     /**<Text subtitle *//**<CNcomment:�ı���Ļ */
        HI_UNF_SO_ASS_S  stAss;      /**<Ass subtitle *//**<CNcomment:ASS��Ļ */
    } unSubtitleParam;
} HI_UNF_SO_SUBTITLE_INFO_S;

/**
\brief Call back funtion of getting current play time.
CNcomment:��ȡ��ǰ����֡��ʱ����������ǰʱ����Ч��ps64CurrentPts��ֵΪHI_UNF_SO_NO_PTS��CNend
\attention \n
None
\param[in] pUserData Userdata.CNcomment:ע�ᴫ����û����ݡ�CNend
\param[out] ps64CurrentPts Current play time. CNcomment:��ǰ����֡ʱ�������λms��CNend

\retval ::HI_SUCCESS

\see \n
None
*/
typedef HI_S32 (*HI_UNF_SO_GETPTS_FN)(HI_VOID* pUserData, HI_S64 *ps64CurrentPts);

/**
\brief Callback funtion of drawing the subtitle. CNcomment:��Ļ��ͼ�ص�������CNend
\attention \n
None
\param[in] pUserData Userdata. CNcomment:ע�ᴫ����û����ݡ�CNend
\param[in] pstInfo Information of subtitle. CNcomment:��Ļ��Ϣ��CNend
\param[in] pArg User data. CNcomment:��չ���ݡ�CNend

\retval ::HI_SUCCESS

\see \n
None
*/
typedef HI_S32 (*HI_UNF_SO_ONDRAW_FN)(HI_VOID* pUserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg);

/**
\brief Call back funtion of clearing the subtitle. CNcomment:��Ļ��ʾ��ʱ���������CNend
\attention \n
None
\param[in] pUserData User data. CNcomment:ע�ᴫ����û����ݡ�CNend
\param[out] pArg Parameter of clearing the subtitle, Type is HI_UNF_SO_CLEAR_PARAM_S. CNcomment:����������ָ��HI_UNF_SO_CLEAR_PARAM_S�ṹ��CNend

\retval ::HI_SUCCESS

\see \n
None
*/
typedef HI_S32 (*HI_UNF_SO_ONCLEAR_FN)(HI_VOID* pUserData, HI_VOID *pArg);

/** @} */  /** <!-- ==== Structure Definition End ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      SUBTITLEOUT */
/** @{*/  /** <!-- [SUBTITLEOUT]*/

/**
\brief  Init SO module. CNcomment:subtitle output ģ���ʼ����CNend
\attention \n
None
\param None

\retval ::HI_SUCCESS Init success. CNcomment:��ʼ���ɹ���CNend
\retval ::HI_FAILURE Operation fail. CNcomment:��ʼ��ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_Init(HI_VOID);

/**
\brief  Deinit SO module. CNcomment:subtitle output ģ��ȥ��ʼ����CNend
\attention \n
None
\param None

\retval ::HI_SUCCESS  Deinit success. CNcomment:ȥ��ʼ���ɹ���CNend
\retval ::HI_FAILURE Operation fail. CNcomment:ȥ��ʼ��ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_DeInit(HI_VOID);

/**
\brief  Creates an SO instance. CNcomment:����һ��soʵ����CNend
\attention \n
None
\param[out] phdl Handle of SO instance. CNcomment:������ʵ����CNend

\retval ::HI_SUCCESS  Create success. CNcomment:�����ɹ��������Ч��CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_Create(HI_HANDLE *phdl);

/**
\brief  Destroy an SO instance. CNcomment:����һ��soʵ����CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend

\retval ::HI_SUCCESS  Destroy success. CNcomment:���ٳɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:����ʧ�ܣ������Ƿ���CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_Destroy(HI_HANDLE handle);

/**
\brief  Setting offset time of the subtitle. CNcomment:������Ļʱ��ƫ�ơ�CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] s64OffsetMs Offset of subtitle, unit is Millisecondes.CNcomment:��Ļ��ʾʱ��ƫ��ֵ����λms��CNend

\retval ::HI_SUCCESS  Operation success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetOffset(HI_HANDLE handle, HI_S64 s64OffsetMs);

/**
\brief  Register the callback function of getting current play time. CNcomment:ע��ʱ�����ȡ�ص�������soͨ����ȡ��ǰ����ʱ���ͬ����Ļ��CNend
\attention \n
None
\param[in] handle Handle of SO instance.CNcomment:soʵ�������CNend
\param[in] pstCallback Callback function. CNcomment:�ص�����������CNend
\param[in] pUserData User data. CNcomment:�û����ݡ�CNend

\retval ::HI_SUCCESS  Register success. CNcomment:ע��ɹ���CNend
\retval ::HI_FAILURE  Parameter invalid. CNcomment:ע��ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_RegGetPtsCb(HI_HANDLE handle, HI_UNF_SO_GETPTS_FN pstCallback, HI_VOID* pUserData);

/**
\brief  Register the callback function of drawing subtitle.
CNcomment:ע����Ļ��������ص���������������˸ú�������soʹ�øú���ʵ����Ļ�������Ļ��ʾʱ�������so�����������֪ͨ�����CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] pfnOnDraw Callback function of drawing subtitle. CNcomment:���ƺ�����CNend
\param[in] pfnOnClear Callback function of clearing subtitle. CNcomment:���������CNend
\param[in] pUserData User data. CNcomment:�û����ݡ�CNend

\retval ::HI_SUCCESS  Register success. CNcomment:ע��ɹ���CNend
\retval ::HI_FAILURE Parameter invalid. CNcomment:ע��ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_RegOnDrawCb(HI_HANDLE handle, HI_UNF_SO_ONDRAW_FN pfnOnDraw,
                                          HI_UNF_SO_ONCLEAR_FN pfnOnClear, HI_VOID* pUserData);

/**
\brief  Set the surface of drawing subtitle, if you do not set the ondraw callback function, SO painting subtitles with the surface.
CNcomment:������Ļ���ƻ�����������û������ondraw�ص���������soʹ�����õĻ�����������Ļ��CNend
\attention \n
This feature is not implemented. CNcomment:�ù���δʵ�֡�CNend
\param[in] handle Handle of SO instance.CNcomment:soʵ�������CNend
\param[in] hSurfaceHandle Handle of surface. CNcomment:���������CNend

\retval ::HI_SUCCESS Success of setting surface. CNcomment:���óɹ���CNend
\retval ::HI_FAILURE  Operation invalid. CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetDrawSurface(HI_HANDLE handle, HI_HANDLE hSurfaceHandle);

/**
\brief  Set the font of drawing subtitle.
CNcomment:������Ļ��ʾ���壬�����ý������û��������Ļ�ķ�ʽ�����á�CNend
\attention \n
This feature is not implemented. CNcomment:�ù���δʵ�֡�CNend
\param[in] handle Handle of SO instance.CNcomment:soʵ�������CNend
\param[in] hFont Handle of font instance.CNcomment:��������������CNend

\retval ::HI_SUCCESS  Success.CNcomment:���óɹ���CNend
\retval ::HI_FAILURE  Operation invalid. CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetFont(HI_HANDLE handle, HI_HANDLE hFont);

/**
\brief Set the color of drawing text subtitle.
CNcomment:������Ļ��ʾ��ɫ�������ý������û��������Ļ�ķ�ʽ�����á�CNend
\attention \n
This feature is not implemented. CNcomment:�ù���δʵ�֡�CNend
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] u32Color Value of the color. CNcomment:��ɫֵ��CNend

\retval ::HI_SUCCESS  Success. CNcomment:���óɹ���CNend
\retval ::HI_FAILURE  Operation invalid. CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetColor(HI_HANDLE handle, HI_U32 u32Color);

/**
\brief Set the position of display subtitle.
CNcomment:������Ļ��ʾ���꣬�����ý������û��������Ļ�ķ�ʽ�����á�CNend
\attention \n
This feature is not implemented. CNcomment:�ù���δʵ�֡�CNend
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] u32x Value of x coordinate.CNcomment:x���ꡣCNend
\param[in] u32y Value of y coordinate. CNcomment:y���ꡣCNend

\retval ::HI_SUCCESS  Success. CNcomment:���óɹ���CNend
\retval ::HI_FAILURE  Parameter invalid. CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetPos(HI_HANDLE handle, HI_U32 u32x, HI_U32 u32y);

/**
\brief  Getting the number in the butitle queue.
CNcomment:��ȡ����buffer��δ��ʾ����Ļ���ݸ�����CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[out] pu32SubNum Number of subtitles in queue. CNcomment:������Ļ������CNend

\retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_GetSubNumInBuff(HI_HANDLE handle, HI_U32 *pu32SubNum);

/**
\brief Clear the subtitles in queue.
CNcomment:�����Ļ�����е����ݣ���Ļ�л�ʱ������øýӿ����so��Ļ���档CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend

\retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE Operation invalid. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_ResetSubBuf(HI_HANDLE handle);

/**
\brief  Clear the subtitles in queue by PTS. If PTS is 0, the same as HI_UNF_SO_ResetSubBuf.
CNcomment:�����Ļ�����е�����,С��ָ��PTS����Ļ���屻���.���ָ��PTSֵΪ0,����ӿڵ�Ч��HI_UNF_SO_ResetSubBuf��CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend

\retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE Operation invalid. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_ResetSubBuf_ByPts(HI_HANDLE handle, HI_S64 s64Pts);

/**
\brief  Send subtitles to SO queue. If the data size and the number is larger than the value set by the user, then the transmission fails.
CNcomment:������Ļ���ݸ�so���������size�͸����������û����õ�ֵ������ʧ�ܡ�CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] pstSubInfo Data of subtitle. CNcomment:��Ļ��Ϣ��CNend
\param[in] u32TimeOut Timeout of sending subtitle. CNcomment:���ͳ�ʱʱ�䣬��λms��CNend

\retval ::HI_SUCCESS  Success. CNcomment:���ͳɹ���CNend
\retval ::HI_FAILURE  Operation fail.CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SendData(HI_HANDLE handle, const HI_UNF_SO_SUBTITLE_INFO_S *pstSubInfo, HI_U32 u32TimeOutMs);

/**
\brief  Get current subt data in SO queue.
CNcomment:��ȡSO �����У���ǰ���ڴ������Ļ���ݡ�CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] pstSubInfo Data of subtitle. CNcomment:��Ļ��Ϣ��CNend

\retval ::HI_SUCCESS  Success. CNcomment:���ͳɹ���CNend
\retval ::HI_FAILURE  Operation fail.CNcomment:����ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_GetCurData(HI_HANDLE handle, HI_UNF_SO_SUBTITLE_INFO_S *pstSubInfo);

/**
\brief  Setting max interval time of the subtitle.
CNcomment:������Ļ����ʱ��ƫ�CNend
\attention \n
None
\param[in] handle Handle of SO instance. CNcomment:soʵ�������CNend
\param[in] u32IntervalMs max interval of subtitle, unit is Millisecondes.
CNcomment:��Ļ����ʱ��ƫ��ֵ����λms��CNend

\retval ::HI_SUCCESS  Operation success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_SO_SetMaxInterval(HI_HANDLE handle, HI_U32 u32IntervalMs );

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_SO_H__ */
