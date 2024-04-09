/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name	    : sample_enc_api.c
Version		    : Initial Draft
Author		    :
Created		    : 2018/01/01
Description	    :
Function List 	:


History       	:
Date				Author        		Modification
2018/01/01  	    sdk  		        Created file
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <setjmp.h>
#include <sys/time.h>

#include "hi_type.h"
#include "hi_jpge_api.h"
#include "hi_jpge_type.h"
#include "hi_jpge_errcode.h"

#include "hi_tde_api.h"
#include "hi_tde_errcode.h"
#include "hi_tde_type.h"

#include "jpeglib.h"
#include "jerror.h"

#include "sample_enc_api.h"

#include "hi_common.h"

#ifdef CONFIG_LINUX_OS
#include "hi_jpeg_api.h"
#else
#include "utils/Log.h"
#endif

/***************************** Macro Definition *************************************************/
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG     "sample_enc"

#ifdef CONFIG_LINUX_OS
#define SAMPLE_TRACE(fmt, args...)\
            do{ \
                fprintf(stderr,fmt, ##args );\
            }while(0)
#else
#define SAMPLE_TRACE    ALOGE
#endif

#define SAMPLE_INPUT_JPEG_FILE        "./../res/jpg/image1.jpg"
#define SAMPLE_ENCODE_JPEG_FILE       "./../res/jpg/image1_enc.jpg"
#define SAMPLE_MAX_PATH               256

#define SAMPLE_TINIT()   struct timeval tv_start, tv_end; unsigned int time_cost,line_start
#define SAMPLE_TSTART()  gettimeofday(&tv_start, NULL);line_start = __LINE__
#define SAMPLE_TEND()    \
    gettimeofday(&tv_end, NULL); \
    time_cost = ((tv_end.tv_usec - tv_start.tv_usec)/1000 + (tv_end.tv_sec - tv_start.tv_sec)*1000); \
    SAMPLE_TRACE("=============================================================================\n"); \
    SAMPLE_TRACE("FROM LINE: %d TO LINE: %d COST: %d ms\n",line_start, __LINE__, time_cost);         \
    SAMPLE_TRACE("=============================================================================\n")

/*************************** Structure Definition ***********************************************/

typedef struct tagJPEG_MYERR_S
{
    struct jpeg_error_mgr pub;
}JPEG_MYERR_S;

typedef struct tagSAMPLE_JPGE_INFO_S
{
    HI_U32  YuvSampleType;
    HI_U32  YuvFmtType;
    HI_U32  Qlevel;

    HI_U32  Width[JPGE_INPUT_COMPONENT_NUM];
    HI_U32  Height[JPGE_INPUT_COMPONENT_NUM];
    HI_U32  Stride[JPGE_INPUT_COMPONENT_NUM];
    HI_U32  PhyBuf[JPGE_INPUT_COMPONENT_NUM];

    HI_U32  OutWidth;
    HI_U32  OutHeight;
	HI_U32  OutStride;
    HI_U32  OutPhyBuf;
    HI_CHAR *pOutVirBuf;
    HI_CHAR *pOutFileName;
}SAMPLE_JPGE_INFO_S;

/********************** Global Variable declaration *********************************************/

static jmp_buf gs_enc_setjmp_buffer;

#ifdef CONFIG_LINUX_OS
static jmp_buf gs_dec_setjmp_buffer;
#endif

/******************************* API declaration ************************************************/
static TDE2_MB_COLOR_FMT_E GetTdeFmt(HI_U32 YuvFmtType)
{
    if (JPGE_INPUT_FMT_YUV420 == YuvFmtType)
    {
        return TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP;
    }

    if (JPGE_INPUT_FMT_YUV422 == YuvFmtType)
    {
        return TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP;
    }

    if (JPGE_INPUT_FMT_YUV444 == YuvFmtType)
    {
        return TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP;
    }

    return TDE2_MB_COLOR_FMT_BUTT;
}

static HI_S32 YuvToRgb(SAMPLE_JPGE_INFO_S *pstInputInfo)
{
    HI_S32 Ret =  HI_SUCCESS;
    TDE2_MB_S SrcSurface;
    TDE2_SURFACE_S DstSurface;
    TDE2_RECT_S SrcRect,DstRect;
    TDE2_MBOPT_S stMbOpt;
    TDE_HANDLE s32Handle;

    if (NULL == pstInputInfo)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (JPGE_INPUT_FMT_YUV420 != pstInputInfo->YuvFmtType)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (JPGE_INPUT_SAMPLER_SEMIPLANNAR != pstInputInfo->YuvSampleType)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    memset(&SrcRect,    0,   sizeof(SrcRect));
    memset(&DstRect,    0,   sizeof(DstRect));
    memset(&SrcSurface, 0,   sizeof(SrcSurface));
    memset(&DstSurface, 0,   sizeof(DstSurface));
    memset(&stMbOpt,    0,   sizeof(stMbOpt));

    SrcSurface.u32YWidth      = pstInputInfo->Width[0];
    SrcSurface.u32YHeight     = pstInputInfo->Height[0];
    SrcSurface.u32YStride     = pstInputInfo->Stride[0];
    SrcSurface.u32CbCrStride  = pstInputInfo->Stride[1];
	SrcSurface.u32YPhyAddr    = pstInputInfo->PhyBuf[0];
    SrcSurface.u32CbCrPhyAddr = pstInputInfo->PhyBuf[1];
    SrcSurface.enMbFmt        = GetTdeFmt(pstInputInfo->YuvFmtType);

    DstSurface.u32Width       = pstInputInfo->Width[0];
    DstSurface.u32Height      = pstInputInfo->Height[0];
	DstSurface.u32Stride      = pstInputInfo->OutStride;
    DstSurface.u32PhyAddr     = pstInputInfo->OutPhyBuf;
    DstSurface.enColorFmt     = TDE2_COLOR_FMT_BGR888;
    DstSurface.pu8ClutPhyAddr = NULL;
    DstSurface.bYCbCrClut     = HI_FALSE;
    DstSurface.bAlphaMax255   = HI_TRUE;
    DstSurface.bAlphaExt1555  = HI_TRUE;
    DstSurface.u8Alpha0       = 0;
    DstSurface.u8Alpha1       = 255;
    DstSurface.u32CbCrPhyAddr = 0;
    DstSurface.u32CbCrStride  = 0;

    SrcRect.s32Xpos   = 0;
    SrcRect.s32Ypos   = 0;
    SrcRect.u32Width  = SrcSurface.u32YWidth;
    SrcRect.u32Height = SrcSurface.u32YHeight;
    DstRect.s32Xpos   = 0;
    DstRect.s32Ypos   = 0;
    DstRect.u32Width  = DstSurface.u32Width;
    DstRect.u32Height = DstSurface.u32Height;

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TRACE("============================Beg Yuv2Rgb Msg ===================================\n");
    SAMPLE_TRACE("=====================================\n");
    SAMPLE_TRACE("SrcSurface.u32YWidth      = %d\n",   SrcSurface.u32YWidth);
    SAMPLE_TRACE("SrcSurface.u32YHeight     = %d\n",   SrcSurface.u32YHeight);
    SAMPLE_TRACE("SrcSurface.u32YStride     = %d\n",   SrcSurface.u32YStride);
    SAMPLE_TRACE("SrcSurface.u32CbCrStride  = %d\n",   SrcSurface.u32CbCrStride);
	SAMPLE_TRACE("SrcSurface.u32YPhyAddr    = 0x%x\n", SrcSurface.u32YPhyAddr);
	SAMPLE_TRACE("SrcSurface.u32CbCrPhyAddr = 0x%x\n", SrcSurface.u32CbCrPhyAddr);
	SAMPLE_TRACE("SrcSurface.enMbFmt        = %d\n",   SrcSurface.enMbFmt);
    SAMPLE_TRACE("=====================================\n");
	SAMPLE_TRACE("=====================================\n");
    SAMPLE_TRACE("DstSurface.u32Width       = %d\n",   DstSurface.u32Width);
    SAMPLE_TRACE("DstSurface.u32Height      = %d\n",   DstSurface.u32Height);
    SAMPLE_TRACE("DstSurface.u32Stride      = %d\n",   DstSurface.u32Stride);
	SAMPLE_TRACE("DstSurface.u32PhyAddr     = 0x%x\n", DstSurface.u32PhyAddr);
	SAMPLE_TRACE("DstSurface.enColorFmt     = %d\n",   DstSurface.enColorFmt);
    SAMPLE_TRACE("=====================================\n");
	SAMPLE_TRACE("=====================================\n");
    SAMPLE_TRACE("SrcRect.s32Xpos      = %d\n",SrcRect.s32Xpos);
    SAMPLE_TRACE("SrcRect.s32Ypos      = %d\n",SrcRect.s32Ypos);
    SAMPLE_TRACE("SrcRect.u32Width     = %d\n",SrcRect.u32Width);
    SAMPLE_TRACE("SrcRect.u32Height    = %d\n",SrcRect.u32Height);
    SAMPLE_TRACE("DstRect.s32Xpos      = %d\n",DstRect.s32Xpos);
    SAMPLE_TRACE("DstRect.s32Ypos      = %d\n",DstRect.s32Ypos);
    SAMPLE_TRACE("DstRect.u32Width     = %d\n",DstRect.u32Width);
    SAMPLE_TRACE("DstRect.u32Height    = %d\n",DstRect.u32Height);
    SAMPLE_TRACE("=====================================\n");
    SAMPLE_TRACE("============================End Yuv2Rgb Msg =================================\n\n");
#endif

    Ret = HI_TDE_Open();
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    s32Handle = HI_TDE2_BeginJob();
    if (HI_ERR_TDE_INVALID_HANDLE == s32Handle)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
		HI_TDE_Close();
        return HI_FAILURE;
    }

    stMbOpt.enResize = TDE2_MBRESIZE_NONE;
	Ret = HI_TDE2_MbBlit(s32Handle, &SrcSurface, &SrcRect, &DstSurface, &DstRect, &stMbOpt);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
		HI_TDE_Close();
        return HI_FAILURE;
    }

	Ret = HI_TDE2_EndJob(s32Handle, HI_TRUE, HI_TRUE, 1000);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
		HI_TDE_Close();
        return HI_FAILURE;
    }

	HI_TDE_Close();

    return HI_SUCCESS;
}

/****************************************************************************
* func          : jpeg_enc_err
* description	: CNcomment: 编码错误管理 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
static HI_VOID jpeg_enc_err(j_common_ptr cinfo)
{
    (*cinfo->err->output_message)(cinfo);
    longjmp(gs_enc_setjmp_buffer, 1);
}

/****************************************************************************
* func          : JPEG_SoftEncToFile
* description	: CNcomment: JPEG软件编码 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
static HI_S32 JPEG_SoftEncToFile(SAMPLE_JPGE_INFO_S *pstInputInfo)
{
    struct jpeg_compress_struct cinfo;
    JPEG_MYERR_S jerr;
    FILE *pOutFile    = NULL;
    JSAMPROW pRowBuf[1];
    HI_S32 Quality = 80;
    HI_S32 EncSuccess = HI_SUCCESS;
    HI_CHAR* pInputData = NULL;

    if ((NULL == pstInputInfo->pOutFileName) || (NULL == pstInputInfo))
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    pOutFile = fopen(pstInputInfo->pOutFileName, "wb+");
    if (NULL == pOutFile)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_enc_err;

    if (setjmp(gs_enc_setjmp_buffer))
    {
        EncSuccess = HI_FAILURE;
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ENCODE_EXIT;
    }

    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, pOutFile);

    cinfo.image_width      = pstInputInfo->OutWidth;
    cinfo.image_height     = pstInputInfo->OutHeight;
    cinfo.in_color_space   = JCS_RGB;
    cinfo.input_components = 3;

    jpeg_set_defaults(&cinfo);

    if ((0 == pstInputInfo->Qlevel) || (pstInputInfo->Qlevel >= 100))
    {
        Quality = 80;
    }
    else
    {
        Quality = pstInputInfo->Qlevel;
    }

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TRACE("============================Beg Soft Encode ===================================\n");
    SAMPLE_TRACE("Quality                 = %d\n",   Quality);
    SAMPLE_TRACE("cinfo.image_width       = %d\n",   cinfo.image_width);
    SAMPLE_TRACE("cinfo.image_height      = %d\n",   cinfo.image_height);
    SAMPLE_TRACE("cinfo.in_color_space    = %d\n",   cinfo.in_color_space);
    SAMPLE_TRACE("cinfo.input_components  = %d\n",   cinfo.input_components);
    SAMPLE_TRACE("input data buffer       = 0x%x\n", (unsigned int)pstInputInfo->pOutVirBuf);
    SAMPLE_TRACE("============================End Soft Encode =================================\n\n");
#endif

    jpeg_set_quality(&cinfo, Quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    pInputData = pstInputInfo->pOutVirBuf;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        pRowBuf[0] = (JSAMPLE FAR*)(&(pInputData[cinfo.next_scanline * pstInputInfo->OutStride]));
        jpeg_write_scanlines(&cinfo, pRowBuf, 1);
    }

    jpeg_finish_compress(&cinfo);

ENCODE_EXIT:

    jpeg_destroy_compress(&cinfo);

    if (NULL != pOutFile)
    {
        fclose(pOutFile);
        pOutFile = NULL;
    }

    return EncSuccess;
}

/****************************************************************************
* func          : JPEG_HardEncToFile
* description	: CNcomment: JPEG硬件编码 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
static HI_S32 JPEG_HardEncToFile(SAMPLE_JPGE_INFO_S *pstInputInfo)
{
    FILE* pOutFile = NULL;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 NeedSize = 0;
    Jpge_EncCfg_S EncCfg;
    Jpge_EncIn_S  EncIn;
    Jpge_EncOut_S EncOut;
    HI_U32 EncHandle = 0;
    HI_U32 OutSize = 0;

    if ((NULL == pstInputInfo->pOutFileName) || (NULL == pstInputInfo))
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

	memset(&EncCfg, 0x0, sizeof(EncCfg));
	memset(&EncIn,  0x0, sizeof(EncIn));
	memset(&EncOut, 0x0, sizeof(EncOut));

    Ret = HI_JPGE_Open();
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    EncCfg.FrameWidth    = pstInputInfo->Width[0];
    EncCfg.FrameHeight   = pstInputInfo->Height[0];
    EncCfg.YuvSampleType = pstInputInfo->YuvFmtType;
    EncCfg.YuvStoreType  = pstInputInfo->YuvSampleType;
    EncCfg.RotationAngle = 0;
    EncCfg.SlcSplitEn    = 0;
    EncCfg.SplitSize     = 0;

    if ((0 == pstInputInfo->Qlevel) || (pstInputInfo->Qlevel >= 100))
    {
        EncCfg.Qlevel = 80;
    }
    else
    {
        EncCfg.Qlevel = pstInputInfo->Qlevel;
    }

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TRACE("============================Beg Hard Encode ===================================\n");
    SAMPLE_TRACE("===================================\n");
    SAMPLE_TRACE("EncCfg.FrameWidth          = %d\n",EncCfg.FrameWidth);
    SAMPLE_TRACE("EncCfg.FrameHeight         = %d\n",EncCfg.FrameHeight);
    SAMPLE_TRACE("EncCfg.YuvSampleType       = %d\n",EncCfg.YuvSampleType);
    SAMPLE_TRACE("EncCfg.YuvStoreType        = %d\n",EncCfg.YuvStoreType);
    SAMPLE_TRACE("EncCfg.Qlevel              = %d\n",EncCfg.Qlevel);
    SAMPLE_TRACE("EncCfg.RotationAngle       = %d\n",EncCfg.RotationAngle);
    SAMPLE_TRACE("EncCfg.SlcSplitEn          = %d\n",EncCfg.SlcSplitEn);
    SAMPLE_TRACE("EncCfg.SplitSize           = %d\n",EncCfg.SplitSize);
    SAMPLE_TRACE("===================================\n");
#endif

    Ret = HI_JPGE_Create(&EncHandle,&EncCfg);
    if (HI_SUCCESS != Ret )
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERROR1;
    }

    EncIn.BusViY     = pstInputInfo->PhyBuf[0];
    EncIn.BusViC     = pstInputInfo->PhyBuf[1];
    EncIn.BusViV     = pstInputInfo->PhyBuf[2];
    EncIn.ViYStride  = pstInputInfo->Stride[0];
    EncIn.ViCStride  = pstInputInfo->Stride[1];

    EncIn.BusOutBuf  = pstInputInfo->OutPhyBuf;
    EncIn.pOutBuf    = (HI_U8*)pstInputInfo->pOutVirBuf;

    OutSize = pstInputInfo->OutStride * pstInputInfo->OutHeight;
    EncIn.OutBufSize = OutSize;

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TRACE("===================================\n");
    SAMPLE_TRACE("EncIn.BusViY          = 0x%x\n",EncIn.BusViY);
    SAMPLE_TRACE("EncIn.BusViC          = 0x%x\n",EncIn.BusViC);
    SAMPLE_TRACE("EncIn.BusViV          = 0x%x\n",EncIn.BusViV);
    SAMPLE_TRACE("EncIn.ViYStride       = %d\n",  EncIn.ViYStride);
    SAMPLE_TRACE("EncIn.ViCStride       = %d\n",  EncIn.ViCStride);
    SAMPLE_TRACE("EncIn.BusOutBuf       = 0x%x\n",EncIn.BusOutBuf);
    SAMPLE_TRACE("EncIn.pOutBuf         = 0x%x\n",(unsigned int)EncIn.pOutBuf);
    SAMPLE_TRACE("EncIn.OutBufSize      = %d\n",  EncIn.OutBufSize);
    SAMPLE_TRACE("===================================\n");
#endif

    Ret = HI_JPGE_Encode(EncHandle, &EncIn, &EncOut);
    if (HI_SUCCESS != Ret)
	{
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERROR0;
    }

    NeedSize = (HI_S32)((HI_U32)EncOut.pStream - (HI_U32)pstInputInfo->pOutVirBuf) + EncOut.StrmSize;
    if (NeedSize > OutSize)
	{
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERROR0;
    }

    if ((pOutFile = fopen(pstInputInfo->pOutFileName, "wb+")) == NULL)
	{
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERROR0;
    }

    fwrite(EncOut.pStream,1,EncOut.StrmSize,pOutFile);
    if (NULL != pOutFile)
	{
        fclose(pOutFile);
        pOutFile = NULL;
    }

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TRACE("===================================\n");
    SAMPLE_TRACE("EncOut.pStream          = 0x%x\n",(unsigned int)EncOut.pStream);
    SAMPLE_TRACE("EncOut.StrmSize         = %d\n",EncOut.StrmSize);
    SAMPLE_TRACE("===================================\n");
    SAMPLE_TRACE("============================End Hard Encode ===================================\n\n");
#endif

    Ret = HI_JPGE_Destroy(EncHandle);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERROR1;
    }

    HI_JPGE_Close();

    return HI_SUCCESS;

ERROR0:
    HI_JPGE_Destroy(EncHandle);

ERROR1:
    HI_JPGE_Close();

    if (NULL != pOutFile)
    {
        fclose(pOutFile);
        pOutFile = NULL;
    }

    return HI_FAILURE;
}

/****************************************************************************
* func          : HI_SAMPLE_Encode
* description	: CNcomment: 编码成jpeg图片 CNend\n
* param[in] 	: 只支持YUV420 SP格式的码流
* retval		: NA
* others:		: NA
******************************************************************************/
HI_S32 HI_SAMPLE_Encode(HI_CHAR *pOutFileName,SAMPLE_VIDEO_FREMAE_INFO_S *pstVideoFrameInfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL bHardEnc = HI_FALSE;
    SAMPLE_JPGE_INFO_S stJpgeInput;

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TINIT();
    SAMPLE_TSTART();
#endif

    if ((NULL == pOutFileName) || (NULL == pstVideoFrameInfo))
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (pstVideoFrameInfo->Stride[0] != pstVideoFrameInfo->Stride[1])
    {/** it is not yuv420 sp **/
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (0 != pstVideoFrameInfo->PhyBuf[2])
    {/** it is not yuv420 sp **/
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (pstVideoFrameInfo->Width[1] != (pstVideoFrameInfo->Width[0] >> 1))
    {
        /** it is not yuv420 sp **/
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

     if (pstVideoFrameInfo->Height[1] != (pstVideoFrameInfo->Height[0] >> 1))
    {
        /** it is not yuv420 sp **/
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (JPGE_INPUT_FMT_YUV420 != pstVideoFrameInfo->YuvFmtType)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    if (JPGE_INPUT_SAMPLER_SEMIPLANNAR != pstVideoFrameInfo->YuvSampleType)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    memset(&stJpgeInput,0,sizeof(stJpgeInput));

    stJpgeInput.YuvFmtType    = pstVideoFrameInfo->YuvFmtType;
    stJpgeInput.YuvSampleType = pstVideoFrameInfo->YuvSampleType;
    stJpgeInput.Qlevel        = pstVideoFrameInfo->Qlevel;

    stJpgeInput.Width[0]  = pstVideoFrameInfo->Width[0];
    stJpgeInput.Height[0] = pstVideoFrameInfo->Height[0];
    stJpgeInput.Stride[0] = pstVideoFrameInfo->Stride[0];
	stJpgeInput.PhyBuf[0] = pstVideoFrameInfo->PhyBuf[0];

    stJpgeInput.Width[1]  = pstVideoFrameInfo->Width[1];
    stJpgeInput.Height[1] = pstVideoFrameInfo->Height[1];
    stJpgeInput.Stride[1] = pstVideoFrameInfo->Stride[1];
	stJpgeInput.PhyBuf[1] = pstVideoFrameInfo->PhyBuf[1];

    stJpgeInput.pOutFileName = pOutFileName;
    stJpgeInput.OutWidth  = pstVideoFrameInfo->Width[0];
    stJpgeInput.OutHeight = pstVideoFrameInfo->Height[0];
	stJpgeInput.OutStride = (stJpgeInput.OutWidth * 3 + 16 - 1) & (~(16 - 1));

    stJpgeInput.OutPhyBuf = (HI_U32)HI_MMZ_New(stJpgeInput.OutStride * stJpgeInput.OutHeight, 64, NULL, "sample_enc_jpeg");
    if (0 == stJpgeInput.OutPhyBuf)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERR_EXIT;
    }

    stJpgeInput.pOutVirBuf = (HI_CHAR*)HI_MMZ_Map(stJpgeInput.OutPhyBuf, HI_FALSE);
    if (NULL == stJpgeInput.pOutVirBuf)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERR_EXIT;
    }

    Ret = JPEG_HardEncToFile(&stJpgeInput);
	if (HI_SUCCESS == Ret)
	{
        bHardEnc = HI_TRUE;
        goto ENC_FINISH;
	}

    Ret = YuvToRgb(&stJpgeInput);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERR_EXIT;
    }

    Ret = JPEG_SoftEncToFile(&stJpgeInput);
	if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto ERR_EXIT;
    }

ENC_FINISH:

    if (NULL != stJpgeInput.pOutVirBuf)
    {
        HI_MMZ_Unmap(stJpgeInput.OutPhyBuf);
    }

    if (0 != stJpgeInput.OutPhyBuf)
    {
        HI_MMZ_Delete(stJpgeInput.OutPhyBuf);
    }

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TEND();
#endif

    SAMPLE_TRACE("\n=============================================================================\n");
    if (HI_TRUE == bHardEnc)
    {
        SAMPLE_TRACE("hard enc %s success\n",stJpgeInput.pOutFileName);
    }
    else
    {
        SAMPLE_TRACE("soft enc %s success\n",stJpgeInput.pOutFileName);
    }
    SAMPLE_TRACE("=============================================================================\n");

    return HI_SUCCESS;

ERR_EXIT:
    if (NULL != stJpgeInput.pOutVirBuf)
    {
        HI_MMZ_Unmap(stJpgeInput.OutPhyBuf);
    }

    if (0 != stJpgeInput.OutPhyBuf)
    {
        HI_MMZ_Delete(stJpgeInput.OutPhyBuf);
    }

    SAMPLE_TRACE("\n=============================================================================\n");
    SAMPLE_TRACE("save %s failure\n",stJpgeInput.pOutFileName);
    SAMPLE_TRACE("=============================================================================\n");

#ifdef CONFIG_DEBUG_MSG
    SAMPLE_TEND();
#endif

    return HI_FAILURE;
}

#ifdef CONFIG_LINUX_OS
/****************************************************************************
* func          : jpeg_dec_err
* description	: CNcomment: 解码错误处理 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
static HI_VOID jpeg_dec_err(j_common_ptr cinfo)
{
    (*cinfo->err->output_message)(cinfo);
    longjmp(gs_dec_setjmp_buffer, 1);
}

/****************************************************************************
* func          : SAMPLE_JPEG_Decode
* description	: CNcomment: JPEG解码获取数据 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
static HI_S32 SAMPLE_JPEG_Decode(SAMPLE_VIDEO_FREMAE_INFO_S *pstVideoFrameInfo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_CHAR* pDataBuf = NULL;
	FILE* pInFile = NULL;
    JPEG_MYERR_S jerr;
	struct jpeg_decompress_struct cinfo;
    HI_JPEG_SURFACE_S stSurfaceDesc;
    HI_JPEG_INFO_S stJpegInfo;
    HI_JPEG_OUT_INFO_S stOutInfo;

    if (NULL == pstVideoFrameInfo)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    memset(&cinfo,         0x0,    sizeof(struct jpeg_decompress_struct));
    memset(&stSurfaceDesc, 0x0,    sizeof(HI_JPEG_SURFACE_S));
    memset(&stJpegInfo,    0x0,    sizeof(HI_JPEG_INFO_S));
    memset(&stOutInfo,     0x0,    sizeof(HI_JPEG_OUT_INFO_S));

    pInFile = fopen(SAMPLE_INPUT_JPEG_FILE,"rb");
	if (NULL == pInFile)
	{
	   SAMPLE_TRACE("open %s failure\n",SAMPLE_INPUT_JPEG_FILE);
       return HI_FAILURE;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = jpeg_dec_err;

	if (setjmp(gs_dec_setjmp_buffer))
	{
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
		goto DEC_FAILURE;
	}

	jpeg_create_decompress(&cinfo);

    jpeg_stdio_src(&cinfo, pInFile);

    jpeg_read_header(&cinfo, TRUE);

    stJpegInfo.bOutInfo = HI_FALSE;
    Ret = HI_JPEG_GetJpegInfo((HI_ULONG)(cinfo.client_data), &stJpegInfo);
    if (HI_SUCCESS != Ret)
    {
       SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
       goto DEC_FAILURE;
    }

	cinfo.scale_num       = 1 ;
    cinfo.scale_denom     = 1;
    cinfo.out_color_space = JCS_YUV420_SP;

    stOutInfo.scale_num   = cinfo.scale_num;
    stOutInfo.scale_denom = cinfo.scale_denom;
    stOutInfo.OutFmt      = HI_JPEG_FMT_YUV420;

    Ret = HI_JPEG_SetOutInfo((HI_ULONG)(cinfo.client_data), &stOutInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto DEC_FAILURE;
    }

    stJpegInfo.bOutInfo = HI_TRUE;
    Ret = HI_JPEG_GetJpegInfo((HI_ULONG)(cinfo.client_data), &stJpegInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto DEC_FAILURE;
    }

    pstVideoFrameInfo->Width[0]  = stJpegInfo.u32Width[0];
    pstVideoFrameInfo->Height[0] = stJpegInfo.u32Height[0];
    pstVideoFrameInfo->Stride[0] = stJpegInfo.u32OutStride[0];

    pstVideoFrameInfo->Width[1]  = stJpegInfo.u32Width[1];
    pstVideoFrameInfo->Height[1] = stJpegInfo.u32Height[1];
    pstVideoFrameInfo->Stride[1] = stJpegInfo.u32OutStride[1];

    pstVideoFrameInfo->PhyBuf[0] = (HI_U32)HI_MMZ_New((stJpegInfo.u32OutSize[0] + stJpegInfo.u32OutSize[1]), 128, NULL, "sample_dec_jpeg");
    pstVideoFrameInfo->PhyBuf[1] = pstVideoFrameInfo->PhyBuf[0] + stJpegInfo.u32OutSize[0];

    if (0 == pstVideoFrameInfo->PhyBuf[0])
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto DEC_FAILURE;
    }

    pDataBuf = (HI_CHAR*)HI_MMZ_Map(pstVideoFrameInfo->PhyBuf[0], HI_FALSE);
    if (NULL == pDataBuf)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto DEC_FAILURE;
    }

    stSurfaceDesc.u32OutPhy[0] = pstVideoFrameInfo->PhyBuf[0];
    stSurfaceDesc.u32OutPhy[1] = pstVideoFrameInfo->PhyBuf[1];
    stSurfaceDesc.pOutVir[0]   = pDataBuf;
    stSurfaceDesc.pOutVir[1]   = (HI_CHAR *)(pDataBuf + stJpegInfo.u32OutSize[0]);
    stSurfaceDesc.u32OutStride[0] = stJpegInfo.u32OutStride[0];
    stSurfaceDesc.u32OutStride[1] = stJpegInfo.u32OutStride[1];

    Ret = HI_JPEG_SetOutDesc((HI_ULONG)(cinfo.client_data), &stSurfaceDesc);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto DEC_FAILURE;
    }

    jpeg_start_decompress(&cinfo);

	while (cinfo.output_scanline < cinfo.output_height)
    {
	    jpeg_read_scanlines(&cinfo, NULL, 1);
	}

	jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);

    if (NULL != pInFile)
    {
		fclose(pInFile);
    }

    if (NULL != pDataBuf)
    {
        HI_MMZ_Unmap(pstVideoFrameInfo->PhyBuf[0]);
    }

	return HI_SUCCESS;

DEC_FAILURE:

  	jpeg_destroy_decompress(&cinfo);

    if (NULL != pInFile)
    {
		fclose(pInFile);
    }

    if (NULL != pDataBuf)
    {
        HI_MMZ_Unmap(pstVideoFrameInfo->PhyBuf[0]);
    }

    if (0 != pstVideoFrameInfo->PhyBuf[0])
    {
        HI_MMZ_Delete(pstVideoFrameInfo->PhyBuf[0]);
    }

	return HI_FAILURE;
}


/****************************************************************************
* func          : main
* description	: CNcomment: 应用程序入口 CNend\n
* param[in] 	: NA
* retval		: NA
* others:		: NA
******************************************************************************/
HI_S32 main(int argc, char* argv[])
{
    HI_S32 Ret = HI_SUCCESS;
    SAMPLE_VIDEO_FREMAE_INFO_S stVideoFrameInfo;

    Ret = SAMPLE_JPEG_Decode(&stVideoFrameInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto FINISH_EXIT;
    }

    stVideoFrameInfo.Qlevel = 80;
    stVideoFrameInfo.YuvFmtType = JPGE_INPUT_FMT_YUV420;
    stVideoFrameInfo.YuvSampleType = JPGE_INPUT_SAMPLER_SEMIPLANNAR;

    Ret = HI_SAMPLE_Encode(SAMPLE_ENCODE_JPEG_FILE,&stVideoFrameInfo);
    if (HI_SUCCESS != Ret)
    {
        SAMPLE_TRACE("\n[%s %d] --------->failure\n",__FUNCTION__,__LINE__);
        goto FINISH_EXIT;
    }

FINISH_EXIT:

    if (0 != stVideoFrameInfo.PhyBuf[0])
    {
        HI_MMZ_Delete(stVideoFrameInfo.PhyBuf[0]);
    }

    return 0;
}
#endif
