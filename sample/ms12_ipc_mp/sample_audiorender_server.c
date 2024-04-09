/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_audiorender_server.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/11/14
  Description   :
  History       :
  1.Date        : 2017/11/14
    Author      :
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <sys/stat.h>

#include "hi_unf_common.h"
#include "hi_unf_sound.h"

#define RENDER_SERVER_PATH "/tmp/render_server"  /*Must be Readable and writable */

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                  s32Ret;
    HI_UNF_SND_ATTR_S       stAttr;
    HI_UNF_SND_RENDER_ATTR_S stRenderAttr;
    HI_CHAR aCommPath[128];

    HI_SYS_Init();

    /* Init Sound0 */
    s32Ret = HI_UNF_SND_Init();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_Init failed(0x%x).\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_GetDefaultOpenAttr failed(0x%x).\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_Open failed(0x%x).\n", s32Ret);
        return s32Ret;
    }

    /* Start Render */
    memset(aCommPath, 0, sizeof(aCommPath));
    strncpy(aCommPath, RENDER_SERVER_PATH, sizeof(aCommPath));

    stRenderAttr.pCommPath = aCommPath;

    s32Ret = HI_UNF_SND_StartRender(HI_UNF_SND_0, &stRenderAttr);
    if (HI_SUCCESS != s32Ret)
    {
        printf("\n\n\n\n ######### RenderStart failed(0x%x) ##########\n\n\n\n", s32Ret);
        goto EXIT;
    }

    /*Comm file Must be Readable and writable */
    s32Ret = chmod(RENDER_SERVER_PATH, 0x777);
    if (HI_SUCCESS != s32Ret)
    {
        printf("\n\n\n\n ######### Render chmod(%s) failed(0x%x) ##########\n\n\n\n", RENDER_SERVER_PATH, s32Ret);
        goto ERR_CHMOD;
    }

    while (1)
    {
        sleep(1);  /* never say bye bye */
    }

ERR_CHMOD:
    /* Stop Render */
    s32Ret = HI_UNF_SND_StopRender(HI_UNF_SND_0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_StopRender failed(0x%x)\n", s32Ret);
    }

EXIT:
    /* Deinit Sound0 */
    s32Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_Close failed.\n");
    }

    s32Ret = HI_UNF_SND_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        printf("call HI_UNF_SND_DeInit failed.\n");
    }

    HI_SYS_DeInit();

    return s32Ret;
}
