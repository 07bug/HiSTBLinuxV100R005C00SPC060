/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : jpeg_sdec_color.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     :
Function List   :

History         :
Date                       Author                    Modification
2018/01/01                 sdk                        Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jpeglib.h"
#include "jerror.h"

#include "jpeg_sdec_api.h"
/***************************** Macro Definition     ***********************************************/

#define SkMulS16(x, y)  ((x) * (y))

/***************************** Structure Definition ***********************************************/

/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_U8 MulDiv255Round(HI_U16 a, HI_U16 b)
{
	if ((a > 32767) || (b > 32767))
	{
		return 0;
	}

	unsigned prod = SkMulS16(a, b) + 128;

	return (prod + (prod >> 8)) >> 8;
}

/****************************  add include here     ***********************************************/
#include "jpeg_sdec_dcoloryuvsp.c"
#include "jpeg_sdec_dcolorxrgb.c"
#include "jpeg_sdec_dcolorycbcr.c"
/****************************  add include end      ***********************************************/
