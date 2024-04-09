/******************************************************************************
*
* Copyright (C) 2014-2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_comm.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#include "hi_drv_mem.h"
#include "pq_hal_comm.h"
#include "hi_osal.h"


#define VPSS_REGS_ADDR    0xf8cb0000UL
#define VDP_REGS_ADDR     0xf8cc0000UL
#define SPECIAL_REGS_ADDR 0xfffe0000UL

#define VPSS_PQ_REG_SIZE(start, end)\
    (offsetof(S_CAS_REGS_TYPE, end) + sizeof(HI_U32) -\
     offsetof(S_CAS_REGS_TYPE, start))

#define VDP_PQ_REG_SIZE(start, end)\
    (offsetof(S_VDP_REGS_TYPE, end) + sizeof(HI_U32) -\
     offsetof(S_VDP_REGS_TYPE, start))


/* VPSS/VDP ���ؼĴ��������ڳ�ʼ������*/
static S_CAS_REGS_TYPE *sg_pstVPSSRegLocal = NULL;
static S_VDP_REGS_TYPE *sg_pstVDPRegLocal  = NULL;

/* VPSS/VDP ����Ĵ������������ò���*/
static S_CAS_REGS_TYPE    *sg_pstVPSSRegMem[VPSS_HANDLE_NUM]    = {NULL};
static S_VPSSWB_REGS_TYPE *sg_pstVPSSWbcRegMem[VPSS_HANDLE_NUM] = {NULL};
static S_VDP_REGS_TYPE    *sg_pstVDPRegMem = NULL;

/* VPSSģ�鿪�ز���*/
static PQ_HAL_MODULE_S *sg_pstPQModuleLocal = NULL;
static PQ_HAL_MODULE_S *sg_pstPQModuleMem   = NULL;

/* PQ HAL��ʼ����־λ*/
static HI_BOOL sg_bHALInit = HI_FALSE;

/* ��ӡʹ�ܿ��� */
static HI_U32 sg_PrintType = PQ_PRN_NOTHING;

/* ��ӡ�м������ݴ����� */
static HI_S8  sg_PrintMsg[1024];


/**
 \brief ��ʼ��HALģ�飬���뱾�ؼĴ����ڴ�;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32  PQ_HAL_Init(HI_VOID)
{
    if (HI_TRUE == sg_bHALInit)
    {
        return HI_SUCCESS;
    }
#ifndef  __PQ_PLATFORM_BOOT__

    sg_pstVPSSRegLocal = (S_CAS_REGS_TYPE *)PQ_KMALLOC(sizeof(S_CAS_REGS_TYPE), GFP_KERNEL);
    if (sg_pstVPSSRegLocal == HI_NULL)
    {
        HI_ERR_PQ("sg_pstVPSSRegLocal can not kmalloc!\n");

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }
    PQ_SAFE_MEMSET(sg_pstVPSSRegLocal, 0, sizeof(S_CAS_REGS_TYPE));

    sg_pstVDPRegLocal = (S_VDP_REGS_TYPE *)PQ_KMALLOC(sizeof(S_VDP_REGS_TYPE), GFP_KERNEL);
    if (sg_pstVDPRegLocal == HI_NULL)
    {
        PQ_KFREE_SAFE(sg_pstVPSSRegLocal);

        HI_ERR_PQ("sg_pstVDPRegLocal can not kmalloc!\n");

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }
    PQ_SAFE_MEMSET(sg_pstVDPRegLocal, 0, sizeof(S_VDP_REGS_TYPE));

    sg_pstPQModuleLocal = (PQ_HAL_MODULE_S *)PQ_KMALLOC(sizeof(PQ_HAL_MODULE_S), GFP_KERNEL);
    if (sg_pstPQModuleLocal == HI_NULL)
    {
        PQ_KFREE_SAFE(sg_pstVPSSRegLocal);
        PQ_KFREE_SAFE(sg_pstVDPRegLocal);

        HI_ERR_PQ("sg_pstPQModuleLocal can not kmalloc!\n");

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }
    PQ_SAFE_MEMSET(sg_pstPQModuleLocal, 0, sizeof(PQ_HAL_MODULE_S));
#endif

    sg_bHALInit = HI_TRUE;

    return HI_SUCCESS;
}

/**
 \brief ȥ��ʼ��HALģ��,�ͷű��ؼĴ����ڴ�;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32  PQ_HAL_Deinit(HI_VOID)
{
    HI_S32 i;

    if (HI_FALSE == sg_bHALInit)
    {
        return HI_SUCCESS;
    }
#ifndef  __PQ_PLATFORM_BOOT__
    PQ_KFREE_SAFE(sg_pstVPSSRegLocal);
    PQ_KFREE_SAFE(sg_pstVDPRegLocal);
    PQ_KFREE_SAFE(sg_pstPQModuleLocal);
#endif
    sg_pstVPSSRegLocal  = NULL;
    sg_pstVDPRegLocal   = NULL;
    sg_pstPQModuleLocal = NULL;

    for (i = 0; i < VPSS_HANDLE_NUM; i++)
    {
        sg_pstVPSSRegMem[i]    = NULL;
        sg_pstVPSSWbcRegMem[i] = NULL;
    }
    sg_pstVDPRegMem   = NULL;
    sg_pstPQModuleMem = NULL;

    sg_bHALInit = HI_FALSE;

    return HI_SUCCESS;
}


/**
 \brief ����VPSS PQ;
 \attention \n
  ��

 \param[in] *pDstVpssAddr  : Ŀ���ַ
 \param[in] *pSrcVpssAddr  :Դ��ַ
 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_UpdateVpssPQ(S_CAS_REGS_TYPE *pDstVpssAddr, S_CAS_REGS_TYPE *pSrcVpssAddr)
{
    HI_U32 u32RegSize;

    PQ_CHECK_NULL_PTR_RE_NULL(pDstVpssAddr);
    PQ_CHECK_NULL_PTR_RE_NULL(pSrcVpssAddr);

    /* DEI */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DIELMA2, VPSS_DIEDIR12_14 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DIELMA2),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DIELMA2), u32RegSize);

    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DIEINTPSCL0, VPSS_CCRSCLR1);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DIEINTPSCL0),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DIEINTPSCL0), u32RegSize);

#if defined(CHIP_TYPE_hi3798cv200_a)||defined(CHIP_TYPE_hi3798cv200_b)
    /* iglb_en */
    pDstVpssAddr->VPSS_CTRL.bits.iglb_en = pSrcVpssAddr->VPSS_CTRL.bits.iglb_en;

    /* FMD */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_PDPHISTTHD1, VPSS_PDREGION );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_PDPHISTTHD1),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_PDPHISTTHD1), u32RegSize);

    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c;
    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_l      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_c      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_c;

    /* DR */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DR_CTRL, VPSS_DROVTSTRLUT2 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DR_CTRL),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DR_CTRL), u32RegSize);

    /* DB */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DB_CTRL, VPSS_DB_LUT10 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DB_CTRL),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_CTRL), u32RegSize);
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DBD_THDEDGE, VPSS_DBD_BLKSIZE );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DBD_THDEDGE),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DBD_THDEDGE), u32RegSize);
    //u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DB_BORD_FLAG[0], VPSS_DB_BORD_FLAG[127] );
    u32RegSize = sizeof(pSrcVpssAddr->VPSS_DB_BORD_FLAG);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DB_BORD_FLAG[0]),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_BORD_FLAG[0]), u32RegSize);

    /* SD DR */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DR_CFG0, VPSS_DNR_INFO);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DR_CFG0),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DR_CFG0), u32RegSize);

    /* VPSS CTRL DNR DB DR   dr_en\db_en\SD dr_en control by vpss*/
    /*
    pDstVpssAddr->VPSS_CTRL.bits.dnr_en = pSrcVpssAddr->VPSS_CTRL.bits.dnr_en;
    pDstVpssAddr->VPSS_CTRL.bits.db_en  = pSrcVpssAddr->VPSS_CTRL.bits.db_en;
    pDstVpssAddr->VPSS_CTRL.bits.dr_en  = pSrcVpssAddr->VPSS_CTRL.bits.dr_en;
    */

    /* HSHARPEN */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_HSPCFG1, VPSS_HSPCFG2);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_HSPCFG1),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_HSPCFG1), u32RegSize);
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_HSPCFG3, VPSS_HSPCFG6);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_HSPCFG3),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_HSPCFG3), u32RegSize);
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_HSPCFG7, VPSS_HSPCFG10);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_HSPCFG7),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_HSPCFG7), u32RegSize);

    //pDstVpssAddr->VPSS_CTRL.bits.hsp_en = pSrcVpssAddr->VPSS_CTRL.bits.hsp_en;
#endif

#if defined(CHIP_TYPE_hi3716mv410)||defined(CHIP_TYPE_hi3716mv420)
    /* iglb_en */
    pDstVpssAddr->VPSS_CTRL.bits.iglb_en = pSrcVpssAddr->VPSS_CTRL.bits.iglb_en;
    /* TNR */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_TNR_MODE, VPSS_TNR_TE_YCMT_MAPPING_K2 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_MODE),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_MODE), u32RegSize);
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_TNR_TE_YCEG_MAPPING_CTRL, VPSS_TNR_EDGE_CMOVING_CK );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_TE_YCEG_MAPPING_CTRL),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_TE_YCEG_MAPPING_CTRL), u32RegSize);
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_TNR_CLUT10, VPSS_TNR_CLUT67 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_CLUT10),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_CLUT10), u32RegSize);

    /* FMD */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_PDPHISTTHD1, VPSS_PDREGION );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_PDPHISTTHD1),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_PDPHISTTHD1), u32RegSize);

    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c;
    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_l      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_c      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_c;

    /* DM */
    pDstVpssAddr->VPSS_DB_CTRL.bits.dm_en = pSrcVpssAddr->VPSS_DB_CTRL.bits.dm_en;

    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DM_DIR, VPSS_DM_LUT4 );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DM_DIR),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DM_DIR), u32RegSize);

    /* DB */
    pDstVpssAddr->VPSS_DB_CTRL.bits.db_lum_ver_en          = pSrcVpssAddr->VPSS_DB_CTRL.bits.db_lum_ver_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.db_lum_hor_en          = pSrcVpssAddr->VPSS_DB_CTRL.bits.db_lum_hor_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.db_chr_ver_en          = pSrcVpssAddr->VPSS_DB_CTRL.bits.db_chr_ver_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.db_chr_hor_en          = pSrcVpssAddr->VPSS_DB_CTRL.bits.db_chr_hor_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.db_chr_hor_mid_grey_en = pSrcVpssAddr->VPSS_DB_CTRL.bits.db_chr_hor_mid_grey_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.dbm_demo_en            = pSrcVpssAddr->VPSS_DB_CTRL.bits.dbm_demo_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.dbm_demo_mode          = pSrcVpssAddr->VPSS_DB_CTRL.bits.dbm_demo_mode;
    pDstVpssAddr->VPSS_DB_CTRL.bits.det_size_en            = pSrcVpssAddr->VPSS_DB_CTRL.bits.det_size_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.det_hy_en              = pSrcVpssAddr->VPSS_DB_CTRL.bits.det_hy_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.det_hc_en              = pSrcVpssAddr->VPSS_DB_CTRL.bits.det_hc_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.det_vy_en              = pSrcVpssAddr->VPSS_DB_CTRL.bits.det_vy_en;
    pDstVpssAddr->VPSS_DB_CTRL.bits.dbm_out_mode           = pSrcVpssAddr->VPSS_DB_CTRL.bits.dbm_out_mode;
    pDstVpssAddr->VPSS_DB_CTRL.bits.dbm_out_sel_gain       = pSrcVpssAddr->VPSS_DB_CTRL.bits.dbm_out_sel_gain;

    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DB_DIR, VPSS_DBD_BLKSIZE );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DB_DIR),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_DIR), u32RegSize);

    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DB_BORD_FLAG[0], VPSS_DB_BORD_FLAG[128] );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DB_BORD_FLAG),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_BORD_FLAG), u32RegSize);

    /* VPSS CTRL DB DM dbm_en control by vpss*/
    /*
    pDstVpssAddr->VPSS_CTRL.bits.dbm_en = pSrcVpssAddr->VPSS_CTRL.bits.dbm_en;
    */
#endif

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    /* FMD */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_PDPHISTTHD1, VPSS_PDREGION );
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_PDPHISTTHD1),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_PDPHISTTHD1), u32RegSize);

    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_c;
    pDstVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l = pSrcVpssAddr->VPSS_DIECTRL.bits.die_out_sel_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_l      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_l;
    pDstVpssAddr->VPSS_PDCTRL.bits.dir_mch_c      = pSrcVpssAddr->VPSS_PDCTRL.bits.dir_mch_c;

    /* DR */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DR_CFG0, VPSS_DR_CFG1);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DR_CFG0),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DR_CFG0), u32RegSize);

    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_DNR_INFO, VPSS_DNR_INFO);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_DNR_INFO),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_DNR_INFO), u32RegSize);

    pDstVpssAddr->VPSS_CTRL.bits.dr_en = pSrcVpssAddr->VPSS_CTRL.bits.dr_en;

    /* SHARPEN:LTI,CTI */
    u32RegSize = VPSS_PQ_REG_SIZE(VPSS_VHD_LTI_CTRL, VPSS_VHD_CTI_THD);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVpssAddr->VPSS_VHD_LTI_CTRL),
                   (HI_VOID *)(&pSrcVpssAddr->VPSS_VHD_LTI_CTRL), u32RegSize);
#endif
}


/**
 \brief ����VDP PQ;
 \attention \n
  ��

 \param[in] *pDstVdpAddr  : Ŀ���ַ
 \param[in] *pSrcVdpAddr  :Դ��ַ
 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_UpdateVdpPQ(S_VDP_REGS_TYPE *pDstVdpAddr, S_VDP_REGS_TYPE *pSrcVdpAddr)
{
    HI_U32 u32RegSize;

    PQ_CHECK_NULL_PTR_RE_NULL(pDstVdpAddr);
    PQ_CHECK_NULL_PTR_RE_NULL(pSrcVdpAddr);

    /* ACM */
    u32RegSize = VDP_PQ_REG_SIZE(VP0_ACM_CTRL, VP0_ACM_ADJ);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->VP0_ACM_CTRL),
                   (HI_VOID *)(&pSrcVdpAddr->VP0_ACM_CTRL), u32RegSize);
    pDstVdpAddr->VP0_ACM_CAD.bits.coef_addr = pSrcVdpAddr->VP0_ACM_CAD.bits.coef_addr;
    pDstVdpAddr->VP0_PARAUP.bits.vp0_acmcoef_upd = pSrcVdpAddr->VP0_PARAUP.bits.vp0_acmcoef_upd;

    /* DCI */
    u32RegSize = VDP_PQ_REG_SIZE(VP0_DCICTRL, VP0_DCIADJSW10);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->VP0_DCICTRL),
                   (HI_VOID *)(&pSrcVdpAddr->VP0_DCICTRL), u32RegSize);
    pDstVdpAddr->VP0_DCI_CAD.bits.coef_addr = pSrcVdpAddr->VP0_DCI_CAD.bits.coef_addr;
    pDstVdpAddr->VP0_PARAUP.bits.vp0_acccoef_upd = pSrcVdpAddr->VP0_PARAUP.bits.vp0_acccoef_upd;

#if defined(CHIP_TYPE_hi3798cv200_a)||defined(CHIP_TYPE_hi3798cv200_b)
    /* SR */
    u32RegSize = VDP_PQ_REG_SIZE(SR_CTRL, SR_SMOOTH);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->SR_CTRL),
                   (HI_VOID *)(&pSrcVdpAddr->SR_CTRL), u32RegSize);
    u32RegSize = VDP_PQ_REG_SIZE(SR_RINGDT0, SR_DIR_CTRL);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->SR_RINGDT0),
                   (HI_VOID *)(&pSrcVdpAddr->SR_RINGDT0), u32RegSize);
#endif

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    /* SR */
    u32RegSize = VDP_PQ_REG_SIZE(SR_CTRL, SR_SMOOTH);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->SR_CTRL),
                   (HI_VOID *)(&pSrcVdpAddr->SR_CTRL), u32RegSize);
#endif

#if defined(CHIP_TYPE_hi3716mv410)||defined(CHIP_TYPE_hi3716mv420)
    /* Sharpen */
    u32RegSize = VDP_PQ_REG_SIZE(SPCTRL, SPEDGEEI);
    PQ_SAFE_MEMCPY((HI_VOID *)(&pDstVdpAddr->SPCTRL),
                   (HI_VOID *)(&pSrcVdpAddr->SPCTRL), u32RegSize);
#endif

    return;
}

/**
 \brief ����VPSS�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo  :VPSSͨ����
 \param[in] *pstVPSSReg  :  �������������ļĴ���ָ��

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVpssReg(HI_U32 u32HandleNo, S_CAS_REGS_TYPE *pstVPSSReg, S_VPSSWB_REGS_TYPE *pstVPSSWbcReg)
{
    HI_BOOL bReload = HI_FALSE;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    if (sg_pstVPSSWbcRegMem[u32HandleNo] != pstVPSSWbcReg)
    {
        sg_pstVPSSWbcRegMem[u32HandleNo] = pstVPSSWbcReg;
    }

    if (sg_pstVPSSRegMem[u32HandleNo] != pstVPSSReg)
    {
        sg_pstVPSSRegMem[u32HandleNo] = pstVPSSReg;
        bReload = HI_TRUE;
    }

    if (sg_pstVPSSRegMem[u32HandleNo] != NULL && bReload == HI_TRUE)
    {
        PQ_HAL_UpdateVpssPQ(sg_pstVPSSRegMem[u32HandleNo], sg_pstVPSSRegLocal);
    }

    return HI_SUCCESS;
}

/**
 \brief ����VDP�Ĵ���;
 \attention \n
  ��

 \param[in] *pstVDPReg  :��������������VPSS�Ĵ���ָ��

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVdpReg(S_VDP_REGS_TYPE *pstVDPReg)
{
    HI_BOOL bReload = HI_FALSE;

    if (sg_pstVDPRegMem != pstVDPReg)
    {
        sg_pstVDPRegMem = pstVDPReg;
        bReload = HI_TRUE;
    }

    if (sg_pstVDPRegMem != NULL && bReload == HI_TRUE)
    {
        PQ_HAL_UpdateVdpPQ(sg_pstVDPRegMem, sg_pstVDPRegLocal);
    }

    return HI_SUCCESS;
}

/**
 \brief ����PQ Module���ز���;
 \attention \n
  ��

 \param[in] *pstPQModule

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdatePQModule(PQ_HAL_MODULE_S *pstPQModule)
{
    HI_BOOL bReload = HI_FALSE;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPQModule);

    if (sg_pstPQModuleMem != pstPQModule)
    {
        sg_pstPQModuleMem = pstPQModule;
        bReload = HI_TRUE;
    }

    if (sg_pstPQModuleMem != NULL && bReload == HI_TRUE)
    {
        PQ_SAFE_MEMCPY(sg_pstPQModuleMem, sg_pstPQModuleLocal, sizeof(PQ_HAL_MODULE_S));
    }

    return HI_SUCCESS;
}

/**
 \brief ���VPSS��ǰu32HandleNo��Ӧ����Ĵ����Ƿ���Ч;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::HI_S32

 */
HI_S32 PQ_HAL_CheckVpssValid(HI_U32 u32HandleNo)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    /* NULL means RegMem has been clear */
    if (sg_pstVPSSRegMem[u32HandleNo] == NULL)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/**
 \brief ���VDP�Ĵ����Ƿ���Ч;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_S32

 */
HI_S32 PQ_HAL_CheckVdpValid(HI_VOID)
{
    if (sg_pstVDPRegMem == NULL)
    {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

/**
 \brief ��ȡVPSS��ǰ�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::VPSS�Ĵ���ָ��

 */
S_CAS_REGS_TYPE *PQ_HAL_GetVpssReg(HI_U32 u32HandleNo)
{
    S_CAS_REGS_TYPE *pstVPSSReg = HI_NULL;

    if (u32HandleNo >= VPSS_HANDLE_NUM)
    {
        HI_ERR_PQ("VPSS HandleNo=%d is over range!\n", u32HandleNo);
        return NULL;
    }

    if (sg_pstVPSSRegMem[u32HandleNo] == NULL)
    {
        pstVPSSReg = sg_pstVPSSRegLocal;
    }
    else
    {
        pstVPSSReg = sg_pstVPSSRegMem[u32HandleNo];
    }

    return pstVPSSReg;
}


/**
 \brief ��ȡVPSS WBC INFO;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::VPSS WBC INFO

 */
S_VPSSWB_REGS_TYPE *PQ_HAL_GetVpssWbcReg(HI_U32 u32HandleNo)
{
    S_VPSSWB_REGS_TYPE *pstVPSSWbcReg = HI_NULL;

    if (u32HandleNo >= VPSS_HANDLE_NUM)
    {
        HI_ERR_PQ("VPSS HandleNo=%d is over range!\n", u32HandleNo);
        return NULL;
    }

    if (sg_pstVPSSWbcRegMem[u32HandleNo] != HI_NULL)
    {
        pstVPSSWbcReg = sg_pstVPSSWbcRegMem[u32HandleNo];
    }
    else
    {
        HI_ERR_PQ("ERROR: VPSS Wbc REG is null point!\n");
    }

    return pstVPSSWbcReg;
}


/**
 \brief ��ȡVDP��ǰ�Ĵ���;
 \attention \n
  ��

 \param[in] none

 \retval ::VDP�Ĵ���ָ��

 */
S_VDP_REGS_TYPE *PQ_HAL_GetVdpReg(HI_VOID)
{
    S_VDP_REGS_TYPE *pstVDPReg = NULL;

    if (sg_pstVDPRegMem == NULL)
    {
        pstVDPReg = sg_pstVDPRegLocal;
    }
    else
    {
        pstVDPReg = sg_pstVDPRegMem;
    }

    return pstVDPReg;
}

/**
 \brief ��ȡPQ Module���ز���;
 \attention \n
  ��

 \param[in] none

 \retval ::PQ Module�Ĵ���ָ��

 */
PQ_HAL_MODULE_S *PQ_HAL_GetPQModule(HI_VOID)
{
    PQ_HAL_MODULE_S *pstPQModule = NULL;

    if (sg_pstPQModuleMem == NULL)
    {
        pstPQModule = sg_pstPQModuleLocal;
    }
    else
    {
        pstPQModule = sg_pstPQModuleMem;
    }

    return pstPQModule;
}

/**
 \brief д�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo
 \param[in] u32RegAddr
 \param[in] u32Value

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_WriteRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32 u32Value)
{
    S_CAS_REGS_TYPE *pstVPSSReg = HI_NULL;
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    HI_U32 u32OffsetAddr = 0x0;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    u32OffsetAddr = u32RegAddr & REG_OFFSET_ADDR_MASK;

    if ((PQ_HAL_IsVpssReg(u32RegAddr) == HI_SUCCESS) && (u32HandleNo < VPSS_HANDLE_NUM))
    {
        pstVPSSReg = PQ_HAL_GetVpssReg(u32HandleNo);
        if (pstVPSSReg == HI_NULL)
        {
            HI_ERR_PQ("VPSS REG is null point!\n");
            return HI_FAILURE;
        }
        *(HI_U32 *)((HI_VOID *)pstVPSSReg + u32OffsetAddr) = u32Value;
    }
    else if (PQ_HAL_IsVdpReg(u32RegAddr) == HI_SUCCESS)
    {
        pstVDPReg = PQ_HAL_GetVdpReg();
        if (pstVDPReg == HI_NULL)
        {
            HI_ERR_PQ("VDP REG is null point!\n");
            return HI_FAILURE;
        }
        *(HI_U32 *)((HI_VOID *)pstVDPReg + u32OffsetAddr) = u32Value;
    }
    else
    {}

    return HI_SUCCESS;
}

/* ���Ĵ��� */
HI_S32 PQ_HAL_ReadRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32 *pu32Value)
{
    S_CAS_REGS_TYPE *pstVPSSReg = HI_NULL;
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    HI_U32 u32OffsetAddr = 0x0;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    u32OffsetAddr = u32RegAddr & REG_OFFSET_ADDR_MASK;

    if ((PQ_HAL_IsVpssReg(u32RegAddr) == HI_SUCCESS) && (u32HandleNo < VPSS_HANDLE_NUM))
    {
        pstVPSSReg = PQ_HAL_GetVpssReg(u32HandleNo);
        if (pstVPSSReg == NULL)
        {
            HI_ERR_PQ("VPSS REG is null point!\n");
            return HI_FAILURE;
        }
        *pu32Value = *((HI_U32 *)((HI_VOID *)pstVPSSReg + u32OffsetAddr));
    }
    else if (PQ_HAL_IsVdpReg(u32RegAddr) == HI_SUCCESS)
    {
        pstVDPReg = PQ_HAL_GetVdpReg();
        if (pstVDPReg == NULL)
        {
            HI_ERR_PQ("VDP REG is null point!\n");
            return HI_FAILURE;
        }
        *pu32Value = *((HI_U32 *)((HI_VOID *)pstVDPReg + u32OffsetAddr));
    }
    else
    {}

    return HI_SUCCESS;
}

/* ������ʼBITλ����U32���� */
HI_VOID PQ_HAL_CopyU32ByBit(HI_U32 u32Src, HI_U32 u32SrcStartBit, HI_U32 *pu32Dst, HI_U32 u32DstStartBit, HI_U32 u32Num)
{
    HI_U32 u32SrcTmp = 0;
    HI_U32 u32DstTmp = 0;
    HI_U32 u32DstTmpLow  = 0;
    HI_U32 u32DstTmpHigh = 0;

    PQ_CHECK_NUM_OVER_RANGE_RE_NULL(u32SrcStartBit + u32Num, 32);
    PQ_CHECK_NUM_OVER_RANGE_RE_NULL(u32DstStartBit + u32Num, 32);

    /* ����src��Ҫ������u32Num��bits�����ƶ���dstָ����λ��; ����λ��0 */
    u32SrcTmp = u32Src << (32 - u32SrcStartBit - u32Num);

    /* ��ָ����u32Numλ�Ƶ���bitλ�� */
    u32SrcTmp = u32SrcTmp >> (32 - u32Num);
    u32SrcTmp = u32SrcTmp << u32DstStartBit;

    /* ����dst��0bit��u32DstStartBitλ */
    u32DstTmpLow = *pu32Dst << (32 - u32DstStartBit); /* ����λ��0 */
    u32DstTmpLow = u32DstTmpLow >> (32 - u32DstStartBit);

    /* ����dst��u32DstStartBit + u32Numλ��32bit */
    u32DstTmpHigh = *pu32Dst >> (u32DstStartBit + u32Num);
    u32DstTmpHigh = u32DstTmpHigh << (u32DstStartBit + u32Num);

    /* ������ */
    u32DstTmp = u32DstTmpHigh | u32SrcTmp | u32DstTmpLow;
    *pu32Dst = u32DstTmp;

    return ;
}

/**
 \brief ����bitλ����U32����
 \attention \n
  ��

 \param[in] pulData,ucBitNo;

 \retval ::HI_SUCCESS

 */
HI_VOID  PQ_HAL_U32SetBit( HI_U32 *pulData, HI_U8 ucBitNo)
{
    HI_U32 ulBitsMask, ulData;

    PQ_CHECK_NUM_OVER_RANGE_RE_NULL(ucBitNo, 31);

    /* Bits Mask */
    ulBitsMask = 0x00000001;
    ulBitsMask = ulBitsMask << ucBitNo;

    ulData   = *pulData;
    *pulData = ulData | ulBitsMask;
}

/**
 \brief ��U32��Ӧ��bitλ����
 \attention \n
  ��

 \param[in] pulData,ucBitNo;

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_U32ClearBit( HI_U32 *pulData, HI_U8 ucBitNo)
{
    HI_U32 ulBitsMask, ulData;

    PQ_CHECK_NUM_OVER_RANGE_RE_NULL(ucBitNo, 31);

    /* Bits Mask */
    ulBitsMask = 0x00000001;
    ulBitsMask = ulBitsMask << ucBitNo;

    ulData   = *pulData;
    *pulData = ulData & (~ulBitsMask);
}

/**
 \brief ��U32�����������λ����ͻ�ȡ��Ӧ��ֵ
 \attention \n
  ��

 \param[in]  ulData,  ucMaxBit,  ucMinBit;

 \retval ::HI_U32

 */
HI_U32 PQ_HAL_GetU32ByBit( HI_U32 ulData, HI_U8 ucMaxBit, HI_U8 ucMinBit)
{
    HI_U8 ucFlagEr = HI_FALSE;

    if (ucMaxBit < ucMinBit)
    {
        ucFlagEr = HI_TRUE;
    }

    if (ucMaxBit > 31 || ucMinBit > 31)
    {
        ucFlagEr = HI_TRUE;
    }

    if (ucFlagEr == HI_TRUE)
    {
        HI_ERR_PQ("NTDRIVER_BITS_u32GetData bit over range!\n");
        return ucFlagEr;
    }

    ulData = ulData << (31 - ucMaxBit);
    ulData = ulData >> (31 - ucMaxBit);
    ulData = (ulData >> ucMinBit);
    return ulData;
}

/**
 \brief �������λ�����λ����U32������Ӧ��ֵ
 \attention \n
  ��

 \param[in] pulData, ucMaxBit, ucMinBit, ulValue;

 \retval ::none

 */
HI_VOID PQ_HAL_SetU32ByBit( HI_U32 *pulData, HI_U8 ucMaxBit, HI_U8 ucMinBit, HI_U32 ulValue)
{
    HI_U8 ucFlagEr = HI_FALSE;
    HI_U32 ulBitsMask, ulData;

    if (ucMaxBit < ucMinBit)
    {
        ucFlagEr = HI_TRUE;
    }

    if (ucMaxBit > 31 || ucMinBit > 31)
    {
        ucFlagEr = HI_TRUE;
    }

    if (ucFlagEr == HI_TRUE)
    {
        HI_ERR_PQ("NTDRIVER_BITS_u32SetData bit over range!\n");
        return;
    }

    /* Bits Mask */
    ulBitsMask = 0xFFFFFFFF;
    ulBitsMask = ulBitsMask >> ucMinBit;
    ulBitsMask = ulBitsMask << (31 - ucMaxBit + ucMinBit);
    ulBitsMask = ulBitsMask >> (31 - ucMaxBit);

    ulData   = *pulData;
    ulData   = ulData & (~ulBitsMask);
    ulValue  = (ulValue << ucMinBit) & ulBitsMask;
    *pulData = ulData | ulValue;
}

HI_S32 PQ_HAL_IsVpssReg(HI_U32 u32RegAddr)
{
    if ((u32RegAddr & REG_BASE_ADDR_MASK) == VPSS_REGS_ADDR)
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 PQ_HAL_IsVdpReg(HI_U32 u32RegAddr)
{
    if ((u32RegAddr & REG_BASE_ADDR_MASK) == VDP_REGS_ADDR)
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 PQ_HAL_IsSpecialReg(HI_U32 u32RegAddr)
{
    if ((u32RegAddr & REG_BASE_ADDR_MASK) == SPECIAL_REGS_ADDR)
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_U32 PQ_HAL_RegRead(volatile HI_U32 a)
{
    return (*((HI_U32 *)a));
}

HI_VOID PQ_HAL_RegWrite(volatile HI_U32 a, HI_U32 value)
{
    *((HI_U32 *)a) = value;

    return;
}

HI_S32 PQ_REG_RegWrite(volatile HI_U32 *a, HI_U32 b)
{
    *a = b;

    return HI_SUCCESS;
}

HI_U32 PQ_REG_RegRead(volatile HI_U32 *a)
{
    return (*(a));
}

HI_S32 PQ_HAL_PrintMsg(HI_U32 type, const HI_S8 *format, ...)
{
    va_list args;
    HI_S32  nTotalChar = 0;

    /* ��Ϣ���͹��� */
    if ((PQ_PRN_ALWS != type) && (0 == (sg_PrintType & type))) /* ������ӡû�д� */
    {
        return HI_FAILURE;
    }
    /* ����Ϣ��ӡ���ַ��� */
    va_start( args, format );
    nTotalChar = HI_OSAL_Vsnprintf( sg_PrintMsg, sizeof(sg_PrintMsg), format, args );
    va_end( args );

    if ((nTotalChar <= 0) || (nTotalChar >= 1023))
    {
        return HI_FAILURE;
    }

#ifdef PQ_PROC_CTRL_SUPPORT
    HI_PRINT("%s", sg_PrintMsg);
#endif

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetPrintType(HI_U32 type)
{
    sg_PrintType = type;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetVpssDitherEn(HI_U32 u32HandleNo, HI_BOOL *bOnOff)
{
#if defined(CHIP_TYPE_hi3798cv200_a)||defined(CHIP_TYPE_hi3798cv200_b)
    S_CAS_REGS_TYPE *pstVpssVirReg = HI_NULL;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssVirReg);

    *bOnOff = pstVpssVirReg->VPSS_VHD0CTRL.bits.vhd0_dither_en;
#endif
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetDnrDitherEn(HI_U32 u32HandleNo, HI_BOOL *bOnOff)
{
#if defined(CHIP_TYPE_hi3798cv200_a)||defined(CHIP_TYPE_hi3798cv200_b)
    S_CAS_REGS_TYPE *pstVpssVirReg = HI_NULL;

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    pstVpssVirReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssVirReg);

    *bOnOff = pstVpssVirReg->VPSS_DNR_INFO.bits.dnr_dither_en;
#endif
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetVdpDitherEn(HI_BOOL *bOnOff)
{
#if defined(CHIP_TYPE_hi3798cv200_a)||defined(CHIP_TYPE_hi3798cv200_b)
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_WBC_DHD0_DITHER_CTRL WBC_DHD0_DITHER_CTRL;

    pstVdpReg = PQ_HAL_GetVdpReg();
    WBC_DHD0_DITHER_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->WBC_DHD0_DITHER_CTRL.u32));/* VDP_LAYER_WBC_HD0 */
    *bOnOff = WBC_DHD0_DITHER_CTRL.bits.dither_en;
#endif
    return HI_SUCCESS;
}



