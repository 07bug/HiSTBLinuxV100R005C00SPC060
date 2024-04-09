/*******************************************************************************
 *             Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: keyled_fd650.h
 * Description:
 *
 * History:
 * Version   Date              Author    DefectNum       Description
 *          May, 30th           y45343                      Create file
 *******************************************************************************/
 
#ifndef __KEYLED_FD650_H__
#define __KEYLED_FD650_H__

#ifdef HI_KEYLED_FD650_CLOCK_GPIO
#define CLK_FD650  HI_KEYLED_FD650_CLOCK_GPIO
#define DINOUT_FD650  HI_KEYLED_FD650_DINOUT_GPIO
#else
#define CLK_FD650  0x2b
#define DINOUT_FD650  0x2d
#endif

#define FD650_SCL       (CLK_FD650)
#define FD650_SDA       (DINOUT_FD650)
#define HIGH    (1)
#define LOW     (0)
#define FD50_OUTPUT LOW
#define FD50_INPUT HIGH

#define DELAY  udelay(1)

#define FD650_SCL_SET\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioWriteBit)\
               s_pGpioFunc->pfnGpioWriteBit(FD650_SCL, HIGH);\
    } while(0)

#define FD650_SCL_CLR\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioWriteBit)\
               s_pGpioFunc->pfnGpioWriteBit(FD650_SCL, LOW);\
    } while(0)

#define FD650_SCL_D_OUT\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioDirSetBit)\
               s_pGpioFunc->pfnGpioDirSetBit(FD650_SCL, FD50_OUTPUT);\
    } while(0)

#define FD650_SDA_SET\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioWriteBit)\
               s_pGpioFunc->pfnGpioWriteBit(FD650_SDA, HIGH);\
    } while(0)

#define FD650_SDA_CLR\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioWriteBit)\
               s_pGpioFunc->pfnGpioWriteBit(FD650_SDA, LOW);\
    } while(0)

#define FD650_SDA_IN         hi_gpio_read_SDA_IN()

#define FD650_SDA_D_OUT\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioDirSetBit)\
               s_pGpioFunc->pfnGpioDirSetBit(FD650_SDA, FD50_OUTPUT);\
    } while(0)

#define FD650_SDA_D_IN\
    do {\
           if (s_pGpioFunc && s_pGpioFunc->pfnGpioDirSetBit)\
               s_pGpioFunc->pfnGpioDirSetBit(FD650_SDA, FD50_INPUT);\
    } while(0)

/** System parameter command  */
/**CNcomment:����ϵͳ�������� */
#define FD650_BIT_ENABLE     0x01   /**<Open/close bit           */     /**<CNcomment: ����/�ر�λ */
#define FD650_BIT_SLEEP      0x04   /**<Sleep control bit        */     /**<CNcomment: ˯�߿���λ  */
#define FD650_BIT_7SEG       0x08   /**<Seven segment control bit*/     /**<CNcomment: 7�ο���λ   */
#define FD650_BIT_INTENS1    0x10   /**<Level 1 light            */     /**<CNcomment: 1������     */
#define FD650_BIT_INTENS2    0x20   /**<Level 2 light            */     /**<CNcomment: 2������     */
#define FD650_BIT_INTENS3    0x30   /**<Level 3 light            */     /**<CNcomment: 3������     */
#define FD650_BIT_INTENS4    0x40   /**<Level 4 light            */     /**<CNcomment: 4������     */
#define FD650_BIT_INTENS5    0x50   /**<Level 5 light            */     /**<CNcomment: 5������     */
#define FD650_BIT_INTENS6    0x60   /**<Level 6 light            */     /**<CNcomment: 6������     */
#define FD650_BIT_INTENS7    0x70   /**<Level 7 light            */     /**<CNcomment: 7������     */
#define FD650_BIT_INTENS8    0x00   /**<Level 8 light            */     /**<CNcomment: 8������     */

#define FD650_SYSOFF     0x0400                              /**<Close led and key  */              /**<CNcomment:�ر���ʾ���رռ���      */
#define FD650_SYSON      ( FD650_SYSOFF | FD650_BIT_ENABLE ) /**<Open led and key  */               /**<CNcomment:������ʾ������          */
#define FD650_SLEEPOFF    FD650_SYSOFF                       /**<Close sleep  */                    /**<CNcomment:�ر�˯��                */
#define FD650_SLEEPON    ( FD650_SYSOFF | FD650_BIT_SLEEP )  /**<Open sleep  */                     /**<CNcomment:����˯��                */
#define FD650_7SEG_ON    ( FD650_SYSON | FD650_BIT_7SEG )    /**<Open seven segment mode  */        /**<CNcomment:�����߶�ģʽ            */
#define FD650_8SEG_ON    ( FD650_SYSON | 0x00 )              /**<Open eight segment mode  */        /**<CNcomment:�����˶�ģʽ            */
#define FD650_SYSON_1    ( FD650_SYSON | FD650_BIT_INTENS1 ) /**<Open led, key, level 1 light  */   /**<CNcomment:������ʾ�����̡�1������ */
#define FD650_SYSON_2    ( FD650_SYSON | FD650_BIT_INTENS2 ) /**<Open led, key, level 2 light  */   /**<CNcomment:������ʾ�����̡�2������ */
#define FD650_SYSON_3    ( FD650_SYSON | FD650_BIT_INTENS3 ) /**<Open led, key, level 3 light  */   /**<CNcomment:������ʾ�����̡�3������ */
#define FD650_SYSON_4    ( FD650_SYSON | FD650_BIT_INTENS4 ) /**<Open led, key, level 4 light  */   /**<CNcomment:������ʾ�����̡�4������ */
#define FD650_SYSON_5    ( FD650_SYSON | FD650_BIT_INTENS5 ) /**<Open led, key, level 5 light  */   /**<CNcomment:������ʾ�����̡�5������ */
#define FD650_SYSON_6    ( FD650_SYSON | FD650_BIT_INTENS6 ) /**<Open led, key, level 6 light  */   /**<CNcomment:������ʾ�����̡�6������ */
#define FD650_SYSON_7    ( FD650_SYSON | FD650_BIT_INTENS7 ) /**<Open led, key, level 7 light  */   /**<CNcomment:������ʾ�����̡�7������ */
#define FD650_SYSON_8    ( FD650_SYSON | FD650_BIT_INTENS8 ) /**<Open led, key, level 8 light  */   /**<CNcomment:������ʾ�����̡�8������ */

/** Data command */
/**<CNcomment:�������������� */
#define FD650_DIG0        0x1400            
#define FD650_DIG1        0x1500            
#define FD650_DIG2        0x1600            
#define FD650_DIG3        0x1700            
#define FD650_DOT         0x0080

/** Reading key command */
/**<CNcomment:��ȡ������������ */
#define FD650_GET_KEY     0x0700

#define SCAN_INTV   (30)    //ms

#define DISPLAY_ON  1
#define DISPLAY_OFF  0
#define KEY_MACRO_NO (0xff)
#define DISPLAY_REG_NUM     (14)
#define DISPLAY_SEG_CURR     (4)
#define KEY_COL_NUM     10
//#define KEY_REAL_NUM     30
//#define DISPLAY_MODE_NUM 4
#define DISPLAY_REG_START_ADDR  (0x00)


HI_S32 KEYLED_KEY_Open_FD650(HI_VOID);
HI_S32 KEYLED_KEY_Close_FD650(HI_VOID);
HI_S32 KEYLED_KEY_Reset_FD650(HI_VOID);
HI_S32 KEYLED_KEY_GetValue_FD650(HI_U32 *pu32PressStatus, HI_U32 *pu32KeyId);
HI_S32 KEYLED_KEY_SetBlockTime_FD650(HI_U32 u32BlockTimeMs);
HI_S32 KEYLED_KEY_SetRepTime_FD650(HI_U32 u32RepTimeMs);
HI_S32 KEYLED_KEY_IsRepKey_FD650(HI_U32 u32IsRepKey);
HI_S32 KEYLED_KEY_IsKeyUp_FD650(HI_U32 u32IsKeyUp);

HI_S32 KEYLED_LED_Open_FD650(HI_VOID);
HI_S32 KEYLED_LED_Close_FD650(HI_VOID);
HI_S32 KEYLED_LED_Display_FD650(HI_U32 u32CodeValue);
HI_S32 KEYLED_LED_DisplayTime_FD650(HI_UNF_KEYLED_TIME_S stKeyLedTime);
HI_S32 KEYLED_LED_SetFlashPin_FD650(HI_UNF_KEYLED_LIGHT_E enPin);
HI_S32 KEYLED_LED_SetFlashFreq_FD650(HI_UNF_KEYLED_LEVEL_E enLevel);
HI_S32 KEYLED_LED_SetLockIndicator_FD650(HI_BOOL bLock);

HI_S32 KEYLED_GetProcInfo_FD650(KEYLED_PROC_INFO_S *stInfo);

HI_S32 KEYLED_Suspend_FD650(HI_VOID);
HI_S32 KEYLED_Resume_FD650(HI_VOID);

#endif

