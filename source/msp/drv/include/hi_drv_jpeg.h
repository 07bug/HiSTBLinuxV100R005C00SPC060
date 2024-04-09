/***************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name       : hi_drv_jpeg.h
Version         : Initial Draft
Author          : sdk
Created         : 2018/01/01
Description     :
Function List   :


History         :
Date               Author                Modification
2018/01/01          sdk                   Created file
****************************************************************************************************/
#ifndef __HI_DRV_JPEG_H__
#define __HI_DRV_JPEG_H__


/***************************** add include here*****************************************************/
#include "hi_type.h"


/***************************************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ************************************************/
    #define VID_CMD_MAGIC     'j'


    #define CMD_JPG_GETDEVICE                  _IO(VID_CMD_MAGIC,   0)
    #define CMD_JPG_GETSUSPEND                 _IO(VID_CMD_MAGIC,   1)
    #define CMD_JPG_GETRESUME                  _IO(VID_CMD_MAGIC,   2)

    #define CMD_JPG_RESET                      _IO(VID_CMD_MAGIC,   3)
    #define CMD_JPG_CANCEL_RESET               _IO(VID_CMD_MAGIC,   4)

#ifdef CHIP_TYPE_X5HD_hi3716m
    #define CMD_JPG_GETINTSTATUS               _IOWR(VID_CMD_MAGIC, 5,  JPEG_GETINTTYPE_S*)
#else
    #define CMD_JPG_GETINTSTATUS               _IOWR(VID_CMD_MAGIC, 5,  JPEG_GETINTTYPE_S)
#endif
    #define CMD_JPG_GETRESUMEVALUE             _IOWR(VID_CMD_MAGIC, 6,  HI_JPG_SAVEINFO_S)

    #define CMD_JPG_LOWDELAY_LINEINFO          _IOWR(VID_CMD_MAGIC, 7,  HI_JPEG_OUTPUTINFO_S)
    #define CMD_JPG_COMPAT_LOWDELAY_LINEINFO   _IOWR(VID_CMD_MAGIC, 7,  HI_JPEG_COMPAT_OUTPUTINFO_S)

    #define MAX_COMPONENT_NUM                 3
    #define JPEG_INTTYPE_DELAY_TIME           10000 /** 10s **/

    /***************************** Structure Definition ********************************************/
    typedef enum hiJPEG_INTTYPE_E{
        JPG_INTTYPE_NONE       = 0,
        JPG_INTTYPE_CONTINUE,
        JPG_INTTYPE_LOWDEALY,
        JPG_INTTYPE_FINISH,
        JPG_INTTYPE_ERROR,
        JPG_INTTYPE_STREAM_ERROR,
        JPG_INTTYPE_BUTT
    }JPEG_INTTYPE_E;

    typedef struct hiJPEG_GETINTTYPE_S
    {
        HI_U32 TimeOut;
        JPEG_INTTYPE_E IntType;
    }JPEG_GETINTTYPE_S;

    typedef struct hiJPG_SAVEINFO_S{
        HI_U32  u32ResumeData0;
        HI_U32  u32ResumeData1;
        HI_U32  u32ResBitRemain;
        HI_U32  u32ResByteConsu;
        HI_U32  u32ResMcuy;
        HI_U32  u32Pdy;
        HI_U32  u32Pdcbcr;
        HI_U32  u32DriCnt;
    }HI_JPG_SAVEINFO_S;

    typedef struct hiJPEG_OUTPUTINFO_S{
         HI_CHAR* pVirLineBuf;
         HI_U32 u32OutHeight[MAX_COMPONENT_NUM];
    }HI_JPEG_OUTPUTINFO_S;

    typedef struct hiJPEG_COMPAT_OUTPUTINFO_S{
         HI_U32 u32VirLineBuf;
         HI_U32 u32OutHeight[MAX_COMPONENT_NUM];
    }HI_JPEG_COMPAT_OUTPUTINFO_S;

    typedef struct hiJPEG_PROC_INFO_S{
         HI_BOOL bProcOn;
         HI_U32 DecPthreadNums;
         HI_S32 DecLockTimes;
         HI_S32 OpenDevConTimes;
    }HI_JPEG_PROC_INFO_S;
    /***************************** Global Variable declaration *************************************/

    /***************************** API forward declarations *****************************************/

    /***************************** API realization *************************************************/

    /***********************************************************************************************/


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HI_DRV_JPEG_H__*/
