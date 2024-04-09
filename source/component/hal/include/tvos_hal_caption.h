/**
 * \file
 * \brief Describes the information about the caption module.
 */

#ifndef  __TVOS_HAL_CAPTION_H__
#define __TVOS_HAL_CAPTION_H__


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
#endif /* __cplusplus */

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_CAPTION */
/** @{ */  /** <!-- [HAL_CAPTION] */

/**Module id define.*//** CNcomment:ģ��ID ���� */
#define CAPTION_HARDWARE_MODULE_ID          "caption"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define CAPTION_HARDWARE_CAPTION0           "caption0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_CAPTION */
/** @{ */  /** <!-- [HAL_CAPTION] */

/**Raw data of Teletext Caption**//** CNcomment:Teletext ԭʼ���� */
typedef struct _CAPTION_TTX_RAWDATA_S
{
    U32 u32ValidLines;      /**<bit-field lines  0..31 *//**<CNcomment:��Чλ��ʶ */
    U8  au8Lines[32][46];   /**<line data *//**<CNcomment:Teletext������ */
} CAPTION_TTX_RAWDATA_S;


/**parameters of draw bitmap event*//** CNcomment: ����bitmap��Ϣ����*/
typedef struct _CAPTION_DRAWBITMAP_CB_PARAMS_S
{
    U32 u32CanvasWidth;             /**Canvas width*//** CNcomment: �������*/
    U32 u32CanvasHeight;            /**Canvas height*//** CNcomment: �����߶�*/
    S32 s32X;                       /**Position of display (X)*//** CNcomment: ��ʾλ��(X����)*/
    S32 s32Y;                       /**Position of display (Y)*//** CNcomment: ��ʾλ��(Y����)*/
    S32 s32Width;                   /**Display width*//** CNcomment: ��ʾ���*/
    S32 s32Height;                  /**Display height*//** CNcomment: ��ʾ�߶�*/
} CAPTION_DRAWBITMAP_CB_PARAMS_S;

/**parameters of fill rect event*//** CNcomment: �����ο���Ϣ����*/
typedef struct _CAPTION_FILLRECT_CB_PARAMS_S
{
    U32 u32CanvasWidth;             /**Canvas width*//** CNcomment: �������*/
    U32 u32CanvasHeight;            /**Canvas height*//** CNcomment: �����߶�*/
    S32 s32X;                       /**Position of display (X)*//** CNcomment: ��ʾλ��(X����)*/
    S32 s32Y;                       /**Position of display (Y)*//** CNcomment: ��ʾλ��(Y����)*/
    S32 s32Width;                   /**Display width*//** CNcomment: ��ʾ���*/
    S32 s32Height;                  /**Display height*//** CNcomment: ��ʾ�߶�*/
    U32 u32Color;                   /**color*//** CNcomment: �����ɫ*/
} CAPTION_FILLRECT_CB_PARAMS_S;

/**caption event of draw *//** CNcomment:��Ļ������Ϣ */
typedef enum _CAPTION_EVENT_E
{
    CAPTION_EVENT_DRAW_BITMAP_TO_SURFACE,   /** draw bitmap event, the param is CAPTION_DRAWBITMAP_CB_PARAMS_S  *//**<CNcomment:����bitmap��Ϣ�����Ӳ�����CAPTION_DRAWBITMAP_CB_PARAMS_S */
    CAPTION_EVENT_FILL_RECT_TO_SURFACE,     /** fill rect event, the param is CAPTION_FILLRECT_CB_PARAMS_S  *//**<CNcomment:�����ο���Ϣ�����Ӳ�����CAPTION_FILLRECT_CB_PARAMS_S */
    CAPTION_EVENT_BUTT
} CAPTION_EVENT_E;


/****************�ص���������************************/

/**
 \brief RawData callbak function of Teletext Caption.CNcomment:�ش�ttx ԭʼ���ݡ�CNend
 \attention \n
  none.CNcomment: �ޡ�CNend
 \param[in] pstRawData raw data param.CNcomment:Teletext ��Ļԭʼ���ݡ�CNend
 \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
 \retval ::FAILURE  other error.CNcomment:�������� CNend
 \see \n
 none. CNcomment: �ޡ�CNend
 */
typedef S32 (*CAPTION_TTX_REQUEST_CALLBACK_PFN)(CAPTION_TTX_RAWDATA_S *pstRawData);

/**
 \brief get pts callbak function.CNcomment:��ȡPTS ���ݡ�CNend
 \attention \n
  none.CNcomment: �ޡ�CNend
 \param[in] u32UserData usr private data param.CNcomment:�û�˽�����ݡ�CNend
 \param[out] pu32CurrentPts current pts param.CNcomment:��ǰPTS ֵ��CNend
 \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
 \retval ::FAILURE  other error.CNcomment:�������� ��CNend
 \see \n
 none. CNcomment: �ޡ�CNend
 */
typedef S32 (*CAPTION_GETPTS_CALLBACK_PFN)(U32* pu32CurrentPts);

/**
 \brief draw caption callbak function.CNcomment:��Ļ���ƻص�������CNend
 \attention \n
  none.CNcomment: �ޡ�CNend
 \param[in] enEvent the event of drawing.CNcomment:������Ϣ��CNend
 \param[in] pParam the parameter of drawing event.CNcomment:������Ϣ����������CNend
 \param[in] pUserData usr private data param.CNcomment:�û�˽�����ݡ�CNend
 \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
 \retval ::FAILURE  other error.CNcomment:�������� ��CNend
 \see \n
 none. CNcomment: �ޡ�CNend
 */
typedef S32 (*CAPTION_DRAW_CALLBACK_PFN_S)(CAPTION_EVENT_E enEvent, VOID* pParam, VOID* pUserData);


/** Request raw data of Teletext Caption*//** CNcomment:����Teletext ԭʼ���� */
typedef struct _CAPTION_TTX_REQUESET_RAWDATA_S
{
    CAPTION_TTX_RAWDATA_S *pstRawData;                      /**<raw data*//**<CNcomment:ԭʼ������Ϣ */
    CAPTION_TTX_REQUEST_CALLBACK_PFN pfnRequestCallback;    /**<Callback function *//**<CNcomment:�ص����� */
} CAPTION_TTX_REQUESET_RAWDATA_S;

/**Caption Type *//** CNcomment:��Ļ���� */
typedef enum _CAPTION_TYPE_E
{
    CAPTION_TYPE_SUBT = 0,  /**<Subtitle  Data*//**<CNcomment:Subt ��Ļ���� */
    CAPTION_TYPE_TTX,       /**<Teletext Data*//**<CNcomment:ͼ����Ļ���� */
    CAPTION_TYPE_CC,        /**<Closed Caption Data*//**<CNcomment:��ʽ��Ļ���� */
    CAPTION_TYPE_BUTT       /**<Invalid Caption Data*//**<CNcomment:��Ч��Ļ���� */
} CAPTION_TYPE_E;

/** Caption init params */
/** CNcomment:Caption��ʼ������ */
typedef struct _CAPTION_INIT_PARAMS_S
{
    CAPTION_TYPE_E enCaptionType;
} CAPTION_INIT_PARAMS_S;

/** Caption term params */
/** CNcomment:Caption��ֹ���� */
typedef  struct _CAPTION_TERM_PARAM_S
{
    CAPTION_TYPE_E enCaptionType;
} CAPTION_TERM_PARAM_S;


/**Caption State *//** CNcomment:��Ļ����״̬ */
typedef enum _CAPTION_STATE_E
{
    CAPTION_STOPPED = 0,    /**<Subtitle  Stopped*//**<CNcomment: ֹͣ״̬*/
    CAPTION_RUNNING,        /**<Subtitle  Running*//**<CNcomment: ��״̬*/
    CAPTION_SHOW,           /**<Subtitle  Show*//**<CNcomment: �Ѿ��򿪣���������ʾ״̬*/
    CAPTION_HIDE,           /**<Subtitle  Hide*//**<CNcomment:  �Ѿ��򿪣�����������״̬*/
    CAPTION_BUTT,           /**<Invalid State*//**<CNcomment:  ��Ч״̬*/
} CAPTION_STATE_E;

/**Data Type of Subtitle Caption *//** CNcomment:Subt ��Ļ���� */
typedef enum _CAPTION_SUBT_DATA_E
{
    CAPTION_SUBT_DATA_DVB = 0, /**<DVB Subtitle*//**<CNcomment: ŷ����Ļ*/
    CAPTION_SUBT_DATA_SCTE,    /**<SCTE Subtitle*//**<CNcomment: ������Ļ*/
    CAPTION_SUBT_DATA_BUTT     /**<Invalid Data Type *//**<CNcomment:��ЧSubt ��Ļ����*/
} CAPTION_SUBT_DATA_E;

/**Param of Subtitle Caption *//** CNcomment:Subt ��Ļ��������*/
typedef struct _CAPTION_SUBT_PARAM_S
{
    CAPTION_SUBT_DATA_E enSubtDataType;     /**<Subtitle Data Type*//**<CNcomment: Subt ��Ļ���� */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:��ȡPTS �ص����� */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:��Ļ���ƻص����� */
} CAPTION_SUBT_PARAM_S;

/**Item Param of Subtitle Caption *//** CNcomment:Subt ��Ļ���������*/
typedef struct _CAPTION_SUBT_ITEM_S
{
    U32 u32SubtPID;     /**<Subtitle  Pid*//**<CNcomment: Subt ��ĻPID */
    U16 u16PageID;      /**<Subtitle  Page ID*//**<CNcomment: Subt ��ĻҳID */
    U16 u16AncillaryID; /**<Subtitle  Ancillary ID*//**<CNcomment: Subt ��Ļ����ҳID */
} CAPTION_SUBT_ITEM_S;

/**Output Type of Teletext Caption *//** CNcomment: ͼ�� ��Ļ�������*/
typedef enum _CAPTION_TTX_OUTPUT_TYPE_E
{
    CAPTION_TTX_OUTPUT_VBI = 1,     /**<Only VBI output *//**<CNcomment:VBI ���*/
    CAPTION_TTX_OUTPUT_OSD = 2,     /**<Only OSD output *//**<CNcomment:OSD ���*/
    CAPTION_TTX_OUTPUT_VBI_OSD = 3, /**<VBI OSD dual output *//**<CNcomment:VBI ��OSDͬʱ���*/
    CAPTION_TTX_OUTPUT_BUTT         /**<Invalid output type *//**<CNcomment:��Ч�������*/
} CAPTION_TTX_OUTPUT_TYPE_E;

/**Data Source of Teletext Caption *//** CNcomment: ͼ�� ��Ļ������Դ*/
typedef enum _CAPTION_TTX_DATA_SOURCE_E
{
    CAPTION_TTX_DATA_SOURCE_PES = 0, /**<PES Data from TS stream , has pes head*//**<PES��������TS��, ����pesͷ*/
    CAPTION_TTX_DATA_SOURCE_RAW,     /**<Simulation VBI Data in ATV , has no pes head*//**<ATV������ģ���VBI���ݣ�û��PESͷ*/
    CAPTION_TTX_DATA_SOURCE_BUTT     /**<Invalid Data Source *//**<CNcomment:��Ч��Ļ������Դ*/
} CAPTION_TTX_DATA_SOURCE_E;

/**Data Type of Teletext Caption *//** CNcomment: ͼ�� ��Ļ����*/
typedef enum _CAPTION_TTX_DATA_TYPE_E
{
    CAPTION_TTX_DATA_INITTTX = 1, /**<Initial Teletext page *//**<CNcomment:Teletext ͼ�� */
    CAPTION_TTX_DATA_TTXSUBT = 2, /**<Teletext subtitle page *//**<CNcomment:Teletext ��Ļ */
    CAPTION_TTX_DATA_BUTT         /**<Invalid teletext type *//**<CNcomment:��Ч��Teletext  ���� */
} CAPTION_TTX_DATA_TYPE_E;

/**Item param of Teletext Caption *//** CNcomment: Teletext ���������*/
typedef struct _CAPTION_TTX_PAGE_ITEM_S
{
    U8  u8MagazineNum;  /**<Teletext Magazine number *//**<CNcomment: Teletext ��־�� */
    U8  u8PageNum;      /**<Teletext Page number *//**<CNcomment:Teletext ҳ�� */
    U16 u16PageSubCode; /**<Teletext Page sub-code *//**<CNcomment:Teletext ��ҳ�� */
} CAPTION_TTX_PAGE_ITEM_S;

/** Key support list of Teletext Caption*//** CNcomment:Teletext Ĭ��֧�ֵĽ�����ʽ(������ʽ) */
typedef enum _CAPTION_TTX_KEY_E
{
    CAPTION_TTX_KEY_0,
    CAPTION_TTX_KEY_1,
    CAPTION_TTX_KEY_2,
    CAPTION_TTX_KEY_3,
    CAPTION_TTX_KEY_4,
    CAPTION_TTX_KEY_5,
    CAPTION_TTX_KEY_6,
    CAPTION_TTX_KEY_7,
    CAPTION_TTX_KEY_8,
    CAPTION_TTX_KEY_9,                 /**<Three number key to open a specified page *//**<CNcomment:�������ּ���ָ��ҳ */
    CAPTION_TTX_KEY_PREVIOUS_PAGE,     /**<Previous page *//**<CNcomment:��һҳ */
    CAPTION_TTX_KEY_NEXT_PAGE,         /**<Next page *//**<CNcomment:��һҳ */
    CAPTION_TTX_KEY_PREVIOUS_SUBPAGE,  /**<Previous subpage *//**<CNcomment:��һ ��ҳ */
    CAPTION_TTX_KEY_NEXT_SUBPAGE,      /**<Next subpage *//**<CNcomment:��һ ��ҳ */
    CAPTION_TTX_KEY_PREVIOUS_MAGAZINE, /**<Previous magazine *//**<CNcomment:��һ��־ */
    CAPTION_TTX_KEY_NEXT_MAGAZINE,     /**<Next magazine *//**<CNcomment:��һ��־ */
    CAPTION_TTX_KEY_RED,               /**<First link in packet X/27, if inexistence, Show first valid page*//**<CNcomment:X/27 ���еĵ�һ�����ӣ���X/27����ʾ�����Чҳ */
    CAPTION_TTX_KEY_GREEN,             /**<Second  link in packet X/27, if inexistence, Show second valid page*//**<CNcomment:X/27 ���еĵڶ������ӣ���X/27����ʾ�ڶ���Чҳ */
    CAPTION_TTX_KEY_YELLOW,            /**<Third  link in packet X/27, if inexistence, Show third valid page*//**<CNcomment:X/27 ���еĵ��������ӣ���X/27����ʾ������Чҳ */
    CAPTION_TTX_KEY_CYAN,              /**<Fourth  link in packet X/27, if inexistence, Show fourth valid page. you can replace it with blue key if no cyan key on the user's control unit*/
                                       /**<CNcomment:X/27 ���еĵ��ĸ����ӣ���X/27����ʾ������Чҳ�����ң������û��CYAN�����������BLUE���������*/
    CAPTION_TTX_KEY_INDEX,             /**<Sixth  link in packet X/27, if inexistence, Show index  page*//**<CNcomment:X/27 ���еĵ��������ӣ���X/27��ָ����ʼҳ */
    CAPTION_TTX_KEY_REVEAL,            /**<Reveal or hide concealed  information *//**<CNcomment:��ʾ/����conceal ��Ϣ */
    CAPTION_TTX_KEY_HOLD,              /**<Switch between start and stop auto play  *//**<CNcomment:�Զ�����/ֹͣ�Զ������л� */
    CAPTION_TTX_KEY_MIX,               /**<Switch  between  transparent and nontransparent  background *//**<CNcomment:Teletext����͸��/��͸���л� */
    CAPTION_TTX_KEY_UPDATE,            /**<Update current page*//**<CNcomment:���µ�ǰҳ */
    CAPTION_TTX_TTX_KEY_ZOOM,          /**<Send this cmd sevral times to display the upper,then the lower part of the screen and then return to the normal size teletext page*/
                                       /**<CNcomment:ͨ���������ʹ�����������ʾteletextҳ����ϰ벿�֡��°벿�֡�ȫ�� */
    CAPTION_TTX_TTX_KEY_SUBPAGE,       /**<switch from page num ipunt mode to subpage input mode*//**<CNcomment:����ҳ������ģʽת��subpage����ģʽ */
    CAPTION_TTX_TTX_KEY_CANCEL,        /**<Hide or display current page except page number, currently not support*//**<CNcomment:���ػ�����ʾ����ҳ����ĵ�ǰҳ���� */
    CAPTION_TTX_TTX_KEY_TIME,          /**<Hide or display current time*//**<CNcomment:���ػ�����ʾ��ǰʱ��*/
    CAPTION_TTX_KEY_BUTT               /**<Invalid key*//**<CNcomment:��Ч�İ��� */
} CAPTION_TTX_KEY_E;

/** Page type of Teletext Caption*//** CNcomment:Teletextҳ������ */
typedef enum _CAPTION_TTX_PAGE_TYPE_E
{
    CAPTION_TTX_PAGE_CUR,   /**<Current reveal page *//**<CNcomment:��ǰ��ʾҳ */
    CAPTION_TTX_PAGE_INDEX, /**<Initial Teletext page , if  packet X/30 exist, return index page in X/30, otherwise return default index page 100*/
                            /**<CNcomment:��ʼҳ�������X/30��������X/30��ָ����ʼҳ�����򷵻�Ĭ����ҳ100 */
    CAPTION_TTX_PAGE_LINK1, /**<First link  in packet  X/27, if  inexistence, return first valid page*//**<CNcomment:X/27���е�1�����ӣ����û�У����ص�ǰҳ�����Чҳ */
    CAPTION_TTX_PAGE_LINK2, /**<Second link  in packet  X/27, if inexistence, return second valid page*//**<CNcomment:X/27���е�2�����ӣ����û�У����ص�ǰҳ�ڶ���Чҳ */
    CAPTION_TTX_PAGE_LINK3, /**<Third link  in packet  X/27, if  inexistence, return third valid page*//**<CNcomment:X/27���е�3�����ӣ����û�У����ص�ǰҳ������Чҳ */
    CAPTION_TTX_PAGE_LINK4, /**<Fourth  link  in packet  X/27, if  inexistence, return fourth valid page*//**<CNcomment:X/27���е�4�����ӣ����û�У����ص�ǰҳ������Чҳ */
    CAPTION_TTX_PAGE_LINK5, /**<Fifth link  in packet  X/27, if inexistence, return fifth valid page*//**<CNcomment:X/27���е�5�����ӣ����û�У�����0ff:3f7f */
    CAPTION_TTX_PAGE_LINK6, /**<Sixth link  in packet  X/27, if inexistence, return Sixth valid page*//**<CNcomment:X/27���е�6�����ӣ����û�У�����0ff:3f7f */
    CAPTION_TTX_PAGE_BUTT   /**<Invalid  page type *//**<CNcomment:��Чҳ���� */
} CAPTION_TTX_PAGE_TYPE_E;

/** Checked param of Teletext Caption*//** CNcomment:Teletext������ */
typedef struct _CAPTION_TTX_CHECK_PARAM_S
{
    CAPTION_TTX_PAGE_ITEM_S  stPageInfo; /**<page item info*//**<CNcomment:ҳ��Ϣ */
    BOOL                     bSucceed;   /**<success or failure*//**<CNcomment:�Ƿ�ɹ� */
} CAPTION_TTX_CHECK_PARAM_S;

/** Get page address of Teletext Caption*//** CNcomment:��ȡTeletextҳ */
typedef struct _CAPTION_TTX_GETPAGEADDR_S
{
    CAPTION_TTX_PAGE_TYPE_E enPageType; /**<page type *//**<CNcomment:ҳ���� */
    CAPTION_TTX_PAGE_ITEM_S stPageInfo; /**<page item info*//**<CNcomment:ҳ��Ϣ */
} CAPTION_TTX_GETPAGEADDR_S;

/**User command type of Teletext Caption*//** CNcomment:Teletext �������� */
typedef enum _CAPTION_TTX_CMD_E
{
    CAPTION_TTX_CMD_KEY,          /**<(CAPTION_TTX_KEY_E *)Default alternation type, key *//**<CNcomment:������Ĭ�ϵĽ�����ʽ */
    CAPTION_TTX_CMD_OPENPAGE,     /**<(CAPTION_TTX_PAGE_ITEM_S *) Open specified page*//**<CNcomment:(CAPTION_TTX_PAGE_ITEM_S *)��ָ��ҳ */
    CAPTION_TTX_CMD_GETPAGEADDR,  /**<(CAPTION_TTX_GETPAGEADDR_S *)Get current page , index page and  link page  address*//**<CNcomment:(CAPTION_TTX_GETPAGEADDR_S *) ��ȡ��ǰ����ҳ������ҳ��ַ */
    CAPTION_TTX_CMD_CHECKPAGE,    /**<(CAPTION_TTX_CHECK_PARAM_S *) Check the specified page be received or not*//**<CNcomment:(CAPTION_TTX_CHECK_PARAM_S *) ����Ƿ��յ�������ָ����ҳ */
    CAPTION_TTX_CMD_SETREQUEST,   /**<(CAPTION_TTX_REQUESET_RAWDATA_S *) Sets up a request for teletext raw data*//**<CNcomment:(CAPTION_TTX_REQUESET_RAWDATA_S *) �����ȡteletext�е�ԭʼ���� */
    CAPTION_TTX_CMD_CLEARREQUEST, /**<(CAPTION_TTX_REQUESET_RAWDATA_S *) Clears a request set up by the HI_UNF_TTX_CMD_SETREQUEST*//**<CNcomment:(CAPTION_TTX_REQUESET_RAWDATA_S *) �ͷ���HI_UNF_TTX_CMD_SETREQUEST�������������� */
    CAPTION_TTX_CMD_BUTT          /**<Invalid command type *//**<CNcomment:��Ч�������� */
} CAPTION_TTX_CMD_E;

/**Start param of Teletext Caption*//** CNcomment:Teletext �������� */
typedef struct _CAPTION_TTX_PARAM_S
{
    CAPTION_TTX_DATA_SOURCE_E enDataSource; /**<Teletext data source *//**<CNcomment:Teletext ������Դ */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:��ȡPTS �ص����� */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:��Ļ���ƻص����� */
} CAPTION_TTX_PARAM_S;

/** Switch content param  of Teletext Caption*//** CNcomment:Teletext �����л����� */
typedef struct _CAPTION_TTX_CONTENT_S
{
    CAPTION_TTX_DATA_TYPE_E enType;            /**<Teletext content type *//**<CNcomment:Teletext�������� */
    U32                     u32ISO639LanCode;  /**<teletext iso639  language code*//**<CNcomment:Teletext  iso639����*/
    CAPTION_TTX_PAGE_ITEM_S stInitPagInfo;     /**<Init page info, if Magazine number or Page number be equal to 0xFF,set to 100th page.sub-page numbet default  0*/
                                               /**<CNcomment:��ʼҳ��Ϣ�������־�Ż�ҳ��Ϊ0xff��������Ϊ��100ҳ����ҳ��Ĭ��Ϊ0 */
} CAPTION_TTX_CONTENT_S;

/**Data type of CC Caption*//** CNcomment:CC�������� */
typedef enum _CAPTION_CC_DATA_E
{
    CAPTION_CC_DATA_608 = 0,  /**<CC608*//**<CNcomment:CC608���� */
    CAPTION_CC_DATA_708,      /**<CC708*//**<CNcomment:CC708���� */
    CAPTION_CC_DATA_ARIB,     /**<ARIB CC*//**<CNcomment:ARIB CC���� */
    CAPTION_CC_DATA_BUTT
} CAPTION_CC_DATA_E;

/**Opacity of CC Caption*//** CNcomment:CC͸���� */
typedef enum _CAPTION_CC_OPACITY_E
{
    CAPTION_CC_OPACITY_DEFAULT,         /**<default*//**<CNcomment:Ĭ��͸���� */
    CAPTION_CC_OPACITY_SOLID,           /**<opaque*//**<CNcomment:��͸�� */
    CAPTION_CC_OPACITY_FLASH,           /**<flash*//**<CNcomment:��˸ */
    CAPTION_CC_OPACITY_TRANSLUCENT,     /**<translucent*//**<CNcomment:��͸�� */
    CAPTION_CC_OPACITY_TRANSPARENT,     /**<transparent*//**<CNcomment:͸�� */
    CAPTION_CC_OPACITY_BUTT             /**<Invalid opacity *//**<CNcomment:��Ч͸������ */
} CAPTION_CC_OPACITY_E;

/**Font style of CC Caption*//** CNcomment:CC������ */
typedef enum _CAPTION_CC_FONTSTYLE_E
{
    CAPTION_CC_FONTSTYLE_DEFAULT,         /**<default*//**<CNcomment:Ĭ�������� */
    CAPTION_CC_FONTSTYLE_NORMAL,          /**<normal*//**<CNcomment:���� */
    CAPTION_CC_FONTSTYLE_ITALIC,          /**<italic*//**<CNcomment:б�� */
    CAPTION_CC_FONTSTYLE_UNDERLINE,       /**<underline*//**<CNcomment:�»��� */
    CAPTION_CC_FONTSTYLE_ITALIC_UNDERLINE,/**<italic&underline*//**<CNcomment:б�岢�Ҵ��»��� */
    CAPTION_CC_FONTSTYLE_BUTT             /**<Invalid font style *//**<CNcomment:��Ч������*/
} CAPTION_CC_FONTSTYLE_E;

/**display format of CC Caption*//** CNcomment:CC��ʾ���ڵ���ʾģʽ */
typedef enum _CAPTION_CC_DF_E
{
    CAPTION_CC_DF_720X480,   /**<caption display screen is 720*480*//**<CNcomment:��ʾ���ڵĿ����720*480 */
    CAPTION_CC_DF_720X576,   /**<caption display screen is 720*576*//**<CNcomment:��ʾ���ڵĿ����720*576 */
    CAPTION_CC_DF_960X540,   /**<caption display screen is 960*540*//**<CNcomment:��ʾ���ڵĿ����960*540 */
    CAPTION_CC_DF_1280X720,  /**<caption display screen is 1280*720*//**<CNcomment:��ʾ���ڵĿ����1280*720 */
    CAPTION_CC_DF_1920X1080, /**<caption display screen is 1920*1080*//**<CNcomment:��ʾ���ڵĿ����1920*1080 */
    CAPTION_CC_DF_BUTT       /**<Invalid display format  *//**<CNcomment:��Ч��ʾģʽ */
} CAPTION_CC_DF_E;

/**CC608 data type*//** CNcomment:CC608��������*/
typedef enum _CAPTION_CC608_DATATYPE_E
{
    CAPTION_CC_608_DATATYPE_CC1,      /**<CC1*//**<CNcomment:CC1 */
    CAPTION_CC_608_DATATYPE_CC2,      /**<CC2*//**<CNcomment:CC2 */
    CAPTION_CC_608_DATATYPE_CC3,      /**<CC3*//**<CNcomment:CC3 */
    CAPTION_CC_608_DATATYPE_CC4,      /**<CC4*//**<CNcomment:CC4 */
    CAPTION_CC_608_DATATYPE_TEXT1,    /**<TEXT1*//**<CNcomment:TEXT1 */
    CAPTION_CC_608_DATATYPE_TEXT2,    /**<TEXT2*//**<CNcomment:TEXT2 */
    CAPTION_CC_608_DATATYPE_TEXT3,    /**<TEXT3*//**<CNcomment:TEXT3 */
    CAPTION_CC_608_DATATYPE_TEXT4,    /**<TEXT4*//**<CNcomment:TEXT4 */
    CAPTION_CC_608_DATATYPE_BUTT      /**<Invalid CC608 data type  *//**<CNcomment:��ЧCC608��������*/
} CAPTION_CC608_DATATYPE_E;

/**CC608 config param *//** CNcomment:CC608 ������Ϣ���� */
typedef struct _CAPTION_CC608_ATTR_S
{
    CAPTION_CC608_DATATYPE_E     enCC608DataType;      /**<CC608 data type *//**<CNcomment:����cc608�������� */
    U32                          u32CC608TextColor;    /**<CC608 text color *//**<CNcomment:����cc608������ɫ */
    CAPTION_CC_OPACITY_E         enCC608TextOpac;      /**<CC608 text opacity *//**<CNcomment:����cc608����͸���� */
    U32                          u32CC608BgColor;      /**<CC608 background color *//**<CNcomment:����cc608����ɫ */
    CAPTION_CC_OPACITY_E         enCC608BgOpac;        /**<CC608 background opacity *//**<CNcomment:����cc608����͸���� */
    CAPTION_CC_FONTSTYLE_E       enCC608FontStyle;     /**<CC608 font style *//**<CNcomment:����cc608������ */
    CAPTION_CC_DF_E              enCC608DispFormat;    /**<CC608 display format of caption display screen *//**<CNcomment:����cc608��ʾģʽ */
    BOOL                         bLeadingTailingSpace; /**< CC608 leading/tailing space flag*//**<CNcomment: �Ƿ���ʾleading/tailing space*/
} CAPTION_CC608_ATTR_S;

/**CC708 service channel*//** CNcomment:CC708 �ķ���ͨ����*/
typedef enum _CAPTION_CC708_SERVICE_NUM_E
{
    CAPTION_CC_708_SERVICE1 = 1,            /**<CC708 service 1*//**<CNcomment:CC708����1 */
    CAPTION_CC_708_SERVICE2,                /**<CC708 service 2*//**<CNcomment:CC708����2 */
    CAPTION_CC_708_SERVICE3,                /**<CC708 service 3*//**<CNcomment:CC708����3 */
    CAPTION_CC_708_SERVICE4,                /**<CC708 service 4*//**<CNcomment:CC708����4 */
    CAPTION_CC_708_SERVICE5,                /**<CC708 service 5*//**<CNcomment:CC708����5 */
    CAPTION_CC_708_SERVICE6,                /**<CC708 service 6*//**<CNcomment:CC708����6 */
    /* enum values 7 - 63 are reserved for Extended Caption Services */
    CAPTION_CC_708_LINE21_DATA_SERVICE1 = 64,   /**<CC1*//**<CNcomment:CC708����CC608�ķ���CC1 */
    CAPTION_CC_708_LINE21_DATA_SERVICE2,        /**<CC2*//**<CNcomment:CC708����CC608�ķ���CC2 */
    CAPTION_CC_708_LINE21_DATA_SERVICE3,        /**<CC3*//**<CNcomment:CC708����CC608�ķ���CC3 */
    CAPTION_CC_708_LINE21_DATA_SERVICE4,        /**<CC4*//**<CNcomment:CC708����CC608�ķ���CC4 */
    CAPTION_CC_708_SERVICE_BUTT                 /**<Invalid CC708 service channel *//**<CNcomment:��ЧCC708 �ķ���ͨ����*/
} CAPTION_CC708_SERVICE_NUM_E;

/**CC708 font name*//** CNcomment:������ʽ */
typedef enum  _CAPTION_CC_FONTNAME_E
{
    CAPTION_CC_FN_DEFAULT,                  /**<default *//**<CNcomment:Ĭ��������ʽ */
    CAPTION_CC_FN_MONOSPACED,               /**<monospaced*//**<CNcomment:monospaced���� */
    CAPTION_CC_FN_PROPORT,                  /**<proport*//**<CNcomment:proport���� */
    CAPTION_CC_FN_MONOSPACED_NO_SERIAFS,    /**<monospaced with no seriafs*//**<CNcomment:monospaced����(�޳���) */
    CAPTION_CC_FN_PROPORT_NO_SERIAFS,       /**<proport with no seriafs*//**<CNcomment:proport����(�޳���) */
    CAPTION_CC_FN_CASUAL,                   /**<casual*//**<CNcomment:casual���� */
    CAPTION_CC_FN_CURSIVE,                  /**<cursive*//**<CNcomment:cursive���� */
    CAPTION_CC_FN_SMALL_CAPITALS,           /**<small capitals*//**<CNcomment:Сд���� */
    CAPTION_CC_FN_BUTT                      /**<Invalid CC708 font name*//**<CNcomment:��ЧCC708 ������ʽ */
} CAPTION_CC_FONTNAME_E;

/**Font size of CC Caption*//** CNcomment:CC �����С */
typedef enum _CAPTION_CC_FONTSIZE_E
{
    CAPTION_CC_FONTSIZE_DEFAULT,            /**<default font size *//**<CNcomment:Ĭ�������С */
    CAPTION_CC_FONTSIZE_SMALL,              /**<small*//**<CNcomment:С */
    CAPTION_CC_FONTSIZE_STANDARD,           /**<standard*//**<CNcomment:��׼ */
    CAPTION_CC_FONTSIZE_LARGE,              /**<large*//**<CNcomment:��*/
    CAPTION_CC_FONTSIZE_BUTT                /**<Invalid CC font size*//**<CNcomment:��ЧCC �����С */
} CAPTION_CC_FONTSIZE_E;

/**Font edge type of CC Caption*//** CNcomment:�����Ե���� */
typedef enum _CAPTION_CC_EDGETYPE_E
{
    CAPTION_CC_EDGETYPE_DEFAULT,            /**<default *//**<CNcomment:Ĭ�������Ե���� */
    CAPTION_CC_EDGETYPE_NONE,               /**<none edge type *//**<CNcomment:û�б�Ե */
    CAPTION_CC_EDGETYPE_RAISED,             /**<raised *//**<CNcomment:��Եͻ�� */
    CAPTION_CC_EDGETYPE_DEPRESSED,          /**<depressed *//**<CNcomment:��Ե���� */
    CAPTION_CC_EDGETYPE_UNIFORM,            /**<uniform *//**<CNcomment:��Եͳһ */
    CAPTION_CC_EDGETYPE_LEFT_DROP_SHADOW,   /**<left drop shadow *//**<CNcomment:������Ӱ */
    CAPTION_CC_EDGETYPE_RIGHT_DROP_SHADOW,  /**<right drop shadow *//**<CNcomment:������Ӱ */
    CAPTION_CC_EDGETYPE_BUTT                /**<Invalid CC font edge type*//**<CNcomment:��ЧCC �����Ե���� */
} CAPTION_CC_EDGETYPE_E;

/**CC708 config param *//** CNcomment:CC708 ������Ϣ���� */
typedef struct _CAPTION_CC708_ATTR_S
{
    CAPTION_CC708_SERVICE_NUM_E  enCC708ServiceNum;      /**<CC708 service number *//**<CNcomment:����cc708����ͨ���� */
    CAPTION_CC_FONTNAME_E        enCC708FontName;        /**<CC708 font name *//**<CNcomment:����cc708���� */
    CAPTION_CC_FONTSTYLE_E       enCC708FontStyle;       /**<CC708 font style *//**<CNcomment:����cc708������ */
    CAPTION_CC_FONTSIZE_E        enCC708FontSize;        /**<CC708 font size *//**<CNcomment:����cc708�����С */
    U32                          u32CC708TextColor;      /**<CC708 text color *//**<CNcomment:����cc708������ɫ */
    CAPTION_CC_OPACITY_E         enCC708TextOpac;        /**<CC708 text opacity *//**<CNcomment:����cc708����͸���� */
    U32                          u32CC708BgColor;        /**<CC708 background color *//**<CNcomment:����cc708������ɫ */
    CAPTION_CC_OPACITY_E         enCC708BgOpac;          /**<CC708 background opacity *//**<CNcomment:����cc708����͸���� */
    U32                          u32CC708WinColor;       /**<CC708 window color *//**<CNcomment:����cc708������ɫ */
    CAPTION_CC_OPACITY_E         enCC708WinOpac;         /**<CC708 window opacity *//**<CNcomment:����cc708����͸���� */
    CAPTION_CC_EDGETYPE_E        enCC708TextEdgeType;    /**<CC708 text egde type *//**<CNcomment:����cc708�����Ե���� */
    U32                          u32CC708TextEdgeColor;  /**<CC708 text edge color *//**<CNcomment:����cc708�����Ե��ɫ */
    CAPTION_CC_DF_E              enCC708DispFormat;      /**<CC708 display format of caption display screen *//**<CNcomment:����cc708��ʾģʽ */
} CAPTION_CC708_ATTR_S;

/**ARIB CC config param *//** CNcomment:ARIB CC ������Ϣ���� */
typedef struct _CAPTION_ARIBCC_ATTR_S
{
    U32  u32BufferSize;    /**<size of buffer which used to cache pes data,Recommends its value is 64K ~ 512K.note:This value can only be set when created,does not support dynamic setting*/
                           /**<CNcomment:����PES���ݵĻ�������С��ȡֵΪ64k~512K��ע��:���ֵֻ���ڴ���ʱ���ã���֧�ֶ�̬����*/
} CAPTION_ARIBCC_ATTR_S;

/**Data attribution of CC Caption*//** CNcomment:CC������Ϣ */
typedef struct _CAPTION_CC_ATTR_S
{
    CAPTION_CC_DATA_E enCCDataType; /**<CC data type *//**<CNcomment:cc�������� */
    union
    {
        CAPTION_CC608_ATTR_S stCC608ConfigParam;    /**<CC608 config param *//**<CNcomment:CC608 ������Ϣ���� */
        CAPTION_CC708_ATTR_S stCC708ConfigParam;    /**<CC708 config param *//**<CNcomment:CC708 ������Ϣ���� */
        CAPTION_ARIBCC_ATTR_S stAribCCConfigParam;  /**<ARIB CC config param *//**<CNcomment:ARIB CC ������Ϣ���� */
    } unCCConfig;
} CAPTION_CC_ATTR_S;

/**Start param of CC Caption*//** CNcomment:CC�������� */
typedef struct _CAPTION_CC_PARAM_S
{
    CAPTION_CC_DATA_E enCCDataType;         /**<CC data type *//**<CNcomment:cc�������� */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:��ȡPTS �ص����� */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:��Ļ���ƻص����� */
} CAPTION_CC_PARAM_S;

#ifdef ANDROID_HAL_MODULE_USED
/**caption module structure(Android require)*/
/**CNcomment:��Ļ���ģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _CAPTION_MODULE_S
{
    struct hw_module_t stCommon;
} CAPTION_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_CAPTION*/
/** @{*/  /** <!-- -HAL_CAPTION=*/

/**Caption device structure*//** CNcomment:��Ļ�豸�ṹ*/
typedef struct _CAPTION_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif

    /**
    \brief Caption init.CNcomment:��Ļ��ʼ�� ��CNend
    \attention \n
     repeat call return success.
    CNcomment:�������ظ����÷��سɹ���CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:��Ļ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*caption_init)(struct _CAPTION_DEVICE_S* pstDev, const CAPTION_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Caption term.CNcomment:��Ļ��ֹ ��CNend
    \attention \n
    repeat call return success.
    CNcomment:�������ظ����÷��سɹ���CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:��Ļȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*caption_term)(struct _CAPTION_DEVICE_S* pstDev, const CAPTION_TERM_PARAM_S* const pstTermParams);

    /**
    \brief Caption data inject.CNcomment:��Ļ��������ע�봦�� ��CNend
    \attention \n
    repeat call return success.
    �������ظ����÷��سɹ���CNend
    \param[in] enCaptionType caption type param.CNcomment:��Ļ���� ��CNend
    \param[in] pu8Data caption data param.CNcomment:��Ļ���� ��CNend
    \param[in] u32DataSize caption data size param. CNcomment:��Ļ���ݴ�С ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_TYPE_E

    \par example
    \code
    CAPTION_TYPE_E enCaptionType;
    enCaptionType = CAPTION_TYPE_SUBT;
    if (SUCCESS != caption_common_injectData(pstDev, enCaptionType, pu8Data, u32DataSize))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*caption_common_injectData)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TYPE_E enCaptionType, U8* pu8Data, U32 u32DataSize);

    /**
    \brief Caption position of display.CNcomment:��Ļ��ʾ���� ��CNend
    \attention \n
    repeat call return success.
    �������ظ����÷��سɹ���CNend
    \param[in] u32PosX position x.CNcomment:��ʾλ��x ��CNend
    \param[in] u32PosY position y.CNcomment:��ʾλ��y ��CNend
    \param[in] u32PosWidth the width of position. CNcomment:��ʾ��� ��CNend
    \param[in] u32PosHeight the height of position . CNcomment:��ʾ�� �ȡ�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*caption_set_window)(struct _CAPTION_DEVICE_S* pstDev, U32 u32PosX, U32 u32PosY, U32 u32PosWidth, U32 u32PosHeight);

    /*****************Subtitle��غ���*******************************/
    /**
    \brief Subtitle start.CNcomment:Subtitle ��Ļ���� ��CNend
    \attention \n
    call flow:start->setWindow->switch->inject->show->hide->stop.
    ��������:start->setWindow->switch->inject->show->hide->stop��CNend
    \param[in] stSubtParam start param.CNcomment:�������� ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_SUBT_PARAM_S

    \par example
    \code
    CAPTION_SUBT_PARAM_S stSubtParam;
    memset(&stSubtParam, 0x0, sizeof(CAPTION_SUBT_PARAM_S));
    stSubtParam.enSubtDataType = CAPTION_SUBT_DATA_DVB;
    if (SUCCESS != subt_start(pstDev, stSubtParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*subt_start)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_SUBT_PARAM_S* pstSubtParam);

    /**
    \brief Subtitle switch.CNcomment:Subtitle ��Ļ�л� ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[in] stSubtItem subt item to dispaly.CNcomment:��Ļ��ʾ�� ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_SUBT_ITEM_S

    \par example
    \code
    CAPTION_SUBT_ITEM_S stSubtItem;
    memset(&stSubtItem, 0x0, sizeof(CAPTION_SUBT_ITEM_S));
    stSubtItem.u32SubtPID = 0x1ff;
    stSubtItem.u16PageID = 0x01;
    stSubtItem.u16AncillaryID = 0x02;
    if (SUCCESS != subt_switch(pstDev, stSubtItem))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*subt_switch)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_SUBT_ITEM_S* pstSubtItem);

    /**
    \brief Subtitle show.CNcomment:Subtitle ��Ļ��ʾ ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*subt_show)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Subtitle hide.CNcomment:Subtitle ��Ļ���� ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*subt_hide)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Subtitle stop.CNcomment:Subtitle ��Ļֹͣ ��CNend
    \attention \n
    clear all display, stop all subt work no matter subt show or hide.
    ������е���Ļ��ʾ������, ��������Show ����Hide ״̬��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*subt_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief set Subtitle Items.CNcomment:���ö����Ļ������������Ƚ������Ļ�����ø���Ļģ�飬������л���Ļʱ���ٶ� ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[in] pstSubtItem the number of subt items .CNcomment:��Ļ����� ��CNend
    \param[in] pstSubtItem subt items.CNcomment:Ҫ���õ���Ļ�� ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*subt_setItems)(struct _CAPTION_DEVICE_S* pstDev, U32 u32ItemNum, CAPTION_SUBT_ITEM_S *pstSubtItem);


    /**
    \brief Subtitle get running status.CNcomment:Subtitle ��ȡ��ǰ����״̬ ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[out] penStatus subt status.CNcomment:Subtitle ��Ļ����״̬ ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_STATE_E

    \par example
    \code
    CAPTION_STATE_E enStatus;
    enStatus = CAPTION_BUTT;
    if (SUCCESS != subt_get_status(pstDev, &enStatus))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*subt_get_status)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus);

    /****************teletext��غ���************************************/
    /**
    \brief Teletext start.CNcomment:Teletext ��Ļ������CNend
    \attention \n
    call flow:start->setWindow->switch->inject->show->hide->stop.
    ��������:start->setWindow->switch->inject->show->hide->stop ��CNend
    \param[in] stTTXParam start param.CNcomment:����������CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_TTX_PARAM_S

    \par example
    \code
    CAPTION_TTX_PARAM_S stTTXParam;
    stTTXParam.enDataSource = CAPTION_TTX_DATA_SOURCE_PES;
    if (SUCCESS != ttx_start(pstDev, stTTXParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*ttx_start)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_PARAM_S* pstTTXParam);

    /**
    \brief Teletext switch.CNcomment:Teletext ��Ļ�л� ��CNend
    \attention \n
    stTTXContentParam.u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16).
    stTTXContentParam.u32ISO639LanCode ��ISO 639��ӳ���ϵ:u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16) ��CNend
    \param[in] stTTXContentParam teletext content to dispaly.CNcomment:Teletext��Ļ��ʾ���ݡ�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_TTX_CONTENT_S

    \par example
    \code
    CAPTION_TTX_CONTENT_S stTTXContentParam;
    memset(&stTTXContentParam, 0x0, sizeof(CAPTION_TTX_CONTENT_S));
    stTTXContentParam.enType = CAPTION_TTX_DATA_TTXSUBT;
    stTTXContentParam.u32ISO639LanCode = 0x656E67; //eng
    stTTXContentParam.stInitPagInfo.u8MagazineNum = 0x0;
    stTTXContentParam.stInitPagInfo.u8PageNum = 0x89;
    stTTXContentParam.stInitPagInfo.u16PageSubCode = 0x0;
    if (SUCCESS != ttx_switch(pstDev, stSubtItem))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*ttx_switch)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_CONTENT_S* pstTTXContentParam);

    /**
    \brief reset teletext buffer.CNcomment:���� Teletext buffer ��CNend
    \attention \n
    ����teletext buffer,����̨���߼�⵽teletext��������Դ�б仯ʱ��Ӧ����teletext buffer�Է�ֹ�¾�teletext���ݻ����ʾ
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    */
    S32 (*ttx_resetBuffer)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Teletext stop.CNcomment:Teletext ��Ļֹͣ ��CNend
    \attention \n
    clear all display, stop all ttx work no matter ttx show or hide.
    ������е�Teletext ��Ļ��ʾ������, ��������Show ����Hide ״̬��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    */
    S32 (*ttx_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Teletext show.CNcomment:Teletext ��Ļ��ʾ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[in] enOutputType output type.CNcomment:Teletext ��Ļ������͡�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_TTX_OUTPUT_TYPE_E

    \par example
    \code
    CAPTION_TTX_OUTPUT_TYPE_E enOutputType;
    enOutputType = CAPTION_TTX_OUTPUT_OSD;
    if (SUCCESS != ttx_show(pstDev, enOutputType))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*ttx_show)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_OUTPUT_TYPE_E enOutputType);

    /**
    \brief Teletext hide.CNcomment:Teletext ��Ļ���ء�CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[in] enOutputType output type.CNcomment:Teletext ��Ļ������͡�CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_TTX_OUTPUT_TYPE_E

    \par example
    \code
    CAPTION_TTX_OUTPUT_TYPE_E enOutputType;
    enOutputType = CAPTION_TTX_OUTPUT_OSD;
    if (SUCCESS != ttx_hide(pstDev, enOutputType))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*ttx_hide)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_OUTPUT_TYPE_E enOutputType);

    /**
    \brief  Handle user's operation.  CNcomment:TTX �û�������������CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[in] enCMD Type of command.   CNcomment:�������͡�CNend
    \param[in] pvCMDParam Parameter of  command(The parameter must be  conveted to appropriate  type at every
     specifical application), when the command is UPDATE or EXIT, the command can be NULL.
     CNcomment:�������(����Ӧ����Ҫǿ��ת��)��UPDATE/EXITʱ��ΪNULL��CNend
    \param[out] pvCMDParam    Parameter of command , when the command is  GETPAGEADDR, it points to the address of specifical  pages.
     CNcomment:���������GETPAGEADDRʱ���ҳ��ַ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*ttx_execCmd)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_CMD_E enCMD, VOID* pvCMDParam);

    /**
    \brief Teletext get running status.CNcomment:Teletext ��ȡ��ǰ����״̬ ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[out] penStatus subt status.CNcomment:Teletext ��Ļ����״̬ ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_STATE_E

    \par example
    \code
    CAPTION_STATE_E enStatus;
    enStatus = CAPTION_BUTT;
    if (SUCCESS != ttx_get_status(pstDev, &enStatus))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*ttx_get_status)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus);

    /****************CC��غ���************************************/

    /**
    \brief Closed Caption create.CNcomment:Closed Caption ��Ļ���� ��CNend
    \attention \n
    call flow:creat->setWindow->start->inject->getAttr(setAttr)->stop.
    ��������:creat->setWindow->start->inject->getAttr(setAttr)->stop��CNend
    \param[in] stCCParam create param.CNcomment:�������� ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_CC_PARAM_S

    \par example
    \code
    CAPTION_CC_PARAM_S stCCParam;
    memset(&stCCParam, 0x0, sizeof(CAPTION_CC_PARAM_S));
    stCCParam.enCCDataType = CAPTION_CC_DATA_608;
    if (SUCCESS != cc_creat(pstDev, stCCParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*cc_creat)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_CC_PARAM_S* pstCCParam);

    /**
    \brief Closed Caption destroy.CNcomment:Closed Caption ��Ļ���� ��CNend
    \attention \n
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    */
    S32 (*cc_destroy)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption start.CNcomment:Closed Caption ��Ļ���� ��CNend
    start cc data recv and display.
    ����cc ���ݵĽ��պ���ʾ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*cc_start)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption stop.CNcomment:Closed Caption ��Ļֹͣ ��CNend
    \attention \n
    stop cc data recv and display.
    ֹͣcc ���ݵĽ��պ���ʾ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*cc_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption reset.CNcomment:Closed Caption ��Ļ��λ��CNend
    \attention \n
    reset cc.
    ccģ�鸴λ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    none. CNcomment: �ޡ�CNend
    */
    S32 (*cc_reset)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption get attribution.CNcomment:Closed Caption ��ȡ��Ļ������Ϣ ��CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[out]  pstCCAttr  cc attribution structure. CNcomment: CC ������Ϣ�ṹ�塣CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_CC_ATTR_S

    \par example
    \code
    CAPTION_CC_ATTR_S stCCAttr;
    memset(&stCCAttr, 0x0, sizeof(CAPTION_CC_PARAM_S));
    stCCAttr.enCCDataType = CAPTION_CC_DATA_608;
    if (SUCCESS != cc_getAttr(pstDev, &stCCParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*cc_getAttr)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_CC_ATTR_S* pstCCAttr);

    /**
    \brief Closed Caption set display attribution. CNcomment: Closed Caption ������Ļ��ʾ������Ϣ��CNend
    \attention \n
    none. CNcomment: �ޡ�CNend
    \param[in]  stCCAttr  cc attribution structure. CNcomment:������Ϣ�ṹ�塣CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� ��CNend
    \see \n
    ::CAPTION_CC_ATTR_S

    \par example
    \code
    CAPTION_CC_ATTR_S stCCAttr;
    memset(&stCCAttr, 0x0, sizeof(CAPTION_CC_PARAM_S));
    stCCAttr.enCCDataType = CAPTION_CC_DATA_608;

    if (SUCCESS == cc_getAttr(pstDev, &stCCParam))
    {
        stCCAttr.unCCConfig.stCC608ConfigParam.enCC608DataType = CAPTION_CC_608_DATATYPE_CC1;
        if (SUCCESS != cc_setAttr(pstDev, stCCParam))
        {
            return FAILURE;
        }
    }

    \endcode
    */
    S32 (*cc_setAttr)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_CC_ATTR_S* pstCCAttr);

    /**
    \brief cc get running status.CNcomment:cc ��ȡ��ǰ����״̬ ��CNend
    \attention \n
    none.CNcomment: �ޡ�CNend
    \param[out] penStatus cc status.CNcomment:cc ��Ļ����״̬ ��CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:��������CNend
    \see \n
    ::CAPTION_STATE_E

    \par example
    \code
    CAPTION_STATE_E enStatus;
    enStatus = CAPTION_BUTT;
    if (SUCCESS != cc_get_status(pstDev, &enStatus))
    {
    return FAILURE;
    }

    \endcode
    */
    S32 (*cc_get_status)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_STATE_E* penStatus);
} CAPTION_DEVICE_S;

/**
 \brief direct get caption device api, for linux and android.CNcomment:��ȡ��Ļ�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
 \attention \n
get caption device api��for linux and andorid.
CNcomment:��ȡ��Ļ�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
 \retval  caption device pointer when success.CNcomment:�ɹ�����caption�豸ָ�롣CNend
 \retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
 \see \n
::CAPTION_DEVICE_S

 \par example
 */
CAPTION_DEVICE_S *getCaptionDevice();

/**
\brief Open HAL caption module device.CNcomment: ��HAL��Ļģ���豸 ��CNend
\attention \n
Open HAL caption module device(for compatible Android HAL).
CNcomment:��HAL��Ļģ���豸(Ϊ����Android HAL�ṹ)��CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[in] ppstDevice caption device structure.CNcomment:��Ļ�豸���ݽṹ ��CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� ��CNend
\see \n
::CAPTION_DEVICE_S

\par example
*/
static inline int caption_open(const struct hw_module_t* pstModule, CAPTION_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, CAPTION_HARDWARE_CAPTION0, (struct hw_device_t**)ppstDevice);
#else
    *ppstDevice = getCaptionDevice();
    return SUCCESS;
#endif
}


/**
\brief  Close HAL caption module device.CNcomment: �ر�HAL��Ļģ���豸 ��CNend
\attention \n
Close HAL caption module device(for compatible Android HAL).
CNcomment:�ر�HAL��Ļģ���豸(Ϊ����android  HAL�ṹ)��CNend
\param[in] pstDevice caption device structure.CNcomment:��Ļ�豸���ݽṹ ��CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� ��CNend
\see \n
::CAPTION_DEVICE_S

\par example
*/
static inline int caption_close(CAPTION_DEVICE_S* pstDevice)
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
#endif /* __cplusplus */

#endif /* __TVOS_HAL_CAPTION_H__ */
