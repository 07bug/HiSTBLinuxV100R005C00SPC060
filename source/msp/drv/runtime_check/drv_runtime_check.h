/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name             :    drv_runtime_check.h
  Version               :     Initial Draft
  Author                :     Hisilicon multimedia software group
  Created               :     2014/10/18
  Last Modified        :
  Description          :
  Function List        :
  History                :
  1.Date                 :     2014/10/18
    Author               :
    Modification        :    Created file

******************************************************************************/

#ifndef __DRV_RUNTIME_CHECK_H__
#define __DRV_RUNTIME_CHECK_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#ifdef HI_ROOTFS_RUNTIME_CHECK_ENABLE
void set_hash_calculate_flag(HI_BOOL bCalulate);
HI_BOOL get_hash_calculate_flag(void);
HI_BOOL get_runtime_check_enable_flag(void);
#endif
void set_fisrt_copy_flag(HI_BOOL bFistCopy);
void set_suspend_flag(HI_BOOL bRuntimeCheckSuspend);
void delete_timer(void);
#endif

HI_S32  DRV_RUNTIME_CHECK_Init(HI_VOID);
HI_VOID DRV_RUNTIME_CHECK_Exit(HI_VOID);
HI_VOID DRV_RUNTIME_CHECK_ConfigLPC(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

