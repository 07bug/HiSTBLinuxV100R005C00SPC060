#ifndef __HI_UNF_SUBT_H__
#define __HI_UNF_SUBT_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus*/

/*************************** Structure Definition ****************************/
/** \addtogroup      SUBTITLE */
/** @{ */  /** <!-- ��SUBTITLE�� */

/** Invalid handle in subtitle *//** CNcomment:��Ч����Ļ��� */
#define SUBT_INVALID_HANDLE   (0x0)
/** the max item(language) in Subtitling descriptor *//** CNcomment:������Ļ��(����)���� */
#define SUBT_ITEM_MAX_NUM     (32)
/** the max subtitle instance *//** CNcomment:������Ļģ��ʵ�� */
#define SUBT_INSTANCE_MAX_NUM (8)

/** Defines the subtitle data type  *//** CNcomment: ������Ļ�������� */
typedef enum hiUNF_SUBT_DATA_TYPE_E
{
    HI_UNF_SUBT_DVB  = 0x1, /**<DVB subtitle *//**<CNcomment: DVB��Ļ */
    HI_UNF_SUBT_SCTE = 0x2, /**<SCTE subtitle *//**<CNcomment: SCTE��Ļ */
    HI_UNF_SUBT_BUTT
}HI_UNF_SUBT_DATA_TYPE_E;

/** Defines the type used to code the subtitle *//** CNcomment:������Ļ��������ö�� */
typedef enum hiUNF_SUBT_TYPE_E
{
    HI_UNF_SUBT_TYPE_BITMAP = 0, /**<Coding of bitmap *//**<CNcomment:λͼ���� */
    HI_UNF_SUBT_TYPE_TEXT,       /**<Coded as a string of characters *//**<CNcomment:�ı����� */
    HI_UNF_SUBT_TYPE_BUTT
}HI_UNF_SUBT_TYPE_E;

/** Defines the status of the subtitling page *//** CNcomment:������Ļҳ״̬ö�� */
typedef enum hiUNF_SUBT_PAGE_STATE_E
{
    HI_UNF_SUBT_PAGE_NORMAL_CASE        = 0,    /**<Page update, use previous page instance to display *//**<CNcomment:�ֲ����� */
    HI_UNF_SUBT_PAGE_ACQUISITION_POINT,         /**<Page refresh, use next page instance to display *//**<CNcomment:ȫ��ˢ�� */
    HI_UNF_SUBT_PAGE_MODE_CHANGE,               /**<New page, needed to display the new page *//**<CNcomment:ˢ��������Ļҳ */
    HI_UNF_SUBT_PAGE_BUTT
}HI_UNF_SUBT_PAGE_STATE_E;

/** Defines the data of the subtitle output *//** CNcomment:������Ļ������ݽṹ�� */
typedef struct hiUNF_SUBT_DATA_S
{
    HI_UNF_SUBT_TYPE_E enDataType;        /**<The type used to code the subtitle *//**<CNcomment:��Ļ�������� */
    HI_UNF_SUBT_PAGE_STATE_E enPageState; /**<The status of the subtitling page *//**<CNcomment:��Ļҳ״̬ */
    HI_U32             u32x;              /**<The horizontal address of subtitling page *//**<CNcomment:x���� */
    HI_U32             u32y;              /**<The vertical address of subtitling page *//**<CNcomment:y���� */
    HI_U32             u32w;              /**<The horizontal length of subtitling page *//**<CNcomment:��� */
    HI_U32             u32h;              /**<The vertical length of subtitling page *//**<CNcomment:�߶� */
    HI_U32             u32BitWidth;       /**<Bits in pixel-code *//**<CNcomment:λ�� */
    HI_U32             u32PTS;            /**<Presentation time stamp *//**<CNcomment:ʱ��� */
    HI_U32             u32Duration;       /**<The period, expressed in ms, after which a page instance is no longer valid *//**<CNcomment:����ʱ�䣬��λ��ms */
    HI_U32             u32PaletteItem;    /**<Pixels of palette *//**<CNcomment:��ɫ�峤�� */
    HI_VOID*           pvPalette;         /**<Palette data *//**<CNcomment:��ɫ������ */
    HI_U32             u32DataLen;        /**<Subtitling page data length *//**<CNcomment:��Ļ���ݳ��� */
    HI_U8*             pu8SubtData;       /**<Subtitling page data *//**<CNcomment:��Ļ���� */
    HI_U32             u32DisplayWidth;   /**<Display canvas width *//**<CNcomment:��ʾ�����Ŀ�� */
    HI_U32             u32DisplayHeight;  /**<Display canvas height *//**<CNcomment:��ʾ�����ĸ߶� */
}HI_UNF_SUBT_DATA_S;

/** Defines the item of the subtitling content *//** CNcomment:������Ļ������ṹ�� */
typedef struct hiUNF_SUBT_ITEM_S
{
    HI_U32 u32SubtPID;      /**<The pid for playing subtitle *//**<CNcomment:��Ļpid */
    HI_U16 u16PageID;       /**<The Subtitle page id *//**<CNcomment:��Ļҳid */
    HI_U16 u16AncillaryID;  /**<The Subtitle ancillary id *//**<CNcomment:��Ļ����ҳid */
}HI_UNF_SUBT_ITEM_S;

/** Defines the callback function which output the subtitling data *//** CNcomment:���������Ļ���ݵĻص����� */
typedef HI_S32 (*HI_UNF_SUBT_CALLBACK_FN)(HI_VOID* pUserData, HI_UNF_SUBT_DATA_S *pstData);

/** Defines the callback function which get current pts *//** CNcomment:�����ȡ��ǰʱ����Ļص����� */
typedef HI_S32 (*HI_UNF_SUBT_GETPTS_FN)(HI_VOID* pUserData, HI_S64 *ps64Pts);

/** Defines the parameter of subtitle instance *//** CNcomment:������Ļģ������ṹ�� */
typedef struct hiUNF_SUBT_PARAM_S
{
    HI_UNF_SUBT_ITEM_S astItems[SUBT_ITEM_MAX_NUM]; /**<The item of the subtitling content *//**<CNcomment:��Ļ���� */
    HI_U8  u8SubtItemNum;                           /**<Amount of subtitling item *//**<CNcomment:��Ļ���ݸ��� */
    HI_UNF_SUBT_CALLBACK_FN pfnCallback;            /**<Callback function in which output subtitling page data *//**<CNcomment:�ص����������������������Ļ���� */
    HI_VOID* pUserData;                             /**<User data used in callback function *//**<CNcomment:�û����ݣ�ֻ���ڻص��������� */
    HI_UNF_SUBT_DATA_TYPE_E enDataType;             /**<subtitle data type in subt module *//**<CNcomment:��subtģ�����õ���Ļ�������� */
}HI_UNF_SUBT_PARAM_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      SUBTITLE */
/** @{*/  /** <!-- [SUBTITLE] */

/**
\brief Initialize subtitle module. CNcomment:��ʼ����Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\retval ::HI_SUCCESS initialize success. CNcomment:��ʼ���ɹ���CNend
\retval ::HI_FAILURE initialize failure. CNcomment:��ʼ��ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_Init(HI_VOID);

/**
\brief DeInitialize subtitle module. CNcomment:ȥ��ʼ����Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\retval ::HI_SUCCESS deinitialize success. CNcomment:ȥ��ʼ���ɹ���CNend
\retval ::HI_FAILURE deinitialize failure. CNcomment:ȥ��ʼ��ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
 HI_S32 HI_UNF_SUBT_DeInit(HI_VOID);

/**
\brief Create subtitle module. CNcomment:������Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  pstSubtParam  parameters used in created subtitle. CNcomment:����ֵ��CNend
\param[out] phSubt        subtitle handle. CNcomment:��Ļ�����CNend
\retval ::HI_SUCCESS create success. CNcomment:�����ɹ���CNend
\retval ::HI_FAILURE create failure. CNcomment:����ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_Create(HI_UNF_SUBT_PARAM_S *pstSubtParam, HI_HANDLE *phSubt);

/**
\brief Destroy subtitle module. CNcomment:������Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\retval ::HI_SUCCESS destroy success. CNcomment:���ٳɹ���CNend
\retval ::HI_FAILURE destroy failure. CNcomment:����ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_Destroy(HI_HANDLE hSubt);

/**
\brief Select one subtitle content to output. CNcomment:�л���Ļ���ݡ�CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\param[in]  pstSubtItem   subtitle item. CNcomment:��Ļ�����CNend
\retval ::HI_SUCCESS switching success. CNcomment:�л��ɹ���CNend
\retval ::HI_FAILURE switching failure. CNcomment:�л�ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_SwitchContent(HI_HANDLE hSubt, HI_UNF_SUBT_ITEM_S *pstSubtItem);

/**
\brief Reset subtitle module. CNcomment:��λ��Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\retval ::HI_SUCCESS reset success. CNcomment:��λ�ɹ���CNend
\retval ::HI_FAILURE reset failure. CNcomment:��λʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_Reset(HI_HANDLE hSubt);

/**
\brief Update subtitle module. CNcomment:������Ļģ�顣CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\param[in]  pstSubtParam  the new subtitle content. CNcomment:�µ���Ļ������Ϣ��CNend
\retval ::HI_SUCCESS update success. CNcomment:���³ɹ���CNend
\retval ::HI_FAILURE update failure. CNcomment:����ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_Update(HI_HANDLE hSubt, HI_UNF_SUBT_PARAM_S *pstSubtParam);

/**
\brief Inject DVB subtitle stream to decoder. CNcomment:ע����Ļ���ݵ���������CNend
\attention \n
Used the PES packet syntax for carriage of DVB subtitles. CNcomment:DVB��Ļ����ʹ��PES��ʽ��CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\param[in]  u32SubtPID    the pid of subtitle stream. CNcomment:��Ļ��pid��CNend
\param[in]  pu8Data       subtitle stream data. CNcomment:��Ļ���ݡ�CNend
\param[in]  u32DataSize   the size of subtitle stream data. CNcomment:��Ļ���ݳ��ȡ�CNend
\retval ::HI_SUCCESS inject success. CNcomment:ע��ɹ���CNend
\retval ::HI_FAILURE inject failure. CNcomment:ע��ʧ�ܡ�CNend
\see \n
none. CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_InjectData(HI_HANDLE hSubt, HI_U32 u32SubtPID, HI_U8* pu8Data, HI_U32 u32DataSize);

/**
\brief Register the callback function geted current pts.
CNcomment:ע���ȡ��ǰʱ����Ļص�������CNend
\attention \n
none. CNcomment:�ޡ�CNend
\param[in]  hSubt         subtitle handle. CNcomment:��Ļ�����CNend
\param[in]  pfnGetPts     callback funtion which geted current pts. CNcomment:��ȡ��ǰʱ����Ļص�������CNend
\param[in]  pUserData   userdata which used in callback funtion. CNcomment:�ص��������û����ݡ�CNend
\retval   ::HI_SUCCESS    success. CNcomment:�ɹ���CNend
\retval   ::HI_FAILURE    failure. CNcomment:ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_SUBT_RegGetPtsCb(HI_HANDLE hSubt, HI_UNF_SUBT_GETPTS_FN pfnGetPts, HI_VOID* pUserData);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus*/

#endif
