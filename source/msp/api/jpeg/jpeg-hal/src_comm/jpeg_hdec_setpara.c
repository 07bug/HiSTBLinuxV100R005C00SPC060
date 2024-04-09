/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_setpara.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : write decode register
Function List    :


History          :
Date                        Author                    Modification
2018/01/01                  sdk                       Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#ifdef HI_BUILD_IN_BOOT
  #ifndef HI_BUILD_IN_MINI_BOOT
     #include <linux/string.h>
  #else
     #include "string.h"
  #endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#endif

#include "hi_jpeg_config.h"
#include "hi_jpeg_reg.h"

#include "jpeg_hdec_api.h"
/***************************** Macro Definition     ***********************************************/


/***************************** Structure Definition ***********************************************/
typedef enum tagJPEG_MEMTYPE_E
{
    JPEG_STREAM_MEM_MMU_TYPE            = 0X1,    /**< 0bit 码流内存为MMU类型           >**/
    JPEG_YOUTPUT_MEM_MMU_TYPE           = 0X2,    /**< 1bit Y分量输出内存为MMU类型      >**/
    JPEG_UVOUTPUT_MEM_MMU_TYPE          = 0X4,    /**< 2bit UV分量输出内存为MMU类型     >**/
    JPEG_XRGBSAMPLE0_READ_MEM_MMU_TYPE  = 0X8,    /**< RGB输出需要的上采样0buffer读类型 >**/
    JPEG_XRGBSAMPLE1_READ_MEM_MMU_TYPE  = 0X10,   /**< RGB输出需要的上采样1buffer读类型 >**/
    JPEG_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE = 0X20,   /**< RGB输出需要的上采样0buffer写类型 >**/
    JPEG_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE = 0X40,   /**< RGB输出需要的上采样1buffer写类型 >**/
    JPEG_XRGBOUTPUT_MEM_MMU_TYPE        = 0X80,   /**< 7bitRGB输出内存为MMU类型         >**/
    JPEG_LINENUM_MEM_MMU_TYPE           = 0X100,  /**< 8bit行号输出内存为MMU类型        >**/
    JPEG_MEMTYPE_BUTT
}JPEG_MEMTYPE_E;


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_VOID JPEG_HDEC_ImagFmt2HardFmt(const HI_JPEG_FMT_E enJpegFmt,HI_U32 *pu32Fmt)
{
    switch (enJpegFmt)
    {
        case HI_JPEG_FMT_YUV400:
           *pu32Fmt = 0;
           break;
        case HI_JPEG_FMT_YUV420:
           *pu32Fmt = 3;
           break;
        case HI_JPEG_FMT_YUV422_21:
           *pu32Fmt = 4;
            break;
        case HI_JPEG_FMT_YUV422_12:
           *pu32Fmt = 5;
           break;
        case HI_JPEG_FMT_YUV444:
           *pu32Fmt = 6;
           break;
        default:
           *pu32Fmt = 7;
           break;
    }

    return;
}

static inline HI_VOID JPEG_HDEC_SetDqt(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_CpyData2Reg(pJpegHandle->pJpegRegVirAddr, (HI_VOID *)pJpegHandle->stImgInfo.QuantTab, JPGD_REG_QUANT, sizeof(pJpegHandle->stImgInfo.QuantTab));
    return;
}

static inline HI_VOID JPEG_HDEC_SetDhtDc(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_CpyData2Reg(pJpegHandle->pJpegRegVirAddr,pJpegHandle->stImgInfo.HuffDcTab,JPGD_REG_HDCTABLE,48);
    return;
}

static inline HI_VOID JPEG_HDEC_SetDhtAc(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_CpyData2Reg(pJpegHandle->pJpegRegVirAddr, pJpegHandle->stImgInfo.HufAcMinTab,  JPGD_REG_HACMINTABLE,  32);
    JPEG_HDEC_CpyData2Reg(pJpegHandle->pJpegRegVirAddr, pJpegHandle->stImgInfo.HufAcBaseTab, JPGD_REG_HACBASETABLE, 32);

    /**< 0x2c0 = ac_max_sum_syms * 4  >**/
    /**< CNcomment: 值0x2c0 = ac_max_sum_syms * 4计算得来  >**/
    JPEG_HDEC_CpyData2Reg(pJpegHandle->pJpegRegVirAddr, pJpegHandle->stImgInfo.HufAcSymbolTab,JPGD_REG_HACSYMTABLE,  0x2c0);

    return;
}

static inline HI_VOID JPEG_HDEC_SetDht(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
   JPEG_HDEC_SetDhtDc(pJpegHandle);
   JPEG_HDEC_SetDhtAc(pJpegHandle);
   return;
}

static inline HI_S32 JPEG_HDEC_SetSof(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 DefaultScale    = 0;
    HI_U32 u32Stride       = 0;
    HI_U32 u32HardFmt      = 0;

    JPEG_HDEC_ImagFmt2HardFmt(pJpegHandle->stImgInfo.jpeg_color_space,&u32HardFmt);
    if (u32HardFmt >= 7)
    {
        return HI_FAILURE;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_PICTYPE, u32HardFmt);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
       JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_SCALE, (0x30 | 0x8));
    }
    else
#endif
    {
        DefaultScale = 0x34;
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_SCALE, ((DefaultScale & 0xfffffffc) | pJpegHandle->ScalRation | 0x8));
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_PICSIZE, pJpegHandle->stJpegSofInfo.u32InWandH);

    u32Stride = (pJpegHandle->stJpegSofInfo.u32CbCrStride << 16 ) | pJpegHandle->stJpegSofInfo.u32YStride;
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_STRIDE,u32Stride);

    return HI_SUCCESS;
}

static inline HI_VOID JPEG_HDEC_SetSampleFactor(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U8 u8YFac = 0,u8UFac = 0,u8VFac = 0;

    u8YFac = (HI_U8)(((pJpegHandle->stImgInfo.u8Fac[0][0] << 4) | pJpegHandle->stImgInfo.u8Fac[0][1]) & 0xff);
    u8UFac = (HI_U8)(((pJpegHandle->stImgInfo.u8Fac[1][0] << 4) | pJpegHandle->stImgInfo.u8Fac[1][1]) & 0xff);
    u8VFac = (HI_U8)(((pJpegHandle->stImgInfo.u8Fac[2][0] << 4) | pJpegHandle->stImgInfo.u8Fac[2][1]) & 0xff);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_SAMPLINGFACTOR,((u8YFac << 16) |(u8UFac << 8) | u8VFac));

    return;
}

static inline HI_VOID JPEG_HDEC_SetDri(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_DRI, pJpegHandle->stImgInfo.restart_interval);
    return;
}

static inline HI_VOID JPEG_HDEC_SetMemtype(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    /**=========================================================================
        ** [0] :  1 MMZ   0 MMU   读码流内存类型
        ** [1] :  1 MMZ   0 MMU   Y分量输出内存类型
        ** [2] :  1 MMZ   0 MMU   UV分量输出内存类型
     **======================================================================**/
    HI_U32 u32Mask =   JPEG_STREAM_MEM_MMU_TYPE            \
                     | JPEG_YOUTPUT_MEM_MMU_TYPE           \
                     | JPEG_UVOUTPUT_MEM_MMU_TYPE          \
                     | JPEG_XRGBSAMPLE0_READ_MEM_MMU_TYPE  \
                     | JPEG_XRGBSAMPLE1_READ_MEM_MMU_TYPE  \
                     | JPEG_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE \
                     | JPEG_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE \
                     | JPEG_XRGBOUTPUT_MEM_MMU_TYPE        \
                     | JPEG_LINENUM_MEM_MMU_TYPE;

#ifdef CONFIG_GFX_MMU_SUPPORT
    u32Mask &= ~JPEG_STREAM_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_YOUTPUT_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_UVOUTPUT_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_XRGBSAMPLE0_READ_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_XRGBSAMPLE1_READ_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_XRGBSAMPLE0_WRITE_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_XRGBSAMPLE1_WRITE_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_XRGBOUTPUT_MEM_MMU_TYPE;
    u32Mask &= ~JPEG_LINENUM_MEM_MMU_TYPE;
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MMU_BYPASS,u32Mask);
#else
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MMU_BYPASS,u32Mask);
#endif
    return;
}

static inline HI_VOID JPEG_HDEC_SetDecOutBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_YSTADDR,pJpegHandle->stOutSurface.BufPhy[0]);
        return;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_YSTADDR,pJpegHandle->stDecSurface.BufPhy[0]);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_UVSTADDR,pJpegHandle->stDecSurface.BufPhy[1]);

    return;
}


#ifdef CONFIG_JPEG_HARDDEC2ARGB
static inline HI_VOID JPEG_HDEC_SetXRGBFmt(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 OutType = 0x0;
    HI_U32 OutPut  = 0x0;

    #ifndef CONFIG_GFX_ONLY_HARD_DECOMPRESS
    /**只实现硬件解码，只解YUV输出 **/
    OutPut = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_OUTTYPE);
    #endif

    if (HI_JPEG_FMT_ARGB_8888 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x000;
    }
    else if (HI_JPEG_FMT_ABGR_8888 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x100;
    }
    else if (HI_JPEG_FMT_ABGR_1555 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x300;
    }
    else if (HI_JPEG_FMT_ARGB_1555 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x200;
    }
    else if (HI_JPEG_FMT_BGR_565 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x500;
    }
    else if (HI_JPEG_FMT_RGB_565 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x400;
    }
    else if (HI_JPEG_FMT_BGR_888 == pJpegHandle->stImgInfo.output_color_space)
    {
        OutType  =  0x700;
    }
    else
    {
        OutType  =  0x600;
    }

    OutPut = OutPut | OutType;

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_OUTTYPE,OutPut);

    return;
}


static inline HI_VOID JPEG_HDEC_SetDecARGBPara(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 CropX         = 0;
    HI_U32 CropY         = 0;
    HI_U32 CropStargPos  = 0;
    HI_U32 CropEndX      = 0;
    HI_U32 CropEndY      = 0;
    HI_U32 CropEndPos    = 0;

    CropX    = pJpegHandle->stOutSurface.stCropRect.x;
    CropY    = pJpegHandle->stOutSurface.stCropRect.y;
    CropEndX = (CropX + pJpegHandle->stOutSurface.stCropRect.w - 1);
    CropEndY = (CropY + pJpegHandle->stOutSurface.stCropRect.h - 1);

    CropStargPos = (CropX | (CropY << 16));
    CropEndPos   = (CropEndX | (CropEndY << 16));

    if (HI_TRUE == pJpegHandle->bOutUsrBuf)
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ARGBOUTSTRIDE,pJpegHandle->stOutSurface.Stride[0]);
    }
    else
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ARGBOUTSTRIDE,pJpegHandle->stJpegSofInfo.DecOutStride);
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_OUTSTARTPOS,CropStargPos);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_OUTENDPOS,CropEndPos);

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ALPHA,0XFF);

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MINADDR,  pJpegHandle->DecXRGBLinePhyBuf);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_MINADDR1, pJpegHandle->DecXRGBLinePhyBuf  + pJpegHandle->stJpegSofInfo.u32MINSize);

    JPEG_HDEC_SetXRGBFmt(pJpegHandle);

    return;
}

static inline HI_VOID JPEG_HDEC_SetCropAndARGBInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_SetDecARGBPara(pJpegHandle);
    return;
}
#endif


#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
static inline HI_VOID JPEG_HDEC_SetYUV420SPInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_OUTTYPE,0x4);
    return;
}
#endif


#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
static inline HI_VOID JPEG_HDEC_SetLuPixSumInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (HI_FALSE == pJpegHandle->bOutYCbCrSP)
    {
       return;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM1,0x80000000);

    return;
}
#endif

#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
static inline HI_VOID JPEG_HDEC_SetLowDelayInf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 McuLineNum = 8;

    if (HI_TRUE != pJpegHandle->bLowDelayEn)
    {
        return;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_LINE_ADDR, pJpegHandle->u32PhyLineBuf);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_LINE_NUM, McuLineNum);

    return;
}
#endif

static inline HI_VOID JPEG_HDEC_SetInputStreamBuffer(JPEG_HDEC_HANDLE_S_PTR  pJpegHandle)
{
    HI_U32 StartInputStreamPhyBuf = 0, EndInputStreamPhyBuf = 0;

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
        StartInputStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf;
        EndInputStreamPhyBuf   = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize;
        StartInputStreamPhyBuf = (StartInputStreamPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1) & (~(CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1));
        StartInputStreamPhyBuf = StartInputStreamPhyBuf - CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN;
        EndInputStreamPhyBuf   = (EndInputStreamPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1) & (~(CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN - 1));
    }
    else
    {
        StartInputStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf;
        EndInputStreamPhyBuf   = StartInputStreamPhyBuf + CONFIG_JPED_INPUT_DATA_BUFFER_NUM * (CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE + CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE);
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADDR, StartInputStreamPhyBuf);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADDR,EndInputStreamPhyBuf);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ERR_STREAM_EN,0x0);

    return;
}

static HI_S32 JPEG_HDEC_SetPara(HI_ULONG HdecHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FAILURE;
    }

    if (HI_TRUE == pJpegHandle->bFinishSetPara)
    {
       return HI_SUCCESS;
    }

#ifndef CONFIG_GFX_ONLY_HARD_DECOMPRESS
    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.HardDecTimes, NULL);
#endif

    pJpegHandle->bFinishSetPara = HI_TRUE;

    /**< set dqt table register >**/
    /**< CNcomment: 配置量化表，21us CNend>**/
    JPEG_HDEC_SetDqt(pJpegHandle);

    /**<set dht table register>**/
    /**<CNcomment: 配置哈夫曼表，100us ~ 120us CNend>**/
    JPEG_HDEC_SetDht(pJpegHandle);

    /**<set sof message>**/
    /**<CNcomment: 设置SOF信息 CNend  >**/
    Ret = JPEG_HDEC_SetSof(pJpegHandle);
    if  (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    /**< set sample factor message >**/
    /**< CNcomment: 设置采样因子信息 CNend >**/
    JPEG_HDEC_SetSampleFactor(pJpegHandle);

    /**< set dri value>**/
    /**<  CNcomment: 设置dri得值 CNend>**/
    JPEG_HDEC_SetDri(pJpegHandle);

    /**< set mem type>**/
    /**<  CNcomment: 设置内存类型 CNend >**/
    JPEG_HDEC_SetMemtype(pJpegHandle);

    /**< et middle buffer register>**/
    /**< CNcomment: 设置JPEG硬件解码输出寄存器 CNend>**/
    JPEG_HDEC_SetDecOutBuf(pJpegHandle);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
    /**< set about dec out argb register>**/
       /**< CNcomment: 设置解码输出为ARGB相关信息 CNend>**/
    if (HI_TRUE == pJpegHandle->bDecOutColorSpaecXRGB)
    {
       JPEG_HDEC_SetCropAndARGBInfo(pJpegHandle);
    }
#endif

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    /**< set all decode output yuv420sp informationv>**/
    /**< CNcomment: 设置解码统一输出yuvsp420sp寄存器 CNend>**/
    if (HI_TRUE == pJpegHandle->bOutYUV420SP)
    {
       JPEG_HDEC_SetYUV420SPInfo(pJpegHandle);
    }
#endif

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    /**<  set count lu pixle sum value>**/
    /**< CNcomment: 设置统计亮度值寄存器 CNend>**/
    JPEG_HDEC_SetLuPixSumInfo(pJpegHandle);
#endif

#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    JPEG_HDEC_SetLowDelayInf(pJpegHandle);
#endif

    JPEG_HDEC_SetInputStreamBuffer(pJpegHandle);

    return HI_SUCCESS;
}
