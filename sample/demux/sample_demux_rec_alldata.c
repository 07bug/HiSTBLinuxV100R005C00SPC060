/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_pvr_rec_alldata.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/03/23
  Description   :
  History       :
  1.Date        : 2017/03/23
    Author      : c
    Modification: Created file

******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_unf_common.h"
#include "hi_unf_demux.h"
#include "hi_unf_ecs.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"

#define DEMUX_ID        0
#define TUNER_ID        0  /* tunerID */
#define PORT_ID        DEFAULT_DVB_PORT /* tunerID */


typedef struct
{
    HI_HANDLE   RecHandle;
    HI_CHAR     FileName[256];
    HI_BOOL     ThreadRunFlag;
} TsFileInfo;

HI_VOID* TVL_SaveRecDataThread(HI_VOID *arg)
{
    HI_S32      ret;
    TsFileInfo *Ts      = (TsFileInfo*)arg;
    FILE       *RecFile = HI_NULL;

    RecFile = fopen(Ts->FileName, "w");
    if (!RecFile)
    {
        perror("fopen error");

        Ts->ThreadRunFlag = HI_FALSE;

        return HI_NULL;
    }

    printf("[%s] open file %s\n", __FUNCTION__, Ts->FileName);

    while (Ts->ThreadRunFlag)
    {
        HI_UNF_DMX_REC_DATA_S RecData;

        ret = HI_UNF_DMX_AcquireRecData(Ts->RecHandle, &RecData, 100);
        if (HI_SUCCESS != ret)
        {
            if (HI_ERR_DMX_TIMEOUT == ret)
            {
                continue;
            }

            if (HI_ERR_DMX_NOAVAILABLE_DATA == ret)
            {
                continue;
            }

            printf("[%s] HI_UNF_DMX_AcquireRecData failed 0x%x\n", __FUNCTION__, ret);

            break;
        }

        if (RecData.u32Len != fwrite(RecData.pDataAddr, 1, RecData.u32Len, RecFile))
        {
            perror("[SaveRecDataThread] fwrite error");

            break;
        }
        ret = HI_UNF_DMX_ReleaseRecData(Ts->RecHandle, &RecData);
        if (HI_SUCCESS != ret)
        {
            printf("[%s] HI_UNF_DMX_ReleaseRecData failed 0x%x\n", __FUNCTION__, ret);

            break;
        }

    }

    fclose(RecFile);

    Ts->ThreadRunFlag = HI_FALSE;

    return HI_NULL;
}

HI_S32 TVL_DmxStartRecord(HI_CHAR *Path)
{
    HI_S32                  ret;
    HI_UNF_DMX_REC_ATTR_S   RecAttr;
    HI_HANDLE               RecHandle;
    HI_BOOL                 RecordStatus    = HI_FALSE;
    pthread_t               RecThreadId     = -1;
    TsFileInfo              TsRecInfo;
    HI_CHAR                 FileName[256];

    RecAttr.u32DmxId        = DEMUX_ID;
    RecAttr.u32RecBufSize   = 4 * 1024 * 1024;
    /*this is important for recv TVL data*/
    RecAttr.enRecType       = HI_UNF_DMX_REC_TYPE_ALL_DATA;
    RecAttr.bDescramed      = HI_TRUE;
    RecAttr.enIndexType     = HI_UNF_DMX_REC_INDEX_TYPE_NONE;

    ret = HI_UNF_DMX_CreateRecChn(&RecAttr, &RecHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_CreateRecChn failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        return ret;;
    }

    sprintf(FileName, "%s/recv_alldata", Path);

    ret = HI_UNF_DMX_StartRecChn(RecHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_StartRecChn failed 0x%x\n", __FUNCTION__, __LINE__, ret);

        goto exit;
    }

    RecordStatus = HI_TRUE;

    TsRecInfo.RecHandle     = RecHandle;
    TsRecInfo.ThreadRunFlag = HI_TRUE;
    sprintf(TsRecInfo.FileName, "%s.alldata", FileName);

    ret = pthread_create(&RecThreadId, HI_NULL, TVL_SaveRecDataThread, (HI_VOID*)&TsRecInfo);
    if (0 != ret)
    {
        perror("[DmxStartRecord] pthread_create record error");

        goto exit;
    }

    sleep(1);

    while (1)
    {
        HI_CHAR InputCmd[256]   = {0};

        printf("please input the q to quit!\n");

        fgets(InputCmd, sizeof(InputCmd) - 1, stdin);
        if ('q' == InputCmd[0])
        {
            break;
        }
    }

exit :
    if (-1 != RecThreadId)
    {
        TsRecInfo.ThreadRunFlag = HI_FALSE;
        pthread_join(RecThreadId, HI_NULL);
    }

    if (RecordStatus)
    {
        ret = HI_UNF_DMX_StopRecChn(RecHandle);
        if (HI_SUCCESS != ret)
        {
            printf("[%s - %u] HI_UNF_DMX_StopRecChn failed 0x%x\n", __FUNCTION__, __LINE__, ret);
        }
    }

    ret = HI_UNF_DMX_DestroyRecChn(RecHandle);
    if (HI_SUCCESS != ret)
    {
        printf("[%s - %u] HI_UNF_DMX_DestroyRecChn failed 0x%x\n", __FUNCTION__, __LINE__, ret);
    }

    return ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32      ret;
    HI_CHAR    *Path            = HI_NULL;
    HI_U32      Type            = 0;
    HI_U32      Freq            = 610;
    HI_U32      SymbolRate      = 6875;
    HI_U32      ThridParam      = 64;
    HI_UNF_DMX_PORT_ATTR_S DmxAttachPortAttr;

    if (argc < 4)
    {
        printf( "Usage: %s path serial_parallel_type freq [srate] [qamtype or polarization]\n"
                "       serial_parallel_type: 0: serial, 1: parallel\n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n",
                argv[0]);

        return -1;
    }

    Path        = argv[1];
    Type        = strtol(argv[2], NULL, 0);
    Freq        = strtol(argv[3], NULL, 0);
    SymbolRate  = (Freq > 1000) ? 27500 : 6875;
    ThridParam  = (Freq > 1000) ? 0 : 64;

    if (argc >= 5)
    {
        SymbolRate  = strtol(argv[4], NULL, 0);
    }

    if (argc >= 6)
    {
        ThridParam = strtol(argv[5], NULL, 0);
    }

    HI_SYS_Init();

    ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != ret)
    {
        printf("call HIADP_Demux_Init failed.\n");
        goto TUNER_DEINIT;
    }

    ret = HIADP_Tuner_Connect(TUNER_ID, Freq, SymbolRate, ThridParam);
    if (HI_SUCCESS != ret)
    {
        printf("call HIADP_Tuner_Connect failed.\n");
        goto TUNER_DEINIT;
    }

    ret = HI_UNF_DMX_Init();
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_DMX_Init failed 0x%x\n", ret);
        goto TUNER_DEINIT;
    }

    ret = HI_UNF_DMX_GetTSPortAttr(PORT_ID, &DmxAttachPortAttr);
    /*this is important for recv TVL data*/
    //DmxAttachPortAttr.enPortType = HI_TSI0_TYPE;

    if (1 == Type)
    {
        DmxAttachPortAttr.enPortType = HI_UNF_DMX_PORT_TYPE_PARALLEL_VALID_DUMMY_SYNC;
    }
    else
    {
        DmxAttachPortAttr.enPortType = HI_UNF_DMX_PORT_TYPE_SERIAL;
        DmxAttachPortAttr.u32SerialBitSelector = HI_TSI0_BIT_SELECTOR;
        DmxAttachPortAttr.u32TunerInClk = HI_TSI0_CLK_PHASE_REVERSE;
        DmxAttachPortAttr.enSerialPortShareClk = HI_TSI0_SERIAL_SHARE_CLK;
    }

    ret |= HI_UNF_DMX_SetTSPortAttr(PORT_ID, &DmxAttachPortAttr);
    if (HI_SUCCESS != ret)
    {
        printf("call HI_UNF_DMX_SetTSPortAttr failed.\n");
        goto TUNER_DEINIT;
    }

    ret = HI_UNF_DMX_AttachTSPort(DEMUX_ID, PORT_ID);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_DMX_AttachTSPort failed 0x%x\n", ret);
        goto TUNER_DEINIT;
    }
#if 0
    ret = HIADP_DMX_AttachTSPort(DEMUX_ID, TUNER_ID);
    if (HI_SUCCESS != ret)
    {
        printf("call HI_UNF_DMX_SetTSPortAttr failed.\n");
        goto TUNER_DEINIT;
    }
#endif
    TVL_DmxStartRecord(Path);


    HI_UNF_DMX_DetachTSPort(DEMUX_ID);
    HI_UNF_DMX_DeInit();

TUNER_DEINIT:
    HIADP_Tuner_DeInit();
    HI_SYS_DeInit();

    return ret;
}

