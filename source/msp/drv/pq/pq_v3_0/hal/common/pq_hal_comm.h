/******************************************************************************
*
* Copyright (C) 2014-2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_comm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_COMM_H__
#define __PQ_HAL_COMM_H__

#ifndef  __PQ_PLATFORM_BOOT__
#include <linux/fs.h>
#endif
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_reg_common.h"
#include "hi_drv_pq.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define REG_BASE_ADDR_MASK     0xffff0000
#define REG_OFFSET_ADDR_MASK   0x0000ffff

#define VPSS_HANDLE_NUM    16
#define VDP_CHN_MAX        3

#define PQ_KMALLOC(fmt...) HI_KMALLOC(HI_ID_PQ, fmt)

#define PQ_KFREE_SAFE(ptr) \
    do{\
        if (HI_NULL!=ptr)\
        {\
            HI_KFREE(HI_ID_PQ, ptr);\
            ptr=HI_NULL;\
        }\
    }while(0)

#define PQ_VMALLOC(fmt...)  HI_VMALLOC(HI_ID_PQ, fmt)

#define PQ_VFREE_SAFE(ptr) \
    do{\
        if (HI_NULL!=ptr)\
        {\
            HI_VFREE(HI_ID_PQ, ptr);\
            ptr=HI_NULL;\
        }\
    }while(0)


#define VDP_VP_MAX         2

#define VID_MAX            5 /* in 98c equal to 8; but equal to 5 in 98m and 98m_a*/

#define VDP_CHN_OFFSET     0x400
#define VDP_VID_OFFSET     0x800
#define VDP_VP_OFFSET      0x800


#define PQ_TRACE(level, range, fmt...) \
    do{\
        if (level <= range)\
        {\
            HI_TRACE(HI_LOG_LEVEL_ERROR, HI_ID_PQ, fmt);\
        }\
    }while(0)

#define PQ_CHECK_NULL_PTR_RE_FAIL(ptr) \
    do{\
        if (NULL == ptr){\
            HI_ERR_PQ("%s ptr is NULL!\n",#ptr);\
            return HI_FAILURE;\
        }\
    }while(0)

#define PQ_CHECK_NULL_PTR_RE_NULL(ptr) \
    do{\
        if (NULL == ptr){\
            HI_ERR_PQ("%s ptr is NULL!\n",#ptr);\
            return;\
        }\
    }while(0)

#define PQ_CHECK_OVER_RANGE_RE_FAIL(ID, MaxID) \
    do{\
        if (ID >= MaxID){\
            HI_ERR_PQ("[%d] over range!\n",ID);\
            return HI_FAILURE;\
        }\
    }while(0)

#define PQ_CHECK_OVER_RANGE_RE_NULL(ID, MaxID) \
    do{\
        if (ID >= MaxID){\
            HI_ERR_PQ("[%d] over range!\n",ID);\
            return;\
        }\
    }while(0)

#define PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(num, MAX) \
    do{\
        if (num > MAX){\
            HI_ERR_PQ("[%d] num over range!\n",num);\
            return HI_FAILURE;\
        }\
    }while(0)

#define PQ_CHECK_NUM_OVER_RANGE_RE_NULL(num, MAX) \
    do{\
        if (num > MAX){\
            HI_ERR_PQ("[%d] num over range!\n",num);\
            return;\
        }\
    }while(0)

#define PQ_CHECK_ZERO_RE_FAIL(num) \
    do{\
        if (0 == num){\
            HI_ERR_PQ("[%d] denominator is zero !\n",num);\
            return HI_FAILURE;\
        }\
    }while(0)

#define PQ_CHECK_ZERO_RE_NULL(num) \
    do{\
        if (0 == num){\
            HI_ERR_PQ("[%d] denominator is zero !\n",num);\
            return;\
        }\
    }while(0)

#define PQ_DBG() \
    do{\
        HI_PRINT("<-PQ DBG->%s %d\n",__func__,__LINE__);\
    }while(0)

#define PQ_SAFE_MEMCPY(dst, src, size)   memcpy(dst, src, size)
#define PQ_SAFE_MEMSET(src, value, size) memset(src, value, size)


#ifdef PQ_PROC_CTRL_SUPPORT
#define pqprint(type, fmt, arg...)  PQ_HAL_PrintMsg(type, fmt, ##arg)
#else
#define pqprint(type, fmt, arg...)
#endif


/*PQ Bin Module����*/
typedef enum hiPQ_PRN_TYPE_E
{
    PQ_PRN_NOTHING  = 0,          /*����ӡ��Ϣ����ʼ��ʱʹ��*/
    PQ_PRN_FATAL    = 0x1,        /*�����쳣��fatal error��������δ֪�쳣*/
    PQ_PRN_ERROR    = 0x2,        /*һ���쳣��error���������﷨����*/
    PQ_PRN_WARNING  = 0x4,        /*�澯�쳣*/
    PQ_PRN_INFO     = 0x8,        /*֪ͨ��Ϣ*/
    PQ_PRN_DBG      = 0x10,       /*������Ϣ*/

    PQ_PRN_VPSS     = 0x20,       /*VPSS ������Ϣ*/
    PQ_PRN_VDP      = 0x40,       /*VDP ������Ϣ*/
    PQ_PRN_TABLE    = 0x80,       /*PQ Table ������Ϣ��ӡ*/

    PQ_PRN_DEI      = 0x100,      /*DEI �㷨������Ϣ��ӡ*/
    PQ_PRN_FMD_READ = 0x200,      /*FMD_READ �㷨������Ϣ��ӡ*/
    PQ_PRN_FMD_CALC = 0x400,      /*FMD_CALC �㷨������Ϣ��ӡ*/
    PQ_PRN_HSHARPEN = 0x800,      /*HSHARPEN �㷨������Ϣ��ӡ*/
    PQ_PRN_DNR      = 0x1000,     /*DNR �㷨������Ϣ��ӡ*/
    PQ_PRN_DCI      = 0x2000,     /*DCI �㷨������Ϣ��ӡ*/
    PQ_PRN_ACM      = 0x4000,     /*ACM �㷨������Ϣ��ӡ*/
    PQ_PRN_SHARPEN  = 0x10000,    /*SHARPEN �㷨������Ϣ��ӡ*/
    PQ_PRN_SR       = 0x20000,    /*SR �㷨������Ϣ��ӡ*/
    PQ_PRN_DB_READ  = 0x40000,    /*DB_READ �㷨������Ϣ��ӡ*/
    PQ_PRN_DB_CALC  = 0x80000,    /*DB_CALC �㷨������Ϣ��ӡ*/
    PQ_PRN_DM       = 0x100000,   /*DM �㷨������Ϣ��ӡ*/
    PQ_PRN_CSC      = 0x200000,   /*CSC �㷨������Ϣ��ӡ*/
    PQ_PRN_ZME      = 0x400000,   /*ZME �㷨������Ϣ��ӡ*/
    PQ_PRN_TNR      = 0x800000,   /*TNR �㷨������Ϣ��ӡ*/

    PQ_PRN_ALWS     = 0xffffffff  /*���ܿش�ӡ*/
} PQ_PRN_TYPE_E;

typedef enum tagPQ_HAL_LAYER_VP_E
{
    VDP_LAYER_VP0   = 0,
    VDP_LAYER_VP1   = 1,
    VDP_LAYER_DHD0  = 2,

    VDP_LAYER_VP_BUTT

} PQ_HAL_LAYER_VP_E;


typedef enum tagVDP_LAYER_VID_E
{
    VDP_LAYER_VID0  = 0, /* VDP_LAYER_V0 */
    VDP_LAYER_VID1  = 1, /* VDP_LAYER_V1 */
    VDP_LAYER_VID2  = 2, /* VDP_LAYER_V2 */
    VDP_LAYER_VID3  = 3, /* VDP_LAYER_V3 */
    VDP_LAYER_VID4  = 4, /* VDP_LAYER_V4 */

    VDP_LAYER_VID5  = 5, /* VDP_LAYER_V5 */
    VDP_LAYER_VID6  = 6, /* for FI pixel */ /* using in VDP */
    VDP_LAYER_VID7  = 7, /* for FI info  */ /* using in VDP */

    VDP_LAYER_VID_BUTT

} VDP_LAYER_VID_E;


/* PQģ�鿪����Ϣ */
typedef struct hiPQ_HAL_MODULE_S
{
    HI_BOOL                     bFMD;         /*FMD����*/
    HI_BOOL                     bTNR;         /*NR����*/
    HI_BOOL                     bCCCL;        /*CCCL����*/
} PQ_HAL_MODULE_S;

/**
 \brief ��ʼ��HALģ�飬���뱾�ؼĴ����ڴ�;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_Init(HI_VOID);

/**
 \brief ȥ��ʼ��HALģ��,�ͷű��ؼĴ����ڴ�;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_Deinit(HI_VOID);

/**
 \brief ����VPSS�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo  : VPSSͨ����
 \param[in] *pstVPSSReg  : �������������ļĴ���ָ��

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVpssReg(HI_U32 u32HandleNo, S_CAS_REGS_TYPE *pstVPSSReg, S_VPSSWB_REGS_TYPE *pstVPSSWbcReg);


/**
 \brief ����VDP�Ĵ���;
 \attention \n
  ��

 \param[in] *pstVDPReg  : ��������������VPSS�Ĵ���ָ��

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdateVdpReg(S_VDP_REGS_TYPE *pstVDPReg);

/**
 \brief ����PQ Module���ز���;
 \attention \n
  ��

 \param[in] *pstPQModule

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_UpdatePQModule(PQ_HAL_MODULE_S *pstPQModule);

/**
 \brief ���VPSS��ǰu32HandleNo��Ӧ����Ĵ����Ƿ���Ч;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::HI_S32

 */
HI_S32 PQ_HAL_CheckVpssValid(HI_U32 u32HandleNo);

/**
 \brief ���VDP�Ĵ����Ƿ���Ч;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_S32

 */
HI_S32 PQ_HAL_CheckVdpValid(HI_VOID);

/**
 \brief ��ȡVPSS��ǰ�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::VPSS�Ĵ���ָ��

 */
S_CAS_REGS_TYPE *PQ_HAL_GetVpssReg(HI_U32 u32HandleNo);

/**
 \brief ��ȡVPSS WBC INFO;
 \attention \n
  ��

 \param[in] u32HandleNo

 \retval ::VPSS WBC INFO

 */
S_VPSSWB_REGS_TYPE *PQ_HAL_GetVpssWbcReg(HI_U32 u32HandleNo);

/**
 \brief ��ȡVDP��ǰ�Ĵ���;
 \attention \n
  ��

 \param[in] none

 \retval ::VDP�Ĵ���ָ��

 */
S_VDP_REGS_TYPE *PQ_HAL_GetVdpReg(HI_VOID);

/**
 \brief ��ȡPQ Module���ز���;
 \attention \n
  ��

 \param[in] none

 \retval ::PQ Module�Ĵ���ָ��

 */
PQ_HAL_MODULE_S *PQ_HAL_GetPQModule(HI_VOID);

/**
 \brief д�Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo
 \param[in] u32RegAddr
 \param[in] u32Value

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_WriteRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32 u32Value);

/**
 \brief ���Ĵ���;
 \attention \n
  ��

 \param[in] u32HandleNo
 \param[in] u32RegAddr
 \param[out] *pu32Value

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_ReadRegister(HI_U32 u32HandleNo, HI_U32 u32RegAddr, HI_U32 *pu32Value);

/**
 \brief ������ʼBITλ����U32����;
 \attention \n
  ��

 \param[in] u32Src
 \param[in] u32SrcStartBit
 \param[out] *pu32Dst
 \param[in] u32DstStartBit
 \param[in] u32Num

 \retval ::

 */
HI_VOID PQ_HAL_CopyU32ByBit(HI_U32 u32Src, HI_U32 u32SrcStartBit, HI_U32 *pu32Dst, HI_U32 u32DstStartBit, HI_U32 u32Num);

/**
 \brief ����bitλ����U32����
 \attention \n
  ��

 \param[out] pulData,;
 \param[in] ucBitNo

 \retval ::HI_SUCCESS

 */
HI_VOID  PQ_HAL_U32SetBit( HI_U32 *pulData, HI_U8 ucBitNo);

/**
 \brief ��U32��Ӧ��bitλ����
 \attention \n
  ��

 \param[out] pulData,;
 \param[in] ucBitNo

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_U32ClearBit( HI_U32 *pulData, HI_U8 ucBitNo);

/**
 \brief ��U32�����������λ����ͻ�ȡ��Ӧ��ֵ
 \attention \n
  ��

 \param[in]  ulData,  ucMaxBit,  ucMinBit;

 \retval ::HI_SUCCESS

 */
HI_U32 PQ_HAL_GetU32ByBit( HI_U32 ulData, HI_U8 ucMaxBit, HI_U8 ucMinBit);

/**
 \brief �������λ�����λ����U32������Ӧ��ֵ
 \attention \n
  ��

 \param[in] pulData, ucMaxBit, ucMinBit, ulValue;

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetU32ByBit( HI_U32 *pulData, HI_U8 ucMaxBit, HI_U8 ucMinBit, HI_U32 ulValue);
HI_S32 PQ_HAL_IsVpssReg(HI_U32 u32RegAddr);
HI_S32 PQ_HAL_IsVdpReg(HI_U32 u32RegAddr);
HI_S32 PQ_HAL_IsSpecialReg(HI_U32 u32RegAddr);
HI_U32  PQ_HAL_RegRead(volatile HI_U32 a);
HI_VOID PQ_HAL_RegWrite(volatile HI_U32 a, HI_U32 value);
HI_S32  PQ_REG_RegWrite(volatile HI_U32 *a, HI_U32 b);
HI_U32  PQ_REG_RegRead(volatile HI_U32 *a);
HI_S32  PQ_HAL_PrintMsg(HI_U32 type, const HI_S8 *format, ...);
HI_S32  PQ_HAL_SetPrintType(HI_U32 type);
HI_S32  PQ_HAL_GetVpssDitherEn(HI_U32 u32HandleNo, HI_BOOL *bOnOff);
HI_S32  PQ_HAL_GetDnrDitherEn(HI_U32 u32HandleNo, HI_BOOL *bOnOff);
HI_S32  PQ_HAL_GetVdpDitherEn(HI_BOOL *bOnOff);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __PQ_HAL_COMM_H__ */
