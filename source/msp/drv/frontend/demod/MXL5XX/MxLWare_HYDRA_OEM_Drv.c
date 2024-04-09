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
#include <linux/time.h>
#include <linux/string.h>
#include <asm/unistd.h>

#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>
#include <asm/delay.h>

//hisilicon
#include "hi_type.h"

#include "hi_drv_i2c.h"
#include "hi_drv_gpio.h"
#include "hi_debug.h"
#include "hi_drv_proc.h"
#include "hi_drv_tuner.h"
#include "hi_mpi_mem.h"
#include "drv_tuner_ioctl.h"

#include "MxLWare_HYDRA_OEM_Defines.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "hi_drv_mmz.h"

#ifdef __MXL_OEM_DRIVER__
#include "MxL_HYDRA_I2cWrappers.h"
#endif

//MMZ_BUFFER_S            g_stMmzBuf;

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_DeviceReset
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API performs a hardware reset on Hydra SOC identified by devId.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_DeviceReset(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  devId = devId;
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_SleepInMs
 *
 * @param[in]   delayTimeInMs
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * his API will implement delay in milliseconds specified by delayTimeInMs.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
void MxLWare_HYDRA_OEM_SleepInMs(UINT16 delayTimeInMs)
{
    delayTimeInMs=delayTimeInMs;

    tuner_mdelay(delayTimeInMs);
    return;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_GetCurrTimeInMs
 *
 * @param[out]   msecsPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should return system time milliseconds.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
void MxLWare_HYDRA_OEM_GetCurrTimeInMs(UINT64 *msecsPtr)
{
    struct timeval stCurrTime;
    msecsPtr = msecsPtr;

    /*#ifdef __MXL_OEM_DRIVER__
    *msecsPtr = GetTickCount();
    #endif*/
    do_gettimeofday(&stCurrTime);
    *msecsPtr = stCurrTime.tv_sec * 1000 + stCurrTime.tv_usec / 1000;
    return;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_I2cWrite
 *
 * @param[in]   devId           Device ID
 * @param[in]   dataLen
 * @param[in]   buffPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API performs an I2C block write by writing data payload to Hydra device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_OEM_I2cWrite(UINT8 devId, UINT16 dataLen, UINT8 *buffPtr)
{
    // format.
    // I2C Block Write Protocol:
    // +------+-+-----+-+-+-----+-+-----+-+---+-+-----+-+-+
    // |MASTER|S|SADDR|W| |Data0| |Data1| |...| |DataN| |P|
    // +------+-+-----+-+-+-----+-+-----+-+---+-+-----+-+-+
    // |SLAVE |         |A|     |A|     |A|   |A|     |A| |
    // +------+---------+-+-----+-+-----+-+---+-+-----+-+-+
    // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK), 
    // P(Stop condition)
    MXL_STATUS_E mxlStatus = MXL_SUCCESS;
    oem_data_t *oemDataPtr = (oem_data_t *)0;
    HI_S32 s32Ret = HI_SUCCESS;

    oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];
    buffPtr = buffPtr;
    dataLen = dataLen;

    if (oemDataPtr)
    {
        /*#ifdef __MXL_OEM_DRIVER__
        mxlStatus = MxL_HYDRA_I2C_WriteData(oemDataPtr->drvIndex, devId, oemDataPtr->i2cAddress, oemDataPtr->channel, dataLen, buffPtr);
        #endif*/
        UINT8 i2cIndex = oemDataPtr->channel; // get device i2c address
        UINT8 i2cAddress = oemDataPtr->i2cAddress;
        //printk("%s,line:%d,i2c channel:%d,i2c addr:0x%x.\n",__func__,__LINE__,i2cIndex,i2cAddress);

        if(HI_STD_I2C_NUM >i2cIndex)
        {
            s32Ret = s_tuner_pI2cFunc->pfnI2cWrite(i2cIndex, i2cAddress, 0,0, buffPtr, dataLen);

            if(HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("---->[Failed] i2c:%d,addr:0x%x\n",i2cIndex,i2cAddress);
                return MXL_FAILURE;
            }
        }
        else
        {
            s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cWriteExt(i2cIndex,i2cAddress, 0, 0, buffPtr, dataLen);
            if(HI_SUCCESS != s32Ret)
            {
                return MXL_FAILURE;
            }
        }
    }
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_I2cRead
 *
 * @param[in]   devId           Device ID
 * @param[in]   dataLen
 * @param[out]  buffPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API shall be used to perform I2C block read transaction.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_I2cRead(UINT8 devId, UINT16 dataLen, UINT8 *buffPtr)
{
    // format.

    // I2C Block Read Protocol:
    // +------+-+-----+-+-+-----+-----+--+-+
    // |MASTER|S|SADDR|R| |     |     |MN|P|
    // +------+-+-----+-+-+-----+-----+--+-+
    // |SLAVE |         |A|Data |Data |  | |
    // +------+---------+-+-----+-----+--+-+
    // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK), 
    // P(Stop condition)
    MXL_STATUS_E mxlStatus = MXL_SUCCESS;
    oem_data_t *oemDataPtr = (oem_data_t *)0;
    HI_S32 s32Ret = HI_SUCCESS;

    oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];
    buffPtr = buffPtr;
    dataLen = dataLen;

    if (oemDataPtr)
    {
        #ifdef __MXL_OEM_DRIVER__
        mxlStatus = MxL_HYDRA_I2C_ReadData(oemDataPtr->drvIndex, devId, oemDataPtr->i2cAddress, oemDataPtr->channel, dataLen, buffPtr);
        #endif
        UINT8 i2cIndex = oemDataPtr->channel; // get device i2c address
        UINT8 i2cAddress = oemDataPtr->i2cAddress;
        //printk("%s,line:%d,i2c channel:%d,i2c addr:0x%x.\n",__func__,__LINE__,i2cIndex,i2cAddress);

        if(HI_STD_I2C_NUM > i2cIndex)
        {
            s32Ret = s_tuner_pI2cFunc->pfnI2cReadDirectly(i2cIndex, i2cAddress, 0, 0, buffPtr, dataLen);
            if(HI_SUCCESS != s32Ret)
            {
                *buffPtr = 0;
                HI_ERR_TUNER("---->[Failed] i2c:%d,addr:0x%x\n",i2cIndex,i2cAddress);
                return MXL_FAILURE;
            }
            else
            {
                //HI_ERR_TUNER("----->read regester reg:0x%04x,size:0x%x, date[0:0x%02x, 1:0x%02x]\n",(UINT16)readAddr,2,sout[0],sout[1]);
            }
        }

        else
        {
            s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(i2cIndex, i2cAddress,0, 0, buffPtr, dataLen);
            if(HI_SUCCESS != s32Ret)
            {
                *buffPtr = 0;
                return MXL_FAILURE;
            }
        }
    }
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_InitI2cAccessLock
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 04/11/2013 Initial release
 *
 * This API will initilize locking mechanism used to serialize access for
 * I2C operations.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_InitI2cAccessLock(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  oem_data_t *oemDataPtr = (oem_data_t *)0;

  oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];

  if (oemDataPtr)
  {

  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_DeleteI2cAccessLock
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 04/11/2013 Initial release
 *
 * This API will release locking mechanism and associated resources.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_DeleteI2cAccessLock(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  oem_data_t *oemDataPtr = (oem_data_t *)0;

  oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];
  if (oemDataPtr)
  {

  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_Lock
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 04/11/2013 Initial release
 *
 * This API will should be used to lock access to device i2c access
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_Lock(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  oem_data_t *oemDataPtr = (oem_data_t *)0;

  oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];
  if (oemDataPtr)
  {

  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_Unlock
 *
 * @param[in]   devId           Device ID
 *
 * @author Mahee
 *
 * @date 04/11/2013 Initial release
 *
 * This API will should be used to unlock access to device i2c access
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_OEM_Unlock(UINT8 devId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  oem_data_t *oemDataPtr = (oem_data_t *)0;

  oemDataPtr = (oem_data_t *)MxL_HYDRA_OEM_DataPtr[devId];

  if (oemDataPtr)
  {

  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_MemAlloc
 *
 * @param[in]   sizeInBytes
 *
 * @author Sateesh
 *
 * @date 04/23/2015 Initial release
 *
 * This API shall be used to allocate memory.
 *
 * @retval memPtr                 - Memory Pointer
 *
 ************************************************************************/
void* MxLWare_HYDRA_OEM_MemAlloc(UINT32 sizeInBytes)
{
    void *memPtr = NULL;
    sizeInBytes = sizeInBytes;

    /*#ifdef __MXL_OEM_DRIVER__
    memPtr = malloc(sizeInBytes * sizeof(UINT8));
    #endif*/
    /*memPtr = HI_MALLOC(HI_ID_TUNER,sizeInBytes * sizeof(UINT8));
    if(!memPtr)
    {
        HI_ERR_TUNER("HI_MALLOC %d Bytes fail.\n",sizeInBytes);
    }*/
    printk("sizeInBytes=%d\n", sizeInBytes);

    /*if (HI_SUCCESS != HI_DRV_MMZ_AllocAndMap("MXL582", MMZ_OTHERS, sizeInBytes * sizeof(UINT8), 0, &g_stMmzBuf))
    {
        HI_ERR_TUNER("memory allocate failed\n");

        return NULL;
    }

    memPtr = (void *)g_stMmzBuf.u32StartPhyAddr;*/
    
    return memPtr;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_OEM_MemFree
 *
 * @param[in]   memPtr
 *
 * @author Sateesh
 *
 * @date 04/23/2015 Initial release
 *
 * This API shall be used to free memory.
 *
 *
 ************************************************************************/
void MxLWare_HYDRA_OEM_MemFree(void *memPtr)
{
    memPtr = memPtr;
    /*#ifdef __MXL_OEM_DRIVER__
    free(memPtr);
    #endif*/
    //HI_FREE(HI_ID_TUNER, memPtr);
    //HI_DRV_MMZ_UnmapAndRelease(&g_stMmzBuf);
}
