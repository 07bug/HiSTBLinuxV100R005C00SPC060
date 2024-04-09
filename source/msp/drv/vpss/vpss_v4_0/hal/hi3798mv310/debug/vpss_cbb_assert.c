#include "hi_reg_common.h"
#include "vpss_cbb_assert.h"
#include "vpss_hal_comm.h"
#include "hi_reg_common.h"
#include "vpss_assert_tnr.h"
#include "vpss_assert_rgme.h"
#include "vpss_assert_dei.h"
#include "vpss_assert_snr.h"

HI_VOID VPSS_HAL_Assert(HI_S32 s32NodeId, volatile S_VPSS_REGS_TYPE *vpss_reg)
{
    VPSS_ConfigCheck((S_VPSS_REGS_TYPE *)vpss_reg, HI_TRUE);
    return;
}

HI_U32 VPSS_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable)
{
    VPSS_CFG_INFO_S stCfgInfo;

    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    //XDP_PRINT("VPSS Config Check Start:\n");

    VPSS_GetCfgInfo(pReg, HI_TRUE, &stCfgInfo);
    //VPSS_SYS_APB_ConfigCheck(pReg, HI_TRUE, &stCfgInfo);
    VPSS_SYS_ConfigCheck(pReg, HI_TRUE, &stCfgInfo);
    VPSS_MAC_ConfigCheck(pReg, HI_TRUE, &stCfgInfo);
    VPSS_IP_ConfigCheck(pReg, HI_TRUE, &stCfgInfo);

    //XDP_PRINT("VPSS Config Check End!\n");

    return HI_SUCCESS;
}

HI_U32 VPSS_GetCfgInfo(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo)
{
    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    //XDP_PRINT("VPSS Get Config Info Start:\n");
    /******************* declairation  *********************/


    /******************* get reg value *********************/
    pstCfgInfo->u32Format      = pReg->VPSS_CF_CTRL.bits.cf_format;
    pstCfgInfo->u32Prio        = 0;
    pstCfgInfo->u32Img2d3dMode = 0;
    pstCfgInfo->u32Pro         = pReg->VPSS_CF_CTRL.bits.cf_lm_rmode == 1 ? 1 : 0;
    pstCfgInfo->u32Even        = 0;
    pstCfgInfo->u32Bfield      = pReg->VPSS_CF_CTRL.bits.cf_lm_rmode % 2;
    pstCfgInfo->u32Type        = pReg->VPSS_CF_CTRL.bits.cf_type;
    pstCfgInfo->u32DcmpMode    = pReg->VPSS_CF_CTRL.bits.cf_dcmp_mode;
    pstCfgInfo->u32PreMultEn   = 0;
    pstCfgInfo->u32CompValid   = 0xffffffff;

    pstCfgInfo->u32Wth         = pReg->VPSS_CF_SIZE.bits.cf_width  + 1;
    pstCfgInfo->u32Hgt         = pReg->VPSS_CF_SIZE.bits.cf_height + 1;

    /*******************   assertion   *********************/

    XDP_ASSERT(pstCfgInfo->u32Format <= XDP_PROC_FMT_SP_400);
    XDP_ASSERT(pstCfgInfo->u32Format != XDP_PROC_FMT_SP_444);
    if (pstCfgInfo->u32Format == XDP_PROC_FMT_SP_400)
    {
        pstCfgInfo->u32Format = XDP_PROC_FMT_SP_420;
    }

    if (pstCfgInfo->u32Type == XDP_DATA_TYPE_PACKAGE)
    {
        XDP_ASSERT(pstCfgInfo->u32Format == XDP_PROC_FMT_SP_422);
    }
    if (pstCfgInfo->u32Type == XDP_DATA_TYPE_SP_TILE)
    {
        XDP_ASSERT(pstCfgInfo->u32Format != XDP_PROC_FMT_SP_422);
    }

    if (pstCfgInfo->u32Pro == 0)
    {
        pstCfgInfo->u32Hgt /= 2;
    }

    if (pstCfgInfo->u32DcmpMode == 1)
    {
        XDP_ASSERT((pReg->VPSS_CF_CTRL.bits.cf_lm_rmode < 2) || (pReg->VPSS_CF_CTRL.bits.cf_lm_rmode > 3));
        XDP_ASSERT(pstCfgInfo->u32Type == XDP_DATA_TYPE_SP_TILE);
    }

    //if((pReg->VPSS_CF_CTRL.bits.cf_bitw==1)&&(pstCfgInfo->u32Type==XDP_DATA_TYPE_SP_TILE))
    //    XDP_ASSERT(pstCfgInfo->u32DcmpMode==1);

    //XDP_PRINT("VPSS Get Config Info End!\n");

    return HI_SUCCESS;
}


HI_U32 VPSS_SYS_APB_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo)
{
    HI_U32 scb_ttbr       = pReg->VPSS0_SMMU_SCB_TTBR      .bits. scb_ttbr       ;
    HI_U32 cb_ttbr        = pReg->VPSS0_SMMU_CB_TTBR       .bits. cb_ttbr        ;
    HI_U32 err_s_rd_addr  = pReg->VPSS0_SMMU_ERR_RDADDR_S  .bits. err_s_rd_addr  ;
    HI_U32 err_s_wr_addr  = pReg->VPSS0_SMMU_ERR_WRADDR_S  .bits. err_s_wr_addr  ;
    HI_U32 err_ns_rd_addr = pReg->VPSS0_SMMU_ERR_RDADDR_NS .bits. err_ns_rd_addr ;
    HI_U32 err_ns_wr_addr = pReg->VPSS0_SMMU_ERR_WRADDR_NS .bits. err_ns_wr_addr ;

    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    //XDP_PRINT("VPSS SYS Config Check Start:\n");

    //MMU
    XDP_ASSERT((scb_ttbr       & 0x3f) == 0);
    XDP_ASSERT((cb_ttbr        & 0x3f) == 0);
    XDP_ASSERT((err_s_rd_addr  & 0xff) == 0);
    XDP_ASSERT((err_s_wr_addr  & 0xff) == 0);
    XDP_ASSERT((err_ns_rd_addr & 0xff) == 0);
    XDP_ASSERT((err_ns_wr_addr & 0xff) == 0);

    //    XDP_PRINT("[%s][%d] &pReg->VPSS_MST_CTRL = %#x.\n",__func__,__LINE__,&pReg->VPSS_MST_CTRL);
    //    XDP_PRINT("[%s][%d] pReg->VPSS_MST_CTRL.u32 = %#x.\n",__func__,__LINE__,pReg->VPSS_MST_CTRL.u32);
    XDP_ASSERT(pReg->VPSS_MST_CTRL.bits.mid_enable == 1);
    XDP_ASSERT(pReg->VPSS_MST_CTRL.bits.split_mode != 0);
    XDP_ASSERT(pReg->VPSS_MST_CTRL.bits.split_mode <= 4);
    XDP_ASSERT(pReg->VPSS_MST_OUTSTANDING.bits.mstr0_routstanding <= 15);
    XDP_ASSERT(pReg->VPSS_MST_OUTSTANDING.bits.mstr0_woutstanding <=  7);

    //XDP_PRINT("VPSS SYS Config Check End!\n");

    return HI_SUCCESS;
}

HI_U32 VPSS_SYS_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo)
{
    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    //XDP_PRINT("VPSS SYS Config Check Start:\n");

    XDP_ASSERT((pReg->VPSS_CHN_CFG_CTRL.bits.prot == 0) || (pReg->VPSS_CHN_CFG_CTRL.bits.prot == 2));
    XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.max_req_len <=  1);
    XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.max_req_num <=  2);

    if (pReg->VPSS_CHN_CFG_CTRL.bits.dma_en == 1 || pReg->VPSS_CHN_CFG_CTRL.bits.rotate_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.igbm_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.ifmd_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.mcdi_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.dei_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.mcnr_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.tnr_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.snr_en == 0);
    }

    if (pReg->VPSS_CHN_CFG_CTRL.bits.rotate_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.dma_en == 0);
        XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.img_pro_mode != 0);
        XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.img_pro_mode <= 2);
    }
    else
    {
        XDP_ASSERT(pReg->VPSS_CHN_CFG_CTRL.bits.img_pro_mode == 0);
    }

    if (pReg->VPSS_CTRL.bits.four_pix_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.igbm_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.ifmd_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.mcdi_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.dei_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.mcnr_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.tnr_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.snr_en == 0);
        XDP_ASSERT(pReg->VPSS_CF_CTRL.bits.cf_type != XDP_DATA_TYPE_PACKAGE);
    }
    if ((pReg->VPSS_CF_CTRL.bits.cf_type == XDP_DATA_TYPE_PACKAGE))
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.snr_en == 0);
    }

    if ((pstCfgInfo->u32Wth > 1920) && (pReg->VPSS_CF_CTRL.bits.cf_type == XDP_DATA_TYPE_SP_TILE))
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.four_pix_en == 1);
    }


    if ((0x1 == pReg->VPSS_LCHDR_CTRL.bits.lchdr_en) && (0x1 == pReg->VPSS_CTRL.bits.four_pix_en))
    {
        XDP_ASSERT(pReg->VPSS_CTRL3.bits.zme_vhd0_en == 1);
    }

    if ((pReg->VPSS_CF_CTRL.bits.cf_dcmp_mode == 1) && (pReg->VPSS_CF_CTRL.bits.cf_type == XDP_DATA_TYPE_SP_TILE))
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.dei_en == 0);
        XDP_ASSERT(pReg->VPSS_CTRL.bits.snr_en == 0);
    }

    if (pReg->VPSS_CTRL.bits.dei_en == 1)
    {
        XDP_ASSERT((pReg->VPSS_CF_CTRL.bits.cf_lm_rmode > 1));
    }

    if ((pReg->VPSS_CF_CTRL.bits.cf_type == XDP_DATA_TYPE_SP_TILE) && (pReg->VPSS_CTRL.bits.snr_en == 1))
    {
        XDP_ASSERT((pReg->VPSS_CF_CTRL.bits.cf_lm_rmode > 1) || (pReg->VPSS_CF_CTRL.bits.cf_lm_rmode < 4));
    }
    if (pReg->VPSS_CTRL3.bits.zme_vhd0_en == 1)
    {
        XDP_ASSERT(pstCfgInfo->u32Hgt % 2 == 0);
    }
    //XDP_PRINT("VPSS SYS Config Check End!\n");

    return HI_SUCCESS;
}

HI_U32 VPSS_MAC_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo)
{
#if 0
    HI_U32 u32CfgChkScanCnt;
    HI_U64 u64ScanPnextAddr;
    HI_U32 u32AddrCnt;
    S_VPSS_REGS_TYPE *pRegScan;
    HI_U32 *pCfgChnLowAddr;
    HI_U32 *pCfgChnSizeWidth ;
    HI_U32 *pCfgChnSizeHeight;
    HI_U32 di_cf_tunl_en     ;
    HI_U32 snr_rmad_tunl_en  ;
    HI_U32 nr_cfmv_tunl_en   ;
    HI_U32 me_cf_tunl_en     ;
    HI_U32 me_p2rgmv_tunl_en ;
    HI_U32 me_cfmv_tunl_en   ;
    HI_U32 me_cfgmv_tunl_en  ;

    HI_U32 chk_sum_en    =  pReg->VPSS_CHK_SUM_CTRL    .bits. chk_sum_en    ;
    HI_U32 cf_rtunl_en   =  pReg->VPSS_CF_RTUNL_CTRL   .bits. cf_rtunl_en   ;
    HI_U32 out0_wtunl_en =  pReg->VPSS_OUT0_WTUNL_CTRL .bits. out0_wtunl_en ;
    HI_U32 cf_en         =  pReg->VPSS_CF_CTRL         .bits. cf_en         ;
    HI_U32 out0_en       =  pReg->VPSS_OUT0_CTRL       .bits. out0_en       ;
    HI_U32 out3_en       =  pReg->VPSS_OUT3_CTRL       .bits. out3_en       ;
    HI_U32 nr_rfrh_en    =  pReg->VPSS_NR_RFRH_CTRL    .bits. nr_rfrh_en    ;
    HI_U32 nr_rfrhv_en   =  pReg->VPSS_NR_RFRHV_CTRL   .bits. nr_rfrhv_en   ;

    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    XDP_PRINT("VPSS MAC Config Check Start:\n");

    pCfgChnLowAddr = (HI_U32 *)malloc(LAST_CHN_ADDR * sizeof(HI_U32));
    memset(pCfgChnLowAddr, 0 , LAST_CHN_ADDR * sizeof(HI_U32));
    pCfgChnSizeWidth  = (HI_U32 *)malloc(LAST_CHN_SIZE * sizeof(HI_U32));
    memset(pCfgChnSizeWidth , 0 , LAST_CHN_SIZE * sizeof(HI_U32));
    pCfgChnSizeHeight = (HI_U32 *)malloc(LAST_CHN_SIZE * sizeof(HI_U32));
    memset(pCfgChnSizeHeight, 0 , LAST_CHN_SIZE * sizeof(HI_U32));


    di_cf_tunl_en     = pReg->VPSS_DI_CF_CTRL.     bits.di_cf_tunl_en     ;
    snr_rmad_tunl_en  = pReg->VPSS_SNR_RMAD_CTRL.  bits.snr_rmad_tunl_en  ;
    nr_cfmv_tunl_en   = pReg->VPSS_NR_CFMV_CTRL.   bits.nr_cfmv_tunl_en   ;
    me_cf_tunl_en     = pReg->VPSS_ME_CF_CTRL.     bits.me_cf_tunl_en     ;
    me_p2rgmv_tunl_en = pReg->VPSS_ME_P2RGMV_CTRL. bits.me_p2rgmv_tunl_en ;
    pCfgChnLowAddr[ VPSS_STT_R_ADDR      ] =  pReg->VPSS_STT_R_ADDR_LOW.bits.stt_r_addr_l;
    pCfgChnLowAddr[ VPSS_STT_W_ADDR      ] =  pReg->VPSS_STT_W_ADDR_LOW.bits.stt_w_addr_l;
    pCfgChnLowAddr[ VPSS_CHK_SUM_ADDR    ] =  pReg->VPSS_CHK_SUM_ADDR_LOW.bits.chk_sum_addr_l;
    pCfgChnLowAddr[ VPSS_CF_RTUNL_ADDR   ] =  pReg->VPSS_CF_RTUNL_ADDR_LOW.bits.cf_rtunl_addr_l;
    pCfgChnLowAddr[ VPSS_OUT0_WTUNL_ADDR ] =  pReg->VPSS_OUT0_WTUNL_ADDR_LOW.bits.out0_wtunl_addr_l;
    pCfgChnLowAddr[ VPSS_CFY_ADDR        ] =  pReg->VPSS_CFY_ADDR_LOW.bits.cfy_addr_l;
    pCfgChnLowAddr[ VPSS_CFC_ADDR        ] =  pReg->VPSS_CFC_ADDR_LOW.bits.cfc_addr_l;
    pCfgChnLowAddr[ VPSS_CFCR_ADDR       ] =  pReg->VPSS_CFCR_ADDR_LOW.bits.cfcr_addr_l;
    pCfgChnLowAddr[ VPSS_DI_CFY_ADDR     ] =  pReg->VPSS_DI_CFY_ADDR_LOW.bits.di_cfy_addr_l;
    pCfgChnLowAddr[ VPSS_DI_CFC_ADDR     ] =  pReg->VPSS_DI_CFC_ADDR_LOW.bits.di_cfc_addr_l;
    pCfgChnLowAddr[ VPSS_DI_CFCR_ADDR    ] =  pReg->VPSS_DI_CFCR_ADDR_LOW.bits.di_cfcr_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P1Y_ADDR     ] =  pReg->VPSS_DI_P1Y_ADDR_LOW.bits.di_p1y_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P1C_ADDR     ] =  pReg->VPSS_DI_P1C_ADDR_LOW.bits.di_p1c_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P2Y_ADDR     ] =  pReg->VPSS_DI_P2Y_ADDR_LOW.bits.di_p2y_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P2C_ADDR     ] =  pReg->VPSS_DI_P2C_ADDR_LOW.bits.di_p2c_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P3Y_ADDR     ] =  pReg->VPSS_DI_P3Y_ADDR_LOW.bits.di_p3y_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P3C_ADDR     ] =  pReg->VPSS_DI_P3C_ADDR_LOW.bits.di_p3c_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P3IY_ADDR    ] =  pReg->VPSS_DI_P3IY_ADDR_LOW.bits.di_p3iy_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P3IC_ADDR    ] =  pReg->VPSS_DI_P3IC_ADDR_LOW.bits.di_p3ic_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR0Y_ADDR    ] =  pReg->VPSS_CC_PR0Y_ADDR_LOW.bits.cc_pr0y_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR0C_ADDR    ] =  pReg->VPSS_CC_PR0C_ADDR_LOW.bits.cc_pr0c_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR4Y_ADDR    ] =  pReg->VPSS_CC_PR4Y_ADDR_LOW.bits.cc_pr4y_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR4C_ADDR    ] =  pReg->VPSS_CC_PR4C_ADDR_LOW.bits.cc_pr4c_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR8Y_ADDR    ] =  pReg->VPSS_CC_PR8Y_ADDR_LOW.bits.cc_pr8y_addr_l;
    pCfgChnLowAddr[ VPSS_CC_PR8C_ADDR    ] =  pReg->VPSS_CC_PR8C_ADDR_LOW.bits.cc_pr8c_addr_l;
    pCfgChnLowAddr[ VPSS_NR_REFY_ADDR    ] =  pReg->VPSS_NR_REFY_ADDR_LOW.bits.nr_refy_addr_l;
    pCfgChnLowAddr[ VPSS_NR_REFC_ADDR    ] =  pReg->VPSS_NR_REFC_ADDR_LOW.bits.nr_refc_addr_l;
    pCfgChnLowAddr[ VPSS_DI_RSADY_ADDR   ] =  pReg->VPSS_DI_RSADY_ADDR_LOW.bits.di_rsady_addr_l;
    pCfgChnLowAddr[ VPSS_DI_RSADC_ADDR   ] =  pReg->VPSS_DI_RSADC_ADDR_LOW.bits.di_rsadc_addr_l;
    pCfgChnLowAddr[ VPSS_DI_RHISM_ADDR   ] =  pReg->VPSS_DI_RHISM_ADDR_LOW.bits.di_rhism_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P1MV_ADDR    ] =  pReg->VPSS_DI_P1MV_ADDR_LOW.bits.di_p1mv_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P2MV_ADDR    ] =  pReg->VPSS_DI_P2MV_ADDR_LOW.bits.di_p2mv_addr_l;
    pCfgChnLowAddr[ VPSS_DI_P3MV_ADDR    ] =  pReg->VPSS_DI_P3MV_ADDR_LOW.bits.di_p3mv_addr_l;
    pCfgChnLowAddr[ VPSS_CC_RCCNT_ADDR   ] =  pReg->VPSS_CC_RCCNT_ADDR_LOW.bits.cc_rccnt_addr_l;
    pCfgChnLowAddr[ VPSS_CC_RYCNT_ADDR   ] =  pReg->VPSS_CC_RYCNT_ADDR_LOW.bits.cc_rycnt_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RMAD_ADDR    ] =  pReg->VPSS_NR_RMAD_ADDR_LOW.bits.nr_rmad_addr_l;
    pCfgChnLowAddr[ VPSS_SNR_RMAD_ADDR   ] =  pReg->VPSS_SNR_RMAD_ADDR_LOW.bits.snr_rmad_addr_l;
    pCfgChnLowAddr[ VPSS_NR_CFMV_ADDR    ] =  pReg->VPSS_NR_CFMV_ADDR_LOW.bits.nr_cfmv_addr_l;
    pCfgChnLowAddr[ VPSS_NR_P1RGMV_ADDR  ] =  pReg->VPSS_NR_P1RGMV_ADDR_LOW.bits.nr_p1rgmv_addr_l;
    pCfgChnLowAddr[ VPSS_NR_P2RGMV_ADDR  ] =  pReg->VPSS_NR_P2RGMV_ADDR_LOW.bits.nr_p2rgmv_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RCNT_ADDR    ] =  pReg->VPSS_NR_RCNT_ADDR_LOW.bits.nr_rcnt_addr_l;
    pCfgChnLowAddr[ VPSS_RG_RPRJH_ADDR   ] =  pReg->VPSS_RG_RPRJH_ADDR_LOW.bits.rg_rprjh_addr_l;
    pCfgChnLowAddr[ VPSS_RG_RPRJV_ADDR   ] =  pReg->VPSS_RG_RPRJV_ADDR_LOW.bits.rg_rprjv_addr_l;
    pCfgChnLowAddr[ VPSS_RG_P1RGMV_ADDR  ] =  pReg->VPSS_RG_P1RGMV_ADDR_LOW.bits.rg_p1rgmv_addr_l;
    pCfgChnLowAddr[ VPSS_RG_P2RGMV_ADDR  ] =  pReg->VPSS_RG_P2RGMV_ADDR_LOW.bits.rg_p2rgmv_addr_l;
    pCfgChnLowAddr[ VPSS_OUT0Y_ADDR      ] =  pReg->VPSS_OUT0Y_ADDR_LOW.bits.out0y_addr_l;
    pCfgChnLowAddr[ VPSS_OUT0C_ADDR      ] =  pReg->VPSS_OUT0C_ADDR_LOW.bits.out0c_addr_l;
    pCfgChnLowAddr[ VPSS_OUT3Y_ADDR      ] =  pReg->VPSS_OUT3Y_ADDR_LOW.bits.out3y_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RFRY_ADDR    ] =  pReg->VPSS_NR_RFRY_ADDR_LOW.bits.nr_rfry_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RFRC_ADDR    ] =  pReg->VPSS_NR_RFRC_ADDR_LOW.bits.nr_rfrc_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RFRHY_ADDR   ] =  pReg->VPSS_NR_RFRHY_ADDR_LOW.bits.nr_rfrhy_addr_l;
    pCfgChnLowAddr[ VPSS_NR_RFRHVY_ADDR  ] =  pReg->VPSS_NR_RFRHVY_ADDR_LOW.bits.nr_rfrhvy_addr_l;
    pCfgChnLowAddr[ VPSS_CC_RFRY_ADDR    ] =  pReg->VPSS_CC_RFRY_ADDR_LOW.bits.cc_rfry_addr_l;
    pCfgChnLowAddr[ VPSS_CC_RFRC_ADDR    ] =  pReg->VPSS_CC_RFRC_ADDR_LOW.bits.cc_rfrc_addr_l;
    pCfgChnLowAddr[ VPSS_DI_RFRY_ADDR    ] =  pReg->VPSS_DI_RFRY_ADDR_LOW.bits.di_rfry_addr_l;
    pCfgChnLowAddr[ VPSS_DI_RFRC_ADDR    ] =  pReg->VPSS_DI_RFRC_ADDR_LOW.bits.di_rfrc_addr_l;
    pCfgChnLowAddr[ VPSS_NR_WMAD_ADDR    ] =  pReg->VPSS_NR_WMAD_ADDR_LOW.bits.nr_wmad_addr_l;
    pCfgChnLowAddr[ VPSS_NR_WCNT_ADDR    ] =  pReg->VPSS_NR_WCNT_ADDR_LOW.bits.nr_wcnt_addr_l;
    pCfgChnLowAddr[ VPSS_CC_WCCNT_ADDR   ] =  pReg->VPSS_CC_WCCNT_ADDR_LOW.bits.cc_wccnt_addr_l;
    pCfgChnLowAddr[ VPSS_CC_WYCNT_ADDR   ] =  pReg->VPSS_CC_WYCNT_ADDR_LOW.bits.cc_wycnt_addr_l;
    pCfgChnLowAddr[ VPSS_DI_WSADY_ADDR   ] =  pReg->VPSS_DI_WSADY_ADDR_LOW.bits.di_wsady_addr_l;
    pCfgChnLowAddr[ VPSS_DI_WSADC_ADDR   ] =  pReg->VPSS_DI_WSADC_ADDR_LOW.bits.di_wsadc_addr_l;
    pCfgChnLowAddr[ VPSS_DI_WHISM_ADDR   ] =  pReg->VPSS_DI_WHISM_ADDR_LOW.bits.di_whism_addr_l;
    pCfgChnLowAddr[ VPSS_RG_WPRJH_ADDR   ] =  pReg->VPSS_RG_WPRJH_ADDR_LOW.bits.rg_wprjh_addr_l;
    pCfgChnLowAddr[ VPSS_RG_WPRJV_ADDR   ] =  pReg->VPSS_RG_WPRJV_ADDR_LOW.bits.rg_wprjv_addr_l;
    pCfgChnLowAddr[ VPSS_RG_CFRGMV_ADDR  ] =  pReg->VPSS_RG_CFRGMV_ADDR_LOW.bits.rg_cfrgmv_addr_l;

    pCfgChnSizeWidth [ VPSS_CF_SIZE             ]    =  pReg->VPSS_CF_SIZE.bits.cf_width;
    pCfgChnSizeHeight[ VPSS_CF_SIZE             ]    =  pReg->VPSS_CF_SIZE.bits.cf_height;

    XDP_ASSERT(chk_sum_en == 0);
    XDP_ASSERT(cf_en == 1);
    XDP_ASSERT(out0_en == 1);

    for (u32AddrCnt = 0; u32AddrCnt < LAST_CHN_ADDR; u32AddrCnt++)
    {
        XDP_ASSERT((pCfgChnLowAddr[u32AddrCnt] & 0xf) == 0);
    }
    XDP_ASSERT((pCfgChnLowAddr[VPSS_CF_RTUNL_ADDR]  & 0x1f) == 0);
    XDP_ASSERT((pCfgChnLowAddr[VPSS_OUT0_WTUNL_ADDR] & 0x1f) == 0);

    if (di_cf_tunl_en == 1)
    {
        XDP_ASSERT(pCfgChnLowAddr[VPSS_NR_RFRY_ADDR] == pCfgChnLowAddr[ VPSS_DI_CFY_ADDR   ]);
        XDP_ASSERT(pCfgChnLowAddr[VPSS_NR_RFRC_ADDR] == pCfgChnLowAddr[ VPSS_DI_CFC_ADDR   ]);
    }
    if (snr_rmad_tunl_en == 1)
    {
        XDP_ASSERT(pCfgChnLowAddr[VPSS_SNR_RMAD_ADDR] == pCfgChnLowAddr[ VPSS_NR_WMAD_ADDR   ]);
    }

    u64ScanPnextAddr = ((HI_U64)pReg->SCAN_START_ADDR_H.u32 << 20) + pReg->SCAN_START_ADDR_L.u32;
    u32CfgChkScanCnt = 0;
    XDP_ASSERT(u64ScanPnextAddr != 0);
    while (u64ScanPnextAddr != 0)
    {
        pRegScan = (S_VPSS_REGS_TYPE *)((HI_U32 *)pReg + VPSS_MAX_REGS_NUM_IN_ONE_SCAN * u32CfgChkScanCnt);

        if (pRegScan->SCAN_CTRL.bits.me_en == 1)
        {
            XDP_ASSERT(nr_rfrh_en == 1);
            XDP_ASSERT(nr_rfrhv_en == 1);
        }

        //assert code

        pCfgChnLowAddr[ VPSS_ME_CFY_ADDR    ] =  pRegScan->VPSS_ME_CFY_ADDR_LOW.bits.me_cfy_addr_l;
        pCfgChnLowAddr[ VPSS_ME_REFY_ADDR   ] =  pRegScan->VPSS_ME_REFY_ADDR_LOW.bits.me_refy_addr_l;
        pCfgChnLowAddr[ VPSS_ME_P1MV_ADDR   ] =  pRegScan->VPSS_ME_P1MV_ADDR_LOW.bits.me_p1mv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_PRMV_ADDR   ] =  pRegScan->VPSS_ME_PRMV_ADDR_LOW.bits.me_prmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_P1GMV_ADDR  ] =  pRegScan->VPSS_ME_P1GMV_ADDR_LOW.bits.me_p1gmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_PRGMV_ADDR  ] =  pRegScan->VPSS_ME_PRGMV_ADDR_LOW.bits.me_prgmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_P1RGMV_ADDR ] =  pRegScan->VPSS_ME_P1RGMV_ADDR_LOW.bits.me_p1rgmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_P2RGMV_ADDR ] =  pRegScan->VPSS_ME_P2RGMV_ADDR_LOW.bits.me_p2rgmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_CFMV_ADDR   ] =  pRegScan->VPSS_ME_CFMV_ADDR_LOW.bits.me_cfmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_CFGMV_ADDR  ] =  pRegScan->VPSS_ME_CFGMV_ADDR_LOW.bits.me_cfgmv_addr_l;
        pCfgChnLowAddr[ VPSS_ME_STT_W_ADDR  ] =  pRegScan->VPSS_ME_STT_W_ADDR_LOW.bits.me_stt_w_addr_l;

        for (u32AddrCnt = VPSS_ME_CFY_ADDR; u32AddrCnt < LAST_CHN_ADDR; u32AddrCnt++)
        {
            XDP_ASSERT((pCfgChnLowAddr[u32AddrCnt] & 0xf) == 0);
        }
        XDP_ASSERT(pCfgChnLowAddr[VPSS_ME_PRMV_ADDR] == pCfgChnLowAddr[ VPSS_ME_CFMV_ADDR   ]);
        XDP_ASSERT(pCfgChnLowAddr[VPSS_ME_PRGMV_ADDR] == pCfgChnLowAddr[ VPSS_ME_CFGMV_ADDR   ]);

        if ((nr_cfmv_tunl_en == 1) && (u32CfgChkScanCnt == 0))
        {
            XDP_ASSERT(pCfgChnLowAddr[VPSS_NR_CFMV_ADDR] == pCfgChnLowAddr[ VPSS_ME_CFMV_ADDR   ]);
        }

        if (me_p2rgmv_tunl_en == 1)
        {
            XDP_ASSERT(pCfgChnLowAddr[VPSS_ME_P2RGMV_ADDR] == pCfgChnLowAddr[ VPSS_RG_CFRGMV_ADDR   ]);
        }

        u64ScanPnextAddr  = ((HI_U64)pRegScan->SCAN_PNEXT_ADDR_H.u32 << 20) + pRegScan->SCAN_PNEXT_ADDR_L.u32;
        u32CfgChkScanCnt += 1;
    }

    XDP_PRINT("VPSS MAC Config Check End!\n");

    free(pCfgChnLowAddr);
    free(pCfgChnSizeWidth);
    free(pCfgChnSizeHeight);
#endif
    return HI_SUCCESS;
}

HI_U32 VPSS_IP_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo)
{
#if 0
    HI_U32 u32ExtInfo;
    HI_U32 u32CfgChkScanCnt;
    HI_U64 u64ScanPnextAddr;
    S_VPSS_REGS_TYPE *pRegScan;
    S_VPSS_REGS_TYPE *pRegScanPre;
    VPSS_CFG_INFO_S *pstCfgInfoOut0;
    VPSS_CFG_INFO_S *pstCfgInfoOut3;
    VPSS_CFG_INFO_S *pstCfgInfoRgme;
    VPSS_CFG_INFO_S *pstCfgInfoMe;
    VPSS_CFG_INFO_S *pstCfgInfoMeCf;
    VPSS_CFG_INFO_S *pstCfgInfoMeP2;

    pstCfgInfoOut0 = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoOut0, 0 , sizeof(VPSS_CFG_INFO_S));

    pstCfgInfoOut3 = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoOut3, 0 , sizeof(VPSS_CFG_INFO_S));

    pstCfgInfoRgme = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoRgme, 0 , sizeof(VPSS_CFG_INFO_S));

    pstCfgInfoMe = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoMe, 0 , sizeof(VPSS_CFG_INFO_S));

    pstCfgInfoMeCf = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoMeCf, 0 , sizeof(VPSS_CFG_INFO_S));

    pstCfgInfoMeP2 = (VPSS_CFG_INFO_S *)malloc(sizeof(VPSS_CFG_INFO_S));
    memset(pstCfgInfoMeP2, 0 , sizeof(VPSS_CFG_INFO_S));

    if (bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    XDP_PRINT("VPSS IP Config Check Start:\n");

    if (pReg->VPSS_CTRL.bits.hfr_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_CTRL.bits.cccl_en == 0);
    }
    VPSS_HFR_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_CCCL_ConfigCheck          ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_VC1_ConfigCheck           ( pReg, XDP_VC1_ID_CF, pstCfgInfo, u32ExtInfo);
    VPSS_SCD_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);

    if ((pReg->VPSS_CTRL.bits.dei_en == 1) || (pstCfgInfo->u32Wth < 160) || (pstCfgInfo->u32Hgt < 64))
    {
        XDP_ASSERT(pReg->VPSS_NR_REF_CTRL.bits.nr_ref_dcmp_mode == 0);
        XDP_ASSERT(pReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_cmp_mode == 0);
        XDP_ASSERT(pReg->VPSS_FCMP_NR_CFY_Y_GLB_INFO.bits.nr_cfy_cmp_en == 0);
    }
    XDP_ASSERT(pReg->VPSS_FCMP_NR_CFY_Y_GLB_INFO.bits.nr_cfy_cmp_en == pReg->VPSS_FCMP_NR_CFC_C_GLB_INFO.bits.nr_cfc_cmp_en);

    XDP_ASSERT(pReg->VPSS_FDCMP_NR_REFY_FHD_Y_GLB_INFO.bits.nr_refy_dcmp_en == pReg->VPSS_FDCMP_NR_REFC_FHD_C_GLB_INFO.bits.nr_refc_dcmp_en);
    if (pReg->VPSS_FDCMP_NR_REFY_FHD_Y_GLB_INFO.bits.nr_refy_dcmp_en == 0)
    {
        XDP_ASSERT(pReg->VPSS_NR_REF_CTRL.bits.nr_ref_dcmp_mode == 0);
    }
    if (pReg->VPSS_FDCMP_NR_REFY_FHD_Y_GLB_INFO.bits.nr_refy_dcmp_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_NR_REF_CTRL.bits.nr_ref_dcmp_mode == 3);
    }

    XDP_ASSERT(pReg->VPSS_FCMP_NR_RFRY_FHD_Y_GLB_INFO.bits.nr_rfry_cmp_en == pReg->VPSS_FCMP_NR_RFRC_FHD_C_GLB_INFO.bits.nr_rfrc_cmp_en);
    if (pReg->VPSS_FCMP_NR_RFRY_FHD_Y_GLB_INFO.bits.nr_rfry_cmp_en == 0)
    {
        XDP_ASSERT(pReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_cmp_mode == 0);
    }
    if (pReg->VPSS_FCMP_NR_RFRY_FHD_Y_GLB_INFO.bits.nr_rfry_cmp_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_NR_RFR_CTRL.bits.nr_rfr_cmp_mode == 3);
    }
    VPSS_TNR_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);

    memcpy(pstCfgInfoRgme, pstCfgInfo, sizeof(VPSS_CFG_INFO_S));

    VPSS_DEI_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_SNR_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_HSP_ConfigCheck           ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_HCTI_ConfigCheck          ( pReg, 0, pstCfgInfo, u32ExtInfo);
    VPSS_VCTI_ConfigCheck          ( pReg, 0, pstCfgInfo, u32ExtInfo);

    memcpy(pstCfgInfoOut0, pstCfgInfo, sizeof(VPSS_CFG_INFO_S));
    memcpy(pstCfgInfoOut3, pstCfgInfo, sizeof(VPSS_CFG_INFO_S));

    VPSS_OUT3_PZME_ConfigCheck     ( pReg, 0, pstCfgInfoOut3, u32ExtInfo);
    VPSS_OUT0_PZME_ConfigCheck     ( pReg, 0, pstCfgInfoOut0, u32ExtInfo);

    if ((pReg->VPSS_HIPP_VCTI_CTRL.bits.vcti_vcti_en == 1) || (pstCfgInfoOut0->u32Wth < 160) || (pstCfgInfoOut0->u32Hgt < 64))
    {
        XDP_ASSERT(pReg->VPSS_OUT0_CTRL.bits.out0_cmp_mode == 0);
    }

    if (pReg->VPSS_FCMP_OUT0_4K_GLB_INFO.bits.out0_cmp_en == 0)
    {
        XDP_ASSERT(pReg->VPSS_OUT0_CTRL.bits.out0_cmp_mode == 0);
    }
    if (pReg->VPSS_FCMP_OUT0_4K_GLB_INFO.bits.out0_cmp_en == 1)
    {
        XDP_ASSERT(pReg->VPSS_OUT0_CTRL.bits.out0_cmp_mode == 3);
    }



    XDP_ASSERT(pReg->VPSS_CTRL.bits.meds_en == pReg->VPSS_WR0_HDS_ZME_HSP.bits.vpss_wr0_hds_lhfir_en);
    VPSS_HZME_ConfigCheck          ( pReg, XDP_ZME_ID_VPSS_WR0_HDS_HZME, pstCfgInfoRgme, u32ExtInfo);
    VPSS_RGME_ConfigCheck          ( pReg, 0, pstCfgInfoRgme, u32ExtInfo);

    memcpy(pstCfgInfoMe, pstCfgInfoRgme, sizeof(VPSS_CFG_INFO_S));

    VPSS_HZME_ConfigCheck          ( pReg, XDP_ZME_ID_VPSS_WR1_HVDS_HZME, pstCfgInfoRgme, u32ExtInfo);
    VPSS_VZME_ConfigCheck          ( pReg, XDP_ZME_ID_VPSS_WR1_HVDS_VZME, pstCfgInfoRgme, u32ExtInfo);

    u64ScanPnextAddr = ((HI_U64)pReg->SCAN_START_ADDR_H.u32 << 20) + pReg->SCAN_START_ADDR_L.u32;
    u32CfgChkScanCnt = 0;
    while (u64ScanPnextAddr != 0)
    {
        pRegScan = (S_VPSS_REGS_TYPE *)((HI_U32 *)pReg + VPSS_MAX_REGS_NUM_IN_ONE_SCAN * u32CfgChkScanCnt);
        if (u32CfgChkScanCnt > 0)
        {
            pRegScanPre = (S_VPSS_REGS_TYPE *)((HI_U32 *)pReg + VPSS_MAX_REGS_NUM_IN_ONE_SCAN * (u32CfgChkScanCnt - 1));
        }

        pstCfgInfoMeCf->u32Format      = pRegScan->VPSS_ME_CF_CTRL.bits.me_cf_format;
        pstCfgInfoMeCf->u32Prio        = 0;
        pstCfgInfoMeCf->u32Img2d3dMode = 0;
        pstCfgInfoMeCf->u32Pro         = pRegScan->VPSS_ME_CF_CTRL.bits.me_cf_lm_rmode == 1 ? 1 : 0;
        pstCfgInfoMeCf->u32Even        = 0;
        pstCfgInfoMeCf->u32Bfield      = pRegScan->VPSS_ME_CF_CTRL.bits.me_cf_lm_rmode % 2;
        pstCfgInfoMeCf->u32PreMultEn   = 0;
        pstCfgInfoMeCf->u32CompValid   = 0xffffffff;
        pstCfgInfoMeCf->u32Wth         = pRegScan->VPSS_ME_CF_SIZE.bits.me_cf_width  + 1;
        pstCfgInfoMeCf->u32Hgt         = pRegScan->VPSS_ME_CF_SIZE.bits.me_cf_height + 1;

        if (pstCfgInfoMeCf->u32Format == XDP_PROC_FMT_SP_400)
        {
            pstCfgInfoMeCf->u32Format = XDP_PROC_FMT_SP_420;
        }
        if (pstCfgInfoMeCf->u32Pro == 0)
        {
            pstCfgInfoMeCf->u32Hgt /= 2;
        }

        pstCfgInfoMeP2->u32Format      = pRegScan->VPSS_ME_REF_CTRL.bits.me_ref_format;
        pstCfgInfoMeP2->u32Prio        = 0;
        pstCfgInfoMeP2->u32Img2d3dMode = 0;
        pstCfgInfoMeP2->u32Pro         = pstCfgInfoMeCf->u32Pro;
        pstCfgInfoMeP2->u32Even        = 0;
        pstCfgInfoMeP2->u32Bfield      = pstCfgInfoMeCf->u32Bfield;
        pstCfgInfoMeP2->u32PreMultEn   = 0;
        pstCfgInfoMeP2->u32CompValid   = 0xffffffff;
        pstCfgInfoMeP2->u32Wth         = pRegScan->VPSS_ME_REF_SIZE.bits.me_ref_width  + 1;
        pstCfgInfoMeP2->u32Hgt         = pRegScan->VPSS_ME_REF_SIZE.bits.me_ref_height + 1;

        if (pstCfgInfoMeP2->u32Format == XDP_PROC_FMT_SP_400)
        {
            pstCfgInfoMeP2->u32Format = XDP_PROC_FMT_SP_420;
        }
        if (pstCfgInfoMeP2->u32Pro == 0)
        {
            pstCfgInfoMeP2->u32Hgt /= 2;
        }

        VPSS_VC1_ConfigCheck       ( pRegScan, XDP_VC1_ID_ME_CF, pstCfgInfoMeCf, u32ExtInfo);
        VPSS_HZME_ConfigCheck      ( pRegScan, XDP_ZME_ID_VPSS_ME_CF_HDS_HZME, pstCfgInfoMeCf, u32ExtInfo);
        VPSS_HZME_ConfigCheck      ( pRegScan, XDP_ZME_ID_VPSS_ME_P2_HDS_HZME, pstCfgInfoMeP2, u32ExtInfo);
        VPSS_ME_ConfigCheck        ( pRegScan, 0, pstCfgInfoMe, u32ExtInfo);
        if (u32CfgChkScanCnt > 0)
        {
            VPSS_Scan_ConfigCheck      (pRegScanPre , pRegScan);
        }

        u64ScanPnextAddr  = ((HI_U64)pRegScan->SCAN_PNEXT_ADDR_H.u32 << 20) + pRegScan->SCAN_PNEXT_ADDR_L.u32;
        u32CfgChkScanCnt += 1;
    }

    XDP_PRINT("VPSS IP Config Check End!\n");

    free(pstCfgInfoOut0);
    free(pstCfgInfoOut3);
    free(pstCfgInfoRgme);
    free(pstCfgInfoMe);
    free(pstCfgInfoMeCf);
    free(pstCfgInfoMeP2);

#endif
    return HI_SUCCESS;
}

