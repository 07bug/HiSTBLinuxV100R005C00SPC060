#ifndef __VPSS_TC_WRAPPER_H__
#define __VPSS_TC_WRAPPER_H__

#include "vpss_hal_reg.h"
//#include "vpss_driver.h"
#include "vpss_func_mac_rchn.h"
#include "vpss_func_mac_wchn.h"
#include "xdp_define.h"
//#include "vpss_mac_getinfo.h"
//#include "vdp_fdr_comm.h"
#include "hi_drv_mmz.h"
#include "vpss_cbb_intf.h"

#define VPSS_HOR_ZME_PRECISION  (1<<20)
#define VPSS_VER_ZME_PRECISION  (1<<12)
#define VPSS_HOR_OFFSET_PRECISION  (1<<20)
#define VPSS_VER_OFFSET_PRECISION  (1<<12)
//#define CLIP3(low,high,x) (MAX(MIN((X),high),low))

typedef enum
{
    ME_TO_RGME_CF = 0,
    ME_TO_ME_CF,
    VPSS_3DRS_INTER_CFG_BUTT
} THRDRS_INTER_CFG_E;

typedef enum
{
    PARA_MIN       = 0,
    PARA_MAX       = 1,
    PARA_TYPE      = 2,
    PARA_RAND      = 3,
    PARA_SET       = 4,//for mac para
    PATA_BUTT
} MODULE_PARA;

typedef struct
{
    HI_U32 i;//node_no
    HI_U32 en;
    HI_U32 in_width;
    HI_U32 in_height;
    HI_U32 ali_hor;
    HI_U32 ali_ver;
    HI_U32 pro;

    HI_U32 para;
    HI_U32 out_width;
    HI_U32 out_height;

} VPSS_CROP_CFG;

typedef struct
{
    HI_U32 i;//node_no
    HI_U32 en;
    HI_U32 in_width;
    HI_U32 in_height;
    HI_U32 ali_hor;
    HI_U32 ali_ver;
    HI_U32 pro;

    HI_U32 para;
    HI_U32 out_width;
    HI_U32 out_height;


} VPSS_LBA_CFG;

typedef struct
{
    HI_BOOL nrrfr_en ;
    HI_U32  width  ;
    HI_U32  height ;
    HI_U32  pro    ;
    HI_U32  bitwth ;

} VPSS_NRRFR_CFG_S;


typedef struct
{
    HI_U32 width ;
    HI_U32 height ;
    HI_U32 format ;
    HI_U32 pro    ;
    HI_U32 i      ;
    HI_U32 bitwth ;
    HI_U32 tnr_en ;
    HI_U32 mcnr_en ;
    HI_U32 madmode ;
    HI_U32 meds_en ;
} VPSS_TNR_CFG_S;

typedef enum
{
    VPSS_TNR_TYP = 0,
    VPSS_TNR_TYP1 ,
    VPSS_TNR_RAND ,
    VPSS_TNR_MAX ,
    VPSS_TNR_MIN ,
    VPSS_TNR_ZERO ,
    VPSS_TNR_BUTT
} VPSS_TNR_MODE_E;

typedef struct
{
    HI_U32 width ;
    HI_U32 height ;
    HI_U32 format ;
    HI_U32 pro    ;
    HI_U32 i      ;
    HI_U32 snr_en ;
    HI_U32 db_en ;
    HI_U32 blk_det_en ;
    HI_U32 mad_vfir_en ;
} VPSS_SNR_CFG_S;

typedef struct
{
    HI_U32 rgme_en ;
    HI_U32 width ;
    HI_U32 height ;
    HI_U32 pro;
} VPSS_RGME_CFG_S;

typedef struct
{
    HI_U32 width ;
    HI_U32 height ;
    HI_U32 format ;
    HI_U32 pro    ;
    HI_U32 i      ;
    HI_U32 bitwth ;
    HI_U32 dei_en ;
    HI_U32 mcdi_en ;
    HI_U32 rgme_en ;
    HI_U32 ifmd_en;
    HI_U32 igbm_en;
    HI_U32 bfield_first;
} VPSS_DEI_CFG_S;

typedef struct
{
    HI_U32 i;//node_no
    HI_U32 en;
    HI_U32 in_width;
    HI_U32 in_height;
    HI_U32 in_yc422;
    HI_U32 ali_hor;
    HI_U32 ali_ver;
    HI_U32 pro;

    HI_U32 para;
    HI_U32 out_width;
    HI_U32 out_height;
    HI_U32 out_yc422;

    HAL_VPSS_INPUTOUTPUT_CHANNEL_E channel;

} VPSS_ZME_CFG;

typedef struct
{
    HI_U32 u32FourPixEn;
} VPSS_GOLOBAL_CFG_S;

typedef struct
{
    CBB_FRAME_S     stNrRfr;
    CBB_FRAME_S     stNrP2;
    CBB_INFO_S      stInfoTnrMad;
    CBB_INFO_RGMV_S stInfoRgmv;

} VPSS_TNR_CHN_CFG_S;

typedef struct
{
    CBB_INFO_S      stInfoSnrMad;

} VPSS_SNR_CHN_CFG_S;

typedef struct
{
    CBB_FRAME_S      stP1;
    CBB_FRAME_S      stNrP2;
    CBB_FRAME_S      stP3;
    CBB_FRAME_S      stP3I;
    CBB_FRAME_S      stDiRfr;
    CBB_INFO_S       stInfoDiSt;
    CBB_INFO_DI_S    stInfoDiStCnt;
    CBB_INFO_BLKMV_S stInfoBlkmv;
    CBB_INFO_BLKMT_S stInfoBlkmt;
    CBB_INFO_RGMV_S  stInfoRgmv;
    CBB_INFO_PRJH_S  stInfoPrjh;
    CBB_INFO_PRJV_S  stInfoPrjv;

    HI_U32           u32BitWidth;

} VPSS_DEI_CHN_CFG_S;

typedef struct
{
    ////  ===============================================
    ////  DB
    unsigned int db_grad_sub_ratio       ;
    unsigned int db_ctrst_thresh         ;
    unsigned int db_lum_h_blk_size       ;
    unsigned int db_lum_hor_scale_ratio  ;
    unsigned int db_lum_hor_filter_sel   ;
    unsigned int db_global_db_strenth_lum;
    unsigned int db_lum_hor_txt_win_size ;
    unsigned int db_lum_hor_hf_diff_core ;
    unsigned int db_lum_hor_hf_diff_gain1;
    unsigned int db_lum_hor_hf_diff_gain2;
    unsigned int db_lum_hor_hf_var_core  ;
    unsigned int db_lum_hor_hf_var_gain1 ;
    unsigned int db_lum_hor_hf_var_gain2 ;
    unsigned int db_lum_hor_adj_gain     ;
    unsigned int db_lum_hor_bord_adj_gain;
    unsigned int db_ctrst_adj_core       ;
    unsigned int db_dir_smooth_mode      ;
    unsigned int db_ctrst_adj_gain1      ;
    unsigned int db_ctrst_adj_gain2      ;
    unsigned int db_max_lum_hor_db_dist  ;

    ////  ===============================================
    ////  DBD
    unsigned int dbd_hy_thd_edge     ;
    unsigned int dbd_hy_thd_txt      ;
    unsigned int dbd_hy_rtn_bd_txt   ;
    unsigned int dbd_hy_tst_blk_num  ;
    unsigned int dbd_min_blk_size    ;
    unsigned int dbd_hy_max_blk_size ;
    unsigned int dbd_thr_flat        ;

    ////  ===============================================
    ////  DM
    unsigned int dm_grad_sub_ratio    ;
    unsigned int dm_ctrst_thresh      ;
    unsigned int dm_opp_ang_ctrst_t   ;
    unsigned int dm_opp_ang_ctrst_div ;
    unsigned int dm_mmf_set           ;
    unsigned int dm_init_val_step     ;
    unsigned int dm_global_str        ;
    unsigned int dm_mndir_opp_ctrst_t ;
    unsigned int dm_mmf_limit_en      ;
    unsigned int dm_csw_trsnt_st_10   ;
    unsigned int dm_lw_ctrst_t        ;
    unsigned int dm_lw_ctrst_t_10     ;
    unsigned int dm_csw_trsnt_st      ;
    unsigned int dm_lsw_ratio         ;
    unsigned int dm_mmf_lr            ;
    unsigned int dm_mmf_lr_10         ;
    unsigned int dm_csw_trsnt_lt      ;
    unsigned int dm_mmf_sr            ;
    unsigned int dm_mmf_sr_10         ;
    unsigned int dm_csw_trsnt_lt_10   ;
    unsigned int dm_limit_lsw_ratio   ;
    unsigned int dm_lim_res_blend_str1;
    unsigned int dm_lim_res_blend_str2;
    unsigned int dm_dir_blend_str     ;
    unsigned int dm_limit_t           ;
    unsigned int dm_limit_t_10        ;

    ////  SNR
    int ynr2den             ;
    int cnr2den             ;
    int motionedgeweighten  ;
    int colorweighten       ;
    int edgeprefilteren     ;
    int edgemaxratio        ;
    int edgeminratio        ;
    int edgeoriratio        ;
    int edgemaxstrength     ;
    int edgeminstrength     ;
    int edgeoristrength     ;
    int edgestrth1          ;
    int edgestrth2          ;
    int edgestrth3          ;
    int edgestrk1           ;
    int edgestrk2           ;
    int edgestrk3           ;
    int edgemeanth1         ;
    int edgemeanth2         ;
    int edgemeanth3         ;
    int edgemeanth4         ;
    int edgemeanth5         ;
    int edgemeanth6         ;
    int edgemeanth7         ;
    int edgemeanth8         ;
    int edgemeank1          ;
    int edgemeank2          ;
    int edgemeank3          ;
    int edgemeank4          ;
    int edgemeank5          ;
    int edgemeank6          ;
    int edgemeank7          ;
    int edgemeank8          ;
    int y2dwinwidth         ;
    int y2dwinheight        ;
    int c2dwinwidth         ;
    int c2dwinheight        ;
    int ysnrstr             ;
    int csnrstr             ;
    int stroffset0          ;
    int stroffset1          ;
    int stroffset2          ;
    int stroffset3          ;
    int ystradjust          ;
    int cstradjust          ;
    int scenechangeth       ;
    int ratio1              ;
    int ratio2              ;
    int ratio3              ;
    int ratio4              ;
    int ratio5              ;
    int ratio6              ;
    int ratio7              ;
    int ratio8              ;
    int edge1               ;
    int edge2               ;
    int edge3               ;
    int test_en             ;
    int test_color_cb       ;
    int test_color_cr       ;
    int scenechange_info    ;
    int scenechange_en      ;
    int scenechange_mode1_en;
    int scenechange_bldk    ;
    int scenechange_bldcore ;
    int scenechange_mode2_en;
    int motionalpha         ;
    int cb_begin1           ;
    int cr_begin1           ;
    int cb_end1             ;
    int cr_end1             ;
    int cbcr_weight1        ;
    int cb_begin2           ;
    int cr_begin2           ;
    int cb_end2             ;
    int cr_end2             ;
    int cbcr_weight2        ;
    int motion_edge_lut[32];

    int ywin_num            ;
    int yWinRand_Width      ;
} VPSS_TNR_REG_TYPE_S;

XDP_DATA_RMODE_E RMODE_ADP(XDP_DATA_RMODE_E enRdMode);
HI_VOID RCHN_CFG_CP(VPSS_MAC_RCHN_CFG_S *psSrcCfg, VPSS_MAC_RCHN_CFG_S *psDesCfg);
HI_VOID VPSS_DRV_SetVhd0CropCfg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_CROP_CFG *crop_cfg);
HI_VOID VPSS_DRV_SetVhd0LbaCfg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_LBA_CFG *lba_cfg);
HI_VOID VPSS_DRV_SetZmeCfg(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_ZME_CFG *zme_cfg);
HI_VOID vpss_scl8Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][8]);
HI_VOID vpss_scl6Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][6]);
HI_VOID vpss_scl4Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][4]);
HI_VOID vpss_scl2Tapcoef_to_dut(HI_U32 coef_start_addr, HI_S32 arr[17][2]);           //for 17*2
HI_U32 VPSS_DRV_Conver_ScaleCoef(HI_S32 s32Value);
HI_VOID VPSS_NRRFR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_NRRFR_CFG_S *pstNrRfrCfg, CBB_FRAME_S *pstNrRfr);
HI_VOID VPSS_RGME_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_RGME_CFG_S *pstRgmeCfg, VPSS_DEI_CHN_CFG_S *pstDeiChnCfg);
HI_VOID VPSS_TNR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_TNR_CFG_S *pstTnrCfg, VPSS_TNR_CHN_CFG_S *pstTnrChnCfg);
HI_VOID VPSS_SNR_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_SNR_CFG_S *pstSnrCfg, VPSS_SNR_CHN_CFG_S *pstSnrChnCfg);
HI_VOID VPSS_DEI_CHN_SET(CBB_REG_ADDR_S stRegAddr, VPSS_DEI_CFG_S *pstDeiCfg, VPSS_DEI_CHN_CFG_S *pstDeiChnCfg);
HI_VOID VPSS_FUNC_SetTnrMode(S_VPSS_REGS_TYPE *pstVpssRegs, VPSS_TNR_MODE_E TnrMode, VPSS_TNR_CFG_S *pstCfg);
HI_VOID VPSS_FUNC_SetSnrMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_SNR_CFG_S *pstCfg);
HI_VOID VPSS_FUNC_SetDeiMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset  , VPSS_DEI_CFG_S *pstCfg);
#endif
