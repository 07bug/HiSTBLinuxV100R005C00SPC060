/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_adp.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/

/*********************************add include here**********************************************/
#include "tde_hal.h"
#include "tde_define.h"
#include "tde_adp.h"
#include "tde_check_para.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition ********************************************/

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/********************** Global Variable declaration ****************************************/

static HI_U32 gs_u32Capability =  ROP      | ALPHABLEND | COLORIZE  | CLUT
                                | COLORKEY | CLIP       | DEFLICKER | RESIZE
                                | MIRROR   | CSCCOVERT  | QUICKFILL | QUICKCOPY
                                | PATTERFILL;

extern HI_BOOL gs_TdeDebugInterApi;
/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/
HI_S32 TdeHalGetCapability(HI_U32 *pstCapability)
{
    HI_GFX_LOG_FuncEnter(gs_TdeDebugInterApi);
    TDE_CHECK_NULLPOINTER_RETURN_VALUE(pstCapability, HI_FAILURE);
    *pstCapability = gs_u32Capability;
    HI_GFX_LOG_FuncExit(gs_TdeDebugInterApi);
    return HI_SUCCESS;
}
