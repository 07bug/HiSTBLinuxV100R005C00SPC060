/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : jpeg_hdec_rwreg.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     : write data to register and read data from register
                  CNcomment: ¶ÁÐ´¼Ä´æÆ÷ CNend\n
Function List   :


History         :
Date                 Author                Modification
2018/01/01           sdk                    Created file
***************************************************************************************************/

/*********************************add include here*************************************************/
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
#endif

#include "hi_jpeg_reg.h"
/***************************** Macro Definition ***************************************************/

/*************************** Structure Definition *************************************************/

/********************** Global Variable declaration ***********************************************/

/******************************* API forward declarations *****************************************/

/******************************* API realization **************************************************/
static HI_VOID JPEG_HDEC_WriteReg(volatile HI_CHAR *pJpegRegVirAddr, HI_U32 PhyOff, HI_U32 Val)
{
    volatile HI_U32  *pAddr = NULL;

    if ((PhyOff >= JPGD_REG_LENGTH) || (NULL == pJpegRegVirAddr))
    {
       return;
    }

    pAddr  = (volatile HI_U32*)(pJpegRegVirAddr + PhyOff);

    *pAddr = Val;

    return;
}

#if !defined(CONFIG_GFX_ONLY_HARD_DECOMPRESS) || defined(HI_BUILD_IN_BOOT)
HI_S32 JPEG_HDEC_ReadReg(const volatile HI_CHAR *pJpegRegVirAddr, HI_U32 PhyOff)
{
   if (NULL == pJpegRegVirAddr)
   {
      return HI_FAILURE;
   }

   return PhyOff < JPGD_REG_LENGTH ?  *(volatile int *)(pJpegRegVirAddr + PhyOff) : HI_FAILURE;
}
#endif

static HI_VOID JPEG_HDEC_CpyData2Reg(volatile HI_CHAR *pJpegRegVirAddr,const HI_VOID *pInMem,HI_U32 PhyOff,HI_U32 u32Bytes)
{
    HI_U32 Cnt = 0;

    if ((NULL == pJpegRegVirAddr) || (NULL == pInMem))
    {
       return;
    }

    if (((PhyOff + u32Bytes) >= JPGD_REG_LENGTH) || (NULL == pJpegRegVirAddr) || (NULL == pInMem))
    {
       return;
    }

    for (Cnt = 0; Cnt < u32Bytes; Cnt += 4)
    {
        *(volatile int *)(pJpegRegVirAddr + PhyOff + Cnt) = *(int *)((char*)pInMem + Cnt);
    }

    return;
}

#if 0
static HI_S32 JPEG_HDEC_CpyData2Buf(const volatile HI_CHAR *pJpegRegVirAddr,const HI_U32 PhyOff,const HI_U32 u32Bytes,HI_VOID *pOutMem)
{
    HI_U32 Cnt = 0;

    if ((NULL == pJpegRegVirAddr) || (NULL == pOutMem))
    {
       return HI_FAILURE;
    }

    if (((PhyOff + u32Bytes) >= JPGD_REG_LENGTH) || (NULL == pJpegRegVirAddr) || (NULL == pOutMem))
    {
       return HI_FAILURE;
    }

    for (Cnt = 0; Cnt < u32Bytes; Cnt += 4)
    {
        *(volatile int *)((char*)pOutMem + Cnt) = *(int *)(pJpegRegVirAddr + PhyOff + Cnt);
    }

    return HI_SUCCESS;
}
#endif
