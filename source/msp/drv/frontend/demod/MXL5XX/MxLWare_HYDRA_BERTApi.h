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


#ifndef __MXL_HDR_BERT_API__
#define __MXL_HDR_BERT_API__

#include "MxLWare_HYDRA_DemodTunerApi.h"

#ifdef __cplusplus
extern "C" {
#endif

// BERT sequence type
typedef enum
{
  MXL_BERT_SEQ_PN15 = 0,
  MXL_BERT_SEQ_PN23
} MXL_BERT_SEQUENCE_E;

// BERT packet length
typedef enum
{
  MXL_BERT_PKT_LEN_188 = 0,
  MXL_BERT_PKT_LEN_204,
  MXL_BERT_PKT_LEN_130,
} MXL_BERT_PKT_LEN_E;

// BERT packet header size
typedef enum
{
  MXL_BERT_PKT_HDR_0_BYTES = 0,
  MXL_BERT_PKT_HDR_1_BYTES,
  MXL_BERT_PKT_HDR_3_BYTES,
  MXL_BERT_PKT_HDR_4_BYTES,
} MXL_BERT_PKT_HDR_E;

MXL_STATUS_E MxLWare_HYDRA_API_CfgInitBERT(UINT8 devId,
                                           MXL_HYDRA_DEMOD_ID_E demodId,
                                           MXL_BERT_SEQUENCE_E bertSeqType,
                                           MXL_BERT_PKT_LEN_E bertPktLen,
                                           MXL_BERT_PKT_HDR_E bertPktHdrSize,
                                           MXL_BOOL_E invertBertData,
                                           MXL_BOOL_E invertSequencePolarity,
                                           MXL_BOOL_E invertOutputPolarity);

MXL_STATUS_E MxLWare_HYDRA_API_ReqBERTLockStatus(UINT8 devId,
                                                 MXL_HYDRA_DEMOD_ID_E demodId,
                                                 MXL_BOOL_E *berkLockStatusPtr);

MXL_STATUS_E MxLWare_HYDRA_API_ReqBERTStats(UINT8 devId,
                                            MXL_HYDRA_DEMOD_ID_E demodId,
                                            UINT64 *totalbitCountPtr,
                                            UINT64 *totalbitErrorPtr,
                                            MXL_BOOL_E *bitCountSaturationFlagPtr);


MXL_STATUS_E MxLWare_HYDRA_API_CfgResetBERTStats(UINT8 devId, MXL_HYDRA_DEMOD_ID_E demodId);

#ifdef __cplusplus
}
#endif

#endif
