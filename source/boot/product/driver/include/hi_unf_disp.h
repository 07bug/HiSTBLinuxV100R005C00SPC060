/******************************************************************************
  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
  File Name     : optm_disp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/8/15
  Last Modified :
  Description   : header file for video output control
  Function List :
  History       :
  1.Date        :
  Author        :
  Modification  : Created file
******************************************************************************/

#ifndef __OPTM_DISP_H__
#define __OPTM_DISP_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */


/**max DAC count*/
/**CNcomment:����DAC��Ŀ*/
#ifndef MAX_DAC_NUM
#define MAX_DAC_NUM (6)
#endif

/**enum define about DISPLAY channel*/
/**CNcomment:����DISPLAYͨ��ö��*/
typedef enum hiUNF_DISP_E
{
    HI_UNF_DISPLAY0 = 0x0,  /**< DISPLAY0,Compatible with SD */ /**<CNcomment:����DISPLAY0�����ݱ��� */
    HI_UNF_DISPLAY1,         /**< DISPLAY1 *//**<CNcomment: ����DISPLAY1 */
    HI_UNF_DISPLAY2,         /**< DISPLAY2 *//**<CNcomment: ����DISPLAY2 */
    HI_UNF_DISPLAY_BUTT
}HI_UNF_DISP_E;

/**define the sigal type of DAC output*/
/**CNcomment:����֧�ֵ�DAC�źŸ�ʽ*/
typedef enum hiUNF_DISP_DAC_MODE_E
{
    HI_UNF_DISP_DAC_MODE_SILENCE = 0,               /**<No signal */ /**<CNcomment:�����*/
    HI_UNF_DISP_DAC_MODE_CVBS,                      /**<CVBS output */ /**<CNcomment:CVBS���*/
    HI_UNF_DISP_DAC_MODE_Y,                         /**<Y component signal output*//**<CNcomment:Y���ȷ������*/
    HI_UNF_DISP_DAC_MODE_PB,                        /**<PB component signal output*//**<CNcomment:��ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_PR,                        /**<PR componet signal output *//**<CNcomment:��ɫɫ��������*/
    HI_UNF_DISP_DAC_MODE_R,                         /**< Red component signal output*//**<CNcomment:CNcomment:��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_G,                         /**<green component signal output*//**<CNcomment:��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_G_NOSYNC,                  /**<green component signal output�� without sync signal*//**<CNcomment:��ɫ�������, ��ͬ���ź�*/
    HI_UNF_DISP_DAC_MODE_B,                         /**<blue component signal output*//**<CNcomment:��ɫ�������*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_Y,                  /**<SVIDEO Y signal output*//**<CNcomment:SVIDEO_Y�������*/
    HI_UNF_DISP_DAC_MODE_SVIDEO_C,                  /**<SVIDEO C signal output *//**<CNcomment:SVIDEO_C�������*/

    HI_UNF_DISP_DAC_MODE_BUTT
}HI_UNF_DISP_DAC_MODE_E;

typedef enum hiUNF_ENC_FMT_E
{
    HI_UNF_ENC_FMT_1080P_60 = 0,     /**<1080p 60 Hz*/
    HI_UNF_ENC_FMT_1080P_50,         /**<1080p 50 Hz*/
    HI_UNF_ENC_FMT_1080P_30,         /**<1080p 30 Hz*/
    HI_UNF_ENC_FMT_1080P_25,         /**<1080p 25 Hz*/
    HI_UNF_ENC_FMT_1080P_24,         /**<1080p 24 Hz*/

    HI_UNF_ENC_FMT_1080i_60,         /**<1080i 60 Hz*/
    HI_UNF_ENC_FMT_1080i_50,         /**<1080i 50 Hz*/

    HI_UNF_ENC_FMT_720P_60,          /**<720p 60 Hz*/
    HI_UNF_ENC_FMT_720P_50,          /**<720p 50 Hz */

    HI_UNF_ENC_FMT_576P_50,          /**<576p 50 Hz*/
    HI_UNF_ENC_FMT_480P_60,          /**<480p 60 Hz*/

    HI_UNF_ENC_FMT_PAL,              /* B D G H I PAL */
    HI_UNF_ENC_FMT_PAL_N,            /* (N)PAL        */
    HI_UNF_ENC_FMT_PAL_Nc,           /* (Nc)PAL       */

    HI_UNF_ENC_FMT_NTSC,             /* (M)NTSC       */
    HI_UNF_ENC_FMT_NTSC_J,           /* NTSC-J        */
    HI_UNF_ENC_FMT_NTSC_PAL_M,       /* (M)PAL        */

    HI_UNF_ENC_FMT_SECAM_SIN,        /**< SECAM_SIN*/
    HI_UNF_ENC_FMT_SECAM_COS,        /**< SECAM_COS*/

    HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING,
    HI_UNF_ENC_FMT_720P_60_FRAME_PACKING,
    HI_UNF_ENC_FMT_720P_50_FRAME_PACKING,

    HI_UNF_ENC_FMT_861D_640X480_60,
    HI_UNF_ENC_FMT_VESA_800X600_60,
    HI_UNF_ENC_FMT_VESA_1024X768_60,
    HI_UNF_ENC_FMT_VESA_1280X720_60,
    HI_UNF_ENC_FMT_VESA_1280X800_60,
    HI_UNF_ENC_FMT_VESA_1280X1024_60,
    HI_UNF_ENC_FMT_VESA_1360X768_60,         //Rowe
    HI_UNF_ENC_FMT_VESA_1366X768_60,
    HI_UNF_ENC_FMT_VESA_1400X1050_60,        //Rowe
    HI_UNF_ENC_FMT_VESA_1440X900_60,
    HI_UNF_ENC_FMT_VESA_1440X900_60_RB,
    HI_UNF_ENC_FMT_VESA_1600X900_60_RB,
    HI_UNF_ENC_FMT_VESA_1600X1200_60,
    HI_UNF_ENC_FMT_VESA_1680X1050_60,
    HI_UNF_ENC_FMT_VESA_1680X1050_60_RB,  //
    HI_UNF_ENC_FMT_VESA_1920X1080_60,
    HI_UNF_ENC_FMT_VESA_1920X1200_60,
    HI_UNF_ENC_FMT_VESA_1920X1440_60,//
    HI_UNF_ENC_FMT_VESA_2048X1152_60,
    HI_UNF_ENC_FMT_VESA_2560X1440_60_RB,//
    HI_UNF_ENC_FMT_VESA_2560X1600_60_RB,//sequece:42

    HI_UNF_ENC_FMT_3840X2160_24 = 0x40,
    HI_UNF_ENC_FMT_3840X2160_25,
    HI_UNF_ENC_FMT_3840X2160_30,
    HI_UNF_ENC_FMT_3840X2160_50,
    HI_UNF_ENC_FMT_3840X2160_60,

    HI_UNF_ENC_FMT_4096X2160_24,
    HI_UNF_ENC_FMT_4096X2160_25,
    HI_UNF_ENC_FMT_4096X2160_30,
    HI_UNF_ENC_FMT_4096X2160_50,
    HI_UNF_ENC_FMT_4096X2160_60,

    HI_UNF_ENC_FMT_3840X2160_23_976,
    HI_UNF_ENC_FMT_3840X2160_29_97,
    HI_UNF_ENC_FMT_720P_59_94,
    HI_UNF_ENC_FMT_1080P_59_94,
    HI_UNF_ENC_FMT_1080P_29_97,
    HI_UNF_ENC_FMT_1080P_23_976,
    HI_UNF_ENC_FMT_1080i_59_94,
    HI_UNF_ENC_FMT_BUTT
}HI_UNF_ENC_FMT_E;

/**Defines the device aspect ratio.*/
/**CNcomment: �����豸��߱�ö��*/
typedef enum hiUNF_DISP_ASPECT_RATIO_E
{
    HI_UNF_DISP_ASPECT_RATIO_AUTO,                              /**<aspect ratio as device Resolution*/ /**<CNcomment: ��߱����豸�ֱ���һ��*/
    HI_UNF_DISP_ASPECT_RATIO_4TO3,                              /**<4:3*/ /**<CNcomment: 4��3*/
    HI_UNF_DISP_ASPECT_RATIO_16TO9,                             /**<16:9*/ /**<CNcomment: 16��9*/
    HI_UNF_DISP_ASPECT_RATIO_221TO1,                            /**<221:100*/ /**<CNcomment: 221��100*/
    HI_UNF_DISP_ASPECT_RATIO_USER,                              /**<user define*/ /**<CNcomment: �û�����*/

    HI_UNF_DISP_ASPECT_RATIO_BUTT
}HI_UNF_DISP_ASPECT_RATIO_E;


/**Defines the device aspect ratio struct.*/
/**CNcomment: �����豸��߱Ƚṹ*/
typedef struct hiUNF_DISP_ASPECT_RATIO_S
{
    HI_UNF_DISP_ASPECT_RATIO_E          enDispAspectRatio;      /**<aspect ratio type of device*/ /**<CNcomment: �豸��߱�����*/
    HI_U32                              u32UserAspectWidth;     /**<user define width of device*/ /**<CNcomment: �û������豸���*/
    HI_U32                              u32UserAspectHeight;    /**<user define height of device*/ /**<CNcomment: �û������豸�߶�*/
}HI_UNF_DISP_ASPECT_RATIO_S;

/********************************ENCODER STRUCT********************************/
/** define the enum of Macrovision output type*/
/** CNcomment:��ʾ���Macrovisionģʽö�ٶ���*/
typedef enum hiUNF_DISP_MACROVISION_MODE_E
{
    HI_UNF_DISP_MACROVISION_MODE_TYPE0,  /**<type 0 *//**<CNcomment:��������0 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE1,  /**<type 1 *//**<CNcomment:��������1 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE2,  /**<type 2  *//**<CNcomment:��������2 */
    HI_UNF_DISP_MACROVISION_MODE_TYPE3,  /**<type 3  *//**<CNcomment:��������3 */
    HI_UNF_DISP_MACROVISION_MODE_CUSTOM, /**<type of configure by user  *//**<CNcomment:�û��Զ������� */
    HI_UNF_DISP_MACROVISION_MODE_BUTT
} HI_UNF_DISP_MACROVISION_MODE_E;

/* CGMS type select */
/*CNcomment:CGMS ����ѡ��*/
typedef enum hiUNF_DISP_CGMS_TYPE_E
{
    HI_UNF_DISP_CGMS_TYPE_A = 0x00,     /* CGMS type  A*//*CNcomment:CGMS ����A*/
    HI_UNF_DISP_CGMS_TYPE_B,                /* CGMS type  B*//*CNcomment:CGMS ����B*/

    HI_UNF_DISP_CGMS_TYPE_BUTT
}HI_UNF_DISP_CGMS_TYPE_E;



/* definition of CGMS mode */
typedef enum hiUNF_DISP_CGMS_MODE_E
{
   HI_UNF_DISP_CGMS_MODE_COPY_FREELY    = 0,    /* copying is permitted without restriction */
   HI_UNF_DISP_CGMS_MODE_COPY_NO_MORE   = 0x01, /* No more copies are allowed (one generation copy has been made) */
   HI_UNF_DISP_CGMS_MODE_COPY_ONCE      = 0x02, /* One generation of copies may be made */
   HI_UNF_DISP_CGMS_MODE_COPY_NEVER     = 0x03, /* No copying is permitted */

   HI_UNF_DISP_CGMS_MODE_BUTT
}HI_UNF_DISP_CGMS_MODE_E;


/** definition of CGMS configuration */
typedef struct hiUNF_DISP_CGMS_CFG_S
{
    HI_BOOL                  bEnable;    /** HI_TRUE:CGMS is enabled; HI_FALSE:CGMS is disabled */
    HI_UNF_DISP_CGMS_TYPE_E  enType;     /** type-A or type-B or None(BUTT) */
    HI_UNF_DISP_CGMS_MODE_E  enMode;     /** CGMS mode. */

}HI_UNF_DISP_CGMS_CFG_S;

typedef enum hiUNF_HDMI_ID_E
{
    HI_UNF_HDMI_ID_0,
    HI_UNF_HDMI_ID_BUTT
}HI_UNF_HDMI_ID_E;

/*bt1120 interface ID *//**CNcomment:bt1120 �ӿ�ID  */
typedef enum hiUNF_DISP_BT1120_E
{
    HI_UNF_DISP_BT1120_0,                                   /**<BT1120 interface 0 *//**CNcomment:< BT1120�ӿ�0 */
    HI_UNF_DISP_BT1120_BUTT,
}HI_UNF_DISP_BT1120_E;

/*BT656 interface ID *//**CNcomment:BT656 �ӿ�ID  */
typedef enum hiUNF_DISP_BT656_E
{
    HI_UNF_DISP_BT656_0,                                    /**<BT656 interface 0 *//**CNcomment:< BT656�ӿ�0 */
    HI_UNF_DISP_BT656_BUTT,
}HI_UNF_DISP_BT656_E;

/*LCD interface ID *//**CNcomment:LCD �ӿ�ID  */
typedef enum hiUNF_LCD_E
{
    HI_UNF_DISP_LCD_0,                                    /**<LCD interface 0 *//**CNcomment:< LCD�ӿ�0 */
    HI_UNF_DISP_LCD_BUTT,
}HI_UNF_DISP_LCD_E;

/**define the type of interface*/
/**CNcomment:����ӿ�����*/
typedef enum  hiUNF_DISP_INTF_TYPE_E
{
    HI_UNF_DISP_INTF_TYPE_HDMI,     /**<HDMI interface type *//**<CNcomment:HDMI�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_LCD,      /**<LCD interface type *//**<CNcomment:LCD�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_BT1120,   /**<bt1120 digital interface type *//**<CNcomment:BT1120���ֽӿ�����*/
    HI_UNF_DISP_INTF_TYPE_BT656,    /**<bt656 digital interface type*//**<CNcomment:BT656���ֽӿ�����*/
    HI_UNF_DISP_INTF_TYPE_YPBPR,    /**<YPBPR interface type*//**<CNcomment:YPBPR�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_RGB,      /**<RGB interface type*//**<CNcomment:RGB�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_CVBS,     /**<CVBS interface type*//**<CNcomment:CVBS�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_SVIDEO,   /**<SVIDEO interface type*//**<CNcomment:SVIDEO�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_VGA,      /**<VGA interface type*//**<CNcomment:VGA�ӿ�����*/
    HI_UNF_DISP_INTF_TYPE_BUTT
}HI_UNF_DISP_INTF_TYPE_E;

/**define the VGA type struct of interface*/
/**CNcomment:����VGA�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_VGA_S
{
    HI_U8  u8DacR;            /**<DAC num of R  *//**<CNcomment:R����dac�˿ں�*/
    HI_U8  u8DacG;            /**<DAC num of G  *//**<CNcomment:G����dac�˿ں�*/
    HI_U8  u8DacB;            /**<DAC num of B  *//**<CNcomment:B����dac�˿ں�*/
}HI_UNF_DISP_INTF_VGA_S;

/**define the YPBPR type struct of interface*/
/**CNcomment:����YPBPR�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_YPBPR_S
{
    HI_U8 u8DacY;                               /**<DAC num of Y  *//**<CNcomment:Y����dac�˿ں�*/
    HI_U8 u8DacPb;                              /**<DAC num of Pb  *//**<CNcomment:Pb����dac�˿ں�*/
    HI_U8 u8DacPr;                              /**<DAC num of Pr  *//**<CNcomment:Pr����dac�˿ں�*/
}HI_UNF_DISP_INTF_YPBPR_S;

/**define the RGB type struct of interface*/
/**CNcomment:����RGB�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_RGB_S
{
    HI_U8   u8DacR;                             /**<DAC num of R  *//**<CNcomment:R����dac�˿ں�*/
    HI_U8   u8DacG;                             /**<DAC num of G  *//**<CNcomment:G����dac�˿ں�*/
    HI_U8   u8DacB;                             /**<DAC num of B  *//**<CNcomment:B����dac�˿ں�*/
    HI_BOOL bDacSync;                           /**<G without sync signal  *//**<CNcomment:G��������ͬ���ź�*/
}HI_UNF_DISP_INTF_RGB_S;

/**define the CVBS type struct of interface*/
/**CNcomment:����CVBS�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_CVBS_S
{
    HI_U8 u8Dac;                                /**<DAC num of CVBS  *//**<CNcomment:CVBS����dac�˿ں�*/
}HI_UNF_DISP_INTF_CVBS_S;


/**define the SVIDEO type struct of interface*/
/**CNcomment:����SVIDEO�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_SVIDEO_S
{
    HI_U8 u8DacY;                               /**<DAC num of Y  *//**<CNcomment:Y����dac�˿ں�*/
    HI_U8 u8DacC;                               /**<DAC num of C  *//**<CNcomment:c����dac�˿ں�*/
}HI_UNF_DISP_INTF_SVIDEO_S;


/**define display interface struct*/
/**CNcomment:������ʾ�ӿڽṹ*/
typedef struct  hiUNF_DISP_INTF_S
{
    HI_UNF_DISP_INTF_TYPE_E enIntfType;         /**<interface type *//**<CNcomment:�ӿ�����*/
    union
    {
        HI_UNF_HDMI_ID_E        enHdmi;         /**<hdmi id *//**<CNcomment:HDMI ���*/
        HI_UNF_DISP_BT1120_E    enBT1120;       /**<bt1120 id *//**<CNcomment:BT1120���*/
        HI_UNF_DISP_BT656_E     enBT656;        /**<bt656 id *//**<CNcomment:BT656���*/
        HI_UNF_DISP_LCD_E       enLcd;          /**<lcd id *//**<CNcomment:LCD���*/

        HI_UNF_DISP_INTF_YPBPR_S    stYPbPr;    /**<intf config of YPBPR  *//**<CNcomment:YPBPR�ӿ�����*/
        HI_UNF_DISP_INTF_RGB_S      stRGB;      /**<intf config of RGB  *//**<CNcomment:RGB�ӿ�����*/
        HI_UNF_DISP_INTF_VGA_S      stVGA;      /**<intf config of VGA  *//**<CNcomment:VGA�ӿ�����*/
        HI_UNF_DISP_INTF_CVBS_S     stCVBS;     /**<intf config of CVBS  *//**<CNcomment:CVBS�ӿ�����*/
        HI_UNF_DISP_INTF_SVIDEO_S   stSVideo;   /**<intf config of SVIDEO  *//**<CNcomment:SVIDEO�ӿ�����*/
    }unIntf;
}HI_UNF_DISP_INTF_S;


typedef enum hiDISP_DAC_MODE_E
{
    DISP_DAC_MODE_SILENCE = 0,    /**<No signal */ /**<CNcomment:���ź�*/
    DISP_DAC_MODE_CVBS,           /**<CVBS output */ /**<CNcomment:CVBS���*/
    DISP_DAC_MODE_Y,              /**<Y component signal output*//**<CNcomment:Y���ȷ������*/
    DISP_DAC_MODE_PB,             /**<PB component signal output*//**<CNcomment:��ɫɫ��������*/
    DISP_DAC_MODE_PR,             /**<PR componet signal output *//**<CNcomment:��ɫɫ��������*/
    DISP_DAC_MODE_R,              /**< Red component signal output*//**<CNcomment:CNcomment:��ɫ�������*/
    DISP_DAC_MODE_G,              /**<green component signal output*//**<CNcomment:��ɫ�������*/
    DISP_DAC_MODE_B,              /**<blue component signal output*//**<CNcomment:��ɫ�������*/
    DISP_DAC_MODE_SVIDEO_Y,       /**<SVIDEO Y signal output*//**<CNcomment:SVIDEO_Y�������*/
    DISP_DAC_MODE_SVIDEO_C,       /**<SVIDEO C signal output *//**<CNcomment:SVIDEO_C �������*/
    DISP_DAC_MODE_HD_Y,           /**<HD Y component signal output*//**<CNcomment:����Y���ȷ������*/
    DISP_DAC_MODE_HD_PB,          /**<HD PB component signal output*//**<CNcomment:������ɫɫ�ȷ������*/
    DISP_DAC_MODE_HD_PR,          /**< HD PR component signal output *//**<CNcomment:�����ɫɫ�ȷ������*/
    DISP_DAC_MODE_HD_R,           /**< HD red component signal output*/ /**<CNcomment:�����ɫɫ�ȷ������*/
    DISP_DAC_MODE_HD_G,           /**< HD green component signal output*//**<CNcomment:������ɫɫ�ȷ������*/
    DISP_DAC_MODE_HD_B,           /**< HD blue component signal output*//**<CNcomment:������ɫɫ�ȷ������*/
    DISP_DAC_MODE_BUTT
}DISP_DAC_MODE_E;

/*the supported display interface.*//*CNcomment:����֧�ֵ���ʾ����ӿ� */
typedef struct  hiDISP_INTERFACE_S
{
    HI_BOOL                      bScartEnable;
    HI_BOOL                      bBt1120Enable;
    HI_BOOL                      bBt656Enable;
    DISP_DAC_MODE_E       enDacMode[MAX_DAC_NUM];
}DISP_INTERFACE_S ;

/**define LCD output data width*/
/**CNcomment:����LCD���������λ��*/
typedef enum hiUNF_DISP_INTF_DATA_WIDTH_E
{
    HI_UNF_DISP_INTF_DATA_WIDTH8 = 0,       /**<8 bits*//**<CNcomment:8λ*/
    HI_UNF_DISP_INTF_DATA_WIDTH16,          /**<16 bits*//**<CNcomment:16λ*/
    HI_UNF_DISP_INTF_DATA_WIDTH24,          /**<24 bits*//**<CNcomment:24λ*/
    HI_UNF_DISP_INTF_DATA_WIDTH_BUTT
}HI_UNF_DISP_INTF_DATA_WIDTH_E;


/**define the LCD data format*/
/**CNcomment:����LCD�����ݸ�ʽ*/
typedef enum hiHI_UNF_DISP_INTF_DATA_FMT
{
    HI_UNF_DISP_INTF_DATA_FMT_YUV422 = 0,         /**<YUV422��data width is 16*//**<CNcomment:YUV422��λ��Ϊ16*/
    HI_UNF_DISP_INTF_DATA_FMT_RGB565 = 0x8,       /**<RGB565��data width is 16*//**<CNcomment:RGB565��λ��Ϊ16*/
    HI_UNF_DISP_INTF_DATA_FMT_RGB444 = 0xa,       /**<RGB444��data width is 16*//**<CNcomment:RGB444��λ��Ϊ16*/
    HI_UNF_DISP_INTF_DATA_FMT_RGB666 = 0xb,       /**<RGB666��data width is 24*//**<CNcomment:RGB666��λ��Ϊ24*/
    HI_UNF_DISP_INTF_DATA_FMT_RGB888 = 0xc,       /**<RGB888��data widht is 24*//**<CNcomment:RGB888��λ��Ϊ24*/
    HI_UNF_DISP_INTF_DATA_FMT_BUTT
}HI_UNF_DISP_INTF_DATA_FMT_E;

/**define the struct about color */
/**CNcomment:������ʾ��ɫ�Ľṹ�� */
typedef struct  hiUNF_DISP_BG_COLOR_S
{
    HI_U8 u8Red ;            /**<red */ /**<CNcomment:��ɫ����*/
    HI_U8 u8Green ;          /**<green*//**<CNcomment:��ɫ����*/
    HI_U8 u8Blue ;           /**<blue*//**<CNcomment:��ɫ����*/
} HI_UNF_DISP_BG_COLOR_S;


/**define display output range struct */
/**CNcomment:����DISPLAY�����Χ����*/
typedef struct hiUNF_RECT_S
{
    HI_S32 x, y;
    HI_S32 w, h;
} HI_UNF_RECT_S;


/**define LCD timing */
/**CNcomment:����LCD��ʱ�����*/
typedef struct hiUNF_DISP_TIMING_S
{
    HI_U32                    VFB;                 /**<vertical front blank*//**<CNcomment:��ֱǰ����*/
    HI_U32                    VBB;                 /**<vertical back blank*//**<CNcomment:��ֱ������*/
    HI_U32                    VACT;                /**<vertical active area*//**<CNcomment:��ֱ��Ч��*/
    HI_U32                    HFB;                 /**<horizonal front blank*//**<CNcomment:ˮƽǰ����*/
    HI_U32                    HBB;                 /**<horizonal back blank*//**<CNcomment:ˮƽ������*/
    HI_U32                    HACT;                /**<horizonal active area*/ /**<CNcomment:ˮƽ��Ч��*/
    HI_U32                    VPW;                 /**<vertical sync pluse width*//**<CNcomment:��ֱ������*/
    HI_U32                    HPW;                 /**<horizonal sync pluse width*/ /**<CNcomment:ˮƽ������*/
    HI_BOOL                   IDV;                 /**< flag of data valid signal is needed flip*//**<CNcomment:��Ч�����ź��Ƿ�ת*/
    HI_BOOL                   IHS;                 /**<flag of horizonal sync pluse is needed flip*//**<CNcomment:ˮƽͬ�������ź��Ƿ�ת*/
    HI_BOOL                   IVS;                 /**<flag of vertical sync pluse is needed flip*//**<CNcomment:��ֱͬ�������ź��Ƿ�ת*/
    HI_BOOL                   ClockReversal;       /**<flag of clock is needed flip*//**<CNcomment:ʱ���Ƿ�ת*/
    HI_UNF_DISP_INTF_DATA_WIDTH_E DataWidth;           /**<data width*/ /**<CNcomment:����λ��*/
    HI_UNF_DISP_INTF_DATA_FMT_E       ItfFormat;      /**<data format.*//**<CNcomment:���ݸ�ʽ.*/

    HI_BOOL                   DitherEnable;        /**< flag of is enable Dither*//**<CNcomment:���ݸ�ʽ.*/
    HI_U32                    ClkPara0;            /**<PLL  register SC_VPLL1FREQCTRL0  value *//**<CNcomment:PLL  SC_VPLL1FREQCTRL0  �Ĵ���*/
    HI_U32                    ClkPara1;            /**<PLL  register SC_VPLL1FREQCTRL1 value*//**<CNcomment:PLL   SC_VPLL1FREQCTRL1�Ĵ���*/

    HI_BOOL                   bInterlace;           /**<progressive or interlace*//**<CNcomment:���л��߸���*/
    HI_U32                    PixFreq;              /**<pixel clock*//**<CNcomment:����ʱ��*/
    HI_U32                    VertFreq;             /**<display rate*//**<CNcomment:ˢ����*/
    HI_U32                    AspectRatioW;         /**<width of screen*//**<CNcomment:��Ļ���*/
    HI_U32                    AspectRatioH;         /**<height of screen*//**<CNcomment:��Ļ�߶�*/
    HI_BOOL                   bUseGamma;            /**<gamma modulation*//**<CNcomment:٤�����*/
    HI_U32                    Reserve0;             /**<reserved byte*//**<CNcomment:����λ*/
    HI_U32                    Reserve1;             /**<reserved byte*//**<CNcomment:����λ*/
} HI_UNF_DISP_TIMING_S;



/**define display margin stucture*/
/**CNcomment:������ʾ�հ�����ṹ�� */
typedef struct hiUNF_DISP_OFFSET_S
{
    HI_U32 u32Left;    /**<left offset *//**<CNcomment:���ƫ��*/
    HI_U32 u32Top;     /**<top offset *//**<CNcomment:�Ϸ�ƫ��*/
    HI_U32 u32Right;   /**<right offset *//**<CNcomment:�Ҳ�ƫ��*/
    HI_U32 u32Bottom;  /**<bottom offset *//**<CNcomment:�·�ƫ��*/
}HI_UNF_DISP_OFFSET_S;

HI_S32 HI_UNF_DISP_Init(HI_VOID);
HI_S32 HI_UNF_DISP_DeInit(HI_VOID);
HI_S32 HI_UNF_DISP_Open (HI_UNF_DISP_E enDisp) ;
HI_S32 HI_UNF_DISP_Close(HI_UNF_DISP_E enDisp);


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif  /* __OPTM_DISP_H__ */
