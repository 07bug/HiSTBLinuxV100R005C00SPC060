#ifndef __VDM_HAL_DIVX3_C__
#define __VDM_HAL_DIVX3_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID DIVX3HAL_V5R6C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask);
VOID DIVX3HAL_V5R6C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);
VOID DIVX3HAL_V5R6C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam);


SINT32 DIVX3HAL_V5R6C1_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 DIVX3HAL_V5R6C1_StartDec( DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask)
{
    return VDMHAL_OK;
}

VOID DIVX3HAL_V5R6C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam, SINT32 VdhId, VOID *pTask)
{
    return;
}

VOID DIVX3HAL_V5R6C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}

VOID DIVX3HAL_V5R6C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, DIVX3_DEC_PARAM_S *pDivx3DecParam)
{
    return;
}

#endif //__VDM_HAL_REAL9_C__
