/***********************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : hisi_mem_manager.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      : The user will use this api to realize some function
Function List    :


History           :
Date                      Author                    Modification
2017/10/01                sdk                        Created file
************************************************************************************************/


/****************************  add include here     ********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

/***************************** Macro Definition     ********************************************/

/***************************** Structure Definition ********************************************/

/********************** Global Variable declaration ********************************************/

/********************** API forward declarations    ********************************************/


/**********************       API realization       ********************************************/
static void hisi_mem_manager_log(SurfaceManager *manager)
{
#ifdef CFG_DEBUG_MMZ
   #ifdef CONFIG_HISI_MEM_SUPPORT
      if (NULL != allocation)
      {
        direct_log_printf(dfb_mmz_info.mmz_log, "[mmz-pool]  mem available: %d\n", manager->avail);
      }
   #else
      if (NULL != allocation)
      {
        direct_log_printf(dfb_mmz_info.mmz_log, "[fb-pool]  mem available: %d\n", manager->avail);
      }
   #endif
#endif
   return;
}
