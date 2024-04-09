/******************************************************************************

Copyright (C), 2012-2014, HiSilicon Technologies Co., Ltd.
******************************************************************************
File Name     :
Version       : Initial draft
Author        :
Created Date   :
Last Modified by:
Description   :
Function List :
Change History:
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "hi_type.h"
#include "cc_debug.h"
#include "aribcc_graphic.h"
#include "ccdisp_api.h"
#include "hi_unf_cc.h"

#define ARIBCC_WINDOW_ID  CCDISP_WINDOW_ID_0

#if 0
static HI_S32 remain_height = 0;  /*defined for the zoom rollup*/

static HI_U8 base_palette[64][4]={
        {0,  0,  0, },{255,0,  0  },{0,  255,0, },{255,255,0, },
        {0,  0,  255},{255,0,  255},{0,  255,255},{255,255,255},
        {170,0,  0  },{0,  170,0  },{170,170,0  },{0,  0,  170},
        {170,0,  170},{0,  170,170},{170,170,170},{0,  0,  85 },
        {0,  85, 0  },{0,  85, 85 },{0,  85, 170},{0,  85, 255},
        {0,  170,85 },{0,  170,255},{0,  255,85 },{0,  255,170},
        {85, 0,  0  },{85, 0,  85 },{85, 0,  170},{85, 0,  255},
        {85, 85, 0  },{85, 85, 85 },{85, 85, 170},{85, 85, 255},
        {85, 170,0  },{85, 170,85 },{85, 170,170},{85, 170,255},
        {85, 255,0  },{85, 255,85 },{85, 255,170},{85, 255,255},
        {170,0,  85 },{170,0,  255},{170,85, 0  },{170,85, 85 },
        {170,85, 170},{170,85, 255},{170,170,85 },{170,170,255},
        {170,255,0  },{170,255,85 },{170,255,170},{170,255,255},
        {255,0,  85 },{255,0,  170},{255,85, 0  },{255,85, 85 },
        {255,85, 170},{255,85, 255},{255,170,0  },{255,170,85 },
        {255,170,170},{255,170,255},{255,255,85 },{255,255,170}};

#endif
#define HI_ARUB_CC_DEFAULT_FONTSIZE      (20)


typedef struct tagAribCCDisp_Text_S
{
    HI_U32                u32FgColor;
    HI_UNF_CC_COLOR_S     stFgColor;
    HI_UNF_CC_OPACITY_E   enFgOpacity;
    HI_U32                u32BgColor;
    HI_UNF_CC_COLOR_S     stBgColor;
    HI_UNF_CC_OPACITY_E   enBgOpacity;
    HI_UNF_CC_FONTNAME_E  enFontName;
    HI_UNF_CC_FONTSTYLE_E enFontStyle;
    HI_U8                 u8FontSize;
    HI_U8                 u8FontScale;

    HI_UNF_CC_EdgeType_E  enEdgeType;
    HI_U32                u32EdgeColor;
    HI_UNF_CC_COLOR_S     stEdgeColor;
    HI_UNF_CC_OPACITY_E   enEdgeOpacity;
    HI_UNF_CC_ARIB_PRTDIRECT_E enPrtDirect;
    //HI_BOOL bFlash;
    //HI_S32  s32UnderlinePos;
    //HI_S32  s32UnderlineThick;
} ARIB_CCDisp_Text_S;

typedef struct tagAribCCDisp_Window_S
{
    CCDISP_WINDOW_ID_E   enWinID;
    HI_BOOL              bVisible;
    HI_UNF_CC_RECT_S     stWinRect;
    HI_U32               u32WinColor;
    HI_UNF_CC_COLOR_S    stWinColor;
    HI_UNF_CC_OPACITY_E  enWinOpacity;
    ARIB_CCDisp_Text_S   stText;
} ARIB_CCDisp_Window_S;


typedef struct tagAribCCDisp_Screen_S
{
    HI_UNF_CC_RECT_S     stScreenRect;
    HI_UNF_CC_RECT_S     stClipArea;
    HI_U32                u32ScreenColor;
    HI_UNF_CC_COLOR_S    stScreenColor;
    HI_UNF_CC_OPACITY_E  enScreenOpacity;

    //HI_U16 u16Display_x;
    //HI_U16 u16Display_y;
    //HI_U16 u16displayWidth;
    //HI_U16 u16DisplayHeight;

    //HI_U8 real_font_size[HI_UNF_CC_FN_BUTT][HI_UNF_CC_FONTSIZE_BUTT];   /*to store the font size of nano-x matched theCCFontSize*/
    //HI_U32 flag;                 /*underline and edge type*/

    ARIB_CCDisp_Window_S astWindow[CCDISP_MAX_WINDOWS];
    CCDISP_OPT_S stOpt;
} ARIB_CCDisp_Screen_S;


#ifdef ENABLE_ARIBCC_RENDER_DRAW
extern HI_S32 hi_aribcc_render_draw(HI_U32 u32UserData, HI_UNF_CC_DISPLAY_PARAM_S* pstDisplayParam);
extern HI_S32 hi_aribcc_render_getTextSize(HI_U32 u32Userdata, HI_UNF_CC_TEXT_S *pstText, HI_S32* ps32Width, HI_S32* ps32Heigth);
#endif

#define ARIBCC_WINDOW_ID  CCDISP_WINDOW_ID_0


#define CCDISP_MUTEX_LOCK(x)  \
    do{\
        int ret = pthread_mutex_lock(x);\
        if(ret != 0){\
            HI_ERR_CC("CC call pthread_mutex_lock(DISP) failure,ret = 0x%x\n",ret);\
        }\
    }while(0)

#define CCDISP_MUTEX_UNLOCK(x)  \
    do{\
        int ret = pthread_mutex_unlock(x);\
        if(ret != 0){\
            HI_ERR_CC("CC call pthread_mutex_unlock(DISP) failure, ret = 0x%x\n",ret);\
        }\
    }while(0)

/*****************************************************************************
*                       Macro Definitions
*****************************************************************************/
#define INC(x) if(x < 0) { x = 0;}
#define COLOR2ARGB(a, c) do { \
    (a).u8Alpha = ((c) >> 24) & 0xff; \
    (a).u8Red   = ((c) >> 16) & 0xff; \
    (a).u8Green = ((c) >> 8 ) & 0xff; \
    (a).u8Blue  =  (c)        & 0xff; \
    } while (0)
#define ARGB(a,rgb) (0x00000000==s_u32Opacity[a])||(0x00000000==rgb)?\
        0x00000000:s_u32Opacity[a] |(rgb & 0x00ffffff);

#define ARGB2COLOR(a,c) c=((a).u8Alpha << 24)|((a).u8Red << 16)|((a).u8Green << 8)|((a).u8Blue)

/*****************************************************************************
*                       Type Definitions
*****************************************************************************/
#define INTERLINE_HEIGTH 5
#define MAX_CC_COLUMNS_4B3 32
#define MAX_CC_COLUMNS_16B9 42
/*******************************************************************************
*                       Extern Data Definition
*******************************************************************************/

/*******************************************************************************
*                       Static Data Definition
*******************************************************************************/

                               /*default,   solid,      flash, translucent, transparent */
static HI_U32 s_u32Opacity[5]={0x00000000,0xff000000,0xff000000,0x7f000000,0x00000000};

static ARIB_CCDisp_Screen_S s_astAribCCDispScreen[1];
//static HI_UNF_CC_RECT_S s_astWindowRect[8];
static CCDISP_FlashText_S * s_astCCDispFlashText[8];
static pthread_mutex_t flashMutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t drawMutex = PTHREAD_MUTEX_INITIALIZER;


static HI_S32 AIBCC_DISP_CheckRect(HI_UNF_CC_RECT_S stMasterRect, HI_UNF_CC_RECT_S stSlaveRect)
{
    if ((stSlaveRect.x < stMasterRect.x-1)
        || (stSlaveRect.x + stSlaveRect.width > stMasterRect.x + stMasterRect.width+2)
        || (stSlaveRect.y < stMasterRect.y-1)
        || (stSlaveRect.y + stSlaveRect.height > stMasterRect.y + stMasterRect.height+2))
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_DispInit(CCDISP_INIT_PARAM_S *pstInitParam)
{
    if (HI_NULL == pstInitParam)
    {
        HI_ERR_CC("param is error\n");
        return HI_FAILURE;
    }

    memset(&s_astAribCCDispScreen[0], 0, sizeof(ARIB_CCDisp_Screen_S));
    s_astAribCCDispScreen[0].stOpt = pstInitParam->stOpt;

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_DispDeInit(void)
{
    memset(&s_astAribCCDispScreen[0], 0, sizeof(ARIB_CCDisp_Screen_S));
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_Init(void)
{
    return HI_SUCCESS;
}

/*create the display screen*/
HI_S32 ARIBCC_GRAPHIC_CreateScreen(HI_S32 ccType, HI_S32 width, HI_S32 height)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_UNF_CC_RECT_S stScreenRect;

    stScreenRect.x = stScreenRect.y = 0;
    stScreenRect.width = width;
    stScreenRect.height = height;

    pstScreen->u32ScreenColor = HI_UNF_CC_COLOR_BLACK;
    pstScreen->enScreenOpacity = HI_UNF_CC_OPACITY_TRANSPARENT;
    pstScreen->stScreenRect = stScreenRect;
    pstScreen->u32ScreenColor = HI_UNF_CC_COLOR_BLACK;
    pstScreen->enScreenOpacity = HI_UNF_CC_OPACITY_TRANSPARENT;

    //pstScreen->stClipArea.x = stScreenRect.width /10;
    //pstScreen->stClipArea.y = stScreenRect.height /10;
    //pstScreen->stClipArea.width  = (stScreenRect.width * 8) /10;
    //pstScreen->stClipArea.height = (stScreenRect.height * 8) /10;

    pstScreen->stClipArea = pstScreen->stScreenRect;

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_DestroyScreen(HI_S32 ccType)
{
    (HI_VOID)ARIBCC_GRAPHIC_ClearScreen(ccType, HI_TRUE);
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_ClearScreen(HI_S32 ccType, HI_BOOL bBlit)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_U32 u32RGB = pstScreen->u32ScreenColor;
    HI_UNF_CC_OPACITY_E enOpacity = pstScreen->enScreenOpacity;
    HI_U32 u32Color = 0;
    HI_UNF_CC_DISPLAY_PARAM_S stDispParam;

    //(void)ARIBCC_Text_DeleteCharFlash();

    DISP_TRACE("color:0x%x,opa:%s\n",u32RGB,DBG_OPA_OUT[enOpacity]);

    stDispParam.enOpt = HI_UNF_CC_OPT_FILLRECT;
    stDispParam.stRect = pstScreen->stScreenRect;
    stDispParam.u32DisplayWidth = pstScreen->stScreenRect.width;
    stDispParam.u32DisplayHeight = pstScreen->stScreenRect.height;
    u32Color=ARGB(enOpacity,u32RGB);
    COLOR2ARGB(stDispParam.unDispParam.stFillRect.stColor, u32Color);
    stDispParam.bBlit = bBlit;

    CCDISP_MUTEX_LOCK(&drawMutex);
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stDispParam);
#else
    if (pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(pstScreen->stOpt.pUserData, &stDispParam);
    }
#endif
    CCDISP_MUTEX_UNLOCK(&drawMutex);

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_UpdateScreen()
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_UNF_CC_DISPLAY_PARAM_S stDispParam;

    stDispParam.enOpt = HI_UNF_CC_OPT_UPDATE;
    stDispParam.stRect = pstScreen->stScreenRect;
    stDispParam.u32DisplayWidth = pstScreen->stScreenRect.width;
    stDispParam.u32DisplayHeight = pstScreen->stScreenRect.height;
    stDispParam.bBlit = HI_TRUE;

    CCDISP_MUTEX_LOCK(&drawMutex);
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stDispParam);
#else
    if (pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(pstScreen->stOpt.pUserData, &stDispParam);
    }
#endif
    CCDISP_MUTEX_UNLOCK(&drawMutex);

    return HI_SUCCESS;
}

/*create off screen frame buffer for drawing*/
HI_S32 ARIBCC_GRAPHIC_NewWindow(HI_S32 ccType,HI_S32 x,HI_S32 y,HI_S32 width,HI_S32 height)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_UNF_CC_RECT_S stWinRect;
    HI_U8 u8FontScale = 0;

    stWinRect.x = x;
    stWinRect.y = y;
    stWinRect.width = width;
    stWinRect.height = height;

    if(HI_NULL == pstWindow )
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if (HI_FAILURE == AIBCC_DISP_CheckRect(pstScreen->stClipArea, stWinRect))
    {
        HI_ERR_CC("stWinRect(%d %d %d %d) is invalid ! screen(%d %d %d %d)\n", stWinRect.x, stWinRect.y,
                  stWinRect.width, stWinRect.height, pstScreen->stClipArea.x, pstScreen->stClipArea.y,
                  pstScreen->stClipArea.width, pstScreen->stClipArea.height);
    }

    u8FontScale = pstWindow->stText.u8FontScale;

    memset(pstWindow, 0, sizeof(ARIB_CCDisp_Window_S));
    pstWindow->enWinID            = ARIBCC_WINDOW_ID;
    pstWindow->bVisible           = HI_TRUE;
    pstWindow->stWinRect          = stWinRect;
    pstWindow->u32WinColor         = HI_UNF_CC_COLOR_BLACK;
    pstWindow->enWinOpacity       = HI_UNF_CC_OPACITY_TRANSPARENT;
    pstWindow->stText.u32FgColor   = HI_UNF_CC_COLOR_WHITE;
    pstWindow->stText.enFgOpacity = HI_UNF_CC_OPACITY_SOLID;
    pstWindow->stText.u32BgColor   = HI_UNF_CC_COLOR_BLACK;
    pstWindow->stText.enBgOpacity = HI_UNF_CC_OPACITY_SOLID;
    pstWindow->stText.enEdgeOpacity = HI_UNF_CC_OPACITY_SOLID;
    pstWindow->stText.enFontName  = HI_UNF_CC_FN_DEFAULT;
    pstWindow->stText.enFontStyle = HI_UNF_CC_FONTSTYLE_NORMAL;
    pstWindow->stText.u8FontSize  = HI_ARUB_CC_DEFAULT_FONTSIZE;
    pstWindow->stText.u8FontScale = u8FontScale;

    return HI_SUCCESS;
}

/*free the off-screen frame buffer for the window, when the window size changed. call this function*/
HI_S32 ARIBCC_GRAPHIC_DelWindow(HI_S32 ccType)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    memset(pstWindow, 0, sizeof(ARIB_CCDisp_Window_S));
    pstWindow->bVisible = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_SetWindowSize(HI_S32 ccType,HI_S32 x,HI_S32 y,HI_S32 width,HI_S32 height)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_UNF_CC_RECT_S stWinRect;

    stWinRect.x = x;
    stWinRect.y = y;
    stWinRect.width = width;
    stWinRect.height = height;

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if (HI_FAILURE == AIBCC_DISP_CheckRect(pstScreen->stClipArea, stWinRect))
    {
        HI_ERR_CC("stWinRect(%d %d %d %d) is invalid !\n", stWinRect.x, stWinRect.y,
                  stWinRect.width, stWinRect.height);
    }

    pstWindow->stWinRect = stWinRect;

    return HI_SUCCESS;
}

/*copy the off-screen frame buffer to on-screen using the bitblt. when CC_Arib_text_show will call this
  function to show the cc*/
HI_S32 ARIBCC_GRAPHIC_ShowWindow(HI_S32 ccType,HI_S32 dstx,HI_S32 dsty,HI_S32 width,HI_S32 height,HI_S32 startx,HI_S32 starty,HI_S32 is_colorkey_enable)
{
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_FillWindow(HI_S32 ccType, HI_S32 x, HI_S32 y, HI_S32 width, HI_S32 height, HI_UNF_CC_COLOR_S color)
{
    return ARIBCC_GRAPHIC_FillRect(ccType, x, y, width, height, color, HI_TRUE);
}

HI_S32 ARIBCC_GRAPHIC_SetFGColor(HI_S32 ccType, HI_UNF_CC_COLOR_S color, HI_S32 is_flash)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.stFgColor = color;
    if (HI_TRUE == is_flash)
    {
        pstWindow->stText.enFgOpacity = HI_UNF_CC_OPACITY_FLASH;
    }
    /*text flash 如果配置过闪烁，要恢复回去*/
    else if (pstWindow->stText.enFgOpacity == HI_UNF_CC_OPACITY_FLASH)
    {
        pstWindow->stText.enFgOpacity = HI_UNF_CC_OPACITY_SOLID; /*恢复成初始化Window时的状态*/
    }

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_SetBGColor(HI_S32 ccType,HI_UNF_CC_COLOR_S color)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.stBgColor = color;
    return HI_SUCCESS;
}

/*set text background middle color and foreground middle color*/
HI_S32 ARIBCC_GRAPHIC_SetMidColor(HI_S32 ccType,HI_UNF_CC_COLOR_S fg_mid_color, HI_UNF_CC_COLOR_S bg_mid_color)
{
    return HI_SUCCESS;
}


/*Set font edge type edge color*/
HI_S32 ARIBCC_GRAPHIC_SetEdgeColor(HI_S32 ccType,HI_UNF_CC_COLOR_S edge_color)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.stEdgeColor = edge_color;

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_GetTextSize(HI_S32 ccType, HI_UNF_CC_TEXT_S* pstText, HI_S32 *pWidth, HI_S32 *pHeight)
{
    HI_S32 s32Ret = HI_SUCCESS;
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_S32 s32Width = 0, s32Height = 0;

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

#ifdef ENABLE_ARIBCC_RENDER_DRAW
    s32Ret = hi_aribcc_render_getTextSize(pstScreen->stOpt.u32UserData, pstText, &s32Width, &s32Height);
#else
    if(pstScreen->stOpt.pfnGetTextSizeEx)
    {
        s32Ret = pstScreen->stOpt.pfnGetTextSizeEx(0, pstText, &s32Width, &s32Height);
    }
    else if(pstScreen->stOpt.pfnGetTextSize)
    {
        s32Ret = pstScreen->stOpt.pfnGetTextSize(0, pstText->pu16Text, pstText->u8TextLen, &s32Width, &s32Height);
    }
#endif
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_CC("failed to get text size !\n");
        return HI_FAILURE;
    }

    if (pWidth)
    {
        *pWidth = s32Width;
    }

    if (pHeight)
    {
        *pHeight = s32Height;
    }
    return s32Ret;
}

HI_S32 ARIBCC_GRAPHIC_SetFontSize(HI_S32 ccType, HI_U8 size)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.u8FontSize = size;
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_FillRect(HI_S32 ccType, HI_S32 x, HI_S32 y, HI_S32 width, HI_S32 height, HI_UNF_CC_COLOR_S color, HI_BOOL bBlit)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_UNF_CC_DISPLAY_PARAM_S stDispParam;

    HI_UNF_CC_RECT_S stRect;

    stRect.x = x;
    stRect.y = y;
    stRect.width = width;
    stRect.height = height;

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if( HI_FALSE == pstWindow->bVisible )
    {
        return HI_SUCCESS;
    }

    if (0 == stRect.width || 0 == stRect.height)
    {
        return HI_SUCCESS;
    }

    DISP_TRACE("FillRect, rect[%d %d %d %d], Color : [%d %d %d %d]\n",
               stRect.x,stRect.y,stRect.width,stRect.height,color.u8Alpha,color.u8Red,color.u8Green,color.u8Blue);

    if (HI_FAILURE == AIBCC_DISP_CheckRect(pstWindow->stWinRect, stRect))
    {
        HI_ERR_CC("window rect is (%d %d %d %d)\n", pstWindow->stWinRect.x, pstWindow->stWinRect.y,
                  pstWindow->stWinRect.width, pstWindow->stWinRect.height);
        HI_ERR_CC("stRect(%d %d %d %d) is invalid !\n", stRect.x, stRect.y,
                  stRect.width, stRect.height);
    }

    pstWindow->stWinColor = color;

    stDispParam.enOpt = HI_UNF_CC_OPT_FILLRECT;
    stDispParam.stRect = stRect;
    stDispParam.u32DisplayWidth = pstScreen->stScreenRect.width;
    stDispParam.u32DisplayHeight = pstScreen->stScreenRect.height;
    stDispParam.unDispParam.stFillRect.stColor = color;
    stDispParam.bBlit = bBlit;

    CCDISP_MUTEX_LOCK(&drawMutex);
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stDispParam);
#else
    if (pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(pstScreen->stOpt.pUserData, &stDispParam);
    }
#endif
    CCDISP_MUTEX_UNLOCK(&drawMutex);

    return HI_SUCCESS;


}

/*if the flag is 1, write the caption to the on screen(displayed screen)*/
HI_S32 ARIBCC_GRAPHIC_TextOut(HI_S32 ccType, HI_S32 x, HI_S32 y, void *str, HI_S32 length, HI_S32 charInterval, HI_S32 lineInterval, HI_BOOL bBlit)
{
    HI_S32 s32Ret = HI_SUCCESS;
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_S32 s32Width = 0, s32Height = 0;
    HI_UNF_CC_RECT_S stRect;
    HI_U32 u32FgColor = 0, u32BgColor = 0,u32EdgeColor=0;
    HI_UNF_CC_DISPLAY_PARAM_S stDispParam;
    HI_U16* pu16Str = (HI_U16*)str;
    HI_S32 s32StrLen = length;

    if (ARIBCC_TYPE_CC != ccType)
    {
        HI_ERR_CC("Not implement superimose!\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if (HI_FALSE == pstWindow->bVisible)
    {
        return HI_SUCCESS;
    }

    if ((HI_NULL == pu16Str) || (s32StrLen <= 0))
    {
        HI_ERR_CC("parameter is error\n");
        return HI_FAILURE;
    }

    DISP_TRACE("TextDraw, xy : %d %d, text : %s s32Length : %d \n", x, y, pu16Str, s32StrLen);

    //HI_FLOAT scale;
    //HI_U8 rowNum;

    stDispParam.unDispParam.stText.pu16Text = pu16Str;
    stDispParam.unDispParam.stText.u8TextLen = s32StrLen;
    //u8Justify ?
    //u8WordWrap ?
    stDispParam.unDispParam.stText.enFontStyle = pstWindow->stText.enFontStyle;
    stDispParam.unDispParam.stText.u8AribFontSize = pstWindow->stText.u8FontSize;
    stDispParam.unDispParam.stText.enScaleType = pstWindow->stText.u8FontScale;
    stDispParam.unDispParam.stText.enEdgetype = pstWindow->stText.enEdgeType;
    stDispParam.unDispParam.stText.enPrtDirect = pstWindow->stText.enPrtDirect;
    stDispParam.unDispParam.stText.u8CharInterval = charInterval;
    stDispParam.unDispParam.stText.u8LineInterval = lineInterval;
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    s32Ret = hi_aribcc_render_getTextSize(pstScreen->stOpt.u32UserData, &(stDispParam.unDispParam.stText), &s32Width, &s32Height);
#else
    if(pstScreen->stOpt.pfnGetTextSizeEx)
    {
        s32Ret = pstScreen->stOpt.pfnGetTextSizeEx(0, &stDispParam.unDispParam.stText, &s32Width, &s32Height);
    }
    else if(pstScreen->stOpt.pfnGetTextSize)
    {
        s32Ret = pstScreen->stOpt.pfnGetTextSize(0, pu16Str, s32StrLen, &s32Width, &s32Height);
    }
#endif
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_CC("failed to get text size !\n");
        return HI_FAILURE;
    }

    stRect.x = x;
    stRect.y = y;
    stRect.width = s32Width;
    stRect.height = s32Height;

    stDispParam.enOpt = HI_UNF_CC_OPT_DRAWTEXT;
    stDispParam.stRect = stRect;
    stDispParam.u32DisplayWidth = pstScreen->stScreenRect.width;
    stDispParam.u32DisplayHeight = pstScreen->stScreenRect.height;

    ARGB2COLOR(pstWindow->stText.stFgColor, pstWindow->stText.u32FgColor);
    u32FgColor = ARGB(pstWindow->stText.enFgOpacity,pstWindow->stText.u32FgColor);
    COLOR2ARGB(stDispParam.unDispParam.stText.stFgColor, u32FgColor);

    ARGB2COLOR(pstWindow->stText.stBgColor, pstWindow->stText.u32BgColor);
    u32BgColor = ARGB(pstWindow->stText.enBgOpacity,pstWindow->stText.u32BgColor);
    COLOR2ARGB(stDispParam.unDispParam.stText.stBgColor, u32BgColor);

    ARGB2COLOR(pstWindow->stText.stEdgeColor, pstWindow->stText.u32EdgeColor);
    u32EdgeColor=ARGB(pstWindow->stText.enEdgeOpacity,pstWindow->stText.u32EdgeColor);
    COLOR2ARGB(stDispParam.unDispParam.stText.stEdgeColor, u32EdgeColor);

    //record flash char
    if ((pstWindow->stText.enFgOpacity == HI_UNF_CC_OPACITY_FLASH || pstWindow->stText.enBgOpacity == HI_UNF_CC_OPACITY_FLASH))
    {
        CCDISP_FlashText_S* temp = HI_NULL;
        CCDISP_FlashText_S* text = (CCDISP_FlashText_S*)malloc(sizeof(CCDISP_FlashText_S));
        HI_U16 * pu16buf = (HI_U16*)malloc(2*s32StrLen);
        if (HI_NULL == pu16buf)
        {
            HI_ERR_CC("malloc pu16buf failed\n");
            if(HI_NULL!=text)
            {
                free(text);
            }
        }
        else
        {
            if (HI_NULL == text)
            {
                free(pu16buf);
                HI_ERR_CC("malloc text failed\n");
            }
            else
            {
                memcpy(pu16buf, pu16Str, s32StrLen * 2);
                text->pu16Text = pu16buf;
                text->s32TextLen = s32StrLen;
                text->stRect = stRect;
                text->u32DisplayWidth = pstScreen->stScreenRect.width;
                text->u32DisplayHeight = pstScreen->stScreenRect.height;
                text->u32FgColor = u32FgColor;
                text->u32BgColor = u32BgColor;
                text->u8AribFontSize = pstWindow->stText.u8FontSize;
                text->enScaleType = pstWindow->stText.u8FontScale;
                text->u8CharInterval = charInterval;
                text->u8LineInterval = lineInterval;
                text->enPrtDirect = pstWindow->stText.enPrtDirect;
                if (pstWindow->stText.enFgOpacity == HI_UNF_CC_OPACITY_FLASH)
                {
                    text->bFgFlash = HI_TRUE;
                }
                else
                {
                    text->bFgFlash = HI_FALSE;
                }
                text->next = HI_NULL;

                //head insert
                CCDISP_MUTEX_LOCK(&flashMutex);
                temp = s_astCCDispFlashText[ARIBCC_WINDOW_ID];
                s_astCCDispFlashText[ARIBCC_WINDOW_ID] = text;
                s_astCCDispFlashText[ARIBCC_WINDOW_ID]->next = temp;
                CCDISP_MUTEX_UNLOCK(&flashMutex);
            }
        }
    }
    stDispParam.bBlit = bBlit;
    CCDISP_MUTEX_LOCK(&drawMutex);
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    s32Ret = hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stDispParam);
#else
    if(pstScreen->stOpt.pfnDisplay)
    {
        s32Ret = pstScreen->stOpt.pfnDisplay(0, &stDispParam);
    }
#endif
    CCDISP_MUTEX_UNLOCK(&drawMutex);

    return s32Ret;
}

HI_S32 ARIBCC_GRAPHIC_TextOutEUC(HI_S32 ccType,HI_S32 x, HI_S32 y, void *str, HI_S32 length, HI_S32 flag)
{
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_SetUnderline(HI_S32 ccType, HI_S32 is_under)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if (is_under)
    {
        if ((HI_UNF_CC_FONTSTYLE_ITALIC == pstWindow->stText.enFontStyle)||(HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE == pstWindow->stText.enFontStyle))
        {
            pstWindow->stText.enFontStyle = HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE;
        }
        else
        {
            pstWindow->stText.enFontStyle = HI_UNF_CC_FONTSTYLE_UNDERLINE;
        }
    }
    else
    {
        if ((HI_UNF_CC_FONTSTYLE_ITALIC == pstWindow->stText.enFontStyle)||(HI_UNF_CC_FONTSTYLE_ITALIC_UNDERLINE == pstWindow->stText.enFontStyle))
        {
            pstWindow->stText.enFontStyle = HI_UNF_CC_FONTSTYLE_ITALIC;
        }
        else
        {
            pstWindow->stText.enFontStyle = HI_UNF_CC_FONTSTYLE_NORMAL;
        }
    }

    return HI_SUCCESS;
}

/*set text edge type*/
HI_S32 ARIBCC_GRAPHIC_SetOrnament(HI_S32 ccType, HI_S32 ornament)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.enEdgeType = (HI_U8)ornament;
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_SetFontScale(HI_S32 ccType, ARIBCC_CHARSIZE_E scale)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.u8FontScale = (HI_U8)scale;
    return HI_SUCCESS;
}

/*set print direction*/
HI_S32 ARIBCC_GRAPHIC_SetPrintDirection(HI_S32 ccType, HI_S32 direction)
{
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    pstWindow->stText.enPrtDirect = (HI_UNF_CC_ARIB_PRTDIRECT_E)direction;

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_DrawLine(HI_S32 ccType,HI_S32 x1,HI_S32 y1,HI_S32 x2,HI_S32 y2, HI_UNF_CC_COLOR_S color)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_UNF_CC_DISPLAY_PARAM_S stCCdispalyParm;

    stCCdispalyParm.enOpt = HI_UNF_CC_OPT_DRAWLINE;
    stCCdispalyParm.unDispParam.stLine.u32X1 = x1;
    stCCdispalyParm.unDispParam.stLine.u32Y1 = y1;
    stCCdispalyParm.unDispParam.stLine.u32X2 = x2;
    stCCdispalyParm.unDispParam.stLine.u32Y2 = y2;
    stCCdispalyParm.unDispParam.stLine.stColor = color;
    stCCdispalyParm.bBlit = HI_FALSE;

    //参数检查要用
    stCCdispalyParm.u32DisplayWidth = 1;
    stCCdispalyParm.u32DisplayHeight = 1;
    stCCdispalyParm.stRect.width = 1;
    stCCdispalyParm.stRect.height = 1;

#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stCCdispalyParm);
#else
    if(pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(0, &stCCdispalyParm);
    }
#endif

    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_BlockMove(HI_S32 ccType,HI_S32 srcx, HI_S32 srcy, HI_S32 width, HI_S32 height, HI_S32 dstx, HI_S32 dsty)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);
    HI_UNF_CC_RECT_S stSrcRect, stDstRect;

    HI_S32 s32DstX = dstx;
    HI_S32 s32DstY = dsty;
    HI_S32 s32Width = width;
    HI_S32 s32Height = height;
    HI_S32 s32SrcX = srcx;
    HI_S32 s32SrcY = srcy;

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if( HI_FALSE == pstWindow->bVisible )
    {
        return HI_SUCCESS;
    }

    INC(s32SrcX);
    INC(s32SrcY);
    INC(s32DstX);
    INC(s32DstY);

    if((s32SrcX + s32Width - 1) > pstWindow->stWinRect.width)
    {
        s32Width = pstWindow->stWinRect.width - s32SrcX;
    }
    if((s32DstY + s32Height - 1) > pstWindow->stWinRect.height)
    {
        s32Height = pstWindow->stWinRect.height - s32DstY;
    }

    if((s32DstX + s32Width - 1) > pstWindow->stWinRect.width)
    {
        s32DstX = pstWindow->stWinRect.width - s32Width;
    }
    if((s32DstY + s32Height - 1) > pstWindow->stWinRect.height)
    {
        s32DstY = pstWindow->stWinRect.height - s32Height;
    }

    stSrcRect.x = s32SrcX;
    stSrcRect.y = s32SrcY;
    stSrcRect.width= s32Width;
    stSrcRect.height= s32Height;

    stDstRect.x = s32DstX;
    stDstRect.y = s32DstY;
    stDstRect.width = s32Width;
    stDstRect.height= s32Height;

    if (pstScreen->stOpt.pfnBlit)
    {
        (HI_VOID)pstScreen->stOpt.pfnBlit(0, &stSrcRect, &stDstRect);
    }

    return HI_SUCCESS;
}

/***********************************************************************************************
 * function name: ARIBCC_GRAPHIC_DrawFontBitmap(...)                                                       *
 * description:  Draw font bitmap data to screen.                                              *
 *               for DRCS use. The DRCS character draw. copy the pbitmap from system memory    *
 *               to framebuffer.                                                               *
 ***********************************************************************************************/
HI_S32 ARIBCC_GRAPHIC_DrawFontBitmap(HI_S32 ccType,HI_S32 x,HI_S32 y,HI_U16 width, HI_U16 height, HI_S32 depth, HI_U8 *pbitmap, HI_U32 bitmaplen)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_UNF_CC_DISPLAY_PARAM_S stCCdispalyParm;

    HI_UNF_CC_RECT_S stRect;
    HI_UNF_CC_BITMAP_S stBitmap;

    stRect.x = x;
    stRect.y = y;
    stRect.width  = width;
    stRect.height = height;
    memset(&stBitmap, 0, sizeof(HI_UNF_CC_BITMAP_S));
    stBitmap.s32BitWidth = depth;
    stBitmap.pu8BitmapData = pbitmap;
    stBitmap.u32BitmapDataLen = bitmaplen;

    stCCdispalyParm.enOpt = HI_UNF_CC_OPT_DRAWBITMAP;
    stCCdispalyParm.stRect = stRect;
    stCCdispalyParm.u32DisplayWidth = pstScreen->stScreenRect.width;
    stCCdispalyParm.u32DisplayHeight = pstScreen->stScreenRect.height;
    stCCdispalyParm.unDispParam.stBitmap = stBitmap;
    stCCdispalyParm.bBlit = HI_TRUE;
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stCCdispalyParm);
#else
    if (pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(0, &stCCdispalyParm);
    }
#endif

    return HI_SUCCESS;
}

/*set the flash color opaque. is the is_same_with_fg == 1, We should clear the bit4 of 0x28
  if the is_same_with_fg == 0 we should set the bit4 of ox28 and set the alpha to bit0-3 of 0x28*/
HI_S32 ARIBCC_GRAPHIC_SetFlashOpaqu(HI_S32 ccType, HI_U8 is_same_with_fg, HI_U8 alpha)
{
    return HI_SUCCESS;
}

HI_S32 ARIBCC_GRAPHIC_GetAribPalette(HI_U8 u8Index, HI_UNF_CC_COLOR_S *color)
{
    return HI_SUCCESS;
}


/*There are 64 basic color in ARIB. And plus the alpha (128,0) . There are 129 colors in total
  we set the 0-63 as the basic color(alpha = 255). 64-127 as the trnaslucent color(alpha=128)
  128-191 as the flashing color,   192 as the trnaparent color
  The arib spec has been defined the clut of 129 colors. Please refer to the B14 P267 */
HI_S32 ARIBCC_GRAPHIC_SetAribPalette(HI_S32 ccType)
{
    return HI_SUCCESS;
}


/*The flash behavior is display the foreground color and background color alternatively with
  The frequency 0.5 seconds. The foreground color is pre defined with the lut, but the background
  color combined with the foreground color is random. So we must add this function to set the
  flash background color
  This function is to modify the item in lut of the index specific to fg_color*/
HI_S32 ARIBCC_GRAPHIC_SetFlashBGColor(HI_S32 ccType, HI_UNF_CC_COLOR_S fg_color, HI_UNF_CC_COLOR_S bg_color)
{
    return HI_SUCCESS;
}


/*copy the system memory to frame buffer use the 2dge enginee*/
HI_S32 ARIBCC_GRAPHIC_SysMem2FBCopy(HI_S32 ccType,HI_U8 *pBuf,HI_S32 width,HI_S32 height,HI_S32 bpp,HI_S32 rowbytes,HI_S32 dstx,HI_S32 dsty)
{
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    HI_UNF_CC_DISPLAY_PARAM_S stCCdispalyParm;

    HI_UNF_CC_RECT_S stRect;
    HI_UNF_CC_BITMAP_S stBitmap;

    stRect.x = dstx;
    stRect.y = dsty;
    stRect.width = width;
    stRect.height = height;
    memset(&stBitmap, 0, sizeof(HI_UNF_CC_BITMAP_S));
    stBitmap.pu8BitmapData = pBuf;
    stBitmap.u32BitmapDataLen = (HI_U32)rowbytes;
    stBitmap.s32BitWidth = bpp;

    stCCdispalyParm.enOpt = HI_UNF_CC_OPT_DRAWBITMAP;
    stCCdispalyParm.stRect = stRect;
    stCCdispalyParm.u32DisplayWidth = pstScreen->stScreenRect.width;
    stCCdispalyParm.u32DisplayHeight = pstScreen->stScreenRect.height;
    stCCdispalyParm.unDispParam.stBitmap = stBitmap;
    stCCdispalyParm.bBlit = HI_TRUE;
#ifdef ENABLE_ARIBCC_RENDER_DRAW
    hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stCCdispalyParm);
#else
    if (pstScreen->stOpt.pfnDisplay)
    {
        (HI_VOID)pstScreen->stOpt.pfnDisplay(0, &stCCdispalyParm);
    }
#endif

    return HI_SUCCESS;
}


HI_S32 ARIBCC_GRAPHIC_SetPalette(HI_S32 ccType, ARIBCC_Pallette_S *pLut, HI_S32 start, HI_S32 length)
{
    return HI_SUCCESS;
}

#define ROLLLFT_STEP  4

HI_S32 ARIBCC_GRAPHIC_RollLeft(HI_S32 ccType,HI_U16 x,HI_U16 y, HI_U16 width,HI_U16 height,
                HI_U16 offset,HI_UNF_CC_COLOR_S win_color,HI_U8 speed)
{
    return HI_SUCCESS;
}


HI_S32 ARIBCC_GRAPHIC_RollupStart(HI_S32 ccType)
{
    return HI_SUCCESS;
}


HI_S32 ARIBCC_GRAPHIC_Rollup(HI_S32 ccType,HI_U16 x, HI_U16 width, HI_U16 top_y,
                 HI_U16 btm_y,HI_U16 offset, HI_UNF_CC_COLOR_S win_color,HI_U8 speed)
{
    HI_S32 s32Ret = HI_SUCCESS;
    ARIB_CCDisp_Screen_S *pstScreen = &s_astAribCCDispScreen[0];
    ARIB_CCDisp_Window_S *pstWindow = &(s_astAribCCDispScreen[0].astWindow[ARIBCC_WINDOW_ID]);

    HI_S32 s32RollupStep = 0,s32RollupOffset = 0,s32ScrollStep = 0,s32ScrollHeight= 0;
    HI_U16 u16DstY = 0,u16SrcY= 0;
    HI_UNF_CC_RECT_S stSrcRect, stDstRect;
    HI_U32 u32Color = 0;
    HI_UNF_CC_DISPLAY_PARAM_S stDispParam;


    HI_U16 u16StartY = top_y;
    HI_U16 u16EndY = btm_y;
    HI_U16 u16Offset= offset;
    CCDISP_ROLLSPEED_E enSpeed = CCDISP_SPEED6;

    if(HI_NULL == pstWindow)
    {
        HI_ERR_CC("enWinID : %d is invalid !\n", ARIBCC_WINDOW_ID);
        return HI_FAILURE;
    }

    if( HI_FALSE == pstWindow->bVisible )
    {
        return HI_SUCCESS;
    }

    /*here we should add a function to convert the speed into the rollup step*/

    s32RollupOffset = u16Offset;
    s32ScrollHeight = u16EndY - u16StartY;
    u16DstY = u16StartY;
    s32RollupStep = s32RollupOffset/(enSpeed + 1);

    stDispParam.enOpt = HI_UNF_CC_OPT_FILLRECT;
    stDispParam.u32DisplayWidth = pstScreen->stScreenRect.width;
    stDispParam.u32DisplayHeight = pstScreen->stScreenRect.height;
    u32Color = ARGB(pstWindow->enWinOpacity,pstWindow->u32WinColor);
    COLOR2ARGB(stDispParam.unDispParam.stFillRect.stColor, u32Color);

    while(s32RollupOffset > 0)
    {
        s32ScrollStep = (s32RollupOffset > s32RollupStep) ? s32RollupStep : s32RollupOffset;
        s32RollupOffset -= s32ScrollStep;
        u16SrcY = u16StartY + s32ScrollStep;
        s32ScrollHeight -= s32ScrollStep;

        stSrcRect.x = x;
        stSrcRect.y = u16SrcY;
        stSrcRect.width = width;
        stSrcRect.height = s32ScrollHeight;


        stDstRect.x = x;
        stDstRect.y = u16DstY;
        stDstRect.width = width;
        stDstRect.height = s32ScrollHeight;

        if(pstScreen->stOpt.pfnBlit)
        {
            s32Ret = pstScreen->stOpt.pfnBlit(0, &stSrcRect, &stDstRect);
        }

        stDstRect.x = x;
        stDstRect.y = u16DstY+s32ScrollHeight;
        stDstRect.width = width;
        stDstRect.height = s32ScrollStep;
        stDispParam.stRect = stDstRect;
        stDispParam.bBlit = HI_TRUE;
        CCDISP_MUTEX_LOCK(&drawMutex);
#ifdef ENABLE_ARIBCC_RENDER_DRAW
        s32Ret |= hi_aribcc_render_draw(pstScreen->stOpt.u32UserData, &stDispParam);
#else
        if(pstScreen->stOpt.pfnDisplay)
        {
            s32Ret |= pstScreen->stOpt.pfnDisplay(0, &stDispParam);
        }
#endif
        CCDISP_MUTEX_UNLOCK(&drawMutex);

        //u16SrcY = u16DstY;
    }

    return s32Ret;
}


HI_S32 ARIBCC_GRAPHIC_SetScaleFactor(HI_S32 ccType, HI_S32 vscale, HI_S32 hscale, HI_S32 fifo_lvl)
{
    return HI_SUCCESS;
}


HI_S32 ARIBCC_GRAPHIC_SetResolution(ARIBCC_WINDOWFORMAT_E resolution)
{

    return HI_SUCCESS;
}

