/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name                 :   drv_aenc.c
  Version                   :   Initial Draft
  Author                    :   Hisilicon multimedia software group
  Created                   :   2006/01/23
  Last Modified             :
  Description               :
  Function List         :
  History               :
  1.Date                :   2010/03/11
    Author              :   sdk
    Modification        :   Created file

******************************************************************************/
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>

#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/seq_file.h>

#include "hi_drv_mmz.h"
#include "hi_drv_stat.h"
#include "hi_drv_sys.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_drv_file.h"

#include "hi_drv_aenc.h"

#include "hi_kernel_adapt.h"
#include "hi_drv_file.h"
#include "hi_drv_module.h"

#include "drv_aenc_ext.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

#define AENC_NAME "HI_AENC"

typedef struct
{
    HI_BOOL           bUsed;
    AENC_PROC_ITEM_S* psAencKernelAddr;
    MMZ_BUFFER_S      AencProcMmz;
    HI_CHAR           szProcMmzName[32];
} AENC_KADDR_S;

#ifdef HI_PROC_SUPPORT
typedef struct
{
    DRV_PROC_READ_FN  pfnReadProc;
    DRV_PROC_WRITE_FN pfnWriteProc;
} AENC_REGISTER_PARAM_S;

static AENC_REGISTER_PARAM_S s_stProcParam;
static HI_S32 AENC_RegProc(HI_U32 u32AencNum, AENC_REGISTER_PARAM_S* pstParam);
#endif

static AENC_KADDR_S g_sAencKAddrArray[AENC_INSTANCE_MAXNUM];
static UMAP_DEVICE_S g_sAencDevice;

HI_DECLARE_MUTEX(g_AencMutex);

static HI_VOID AENCResetVKaddrArray(HI_VOID)
{
    memset(g_sAencKAddrArray, 0, sizeof(AENC_KADDR_S) * AENC_INSTANCE_MAXNUM);
}

/* Register AENC Dev */
static HI_S32 AENCRegisterDevice(struct file_operations* fops, PM_BASEOPS_S* pm_ops)
{
    AENCResetVKaddrArray();

    /* register AENC Dev */
    snprintf(g_sAencDevice.devfs_name, sizeof(g_sAencDevice.devfs_name), "%s", UMAP_DEVNAME_AENC);
    g_sAencDevice.fops   = fops;
    g_sAencDevice.minor  = UMAP_MIN_MINOR_AENC;
    g_sAencDevice.owner  = THIS_MODULE;
    g_sAencDevice.drvops = pm_ops;
    if (HI_DRV_DEV_Register(&g_sAencDevice) < 0)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* Unregister AENC Dev */
static HI_VOID AENCUnregisterDevice(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_sAencDevice);
}

static HI_S32 AENC_DRV_Destory(struct file* filp)
{
    AENC_KADDR_S* psKAddrElem;

    psKAddrElem = (AENC_KADDR_S*)filp->private_data;
    if (!psKAddrElem)
    {
        return HI_SUCCESS;
    }

    if (psKAddrElem->bUsed != HI_TRUE)
    {
        return HI_FAILURE;
    }

#ifdef HI_PROC_SUPPORT
    {
        HI_U32 u32ChanId;
        HI_CHAR aszBuf[16];
        u32ChanId = (psKAddrElem->szProcMmzName[9] - '0') * 10 + (psKAddrElem->szProcMmzName[10] - '0');
        snprintf(aszBuf, sizeof(aszBuf), "aenc%02d", u32ChanId);
        HI_DRV_PROC_RemoveModule(aszBuf);
    }
#endif

    if (psKAddrElem->psAencKernelAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&psKAddrElem->AencProcMmz);
        psKAddrElem->psAencKernelAddr = HI_NULL;
    }

    psKAddrElem->bUsed = HI_FALSE;
    filp->private_data = HI_NULL;

    return HI_SUCCESS;
}

static HI_S32 AENC_DRV_Create(unsigned long arg, struct file* filp)
{
    HI_U32 i;
    HI_S32 s32Ret;
    AENC_KADDR_S* psKAddrElem;

    for (i = 0; i < AENC_INSTANCE_MAXNUM; i++)
    {
        if (g_sAencKAddrArray[i].bUsed == HI_FALSE)
        {
            break;
        }
    }

    if (i >= AENC_INSTANCE_MAXNUM)
    {
        return HI_FAILURE;
    }

    g_sAencKAddrArray[i].bUsed = HI_TRUE;
    g_sAencKAddrArray[i].psAencKernelAddr = HI_NULL;
    snprintf(g_sAencKAddrArray[i].szProcMmzName, sizeof(g_sAencKAddrArray[i].szProcMmzName), "%s%02d", "AENC_Proc", i);

#ifdef HI_PROC_SUPPORT
    AENC_RegProc(i, &s_stProcParam);
#endif

    psKAddrElem = &g_sAencKAddrArray[i];

    s32Ret = HI_DRV_MMZ_AllocAndMap(psKAddrElem->szProcMmzName, MMZ_OTHERS, sizeof(AENC_PROC_ITEM_S), 0, &psKAddrElem->AencProcMmz);
    if (HI_SUCCESS != s32Ret)
    {
        AENC_DRV_Destory(filp);
        return HI_FAILURE;
    }

    memset(psKAddrElem->AencProcMmz.pu8StartVirAddr, 0, sizeof(AENC_PROC_ITEM_S));
    psKAddrElem->psAencKernelAddr = (AENC_PROC_ITEM_S *)psKAddrElem->AencProcMmz.pu8StartVirAddr;
    psKAddrElem->psAencKernelAddr->enPcmCtrlState= AENC_CMD_CTRL_STOP;
    psKAddrElem->psAencKernelAddr->u32SavePcmCnt = 0;
    psKAddrElem->psAencKernelAddr->enEsCtrlState= AENC_CMD_CTRL_STOP;
    psKAddrElem->psAencKernelAddr->u32SaveEsCnt = 0;

    if (copy_to_user((void*)arg, &psKAddrElem->AencProcMmz.u32StartPhyAddr, sizeof(HI_U32)))
    {
        AENC_DRV_Destory(filp);
        return HI_FAILURE;
    }

    filp->private_data = (void*)psKAddrElem;
    return s32Ret;
}

static HI_S32 AENC_DRV_Open(struct inode* inode, struct file* filp)
{
    return HI_SUCCESS;
}

static HI_S32 AENC_DRV_Release(struct inode* inode, struct file* filp)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = down_interruptible(&g_AencMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AENC("lock g_AencMutex failed\n");
        return s32Ret;
    }

    s32Ret = AENC_DRV_Destory(filp);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AENC("AENC_DRV_Destory Failed!\n");
    }

    up(&g_AencMutex);
    return s32Ret;
}

static long AENC_DRV_Ioctl(struct file* filp, HI_U32 cmd, unsigned long arg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = down_interruptible(&g_AencMutex);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_AENC("lock g_AencMutex failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    switch (cmd)
    {
        case DRV_AENC_PROC_INIT:
        {
            s32Ret = AENC_DRV_Create(arg, filp);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_AENC("AENC_DRV_Create failed(0x%x)\n", s32Ret);
            }
            break;
        }

        case DRV_AENC_PROC_EXIT:
        {
            s32Ret = AENC_DRV_Destory(filp);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_AENC("AENC_DRV_Destory failed(0x%x)\n", s32Ret);
            }
            break;
        }

        default:
        {
            s32Ret = HI_FAILURE;
            HI_ERR_AENC("Invalid cmd!\n");
            break;
        }
    }

    up(&g_AencMutex);
    return s32Ret;
}

static struct file_operations aenc_fops =
{
    .owner          = THIS_MODULE,
    .open           = AENC_DRV_Open,
    .unlocked_ioctl = AENC_DRV_Ioctl,
    .release        = AENC_DRV_Release,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = AENC_DRV_Ioctl,
#endif
};

static int aenc_pm_suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    return 0;
}

static int aenc_pm_resume(PM_BASEDEV_S* pdev)
{
    return 0;
}

static PM_BASEOPS_S aenc_pm_ops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = aenc_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = aenc_pm_resume,
};

#ifdef HI_PROC_SUPPORT
static  HI_CHAR* AENC_DRV_ReadAttachname(AENC_PROC_ITEM_S* param)
{
    HI_CHAR *AencName[ANEC_SOURCE_BUTT + 1] =
    {
        "Ai",
        "Cast",
        "Track",
        "None",
    };

    return AencName[param->stAttach.eType];
}

static HI_S32 AENC_DRV_Proc(struct seq_file *p, HI_U32 u32ChNum)
{
    HI_U32 u32BufPercent, u32FramePercent, u32FrameFullNum;
    HI_U32 u32DataSize = 0;
    AENC_PROC_ITEM_S* tmp = NULL;
    HI_CHAR* attachname;

    PROC_PRINT(p, "\n----------------------- AENC[%02d] State --------------------------\n", u32ChNum);

    if (g_sAencKAddrArray[u32ChNum].bUsed == HI_FALSE)
    {
        PROC_PRINT(p, "AENC[%02d] not open\n", u32ChNum);
        return HI_FAILURE;
    }

    if (g_sAencKAddrArray[u32ChNum].psAencKernelAddr == NULL)
    {
        PROC_PRINT(p, "AENC[%02d] PROC not INIT\n", u32ChNum);
        return HI_FAILURE;
    }

    tmp = (AENC_PROC_ITEM_S*)g_sAencKAddrArray[u32ChNum].psAencKernelAddr;
    if (tmp->u32InBufSize)
    {
        if (tmp->tInBufWrite >= tmp->tInBufRead)
        {
            u32DataSize = tmp->tInBufWrite - tmp->tInBufRead;
        }
        else
        {
            u32DataSize = tmp->u32InBufSize + tmp->tInBufWrite - tmp->tInBufRead;
        }
        u32BufPercent = u32DataSize * 100 / tmp->u32InBufSize;
    }
    else
    {
        u32BufPercent = 0;
    }

    if (tmp->u32OutFrameNum)
    {
        if (tmp->u32OutFrameWIdx >= tmp->u32OutFrameRIdx)
        {
            u32FramePercent = (tmp->u32OutFrameWIdx - tmp->u32OutFrameRIdx) * 100 / tmp->u32OutFrameNum;
            u32FrameFullNum = tmp->u32OutFrameWIdx - tmp->u32OutFrameRIdx;
        }
        else
        {
            u32FramePercent = (tmp->u32OutFrameNum - tmp->u32OutFrameRIdx + tmp->u32OutFrameWIdx) * 100 / tmp->u32OutFrameNum;
            u32FrameFullNum = tmp->u32OutFrameNum - tmp->u32OutFrameRIdx + tmp->u32OutFrameWIdx;
        }
    }
    else
    {
        u32FramePercent = 0;
        u32FrameFullNum = 0;
    }

    attachname = AENC_DRV_ReadAttachname(tmp);

    PROC_PRINT(p,
                "WorkStatus                           :%s\n"
                "Codec ID                             :0x%x\n"
                "Description                          :%s\n"
                "Sample Rate                          :%u\n"
                "Channels                             :%u\n"
                "BitWidth                             :%u\n",
                (tmp->bAencWorkEnable == HI_TRUE) ? "start" : "stop",
                tmp->u32CodecID,
                tmp->szCodecType,
                tmp->u32SampleRate,
                tmp->u32Channels,
                tmp->u32BitWidth);

    if (!strcasecmp("None", attachname))
    {
        PROC_PRINT(p, "AttachSource                         :%s\n", attachname);
    }
    else
    {
        PROC_PRINT(p, "AttachSource                         :%s%02d\n", attachname, (tmp->stAttach.hSource & 0xff));
    }

    PROC_PRINT(p,
                "\nTryEncodeTimes                       :%u\n"
                "EncodeFrameNum(Total/Error)          :%u/%u\n"
                "FrameBuf(Total/Use/Percent)(Bytes)   :%u/%u/%u%%\n"
                "StreamBuf(Total/Use/Percent)         :%u/%u/%u%%\n"
                "SendFrame(Try/OK)                    :%u/%u\n"
                "ReceiveStream(Try/OK)                :%u/%u\n"
                "ReleaseStream(Try/OK)                :%u/%u\n\n",
                tmp->u32DbgTryEncodeCount,
                tmp->u32EncFrame,
                tmp->u32ErrFrame,
                tmp->u32InBufSize,
                u32DataSize,
                u32BufPercent,
                tmp->u32OutFrameNum,
                u32FrameFullNum,
                u32FramePercent,
                tmp->u32DbgSendBufCount_Try,
                tmp->u32DbgSendBufCount,
                tmp->u32DbgReceiveStreamCount_Try,
                tmp->u32DbgReceiveStreamCount,
                tmp->u32DbgReleaseStreamCount_Try,
                tmp->u32DbgReleaseStreamCount);

    return HI_SUCCESS;
}

#define AENC_DEBUG_SHOW_HELP(u32ChNum) \
    do                                                         \
    {                                                          \
        HI_DRV_PROC_EchoHelper("\nfunction: save pcm data before audio encode\n"); \
        HI_DRV_PROC_EchoHelper("commad:   echo save_pcm start|stop > /proc/msp/aenc%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("example:  echo save_pcm start > /proc/msp/aenc%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("\nfunction: save es data after audio encode \n"); \
        HI_DRV_PROC_EchoHelper("commad:   echo save_es start|stop > /proc/msp/aenc%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("example:  echo save_es start > /proc/msp/aenc%02d\n\n", u32ChNum); \
    } while (0)

#define AENC_STRING_SKIP_BLANK(str)            \
    while (str[0] == ' ')      \
    {                                  \
        (str)++;                    \
    }

#define AENC_STRING_SKIP_NON_BLANK(str) \
    while (str[0] != ' ')      \
    {                                  \
        (str)++;                    \
    }

static HI_S32 AENC_DRV_ReadProc(struct seq_file* p, HI_VOID* v)
{
    HI_U32 u32ChNum;
    DRV_PROC_ITEM_S* pstProcItem;

    pstProcItem = p->private;

    if (HI_NULL == pstProcItem)
    {
        HI_ERR_AENC("the proc item pointer of aenc is NULL\n");
        return HI_FAILURE;
    }

    /* sizeof("aenc") is 4 */
    u32ChNum = (pstProcItem->entry_name[4] - '0') * 10 + (pstProcItem->entry_name[5] - '0');
    if (u32ChNum >= AENC_INSTANCE_MAXNUM)
    {
        PROC_PRINT(p, "Invalid Aenc ID:%d.\n", u32ChNum);
        return HI_FAILURE;
    }

    AENC_DRV_Proc(p, u32ChNum);

    return HI_SUCCESS;
}

#define  AENC_PATH_NAME_MAXLEN  256
#define  AENC_FILE_NAME_MAXLEN  256

static HI_S32 AENC_DRV_WriteProc(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
    HI_U32 u32ChNum;
    AENC_CMD_SAVE_E enSaveCmd;
    HI_CHAR szBuf[256] = {0};
    HI_CHAR* pcBuf = szBuf;
    HI_CHAR* pcStartCmd = "start";
    HI_CHAR* pcStopCmd = "stop";
    HI_CHAR* pcSavePcmCmd = "save_pcm";
    HI_CHAR* pcSaveEsCmd = "save_es";
    HI_CHAR* pcHelpCmd = "help";
    struct seq_file* p = file->private_data;
    AENC_PROC_ITEM_S* pstAencProc;
    DRV_PROC_ITEM_S* pstProcItem = p->private;

    if (copy_from_user(szBuf, buf, count < sizeof(szBuf) - 1 ? count : sizeof(szBuf) - 1))
    {
        HI_ERR_AENC("copy from user failed\n");
        return HI_FAILURE;
    }

    u32ChNum = (pstProcItem->entry_name[4] - '0') * 10 + (pstProcItem->entry_name[5] - '0');
    if (u32ChNum >= AENC_INSTANCE_MAXNUM)
    {
        HI_ERR_AENC("Invalid Aenc ID:%02d.\n", u32ChNum);
        goto SAVE_CMD_FAULT;
    }

    if (g_sAencKAddrArray[u32ChNum].bUsed == HI_FALSE)
    {
        HI_ERR_AENC("AENC[%02d] not open\n", u32ChNum);
        return HI_FAILURE;
    }

    if (g_sAencKAddrArray[u32ChNum].psAencKernelAddr == NULL)
    {
        HI_ERR_AENC("AENC[%02d] PROC not INIT\n", u32ChNum);
        return HI_FAILURE;
    }

    pstAencProc = (AENC_PROC_ITEM_S*)g_sAencKAddrArray[u32ChNum].psAencKernelAddr;
    AENC_STRING_SKIP_BLANK(pcBuf);

    if (strstr(pcBuf, pcSavePcmCmd))
    {
        enSaveCmd = AENC_CMD_PROC_SAVE_PCM;
        pcBuf += strlen(pcSavePcmCmd);
    }
    else if (strstr(pcBuf, pcSaveEsCmd))
    {
        enSaveCmd = AENC_CMD_PROC_SAVE_ES;
        pcBuf += strlen(pcSaveEsCmd);
    }
    else if (strstr(pcBuf, pcHelpCmd))
    {
        AENC_DEBUG_SHOW_HELP(u32ChNum);
        return count;
    }
    else
    {
        goto SAVE_CMD_FAULT;
    }

    AENC_STRING_SKIP_BLANK(pcBuf);

    if (strstr(pcBuf, pcStartCmd))
    {
        if (HI_SUCCESS != HI_DRV_FILE_GetStorePath(pstAencProc->filePath, AENC_PATH_NAME_MAXLEN))
        {
            HI_ERR_AENC("get store path failed\n");
            return HI_FAILURE;
        }

        if (enSaveCmd == AENC_CMD_PROC_SAVE_PCM)
        {
            if (pstAencProc->enPcmCtrlState != AENC_CMD_CTRL_START)
            {
                snprintf(pstAencProc->filePath, sizeof(pstAencProc->filePath), "%s/aenc%02d_%d.pcm", pstAencProc->filePath, u32ChNum, pstAencProc->u32SavePcmCnt);
                pstAencProc->u32SavePcmCnt++;
                pstAencProc->enPcmCtrlState = AENC_CMD_CTRL_START;

                HI_DRV_PROC_EchoHelper("Started saving aenc pcm data to %s\n", pstAencProc->filePath);
            }
        }
        else if (enSaveCmd == AENC_CMD_PROC_SAVE_ES)
        {
            if (pstAencProc->enEsCtrlState != AENC_CMD_CTRL_START)
            {
                snprintf(pstAencProc->filePath, sizeof(pstAencProc->filePath), "%s/aenc%02d_%d.es", pstAencProc->filePath, u32ChNum, pstAencProc->u32SaveEsCnt);
                pstAencProc->u32SaveEsCnt++;
                pstAencProc->enEsCtrlState = AENC_CMD_CTRL_START;

                HI_DRV_PROC_EchoHelper("Started saving aenc es data to %s\n", pstAencProc->filePath);
            }
        }
    }
    else if (strstr(pcBuf, pcStopCmd))
    {
        if (enSaveCmd == AENC_CMD_PROC_SAVE_PCM)
        {
            pstAencProc->enPcmCtrlState = AENC_CMD_CTRL_STOP;
        }
        else if (enSaveCmd == AENC_CMD_PROC_SAVE_ES)
        {
             pstAencProc->enEsCtrlState = AENC_CMD_CTRL_STOP;
        }
    }
    else
    {
        goto SAVE_CMD_FAULT;
    }

    return count;

SAVE_CMD_FAULT:
    HI_ERR_AENC("proc cmd is fault\n");
    AENC_DEBUG_SHOW_HELP(u32ChNum);
    return HI_FAILURE;
}

static AENC_REGISTER_PARAM_S s_stProcParam =
{
    .pfnReadProc  = AENC_DRV_ReadProc,
    .pfnWriteProc = AENC_DRV_WriteProc,
};

static HI_S32 AENC_RegProc(HI_U32 u32AencNum, AENC_REGISTER_PARAM_S* pstParam)
{
    HI_CHAR aszBuf[16] = {0};
    DRV_PROC_ITEM_S* pProcItem;

    /* Check parameters */
    if (HI_NULL == pstParam)
    {
        HI_ERR_AENC("the parameter pointer of aenc register is NULL\n");
        return HI_FAILURE;
    }

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), "aenc%02d", u32AencNum);
    pProcItem = HI_DRV_PROC_AddModule(aszBuf, HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_FATAL_AENC("Create Aenc proc entry fail!\n");
        return HI_FAILURE;
    }

    /* Set functions */
    pProcItem->read  = pstParam->pfnReadProc;
    pProcItem->write = pstParam->pfnWriteProc;

    HI_INFO_AENC("Create Aenc proc entry OK!\n");
    return HI_SUCCESS;
}
#endif

static HI_S32 HI_DRV_AENC_Init(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_AENC, AENC_NAME, (HI_VOID*)HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_AENC("HI_DRV_MODULE_Register HI_ID_AENC failed\n");
    }

    return s32Ret;
}

static HI_VOID HI_DRV_AENC_DeInit(HI_VOID)
{
    HI_DRV_MODULE_UnRegister(HI_ID_AENC);
}

HI_S32 AENC_DRV_ModInit(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_DRV_AENC_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_AENC("HI_DRV_AENC_Init failed\n");
        return s32Ret;
    }

    /*register AENC device*/
    AENCRegisterDevice(&aenc_fops, &aenc_pm_ops);

#ifdef MODULE
    HI_PRINT("Load hi_aenc.ko success.  \t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID AENC_DRV_ModExit(HI_VOID)
{
    AENCUnregisterDevice();
    HI_DRV_AENC_DeInit();
}

#ifdef MODULE
module_init(AENC_DRV_ModInit);
module_exit(AENC_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
