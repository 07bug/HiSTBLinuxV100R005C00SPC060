#ifndef __VPSS_ASSERT_H__
#define __VPSS_ASSERT_H__

#include "hi_type.h"
#include "hi_reg_common.h"

#define VPSS_ASSERT(ops) {\
        if(!(ops)) \
        {\
            VPSS_FATAL("ASSERT failed at: [%s] \n", #ops);\
        }}


typedef struct tagVPSS_CFG_INFO_S
{
    HI_U32 u32Format      ; //0:420 1: 422 2:444 3:400
    HI_U32 u32Prio        ;
    HI_U32 u32Img2d3dMode ;
    HI_U32 u32Pro         ; //0:interlace 1:progressive
    HI_U32 u32Even        ; //0:odd 1:even
    HI_U32 u32Bfield      ; //0:top 1:bottom
    HI_U32 u32Type        ; //0:sp linear 1:sp tile 2:sp pakage
    HI_U32 u32DcmpMode    ;
    HI_U32 u32PreMultEn   ;
    HI_U32 u32CompValid   ; //A/W Y/R U/G V/B

    HI_U32 u32Wth         ;
    HI_U32 u32Hgt         ;

} VPSS_CFG_INFO_S;
#if 0
typedef enum
{
    VPSS_STT_R_ADDR            = 0,
    VPSS_STT_W_ADDR              ,
    VPSS_CHK_SUM_ADDR            ,
    VPSS_CF_RTUNL_ADDR           ,
    VPSS_OUT0_WTUNL_ADDR         ,
    VPSS_CFY_ADDR                ,
    VPSS_CFC_ADDR                ,
    VPSS_CFCR_ADDR               ,
    VPSS_DI_CFY_ADDR             ,
    VPSS_DI_CFC_ADDR             ,
    VPSS_DI_CFCR_ADDR            ,
    VPSS_DI_P1Y_ADDR             ,
    VPSS_DI_P1C_ADDR             ,
    VPSS_DI_P2Y_ADDR             ,
    VPSS_DI_P2C_ADDR             ,
    VPSS_DI_P3Y_ADDR             ,
    VPSS_DI_P3C_ADDR             ,
    VPSS_DI_P3IY_ADDR            ,
    VPSS_DI_P3IC_ADDR            ,
    VPSS_CC_PR0Y_ADDR            ,
    VPSS_CC_PR0C_ADDR            ,
    VPSS_CC_PR4Y_ADDR            ,
    VPSS_CC_PR4C_ADDR            ,
    VPSS_CC_PR8Y_ADDR            ,
    VPSS_CC_PR8C_ADDR            ,
    VPSS_NR_REFY_ADDR            ,
    VPSS_NR_REFC_ADDR            ,
    VPSS_DI_RSADY_ADDR           ,
    VPSS_DI_RSADC_ADDR           ,
    VPSS_DI_RHISM_ADDR           ,
    VPSS_DI_P1MV_ADDR            ,
    VPSS_DI_P2MV_ADDR            ,
    VPSS_DI_P3MV_ADDR            ,
    VPSS_CC_RCCNT_ADDR           ,
    VPSS_CC_RYCNT_ADDR           ,
    VPSS_NR_RMAD_ADDR            ,
    VPSS_SNR_RMAD_ADDR           ,
    VPSS_NR_CFMV_ADDR            ,
    VPSS_NR_P1RGMV_ADDR          ,
    VPSS_NR_P2RGMV_ADDR          ,
    VPSS_NR_RCNT_ADDR            ,
    VPSS_RG_RPRJH_ADDR           ,
    VPSS_RG_RPRJV_ADDR           ,
    VPSS_RG_P1RGMV_ADDR          ,
    VPSS_RG_P2RGMV_ADDR          ,
    VPSS_OUT0Y_ADDR              ,
    VPSS_OUT0C_ADDR              ,
    VPSS_OUT3Y_ADDR              ,
    VPSS_NR_RFRY_ADDR            ,
    VPSS_NR_RFRC_ADDR            ,
    VPSS_NR_RFRHY_ADDR           ,
    VPSS_NR_RFRHVY_ADDR          ,
    VPSS_CC_RFRY_ADDR            ,
    VPSS_CC_RFRC_ADDR            ,
    VPSS_DI_RFRY_ADDR            ,
    VPSS_DI_RFRC_ADDR            ,
    VPSS_NR_WMAD_ADDR            ,
    VPSS_NR_WCNT_ADDR            ,
    VPSS_CC_WCCNT_ADDR           ,
    VPSS_CC_WYCNT_ADDR           ,
    VPSS_DI_WSADY_ADDR           ,
    VPSS_DI_WSADC_ADDR           ,
    VPSS_DI_WHISM_ADDR           ,
    VPSS_RG_WPRJH_ADDR           ,
    VPSS_RG_WPRJV_ADDR           ,
    VPSS_RG_CFRGMV_ADDR          ,
    VPSS_ME_CFY_ADDR             ,
    VPSS_ME_REFY_ADDR            ,
    VPSS_ME_P1MV_ADDR            ,
    VPSS_ME_PRMV_ADDR            ,
    VPSS_ME_P1GMV_ADDR           ,
    VPSS_ME_PRGMV_ADDR           ,
    VPSS_ME_P1RGMV_ADDR          ,
    VPSS_ME_P2RGMV_ADDR          ,
    VPSS_ME_CFMV_ADDR            ,
    VPSS_ME_CFGMV_ADDR           ,
    VPSS_ME_STT_W_ADDR           ,
    LAST_CHN_ADDR
} CHN_ADDR_E;
#endif

typedef enum
{
    VPSS_CF_SIZE     = 0  ,
    VPSS_DI_RSADY_SIZE    ,
    VPSS_DI_RSADC_SIZE    ,
    VPSS_DI_RHISM_SIZE    ,
    VPSS_DI_P1MV_SIZE     ,
    VPSS_NR_RMAD_SIZE     ,
    VPSS_NR_CFMV_SIZE     ,
    VPSS_NR_P1RGMV_SIZE   ,
    VPSS_NR_RCNT_SIZE     ,
    VPSS_RG_RPRJH_SIZE    ,
    VPSS_RG_RPRJV_SIZE    ,
    VPSS_RG_P1RGMV_SIZE   ,
    VPSS_ME_CF_SIZE       ,
    VPSS_ME_REF_SIZE      ,
    VPSS_ME_P1MV_SIZE     ,
    VPSS_ME_PRMV_SIZE     ,
    VPSS_ME_P1GMV_SIZE    ,
    VPSS_ME_PRGMV_SIZE    ,
    VPSS_ME_P1RGMV_SIZE   ,
    VPSS_ME_P2RGMV_SIZE   ,
    LAST_CHN_SIZE
} CHN_SIZE_E;

HI_U32 VPSS_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable);
HI_U32 VPSS_GetCfgInfo(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo);
HI_U32 VPSS_SYS_APB_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo);
HI_U32 VPSS_SYS_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo);
HI_U32 VPSS_MAC_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo);
HI_U32 VPSS_IP_ConfigCheck(S_VPSS_REGS_TYPE *pReg, HI_BOOL bEnable, VPSS_CFG_INFO_S *pstCfgInfo);

#endif


