/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : jpeg_hdec_startdec.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     : start hard decode
Function List   :


History         :
Date                    Author                    Modification
2018/01/01               sdk                      Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hi_jpeg_config.h"
#include "hi_drv_jpeg.h"
#include "hi_jpeg_reg.h"

#include "jpeg_hdec_api.h"

/***************************** Macro Definition     ************************************************/
#define JPEG_DEC_RESUME_VALUE           0x01
#define JPEG_DEC_EOF_VALUE              0x02
/***************************** Structure Definition ************************************************/


/********************** Global Variable declaration ************************************************/
static inline HI_VOID JPEG_HDEC_OnDecInputPhyMemData(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_VOID JPEG_HDEC_SetSaveStreamBuffer(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_S32 JPEG_HDEC_GetDecStatus(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, JPEG_INTTYPE_E *pIntType, HI_U32 u32TimeOut);
static inline HI_VOID JPEG_HDEC_FillPhyMemInputBuffer(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_VOID JPEG_HDEC_SetLowDelayBufferDate(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_S32  JPEG_HDEC_OnDecInputUnPhyMemData(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_BOOL HasBeenStartDec, JPEG_INTTYPE_E *pIntStatus);

/********************** API forward declarations    ************************************************/
extern HI_VOID JPEG_DEC_IfSupport(HI_ULONG HdecHandle);

/**********************       API realization       ************************************************/
/*****************************************************************************
 * func         : JPEG_DEC_GetStopDec
 * description  : stop decompress
                  CNcomment: 终止解码 CNend\n
 * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
 * param[in]    : StopDec      CNcomment:   是否终止解码 CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetStopDec(HI_ULONG HdecHandle, HI_BOOL* StopDec)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != StopDec)
    {
       *StopDec = pJpegHandle->EnStopDecode;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetPara
 * description  : set hard register para in jpeg_start_decompress
                  CNcomment: 在开始解码中设置寄存器 CNend\n
 * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetPara(HI_ULONG HdecHandle)
{
    HI_S32 Ret = HI_FAILURE;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    JPEG_DEC_IfSupport(HdecHandle);
    if (HI_FALSE == pJpegHandle->SupportHardDec)
    {
       return;
    }

    Ret = JPEG_HDEC_SetPara(HdecHandle);
    if (HI_SUCCESS != Ret)
    {
        return;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_CscConvert
 * description  : csc convert
                  CNcomment: CSC 色彩空间转换 CNend\n
 * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_S32 JPEG_DEC_CscConvert(HI_ULONG HdecHandle, HI_CHAR* ScanlineBuf, HI_U32 MaxLines, HI_U32 *pCurScanlines)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 RowLineNums = 0;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if ((NULL == pJpegHandle) || (NULL == pCurScanlines))
    {
        return MaxLines;
    }

    if (HI_FALSE == pJpegHandle->bHdecSuccess)
    {
        return MaxLines;
    }

#ifndef CONFIG_JPEG_CSC_DISABLE
    Ret = JPEG_HDEC_HardCSC(HdecHandle);
    if (HI_SUCCESS != Ret)
    {
        JPEG_HDEC_FreeDecodeMemory(HdecHandle);
        pJpegHandle->bHdecSuccess = HI_FALSE;
        return 0;
    }
#endif

    if (HI_TRUE == pJpegHandle->bDiscardScanlines)
    {
       /**<-- if skip scanlines, should not copy data to user buffer >**/
       /**<--如果是丢行处理则不需要拷贝码流>**/
       return MaxLines;
    }

    RowLineNums = JPEG_HDEC_OutUserBuf(HdecHandle, ScanlineBuf, MaxLines, pCurScanlines);

    return RowLineNums;
}


/*****************************************************************************
 * func         : JPEG_DEC_StartDec
 * description  : start decompress
                  CNcomment: 启动解码 CNend\n
 * param[in]    : HdecHandle        CNcomment:   解码器句柄   CNend\n
 * param[in]    : HasBeenStartDec   CNcomment:   是否已经启动过解码   CNend\n
 * param[in]    : SupportSeekToSoft CNcomment:   是否支持码流回退解码 CNend\n
 * retval       : if finish hard dec
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_BOOL JPEG_DEC_StartDec(HI_ULONG HdecHandle, HI_BOOL HasBeenStartDec, HI_BOOL SupportSeekToSoft)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 PreTime = 0;
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    HI_U32 u32RegistLuaPixSum0 = 0;
    HI_U64 u64RegistLuaPixSum1 = 0;
#endif
    //JPEG_IMG_INFO_S stImgInfo;
    JPEG_INTTYPE_E IntStatus = JPG_INTTYPE_NONE;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_TRUE;
    }

    HI_UNUSED(SupportSeekToSoft);

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
        JPEG_HDEC_OnDecInputPhyMemData(pJpegHandle);
        goto DEC_FINISH;
    }

    /** continue decompress **/
    JPEG_HDEC_FlushBuf(HdecHandle, pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf);

    Ret = JPEG_HDEC_OnDecInputUnPhyMemData(pJpegHandle,HasBeenStartDec,&IntStatus);
#ifdef CONFIG_JPEG_SEEK_SUPPORT
    if (HI_SUCCESS != Ret)
    {
       goto DEC_FAILURE;
    }
#else
    HI_UNUSED(Ret);
#endif
    if ((JPG_INTTYPE_CONTINUE == IntStatus) || (JPG_INTTYPE_NONE == IntStatus))
    {
        /** has not finish decompress **/
       return HI_FALSE;
    }

#if 0
    JPEG_DEC_GetImgInfo(HdecHandle, &stImgInfo);
    if (stImgInfo.bytes_in_buffer > 4096)
    {
       if (JPG_INTTYPE_ERROR == IntStatus)
       {
          goto DEC_FAILURE;
       }
    }
#endif

#ifdef CONFIG_JPEG_SEEK_SUPPORT
    if (JPG_INTTYPE_FINISH == IntStatus)
#else
    if ( (JPG_INTTYPE_ERROR == IntStatus) || (JPG_INTTYPE_FINISH == IntStatus))
#endif
    {
        goto DEC_FINISH;
    }

    goto DEC_FAILURE;

DEC_FINISH:
    PreTime = pJpegHandle->stProcInfo.HardDecTimes;
    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.HardDecTimes,NULL);
    pJpegHandle->stProcInfo.HardDecTimes = pJpegHandle->stProcInfo.HardDecTimes - PreTime;

#if defined(CONFIG_JPEG_OUTPUT_LUPIXSUM) && !defined(CONFIG_GFX_ONLY_HARD_DECOMPRESS)
    /**只实现硬件解码，只解YUV输出, 不需要额外的功能 **/
    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
       u32RegistLuaPixSum0 = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM0);
       u64RegistLuaPixSum1 = (HI_U64)(JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM1) & 0xf);
       pJpegHandle->u64LuPixValue = (HI_U64)((u64RegistLuaPixSum1 << 32) | u32RegistLuaPixSum0);
    }
#endif

    pJpegHandle->bHdecSuccess = HI_TRUE;

    return HI_TRUE;

DEC_FAILURE:
    pJpegHandle->bHdecSuccess = HI_FALSE;
    return HI_TRUE;
}

static inline HI_VOID JPEG_HDEC_OnDecInputPhyMemData(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 LowDelayValue = 0;
    HI_S32 Ret = HI_SUCCESS;
    JPEG_INTTYPE_E IntStatus = JPG_INTTYPE_NONE;

    JPEG_HDEC_FillPhyMemInputBuffer(pJpegHandle);

    /**<-- set save stream buffer register >**/
    /**<-- 设置存储码流buffer 寄存器>**/
    JPEG_HDEC_SetSaveStreamBuffer(pJpegHandle);

#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    if (HI_TRUE == pJpegHandle->bLowDelayEn)
    {
       LowDelayValue = 0x8;
    }
#endif

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME, 0x2);
#ifdef CONFIG_JPEG_4KDDR_DISABLE
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, (0x5 | LowDelayValue));
#else
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, (0x1 | LowDelayValue));
#endif

    Ret = JPEG_HDEC_GetDecStatus(pJpegHandle, &IntStatus, JPEG_INTTYPE_DELAY_TIME);
    if (HI_SUCCESS != Ret)
    {
        JPEG_HDEC_SetLowDelayBufferDate(pJpegHandle);
        pJpegHandle->bHdecSuccess = HI_FALSE;
        return;
    }

#if 0
    if ((JPG_INTTYPE_CONTINUE == IntStatus) || (JPG_INTTYPE_ERROR == IntStatus))
#else
    if (JPG_INTTYPE_CONTINUE == IntStatus)
#endif
    {
        JPEG_HDEC_SetLowDelayBufferDate(pJpegHandle);
        pJpegHandle->bHdecSuccess = HI_FALSE;
        return;
    }

    pJpegHandle->bHdecSuccess = HI_TRUE;

    return;
}

static inline HI_VOID JPEG_HDEC_FillPhyMemInputBuffer(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 FirstStartPhyBuf = 0;
    /**<-- use physical buffer, and memory buffer is not return >**/
    /**<--连续物理内存方式，没有使用码流回绕方式>**/
    if (HI_FALSE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamBufSize = pJpegHandle->stImgInfo.bytes_in_buffer;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = pJpegHandle->stImgInfo.next_input_byte;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize - pJpegHandle->stImgInfo.bytes_in_buffer);
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize;
       return;
    }

    /**<-- save data buffer that will hard decode from second buffer >**/
    /**<--硬件解码使用的存储码流buffer 使用第二块buffer >**/
    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf)
    {
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamBufSize = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) + pJpegHandle->stImgInfo.bytes_in_buffer;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = pJpegHandle->stImgInfo.next_input_byte;
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize - pJpegHandle->stImgInfo.bytes_in_buffer);
       pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize;
       return;
    }

    /**<-- save data buffer that will hard decode from first buffer >**/
    /**<--硬件解码使用的存储码流buffer 起始地址使用第一块buffer >**/
    FirstStartPhyBuf = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf);
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamBufSize = (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize - pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize) + pJpegHandle->stImgInfo.bytes_in_buffer;
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].pSaveStreamVirBuf = pJpegHandle->stImgInfo.next_input_byte;
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf  = FirstStartPhyBuf + (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize - pJpegHandle->stImgInfo.bytes_in_buffer);
    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf  = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize;

    return;
}

static inline HI_VOID JPEG_HDEC_SetSaveStreamBuffer(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 DecDataBufIndex = 0;
    HI_U32 StartSaveStreamPhyBuf = 0;
    HI_U32 EndSaveStreamPhyBuf = 0;

    /**##########################################
     **   |<--------stream buffer---------------------->|
     **   |0x20  ~ 0x2c |<-----save stream buffer ->|0x28 ~ 0x24  |
     **   |___________|_______________________|___________|
     **##########################################**/
    if (pJpegHandle->stInputDataBufInfo.DecDataBufIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
       return;
    }

    if (HI_TRUE == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf)
    {
       StartSaveStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[0].SaveStreamPhyBuf;
       EndSaveStreamPhyBuf   = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[1].SaveStreamPhyBuf;
    }
    else
    {
       DecDataBufIndex = pJpegHandle->stInputDataBufInfo.DecDataBufIndex;
       StartSaveStreamPhyBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].SaveStreamPhyBuf;
       EndSaveStreamPhyBuf = StartSaveStreamPhyBuf + pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].SaveStreamBufSize;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, StartSaveStreamPhyBuf & 0xffffffff);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,EndSaveStreamPhyBuf & 0xffffffff);

    return;
}

static inline HI_S32 JPEG_HDEC_OnDecInputUnPhyMemData(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, HI_BOOL HasBeenStartDec, JPEG_INTTYPE_E *pIntStatus)
{
    HI_U32 PreTime = 0;
    HI_U32 EndTime = 0;
    HI_U32 TotalTimes = 0;
    HI_CHAR* pStremBuf = NULL;
    HI_S32 DataSize = 0;
    HI_U32 DecDataIndex = 0;
    HI_BOOL DecDataEof = HI_FALSE;
    HI_BOOL InputDataErr = HI_FALSE;

    if (HI_TRUE == HasBeenStartDec)
    {
       JPEG_HDEC_GetTimeStamp(&PreTime, NULL);
       (HI_VOID)JPEG_HDEC_GetDecStatus(pJpegHandle, pIntStatus, JPEG_INTTYPE_DELAY_TIME);
       JPEG_HDEC_GetTimeStamp(&EndTime,NULL);
       TotalTimes = EndTime - PreTime;
    }

    if (TotalTimes >= JPEG_INTTYPE_DELAY_TIME)
    {
        JPEG_TRACE("+++++warning: decode timeout %d\n",TotalTimes);
    }

    if ( (JPG_INTTYPE_ERROR == *pIntStatus) || (JPG_INTTYPE_FINISH == *pIntStatus))
    {
        return HI_SUCCESS;
    }

    DecDataIndex = pJpegHandle->stInputDataBufInfo.DecDataBufIndex;
    if (DecDataIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
        return HI_FAILURE;
    }

    pStremBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataIndex].pSaveStreamVirBuf;
    DataSize  = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataIndex].SaveStreamBufSize;
    DecDataEof = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataIndex].DecDataEof;
    if ((HI_TRUE == DecDataEof) && (0xff != pStremBuf[DataSize - 2]) && (0xd9 != pStremBuf[DataSize - 1]))
    {
        InputDataErr = HI_TRUE;
    }

#if 0
    JPEG_TRACE("==========================================\n");
    JPEG_TRACE("input data [0x%x 0x%x 0x%x 0x%x 0x%x]\n",pStremBuf[0],pStremBuf[1],pStremBuf[2],pStremBuf[3],pStremBuf[4]);
    JPEG_TRACE("==========================================\n");
#endif

    JPEG_HDEC_SetSaveStreamBuffer(pJpegHandle);

    if (HI_FALSE == HasBeenStartDec)
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(DecDataEof ? JPEG_DEC_EOF_VALUE : 0x0));
      #ifdef CONFIG_JPEG_4KDDR_DISABLE
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
      #else
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
      #endif
    }
    else
    {
        JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(DecDataEof ? (JPEG_DEC_EOF_VALUE | JPEG_DEC_RESUME_VALUE) : JPEG_DEC_RESUME_VALUE));
    }

    if (HI_FALSE == InputDataErr)
    {
        return HI_SUCCESS;
    }

    (HI_VOID)JPEG_HDEC_GetDecStatus(pJpegHandle, pIntStatus, JPEG_INTTYPE_DELAY_TIME);
#ifdef CONFIG_JPEG_SEEK_SUPPORT
    if (JPG_INTTYPE_FINISH == *pIntStatus)
    {
        //JPEG_TRACE("+++++++++++++hard dec success\n");
        return HI_SUCCESS;
    }
#else
    if ( (JPG_INTTYPE_ERROR == *pIntStatus) || (JPG_INTTYPE_FINISH == *pIntStatus))
    {
        //JPEG_TRACE("+++++++++++++hard dec success\n");
        return HI_SUCCESS;
    }
#endif

    //JPEG_TRACE("+++++++++++++*pIntStatus = %d JPG_INTTYPE_ERROR = %d\n",*pIntStatus,JPG_INTTYPE_ERROR);
    JPEG_TRACE("+++++++input stream err with eof data [0x%x 0x%x],seek to soft dec\n",pStremBuf[DataSize - 2],pStremBuf[DataSize - 1]);

    return HI_FAILURE;
}

static inline HI_S32 JPEG_HDEC_GetDecStatus(JPEG_HDEC_HANDLE_S_PTR pJpegHandle, JPEG_INTTYPE_E *pIntType, HI_U32 u32TimeOut)
{
    HI_S32 Ret = HI_SUCCESS;
    JPEG_GETINTTYPE_S GetIntType;

    GetIntType.IntType = JPG_INTTYPE_NONE;
    GetIntType.TimeOut = u32TimeOut;

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETINTSTATUS, &GetIntType);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

    *pIntType = GetIntType.IntType;

    return HI_SUCCESS;
}

static inline HI_VOID JPEG_HDEC_SetLowDelayBufferDate(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef CONFIG_JPEG_LOW_DELAY_SUPPORT
     HI_UNUSED(pJpegHandle);
#else
     HI_U32* pu32VirLineBuf = NULL;

     if (HI_TRUE != pJpegHandle->bLowDelayEn)
     {
        return;
     }

     pu32VirLineBuf = (HI_U32*)pJpegHandle->pVirLineBuf;
     if (NULL == pu32VirLineBuf)
     {
        return;
     }

     *pu32VirLineBuf = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
     *(pu32VirLineBuf + 4) = pJpegHandle->stJpegSofInfo.u32CMcuHeight;
#endif

     return;
}
