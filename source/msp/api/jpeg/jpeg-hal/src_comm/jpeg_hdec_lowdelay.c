/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_dec_lowdelay.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : ���ӳٹ���
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "jpeg_hdec_api.h"
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/


/******************************* API realization **************************************************/
static HI_VOID JPEG_DEC_SetLowDelayBufferDate(HI_ULONG HdecHandle)
{
     HI_U32* pu32VirLineBuf = NULL;

     JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
     if (NULL == pJpegHandle)
     {
        return;
     }

     if (HI_FALSE == pJpegHandle->bLowDelayEn)
     {
         return;
     }

     pu32VirLineBuf = (HI_U32*)pJpegHandle->pVirLineBuf;
     if (NULL == pu32VirLineBuf)
     {
         return;
     }

     *pu32VirLineBuf = pJpegHandle->stJpegSofInfo.u32YMcuHeight;
     *(pu32VirLineBuf + 4) = pJpegHandle->stJpegSofInfo.u32CMcuHeight;

     return;
}

static HI_BOOL JPEG_HDEC_SupportLowDelay(HI_ULONG HdecHandle)
{
#ifdef CONFIG_JPEG_LOW_DELAY_SUPPORT
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_FALSE;
    }

    if (HI_FALSE == pJpegHandle->bLowDelayEn)
    {
       return HI_TRUE;
    }

    /**<-- only support decode to user physical memory >**/
    /**<--ֻ֧�ֽ���������û������������ڴ棬�����޷�ʵ�ֵ��ӳ����ݶ�ȡ>**/
    if (HI_FALSE == pJpegHandle->bOutUsrBuf)
    {
       pJpegHandle->bLowDelayEn = HI_FALSE;
       return HI_FALSE;
    }

    /**<-- not support scale for low delay >**/
    /**<--���ӳٲ�֧������>**/
    if (0 != pJpegHandle->ScalRation)
    {
       pJpegHandle->bLowDelayEn = HI_FALSE;
       return HI_FALSE;
    }

    /**<-- not support all output to yuv420sp >**/
    /**<--��֧��ͳһ�����yuv420sp >**/
    if (HI_TRUE == pJpegHandle->bOutYUV420SP)
    {
       pJpegHandle->bLowDelayEn = HI_FALSE;
       return HI_FALSE;
    }

    /**<-- only support decode to yuv semi-planer  >**/
    /**<--ֻ֧�����yuv semi-planer >**/
    if (HI_TRUE != pJpegHandle->bOutYCbCrSP)
    {
        pJpegHandle->bLowDelayEn = HI_FALSE;
        return HI_FALSE;
    }
#else
    HI_UNUSED(HdecHandle);
#endif

    return HI_TRUE;
}
