
/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_osal.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2012/12/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_DISP_OSAL_H__
#define __DRV_DISP_OSAL_H__


/* platform switch */
//#define __DISP_PLATFORM_VC__
//#define __DISP_PLATFORM_SDK__
//#define __DISP_PLATFORM_BOOT__

#if defined(__DISP_PLATFORM_SDK__)

// for printk
#include <linux/kernel.h>

// for memset
#include <linux/string.h>

// for msleep
#include <linux/delay.h>


// for HI_KMALLOC
#include "hi_drv_mem.h"

#include "hi_drv_sys.h"


// for HI_ID_DISP
#include "hi_module.h"


// for HI_FATAL_PRINT
#include "hi_debug.h"

// for error code
#include "hi_error_mpi.h"

// for interrupt
#include <linux/interrupt.h>

// for do_gettimeofday
#include <linux/time.h>
#include <linux/ktime.h>


// for IO_ADDRESS
#include <asm/io.h>

// for MMZ
#include "hi_drv_mmz.h"

#define VDP_MEM_MAX 0x4000000

//for snprintf

/*
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <asm/signal.h>
#include <linux/time.h>
#include <linux/unistd.h>
#include <linux/delay.h>
#include <mach/hardware.h>
*/


#elif defined(__DISP_PLATFORM_VC__)
#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#endif

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


#if defined(__DISP_PLATFORM_SDK__)
/******************* SDK **********************/
#define DISP_PRINT(fmt...) \
            HI_INFO_PRINT(HI_ID_DISP, fmt)

#define DISP_FATAL(fmt...) \
            HI_FATAL_PRINT(HI_ID_DISP, fmt)

#define DISP_ERROR(fmt...) \
            HI_ERR_PRINT(HI_ID_DISP, fmt)

#define DISP_WARN(fmt...) \
            HI_WARN_PRINT(HI_ID_DISP, fmt)

#define DISP_INFO(fmt...) \
            HI_INFO_PRINT(HI_ID_DISP, fmt)

#define DISP_FATAL_RETURN() \
do{    \
    HI_FATAL_PRINT(HI_ID_DISP, "\n"); \
    return HI_FAILURE;  \
}while(0)

#define WIN_FATAL(fmt...) \
            HI_FATAL_PRINT(HI_ID_VO, fmt)

#define WIN_ERROR(fmt...) \
            HI_ERR_PRINT(HI_ID_VO, fmt)

#define WIN_WARN(fmt...) \
            HI_WARN_PRINT(HI_ID_VO, fmt)

#define WIN_INFO(fmt...) \
            HI_INFO_PRINT(HI_ID_VO, fmt)


#define DISP_ASSERT(exp) HI_ASSERT(exp)


#define DISP_IOADDRESS(a) IO_ADDRESS(a)

#define DISP_MALLOC(a) ({         \
                 HI_VOID* b = 0; \
                 if(a>VDP_MEM_MAX)\
                 {\
                    DISP_ERROR("alloc mem size (%d) more than MAX\n", a);\
                 }\
                 else\
                 {  \
                    b =  HI_VMALLOC(HI_ID_DISP, a); \
                    if (b) \
                        memset((HI_VOID*)b, 0, a); \
                 }\
                 b; \
 })



#define DISP_FREE(a)  \
             do{     \
                 if (a)\
                 { HI_VFREE(HI_ID_DISP, a); a = HI_NULL;} \
             }while(0)

#define DISP_MEMSET(a, b, c) memset(a, b, c)

#define DISP_MSLEEP(a) msleep(a)

#define DISP_UDELAY(a) udelay(a)

#define DISP_DSB()   dsb()

#define DISP_SPRINTF sprintf

#elif defined(__DISP_PLATFORM_VC__)
/******************* VC **********************/
#define DISP_PRINT printf

#define DISP_FATAL printf
#define DISP_ERROR printf
#define DISP_WARN  printf
#define DISP_INFO  printf

#define DISP_FATAL_RETURN() \
do{    \
    printf("FATAL! F=%s, L=%d\n", __FUNCTION__, __LINE__); \
    return HI_FAILURE;  \
}while(0)

#define WIN_FATAL printf
#define WIN_ERROR printf
#define WIN_WARN  printf
#define WIN_INFO  printf



#define DISP_IOADDRESS(a)

#define DISP_MALLOC(a) ({         \
                HI_VOID* b = 0; \
                if(a > VDP_MEM_MAX)\
                {\
                    DISP_ERROR("alloc mem size (%d) more than MAX\n", a);\
                }\
                else\
                {  \
                    b = (HI_U32) malloc(a); \
                    if (b) \
                        memset((HI_VOID*)b, 0, a); \
                }\
                b; \
})

#define DISP_FREE(a)  \
             do{     \
                 if (a)\
                 { free(a); a = HI_NULL;} \
             }while(0)

#define DISP_MEMSET(a, b, c) memset(a, b, c)

#define DISP_MSLEEP(a)

#define DISP_UDELAY(a)

#define DISP_DSB()

#define DISP_SPRINTF sprintf

#elif defined(__DISP_PLATFORM_BOOT__)

#include <uboot.h>
#ifdef HI_MINIBOOT_SUPPORT
#include <delay.h>
#endif
#include "hi_error_mpi.h"
#include "hi_common.h"


#define DISP_PRINT(fmt...)       HI_INFO_PRINT(HI_ID_DISP, fmt)

#define DISP_FATAL(fmt...)       HI_ERR_PRINT(HI_ID_DISP, fmt)

#define DISP_ERROR(fmt...)       HI_ERR_PRINT(HI_ID_DISP, fmt)

#define DISP_WARN(fmt...)        HI_INFO_PRINT(HI_ID_DISP, fmt)

#define DISP_INFO(fmt...)        HI_INFO_PRINT(HI_ID_DISP, fmt)

#define DISP_FATAL_RETURN() \
do{    \
    printf("\n"); \
    return HI_FAILURE;  \
}while(0)

//#define DISP_ASSERT(exp) HI_ASSERT(exp)


#define DISP_IOADDRESS(a) (HI_U32 *)(a)

#define DISP_MALLOC(a) ({         \
             HI_VOID* b = 0; \
             if(a > VDP_MEM_MAX)\
             {\
                DISP_ERROR("alloc mem size (%d) more than MAX\n", a);\
             }\
             else\
             {\
                b =  malloc(a); \
                if (b) \
                    memset((HI_VOID*)b, 0, a); \
             }\
             b; \
})


#define DISP_FREE(a)   free
#define DISP_MEMSET(a, b, c) memset(a, b, c)

#define DISP_MSLEEP(a) udelay(a*1000)

#define DISP_UDELAY(a) udelay(a)

//#define DISP_DSB()   dsb()

//#define DISP_SPRINTF sprintf

#endif


#define VDP_MEM_ALIGN 16

#define VDP_MEM_TYPE_SMMU "iommu"
#define VDP_MEM_TYPE_PHY  HI_NULL

#ifdef  CFG_VDP_MMU_SUPPORT
#define VDP_MEM_TYPE_MMZ  VDP_MEM_TYPE_SMMU
#else
#define VDP_MEM_TYPE_MMZ  VDP_MEM_TYPE_PHY
#endif

#define VDP_ADDR_NULL_PTR  HI_NULL_PTR
#define VDP_ADDR_INVALID (~0)

HI_S32 DISP_OS_GetTime(HI_U32 *t_ms);
HI_U64 DISP_OS_GetTimeUs(void);


typedef struct hiDISP_MMZ_BUF_S
{
    HI_U8 *pu8StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32Size;
    HI_BOOL bSmmu;
    HI_BOOL bSecure;
}DISP_MMZ_BUF_S;

#ifndef __DISP_PLATFORM_BOOT__

typedef  struct task_struct *THREAD;
typedef   wait_queue_head_t    WAIT_QUEUE_HAEAD;

#define  EVENT_WIN_NOTHING  0
#define  EVENT_WIN_STATE_UP_COMPLET  1
#define  EVENT_WIN_SYSTEM_UP_COMPLET  2
#define  EVENT_WIN_ATTR_UP_COMPLET  3

typedef struct hiQUEUE_EVENT_S
{
    wait_queue_head_t   queue_head;
    HI_U32              u32EventID;
} QUEUE_EVENT_S;
HI_S32 DISP_OSAL_InitEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID);
HI_S32 DISP_OSAL_SendEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID);
HI_S32 DISP_OSAL_WaitEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID, HI_S32 s32WaitTime );
HI_S32 DISP_OSAL_ResetEvent( QUEUE_EVENT_S *pEvent, HI_U32 u32EventID);


/************************************************************************/
/* spin lock operation                                                  */
/************************************************************************/

typedef spinlock_t DISP_OSAL_SPIN;
typedef struct list_head DISP_OSAL_LIST;
HI_S32 DISP_OSAL_InitSpin(DISP_OSAL_SPIN *pLock);
HI_S32 DISP_OSAL_DownSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags);
HI_S32 DISP_OSAL_UpSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags);
HI_S32 DISP_OSAL_TryLockSpin(DISP_OSAL_SPIN *pLock, unsigned long *flags);
#endif
HI_S32  DISP_OS_MMZ_Alloc(const char *bufname, char *zone_name, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf);
HI_VOID DISP_OS_MMZ_Release(DISP_MMZ_BUF_S *pstMBuf);

HI_S32 DISP_OS_MMZ_Map(DISP_MMZ_BUF_S *pstMBuf);
HI_S32 DISP_OS_MMZ_UnMap(DISP_MMZ_BUF_S *pstMBuf);

HI_S32 DISP_OS_MMZ_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf);
HI_VOID DISP_OS_MMZ_UnmapAndRelease(DISP_MMZ_BUF_S *pstMBuf);


HI_S32  DISP_OS_SECSMMU_Alloc(const char *bufname, HI_U32 size, int align, DISP_MMZ_BUF_S *pstMBuf);
HI_VOID DISP_OS_SECSMMU_Release(DISP_MMZ_BUF_S *pstMBuf);

HI_VOID DISP_OS_DIV64(HI_U64 numerator, HI_U32 denominator, HI_U64 *pu64Result);



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /*  __DRV_DISP_OSAL_H__  */


