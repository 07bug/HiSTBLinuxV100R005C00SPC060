
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_hal.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "drv_disp_com.h"
#include "drv_disp_hal.h"
#include "drv_disp_osal.h"
#include "drv_disp_da.h"
#ifndef __DISP_PLATFORM_BOOT__
#include "hi_drv_sys.h"
#endif

#include "drv_disp_hal_adp.h"
#include "hi_reg_common.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*==========================================
     VDP / SYS / VDAC phy-address
*/
/*==========================================
     HAL global parameters
*/
HI_U32 s_u32VdpBaseAddr  = 0;
static HI_S32 s_DispIntfFlag = 0;
static DISP_CAPA_S s_stDispCapability[HI_DRV_DISPLAY_BUTT];
static DISP_CH_CFG_S s_stDispConfig[HI_DRV_DISPLAY_BUTT];

static HI_DRV_DISP_VERSION_S s_stVersion = {0};
static DISP_INTF_OPERATION_S s_stIntfOps = {0};

/*==========================================
    HAL module
*/
static DISP_LOCAL_INTF_S s_stHalIntf[HI_DRV_DISP_INTF_ID_MAX];
//static DISP_LOCAL_VDAC_S s_stHalVEnc[DISP_VENC_MAX];
static DISP_LOCAL_VDAC_S s_stHalVDac[HI_DISP_VDAC_MAX_NUMBER];
static DISP_LOCAL_WBC_S  s_stWBC[DISP_WBC_BUTT];
static HI_DRV_VDAC_ATTR_S g_stVDACAttr;

#define DISP_CLOCK_SOURCE_SD0  0
#define DISP_CLOCK_SOURCE_HD0  1
#define DISP_CLOCK_SOURCE_HD1  2
DISP_MMZ_BUF_S   g_RegBackBuf;

static HI_S32 HAL_Set3DMode(HI_DRV_DISPLAY_E eChn,HI_U32 u32DispId, DISP_FMT_CFG_S *pstCfg)
{
    return Chip_Specific_Set3DMode(eChn, u32DispId, pstCfg);
}

HI_S32 DispHalGetEnFmtIndex(HI_DRV_DISP_FMT_E eFmt)
{
    switch (eFmt)
    {
        case HI_DRV_DISP_FMT_1080P_60:
            return 1;
        case HI_DRV_DISP_FMT_1080P_50:
            return 2;
        case HI_DRV_DISP_FMT_1080P_30:
            return 3;
        case HI_DRV_DISP_FMT_1080P_25:
            return 4;
        case HI_DRV_DISP_FMT_1080P_24:
            return 5;
        case HI_DRV_DISP_FMT_1080i_60:
            return 6;
        case HI_DRV_DISP_FMT_1080i_50:
            return 7;
        case HI_DRV_DISP_FMT_720P_60:
            return 8;
        case HI_DRV_DISP_FMT_720P_50:
            return 9;
        case HI_DRV_DISP_FMT_576P_50:
            return 10;
        case HI_DRV_DISP_FMT_480P_60:
            return 11;
        case HI_DRV_DISP_FMT_PAL:
        case HI_DRV_DISP_FMT_PAL_B:
        case HI_DRV_DISP_FMT_PAL_B1:
        case HI_DRV_DISP_FMT_PAL_D:
        case HI_DRV_DISP_FMT_PAL_D1:
        case HI_DRV_DISP_FMT_PAL_G:
        case HI_DRV_DISP_FMT_PAL_H:
        case HI_DRV_DISP_FMT_PAL_K:
        case HI_DRV_DISP_FMT_PAL_I:
        case HI_DRV_DISP_FMT_PAL_N:
        case HI_DRV_DISP_FMT_PAL_Nc:
        case HI_DRV_DISP_FMT_SECAM_SIN:
        case HI_DRV_DISP_FMT_SECAM_COS:
        case HI_DRV_DISP_FMT_SECAM_L:
        case HI_DRV_DISP_FMT_SECAM_B:
        case HI_DRV_DISP_FMT_SECAM_G:
        case HI_DRV_DISP_FMT_SECAM_D:
        case HI_DRV_DISP_FMT_SECAM_K:
        case HI_DRV_DISP_FMT_SECAM_H:
            return 12;


        case HI_DRV_DISP_FMT_PAL_M:
        case HI_DRV_DISP_FMT_PAL_60:
        case HI_DRV_DISP_FMT_NTSC:
        case HI_DRV_DISP_FMT_NTSC_J:
        case HI_DRV_DISP_FMT_NTSC_443:
            return 13;
        case HI_DRV_DISP_FMT_861D_640X480_60:
        case HI_DRV_DISP_FMT_VESA_800X600_60:
        case HI_DRV_DISP_FMT_VESA_1024X768_60:
        case HI_DRV_DISP_FMT_VESA_1280X720_60:
        case HI_DRV_DISP_FMT_VESA_1280X800_60:
        case HI_DRV_DISP_FMT_VESA_1280X1024_60:
        case HI_DRV_DISP_FMT_VESA_1360X768_60:
        case HI_DRV_DISP_FMT_VESA_1366X768_60:
        case HI_DRV_DISP_FMT_VESA_1400X1050_60:
        case HI_DRV_DISP_FMT_VESA_1440X900_60:
        case HI_DRV_DISP_FMT_VESA_1440X900_60_RB:
        case HI_DRV_DISP_FMT_VESA_1600X900_60_RB:
        case HI_DRV_DISP_FMT_VESA_1600X1200_60:
        case HI_DRV_DISP_FMT_VESA_1680X1050_60: /*27*/
        case HI_DRV_DISP_FMT_VESA_1680X1050_60_RB:      /*28*/
        case HI_DRV_DISP_FMT_VESA_1920X1080_60: /*29*/
        case HI_DRV_DISP_FMT_VESA_1920X1200_60: /*30*/
        case HI_DRV_DISP_FMT_VESA_1920X1440_60:  /*31*/
        case HI_DRV_DISP_FMT_VESA_2048X1152_60:/*32*/
        case HI_DRV_DISP_FMT_VESA_2560X1440_60_RB:/*33*/
        case HI_DRV_DISP_FMT_VESA_2560X1600_60_RB:/*34*/
            return (14 + eFmt - HI_DRV_DISP_FMT_861D_640X480_60);

        case HI_DRV_DISP_FMT_1080P_24_FP:
            return 36;
        case HI_DRV_DISP_FMT_720P_60_FP:
            return 37;
        case HI_DRV_DISP_FMT_720P_50_FP:
            return 38;
        case HI_DRV_DISP_FMT_1440x576i_50:
            return 39;
        case HI_DRV_DISP_FMT_1440x480i_60:
            return 40;
        case HI_DRV_DISP_FMT_3840X2160_24:
        return 41;
        case HI_DRV_DISP_FMT_3840X2160_25:
        return 42;
        case HI_DRV_DISP_FMT_3840X2160_30:
        return 43;
		case HI_DRV_DISP_FMT_3840X2160_50:
        return 44;
		case HI_DRV_DISP_FMT_3840X2160_60:
        return 45;

		case HI_DRV_DISP_FMT_4096X2160_24:
        return 46;
        case HI_DRV_DISP_FMT_4096X2160_25:
        return 47;
        case HI_DRV_DISP_FMT_4096X2160_30:
        return 48;
		case HI_DRV_DISP_FMT_4096X2160_50:
        return 49;
		case HI_DRV_DISP_FMT_4096X2160_60:
        return 50;

        case HI_DRV_DISP_FMT_3840X2160_23_976:
            return 51;
        case HI_DRV_DISP_FMT_3840X2160_29_97:
            return 52;
        case HI_DRV_DISP_FMT_720P_59_94:
            return 53;
        case HI_DRV_DISP_FMT_1080P_59_94:
            return 54;
        case HI_DRV_DISP_FMT_1080P_29_97:
            return 55;
        case HI_DRV_DISP_FMT_1080P_23_976:
            return 56;
        case HI_DRV_DISP_FMT_1080i_59_94:
            return 57;
        default :
            return 0;
    }

    return 0;
}


/********************************************/
/* usual */
HI_S32 DISP_HAL_GetFmtAspectRatio(HI_DRV_DISP_FMT_E eFmt, HI_U32 *pH, HI_U32 *pV)
{
    HI_S32 index;
    DISP_FMT_CFG_S stDispFormatParam;

    index = DispHalGetEnFmtIndex(eFmt);
    if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stDispFormatParam))
        return HI_FAILURE;

    *pH = stDispFormatParam.stInfo.stAR.u32ARw;
    *pV = stDispFormatParam.stInfo.stAR.u32ARh;

    return HI_SUCCESS;
}

HI_S32 DISP_HAL_GetFmtColorSpace(HI_DRV_DISP_FMT_E eFmt, HI_DRV_COLOR_SPACE_E  *penColorSpace)
{
    HI_S32 index;
    DISP_FMT_CFG_S stDispFormatParam;

    index = DispHalGetEnFmtIndex(eFmt);
    if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stDispFormatParam))
        return HI_FAILURE;

    *penColorSpace = stDispFormatParam.stInfo.enColorSpace;

    return HI_SUCCESS;
}

HI_S32 DISP_HAL_GetEncFmtPara(HI_DRV_DISP_FMT_E eFmt, DISP_HAL_ENCFMT_PARAM_S *pstFmtPara)
{
    HI_S32 index;
    DISP_FMT_CFG_S stDispFormatParam;

    index = DispHalGetEnFmtIndex(eFmt);
    if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stDispFormatParam))
        return HI_FAILURE;

    *pstFmtPara = stDispFormatParam.stInfo;
    return HI_SUCCESS;
}

VDP_CBM_MIX_E DISP_HAL_GetMixID(HI_DRV_DISPLAY_E eChn)
{
    switch(eChn)
    {
        case HI_DRV_DISPLAY_0:
            return VDP_CBM_MIX1;
        case HI_DRV_DISPLAY_1:
            return VDP_CBM_MIX0;
        default :
            return VDP_CBM_MIX0;
    }
}

HI_U32 DISP_HAL_GetChID(HI_DRV_DISPLAY_E eChn)
{
    switch(eChn)
    {
        case HI_DRV_DISPLAY_0:
            return 1;
        case HI_DRV_DISPLAY_1:
            return 0;
        default :
            return 0;
    }
}


/*
HI_S32 DISP_HAL_GetPll(HI_DRV_DISP_FMT_E eFmt, HI_U32 *pLow, HI_U32 *pHigh)
{
    *pLow  = s_u32PllConfig[DispHalGetEnFmtIndex(eFmt)][0];
    *pHigh = s_u32PllConfig[DispHalGetEnFmtIndex(eFmt)][1];
    return HI_SUCCESS;
}
*/


/********************************************/
HI_VOID DISP_HAL_ResetDispState(HI_VOID);
HI_VOID DISP_HAL_ResetIntfState(HI_VOID);
HI_VOID DISP_HAL_ResetVDacState(HI_VOID);
HI_VOID InitWbcState(HI_VOID);

HI_S32 DISP_HAL_InitVDPState(HI_VOID)
{
    /*set the virtual addr of vdp base register.*/
    VDP_DRIVER_SetVirtualAddr(s_u32VdpBaseAddr);

    /*reset the disp/interface/vdac status.*/
    DISP_HAL_ResetDispState();
    DISP_HAL_ResetIntfState();
    DISP_HAL_ResetVDacState();

    InitWbcState();
    return HI_SUCCESS;
}

HI_S32 PF_ResetVdpHardware(HI_VOID)
{
#if 0
    HI_U32 v;

    // init sysreg
    v = g_pstRegCrg->PERI_CRG54.u32;

    g_pstRegCrg->PERI_CRG54.u32 = 0;
    g_pstRegCrg->PERI_CRG54.u32 = DISP_CV200_ES_SYSCTRL_RESET_VALUE | DISP_CV200_ES_SYSCTRL_RESET_BIT;

    DISP_MSLEEP(5);

    g_pstRegCrg->PERI_CRG54.u32 = DISP_CV200_ES_SYSCTRL_RESET_VALUE;
#else
    DISP_ResetCRG();
#endif

    // init vdp
    VDP_DRIVER_Initial();

    // init vdac
    //VDAC_DRIVER_Initial();
    VDP_VDAC_Reset();

    return HI_SUCCESS;
}

HI_S32 PF_CloseClkResetModule(HI_VOID)
{
    VDP_CloseClkResetModule();
    return HI_SUCCESS;
}

/********************************************/
/* Display config */
#define DISP_HAL_FUNCTION_START_HAERE
HI_VOID DISP_HAL_ResetDispState(HI_VOID)
{
    memset(s_stDispCapability, 0, sizeof(s_stDispCapability));

    s_stDispCapability[HI_DRV_DISPLAY_0].bSupport = HI_TRUE;
    s_stDispCapability[HI_DRV_DISPLAY_0].bHD      = HI_TRUE;
    s_stDispCapability[HI_DRV_DISPLAY_0].bWbc    = HI_FALSE;

    s_stDispCapability[HI_DRV_DISPLAY_1].bSupport = HI_TRUE;
    s_stDispCapability[HI_DRV_DISPLAY_1].bHD      = HI_TRUE;
    s_stDispCapability[HI_DRV_DISPLAY_1].bWbc     = HI_TRUE;

    s_stDispCapability[HI_DRV_DISPLAY_2].bSupport = HI_FALSE;


    memset(s_stDispConfig, 0, sizeof(s_stDispConfig));


    return;
}

HI_BOOL PF_TestChnSupport(HI_DRV_DISPLAY_E eChn)
{

    return s_stDispCapability[eChn].bSupport;
}


HI_BOOL PF_TestChnSupportHD(HI_DRV_DISPLAY_E eChn)
{

    return s_stDispCapability[eChn].bHD;
}

HI_BOOL PF_TestChnSupportCast(HI_DRV_DISPLAY_E eChn)
{

    return s_stDispCapability[eChn].bWbc;
}

HI_BOOL PF_TestIntfSupport(HI_DRV_DISPLAY_E eChn, HI_DRV_DISP_INTF_ID_E eIntf)
{
    if (HI_DRV_DISPLAY_0 == eChn)
    {
        if (  (HI_DRV_DISP_INTF_SVIDEO0 == eIntf)
            ||(HI_DRV_DISP_INTF_CVBS0   == eIntf)
            ||(HI_DRV_DISP_INTF_RGB0    == eIntf)
            ||(HI_DRV_DISP_INTF_HDMI0  == eIntf)
            ||(HI_DRV_DISP_INTF_VGA0    == eIntf)
            ||(HI_DRV_DISP_INTF_YPBPR0 == eIntf)
            )
        {
            return HI_TRUE;
        }
    }

    if (HI_DRV_DISPLAY_1 == eChn)
    {
        if (  (HI_DRV_DISP_INTF_YPBPR0 == eIntf)
            ||(HI_DRV_DISP_INTF_HDMI0  == eIntf)
            ||(HI_DRV_DISP_INTF_VGA0   == eIntf)
            ||(HI_DRV_DISP_INTF_RGB0    == eIntf)
            ||(HI_DRV_DISP_INTF_LCD0   == eIntf)
            ||(HI_DRV_DISP_INTF_BT1120_0== eIntf)
            )
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}
HI_BOOL DISP_HAL_IS_4K(HI_DRV_DISP_FMT_E eFmt)
{
	if ((eFmt >= HI_DRV_DISP_FMT_3840X2160_24) && (eFmt <= HI_DRV_DISP_FMT_3840X2160_29_97))
		return HI_TRUE;
	else
		return HI_FALSE;
}

HI_BOOL PF_TestChnEncFmt(HI_DRV_DISPLAY_E eChn, HI_DRV_DISP_FMT_E eFmt)
{
    HI_CHIP_TYPE_E enChipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E enChipVersion = HI_CHIP_VERSION_BUTT;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);
    if (enChipType == HI_CHIP_TYPE_HI3796C
        || enChipType == HI_CHIP_TYPE_HI3796C_A
        || enChipType == HI_CHIP_TYPE_HI3798C
        || enChipType == HI_CHIP_TYPE_HI3798C_A
        || enChipType == HI_CHIP_TYPE_HI3798C_B
        || enChipType == HI_CHIP_TYPE_HI3798M
        || enChipType == HI_CHIP_TYPE_HI3798M_A
        || enChipType == HI_CHIP_TYPE_HI3796M)
    {
		//DISP_ERROR("chip 96cm 98cm suport 4k \n");
        if (eFmt <= HI_DRV_DISP_FMT_CUSTOM)
        {
            return HI_TRUE;
        }
    }
    else
    {

        if ((eFmt <= HI_DRV_DISP_FMT_CUSTOM))
        {
			/*not support 4K*/
			if (HI_TRUE == DISP_HAL_IS_4K(eFmt))
			{
				//DISP_ERROR("suport 4k (%d)\n",enChipType);
				return HI_FALSE;
			}
			else
			{
				//DISP_ERROR("suport 4k (%d)\n",enChipType);
				return HI_TRUE;
			}
        }
    }

    return HI_FALSE;

}

HI_BOOL PF_TestChnAttach(HI_DRV_DISPLAY_E enM, HI_DRV_DISPLAY_E enS)
{
    if( (enM != HI_DRV_DISPLAY_1) || (enS != HI_DRV_DISPLAY_0))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}






    // bypass and power down

    // config div para

    // power up


HI_S32 PF_ResetChn(HI_U32 u32DispId, HI_U32 bIntMode)
{
    VDP_DISP_CLIP_S stClipData;
    //HI_U32 u32DispId = DISP_HAL_GetChID(eChn);

    // s1 set dhd
    VDP_DHD_Reset(u32DispId);

    VDP_DISP_SetVtThdMode(u32DispId, 1, bIntMode);
    VDP_DISP_SetVtThdMode(u32DispId, 2, bIntMode);
    VDP_DISP_SetVtThdMode(u32DispId, 3, bIntMode);

    VDP_DISP_SetCscEnable(u32DispId, 0);

    // s2 set clip

    stClipData.bClipEn = 1;
    stClipData.u32ClipLow_y  = 0;
    stClipData.u32ClipLow_cb = 0;
    stClipData.u32ClipLow_cr = 0;

    stClipData.u32ClipHigh_y  = 1023;
    stClipData.u32ClipHigh_cb = 1023;
    stClipData.u32ClipHigh_cr = 1023;

    VDP_DISP_SetClipCoef(u32DispId, VDP_DISP_INTF_LCD, stClipData);
    VDP_DISP_SetClipCoef(u32DispId, VDP_DISP_INTF_BT1120, stClipData);
    VDP_DISP_SetClipCoef(u32DispId, VDP_DISP_INTF_HDMI, stClipData);
    VDP_DISP_SetClipCoef(u32DispId, VDP_DISP_INTF_VGA, stClipData);

    stClipData.u32ClipLow_y  = 64;
    stClipData.u32ClipLow_cb = 64;
    stClipData.u32ClipLow_cr = 64;
    VDP_DISP_SetClipCoef(u32DispId, VDP_DISP_INTF_DATE, stClipData);

    VDP_DISP_SetRegUp(u32DispId);

    return HI_SUCCESS;
}

HI_S32 PF_ConfigChn(HI_DRV_DISPLAY_E eChn, DISP_CH_CFG_S *pstCfg)
{
    //HI_U32 u32DispId = DISP_HAL_GetChID(eChn);

    return HI_SUCCESS;
}


#define DISP_VTTHD_VIDEO_OFFSET 0
#define DISP_VTTHD_GFX_OFFSET 80
#define DISP_VTTHD_DISP0_TO_DISP1 32
/*to caculte when an interrupt occurs, can gfx write operation
 *can neither cover the reading buffer, nor miss the next updating chance.
 */
HI_S32 DISP_GFX_GetIsrPoint(HI_U32 u32DispId, DISP_FMT_CFG_S *pstCfg)
{
    HI_U32 u32PeriodMs = 0;
    HI_U32 u32TotalLines = 0;
    HI_U32 u32ThreshHoldLine = 0;

    /*Generate time cost for every period in MicroSeconds.*/
    if ((0 == pstCfg->stInfo.u32RefreshRate)
        || (100000 < pstCfg->stInfo.u32RefreshRate))
    {
        DISP_ERROR("Denominator may be zero !\n");
        return 0;
    }
    u32PeriodMs = 100000/pstCfg->stInfo.u32RefreshRate;

    if (pstCfg->stInfo.eDispMode == DISP_STEREO_FPK)
    {
        /*
           ||<--------- FRRAME L--------->||<--------- FRRAME R--------->||
           -----------------------------------------------------------------
           | VFB0 || VBB0 |     VACT0     | VFB0 || VBB01 |     VACT1    |
           -----------------------------------------------------------------
                                            |<----------->|
                                             Pos2    ^
                                                    /|\
                                                     |
                                               Here equal to 'DISP_VTTHD_GFX_OFFSET'
        */

        u32TotalLines = (pstCfg->stTiming.u32Vbb
                         + pstCfg->stTiming.u32Vfb
                         + pstCfg->stTiming.u32Vact
                         + pstCfg->stTiming.u32Bvact
                         + pstCfg->stTiming.u32Bvbb
                         + pstCfg->stTiming.u32Bvfb);
    }
    else
    {
        /*
           ||<--------- FRRAME 1--------->||<--------- FRRAME 2------->||
           --------------------------------------------------------------
           | VFB1 || VBB1 |     VACT1     | VFB2 || VBB2 |     VACT1    |
           --------------------------------------------------------------
                                            |<----------->|
                                             Pos2    ^
                                                    /|\
                                                     |
                                               Here equal to 'DISP_VTTHD_GFX_OFFSET'
        */

        u32TotalLines = (pstCfg->stTiming.u32Vbb + pstCfg->stTiming.u32Vfb + pstCfg->stTiming.u32Vact);
    }

    /*hd channel*/
    if (u32DispId == 0)
    {
        /*we set the theshhold for 1.5ms, so we can get the u32ThreshHoldLine.*/
        u32ThreshHoldLine = (2*u32TotalLines)/(u32PeriodMs);
    }
    else/*sd channel*/
    {
        /*we set the theshhold for 1.5ms, so we can get the u32ThreshHoldLine.*/
        u32ThreshHoldLine = (7*u32TotalLines)/(4*u32PeriodMs);
    }

    /*To avoid the isr configure missing the update point in vbb in next ISR period,
     *we should consider this.
     */
    u32ThreshHoldLine -= pstCfg->stTiming.u32Vfb;

    /*so the final isr point is as follows*/
    if ((HI_S32)(u32TotalLines - u32ThreshHoldLine) < 0)
    {
        return 0;
    }
	
    return u32TotalLines - u32ThreshHoldLine;
}

HI_U32 DISP_GFX_GetIsrPoint1(HI_U32 u32DispId, DISP_FMT_CFG_S *pstCfg)
{
    HI_U32 u32TotalLines = 0;

    if (pstCfg->stInfo.eDispMode == DISP_STEREO_FPK)
    {
        u32TotalLines = (pstCfg->stTiming.u32Vbb
                         + pstCfg->stTiming.u32Vfb
                         + pstCfg->stTiming.u32Vact
                         + pstCfg->stTiming.u32Bvact
                         + pstCfg->stTiming.u32Bvbb
                         + pstCfg->stTiming.u32Bvfb);
    }
    else
    {
        u32TotalLines = (pstCfg->stTiming.u32Vbb + pstCfg->stTiming.u32Vfb + pstCfg->stTiming.u32Vact);
    }

    return u32TotalLines - 5;
}

HI_S32 PF_SetChnBaseTiming(HI_DRV_DISPLAY_E eChn, DISP_FMT_CFG_S *pstCfg)
{
    HI_S32 thd;
    VDP_DISP_RECT_S DispRect;
    VDP_LAYER_VP_E vdp_layer;
    HI_U32 u32DispId = DISP_HAL_GetChID(eChn);

    DISP_PRINT(">>>>>>>>>>>>>>>u32DispId=%d>>> (%d)(%d)\n",u32DispId, pstCfg->stTiming.u32Vact,pstCfg->stTiming.u32Hact);

    if(pstCfg->stInfo.eDispMode == DISP_STEREO_FPK)
        PF_ResetChn(u32DispId, DHD_VTXTHD_FRAME_MODE);
    else
        PF_ResetChn(u32DispId, DHD_VTXTHD_FIELD_MODE);

    (HI_VOID)HAL_Set3DMode(eChn, u32DispId, pstCfg);
    // set dhd
    /*
      timing is like that:

      ||<--------- FRRAME 0--------->||<--------- FRRAME 1--------->||
      -----------------------------------------------------------------
      || VBB0 |     VACT0     | VFB0 || VBB01 |     VACT1    | VFB1 ||
      -----------------------------------------------------------------
                              ^
                             /|\
                              |
                NOTICE: The 'thd' is start here, NOT between VFB0 and VBB1.
                        That means here thd is '0'.
    */
    /*
      ||<--------- FRRAME 0--------->||<--------- FRRAME 1--------->||
      -----------------------------------------------------------------
      || VBB0 |     VACT0     | VFB0 || VBB01 |     VACT1    | VFB1 ||
      -----------------------------------------------------------------
                              |---------------|<----->|
                                                  ^   Pos1
                                                 /|\
                                                  |
                                         Here equal to 'DISP_VTTHD_VIDEO_OFFSET'
                                         And Pos1 is thd1
    */

    VDP_DISP_SetTiming(u32DispId, &(pstCfg->stTiming));

    /*here we turn on p2i according the fmt is interleave or not.*/
    if (pstCfg->stTiming.bIop)
    {
        VDP_DISP_SetProToInterEnable(u32DispId,0);
    }
    else
    {
        VDP_DISP_SetProToInterEnable(u32DispId,1);
    }


    if (pstCfg->stInfo.eDispMode == DISP_STEREO_FPK)
    {
        thd = (pstCfg->stTiming.u32Vfb + pstCfg->stTiming.u32Vbb)*2 +
                pstCfg->stTiming.u32Vact + DISP_VTTHD_VIDEO_OFFSET;

        if (u32DispId == 1)
        {
            thd = thd + DISP_VTTHD_DISP0_TO_DISP1;
        }

        VDP_DISP_SetVtThd(u32DispId, 1, (HI_U32)thd);
		/*
              ||<--------- FRRAME L--------->||<--------- FRRAME R--------->||
              -----------------------------------------------------------------
       | VFB0 || VBB0 |     VACT0     | VFB0 || VBB01 |     VACT1    | VFB1 ||
              -----------------------------------------------------------------
                                        |<----------->|
                                       Pos2    ^
                                              /|\
                                               |
                                         Here equal to 'DISP_VTTHD_GFX_OFFSET'
                                         Pos2 is thd2.
                                         If DISP_VTTHD_GFX_OFFSET is bigger tha (VFB0+VBB1),
                                         Pos2 is in VACT0.
            */
        thd = DISP_GFX_GetIsrPoint(u32DispId, pstCfg);
		if (thd < 0)
        {
            DISP_ERROR("thd is less than 0.\n");
            return HI_FAILURE;
        }

        VDP_DISP_SetVtThd(u32DispId, 2, (HI_U32)thd);

        thd = DISP_GFX_GetIsrPoint1(u32DispId, pstCfg);
        if (thd < 0)
        {
            DISP_ERROR("thd is less than 0.\n");
            return HI_FAILURE;
        }

        VDP_DISP_SetVtThd(u32DispId, 3, (HI_U32)thd);

    }
    else
    {
    #if 0
        thd = pstCfg->stTiming.u32Vfb + pstCfg->stTiming.u32Vbb + DISP_VTTHD_VIDEO_OFFSET;
    #else
        thd = (pstCfg->stTiming.u32Vfb
                + pstCfg->stTiming.u32Vbb
                + pstCfg->stTiming.u32Vact)*8/10;
    #endif
        if (u32DispId == 1)
        {
            thd = thd + DISP_VTTHD_DISP0_TO_DISP1;
        }

        VDP_DISP_SetVtThd(u32DispId, 1, (HI_U32)thd);

        /*
          ||<--------- FRRAME 0--------->||<--------- FRRAME 1--------->||
          -----------------------------------------------------------------
          || VBB0 |     VACT0     | VFB0 || VBB01 |     VACT1    | VFB1 ||
          -----------------------------------------------------------------
                                    |<----------->|
                                   Pos2    ^
                                          /|\
                                           |
                                     Here equal to 'DISP_VTTHD_GFX_OFFSET'
                                     Pos2 is thd2.
                                     If DISP_VTTHD_GFX_OFFSET is bigger tha (VFB0+VBB1),
                                     Pos2 is in VACT0.
        */

        thd = DISP_GFX_GetIsrPoint(u32DispId, pstCfg);
        if (thd < 0)
        {
            DISP_ERROR("thd is less than 0.\n");
            return HI_FAILURE;
        }

        VDP_DISP_SetVtThd(u32DispId, 2, (HI_U32)thd);


        thd = DISP_GFX_GetIsrPoint1(u32DispId, pstCfg);
        if (thd < 0)
        {
            DISP_ERROR("thd is less than 0.\n");
            return HI_FAILURE;
        }

        VDP_DISP_SetVtThd(u32DispId, 3, (HI_U32)thd);
    }

    // set vp
    DISP_MEMSET(&DispRect, 0, sizeof(VDP_DISP_RECT_S));
    DispRect.u32DXL  = pstCfg->stInfo.stOrgRect.s32Width;
    DispRect.u32DYL  = pstCfg->stInfo.stOrgRect.s32Height;
    DispRect.u32IWth = pstCfg->stInfo.stOrgRect.s32Width;
    DispRect.u32IHgt = pstCfg->stInfo.stOrgRect.s32Height;
    DispRect.u32OWth = pstCfg->stInfo.stOrgRect.s32Width;
    DispRect.u32OHgt = pstCfg->stInfo.stOrgRect.s32Height;
    DispRect.u32VXL  = pstCfg->stInfo.stOrgRect.s32Width;
    DispRect.u32VYL  = pstCfg->stInfo.stOrgRect.s32Height;

    Chip_Specific_DispSetChanClk(eChn,pstCfg);

    vdp_layer = (HI_DRV_DISPLAY_1 == eChn) ? VDP_LAYER_VP0 : VDP_LAYER_VP1;

    VDP_VP_SetLayerReso(vdp_layer, DispRect);
    VDP_VP_SetRegUp(vdp_layer);
#if defined (CHIP_HIFONEB02)

	//DISP_ERROR("chan->%d--fmt -->%d\n",eChn,pstCfg->stInfo.eFmt);
	/*to support two channels(4k@50/4k@60), may  98m and 98c can not succeed in compiling.*/
	if (HI_DRV_DISPLAY_1 == eChn)
	{
		if (((pstCfg->stInfo.eFmt == HI_DRV_DISP_FMT_3840X2160_50)
			 || (pstCfg->stInfo.eFmt == HI_DRV_DISP_FMT_3840X2160_60))
			 )
		{
			if (1)
			{
				VDP_FUNC_SetIntf(VDP_INTF_MODE_4K60_ALL);
			}
			else
			{
				VDP_FUNC_SetIntf(VDP_INTF_MODE_4K60_HDMI420);
			}
		}
		else
		{
			VDP_FUNC_SetIntf(VDP_INTF_MODE_NON_4K60);
		}
	}
#endif
    VDP_DISP_SetRegUp(u32DispId);

    return HI_SUCCESS;
}


HI_S32 PF_SetChnFmt(HI_DRV_DISPLAY_E eChn, HI_DRV_DISP_FMT_E eFmt, HI_DRV_DISP_STEREO_E enStereo)
{
    DISP_FMT_CFG_S stCfg;
    HI_S32  Ret;
    HI_S32 index;

       index = DispHalGetEnFmtIndex(eFmt);
       if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stCfg))
           return HI_FAILURE;

    /*select clk source*/
    if  ((stCfg.stInfo.eFmt >= HI_DRV_DISP_FMT_576P_50 )&& (stCfg.stInfo.eFmt <= HI_DRV_DISP_FMT_1440x480i_60 ))
        stCfg.enPllIndex = DISP_CLOCK_SOURCE_SD0;
    else
    {
        #ifdef HI_DISP_DOUBLE_HD_SUPPORT
        if (HI_DRV_DISPLAY_1 == eChn)
            stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD0;
        else
            stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD1;

        #else
        stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD0;

        #endif
    }


    stCfg.stInfo.eDispMode = enStereo;
	stCfg.stInfo.eFmt= eFmt;

    Ret = PF_SetChnBaseTiming(eChn, &stCfg);
    return Ret;
}


HI_S32 PF_GetFmtTiming(HI_DRV_DISP_FMT_E eFmt, HI_DRV_DISP_TIMING_S *pstTiming)
{
    DISP_FMT_CFG_S stCfg;
	HI_U32 index;

	index = DispHalGetEnFmtIndex(eFmt);
	if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stCfg))
	{
	   return HI_FAILURE;
	}

    pstTiming->u32VACT = stCfg.stTiming.u32Vact ;
    pstTiming->u32VBB  = stCfg.stTiming.u32Vbb;
    pstTiming->u32VFB  = stCfg.stTiming.u32Vfb ;


    pstTiming->u32HACT = stCfg.stTiming.u32Hact ;

    pstTiming->u32HBB = stCfg.stTiming.u32Hbb ;
    pstTiming->u32HFB = stCfg.stTiming.u32Hfb ;


    pstTiming->u32HPW = stCfg.stTiming.u32Hpw ;
    pstTiming->u32VPW = stCfg.stTiming.u32Vpw ;


    pstTiming->bIDV = stCfg.stTiming.bIdv ;
    pstTiming->bIHS = stCfg.stTiming.bIhs ;
    pstTiming->bIVS = stCfg.stTiming.bIvs ;

    pstTiming->u32ClkPara0 = stCfg.u32Pll[0] ;
    pstTiming->u32ClkPara1 = stCfg.u32Pll[1] ;

	pstTiming->u32AspectRatioW = stCfg.stInfo.stAR.u32ARw;
	pstTiming->u32AspectRatioH= stCfg.stInfo.stAR.u32ARh;
	pstTiming->u32VertFreq = stCfg.stInfo.u32RefreshRate;
	pstTiming->u32PixFreq =  (( pstTiming->u32HBB + pstTiming->u32HACT + pstTiming->u32HFB)
                                  * ( pstTiming->u32VBB + pstTiming->u32VACT + pstTiming->u32VFB)
                                  * (pstTiming->u32VertFreq / 100)) / 1000;

	//DISP_ERROR("u32VertFreq ,pix(%d,%d)\n",pstTiming->u32VertFreq,pstTiming->u32PixFreq);
    return HI_SUCCESS;
}

#if defined (CHIP_HIFONEB02)
HI_S32 PF_SetHDMI420(HI_DRV_DISPLAY_E enDisp,HI_BOOL bEnable)
{
	VDP_DISP_Hdmi420En(DISP_HAL_GetChID(enDisp),bEnable);
	return HI_SUCCESS;
}
#else
HI_S32 PF_SetHDMI420(HI_DRV_DISPLAY_E enDisp,HI_BOOL bEnable)
{
	return HI_SUCCESS;
}
#endif

HI_S32 DispCheck_FOUTVCO(TEMP_PARA_S* pstTmpPara, HI_U32 u32FREF)
{
    HI_U32 i, TmpFBDIV = 0, u32Tmpm;

    if (0 == u32FREF)
    {
        DISP_ERROR("Denominator may be zero !\n");
        return HI_FAILURE;
    }

    if ((pstTmpPara->u32TmpFOUTVCO < FOUTVCO_MAX) && (pstTmpPara->u32TmpFOUTVCO > FOUTVCO_MIN))
    {
        //debug_printf("Check FOUTVCO(%d)\n", pstTmpPara->u32TmpFOUTVCO);
        /*FOUTVCO  =m* FBDIV */
        for ( i = REFDIV_I_MIN; i < REFDIV_I_MAX;  i++ )
        {
            /*div m */
            if ( 0 == u32FREF % i )
            {
                u32Tmpm =  u32FREF / i ;
                if (u32Tmpm)
                {
                    // debug_printf("try :FCO (%d),m(%d)", pstTmpPara->u32TmpFOUTVCO, u32Tmpm);
                    if (0 == pstTmpPara->u32TmpFOUTVCO % u32Tmpm)
                    {
                        TmpFBDIV = pstTmpPara->u32TmpFOUTVCO / u32Tmpm;
                        if ((TmpFBDIV < FBDIV_I_MAX) && (TmpFBDIV >  FBDIV_I_MIN)  )
                        {
                            pstTmpPara->u32TmpM = u32Tmpm;
                            pstTmpPara->u32TmpFBDIV = TmpFBDIV;
                            return HI_SUCCESS;
                        }
                    }
                }
                else
                {
                    DISP_ERROR("denominator is zero\n");
                    return HI_FAILURE;
                }
            }
        }
    }

    return HI_FAILURE;
}

/*PixClk  XKHz*/
HI_S32 MakePixClkParaInteger(HI_U32 u32TestPixClk, PLL_PARA_S* pstPllPara)
{
    //HI_S32  nRet;
    HI_U32 i, j;
    TEMP_PARA_S stTmpPara;
    /*  (0~7)* (0~7)*/
    HI_U32 nPara[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 24, 25, 28, 30, 35, 36, 42, 49};

    /*1: Make  FOUTVCO ,n, FBDIV */
    for ( i = 0; i < (sizeof(nPara) / sizeof(HI_U32)); i++ )
    {
        stTmpPara.u32TmpFOUTVCO = u32TestPixClk * 2 * 2 * nPara[i];

        if (HI_SUCCESS == DispCheck_FOUTVCO(&stTmpPara, pstPllPara->u32FREF))
        {
            stTmpPara.u32TmpN = nPara[i];
            pstPllPara->u32FOUTVCO = stTmpPara.u32TmpFOUTVCO;
            pstPllPara->u32FBDIV = stTmpPara.u32TmpFBDIV;

            /*2:get PSTDIV1 PSTDIV2 value*/
            for ( j = 1; j <= 7; j++ )
            {
                if ((!(stTmpPara.u32TmpN % j)) && (j <= 7) && ( stTmpPara.u32TmpN / j <= 7))
                {
                    pstPllPara->u32PSTDIV1 = j;
                    pstPllPara->u32PSTDIV2 = stTmpPara.u32TmpN / j;

                    if (stTmpPara.u32TmpM)
                    {
                        pstPllPara->u32REFDIV = pstPllPara->u32FREF / stTmpPara.u32TmpM;
                    }
                    else
                    {
                        DISP_ERROR("denominator is zero\n");
                        return HI_FAILURE;
                    }

                    return HI_SUCCESS;
                }
            }
        }
    }

    return HI_FAILURE;
}


HI_S32 MakeReg(PLL_PARA_S* pstPllPara)
{
    pstPllPara->u32REG1 = (HI_U32)(pstPllPara->u32PSTDIV1 << 28) + (HI_U32)(pstPllPara->u32PSTDIV2 << 24) + (HI_U32)(pstPllPara->u32FRAC);
    pstPllPara->u32REG2 = (HI_U32)( 1 << 25) + (HI_U32)(pstPllPara->u32REFDIV << 12) + (HI_U32)(pstPllPara->u32FBDIV);
    return HI_SUCCESS;
}

HI_S32 DispCheckCustomTimingPllPara(HI_U32 u32TestPixClk, REG_PARA_S* pstRegPara)
{
    HI_S32 nRet;
    PLL_PARA_S stPllPara;

    HI_U32 i, TestOk, TmpDiff, TmpClkAdd, TmpClkDec, u32CheckPixClk = 0;
    //HI_U32 all_h, all_v, all_pix, pixclk;

    memset(&stPllPara, 0, sizeof(PLL_PARA_S));
    stPllPara.u32FREF = 24000;
    nRet = MakePixClkParaInteger(u32TestPixClk, &stPllPara);

    if (HI_SUCCESS != nRet)
    {
        TestOk = 0;
        TmpDiff = (u32TestPixClk * PIX_DIFF_MAX) / 10000;

        for (i = 0; i < TmpDiff; i++)
        {
            TmpClkAdd = u32TestPixClk + i;
            TmpClkDec  = u32TestPixClk - i;

            if (HI_SUCCESS == MakePixClkParaInteger(TmpClkAdd, &stPllPara))
            {
                u32CheckPixClk = TmpClkAdd;
                TestOk = 1;
                break;
            }

            if (HI_SUCCESS == MakePixClkParaInteger(TmpClkDec, &stPllPara))
            {
                u32CheckPixClk = TmpClkDec;
                TestOk = 1;
                break;
            }
        }
    }
    else
    { TestOk = 1; }

    if (!TestOk)
    {
        return HI_FAILURE;
    }

    MakeReg(&stPllPara);
    pstRegPara->u32ClkPara0 = stPllPara.u32REG1;
    pstRegPara->u32ClkPara1 = stPllPara.u32REG2;
    pstRegPara->u32CalcPixFreq =  u32CheckPixClk;
    // s2 set calculate pll reg para

    return HI_SUCCESS;
}

HI_S32 DISP_GetTimingReg( HI_DRV_DISP_TIMING_S* pstTiming)
{
    HI_S32 Ret;
    /*VESA and CUSTOM  format need calculate Reg value!*/
    // s1 make pixclk
    REG_PARA_S stRegPara;

    if ((pstTiming->u32ClkPara0) || (pstTiming->u32ClkPara1))
    {
        DISP_WARN("used custom clk reg value! (0x%x)(0x%x)\n", pstTiming->u32ClkPara0, pstTiming->u32ClkPara1);
        return HI_SUCCESS;
    }

    if ( (pstTiming->u32VertFreq / 1000) > 120)
    {
        DISP_ERROR("freshRate  out of rang  (0~120)!!\n");
        return HI_FAILURE;
    }

    if ( 0 == pstTiming->u32PixFreq )
    {
        pstTiming->u32PixFreq =  (( pstTiming->u32HBB + pstTiming->u32HACT + pstTiming->u32HFB)
                                  * ( pstTiming->u32VBB + pstTiming->u32VACT + pstTiming->u32VFB)
                                  * (pstTiming->u32VertFreq / 1000)) / 1000;
    }

    if ((20000 > pstTiming->u32PixFreq) || (600000 < pstTiming->u32PixFreq))
    {
        DISP_ERROR("u32PixClk (%d)out of rang  (20000~600000)!!\n", pstTiming->u32PixFreq);
        return HI_FAILURE;
    }

    DISP_MEMSET(&stRegPara, 0, sizeof(REG_PARA_S));
    Ret = DispCheckCustomTimingPllPara(pstTiming->u32PixFreq, &stRegPara);

    if (HI_SUCCESS != Ret)
    {
        DISP_ERROR("make  REG  err!!\n");
        return HI_FAILURE;
    }

    pstTiming->u32ClkPara0 = stRegPara.u32ClkPara0;
    pstTiming->u32ClkPara1 = stRegPara.u32ClkPara1;
    DISP_INFO("u32PixClk (%d)reg(0x%x)(0x%x)!!\n", pstTiming->u32PixFreq, pstTiming->u32ClkPara0, pstTiming->u32ClkPara1);
    return HI_SUCCESS;
}


HI_S32 PF_SetChnTiming(HI_DRV_DISPLAY_E eChn, HI_DRV_DISP_TIMING_S *pstTiming)
{
    DISP_FMT_CFG_S stCfg;
    HI_S32 Ret;

    //pstTiming
    DISP_MEMSET(&stCfg, 0, sizeof(DISP_FMT_CFG_S));

    Ret = DISP_GetTimingReg(pstTiming);
    if (HI_SUCCESS != Ret)
    {
        DISP_ERROR("Get Custom Timing Reg Para err! (%d)\n", Ret);
        return Ret;
    }

    /*select clk source*/
    if  ((stCfg.stInfo.eFmt >= HI_DRV_DISP_FMT_576P_50 )&& (stCfg.stInfo.eFmt <= HI_DRV_DISP_FMT_1440x480i_60 ))
        stCfg.enPllIndex = DISP_CLOCK_SOURCE_SD0;
    else
    {
    #ifdef HI_DISP_DOUBLE_HD_SUPPORT
        if (HI_DRV_DISPLAY_1 == eChn)
            stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD0;
        else
            stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD1;

        #else
        stCfg.enPllIndex = DISP_CLOCK_SOURCE_HD0;
     #endif
    }


    stCfg.stInfo.eFmt = HI_DRV_DISP_FMT_CUSTOM;
    stCfg.stInfo.eDispMode = DISP_STEREO_NONE;

    stCfg.stInfo.u32RefreshRate = pstTiming->u32VertFreq;

    stCfg.stInfo.stOrgRect.s32X = 0;
    stCfg.stInfo.stOrgRect.s32Y = 0;
    stCfg.stInfo.stOrgRect.s32Width = pstTiming->u32HACT;
    stCfg.stInfo.stOrgRect.s32Height = pstTiming->u32VACT;

    stCfg.stTiming.bSynm = 1 ;
    stCfg.stTiming.bIop = 1 ;
    stCfg.stTiming.u32Intfb = 2 ;

    stCfg.stTiming.u32Vact = pstTiming->u32VACT;
    stCfg.stTiming.u32Vbb = pstTiming->u32VBB ;
    stCfg.stTiming.u32Vfb = pstTiming->u32VFB ;

    stCfg.stTiming.u32Bvact = 1;
    stCfg.stTiming.u32Bvbb = 1 ;
    stCfg.stTiming.u32Bvfb = 1 ;

    stCfg.stTiming.u32Hact = pstTiming->u32HACT ;
    if (eChn == s_stHalIntf[HI_DRV_DISP_INTF_VGA0].enChan)
    {
        /*if VGA interface ,need date is later than sync ,so need to adjust :*/
        stCfg.stTiming.u32Hbb = pstTiming->u32HBB -7 ;
        stCfg.stTiming.u32Hfb = pstTiming->u32HFB + 7 ;
    }
    else
    {
        stCfg.stTiming.u32Hbb = pstTiming->u32HBB ;
        stCfg.stTiming.u32Hfb = pstTiming->u32HFB ;
    }


    stCfg.stTiming.u32Hpw = pstTiming->u32HPW ;
    stCfg.stTiming.u32Vpw = pstTiming->u32VPW ;

    stCfg.stTiming.u32Hmid = 1;

    stCfg.stTiming.bIdv = pstTiming->bIDV ;
    stCfg.stTiming.bIhs = pstTiming->bIHS;
    stCfg.stTiming.bIvs = pstTiming->bIVS;

    stCfg.u32Pll[0] = pstTiming->u32ClkPara0;
    stCfg.u32Pll[1] = pstTiming->u32ClkPara1;

    Ret = PF_SetChnBaseTiming(eChn, &stCfg);
    return Ret;
}

HI_S32 PF_SetChnPixFmt(HI_DRV_DISPLAY_E eChn, HI_DRV_PIX_FORMAT_E ePix)
{
//    HI_U32 u32DispId = DISP_HAL_GetChID(eChn);
    return HI_SUCCESS;
}

HI_S32 PF_SetChnBgColor(HI_DRV_DISPLAY_E eChn, HI_DRV_COLOR_SPACE_E enCS, HI_DRV_DISP_COLOR_S *pstBGC)
{
    VDP_BKG_S stBkg;
    ALG_COLOR_S stAlgC;
    DISP_DA_FUNCTION_S *pstDA;

    pstDA = DISP_DA_GetFunction();
    if (!pstDA)
    {
        return HI_FAILURE;
    }

    stAlgC.u8Red   = pstBGC->u8Red;
    stAlgC.u8Green = pstBGC->u8Green;
    stAlgC.u8Blue  = pstBGC->u8Blue;

    //DISP_ERROR("chan%d--->(%d,%d,%d)\n",eChn,stAlgC.u8Red ,stAlgC.u8Green,stAlgC.u8Blue);

    if( (HI_DRV_CS_BT601_RGB_LIMITED == enCS)
    ||(HI_DRV_CS_BT601_RGB_FULL == enCS)
    ||(HI_DRV_CS_BT709_RGB_LIMITED == enCS)
    ||(HI_DRV_CS_BT709_RGB_FULL == enCS)
    )
    {
        /*now, the internal bitwidth is 10bit, but
        stAlgC.u8Red and others is 8 bit. so we should left shift 2 bit.*/
        stBkg.bBkType = 0;
        stBkg.u32BkgA = 0;
        stBkg.u32BkgY = ((HI_U32)stAlgC.u8Red<< 2);
        stBkg.u32BkgU = ((HI_U32)stAlgC.u8Green<< 2);
        stBkg.u32BkgV = ((HI_U32)stAlgC.u8Blue<< 2);
    }
    else
    {
        pstDA->PFCscRgb2Yuv(&stAlgC, &stAlgC);
        // TODO:
        stBkg.bBkType = 0;
        stBkg.u32BkgA = 0;
        stBkg.u32BkgY = ((HI_U32)stAlgC.u8Y)  << 2;
        stBkg.u32BkgU = ((HI_U32)stAlgC.u8Cb) << 2;
        stBkg.u32BkgV = ((HI_U32)stAlgC.u8Cr) << 2;
    }
/*
    DISP_PRINT(">>>>>>>>SET BGC R=%d, G=%d, B=%d, Y=%d, PB=%d, PR=%d\n",
               stAlgC.u8Red, stAlgC.u8Green, stAlgC.u8Blue,
               stAlgC.u8Y, stAlgC.u8Cb, stAlgC.u8Cr);
*/

    Chip_Specific_SetMixerBgColor(eChn, stBkg);
    return HI_SUCCESS;
}


HI_S32 PF_SetChnColor(HI_DRV_DISPLAY_E eChn, DISP_HAL_COLOR_S *pstColor)
{
    #ifndef __DISP_PLATFORM_BOOT__
    VDP_CSC_DC_COEF_S stCscCoef;
    VDP_CSC_COEF_S stCscCoef2;
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_PQ_CSC_MODE_E enCSCMode = HI_PQ_CSC_BUTT;

    HI_U32 u32DispId = DISP_HAL_GetChID(eChn);

    memset((void*)&stPictureSetting, 0, sizeof(HI_PQ_PICTURE_SETTING_S));

    switch(pstColor->enInputCS)
   {
    case HI_DRV_CS_BT601_YUV_LIMITED:
        switch (pstColor->enOutputCS)
        {
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV_601_709;
                break;
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV;
                break;
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_601;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT601_YUV_FULL:
        switch (pstColor->enOutputCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_601;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
     case HI_DRV_CS_BT709_YUV_LIMITED:
        switch (pstColor->enOutputCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_709;
                break;
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV_709_601;
                break;
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT709_YUV_FULL:
        switch (pstColor->enOutputCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_709_FULL;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT709_RGB_FULL:
        switch (pstColor->enOutputCS)
        {
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_RGB2YUV_601;
                break;
            case HI_DRV_CS_BT601_YUV_FULL:
                enCSCMode = HI_PQ_CSC_RGB2YUV_601_FULL;
                break;
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_RGB2YUV_709;
                break;
            case HI_DRV_CS_BT709_YUV_FULL:
                enCSCMode = HI_PQ_CSC_RGB2YUV_709_FULL;
                break;
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_RGB2RGB;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
     default:
        break;
    }

    DRV_PQ_Get8BitCSCCoef(enCSCMode, (HI_PQ_CSC_COEF_S *)&stCscCoef2, (HI_PQ_CSC_DCCOEF_S *)&stCscCoef);
    VDP_DISP_SetCscDcCoef(u32DispId, stCscCoef);
    VDP_DISP_SetCscCoef(u32DispId, stCscCoef2);
    VDP_DISP_SetCscEnable(u32DispId, 1);
    VDP_DISP_SetRegUp(u32DispId);

    #endif

    return HI_SUCCESS;
}

HI_S32 PF_SetChnEnable(HI_DRV_DISPLAY_E eChn, HI_BOOL bEnalbe)
{
    HI_U32 u32DispId = DISP_HAL_GetChID(eChn);
    U_PERI_CRG54 unTmpValue, u32SaveValue;
#ifdef HI_DISP_BUILD_FULL
    HI_U32 t;
#endif

    VDP_DISP_SetIntfEnable(u32DispId, bEnalbe);

    VDP_DISP_SetRegUp(u32DispId);

#ifdef HI_DISP_BUILD_FULL
    if (HI_DRV_SYS_GetTimeStampMs(&t))
    {
        DISP_ERROR("get sys time failed, not init.\n");
        return HI_FAILURE;
    }
    //DISP_ERROR("disp=%d, t=%d, en=%d\n", u32DispId, t, bEnalbe);
#endif

    // switch sd clock divide parameters otherwis DISP0 maybe die.
    if ( (eChn == HI_DRV_DISPLAY_0) && bEnalbe )
    {
        u32SaveValue.u32 = g_pstRegCrg->PERI_CRG54.u32;

        unTmpValue.u32 = u32SaveValue.u32;

        /*set not div */
        unTmpValue.bits.vo_sd_clk_div = 3;
        g_pstRegCrg->PERI_CRG54.u32 = unTmpValue.u32;

        mdelay(5);

        /*restore value !*/
        g_pstRegCrg->PERI_CRG54.u32 = u32SaveValue.u32;
    }
    else if ( (eChn == HI_DRV_DISPLAY_1) && bEnalbe )
    {
        u32SaveValue.u32 = g_pstRegCrg->PERI_CRG54.u32;

        unTmpValue.u32 = u32SaveValue.u32;
        unTmpValue.bits.vo_hd_clk_div = 3;
        g_pstRegCrg->PERI_CRG54.u32 = unTmpValue.u32;

        mdelay(5);
        g_pstRegCrg->PERI_CRG54.u32 = u32SaveValue.u32;
    }


    return HI_SUCCESS;
}

HI_S32 PF_SetMSChnEnable(HI_DRV_DISPLAY_E eChnM, HI_DRV_DISPLAY_E eChnS, HI_U32 u32DelayMs, HI_BOOL bEnalbe)
{
#ifdef HI_DISP_BUILD_FULL
    HI_U32 t;
#endif
    HI_U32 u32DispIdM = DISP_HAL_GetChID(eChnM);
    HI_U32 u32DispIdS = DISP_HAL_GetChID(eChnS);
    Chip_Specific_DispSetMSChnEnable(u32DispIdM, u32DispIdS, u32DelayMs, bEnalbe);


#ifdef HI_DISP_BUILD_FULL
    if (HI_DRV_SYS_GetTimeStampMs(&t))
    {
    	DISP_ERROR("get sys time failed, not init.\n");
        return HI_FAILURE;
    }
    //DISP_ERROR("dispM=%d, t=%d, en=%d\n", eChnM, t, bEnalbe);
#endif

    return HI_SUCCESS;
}


HI_S32 PF_GetChnEnable(HI_DRV_DISPLAY_E eChn, HI_BOOL *pbEnalbe)
{
    HI_U32 u32DispId = DISP_HAL_GetChID(eChn);
    HI_U32 bTrue;

    VDP_DISP_GetIntfEnable(u32DispId, &bTrue);

    *pbEnalbe = bTrue ? HI_TRUE : HI_FALSE;
    return HI_SUCCESS;
}

/********************************************/
/* capability */

/********************************************/
/* interrupt */
HI_S32 PF_SetIntEnable(HI_U32 u32Int, HI_BOOL bEnable)
{
    //DISP_ERROR("PF_SetIntEnable   int=%d, en=%d\n", u32Int, bEnable);
    if (bEnable)
    {
        VDP_DISP_SetIntMask(u32Int);
    }
    else
    {
        VDP_DISP_SetIntDisable(u32Int);
    }
    return HI_SUCCESS;
}

HI_S32 PF_GetIntSetting(HI_U32 *pu32IntSetting)
{
    VDP_DISP_GetIntMask(pu32IntSetting);
    return HI_SUCCESS;
}

HI_S32 PF_GetMaskedIntState(HI_U32 *pu32State)
{
    *pu32State = VDP_DISP_GetMaskIntSta((HI_U32)DISP_INTERRUPT_ALL);
    return HI_SUCCESS;
}

HI_S32 PF_GetUnmaskedIntState(HI_U32 *pu32State)
{

    *pu32State = VDP_DISP_GetIntSta((HI_U32)DISP_INTERRUPT_ALL);
    return HI_SUCCESS;
}


HI_S32 PF_CleanIntState(HI_U32 u32State)
{
    VDP_DISP_ClearIntSta(u32State);
    return HI_SUCCESS;
}

HI_U32 FP_GetChnIntState(HI_DRV_DISPLAY_E enDisp, HI_U32 u32IntState)
{
    switch (enDisp)
    {
        case HI_DRV_DISPLAY_1 :

            return (HI_U32)(u32IntState & 0x0ful);

        case HI_DRV_DISPLAY_0 :

            return (HI_U32)(u32IntState & 0xf0ul);

        default:
            return (HI_U32)0;
    }
}

HI_U32 FP_GetChnBottomFlag(HI_DRV_DISPLAY_E enDisp, HI_BOOL *pbBtm, HI_U32 *pu32Vcnt)
{
    HI_U32 u32DispId = DISP_HAL_GetChID(enDisp);

    if (pbBtm && pu32Vcnt)
    {
        VDP_DISP_GetVactState(u32DispId, pbBtm, pu32Vcnt);
    }

    return 0;
}


VDP_DISP_INTF_E DISP_HAL_GetHalIntfIdForVenc(HI_DRV_DISPLAY_E enDisp,DISP_INTF_S *pstIf,HI_DRV_DISP_FMT_E eFmt)
{
    DISP_VENC_E enVenc = DISP_VENC_MAX;
    HI_BOOL bNeedVenc = HI_FALSE;
    VDP_DISP_INTF_E  enVDPInf = VDP_DISP_INTF_BUTT;


    switch (pstIf->stIf.eID)
    {
        case HI_DRV_DISP_INTF_YPBPR0:
        case HI_DRV_DISP_INTF_RGB0:
            /*(link to xDate   adjust by format !!)*/
            bNeedVenc = HI_TRUE;
            if ((eFmt >= HI_DRV_DISP_FMT_PAL) && (eFmt <= HI_DRV_DISP_FMT_1440x480i_60) )
            //if ((eFmt >= HI_DRV_DISP_FMT_PAL) && (eFmt <= HI_DRV_DISP_FMT_SECAM_H) )
            {
                enVenc   = DISP_VENC_SDATE0;
                enVDPInf =   VDP_DISP_INTF_SDDATE;
            }
            else
            {
                enVenc   = DISP_VENC_HDATE0;
                enVDPInf =  VDP_DISP_INTF_HDDATE;
            }
            break;
        case HI_DRV_DISP_INTF_SVIDEO0:
        case HI_DRV_DISP_INTF_CVBS0:

            bNeedVenc = HI_TRUE;
            enVenc  = DISP_VENC_SDATE0;
            enVDPInf  =  VDP_DISP_INTF_SDDATE;
            break;
    case HI_DRV_DISP_INTF_VGA0:
        bNeedVenc = HI_FALSE;
        enVenc   = DISP_VENC_VGA0;
            enVDPInf  =  VDP_DISP_INTF_VGA;
            break;
        case HI_DRV_DISP_INTF_HDMI0:
        case HI_DRV_DISP_INTF_HDMI1:
        case HI_DRV_DISP_INTF_HDMI2:
            enVDPInf  =  VDP_DISP_INTF_HDMI;
            break;

        case HI_DRV_DISP_INTF_BT1120_0:
        case HI_DRV_DISP_INTF_BT1120_1:
        case HI_DRV_DISP_INTF_BT1120_2:
            enVDPInf  =  VDP_DISP_INTF_BT1120;
            break;
        case HI_DRV_DISP_INTF_LCD0:
        case HI_DRV_DISP_INTF_LCD1:
        case HI_DRV_DISP_INTF_LCD2:
            enVDPInf  =  VDP_DISP_INTF_LCD;
            break;

        case HI_DRV_DISP_INTF_BT656_0:
        case HI_DRV_DISP_INTF_BT656_1:
        case HI_DRV_DISP_INTF_BT656_2:
        default:
            enVDPInf  =  VDP_DISP_INTF_BUTT;
            break;
    }

    pstIf->bLinkVenc = bNeedVenc;
    pstIf->eVencId   = enVenc;
    return enVDPInf;
}

/********************************************/
/* VDAC */
HI_VOID DISP_HAL_ResetVDacState(HI_VOID)
{
    HI_S32 i;

    DISP_MEMSET(s_stHalVDac, 0, sizeof(s_stHalVDac));

    for(i=0; i<HI_DISP_VDAC_MAX_NUMBER; i++)
    {
        s_stHalVDac[i].bSupport = HI_TRUE;
        s_stHalVDac[i].bIdle    = HI_TRUE;
    }

    return;
}

HI_S32 DISP_HAL_VDACIsIdle(HI_U32 uVdac)
{
    HI_U32 v0;

    v0 = uVdac & 0xff;

    if (v0 < HI_DISP_VDAC_MAX_NUMBER)
    {
        if (s_stHalVDac[v0].bSupport && s_stHalVDac[v0].bIdle)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

HI_S32 PF_AcquireVDAC(HI_U32 uVdac)
{
    HI_U32 v0;

    v0 = uVdac & 0xff;

    if (v0 < HI_DISP_VDAC_MAX_NUMBER)
    {
        if (s_stHalVDac[v0].bSupport && s_stHalVDac[v0].bIdle)
        {
            s_stHalVDac[v0].bIdle = HI_FALSE;
        }
        else
        {
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 PF_ReleaseVDAC(HI_U32 uVdac)
{
    HI_U32 v0;

    v0 = uVdac & 0xff;

    if (v0 < HI_DISP_VDAC_MAX_NUMBER)
    {
        if (s_stHalVDac[v0].bSupport && !s_stHalVDac[v0].bIdle)
        {
            s_stHalVDac[v0].bIdle = HI_TRUE;
        }
    }

    return HI_SUCCESS;
}

HI_VOID VDP_VDAC_SetClk(HI_DRV_DISPLAY_E enDisp,DISP_VENC_E eDate, HI_U32 uVdac)
{

    U_PERI_CRG54 unTmpValue;

#if defined (CHIP_HIFONEB02)
	U_PERI_CRG71 unTmpCRG71Value;
	unTmpCRG71Value.u32 = g_pstRegCrg->PERI_CRG71.u32;
	unTmpCRG71Value.bits.vdac_chop_cken = HI_TRUE;
	g_pstRegCrg->PERI_CRG71.u32 = unTmpCRG71Value.u32;
#endif

    unTmpValue.u32 = g_pstRegCrg->PERI_CRG54.u32;

    /*select VDaCx clk*/
    switch(uVdac)
    {
        case 0:
            if (DISP_VENC_VGA0 == eDate)
                unTmpValue.bits.vdac_ch0_clk_sel = (HI_DRV_DISPLAY_0 == enDisp) ? 0 : 1;
            else
                unTmpValue.bits.vdac_ch0_clk_sel = (DISP_VENC_SDATE0 == eDate) ? 0 : 1;
            break;
#if !(defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100))
        case 1:
            if (DISP_VENC_VGA0 == eDate)
                unTmpValue.bits.vdac_ch1_clk_sel = (HI_DRV_DISPLAY_0 == enDisp) ? 0 : 1;
            else
                unTmpValue.bits.vdac_ch1_clk_sel = (DISP_VENC_SDATE0 == eDate) ? 0 : 1;
            break;
        case 2:
            if (DISP_VENC_VGA0 == eDate)
                unTmpValue.bits.vdac_ch2_clk_sel = (HI_DRV_DISPLAY_0 == enDisp) ? 0 : 1;
            else
                unTmpValue.bits.vdac_ch2_clk_sel = (DISP_VENC_SDATE0 == eDate) ? 0 : 1;
            break;
        case 3:
            if (DISP_VENC_VGA0 == eDate)
                unTmpValue.bits.vdac_ch3_clk_sel = (HI_DRV_DISPLAY_0 == enDisp) ? 0 : 1;
            else
                unTmpValue.bits.vdac_ch3_clk_sel = (DISP_VENC_SDATE0 == eDate) ? 0 : 1;
            break;
#endif
        default:
            break;
    }

    g_pstRegCrg->PERI_CRG54.u32 = unTmpValue.u32;

}


/*
    xDate clock link:
    SDate --->DHD1
    HDate --->DHD0
    YPbPr CVBS DAC clock linked by XDate.

    VGA DAC is not across XDate ,clock  linked by channel.
*/
HI_S32 PF_AddVDacToVenc(HI_DRV_DISPLAY_E enDisp,DISP_VENC_E eVenc, HI_U32 uVdac, HI_DRV_DISP_VDAC_SIGNAL_E signal)
{
    HI_U32 v0;

    v0 = (uVdac >> 0) & 0xff;

    if (eVenc >= DISP_VENC_MAX ||
        signal >= HI_DRV_DISP_VDAC_SIGNAL_BUTT)
    {
        DISP_ERROR("eVenc or signal out of range.\n");
        return HI_FAILURE;
    }

    if (v0 < HI_DISP_VDAC_MAX_NUMBER)
    {
        VDP_VDAC_SetLink(eVenc, v0, signal);
        VDP_VDAC_SetClk(enDisp,eVenc, v0);
    }
    return HI_SUCCESS;
}


HI_S32 DISP_HAL_SetIdleVDACDisable(HI_VOID)
{
    HI_U32 i;

    for(i=0; i<HI_DISP_VDAC_MAX_NUMBER; i++)
    {
        if (s_stHalVDac[i].bSupport && s_stHalVDac[i].bIdle)
        {
            //DISP_ERROR("================Vdac %d is idle and close it\n", i);
            VDP_VDAC_SetEnable(i, 0,0);

        }
    }

    return HI_SUCCESS;
}


HI_S32 PF_SetVDACEnable(HI_U32 uVdac, HI_BOOL bEnable,HI_U32 u32DelayMs)
{
    HI_U32 v0;

    v0 = (uVdac >> 0) & 0xff;

    if (v0 < HI_DISP_VDAC_MAX_NUMBER)
    {
        if (HI_TRUE == bEnable)
        {
            VDP_VDAC_SetClockEnable(v0, bEnable);
            VDP_VDAC_SetEnable(v0, bEnable,u32DelayMs);
        }
        else
        {
            VDP_VDAC_SetEnable(v0, bEnable,u32DelayMs);
            VDP_VDAC_SetClockEnable(v0, bEnable);
        }
    }


    DISP_HAL_SetIdleVDACDisable();

    return HI_SUCCESS;
}


/********************************************/
/* interface */
#define DISP_HAL_INTF_FUNCTION_START_HAERE
HI_VOID DISP_HAL_ResetIntfState(HI_VOID)
{
    DISP_MEMSET(s_stHalIntf, 0, sizeof(s_stHalIntf));

    s_stHalIntf[HI_DRV_DISP_INTF_YPBPR0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_YPBPR0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_YPBPR0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_SVIDEO0].bSupport = HI_FALSE;
    s_stHalIntf[HI_DRV_DISP_INTF_SVIDEO0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_SVIDEO0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_CVBS0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_CVBS0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_CVBS0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_VGA0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_VGA0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_VGA0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_RGB0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_RGB0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_RGB0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_HDMI0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_HDMI0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_HDMI0].enChan = HI_DRV_DISPLAY_BUTT;

    s_stHalIntf[HI_DRV_DISP_INTF_LCD0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_LCD0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_LCD0].enChan = HI_DRV_DISPLAY_BUTT;
    s_stHalIntf[HI_DRV_DISP_INTF_BT1120_0].bSupport = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_BT1120_0].bIdle    = HI_TRUE;
    s_stHalIntf[HI_DRV_DISP_INTF_BT1120_0].enChan = HI_DRV_DISPLAY_BUTT;
    return;
}



HI_BOOL DISP_HAL_INTFNeedVenc(HI_DRV_DISP_INTF_ID_E eID)
{
    switch( eID)
    {
        case HI_DRV_DISP_INTF_YPBPR0:
        case HI_DRV_DISP_INTF_RGB0:
        case HI_DRV_DISP_INTF_SVIDEO0:
        case HI_DRV_DISP_INTF_CVBS0:
        case HI_DRV_DISP_INTF_VGA0:
            return HI_TRUE;
        default:
            return HI_FALSE;
    }
}

HI_S32 PF_AcquireIntf2(HI_DRV_DISPLAY_E enDisp, DISP_INTF_S *pstIf)
{
    HI_DRV_DISP_INTF_S *pstIntf = &pstIf->stIf;

    if(    !PF_TestIntfSupport(enDisp, pstIntf->eID)
        || !s_stHalIntf[pstIntf->eID].bSupport
        || !s_stHalIntf[pstIntf->eID].bIdle)
    {
    //DISP_ERROR("PF_AcquireIntf2*******************(%d)(%d)(%d)(%d)\n",enDisp,PF_TestIntfSupport(enDisp, pstIntf->eID),s_stHalIntf[pstIntf->eID].bSupport,s_stHalIntf[pstIntf->eID].bIdle);
        return HI_FAILURE;
    }
 //DISP_ERROR("PF_AcquireIntf2  ****(%d)(%d)(%d)***2\n", pstIntf->u8VDAC_Y_G, pstIntf->u8VDAC_Pb_B, pstIntf->u8VDAC_Pr_R);

    switch (pstIntf->eID)
    {
        case HI_DRV_DISP_INTF_YPBPR0:
        case HI_DRV_DISP_INTF_SVIDEO0:
        case HI_DRV_DISP_INTF_CVBS0:
        case HI_DRV_DISP_INTF_RGB0:
        case HI_DRV_DISP_INTF_VGA0:
            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                if (!DISP_HAL_VDACIsIdle(pstIntf->u8VDAC_Y_G))
                {
                    return HI_FAILURE;
                }
            }
            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                if (!DISP_HAL_VDACIsIdle(pstIntf->u8VDAC_Pb_B))
                {
                    return HI_FAILURE;
                }
            }
            if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
            {
                if (!DISP_HAL_VDACIsIdle(pstIntf->u8VDAC_Pr_R))
                {
                    return HI_FAILURE;
                }
            }
            //DISP_ERROR("PF_AcquireIntf2  ****(%d)(%d)(%d)***3\n", pstIntf->u8VDAC_Y_G, pstIntf->u8VDAC_Pb_B, pstIntf->u8VDAC_Pr_R);

        //acquire vdac
        if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
        {
            PF_AcquireVDAC(pstIntf->u8VDAC_Y_G);
        }

        if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
        {
            PF_AcquireVDAC(pstIntf->u8VDAC_Pb_B);
        }

        if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
        {
            PF_AcquireVDAC(pstIntf->u8VDAC_Pr_R);
            }
            break;
        default:
            break;
    }
    s_stHalIntf[pstIntf->eID].bIdle = HI_FALSE;
    s_stHalIntf[pstIntf->eID].enChan = enDisp;
    return HI_SUCCESS;
}

HI_S32 PF_ReleaseIntf2(HI_DRV_DISPLAY_E enDisp, DISP_INTF_S *pstIf)
{
    HI_DRV_DISP_INTF_S *pstIntf = &pstIf->stIf;
    if(    s_stHalIntf[pstIntf->eID].bSupport
        && !s_stHalIntf[pstIntf->eID].bIdle)
    {
        switch (pstIntf->eID)
        {
            case HI_DRV_DISP_INTF_YPBPR0:
            case HI_DRV_DISP_INTF_SVIDEO0:
            case HI_DRV_DISP_INTF_CVBS0:
            case HI_DRV_DISP_INTF_RGB0:
            case HI_DRV_DISP_INTF_VGA0:
                if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_ReleaseVDAC(pstIntf->u8VDAC_Y_G);
            }

            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                PF_ReleaseVDAC(pstIntf->u8VDAC_Pb_B);
            }

            if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
            {
                PF_ReleaseVDAC(pstIntf->u8VDAC_Pr_R);
    }
                break;

            default:
                break;
        }

        s_stHalIntf[pstIntf->eID].bIdle = HI_TRUE;
    s_stHalIntf[pstIntf->eID].enChan = HI_DRV_DISPLAY_BUTT;
    }

    return HI_SUCCESS;
}

VDP_DISP_INTF_E DISP_HAL_GetHalIntfId(HI_DRV_DISP_INTF_ID_E eIntf)
{
    switch (eIntf)
    {
        case HI_DRV_DISP_INTF_VGA0:
            return VDP_DISP_INTF_VGA;
        case HI_DRV_DISP_INTF_HDMI0:
            return VDP_DISP_INTF_HDMI;
        case HI_DRV_DISP_INTF_BT1120_0:
            return VDP_DISP_INTF_BT1120;
        case HI_DRV_DISP_INTF_LCD0:
            return VDP_DISP_INTF_LCD;
        default:
            return VDP_DISP_INTF_BUTT;
    }
}
/*
   hor = hsync + hbb + hact + hfb
   ver = vsync + vbb + vact + vfb
   Detect_line = vsync + x (x < vbb)
   or
   Detect_line = vsync + vbb + vact + x (x < vfb)
   Detect Pixel Start = hsync + hbb + x (x < hact)
*/
HI_S32 VDP_SetDACDET(DISP_VENC_E enDate,HI_DRV_DISP_FMT_E enFmt)
{
    HI_U32 u32DetLine = 0,u32DetPixelSta = 0;

    if(enDate >= DISP_VENC_MAX)
    {
        DISP_PRINT("enDate invalidation\n");
        return HI_FAILURE;
    }

    if ((enFmt < HI_DRV_DISP_FMT_861D_640X480_60)
        || ((enFmt >= HI_DRV_DISP_FMT_3840X2160_24)
           && (enFmt <= HI_DRV_DISP_FMT_1080i_59_94))
        )
    {
        switch(enFmt)
        {
            case HI_DRV_DISP_FMT_1080P_60:
                /*
                    HACT : 281 -2200
                    VFB  : 1122-1125
                    VBB  : 6   - 41
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;
                break;
            case HI_DRV_DISP_FMT_1080P_50:
                /*
                    HACT : 721 -2640
                    VFB  : 1122-1125
                    VBB  : 6   - 41
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;

                break;
            case HI_DRV_DISP_FMT_1080P_30:
                /*
                    HACT : 720 -2640
                    VFB  : 1122-1125
                    VBB  : 6   - 41
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;

                break;
             case HI_DRV_DISP_FMT_1080P_25:
                /*
                    HACT : 830 -2200
                    VFB  : 1122-1125
                    VBB  : 6   - 41
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;

                break;
             case HI_DRV_DISP_FMT_1080P_24:
                /*
                    HACT : 280 -2750
                    VFB  : 1122-1125
                    VBB  : 6   - 41
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;

                break;
            case HI_DRV_DISP_FMT_1080i_60:
                /*
                    HACT : 281 -2200
                    VFB  : 1124-1125
                    VBB  : 6   - 20
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;
                break;

            case HI_DRV_DISP_FMT_1080i_50:
                /*
                    HACT : 721 -2640
                    VFB  : 1124-1125
                    VBB  : 6   - 20
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;

                break;
            case HI_DRV_DISP_FMT_720P_60:
                /*
                    HACT : 371 -1650
                    VFB  : 746 - 750
                    VBB  : 6   - 25
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;
                break;
            case HI_DRV_DISP_FMT_720P_50:
                /*
                    HACT : 701 -1980
                    VFB  : 746 - 750
                    VBB  : 6   - 25
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 1000;
                break;
            case HI_DRV_DISP_FMT_576P_50:
                /*
                    HACT : 145 - 864
                    VFB  : 621 - 625
                    VBB  : 6   - 44
                    VPW  : 1 -5
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 600;

                break;
            case HI_DRV_DISP_FMT_480P_60:
                 /*
                    HACT : 139 - 858
                    VFB  : 523 - 525,525 - 6
                    VBB  : 13   - 42
                    VPW  : 7 -12
                */
                u32DetLine = 0x12;
                u32DetPixelSta = 600;
                break;
             case HI_DRV_DISP_FMT_PAL ... HI_DRV_DISP_FMT_1440x480i_60:
                u32DetLine = 10;
                u32DetPixelSta = 0x118;
                break;
             case HI_DRV_DISP_FMT_1080P_24_FP:
             case HI_DRV_DISP_FMT_720P_60_FP:
             case HI_DRV_DISP_FMT_720P_50_FP:
                /*when frame pack timing close dac*/
                u32DetLine = 0;
                u32DetPixelSta = 0;
                break;
             case HI_DRV_DISP_FMT_3840X2160_24:
             case HI_DRV_DISP_FMT_3840X2160_25:
             case HI_DRV_DISP_FMT_3840X2160_30:
             case HI_DRV_DISP_FMT_3840X2160_50:
             case HI_DRV_DISP_FMT_3840X2160_60:

             case HI_DRV_DISP_FMT_4096X2160_24:
             case HI_DRV_DISP_FMT_4096X2160_25:
             case HI_DRV_DISP_FMT_4096X2160_30:
             case HI_DRV_DISP_FMT_4096X2160_50:
             case HI_DRV_DISP_FMT_4096X2160_60:

             case HI_DRV_DISP_FMT_3840X2160_23_976:
             case HI_DRV_DISP_FMT_3840X2160_29_97:
             case HI_DRV_DISP_FMT_720P_59_94:
             case HI_DRV_DISP_FMT_1080P_59_94:
             case HI_DRV_DISP_FMT_1080P_29_97:
             case HI_DRV_DISP_FMT_1080P_23_976:
             case HI_DRV_DISP_FMT_1080i_59_94:
                /*when 4k*2k timing close dac*/
                u32DetLine = 0;
                u32DetPixelSta = 0;
                break;

             default :
                u32DetLine = 0;
                u32DetPixelSta = 0;
                break;
        }
        VDP_DATE_SetDACDET(enDate, u32DetLine, u32DetPixelSta);
    }
    else // VGA Timing
    {
    }

    return HI_SUCCESS;
}

HI_VOID DISP_HAL_SetSyncInv(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_INTF_ID_E eID,HI_DRV_DISP_FMT_E enFmt,HI_DRV_DISP_TIMING_S *pstCustomTimg)
{

    HI_S32 index;
    HI_U32 u32Vinv = 0,u32Hinv = 0;
    VDP_DISP_INTF_E enIntf = VDP_DISP_INTF_BUTT;
    VDP_DISP_SYNCINV_E enInv;
    DISP_FMT_CFG_S stCfg;
    memset(&enInv,0,sizeof(VDP_DISP_SYNCINV_E));
    memset(&stCfg,0,sizeof(DISP_FMT_CFG_S));

    if ((enFmt < HI_DRV_DISP_FMT_CUSTOM) && (enFmt > HI_DRV_DISP_FMT_1080P_60))
    {
        index = DispHalGetEnFmtIndex(enFmt);
       if  ( HI_SUCCESS != Get_FormatCfgPara(index ,&stCfg))
           return ;
       u32Hinv = (HI_U32) stCfg.stTiming.bIhs;
       u32Vinv = (HI_U32) stCfg.stTiming.bIvs;
    }
    else if (HI_DRV_DISP_FMT_CUSTOM == enFmt)
    {
        u32Hinv = (HI_U32) pstCustomTimg->bIHS;
        u32Vinv = (HI_U32) pstCustomTimg->bIVS;
    }
    else
    {
        u32Hinv = 0;
        u32Vinv = 0;
    }

    /*select  interface inv mode */
    switch (eID)
    {
        case HI_DRV_DISP_INTF_YPBPR0:
        case HI_DRV_DISP_INTF_RGB0:
        case HI_DRV_DISP_INTF_SVIDEO0:
        case HI_DRV_DISP_INTF_CVBS0:
            enInv.u32DatHinv = u32Hinv;
            enInv.u32DatVinv = u32Vinv;
            enIntf = VDP_DISP_INTF_DATE;
            break;
        case HI_DRV_DISP_INTF_VGA0:
            enInv.u32Vgahinv= u32Hinv;
            enInv.u32Vgavinv = u32Vinv;
            enIntf = VDP_DISP_INTF_VGA;
            break;
        case HI_DRV_DISP_INTF_HDMI0:
        case HI_DRV_DISP_INTF_HDMI1:
        case HI_DRV_DISP_INTF_HDMI2:
            enInv.u32Hdhinv= u32Hinv;
            enInv.u32Hdvinv = u32Vinv;
            enIntf = VDP_DISP_INTF_HDMI;
            break;
        case HI_DRV_DISP_INTF_LCD0:
        case HI_DRV_DISP_INTF_LCD1:
        case HI_DRV_DISP_INTF_LCD2:
            enInv.u32Lcdhinv= u32Hinv;
            enInv.u32Lcdvinv = u32Vinv;
            enIntf = VDP_DISP_INTF_LCD;
            break;
        case HI_DRV_DISP_INTF_BT1120_0:
        case HI_DRV_DISP_INTF_BT1120_1:
        case HI_DRV_DISP_INTF_BT1120_2:
            enIntf = VDP_DISP_INTF_BT1120;
            break;
        default:
            enIntf = VDP_DISP_INTF_BUTT;
            break;
    }

    //DISP_ERROR("disp%d,enIntf %d----(%d,%d)\n",enDisp,enIntf,u32Hinv,u32Vinv);
    VDP_DISP_SetSyncInv(DISP_HAL_GetChID(enDisp),enIntf,enInv);
}

HI_S32 PF_ResetIntfFmt2(HI_DRV_DISPLAY_E enDisp, DISP_INTF_S *pstIf, HI_DRV_DISP_FMT_E eFmt,HI_DRV_DISP_TIMING_S *pstCustomTimg)
{
    HI_DRV_DISP_INTF_S *pstIntf = &pstIf->stIf;
    VDP_DISP_INTF_E enVdpIntf;

    /*judge enVdpIntf and Venc link
    */
    if (eFmt >= HI_DRV_DISP_FMT_BUTT)
    {
        DISP_ERROR("eFmt out of range.\n");
        return HI_FAILURE;
    }

    enVdpIntf = DISP_HAL_GetHalIntfIdForVenc(enDisp,pstIf,eFmt);
    VDP_SetDACDET(pstIf->eVencId,eFmt);

    if (VDP_DISP_INTF_SDDATE == enVdpIntf )
    {
        /*SDate attach to DHD1 all the time.*/
        VDP_DISP_SetIntfMuxSel(DISP_HAL_GetChID(HI_DRV_DISPLAY_0), enVdpIntf);
    }
    else
        VDP_DISP_SetIntfMuxSel(DISP_HAL_GetChID(enDisp), enVdpIntf);

    if ( pstIf->bLinkVenc)
    {
        // s2 add venc to disp
#ifdef __DISP_D0_FOLLOW_D1__
        if ( (HI_DRV_DISPLAY_1 == enDisp) && (pstIf->eVencId == DISP_VENC_SDATE0) )
        {
            // nothing todo
        }
        else
        {
            //s3 reset venc format
            VDP_DATE_ResetFmt(pstIf->eVencId, eFmt);
        }
#else

        VDP_DATE_ResetFmt(pstIf->eVencId, eFmt);
#endif
    }
        // s4 add vdac to venc

    DISP_HAL_SetSyncInv(enDisp,pstIf->stIf.eID,eFmt,pstCustomTimg);
    //add rgb and Ypbpr interface
    if ((HI_DRV_DISP_INTF_RGB0 == pstIf->stIf.eID) || (HI_DRV_DISP_INTF_YPBPR0== pstIf->stIf.eID))
    {
        VDP_DATE_SetSignal(pstIf->stIf.eID,pstIf->eVencId,pstIntf->bDacSync);
    }
    switch (pstIf->stIf.eID)
    {
        case HI_DRV_DISP_INTF_YPBPR0:

            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Y_G, HI_DRV_DISP_VDAC_Y);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Y_G, eFmt,pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pb_B, HI_DRV_DISP_VDAC_PB);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pb_B, eFmt,pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pr_R, HI_DRV_DISP_VDAC_PR);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pr_R, eFmt, pstCustomTimg->u32PixFreq);
            }
            break;
        case HI_DRV_DISP_INTF_RGB0:
            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Y_G, HI_DRV_DISP_VDAC_G);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Y_G, eFmt, pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pb_B, HI_DRV_DISP_VDAC_B);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pb_B, eFmt, pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pr_R, HI_DRV_DISP_VDAC_R);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pr_R, eFmt, pstCustomTimg->u32PixFreq);
            }
            break;

        case HI_DRV_DISP_INTF_CVBS0:

            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Y_G, HI_DRV_DISP_VDAC_CVBS);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Y_G, eFmt, pstCustomTimg->u32PixFreq);
            }
            break;

        case HI_DRV_DISP_INTF_SVIDEO0:

            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pb_B, HI_DRV_DISP_VDAC_SV_Y);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pb_B, eFmt, pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pr_R, HI_DRV_DISP_VDAC_SV_C);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pr_R, eFmt, pstCustomTimg->u32PixFreq);
            }
            break;

        case HI_DRV_DISP_INTF_VGA0:
            if (pstIntf->u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Y_G, HI_DRV_DISP_VDAC_G);

                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Y_G, eFmt, pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pb_B, HI_DRV_DISP_VDAC_B);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pb_B, eFmt, pstCustomTimg->u32PixFreq);
            }

            if (pstIntf->u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
            {
                PF_AddVDacToVenc(enDisp,pstIf->eVencId, pstIntf->u8VDAC_Pr_R, HI_DRV_DISP_VDAC_R);
                VDP_VDAC_ResetFmt(pstIf->eVencId, pstIntf->u8VDAC_Pr_R, eFmt, pstCustomTimg->u32PixFreq);
            }

            break;
        case HI_DRV_DISP_INTF_HDMI0:
            /*select hdmi corlor space
                vdp set  yuv ,so need  hdmi judge whether  use CSC yuv to rgb;*/

            if  ((eFmt >= HI_DRV_DISP_FMT_861D_640X480_60) && (eFmt < HI_DRV_DISP_FMT_3840X2160_24))
            {
                pstIf ->enHDMIDataType = DISP_HDMI_DATA_RGB;
            }
            else
            {
                pstIf ->enHDMIDataType = DISP_HDMI_DATA_YUV;
            }

            if  ((eFmt >= HI_DRV_DISP_FMT_PAL) && (eFmt <= HI_DRV_DISP_FMT_1440x480i_60) )
            {
                /*SD format */
                /*clk : 1:2*/
                VDP_DISP_SetHdmiClk(DISP_HAL_GetChID(enDisp),1);
            }
            else
            {
                /*clk : 1:1*/
                VDP_DISP_SetHdmiClk(DISP_HAL_GetChID(enDisp),0);
            }

            VDP_DISP_SetHdmiMode(DISP_HAL_GetChID(enDisp), pstIf->enHDMIDataType);

#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100) || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
            VDP_DISP_SetDataSel(DISP_HAL_GetChID(enDisp), pstIf->enHDMIDataType);
#endif
            VDP_DISP_SetRegUp(DISP_HAL_GetChID(enDisp));

            break;
        case HI_DRV_DISP_INTF_BT656_0:
        case HI_DRV_DISP_INTF_BT1120_0:
        case HI_DRV_DISP_INTF_LCD0:
            break;

        default:
            return VDP_DISP_INTF_BUTT;
    }


    return HI_SUCCESS;
}

#if 0
HI_S32 PF_AddIntfToDisp(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_INTF_ID_E eIntf)
{
    VDP_DISP_SetIntfMuxSel(DISP_HAL_GetChID(enDisp),
                           DISP_HAL_GetHalIntfId(eIntf));

    return HI_SUCCESS;
}

HI_S32 PF_SetIntfColor(HI_DRV_DISP_INTF_ID_E eIntf, DISP_HAL_COLOR_S *pstColor)
{

    return HI_SUCCESS;
}
#endif
#define DEF_DISP_Y_VDAC_DELAY 40
#define DEF_DISP_PB_VDAC_DELAY 20
#define DEF_DISP_PR_VDAC_DELAY 20

HI_S32 PF_SetIntfEnable2(HI_DRV_DISPLAY_E enDisp, DISP_INTF_S *pstIt, HI_BOOL bEnable)
{
    DISP_VENC_E enVencId = DISP_VENC_MAX;
    /* switch fmt process:
        attach mode :
            step1: close HD  adn SD interface
            step2: switch format
            step3: open  HD  adn SD interface,
        no attach mode :
            step1: close HD/SD interface
            step2: switch format
            step3: open HD/SD interface,
        but in  no attach mode:
            if disp1 switch format  HDFmt -->SDFmt ,
            step1: close hdate
            step2: switch format
            step3: open sdate,
            SDFmt -->HDFmt has the same bug;
            so should process disp  by channel;
    */

    if (pstIt->bLinkVenc)
    {
        if ( HI_DRV_DISPLAY_0 == enDisp )
            enVencId = DISP_VENC_SDATE0;
        else if  (HI_DRV_DISPLAY_1 == enDisp )
            enVencId = DISP_VENC_HDATE0;
        else
            enVencId = DISP_VENC_MAX;

#if !defined(DAC_TYPE_HISI_VOLTAGE)
		/*closed DAC Det*/
        VDP_DATE_SetDACDetEn(enVencId, 0);
#else
        if (g_stVDACAttr.bDACDetEn)
        {
            VDP_DATE_SetDACDetEn(enVencId, (HI_U32)bEnable);
        }
        else
        {
            VDP_DATE_SetDACDetEn(enVencId, 0);
        }
#endif

    }

    // set vdac link
    if (pstIt->stIf.u8VDAC_Y_G != HI_DISP_VDAC_INVALID_ID)
    {
        if (pstIt->stIf.u8VDAC_Y_G >= sizeof(g_stVDACAttr.stDACState)/sizeof(HI_DRV_VDAC_STATE_S))
        {
            DISP_ERROR("pstIt->stIf.u8VDAC_Y_G is too big:%d!\n", pstIt->stIf.u8VDAC_Y_G);
            return HI_FAILURE;
        }

        if (DISP_VENC_VGA0 == pstIt->eVencId)
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Y_G].bDACDetectEn = HI_FALSE;
        else
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Y_G].bDACDetectEn = bEnable;

        if (bEnable)
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Y_G, bEnable, 0);
        }
        else
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Y_G, bEnable, DEF_DISP_Y_VDAC_DELAY);
        }
    }



    if (pstIt->stIf.u8VDAC_Pb_B != HI_DISP_VDAC_INVALID_ID)
    {
        if (pstIt->stIf.u8VDAC_Pb_B >= sizeof(g_stVDACAttr.stDACState)/sizeof(HI_DRV_VDAC_STATE_S))
        {
            DISP_ERROR("pstIt->stIf.u8VDAC_Pb_B is too big.\n");
            return HI_FAILURE;
        }

        if (DISP_VENC_VGA0 == pstIt->eVencId)
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Pb_B].bDACDetectEn = HI_FALSE;
        else
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Pb_B].bDACDetectEn = bEnable;
        if (bEnable)
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Pb_B, bEnable,0);
        }
        else
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Pb_B, bEnable,DEF_DISP_PB_VDAC_DELAY);
        }
    }



    if (pstIt->stIf.u8VDAC_Pr_R != HI_DISP_VDAC_INVALID_ID)
    {
        if (pstIt->stIf.u8VDAC_Pr_R >= sizeof(g_stVDACAttr.stDACState)/sizeof(HI_DRV_VDAC_STATE_S))
        {
            DISP_ERROR("pstIt->stIf.u8VDAC_Pr_R is too big.\n");
            return HI_FAILURE;
        }

        if (DISP_VENC_VGA0 == pstIt->eVencId)
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Pr_R].bDACDetectEn = HI_FALSE;
        else
            g_stVDACAttr.stDACState[pstIt->stIf.u8VDAC_Pr_R].bDACDetectEn = bEnable;

        if (bEnable)
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Pr_R, bEnable,0);
        }
        else
        {
            PF_SetVDACEnable(pstIt->stIf.u8VDAC_Pr_R, bEnable,DEF_DISP_PB_VDAC_DELAY);
        }
    }

    return HI_SUCCESS;
}





/*===========================================================*/
/* WBC manager */
HI_VOID InitWbcState(HI_VOID)
{
    DISP_WBC_E eID;

    for(eID = DISP_WBC_00; eID < DISP_WBC_BUTT; eID++)
    {
        s_stWBC[eID].bSupport = HI_TRUE;
        s_stWBC[eID].bIdle    = HI_TRUE;
    }

    return;
}


HI_S32 PF_AcquireWbcByChn(HI_DRV_DISPLAY_E eChn, DISP_WBC_E *peWbc)
{
    if (eChn == HI_DRV_DISPLAY_1)
    {
        if(  (s_stWBC[DISP_WBC_00].bSupport == HI_TRUE)
            &&(s_stWBC[DISP_WBC_00].bIdle == HI_TRUE)
            )
        {
            s_stWBC[DISP_WBC_00].bIdle = HI_FALSE;
            s_stWBC[DISP_WBC_00].u32RefCnt = 1;
            *peWbc = DISP_WBC_00;
            return HI_SUCCESS;
        } else if ((s_stWBC[DISP_WBC_00].bSupport == HI_TRUE)
            &&(s_stWBC[DISP_WBC_00].bIdle == HI_FALSE))
        {
            s_stWBC[DISP_WBC_00].u32RefCnt++;
            *peWbc = DISP_WBC_00;
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;
}

HI_S32 PF_AcquireWbc(DISP_WBC_E eWbc)
{
    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }
    if(  (s_stWBC[eWbc].bSupport == HI_TRUE)
        &&(s_stWBC[eWbc].bIdle == HI_TRUE)
        )
    {
        s_stWBC[eWbc].bIdle = HI_FALSE;
        s_stWBC[eWbc].u32RefCnt = 1;
        return HI_SUCCESS;
    } else if ((s_stWBC[eWbc].bSupport == HI_TRUE)
        &&(s_stWBC[eWbc].bIdle == HI_FALSE))
    {
        s_stWBC[eWbc].u32RefCnt ++;
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 PF_ReleaseWbc(DISP_WBC_E eWbc)
{
    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }
    if(  (s_stWBC[eWbc].bSupport == HI_TRUE)
        &&(s_stWBC[eWbc].bIdle == HI_FALSE)
        )
    {
        if (--s_stWBC[eWbc].u32RefCnt == 0)
        s_stWBC[eWbc].bIdle = HI_TRUE;
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}


#ifndef __DISP_PLATFORM_BOOT__
static VDP_LAYER_WBC_E s_eWbcHalID[DISP_WBC_BUTT] =
{VDP_LAYER_WBC_HD0};
#endif

/* WBC */
HI_S32 PF_SetWbcDefault(DISP_WBC_E eWbc)
{
    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }

#ifndef __DISP_PLATFORM_BOOT__
    VDP_WBC_SetOutIntf(s_eWbcHalID[eWbc], VDP_RMODE_PROGRESSIVE);
    VDP_WBC_SetZmeInFmt_Define1(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
#endif

    return HI_SUCCESS;
}

#ifndef __DISP_PLATFORM_BOOT__
static HI_S32 HAL_ReviseWbcZmeInput(DISP_WBC_E eWbc, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_U32 *u32Width, HI_U32 *u32Height)
{
    return Chip_Specific_ReviseWbcZmeInput(eWbc, pstDispInfo, u32Width, u32Height);
}
#endif


HI_S32 PF_SetWbc3DInfo(DISP_WBC_E eWbc, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_RECT_S *in)
{
    #ifndef __DISP_PLATFORM_BOOT__
    return Chip_Specific_SetWbc3DInfo(eWbc, pstDispInfo, in);
    #else
    return HI_SUCCESS;
    #endif
}

HI_S32 PF_SetWbcIORect(DISP_WBC_E eWbc, HI_DISP_DISPLAY_INFO_S *pstDispInfo, HI_RECT_S *in, HI_RECT_S *out)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_DISP_RECT_S stRect;
    HI_PQ_ZME_PARA_IN_S stZmeI;
    HI_U32 pbBtm = 0, pu32Vcnt = 0;
    HI_BOOL bAlwayPro = HI_FALSE;

    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }

    DISP_MEMSET(&stRect, 0, sizeof(VDP_DISP_RECT_S));
    DISP_MEMSET(&stZmeI, 0, sizeof(HI_PQ_ZME_PARA_IN_S));

    stRect.u32DXS = (HI_U32)in->s32X;
    stRect.u32DYS = (HI_U32)in->s32Y;
    stRect.u32DXL = (HI_U32)in->s32Width + stRect.u32DXS;
    stRect.u32DYL = (HI_U32)in->s32Height  + stRect.u32DYS;

    stRect.u32OWth = (HI_U32)out->s32Width;
    stRect.u32OHgt = (HI_U32)out->s32Height;
    VDP_WBC_SetLayerReso(s_eWbcHalID[eWbc], stRect);

    /*wbc we fix to progressive.*/
    VDP_WBC_SetOutIntf(s_eWbcHalID[eWbc], VDP_RMODE_PROGRESSIVE);

    stZmeI.u32ZmeFrmWIn = in->s32Width;
    stZmeI.u32ZmeFrmHIn = in->s32Height;
    HAL_ReviseWbcZmeInput(eWbc, pstDispInfo, &stZmeI.u32ZmeFrmWIn, &stZmeI.u32ZmeFrmHIn);

    stZmeI.u32ZmeFrmWOut = (HI_U32)out->s32Width;
    stZmeI.u32ZmeFrmHOut = (HI_U32)out->s32Height;

    stZmeI.u8ZmeYCFmtIn  = 0; /*zme in is always 422.*/
    stZmeI.u8ZmeYCFmtOut = 1; /*zme out is 420 in wbc for encoder,
                               other condition  422 may be neccessary,but ip not validated.*/

    /*Pay attention, although we set frame width to ip,
      but here we should pass real filed mode to alg.*/
    (HI_VOID)VDP_WBC_GetAlwaysProFlag(/*eWbc,*/ &bAlwayPro);

    if (bAlwayPro == 0)
    {
        if (0 == VDP_DHD_GetDispMode(0)){
            /*since this configure will take affect next intr,so opposite it.*/
            VDP_DISP_GetVactState(0, &pbBtm, &pu32Vcnt);
            pbBtm = 1 - pbBtm;
            stZmeI.bZmeFrmFmtIn  = 0;
            stZmeI.bZmeBFIn  = pbBtm;
        } else {
            stZmeI.bZmeFrmFmtIn  = 1;
            stZmeI.bZmeBFIn  = 0;
        }

    } else {
        /*in cv200, always progressive.*/
        stZmeI.bZmeFrmFmtIn = 1;
        stZmeI.bZmeBFIn  = 0;
    }

    /*wbc output fix to 1, frame.*/
    stZmeI.bZmeFrmFmtOut = 1;
    stZmeI.bZmeBFOut = 0;

    if (HI_SUCCESS != Chip_Specific_WbcZmeFunc(HI_PQ_DISP_WBC0_LAYER_ZME, &stZmeI,HI_TRUE))
        return HI_FAILURE;
#endif

    return HI_SUCCESS;
}

HI_S32 PF_SetWbcColorSpace(DISP_WBC_E eWbc, HI_DRV_COLOR_SPACE_E eSrcCS, HI_DRV_COLOR_SPACE_E eDstCS)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_CSC_DC_COEF_S stDcCoef;
    VDP_CSC_COEF_S stCoef;
    HI_PQ_CSC_MODE_E enCSCMode = HI_PQ_CSC_BUTT;

   if (eWbc >= DISP_WBC_BUTT)
   {
       DISP_ERROR("eWbc out of range.\n");
       return HI_FAILURE;
   }

   switch(eSrcCS)
   {
    case HI_DRV_CS_BT601_YUV_LIMITED:
        switch (eDstCS)
        {
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV_601_709;
                break;
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV;
                break;
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_601;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT601_YUV_FULL:
        switch (eDstCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_601;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
     case HI_DRV_CS_BT709_YUV_LIMITED:
        switch (eDstCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_709;
                break;
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV_709_601;
                break;
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_YUV2YUV;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT709_YUV_FULL:
        switch (eDstCS)
        {
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_YUV2RGB_709_FULL;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
    case HI_DRV_CS_BT709_RGB_FULL:
        switch (eDstCS)
        {
            case HI_DRV_CS_BT601_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_RGB2YUV_601;
                break;
            case HI_DRV_CS_BT601_YUV_FULL:
                enCSCMode = HI_PQ_CSC_RGB2YUV_601_FULL;
                break;
            case HI_DRV_CS_BT709_YUV_LIMITED:
                enCSCMode = HI_PQ_CSC_RGB2YUV_709;
                break;
            case HI_DRV_CS_BT709_YUV_FULL:
                enCSCMode = HI_PQ_CSC_RGB2YUV_709_FULL;
                break;
            case HI_DRV_CS_BT709_RGB_FULL:
                enCSCMode = HI_PQ_CSC_RGB2RGB;
                break;
            default:
                enCSCMode = HI_PQ_CSC_BUTT;
                break;
        }
        break;
     default:
        break;
    }

    DRV_PQ_Get8BitCSCCoef(enCSCMode, (HI_PQ_CSC_COEF_S*)&stCoef, (HI_PQ_CSC_DCCOEF_S*)&stDcCoef);

    if (eSrcCS == eDstCS)
    {
        VDP_WBC_SetCscEnable(s_eWbcHalID[eWbc], HI_FALSE);
    }
    else
    {
        VDP_WBC_SetCscDcCoef(s_eWbcHalID[eWbc], stDcCoef);
        VDP_WBC_SetCscCoef(s_eWbcHalID[eWbc],stCoef);
        VDP_WBC_SetCscEnable(s_eWbcHalID[eWbc], HI_TRUE);
    }

#endif

    return HI_SUCCESS;
}

HI_S32 PF_SetWbcPixFmt(DISP_WBC_E eWbc, HI_DRV_PIX_FORMAT_E eFmt)
{
#ifndef __DISP_PLATFORM_BOOT__

    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }

    switch(eFmt)
    {
        case HI_DRV_PIX_FMT_NV21:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_SP420);
            VDP_WBC_SetOutFmtUVOrder(s_eWbcHalID[eWbc], 0);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_420);
            break;
        case HI_DRV_PIX_FMT_NV12:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_SP420);
            VDP_WBC_SetOutFmtUVOrder(s_eWbcHalID[eWbc], 1);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_420);
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_SP422);
            VDP_WBC_SetOutFmtUVOrder(s_eWbcHalID[eWbc], 0);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
            break;
        case HI_DRV_PIX_FMT_NV16_2X1:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_SP422);
            VDP_WBC_SetOutFmtUVOrder(s_eWbcHalID[eWbc], 1);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
            break;
        case HI_DRV_PIX_FMT_YUYV:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_PKG_YUYV);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
            break;
        case HI_DRV_PIX_FMT_UYVY:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_PKG_UYVY);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
            break;
        case HI_DRV_PIX_FMT_YVYU:
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_PKG_YVYU);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_422);
            break;
        default :
            DISP_FATAL("set cast format %d fail\n",eFmt);
            VDP_WBC_SetOutFmt(s_eWbcHalID[eWbc], VDP_WBC_OFMT_SP420);
            VDP_WBC_SetOutFmtUVOrder(s_eWbcHalID[eWbc], 0);
            VDP_WBC_SetZmeOutFmt(s_eWbcHalID[eWbc], VDP_PROC_FMT_SP_420);
            break;
    }

#endif

    return HI_SUCCESS;
}

HI_S32 PF_SetWbcAddr(DISP_WBC_E eWbc, HI_DRV_VID_FRAME_ADDR_S *pstAddr)
{
#ifndef __DISP_PLATFORM_BOOT__

    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }

    VDP_WBC_SetLayerAddr(s_eWbcHalID[eWbc],
                         pstAddr->u32PhyAddr_Y, pstAddr->u32PhyAddr_C,
                         pstAddr->u32Stride_Y, pstAddr->u32Stride_C);
#endif
    return HI_SUCCESS;
}

HI_S32 PF_SetWbcEnable(DISP_WBC_E eWbc, HI_BOOL bEnable)
{
#ifndef __DISP_PLATFORM_BOOT__

    if (eWbc >= DISP_WBC_BUTT)
    {
        DISP_ERROR("eWbc out of range.\n");
        return HI_FAILURE;
    }

    VDP_WBC_SetEnable(s_eWbcHalID[eWbc], (HI_U32)bEnable);
#endif
    return HI_SUCCESS;
}

HI_S32 PF_SetWbcLowdlyEnable(DISP_WBC_E eWbc, HI_BOOL bEnable)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_WBC_SetLowdlyEnable(s_eWbcHalID[eWbc], (HI_U32)bEnable);
#endif
    return HI_SUCCESS;
}

HI_S32  PF_SetWbcPartfnsLineNum(DISP_WBC_E eWbc, HI_U32 u32LineNum)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_WBC_SetPartfnsLineNum(s_eWbcHalID[eWbc], u32LineNum);
#endif

    return HI_SUCCESS;
}

HI_S32  PF_SetWbcLineNumInterval(DISP_WBC_E eWbc, HI_U32 u32Interval)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_WBC_SetWbPerLineNum(s_eWbcHalID[eWbc], u32Interval);
#endif

    return HI_SUCCESS;
}

HI_S32 PF_SetWbcLineAddr(DISP_WBC_E eWbc, HI_U32 u32Addr)
{

#ifndef __DISP_PLATFORM_BOOT__
        VDP_WBC_SetTunlCellAddr(s_eWbcHalID[eWbc], u32Addr);
#endif
        return HI_SUCCESS;
}
HI_S32 PF_UpdateWbc(DISP_WBC_E eWbc)
{
#ifndef __DISP_PLATFORM_BOOT__
    VDP_WBC_SetRegUp(s_eWbcHalID[eWbc]);
#endif
    return HI_SUCCESS;
}

HI_S32 PF_CBM_MovTOP(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_LAYER_E enLayer)
{
    return Chip_Specific_CBM_MovTOP(enDisp,enLayer);
}

HI_S32 PF_VDP_RegSave(HI_VOID)
{
    HI_U32 nRet;
    nRet = DISP_OS_MMZ_Map(&g_RegBackBuf);
    if (HI_SUCCESS == nRet)
    {
        VDP_RegSave(g_RegBackBuf.u32StartVirAddr);
        DISP_OS_MMZ_UnMap(&g_RegBackBuf);
    }
    else
    {
        DISP_FATAL("save reg buffer mmz mmp fail\n");
        return HI_ERR_DISP_MALLOC_MAP_ERR;
    }
    return HI_SUCCESS;
}
HI_S32 PF_VDP_RegReStore(HI_VOID)
{
    HI_U32 nRet;
    nRet = DISP_OS_MMZ_Map(&g_RegBackBuf);
    if (HI_SUCCESS == nRet)
    {
        VDP_RegReStore(g_RegBackBuf.u32StartVirAddr);
        DISP_OS_MMZ_UnMap(&g_RegBackBuf);
    }
    else
    {
        DISP_FATAL("restore reg buffer mmz mmp fail\n");
        return HI_ERR_DISP_MALLOC_MAP_ERR;
    }
    return HI_SUCCESS;
}

//interrupt
#define DAC_B    0x1           //DAC3
#define DAC_R    0x2           //DAC1
#define DAC_G    0x4           //DAC2
#define DAC_CVBS 0x8           //DAC0

/*******************************************
interrupt           vo dac ctrl
DAC0    ---------->> VDAC3    0xf8cc013c
DAC1    ---------->> VDAC0    0xf8cc0130
DAC2    ---------->> VDAC1    0xf8cc0134
DAC3    ---------->> VDAC2    0xf8cc0138
********************************************/

HI_S32 DAC_PoweDown(HI_U8 u8DAC)
{
    HI_U32 s32Enable = 0;

    if (u8DAC >= sizeof(g_stVDACAttr.stDACState)/sizeof(HI_DRV_VDAC_STATE_S))
    {
        DISP_ERROR("u8DAC out of range.\n");
        return HI_FAILURE;
    }

    if(!g_stVDACAttr.stDACState[u8DAC].bDACDetectEn)
    {
        return HI_SUCCESS;
    }

    VDP_VDAC_GetEnable(u8DAC, &s32Enable);
    if(s32Enable)
    {
        VDP_VDAC_SetEnable(u8DAC, HI_FALSE,0);
    }
    return HI_SUCCESS;
}

HI_S32 DAC_PoweUp(HI_U8 u8DAC)
{
    HI_U32 s32Enable = 0;
    if(!g_stVDACAttr.stDACState[u8DAC].bDACDetectEn)
    {
        return HI_SUCCESS;
    }

    VDP_VDAC_GetEnable(u8DAC, &s32Enable);
    if(!s32Enable)
    {
        VDP_VDAC_SetEnable(u8DAC, HI_TRUE,0);
    }
    return HI_SUCCESS;
}
static HI_U32 g_u32RecordTime = 0;
#define WAKEUP_TIMER_MS 2000
#define POWERDOWN_TIMRR_MS 100
#define POWERUP_EVENT    1
#define POWERDOWN_EVENT  2

HI_VOID InitDacDetectStatus(HI_U32 u32Index,HI_BOOL bEnable)
{
    if (u32Index >= HI_DISP_VDAC_MAX_NUMBER)
        return;
    //DISP_ERROR("dac--init detect -----(%d)=============%d\n",u32Index,bEnable);
    g_stVDACAttr.stDACState[u32Index].bDACDetectEn = bEnable;
}

HI_S32 PF_InitDacDetect( HI_DRV_DISP_INTF_S *pstIf)
{
    HI_BOOL bEnable = HI_FALSE;

    if (HI_DRV_DISP_INTF_VGA0 == pstIf->eID)
    {
        InitDacDetectStatus(pstIf->u8VDAC_Y_G,HI_FALSE);
        InitDacDetectStatus(pstIf->u8VDAC_Pb_B,HI_FALSE);
        InitDacDetectStatus(pstIf->u8VDAC_Pr_R,HI_FALSE);
    }
    else
    {
        VDP_VDAC_GetEnable(pstIf->u8VDAC_Y_G, &bEnable);
        InitDacDetectStatus(pstIf->u8VDAC_Y_G,bEnable);

        VDP_VDAC_GetEnable(pstIf->u8VDAC_Pb_B, &bEnable);
        InitDacDetectStatus(pstIf->u8VDAC_Pb_B,bEnable);

        VDP_VDAC_GetEnable(pstIf->u8VDAC_Pr_R, &bEnable);
        InitDacDetectStatus(pstIf->u8VDAC_Pr_R,bEnable);
    }
    return HI_SUCCESS;
}

HI_U32 GetTimerStatus(HI_VOID)
{
    HI_S32 u32Time = 0,u32TimeDiff = 0;
    DISP_OS_GetTime((HI_U32 *)&u32Time);

    u32TimeDiff = u32Time - g_u32RecordTime;
    if(u32TimeDiff >= WAKEUP_TIMER_MS)
    {
        g_u32RecordTime = u32Time;
        return POWERUP_EVENT;
    }
    else if (u32TimeDiff >= POWERDOWN_TIMRR_MS)
    {
        return POWERDOWN_EVENT;
    }
    else
    {
        //void
    }

    return HI_SUCCESS;
}

HI_S32 PF_SetDACDetEn (HI_BOOL bDACDetEn)
{
    g_stVDACAttr.bDACDetEn = bDACDetEn;

#if !defined(DAC_TYPE_HISI_VOLTAGE)
	/*closed DAC Det*/
    VDP_DATE_SetDACDetEn(DISP_VENC_HDATE0, 0);
    VDP_DATE_SetDACDetEn(DISP_VENC_SDATE0, 0);
#else
    VDP_DATE_SetDACDetEn(DISP_VENC_HDATE0, bDACDetEn);
    VDP_DATE_SetDACDetEn(DISP_VENC_SDATE0, bDACDetEn);
#endif

    return HI_SUCCESS;
}

HI_S32 PF_GetDACAttr(HI_DRV_VDAC_ATTR_S *pDACAttr)
{
    *pDACAttr = g_stVDACAttr;
    return HI_SUCCESS;
}

HI_S32 PF_DACIsr(HI_U8 u8DAC)
{
    HI_U8 u8Data,u32Event;
    //return;
    //    g_stVDACAttr.bDAC2State,g_stVDACAttr.bDAC3State);
    if(!g_stVDACAttr.bDACDetEn)
    {
        return HI_SUCCESS;
    }

    u8Data = u8DAC&DAC_CVBS;
    u32Event =  GetTimerStatus();
   // DISP_ERROR("dac:0x%x,event:0x%d\n",u8DAC,u32Event);
    if(!u8Data)
    {
        if(POWERDOWN_EVENT == u32Event)
        {
            DAC_PoweDown(DAC_B_CTRL);
            g_stVDACAttr.stDACState[DAC_B_CTRL].bDACPlugIn = HI_FALSE;
        }
    }
    else
    {
        g_stVDACAttr.stDACState[DAC_B_CTRL].bDACPlugIn = HI_TRUE;
    }

    u8Data = u8DAC&DAC_R;
    if(!u8Data)
    {
        if(POWERDOWN_EVENT == u32Event)
        {
            DAC_PoweDown(DAC_R_CTRL);
            g_stVDACAttr.stDACState[DAC_R_CTRL].bDACPlugIn = HI_FALSE;
        }
    }
    else
    {
        g_stVDACAttr.stDACState[DAC_R_CTRL].bDACPlugIn = HI_TRUE;
    }

    u8Data = u8DAC&DAC_G;
    if(!u8Data)
    {
        if(POWERDOWN_EVENT == u32Event)
        {
            DAC_PoweDown(DAC_G_CTRL);
            g_stVDACAttr.stDACState[DAC_G_CTRL].bDACPlugIn = HI_FALSE;
        }
    }
    else
    {
        g_stVDACAttr.stDACState[DAC_G_CTRL].bDACPlugIn = HI_TRUE;
    }

    u8Data = u8DAC&DAC_B;
    if(!u8Data)
    {
        if(POWERDOWN_EVENT == u32Event)
        {
            DAC_PoweDown(DAC_C_CTRL);
            g_stVDACAttr.stDACState[DAC_C_CTRL].bDACPlugIn = HI_FALSE;
        }
    }
    else
    {
        g_stVDACAttr.stDACState[DAC_C_CTRL].bDACPlugIn = HI_TRUE;
    }

    if(POWERUP_EVENT == u32Event)
    {
        DAC_PoweUp(DAC_R_CTRL);
        DAC_PoweUp(DAC_G_CTRL);
        DAC_PoweUp(DAC_B_CTRL);
        DAC_PoweUp(DAC_C_CTRL);
        PF_CleanIntState(VDAC_STATE_INT);//clear status
    }

    //DISP_ERROR("dac:%d/%d/%d/%d\n",g_stVDACAttr.stDAC0State.bDACPlugIn,g_stVDACAttr.stDAC1State.bDACPlugIn,
    //   g_stVDACAttr.stDAC2State.bDACPlugIn,g_stVDACAttr.stDAC3State.bDACPlugIn);
    return HI_SUCCESS;
}

/*==============================================*/
HI_VOID DispGetVersion(HI_DRV_DISP_VERSION_S * pVersion)
{
    Chip_Specific_GetVersion(pVersion);
    return;
}



HI_S32 PF_DATE_SetCoef(HI_DRV_DISPLAY_E enDisp, HI_S32 u32Index)
{
    if (HI_DRV_DISPLAY_0 != enDisp)
        return HI_FAILURE;

    VDP_DATE_SetSrcCoef(DISP_VENC_SDATE0, VDP_Get_SDateSrcCoef(u32Index));

    return HI_SUCCESS;
}

HI_S32 PF_DATE_SetIRE(HI_DRV_DISPLAY_E enDisp, HI_U32 u32IRE)
{
    if (HI_DRV_DISPLAY_0 != enDisp)
        return HI_FAILURE;

    SDATE_SetIreEn(u32IRE);
    return HI_SUCCESS;
}
HI_S32 PF_SetAllDACEn (HI_BOOL bDACEn)
{
    if (bDACEn)
    {
        DAC_PoweUp(DAC_C_CTRL);
        DAC_PoweUp(DAC_R_CTRL);
        DAC_PoweUp(DAC_G_CTRL);
        DAC_PoweUp(DAC_B_CTRL);
    }
    else
    {
        DAC_PoweDown(DAC_C_CTRL);
        DAC_PoweDown(DAC_R_CTRL);
        DAC_PoweDown(DAC_G_CTRL);
        DAC_PoweDown(DAC_B_CTRL);
    }

    return HI_SUCCESS;
}

HI_S32 DISP_HAL_Init(HI_U32 u32Base)
{
    HI_S32 nRet;

    // s1 if input version
    if(s_DispIntfFlag > 0)
    {
        return HI_SUCCESS;
    }

    // s1.2 open vdp clock.
    nRet = Chip_Specific_DISP_OpenClock();
    if (nRet != HI_SUCCESS)
    {
        return nRet;
    }

    s_u32VdpBaseAddr = (HI_U32)DISP_IOADDRESS(u32Base);

    if (!s_u32VdpBaseAddr)
    {
        return HI_FAILURE;
    }

#ifndef __DISP_PLATFORM_BOOT__
    nRet = DISP_OS_MMZ_Alloc("VDP_RegBackBuff", HI_NULL, 0x10000, 16, &g_RegBackBuf);
    if (nRet)
    {
        DISP_FATAL("Alloc MMZ VDP_RegBackBuff failed\n");
        return nRet;
    }
#else
	/*for fast_bootup, we should set a flag to tell the reume func ,that it's just a fastbootup,
	 * suspend  func will not be called.
	 */
    Disp_SetFastbootupFlag(DISP_FASTBOOTUP_FLAG);
#endif

    DispGetVersion(&s_stVersion);

    // s2.3 initial ops
    DISP_MEMSET(&s_stIntfOps, 0, sizeof(DISP_INTF_OPERATION_S));
    memset(&g_stVDACAttr, 0, sizeof(HI_DRV_VDAC_ATTR_S));

    g_stVDACAttr.bDACDetEn = HI_FALSE;


    nRet = DISP_HAL_InitVDPState();
    if (nRet)
    {
#ifndef __DISP_PLATFORM_BOOT__
        DISP_OS_MMZ_Release( &g_RegBackBuf);
#endif
        Chip_Specific_DISP_CloseClock();
        DISP_FATAL("Hal init vdp state failed\n");
        return nRet;
    }

    /* reset hardware */
    s_stIntfOps.PF_ResetHardware  = PF_ResetVdpHardware;
    s_stIntfOps.PF_CloseClkResetModule  = PF_CloseClkResetModule;

    /* display */
    /* capability */
    s_stIntfOps.PF_TestChnSupport     = PF_TestChnSupport;
    s_stIntfOps.PF_TestChnSupportHD   = PF_TestChnSupportHD;
    s_stIntfOps.PF_TestIntfSupport    = PF_TestIntfSupport;
    s_stIntfOps.PF_TestChnSupportCast = PF_TestChnSupportCast;
    s_stIntfOps.PF_TestChnEncFmt      = PF_TestChnEncFmt;
    s_stIntfOps.PF_TestChnAttach      = PF_TestChnAttach;

    //s_stIntfOps.PF_ResetChn  = PF_ResetChn;
    //s_stIntfOps.PF_ConfigChn = PF_ConfigChn;
    s_stIntfOps.PF_SetChnFmt = PF_SetChnFmt;
	s_stIntfOps.PF_GetFmtTiming = PF_GetFmtTiming;
    s_stIntfOps.PF_SetChnTiming = PF_SetChnTiming;
	s_stIntfOps.PF_SetHDMI420 = PF_SetHDMI420;

    s_stIntfOps.PF_SetChnPixFmt  = PF_SetChnPixFmt;
    s_stIntfOps.PF_SetChnBgColor = PF_SetChnBgColor;
    s_stIntfOps.PF_SetChnColor   = PF_SetChnColor;

    s_stIntfOps.PF_SetChnEnable  = PF_SetChnEnable;
    s_stIntfOps.PF_GetChnEnable  = PF_GetChnEnable;
    s_stIntfOps.PF_InitDacDetect  = PF_InitDacDetect;

    s_stIntfOps.PF_SetMSChnEnable = PF_SetMSChnEnable;
    /* interrypt */
    s_stIntfOps.PF_SetIntEnable = PF_SetIntEnable;
    s_stIntfOps.PF_GetMaskedIntState = PF_GetMaskedIntState;
    s_stIntfOps.PF_GetIntSetting = PF_GetIntSetting;
    s_stIntfOps.PF_GetUnmaskedIntState = PF_GetUnmaskedIntState;
    s_stIntfOps.PF_CleanIntState = PF_CleanIntState;
    s_stIntfOps.FP_GetChnIntState = FP_GetChnIntState;
    s_stIntfOps.FP_GetChnBottomFlag = FP_GetChnBottomFlag;

    /* interface manager */
    s_stIntfOps.PF_AcquireIntf2   = PF_AcquireIntf2;
    s_stIntfOps.PF_ReleaseIntf2   = PF_ReleaseIntf2;
    s_stIntfOps.PF_ResetIntfFmt2  = PF_ResetIntfFmt2;
    s_stIntfOps.PF_SetIntfEnable2 = PF_SetIntfEnable2;

    /* WBC manager */
    s_stIntfOps.PF_AcquireWbcByChn = PF_AcquireWbcByChn;
    s_stIntfOps.PF_AcquireWbc = PF_AcquireWbc;
    s_stIntfOps.PF_ReleaseWbc = PF_ReleaseWbc;

    /* WBC */
    s_stIntfOps.PF_SetWbcIORect = PF_SetWbcIORect;
    s_stIntfOps.PF_SetWbc3DInfo = PF_SetWbc3DInfo;
    s_stIntfOps.PF_SetWbcColorSpace = PF_SetWbcColorSpace;
    s_stIntfOps.PF_SetWbcPixFmt = PF_SetWbcPixFmt;
    s_stIntfOps.PF_SetWbcAddr = PF_SetWbcAddr;
    s_stIntfOps.PF_SetWbcEnable = PF_SetWbcEnable;
    s_stIntfOps.PF_SetWbcLowDlyEnable = PF_SetWbcLowdlyEnable;
    s_stIntfOps.PF_SetWbcPartfnsLineNum = PF_SetWbcPartfnsLineNum;
    s_stIntfOps.PF_SetWbcLineNumInterval = PF_SetWbcLineNumInterval;
    s_stIntfOps.PF_SetWbcLineAddr = PF_SetWbcLineAddr;
    s_stIntfOps.PF_UpdateWbc= PF_UpdateWbc;
    s_stIntfOps.PF_DACIsr = PF_DACIsr;
    s_stIntfOps.PF_SetDACDetEn = PF_SetDACDetEn;
    s_stIntfOps.PF_GetDACAttr = PF_GetDACAttr;
    /*set CBM Zorder*/
    s_stIntfOps.PF_CBM_MovTOP = PF_CBM_MovTOP;
    s_stIntfOps.PF_VDP_RegSave = PF_VDP_RegSave;
    s_stIntfOps.PF_VDP_RegReStore = PF_VDP_RegReStore;
    s_stIntfOps.PF_DATE_SetCoef = PF_DATE_SetCoef;
    s_stIntfOps.PF_DATE_SetIRE = PF_DATE_SetIRE;

    /*O5*/
    s_stIntfOps.PF_SetAllDACEn = PF_SetAllDACEn;

    s_DispIntfFlag++;

    return HI_SUCCESS;
}

HI_S32 DISP_HAL_DeInit(HI_VOID)
{
#ifndef __DISP_PLATFORM_BOOT__
    DISP_OS_MMZ_Release( &g_RegBackBuf);
#endif
    Chip_Specific_DISP_CloseClock();
    s_DispIntfFlag = 0;

    return HI_SUCCESS;
}

HI_S32 DISP_HAL_GetOperation(DISP_INTF_OPERATION_S *pstFunction)
{
    if(s_DispIntfFlag < 0)
    {
        DISP_ERROR("DISP_INTF Not inited\n");
        return HI_FAILURE;
    }

    memcpy(pstFunction, &s_stIntfOps, sizeof(DISP_INTF_OPERATION_S));

    return HI_SUCCESS;
}

DISP_INTF_OPERATION_S *DISP_HAL_GetOperationPtr(HI_VOID)
{
    if(s_DispIntfFlag < 0)
    {
        DISP_ERROR("DISP_INTF Not inited\n");
        return HI_NULL;
    }

    return &s_stIntfOps;
}

HI_S32 DISP_HAL_GetVersion(HI_DRV_DISP_VERSION_S *pstVersion)
{
    if(s_DispIntfFlag < 0)
    {
        DISP_ERROR("DISP_INTF Not inited\n");
        return HI_FAILURE;
    }

    if (pstVersion)
    {
        *pstVersion = s_stVersion;
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}


HI_S32 DISP_DEBUG_PrintPtr(HI_VOID)
{
    HI_S32 i;
    HI_U32 *ptrf;

    ptrf = (HI_U32 *) & s_stIntfOps;

    for(i=0; i<(sizeof(s_stIntfOps)/sizeof(HI_U32)); i++)
    {
        DISP_WARN("i=%d, v=0x%x\n", i, ptrf[i]);
    }


    return HI_SUCCESS;
}




#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */


