#include "vfmw_ctrl.h"
#include "vfmw_tee_client.h"
#include "vfmw_osal_ext.h"
#include "vfmw_osal_proc.h"
#include "ctrl_case.h"
#include "vfmw_sos_kernel_osal.h"

#define PRINT_TEE_VFMW_TIME  (1)

extern const VDEC_CID_NODE VDEC_CID_HandlerTable[];

/* SECURE MARK */
MEMORY_NEEDED_SECVFMW_S *g_pVfmSharewMem  = NULL;
VDEC_CHAN_OPTION_S *g_pChanOption = NULL; //store chan option
RAW_ARRAY_NS *g_pStreamList = NULL; //manage stream buffer
CALLBACK_ARRAY_NS *g_pCallBackList = NULL;//manage callback buffer
VDEC_CHAN_STATE_S  *g_pChanState = NULL; //store chan state
IMAGE_QUEUE_NS     *g_pImageList = NULL; //store image info
UINT8              *g_pProcBuf     = NULL;

SINT32 SEC_VFMW_Init(UINT32 pArgs)
{
    SINT32 ret = VDEC_ERR;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pArgs = SOS_Mmap(pArgs, sizeof(VDEC_OPERATION_S), 1, 1);

    if (pArgs == NULL)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed!\n", __func__, __LINE__);
        return VDEC_ERR;
    }

    ret = VDEC_Init((VDEC_OPERATION_S *)pArgs);

    SOS_Unmap(pArgs, sizeof(VDEC_OPERATION_S));

    return ret;
}

SINT32 SEC_VFMW_Exit(VOID)
{
    SINT32 ret = VDEC_ERR;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    ret = VDEC_Exit();

    return ret;
}

SINT32 SEC_VFMW_Resume(VOID)
{
    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    return VDEC_Resume();
}

SINT32 SEC_VFMW_Suspend(VOID)
{
    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    return VDEC_Suspend();
}

UINT32 SEC_VFMW_GetMapLength(UINT32 eCmdID)
{
    UINT32 Index = 0;
    UINT32 MapLength = 0;

    while (VDEC_CID_HandlerTable[Index].eCmdID < VDEC_CID_BUTT
           && VDEC_CID_HandlerTable[Index].pHandler != NULL)
    {
        if (eCmdID == VDEC_CID_HandlerTable[Index].eCmdID)
        {
            MapLength = VDEC_CID_HandlerTable[Index].Length;
            break;
        }

        Index++;
    }

    return MapLength;
}

SINT32 SEC_VFMW_BeforeControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs)
{
    SINT32 ret = VDEC_OK;

    switch (eCmdID)
    {
        case VDEC_CID_BIND_MEM:
        {
            MEM_REPORT_S *pMemReport;
            MEM_RECORD_S MemRecord = {0};

            pMemReport = (MEM_REPORT_S *)pArgs;

            if (pMemReport->IsMap)
            {
                MemRecord.PhyAddr = pMemReport->PhyAddr;
                MemRecord.Length  = pMemReport->Size;
                pMemReport->VirAddr = PTR_UINT64(OSAL_FP_mmap(&MemRecord));

                if (pMemReport->VirAddr == 0)
                {
                    dprint(PRN_FATAL, "%s map sec mem %s phy 0x%x failed!\n", __func__, pMemReport->BufName, pMemReport->PhyAddr);
                    ret = VDEC_ERR;
                    break;
                }

                ret = MEM_AddMemRecord(pMemReport->PhyAddr, UINT64_PTR(pMemReport->VirAddr), pMemReport->Size);

                if (ret != MEM_MAN_OK)
                {
                    dprint(PRN_FATAL, "%s add mem %s record failed!\n", __func__, pMemReport->BufName);
                    ret = VDEC_ERR;
                    break;
                }
            }
        }
        break;

        default:
            break;
    }

    return ret;
}

SINT32 SEC_VFMW_AfterControl(SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs, SINT32 Result)
{
    SINT32 ret = VDEC_OK;

    switch (eCmdID)
    {
        case VDEC_CID_BIND_MEM:
        {
            MEM_REPORT_S *pMemReport;
            MEM_RECORD_S MemRecord = {0};

            if (Result == VDEC_OK)
            {
                break;
            }

            pMemReport = (MEM_REPORT_S *)pArgs;

            if (pMemReport->IsMap)
            {
                OSAL_FP_unmap(UINT64_PTR(pMemReport->VirAddr));
                MEM_DelMemRecord(pMemReport->PhyAddr, UINT64_PTR(pMemReport->VirAddr), pMemReport->Size);
            }
        }
        break;

        default:
            break;
    }

    return ret;
}

SINT32 SEC_VFMW_Control(SINT32 ChanID, UINT32 eCmdID, UINT32 pArgs, UINT32 ParamLength)
{
    SINT32 ret = VDEC_ERR;
    UINT8  MapFlag = 0;
    UINT32 MapLength = 0;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "Check UUID failed!\n");

        return VDEC_ERR;
    }

    MapLength = SEC_VFMW_GetMapLength(eCmdID);

    if (MapLength != ParamLength)
    {
        dprint(PRN_FATAL, "eCmdID %d check param length failed: MapLength %d != ParamLength %d.\n", eCmdID, MapLength, ParamLength);
    }

    if (pArgs != 0 && MapLength != 0)
    {
        pArgs = SOS_Mmap(pArgs, MapLength, 1, 1);

        if (NULL == pArgs)
        {
            dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__, __LINE__, ret);
            return VDEC_ERR;
        }

        MapFlag = 1;
    }

    ret = SEC_VFMW_BeforeControl(ChanID, eCmdID, pArgs);

    if (ret != VDEC_OK)
    {
        dprint(PRN_ERROR, "%s SEC_VFMW_BeforeControl failed!\n", __func__);
        goto EXIT;
    }

    ret = VDEC_Control(ChanID, eCmdID, (VOID *)pArgs);

    SEC_VFMW_AfterControl(ChanID, eCmdID, pArgs, ret);

EXIT:

    if (1 == MapFlag)
    {
        SOS_Unmap(pArgs, MapLength);
    }

    return ret;
}

SINT32 SEC_VFMW_Thread(VOID)
{
    SINT32 ret = 0;

#if (1 == PRINT_TEE_VFMW_TIME)
    static UINT32 BeginTime = 0;
    static UINT32 StartTime = 0;
    static UINT32 Last_StartTime = 0;

    static UINT32 EndTime = 0;
    static UINT32 TotalTime = 0;
    static UINT32 Count = 0;

    StartTime = SOS_GetTimeInUs();

    if (Count == 0)
    {
        BeginTime = StartTime;
    }

#endif

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    ret = VCTRL_RunProcess();

#if (1 == PRINT_TEE_VFMW_TIME)
    EndTime = SOS_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;

    if (StartTime - Last_StartTime >= 1000 * 15)
    {
        dprint(PRN_TEE, "twice call secure thread exceed cost:   %d  us\n", StartTime - Last_StartTime);
    }

    Last_StartTime = EndTime;

    if (EndTime - StartTime >= 1000 * 5)
    {
        dprint(PRN_TEE, "secure thread exceed cost:  %d  start:   %d  end:   %d   us\n",
               EndTime - StartTime, StartTime, EndTime);
    }

    if (EndTime - BeginTime >= 1000000)
    {
        dprint(PRN_TEE, "secure thread Total: %d  Count: %d  Avg:     %d    us\n", TotalTime, Count, TotalTime / Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }

#endif

    return ret;
}

SINT32 SEC_VFMW_Get_Image(SINT32 ChanID, UINT32 pImage)
{
    SINT32 ret = 0;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pImage = SOS_Mmap(pImage, sizeof(IMAGE), 1, 1);

    if (NULL == pImage)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__, __LINE__, ret);
    }
    else
    {
        ret = VCTRL_GetChanImage(ChanID, (IMAGE *)pImage);
    }

    SOS_Unmap(pImage, sizeof(IMAGE));

    return ret;
}

SINT32 SEC_VFMW_Release_Image(SINT32 ChanID, UINT32 pImage)
{
    SINT32 ret = 0;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    pImage = SOS_Mmap(pImage, sizeof(IMAGE), 1, 1);

    if (NULL == pImage)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__, __LINE__, ret);
    }
    else
    {
        ret = VCTRL_ReleaseChanImage(ChanID, (IMAGE *)pImage);
    }

    SOS_Unmap(pImage, sizeof(IMAGE));

    return ret;
}

SINT32 SEC_VFMW_Read_Proc(UINT32 Page, SINT32 Count)
{
    SINT32 ret = -1;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

    if (g_pProcBuf != NULL)
    {
#ifndef HI_ADVCA_FUNCTION_RELEASE
        ret = SOS_PROC_Read((SINT8 *)g_pProcBuf, Count);
#endif
    }

    return ret;
}

SINT32 SEC_VFMW_Write_Proc(UINT32 Option, SINT32 Value)
{
    SINT32 ret = -1;

    if (SOS_VFMW_CheckUUID() == VDEC_FALSE)
    {
        dprint(PRN_FATAL, "CHeck UUID failed!\n");

        return VDEC_ERR;
    }

#ifndef HI_ADVCA_FUNCTION_RELEASE
    ret = SOS_PROC_Write(Option, Value);
#endif

    return ret;
}

SINT32 SEC_TEST_Memcpy(SINT32 Src, UINT32 Dst, UINT32 Len)
{
    SINT32 ret = -1;
    UINT32 viraddr;

    viraddr = SOS_Mmap(Src, Len, 1, 0);

    if (NULL == viraddr)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__, __LINE__, ret);
        return -1;
    }

    OSAL_FP_memcpy((UINT8 *)Dst, (UINT8 *)viraddr, Len);
    SOS_Unmap(viraddr, Len);

    return 0;
}

/*======================================================================*/
/*     Secure firmware initialization                                   */
/*======================================================================*/
DECLARE_TC_DRV(
    Trusted_Vfmw,
    0,
    0,
    0,
    0,
    VDEC_OpenModule,
    NULL
);

