/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_drv_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/21
  Description   :
  History       :
  1.Date        : 2009/12/21
    Author      : sdk
    Modification: Created file

******************************************************************************/
#ifndef __HI_DRV_PVR_H__
#define __HI_DRV_PVR_H__


#include "hi_type.h"

#include "hi_unf_pvr.h"
#include "hi_mpi_pvr.h"

#ifdef HI_TEE_PVR_SUPPORT
typedef struct tagPVR_TEE_GEN_VALUE_ARGS_S
{
    HI_U32 u32Args[8];/*Input:from 0 -->7; output:from 7-->0*/
}PVR_TEE_GEN_VALUE_ARGS_S;
#endif

typedef struct tagPVR_CHAN_INFO_S
{
    HI_BOOL bUsed;
    HI_U32 u32DeCodeAbilityUsed;
    pid_t owner;
}PVR_CHAN_INFO_S;

typedef struct tagPVR_DeCodeAbility_INFO_S
{
    HI_U32 u32ChnId;
    HI_U32 u32DeCodeAbilityValue;
}PVR_DECODEABILITY_INFO_S;

/* definition of max play channel */
#define PVR_PLAY_MAX_CHN_NUM            5

/* definition of max record channel */
#if    defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)
#define PVR_REC_MAX_CHN_NUM             32
#else
#define PVR_REC_MAX_CHN_NUM             10
#endif
#define PVR_REC_START_NUM               PVR_PLAY_MAX_CHN_NUM

#define CMD_PVR_INIT_PLAY               _IOR(HI_ID_PVR, 0x01, HI_U32)
#define CMD_PVR_CREATE_PLAY_CHN         _IOR(HI_ID_PVR, 0x02, HI_U32)
#define CMD_PVR_DESTROY_PLAY_CHN        _IOW(HI_ID_PVR, 0x03, HI_U32)
#define CMD_PVR_GET_DECODE_ABILITY      _IOR(HI_ID_PVR, 0x04, HI_U32)
#define CMD_PVR_ACQUIRE_DECODE_ABILITY  _IOWR(HI_ID_PVR, 0x05, PVR_DECODEABILITY_INFO_S)
#define CMD_PVR_RELEASE_DECODE_ABILITY  _IOW(HI_ID_PVR, 0x06, PVR_DECODEABILITY_INFO_S)

#define CMD_PVR_INIT_REC                _IOR(HI_ID_PVR, 0x11, HI_U32)
#define CMD_PVR_CREATE_REC_CHN          _IOR(HI_ID_PVR, 0x12, HI_U32)
#define CMD_PVR_DESTROY_REC_CHN         _IOW(HI_ID_PVR, 0x13, HI_U32)
#ifdef HI_TEE_PVR_SUPPORT
#define CMD_PVR_TEE_REC_OPEN            _IOWR(HI_ID_PVR, 0x20, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_REC_CLOSE           _IOW(HI_ID_PVR, 0x21, HI_U32)
#define CMD_PVR_TEE_REC_COPY_REE_TEST   _IOWR(HI_ID_PVR, 0x22, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_REC_PROCESS_TS_DATA _IOW(HI_ID_PVR, 0x23, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_REC_GET_STATE       _IOW(HI_ID_PVR, 0x24, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_REC_GET_ADDRINFO    _IOWR(HI_ID_PVR, 0x25, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_PLAY_COPY_FROM_REE  _IOW(HI_ID_PVR, 0x30, PVR_TEE_GEN_VALUE_ARGS_S)
#define CMD_PVR_TEE_PLAY_PROCESS_DATA   _IOW(HI_ID_PVR, 0x31, PVR_TEE_GEN_VALUE_ARGS_S)
#endif

#if    defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3716mv450)
#define PVR_PLAY_DECODE_ABILITY (65 * 1920 * 1080)
#elif  defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798cv200)
#define PVR_PLAY_DECODE_ABILITY (120 * 1920 * 1080)
#else
#define PVR_PLAY_DECODE_ABILITY (30 * 1920 * 1080)
#endif

#endif
