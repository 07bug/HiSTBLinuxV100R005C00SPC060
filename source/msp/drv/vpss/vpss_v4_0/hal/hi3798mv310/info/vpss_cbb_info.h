#ifndef __VPSS_CBB_INFO_H__
#define __VPSS_CBB_INFO_H__

#include "vpss_cbb_common.h"
#include "vpss_cbb_frame.h"

#if 0
typedef struct
{
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
    HI_U32 u32VirAddr;
} CBB_INFO_ADDR;

typedef struct
{
    CBB_INFO_ADDR stPrjH[3];
    CBB_INFO_ADDR stPrjV[3];
    HI_U32 u32Stride;
    HI_BOOL bMMU;
    HI_BOOL bSecure;
} CBB_INFO_PRJ;
#endif

typedef struct
{
    HI_U32 u32WPhyAddr;
    HI_U8 *pu8WVirAddr;
    HI_U32 u32RPhyAddr;
    HI_U8 *pu8RVirAddr;
    HI_U32 u32ByteSize;
    HI_U32 u32Stride;
    HI_BOOL bSmmu_R;            //底层根据mmu标志 设置通道的mmu bypass属性
    HI_BOOL bSmmu_W;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_S;

typedef struct
{
    //HI_U32        u32Tnr_cfg_addr;
    //HI_U32        u32Tnr_clut_addr;
    CBB_INFO_S stBaseInfo;
} CBB_INFO_TNR_S;

typedef struct
{
    //HI_U32        u32Snr_cfg_addr;
    CBB_INFO_S stBaseInfo;
} CBB_INFO_SNR_S;


typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur读地址
    HI_U32 u32Nx2WriteAddr; //Nx2写地址
    HI_U8 *pu8CurReadAddr;  //Cur?恋?址
    HI_U8 *pu8Nx2WriteAddr; //Nx2写??址
    HI_U32 u32Stride;       //运动指数行间距
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_PRJV_S;

typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur读地址
    HI_U32 u32Nx2WriteAddr; //Nx2写地址
    HI_U8 *pu8CurReadAddr;  //Cur?恋?址
    HI_U8 *pu8Nx2WriteAddr; //Nx2写??址
    HI_U32 u32Stride;       //运动指数行间距
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_PRJH_S;

typedef struct
{
    HI_U32 u32ReadAddr;
    HI_U32 u32WriteAddr;
    HI_U8 *pu8CurReadAddr;
    HI_U8 *pu8Nx2WriteAddr;
    HI_U32 u32Width;
    HI_U32 u32Hight;
    HI_U32 u32Stride;
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_w;
    HI_BOOL bSmmu_r;
    HI_BOOL bSecure;
    HI_BOOL bEn;
} CBB_INFO_DI_S;
typedef struct
{
    HI_U32 u32RefReadAddr;  //Ref读地址
    HI_U32 u32CurReadAddr;  //Cur读地址
    HI_U32 u32Nx1WriteAddr;      //Nx1写??址
    HI_U8 *pu8CurReadAddr;  //Cur?恋?址
    HI_U8 *pu8RefReadAddr;  //Nx1?恋?址
    HI_U8 *pu8Nx1WriteAddr; //Nx2写??址
    HI_U32 u32Stride;       //运动指数行间距
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Ref;
    HI_BOOL bSmmu_Nx1;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_BLKMV_S;

typedef struct
{
    HI_U32 u32CurReadAddr;  //Cur读地址
    HI_U32 u32Nx1ReadAddr;  //Nx1读地址
    HI_U32 u32Nx2WriteAddr; //Nx2写地址
    HI_U8 *pu8CurReadAddr;  //Cur读地址
    HI_U8 *pu8Nx1ReadAddr;  //Nx1读地址
    HI_U8 *pu8Nx2WriteAddr; //Nx2写地址
    HI_U32 u32Stride;       //运动指数行间距
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Nx2;
    HI_BOOL bSmmu_Nx1;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_RGMV_S;

typedef struct
{
    HI_U32 u32CurWriteAddr;  //Cur写地址
    HI_U32 u32RefReadAddr;  //ref读地址
    HI_U8 *pu8CurWriteAddr;  //Cur写地址
    HI_U8 *pu8RefReadAddr;  //Ref读地址
    HI_U32 u32Stride;       //运动指数行间距
    HI_U32 u32ByteSize;
    HI_BOOL bSmmu_Cur;
    HI_BOOL bSmmu_Ref;
    HI_BOOL bSecure;
    HI_U32 u32Wth;
    HI_U32 u32Hgt;
    HI_BOOL bEn;
} CBB_INFO_BLKMT_S;
#if 0
typedef struct
{
    HI_U32 u32CurAddr;  //Cur?恋?址
    HI_U32 u32Nx1Addr;  //Nx1?恋?址
    HI_U32 u32Nx2Addr; //Nx2写??址
    HI_U32 u32Stride;       //?硕?指???屑???
    HI_BOOL bSmmu;
    HI_BOOL bSecure;
} CBB_INFO_TNRRGMV_S;
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern HI_VOID VPSS_InfoCfg_Blkmv(CBB_INFO_BLKMV_S *pstInfoBlkmvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Blkmt(CBB_INFO_BLKMT_S *pstInfoBlkmtCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Dei_ST(CBB_INFO_S *pstInfoDeiCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Prjh(CBB_INFO_PRJH_S *pstInfoPrjhCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Di(CBB_INFO_DI_S *pstInfoDiCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Prjv(CBB_INFO_PRJV_S *pstInfoPrjvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Rgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_TnrRgmv(CBB_INFO_RGMV_S *pstInfoRgmvCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Snr_Mad(CBB_INFO_S *pstInfoSnrCfg, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_SttInfo(CBB_INFO_S *pstInfoStt, CBB_REG_ADDR_S stRegAddr);
extern HI_VOID VPSS_InfoCfg_Tnr_Mad(CBB_INFO_S *pstInfoTnrCfg, CBB_REG_ADDR_S stRegAddr);
//extern HI_VOID VPSS_InfoGet_All(S_VPSS_STT_REGS_TYPE *pstSttReg, CBB_INFO_S *pstInfoStt);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
