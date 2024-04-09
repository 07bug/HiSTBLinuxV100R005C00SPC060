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
#include "MxLWare_HYDRA_Commands.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_Registers.h"
#include "MxLWare_FW_Download.h"
#include "MxLWare_HYDRA_DemodTunerApi.h"

/* MxLWare Driver version for Hydra device */
static const UINT8 MxLWare_HYDRA_Version[] = {2, 2, 1, 18, 1};

#define MXL_HYDRA_DELAY_BETWEEN_CONSECUTIVE_FW_CHECKS_MS 50
#define MAX_ACTIVE_DURATION_OF_EDGE_INTERRUPT 50*1000  //50 uS

static MXL_BOOL_E MxL_Ctrl_IsFirmwareAlive(UINT8 devId, UINT16 timeoutMs)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 fwHeartBeat = 0;
  UINT32 regData = 0;
  MXL_BOOL_E fwActiveFlag = MXL_FALSE;
  MXLDBG2(UINT8 attempt = 0;);

  MXLENTERSTR;
  MXLENTER(MXL_HYDRA_PRINT("timeoutMs=%d\n", timeoutMs);)
  
  while ((mxlStatus == MXL_SUCCESS) && 
          (timeoutMs > MXL_HYDRA_DELAY_BETWEEN_CONSECUTIVE_FW_CHECKS_MS) && 
          (fwActiveFlag == MXL_FALSE))
  {
    mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_HEAR_BEAT, &fwHeartBeat);
    MxLWare_HYDRA_OEM_SleepInMs(10);
    mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_HEAR_BEAT, &regData);
    
    MXLDBG2(attempt++;);
    if ((fwHeartBeat) && (regData) && (!mxlStatus))
    {
      if ((regData - fwHeartBeat) == 0)
      {
        fwActiveFlag = MXL_FALSE;
        MxLWare_HYDRA_OEM_SleepInMs(MXL_HYDRA_DELAY_BETWEEN_CONSECUTIVE_FW_CHECKS_MS);
      }
      else
      {
        fwActiveFlag = MXL_TRUE;
      }
    }
    MXLDBG2(
      if (fwActiveFlag == MXL_FALSE)
      {
        MXL_HYDRA_PRINT("Firmware not alive. Attempt %d\n", attempt);
      }
      );
    timeoutMs -= MXL_HYDRA_DELAY_BETWEEN_CONSECUTIVE_FW_CHECKS_MS;
  }
  MXLDBG2(MXL_HYDRA_PRINT("Firmware %s after %d attempts\n", (fwActiveFlag == MXL_TRUE)?"running":"dead", attempt););
  MXLERR(if (mxlStatus != MXL_SUCCESS) MXL_HYDRA_ERROR("Error reading register\n"););
  MXLEXITSTR(fwActiveFlag);
  return fwActiveFlag;
}

static MXL_BOOL_E MxL_Ctrl_ValidateSku(MXL_HYDRA_CONTEXT_T * devHandlePtr)
{
  MXL_BOOL_E skuOK = MXL_TRUE;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 padMuxBond = 0;
  UINT32 prcmChipId = 0;
  UINT32 prcmSoCId = 0;

  mxlStatus = GET_REG_FIELD_DATA(devHandlePtr->devId, PAD_MUX_BOND_OPTION, &padMuxBond);
  mxlStatus |= GET_REG_FIELD_DATA(devHandlePtr->devId, PRCM_PRCM_CHIP_ID, &prcmChipId);
  mxlStatus |= GET_REG_FIELD_DATA(devHandlePtr->devId, PRCM_AFE_SOC_ID, &prcmSoCId);

  MXLDBG1(MXL_HYDRA_PRINT("SKU Validation %d \n", devHandlePtr->deviceType););

  if (mxlStatus == MXL_SUCCESS)
  {
    if (prcmChipId != 0x560)
    {
      switch(padMuxBond)
      {
        case MXL_HYDRA_SKU_ID_581:
          skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581S))?MXL_TRUE:MXL_FALSE;
          if(skuOK == MXL_TRUE)
          {
            devHandlePtr->deviceType = MXL_HYDRA_DEVICE_581;
          }
          MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL581 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          break;

        case MXL_HYDRA_SKU_ID_584:
          skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_584)?MXL_TRUE:MXL_FALSE;
          MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL584 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          break;

        case MXL_HYDRA_SKU_ID_585:
          skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_585)?MXL_TRUE:MXL_FALSE;
          MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL585 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          break;

        case MXL_HYDRA_SKU_ID_544:
          skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542))?MXL_TRUE:MXL_FALSE;
          if(devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542)
          {
            MxLWare_HYDRA_WriteRegister(devHandlePtr->devId, HYDRA_SKU_MGMT, 1);
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL542 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          }
          else
          {
            MxLWare_HYDRA_WriteRegister(devHandlePtr->devId, HYDRA_SKU_MGMT, 0);
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL544 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          }
          break;

        case MXL_HYDRA_SKU_ID_582:
          skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582)?MXL_TRUE:MXL_FALSE;
          MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL582 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
          break;

        case MXL_HYDRA_SKU_ID_561:
          if (mxlStatus == MXL_SUCCESS)
          {
            if(((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561S)))
            {
              skuOK = MXL_TRUE;
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_561;

              MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL561 correct\n"););
            }
            else
            {
              skuOK = MXL_FALSE;
              MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL561 incorrect\n"););
            }
          }
          break;

        default:
          skuOK = MXL_FALSE;
          break;
      }
    }
    else // Scorpius/Ceres PRCM CHIP ID == 0x560
    {
      if ((prcmSoCId == 0x4) && ((padMuxBond & 0x8) == 0x0)) // Scorpius
      {
        MXLDBG1(MXL_HYDRA_PRINT("SKU %d \n", devHandlePtr->deviceType););
        switch(padMuxBond)
        {
          case MXL_HYDRA_SKU_ID_544:
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541) \
                     || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541C))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_541S;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL541S %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_581:
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581) \
                     || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581C))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_581S;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL581S %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_561:
            // Sku = 561S
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_561S;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL561S %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););

            break;

          case MXL_HYDRA_SKU_ID_568:
            MXL_HYDRA_PRINT("SKU prcmSoCId %d \n", prcmSoCId);
            skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_568)?MXL_TRUE:MXL_FALSE;

            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL568 B0 %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          default:
            skuOK = MXL_FALSE;
            break;
        }
      }
      else if ((prcmSoCId == 0x5) && ((padMuxBond & 0x8) == 0x8)) // Ceres
      {
        MXLDBG1(MXL_HYDRA_PRINT("SKU %d \n", devHandlePtr->deviceType););
        switch(padMuxBond & 0x7)
        {
          case MXL_HYDRA_SKU_ID_544:
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541) \
                     || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_541C))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_541C;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL541C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_581:
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581) \
                     || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_581C))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_581C;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL581C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_561:
            skuOK = ((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561S) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_561))?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_561S;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL561C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_568:
            skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_568)?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_568;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL568C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_582:
            skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_582C)?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_582C;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL582C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          case MXL_HYDRA_SKU_ID_584:
            skuOK = (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C)?MXL_TRUE:MXL_FALSE;
            if(skuOK == MXL_TRUE)
            {
              devHandlePtr->deviceType = MXL_HYDRA_DEVICE_542C;
            }
            MXLDBG1(MXL_HYDRA_PRINT("SKU selection MxL542C %s\n", (skuOK == MXL_TRUE)?"correct":"incorrect"););
            break;

          default:
            skuOK = MXL_FALSE;
            break;
        }
      }
    }
  }
  else
    skuOK = MXL_FALSE;

  return skuOK;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevXtal
 *
 * @param[in]   devId        Device ID
 * @param[in]   xtalParamPtr
 * @param[in]   enableClkOut
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *       11/15/2012 - Update XTAL config code based on new peograming seq.
 *                    Move XTAL cal to FW.
 *
 * This API should be used to configure device XTAL configuration including
 * XTAL frequency, XTAL Capacitance and also control CLK_OUT feature.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevXtal(UINT8 devId, MXL_HYDRA_DEV_XTAL_T * xtalParamPtr, MXL_BOOL_E enableClkOut)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("xtalFreqId=%d, xtalCap=%d, clkOut=%s\n",
                                            (xtalParamPtr) ? xtalParamPtr->xtalFreq : 0,
                                            (xtalParamPtr) ? xtalParamPtr->xtalCap : 0,
                                            (enableClkOut == MXL_ENABLE) ? "on" : "off" ););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    // if clock out feature is not available and user sends enable clock out
    if ((devHandlePtr->features.clkOutAvailable == MXL_FALSE) && (enableClkOut == MXL_ENABLE))
    {
      status = MXL_NOT_SUPPORTED;
      MXLERR(MXL_HYDRA_PRINT("[%s] Clkout is not supported in this device\n", __FUNCTION__););
    }
    else
    {
      // Program Clock out
      // AFE_REG_D2A_XTAL_CAL_TSTEP = 1
      status |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_XTAL_EN_CLKOUT_1P8, enableClkOut);

      if ((xtalParamPtr) && (xtalParamPtr->xtalCap >= MXL_HYDRA_CAP_MIN) && (xtalParamPtr->xtalCap <= MXL_HYDRA_CAP_MAX))
      {
        // program XTAL frequency
        if (xtalParamPtr->xtalFreq == MXL_HYDRA_XTAL_24_MHz)
          status |= MxLWare_HYDRA_WriteRegister(devId, HYDRA_CRYSTAL_SETTING, 0);
        else
          status |= MxLWare_HYDRA_WriteRegister(devId, HYDRA_CRYSTAL_SETTING, 1);

        // Update device context for XTAL value
        devHandlePtr->xtalFreq = xtalParamPtr->xtalFreq;

        // program XTAL cap value
        status |= MxLWare_HYDRA_WriteRegister(devId, HYDRA_CRYSTAL_CAP, xtalParamPtr->xtalCap);
      }
      else
      {
        status |= MXL_INVALID_PARAMETER;
        MXLERR(MXL_HYDRA_PRINT("[%s] xtalCap should be in range <%d;%d>\n", __FUNCTION__, MXL_HYDRA_CAP_MIN, MXL_HYDRA_CAP_MAX););
      }
    }
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevFWDownload
 *
 * @param[in]   devId        Device ID
 * @param[in]   mbinBufferSize
 * @param[in]   mbinBufferPtr
 * @param[in]   fwCallbackFn
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 * @date 07/16/2012 Update API to new programming flow change
 *
 * This API downloads Hydra firmware stored in buffer (mbinBufferPtr) to the
 * device through I2C interface. If fwCallbackFn is defined (not NULL), it
 * will be called after each segment is downloaded.  This callback routine
 * can be used to monitor firmware download progress.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevFWDownload(UINT8 devId, UINT32 mbinBufferSize, UINT8 *mbinBufferPtr, MXL_CALLBACK_FN_T fwCallbackFn)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  UINT32 regData = 0;
  MXL_HYDRA_SKU_COMMAND_T devSkuCfg;
  UINT8 cmdSize = sizeof(MXL_HYDRA_SKU_COMMAND_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("mbinBufferSize=%d, mbinBufferPtr=%p, callback %s\n", mbinBufferSize, mbinBufferPtr, (fwCallbackFn)?"defined":"not defined"););

  // Get MxLWare driver context
  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // validate input parameters
    if ((mbinBufferSize) && (mbinBufferPtr))
    {
      // Keep CPU under reset
      //mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId, PRCM_PRCM_CPU_SOFT_RST_N, 0);
      mxlStatus |= SET_REG_FIELD_DATA(devId, PRCM_PRCM_CPU_SOFT_RST_N, 0);
      if (MXL_SUCCESS == mxlStatus)
      {
        // Delay of 100 ms
        MxLWare_HYDRA_OEM_SleepInMs(1);

        // Reset TX FIFO's
        mxlStatus = MxLWare_HYDRA_WriteRegister(devId, HYDRA_RESET_TRANSPORT_FIFO_REG, HYDRA_RESET_TRANSPORT_FIFO_DATA);
        if (MXL_SUCCESS == mxlStatus)
        {
          // Reset baseband, widebands, SerDes & ADC
          mxlStatus = MxLWare_HYDRA_WriteRegister(devId, HYDRA_RESET_BBAND_REG, HYDRA_RESET_BBAND_DATA);
          if (MXL_SUCCESS == mxlStatus)
          {
            // Reset XBAR
            mxlStatus = MxLWare_HYDRA_WriteRegister(devId, HYDRA_RESET_XBAR_REG, HYDRA_RESET_XBAR_DATA);
            if (MXL_SUCCESS == mxlStatus)
            {
              // Disable clock to Baseband, Wideband, SerDes, Alias ext & Transport modules
              mxlStatus = MxLWare_HYDRA_WriteRegister(devId, HYDRA_MODULES_CLK_2_REG, HYDRA_DISABLE_CLK_2);
              if (MXL_SUCCESS == mxlStatus)
              {
                // Clear Software & Host interrupt status - (Clear on read)
                mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_PRCM_ROOT_CLK_REG, &regData);
                if (MXL_SUCCESS == mxlStatus)
                {
                  mxlStatus = MxLWare_FW_Download(devId, mbinBufferSize, mbinBufferPtr, fwCallbackFn);

                  if (MXL_SUCCESS == mxlStatus)
                  {
#if defined(MXL_HYDRA_568_ENABLE)
                    if (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_568)
                    {
                      MxLWare_HYDRA_OEM_SleepInMs(10);

                      // bring XCPU out of reset
                      MXLDBG3(MXL_HYDRA_PRINT("[%s] Bring XCPU out of reset\n", __FUNCTION__););
                      mxlStatus = MxLWare_HYDRA_WriteRegister(devId, 0x90720000, 1);
                      MxLWare_HYDRA_OEM_SleepInMs(10);
                    }
                    else
#endif
                    {
                      // Bring CPU out of reset
                      mxlStatus = SET_REG_FIELD_DATA(devId, PRCM_PRCM_CPU_SOFT_RST_N, 1);
                      MxLWare_HYDRA_OEM_SleepInMs(50);
                    }

                    // Initilize XPT XBAR
                    mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, XPT_DMD0_BASEADDR, 0x76543210);

                    // Check if Firmware is alive
                    if ((MXL_TRUE == MxL_Ctrl_IsFirmwareAlive(devId, 750)) && (mxlStatus == MXL_SUCCESS))
                    {
                      devSkuCfg.skuType = (UINT32) devHandlePtr->skuType;

                      // buid and send command to configure interrupt settings
                      BUILD_HYDRA_CMD(MXL_HYDRA_DEV_CFG_SKU_CMD, MXL_CMD_WRITE, cmdSize, &devSkuCfg, cmdBuff);
                      mxlStatus = MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
                    }
                    else
                      mxlStatus = MXL_FAILURE;
                  }
                }
              }
            }
          }
        }
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevInterrupt
 *
 * @param[in]   devId        Device ID
 * @param[in]   intrCfg      Device Interrupt configuration
 * @param[in]   intrMask     Interrupt mask
 *
 * @author Mahee
 *
 * @date 06/12/2012
 *
 * This API should be used to enable or disable specific interrupt
 * sources of the device along with type of INTR required.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevInterrupt(UINT8 devId, MXL_HYDRA_INTR_CFG_T intrCfg, UINT32 intrMask)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL_INTR_CFG_T devIntrCfg;
  UINT8 cmdSize = sizeof(MXL_INTR_CFG_T);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("intrType=%d, intrDuration=%dns, intrMask = %x\n", intrCfg.intrType, intrCfg.intrDurationInNanoSecs, intrMask););

  status |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    if (((intrCfg.intrDurationInNanoSecs <= MAX_ACTIVE_DURATION_OF_EDGE_INTERRUPT) && (intrCfg.intrDurationInNanoSecs >=1)) ||
        ((intrCfg.intrType != HYDRA_HOST_INTR_TYPE_EDGE_POSITIVE) && (intrCfg.intrType != HYDRA_HOST_INTR_TYPE_EDGE_NEGATIVE)))
    {
      devIntrCfg.intrMask = intrMask;
      devIntrCfg.intrType = (UINT32)intrCfg.intrType;
      devIntrCfg.intrDurationInNanoSecs = intrCfg.intrDurationInNanoSecs;

      // buid and send command to configure interrupt settings
      BUILD_HYDRA_CMD(MXL_HYDRA_DEMOD_INTR_TYPE_CMD, MXL_CMD_WRITE, cmdSize, &devIntrCfg, cmdBuff);
      status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);

      if (status == MXL_SUCCESS)
      {
        devHandlePtr->intrMask = intrMask;
      }
    } 
    else
    {
      status = MXL_INVALID_PARAMETER;
      MXLERR(MXL_HYDRA_PRINT("Edge interrupt duration must be within 1ns - %dns\n", MAX_ACTIVE_DURATION_OF_EDGE_INTERRUPT););
    }
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgClearDevtInterrupt
 *
 * @param[in]   devId        Device ID
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to clear device interrupt.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgClearDevtInterrupt(UINT8 devId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status;
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    // buid and send command to clear interrupt settings
    cmdBuff[0] = MXL_HYDRA_PLID_CMD_WRITE;
    cmdBuff[1] = (UINT8)(sizeof(UINT32));
    cmdBuff[2] = (UINT8)0;
    cmdBuff[3] = (UINT8)MXL_HYDRA_DEV_INTR_CLEAR_CMD;
    cmdBuff[4] = 0x00;
    cmdBuff[5] = 0x00;

    status = MxLWare_HYDRA_SendCommand(devId, (6 * sizeof(UINT8)), &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDevInterruptStatus
 *
 * @param[in]   devId        Device ID
 * @param[out]  intrStatusPtr
 * @param[out]  intrMaskPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to retrieve interrupt status information from
 * the device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDevInterruptStatus(UINT8 devId, UINT32 *intrStatusPtr, UINT32 *intrMaskPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  UINT32 regData = 0;
  UINT32 tempRegData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT(" "););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    if ((intrStatusPtr) && (intrMaskPtr))
    {
      // read device interrupt status
      *intrStatusPtr = 0;
      *intrMaskPtr = 0;
      status = MxLWare_HYDRA_ReadRegister(devId, HYDRA_INTR_MASK_REG, &regData);
      if(0 == regData)  // If the Interrupt status is 0, no pending interrupts to be processed, return from function
      {
          *intrMaskPtr = devHandlePtr->intrMask;
          MXLEXITAPISTR(devId, status);
          return status;
      }
      //This is done to clear the interrupt status
      //Set the Clear on read mask to clear only the bits read from the Interrupt message register
      status |= MxLWare_HYDRA_WriteRegister(devId, HYDRA_INTR_CLEAR_ON_READ_MASK, regData);
      if (regData & (MXL_HYDRA_INTR_DISEQC_0 | MXL_HYDRA_INTR_DISEQC_1 | MXL_HYDRA_INTR_DISEQC_2 | MXL_HYDRA_INTR_DISEQC_3))
      {
        regData = MxL_Get_DiseqcMappingBitMapReverse(devHandlePtr, regData);        
      }
      //Reading the status register clears the Message and status registers
      status |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_INTR_STATUS_REG, &tempRegData);

      if (status == MXL_SUCCESS)
      {
        *intrStatusPtr = regData;
        *intrMaskPtr = devHandlePtr->intrMask;
        status = GET_REG_FIELD_DATA(devId, WDT_WD_INT_STATUS, &regData);
        if (status == MXL_SUCCESS)
        {
          if (regData == 1)
          {
            status = SET_REG_FIELD_DATA(devId, FSK_TX_FTM_OE, 0);
            status |= SET_REG_FIELD_DATA(devId, FSK_TX_FTM_TX_EN, 0);
            status |= SET_REG_FIELD_DATA(devId, FSK_TX_FTM_TX_INT_SRC_SEL, 0);
            status |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_FSK_TERM_INT_EN, 1);
            status |= SET_REG_FIELD_DATA(devId, AFE_REG_D2A_FSK_RESETB_1P8, 1);
            status |= MxLWare_HYDRA_WriteRegister(devId, 0x3FFFEB5C, 0x0);
            *intrStatusPtr |= (1 << 29);
          }
          else if (regData == 0)
          {
            *intrStatusPtr &=  ~(1 << 29);
          }
        }
      }
    }
    else
      status = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDevVersionInfo
 *
 * @param[in]   devId        Device ID
 * @param[out]  versionInfoPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This function returns Hydra device identification data and version info.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_ReqDevVersionInfo(UINT8 devId, MXL_HYDRA_VER_INFO_T *versionInfoPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  mxlStatus |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (versionInfoPtr)
    {
      versionInfoPtr->chipId = devHandlePtr->deviceType;
      versionInfoPtr->chipVer = devHandlePtr->chipVersion;

      // MxLware Version
      versionInfoPtr->mxlWareVer[0] = MxLWare_HYDRA_Version[0];
      versionInfoPtr->mxlWareVer[1] = MxLWare_HYDRA_Version[1];
      versionInfoPtr->mxlWareVer[2] = MxLWare_HYDRA_Version[2];
      versionInfoPtr->mxlWareVer[3] = MxLWare_HYDRA_Version[3];
      versionInfoPtr->mxlWareVer[4] = MxLWare_HYDRA_Version[4];

      // Firmware status - Check if heart beat is active
      versionInfoPtr->firmwareDownloaded = MxL_Ctrl_IsFirmwareAlive(devId, 150);

      if (versionInfoPtr->firmwareDownloaded == MXL_TRUE)
      {
        // Read Firmware version
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_FIRMWARE_VERSION, &regData);
        versionInfoPtr->firmwareVer[0] = GET_BYTE(regData,3);
        versionInfoPtr->firmwareVer[1] = GET_BYTE(regData,2);
        versionInfoPtr->firmwareVer[2] = GET_BYTE(regData,1);
        versionInfoPtr->firmwareVer[3] = GET_BYTE(regData,0);

        // Read Firmware RC version
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_FW_RC_VERSION, &regData);
        versionInfoPtr->firmwareVer[4] = GET_BYTE(regData,0);

        // Read Firmware Patch version
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_FIRMWARE_PATCH_VERSION, &regData);
        versionInfoPtr->fwPatchVer[0] = 0; // GET_BYTE(regData,0);
        versionInfoPtr->fwPatchVer[1] = 0; // GET_BYTE(regData,1);
        versionInfoPtr->fwPatchVer[2] = 0; // GET_BYTE(regData,2);
        versionInfoPtr->fwPatchVer[3] = 0; // GET_BYTE(regData,3);
        versionInfoPtr->fwPatchVer[4] = 0;
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevPowerMode
 *
 * @param[in]   devId        Device ID
 * @param[out]  pwrMode
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API can be called to configure Hydra device into a required power
 * mode. Please refer to corresponding device�s datasheet for power
 * consumption values.

 * Power Mode    Description
 * MXL_HYDRA_PWR_MODE_ACTIVE
 *       All tuners and demods are active. Hydra is normal working mode.
 * MXL_HYDRA_PWR_MODE_STANDBY
 *       Power saving mode where all tuners and demods are inactive.
 * MXL_HYDRA_PWR_MODE_LP_TUNER
 *       Only low power tuner (network tuner) will be active.
 * MXL_HYDRA_PWR_MODE_WAKE_ON_RF
 *       Device is configured to a low power sleep mode and can be woken
 *       up by RF input signal.
 * MXL_HYDRA_PWR_MODE_WAKE_ON_BROADCAST
 *       Device is configured to a low power single tuner mode and can
 *       be woken up by a magic packet broadcast from satellite.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevPowerMode(UINT8 devId, MXL_HYDRA_PWR_MODE_E pwrMode)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MxL_HYDRA_POWER_MODE_CMD devPowerCfg;
  UINT8 cmdSize = sizeof(devPowerCfg);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("pwrMode=%d\n", pwrMode););

  status |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    devPowerCfg.powerMode = pwrMode;

    // buid and send command to configure device power mode
    BUILD_HYDRA_CMD(MXL_HYDRA_DEV_CFG_POWER_MODE_CMD, MXL_CMD_WRITE, cmdSize, &devPowerCfg, cmdBuff);
    status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevWakeOnRF
 *
 * @param[in]   devId        Device ID
 * @param[in]   tunerId
 * @param[in]   wakeTimeInSeconds
 * @param[in]   rssiThreshold
 *
 * @author Mahee
 *
 * @date 02/21/2013 Initial release
 *
 * This API configures wake on RF fetaure of HYDRA.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevWakeOnRF(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT32 wakeTimeInSeconds, SINT32 rssiThreshold)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXL_HYDRA_RF_WAKEUP_CFG_T rfWakeCfg;
  UINT8 cmdSize = sizeof(rfWakeCfg);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("tunerId=%d, wakeTimeInSeconds=%d rssiThreshold=%d\n", tunerId, wakeTimeInSeconds, rssiThreshold););

  status |= MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    rfWakeCfg.tunerCount = 1;
    rfWakeCfg.params.tunerIndex = tunerId;
    rfWakeCfg.params.timeIntervalInSeconds = wakeTimeInSeconds;
    rfWakeCfg.params.rssiThreshold = rssiThreshold;

    // buid and send command to configure wake on RF feature
    BUILD_HYDRA_CMD(MXL_HYDRA_DEV_RF_WAKE_UP_CMD, MXL_CMD_WRITE, cmdSize, &rfWakeCfg, cmdBuff);
    status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
  }

  MXLEXITAPISTR(devId, status);
  return (MXL_STATUS_E)status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevWakeOnPidParams
 *
 * @param[in]   devId        Device ID
 * @param[in]   chanTuneParamsPtr
 * @param[in]   interruptLockFail 
 * @param[in]   awakeTimeSeconds
 * @param[in]   sleepTimeSeconds
 * @param[in]   magicPid
 * @param[in]   matchBufferPtr 
 * @param[in]   maskBufferPtr 
 *
 * @author Aman/John
 *
 * @date 12/04/2015 Initial release
 *
 * This API configures PIDs for use with wake on broadcast feature of the device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevWakeOnPidParams(UINT8 devId,
                              MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr,
                              MXL_BOOL_E interruptLockFail, UINT16 awakeTimeInSeconds, 
                              UINT16 sleepTimeInSeconds, UINT16 magicPid,
                              UINT8 * matchBufferPtr, UINT8 * maskBufferPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;
  MXL_HYDRA_BROADCAST_WAKEUP_CFG_T broadcastWakeCfg;
  UINT8 cmdSize = sizeof(broadcastWakeCfg);
  UINT8 cmdBuff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];
  interruptLockFail = MXL_FALSE;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("awakeTimeInSeconds=%d, sleepTimeInSeconds=%d, \
                               interruptLockFail=%d, magicPid=%d\n", 
                               awakeTimeInSeconds, sleepTimeInSeconds, \
                               interruptLockFail, magicPid);); 

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);

  if ((status == MXL_SUCCESS) && (chanTuneParamsPtr) && (awakeTimeInSeconds >= MXL_HYDRA_MIN_TIME_IN_SECS && awakeTimeInSeconds <= MXL_HYDRA_MAX_TIME_IN_SECS) &&
      (sleepTimeInSeconds >= MXL_HYDRA_MIN_TIME_IN_SECS && sleepTimeInSeconds <= MXL_HYDRA_MAX_TIME_IN_SECS) && (magicPid >= MXL_HYDRA_MIN_PID && magicPid <= MXL_HYDRA_MAX_PID) && 
      ( ((matchBufferPtr) && (maskBufferPtr)) || ((!matchBufferPtr) && (!maskBufferPtr)) ) )
  {
    MXL_HYDRA_TUNER_ID_E tunerId = 0;
    MXL_HYDRA_DEMOD_ID_E demodId = 0;
    MXLDBG1(MXL_HYDRA_PRINT("Using demodId=%d, tunerId=%d\n", demodId, tunerId););
    status = MxLWare_HYDRA_HelperFn_CfgDemodChanTuneParamSetUp(devId, tunerId, demodId, &broadcastWakeCfg.demodChanCfg, chanTuneParamsPtr);

    broadcastWakeCfg.interruptLockFail = (UINT32) (interruptLockFail == MXL_TRUE)?1:0;
    broadcastWakeCfg.awakeTimeInSeconds = awakeTimeInSeconds;
    broadcastWakeCfg.sleepTimeInSeconds = sleepTimeInSeconds;
    broadcastWakeCfg.magicPid = magicPid;

    if(status == MXL_SUCCESS)
    {
      // buid and send command to configure wake on RF feature
      BUILD_HYDRA_CMD(MXL_HYDRA_DEV_BROADCAST_WAKE_UP_CMD, MXL_CMD_WRITE, cmdSize, &broadcastWakeCfg, cmdBuff);
      status |= MxLWare_HYDRA_SendCommand(devId, cmdSize + MXL_HYDRA_CMD_HEADER_SIZE, &cmdBuff[0]);
    }
  }
  else
  {
    status = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevOverwriteDefault
 *
 * @param[in]   devId        Device ID
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API configures Hydra devices control registers to their updated
 * default values. This API will initialize all modules and their
 * related sub-modules
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevOverwriteDefault(UINT8 devId)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status = MXL_SUCCESS;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT(" "););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    if(MxL_Ctrl_ValidateSku(devHandlePtr) == MXL_TRUE)
    {
      MXLDBG1(MXL_HYDRA_PRINT("SKU Validated"););
      // Enable AFE
      status |= SET_REG_FIELD_DATA(devId, PRCM_AFE_REG_CLOCK_ENABLE, 1);

      //status |= MxLWare_Hydra_UpdateByMnemonic(devId, PRCM_PRCM_AFE_REG_SOFT_RST_N, 1);
      if (status == MXL_SUCCESS)
      {
        status |= SET_REG_FIELD_DATA(devId, PRCM_PRCM_AFE_REG_SOFT_RST_N, 1);
        if (status == MXL_SUCCESS)
        {
          UINT32 chipVer;
          status |= GET_REG_FIELD_DATA(devId, PRCM_CHIP_VERSION, &chipVer);
          if (status == MXL_SUCCESS)
          {
            devHandlePtr->chipVersion = (chipVer == 2)?2:1;
            MXLDBG1(MXL_HYDRA_PRINT("[hydra] chip version: %d\n", devHandlePtr->chipVersion););
          }
          else
            devHandlePtr->chipVersion = 0;
        }
      }
    }
    else
      status = MXL_FAILURE;
  }

  MXLEXITAPISTR(devId, status);
  return (MXL_STATUS_E)status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode
 *
 * @param[in]   devId           Device ID
 * @param[in]   devAuxCtrlMode
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to enable either DiSEqC or FSK (SWM).
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E  MxLWare_HYDRA_API_CfgDevDiseqcFskOpMode(UINT8 devId, MXL_HYDRA_AUX_CTRL_MODE_E devAuxCtrlMode)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E status;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devAuxCtrlMode=%d\n", devAuxCtrlMode););

  status = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (status == MXL_SUCCESS)
  {
    // update device context
    if (devAuxCtrlMode == MXL_HYDRA_AUX_CTRL_MODE_FSK)
    {
      devHandlePtr->features.FSKEnabled = MXL_TRUE;
      devHandlePtr->features.DiSEqCEnabled = MXL_FALSE;
    }
    else
    {
      devHandlePtr->features.FSKEnabled = MXL_FALSE;
      devHandlePtr->features.DiSEqCEnabled = MXL_TRUE;
    }
  }

  MXLEXITAPISTR(devId, status);
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevGPIODirection
 *
 * @param[in]   devId           Device ID
 * @param[in]   gpioId
 * @param[in]   gpioDir
 *
 * @author Sateesh
 *
 * @date 10/12/2014 Initial release
 *
 * This API should be used to configure device GPIO pin�s direction
 * (input or output).
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_API_CfgDevGPIODirection(UINT8 devId, UINT8 gpioId, MXL_HYDRA_GPIO_DIR_E gpioDir)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 pinMuxSel = 0, gpioOutPinMux = 1;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("gpioId=%d, gpioDir=%d\n", gpioId, gpioDir););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if ((gpioId < devHandlePtr->gpioMaxNum) && (gpioDir < MXL_HYDRA_GPIO_DIR_MAX))
    {
      if (((devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_544) || (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_542C)) && \
          ((gpioId >= 5) && (gpioId <= 8)) && (gpioDir == MXL_HYDRA_GPIO_DIR_OUTPUT))
        gpioOutPinMux = 0;

      pinMuxSel = (gpioDir == MXL_HYDRA_GPIO_DIR_INPUT) ? MXL_HYDRA_GPIO_IN_PINMUX_SEL : gpioOutPinMux;
      mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId, 
                                devHandlePtr->gpioInfoPtr[gpioId].regAddr,
                                devHandlePtr->gpioInfoPtr[gpioId].lsbPos,
                                devHandlePtr->gpioInfoPtr[gpioId].numOfBits,
                                pinMuxSel);

      if (mxlStatus == MXL_SUCCESS)
      {
        mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId, 
                                  ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? PAD_MUX_GPIO_CE_BASEADDR1 : PAD_MUX_GPIO_CE_BASEADDR2),
                                  ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? gpioId : (gpioId - MXL_HYDRA_BITS_IN_REGISTER)),
                                  1,
                                  gpioDir);
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }
  
  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_CfgDevGPOData
 *
 * @param[in]   devId           Device ID
 * @param[in]   gpioId
 * @param[in]   gpioData
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API writes data to GPIO pin when the pin is used as output.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E  MxLWare_HYDRA_API_CfgDevGPOData(UINT8 devId, UINT8 gpioId, MXL_HYDRA_GPIO_DATA_E gpioData)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regReadValue = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("gpioId=%d, gpioData=%d\n", gpioId, gpioData););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if ((gpioId < devHandlePtr->gpioMaxNum) && (gpioData < MXL_HYDRA_GPIO_DATA_MAX))
    {
      mxlStatus = MxLWare_Hydra_ReadByMnemonic(devId, 
                                ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? PAD_MUX_GPIO_CE_BASEADDR1: PAD_MUX_GPIO_CE_BASEADDR2),
                                ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? gpioId : (gpioId - MXL_HYDRA_BITS_IN_REGISTER)),
                                1,
                                &regReadValue);

      if ((mxlStatus == MXL_SUCCESS) && (regReadValue == MXL_HYDRA_GPIO_DIR_OUTPUT))
      {
        mxlStatus = MxLWare_Hydra_UpdateByMnemonic(devId, 
                                  ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? PAD_MUX_GPIO_CO_BASEADDR1: PAD_MUX_GPIO_CO_BASEADDR2),
                                  ((gpioId < MXL_HYDRA_BITS_IN_REGISTER) ? gpioId : (gpioId - MXL_HYDRA_BITS_IN_REGISTER)),
                                  1,
                                  gpioData);
      }
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_API_ReqDevTemperature
 *
 * @param[in]   devId           Device ID
 * @param[out]  devTemperatureInCelsiusPtr - Current device temperature.
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to retrieve current device temperature.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E  MxLWare_HYDRA_API_ReqDevTemperature(UINT8 devId, SINT16 *devTemperatureInCelsiusPtr)
{
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regData = 0;

  MXLENTERAPISTR(devId);
  MXLENTERAPI(MXL_HYDRA_PRINT("devId=%d\n", devId););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    if (devTemperatureInCelsiusPtr)
    {
      mxlStatus = MxLWare_HYDRA_ReadRegister(devId, HYDRA_TEMPARATURE, &regData);
      *devTemperatureInCelsiusPtr = (SINT16)(regData & 0xFFFF);
    }
    else
      mxlStatus = MXL_INVALID_PARAMETER;
  }

  MXLEXITAPISTR(devId, mxlStatus);
  return mxlStatus;
}
