#ifndef __VDM_HAL_REAL9_C__
#define __VDM_HAL_REAL9_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID RV9HAL_V5R6C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId, VOID *pTask);
VOID RV9HAL_V5R6C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);
VOID RV9HAL_V5R6C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam);


SINT32 RV9HAL_V5R6C1_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV9HAL_V5R6C1_StartDec( RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId, VOID *pTask)
{
    return VDMHAL_ERR;
}

VOID RV9HAL_V5R6C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam, SINT32 VdhId, VOID *pTask)
{
    return;
}

VOID RV9HAL_V5R6C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}

VOID RV9HAL_V5R6C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV9_DEC_PARAM_S *pRv9DecParam)
{
    return;
}

#endif //__VDM_HAL_REAL9_C__
