/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name      : drv_hifb_scrolltext.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History         :
Date                      Author                Modification
2018/01/01                sdk                   Created file
*************************************************************************************************/
#ifndef __DRV_HIFB_SCROLLTEXT_H__
#define __DRV_HIFB_SCROLLTEXT_H__


/*********************************add include here***********************************************/
#include "hi_type.h"
#include <linux/fb.h>

/************************************************************************************************/


/************************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition *************************************************/

#define SCROLLTEXT_CACHE_NUM  2   /** 双buffer  **/
#define SCROLLTEXT_NUM        2   /** 最大只支持上下两个字幕  **/

/*************************** Structure Definition ***********************************************/
typedef enum
{
    HIFB_SCROLLTEXT_HD0_HANDLE0 = 0x00,
    HIFB_SCROLLTEXT_HD0_HANDLE1 = 0x01,
    HIFB_SCROLLTEXT_HD1_HANDLE0 = 0x10,
    HIFB_SCROLLTEXT_HD1_HANDLE1 = 0x11,
    HIFB_SCROLLTEXT_HD2_HANDLE0 = 0x20,
    HIFB_SCROLLTEXT_HD2_HANDLE1 = 0x21,
    HIFB_SCROLLTEXT_SD0_HANDLE0 = 0x40,
    HIFB_SCROLLTEXT_SD0_HANDLE1 = 0x41,
    HIFB_SCROLLTEXT_BUTT_HANDLE
}HIFB_SCROLLTEXT_HANDLE;


/*************************** Structure Definition ***********************************************/
typedef struct
{
    HI_BOOL bInusing;
    HI_U32  u32PhyAddr;
    HI_U8   *pVirAddr;
}HIFB_SCROLLTEXT_CACHE;

typedef struct
{
    HI_BOOL bAvailable;
    HI_BOOL bPause;
    HI_BOOL bDeflicker;
    HI_BOOL bBliting;
    HI_U32  u32cachebufnum;
    HI_U32  u32Stride;
    HI_S32  s32TdeBlitHandle;
    HIFB_SCROLLTEXT_HANDLE enHandle;
    volatile HI_U32 u32IdleFlag;
    wait_queue_head_t wbEvent;
    HIFB_RECT  stRect;
    HIFB_COLOR_FMT_E  ePixelFmt;
    HIFB_SCROLLTEXT_CACHE stCachebuf[SCROLLTEXT_CACHE_NUM];
}HIFB_SCROLLTEXT_S;

typedef struct
{
    HI_BOOL bAvailable;
    HI_U32  u32textnum;
    HI_U32  u32ScrollTextId;
    HIFB_SCROLLTEXT_S stScrollText[SCROLLTEXT_NUM];
    struct work_struct blitScrollTextWork;
}HIFB_SCROLLTEXT_INFO_S;

/********************** Global Variable declaration *********************************************/

/******************************* API declaration ************************************************/
HI_U32 hifb_alloscrolltext_handle(HI_U32 u32LayerId);

HI_U32 hifb_parse_scrolltexthandle(HI_U32 u32Handle, HI_U32 *pU32LayerId, HI_U32 *pScrollTextId);

HI_S32 hifb_check_scrolltext_para(HI_U32 u32LayerId, HIFB_SCROLLTEXT_ATTR_S *stAttr);

HI_S32 hifb_freescrolltext_cachebuf(HIFB_SCROLLTEXT_S *pstScrollText);

HI_S32 hifb_allocscrolltext_buf(HI_U32 u32LayerId, HIFB_SCROLLTEXT_ATTR_S *stAttr);

HI_S32 hifb_create_scrolltext(HI_U32 u32LayerId, HIFB_SCROLLTEXT_CREATE_S *stScrollText);

HI_S32 hifb_fill_scrolltext(HIFB_SCROLLTEXT_DATA_S *stScrollTextData);

HI_S32 hifb_destroy_scrolltext(HI_U32 u32LayerID, HI_U32 u32ScrollTextID);

HI_S32 hifb_scrolltext_blit(HI_U32 u32LayerId);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
