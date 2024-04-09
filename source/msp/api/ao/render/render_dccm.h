/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : render_dccm.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/07/18
  Description  :
  History       :
  1.Date        : 2017/07/18
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __RENDER_DCCM_H__
#define  __RENDER_DCCM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef HI_VOID*  HI_DCCM_HANDLE;

HI_S32  DCCM_Init(HI_DCCM_HANDLE* phDccm);
HI_VOID DCCM_DeInit(HI_DCCM_HANDLE hDccm);
HI_VOID DCCM_ApplyPolicy(HI_DCCM_HANDLE hDccm, HI_U32 u32PtsMs);
HI_BOOL DCCM_CheckIsNeedDecode(HI_DCCM_HANDLE hDccm);
HI_VOID DCCM_Reset(HI_DCCM_HANDLE hDccm);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
