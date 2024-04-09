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
  Author        : sdk sdk
  Created       : 2013/10/15
  Description   :

******************************************************************************/
#include "pq_hal_comm.h"
#ifndef HI_BUILD_IN_BOOT
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"
#include "hi_osal.h"
#else
#include "hi_common.h"
#include "hi_drv_pdm.h"
#endif

#ifndef HI_BUILD_IN_BOOT

/* VPSS/VDP ���ؼĴ��������ڳ�ʼ������*/
static S_CAS_REGS_TYPE *sg_pstVPSSRegLocal = NULL;
static S_VDP_REGS_TYPE *sg_pstVDPRegLocal  = NULL;

/* VPSS/VDP ����Ĵ������������ò���*/
static S_CAS_REGS_TYPE    *sg_pstVPSSRegMem[VPSS_HANDLE_NUM]    = {NULL};
static S_VPSSWB_REGS_TYPE *sg_pstVPSSWbcRegMem[VPSS_HANDLE_NUM] = {NULL};
static S_VDP_REGS_TYPE    *sg_pstVDPRegMem = NULL;

/* PQ HAL��ʼ����־λ*/
static HI_BOOL sg_bHALInit = HI_FALSE;

/* ��ӡʹ�ܿ��� */
static HI_U32 sg_PrintType = PQ_PRN_NOTHING;

/* ��ӡ�м������ݴ����� */
static HI_S8  sg_PrintMsg[1024];

#if defined(CHIP_TYPE_hi3798cv200)
PQ_MMZ_BUF_S     g_stIPSelAlgBuffer;
S_VDP_REGS_TYPE *g_pstIPSelVdpAlg = HI_NULL;
#endif

#if defined(SHARPEN_CFG_STYLE_COEF)
PQ_MMZ_BUF_S g_stSharpCfgBuff;
#endif


void pq_alg_memset(void *s, char ch, unsigned long size)
{
    memset(s, ch, size);
}

void pq_alg_memcpy(void *dest, const void *src, unsigned long size)
{
    memcpy(dest, src, size);
}

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
        HI_ERR_PQ("sg_pstVDPRegLocal can not kmalloc!\n");
        PQ_KFREE_SAFE(sg_pstVPSSRegLocal);

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }

    PQ_SAFE_MEMSET(sg_pstVDPRegLocal, 0, sizeof(S_VDP_REGS_TYPE));

#if defined(CHIP_TYPE_hi3798cv200)
    PQ_SAFE_MEMSET(&g_stIPSelAlgBuffer, 0, sizeof(PQ_MMZ_BUF_S));
    if (HI_SUCCESS != PQ_HAL_MMZ_AllocAndMap("PQ_IPSEL_ALG", HI_NULL, sizeof(S_VDP_REGS_TYPE), 0, &g_stIPSelAlgBuffer))
    {
        HI_ERR_PQ("PQ_IPSEL_ALG memory allocated failed!\n");
        PQ_KFREE_SAFE(sg_pstVPSSRegLocal);
        PQ_KFREE_SAFE(sg_pstVDPRegLocal);

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }
    g_pstIPSelVdpAlg = (S_VDP_REGS_TYPE *)g_stIPSelAlgBuffer.pu8StartVirAddr;
#endif

#if defined(SHARPEN_CFG_STYLE_COEF)
    PQ_SAFE_MEMSET(&g_stSharpCfgBuff, 0, sizeof(PQ_MMZ_BUF_S));
    if (HI_SUCCESS != PQ_HAL_MMZ_AllocAndMap("PQ_VDP_SHARP_CFG", HI_NULL, 0x1000, 0, &g_stSharpCfgBuff))
    {
        HI_ERR_PQ("PQ_VDP_SHARP_CFG Alloc failed\n");
        PQ_KFREE_SAFE(sg_pstVPSSRegLocal);
        PQ_KFREE_SAFE(sg_pstVDPRegLocal);

        sg_bHALInit = HI_FALSE;

        return HI_FAILURE;
    }

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
    HI_U32 i;

    if (HI_FALSE == sg_bHALInit)
    {
        return HI_SUCCESS;
    }

    PQ_KFREE_SAFE(sg_pstVPSSRegLocal);
    PQ_KFREE_SAFE(sg_pstVDPRegLocal);

    for (i = 0; i < VPSS_HANDLE_NUM; i++)
    {
        sg_pstVPSSRegMem[i]    = NULL;
        sg_pstVPSSWbcRegMem[i] = NULL;
    }

    sg_pstVDPRegMem   = NULL;

#if defined(CHIP_TYPE_hi3798cv200)
    if (HI_NULL != g_stIPSelAlgBuffer.pu8StartVirAddr)
    {
        PQ_HAL_MMZ_UnmapAndRelease(&g_stIPSelAlgBuffer);
        g_pstIPSelVdpAlg = HI_NULL;
    }
#endif

#if defined(SHARPEN_CFG_STYLE_COEF)
    if (HI_NULL != g_stSharpCfgBuff.pu8StartVirAddr)
    {
        PQ_HAL_MMZ_UnmapAndRelease(&g_stSharpCfgBuff);
        g_stSharpCfgBuff.pu8StartVirAddr = HI_NULL;
    }
#endif

    sg_bHALInit = HI_FALSE;

    return HI_SUCCESS;
}


HI_VOID PQ_HAL_CopyRegBySize(HI_U32 *pDstReg, HI_U32 *pSrcReg, HI_U32 u32RegSize)
{
    HI_U32 i = 0;

    for (i = 0; i < u32RegSize; i++)
    {
        PQ_HAL_RegWrite((HI_U32 *)(pDstReg + i), (*(pSrcReg + i)));
    }

    return;
}


/**
 \brief ����VPSS PQ;
 \attention \n
  ��

 \param[in] *pDstVpssAddr  :Ŀ���ַ
 \param[in] *pSrcVpssAddr  :Դ��ַ
 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_UpdateVpssPQ(S_CAS_REGS_TYPE *pDstVpssAddr, S_CAS_REGS_TYPE *pSrcVpssAddr)
{
    HI_U32 u32ByteSize = 0;

    HI_UNUSED(u32ByteSize);
    PQ_CHECK_NULL_PTR_RE_NULL(pDstVpssAddr);
    PQ_CHECK_NULL_PTR_RE_NULL(pSrcVpssAddr);

#ifdef PQ_ALG_DB
    /* DB */
#if defined(CHIP_TYPE_hi3798cv200)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DB_CTRL, VPSS_DB_CTRL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DB_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DB_LUT34, VPSS_DB_LUT40);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DB_LUT34),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_LUT34), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DB_LUT44, VPSS_DB_THR3);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DB_LUT44),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_LUT44), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DBD_THDEDGE, VPSS_DBD_BLKSIZE);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DBD_THDEDGE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DBD_THDEDGE), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DB_CTRL, VPSS_DB_LUT6);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DB_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DBD_THDEDGE, VPSS_DBD_FLAT);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DBD_THDEDGE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DBD_THDEDGE), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DB_CTRL, VPSS_DB_LUT6);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DB_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DB_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DBD_THDEDGE, VPSS_DBD_FLAT);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DBD_THDEDGE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DBD_THDEDGE), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    /* add db ctrl and demo info */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_CTRL, VPSS_DB_ADPT);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DBD_THDEDGE, VPSS_DBD_FLAT);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DBD_THDEDGE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DBD_THDEDGE), u32ByteSize / 4);
#endif
#endif

#ifdef PQ_ALG_DM
    /* DM */
#if defined(CHIP_TYPE_hi3798cv200)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DM_DIR, VPSS_DM_THR2);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DM_DIR),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DM_DIR), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DM_DIR, VPSS_DM_LUT11);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DM_DIR),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DM_DIR), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DM_DIR, VPSS_DM_LUT11);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DM_DIR),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DM_DIR), u32ByteSize / 4);

#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    /* add dm ctrl and demo info */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_CTRL, VPSS_DBM_DEMO);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DM_DIR, VPSS_DM_TRANS_WID);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DM_DIR),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DM_DIR), u32ByteSize / 4);
#endif
#endif


#ifdef PQ_ALG_DEI
    /* DEI */
#if defined(CHIP_TYPE_hi3798cv200)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DIECTRL, VPSS_DIEMCGBMCOEF1);
#elif defined(CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300)||defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DIECTRL, VPSS_DIEKMAG2);
#elif defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DIECTRL, VPSS_DIE_S3ADD);

#endif
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DIECTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DIECTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_MCDI_RGDIFY, VPSS_MCDI_DEMO);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_MCDI_RGDIFY),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_MCDI_RGDIFY), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_FMD
    /* FMD */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_PDPCCMOV, VPSS_PDREGION);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_PDPCCMOV),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_PDPCCMOV), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_TNR
    /* TNR */
#if defined(CHIP_TYPE_hi3798cv200)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_MODE, VPSS_TNR_TE_YCMT_MAPPING_K2 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_MODE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_MODE), u32ByteSize / 4);
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_TE_YCEG_MAPPING_CTRL, VPSS_TNR_EDGE_CMOVING_CK );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_TE_YCEG_MAPPING_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_TE_YCEG_MAPPING_CTRL), u32ByteSize / 4);
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_CLUT10, VPSS_TNR_CLUT67 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_CLUT10),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_CLUT10), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_CONTRL, VPSS_TNR_CMOTIONSTR_LUT31 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_CONTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_CONTRL), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_CONTRL, VPSS_TNR_CBLENDING_LUT7 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_CONTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_CONTRL), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    /* add tnr ctrl  */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_CTRL, VPSS_SNR_CTRL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_TNR_CONTRL, VPSS_TNR_CMOTIONSTR_LUT31 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_TNR_CONTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_TNR_CONTRL), u32ByteSize / 4);
#endif
#endif

#ifdef PQ_ALG_SNR
    /* SNR */
#if defined(CHIP_TYPE_hi3798cv200)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_ENABLE, VPSS_SNR_DEMO);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_ENABLE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_ENABLE), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(MOTION_EDGE_LUT_01a, MOTION_EDGE_LUT_16h);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->MOTION_EDGE_LUT_01a),
                         (HI_VOID *)(&pSrcVpssAddr->MOTION_EDGE_LUT_01a), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(COLOR_BASED_LUT_01a, COLOR_BASED_LUT_16d);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->COLOR_BASED_LUT_01a),
                         (HI_VOID *)(&pSrcVpssAddr->COLOR_BASED_LUT_01a), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3798mv200)||defined(CHIP_TYPE_hi3798mv300)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_ENABLE, MOTION_EDGE_LUT_32);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_ENABLE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_ENABLE), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_ENABLE, MOTION_EDGE_LUT_32);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_ENABLE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_ENABLE), u32ByteSize / 4);
#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    /* add tnr ctrl  */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_CTRL, VPSS_SNR_CTRL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_SNR_ENABLE, MOTION_EDGE_LUT_32);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_SNR_ENABLE),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_SNR_ENABLE), u32ByteSize / 4);
#endif

#endif

#ifdef PQ_ALG_DERING
    /* DERING */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DR_CTRL, VPSS_DR_THR26);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DR_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DR_CTRL), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_DESHOOT
    /* DESHOOT */
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_DS_CTRL, VPSS_DS_THR20);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_DS_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_DS_CTRL), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_VPSSCSC
    /* VPSS CSC */
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_FMTC_GAMMA_CSC_CTRL, VPSS_FMTC_GAMMA_CSC_CTRL);

    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_FMTC_GAMMA_CSC_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_FMTC_GAMMA_CSC_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_FMTC_CSC_COEF_0, VPSS_FMTC_CSC_COEF_7);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_FMTC_CSC_COEF_0),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_FMTC_CSC_COEF_0), u32ByteSize / 4);
#endif
#endif

#ifdef PQ_ALG_VPSSGAMMA
    /* VPSS gamma */
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_FMTC_GAMMA_CSC_CTRL, VPSS_FMTC_GAMMA_CSC_CTRL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_FMTC_GAMMA_CSC_CTRL),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_FMTC_GAMMA_CSC_CTRL), u32ByteSize / 4);

    u32ByteSize = VPSS_PQ_REG_SIZE(VPSS_FMTC_GAMMA_YLUT_0, VPSS_FMTC_GAMMA_VLUT_8);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVpssAddr->VPSS_FMTC_GAMMA_YLUT_0),
                         (HI_VOID *)(&pSrcVpssAddr->VPSS_FMTC_GAMMA_YLUT_0), u32ByteSize / 4);
#endif
#endif


    return;
}


/**
 \brief ����VDP PQ;
 \attention \n
  ��

 \param[in] *pDstVdpAddr  :Ŀ���ַ
 \param[in] *pSrcVdpAddr  :Դ��ַ
 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_UpdateVdpPQ(S_VDP_REGS_TYPE *pDstVdpAddr, S_VDP_REGS_TYPE *pSrcVdpAddr)
{
    HI_U32 u32ByteSize = 0;

    HI_UNUSED(u32ByteSize);

    PQ_CHECK_NULL_PTR_RE_NULL(pDstVdpAddr);
    PQ_CHECK_NULL_PTR_RE_NULL(pSrcVdpAddr);

#ifdef PQ_ALG_ARTDS
    /* DESHOOT */
    u32ByteSize = VDP_PQ_REG_SIZE(V0_ZME_SHOOTCTRL_HL, V0_ZME_SHOOTCTRL_HL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_ZME_SHOOTCTRL_HL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_ZME_SHOOTCTRL_HL), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_ZME_SHOOTCTRL_VL, V0_ZME_SHOOTCTRL_VL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_ZME_SHOOTCTRL_VL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_ZME_SHOOTCTRL_VL), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_ZME2_SHOOTCTRL_HL, V0_ZME2_SHOOTCTRL_HL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_ZME2_SHOOTCTRL_HL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_ZME2_SHOOTCTRL_HL), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_ZME2_SHOOTCTRL_VL, V0_ZME2_SHOOTCTRL_VL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_ZME2_SHOOTCTRL_VL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_ZME2_SHOOTCTRL_VL), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_SHARPEN
#if defined(CHIP_TYPE_hi3798mv310)
    u32ByteSize = VDP_PQ_REG_SIZE(SPCTRL, SPSHOOTRATIO);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->SPCTRL),
                         (HI_VOID *)(&pSrcVdpAddr->SPCTRL), u32ByteSize / 4);
#else
    u32ByteSize = VDP_PQ_REG_SIZE(SPCTRL, SPGRADCONTRAST);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->SPCTRL),
                         (HI_VOID *)(&pSrcVdpAddr->SPCTRL), u32ByteSize / 4);
#endif
#endif

#ifdef PQ_ALG_ACM
    u32ByteSize = VDP_PQ_REG_SIZE(VP0_ACM_CTRL, VP0_ACM_PARA_DATA);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->VP0_ACM_CTRL),
                         (HI_VOID *)(&pSrcVdpAddr->VP0_ACM_CTRL), u32ByteSize / 4);
    /* addr and reg update */
    pDstVdpAddr->VP0_ACM_CAD.bits.coef_addr      = pSrcVdpAddr->VP0_ACM_CAD.bits.coef_addr;
    pDstVdpAddr->VP0_PARAUP.bits.vp0_acmcoef_upd = pSrcVdpAddr->VP0_PARAUP.bits.vp0_acmcoef_upd;
#endif

#ifdef PQ_ALG_LCACM
    u32ByteSize = VDP_PQ_REG_SIZE(VHDACM0, VHDACM7);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->VHDACM0),
                         (HI_VOID *)(&pSrcVdpAddr->VHDACM0), u32ByteSize / 4);
#endif


#ifdef PQ_ALG_DCI
    u32ByteSize = VDP_PQ_REG_SIZE(VP0_DCICTRL, VP0_DCI_STATICS_DATA);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->VP0_DCICTRL),
                         (HI_VOID *)(&pSrcVdpAddr->VP0_DCICTRL), u32ByteSize / 4);
    /* addr and reg update */
    pDstVdpAddr->V0_DCICOEFAD.bits.dci_coef_addr = pSrcVdpAddr->V0_DCICOEFAD.bits.dci_coef_addr;
    pDstVdpAddr->V0_PARAUP.bits.v0_dcicoef_upd   = pSrcVdpAddr->V0_PARAUP.bits.v0_dcicoef_upd;
#endif

#ifdef PQ_ALG_ACC
    u32ByteSize = VDP_PQ_REG_SIZE(VHDACCTHD1, VHDACCTOTAL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->VHDACCTHD1),
                         (HI_VOID *)(&pSrcVdpAddr->VHDACCTHD1), u32ByteSize / 4);
#endif

#ifdef PQ_ALG_DB
#if !(defined(CHIP_TYPE_hi3798mv310))
    /* DB */
    u32ByteSize = VDP_PQ_REG_SIZE(V0_DB_CTRL, V0_DB_CTRL);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_DB_CTRL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_DB_CTRL), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_DB_LUT34, V0_DB_LUT40);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_DB_LUT34),
                         (HI_VOID *)(&pSrcVdpAddr->V0_DB_LUT34), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_DB_LUT44, V0_DB_THR3);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_DB_LUT44),
                         (HI_VOID *)(&pSrcVdpAddr->V0_DB_LUT44), u32ByteSize / 4);

    u32ByteSize = VDP_PQ_REG_SIZE(V0_DBD_THDEDGE, V0_DBD_BLKSIZE);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_DBD_THDEDGE),
                         (HI_VOID *)(&pSrcVdpAddr->V0_DBD_THDEDGE), u32ByteSize / 4);
#endif
#endif

#ifdef PQ_ALG_TNR
#if !(defined(CHIP_TYPE_hi3798mv310))
    /* TNR */
    u32ByteSize = VDP_PQ_REG_SIZE(V0_TNR_MODE, V0_TNR_TE_YCMT_MAPPING_K2 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_TNR_MODE),
                         (HI_VOID *)(&pSrcVdpAddr->V0_TNR_MODE), u32ByteSize / 4);
    u32ByteSize = VDP_PQ_REG_SIZE(V0_TNR_TE_YCEG_MAPPING_CTRL, V0_TNR_EDGE_CMOVING_CK );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_TNR_TE_YCEG_MAPPING_CTRL),
                         (HI_VOID *)(&pSrcVdpAddr->V0_TNR_TE_YCEG_MAPPING_CTRL), u32ByteSize / 4);
    u32ByteSize = VDP_PQ_REG_SIZE(V0_TNR_CLUT10, V0_TNR_CLUT67 );
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_TNR_CLUT10),
                         (HI_VOID *)(&pSrcVdpAddr->V0_TNR_CLUT10), u32ByteSize / 4);
#endif
#endif


#ifdef PQ_ALG_VDP4KSNR
    u32ByteSize = VDP_PQ_REG_SIZE(V0_SNR_ENABLE, V0_MOTION_EDGE_LUT_01h);
    PQ_HAL_CopyRegBySize((HI_VOID *)(&pDstVdpAddr->V0_SNR_ENABLE),
                         (HI_VOID *)(&pSrcVdpAddr->V0_SNR_ENABLE), u32ByteSize / 4);
#endif

    return;
}

/**
 \brief ����VPSS�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo  :VPSSͨ����
 \param[in] *pstVPSSReg  :�������������ļĴ���ָ��

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
        if (HI_TRUE == sg_bHALInit)
        {
            pstVPSSReg = sg_pstVPSSRegLocal;
        }
        else
        {
            pstVPSSReg = HI_NULL;
        }
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
        if (HI_TRUE == sg_bHALInit)
        {
            pstVDPReg = sg_pstVDPRegLocal;
        }
        else
        {
            pstVDPReg = HI_NULL;
        }
    }
    else
    {
        pstVDPReg = sg_pstVDPRegMem;
    }

    return pstVDPReg;
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
        HI_ERR_PQ("bit over range:maxbit[%d],minbit[%d]\n", ucMaxBit, ucMinBit);
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

#else
S_VDP_REGS_TYPE *PQ_HAL_GetVdpReg(HI_VOID)
{
    S_VDP_REGS_TYPE *pstVDPReg = NULL;

    pstVDPReg = (S_VDP_REGS_TYPE *)VDP_REGS_ADDR;

    return pstVDPReg;
}
#endif

HI_VOID PQ_HAL_RegWrite(volatile HI_U32 *a, HI_U32 value)
{
    *a = value;

#if defined(SHARPEN_CFG_STYLE_COEF)
    {
        HI_U32 addr = VDP_REGS_ADDR + (HI_U32)a - (HI_U32)(&(sg_pstVDPRegMem->VOCTRL.u32));
        if ((addr >= 0xf8cc7004) && (addr <= 0xf8cc704c))
        {
            addr = (addr - 0xf8cc7004 );
            *(volatile HI_U32 *)((HI_VOID *)(g_stSharpCfgBuff.pu8StartVirAddr) + addr) = value;
        }
    }
#endif

    return;
}

HI_U32 PQ_HAL_RegRead(volatile HI_U32 *a)
{
#if defined(SHARPEN_CFG_STYLE_COEF)
    HI_U32 addr = VDP_REGS_ADDR + (HI_U32)a - (HI_U32)(&(sg_pstVDPRegMem->VOCTRL.u32));
    if ((addr >= 0xf8cc7004) && (addr <= 0xf8cc704c))
    {
        addr = (addr - 0xf8cc7004 + (HI_U32)g_stSharpCfgBuff.pu8StartVirAddr);
        a = (volatile HI_U32 *)addr;
    }
#endif

    return (*a);
}


/*
�ڵײ����ĵط�����δ��ݸ�mmz��ʵ�ʸ�mmu��ַ����������λ�ò���
ʹ�õĵ�ַ����u32StartPhyAddr ������mmu ��u32StartSmmuAddr
*/

HI_S32 PQ_HAL_AllocAndMap(const HI_CHAR *pchBufName, HI_CHAR *pchZoneName, HI_U32 u32Size, HI_S32 s32Align, PQ_MMZ_BUF_S *pstMBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;

#ifndef HI_BUILD_IN_BOOT
#ifdef  HI_PQ_SMMU_SUPPORT
    SMMU_BUFFER_S stMMU;
    s32Ret = HI_DRV_SMMU_AllocAndMap( pchBufName, u32Size, 0, &stMMU);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("SMMU AllocAndMap Failed !!!\n");
        return HI_FAILURE;
    }

    pstMBuf->u32StartPhyAddr = stMMU.u32StartSmmuAddr;
    pstMBuf->pu8StartVirAddr = stMMU.pu8StartVirAddr;
    pstMBuf->u32Size         = stMMU.u32Size;

#else
    MMZ_BUFFER_S stMMZ;
    s32Ret = HI_DRV_MMZ_AllocAndMap(pchBufName, pchZoneName, u32Size, s32Align, &stMMZ);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("MMZ AllocAndMap Failed !!!\n");
        return HI_FAILURE;
    }

    pstMBuf->u32StartPhyAddr = stMMZ.u32StartPhyAddr;
    pstMBuf->pu8StartVirAddr = stMMZ.pu8StartVirAddr;
    pstMBuf->u32Size         = stMMZ.u32Size;

#endif
#else

    if (HI_SUCCESS == HI_DRV_PDM_AllocReserveMem(pchBufName, u32Size, &pstMBuf->u32StartPhyAddr))
    {
        pstMBuf->pu8StartVirAddr = (HI_U8 *)pstMBuf->u32StartPhyAddr; /*to do*/
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

#endif

    return s32Ret;
}


HI_VOID PQ_HAL_UnmapAndRelease(PQ_MMZ_BUF_S *pstMBuf)
{
#ifndef HI_BUILD_IN_BOOT

#ifdef HI_PQ_SMMU_SUPPORT
    SMMU_BUFFER_S stMMU;

    stMMU.u32StartSmmuAddr  = pstMBuf->u32StartPhyAddr;
    stMMU.pu8StartVirAddr   = pstMBuf->pu8StartVirAddr;
    stMMU.u32Size           = pstMBuf->u32Size;
    HI_DRV_SMMU_UnmapAndRelease(&stMMU);
#else
    MMZ_BUFFER_S stMMZ;

    stMMZ.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
    stMMZ.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
    stMMZ.u32Size         = pstMBuf->u32Size;

    HI_DRV_MMZ_UnmapAndRelease(&stMMZ);
#endif

#endif

    return;
}

HI_S32 PQ_HAL_MMZ_AllocAndMap(const HI_CHAR *pchBufName, HI_CHAR *pchZoneName, HI_U32 u32Size, HI_S32 s32Align, PQ_MMZ_BUF_S *pstMBuf)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifndef HI_BUILD_IN_BOOT
    MMZ_BUFFER_S stMMZ;

    s32Ret = HI_DRV_MMZ_AllocAndMap(pchBufName, pchZoneName, u32Size, s32Align, &stMMZ);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("MMZ AllocAndMap Failed !!!\n");
        return HI_FAILURE;
    }

    pstMBuf->u32StartPhyAddr = stMMZ.u32StartPhyAddr;
    pstMBuf->pu8StartVirAddr = stMMZ.pu8StartVirAddr;
    pstMBuf->u32Size         = stMMZ.u32Size;
#else
    s32Ret = HI_DRV_PDM_AllocReserveMem(pchBufName, u32Size, &pstMBuf->u32StartPhyAddr);
    if (HI_SUCCESS == s32Ret)
    {
        pstMBuf->pu8StartVirAddr = (HI_U8 *)pstMBuf->u32StartPhyAddr;
    }
    else
    {
        return HI_FAILURE;
    }
#endif

    return s32Ret;
}

HI_VOID PQ_HAL_MMZ_UnmapAndRelease(PQ_MMZ_BUF_S *pstMBuf)
{
#ifndef HI_BUILD_IN_BOOT
    MMZ_BUFFER_S stMMZ;

    stMMZ.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
    stMMZ.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
    stMMZ.u32Size         = pstMBuf->u32Size;
    HI_DRV_MMZ_UnmapAndRelease(&stMMZ);
#endif

    return;
}

