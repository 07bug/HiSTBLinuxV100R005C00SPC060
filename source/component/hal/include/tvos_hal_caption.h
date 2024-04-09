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

/**Module id define.*//** CNcomment:模块ID 定义 */
#define CAPTION_HARDWARE_MODULE_ID          "caption"

/**Device name define .*//** CNcomment:设备名称定义 */
#define CAPTION_HARDWARE_CAPTION0           "caption0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_CAPTION */
/** @{ */  /** <!-- [HAL_CAPTION] */

/**Raw data of Teletext Caption**//** CNcomment:Teletext 原始数据 */
typedef struct _CAPTION_TTX_RAWDATA_S
{
    U32 u32ValidLines;      /**<bit-field lines  0..31 *//**<CNcomment:有效位标识 */
    U8  au8Lines[32][46];   /**<line data *//**<CNcomment:Teletext行数据 */
} CAPTION_TTX_RAWDATA_S;


/**parameters of draw bitmap event*//** CNcomment: 绘制bitmap消息参数*/
typedef struct _CAPTION_DRAWBITMAP_CB_PARAMS_S
{
    U32 u32CanvasWidth;             /**Canvas width*//** CNcomment: 画布宽度*/
    U32 u32CanvasHeight;            /**Canvas height*//** CNcomment: 画布高度*/
    S32 s32X;                       /**Position of display (X)*//** CNcomment: 显示位置(X坐标)*/
    S32 s32Y;                       /**Position of display (Y)*//** CNcomment: 显示位置(Y坐标)*/
    S32 s32Width;                   /**Display width*//** CNcomment: 显示宽度*/
    S32 s32Height;                  /**Display height*//** CNcomment: 显示高度*/
} CAPTION_DRAWBITMAP_CB_PARAMS_S;

/**parameters of fill rect event*//** CNcomment: 填充矩形框消息参数*/
typedef struct _CAPTION_FILLRECT_CB_PARAMS_S
{
    U32 u32CanvasWidth;             /**Canvas width*//** CNcomment: 画布宽度*/
    U32 u32CanvasHeight;            /**Canvas height*//** CNcomment: 画布高度*/
    S32 s32X;                       /**Position of display (X)*//** CNcomment: 显示位置(X坐标)*/
    S32 s32Y;                       /**Position of display (Y)*//** CNcomment: 显示位置(Y坐标)*/
    S32 s32Width;                   /**Display width*//** CNcomment: 显示宽度*/
    S32 s32Height;                  /**Display height*//** CNcomment: 显示高度*/
    U32 u32Color;                   /**color*//** CNcomment: 填充颜色*/
} CAPTION_FILLRECT_CB_PARAMS_S;

/**caption event of draw *//** CNcomment:字幕绘制消息 */
typedef enum _CAPTION_EVENT_E
{
    CAPTION_EVENT_DRAW_BITMAP_TO_SURFACE,   /** draw bitmap event, the param is CAPTION_DRAWBITMAP_CB_PARAMS_S  *//**<CNcomment:绘制bitmap消息，附加参数是CAPTION_DRAWBITMAP_CB_PARAMS_S */
    CAPTION_EVENT_FILL_RECT_TO_SURFACE,     /** fill rect event, the param is CAPTION_FILLRECT_CB_PARAMS_S  *//**<CNcomment:填充矩形框消息，附加参数是CAPTION_FILLRECT_CB_PARAMS_S */
    CAPTION_EVENT_BUTT
} CAPTION_EVENT_E;


/****************回调函数定义************************/

/**
 \brief RawData callbak function of Teletext Caption.CNcomment:回传ttx 原始数据。CNend
 \attention \n
  none.CNcomment: 无。CNend
 \param[in] pstRawData raw data param.CNcomment:Teletext 字幕原始数据。CNend
 \retval 0  SUCCESS Success.CNcomment:成功。CNend
 \retval ::FAILURE  other error.CNcomment:其它错误 CNend
 \see \n
 none. CNcomment: 无。CNend
 */
typedef S32 (*CAPTION_TTX_REQUEST_CALLBACK_PFN)(CAPTION_TTX_RAWDATA_S *pstRawData);

/**
 \brief get pts callbak function.CNcomment:获取PTS 数据。CNend
 \attention \n
  none.CNcomment: 无。CNend
 \param[in] u32UserData usr private data param.CNcomment:用户私有数据。CNend
 \param[out] pu32CurrentPts current pts param.CNcomment:当前PTS 值。CNend
 \retval 0  SUCCESS Success.CNcomment:成功。CNend
 \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
 \see \n
 none. CNcomment: 无。CNend
 */
typedef S32 (*CAPTION_GETPTS_CALLBACK_PFN)(U32* pu32CurrentPts);

/**
 \brief draw caption callbak function.CNcomment:字幕绘制回调函数。CNend
 \attention \n
  none.CNcomment: 无。CNend
 \param[in] enEvent the event of drawing.CNcomment:绘制消息。CNend
 \param[in] pParam the parameter of drawing event.CNcomment:绘制消息附带参数。CNend
 \param[in] pUserData usr private data param.CNcomment:用户私有数据。CNend
 \retval 0  SUCCESS Success.CNcomment:成功。CNend
 \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
 \see \n
 none. CNcomment: 无。CNend
 */
typedef S32 (*CAPTION_DRAW_CALLBACK_PFN_S)(CAPTION_EVENT_E enEvent, VOID* pParam, VOID* pUserData);


/** Request raw data of Teletext Caption*//** CNcomment:请求Teletext 原始数据 */
typedef struct _CAPTION_TTX_REQUESET_RAWDATA_S
{
    CAPTION_TTX_RAWDATA_S *pstRawData;                      /**<raw data*//**<CNcomment:原始数据信息 */
    CAPTION_TTX_REQUEST_CALLBACK_PFN pfnRequestCallback;    /**<Callback function *//**<CNcomment:回调函数 */
} CAPTION_TTX_REQUESET_RAWDATA_S;

/**Caption Type *//** CNcomment:字幕类型 */
typedef enum _CAPTION_TYPE_E
{
    CAPTION_TYPE_SUBT = 0,  /**<Subtitle  Data*//**<CNcomment:Subt 字幕数据 */
    CAPTION_TYPE_TTX,       /**<Teletext Data*//**<CNcomment:图文字幕数据 */
    CAPTION_TYPE_CC,        /**<Closed Caption Data*//**<CNcomment:隐式字幕数据 */
    CAPTION_TYPE_BUTT       /**<Invalid Caption Data*//**<CNcomment:无效字幕数据 */
} CAPTION_TYPE_E;

/** Caption init params */
/** CNcomment:Caption初始化参数 */
typedef struct _CAPTION_INIT_PARAMS_S
{
    CAPTION_TYPE_E enCaptionType;
} CAPTION_INIT_PARAMS_S;

/** Caption term params */
/** CNcomment:Caption终止参数 */
typedef  struct _CAPTION_TERM_PARAM_S
{
    CAPTION_TYPE_E enCaptionType;
} CAPTION_TERM_PARAM_S;


/**Caption State *//** CNcomment:字幕运行状态 */
typedef enum _CAPTION_STATE_E
{
    CAPTION_STOPPED = 0,    /**<Subtitle  Stopped*//**<CNcomment: 停止状态*/
    CAPTION_RUNNING,        /**<Subtitle  Running*//**<CNcomment: 打开状态*/
    CAPTION_SHOW,           /**<Subtitle  Show*//**<CNcomment: 已经打开，并处于显示状态*/
    CAPTION_HIDE,           /**<Subtitle  Hide*//**<CNcomment:  已经打开，但处于隐藏状态*/
    CAPTION_BUTT,           /**<Invalid State*//**<CNcomment:  无效状态*/
} CAPTION_STATE_E;

/**Data Type of Subtitle Caption *//** CNcomment:Subt 字幕类型 */
typedef enum _CAPTION_SUBT_DATA_E
{
    CAPTION_SUBT_DATA_DVB = 0, /**<DVB Subtitle*//**<CNcomment: 欧标字幕*/
    CAPTION_SUBT_DATA_SCTE,    /**<SCTE Subtitle*//**<CNcomment: 美标字幕*/
    CAPTION_SUBT_DATA_BUTT     /**<Invalid Data Type *//**<CNcomment:无效Subt 字幕类型*/
} CAPTION_SUBT_DATA_E;

/**Param of Subtitle Caption *//** CNcomment:Subt 字幕启动参数*/
typedef struct _CAPTION_SUBT_PARAM_S
{
    CAPTION_SUBT_DATA_E enSubtDataType;     /**<Subtitle Data Type*//**<CNcomment: Subt 字幕类型 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:字幕绘制回调函数 */
} CAPTION_SUBT_PARAM_S;

/**Item Param of Subtitle Caption *//** CNcomment:Subt 字幕服务项参数*/
typedef struct _CAPTION_SUBT_ITEM_S
{
    U32 u32SubtPID;     /**<Subtitle  Pid*//**<CNcomment: Subt 字幕PID */
    U16 u16PageID;      /**<Subtitle  Page ID*//**<CNcomment: Subt 字幕页ID */
    U16 u16AncillaryID; /**<Subtitle  Ancillary ID*//**<CNcomment: Subt 字幕辅助页ID */
} CAPTION_SUBT_ITEM_S;

/**Output Type of Teletext Caption *//** CNcomment: 图文 字幕输出类型*/
typedef enum _CAPTION_TTX_OUTPUT_TYPE_E
{
    CAPTION_TTX_OUTPUT_VBI = 1,     /**<Only VBI output *//**<CNcomment:VBI 输出*/
    CAPTION_TTX_OUTPUT_OSD = 2,     /**<Only OSD output *//**<CNcomment:OSD 输出*/
    CAPTION_TTX_OUTPUT_VBI_OSD = 3, /**<VBI OSD dual output *//**<CNcomment:VBI 和OSD同时输出*/
    CAPTION_TTX_OUTPUT_BUTT         /**<Invalid output type *//**<CNcomment:无效输出类型*/
} CAPTION_TTX_OUTPUT_TYPE_E;

/**Data Source of Teletext Caption *//** CNcomment: 图文 字幕数据来源*/
typedef enum _CAPTION_TTX_DATA_SOURCE_E
{
    CAPTION_TTX_DATA_SOURCE_PES = 0, /**<PES Data from TS stream , has pes head*//**<PES数据来自TS流, 包含pes头*/
    CAPTION_TTX_DATA_SOURCE_RAW,     /**<Simulation VBI Data in ATV , has no pes head*//**<ATV，来自模拟的VBI数据，没有PES头*/
    CAPTION_TTX_DATA_SOURCE_BUTT     /**<Invalid Data Source *//**<CNcomment:无效字幕数据来源*/
} CAPTION_TTX_DATA_SOURCE_E;

/**Data Type of Teletext Caption *//** CNcomment: 图文 字幕类型*/
typedef enum _CAPTION_TTX_DATA_TYPE_E
{
    CAPTION_TTX_DATA_INITTTX = 1, /**<Initial Teletext page *//**<CNcomment:Teletext 图文 */
    CAPTION_TTX_DATA_TTXSUBT = 2, /**<Teletext subtitle page *//**<CNcomment:Teletext 字幕 */
    CAPTION_TTX_DATA_BUTT         /**<Invalid teletext type *//**<CNcomment:无效的Teletext  类型 */
} CAPTION_TTX_DATA_TYPE_E;

/**Item param of Teletext Caption *//** CNcomment: Teletext 服务项参数*/
typedef struct _CAPTION_TTX_PAGE_ITEM_S
{
    U8  u8MagazineNum;  /**<Teletext Magazine number *//**<CNcomment: Teletext 杂志号 */
    U8  u8PageNum;      /**<Teletext Page number *//**<CNcomment:Teletext 页号 */
    U16 u16PageSubCode; /**<Teletext Page sub-code *//**<CNcomment:Teletext 子页号 */
} CAPTION_TTX_PAGE_ITEM_S;

/** Key support list of Teletext Caption*//** CNcomment:Teletext 默认支持的交互方式(按键方式) */
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
    CAPTION_TTX_KEY_9,                 /**<Three number key to open a specified page *//**<CNcomment:三个数字键打开指定页 */
    CAPTION_TTX_KEY_PREVIOUS_PAGE,     /**<Previous page *//**<CNcomment:上一页 */
    CAPTION_TTX_KEY_NEXT_PAGE,         /**<Next page *//**<CNcomment:下一页 */
    CAPTION_TTX_KEY_PREVIOUS_SUBPAGE,  /**<Previous subpage *//**<CNcomment:上一 子页 */
    CAPTION_TTX_KEY_NEXT_SUBPAGE,      /**<Next subpage *//**<CNcomment:下一 子页 */
    CAPTION_TTX_KEY_PREVIOUS_MAGAZINE, /**<Previous magazine *//**<CNcomment:上一杂志 */
    CAPTION_TTX_KEY_NEXT_MAGAZINE,     /**<Next magazine *//**<CNcomment:下一杂志 */
    CAPTION_TTX_KEY_RED,               /**<First link in packet X/27, if inexistence, Show first valid page*//**<CNcomment:X/27 包中的第一个链接，无X/27则显示最近有效页 */
    CAPTION_TTX_KEY_GREEN,             /**<Second  link in packet X/27, if inexistence, Show second valid page*//**<CNcomment:X/27 包中的第二个链接，无X/27则显示第二有效页 */
    CAPTION_TTX_KEY_YELLOW,            /**<Third  link in packet X/27, if inexistence, Show third valid page*//**<CNcomment:X/27 包中的第三个链接，无X/27则显示第三有效页 */
    CAPTION_TTX_KEY_CYAN,              /**<Fourth  link in packet X/27, if inexistence, Show fourth valid page. you can replace it with blue key if no cyan key on the user's control unit*/
                                       /**<CNcomment:X/27 包中的第四个链接，无X/27则显示第四有效页。如果遥控器上没有CYAN键，你可以用BLUE键来替代。*/
    CAPTION_TTX_KEY_INDEX,             /**<Sixth  link in packet X/27, if inexistence, Show index  page*//**<CNcomment:X/27 包中的第六个链接，无X/27则指向起始页 */
    CAPTION_TTX_KEY_REVEAL,            /**<Reveal or hide concealed  information *//**<CNcomment:显示/隐藏conceal 信息 */
    CAPTION_TTX_KEY_HOLD,              /**<Switch between start and stop auto play  *//**<CNcomment:自动播放/停止自动播放切换 */
    CAPTION_TTX_KEY_MIX,               /**<Switch  between  transparent and nontransparent  background *//**<CNcomment:Teletext背景透明/不透明切换 */
    CAPTION_TTX_KEY_UPDATE,            /**<Update current page*//**<CNcomment:更新当前页 */
    CAPTION_TTX_TTX_KEY_ZOOM,          /**<Send this cmd sevral times to display the upper,then the lower part of the screen and then return to the normal size teletext page*/
                                       /**<CNcomment:通过连续发送此命令依次显示teletext页面的上半部分、下半部分、全部 */
    CAPTION_TTX_TTX_KEY_SUBPAGE,       /**<switch from page num ipunt mode to subpage input mode*//**<CNcomment:输入页号输入模式转到subpage输入模式 */
    CAPTION_TTX_TTX_KEY_CANCEL,        /**<Hide or display current page except page number, currently not support*//**<CNcomment:隐藏或者显示除了页号外的当前页内容 */
    CAPTION_TTX_TTX_KEY_TIME,          /**<Hide or display current time*//**<CNcomment:隐藏或者显示当前时间*/
    CAPTION_TTX_KEY_BUTT               /**<Invalid key*//**<CNcomment:无效的按键 */
} CAPTION_TTX_KEY_E;

/** Page type of Teletext Caption*//** CNcomment:Teletext页的类型 */
typedef enum _CAPTION_TTX_PAGE_TYPE_E
{
    CAPTION_TTX_PAGE_CUR,   /**<Current reveal page *//**<CNcomment:当前显示页 */
    CAPTION_TTX_PAGE_INDEX, /**<Initial Teletext page , if  packet X/30 exist, return index page in X/30, otherwise return default index page 100*/
                            /**<CNcomment:初始页，如果有X/30包，返回X/30包指定初始页，否则返回默认首页100 */
    CAPTION_TTX_PAGE_LINK1, /**<First link  in packet  X/27, if  inexistence, return first valid page*//**<CNcomment:X/27包中第1个链接，如果没有，返回当前页最近有效页 */
    CAPTION_TTX_PAGE_LINK2, /**<Second link  in packet  X/27, if inexistence, return second valid page*//**<CNcomment:X/27包中第2个链接，如果没有，返回当前页第二有效页 */
    CAPTION_TTX_PAGE_LINK3, /**<Third link  in packet  X/27, if  inexistence, return third valid page*//**<CNcomment:X/27包中第3个链接，如果没有，返回当前页第三有效页 */
    CAPTION_TTX_PAGE_LINK4, /**<Fourth  link  in packet  X/27, if  inexistence, return fourth valid page*//**<CNcomment:X/27包中第4个链接，如果没有，返回当前页第四有效页 */
    CAPTION_TTX_PAGE_LINK5, /**<Fifth link  in packet  X/27, if inexistence, return fifth valid page*//**<CNcomment:X/27包中第5个链接，如果没有，返回0ff:3f7f */
    CAPTION_TTX_PAGE_LINK6, /**<Sixth link  in packet  X/27, if inexistence, return Sixth valid page*//**<CNcomment:X/27包中第6个链接，如果没有，返回0ff:3f7f */
    CAPTION_TTX_PAGE_BUTT   /**<Invalid  page type *//**<CNcomment:无效页类型 */
} CAPTION_TTX_PAGE_TYPE_E;

/** Checked param of Teletext Caption*//** CNcomment:Teletext检测参数 */
typedef struct _CAPTION_TTX_CHECK_PARAM_S
{
    CAPTION_TTX_PAGE_ITEM_S  stPageInfo; /**<page item info*//**<CNcomment:页信息 */
    BOOL                     bSucceed;   /**<success or failure*//**<CNcomment:是否成功 */
} CAPTION_TTX_CHECK_PARAM_S;

/** Get page address of Teletext Caption*//** CNcomment:获取Teletext页 */
typedef struct _CAPTION_TTX_GETPAGEADDR_S
{
    CAPTION_TTX_PAGE_TYPE_E enPageType; /**<page type *//**<CNcomment:页类型 */
    CAPTION_TTX_PAGE_ITEM_S stPageInfo; /**<page item info*//**<CNcomment:页信息 */
} CAPTION_TTX_GETPAGEADDR_S;

/**User command type of Teletext Caption*//** CNcomment:Teletext 命令类型 */
typedef enum _CAPTION_TTX_CMD_E
{
    CAPTION_TTX_CMD_KEY,          /**<(CAPTION_TTX_KEY_E *)Default alternation type, key *//**<CNcomment:按键，默认的交互方式 */
    CAPTION_TTX_CMD_OPENPAGE,     /**<(CAPTION_TTX_PAGE_ITEM_S *) Open specified page*//**<CNcomment:(CAPTION_TTX_PAGE_ITEM_S *)打开指定页 */
    CAPTION_TTX_CMD_GETPAGEADDR,  /**<(CAPTION_TTX_GETPAGEADDR_S *)Get current page , index page and  link page  address*//**<CNcomment:(CAPTION_TTX_GETPAGEADDR_S *) 获取当前、首页、链接页地址 */
    CAPTION_TTX_CMD_CHECKPAGE,    /**<(CAPTION_TTX_CHECK_PARAM_S *) Check the specified page be received or not*//**<CNcomment:(CAPTION_TTX_CHECK_PARAM_S *) 检查是否收到参数中指定的页 */
    CAPTION_TTX_CMD_SETREQUEST,   /**<(CAPTION_TTX_REQUESET_RAWDATA_S *) Sets up a request for teletext raw data*//**<CNcomment:(CAPTION_TTX_REQUESET_RAWDATA_S *) 请求获取teletext中的原始数据 */
    CAPTION_TTX_CMD_CLEARREQUEST, /**<(CAPTION_TTX_REQUESET_RAWDATA_S *) Clears a request set up by the HI_UNF_TTX_CMD_SETREQUEST*//**<CNcomment:(CAPTION_TTX_REQUESET_RAWDATA_S *) 释放由HI_UNF_TTX_CMD_SETREQUEST创建的数据请求 */
    CAPTION_TTX_CMD_BUTT          /**<Invalid command type *//**<CNcomment:无效命令类型 */
} CAPTION_TTX_CMD_E;

/**Start param of Teletext Caption*//** CNcomment:Teletext 启动参数 */
typedef struct _CAPTION_TTX_PARAM_S
{
    CAPTION_TTX_DATA_SOURCE_E enDataSource; /**<Teletext data source *//**<CNcomment:Teletext 数据来源 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:字幕绘制回调函数 */
} CAPTION_TTX_PARAM_S;

/** Switch content param  of Teletext Caption*//** CNcomment:Teletext 内容切换参数 */
typedef struct _CAPTION_TTX_CONTENT_S
{
    CAPTION_TTX_DATA_TYPE_E enType;            /**<Teletext content type *//**<CNcomment:Teletext内容类型 */
    U32                     u32ISO639LanCode;  /**<teletext iso639  language code*//**<CNcomment:Teletext  iso639语言*/
    CAPTION_TTX_PAGE_ITEM_S stInitPagInfo;     /**<Init page info, if Magazine number or Page number be equal to 0xFF,set to 100th page.sub-page numbet default  0*/
                                               /**<CNcomment:初始页信息，如果杂志号或页号为0xff，则设置为第100页。子页号默认为0 */
} CAPTION_TTX_CONTENT_S;

/**Data type of CC Caption*//** CNcomment:CC数据类型 */
typedef enum _CAPTION_CC_DATA_E
{
    CAPTION_CC_DATA_608 = 0,  /**<CC608*//**<CNcomment:CC608数据 */
    CAPTION_CC_DATA_708,      /**<CC708*//**<CNcomment:CC708数据 */
    CAPTION_CC_DATA_ARIB,     /**<ARIB CC*//**<CNcomment:ARIB CC数据 */
    CAPTION_CC_DATA_BUTT
} CAPTION_CC_DATA_E;

/**Opacity of CC Caption*//** CNcomment:CC透明度 */
typedef enum _CAPTION_CC_OPACITY_E
{
    CAPTION_CC_OPACITY_DEFAULT,         /**<default*//**<CNcomment:默认透明度 */
    CAPTION_CC_OPACITY_SOLID,           /**<opaque*//**<CNcomment:不透明 */
    CAPTION_CC_OPACITY_FLASH,           /**<flash*//**<CNcomment:闪烁 */
    CAPTION_CC_OPACITY_TRANSLUCENT,     /**<translucent*//**<CNcomment:半透明 */
    CAPTION_CC_OPACITY_TRANSPARENT,     /**<transparent*//**<CNcomment:透明 */
    CAPTION_CC_OPACITY_BUTT             /**<Invalid opacity *//**<CNcomment:无效透明设置 */
} CAPTION_CC_OPACITY_E;

/**Font style of CC Caption*//** CNcomment:CC字体风格 */
typedef enum _CAPTION_CC_FONTSTYLE_E
{
    CAPTION_CC_FONTSTYLE_DEFAULT,         /**<default*//**<CNcomment:默认字体风格 */
    CAPTION_CC_FONTSTYLE_NORMAL,          /**<normal*//**<CNcomment:正常 */
    CAPTION_CC_FONTSTYLE_ITALIC,          /**<italic*//**<CNcomment:斜体 */
    CAPTION_CC_FONTSTYLE_UNDERLINE,       /**<underline*//**<CNcomment:下划线 */
    CAPTION_CC_FONTSTYLE_ITALIC_UNDERLINE,/**<italic&underline*//**<CNcomment:斜体并且带下滑线 */
    CAPTION_CC_FONTSTYLE_BUTT             /**<Invalid font style *//**<CNcomment:无效字体风格*/
} CAPTION_CC_FONTSTYLE_E;

/**display format of CC Caption*//** CNcomment:CC显示窗口的显示模式 */
typedef enum _CAPTION_CC_DF_E
{
    CAPTION_CC_DF_720X480,   /**<caption display screen is 720*480*//**<CNcomment:显示窗口的宽高是720*480 */
    CAPTION_CC_DF_720X576,   /**<caption display screen is 720*576*//**<CNcomment:显示窗口的宽高是720*576 */
    CAPTION_CC_DF_960X540,   /**<caption display screen is 960*540*//**<CNcomment:显示窗口的宽高是960*540 */
    CAPTION_CC_DF_1280X720,  /**<caption display screen is 1280*720*//**<CNcomment:显示窗口的宽高是1280*720 */
    CAPTION_CC_DF_1920X1080, /**<caption display screen is 1920*1080*//**<CNcomment:显示窗口的宽高是1920*1080 */
    CAPTION_CC_DF_BUTT       /**<Invalid display format  *//**<CNcomment:无效显示模式 */
} CAPTION_CC_DF_E;

/**CC608 data type*//** CNcomment:CC608数据类型*/
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
    CAPTION_CC_608_DATATYPE_BUTT      /**<Invalid CC608 data type  *//**<CNcomment:无效CC608数据类型*/
} CAPTION_CC608_DATATYPE_E;

/**CC608 config param *//** CNcomment:CC608 配置信息参数 */
typedef struct _CAPTION_CC608_ATTR_S
{
    CAPTION_CC608_DATATYPE_E     enCC608DataType;      /**<CC608 data type *//**<CNcomment:配置cc608数据类型 */
    U32                          u32CC608TextColor;    /**<CC608 text color *//**<CNcomment:配置cc608字体颜色 */
    CAPTION_CC_OPACITY_E         enCC608TextOpac;      /**<CC608 text opacity *//**<CNcomment:配置cc608字体透明度 */
    U32                          u32CC608BgColor;      /**<CC608 background color *//**<CNcomment:配置cc608背景色 */
    CAPTION_CC_OPACITY_E         enCC608BgOpac;        /**<CC608 background opacity *//**<CNcomment:配置cc608背景透明度 */
    CAPTION_CC_FONTSTYLE_E       enCC608FontStyle;     /**<CC608 font style *//**<CNcomment:配置cc608字体风格 */
    CAPTION_CC_DF_E              enCC608DispFormat;    /**<CC608 display format of caption display screen *//**<CNcomment:配置cc608显示模式 */
    BOOL                         bLeadingTailingSpace; /**< CC608 leading/tailing space flag*//**<CNcomment: 是否显示leading/tailing space*/
} CAPTION_CC608_ATTR_S;

/**CC708 service channel*//** CNcomment:CC708 的服务通道号*/
typedef enum _CAPTION_CC708_SERVICE_NUM_E
{
    CAPTION_CC_708_SERVICE1 = 1,            /**<CC708 service 1*//**<CNcomment:CC708服务1 */
    CAPTION_CC_708_SERVICE2,                /**<CC708 service 2*//**<CNcomment:CC708服务2 */
    CAPTION_CC_708_SERVICE3,                /**<CC708 service 3*//**<CNcomment:CC708服务3 */
    CAPTION_CC_708_SERVICE4,                /**<CC708 service 4*//**<CNcomment:CC708服务4 */
    CAPTION_CC_708_SERVICE5,                /**<CC708 service 5*//**<CNcomment:CC708服务5 */
    CAPTION_CC_708_SERVICE6,                /**<CC708 service 6*//**<CNcomment:CC708服务6 */
    /* enum values 7 - 63 are reserved for Extended Caption Services */
    CAPTION_CC_708_LINE21_DATA_SERVICE1 = 64,   /**<CC1*//**<CNcomment:CC708兼容CC608的服务CC1 */
    CAPTION_CC_708_LINE21_DATA_SERVICE2,        /**<CC2*//**<CNcomment:CC708兼容CC608的服务CC2 */
    CAPTION_CC_708_LINE21_DATA_SERVICE3,        /**<CC3*//**<CNcomment:CC708兼容CC608的服务CC3 */
    CAPTION_CC_708_LINE21_DATA_SERVICE4,        /**<CC4*//**<CNcomment:CC708兼容CC608的服务CC4 */
    CAPTION_CC_708_SERVICE_BUTT                 /**<Invalid CC708 service channel *//**<CNcomment:无效CC708 的服务通道号*/
} CAPTION_CC708_SERVICE_NUM_E;

/**CC708 font name*//** CNcomment:字体样式 */
typedef enum  _CAPTION_CC_FONTNAME_E
{
    CAPTION_CC_FN_DEFAULT,                  /**<default *//**<CNcomment:默认字体样式 */
    CAPTION_CC_FN_MONOSPACED,               /**<monospaced*//**<CNcomment:monospaced字体 */
    CAPTION_CC_FN_PROPORT,                  /**<proport*//**<CNcomment:proport字体 */
    CAPTION_CC_FN_MONOSPACED_NO_SERIAFS,    /**<monospaced with no seriafs*//**<CNcomment:monospaced字体(无衬线) */
    CAPTION_CC_FN_PROPORT_NO_SERIAFS,       /**<proport with no seriafs*//**<CNcomment:proport字体(无衬线) */
    CAPTION_CC_FN_CASUAL,                   /**<casual*//**<CNcomment:casual字体 */
    CAPTION_CC_FN_CURSIVE,                  /**<cursive*//**<CNcomment:cursive字体 */
    CAPTION_CC_FN_SMALL_CAPITALS,           /**<small capitals*//**<CNcomment:小写字体 */
    CAPTION_CC_FN_BUTT                      /**<Invalid CC708 font name*//**<CNcomment:无效CC708 字体样式 */
} CAPTION_CC_FONTNAME_E;

/**Font size of CC Caption*//** CNcomment:CC 字体大小 */
typedef enum _CAPTION_CC_FONTSIZE_E
{
    CAPTION_CC_FONTSIZE_DEFAULT,            /**<default font size *//**<CNcomment:默认字体大小 */
    CAPTION_CC_FONTSIZE_SMALL,              /**<small*//**<CNcomment:小 */
    CAPTION_CC_FONTSIZE_STANDARD,           /**<standard*//**<CNcomment:标准 */
    CAPTION_CC_FONTSIZE_LARGE,              /**<large*//**<CNcomment:大*/
    CAPTION_CC_FONTSIZE_BUTT                /**<Invalid CC font size*//**<CNcomment:无效CC 字体大小 */
} CAPTION_CC_FONTSIZE_E;

/**Font edge type of CC Caption*//** CNcomment:字体边缘类型 */
typedef enum _CAPTION_CC_EDGETYPE_E
{
    CAPTION_CC_EDGETYPE_DEFAULT,            /**<default *//**<CNcomment:默认字体边缘类型 */
    CAPTION_CC_EDGETYPE_NONE,               /**<none edge type *//**<CNcomment:没有边缘 */
    CAPTION_CC_EDGETYPE_RAISED,             /**<raised *//**<CNcomment:边缘突起 */
    CAPTION_CC_EDGETYPE_DEPRESSED,          /**<depressed *//**<CNcomment:边缘凹下 */
    CAPTION_CC_EDGETYPE_UNIFORM,            /**<uniform *//**<CNcomment:边缘统一 */
    CAPTION_CC_EDGETYPE_LEFT_DROP_SHADOW,   /**<left drop shadow *//**<CNcomment:左下阴影 */
    CAPTION_CC_EDGETYPE_RIGHT_DROP_SHADOW,  /**<right drop shadow *//**<CNcomment:右下阴影 */
    CAPTION_CC_EDGETYPE_BUTT                /**<Invalid CC font edge type*//**<CNcomment:无效CC 字体边缘类型 */
} CAPTION_CC_EDGETYPE_E;

/**CC708 config param *//** CNcomment:CC708 配置信息参数 */
typedef struct _CAPTION_CC708_ATTR_S
{
    CAPTION_CC708_SERVICE_NUM_E  enCC708ServiceNum;      /**<CC708 service number *//**<CNcomment:配置cc708服务通道号 */
    CAPTION_CC_FONTNAME_E        enCC708FontName;        /**<CC708 font name *//**<CNcomment:配置cc708字体 */
    CAPTION_CC_FONTSTYLE_E       enCC708FontStyle;       /**<CC708 font style *//**<CNcomment:配置cc708字体风格 */
    CAPTION_CC_FONTSIZE_E        enCC708FontSize;        /**<CC708 font size *//**<CNcomment:配置cc708字体大小 */
    U32                          u32CC708TextColor;      /**<CC708 text color *//**<CNcomment:配置cc708字体颜色 */
    CAPTION_CC_OPACITY_E         enCC708TextOpac;        /**<CC708 text opacity *//**<CNcomment:配置cc708字体透明度 */
    U32                          u32CC708BgColor;        /**<CC708 background color *//**<CNcomment:配置cc708背景颜色 */
    CAPTION_CC_OPACITY_E         enCC708BgOpac;          /**<CC708 background opacity *//**<CNcomment:配置cc708背景透明度 */
    U32                          u32CC708WinColor;       /**<CC708 window color *//**<CNcomment:配置cc708窗口颜色 */
    CAPTION_CC_OPACITY_E         enCC708WinOpac;         /**<CC708 window opacity *//**<CNcomment:配置cc708窗口透明度 */
    CAPTION_CC_EDGETYPE_E        enCC708TextEdgeType;    /**<CC708 text egde type *//**<CNcomment:配置cc708字体边缘类型 */
    U32                          u32CC708TextEdgeColor;  /**<CC708 text edge color *//**<CNcomment:配置cc708字体边缘颜色 */
    CAPTION_CC_DF_E              enCC708DispFormat;      /**<CC708 display format of caption display screen *//**<CNcomment:配置cc708显示模式 */
} CAPTION_CC708_ATTR_S;

/**ARIB CC config param *//** CNcomment:ARIB CC 配置信息参数 */
typedef struct _CAPTION_ARIBCC_ATTR_S
{
    U32  u32BufferSize;    /**<size of buffer which used to cache pes data,Recommends its value is 64K ~ 512K.note:This value can only be set when created,does not support dynamic setting*/
                           /**<CNcomment:缓存PES数据的缓冲区大小，取值为64k~512K。注意:这个值只能在创建时设置，不支持动态设置*/
} CAPTION_ARIBCC_ATTR_S;

/**Data attribution of CC Caption*//** CNcomment:CC属性信息 */
typedef struct _CAPTION_CC_ATTR_S
{
    CAPTION_CC_DATA_E enCCDataType; /**<CC data type *//**<CNcomment:cc数据类型 */
    union
    {
        CAPTION_CC608_ATTR_S stCC608ConfigParam;    /**<CC608 config param *//**<CNcomment:CC608 配置信息参数 */
        CAPTION_CC708_ATTR_S stCC708ConfigParam;    /**<CC708 config param *//**<CNcomment:CC708 配置信息参数 */
        CAPTION_ARIBCC_ATTR_S stAribCCConfigParam;  /**<ARIB CC config param *//**<CNcomment:ARIB CC 配置信息参数 */
    } unCCConfig;
} CAPTION_CC_ATTR_S;

/**Start param of CC Caption*//** CNcomment:CC启动参数 */
typedef struct _CAPTION_CC_PARAM_S
{
    CAPTION_CC_DATA_E enCCDataType;         /**<CC data type *//**<CNcomment:cc数据类型 */
    CAPTION_GETPTS_CALLBACK_PFN pfnGetPts;  /**<get pts call bak function *//**<CNcomment:获取PTS 回调函数 */
    CAPTION_DRAW_CALLBACK_PFN_S pfnDrawCb;  /**<draw call bak function *//**<CNcomment:字幕绘制回调函数 */
} CAPTION_CC_PARAM_S;

#ifdef ANDROID_HAL_MODULE_USED
/**caption module structure(Android require)*/
/**CNcomment:字幕输出模块结构(Android对接要求) */
typedef struct _CAPTION_MODULE_S
{
    struct hw_module_t stCommon;
} CAPTION_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_CAPTION*/
/** @{*/  /** <!-- -HAL_CAPTION=*/

/**Caption device structure*//** CNcomment:字幕设备结构*/
typedef struct _CAPTION_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif

    /**
    \brief Caption init.CNcomment:字幕初始化 。CNend
    \attention \n
     repeat call return success.
    CNcomment:本函数重复调用返回成功。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:字幕初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*caption_init)(struct _CAPTION_DEVICE_S* pstDev, const CAPTION_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Caption term.CNcomment:字幕终止 。CNend
    \attention \n
    repeat call return success.
    CNcomment:本函数重复调用返回成功。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_CAPTION_INIT_FAILED  Caption init error.CNcomment:字幕去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*caption_term)(struct _CAPTION_DEVICE_S* pstDev, const CAPTION_TERM_PARAM_S* const pstTermParams);

    /**
    \brief Caption data inject.CNcomment:字幕解析数据注入处理 。CNend
    \attention \n
    repeat call return success.
    本函数重复调用返回成功。CNend
    \param[in] enCaptionType caption type param.CNcomment:字幕类型 。CNend
    \param[in] pu8Data caption data param.CNcomment:字幕数据 。CNend
    \param[in] u32DataSize caption data size param. CNcomment:字幕数据大小 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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
    \brief Caption position of display.CNcomment:字幕显示区域 。CNend
    \attention \n
    repeat call return success.
    本函数重复调用返回成功。CNend
    \param[in] u32PosX position x.CNcomment:显示位置x 。CNend
    \param[in] u32PosY position y.CNcomment:显示位置y 。CNend
    \param[in] u32PosWidth the width of position. CNcomment:显示宽度 。CNend
    \param[in] u32PosHeight the height of position . CNcomment:显示高 度。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*caption_set_window)(struct _CAPTION_DEVICE_S* pstDev, U32 u32PosX, U32 u32PosY, U32 u32PosWidth, U32 u32PosHeight);

    /*****************Subtitle相关函数*******************************/
    /**
    \brief Subtitle start.CNcomment:Subtitle 字幕启动 。CNend
    \attention \n
    call flow:start->setWindow->switch->inject->show->hide->stop.
    调用流程:start->setWindow->switch->inject->show->hide->stop。CNend
    \param[in] stSubtParam start param.CNcomment:启动参数 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief Subtitle switch.CNcomment:Subtitle 字幕切换 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[in] stSubtItem subt item to dispaly.CNcomment:字幕显示项 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief Subtitle show.CNcomment:Subtitle 字幕显示 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*subt_show)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Subtitle hide.CNcomment:Subtitle 字幕隐藏 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*subt_hide)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Subtitle stop.CNcomment:Subtitle 字幕停止 。CNend
    \attention \n
    clear all display, stop all subt work no matter subt show or hide.
    清空所有的字幕显示及工作, 不管是在Show 还是Hide 状态。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*subt_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief set Subtitle Items.CNcomment:设置多个字幕项，可以用来事先将多个字幕项设置给字幕模块，以提高切换字幕时的速度 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[in] pstSubtItem the number of subt items .CNcomment:字幕项个数 。CNend
    \param[in] pstSubtItem subt items.CNcomment:要设置的字幕项 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*subt_setItems)(struct _CAPTION_DEVICE_S* pstDev, U32 u32ItemNum, CAPTION_SUBT_ITEM_S *pstSubtItem);


    /**
    \brief Subtitle get running status.CNcomment:Subtitle 获取当前运行状态 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[out] penStatus subt status.CNcomment:Subtitle 字幕运行状态 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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

    /****************teletext相关函数************************************/
    /**
    \brief Teletext start.CNcomment:Teletext 字幕启动。CNend
    \attention \n
    call flow:start->setWindow->switch->inject->show->hide->stop.
    调用流程:start->setWindow->switch->inject->show->hide->stop 。CNend
    \param[in] stTTXParam start param.CNcomment:启动参数。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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
    \brief Teletext switch.CNcomment:Teletext 字幕切换 。CNend
    \attention \n
    stTTXContentParam.u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16).
    stTTXContentParam.u32ISO639LanCode 与ISO 639的映射关系:u32ISO639LanCode = pu8ISO639[2] + (pu8ISO639[1] << 8) + (pu8ISO639[0] << 16) 。CNend
    \param[in] stTTXContentParam teletext content to dispaly.CNcomment:Teletext字幕显示内容。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief reset teletext buffer.CNcomment:重置 Teletext buffer 。CNend
    \attention \n
    重置teletext buffer,当切台或者检测到teletext的数据来源有变化时，应重置teletext buffer以防止新旧teletext数据混合显示
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    */
    S32 (*ttx_resetBuffer)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Teletext stop.CNcomment:Teletext 字幕停止 。CNend
    \attention \n
    clear all display, stop all ttx work no matter ttx show or hide.
    清空所有的Teletext 字幕显示及工作, 不管是在Show 还是Hide 状态。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    */
    S32 (*ttx_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Teletext show.CNcomment:Teletext 字幕显示。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[in] enOutputType output type.CNcomment:Teletext 字幕输出类型。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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
    \brief Teletext hide.CNcomment:Teletext 字幕隐藏。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[in] enOutputType output type.CNcomment:Teletext 字幕输出类型。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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
    \brief  Handle user's operation.  CNcomment:TTX 用户操作处理函数。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[in] enCMD Type of command.   CNcomment:命令类型。CNend
    \param[in] pvCMDParam Parameter of  command(The parameter must be  conveted to appropriate  type at every
     specifical application), when the command is UPDATE or EXIT, the command can be NULL.
     CNcomment:命令参数(具体应用需要强制转换)，UPDATE/EXIT时可为NULL。CNend
    \param[out] pvCMDParam    Parameter of command , when the command is  GETPAGEADDR, it points to the address of specifical  pages.
     CNcomment:命令参数，GETPAGEADDR时输出页地址。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*ttx_execCmd)(struct _CAPTION_DEVICE_S* pstDev, CAPTION_TTX_CMD_E enCMD, VOID* pvCMDParam);

    /**
    \brief Teletext get running status.CNcomment:Teletext 获取当前运行状态 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[out] penStatus subt status.CNcomment:Teletext 字幕运行状态 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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

    /****************CC相关函数************************************/

    /**
    \brief Closed Caption create.CNcomment:Closed Caption 字幕创建 。CNend
    \attention \n
    call flow:creat->setWindow->start->inject->getAttr(setAttr)->stop.
    调用流程:creat->setWindow->start->inject->getAttr(setAttr)->stop。CNend
    \param[in] stCCParam create param.CNcomment:创建参数 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief Closed Caption destroy.CNcomment:Closed Caption 字幕销毁 。CNend
    \attention \n
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
    \see \n
    */
    S32 (*cc_destroy)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption start.CNcomment:Closed Caption 字幕启动 。CNend
    start cc data recv and display.
    启动cc 数据的接收和显示。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*cc_start)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption stop.CNcomment:Closed Caption 字幕停止 。CNend
    \attention \n
    stop cc data recv and display.
    停止cc 数据的接收和显示。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*cc_stop)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption reset.CNcomment:Closed Caption 字幕复位。CNend
    \attention \n
    reset cc.
    cc模块复位。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*cc_reset)(struct _CAPTION_DEVICE_S* pstDev);

    /**
    \brief Closed Caption get attribution.CNcomment:Closed Caption 获取字幕属性信息 。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[out]  pstCCAttr  cc attribution structure. CNcomment: CC 属性信息结构体。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief Closed Caption set display attribution. CNcomment: Closed Caption 设置字幕显示属性信息。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in]  stCCAttr  cc attribution structure. CNcomment:属性信息结构体。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
    \brief cc get running status.CNcomment:cc 获取当前运行状态 。CNend
    \attention \n
    none.CNcomment: 无。CNend
    \param[out] penStatus cc status.CNcomment:cc 字幕运行状态 。CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误。CNend
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
 \brief direct get caption device api, for linux and android.CNcomment:获取字幕设备的接口, Linux和Android平台都可以使用 CNend
 \attention \n
get caption device api，for linux and andorid.
CNcomment:获取字幕设备接口，linux和android平台都可以使用. CNend
 \retval  caption device pointer when success.CNcomment:成功返回caption设备指针。CNend
 \retval ::NULL when failure.CNcomment:失败返回空指针 CNend
 \see \n
::CAPTION_DEVICE_S

 \par example
 */
CAPTION_DEVICE_S *getCaptionDevice();

/**
\brief Open HAL caption module device.CNcomment: 打开HAL字幕模块设备 。CNend
\attention \n
Open HAL caption module device(for compatible Android HAL).
CNcomment:打开HAL字幕模块设备(为兼容Android HAL结构)。CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[in] ppstDevice caption device structure.CNcomment:字幕设备数据结构 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
\brief  Close HAL caption module device.CNcomment: 关闭HAL字幕模块设备 。CNend
\attention \n
Close HAL caption module device(for compatible Android HAL).
CNcomment:关闭HAL字幕模块设备(为兼容android  HAL结构)。CNend
\param[in] pstDevice caption device structure.CNcomment:字幕设备数据结构 。CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
