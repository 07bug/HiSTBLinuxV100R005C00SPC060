#include "vpss_cbb_common.h"

HI_VOID VPSS_DRV_Set_VPSS_VHD0CROP_SIZE(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 height , HI_U32 width )
{
    U_VPSS_VHD0CROP_SIZE VPSS_VHD0CROP_SIZE;

    if ((1 > width) || (1 > height))
    {
        //VPSS_ERROR("Invalid crop w h %d %d\n", width, height);
        //sometimes, function is disabled!
        return;
    }

    VPSS_VHD0CROP_SIZE.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32));
    VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width  = width - 1;
    VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height = height - 1;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32), VPSS_VHD0CROP_SIZE.u32);

}

HI_VOID VPSS_DRV_Set_VPSS_VHD0CROP_POS(S_VPSS_REGS_TYPE *pstVpssRegs , HI_U32 y, HI_U32 x )
{
    U_VPSS_VHD0CROP_POS VPSS_VHD0CROP_POS;
    VPSS_VHD0CROP_POS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS_VHD0CROP_POS.u32));
    VPSS_VHD0CROP_POS.bits.vhd0_crop_x = x;
    VPSS_VHD0CROP_POS.bits.vhd0_crop_y = y;
    VPSS_RegWrite(&(pstVpssRegs->VPSS_VHD0CROP_POS.u32), VPSS_VHD0CROP_POS.u32);
}

