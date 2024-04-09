#ifndef __VPSS_STT_MCDEI_H__
#define __VPSS_STT_MCDEI_H__

#include "hi_drv_mmz.h"
#include "vpss_common.h"
#include "hi_drv_vpss.h"
#include <linux/list.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define VPSS_RGME_MAX_NODE  3
typedef struct hiVPSS_MC_ATTR_S
{
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_BOOL bSecure;
    HI_BOOL bProgressive;
    VPSS_MCDI_SPLIT_MODE_E enSplitMode;
    HI_BOOL bSplitEnable;
} VPSS_MC_ATTR_S;

typedef struct hiVPSS_MC_DATA_S
{
    HI_U32 u32PhyAddr;
    HI_U8  *pu8VirAddr;
    LIST node;
} VPSS_MC_DATA_S;

typedef struct hiVPSS_ST_RGME_CFG_S
{
    HI_U32 u32CurReadAddr;  //Cur����ַ
    HI_U32 u32Nx1ReadAddr;  //Nx1����ַ
    HI_U32 u32Nx2WriteAddr;  //Nx2д��ַ
    HI_U8 *pu8CurReadAddr;  //Cur����ַ
    HI_U8 *pu8Nx1ReadAddr;  //Nx1����ַ
    HI_U8 *pu8Nx2WriteAddr;  //Nx2д��ַ
    HI_U32 u32Stride;        //�˶�ָ���м��
} VPSS_ST_RGME_CFG_S;

typedef struct hiVPSS_ST_RGME_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    HI_BOOL bProgressive;
    VPSS_MC_DATA_S stDataList[VPSS_RGME_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif

    SMMU_BUFFER_S stTEEBuf;

    LIST *pstFirstRef;
} VPSS_ST_RGME_S;

HI_S32 VPSS_ST_RGME_Init(VPSS_ST_RGME_S *pstStRgme, VPSS_MC_ATTR_S *pstAttr);
HI_S32 VPSS_ST_RGME_DeInit(VPSS_ST_RGME_S *pstStRgme);

//��ȡRGME�˶���Ϣ
HI_S32 VPSS_ST_RGME_GetCfg(VPSS_ST_RGME_S *pstStRgme,
                           VPSS_ST_RGME_CFG_S *pstStRgmeCfg);

//RGME�˶���Ϣ������ת
HI_S32 VPSS_ST_RGME_Complete(VPSS_ST_RGME_S *pstStRgme);

//RGME�˶���Ϣ����reset
HI_S32 VPSS_ST_RGME_Reset(VPSS_ST_RGME_S *pstStRgme);

///////////////////////////////////////////////////////////////////
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
#define VPSS_BLKMV_MAX_NODE 3
#else
#define VPSS_BLKMV_MAX_NODE 4
#endif

typedef struct hiVPSS_ST_BLKMV_CFG_S
{
    HI_U32 u32RefReadAddr;  //Ref����ַ
    HI_U32 u32CurReadAddr;  //Cur����ַ
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) || defined(CHIP_TYPE_hi3798mv310)
    HI_U32 u32Nx1WriteAddr;  //Nx1����ַ
#else
    HI_U32 u32Nx1ReadAddr;  //Nx1����ַ
    HI_U32 u32Nx2WriteAddr;  //Nx2д��ַ
#endif
    HI_U32 u32Stride;              //�˶�ָ���м��
} VPSS_ST_BLKMV_CFG_S;


typedef struct hiVPSS_ST_BLKMV_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    VPSS_MC_DATA_S stDataList[VPSS_BLKMV_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif


    SMMU_BUFFER_S stTEEBuf;

    LIST *pstFirstRef;
} VPSS_ST_BLKMV_S;

HI_S32 VPSS_ST_BLKMV_Init(VPSS_ST_BLKMV_S *pstStBlkmv, VPSS_MC_ATTR_S *pstAttr);

HI_S32 VPSS_ST_BLKMV_DeInit(VPSS_ST_BLKMV_S *pstStBlkmv);

HI_S32 VPSS_ST_BLKMV_GetCfg(VPSS_ST_BLKMV_S *pstStBlkmv,
                            VPSS_ST_BLKMV_CFG_S *pstStBlkmvCfg);

//BLKMV�˶���Ϣ������ת
HI_S32 VPSS_ST_BLKMV_Complete(VPSS_ST_BLKMV_S *pstStBlkmv);

//BLKMV�˶���Ϣ����reset
HI_S32 VPSS_ST_BLKMV_Reset(VPSS_ST_BLKMV_S *pstStBlkmv);

#if defined(VPSS_SUPPORT_BLKMT)

#define VPSS_BLKMT_MAX_NODE 2


typedef struct hiVPSS_ST_BLKMT_CFG_S
{
    HI_U32 u32RefReadAddr;   //Ref����ַ
    HI_U32 u32CurWriteAddr;  //Curд��ַ
    HI_U32 u32Stride;        //�˶�ָ���м��
} VPSS_ST_BLKMT_CFG_S;


typedef struct hiVPSS_ST_BLKMT_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    VPSS_MC_DATA_S stDataList[VPSS_BLKMT_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif


    SMMU_BUFFER_S stTEEBuf;

    LIST *pstFirstRef;
} VPSS_ST_BLKMT_S;

HI_S32 VPSS_ST_BLKMT_Init(VPSS_ST_BLKMT_S *pstStBLKMT, VPSS_MC_ATTR_S *pstAttr);

HI_S32 VPSS_ST_BLKMT_DeInit(VPSS_ST_BLKMT_S *pstStBLKMT);

HI_S32 VPSS_ST_BLKMT_GetCfg(VPSS_ST_BLKMT_S *pstStBLKMT,
                            VPSS_ST_BLKMT_CFG_S *pstStBLKMTCfg);

//BLKMT�˶���Ϣ������ת
HI_S32 VPSS_ST_BLKMT_Complete(VPSS_ST_BLKMT_S *pstStBLKMT);

//BLKMT�˶���Ϣ����reset
HI_S32 VPSS_ST_BLKMT_Reset(VPSS_ST_BLKMT_S *pstStBLKMT);
#endif //#if defined(VPSS_SUPPORT_BLKMT)


#ifdef VPSS_SUPPORT_DICNT
#define VPSS_DICNT_MAX_NODE 2

typedef struct hiVPSS_ST_DICNT_CFG_S
{
    HI_U32 u32ReadAddr;   //Ref����ַ
    HI_U32 u32WriteAddr;  //Curд��ַ
    HI_U32 u32Stride;        //�˶�ָ���м��
    HI_U32 u32Width;
    HI_U32 u32Height;
} VPSS_ST_DICNT_CFG_S;


typedef struct hiVPSS_ST_DICNT_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    VPSS_MC_DATA_S stDataList[VPSS_DICNT_MAX_NODE];
    HI_U32 u32InstanceId;
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif
    SMMU_BUFFER_S stTEEBuf;
    LIST *pstFirstRef;
} VPSS_ST_DICNT_S;

HI_S32 VPSS_ST_DICNT_Init(VPSS_ST_DICNT_S *pstStDICNT, VPSS_MC_ATTR_S *pstAttr);

HI_S32 VPSS_ST_DICNT_DeInit(VPSS_ST_DICNT_S *pstStDICNT);

HI_S32 VPSS_ST_DICNT_GetCfg(VPSS_ST_DICNT_S *pstStDICNT,
                            VPSS_ST_DICNT_CFG_S *pstStDICNTCfg);

//DICNT�˶���Ϣ������ת
HI_S32 VPSS_ST_DICNT_Complete(VPSS_ST_DICNT_S *pstStDICNT);

//DICNT�˶���Ϣ����reset
HI_S32 VPSS_ST_DICNT_Reset(VPSS_ST_DICNT_S *pstStDICNT);
#endif //#if defined(VPSS_SUPPORT_DICNT)


///////////////////////////////////////////////////////////////////

#define VPSS_PRJH_MAX_NODE 3

typedef struct hiVPSS_ST_PRJH_CFG_S
{
    HI_U32 u32CurReadAddr;  //Cur����ַ
    HI_U32 u32Nx2WriteAddr;  //Nx2д��ַ
    HI_U32 u32Stride;              //�˶�ָ���м��
} VPSS_ST_PRJH_CFG_S;


typedef struct hiVPSS_ST_PRJH_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    HI_U32 u32InstanceId;
    VPSS_MC_DATA_S stDataList[VPSS_PRJH_MAX_NODE];
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif


    SMMU_BUFFER_S stTEEBuf;


    LIST *pstFirstRef;
} VPSS_ST_PRJH_S;

HI_S32 VPSS_ST_PRJH_Init(VPSS_ST_PRJH_S *pstStPrjh, VPSS_MC_ATTR_S *pstAttr);
HI_S32 VPSS_ST_PRJH_DeInit(VPSS_ST_PRJH_S *pstStPrjh);

//��ȡPRJH�˶���Ϣ
HI_S32 VPSS_ST_PRJH_GetCfg(VPSS_ST_PRJH_S *pstStPrjh,
                           VPSS_ST_PRJH_CFG_S *pstStPrjhCfg);

//PRJH�˶���Ϣ������ת
HI_S32 VPSS_ST_PRJH_Complete(VPSS_ST_PRJH_S *pstStPrjh);

//PRJH�˶���Ϣ����reset
HI_S32 VPSS_ST_PRJH_Reset(VPSS_ST_PRJH_S *pstStPrjh);


///////////////////////////////////////////////////////////////////

#define VPSS_PRJV_MAX_NODE 3

typedef struct hiVPSS_ST_PRJV_CFG_S
{
    HI_U32 u32CurReadAddr;  //Cur����ַ
    HI_U32 u32Nx2WriteAddr;  //Nx2д��ַ
    HI_U32 u32Stride;              //�˶�ָ���м��
} VPSS_ST_PRJV_CFG_S;


typedef struct hiVPSS_ST_PRJV_S
{
    HI_BOOL bInit;
    HI_U32 u32Cnt;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_U32 u32stride;
    HI_U32 u32InstanceId;
    VPSS_MC_DATA_S stDataList[VPSS_PRJV_MAX_NODE];
#ifdef HI_VPSS_SMMU_SUPPORT
    SMMU_BUFFER_S stMMUBuf;
#else
    MMZ_BUFFER_S stMMZBuf;
#endif

    SMMU_BUFFER_S stTEEBuf;

    LIST *pstFirstRef;
} VPSS_ST_PRJV_S;

HI_S32 VPSS_ST_PRJV_Init(VPSS_ST_PRJV_S *pstStPrjv, VPSS_MC_ATTR_S *pstAttr);
HI_S32 VPSS_ST_PRJV_DeInit(VPSS_ST_PRJV_S *pstStPrjv);

//��ȡPRJV�˶���Ϣ
HI_S32 VPSS_ST_PRJV_GetCfg(VPSS_ST_PRJV_S *pstStPrjv,
                           VPSS_ST_PRJV_CFG_S *pstStPrjvCfg);

//PRJV�˶���Ϣ������ת
HI_S32 VPSS_ST_PRJV_Complete(VPSS_ST_PRJV_S *pstStPrjv);

//PRJV�˶���Ϣ����reset
HI_S32 VPSS_ST_PRJV_Reset(VPSS_ST_PRJV_S *pstStPrjv);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__VPSS_STT_MCDEI_H__*/
