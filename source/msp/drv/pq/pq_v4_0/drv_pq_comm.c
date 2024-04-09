/******************************************************************************

  Copyright (C), 2015, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_comm.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/09/07
  Description   :

******************************************************************************/
#include <linux/fs.h>

#include "hi_osal.h"
#include "hi_drv_pq.h"
#include "drv_pq_comm.h"
#include "pq_hal_comm.h"
#include "hi_drv_mem.h"

DEFINE_SEMAPHORE(g_PqMutex);

#define DRV_PQ_LOCK()      \
    do{         \
        if(down_interruptible(&g_PqMutex))   \
        {       \
            HI_ERR_PQ("DRV PQ lock error!\n"); \
            return HI_FAILURE;  \
        }       \
    }while(0)

#define DRV_PQ_UNLOCK()      \
    do{         \
        up(&g_PqMutex);    \
    }while(0)

#define MIN_LEN(x, y) ( (x) > (y) ? (y) : (x) )

static PQ_SOURCE_MODE_E sg_enSourceMode = PQ_SOURCE_MODE_NO;
static PQ_OUTPUT_MODE_E sg_enOutputMode = PQ_OUTPUT_MODE_NO;
static PQ_ALG_REG_S   *psg_astAlgRegModule[HI_PQ_MODULE_BUTT] = { NULL };
static HI_U8 sg_au8MoudleCtrl[HI_PQ_MODULE_BUTT][PQ_SOURCE_MODE_BUTT];

HI_S32 PQ_COMM_SetPqStatus(PQ_STATUS_S *pstPqStatus)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqStatus);

    DRV_PQ_LOCK();
    memcpy(&g_stPqStatus, pstPqStatus, sizeof(PQ_STATUS_S));
    DRV_PQ_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 PQ_COMM_GetPqStatus(PQ_STATUS_S *pstPqStatus)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqStatus);

    memcpy(pstPqStatus, &g_stPqStatus, sizeof(PQ_STATUS_S));

    return HI_SUCCESS;
}


HI_S32 PQ_COMM_CheckChipName(HI_CHAR *pchChipName)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_CHECK_NULL_PTR_RE_FAIL(pchChipName);

#if defined(CHIP_TYPE_hi3798cv200)
    s32Ret = HI_OSAL_Strncmp(pchChipName , "HI_CHIP_TYPE_HI3798C", strlen("HI_CHIP_TYPE_HI3798C"));
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    s32Ret = HI_OSAL_Strncmp(pchChipName , "HI_CHIP_TYPE_HI3798M", strlen("HI_CHIP_TYPE_HI3798M"));
#elif defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    s32Ret = HI_OSAL_Strncmp(pchChipName , "HI_CHIP_TYPE_HI3796M", strlen("HI_CHIP_TYPE_HI3796M"));
#else
    HI_ERR_PQ("unknown Chip Type \r\n");
    return HI_FAILURE;
#endif

    if (0 != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 PQ_COMM_AlgRegister( HI_PQ_MODULE_E       enModule,
                            PQ_REG_TYPE_E                enRegType,
                            PQ_BIN_ADAPT_TYPE_E          enAdaptType,
                            const HI_U8                 *pu8AlgName,
                            HI_VOID                     *pData,
                            const stPQAlgFuncs          *pFuncs)
{
    PQ_ALG_REG_S *pstAlgReg;
    HI_U32   u32MinLen = 0;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enModule, HI_PQ_MODULE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enRegType, REG_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enAdaptType, PQ_BIN_ADAPT_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pu8AlgName);
    PQ_CHECK_NULL_PTR_RE_FAIL(pFuncs);

    if (HI_NULL == psg_astAlgRegModule[enModule])
    {
        pstAlgReg = (PQ_ALG_REG_S *)PQ_KMALLOC(sizeof(PQ_ALG_REG_S), GFP_KERNEL);
        if (HI_NULL == pstAlgReg)
        {
            HI_ERR_PQ("ID: %d, register failure!", (HI_U32)enRegType);
            return HI_FAILURE;
        }

        psg_astAlgRegModule[enModule] = pstAlgReg;
    }
    else
    {
        pstAlgReg = psg_astAlgRegModule[enModule];
    }

    pstAlgReg->u32AlgID      = (HI_U32)enModule;
    pstAlgReg->u32TypeID     = (HI_U32)enRegType;
    pstAlgReg->u32AdapeType  = (HI_U32)enAdaptType;
    pstAlgReg->Data          = pData;
    pstAlgReg->pFun          = pFuncs;

    u32MinLen = MIN_LEN( sizeof(pstAlgReg->u8AlgName) - 1, strlen(pu8AlgName));
    memset(pstAlgReg->u8AlgName, 0, sizeof(pstAlgReg->u8AlgName));
    memcpy(pstAlgReg->u8AlgName, pu8AlgName, u32MinLen);

    return HI_SUCCESS;
}

HI_S32 PQ_COMM_AlgUnRegister( HI_PQ_MODULE_E      enModule)
{
    PQ_ALG_REG_S *pstAlgReg;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enModule, HI_PQ_MODULE_BUTT);

    pstAlgReg = psg_astAlgRegModule[enModule];

    pstAlgReg->u32AlgID      =  HI_NULL;
    pstAlgReg->u32TypeID     =  HI_NULL;
    pstAlgReg->u32AdapeType  =  HI_NULL;
    pstAlgReg->Data          =  HI_NULL;
    pstAlgReg->pFun          =  HI_NULL;

    memset(pstAlgReg->u8AlgName, 0, sizeof(pstAlgReg->u8AlgName));

    PQ_KFREE_SAFE(pstAlgReg);

    psg_astAlgRegModule[enModule] = HI_NULL;
    return HI_SUCCESS;
}

PQ_ALG_REG_S *PQ_COMM_GetAlg(HI_PQ_MODULE_E    enModule )
{
    if (HI_PQ_MODULE_BUTT <= enModule)
    {
        return HI_NULL;
    }

    return psg_astAlgRegModule[enModule];
}

HI_U32 PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_E    enModule )
{
    if (HI_PQ_MODULE_BUTT <= enModule)
    {
        return REG_TYPE_BUTT;
    }

    if (HI_NULL == psg_astAlgRegModule[enModule])
    {
        return REG_TYPE_BUTT;
    }

    return psg_astAlgRegModule[enModule]->u32TypeID;
}

HI_U32 PQ_COMM_GetAlgAdapeType(HI_PQ_MODULE_E    enModule )
{
    if (HI_PQ_MODULE_BUTT <= enModule)
    {
        return PQ_BIN_ADAPT_BUTT;
    }

    if (HI_NULL == psg_astAlgRegModule[enModule])
    {
        return PQ_BIN_ADAPT_BUTT;
    }

    return psg_astAlgRegModule[enModule]->u32AdapeType;
}

HI_U8 *PQ_COMM_GetAlgName(HI_PQ_MODULE_E    enModule )
{
    if (HI_PQ_MODULE_BUTT <= enModule)
    {
        return HI_NULL;
    }

    if (HI_NULL == psg_astAlgRegModule[enModule])
    {
        return HI_NULL;
    }

    return psg_astAlgRegModule[enModule]->u8AlgName;
}

/* enModule must be a  Clear Module , enSrcMode has been charged when set*/
HI_U8 PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_E  enModule, PQ_SOURCE_MODE_E enSrcMode)
{
    return sg_au8MoudleCtrl[enModule][enSrcMode];
}

HI_VOID PQ_COMM_SetMoudleCtrl(HI_PQ_MODULE_E  enModule, PQ_SOURCE_MODE_E enSrcMode, HI_U8 u8OnOff)
{
    sg_au8MoudleCtrl[enModule][enSrcMode] = u8OnOff;
    return;
}

PQ_SOURCE_MODE_E PQ_COMM_CheckSourceMode(HI_U32 u32Width)
{
    if (720 >= u32Width) /* SD Source */
    {
        return PQ_SOURCE_MODE_SD;
    }
    else if ((1280 >= u32Width) && (720 < u32Width)) /* HD Source */
    {
        return PQ_SOURCE_MODE_HD;
    }
    else if ((1920 >= u32Width) && (1280 < u32Width)) /* FHD Source */
    {
        return PQ_SOURCE_MODE_HD;
    }
    else if ((4096 >= u32Width) && (1920 < u32Width)) /* UHD Source */
    {
        return PQ_SOURCE_MODE_UHD;
    }

    return PQ_SOURCE_MODE_NO;
}

PQ_OUTPUT_MODE_E PQ_COMM_CheckOutputMode(HI_S32 s32Width)
{
    if ((720 >= s32Width) && (0 < s32Width)) /* SD Source */
    {
        return PQ_OUTPUT_MODE_SD;
    }
    else if ((1280 >= s32Width) && (720 < s32Width)) /* HD Source */
    {
        return PQ_OUTPUT_MODE_HD;
    }
    else if ((1920 >= s32Width) && (1280 < s32Width)) /* FHD Source */
    {
        return PQ_OUTPUT_MODE_HD;
    }
    else if ((4096 >= s32Width) && (1920 < s32Width)) /* UHD Source */
    {
        return PQ_OUTPUT_MODE_UHD;
    }

    return PQ_OUTPUT_MODE_NO;

}

PQ_SOURCE_MODE_E PQ_COMM_GetSourceMode(HI_VOID)
{
    return sg_enSourceMode;
}

HI_VOID PQ_COMM_SetSourceMode(PQ_SOURCE_MODE_E enMode)
{
    PQ_CHECK_OVER_RANGE_RE_NULL(enMode, PQ_SOURCE_MODE_BUTT);

    sg_enSourceMode = enMode;
    return;
}

PQ_OUTPUT_MODE_E PQ_COMM_GetOutputMode(HI_VOID)
{
    return sg_enOutputMode;
}

HI_VOID PQ_COMM_SetOutputMode(PQ_OUTPUT_MODE_E enMode)
{
    PQ_CHECK_OVER_RANGE_RE_NULL(enMode, PQ_OUTPUT_MODE_BUTT);

    sg_enOutputMode = enMode;
    return;
}

HI_ULONG PQ_GetTimeUs(void)
{
#ifndef __PQ_PLATFORM_BOOT__
    struct timeval stTime;

    do_gettimeofday(&stTime);

    return  (HI_ULONG)((stTime.tv_sec * 1000000LLU) + stTime.tv_usec);

#else
    return 0;
#endif
}


