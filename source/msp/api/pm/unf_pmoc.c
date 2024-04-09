/***********************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_unf_pm.c
 * Description:
 *
 * History:
 * Version   Date                Author     DefectNum    Description
 * main\1                                     NULL         Create this file.
 ******************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>

#include "drv_pmoc_ioctl.h"
#include "hi_drv_pmoc.h"
#include "hi_drv_struct.h"
#include "hi_osal.h"

#include <sys/socket.h>
#include <net/if.h>

/* socket ioctl */
#define SIOCDEVPRIVATE  0x89F0  /* to 89FF, copy from include/linux/sockios.h */
#define SIOCGETMODE     (SIOCDEVPRIVATE)        /* get work mode */
#define SIOCSETMODE     (SIOCDEVPRIVATE + 1)    /* set work mode */
#define SIOCGETFWD      (SIOCDEVPRIVATE + 2)    /* get forcing forward config */
#define SIOCSETFWD      (SIOCDEVPRIVATE + 3)    /* set forcing forward config */
#define SIOCSETPM       (SIOCDEVPRIVATE + 4)    /* set pmt wake up config */
#define SIOCSETSUSPEND  (SIOCDEVPRIVATE + 5)    /* call dev->suspend, debug only */
#define SIOCSETRESUME   (SIOCDEVPRIVATE + 6)    /* call dev->resume, debug only */
#define GPIO5_NO_MAX    (47)
#define GPIO5_NO_MIN    (40)
#define FILTER_MIN_OFFSET (12)
#define DISPLAY_MODE_NONE  (0)
#define DISPLAY_MODE_DIGIT (1)
#define DISPLAY_MODE_TIME  (2)
#define DISPLAY_MAX_DIGIT  (9999)
#define DISPLAY_MAX_HOUR   (23)
#define DISPLAY_MAX_MINUTE (59)
#define MAX_COUNT (100)

struct pm_config {
    char index;             /* bit0--eth0 bit1--eth1 */
    char uc_pkts_enable;
    char magic_pkts_enable;
    char wakeup_pkts_enable;
    struct {
        unsigned int    mask_bytes;
        unsigned char   offset; /* >= 12 */
        unsigned char   value[FILTER_VALUE_COUNT];/* byte string */
        char            valid;  /* valid filter */
    } filter[FILTER_COUNT];
};

static HI_S32 g_s32C51Fd = -1;
static HI_S32 g_Netfd = -1;
static HI_U32 g_u32PmocInitCount = 0;
static HI_U32 g_bEnterSmartStandby = 0;

extern int get_remotewakeup_devnum(unsigned char * intmask);
extern int set_remotewakeup(void);

/*---- pm ----*/

/***********************************************************************************
*  Function:       HI_UNF_PMOC_Open
*  Description:    open pmoc
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:          ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_Init(HI_VOID)
{
    g_u32PmocInitCount++;

    if (g_s32C51Fd < 0)
    {
        g_s32C51Fd = open("/dev/"UMAP_DEVNAME_PM, O_RDWR, 0);
        if (g_s32C51Fd < 0)
        {
            HI_ERR_PM("pmoc open err. \n");
            return HI_ERR_PMOC_FAILED_INIT;
        }
    }

    if (g_Netfd < 0)
    {
        g_Netfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (g_Netfd < 0)
        {
            HI_WARN_PM("open socket failed \n");
        }
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_PMOC_Close
*  Description:    close pmoc
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:         ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_DeInit(HI_VOID)
{
    HI_S32 s32Ret = 0;

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM("pmoc not init\n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    g_u32PmocInitCount--;

    /* clean wake up param */
    s32Ret = ioctl(g_s32C51Fd, HI_PMOC_CLEAN_WAKEUP_PARAM_CMD);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_CLEAN_WAKEUP_PARAM_CMD error ret = 0x%x \n", s32Ret);
        return HI_FAILURE;
    }

    if (0 == g_u32PmocInitCount)
    {
        s32Ret = close(g_s32C51Fd);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PM("DeInit pmoc err. \n");
            return HI_FAILURE;
        }
        g_s32C51Fd = -1;

        if (g_Netfd >= 0)
        {
            close(g_Netfd);
            g_Netfd = -1;
        }
    }

    return HI_SUCCESS;
}

/***********************************************************************************
*  Function:       HI_UNF_PMOC_SetStandbyDispMode
*  Description:    set led display content
*  Calls:
*  Data Accessed:  NA
*  Data Updated:   NA
*  Input:          NA
*  Output:         NA
*  Return:         ErrorCode(reference to document)
*  Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_SetStandbyDispMode(HI_UNF_PMOC_STANDBY_MODE_S_PTR pstStandbyMode)
{
    HI_S32 ret = 0;
    C51_PMOC_DISP_S dispInfo;

    if (HI_NULL == pstStandbyMode)
    {
        HI_ERR_PM(" Input parameter(pstStandbyMode) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM("file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (pstStandbyMode->u32Mode > DISPLAY_MODE_TIME)
    {
        HI_ERR_PM("mode parameter is illegal \n");
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if (pstStandbyMode->u32Mode == DISPLAY_MODE_TIME)
    {
        if ((pstStandbyMode->stTimeInfo.u32Hour > DISPLAY_MAX_HOUR)
           || (pstStandbyMode->stTimeInfo.u32Minute > DISPLAY_MAX_MINUTE)
           || (pstStandbyMode->stTimeInfo.u32Second > DISPLAY_MAX_MINUTE))
        {
            HI_ERR_PM("time parameter is illegal \n");
            return HI_ERR_PMOC_INVALID_PARA;
        }

        dispInfo.mode  = 2;
        dispInfo.value = (((pstStandbyMode->stTimeInfo.u32Hour & 0xff) << 16)
                          | ((pstStandbyMode->stTimeInfo.u32Minute & 0xff) << 8)
                          | ((pstStandbyMode->stTimeInfo.u32Second & 0xff)));
    }
    else if (pstStandbyMode->u32Mode == DISPLAY_MODE_DIGIT)
    {
        HI_U32 tmp0;
        HI_U32 tmp1;

        if (pstStandbyMode->u32DispCode > DISPLAY_MAX_DIGIT)
        {
            HI_ERR_PM("chan num is illegal \n");
            return HI_ERR_PMOC_INVALID_PARA;
        }

        dispInfo.mode  = DISPLAY_MODE_DIGIT;
        dispInfo.value = 0;

        // 0
        tmp0 = pstStandbyMode->u32DispCode;
        tmp1 = tmp0 % 10;
        dispInfo.value |= tmp1 & 0xff;

        // 1
        tmp0 = tmp0 / 10;
        tmp1 = tmp0 % 10;
        dispInfo.value |= ((tmp1 & 0xff) << 8);

        // 2
        tmp0 = tmp0 / 10;
        tmp1 = tmp0 % 10;
        dispInfo.value |= ((tmp1 & 0xff) << 16);

        // 3
        tmp0 = tmp0 / 10;
        tmp1 = tmp0 % 10;
        dispInfo.value |= ((tmp1 & 0xff) << 24);
    }
    else
    {
        dispInfo.mode  = DISPLAY_MODE_NONE;
        dispInfo.value = 0;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_STANDBY_CMD, (&dispInfo));
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM("pm HI_ERR_PMoC_FAILED_STANDBY error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_STANDBY;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
Function:       HI_UNF_PMOC_SetWakeUpAttr
Description:
Calls:
Data Accessed:  NA
Data Updated:   NA
Input:          NA
Output:         NA
Return:         ErrorCode(reference to document)
Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_SetWakeUpAttr(HI_UNF_PMOC_WKUP_S_PTR pstAttr)
{
    HI_U32 i;
    HI_S32 ret;
    C51_PMOC_VAL_S pmocVal;
    HI_U8 u8IntMask = 0, u8FilterNumber;
    struct pm_config pm;
    struct ifreq ifr;

    if (HI_NULL == pstAttr)
    {
        HI_ERR_PM(" Input parameter(pstAttr) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (pstAttr->u32IrPmocNum > PMOC_WKUP_IRKEY_MAXNUM)
    {
        HI_ERR_PM("IrPmocNum too much \n");
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if (pstAttr->stNetwork.enEthIndex >= HI_UNF_PMOC_ETH_BUTT)
     {
        HI_ERR_PM("Eth index not support \n");
        return HI_ERR_PMOC_INVALID_PARA;
    }

    memset(&pmocVal, 0, sizeof(pmocVal));

    pmocVal.irnum = pstAttr->u32IrPmocNum;
    for (i = 0; i < pmocVal.irnum; i++)
    {
        pmocVal.irlVal[i] = pstAttr->u32IrPowerKey0[i];
        pmocVal.irhVal[i] = pstAttr->u32IrPowerKey1[i];
    }

    pmocVal.keyVal  = pstAttr->u32KeypadPowerKey;
    pmocVal.timeVal = pstAttr->u32WakeUpTime;

    if (pstAttr->bMouseKeyboardEnable)
    {
        pmocVal.mouseKeyboardEnable = 0x1;
    }

    if (pstAttr->bMouseKeyboardEnable == HI_TRUE)
    {
        ret = get_remotewakeup_devnum(&u8IntMask);
        HI_INFO_PM("\n mouse wakeup dev num = %d mask = %d\n", ret, u8IntMask);
        if (ret == HI_FAILURE)
        {
            HI_ERR_PM(" pm get usb wakeup dev number error ret = 0x%x \n", ret);
            return HI_ERR_PMOC_FAILED_SETWAKEUPVAL;
        }
        ret = set_remotewakeup();
        if (ret == HI_FAILURE)
        {
            HI_ERR_PM(" pm set usb wakeup error ret = 0x%x \n", ret);
            return HI_ERR_PMOC_FAILED_SETWAKEUPVAL;
        }

        pmocVal.usbWakeupMask = u8IntMask;
    }
    else
    {
        pmocVal.usbWakeupMask = 0;
    }

    if (sizeof(HI_UNF_PMOC_NETWORK_S) == sizeof(C51_PmocNet_S))
    {
        memcpy(&pmocVal.stNetwork, &pstAttr->stNetwork, sizeof(HI_UNF_PMOC_NETWORK_S));
    }

    if (pstAttr->stNetwork.bUcPacketEnable || pstAttr->stNetwork.bMagicPacketEnable
            || pstAttr->stNetwork.bWakeupFrameEnable)
    {
        memset(&ifr, 0, sizeof(ifr));

        /* for gmac driver, we don't care use eth0 or eth1 */
        HI_OSAL_Strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);

        pm.index = pstAttr->stNetwork.enEthIndex;
        pm.uc_pkts_enable = pstAttr->stNetwork.bUcPacketEnable;
        pm.magic_pkts_enable = pstAttr->stNetwork.bMagicPacketEnable;
        pm.wakeup_pkts_enable = pstAttr->stNetwork.bWakeupFrameEnable;

        if (pm.wakeup_pkts_enable == 1)
        {
            for (u8FilterNumber = 0; u8FilterNumber < FILTER_COUNT; u8FilterNumber++)
            {
                pm.filter[u8FilterNumber].valid = pstAttr->stNetwork.stFrame[u8FilterNumber].bFilterValid;

                if (pstAttr->stNetwork.stFrame[u8FilterNumber].u8Offset < FILTER_MIN_OFFSET)
                {
                    HI_ERR_PM(" Filter Offset less than 12, force it to be 12 \n");
                    pm.filter[u8FilterNumber].offset = FILTER_MIN_OFFSET;
                }
                else
                {
                    pm.filter[u8FilterNumber].offset = pstAttr->stNetwork.stFrame[u8FilterNumber].u8Offset;
                }
                pm.filter[u8FilterNumber].mask_bytes = pstAttr->stNetwork.stFrame[u8FilterNumber].u32MaskBytes;

                for (i = 0; i < FILTER_VALUE_COUNT; i++)
                {
                    pm.filter[u8FilterNumber].value[i] = pstAttr->stNetwork.stFrame[u8FilterNumber].u8Value[i];
                }
            }

            for (u8FilterNumber = 0; u8FilterNumber < FILTER_COUNT; u8FilterNumber++)
            {
                HI_INFO_PM("filter[%d]: ", u8FilterNumber);
                HI_INFO_PM("valid: %d, ", pm.filter[u8FilterNumber].valid);
                HI_INFO_PM("offset: %d, ", pm.filter[u8FilterNumber].offset);
                HI_INFO_PM("mask_bytes: %x \n", pm.filter[u8FilterNumber].mask_bytes);
                for (i = 0; i < FILTER_VALUE_COUNT; i++)
                {
                    HI_INFO_PM("%02hhx ", pm.filter[u8FilterNumber].value[i]);
                }
                HI_INFO_PM("\n");
            }
        }

        ifr.ifr_data = (caddr_t)&pm;

        ret = ioctl(g_Netfd, SIOCSETPM, &ifr);
        if (ret != HI_SUCCESS)
        {
            /* if eth config error, don't return error status */
            HI_ERR_PM(" pm set network wake-up error ret = 0x%x \n", ret);
        }

        pmocVal.ethWakeupFlag = 0x1;
    }

    if (pstAttr->bResumeResetEnable)
    {
        pmocVal.resumeResetFlag = 0x1;
    }

    if (pstAttr->bGpioWakeUpEnable)
    {
        pmocVal.gpioWakeUpEnable = 0x1;
    }

    if (pstAttr->bCECWakeUpEnable)
    {
        pmocVal.cecWakeUpEnable = 0x1;
    }

    if (HI_TRUE == pstAttr->bGpioWakeUpEnable)
    {
        pmocVal.gpioPort = pstAttr->u32GpioNo;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_SET_WAKEUP_CMD, &pmocVal);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_SET_WAKEUP_CMD error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_SETWAKEUPVAL;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
Function:       HI_UNF_PMOC_GetWakeUpAttr
Description:    get wake up attr
Calls:
Data Accessed:  NA
Data Updated:   NA
Input:          NA
Output:         NA
Return:         ErrorCode(reference to document)
Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_GetWakeUpAttr(HI_UNF_PMOC_WKUP_S_PTR pstAttr)
{
    HI_U32 i;
    HI_S32 ret;
    C51_PMOC_VAL_S pmocVal;

    if (HI_NULL == pstAttr)
    {
        HI_ERR_PM(" Input parameter(pstAttr) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_GET_WAKEUP_CMD, &pmocVal);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_GET_WAKEUP_CMD error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_GETWAKEUPVAL;
    }

    pstAttr->u32IrPmocNum = pmocVal.irnum;
    for (i = 0; i < pmocVal.irnum; i++)
    {
        pstAttr->u32IrPowerKey0[i] = pmocVal.irlVal[i];
        pstAttr->u32IrPowerKey1[i] = pmocVal.irhVal[i];
    }

    pstAttr->u32KeypadPowerKey = pmocVal.keyVal;
    pstAttr->u32WakeUpTime = pmocVal.timeVal;

    pstAttr->bMouseKeyboardEnable = (pmocVal.mouseKeyboardEnable) ? HI_TRUE : HI_FALSE;

    pstAttr->bResumeResetEnable = (pmocVal.resumeResetFlag) ? HI_TRUE : HI_FALSE;

    pstAttr->bGpioWakeUpEnable = (pmocVal.gpioWakeUpEnable) ? HI_TRUE : HI_FALSE;

    if (pmocVal.gpioWakeUpEnable)
    {
        pstAttr->u32GpioNo = pmocVal.gpioPort;
    }
    else
    {
        pstAttr->u32GpioNo = 0;
    }

    pstAttr->bCECWakeUpEnable = (pmocVal.cecWakeUpEnable) ? HI_TRUE : HI_FALSE;

    if (sizeof(HI_UNF_PMOC_NETWORK_S) == sizeof(C51_PmocNet_S))
    {
        memcpy(&pstAttr->stNetwork, &pmocVal.stNetwork, sizeof(HI_UNF_PMOC_NETWORK_S));
    }

    return HI_SUCCESS;
}


/***********************************************************************************
Function:       HI_UNF_PMOC_ReadSystemMode
Description:    get the current system mode
Calls:
Data Accessed:  NA
Data Updated:   NA
Input:          NA
Output:         NA
Return:         ErrorCode(reference to document)
Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_ReadSystemMode(HI_UNF_PMOC_MODE_E * penSystemMode)
{

    if (HI_NULL == penSystemMode)
    {
        HI_ERR_PM(" Input parameter(penSystemMode) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    *penSystemMode = HI_UNF_PMOC_MODE_NORMAL;

    return HI_SUCCESS;
}

/***********************************************************************************
Function:       HI_UNF_PMOC_SwitchSystemMode
Description:    set the switch mode of  the system
Calls:          HI_PMoC_SwitchSystemMode
Data Accessed:  NA
Data Updated:   NA
Input:          NA
Output:         NA
Return:         ErrorCode(reference to document)
Others:         NA
***********************************************************************************/
HI_S32 HI_UNF_PMOC_SwitchSystemMode(HI_UNF_PMOC_MODE_E enSystemMode, HI_UNF_PMOC_ACTUAL_WKUP_E * pu32WakeUpStatus)
{
    HI_S32 ret;
    HI_U32 cnt;
    C51_WAKEUP_MODE_S wakeupmode;
    FILE *fp;
    struct timeval tv = {0,0};

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (HI_UNF_PMOC_MODE_NORMAL == enSystemMode)
    {
        return HI_SUCCESS;
    }

    switch (enSystemMode)
    {
        case HI_UNF_PMOC_MODE_SLOW:
        case HI_UNF_PMOC_MODE_DOZE:
        case HI_UNF_PMOC_MODE_SLEEP:
        {
            break;
        }
        default:
        {
            HI_ERR_PM(" invalid mode %d ! \n", enSystemMode);
            return HI_ERR_PMOC_INVALID_PARA;
        }
    }

    /* handle things before entering standby, for example: close dvfs */
    ret = ioctl(g_s32C51Fd, HI_PMOC_WAKEUP_READY_CMD);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_WAKEUP_READY_CMD error \n");
        return HI_ERR_PMOC_FAILED_STANDBY;
    }

    /* standby and then wait for wake up */
    fp = fopen( "/sys/power/state", "r+" );
    if (fp == NULL)
    {
        HI_ERR_PM( "file open error!\n" );
        return HI_ERR_PMOC_FAILED_STANDBY;
    }

    fputs("mem", fp );
    fclose(fp);
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    select(0, NULL, NULL, NULL, &tv);

    /* wake up */
    cnt  = 0;
    wakeupmode.enWakeUpMode = C51_PMOC_WAKEUP_BUTT;
    while (cnt < MAX_COUNT)
    {
        cnt++;
        ret = ioctl(g_s32C51Fd, HI_PMOC_GET_WAKEUPMODE_CMD, &wakeupmode);
        if (ret != HI_SUCCESS)
        {
            tv.tv_sec = 0;
            tv.tv_usec = 10000;
            select(0, NULL, NULL, NULL, &tv);
            continue;
        }

        if (wakeupmode.enWakeUpMode >= C51_PMOC_WAKEUP_BUTT)
        {
            tv.tv_sec = 0;
            tv.tv_usec = 10000;
            select(0, NULL, NULL, NULL, &tv);
            continue;
        }

        break;
    }

    if (cnt >= MAX_COUNT)
    {
        HI_ERR_PM(" fail to get wake up mode after resume \n");
        return HI_ERR_PMOC_FAILED_STANDBY;
    }

    HI_INFO_PM(" wakeup mode: %d ! \n", wakeupmode.enWakeUpMode);

    if (pu32WakeUpStatus)
    {
        *pu32WakeUpStatus = (HI_UNF_PMOC_ACTUAL_WKUP_E)wakeupmode.enWakeUpMode;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_SetScene(HI_UNF_PMOC_SCENE_E eScene)
{
    if (eScene != HI_UNF_PMOC_SCENE_STANDARD)
    {
        HI_ERR_PM(" eScene = %d  err ! \n", eScene);
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_SetDevType(HI_UNF_PMOC_DEV_TYPE_S_PTR pdevType)
{
    HI_S32  ret;
    C51_PMOC_DEV_S dev;

    if (HI_NULL == pdevType)
    {
        HI_ERR_PM(" Input parameter(pdevType) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (pdevType->irtype >= HI_UNF_IR_CODE_BUTT)
    {
        HI_ERR_PM(" pdevType->irtype = %d  err ! \n", pdevType->irtype);
        return HI_ERR_PMOC_INVALID_PARA;
    }

    dev.irtype = pdevType->irtype;
    HI_INFO_PM("\n dev.irtype = %d  \n", dev.irtype);

#ifdef HI_KEYLED_SUPPORT
    if (pdevType->kltype >= HI_UNF_KEYLED_TYPE_BUTT)
    {
        HI_ERR_PM(" pdevType->kltype = %d  err ! \n", pdevType->kltype);
        return HI_ERR_PMOC_INVALID_PARA;
    }

    dev.kltype = pdevType->kltype;
#endif

    ret = ioctl(g_s32C51Fd, HI_PMOC_WAKEUP_SETDEV_CMD, (&dev));
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_WAKEUP_SETDEV_CMD error  ret = 0x%x\n", ret);
        return HI_ERR_PMOC_FAILED_SETDEV;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_LoadMcuCode(HI_U8 *pMcuCode, HI_U32 CodeSize)
{
    HI_S32  ret;

    if (HI_NULL == pMcuCode)
    {
        HI_ERR_PM(" Input parameter(pMcuCode) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (CodeSize > MCU_CODE_MAXSIZE)
    {
        HI_ERR_PM(" Input parameter(CodeSize) bigger than 0x%x bytes\n", MCU_CODE_MAXSIZE);
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_LOAD_MCUCODE_CMD, (pMcuCode));
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_LOAD_MCUCODE_CMD error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_SETDEV;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_SetPwrOffGpio(HI_U32 u32GpioNo,HI_BOOL bHighOrLow)
{
    HI_S32  ret;
    HI_U32 u32GpioValArray[2] = {0, 0};

    if (((u32GpioNo < GPIO5_NO_MIN) && (0 != u32GpioNo)) || (u32GpioNo > GPIO5_NO_MAX))
    {
        HI_ERR_PM("para u32GpioNo is invalid.\n");
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if ((bHighOrLow != HI_TRUE) && (bHighOrLow != HI_FALSE))
    {
        HI_ERR_PM("para bHighOrLow is invalid.\n");
        return HI_ERR_PMOC_INVALID_PARA;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    u32GpioValArray[0] = u32GpioNo;
    if(bHighOrLow)
    {
        u32GpioValArray[1] = 1;
    }
    else
    {
        u32GpioValArray[1] = 0;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_SET_PWROFFGPIO_CMD, u32GpioValArray);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_PMOC_SET_PWROFFGPIO_CMD error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_SETDEV;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_GetStandbyPeriod(HI_U32 *pu32Period)
{
    HI_S32  ret;
    HI_U32 u32Period = 0;

    if (HI_NULL == pu32Period)
    {
       HI_ERR_PM(" Input parameter(pu32Period) invalid \n");
       return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
       HI_ERR_PM("file descriptor is illegal \n");
       return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_GET_PERIOD_CMD, &u32Period);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_UNF_PMOC_GetStandbyPeriod error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_GETPERIOD;
    }

    *pu32Period = u32Period;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_EnterSmartStandby(HI_U32 u32HoldModules)
{
    HI_S32  ret;

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM("file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (g_bEnterSmartStandby)
    {
        HI_ERR_PM("can't re-enter standby \n");
        return HI_FAILURE;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_ENTER_SMARTSTANDBY_CMD, &u32HoldModules);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_UNF_PMOC_EnterSmartStandby error ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    g_bEnterSmartStandby = 1;

    return HI_SUCCESS;
}


HI_S32 HI_UNF_PMOC_QuitSmartStandby(HI_VOID)
{
    HI_S32  ret;

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM("file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    if (0 == g_bEnterSmartStandby)
    {
        HI_ERR_PM("can't re-enter resume \n");
        return HI_FAILURE;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_QUIT_SMARTSTANDBY_CMD);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_UNF_PMOC_QuitSmartStandby error ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    g_bEnterSmartStandby = 0;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PMOC_BoostCpuFreq(HI_VOID)
{
    HI_S32  ret;

    if (g_s32C51Fd < 0)
    {
       HI_ERR_PM("file descriptor is illegal \n");
       return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_BOOST_CPU);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_MPI_PMOC_BoostCpuFreq error ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_GetWakeUpMode(HI_UNF_PMOC_WAKEUP_MODE_S_PTR pstAttr)
{
    HI_S32 ret;
    C51_WAKEUP_MODE_S wakeupmode;

    if (HI_NULL == pstAttr)
    {
        HI_ERR_PM(" Input parameter(pstAttr) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_GET_WAKEUPMODE_CMD, &wakeupmode);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_UNF_PMOC_GetWakeUpMode error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_GETWAKEUPMODE;
    }

    pstAttr->enWakeUpMode = wakeupmode.enWakeUpMode;
    pstAttr->u64IRPowerKey = wakeupmode.u64IRPowerKey;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_PMOC_GetChipTemp(HI_UNF_PMOC_CHIP_TEMP_S *pstChipTemp)
{
    HI_S32 ret;
    HI_S32 s32ChipTemp;

    if (HI_NULL == pstChipTemp)
    {
        HI_ERR_PM(" Input parameter(pstChipTemp) invalid \n");
        return HI_ERR_PMOC_INVALID_POINT;
    }

    if (g_s32C51Fd < 0)
    {
        HI_ERR_PM(" file descriptor is illegal \n");
        return HI_ERR_PMOC_NOT_INIT;
    }

    ret = ioctl(g_s32C51Fd, HI_PMOC_GET_TEMPERATURE_CMD, &s32ChipTemp);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_UNF_PMOC_GetChipTemperature error ret = 0x%x \n", ret);
        return HI_ERR_PMOC_FAILED_GETTEMPERATURE;
    }

    pstChipTemp->s32ChipSensor1Temp = s32ChipTemp;
    pstChipTemp->s32ChipSensor2Temp = 0;
    pstChipTemp->s32ChipSensor3Temp = 0;
    pstChipTemp->s32ChipSensor4Temp = 0;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_PMOC_SetCPUMinFreq(HI_BOOL bFlag, HI_U32 u32MinFreq)
{
    HI_S32  ret;
    C51_CPU_MINFREQ_S stMinFreq = {0};

    if (g_s32C51Fd < 0)
    {
       HI_ERR_PM("file descriptor is illegal \n");
       return HI_ERR_PMOC_NOT_INIT;
    }

    stMinFreq.bSetMinFreqFlag = bFlag;
    stMinFreq.u32CPUMinFreq = u32MinFreq;

    ret = ioctl(g_s32C51Fd, HI_PMOC_SET_CPU_MIN_FREQ_CMD, &stMinFreq);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PM(" pm HI_MPI_PMOC_SetMinCPUFreq error ret = 0x%x \n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
