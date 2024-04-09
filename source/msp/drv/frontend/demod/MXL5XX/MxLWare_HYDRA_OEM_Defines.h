/*
* Copyright (c) 2011-2013 MaxLinear, Inc. All rights reserved
*
* License type: GPLv2
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License as published by the Free Software
* Foundation.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with
* this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*
* This program may alternatively be licensed under a proprietary license from
* MaxLinear, Inc.
*
* See terms and conditions defined in file 'LICENSE.txt', which is part of this
* source code package.
*/


#ifndef __MXL_HYDRA_OEM_DEFINES_H__
#define __MXL_HYDRA_OEM_DEFINES_H__

/*****************************************************************************************
    Include Header Files
*****************************************************************************************/
#ifdef __MXL_OEM_DRIVER__
#include "MxL_Debug.h"
#endif
#ifndef _MSC_VER 
#ifdef __KERNEL__
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#else
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#endif
#endif

#include "hi_type.h"

#include "hi_drv_i2c.h"
#include "hi_drv_gpio.h"
#include "hi_debug.h"
#include "hi_drv_proc.h"
#include "hi_drv_tuner.h"
#include "drv_demod.h"
#include "hi_kernel_adapt.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************
    Macros
*****************************************************************************************/

#define MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH 360 /* maximum number bytes allowed in one I2C block write */

// Flag to set Big Endian host platform
// 0 -> Little Endian host platform
// 1 -> Big Endian host platform
#define MXL_ENABLE_BIG_ENDIAN        (0)

// NOTE: VC 2003 does not support Variadic Macros
#ifdef __MXL_OEM_DRIVER__
#define MXL_HYDRA_DEBUG               MxL_DLL_DEBUG0
#define MXL_HYDRA_ERROR               MxL_DLL_DEBUG0
#define MXL_HYDRA_PRINT               MxL_DLL_DEBUG0
#else
#ifdef __KERNEL__
#define MXL_HYDRA_DEBUG               HI_INFO_TUNER//printk
#define MXL_HYDRA_ERROR               HI_INFO_TUNER//printk
#define MXL_HYDRA_PRINT               HI_INFO_TUNER//printk
#else
#define MXL_HYDRA_DEBUG               printf
#define MXL_HYDRA_ERROR               printf
#define MXL_HYDRA_PRINT               printf
#endif
#endif

#ifdef MXL_DO_NOT_DEFINE_BASIC_DATATYPES
/* OEM specific data types to declare here */
#ifdef _MSC_VER
#ifndef __midl
typedef unsigned __int8     UINT8;
typedef unsigned __int16    UINT16;
typedef unsigned __int32    UINT32;
typedef unsigned __int64    UINT64;

typedef __int8              SINT8;
typedef __int16             SINT16;
#else
typedef small               SINT8;
typedef short               SINT16;
#endif

typedef __int32             SINT32;
typedef __int64             SINT64;
#else
typedef uint8_t             UINT8;
typedef uint16_t            UINT16;
typedef uint32_t            UINT32;
typedef uint64_t            UINT64;

typedef int8_t              SINT8;
typedef int16_t             SINT16;
typedef int32_t             SINT32;
typedef int64_t             SINT64;
#endif

typedef float               REAL32;
typedef double              REAL64;
#endif

#define MXL_MODULE_DEBUG_LEVEL 0////3
#define MXL_MODULE_DEBUG_OPTIONS 0//MXLDBG_ERROR+MXLDBG_ENTER+MXLDBG_EXIT+MXLDBG_API
#define MXL_MODULE_DEBUG_FCT MXL_HYDRA_DEBUG

#include "MaxLinearDataTypes.h"

typedef struct
{
  UINT8 drvIndex;
  UINT8 channel;
  UINT16 i2cAddress;
} oem_data_t;

#define not_MXL_HYDRA_WAKE_ON_WAN_ENABLED_

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/

/*****************************************************************************************
    Prototypes
*****************************************************************************************/
#ifdef __cplusplus
}
#endif

#endif // __MXL_HYDRA_OEM_DEFINES_H__

