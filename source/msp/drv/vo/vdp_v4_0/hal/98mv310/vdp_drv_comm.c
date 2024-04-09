//**********************************************************************
// File Name   : vdp_drv_comm.cpp
// Data        : 2012/10/17
// Version     : v1.0
// Abstract    : header of vdp define
//
// Modification history
//----------------------------------------------------------------------
// Version       Data(yyyy/mm/dd)      name
// Description
//
//
//
//
//
//**********************************************************************

#include "vdp_drv_comm.h"
#include "outer_depend.h"

VDP_COEF_ADDR_S gstVdpCoefBufAddr;
VDP_ADDR_CFG_S  gstVdpAddrCfg;
HI_U32 VDP_FhdShpVirAddr;
HI_U32 VDP_MrgVirAddr;
HI_U32 VDP_MrgPhyAddr;

#ifndef __DISP_PLATFORM_BOOT__
#include "hi_drv_mmz.h"
#endif
extern  HI_S32 HI_DRV_PDM_AllocReserveMem(const HI_CHAR *BufName, HI_U32 u32Len, HI_U32 *pu32PhyAddr);

//----------------------------------------------------------------------
// memory/address managerment
//----------------------------------------------------------------------
HI_S32 VDP_DRV_AllocateMem(HI_U32 u32Size, VDP_MMZ_BUFFER_S* stVdpMmzBuffer)
{
#ifdef __DISP_PLATFORM_BOOT__
    HI_S32 nRet;
    nRet = HI_DRV_PDM_AllocReserveMem(VDP_DDR_NAME_UBOOT, u32Size, &stVdpMmzBuffer->u32StartPhyAddr);
    if (nRet != 0)
    {
         VDP_PRINT("VDP_DDR_CFG  failed\n");
         return HI_FAILURE;
    }

    stVdpMmzBuffer->pu8StartVirAddr = HI_NULL;
    stVdpMmzBuffer->u32Size         = u32Size;
#else
    HI_S32 nRet;
    nRet = HI_DRV_MMZ_AllocAndMap("VDP_DDR_CFG", HI_NULL, u32Size, 0, (MMZ_BUFFER_S *)stVdpMmzBuffer);
    if (nRet != 0)
    {
        VDP_PRINT("VDP_DDR_CFG  failed\n");
        return nRet;
    }
#endif
    return HI_SUCCESS;

}

HI_S32 VDP_DRV_DeleteMem(VDP_MMZ_BUFFER_S* stVdpMmzBuffer)
{
#ifdef __DISP_PLATFORM_BOOT__
     /*todo nothing.*/
#else
    HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)stVdpMmzBuffer);
#endif
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_AllocateCfgMem(HI_U32 u32Size, VDP_MMZ_BUFFER_S* pstVdpCfgBuffer)
{
#ifdef __DISP_PLATFORM_BOOT__
    HI_S32 nRet;
    nRet = HI_DRV_PDM_AllocReserveMem(VDP_DDR_NAME_UBOOT, u32Size, &pstVdpCfgBuffer->u32StartPhyAddr);
    if (nRet != 0)
    {
         VDP_PRINT("VDP_DDR_CFG  failed\n");
         return HI_FAILURE;
    }

    pstVdpCfgBuffer->pu8StartVirAddr = HI_NULL;
    pstVdpCfgBuffer->u32Size         = u32Size;
    VDP_MrgPhyAddr = pstVdpCfgBuffer->u32StartPhyAddr;

#else
    HI_S32 nRet;
    nRet = HI_DRV_MMZ_AllocAndMap("VDP_MRG_CFG", HI_NULL, u32Size, 0, (MMZ_BUFFER_S *)pstVdpCfgBuffer);

    if (nRet != 0)
    {
        VDP_PRINT("VDP_MRG_CFG  failed\n");
        return nRet;
    }

    VDP_MrgVirAddr = (HI_U32)(pstVdpCfgBuffer->pu8StartVirAddr);
    VDP_MrgPhyAddr = pstVdpCfgBuffer->u32StartPhyAddr;
#endif
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_DeleteCfgMem(VDP_MMZ_BUFFER_S* stVdpCfgBuffer)
{
#ifdef __DISP_PLATFORM_BOOT__
     /*todo nothing.*/
#else
    HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)stVdpCfgBuffer);
#endif
    return HI_SUCCESS;
}



//----------------------------------------------------------------------
// memory/address distribute
//----------------------------------------------------------------------
HI_S32 VDP_DRV_CoefBufAddrDistribute(VDP_COEF_ADDR_S* stVdpCoefBufAddr)
{
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEH]  = stVdpCoefBufAddr->stBufBaseAddr.pu8StartVirAddr;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEV]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEH] + COEF_SIZE_ZMEH;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2H]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZMEV] + COEF_SIZE_ZMEV;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2V]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2H] + COEF_SIZE_ZME2H;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2V] + COEF_SIZE_ZME2V;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2_TMP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP] + COEF_SIZE_ZME_TMP;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEH]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_ZME2_TMP] + COEF_SIZE_ZME_TMP;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEV]  = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEH] + COEF_SIZE_GPZMEH;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZME_TMP] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEV] + COEF_SIZE_GPZMEV;

    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_D  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZME_TMP] + COEF_SIZE_GPZME_TMP;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_S  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_D  ] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_TMP  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_S  ] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_GMM  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_TMP] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_SHARP  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_GMM] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GP0ZME  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_SHARP  ] + COEF_SIZE_SHARP;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_HZME  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GP0ZME] + COEF_SIZE_GP0ZME;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_VZME  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_HZME] + COEF_SIZE_WBC_HZME;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GFXCLUT  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_WBC_VZME] + COEF_SIZE_WBC_VZME;
    stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GFXCLUT2  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GFXCLUT] + COEF_SIZE_GFXCLUT;
    //stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MRGCFG  ] = stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GFXCLUT2] + COEF_SIZE_GFXCLUT2;


    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH]  = stVdpCoefBufAddr->stBufBaseAddr.u32StartPhyAddr ;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH] + COEF_SIZE_ZMEH;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV] + COEF_SIZE_ZMEV;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H] + COEF_SIZE_ZME2H;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_TMP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V] + COEF_SIZE_ZME2V;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2_TMP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME_TMP] + COEF_SIZE_ZME_TMP;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEH]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2_TMP] + COEF_SIZE_ZME_TMP;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEV]  = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEH] + COEF_SIZE_GPZMEH;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZME_TMP] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEV] + COEF_SIZE_GPZMEV;

    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_D  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZME_TMP] + COEF_SIZE_GPZME_TMP;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_S  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_D  ] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_TMP  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_S  ] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_GMM  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_TMP] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_SHARP  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_GMM] + COEF_SIZE_HIHDR;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GP0ZME  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_SHARP  ] + COEF_SIZE_SHARP;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_HZME  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GP0ZME] + COEF_SIZE_GP0ZME;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_VZME  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_HZME  ] + COEF_SIZE_WBC_HZME;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_VZME] + COEF_SIZE_WBC_VZME;
    stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT2  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT] + COEF_SIZE_GFXCLUT;
    //stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MRGCFG  ] = stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT2] + COEF_SIZE_GFXCLUT2;

#if 0
    XDP_PRINT("[%s]ps16ZMEHCoefVir = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEH]);
    XDP_PRINT("[%s]ps16ZMEVCoefVir = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GPZMEV]);
    XDP_PRINT("[%s]u32ZMEHCoefPhy = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEH]);
    XDP_PRINT("[%s]u32ZMEVCoefPhy = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GPZMEV]);
    XDP_PRINT("[%s]VDP_FhdShpVirAddr = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_SHARP]);
    XDP_PRINT("[%s]Vir VDP_COEF_BUF_GP0ZME = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_GP0ZME]);
    XDP_PRINT("[%s]Phy VDP_COEF_BUF_GP0ZME = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GP0ZME]);
    XDP_PRINT("[%s]VDP_FhdShpPhyAddr = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_SHARP]);
    XDP_PRINT("[%s]Vir VDP_COEF_BUF_HIHDR_V_D = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_D]);
    XDP_PRINT("[%s]Phy VDP_COEF_BUF_HIHDR_V_D = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_D]);
    XDP_PRINT("[%s]Vir VDP_COEF_BUF_HIHDR_V_S = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_S]);
    XDP_PRINT("[%s]Phy VDP_COEF_BUF_HIHDR_V_S = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_S]);
    XDP_PRINT("[%s]VDP_MrgVirAddr = 0x%x\n",__FUNCTION__,(HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MRGCFG]);
    XDP_PRINT("[%s]VDP_MrgPhyAddr = 0x%x\n",__FUNCTION__,stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MRGCFG]);
#endif
	VDP_FhdShpVirAddr = (HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_SHARP ];
    //VDP_MrgVirAddr = (HI_U32)stVdpCoefBufAddr->pu8CoefVirAddr[VDP_COEF_BUF_MRGCFG  ];

    VDP_PARA_SetParaAddrVhdChn00( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH]);
    VDP_PARA_SetParaAddrVhdChn01( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV]);
    VDP_PARA_SetParaAddrVhdChn02( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEH] + 0x100);
    VDP_PARA_SetParaAddrVhdChn03( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZMEV] + 0x100);
    /*VDP_PARA_SetParaAddrVhdChn04( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_SHARP  ]);*/
    VDP_PARA_SetParaAddrVhdChn05( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H]);
    VDP_PARA_SetParaAddrVhdChn06( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V]);
    VDP_PARA_SetParaAddrVhdChn07( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2H] + 0x100);
    VDP_PARA_SetParaAddrVhdChn08( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_ZME2V] + 0x100);
    VDP_PARA_SetParaAddrVhdChn09( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_D  ]);
    VDP_PARA_SetParaAddrVhdChn10( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_V_S  ]);
    VDP_PARA_SetParaAddrVhdChn11( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_HZME  ]);
    VDP_PARA_SetParaAddrVhdChn12( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_WBC_VZME  ]);
    VDP_PARA_SetParaAddrVhdChn14( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_TMP  ]);
    VDP_PARA_SetParaAddrVhdChn15( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_GMM  ]);
    //VDP_PARA_SetParaAddrVhdChn16( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GP0ZME  ]);
    VDP_PARA_SetParaAddrVhdChn17( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT  ]);
    VDP_PARA_SetParaAddrVhdChn18( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_GFXCLUT2 ]);
    //VDP_PARA_SetParaAddrVhdChn19( stVdpCoefBufAddr->u32CoefPhyAddr[VDP_COEF_BUF_MRGCFG  ]);
    VDP_PARA_SetParaAddrVhdChn19( VDP_MrgPhyAddr);

    return HI_SUCCESS;
}






HI_S32 VDP_DRV_IoRemap(HI_U32 u32Phy, HI_U32 u32Size,HI_U32 **pu32VirtualAddr)
{

#ifndef __DISP_PLATFORM_BOOT__
    *pu32VirtualAddr = ioremap_nocache(u32Phy, u32Size);
    if (HI_NULL == *pu32VirtualAddr)
    {
        return HI_FAILURE;
    }
#else
     /*todo nothing.*/
#endif
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_IoUnmap(HI_U32 **pu32VirtualAddr)
{
#ifndef __DISP_PLATFORM_BOOT__
    (HI_VOID)iounmap(*pu32VirtualAddr);
    *pu32VirtualAddr = HI_NULL;
#else
     /*todo nothing.*/
#endif

    return HI_SUCCESS;
}


