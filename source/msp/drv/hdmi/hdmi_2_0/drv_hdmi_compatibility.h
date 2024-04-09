#ifndef __DRV_HDMI_COMPATIBILITY_H__
#define __DRV_HDMI_COMPATIBILITY_H__

#include "drv_hdmi_common.h"
#include "drv_hdmi_intf.h"

typedef struct
{
    HI_U32  u32CrgDivMs;
    HI_U32  u32PhySrstMs;
}COMPAT_CRG_SRST_S;

HI_BOOL DRV_HDMI_CompatCecValidCheck(HDMI_DEVICE_S *pstHdmiDev);
HI_S32  DRV_HDMI_CompatHdcpMsGet(HDMI_DEVICE_ID_E enHdmiId,HI_U64 *pu64WaitMs);
HI_S32  DRV_HDMI_CompatAvmuteGet(HDMI_DEVICE_ID_E enHdmiId,HI_BOOL bAvmute,HDMI_AVMUTE_CFG_S *pstAvmuteCfg);
HI_S32  DRV_HDMI_CompatCrgMsGet(HDMI_DEVICE_ID_E enHdmiId,HI_U32 *pu32CrgDivMs,HI_U32 *pu32PhySrstMs);
HI_BOOL DRV_HDMI_CompatScdcInStartGet(HDMI_DEVICE_ID_E enHdmiId);
HI_S32  DRV_HDMI_CompatAudNCtsGet(HDMI_DEVICE_ID_E enHdmiId, HI_U32 *pu32NValue, HI_U32 *pu32CtsValue);
HI_BOOL DRV_HDMI_CompatCecMapPlaydev(HDMI_DEVICE_ID_E enHdmiId);
HI_S32  DRV_HDMI_CompatDelayGet(HDMI_DEVICE_ID_E enHdmiId, HDMI_DELAY_S *pstDelay);
HI_S32  DRV_HDMI_CompatStopDelay(HDMI_DEVICE_ID_E enHdmiId);
HI_S32  DRV_HDMI_CompatHpdFillterGet(HDMI_DEVICE_ID_E enHdmiId,HDMI_HPD_FILLTER_S *pstHpdCfg);

#endif //__DRV_HDMI_COMPATIBILITY_H__