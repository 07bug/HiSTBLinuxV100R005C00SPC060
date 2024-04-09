#ifndef DRV_DISP_ALG_SERVICE_H
#define DRV_DISP_ALG_SERVICE_H
#include "hi_type.h"
#include "hi_drv_disp.h"
#include <linux/string.h>


#define V0 0
#define V1 1

typedef struct hiAlgInfor_s{
    HI_S32   x_start;        
    HI_U32 u32OrigPos;    
}AlgInfor_s;

typedef struct hiWindowZorderInfor_s{           
    /*input param*/
    HI_U32 		winZorder;    
    HI_U32 		layerZorder;    
    HI_U32 		layerNumber;
    
    /*output param.*/
    HI_DRV_DISP_ZORDER_E   matchOperation;
}WindowZorderInfor_S;


typedef struct hiWindowInfor_S{
    HI_S32   x_start;
    HI_S32   x_end;
    
    HI_S32   y_start;
    HI_S32   y_end;
    
    /*the zorder is a input param.*/
    HI_U32 zorder;
}WindowInfor_S;

typedef struct hiWindowMappingResult_S{
    /* videolayer and regionNo are output params.*/
    HI_U32 videoLayer;    
    HI_U32 regionNo;
    HI_U32 u32OverlapCnt;
}WindowMappingResult_S;


HI_S32 WindowAndLayerMapping( WindowInfor_S *winCoordinate,
            			      WindowMappingResult_S *winMappingResult,
			                  HI_U32 numofWindow);
HI_S32 layerZorderMatch( WindowZorderInfor_S *winZorderInfor,			    
		                 HI_U32  numofWindow);
#endif
