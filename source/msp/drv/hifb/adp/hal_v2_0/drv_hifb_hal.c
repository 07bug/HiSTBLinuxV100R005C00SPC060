/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : drv_hifb_hal.c
Version          : Initial Draft
Author           : sdk
Created          : 2018/01/01
Description      :
                   G0 : 0xf8cc5000   G1 : 0xf8cc5800  GP0 : 0xf8cc6800
Function List    :

History          :
Date                Author         Modification
2018/01/01          sdk            Created file
*************************************************************************************************/


/***************************** add include here**************************************************/
#include "hi_debug.h"

#include "drv_hifb_adp.h"
#include "drv_hifb_hal.h"

#ifdef HI_BUILD_IN_BOOT
#include "hifb_debug.h"
#include "hi_common.h"
#endif

#include "drv_hifb_config.h"
#include "hi_reg_common.h"

/***************************** Macro Definition *************************************************/
#define STRIDE_ALIGN          16

#define OPTM_HAL_CHECK_NULL_POINT(p) do\
{\
 if (HI_NULL == p)\
    {\
        HIFB_ERROR("can't handle null point.\n");\
        return;\
    }\
}while(0)

#define OPTM_HAL_CHECK_LAYER_VALID(u32Data) do\
 {\
  if (u32Data >= OPTM_GFX_MAX)\
     {\
         HIFB_ERROR("Select Wrong Graph Layer ID\n");\
         return;\
     }\
 }while(0)


#define OPTM_HAL_CHECK_GP_VALID(u32Data) do\
   {\
    if (u32Data >= OPTM_GP_MAX)\
       {\
           HIFB_ERROR("Select Wrong Graph Layer ID\n");\
           return;\
       }\
   }while(0)

#define OPTM_HAL_CHECK_ADDRESS(address) do\
  {\
   if (0 == address)\
      {\
          HIFB_ERROR("set address is null!\n");\
          return;\
      }\
  }while(0)

/***************************** Structure Definition *********************************************/

/***************************** Global Variable declaration **************************************/
static volatile S_VDP_REGS_TYPE* pOptmVdpReg = NULL;

/***************************** API forward declarations *****************************************/

/***************************** API realization **************************************************/

/***************************************************************************************
* func          : OPTM_VDP_DRIVER_Initial
* description   : CNcomment: hal层保存寄存器相关信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID  OPTM_VDP_DRIVER_Initial(volatile HI_U32* virAddr)
{
    pOptmVdpReg = (S_VDP_REGS_TYPE*)virAddr;
}

HI_U32 OPTM_VDP_RegRead(HI_U32* a)
{
   return (*a);
}

HI_VOID OPTM_VDP_RegWrite(HI_U32* a, HI_U32 b)
{
    OPTM_HAL_CHECK_NULL_POINT(a);
    *a = b;
}

#ifdef CONFIG_HIFB_GFX3_TO_GFX5
/***************************************************************************************
* func         : OPTM_VDP_SetLayerConnect
* description  : CNcomment: 设置图形链接到高清通道还是标清通道 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_SetLayerConnect(HI_U32 u32Data)
{
    HI_UNUSED(u32Data);
    return;
}

/***************************************************************************************
* func         : OPTM_VDP_OpenGFX3
* description  : CNcomment: 打开G3 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_OpenGFX3(HI_BOOL bOpen)
{
    HI_UNUSED(bOpen);
    return;
}
#endif

#ifndef HI_BUILD_IN_BOOT
HI_VOID HIFB_HAL_GetDhd0Vtthd3(HI_ULONG *pExpectIntLineNumsForEndCallBack)
{
    if (NULL != pExpectIntLineNumsForEndCallBack)
    {/** 从前消隐开始算的 **/
        *pExpectIntLineNumsForEndCallBack = pOptmVdpReg->DHD0_VTTHD3.bits.vtmgthd3 - (pOptmVdpReg->DHD0_VSYNC2.bits.vfb + 1);
    }
    return;
}

HI_VOID HIFB_HAL_GetDhd0Vtthd(HI_ULONG *pExpectIntLineNumsForVoCallBack)
{
    if (NULL != pExpectIntLineNumsForVoCallBack)
    {/** 从前消隐开始算的 **/
        *pExpectIntLineNumsForVoCallBack = pOptmVdpReg->DHD0_VTTHD.bits.vtmgthd2 - (pOptmVdpReg->DHD0_VSYNC2.bits.vfb + 1);
    }
    return;
}

HI_VOID HIFB_HAL_GetDhd0State(HI_ULONG *pActualIntLineNumsForCallBack,HI_ULONG *pHardIntCntForCallBack)
{
    if (NULL != pActualIntLineNumsForCallBack)
    {/** 从后消隐开始算的 **/
        *pActualIntLineNumsForCallBack = pOptmVdpReg->DHD0_STATE.bits.count_vcnt;
    }
    if (NULL != pHardIntCntForCallBack)
    {/** 从后消隐开始算的 **/
        *pHardIntCntForCallBack = pOptmVdpReg->DHD0_STATE.bits.count_int;
    }
    return;
}

HI_VOID HIFB_HAL_GetWorkedLayerAddr(HI_U32 u32Data, HI_U32 *pu32Addr)
{
    volatile U_GFX_WORK_ADDR GFX_WORK_ADDR;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu32Addr);

    GFX_WORK_ADDR.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_WORK_ADDR.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));

    *pu32Addr = GFX_WORK_ADDR.u32;

    return;
}

HI_VOID HIFB_HAL_GetWillWorkLayerAddr(HI_U32 u32Data, HI_U32 *pu32Addr)
{
    volatile U_GFX_ADDR_L GFX_ADDR_L;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu32Addr);

    GFX_ADDR_L.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pu32Addr = GFX_ADDR_L.u32;

    return;
}
#endif

/***************************************************************************************
* func        : OPTM_VDP_CBM_SetMixerBkg
* description : CNcomment: 设置MIXG0叠加背景色寄存器 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_CBM_SetMixerBkg(OPTM_VDP_CBM_MIX_E u32mixer_id, OPTM_VDP_BKG_S *pstBkg)
{
    volatile U_MIXG0_BKG MIXG0_BKG;
    volatile U_MIXG0_BKALPHA MIXG0_BKALPHA;

    OPTM_HAL_CHECK_NULL_POINT(pstBkg);

    if (u32mixer_id == VDP_CBM_MIXG0)
    {
        /* G0 mixer link */
        MIXG0_BKG.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_BKG.u32)));
        MIXG0_BKG.bits.mixer_bkgy  = pstBkg->u32BkgY;
        MIXG0_BKG.bits.mixer_bkgcb = pstBkg->u32BkgU;
        MIXG0_BKG.bits.mixer_bkgcr = pstBkg->u32BkgV;
        OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_BKG.u32)), MIXG0_BKG.u32);
        /** MIXG0 use SRC OVER alpha **/
        MIXG0_BKALPHA.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_BKALPHA.u32)));
        MIXG0_BKALPHA.bits.mixer_alpha  = pstBkg->u32BkgA;
        OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_BKALPHA.u32)), MIXG0_BKALPHA.u32);
    }
    else if(u32mixer_id == VDP_CBM_MIXG1)
    {
        return ;
    }
    else
    {
        HIFB_ERROR("Select Wrong mixer ID\n");
    }

    return;
}

HI_VOID OPTM_VDP_CBM_GetMixerPrio(OPTM_VDP_CBM_MIX_E u32mixer_id, HI_U32 *pu32prio)
{
    OPTM_HAL_CHECK_NULL_POINT(pu32prio);

    if (u32mixer_id == VDP_CBM_MIXG0)
    {
        *pu32prio = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)));
    }
    else
    {
        *pu32prio= 0;
    }

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_SetMixgPrio
* description  : CNcomment: MIXG0优先级配置寄存器。在vsync处更新有效。
                            mixer_prio_x表示第x个优先级所配置的层。
                            该寄存器为即时寄存器。CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_SetMixgPrio(OPTM_VDP_CBM_MIX_E u32mixer_id,HI_U32 u32prio)
{
    volatile U_MIXG0_MIX MIXG0_MIX;

    if (u32mixer_id == VDP_CBM_MIXG0)
    {
        MIXG0_MIX.u32 = u32prio;
        OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
    }

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_CBM_SetMixerPrio
* description  : CNcomment: 设置图形层叠加优先级，Z序 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_CBM_SetMixerPrio(OPTM_VDP_CBM_MIX_E u32mixer_id,HI_U32 u32layer_id,HI_U32 u32prio)
{
    volatile U_MIXG0_MIX MIXG0_MIX;

    if (u32mixer_id == VDP_CBM_MIXG0)
    {
        switch (u32prio)
        {
            case 0:
            {
                MIXG0_MIX.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio0 = u32layer_id+1;
                OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 1:
            {
                MIXG0_MIX.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio1 = u32layer_id+1;
                OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 2:
            {
                MIXG0_MIX.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio2 = u32layer_id + 2;/** G3 **/
                OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            case 3:
            {
                MIXG0_MIX.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)));
                MIXG0_MIX.bits.mixer_prio3 = u32layer_id+1;
                OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->MIXG0_MIX.u32)), MIXG0_MIX.u32);
                break;
            }
            default:
            {
                HIFB_ERROR("select wrong layer ID\n");
                return ;
            }
        }
    }

    return;
}


//-------------------------------------------------------------------
//GFX_BEGIN
//-------------------------------------------------------------------
/***************************************************************************************
* func         : OPTM_VDP_GFX_GetLayerEnable
* description  : CNcomment: 从寄存器中获取图层是否使能数据 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerEnable(HI_U32 u32Data, HI_U32 *pu32Enable)
{
    volatile U_G0_CTRL G0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu32Enable);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));

    *pu32Enable  = G0_CTRL.bits.surface_en;

    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetLayerEnable
* description  : CNcomment: 设置图层使能 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerEnable(HI_U32 u32Data, HI_U32 u32bEnable)
{
    volatile U_GFX_ADDR_L GFX_ADDR_L;
    volatile U_G0_CTRL G0_CTRL;
    volatile U_GP0_CTRL GP0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_ADDR_L.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    if (0 == GFX_ADDR_L.u32)
    {
        return;
    }

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_CTRL.bits.surface_en = u32bEnable;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_CTRL.u32);

    if (u32Data < 4)
    {
       GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32))));
       GP0_CTRL.bits.surface_en = u32bEnable;
       OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32))), GP0_CTRL.u32);
    }
    else
    {
       GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + CONFIG_HIFB_GP_OFFSET));
       GP0_CTRL.bits.surface_en = u32bEnable;
       OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + CONFIG_HIFB_GP_OFFSET), GP0_CTRL.u32);
    }

    return;
}


/***************************************************************************************
* func         : OPTM_VDP_GFX_SetNoSecFlag
* description  : CNcomment: 设置DDR模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetNoSecFlag(HI_U32 u32Data, HI_U32 u32Enable)
{
    volatile U_G0_CTRL G0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_CTRL.bits.nosec_flag= u32Enable;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_CTRL.u32);

    return;
}


/***************************************************************************************
* func         : OPTM_VDP_GFX_SetDcmpEnable
* description  : CNcomment: 配置解压寄存器，和压缩有关, 现在是无损压缩 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetDcmpEnable(HI_U32 u32Data, HI_U32 u32bEnable)
{
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;
    volatile U_GFX_READ_CTRL GFX_READ_CTRL;

    if (0 != u32Data)
    {
        return;
    }

    GFX_SRC_INFO.u32  = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_INFO.u32))));
    GFX_READ_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_READ_CTRL.u32))));

    GFX_SRC_INFO.bits.dcmp_type = (0 == u32bEnable) ? (0) : (1);
    GFX_READ_CTRL.bits.addr_map_en = 1;

    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_INFO.u32))), GFX_SRC_INFO.u32);
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_READ_CTRL.u32))), GFX_READ_CTRL.u32);

    return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetDcmpARHeadAddr
* description   : CNcomment: 2D或3D左眼AR压缩头地址CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
#if !defined(HI_BUILD_IN_BOOT)
HI_VOID OPTM_VDP_GFX_SetDcmpARHeadAddr(HI_U32 u32Data, HI_U32 ARHeadDdr)
{
    volatile U_GFX_HEAD_ADDR_L GFX_HEAD_ADDR_L;
#ifdef CONFIG_HIFB_MMU_SUPPORT
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
#endif

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_ADDRESS(ARHeadDdr);

    GFX_HEAD_ADDR_L.u32 = ARHeadDdr;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_HEAD_ADDR_L.u32);

#ifdef CONFIG_HIFB_MMU_SUPPORT
   GFX_SMMU_BYPASS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
   #ifdef CONFIG_GFX_MMU_SUPPORT
     GFX_SMMU_BYPASS.bits.smmu_bypass_h2d = 0;
   #else
     GFX_SMMU_BYPASS.bits.smmu_bypass_h2d = 1;
   #endif
     OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SMMU_BYPASS.u32);
#endif
     return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetDcmpGBHeadAddr
* description   : CNcomment: 2D或3D左眼GB压缩头地址CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetDcmpGBHeadAddr(HI_U32 u32Data, HI_U32 GBHeadDdr)
{
    volatile U_GFX_HEAD2_ADDR_L GFX_HEAD2_ADDR_L;
#ifdef CONFIG_HIFB_MMU_SUPPORT
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
#endif

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_ADDRESS(GBHeadDdr);

    GFX_HEAD2_ADDR_L.u32 = GBHeadDdr;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD2_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_HEAD2_ADDR_L.u32);

#ifdef CONFIG_HIFB_MMU_SUPPORT
    GFX_SMMU_BYPASS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
   #ifdef CONFIG_GFX_MMU_SUPPORT
     GFX_SMMU_BYPASS.bits.smmu_bypass_h3d = 0;
   #else
     GFX_SMMU_BYPASS.bits.smmu_bypass_h3d = 1;
   #endif
     OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SMMU_BYPASS.u32);
#endif

     return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetDcmpGBDataAddr
* description   : CNcomment: GB压缩数据地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetDcmpGBDataAddr(HI_U32 u32Data, HI_U32 GBDataDdr)
{
    volatile U_GFX_DCMP_ADDR_L GFX_DCMP_ADDR_L;
#ifdef CONFIG_HIFB_MMU_SUPPORT
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
#endif

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_ADDRESS(GBDataDdr);

    GFX_DCMP_ADDR_L.u32 = GBDataDdr;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_DCMP_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_DCMP_ADDR_L.u32);

#ifdef CONFIG_HIFB_MMU_SUPPORT
    GFX_SMMU_BYPASS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    #ifdef CONFIG_GFX_MMU_SUPPORT
        GFX_SMMU_BYPASS.bits.smmu_bypass_3d = 0;
    #else
        GFX_SMMU_BYPASS.bits.smmu_bypass_3d = 1;
    #endif
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SMMU_BYPASS.u32);
#endif

    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_GFX_GetLayerAddr
* description  : CNcomment: 获取surface 帧buffer地址 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerAddr(HI_U32 u32Data, HI_U32 *pu32Addr)
{
    volatile U_GFX_ADDR_L GFX_ADDR_L;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu32Addr);

    GFX_ADDR_L.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));

    *pu32Addr = GFX_ADDR_L.u32;

    return;
}
#endif

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetLayerAddrEX
* description   : CNcomment: 2D或3D左眼显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerAddrEX(HI_U32 u32Data, HI_U32 u32LAddr)
{
    volatile U_G0_CTRL G0_CTRL;
    volatile U_GFX_ADDR_L GFX_ADDR_L;
#ifdef CONFIG_HIFB_MMU_SUPPORT
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
#endif

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    if ((0 == u32LAddr) && (1 == G0_CTRL.bits.surface_en))
    {
       HIFB_ERROR("set address is null\n");
       return;
    }

    GFX_ADDR_L.u32 = u32LAddr;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_ADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_ADDR_L.u32);

#ifdef CONFIG_HIFB_MMU_SUPPORT
    GFX_SMMU_BYPASS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    #ifdef CONFIG_GFX_MMU_SUPPORT
        GFX_SMMU_BYPASS.bits.smmu_bypass_2d = 0;
    #else
        GFX_SMMU_BYPASS.bits.smmu_bypass_2d = 1;
    #endif
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SMMU_BYPASS.u32);
#endif

    return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_GetLayerStride
* description   : CNcomment: 获取stride CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerStride(HI_U32 u32Data, HI_U32 *pu32Stride)
{
    volatile U_GFX_STRIDE GFX_STRIDE;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu32Stride);

    GFX_STRIDE.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pu32Stride = GFX_STRIDE.bits.surface_stride * STRIDE_ALIGN;

    return;
}
#endif


/***************************************************************************************
* func        : OPTM_GfxSetLayerStride
* description : CNcomment: 设置图层stride CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerStride(HI_U32 u32Data, HI_U32 u32Stride)
{
    volatile U_GFX_STRIDE GFX_STRIDE;
    volatile U_GFX_HEAD_STRIDE GFX_HEAD_STRIDE;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_STRIDE.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_STRIDE.bits.surface_stride = u32Stride / STRIDE_ALIGN;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_STRIDE.u32);


    GFX_HEAD_STRIDE.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_HEAD_STRIDE.bits.head_stride = 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_HEAD_STRIDE.u32);

    return;
}

#if !defined(HI_BUILD_IN_BOOT)
/***************************************************************************************
* func        : OPTM_VDP_GFX_SetGBdataStride
* description : CNcomment: 设置压缩数据GB的stride CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
static inline HI_VOID OPTM_VDP_GFX_SetGBdataStride(HI_U32 u32Data, HI_U32 GBDataStride)
{
    volatile U_GFX_STRIDE GFX_STRIDE;
    volatile U_GFX_HEAD_STRIDE GFX_HEAD_STRIDE;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_STRIDE.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_STRIDE.bits.dcmp_stride = GBDataStride / STRIDE_ALIGN;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_STRIDE.u32);

    GFX_HEAD_STRIDE.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_HEAD_STRIDE.bits.head2_stride = 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_HEAD_STRIDE.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_HEAD_STRIDE.u32);

    return;
}
#endif

HI_VOID DRV_HAL_SetDeCmpDdrInfo(HI_U32 u32Data, HI_U32 ARHeadDdr,HI_U32 ARDataDdr,HI_U32 GBHeadDdr,HI_U32 GBDataDdr,HI_U32 DeCmpStride)
{
#if !defined(HI_BUILD_IN_BOOT)
      OPTM_HAL_CHECK_ADDRESS(ARHeadDdr);
      OPTM_HAL_CHECK_ADDRESS(ARDataDdr);
      OPTM_HAL_CHECK_ADDRESS(GBHeadDdr);
      OPTM_HAL_CHECK_ADDRESS(GBDataDdr);
      OPTM_HAL_CHECK_ADDRESS(DeCmpStride);

      if (0 != u32Data)
      {
         return;
      }

      OPTM_VDP_GFX_SetDcmpARHeadAddr (u32Data,ARHeadDdr);
      OPTM_VDP_GFX_SetLayerAddrEX    (u32Data,ARDataDdr);
      OPTM_VDP_GFX_SetDcmpGBHeadAddr (u32Data,GBHeadDdr);
      OPTM_VDP_GFX_SetDcmpGBDataAddr (u32Data,GBDataDdr);
      OPTM_VDP_GFX_SetLayerStride    (u32Data,DeCmpStride);
      OPTM_VDP_GFX_SetGBdataStride   (u32Data,DeCmpStride);
#else
      HI_UNUSED(u32Data);
      HI_UNUSED(ARHeadDdr);
      HI_UNUSED(ARDataDdr);
      HI_UNUSED(GBHeadDdr);
      HI_UNUSED(GBDataDdr);
      HI_UNUSED(DeCmpStride);
#endif
      return;
}


/***************************************************************************************
* func        : DRV_HAL_GetDeCmpStatus
* description : CNcomment: 获取解压处理信息，调试使用 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID  DRV_HAL_GetDeCmpStatus(HI_U32 u32Data, HI_BOOL *pbARDataDecompressErr, HI_BOOL *pbGBDataDecompressErr)
{
    volatile U_DCMP_WRONG_STA DCMP_WRONG_STA;
    if (0 != u32Data)
    {
        return;
    }
    OPTM_HAL_CHECK_NULL_POINT(pbARDataDecompressErr);
    OPTM_HAL_CHECK_NULL_POINT(pbGBDataDecompressErr);

    DCMP_WRONG_STA.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->DCMP_WRONG_STA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    if (1 == DCMP_WRONG_STA.bits.wrong_ar)
    {
        *pbARDataDecompressErr = HI_TRUE;
    }

    if (1 == DCMP_WRONG_STA.bits.wrong_gb)
    {
        *pbGBDataDecompressErr = HI_TRUE;
    }

    DCMP_WRONG_STA.bits.wrong_ar = 1;
    DCMP_WRONG_STA.bits.wrong_gb = 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->DCMP_WRONG_STA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), DCMP_WRONG_STA.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetLutAddr
* description  : CNcomment: 设置调色板地址 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLutAddr(HI_U32 u32Data, HI_U32 u32LutAddr)
{
    volatile U_PARA_ADDR_VHD_CHN17 PARA_ADDR_VHD_CHN17;
    volatile U_PARA_ADDR_VHD_CHN18 PARA_ADDR_VHD_CHN18;

    HI_UNUSED(u32Data);

    PARA_ADDR_VHD_CHN17.u32 = u32LutAddr;
    PARA_ADDR_VHD_CHN18.u32 = u32LutAddr;

    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_ADDR_VHD_CHN17.u32))), PARA_ADDR_VHD_CHN17.u32);
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_ADDR_VHD_CHN18.u32))), PARA_ADDR_VHD_CHN18.u32);

    return;
}


/***************************************************************************************
* func         : OPTM_VDP_GFX_GetInDataFmt
* description  : CNcomment: 获取输入的像素格式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetInDataFmt(HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E *enDataFmt)
{
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(enDataFmt);

    GFX_SRC_INFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_INFO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *enDataFmt = GFX_SRC_INFO.bits.ifmt ;

    return;
}
#endif


/***************************************************************************************
* func          : OPTM_VDP_GFX_SetInDataFmt
* description   : CNcomment: 输入数据格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetInDataFmt(HI_U32 u32Data, OPTM_VDP_GFX_IFMT_E  enDataFmt)
{
    volatile U_GFX_SRC_INFO GFX_SRC_INFO;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_SRC_INFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_INFO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_SRC_INFO.bits.ifmt = enDataFmt;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_INFO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SRC_INFO.u32);

    return;
}


/***************************************************************************************
* func        : OPTM_VDP_GFX_SetBitExtend
* description : CNcomment: 设置低位扩展模式
                           所谓低位扩展就是比如ARGB1555,R少了3位，这三位如何补齐
                           是用高一位还高几位还是使用0来补齐 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetBitExtend(HI_U32 u32Data, OPTM_VDP_GFX_BITEXTEND_E u32mode)
{
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_OUT_CTRL.bits.bitext = u32mode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_OUT_CTRL.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetColorKey
* description  : CNcomment:设置color key的值CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetColorKey(HI_U32 u32Data,HI_U32  bkeyEn,OPTM_VDP_GFX_CKEY_S *pstKey)
{
    volatile U_GFX_CKEY_MAX GFX_CKEY_MAX;
    volatile U_GFX_CKEY_MIN GFX_CKEY_MIN;
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;

    OPTM_HAL_CHECK_NULL_POINT(pstKey);
    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_CKEY_MAX.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MAX.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_CKEY_MAX.bits.key_r_max = pstKey->u32Key_r_max;
    GFX_CKEY_MAX.bits.key_g_max = pstKey->u32Key_g_max;
    GFX_CKEY_MAX.bits.key_b_max = pstKey->u32Key_b_max;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MAX.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_CKEY_MAX.u32);

    GFX_CKEY_MIN.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MIN.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_CKEY_MIN.bits.key_r_min = pstKey->u32Key_r_min;
    GFX_CKEY_MIN.bits.key_g_min = pstKey->u32Key_g_min;
    GFX_CKEY_MIN.bits.key_b_min = pstKey->u32Key_b_min;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MIN.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_CKEY_MIN.u32);

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_OUT_CTRL.bits.key_en   = bkeyEn;
    GFX_OUT_CTRL.bits.key_mode = pstKey->bKeyMode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_OUT_CTRL.u32);

    return;
}

#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetColorKey(HI_U32 u32Data, HI_U32 *pbkeyEn,OPTM_VDP_GFX_CKEY_S *pstKey)
{
    volatile U_GFX_CKEY_MAX GFX_CKEY_MAX;
    volatile U_GFX_CKEY_MIN GFX_CKEY_MIN;
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pbkeyEn);
    OPTM_HAL_CHECK_NULL_POINT(pstKey);

    GFX_CKEY_MAX.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MAX.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    pstKey->u32Key_r_max = GFX_CKEY_MAX.bits.key_r_max;
    pstKey->u32Key_g_max = GFX_CKEY_MAX.bits.key_g_max;
    pstKey->u32Key_b_max = GFX_CKEY_MAX.bits.key_b_max;

    GFX_CKEY_MIN.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MIN.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    pstKey->u32Key_r_min = GFX_CKEY_MIN.bits.key_r_min;
    pstKey->u32Key_g_min = GFX_CKEY_MIN.bits.key_g_min;
    pstKey->u32Key_b_min = GFX_CKEY_MIN.bits.key_b_min;

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pbkeyEn = GFX_OUT_CTRL.bits.key_en;
    pstKey->bKeyMode = GFX_OUT_CTRL.bits.key_mode;

    return;
}
#endif


/***************************************************************************************
* func         : OPTM_VDP_GFX_SetKeyMask
* description  : CNcomment:设置掩码值，将color key的实际值与掩码值做与操作，这样就可以
                           key掉一个范围值，而不只单个值CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetKeyMask(HI_U32 u32Data, OPTM_VDP_GFX_MASK_S *pstMsk)
{
    volatile U_GFX_CKEY_MASK GFX_CKEY_MASK;

    OPTM_HAL_CHECK_NULL_POINT(pstMsk);
    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_CKEY_MASK.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MASK.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_CKEY_MASK.bits.key_r_msk = pstMsk->u32Mask_r;
    GFX_CKEY_MASK.bits.key_g_msk = pstMsk->u32Mask_g;
    GFX_CKEY_MASK.bits.key_b_msk = pstMsk->u32Mask_b;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MASK.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_CKEY_MASK.u32);

    return;
}

#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetKeyMask(HI_U32 u32Data, OPTM_VDP_GFX_MASK_S *pstMsk)
{
    volatile U_GFX_CKEY_MASK GFX_CKEY_MASK;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pstMsk);

    GFX_CKEY_MASK.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_CKEY_MASK.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    pstMsk->u32Mask_r = GFX_CKEY_MASK.bits.key_r_msk;
    pstMsk->u32Mask_g = GFX_CKEY_MASK.bits.key_g_msk;
    pstMsk->u32Mask_b = GFX_CKEY_MASK.bits.key_b_msk;

    return;
}
#endif


/***************************************************************************************
* func          : OPTM_VDP_GFX_SetReadMode
* description   : CNcomment: 设置图层读取数据模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetReadMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    volatile U_GFX_READ_CTRL GFX_READ_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_READ_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_READ_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_READ_CTRL.bits.read_mode = u32Mode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_READ_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_READ_CTRL.u32);

    return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetParaUpd
* description   : CNcomment: 设置图层更新模式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetParaUpd(HI_U32 u32Data, OPTM_VDP_DISP_COEFMODE_E enMode)
{
    volatile U_PARA_UP_VHD PARA_UP_VHD;

    if ((enMode != VDP_DISP_COEFMODE_LUT) && (enMode != VDP_DISP_COEFMODE_ALL))
    {
        return;
    }

    if (0 == u32Data)
    {
        PARA_UP_VHD.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32))));
        PARA_UP_VHD.bits.para_up_vhd_chn17 = 0x1;
        OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32))), PARA_UP_VHD.u32);
    }
    else
    {
        PARA_UP_VHD.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32))));
        PARA_UP_VHD.bits.para_up_vhd_chn18 = 0x1;
        OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32))), PARA_UP_VHD.u32);
    }

    return;
}

/***************************************************************************************
* func          : OPTM_VDP_GFX_SetThreeDimDofEnable
* description   : CNcomment: 设置景深 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_SetThreeDimDofEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    volatile U_G0_DOF_CTRL G0_DOF_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_DOF_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DOF_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_DOF_CTRL.bits.dof_en = bEnable;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DOF_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_DOF_CTRL.u32);

    return;
}

HI_VOID OPTM_VDP_GFX_SetThreeDimDofStep(HI_U32 u32Data, HI_S32 s32LStep, HI_S32 s32RStep)
{
    volatile U_G0_DOF_STEP G0_DOF_STEP;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_DOF_STEP.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DOF_STEP.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_DOF_STEP.bits.right_step= s32RStep;
    G0_DOF_STEP.bits.left_step = s32LStep;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DOF_STEP.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_DOF_STEP.u32);

    return;
}

/***************************************************************************************
* func        : OPTM_VDP_GFX_GetLayerInRect
* description : CNcomment: 获取图层的输入数据 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_GetLayerInRect(HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *stInRect)
{
    /** LBOX **/
    U_G0_VFPOS G0_VFPOS;
    U_G0_VLPOS G0_VLPOS;
    U_G0_DFPOS G0_DFPOS;
    U_G0_DLPOS G0_DLPOS;

    U_GFX_SRC_CROP GFX_SRC_CROP;
    U_GFX_IRESO GFX_IRESO;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(stInRect);

    G0_VFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    stInRect->u32VX = G0_VFPOS.bits.video_xfpos;
    stInRect->u32VY = G0_VFPOS.bits.video_yfpos;

    G0_DFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    stInRect->u32DXS = G0_DFPOS.bits.disp_xfpos;
    stInRect->u32DYS = G0_DFPOS.bits.disp_yfpos;

    G0_DLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    stInRect->u32DXL = G0_DLPOS.bits.disp_xlpos + 1;
    stInRect->u32DYL = G0_DLPOS.bits.disp_ylpos + 1;

    G0_VLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    stInRect->u32VXL = G0_VLPOS.bits.video_xlpos + 1;
    stInRect->u32VYL = G0_VLPOS.bits.video_ylpos + 1;

    GFX_SRC_CROP.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_CROP.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    stInRect->u32SX = GFX_SRC_CROP.bits.src_crop_x;
    stInRect->u32SY = GFX_SRC_CROP.bits.src_crop_y;

    GFX_IRESO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_IRESO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    stInRect->u32IWth = GFX_IRESO.bits.ireso_w + 1;
    stInRect->u32IHgt = GFX_IRESO.bits.ireso_h + 1;

    return;
}
#endif


/***************************************************************************************
* func          : OPTM_VDP_GFX_SetLayerReso
* description   : CNcomment: 设置图层分辨率 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerReso(HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect)
{
    /** LBOX **/
    volatile U_G0_VFPOS G0_VFPOS;
    volatile U_G0_VLPOS G0_VLPOS;
    volatile U_G0_DFPOS G0_DFPOS;
    volatile U_G0_DLPOS G0_DLPOS;

    U_GFX_SRC_RESO GFX_SRC_RESO;
    U_GFX_SRC_CROP GFX_SRC_CROP;
    U_GFX_IRESO GFX_IRESO;

    OPTM_HAL_CHECK_NULL_POINT(pstRect);
    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_VFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_VFPOS.bits.video_xfpos = pstRect->u32VX;
    G0_VFPOS.bits.video_yfpos = pstRect->u32VY;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_VFPOS.u32);

    G0_VLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_VLPOS.bits.video_xlpos = pstRect->u32VX + pstRect->u32OWth;
    if (G0_VLPOS.bits.video_xlpos)
    {
        G0_VLPOS.bits.video_xlpos -= 1;
    }

    G0_VLPOS.bits.video_ylpos = pstRect->u32VY + pstRect->u32OHgt;
    if (G0_VLPOS.bits.video_ylpos)
    {
        G0_VLPOS.bits.video_ylpos -= 1;
    }
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_VLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_VLPOS.u32);

    G0_DFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_DFPOS.bits.disp_xfpos = pstRect->u32DXS;
    G0_DFPOS.bits.disp_yfpos = pstRect->u32DYS;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DFPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_DFPOS.u32);

    G0_DLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_DLPOS.bits.disp_xlpos = pstRect->u32DXL;
    if (G0_DLPOS.bits.disp_xlpos)
    {
        G0_DLPOS.bits.disp_xlpos -= 1;
    }

    G0_DLPOS.bits.disp_ylpos = pstRect->u32DYL;
    if (G0_DLPOS.bits.disp_ylpos)
    {
        G0_DLPOS.bits.disp_ylpos -= 1;
    }
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_DLPOS.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_DLPOS.u32);


    GFX_SRC_CROP.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_CROP.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_SRC_CROP.bits.src_crop_x = pstRect->u32SX;
    GFX_SRC_CROP.bits.src_crop_y = pstRect->u32SY;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_CROP.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SRC_CROP.u32);

    GFX_IRESO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_IRESO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_IRESO.bits.ireso_w = pstRect->u32IWth;
    if (GFX_IRESO.bits.ireso_w)
    {
        GFX_IRESO.bits.ireso_w -= 1;
    }

    GFX_IRESO.bits.ireso_h = pstRect->u32IHgt;
    if (GFX_IRESO.bits.ireso_h)
    {
        GFX_IRESO.bits.ireso_h -= 1;
    }
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_IRESO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_IRESO.u32);

    GFX_SRC_RESO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_RESO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_SRC_RESO.bits.src_w = pstRect->u32IWth;
    if (GFX_SRC_RESO.bits.src_w)
    {
        GFX_SRC_RESO.bits.src_w -= 1;
    }

    GFX_SRC_RESO.bits.src_h = pstRect->u32IHgt;
    if (GFX_SRC_RESO.bits.src_h)
    {
        GFX_SRC_RESO.bits.src_h -= 1;
    }
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SRC_RESO.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SRC_RESO.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetRegUp
* description  : CNcomment: 设置图层更新使能寄存器，更新完之后硬件自动清0 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetRegUp(HI_U32 u32Data)
{
    volatile U_G0_UPD G0_UPD;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_UPD.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_UPD.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_UPD.bits.regup = 0x1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_UPD.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_UPD.u32);

    return;
}


/***************************************************************************************
* func        : OPTM_VDP_GFX_SetLayerBkg
* description : CNcomment: 设置图层背景色 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerBkg(HI_U32 u32Data, OPTM_VDP_BKG_S *pstBkg)
{
    volatile U_G0_BK    G0_BK;
    volatile U_G0_ALPHA G0_ALPHA;

    OPTM_HAL_CHECK_NULL_POINT(pstBkg);
    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_BK.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_BK.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    G0_BK.bits.vbk_y  = pstBkg->u32BkgY ;
    G0_BK.bits.vbk_cb = pstBkg->u32BkgU;
    G0_BK.bits.vbk_cr = pstBkg->u32BkgV;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_BK.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), G0_BK.u32);

    G0_ALPHA.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_ALPHA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    G0_ALPHA.bits.vbk_alpha = pstBkg->u32BkgA;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_ALPHA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), G0_ALPHA.u32);

    return;
}


/***************************************************************************************
* func         : OPTM_VDP_GFX_SetLayerGalpha
* description  : CNcomment: 设置图层全局alpha CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerGalpha(HI_U32 u32Data, HI_U32 u32Alpha0)
{
    volatile U_G0_CTRL G0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_CTRL.bits.galpha = u32Alpha0;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_CTRL.u32);

    return;
}

#ifndef HI_BUILD_IN_BOOT
HI_VOID OPTM_VDP_GFX_GetLayerGalpha(HI_U32 u32Data, HI_U8 *pu8Alpha0)
{
    volatile U_G0_CTRL G0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pu8Alpha0);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    *pu8Alpha0 = G0_CTRL.bits.galpha;

    return;
}
#endif


/***************************************************************************************
* func          : OPTM_VDP_GFX_SetPalpha
* description   : CNcomment: 设置pixle alpha值 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetPalpha(HI_U32 u32Data, HI_U32 bAlphaEn,HI_U32 bArange,HI_U32 u32Alpha0,HI_U32 u32Alpha1)
{
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;
    volatile U_GFX_1555_ALPHA GFX_1555_ALPHA;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_1555_ALPHA.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_1555_ALPHA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_1555_ALPHA.bits.alpha_0 = u32Alpha0;
    GFX_1555_ALPHA.bits.alpha_1 = u32Alpha1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_1555_ALPHA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_1555_ALPHA.u32);

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_OUT_CTRL.bits.palpha_en    = bAlphaEn;
    GFX_OUT_CTRL.bits.palpha_range = bArange;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_OUT_CTRL.u32);

    return;
}

#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GFX_GetPalpha(HI_U32 u32Data, HI_U32 *pbAlphaEn,HI_U32 *pbArange,HI_U8 *pu8Alpha0,HI_U8 *pu8Alpha1)
{
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;
    volatile U_GFX_1555_ALPHA GFX_1555_ALPHA;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pbAlphaEn);
    OPTM_HAL_CHECK_NULL_POINT(pu8Alpha1);
    OPTM_HAL_CHECK_NULL_POINT(pu8Alpha0);
    OPTM_HAL_CHECK_NULL_POINT(pbArange);

    GFX_1555_ALPHA.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_1555_ALPHA.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pu8Alpha0 = GFX_1555_ALPHA.bits.alpha_0;
    *pu8Alpha1 = GFX_1555_ALPHA.bits.alpha_1;

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pbArange  = GFX_OUT_CTRL.bits.palpha_range;
    *pbAlphaEn = GFX_OUT_CTRL.bits.palpha_en;

    return;
}


/***************************************************************************************
* func          : OPTM_VDP_GFX_SetLayerNAddr
* description   : CNcomment: 3D右眼显示地址 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetLayerNAddr(HI_U32 u32Data, HI_U32 u32NAddr)
{
    volatile U_GFX_NADDR_L GFX_NADDR_L;
#ifdef CONFIG_HIFB_MMU_SUPPORT
    volatile U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
#endif

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_NADDR_L.u32 = u32NAddr;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_NADDR_L.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_NADDR_L.u32);

#ifdef CONFIG_HIFB_MMU_SUPPORT
    GFX_SMMU_BYPASS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    #ifdef CONFIG_GFX_MMU_SUPPORT
        GFX_SMMU_BYPASS.bits.smmu_bypass_3d = 0;
    #else
        GFX_SMMU_BYPASS.bits.smmu_bypass_3d = 1;
    #endif
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_SMMU_BYPASS.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_SMMU_BYPASS.u32);
#endif

    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetPreMultEnable
* description  : CNcomment: 叠加寄存器预乘使能 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetPreMultEnable(HI_U32 u32Data, HI_U32 bEnable, HI_BOOL bHdr)
{
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;
    volatile U_GP0_CTRL GP0_CTRL;

    HI_UNUSED(bHdr);
    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    GFX_OUT_CTRL.bits.premulti_en = bEnable;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET), GFX_OUT_CTRL.u32);

    if (u32Data > 2)
    {
        return;
    }

    GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32))));
    GP0_CTRL.bits.depremult_en = bEnable;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32))), GP0_CTRL.u32);

    return;
}

HI_VOID OPTM_VDP_GFX_GetPreMultEnable(HI_U32 u32Data, HI_U32 *pbEnable)
{
    volatile U_GFX_OUT_CTRL GFX_OUT_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pbEnable);

    GFX_OUT_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GFX_OUT_CTRL.u32)) + u32Data * CONFIG_HIFB_GFX_OFFSET));
    *pbEnable = GFX_OUT_CTRL.bits.premulti_en;

    return;
}

HI_VOID OPTM_VDP_GFX_ReadRegister(HI_U32 Offset)
{
#ifndef CONFIG_GFX_LOG_SUPPORT
    HI_UNUSED(Offset);
#else
    HI_U32 Index = 0;
    HI_U32 Loop = 16;
    HI_U32 Value = 0x0;
    HI_UNUSED(Value);

    if ((Offset < 0x4) || (Offset >= 0xf000))
    {
        return;
    }

    for (Index = 0; Index < Loop; Index++)
    {
        HI_PRINT("%04x: ",(Offset + Index * 16));
        Value = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset + Index * 16));
        HI_PRINT("%08x ",Value);
        Value = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset + Index * 16 + 0x4));
        HI_PRINT("%08x ",Value);
        Value = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset + Index * 16 + 0x8));
        HI_PRINT("%08x ",Value);
        Value = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset + Index * 16 + 0xc));
        HI_PRINT("%08x ",Value);
        HI_PRINT("\n");
    }
#endif
    return;
}

HI_VOID OPTM_VDP_GFX_WriteRegister(HI_U32 Offset,HI_U32 Value)
{
    HI_U32 PreValue = 0x0;
    HI_U32 CurValue = 0x0;

    if ((Offset < 0x4) || (Offset >= 0xf000))
    {
        return;
    }

    PreValue = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset));

    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset), Value);

    CurValue = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->VOCTRL.u32)) + Offset));

    HI_PRINT("\n%04x: 0x%x - > 0x%x\n",Offset, PreValue, CurValue);

    return;
}


#if !defined(HI_BUILD_IN_BOOT) && defined(CONFIG_HIFB_LOWPOWER_SUPPORT)
HI_VOID HIFB_HAL_SetLowPowerInfo(HI_U32 u32Data, HI_U32 *pLowPowerInfo)
{
    HI_UNUSED(u32Data);
    HI_UNUSED(pLowPowerInfo);
    return;
}

HI_VOID HIFB_HAL_EnableLayerLowPower(HI_U32 u32Data, HI_BOOL EnLowPower)
{
   HI_UNUSED(u32Data);
   HI_UNUSED(EnLowPower);
   return;
}

HI_VOID  HIFB_HAL_EnableGpLowPower(HI_U32 u32Data, HI_BOOL EnLowPower)
{
    HI_UNUSED(u32Data);
    HI_UNUSED(EnLowPower);
    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_GFX_SetUpdMode
* description  : CNcomment: 设置图层更新数据模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GFX_SetUpdMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    volatile U_G0_CTRL G0_CTRL;

    OPTM_HAL_CHECK_LAYER_VALID(u32Data);

    G0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET));
    G0_CTRL.bits.upd_mode = u32Mode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->G0_CTRL.u32)) + u32Data * CONFIG_HIFB_CTL_OFFSET), G0_CTRL.u32);

    return;
}


//-------------------------------------------------------------------
//GP_BEGIN
//-------------------------------------------------------------------
HI_VOID OPTM_VDP_GP_SetParaUpd(HI_U32 u32Data, OPTM_VDP_GP_PARA_E enMode)
{
    volatile U_PARA_UP_VHD PARA_UP_VHD;

    OPTM_HAL_CHECK_GP_VALID(u32Data);

    PARA_UP_VHD.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    PARA_UP_VHD.bits.para_up_vhd_chn16 = 0x1;

    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->PARA_UP_VHD.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), PARA_UP_VHD.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GP_SetReadMode
* description  : CNcomment: 设置GP读取数据模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GP_SetReadMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    volatile U_GP0_CTRL GP0_CTRL;

    OPTM_HAL_CHECK_GP_VALID(u32Data);

    GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_CTRL.bits.read_mode = u32Mode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_CTRL.u32);

    return;
}

HI_VOID OPTM_VDP_GP_SetUpMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    volatile U_GP0_CTRL GP0_CTRL;

    OPTM_HAL_CHECK_GP_VALID(u32Data);

    GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_CTRL.bits.rgup_mode = u32Mode;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_CTRL.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GP_GetRect
* description  : CNcomment: 获取GP大小 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT
HI_VOID  OPTM_VDP_GP_GetRect(HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect)
{
    volatile U_GP0_IRESO GP0_IRESO;
    volatile U_GP0_ZME_VINFO GP0_ZME_VINFO;
    volatile U_GP0_ZME_HINFO GP0_ZME_HINFO;

    OPTM_HAL_CHECK_GP_VALID(u32Data);
    OPTM_HAL_CHECK_NULL_POINT(pstRect);

    GP0_IRESO.u32    = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_IRESO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    pstRect->u32IWth = GP0_IRESO.bits.iw + 1;
    pstRect->u32IHgt = GP0_IRESO.bits.ih + 1;

    GP0_ZME_VINFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_VINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_ZME_HINFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_HINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    pstRect->u32OWth  = GP0_ZME_HINFO.bits.out_width + 1;
    pstRect->u32OHgt  = GP0_ZME_VINFO.bits.out_height + 1;

    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_GP_SetLayerReso
* description  : CNcomment: 设置GP输入输出分辨率 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GP_SetLayerReso(HI_U32 u32Data, OPTM_VDP_DISP_RECT_S *pstRect)
{
    volatile U_GP0_VFPOS GP0_VFPOS;
    volatile U_GP0_VLPOS GP0_VLPOS;
    volatile U_GP0_DFPOS GP0_DFPOS;
    volatile U_GP0_DLPOS GP0_DLPOS;

    volatile U_GP0_IRESO GP0_IRESO;
    volatile U_GP0_ZME_VINFO GP0_ZME_VINFO;
    volatile U_GP0_ZME_HINFO GP0_ZME_HINFO;

    OPTM_HAL_CHECK_NULL_POINT(pstRect);
    OPTM_HAL_CHECK_GP_VALID(u32Data);

    /** video position **/
    GP0_VFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_VFPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_VFPOS.bits.video_xfpos = pstRect->u32VX;
    GP0_VFPOS.bits.video_yfpos = pstRect->u32VY;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_VFPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_VFPOS.u32);

    GP0_VLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_VLPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_VLPOS.bits.video_xlpos = pstRect->u32VX + pstRect->u32OWth - 1;
    GP0_VLPOS.bits.video_ylpos = pstRect->u32VY + pstRect->u32OHgt - 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_VLPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_VLPOS.u32);

    GP0_DFPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_DFPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_DFPOS.bits.disp_xfpos = pstRect->u32DXS;
    GP0_DFPOS.bits.disp_yfpos = pstRect->u32DYS;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_DFPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_DFPOS.u32);

    GP0_DLPOS.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_DLPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_DLPOS.bits.disp_xlpos = pstRect->u32DXL-1;
    GP0_DLPOS.bits.disp_ylpos = pstRect->u32DYL-1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_DLPOS.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_DLPOS.u32);

    GP0_IRESO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_IRESO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_IRESO.bits.iw = pstRect->u32IWth - 1;
    GP0_IRESO.bits.ih = pstRect->u32IHgt - 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_IRESO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_IRESO.u32);

    GP0_ZME_VINFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_VINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_ZME_HINFO.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_HINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_ZME_HINFO.bits.out_width  = pstRect->u32OWth - 1;
    GP0_ZME_VINFO.bits.out_height = pstRect->u32OHgt - 1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_VINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_ZME_VINFO.u32);
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_ZME_HINFO.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_ZME_HINFO.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_GP_SetLayerGalpha
* description  : CNcomment: 设置全局alpha CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GP_SetLayerGalpha(HI_U32 u32Data, HI_U32 u32Alpha)
{
    volatile U_GP0_CTRL GP0_CTRL;

    OPTM_HAL_CHECK_GP_VALID(u32Data);

    GP0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET));
    GP0_CTRL.bits.galpha = u32Alpha;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_CTRL.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_CTRL.u32);

    return;
}

/***************************************************************************************
* func        : OPTM_VDP_GP_SetRegUp
* description : CNcomment: 更新GP寄存器 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_GP_SetRegUp(HI_U32 u32Data)
{
    volatile U_GP0_UPD GP0_UPD;

    OPTM_HAL_CHECK_GP_VALID(u32Data);

    GP0_UPD.bits.regup = 0x1;
    OPTM_VDP_RegWrite((HI_U32*)((unsigned long)(&(pOptmVdpReg->GP0_UPD.u32)) + u32Data * CONFIG_HIFB_GP_OFFSET), GP0_UPD.u32);

    return;
}

/***************************************************************************************
* func         : OPTM_VDP_WBC_SetThreeMd
* description  : CNcomment:  设置回写模式 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetThreeMd(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bMode)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(bMode);
    return;
}


/***************************************************************************************
* func        : OPTM_VDP_WBC_SetEnable
* description : CNcomment: 配置回写使能寄存器 CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetEnable(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 bEnable)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(bEnable);
    return;
}

#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func         : OPTM_VDP_WBC_GetEnable
* description  : CNcomment: 回写是否使能 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_GetEnable(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 *pEnable)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(pEnable);
    return;
}
#endif

/***************************************************************************************
* func         : OPTM_VDP_WBC_SetOutIntf
* description  : CNcomment:WBC输出模式。 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetOutIntf(OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DATA_RMODE_E u32RdMode)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(u32RdMode);
    return;
}


/***************************************************************************************
* func         : OPTM_VDP_WBC_SetRegUp
* description  : CNcomment:更新回写寄存器 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetRegUp(OPTM_VDP_LAYER_WBC_E enLayer)
{
    HI_UNUSED(enLayer);
    return;
}

/***************************************************************************************
* func         : OPTM_VDP_WBC_SetOutFmt
* description  : CNcomment:WBC的输出数据格式。 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetOutFmt(OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_WBC_OFMT_E stIntfFmt)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(stIntfFmt);
    return;
}


/***************************************************************************************
* func         : OPTM_VDP_WBC_SetLayerAddr
* description  : CNcomment: 设置WBC回写地址 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetLayerAddr(OPTM_VDP_LAYER_WBC_E enLayer, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(u32LAddr);
    HI_UNUSED(u32CAddr);
    HI_UNUSED(u32LStr);
    HI_UNUSED(u32CStr);
    return;
}


/***************************************************************************************
* func         : OPTM_VDP_WBC_SetLayerReso
* description  : CNcomment: 设置回写标清图层分辨率 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetLayerReso(OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S *pstRect)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(pstRect);
    return;
}

/***************************************************************************************
* func         : OPTM_VDP_WBC_SetDitherMode
* description  : CNcomment: Dither输出模式选择。 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetDitherMode(OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DITHER_E enDitherMode)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(enDitherMode);
    return;
}

/***************************************************************************************
* func         : OPTM_VDP_WBC_SetCropReso
* description  : CNcomment: 设置回写标清图层裁剪分辨率 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_VDP_WBC_SetCropReso(OPTM_VDP_LAYER_WBC_E enLayer, OPTM_VDP_DISP_RECT_S *pstRect)
{
    HI_UNUSED(enLayer);
    HI_UNUSED(pstRect);
    return;
}

//-------------------------------------------------------------------
//WBC_GFX_BEGIN
//-------------------------------------------------------------------
#ifndef HI_BUILD_IN_BOOT
OPTM_VDP_DISP_MODE_E OPTM_DISP_GetDispMode(HI_U32 u32Data)
{
    volatile U_DHD0_CTRL DHD0_CTRL;

    if ((u32Data >= OPTM_CHN_MAX) || (NULL == pOptmVdpReg))
    {
        HIFB_ERROR("Select Wrong CHANNEL ID\n");
        return VDP_DISP_MODE_2D;
    }

    DHD0_CTRL.u32 = OPTM_VDP_RegRead((HI_U32*)((unsigned long)(&(pOptmVdpReg->DHD0_CTRL.u32)) + u32Data * CONFIG_HIFB_CHN_OFFSET));

    return (OPTM_VDP_DISP_MODE_E)DHD0_CTRL.bits.disp_mode;
}


/***************************************************************************************
* func         : OPTM_VDP_DISP_GetIntSignal
* description  : CNcomment: 获取中断状态 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_U32 OPTM_VDP_DISP_GetIntSignal(HI_U32 u32intmask)
{
    volatile U_VOINTSTA VOINTSTA;

    VOINTSTA.u32 = OPTM_VDP_RegRead((HI_U32*)(unsigned long)(&(pOptmVdpReg->VOINTSTA.u32)));

    return (VOINTSTA.u32 & u32intmask);
}

/***************************************************************************************
* func         : OPTM_ClearIntSignal
* description  : CNcomment: 清除中断状态 CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_VOID OPTM_ClearIntSignal(HI_U32 u32intmask)
{
    OPTM_VDP_RegWrite((HI_U32*)(unsigned long)(&(pOptmVdpReg->VOMSKINTSTA.u32)), u32intmask);
}
#endif
//-------------------------------------------------------------------
//WBC_GFX_END
//-------------------------------------------------------------------
