/******************************************************************************

Copyright (C), 2012-2014, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name       : hi_unf_cc.h
Version         : Initial draft
Author          :
Created Date    :
Last Modified by:
Description     :
Function List   :
Change History  :
******************************************************************************/

/**
 * \file
 * \brief Describes the information about CC module (CC).
*/

#ifndef _HI_UNF_CC_H_
#define _HI_UNF_CC_H_

#include "hi_type.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
*                    Macro Definitions
*****************************************************************************/
#define ARIBCC_MAX_LANGUAGE 2

/*************************** Structure Definition ****************************/
/** \addtogroup      CC */
/** @{*/  /** <!-- [CC]*/

/**CC data type*//** CNcomment:CC�������ͷ��� */
typedef enum hiUNF_CC_DATA_TYPE_E
{
    HI_UNF_CC_DATA_TYPE_608,  /**<CC608*//**<CNcomment:CC608���� */
    HI_UNF_CC_DATA_TYPE_708,        /**<CC708*//**<CNcomment:CC708���� */
    HI_UNF_CC_DATA_TYPE_ARIB,       /**<ARIB CC*//**<CNcomment:ARIB CC���� */
    HI_UNF_CC_DATA_TYPE_BUTT
}HI_UNF_CC_DATA_TYPE_E;

/**708CC service channel*//** CNcomment:708CC�ķ���ͨ����*/
typedef enum hiUNF_CC_708_SERVICE_NUM_E
{
    HI_UNF_CC_708_SERVICE1 = 0x1, /**<708CC service 1*//**<CNcomment:708CC����1 */
    HI_UNF_CC_708_SERVICE2,       /**<708CC service 2*//**<CNcomment:708CC����2 */
    HI_UNF_CC_708_SERVICE3,       /**<708CC service 3*//**<CNcomment:708CC����3 */
    HI_UNF_CC_708_SERVICE4,       /**<708CC service 4*//**<CNcomment:708CC����4 */
    HI_UNF_CC_708_SERVICE5,       /**<708CC service 5*//**<CNcomment:708CC����5 */
    HI_UNF_CC_708_SERVICE6,       /**<708CC service 6*//**<CNcomment:708CC����6 */
    HI_UNF_CC_708_SERVICE_BUTT
}HI_UNF_CC_708_SERVICE_NUM_E;

/**CC608 data type*//** CNcomment:CC608��line 21���������ͷ��� */
typedef enum hiUNF_CC_608_DATATYPE_E
{
    HI_UNF_CC_608_DATATYPE_CC1,       /**<CC1*//**<CNcomment:CC1 */
    HI_UNF_CC_608_DATATYPE_CC2,       /**<CC2*//**<CNcomment:CC2 */
    HI_UNF_CC_608_DATATYPE_CC3,       /**<CC3*//**<CNcomment:CC3 */
    HI_UNF_CC_608_DATATYPE_CC4,       /**<CC4*//**<CNcomment:CC4 */
    HI_UNF_CC_608_DATATYPE_TEXT1,     /**<TEXT1*//**<CNcomment:TEXT1 */
    HI_UNF_CC_608_DATATYPE_TEXT2,     /**<TEXT2*//**<CNcomment:TEXT2 */
    HI_UNF_CC_608_DATATYPE_TEXT3,     /**<TEXT3*//**<CNcomment:TEXT3 */
    HI_UNF_CC_608_DATATYPE_TEXT4,     /**<TEXT4*//**<CNcomment:TEXT4 */
    HI_UNF_CC_608_DATATYPE_BUTT
}HI_UNF_CC_608_DATATYPE_E;

/**standard color*//** CNcomment:��׼��ɫ */
typedef enum hiUNF_CC_COLOR_E
{
    HI_UNF_CC_COLOR_DEFAULT=0x00000000,       /**<default color*//**<CNcomment:Ĭ����ɫ */
    HI_UNF_CC_COLOR_BLACK=0xff000000,         /**<black*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_WHITE=0xffffffff,         /**<white*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_RED=0xffff0000,           /**<red*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_GREEN=0xff00ff00,         /**<green*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_BLUE=0xff0000ff,          /**<blue*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_YELLOW=0xffffff00,        /**<yellow*//**<CNcomment:��ɫ */
    HI_UNF_CC_COLOR_MAGENTA=0xffff00ff,       /**<magenta*//**<CNcomment:Ʒ�� */
    HI_UNF_CC_COLOR_CYAN=0xff00ffff,          /**<cyan*//**<CNcomment:��ɫ */
}HI_UNF_CC_COLOR_E;

/**opacity*//** CNcomment:͸���� */
typedef enum hiUNF_CC_OPACITY_E
{
    HI_UNF_CC_OPACITY_DEFAULT,         /**<default*//**<CNcomment:Ĭ��͸���� */
    HI_UNF_CC_OPACITY_SOLID,           /**<opaque*//**<CNcomment:��͸�� */
    HI_UNF_CC_OPACITY_FLASH,           /**<flash*//**<CNcomment:��˸ */
    HI_UNF_CC_OPACITY_TRANSLUCENT,     /**<translucent*//**<CNcomment:��͸�� */
    HI_UNF_CC_OPACITY_TRANSPARENT,     /**<transparent*//**<CNcomment:͸�� */
    HI_UNF_CC_OPACITY_BUTT
}HI_UNF_CC_OPACITY_E;

/**justify*//** CNcomment:�Ű�*/
typedef enum hiUNF_CC_JUSTIFY_E
{
    HI_UNF_CC_JUSTIFY_LEFT,        /**<left*//**<CNcomment:���� */
    HI_UNF_CC_JUSTIFY_RIGHT,       /**<rigth*//**<CNcomment:���� */
    HI_UNF_CC_JUSTIFY_CENTER,      /**<center*//**<CNcomment:���� */
    HI_UNF_CC_JUSTIFY_FULL,        /**<full*//**<CNcomment:���˶��� */
    HI_UNF_CC_JUSTIFY_BUTT
}HI_UNF_CC_JUSTIFY_E;

/**word wrap*//** CNcomment:�Զ�����*/
typedef enum hiUNF_CC_WORDWRAP_E
{
    HI_UNF_CC_WW_DISABLE,         /**<disable*//**<CNcomment:���Զ����� */
    HI_UNF_CC_WW_ENABLE,          /**<enable*//**<CNcomment:�Զ����� */
    HI_UNF_CC_WW_BUTT
}HI_UNF_CC_WORDWRAP_E;

/**font style*//** CNcomment:������ */
typedef enum hiUNF_CC_FONTSTYLE_E
{
    HI_UNF_CC_FONTSTYLE_DEFAULT,         /**<default*//**<CNcomment:Ĭ�������� */
    HI_UNF_CC_FONTSTYLE_NORMAL,          /**<normal*//**<CNcomment:���� */
    HI_UNF_CC_FONTSTYLE_ITALIC,          /**<italic*//**<CNcomment:б�� */
    HI_UNF_CC_FONTSTYLE_UNDERLINE,       /**<underline*//**<CNcomment:�»��� */
    HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE,/**<italic&underline*//**<CNcomment:б�岢�Ҵ��»��� */
    HI_UNF_CC_FONTSTYLE_BUTT
}HI_UNF_CC_FONTSTYLE_E;

/**font size*//** CNcomment:�����С */
typedef enum hiUNF_CC_FONTSIZE_E
{
    HI_UNF_CC_FONTSIZE_DEFAULT,       /**<default font size *//**<CNcomment:Ĭ�������С */
    HI_UNF_CC_FONTSIZE_SMALL,         /**<small*//**<CNcomment:С */
    HI_UNF_CC_FONTSIZE_STANDARD,      /**<standard*//**<CNcomment:��׼ */
    HI_UNF_CC_FONTSIZE_LARGE,         /**<large*//**<CNcomment:�� */
    HI_UNF_CC_FONTSIZE_BUTT
} HI_UNF_CC_FONTSIZE_E;

typedef enum hiUNF_CC_ARIB_SCALE_E
{
    HI_UNF_CC_ARIB_SCALE_NORMAL,
    HI_UNF_CC_ARIB_SCALE_HALF_ALL,
    HI_UNF_CC_ARIB_SCALE_HALF_WIDTH,
    HI_UNF_CC_ARIB_SCALE_DOUBLE_HEIGHT,
    HI_UNF_CC_ARIB_SCALE_DOUBLE_WIDTH,
    HI_UNF_CC_ARIB_SCALE_DOUBLE_ALL,
    HI_UNF_CC_ARIB_SCALE_TINY,
    HI_UNF_CC_ARIB_SCALE_BUTT
}HI_UNF_CC_ARIB_SCALE_E;

typedef enum tagUNF_CC_ARIB_PRTDIRECT_E
{
    HI_UNF_CC_ARIB_PRINT_HORIZONTAL,
    HI_UNF_CC_ARIB_PRINT_VERTICAL,
} HI_UNF_CC_ARIB_PRTDIRECT_E;

/**font name*//** CNcomment:������ʽ */
typedef enum  hiUNF_CC_FONTNAME_E
{
    HI_UNF_CC_FN_DEFAULT,                  /**<default *//**<CNcomment:Ĭ��������ʽ */
    HI_UNF_CC_FN_MONOSPACED,               /**<monospaced*//**<CNcomment:monospaced���� */
    HI_UNF_CC_FN_PROPORT,                  /**<proport*//**<CNcomment:proport���� */
    HI_UNF_CC_FN_MONOSPACED_NO_SERIAFS,    /**<monospaced with no seriafs*//**<CNcomment:monospaced����(�޳���) */
    HI_UNF_CC_FN_PROPORT_NO_SERIAFS,       /**<proport with no seriafs*//**<CNcomment:proport����(�޳���) */
    HI_UNF_CC_FN_CASUAL,                   /**<casual*//**<CNcomment:casual���� */
    HI_UNF_CC_FN_CURSIVE,                  /**<cursive*//**<CNcomment:cursive���� */
    HI_UNF_CC_FN_SMALL_CAPITALS,           /**<small capitals*//**<CNcomment:Сд���� */
    HI_UNF_CC_FN_BUTT
}HI_UNF_CC_FONTNAME_E;

/**font edge type*//** CNcomment:�����Ե���� */
typedef enum hiUNF_CC_EdgeType_E
{
    HI_UNF_CC_EDGETYPE_DEFAULT,            /**<default *//**<CNcomment:Ĭ�������Ե���� */
    HI_UNF_CC_EDGETYPE_NONE,               /**<none edge type *//**<CNcomment:û�б�Ե */
    HI_UNF_CC_EDGETYPE_RAISED,             /**<raised *//**<CNcomment:��Եͻ�� */
    HI_UNF_CC_EDGETYPE_DEPRESSED,          /**<depressed *//**<CNcomment:��Ե���� */
    HI_UNF_CC_EDGETYPE_UNIFORM,            /**<uniform *//**<CNcomment:��Եͳһ */
    HI_UNF_CC_EDGETYPE_LEFT_DROP_SHADOW,   /**<left drop shadow *//**<CNcomment:������Ӱ */
    HI_UNF_CC_EDGETYPE_RIGHT_DROP_SHADOW,  /**<right drop shadow *//**<CNcomment:������Ӱ */
    HI_UNF_CC_EDGETYPE_BUTT
}HI_UNF_CC_EdgeType_E;

/**display format of caption display screen*//** CNcomment:��ʾ���ڵ���ʾģʽ */
typedef enum hiUNF_CC_DF_E
{
    HI_UNF_CC_DF_720X480,       /**<caption display screen is 720*480*//**<CNcomment:��ʾ���ڵĿ����720*480 */
    HI_UNF_CC_DF_720X576,       /**<caption display screen is 720*576*//**<CNcomment:��ʾ���ڵĿ����720*576 */
    HI_UNF_CC_DF_960X540,       /**<caption display screen is 960*540*//**<CNcomment:��ʾ���ڵĿ����960*540 */
    HI_UNF_CC_DF_1280X720,      /**<caption display screen is 1280*720*//**<CNcomment:��ʾ���ڵĿ����1280*720 */
    HI_UNF_CC_DF_1920X1080,     /**<caption display screen is 1920*1080*//**<CNcomment:��ʾ���ڵĿ����1920*1080 */
    HI_UNF_CC_DF_BUTT
} HI_UNF_CC_DF_E;

/**CC display operation*//** CNcomment:CC��ʾ���� */
typedef enum hiUNF_CC_OPT_E
{
     HI_UNF_CC_OPT_DRAWTEXT = 0x1, /**<draw text *//**<CNcomment:�����ı� */
     HI_UNF_CC_OPT_DRAWBITMAP,     /**<draw bitmap *//**<CNcomment:����λͼ */
     HI_UNF_CC_OPT_FILLRECT,       /**<fill rect *//**<CNcomment:���������� */
     HI_UNF_CC_OPT_UPDATE,        /**<Display buffer on the screen. *//**<CNcomment:�����������������Ƶ���Ļ�� */
     HI_UNF_CC_OPT_DRAWLINE,        /**<draw line. *//**<CNcomment:����*/
     HI_UNF_CC_OPT_BUTT
} HI_UNF_CC_OPT_E;

/**Arib CC rollup mode*//** CNcomment:arib CC rollupģʽ*/
typedef enum hiUNF_CC_ARIB_ROLLUP_E
{
    HI_UNF_CC_ARIB_NON_ROLLUP,        /**<Non roll-up *//**<CNcomment:��rollupģʽ*/
    HI_UNF_CC_ARIB_ROLLUP,      /**<roll-up*//**<CNcomment:rollupģʽ*/
    HI_UNF_CC_ARIB_ROLLUP_BUTT
}HI_UNF_CC_ARIB_ROLLUP_E;


/**Arib CC character coding*//** CNcomment:arib CC �ַ����뷽ʽ*/
typedef enum hiUNF_CC_ARIB_TCS_E
{
    HI_UNF_CC_ARIB_TCS_8BIT,         /**<the type of character codig is 8bit-code*//**<CNcomment:�ַ����뷽ʽ(8λ)*/
    HI_UNF_CC_ARIB_TCS_BUTT
}HI_UNF_CC_ARIB_TCS_E;

/**Arib CC display format*//** CNcomment:arib CC��ʾ��ʽ*/
typedef enum hiUNF_CC_ARIB_DF_E
{
    HI_UNF_CC_ARIB_DF_HORIZONTAL_SD,                /**<horizontal writing in stardard density*/    /**<CNcomment:ˮƽ��ʾ������*/
    HI_UNF_CC_ARIB_DF_VERTICAL_SD,                  /**<vertical writing in standard density*/      /**<CNcomment:��ֱ��ʾ������*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_HD,                /**<horizontal writing in high density*/        /**<CNcomment:ˮƽ��ʾ������*/
    HI_UNF_CC_ARIB_DF_VERTICAL_HD,                  /**<vertical writing in high density*/          /**<CNcomment:��ֱ��ʾ������*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_WESTERN,           /**<horizontal writing of western language*/    /**<CNcomment:ˮƽ��ʾ������*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_1920X1080,         /**<horizontal writing in 1920X1080*/           /**<CNcomment:ˮƽ��ʾ����Ļ1920X1080*/
    HI_UNF_CC_ARIB_DF_VERTICAL_1920X1080,           /**<vertical writing in 1920X1080*/             /**<CNcomment:��ֱ��ʾ����Ļ1920X1080*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_960X540,           /**<horizontal writing in 960X540*/             /**<CNcomment:ˮƽ��ʾ����Ļ960X540*/
    HI_UNF_CC_ARIB_DF_VERTICAL_960X540,             /**<vertical writing in 960X540*/               /**<CNcomment:��ֱ��ʾ����Ļ960X540*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_1280X720,          /**<horizontal writing in 1280X720*/            /**<CNcomment:ˮƽ��ʾ����Ļ1280X720*/
    HI_UNF_CC_ARIB_DF_VERTICAL_1280X720,            /**<vertical writing in 1280X720*/              /**<CNcomment:��ֱ��ʾ����Ļ1280X720*/
    HI_UNF_CC_ARIB_DF_HORIZONTAL_720X480,           /**<horizontal writing in 720X480*/             /**<CNcomment:ˮƽ��ʾ����Ļ720X480*/
    HI_UNF_CC_ARIB_DF_VERTICAL_720X480,             /**<vertical writing in 720X480*/               /**<CNcomment:��ֱ��ʾ����Ļ720X480*/
    HI_UNF_CC_ARIB_DF_BUTT
}HI_UNF_CC_ARIB_DF_E;

/**Arib CC display mode*//** CNcomment:arib CC��ʾģʽ*/
typedef enum hiUNF_CC_ARIB_DMF_E
{
    HI_UNF_CC_ARIB_DMF_AUTO_AND_AUTO=0x0,           /**<atomatic display when received ,automatic display when recording and playback */                    /**<CNcomment:���պ��Զ����ţ�¼�ƺͻط�ʱ�Զ�����*/
    HI_UNF_CC_ARIB_DMF_AUTO_AND_NOT,                /**<atomatic display when received ,Non-displayed automatically when recording and playback*/           /**<CNcomment:���պ��Զ����ţ�¼�ƺͻط�ʱ���Զ�����*/
    HI_UNF_CC_ARIB_DMF_AUTO_AND_SELECT,             /**<atomatic display when received ,Selectable display when recording and playback*/                    /**<CNcomment:���պ��Զ����ţ�¼�ƺͻط�ʱ��ѡ�񲥷�*/
    HI_UNF_CC_ARIB_DMF_NON_AND_AUTO=0x4,            /**<non-displayed automatically when received, automatic display when recording and playback */         /**<CNcomment:����ʱ���Զ����ţ�¼�ƺͻط�ʱ�Զ�����*/
    HI_UNF_CC_ARIB_DMF_NON_AND_NON,                 /**<non-displayed automatically when received,Non-displayed automatically when recording and playback*/ /**<CNcomment:����ʱ���Զ����ţ�¼�ƺͻط�ʱ���Զ�����*/
    HI_UNF_CC_ARIB_DMF_NON_AND_SELECT,              /**<non-displayed automatically when received,Selectable display when recording and playback*/          /**<CNcomment:����ʱ���Զ����ţ�¼�ƺͻط�ʱ��ѡ�񲥷�*/
    HI_UNF_CC_ARIB_DMF_SELECT_AND_AUTO=0x8,         /**<selectable display when received, automatic display when recording and playback */                  /**<CNcomment:����ʱ��ѡ�񲥷ţ�¼�ƺͻط�ʱ���Զ�����*/
    HI_UNF_CC_ARIB_DMF_SELECT_AND_NON,              /**<selectable display when received,Non- displayed automatically when recording and playback*/         /**<CNcomment:����ʱ��ѡ�񲥷ţ�¼�ƺͻط�ʱ���Զ�����*/
    HI_UNF_CC_ARIB_DMF_SELECT_AND_SELECT,           /**<selectable display when received,Selectable display when recording and playback*/                   /**<CNcomment:����ʱ��ѡ�񲥷ţ�¼�ƺͻط�ʱ��ѡ�񲥷�*/
    HI_UNF_CC_ARIB_DMF_SPECIAL_AND_AUTO=0xc,        /**<automatic display/non-display under specific condition when received,automatic display when recording and playback */           /**<CNcomment:����ʱ�ض�������Զ�/���Զ����ţ�¼�ƺͻط�ʱ�Զ�����*/
    HI_UNF_CC_ARIB_DMF_SPECIAL_AND_NON,             /**<automatic display/non-display under specific condition when received,Non-displayed automatically when recording and playback*/  /**<CNcomment:����ʱ�ض�������Զ�/���Զ����ţ�¼�ƺͻط�ʱ���Զ�����*/
    HI_UNF_CC_ARIB_DMF_SPECIAL_AND_SELECT,          /**<automatic display/non-display under specific condition when received,Selectable display when recording and playback*/           /**<CNcomment:����ʱ�ض�������Զ�/���Զ����ţ�¼�ƺͻط�ʱ��ѡ�񲥷�*/
    HI_UNF_CC_ARIB_DMF_BUTT
}HI_UNF_CC_ARIB_DMF_E;

/**Arib CC time control mode*//** CNcomment:arib CCʱ�����ģʽ*/
typedef enum hiUNF_CC_ARIB_TMD_E
{
    HI_UNF_CC_ARIB_TMD_FREE,            /**<playback time is not restricted to synchronize to the clock*//**<CNcomment:�ط�ʱ���ʱ���޹�*/
    HI_UNF_CC_ARIB_TMD_REAL_TIME,       /**<playback time is given by PTS*//**<CNcomment:�ط�ʱ����PTS����*/
    HI_UNF_CC_ARIB_TMD_OFFSET_TIME,     /**<playback time added with offset time should be the new playback time*//**<CNcomment:�ط�ʱ�����ƫ��ʱ�佫���µ��ط�ʱ��*/
    HI_UNF_CC_ARIB_TMD_BUTT
}HI_UNF_CC_ARIB_TMD_E;

/**CC608 VBI data*//** CNcomment:CC608 VBI���� */
typedef struct hiUNF_CC_VBI_DADA_S
{
    HI_U8 u8FieldParity; /**<parity field *//**<CNcomment:��ż�� */
    HI_U8 u8Data1;       /**<first byte *//**<CNcomment:��һ���ֽ� */
    HI_U8 u8Data2;       /**<second byte *//**<CNcomment:�ڶ����ֽ� */
}HI_UNF_CC_VBI_DADA_S;

/**CC rect*//** CNcomment:����CC��������*/
typedef struct hiUNF_CC_RECT_S
{
    HI_U16 x;           /**<x cordinate *//**<CNcomment:�������Ͻǵ�x���� */
    HI_U16 y;           /**<y cordinate *//**<CNcomment:�������Ͻǵ�y���� */
    HI_U16 width;       /**<rect width *//**<CNcomment:���εĿ�� */
    HI_U16 height;      /**<rect heigth *//**<CNcomment:���εĸ߶� */
}HI_UNF_CC_RECT_S;

/**CC color components*//** CNcomment:CC������ɫ�ṹ */
typedef struct hiUNF_CC_COLOR_S
{
    HI_U8 u8Blue;       /**<blue component *//**<CNcomment:B������ɫֵ */
    HI_U8 u8Green;      /**<green component *//**<CNcomment:G������ɫֵ */
    HI_U8 u8Red;        /**<red component *//**<CNcomment:R������ɫֵ */
    HI_U8 u8Alpha;      /**<alpha component *//**<CNcomment:͸���ȣ�ֵΪ0Ϊ͸����0xFFΪ��͸�� */
} HI_UNF_CC_COLOR_S;

/**CC data with text format*//** CNcomment:�ı���ʽ��CC���� */
typedef struct hiUNF_CC_TEXT_S
{
    HI_U16                 *pu16Text;    /**<cc data,2 bytes,unicode *//**<CNcomment:cc���ݣ�unicode���룬2���ֽ� */
    HI_U8                  u8TextLen;    /**<cc data length *//**<CNcomment:Ҫ��ʾ��cc���ݳ��� */

    HI_UNF_CC_COLOR_S      stFgColor;    /**<cc foregroud color*//**<CNcomment:Ҫ��ʾ��cc����ǰ��ɫ */
    HI_UNF_CC_COLOR_S      stBgColor;    /**<cc backgroud color*//**<CNcomment:Ҫ��ʾ��cc�������屳��ɫ */
    HI_UNF_CC_COLOR_S      stEdgeColor;   /**<cc edge color*//**<CNcomment:Ҫ��ʾ��cc���������Ե��ɫ*/

    HI_U8                  u8Justify;    /*see HI_UNF_CC_JUSTIFY_E,used when decode cc708*//**<CNcomment:cc������ʾʱ���Ű淽ʽ */
    HI_U8                  u8WordWrap;   /*see HI_UNF_CC_WORDWRAP_E,used when decode cc708*//**<CNcomment:�Զ����� */
    HI_UNF_CC_FONTSTYLE_E  enFontStyle;  /*font style ,see HI_UNF_CC_FONTSTYLE_E*//**<CNcomment:Ҫ��ʾ��cc���ݵ������� */
    HI_UNF_CC_FONTSIZE_E   enFontSize;   /*font size ,see HI_UNF_CC_FONTSIZE_E*//**<CNcomment:Ҫ��ʾ��cc���ݵ������С */
    HI_UNF_CC_EdgeType_E   enEdgetype;  /**<cc edge type*//**<CNcomment:Ҫ��ʾ��cc���������Ե����*/
    HI_U8                  u8AribFontSize;   /*font size *//**<CNcomment:Ҫ��ʾ��cc���ݵ������С */
    HI_UNF_CC_ARIB_SCALE_E enScaleType;
    HI_U8                  u8CharInterval;
    HI_U8                  u8LineInterval;
    HI_UNF_CC_ARIB_PRTDIRECT_E enPrtDirect;
} HI_UNF_CC_TEXT_S;

/**CC data with bitmap format*//** CNcomment:λͼ��ʽ��CC���� */
typedef struct hiUNF_CC_BITMAP_S
{
    HI_S32                 s32BitWidth;         /**<bit width, is 2/4/8/16/24/32 *//**<CNcomment:λ��,ֵ��2/4/8/16/24/32 */
    HI_U8                  *pu8BitmapData;      /**<pixel data *//**<CNcomment:ͼ������ */
    HI_U32                 u32BitmapDataLen;    /**<length of pixel data *//**<CNcomment:ͼ�����ݳ��� */
    HI_UNF_CC_COLOR_S      astPalette[256];     /**<palette data *//**<CNcomment:��ɫ������ */
    HI_U32                 u32PaletteLen;       /**<length of palette data *//**<CNcomment:��ɫ�����ݳ��� */
} HI_UNF_CC_BITMAP_S;

/**parameter of fill rect*//** CNcomment:����������Ĳ��� */
typedef struct hiUNF_CC_FILLRECT_S
{
    HI_UNF_CC_COLOR_S      stColor;      /**<color *//**<CNcomment:��ɫֵ */
} HI_UNF_CC_FILLRECT_S;

typedef struct hiUNF_CC_LINE_S
{
    HI_U32 u32X1;      /*�����������X1*/
    HI_U32 u32Y1;      /*�����������Y1*/
    HI_U32 u32X2;      /*�����յ�����X2*/
    HI_U32 u32Y2;      /*�����յ�����Y2*/
    HI_UNF_CC_COLOR_S      stColor;      /*�ߵ���ɫֵ*/
} HI_UNF_CC_LINE_S;

/**CC display param*//** CNcomment:����CC������ʾʱ�Ĳ��� */
typedef struct hiUNF_CC_DISPLAY_PARAM_S
{
    HI_UNF_CC_OPT_E        enOpt;
    HI_U32                 u32DisplayWidth; /**<display screen width*//**<CNcomment:������� */
    HI_U32                 u32DisplayHeight;/**<display screen height*//**<CNcomment:�����߶� */
    HI_UNF_CC_RECT_S       stRect;          /**<cc display location*//**<CNcomment:Ҫ��ʾ��cc���ݵ�λ����Ϣ */
    union
    {
        HI_UNF_CC_TEXT_S   stText;          /**<CC data with text format*//**<CNcomment:�ı���ʽ��CC���� */
        HI_UNF_CC_BITMAP_S stBitmap;        /**<CC data with bitmap format*//**<CNcomment:λͼ��ʽ��CC���� */
        HI_UNF_CC_FILLRECT_S stFillRect;    /**<parameter of fill rect*//**<CNcomment:����������Ĳ��� */
        HI_UNF_CC_LINE_S   stLine;          /**<CC data with line format*//**<CNcomment:ֱ�߸�ʽ��CC���� */
    } unDispParam;

    HI_BOOL bBlit;                          /**<Whether display on screen. HI_TRUE for display immediately and HI_FALSE for save in buffer. */
                                            /**<CNcomment:�Ƿ��������Ƶ���Ļ�ϣ�HI_TRUE��ʾ�������ƣ�HI_FALSE��ʾ�Ȼ��浽buffer�ϣ��ݲ����Ƶ���Ļ�� */
} HI_UNF_CC_DISPLAY_PARAM_S;

/**
\brief cc get text size callback function. CNcomment: cc���ڻ�������С(���)�Ļص�������CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] u32UserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[in] u16Str  string. CNcomment: ���ݵ�ַ��CNend
\param[in] s32StrNum  number of character. CNcomment: ���ݳ��ȡ�CNend
\param[out] ps32Width  total width of character. CNcomment: �õ��������CNend
\param[out] ps32Heigth heigth of character. CNcomment: �õ�������ߡ�CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_GETTEXTSIZE_CB_FN)(HI_VOID* pUserData, HI_U16 *u16Str,HI_S32 s32StrNum, HI_S32 *ps32Width, HI_S32 *ps32Heigth);

/**
\brief cc get text size callback function(EX). CNcomment: cc���ڻ�������С(���)�Ļص�����(��չ���)��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] u32UserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[in] pstText  text data. CNcomment: �ı���Ϣ��CNend
\param[out] ps32Width  total width of character. CNcomment: �õ��������CNend
\param[out] ps32Heigth heigth of character. CNcomment: �õ�������ߡ�CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_GETTEXTSIZE_EX_CB_FN)(HI_U32 u32Userdata, HI_UNF_CC_TEXT_S *pstText, HI_S32 *ps32Width, HI_S32 *ps32Heigth);


/**
\brief cc display callback function. CNcomment: cc��ʾ���ݻص���CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] u32UserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[in] pstCCdisplayParam parameter of display. CNcomment: cc��ʾ���ݽṹ��CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_DISPLAY_CB_FN)(HI_VOID* pUserData, HI_UNF_CC_DISPLAY_PARAM_S *pstCCdisplayParam);


/**
\brief cc get avplay pts callback function. CNcomment: cc��ȡ��ǰ��Ŀ��PTSֵ�Ļص���CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] pUserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[out] ps64CurrentPts current pts. CNcomment: �洢��ǰPTSֵ�ı���ָ�롣CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_GETPTS_CB_FN)(HI_VOID* pUserData, HI_S64 *ps64CurrentPts);

/**
\brief cc data blit callback function. CNcomment: cc���ݰ��ƻص���CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] pUserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[in] SrcRect source rect. CNcomment: ��Ҫ���Ƶ�ԭ����CNend
\param[in] DstRect destination rect. CNcomment: ��Ҫ���Ƶ�Ŀ������CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_BLIT_CB_FN)(HI_VOID* pUserData, HI_UNF_CC_RECT_S *pstSrcRect, HI_UNF_CC_RECT_S *pstDstRect);

/**
\brief cc data blit callback function. CNcomment: cc vbi ��������ص���CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in] pUserData user data. CNcomment: HI_UNF_CC_Create������û�˽�����ݡ�CNend
\param[out] pstVBIOddDataField1 VBI data,odd field data. CNcomment: VBI���ݽṹ,�泡���ݡ�CNend
\param[out] pstVBIEvenDataField2 VBI data,even field data. CNcomment: VBI���ݽṹ,ż�����ݡ�CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
none. CNcomment: �ޡ�CNend
*/
typedef HI_S32 (*HI_UNF_CC_VBI_CB_FN)(HI_VOID* pUserData, HI_UNF_CC_VBI_DADA_S *pstVBIOddDataField1,HI_UNF_CC_VBI_DADA_S *pstVBIEvenDataField2);

/**
\brief output XDS packets in CC608. CNcomment: ���CC608�е�XDS�����ݡ�CNend
\attention \n
XDS packet is a third data service intended to supply program related and other information.
CNcomment: XDS���ǵ��������ݷ��������ṩ��Ŀ�������������Ϣ��CNend
\param[in] u8XDSClass XDS class. CNcomment: XDS�ķ��ࡣCNend
\param[in] u8XDSPacketType  XDS packet type. CNcomment: XDS���ݰ������͡�CNend
\param[in] pu8Data  XDS data. CNcomment: XDS���ݡ�CNend
\param[in] u8DataLen  XDS data length. CNcomment: XDS���ݳ��ȡ�CNend
\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\see \n
Decoding of XDS packet data, see sample/cc/sample_cc_xds.c.
CNcomment: XDS���ݰ��Ľ�������ο�sdk��sample/cc/sample_cc_xds.c��CNend
*/
typedef HI_S32 (*HI_UNF_CC_XDS_CB_FN)(HI_U8 u8XDSClass, HI_U8 u8XDSPacketType, HI_U8 *pu8Data, HI_U8 u8DataLen);


/**user data in MPEG*//** CNcomment:MPEG�е�USERDATA���� */
typedef struct hiUNF_CC_USERDATA_S
{
    HI_U8       *pu8userdata;  /**<cc user data in mpeg *//**<CNcomment:mpeg��Ƶ֡�е�cc�û����� */
    HI_U32      u32dataLen;    /**<cc user data length *//**<CNcomment:cc���ݳ��� */
    HI_BOOL     bTopFieldFirst;/**<cc top field first flag *//**<CNcomment:cc�������ȱ�� */
} HI_UNF_CC_USERDATA_S;

/**CC608 config param *//** CNcomment:CC608 ������Ϣ���� */
/**CC608 just support 8 stardard colors*//**CNcomment:CC608ֻ֧��8�ֱ�׼��ɫ*/
typedef struct hiUNF_CC_608_CONFIGPARAM_S
{
    HI_UNF_CC_608_DATATYPE_E    enCC608DataType;        /**<CC608 data type *//**<CNcomment:����cc608�������� */
    HI_U32                      u32CC608TextColor;      /**<CC608 text color *//**<CNcomment:����cc608������ɫ */
    HI_UNF_CC_OPACITY_E         enCC608TextOpac;        /**<CC608 text opacity *//**<CNcomment:����cc608����͸���� */
    HI_U32                      u32CC608BgColor;        /**<CC608 background color *//**<CNcomment:����cc608����ɫ */
    HI_UNF_CC_OPACITY_E         enCC608BgOpac;          /**<CC608 background opacity *//**<CNcomment:����cc608����͸���� */
    HI_UNF_CC_FONTSTYLE_E       enCC608FontStyle;       /**<CC608 font style *//**<CNcomment:����cc608������ */
    HI_UNF_CC_DF_E              enCC608DispFormat;      /**<CC608 display format of caption display screen *//**<CNcomment:����cc608��ʾģʽ */
    HI_BOOL                     bLeadingTailingSpace;   /**<CC608 leading/tailing space flag*//**<CNcomment: �Ƿ���ʾleading/tailing space*/
} HI_UNF_CC_608_CONFIGPARAM_S;

/**CC708 config param *//** CNcomment:CC708 ������Ϣ���� */
/**CC708 color specification CEA-708-B-1999.pdf section 9.20 Color Representation*//**CNcomment:CC708��ɫ˵����ο�Э��CEA-708-B-1999.pdf 9.20 ��ɫ���� �½�*/
/**The specification does not define the specific color component, using the following component values in our version*/
/**Э����û�ж���������ɫ�����������ǰ汾�в������·���ֵ*/
/**CC708 support 64 colors.one of RGB color components can be 0x00,0x5f,0xaf,0xff*//**CNcomment:CC708֧��64����ɫ,һ��RGB������ȡ��ֵ��0x00,0x5f,0xaf,0xff��4��*/
/** 0x    FF          FF          FF          FF*/       /**CNcomment: 0x FF     FF         FF          FF*/
/**    reserve    red value   green value  blue value*/  /**              ����   ��ɫ����   ��ɫ����    ��ɫ����*/
typedef struct hiUNF_CC_708_CONFIGPARAM_S
{
    HI_UNF_CC_708_SERVICE_NUM_E enCC708ServiceNum;      /**<CC708 service number *//**<CNcomment:����cc708����ͨ���� */
    HI_UNF_CC_FONTNAME_E        enCC708FontName;        /**<CC708 font name *//**<CNcomment:����cc708���� */
    HI_UNF_CC_FONTSTYLE_E       enCC708FontStyle;       /**<CC708 font style *//**<CNcomment:����cc708������ */
    HI_UNF_CC_FONTSIZE_E        enCC708FontSize;        /**<CC708 font size *//**<CNcomment:����cc708�����С */
    HI_U32                      u32CC708TextColor;      /**<CC708 text color *//**<CNcomment:����cc708������ɫ */
    HI_UNF_CC_OPACITY_E         enCC708TextOpac;        /**<CC708 text opacity *//**<CNcomment:����cc708����͸���� */
    HI_U32                      u32CC708BgColor;        /**<CC708 background color *//**<CNcomment:����cc708������ɫ */
    HI_UNF_CC_OPACITY_E         enCC708BgOpac;          /**<CC708 background opacity *//**<CNcomment:����cc708����͸���� */
    HI_U32                      u32CC708WinColor;       /**<CC708 window color *//**<CNcomment:����cc708������ɫ */
    HI_UNF_CC_OPACITY_E         enCC708WinOpac;         /**<CC708 window opacity *//**<CNcomment:����cc708����͸���� */
    HI_UNF_CC_EdgeType_E        enCC708TextEdgeType;    /**<CC708 text egde type *//**<CNcomment:����cc708�����Ե���� */
    HI_U32                      u32CC708TextEdgeColor;  /**<CC708 text edge color *//**<CNcomment:����cc708�����Ե��ɫ */
    HI_UNF_CC_DF_E              enCC708DispFormat;      /**<CC708 display format of caption display screen *//**<CNcomment:����cc708��ʾģʽ */
} HI_UNF_CC_708_CONFIGPARAM_S;

/**ARIB CC config param *//** CNcomment:ARIB CC ������Ϣ���� */
typedef struct hiUNF_CC_ARIB_CONFIGPARAM_S
{
    HI_U32      u32BufferSize;   /**<size of buffer which used to cache pes data,Recommends its value is 64K ~ 512K.note:This value can only be set when created,does not support dynamic setting*/
                                 /**<CNcomment:����PES���ݵĻ�������С��ȡֵΪ64k~512K��ע��:���ֵֻ���ڴ���ʱ���ã���֧�ֶ�̬����*/
} HI_UNF_CC_ARIB_CONFIGPARAM_S;

/**CC data attribution *//** CNcomment:CC������Ϣ */
typedef struct hiUNF_CC_ATTR_S
{
    HI_UNF_CC_DATA_TYPE_E enCCDataType;   /**<cc data type *//**<CNcomment:cc�������� */
    union
    {
        HI_UNF_CC_608_CONFIGPARAM_S  stCC608ConfigParam;   /**<CC608 config param *//**<CNcomment:CC608 ������Ϣ���� */
        HI_UNF_CC_708_CONFIGPARAM_S  stCC708ConfigParam;   /**<CC708 config param *//**<CNcomment:CC708 ������Ϣ���� */
        HI_UNF_CC_ARIB_CONFIGPARAM_S stCCARIBConfigParam;  /**<ARIB CC config param *//**<CNcomment:ARIB CC ������Ϣ���� */
    } unCCConfig;
} HI_UNF_CC_ATTR_S;

/**CC instance param *//** CNcomment:����ʵ��ʱ��Ҫ�Ĳ�����Ϣ */
typedef struct hiUNF_CC_PARAM_S
{
    HI_UNF_CC_ATTR_S             stCCAttr;           /**<cc attribution *//**<CNcomment:cc������Ϣ */

    HI_UNF_CC_GETPTS_CB_FN       pfnCCGetPts;        /**<get current pts callback function *//**<CNcomment:��ȡ��ǰpts�Ļص����� */
    HI_UNF_CC_DISPLAY_CB_FN      pfnCCDisplay;       /**<cc display callback function *//**<CNcomment:cc��ʾ�Ļص����� */
    HI_UNF_CC_GETTEXTSIZE_CB_FN  pfnCCGetTextSize;   /**<cc get text size callback function *//**<CNcomment:cc���ڻ�������С(���)�Ļص�����  */
    HI_UNF_CC_GETTEXTSIZE_EX_CB_FN pfnCCGetTextSizeEx;
    HI_UNF_CC_BLIT_CB_FN         pfnBlit;            /**<cc data blit callback function *//**<CNcomment:����cc��������Ļ�ϰ��ƵĻص����� */
    HI_UNF_CC_VBI_CB_FN          pfnVBIOutput;       /**<output VBI data callback function *//**<CNcomment:���VBI���ݻص����� */
    HI_UNF_CC_XDS_CB_FN          pfnXDSOutput;       /**<output XDS packets function *//**<CNcomment:���CC608�е�XDS������ */
    HI_VOID*                     pUserData;        /**<user data,used in callback function *//**<CNcomment:�û�˽�����ݣ����ڻص����� */
} HI_UNF_CC_PARAM_S;

/*ARIB CC info node*//** CNcomment:arib cc��Ļ��Ϣ�ڵ� */
typedef struct hiUNF_CC_ARIB_INFONODE_S
{
    HI_U8 u8LanguageTag;                   /**<identification of language*//**<CNcomment:��Ļ���Ա�� */
    HI_UNF_CC_ARIB_DMF_E    enCCAribDMF;   /**<display mode *//**<CNcomment:��ʾģʽ */
    HI_CHAR    acISO639LanguageCode[4];    /**<language code *//**<CNcomment:��Ļ���Դ��� */
    HI_UNF_CC_ARIB_DF_E enCCAribDF;        /**<display format *//**<CNcomment:��ʾ��ʽ */
    HI_UNF_CC_ARIB_TCS_E enCCAribTCS;         /**<character coding *//**<CNcomment:�ַ����� */
    HI_UNF_CC_ARIB_ROLLUP_E enCCAribRollup;    /**<roll-up mode *//**<CNcomment:roll-upģʽ */
}HI_UNF_CC_ARIB_INFONODE_S;

/*ARIB CC info struct*//** CNcomment:arib cc��Ļ��Ϣ�ṹ�� */
typedef struct hiUNF_CC_ARIB_INFO_S
{
    HI_UNF_CC_ARIB_TMD_E enCCAribTMD;   /**<time control mode*//**<CNcomment:ʱ�����ģʽ */
    HI_U32 u32NumLanguage;       /**<number of languages *//**<CNcomment:��Ļ���Ը��� */
    HI_UNF_CC_ARIB_INFONODE_S stCCAribInfonode[ARIBCC_MAX_LANGUAGE];     /**<array of arib cc info *//**<CNcomment:arib cc��Ļ��Ϣ���� */
}HI_UNF_CC_ARIB_INFO_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API Declaration *****************************/
/**
\brief Initialize cc module. CNcomment: ��ʼ��CCģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\retval ::HI_SUCCESS initialize success. CNcomment: ��ʼ���ɹ���CNend
\retval ::HI_FAILURE initialize failure. CNcomment: ��ʼ��ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Init(HI_VOID);

/**
\brief DeInitialize cc module. CNcomment: ȥ��ʼ��CCģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\retval ::HI_SUCCESS deinitialize success. CNcomment: ȥ��ʼ���ɹ���CNend
\retval ::HI_FAILURE deinitialize failure. CNcomment: ȥ��ʼ��ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_DeInit(HI_VOID);

/**
\brief Get default attribution in cc module. CNcomment: ��ȡCCģ���Ĭ������ֵ��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_GetDefaultAttr(HI_UNF_CC_ATTR_S *pstDefaultAttr);

/**
\brief open cc module. CNcomment: ����ccʵ����CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  pstAttr  cc attribution. CNcomment: ����ʱ����Ľ��������ԡ�CNend
\param[out]  phCC  cc handle. CNcomment: ccģ������CNend
\retval ::HI_SUCCESS success. CNcomment: �����ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ����ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Create(HI_UNF_CC_PARAM_S *pstCCParam, HI_HANDLE *phCC);

/**
\brief close cc module. CNcomment: ����ccʵ����CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\retval ::HI_SUCCESS success. CNcomment: ���ٳɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ����ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Destroy(HI_HANDLE hCC);

/**
\brief start cc module. CNcomment: ��ʼccģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Start(HI_HANDLE hCC);

/**
\brief stop cc module. CNcomment: ����ccģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Stop(HI_HANDLE hCC);

/**
\brief reset cc module. CNcomment: ��λccģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_Reset(HI_HANDLE hCC);

/**
\brief inject mpeg userdata to  cc module. CNcomment: ע��mpeg�û����ݵ�ccģ�顣CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\param[in]  pstUserData  cc userdata structure used in inject cc data. CNcomment: �û����ݽṹ�塣CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_InjectUserData(HI_HANDLE hCC, HI_UNF_CC_USERDATA_S *pstUserData);

/**
\brief inject cc pes data to cc module. CNcomment: ע��pes���ݵ�ccģ��(�ݲ�֧��)��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment:ģ������CNend
\param[in]  pu8PesData  pes data address. CNcomment: pes�����׵�ַ��CNend
\param[in]  u32DataLen  pes data length. CNcomment: pes���ݳ��ȡ�CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_InjectPESData(HI_HANDLE hCC, HI_U8 *pu8PesData, HI_U32 u32DataLen);

/**
\brief get cc attribution. CNcomment: ��ȡcc������Ϣ��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment: ģ������CNend
\param[out]  pstCCAttr  cc attribution structure. CNcomment: ������Ϣ�ṹ�塣CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_GetAttr(HI_HANDLE hCC, HI_UNF_CC_ATTR_S *pstCCAttr);

/**
\brief set cc attribution. CNcomment:����cc������Ϣ��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  cc handle. CNcomment. CNcomment: ģ������CNend
\param[in]  pstCCAttr  cc attribution structure. CNcomment:������Ϣ�ṹ�塣CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_SetAttr(HI_HANDLE hCC, HI_UNF_CC_ATTR_S *pstCCAttr);


/**
\brief get cc arib info. CNcomment: ��ȡarib cc��Ļ��Ϣ��CNend
\attention \n
none. CNcomment: �ޡ�CNend
\param[in]  hCC  arib cc handle. CNcomment: ģ������CNend
\param[out]  pstCCAttr  arib cc info structure. CNcomment:arib cc��Ļ��Ϣ�ṹ�塣CNend
\retval ::HI_SUCCESS success. CNcomment: �ɹ���CNend
\retval ::HI_FAILURE failure. CNcomment: ʧ�ܡ�CNend
\see \n
none. CNcomment: �ޡ�CNend
*/
HI_S32 HI_UNF_CC_GetARIBCCInfo(HI_HANDLE hCC,HI_UNF_CC_ARIB_INFO_S *pstCCAribInfo);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
