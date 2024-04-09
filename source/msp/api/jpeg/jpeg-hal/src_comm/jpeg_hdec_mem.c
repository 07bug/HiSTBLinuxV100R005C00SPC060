/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_mem.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "hi_jpeg_config.h"
#include  "hi_gfx_comm.h"
#include  "jpeg_hdec_api.h"

#include  "jpeg_hdec_mem.h"

/***************************** Macro Definition ***************************************************/
#ifdef CONFIG_GFX_MMU_SUPPORT
#define MMZ_TAG                 "iommu"
#else
#define MMZ_TAG                 "mmz"
#endif

#define INPUT_DATA_MODULE       "JPEG_INPUT_DATA_BUF"
#define DEC_YUVSP_MODULE        "JPEG_DECODE_YUVSP_BUF"
#define DEC_XRGB_MODULE         "JPEG_DECODE_XRGB_BUF"
#define DEC_XRGB_MIN_MODULE     "JPEG_DECODE_XRGB_MIN_BUF"

/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/
static HI_S32 JPEG_HDEC_AllocInputDataBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, const HI_U32 InputDataSize);
static HI_S32 JPEG_HDEC_AllocYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_S32 JPEG_HDEC_AllocXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);

static HI_VOID JPEG_HDEC_FreeInputDataBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_VOID JPEG_HDEC_FreeXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);

/***************************** API realization ****************************************************/
static HI_BOOL JPEG_HDEC_AllocDecodeMemory(HI_ULONG HdecHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FALSE;
    }

    Ret = JPEG_HDEC_AllocInputDataBuf(pJpegHandle,(CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE) * CONFIG_JPED_INPUT_DATA_BUFFER_NUM);
    if (HI_SUCCESS != Ret)
    {
       return HI_FALSE;
    }

    Ret = JPEG_HDEC_AllocYUVMem(pJpegHandle);
    if (HI_SUCCESS != Ret)
    {
       return HI_FALSE;
    }

    Ret = JPEG_HDEC_GetMinMem(pJpegHandle);
    if (HI_SUCCESS != Ret)
    {
       return HI_FALSE;
    }

    Ret = JPEG_HDEC_AllocXRGBMem(pJpegHandle);
    if (HI_SUCCESS != Ret)
    {
       return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_S32 JPEG_HDEC_AllocInputDataBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, const HI_U32 InputDataSize)
{
    HI_U32 SaveStreamPhyBuf = 0;
    HI_U32 SaveStreamBufIndex = 0;
    HI_CHAR* pSaveStreamVirBuf = NULL;
    HI_BOOL bMemMMUType  = HI_TRUE;

    if (0 == InputDataSize)
    {
        return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
         return HI_SUCCESS;
    }

#ifdef CONFIG_GFX_MEM_ION
    SaveStreamPhyBuf = HI_GFX_AllocMem(pJpegHandle->MemDev,InputDataSize, CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)INPUT_DATA_MODULE, &(pJpegHandle->pSaveStreamMemHandle),&bMemMMUType);
#else
    SaveStreamPhyBuf = HI_GFX_AllocMem(InputDataSize, CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)INPUT_DATA_MODULE, &bMemMMUType);
#endif

    if (0 == SaveStreamPhyBuf)
    {
        return HI_FAILURE;
    }

    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamPhyBuf = SaveStreamPhyBuf + SaveStreamBufIndex * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE);
    }

#ifdef CONFIG_GFX_MEM_ION
    pSaveStreamVirBuf = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->MemDev,SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
    pSaveStreamVirBuf = (HI_CHAR*)HI_GFX_MapCached(SaveStreamPhyBuf, bMemMMUType);
#endif
    if (NULL == pSaveStreamVirBuf)
    {
        return HI_FAILURE;
    }

    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamBufSize = CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].pSaveStreamVirBuf = (HI_CHAR*)(pSaveStreamVirBuf + SaveStreamBufIndex * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE));
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (HI_TRUE != bMemMMUType)
    {
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

static HI_S32 JPEG_HDEC_AllocYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 u32MemSize   = 0;
    HI_U32 DecOutPhy    = 0;
    HI_U32 u32Align     = JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN;
    HI_BOOL bMemMMUType = HI_TRUE;

    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_TRUE == pJpegHandle->bOutYCbCrSP))
    {
         pJpegHandle->stDecSurface.BufPhy[0] = pJpegHandle->stOutSurface.BufPhy[0];
         pJpegHandle->stDecSurface.BufPhy[1] = pJpegHandle->stOutSurface.BufPhy[1];
         pJpegHandle->stDecSurface.BufPhy[2] = pJpegHandle->stOutSurface.BufPhy[2];
         pJpegHandle->stDecSurface.BufVir[0] = pJpegHandle->stOutSurface.BufVir[0];
         pJpegHandle->stDecSurface.BufVir[1] = pJpegHandle->stOutSurface.BufVir[1];
         pJpegHandle->stDecSurface.BufVir[2] = pJpegHandle->stOutSurface.BufVir[2];
         pJpegHandle->stDecSurface.Stride[0] = pJpegHandle->stOutSurface.Stride[0];
         pJpegHandle->stDecSurface.Stride[1] = pJpegHandle->stOutSurface.Stride[1];
         pJpegHandle->stDecSurface.Stride[2] = pJpegHandle->stOutSurface.Stride[2];
         return HI_SUCCESS;
    }

    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return HI_SUCCESS;
    }

    if ((0 == pJpegHandle->stJpegSofInfo.u32YSize) || (pJpegHandle->stJpegSofInfo.u32YSize > (UINT_MAX - pJpegHandle->stJpegSofInfo.u32CSize)))
    {
        return HI_FAILURE;
    }

    u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize + pJpegHandle->stJpegSofInfo.u32CSize;
    if (0 == u32MemSize)
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MEM_ION
    DecOutPhy = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_YUVSP_MODULE, &(pJpegHandle->pMiddleMemHandle),&bMemMMUType);
#else
    DecOutPhy = HI_GFX_AllocMem(u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_YUVSP_MODULE, &bMemMMUType);
#endif
    if (0 == DecOutPhy)
    {
        return HI_FAILURE;
    }

    pJpegHandle->stDecSurface.BufPhy[0] = DecOutPhy;
    pJpegHandle->stDecSurface.BufPhy[1] = DecOutPhy + pJpegHandle->stJpegSofInfo.u32YSize;

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (HI_TRUE != bMemMMUType)
    {
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}

static HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef CONFIG_JPEG_HARDDEC2ARGB
    HI_UNUSED(pJpegHandle);
#else
    HI_U32 u32MemSize = 0;
    HI_BOOL bMemMMUType = HI_TRUE;

    if (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return HI_SUCCESS;
    }

    u32MemSize = pJpegHandle->stJpegSofInfo.u32RGBSizeReg;
    if (0 == u32MemSize)
    {
        return HI_FAILURE;
    }

    #ifdef CONFIG_GFX_MEM_ION
    pJpegHandle->DecXRGBLinePhyBuf = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_XRGB_MIN_MODULE, &(pJpegHandle->pMinMemHandle),&bMemMMUType);
    #else
    pJpegHandle->DecXRGBLinePhyBuf = HI_GFX_AllocMem(u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)DEC_XRGB_MIN_MODULE, &bMemMMUType);
    #endif
    if (0 == pJpegHandle->DecXRGBLinePhyBuf)
    {
        return HI_FAILURE;
    }

    #ifdef CONFIG_GFX_MMU_SUPPORT
    if (HI_TRUE != bMemMMUType)
    {
        return HI_FAILURE;
    }
    #endif

#endif
    return HI_SUCCESS;
}

static HI_S32 JPEG_HDEC_AllocXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL bMemMMUType = HI_TRUE;
    HI_U32 u32OutStride = 0;
    HI_U32 u32MemSize   = 0;
    HI_ULONG tmp_value = 0;

    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
        return HI_SUCCESS;
    }

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {/** csc to xrgb **/
        return HI_SUCCESS;
    }

    u32OutStride = pJpegHandle->stJpegSofInfo.DecOutStride;

    tmp_value = (HI_ULONG)u32OutStride * (HI_ULONG)pJpegHandle->stOutSurface.stCropRect.h;
    if ((0 == tmp_value) || (tmp_value > UINT_MAX))
    {
        return HI_FAILURE;
    }
    u32MemSize = (HI_U32)tmp_value;

#ifdef CONFIG_GFX_MEM_ION
    pJpegHandle->stOutSurface.BufPhy[0] = HI_GFX_AllocMem(pJpegHandle->MemDev,u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)DEC_XRGB_MODULE, &(pJpegHandle->pOutMemHandle),&bMemMMUType);
#else
    pJpegHandle->stOutSurface.BufPhy[0] = HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)DEC_XRGB_MODULE, &bMemMMUType);
#endif
    if (0 == pJpegHandle->stOutSurface.BufPhy[0])
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MEM_ION
    pJpegHandle->stOutSurface.BufVir[0] = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->MemDev,pJpegHandle->stOutSurface.BufPhy[0], pJpegHandle->pOutMemHandle);
#else
    pJpegHandle->stOutSurface.BufVir[0] = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->stOutSurface.BufPhy[0], bMemMMUType);
#endif
    if (NULL == pJpegHandle->stOutSurface.BufVir[0])
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MEM_ION
    Ret = HI_GFX_Flush(pJpegHandle->MemDev,pJpegHandle->stOutSurface.BufPhy[0], pJpegHandle->pOutMemHandle);
#else
    Ret = HI_GFX_Flush(pJpegHandle->stOutSurface.BufPhy[0], bMemMMUType);
#endif
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_MMU_SUPPORT
    if (HI_TRUE != bMemMMUType)
    {
        return HI_FAILURE;
    }
#endif

    return HI_SUCCESS;
}


static HI_VOID JPEG_HDEC_FreeDecodeMemory(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    JPEG_HDEC_FreeInputDataBuf(pJpegHandle);

    JPEG_HDEC_FreeYUVMem(pJpegHandle);

    JPEG_HDEC_FreeMinMem(pJpegHandle);

    JPEG_HDEC_FreeXRGBMem(pJpegHandle);

    return;
}

static HI_VOID JPEG_HDEC_FreeInputDataBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 SaveStreamBufIndex = 0;

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
        return;
    }

    if (0 ==  pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf)
    {
         return;
    }

#ifdef CONFIG_GFX_MEM_ION
    if (NULL != pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf)
    {
       (HI_VOID)HI_GFX_Unmap(pJpegHandle->MemDev,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
    }
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle,HI_TRUE);
#else
    if (NULL != pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf)
    {
       (HI_VOID)HI_GFX_Unmap(pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, HI_TRUE);
    }
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf, HI_TRUE);
#endif

    for (SaveStreamBufIndex = 0; SaveStreamBufIndex < CONFIG_JPED_INPUT_DATA_BUFFER_NUM; SaveStreamBufIndex++)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamPhyBuf = 0;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].pSaveStreamVirBuf = NULL;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[SaveStreamBufIndex].SaveStreamBufSize = 0;
    }

    return;
}


static HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if ((HI_TRUE == pJpegHandle->bOutUsrBuf) && (HI_TRUE == pJpegHandle->bOutYCbCrSP))
    {
       return;
    }

    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return;
    }

    if (0 == pJpegHandle->stDecSurface.BufPhy[0])
    {
        return;
    }

#ifdef CONFIG_GFX_MEM_ION
   (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stDecSurface.BufPhy[0], pJpegHandle->pMiddleMemHandle,HI_TRUE);
#else
   (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stDecSurface.BufPhy[0], HI_TRUE);
#endif

    pJpegHandle->stDecSurface.BufPhy[0]  = 0;
    pJpegHandle->stDecSurface.BufPhy[1]  = 0;
    pJpegHandle->stDecSurface.BufPhy[2]  = 0;
    pJpegHandle->stDecSurface.BufVir[0]  = NULL;
    pJpegHandle->stDecSurface.BufVir[1]  = NULL;
    pJpegHandle->stDecSurface.BufVir[2]  = NULL;

    return;
}

static HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef CONFIG_JPEG_HARDDEC2ARGB
    HI_UNUSED(pJpegHandle);
#else
    if (HI_TRUE != pJpegHandle->bDecOutColorSpaecXRGB)
    {
        return;
    }

    if (0 == pJpegHandle->DecXRGBLinePhyBuf)
    {
        return;
    }

    #ifdef CONFIG_GFX_MEM_ION
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->DecXRGBLinePhyBuf, pJpegHandle->pMinMemHandle,HI_TRUE);
    #else
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->DecXRGBLinePhyBuf,HI_TRUE);
    #endif

    pJpegHandle->DecXRGBLinePhyBuf = 0;
#endif

    return;
}

static HI_VOID JPEG_HDEC_FreeXRGBMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
        return;
    }

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {
        return;
    }

    if (0 == pJpegHandle->stOutSurface.BufPhy[0])
    {
        return;
    }

#ifdef CONFIG_GFX_MEM_ION
    (HI_VOID)HI_GFX_Unmap(pJpegHandle->MemDev,pJpegHandle->stOutSurface.BufPhy[0], pJpegHandle->pOutMemHandle);
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->MemDev,pJpegHandle->stOutSurface.BufPhy[0], pJpegHandle->pOutMemHandle,HI_TRUE);
#else
    (HI_VOID)HI_GFX_Unmap(pJpegHandle->stOutSurface.BufPhy[0], HI_TRUE);
    (HI_VOID)HI_GFX_FreeMem(pJpegHandle->stOutSurface.BufPhy[0], HI_TRUE);
#endif

    pJpegHandle->stOutSurface.BufPhy[0]  = 0;
    pJpegHandle->stOutSurface.BufVir[0] = NULL;

    return;
}

static HI_VOID JPEG_HDEC_FlushBuf(HI_ULONG HdecHandle, HI_U32 PhyAddr)
{
#ifdef CONFIG_GFX_MEM_ION
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }
    (HI_VOID)HI_GFX_Flush(pJpegHandle->MemDev, PhyAddr, pJpegHandle->pSaveStreamMemHandle);
#else
    (HI_VOID)HI_GFX_Flush(PhyAddr, HI_TRUE);
#endif

    return;
}

#ifdef CONFIG_GFX_MEM_ION
static HI_S32 JPEG_HDEC_OpenMemDev(HI_VOID)
{
    return gfx_mem_open();
}

static HI_VOID JPEG_DEC_CloseMemDev(HI_S32 Device)
{
    gfx_mem_close(Device);
}
#endif
