#ifndef __VDP_DRV_COEF_H__
#define __VDP_DRV_COEF_H__

#include "vdp_drv_comm.h"

typedef struct file FILE;

typedef struct
{
    HI_U32 data3;
    HI_U32 data2;
    HI_U32 data1;
    HI_U32 data0;
    HI_U32 depth;
}VDP_DRV_U128_S;


typedef enum tagVDP_DRV_COEF_DATA_TYPE
{
    DRV_COEF_DATA_TYPE_U8 = 0,
    DRV_COEF_DATA_TYPE_S8  ,
    DRV_COEF_DATA_TYPE_U16 ,
    DRV_COEF_DATA_TYPE_S16 ,
    DRV_COEF_DATA_TYPE_U32 ,
    DRV_COEF_DATA_TYPE_S32 ,
    DRV_COEF_DATA_TYPE_BUTT
} VDP_DRV_COEF_DATA_TYPE_E;

typedef enum tagSTI_FILE_TYPE_E
{
    STI_FILE_DATA_VID0 = 0 ,
    STI_FILE_DATA_VID1     ,
    STI_FILE_DATA_VID2     ,
    STI_FILE_DATA_VID3     ,
    STI_FILE_DATA_VID4     ,
    STI_FILE_DATA_GFX0     ,
    STI_FILE_DATA_GFX1     ,
    STI_FILE_DATA_GFX2     ,
    STI_FILE_DATA_GFX3     ,
    STI_FILE_DATA_GFX4     ,

    STI_FILE_COEF_ZME_V0   ,
    STI_FILE_COEF_ACM      ,
    STI_FILE_COEF_DCI      ,
    STI_FILE_COEF_DIM      ,
    STI_FILE_COEF_GMM      ,
    STI_FILE_COEF_SHARP    ,
    STI_FILE_COEF_OD       ,
    STI_FILE_COEF_RGBW     ,
    STI_FILE_COEF_DEMURA   ,
    STI_FILE_TYPE_NODEF    ,
    STI_FILE_TILE_64_CMP_Y ,
    STI_FILE_TILE_64_CMP_C ,
    STI_FILE_TILE_64_CMP_Y_2BIT,
    STI_FILE_TILE_64_CMP_C_2BIT,
    STI_FILE_TILE_64_CMP_Y_HEAD,
    STI_FILE_TILE_64_CMP_C_HEAD,
    STI_FILE_OSD_CMP            ,
    STI_FILE_OSD_CMP_AR_HEAD    ,
    STI_FILE_OSD_CMP_GB_HEAD    ,
    STI_FILE_OSD_CMP_AR         ,
    STI_FILE_OSD_CMP_GB         ,
    STI_FILE_COEF_BT2020_GAMM   ,
    STI_FILE_COEF_BT2020_DEGAMM ,
    STI_FILE_COEF_DM_GAMM       ,
    STI_FILE_COEF_DM_DEGAMM     ,
    STI_FILE_COEF_DM_CVM        ,
    STI_FILE_COEF_GDM_GAMM      ,
    STI_FILE_COEF_GDM_CVM      ,
    STI_FILE_COEF_GDM_DEGAMM    ,
    STI_FILE_COEF_METADATA      ,
    STI_FILE_COEF_VMX           ,
    STI_FILE_DATA_TNR_REF       ,
    STI_FILE_DATA_TNR_MAD       ,
    STI_FILE_DATA_VDH_DB        ,
    STI_FILE_COEF_VDM,
    STI_FILE_COEF_TCHDR,
    STI_FILE_COEF_G0ZME,
    STI_FILE_COEF_HIHDR_G,
    STI_FILE_COEF_HIHDR_V,
    STI_FILE_COEF_WDHZME,
    STI_FILE_COEF_VZME,
    STI_FILE_V0_REGION,
    STI_FILE_V1_REGION,
    STI_FILE_COEF_SHP,

    STI_FILE_TYPE_BUTT
} STI_FILE_TYPE_E;

typedef enum tagVDP_RM_COEF_MODE_E
{
    VDP_RM_COEF_MODE_TYP  = 0x0,
    VDP_RM_COEF_MODE_RAN  = 0x1,
    VDP_RM_COEF_MODE_MIN  = 0x2,
    VDP_RM_COEF_MODE_MAX  = 0x3,
    VDP_RM_COEF_MODE_ZRO  = 0x4,
    VDP_RM_COEF_MODE_CUS  = 0x5,
    VDP_RM_COEF_MODE_UP   = 0x6,
    VDP_RM_COEF_MODE_LBL_TYP = 0x7,
    VDP_RM_COEF_MODE_LBL_RAN = 0x8,
    VDP_RM_COEF_MODE_LBL_MIN = 0x9,
    VDP_RM_COEF_MODE_LBL_MAX = 0x10,
    VDP_RM_COEF_MODE_BUTT
} VDP_RM_COEF_MODE_E;

typedef struct
{
    HI_U8 *                     coef_addr       ;
    STI_FILE_TYPE_E             sti_type        ;
    FILE*                       fp_coef         ;
    HI_U32                      lut_num         ;
    HI_U32                      burst_num       ;
    HI_U32                      cycle_num       ;
    void   * *                  p_coef_array    ;
    HI_U32 *                    lut_length      ;
    HI_U32 *                    coef_bit_length ;
    VDP_DRV_COEF_DATA_TYPE_E    data_type       ;
}VDP_DRV_COEF_SEND_CFG;


HI_U8* VDP_DRV_SendCoef(VDP_DRV_COEF_SEND_CFG* stCfg);
HI_S32 VDP_DRV_Push128(VDP_DRV_U128_S* pstData128, HI_U32 coef_data, HI_U32 bit_len);
HI_U32 VDP_DRV_WriteDDR(STI_FILE_TYPE_E enStiType, FILE* fp_coef ,HI_U8 * addr, VDP_DRV_U128_S * pstData128 );
HI_U32 VDP_DRV_FindMax(HI_U32* u32Array, HI_U32 num);

#endif
