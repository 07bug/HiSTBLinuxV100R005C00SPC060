/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_advca_agent.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#ifndef __DRV_TEE_ADVCA_AGENT_H__
#define __DRV_TEE_ADVCA_AGENT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef CONFIG_TEE

int advca_agent_register(void);

int advca_agent_unregister(void);

#else
static inline int advca_agent_register(void)
{
    return 0;
}

static inline int advca_agent_unregister(void)
{
    return 0;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_TEE_ADVCA_AGENT_H__ */

