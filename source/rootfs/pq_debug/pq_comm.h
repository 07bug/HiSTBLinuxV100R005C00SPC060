/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_comm.h
  Version       : Initial Draft
  Author        : Hisilicon PQ software group
  Created       : 2013/06/04
  Description   : pq common define

******************************************************************************/

#ifndef __PQ_COMM_H__
#define __PQ_COMM_H__


#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_drv_struct.h"
#include "drv_pq_define.h"
#include "pq_comm_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif/*cplusplus*/

#define VDP_PQ_NAME  "/dev/"UMAP_DEVNAME_PQ

typedef struct hiPQ_FLASH_INFO_S
{
    HI_CHAR             Name[32];
    HI_U32              u32Offset;
    HI_U32              u32Size;
} PQ_FLASH_INFO_S;
/*--------------------------------------------------------------------------------*
Function        :HI_S32  PQ_DRV_Tool_Init()
Description     : ��ʼ��PQ�豸 ģ��
Input           :NA
Output
Return          :HI_SUCCESS, ��ʼ���ɹ�
                   :HI_FAILURE, ��ʼ��ʧ��
Others          :NA
*--------------------------------------------------------------------------------*/

HI_S32                PQ_DRV_Tool_Init(HI_VOID);

/*--------------------------------------------------------------------------------*
Function        :HI_S32  PQ_DRV_Tool_Deinit()
Description     : ȥ��ʼ��PQ�豸 ģ��
Input           :NA
Output          :NA
Return          :HI_SUCCESS, ȥ��ʼ���ɹ�
                   :HI_FAILURE, ȥ��ʼ��ʧ��
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32                PQ_DRV_Tool_Deinit(HI_VOID);


/*--------------------------------------------------------------------------------*
Function        :PQ_DRV_Tool_WriteReg(HI_U32 u32RegAddr, HI_U32 u32Value)
Description     : д����Ĵ���
Input           :u32RegAddr, ��Ҫд��ļĴ�����ַ�u
                    u32Value,д���ֵ
                    *pstBitRange  ��Ҫ��ȡ�ļĴ�������λ
Output          :NA
Return          :HI_SUCCESS
                   :HI_FAILURE
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_DRV_Tool_WriteReg(HI_U32 u32RegAddr, HI_U32 u32Value, PQ_DBG_BIT_RANGE_S* pstBitRange);


/*--------------------------------------------------------------------------------*
Function        :PQ_DRV_Tool_ReadReg(HI_U32 u32RegAddr, HI_U32 u32Value, PQ_DBG_BIT_RANGE_S* pstBitRange)
Description     : ������Ĵ���
Input           :u32RegAddr, ��Ҫ��ȡ�ļĴ�����ַ
                    *pstBitRange  ��Ҫ��ȡ�ļĴ�������λ
Output          :pu32Value����ȡ��ֵ
Return          :HI_SUCCESS
                   :HI_FAILURE
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_DRV_Tool_ReadReg(HI_U32 u32RegAddr, HI_U32* pu32Value, PQ_DBG_BIT_RANGE_S* pstBitRange);



/*--------------------------------------------------------------------------------*
Function        :PQ_DRV_Tool_ReadGroupPara(HI_U32 u32RegAddr, HI_U32* pu32Value,HI_U32 u32Len)
Description     : ������Ĵ���
Input             :u32RegAddr, ��Ҫ��ȡ������Ĵ�����ַ(�����Ϊ������ID)
                    :u32Len ,��Ҫ��ȡ�ĳ��ȣ�����У��
Output          :pu32Value����ȡ��ֵ
Return          :HI_SUCCESS
                   :HI_FAILURE
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_DRV_Tool_ReadFromPqDriver(HI_U32 u32RegAddr, HI_U32* pu32Data, HI_U32 u32Len);

/*--------------------------------------------------------------------------------*
Function        :PQ_DRV_Tool_WriteGroupPara(HI_U32 u32RegAddr, const HI_U32* pu32Value,HI_U32 u32Len)
Description     : ������Ĵ���
Input             :u32RegAddr, ��Ҫд�������Ĵ�����ַ(�����Ϊ������ID)
                    :u32Len ,��Ҫд��ĳ��ȣ�����У��
Output          :pu32Value��д���ֵ
Return          :HI_SUCCESS
                   :HI_FAILURE
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_DRV_Tool_WriteToPqDriver(HI_U32 u32RegAddr, const HI_U32* pu32Data, HI_U32 u32Len);

HI_S32 PQ_DRV_Tool_WriteACM(HI_U32 u32RegAddr, HI_U8* pu8Buffer, HI_U32 u32BufferLen);

HI_S32 PQ_DRV_Tool_ReadDCI(HI_U32 u32RegAddr, HI_U8* pu8Buffer, HI_U32 u32BufferLen);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/*__cplusplus*/

#endif/*__MPI_PQ_COMM_H__*/
