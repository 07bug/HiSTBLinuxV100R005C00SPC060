/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : jpeg_decode.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : decode images
                     CNcomment: JPEGÍ¼Æ¬½âÂëCNend\n
Function List      :
History            :
Date                           Author                     Modification
2018/01/01                     sdk                        Created file
************************************************************************************************/


/***************************** add include here*************************************************/
#include "hi_gfx_surface.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_layer.h"
#include "hi_gfx_sys.h"

#include "jpeg_decode.h"
#include "hi_drv_jpeg.h"
#include "hi_jpeg_api.h"

/***************************** Macro Definition ************************************************/

/***************************** Structure Definition ********************************************/

/***************************** Global Variable declaration *************************************/

/***************************** API forward declarations ****************************************/

static inline HI_S32 CalcScale(HI_U32 Width, HI_U32 Height, HI_BOOL *pVoDispSupport);

/***************************** API realization *************************************************/
HI_S32 JPEG_ADP_CreateDecode(HI_U32 *pDecHandle,HI_CHAR* pSrcBuf,HI_U32 u32SrcLen)
{
    HI_ULONG DecHandle = 0;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pDecHandle);
    CHECK_POINT_NULL(pSrcBuf);
    CHECK_PARA_ZERO(u32SrcLen);

    DecHandle = HI_JPEG_CreateDecompress((HI_U32)pSrcBuf, u32SrcLen, pSrcBuf, u32SrcLen, NULL, 0);
    if (0 == DecHandle)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (DecHandle > UINT_MAX)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       HI_JPEG_DestroyDecompress(DecHandle);
       return HI_FAILURE;
    }

    *pDecHandle = (HI_U32)DecHandle;

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 JPEG_ADP_GetImgInfo(HI_U32 DecHandle,HI_HANDLE hSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_JPEG_INFO_S stJpegInfo;
    HI_JPEG_OUT_INFO_S stOutInfo;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);
    HI_GFX_LOG_FuncEnter();

    CHECK_PARA_ZERO(DecHandle);

    Ret = HI_JPEG_ParseHeader(DecHandle);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_Memset(&stJpegInfo, 0x0, sizeof(stJpegInfo));
    HI_GFX_Memset(&stOutInfo, 0x0, sizeof(stOutInfo));

    stJpegInfo.bOutInfo = HI_FALSE;
    Ret = HI_JPEG_GetJpegInfo(DecHandle,&stJpegInfo);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    stOutInfo.OutFmt = (HI_TRUE == pstSurface->bVoDispSupport) ? (HI_JPEG_FMT_YUV420) : (stJpegInfo.enFmt);
    stOutInfo.scale_num   = 1;
    stOutInfo.scale_denom = CalcScale(stJpegInfo.u32Width[0], stJpegInfo.u32Height[0], &(pstSurface->bVoDispSupport));
    HI_JPEG_SetOutInfo(DecHandle, &stOutInfo);

    stJpegInfo.bOutInfo = HI_TRUE;
    Ret = HI_JPEG_GetJpegInfo(DecHandle,&stJpegInfo);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }

    if ((stJpegInfo.u32Width[0] < CONFIG_GFX_MINWIDTH) || (stJpegInfo.u32Width[0] > CONFIG_GFX_MAXWIDTH))
    {
        HI_GFX_DBG_PrintUInt(stJpegInfo.u32Width[0]);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINWIDTH);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXWIDTH);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((stJpegInfo.u32Height[0] < CONFIG_GFX_MINHEIGHT) || (stJpegInfo.u32Height[0] > CONFIG_GFX_MAXHEIGHT))
    {
        HI_GFX_DBG_PrintUInt(stJpegInfo.u32Height[0]);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINHEIGHT);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXHEIGHT);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((stJpegInfo.u32Width[1] < CONFIG_GFX_MINWIDTH) || (stJpegInfo.u32Width[1] > CONFIG_GFX_MAXWIDTH))
    {
        HI_GFX_DBG_PrintUInt(stJpegInfo.u32Width[1]);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINWIDTH);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXWIDTH);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((stJpegInfo.u32Height[1] < CONFIG_GFX_MINHEIGHT) || (stJpegInfo.u32Height[1] > CONFIG_GFX_MAXHEIGHT))
    {
        HI_GFX_DBG_PrintUInt(stJpegInfo.u32Height[1]);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINHEIGHT);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXHEIGHT);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    pstSurface->u32Width[0]  = stJpegInfo.u32Width[0];
    pstSurface->u32Height[0] = stJpegInfo.u32Height[0];
    pstSurface->u32Stride[0] = stJpegInfo.u32OutStride[0];
    pstSurface->u32Size[0]   = stJpegInfo.u32OutSize[0];
    pstSurface->u32Width[1]  = stJpegInfo.u32Width[1];
    pstSurface->u32Height[1] = stJpegInfo.u32Height[1];
    pstSurface->u32Stride[1] = stJpegInfo.u32OutStride[1];
    pstSurface->u32Size[1]   = stJpegInfo.u32OutSize[1];
    switch (stJpegInfo.enFmt)
    {
        case HI_JPEG_FMT_YUV400:
            pstSurface->enPixelFormat = HI_GFX_PF_YUV400;
            break;
        case HI_JPEG_FMT_YUV420:
            pstSurface->enPixelFormat = HI_GFX_PF_YUV420;
            break;
        case HI_JPEG_FMT_YUV444:
            pstSurface->enPixelFormat = HI_GFX_PF_YUV444;
            break;
        case HI_JPEG_FMT_YUV422_12:
            pstSurface->enPixelFormat = HI_GFX_PF_YUV422_12;
            break;
        case HI_JPEG_FMT_YUV422_21:
            pstSurface->enPixelFormat = HI_GFX_PF_YUV422_21;
            break;
        default:
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            return HI_FAILURE;
    }

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

static inline HI_S32 CalcScale(HI_U32 Width, HI_U32 Height, HI_BOOL *pVoDispSupport)
{
    HI_S32 Scale = 0;
    HI_GFX_LOG_FuncEnter();

    *pVoDispSupport = HI_FALSE;

    if( (Width >= CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH * 2) || (Height >= CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT * 2))
    {
        Scale = 8;
    }
    else if ( (Width > CONFIG_GFX_DISP_REALLY4K_VIRTUAL_WIDTH) || (Height > CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT))
    {
        Scale = 4;
    }
    else
    {
        Scale = 1;
    }

#ifdef CONFIG_GFX_SUPPORT_VO_4K
    if ( (Width >= CONFIG_GFX_DISP_4K_VIRTUAL_WIDTH) && (Height >= CONFIG_GFX_DISP_4K_VIRTUAL_HEIGHT))
    {
        *pVoDispSupport = HI_TRUE;
        Scale = 1;
    }
#endif

    HI_GFX_LOG_FuncExit();
    return Scale;
}

HI_S32 JPEG_ADP_StartDecode(HI_U32 DecHandle, HI_HANDLE hSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_JPEG_SURFACE_S stSurfaceDesc;
    HI_JPEG_INFO_S stJpegInfo;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    HI_GFX_LOG_FuncEnter();
    CHECK_POINT_NULL(pstSurface);

    CHECK_PARA_ZERO(DecHandle);

    HI_GFX_Memset(&stSurfaceDesc,0,sizeof(stSurfaceDesc));
    HI_GFX_Memset(&stJpegInfo,0,sizeof(stJpegInfo));

    stJpegInfo.bOutInfo = HI_TRUE;
    Ret = HI_JPEG_GetJpegInfo(DecHandle,&stJpegInfo);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }

    stSurfaceDesc.u32OutPhy[0]    = (HI_U32)pstSurface->pPhyAddr[0];
    stSurfaceDesc.u32OutPhy[1]    = (HI_U32)pstSurface->pPhyAddr[1];
    stSurfaceDesc.pOutVir[0]      = pstSurface->pPhyAddr[0];
    stSurfaceDesc.pOutVir[1]      = pstSurface->pPhyAddr[1];
    stSurfaceDesc.u32OutStride[0] = stJpegInfo.u32OutStride[0];
    stSurfaceDesc.u32OutStride[1] = stJpegInfo.u32OutStride[1];

    Ret = HI_JPEG_SetOutDesc(DecHandle,&stSurfaceDesc);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }

    Ret = HI_JPEG_StartDecompress(DecHandle);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 JPEG_ADP_DestroyDecode(HI_U32 DecHandle)
{
    HI_GFX_LOG_FuncEnter();
    CHECK_PARA_ZERO(DecHandle);
    HI_JPEG_DestroyDecompress(DecHandle);
    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}
