#ifndef __DRV_CGMS_H__
#define __DRV_CGMS_H__


#include "hi_type.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "drv_disp_isr.h"
#endif

#include "drv_disp_hal.h"
#include "hi_drv_disp.h"

#define CgmsCheckNullPointer(ptr) \
    {                                \
        if (!ptr)                    \
        {                            \
            DISP_ERROR("DISP ERROR! Input null pointer in %s!\n", __FUNCTION__); \
            return HI_ERR_DISP_NULL_PTR;  \
        }                             \
    }

typedef struct hiDISP_CGMS_INFO_S
{
#ifndef __DISP_PLATFORM_BOOT__
    HI_BOOL bEnable;
    HI_DRV_DISPLAY_E enAttachedDisp;
    HI_DRV_DISP_CGMSA_TYPE_E  enType;
    HI_DRV_DISP_CGMSA_MODE_E  enMode;
    HI_DRV_DISP_FMT_E enCurFormat;
#endif
}DISP_CGMS_INFO_S;


typedef struct hiDISP_CGMS_STATE_S
{
#ifndef __DISP_PLATFORM_BOOT__
    HI_BOOL bEnable;
    HI_DRV_DISPLAY_E enAttachedDisp;
    HI_DRV_DISP_CGMSA_TYPE_E  enType;
    HI_DRV_DISP_CGMSA_MODE_E  enMode;
#endif
}DISP_CGMS_STATE_S;

typedef struct hiDISP_CGMS_FMT_CFG_s
{
    HI_DRV_DISP_FMT_E enFmt;
    HI_U32  au32CfgData[HI_DRV_DISP_CGMSA_MODE_BUTT];
} DISP_CGMS_FMT_CFG_s;


// Define the union U_ANALOG_CTRL, Get REE config from this REG
typedef union
{
    // Define the struct bits
    struct
    {
        unsigned int    cgms_en             : 1   ; // [0]
        unsigned int    cgms_type           : 3   ; // [3..1]
        unsigned int    cgms_mode           : 3   ; // [6..4]
        unsigned int    mcvn_en             : 1   ; // [7]
        unsigned int    mcvn_mode           : 4   ; // [11..8]
        unsigned int    disp0_fmt           : 7   ; // [18..12]
        unsigned int    disp1_fmt           : 7   ; // [25..19]
        unsigned int    sdate_attach        : 2   ; // [27..26]     0-no_attaching, 0x1-DISP0, 0x2-DISP1
        unsigned int    hdate_attach        : 2   ; // [29..28]     0-no_attaching, 0x1-DISP0, 0x2-DISP1
    } bits;

    // Define an unsigned member
    unsigned int    u32;

} U_ANALOG_CTRL;

//==============================================================================
/* Define the global struct */
typedef struct
{
    U_ANALOG_CTRL ANALOG_CTRL;
} S_VDP_COM_REGS_TYPE;

extern S_VDP_COM_REGS_TYPE *pVdpComReg;

#ifndef __DISP_PLATFORM_BOOT__

HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E enFmt, DISP_CGMS_INFO_S* pstCgms);

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms);

HI_S32 DRV_CGMS_Set(HI_DRV_DISP_FMT_E enSdateFmt, HI_DRV_DISP_FMT_E enHdateFmt, const HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg);

HI_S32 DRV_CGMS_Get(DISP_CGMS_STATE_S *pstCurState);
#endif

HI_VOID DRV_SetDateAttachToComReg(DISP_VENC_E enDate, HI_DRV_DISPLAY_E enDisp);

HI_VOID DRV_SetDispFmtToComReg(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E enFmt);

HI_VOID DRV_InitComReg(HI_VOID);

#endif
