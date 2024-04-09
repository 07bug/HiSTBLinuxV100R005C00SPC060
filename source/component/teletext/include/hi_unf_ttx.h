/******************************************************************************

*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*

******************************************************************************
  File Name     : hi_unf_ttx.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011/10/20
  Description   : Teletext UNF header file
  History       :
  1.Date        : 2011/10/20
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __HI_UNF_TTX_H__
#define __HI_UNF_TTX_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif  /* End of #ifdef __cplusplus */

/********************************Structure Definition********************************/
/** \addtogroup      Teletext */
/** @{ */  /** <!-- [Teletext] */

/** Teletext max line in page *//** CNcomment:teletextҳ��������� */
#define HI_UNF_TTX_MAX_LINES (32)
/** Teletext line size */ /** CNcomment:teletext�еĳ��� */
#define HI_UNF_TTX_LINE_SIZE (46)

/** Teletext key support list *//** CNcomment:Ĭ��֧�ֵĽ�����ʽ */
typedef enum hiUNF_TTX_KEY_E
{
    HI_UNF_TTX_KEY_0,
    HI_UNF_TTX_KEY_1,
    HI_UNF_TTX_KEY_2,
    HI_UNF_TTX_KEY_3,
    HI_UNF_TTX_KEY_4,
    HI_UNF_TTX_KEY_5,
    HI_UNF_TTX_KEY_6,
    HI_UNF_TTX_KEY_7,
    HI_UNF_TTX_KEY_8,
    HI_UNF_TTX_KEY_9, /**<Three number key to open a specified page *//**<CNcomment:�������ּ���ָ��ҳ */
    HI_UNF_TTX_KEY_PREVIOUS_PAGE, /**<Previous page *//**<CNcomment:��һҳ */
    HI_UNF_TTX_KEY_NEXT_PAGE, /**<Next page *//**<CNcomment:��һҳ */
    HI_UNF_TTX_KEY_PREVIOUS_SUBPAGE, /**<Previous subpage *//**<CNcomment:��һ ��ҳ */
    HI_UNF_TTX_KEY_NEXT_SUBPAGE, /**<Next subpage *//**<CNcomment:��һ ��ҳ */
    HI_UNF_TTX_KEY_PREVIOUS_MAGAZINE, /**<Previous magazine *//**<CNcomment:��һ��־ */
    HI_UNF_TTX_KEY_NEXT_MAGAZINE, /**<Next magazine *//**<CNcomment:��һ��־ */
    HI_UNF_TTX_KEY_RED,    /**<First link in packet X/27, if inexistence, Show first valid page*//**<CNcomment:X/27 ���еĵ�һ�����ӣ���X/27����ʾ�����Чҳ */
    HI_UNF_TTX_KEY_GREEN,  /**<Second  link in packet X/27, if inexistence, Show second valid page*//**<CNcomment:X/27 ���еĵڶ������ӣ���X/27����ʾ�ڶ���Чҳ */
    HI_UNF_TTX_KEY_YELLOW, /**<Third  link in packet X/27, if inexistence, Show third valid page*//**<CNcomment:X/27 ���еĵ��������ӣ���X/27����ʾ������Чҳ */
    HI_UNF_TTX_KEY_CYAN,   /**<Fourth  link in packet X/27, if inexistence, Show fourth valid page. you can replace it with blue key if no cyan key on the user's control unit*/
                           /**<CNcomment:X/27 ���еĵ��ĸ����ӣ���X/27����ʾ������Чҳ�����ң������û��CYAN�����������BLUE���������*/
    HI_UNF_TTX_KEY_INDEX,  /**<Sixth  link in packet X/27, if inexistence, Show index  page*//**<CNcomment:X/27 ���еĵ��������ӣ���X/27��ָ����ʼҳ */
    HI_UNF_TTX_KEY_REVEAL, /**<Reveal or hide concealed  information *//**<CNcomment:��ʾ/����conceal ��Ϣ */
    HI_UNF_TTX_KEY_HOLD,   /**<Switch between hold and resume ttx play  *//**<CNcomment:��ͣͼ�Ĳ���/�ָ�ͼ�Ĳ����л� */
    HI_UNF_TTX_KEY_MIX,    /**<Switch  between  transparent and nontransparent  background *//**<CNcomment:Teletext����͸��/��͸���л� */
    HI_UNF_TTX_KEY_UPDATE, /**<Update current page*//**<CNcomment:���µ�ǰҳ */
    HI_UNF_TTX_KEY_ZOOM,   /**<Send this cmd sevral times to display the upper,then the lower part of the screen and then return to the normal size teletext page*/
                           /**<CNcomment:ͨ���������ʹ�����������ʾteletextҳ����ϰ벿�֡��°벿�֡�ȫ�� */
    HI_UNF_TTX_KEY_SUBPAGE,/**<switch from page num ipunt mode to subpage input mode*//**<CNcomment:����ҳ������ģʽת��subpage����ģʽ */
    HI_UNF_TTX_KEY_CANCEL, /**<Hide or display current page except page number, currently not support*//**<CNcomment:���ػ�����ʾ����ҳ����ĵ�ǰҳ���� ,��ǰ�ݲ�֧��*/
    HI_UNF_TTX_KEY_TIME,   /**<Hide or display current time*//**<CNcomment:���ػ�����ʾ��ǰʱ��*/
    HI_UNF_TTX_KEY_BUTT    /**<Invalid key*//**<CNcomment:��Ч�İ��� */
} HI_UNF_TTX_KEY_E;

/** Teletext output type *//** CNcomment:Teletext��������� */
typedef enum hiUNF_TTX_OUTPUT_E
{
    HI_UNF_TTX_VBI_OUTPUT,  /**<Only VBI output *//**<CNcomment:VBI ��� */
    HI_UNF_TTX_OSD_OUTPUT,  /**<Only OSD output *//**<CNcomment:OSD ��� */
    HI_UNF_TTX_DUAL_OUTPUT, /**<VBI OSD dual output *//**<CNcomment:VBI��OSDͬʱ��� */
    HI_UNF_TTX_BUTT         /**<Invalid output type *//**<CNcomment:��Ч������� */
} HI_UNF_TTX_OUTPUT_E;

/** Teletext type *//** CNcomment:Teletext������ */
typedef enum hiUNF_TTX_TYPE_E
{
    HI_UNF_TTX_INITTTX = 1, /**<Initial Teletext page *//**<CNcomment:Teletext ͼ�� */
    HI_UNF_TTX_TTXSUBT = 2, /**<Teletext subtitle page *//**<CNcomment:Teletext ��Ļ */
    HI_UNF_TTX_ADDINFO = 3, /**<Nonsupport for the moment <Additional information page *//**<CNcomment:�ݲ�֧�ָ�����Ϣҳ */
    HI_UNF_TTX_PROGSCD = 4, /**<Nonsupport for the moment <Programme schedule page *//**<CNcomment:�ݲ�֧�ֽ�Ŀָ��ҳ */
    HI_UNF_TTX_TTXSUBT_HIP = 5, /**<Nonsupport for the moment <Teletext subtitle page for hearing impaired people *//**<CNcomment:�ݲ�֧��Ϊ�������ϰ��������õ�Teletext��Ļҳ */
    HI_UNF_TTX_TTXSUBT_BUTT /**<Invalid teletext type *//**<CNcomment:��Ч��teletext ���� */
} HI_UNF_TTX_TYPE_E;

/** Teletext page type *//** CNcomment:Teletextҳ������ */
typedef enum hiUNF_TTX_PAGE_TYPE_E
{
    HI_UNF_TTX_PAGE_CUR,   /**<Current reveal page *//**<CNcomment:��ǰ��ʾҳ */
    HI_UNF_TTX_PAGE_INDEX, /**<Initial Teletext page , if  packet X/30 exist, return index page in X/30, otherwise return default index page 100*/
                           /**<CNcomment:��ʼҳ�������X/30��������X/30��ָ����ʼҳ�����򷵻�Ĭ����ҳ100 */
    HI_UNF_TTX_PAGE_LINK1, /**<First link  in packet  X/27, if  inexistence, return first valid page*//**<CNcomment:X/27���е�1�����ӣ����û�У����ص�ǰҳ�����Чҳ */
    HI_UNF_TTX_PAGE_LINK2, /**<Second link  in packet  X/27, if inexistence, return second valid page*//**<CNcomment:X/27���е�2�����ӣ����û�У����ص�ǰҳ�ڶ���Чҳ */
    HI_UNF_TTX_PAGE_LINK3, /**<Third link  in packet  X/27, if  inexistence, return third valid page*//**<CNcomment:X/27���е�3�����ӣ����û�У����ص�ǰҳ������Чҳ */
    HI_UNF_TTX_PAGE_LINK4, /**<Fourth  link  in packet  X/27, if  inexistence, return fourth valid page*//**<CNcomment:X/27���е�4�����ӣ����û�У����ص�ǰҳ������Чҳ */
    HI_UNF_TTX_PAGE_LINK5, /**<Fifth link  in packet  X/27, if inexistence, return fifth valid page*//**<CNcomment:X/27���е�5�����ӣ����û�У�����0ff:3f7f */
    HI_UNF_TTX_PAGE_LINK6, /**<Sixth link  in packet  X/27, if inexistence, return Sixth valid page*//**<CNcomment:X/27���е�6�����ӣ����û�У�����0ff:3f7f */
    HI_UNF_TTX_PAGE_BUTT   /**<Invalid  page type *//**<CNcomment:��Чҳ���� */
} HI_UNF_TTX_PAGE_TYPE_E;

/** Teletext user command type *//** CNcomment:Teletext�������� */
typedef enum hiUNF_TTX_CMD_E
{
    HI_UNF_TTX_CMD_KEY,          /**<(HI_UNF_TTX_KEY_E *)Default alternation type, key *//**<CNcomment:������Ĭ�ϵĽ�����ʽ */
    HI_UNF_TTX_CMD_OPENPAGE,     /**<(HI_UNF_TTX_PAGE_ADDR_S *) Open specified page*//**<CNcomment:(HI_UNF_TTX_PAGE_ADDR_S *)��ָ��ҳ */
    HI_UNF_TTX_CMD_GETPAGEADDR,  /**<(HI_UNF_TTX_GETPAGEADDR_S *)Get current page , index page and  link page  address*//**<CNcomment:(HI_UNF_TTX_GETPAGEADDR_S *) ��ȡ��ǰ����ҳ������ҳ��ַ */
    HI_UNF_TTX_CMD_CHECKPAGE,    /**<(HI_UNF_TTX_CHECK_PARAM_S *) Check the specified page be received or not*//**<CNcomment:(HI_UNF_TTX_CHECK_PARAM_S *) ����Ƿ��յ�������ָ����ҳ */
    HI_UNF_TTX_CMD_SETREQUEST,   /**<(HI_UNF_TTX_REQUEST_RAWDATA_S *) Sets up a request for teletext raw data*//**<CNcomment:(HI_UNF_TTX_REQUEST_RAWDATA_S *) �����ȡteletext�е�ԭʼ���� */
    HI_UNF_TTX_CMD_CLEARREQUEST, /**<(HI_UNF_TTX_REQUEST_RAWDATA_S *) Clears a request set up by the HI_UNF_TTX_CMD_SETREQUEST*//**<CNcomment:(HI_UNF_TTX_REQUEST_RAWDATA_S *) �ͷ���HI_UNF_TTX_CMD_SETREQUEST�������������� */
    HI_UNF_TTX_CMD_BUTT          /**<Invalid command type *//**<CNcomment:��Ч�������� */
} HI_UNF_TTX_CMD_E;

/** G0 char set *//** CNcomment:G0�ַ��� */
typedef  enum   hiUNF_TTX_G0SET_E
{
    HI_UNF_TTX_G0SET_LATIN,      /**<LATIN G0 Primary Set  *//**<CNcomment:LATIN G0���ַ��� */
    HI_UNF_TTX_G0SET_CYRILLIC_1, /**<CYRILLIC_1 G0 Primary Set *//**<CNcomment:CYRILLIC_1  G0���ַ��� */
    HI_UNF_TTX_G0SET_CYRILLIC_2, /**<CYRILLIC_2 G0 Primary Set*//**<CNcomment:CYRILLIC_2 G0���ַ��� */
    HI_UNF_TTX_G0SET_CYRILLIC_3, /**<CYRILLIC_3 G0 Primary Set*//**<CNcomment:CYRILLIC_3 G0���ַ��� */
    HI_UNF_TTX_G0SET_GREEK,      /**<GREEK G0 Primary Set*//**<CNcomment:GREEK G0���ַ��� */
    HI_UNF_TTX_G0SET_HEBREW,     /**<HEBREW G0 Primary Set*//**<CNcomment:HEBREW  G0���ַ��� */
    HI_UNF_TTX_G0SET_ARABIC,     /**<ARABIC G0 Primary Set*//**<CNcomment:ARABIC G0���ַ��� */
    HI_UNF_TTX_G0SET_BUTT        /**<Invalid G0 Primary Set *//**<CNcomment:��ЧG0���ַ��� */
} HI_UNF_TTX_G0SET_E;

/** G2 char set *//** CNcomment:G2�ַ��� */
typedef enum hiUNF_TTX_G2SET_E
{
    HI_UNF_TTX_G2SET_LATIN,    /**<LATIN G2 Set *//**<CNcomment:LATIN G2�ַ��� */
    HI_UNF_TTX_G2SET_CYRILLIC, /**<CYRILLIC G2 Set *//**<CNcomment:CYRILLIC G2�ַ��� */
    HI_UNF_TTX_G2SET_GREEK,    /**<GREEK G2 Set *//**<CNcomment:GREEK G2�ַ��� */
    HI_UNF_TTX_G2SET_ARABIC,   /**<ARABIC G2 Set *//**<CNcomment:ARABIC G2�ַ��� */
    HI_UNF_TTX_G2SET_BUTT      /**<Invalid G2 Set *//**<CNcomment:��ЧG2�ַ��� */
}HI_UNF_TTX_G2SET_E;

/** Latin G0 National Option Sub-sets *//** CNcomment:Latin G0�����ַ��Ӽ� */
typedef enum hiUNF_TTX_NATION_SET_E
{
    HI_UNF_TTX_NATION_SET_PRIMARY,      /**<Latin G0 Primary nation sub set*//**<CNcomment:LATIN�������Ӽ�*/
    HI_UNF_TTX_NATION_SET_CZECH,        /**<Latin czech slovak nation sub set*//**<CNcomment:LATIN czech/slovak�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_ENGLISH,      /**<Latin english nation sub set*//**<CNcomment:LATIN english�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_ESTONIAN,     /**<Latin estonian nation sub set*//**<CNcomment:LATIN estonian�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_FRENCH,       /**<Latin french nation sub set*//**<CNcomment:LATIN french�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_GERMAN,       /**<Latin german nation sub set*//**<CNcomment:LATIN german�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_ITALIAN,      /**<Latin italish nation sub set*//**<CNcomment:LATIN italish�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_LETTISH,      /**<Latin lettish lithuanian nation sub set*//**<CNcomment:LATIN lithuanian�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_POLISH,       /**<Latin polish nation sub set*//**<CNcomment:LATIN polish�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_PORTUGUESE,   /**<Latin portutuese spanish nation sub set*//**<CNcomment:LATIN portutuese/spanish�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_RUMANIAN,     /**<Latin rumanian nation sub set*//**<CNcomment:LATIN rumanian�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_SERBIAN,      /**<Latin serbian croatian slovenian nation sub set*//**<CNcomment:LATIN serbian/croatian/slovenian�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_SWEDISH,      /**<Latin swedish finnish nation sub set*//**<CNcomment:LATIN finnish�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_TURKISH,      /**<Latin turkish nation sub set*//**<CNcomment:LATIN turkish�����Ӽ�*/
    HI_UNF_TTX_NATION_SET_BUTT          /**<Invalid nation sub Set *//**<CNcomment:��Ч�����ַ��Ӽ�*/

}HI_UNF_TTX_NATION_SET_E;

/** Teletext char set *//** CNcomment:Teletext�ַ��� */
typedef  enum   hiUNF_TTX_CHARSET_E
{
    HI_UNF_TTX_CHARSET_G0,  /**<G0  character set *//**<CNcomment:G0 �ַ��� */
    HI_UNF_TTX_CHARSET_G1,  /**<G1  character set*//**<CNcomment:G1 �ַ��� */
    HI_UNF_TTX_CHARSET_G2,  /**<G2  character set *//**<CNcomment:G2 �ַ��� */
    HI_UNF_TTX_CHARSET_G3,  /**<G3  character set *//**<CNcomment:G3 �ַ��� */
    HI_UNF_TTX_CHARSET_BUTT /**<Invalid  character set *//**<CNcomment:��Ч�ַ��� */
} HI_UNF_TTX_CHARSET_E;

/** DRCS character size *//** CNcomment:DRCS�ַ���С */
typedef enum hiUNF_TTX_DRCS_SIZE_E
{
    HI_UNF_TTX_DRCS_SIZE_NORMAL = 0,  /**<char size is 12*10*//**<CNcomment:�ַ���С12*10*/
    HI_UNF_TTX_DRCS_SIZE_SMALL = 1,   /**<char size is 6*5*//**<CNcomment:�ַ���С6*5*/
    HI_UNF_TTX_DRCS_SIZE_BUTT         /**<Invalid char size*//**<CNcomment:��Ч�ַ���С*/
}HI_UNF_TTX_DRCS_SIZE_E;

typedef HI_U32 HI_UNF_TTX_COLOR;

/** Teletext page info *//** CNcomment:Teletextҳ������Ϣ */
typedef struct hiUNF_TTX_PAGEAREA_S
{
    HI_U32 u32Row         : 8; /**<The origination  row  number of the area  *//**<CNcomment:������ʼ�к� */
    HI_U32 u32Column      : 8; /**<The origination  column  number of the area *//**<CNcomment:������ʼ�к� */
    HI_U32 u32RowCount    : 8; /**<The count of row the area covers *//**<CNcomment:���򸲸ǵ����� */
    HI_U32 u32ColumnCount : 8; /**<The count of column  the area covers *//**<CNcomment:���򸲸ǵ����� */
} HI_UNF_TTX_PAGEAREA_S;

/** Teletext char attribute *//** CNcomment:Teletext�ַ����� */
typedef  struct  hiUNF_TTX_CHARATTR_S
{
    HI_U32               u32Index    : 8; /**<Index of a char in a character set *//**<CNcomment:�ַ����ַ����е����� */
    HI_BOOL              bContiguous : 1; /**<Contiguous mosaic char or not *//**<CNcomment:�Ƿ�Ϊ���������˱�־ */
    HI_UNF_TTX_G0SET_E   enG0Set     : 3; /**<G0 Primary Set  , latin , arabic .... *//**<CNcomment:G0���ַ��� */
    HI_UNF_TTX_G2SET_E   enG2Set     : 3;  /**<G2 set ,latin, cyrillic, greek, arabic*//**<CNcomment:G2���ַ���*/
    HI_UNF_TTX_CHARSET_E enCharSet   : 3; /**<Character set  , G0 ,  G1  ....*//**<CNcomment:�ַ��� */
    HI_U32               u8NationSet : 6; /**<Latin National  subset,  English ,French,  German .... *//**<CNcomment:�����ַ��Ӽ� */
    HI_U32               u8Reserved  : 8; /**<Reserved *//**<CNcomment:Ԥ�� */
} HI_UNF_TTX_CHARATTR_S;

/** The info of draw char *//** CNcomment:�����ַ�����Ϣ */
typedef struct hiUNF_TTX_DRAWCAHR_S
{
    HI_UNF_TTX_CHARATTR_S  * pstCharAttr;   /**<Character attribution, it can decide the position of a char in  a  font */
                                            /**<CNcomment:�ַ����ԣ�������һ���ַ����ض��ֿ��е�λ�� */
    HI_UNF_TTX_PAGEAREA_S * pstPageArea;    /**<Area of character in page *//**<CNcomment:�ַ���ҳ���ϵ�λ�� */
    HI_UNF_TTX_COLOR        u32Foreground;  /**<Foreground color *//**<CNcomment:ǰ��ɫ */
    HI_UNF_TTX_COLOR        u32Background;  /**<Background color *//**<CNcomment:����ɫ */
} HI_UNF_TTX_DRAWCAHR_S;

/** The info of draw DRCS character *//** CNcomment:����DRCS�ַ�����Ϣ */
typedef struct hiUNF_TTX_DRAWDRCSCHAR_S
{
    HI_UNF_TTX_PAGEAREA_S  *pstPageArea;      /**<Area of character in page *//**<CNcomment:�ַ���ҳ���ϵ�λ�� */
    HI_UNF_TTX_COLOR       u32Background;     /**<Background color *//**<CNcomment:����ɫ */
    HI_UNF_TTX_COLOR*      pu32DRCSColorInfo; /**<color info of DRCS char,which define the color value of  every pixel in a DRCS char*/
                                              /**<CNcomment:DRCS�ַ���ɫ��Ϣ��ָ����DRCS�ַ�ÿ�����ص���ɫֵ*/
    HI_UNF_TTX_DRCS_SIZE_E enDRCSSize;        /**<size of DRCS char,normal is 12*10,and small is 6*5*//**<CNcomment:DRCS�ַ���С��������12*10,С�ַ���6*5 */
}HI_UNF_TTX_DRAWDRCSCHAR_S;


/** The filled area *//** CNcomment:������� */
typedef struct hiUNF_TTX_FILLRECT_S
{
    HI_UNF_TTX_PAGEAREA_S * pstPageArea; /**<Destination rectangle  *//**<CNcomment:Ŀ�ľ��� */
    HI_UNF_TTX_COLOR        u32Color;    /**<Color *//**<CNcomment:��ɫֵ */
} HI_UNF_TTX_FILLRECT_S;

/** Refreshed layer *//** CNcomment:ˢ��ͼ�� */
typedef struct hiUNF_TTX_REFRESHLAYER_S
{
    HI_UNF_TTX_PAGEAREA_S * pstPageArea; /**<Destination rectangle  *//**<CNcomment:(HI_UNF_TTX_BUFFER_PARAM_S *) �������� */
} HI_UNF_TTX_REFRESHLAYER_S;

/** Teletext Buffer info *//** CNcomment:Teletext������Ϣ */
typedef struct hiUNF_TTX_BUFFER_PARAM_S
{
    HI_U32 u32Row     : 8; /**<The row number of buffer page*//**<CNcomment:����ҳ������� */
    HI_U32 u32Column  : 8; /**<The column  number of buffer page*//**<CNcomment:����ҳ������� */
    HI_U32 u8Reserved : 16;/**<Reserved *//**<CNcomment:Ԥ�� */
} HI_UNF_TTX_BUFFER_PARAM_S;

/** The set of callback cmd *//** CNcomment:�ص������ */
typedef enum hiUNF_TTX_CB_E
{
    HI_UNF_TTX_CB_TTX_TO_APP_MSG, /**<Send message to GUI pthread *//**<CNcomment:���ͻ�����Ϣ��GUI�߳� */
    HI_UNF_TTX_CB_APP_FILLRECT,   /**<(HI_UNF_TTX_FILLRECT_S *) Fill rectangle *//**<CNcomment:(HI_UNF_TTX_FILLRECT_S *)������� */
    HI_UNF_TTX_CB_APP_DRAWCHAR,   /**<(HI_UNF_TTX_DRAWCAHR_S*)Select a char from a specified font and draw it  in specified rectangle of OSD by specified foreground and background */
                                  /**<CNcomment:(HI_UNF_TTX_DRAWCAHR_S*) ���ƺ�������ָ���ַ���ָ����ǰ������ɫ��ʾ��OSD��ָ������ */
    HI_UNF_TTX_CB_APP_DRAWDRCSCHAR,/**<(HI_UNF_TTX_DRAWDRCSCHAR_S*)draw a DRCS char which specified by the color of every pixel*//**<CNcomment:����DRCS�ַ����ַ���ÿ�����ص���ɫֵȷ��*/
    HI_UNF_TTX_CB_APP_REFRESH,    /**<(HI_UNF_TTX_REFRESHLAYER_S*) Refresh layer *//**<CNcomment:(HI_UNF_TTX_REFRESHLAYER_S*) ͼ��ˢ�º��� */
    HI_UNF_TTX_CB_CREATE_BUFF,    /**<(HI_UNF_TTX_BUFFER_PARAM_S *) Create buffer *//**<CNcomment:(HI_UNF_TTX_BUFFER_PARAM_S *) �������� */
    HI_UNF_TTX_CB_DESTROY_BUFF,   /**<Destroy buffer *//**<CNcomment:���ٻ��� */
    HI_UNF_TTX_CB_GETPTS,         /**<(HI_S64 *) Get the PTS of the stream *//**<CNcomment:(HI_S64 *) ��ȡ��ǰ����������PTS */
    HI_UNF_TTX_CB_BUTT            /**<Invalid callback type*//**<CNcomment:��Ч�ص����� */
} HI_UNF_TTX_CB_E;

typedef enum hiUNF_TTX_PACKET_TYPE_E
{
    HI_UNF_TTX_PACKET_TYPE_PES,  /**<ETSI EN DVB 300472 teletext syntax data packets, including PES header information*//**<CNcomment:ETSI EN 300472 DVB teletext�﷨���ݰ�,����PESͷ����Ϣ*/
    HI_UNF_TTX_PACKET_TYPE_RAW,   /**<ETSI EN DVB 300706 teletext syntax data packets, not including PES header information*//**<CNcomment:ETSI EN 300706 DVB teletext�﷨���ݰ�,������PESͷ����Ϣ*/
    HI_UNF_TTX_PACKET_TYPE_BUTT,
}HI_UNF_TTX_PACKET_TYPE_E;

/** Callback function *//** CNcomment:�ص����� */
typedef HI_S32 (*HI_UNF_TTX_CB_FN)(HI_HANDLE hTTX, HI_UNF_TTX_CB_E enCB, HI_VOID *pvCBParam);


typedef enum hiUNF_TTX_LEVEL_E
{
    HI_UNF_TTX_LEVEL_1_5 = 0, /**<TTX Level 1.5 *//**<CNcomment:TTX 1.5 ���� */
    HI_UNF_TTX_LEVEL_2_5 = 1, /**<TTX Level 2.5*//**<CNcomment:TTX 2.5 ���� */
    HI_UNF_TTX_LEVEL_3_5 = 2, /**<TTX Level 3.5*//**<CNcomment:TTX 3.5 ���� */
    HI_UNF_TTX_LEVEL_BUTT     /**<Invalid TTX Level*//**<CNcomment:TTX ��Ч���� */
}HI_UNF_TTX_LEVEL_E;

/** Teletext Init param *//** CNcomment:Teletext��ʼ������ */
typedef struct hiUNF_TTX_INIT_PARA_S
{
    HI_U8 *pu8MemAddr;       /**<The address of memory, If  0, malloc the memory in the module, Otherwise malloced outside the module */
                             /**<CNcomment:���ݷ������ʼ��ַ�����Ϊ0���ڲ����� ���������ⲿ�����ڴ� */
    HI_U32 u32MemSize;       /**<The size of memory,  If  0, the size decided in the module, Otherwise decided outside the module */
                             /**<CNcomment:���ݷ���Ĵ�С�����Ϊ0 �����ڲ������������С���ⲿ���� */

    HI_UNF_TTX_LEVEL_E  enTtxLevel; /**<TTX level*//**<CNcomment:TTX ���� */

    HI_UNF_TTX_CB_FN pfnCB;  /**<Callback function *//**<CNcomment:�ص����� */
    HI_BOOL          bFlash; /**<Permit flash or not *//**<CNcomment:�Ƿ�����˸���� */
    HI_BOOL          bNavigation; /**<Permit navigation bar *//**<CNcomment:�Ƿ��ṩ������ */
} HI_UNF_TTX_INIT_PARA_S;

/** Teletext page address *//** CNcomment:Teletextҳ���� */
typedef struct hiUNF_TTX_PAGE_ADDR_S
{
    HI_U8  u8MagazineNum;  /**<Magazine number *//**<CNcomment:��־�� */
    HI_U8  u8PageNum;      /**<Page number *//**<CNcomment:ҳ�� */
    HI_U16 u16PageSubCode; /**<Page sub-code *//**<CNcomment:��ҳ�� */
} HI_UNF_TTX_PAGE_ADDR_S;

/** Teletext content param *//** CNcomment:Teletext���ݲ��� */
typedef struct hiUNF_TTX_CONTENT_PARA_S
{
    HI_UNF_TTX_TYPE_E      enType; /**<Teletext content type *//**<CNcomment:Teletext�������� */
    HI_U32                         u32ISO639LanCode;/**<teletext iso639  language code*//**<CNcomment:Teletext  iso639����*/
    HI_UNF_TTX_PAGE_ADDR_S stInitPgAddr; /**<Init page address, if Magazine number or Page number be equal to 0xFF,set to 100th page.sub-page numbet default  0*/
                                         /**<CNcomment:��ʼҳ��ַ�������־�Ż�ҳ��Ϊ0xff��������Ϊ��100ҳ����ҳ��Ĭ��Ϊ0 */
} HI_UNF_TTX_CONTENT_PARA_S;

/** Teletext checked param *//** CNcomment:Teletext������ */
typedef struct hiUNF_TTX_CHECK_PARAM_S
{
    HI_UNF_TTX_PAGE_ADDR_S stPageAddr; /**<page address*//**<CNcomment:ҳ��ַ  */
    HI_BOOL                bSucceed;   /**<success or failure*//**<CNcomment:�Ƿ�ɹ� */
} HI_UNF_TTX_CHECK_PARAM_S;

/** Get page address*//** CNcomment:��ȡTeletextҳ */
typedef struct hiUNF_TTX_GETPAGEADDR_S
{
    HI_UNF_TTX_PAGE_TYPE_E enPageType; /**<page type *//**<CNcomment:ҳ���� */
    HI_UNF_TTX_PAGE_ADDR_S stPageAddr; /**<page address *//**<CNcomment:ҳ��ַ*/
} HI_UNF_TTX_GETPAGEADDR_S;

/** Teletext raw data*//** CNcomment:ttxԭʼ���� */
typedef struct hiUNF_TTX_RAWDATA_S
{
    HI_U32 u32ValidLines; /**<bit-field lines  0..31 *//**<CNcomment:��Чλ��ʶ */
    HI_U8  au8Lines[HI_UNF_TTX_MAX_LINES][HI_UNF_TTX_LINE_SIZE]; /**<line data *//**<CNcomment:ttx������ */
} HI_UNF_TTX_RAWDATA_S;

/** Callback function in which notified raw data to consumer *//** CNcomment:���ڻش�ttxԭʼ���ݵĻص����� */
typedef HI_S32 (*HI_UNF_TTX_REQUEST_CALLBACK_FN)(HI_UNF_TTX_RAWDATA_S *pstRawData);

/** Request teletext raw data*//** CNcomment:����ttxԭʼ���� */
typedef struct hiUNF_TTX_REQUEST_RAWDATA_S
{
    HI_UNF_TTX_RAWDATA_S *pstRawData;  /**<raw data address*//**<CNcomment:ԭʼ���ݵ�ַ */
    HI_UNF_TTX_REQUEST_CALLBACK_FN pfnRequestCallback; /**<Callback function *//**<CNcomment:�ص����� */
} HI_UNF_TTX_REQUEST_RAWDATA_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/********************************API declaration********************************/
/** \addtogroup      Teletext  */
/** @{ */  /** <!-- [Teletext] */

/**
\brief     Initializes  TTX  module. CNcomment:��ʼ��TTXģ�顣CNend
\attention \n
none.
\retval ::HI_SUCCESS     success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE     failure. CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_Init(HI_VOID);

/**
\brief  Deinitializes TTX module. CNcomment:ȥ��ʼ��TTXģ�顣CNend
\attention \n
none.
\retval ::HI_SUCCESS     success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE     failure. CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_DeInit(HI_VOID);

/**
\brief  Create a TTX instance, just support for a single  instance for the moment.  CNcomment:����TTXʵ����Ŀǰֻ֧�ֵ�ʵ����CNend
\attention \n
After creating a instance  successfully, the instance  default  to be enable , decode and be
prepared to display teletext. Call  correspond interface to display teletext.
CNcomment:�����ɹ������ʵ��Ĭ��enable��������׼����ʾteletext���ݡ�������Ӧ��������ƽӿں������CNend
\param[in]  pstInitParam  Initialized  parameter. CNcomment:��ʼ��������CNend
\param[out] phTTX         Teletext instance. CNcomment:Teletext�����CNend
\retval ::HI_SUCCESS      success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE      failure.  CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_Create(HI_UNF_TTX_INIT_PARA_S* pstInitParam, HI_HANDLE* phTTX);

/**
\brief    Destory  a  teletext instance.  CNcomment:����TTXʵ����CNend
\attention \n
none.
\param[in] hTTX        Teletext instance. CNcomment:Teletext�����CNend
\retval ::HI_SUCCESS   success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE   failure.  CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_Destroy(HI_HANDLE hTTX);

/**
\brief   Inject the teletext PES data . CNcomment:ע��Teletext PES ���ݡ�CNend
\attention \n
none.
\param[in] hTTX    Teletext instance. CNcomment:Teletext�����CNend
\param[in] pu8Data   Address of data. CNcomment:���ݵ�ַ��CNend
\param[in] u32DataSize  the length of data. CNcomment:���ݳ��ȡ�CNend
\retval ::HI_SUCCESS    success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE    failure.  CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_InjectData(HI_HANDLE hTTX, HI_U8 *pu8Data, HI_U32 u32DataSize);

/**
\brief   Reset data. CNcomment:����յ������ݡ�CNend
\attention \n
none.
\param[in] hTTX   Teletext instance. CNcomment:Teletext�����CNend
\retval ::HI_SUCCESS    success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE    failure.  CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_ResetData(HI_HANDLE hTTX);

/**
\brief  Set the initial page address of teletext. CNcomment:����Teletext�ĳ�ʼҳ��CNend
\attention \n
none.
\param[in] hTTX   Teletext instance. CNcomment:Teletext�����CNend
\param[in] pstContentParam  context  parameter.  CNcomment:���ݲ�����CNend
\retval ::HI_SUCCESS    success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE    failure. CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_SwitchContent (HI_HANDLE hTTX, HI_UNF_TTX_CONTENT_PARA_S* pstContentParam);

/**
\brief  All operation related to OSD. CNcomment:��OSD��ص����в�����CNend
\attention \n
none.
\param[in] hTTX    Teletext instance.   CNcomment:Teletext�����CNend
\param[in] enMsgAction  Action of the message.  CNcomment:��Ϣָ���Ķ�����CNend
\retval ::HI_SUCCESS    success.   CNcomment:�ɹ���CNend
\retval ::HI_FAILURE    failure.   CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_Display(HI_HANDLE hTTX, HI_HANDLE hDispalyHandle);

/**
\brief   Enable  or disable teletext output, and set the type of output.
CNcomment:ʹ�ܻ�ر�teletext���������������͡�CNend
\attention \n
 The parameter can be reset  time after time.   CNcomment: ���ظ�����������á�CNend
\param[in] hTTX        Teletext instance.     CNcomment:Teletext�����CNend
\param[in]enOutput     Output  type: OSD,VBI or OSD  VBI dual output.   CNcomment:�������:OSD / VBI /OSD-VBIͬʱ�����CNend
\param[in] bEnable       HI_TRUE: enable,  HI_FALSE: disable.   CNcomment:HI_TRUE: ʹ�ܣ�HI_FALSE: �رա�CNend
\retval ::HI_SUCCESS      success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE      failure.  CNcomment:ʧ�ܡ�CNend
\see \n
none.
*/
HI_S32 HI_UNF_TTX_Output (HI_HANDLE hTTX, HI_UNF_TTX_OUTPUT_E enOutput, HI_BOOL bEnable);

/**
\brief     The function  of TTX instance to handle user's operation.  CNcomment:TTXʵ���û�������������CNend
\attention \n
none.
\param[in] hTTX     Teletext instance.   CNcomment:Teletext�����CNend
\param[in] enCMD      Type of command.   CNcomment:�������͡�CNend
\param[in] pvCMDParam     Parameter of  command(The parameter must be  conveted to appropriate  type at every
 specifical application), when the command is UPDATE or EXIT, the command can be NULL.
 CNcomment:�������(����Ӧ����Ҫǿ��ת��)��UPDATE/EXITʱ��ΪNULL��CNend
\param[out] pvCMDParam    Parameter of command , when the command is  GETPAGEADDR, it points to the address of specifical  pages.
 CNcomment:���������GETPAGEADDRʱ���ҳ��ַ��CNend
\retval ::HI_SUCCESS    success.  CNcomment:�ɹ���CNend
\retval ::HI_FAILURE    failure.  CNcomment:ʧ�ܡ�CNend
\see \n
 Please  consult  the definition of  HI_UNF_TTX_CMD_E.  CNcomment:��ο�HI_UNF_TTX_CMD_E���塣CNend
*/
HI_S32 HI_UNF_TTX_ExecCmd(HI_HANDLE hTTX,
                          HI_UNF_TTX_CMD_E enCMD, HI_VOID *pvCMDParam);

/**
\brief  Setting teletext language of region.
CNcomment:����ͼ�����������롣CNend
\attention \n
None
\param[in] handle Handle of teletext instance. CNcomment:TTXʵ�������CNend
\param[in] pu8Language language code.
CNcomment:������ CNend

\retval ::HI_SUCCESS  Operation success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_TTX_SetLanguage(HI_HANDLE hTTX, HI_U8* pu8Language);

/**
\brief  Setting max interval time of the teletext.
CNcomment:����ͼ������ʱ��ƫ�CNend
\attention \n
None
\param[in] handle Handle of teletext instance. CNcomment:TTXʵ�������CNend
\param[in] u32IntervalMs max interval of teletext, unit is Millisecondes.
CNcomment:ͼ������ʱ��ƫ��ֵ����λms��CNend

\retval ::HI_SUCCESS  Operation success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_TTX_SetMaxInterval(HI_HANDLE hTTX, HI_U32 u32IntervalMs );

/**
\brief  Setting teletext packet type.
CNcomment:����ͼ�Ľ��������ݰ����͡�CNend
\attention \n
None
\param[in] handle Handle of teletext instance. CNcomment:TTXʵ�������CNend
\param[in] enPacketType the type of teletext packet
CNcomment:ͼ�����ݰ����͡�CNend

\retval ::HI_SUCCESS  Operation success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Operation fail. CNcomment:ʧ�ܡ�CNend

\see \n
None
*/
HI_S32 HI_UNF_TTX_SetPacketType (HI_HANDLE hTTX, HI_UNF_TTX_PACKET_TYPE_E enPacketType);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
#endif
