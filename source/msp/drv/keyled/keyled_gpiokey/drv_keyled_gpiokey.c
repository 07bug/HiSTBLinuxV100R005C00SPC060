#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <asm/unistd.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <asm/signal.h>
#include <linux/time.h>
#include <linux/unistd.h>
#include <linux/poll.h>

#include "hi_type.h"
#include "hi_drv_mem.h"
#include "drv_gpio_ext.h"
#include "hi_drv_module.h"

#include "hi_unf_keyled.h"
#include "hi_error_mpi.h"
#include "hi_drv_keyled.h"
#include "drv_keyled_ioctl.h"
#include "drv_keyled.h"
#include "drv_keyled_gpiokey.h"

#ifdef CONFIG_HIGH_RES_TIMERS
#include <linux/hrtimer.h>
#endif


static  GPIO_EXT_FUNC_S *s_pGpioFunc = HI_NULL;

static atomic_t g_GpioKeyOpen = ATOMIC_INIT(0);

#define DEFAULT_REP_KEY_TIME   300

static keyled_dev_s keyled_dev;
//static HI_UNF_KEYLED_TIME_S keyled_time = {0};
static wait_queue_head_t wait_keyleds;

static HI_U32 s_key_detected_flag = 0;
HI_BOOL g_bTimerRunFlag =  HI_FALSE;

static HI_U32 s_key_code_last = KEY_MACRO_NO;
static HI_U32 s_key_code_curr = KEY_MACRO_NO;
static HI_U32 s_bKeyPressFlag = 0;

static HI_U32 s_cycle_cnt = 0;

static HI_VOID keyled_key_scan(HI_VOID);                                    /*KEY scan manage func*/

#define  KEYLED_TIMER_INTERVAL_MS 10

HI_VOID * pKey_timer = NULL;

/* BEGIN: Added by fzh, 2010/11/9*/
HI_VOID * HI_HIGH_RES_TimerInit(HI_VOID *pTimerProc)
{

#ifdef CONFIG_HIGH_RES_TIMERS       //defined in linux kernel
    struct hrtimer *pstApi_timer = NULL;
    pstApi_timer = (struct hrtimer *)HI_KMALLOC(HI_ID_KEYLED, sizeof(struct hrtimer),GFP_ATOMIC);
    if (NULL != pstApi_timer)
    {
        hrtimer_init(pstApi_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
        pstApi_timer->function = pTimerProc;
        HI_INFO_KEYLED("hrtimer_init OK! \n");
        return (void *)pstApi_timer;
    }
#else
    struct timer_list *pstApi_timer = NULL;
    pstApi_timer = (struct timer_list *)HI_KMALLOC(HI_ID_KEYLED, sizeof(struct timer_list),GFP_ATOMIC);
    if (NULL != pstApi_timer)
    {
        init_timer(pstApi_timer);
        pstApi_timer->function = pTimerProc;
        pstApi_timer->data = 0;
        HI_INFO_KEYLED("init_timer OK! \n");
        return (void *)pstApi_timer;
    }
#endif

    return NULL;
}

HI_S32 HI_HIGH_RES_TimerStart(HI_VOID *handle,HI_BOOL bInit)
{
    if(handle == NULL)
    {
        HI_ERR_KEYLED("HI_HIGH_RES_TimerStart handle invalid \n");
        return HI_FAILURE;
    }

#ifdef CONFIG_HIGH_RES_TIMERS    //defined in linux kernel
    hrtimer_start((struct hrtimer *)handle,ktime_set(0,KEYLED_TIMER_INTERVAL_MS*1000000),HRTIMER_MODE_REL);
#else
    {
        struct timer_list *pstApi_timer = NULL;
        pstApi_timer = (struct timer_list *)handle;
        pstApi_timer->expires = (jiffies + msecs_to_jiffies(KEYLED_TIMER_INTERVAL_MS));
        if(bInit == HI_TRUE)
        {
            add_timer(pstApi_timer);
        }
        else
        {
            mod_timer(pstApi_timer,pstApi_timer->expires);
        }
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_HIGH_RES_TimerUpdate(HI_VOID *handle)
{
    if(handle == NULL)
    {
        HI_ERR_KEYLED("HI_HIGH_RES_TimerUpdate handle invalid \n");
        return HI_FAILURE;
    }

#ifdef CONFIG_HIGH_RES_TIMERS    //defined in linux kernel
    hrtimer_forward((struct hrtimer *)handle, ktime_get(), ktime_set(0,KEYLED_TIMER_INTERVAL_MS*1000000));
#else
    {
        struct timer_list *pstApi_timer = NULL;
        pstApi_timer = (struct timer_list *)handle;
        pstApi_timer->expires = (jiffies + msecs_to_jiffies(KEYLED_TIMER_INTERVAL_MS));
        mod_timer(pstApi_timer,pstApi_timer->expires);
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_HIGH_RES_TimerDestroy(HI_VOID *handle)
{
    if(handle == NULL)
    {
        HI_ERR_KEYLED("HI_HIGH_RES_TimerDestroy handle invalid \n");
        return HI_FAILURE;
    }

#ifdef CONFIG_HIGH_RES_TIMERS    //defined in linux kernel
    hrtimer_cancel((struct hrtimer *)handle);
#else
    del_timer_sync((struct timer_list *)handle);
#endif

    HI_KFREE(HI_ID_KEYLED, handle);

    return HI_SUCCESS;
}

HI_VOID Key_TimerProc(HI_VOID)
{
    if (HI_SUCCESS != HI_HIGH_RES_TimerUpdate(pKey_timer))
    {
        HI_ERR_KEYLED("Err in HI_HIGH_RES_TimerUpdate!\n");
        return;
    }

    keyled_key_scan();
       
    if (HI_SUCCESS != HI_HIGH_RES_TimerStart(pKey_timer,HI_FALSE))
    {
        HI_ERR_KEYLED("Err in HI_HIGH_RES_TimerStart!\n");
        return;
    }

    return;
}

HI_S32 Key_InitTimer(HI_VOID)
{
    if (NULL != pKey_timer)
    {
        HI_ERR_KEYLED("Key_InitTimer pKey_timer is not NULL\n");
        return HI_FAILURE;
    }

    pKey_timer = HI_HIGH_RES_TimerInit(Key_TimerProc);

    if (HI_SUCCESS != HI_HIGH_RES_TimerStart(pKey_timer,HI_TRUE))
    {
        HI_ERR_KEYLED("HI_HIGH_RES_TimerStart start failure \n");
        return HI_FAILURE;
    }
    g_bTimerRunFlag = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID Key_DeleteTimer(HI_VOID)
{
    HI_HIGH_RES_TimerDestroy(pKey_timer);

    pKey_timer = NULL;
    g_bTimerRunFlag = HI_FALSE;

    HI_INFO_KEYLED("DeleteTimer g_bTimerRunFlag =  %d\n", g_bTimerRunFlag);

    return;
}


HI_S32 keyled_gpiokey_get_keycode(HI_VOID)
{
    HI_S32 s32key_code_sum = 0;

    HI_U32 u32Val = 1;

    if((!s_pGpioFunc) || (!s_pGpioFunc->pfnGpioReadBit))
    {
        HI_ERR_KEYLED("s_pGpioFunc or s_pGpioFunc->pfnGpioReadBit is NULL! \n");
        return HI_FAILURE;
    }

    //use gpio to query key 1*7
    if(0xFF != KEY_PWR)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_PWR, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1;
        }
    }

    if(0xFF != KEY_OK)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_OK, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 1;
        }
    }

    if(0xFF != KEY_RIGHT)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_RIGHT, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 2;
        }
    }

    if(0xFF != KEY_LEFT)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_LEFT, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 3;
        }
    }

    if(0xFF != KEY_DOWN)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_DOWN, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 4;
        }
    }

    if(0xFF != KEY_UP)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_UP, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 5;
        }
    }

    if(0xFF != KEY_MENU)
    {
        s_pGpioFunc->pfnGpioReadBit(KEY_MENU, &u32Val);
        if (0 == u32Val)
        {
            s32key_code_sum += 0x1 << 6;
        }
    }
    
    if (0 != s32key_code_sum)
    {
        return s32key_code_sum;
    }
    else /*when none*/
    {
        return HI_FAILURE;
    }
}

HI_S32 keyled_gpiokey_handle_keycode(HI_VOID)
{
    if (0 == s_key_detected_flag)  //no key pressed in this period
    {
        if (s_key_code_last == KEY_MACRO_NO)  //no key in last period
        {
            ;
        }
        else  //has key in last period
        {
            if (s_bKeyPressFlag)
            {
                /* report last key 'RELEASE', and recode no key pressed in this time */
                if(keyled_dev.enable_keyup)
                {
                    KEYLED_BUF_HEAD.keyled_code = s_key_code_last;
                    KEYLED_BUF_HEAD.keyled_state = KEY_RELEASE;
                    keyled_dev.head = KEYLED_INC_BUF(keyled_dev.head, keyled_dev.buf_len);

                    wake_up_interruptible(&wait_keyleds);
                }

                s_bKeyPressFlag =HI_FALSE;
            }
            else    /*warning: key twitter*/
            {
                ;
            }
            s_key_code_last = KEY_MACRO_NO;
        }
    }
    else  //has key pressed in this period
    {
        if (s_key_code_curr != s_key_code_last)  //new key
        {
            if (KEY_MACRO_NO == s_key_code_last)  /*no key in last scan*/
            {
                ;
            }
            else    /*has key in last scan*/
            {
                if (s_bKeyPressFlag)  /*last key is valid*/
                {
                    if (keyled_dev.enable_keyup)
                    {
                        KEYLED_BUF_HEAD.keyled_state= KEY_RELEASE;
                        KEYLED_BUF_HEAD.keyled_code = s_key_code_last;
                        keyled_dev.head = KEYLED_INC_BUF(keyled_dev.head, keyled_dev.buf_len);

                        wake_up_interruptible(&wait_keyleds);
                    }
                    s_bKeyPressFlag =HI_FALSE;
                }
                else   /*warning: key twitter */
                {
                    ;
                }
            }
            s_cycle_cnt = 0;
            s_key_code_last = s_key_code_curr;
        }
        else  //old key
        {
            s_cycle_cnt ++;
            if ((1 == s_cycle_cnt) && (HI_TRUE != s_bKeyPressFlag))
            {
                KEYLED_BUF_HEAD.keyled_state = KEY_PRESS;
                KEYLED_BUF_HEAD.keyled_code = s_key_code_last;
                keyled_dev.head = KEYLED_INC_BUF(keyled_dev.head, keyled_dev.buf_len);

                wake_up_interruptible(&wait_keyleds);
                s_cycle_cnt = 0;
                s_bKeyPressFlag = HI_TRUE;
            }

            if ((s_cycle_cnt >= keyled_dev.repkey_delaytime * 8 / (SCAN_INTV_GPIOKEY))
                        && (s_bKeyPressFlag))
            {
                if (keyled_dev.enable_repkey)
                {
                    KEYLED_BUF_HEAD.keyled_state = KEY_HOLD;
                    KEYLED_BUF_HEAD.keyled_code = s_key_code_last;
                    keyled_dev.head = KEYLED_INC_BUF(keyled_dev.head, keyled_dev.buf_len);

                    wake_up_interruptible(&wait_keyleds);
                }

            s_cycle_cnt = 0;
            s_bKeyPressFlag =HI_TRUE;
           }
        }
    }

    s_key_code_curr = KEY_MACRO_NO;
    s_key_detected_flag = 0;

    return HI_FAILURE;
}

static HI_VOID keyled_key_scan(HI_VOID)
{
    HI_S32 s32keycode = 0;

    s32keycode = keyled_gpiokey_get_keycode();

    if (HI_FAILURE == s32keycode)
    {
        s_key_detected_flag = 0;
        s_key_code_curr = KEY_MACRO_NO;
    }
    else
    {
        s_key_detected_flag = 1;
        s_key_code_curr = s32keycode;
        keyled_dev.key_come++;
        HI_INFO_KEYLED("enter hi_keyled_read : head=%d, tail=%d, buf_len=%d, getkey:%d\n",
            keyled_dev.head, keyled_dev.tail, keyled_dev.buf_len, s_key_code_curr);
    }

    keyled_gpiokey_handle_keycode();

}


HI_S32 keyled_gpiokey_dirset(HI_VOID)
{
    if((!s_pGpioFunc) || (!s_pGpioFunc->pfnGpioDirSetBit) || (!s_pGpioFunc->pfnGpioWriteBit))
    {
        HI_ERR_KEYLED(" s_pGpioFunc,s_pGpioFunc->pfnGpioDirSetBit or s_pGpioFunc->pfnGpioWriteBit is NULL\n");
        return HI_FAILURE;
    }

    if(0xFF != KEY_PWR)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_PWR, 1);   //input
    if(0xFF != KEY_OK)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_OK, 1);    //input
    if(0xFF != KEY_RIGHT)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_RIGHT, 1); //input
    if(0xFF != KEY_LEFT)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_LEFT, 1);  //input
    if(0xFF != KEY_DOWN)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_DOWN, 1);  //input
    if(0xFF != KEY_UP)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_UP, 1);    //input
    if(0xFF != KEY_MENU)
        s_pGpioFunc->pfnGpioDirSetBit(KEY_MENU, 1);  //input

    s_pGpioFunc->pfnGpioDirSetBit(LED0, 0);  //output
    s_pGpioFunc->pfnGpioDirSetBit(LED1, 0);  //output

    s_pGpioFunc->pfnGpioWriteBit(LED0, 0);  //output
    s_pGpioFunc->pfnGpioWriteBit(LED1, 1);  //output

    return 0;
}

HI_VOID keyled_gpiokey_clear_keybuf_func(HI_VOID)
{
    keyled_dev.tail = keyled_dev.head;
    keyled_dev.key_come = 0;
    keyled_dev.key_read = 0;

    return;
}


HI_S32 KEYLED_Init_GpioKey(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_GPIO, (HI_VOID**)&s_pGpioFunc);
    if (HI_SUCCESS != s32Ret || s_pGpioFunc == HI_NULL)
    {
        HI_ERR_KEYLED("Get GPIO function failed! \n");
        return HI_FAILURE;
    }

    init_waitqueue_head(&wait_keyleds);

    keyled_dev.head = 0;
    keyled_dev.tail = 0;
    keyled_dev.buf_len = KEYBUF_LEN;
    keyled_dev.enable_repkey = 1;
    keyled_dev.enable_keyup = 1;
    keyled_dev.key_come = 0;
    keyled_dev.key_read = 0;
    keyled_dev.blocktime = DEFAULT_BLOCKTIME;
    keyled_dev.repkey_delaytime = DEFAULT_REP_KEY_TIME;

    keyled_gpiokey_dirset();
    keyled_gpiokey_clear_keybuf_func();

    if (HI_FALSE == g_bTimerRunFlag)
    {
        Key_InitTimer();
        HI_INFO_KEYLED("KEYLED_Init_CT1642  do  Key_InitTimer\n");
    }

    return HI_SUCCESS;
}

HI_S32 KEYLED_DeInit_GpioKey(HI_VOID)
{
    Key_DeleteTimer();
    return HI_SUCCESS;
}

/* led display data */
HI_S32 KEYLED_LED_Display_GpioKey(HI_U32 u32Value)
{
    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_Open_GpioKey(HI_VOID)
{
    HI_INFO_KEYLED("KEYLED_KEY_Open_GpioKey --- g_GpioKeyOpen = %d \n",g_GpioKeyOpen);

    if (1 == atomic_inc_return(&g_GpioKeyOpen))
    {
        KEYLED_Init_GpioKey();
        HI_INFO_KEYLED("KEYLED GpioKey init \n");
    }

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_Close_GpioKey(HI_VOID)
{
    HI_INFO_KEYLED("KEYLED_KEY_Close_GpioKey --- g_GpioKeyOpen = %d \n",g_GpioKeyOpen);

    if((!s_pGpioFunc)||(!s_pGpioFunc->pfnGpioWriteBit))
    {
        HI_ERR_KEYLED("s_pGpioFunc or s_pGpioFunc->pfnGpioWriteBit is NULL! \n");
        return HI_FAILURE;
    }
    s_pGpioFunc->pfnGpioWriteBit(LED0, 1);  //output
    s_pGpioFunc->pfnGpioWriteBit(LED1, 0);  //output

    if (atomic_dec_and_test(&g_GpioKeyOpen))
    {
        HI_INFO_KEYLED("KEYLED GpioKey deinit \n");
        KEYLED_DeInit_GpioKey();
    }

    if (atomic_read(&g_GpioKeyOpen) < 0)
    {
        atomic_set(&g_GpioKeyOpen,0);
    }

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_Reset_GpioKey(HI_VOID)
{
    keyled_gpiokey_clear_keybuf_func();
    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_GetValue_GpioKey(HI_U32 *pu32PressStatus, HI_U32 *pu32KeyId)
{
    keyled_key_info_s keyled_to_user = {0};
    HI_S32 err = 0;

    HI_INFO_KEYLED("enter hi_keyled_read : head=%d, tail=%d, buf_len=%d\n",
                        keyled_dev.head, keyled_dev.tail, keyled_dev.buf_len);

    if ((keyled_dev.head) == (keyled_dev.tail))
    {
        if (0 == keyled_dev.blocktime)
        {
            return HI_ERR_KEYLED_NO_NEW_KEY;
        }

        err = wait_event_interruptible_timeout(wait_keyleds, (keyled_dev.head != keyled_dev.tail),
                                               (long)(keyled_dev.blocktime * HZ / 1000));

        if (err <= 0)  /*not wake up by received key*/
        {
            HI_INFO_KEYLED("wake up by timeout\n");
            return HI_ERR_KEYLED_TIMEOUT;
        }
    }

    HI_INFO_KEYLED("enter hi_keyled_read : head=%d, tail=%d, buf_len=%d\n",
                        keyled_dev.head, keyled_dev.tail, keyled_dev.buf_len);

    if (keyled_dev.head != keyled_dev.tail)
    {
        keyled_to_user  = KEYLED_BUF_TAIL;
        keyled_dev.tail = KEYLED_INC_BUF(keyled_dev.tail, keyled_dev.buf_len);
        keyled_dev.key_read++;

        *pu32PressStatus = keyled_to_user.keyled_state;
        *pu32KeyId = keyled_to_user.keyled_code;

        return HI_SUCCESS;
    }
    else
    {
        return HI_ERR_KEYLED_NO_NEW_KEY;
    }

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_IsRepKey_GpioKey(HI_U32 u32IsRepKey)
{
    keyled_dev.enable_repkey = u32IsRepKey;

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_IsKeyUp_GpioKey(HI_U32 u32IsKeyUp)
{
    keyled_dev.enable_keyup = u32IsKeyUp;

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_SetBlockTime_GpioKey(HI_U32 u32BlockTimeMs)
{
    keyled_dev.blocktime = u32BlockTimeMs;

    return HI_SUCCESS;
}

HI_S32 KEYLED_KEY_SetRepTime_GpioKey(HI_U32 u32RepTimeMs)
{
    keyled_dev.repkey_delaytime = u32RepTimeMs;

    return HI_SUCCESS;
}

HI_S32 KEYLED_LED_Open_GpioKey(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 KEYLED_LED_Close_GpioKey(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 KEYLED_LED_SetFlashPin_GpioKey(HI_UNF_KEYLED_LIGHT_E enPin)
{
    return HI_SUCCESS;
}

HI_S32 KEYLED_LED_SetFlashFreq_GpioKey(HI_UNF_KEYLED_LEVEL_E enLevel)
{
    return HI_SUCCESS;
}

HI_S32 KEYLED_LED_DisplayTime_GpioKey(HI_UNF_KEYLED_TIME_S stKeyLedTime)
{
    return HI_SUCCESS;
}

 HI_S32 KEYLED_GetProcInfo_GpioKey(KEYLED_PROC_INFO_S *stInfo)
 {
     stInfo->KeyBufSize = keyled_dev.buf_len;
     stInfo->KeyBufHead = keyled_dev.head;
     stInfo->KeyBufTail = keyled_dev.tail;
     stInfo->KeyComeNum = keyled_dev.key_come;
     stInfo->KeyReadNum = keyled_dev.key_read;
     stInfo->u32RepKeyTimeMs = keyled_dev.repkey_delaytime;
     stInfo->u32IsRepKeyEnable = keyled_dev.enable_repkey;
     stInfo->u32IsUpKeyEnable = keyled_dev.enable_keyup;
     stInfo->u32BlockTime = keyled_dev.blocktime;
     stInfo->enFlashPin = keyled_dev.FlashPin;
     stInfo->enFlashLevel = keyled_dev.FlashLevel;
     stInfo->KeyBufTail= keyled_dev.tail;

     return HI_SUCCESS;
 }

 HI_S32 KEYLED_Suspend_GpioKey(HI_VOID)
{
    keyled_gpiokey_clear_keybuf_func();

    return HI_SUCCESS;
}

 HI_S32 KEYLED_Resume_GpioKey(HI_VOID)
{
    /* del by sdk for the settings of GPIO5 do not lose when power up */
    //keyled_ct1642_gpio_dirset();

    return HI_SUCCESS;
}

#ifndef MODULE

EXPORT_SYMBOL(KEYLED_KEY_Open_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_Close_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_Reset_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_GetValue_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_SetBlockTime_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_SetRepTime_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_IsRepKey_GpioKey);
EXPORT_SYMBOL(KEYLED_KEY_IsKeyUp_GpioKey);

EXPORT_SYMBOL(KEYLED_LED_Open_GpioKey);
EXPORT_SYMBOL(KEYLED_LED_Close_GpioKey);
EXPORT_SYMBOL(KEYLED_LED_Display_GpioKey);
EXPORT_SYMBOL(KEYLED_LED_DisplayTime_GpioKey);
EXPORT_SYMBOL(KEYLED_LED_SetFlashPin_GpioKey);
EXPORT_SYMBOL(KEYLED_LED_SetFlashFreq_GpioKey);
EXPORT_SYMBOL(KEYLED_Suspend_GpioKey);
EXPORT_SYMBOL(KEYLED_Resume_GpioKey);
#endif

