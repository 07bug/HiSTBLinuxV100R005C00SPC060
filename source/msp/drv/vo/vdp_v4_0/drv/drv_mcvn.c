#include "drv_mcvn.h"
#include "drv_cgms.h"
#include "vdp_hal_comm.h"
#include "vdp_software_selfdefine.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
HI_S32 DRV_MCVN_SetDateMcvn(HI_DRV_DISP_FMT_E enFmt, HI_DRV_DISP_MACROVISION_E enMcvn);


static HI_U32 g_MacrovisionCoef[6][4][5]=
{
#if 0
    {
        {0x0,       0x0,      0x0,     0x0,       0x0},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10607efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10607efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10607efe,0x800aaf40}
    },    /*PAL  PAL_N  PAL_Nc */
#else
    // 2011.9.17 ange for zg by caobin, according to new macrovision standard
    {
        {0x0,       0x0,      0x0,     0x0,       0x0},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10407efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10607efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10507efe,0x800aaf40}
    },    /*PAL  PAL_N  PAL_Nc */

#endif

#if 0
    {
        {0x0,       0x0,      0x0,  0x0,       0x0},
        {0x46545d36,0x246db39,0x7f8,0x15600f0f,0x801ffc50},
        {0x46545d3e,0x246db39,0x7f8,0x15600f0f,0x801ffc50},
        {0x5615573e,0x246dbad,0x7f8,0x15500f0f,0x801ffc50}
    },    /*NTSC NTSC_J */
#else
    // 2011.9.17 ange for zg by caobin, according to new macrovision standard
    {
        {0x0,       0x0,      0x0,  0x0,       0x0},
        {0x46545d36,0x246db39,0x7f8,0x15400f0f,0x801ffc50},
        {0x46545d3e,0x246db39,0x7f8,0x15600f0f,0x801ffc50},
        {0x5615573e,0x246dbad,0x7f8,0x15500f0f,0x801ffc50}
    },    /*NTSC NTSC_J */

#endif

    {
        {0x0,       0x0,      0x0,  0x0,       0x0},
        {0x56155736,0x246dbad,0x7f8,0x15600f0f,0x801ffc50},
        {0x46545d36,0x246db39,0x7f8,0x15600f0f,0x801ffc50},
        {0x56155736,0x246dbad,0x7f8,0x15500f0f,0x801ffc50}
    },    /* NTSC_PAL_M*/

#if 0
    {
        {0x0,       0x0,      0x0,     0x0,   0x0       },
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10507efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10507efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10507efe,0x800aaf40}
    },    /*SECAM */
#else
    // 2011.9.17 ange for zg by caobin, according to new macrovision standard
    {
        {0x0,       0x0,      0x0,     0x0,   0x0       },
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10407efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10607efe,0x800aaf40},
        {0x8aa89a36,0x14f5c15,0xaa03fe,0x10407efe,0x800aaf40}
    },    /*SECAM SIN/COS */
#endif

    {
        {0x0,       0x0,      0x0,  0x0,       0x0     },
        {0x56155736,0x246dbad,0x7f8,0x15601e1e,0x1ffc50},
        {0x56155736,0x246dbad,0x7f8,0x15601e1e,0x1ffc50},
        {0x56155736,0x246dbad,0x7f8,0x15601e1e,0x1ffc50}
    },  /*PAL_60*/

    {
        {0x0,       0x0,      0x0,  0x0,       0x0     },
        {0x56155736,0x246dbad,0x7f8,0x15500f0f,0x1ffc50},
        {0x56155736,0x246dbad,0x7f8,0x15500f0f,0x1ffc50},
        {0x56155736,0x246dbad,0x7f8,0x15500f0f,0x1ffc50}
    },  /*NTSC_443*/


};

HI_S32 DRV_MCVN_Init(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_FMT_E enFmt)
{
    VDP_MVCN_SetMcvnEnable(HI_FALSE);

    DRV_MCVN_SetDateMcvn(enFmt, HI_DRV_DISP_MACROVISION_TYPE0);

    return HI_SUCCESS;
}

HI_S32 DRV_MCVN_DeInit(HI_DRV_DISPLAY_E enDisp)
{
    return HI_SUCCESS;
}

static HI_VOID DISP_SetMcvnCfgToComReg(HI_DRV_DISP_MACROVISION_E enMode)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));
    ANALOG_CTRL.bits.mcvn_mode  = enMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);

    return;
}

static HI_VOID DISP_GetMcvnCfgFromComReg(HI_DRV_DISP_MACROVISION_E *penMode)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));
    *penMode = ANALOG_CTRL.bits.mcvn_mode;

    return;
}

HI_S32 DRV_MCVN_GetDateMcvn(HI_DRV_DISP_MACROVISION_E* penMcvn)
{
    DISP_GetMcvnCfgFromComReg(penMcvn);

    return HI_SUCCESS;
}

HI_S32 DRV_MCVN_SetDateMcvn(HI_DRV_DISP_FMT_E enFmt, HI_DRV_DISP_MACROVISION_E enMcvn)
{
    HI_U32 *pu32McvnDate;

    switch (enFmt)
    {
        case HI_DRV_DISP_FMT_SECAM_COS:
        case HI_DRV_DISP_FMT_SECAM_SIN:

            pu32McvnDate = g_MacrovisionCoef[3][enMcvn];
            break;

        case HI_DRV_DISP_FMT_PAL_M:

            pu32McvnDate = g_MacrovisionCoef[2][enMcvn];
            break;

        case HI_DRV_DISP_FMT_NTSC:
        case HI_DRV_DISP_FMT_NTSC_J:

            pu32McvnDate = g_MacrovisionCoef[1][enMcvn];
            break;

        case HI_DRV_DISP_FMT_PAL:
        case HI_DRV_DISP_FMT_PAL_N:
        case HI_DRV_DISP_FMT_PAL_Nc:

            pu32McvnDate = g_MacrovisionCoef[0][enMcvn];
            break;

        default:
            pu32McvnDate = g_MacrovisionCoef[0][0];
            break;
    }

    SDATE_MVCN_DATE_SetMcvn(pu32McvnDate);

    return HI_SUCCESS;
}

HI_S32 DRV_MCVN_SetMacrovision(HI_DRV_DISP_MACROVISION_E enMode, HI_DRV_DISP_FMT_E enFmt)
{
    if (HI_DRV_DISP_MACROVISION_TYPE3  < enMode)
    {
        HI_ERR_DISP("DISP does not support the macrovision type!\n");
        return HI_ERR_DISP_INVALID_PARA;
    }

    /* Set Hdate macrovision */
    if(enMode == HI_DRV_DISP_MACROVISION_TYPE0)
    {
        VDP_MVCN_SetMcvnEnable(HI_FALSE);
    }
    else if(  (enMode >= HI_DRV_DISP_MACROVISION_TYPE1)
            &&(enMode <= HI_DRV_DISP_MACROVISION_TYPE3))
    {
        VDP_MVCN_SetMcvnEnable(HI_TRUE);
    }
    else
    {
        HI_ERR_DISP("HD DISP does not support the macrovision type!\n");
        return HI_ERR_DISP_INVALID_PARA;
    }

    /* Set Sdate macrovision */
    DRV_MCVN_SetDateMcvn(enFmt, enMode);

    DISP_SetMcvnCfgToComReg(enMode);

    return HI_SUCCESS;
}

HI_S32 DRV_MCVN_GetMacrovision(HI_DRV_DISP_MACROVISION_E *penMode)
{
    /* Get macrovision infomation from COM-Reg */
    DRV_MCVN_GetDateMcvn(penMode);

    if (*penMode >= HI_DRV_DISP_MACROVISION_BUTT)
    {
        HI_ERR_DISP("Mode=%d is out of range !\n", *penMode);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

