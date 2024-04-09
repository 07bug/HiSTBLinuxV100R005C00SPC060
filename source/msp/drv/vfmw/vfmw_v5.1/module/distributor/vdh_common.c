#include "public.h"
#include "vdh_common.h"
#include "vdh_module.h"

UINT8 g_HalDisable = 1;

/*============== INTERNAL FUNCTION =============*/
static SINT32 Get_Usage_Struct(USAGE_MODULE_E Usage, SINT32 ModuleID, VDH_USAGE_S **pUsage, VDH_COMMON_CTX_S *pCtx)
{
    switch (Usage)
    {
        case USAGE_SCD:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < SCD_MODULE_NUM), "invalid Scd ModuleID");
            *pUsage = &(pCtx->Scd_Module[ModuleID].Usage);
            break;

        case USAGE_MFDE:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < MFDE_MODULE_NUM), "invalid Mfde ModuleID");
            *pUsage = &(pCtx->Mfde_Module[ModuleID].Usage);
            break;

        case USAGE_BPD:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < BPD_MODULE_NUM), "invalid Bpd ModuleID");
            *pUsage = &(pCtx->Bpd_Module[ModuleID].Usage);
            break;

        default:
            dprint(PRN_ERROR, "%s unsupport Usage %d!\n", __func__, Usage);
            return VDH_ERR;
    }

    return VDH_OK;
}

static SINT32 Get_Usage_Member(SPONSOR_TYPE_E Sponsor, UINT8 **pMaster, UINT8 **pGuest, VDH_USAGE_S *pUsage)
{
    switch (Sponsor)
    {
        case SPONSOR_DISTR:
            *pMaster = &(pUsage->DistrUsage);
            pGuest[0] = &(pUsage->NormalUsage);
            pGuest[1] = &(pUsage->SecureUsage);
            break;

        case SPONSOR_NORMAL:
            *pMaster = &(pUsage->NormalUsage);
            pGuest[0] = &(pUsage->DistrUsage);
            pGuest[1] = &(pUsage->SecureUsage);
            break;

        case SPONSOR_SECURE:
            *pMaster = &(pUsage->SecureUsage);
            pGuest[0] = &(pUsage->DistrUsage);
            pGuest[1] = &(pUsage->NormalUsage);
            break;

        default:
            dprint(PRN_ERROR, "%s unsupport sponsor %d!\n", __func__, Sponsor);
            return VDH_ERR;
    }

    return VDH_OK;
}

/*============== EXTERNAL FUNCTION =============*/

/******************************************
 Client notify distributor module idle
******************************************/
VOID VDH_Notify_ModuleIdle(MODULE_TYPE_E Module, SINT32 ModuleID)
{
    VDH_COMMON_CTX_S *pCtx = NULL;

    VDH_GET_COMMON_CTX(pCtx);

    switch (Module)
    {
        case MODULE_SCD:
            VDH_ASSERT((ModuleID >= 0 && ModuleID < SCD_MODULE_NUM), "invalid Scd ModuleID");
            pCtx->Scd_Module[ModuleID].ModuleState = MODULE_IDLE;
            VDH_WakeUp_Distributor(WAKE_UP_SCD_IDLE);
            break;

        case MODULE_MFDE:
            VDH_ASSERT((ModuleID >= 0 && ModuleID < MFDE_MODULE_NUM), "invalid Mfde ModuleID");
            pCtx->Mfde_Module[ModuleID].ModuleState = MODULE_IDLE;
            VDH_WakeUp_Distributor(WAKE_UP_MFDE_IDLE);
            break;

        default:
            dprint(PRN_FATAL, "%s unsupport module %d\n", __func__, Module);
            break;
    }

    return;
}


/******************************************
 Acquire Usage
******************************************/
SINT32 VDH_Acquire_Usage(USAGE_MODULE_E Usage, SINT32 ModuleID, SPONSOR_TYPE_E Sponsor, UINT32 MaxWaitInMs, UINT8 ForceFlag)
{
    UINT8  *pMaster = NULL;
    UINT8 *pGuest[2] = {NULL};
    UINT32 CurWaitInMs   = 0;
    UINT32 StartTimeInMs = 0;
    UINT32 CurTimeInMs   = 0;
    VDH_USAGE_S *pUsage = NULL;
    VDH_COMMON_CTX_S *pCtx   = NULL;

    VDH_GET_COMMON_CTX_RET(pCtx);

    // get usage struct
    if (Get_Usage_Struct(Usage, ModuleID, &pUsage, pCtx) < 0)
    {
        dprint(PRN_ERROR, "%s %d error\n", __func__, __LINE__);
        return VDH_ERR;
    }

    // get usage member
    if (Get_Usage_Member(Sponsor, &pMaster, pGuest, pUsage) < 0)
    {
        dprint(PRN_ERROR, "%s %d error\n", __func__, __LINE__);
        return VDH_ERR;
    }

    // try to get usage
    StartTimeInMs = OSAL_FP_get_time_ms();

    do
    {
        // first check
        if (0 == (*pGuest[0]) && 0 == (*pGuest[1]))
        {
            (*pMaster) = 1;

            // second check
            if (0 == (*pGuest[0]) && 0 == (*pGuest[1]))
            {
                break;
            }

            // second check failed, loose usage, try again
            dprint(PRN_FATAL, "Sponsor %d second wait usage %d failed, try again!\n", Sponsor, Usage);
        }

        (*pMaster) = 0;

        CurTimeInMs = OSAL_FP_get_time_ms();

        if (CurTimeInMs < StartTimeInMs)
        {
            StartTimeInMs = 0;
        }

        CurWaitInMs = CurTimeInMs - StartTimeInMs;

        if (SPONSOR_DISTR == Sponsor)
        {
            OSAL_FP_msleep(5);
        }
    }
    while (CurWaitInMs < MaxWaitInMs);

    if (CurWaitInMs < MaxWaitInMs)
    {
        return VDH_OK;
    }
    else
    {
        if (WITH_FORCE == ForceFlag)
        {
            dprint(PRN_ERROR, "Sponsor %d wait usage %d time out(%d ms), Force to get it!\n", Sponsor, Usage, MaxWaitInMs, *pGuest[0], *pGuest[1]);
            (*pMaster) = 1;
            return VDH_OK;
        }
        else
        {
            dprint(PRN_FATAL, "Sponsor %d wait usage %d time out(%d ms), Guest0 = %d, Guest1 = %d!\n", Sponsor, Usage, MaxWaitInMs, *pGuest[0], *pGuest[1]);
            return VDH_ERR;
        }
    }
}


/******************************************
 Loose Usage
******************************************/
SINT32 VDH_Loose_Usage(USAGE_MODULE_E Usage, SINT32 ModuleID, SPONSOR_TYPE_E Sponsor)
{
    UINT8 *pMaster = NULL;
    VDH_USAGE_S      *pUsage = NULL;
    VDH_COMMON_CTX_S *pCtx = NULL;

    VDH_GET_COMMON_CTX_RET(pCtx);

    // get usage struct
    switch (Usage)
    {
        case USAGE_SCD:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < SCD_MODULE_NUM), "invalid Scd ModuleID");
            pUsage = &(pCtx->Scd_Module[ModuleID].Usage);
            break;

        case USAGE_MFDE:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < MFDE_MODULE_NUM), "invalid Mfde ModuleID");
            pUsage = &(pCtx->Mfde_Module[ModuleID].Usage);
            break;

        case USAGE_BPD:
            VDH_ASSERT_RET((ModuleID >= 0 && ModuleID < BPD_MODULE_NUM), "invalid Bpd ModuleID");
            pUsage = &(pCtx->Bpd_Module[ModuleID].Usage);
            break;

        default:
            dprint(PRN_ERROR, "%s unsupport Usage %d!\n", __func__, Usage);
            return VDH_ERR;
    }

    // get usage member
    switch (Sponsor)
    {
        case SPONSOR_DISTR:
            pMaster = &(pUsage->DistrUsage);
            break;

        case SPONSOR_NORMAL:
            pMaster = &(pUsage->NormalUsage);
            break;

        case SPONSOR_SECURE:
            pMaster = &(pUsage->SecureUsage);
            break;

        default:
            dprint(PRN_ERROR, "%s unsupport sponsor %d!\n", __func__, Sponsor);
            return VDH_ERR;
    }

    // loose usage
    (*pMaster) = 0;

    return VDH_OK;
}


/******************************************
 Get Parameter
******************************************/
SINT32 VDH_Get_Parameter(PARAM_INDEX_E Index, VOID *pParam)
{
    VDH_COMMON_CTX_S *pCtx        = NULL;
    PARAM_STATE_S    *pStateParam = NULL;

    VDH_ASSERT_RET(NULL != pParam, "pParam = NULL");

    VDH_GET_COMMON_CTX_RET(pCtx);

    // TODO: extend other case if needed
    switch (Index)
    {
        case PARAM_INDEX_STATE:
            pStateParam = (PARAM_STATE_S *)pParam;

            if (MODULE_BPD == pStateParam->Type)
            {
                VDH_ASSERT_RET((pStateParam->ModuleID >= 0 && pStateParam->ModuleID < BPD_MODULE_NUM), "invalid Bpd ModuleID");
                pStateParam->State = pCtx->Bpd_Module[pStateParam->ModuleID].ModuleState;
            }
            else
            {
                dprint(PRN_ERROR, "%s Index %d unsupport module type %d!\n", __func__, Index, pStateParam->Type);
            }

            break;

        default:
            dprint(PRN_ERROR, "%s unsupport index %d!\n", __func__, Index);
            return VDH_ERR;
    }

    return VDH_OK;
}


/******************************************
 Set Parameter
******************************************/
SINT32 VDH_Set_Parameter(PARAM_INDEX_E Index, VOID *pParam)
{
    VDH_COMMON_CTX_S *pCtx        = NULL;
    PARAM_STATE_S    *pStateParam = NULL;
    MODULE_DEC_S     *pModule     = NULL;

    VDH_ASSERT_RET(NULL != pParam, "pParam = NULL");

    VDH_GET_COMMON_CTX_RET(pCtx);

    // TODO: extend other case if needed
    switch (Index)
    {
        case PARAM_INDEX_STATE:
            pStateParam = (PARAM_STATE_S *)pParam;

            if (MODULE_BPD == pStateParam->Type)
            {
                VDH_ASSERT_RET((pStateParam->ModuleID >= 0 && pStateParam->ModuleID < BPD_MODULE_NUM), "invalid Bpd ModuleID");
                pModule = &(pCtx->Bpd_Module[pStateParam->ModuleID]);

                if (pModule->PowerState != MODULE_POWER_ON)
                {
                    VDH_Enable_Bpd_Module(pStateParam->ModuleID);
                    pModule->PowerState = MODULE_POWER_ON;
                }

                pModule->ModuleState = pStateParam->State;

                if (MODULE_NORMAL_WORKING == pStateParam->State)
                {
                    pModule->NormalStartCount++;
                }
                else if (MODULE_SECURE_WORKING == pStateParam->State)
                {
                    pModule->SecureStartCount++;
                }
            }
            else
            {
                dprint(PRN_ERROR, "%s unsupport module type %d!\n", __func__, pStateParam->Type);
            }

            break;

        default:
            dprint(PRN_ERROR, "%s unsupport index %d!\n", __func__, Index);
            return VDH_ERR;
    }

    return VDH_OK;
}


/******************************************
 Record Reg Data into Task
******************************************/
VOID VDH_Record_RegData(TASK_PARAM_S *pTask, REG_BASE_E Base, UINT32 Reg, UINT32 Data)
{
    VDH_ASSERT(NULL != pTask, "pTask = NULL");

    if (REG_CRG == Base)
    {
        VDH_Record_CrgRegData(&(pTask->CRG_Regs), Reg, Data);
    }
    else if (REG_SCD == Base)
    {
        VDH_Record_ScdRegData(&(pTask->SCD_Regs), Reg, Data);
    }
    else if (REG_MFDE == Base)
    {
        VDH_Record_MfdeRegData(&(pTask->MFDE_Regs), Reg, Data);
    }
    else
    {
        dprint(PRN_ERROR, "%s unsupport task type %d!\n", __func__, pTask->Type);
    }

    return;
}

