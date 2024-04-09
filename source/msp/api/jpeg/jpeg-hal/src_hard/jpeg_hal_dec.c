/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hal_dec.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : ´¿Ó²¼þ½âÂë
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#ifdef HI_BUILD_IN_BOOT
  #include "hi_reg_common.h"
  #ifndef HI_BUILD_IN_MINI_BOOT
     #include <linux/string.h>
     #include "common.h"
  #else
     #include "string.h"
     #include "delay.h"
  #endif
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#include "hi_jpeg_config.h"
#include "hi_jpeg_api.h"
#include "hi_jpeg_reg.h"
#include "jpeg_hdec_api.h"

#include "jpeg_hdec_rwreg.c"
#include "jpeg_hdec_setpara.c"
#include "jpeg_hal_parse.c"
#include "jpeg_sdec_table.c"

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
#include "jpeg_hdec_debug.c"
#endif
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
#ifndef CONFIG_GFX_JPEG_MINI_SUPPROT
    static inline HI_S32 JPEG_HDEC_Decompress(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
    #ifdef HI_BUILD_IN_BOOT
        static inline HI_VOID JPEG_OpenDev(HI_VOID);
        static inline HI_VOID JPEG_CloseDev(HI_VOID);
        static inline HI_VOID JPEG_DRV_QuerytIntStatus(volatile HI_CHAR *pRegBase, JPEG_INTTYPE_E *pIntType);
    #else
        static inline HI_VOID JPEG_HDEC_LowDelayInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
    #endif

    #if !defined(CONFIG_JPEG_ADD_GOOGLEFUNCTION) && !defined(HI_BUILD_IN_BOOT)
        //extern HI_VOID JPEG_DEC_PrintProcMsg(HI_ULONG DecHandle);
    #endif
#endif

/******************************* API realization **************************************************/
#if !defined(HI_BUILD_IN_BOOT) && !defined(CONFIG_GFX_JPEG_MINI_SUPPROT)
static inline HI_VOID JPEG_HDEC_GetTimeStamp(HI_U32 *pu32TimeMs)
{
    HI_S32 Ret = HI_SUCCESS;
    struct timespec timenow = {0, 0};
    clockid_t id = CLOCK_MONOTONIC_RAW;

    if (HI_NULL == pu32TimeMs)
    {
        return;
    }

    Ret = clock_gettime(id, &timenow);
    if (Ret < 0)
    {
        return;
    }

    *pu32TimeMs = (HI_U32)(timenow.tv_sec * 1000 + timenow.tv_nsec/1000000);

    return;
}
#endif

HI_VOID HI_JPEG_DestroyDecompress(HI_ULONG DecHandle)
{
#ifndef HI_BUILD_IN_BOOT
    HI_U32 PreTime = 0;
#endif
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

#ifndef HI_BUILD_IN_BOOT
    if (NULL != pJpegHandle->pJpegRegVirAddr)
    {
       (HI_VOID)munmap((void*)pJpegHandle->pJpegRegVirAddr, JPGD_REG_LENGTH);
       pJpegHandle->pJpegRegVirAddr = NULL;
    }

    if (pJpegHandle->JpegDev >= 0)
    {
       close(pJpegHandle->JpegDev);
       pJpegHandle->JpegDev = -1;
    }

    PreTime = pJpegHandle->stProcInfo.DecCostTimes;
    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.DecCostTimes);
    pJpegHandle->stProcInfo.DecCostTimes = pJpegHandle->stProcInfo.DecCostTimes - PreTime;

    //JPEG_DEC_PrintProcMsg(DecHandle);
#else
    JPEG_CloseDev();
#endif

    free(pJpegHandle);

    return;
}

HI_ULONG HI_JPEG_CreateDecompress(HI_U32 StreamPhyAddr,HI_U32 TotalStremBufSize,HI_CHAR* pFirstStreamVirBuf,HI_U32 FirstStreamBufSize,HI_CHAR* pSecondStreamVirBuf,HI_U32 SecondStreamBufSize)
{
#ifdef CONFIG_GFX_JPEG_MINI_SUPPROT
    HI_UNUSED(StreamPhyAddr);
    HI_UNUSED(TotalStremBufSize);
    HI_UNUSED(pFirstStreamVirBuf);
    HI_UNUSED(FirstStreamBufSize);
    HI_UNUSED(pSecondStreamVirBuf);
    HI_UNUSED(SecondStreamBufSize);
    return 0;
#else

#ifndef HI_BUILD_IN_BOOT
    HI_S32 Ret = HI_SUCCESS;
#endif
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    if ((0 == StreamPhyAddr) || (0 == TotalStremBufSize) || (NULL == pFirstStreamVirBuf) || (0 == FirstStreamBufSize))
    {
        return 0;
    }

#ifndef HI_BUILD_IN_BOOT
    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)calloc(1, sizeof(JPEG_HDEC_HANDLE_S));
    if (NULL == pJpegHandle)
    {
        return 0;
    }

    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.DecCostTimes);

    pJpegHandle->JpegDev = open("/dev/jpeg", O_RDWR | O_SYNC, S_IRUSR);
    if (pJpegHandle->JpegDev < 0)
    {
        HI_JPEG_DestroyDecompress((HI_ULONG)pJpegHandle);
        return 0;
    }

    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETDEVICE);
    if (HI_SUCCESS != Ret)
    {
        HI_JPEG_DestroyDecompress((HI_ULONG)pJpegHandle);
        return 0;
    }

    pJpegHandle->pJpegRegVirAddr = (volatile char*)mmap(NULL,JPGD_REG_LENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,pJpegHandle->JpegDev,(off_t)0);
    if (MAP_FAILED == pJpegHandle->pJpegRegVirAddr)
    {
        HI_JPEG_DestroyDecompress((HI_ULONG)pJpegHandle);
        return 0;
    }
#else
    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)malloc(sizeof(JPEG_HDEC_HANDLE_S));
    if (NULL == pJpegHandle)
    {
        return 0;
    }
    HI_GFX_Memset(pJpegHandle, 0x0, sizeof(JPEG_HDEC_HANDLE_S));

    JPEG_OpenDev();
    pJpegHandle->pJpegRegVirAddr = (HI_CHAR*)JPGD_REG_BASEADDR;
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_INTMASK, JPEG_REG_INTMASK_VALUE);
#endif

    pJpegHandle->CscDev       = -1;
    pJpegHandle->MemDev       = -1;
    pJpegHandle->SkipLines    = 0;
    pJpegHandle->u8ImageCount = 1;
    pJpegHandle->stImgInfo.jpeg_color_space   = HI_JPEG_FMT_BUTT;
    pJpegHandle->stImgInfo.output_color_space = HI_JPEG_FMT_BUTT;

    pJpegHandle->stProcInfo.UseStandardLibDec = HI_FALSE;

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf   = StreamPhyAddr;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize = TotalStremBufSize;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf = HI_TRUE;

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf = pFirstStreamVirBuf;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize     = FirstStreamBufSize;

    if (0 == SecondStreamBufSize)
    {
       pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_FALSE;
       return (HI_ULONG)pJpegHandle;
    }

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserInputBufReturn = HI_TRUE;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserTotalInputBufSize = TotalStremBufSize;
    if (NULL == pSecondStreamVirBuf)
    {
       HI_JPEG_DestroyDecompress((HI_ULONG)pJpegHandle);
       return 0;
    }

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserSecondInputDataVirBuf = pSecondStreamVirBuf;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserSecondInputBufSize = SecondStreamBufSize;

    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UseSecondInputBuf = HI_FALSE;
    pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserDataHasBeenReadSize = 0;

    return (HI_ULONG)pJpegHandle;
#endif
}

HI_S32 HI_JPEG_StartDecompress(HI_ULONG DecHandle)
{
#ifdef CONFIG_GFX_JPEG_MINI_SUPPROT
    HI_UNUSED(DecHandle);
    return HI_FAILURE;
#else
    HI_S32 Ret = HI_SUCCESS;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    Ret = JPEG_HDEC_SetPara(DecHandle);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    return JPEG_HDEC_Decompress(pJpegHandle);
#endif
}

#ifndef CONFIG_GFX_JPEG_MINI_SUPPROT
static inline HI_S32 JPEG_HDEC_Decompress(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef HI_BUILD_IN_BOOT
    HI_S32 Ret = HI_SUCCESS;
#else
    HI_ULONG ticks_start = 0, ticks_now = 0;
    HI_U32 diff_ms = 0;
    HI_ULONG time_sec = 0;
    HI_U16 time_msec = 0,time_usec = 0;
    HI_U32 LoopCnt = 0;
#endif

    HI_U32 StartSaveStreamPhyBuf = 0;
    HI_U32 EndSaveStreamPhyBuf = 0;
    HI_U32 LowDelayValue = 0;
    JPEG_GETINTTYPE_S GetIntType;

    if (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos >= pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize)
    {
       JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
       return HI_FAILURE;
    }

    StartSaveStreamPhyBuf =   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf
                            + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos;
    EndSaveStreamPhyBuf   =   pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf
                            + pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize;

    if (0 == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputDataPhyBuf)
    {
       JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
       return HI_FAILURE;
    }

    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, StartSaveStreamPhyBuf & 0xffffffff);
    JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,EndSaveStreamPhyBuf & 0xffffffff);

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

    GetIntType.IntType = JPG_INTTYPE_NONE;
    GetIntType.TimeOut = JPEG_INTTYPE_DELAY_TIME;

#ifndef HI_BUILD_IN_BOOT
    Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETINTSTATUS, &GetIntType);
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
        JPEG_HDEC_LowDelayInfo(pJpegHandle);
        return HI_FAILURE;
    }

    if ((JPG_INTTYPE_CONTINUE == GetIntType.IntType) || (JPG_INTTYPE_ERROR == GetIntType.IntType))
    {
        JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
        JPEG_HDEC_LowDelayInfo(pJpegHandle);
        return HI_FAILURE;
    }
#else

    ticks_start = do_gettime(&time_sec,&time_msec,&time_usec);

    do
    {
        LoopCnt++;
        ticks_now = do_gettime(&time_sec,&time_msec,&time_usec);
        diff_ms = (HI_U32)((ticks_now - ticks_start) / 1000);

        GetIntType.IntType = JPG_INTTYPE_NONE;
        JPEG_DRV_QuerytIntStatus(pJpegHandle->pJpegRegVirAddr,&(GetIntType.IntType));
        if (JPG_INTTYPE_FINISH == GetIntType.IntType)
        {
            return HI_SUCCESS;
        }
        else if (JPG_INTTYPE_CONTINUE == GetIntType.IntType || JPG_INTTYPE_ERROR == GetIntType.IntType)
        {
            JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
            return HI_FAILURE;
        }
        else
        {
            continue;
        }
     }while (diff_ms < 3000);

     if (diff_ms >= 3000)
     {
        JPEG_TRACE("[module-gfx] : %s[%d] : logo decode timeout %d LoopCnt %d\n",   __FUNCTION__,__LINE__,diff_ms,LoopCnt);
     }
#endif

    return HI_SUCCESS;
}
#endif

#if !defined(HI_BUILD_IN_BOOT) && !defined(CONFIG_GFX_JPEG_MINI_SUPPROT)
static inline HI_VOID JPEG_HDEC_LowDelayInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
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
#endif

HI_S32 HI_JPEG_ParseHeader(HI_ULONG DecHandle)
{
#ifdef CONFIG_GFX_JPEG_MINI_SUPPROT
    HI_UNUSED(DecHandle);
    return HI_FAILURE;
#else
    HI_S32 Ret = HI_SUCCESS;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    Ret = JPEG_HAL_Parse(DecHandle);
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("%s %d failure\n",__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }

    JPEG_SDEC_GetTable(&(pJpegHandle->stImgInfo));

    return HI_SUCCESS;
#endif
}

#ifdef HI_BUILD_IN_BOOT
static inline HI_VOID JPEG_OpenDev(HI_VOID)
{
    volatile U_PERI_CRG31 unTempValue;
  #ifdef CONFIG_GFX_MMU_CLOCK
    volatile U_PERI_CRG205 unTempSmmuValue;
  #endif
    if (NULL == g_pstRegCrg)
    {
       return;
    }

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_cken     = 0x1;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    udelay(1000);
    unTempValue.bits.jpgd_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

  #ifdef CONFIG_GFX_MMU_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_cken = 0x1;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    udelay(1000);
    unTempSmmuValue.bits.jpgd_smmu_srst_req = 0x0;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
  #endif

    return;
}

static inline HI_VOID JPEG_CloseDev(HI_VOID)
{
    volatile U_PERI_CRG31 unTempValue;
  #ifdef CONFIG_GFX_MMU_CLOCK
    volatile U_PERI_CRG205 unTempSmmuValue;
  #endif
    if (NULL == g_pstRegCrg)
    {
      return;
    }

    unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
    unTempValue.bits.jpgd_srst_req  = 0x1;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
    udelay(1000);
    unTempValue.bits.jpgd_cken      = 0x0;
    g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

  #ifdef CONFIG_GFX_MMU_CLOCK
    unTempSmmuValue.u32 = g_pstRegCrg->PERI_CRG205.u32;
    unTempSmmuValue.bits.jpgd_smmu_srst_req = 0x1;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
    udelay(1000);
    unTempSmmuValue.bits.jpgd_smmu_cken = 0x0;
    g_pstRegCrg->PERI_CRG205.u32 = unTempSmmuValue.u32;
  #endif

    return;
}

static inline HI_VOID JPEG_DRV_QuerytIntStatus(volatile HI_CHAR *pRegBase, JPEG_INTTYPE_E *pIntType)
{
    HI_U32 IntType = 0;

    IntType = JPEG_HDEC_ReadReg(pRegBase, JPGD_REG_INT);
    JPEG_HDEC_WriteReg(pRegBase, JPGD_REG_INT, IntType);

    if (IntType & 0x1)
    {
        *pIntType = JPG_INTTYPE_FINISH;
    }
    else if (IntType & 0x2)
    {
        *pIntType = JPG_INTTYPE_ERROR;
    }
    else if (IntType & 0x4)
    {
        *pIntType = JPG_INTTYPE_CONTINUE;
    }
    else
    {
        *pIntType = JPG_INTTYPE_NONE;
    }

    return;
}
#endif
