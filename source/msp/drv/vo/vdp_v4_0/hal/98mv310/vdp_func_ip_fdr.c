#include "vdp_func_ip_fdr.h"

extern VDP_ADDR_CFG_S  gstVdpAddrCfg;

HI_VOID VDP_VID_InitFdrCfg(HI_U32 enLayer, VDP_FDR_CFG_MODE_E enCfgMode, VDP_VID_FDR_CFG_S* pstFdrCfg)
{
    HI_U32 ii = 0;
    memset(pstFdrCfg, 0, sizeof(VDP_VID_FDR_CFG_S));
#if 0
    //addr config
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64LumAddr = gstVdpAddrCfg.u64VidLumDataAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64ChmAddr = gstVdpAddrCfg.u64VidChmDataAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64LumAddr   = gstVdpAddrCfg.u64VidLum2BitAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64ChmAddr   = gstVdpAddrCfg.u64VidChm2BitAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64LumAddr = gstVdpAddrCfg.u64VidLumHeadAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64ChmAddr = gstVdpAddrCfg.u64VidChmHeadAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64LumAddr   = gstVdpAddrCfg.u64VidLum2BitAddr[enLayer] ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64ChmAddr   = gstVdpAddrCfg.u64VidChm2BitAddr[enLayer] ;
#endif

    pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32LumStr       = gstVdpAddrCfg.u32VidLumHeadStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32ChmStr       = gstVdpAddrCfg.u32VidChmHeadStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr    = gstVdpAddrCfg.u32VidLum2BitStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr    = gstVdpAddrCfg.u32VidChm2BitStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr       = gstVdpAddrCfg.u32VidLumDataStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr       = gstVdpAddrCfg.u32VidChmDataStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32LumStr         = gstVdpAddrCfg.u32VidLum2BitStr[enLayer]  ;
    pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32ChmStr         = gstVdpAddrCfg.u32VidChm2BitStr[enLayer]  ;

    //other config
    if(enCfgMode == VDP_FDR_CFG_MODE_TYP)
    {

        pstFdrCfg->enInFmt                      = VDP_VID_IFMT_SP_444       ;
        pstFdrCfg->enDataWidth                  = VDP_DATA_WTH_8            ;
        pstFdrCfg->enReadMode                   = VDP_RMODE_PROGRESSIVE     ;

        pstFdrCfg->stInRect.u32Wth             = 256                       ;
        pstFdrCfg->stInRect.u32Hgt             = 32                        ;
        pstFdrCfg->stSrcRect.u32Wth            = pstFdrCfg->stInRect.u32Wth + pstFdrCfg->stInRect.u32X;
        pstFdrCfg->stSrcRect.u32Hgt            = pstFdrCfg->stInRect.u32Hgt + pstFdrCfg->stInRect.u32Y;

        pstFdrCfg->enSrc3dMode                  = VDP_DISP_MODE_2D          ;
        pstFdrCfg->enRMode3d                    = VDP_RMODE_3D_INTF         ;

        pstFdrCfg->bSmmuEn                      = HI_FALSE                  ;
        pstFdrCfg->bChkSumEn                    = HI_TRUE                   ;
        pstFdrCfg->bCkGtEn                      = HI_TRUE                   ;


        pstFdrCfg->bFlipEn                      = HI_FALSE                  ;
        pstFdrCfg->bUvOrder                     = HI_FALSE                  ;
        pstFdrCfg->bChmCopyEn                   = HI_FALSE                  ;

        pstFdrCfg->enDrawMode                   = VDP_DRAW_MODE_1           ; //lm & chm
        pstFdrCfg->enDrawPixelMode              = VDP_DRAW_MODE_1           ; //reserved

        pstFdrCfg->stPatternCfg.bPatternEn      = HI_FALSE                  ;
        pstFdrCfg->stPatternCfg.enDemoMode      = VDP_TESTPTTN_MODE_STATIC  ;
        pstFdrCfg->stPatternCfg.enColorMode     = VDP_TESTPTTN_CLR_MODE_FIX ;
        pstFdrCfg->stPatternCfg.enLineWidth     = VDP_TESTPTTN_LINEW_1P     ;
        pstFdrCfg->stPatternCfg.u32Speed        = 1                         ; // Speed * 4pixel
        pstFdrCfg->stPatternCfg.u32Seed         = 0                         ;

        pstFdrCfg->bFdrMuteEn                   = HI_FALSE                  ;
        pstFdrCfg->bFdrMuteReqEn                = HI_FALSE                  ;
        pstFdrCfg->stFdrMuteBkg.u32BkgY         = 0x80                      ; //R,G,B
        pstFdrCfg->stFdrMuteBkg.u32BkgU         = 0x60                      ; //R,G,B
        pstFdrCfg->stFdrMuteBkg.u32BkgV         = 0x10                      ; //R,G,B

        pstFdrCfg->bPreRdEn                     = HI_TRUE                   ;
        pstFdrCfg->bOflMaster                   = HI_FALSE                  ; //reserved
        pstFdrCfg->enReqLen                     = VDP_REQ_LENGTH_16         ;
        pstFdrCfg->enReqCtrl                    = VDP_REQ_CTRL_16BURST_1    ;

        pstFdrCfg->bIsSinglePort                = HI_FALSE                  ;
        pstFdrCfg->bMemMode                     = HI_TRUE                   ;

        pstFdrCfg->enCmpType                    = XDP_CMP_TYPE_OFF          ;

		//tunl
        pstFdrCfg->stTunlCfg.enLowdlyMode       = VDP_LOWDLY_MODE_OFF ;
        pstFdrCfg->stTunlCfg.u64TunlAddr        = 0xfd00000 ;
        pstFdrCfg->stTunlCfg.u32Intervalx1024   = 8 ;
		//press
        pstFdrCfg->stPressCfg.bPressEn          = HI_FALSE ;
        pstFdrCfg->stPressCfg.u32ScopeDrdyNum   = 0 ;
        pstFdrCfg->stPressCfg.u32MinDrdyNum     = 0 ;
        pstFdrCfg->stPressCfg.u32ScopeNoDrdyNum = 0 ;
        pstFdrCfg->stPressCfg.u32MinNoDrdyNum   = 0 ;
        //---------------------------------------------
        // multi-region
        //---------------------------------------------
        pstFdrCfg->bMultiRegionEn        = HI_FALSE                  ;
        pstFdrCfg->enMultiRegionMuteMode = VDP_REGION_MUTE_MODE_SHOW ;
        if(enLayer == VDP_LAYER_VID0)
        {
            pstFdrCfg->u32RegionNum = 0;
        }
        else if(enLayer == VDP_LAYER_VID1)
        {
            pstFdrCfg->u32RegionNum = 4;
        }
        else
        {
            pstFdrCfg->u32RegionNum = 0;
        }
        for(ii=0;ii<pstFdrCfg->u32RegionNum;ii++)
        {
            pstFdrCfg->stRegionInfo[ii].bRegionEn        = HI_FALSE;
            pstFdrCfg->stRegionInfo[ii].bMuteEn          = HI_FALSE;
            pstFdrCfg->stRegionInfo[ii].bMmuBypass       = HI_TRUE ;
            pstFdrCfg->stRegionInfo[ii].bCropEn          = HI_FALSE;
            pstFdrCfg->stRegionInfo[ii].enEdgeColorType  = VDP_REGION_COLOR_MODE_FORE;
            pstFdrCfg->stRegionInfo[ii].bEdgeEn          = HI_FALSE;
            pstFdrCfg->stRegionInfo[ii].stDispReso.u32X   = 0;
            pstFdrCfg->stRegionInfo[ii].stDispReso.u32Y   = 0;
            pstFdrCfg->stRegionInfo[ii].stDispReso.u32Wth = 256;
            pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt = 32 ;
            pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth  = 256;
            pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt  = 32 ;
            pstFdrCfg->stRegionInfo[ii].stInReso.u32X     = 0;
            pstFdrCfg->stRegionInfo[ii].stInReso.u32Y     = 0;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u64Addr = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64LumAddr;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u64Addr = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64ChmAddr;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u64Addr = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64LumAddr;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u64Addr = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64ChmAddr;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str  = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr ;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str  = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr ;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u32Str  = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr ;
            pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u32Str  = pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr ;
        }
    }
    else
    {
        VDP_ASSERT(0);
    }

    return;

}

HI_VOID VDP_VID_SetFdrCfg(HI_U32 enLayer, VDP_VID_FDR_CFG_S* pstFdrCfg)
{
    HI_U32 ii = 0;
    HI_U32  u32RealOffset = 0;
    HI_U32  u32RegionOffset = 0;
    //HI_U32  u32DataWidth = 0;
    VDP_PROC_FMT_E enDataFmt = VDP_PROC_FMT_SP_420;

    u32RealOffset = (gu32VdpVfdrAddr[enLayer] - VDP_VFDR_START_OFFSET);
    //---------------------------
    //Initial Tmp Parameter Addr
    //---------------------------
    VDP_FDR_VID_SetVhdaddrL       (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u64LumAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetVhdcaddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u64ChmAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetVhdnaddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64LumAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetVhdncaddrL     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64ChmAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetHVhdaddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u64LumAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetHVhdcaddrL     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u64ChmAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetBVhdaddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u64LumAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetBVhdcaddrL     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u64ChmAddr    ) & 0xffffffff) );
    VDP_FDR_VID_SetVhdaddrH       (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u64LumAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetVhdcaddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u64ChmAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetVhdnaddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64LumAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetVhdncaddrH     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64ChmAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetHVhdaddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u64LumAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetHVhdcaddrH     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u64ChmAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetBVhdaddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u64LumAddr>>32) & 0xffffffff) );
    VDP_FDR_VID_SetBVhdcaddrH     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u64ChmAddr>>32) & 0xffffffff) );

    VDP_FDR_VID_SetLmStride       (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32LumStr  );//left & right use same stride
    VDP_FDR_VID_SetChmStride      (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32ChmStr  );
    VDP_FDR_VID_SetLmHeadStride   (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32LumStr  );
    VDP_FDR_VID_SetChmHeadStride  (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32ChmStr  );
    VDP_FDR_VID_SetLmTileStride   (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u32LumStr  );
    VDP_FDR_VID_SetChmTileStride  (u32RealOffset, pstFdrCfg->stAddr[VDP_VID_ADDR_2B     ].u32ChmStr  );

    //---------------------------
    //Cfg reso
    //---------------------------
    VDP_FDR_VID_SetIresoW         (u32RealOffset, pstFdrCfg->stInRect.u32Wth - 1  );
    VDP_FDR_VID_SetIresoH         (u32RealOffset, pstFdrCfg->stInRect.u32Hgt - 1  );
    VDP_FDR_VID_SetSrcCropX       (u32RealOffset, pstFdrCfg->stInRect.u32X        );
    VDP_FDR_VID_SetSrcCropY       (u32RealOffset, pstFdrCfg->stInRect.u32Y        );
    VDP_FDR_VID_SetSrcW           (u32RealOffset, pstFdrCfg->stSrcRect.u32Wth - 1 );
    VDP_FDR_VID_SetSrcH           (u32RealOffset, pstFdrCfg->stSrcRect.u32Hgt - 1 );

    //src information
    switch(pstFdrCfg->enInFmt)
    {
        case VDP_VID_IFMT_SP_TILE    :
        case VDP_VID_IFMT_SP_TILE_64 :
        case VDP_VID_IFMT_SP_TILE_400:
        {
            VDP_FDR_VID_SetDataFmt (u32RealOffset, VDP_VID_DATA_FMT_TILE) ;
            break;
        }
        case VDP_VID_IFMT_PKG_UYVY  :
        case VDP_VID_IFMT_PKG_YUYV  :
        case VDP_VID_IFMT_PKG_YVYU  :
        case VDP_VID_IFMT_RGB_888   :
        case VDP_VID_IFMT_PKG_444:
        case VDP_VID_IFMT_PKG_888:
        case VDP_VID_IFMT_ARGB_8888 :
        {
            VDP_FDR_VID_SetDataFmt (u32RealOffset, VDP_VID_DATA_FMT_PKG) ;
            break;
        }
        case VDP_VID_IFMT_SP_400    :
        case VDP_VID_IFMT_SP_420    :
        case VDP_VID_IFMT_SP_422    :
        case VDP_VID_IFMT_SP_444    :
        {
            VDP_FDR_VID_SetDataFmt (u32RealOffset, VDP_VID_DATA_FMT_LINEAR) ;
            break;
        }
        default:
        {
            VDP_ASSERT(0) ;
        }
    }

    switch(pstFdrCfg->enInFmt)
    {
        case VDP_VID_IFMT_ARGB_8888:
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_ARGB8888) ;
            enDataFmt = VDP_PROC_FMT_SP_444;
            break;
        }
        case VDP_VID_IFMT_RGB_888   :
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_RGB888) ;
            enDataFmt = VDP_PROC_FMT_SP_444;
            break;
        }
        case VDP_VID_IFMT_PKG_444:
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV444) ;
            enDataFmt = VDP_PROC_FMT_SP_444;
            break;
        }
        case VDP_VID_IFMT_PKG_888:
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV444) ;
            enDataFmt = VDP_PROC_FMT_SP_444;
            break;
        }
        case VDP_VID_IFMT_SP_444    :
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV444) ;
            enDataFmt = VDP_PROC_FMT_SP_444;
            break;
        }
        case VDP_VID_IFMT_PKG_UYVY  :
        case VDP_VID_IFMT_PKG_YUYV  :
        case VDP_VID_IFMT_PKG_YVYU  :
        case VDP_VID_IFMT_SP_422    :
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV422) ;
            enDataFmt = VDP_PROC_FMT_SP_422;
            break;
        }
        case VDP_VID_IFMT_SP_TILE   :
        case VDP_VID_IFMT_SP_TILE_64:
        case VDP_VID_IFMT_SP_420    :
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV420) ;
            enDataFmt = VDP_PROC_FMT_SP_420;
            break;
        }
        case VDP_VID_IFMT_SP_400     :
        case VDP_VID_IFMT_SP_TILE_400:
        {
            VDP_FDR_VID_SetDataType(u32RealOffset, VDP_VID_DATA_TYPE_YUV400) ;
            enDataFmt = VDP_PROC_FMT_SP_400;
            break;
        }
        default:
        {
            VDP_ASSERT(0) ;
        }
    }

    VDP_FDR_VID_SetDataWidth      (u32RealOffset, pstFdrCfg->enDataWidth     ) ;
    VDP_FDR_VID_SetDispMode       (u32RealOffset, pstFdrCfg->enSrc3dMode     ) ;
	VDP_FDR_VID_SetRmode3d        (u32RealOffset, pstFdrCfg->enRMode3d       );

    //mmu
    #if MMU_TEST
    VDP_FDR_VID_SetLmBypass2d     (u32RealOffset, 0       ) ;
    VDP_FDR_VID_SetChmBypass2d    (u32RealOffset, 0       ) ;
    VDP_FDR_VID_SetLmBypass3d     (u32RealOffset, 0       ) ;
    VDP_FDR_VID_SetChmBypass3d    (u32RealOffset, 0       ) ;
    #else
    VDP_FDR_VID_SetLmBypass2d     (u32RealOffset, 1       ) ;
    VDP_FDR_VID_SetChmBypass2d    (u32RealOffset, 1       ) ;
    VDP_FDR_VID_SetLmBypass3d     (u32RealOffset, 1       ) ;
    VDP_FDR_VID_SetChmBypass3d    (u32RealOffset, 1       ) ;
    #endif
    VDP_FDR_VID_SetChecksumEn	  (u32RealOffset, pstFdrCfg->bChkSumEn	     ) ;
    VDP_FDR_VID_SetFdrCkGtEn	  (u32RealOffset, pstFdrCfg->bCkGtEn   	     ) ;

    //read mode
    VDP_FDR_VID_SetLmRmode        (u32RealOffset, pstFdrCfg->enReadMode      ) ;
    VDP_FDR_VID_SetChmRmode       (u32RealOffset, pstFdrCfg->enReadMode      ) ;
    VDP_FDR_VID_SetChmCopyEn      (u32RealOffset, pstFdrCfg->bChmCopyEn      ) ;

    //draw hor & ver
    VDP_FDR_VID_SetDrawPixelMode  (u32RealOffset, pstFdrCfg->enDrawPixelMode ) ;
    VDP_FDR_VID_SetLmDrawMode     (u32RealOffset, pstFdrCfg->enDrawMode      ) ;
    VDP_FDR_VID_SetChmDrawMode    (u32RealOffset, pstFdrCfg->enDrawMode      ) ;

    //coperation
    VDP_FDR_VID_SetFlipEn         (u32RealOffset, pstFdrCfg->bFlipEn         ) ;
    VDP_FDR_VID_SetUvOrderEn      (u32RealOffset, pstFdrCfg->bUvOrder        ) ;

    //mute
	VDP_FDR_VID_SetMuteEn         (u32RealOffset, pstFdrCfg->bFdrMuteEn           );
	VDP_FDR_VID_SetMuteReqEn      (u32RealOffset, pstFdrCfg->bFdrMuteReqEn        );
	//VDP_FDR_VID_SetMuteAlpha    (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgA );
	VDP_FDR_VID_SetMuteY          (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgY );
	VDP_FDR_VID_SetMuteCb         (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgU );
	VDP_FDR_VID_SetMuteCr         (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgV );

    //mac
	VDP_FDR_VID_SetPreRdEn        (u32RealOffset, pstFdrCfg->bPreRdEn             );
	VDP_FDR_VID_SetOflMaster      (u32RealOffset, pstFdrCfg->bOflMaster           );
	VDP_FDR_VID_SetReqLen         (u32RealOffset, pstFdrCfg->enReqLen             );
	VDP_FDR_VID_SetReqCtrl        (u32RealOffset, pstFdrCfg->enReqCtrl            );

    //testpatten
    VDP_FDR_VID_SetTestpatternEn  (u32RealOffset, pstFdrCfg->stPatternCfg.bPatternEn   );
	VDP_FDR_VID_SetTpMode         (u32RealOffset, pstFdrCfg->stPatternCfg.enDemoMode   );
	VDP_FDR_VID_SetTpColorMode    (u32RealOffset, pstFdrCfg->stPatternCfg.enColorMode  );
	VDP_FDR_VID_SetTpLineW        (u32RealOffset, pstFdrCfg->stPatternCfg.enLineWidth  );
	VDP_FDR_VID_SetTpSpeed        (u32RealOffset, pstFdrCfg->stPatternCfg.u32Speed     );
	VDP_FDR_VID_SetTpSeed         (u32RealOffset, pstFdrCfg->stPatternCfg.u32Seed      );

	//press
	VDP_FDR_VID_SetFdrPressEn	  (u32RealOffset, pstFdrCfg->stPressCfg.bPressEn          );
	VDP_FDR_VID_SetScopeDrdyNum   (u32RealOffset, pstFdrCfg->stPressCfg.u32ScopeDrdyNum   );
	VDP_FDR_VID_SetMinDrdyNum     (u32RealOffset, pstFdrCfg->stPressCfg.u32MinDrdyNum     );
	VDP_FDR_VID_SetScopeNodrdyNum (u32RealOffset, pstFdrCfg->stPressCfg.u32ScopeNoDrdyNum );
	VDP_FDR_VID_SetMinNodrdyNum   (u32RealOffset, pstFdrCfg->stPressCfg.u32MinNoDrdyNum   );

	//tunl
	VDP_FDR_VID_SetReqLdMode	  (u32RealOffset, pstFdrCfg->stTunlCfg.enLowdlyMode    );
	VDP_FDR_VID_SetTunlInterval   (u32RealOffset, pstFdrCfg->stTunlCfg.u32Intervalx1024);
	VDP_FDR_VID_SetTunlThd        (u32RealOffset, 0x100                                );
	VDP_FDR_VID_SetTunlAddrL      (u32RealOffset, ((pstFdrCfg->stTunlCfg.u64TunlAddr    ) & 0xffffffff));
	VDP_FDR_VID_SetTunlAddrH      (u32RealOffset, ((pstFdrCfg->stTunlCfg.u64TunlAddr>>32) & 0xffffffff));

	//VDP_FDR_VID_SetSinglePortMode (u32RealOffset, pstFdrCfg->bIsSinglePort        );
    //VDP_FDR_VID_SetMemMode        (u32RealOffset, pstFdrCfg->bMemMode             );

    //dcmp
    VDP_FDR_VID_SetDcmpType       (u32RealOffset, pstFdrCfg->enCmpType); // DcmpEn => DcmpType

    //---------------------------------------------
    // multi-region
    //---------------------------------------------
    VDP_FDR_VID_SetMrgEnable  (u32RealOffset, pstFdrCfg->bMultiRegionEn       );
    VDP_FDR_VID_SetMrgMuteMode(u32RealOffset, pstFdrCfg->enMultiRegionMuteMode);
    if(enLayer == VDP_LAYER_VID0)
    {
        u32RegionOffset = 0;
        VDP_ASSERT(pstFdrCfg->u32RegionNum == 0);
    }
    else if(enLayer == VDP_LAYER_VID1)
    {
        u32RegionOffset = 0;
        VDP_ASSERT(pstFdrCfg->u32RegionNum == 4);
    }
    else
    {
        VDP_ASSERT(pstFdrCfg->u32RegionNum == 0);
        VDP_ASSERT(pstFdrCfg->bMultiRegionEn == HI_FALSE);
    }

    if(pstFdrCfg->bMultiRegionEn)
    {
        for(ii=0;ii<pstFdrCfg->u32RegionNum;ii++)
        {
            VDP_FDR_VID_SetMrgEn          (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].bRegionEn          );
            VDP_FDR_VID_SetMrgMuteEn      (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].bMuteEn            );           
            #if MMU_TEST
            VDP_FDR_VID_SetMrgChmMmuBypass(u32RegionOffset, 0         );
            VDP_FDR_VID_SetMrgLmMmuBypass (u32RegionOffset, 0         );
            #else         
            VDP_FDR_VID_SetMrgChmMmuBypass(u32RegionOffset, 1         );
            VDP_FDR_VID_SetMrgLmMmuBypass (u32RegionOffset, 1         );
            #endif            
            VDP_FDR_VID_SetMrgCropEn      (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].bCropEn            );
            VDP_FDR_VID_SetMrgEdgeTyp     (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].enEdgeColorType    );
            VDP_FDR_VID_SetMrgEdgeEn      (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].bEdgeEn            );
            VDP_FDR_VID_SetMrgXpos        (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stDispReso.u32X    );
            VDP_FDR_VID_SetMrgYpos        (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stDispReso.u32Y    );
            VDP_FDR_VID_SetMrgWidth       (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stDispReso.u32Wth-1);
            VDP_FDR_VID_SetMrgHeight      (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt-1);
            VDP_FDR_VID_SetMrgSrcWidth    (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth -1);
            VDP_FDR_VID_SetMrgSrcHeight   (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt -1);
            VDP_FDR_VID_SetMrgSrcHoffset  (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stInReso.u32X      );
            VDP_FDR_VID_SetMrgSrcVoffset  (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stInReso.u32Y      );
            VDP_FDR_VID_SetMrgYAddr       (u32RegionOffset, (pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u64Addr));//>>4
            VDP_FDR_VID_SetMrgCAddr       (u32RegionOffset, (pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u64Addr));//>>4
            VDP_FDR_VID_SetMrgYhAddr      (u32RegionOffset, (pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u64Addr));//>>4
            VDP_FDR_VID_SetMrgChAddr      (u32RegionOffset, (pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u64Addr));//>>4
            VDP_FDR_VID_SetMrgYStride     (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str  );
            VDP_FDR_VID_SetMrgCStride     (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str  );
            VDP_FDR_VID_SetMrgYhStride    (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u32Str  );
            VDP_FDR_VID_SetMrgChStride    (u32RegionOffset, pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u32Str  );

            u32RegionOffset = u32RegionOffset + REGION_OFFSET;
        }
    }
#if EDA_TEST
    cout << "--------------------------------------------------------------" <<endl;
    cout << "[vid_fdr] enLayer = " << enLayer <<endl;
    cout << "[vid_fdr] u32RealOffset = " << u32RealOffset <<endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64LumAddr    = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64LumAddr    << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64ChmAddr    = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u64ChmAddr    << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr     = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr     << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr     = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr     << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64LumAddr = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64LumAddr << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64ChmAddr = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u64ChmAddr << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr  = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr  << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr  = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr  << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64LumAddr    = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64LumAddr    << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64ChmAddr    = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u64ChmAddr    << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32LumStr     = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32LumStr     << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32ChmStr     = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD].u32ChmStr     << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64LumAddr      = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64LumAddr      << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64ChmAddr      = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u64ChmAddr      << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32LumStr       = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32LumStr       << endl;
    cout << "[vid_fdr] pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32ChmStr       = 0x" << hex << pstFdrCfg->stAddr[VDP_VID_ADDR_2B].u32ChmStr       << endl;
    cout << "[vid_fdr] pstFdrCfg->enInFmt                                 = 0x" << hex << pstFdrCfg->enInFmt                                 << endl;
    cout << "[vid_fdr] pstFdrCfg->enDataWidth                             = 0x" << hex << pstFdrCfg->enDataWidth                             << endl;
    cout << "[vid_fdr] pstFdrCfg->stInRect.u32X                           = "   << dec << pstFdrCfg->stInRect.u32X                           << endl;
    cout << "[vid_fdr] pstFdrCfg->stInRect.u32Y                           = "   << dec << pstFdrCfg->stInRect.u32Y                           << endl;
    cout << "[vid_fdr] pstFdrCfg->stInRect.u32Wth                         = "   << dec << pstFdrCfg->stInRect.u32Wth                         << endl;
    cout << "[vid_fdr] pstFdrCfg->stInRect.u32Hgt                         = "   << dec << pstFdrCfg->stInRect.u32Hgt                         << endl;
    cout << "[vid_fdr] pstFdrCfg->stSrcRect.u32Wth                        = "   << dec << pstFdrCfg->stSrcRect.u32Wth                        << endl;
    cout << "[vid_fdr] pstFdrCfg->stSrcRect.u32Hgt                        = "   << dec << pstFdrCfg->stSrcRect.u32Hgt                        << endl;
    cout << "[vid_fdr] pstFdrCfg->enCmpType                               = 0x" << hex << pstFdrCfg->enCmpType                               << endl;
    cout << "[vid_fdr] pstFdrCfg->enSrc3dMode                             = 0x" << hex << pstFdrCfg->enSrc3dMode                             << endl;
    cout << "[vid_fdr] pstFdrCfg->enRMode3d                               = 0x" << hex << pstFdrCfg->enRMode3d                               << endl;
    cout << "[vid_fdr] pstFdrCfg->bSmmuEn                                 = 0x" << hex << pstFdrCfg->bSmmuEn                                 << endl;
    cout << "[vid_fdr] pstFdrCfg->bChkSumEn                               = 0x" << hex << pstFdrCfg->bChkSumEn                               << endl;
    cout << "[vid_fdr] pstFdrCfg->bCkGtEn                                 = 0x" << hex << pstFdrCfg->bCkGtEn                                 << endl;
    cout << "[vid_fdr] pstFdrCfg->enReadMode                              = 0x" << hex << pstFdrCfg->enReadMode                              << endl;
    cout << "[vid_fdr] pstFdrCfg->bChmCopyEn                              = 0x" << hex << pstFdrCfg->bChmCopyEn                              << endl;
    cout << "[vid_fdr] pstFdrCfg->bFlipEn                                 = 0x" << hex << pstFdrCfg->bFlipEn                                 << endl;
    cout << "[vid_fdr] pstFdrCfg->bUvOrder                                = 0x" << hex << pstFdrCfg->bUvOrder                                << endl;
    cout << "[vid_fdr] pstFdrCfg->enDrawMode                              = 0x" << hex << pstFdrCfg->enDrawMode                              << endl;
    cout << "[vid_fdr] pstFdrCfg->enDrawPixelMode                         = 0x" << hex << pstFdrCfg->enDrawPixelMode                         << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.bPatternEn                 = 0x" << hex << pstFdrCfg->stPatternCfg.bPatternEn                 << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.enDemoMode                 = 0x" << hex << pstFdrCfg->stPatternCfg.enDemoMode                 << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.enColorMode                = 0x" << hex << pstFdrCfg->stPatternCfg.enColorMode                << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.enLineWidth                = 0x" << hex << pstFdrCfg->stPatternCfg.enLineWidth                << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.u32Speed                   = 0x" << hex << pstFdrCfg->stPatternCfg.u32Speed                   << endl;
    cout << "[vid_fdr] pstFdrCfg->stPatternCfg.u32Seed                    = 0x" << hex << pstFdrCfg->stPatternCfg.u32Seed                    << endl;
    cout << "[vid_fdr] pstFdrCfg->bFdrMuteEn                              = 0x" << hex << pstFdrCfg->bFdrMuteEn                              << endl;
    cout << "[vid_fdr] pstFdrCfg->bFdrMuteReqEn                           = 0x" << hex << pstFdrCfg->bFdrMuteReqEn                           << endl;
    cout << "[vid_fdr] pstFdrCfg->bMultiRegionEn                          = 0x" << hex << pstFdrCfg->bMultiRegionEn                          << endl;
    if(pstFdrCfg->bMultiRegionEn)
    {
        for(ii=0;ii<pstFdrCfg->u32RegionNum;ii++)
        {
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].bRegionEn = 0x" << hex << pstFdrCfg->stRegionInfo[ii].bRegionEn << endl;
            if(pstFdrCfg->stRegionInfo[ii].bRegionEn == HI_FALSE)
            {
                continue;
            }
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].bMuteEn          = 0x" << hex << pstFdrCfg->stRegionInfo[ii].bMuteEn          << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].bMmuBypass       = 0x" << hex << pstFdrCfg->stRegionInfo[ii].bMmuBypass       << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].bCropEn          = 0x" << hex << pstFdrCfg->stRegionInfo[ii].bCropEn          << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].enEdgeColorType  = 0x" << hex << pstFdrCfg->stRegionInfo[ii].enEdgeColorType  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].bEdgeEn          = 0x" << hex << pstFdrCfg->stRegionInfo[ii].bEdgeEn          << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stDispReso.u32X  =   " << dec << pstFdrCfg->stRegionInfo[ii].stDispReso.u32X  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stDispReso.u32Y  =   " << dec << pstFdrCfg->stRegionInfo[ii].stDispReso.u32Y  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stDispReso.u32Wth=   " << dec << pstFdrCfg->stRegionInfo[ii].stDispReso.u32Wth<< endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stDispReso.u32Hgt=   " << dec << pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt<< endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stSrcReso.u32Wth =   " << dec << pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stSrcReso.u32Hgt =   " << dec << pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stInReso.u32X    =   " << dec << pstFdrCfg->stRegionInfo[ii].stInReso.u32X    << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stInReso.u32Y    =   " << dec << pstFdrCfg->stRegionInfo[ii].stInReso.u32Y    << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_DATA_LUM].u64Addr = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u64Addr << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_DATA_CHM].u64Addr = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u64Addr << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_HEAD_LUM].u64Addr = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u64Addr << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_HEAD_CHM].u64Addr = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u64Addr << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str  = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str  = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_HEAD_LUM].u32Str  = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u32Str  << endl;
            cout << "[vid_fdr] pstFdrCfg->stRegionInfo[" << dec << ii << "].stAddr[VDP_REGION_ADDR_HEAD_CHM].u32Str  = 0x" << hex << pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u32Str  << endl;
        }
    }
#endif

#if 0
    //---------------------------
    //Assertion
    //---------------------------
    VDP_ASSERT( pstFdrCfg->stInRect.u32Wth >= 32 );
    VDP_ASSERT( pstFdrCfg->stInRect.u32Hgt >= 8  );
    VDP_ASSERT((pstFdrCfg->stInRect.u32Wth% 2) == 0  );
    VDP_ASSERT((pstFdrCfg->stInRect.u32Hgt% 2) == 0  );
    VDP_ASSERT( pstFdrCfg->stSrcRect.u32Wth >= pstFdrCfg->stInRect.u32Wth + pstFdrCfg->stInRect.u32X);
    VDP_ASSERT( pstFdrCfg->stSrcRect.u32Hgt >= pstFdrCfg->stInRect.u32Hgt + pstFdrCfg->stInRect.u32Y);

    if((pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_420)&&((pstFdrCfg->enReadMode==VDP_RMODE_TOP)||(pstFdrCfg->enReadMode==VDP_RMODE_BOTTOM)))
    {
        VDP_ASSERT((pstFdrCfg->stInRect.u32Y% 4  ) == 0  );
        VDP_ASSERT((pstFdrCfg->stInRect.u32Hgt% 4) == 0  );
    }

    if((pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_TILE)||(pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_TILE_400))
    {
        VDP_ASSERT((pstFdrCfg->enDataWidth == VDP_DATA_WTH_8)||(pstFdrCfg->enDataWidth == VDP_DATA_WTH_10));
    }

    if(pstFdrCfg->enCmpType == XDP_CMP_TYPE_SEG)
    {
        VDP_ASSERT((pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_TILE)||(pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_TILE_400));
    }

    VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr%16 == 0);
    VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr%16 == 0);

    u32DataWidth  = 8+((HI_U32)pstFdrCfg->enDataWidth)*2;

    switch(pstFdrCfg->enInFmt)
    {
        case VDP_VID_IFMT_SP_420:
        case VDP_VID_IFMT_SP_422:
        case VDP_VID_IFMT_SP_444:
            {
                //VDP_ASSERT(pstFdrCfg->enDataWidth <= 2);
                VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr >= ((pstFdrCfg->stSrcRect.u32Wth)*u32DataWidth+7)/8);
                //VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32ChmStr >= ((pstFdrCfg->stSrcRect.u32Wth)*u32DataWidth+7)/8);
                break;
            }
        case VDP_VID_IFMT_SP_400:
            {
                //VDP_ASSERT(pstFdrCfg->enDataWidth <= 2);
                VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr >= ((pstFdrCfg->stSrcRect.u32Wth)*u32DataWidth+7)/8);
                break;
            }
        case VDP_VID_IFMT_SP_TILE    :
        case VDP_VID_IFMT_SP_TILE_400:
            {
                //VDP_ASSERT(pstFdrCfg->stAddr[VDP_VID_ADDR_DATA].u32LumStr >= ((VdpUpAlign(pstFdrCfg->stSrcRect.u32Wth,64))*8+7)/8);
                break;
            }
        case VDP_VID_IFMT_RGB_888    :
        case VDP_VID_IFMT_PKG_444 :
        case VDP_VID_IFMT_PKG_888 :
        case VDP_VID_IFMT_ARGB_8888  :
            {
                break;
            }
        case VDP_VID_IFMT_PKG_UYVY  :
        case VDP_VID_IFMT_PKG_YUYV  :
        case VDP_VID_IFMT_PKG_YVYU  :
        case VDP_VID_IFMT_SP_TILE_64:
            {
                break;
            }
        default:XDP_ASSERT(0);
    }

	if(pstFdrCfg->enCmpType == XDP_CMP_TYPE_FRM)
	{
        VDP_ASSERT(0);
    }

    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA    ].u32LumStr < 0x10000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA    ].u32ChmStr < 0x10000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D ].u32LumStr < 0x10000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D ].u32ChmStr < 0x10000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD    ].u32LumStr < 0x10000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD    ].u32ChmStr < 0x10000);

    if(pstFdrCfg->bMultiRegionEn)
    {
        VDP_ASSERT((pstFdrCfg->enDataWidth == VDP_DATA_WTH_8)||(pstFdrCfg->enDataWidth == VDP_DATA_WTH_10));
        for(ii=0;ii<pstFdrCfg->u32RegionNum;ii++)
        {
            if(pstFdrCfg->stRegionInfo[ii].bRegionEn)
            {
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stDispReso.u32Wth >= 32);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt >= 32);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stDispReso.u32X %2) == 0);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stDispReso.u32Y %2) == 0);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth%2) == 0);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt%2) == 0);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stInReso.u32X   %2) == 0);
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stInReso.u32Y   %2) == 0);
                if (pstFdrCfg->stRegionInfo[ii].bCropEn)
                {
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth >= (pstFdrCfg->stRegionInfo[ii].stInReso.u32X+pstFdrCfg->stRegionInfo[ii].stDispReso.u32Wth)));
                VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt >= (pstFdrCfg->stRegionInfo[ii].stInReso.u32Y+pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt)));
                }
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u64Addr%16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u64Addr%16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u64Addr%16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u64Addr%16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str %16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str %16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_LUM].u32Str %16 == 0);
                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_HEAD_CHM].u32Str %16 == 0);

                VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_LUM].u32Str >= pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth  );
                if(pstFdrCfg->enInFmt == VDP_VID_IFMT_SP_444)
                {
                    VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str >= pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth*2);
                }
                else if(pstFdrCfg->enInFmt != VDP_VID_IFMT_SP_400)
                {
                    VDP_ASSERT(pstFdrCfg->stRegionInfo[ii].stAddr[VDP_REGION_ADDR_DATA_CHM].u32Str >= pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Wth);
                }

                if((pstFdrCfg->enInFmt==VDP_VID_IFMT_SP_420)&&((pstFdrCfg->enReadMode==VDP_RMODE_TOP)||(pstFdrCfg->enReadMode==VDP_RMODE_BOTTOM)))
                {
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stDispReso.u32Y  % 4 ) == 0);
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stDispReso.u32Hgt% 4 ) == 0);
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Y   % 4 ) == 0);
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stSrcReso.u32Hgt % 4 ) == 0);
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stInReso.u32Y    % 4 ) == 0);
                    VDP_ASSERT((pstFdrCfg->stRegionInfo[ii].stInReso.u32Hgt  % 4 ) == 0);
                }

            }
        }
    }

#if 0
    if(pstFdrCfg->bSmmuEn == HI_TRUE)
    {
        if(VDP_LAYER_VID0 == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32LumStr <= (8192*32/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32ChmStr <= (8192*24/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr <= (4096*32/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr <= (4096*24/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32LumStr <= (4096*32/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32ChmStr <= (4096*24/8));
        }
        else if(VDP_LAYER_VID1 == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32LumStr <= (4096*10/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA   ].u32ChmStr <= (4096*20/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr <= (4096*10/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr <= (4096*20/8));
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32LumStr == 0);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32ChmStr == 0);
        }
        else if(VDP_LAYER_VID_EL == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA    ].u32LumStr <= (4096*32/8));
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA    ].u32ChmStr <= (4096*20/8));
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32LumStr == 0);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_DATA_3D].u32ChmStr == 0);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32LumStr == 0);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_VID_ADDR_HEAD   ].u32ChmStr == 0);
        }
    }
#endif
#endif
    return;
}



HI_VOID VDP_GFX_InitFdrCfg(HI_U32 enLayer, VDP_FDR_CFG_MODE_E enCfgMode, VDP_GFX_FDR_CFG_S* pstFdrCfg)
{
    memset(pstFdrCfg, 0, sizeof(VDP_GFX_FDR_CFG_S));

    #if 0
    //src info
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u64Addr = gstVdpAddrCfg.u64GfxDataAddr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u64Addr = gstVdpAddrCfg.u64GfxDcmpAddr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u64Addr = gstVdpAddrCfg.u64GfxDcmpAddr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u64Addr = 0;
    pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u64Addr = gstVdpAddrCfg.u64GfxHeadAddr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u64Addr = gstVdpAddrCfg.u64GfxAlphaAddr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u64Addr = 0;
    pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u64Addr = 0;
    #endif
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u32Str  = gstVdpAddrCfg.u32GfxDataStr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u32Str  = gstVdpAddrCfg.u32GfxDcmpStr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u32Str  = gstVdpAddrCfg.u32GfxDcmpStr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u32Str  = 0;
    pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u32Str  = gstVdpAddrCfg.u32GfxHeadStr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u32Str  = gstVdpAddrCfg.u32GfxHeadStr[enLayer];
    pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u32Str  = 0;
    pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u32Str  = 0;

    if(enCfgMode == VDP_FDR_CFG_MODE_TYP)
    {
        pstFdrCfg->enInFmt                   = VDP_GFX_IFMT_ARGB_8888    ;
        pstFdrCfg->enReadMode                = VDP_RMODE_PROGRESSIVE     ;
        pstFdrCfg->stInRect.u32Wth           = 256                       ;
        pstFdrCfg->stInRect.u32Hgt           = 32                        ;
        pstFdrCfg->enSrc3dMode               = VDP_DISP_MODE_2D          ; //fdr in img mode
        pstFdrCfg->enRMode3d                 = VDP_RMODE_3D_INTF         ; //fdr in img mode
        pstFdrCfg->bPreMultEn                = HI_FALSE                  ; //open this later...need modify
        pstFdrCfg->bPalphaEn                 = HI_FALSE                  ;
        pstFdrCfg->bPalphaRangeIsFull        = HI_TRUE                   ; //0: 0~128, 1: 0~255
        pstFdrCfg->u32Alpha0                 = 0                         ;
        pstFdrCfg->u32Alpha1                 = 255                       ;
        pstFdrCfg->bFlipEn                   = HI_FALSE                  ;
        pstFdrCfg->enDrawMode                = VDP_DRAW_MODE_1           ;
        //ckey
        pstFdrCfg->bCkeyEn                   = HI_FALSE                  ;
        pstFdrCfg->stCkeyCfg.u32Key_r_min    = 0                         ;
        pstFdrCfg->stCkeyCfg.u32Key_g_min    = 0                         ;
        pstFdrCfg->stCkeyCfg.u32Key_b_min    = 0                         ;
        pstFdrCfg->stCkeyCfg.u32Key_r_max    = 255                       ;
        pstFdrCfg->stCkeyCfg.u32Key_g_max    = 255                       ;
        pstFdrCfg->stCkeyCfg.u32Key_b_max    = 255                       ;
        pstFdrCfg->stCkeyCfg.u32Key_r_msk    = 0xff                      ;
        pstFdrCfg->stCkeyCfg.u32Key_g_msk    = 0xff                      ;
        pstFdrCfg->stCkeyCfg.u32Key_b_msk    = 0xff                      ;
        pstFdrCfg->stCkeyCfg.bKeyMode        = 0                         ;
        pstFdrCfg->enBitextMode              = VDP_GFX_BITEXTEND_1ST     ;
        //fdr mute
        pstFdrCfg->bFdrMuteEn                = HI_FALSE                  ;
        pstFdrCfg->bFdrMuteReqEn             = HI_FALSE                  ;
        pstFdrCfg->stFdrMuteBkg.u32BkgA      = 0x10                      ;
        pstFdrCfg->stFdrMuteBkg.u32BkgY      = 0x20                      ;
        pstFdrCfg->stFdrMuteBkg.u32BkgU      = 0x30                      ;
        pstFdrCfg->stFdrMuteBkg.u32BkgV      = 0x40                      ;
        //dcmp
        pstFdrCfg->enCmpType                 = XDP_CMP_TYPE_OFF          ;
        pstFdrCfg->stDcmpSegCfg.bAddrMapEn   = HI_FALSE;//HI_TRUE                   ;
        //testpatten
        pstFdrCfg->stPatternCfg.bPatternEn  = HI_FALSE                  ;
        pstFdrCfg->stPatternCfg.enDemoMode  = VDP_TESTPTTN_MODE_STATIC  ;
        pstFdrCfg->stPatternCfg.enColorMode = VDP_TESTPTTN_CLR_MODE_FIX ;
        pstFdrCfg->stPatternCfg.enLineWidth = VDP_TESTPTTN_LINEW_1P     ;
        pstFdrCfg->stPatternCfg.u32Speed    = 4                         ;
        pstFdrCfg->stPatternCfg.u32Seed     = 1                         ;
        //mac
        pstFdrCfg->bOflMaster                = HI_FALSE                  ;
        pstFdrCfg->enReqLen                  = VDP_REQ_LENGTH_16         ;
        pstFdrCfg->enReqCtrl                 = VDP_REQ_CTRL_16BURST_1    ;
        //mmu
        pstFdrCfg->bSmmuEn                   = HI_FALSE                  ;
        pstFdrCfg->bChkSumEn                 = HI_TRUE                   ;
        pstFdrCfg->bCkGtEn                   = HI_TRUE                   ;
        //memory
        pstFdrCfg->bPortMode                 = HI_FALSE                  ;
        //axi
        pstFdrCfg->bLatencyClr               = HI_FALSE                  ;
		//press
        pstFdrCfg->stPressCfg.bPressEn          = HI_FALSE ;
        pstFdrCfg->stPressCfg.u32ScopeDrdyNum   = 0 ;
        pstFdrCfg->stPressCfg.u32MinDrdyNum     = 0 ;
        pstFdrCfg->stPressCfg.u32ScopeNoDrdyNum = 0 ;
        pstFdrCfg->stPressCfg.u32MinNoDrdyNum   = 0 ;
    }
	else
    {
        //VDP_ASSERT(0);
    }

    return;

}

HI_VOID VDP_GFX_SetFdrCfg(HI_U32 enLayer, VDP_GFX_FDR_CFG_S* pstFdrCfg)
{
    HI_U32  u32RealOffset = 0;

    u32RealOffset = (gu32VdpGfdrAddr[enLayer] - VDP_GFDR_START_OFFSET);
#if EDA_TEST

    cout << "--------------------------------------------------------------" <<endl;
    cout << "[gfx_fdr] enLayer = " << enLayer << endl ;
    cout << "[gfx_fdr] u32RealOffset = " << u32RealOffset << endl ;

    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2   ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u32Str  << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u64Addr = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u64Addr << endl;
    cout << "[gfx_fdr ] pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u32Str  = 0x" << hex << pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u32Str  << endl;

    cout << "[gfx_fdr] pstFdrCfg->enInFmt                  = 0x" << hex << pstFdrCfg->enInFmt                  << endl;
    cout << "[gfx_fdr] pstFdrCfg->enReadMode               = 0x" << hex << pstFdrCfg->enReadMode               << endl;
    cout << "[gfx_fdr] pstFdrCfg->stInRect.u32X            = "   << dec << pstFdrCfg->stInRect.u32X            << endl;
    cout << "[gfx_fdr] pstFdrCfg->stInRect.u32Y            = "   << dec << pstFdrCfg->stInRect.u32Y            << endl;
    cout << "[gfx_fdr] pstFdrCfg->stInRect.u32Wth          = "   << dec << pstFdrCfg->stInRect.u32Wth          << endl;
    cout << "[gfx_fdr] pstFdrCfg->stInRect.u32Hgt          = "   << dec << pstFdrCfg->stInRect.u32Hgt          << endl;
    cout << "[gfx_fdr] pstFdrCfg->stSrcRect.u32Wth         = "   << dec << pstFdrCfg->stSrcRect.u32Wth         << endl;
    cout << "[gfx_fdr] pstFdrCfg->stSrcRect.u32Hgt         = "   << dec << pstFdrCfg->stSrcRect.u32Hgt         << endl;
    cout << "[gfx_fdr] pstFdrCfg->enSrc3dMode              = 0x" << hex << pstFdrCfg->enSrc3dMode              << endl;
    cout << "[gfx_fdr] pstFdrCfg->enRMode3d                = 0x" << hex << pstFdrCfg->enRMode3d                << endl;
    cout << "[gfx_fdr] pstFdrCfg->bPreMultEn               = 0x" << hex << pstFdrCfg->bPreMultEn               << endl;
    cout << "[gfx_fdr] pstFdrCfg->bPalphaEn                = 0x" << hex << pstFdrCfg->bPalphaEn                << endl;
    cout << "[gfx_fdr] pstFdrCfg->bPalphaRangeIsFull       = 0x" << hex << pstFdrCfg->bPalphaRangeIsFull       << endl;
    cout << "[gfx_fdr] pstFdrCfg->u32Alpha0                = 0x" << hex << pstFdrCfg->u32Alpha0                << endl;
    cout << "[gfx_fdr] pstFdrCfg->u32Alpha1                = 0x" << hex << pstFdrCfg->u32Alpha1                << endl;
    cout << "[gfx_fdr] pstFdrCfg->bFlipEn                  = 0x" << hex << pstFdrCfg->bFlipEn                  << endl;
    cout << "[gfx_fdr] pstFdrCfg->enDrawMode               = 0x" << hex << pstFdrCfg->enDrawMode               << endl;

    cout << "[gfx_fdr] pstFdrCfg->bCkeyEn                  = 0x" << hex << pstFdrCfg->bCkeyEn                  << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_r_min   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_r_min   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_g_min   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_g_min   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_b_min   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_b_min   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_r_max   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_r_max   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_g_max   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_g_max   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_b_max   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_b_max   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_r_msk   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_r_msk   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_g_msk   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_g_msk   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.u32Key_b_msk   = 0x" << hex << pstFdrCfg->stCkeyCfg.u32Key_b_msk   << endl;
    cout << "[gfx_fdr] pstFdrCfg->stCkeyCfg.bKeyMode       = 0x" << hex << pstFdrCfg->stCkeyCfg.bKeyMode       << endl;
    cout << "[gfx_fdr] pstFdrCfg->enBitextMode             = 0x" << hex << pstFdrCfg->enBitextMode             << endl;

    cout << "[gfx_fdr] pstFdrCfg->bFdrMuteEn               = 0x" << hex << pstFdrCfg->bFdrMuteEn               << endl;
    cout << "[gfx_fdr] pstFdrCfg->bFdrMuteReqEn            = 0x" << hex << pstFdrCfg->bFdrMuteReqEn            << endl;
    cout << "[gfx_fdr] pstFdrCfg->stFdrMuteBkg.u32BkgA     = 0x" << hex << pstFdrCfg->stFdrMuteBkg.u32BkgA     << endl;
    cout << "[gfx_fdr] pstFdrCfg->stFdrMuteBkg.u32BkgY     = 0x" << hex << pstFdrCfg->stFdrMuteBkg.u32BkgY     << endl;
    cout << "[gfx_fdr] pstFdrCfg->stFdrMuteBkg.u32BkgU     = 0x" << hex << pstFdrCfg->stFdrMuteBkg.u32BkgU     << endl;
    cout << "[gfx_fdr] pstFdrCfg->stFdrMuteBkg.u32BkgV     = 0x" << hex << pstFdrCfg->stFdrMuteBkg.u32BkgV     << endl;

    cout << "[gfx_fdr] pstFdrCfg->enCmpType                = 0x" << hex << pstFdrCfg->enCmpType                << endl;
    cout << "[gfx_fdr] pstFdrCfg->stDcmpSegCfg.bAddrMapEn  = 0x" << hex << pstFdrCfg->stDcmpSegCfg.bAddrMapEn  << endl;

    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.bPatternEn  = 0x" << hex << pstFdrCfg->stPatternCfg.bPatternEn  << endl;
    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.enDemoMode  = 0x" << hex << pstFdrCfg->stPatternCfg.enDemoMode  << endl;
    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.enColorMode = 0x" << hex << pstFdrCfg->stPatternCfg.enColorMode << endl;
    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.enLineWidth = 0x" << hex << pstFdrCfg->stPatternCfg.enLineWidth << endl;
    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.u32Speed    = 0x" << hex << pstFdrCfg->stPatternCfg.u32Speed    << endl;
    cout << "[gfx_fdr] pstFdrCfg->stPatternCfg.u32Seed     = 0x" << hex << pstFdrCfg->stPatternCfg.u32Seed     << endl;

    cout << "[gfx_fdr] pstFdrCfg->bOflMaster               = 0x" << hex << pstFdrCfg->bOflMaster               << endl;
    cout << "[gfx_fdr] pstFdrCfg->enReqLen                 = 0x" << hex << pstFdrCfg->enReqLen                 << endl;
    cout << "[gfx_fdr] pstFdrCfg->enReqCtrl                = 0x" << hex << pstFdrCfg->enReqCtrl                << endl;

    cout << "[gfx_fdr] pstFdrCfg->bSmmuEn                  = 0x" << hex << pstFdrCfg->bSmmuEn                  << endl;
    cout << "[gfx_fdr] pstFdrCfg->bChkSumEn                = 0x" << hex << pstFdrCfg->bChkSumEn                << endl;
    cout << "[gfx_fdr] pstFdrCfg->bCkGtEn                  = 0x" << hex << pstFdrCfg->bCkGtEn                  << endl;
    cout << "[gfx_fdr] pstFdrCfg->bAlphaLayerEn            = 0x" << hex << pstFdrCfg->bAlphaLayerEn            << endl;
    cout << "[gfx_fdr] pstFdrCfg->bPortMode                = 0x" << hex << pstFdrCfg->bPortMode                << endl;
    cout << "[gfx_fdr] pstFdrCfg->bLatencyClr              = 0x" << hex << pstFdrCfg->bLatencyClr              << endl;
#endif
    //---------------------------
    //Initial Tmp Parameter Addr
    //---------------------------

	//VDP_FDR_GFX_SetSinglePortMode (u32RealOffset, pstFdrCfg->bPortMode);
	VDP_FDR_GFX_SetFlipEn         (u32RealOffset, pstFdrCfg->bFlipEn);
	VDP_FDR_GFX_SetBitext         (u32RealOffset, pstFdrCfg->enBitextMode);
	VDP_FDR_GFX_SetIfmt           (u32RealOffset, pstFdrCfg->enInFmt);
	VDP_FDR_GFX_SetDispMode       (u32RealOffset, pstFdrCfg->enSrc3dMode);
	VDP_FDR_GFX_SetRmode3d        (u32RealOffset, pstFdrCfg->enRMode3d  );
	VDP_FDR_GFX_SetDrawMode       (u32RealOffset, pstFdrCfg->enDrawMode);
	VDP_FDR_GFX_SetReadMode       (u32RealOffset, pstFdrCfg->enReadMode);

	VDP_FDR_GFX_SetPremultiEn     (u32RealOffset, pstFdrCfg->bPreMultEn);
	VDP_FDR_GFX_SetPalphaEn       (u32RealOffset, pstFdrCfg->bPalphaEn);
	VDP_FDR_GFX_SetPalphaRange    (u32RealOffset, pstFdrCfg->bPalphaRangeIsFull);
	VDP_FDR_GFX_SetAlpha1         (u32RealOffset, pstFdrCfg->u32Alpha1);
	VDP_FDR_GFX_SetAlpha0         (u32RealOffset, pstFdrCfg->u32Alpha0);

	VDP_FDR_GFX_SetMuteReqEn      (u32RealOffset, pstFdrCfg->bFdrMuteReqEn);
	VDP_FDR_GFX_SetMuteEn         (u32RealOffset, pstFdrCfg->bFdrMuteEn);
	VDP_FDR_GFX_SetMuteAlpha      (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgA);
	VDP_FDR_GFX_SetMuteY          (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgY);
	VDP_FDR_GFX_SetMuteCb         (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgU);
	VDP_FDR_GFX_SetMuteCr         (u32RealOffset, pstFdrCfg->stFdrMuteBkg.u32BkgV);

	VDP_FDR_GFX_SetKeyEn          (u32RealOffset, pstFdrCfg->bCkeyEn);
	VDP_FDR_GFX_SetKeyMode        (u32RealOffset, pstFdrCfg->stCkeyCfg.bKeyMode);
	VDP_FDR_GFX_SetKeyRMin        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_r_min);
	VDP_FDR_GFX_SetKeyGMin        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_g_min);
	VDP_FDR_GFX_SetKeyBMin        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_b_min);
	VDP_FDR_GFX_SetKeyRMax        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_r_max);
	VDP_FDR_GFX_SetKeyGMax        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_g_max);
	VDP_FDR_GFX_SetKeyBMax        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_b_max);
	VDP_FDR_GFX_SetKeyRMsk        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_r_msk);
	VDP_FDR_GFX_SetKeyGMsk        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_g_msk);
	VDP_FDR_GFX_SetKeyBMsk        (u32RealOffset, pstFdrCfg->stCkeyCfg.u32Key_b_msk);


	VDP_FDR_GFX_SetOflMaster      (u32RealOffset, pstFdrCfg->bOflMaster);
	VDP_FDR_GFX_SetReqLen         (u32RealOffset, pstFdrCfg->enReqLen);
	VDP_FDR_GFX_SetReqCtrl        (u32RealOffset, pstFdrCfg->enReqCtrl);
    #if MMU_TEST
	VDP_FDR_GFX_SetSmmuBypass3d   (u32RealOffset, 0      );
	VDP_FDR_GFX_SetSmmuBypass2d   (u32RealOffset, 0      );
	VDP_FDR_GFX_SetSmmuBypassH3d  (u32RealOffset, 0      );
	VDP_FDR_GFX_SetSmmuBypassH2d  (u32RealOffset, 0      );
    #else
	VDP_FDR_GFX_SetSmmuBypass3d   (u32RealOffset, 1      );
	VDP_FDR_GFX_SetSmmuBypass2d   (u32RealOffset, 1      );
	VDP_FDR_GFX_SetSmmuBypassH3d  (u32RealOffset, 1      );
	VDP_FDR_GFX_SetSmmuBypassH2d  (u32RealOffset, 1      );
    #endif
    VDP_FDR_GFX_SetChecksumEn	  (u32RealOffset, pstFdrCfg->bChkSumEn	 ) ;
    VDP_FDR_GFX_SetFdrCkGtEn	  (u32RealOffset, pstFdrCfg->bCkGtEn	 ) ;

	VDP_FDR_GFX_SetGfxAddrL       (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA   ].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetGfxNaddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetDcmpAddrL      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP   ].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetDcmpNaddrL     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2  ].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetHAddrL         (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD   ].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetH2AddrL        (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2  ].u64Addr      ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetGfxAddrH       (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA   ].u64Addr >>32 ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetGfxNaddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D].u64Addr >>32 ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetDcmpAddrH      (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP   ].u64Addr >>32 ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetDcmpNaddrH     (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2  ].u64Addr >>32 ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetHAddrH         (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD   ].u64Addr >>32 ) & 0xffffffff)) ;
	VDP_FDR_GFX_SetH2AddrH        (u32RealOffset, ((pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2  ].u64Addr >>32 ) & 0xffffffff)) ;

	VDP_FDR_GFX_SetSurfaceStride  (u32RealOffset, pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA ].u32Str);
	VDP_FDR_GFX_SetDcmpStride     (u32RealOffset, pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP ].u32Str);
	VDP_FDR_GFX_SetHeadStride     (u32RealOffset, pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD ].u32Str);
	VDP_FDR_GFX_SetHead2Stride    (u32RealOffset, pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD2].u32Str);

	VDP_FDR_GFX_SetIresoH         (u32RealOffset,(pstFdrCfg->stInRect.u32Hgt-1));
	VDP_FDR_GFX_SetIresoW         (u32RealOffset,(pstFdrCfg->stInRect.u32Wth-1));
    VDP_FDR_GFX_SetSrcCropX       (u32RealOffset, pstFdrCfg->stInRect.u32X);
    VDP_FDR_GFX_SetSrcCropY       (u32RealOffset, pstFdrCfg->stInRect.u32Y);
    VDP_FDR_GFX_SetSrcW           (u32RealOffset, pstFdrCfg->stSrcRect.u32Wth - 1 );
    VDP_FDR_GFX_SetSrcH           (u32RealOffset, pstFdrCfg->stSrcRect.u32Hgt - 1 );

	VDP_FDR_GFX_SetTestpatternEn  (u32RealOffset, pstFdrCfg->stPatternCfg.bPatternEn);
	VDP_FDR_GFX_SetTpMode         (u32RealOffset, pstFdrCfg->stPatternCfg.enDemoMode);
	VDP_FDR_GFX_SetTpColorMode    (u32RealOffset, pstFdrCfg->stPatternCfg.enColorMode);
	VDP_FDR_GFX_SetTpLineW        (u32RealOffset, pstFdrCfg->stPatternCfg.enLineWidth);
	VDP_FDR_GFX_SetTpSpeed        (u32RealOffset, pstFdrCfg->stPatternCfg.u32Speed);
	VDP_FDR_GFX_SetTpSeed         (u32RealOffset, pstFdrCfg->stPatternCfg.u32Seed);

	//VDP_FDR_GFX_SetLatencyClr   (u32RealOffset, pstFdrCfg->bLatencyClr);

	//press
	VDP_FDR_GFX_SetFdrPressEn	  (u32RealOffset, pstFdrCfg->stPressCfg.bPressEn          );
	VDP_FDR_GFX_SetScopeDrdyNum   (u32RealOffset, pstFdrCfg->stPressCfg.u32ScopeDrdyNum   );
	VDP_FDR_GFX_SetMinDrdyNum     (u32RealOffset, pstFdrCfg->stPressCfg.u32MinDrdyNum     );
	VDP_FDR_GFX_SetScopeNodrdyNum (u32RealOffset, pstFdrCfg->stPressCfg.u32ScopeNoDrdyNum );
	VDP_FDR_GFX_SetMinNodrdyNum   (u32RealOffset, pstFdrCfg->stPressCfg.u32MinNoDrdyNum   );

    //dcmp
	VDP_FDR_GFX_SetDcmpType       (u32RealOffset, pstFdrCfg->enCmpType);
	VDP_FDR_GFX_SetAddrMapEn      (u32RealOffset, pstFdrCfg->stDcmpSegCfg.bAddrMapEn  );
    VDP_FDR_GFX_SetTyp            (u32RealOffset, 0);

    //---------------------------
    // gfx alpha
    //---------------------------
    if(pstFdrCfg->bAlphaLayerEn == HI_TRUE)
    {
        VDP_ASSERT(enLayer == 2);

        VDP_ASSERT((pstFdrCfg->stSrcRect.u32Wth% 2) == 0);
        VDP_ASSERT((pstFdrCfg->stInRect.u32Wth% 2)  == 0);
        VDP_ASSERT((pstFdrCfg->stInRect.u32X% 2)    == 0);
        //VDP_ASSERT((pstFdrCfg->stSrcRect.u32Hgt% 2) == 0);
        //VDP_ASSERT((pstFdrCfg->stInRect.u32Hgt% 2)  == 0);
        //VDP_ASSERT((pstFdrCfg->stInRect.u32Y% 2)    == 0);
    }

    //---------------------------
    //Assertion
    //---------------------------
#if 0
    VDP_ASSERT( pstFdrCfg->stInRect.u32Wth >= 32 );
    VDP_ASSERT( pstFdrCfg->stInRect.u32Hgt >= 8  );
    // VDP_ASSERT((pstFdrCfg->stInRect.u32Hgt% 2) == 0  );
    // VDP_ASSERT((pstFdrCfg->stInRect.u32Wth% 2) == 0  );

    VDP_ASSERT( pstFdrCfg->stSrcRect.u32Hgt >= (pstFdrCfg->stInRect.u32Hgt + pstFdrCfg->stInRect.u32Y));
    VDP_ASSERT( pstFdrCfg->stSrcRect.u32Wth >= (pstFdrCfg->stInRect.u32Wth + pstFdrCfg->stInRect.u32X));

    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA    ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP    ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DCMP2   ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD    ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u32Str < 0x1000);
    VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u32Str < 0x1000);

    if(pstFdrCfg->enCmpType == XDP_CMP_TYPE_SEG)
    {
        VDP_ASSERT(pstFdrCfg->enInFmt==VDP_GFX_IFMT_ARGB_8888);
    }

#if 0
    if(pstFdrCfg->bSmmuEn == HI_TRUE)
    {
        if(VDP_LAYER_GFX0 == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA   ].u32Str <= (4096*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D].u32Str <= (4096*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD   ].u32Str <= (4096*32/8)/16);
        }
        else if(VDP_LAYER_GFX1 == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA   ].u32Str <= (4096*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D].u32Str <= (4096*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD   ].u32Str <= (4096*32/8)/16);
        }
        else if(VDP_LAYER_GFX3 == enLayer)
        {
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA   ].u32Str <= (4096*32/8)/16);//(1920*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_DATA_3D].u32Str <= (4096*32/8)/16);//(1920*32/8)/16);
            VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_HEAD   ].u32Str <= (4096*32/8)/16);//(1920*32/8)/16);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA   ].u32Str <= (1920/8)/16);
            //VDP_ASSERT( pstFdrCfg->stAddr[VDP_GFX_ADDR_ALPHA_3D].u32Str <= (1920/8)/16);
        }
    }
#endif

#endif
    return;
}

