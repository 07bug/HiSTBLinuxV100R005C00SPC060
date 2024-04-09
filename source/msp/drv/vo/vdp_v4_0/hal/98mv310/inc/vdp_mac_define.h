#ifndef _VDP_MAC_DEFINE_H_
#define _VDP_MAC_DEFINE_H_
#include "vdp_ip_define.h"

/****************************************************************/
// LAYER NAME USE IN FUNC
/****************************************************************/
/*
typedef enum
{
    VDP_MAC_RCHN_PARA_CORE =0,
    VDP_MAC_RCHN_PARA_SUB    ,
    VDP_MAC_RCHN_V0          ,
    VDP_MAC_RCHN_V1          ,
    VDP_MAC_RCHN_G0          ,
    VDP_MAC_RCHN_G1          ,
    VDP_MAC_RCHN_G3          ,
    VDP_MAC_RCHN_OD_DCMP     ,
    VDP_MAC_RCHN_PARA_OD     ,
    VDP_MAC_RCHN_PARA_DEMURA ,
    VDP_MAC_RCHN_BUTT
}VDP_MAC_RCHN_E;

typedef enum
{
    VDP_MAC_V0F_RCHN_PARA_CORE =0,
    VDP_MAC_V0F_RCHN_PARA_SUB    ,
    VDP_MAC_V0F_RCHN_V0          ,
    VDP_MAC_V0F_RCHN_V1          ,
    VDP_MAC_V0F_RCHN_G0          ,
    VDP_MAC_V0F_RCHN_G1          ,
    VDP_MAC_V0F_RCHN_G3          ,
    VDP_MAC_V0F_RCHN_OD_DCMP     ,
    VDP_MAC_V0F_RCHN_PARA_OD     ,
    VDP_MAC_V0F_RCHN_PARA_DEMURA ,
    VDP_MAC_V0F_RCHN_BUTT
}VDP_MAC_V0F_RCHN_E;
*/

typedef enum
{
    VDP_MAC_WCHN_WBC0 = 0,
    VDP_MAC_WCHN_WBC1 ,
    VDP_MAC_WCHN_WBC2 ,

    VDP_MAC_WCHN_BUTT
} VDP_MAC_WCHN_E;


/****************************************************************/
// LAYER CONT
/****************************************************************/
#define VDP_RCHN_MAX ((HI_U32)(VDP_MAC_RCHN_BUTT))
#define VDP_WCHN_MAX ((HI_U32)(VDP_MAC_WCHN_BUTT))
#define VDP_STT_MAX  1

extern const HI_U32 gu32VdpVfdrAddr  [VDP_LAYER_VID_BUTT];
extern const HI_U32 gu32VdpVfdrMaxWth[VDP_LAYER_VID_BUTT];
extern const HI_U32 gu32VdpVfdrMaxHgt[VDP_LAYER_VID_BUTT];

extern const HI_U32 gu32VdpGfdrAddr  [VDP_LAYER_GFX_BUTT];
extern const HI_U32 gu32VdpGfdrMaxWth[VDP_LAYER_GFX_BUTT];
extern const HI_U32 gu32VdpGfdrMaxHgt[VDP_LAYER_GFX_BUTT];

extern const HI_U32 gu32VdpWchnAddr  [VDP_WCHN_MAX];
extern const HI_U32 gu32VdpWchnMaxWth[VDP_WCHN_MAX];
extern const HI_U32 gu32VdpWchnMaxHgt[VDP_WCHN_MAX];

extern const HI_U32 gu32VdpCapMaxWth[1];
extern const HI_U32 gu32VdpCapMaxHgt[1];

#define VDP_VFDR_START_OFFSET  (gu32VdpVfdrAddr[VDP_LAYER_VID0])
#define VDP_GFDR_START_OFFSET  (gu32VdpGfdrAddr[VDP_LAYER_GFX0])
// #define VDP_RCHN_IMG_START_OFFSET  (gu32VdpRchnAddr[VDP_MAC_RCHN_BUTT])
#define VDP_WCHN_IMG_START_OFFSET  (gu32VdpWchnAddr[VDP_MAC_WCHN_WBC0])


#if 0
/* Define the union U_VDP_BASE_RD_IMG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    format               : 4   ; /* [3..0]  */
        unsigned int    type                 : 4   ; /* [7..4]  */
        unsigned int    order                : 4   ; /* [11..8]  */
        unsigned int    bitw                 : 4   ; /* [15..12]  */
        unsigned int    dcmp_mode            : 4   ; /* [19..16]  */
        unsigned int    uv_invert            : 1   ; /* [20]  */
        unsigned int    mirror               : 1   ; /* [21]  */
        unsigned int    flip                 : 1   ; /* [22]  */
        unsigned int    lm_rmode             : 3   ; /* [25..23]  */
        unsigned int    b_bypass             : 1   ; /* [26]  */
        unsigned int    h_bypass             : 1   ; /* [27]  */
        unsigned int    d_bypass             : 1   ; /* [28]  */
        unsigned int    mute_en              : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VDP_BASE_RD_IMG_CTRL;

/* Define the union U_VDP_BASE_WR_IMG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    format               : 4   ; /* [3..0]  */
        unsigned int    type                 : 4   ; /* [7..4]  */
        unsigned int    bitw                 : 4   ; /* [11..8]  */
        unsigned int    cmp_mode             : 4   ; /* [15..12]  */
        unsigned int    uv_invert            : 1   ; /* [16]  */
        unsigned int    mirror               : 1   ; /* [17]  */
        unsigned int    flip                 : 1   ; /* [18]  */
        unsigned int    dither_en            : 1   ; /* [19]  */
        unsigned int    dither_mode          : 1   ; /* [20]  */
        unsigned int    reserved_1           : 2   ; /* [22..21]  */
        unsigned int    lm_rmode             : 3   ; /* [25..23]  */
        unsigned int    reserved_2           : 2   ; /* [27..26]  */
        unsigned int    h_bypass             : 1   ; /* [28]  */
        unsigned int    d_bypass             : 1   ; /* [29]  */
        unsigned int    tunl_en              : 1   ; /* [30]  */
        unsigned int    en                   : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VDP_BASE_WR_IMG_CTRL;
#endif

/****************************************************************/
// Function
/****************************************************************/
//HI_VOID VdpGetRchnLayerName (VDP_MAC_RCHN_E enLayer, HI_CHAR * cChnName);
//HI_VOID VdpGetWchnLayerName (VDP_MAC_WCHN_E enLayer, HI_CHAR * cChnName);

/****************************************************************/
// MULTI REGION DEFINE
/****************************************************************/
#define MAX_REGION_NUM 4
#define V0_REGION_NUM  0
#define V1_REGION_NUM  4
#define REGION_OFFSET  0x30

typedef struct
{
    HI_U64 u64Addr;
    HI_U32 u32Str ;
} VDP_MRG_ADDR_S;

typedef enum
{
	VDP_REGION_ADDR_DATA_LUM = 0,
	VDP_REGION_ADDR_DATA_CHM    ,
	VDP_REGION_ADDR_HEAD_LUM    ,
	VDP_REGION_ADDR_HEAD_CHM    ,
	VDP_REGION_ADDR_BUTT
}VDP_REGION_ADDR_E;

typedef enum
{
	VDP_REGION_COLOR_MODE_FORE = 0,
	VDP_REGION_COLOR_MODE_BACK   ,
	VDP_REGION_COLOR_MODE_BUTT
}VDP_REGION_EDGE_COLOR_MODE_E;

typedef enum
{
	VDP_REGION_MUTE_MODE_SHOW = 0,
	VDP_REGION_MUTE_MODE_NOSHOW  ,
	VDP_REGION_MUTE_MODE_BUTT
}VDP_REGION_MUTE_MODE_E;

typedef struct
{
    HI_BOOL     bRegionEn ;
    HI_BOOL     bMuteEn   ;
    HI_BOOL     bMmuBypass;
    HI_BOOL     bCropEn   ;
    HI_BOOL     bEdgeEn   ;
    VDP_REGION_EDGE_COLOR_MODE_E enEdgeColorType;
    VDP_RECT_S  stDispReso;
    VDP_RECT_S  stSrcReso ;
    VDP_RECT_S  stInReso  ;
    VDP_MRG_ADDR_S  stAddr[VDP_REGION_ADDR_BUTT] ;
}VDP_REGION_INFO_S;

#endif

