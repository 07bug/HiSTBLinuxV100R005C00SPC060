#include "hi_drv_hdmi.h"

typedef struct hiHDMI_DELAY_TIME_S{
    HI_U8           u8IDManufactureName[4];   /**<Manufacture name*//**<CNcomment:设备厂商标识 */
    HI_U32          u32IDProductCode;         /**<Product code*//**<CNcomment:设备ID */
    HI_U32          u32DelayTimes;            
    HI_U32          u32MuteDelay;
    HI_U8           u8ProductType[32];    /**<Product Type*//**<CNcomment:产品型号 */
}HDMI_DELAY_TIME_S;

#define HDMI_EDID_MAX_SINKNAME_COUNT        14

/**EDID MANUFACTURE information */
typedef struct
{
    HI_U8               u8MfrsName[4];
    HI_U32              u32ProductCode;
    HI_U32              u32SerialNumber;
    HI_U32              u32Week;
    HI_U32              u32Year;
    HI_U8               u8pSinkName[HDMI_EDID_MAX_SINKNAME_COUNT];
}HDMI_EDID_MANUFACTURE_INFO_S;

typedef struct
{
    HDMI_EDID_MANUFACTURE_INFO_S stEdid;
    HI_U32                       u32StopDelay;
}COMPAT_SINK_STOPDELAY_S;


HI_S32 GetFormatDelay(HI_UNF_HDMI_ID_E enHdmi,HI_U32 *DelayTime);
HI_S32 GetmuteDelay(HI_UNF_HDMI_ID_E enHdmi,HI_U32 *DelayTime);


void SetGlobalFmtDelay(HI_U32 Delay);
HI_U32 GetGlobalFmtDelay(void);
void SetForceDelayMode(HI_BOOL bforceFmtDelay,HI_BOOL bforceMuteDelay);
HI_BOOL IsForceFmtDelay(void);
HI_BOOL IsForceMuteDelay(void);


void SetGlobalMuteDelay(HI_U32 Delay);
HI_U32 GetGlobalsMuteDelay(void);


void Check1stOE(HI_UNF_HDMI_ID_E enHdmi);

HI_BOOL Is3716Cv200ECVer(void);
HI_S32  DRV_HDMI_CompatStopDelay(HI_UNF_HDMI_ID_E enHdmiId);



