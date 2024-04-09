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

#include "MxLWare_HYDRA_OEM_Defines.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Registers.h"

/* OEM Data pointer array */
void * MxL_HYDRA_OEM_DataPtr[MXL_HYDRA_MAX_NUM_DEVICES];

static UINT8 tsMap1_to_1[MXL_HYDRA_DEMOD_MAX] =
{
  MXL_HYDRA_DEMOD_ID_0,
  MXL_HYDRA_DEMOD_ID_1,
  MXL_HYDRA_DEMOD_ID_2,
  MXL_HYDRA_DEMOD_ID_3,
  MXL_HYDRA_DEMOD_ID_4,
  MXL_HYDRA_DEMOD_ID_5,
  MXL_HYDRA_DEMOD_ID_6,
  MXL_HYDRA_DEMOD_ID_7
};

static UINT8 tsMap54x[MXL_HYDRA_DEMOD_MAX] =
{
  MXL_HYDRA_DEMOD_ID_2,
  MXL_HYDRA_DEMOD_ID_3,
  MXL_HYDRA_DEMOD_ID_4,
  MXL_HYDRA_DEMOD_ID_5,
  MXL_HYDRA_DEMOD_MAX,
  MXL_HYDRA_DEMOD_MAX,
  MXL_HYDRA_DEMOD_MAX,
  MXL_HYDRA_DEMOD_MAX
};

static MXL_REG_FIELD_T gpioPinInfo_5x1[MXL_HYDRA_DEV_5X1_GPIO_MAX] = {
  {PAD_MUX_DIGIO_00_PINMUX_SEL}, {PAD_MUX_DIGIO_01_PINMUX_SEL}, {PAD_MUX_DIGIO_02_PINMUX_SEL}, {PAD_MUX_DIGIO_03_PINMUX_SEL},
  {PAD_MUX_DIGIO_04_PINMUX_SEL}, {PAD_MUX_DIGIO_05_PINMUX_SEL}, {PAD_MUX_DIGIO_06_PINMUX_SEL}, {PAD_MUX_DIGIO_07_PINMUX_SEL},
  {PAD_MUX_DIGIO_08_PINMUX_SEL}, {PAD_MUX_DIGIO_09_PINMUX_SEL}, {PAD_MUX_DIGIO_10_PINMUX_SEL}, {PAD_MUX_DIGIO_11_PINMUX_SEL},
  {PAD_MUX_DIGIO_12_PINMUX_SEL}, {PAD_MUX_DIGIO_13_PINMUX_SEL}, {PAD_MUX_DIGIO_14_PINMUX_SEL}, {PAD_MUX_DIGIO_16_PINMUX_SEL},
  {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_18_PINMUX_SEL}, {PAD_MUX_DIGIO_19_PINMUX_SEL}, {PAD_MUX_DIGIO_20_PINMUX_SEL},
  {PAD_MUX_DIGIO_21_PINMUX_SEL}, {PAD_MUX_DIGIO_22_PINMUX_SEL}, {PAD_MUX_DIGIO_23_PINMUX_SEL}, {PAD_MUX_DIGIO_24_PINMUX_SEL},
  {PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_26_PINMUX_SEL}, {PAD_MUX_DIGIO_27_PINMUX_SEL}, {PAD_MUX_DIGIO_28_PINMUX_SEL},
  {PAD_MUX_DIGIO_29_PINMUX_SEL}, {PAD_MUX_DIGIO_30_PINMUX_SEL}, {PAD_MUX_DIGIO_31_PINMUX_SEL}, {PAD_MUX_DIGIO_32_PINMUX_SEL},
  {PAD_MUX_DIGIO_33_PINMUX_SEL}, {PAD_MUX_DIGIO_34_PINMUX_SEL}
};

static MXL_REG_FIELD_T gpioPinInfo_5x2_5x4[MXL_HYDRA_DEV_5X2_GPIO_MAX] = {
  {PAD_MUX_DIGIO_01_PINMUX_SEL}, {PAD_MUX_DIGIO_02_PINMUX_SEL}, {PAD_MUX_DIGIO_03_PINMUX_SEL}, {PAD_MUX_DIGIO_04_PINMUX_SEL},
  {PAD_MUX_DIGIO_08_PINMUX_SEL}, {PAD_MUX_DIGIO_09_PINMUX_SEL}, {PAD_MUX_DIGIO_10_PINMUX_SEL}, {PAD_MUX_DIGIO_11_PINMUX_SEL},
  {PAD_MUX_DIGIO_12_PINMUX_SEL}, {PAD_MUX_DIGIO_13_PINMUX_SEL}, {PAD_MUX_DIGIO_14_PINMUX_SEL}, {PAD_MUX_DIGIO_15_PINMUX_SEL},
  {PAD_MUX_DIGIO_16_PINMUX_SEL}, {PAD_MUX_DIGIO_17_PINMUX_SEL}, {PAD_MUX_DIGIO_18_PINMUX_SEL}, {PAD_MUX_DIGIO_19_PINMUX_SEL},
  {PAD_MUX_DIGIO_20_PINMUX_SEL}, {PAD_MUX_DIGIO_21_PINMUX_SEL}, {PAD_MUX_DIGIO_22_PINMUX_SEL}, {PAD_MUX_DIGIO_23_PINMUX_SEL},
  {PAD_MUX_DIGIO_24_PINMUX_SEL}, {PAD_MUX_DIGIO_25_PINMUX_SEL}, {PAD_MUX_DIGIO_26_PINMUX_SEL}, {PAD_MUX_DIGIO_27_PINMUX_SEL},
  {PAD_MUX_DIGIO_28_PINMUX_SEL}, {PAD_MUX_DIGIO_29_PINMUX_SEL}, {PAD_MUX_DIGIO_30_PINMUX_SEL}, {PAD_MUX_DIGIO_32_PINMUX_SEL},
  {PAD_MUX_DIGIO_33_PINMUX_SEL}
};

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDrvInit
 *
 * @param[in]   devId        Device ID
 * @param[in]   oemDataPtr   pointer to OEM data structure if required
 * @param[in]   deviceType   Hydra SKU device type
 *
 * @author Mahee
 *
 * @date 06/12/2012
 *
 * This API must be called before any other API's are called for a given
 * devId. Otherwise, a called API function must return MXL_HYDRA_NOT_INITIALIZED
 * without performing any further operation.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_ALREADY_INITIALIZED  - MxLWare is already initilized
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgDrvInit(UINT8 devId, void * oemDataPtr, MXL_HYDRA_DEVICE_E deviceType)
{
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  UINT8 i = 0;
  UINT8 j = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("oemDataPtr = %p, deviceType = %d\n", oemDataPtr, deviceType););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_NOT_INITIALIZED)
  {
    // update initilized flag
    devHandlePtr->initialized = MXL_TRUE;
    devHandlePtr->deviceType = deviceType;
    devHandlePtr->intrMask = 0;
    devHandlePtr->features.chanBond = MXL_FALSE;
    devHandlePtr->tsMap = NULL;

    // store oem data pointer
    MxL_HYDRA_OEM_DataPtr[devId] = (void *)oemDataPtr;

    // Initilize i2c access lock
    status = MxLWare_HYDRA_OEM_InitI2cAccessLock(devId);

    // update device features like, number of demods, tuners available for the given device type
    switch(devHandlePtr->deviceType)
    {
      case MXL_HYDRA_DEVICE_581:
      case MXL_HYDRA_DEVICE_581S:
      case MXL_HYDRA_DEVICE_581C:
        devHandlePtr->features.clkOutAvailable = MXL_TRUE;
        devHandlePtr->features.demodsCnt = 8;
        devHandlePtr->features.tunersCnt = 1;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_581;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X1_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x1;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_58X;
        break;

      case MXL_HYDRA_DEVICE_582:
      case MXL_HYDRA_DEVICE_582C:
        devHandlePtr->features.clkOutAvailable = MXL_TRUE;
        devHandlePtr->features.demodsCnt = 8;
        devHandlePtr->features.tunersCnt = 3;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_582;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X2_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x2_5x4;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_58X;
        break;

      case MXL_HYDRA_DEVICE_585:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 8;
        devHandlePtr->features.tunersCnt = 4;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_585;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X2_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x2_5x4;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_58X;
        break;

      case MXL_HYDRA_DEVICE_544:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 4;
        devHandlePtr->features.tunersCnt = 4;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_544;
        devHandlePtr->tsMap = tsMap54x;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X2_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x2_5x4;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_54X;
        break;

      case MXL_HYDRA_DEVICE_541:
      case MXL_HYDRA_DEVICE_541S:
      case MXL_HYDRA_DEVICE_541C:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 4;
        devHandlePtr->features.tunersCnt = 1;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_541;
        devHandlePtr->tsMap = tsMap54x;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X1_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x1;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_54X;
        break;

      case MXL_HYDRA_DEVICE_561:
      case MXL_HYDRA_DEVICE_561S:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 6;
        devHandlePtr->features.tunersCnt = 1;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_561;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X1_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x1;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_56X;
        break;

      case MXL_HYDRA_DEVICE_568:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 8;
        devHandlePtr->features.tunersCnt = 1;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_568;
        devHandlePtr->features.chanBond = MXL_TRUE;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X1_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x1;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_56X;
        break;

      case MXL_HYDRA_DEVICE_542:
      case MXL_HYDRA_DEVICE_542C:
        devHandlePtr->features.clkOutAvailable = MXL_TRUE;
        devHandlePtr->features.demodsCnt = 4;
        devHandlePtr->features.tunersCnt = 3;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_542;
        devHandlePtr->tsMap = tsMap54x;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X2_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x2_5x4;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_54X;
        break;

      case MXL_HYDRA_DEVICE_TEST:
      case MXL_HYDRA_DEVICE_584:
      default:
        devHandlePtr->features.clkOutAvailable = MXL_FALSE;
        devHandlePtr->features.demodsCnt = 8;
        devHandlePtr->features.tunersCnt = 4;
        devHandlePtr->skuType = MXL_HYDRA_SKU_TYPE_584;
        devHandlePtr->tsMap = tsMap1_to_1;
        devHandlePtr->gpioMaxNum = MXL_HYDRA_DEV_5X2_GPIO_MAX;
        devHandlePtr->gpioInfoPtr = gpioPinInfo_5x2_5x4;
        devHandlePtr->skuFamily = MXL_HYDRA_SKU_58X;
        break;
    }

#ifdef __HYDRA_FPGA__
    devHandlePtr->tsMap = tsMap1_to_1;
#endif

    switch(devHandlePtr->deviceType)
    {
      case MXL_HYDRA_DEVICE_541S:
      case MXL_HYDRA_DEVICE_561S:
      case MXL_HYDRA_DEVICE_568:
      case MXL_HYDRA_DEVICE_581S:
      case MXL_HYDRA_DEVICE_541C:
      case MXL_HYDRA_DEVICE_542C:
      case MXL_HYDRA_DEVICE_581C:
      case MXL_HYDRA_DEVICE_582C:
        devHandlePtr->maxRegPidEntries = MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT;
        devHandlePtr->maxFixPidEntries = 0;
        break;

      default:
        devHandlePtr->maxRegPidEntries = MXL_HYDRA_SHARED_PID_FILT_SIZE_HYDRA_DEFAULT;
        devHandlePtr->maxFixPidEntries = MAX_FIXED_PID_NUM;
        break;
    }

    MXL_HYDRA_PRINT("Fix pids: %d reg pids: %d\n", devHandlePtr->maxFixPidEntries, devHandlePtr->maxRegPidEntries);
    devHandlePtr->devId = devId;
    // default XTAL value is 24MHz
    devHandlePtr->xtalFreq = MXL_HYDRA_XTAL_24_MHz;

    // PID filter bank to use while programming PID filters
    devHandlePtr->pidFilterBank = MXL_HYDRA_PID_BANK_A;

    // by default TS muxing is disabled i.e 1 to 1 mux
    devHandlePtr->tsMuxModeSlice0 = MXL_HYDRA_TS_MUX_DISABLE;
    devHandlePtr->tsMuxModeSlice1 = MXL_HYDRA_TS_MUX_DISABLE;
    devHandlePtr->sharedPidFilterSize = devHandlePtr->maxRegPidEntries;

    // assign default broadcast standard as DVB-S
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_0]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_1]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_2]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_3]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_4]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_5]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_6]  = MXL_HYDRA_DVBS;
    devHandlePtr->bcastStd[MXL_HYDRA_DEMOD_ID_7]  = MXL_HYDRA_DVBS;

    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_0]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_1]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_2]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_3]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_4]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_5]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_6]  = MXL_FALSE;
    devHandlePtr->dss2dvbEnacapMode[MXL_HYDRA_DEMOD_ID_7]  = MXL_FALSE;

    // Init pid filters
    for (i = 0; i < MXL_HYDRA_DEMOD_MAX; i++)
    {
      MXLWARE_OSAL_MEMSET(&devHandlePtr->fixedPidFilt[i][0], 0, (devHandlePtr->maxFixPidEntries * sizeof(MXL_HYDRA_PID_T)));
      MXLWARE_OSAL_MEMSET(&devHandlePtr->regPidFilt[i][0], 0, (devHandlePtr->maxRegPidEntries * sizeof(MXL_HYDRA_PID_T)));

      if (i < MXL_HYDRA_DEMOD_ID_4)
      {
        // update register address for slice 0
        for (j = 0; j < devHandlePtr->maxRegPidEntries; j++)
        {
          // register address - (based Addr) + (demodID offset) + (pid filter item's offset)
          if (j < devHandlePtr->maxFixPidEntries)
            devHandlePtr->fixedPidFilt[i][j].regAddr = XPT_KNOWN_PID_BASEADDR + ((i % MXL_HYDRA_DEMOD_ID_4) * 0x80) + (j * 4);

          devHandlePtr->regPidFilt[i][j].regAddr = XPT_PID_BASEADDR + ((i % MXL_HYDRA_DEMOD_ID_4) * 0x200) + (j * 8);
        }
      }
      else
      {
        // update register address for slice 1
        for (j = 0; j < devHandlePtr->maxRegPidEntries; j++)
        {
          // register address - (based Addr) + (demodID offset) + (pid filter item's offset)
          if (j < devHandlePtr->maxFixPidEntries)
            devHandlePtr->fixedPidFilt[i][j].regAddr = XPT_KNOWN_PID_BASEADDR1 + ((i % MXL_HYDRA_DEMOD_ID_4) * 0x80) + (j * 4);

          devHandlePtr->regPidFilt[i][j].regAddr = XPT_PID_BASEADDR1 + ((i % MXL_HYDRA_DEMOD_ID_4) * 0x200) + (j * 8);
        }
      }
    }

#ifdef _MXL_HYDRA_CHAN_BOND_
    if (devHandlePtr->features.chanBond == MXL_TRUE)
    {
      MXLDBG2(MXL_HYDRA_PRINT("[%s] Channel bonding enabled. Initialize structures\n", __FUNCTION__););
      // Clear Channel bonding group
      for (i = 0; i < MXL_HYDRA_CB_GROUP_MAX; i++)
      {
        devHandlePtr->cbBondedGroup[i].cbGroupInUse = MXL_FALSE;
        devHandlePtr->cbBondedGroup[i].numOfDemodsInCB = 0;
        devHandlePtr->cbBondedGroup[i].numOfTsPorts = 0;
        for (j = 0; j < MXL_HYDRA_CB_DEMODS_MAX; j++)
        {
          devHandlePtr->cbBondedGroup[i].cbDemodId[j] = MXL_HYDRA_DEMOD_MAX;
        }
        for (j = 0; j < MXL_HYDRA_CB_TS_PORTS_MAX; j++)
        {
          devHandlePtr->cbBondedGroup[i].cbTsOutId[j] = MXL_HYDRA_TS_OUT_MAX;
        }
      }
    }
#endif

    status |= MXL_SUCCESS;
    MXLDBG1(MXL_HYDRA_PRINT("[%s] Device %s initialized\n", __FUNCTION__, MxLWare_HYDRA_DBG_GetDeviceName(deviceType)););
  }
  else if (status == MXL_SUCCESS)
  {
    status = MXL_ALREADY_INITIALIZED;
    MXLERR(MXL_HYDRA_PRINT("[%s] The device%d is already initialized\n", __FUNCTION__, devId););
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDrvUnInit
 *
 * @param[in]   devId        Device ID
 *
 * @author Mahee
 *
 * @date 06/12/2012
 *
 * This API must be called while closing MxLWare driver interface.
 *
 * @retval MXL_SUCCESS              - OK
 * @retval MXL_FAILURE              - Failure
 * @retval MXL_INVALID_PARAMETER    - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDrvUnInit(UINT8 devId)
{
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId = %d\n", devId););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    // update initilized flag
    devHandlePtr->initialized = MXL_FALSE;

    devHandlePtr->intrMask = 0;

    // store oem data pointer
    MxL_HYDRA_OEM_DataPtr[devId] = (void *)0;

    // update device features like, number of demods, tuners available for the given device type
    devHandlePtr->features.demodsCnt = 0;
    devHandlePtr->features.tunersCnt = 0;

    status = MXL_SUCCESS;

    // Clear i2c access lock
    status |= MxLWare_HYDRA_OEM_DeleteI2cAccessLock(devId);

  }
  else if (status == MXL_NOT_INITIALIZED)
  {
    status = MXL_NOT_INITIALIZED;
    MXLERR(MXL_HYDRA_PRINT("[%s] The device%d is already initialized\n", __FUNCTION__, devId););
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

UINT32 print_progress(UINT8 devId, UINT32 callbackType, void * callbackPayload)
{
 	return 0;
}

MXL_STATUS_E mxl5xx_downloadFirmware(UINT32 devId)
{
    static UINT8 buff[] =
    {
        #include "MxL_5xx_FW.h"
    };

    UINT32 size = 0;
    MXL_STATUS_E mxlStatus = MXL_SUCCESS;

    size = sizeof(buff);

    mxlStatus = MxLWare_HYDRA_API_CfgDevFWDownload(devId,
                                                    size,
                                                    buff,
                                                    print_progress);

    return mxlStatus;
}
