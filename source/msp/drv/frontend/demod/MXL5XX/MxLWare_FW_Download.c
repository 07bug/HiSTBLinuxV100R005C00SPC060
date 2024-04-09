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
#include "MaxLinearDataTypes.h"
#include "MaxLinearDebug.h"
#include "MxLWare_HYDRA_OEM_Drv.h"
#include "MxLWare_FW_Download.h"
#include "MxLWare_HYDRA_Registers.h"

static UINT32 MxL_Ctrl_GetBigEndian(UINT8 numOfBits, const UINT8 buf[])
{
  UINT32 retValue = 0;

  switch(numOfBits)
  {
    case 24:
      retValue = (((UINT32)buf[0])<<16) | (((UINT32)buf[1])<<8) | buf[2];
      break;

    case 32:
      retValue = (((UINT32)buf[0])<<24) |
                  (((UINT32)buf[1])<<16) |
                  (((UINT32)buf[2])<<8) | buf[3];
      break;

    default:
      break;
  }
  return retValue;
}

static MXL_STATUS_E MxL_Ctrl_WriteFWSegement(UINT8 devId,
                                               UINT32 MemAddr,
                                               UINT32 segSize,         // Segment size
                                               UINT32 mbinBufferSize,  // mbin size
                                               const UINT8 *dataPtr,
                                               /*@null@*/ MXL_CALLBACK_FN_T fwCallbackFn)
{
  MXL_STATUS_E mxlStatus = MXL_FAILURE;
  UINT32 dataCount = 0;
  UINT32 size = 0;
  UINT8* wBufPtr = NULL;
  UINT32 blockSize = ((MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH-(MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES))/4)*4;
  UINT8 wMsgBuffer[MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH-(MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES)];
  UINT32 fwCBFreq = 0;
  MXL_HYDRA_FW_DOWNLOAD_CB_PAYLOAD_T cbPayload;
  static UINT32 currentSize = sizeof(MBIN_FILE_HEADER_T);

  cbPayload.totalSize = mbinBufferSize;
  currentSize += sizeof(MBIN_SEGMENT_HEADER_T);
  cbPayload.currentSize = currentSize;

  // if data to send is multiple of 4 i.e size should be always 32-bit aligned
  if (segSize & 3)
  {
    segSize = (segSize + 4) & (UINT16)(~3);
  }

  do
  {
    // size is OEM block size/remaining data bytes in the segment
    size = (((UINT32)(dataCount + blockSize)) > segSize) ? (segSize - dataCount) : blockSize;

    wBufPtr = &wMsgBuffer[0];
    MXLWARE_OSAL_MEMSET((void *)wBufPtr, 0x0, size);
    MXLWARE_OSAL_MEMCPY((void *)wBufPtr, (void *)dataPtr, size);

    // each 4 bytes: LSB->MSB
    MxL_CovertDataForEndianness(MXL_TRUE, size, wBufPtr);

    // Send fw segment data to device
    mxlStatus = MxLWare_HYDRA_WriteFirmwareBlock(devId, MemAddr, size, wBufPtr);

    if (MXL_SUCCESS != mxlStatus)
      break;

    dataCount += size;
    MemAddr   += size;
    dataPtr   += size;

    if (fwCallbackFn)
    {
      fwCBFreq += size;
      currentSize += size;
      cbPayload.currentSize = currentSize;

      if ((fwCBFreq >= (UINT32)(7 * blockSize)) || (cbPayload.currentSize == cbPayload.totalSize))
      {
        if (MXL_HYDRA_FW_DOWNLOAD_ABORT == fwCallbackFn(devId, (UINT32)fwCBFreq, &cbPayload))
        {
          MXLDBG1(MXL_HYDRA_PRINT("%s: Firmware download has been aborted based on application's request\n", __FUNCTION__););
          mxlStatus = MXL_NOT_READY; // FW ABORT request received
          break;
        }

        fwCBFreq = 0;
      }
    }
  } while (dataCount < segSize);

  return mxlStatus;
}

MXL_STATUS_E MxLWare_FW_Download(UINT8 devId, UINT32 mbinBufferSize, const UINT8 *mbinBufferPtr, MXL_CALLBACK_FN_T fwCallbackFn)
{
  MXL_STATUS_E mxlStatus = MXL_SUCCESS;
  UINT32 index = 0;
  UINT32 segLength = 0;
  UINT32 segAddress = 0;
  const MBIN_FILE_T* mbinPtr  = (MBIN_FILE_T*)mbinBufferPtr;
  MBIN_SEGMENT_T *segmentPtr;
  MXL_HYDRA_CONTEXT_T * devHandlePtr;
  
#if defined (MXL_HYDRA_568_ENABLE)
  MXL_BOOL_E xcpuResetFlag = MXL_FALSE;
#endif

#ifdef _MXL_BRING_UP__
  UINT32 data = 0;
#endif

  // mbinBufferSize is set to mutliple of 4 if it not.
  if (mbinBufferSize & 3)
  {
    mbinBufferSize = (mbinBufferSize + 4) & (UINT32)(~3);
  }

  MXLDBG2(MXL_HYDRA_PRINT("%s: Header ID = %d, Segments number = %d \n", __FUNCTION__, mbinPtr->header.id, mbinPtr->header.numSegments););

  mxlStatus = MxLWare_HYDRA_Ctrl_GetDeviceContext(devId, &devHandlePtr);
  if (mxlStatus == MXL_SUCCESS)
  {
    // Verify firmware header
    if (mbinPtr->header.id == MBIN_FILE_HEADER_ID)
    {
      //set this to 0 before downloading fw. FW will write is back FW_DL_SIGN_ADDR after boot up
      mxlStatus = MxLWare_HYDRA_WriteRegister(devId, FW_DL_SIGN_ADDR, 0);

      segmentPtr = (MBIN_SEGMENT_T *) (&mbinPtr->data[0]);

      for (index = 0; index < mbinPtr->header.numSegments; index++)
      {
        // Validate segment header ID
        if ( segmentPtr->header.id != MBIN_SEGMENT_HEADER_ID)
        {
          MXLERR(MXL_HYDRA_PRINT("%s: Invalid segment header ID (%c)\n", __FUNCTION__, segmentPtr->header.id););
          mxlStatus = MXL_NOT_SUPPORTED; // If the segment format is wrong, then exit with MXL_FAILURE
          break;
        }

        // Get segment data length and start address
        segLength  = MxL_Ctrl_GetBigEndian(24, &(segmentPtr->header.len24[0]));
        segAddress = MxL_Ctrl_GetBigEndian(32, &(segmentPtr->header.address[0]));

#ifdef _MXL_BRING_UP__
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_CPU_RESET_REG, &data);
        MXL_HYDRA_PRINT("%s: Before Segment = %d SegAddr = 0x%X\n", __FUNCTION__, index, segAddress);
#endif
        MXLDBG3(MXL_HYDRA_PRINT("%s: Segment = %d SegAddr = 0x%X SegLength = %d\n", __FUNCTION__, index, segAddress, segLength););


#if defined (MXL_HYDRA_568_ENABLE)
        if (devHandlePtr->deviceType == MXL_HYDRA_DEVICE_568)
        {
          if ((((segAddress & 0x90760000) == 0x90760000) || ((segAddress & 0x90740000) == 0x90740000)) && (xcpuResetFlag == MXL_FALSE))
          {
            // MCPU softreset
            // MxLWare_Hydra_UpdateByMnemonic(devId, 0x8003003C, 0 , 1, 1);
            mxlStatus |= SET_REG_FIELD_DATA(devId, PRCM_PRCM_CPU_SOFT_RST_N, 1);

            MxLWare_HYDRA_OEM_SleepInMs(200);

            // XCPU into reset
            mxlStatus |= MxLWare_HYDRA_WriteRegister(devId, 0x90720000, 0);

            MxLWare_HYDRA_OEM_SleepInMs(10);

            xcpuResetFlag = MXL_TRUE;
          }
          mxlStatus |= MxL_Ctrl_WriteFWSegement(devId, segAddress, segLength, mbinBufferSize, (UINT8*)segmentPtr->data, fwCallbackFn);
        }
        else
#endif
        // Send segment
        {
          if (((segAddress & 0x90760000) != 0x90760000) && ((segAddress & 0x90740000) != 0x90740000))
            mxlStatus |= MxL_Ctrl_WriteFWSegement(devId, segAddress, segLength, mbinBufferSize, (UINT8*)segmentPtr->data, fwCallbackFn);
        }

#ifdef _MXL_BRING_UP__
        mxlStatus |= MxLWare_HYDRA_ReadRegister(devId, HYDRA_CPU_RESET_REG, &data);
#endif

        if (MXL_SUCCESS != mxlStatus)
        {
          break;
        }

        // Next segment
        segmentPtr = (MBIN_SEGMENT_T*)&(segmentPtr->data[((segLength + 3)/4)*4]);
      }
    }
    else
    {
      MXLERR(MXL_HYDRA_PRINT("%s: Invalid file header ID (%c)\n", __FUNCTION__, mbinPtr->header.id););
      mxlStatus = MXL_NOT_SUPPORTED; // the mbin file formate not supported
    }
  }
  return mxlStatus;
}
