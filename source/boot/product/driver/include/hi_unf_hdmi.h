/*******************************************************************************
 *              Copyright 2005 - 2006, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName:    hi_hdmi.h
 * Description: This is internal include file for irda
 *
 * History:
 * Version      Date         Author       DefectNum    Description
 *  0.01     2010-08-06      luochen      NULL       Create this file
 ******************************************************************************/

#ifndef  __HI_HDMI_H__
#define  __HI_HDMI_H__

#include "hi_type.h"
//#include "eedefs.h"
//#include "hdmitx.h"
//#include "infofrm.h"
#include "hi_unf_disp.h"
//#include "de.h"
#include "hi_common.h"
#include "hi_type.h"
#include "exports.h"
#ifdef HI_HDMI_EDID_SUPPORT
#include "hi_unf_edid.h"
#include "hi_drv_pdm.h"
#endif
#ifdef HI_ADVCA_FUNCTION_RELEASE
#define HDMIPrint(format, arg...)
#else
//#define HDMIPrint(fmt, arg...)   printf( fmt,##arg)
#define HDMIPrint(fmt...)    HI_INFO_PRINT(HI_ID_HDMI, fmt)//printf(fmt)
#endif

typedef enum hiUNF_HDMI_VIDEO_MODE
{
    HI_UNF_HDMI_VIDEO_MODE_RGB444, 
    HI_UNF_HDMI_VIDEO_MODE_YCBCR422,
    HI_UNF_HDMI_VIDEO_MODE_YCBCR444,  
	HI_UNF_HDMI_VIDEO_MODE_YCBCR420, 	
    HI_UNF_HDMI_VIDEO_MODE_BUTT    
}HI_UNF_HDMI_VIDEO_MODE_E;

/**HDMI Deep color mode*//**CNcomment: HDMI ��ɫģʽ */
typedef enum hiUNF_HDMI_DEEP_COLOR_E
{
    HI_UNF_HDMI_DEEP_COLOR_24BIT = 0x00,    /**<HDMI Deep color 24bit mode*//**<CNcomment:HDMI 24bit ��ɫģʽ  */
    HI_UNF_HDMI_DEEP_COLOR_30BIT,           /**<HDMI Deep color 30bit mode*//**<CNcomment:HDMI 30bit ��ɫģʽ  */
    HI_UNF_HDMI_DEEP_COLOR_36BIT,           /**<HDMI Deep color 36bit mode*//**<CNcomment:HDMI 36bit ��ɫģʽ  */
    HI_UNF_HDMI_DEEP_COLOR_OFF   = 0xff,
    HI_UNF_HDMI_DEEP_COLOR_BUTT
}HI_UNF_HDMI_DEEP_COLOR_E;

/**HDMI AVI InfoFrame colorimetry enum*//**CNcomment: HDMI AVI��Ϣ֡ ɫ�ȿռ� ö�� */
typedef enum hiUNF_HDMI_COLORSPACE_E
{
    HDMI_COLORIMETRY_NO_DATA,               /**<Colorimetry No Data option*//**<CNcomment:Colorimetry No Dataѡ�� */
    HDMI_COLORIMETRY_ITU601,                /**<Colorimetry ITU601 option*//**<CNcomment:Colorimetry ITU601ɫ�ȿռ�ѡ�� */
    HDMI_COLORIMETRY_ITU709,                /**<Colorimetry ITU709 option*//**<CNcomment:Colorimetry ITU709ɫ�ȿռ�ѡ�� */
    HDMI_COLORIMETRY_EXTENDED,              /**<Colorimetry extended option*//**<CNcomment:Colorimetry ��չѡ�� */
    HDMI_COLORIMETRY_XVYCC_601,             /**<Colorimetry xvYCC601 extened option*//**<CNcomment:Colorimetry xvYCC601��չѡ�� */
    HDMI_COLORIMETRY_XVYCC_709,             /**<Colorimetry xvYCC709 extened option*//**<CNcomment:Colorimetry xvYCC709��չѡ�� */
	HDMI_COLORIMETRY_S_YCC_601,             /**<Colorimetry S YCC 601 extened option*//**<CNcomment:Colorimetry S YCC 601��չѡ�� */
	HDMI_COLORIMETRY_ADOBE_YCC_601,         /**<Colorimetry ADOBE YCC 601 extened option*//**<CNcomment:Colorimetry ADOBE YCC 601��չѡ�� */
	HDMI_COLORIMETRY_ADOBE_RGB,             /**<Colorimetry ADOBE RGB extened option*//**<CNcomment:Colorimetry ADOBE RGB��չѡ�� */
	HDMI_COLORIMETRY_2020_CONST_LUMINOUS,    /**<Colorimetry ITU2020 extened option*//**<CNcomment:Colorimetry ITU2020��չѡ��:BT2020cYCC */
    HDMI_COLORIMETRY_2020_NON_CONST_LUMINOUS,/**<Colorimetry ITU2020 extened option*//**<CNcomment:Colorimetry ITU2020��չѡ��:BT2020RGB��BT2020YCC*/
}HI_UNF_HDMI_COLORSPACE_E;

/*HDMI Output Aspect Ratio*//**CNcomment:HDMI�����߱�*/
typedef enum hiUNF_HDMI_ASPECT_RATIO_E
{
    HI_UNF_HDMI_ASPECT_RATIO_NO_DATA,        /**<Aspect Ratio unknown *//**<CNcomment:δ֪��߱� */
    HI_UNF_HDMI_ASPECT_RATIO_4TO3,           /**<Aspect Ratio 4:3  *//**<CNcomment:��߱�4:3*/
    HI_UNF_HDMI_ASPECT_RATIO_16TO9,          /**<Aspect Ratio 16:9 *//**<CNcomment:��߱�16:9 */
    HI_UNF_HDMI_ASPECT_RATIO_FUTURE,
    HI_UNF_HDMI_ASPECT_RATIO_BUTT
}HI_UNF_HDMI_ASPECT_RATIO_E;

#if defined(HI_HDMI_SUPPORT_2_0)
/**the config parameter of HDMI interface*/
/**CNcomment:HDMI �ӿڲ������� */
typedef struct hiUNF_HDMI_ATTR_S
{
	HI_BOOL                  bEnableHdmi;         /**<force to HDMI or DVI,the value must set before HI_UNF_HDMI_Start or behind HI_UNF_HDMI_Stop*//**<CNcomment:�Ƿ�ǿ��HDMI,����ΪDVI.��ֵ������ HI_UNF_HDMI_Start֮ǰ����HI_UNF_HDMI_Stop֮������  */
   // HI_BOOL                  bEnableVideo;        /**<parameter must set HI_TRUE,or the HDMI diver will force to set HI_TRUE*//**<CNcomment:������HI_TRUE, �����HI_FALSE:HDMI������ǿ������ΪHI_TRUE */
  //  HI_BOOL                  bEnableAudio;        /**<Enable flag of Audio*//**CNcomment:�Ƿ�Enable��Ƶ */
    HI_U32                   u32DispFmt;         /**<video format*//**CNcomment:��Ƶ��ʽ */
    HI_UNF_HDMI_VIDEO_MODE_E enVidOutMode;       /**<HDMI output vedio mode VIDEO_MODE_YCBCR,VIDEO_MODE_YCBCR444,VIDEO_MODE_YCBCR422,VIDEO_MODE_RGB444 *//**<CNcomment:HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_VIDEO_MODE_E enVidInMode;        /**<HDMI input vedio mode VIDEO_MODE_YCBCR,VIDEO_MODE_YCBCR444,VIDEO_MODE_YCBCR422,VIDEO_MODE_RGB444 *//**<CNcomment:HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
}HI_UNF_HDMI_ATTR_S;
#endif

HI_S32 HI_UNF_HDMI_Init(HI_VOID);
HI_S32 HI_UNF_HDMI_DeInit(HI_VOID);
HI_S32 HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi);

#if defined(HI_HDMI_SUPPORT_2_0)
HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi);
HI_S32 HI_UNF_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr);
#else
HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi,HI_UNF_ENC_FMT_E enFormat);
HI_U32 HDMI_Display(HI_UNF_ENC_FMT_E enHdFmt, HI_UNF_HDMI_VIDEO_MODE_E einput, HI_UNF_HDMI_VIDEO_MODE_E eoutput);
#ifdef HI_HDMI_EDID_SUPPORT
HI_S32 HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_E enHdmi,HI_UNF_EDID_BASE_INFO_S *pSinkCap);
HI_S32 HI_UNF_HDMI_SetBaseParamByEDID(HI_VOID);
#endif
#endif



#endif
