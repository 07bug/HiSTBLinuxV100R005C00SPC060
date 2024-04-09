/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_pvr_intf.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/04/27
  Description   :
  History       :
  1.Date        : 2010/04/27
    Author      : sdk
    Modification: Created file

*******************************************************************************/
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/errno.h>
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_common.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "hi_kernel_adapt.h"
#include "pvr_debug.h"
#include "drv_pvr_ext.h"
#include "hi_drv_pvr.h"
#include "hi_error_mpi.h"
#ifdef HI_TEE_PVR_SUPPORT
#include "drv_pvr_tee_func.h"
#endif

#define PVR_NAME                "HI_PVR"

static UMAP_DEVICE_S            PvrDev;
static struct file_operations   PvrFileOps;
static PVR_CHAN_INFO_S          PvrPlayChanInfo[PVR_PLAY_MAX_CHN_NUM];
static PVR_CHAN_INFO_S          PvrRecChanInfo[PVR_REC_MAX_CHN_NUM];
static HI_U32                   PvrDecodeAbility;

HI_DECLARE_MUTEX(PvrMutex);

static HI_S32 PVR_CreatePlay(HI_U32 *pChanId)
{
    HI_U32 i = 0;

    for (i = 0; i < PVR_PLAY_MAX_CHN_NUM; i++)
    {
        if (HI_FALSE == PvrPlayChanInfo[i].bUsed)
        {
            PvrPlayChanInfo[i].bUsed = HI_TRUE;
            PvrPlayChanInfo[i].owner = task_tgid_nr(current);
            PvrPlayChanInfo[i].u32DeCodeAbilityUsed = 0;
            *pChanId = i;
            return HI_SUCCESS;
        }
    }

    HI_ERR_PVR("Create Play Chanel failed!\n");
    return HI_ERR_PVR_NO_CHN_LEFT;
}

static HI_S32 PVR_DestroyPlay(const HI_U32 ChanId)
{
    if (ChanId >= PVR_PLAY_MAX_CHN_NUM)
    {
        HI_ERR_PVR("invalid ChanId(%u)! \n", ChanId);
        return HI_FAILURE;
    }

    if (HI_TRUE == PvrPlayChanInfo[ChanId].bUsed)
    {
        PvrPlayChanInfo[ChanId].bUsed = HI_FALSE;
        PvrPlayChanInfo[ChanId].owner = 0;
        PvrDecodeAbility += PvrPlayChanInfo[ChanId].u32DeCodeAbilityUsed;
        PvrPlayChanInfo[ChanId].u32DeCodeAbilityUsed = 0;
    }
    else
    {
        HI_WARN_PVR("Play Chanel(%u) has already released! bUsed: %d\n", ChanId, PvrPlayChanInfo[ChanId].bUsed);
    }

    return HI_SUCCESS;
}

static HI_S32 PVR_CreateRec(HI_U32 *pChanId)
{
    HI_U32 i = 0;

    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        if (HI_FALSE == PvrRecChanInfo[i].bUsed)
        {
            PvrRecChanInfo[i].bUsed = HI_TRUE;
            PvrRecChanInfo[i].owner = task_tgid_nr(current);
            PvrRecChanInfo[i].u32DeCodeAbilityUsed = 0;
            *pChanId = i;
            return HI_SUCCESS;
        }
    }

    HI_ERR_PVR("Create Rec Chanel failed!\n");
    return HI_ERR_PVR_NO_CHN_LEFT;
}

static HI_S32 PVR_DestroyRec(const HI_U32 ChanId)
{
    if (ChanId >= PVR_REC_MAX_CHN_NUM)
    {
        HI_ERR_PVR("invalid ChanId(%u)! \n", ChanId);
        return HI_FAILURE;
    }

    if (HI_TRUE == PvrRecChanInfo[ChanId].bUsed)
    {
        PvrRecChanInfo[ChanId].bUsed = HI_FALSE;
        PvrRecChanInfo[ChanId].owner = 0;
        PvrRecChanInfo[ChanId].u32DeCodeAbilityUsed = 0;
    }
    else
    {
        HI_WARN_PVR("Play Chanel(%u) has already released! bUsed: %d\n", ChanId, PvrRecChanInfo[ChanId].bUsed);
    }

    return HI_SUCCESS;
}

static HI_S32 PVR_AcquireDecodeAbility(struct file *file, PVR_DECODEABILITY_INFO_S *pstDecodeAbilityInfo)
{
    pid_t cPid = (pid_t)(unsigned long)file->private_data;

    if (pstDecodeAbilityInfo->u32ChnId >= PVR_PLAY_MAX_CHN_NUM)
    {
        HI_ERR_PVR("invalid ChanId(%u)! \n", pstDecodeAbilityInfo->u32ChnId);
        return HI_FAILURE;
    }

    if ((cPid == PvrPlayChanInfo[pstDecodeAbilityInfo->u32ChnId].owner) && (PvrDecodeAbility >= pstDecodeAbilityInfo->u32DeCodeAbilityValue))
    {
        PvrPlayChanInfo[pstDecodeAbilityInfo->u32ChnId].u32DeCodeAbilityUsed += pstDecodeAbilityInfo->u32DeCodeAbilityValue;
        PvrDecodeAbility -= pstDecodeAbilityInfo->u32DeCodeAbilityValue;
        return HI_SUCCESS;
    }

    HI_ERR_PVR("get DecodeAbility failed! need/surplus(%u/%u)\n", pstDecodeAbilityInfo->u32DeCodeAbilityValue, PvrDecodeAbility);
    return HI_FAILURE;
}

static HI_S32 PVR_ReleaseDecodeAbility(struct file *file, PVR_DECODEABILITY_INFO_S *pstDecodeAbilityInfo)
{
    pid_t cPid = (pid_t)(unsigned long)file->private_data;

    if (pstDecodeAbilityInfo->u32ChnId >= PVR_PLAY_MAX_CHN_NUM)
    {
        HI_ERR_PVR("invalid ChanId(%u)! \n", pstDecodeAbilityInfo->u32ChnId);
        return HI_FAILURE;
    }

    if ((cPid == PvrPlayChanInfo[pstDecodeAbilityInfo->u32ChnId].owner) && (pstDecodeAbilityInfo->u32DeCodeAbilityValue <= PvrPlayChanInfo[pstDecodeAbilityInfo->u32ChnId].u32DeCodeAbilityUsed))
    {
        PvrPlayChanInfo[pstDecodeAbilityInfo->u32ChnId].u32DeCodeAbilityUsed -= pstDecodeAbilityInfo->u32DeCodeAbilityValue;
        PvrDecodeAbility += pstDecodeAbilityInfo->u32DeCodeAbilityValue;
        return HI_SUCCESS;
    }

    HI_ERR_PVR("release DecodeAbility failed! release/surplus(%u/%u)\n", pstDecodeAbilityInfo->u32DeCodeAbilityValue, PvrDecodeAbility);
    return HI_FAILURE;
}

static HI_S32 PVR_Ioctl(struct inode *inode, struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret;

    ret = down_interruptible(&PvrMutex);

    switch (cmd)
    {
        case CMD_PVR_CREATE_PLAY_CHN:
        {
            ret = PVR_CreatePlay((HI_U32*)arg);

            break;
        }

        case CMD_PVR_DESTROY_PLAY_CHN:
        {
            ret = PVR_DestroyPlay(*((HI_U32*)arg));

            break;
        }

        case CMD_PVR_CREATE_REC_CHN:
        {
            ret = PVR_CreateRec((HI_U32*)arg);

            break;
        }

        case CMD_PVR_DESTROY_REC_CHN:
        {
            ret = PVR_DestroyRec(*((HI_U32*)arg));

            break;
        }

        case CMD_PVR_ACQUIRE_DECODE_ABILITY:
        {
            ret = PVR_AcquireDecodeAbility(file, arg);

            break;
        }

        case CMD_PVR_RELEASE_DECODE_ABILITY:
        {
            ret = PVR_ReleaseDecodeAbility(file, arg);

            break;
        }

        case CMD_PVR_GET_DECODE_ABILITY:
        {
            *((HI_U32*)arg) = PvrDecodeAbility;
            break;
        }
#ifdef HI_TEE_PVR_SUPPORT
        case CMD_PVR_TEE_REC_OPEN:
        case CMD_PVR_TEE_REC_CLOSE:
        case CMD_PVR_TEE_REC_COPY_REE_TEST:
        case CMD_PVR_TEE_REC_PROCESS_TS_DATA:
        case CMD_PVR_TEE_REC_GET_STATE:
        case CMD_PVR_TEE_REC_GET_ADDRINFO:
        case CMD_PVR_TEE_PLAY_COPY_FROM_REE:
        case CMD_PVR_TEE_PLAY_PROCESS_DATA:
            ret = PVR_TeecIoctl(inode, file, cmd, arg);
            break;
#endif
        default:
            ret = -ENOIOCTLCMD;
    }

    up(&PvrMutex);

    return ret;
}

static int PVR_DRV_Open(struct inode *inode, struct file *file)
{
#ifdef HI_TEE_PVR_SUPPORT
    HI_S32 ret = HI_SUCCESS;
#endif

    ((struct file *)file)->private_data = (void *)(unsigned long)task_tgid_nr(current);

#ifdef HI_TEE_PVR_SUPPORT
    ret = PVR_TeecInit();
    if (HI_SUCCESS != ret)
    {
        HI_PRINT("Initize the tee failed, ret = 0x%08x\n", ret);
        return ret;
    }
#endif

    return 0;
}

static int PVR_DRV_Close(struct inode *inode, struct file *file)
{
    HI_S32 ret;
    HI_U32 i;
    pid_t cPid = (pid_t)(unsigned long)file->private_data;

    ret = down_interruptible(&PvrMutex);

    for (i = 0; i < PVR_PLAY_MAX_CHN_NUM; i++)
    {
        if(cPid == PvrPlayChanInfo[i].owner)
        {
            (HI_VOID)PVR_DestroyPlay(i);
        }
    }

    for (i = 0; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        if(cPid == PvrRecChanInfo[i].owner)
        {
            (HI_VOID)PVR_DestroyRec(i);
        }
    }
#ifdef HI_TEE_PVR_SUPPORT
    PVR_TeeRelease(file);
    (HI_VOID)PVR_TeecDeInit();
#endif
    up(&PvrMutex);

    return 0;
}

static long PVR_DRV_Ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    return (long)HI_DRV_UserCopy(file->f_path.dentry->d_inode, file, cmd, arg, PVR_Ioctl);
}

HI_S32 PVR_DRV_ModInit(HI_VOID)
{
    HI_S32 ret;
    HI_U32 i;
    HI_CHIP_TYPE_E enChipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E ecChipVersion = HI_CHIP_VERSION_BUTT;

    ret = HI_DRV_MODULE_Register(HI_ID_PVR, PVR_NAME, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    PvrFileOps.owner            = THIS_MODULE;
    PvrFileOps.open             = PVR_DRV_Open;
    PvrFileOps.release          = PVR_DRV_Close;
    PvrFileOps.unlocked_ioctl   = PVR_DRV_Ioctl;
#ifdef CONFIG_COMPAT
    PvrFileOps.compat_ioctl     = PVR_DRV_Ioctl;
#endif

    strncpy(PvrDev.devfs_name, UMAP_DEVNAME_PVR, sizeof(UMAP_DEVNAME_PVR));
    PvrDev.minor  = UMAP_MIN_MINOR_PVR;
    PvrDev.owner  = THIS_MODULE;
    PvrDev.fops   = &PvrFileOps;
    PvrDev.drvops = HI_NULL;

    if (HI_DRV_DEV_Register(&PvrDev) < 0)
    {
        HI_FATAL_PVR("register failed\n");

        HI_DRV_MODULE_UnRegister(HI_ID_PVR);

        return HI_FAILURE;
    }

    for (i = 0 ; i < PVR_PLAY_MAX_CHN_NUM; i++)
    {
        PvrPlayChanInfo[i].bUsed = HI_FALSE;
        PvrPlayChanInfo[i].owner = 0;
        PvrPlayChanInfo[i].u32DeCodeAbilityUsed = 0;
    }

    for (i = 0 ; i < PVR_REC_MAX_CHN_NUM; i++)
    {
        PvrRecChanInfo[i].bUsed = HI_FALSE;
        PvrRecChanInfo[i].owner = 0;
        PvrRecChanInfo[i].u32DeCodeAbilityUsed = 0;
    }

    PvrDecodeAbility = PVR_PLAY_DECODE_ABILITY;
    HI_DRV_SYS_GetChipVersion(&enChipType, &ecChipVersion);
    if ((HI_CHIP_TYPE_HI3716M == enChipType) && (HI_CHIP_VERSION_V450 == ecChipVersion))
    {
        PvrDecodeAbility = 65*1920*1080;
    }
#ifdef MODULE
    HI_PRINT("Load hi_pvr.ko success.  \t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID PVR_DRV_ModExit(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&PvrDev);

    HI_DRV_MODULE_UnRegister(HI_ID_PVR);
}

#ifdef MODULE
module_init(PVR_DRV_ModInit);
module_exit(PVR_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

