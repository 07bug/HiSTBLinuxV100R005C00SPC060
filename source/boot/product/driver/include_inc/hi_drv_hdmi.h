/***********************************************************************************/
#ifndef __BOOT_DRV_HDMI_EXT_H__
#define __BOOT_DRV_HDMI_EXT_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

//#include "hi_unf_disp.h"
//#include "de.h"
#include "hi_common.h"
#include "hi_type.h"
#include "exports.h"
#include "hi_unf_hdmi.h"
#include "hi_drv_disp.h"

#if defined(HI_HDMI_SUPPORT_2_0)
/**the config parameter of HDMI interface*/
/**CNcomment:HDMI �ӿڲ������� */
typedef struct 
{
	HI_BOOL                  bEnableHdmi;         /**<force to HDMI or DVI,the value must set before HI_UNF_HDMI_Start or behind HI_UNF_HDMI_Stop*//**<CNcomment:�Ƿ�ǿ��HDMI,����ΪDVI.��ֵ������ HI_UNF_HDMI_Start֮ǰ����HI_UNF_HDMI_Stop֮������  */
    //HI_BOOL                  bEnableVideo;        /**<parameter must set HI_TRUE,or the HDMI diver will force to set HI_TRUE*//**<CNcomment:������HI_TRUE, �����HI_FALSE:HDMI������ǿ������ΪHI_TRUE */
    //HI_BOOL                  bEnableAudio;        /**<Enable flag of Audio*//**CNcomment:�Ƿ�Enable��Ƶ */
    HI_BOOL                  bVSyncPol;                  /**CNcomment: �����ֱ���Է������ */
    HI_BOOL                  bHSyncPol;                  /**CNcomment: ���ˮƽ���Է������ */
    HI_BOOL                  bDEPol;                     /**CNcomment: ������ݼ��Է������ */
    HI_U32                   u32DispFmt;         /**<video format*//**CNcomment:��Ƶ��ʽ */
    HI_U32                   u32ClkFs;
    HI_UNF_HDMI_VIDEO_MODE_E enVidOutMode;       /**<HDMI output vedio mode VIDEO_MODE_YCBCR,VIDEO_MODE_YCBCR444,VIDEO_MODE_YCBCR422,VIDEO_MODE_RGB444 *//**<CNcomment:HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_VIDEO_MODE_E enVidInMode;        /**<HDMI input vedio mode VIDEO_MODE_YCBCR,VIDEO_MODE_YCBCR444,VIDEO_MODE_YCBCR422,VIDEO_MODE_RGB444 *//**<CNcomment:HDMI�����Ƶģʽ��VIDEO_MODE_YCBCR444��VIDEO_MODE_YCBCR422��VIDEO_MODE_RGB444 */
    HI_UNF_HDMI_DEEP_COLOR_E enDeepColor;
}HI_DRV_HDMI_ATTR_S;
#endif



HI_S32 HI_DRV_HDMI_Init(void);
HI_S32 HI_DRV_HDMI_DeInit(void);
    
#if defined(HI_HDMI_SUPPORT_2_0)
HI_S32 HI_DRV_HDMI_Open(HI_UNF_HDMI_ID_E enHdmiID);
HI_S32 HI_DRV_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmiID, HI_DRV_HDMI_ATTR_S *pstAttr);
HI_S32 HI_DRV_HDMI_Start(HI_UNF_HDMI_ID_E enHdmiID);
HI_S32 HI_DRV_HDMI_Close(HI_UNF_HDMI_ID_E enHdmiID);
#else
HI_S32 HI_DRV_HDMI_Open(HI_DRV_DISP_FMT_E enFormat);
HI_S32 HI_DRV_HDMI_Start(void);
HI_S32 HI_DRV_HDMI_Close(void);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif

