/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name       : drv_hifb_mem.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date                  Author                Modification
2018/01/01            sdk                   Created file
*************************************************************************************************/

/*********************************add include here***********************************************/
#include "drv_hifb_mem.h"
#include "hi_drv_mmz.h"
#include "drv_pdm_ext.h"
#include "drv_hifb_paracheck.h"

/***************************** Macro Definition *************************************************/


/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/

/******************************* API declaration ************************************************/
static inline HI_U32 DRV_HIFB_GetBpp32FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline HI_U32 DRV_HIFB_GetBpp24FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt);
static inline HI_U32 DRV_HIFB_GetBpp16FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt);

/******************************* API release ****************************************************/

/***************************************************************************************
* func          : hifb_buf_map
* description   : CNcomment: �ڴ�ӳ�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID *hifb_buf_map(HI_U32 u32PhyAddr)
{
    return HI_GFX_Map(u32PhyAddr,0,HI_TRUE);
}

/***************************************************************************************
* func          : hifb_buf_ummap
* description   : CNcomment: �ڴ���ӳ�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 hifb_buf_ummap(HI_VOID *pViraddr)
{
    //dump_stack();
    return HI_GFX_Unmap(pViraddr,HI_TRUE);
}

/***************************************************************************************
* func         : hifb_buf_freemem
* description  : CNcomment: �ͷ��ڴ� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID hifb_buf_freemem(HI_U32 u32Phyaddr,HI_BOOL bSmmu)
{
    HI_GFX_FreeMem(u32Phyaddr,bSmmu);
}

#if 0
static inline HI_VOID GFX_CheckMemLegal(const HI_U32 AllocBuf, const HI_U32 AllocBufSize)
{
    HI_U32 HdReseverDdr = 0;
    HI_U32 HdReseverBufSize = 0;
    HI_U32 WbcReseverDdr = 0;
    HI_U32 WbcReseverBufSize = 0;

    PDM_EXPORT_FUNC_S *pstPdmExportFuncs = HI_NULL;

    (HI_VOID)HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&pstPdmExportFuncs);
    if (HI_NULL == pstPdmExportFuncs)
    {
       return;
    }

    pstPdmExportFuncs->pfnPDM_GetReserveMem("HIFB_DispBuf_HD",&HdReseverDdr,&HdReseverBufSize);
    pstPdmExportFuncs->pfnPDM_GetReserveMem("HIFB_GfxWbc2",&WbcReseverDdr,&WbcReseverBufSize);

    if (   (( (AllocBuf + AllocBufSize) >= HdReseverDdr) && ( (AllocBuf + AllocBufSize) <= (HdReseverDdr + HdReseverBufSize)))
         ||((AllocBuf >= HdReseverDdr) && (AllocBuf <= (HdReseverDdr + HdReseverBufSize))))
    {
         HI_PRINT("\n=============================================================================\n");
         HI_PRINT("%s %d failure\n",__FUNCTION__,__LINE__);
         HI_PRINT("hd reserver[0x%x  0x%x] alloc mem[0x%x  0x%x]\n",HdReseverDdr,HdReseverDdr + HdReseverBufSize,AllocBuf,AllocBuf + AllocBufSize);
         HI_PRINT("=============================================================================\n");
    }

    if (   (( (AllocBuf + AllocBufSize) >= WbcReseverDdr) && ( (AllocBuf + AllocBufSize) <= (WbcReseverDdr + WbcReseverBufSize)))
         ||((AllocBuf >= WbcReseverDdr) && (AllocBuf <= (WbcReseverDdr + WbcReseverBufSize))))
    {
         HI_PRINT("\n=============================================================================\n");
         HI_PRINT("%s %d failure\n",__FUNCTION__,__LINE__);
         HI_PRINT("wbc reserver[0x%x  0x%x] alloc mem[0x%x  0x%x]\n",WbcReseverDdr,WbcReseverDdr + WbcReseverBufSize,AllocBuf,AllocBuf + AllocBufSize);
         HI_PRINT("=============================================================================\n");
    }

    return;
}
#endif

/***************************************************************************************
* func         : hifb_buf_allocmem
* description  : CNcomment: �����ڴ� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_U32 hifb_buf_allocmem(HI_CHAR *pName, HI_CHAR* pZoneName, HI_U32 u32LayerSize)
{
    HI_U32 PhyAddr = 0;
    HI_BOOL bMmu = HI_FALSE;

    PhyAddr = HI_GFX_AllocMem(pName, pZoneName, u32LayerSize,&bMmu);
#if 0
    if (HI_FALSE == bMmu)
    {
         GFX_CheckMemLegal(PhyAddr,u32LayerSize);
    }
#endif

    return PhyAddr;
}

/***************************************************************************************
* func        : hifb_buf_map2smmu
* description : CNcomment: map mmz to smmu mem CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_U32 hifb_buf_map2smmu(HI_U32 u32PhyBuf)
{
   return HI_GFX_MapMmzToSmmu(u32PhyBuf);
}

/***************************************************************************************
* func         : hifb_buf_unmapsmmu
* description  : CNcomment: un map smmu mem CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 hifb_buf_unmapsmmu(HI_U32 u32SmmuBuf)
{
   return HI_GFX_UnMapSmmu(u32SmmuBuf);
}

/**< check these two rectangle cover each other >**/
HI_BOOL hifb_iscontain(HIFB_RECT *pstParentRect, HIFB_RECT *pstChildRect)
{
    HIFB_POINT_S stPoint = {0};

    HIFB_CHECK_NULLPOINTER_RETURN(pstParentRect, HI_FALSE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstChildRect, HI_FALSE);

    stPoint.s32XPos = pstChildRect->x;
    stPoint.s32YPos = pstChildRect->y;

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(pstParentRect->w, pstParentRect->x, HI_FALSE);
    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(pstParentRect->h, pstParentRect->y, HI_FALSE);

    if ((stPoint.s32XPos < pstParentRect->x) || (stPoint.s32XPos > (pstParentRect->x + pstParentRect->w))
      ||(stPoint.s32YPos < pstParentRect->y) || (stPoint.s32YPos > (pstParentRect->y + pstParentRect->h)))
    {
        return HI_FALSE;
    }

    stPoint.s32XPos = pstChildRect->x + pstChildRect->w;
    stPoint.s32YPos = pstChildRect->y + pstChildRect->h;

    if ((stPoint.s32XPos < pstParentRect->x) || (stPoint.s32XPos > (pstParentRect->x + pstParentRect->w))
      ||(stPoint.s32YPos < pstParentRect->y) || (stPoint.s32YPos > (pstParentRect->y + pstParentRect->h)))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_U32 DRV_HIFB_GetBppByFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    HI_U32 BppDepth = 0;

    BppDepth = DRV_HIFB_GetBpp32FromPixelFmt(enDataFmt);
    if (32 == BppDepth)
    {
        return BppDepth;
    }

    BppDepth = DRV_HIFB_GetBpp24FromPixelFmt(enDataFmt);
    if (24 == BppDepth)
    {
        return BppDepth;
    }

    BppDepth = DRV_HIFB_GetBpp16FromPixelFmt(enDataFmt);
    if (16 == BppDepth)
    {
        return BppDepth;
    }

    switch (enDataFmt)
    {
        case HIFB_FMT_1BPP:
            return 1;
        case HIFB_FMT_2BPP:
            return 2;
        case HIFB_FMT_4BPP:
            return 4;
        case HIFB_FMT_8BPP:
        case HIFB_FMT_ACLUT44:
            return 8;
        default:
            return 0;
    }
}

static inline HI_U32 DRV_HIFB_GetBpp32FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    switch (enDataFmt)
    {
       case HIFB_FMT_KRGB888:
       case HIFB_FMT_ARGB8888:
       case HIFB_FMT_RGBA8888:
       case HIFB_FMT_ABGR8888:
       case HIFB_FMT_KBGR888:
           return 32;
       default:
           return 0;
    }
}

static inline HI_U32 DRV_HIFB_GetBpp24FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    switch (enDataFmt)
    {
       case HIFB_FMT_RGB888:
       case HIFB_FMT_ARGB8565:
       case HIFB_FMT_RGBA5658:
       case HIFB_FMT_ABGR8565:
       case HIFB_FMT_BGR888:
           return 24;
       default:
           return 0;
    }
}

static inline HI_U32 DRV_HIFB_GetBpp16FromPixelFmt(HIFB_COLOR_FMT_E enDataFmt)
{
    switch (enDataFmt)
    {
       case HIFB_FMT_RGB565:
       case HIFB_FMT_KRGB444:
       case HIFB_FMT_KRGB555:
       case HIFB_FMT_ARGB4444:
       case HIFB_FMT_ARGB1555:
       case HIFB_FMT_RGBA4444:
       case HIFB_FMT_RGBA5551:
       case HIFB_FMT_ACLUT88:
       case HIFB_FMT_BGR565:
       case HIFB_FMT_ABGR1555:
       case HIFB_FMT_ABGR4444:
       case HIFB_FMT_KBGR444:
       case HIFB_FMT_KBGR555:
           return 16;
       default:
           return 0;
    }
}


/***************************************************************************************
* func         : hifb_bitfieldcmp
* description  : CNcomment: �ж��������ظ�ʽ�Ƿ���� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 hifb_bitfieldcmp(struct fb_bitfield x, struct fb_bitfield y)
{
    if ((x.offset == y.offset) && (x.length == y.length) && (x.msb_right == y.msb_right))
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}
