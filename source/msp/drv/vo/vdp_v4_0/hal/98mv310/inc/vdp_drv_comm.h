#ifndef __DRV_COMM_H__
#define __DRV_COMM_H__

#include "vdp_define.h"
#include "vdp_hal_comm.h"
#include "vdp_hal_ip_para.h"

//----------------------------------------------------------------------
// address distrubite
//----------------------------------------------------------------------
#define  VDP_ALL_COEF_SIZE        0x100000
#define  VDP_HAL_CFG_SIZE         0x100
#define  COEF_SIZE_ZMEH           4096
#define  COEF_SIZE_ZMEV           4096
#define  COEF_SIZE_ZME2H          4096
#define  COEF_SIZE_ZME2V          4096

#define  COEF_SIZE_ZME_TMP        4096
#define  COEF_SIZE_GPZMEH         4096
#define  COEF_SIZE_GPZMEV         4096
#define  COEF_SIZE_GPZME_TMP      4096

#define  COEF_SIZE_WBC_ZMEH       4096
#define  COEF_SIZE_WBC_ZMEV       4096

#define  COEF_SIZE_HIHDR          4096
#define  COEF_SIZE_SHARP          4096
#define  COEF_SIZE_GP0ZME         4096
#define  COEF_SIZE_WBC_HZME       4096
#define  COEF_SIZE_WBC_VZME       4096
#define  COEF_SIZE_GFXCLUT        4096
#define  COEF_SIZE_GFXCLUT2       4096
#define  COEF_SIZE_MRGCFG         4096

typedef struct hiVDP_MMZ_BUFFER_S
{
	HI_U8* pu8StartVirAddr;
	HI_U32 u32StartPhyAddr;
	HI_U32 u32Size;
}VDP_MMZ_BUFFER_S;

typedef enum
{
    VDP_COEF_BUF_ZME1HLUM   = 0,
    VDP_COEF_BUF_ZME1VLUM   ,
    VDP_COEF_BUF_ZME1HCHM   ,
    VDP_COEF_BUF_ZME1VCHM   ,
    VDP_COEF_BUF_SHARP      ,
    VDP_COEF_BUF_ZME2HLUM   ,
    VDP_COEF_BUF_ZME2VLUM   ,
    VDP_COEF_BUF_ZME2HCHM   ,
    VDP_COEF_BUF_ZME2VCHM   ,

    VDP_COEF_BUF_HIHDR_V_D  ,
    VDP_COEF_BUF_HIHDR_V_S  ,
    VDP_COEF_BUF_WBC_HZME   ,
    VDP_COEF_BUF_WBC_VZME   ,
    VDP_COEF_BUF_HIHDR_G_TMP,
    VDP_COEF_BUF_HIHDR_G_GMM,
    VDP_COEF_BUF_GP0ZME     ,
    VDP_COEF_BUF_GFXCLUT    ,
    VDP_COEF_BUF_GFXCLUT2   ,
    VDP_COEF_BUF_MRGCFG     ,


    VDP_COEF_BUF_ZMEH       ,
    VDP_COEF_BUF_ZMEV       ,
    VDP_COEF_BUF_ZME_TMP    ,
    VDP_COEF_BUF_ZME2_TMP   ,
    VDP_COEF_BUF_ZME2H      ,
    VDP_COEF_BUF_ZME2V      ,
    VDP_COEF_BUF_GPZMEH     ,
    VDP_COEF_BUF_GPZMEV     ,
	VDP_COEF_BUF_GPZME_TMP  ,

    VDP_COEF_BUF_BUTT       ,

}VDP_COEF_BUF_E;

typedef struct hiVDP_COEF_ADDR_S
{
	VDP_MMZ_BUFFER_S 		stBufBaseAddr   ;
    HI_U32                  u32size         ;

    HI_U8                  *pu8CoefVirAddr[VDP_COEF_BUF_BUTT]     ;
    HI_U32                 u32CoefPhyAddr[VDP_COEF_BUF_BUTT]     ;
}VDP_COEF_ADDR_S;

typedef struct
{
    // Vid Layer
    HI_U64 u64VidLumDataAddr[VID_MAX];
    HI_U64 u64VidChmDataAddr[VID_MAX];
    HI_U64 u64VidLumHeadAddr[VID_MAX];
    HI_U64 u64VidChmHeadAddr[VID_MAX];
    HI_U64 u64VidLum2BitAddr[VID_MAX];
    HI_U64 u64VidChm2BitAddr[VID_MAX];
    HI_U64 u64VidLumTileAddr[VID_MAX];
    HI_U64 u64VidChmTileAddr[VID_MAX];
    HI_U32 u32VidLumDataStr [VID_MAX];
    HI_U32 u32VidChmDataStr [VID_MAX];
    HI_U32 u32VidLumHeadStr [VID_MAX];
    HI_U32 u32VidChmHeadStr [VID_MAX];
    HI_U32 u32VidLum2BitStr [VID_MAX];
    HI_U32 u32VidChm2BitStr [VID_MAX];
    HI_U32 u32VidLumTileStr [VID_MAX];
    HI_U32 u32VidChmTileStr [VID_MAX];
    // Gfx Layer
    HI_U64 u64GfxDataAddr [GFX_MAX];
    HI_U64 u64GfxDcmpAddr [GFX_MAX];
    HI_U64 u64GfxHeadAddr [GFX_MAX];
    HI_U64 u64GfxAlphaAddr[GFX_MAX];
    HI_U32 u32GfxDataStr  [GFX_MAX];
    HI_U32 u32GfxDcmpStr  [GFX_MAX];
    HI_U32 u32GfxHeadStr  [GFX_MAX];
    HI_U32 u32GfxAlphaStr [GFX_MAX];
    // Wbc Layer
    HI_U64 u64WbcLumDataAddr[WBC_MAX];
    HI_U64 u64WbcChmDataAddr[WBC_MAX];
    HI_U64 u64WbcLumHeadAddr[WBC_MAX];
    HI_U64 u64WbcChmHeadAddr[WBC_MAX];
    HI_U32 u32WbcLumDataStr [WBC_MAX];
    HI_U32 u32WbcChmDataStr [WBC_MAX];
    HI_U32 u32WbcLumHeadStr [WBC_MAX];
    HI_U32 u32WbcChmHeadStr [WBC_MAX];
    // Para
    HI_U64 u64ParaAddr[PARA_MAX];
    // Od/Cmp/Dcmp
   	HI_U64 u64OdCmpAddr [2];
   	HI_U64 u64OdDcmpAddr[1];
   	HI_U64 u64SttAddr [2];

    // v0fi wchn addr
    XDP_TRIO_ADDR_S stWchnAddr[VDP_WCHN_MAX];

   	HI_U64 u64AddrEnd;

}VDP_ADDR_CFG_S;

extern VDP_ADDR_CFG_S  gstVdpAddrCfg;

//-------------------------------------------------------------------
// function
//-------------------------------------------------------------------
HI_S32 VDP_DRV_AllocateMem(HI_U32 u32Size,VDP_MMZ_BUFFER_S *stVdpMmzBuffer);
HI_S32 VDP_DRV_DeleteMem(VDP_MMZ_BUFFER_S* stVdpMmzBuffer);
HI_S32 VDP_DRV_AllocateCfgMem(HI_U32 u32Size, VDP_MMZ_BUFFER_S* stVdpCfgBuffer);
HI_S32 VDP_DRV_DeleteCfgMem(VDP_MMZ_BUFFER_S* stVdpCfgBuffer);

HI_S32 VDP_DRV_CoefBufAddrDistribute(VDP_COEF_ADDR_S *stVdpCoefBufAddr);

HI_S32 VDP_DRV_IoRemap(HI_U32 u32Phy, HI_U32 u32Size,HI_U32 **pu32VirtualAddr);
HI_S32 VDP_DRV_IoUnmap(HI_U32 **pu32VirtualAddr);

#endif//__DRV_COMM_H__
