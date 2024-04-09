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

#include "MxLWare_HYDRA_CommonApi.h"
#include "MxLWare_HYDRA_PhyCtrl.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MxLWare_HYDRA_Commands.h"
#include "MxLWare_HYDRA_Registers.h"

static MXL_HYDRA_CONTEXT_T mxlware_hydra_devices[MXL_HYDRA_MAX_NUM_DEVICES] = {{0, }, };

/**
 ************************************************************************
 *
 * @brief MxL_Ctrl_GetTsID
 *
 * @param[in]   devType
 * @param[in]   logicalDemodId
 * @param[out]  physicalDemodId
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 * @date 05/09/2013 Add tsMap to permit logical to physical TS mapping seperate from demod
 *
 * This API will returns matching physical TS id for a give logical demod/ts id.
 * If there is an error, it will return invalid demod id (MXL_HYDRA_DEMOD_MAX)
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_NOT_INITIALIZED    - Not Initialized
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxL_Ctrl_GetTsID(MXL_HYDRA_CONTEXT_T *devHandlePtr, MXL_HYDRA_DEMOD_ID_E logicalDemodId, MXL_HYDRA_DEMOD_ID_E *physicalDemodId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;

  if (logicalDemodId < devHandlePtr->features.demodsCnt)
  {
    if (devHandlePtr->tsMap)
    {
      *physicalDemodId = devHandlePtr->tsMap[logicalDemodId];
    }
    else
      mxlStatus = MXL_NOT_INITIALIZED;
  }
  else
    mxlStatus = MXL_INVALID_PARAMETER;
  // return right physical TS id connected to corrsponding logical demod id
  MXLDBG2(MXL_HYDRA_PRINT("%s: TSID = dev%d log%d phys%d\n", __FUNCTION__, devHandlePtr->deviceType, logicalDemodId, *physicalDemodId););
  return mxlStatus;
}

MXL_STATUS_E MxL_Ctrl_GetPhyTsID(UINT8 devId, MXL_HYDRA_DEMOD_ID_E physicalDemodId, MXL_HYDRA_TS_ID_E *physicalTsId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 xbarSetting;
  MXLDBG2(UINT32 i;)
  MXL_HYDRA_TS_ID_E tsId;
  UINT8 count = 0;

  mxlStatus = MxLWare_HYDRA_ReadRegister(devId, XPT_DMD0_BASEADDR, &xbarSetting);
  if (mxlStatus == MXL_SUCCESS)
  {
    for (tsId = MXL_HYDRA_TS_ID_0; tsId < MXL_HYDRA_TS_MAX; tsId++)
    {  
      if ((xbarSetting & 0x7) == physicalDemodId) {
        physicalTsId[++count] = tsId;
      }
      xbarSetting = xbarSetting >> 4;
    }
    physicalTsId[0] = count;
  }

  MXLDBG2(MXL_HYDRA_PRINT("%s: phyDmd: %d ", __FUNCTION__, physicalDemodId);
  for (i = 0; i < count; i++)
    MXL_HYDRA_PRINT("phyTs: %d\n", physicalTsId[i]);
    );
  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxL_Ctrl_SignExt
 *
 * @param[in]   data
 * @param[in]   n - Number of bits in data
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API will returns matching physical demod id for a give logical demod id.
 * If there is an error, it will return invalid demod id (MXL_HYDRA_DEMOD_MAX)
 *
 * @retval physical demod id    - Physical demod id of the device
 *
 ************************************************************************/
SINT32 MxL_Ctrl_SignExt(UINT32 data, UINT32 n)
{
  SINT32 r = (SINT32)(data << (32-n));
  return (r>>(32-n));
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_SendCommand
 *
 * @param[in]   devId           Device ID
 * @param[in]   cmdId
 * @param[in]   size
 * @param[in]   cmdBuffPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to send a command to device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_SendCommand(UINT8 devId, UINT32 size, UINT8 *cmdBuffPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regReadData = 0;
  UINT8 cnt = 0;

  if ((size) && (cmdBuffPtr))
  {
	// Do not send a I2C write if the previous I2C write is not processed by FW
    mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, DMA_I2C_INTERRUPT_ADDR, &regReadData);
	while((regReadData & DMA_INTR_PROT_WR_CMP) && (cnt < 10)) //Timeout after 10ms
	{
		MxLWare_HYDRA_OEM_SleepInMs(1);
		cnt += 1;
		mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, DMA_I2C_INTERRUPT_ADDR, &regReadData);
	}

	if(cnt >= 10)
	{
		mxlStatus |= MXL_FAILURE;
	}

    mxlStatus |= MxLWare_HYDRA_OEM_Lock(devId);

    MXLDBG2(MXL_HYDRA_PRINT("%s: Command Id = %d  0x%02X\n", __FUNCTION__, cmdBuffPtr[3], cmdBuffPtr[3]););

    mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId, (UINT16)size, cmdBuffPtr);

    mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);
  }
  else
    mxlStatus |= MXL_INVALID_PARAMETER;

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_WriteRegister
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddress
 * @param[in]   regData
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to write a 32-bit register to the device.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_WriteRegister(UINT8 devId, UINT32 regAddress, UINT32 regData)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 data[MXL_HYDRA_REG_WRITE_LEN];

  mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

  // I2C request header
  data[0] = MXL_HYDRA_PLID_REG_WRITE;   // PLID for register write
  data[1] = 0x08;                       // length byte

  // Register Address
  data[2] = GET_BYTE(regAddress,0);     // reg addr byte
  data[3] = GET_BYTE(regAddress,1);     // reg addr byte
  data[4] = GET_BYTE(regAddress,2);     // reg addr byte
  data[5] = GET_BYTE(regAddress,3);     // reg addr byte

  // Register Data
  data[6] = GET_BYTE(regData,0);        // reg data byte
  data[7] = GET_BYTE(regData,1);        // reg data byte
  data[8] = GET_BYTE(regData,2);        // reg data byte
  data[9] = GET_BYTE(regData,3);        // reg data byte

  mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId, (MXL_HYDRA_REG_WRITE_LEN), &data[0]);

  MXLDBG3(MXL_HYDRA_PRINT("\n%s: Reg Addr = 0x%08X - 0x%08X\n", __FUNCTION__, regAddress, regData););

  mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_ReadRegister
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddress
 * @param[out]  regDataPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * OEM Drv/Lib (DLL) modules should call this function to read a block
 * device registers or a block memory from the device using I2C device interface.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_ReadRegister(UINT8 devId, UINT32 regAddress, UINT32 *regDataPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 regAddr[MXL_HYDRA_REG_SIZE_IN_BYTES+MXL_HYDRA_I2C_HDR_SIZE];

  mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

  // I2C request header
  regAddr[0] = MXL_HYDRA_PLID_REG_READ;   // PLID for register write
  regAddr[1] = 0x04;                       // length byte

  // Register Address
  regAddr[2] = GET_BYTE(regAddress, 0);     // reg addr byte
  regAddr[3] = GET_BYTE(regAddress, 1);     // reg addr byte
  regAddr[4] = GET_BYTE(regAddress, 2);     // reg addr byte
  regAddr[5] = GET_BYTE(regAddress, 3);     // reg addr byte

  // Write register address
  mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId, (MXL_HYDRA_REG_SIZE_IN_BYTES+MXL_HYDRA_I2C_HDR_SIZE), &regAddr[0]);

  // Read register data from the device
  mxlStatus |= MxLWare_HYDRA_OEM_I2cRead(devId, (MXL_HYDRA_REG_SIZE_IN_BYTES), (UINT8 *)regDataPtr);
  MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, MXL_HYDRA_REG_SIZE_IN_BYTES, (UINT8 *)regDataPtr);

  MXLDBG3(MXL_HYDRA_PRINT("(%d) %s: RegAddr = 0x%08X Data = 0x%08X\n", mxlStatus, __FUNCTION__, regAddress, *regDataPtr););

  mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_WriteRegisterBlock
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddress
 * @param[in]   size
 * @param[in]   regDataPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API is used to perform block register write operation.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_WriteFirmwareBlock(UINT8 devId, UINT32 regAddress, UINT32 size, UINT8 *regDataPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  if (regDataPtr)
  {
    mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

    // I2C request header
    buff[0] = MXL_HYDRA_PLID_REG_WRITE;   // PLID for register write
    buff[1] = (UINT8)size+4;                     // length byte

    // Register Address
    buff[2] = GET_BYTE(regAddress, 0);     // reg addr byte
    buff[3] = GET_BYTE(regAddress, 1);     // reg addr byte
    buff[4] = GET_BYTE(regAddress, 2);     // reg addr byte
    buff[5] = GET_BYTE(regAddress, 3);     // reg addr byte

    // copy data buffer
    MXLWARE_OSAL_MEMCPY(&buff[6], regDataPtr, size);

    // write data to device
    mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId,
                                           (UINT16)(MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES + size),
                                            buff);

    mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);
  }
  else
    mxlStatus |= MXL_INVALID_PARAMETER;

  return mxlStatus;
}

void MxL_CovertDataForEndianness(UINT8 convertDataFlag, UINT32 size, UINT8* dataPtr)
{
  UINT32 i;

  if (convertDataFlag)
  {
    for (i = 0; i < (size & ~3); i += 4)
    {
      dataPtr[i + 0] ^= dataPtr[i + 3];
      dataPtr[i + 3] ^= dataPtr[i + 0];
      dataPtr[i + 0] ^= dataPtr[i + 3];

      dataPtr[i + 1] ^= dataPtr[i + 2];
      dataPtr[i + 2] ^= dataPtr[i + 1];
      dataPtr[i + 1] ^= dataPtr[i + 2];
    }

    switch (size & 3)
    {
      case 0: case 1: /* do nothing */ break;
      case 2:
        dataPtr[i + 0] ^= dataPtr[i + 1];
        dataPtr[i + 1] ^= dataPtr[i + 0];
        dataPtr[i + 0] ^= dataPtr[i + 1];
        break;

      case 3:
        dataPtr[i + 0] ^= dataPtr[i + 2];
        dataPtr[i + 2] ^= dataPtr[i + 0];
        dataPtr[i + 0] ^= dataPtr[i + 2];
        break;
    }
#if 0
    for (i = 0; i < size; i+=4)
    {
      MXL_HYDRA_PRINT("0x%02X 0x%02X 0x%02X 0x%02X\n", dataPtr[i], dataPtr[i+1], dataPtr[i+2], dataPtr[i+3]);
    }
#endif
  }
}

MXL_STATUS_E MxLWare_HYDRA_WriteRegisterBlock(UINT8 devId, UINT32 regAddress, UINT32 size, UINT8 *regDataPtr)
{
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  UINT8 buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  if (regDataPtr)
  {
    mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

    // I2C request header
    buff[0] = MXL_HYDRA_PLID_REG_WRITE;   // PLID for register write
    buff[1] = (UINT8)size+4;              // length byte

    // Register Address
    buff[2] = GET_BYTE(regAddress, 0);     // reg addr byte
    buff[3] = GET_BYTE(regAddress, 1);     // reg addr byte
    buff[4] = GET_BYTE(regAddress, 2);     // reg addr byte
    buff[5] = GET_BYTE(regAddress, 3);     // reg addr byte

    // copy data buffer
    MXLWARE_OSAL_MEMCPY(&buff[6], regDataPtr, size);

    MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, size, &buff[6]);

    // write data to device
    mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId,
                                           (UINT16)(MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES + size),
                                            buff);

    mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);
  }
  else
    mxlStatus = MXL_INVALID_PARAMETER;

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_ReadRegisterBlock
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddress
 * @param[in]   size
 * @param[out]  regDataPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API is used to perform block register read operation.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_ReadRegisterBlock(UINT8 devId, UINT32 regAddress, UINT32 size, UINT8 *regDataPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 buff[MXL_HYDRA_OEM_MAX_CMD_BUFF_LEN];

  if ((size) && (regDataPtr))
  {
    mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

    // I2C request header
    buff[0] = MXL_HYDRA_PLID_REG_READ;   // PLID for register write
    buff[1] = (UINT8)size+4;                    // length byte

    // Register Address
    buff[2] = GET_BYTE(regAddress, 0);     // reg addr byte
    buff[3] = GET_BYTE(regAddress, 1);     // reg addr byte
    buff[4] = GET_BYTE(regAddress, 2);     // reg addr byte
    buff[5] = GET_BYTE(regAddress, 3);     // reg addr byte

    // write data to device
    mxlStatus |= MxLWare_HYDRA_OEM_I2cWrite(devId,
                                            (MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES),
                                            buff);

    // Read register data from the device
    if (mxlStatus == MXL_SUCCESS)
    {
      mxlStatus = MxLWare_HYDRA_OEM_I2cRead(devId, (UINT16)(size), (UINT8 *)regDataPtr);
      MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, size, (UINT8 *)regDataPtr);
      MXLDBG2(MXL_HYDRA_PRINT("%s: RegAddr = 0x%08X Size = %d\n", __FUNCTION__, regAddress, size););

    }
    MXLERR(
    else
      MXL_HYDRA_PRINT("%s: RegAddr = 0x%08X - Error\n", __FUNCTION__, regAddress);
    );
    mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);

  }
  else
    mxlStatus = MXL_INVALID_PARAMETER;

  return mxlStatus;
}

static MXL_STATUS_E MxL_Ctrl_MessageRead(UINT8 devId, UINT8* buffPtr, UINT16 msgLen)
{
  MXL_STATUS_E status = MXL_SUCCESS;
  UINT8 tmpData[4];

  // This is to check if FW sends an invalid msgLen
  // Check if msgLen does not exceed 260 bytes to avoid memory corruption in MxlWare
  if ((buffPtr) && (msgLen) && (msgLen < DMA_I2C_READ_LEN_MAX))
  {
    // try to read of 0x8000011C check bit 5 until bit 5 != 1
    tmpData[0] = MXL_HYDRA_PLID_CMD_READ;               // Copy PLID
    tmpData[1] = 0x00;                                  // Hardware Length
    tmpData[2] = 0x00;                                  // Hardware Length
    tmpData[3] = 0x00;                                  // Hardware Length

    // Scorpius-229
    //MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, 2, (UINT8 *)&tmpData[0]);

    status = MxLWare_HYDRA_OEM_I2cWrite(devId, 4, (UINT8 *)&tmpData[0]);  // write 2 bytes to I2C device
    if (status == MXL_SUCCESS)                              // not success, return fail
    {
		// Read data from I2C device
        status = MxLWare_HYDRA_OEM_I2cRead(devId, msgLen, buffPtr);
    }
  }
  else
  {
    status = MXL_INVALID_PARAMETER;
  }
  return status;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_CheckForCmdResponse
 *
 * @param[in]   devId           Device ID
 * @param[in]   ctxPtr
 * @param[in]   cmdId
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to read response for a command from the device
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_HYDRA_CheckForCmdResponse(UINT8 devId, MXL_HYDRA_CONTEXT_T *ctxPtr, UINT8 cmdId)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT8 dataLen = 0;
  UINT8 respCmd = 0;
  UINT8 timeOutCount = 0;
  UINT32 msgLen = DMA_I2C_READ_LEN_MAX;

  if (ctxPtr)
  {
    // check data availble loop
    while (timeOutCount < 100)
    {
      ctxPtr->cmdData.dataSize = 0;

	  mxlStatus = MxLWare_HYDRA_ReadRegister(devId, DMA_I2C_READ_LEN_ADDR, &msgLen);

      if (mxlStatus != MXL_SUCCESS)
        break; // Quit loop
	  
      mxlStatus = MxLWare_HYDRA_OEM_Lock(devId);

	  // read back the message
	  mxlStatus |= MxL_Ctrl_MessageRead(devId, &ctxPtr->cmdData.data[0], (UINT16)msgLen);

      mxlStatus |= MxLWare_HYDRA_OEM_Unlock(devId);

      if (mxlStatus != MXL_SUCCESS)
        break; // Quit loop

      dataLen = ctxPtr->cmdData.data[0];
      respCmd = ctxPtr->cmdData.data[1];

      if (respCmd > 0xE0)
        continue;

      MXLDBG2(MXL_HYDRA_PRINT("[%s] length = %d CMDID = %d\r\n", __FUNCTION__, dataLen, respCmd););

      // invalid coomand ID, then contiue next read
      if (respCmd != cmdId)
      {
        // Sleep 5 ms
        MxLWare_HYDRA_OEM_SleepInMs(10);
        timeOutCount++;
      }
      else
      {
        ctxPtr->cmdData.dataSize = dataLen+4;
        break;
      }
    }
  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_Hydra_ReadByMnemonic
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddr        Register Address
 * @param[in]   lsbLoc           LSB location of the bit
 * @param[in]   numOfBits     Number of bits.
 * @param[out] dataPtr          bit field value
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to read registers bit field value
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_Hydra_ReadByMnemonic(UINT8 devId, UINT32 regAddr, UINT8 lsbLoc, UINT8 numOfBits, UINT32 *dataPtr)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regReadData = 0;
  UINT32 regDataMask = 0;

  if (dataPtr)
  {
    // read 32-bit register from the device
    mxlStatus = MxLWare_HYDRA_ReadRegister(devId, regAddr, &regReadData);

    if (MXL_SUCCESS == mxlStatus)
    {
      // generate mask by shifting bits
      regDataMask =  MXL_GET_REG_MASK_32(lsbLoc,numOfBits);

      regReadData &= regDataMask;
      regReadData >>= lsbLoc;

      *dataPtr = regReadData;
    }
  }
  else
    mxlStatus = MXL_INVALID_PARAMETER;

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_Hydra_UpdateByMnemonic
 *
 * @param[in]   devId           Device ID
 * @param[in]   regAddr        Register Address
 * @param[in]   lsbLoc           LSB location of the bit
 * @param[in]   numOfBits     Number of bits.
 * @param[in]   data             bit field value
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to update registers bit field value
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/
MXL_STATUS_E MxLWare_Hydra_UpdateByMnemonic(UINT8 devId, UINT32 regAddr, UINT8 lsbLoc, UINT8 numOfBits, UINT32 data)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 regWriteData = 0;
  UINT32 regDataMask = 0;
  UINT32 regReadData = 0;

  mxlStatus = MxLWare_HYDRA_ReadRegister(devId, regAddr, &regReadData);

  if (MXL_SUCCESS == mxlStatus)
  {
    // generate mask by shifting bits
    regDataMask = MXL_GET_REG_MASK_32(lsbLoc,numOfBits);

    // use data mask to get desired bits value to write
    regWriteData = (regReadData & ~regDataMask) | ((data << lsbLoc) & regDataMask);

    mxlStatus = MxLWare_HYDRA_WriteRegister(devId, regAddr, regWriteData);
  }

  return mxlStatus;
}

/**
 ************************************************************************
 *
 * @brief MxLWare_HYDRA_Ctrl_GetDeviceContext
 *
 * @param[in]   devId           Device ID
 * @param[out]  deviceContextPtr
 *
 * @author Mahee
 *
 * @date 06/12/2012 Initial release
 *
 * This API should be used to get current device's context info.
 *
 * @retval MXL_SUCCESS            - OK
 * @retval MXL_FAILURE            - Failure
 * @retval MXL_INVALID_PARAMETER  - Invalid parameter is passed
 *
 ************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_Ctrl_GetDeviceContext(UINT8 devId, MXL_HYDRA_CONTEXT_T ** deviceContextPtr)
{
  MXL_STATUS_E status = MXL_SUCCESS;

  if (devId < MXL_HYDRA_MAX_NUM_DEVICES)
  {
    if (deviceContextPtr)
      *deviceContextPtr = &mxlware_hydra_devices[devId];

    if (mxlware_hydra_devices[devId].initialized != MXL_TRUE)
    {
      status = MXL_NOT_INITIALIZED;
      MXLERR(MXL_HYDRA_PRINT("[%s] Device #%d is not initialized\n", __FUNCTION__, devId););
    }
  }
  else
  {
    status = MXL_INVALID_PARAMETER;
    MXLERR(MXL_HYDRA_PRINT("[%s] Device id#%d is greater than max number of devices (%d)\n", __FUNCTION__, devId, MXL_HYDRA_MAX_NUM_DEVICES););
  }

  return status;
}

MXLDBG1(
char * MxLWare_HYDRA_DBG_GetDeviceName(MXL_HYDRA_DEVICE_E deviceType)
{
  char *deviceName;
  switch (deviceType)
  {
    case MXL_HYDRA_DEVICE_581:
        deviceName = "MxL581";
        break;
    case MXL_HYDRA_DEVICE_584:
        deviceName = "MxL584";
        break;
    case MXL_HYDRA_DEVICE_585:
        deviceName = "MxL585";
        break;
    case MXL_HYDRA_DEVICE_544:
        deviceName = "MxL544";
        break;
    case MXL_HYDRA_DEVICE_541:
        deviceName = "MxL541";
        break;
    case MXL_HYDRA_DEVICE_561:
        deviceName = "MxL561";
        break;
    case MXL_HYDRA_DEVICE_582:
        deviceName = "MxL582";
        break;
    case MXL_HYDRA_DEVICE_568:
        deviceName = "MxL568";
        break;
    case MXL_HYDRA_DEVICE_542:
        deviceName = "MxL542";
        break;
    case MXL_HYDRA_DEVICE_541S:
        deviceName = "MxL541S";
        break;
    case MXL_HYDRA_DEVICE_561S:
        deviceName = "MxL561S";
        break;
    case MXL_HYDRA_DEVICE_581S:
        deviceName = "MxL581S";
        break;
    case MXL_HYDRA_DEVICE_541C:
        deviceName = "MxL541C";
        break;
    case MXL_HYDRA_DEVICE_542C:
        deviceName = "MxL542C";
        break;
    case MXL_HYDRA_DEVICE_581C:
        deviceName = "MxL581C";
        break;
    case MXL_HYDRA_DEVICE_582C:
        deviceName = "MxL582C";
        break;
    default:
        deviceName = "unknown";
        break;
  }
  return deviceName;
}
)

void MxLWare_HYDRA_ExtractFromMnemonic(UINT32 regAddr, UINT8 lsbPos, UINT8 width, UINT32 * toAddr, UINT8 * toLsbPos, UINT8 * toWidth)
{
  if (toAddr) *toAddr = regAddr;
  if (toLsbPos) *toLsbPos = lsbPos;
  if (toWidth) *toWidth = width;
}

