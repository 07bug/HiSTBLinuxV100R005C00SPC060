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


#ifndef __MXL_FW_DOWNLOAD_H__
#define __MXL_FW_DOWNLOAD_H__

#include "MaxLinearDataTypes.h"
#include "MxLWare_HYDRA_PhyCtrl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MBIN_FORMAT_VERSION               '1'
#define MBIN_FILE_HEADER_ID               'M'
#define MBIN_SEGMENT_HEADER_ID            'S'
#define MBIN_MAX_FILE_LENGTH              (1<<23)

typedef struct
{
  UINT8 id;
  UINT8 fmtVersion;
  UINT8 headerLen;
  UINT8 numSegments;
  UINT8 entryAddress[4];
  UINT8 imageSize24[3];
  UINT8 imageChecksum;
  UINT8 reserved[4];
} MBIN_FILE_HEADER_T;

typedef struct
{
  MBIN_FILE_HEADER_T  header;
  UINT8 data[1];
} MBIN_FILE_T;

typedef struct
{
  UINT8 id;
  UINT8 len24[3];
  UINT8 address[4];
} MBIN_SEGMENT_HEADER_T;

typedef struct
{
  MBIN_SEGMENT_HEADER_T header;
  UINT8 data[1];
} MBIN_SEGMENT_T;

MXL_STATUS_E MxLWare_FW_Download(UINT8 devId, UINT32 mbinBufferSize, const UINT8 *mbinBufferPtr, /*@null@*/ MXL_CALLBACK_FN_T fwCallbackFn);

#ifdef __cplusplus
}
#endif

#endif //__MXL_FW_DOWNLOAD_H__

