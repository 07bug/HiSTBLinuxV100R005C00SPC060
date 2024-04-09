#include "hi_type.h"
#include "vdp_define.h"
#include "vdp_mac_define.h"
#include "vdp_drv_comm.h"


//--------------------------------------------
// channel register offset
//--------------------------------------------
const HI_U32 gu32VdpVfdrAddr[VDP_LAYER_VID_BUTT] = 
{
    (0x0000),   // vid0
    (0x0200),   // vid1
    (0x0400)    // el
};

const HI_U32 gu32VdpGfdrAddr[VDP_LAYER_GFX_BUTT] = 
{
    (0x000),   // gfx0
    (0x200),   // gfx1
    (0x400),   // gfx3
    (0x600)    // ga
};

const HI_U32 gu32VdpWchnAddr[VDP_WCHN_MAX] = 
{
    (0x00),   // wbc0
    (0x40),   // wbc1
    (0x80)    // wbc2
};

//--------------------------------------------
// channel max reso
//--------------------------------------------
const HI_U32 gu32VdpVfdrMaxWth[VDP_LAYER_VID_BUTT] = 
{
    8192,   // vid0
    4096,   // el
    4096    // vid1
};

const HI_U32 gu32VdpVfdrMaxHgt[VDP_LAYER_VID_BUTT] = 
{
    4320,   // vid0
    2160,   // el
    2160    // vid1
};

const HI_U32 gu32VdpGfdrMaxWth[VDP_LAYER_GFX_BUTT] = 
{
    4096,   // gfx0
    4096,   // gfx1
    4096,   // gfx2
    4096    // ga  
};

const HI_U32 gu32VdpGfdrMaxHgt[VDP_LAYER_GFX_BUTT] = 
{
    2160,   // gfx0
    2160,   // gfx1
    2160,   // gfx2
    2160    // ga  
};

const HI_U32 gu32VdpWchnMaxWth[VDP_WCHN_MAX] = 
{
    3840,   // wbc0
    1920,   // wbc1
     960    // wbc2
};

const HI_U32 gu32VdpWchnMaxHgt[VDP_WCHN_MAX] = 
{
    2160,   // wbc0    
    1080,   // wbc1           
     540    // wbc2           
};

const HI_U32 gu32VdpCapMaxWth[1] = 
{
    4096,   // wbc_dhd0
};

const HI_U32 gu32VdpCapMaxHgt[1] = 
{
    2160,   // wbc_dhd0
};

//--------------------------------------------
// channel name
//--------------------------------------------
//HI_VOID VdpGetRchnLayerName(VDP_MAC_RCHN_E enLayer, HI_CHAR * cChnName)
//{
//	switch(enLayer)
//	{
//		default : strcpy(cChnName , "no_name" );
//	}
//    return;
//}
//
//HI_VOID VdpGetWchnLayerName(VDP_MAC_WCHN_E enLayer, HI_CHAR * cChnName)
//{
//	switch(enLayer)
//	{
//		case VDP_MAC_WCHN_WBC0       : strcpy(cChnName , "wchn_wbc0"     ); break ;
//		case VDP_MAC_WCHN_WBC1       : strcpy(cChnName , "wchn_wbc1"     ); break ;
//		case VDP_MAC_WCHN_WBC2       : strcpy(cChnName , "wchn_wbc2"     ); break ;
//        default:break;
//		//default : strcpy(cChnName , "no_name" );
//	}
//    return;
//}


