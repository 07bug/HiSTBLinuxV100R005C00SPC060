/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : sample_multi_wm.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/

/*********************************add include here**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hi_go.h"
#include "sample_displayInit.h"

/***************************** Macro Definition ********************************************/

/*************************** Structure Definition ******************************************/
extern HI_S32 HI_GO_SetWindowDispRegion(HI_HANDLE Window, HI_RECT *pRegion);

/********************** Global Variable declaration ****************************************/

/******************************* API declaration *******************************************/
HI_S32 main(HI_S32 argc, HI_CHAR* argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_HANDLE hLayer;
    HIGO_WNDINFO_S WinInfo;
    HI_HANDLE hWindow1 = 0;
    HI_HANDLE hWindow2 = 0;
    HI_HANDLE hWindow3 = 0;
    HI_HANDLE hWinSurface1 = 0;
    HI_HANDLE hWinSurface2 = 0;
    HI_HANDLE hWinSurface3 = 0;
    HI_S32 sWidth = 300, sHeight = 200;
    HIGO_LAYER_INFO_S LayerInfo;
    HIGO_LAYER_E eLayerID = HIGO_LAYER_HD_0;
    HI_RECT Region = {0,0,0,0};
    HI_RECT Rect   = {0,0,0,0};

    ret = Display_Init();
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = HI_GO_Init();
    if (HI_SUCCESS != ret)
    {
        goto ERR1;
    }

    ret = HI_GO_GetLayerDefaultParam(eLayerID, &LayerInfo);
    if (HI_SUCCESS != ret)
    {
        goto ERR2;
    }

    ret = HI_GO_CreateLayer(&LayerInfo, &hLayer);
    if (HI_SUCCESS != ret)
    {
        goto ERR2;
    }

    ret = HI_GO_SetLayerBGColor(hLayer,0xffffffff);
    if (HI_SUCCESS != ret)
    {
        goto ERR3;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("创建第一个窗口\n");
    HI_PRINT("=====================================================\n");
    sleep(1);
    WinInfo.hLayer   = hLayer;
    WinInfo.rect.x   = 0;
    WinInfo.rect.y   = 0;
    WinInfo.rect.w   = sWidth;
    WinInfo.rect.h   = sHeight;
    WinInfo.LayerNum = 0;
    WinInfo.PixelFormat = HIGO_PF_8888;
    WinInfo.BufferType  = HIGO_BUFFER_SINGLE;

    ret = HI_GO_CreateWindowEx(&WinInfo, &hWindow1);
    if (HI_SUCCESS != ret)
    {
        goto ERR3;
    }

    ret = HI_GO_GetWindowSurface(hWindow1, &hWinSurface1);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_FillRect(hWinSurface1,NULL,0xFFFF0000,HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret =  HI_GO_SetWindowOpacity(hWindow1,128);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_UpdateWindow(hWindow1,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("创建第二个窗口\n");
    HI_PRINT("=====================================================\n");
    sleep(1);
    WinInfo.rect.x   = 200;
    WinInfo.rect.y   = 150;
    WinInfo.rect.w   = sWidth;
    WinInfo.rect.h   = sHeight;

    ret = HI_GO_CreateWindowEx(&WinInfo, &hWindow2);
    if (HI_SUCCESS != ret)
    {
        goto ERR3;
    }

    ret = HI_GO_GetWindowSurface(hWindow2, &hWinSurface2);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_FillRect(hWinSurface2,NULL,0xFFFFFF00,HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret =  HI_GO_SetWindowOpacity(hWindow2,128);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_UpdateWindow(hWindow2,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("创建第三个窗口\n");
    HI_PRINT("=====================================================\n");
    sleep(1);
    WinInfo.rect.x   = 400;
    WinInfo.rect.y   = 300;
    WinInfo.rect.w   = sWidth;
    WinInfo.rect.h   = sHeight;

    ret = HI_GO_CreateWindowEx(&WinInfo, &hWindow3);
    if (HI_SUCCESS != ret)
    {
        goto ERR3;
    }

    ret = HI_GO_GetWindowSurface(hWindow3, &hWinSurface3);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_FillRect(hWinSurface3,NULL,0xFF00FF00,HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret =  HI_GO_SetWindowOpacity(hWindow3,128);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_UpdateWindow(hWindow3,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("放大第三个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    Region.x = 300;
    Region.y = 250;
    Region.w = 700;
    Region.h = 400;
    ret = HI_GO_SetWindowDispRegion(hWindow3,&Region);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }
    ret = HI_GO_UpdateWindow(hWindow3, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("更新第一个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    ret = HI_GO_UpdateWindow(hWindow1,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("更新第二个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    ret = HI_GO_UpdateWindow(hWindow2,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("更新第三个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    Rect.x = 50;
    Rect.y = 50;
    Rect.w = 200;
    Rect.h = 100;
    ret = HI_GO_FillRect(hWinSurface3,&Rect,0xFF00FFFF,HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_UpdateWindow(hWindow3,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("局部更新第一个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    Region.x = 100;
    Region.y = 100;
    Region.w = 100;
    Region.h = 100;
    ret = HI_GO_UpdateWindow(hWindow1, &Region);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("全屏第三个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    ret = HI_GO_SetWindowDispRegion(hWindow3,NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }
    ret = HI_GO_UpdateWindow(hWindow3, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("放大第三个窗口\n");
    HI_PRINT("=====================================================\n");
    getchar();
    Region.x = 300;
    Region.y = 250;
    Region.w = 700;
    Region.h = 400;
    ret = HI_GO_SetWindowDispRegion(hWindow3,&Region);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }
    ret = HI_GO_UpdateWindow(hWindow3, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("移动第三个窗口(400 300)\n");
    HI_PRINT("=====================================================\n");
    getchar();
    ret = HI_GO_SetWindowPos(hWindow3,400,300);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }
    ret = HI_GO_UpdateWindow(hWindow3, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    HI_PRINT("\n=====================================================\n");
    HI_PRINT("移动第三个窗口(600 550)\n");
    HI_PRINT("=====================================================\n");
    getchar();
    ret = HI_GO_SetWindowPos(hWindow3,600,550);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }
    ret = HI_GO_UpdateWindow(hWindow3, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

    ret = HI_GO_RefreshLayer(hLayer, NULL);
    if (HI_SUCCESS != ret)
    {
        goto ERR4;
    }

#ifdef CONFIG_GFX_PROC_UNSUPPORT
    sleep(20);
#else
    HI_PRINT("press any key to exit\n");
    getchar();
#endif

ERR4:
    if (0 != hWindow1)
    {
        HI_GO_DestroyWindow(hWindow1);
    }

    if (0 != hWindow2)
    {
        HI_GO_DestroyWindow(hWindow2);
    }

    if (0 != hWindow3)
    {
        HI_GO_DestroyWindow(hWindow3);
    }
ERR3:
    HI_GO_DestroyLayer(hLayer);
ERR2:
    HI_GO_Deinit();
ERR1:

    Display_DeInit();

    return ret;
}
