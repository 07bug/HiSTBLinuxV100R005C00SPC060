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

#ifndef __MXLWARE_HYDRA_PHYCTRL_H__
#define __MXLWARE_HYDRA_PHYCTRL_H__

#include "MxLWare_HYDRA_DeviceApi.h"
#include "MxLWare_HYDRA_TsMuxCtrlApi.h"
#include "MxLWare_HYDRA_Commands.h"
#include "MxLWare_HYDRA_ChanBondApi.h"

#ifdef __cplusplus
extern "C" {
#endif

//#define _MXL_BRING_UP__ 1

#define MXL_HYDRA_CAP_MIN     10
#define MXL_HYDRA_CAP_MAX     33

#define MXL_HYDRA_PLID_REG_READ       0xFB   // Read register PLID
#define MXL_HYDRA_PLID_REG_WRITE      0xFC   // Write register PLID

#define MXL_HYDRA_PLID_CMD_READ       0xFD   // Command Read PLID
#define MXL_HYDRA_PLID_CMD_WRITE      0xFE   // Command Write PLID

#define MXL_HYDRA_REG_SIZE_IN_BYTES   4      // Hydra register size in bytes
#define MXL_HYDRA_I2C_HDR_SIZE        (2 * sizeof(UINT8))   // PLID + LEN(0xFF)
#define MXL_HYDRA_CMD_HEADER_SIZE     (MXL_HYDRA_REG_SIZE_IN_BYTES+MXL_HYDRA_I2C_HDR_SIZE)

#define MXL_HYDRA_SKU_ID_581 0
#define MXL_HYDRA_SKU_ID_584 1
#define MXL_HYDRA_SKU_ID_585 2
#define MXL_HYDRA_SKU_ID_544 3
#define MXL_HYDRA_SKU_ID_561 4
#define MXL_HYDRA_SKU_ID_582 5
#define MXL_HYDRA_SKU_ID_568 6

// macro for register write data buffer size (PLID + LEN (0xFF) + RegAddr + RegData)
#define MXL_HYDRA_REG_WRITE_LEN       (MXL_HYDRA_I2C_HDR_SIZE + (2 * MXL_HYDRA_REG_SIZE_IN_BYTES))

// maro to extract a single byte from 4-byte(32-bit) data
#define GET_BYTE(x,n)  (((x) >> (8*(n))) & 0xFF)

#define MXL_HYDRA_GPIO_IN_PINMUX_SEL 5
#define MXL_HYDRA_BITS_IN_REGISTER 32
#define MXL_HYDRA_DEV_5X1_GPIO_MAX 34
#define MXL_HYDRA_DEV_5X2_GPIO_MAX 29

#define MXL_GET_REG_MASK_32(lsbLoc,numOfBits) ((0xFFFFFFFF >> (32 - (numOfBits))) << (lsbLoc))

#define GET_REG_FIELD_DATA(devId, fieldName, dataPtr) MxLWare_Hydra_ReadByMnemonic(devId, fieldName, dataPtr);
#define SET_REG_FIELD_DATA(devId, fieldName, data) MxLWare_Hydra_UpdateByMnemonic(devId, fieldName, data);

#define FW_DL_SIGN (0xDEADBEEF)

#define DMA_I2C_INTERRUPT_ADDR 0x8000011C
#define DMA_INTR_PROT_WR_CMP 0x08

#define DMA_I2C_READ_LEN_ADDR		0x3FFFEBF8
#define DMA_I2C_READ_LEN_MAX		260	// 4 bytes of Header and 256 bytes payload. Should be a multiple of 4

typedef enum
{
  MXL_CMD_WRITE = 0,
  MXL_CMD_READ
} MXL_CMD_TYPE_E;

#define BUILD_HYDRA_CMD(cmdID, reqType, size, dataPtr, cmdBuff)                                       \
    do {                                                                                              \
      cmdBuff[0] = ((reqType == MXL_CMD_WRITE) ? MXL_HYDRA_PLID_CMD_WRITE : MXL_HYDRA_PLID_CMD_READ); \
      cmdBuff[1] = (size > 251)? 0xFF : (UINT8)(size + 4);                                            \
      cmdBuff[2] = (UINT8)size;                                                                       \
      cmdBuff[3] = (UINT8)cmdID;                                                                      \
      cmdBuff[4] = 0x00;                                                                              \
      cmdBuff[5] = 0x00;                                                                              \
      MxL_CovertDataForEndianness(MXL_ENABLE_BIG_ENDIAN, size, (UINT8 *)dataPtr);                     \
      MXLWARE_OSAL_MEMCPY((void *)&cmdBuff[6], (const void *)dataPtr, size);                          \
    } while(0) //;

typedef struct
{
  UINT32 regAddr;
  UINT8 lsbPos;
  UINT8 numOfBits;
} MXL_REG_FIELD_T;

typedef struct
{
  UINT32 dataSize;
  UINT8 data[DMA_I2C_READ_LEN_MAX];
} MXL_DEV_CMD_DATA_T;

typedef enum
{
  MXL_HYDRA_SKU_54X = 0,
  MXL_HYDRA_SKU_56X,
  MXL_HYDRA_SKU_58X,
  MXL_HYDRA_SKU_MAX
} MXL_HYDRA_SKU_FAMILY_E;

typedef struct
{
  MXL_BOOL_E      firmwareDownloaded;
  MXL_BOOL_E      initialized;
  UINT8           devId;
  MXL_HYDRA_DEVICE_E  deviceType;
  UINT8           chipVersion;
  MXL_HYDRA_SKU_TYPE_E  skuType;

  struct
  {
    MXL_BOOL_E    clkOutAvailable;
    UINT8         tunersCnt;
    UINT8         demodsCnt;
    MXL_BOOL_E    FSKEnabled;
    MXL_BOOL_E    DiSEqCEnabled;
    MXL_BOOL_E    chanBond;
  } features;

  // Broadcast standard
  MXL_HYDRA_BCAST_STD_E bcastStd[MXL_HYDRA_DEMOD_MAX];

  // DSS to DVB encapsulation mode
  MXL_BOOL_E dss2dvbEnacapMode[MXL_HYDRA_DEMOD_MAX];

  // PID filter back to use
  MXL_HYDRA_PID_FILTER_BANK_E pidFilterBank;

  // TS MUX mode in use
  MXL_HYDRA_TS_MUX_TYPE_E tsMuxModeSlice0; // TS0 to TS3
  MXL_HYDRA_TS_MUX_TYPE_E tsMuxModeSlice1; // TS4 to TS7

  // Shared PID filter size, depend on TS MUX mode
  UINT8 sharedPidFilterSize;

  // Allow (MXL_YES) or Drop(MXL_NO) matching PIDs
  MXL_BOOL_E pidFilterType;

  // Command response and data
  MXL_DEV_CMD_DATA_T cmdData;

  MXL_HYDRA_PID_T fixedPidFilt[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_TS_FIXED_PID_FILT_SIZE];
  MXL_HYDRA_PID_T regPidFilt[MXL_HYDRA_DEMOD_MAX][MXL_HYDRA_SHARED_PID_FILT_SIZE_SCORPIUS_DEFAULT];

  // INterrupt Mask
  UINT32 intrMask;

  MXL_HYDRA_MPEG_MODE_E mpegMode[MXL_HYDRA_DEMOD_MAX];

  // XTAL value
  MXL_HYDRA_XTAL_FREQ_E xtalFreq; // XTAL frequency

  MXL_BOOL_E serialInterface;   // MXL_TRUE is serial interface and MXL_FALSE for parallel interface

  UINT8 *tsMap;

  MXL_HYDRA_CHANBOND_GROUP_T cbBondedGroup[MXL_HYDRA_CB_GROUP_MAX];

  UINT8 gpioMaxNum;

  UINT8 maxRegPidEntries;
  UINT8 maxFixPidEntries;

  MXL_REG_FIELD_T *gpioInfoPtr;

  MXL_HYDRA_SKU_FAMILY_E skuFamily;

} MXL_HYDRA_CONTEXT_T;

MXL_STATUS_E MxLWare_HYDRA_Ctrl_GetDeviceContext(UINT8 devId, /*@out@*/ MXL_HYDRA_CONTEXT_T ** deviceContextPtr);

MXL_STATUS_E MxLWare_HYDRA_SendCommand(UINT8 devId, UINT32 size, UINT8 *cmdBuffPtr);

MXL_STATUS_E MxLWare_HYDRA_WriteRegister(UINT8 devId, UINT32 regAddress, UINT32 regData);

MXL_STATUS_E MxLWare_HYDRA_ReadRegister(UINT8 devId, UINT32 regAddress, /*@out@*/ UINT32 *regDataPtr);

MXL_STATUS_E MxLWare_HYDRA_WriteRegisterBlock(UINT8 devId, UINT32 regAddress, UINT32 size, UINT8 *regDataPtr);

MXL_STATUS_E MxLWare_HYDRA_ReadRegisterBlock(UINT8 devId, UINT32 regAddress, UINT32 size, /*@out@*/ UINT8 *regDataPtr);

MXL_STATUS_E MxLWare_HYDRA_CheckForCmdResponse(UINT8 devId, MXL_HYDRA_CONTEXT_T *ctxPtr, UINT8 cmdId);

MXL_STATUS_E MxLWare_HYDRA_WriteFirmwareBlock(UINT8 devId, UINT32 regAddress, UINT32 size, UINT8 *regDataPtr);

// Debug functions
char * MxLWare_HYDRA_DBG_GetDeviceName(MXL_HYDRA_DEVICE_E deviceType);

MXL_HYDRA_DEMOD_ID_E MxL_Ctrl_GetDemodID(MXL_HYDRA_CONTEXT_T *devHandlePtr, MXL_HYDRA_DEMOD_ID_E logicalDemodId);
MXL_STATUS_E MxL_Ctrl_GetTsID(MXL_HYDRA_CONTEXT_T *devHandlePtr, MXL_HYDRA_DEMOD_ID_E logicalDemodId, MXL_HYDRA_DEMOD_ID_E *physicalDemodId);
MXL_STATUS_E MxL_Ctrl_GetPhyTsID(UINT8 devId, MXL_HYDRA_DEMOD_ID_E physicalDemodId, MXL_HYDRA_TS_ID_E *physicalTsId);

MXL_STATUS_E MxLWare_Hydra_ReadByMnemonic(UINT8 devId, UINT32 regAddr, UINT8 lsbLoc, UINT8 numOfBits, /*@out@*/ UINT32 *dataPtr);
MXL_STATUS_E MxLWare_Hydra_UpdateByMnemonic(UINT8 devId, UINT32 regAddr, UINT8 lsbLoc, UINT8 numOfBits, UINT32 data);
MXL_STATUS_E MxLWare_Hydra_Offset_UpdateByMnemonic(UINT8 devId, UINT32 regAddr, UINT8 lsbLoc, UINT8 numOfBits, UINT32 offset, UINT32 data);

void MxLWare_HYDRA_ExtractFromMnemonic(UINT32 regAddr, UINT8 lsbPos, UINT8 width, /*@null@*/ /*@out@*/ UINT32 * toAddr, /*@null@*/ /*@out@*/ UINT8 * toLsbPos, /*@null@*/ /*@out@*/ UINT8 * toWidth);

void MxL_CovertDataForEndianness(UINT8 convertDataFlag, UINT32 size, /*@in@*/ /*@out@*/ UINT8* dataPtr);

SINT32 MxL_Ctrl_SignExt(UINT32 data, UINT32 n);

UINT32 MxL_Get_DiseqcMappingBitMapReverse(MXL_HYDRA_CONTEXT_T * devHandlePtr, UINT32 bitMap);

#ifdef __cplusplus
}
#endif

#endif

