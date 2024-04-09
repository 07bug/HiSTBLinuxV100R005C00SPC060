#ifndef __VPSS_STTINF_H__
#define __VPSS_STTINF_H__
#include "vpss_common.h"
#include "hi_drv_vpss.h"
#include "vpss_osal.h"

/* DIE ST */
#define VPSS_DIE_MAX_NODE 3
typedef struct hiVPSS_DIE_DATA_S
{
    HI_U32 u32PhyAddr;
    LIST node;
} VPSS_DIE_DATA_S;

typedef struct hiVPSS_DIESTINFO_S
{
    HI_BOOL bInit;                     //��ʼ����ʶ
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32Stride;
    HI_U32 u32DieInfoSize;
    VPSS_DIE_DATA_S stDataList[VPSS_DIE_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif

    SMMU_BUFFER_S stTEEBuf;
    LIST *pstFirstRef;
} VPSS_DIESTINFO_S;

typedef struct hiVPSS_DIESTCFG_S
{
    HI_U32 u32CurAddr;
    HI_U32 u32PreAddr;
    HI_U32 u32PPreAddr;
    HI_U32 u32Stride;
} VPSS_DIESTCFG_S;

HI_S32 VPSS_STTINFO_DieInit(VPSS_DIESTINFO_S *pstDieStInfo,
                            HI_U32 u32Width,
                            HI_U32 u32Heigth,
                            HI_BOOL bSecure,
                            VPSS_MCDI_SPLIT_INFO_S *pstSplitInfo);
HI_S32 VPSS_STTINFO_DieDeInit(VPSS_DIESTINFO_S *pstDieStInfo);
HI_S32 VPSS_STTINFO_DieGetInfo(VPSS_DIESTINFO_S *pstDieStInfo, VPSS_DIESTCFG_S *pstDieStCfg);
HI_S32 VPSS_STTINFO_DieComplete(VPSS_DIESTINFO_S *pstDieStInfo);
HI_S32 VPSS_STTINFO_DieReset(VPSS_DIESTINFO_S *pstDieStInfo);


/* NR MAD */

#define VPSS_NR_MAX_NODE 4
typedef struct hiVPSS_NR_DATA_S
{
    HI_U32 u32PhyAddr;
    LIST node;
} VPSS_NR_DATA_S;

typedef enum hiVPSS_NR_MODE_E
{
    NR_MODE_FRAME  = 0,
    NR_MODE_5FIELD,
    NR_MODE_3FIELD,
    NR_MODE_BUTT
} VPSS_NR_MODE_E;


typedef struct hiVPSS_NR_ATTR_S
{
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_BOOL bSecure;
    HI_BOOL bProgressive;
    VPSS_NR_MODE_E enMode;
    HI_BOOL bSplitEnable;
    VPSS_MCDI_SPLIT_MODE_E enSplitMode;
} VPSS_NR_ATTR_S;

typedef struct hiVPSS_NRMADINFO_S
{
    HI_BOOL bInit;                     //��ʼ����ʶ
    HI_U32 u32Cnt;
    VPSS_NR_ATTR_S stAttr;
    HI_U32 u32NRMADSize;
    HI_U32 u32madstride;
    VPSS_NR_DATA_S stDataList[VPSS_NR_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif

    SMMU_BUFFER_S stTEEBuf;

    LIST *pstFirstRef;
} VPSS_NRMADINFO_S;

typedef struct hiVPSS_NRMADCFG_S
{
    HI_U32 u32Tnrmad_raddr;
    HI_U32 u32Tnrmad_waddr;
    HI_U32 u32Snrmad_raddr;
    HI_U32 u32madstride;
} VPSS_NRMADCFG_S;

HI_S32 VPSS_STTINFO_NrInit(VPSS_NRMADINFO_S *pstNrMadInfo, VPSS_NR_ATTR_S *pstAttr);
HI_S32 VPSS_STTINFO_NrDeInit(VPSS_NRMADINFO_S *pstNrMadInfo);
HI_S32 VPSS_STTINFO_NrGetInfo(VPSS_NRMADINFO_S *pstNrMadInfo,
                              VPSS_NRMADCFG_S *pstNrMadCfg);
HI_S32 VPSS_STTINFO_NrComplete(VPSS_NRMADINFO_S *pstNrMadInfo);
HI_S32 VPSS_STTINFO_NrReset(VPSS_NRMADINFO_S *pstNrMadInfo);

typedef struct hiVPSS_STTWBC_S
{
    HI_BOOL bInit;                     //��ʼ����ʶ
    HI_U32 u32Cnt;
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT_STT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif
} VPSS_STTWBC_S;

/* STT WBC */
#ifdef VPSS_SUPPORT_SPLIT_MCDI
#define VPSS_STTWBC_SIZE (32*1024)*5
#else
#define VPSS_STTWBC_SIZE (32*1024)
#endif
HI_S32 VPSS_STTINFO_SttWbcInit(VPSS_STTWBC_S *psttWbc);
HI_S32 VPSS_STTINFO_SttWbcDeInit(VPSS_STTWBC_S *psttWbc);
HI_S32 VPSS_STTINFO_SttWbcGetAddr(VPSS_STTWBC_S *psttWbc,
                                  HI_U32 *pu32stt_w_phy_addr,
                                  HI_U8 **ppu8stt_w_vir_addr);

HI_S32 VPSS_STTINFO_SttWbcComplete(VPSS_STTWBC_S *psttWbc);
HI_S32 VPSS_STTINFO_SttWbcReset(VPSS_STTWBC_S *psttWbc);

#endif
