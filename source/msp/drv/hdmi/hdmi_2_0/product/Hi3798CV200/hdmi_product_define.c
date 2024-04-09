/******************************************************************************

  Copyright (C), 2014-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hdmi_product_define.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2015/08/13
  Description   :
  History       :
  Date          : 2015/08/13
  Author        : sdk
  Modification  :
*******************************************************************************/

#include "hdmi_platform.h"
#ifndef HDMI_BUILD_IN_BOOT
#include "drv_hdmi_platform.h"
#endif
#include "hdmi_product_define.h"

#define PRODUCT_NULL_CHK(p) do{\
    if(HI_NULL == p)\
    {HDMI_ERR("%s is null pointer!return fail.\n",#p);\
    return HI_FAILURE;}\
}while(0)



HI_S32 HDMI_RegWrite  (HI_U32 *pu32RegAddr, HI_U32 u32Value)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    *(volatile HI_U32*)pu32RegAddr = u32Value;
    return HI_SUCCESS;
}


HI_U32 HDMI_RegRead(HI_U32 *pu32RegAddr)
{
    PRODUCT_NULL_CHK(pu32RegAddr);
    return *(volatile HI_U32*)(pu32RegAddr);
}



HI_S32 HDMI_RegWriteMap(HI_U32 u32RegAddr, HI_U32 u32Value)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP(u32RegAddr,4) ;

    if (pu32RegAddr)
    {
        *pu32RegAddr = u32Value ;
        HDMI_IO_UNMAP(pu32RegAddr);
        return HI_SUCCESS;
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x err!\n",u32RegAddr);
        return HI_FAILURE;
    }


}


HI_U32 HDMI_RegReadMap (HI_U32 u32RegAddr)
{
    volatile HI_U32 *pu32RegAddr = HI_NULL;
    HI_U32  u32Value = 0;

    pu32RegAddr = (volatile HI_U32 *)HDMI_IO_MAP(u32RegAddr,4);

    if (pu32RegAddr)
    {
        u32Value = *pu32RegAddr ;
        HDMI_IO_UNMAP(pu32RegAddr);
    }
    else
    {
        HDMI_ERR("HDMI_IO_MAP addr=0x%x\n err!\n",u32RegAddr);
    }

    return  u32Value;
}




HI_VOID DRV_HDMI_ProdIoTrimSet(HI_VOID)
{

    return ;
}
