#ifndef __HI_GO_TEXT_H__
#define __HI_GO_TEXT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/
/** \addtogroup      HIGO_TEXT */
/** @{ */  /** <!��[HIGO_TEXT] */

#define LAYOUT_LEFT          HIGO_LAYOUT_LEFT     /**<Horizontally left*//**<CNcomment:ˮƽ����*/
#define LAYOUT_RIGHT         HIGO_LAYOUT_RIGHT    /**<Horizontally right*//**<CNcomment:ˮƽ����*/
#define LAYOUT_HCENTER       HIGO_LAYOUT_HCENTER  /**<Horizontally center*//**<CNcomment:ˮƽ����*/
#define LAYOUT_TOP           HIGO_LAYOUT_TOP      /**<Vertically top*//**<CNcomment:��ֱ�Ӷ�*/
#define LAYOUT_BOTTOM        HIGO_LAYOUT_BOTTOM   /**<Vertically bottom*//**<CNcomment:��ֱ�ӵ�*/
#define LAYOUT_VCENTER       HIGO_LAYOUT_VCENTER  /**<Vertically center*//**<CNcomment:��ֱ����*/
#define LAYOUT_WRAP          HIGO_LAYOUT_WRAP     /**<Wrap*//**<CNcomment:�Զ�����*/
#define LAYOUT_WORDELLIPSIS  HIGO_LAYOUT_WORDELLIPSIS /**<Ellipsis format*//**<CNcomment:ʹ��ʡ�Ժŷ��*/
#define LAYOUT_FORCE_LEFT    HIGO_LAYOUT_FORCE_LEFT     /**<Force Horizontally left*//**<CNcomment:ǿ��ˮƽ����*/
#define LAYOUT_FORCE_RIGHT   HIGO_LAYOUT_FORCE_RIGHT    /**<Force Horizontally right*//**<CNcomment:ǿ��ˮƽ����*/

/** */
typedef enum
{
    HIGO_LAYOUT_LEFT             = 0x0001,
    HIGO_LAYOUT_RIGHT            = 0x0002,
    HIGO_LAYOUT_HCENTER          = 0x0004,
    HIGO_LAYOUT_WRAP             = 0x0008,
    HIGO_LAYOUT_WORDELLIPSIS     = 0x0010,
    HIGO_LAYOUT_TOP              = 0x0100,
    HIGO_LAYOUT_BOTTOM           = 0x0200,
    HIGO_LAYOUT_VCENTER          = 0x0400,
    HIGO_LAYOUT_FORCE_LEFT        = 0x8000,
    HIGO_LAYOUT_FORCE_RIGHT      = 0x10000,
    HIGO_LAYOUT_BUTT             = 0x20000,
} HIGO_LAYOUT_E;

/**<Definition of a character set*//** CNcomment: �ַ������� */
typedef enum
{
    HIGO_CHARSET_UNKOWN,
    HIGO_CHARSET_ASCI,
    HIGO_CHARSET_GB2312,
    HIGO_CHARSET_UTF8,
    HIGO_CHARSET_UTF16,
    HIGO_CHARSET_UCS2 = HIGO_CHARSET_UTF16,
    HIGO_CHARSET_UTF32,
    HIGO_CHARSET_BUTT,
} HIGO_CHARSET_E;

/** Definition of a text base direction*//** CNcomment: �ı��������������*/
typedef enum
{
    HIGO_TEXT_DIR_NEUTRAL = 0,/**<neutral deirction*//**<CNcomment:���Է��򣬰����ݲ���ǿ�ַ�����*/
    HIGO_TEXT_DIR_LTR,/**<Left to right*//**<CNcomment:�����ҷ��� */
    HIGO_TEXT_DIR_RTL,/**<Right to left*//**<CNcomment:���ҵ����� */
    HIGO_TEXT_DIR_BUTT
} HIGO_TEXT_DIR_E;


typedef struct
{
    HIGO_CHARSET_E Charset; /**<Character set name*//**<CNcomment:�ַ������� */
    HI_U8 Height;         /**<Font height*//**<CNcomment:����߶� */
    HI_U8 MaxWidth;      /**<Maximum font width*//**<CNcomment:��������� */
}HIGO_FONTATTR_S;

/** Attributes of a text output object*//** CNcomment: �ı������������ */
typedef struct
{
    HI_COLOR        BgColor;     /**<Background color*//**<CNcomment:����ɫ */
    HI_COLOR        FgColor;     /**<Foreground color*/ /**<CNcomment:ǰ��ɫ */
    HIGO_FONTATTR_S SbFontAttr;  /**<Font attributes of the single-byte character set*/ /**<CNcomment:���ֽ��ַ����������� */
    HIGO_FONTATTR_S MbFontAttr;  /**<Font attributes of the multi-byte character set*//**<CNcomment:���ֽ��ַ����������� */
} HIGO_TEXTOUTATTR_S;

/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      HIGO_TEXT */
/** @{ */  /** <!��[HIGO_TEXT] */

/**
\brief Creates a text output object.CNcomment: �����ı�������� CNend
\attention \n
The values of pSbFontFile and pMbFontFile cannot be empty at the same time. If the received file name is in vector
font, the font height is set based on the 22-dot array.
CNcomment: pSbFontFile��pMbFontFile����ͬʱΪ��,����������ʸ�������ļ���,������߶Ȱ�
22���󴴽� CNend
\param[in] pSbFontFile Font file of the single-byte character set. If the value is empty, it indicates that the single
-byte character set library is not used.CNcomment: ���ֽ��ַ��������ļ���Ϊ�ձ�ʾ��ʹ�õ��ֽ��ַ����ֿ� CNend
\param[in] pMbFontFile  Font file of the multi-byte character set. If the value is empty, it indicates that the multi-
byte character set library is not used. Ensure that the font files of the single-byte and multi-byte character sets
cannot be empty concurrently.CNcomment: ���ֽ��ַ��������ļ���Ϊ�ձ�ʾ��ʹ�ö��ֽ��ַ����ֿ⣬���ǲ����뵥�ֽ��ַ��ļ�ͬʱΪ�ա� CNend
\param[out]  pTextOut Handle of a text output object.CNcomment: �ı���������� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVFILE
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM

\see \n
::HI_GO_DestroyText
*/
HI_S32 HI_GO_CreateText(const HI_CHAR* pSbFontFile, const HI_CHAR* pMbFontFile, HI_HANDLE* pTextOut);

/**
\brief Destroys a text output object.CNcomment:�����ı�������� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_CreateText
*/
HI_S32 HI_GO_DestroyText(HI_HANDLE TextOut);

/**
\brief set the input charset. CNcomment:���������ַ��� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[out] CharSet  charset of input text.CNcomment:�����ı��ַ����� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORT_CHARSET

\see \n
::HI_GO_CreateText
*/
HI_S32 HI_GO_SetInputCharSet(HI_HANDLE TextOut, HIGO_CHARSET_E CharSet);

/**
\brief Obtains the attributes of a text output object.CNcomment:��ȡ�ı������������ CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[out] pTextOutAttr  Attributes of a text output object.CNcomment:�ı������������ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_GetTextAttr(HI_HANDLE TextOut,HIGO_TEXTOUTATTR_S *pTextOutAttr);

/**
\brief Obtains the width and height of text contents.CNcomment:��ȡ�ı����ݵĿ�� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[in] pText Text contents.CNcomment:�ı����� CNend
\param[out] pWidth Width of text contents. It cannot be empty.CNcomment:�ı����ݿ�ȣ�����Ϊ�� CNend
\param[out] pHeight Height of text contents. It cannot be empty.CNcomment:�ı����ݸ߶ȣ�����Ϊ�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_UNSUPPORT_CHARSET

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_GetTextExtent(HI_HANDLE TextOut, const HI_CHAR *pText, HI_S32 *pWidth, HI_S32 *pHeight);

/**
\brief Sets to display the background color of a text output object.CNcomment:�����ı��������ı���ɫ�Ƿ���ʾ CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[in] bTransparent  Whether to display the background color of a text output object. If the value is set to
HI_TRUE, the background color is not displayed. The default value is HI_TRUE.CNcomment:�ı�������󱳾�ɫ�Ƿ���ʾ��ΪHI_TRUE, ����ʾ��Ĭ��ΪHI_TRUE CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/ACNcomment:�� CNend
*/
HI_S32 HI_GO_SetTextBGTransparent(HI_HANDLE TextOut, HI_BOOL bTransparent);

/**
\brief Sets the background color of a text output object.CNcomment:�����ı��������ı���ɫ CNend
\attention \n
If the target surface is a palette, the color is the palette index.CNcomment:���Ŀ��surface�ǵ�ɫ�壬��Color�ǵ�ɫ������ CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[in] Color  Background color of a text output object.CNcomment:�ı�������󱳾�ɫ��CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetTextBGColor(HI_HANDLE TextOut, HI_COLOR Color);

/**
\brief Sets the font color of a text output object.CNcomment: �����ı���������������ɫ CNend
\attention \n
If the target surface is a palette, the color is the palette index.CNcomment: ���Ŀ��surface�ǵ�ɫ�壬��Color�ǵ�ɫ������ CNend
\param[in] TextOut Handle of a text output object.CNcomment: �ı���������� CNend
\param[in] Color  Font color of a text output object.CNcomment: �ı��������������ɫ CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment: �� CNend
*/
HI_S32 HI_GO_SetTextColor(HI_HANDLE TextOut, HI_COLOR Color);

/**
\brief Outputs text contents to a specified surface.CNcomment:����ı����ݵ�ָ��surface CNend
\attention
N/A.CNcomment:�� CNend
\param[in] TextOut Handle of a text output object.CNcomment:�ı���������� CNend
\param[in] Surface Surface handle.CNcomment:Surface��� CNend
\param[in] pText  Text contents.CNcomment:�ı����� CNend
\param[in] pRect Text output region. If the value is empty, it indicates that text contents are output from the
surface origin.CNcomment:�ı��������Ϊ�ձ�ʾ��surfaceԭ����� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_TextOut(HI_HANDLE TextOut,HI_HANDLE Surface, const HI_CHAR *pText,
                           const HI_RECT *pRect);

/**
\brief Outputs texts. This API is an extended API. You can call this API to output contents based on customized
styles and formatting.CNcomment:�ı������չ�ӿ�,������ݿ��԰����û�ָ�����Ű���������CNend
\param[in] hTextOut Text output handle.CNcomment:�ı������� CNend
\param[in] hSurface Surface handle.CNcomment:Surface��� CNend
\param[in] pText    Text contents ending with /0.CNcomment:��/0��β���ı����� CNend
\param[in] pRect    Text output region.CNcomment:�ı�������� CNend
\param[in] Style    Styles and formatting including LAYOUT_LEFT, LAYOUT_RIGHT, and LAYOUT_HCENTER.CNcomment:�Ű��ʽ����LAYOUT_LEFT��LAYOUT_RIGHT��LAYOUT_HCENTER�� CNend

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_NULLPTR

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_TextOutEx(HI_HANDLE hTextOut, HI_HANDLE hSurface,
                               const HI_CHAR *pText,  const HI_RECT *pRect,
                               HIGO_LAYOUT_E Style);

/**
\brief Calculates the number of characters in a specified text output region.CNcomment: ����ָ���ı���������ַ����� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] hTextOut Text output handle.CNcomment: �ı������� CNend
\param[in] pText    Text contents ending with /0.CNcomment: ��/0��β���ı����� CNend
\param[in] pRect    Text output region. The value cannot be empty.CNcomment: �ı��������,����Ϊ�� CNend
\param[in] pLen      Pointer to the string length.CNcomment: �ַ�������ָ�� CNend

\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_INVHANDLE
\retval ::HI_SUCCESS

\see \n
N/A.CNcomment: �� CNend
*/
HI_S32 HI_GO_GetTextExtentEx(HI_HANDLE TextOut, const HI_CHAR *pText,
                                       const HI_RECT *pRect, HI_U32 *pLen);

typedef enum
{
    HIGO_TEXT_STYLE_NORMAL = 0x00,/*Normal font*//**<CNcomment:��������*/
    HIGO_TEXT_STYLE_ITALIC = 0x01, /*Italic font*//**<CNcomment:б������*/
    HIGO_TEXT_STYLE_BOLD   = 0x02, /*Bold font*//**<CNcomment:��������*/
    HIGO_TEXT_STYLE_BUTT   = 0x80,
} HIGO_TEXT_STYLE_E;

typedef struct{
    HI_HANDLE     hFont;           		 /* handle of font file                         */
    HI_U32        Style;     		 /* layout style                                */
    HI_S32        s32Width;    		 /* width of display arear                      */
    HI_S32        s32Height;   		 /* height of display arear                     */
    HI_S32  	  horz_dist;         /* �ַ����                                    */
    HI_S32  	  vert_dist;         /* �м��,һ���������ߺ�������������֮��ľ��� */
    HI_BOOL       single_para_flg;   /* �Ƿ�Ϊ������                                */
    HI_BOOL    	  auto_dir;          /* �Ƿ�Ϊ�Զ�����                              */
    HIGO_TEXT_DIR_E base_dir;        /* ��������                                    */
    HI_U32        max_char;          /* ����ַ�����                                */
    HI_COLOR      select_bg;         /* ѡ�еı���ɫ                                */
    HI_COLOR      select_fg;         /* ѡ�еı���ɫ                                */
}HIGO_LAYOUT_INFO_S;

typedef struct
{
    const HI_CHAR* pSbcFontFile;
    const HI_CHAR* pMbcFontFile;
    HI_U32   u32Size; /*This value is ignored for the dot-matrix font.*//**<CNcomment:����ǵ������壬���ֵ������*/
} HIGO_TEXT_INFO_S;

typedef enum{
	HIGO_LAYOUT_MOVECURSOR_UP,    /**< move cursor to left position 			 */
	HIGO_LAYOUT_MOVECURSOR_DOWN,  /**< move cursor to right position 			 */
	HIGO_LAYOUT_MOVECURSOR_PREV,  /**< move cursor to previous postion 			 */
	HIGO_LAYOUT_MOVECURSOR_NEXT,  /**< move cursor to next position 			 */
	HIGO_LAYOUT_MOVECURSOR_LEFT,  /**< move cursor to left position 			 */
	HIGO_LAYOUT_MOVECURSOR_RIGHT, /**< move cursor to right positon 			 */
	HIGO_LAYOUT_MOVECURSOR_SOT,   /**< move cursor to start position of text 	 */
	HIGO_LAYOUT_MOVECURSOR_EOT,   /**< move curosr to end position of text 		 */
	HIGO_LAYOUT_MOVECURSOR_SOL,   /**< move cursor to start of current line		 */
	HIGO_LAYOUT_MOVECURSOR_EOL,   /**< move cursor to end of current line 		 */
	HIGO_LAYOUT_MOVECURSOR_SOP,   /**< move cursor to start of current paragraph */
	HIGO_LAYOUT_MOVECURSOR_EOP,   /**< move cursor to end of current paragraph	 */
	HIGO_LAYOUT_MOVECURSOR_BUTT,
}HIGO_TEXT_CURSOR_DIR_E;


/**
\brief Creates a font.CNcomment:�������� CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] phText Text output handle.CNcomment:�ı������� CNend
\param[in] pInfo  Text information.CNcomment:�ļ���Ϣ CNend

\retval ::HI_SUCCESS A font is created successfully.CNcomment:���崴���ɹ� CNend
\retval ::HI_FAILURE A font fails to be created.CNcomment:���崴��ʧ�� CNend
\retval ::HIGO_ERR_INVPARAM
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_CreateTextEx(const HIGO_TEXT_INFO_S* pInfo, HI_HANDLE* phText);

/**
\brief Sets the style of a font, such as bold, italic, or normal.CNcomment:��������ķ�񣬱���:���壬б�壬������ CNend
\attention \n
N/A.CNcomment:�� CNend
\param[in] hTextOut Text output handle.CNcomment:�ı������� CNend
\param[in] eStyle   Font style.CNcomment:������ CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetTextStyle(HI_HANDLE hTextOut, HIGO_TEXT_STYLE_E eStyle);



/**
\brief Sets the the text base direction
lines.CNcomment:�����ı��������Ļ������� CNend
\attention \n
N/A.CNcomment:�� CNend

\param[in] hTextOut Text output handle. CNcomment:�ı������� CNend
\param[in] BaseDir the base direction of the text. CNcomment: �ı��������������� CNend

\retval ::HI_SUCCESS Success.CNcomment: �ɹ� CNend
\retval ::HIGO_ERR_INVHANDLE Failure.CNcomment:ʧ�� CNend

\see \n
N/A.CNcomment:�� CNend
*/

HI_S32 HI_GO_SetBaseDir(HI_HANDLE TextOut, HIGO_TEXT_DIR_E eBaseDir);
/**
\brief Sets the horizontal spacing between displayed characters, that is, the horizontal spacing between character
lines.CNcomment:�����ַ���ʾˮƽ��࣬�����ַ���ˮƽ��� CNend
\attention \n
N/A.CNcomment:�� CNend

\param[in] hTextOut Text output handle.CNcomment:�ı������� CNend
\param[in] u32Distance Horizontal spacing.CNcomment:ˮƽ��� CNend

\retval ::HI_SUCCESS Success.CNcomment: �ɹ� CNend
\retval ::HIGO_ERR_INVHANDLE Failure.CNcomment:ʧ�� CNend

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetCharExtra(HI_HANDLE hTextOut, HI_U32 u32Distance);

/**
\brief Sets the vertical and horizontal spacing.CNcomment:���ô�ֱˮƽ��� CNend
\attention \n
This API is available only when the font style is changed.CNcomment:ֻ�л��з�����Ч CNend

\param[in] hTextOut Text output handle.CNcomment:�ı������� CNend
\param[in] u32Distance Vertical spacing.CNcomment:��ֱ��� CNend

\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HIGO_ERR_INVHANDLE Failure.CNcomment:ʧ�� CNend

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_SetLineExtra(HI_HANDLE hText, HI_U32 u32Distance);

/**
\brief Initializes the character module.CNcomment: ��ʼ���ַ�ģ�� CNend
\attention \n
N/A.CNcomment: �� CNend
\param N/A.CNcomment: �� CNend
\retval ::HI_SUCCESS Success.CNcomment: �ɹ� CNend
\retval ::HI_FAILURE Failure.CNcomment: ʧ�� CNend
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
N/A.CNcomment: �� CNend
*/
HI_S32 HI_GO_InitText();

/**
\brief Deinitializes the character module.CNcomment:ȥ��ʼ���ַ�ģ�� CNend
\attention \n
N/A.CNcomment:�� CNend
\param N/A.CNcomment:�� CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::HIGO_ERR_NOTINIT Failure.CNcomment:ʧ�� CNend

\see \n
N/A.CNcomment:�� CNend
*/
HI_S32 HI_GO_DeinitText();


/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif /* __HI_GO_TEXT_H__ */
