#ifndef __VDP_FUNC_IP_FDR_H__
#define __VDP_FUNC_IP_FDR_H__

#include "ice_define.h"
#include "vdp_mac_define.h"
#include "vdp_drv_comm.h"
#include "vdp_hal_ip_region.h"
#include "vdp_hal_ip_fdr.h"


typedef enum
{
    VDP_FDR_CFG_MODE_TYP,
    VDP_FDR_CFG_MODE_CFG,
    VDP_FDR_CFG_MODE_RAND,

    VDP_FDR_CFG_MODE_BUTT
}VDP_FDR_CFG_MODE_E;

typedef struct
{
	HI_U64 u64LumAddr;
	HI_U64 u64ChmAddr;

	HI_U32 u32LumStr;
	HI_U32 u32ChmStr;
}VDP_VID_ADDR_S;

typedef enum
{
	VDP_VID_ADDR_DATA = 0,//2d left eye data
	VDP_VID_ADDR_DATA_3D ,//3d right eye data
	VDP_VID_ADDR_HEAD    ,//dcmp head data
	VDP_VID_ADDR_2B      ,//2bit
	VDP_VID_ADDR_TILE_8B ,//tile 8bit
	VDP_VID_ADDR_BUTT
}VDP_VID_ADDR_E;


typedef struct
{
	HI_U64 u64Addr;
	HI_U32 u32Str;
}VDP_GFX_ADDR_S;

typedef enum
{
	VDP_GFX_ADDR_DATA = 0,//2d left eye data
	VDP_GFX_ADDR_DATA_3D ,//3d right eye data
	VDP_GFX_ADDR_DCMP    ,//dcmp data
	VDP_GFX_ADDR_DCMP2   ,//dcmp data
	VDP_GFX_ADDR_HEAD    ,//dcmp head
	VDP_GFX_ADDR_HEAD2   ,//dcmp head
	VDP_GFX_ADDR_ALPHA   ,//alpha layer
	VDP_GFX_ADDR_ALPHA_3D,//alpha layer
	VDP_GFX_ADDR_BUTT
}VDP_GFX_ADDR_E;

typedef enum
{
    VDP_TESTPTTN_CLR_MODE_FIX = 0,
    VDP_TESTPTTN_CLR_MODE_NORM	 ,
    VDP_TESTPTTN_CLR_MODE_BUTT
}VDP_TESTPTTN_CLR_MODE_E;

typedef enum
{
    VDP_DCMP_SRC_MODE_ARGB8888 = 0 ,
    VDP_DCMP_SRC_MODE_ARGB1555     ,
    VDP_DCMP_SRC_MODE_ARGB4444     ,
    VDP_DCMP_SRC_MODE_RGB565       ,
    VDP_DCMP_SRC_MODE_RGB888       ,
    VDP_DCMP_SRC_MODE_YUV444       ,
    VDP_DCMP_SRC_MODE_BUTT
}VDP_DCMP_SRC_MODE_E;

typedef enum
{
    VDP_CMP_MODE_CMP = 0 ,
    VDP_CMP_MODE_RAW	 ,
    VDP_CMP_MODE_BUTT
}VDP_CMP_MODE_E    ;

typedef enum
{
    VDP_TESTPTTN_LINEW_1P = 0,
    VDP_TESTPTTN_LINEW_2P    ,
    VDP_TESTPTTN_LINEW_BUTT
}VDP_TESTPTTN_LINEW_E;


typedef struct
{
    HI_BOOL        bDcmpEn        ;
    HI_BOOL        bAddrMapEn     ;
}VDP_FDR_DCMP_SEG_CFG_S;

typedef struct
{
    HI_BOOL             bDcmpEn      ;
    HI_BOOL  			bIsRawEn     ;
    HI_BOOL  			bIsLossyY    ;
    HI_BOOL  			bIsLossyC    ;
    HI_U32   			u32CmpRatioY ;
    HI_U32   			u32CmpRatioC ;
    ICE_REG_CFG_MODE_E 	enCmpCfgMode ;
    ICE_FRM_PART_MODE_S stPartModeCfg;
    ICE_FRM_SLICE_MODE_S stSliceModeCfg;
}VDP_FDR_DCMP_FRM_CFG_S;

typedef struct
{
    HI_BOOL                 bPatternEn ;
    VDP_TESTPTTN_MODE_E     enDemoMode ;
    VDP_TESTPTTN_CLR_MODE_E enColorMode;
    VDP_TESTPTTN_LINEW_E    enLineWidth;
    HI_U32                  u32Speed   ; // Speed * 4pixel
    HI_U32                  u32Seed    ;
}VDP_PATTERN_CFG_S;

typedef enum
{
    VDP_LOWDLY_MODE_OFF = 0,
    VDP_LOWDLY_MODE_TUNL,
    VDP_LOWDLY_MODE_VDH ,
    VDP_LOWDLY_MODE_BUTT
}VDP_LOWDLY_MODE_E;

typedef struct
{
	VDP_LOWDLY_MODE_E	enLowdlyMode   ;
	HI_U64	u64TunlAddr ;
	HI_U32	u32Intervalx1024;
}VDP_RTUNL_CFG_S;

typedef struct
{
    HI_BOOL bPressEn ;

	HI_U32	u32ScopeDrdyNum   ;
	HI_U32	u32MinDrdyNum     ;

	HI_U32	u32ScopeNoDrdyNum ;
	HI_U32	u32MinNoDrdyNum   ;
}VDP_PRESS_CFG_S;

typedef struct
{
    //src info
    VDP_VID_ADDR_S          stAddr[VDP_VID_ADDR_BUTT] ;//every

    VDP_VID_IFMT_E          enInFmt                   ;//once
    VDP_DATA_WTH            enDataWidth               ;//once

    VDP_RECT_S              stSrcRect                 ;//once
    VDP_RECT_S              stInRect                  ;//once

    VDP_DISP_MODE_E         enSrc3dMode               ;//once
    VDP_RMODE_3D_E          enRMode3d                 ;//reserved

    HI_BOOL                 bSmmuEn                   ;//once
    HI_BOOL                 bChkSumEn         		  ;//once
    HI_BOOL                 bCkGtEn         		  ;//once

    VDP_DATA_RMODE_E        enReadMode                ;//once  //lm & chm
    HI_BOOL                 bChmCopyEn                ;//once  //

    //dcmp
    XDP_CMP_TYPE_E      	enCmpType    			  ;//once
    VDP_FDR_DCMP_SEG_CFG_S  stDcmpSegCfg              ;//once
    //
    //operation
    HI_BOOL                 bFlipEn                   ;//reserved
    HI_BOOL                 bUvOrder                  ;//once

    VDP_DRAW_MODE_E         enDrawMode                ;//once  //lm & chm
    VDP_DRAW_MODE_E         enDrawPixelMode           ;//once  //lm & chm

    //testpatten
    VDP_PATTERN_CFG_S       stPatternCfg              ;//once

    //fdr mute
    HI_BOOL                 bFdrMuteEn                ;//once
    HI_BOOL                 bFdrMuteReqEn             ;//once
    VDP_BKG_S               stFdrMuteBkg              ;//once //R,G,B

    //mac
    HI_BOOL                 bPreRdEn                  ;//once
    HI_BOOL                 bOflMaster                ;//reserved
    VDP_REQ_LENGTH_E        enReqLen                  ;//once
    VDP_REQ_CTRL_E          enReqCtrl                 ;//once

    //memory
    HI_BOOL                 bIsSinglePort             ;
    HI_BOOL                 bMemMode                  ;

	//tunl
	VDP_RTUNL_CFG_S         stTunlCfg                 ;

	//press
	VDP_PRESS_CFG_S         stPressCfg                ;

    // multi-region
    HI_BOOL bMultiRegionEn;
    HI_U32  u32RegionNum  ;
    HI_BOOL bConfigWholeLayer;
    VDP_REGION_MUTE_MODE_E  enMultiRegionMuteMode      ;
    VDP_REGION_INFO_S stRegionInfo[MAX_REGION_NUM];

}VDP_VID_FDR_CFG_S;


typedef struct
{
    HI_BOOL                 bDcmpEn           ;
    VDP_DCMP_SRC_MODE_E		enDcmpSrcMode     ;
    VDP_CMP_MODE_E    		enArgbCmpMode     ;
    HI_BOOL                 bCmpLostless      ;
    HI_BOOL                 bCmpLostlessA     ;
    HI_BOOL                 bTpredEn          ;

}VDP_OSD_DCMP_CFG_S;

typedef struct
{
    //src info
    VDP_GFX_ADDR_S          stAddr[VDP_GFX_ADDR_BUTT] ;

    VDP_GFX_IFMT_E          enInFmt               ;
    VDP_DATA_RMODE_E        enReadMode            ;
    VDP_RECT_S              stSrcRect             ;
    VDP_RECT_S              stInRect              ;
    VDP_DISP_MODE_E         enSrc3dMode           ;  //fdr in img mode
    VDP_RMODE_3D_E          enRMode3d             ;
    HI_BOOL                 bPreMultEn            ;

    //palpha
    HI_BOOL                 bPalphaEn             ;
    HI_BOOL                 bPalphaRangeIsFull    ; //0: 0~128, 1: 0~255

    //for 1555
    HI_U32                  u32Alpha0             ;
    HI_U32                  u32Alpha1             ;

    //read way

    HI_BOOL                 bFlipEn               ;
    VDP_DRAW_MODE_E         enDrawMode            ;

    //pixel value calc
    HI_BOOL                 bCkeyEn               ;
    VDP_GFX_CKEY_S          stCkeyCfg             ;
    VDP_GFX_BITEXTEND_E     enBitextMode          ;

    //fdr mute
    HI_BOOL                 bFdrMuteEn            ;
    HI_BOOL                 bFdrMuteReqEn         ;
    VDP_BKG_S               stFdrMuteBkg          ;//A,R,G,B

    //dcmp
    XDP_CMP_TYPE_E      	enCmpType    		  ;
    VDP_FDR_DCMP_SEG_CFG_S  stDcmpSegCfg          ;

    //testpatten
    VDP_PATTERN_CFG_S       stPatternCfg          ;

    //mac
    HI_BOOL                 bOflMaster            ;
    VDP_REQ_LENGTH_E        enReqLen              ;
    VDP_REQ_CTRL_E          enReqCtrl             ;

    //mmu
    HI_BOOL                 bSmmuEn      		  ;
    HI_BOOL                 bChkSumEn      		  ;
    HI_BOOL                 bCkGtEn         	  ;
    HI_BOOL                 bAlphaLayerEn         ;

    //memory
    HI_BOOL                 bPortMode			  ;

    //axi
    HI_BOOL                 bLatencyClr			  ;
	//press
	VDP_PRESS_CFG_S         stPressCfg                ;

}VDP_GFX_FDR_CFG_S;



//function declare
HI_VOID VDP_VID_InitFdrCfg(HI_U32 enLayer, VDP_FDR_CFG_MODE_E enCfgMode, VDP_VID_FDR_CFG_S* pstFdrCfg);
HI_VOID VDP_VID_SetFdrCfg(HI_U32 enLayer, VDP_VID_FDR_CFG_S* pstFdrCfg);

HI_VOID VDP_GFX_InitFdrCfg(HI_U32 enLayer, VDP_FDR_CFG_MODE_E enCfgMode, VDP_GFX_FDR_CFG_S* pstFdrCfg);
HI_VOID VDP_GFX_SetFdrCfg(HI_U32 enLayer, VDP_GFX_FDR_CFG_S* pstFdrCfg);


#endif

