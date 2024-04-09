/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name                 : adec_intf.c
  Version                   : Initial Draft
  Author                    : Hisilicon multimedia software group
  Created                   : 2006/01/23
  Last Modified             :
  Description               :
  Function List             :So Much
  History                   :
  1.Date                    : 2006/01/23
    Author                  : sdk
    Modification            : Created file

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
#ifdef HI_PROC_SUPPORT
#include "hi_drv_proc.h"
#endif
#include "hi_error_mpi.h"
#include "drv_adec_ext.h"
#include "hi_drv_adec.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_file.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef struct hiADEC_KADDR_S
{
    HI_BOOL            bUsed;
    ADEC_PROC_ITEM_S*  psAdecKernelAddr;
    MMZ_BUFFER_S       AdecProcMmz;
    HI_CHAR            szProcMmzName[32];
} ADEC_KADDR_S;

static ADEC_KADDR_S g_sAdecKAddrArray[ADEC_INSTANCE_MAXNUM];
static UMAP_DEVICE_S g_sAdecDevice;
HI_DECLARE_MUTEX(g_AdecMutex);

#ifdef HI_PROC_SUPPORT
typedef struct tagAdec_REGISTER_PARAM_S
{
    DRV_PROC_READ_FN  pfnReadProc;
    DRV_PROC_WRITE_FN pfnWriteProc;
} ADEC_REGISTER_PARAM_S;

static ADEC_REGISTER_PARAM_S s_stProcParam;
static HI_S32 ADEC_RegProc(HI_U32 u32AdecNum, ADEC_REGISTER_PARAM_S* pstParam);

static HI_S32 ADECConvertSampleRate(HI_UNF_SAMPLE_RATE_E enSampleRate)
{
    return (HI_S32)enSampleRate;
}
#endif

static HI_VOID ADECResetVKaddrArray(HI_VOID)
{
    HI_U32 i;

    for (i = 0; i < ADEC_INSTANCE_MAXNUM; i++)
    {
        g_sAdecKAddrArray[i].bUsed = HI_FALSE;
        g_sAdecKAddrArray[i].psAdecKernelAddr = NULL;
    }
}

/* Register adec Dev */
static HI_S32 ADECRegisterDevice(struct file_operations* drvFops, PM_BASEOPS_S* drvops)
{
    ADECResetVKaddrArray();

    /*register adec Dev*/
    snprintf(g_sAdecDevice.devfs_name, sizeof(g_sAdecDevice.devfs_name), "%s", UMAP_DEVNAME_ADEC);
    g_sAdecDevice.fops  = drvFops;
    g_sAdecDevice.minor = UMAP_MIN_MINOR_ADEC;
    g_sAdecDevice.owner  = THIS_MODULE;
    g_sAdecDevice.drvops = drvops;
    if (HI_DRV_DEV_Register(&g_sAdecDevice) < 0)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* Unregister adec Dev */
static HI_VOID ADECUnregisterDevice(HI_VOID)
{
    HI_DRV_DEV_UnRegister(&g_sAdecDevice);
}

static HI_S32 ADEC_DRV_Destory(struct file* filp)
{
    ADEC_KADDR_S  *psKAddrElem = HI_NULL;

    psKAddrElem = (ADEC_KADDR_S *)filp->private_data;
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
        snprintf(aszBuf, sizeof(aszBuf), "adec%02d", u32ChanId);
        HI_DRV_PROC_RemoveModule(aszBuf);
    }
#endif

    if (psKAddrElem->psAdecKernelAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&psKAddrElem->AdecProcMmz);
        psKAddrElem->psAdecKernelAddr = HI_NULL;
    }

    psKAddrElem->bUsed = HI_FALSE;
    filp->private_data = HI_NULL;

    return HI_SUCCESS;
}

static HI_S32 ADEC_DRV_Create(unsigned long arg, struct file* filp)
{
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    ADEC_KADDR_S *psKAddrElem;

    for (i = 0;  i < ADEC_INSTANCE_MAXNUM;  i++)
    {
        if (g_sAdecKAddrArray[i].bUsed == HI_FALSE)
        {
            break;
        }
    }

    if (i >= ADEC_INSTANCE_MAXNUM)
    {
        return HI_FAILURE;
    }

    g_sAdecKAddrArray[i].bUsed = HI_TRUE;
    g_sAdecKAddrArray[i].psAdecKernelAddr = HI_NULL;
    snprintf(g_sAdecKAddrArray[i].szProcMmzName, sizeof(g_sAdecKAddrArray[i].szProcMmzName), "%s%02d", "ADEC_Proc", i);

#ifdef HI_PROC_SUPPORT
    ADEC_RegProc(i, &s_stProcParam);
#endif

    psKAddrElem = &g_sAdecKAddrArray[i];

    s32Ret = HI_DRV_MMZ_AllocAndMap(psKAddrElem->szProcMmzName, MMZ_OTHERS, sizeof(ADEC_PROC_ITEM_S), 0, &psKAddrElem->AdecProcMmz);
    if (HI_SUCCESS != s32Ret)
    {
        ADEC_DRV_Destory(filp);
        return HI_FAILURE;
    }

    psKAddrElem->psAdecKernelAddr = (ADEC_PROC_ITEM_S *)psKAddrElem->AdecProcMmz.pu8StartVirAddr;
    psKAddrElem->psAdecKernelAddr->enPcmCtrlState= ADEC_CMD_CTRL_STOP;
    psKAddrElem->psAdecKernelAddr->u32SavePcmCnt = 0;
    psKAddrElem->psAdecKernelAddr->enEsCtrlState= ADEC_CMD_CTRL_STOP;
    psKAddrElem->psAdecKernelAddr->u32SaveEsCnt = 0;

    if(copy_to_user((void*)arg, &psKAddrElem->AdecProcMmz.u32StartPhyAddr, sizeof(HI_U32)))
    {
        ADEC_DRV_Destory(filp);
        return HI_FAILURE;
    }

    filp->private_data = (void*)psKAddrElem;
    return s32Ret;
}

static HI_S32 ADEC_DRV_Open(struct inode* inode, struct file* filp)
{
    return HI_SUCCESS;
}

static HI_S32 ADEC_DRV_Release(struct inode* inode, struct file* filp)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = down_interruptible(&g_AdecMutex);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_ADEC("lock g_AdecMutex failed\n");
        return s32Ret;
    }

    s32Ret = ADEC_DRV_Destory(filp);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_ADEC("ADEC_DRV_Destory Failed!\n");
    }

    up(&g_AdecMutex);
    return s32Ret;
}

static long ADEC_DRV_Ioctl(struct file* filp, HI_U32 cmd, unsigned long arg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = down_interruptible(&g_AdecMutex);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADEC("lock g_AdecMutex failed(0x%x)\n", s32Ret);
        return s32Ret;
    }

    switch (cmd)
    {
        case DRV_ADEC_PROC_INIT:
        {
            s32Ret = ADEC_DRV_Create(arg, filp);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_ADEC("ADEC_DRV_Create Failed!\n");
            }
            break;
        }

        case DRV_ADEC_PROC_EXIT:
        {
            s32Ret = ADEC_DRV_Destory(filp);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_ADEC("ADEC_DRV_Destory Failed!\n");
            }
            break;
        }

        default:
        {
            s32Ret = HI_FAILURE;
            HI_ERR_ADEC("Invalid cmd!\n");
            break;
        }
    }

    up(&g_AdecMutex);
    return s32Ret;
}

static struct file_operations ADEC_DRV_Fops =
{
    .owner          = THIS_MODULE,
    .open           = ADEC_DRV_Open,
    .unlocked_ioctl = ADEC_DRV_Ioctl,
    .release        = ADEC_DRV_Release,
#ifdef CONFIG_COMPAT
    .compat_ioctl   = ADEC_DRV_Ioctl,
#endif
};

#ifdef HI_PROC_SUPPORT
static HI_S32 ADEC_DRV_Proc(struct seq_file* p, HI_U32  u32ChNum)
{
    HI_U32 u32BufPercent, u32FramePercent, u32FrameFullNum, u32DataSize;
    ADEC_PROC_ITEM_S* tmp = NULL;
    DRV_PROC_ITEM_S*  pProcItem;

    pProcItem = p->private;

    PROC_PRINT(p, "\n--------------------------- ADEC[%02d] State --------------------------\n\n",u32ChNum);

    if (g_sAdecKAddrArray[u32ChNum].bUsed == HI_FALSE)
    {
        PROC_PRINT(p, "  ADEC[%02d] not open\n", u32ChNum);
        return HI_SUCCESS;
    }

    if (g_sAdecKAddrArray[u32ChNum].psAdecKernelAddr == NULL)
    {
        PROC_PRINT(p, "  ADEC[%02d] PROC not INIT\n", u32ChNum);
        return HI_SUCCESS;
    }

    tmp = (ADEC_PROC_ITEM_S*)g_sAdecKAddrArray[u32ChNum].psAdecKernelAddr;
    if (tmp->u32BufSize)
    {
        if (tmp->u32BufWrite >= tmp->s32BufRead)
        {
            u32DataSize = (tmp->u32BufWrite - tmp->s32BufRead);
        }
        else
        {
            u32DataSize = (tmp->u32BufSize - tmp->s32BufRead) + tmp->u32BufWrite;
        }
        u32BufPercent = u32DataSize * 100 / tmp->u32BufSize;
    }
    else
    {
        u32BufPercent = 0;
        u32DataSize = 0;
    }

    if (tmp->u32FrameSize)
    {
        if (tmp->u32FrameWrite >= tmp->u32FrameRead)
        {
            u32FramePercent = (tmp->u32FrameWrite - tmp->u32FrameRead) * 100 / tmp->u32FrameSize;
            u32FrameFullNum = tmp->u32FrameWrite - tmp->u32FrameRead;
        }
        else
        {
            u32FramePercent = ((tmp->u32FrameSize - tmp->u32FrameRead) + tmp->u32FrameWrite) * 100 / tmp->u32FrameSize;
            u32FrameFullNum = tmp->u32FrameSize - tmp->u32FrameRead + tmp->u32FrameWrite;
        }
    }
    else
    {
        u32FramePercent = 0;
        u32FrameFullNum = 0;
    }

    PROC_PRINT(p,
               "WorkState                              :%s\n"
               "CodecID                                :0x%x\n"
               "DecoderName                            :%s\n"
               "Description                            :%s\n"
               "*DecodeThreadID                        :%d\n"
               "Volume                                 :%d\n"
               "SampleRate                             :%d\n"
               "BitWidth                               :%d\n"
               "Channels                               :%d\n"
               "*PcmSamplesPerFrame                    :%d\n"
               "*BitsBytePerFrame                      :0x%x\n"
               "StreamFormat                           :%s\n\n"
               "*TryDecodetimes                        :%u\n"
               "FrameNum(Total/Error)                  :%d/%d\n"
               "FrameUnsupportNum                      :%d\n"
               "StreamCorruptNum                       :%d\n"
               "StreamBuf(Total/Use/Percent)(Bytes)    :%u/%d/%u%%\n"
               "StreamBuf(readPos/writePos)            :0x%x/0x%x\n"
               "OutFrameBuf(Total/Use/Percent)         :%u/%u/%u%%\n"
               "GetBuffer(Try/OK)                      :%u/%u\n"
               "PutBuffer(Try/OK)                      :%u/%u\n"
               "SendStream(Try/OK)                     :%u/%u\n"
               "ReceiveFrame(Try/OK)                   :%u/%u\n"
               "PtsLostNum                             :%d\n"
               "*DecodeThreadExecTimeOutCnt            :%u\n"
               "*DecodeThreadScheTimeOutCnt            :%u\n"
               "*DecodeThreadSleepTimeMS               :%d\n"
               "AdecDelayMS                            :%d\n\n",
               (tmp->bAdecWorkEnable == HI_TRUE) ? "start" : "stop",
               tmp->u32CodecID,
               tmp->szCodecType,
               tmp->szCodecDescription,
               tmp->u32ThreadId, //verify
               tmp->u32Volume,
               (ADECConvertSampleRate(tmp->enSampleRate)),
               tmp->enBitWidth,
               tmp->u32OutChannels,
               tmp->u32PcmSamplesPerFrame,
               tmp->u32BitsOutBytesPerFrame,
               (tmp->enFmt == HI_TRUE) ? "packet" : "non-packet",
               tmp->u32DbgTryDecodeCount,
               tmp->u32FramnNm,
               (HI_S32)tmp->u32ErrFrameNum,
               tmp->u32CodecUnsupportNum,
               tmp->u32StreamCorruptNum,
               tmp->u32BufSize,
               u32DataSize,
               u32BufPercent,
               tmp->s32BufRead,
               tmp->u32BufWrite,
               tmp->u32FrameSize,
               u32FrameFullNum,
               u32FramePercent,
               tmp->u32DbgGetBufCount_Try,
               tmp->u32DbgGetBufCount,
               tmp->u32DbgPutBufCount_Try,
               tmp->u32DbgPutBufCount,
               tmp->u32DbgSendStraemCount_Try,
               tmp->u32DbgSendStraemCount,
               tmp->u32DbgReceiveFrameCount_Try,
               tmp->u32DbgReceiveFrameCount,
               tmp->u32PtsLost,
               tmp->ThreadExeTimeOutCnt,
               tmp->ThreadScheTimeOutCnt,
               tmp->u32AdecSystemSleepTime,
               tmp->u32AdecDelayMS);

    return HI_SUCCESS;
}
#endif

static int adec_pm_suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
    int ret;
    ret = down_trylock(&g_AdecMutex);
    if (ret)
    {
        HI_FATAL_ADEC("lock err!\n");
        return -1;
    }

    up(&g_AdecMutex);
    HI_PRINT("ADEC suspend OK\n");
    return 0;
}

static int adec_pm_resume(PM_BASEDEV_S* pdev)
{
    HI_PRINT("ADEC resume OK\n");
    return 0;
}

static PM_BASEOPS_S adec_drvops =
{
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = adec_pm_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = adec_pm_resume,
};

#ifdef HI_PROC_SUPPORT
#define ADEC_DEBUG_SHOW_HELP(u32ChNum) \
    do                                                         \
    {                                                          \
        HI_DRV_PROC_EchoHelper("\nfunction: save es data before audio decode\n"); \
        HI_DRV_PROC_EchoHelper("commad:   echo save_es start|stop > /proc/msp/adec%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("example:  echo save_es start > /proc/msp/adec%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("\nfunction: save pcm data after audio decode \n"); \
        HI_DRV_PROC_EchoHelper("commad:   echo save_pcm start|stop > /proc/msp/adec%02d\n", u32ChNum); \
        HI_DRV_PROC_EchoHelper("example:  echo save_pcm start > /proc/msp/adec%02d\n\n", u32ChNum); \
    } while (0)

#define ADEC_STRING_SKIP_BLANK(str)            \
    while (str[0] == ' ')      \
    {                                  \
        (str)++;                    \
    }

#define ADEC_STRING_SKIP_NON_BLANK(str) \
    while (str[0] != ' ')      \
    {                                  \
        (str)++;                    \
    }

static HI_S32 ADEC_DRV_ReadProc( struct seq_file* p, HI_VOID* v )
{
    HI_U32 u32ChNum;
    DRV_PROC_ITEM_S* pstProcItem;

    pstProcItem = p->private;

    if (HI_NULL == pstProcItem)
    {
        HI_ERR_ADEC("the proc item pointer of adec  is NULL\n");
        return HI_FAILURE;
    }

    /*sizeof("adec") is 4*/
    u32ChNum = (pstProcItem->entry_name[4] - '0') * 10 + (pstProcItem->entry_name[5] - '0');
    if (u32ChNum >= ADEC_INSTANCE_MAXNUM)
    {
        PROC_PRINT(p, "Invalid Adec ID:%d.\n", u32ChNum);
        return HI_FAILURE;
    }

    ADEC_DRV_Proc(p, u32ChNum);

    return HI_SUCCESS;
}

#define  ADEC_PATH_NAME_MAXLEN  256
#define  ADEC_FILE_NAME_MAXLEN  256

static HI_S32 ADEC_DRV_WriteProc(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
    HI_U32 u32ChNum;
    ADEC_CMD_SAVE_E enSaveCmd;
    HI_CHAR  szBuf[256]    = {0};
    HI_CHAR* pcBuf         = szBuf;
    HI_CHAR* pcStartCmd    = "start";
    HI_CHAR* pcStopCmd     = "stop";
    HI_CHAR* pcSavePcmCmd  = "save_pcm";
    HI_CHAR* pcSaveEsCmd   = "save_es";
    HI_CHAR* pcHelpCmd     = "help";
    HI_CHAR  tempFilePath[256] = {0};
    struct seq_file* p = file->private_data;
    ADEC_PROC_ITEM_S* pstAdecProc;
    DRV_PROC_ITEM_S* pstProcItem = p->private;
    struct tm now;

    if (copy_from_user(szBuf, buf, count < sizeof(szBuf) - 1 ? count : sizeof(szBuf) - 1))
    {
        HI_ERR_ADEC("copy from user failed\n");
        return HI_FAILURE;
    }

    // sizeof("adec") is 4, adec proc node is as /proc/msp/adec00 --- /proc/msp/adec01
    u32ChNum = (pstProcItem->entry_name[4] - '0') * 10 + (pstProcItem->entry_name[5] - '0');
    if (u32ChNum >= ADEC_INSTANCE_MAXNUM)
    {
        HI_ERR_ADEC("Invalid Adec ID:%02d.\n", u32ChNum);
        goto SAVE_CMD_FAULT;
    }

    if (g_sAdecKAddrArray[u32ChNum].bUsed == HI_FALSE)
    {
        HI_ERR_ADEC("  ADEC[%02d] not open\n", u32ChNum);
        return HI_FAILURE;
    }

    if (g_sAdecKAddrArray[u32ChNum].psAdecKernelAddr == NULL)
    {
        HI_ERR_ADEC("  ADEC[%02d] PROC not INIT\n", u32ChNum);
        return HI_FAILURE;
    }

    pstAdecProc = (ADEC_PROC_ITEM_S*)g_sAdecKAddrArray[u32ChNum].psAdecKernelAddr;
    ADEC_STRING_SKIP_BLANK(pcBuf);

    if (strstr(pcBuf, pcSavePcmCmd))
    {
        enSaveCmd = ADEC_CMD_PROC_SAVE_PCM;
        pcBuf += strlen(pcSavePcmCmd);
    }
    else if (strstr(pcBuf, pcSaveEsCmd))
    {
        enSaveCmd = ADEC_CMD_PROC_SAVE_ES;
        pcBuf += strlen(pcSaveEsCmd);
    }
    else if (strstr(pcBuf, pcHelpCmd))
    {
        ADEC_DEBUG_SHOW_HELP(u32ChNum);
        return count;
    }
    else
    {
        goto SAVE_CMD_FAULT;
    }

    ADEC_STRING_SKIP_BLANK(pcBuf);

    if (strstr(pcBuf, pcStartCmd))
    {
        if ( HI_SUCCESS != HI_DRV_FILE_GetStorePath( tempFilePath, ADEC_PATH_NAME_MAXLEN ) )
        {
            HI_ERR_ADEC("get store path failed\n");
            return HI_FAILURE;
        }

        time_to_tm(get_seconds(), 0, &now);
        if (enSaveCmd == ADEC_CMD_PROC_SAVE_PCM)
        {
            snprintf( pstAdecProc->pcmFilePath, sizeof( pstAdecProc->pcmFilePath ), "%s/adec%d_%02u_%02u_%02u.pcm", tempFilePath, u32ChNum, now.tm_hour, now.tm_min, now.tm_sec);
            snprintf(pstAdecProc->adfilePath, sizeof(pstAdecProc->adfilePath), "%s/AD_adec%d_%02u_%02u_%02u.pcm", tempFilePath, u32ChNum, now.tm_hour, now.tm_min, now.tm_sec);
            if (pstAdecProc->enPcmCtrlState != ADEC_CMD_CTRL_START)
            {
                pstAdecProc->u32SavePcmCnt++;
                pstAdecProc->enPcmCtrlState = ADEC_CMD_CTRL_START;
                HI_DRV_PROC_EchoHelper("Started saving adec pcm data to %s\n", tempFilePath);
            }
            else
            {
                HI_DRV_PROC_EchoHelper("Started saving adec pcm data already.\n");
            }
        }
        else if (enSaveCmd == ADEC_CMD_PROC_SAVE_ES)
        {
            snprintf( pstAdecProc->esFilePath, sizeof( pstAdecProc->esFilePath ), "%s/adec%d_%02u_%02u_%02u.es", tempFilePath, u32ChNum, now.tm_hour, now.tm_min, now.tm_sec);
            snprintf(pstAdecProc->adfilePath, sizeof(pstAdecProc->adfilePath), "%s/AD_adec%d_%02u_%02u_%02u.es", tempFilePath, u32ChNum, now.tm_hour, now.tm_min, now.tm_sec);
            if (pstAdecProc->enEsCtrlState != ADEC_CMD_CTRL_START)
            {
                pstAdecProc->u32SaveEsCnt++;
                pstAdecProc->enEsCtrlState = ADEC_CMD_CTRL_START;
                HI_DRV_PROC_EchoHelper("Started saving adec es data to %s\n", tempFilePath);
            }
            else
            {
                HI_DRV_PROC_EchoHelper("Started saving adec es data already.\n");
            }
        }
    }
    else if (strstr(pcBuf, pcStopCmd))
    {
        if (enSaveCmd == ADEC_CMD_PROC_SAVE_PCM)
        {
            HI_DRV_PROC_EchoHelper("Finished saving adec pcm data.\n");
            pstAdecProc->enPcmCtrlState = ADEC_CMD_CTRL_STOP;
        }
        else if (enSaveCmd == ADEC_CMD_PROC_SAVE_ES)
        {
            HI_DRV_PROC_EchoHelper("Finished saving adec es data.\n");
            pstAdecProc->enEsCtrlState = ADEC_CMD_CTRL_STOP;
        }
    }
    else
    {
        goto SAVE_CMD_FAULT;
    }

    return count;

SAVE_CMD_FAULT:
    HI_ERR_ADEC("proc cmd is fault\n");
    ADEC_DEBUG_SHOW_HELP(u32ChNum);
    return HI_FAILURE;
}

static ADEC_REGISTER_PARAM_S s_stProcParam =
{
    .pfnReadProc  = ADEC_DRV_ReadProc,
    .pfnWriteProc = ADEC_DRV_WriteProc,
};

static HI_S32 ADEC_RegProc(HI_U32 u32AdecNum, ADEC_REGISTER_PARAM_S* pstParam)
{
    HI_CHAR aszBuf[16];
    DRV_PROC_ITEM_S*  pProcItem;

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), "adec%02d", u32AdecNum);
    pProcItem = HI_DRV_PROC_AddModule(aszBuf, HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_FATAL_ADEC("Create Adec proc entry fail!\n");
        return HI_FAILURE;
    }

    /* Set functions */
    pProcItem->read  = pstParam->pfnReadProc;
    pProcItem->write = pstParam->pfnWriteProc;

    HI_INFO_ADEC("Create Adec proc entry for OK!\n");
    return HI_SUCCESS;
}
#endif

HI_S32 ADEC_DRV_ModInit(HI_VOID)
{
    HI_S32 s32Ret;

#ifndef HI_MCE_SUPPORT
    s32Ret = HI_DRV_ADEC_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_ADEC("ADEC_DRV_Init failed(0x%x)\n", s32Ret);
        return s32Ret;
    }
#endif

    s32Ret = ADECRegisterDevice(&ADEC_DRV_Fops, &adec_drvops);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADEC("ADECRegisterDevice failed(0x%x)\n", s32Ret);
#ifndef HI_MCE_SUPPORT
        HI_DRV_ADEC_DeInit();
#endif
        return s32Ret;
    }

#ifdef MODULE
    HI_PRINT("Load hi_adec.ko success.  \t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID  ADEC_DRV_ModExit(HI_VOID)
{
    ADECUnregisterDevice();

#ifndef HI_MCE_SUPPORT
    HI_DRV_ADEC_DeInit();
#endif
}

#ifdef MODULE
module_init(ADEC_DRV_ModInit);
module_exit(ADEC_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
