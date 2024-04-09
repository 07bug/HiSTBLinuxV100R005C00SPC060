#include "hi_type.h"
#include "vdp_drv_vid.h"
#include "vdp_drv_ip_hihdr_v.h"
#include "vdp_drv_hihdr_v_coef.h"
#include "vdp_func_pq_csc.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_drv_bkg_process.h"
#include "vdp_hal_vid.h"
#include "vdp_func_ip_fdr.h"
#include "vdp_hal_ip_cap.h"
#include "vdp_hal_gfx.h"

#ifndef  __DISP_PLATFORM_BOOT__
#if (!EDA_TEST)
#include <linux/string.h>
#include <linux/kernel.h>
#else
#include <string.h>
#include <sys/timeb.h>
#endif


extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;

HI_S32 VDP_DRV_HdrRegClean(XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_U32 ii=0;

    for (ii = 0; ii < MAX_WINDOWS_NUM; ii++)
    {
        if (pstInfoIn->stXdpSysCfg.bVdmProcess[ii] == HI_TRUE)
        {
            return HI_SUCCESS;
        }
    }

    VDP_HIHDR_V_SetHihdrV0VhdrEn       (0);
    VDP_HIHDR_V_SetHihdrV1VhdrEn       (0);
    VDP_HIHDR_V_SetVhdrGamutBind       (0);
    VDP_HIHDR_V_SetVhdrEn              (0);
    VDP_HIHDR_V_SetVhdrTmapEn          (0);
    VDP_HIHDR_V_SetVhdrDegmmEn         (0);
    VDP_HIHDR_V_SetVhdrGmmEn           (0);
    VDP_HIHDR_V_SetVhdrCadjEn          (0);
    VDP_HIHDR_V_SetVhdrGamutEn         (0);
    VDP_HIHDR_V_SetVhdrR2yEn           (0);
    VDP_HIHDR_V_SetHihdrY2rEn          (0);
    VDP_HIHDR_V_SetHihdrV0Y2rEn        (0);
    VDP_HIHDR_V_SetHihdrV1Y2rEn        (0);

    return HI_SUCCESS;
}

HI_VOID VDP_DRV_SysRegClean(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    VDP_VID_SetV0LinkCtrl(VDP_LAYER_VID0, 0);
    pstInfoIn->stXdpLayerExtern.u32LinkEn = 0;
    return;
}

HI_S32 XDP_DRV_RegisterClen(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfo)
{
    VDP_DRV_SysRegClean(u32LayerId,pstInfo);
    VDP_DRV_HdrRegClean(pstInfo);

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_JudgeVidLayerEnable(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfo)
{
    if ((u32LayerId == VDP_LAYER_VID0) && (pstInfo->stXdpSysCfg.bRegionEn == HI_FALSE))
    {
        VDP_VID_SetLayerEnable (u32LayerId, HI_FALSE);
        VDP_VID_SetRegUp(u32LayerId);
        return HI_SUCCESS;
    }
    else if ((u32LayerId == VDP_LAYER_VID1) && (pstInfo->stXdpSysCfg.bRegionEn == HI_FALSE))
    {
        VDP_VID_SetRegionEnable(u32LayerId, pstInfo->stXdpSysCfg.u32RegionNO, pstInfo->stXdpSysCfg.bRegionEn);

        if ( HI_TRUE == VDP_VID_CheckLastRegionState(pstInfo->stXdpSysCfg.u32RegionNO) )
        {
            VDP_VID_SetLayerEnable (u32LayerId, HI_FALSE);
        }
        VDP_VID_SetRegUp(u32LayerId);
        VDP_VID_SetRegionParaUp(VDP_LAYER_VID1);
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 XDP_DRV_SetVidLayerFdr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_BOOL bRgbColorSpace = HI_FALSE;
    VDP_BKG_S   stMuteColor;
    HI_U32  u32FdrOffset = 0;
    u32FdrOffset = u32LayerId * VID_FDR_OFFSET;

    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64 || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE)
    {
        VDP_FDR_VID_SetLmStride       (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr);
        VDP_FDR_VID_SetChmStride      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);
        VDP_FDR_VID_SetVhdaddrL       (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr);
        VDP_FDR_VID_SetVhdcaddrL      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr);

        if (pstInfoIn->stXdpSrcCfg.bDcmpEn == HI_TRUE)
        {
            VDP_FDR_VID_SetHVhdaddrL      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32LumAddr);
            VDP_FDR_VID_SetHVhdcaddrL     (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32ChmAddr);
            VDP_FDR_VID_SetLmHeadStride   (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32LumStr );
            VDP_FDR_VID_SetChmHeadStride  (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_HEAD].u32ChmStr );
        }
        if (pstInfoIn->stXdpSrcCfg.enDataWidth == VDP_DATA_WTH_10)
        {
            VDP_FDR_VID_SetBVhdaddrL      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumAddr);
            VDP_FDR_VID_SetBVhdcaddrL     (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32ChmAddr);
            VDP_FDR_VID_SetLmTileStride   (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32LumStr );
            VDP_FDR_VID_SetChmTileStride  (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_TILE].u32ChmStr );
        }
    }
    else
    {
        VDP_FDR_VID_SetLmStride       (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr);
        VDP_FDR_VID_SetChmStride      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr);
        VDP_FDR_VID_SetVhdaddrL       (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr);
        VDP_FDR_VID_SetVhdcaddrL      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr);

        if (pstInfoIn->stXdpDispCfg.enDispMode != VDP_DISP_MODE_2D)
        {
            VDP_FDR_VID_SetVhdnaddrL      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32LumAddr  );
            VDP_FDR_VID_SetVhdncaddrL     (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_3D].u32ChmAddr  );
        }
    }

    //src information
    switch(pstInfoIn->stXdpSrcCfg.enInFmt)
    {
        case VDP_VID_IFMT_SP_TILE    :
        case VDP_VID_IFMT_SP_TILE_64 :
        case VDP_VID_IFMT_SP_TILE_400:
        {
            VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_TILE) ;
            break;
        }
        case VDP_VID_IFMT_PKG_UYVY  :
        case VDP_VID_IFMT_PKG_YUYV  :
        case VDP_VID_IFMT_PKG_YVYU  :
        case VDP_VID_IFMT_RGB_888   :
        case VDP_VID_IFMT_PKG_444   :
        case VDP_VID_IFMT_PKG_888   :
        case VDP_VID_IFMT_ARGB_8888 :
        {
            VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_PKG) ;
            VDP_VID_SetV0LinkCtrl  (u32LayerId, 1);/*RGB or 444 enable link special way*/
            pstInfoIn->stXdpLayerExtern.u32LinkEn = 1;
            break;
        }
        case VDP_VID_IFMT_SP_444    :
        {
            VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_LINEAR) ;
            VDP_VID_SetV0LinkCtrl  (u32LayerId, 1);/*RGB or 444 enable link special way*/
            pstInfoIn->stXdpLayerExtern.u32LinkEn = 1;
            break;
        }
        case VDP_VID_IFMT_SP_400    :
        case VDP_VID_IFMT_SP_420    :
        case VDP_VID_IFMT_SP_422    :
        case VDP_VID_IFMT_SP_422V   :
        {
            VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_LINEAR) ;
            break;
        }
        default:
        {
            VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_LINEAR) ;
        }
    }

    switch(pstInfoIn->stXdpSrcCfg.enInFmt)
    {
        case VDP_VID_IFMT_ARGB_8888:
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_ARGB8888) ;
            break;
        }
        case VDP_VID_IFMT_RGB_888  :
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_RGB888) ;
            break;
        }
        case VDP_VID_IFMT_PKG_444:
        case VDP_VID_IFMT_PKG_888:
        case VDP_VID_IFMT_SP_444 :
        case VDP_VID_IFMT_SP_422V:
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV444) ;
            break;
        }
        case VDP_VID_IFMT_PKG_UYVY  :
        case VDP_VID_IFMT_PKG_YUYV  :
        case VDP_VID_IFMT_PKG_YVYU  :
        case VDP_VID_IFMT_SP_422    :
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV422) ;
            break;
        }
        case VDP_VID_IFMT_SP_TILE   :
        case VDP_VID_IFMT_SP_TILE_64:
        case VDP_VID_IFMT_SP_420    :
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV420) ;
            break;
        }
        case VDP_VID_IFMT_SP_400     :
        case VDP_VID_IFMT_SP_TILE_400:
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV400) ;
            break;
        }
        default:
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV422) ;
        }
    }

    if (pstInfoIn->stXdpSrcCfg.bDcmpEn == HI_TRUE)
    {
        VDP_FDR_VID_SetDcmpType       (u32FdrOffset, XDP_CMP_TYPE_SEG); // DcmpEn => DcmpType
    }
    else
    {
        VDP_FDR_VID_SetDcmpType       (u32FdrOffset, XDP_CMP_TYPE_OFF); // DcmpEn => DcmpType
    }

    /*V1 NoMrg In Sp420*/
    if ((pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420 && u32LayerId == VDP_LAYER_VID1)
            || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422V)
    {
        VDP_FDR_VID_SetChmCopyEn      (u32FdrOffset, HI_TRUE     );
    }
    else
    {
        VDP_FDR_VID_SetChmCopyEn      (u32FdrOffset, HI_FALSE     );
    }
    VDP_FDR_VID_SetIresoW         (u32FdrOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth -1 );
    VDP_FDR_VID_SetIresoH         (u32FdrOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt -1 );
    VDP_FDR_VID_SetSrcCropX       (u32FdrOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32X   );
    VDP_FDR_VID_SetSrcCropY       (u32FdrOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Y   );
    VDP_FDR_VID_SetSrcW           (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stSrcRect.u32Wth - 1 );
    VDP_FDR_VID_SetSrcH           (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stSrcRect.u32Hgt - 1 );

    VDP_FDR_VID_SetDataWidth      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.enDataWidth    );
    VDP_FDR_VID_SetDispMode       (u32FdrOffset, pstInfoIn->stXdpDispCfg.enDispMode    );

    //read mode
    VDP_FDR_VID_SetLmRmode        (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enReadMode     );
    VDP_FDR_VID_SetChmRmode       (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enReadMode     );

    //draw hor & ver
    VDP_FDR_VID_SetDrawPixelMode  (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enDrawPixelMode );
    VDP_FDR_VID_SetLmDrawMode     (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enDrawMode      );
    VDP_FDR_VID_SetChmDrawMode    (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enDrawMode      );

    //coperation
    VDP_FDR_VID_SetUvOrderEn      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.bUVOrder        );

    //mute
    VDP_FDR_VID_SetMuteEn         (u32FdrOffset, pstInfoIn->stXdpSysCfg.bMuteEn             );
    XDP_DRV_JudgeRgbColorSpace    (pstInfoIn->stXdpSrcCfg.enSrcClrSpace, &bRgbColorSpace);
    XDP_DRV_AdjustColor           (&stMuteColor,pstInfoIn->stXdpBkgCfg.stMuteColor, bRgbColorSpace);
    VDP_FDR_VID_SetMuteY          (u32FdrOffset, stMuteColor.u32BkgY );
    VDP_FDR_VID_SetMuteCb         (u32FdrOffset, stMuteColor.u32BkgU );
    VDP_FDR_VID_SetMuteCr         (u32FdrOffset, stMuteColor.u32BkgV );

    VDP_VID_SetMuteEnable         (u32LayerId, pstInfoIn->stXdpSysCfg.bMuteEn);
    VDP_VID_SetMuteBkg            (u32LayerId, stMuteColor);
    VDP_VID_SetLayerGalpha        (u32LayerId, pstInfoIn->stXdpSysCfg.u32Alpha);

    /*Secure enable set*/
    VDP_VID_SetNoSecFlag(u32LayerId,!pstInfoIn->stXdpSysCfg.bSecureEn);

    /*Layer enable set*/
    VDP_VID_SetLayerEnable         (u32LayerId, HI_TRUE);

    /*Calc the zme inrect*/
    pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth=pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth >> pstInfoIn->stXdpFdrCfg.enDrawPixelMode;
    pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt=pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt >> pstInfoIn->stXdpFdrCfg.enDrawMode;

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidLayerRegion(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_BOOL bRgbColorSpace = HI_FALSE;
    VDP_BKG_S   stMuteColor;
    HI_U32  u32FdrOffset = 0;
    HI_U32  u32RegionOffset = 0;

    u32FdrOffset = u32LayerId * VID_FDR_OFFSET;
    u32RegionOffset = u32RegionOffset + REGION_OFFSET*pstInfoIn->stXdpSysCfg.u32RegionNO;

    VDP_FDR_VID_SetMrgEn          (u32RegionOffset, pstInfoIn->stXdpSysCfg.bRegionEn          );
    VDP_FDR_VID_SetMrgMuteEn      (u32RegionOffset, pstInfoIn->stXdpSysCfg.bMuteEn            );

    VDP_FDR_VID_SetMrgCropEn      (u32RegionOffset, 1            );
    VDP_FDR_VID_SetMrgXpos        (u32RegionOffset, pstInfoIn->stXdpPositionCfg.stVideoRect.u32X  );
    VDP_FDR_VID_SetMrgYpos        (u32RegionOffset, pstInfoIn->stXdpPositionCfg.stVideoRect.u32Y  );
    VDP_FDR_VID_SetMrgWidth       (u32RegionOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth -1);
    VDP_FDR_VID_SetMrgHeight      (u32RegionOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt -1);

    VDP_FDR_VID_SetMrgSrcWidth    (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stSrcRect.u32Wth-1);
    VDP_FDR_VID_SetMrgSrcHeight   (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stSrcRect.u32Hgt-1);
    VDP_FDR_VID_SetMrgSrcHoffset  (u32RegionOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32X     );
    VDP_FDR_VID_SetMrgSrcVoffset  (u32RegionOffset, pstInfoIn->stXdpFdrCfg.stCropRect.u32Y     );

    VDP_FDR_VID_SetMrgYAddr       (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr);
    VDP_FDR_VID_SetMrgCAddr       (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr);
    VDP_FDR_VID_SetMrgYStride     (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr );
    VDP_FDR_VID_SetMrgCStride     (u32RegionOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr );

    XDP_DRV_JudgeRgbColorSpace    (pstInfoIn->stXdpSrcCfg.enSrcClrSpace, &bRgbColorSpace);
    XDP_DRV_AdjustColor           (&stMuteColor,pstInfoIn->stXdpBkgCfg.stMuteColor, bRgbColorSpace);
    VDP_FDR_VID_SetMuteY          (u32FdrOffset, stMuteColor.u32BkgY );
    VDP_FDR_VID_SetMuteCb         (u32FdrOffset, stMuteColor.u32BkgU );
    VDP_FDR_VID_SetMuteCr         (u32FdrOffset, stMuteColor.u32BkgV );
    VDP_VID_SetLayerGalpha        (u32LayerId, pstInfoIn->stXdpSysCfg.u32Alpha);

    if (pstInfoIn->stXdpLayerExtern.bConfigWholeLayer == HI_TRUE)
    {
        if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
            || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422V)
        {
            VDP_FDR_VID_SetChmCopyEn      (u32FdrOffset, HI_TRUE);
        }
        else
        {
            VDP_FDR_VID_SetChmCopyEn      (u32FdrOffset, HI_FALSE);
        }

        VDP_FDR_VID_SetDataFmt (u32FdrOffset, VDP_VID_DATA_FMT_LINEAR) ;

        if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422)
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV422);
        }
        else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420)
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV420);
        }
        else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422V)
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV444);
        }
        else
        {
            VDP_FDR_VID_SetDataType(u32FdrOffset, VDP_VID_DATA_TYPE_YUV422);
        }

        if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422V)
        {
            VDP_VID_SetIfirEn (u32LayerId, 0);
        }
        else
        {
            VDP_VID_SetIfirEn (u32LayerId, 1);
        }

        VDP_FDR_VID_SetMrgEnable      (u32FdrOffset, pstInfoIn->stXdpSysCfg.bRegionModeEn       );
        VDP_FDR_VID_SetMuteReqEn      (u32FdrOffset, pstInfoIn->stXdpSysCfg.bMuteEn             );
        VDP_FDR_VID_SetIresoW         (u32FdrOffset, pstInfoIn->stXdpDispCfg.stFmtReso.u32Wth - 1  );
        VDP_FDR_VID_SetIresoH         (u32FdrOffset, pstInfoIn->stXdpDispCfg.stFmtReso.u32Hgt - 1  );
        VDP_FDR_VID_SetSrcW           (u32FdrOffset, pstInfoIn->stXdpDispCfg.stFmtReso.u32Wth  - 1 );
        VDP_FDR_VID_SetSrcH           (u32FdrOffset, pstInfoIn->stXdpDispCfg.stFmtReso.u32Hgt  - 1 );
        VDP_FDR_VID_SetLmStride       (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr  );
        VDP_FDR_VID_SetChmStride      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr  );
        VDP_FDR_VID_SetLmRmode        (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enReadMode     );
        VDP_FDR_VID_SetChmRmode       (u32FdrOffset, pstInfoIn->stXdpFdrCfg.enReadMode     );
        VDP_FDR_VID_SetDataWidth      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.enDataWidth    );
        VDP_FDR_VID_SetUvOrderEn      (u32FdrOffset, pstInfoIn->stXdpSrcCfg.bUVOrder       );
    }

    /*Secure enable set*/
    VDP_VID_SetNoSecFlag(u32LayerId,!pstInfoIn->stXdpSysCfg.bSecureEn);

    /*Layer enable set*/
    VDP_VID_SetLayerEnable         (u32LayerId, HI_TRUE);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_GetVidZmeStrategy(XDP_LAYER_VID_INFO_S *pstInfoIn,HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio, HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefType)
{
    VDP_RECT_S stZme1Out  = {0};
    HI_S32 s32RatioHL = 100;
    HI_S32 s32RatioHC = 100;
    HI_S32 s32RatioVL = 100;
    HI_S32 s32RatioVC = 100;

    HI_S32 s32Ratio1d0  = 1 * 100;
    HI_S32 s32Ratio0d75 = 3 * 100 / 4;
    HI_S32 s32Ratio0d5  = 1 * 100 / 2;
    HI_S32 s32Ratio0d33 = 1 * 100 / 3;
    HI_S32 s32Ratio0d25 = 1 * 100 / 4;

    if((0 == pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth)
        || (0 == pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt))
    {
        VDP_PRINT("Denominator Is Zero !!!!\n");
        return HI_FAILURE;
    }

    if(( HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable )
      && (HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))
    {
        stZme1Out =  pstInfoIn->stXdpPositionCfg.stVideoRect;
    }
    else
    {
        stZme1Out.u32Wth = pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
        stZme1Out.u32Hgt = pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    }

    s32RatioHL  = (stZme1Out.u32Wth * 100) / pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth;
    s32RatioHC  = (stZme1Out.u32Wth * 100) / pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth;
    s32RatioVL  = (stZme1Out.u32Hgt * 100) / pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt;

    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
        || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE
        || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        s32RatioVC  = s32RatioVL * 2;
    }
    else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422)
    {
        s32RatioVC  = s32RatioVL;
    }

    switch (enPqZmeCoefType)
    {
        case HI_PQ_ZME_COEF_TYPE_LH:
            if (s32RatioHL > s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else  if (s32RatioHL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_E1;
            }
            else if ((s32RatioHL >= s32Ratio0d75) && (s32RatioHL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHL >= s32Ratio0d5) && (s32RatioHL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHL >= s32Ratio0d33) && (s32RatioHL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHL >= s32Ratio0d25) && (s32RatioHL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_CH:
            if (s32RatioHC > s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if (s32RatioHC == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_E1;
            }
            else if ((s32RatioHC >= s32Ratio0d75) && (s32RatioHC < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHC >= s32Ratio0d5) && (s32RatioHC < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHC >= s32Ratio0d33) && (s32RatioHC < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHC >= s32Ratio0d25) && (s32RatioHC < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_LV:
            if (s32RatioVL > s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if (s32RatioVL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_E1;
            }
            else if ((s32RatioVL >= s32Ratio0d75) && (s32RatioVL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioVL >= s32Ratio0d5) && (s32RatioVL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioVL >= s32Ratio0d33) && (s32RatioVL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioVL >= s32Ratio0d25) && (s32RatioVL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_CV:
            if (s32RatioVC > s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if (s32RatioVC == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_E1;
            }
            else if ((s32RatioVC >= s32Ratio0d75) && (s32RatioVC < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioVC >= s32Ratio0d5) && (s32RatioVC < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioVC >= s32Ratio0d33) && (s32RatioVC < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioVC >= s32Ratio0d25) && (s32RatioVC < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            break;

        default:
            *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            break;
    }

    return  HI_SUCCESS;
}

HI_S32 VDP_DRV_GetVidZme2Strategy(XDP_LAYER_VID_INFO_S *pstInfoIn,
                                 HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio,
                                 HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefType)
{
    HI_S32 s32RatioHL = 100;
    HI_S32 s32RatioHC = 100;
    HI_S32 s32RatioVL = 100;

    HI_S32 s32Ratio1d0 = 1 * 100;
    HI_S32 s32Ratio0d75 = 3 * 100 / 4;
    HI_S32 s32Ratio0d5 = 1 * 100 / 2;
    HI_S32 s32Ratio0d25 = 1 * 100 / 4;
    HI_S32 s32Ratio0d33 = 1 * 100 / 3;
    HI_S32 s32Ratio0d2 = 1 * 100 / 5;

    if((0 == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth)
        || (0 ==pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight))
    {
        VDP_PRINT("Denominator is Zero !!!!\n");
        return HI_FAILURE;
    }

    s32RatioHL  = (pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth * 100)/pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    s32RatioHC  = (pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth * 100)/pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    s32RatioVL  = (pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight* 100)/pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;

    switch (enPqZmeCoefType)
    {
        case HI_PQ_ZME_COEF_TYPE_LH:
            if (s32RatioHL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHL >= s32Ratio0d75) && (s32RatioHL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHL >= s32Ratio0d5) && (s32RatioHL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHL >= s32Ratio0d33) && (s32RatioHL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHL >= s32Ratio0d25) && (s32RatioHL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHL >= s32Ratio0d2) && (s32RatioHL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_CH:
            if (s32RatioHC == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioHC >= s32Ratio0d75) && (s32RatioHC < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioHC >= s32Ratio0d5) && (s32RatioHC < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioHC >= s32Ratio0d33) && (s32RatioHC < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioHC >= s32Ratio0d25) && (s32RatioHC < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioHC >= s32Ratio0d2) && (s32RatioHC < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;
        case HI_PQ_ZME_COEF_TYPE_LV:
        case HI_PQ_ZME_COEF_TYPE_CV:
            if (s32RatioVL == s32Ratio1d0)
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            else if ((s32RatioVL >= s32Ratio0d75) && (s32RatioVL < s32Ratio1d0))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_075;
            }
            else if ((s32RatioVL >= s32Ratio0d5) && (s32RatioVL < s32Ratio0d75))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_05;
            }
            else if ((s32RatioVL >= s32Ratio0d33) && (s32RatioVL < s32Ratio0d5))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_033;
            }
            else if ((s32RatioVL >= s32Ratio0d25) && (s32RatioVL < s32Ratio0d33))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_025;
            }
            else if ((s32RatioVL >= s32Ratio0d2) && (s32RatioVL < s32Ratio0d25))
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_0;
            }
            else
            {
                *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            }
            break;

        default:
            *penHiPqZmeCoefRatio = HI_PQ_ZME_COEF_1;
            break;
    }

    return  HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZmeFmt(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_420
        || pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE
        ||  pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_TILE_64)
    {
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_420;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = VDP_PROC_FMT_SP_420;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = VDP_PROC_FMT_SP_422;
    }
    else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_444)
    {
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_444;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_444;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = VDP_PROC_FMT_SP_444;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = VDP_PROC_FMT_SP_444;
    }
    else if (pstInfoIn->stXdpSrcCfg.enInFmt == VDP_VID_IFMT_SP_422)
    {
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = VDP_PROC_FMT_SP_422;
    }
    else
    {
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = VDP_PROC_FMT_SP_422;
        pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = VDP_PROC_FMT_SP_422;
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidHZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if (pstInfoIn->stXdpHZmeCfg.bHzmeEn == HI_TRUE)
    {
        pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth /= 2;
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZme3DCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_U32 u32HorRation = 1;
    HI_U32 u32VerRation = 1;

    if (pstInfoIn->stXdpDispCfg.enDispMode == VDP_DISP_MODE_SBS)
    {
        u32HorRation = 2;
        u32VerRation = 1;
    }
    else if ((pstInfoIn->stXdpDispCfg.enDispMode  == VDP_DISP_MODE_TAB)
             || (pstInfoIn->stXdpDispCfg.enDispMode  == VDP_DISP_MODE_LBL))
    {
        u32HorRation = 1;
        u32VerRation = 2;
    }
    else
    {
        u32HorRation = 1;
        u32VerRation = 1;
    }

    pstInfoIn->stXdpLayerExtern.u32HorRation = u32HorRation;
    pstInfoIn->stXdpLayerExtern.u32VerRation = u32VerRation;

    return HI_SUCCESS;
}

HI_S32  XDP_DRV_GetOptimizePerformance(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if(pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt == 0)
    {
        return HI_FAILURE;
    }
    if ((u32LayerId == VDP_LAYER_VID0)
        && (pstInfoIn->stXdpSrcCfg.stSrcRect.u32Hgt * 10 / pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt > 25 )
        && ((pstInfoIn->stXdpDispCfg.stFmtReso.u32Wth == 3840)||(pstInfoIn->stXdpDispCfg.stFmtReso.u32Hgt == 2160)))
    {
        pstInfoIn->stXdpLayerExtern.bVtapReduce = HI_TRUE;
    }
    //hi3798mv310 zme no need reduce!
    pstInfoIn->stXdpLayerExtern.bVtapReduce = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidZmeRationCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_PQ_ZME_COEF_RATIO_E enRationHL = HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationHC = HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationVL = HI_PQ_ZME_COEF_E1;
    HI_PQ_ZME_COEF_RATIO_E enRationVC = HI_PQ_ZME_COEF_E1;

    VDP_DRV_GetVidZmeStrategy(pstInfoIn, &enRationHL, HI_PQ_ZME_COEF_TYPE_LH);
    VDP_DRV_GetVidZmeStrategy(pstInfoIn, &enRationHC, HI_PQ_ZME_COEF_TYPE_CH);
    VDP_DRV_GetVidZmeStrategy(pstInfoIn, &enRationVL, HI_PQ_ZME_COEF_TYPE_LV);
    VDP_DRV_GetVidZmeStrategy(pstInfoIn, &enRationVC, HI_PQ_ZME_COEF_TYPE_CV);

    pstInfoIn->stXdpLayerExtern.enRationHL = enRationHL;
    pstInfoIn->stXdpLayerExtern.enRationHC = enRationHC;
    pstInfoIn->stXdpLayerExtern.enRationVL = enRationVL;
    pstInfoIn->stXdpLayerExtern.enRationVC = enRationVC;

    if((HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable)
        || (HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))
    {

        VDP_DRV_GetVidZme2Strategy(pstInfoIn, &enRationHL, HI_PQ_ZME_COEF_TYPE_LH);
        VDP_DRV_GetVidZme2Strategy(pstInfoIn, &enRationHC, HI_PQ_ZME_COEF_TYPE_CH);
        VDP_DRV_GetVidZme2Strategy(pstInfoIn, &enRationVL, HI_PQ_ZME_COEF_TYPE_LV);
        VDP_DRV_GetVidZme2Strategy(pstInfoIn, &enRationVC, HI_PQ_ZME_COEF_TYPE_CV);

        pstInfoIn->stXdpLayerExtern.enZme2RationHL = enRationHL;
        pstInfoIn->stXdpLayerExtern.enZme2RationHC = enRationHC;
        pstInfoIn->stXdpLayerExtern.enZme2RationVL = enRationVL;
        pstInfoIn->stXdpLayerExtern.enZme2RationVC = enRationVC;
    }

    return HI_SUCCESS;
}

HI_U32 AlignDown(HI_S32 s32X, HI_U32 u32A)
{
    if (0 == u32A)
    {
        return s32X;
    }
    else
    {
        return (( s32X / u32A ) * u32A);
    }
}

HI_S32 XDP_DRV_GetVidZmeCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if (pstInfoIn->stXdpLayerExtern.u32LinkEn == 1)
    {
        return HI_FAILURE;
    }
    if(u32LayerId == VDP_LAYER_VID0)
    {
        XDP_DRV_GetVidZmeFmt(u32LayerId,pstInfoIn);
        XDP_DRV_GetVidHZme(u32LayerId, pstInfoIn);
        XDP_DRV_GetVidZme3DCfg(u32LayerId, pstInfoIn);
        XDP_DRV_GetOptimizePerformance(u32LayerId, pstInfoIn);
        XDP_DRV_GetVidZmeRationCoef(u32LayerId, pstInfoIn);
    }

    pstInfoIn->stXdpPositionCfg.stDispRect.u32Wth = AlignDown(pstInfoIn->stXdpPositionCfg.stDispRect.u32Wth, 2);
    pstInfoIn->stXdpPositionCfg.stDispRect.u32Hgt = AlignDown(pstInfoIn->stXdpPositionCfg.stDispRect.u32Hgt, 2);
    pstInfoIn->stXdpPositionCfg.stVideoRect.u32Wth = AlignDown(pstInfoIn->stXdpPositionCfg.stVideoRect.u32Wth, 2);
    pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt = AlignDown(pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt, 2);
    pstInfoIn->stXdpPositionCfg.stVp0DispRect.u32Wth = AlignDown(pstInfoIn->stXdpPositionCfg.stVp0DispRect.u32Wth, 2);
    pstInfoIn->stXdpPositionCfg.stVp0DispRect.u32Hgt = AlignDown(pstInfoIn->stXdpPositionCfg.stVp0DispRect.u32Hgt, 2);

    pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Wth = AlignDown(pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Wth, 2);
    pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Hgt = AlignDown(pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Hgt, 2);

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidIfir(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_S32 s32V0IfirCoef[8] = {-7, 12, -17, 25, -38, 58, -105, 328};
    HI_S32 s32V1IfirCoef[8] = {0,  0,   0,  0,   0,  0,  -10,   42};

    if(u32LayerId == VDP_LAYER_VID0)
    {
        VDP_VID_SetIfirCoef (u32LayerId,s32V0IfirCoef);
        VDP_VID_SetIfirMode (u32LayerId, VDP_IFIRMODE_6TAPFIR);
    }
    if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_VID_SetIfirCoef (u32LayerId,s32V1IfirCoef);
        VDP_VID_SetIfirMode (u32LayerId, VDP_IFIRMODE_COPY);
    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidHZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if (HI_FALSE == pstInfoIn->stXdpHZmeCfg.bHzmeEn)
    {
        VDP_VID_SetHpzmeEn(VDP_LAYER_VID0, 0);
        return HI_SUCCESS;
    }

    VDP_VID_SetHpzmeEn(u32LayerId, pstInfoIn->stXdpHZmeCfg.bHzmeEn);
    VDP_VID_SetHpzmeMode(u32LayerId, pstInfoIn->stXdpHZmeCfg.enHzmeMode);

    VDP_VID_SetHpzmeCoef0(u32LayerId, 6);
    VDP_VID_SetHpzmeCoef1(u32LayerId, 52);
    VDP_VID_SetHpzmeCoef2(u32LayerId, 6);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidZme1(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_U32 u32RatioH = 1;
    HI_U32 u32RatioV = 1;

    VDP_RECT_S stZme1In  = {0};
    VDP_RECT_S stZme1Out = {0};

    if(( HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable )
      && (HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable))
    {
        VDP_VID_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HOR, 0);
        VDP_VID_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VER, 0);
        return HI_SUCCESS;
    }

    stZme1In.u32Wth = pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth;
    stZme1In.u32Hgt = pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt;

    if(( HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable )
      && (HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))
    {
        stZme1Out =  pstInfoIn->stXdpPositionCfg.stVideoRect;
    }
    else
    {
        stZme1Out = pstInfoIn->stXdpZmeCfg.stZme2InRect;
    }
    VDP_VID_SetZmeOutReso       (u32LayerId, stZme1Out);

    if (stZme1In.u32Hgt >= stZme1Out.u32Hgt)
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 0, 0);
    }
    else
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 1, 0);
    }

    if (stZme1In.u32Wth >= stZme1Out.u32Wth)
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 0, 0);
    }
    else
    {
      VDP_VID_SetZmeShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 1, 0);
    }

    VDP_VID_SetZmeEnable  (u32LayerId, VDP_ZME_MODE_HOR, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable);
    VDP_VID_SetZmeEnable  (u32LayerId, VDP_ZME_MODE_VER, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable);

    if ((stZme1Out.u32Wth ==0)||(stZme1Out.u32Hgt==0))
    {
        VDP_PRINT("Denominator Is Zero !!!!\n");
        return HI_FAILURE;
    }

    u32RatioH  = (stZme1In.u32Wth / 2 * ZME_HPREC) / stZme1Out.u32Wth * 2 * pstInfoIn->stXdpLayerExtern.u32HorRation;
    u32RatioV  = (stZme1In.u32Hgt * ZME_VPREC) / stZme1Out.u32Hgt * pstInfoIn->stXdpLayerExtern.u32VerRation;
    VDP_VID_SetZmeHorRatio(u32LayerId, u32RatioH);
    VDP_VID_SetZmeVerRatio(u32LayerId, u32RatioV);

    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERL,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVL);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERC,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVC);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERBL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVLBtm);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_VERBC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetVCBtm);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_HORL,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHL);
    VDP_VID_SetZmePhase   (u32LayerId, VDP_ZME_MODE_HORC,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].stZmeOffset.s32ZmeOffsetHC);
    VDP_VID_SetZmeInFmt   (u32LayerId, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt );
    VDP_VID_SetZmeOutFmt  (u32LayerId, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt);


    VDP_VID_SetZmeHfirOrder(u32LayerId, VDP_ZME_ORDER_VH);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_HORL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_HORC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_VERL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL);
    VDP_VID_SetZmeFirEnable(u32LayerId, VDP_ZME_MODE_VERC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC);

    VDP_VID_SetZmeMidEnable(u32LayerId, VDP_ZME_MODE_VER, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV);
    VDP_VID_SetZmeMidEnable(u32LayerId, VDP_ZME_MODE_HOR, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidZme2(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_U32 u32RatioH = 1;
    HI_U32 u32RatioV = 1;
    VDP_RECT_S stZme2In  = {0};
    VDP_RECT_S stZme2Out = {0};

    if((HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable)
      && (HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))
    {
        VDP_VID_SetZme2Enable(u32LayerId, VDP_ZME_MODE_HOR, 0);
        VDP_VID_SetZme2Enable(u32LayerId, VDP_ZME_MODE_VER, 0);
        return HI_SUCCESS;
    }

    stZme2Out =  pstInfoIn->stXdpPositionCfg.stVideoRect;

    if(( HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable )
      && (HI_FALSE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable))
    {
        stZme2In.u32Wth = pstInfoIn->stXdpFdrCfg.stCropRect.u32Wth;
        stZme2In.u32Hgt = pstInfoIn->stXdpFdrCfg.stCropRect.u32Hgt;
    }
    else
    {
        stZme2In.u32Wth = pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Wth;
        stZme2In.u32Hgt = pstInfoIn->stXdpZmeCfg.stZme2InRect.u32Hgt;

        pstInfoIn->stXdpLayerExtern.u32HorRation = 1;
        pstInfoIn->stXdpLayerExtern.u32VerRation = 1;
    }
    VDP_VID_SetZme2OutReso      (u32LayerId, pstInfoIn->stXdpPositionCfg.stVideoRect);

    if (stZme2In.u32Hgt >= pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt)
    {
      VDP_VID_SetZme2ShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 0, 0);
    }
    else
    {
      VDP_VID_SetZme2ShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_VER, 1, 0);
    }

    if (stZme2In.u32Wth >= pstInfoIn->stXdpPositionCfg.stVideoRect.u32Wth)
    {
      VDP_VID_SetZme2ShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 0, 0);
    }
    else
    {
      VDP_VID_SetZme2ShootCtrlEnable  (u32LayerId, VDP_ZME_MODE_HOR, 1, 0);
    }

    if ((pstInfoIn->stXdpPositionCfg.stVideoRect.u32Wth ==0)||(pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt==0))
    {
        VDP_PRINT("Denominator is Zero !!!!\n");
        return HI_FAILURE;
    }
    u32RatioH  = (stZme2In.u32Wth / 2 * ZME_HPREC) / pstInfoIn->stXdpPositionCfg.stVideoRect.u32Wth * 2 * pstInfoIn->stXdpLayerExtern.u32HorRation;
    u32RatioV  = (stZme2In.u32Hgt * ZME_VPREC) / pstInfoIn->stXdpPositionCfg.stVideoRect.u32Hgt * pstInfoIn->stXdpLayerExtern.u32VerRation;
    VDP_VID_SetZme2HorRatio(u32LayerId, u32RatioH);
    VDP_VID_SetZme2VerRatio(u32LayerId, u32RatioV);

    VDP_VID_SetZme2Enable              (u32LayerId, VDP_ZME_MODE_HOR, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable);
    VDP_VID_SetZme2Enable              (u32LayerId, VDP_ZME_MODE_VER,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable);

    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_VERL,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVL);
    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_VERC,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVC);
    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_VERBL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVLBtm);
    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_VERBC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetVCBtm);
    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_HORL,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHL);
    VDP_VID_SetZme2Phase    (u32LayerId, VDP_ZME_MODE_HORC,  pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].stZmeOffset.s32ZmeOffsetHC);
    VDP_VID_SetZme2InFmt    (u32LayerId, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt );
    VDP_VID_SetZme2OutFmt   (u32LayerId, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt);
    VDP_VID_SetZme2FirEnable(u32LayerId, VDP_ZME_MODE_HORL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL);
    VDP_VID_SetZme2FirEnable(u32LayerId, VDP_ZME_MODE_HORC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC);
    VDP_VID_SetZme2FirEnable(u32LayerId, VDP_ZME_MODE_VERL, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL);
    VDP_VID_SetZme2FirEnable(u32LayerId, VDP_ZME_MODE_VERC, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC);
    VDP_VID_SetZme2MidEnable(u32LayerId, VDP_ZME_MODE_VER, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV);
    VDP_VID_SetZme2MidEnable(u32LayerId, VDP_ZME_MODE_HOR, pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVidZmePerformance(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if (HI_TRUE == pstInfoIn->stXdpLayerExtern.bVtapReduce)
    {
        VDP_VID_SetZme1ReduceTap(u32LayerId,  1 );
        VDP_VID_SetZme2ReduceTap(u32LayerId,  1 );
    }
    return HI_SUCCESS;
}

HI_PQ_ZME_COEF_RATIO_E enZME1RationHL =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME1RationHC =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME1RationVL =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME1RationVC =  HI_PQ_ZME_COEF_RATIO_BUTT;

HI_PQ_ZME_COEF_RATIO_E enZME2RationHL =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME2RationHC =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME2RationVL =  HI_PQ_ZME_COEF_RATIO_BUTT;
HI_PQ_ZME_COEF_RATIO_E enZME2RationVC =  HI_PQ_ZME_COEF_RATIO_BUTT;

HI_S32 VDP_DRV_SetZmeCoef(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn )
{
#if 1
    HI_BOOL bPQZmeCoefRefresh = pstInfoIn->stXdpLayerExtern.bPQZmeCoefRefresh;
    //HI_BOOL bPQZmeCoefRefresh = HI_FALSE;

    VDP_COEF_BUF_E enVdpCoefBufZmeHTmp = VDP_COEF_BUF_ZMEH;
    VDP_COEF_BUF_E enVdpCoefBufZmeVTmp = VDP_COEF_BUF_ZMEV;

    enVdpCoefBufZmeHTmp = VDP_COEF_BUF_ZMEH ;
    enVdpCoefBufZmeVTmp = VDP_COEF_BUF_ZMEV ;


    if (pstInfoIn->stXdpLayerExtern.enRationHL >= HI_PQ_ZME_COEF_RATIO_BUTT)
    {
        VDP_PRINT("enRationHL arange Error !!! \n");
        return HI_FAILURE;
    }
    if (pstInfoIn->stXdpLayerExtern.enRationHC >= HI_PQ_ZME_COEF_RATIO_BUTT)
    {
        VDP_PRINT("enRationHC arange Error !!! \n");
        return HI_FAILURE;
    }
    if (pstInfoIn->stXdpLayerExtern.enRationVL >= HI_PQ_ZME_COEF_RATIO_BUTT)
    {
        VDP_PRINT("enRationVL arange Error !!! \n");
        return HI_FAILURE;
    }
    if (pstInfoIn->stXdpLayerExtern.enRationVC >= HI_PQ_ZME_COEF_RATIO_BUTT)
    {
        VDP_PRINT("enRationVC arange Error !!! \n");
        return HI_FAILURE;
    }

    if ( (HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable)
        || (HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable))
    {
        if(HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeHTmp]
         || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp]
         || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP])
        {
            VDP_PRINT("zme1 coef PTR Is NUll Please check it !!! \n");
            return HI_FAILURE;
        }

        if (enZME1RationHL  !=  pstInfoIn->stXdpLayerExtern.enRationHL
            || bPQZmeCoefRefresh)
        {
            enZME1RationHL  =  pstInfoIn->stXdpLayerExtern.enRationHL;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationHL, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeHTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }
        if (enZME1RationHC  !=  pstInfoIn->stXdpLayerExtern.enRationHC
            || bPQZmeCoefRefresh)
        {
            enZME1RationHC  =  pstInfoIn->stXdpLayerExtern.enRationHC;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationHC, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CH, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeHTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }

        if (HI_TRUE == pstInfoIn->stXdpLayerExtern.bVtapReduce)
        {
            if (enZME1RationVL  !=  pstInfoIn->stXdpLayerExtern.enRationVL
                || bPQZmeCoefRefresh)
            {
                enZME1RationVL  =  pstInfoIn->stXdpLayerExtern.enRationVL;
                GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_5T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
                DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_5LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            }
            if (enZME1RationVC  !=  pstInfoIn->stXdpLayerExtern.enRationVC
                || bPQZmeCoefRefresh)
            {
                enZME1RationVC  =  pstInfoIn->stXdpLayerExtern.enRationVC;
                GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_3T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
                DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_3CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            }
        }
        else
        {
            if (enZME1RationVL  !=  pstInfoIn->stXdpLayerExtern.enRationVL
                || bPQZmeCoefRefresh)
            {
                enZME1RationVL  =  pstInfoIn->stXdpLayerExtern.enRationVL;
                GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
                DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_6LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            }
            if (enZME1RationVC  !=  pstInfoIn->stXdpLayerExtern.enRationVC
                || bPQZmeCoefRefresh)
            {
                enZME1RationVC  =  pstInfoIn->stXdpLayerExtern.enRationVC;
                GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enRationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
                DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[enVdpCoefBufZmeVTmp] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            }
        }

        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeHTmp]));
        VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[enVdpCoefBufZmeVTmp]));


        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_HOR);
        VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_VER);

    }

    if ((HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable)
        || (HI_TRUE == pstInfoIn->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable))
    {
        if(HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2H]
         || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2V]
         || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP])
        {
            VDP_PRINT("ZME 2 PTR Is NUll Please check it !!! \n");
            return HI_FAILURE;
        }

        if (pstInfoIn->stXdpLayerExtern.enZme2RationHL >= HI_PQ_ZME_COEF_RATIO_BUTT)
        {
            VDP_PRINT("enRationHL arange Error !!! \n");
            return HI_FAILURE;
        }
        if (pstInfoIn->stXdpLayerExtern.enZme2RationHC >= HI_PQ_ZME_COEF_RATIO_BUTT)
        {
            VDP_PRINT("enRationHC arange Error !!! \n");
            return HI_FAILURE;
        }
        if (pstInfoIn->stXdpLayerExtern.enZme2RationVL >= HI_PQ_ZME_COEF_RATIO_BUTT)
        {
            VDP_PRINT("enRationVL arange Error !!! \n");
            return HI_FAILURE;
        }
        if (pstInfoIn->stXdpLayerExtern.enZme2RationVC >= HI_PQ_ZME_COEF_RATIO_BUTT)
        {
            VDP_PRINT("enRationVC arange Error !!! \n");
            return HI_FAILURE;
        }
        if (enZME2RationHL  !=  pstInfoIn->stXdpLayerExtern.enZme2RationHL
            || bPQZmeCoefRefresh)
        {
            enZME2RationHL  =  pstInfoIn->stXdpLayerExtern.enZme2RationHL;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enZme2RationHL, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2H]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }
        if (enZME2RationHC  !=  pstInfoIn->stXdpLayerExtern.enZme2RationHC
            || bPQZmeCoefRefresh)
        {
            enZME2RationHC  =  pstInfoIn->stXdpLayerExtern.enZme2RationHC;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enZme2RationHC, HI_PQ_ZME_COEF_TYPE_CH, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2H] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }
        if (enZME2RationVL  !=  pstInfoIn->stXdpLayerExtern.enZme2RationVL
            || bPQZmeCoefRefresh)
        {
            enZME2RationVL  =  pstInfoIn->stXdpLayerExtern.enZme2RationVL;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enZme2RationVL, HI_PQ_ZME_COEF_TYPE_LV, HI_PQ_ZME_TAP_6T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_6LV, HI_PQ_ZME_COEF_TYPE_LV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2V]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }
        if (enZME2RationVC  !=  pstInfoIn->stXdpLayerExtern.enZme2RationVC
            || bPQZmeCoefRefresh)
        {
            enZME2RationVC  =  pstInfoIn->stXdpLayerExtern.enZme2RationVC;
            GetVdpZmeCoef(pstInfoIn->stXdpLayerExtern.enZme2RationVC, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CV, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME2V] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
        }

        VDP_VID_SetZme2CoefAddr(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME2H]));
        VDP_VID_SetZme2CoefAddr(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME2V]));

        VDP_VID_SetParaUpd(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_HOR);
        VDP_VID_SetParaUpd(VDP_LAYER_VID0, VDP_VID_PARA_ZME2_VER);
    }
#endif
    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidZme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    if(u32LayerId == VDP_LAYER_VID0)
    {
        VDP_DRV_SetVidHZme(u32LayerId, pstInfoIn);
        VDP_DRV_SetVidZme1(u32LayerId, pstInfoIn);
        VDP_DRV_SetVidZme2(u32LayerId, pstInfoIn);
        VDP_DRV_SetVidZmePerformance(u32LayerId, pstInfoIn);
        VDP_DRV_SetZmeCoef(u32LayerId, pstInfoIn);
    }
    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidReso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    VDP_VID_SetVideoPos         (u32LayerId, pstInfoIn->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetDispPos          (u32LayerId, pstInfoIn->stXdpPositionCfg.stDispRect) ;

    if (u32LayerId == VDP_LAYER_VID1 && pstInfoIn->stXdpSysCfg.bRegionModeEn == 1)
    {
        VDP_VID_SetDispPos      (u32LayerId, pstInfoIn->stXdpDispCfg.stFmtReso) ;
        VDP_VID_SetVideoPos     (u32LayerId, pstInfoIn->stXdpDispCfg.stFmtReso);
    }
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_GetCscMode(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    VDP_CSC_MODE_E enTmpCscMode = VDP_CSC_BUTT;
    HI_PQ_CSC_MODE_E enTmpPqCscMode = HI_PQ_CSC_BUTT;

    VDP_CLR_SPACE_E enTmpInClr  = pstInfoOut->stXdpSrcCfg.enSrcClrSpace;
    VDP_CLR_SPACE_E enTmpOutClr = pstInfoOut->stXdpDispCfg.enOutClrSpace;
    HI_U32 i = 0;
    HI_U32 j = 0;

    VDP_CSC_INFO stCscModeInfo[] =
    {
        {VDP_CLR_SPACE_YUV_601_L, VDP_CLR_SPACE_YUV_601_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV},
        {VDP_CLR_SPACE_YUV_601_L, VDP_CLR_SPACE_YUV_709_L, VDP_CSC_YUV2YUV_601_709, HI_PQ_CSC_YUV2YUV_601_709},
        {VDP_CLR_SPACE_YUV_601_L, VDP_CLR_SPACE_YUV_2020_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV},
        {VDP_CLR_SPACE_YUV_601_L, VDP_CLR_SPACE_RGB_709, VDP_CSC_YUV2RGB_709, HI_PQ_CSC_YUV2RGB_709},

        {VDP_CLR_SPACE_YUV_709_L, VDP_CLR_SPACE_YUV_601_L, VDP_CSC_YUV2YUV_709_601, HI_PQ_CSC_YUV2YUV_709_601},
        {VDP_CLR_SPACE_YUV_709_L, VDP_CLR_SPACE_YUV_709_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV},
        {VDP_CLR_SPACE_YUV_709_L, VDP_CLR_SPACE_YUV_2020_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV},
        {VDP_CLR_SPACE_YUV_709_L, VDP_CLR_SPACE_RGB_709, VDP_CSC_YUV2RGB_709, HI_PQ_CSC_YUV2RGB_709},

        {VDP_CLR_SPACE_YUV_2020_L, VDP_CLR_SPACE_YUV_601_L, VDP_CSC_YUV2YUV_2020_601_L_L, HI_PQ_CSC_YUV2YUV_2020_601_L_L},
        {VDP_CLR_SPACE_YUV_2020_L, VDP_CLR_SPACE_YUV_709_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV_2020_709_L_L},
        {VDP_CLR_SPACE_YUV_2020_L, VDP_CLR_SPACE_YUV_2020_L, VDP_CSC_YUV2YUV, HI_PQ_CSC_YUV2YUV},
        {VDP_CLR_SPACE_YUV_2020_L, VDP_CLR_SPACE_RGB_709, VDP_CSC_YUV2RGB_709, HI_PQ_CSC_YUV2RGB_2020_709_L},

        {VDP_CLR_SPACE_RGB_709, VDP_CLR_SPACE_YUV_601_L, VDP_CSC_RGB2YUV_601, HI_PQ_CSC_RGB2YUV_601},
        {VDP_CLR_SPACE_RGB_709, VDP_CLR_SPACE_YUV_709_L, VDP_CSC_RGB2YUV_709, HI_PQ_CSC_RGB2YUV_709},
        {VDP_CLR_SPACE_RGB_709, VDP_CLR_SPACE_YUV_2020_L, VDP_CSC_RGB2YUV_2020_2020_L, HI_PQ_CSC_RGB2YUV_2020_2020_L},
        {VDP_CLR_SPACE_RGB_709, VDP_CLR_SPACE_RGB_709, VDP_CSC_RGB2RGB, VDP_CSC_RGB2RGB},
    };

    if ((enTmpInClr == VDP_CLR_SPACE_BUTT) || (enTmpOutClr == VDP_CLR_SPACE_BUTT))
    {
        VDP_PRINT("enTmpInClr or enTmpOutClr value is buttom\n");
        return HI_FAILURE;
    }

    if ((VDP_CLR_SPACE_YUV_601 == enTmpInClr) || (VDP_CLR_SPACE_YUV_601_L == enTmpInClr))
    {
        enTmpInClr = VDP_CLR_SPACE_YUV_601_L;
    }
    else if ((VDP_CLR_SPACE_YUV_2020 == enTmpInClr) || (VDP_CLR_SPACE_YUV_2020_L == enTmpInClr))
    {
        enTmpInClr = VDP_CLR_SPACE_YUV_2020_L;
    }
    else if ((VDP_CLR_SPACE_RGB_601 == enTmpInClr)
            || (VDP_CLR_SPACE_RGB_709 == enTmpInClr)
            || (VDP_CLR_SPACE_RGB_2020 == enTmpInClr)
            || (VDP_CLR_SPACE_RGB_601_L == enTmpInClr)
            || (VDP_CLR_SPACE_RGB_709_L == enTmpInClr)
            || (VDP_CLR_SPACE_RGB_2020_L == enTmpInClr))
    {
        enTmpInClr = VDP_CLR_SPACE_RGB_709;
    }
    else
    {
        enTmpInClr = VDP_CLR_SPACE_YUV_709_L;
    }

    if ((VDP_CLR_SPACE_YUV_601 == enTmpOutClr) || (VDP_CLR_SPACE_YUV_601_L == enTmpOutClr))
    {
        enTmpOutClr = VDP_CLR_SPACE_YUV_601_L;
    }
    else if ((VDP_CLR_SPACE_YUV_709 == enTmpOutClr) || (VDP_CLR_SPACE_YUV_709_L == enTmpOutClr))
    {
        enTmpOutClr = VDP_CLR_SPACE_YUV_709_L;
    }
    else if ((VDP_CLR_SPACE_YUV_2020 == enTmpOutClr) || (VDP_CLR_SPACE_YUV_2020_L == enTmpOutClr))
    {
        enTmpOutClr = VDP_CLR_SPACE_YUV_2020_L;
    }
    else
    {
        enTmpOutClr = VDP_CLR_SPACE_RGB_709;
    }

    for (i = 0; i < sizeof(stCscModeInfo) / sizeof(VDP_CSC_INFO); i++)
    {
        if (stCscModeInfo[i].enTmpInClr == enTmpInClr)
        {
            for (j = i; j < sizeof(stCscModeInfo) / sizeof(VDP_CSC_INFO); j++)
            {
                if (stCscModeInfo[j].enTmpOutClr == enTmpOutClr)
                {

                    enTmpCscMode = stCscModeInfo[j].enCscMode;
                    enTmpPqCscMode = stCscModeInfo[j].enPqCscMode;
                    break;
                }
            }

            break;
        }
    }

    if ((VDP_CSC_BUTT == enTmpCscMode) || (HI_PQ_CSC_BUTT == enTmpPqCscMode))
    {
        VDP_PRINT("No this breach (enTmpInClr:%d, enTmpOutClr:%d)\n", enTmpInClr, enTmpOutClr);
        return HI_FAILURE;
    }

    *enCscMode = enTmpCscMode;
    *enPqCscMode = enTmpPqCscMode;

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_AdjustVidCscInfo(HI_U32 u32LayerId, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
    if (u32LayerId == VDP_LAYER_VID0)
    {
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef00 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef01 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef02 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef10 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef11 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef12 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef20 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef21 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef.csc_coef22 *= 4;
    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef00 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef01 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef02 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef10 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef11 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef12 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef20 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef21 *= 4;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef.csc_coef22 *= 4;
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidCscInfo(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
    HI_PQ_CSC_CRTL_S stCscCtrl = {0};
    VDP_CSC_MODE_E enCscMode = HI_PQ_CSC_BUTT;
    HI_PQ_CSC_MODE_E enPqCscMode = HI_PQ_CSC_BUTT;
    HI_PQ_CSC_COEF_S   stPqCscCoef = {0};
    HI_PQ_CSC_DCCOEF_S stPqCscDc = {0};
    HI_PQ_CSC_TYPE_E enHiPqCscType = HI_PQ_CSC_TUNING_V0;

    VDP_DRV_GetCscMode(u32LayerId, pstInfoIn, &enCscMode, &enPqCscMode);

    if(enPqCscMode >= HI_PQ_CSC_BUTT)
    {
        //VDP_PRINT("enPqCscMode arange Error !!! \n");
        return HI_FAILURE;
    }


    if (u32LayerId == VDP_LAYER_VID0)
    {
        stCscCtrl.bCSCEn    = HI_TRUE;
        stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;
        enHiPqCscType =  HI_PQ_CSC_TUNING_V0;

        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].enCbbCscMode = enCscMode;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V0].enPqCscMode  = enPqCscMode;
    }
    else  if (u32LayerId == VDP_LAYER_VID1)
    {
        stCscCtrl.bCSCEn    = HI_TRUE;
        stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V1;
        enHiPqCscType =  HI_PQ_CSC_TUNING_V1;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].enCbbCscMode = enCscMode;
        stXdpCscCfg[HI_PQ_CSC_TUNING_V1].enPqCscMode  = enPqCscMode;
    }

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);
    memcpy(&stXdpCscCfg[enHiPqCscType].stPqCscCoef, &stPqCscCoef, sizeof(stXdpCscCfg[enHiPqCscType].stPqCscCoef));
    memcpy(&stXdpCscCfg[enHiPqCscType].stPqCscDc,   &stPqCscDc,   sizeof(stXdpCscCfg[enHiPqCscType].stPqCscDc));

    XDP_DRV_AdjustVidCscInfo(u32LayerId, stXdpCscCfg);

    return HI_SUCCESS;

}

HI_S32 XDP_DRV_SetVidCsc(HI_U32 u32LayerId, XDP_CSC_CFG_S  stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT])
{
#ifndef  __DISP_PLATFORM_BOOT__
    VDP_HIHDR_V_SetHihdrY2rV1Scale2p( 12);
    VDP_HIHDR_V_SetHihdrY2rV0Scale2p( 12);

    VDP_HIHDR_V_SetHihdrY2rV1ClipMin( 0);
    VDP_HIHDR_V_SetHihdrY2rV0ClipMin( 0);
    VDP_HIHDR_V_SetHihdrY2rV1ClipMax( 1023);
    VDP_HIHDR_V_SetHihdrY2rV0ClipMax( 1023);

	VDP_HIHDR_V_SetVhdrDitherEn( 0);
    VDP_HIHDR_V_SetHihdrY2rEn( 1);

    if (u32LayerId == VDP_LAYER_VID0)
    {
    	VDP_HIHDR_V_SetHihdrV0Y2rEn( 1);

        VDP_FUNC_SetCSC1Coef(&stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscCoef);
        VDP_FUNC_SetCSC1DcCoef(&stXdpCscCfg[HI_PQ_CSC_TUNING_V0].stPqCscDc);

    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
    	VDP_HIHDR_V_SetHihdrV1Y2rEn( 1);

        VDP_FUNC_SetCSC2Coef(&stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscCoef);
        VDP_FUNC_SetCSC2DcCoef(&stXdpCscCfg[HI_PQ_CSC_TUNING_V1].stPqCscDc);

    }
#endif

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidBkg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    HI_BOOL bRgbColorSpace = HI_FALSE;
    VDP_BKG_S   stMixvColor;

    /* set the mixv background color for out colorspace,beacause mixvbkg no csc process*/
    XDP_DRV_JudgeRgbColorSpace(pstInfoIn->stXdpDispCfg.enOutClrSpace, &bRgbColorSpace);
    XDP_DRV_AdjustColor(&stMixvColor,pstInfoIn->stXdpBkgCfg.stMixvColor, bRgbColorSpace);

    VDP_CBM_SetMixerBkg(VDP_CBM_MIXV0, stMixvColor);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        XDP_DRV_JudgeRgbColorSpace(pstInfoIn->stXdpSrcCfg.enSrcClrSpace, &bRgbColorSpace);
        VDP_DRV_SetLayerLetterboxBkg(bRgbColorSpace);
    }

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_GetVidSceneMode(HI_U32 u32LayerId,XDP_LAYER_VID_INFO_S *pstInfoIn,HIHDR_SCENE_MODE_E *penSceneMode)
{
    XDP_VIDEO_FRAME_TYPE_E enFrmType   = pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType;
    XDP_DISP_OUT_TYPE_E  enDisPlayMode = pstInfoIn->stXdpDispCfg.enDisPlayMode;

    switch (enDisPlayMode)
    {
        case XDP_DISP_TYPE_NORMAL:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    if (((VDP_CLR_SPACE_YUV_2020    == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace ))&&
                        ((VDP_CLR_SPACE_YUV_709     == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                        || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                        || (VDP_CLR_SPACE_RGB_709   == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_YUV_601   == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_YUV_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601 == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )))
                    {
                        *penSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else if (((VDP_CLR_SPACE_YUV_709   == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                              || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                              || (VDP_CLR_SPACE_YUV_601_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                              || (VDP_CLR_SPACE_YUV_601 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace ) ) &&
                        ((VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                        || (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                        || (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )))
                    {
                        *penSceneMode = HIHDR_709_IN_BT2020_OUT;
                    }
                    else if(((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace ) ||
                        (VDP_CLR_SPACE_YUV_2020 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )))
                    {
                     *penSceneMode = HIHDR_BT2020_IN_2020_OUT;
                    }
                    else
                    {
                        *penSceneMode = HIHDR_BYPASS_MODE;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = HIHDR_HDR10_IN_SDR_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    *penSceneMode = HIHDR_HLG_IN_SDR_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *penSceneMode = HIHDR_SLF_IN_SDR_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *penSceneMode = HIHDR_TECHNI_IN_SDR_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_HDR10:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *penSceneMode = HIHDR_SDR_IN_HDR10_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    if(((VDP_CLR_SPACE_YUV_709   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                         || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_709 == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_YUV_601   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                         || (VDP_CLR_SPACE_YUV_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601 == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace ))
                         &&
                        ((VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *penSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else  if(((VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                               || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                               || (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                               || (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_709   == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *penSceneMode = HIHDR_709_IN_BT2020_OUT;

                    }
                    else if(((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace ) ||
                        (VDP_CLR_SPACE_YUV_2020 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                        )
                    )
                    {
                     *penSceneMode = HIHDR_BT2020_IN_2020_OUT;
                    }
                    else
                    {
                        *penSceneMode = HIHDR_BYPASS_MODE;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    *penSceneMode = HIHDR_HLG_IN_HDR10_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *penSceneMode = HIHDR_SLF_IN_HDR10_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *penSceneMode = HIHDR_TECHNI_IN_HDR10_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }

            break;
        case XDP_DISP_TYPE_HLG:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *penSceneMode = HIHDR_SDR_IN_HLG_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_HLG:
                    if(((VDP_CLR_SPACE_YUV_709   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                         || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_709 == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_709_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_YUV_601   == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_YUV_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601 == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                         || (VDP_CLR_SPACE_RGB_601_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                        || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *penSceneMode = HIHDR_BT2020_IN_709_OUT;
                    }
                    else  if(((VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace)
                               || (VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                               || (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                               || (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_709   == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_YUV_709_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_YUV_601_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_YUV_601 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_RGB_601_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )
                               || (VDP_CLR_SPACE_RGB_601 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )))
                    {
                        *penSceneMode = HIHDR_709_IN_BT2020_OUT;

                    }
                    else if(((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpSrcCfg.enSrcClrSpace ) ||
                        (VDP_CLR_SPACE_YUV_2020 == pstInfoIn->stXdpSrcCfg.enSrcClrSpace )) &&
                        ((VDP_CLR_SPACE_YUV_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_YUV_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020   == pstInfoIn->stXdpDispCfg.enOutClrSpace ) ||
                         (VDP_CLR_SPACE_RGB_2020_L == pstInfoIn->stXdpDispCfg.enOutClrSpace )
                        )
                    )
                    {
                     *penSceneMode = HIHDR_BT2020_IN_2020_OUT;
                    }
                    else
                    {
                        *penSceneMode = HIHDR_BYPASS_MODE;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = HIHDR_HDR10_IN_HLG_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SLF:
                    *penSceneMode = HIHDR_SLF_IN_HLG_OUT;
                    break;
                case XDP_VIDEO_FRAME_TYPE_TECHNICOLOR:
                    *penSceneMode = HIHDR_TECHNI_IN_HLG_OUT;
                    break;

                default:
                    VDP_PRINT("Not valid frame.\n");
                    break;
            }
        break;
        case XDP_DISP_TYPE_TECHNICOLOR:
            VDP_PRINT("Unsupport mode currently.\n");
            // TODO:
            break;
        default:
            *penSceneMode = HIHDR_BYPASS_MODE;
            break;
    }

    if(*penSceneMode != HIHDR_BYPASS_MODE)
    {
        if(pstInfoIn->stXdpSysCfg.u32VdmOnLayerId != u32LayerId)
        {
            *penSceneMode = HIHDR_BYPASS_MODE;
        }
    }

    if (*penSceneMode >= HIHDR_SCENE_BUTT)
    {
        VDP_PRINT("*penSceneMode arange Error !!! \n");
    }

    return HI_SUCCESS;
}

HI_VOID VDP_DRV_GetHiHdrAjust(HI_U32 u32LayerId, HI_PQ_HDR_CFG  *pstPqHdrCfg,VDP_HIHDR_V_CFG_S *pstHiHdrCfg)
{
#ifdef VDP_DEFINE_HI_HDR
    pstHiHdrCfg->vhdr_gamut_bind                = pstPqHdrCfg->bGMapPosSel;
    pstHiHdrCfg->hihdr_y2r_en                   = pstPqHdrCfg->bY2REn;
    pstHiHdrCfg->hihdr_v0_cl_en                 = pstPqHdrCfg->bV0CLEn;
    pstHiHdrCfg->hihdr_v1_cl_en                 = pstPqHdrCfg->bV1CLEn;
    pstHiHdrCfg->hihdr_v0_y2r_en                = pstPqHdrCfg->bV0Y2REn;
    pstHiHdrCfg->hihdr_v1_y2r_en                = pstPqHdrCfg->bV1Y2REn;
    pstHiHdrCfg->vhdr_cadj_en                   = pstPqHdrCfg->bChromaAdjEn;
    pstHiHdrCfg->vhdr_degmm_en                  = pstPqHdrCfg->bDegammaEn;
    pstHiHdrCfg->vhdr_gamut_en                  = pstPqHdrCfg->bGMapEn;
    pstHiHdrCfg->vhdr_tmap_en                   = pstPqHdrCfg->bTMapEn;
    pstHiHdrCfg->vhdr_gmm_en                    = pstPqHdrCfg->bGammaEn;
    pstHiHdrCfg->vhdr_dither_en                 = pstPqHdrCfg->bDitherEn;
    pstHiHdrCfg->vhdr_dither_domain_mode        = pstPqHdrCfg->bDitherMode;
    pstHiHdrCfg->vhdr_r2y_en                    = pstPqHdrCfg->bR2YEn;
    pstHiHdrCfg->hihdr_v0_vhdr_en               = pstPqHdrCfg->bV0HdrEn;
    pstHiHdrCfg->hihdr_v1_vhdr_en               = pstPqHdrCfg->bV1HdrEn;


    /********** YUV2RGB **********/

    if (u32LayerId == VDP_LAYER_VID0)
    {
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00 = pstPqHdrCfg->stY2R.as16M33Y2R[0][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01 = pstPqHdrCfg->stY2R.as16M33Y2R[0][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02 = pstPqHdrCfg->stY2R.as16M33Y2R[0][2]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03 = pstPqHdrCfg->stY2R.as16M33Y2R[1][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04 = pstPqHdrCfg->stY2R.as16M33Y2R[1][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05 = pstPqHdrCfg->stY2R.as16M33Y2R[1][2]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06 = pstPqHdrCfg->stY2R.as16M33Y2R[2][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07 = pstPqHdrCfg->stY2R.as16M33Y2R[2][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08 = pstPqHdrCfg->stY2R.as16M33Y2R[2][2]  ;

        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00 = pstPqHdrCfg->stY2R.as16DcInY2R[0];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01 = pstPqHdrCfg->stY2R.as16DcInY2R[1];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02 = pstPqHdrCfg->stY2R.as16DcInY2R[2];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00 = pstPqHdrCfg->stY2R.as16DcOutY2R[0];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01 = pstPqHdrCfg->stY2R.as16DcOutY2R[1];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02 = pstPqHdrCfg->stY2R.as16DcOutY2R[2];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = pstPqHdrCfg->stY2R.u16ScaleY2R;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = pstPqHdrCfg->stY2R.u16ClipMinY2R;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = pstPqHdrCfg->stY2R.u16ClipMaxY2R;
    }

    if (u32LayerId == VDP_LAYER_VID1)
    {
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10 = pstPqHdrCfg->stY2R.as16M33Y2R[0][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11 = pstPqHdrCfg->stY2R.as16M33Y2R[0][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12 = pstPqHdrCfg->stY2R.as16M33Y2R[0][2]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13 = pstPqHdrCfg->stY2R.as16M33Y2R[1][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14 = pstPqHdrCfg->stY2R.as16M33Y2R[1][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15 = pstPqHdrCfg->stY2R.as16M33Y2R[1][2]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16 = pstPqHdrCfg->stY2R.as16M33Y2R[2][0]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17 = pstPqHdrCfg->stY2R.as16M33Y2R[2][1]  ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18 = pstPqHdrCfg->stY2R.as16M33Y2R[2][2]  ;

        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10 = pstPqHdrCfg->stY2R.as16DcInY2R[0];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11 = pstPqHdrCfg->stY2R.as16DcInY2R[1];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12 = pstPqHdrCfg->stY2R.as16DcInY2R[2];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10 = pstPqHdrCfg->stY2R.as16DcOutY2R[0];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11 = pstPqHdrCfg->stY2R.as16DcOutY2R[1];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12 = pstPqHdrCfg->stY2R.as16DcOutY2R[2];
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = pstPqHdrCfg->stY2R.u16ScaleY2R;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = pstPqHdrCfg->stY2R.u16ClipMinY2R;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = pstPqHdrCfg->stY2R.u16ClipMaxY2R;
    }

    /********** DeGamma ***********/
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = pstPqHdrCfg->stDeGmm.au32Step[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = pstPqHdrCfg->stDeGmm.au32Step[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = pstPqHdrCfg->stDeGmm.au32Step[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = pstPqHdrCfg->stDeGmm.au32Step[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = pstPqHdrCfg->stDeGmm.au32Step[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = pstPqHdrCfg->stDeGmm.au32Step[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = pstPqHdrCfg->stDeGmm.au32Step[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = pstPqHdrCfg->stDeGmm.au32Step[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = pstPqHdrCfg->stDeGmm.au32Pos[0] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = pstPqHdrCfg->stDeGmm.au32Pos[1] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = pstPqHdrCfg->stDeGmm.au32Pos[2] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = pstPqHdrCfg->stDeGmm.au32Pos[3] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = pstPqHdrCfg->stDeGmm.au32Pos[4] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = pstPqHdrCfg->stDeGmm.au32Pos[5] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = pstPqHdrCfg->stDeGmm.au32Pos[6] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = pstPqHdrCfg->stDeGmm.au32Pos[7] ;
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = pstPqHdrCfg->stDeGmm.au32Num[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = pstPqHdrCfg->stDeGmm.au32Num[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = pstPqHdrCfg->stDeGmm.au32Num[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = pstPqHdrCfg->stDeGmm.au32Num[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = pstPqHdrCfg->stDeGmm.au32Num[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = pstPqHdrCfg->stDeGmm.au32Num[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = pstPqHdrCfg->stDeGmm.au32Num[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = pstPqHdrCfg->stDeGmm.au32Num[7];

    /********** ToneMapping **********/
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = pstPqHdrCfg->stTMAP.au16M3LumaCal[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = pstPqHdrCfg->stTMAP.au16M3LumaCal[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = pstPqHdrCfg->stTMAP.au16M3LumaCal[2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = pstPqHdrCfg->stTMAP.u16ScaleLumaCal;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = pstPqHdrCfg->stTMAP.u16ScaleCoefTM;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = pstPqHdrCfg->stTMAP.u32ClipMinTM;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = pstPqHdrCfg->stTMAP.u32ClipMaxTM;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = pstPqHdrCfg->stTMAP.as32TMOff[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = pstPqHdrCfg->stTMAP.as32TMOff[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = pstPqHdrCfg->stTMAP.as32TMOff[2];

    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step            = pstPqHdrCfg->stTMAP.au32StepTM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step            = pstPqHdrCfg->stTMAP.au32StepTM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step            = pstPqHdrCfg->stTMAP.au32StepTM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step            = pstPqHdrCfg->stTMAP.au32StepTM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step            = pstPqHdrCfg->stTMAP.au32StepTM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step            = pstPqHdrCfg->stTMAP.au32StepTM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step            = pstPqHdrCfg->stTMAP.au32StepTM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step            = pstPqHdrCfg->stTMAP.au32StepTM[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos             = pstPqHdrCfg->stTMAP.au32PosTM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos             = pstPqHdrCfg->stTMAP.au32PosTM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos             = pstPqHdrCfg->stTMAP.au32PosTM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos             = pstPqHdrCfg->stTMAP.au32PosTM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos             = pstPqHdrCfg->stTMAP.au32PosTM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos             = pstPqHdrCfg->stTMAP.au32PosTM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos             = pstPqHdrCfg->stTMAP.au32PosTM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos             = pstPqHdrCfg->stTMAP.au32PosTM[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num             = pstPqHdrCfg->stTMAP.au32NumTM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num             = pstPqHdrCfg->stTMAP.au32NumTM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num             = pstPqHdrCfg->stTMAP.au32NumTM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num             = pstPqHdrCfg->stTMAP.au32NumTM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num             = pstPqHdrCfg->stTMAP.au32NumTM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num             = pstPqHdrCfg->stTMAP.au32NumTM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num             = pstPqHdrCfg->stTMAP.au32NumTM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num             = pstPqHdrCfg->stTMAP.au32NumTM[7];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = pstPqHdrCfg->stTMAP.u32ScaleMixAlpha;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = pstPqHdrCfg->stTMAP.u32MixAlpha     ;

    /************ GMapping ***********/
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = pstPqHdrCfg->stGMAP.as16M33GMAP[0][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = pstPqHdrCfg->stGMAP.as16M33GMAP[0][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = pstPqHdrCfg->stGMAP.as16M33GMAP[0][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = pstPqHdrCfg->stGMAP.as16M33GMAP[1][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = pstPqHdrCfg->stGMAP.as16M33GMAP[1][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = pstPqHdrCfg->stGMAP.as16M33GMAP[1][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = pstPqHdrCfg->stGMAP.as16M33GMAP[2][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = pstPqHdrCfg->stGMAP.as16M33GMAP[2][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = pstPqHdrCfg->stGMAP.as16M33GMAP[2][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = pstPqHdrCfg->stGMAP.as32DcInGMAP[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = pstPqHdrCfg->stGMAP.as32DcInGMAP[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = pstPqHdrCfg->stGMAP.as32DcInGMAP[2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = pstPqHdrCfg->stGMAP.as32DcOutGMAP[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = pstPqHdrCfg->stGMAP.as32DcOutGMAP[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = pstPqHdrCfg->stGMAP.as32DcOutGMAP[2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = pstPqHdrCfg->stGMAP.u16ScaleGMAP;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = pstPqHdrCfg->stGMAP.u32ClipMinGMAP;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = pstPqHdrCfg->stGMAP.u32ClipMaxGMAP;

    /************* Gamma ***********************/
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step  = pstPqHdrCfg->stGmm.au32Step[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step  = pstPqHdrCfg->stGmm.au32Step[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step  = pstPqHdrCfg->stGmm.au32Step[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step  = pstPqHdrCfg->stGmm.au32Step[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step  = pstPqHdrCfg->stGmm.au32Step[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step  = pstPqHdrCfg->stGmm.au32Step[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step  = pstPqHdrCfg->stGmm.au32Step[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step  = pstPqHdrCfg->stGmm.au32Step[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos   = pstPqHdrCfg->stGmm.au32Pos[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos   = pstPqHdrCfg->stGmm.au32Pos[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos   = pstPqHdrCfg->stGmm.au32Pos[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos   = pstPqHdrCfg->stGmm.au32Pos[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos   = pstPqHdrCfg->stGmm.au32Pos[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos   = pstPqHdrCfg->stGmm.au32Pos[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos   = pstPqHdrCfg->stGmm.au32Pos[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos   = pstPqHdrCfg->stGmm.au32Pos[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num   = pstPqHdrCfg->stGmm.au32Num[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num   = pstPqHdrCfg->stGmm.au32Num[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num   = pstPqHdrCfg->stGmm.au32Num[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num   = pstPqHdrCfg->stGmm.au32Num[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num   = pstPqHdrCfg->stGmm.au32Num[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num   = pstPqHdrCfg->stGmm.au32Num[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num   = pstPqHdrCfg->stGmm.au32Num[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num   = pstPqHdrCfg->stGmm.au32Num[7];


    /************** RGB2YUV ********************/
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = pstPqHdrCfg->stR2Y.as16M33R2Y[0][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = pstPqHdrCfg->stR2Y.as16M33R2Y[0][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = pstPqHdrCfg->stR2Y.as16M33R2Y[0][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = pstPqHdrCfg->stR2Y.as16M33R2Y[1][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = pstPqHdrCfg->stR2Y.as16M33R2Y[1][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = pstPqHdrCfg->stR2Y.as16M33R2Y[1][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = pstPqHdrCfg->stR2Y.as16M33R2Y[2][0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = pstPqHdrCfg->stR2Y.as16M33R2Y[2][1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = pstPqHdrCfg->stR2Y.as16M33R2Y[2][2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = pstPqHdrCfg->stR2Y.u16ScaleR2Y;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = pstPqHdrCfg->stR2Y.as16DcInR2Y[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = pstPqHdrCfg->stR2Y.as16DcInR2Y[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = pstPqHdrCfg->stR2Y.as16DcInR2Y[2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = pstPqHdrCfg->stR2Y.as16DcOutR2Y[0];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = pstPqHdrCfg->stR2Y.as16DcOutR2Y[1];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = pstPqHdrCfg->stR2Y.as16DcOutR2Y[2];
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = pstPqHdrCfg->stR2Y.u16ClipMinR2Y_Y ;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = pstPqHdrCfg->stR2Y.u16ClipMaxR2Y_Y ;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = pstPqHdrCfg->stR2Y.u16ClipMinR2Y_UV;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = pstPqHdrCfg->stR2Y.u16ClipMaxR2Y_UV;
    pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p   = pstPqHdrCfg->stCadj.u16Scale2P;

    /************** SMAP ********************/
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step    = pstPqHdrCfg->stSMAP.au32StepSM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step    = pstPqHdrCfg->stSMAP.au32StepSM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step    = pstPqHdrCfg->stSMAP.au32StepSM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step    = pstPqHdrCfg->stSMAP.au32StepSM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step    = pstPqHdrCfg->stSMAP.au32StepSM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step    = pstPqHdrCfg->stSMAP.au32StepSM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step    = pstPqHdrCfg->stSMAP.au32StepSM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step    = pstPqHdrCfg->stSMAP.au32StepSM[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos     = pstPqHdrCfg->stSMAP.au32PosSM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos     = pstPqHdrCfg->stSMAP.au32PosSM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos     = pstPqHdrCfg->stSMAP.au32PosSM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos     = pstPqHdrCfg->stSMAP.au32PosSM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos     = pstPqHdrCfg->stSMAP.au32PosSM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos     = pstPqHdrCfg->stSMAP.au32PosSM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos     = pstPqHdrCfg->stSMAP.au32PosSM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos     = pstPqHdrCfg->stSMAP.au32PosSM[7];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num     = pstPqHdrCfg->stSMAP.au32NumSM[0];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num     = pstPqHdrCfg->stSMAP.au32NumSM[1];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num     = pstPqHdrCfg->stSMAP.au32NumSM[2];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num     = pstPqHdrCfg->stSMAP.au32NumSM[3];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num     = pstPqHdrCfg->stSMAP.au32NumSM[4];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num     = pstPqHdrCfg->stSMAP.au32NumSM[5];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num     = pstPqHdrCfg->stSMAP.au32NumSM[6];
    pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num     = pstPqHdrCfg->stSMAP.au32NumSM[7];

#endif
    return;

}

HI_VOID VDP_DRV_GetHiHdrCbb(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn,HIHDR_SCENE_MODE_E enSceneMode,VDP_HIHDR_V_CFG_S *pstHiHdrCfg)
{
#ifdef VDP_DEFINE_HI_HDR
    if(enSceneMode == HIHDR_BT2020_IN_2020_OUT)//98mv200t test ok!
    {
       // enable signal
       pstHiHdrCfg->hihdr_y2r_en   = 1 ;
       pstHiHdrCfg->vhdr_en        = 0 ;
       pstHiHdrCfg->vhdr_degmm_en  = 0 ;
       pstHiHdrCfg->vhdr_r2y_en    = 0 ;
       pstHiHdrCfg->vhdr_tmap_en   = 0 ;
       pstHiHdrCfg->vhdr_gmm_en    = 0 ;
       pstHiHdrCfg->vhdr_dither_en = 0 ;
       pstHiHdrCfg->vhdr_gamut_en  = 0 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_SDR_OUT) // test ok!
    {
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HDR10)
            {
            pstHiHdrCfg->hihdr_v0_vhdr_en  = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en   = 1 ; //use BT2020
            }
            else
            {
            pstHiHdrCfg->hihdr_v0_vhdr_en  = 0 ;
            pstHiHdrCfg->hihdr_v0_y2r_en   = 0 ; //use BT2020
            }
            //YUV2RGB
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01       = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02       = 6896;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04       = -770;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05       = -2672;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07       = 8799;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08       = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00        = -64;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01        = -512;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02        = -512;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p   = 12;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min  = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max  = 770;
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HDR10)
            {
            pstHiHdrCfg->hihdr_v1_vhdr_en  = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en   = 1 ;
            }
            else
            {
            pstHiHdrCfg->hihdr_v1_vhdr_en  = 0 ;
            pstHiHdrCfg->hihdr_v1_y2r_en   = 0 ;
            }
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11       = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12       = 6896;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14       = -770;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15       = -2672;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16       = 4783;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17       = 8799;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18       = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10        = -64;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11        = -512;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12        = -512;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12        = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p   = 12;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min  = 0;
            pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max  = 770;
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076    ;        //= 8608    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777    ;        //= 22217   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243     ;        //= 1943    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 64;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step   = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step   = 1    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step   = 2    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step   = 3    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step   = 4    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step   = 5    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step   = 4    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step   = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos    = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos    = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos    = 16   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos    = 96   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos    = 640  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos    = 928  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos    = 1023 ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos    = 1023 ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num    = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num    = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num    = 4    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num    = 14   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num    = 48   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num    = 57   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num    = 63   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num    = 63   ;

        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128     ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151 ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63      ;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step     = 1       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step     = 3       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step     = 5       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step     = 6       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step     = 7       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step     = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step     = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step     = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos      = 4       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos      = 28      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos      = 92      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos      = 220     ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos      = 476     ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos      = 4060    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos      = 18396   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos      = 65535   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num      = 2       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num      = 5       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num      = 7       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num      = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num      = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num      = 18      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num      = 25      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num      = 31      ;

        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step     = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step     = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step     = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step     = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step     = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step     = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step     = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step     = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos      = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos      = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos      = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos      = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos      = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos      = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos      = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos      = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num      = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num      = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num      = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num      = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num      = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num      = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num      = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num      = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = 27209   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = -9632   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = -1194   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = -2045   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = 18565   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = -138    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = -297    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = -1648   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = 18330   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = 2097151 ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = 2984    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = 10034   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = 1013    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = -1643   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = -5531   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = -6518   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = -659    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = 940     ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_HDR10_OUT) //98mv200t test ok!
    {
        // enable signal
        pstHiHdrCfg->hihdr_y2r_en     = 0 ;
        pstHiHdrCfg->vhdr_degmm_en    = 0 ;
        pstHiHdrCfg->vhdr_gamut_en    = 0 ;
        pstHiHdrCfg->vhdr_tmap_en     = 0 ;
        pstHiHdrCfg->vhdr_gmm_en      = 0 ;
        pstHiHdrCfg->vhdr_dither_en   = 0 ;
        pstHiHdrCfg->vhdr_dither_en   = 0 ;
        pstHiHdrCfg->vhdr_r2y_en      = 0 ;

        pstHiHdrCfg->hihdr_v0_y2r_en  = 0 ;
        pstHiHdrCfg->hihdr_v1_y2r_en  = 0 ;
        pstHiHdrCfg->hihdr_v0_vhdr_en = 0 ;
        pstHiHdrCfg->hihdr_v1_vhdr_en = 0 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_HLG_OUT) //test ok!
    {
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 0 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        pstHiHdrCfg->hihdr_v0_y2r_en= 1;
        pstHiHdrCfg->hihdr_v1_y2r_en= 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HDR10)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en  = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en  = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HDR10)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en  = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en  = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076    ;        //= 8608    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777    ;        //= 22217   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243     ;        //= 1943    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;

        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128     ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151 ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63      ;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;

        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128     ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144    ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384   ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360  ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151 ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4       ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52      ;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63      ;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = 14;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = 2097151 ;

        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = 3685    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = 9512    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = 832     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = -2004   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = -5171   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = -6598   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = -577    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = 940     ;
    }
    else if (enSceneMode == HIHDR_SDR_IN_HDR10_OUT || enSceneMode == HIHDR_SDR_IN_HLG_OUT)
    {
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        pstHiHdrCfg->hihdr_v0_y2r_en= 1;
        pstHiHdrCfg->hihdr_v1_y2r_en= 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
             pstHiHdrCfg->hihdr_v0_vhdr_en  = 1 ;
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en  = 1 ;
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076    ;        //= 8608    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777    ;        //= 22217   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243     ;        //= 1943    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 15       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;

        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;

        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = 10279;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = 5396;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = 710;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = 1134;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = 15064;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = 187;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = 268;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = 1442;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = 14673;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = 14;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = 2097151 ;

        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 7365;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -876;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2189;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8678;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 7365;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -876;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2189;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8678;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = 3685    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = 9512    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = 832     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = -2004   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = -5171   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = -6598   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = -577    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = 940     ;
    }
    else if (enSceneMode == HIHDR_SLF_IN_SDR_OUT) // test ok!
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 1;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SLF)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SLF)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;

        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 64;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;

        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;
        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = 27209;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = -9632;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = -1194;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = -2045;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = 18565;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = -138;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = -297;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = -1648;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = 18330;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = 0    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = 2097151 ;

        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12   ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12   ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023 ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023 ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = 2984;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = 10034;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = 1013;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = -1643;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = -5531;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = 7175;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = 7175;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = -6518;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = -659;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = 940     ;
    }
    else if (enSceneMode == HIHDR_SLF_IN_HDR10_OUT) //98mv200t test ok!
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 0 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SLF)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SLF)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;

        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;

        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21    = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2      = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale     = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max  = 2097151 ;

        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00     = 3685    ; //BT2020
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01     = 9512    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02     = 832     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10     = -2004   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11     = -5171   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20     = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21     = -6598   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22     = -577    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p    = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0       = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2       = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max = 940     ;
    }
    else if (enSceneMode == HIHDR_HLG_IN_SDR_OUT) //test ok
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HLG)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HLG)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076    ;        //= 8608    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777    ;        //= 22217   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243     ;        //= 1943    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 15       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 514     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 514     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 514     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;
        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;
        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = 27209;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = -9632;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = -1194;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = -2045;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = 18565;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = -138;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = -297;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = -1648;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 18330;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;

         /************** YUV2RGB ********************/
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
         pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;

        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00        = 2984;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01        = 10034;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02        = 1013;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10        = -1643;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11        = -5531;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12        = 7175;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20        = 7175;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21        = -6518;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22        = -659;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p       = 14;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0          = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1          = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2          = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0          = 64;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1          = 512;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2          = 512;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min    = 64;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min    = 64;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max    = 960;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max    = 940;
    }
    else if (enSceneMode == HIHDR_HLG_IN_HDR10_OUT) //test ok!
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 0 ;
        pstHiHdrCfg->vhdr_tmap_en   = 1 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HLG)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_HLG)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 15      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;
        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;
        /************* Gamma ***********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = 0;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 0     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = 0     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = 0     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 0     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;
        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;
        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00        = 3685    ; //BT2020
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01        = 9512    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02        = 832     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10        = -2004   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11        = -5171   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21        = -6598   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22        = -577    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0          = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max    = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max    = 940     ;
    }
    else if (enSceneMode == HIHDR_BT2020_IN_709_OUT) //test ok!
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 0 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;
        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;
        /************* Gamma ******************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = 27209;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = -9632;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = -1194;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = -2045;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = 18565;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = -138;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = -297;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = -1648;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 18330;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14  ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;
        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;
        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00        = 2984    ; //BT709
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01        = 10034   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02        = 1013    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10        = -1643   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11        = -5531   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21        = -6518   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22        = -659    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0          = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max    = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max    = 940     ;
    }
    else if (enSceneMode == HIHDR_BT2020_IN_RGB_709_OUT) //98mv200t test ok!
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 0 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 0 ;

        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
            }
        }

        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;
        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;
        /************* Gamma ******************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = 27209;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = -9632;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = -1194;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = -2045;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = 18565;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = -138;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = -297;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = -1648;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 18330;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14  ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;
        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 6896;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = -770;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = -2672;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 8799;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;
        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00        = 2984    ; //BT709
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01        = 10034   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02        = 1013    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10        = -1643   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11        = -5531   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21        = -6518   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22        = -659    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0          = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max    = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max    = 940     ;

    }
    else if (enSceneMode == HIHDR_709_IN_BT2020_OUT) //not use
    {
        VDP_PRINT("NOUSE SCENEMODE!!!\n");
    }
    else  if (enSceneMode == HIHDR_XVYCC)
    {
        VDP_PRINT("NOUSE SCENEMODE!!!\n");
    }
    else  if (enSceneMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)//test ok
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 1 ;
        pstHiHdrCfg->vhdr_en        = 1 ;
        pstHiHdrCfg->vhdr_degmm_en  = 1 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 0 ;
        pstHiHdrCfg->vhdr_gmm_en    = 1 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 1 ;

        pstHiHdrCfg->vhdr_cadj_en   = 0;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 1 ;
                pstHiHdrCfg->hihdr_v0_cl_en       = 1;
            }
            else
            {
                pstHiHdrCfg->hihdr_v0_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v0_y2r_en      = 0 ;
                pstHiHdrCfg->hihdr_v0_cl_en       = 0;
            }
        }
        else
        {
            if (pstInfoIn->stXdpSrcCfg.enXdpViDeoFrameType == XDP_VIDEO_FRAME_TYPE_SDR)
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 1 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 1 ;
                pstHiHdrCfg->hihdr_v1_cl_en       = 1;
            }
            else
            {
                pstHiHdrCfg->hihdr_v1_vhdr_en     = 0 ;
                pstHiHdrCfg->hihdr_v1_y2r_en      = 0 ;
                pstHiHdrCfg->hihdr_v1_cl_en       = 0;
            }
        }
        // cfg
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef0    = 1076;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef1    = 2777;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_coef2    = 243;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_luma_scale    = 12      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_coef_scale    = 8       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_min  = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_clip_max  = (1 << 21) - 1   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc0       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc1       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_out_dc2       = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_cadj_scale2p       = 8       ;

        /************** DeGmm ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_step = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_step = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_step = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_step = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_step = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_step = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_pos  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_pos  = 16;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_pos  = 96;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_pos  = 640;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_pos  = 928;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_pos  = 1023;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x1_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x2_num  = 0;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x3_num  = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x4_num  = 14;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x5_num  = 48;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x6_num  = 57;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x7_num  = 63;
        pstHiHdrCfg->stHiHdrPqCfg.v_degmm_x8_num  = 63;
        /************** Tomap ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_step  = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_step  = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_step  = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_pos   = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_pos   = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_pos   = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_pos   = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_pos   = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_pos   = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_pos   = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_pos   = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x1_num   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x2_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x3_num   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x4_num   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x5_num   = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x6_num   = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x7_num   = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_tmap_x8_num   = 63;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_scale_mix_alpha = 8;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_tmap_mix_alpha       = 0;

        /************** SMAP ********************/
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_step  = 1;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_step  = 3;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_step  = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_step  = 6;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_step  = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_step  = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_step  = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_step  = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_pos   = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_pos   = 28;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_pos   = 92;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_pos   = 220;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_pos   = 476;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_pos   = 4060;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_pos   = 18396;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_pos   = 65535;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x1_num   = 2;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x2_num   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x3_num   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x4_num   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x5_num   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x6_num   = 18;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x7_num   = 25;
        pstHiHdrCfg->stHiHdrPqCfg.v_smap_x8_num   = 31;
        /************* Gamma ******************/
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_step   = 5;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_step   = 7;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_step   = 9;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_step   = 10;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_step   = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_step   = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_step   = 15;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_step   = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_pos    = 128;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_pos    = 1024;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_pos    = 2048;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_pos    = 6144;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_pos    = 16384;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_pos    = 131072;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_pos    = 655360;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_pos    = 2097151;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x1_num    = 4;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x2_num    = 11;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x3_num    = 13;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x4_num    = 17;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x5_num    = 22;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x6_num    = 36;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x7_num    = 52;
        pstHiHdrCfg->stHiHdrPqCfg.v_gmm_x8_num    = 63;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = -14207;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = -352;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = 30941;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = 27382;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = -1761;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = -9238;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = -2431;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = 18475;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 342;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 0   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;//0xFFFF0  10448575 ;5 ;
        /************** YUV2RGB ********************/
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef00      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef01      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef02      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef03      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef04      = 9074;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef05      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef06      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef07      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef08      = 4647;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef10      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef11      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef12      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef13      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef14      = 9074;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef15      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef16      = 4783;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef17      = 0;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_coef18      = 4647;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_scale2p  = 12      ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc00       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc01       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc02       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc00       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc01       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc02       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc10       = -64     ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc11       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_idc12       = -512    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc10       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc11       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_odc12       = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v0_clip_max = 1023    ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_min = 0       ;
        pstHiHdrCfg->stHiHdrY2RCfg.hihdr_y2r_v1_clip_max = 1023    ;
        /************** RGB2YUV ********************/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef00        = 2984    ; //BT709709
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef01        = 10034   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef02        = 1013    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef10        = -1643   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef11        = -5531   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef12        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef20        = 7175    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef21        = -6518   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_coef22        = -659    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_scale2p       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc0          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc1          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_idc2          = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc0          = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc1          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_odc2          = 512     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_min    = 64      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_c_max    = 960     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_r2y_clip_y_max    = 940     ;
    }
    else  if (enSceneMode == HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT)
    {
        // ctrl signal
        pstHiHdrCfg->hihdr_y2r_en   = 0 ;
        pstHiHdrCfg->vhdr_en        = 0 ;
        pstHiHdrCfg->vhdr_degmm_en  = 0 ;
        pstHiHdrCfg->vhdr_gamut_en  = 1 ;
        pstHiHdrCfg->vhdr_tmap_en   = 0 ;
        pstHiHdrCfg->vhdr_gmm_en    = 0 ;
        pstHiHdrCfg->vhdr_dither_en = 1 ;
        pstHiHdrCfg->vhdr_r2y_en    = 0 ;
        pstHiHdrCfg->vhdr_cadj_en   = 0;

        pstHiHdrCfg->hihdr_v0_vhdr_en = 0 ;
        pstHiHdrCfg->hihdr_v1_vhdr_en = 0 ;
        pstHiHdrCfg->hihdr_v0_cl_en   = 0;
        pstHiHdrCfg->hihdr_v1_cl_en   = 0;
        pstHiHdrCfg->hihdr_v0_y2r_en  = 0;
        pstHiHdrCfg->hihdr_v1_y2r_en  = 0;

        /************ GMapping ***********/
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef00      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef01      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef02      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef10      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef11      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef12      = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef20      = -14207  ; //BT2020 to BT709 B2020 to BT709
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef21      = -352    ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_coef22      = 30941   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc0        = 27382   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc1        = -1761   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_idc2        = -9238   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc0        = -2431   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc1        = 18475   ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_odc2        = 342     ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_scale       = 14      ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_min    = 0       ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_gamut_clip_max    = 2097151 ;//0xFFFF0  1048575 0448575 ;5 ;
    }
#endif

}

HI_S32 XDP_DRV_GetHiHdrCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, HI_PQ_HDR_CFG *pstPqHdrCfg,
                            HIHDR_SCENE_MODE_E enSceneMode, VDP_HIHDR_V_CFG_S *pstHiHdrCfg)
{
#ifdef VDP_DEFINE_HI_HDR
    VDP_CLR_SPACE_E   enOutClr    = pstInfoIn->stXdpDispCfg.enOutClrSpace;
    if (enSceneMode >= HIHDR_SCENE_BUTT)
    {
        VDP_PRINT("enSceneMode arange Error !!! \n");
        return HI_FAILURE;
    }
#if CBB_CFG_FROM_PQ
    VDP_DRV_GetHiHdrAjust(u32LayerId, pstPqHdrCfg, pstHiHdrCfg);
#else
    VDP_DRV_GetHiHdrCbb(u32LayerId, pstInfoIn, enSceneMode, pstHiHdrCfg);
#endif

    if (enSceneMode == HIHDR_BT2020_IN_2020_OUT) //98mv310 test ok!
    {
        //VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_dither_round         = 0 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;
        /*if (u32LayerId == VDP_LAYER_VID0)
                {
                   pstHiHdrCfg->hihdr_v0_vhdr_en           = 0 ;
                   pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
                }
                else
                {
                   pstHiHdrCfg->hihdr_v1_vhdr_en           = 0 ;
                   pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
                }*/
        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_SDR_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_SDR_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_dither_round         = 0 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }
        if (enOutClr == VDP_CLR_SPACE_RGB_601
            || enOutClr == VDP_CLR_SPACE_RGB_709
            || enOutClr == VDP_CLR_SPACE_RGB_2020
            || enOutClr == VDP_CLR_SPACE_RGB_601_L
            || enOutClr == VDP_CLR_SPACE_RGB_709_L
            || enOutClr == VDP_CLR_SPACE_RGB_2020_L
           )
        {
            pstHiHdrCfg->vhdr_r2y_en                = 0 ;
        }
        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_HDR10_OUT) //98mv200t test ok!
    {
        //typ mode
        //VDP_PRINT("VdmSceneMode == HIHDR_HDR10_IN_HDR10_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 0 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 0 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 0 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 0 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 0 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HDR10_IN_HLG_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == VDM_HDR10_IN_HLG_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_SDR_IN_HDR10_OUT || enSceneMode == HIHDR_SDR_IN_HLG_OUT)
    {
        //VDP_PRINT("HIHDR_SDR_IN_HDR10_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_SLF_IN_SDR_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == HIHDR_SLF_IN_SDR_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_SLF_IN_HDR10_OUT) // test ok!
    {
        //VDP_PRINT("VdmSceneMode == HIHDR_SLF_IN_HDR10_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HLG_IN_SDR_OUT)
    {
        //VDP_PRINT("VdmSceneMode == HIHDR_HLG_IN_SDR_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_HLG_IN_HDR10_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == VDM_BBC_IN_HDR10_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_BT2020_IN_709_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == HIHDR_BT2020_IN_709_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_BT2020_IN_RGB_709_OUT) //98mv200t test ok!
    {
        //VDP_PRINT("VdmSceneMode == HIHDR_BT2020_IN_RGB_709_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 0 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else if (enSceneMode == HIHDR_709_IN_BT2020_OUT) //not use
    {
        //VDP_PRINT("HIHDR_709_IN_BT2020_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;

    }
    else  if (enSceneMode == HIHDR_XVYCC)
    {
        VDP_PRINT("NOUSE SCENEMODE!!!\n");
    }
    else  if (enSceneMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        //VDP_PRINT("HIHDR_SDR_BT2020CL_IN_BT709_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 1 ;

        if (u32LayerId == VDP_LAYER_VID0)
        {
            pstHiHdrCfg->hihdr_v0_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v0_y2r_en            = 1 ; //use BT2020
        }
        else
        {
            pstHiHdrCfg->hihdr_v1_vhdr_en           = 1 ;
            pstHiHdrCfg->hihdr_v1_y2r_en            = 1 ; //use BT2020
        }

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
    else  if (enSceneMode == HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT)
    {
        //VDP_PRINT("HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT\n");
        pstHiHdrCfg->vhdr_gamut_bind           = 1 ;// 0:csc->tmap, 1:tmap->csc
        pstHiHdrCfg->vhdr_gamut_en             = 1 ; //use BT2020
        pstHiHdrCfg->vhdr_dither_round         = 1 ;
        pstHiHdrCfg->vhdr_dither_domain_mode   = 0 ;
        pstHiHdrCfg->vhdr_dither_tap_mode      = 0 ;
        pstHiHdrCfg->vhdr_dither_round_unlim   = 0 ;
        pstHiHdrCfg->vhdr_en                   = 0 ;
        pstHiHdrCfg->vhdr_cadj_en              = 0 ;
        pstHiHdrCfg->hihdr_v0_vhdr_en          = 0 ;
        pstHiHdrCfg->hihdr_v1_vhdr_en          = 0 ;
        pstHiHdrCfg->hihdr_v0_cl_en = 0;
        pstHiHdrCfg->hihdr_v1_cl_en = 0;
        pstHiHdrCfg->hihdr_v0_y2r_en = 0;
        pstHiHdrCfg->hihdr_v1_y2r_en = 0;

        //DITHER
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_max      = 65535 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_thr_min      = 0 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y0       = 2147483647;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w0       = 2147483647 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_y1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_u1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_v1       = 2140000000 ;
        pstHiHdrCfg->stHiHdrPqCfg.vhdr_dither_sed_w1       = 2140000000 ;
    }
#endif
    return HI_SUCCESS;
}

HI_BOOL  VDP_DRV_SetVDMBypassProcess(HI_U32 u32LayerId, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode)
{
#ifdef VDP_DEFINE_HI_HDR
    if (enSceneMode == HIHDR_BYPASS_MODE)
    {
        if (VDP_LAYER_VID0 == u32LayerId)
        {
            VDP_HIHDR_V_SetHihdrV0VhdrEn       (0);
        }
        else if (VDP_LAYER_VID1 == u32LayerId)
        {
            VDP_HIHDR_V_SetHihdrV1VhdrEn       (0);
        }
        return HI_FALSE;
    }

#endif
    return HI_TRUE;
}

HI_S32 VDP_DRV_SetVDMCoef(HI_U32 u32LayerId, HI_PQ_HDR_CFG  *pstPqHdrCfg, HIHDR_SCENE_MODE_E enSceneMode)
{
#ifdef VDP_DEFINE_HI_HDR
    if (enSceneMode != HIHDR_HDR10_IN_HDR10_OUT
        && enSceneMode != HIHDR_SDR_BT2020CL_IN_BT2020CL_OUT
        && enSceneMode != HIHDR_BYPASS_MODE
       )
    {
        VDP_DRV_SetHdrVCoef(enSceneMode, pstPqHdrCfg);
    }
#endif
    return HI_SUCCESS;
}

HIHDR_SCENE_MODE_E gSceneMode = HIHDR_BYPASS_MODE ;
HI_S32 XDP_DRV_SetVDMCfg(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn, HI_PQ_HDR_CFG  *pstPqHdrCfg,
                        HIHDR_SCENE_MODE_E enSceneMode, VDP_HIHDR_V_CFG_S *pstHiHdrCfg )
{
#ifdef VDP_DEFINE_HI_HDR
    //HI_BOOL bPQHDRCoefRefresh = pstInfoIn->stXdpLayerExtern.bPQHDRCoefRefresh;

    HI_BOOL bPQHDRCoefRefresh = HI_TRUE;
    if (enSceneMode >= HIHDR_SCENE_BUTT)
    {
        VDP_PRINT("enSceneMode arange Error !!! \n");
        return HI_FAILURE;
    }

    if (HI_FALSE == VDP_DRV_SetVDMBypassProcess(u32LayerId, pstPqHdrCfg, enSceneMode))
    {
        return HI_SUCCESS;
    }

    if ((gSceneMode != enSceneMode) || bPQHDRCoefRefresh)
    {
        gSceneMode = enSceneMode;
        VDP_DRV_SetVDMCoef(u32LayerId, pstPqHdrCfg, enSceneMode);
    }
    VDP_PARA_SetParaUpVhdChn(VDP_COEF_BUF_HIHDR_V_D);
    VDP_PARA_SetParaUpVhdChn(VDP_COEF_BUF_HIHDR_V_S);

    VDP_DRV_SetHiHdrCfg(u32LayerId, pstHiHdrCfg);
#endif
    return HI_SUCCESS;
}


HI_S32 XDP_DRV_SetVP0Reso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoIn)
{
    VDP_VP_SetLayerEnable          (VDP_LAYER_VP0, HI_TRUE);
    VDP_VP_SetVideoPos             (VDP_LAYER_VP0, pstInfoIn->stXdpDispCfg.stFmtReso );
    VDP_VP_SetDispPos              (VDP_LAYER_VP0, pstInfoIn->stXdpDispCfg.stFmtReso );
    VDP_VP_SetInReso               (VDP_LAYER_VP0, pstInfoIn->stXdpDispCfg.stFmtReso );
    VDP_VP_SetLayerGalpha          (VDP_LAYER_VP0, pstInfoIn->stXdpSysCfg.u32AllAlpha);

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetVidCBM(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstOutInfo)
{
    HI_U32  u32LayerZorder = pstOutInfo->stXdpSysCfg.u32LayerZorder;
    VDP_CBM_Clear_MixvPrio(u32LayerId);

    VDP_CBM_SetMixerPrio           (VDP_CBM_MIXV0, u32LayerId, u32LayerZorder);
    VDP_CBM_SetMixerPrio           (VDP_CBM_MIX0, VDP_CBM_VP0, 0);
    VDP_CBM_SetMixerPrio           (VDP_CBM_MIX0, VDP_CBM_GP0, 1);

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetRegUp(HI_U32 u32LayerId)
{
    VDP_VID_SetRegUp(u32LayerId);
    if (VDP_LAYER_VID0 == u32LayerId)
    {
        VDP_VID_SetShpParaUp(HI_TRUE);
    }
    VDP_VID_SetRegionParaUp(u32LayerId);
    VDP_VP_SetRegUp(VDP_LAYER_VP0);

    //VDP_WBC_SetUpdMode(VDP_LAYER_WBC_HD0,1);

    return HI_SUCCESS;
}
HI_VOID VDP_DRV_CloseV0V1Layer(HI_VOID)
{
    VDP_VID_SetLayerEnable (VDP_LAYER_VID0, HI_FALSE);
    VDP_VID_SetRegUp(VDP_LAYER_VID0);

    VDP_VID_SetAllRegionDisable(VDP_LAYER_VID1);
    VDP_VID_SetLayerEnable (VDP_LAYER_VID1, HI_FALSE);
    VDP_VID_SetRegUp(VDP_LAYER_VID1);
}

HI_S32 VDP_DRV_SetVidLayer(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstLayerInfoIn, HI_PQ_HDR_CFG  *pstPqHdrCfg)
{
    static VDP_HIHDR_V_CFG_S    stHiHdrCfg;
    HIHDR_SCENE_MODE_E    enSceneMode = HIHDR_BYPASS_MODE;
    XDP_CSC_CFG_S         stXdpCscCfg[HI_PQ_CSC_TYPE_BUUT];
    VDP_RECT_S            stCropRect       ;

    if (u32LayerId >VDP_LAYER_VID1)
    {
       return HI_FAILURE;
    }

    if (HI_NULL == pstLayerInfoIn)
    {
       VDP_PRINT("pstLayerInfoIn is NULL !!!\n");
       return HI_FAILURE;
    }

    memset(&stHiHdrCfg, 0x0, sizeof(VDP_HIHDR_V_CFG_S));
    memcpy(&stCropRect, &pstLayerInfoIn->stXdpFdrCfg.stCropRect, sizeof(VDP_RECT_S));

    if (HI_SUCCESS == XDP_DRV_JudgeVidLayerEnable(u32LayerId, pstLayerInfoIn))
    {
        return HI_SUCCESS;
    }

    XDP_DRV_RegisterClen(u32LayerId, pstLayerInfoIn);

    if (u32LayerId == VDP_LAYER_VID1 && pstLayerInfoIn->stXdpSysCfg.bRegionModeEn == 1)
    {
        XDP_DRV_SetVidLayerRegion(u32LayerId, pstLayerInfoIn);
    }
    else
    {
        XDP_DRV_SetVidLayerFdr(u32LayerId, pstLayerInfoIn);
    }
    XDP_DRV_SetVidIfir(u32LayerId, pstLayerInfoIn);

    if (HI_SUCCESS == XDP_DRV_GetVidZmeCfg(u32LayerId, pstLayerInfoIn))
    {
        XDP_DRV_SetVidZme(u32LayerId, pstLayerInfoIn);
    }
    XDP_DRV_SetVidReso(u32LayerId, pstLayerInfoIn);

    if (HI_SUCCESS == XDP_DRV_GetVidCscInfo(u32LayerId, pstLayerInfoIn, stXdpCscCfg))
    {
        XDP_DRV_SetVidCsc(u32LayerId, stXdpCscCfg);
    }

    XDP_DRV_SetVidBkg(u32LayerId, pstLayerInfoIn);

    if (HI_NULL != pstPqHdrCfg)
    {
        XDP_DRV_GetVidSceneMode(u32LayerId, pstLayerInfoIn, &enSceneMode);
        XDP_DRV_GetHiHdrCfg(u32LayerId, pstLayerInfoIn, pstPqHdrCfg, enSceneMode, &stHiHdrCfg);
        XDP_DRV_SetVDMCfg(u32LayerId, pstLayerInfoIn, pstPqHdrCfg, enSceneMode, &stHiHdrCfg);
    }

    XDP_DRV_SetVP0Reso(u32LayerId, pstLayerInfoIn);
    XDP_DRV_SetVidCBM(u32LayerId, pstLayerInfoIn);

    XDP_DRV_SetRegUp(u32LayerId);

    memcpy(&pstLayerInfoIn->stXdpFdrCfg.stCropRect, &stCropRect, sizeof(VDP_RECT_S));

    return HI_SUCCESS;
}

#endif


HI_VOID VDP_DRV_Set_SysEslSmmu(HI_VOID)
{
    HI_U32  u32Offset           = 0;
    HI_U32  u32RegionOffset     = 0;
    HI_U32  u32LayerId          = 0;
    HI_U32  u32RegionNO         = 0;
    HI_BOOL bSmmuEn             = HI_TRUE ;
    HI_BOOL bChkSumEn           = HI_TRUE ;
    HI_BOOL bPreRdEn            = HI_TRUE ;
    VDP_REQ_LENGTH_E enReqLen   = VDP_REQ_LENGTH_16      ;
    VDP_REQ_CTRL_E   enReqCtrl  = VDP_REQ_CTRL_16BURST_2 ;

    HI_BOOL bMidEn = HI_TRUE;
    HI_BOOL bArbEn = HI_TRUE;
    HI_U32 Routstanding = 15;
    HI_U32 Woutstanding = 2;
    VDP_AXI_EDGE_MODE_E enSplitMode = VDP_AXI_EDGE_MODE_256;

    /*set vid els register*/
    for(u32LayerId = VDP_LAYER_VID0;u32LayerId<=VDP_LAYER_VID1;u32LayerId++)
    {
        u32Offset = u32LayerId * VID_FDR_OFFSET;
        VDP_FDR_VID_SetLmBypass2d     (u32Offset, !bSmmuEn );
        VDP_FDR_VID_SetChmBypass2d    (u32Offset, !bSmmuEn );
        VDP_FDR_VID_SetLmBypass3d     (u32Offset, !bSmmuEn );
        VDP_FDR_VID_SetChmBypass3d    (u32Offset, !bSmmuEn );

        VDP_FDR_VID_SetChecksumEn     (u32Offset, bChkSumEn);
        VDP_FDR_VID_SetPreRdEn        (u32Offset, bPreRdEn );
        VDP_FDR_VID_SetReqLen         (u32Offset, enReqLen );
        VDP_FDR_VID_SetReqCtrl        (u32Offset, enReqCtrl);

        VDP_SetParaUpMode(u32LayerId,1);
    }

    for(u32RegionNO = 0;u32RegionNO<V1_REGION_NUM;u32RegionNO++)
    {
        u32RegionOffset = u32RegionOffset + REGION_OFFSET*u32RegionNO;
        VDP_FDR_VID_SetMrgChmMmuBypass(u32RegionOffset, !bSmmuEn);
        VDP_FDR_VID_SetMrgLmMmuBypass (u32RegionOffset, !bSmmuEn);
    }

    /*set gfx els register*/
    bSmmuEn     = HI_TRUE                ;
    bChkSumEn   = HI_TRUE                ;
    enReqLen    = VDP_REQ_LENGTH_16      ;
    enReqCtrl   = VDP_REQ_CTRL_16BURST_1 ;

    for(u32LayerId = VDP_LAYER_GFX0;u32LayerId<=VDP_LAYER_GFX1;u32LayerId++)
    {
        u32Offset = u32LayerId * VID_FDR_OFFSET;
        VDP_FDR_GFX_SetReqLen         (u32Offset, enReqLen );
        VDP_FDR_GFX_SetReqCtrl        (u32Offset, enReqCtrl);
        VDP_FDR_GFX_SetChecksumEn	  (u32Offset, bChkSumEn);

        VDP_FDR_GFX_SetSmmuBypass3d   (u32Offset, !bSmmuEn );
        VDP_FDR_GFX_SetSmmuBypass2d   (u32Offset, !bSmmuEn );
        VDP_FDR_GFX_SetSmmuBypassH3d  (u32Offset, !bSmmuEn );
        VDP_FDR_GFX_SetSmmuBypassH2d  (u32Offset, !bSmmuEn );

        VDP_GFX_SetUpdMode(u32LayerId,1);
    }

    /*set wbc els register*/
    bSmmuEn     = HI_TRUE                ;
    bChkSumEn   = HI_TRUE                ;
    enReqLen    = VDP_REQ_CTRL_16BURST_1 ;

    VDP_CAP_SetMmu2dBypass    (VDP_LAYER_WBC_HD0, !bSmmuEn );
    VDP_CAP_SetMmu3dBypass    (VDP_LAYER_WBC_HD0, !bSmmuEn );
    VDP_CAP_SetChksumEn       (VDP_LAYER_WBC_HD0, bChkSumEn);
    VDP_CAP_SetWbcLen         (VDP_LAYER_WBC_HD0, enReqLen );
    VDP_CAP_SetCapCkGtEn      (VDP_LAYER_WBC_HD0, HI_FALSE );

    /*set master register*/
    VDP_MASTER_SetMidEnable         (bMidEn      );
    VDP_MASTER_SetArbMode           (bArbEn      );
    VDP_MASTER_SetSplitMode         (enSplitMode );
    VDP_MASTER_SetMstr0Routstanding (Routstanding);
    VDP_MASTER_SetMstr0Woutstanding (Woutstanding);
    /*set rch2_prio 0x8010 = 0x4*/
    VDP_MASTER_SetRchnPrio(2, 1);

    VDP_VP_SetUpdMode(VDP_LAYER_VP0,1);
    VDP_GP_SetUpdMode(VDP_LAYER_GP0,1);
    //VDP_WBC_SetUpdMode(VDP_LAYER_WBC_HD0,1);

}



