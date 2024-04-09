/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : jpeg_drv_suspend.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : the suspend dispose
                   CNcomment: �������� CNend\n
Function List    :


History          :
Date                   Author                 Modification
2018/01/01             sdk                    Created file
*************************************************************************************************/

/*********************************add include here***********************************************/
#include "jpeg_drv_suspend.h"

#ifdef CONFIG_JPEG_SUSPEND

#include <linux/kernel.h>
#include <linux/types.h>
#include "hi_jpeg_reg.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition *************************************************/

/******************** to see which include file we want to use***********************************/



/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/

static HI_JPG_SAVEINFO_S  sg_SaveInfo = {0};

extern HI_BOOL gs_JpegDebugInterApi;
extern HI_BOOL gs_JpegDebugUnf;

/******************************* API forward declarations ***************************************/

/******************************* API realization ************************************************/


/*****************************************************************************
* func         : JPG_SaveResumeInfo
* description  : save the resume need information
  CNcomment    : �������������Ҫ����Ϣ        CNend\n
* param[in]    : NULL
* retval       : NA
* others:      : NA
*****************************************************************************/
static HI_VOID JPG_SaveResumeInfo(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    sg_SaveInfo.u32ResumeData0   = jpeg_reg_read(JPGD_REG_BSRES_DATA0);
    sg_SaveInfo.u32ResumeData1   = jpeg_reg_read(JPGD_REG_BSRES_DATA1);
    sg_SaveInfo.u32ResBitRemain  = jpeg_reg_read(JPGD_REG_BSRES_BIT);
    sg_SaveInfo.u32ResByteConsu  = jpeg_reg_read(JPGD_REG_BSRES);
    sg_SaveInfo.u32ResMcuy       = jpeg_reg_read(JPGD_REG_MCUY);
    sg_SaveInfo.u32Pdy           = jpeg_reg_read(JPGD_REG_PD_Y);
    sg_SaveInfo.u32Pdcbcr        = jpeg_reg_read(JPGD_REG_PD_CBCR);
    sg_SaveInfo.u32DriCnt        = jpeg_reg_read(JPGD_REG_DRI_CNT);
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

/*****************************************************************************
* func         : JPG_WaitDecTaskDone
* description  : waite the jpeg decode task done
                 CNcomment: �ȴ������������  CNend\n
* param[in]    : NULL
* retval       : NA
* others:      : NA
*****************************************************************************/
HI_VOID JPG_WaitDecTaskDone(HI_VOID)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    /** waite 2ms, release cpu **/
    schedule_timeout(HZ / 500);
    JPG_SaveResumeInfo();
#if 0
    JPEG_TRACE("===============================================================\n");
    JPEG_TRACE("sg_SaveInfo.u32ResByteConsum = %d\n",sg_SaveInfo.u32ResByteConsu);
    JPEG_TRACE("sg_SaveInfo.u32ResumeData0   = %d\n",sg_SaveInfo.u32ResumeData0);
    JPEG_TRACE("sg_SaveInfo.u32ResumeData1   = %d\n",sg_SaveInfo.u32ResumeData1);
    JPEG_TRACE("sg_SaveInfo.u32ResBitRemain  = %d\n",sg_SaveInfo.u32ResBitRemain);
    JPEG_TRACE("sg_SaveInfo.u32ResMcuy       = %d\n",sg_SaveInfo.u32ResMcuy);
    JPEG_TRACE("sg_SaveInfo.u32Pdy           = %d\n",sg_SaveInfo.u32Pdy);
    JPEG_TRACE("sg_SaveInfo.u32Pdcbcr        = %d\n",sg_SaveInfo.u32Pdcbcr);
    JPEG_TRACE("sg_SaveInfo.u32DriCnt        = %d\n",sg_SaveInfo.u32DriCnt);
    JPEG_TRACE("===============================================================\n");
#endif
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}

/*****************************************************************************
* func          : JPG_GetResumeValue
* description   : get the value that resume need
                  CNcomment: ��ȡ����������Ҫ��ֵ  CNend\n
* param[in]     : *pSaveInfo
* retval        : NA
* others:       : NA
*****************************************************************************/
HI_VOID JPG_GetResumeValue(HI_JPG_SAVEINFO_S *pSaveInfo)
{
    HI_GFX_LOG_FuncEnter(gs_JpegDebugInterApi);
    if (NULL != pSaveInfo)
    {
       pSaveInfo->u32ResumeData0    = sg_SaveInfo.u32ResumeData0;
       pSaveInfo->u32ResumeData1    = sg_SaveInfo.u32ResumeData1;
       pSaveInfo->u32ResBitRemain   = sg_SaveInfo.u32ResBitRemain;
       pSaveInfo->u32ResByteConsu   = sg_SaveInfo.u32ResByteConsu;
       pSaveInfo->u32ResMcuy        = sg_SaveInfo.u32ResMcuy;
       pSaveInfo->u32Pdy            = sg_SaveInfo.u32Pdy;
       pSaveInfo->u32Pdcbcr         = sg_SaveInfo.u32Pdcbcr;
       pSaveInfo->u32DriCnt         = sg_SaveInfo.u32DriCnt;
    }
    HI_GFX_LOG_FuncExit(gs_JpegDebugInterApi);
    return;
}
#endif/**CONFIG_JPEG_SUSPEND**/
