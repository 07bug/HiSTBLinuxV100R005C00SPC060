/******************************************************************************

  Copyright (C), 2018, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : main_ca.c
  Version       : Initial Draft
  Author        : Device Chipset STB Development Dept
  Created       : 2018/06/26
  Description   :
  History       :
  1.Date        : 2018/06/26
    Author      : sdk
    Modification: Created file

*******************************************************************************/

#include "hi_type.h"
#include "hi_common.h"

#include "hi_drv_gpio.h"
#include "hi_drv_i2c.h"

#include "hi_ssa.h"

#ifdef HI_BUILD_WITH_KEYLED
#include "hi_unf_keyled.h"
#endif

#ifdef HI_MINIBOOT_SUPPORT
#include <app.h>
#endif

/***************************** Macro Definition ******************************/

#ifdef HI_BUILD_WITH_KEYLED
#if defined HI_BOOT_KEYLED_74HC164
#define PRODUCT_LED_VALUE_BOOT               (0xe1c5c5c1)
#elif defined (HI_BOOT_KEYLED_PT6961) || defined(HI_BOOT_KEYLED_PT6964) || defined(HI_BOOT_KEYLED_FD650)
#define PRODUCT_LED_VALUE_BOOT               (0x785c5c7c)
#elif defined HI_BOOT_KEYLED_CT1642
#define PRODUCT_LED_VALUE_BOOT               (0x1e3a3a3e)
#else
#define PRODUCT_LED_VALUE_BOOT               (0x785c5c7c)
#endif
#endif

/*******************************************************************************/

static HI_VOID SetLogLevel(HI_VOID)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
    HI_CHAR*         pLogLevel = HI_NULL;
    HI_U32          LogLevel = 1;
    HI_CHAR         aszEnvName[64];
    HI_S32          i;
    const HI_CHAR*   pszName;

    HI_LOG_Init();

    pLogLevel = getenv("loglevel");

    if (HI_NULL == pLogLevel)
    {
        HI_LOG_SetLevel(HI_ID_BUTT, 1);
    }
    else
    {
        LogLevel = simple_strtoul_2(pLogLevel, NULL, 10);

        if (LogLevel > HI_TRACE_LEVEL_DBG)
        {
            HI_LOG_SetLevel(HI_ID_BUTT, 0);
        }
        else
        {
            HI_LOG_SetLevel(HI_ID_BUTT, LogLevel);
        }
    }

    for (i = 0; i < HI_ID_BUTT; i++)
    {
        pszName = HI_LOG_GetModuleName(i);

        if ((HI_NULL != pszName) && (strlen(pszName) > 0))
        {
            HI_OSAL_Snprintf(aszEnvName, sizeof(aszEnvName), "loglevel-%s", pszName, sizeof(aszEnvName));
            pLogLevel = getenv(aszEnvName);

            if (HI_NULL != pLogLevel)
            {
                LogLevel = simple_strtoul_2(pLogLevel, NULL, 10);

                if (LogLevel > HI_TRACE_LEVEL_DBG)
                {
                    LogLevel = 0;
                }

                HI_LOG_SetLevel(i, LogLevel);
            }
        }
    }

#endif
    return;
}


HI_S32 product_init(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 fastapp_entry(int argc, char* argv[])
{
    HI_PRINT("\nSDK Version: %s\n\n", SDK_VERSION_STRING);

    SetLogLevel();

#ifndef HI_BOOT_FBL

#ifdef HI_PM_POWERUP_MODE1_SUPPORT
    boot_suspend();
#endif

#ifdef HI_HDMI_EDID_SUPPORT
    HI_UNF_HDMI_SetBaseParamByEDID();
#endif

    HI_DRV_GPIO_Init();
    HI_DRV_I2C_Init();

#ifdef HI_BUILD_WITH_KEYLED
    HI_UNF_KEYLED_Init();
    HI_UNF_KEY_Open();
    HI_UNF_LED_Open();
    HI_UNF_LED_Display(PRODUCT_LED_VALUE_BOOT);
#endif

#endif //HI_BOOT_FBL

    HI_SSA_Entry();

    HI_PRINT("\n Bug!!!..Can not get here\n\n");
    return 0;
}
