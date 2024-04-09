/******************************************************************************

Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mpi_mmz.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2006-07-18
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __MPI_MMZ_H__
#define __MPI_MMZ_H__

#include "hi_type.h"
#include "hi_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define HI_INVALID_MEM_ADDR     (0)
#define HI_MEM_ALGIN_SIZE       (0x1000)

/******************************* MPI declaration *****************************/
/*malloc memory for mmz and map to user-state address, bufname and bufsize used to input,
    physic address and user-state used to output*/
/*CNcomment: ����mmz�ڴ棬��ӳ���û�̬��ַ,bufname��bufsize��Ϊ����, �����ַ���û�̬�����ַ��Ϊ��� */
HI_S32 HI_MPI_MMZ_Malloc(HI_MMZ_BUF_S *pstBuf);

/*free user-state map, release mmz memory, make sure that physic address, user-state address and lengh is right*/
/*CNcomment: ����û�̬��ַ��ӳ�䣬���ͷ�mmz�ڴ�,��֤����������ַ���û�̬�����ַ�ͳ�����ȷ*/
HI_S32 HI_MPI_MMZ_Free(HI_MMZ_BUF_S *pstBuf);

/*malloc mmz memory for appointed mmz name, return physic address*/
/*CNcomment: ָ��mmz����������mmz�ڴ棬���������ַ*/
HI_U32 HI_MPI_MMZ_New(HI_U32 u32Size , HI_U32 u32Align, HI_CHAR *ps8MMZName, HI_CHAR *ps8BufName);

/*CNcomment: �ͷ�mmz�ڴ� */
HI_S32 HI_MPI_MMZ_Delete(HI_U32 u32PhysAddr);

/*get physic address accordint to virtual address*/
/**CNcomment:  ���������ַ����ȡ��Ӧ�������ַ */
HI_S32 HI_MPI_MMZ_GetPhyAddr(HI_VOID *pRefAddr, HI_U32 *pu32PhyAddr, HI_U32 *pu32Size);

/*map physic address of mmz memory to user-state virtual address, can appoint whether cached*/
/**CNcomment:  ��mmz����������ַӳ����û�̬�����ַ������ָ���Ƿ�cached*/
HI_VOID *HI_MPI_MMZ_Map(HI_U32 u32PhysAddr, HI_BOOL bCached);

/*unmap user-state address of mmz memory*/
/**CNcomment:  ���mmz�ڴ��û�̬��ַ��ӳ�� */
HI_S32 HI_MPI_MMZ_Unmap(HI_U32 u32PhysAddr);

/*for cached memory, flush cache to memory*/
/**CNcomment:  ����cached�ڴ棬ˢDcache���ڴ� */
HI_S32 HI_MPI_MMZ_Flush(HI_U32 u32PhysAddr);

/* open the /dev/mmz_usedev device */
/**CNcomment: ��/dev/mmz_usedev �豸*/
HI_S32 HI_MPI_MMZ_Open(HI_VOID);

/* close the /dev/mmz_usedev device */
/**CNcomment: �ر�/dev/mmz_usedev �豸*/
HI_S32 HI_MPI_MMZ_Close(HI_VOID);

#ifdef HI_SMMU_SUPPORT
typedef struct
{
    HI_CHAR bufname[MAX_BUFFER_NAME_SIZE];
    HI_U32  bufsize;
 //   HI_BOOL auth_flag;      /**<the secure flag*/ /**<CNcomment:��ȫ���λ��HI_TRUE��ʾ��Ҫ���ð�ȫ��־��HI_FALSE��ʾ������*/
//    HI_BOOL sec_map_flag;   /**<the secure flag for map to the secure CPU*/ /**<CNcomment:��ȫcpuӳ��ı�־λ��HI_TRUE��ʾ��Ҫ����ȫcpuӳ�䣬HI_FALSE��ʾ����Ҫ*/
} HI_MPI_SMMU_SEC_ATTR_S;

typedef struct
{
    HI_U32 smmu_addr;
    HI_U32 smmu_size;
//    HI_BOOL auth_flag;      /**<the secure flag*/ /**<CNcomment:��ȫ���λ��HI_TRUE��ʾ��Ҫ���ð�ȫ��־��HI_FALSE��ʾ������*/
//    HI_BOOL sec_map_flag;   /**<the secure flag for map to the secure CPU*/ /**<CNcomment:��ȫcpuӳ��ı�־λ��HI_TRUE��ʾ��Ҫ����ȫcpuӳ�䣬HI_FALSE��ʾ����Ҫ*/
//    HI_U32 sec_virt;        /**<the map address of secure CPU*/ /**<CNcomment:��secmapflag��Ӧ����ȫcpu��ӳ���ַ��secmapflagΪ1ʱ��Ч*/
  //  HI_U32 fixed_buf_phy;   /**<the physical address of buffer used to reorganize the memory*/ /**<CNcomment: �ڴ������buffer�������ַ*/
//    HI_U32 fixed_buf_size;  /**<the size of buffer used to reorganize the memory*/ /**<CNcomment: �ڴ������buffer��size*/
} HI_MPI_SMMU_SEC_BUF_S;

typedef struct
{
    HI_CHAR bufname[MAX_BUFFER_NAME_SIZE];
    HI_U32  bufsize;
 //   HI_BOOL auth_flag;      /**<the secure flag*/ /**<CNcomment:��ȫ���λ��HI_TRUE��ʾ��Ҫ���ð�ȫ��־��HI_FALSE��ʾ������*/
//    HI_BOOL sec_map_flag;   /**<the secure flag for map to the secure CPU*/ /**<CNcomment:��ȫcpuӳ��ı�־λ��HI_TRUE��ʾ��Ҫ����ȫcpuӳ�䣬HI_FALSE��ʾ����Ҫ*/
} HI_MPI_MMZ_SEC_ATTR_S;

typedef struct
{
    HI_U32 mmz_addr;
    HI_U32 mmz_size;
//    HI_BOOL auth_flag;      /**<the secure flag*/ /**<CNcomment:��ȫ���λ��HI_TRUE��ʾ��Ҫ���ð�ȫ��־��HI_FALSE��ʾ������*/
//    HI_BOOL sec_map_flag;   /**<the secure flag for map to the secure CPU*/ /**<CNcomment:��ȫcpuӳ��ı�־λ��HI_TRUE��ʾ��Ҫ����ȫcpuӳ�䣬HI_FALSE��ʾ����Ҫ*/
//    HI_U32 sec_virt;        /**<the map address of secure CPU*/ /**<CNcomment:��secmapflag��Ӧ����ȫcpu��ӳ���ַ��secmapflagΪ1ʱ��Ч*/
  //  HI_U32 fixed_buf_phy;   /**<the physical address of buffer used to reorganize the memory*/ /**<CNcomment: �ڴ������buffer�������ַ*/
//    HI_U32 fixed_buf_size;  /**<the size of buffer used to reorganize the memory*/ /**<CNcomment: �ڴ������buffer��size*/
} HI_MPI_MMZ_SEC_BUF_S;


HI_U32 HI_MPI_SMMU_New(HI_CHAR *pBufName, HI_U32 Size);

HI_S32 HI_MPI_SMMU_Delete(HI_U32 SmmuAddr);

/* get smmu address accordint to virtual address */
HI_S32 HI_MPI_SMMU_GetSmmuAddrByMapAddr(HI_VOID *pMapAddr, HI_U32 *pSmmuAddr, HI_U32 *pSize);

/*
 * map physic address of mmz memory to user-state virtual address, can appoint whether cached
 * bCached = 1, Cached; bCached = 0, no Cached
 */
HI_VOID *HI_MPI_SMMU_Map(HI_U32 SmmuAddr, HI_BOOL bCached);

HI_S32 HI_MPI_SMMU_Unmap(HI_U32 SmmuAddr);

/* for cached memory, flush cache to memory for smmu */
HI_S32 HI_MPI_SMMU_Flush(HI_U32 SmmuAddr);

/* map phy memory to smmu address */
HI_S32 HI_MPI_SMMU_MapPhytoSmmu(HI_U32 PhyAddr, HI_U32 *pSmmuAddr);

/* unmap smmu address */
HI_S32 HI_MPI_SMMU_UnmapPhyfromSmmu(HI_U32 SmmuAddr);

/* alloc secure memory in the nor secure side */
HI_S32 HI_MPI_SMMU_SecMemAlloc(const HI_MPI_SMMU_SEC_ATTR_S *pSecAttr, HI_MPI_SMMU_SEC_BUF_S *pSecBuf);

/* free secure memory in the nor secure side */
HI_S32 HI_MPI_SMMU_SecMemFree(HI_MPI_SMMU_SEC_BUF_S *pSecBuf);

HI_S32 HI_MPI_MMZ_SecMemAlloc(const HI_MPI_MMZ_SEC_ATTR_S *pSecAttr, HI_MPI_MMZ_SEC_BUF_S *pSecBuf);

HI_S32 HI_MPI_MMZ_SecMemFree(HI_MPI_MMZ_SEC_BUF_S *pSecBuf);

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MPI_MMZ_H__ */

