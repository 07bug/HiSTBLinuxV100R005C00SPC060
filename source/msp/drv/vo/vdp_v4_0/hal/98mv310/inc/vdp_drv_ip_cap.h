#ifndef __VDP_DRV_IP_CAP_H__
#define __VDP_DRV_IP_CAP_H__

#include "hi_reg_common.h"
#include "ice_define.h"
#include "vdp_hal_ip_cap.h"
#include "vdp_drv_comm.h"

typedef struct
{
	HI_U64 u64LumAddr;
	HI_U64 u64ChmAddr;
	HI_U32 u32LumStr ;
	HI_U32 u32ChmStr ;
}VDP_CAP_ADDR_S;

typedef enum
{
	VDP_CAP_ADDR_DATA = 0,//2d left eye data
	VDP_CAP_ADDR_HEAD    ,//dcmp head data
	VDP_CAP_ADDR_DATA_3D ,//3d right eye data
	VDP_CAP_ADDR_BUTT
}VDP_CAP_ADDR_E;

typedef enum
{
	VDP_CAP_INT_MODE_FRAME = 0,
	VDP_CAP_INT_MODE_FIELD,
	VDP_CAP_INT_BUTT
}VDP_CAP_INT_MODE_E ;

typedef struct
{
	HI_BOOL bCmpEn       ;
	HI_U32	u32CmpRatio  ;
	HI_BOOL	bIsLossy     ;
	HI_BOOL	bEslEn       ;
	ICE_BIT_DEPTH_E	enBitDepth   ;
	ICE_DATA_FMT_E	enDataFmt    ;
	ICE_REG_CFG_MODE_E	enCmpCfgMode ;
}CMP_SEG_CFG_S;

typedef struct
{
	HI_BOOL	bTunlEn          ;
	HI_BOOL	bTestModeEn      ;
	HI_U64	u64TunlAddr      ;
	HI_U32	u32IntervalLine  ;
	HI_U32	u32PartFinishLine;
}VDP_WTUNL_CFG_S;

typedef struct
{
	//src info
	VDP_CAP_ADDR_S          stAddr[VDP_CAP_ADDR_BUTT] ;
	VDP_DATA_WTH            enDataWidth               ;
	VDP_RECT_S              stSrcRect                 ;
	HI_U64                  u64Finfo				  ;
	//bus
	VDP_REQ_LENGTH_E        enReqLen                  ;
	HI_U32                  u32Interval               ;
	HI_U32                  u32Wbc3dEn                ;
	//operation
	CMP_SEG_CFG_S           stCmpSegCfg                ;
	//operation
	HI_BOOL                 bFlipEn                   ; //reserved
	HI_BOOL                 bUvOrder                  ; //reserved
	//mmu
	HI_BOOL                 bSmmuEn                   ; //reserved
	HI_BOOL                 bChkSumEn                 ;
	//tunl
	VDP_WTUNL_CFG_S         stTunlCfg                 ;
}VDP_CAP_CFG_S;

HI_VOID VDP_WBC_InitCapCfg(HI_U32 enLayer, VDP_CAP_CFG_S* pstCapCfg);
HI_VOID VDP_WBC_SetCapCfg( HI_U32 enLayer, VDP_CAP_CFG_S* pstCapCfg);

#endif

