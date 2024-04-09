/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_win_hal.c
Version       : Initial Draft
Author        : Hisilicon multimedia software  group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "drv_win_hal.h"
#include "drv_disp_da.h"
#include "drv_win_priv.h"
#include "drv_win_hal_adp.h"
#include "drv_pq_ext.h"

#include "vdp_hal_intf.h"
#include "vdp_software_selfdefine.h"

#include "drv_win_share.h"
#include "drv_xdr_adapter.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if 0
typedef enum tagVDP_CBM_MIX_E
{
    VDP_CBM_MIXV0 = 0,
    VDP_CBM_MIXV1 = 1,
    VDP_CBM_MIX_BUTT
} VDP_CBM_MIX_E;
#endif

#define VDP_MIXv0_LayerCNT    2
#define VDP_MIXv1_LayerCNT    1

static HI_S32 s_bVideoSurfaceFlag = -1;
static VIDEO_LAYER_FUNCTIONG_S s_stVieoLayerFunc;
static VIDEO_LAYER_S s_stVideoLayer[DEF_VIDEO_LAYER_MAX_NUMBER];

static VDP_LAYER_VID_E s_MIXv0_Zorder[VDP_LAYER_VID_BUTT] =
{
    VDP_LAYER_VID0,
    VDP_LAYER_VID1
};

/*mixv1  and mixg1 be control by CMB*/
static VDP_LAYER_VID_E s_MIXv1_Zorder[VDP_LAYER_VID_BUTT] =
{
    VDP_LAYER_VID3,
};

HI_U32 GetMixvLayerCounts(VDP_CBM_MIX_E eM)
{
    switch (eM)
    {
        case VDP_CBM_MIXV0:
            return VDP_MIXv0_LayerCNT;
        case VDP_CBM_MIXV1:
            return VDP_MIXv1_LayerCNT;
        default:
            return 0;
    }
}

HI_VOID GetMixvPriors(VDP_CBM_MIX_E enMixer, HI_U32 u32prio, HI_U32 *pu32layer_id)
{
    if (enMixer == VDP_CBM_MIXV0)
    {
        *pu32layer_id = s_MIXv0_Zorder[u32prio];
    }
    else
    {
        *pu32layer_id = s_MIXv1_Zorder[u32prio];
    }

    return ;
}

HI_VOID GetSpecialLayerPriorty(HI_U32 u32layer_id, HI_U32 *pu32prio)
{
    HI_U32 i = 0;

    if (HI_NULL == pu32prio)
    {
        WIN_ERROR("pu32prio is null.\n");
        return;
    }

    if ((u32layer_id == VDP_LAYER_VID0)
        || (u32layer_id == VDP_LAYER_VID1))
    {
        for (i = 0 ; i < VDP_MIXv0_LayerCNT; i++)
        {
            if (s_MIXv0_Zorder[i] == u32layer_id)
            {
                *pu32prio = i;
                break;
            }
        }

        if (i == VDP_MIXv0_LayerCNT)
        {
            WIN_ERROR("Getlayer's priorty failed,layerid:%d!\n", u32layer_id);
            return ;
        }
    }
    else if (u32layer_id == VDP_LAYER_VID3)
    {
        for (i = 0 ; i < VDP_MIXv1_LayerCNT; i++)
        {
            if (s_MIXv1_Zorder[i] == u32layer_id)
            {
                *pu32prio = i;
                break;
            }
        }

        if (i == VDP_MIXv1_LayerCNT)
        {
            WIN_ERROR("Getlayer's priorty failed,layerid:%d!\n", u32layer_id);
            return ;
        }
    }

    return;

}


HI_VOID SetMixvPrios(VDP_CBM_MIX_E enMixer, HI_U32 *pMixArray, HI_U32 u32prio)
{
    HI_U32 i = 0;

    if (enMixer == VDP_CBM_MIXV0)
    {
        for (i = 0 ; i < VDP_MIXv0_LayerCNT; i++)
        {
            s_MIXv0_Zorder[i] = pMixArray[i];
        }
    }
    else
    {
        for (i = 0 ; i < VDP_MIXv0_LayerCNT; i++)
        {
            s_MIXv1_Zorder[i] = pMixArray[i];
        }
    }

    return;
}

static HI_VOID TransvertAddr2CBB(CBB_ADDRESS_S *pstCbbAddr, HI_DRV_VID_FRAME_ADDR_S *pstAddr)
{
    if (HI_NULL == pstCbbAddr || HI_NULL == pstAddr)
    {
        WIN_ERROR("pstCbbAddr or pstAddr is null.\n");
        return;
    }

    pstCbbAddr->u32PhyAddr_YHead = pstAddr->u32PhyAddr_YHead;
    pstCbbAddr->u32PhyAddr_Y = pstAddr->u32PhyAddr_Y;
    pstCbbAddr->u32Stride_Y = pstAddr->u32Stride_Y;

    pstCbbAddr->u32PhyAddr_CHead = pstAddr->u32PhyAddr_CHead;
    pstCbbAddr->u32PhyAddr_C = pstAddr->u32PhyAddr_C;
    pstCbbAddr->u32Stride_C = pstAddr->u32Stride_C;

    pstCbbAddr->u32PhyAddr_CrHead = pstAddr->u32PhyAddr_CrHead;
    pstCbbAddr->u32PhyAddr_Cr = pstAddr->u32PhyAddr_Cr;
    pstCbbAddr->u32Stride_Cr = pstAddr->u32Stride_Cr;


    pstCbbAddr->u32Head_Stride = pstAddr->u32Head_Stride;
    pstCbbAddr->u32Head_Size = pstAddr->u32Head_Size;

    return;
}

static HI_VOID TransvertCapability(CBB_VIDEO_LAYER_CAPABILITY_S *pstCbbLayer,
                                   VIDEO_LAYER_CAPABILITY_S *pstLayerCap)
{
    if (HI_NULL == pstCbbLayer || HI_NULL == pstLayerCap)
    {
        WIN_ERROR("pstCbbLayer or pstLayerCap is null.\n");
        return;
    }

    pstLayerCap->bZme = pstCbbLayer->bZme;
    pstLayerCap->bZmePrior = pstCbbLayer->bZmePrior;
    pstLayerCap->bDcmp = pstCbbLayer->bDcmp;
    pstLayerCap->bTnrSnrDbDMDrDs = pstCbbLayer->bTnrSnrDbDMDrDs;
    pstLayerCap->u32BitWidth = pstCbbLayer->u32BitWidth;

    /*memcpy((HI_VOID*)&pstLayerCap->stVideoReadSize,
            (HI_VOID*)&pstCbbLayer->stVideoMaxReadSize,
            sizeof(CBB_RECT_S));*/
    pstLayerCap->stVideoReadSize.s32X = pstCbbLayer->stVideoMaxReadSize.s32X;
    pstLayerCap->stVideoReadSize.s32Y = pstCbbLayer->stVideoMaxReadSize.s32Y;
    pstLayerCap->stVideoReadSize.s32Width = pstCbbLayer->stVideoMaxReadSize.s32Width;
    pstLayerCap->stVideoReadSize.s32Height = pstCbbLayer->stVideoMaxReadSize.s32Height;

    return;
}


HI_VOID TransvertPixelFmt2CBB(HI_DRV_PIX_FORMAT_E *peInputPixelFmt, CBB_PIX_FORMAT_E  *peOutPixelFmt)
{
    if (HI_NULL == peInputPixelFmt || HI_NULL == peOutPixelFmt)
    {
        WIN_ERROR("peInputPixelFmt or peOutPixelFmt is null.\n");
        return;
    }

    switch (*peInputPixelFmt)
    {
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
            *peOutPixelFmt = CBB_VID_IFMT_SP_420;
            break;
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1:
            *peOutPixelFmt = CBB_VID_IFMT_SP_422;
            break;
        case HI_DRV_PIX_FMT_NV42:
            *peOutPixelFmt = CBB_VID_IFMT_SP_444;
            break;
        case HI_DRV_PIX_FMT_YUYV:
            *peOutPixelFmt = CBB_VID_IFMT_PKG_YUYV;
            break;
        case HI_DRV_PIX_FMT_YVYU:
            *peOutPixelFmt = CBB_VID_IFMT_PKG_YVYU;
            break;
        case HI_DRV_PIX_FMT_UYVY:
            *peOutPixelFmt = CBB_VID_IFMT_PKG_UYVY;
            break;
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            *peOutPixelFmt = CBB_VID_IFMT_SP_TILE_64;
            break;
        case HI_DRV_PIX_FMT_RGB24:
            *peOutPixelFmt = CBB_VID_IFMT_RGB_888;
            break;
        case HI_DRV_PIX_FMT_ARGB8888:
            *peOutPixelFmt = CBB_VID_IFMT_ARGB_8888;
            break;
        default:
            WIN_ERROR("Invalid pixel fmt.\n");
            break;
    }

    return ;
}



HI_VOID TransvertSdkCsc2Cbb(HI_DRV_COLOR_SPACE_E eColorSpace,
                            CBB_CSC_MODE_E *penOutColorSpace)
{
    switch (eColorSpace)
    {
        case HI_DRV_CS_BT601_YUV_LIMITED:
            *penOutColorSpace = CBB_CSC_BT601_YUV_LIMITED;
            break;
        case HI_DRV_CS_BT601_YUV_FULL:
            *penOutColorSpace = CBB_CSC_BT601_YUV_FULL;
            break;
        case HI_DRV_CS_BT709_YUV_LIMITED:

            *penOutColorSpace = CBB_CSC_BT709_YUV_LIMITED;
            break;
        case HI_DRV_CS_BT709_YUV_FULL:

            *penOutColorSpace = CBB_CSC_BT709_YUV_FULL;
            break;
        case HI_DRV_CS_BT709_RGB_FULL:
            *penOutColorSpace = CBB_CSC_BT709_RGB_FULL;
            break;
        case HI_DRV_CS_BT2020_YUV_LIMITED:
            *penOutColorSpace = CBB_CSC_BT2020_YUV_LIMITED;
            break;
        case HI_DRV_CS_BT2020_YUV_FULL:
            *penOutColorSpace = CBB_CSC_BT2020_YUV_LIMITED;
            break;
        case HI_DRV_CS_BT2020_RGB_LIMITED:

            *penOutColorSpace = CBB_CSC_BT2020_RGB_FULL;
            break;
        case HI_DRV_CS_BT2020_RGB_FULL:

            *penOutColorSpace = CBB_CSC_BT2020_RGB_FULL;
            break;
        default:
            WIN_ERROR("Invalid color space type--%d.\n", eColorSpace);
            break;
    }

    return;
}

HI_VOID TransvertCbbCsc2Sdk(CBB_CSC_MODE_E eColorSpace,
                            HI_DRV_COLOR_SPACE_E *penOutColorSpace)
{

    switch (eColorSpace)
    {
        case CBB_CSC_BT601_YUV_LIMITED:

            *penOutColorSpace = HI_DRV_CS_BT601_YUV_LIMITED;
            break;
        case CBB_CSC_BT601_YUV_FULL:
            *penOutColorSpace = HI_DRV_CS_BT601_YUV_FULL;
            break;
        case CBB_CSC_BT709_YUV_LIMITED:
            *penOutColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
            break;
        case CBB_CSC_BT709_YUV_FULL:
            *penOutColorSpace = HI_DRV_CS_BT709_YUV_FULL;
            break;
        case CBB_CSC_BT709_RGB_FULL:
            *penOutColorSpace = HI_DRV_CS_BT709_RGB_FULL;
            break;

        case CBB_CSC_BT2020_YUV_LIMITED:
            *penOutColorSpace = HI_DRV_CS_BT2020_YUV_LIMITED;
            break;

        case CBB_CSC_BT2020_RGB_FULL:
            *penOutColorSpace = HI_DRV_CS_BT2020_RGB_FULL;
            break;

        default:
            WIN_ERROR("Invalid color space type.\n");
            break;
    }

    return;
}

/*transvert  sdk's bitwidth definition to cbb's*/



HI_BOOL  CheckFrameIs3D( HI_DRV_FRAME_TYPE_E  eFrmType)
{
    if (( HI_DRV_FT_SBS == eFrmType )
        || ( HI_DRV_FT_TAB == eFrmType )
        || ( HI_DRV_FT_FPK == eFrmType )
        || ( HI_DRV_FT_TILE == eFrmType ))
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

HI_S32 TransWbcInfor2CBB(WIN_WBC_CONFIG_S *pstPara,
                         CBB_WBC_CFG_INFO_S *pCbbLayerBasePara,
                         CBB_CFG_EXT_S *pVDPCfgExtPara)
{
    if (pstPara->bWbcEnable == HI_FALSE)
    {
        pCbbLayerBasePara->enWBC                  = DRV_VDP_WBC_WIN;
        pCbbLayerBasePara->bWbcEnable             = pstPara->bWbcEnable;
    }
    else
    {
        /*when in complex condition,  such as watermark.*/
        pCbbLayerBasePara->bForceWbcPoint2Vp           = pstPara->bComplexMode;
        pCbbLayerBasePara->bForceWbcFieldMode        = pstPara->bForceFieldMode;

        pCbbLayerBasePara->stSdWinOutputSize      = pstPara->stSdWinOutputSize;
        pCbbLayerBasePara->stHdWinOutputSize      = pstPara->stHdWinOutputSize;
        pCbbLayerBasePara->stHdWinInputSize       = pstPara->stHdWinInputSize;

        pCbbLayerBasePara->enWBC                  = DRV_VDP_WBC_WIN;
        pCbbLayerBasePara->bWbcEnable             = pstPara->bWbcEnable;

        TransvertPixelFmt2CBB(&pstPara->eOutPutPixelFmt, &pCbbLayerBasePara->eOutPutPixelFmt);

        pCbbLayerBasePara->eFieldMode             = (CBB_FIELD_MODE_E)pstPara->eFieldMode;

        TransvertSdkCsc2Cbb(pstPara->enHdWinSrcColorSpace, &pCbbLayerBasePara->enHdWinSrcColorSpace);
        TransvertSdkCsc2Cbb(pstPara->enHdWinDestColorSpace, &pCbbLayerBasePara->enHdWinDestColorSpace);
        TransvertAddr2CBB(&pCbbLayerBasePara->stAddr, &pstPara->stAddr);

        pCbbLayerBasePara->bSecure = HI_FALSE;

#ifdef  CFG_VDP_MMU_SUPPORT
        pCbbLayerBasePara->bSmmu   = HI_TRUE;
#else
        pCbbLayerBasePara->bSmmu   = HI_FALSE;
#endif

    }

    return 0;
}


HI_S32 TransCbbWbcPolicy2SDK(WIN_WBC_POLICY_S *pstPolicy,
                             CBB_WBC_POLICY_S *pCbbPolicy)
{
    pstPolicy->bWbcOutputFieldMode = pCbbPolicy->bWbcOutputFieldMode;

    pstPolicy->stWbcOutputSize.s32X = pCbbPolicy->stSdFinaleDispRect.s32X;
    pstPolicy->stWbcOutputSize.s32Y = pCbbPolicy->stSdFinaleDispRect.s32Y;
    pstPolicy->stWbcOutputSize.s32Width = pCbbPolicy->stSdFinaleDispRect.s32Width;
    pstPolicy->stWbcOutputSize.s32Height = pCbbPolicy->stSdFinaleDispRect.s32Height;

    TransvertCbbCsc2Sdk(pCbbPolicy->enDestColorSpace, &pstPolicy->enDestColorSpace);
    TransvertCbbCsc2Sdk(pCbbPolicy->enSrcColorSpace, &pstPolicy->enSrcColorSpace);
    return 0;
}

VDP_CBM_MIX_E GetMixerID(VDP_LAYER_VID_E eLayer)
{
    if (eLayer <= VDP_LAYER_VID1)
    {
        return VDP_CBM_MIXV0;
    }
    else if ( (VDP_LAYER_VID3 == eLayer))
    {
        return VDP_CBM_MIXV1;
    }
    else
    {
        WIN_ERROR("Pass invalid layer !\n");
        return VDP_CBM_BUTT;
    }
}

HI_S32 MovTop(HI_U32 eLayer)
{
    VDP_CBM_MIX_E eMixId;
    HI_U32 nMaxLayer;
    VDP_LAYER_VID_E eLayerHalId;
    HI_U32 MixArray[VDP_LAYER_VID_BUTT + 1];
    HI_U32 i, index;

    /*get eLayer Id and mix id. */
    if (eLayer >= VDP_LAYER_VID_BUTT)
    {
        WIN_ERROR("eLayer out of range.\n");
        return HI_FAILURE;
    }

    eLayerHalId = (VDP_LAYER_VID_E)eLayer;
    eMixId = GetMixerID(eLayerHalId);

    /*get the layer counts in the given mixid. */
    nMaxLayer = GetMixvLayerCounts(eMixId);
    if (nMaxLayer <= 1)
    {
        return HI_SUCCESS;
    }

    /*traversing  the array, get eLayer prios*/
    for (i = 0; i < nMaxLayer; i++)
    {
        /*pay attention:  the index "i" means priorty,  the value MixArray[i] means the layerid. */
        GetMixvPriors(eMixId, i, &MixArray[i]);
    }

    /* get eLayer index, */
    index = nMaxLayer;
    for (i = 0; i < nMaxLayer; i++)
    {
        if (MixArray[i] == (HI_U32)eLayerHalId)
        {
            index = i;
            break;
        }
    }

    // not found or just single layer work
    if (index >= (nMaxLayer - 1))
    {
        return HI_SUCCESS;
    }

    // change mixv order
    for (i = index; i < (nMaxLayer - 1); i++)
    {
        MixArray[i] = MixArray[i + 1];
    }

    MixArray[i] = eLayerHalId;
    SetMixvPrios(eMixId, MixArray, nMaxLayer);

    return HI_SUCCESS;
}

HI_S32 MovBottom(HI_U32 eLayer)
{
    VDP_CBM_MIX_E eMixId;
    HI_U32 nMaxLayer;
    VDP_LAYER_VID_E eLayerHalId;
    HI_U32 MixArray[VDP_LAYER_VID_BUTT + 1];
    HI_U32 i, index;

    // get eLayer Id
    if (eLayer >= VDP_LAYER_VID_BUTT)
    {
        WIN_ERROR("eLayer out of range.\n");
        return HI_FAILURE;
    }

    eLayerHalId = (VDP_LAYER_VID_E)eLayer;

    // get mixv id
    eMixId = GetMixerID(eLayerHalId);

    // get mixv setting
    nMaxLayer = GetMixvLayerCounts(eMixId);
    if (nMaxLayer <= 1)
    {
        return HI_SUCCESS;
    }

    // get eLayer prio
    for (i = 0; i < nMaxLayer; i++)
    {
        GetMixvPriors(eMixId, i, &MixArray[i]);
    }

    // get eLayer index
    index = nMaxLayer;
    for (i = 0; i < nMaxLayer; i++)
    {
        if (MixArray[i] == (HI_U32)eLayerHalId)
        {
            index = i;
            break;
        }
    }

    // not found
    if (index >= nMaxLayer)
    {
        return HI_SUCCESS;
    }

    // layer at bottom
    if (!index)
    {
        return HI_SUCCESS;
    }

    // change mixv order
    for (i = index; i > 0; i--)
    {
        MixArray[i] = MixArray[i - 1];
    }
    MixArray[0] = eLayerHalId;
    SetMixvPrios(eMixId, MixArray, nMaxLayer);
    return HI_SUCCESS;
}


/*to be deleted, seems useless.*/
HI_S32 HAL_Video_AcquireLayerByDisplay(HI_DRV_DISPLAY_E eDisp, HI_U32 *peLayer)
{
    return HI_SUCCESS;
}

HI_S32 HAL_Video_ReleaseLayer(HI_U32 eLayer)
{
    return HI_SUCCESS;
}

/*set layer default.*/
HI_S32 HAL_Video_InitSingleLayer(HI_U32 eLayer)
{
    CBB_Video_SetLayerInit(eLayer);
    return HI_SUCCESS;
}

/*call cbb's func to init all the video layers and etc.*/
HI_S32 HAL_Video_Init(HI_VOID)
{
    /*when suspend resume. when call this do what?*/
    return HI_SUCCESS;
}

HI_S32 HAL_Video_SetSdLayerCfg(HI_U32 u32Layer, HI_VOID *pstWinInfo)
{
    WinCheckNullPointer(pstWinInfo);

    ADAPTER_SetLayerCfg(u32Layer, (WIN_INFO_S *)pstWinInfo, HI_NULL, HI_TRUE);
    return HI_SUCCESS;
}

HI_S32  HAL_Video_GetLayerCapability(HI_U32 eLayer, VIDEO_LAYER_CAPABILITY_S *pstLayerCap)
{
    CBB_VIDEO_LAYER_CAPABILITY_S stLayerCapability;
    memset(&stLayerCapability, 0x0, sizeof(CBB_VIDEO_LAYER_CAPABILITY_S));

    stLayerCapability.eId = eLayer;
    CBB_Video_GetLayersCapability(&stLayerCapability);
    TransvertCapability(&stLayerCapability, pstLayerCap);

    return HI_SUCCESS;
}

/*check whether the layer is opened or not?*/
HI_S32  HAL_Video_GetLayerStatus(HI_U32 eLayer)
{
    return  CBB_Video_GetLayerStatus(eLayer);
}

HI_S32 HAL_Video_MovTop(HI_U32 eLayer)
{
    MovTop(eLayer);
    return HI_SUCCESS;
}

HI_S32 HAL_Video_MovBottom(HI_U32 eLayer)
{
    MovBottom(eLayer);
    return HI_SUCCESS;
}

HI_S32 HAL_Video_GetZorder(HI_U32 eLayer, HI_U32 *pZOrder)
{
    GetSpecialLayerPriorty(eLayer, pZOrder);
    return HI_SUCCESS;
}

HI_S32 HAL_SetEnable(HI_U32 eLayer, HI_U32 u32RegionNum, HI_BOOL bEnable)
{
    VDP_VID_SetRegionEnable_sdk(eLayer, u32RegionNum, bEnable);
    return HI_SUCCESS;
}


/*get the wbc policy to  sdk for v3's config . */
HI_S32 HAL_GetWbcPolicy(WIN_WBC_CONFIG_S *pstPara,
                        WIN_WBC_POLICY_S *pstWbcPolicy)
{
    CBB_WBC_POLICY_S stCbbWbcPolicy;
    CBB_WBC_CFG_INFO_S stWbcCfgInfor;

    if ((HI_NULL == pstPara) || (HI_NULL == pstWbcPolicy))
    {
        WIN_ERROR("pstPara of pstCbb_Layer is null.\n");
        return HI_FAILURE;
    }

    TransWbcInfor2CBB(pstPara, &stWbcCfgInfor, HI_NULL);
    (HI_VOID)CBB_Video_GetWbcPolicy(&stWbcCfgInfor, HI_NULL, &stCbbWbcPolicy);
    (HI_VOID)TransCbbWbcPolicy2SDK(pstWbcPolicy, &stCbbWbcPolicy);

    return HI_SUCCESS;
}

HI_S32 HAL_SetWbcParam(WIN_WBC_CONFIG_S *pstPara)
{
    CBB_WBC_CFG_INFO_S stCbbInfor;

    if (HI_NULL == pstPara)
    {
        WIN_ERROR("pstPara is null.\n");
        return HI_FAILURE;
    }

    TransWbcInfor2CBB(pstPara, &stCbbInfor, HI_NULL);
    (HI_VOID)CBB_Video_SetWbcParam(&stCbbInfor,
                                   HI_NULL);
    return HI_SUCCESS;
}

HI_S32 VideoLayer_Init(HI_VOID)
{
    if (s_bVideoSurfaceFlag >= 0)
    {
        return HI_SUCCESS;
    }

    // s1 init videolayer
    DISP_MEMSET(&s_stVieoLayerFunc, 0, sizeof(VIDEO_LAYER_FUNCTIONG_S));
    DISP_MEMSET(&s_stVideoLayer, 0, sizeof(VIDEO_LAYER_S) * DEF_VIDEO_LAYER_MAX_NUMBER);

    // s2.1 set function pointer
    s_stVieoLayerFunc.PF_GetCapability  = HAL_Video_GetLayerCapability;
    s_stVieoLayerFunc.PF_AcquireLayerByDisplay = HAL_Video_AcquireLayerByDisplay;
    s_stVieoLayerFunc.PF_ReleaseLayer   = HAL_Video_ReleaseLayer;
    s_stVieoLayerFunc.PF_SetEnable   = HAL_SetEnable;

    s_stVieoLayerFunc.PF_InitialLayer     = HAL_Video_InitSingleLayer;
    s_stVieoLayerFunc.PF_CheckLayerInit   = HAL_Video_GetLayerStatus;
    s_stVieoLayerFunc.PF_SetAllLayerDefault = HAL_Video_Init;

#if 1
    //s_stVieoLayerFunc.PF_MovUp          = MovUp;
    s_stVieoLayerFunc.PF_MovTop         = HAL_Video_MovTop;
    //s_stVieoLayerFunc.PF_MovDown        = MovDown;
    s_stVieoLayerFunc.PF_MovBottom      = HAL_Video_MovBottom;
    s_stVieoLayerFunc.PF_GetZorder      = HAL_Video_GetZorder;
#endif
    s_stVieoLayerFunc.PF_SetSdLayerCfg  = HAL_Video_SetSdLayerCfg;
    s_stVieoLayerFunc.PF_GetWbcPolicy = HAL_GetWbcPolicy;
    s_stVieoLayerFunc.PF_SetWbcParam = HAL_SetWbcParam;

    s_bVideoSurfaceFlag++;

    return HI_SUCCESS;
}


HI_S32 VideoLayer_DeInit(HI_VOID)
{
    if (s_bVideoSurfaceFlag < 0)
    {
        return HI_SUCCESS;
    }

    s_bVideoSurfaceFlag--;
    return HI_SUCCESS;
}

HI_S32 VideoLayer_GetFunction(VIDEO_LAYER_FUNCTIONG_S *pstFunc)
{
    if (s_bVideoSurfaceFlag < 0)
    {
        WIN_WARN("Video layer NOT INIT\n");
        return HI_FAILURE;
    }

    if (!pstFunc)
    {
        WIN_WARN("NULL Pointer\n");
        return HI_FAILURE;
    }

    *pstFunc = s_stVieoLayerFunc;

    return HI_SUCCESS;
}

VIDEO_LAYER_FUNCTIONG_S *VideoLayer_GetFunctionPtr(HI_VOID)
{
    if (s_bVideoSurfaceFlag < 0)
    {
        WIN_ERROR("Video layer NOT INIT\n");
        return HI_NULL;
    }

    return &s_stVieoLayerFunc;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
