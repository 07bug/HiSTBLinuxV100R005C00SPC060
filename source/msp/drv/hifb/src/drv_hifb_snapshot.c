/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name      : drv_hifb_snapshot.c
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History         :
Date                  Author                Modification
2018/01/01            sdk                   Created file
***************************************************************************************************/

/*********************************add include here*************************************************/
#include <linux/string.h>
#include "hifb.h"
#include "drv_hifb_osr.h"
#include "drv_hifb_mem.h"
#include "drv_hifb_proc.h"
#include "hi_drv_file.h"
#include "hi_gfx_sys_k.h"
#include "drv_hifb_paracheck.h"

/***************************** Macro Definition ***************************************************/
#ifdef CONFIG_GFX_PROC_SUPPORT

/*************************** Structure Definition *************************************************/

#ifdef CFG_HIFB_ANDROID_SUPPORT

typedef struct  tagBITMAPFILEHEADER{
    HI_U16 u16Type;                /*文件类型，设为0x4D42                   */
    HI_U32 u32Size;                /*文件大小，像素数据加上头文件大小sizeof */
    HI_U16 u16Reserved1;           /*保留位                                 */
    HI_U16 u16Reserved2;           /*保留位                                 */
    HI_U32 u32OffBits;             /*文件头到实际位图数据的偏移量           */
}__attribute__((packed)) BMP_BMFHEADER_S;


typedef  struct tagBITMAPINFOHEADER{
    HI_U32 u32Size;             /*位图信息头的大小,sizeof(BMP_BMIHEADER_S) */
    HI_U32 u32Width;            /*图像宽度                                 */
    HI_U32 u32Height;           /*图像高度                                 */
    HI_U16 u32Planes;           /*位图位面数，设为1                        */
    HI_U16 u32PixbitCount;      /*每个像素的位数，如RGB8888就是32          */
    HI_U32 u32Compression;      /*位图数据压缩类型，设为0，表示不会压缩    */
    HI_U32 u32SizeImage;        /*位图数据大小，设为0                      */
    HI_U32 u32XPelsPerMeter;    /*位图水平分辨率，与图像宽度相同           */
    HI_U32 u32YPelsPerMeter;    /*位图垂直分辨率，与图像高度相同           */
    HI_U32 u32ClrUsed;          /*说明位图实际使用的彩色表中的颜色索引数，设为0*/
    HI_U32 u32ClrImportant;     /*对图像显示很重要的颜色索引数，设为0      */
} BMP_BMIHEADER_S;

#endif

/********************** Global Variable declaration ***********************************************/

#ifdef CFG_HIFB_ANDROID_SUPPORT
extern HIFB_DRV_OPS_S g_stDrvAdpCallBackFunction;
extern HIFB_DRV_TDEOPS_S g_stGfx2dCallBackFunction;
extern HIFB_LAYER_S s_stLayer[HIFB_MAX_LAYER_NUM];
#endif

/******************************* API declaration **************************************************/
extern HI_U32 DRV_HIFB_GetBppByFmt(HIFB_COLOR_FMT_E enColorFmt);

#ifdef CFG_HIFB_ANDROID_SUPPORT
static inline HI_VOID HIFB_SnapshotPrint(HIFB_BUFFER_S *pstSrcBuffer, HIFB_BUFFER_S *pstDstBuffer);
static inline HI_S32  HIFB_SNAPSHOT_CopyDispbufToSaveBuf (HI_U32 LayerID, HI_U32 CmpStride, HIFB_BUFFER_S *pstSrcBuffer,HIFB_BUFFER_S *pstDstBuffer);
static inline HI_VOID HIFB_SNAPSHOT_WriteDispDataToFile  (HI_U32 LayerID, HI_CHAR* pData, HI_U32 BufSize, HIFB_BUFFER_S *pstDstBuffer);
#endif

/******************************* API realization **************************************************/
HI_VOID HI_UNF_HIFB_CaptureImgFromLayer(HI_U32 u32LayerID, HI_CHAR* InputFmt)
{
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

#ifdef CFG_HIFB_ANDROID_SUPPORT
    HI_S32 Ret = HI_SUCCESS;
    HI_S8 *pData = NULL;
    HI_U32 u32BufSize = 0;
    HI_U32 u32Bpp = 0;
    HI_U32 CmpStride = 0;
    HI_U32 Stride = 0;
    HIFB_BUFFER_S stSrcBuffer, stDstBuffer;
    HI_CHAR MemZoneName[HIFB_FILE_NAME_MAX_LEN]= {'\0'};

    HI_GFX_Memset(&stSrcBuffer, 0x0, sizeof(stSrcBuffer));
    HI_GFX_Memset(&stDstBuffer, 0x0, sizeof(stDstBuffer));
#endif

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(u32LayerID);
    info = s_stLayer[u32LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

#ifndef CFG_HIFB_ANDROID_SUPPORT
    HI_PRINT("\n=============================================================================\n");
    HI_PRINT("use tools/linux/utils/bmpGen to save input ui:\nfor example bmpGen phyaddr width height stride pixformat outfile\n");
    HI_PRINT("bmpGen 0x%x %d %d %d %s input.bmp\n",par->stRunInfo.CurScreenAddr,      \
                                                   par->stExtendInfo.u32DisplayWidth, \
                                                   par->stExtendInfo.u32DisplayHeight,\
                                                   info->fix.line_length,             \
                                                   InputFmt);
    HI_PRINT("=============================================================================\n");
#else

    stSrcBuffer.stCanvas.enFmt      = par->stExtendInfo.enColFmt;
    stSrcBuffer.stCanvas.u32Width   = par->stExtendInfo.u32DisplayWidth;
    stSrcBuffer.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stSrcBuffer.stCanvas.u32PhyAddr = par->stRunInfo.CurScreenAddr;
    stSrcBuffer.stCanvas.u32Pitch   = info->fix.line_length;
    if (HIFB_LAYER_BUF_NONE == par->stExtendInfo.enBufMode)
    {
        stSrcBuffer.stCanvas.enFmt = par->stDispInfo.stUserBuffer.stCanvas.enFmt;
        stSrcBuffer.stCanvas.u32Pitch = par->stDispInfo.stUserBuffer.stCanvas.u32Pitch;
    }

    if ((HI_TRUE == par->st3DInfo.IsStereo) && (HIFB_STEREO_FRMPACKING != par->st3DInfo.StereoMode))
    {
        HI_GFX_Memcpy(&stSrcBuffer.stCanvas, &par->st3DInfo.st3DSurface, sizeof(stSrcBuffer.stCanvas));
    }

    stSrcBuffer.UpdateRect.x = 0;
    stSrcBuffer.UpdateRect.y = 0;
    stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
    stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

    HI_GFX_Memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
    stDstBuffer.stCanvas.enFmt = (HI_TRUE == par->bDeCompress) ? (HIFB_FMT_ARGB8888) : (HIFB_FMT_RGB888);
    u32Bpp = DRV_HIFB_GetBppByFmt(stDstBuffer.stCanvas.enFmt);
    Stride = CONIFG_HIFB_GetMaxStride(stSrcBuffer.stCanvas.u32Width,u32Bpp,&CmpStride,CONFIG_HIFB_STRIDE_16ALIGN);

    if (HI_FALSE == par->bDeCompress)
    {
       stDstBuffer.stCanvas.u32Pitch = Stride;
    }
    else
    {
       stDstBuffer.stCanvas.u32Pitch = CmpStride;
    }

    u32BufSize = HI_HIFB_GetMemSize(Stride,stSrcBuffer.stCanvas.u32Height);
    HIFB_CHECK_EQUAL_UNRETURN(u32BufSize, 0);

    snprintf(MemZoneName, sizeof(MemZoneName),"HIFB_SnapShot%d", u32LayerID);
    MemZoneName[sizeof(MemZoneName) - 1] = '\0';

    stDstBuffer.stCanvas.u32PhyAddr = hifb_buf_allocmem(MemZoneName, "iommu", u32BufSize);
    if (0 == stDstBuffer.stCanvas.u32PhyAddr)
    {
        HIFB_ERROR("failed to malloc the snapshot memory, size: %d KBtyes!\n", u32BufSize/1024);
        return;
    }

    pData = (HI_S8*)hifb_buf_map(stDstBuffer.stCanvas.u32PhyAddr);
    if (NULL == pData)
    {
        HIFB_ERROR("Failed to map snapshot memory.\n");
        hifb_buf_freemem(stDstBuffer.stCanvas.u32PhyAddr,HI_TRUE);
        return;
    }
    HI_GFX_Memset(pData, 0x0, u32BufSize);

    Ret = HIFB_SNAPSHOT_CopyDispbufToSaveBuf(u32LayerID,CmpStride,&stSrcBuffer, &stDstBuffer);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("HIFB_SNAPSHOT_CopyDispbufToSaveBuf error! s32Ret = 0x%x\n",Ret);
        hifb_buf_ummap((HI_VOID*)pData);
        hifb_buf_freemem(stDstBuffer.stCanvas.u32PhyAddr,HI_TRUE);
        return;
    }

    HIFB_SNAPSHOT_WriteDispDataToFile(u32LayerID,pData,u32BufSize,&stDstBuffer);

    hifb_buf_ummap((HI_VOID*)pData);
    hifb_buf_freemem(stDstBuffer.stCanvas.u32PhyAddr,HI_TRUE);
#endif

    return;
}

#ifdef CFG_HIFB_ANDROID_SUPPORT
static inline HI_S32 HIFB_SNAPSHOT_CopyDispbufToSaveBuf(HI_U32 LayerID, HI_U32 CmpStride, HIFB_BUFFER_S *pstSrcBuffer,HIFB_BUFFER_S *pstDstBuffer)
{
    HI_S32 Ret = HI_SUCCESS;
    HIFB_BUFFER_S stSrcBuffer;
    HIFB_BUFFER_S stDstBuffer;
    HIFB_BLIT_OPT_S stBlitOpt;
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;
#ifndef CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE
    HI_U32 HeadSize  = 0;
    HI_U32 ARHeadDdr = 0;
    HI_U32 ARDataDdr = 0;
    HI_U32 GBHeadDdr = 0;
    HI_U32 GBDataDdr = 0;
#endif
    HI_GFX_Memset(&stSrcBuffer, 0, sizeof(stSrcBuffer));
    HI_GFX_Memset(&stDstBuffer, 0, sizeof(stDstBuffer));
    HI_GFX_Memset(&stBlitOpt, 0, sizeof(stBlitOpt));

    HIFB_CHECK_NULLPOINTER_RETURN(pstSrcBuffer, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(pstDstBuffer, HI_FAILURE);
    HI_GFX_Memcpy(&stSrcBuffer,pstSrcBuffer,sizeof(HIFB_BUFFER_S));
    HI_GFX_Memcpy(&stDstBuffer,pstDstBuffer,sizeof(HIFB_BUFFER_S));

    HIFB_CHECK_LAYERID_SUPPORT_RETURN(LayerID, HI_FAILURE);
    info = s_stLayer[LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_RETURN(info, HI_FAILURE);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_RETURN(par, HI_FAILURE);

    stBlitOpt.bBlock = HI_TRUE;

    HIFB_CHECK_NULLPOINTER_RETURN(g_stGfx2dCallBackFunction.HIFB_DRV_Blit, HI_FAILURE);
    HIFB_CHECK_NULLPOINTER_RETURN(g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy, HI_FAILURE);

    if (HI_FALSE == par->bDeCompress)
    {
        Ret = g_stGfx2dCallBackFunction.HIFB_DRV_Blit(&stSrcBuffer, &stDstBuffer, &stBlitOpt, HI_TRUE);
        HIFB_SnapshotPrint(&stSrcBuffer, &stDstBuffer);
        return (Ret < 0) ? (HI_FAILURE) : (HI_SUCCESS);
    }

#ifdef CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE
    HI_UNUSED(CmpStride);
    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stSrcBuffer, &stDstBuffer, HI_FALSE);
#else

    Ret = HIFB_PARA_CHECK_SUPPORT(HIFB_PARA_CHECK_HEIGHT | HIFB_PARA_CHECK_STRIDE,0, stDstBuffer.stCanvas.u32Height,CmpStride, 0, 0);
    if (HI_SUCCESS != Ret)
    {
        HIFB_ERROR("Failure\n");
        return HI_FAILURE;
    }

    HeadSize  = (16 * stDstBuffer.stCanvas.u32Height + 0xff) & 0xffffff00;
    ARHeadDdr = stDstBuffer.stCanvas.u32PhyAddr;

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(ARHeadDdr,HeadSize,HI_FAILURE);
    ARDataDdr = ARHeadDdr + HeadSize;

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(ARHeadDdr,(CmpStride * stDstBuffer.stCanvas.u32Height),HI_FAILURE);
    GBHeadDdr = ARDataDdr + CmpStride * stDstBuffer.stCanvas.u32Height;

    HI_GFX_CHECK_INT_ADDITION_REVERSAL_RETURN(GBHeadDdr,HeadSize,HI_FAILURE);
    GBDataDdr = GBHeadDdr + HeadSize;

    stSrcBuffer.stCanvas.u32PhyAddr = par->stRunInfo.CurScreenAddr;
    stSrcBuffer.stCanvas.u32Width   = 4;
    stSrcBuffer.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stSrcBuffer.stCanvas.u32Pitch   = 16;
    stSrcBuffer.stCanvas.enFmt      = HIFB_FMT_ARGB8888;
    stSrcBuffer.UpdateRect.x = 0;
    stSrcBuffer.UpdateRect.y = 0;
    stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
    stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

    HI_GFX_Memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
    stDstBuffer.stCanvas.u32PhyAddr = ARHeadDdr;

#if 0
    HI_PRINT("\n===========================================\n");
    HI_PRINT("src ddr = 0x%lx\n",(unsigned long)stSrcBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("dst ddr = 0x%lx\n",(unsigned long)stDstBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("width = %d\n",stSrcBuffer.stCanvas.u32Width);
    HI_PRINT("height = %d\n",stSrcBuffer.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",stSrcBuffer.stCanvas.u32Pitch);
    HI_PRINT("===========================================\n");
#endif

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stSrcBuffer, &stDstBuffer, HI_FALSE);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(stSrcBuffer.stCanvas.u32PhyAddr,HeadSize,HI_FAILURE);
    stSrcBuffer.stCanvas.u32PhyAddr = stSrcBuffer.stCanvas.u32PhyAddr + HeadSize;

    stSrcBuffer.stCanvas.u32Width   = par->stExtendInfo.u32DisplayWidth;
    stSrcBuffer.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stSrcBuffer.stCanvas.u32Pitch   = CmpStride;
    stSrcBuffer.stCanvas.enFmt      = HIFB_FMT_ARGB1555;
    stSrcBuffer.UpdateRect.x = 0;
    stSrcBuffer.UpdateRect.y = 0;
    stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
    stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

    HI_GFX_Memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
    stDstBuffer.stCanvas.u32PhyAddr = ARDataDdr;

#if 0
    HI_PRINT("\n===========================================\n");
    HI_PRINT("src ddr = 0x%lx\n",(unsigned long)stSrcBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("dst ddr = 0x%lx\n",(unsigned long)stDstBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("width = %d\n",stSrcBuffer.stCanvas.u32Width);
    HI_PRINT("height = %d\n",stSrcBuffer.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",stSrcBuffer.stCanvas.u32Pitch);
    HI_PRINT("===========================================\n");
#endif

    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stSrcBuffer, &stDstBuffer, HI_FALSE);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(stSrcBuffer.stCanvas.u32PhyAddr,(CmpStride * stSrcBuffer.stCanvas.u32Height),HI_FAILURE);
    stSrcBuffer.stCanvas.u32PhyAddr = stSrcBuffer.stCanvas.u32PhyAddr + CmpStride * stSrcBuffer.stCanvas.u32Height;

    stSrcBuffer.stCanvas.u32Width   = 4;
    stSrcBuffer.stCanvas.u32Height  = par->stExtendInfo.u32DisplayHeight;
    stSrcBuffer.stCanvas.u32Pitch   = 16;
    stSrcBuffer.stCanvas.enFmt      = HIFB_FMT_ARGB8888;
    stSrcBuffer.UpdateRect.x = 0;
    stSrcBuffer.UpdateRect.y = 0;
    stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
    stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

    HI_GFX_Memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
    stDstBuffer.stCanvas.u32PhyAddr = GBHeadDdr;

#if 0
    HI_PRINT("\n===========================================\n");
    HI_PRINT("src ddr = 0x%lx\n",(unsigned long)stSrcBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("dst ddr = 0x%lx\n",(unsigned long)stDstBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("width = %d\n",stSrcBuffer.stCanvas.u32Width);
    HI_PRINT("height = %d\n",stSrcBuffer.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",stSrcBuffer.stCanvas.u32Pitch);
    HI_PRINT("===========================================\n");
#endif
    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stSrcBuffer, &stDstBuffer, HI_FALSE);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    HI_GFX_CHECK_UINT_MULTIPLICATION_REVERSAL_RETURN(stSrcBuffer.stCanvas.u32PhyAddr,HeadSize,HI_FAILURE);
    stSrcBuffer.stCanvas.u32PhyAddr = stSrcBuffer.stCanvas.u32PhyAddr + HeadSize;

    stSrcBuffer.stCanvas.u32Width  = par->stExtendInfo.u32DisplayWidth;
    stSrcBuffer.stCanvas.u32Height = par->stExtendInfo.u32DisplayHeight;
    stSrcBuffer.stCanvas.u32Pitch  = CmpStride;
    stSrcBuffer.stCanvas.enFmt     = HIFB_FMT_ARGB1555;
    stSrcBuffer.UpdateRect.x = 0;
    stSrcBuffer.UpdateRect.y = 0;
    stSrcBuffer.UpdateRect.w = stSrcBuffer.stCanvas.u32Width;
    stSrcBuffer.UpdateRect.h = stSrcBuffer.stCanvas.u32Height;

    HI_GFX_Memcpy(&stDstBuffer, &stSrcBuffer, sizeof(HIFB_BUFFER_S));
    stDstBuffer.stCanvas.u32PhyAddr = GBDataDdr;

#if 0
    HI_PRINT("\n===========================================\n");
    HI_PRINT("src ddr = 0x%lx\n",(unsigned long)stSrcBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("dst ddr = 0x%lx\n",(unsigned long)stDstBuffer.stCanvas.u32PhyAddr);
    HI_PRINT("width = %d\n",stSrcBuffer.stCanvas.u32Width);
    HI_PRINT("height = %d\n",stSrcBuffer.stCanvas.u32Height);
    HI_PRINT("stride = %d\n",stSrcBuffer.stCanvas.u32Pitch);
    HI_PRINT("===========================================\n");
#endif
    Ret = g_stGfx2dCallBackFunction.HIFB_DRV_QuickCopy(&stSrcBuffer, &stDstBuffer, HI_FALSE);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }
 #endif

    return Ret;
}

static inline HI_VOID HIFB_SNAPSHOT_WriteDispDataToFile(HI_U32 LayerID, HI_CHAR* pData, HI_U32 BufSize, HIFB_BUFFER_S *pstDstBuffer)
{
    HI_U32 Row = 0;
    HI_S8 *pTemp = NULL;
    struct file* pFileFd = NULL;
    BMP_BMFHEADER_S sBmpHeader;
    BMP_BMIHEADER_S sBmpInfoHeader;
    HI_CHAR SaveFileName[HIFB_FILE_PATH_MAX_LEN] = {'\0'};
    struct fb_info *info = NULL;
    HIFB_PAR_S *par = NULL;

    HIFB_CHECK_LAYERID_SUPPORT_UNRETURN(LayerID);
    info = s_stLayer[LayerID].pstInfo;
    HIFB_CHECK_NULLPOINTER_UNRETURN(info);

    par = (HIFB_PAR_S *)(info->par);
    HIFB_CHECK_NULLPOINTER_UNRETURN(par);

    HI_GFX_Memset(&sBmpHeader,    0x0, sizeof(sBmpHeader));
    HI_GFX_Memset(&sBmpInfoHeader,0x0, sizeof(sBmpInfoHeader));

    HIFB_CHECK_NULLPOINTER_UNRETURN(pData);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstDstBuffer);

    sBmpHeader.u16Type              = 0x4D42;
    sBmpHeader.u32Size              = BufSize + sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);
    sBmpHeader.u16Reserved1         = 0;
    sBmpHeader.u16Reserved2         = 0;
    sBmpHeader.u32OffBits           = sizeof(BMP_BMFHEADER_S) + sizeof(BMP_BMIHEADER_S);

    sBmpInfoHeader.u32Size          = sizeof(BMP_BMIHEADER_S);
    sBmpInfoHeader.u32Width         = pstDstBuffer->stCanvas.u32Width;
    sBmpInfoHeader.u32Height        = pstDstBuffer->stCanvas.u32Height;
    sBmpInfoHeader.u32Planes        = 1;
    sBmpInfoHeader.u32PixbitCount   = 24;
    sBmpInfoHeader.u32Compression   = 0;
    sBmpInfoHeader.u32SizeImage     = 0;
    sBmpInfoHeader.u32XPelsPerMeter = pstDstBuffer->stCanvas.u32Width;
    sBmpInfoHeader.u32YPelsPerMeter = pstDstBuffer->stCanvas.u32Height;
    sBmpInfoHeader.u32ClrUsed       = 0;
    sBmpInfoHeader.u32ClrImportant  = 0;

    if (HI_TRUE == par->bDeCompress)
    {
         snprintf(SaveFileName, sizeof(SaveFileName),"/data/hifb%d_snapshot.cmp", LayerID);
    }
    else
    {
         snprintf(SaveFileName, sizeof(SaveFileName),"/data/hifb%d_snapshot.bmp", LayerID);
    }
    SaveFileName[sizeof(SaveFileName) - 1] = '\0';

    pFileFd = filp_open(SaveFileName, O_WRONLY | O_CREAT | O_LARGEFILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (IS_ERR(pFileFd))
    {
        HIFB_ERROR("fail to open file %s.\n",SaveFileName);
        return;
    }

    if (HI_FALSE == par->bDeCompress)
    {
        if (sizeof(BMP_BMFHEADER_S) != HI_DRV_FILE_Write(pFileFd, (HI_S8*)&sBmpHeader, sizeof(BMP_BMFHEADER_S)))
        {
            HIFB_ERROR("Write data to file %s failure.\n",SaveFileName);
            HI_DRV_FILE_Close(pFileFd);
            return;
        }

        if (sizeof(BMP_BMIHEADER_S) != HI_DRV_FILE_Write(pFileFd, (HI_S8*)&sBmpInfoHeader, sizeof(BMP_BMIHEADER_S)))
        {
            HIFB_ERROR("Write data to file %s failure.\n",SaveFileName);
            HI_DRV_FILE_Close(pFileFd);
            return;
        }
    }

    if (HI_TRUE == par->bDeCompress)
    {
     #ifdef CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE
        for (Row = 0; Row < pstDstBuffer->stCanvas.u32Height; Row++)
        {
             pTemp = pData + Row * pstDstBuffer->stCanvas.u32Pitch;
             HI_DRV_FILE_Write(pFileFd, (HI_S8*)pTemp, pstDstBuffer->stCanvas.u32Pitch);
        }
      #else
        HI_DRV_FILE_Write(pFileFd, (HI_S8*)pData, BufSize);
      #endif
        HI_DRV_FILE_Close(pFileFd);
        HI_PRINT("success to capture fb%d, store in file %s\n", LayerID, SaveFileName);
        return;
    }

    Row = pstDstBuffer->stCanvas.u32Height;
    pTemp = pData;
    pTemp += (pstDstBuffer->stCanvas.u32Pitch * (pstDstBuffer->stCanvas.u32Height - 1));
    while (Row)
    {
        HI_DRV_FILE_Write(pFileFd, (HI_S8*)pTemp, pstDstBuffer->stCanvas.u32Pitch);
        pTemp -= pstDstBuffer->stCanvas.u32Pitch;
        Row--;
    }

    HI_DRV_FILE_Close(pFileFd);

    HI_PRINT("success to capture fb%d, store in file %s\n", LayerID, SaveFileName);

    return;
}

static inline HI_VOID HIFB_SnapshotPrint(HIFB_BUFFER_S *pstSrcBuffer, HIFB_BUFFER_S *pstDstBuffer)
{
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstSrcBuffer);
    HIFB_CHECK_NULLPOINTER_UNRETURN(pstDstBuffer);

    HI_PRINT("\n=============================================================================\n");
    HI_PRINT("hifb_snapshot srcbuf info: phyadd 0x%x, width %d, height %d, stride %d\n",     \
                                                           pstSrcBuffer->stCanvas.u32PhyAddr,\
                                                           pstSrcBuffer->stCanvas.u32Width,  \
                                                           pstSrcBuffer->stCanvas.u32Height, \
                                                           pstSrcBuffer->stCanvas.u32Pitch);

    HI_PRINT("hifb_snapshot dstbuf info: phyadd 0x%x, width %d, height %d, stride %d\n",      \
                                                           pstDstBuffer->stCanvas.u32PhyAddr, \
                                                           pstDstBuffer->stCanvas.u32Width,   \
                                                           pstDstBuffer->stCanvas.u32Height,  \
                                                           pstDstBuffer->stCanvas.u32Pitch);
    HI_PRINT("=============================================================================\n");

    return;
}
#endif

#endif
