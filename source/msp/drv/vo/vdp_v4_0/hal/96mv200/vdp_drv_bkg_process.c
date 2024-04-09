#include "vdp_drv_bkg_process.h"
#include "vdp_hal_comm.h"
#include "vdp_hal_ip_vdm.h"
#include "vdp_drv_ip_vdm.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_func_pq_csc.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "drv_pq_ext.h"

HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_U32 u32LayerId, HI_BOOL bRgbColorSpace)
{
    VDP_BKG_S  stLetterBoxColor = {0};

    stLetterBoxColor.u32BkgA = 0xff;
    if (bRgbColorSpace)
    {
        stLetterBoxColor.u32BkgY = 0x0;
        stLetterBoxColor.u32BkgU = 0x0;
        stLetterBoxColor.u32BkgV = 0x0;
    }
    else
    {
        stLetterBoxColor.u32BkgY = 0x40;
        stLetterBoxColor.u32BkgU = 0x200;
        stLetterBoxColor.u32BkgV = 0x200;
    }
    VDP_VID_SetLayerBkg(u32LayerId, stLetterBoxColor);
    return;
}

HI_VOID XDP_DRV_JudgeRgbColorSpace(VDP_CLR_SPACE_E enOutClrSpace, HI_BOOL *pbRgbColorSpace)
{
    if (enOutClrSpace == VDP_CLR_SPACE_RGB_601
        || enOutClrSpace == VDP_CLR_SPACE_RGB_709
        || enOutClrSpace == VDP_CLR_SPACE_RGB_2020
        || enOutClrSpace == VDP_CLR_SPACE_RGB_601_L
        || enOutClrSpace == VDP_CLR_SPACE_RGB_709_L
        || enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
       )
    {
        *pbRgbColorSpace = HI_TRUE;
    }
    else
    {
        *pbRgbColorSpace = HI_FALSE;
    }
    return;
}

HI_VOID XDP_DRV_AdjustMixvColor(VDP_BKG_S *pstMixvColor, HI_BOOL bRgbColorSpace)
{
    HI_S32 s32Red = 0, s32Y = 0;
    HI_S32 s32Green = 0, s32U = 0;
    HI_S32 s32Blue = 0, s32V = 0;

    s32Red = (HI_S32)pstMixvColor->u32BkgY;
    s32Green = (HI_S32)pstMixvColor->u32BkgU;
    s32Blue = (HI_S32)pstMixvColor->u32BkgV;

    if (bRgbColorSpace)
    {
        //8bit -> 10bit.
        pstMixvColor->u32BkgY = s32Red << 2;
        pstMixvColor->u32BkgU = s32Green << 2;
        pstMixvColor->u32BkgV = s32Blue << 2;
    }
    else
    {
        //change rgb to yuv.
        s32Y = (257 * s32Red  + 504 * s32Green  + 98 * s32Blue ) / 1000 + 16;
        s32U = (-148 * s32Red  - 291 * s32Green  + 439 * s32Blue ) / 1000 + 128;
        s32V = (439 * s32Red  - 368 * s32Green  - 71 * s32Blue ) / 1000 + 128;

        if (s32Y < 16)
        {
            s32Y = 16;
        }

        if (s32Y > 235)
        {
            s32Y = 235;
        }

        if (s32U < 16)
        {
            s32U = 16;
        }

        if (s32U > 240)
        {
            s32U = 240;
        }

        if (s32V < 16)
        {
            s32V = 16;
        }

        if (s32V > 240)
        {
            s32V = 240;
        }

        //8bit -> 10bit.
        pstMixvColor->u32BkgY = (HI_U32)s32Y << 2;
        pstMixvColor->u32BkgU = (HI_U32)s32U << 2;
        pstMixvColor->u32BkgV = (HI_U32)s32V << 2;
    }

    return ;
}
#endif
