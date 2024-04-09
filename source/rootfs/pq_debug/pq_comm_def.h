/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : Hi_comm_def.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2013/10/17
  Description   :comm struct definations
  History       :
  1.Date        : 2013/10/17
    Author      : sdk
    Modification: This file is created.
******************************************************************************/

#ifndef __HI_COMM_DEF_H__
#define __HI_COMM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#include "hi_type.h"

#include <unistd.h>
#include <errno.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <semaphore.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "hi_common.h"
#include "hi_debug.h"
#include "hi_mpi_pq.h"


#pragma pack(1)

#define BACKLOG 20
#define CMDBUF_SIZE (0x2FFFF + 0x100)
#define OFFSET_OF(s, m) (size_t)&(((s *)0)->m)
#define GET_VALUE(buf, s, m) ((*(s *)buf).m)
#define CMD_OFFSET 4
#define VIRTUAL_REG_HEAD 0xFF000000
#define ECHO_BYE 0xB0
#define PQ_CFG_FILE "hipq.cfg"
#define PQ_PARSE_ISVIRREG 1
#define PQ_PARSE_ISREG 0
#define MAXLEN 32


/*У��ָ��*/
#define CHECK_PTR_REINT(p) \
    do {\
        if (NULL == p) return HI_FAILURE;\
    } while (0)

/*У�鷵��ֵ*/
#define CHECK_RETURN(ret) \
    do {\
        if (HI_FAILURE == ret) return HI_FAILURE;\
    } while (0)

typedef struct
{
    HI_U32	u32GammCoef[1024];
} HI_DBG_CSC_GAMM_PARA_S;


/*��Ϣ���ݰ�*/
typedef struct hiMDBG_MSG
{
    HI_U32 u32Datalen;                       /*�������ݰ�����*/
    HI_U8  au8MagicNum[4];                   /*ħ����HIPQ��*/
    HI_U8  au32ChipVersion[16];              /*оƬ�ͺ�3518*/
    HI_U8  au32PQVersion[16];                /*PQ�汾V1B01*/
    HI_U32 u32CMD;                           /*ָ����*/
    HI_U32 u32RegType;                       /*��ַ���ͣ�0x00=���� 0x01=���⣩*/
    HI_U32 u32Addr;                          /*��ֵַ*/
    HI_U32 u32Len;                           /*���ݳ�*/
    HI_U8  au8Para[32];                      /*������*/
    HI_U8* pu8Data;                          /*��Ч����*/
    HI_U32 u32DataCheckSum;                  /*���ݰ�У���*/
} HI_MDBG_MSG_S;

/* ECHOӦ������� */
typedef enum hiDBG_ECHO
{
    HI_MAGIC_ERROR          = 0xE0,          /*ħ��У�����*/
    HI_CHECKSUM_ERROR       = 0xE1,          /*����У�����*/
    HI_CHIP_ERROR           = 0xE2,          /*оƬ�汾��ƥ��*/
    HI_VERSION_ERROR        = 0xE3,          /*�汾��ƥ��*/
    HI_INVALID_CMD          = 0xE4,          /*�������*/
    HI_INVALID_ADDRESS_TYPE = 0xE5,          /*��Ч��ַ����*/
    HI_LEN_ERROR            = 0xE6,          /*���ݳ���У��ʧ��*/
    HI_RUN_ERROR            = 0xE7,          /*��˴���ʧ�ܣ��޷��������*/
    HI_NOT_SUPPORTED        = 0xE8,          /*��˲�֧�ִ˲���*/
    HI_BOARD_PROCESS_ERROR  = 0xEE,	         /*��˴���ʧ�ܣ��޷��������*/
    HI_MDBG_ECHO_BUTT
} HI_DBG_ECHO_E;


/* PQ�������� */
typedef enum hiPQ_DBG_CMD
{
    PQ_CMD_READ_REG         = 0,
    PQ_CMD_WRITE_REG        = 1,

    PQ_CMD_READ_MATRIX      = 8,
    PQ_CMD_WRITE_MATRIX     = 9,

    PQ_CMD_READ_REGS        = 10,
    PQ_CMD_WRITE_REGS       = 11,

    PQ_CMD_READ_GAMMA       = 12,
    PQ_CMD_WRITE_GAMMA      = 13,

    PQ_CMD_READ_ACM         = 14,
    PQ_CMD_WRITE_ACM        = 15,
    PQ_CMD_READ_ACC         = 16,
    PQ_CMD_WRITE_ACC        = 17,

    PQ_CMD_EXPORT_BIN       = 18,
    PQ_CMD_IMPORT_BIN       = 19,
    PQ_CMD_FIX_BIN          = 20,

    PQ_CMD_READ_DCI_LUT     = 110,
    PQ_CMD_WRITE_DCI_LUT    = 111,
    PQ_CMD_READ_HIST        = 112,

    PQ_CMD_READ_SNR_MEAN_RATIO  = 113,
    PQ_CMD_READ_SNR_EDGE_STR    = 114,
    PQ_CMD_WRITE_SNR_MEAN_RATIO = 115,
    PQ_CMD_WRITE_SNR_EDGE_STR   = 116,

    PQ_CMD_READ_TNR_PIXMEAN_TO_RATIO_LUMA   = 117,
    PQ_CMD_READ_TNR_PIXMEAN_TO_RATIO_CHROMA = 118,
    PQ_CMD_READ_TNR_MOTION_MAPPING_LUMA     = 119,
    PQ_CMD_READ_TNR_MOTION_MAPPING_CHROMA   = 120,
    PQ_CMD_READ_TNR_FINAL_MOTION_MAPPING_LUMA   = 121,
    PQ_CMD_READ_TNR_FINAL_MOTION_MAPPING_CHROMA = 122,
    PQ_CMD_WRITE_TNR_PIXMEAN_TO_RATIO_LUMA      = 123,
    PQ_CMD_WRITE_TNR_PIXMEAN_TO_RATIO_CHROMA    = 124,
    PQ_CMD_WRITE_TNR_MOTION_MAPPING_LUMA        = 125,
    PQ_CMD_WRITE_TNR_MOTION_MAPPING_CHROMA      = 126,
    PQ_CMD_WRITE_TNR_FINAL_MOTION_MAPPING_LUMA  = 127,
    PQ_CMD_WRITE_TNR_FINAL_MOTION_MAPPING_CHROMA = 128,

    PQ_CMD_READ_FMOTION_MAPPING     = 139,
    PQ_CMD_WRITE_FMOTION_MAPPING    = 140,

    PQ_CMD_READ_HDR_TM_LUT  = 143,
    PQ_CMD_WRITE_HDR_TM_LUT = 144,

    PQ_CMD_READ_HDR_TMAP    = 145,
    PQ_CMD_WRITE_HDR_TMAP   = 146,
    PQ_CMD_READ_HDR_SMAP    = 147,
    PQ_CMD_WRITE_HDR_SMAP   = 148,

    PQ_CMD_READ_GFXHDR_TM_LUT  = 149,
    PQ_CMD_WRITE_GFXHDR_TM_LUT = 150,

    PQ_CMD_BUTT,
} PQ_DBG_CMD_E;

/* ����ģʽ */
typedef enum hiPQ_DBG_DEMO_E
{
    PQ_DBG_DEMO_SHARPNESS = 0,
    PQ_DBG_DEMO_DCI,
    PQ_DBG_DEMO_COLOR,
    PQ_DBG_DEMO_SR,
    PQ_DBG_DEMO_ALL,
    PQ_DBG_DEMO_ALL_OFF,

    PQ_DBG_DEMO_BUTT
} PQ_DBG_DEMO_E;

/*PQ Source Mode*/
typedef enum hiPQ_DBG_SOURCE_MODE_E
{
    PQ_DBG_SOURCE_MODE_NO = 0,
    PQ_DBG_SOURCE_MODE_SD,
    PQ_DBG_SOURCE_MODE_HD,
    PQ_DBG_SOURCE_MODE_UHD,
    PQ_DBG_SOURCE_MODE_BUTT,
} PQ_DBG_SOURCE_MODE_E;

/*PQ Output Mode*/
typedef enum hiPQ_DBG_OUTPUT_MODE_E
{
    PQ_DBG_OUTPUT_MODE_NO = 0,
    PQ_DBG_OUTPUT_MODE_SD,
    PQ_DBG_OUTPUT_MODE_HD,
    PQ_DBG_OUTPUT_MODE_UHD,
    PQ_DBG_OUTPUT_MODE_BUTT,
} PQ_DBG_OUTPUT_MODE_E;


/*��ȡ�Ĵ���������*/
typedef enum hiPQ_DBG_READ_TYPE_E
{
    PQ_DBG_READ_TYPE_PHY = 0,/* ����Ĵ���*/
    PQ_DBG_READ_TYPE_BIN,    /* PQbin */
    PQ_DBG_READ_TYPE_BUTT,
} PQ_DBG_READ_TYPE_E;


/* �������ط�Χ*/
typedef struct tagPQ_DBG_BIT_RANGE
{
    HI_U32 u32OrgBit;
    HI_U32 u32EndBit;
    HI_U32 u32Signed;
} PQ_DBG_BIT_RANGE_S;

/*PQ ����ʵ�ֽṹ*/
typedef struct hiPQ_DBG_CMD_FUN_S
{
    PQ_DBG_CMD_E enDbgCmd;  /* PQ�ڲ�����, �ο�PQ_DBG_CMD_E */
    HI_S32 (*pfCmdFunction)(HI_S32 client_sockfd, HI_U8* pu8Buffer); /*PQ CMD��Ӧ��ʵ�ֺ���*/
} PQ_DBG_CMD_FUN_S;

/*PQ ����Ĵ���ʵ�ֽṹ*/
typedef struct hiPQ_DBG_REG_TYPE_S
{
    HI_U32 u32CmdRegType;    /* PQ ����Ĵ�������, �ο�PQ_DBG_REG_TYPE_E */
    HI_S32 (*pfRegTypeFun)(HI_U32 u32RegAddr, HI_U8* pu8Buffer, HI_U32 u32BufferLen); /*����Ĵ������Ͷ�Ӧ��ʵ�ֺ���*/
} PQ_DBG_REG_TYPE_S;

#pragma pack()

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __HI_COMM_DEF_H__ */
