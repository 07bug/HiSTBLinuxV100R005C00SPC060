#ifndef __VDM_HAL_REAL8_C__
#define __VDM_HAL_REAL8_C__

#include "vdm_hal.h"
#include "decparam.h"

VOID RV8HAL_V4R3C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId, VOID *pTask);
VOID RV8HAL_V4R3C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);
VOID RV8HAL_V4R3C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam);


SINT32 RV8HAL_V4R3C1_InitHal( VOID )
{
    return VDMHAL_OK;
}


SINT32 RV8HAL_V4R3C1_StartDec( RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId, VOID *pTask)
{
    return VDMHAL_ERR;
}

VOID RV8HAL_V4R3C1_WriteReg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam, SINT32 VdhId, VOID *pTask)
{
    return;
}


VOID RV8HAL_V4R3C1_WritePicMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


VOID RV8HAL_V4R3C1_WriteSliceMsg(VDMHAL_HWMEM_S *pHwMem, RV8_DEC_PARAM_S *pRv8DecParam)
{
    return;
}


#endif //__VDM_HAL_REAL8_C__
