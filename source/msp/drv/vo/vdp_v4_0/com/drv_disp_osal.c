/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_osal.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "drv_disp_osal.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


HI_S32 DISP_OS_GetTime(HI_U32 *t_ms)
{
#ifdef __DISP_PLATFORM_SDK__

    if (HI_DRV_SYS_GetTimeStampMs(t_ms))
    {
        DISP_ERROR("Get sys time failed, maybe not sys init.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;

#else

    return HI_SUCCESS;
#endif
}

HI_U64 DISP_OS_GetTimeUs(void)
{
#ifndef __DISP_PLATFORM_BOOT__
    struct timeval stTime;

    do_gettimeofday(&stTime);

    return  ((stTime.tv_sec * 1000000LLU) + stTime.tv_usec);

#else
    return 0;
#endif
}

#ifndef __DISP_PLATFORM_BOOT__

HI_S32 DISP_OSAL_InitSpin(DISP_OSAL_SPIN *pLock)
{
    spin_lock_init(pLock);
    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_DownSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags)
{
    spin_lock_irqsave(pLock, *flags);

    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_UpSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags)
{
    spin_unlock_irqrestore(pLock, *flags);

    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_TryLockSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags)
{
    if (spin_trylock_irqsave(pLock, *flags))
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}
#endif
HI_S32  DISP_OS_MMZ_Alloc(const char *bufname, char *zone_name, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf)
{
#ifdef __DISP_PLATFORM_SDK__
    HI_S32      Ret = HI_FAILURE;
    HI_BOOL     bSmmu = HI_FALSE;

    if ((size > VDP_MEM_MAX) || (0 == size))
    {
        DISP_ERROR(" alloc mem size (%d) more than MAX or equals to 0.\n", size);
        return HI_ERR_VO_MALLOC_FAILED;
    }

#ifdef CFG_VDP_MMU_SUPPORT
    if (zone_name)
    {
        if (0 == strncmp(zone_name, "iommu", strlen("iommu")))
        {
            bSmmu = HI_TRUE;
        }
    }
#endif

    if (!bSmmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        Ret = HI_DRV_MMZ_Alloc(bufname, zone_name, size, align, &MmzBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = MmzBuf.pu8StartVirAddr;
            pstMBuf->u32StartPhyAddr = MmzBuf.u32StartPhyAddr;
            pstMBuf->u32Size = MmzBuf.u32Size;
            pstMBuf->bSmmu = HI_FALSE;
            pstMBuf->bSecure= HI_FALSE;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
            pstMBuf->u32StartPhyAddr = 0;
            pstMBuf->u32Size = 0;
            pstMBuf->bSmmu = HI_FALSE;
            pstMBuf->bSecure= HI_FALSE;
        }
    }
#ifdef CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf;

        Ret = HI_DRV_SMMU_Alloc(bufname, size, align, &SmmuBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = SmmuBuf.pu8StartVirAddr;
            pstMBuf->u32StartPhyAddr = SmmuBuf.u32StartSmmuAddr;
            pstMBuf->u32Size = SmmuBuf.u32Size;
            pstMBuf->bSmmu = HI_TRUE;
            pstMBuf->bSecure= HI_FALSE;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
            pstMBuf->u32StartPhyAddr = 0;
            pstMBuf->u32Size = 0;
            pstMBuf->bSmmu = HI_TRUE;
            pstMBuf->bSecure= HI_FALSE;
        }
    }
#endif

    return Ret;
#else
    return HI_FAILURE;
#endif
}

HI_S32  DISP_OS_MMZ_Map(DISP_MMZ_BUF_S *pstMBuf)
{
#ifdef __DISP_PLATFORM_SDK__
    HI_S32 Ret = HI_FAILURE;

    if (!pstMBuf->bSmmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        MmzBuf.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
        MmzBuf.u32Size = pstMBuf->u32Size;

        Ret = HI_DRV_MMZ_Map(&MmzBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = MmzBuf.pu8StartVirAddr;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
        }
    }
#ifdef  CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf = {0};

        SmmuBuf.u32StartSmmuAddr = pstMBuf->u32StartPhyAddr;
        SmmuBuf.u32Size = pstMBuf->u32Size;

        Ret = HI_DRV_SMMU_Map(&SmmuBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = SmmuBuf.pu8StartVirAddr;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
        }
    }
#endif

    return Ret;
#else

    return HI_FAILURE;
#endif
}

HI_S32  DISP_OS_MMZ_UnMap(DISP_MMZ_BUF_S *pstMBuf)
{
    if (HI_NULL == pstMBuf)
    {
        DISP_ERROR("Pass null ptr to unmap.\n");
        return HI_ERR_DISP_NULL_PTR;
    }

#ifdef __DISP_PLATFORM_SDK__
    if (!pstMBuf->bSmmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        MmzBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        MmzBuf.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
        MmzBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_MMZ_Unmap(&MmzBuf);
    }
#ifdef  CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf = {0};

        SmmuBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        SmmuBuf.u32StartSmmuAddr = pstMBuf->u32StartPhyAddr;
        SmmuBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_SMMU_Unmap(&SmmuBuf);
    }
#endif

    return HI_SUCCESS;
#else

    return HI_FAILURE;
#endif
}

HI_VOID DISP_OS_MMZ_Release(DISP_MMZ_BUF_S *pstMBuf)
{
    if (HI_NULL == pstMBuf)
    {
        DISP_ERROR("pstMBuf is null !\n");
        return;
    }

#ifdef __DISP_PLATFORM_SDK__
    if (!pstMBuf->bSmmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        MmzBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        MmzBuf.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
        MmzBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_MMZ_Release(&MmzBuf);
    }
#ifdef  CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf = {0};

        SmmuBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        SmmuBuf.u32StartSmmuAddr = pstMBuf->u32StartPhyAddr;
        SmmuBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_SMMU_Release(&SmmuBuf);
    }
#endif
    return;
#else
    return;
#endif
}

HI_S32 DISP_OS_MMZ_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf)
{
#ifdef __DISP_PLATFORM_SDK__
    HI_S32      Ret = HI_FAILURE;
    HI_BOOL     Smmu = HI_FALSE;

    if ((size > VDP_MEM_MAX) || (0 == size))
    {
        DISP_ERROR(" alloc mem size (%d) more than MAX or equals to 0.\n", size);
        return HI_ERR_VO_MALLOC_FAILED;
    }

#ifdef CFG_VDP_MMU_SUPPORT
    if (zone_name)
    {
        if (0 == strncmp(zone_name, "iommu", strlen("iommu")))
        {
            Smmu = HI_TRUE;
        }
    }
#endif

    if (!Smmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        Ret = HI_DRV_MMZ_AllocAndMap(bufname, zone_name, size, align, &MmzBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = MmzBuf.pu8StartVirAddr;
            pstMBuf->u32StartPhyAddr = MmzBuf.u32StartPhyAddr;
            pstMBuf->u32Size = MmzBuf.u32Size;
            pstMBuf->bSmmu = HI_FALSE;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
            pstMBuf->u32StartPhyAddr = 0;
            pstMBuf->u32Size = 0;
            pstMBuf->bSmmu = HI_FALSE;
        }
    }
#ifdef CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf = {0};

        Ret = HI_DRV_SMMU_AllocAndMap(bufname, size, align, &SmmuBuf);
        if (HI_SUCCESS == Ret)
        {
            pstMBuf->pu8StartVirAddr = SmmuBuf.pu8StartVirAddr;
            pstMBuf->u32StartPhyAddr = SmmuBuf.u32StartSmmuAddr;
            pstMBuf->u32Size = SmmuBuf.u32Size;
            pstMBuf->bSmmu = HI_TRUE;
        }
        else
        {
            pstMBuf->pu8StartVirAddr = 0;
            pstMBuf->u32StartPhyAddr = 0;
            pstMBuf->u32Size = 0;
            pstMBuf->bSmmu = HI_TRUE;
        }
    }
#endif
    return Ret;
#else
    return HI_FAILURE;
#endif
}

HI_VOID DISP_OS_MMZ_UnmapAndRelease(DISP_MMZ_BUF_S *pstMBuf)
{
    if (HI_NULL == pstMBuf)
    {
        DISP_ERROR("pstMBuf is null !\n");
        return;
    }

#ifdef __DISP_PLATFORM_SDK__
    if (!pstMBuf->bSmmu)
    {
        MMZ_BUFFER_S MmzBuf = {0};

        MmzBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        MmzBuf.u32StartPhyAddr = pstMBuf->u32StartPhyAddr;
        MmzBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_MMZ_UnmapAndRelease(&MmzBuf);
    }
#ifdef CFG_VDP_MMU_SUPPORT
    else
    {
        SMMU_BUFFER_S SmmuBuf = {0};

        SmmuBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
        SmmuBuf.u32StartSmmuAddr = pstMBuf->u32StartPhyAddr;
        SmmuBuf.u32Size = pstMBuf->u32Size;

        HI_DRV_SMMU_UnmapAndRelease(&SmmuBuf);
    }
#endif

    return;
#else
    return;
#endif
}

HI_S32  DISP_OS_SECSMMU_Alloc(const char *bufname, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf)
{
#ifdef __DISP_PLATFORM_SDK__
    HI_S32      Ret = HI_FAILURE;
    SMMU_BUFFER_S SmmuBuf = {0};

    if ((size > VDP_MEM_MAX) || (0 == size))
    {
        DISP_ERROR(" alloc mem size (%d) more than MAX or equals to 0.\n", size);
        return HI_ERR_VO_MALLOC_FAILED;
    }

    Ret = HI_DRV_SECSMMU_Alloc(bufname, size, align, &SmmuBuf);
    if (HI_SUCCESS == Ret)
    {
        pstMBuf->pu8StartVirAddr = SmmuBuf.pu8StartVirAddr;
        pstMBuf->u32StartPhyAddr = SmmuBuf.u32StartSmmuAddr;
        pstMBuf->u32Size = SmmuBuf.u32Size;
        pstMBuf->bSmmu = HI_TRUE;
        pstMBuf->bSecure= HI_TRUE;
    }
    else
    {
        pstMBuf->pu8StartVirAddr = 0;
        pstMBuf->u32StartPhyAddr = 0;
        pstMBuf->u32Size = 0;
        pstMBuf->bSmmu = HI_TRUE;
        pstMBuf->bSecure= HI_TRUE;
    }

    return Ret;
#else
    return HI_SUCCESS;
#endif
}

HI_VOID DISP_OS_SECSMMU_Release(DISP_MMZ_BUF_S *pstMBuf)
{
#ifdef __DISP_PLATFORM_SDK__

    SMMU_BUFFER_S SmmuBuf = {0};

    SmmuBuf.pu8StartVirAddr = pstMBuf->pu8StartVirAddr;
    SmmuBuf.u32StartSmmuAddr = pstMBuf->u32StartPhyAddr;
    SmmuBuf.u32Size = pstMBuf->u32Size;

    HI_DRV_SECSMMU_Release(&SmmuBuf);
#endif

    return ;
}

#ifdef HI_MINIBOOT_SUPPORT
extern uint64 __udivmoddi4(uint64 a, uint64 b, uint64* rem);
HI_VOID DISP_OS_DIV64(HI_U64 numerator, HI_U32 denominator, HI_U64 *pu64Result)
{
    HI_U64  rem = 0;
    *pu64Result = __udivmoddi4(numerator, denominator, &rem);
    return;
}
#else
HI_VOID DISP_OS_DIV64(HI_U64 numerator, HI_U32 denominator, HI_U64 *pu64Result)
{
    (HI_VOID)do_div(numerator, denominator);
    *pu64Result = numerator;
    return;
}
#endif

#ifndef __DISP_PLATFORM_BOOT__

HI_S32 DISP_OSAL_InitEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID)
{
    pEvent->u32EventID = u32EventID;
    init_waitqueue_head( &(pEvent->queue_head) );
    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_SendEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID)
{
    pEvent->u32EventID = u32EventID;
    wake_up(&(pEvent->queue_head));
    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_WaitEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID, HI_S32 s32WaitTime )
{
    HI_S32 s32Ret = HI_FAILURE;

    HI_S32 u32StartTime = 0;
    HI_S32 u32EndtTime = 0;
    DISP_OS_GetTime(&u32StartTime);

    /*return 0 :means not  match condition time out.
          return num :  means match condition, time left.
        */
    s32Ret = wait_event_timeout(pEvent->queue_head, (pEvent->u32EventID == u32EventID), s32WaitTime );
    if ((s32Ret == 0) || (pEvent->u32EventID != u32EventID))
    {
        return HI_FAILURE;
    }
    DISP_OS_GetTime(&u32EndtTime);

    return HI_SUCCESS;
}

HI_S32 DISP_OSAL_ResetEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID)
{
    pEvent->u32EventID = u32EventID;
    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */
