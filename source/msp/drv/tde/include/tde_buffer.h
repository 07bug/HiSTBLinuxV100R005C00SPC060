/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_buffer.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef  __TDE_BUFFER_H__
#define  __TDE_BUFFER_H__

/*********************************add include here**********************************************/

#include "tde_define.h"

/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ********************************************/
STATIC HI_U32 s_u32TDEPhyBuff = 0;
STATIC HI_U32 s_u32TDEBuffRef = 0;

#ifndef HI_BUILD_IN_BOOT
static spinlock_t s_TDEBuffLock;
static HI_SIZE_T s_TDEBuffLockFlags;

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/
STATIC HI_U32 TDE_AllocPhysicBuff(HI_U32 u32CbCrOffset, HI_U32 BufSize)
{
    HI_U32 u32PhyAddr = 0;
    HI_U32 u32CscBufferSize = 0;
#ifndef HI_BUILD_IN_BOOT
	HI_BOOL bMmu = HI_TRUE;
#endif

#ifdef CFG_HI_TDE_CSCTMPBUFFER_SIZE
    u32CscBufferSize = CFG_HI_TDE_CSCTMPBUFFER_SIZE;
#elif defined(HI_BUILD_IN_BOOT)
    u32CscBufferSize = 0;
#else
   	u32CscBufferSize = g_u32TdeTmpBuf;
#endif

    TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

    if ((u32CbCrOffset + BufSize) >= u32CscBufferSize)
    {
        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        return 0;
    }

    if (0 == s_u32TDEPhyBuff)
    {
        s_u32TDEBuffRef = 0;

        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

        #ifndef HI_BUILD_IN_BOOT
            u32PhyAddr = HI_GFX_AllocMem("TDE_TEMP_BUFFER", "iommu",u32CscBufferSize, &bMmu);
        #else
        	u32PhyAddr = (HI_U32)HI_GFX_MMZ_Malloc(u32CscBufferSize,"TDE_TEMP_BUFFER");
        #endif
        if (0 == u32PhyAddr)
        {
            return 0;
        }

        TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

        s_u32TDEPhyBuff = u32PhyAddr;
    }

    s_u32TDEBuffRef++;

    TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

    return s_u32TDEPhyBuff + u32CbCrOffset;
}
#endif

STATIC HI_VOID TDE_FreePhysicBuff(HI_VOID)
{
    TDE_LOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
    if (0 == s_u32TDEBuffRef)
    {
        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
        return;
    }

    s_u32TDEBuffRef--;
    if (0 == s_u32TDEBuffRef)
    {
    #ifndef HI_BUILD_IN_BOOT
        HI_U32 u32PhyBuff = s_u32TDEPhyBuff;
    #endif

        s_u32TDEPhyBuff = 0;
        TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);

    #ifndef HI_BUILD_IN_BOOT
        HI_GFX_FreeMem(u32PhyBuff, HI_TRUE);
    #endif

        return;
    }

    TDE_UNLOCK(&s_TDEBuffLock, s_TDEBuffLockFlags);
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /* __TDE_BUFFER_H__ */
