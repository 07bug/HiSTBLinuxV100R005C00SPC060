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

#ifndef __MXL_HDR_DEVICEAPI_H__
#define __MXL_HDR_DEVICEAPI_H__

/*****************************************************************************************
    Include Header Files
*****************************************************************************************/

#include "MxLWare_HYDRA_DemodTunerApi.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************
    Macros
*****************************************************************************************/

/** @brief Max number of HYDRA devices that can be managed by a MxLWare driver */
#define MXL_HYDRA_MAX_NUM_DEVICES             4

/** @brief MxL device version size in bytes */
#define MXL_HYDRA_VERSION_SIZE                5 //!< (A.B.C.D-RCx)

// Interrupts mask
// Firmware error status
#define MXL_HYDRA_INTR_ERR                      (1 << 23)
// FW mesg pending flag - dbg only
#define MXL_HYDRA_INTR_MSG_PENDING              (1 << 22)
// Enable INTR
#define MXL_HYDRA_INTR_EN                       (1 << 15)
// RF Wakeup
#define MXL_HYDRA_INTR_RF_WAKEUP                (1 << 13)

#define MXL_HYDRA_INTR_BROADCAST_WAKEUP         (1 << 12)

// Demod lock
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_7           (1 << 11)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_6           (1 << 10)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_5           (1 << 9)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_4           (1 << 8)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_3           (1 << 7)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_2           (1 << 6)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_1           (1 << 5)
#define MXL_HYDRA_INTR_DMD_FEC_LOCK_0           (1 << 4)

// DiSEqC INTR's
#define MXL_HYDRA_INTR_DISEQC_0                 (1 << 0)
#define MXL_HYDRA_INTR_DISEQC_1                 (1 << 1)
#define MXL_HYDRA_INTR_DISEQC_2                 (1 << 2)
#define MXL_HYDRA_INTR_DISEQC_3                 (1 << 3)

// FSK
#define MXL_HYDRA_INTR_FSK                      (1 << 0)

/*****************************************************************************************
    User-Defined Types (Typedefs)
*****************************************************************************************/

/** @brief Hydra device type */
typedef enum
{
  MXL_HYDRA_DEVICE_581 = 0,
  MXL_HYDRA_DEVICE_584,
  MXL_HYDRA_DEVICE_585,
  MXL_HYDRA_DEVICE_544,
  MXL_HYDRA_DEVICE_561,
  MXL_HYDRA_DEVICE_TEST,
  MXL_HYDRA_DEVICE_582,
  MXL_HYDRA_DEVICE_541,
  MXL_HYDRA_DEVICE_568,
  MXL_HYDRA_DEVICE_542,
  MXL_HYDRA_DEVICE_541S,
  MXL_HYDRA_DEVICE_561S,
  MXL_HYDRA_DEVICE_581S,

  // Ceres SKUs
  MXL_HYDRA_DEVICE_541C,
  MXL_HYDRA_DEVICE_542C,
  MXL_HYDRA_DEVICE_581C,
  MXL_HYDRA_DEVICE_582C,
  MXL_HYDRA_DEVICE_MAX
} MXL_HYDRA_DEVICE_E;

typedef enum
{
  MXL_HYDRA_XTAL_24_MHz = 0,
  MXL_HYDRA_XTAL_27_MHz
} MXL_HYDRA_XTAL_FREQ_E;

typedef struct
{
  MXL_HYDRA_XTAL_FREQ_E xtalFreq; // XTAL frequency
  UINT8 xtalCap;                  // XTAL Capacitance value (12pF to 18pF (default))
} MXL_HYDRA_DEV_XTAL_T;

/** @brief Device version info struct */
typedef struct
{
  MXL_HYDRA_DEVICE_E  chipId;                                   //!< SKU type
  UINT8               chipVer;                                  //!< Device version
  UINT8               mxlWareVer[MXL_HYDRA_VERSION_SIZE];       //!< MxLWare version information
  UINT8               firmwareVer[MXL_HYDRA_VERSION_SIZE];      //!< Firmware version information
  UINT8               fwPatchVer[MXL_HYDRA_VERSION_SIZE];       //!< Firmware patch version information
  MXL_BOOL_E          firmwareDownloaded;                       //!< Firmware is downloaded
} MXL_HYDRA_VER_INFO_T;

typedef enum
{
  MXL_HYDRA_CB_FW_DOWNLOAD_STATUS = 0
} MXL_HYDRA_CB_TYPE_E;

typedef struct
{
  UINT8   segmentIndex;
  UINT32  segmentSize;
  UINT32  segmentBytesSent;
} MXL_HYDRA_FIRMWARE_DOWNLOAD_STATS_T;

typedef struct
{
  UINT32 currentSize;
  UINT32 totalSize;
} MXL_HYDRA_FW_DOWNLOAD_CB_PAYLOAD_T;

typedef enum
{
  MXL_HYDRA_FW_DOWNLOAD_CONTINUE = 1,
  MXL_HYDRA_FW_DOWNLOAD_ABORT = 2,
  MXL_HYDRA_FW_DOWNLOAD_MAX
} MXL_HYDRA_FW_DOWNLOAD_E;

typedef enum
{
  MXL_HYDRA_PWR_MODE_ACTIVE = 0,
  MXL_HYDRA_PWR_MODE_STANDBY,
  MXL_HYDRA_PWR_MODE_LP_TUNER,
  MXL_HYDRA_PWR_WAKE_ON_RF,
  MXL_HYDRA_PWR_WAKE_ON_BROADCAST
} MXL_HYDRA_PWR_MODE_E;

typedef enum
{
  MXL_HYDRA_GPIO_DIR_INPUT = 0,   // GPIO pin as INPUT
  MXL_HYDRA_GPIO_DIR_OUTPUT = 1,   // GPIO pin as OUTPUT
  MXL_HYDRA_GPIO_DIR_MAX
} MXL_HYDRA_GPIO_DIR_E;

typedef enum
{
  MXL_HYDRA_GPIO_DATA_LOW = 0,   // Clear GPO pin
  MXL_HYDRA_GPIO_DATA_HIGH = 1,   // Set GPO pin
  MXL_HYDRA_GPIO_DATA_MAX
} MXL_HYDRA_GPIO_DATA_E;

typedef enum
{
  HYDRA_HOST_INTR_TYPE_NONE,           // polling
  HYDRA_HOST_INTR_TYPE_EDGE_POSITIVE,  // default
  HYDRA_HOST_INTR_TYPE_EDGE_NEGATIVE,
  HYDRA_HOST_INTR_TYPE_LEVEL_POSITIVE_SELF_CLEAR,
  HYDRA_HOST_INTR_TYPE_LEVEL_NEGATIVE_SELF_CLEAR,
  HYDRA_HOST_INTR_TYPE_LEVEL_POSITIVE,
  HYDRA_HOST_INTR_TYPE_LEVEL_NEGATIVE,
} HYDRA_HOST_INTR_TYPE_E;

typedef struct
{
  HYDRA_HOST_INTR_TYPE_E  intrType;
  UINT32                  intrDurationInNanoSecs;
} MXL_HYDRA_INTR_CFG_T;

/*****************************************************************************************
    Prototypes
*****************************************************************************************/

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevXtal(UINT8 devId, MXL_HYDRA_DEV_XTAL_T * xtalParam, MXL_BOOL_E enableClkOut);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevFWDownload(UINT8 devId, UINT32 mbinBufferSize, UINT8 *mbinBufferPtr, MXL_CALLBACK_FN_T fwCallbackFn);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevInterrupt(UINT8 devId, MXL_HYDRA_INTR_CFG_T intrCfg, UINT32 intrMask);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDevInterruptStatus(UINT8 devId, UINT32 * intrStatus, UINT32 * intrMask);

MXL_STATUS_E MxLWare_HYDRA_API_CfgClearDevtInterrupt(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_API_ReqDevVersionInfo(UINT8 devId, MXL_HYDRA_VER_INFO_T *versionInfoPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevPowerMode(UINT8 devId, MXL_HYDRA_PWR_MODE_E pwrMode);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevWakeOnRF(UINT8 devId, MXL_HYDRA_TUNER_ID_E tunerId, UINT32 wakeTimeInSeconds, SINT32 rssiThreshold);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevWakeOnPidParams(UINT8 devId,
                              MXL_HYDRA_TUNE_PARAMS_T * chanTuneParamsPtr,
                              MXL_BOOL_E interruptLockFail, UINT16 awakeTimeInSeconds, 
                              UINT16 sleepTimeInSeconds, UINT16 magicPid,
                              UINT8 * matchBufferPtr, UINT8 * maskBufferPtr);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevStartBroadcastWakeUp(UINT8 devId);

MXL_STATUS_E MxLWare_HYDRA_API_CfgDevOverwriteDefault(UINT8 devId);

MXL_STATUS_E  MxLWare_HYDRA_API_CfgDevGPIODirection(UINT8 devId, UINT8 gpioId, MXL_HYDRA_GPIO_DIR_E gpioDir);

MXL_STATUS_E  MxLWare_HYDRA_API_CfgDevGPOData(UINT8 devId, UINT8 gpioId, MXL_HYDRA_GPIO_DATA_E gpioData);

MXL_STATUS_E  MxLWare_HYDRA_API_ReqDevGPIData(UINT8 devId, UINT8 gpioId, MXL_HYDRA_GPIO_DATA_E *gpioDataPtr);

MXL_STATUS_E  MxLWare_HYDRA_API_ReqDevTemperature(UINT8 devId, SINT16 *devTemperatureInCelsiusPtr);

#ifdef __cplusplus
}
#endif

#endif /* __MXL_HDR_COMMONAPI_H__*/

