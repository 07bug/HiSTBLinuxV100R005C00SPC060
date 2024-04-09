#include "sample_ms12.h"

#ifndef __SAMPLE_SERVICE_H__
#define __SAMPLE_SERVICE_H__

#ifdef __cplusplus
extern "C" {
#endif


HI_S32 Sample_Service_GetFreqParams(HI_U32 *pu32Tuner, HI_U32 *pu32TunerFreq, HI_U32 *pu32TunerSrate, HI_U32 *pu32ThirdParam, HI_BOOL bRepeat);
HI_S32 Sample_Service_ProcessKeys(IR_KEY_TYPE_E enKeyType);


#ifdef __cplusplus
}
#endif

#endif

