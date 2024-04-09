
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_venc_intf.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       :
  Description   :
  History       :
  1.Date        : 2010/03/17
    Author      : sdk
    Modification: Created file
******************************************************************************/

#include <asm/uaccess.h>
#include <linux/delay.h>

#include "hi_unf_common.h"
#include "hi_drv_dev.h"
#include "drv_venc_ext.h"
#include "hi_drv_file.h"
#include "hi_drv_proc.h"
#include "hi_drv_module.h"
#include "drv_venc_efl.h"
#include "drv_omxvenc_efl.h"
#include "drv_venc_ioctl.h"
#include "drv_venc.h"
#include "drv_omxvenc.h"
#include "hi_kernel_adapt.h"

#ifdef VENC_SUPPORT_JPGE
#include "drv_jpge_ext.h"
#endif

static UMAP_DEVICE_S g_VencRegisterData;

#ifdef VENC_SUPPORT_JPGE
JPGE_EXPORT_FUNC_S *pJpgeFunc = HI_NULL;
#endif

extern OPTM_VENC_CHN_S g_stVencChn[HI_VENC_MAX_CHN];
extern spinlock_t g_SendFrame_Lock[HI_VENC_MAX_CHN];

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define Smooth_printk printk
#else
#define Smooth_printk(format, arg...)
#endif

#define D_VENC_GET_CHN(u32VeChn, hVencChn) \
    do {\
        if (hVencChn == NULL)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hVEncHandle == hVencChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_GET_CHN_BY_UHND(u32VeChn, hVencUsrChn) \
    do {\
        if (hVencUsrChn == HI_INVALID_HANDLE)\
        {\
            u32VeChn = HI_VENC_MAX_CHN;\
            break;\
        }\
        u32VeChn = 0; \
        while (u32VeChn < HI_VENC_MAX_CHN)\
        {   \
            if (g_stVencChn[u32VeChn].hUsrHandle == hVencUsrChn)\
            { \
                break; \
            } \
            u32VeChn++; \
        } \
    } while (0)

#define D_VENC_UPDATA_2(data,curdata) \
    do{\
          *(data + 1) = *data;\
          *data = curdata;\
        }while(0)

HI_BOOL gb_IsVencChanAlive[HI_VENC_MAX_CHN] = {HI_FALSE};

/*============Deviece===============*/

//VENC device open times
atomic_t g_VencCount = ATOMIC_INIT(0);

HI_VOID VENC_TimerFunc(HI_LENGTH_T value);

HI_S32 VENC_DRV_Resume(HI_VOID);
HI_S32 VENC_DRV_Suspend(HI_VOID);

VENC_EXPORT_FUNC_S s_VencExportFuncs =
{
    .pfnVencQueueFrame   = VENC_DRV_EflQFrameByAttach,
    .pfnVencWakeUpThread = VENC_DRV_EflWakeUpThread,
    .pfnVencResume       = VENC_DRV_Resume,
    .pfnVencSuspend      = VENC_DRV_Suspend,
};

struct timer_list vencTimer;

HI_DECLARE_MUTEX(g_VencMutex);

HI_U32 g_u32VencOpenFlag = 0;

static HI_S32 VENC_DRV_Open(struct inode *finode, struct file  *ffile)
{
    HI_S32 Ret, i;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
#ifdef VENC_S6V550_EXT_CONFIG
        VENC_DRV_BoardInit();
#endif
        VENC_DRV_InitEvent();
        Ret = VENC_DRV_EflOpenVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);
            return HI_FAILURE;
        }


        for (i = 0; i < HI_VENC_MAX_CHN; i++)
        {
            memset(&(g_stVencChn[i]), 0, sizeof(OPTM_VENC_CHN_S));
            g_stVencChn[i].hVEncHandle = NULL;
            g_stVencChn[i].hUsrHandle = HI_INVALID_HANDLE;
        }

        init_timer(&vencTimer);
        vencTimer.expires  = jiffies + (HZ);
        vencTimer.function = VENC_TimerFunc;
        add_timer(&vencTimer);
    }

    g_u32VencOpenFlag = 1;
    up(&g_VencMutex);

#ifdef VENC_SUPPORT_JPGE
    Ret = HI_DRV_MODULE_GetFunction(HI_ID_JPGENC, (HI_VOID**)&pJpgeFunc);
    if(HI_SUCCESS != Ret)
    {
         HI_ERR_VENC("GetFunction from JPGE  failed.\n");
         pJpgeFunc = HI_NULL;
    }
    else
    {
         pJpgeFunc->pfnJpgeInit();
    }
#endif
    return HI_SUCCESS;
}

static HI_S32 VENC_DRV_Close(struct inode *finode, struct file  *ffile)
{
    HI_U32 i = 0;
    HI_S32 Ret = 0;

    Ret = down_interruptible(&g_VencMutex);
   if (Ret != HI_SUCCESS)
   {
       HI_WARN_VENC("call down_interruptible err!\n");
   }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if ((g_stVencChn[i].pWhichFile == ffile)
            && (g_stVencChn[i].hVEncHandle != NULL))
        {
            HI_INFO_VENC("Try VENC_DestroyChn %d/%#p.\n", i, g_stVencChn[i].hVEncHandle);
            Ret = VENC_DRV_DestroyChn(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("force DestroyChn %d failed, Ret=%#x.\n", i, Ret);
            }
            g_stVencChn[i].pWhichFile = HI_NULL;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {

        del_timer_sync(&vencTimer);
        VENC_DRV_EflCloseVedu();

#ifdef VENC_SUPPORT_JPGE
        if (pJpgeFunc)
        {
            pJpgeFunc->pfnJpgeDeInit();
        }
#endif

#ifdef VENC_S6V550_EXT_CONFIG
        VENC_DRV_BoardDeinit();
#endif
    }
    g_u32VencOpenFlag = 0;
    up(&g_VencMutex);


    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Suspend(HI_VOID)
{
    HI_U32 i = 0;
    HI_S32 Ret;

    if (!g_u32VencOpenFlag)
    {
        HI_PRINT("VENC suspend OK\n");
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        HI_INFO_VENC("suspend venc channel %d handle %p, invalid = %x\n", i, g_stVencChn[i].hVEncHandle,
                      HI_INVALID_HANDLE );
        if (g_stVencChn[i].hVEncHandle != NULL && g_stVencChn[i].bEnable == 1)
        {

            Ret = VENC_DRV_StopReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_WARN_VENC("VENC_StopReceivePic %d failed, Ret=%#x.\n", i, Ret);
            }

            gb_IsVencChanAlive[i] = HI_TRUE;
        }
        else
        {
            gb_IsVencChanAlive[i] = HI_FALSE;
        }
    }

    if (atomic_dec_and_test(&g_VencCount))
    {
        VENC_DRV_EflSuspendVedu();

#ifdef VENC_S6V550_EXT_CONFIG
        VENC_DRV_BoardDeinit();
#endif
    }

    HI_PRINT("VENC suspend OK\n");
    up(&g_VencMutex);
    return HI_SUCCESS;
}

HI_S32 VENC_DRV_Resume(HI_VOID)
{
   HI_S32 Ret, i;
    //HI_MOD_ID_E enModId;

    if (!g_u32VencOpenFlag)
    {
        HI_PRINT("VENC resume OK\n");
        return 0;
    }

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    if (1 == atomic_inc_return(&g_VencCount))
    {
#ifdef VENC_S6V550_EXT_CONFIG
        VENC_DRV_BoardInit();
#endif
        VENC_DRV_InitEvent();
        Ret = VENC_DRV_EflResumeVedu();
        if (HI_SUCCESS != Ret)
        {
            HI_FATAL_VENC("VeduEfl_OpenVedu failed, ret=%d\n", Ret);
            atomic_dec(&g_VencCount);
            up(&g_VencMutex);

            return HI_FAILURE;
        }
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        if (gb_IsVencChanAlive[i])
        {
#ifdef HI_SMMU_SUPPORT
            {
                HI_U32 u32ptaddr,u32err_rdaddr,u32err_wraddr;
                HI_DRV_SMMU_GetPageTableAddr(&u32ptaddr,&u32err_rdaddr, &u32err_wraddr);
                g_stVencChn[i].hVEncHandle->u32SmmuPageBaseAddr = u32ptaddr;
                g_stVencChn[i].hVEncHandle->u32SmmuErrReadAddr  = u32err_rdaddr;
                g_stVencChn[i].hVEncHandle->u32SmmuErrWriteAddr = u32err_wraddr;
            }
#endif
            HI_INFO_VENC(" h %d, fr %d. gop %d\n ",
                          g_stVencChn[i].stChnUserCfg.u32Height,
                          g_stVencChn[i].stChnUserCfg.u32TargetFrmRate,
                          g_stVencChn[i].stChnUserCfg.u32Gop);
            Ret = VENC_DRV_StartReceivePic(g_stVencChn[i].hVEncHandle);
            if (HI_SUCCESS != Ret)
            {
                HI_FATAL_VENC(KERN_ERR "Resume VENC_StartReceivePic %d failed.\n", i);
                continue;
            }
        }
    }

    HI_PRINT("VENC resume OK\n");
    up(&g_VencMutex);

    return HI_SUCCESS;
}

static HI_S32 VENC_Ioctl_Create(struct file *file, HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;

    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;
    VeduEfl_EncPara_S* hKernVencChn = NULL;
    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_CreateChn((VeduEfl_EncPara_S**)&hKernVencChn, (venc_chan_cfg *)&(pstCreateInfo->stAttr),
                                 (VENC_CHN_INFO_S *)&(pstCreateInfo->stVeInfo), pstCreateInfo->bOMXChn, file);
    if (hKernVencChn == HI_NULL)
    {
        up(&g_VencMutex);

        return Ret;
    }

    D_VENC_GET_CHN(u32Index, hKernVencChn);

    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CREATE_ERR;
    }
    g_stVencChn[u32Index].hUsrHandle = GET_VENC_CHHANDLE(u32Index);
    pstCreateInfo->hVencChn = g_stVencChn[u32Index].hUsrHandle;
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_Destroy(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *phVencChn = (HI_HANDLE *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *phVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_DestroyChn(g_stVencChn[u32Index].hVEncHandle);

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_AttachInput(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ATTACH_S *pAttachInfo = (VENC_INFO_ATTACH_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pAttachInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_AttachInput(g_stVencChn[u32Index].hVEncHandle, pAttachInfo->hSrc, pAttachInfo->enModId);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_DetachInput(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ATTACH_S *pAttachInfo = (VENC_INFO_ATTACH_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pAttachInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    pAttachInfo->enModId = (HI_MOD_ID_E)((g_stVencChn[u32Index].hSource & 0xff0000) >> 16);
    Ret = VENC_DRV_DetachInput(g_stVencChn[u32Index].hVEncHandle, g_stVencChn[u32Index].hSource, pAttachInfo->enModId);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_SetSrc(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_SET_SRC_S *pSetSrc = (VENC_SET_SRC_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pSetSrc->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_SetSrcInfo(g_stVencChn[u32Index].hVEncHandle,&(pSetSrc->stVencSrc));
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_AcquireStream(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ACQUIRE_STREAM_S *pstAcqStrm = (VENC_INFO_ACQUIRE_STREAM_S*)arg;
    VeduEfl_EncPara_S* tempHandle = NULL;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstAcqStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }
    tempHandle = g_stVencChn[u32Index].hVEncHandle;
    up(&g_VencMutex);

    Ret = VENC_DRV_AcquireStream(tempHandle,
                                 &(pstAcqStrm->stStream),
                                 pstAcqStrm->u32BlockFlag,
                                 &(pstAcqStrm->stBufOffSet));

    return Ret;
}

static HI_S32 VENC_Ioctl_ReleaseStream(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_ACQUIRE_STREAM_S *pstAcqStrm = (VENC_INFO_ACQUIRE_STREAM_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstAcqStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_ReleaseStream(g_stVencChn[u32Index].hVEncHandle, pstAcqStrm);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_StartRecvPic(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_StartReceivePic(g_stVencChn[u32Index].hVEncHandle);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_StopRecvPic(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_StopReceivePic(g_stVencChn[u32Index].hVEncHandle);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_SetChnAttr(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstCreateInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_SetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr.VencUnfAttr),&(pstCreateInfo->stVeInfo));
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_GetChnAttr(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_CREATE_S *pstCreateInfo = (VENC_INFO_CREATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstCreateInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_GetAttr(g_stVencChn[u32Index].hVEncHandle, &(pstCreateInfo->stAttr.VencUnfAttr));
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_RequestIFrame(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    HI_HANDLE *pHandle = (HI_HANDLE*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, *pHandle);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].hJPGE == HI_INVALID_HANDLE)
    {
       Ret = VENC_DRV_RequestIFrame(g_stVencChn[u32Index].hVEncHandle);
    }
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_QueueFrame(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pQueueFrameInfo = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pQueueFrameInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].bOMXChn)
    {
       Ret = VENC_DRV_QueueFrame_OMX(g_stVencChn[u32Index].hVEncHandle, &(pQueueFrameInfo->stVencFrame_OMX));
    }
    else
    {
       Ret = VENC_DRV_QueueFrame(g_stVencChn[u32Index].hVEncHandle, &(pQueueFrameInfo->stVencFrame));
    }

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_DequeueFrame(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pQueueFrameInfo = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pQueueFrameInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_DequeueFrame(g_stVencChn[u32Index].hVEncHandle,&(pQueueFrameInfo->stVencFrame));
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_GetCapability(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_VENC_CAP_S *pstCapability = (HI_UNF_VENC_CAP_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_GetCapability(pstCapability);
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_SetRateControlType(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_RATECONTROL_S *pstRCType = (VENC_INFO_RATECONTROL_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstRCType->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_JPEG)
    {
        HI_ERR_VENC("Current channel(%d) Encode Type = %d, not support Set RateControl Type(%d)!\n",
                    u32Index, g_stVencChn[u32Index].stChnUserCfg.enVencType,pstRCType->eRCType);
        Ret = HI_ERR_VENC_NOT_SUPPORT;
    }
    else
    {
        Ret = VENC_DRV_SetRateControlType(g_stVencChn[u32Index].hVEncHandle, pstRCType->eRCType);
    }

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_GetRateControlType(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_RATECONTROL_S *pstRCType = (VENC_INFO_RATECONTROL_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstRCType->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    if (g_stVencChn[u32Index].stChnUserCfg.enVencType == HI_UNF_VCODEC_TYPE_JPEG)
    {
        HI_ERR_VENC("Current channel(%d) Encode Type = %d not support get RateControl Type\n",
                    u32Index, g_stVencChn[u32Index].stChnUserCfg.enVencType,pstRCType->eRCType);
        pstRCType->eRCType = VENC_DRV_ControlRateMax;
        Ret = HI_ERR_VENC_NOT_SUPPORT;
    }
    else
    {
        Ret = VENC_DRV_GetRateControlType(g_stVencChn[u32Index].hVEncHandle, &pstRCType->eRCType);
    }

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_SetInFrmRateType(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_FRMRATE_S *pstInFrmRateType = (VENC_INFO_FRMRATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstInFrmRateType->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_SetInFrmRateType(g_stVencChn[u32Index].hVEncHandle, pstInFrmRateType->eFrmRateType);

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_GetInFrmRateType(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_FRMRATE_S *pstInFrmRateType = (VENC_INFO_FRMRATE_S *)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstInFrmRateType->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_GetInFrmRateType(g_stVencChn[u32Index].hVEncHandle, &pstInFrmRateType->eFrmRateType);

    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_GetMsg(HI_VOID * arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_GET_MSG_S *pMessageInfo   = (VENC_INFO_GET_MSG_S *)arg;
    VeduEfl_EncPara_S* tempHandle = NULL;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pMessageInfo->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    tempHandle = g_stVencChn[u32Index].hVEncHandle;
    up(&g_VencMutex);

    Ret = VENC_DRV_GetMessage_OMX(tempHandle,&(pMessageInfo->msg_info_omx));

    return Ret;
}

static HI_S32 VENC_Ioctl_MmzMap(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_VENC_MMZ_PHY_S* pMMZPhyInfo = (VENC_INFO_VENC_MMZ_PHY_S*)arg;
    VENC_INFO_MMZ_MAP_S pMMBInfo;

    pMMBInfo.stVencBuf.phyaddr = pMMZPhyInfo->phyaddr;
    pMMBInfo.stVencBuf.bufsize = pMMZPhyInfo->bufsize;
    D_VENC_GET_CHN_BY_UHND(u32Index, pMMZPhyInfo->hVencChn);
    D_VENC_CHECK_CHN(u32Index);

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_MMZ_Map_OMX(u32Index,&(pMMBInfo.stVencBuf) );
    up(&g_VencMutex);
    if (HI_SUCCESS == Ret)
    {
        pMMZPhyInfo->vir2phy_offset = (HI_VIRT_ADDR_T)pMMBInfo.stVencBuf.kernel_viraddr - (HI_VIRT_ADDR_T)pMMBInfo.stVencBuf.phyaddr;
    }

    return Ret;
}

static HI_S32 VENC_Ioctl_MmzUmmap(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_VENC_MMZ_PHY_S* pMMZPhyInfo = (VENC_INFO_VENC_MMZ_PHY_S*)arg;
    VENC_INFO_MMZ_MAP_S pMMBInfo;

    pMMBInfo.stVencBuf.phyaddr = pMMZPhyInfo->phyaddr;
    pMMBInfo.stVencBuf.bufsize = pMMZPhyInfo->bufsize;
    D_VENC_GET_CHN_BY_UHND(u32Index, pMMZPhyInfo->hVencChn);
    D_VENC_CHECK_CHN(u32Index);
    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    Ret = VENC_DRV_MMZ_UMMap_OMX(u32Index,&(pMMBInfo.stVencBuf) );
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_QueueStream(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_QUEUE_FRAME_S *pstQueStrm = (VENC_INFO_QUEUE_FRAME_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstQueStrm->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_QueueStream_OMX(g_stVencChn[u32Index].hVEncHandle, &(pstQueStrm->stVencFrame_OMX));
    up(&g_VencMutex);

    return Ret;
}

static HI_S32 VENC_Ioctl_FlushPort(HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    VENC_INFO_FLUSH_PORT_S *pstFlushPort = (VENC_INFO_FLUSH_PORT_S*)arg;

    Ret = down_interruptible(&g_VencMutex);
    if (Ret != HI_SUCCESS)
    {
        HI_WARN_VENC("call down_interruptible err!\n");
    }

    D_VENC_GET_CHN_BY_UHND(u32Index, pstFlushPort->hVencChn);
    if (u32Index >= HI_VENC_MAX_CHN)
    {
       up(&g_VencMutex);

       return HI_ERR_VENC_CHN_NOT_EXIST;
    }

    Ret = VENC_DRV_FlushPort_OMX(g_stVencChn[u32Index].hVEncHandle, pstFlushPort->u32PortIndex, pstFlushPort->u32InterFlush);
    up(&g_VencMutex);

    return Ret;
}

HI_S32 VENC_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *arg)
{
    HI_S32 Ret = HI_FAILURE;

    if (arg == NULL)
    {
       HI_WARN_VENC("Arg is null!\n");
       return HI_ERR_VENC_INVALID_PARA;
    }

    switch (cmd)
    {
        case CMD_VENC_CREATE_CHN:
        {
            Ret = VENC_Ioctl_Create(file,arg);
        }
        break;

        case CMD_VENC_DESTROY_CHN:
        {
            Ret = VENC_Ioctl_Destroy(arg);
        }
        break;

        case CMD_VENC_ATTACH_INPUT:
        {
            Ret = VENC_Ioctl_AttachInput(arg);
        }
        break;

        case CMD_VENC_DETACH_INPUT:
        {
            Ret = VENC_Ioctl_DetachInput(arg);
        }
        break;

        case CMD_VENC_SET_SRC:
        {
            Ret = VENC_Ioctl_SetSrc(arg);
        }
        break;

        case CMD_VENC_ACQUIRE_STREAM:
        {
            Ret = VENC_Ioctl_AcquireStream(arg);
        }
        break;

        case CMD_VENC_RELEASE_STREAM:
        {
            Ret = VENC_Ioctl_ReleaseStream(arg);
        }
        break;

        case CMD_VENC_START_RECV_PIC:
        {
            Ret = VENC_Ioctl_StartRecvPic(arg);
        }
        break;

        case CMD_VENC_STOP_RECV_PIC:
        {
            Ret = VENC_Ioctl_StopRecvPic(arg);
        }
        break;

        case CMD_VENC_SET_CHN_ATTR:
        {
            Ret = VENC_Ioctl_SetChnAttr(arg);
        }
        break;

        case CMD_VENC_GET_CHN_ATTR:
        {
            Ret = VENC_Ioctl_GetChnAttr(arg);
        }
        break;

        case CMD_VENC_REQUEST_I_FRAME:
        {
            Ret = VENC_Ioctl_RequestIFrame(arg);
        }
        break;

        case CMD_VENC_QUEUE_FRAME:                 //both omxvenc & venc use!!
        {
            Ret = VENC_Ioctl_QueueFrame(arg);
        }
        break;

        case CMD_VENC_DEQUEUE_FRAME:
        {
            Ret = VENC_Ioctl_DequeueFrame(arg);
        }
        break;

        case CMD_VENC_GET_CAP:
        {
            Ret = VENC_Ioctl_GetCapability(arg);
        }
        break;

        case CMD_VENC_GET_RC_TYPE:
        {
            Ret = VENC_Ioctl_GetRateControlType(arg);
        }
        break;

        case CMD_VENC_SET_RC_TYPE:
        {
            Ret = VENC_Ioctl_SetRateControlType(arg);
        }
        break;

        case CMD_VENC_GET_INPUT_FRMRATE_TYPE:
        {
            Ret = VENC_Ioctl_GetInFrmRateType(arg);
        }
        break;

        case CMD_VENC_SET_INPUT_FRMRATE_TYPE:
        {
            Ret = VENC_Ioctl_SetInFrmRateType(arg);
        }
        break;

        case CMD_VENC_GET_MSG:
        {
            Ret = VENC_Ioctl_GetMsg(arg);
        }
        break;

        case CMD_VENC_MMZ_MAP:
        {
            Ret = VENC_Ioctl_MmzMap(arg);
        }
        break;

        case CMD_VENC_MMZ_UMMAP:
        {
            Ret = VENC_Ioctl_MmzUmmap(arg);
        }
        break;

        case CMD_VENC_QUEUE_STREAM:                    //juse omxvenc use this api
        {
            Ret = VENC_Ioctl_QueueStream(arg);
        }
        break;

        case CMD_VENC_FLUSH_PORT:
        {
            Ret = VENC_Ioctl_FlushPort(arg);
        }
        break;

        default:
        {
            HI_ERR_VENC("venc cmd unknown:%x\n", cmd);
        }
        break;
    }

    return Ret;
}

static long VENC_DRV_Ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    long Ret;

    Ret = (long)HI_DRV_UserCopy(file->f_path.dentry->d_inode, file, cmd, arg, VENC_Ioctl);
    return Ret;
}

static struct file_operations VENC_FOPS =
{
    .owner          = THIS_MODULE,
    .open           = VENC_DRV_Open,
    .unlocked_ioctl = VENC_DRV_Ioctl,
    #ifdef CONFIG_COMPAT
    .compat_ioctl   = VENC_DRV_Ioctl,
    #endif
    .release        = VENC_DRV_Close,
};

/*****************************************************************************
 Prototype    : VENC_DRV_Suspend
 Description  : VENC module standby function
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
static int  venc_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    VENC_DRV_Suspend();

    return 0;
}

/*****************************************************************************
 Prototype    : VENC_DRV_Resume
 Description  : VENC module wake-up function
 Input        : None
 Output       : None
 Return Value : None
*****************************************************************************/
static int venc_pm_resume(PM_BASEDEV_S *pdev)
{
    VENC_DRV_Resume();

    return 0;
}

static PM_BASEOPS_S venc_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = venc_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = venc_pm_resume,
};

HI_S32 VENC_DRV_ModInit(HI_VOID)
{
    HI_U32 i;
    HI_S32 s32Ret = HI_FAILURE;
    const HI_U32 DevfsNameLen = 64;

    s32Ret = VENC_DRV_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_VENC("Init drv fail!\n");
        return HI_FAILURE;
    }

    snprintf(g_VencRegisterData.devfs_name, DevfsNameLen, "%s", UMAP_DEVNAME_VENC);
    g_VencRegisterData.fops   = &VENC_FOPS;
    g_VencRegisterData.minor  = UMAP_MIN_MINOR_VENC;
    g_VencRegisterData.owner  = THIS_MODULE;
    g_VencRegisterData.drvops = &venc_drvops;
    if (HI_DRV_DEV_Register(&g_VencRegisterData) < 0)
    {
        HI_FATAL_VENC("register VENC failed.\n");
        return HI_FAILURE;
    }

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        g_stVencChn[i].pWhichFile = NULL;
    }
    VENC_DRV_BoardDeinit();
    HI_INFO_VENC("register VENC successful.\n");

#ifdef MODULE
    HI_PRINT("Load hi_venc.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return 0;
}

HI_VOID VENC_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_VencRegisterData);
    VENC_DRV_Exit();

    return;
}

HI_VOID VENC_TimerFunc(HI_LENGTH_T value)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_FAILURE;
    VeduEfl_StatInfo_S StatInfo;
    VeduEfl_EncPara_S *pstEncChnPara = NULL;
    unsigned long flags;

    for (i = 0; i < HI_VENC_MAX_CHN; i++)
    {
        spin_lock_irqsave(&g_SendFrame_Lock[i], flags);

        if ((g_stVencChn[i].hVEncHandle != NULL) && (VENC_DRV_CheckChnStateSafe(i) == HI_TRUE))
        {
            s32Ret = VENC_DRV_EflQueryStatInfo(g_stVencChn[i].hVEncHandle, &StatInfo);
            if (HI_SUCCESS == s32Ret)
            {
                /* video encoder does frame rate control by this value */
                g_stVencChn[i].u32LastSecEncodedFps = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip
                                                     -StatInfo.ErrCfgSkip - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip
                                                     -StatInfo.TooFewBufferSkip - StatInfo.TooManyBitsSkip
                                                     -g_stVencChn[i].u32FrameNumLastEncoded;
                g_stVencChn[i].u32LastSecInputFps = StatInfo.GetFrameNumOK - g_stVencChn[i].u32FrameNumLastInput;
                g_stVencChn[i].u32LastSecKbps = StatInfo.StreamTotalByte - g_stVencChn[i].u32TotalByteLastEncoded;
                g_stVencChn[i].u32LastSecTryNum = StatInfo.GetFrameNumTry - g_stVencChn[i].u32LastTryNumTotal;
                g_stVencChn[i].u32LastSecOKNum = StatInfo.GetFrameNumOK - g_stVencChn[i].u32LastOKNumTotal;
                g_stVencChn[i].u32LastSecPutNum = StatInfo.PutFrameNumOK - g_stVencChn[i].u32LastPutNumTotal;

                g_stVencChn[i].u32LastSecStrmGetTryNum = StatInfo.GetStreamNumTry - g_stVencChn[i].u32LastStrmGetTryNumTotal;
                g_stVencChn[i].u32LastSecStrmGetOKNum = StatInfo.GetStreamNumOK - g_stVencChn[i].u32LastStrmGetOKNumTotal;
                g_stVencChn[i].u32LastSecStrmRlsTryNum = StatInfo.PutStreamNumTry - g_stVencChn[i].u32LastStrmRlsTryNumTotal;
                g_stVencChn[i].u32LastSecStrmRlsOKNum = StatInfo.PutStreamNumOK - g_stVencChn[i].u32LastStrmRlsOKNumTotal;

                /* save value for next calculation */
                g_stVencChn[i].u32FrameNumLastInput    = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32FrameNumLastEncoded  = StatInfo.GetFrameNumOK - StatInfo.QuickEncodeSkip - StatInfo.ErrCfgSkip
                                                       - StatInfo.FrmRcCtrlSkip - StatInfo.SamePTSSkip
                                                       - StatInfo.TooFewBufferSkip - StatInfo.TooManyBitsSkip ;
                g_stVencChn[i].u32TotalByteLastEncoded = StatInfo.StreamTotalByte;
                g_stVencChn[i].u32LastTryNumTotal      = StatInfo.GetFrameNumTry;
                g_stVencChn[i].u32LastOKNumTotal       = StatInfo.GetFrameNumOK;
                g_stVencChn[i].u32LastPutNumTotal      = StatInfo.PutFrameNumOK;

                g_stVencChn[i].u32LastStrmGetTryNumTotal = StatInfo.GetStreamNumTry;
                g_stVencChn[i].u32LastStrmGetOKNumTotal  = StatInfo.GetStreamNumOK;
                g_stVencChn[i].u32LastStrmRlsTryNumTotal = StatInfo.PutStreamNumTry;
                g_stVencChn[i].u32LastStrmRlsOKNumTotal  = StatInfo.PutStreamNumOK;

#if 1
                pstEncChnPara = (VeduEfl_EncPara_S *)g_stVencChn[i].hVEncHandle;
                D_VENC_UPDATA_2(pstEncChnPara->LastSecInputFrmRate,g_stVencChn[i].u32LastSecInputFps);
                pstEncChnPara->LastSecFrameCnt = 0;
                pstEncChnPara->bFrmRateSataError = 0;
#endif
            }
        }
        spin_unlock_irqrestore(&g_SendFrame_Lock[i], flags);
    }

    vencTimer.expires  = jiffies + (HZ);
    vencTimer.function = VENC_TimerFunc;
    add_timer(&vencTimer);
    return;
}





#ifdef MODULE
module_init(VENC_DRV_ModInit);
module_exit(VENC_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
