#ifndef __DRV_AO_ENGINE_H__
#define __DRV_AO_ENGINE_H__

#include "hi_type.h"
#include "hal_aoe_common.h"
#include "drv_ao_private.h"

HI_VOID    AO_ENGINE_DeInit(SND_CARD_STATE_S* pCard);

HI_S32     AO_ENGINE_Init(SND_CARD_STATE_S* pCard);

HI_S32     AO_ENGINE_Suspend(SND_CARD_STATE_S* pCard);

HI_S32     AO_ENGINE_Resume(SND_CARD_STATE_S* pCard);

AOE_ENGINE_ID_E AO_ENGINE_FindByType(SND_CARD_STATE_S* pCard, SND_ENGINE_TYPE_E enEngineType);

#endif  // __DRV_AO_ENGINE_H__
