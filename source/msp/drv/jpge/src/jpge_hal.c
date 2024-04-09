/***************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name         : jpge_hal.c
Version           : Initial Draft
Author            :
Created           : 2018/01/01
Description       : CNcomment:  CNend\n
Function List     :


History           :
Date                           Author                  Modification
2018/01/01                     sdk                     Created file
****************************************************************************************************/


/*********************************add include here**************************************************/
#include <linux/delay.h>
#include <asm/cacheflush.h>
#include <linux/dma-direction.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "jpge_reg.h"
#include "jpge_hal.h"
#include "hi_reg_common.h"

#ifdef CONFIG_GFX_MMU_SUPPORT
#include "drv_tde_ext.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"
#include "hi_drv_module.h"
#endif

#include "drv_jpge_paracheck.h"
#include "hi_gfx_sys_k.h"


/***************************** Macro Definition ****************************************************/
static JPGE_ENC_INSTANCE_S  gs_pJpgeEncInstance[JPGE_MAX_INSTANCE_NUM];
static Jpge_IpCtx_S JpgeIpCtx;

#ifdef CONFIG_GFX_MMU_SUPPORT
static TDE_EXPORT_FUNC_S *gs_TdeExportFuncs = HI_NULL;
#endif


#define JPEG_TABL_MAX     64

/*************************** Structure Definition **************************************************/


/********************** Global Variable declaration ************************************************/

static const HI_U8 ZigZagScan[JPEG_TABL_MAX] =
{
      0,  1,  5,  6, 14, 15, 27, 28,
       2,  4,  7, 13, 16, 26, 29, 42,
       3,  8, 12, 17, 25, 30, 41, 43,
       9, 11, 18, 24, 31, 40, 44, 53,
      10, 19, 23, 32, 39, 45, 52, 54,
      20, 22, 33, 38, 46, 51, 55, 60,
      21, 34, 37, 47, 50, 56, 59, 61,
      35, 36, 48, 49, 57, 58, 62, 63
};

static const HI_U8 Jpge_Yqt[JPEG_TABL_MAX] =
{
    16, 11, 10, 16,  24,  40,  51,  61,
    12, 12, 14, 19,  26,  58,  60,  55,
    14, 13, 16, 24,  40,  57,  69,  56,
    14, 17, 22, 29,  51,  87,  80,  62,
    18, 22, 37, 56,  68, 109, 103,  77,
    24, 35, 55, 64,  81, 104, 113,  92,
    49, 64, 78, 87, 103, 121, 120, 101,
    72, 92, 95, 98, 112, 100, 103,  99
};
static const HI_U8 Jpge_Cqt[JPEG_TABL_MAX] =
{
    17, 18, 24, 47, 99, 99, 99, 99,
    18, 21, 26, 66, 99, 99, 99, 99,
    24, 26, 56, 99, 99, 99, 99, 99,
    47, 66, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99,
    99, 99, 99, 99, 99, 99, 99, 99
};


static const HI_U8 Jpge_JfifHdr[JPGE_MAX_HDR_LEN] =  /* 2(SOI)+18(APP0)+207(DQT)+19(SOF)+432(DHT)+6(DRI)+14(SOS) */
{
    0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00,
    0xff, 0xdb, 0x00, 0x43, 0x00, 0x10, 0x0b, 0x0c, 0x0e, 0x0c, 0x0a, 0x10, 0x0e, 0x0d, 0x0e, 0x12, 0x11, 0x10, 0x13, 0x18,
    0x28, 0x1a, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1d, 0x28, 0x3a, 0x33, 0x3d, 0x3c, 0x39, 0x33, 0x38, 0x37, 0x40,
    0x48, 0x5c, 0x4e, 0x40, 0x44, 0x57, 0x45, 0x37, 0x38, 0x50, 0x6d, 0x51, 0x57, 0x5f, 0x62, 0x67, 0x68, 0x67, 0x3e, 0x4d,
    0x71, 0x79, 0x70, 0x64, 0x78, 0x5c, 0x65, 0x67, 0x63, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x11, 0x12, 0x12, 0x18, 0x15, 0x18,
    0x2f, 0x1a, 0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xff, 0xdb,
    0x00, 0x43, 0x02, 0x11, 0x12, 0x12, 0x18, 0x15, 0x18, 0x2f, 0x1a, 0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x01, 0x20, 0x01, 0x60, 0x03, 0x01, 0x22, 0x00,
    0x02, 0x11, 0x01, 0x03, 0x11, 0x02, 0xff, 0xc4, 0x00, 0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff,
    0xc4, 0x00, 0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00, 0x02, 0x01,
    0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00, 0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05,
    0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1,
    0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54,
    0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
    0x79, 0x7a, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0xa2,
    0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
    0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5,
    0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00, 0xb5, 0x11,
    0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03,
    0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
    0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15, 0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17,
    0x18, 0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
    0x49, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8,
    0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda,
    0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xdd,
    0x00, 0x04, 0x00, 0x64, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00
};

extern HI_BOOL gs_JpgeDebugInterApi;
extern HI_BOOL gs_JpgeDebugUnf;

/********************** API forward declarations     ***********************************************/


/********************** API forward release          ***********************************************/
/**
 ** support
 ** JPGE_YUV420       0
 ** JPGE_YUV422       1
 ** JPGE_YUV444       2
 ***************************
 ** JPGE_SEMIPLANNAR  0
 ** JPGE_PLANNAR      1
 ** JPGE_PACKAGE      2
 **/
/***************************************************************************
* func          : jpge_issupport
* description   : check the para whether is ok
                  CNcomment: �жϱ����Ƿ�֧��           CNend\n
* param[in]     : pEncCfg     CNcomment: ������Ϣ       CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
****************************************************************************/
static HI_S32 jpge_issupport(Jpge_EncCfg_S *pEncCfg)
{
    HI_S32 CfgErr = 0;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncCfg, HI_FAILURE);

    CfgErr |= (pEncCfg->FrameWidth  < 16) | (pEncCfg->FrameWidth  > 4096);
    CfgErr |= (pEncCfg->FrameHeight < 16) | (pEncCfg->FrameHeight > 4096);

    CfgErr |= (pEncCfg->YuvStoreType  > JPGE_PACKAGE);
    CfgErr |= (pEncCfg->YuvStoreType  > JPGE_ROTATION_180);
    CfgErr |= (pEncCfg->YuvSampleType > JPGE_YUV444);

    CfgErr |= (pEncCfg->SlcSplitEn != 0);
    CfgErr |= (pEncCfg->Qlevel < 1) | (pEncCfg->Qlevel > 99);

    if (CfgErr)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func         : jpge_create_qttable
* description  : create qt table
                 CNcomment: ����������       CNend\n
* param[in]    : s32Q        CNcomment:            CNend\n
* param[in]    : pLumaQt     CNcomment:   ����     CNend\n
* param[in]    : pChromaQt   CNcomment:   ɫ��     CNend\n
* retval       : NA
* others:      : NA
****************************************************************************/
static HI_VOID jpge_create_qttable(HI_S32 s32Q, HI_U8* pLumaQt, HI_U8 *pChromaQt)
{
    HI_S32 i  = 0;
    HI_S32 lq = 0;
    HI_S32 cq = 0;
    HI_S32 factor = s32Q;
    HI_S32 q = s32Q;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_UNRETURN(pLumaQt);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pChromaQt);
    JPGE_CHECK_EQUAL_UNRETURN(0, s32Q);

    if (q < 50)
    {
        q = 5000 / factor;
    }
    else
    {
        q = 200 - factor * 2;
    }

    /** Calculate the new quantizer **/
    for (i = 0; i < JPEG_TABL_MAX; i++)
    {
        lq = (Jpge_Yqt[i] * q + 50) / 100;
        cq = (Jpge_Cqt[i] * q + 50) / 100;

        /** Limit the quantizers to 1 <= q <= 255 **/
        if (lq < 1)
        {
            lq = 1;
        }
        else if (lq > 255)
        {
            lq = 255;
        }

        pLumaQt[i] = lq;

        if (cq < 1)
        {
            cq = 1;
        }
        else if (cq > 255)
        {
            cq = 255;
        }
        pChromaQt[i] = cq;
    }

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}


/***************************************************************************
* func         : Jpge_StartOneFrame
* description  : begin encode
                 CNcomment: ����������Ϣ��ʼ֡���� CNend\n
* param[in]    : pstEncPara      CNcomment: ��������Ϣ     CNend\n
* param[in]    : pEncIn          CNcomment: ������Ϣ       CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
static HI_S32 Jpge_StartOneFrame(Jpge_EncPara_S *pstEncPara, Jpge_EncIn_S *pEncIn)
{
    HI_U32 JfifHdrLen = 0;
    HI_U32 BusBitBuf  = 0;
    HI_U32 TmpSize = 0;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_RETURN(pstEncPara, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn, HI_FAILURE);

    JfifHdrLen = pstEncPara->SlcSplitEn ? (JPGE_MAX_HDR_LEN) : ((JPGE_MAX_HDR_LEN) - 6);

    /**save hdr information **/
    BusBitBuf = pEncIn->BusOutBuf + JfifHdrLen;
    BusBitBuf += 64 - (BusBitBuf & 63);

    /** save encode data **/
    pstEncPara->StrmBufAddr   = BusBitBuf;      /** 64-byte aligned **/
    /** save encode data write pointer data,jpge enc not used **/
    pstEncPara->StrmBufRpAddr = BusBitBuf - 16; /* 16-byte aligned */
    /** save encode data read pointer data,jpge enc not used **/
    pstEncPara->StrmBufWpAddr = BusBitBuf - 32; /* 16-byte aligned */

    /** save encode data size **/
    TmpSize = BusBitBuf - pEncIn->BusOutBuf;
    if (pEncIn->OutBufSize <= TmpSize)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    pstEncPara->StrmBufSize = pEncIn->OutBufSize - TmpSize;
    pstEncPara->StrmBufSize &= 0xFFFFFF00;

    /** offset beyond user input encode out buffer **/
    /** ����û�����buffer��ʵ�ʱ���������ݵ�ƫ��λ�ã����������ַʹ�� **/
    pstEncPara->Vir2BusOffset = BusBitBuf - pEncIn->BusOutBuf;

#ifdef CONFIG_64BIT
    #ifdef CONFIG_SMP
        on_each_cpu((smp_call_func_t)flush_cache_all, NULL, 1);
    #else
        flush_cache_all();
    #endif
#else
    #ifdef CONFIG_SMP
        on_each_cpu((smp_call_func_t)__cpuc_flush_kern_all, NULL, 1);
    #else
        __cpuc_flush_kern_all();
    #endif
    outer_flush_all();
#endif

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func         : Jpge_StartOneFrame_toVenc
* description  : begin encode
                 CNcomment: ����������Ϣ��ʼ֡���� CNend\n
* param[in]    : pstEncPara      CNcomment: ��������Ϣ     CNend\n
* param[in]    : pEncIn          CNcomment: ������Ϣ       CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
static HI_S32 Jpge_StartOneFrame_toVenc(Jpge_EncPara_S  *pstEncPara, Venc2Jpge_EncIn_S *pEncIn)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_RETURN(pstEncPara, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn->pJpgeYqt, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn->pJpgeCqt, HI_FAILURE);

    if (copy_from_user(pstEncPara->JpgeYqt,pEncIn->pJpgeYqt,sizeof(HI_U8)*64))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user, HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = copy_from_user(pstEncPara->JpgeCqt,pEncIn->pJpgeCqt,sizeof(HI_U8)*64);
    if (Ret < 0)
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user, HI_FAILURE);
        return HI_FAILURE;
    }

    pstEncPara->SrcYAddr      = pEncIn->BusViY;
    pstEncPara->SrcCAddr      = pEncIn->BusViC;
    pstEncPara->SrcVAddr      = pEncIn->BusViV;
    pstEncPara->SrcYStride    = pEncIn->ViYStride;
    pstEncPara->SrcCStride    = pEncIn->ViCStride;
    pstEncPara->StrmBufAddr   = pEncIn->StrmBufAddr;      /* 64-byte aligned */
    pstEncPara->StrmBufRpAddr = pEncIn->StrmBufRpAddr;    /* 16-byte aligned */
    pstEncPara->StrmBufWpAddr = pEncIn->StrmBufWpAddr;    /* 16-byte aligned */

    pstEncPara->StrmBufSize   = pEncIn->StrmBufSize;
    pstEncPara->Vir2BusOffset = pEncIn->Vir2BusOffset;

    pstEncPara->YuvSampleType = pEncIn->YuvSampleType;
    pstEncPara->YuvStoreType  = pEncIn->YuvStoreType;
    pstEncPara->RotationAngle = pEncIn->RotationAngle;
    pstEncPara->PackageSel    = pEncIn->PackageSel;

    pstEncPara->PTS0          = pEncIn->PTS0;

    /**<support resolution change enc **/
    pstEncPara->PicWidth      = pEncIn->FrameWidth;
    pstEncPara->PicHeight     = pEncIn->FrameHeight;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}

/***************************************************************************
* func          : jpge_set_register
* description   : set jpeg encode register
                  CNcomment: ���ñ���Ĵ��� CNend\n
* param[in]     : pstEncPara       CNcomment: ����������     CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
static HI_VOID jpge_set_register(Jpge_EncPara_S  *pstEncPara)
{
    HI_S32 s32Cnt1 = 0;
    HI_S32 s32Cnt2 = 0;
    U_JPGE_INTMASK      u32INTMASK;
    U_JPGE_PICFG        u32PICFG;
    U_JPGE_ECSCFG       u32ECSCFG;
    U_JPGE_VEDIMGSIZE   u32VEDIMGSIZE;
    U_JPGE_SSTRIDE      u32STRIDE;
    U_JPGE_QPT          u32QPT;
    S_JPGE_REGS_TYPE  *pAllReg = NULL;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_UNRETURN(pstEncPara);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pstEncPara->pRegBase);
    pAllReg = (S_JPGE_REGS_TYPE*)pstEncPara->pRegBase;

    {
        u32INTMASK.u32 = 0;
        u32INTMASK.bits.VencEndOfPicMask = 1;
        u32INTMASK.bits.VencBufFullMask  = 1;
        pAllReg->JPGE_INTMASK.u32 = u32INTMASK.u32;
    }

    {/** pic cfg **/
        u32PICFG.u32 = 0;
        u32PICFG.bits.strFmt        = pstEncPara->YuvStoreType;
        u32PICFG.bits.yuvFmt        = pstEncPara->YuvSampleType;
        u32PICFG.bits.rotationAngle = pstEncPara->RotationAngle;
        u32PICFG.bits.packageSel    = pstEncPara->PackageSel & 0xFF;

        if (  (pstEncPara->RotationAngle == 1 || pstEncPara->RotationAngle == 2) \
           && (pstEncPara->YuvSampleType == 1))
        {/* 90 or 270 @ 422 */
            u32PICFG.bits.yuvFmt = 0;         /* change 422 to 420 */
        }

        /** revise by sdk **/
        u32PICFG.bits.memClkGateEn = 1;  //��mem �ſ�
        u32PICFG.bits.clkGateEn    = 2;  //ͬʱ��֡���ͺ�鼶ʱ���ſ�

        pAllReg->JPGE_PICFG.u32 = u32PICFG.u32;
    }


    {/** ecs cfg **/
        u32ECSCFG.u32 = 0;
        u32ECSCFG.bits.ecsSplit = pstEncPara->SlcSplitEn;
        u32ECSCFG.bits.ecsSize  = pstEncPara->SplitSize - 1;
        pAllReg->JPGE_ECSCFG.u32 = u32ECSCFG.u32;
    }


    {/** image size **/
        u32VEDIMGSIZE.u32 = 0;
        u32VEDIMGSIZE.bits.ImgWidthInPixelsMinus1  = pstEncPara->PicWidth  - 1;
        u32VEDIMGSIZE.bits.ImgHeightInPixelsMinus1 = pstEncPara->PicHeight - 1;
        pAllReg->JPGE_VEDIMGSIZE.u32 = u32VEDIMGSIZE.u32;
    }

    pAllReg->JPGE_SRCYADDR = pstEncPara->SrcYAddr;
    pAllReg->JPGE_SRCCADDR = pstEncPara->SrcCAddr;
    pAllReg->JPGE_SRCVADDR = pstEncPara->SrcVAddr;

    {
        u32STRIDE.u32 = 0;
        u32STRIDE.bits.SrcYStride = pstEncPara->SrcYStride;
        u32STRIDE.bits.SrcCStride = pstEncPara->SrcCStride;
        if (  (pstEncPara->RotationAngle == 1 || pstEncPara->RotationAngle == 2) \
           && (pstEncPara->YuvSampleType == 1)  )
        {/* 90 or 270 @ 422 */
            u32STRIDE.bits.SrcCStride = pstEncPara->SrcCStride << 1;  /* change 422 to 420 */
        }
        pAllReg->JPGE_SSTRIDE.u32 = u32STRIDE.u32;
    }

    /** output stream buffer **/
    pAllReg->JPGE_STRMADDR       = pstEncPara->StrmBufAddr;   /** �������buffer����ַ **/
    pAllReg->JPGE_SRPTRADDR      = pstEncPara->StrmBufRpAddr;
    pAllReg->JPGE_SWPTRADDR      = pstEncPara->StrmBufWpAddr;
    pAllReg->JPGE_STRMBUFLEN.u32 = pstEncPara->StrmBufSize;   /** �������buffer����   **/

    /** jpge dqt **/
    for(s32Cnt1 = 0; s32Cnt1 < 16; s32Cnt1++)
    {
        s32Cnt2 = (s32Cnt1 & 1) * 32 + (s32Cnt1 >> 1);
        u32QPT.bits.QP0 = pstEncPara->JpgeYqt[s32Cnt2     ];
        u32QPT.bits.QP1 = pstEncPara->JpgeYqt[s32Cnt2 + 8 ];
        u32QPT.bits.QP2 = pstEncPara->JpgeYqt[s32Cnt2 + 16];
        u32QPT.bits.QP3 = pstEncPara->JpgeYqt[s32Cnt2 + 24];
        pAllReg->JPGE_QPT[s32Cnt1].u32 = u32QPT.u32;

        u32QPT.bits.QP0 = pstEncPara->JpgeCqt[s32Cnt2     ];
        u32QPT.bits.QP1 = pstEncPara->JpgeCqt[s32Cnt2 + 8 ];
        u32QPT.bits.QP2 = pstEncPara->JpgeCqt[s32Cnt2 + 16];
        u32QPT.bits.QP3 = pstEncPara->JpgeCqt[s32Cnt2 + 24];
        pAllReg->JPGE_QPT[s32Cnt1+16].u32 = u32QPT.u32;

        u32QPT.bits.QP0 = pstEncPara->JpgeCqt[s32Cnt2     ];
        u32QPT.bits.QP1 = pstEncPara->JpgeCqt[s32Cnt2 + 8 ];
        u32QPT.bits.QP2 = pstEncPara->JpgeCqt[s32Cnt2 + 16];
        u32QPT.bits.QP3 = pstEncPara->JpgeCqt[s32Cnt2 + 24];

        pAllReg->JPGE_QPT[s32Cnt1 + 32].u32 = u32QPT.u32;

    }

    pAllReg->JPGE_PTS0 = pstEncPara->PTS0;
    pAllReg->JPGE_OUTSTD.u32 = 2;

    pAllReg->JPGE_START.u32 = 0;
    pAllReg->JPGE_START.u32 = 1;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}


/***************************************************************************
* func          : Jpge_ReadReg
* description   : ���Ĵ���
                  CNcomment:  CNend\n
* param[in]     : pstEncPara  CNcomment: ��������Ϣ   CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
static HI_VOID Jpge_ReadReg(Jpge_EncPara_S *pstEncPara)
{
    S_JPGE_REGS_TYPE *pAllReg  = NULL;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_UNRETURN(pstEncPara);
    JPGE_CHECK_NULLPOINTER_UNRETURN(pstEncPara->pRegBase);
    pAllReg  = (S_JPGE_REGS_TYPE *)pstEncPara->pRegBase;

    pstEncPara->EndOfPic  = pAllReg->JPGE_INTSTAT.bits.VencEndOfPic;
    pstEncPara->BufFull   = pAllReg->JPGE_INTSTAT.bits.VencBufFull;

    pAllReg->JPGE_INTCLR.u32 = 0xFFFFFFFF;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}

/***************************************************************************
* func          : Jpge_EndOneFrame
* description   : end encode jpeg frame
                  CNcomment:  ����һ֡��� CNend\n
* param[in]     : pstEncPara  CNcomment: ��������Ϣ         CNend\n
* param[in]     : pstEncIn    CNcomment: ������������Ϣ     CNend\n
* param[ou]     : pEncOut     CNcomment: ���������Ϣ       CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
static HI_S32 Jpge_EndOneFrame(Jpge_EncPara_S *pstEncPara, Jpge_EncIn_S *pstEncIn, Jpge_EncOut_S *pEncOut)
{
    HI_U32 TmpSize = 0;
    HI_U32 JfifHdrLen = 0;
    Jpge_NaluHdr_S pNaluHdr ={0};
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_RETURN(pstEncPara, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pstEncIn, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncOut, HI_FAILURE);

    JfifHdrLen = pstEncPara->SlcSplitEn ? (JPGE_MAX_HDR_LEN) : ((JPGE_MAX_HDR_LEN) - 6);

    JPGE_CHECK_NULLPOINTER_RETURN(pstEncIn->pOutBuf, HI_FAILURE);
    if (copy_from_user(&pNaluHdr,(HI_VOID*)((unsigned long)pstEncIn->pOutBuf + pstEncPara->Vir2BusOffset),sizeof(Jpge_NaluHdr_S)))
    {
        HI_GFX_LOG_PrintFuncErr(copy_from_user, HI_FAILURE);
        return -EFAULT;
    }

    if (pstEncPara->BufFull)
    {
        pEncOut->StrmSize  = 0;
        pEncOut->BusStream = 0;
        pEncOut->pStream   = NULL;
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

#if 0
     __cpuc_flush_kern_all(); // flush l1cache
     outer_flush_all(); // flush l2cache
#endif

    /** ���bufferǰ64���ֽ���������֡��Ϣ������֡��Ϣ����ʵ�����������С **/
    if (pNaluHdr.PacketLen < pNaluHdr.InvldByte)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    TmpSize = pNaluHdr.PacketLen - pNaluHdr.InvldByte;
    pEncOut->StrmSize  = TmpSize + JfifHdrLen - 64;

    if (pstEncPara->StrmBufAddr < JfifHdrLen)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }
    pEncOut->BusStream = pstEncPara->StrmBufAddr - JfifHdrLen + 64;

    if (pEncOut->BusStream < pstEncIn->BusOutBuf)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return -EFAULT;
    }
    pEncOut->pStream = (HI_U8 *)((unsigned long)pstEncIn->pOutBuf + (pEncOut->BusStream - pstEncIn->BusOutBuf));

    if (copy_to_user(pEncOut->pStream, pstEncPara->JfifHdr, JfifHdrLen))
    {
        HI_GFX_LOG_PrintFuncErr(copy_to_user, HI_FAILURE);
        return -EFAULT;
    }

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func          : Jpge_Isr
* description   : CNcomment: �жϺ��� CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
static HI_VOID Jpge_Isr(HI_VOID )
{
    Jpge_EncPara_S  *pEncPara = NULL;
    //HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_ARRAY_OVER_UNRETURN(JpgeIpCtx.CurrHandle - 1, JPGE_MAX_INSTANCE_NUM);
    pEncPara = &gs_pJpgeEncInstance[JpgeIpCtx.CurrHandle - 1].EncPara;

    Jpge_ReadReg(pEncPara);
    JpgeOsal_MutexUnlock(&pEncPara->IsrMutex);

    //HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}


/***************************************************************************
* func          : JPEG_ENC_Open
* description   : in insmod jpge inital call this function to do something
                  CNcomment: ��������ʱ������һЩ���� CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_Open( HI_VOID )
{
    HI_S32 s32Cnt = 0;
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_S32 s32Ret = HI_SUCCESS;
#endif
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    if (HI_FAILURE == JpgeOsal_IrqInit(JPGE_IRQ_ID, Jpge_Isr) )
    {
        HI_GFX_LOG_PrintFuncErr(JpgeOsal_IrqInit, HI_FAILURE);
        return HI_FAILURE;
    }

    JpgeIpCtx.pRegBase = (HI_U32*)JpgeOsal_MapRegisterAddr(JPGE_REG_BASE_ADDR, sizeof(S_JPGE_REGS_TYPE));
    if (NULL == JpgeIpCtx.pRegBase)
    {
       JpgeOsal_IrqFree(JPGE_IRQ_ID);
       HI_GFX_LOG_PrintFuncErr(JpgeOsal_MapRegisterAddr, HI_FAILURE);
       return HI_FAILURE;
    }

    JpgeOsal_LockInit (&JpgeIpCtx.ChnLock);
    JpgeOsal_MutexInit(&JpgeIpCtx.ChnMutex);

    for (s32Cnt = 0; s32Cnt < JPGE_MAX_INSTANCE_NUM; s32Cnt++)
    {
        gs_pJpgeEncInstance[s32Cnt].bEncInstanceNull = HI_TRUE;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_TDE, (HI_VOID**)&gs_TdeExportFuncs);
    if (HI_SUCCESS != s32Ret)
    {
        JpgeOsal_IrqFree(JPGE_IRQ_ID);
        JpgeOsal_UnmapRegisterAddr(JpgeIpCtx.pRegBase);
        JpgeIpCtx.pRegBase = NULL;
        HI_GFX_LOG_PrintFuncErr(HI_DRV_MODULE_GetFunction, HI_FAILURE);
        return HI_FAILURE;
    }

    if ((NULL == gs_TdeExportFuncs) || (NULL == gs_TdeExportFuncs->pfnTdeOpen))
    {
        JpgeOsal_IrqFree(JPGE_IRQ_ID);
        JpgeOsal_UnmapRegisterAddr(JpgeIpCtx.pRegBase);
        JpgeIpCtx.pRegBase = NULL;
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    s32Ret = gs_TdeExportFuncs->pfnTdeOpen();
    if (s32Ret < 0)
    {
        HI_PRINT("Tde open failed!\n");
        JpgeOsal_IrqFree(JPGE_IRQ_ID);
        JpgeOsal_UnmapRegisterAddr(JpgeIpCtx.pRegBase);
        JpgeIpCtx.pRegBase = NULL;
        HI_GFX_LOG_PrintFuncErr(pfnTdeOpen, HI_FAILURE);
        return HI_FAILURE;
    }
#endif

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func          : JPEG_ENC_Close
* description   : close irq and umap register
                  CNcomment: ж���жϺ�������ӳ��Ĵ�����ַ CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_Close( HI_VOID )
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_S32 Ret = HI_FAILURE;
#endif
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JpgeOsal_IrqFree(JPGE_IRQ_ID);

    if (NULL != JpgeIpCtx.pRegBase)
    {
       JpgeOsal_UnmapRegisterAddr(JpgeIpCtx.pRegBase);
       JpgeIpCtx.pRegBase = NULL;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_TDE, (HI_VOID**)&gs_TdeExportFuncs);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
        return HI_SUCCESS;
    }

    if ((NULL == gs_TdeExportFuncs) || (NULL == gs_TdeExportFuncs->pfnTdeClose))
    {
        HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
        return HI_SUCCESS;
    }
    gs_TdeExportFuncs->pfnTdeClose();
#endif

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func          : JPEG_ENC_CreateHandle
* description   : create jpeg encode handle
                  CNcomment: ������������� CNend\n
* retval        : NA
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_CreateHandle(HI_S32 *pEncHandle)
{
    HI_S32 s32Cnt = 0;
    JPGE_LOCK_FLAG flag = 0;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncHandle, HI_FAILURE);

    JpgeOsal_Lock(&JpgeIpCtx.ChnLock, &flag );
      for(s32Cnt = 0; s32Cnt < JPGE_MAX_INSTANCE_NUM; s32Cnt++)
      {
          if (HI_TRUE == gs_pJpgeEncInstance[s32Cnt].bEncInstanceNull)
          {
              break;
          }
      }
    JpgeOsal_Unlock( &JpgeIpCtx.ChnLock, &flag);

    if (JPGE_MAX_INSTANCE_NUM == s32Cnt)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    gs_pJpgeEncInstance[s32Cnt].bEncInstanceNull = HI_FALSE;

    *pEncHandle = (s32Cnt + 1);
    JpgeIpCtx.CurrHandle = (s32Cnt + 1);

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;
}

/***************************************************************************
* func         : JPEG_ENC_DestoryHandle
* description  : destory jpeg encode handle
                 CNcomment: ���ٱ�������� CNend\n
* retval       : NA
* others:      : NA
****************************************************************************/
static HI_S32 JPEG_ENC_DestoryHandle(HI_S32 EncHandle)
{
    HI_S32 s32Cnt = 0;
    Jpge_EncPara_S *pEncPara = NULL;
    JPGE_LOCK_FLAG flag = 0;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_ARRAY_OVER_RETURN(EncHandle - 1, JPGE_MAX_INSTANCE_NUM, HI_FAILURE);
    pEncPara = &gs_pJpgeEncInstance[EncHandle - 1].EncPara;

    JpgeOsal_Lock( &JpgeIpCtx.ChnLock, &flag );
        for(s32Cnt = 0; s32Cnt < JPGE_MAX_INSTANCE_NUM; s32Cnt++ )
        {
            if(pEncPara == &gs_pJpgeEncInstance[s32Cnt].EncPara )
            {
                gs_pJpgeEncInstance[s32Cnt].bEncInstanceNull = HI_TRUE;
                break;
            }
        }
    JpgeOsal_Unlock(&JpgeIpCtx.ChnLock, &flag );

    if (s32Cnt == JPGE_MAX_INSTANCE_NUM )
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;
}

/***************************************************************************
* func          : JPEG_ENC_Create
* description   : create jpeg encode handle
                  CNcomment: ����jpeg������ CNend\n
* param[in]     : *pEncHandle      CNcomment: ������������     CNend\n
* param[in]     : pEncCfg          CNcomment: ����ı�����Ϣ     CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_Create(Jpge_EncCfg_S *pEncCfg)
{
    Jpge_EncPara_S  *pEncPara = NULL;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncCfg, HI_FAILURE);
    JPGE_CHECK_ARRAY_OVER_RETURN(JpgeIpCtx.CurrHandle - 1, JPGE_MAX_INSTANCE_NUM, HI_FAILURE);

    if (HI_FAILURE == jpge_issupport(pEncCfg))
    {
        HI_GFX_LOG_PrintFuncErr(jpge_issupport, HI_FAILURE);
        return HI_FAILURE;
    }

    pEncPara = &gs_pJpgeEncInstance[JpgeIpCtx.CurrHandle - 1].EncPara;

    /* init mutex */
    JpgeOsal_MutexInit( &pEncPara->IsrMutex );
    JpgeOsal_MutexLock( &pEncPara->IsrMutex );

    /** Make JFIF header bitstream **/
    {
        HI_U32 w = pEncCfg->FrameWidth, t, i;
        HI_U32 h = pEncCfg->FrameHeight;

        HI_U8  dri[] = {0xff, 0xdd, 0x00, 0x04, 0x00, 0x64};
        HI_U8  sos[] = {0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00};

        for ( i = 0; i < JPGE_MAX_HDR_LEN; i++ )
        {
            pEncPara->JfifHdr[i] = Jpge_JfifHdr[i];
        }

        /* 420 422 or 444 */
        if (pEncCfg->YuvSampleType == JPGE_YUV420)
        {
            pEncPara->JfifHdr[238] = 0x22;
        }
        else if(pEncCfg->YuvSampleType == JPGE_YUV422)
        {
            pEncPara->JfifHdr[238] = 0x21;
        }
        else if( pEncCfg->YuvSampleType == JPGE_YUV444)
        {
            pEncPara->JfifHdr[238] = 0x11;
        }

        if (pEncCfg->RotationAngle == JPGE_ROTATION_90 || pEncCfg->RotationAngle == JPGE_ROTATION_270 )
        {
            if (pEncCfg->YuvSampleType == JPGE_YUV422)
            {/* 90 or 270 @ 422 */
                pEncPara->JfifHdr[238] = 0x22;       /* change 422 to 420 */
            }
            t = w; w = h; h = t;
        }
        /* img size */
        pEncPara->JfifHdr[232] = h >> 8; pEncPara->JfifHdr[233] = h & 0xFF;
        pEncPara->JfifHdr[234] = w >> 8; pEncPara->JfifHdr[235] = w & 0xFF;

        /* DRI & SOS */
        t = 678;
        if(pEncCfg->SlcSplitEn)
        {
            dri[4] = pEncCfg->SplitSize >> 8;
            dri[5] = pEncCfg->SplitSize & 0xFF;
            for (i = 0; i < 6; i++, t++ )
            {
                pEncPara->JfifHdr[t] = dri[i];
            }
        }

        for (i = 0; i < 14; i++, t++ )
        {
            pEncPara->JfifHdr[t] = sos[i];
        }

        /* DQT */
        jpge_create_qttable( pEncCfg->Qlevel, pEncPara->JpgeYqt, pEncPara->JpgeCqt );
        for ( i = 0; i < 64; i++ )
        {
            t = ZigZagScan[i];
            pEncPara->JfifHdr[t +  25] = pEncPara->JpgeYqt[i];
            pEncPara->JfifHdr[t +  94] = pEncPara->JpgeCqt[i];
            pEncPara->JfifHdr[t + 163] = pEncPara->JpgeCqt[i];
        }

    }

    /* Init other reg */
    pEncPara->PicWidth  = pEncCfg->FrameWidth;
    pEncPara->PicHeight = pEncCfg->FrameHeight;

    pEncPara->YuvSampleType = pEncCfg->YuvSampleType;
    pEncPara->YuvStoreType  = pEncCfg->YuvStoreType;
    pEncPara->RotationAngle = pEncCfg->RotationAngle;
    pEncPara->PackageSel    = 0xd8;

    pEncPara->SlcSplitEn    = pEncCfg->SlcSplitEn;
    pEncPara->SplitSize     = pEncCfg->SplitSize;

    pEncPara->pRegBase      = JpgeIpCtx.pRegBase;

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;
}

/***************************************************************************
* func          : JPEG_ENC_CtreateForVenc
* description   : create jpeg encode handle
                  CNcomment: ����jpeg������ CNend\n
* param[in]     : *pEncHandle      CNcomment: ������������     CNend\n
* param[in]     : pEncCfg          CNcomment: ����ı�����Ϣ CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_CtreateForVenc(HI_S32 *pEncHandle, Jpge_EncCfg_S *pEncCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;
    Jpge_EncPara_S  *pEncPara = NULL;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncCfg, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncHandle, HI_FAILURE);

    if (HI_FAILURE == jpge_issupport(pEncCfg))
    {
        HI_GFX_LOG_PrintFuncErr(jpge_issupport, HI_FAILURE);
        return HI_FAILURE;
    }

    s32Ret = JPEG_ENC_CreateHandle(pEncHandle);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(JPEG_ENC_CreateHandle, HI_FAILURE);
        return HI_FAILURE;
    }

    JPGE_CHECK_ARRAY_OVER_RETURN(JpgeIpCtx.CurrHandle - 1, JPGE_MAX_INSTANCE_NUM, HI_FAILURE);
    pEncPara = &gs_pJpgeEncInstance[*pEncHandle - 1].EncPara;

    JpgeOsal_MutexInit( &pEncPara->IsrMutex );
    JpgeOsal_MutexLock( &pEncPara->IsrMutex );

    pEncPara->PicWidth  = pEncCfg->FrameWidth;
    pEncPara->PicHeight = pEncCfg->FrameHeight;

    pEncPara->SlcSplitEn    = pEncCfg->SlcSplitEn;
    pEncPara->SplitSize     = pEncCfg->SplitSize;

    pEncPara->pRegBase      = JpgeIpCtx.pRegBase;

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;
}

#ifdef CONFIG_GFX_MMU_SUPPORT
/***************************************************************************
* func          : JPEG_ENC_QuickCopyEx
* description   : copy data from smmu buffer to mmz buffer
                  CNcomment: ��smmu buffer���ݿ�����mmz buffer CNend\n
* param[in]     : u32Phyaddr  CNcomment: smmu��ַ     CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_S32 JPEG_ENC_QuickCopyEx(HI_U32 u32SrcAddr,HI_U32 u32DstAddr,HI_U32 u32H,HI_U32 u32Stride)
{
    HI_S32 Ret = HI_SUCCESS;
    TDE2_SURFACE_S stSrcSur = {0};
    TDE2_SURFACE_S stDstSur = {0};
    TDE2_RECT_S stSrcRect   = {0};
    TDE2_RECT_S stDstRect   = {0};
    TDE_HANDLE handle = 0;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    stSrcSur.u32PhyAddr   = u32SrcAddr;
    stSrcSur.u32Width     = u32Stride / 4;
    stSrcSur.u32Height    = u32H;
    stSrcSur.u32Stride    = u32Stride;
    stSrcSur.bAlphaMax255 = HI_TRUE;
    stSrcSur.bYCbCrClut   = HI_FALSE;
    stSrcSur.enColorFmt   = TDE2_COLOR_FMT_ARGB8888;
    stSrcSur.u8Alpha0     = 0;
    stSrcSur.u8Alpha1     = 0;
    stSrcRect.s32Xpos     = 0;
    stSrcRect.s32Ypos     = 0;
    stSrcRect.u32Width    = stSrcSur.u32Width;
    stSrcRect.u32Height   = stSrcSur.u32Height;

    stDstSur.u32PhyAddr   = u32DstAddr;
    stDstSur.u32Width     = u32Stride / 4;
    stDstSur.u32Height    = u32H;
    stDstSur.u32Stride    = u32Stride;
    stDstSur.bAlphaMax255 = HI_TRUE;
    stDstSur.bYCbCrClut   = HI_FALSE;
    stDstSur.enColorFmt   = TDE2_COLOR_FMT_ARGB8888;
    stDstSur.u8Alpha0     = 0;
    stDstSur.u8Alpha1     = 0;
    stDstRect.s32Xpos     = 0;
    stDstRect.s32Ypos     = 0;
    stDstRect.u32Width    = stDstSur.u32Width;
    stDstRect.u32Height   = stDstSur.u32Height;

#if 0
    HI_PRINT("===+++stSrcSur.u32PhyAddr = 0x%x\n",stSrcSur.u32PhyAddr);
    HI_PRINT("===+++stSrcSur.u32Width   = %d\n",stSrcSur.u32Width);
    HI_PRINT("===+++stSrcSur.u32Height  = %d\n",stSrcSur.u32Height);
    HI_PRINT("===+++stSrcSur.u32Stride  = %d\n",stSrcSur.u32Stride);

    HI_PRINT("===+++stDstSur.u32PhyAddr = 0x%x\n",stDstSur.u32PhyAddr);
    HI_PRINT("===+++stDstRect.u32Width  = %d\n",  stDstRect.u32Width);
    HI_PRINT("===+++stDstRect.u32Height = %d\n",  stDstRect.u32Height);
    HI_PRINT("===+++stDstSur.u32Stride  = %d\n",  stDstSur.u32Stride);
#endif

    Ret = HI_DRV_MODULE_GetFunction(HI_ID_TDE, (HI_VOID**)&gs_TdeExportFuncs);
    if ((HI_SUCCESS != Ret) || (NULL == gs_TdeExportFuncs))
    {
        HI_GFX_LOG_PrintFuncErr(HI_DRV_MODULE_GetFunction, HI_FAILURE);
        return HI_FAILURE;
    }

    JPGE_CHECK_NULLPOINTER_RETURN(gs_TdeExportFuncs, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(gs_TdeExportFuncs->pfnTdeBeginJob, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(gs_TdeExportFuncs->pfnTdeQuickCopyEx, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(gs_TdeExportFuncs->pfnTdeEndJob, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(gs_TdeExportFuncs->pfnTdeCancelJob, HI_FAILURE);

    Ret = gs_TdeExportFuncs->pfnTdeBeginJob(&handle);
    if (Ret != HI_SUCCESS)
    {
        HI_GFX_LOG_PrintFuncErr(pfnTdeBeginJob, HI_FAILURE);
        return Ret;
    }

    Ret = gs_TdeExportFuncs->pfnTdeQuickCopyEx(handle,&stSrcSur,&stSrcRect,&stDstSur,&stDstRect,HI_FALSE,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        gs_TdeExportFuncs->pfnTdeCancelJob(handle);
        HI_GFX_LOG_PrintFuncErr(pfnTdeQuickCopyEx, HI_FAILURE);
        return Ret;
    }

    Ret = gs_TdeExportFuncs->pfnTdeEndJob(handle,HI_TRUE,100,HI_TRUE,HI_NULL,HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        gs_TdeExportFuncs->pfnTdeCancelJob(handle);
        HI_GFX_LOG_PrintFuncErr(pfnTdeEndJob, HI_FAILURE);
        return Ret;
    }

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}


/***************************************************************************
* func          : JPEG_ENC_FreeMmzBuf
* description   : free mmz buffer
                  CNcomment: �ͷ�MMZ buffer CNend\n
* param[in]     : u32Phyaddr  CNcomment: mmz��ַ     CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_VOID JPEG_ENC_FreeMmzBuf(HI_U32 u32Phyaddr)
{
    MMZ_BUFFER_S stMMZBuffer = {0};
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_EQUAL_UNRETURN(0, u32Phyaddr);
    stMMZBuffer.u32StartPhyAddr = u32Phyaddr;
    HI_DRV_MMZ_Release(&stMMZBuffer);

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}

/***************************************************************************
* func         : JPEG_ENC_AllocMmzBuf
* description  : alloc mmz buffer
                 CNcomment: ����MMZ buffer CNend\n
* param[in]    : pstEncPara  CNcomment: ������Ϣ     CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
static HI_S32 JPEG_ENC_AllocMmzBuf(Jpge_EncPara_S *pstEncPara,HI_U32 *pu32YAddr,HI_U32 *pu32UAddr,HI_U32 *pu32VAddr)
{
    HI_S32 s32Ret     = HI_SUCCESS;
    HI_U32 u32YHeight = pstEncPara->PicHeight;
    HI_U32 u32YStride = pstEncPara->SrcYStride;
    HI_U32 u32UHeight = pstEncPara->PicHeight;
    HI_U32 u32UStride = pstEncPara->SrcCStride;
    HI_U32 u32VHeight = pstEncPara->PicHeight;
    HI_U32 u32VStride = pstEncPara->SrcCStride;
    HI_U32 u32YSize   = pstEncPara->SrcYStride * pstEncPara->PicHeight;
    HI_U32 u32USize   = pstEncPara->SrcCStride * pstEncPara->PicHeight;
    HI_U32 u32VSize   = u32USize;
    HI_U32 u32YAddr   = 0;
    HI_U32 u32UAddr   = 0;
    HI_U32 u32VAddr   = 0;
    MMZ_BUFFER_S  stMMZBuffer = {0};
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    if ( (JPGE_YUV420 == pstEncPara->YuvSampleType )
       &&((JPGE_SEMIPLANNAR == pstEncPara->YuvStoreType) || (JPGE_PLANNAR == pstEncPara->YuvStoreType)))
    {
         u32UHeight = u32YHeight >> 1;
         u32VHeight = u32YHeight >> 1;
    }

    if ((JPGE_SEMIPLANNAR == pstEncPara->YuvStoreType) && (0 != pstEncPara->SrcVAddr))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (  (JPGE_PACKAGE == pstEncPara->YuvStoreType)
        &&((0 != pstEncPara->SrcCAddr) || (0 != pstEncPara->SrcVAddr)))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((0 != pstEncPara->SrcYAddr) && (0 != u32YSize))
    {
        HI_GFX_Memset(&stMMZBuffer,0x0,sizeof(MMZ_BUFFER_S));
        s32Ret = HI_DRV_MMZ_Alloc("JPEG-ENC-YBUF", NULL,u32YSize,16,&stMMZBuffer);
        if (HI_SUCCESS != s32Ret)
        {
            HI_GFX_LOG_PrintFuncErr(HI_DRV_MMZ_Alloc,HI_FAILURE);
            return HI_FAILURE;
        }
        u32YAddr   = stMMZBuffer.u32StartPhyAddr;
        *pu32YAddr = u32YAddr;
        s32Ret     = JPEG_ENC_QuickCopyEx(pstEncPara->SrcYAddr,u32YAddr,u32YHeight,u32YStride);
        if (HI_SUCCESS != s32Ret)
        {
            JPEG_ENC_FreeMmzBuf(u32YAddr);
            HI_GFX_LOG_PrintFuncErr(JPEG_ENC_QuickCopyEx,HI_FAILURE);
            return HI_FAILURE;
        }
    }

    if ((0 != pstEncPara->SrcCAddr) && (0 != u32USize))
    {
        HI_GFX_Memset(&stMMZBuffer,0x0,sizeof(MMZ_BUFFER_S));
        s32Ret = HI_DRV_MMZ_Alloc("JPEG-ENC-UBUF",NULL,u32USize,16,&stMMZBuffer);
        if (HI_SUCCESS != s32Ret)
        {
            JPEG_ENC_FreeMmzBuf(u32YAddr);
            HI_GFX_LOG_PrintFuncErr(HI_DRV_MMZ_Alloc,HI_FAILURE);
            return HI_FAILURE;
        }
        u32UAddr   = stMMZBuffer.u32StartPhyAddr;
        *pu32UAddr = u32UAddr;
        s32Ret     = JPEG_ENC_QuickCopyEx(pstEncPara->SrcCAddr,u32UAddr,u32UHeight,u32UStride);
        if (HI_SUCCESS != s32Ret)
        {
            JPEG_ENC_FreeMmzBuf(u32YAddr);
            JPEG_ENC_FreeMmzBuf(u32UAddr);
            HI_GFX_LOG_PrintFuncErr(JPEG_ENC_QuickCopyEx,HI_FAILURE);
            return HI_FAILURE;
        }
    }

    if ((0 != pstEncPara->SrcVAddr) && (0 != u32VSize))
    {
        HI_GFX_Memset(&stMMZBuffer,0x0,sizeof(MMZ_BUFFER_S));
        s32Ret = HI_DRV_MMZ_Alloc("JPEG-ENC-VBUF",NULL,u32VSize,16,&stMMZBuffer);
        if (HI_SUCCESS != s32Ret)
        {
            JPEG_ENC_FreeMmzBuf(u32YAddr);
            JPEG_ENC_FreeMmzBuf(u32UAddr);
            HI_GFX_LOG_PrintFuncErr(HI_DRV_MMZ_Alloc,HI_FAILURE);
            return HI_FAILURE;
        }
        u32VAddr   = stMMZBuffer.u32StartPhyAddr;
        *pu32VAddr = u32VAddr;
        s32Ret     = JPEG_ENC_QuickCopyEx(pstEncPara->SrcVAddr,u32VAddr,u32VHeight,u32VStride);
        if (HI_SUCCESS != s32Ret)
        {
            JPEG_ENC_FreeMmzBuf(u32YAddr);
            JPEG_ENC_FreeMmzBuf(u32UAddr);
            JPEG_ENC_FreeMmzBuf(u32VAddr);
            HI_GFX_LOG_PrintFuncErr(JPEG_ENC_QuickCopyEx,HI_FAILURE);
            return HI_FAILURE;
        }
    }

    if (0 == u32YAddr)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((JPGE_SEMIPLANNAR == pstEncPara->YuvStoreType) && (0 == u32UAddr))
    {
        JPEG_ENC_FreeMmzBuf(u32YAddr);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((JPGE_PLANNAR == pstEncPara->YuvStoreType) && ((0 == u32UAddr) || (0 == u32VAddr)))
    {
        JPEG_ENC_FreeMmzBuf(u32YAddr);
        JPEG_ENC_FreeMmzBuf(u32UAddr);
        JPEG_ENC_FreeMmzBuf(u32VAddr);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    pstEncPara->SrcYAddr = u32YAddr;
    pstEncPara->SrcCAddr = u32UAddr;
    pstEncPara->SrcVAddr = u32VAddr;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return HI_SUCCESS;
}

#if 0
/***************************************************************************
* func          : JPEG_ENC_AllocOutBuf
* description   : alloc out buffer
                  CNcomment: ����MMZ ���buffer CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
static HI_VOID* JPEG_ENC_AllocOutBuf(HI_U32* pu32OutPhy,HI_U32 u32OutSize)
{
    HI_S32 s32Ret = HI_SUCCESS;
    MMZ_BUFFER_S  stMMZBuffer = {0};
    HI_GFX_Memset(&stMMZBuffer,0x0,sizeof(MMZ_BUFFER_S));
    s32Ret = HI_DRV_MMZ_Alloc("JPEG-ENC-OUTBUF", NULL,u32OutSize,64,&stMMZBuffer);
    if(HI_SUCCESS != s32Ret){
        return NULL;
    }
    *pu32OutPhy = stMMZBuffer.u32StartPhyAddr;

    s32Ret = HI_DRV_MMZ_Map(&stMMZBuffer);
    if(HI_SUCCESS != s32Ret){
        JPEG_ENC_FreeMmzBuf(stMMZBuffer.u32StartPhyAddr,NULL);
        return NULL;
    }

    return stMMZBuffer.pu8StartVirAddr;

}
#endif
#endif

/***************************************************************************
* func         : JPEG_ENC_Start
* description  : begin encode
                 CNcomment: ��ʼ���� CNend\n
* param[in]    : EncHandle       CNcomment: ���������     CNend\n
* param[in]    : pEncIn          CNcomment: ������Ϣ       CNend\n
* param[in]    : pEncOut         CNcomment: �����Ϣ       CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
HI_S32 JPEG_ENC_Start(HI_S32 EncHandle, Jpge_EncIn_S *pEncIn, Jpge_EncOut_S *pEncOut)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_U32 u32YAddr   = 0;
    HI_U32 u32UAddr   = 0;
    HI_U32 u32VAddr   = 0;
#endif
    Jpge_EncPara_S *pEncPara = NULL;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pEncOut, HI_FAILURE);

    JPGE_CHECK_ARRAY_OVER_RETURN(EncHandle - 1, JPGE_MAX_INSTANCE_NUM, HI_FAILURE);
    pEncPara = &gs_pJpgeEncInstance[EncHandle - 1].EncPara;

    pEncPara->SrcYAddr   = pEncIn->BusViY;
    pEncPara->SrcCAddr   = pEncIn->BusViC;
    pEncPara->SrcVAddr   = pEncIn->BusViV;
    pEncPara->SrcYStride = pEncIn->ViYStride;
    pEncPara->SrcCStride = pEncIn->ViCStride;

#ifdef CONFIG_GFX_MMU_SUPPORT
    s32Ret = JPEG_ENC_AllocMmzBuf(pEncPara,&u32YAddr,&u32UAddr,&u32VAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(JPEG_ENC_AllocMmzBuf,HI_FAILURE);
        return HI_FAILURE;
    }
#if 0
    pOutVirAddr = (HI_U8*)JPEG_ENC_AllocOutBuf(&u32OutPhyAddr,pEncIn->OutBufSize);
    if(NULL == pOutVirAddr){
        JPEG_ENC_FreeMmzBuf(u32YAddr,NULL);
        JPEG_ENC_FreeMmzBuf(u32UAddr,NULL);
        JPEG_ENC_FreeMmzBuf(u32VAddr,NULL);
        return HI_FAILURE;
    }
    pEncIn->BusOutBuf = u32OutPhyAddr;
    pEncIn->pOutBuf   = pOutVirAddr;
#endif
#endif
    s32Ret = Jpge_StartOneFrame(pEncPara, pEncIn);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(Jpge_StartOneFrame,HI_FAILURE);
        goto ERR_EXIT;
    }

    JpgeOsal_MutexLock(&JpgeIpCtx.ChnMutex);
      jpge_set_register(pEncPara);
      JpgeOsal_MutexLock(&pEncPara->IsrMutex);
    JpgeOsal_MutexUnlock(&JpgeIpCtx.ChnMutex );

#ifdef CONFIG_GFX_MMU_SUPPORT
    JPEG_ENC_FreeMmzBuf(u32YAddr);
    JPEG_ENC_FreeMmzBuf(u32UAddr);
    JPEG_ENC_FreeMmzBuf(u32VAddr);
#endif

    s32Ret = Jpge_EndOneFrame(pEncPara,pEncIn,pEncOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(Jpge_EndOneFrame,HI_FAILURE);
        return HI_FAILURE;
    }

#if 0
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_GFX_Memcpy(pInOutVir,pEncOut->pStream,pEncOut->StrmSize);
    pEncOut->BusStream = u32InOutPhy;
    pEncOut->pStream   = pInOutVir;
    JPEG_ENC_FreeMmzBuf(u32OutPhyAddr,pOutVirAddr);
#endif
#endif

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;

ERR_EXIT:
#ifdef CONFIG_GFX_MMU_SUPPORT
    JPEG_ENC_FreeMmzBuf(u32YAddr);
    JPEG_ENC_FreeMmzBuf(u32UAddr);
    JPEG_ENC_FreeMmzBuf(u32VAddr);
#endif
    return HI_FAILURE;
}


/***************************************************************************
* func          : JPEG_ENC_StartForVenc
* description   : begin encode
                  CNcomment: ��ʼ���� CNend\n
* param[in]     : EncHandle       CNcomment: ���������     CNend\n
* param[in]     : pEncIn          CNcomment: ������Ϣ       CNend\n
* param[in]     : pEncOut         CNcomment: �����Ϣ       CNend\n
* retval        : HI_SUCCESS �ɹ�
* retval        : HI_FAILURE ʧ��
* others:       : NA
****************************************************************************/
HI_S32 JPEG_ENC_StartForVenc(HI_S32 EncHandle, Venc2Jpge_EncIn_S *pEncIn,HI_BOOL *pBufferFull)
{
#ifdef CONFIG_GFX_MMU_SUPPORT
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32YAddr   = 0;
    HI_U32 u32UAddr   = 0;
    HI_U32 u32VAddr   = 0;
#endif
    Jpge_EncPara_S  *pEncPara = NULL;
    HI_GFX_UNF_FuncEnter(gs_JpgeDebugUnf);

    JPGE_CHECK_NULLPOINTER_RETURN(pEncIn, HI_FAILURE);
    JPGE_CHECK_NULLPOINTER_RETURN(pBufferFull, HI_FAILURE);

    JPGE_CHECK_ARRAY_OVER_RETURN(EncHandle - 1, JPGE_MAX_INSTANCE_NUM, HI_FAILURE);
    pEncPara = &gs_pJpgeEncInstance[EncHandle - 1].EncPara;

    Jpge_StartOneFrame_toVenc(pEncPara, pEncIn);

#ifdef CONFIG_GFX_MMU_SUPPORT
    s32Ret = JPEG_ENC_AllocMmzBuf(pEncPara,&u32YAddr,&u32UAddr,&u32VAddr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_LOG_PrintFuncErr(JPEG_ENC_AllocMmzBuf,HI_FAILURE);
        return HI_FAILURE;
    }
#endif

    JpgeOsal_MutexLock(&JpgeIpCtx.ChnMutex);
      jpge_set_register(pEncPara );
      JpgeOsal_MutexLock(&pEncPara->IsrMutex);
      *pBufferFull = (HI_BOOL)pEncPara->BufFull;
    JpgeOsal_MutexUnlock( &JpgeIpCtx.ChnMutex );

 #ifdef CONFIG_GFX_MMU_SUPPORT
    JPEG_ENC_FreeMmzBuf(u32YAddr);
    JPEG_ENC_FreeMmzBuf(u32UAddr);
    JPEG_ENC_FreeMmzBuf(u32VAddr);
#endif

    HI_GFX_UNF_FuncExit(gs_JpgeDebugUnf);

    return HI_SUCCESS;
}

/***************************************************************************
* func         : JPEG_ENC_Destory
* description  : destory jpge encode
                 CNcomment: ���ٱ����� CNend\n
* param[in]    : EncHandle      CNcomment: ���������     CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
HI_S32 JPEG_ENC_Destory(HI_S32 EncHandle)
{
    return JPEG_ENC_DestoryHandle(EncHandle);
}

/***************************************************************************
* func         : JPEG_ENC_DestoryForVenc
* description  : destory jpge encode
                 CNcomment: ���ٱ����� CNend\n
* param[in]    : EncHandle      CNcomment: ���������     CNend\n
* retval       : HI_SUCCESS �ɹ�
* retval       : HI_FAILURE ʧ��
* others:      : NA
****************************************************************************/
HI_S32  JPEG_ENC_DestoryForVenc(HI_S32 EncHandle)
{
    return JPEG_ENC_DestoryHandle(EncHandle);
}

/***************************************************************************
* func          : JPEG_ENC_OpenClock
* description   : open clock
                  CNcomment: ��ʱ��           CNend\n
* param[in]     : NA
* others:       : NA
****************************************************************************/
HI_VOID JPEG_ENC_OpenClock(HI_VOID)
{
    U_PERI_CRG36 unTempValue;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_UNRETURN(g_pstRegCrg);
    unTempValue.u32 = g_pstRegCrg->PERI_CRG36.u32;

    /*cancel reset*/
    unTempValue.bits.jpge_srst_req = 0x0;
    /*enable clock */
    unTempValue.bits.jpge_cken     = 0x1;
    g_pstRegCrg->PERI_CRG36.u32    = unTempValue.u32;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
    return;
}

/***************************************************************************
* func          : JPEG_ENC_CloseClock
* description   : close clock
                  CNcomment: �ر�ʱ��           CNend\n
* param[in]     : NA
* others:       : NA
****************************************************************************/
HI_VOID JPEG_ENC_CloseClock(HI_VOID)
{
    U_PERI_CRG36 unTempValue;
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);

    JPGE_CHECK_NULLPOINTER_UNRETURN(g_pstRegCrg);
    unTempValue.u32 = g_pstRegCrg->PERI_CRG36.u32;

    /*disable clock */
    unTempValue.bits.jpge_cken     = 0x0;
    /*cancel reset*/
    unTempValue.bits.jpge_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG36.u32    = unTempValue.u32;

    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);

    return;
}

/***************************************************************************
* func          : JPEG_ENC_Reset
* description   : ��������λ
* param[in]     : NA
* others:       : NA
****************************************************************************/
HI_VOID JPEG_ENC_Reset(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_JpgeDebugInterApi);
    JPEG_ENC_DestoryHandle(JpgeIpCtx.CurrHandle);
    HI_GFX_LOG_FuncExit(gs_JpgeDebugInterApi);
}
