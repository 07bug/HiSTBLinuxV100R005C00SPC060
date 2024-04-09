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

#ifndef __MxLWARE_HYDRA_OEM_DRV_H__
#define __MxLWARE_HYDRA_OEM_DRV_H__

/*****************************************************************************************
    Include Header Files
*****************************************************************************************/

#ifdef __KERNEL__
  #include <linux/kernel.h>
  #include <linux/module.h>
#else
  #include <stdlib.h>
  #include <string.h>
#endif

#include "MaxLinearDataTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************
    Macros
*****************************************************************************************/
#define MXLWARE_OSAL_MALLOC     malloc
#define MXLWARE_OSAL_MEMCPY     memcpy
#define MXLWARE_OSAL_MEMSET     memset

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/*****************************************************************************************
    Global Variable Declarations
*****************************************************************************************/
extern void * MxL_HYDRA_OEM_DataPtr[];

/*****************************************************************************************
    Prototypes
*****************************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_OEM_DeviceReset(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_OEM_I2cWrite(UINT8 devId, UINT16 dataLen, UINT8 *buffPtr);

MXL_STATUS_E MxLWare_HYDRA_OEM_I2cRead(UINT8 devId, UINT16 dataLen, /*@out@*/UINT8 *buffPtr);

MXL_STATUS_E MxLWare_HYDRA_OEM_InitI2cAccessLock(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_OEM_Lock(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_OEM_Unlock(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_OEM_DeleteI2cAccessLock(UINT8 devId);

void MxLWare_HYDRA_OEM_SleepInMs(UINT16 delayTimeInMs);

void MxLWare_HYDRA_OEM_GetCurrTimeInMs(UINT64 *msecsPtr);

void *MxLWare_HYDRA_OEM_MemAlloc(UINT32 sizeInBytes);

void MxLWare_HYDRA_OEM_MemFree(void *memPtr);

#ifdef __cplusplus
}
#endif

#endif // __MxLWARE_HYDRA_OEM_DRV_H__

