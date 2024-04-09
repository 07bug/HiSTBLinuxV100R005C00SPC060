#include <linux/io.h>
#include <linux/delay.h>
//#include "vpss_cbb_reg.h"
#include "vpss_cbb_base.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_assert.h"


int bit_conv(int data_in, int bit)
{
    int data_out;
    if (data_in >> (bit - 1))
    {
        data_out = (0xffffffff << (bit)) | data_in;
    }
    else
    {
        data_out = data_in;
    }
    return data_out;
}

HI_VOID VPSS_HAL_Limit(volatile S_VPSS_REGS_TYPE *vpss_reg)
{
#if 0
    HI_BOOL bErrFlag = HI_FALSE; //err print
    //HI_BOOL bErrFlag = HI_TRUE; //err print

    //CBB_ERRMSG ("vpss cfg constraint check start!\n");
    /*****************************/
    //   Gen From Reg Def File
    /*****************************/

    // unsigned int vhd0_en = vpss_reg->VPSS_CTRL.bits.vhd0_en;
    // unsigned int chk_sum_en = vpss_reg->VPSS_CTRL.bits.chk_sum_en;
    unsigned int dei_en = vpss_reg->VPSS_CTRL.bits.dei_en;
    // unsigned int mcdi_en = vpss_reg->VPSS_CTRL.bits.mcdi_en;
    // unsigned int meds_en = vpss_reg->VPSS_CTRL.bits.meds_en;
    unsigned int nx2_vc1_en = vpss_reg->VPSS_CTRL.bits.nx2_vc1_en;
    unsigned int rgme_en = vpss_reg->VPSS_CTRL.bits.rgme_en;
    // unsigned int blk_det_en = vpss_reg->VPSS_CTRL.bits.blk_det_en;
    unsigned int snr_en = vpss_reg->VPSS_CTRL.bits.snr_en;
    unsigned int tnr_en = vpss_reg->VPSS_CTRL.bits.tnr_en;
    // unsigned int rfr_en = vpss_reg->VPSS_CTRL.bits.rfr_en;
    unsigned int four_pix_en = vpss_reg->VPSS_CTRL.bits.four_pix_en;
    unsigned int fmtc_en = vpss_reg->VPSS_CTRL.bits.fmtc_en;
    //  unsigned int rotate_en = vpss_reg->VPSS_CTRL.bits.rotate_en;
    //  unsigned int prot = vpss_reg->VPSS_CTRL.bits.prot;
    //  unsigned int ifmd_en = vpss_reg->VPSS_CTRL.bits.ifmd_en;
    //  unsigned int igbm_en = vpss_reg->VPSS_CTRL.bits.igbm_en;
    //  unsigned int img_pro_mode = vpss_reg->VPSS_CTRL.bits.img_pro_mode;
    //  unsigned int bfield_first = vpss_reg->VPSS_CTRL.bits.bfield_first;
    //  unsigned int bfield_mode = vpss_reg->VPSS_CTRL.bits.bfield_mode;
    unsigned int bfield = vpss_reg->VPSS_CTRL.bits.bfield;
    // unsigned int ram_bank = vpss_reg->VPSS_CTRL2.bits.ram_bank;
    unsigned int zme_vhd0_en = vpss_reg->VPSS_CTRL3.bits.zme_vhd0_en;
    //  unsigned int vhd0_pre_vfir_en = vpss_reg->VPSS_CTRL3.bits.vhd0_pre_vfir_en;
    unsigned int vhd0_crop_en = vpss_reg->VPSS_CTRL3.bits.vhd0_crop_en;
    unsigned int vhd0_lba_en = vpss_reg->VPSS_CTRL3.bits.vhd0_lba_en;

    unsigned int vhd0_zme_ow = vpss_reg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow;
    unsigned int vhd0_zme_oh = vpss_reg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh;

    unsigned int imgwidth = vpss_reg->VPSS_IMGSIZE.bits.imgwidth;
    unsigned int imgheight = vpss_reg->VPSS_IMGSIZE.bits.imgheight;

    unsigned int in_format = vpss_reg->VPSS_IN_CTRL.bits.in_format;

    unsigned int dei_cfg_addr = vpss_reg->VPSS_DEI_ADDR.bits.dei_cfg_addr;

    unsigned int vhd0_crop_width = vpss_reg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width;
    unsigned int vhd0_crop_height = vpss_reg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height;
    unsigned int vhd0_crop_x = vpss_reg->VPSS_VHD0CROP_POS.bits.vhd0_crop_x;
    unsigned int vhd0_crop_y = vpss_reg->VPSS_VHD0CROP_POS.bits.vhd0_crop_y;
    unsigned int vhd0_lba_width = vpss_reg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_width;
    unsigned int vhd0_lba_height = vpss_reg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_height;
    unsigned int vhd0_lba_xfpos = vpss_reg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_xfpos;
    unsigned int vhd0_lba_yfpos = vpss_reg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_yfpos;


    unsigned int stinfo_stop = vpss_reg->VPSS_DIECTRL.bits.stinfo_stop;

    unsigned int two_four_pxl_share = vpss_reg->VPSS_DIECTRL.bits.two_four_pxl_share;
    unsigned int die_c_mode = vpss_reg->VPSS_DIECTRL.bits.die_c_mode;
    unsigned int die_l_mode = vpss_reg->VPSS_DIECTRL.bits.die_l_mode;

    unsigned int recmode_frmfld_blend_mode = vpss_reg->VPSS_DIELMA2.bits.recmode_frmfld_blend_mode;
    signed int min_north_strength = bit_conv(vpss_reg->VPSS_DIEINTEN.bits.min_north_strength, 16);

    unsigned int bc1_max_dz = vpss_reg->VPSS_DIECHECK1.bits.bc1_max_dz;
    unsigned int bc2_max_dz = vpss_reg->VPSS_DIECHECK2.bits.bc2_max_dz;

    unsigned int bc_gain = vpss_reg->VPSS_DIEDIRTHD.bits.bc_gain;

    unsigned int fld_motion_thd_low = vpss_reg->VPSS_DIEFLDMTN.bits.fld_motion_thd_low;
    unsigned int fld_motion_thd_high = vpss_reg->VPSS_DIEFLDMTN.bits.fld_motion_thd_high;
    signed int fld_motion_curve_slope = bit_conv(vpss_reg->VPSS_DIEFLDMTN.bits.fld_motion_curve_slope, 6);

    unsigned int motion_diff_thd_0 = vpss_reg->VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_0;
    unsigned int motion_diff_thd_1 = vpss_reg->VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_1;
    unsigned int motion_diff_thd_2 = vpss_reg->VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_2;
    unsigned int motion_diff_thd_3 = vpss_reg->VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_3;
    unsigned int motion_diff_thd_4 = vpss_reg->VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_4;
    unsigned int motion_diff_thd_5 = vpss_reg->VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_5;
    unsigned int min_motion_iir_ratio = vpss_reg->VPSS_DIEMTNDIFFTHD1.bits.min_motion_iir_ratio;
    unsigned int max_motion_iir_ratio = vpss_reg->VPSS_DIEMTNDIFFTHD1.bits.max_motion_iir_ratio;
    signed int motion_iir_curve_slope_0 = bit_conv(vpss_reg->VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_0, 6);
    signed int motion_iir_curve_slope_1 = bit_conv(vpss_reg->VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_1, 6);
    signed int motion_iir_curve_slope_2 = bit_conv(vpss_reg->VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_2, 6);
    signed int motion_iir_curve_slope_3 = bit_conv(vpss_reg->VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_3, 6);
    unsigned int motion_iir_curve_ratio_0 = vpss_reg->VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_ratio_0;
    unsigned int motion_iir_curve_ratio_1 = vpss_reg->VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_1;
    unsigned int motion_iir_curve_ratio_2 = vpss_reg->VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_2;
    unsigned int motion_iir_curve_ratio_3 = vpss_reg->VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_3;
    unsigned int motion_iir_curve_ratio_4 = vpss_reg->VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_4;
    unsigned int ppre_info_en = vpss_reg->VPSS_DIEHISMODE.bits.ppre_info_en;
    unsigned int pre_info_en = vpss_reg->VPSS_DIEHISMODE.bits.pre_info_en;

    unsigned int frame_motion_smooth_thd0 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd0;
    unsigned int frame_motion_smooth_thd1 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd1;
    unsigned int frame_motion_smooth_thd2 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd2;
    unsigned int frame_motion_smooth_thd3 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd3;
    unsigned int frame_motion_smooth_thd4 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd4;
    unsigned int frame_motion_smooth_thd5 = vpss_reg->VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd5;
    unsigned int frame_motion_smooth_ratio_min = vpss_reg->VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_min;
    unsigned int frame_motion_smooth_ratio_max = vpss_reg->VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_max;
    signed int frame_motion_smooth_slope0 = bit_conv(vpss_reg->VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope0, 6);
    signed int frame_motion_smooth_slope1 = bit_conv(vpss_reg->VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope1, 6);
    signed int frame_motion_smooth_slope2 = bit_conv(vpss_reg->VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope2, 6);
    signed int frame_motion_smooth_slope3 = bit_conv(vpss_reg->VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope3, 6);
    unsigned int frame_motion_smooth_ratio0 = vpss_reg->VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_ratio0;
    unsigned int frame_motion_smooth_ratio1 = vpss_reg->VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio1;
    unsigned int frame_motion_smooth_ratio2 = vpss_reg->VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio2;
    unsigned int frame_motion_smooth_ratio3 = vpss_reg->VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio3;
    unsigned int frame_motion_smooth_ratio4 = vpss_reg->VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio4;
    unsigned int frame_field_blend_thd0 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd0;
    unsigned int frame_field_blend_thd1 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd1;
    unsigned int frame_field_blend_thd2 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd2;
    unsigned int frame_field_blend_thd3 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd3;
    unsigned int frame_field_blend_thd4 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd4;
    unsigned int frame_field_blend_thd5 = vpss_reg->VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd5;
    unsigned int frame_field_blend_ratio_min = vpss_reg->VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_min;
    unsigned int frame_field_blend_ratio_max = vpss_reg->VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_max;
    signed int frame_field_blend_slope0 = bit_conv(vpss_reg->VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope0, 6);
    signed int frame_field_blend_slope1 = bit_conv(vpss_reg->VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope1, 6);
    signed int frame_field_blend_slope2 = bit_conv(vpss_reg->VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope2, 6);
    signed int frame_field_blend_slope3 = bit_conv(vpss_reg->VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope3, 6);
    unsigned int frame_field_blend_ratio0 = vpss_reg->VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_ratio0;
    unsigned int frame_field_blend_ratio1 = vpss_reg->VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio1;
    unsigned int frame_field_blend_ratio2 = vpss_reg->VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio2;
    unsigned int frame_field_blend_ratio3 = vpss_reg->VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio3;
    unsigned int frame_field_blend_ratio4 = vpss_reg->VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio4;

    unsigned int inter_diff_thd0 = vpss_reg->VPSS_DIEEDGENORM4.bits.inter_diff_thd0;

    unsigned int inter_diff_thd1 = vpss_reg->VPSS_DIEEDGENORM5.bits.inter_diff_thd1;

    unsigned int inter_diff_thd2 = vpss_reg->VPSS_DIEEDGEFORMC.bits.inter_diff_thd2;

    signed int mc_strength_k0 = bit_conv(vpss_reg->VPSS_DIEMCSTRENGTH0.bits.mc_strength_k0, 8);
    signed int mc_strength_k1 = bit_conv(vpss_reg->VPSS_DIEMCSTRENGTH0.bits.mc_strength_k1, 8);
    signed int mc_strength_k2 = bit_conv(vpss_reg->VPSS_DIEMCSTRENGTH0.bits.mc_strength_k2, 8);

    unsigned int mc_strength_ming = vpss_reg->VPSS_DIEMCSTRENGTH1.bits.mc_strength_ming;
    unsigned int mc_strength_maxg = vpss_reg->VPSS_DIEMCSTRENGTH1.bits.mc_strength_maxg;
    signed int force_mvx      = vpss_reg->VPSS_MCDI_SEL.bits.force_mvx;
    signed int core_mag_rgmvls = bit_conv(vpss_reg->VPSS_MCDI_RGMAG1.bits.core_mag_rgmvls, 7);

    unsigned int k_max_core_mcw = vpss_reg->VPSS_MCDI_WNDMCW0.bits.k_max_core_mcw;
    unsigned int k_max_dif_mcw = vpss_reg->VPSS_MCDI_WNDMCW0.bits.k_max_dif_mcw;
    unsigned int k1_max_mag_mcw = vpss_reg->VPSS_MCDI_WNDMCW0.bits.k1_max_mag_mcw;
    unsigned int k0_max_mag_mcw = vpss_reg->VPSS_MCDI_WNDMCW0.bits.k0_max_mag_mcw;
    unsigned int k_tbdif_mcw = vpss_reg->VPSS_MCDI_WNDMCW0.bits.k_tbdif_mcw;
    unsigned int k_tbmag_mcw = vpss_reg->VPSS_MCDI_WNDMCW1.bits.k_tbmag_mcw;

    unsigned int gain_lpf_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT0.bits.gain_lpf_dw;
    unsigned int core_bhvdif_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT0.bits.core_bhvdif_dw;
    unsigned int k_bhvdif_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT0.bits.k_bhvdif_dw;
    unsigned int b_bhvdif_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT0.bits.b_bhvdif_dw;
    unsigned int b_hvdif_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT0.bits.b_hvdif_dw;
    unsigned int core_hvdif_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT1.bits.core_hvdif_dw;

    signed int core_mv_dw = bit_conv(vpss_reg->VPSS_MCDI_VERTWEIGHT1.bits.core_mv_dw, 4);
    unsigned int b_mv_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT1.bits.b_mv_dw;

    unsigned int x0_mv_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT3.bits.x0_mv_dw;
    unsigned int k0_mv_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT3.bits.k0_mv_dw;
    unsigned int g0_mv_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT3.bits.g0_mv_dw;
    unsigned int k1_mv_dw = vpss_reg->VPSS_MCDI_VERTWEIGHT3.bits.k1_mv_dw;

    unsigned int gain_up_mclpfv = vpss_reg->VPSS_MCDI_MC0.bits.gain_up_mclpfv;
    unsigned int gain_dn_mclpfv = vpss_reg->VPSS_MCDI_MC0.bits.gain_dn_mclpfv;
    unsigned int gain_mclpfh = vpss_reg->VPSS_MCDI_MC0.bits.gain_mclpfh;

    unsigned int g_pxlmag_mcw = vpss_reg->VPSS_MCDI_MC1.bits.g_pxlmag_mcw;

    unsigned int c0_mc = vpss_reg->VPSS_MCDI_MC5.bits.c0_mc;
    unsigned int r0_mc = vpss_reg->VPSS_MCDI_MC5.bits.r0_mc;
    unsigned int c1_mc = vpss_reg->VPSS_MCDI_MC6.bits.c1_mc;
    unsigned int r1_mc = vpss_reg->VPSS_MCDI_MC6.bits.r1_mc;
    unsigned int mcmvrange = vpss_reg->VPSS_MCDI_MC6.bits.mcmvrange;

    unsigned int mcstartr = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcstartr;
    unsigned int mcstartc = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcstartc;
    unsigned int mcendr = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcendr;
    unsigned int mcendc = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcendc;
    unsigned int movethdh = vpss_reg->VPSS_MCDI_LCDINEW1.bits.movethdh;
    unsigned int movethdl = vpss_reg->VPSS_MCDI_LCDINEW1.bits.movethdl;
    unsigned int movecorig = vpss_reg->VPSS_MCDI_LCDINEW1.bits.movecorig;
    unsigned int movegain = vpss_reg->VPSS_MCDI_LCDINEW1.bits.movegain;


    unsigned int submv_sadchk_en = vpss_reg->VPSS_MCDI_S3ADD7.bits.submv_sadchk_en;

    unsigned int demo_mode_l = vpss_reg->VPSS_MCDI_DEMO.bits.demo_mode_l;
    unsigned int demo_mode_r = vpss_reg->VPSS_MCDI_DEMO.bits.demo_mode_r;
    unsigned int demo_border = vpss_reg->VPSS_MCDI_DEMO.bits.demo_border;

    unsigned int hratio = vpss_reg->VPSS_VHD0_HSP.bits.hratio;

    unsigned int hchmsc_en = vpss_reg->VPSS_VHD0_HSP.bits.hchmsc_en;
    unsigned int hlmsc_en = vpss_reg->VPSS_VHD0_HSP.bits.hlmsc_en;
    unsigned int hor_loffset = vpss_reg->VPSS_VHD0_HLOFFSET.bits.hor_loffset;
    unsigned int hor_coffset = vpss_reg->VPSS_VHD0_HCOFFSET.bits.hor_coffset;
    //  unsigned int zme_out_fmt = vpss_reg->VPSS_VHD0_VSP.bits.zme_out_fmt;

    unsigned int vchmsc_en = vpss_reg->VPSS_VHD0_VSP.bits.vchmsc_en;
    unsigned int vlmsc_en = vpss_reg->VPSS_VHD0_VSP.bits.vlmsc_en;
    unsigned int vratio = vpss_reg->VPSS_VHD0_VSR.bits.vratio;
    unsigned int vchroma_offset = vpss_reg->VPSS_VHD0_VOFFSET.bits.vchroma_offset;
    unsigned int vluma_offset = vpss_reg->VPSS_VHD0_VOFFSET.bits.vluma_offset;

    unsigned int db_lum_h_blk_size = vpss_reg->VPSS_DB_BLK.bits.db_lum_h_blk_size;

    unsigned int db_lum_hor_txt_win_size = vpss_reg->VPSS_DB_RATIO.bits.db_lum_hor_txt_win_size;

    unsigned int db_dir_smooth_mode = vpss_reg->VPSS_DB_CTRS.bits.db_dir_smooth_mode;

    unsigned int db_max_lum_hor_db_dist = vpss_reg->VPSS_DB_CTRS.bits.db_max_lum_hor_db_dist;

    unsigned int db_lum_h_str_fade_lut_p0 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p0;
    unsigned int db_lum_h_str_fade_lut_p1 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p1;
    unsigned int db_lum_h_str_fade_lut_p2 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p2;
    unsigned int db_lum_h_str_fade_lut_p3 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p3;
    unsigned int db_lum_h_str_fade_lut_p4 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p4;
    unsigned int db_lum_h_str_fade_lut_p5 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p5;
    unsigned int db_lum_h_str_fade_lut_p6 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p6;
    unsigned int db_lum_h_str_fade_lut_p7 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p7;
    unsigned int db_lum_h_str_fade_lut_p8 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p8;
    unsigned int db_lum_h_str_fade_lut_p9 = vpss_reg->VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p9;
    unsigned int db_lum_h_str_fade_lut_p10 = vpss_reg->VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p10;
    unsigned int db_lum_h_str_fade_lut_p11 = vpss_reg->VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p11;
    unsigned int db_dir_str_gain_lut_p0 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p0;
    unsigned int db_dir_str_gain_lut_p1 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p1;
    unsigned int db_dir_str_gain_lut_p2 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p2;
    unsigned int db_dir_str_gain_lut_p3 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p3;
    unsigned int db_dir_str_gain_lut_p4 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p4;
    unsigned int db_dir_str_gain_lut_p5 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p5;
    unsigned int db_dir_str_gain_lut_p6 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p6;
    unsigned int db_dir_str_gain_lut_p7 = vpss_reg->VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p7;
    unsigned int db_dir_str_lut_p0 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p0;
    unsigned int db_dir_str_lut_p1 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p1;
    unsigned int db_dir_str_lut_p2 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p2;
    unsigned int db_dir_str_lut_p3 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p3;
    unsigned int db_dir_str_lut_p4 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p4;
    unsigned int db_dir_str_lut_p5 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p5;
    unsigned int db_dir_str_lut_p6 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p6;
    unsigned int db_dir_str_lut_p7 = vpss_reg->VPSS_DB_LUT5.bits.db_dir_str_lut_p7;
    unsigned int db_dir_str_lut_p8 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p8;
    unsigned int db_dir_str_lut_p9 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p9;
    unsigned int db_dir_str_lut_p10 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p10;
    unsigned int db_dir_str_lut_p11 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p11;
    unsigned int db_dir_str_lut_p12 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p12;
    unsigned int db_dir_str_lut_p13 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p13;
    unsigned int db_dir_str_lut_p14 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p14;
    unsigned int db_dir_str_lut_p15 = vpss_reg->VPSS_DB_LUT6.bits.db_dir_str_lut_p15;
    unsigned int db_adpt_flt_mode = vpss_reg->VPSS_DB_ADPT.bits.db_adpt_flt_mode;
    unsigned int db_adpt_delta_adj0 = vpss_reg->VPSS_DB_ADPT.bits.db_adpt_delta_adj0;
    unsigned int db_adpt_delta_scl = vpss_reg->VPSS_DB_ADPT.bits.db_adpt_delta_scl;

    unsigned int dm_csw_trsnt_st_10 = vpss_reg->VPSS_DM_DIRO.bits.dm_csw_trsnt_st_10;
    unsigned int dm_csw_trsnt_st = vpss_reg->VPSS_DM_LSW.bits.dm_csw_trsnt_st;
    signed int dm_mmf_lr = bit_conv(vpss_reg->VPSS_DM_MMFLR.bits.dm_mmf_lr, 9);
    signed int dm_mmf_lr_10 = bit_conv(vpss_reg->VPSS_DM_MMFLR.bits.dm_mmf_lr_10, 11);
    unsigned int dm_csw_trsnt_lt = vpss_reg->VPSS_DM_MMFLR.bits.dm_csw_trsnt_lt;
    signed int dm_mmf_sr = bit_conv(vpss_reg->VPSS_DM_MMFSR.bits.dm_mmf_sr, 9);
    signed int dm_mmf_sr_10 = bit_conv(vpss_reg->VPSS_DM_MMFSR.bits.dm_mmf_sr_10, 11);
    unsigned int dm_csw_trsnt_lt_10 = vpss_reg->VPSS_DM_MMFSR.bits.dm_csw_trsnt_lt_10;
    signed int dm_trans_wid = vpss_reg->VPSS_DM_TRANS_WID.bits.dm_trans_wid;
    signed int dm_trans_wid_10 = vpss_reg->VPSS_DM_TRANS_WID.bits.dm_trans_wid_10;


    unsigned int edgemaxratio = vpss_reg->VPSS_SNR_EDGE_RATIORANGE.bits.edgemaxratio;
    unsigned int edgeminratio = vpss_reg->VPSS_SNR_EDGE_RATIORANGE.bits.edgeminratio;
    unsigned int edgeoriratio = vpss_reg->VPSS_SNR_EDGE_RATIORANGE.bits.edgeoriratio;
    unsigned int edgemaxstrength = vpss_reg->VPSS_SNR_EDGE_STRRANGE.bits.edgemaxstrength;
    unsigned int edgeminstrength = vpss_reg->VPSS_SNR_EDGE_STRRANGE.bits.edgeminstrength;
    unsigned int edgeoristrength = vpss_reg->VPSS_SNR_EDGE_STRRANGE.bits.edgeoristrength;
    unsigned int edgestrth1 = vpss_reg->VPSS_SNR_EDGE_STRTH.bits.edgestrth1;
    unsigned int edgestrth2 = vpss_reg->VPSS_SNR_EDGE_STRTH.bits.edgestrth2;
    unsigned int edgestrth3 = vpss_reg->VPSS_SNR_EDGE_STRTH.bits.edgestrth3;
    unsigned int edgestrk1 = vpss_reg->VPSS_SNR_EDGE_STRK.bits.edgestrk1;
    unsigned int edgestrk2 = vpss_reg->VPSS_SNR_EDGE_STRK.bits.edgestrk2;
    unsigned int edgestrk3 = vpss_reg->VPSS_SNR_EDGE_STRK.bits.edgestrk3;
    unsigned int edgemeanth1 = vpss_reg->VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth1;
    unsigned int edgemeanth2 = vpss_reg->VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth2;
    unsigned int edgemeanth3 = vpss_reg->VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth3;
    unsigned int edgemeanth4 = vpss_reg->VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth4;
    unsigned int edgemeanth5 = vpss_reg->VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth5;
    unsigned int edgemeanth6 = vpss_reg->VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth6;
    unsigned int edgemeanth7 = vpss_reg->VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth7;
    unsigned int edgemeanth8 = vpss_reg->VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth8;
    unsigned int edgemeank1 = vpss_reg->VPSS_SNR_EDGE_MEANK1.bits.edgemeank1;
    unsigned int edgemeank2 = vpss_reg->VPSS_SNR_EDGE_MEANK1.bits.edgemeank2;
    unsigned int edgemeank3 = vpss_reg->VPSS_SNR_EDGE_MEANK1.bits.edgemeank3;
    unsigned int edgemeank4 = vpss_reg->VPSS_SNR_EDGE_MEANK1.bits.edgemeank4;
    unsigned int edgemeank5 = vpss_reg->VPSS_SNR_EDGE_MEANK2.bits.edgemeank5;
    unsigned int edgemeank6 = vpss_reg->VPSS_SNR_EDGE_MEANK2.bits.edgemeank6;
    unsigned int edgemeank7 = vpss_reg->VPSS_SNR_EDGE_MEANK2.bits.edgemeank7;
    unsigned int edgemeank8 = vpss_reg->VPSS_SNR_EDGE_MEANK2.bits.edgemeank8;
    unsigned int y2dwinwidth = vpss_reg->VPSS_SNR_WIN.bits.y2dwinwidth;
    unsigned int y2dwinheight = vpss_reg->VPSS_SNR_WIN.bits.y2dwinheight;
    unsigned int c2dwinwidth = vpss_reg->VPSS_SNR_WIN.bits.c2dwinwidth;
    unsigned int c2dwinheight = vpss_reg->VPSS_SNR_WIN.bits.c2dwinheight;

    unsigned int ratio1 = vpss_reg->VPSS_SNR_EDGE_RATIO_1.bits.ratio1;
    unsigned int ratio2 = vpss_reg->VPSS_SNR_EDGE_RATIO_1.bits.ratio2;
    unsigned int ratio3 = vpss_reg->VPSS_SNR_EDGE_RATIO_1.bits.ratio3;
    unsigned int ratio4 = vpss_reg->VPSS_SNR_EDGE_RATIO_2.bits.ratio4;
    unsigned int ratio5 = vpss_reg->VPSS_SNR_EDGE_RATIO_2.bits.ratio5;
    unsigned int ratio6 = vpss_reg->VPSS_SNR_EDGE_RATIO_2.bits.ratio6;
    unsigned int ratio7 = vpss_reg->VPSS_SNR_EDGE_RATIO_3.bits.ratio7;
    unsigned int ratio8 = vpss_reg->VPSS_SNR_EDGE_RATIO_3.bits.ratio8;
    unsigned int edge1 = vpss_reg->VPSS_SNR_EDGE_STR.bits.edge1;
    unsigned int edge2 = vpss_reg->VPSS_SNR_EDGE_STR.bits.edge2;
    unsigned int edge3 = vpss_reg->VPSS_SNR_EDGE_STR.bits.edge3;

    unsigned int cb_begin1 = vpss_reg->VPSS_SNR_CBCR_W1.bits.cb_begin1;
    unsigned int cr_begin1 = vpss_reg->VPSS_SNR_CBCR_W1.bits.cr_begin1;
    unsigned int cb_end1 = vpss_reg->VPSS_SNR_CBCR_W1.bits.cb_end1;
    unsigned int cr_end1 = vpss_reg->VPSS_SNR_CBCR_W1.bits.cr_end1;

    unsigned int cb_begin2 = vpss_reg->VPSS_SNR_CBCR_W2.bits.cb_begin2;
    unsigned int cr_begin2 = vpss_reg->VPSS_SNR_CBCR_W2.bits.cr_begin2;
    unsigned int cb_end2 = vpss_reg->VPSS_SNR_CBCR_W2.bits.cb_end2;
    unsigned int cr_end2 = vpss_reg->VPSS_SNR_CBCR_W2.bits.cr_end2;

    unsigned int regdrstrenth = vpss_reg->VPSS_DR_THR.bits.regdrstrenth;

    unsigned int lswstrlut00 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut00;
    unsigned int lswstrlut10 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut10;
    unsigned int lswstrlut20 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut20;
    unsigned int lswstrlut30 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut30;
    unsigned int lswstrlut40 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut40;
    unsigned int lswstrlut50 = vpss_reg->VPSS_DRLSWSTRLUT0.bits.lswstrlut50;
    unsigned int lswstrlut01 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut01;
    unsigned int lswstrlut11 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut11;
    unsigned int lswstrlut21 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut21;
    unsigned int lswstrlut31 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut31;
    unsigned int lswstrlut41 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut41;
    unsigned int lswstrlut51 = vpss_reg->VPSS_DRLSWSTRLUT1.bits.lswstrlut51;
    unsigned int lswstrlut02 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut02;
    unsigned int lswstrlut12 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut12;
    unsigned int lswstrlut22 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut22;
    unsigned int lswstrlut32 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut32;
    unsigned int lswstrlut42 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut42;
    unsigned int lswstrlut52 = vpss_reg->VPSS_DRLSWSTRLUT2.bits.lswstrlut52;
    unsigned int lswstrlut03 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut03;
    unsigned int lswstrlut13 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut13;
    unsigned int lswstrlut23 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut23;
    unsigned int lswstrlut33 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut33;
    unsigned int lswstrlut43 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut43;
    unsigned int lswstrlut53 = vpss_reg->VPSS_DRLSWSTRLUT3.bits.lswstrlut53;
    unsigned int lswstrlut04 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut04;
    unsigned int lswstrlut14 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut14;
    unsigned int lswstrlut24 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut24;
    unsigned int lswstrlut34 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut34;
    unsigned int lswstrlut44 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut44;
    unsigned int lswstrlut54 = vpss_reg->VPSS_DRLSWSTRLUT4.bits.lswstrlut54;
    unsigned int lswstrlut05 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut05;
    unsigned int lswstrlut15 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut15;
    unsigned int lswstrlut25 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut25;
    unsigned int lswstrlut35 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut35;
    unsigned int lswstrlut45 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut45;
    unsigned int lswstrlut55 = vpss_reg->VPSS_DRLSWSTRLUT5.bits.lswstrlut55;
    unsigned int lswstrlut06 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut06;
    unsigned int lswstrlut16 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut16;
    unsigned int lswstrlut26 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut26;
    unsigned int lswstrlut36 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut36;
    unsigned int lswstrlut46 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut46;
    unsigned int lswstrlut56 = vpss_reg->VPSS_DRLSWSTRLUT6.bits.lswstrlut56;
    unsigned int lswstrlut07 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut07;
    unsigned int lswstrlut17 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut17;
    unsigned int lswstrlut27 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut27;
    unsigned int lswstrlut37 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut37;
    unsigned int lswstrlut47 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut47;
    unsigned int lswstrlut57 = vpss_reg->VPSS_DRLSWSTRLUT7.bits.lswstrlut57;
    unsigned int lswstrlut08 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut08;
    unsigned int lswstrlut18 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut18;
    unsigned int lswstrlut28 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut28;
    unsigned int lswstrlut38 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut38;
    unsigned int lswstrlut48 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut48;
    unsigned int lswstrlut58 = vpss_reg->VPSS_DRLSWSTRLUT8.bits.lswstrlut58;
    unsigned int lrwstrlut00 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut00;
    unsigned int lrwstrlut10 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut10;
    unsigned int lrwstrlut20 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut20;
    unsigned int lrwstrlut30 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut30;
    unsigned int lrwstrlut40 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut40;
    unsigned int lrwstrlut50 = vpss_reg->VPSS_DRLRWSTRLUT0.bits.lrwstrlut50;
    unsigned int lrwstrlut01 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut01;
    unsigned int lrwstrlut11 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut11;
    unsigned int lrwstrlut21 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut21;
    unsigned int lrwstrlut31 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut31;
    unsigned int lrwstrlut41 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut41;
    unsigned int lrwstrlut51 = vpss_reg->VPSS_DRLRWSTRLUT1.bits.lrwstrlut51;
    unsigned int lrwstrlut02 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut02;
    unsigned int lrwstrlut12 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut12;
    unsigned int lrwstrlut22 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut22;
    unsigned int lrwstrlut32 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut32;
    unsigned int lrwstrlut42 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut42;
    unsigned int lrwstrlut52 = vpss_reg->VPSS_DRLRWSTRLUT2.bits.lrwstrlut52;
    unsigned int lrwstrlut03 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut03;
    unsigned int lrwstrlut13 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut13;
    unsigned int lrwstrlut23 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut23;
    unsigned int lrwstrlut33 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut33;
    unsigned int lrwstrlut43 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut43;
    unsigned int lrwstrlut53 = vpss_reg->VPSS_DRLRWSTRLUT3.bits.lrwstrlut53;
    unsigned int lrwstrlut04 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut04;
    unsigned int lrwstrlut14 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut14;
    unsigned int lrwstrlut24 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut24;
    unsigned int lrwstrlut34 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut34;
    unsigned int lrwstrlut44 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut44;
    unsigned int lrwstrlut54 = vpss_reg->VPSS_DRLRWSTRLUT4.bits.lrwstrlut54;
    unsigned int lrwstrlut05 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut05;
    unsigned int lrwstrlut15 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut15;
    unsigned int lrwstrlut25 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut25;
    unsigned int lrwstrlut35 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut35;
    unsigned int lrwstrlut45 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut45;
    unsigned int lrwstrlut55 = vpss_reg->VPSS_DRLRWSTRLUT5.bits.lrwstrlut55;
    unsigned int lrwstrlut06 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut06;
    unsigned int lrwstrlut16 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut16;
    unsigned int lrwstrlut26 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut26;
    unsigned int lrwstrlut36 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut36;
    unsigned int lrwstrlut46 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut46;
    unsigned int lrwstrlut56 = vpss_reg->VPSS_DRLRWSTRLUT6.bits.lrwstrlut56;
    unsigned int lrwstrlut07 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut07;
    unsigned int lrwstrlut17 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut17;
    unsigned int lrwstrlut27 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut27;
    unsigned int lrwstrlut37 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut37;
    unsigned int lrwstrlut47 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut47;
    unsigned int lrwstrlut57 = vpss_reg->VPSS_DRLRWSTRLUT7.bits.lrwstrlut57;
    unsigned int lrwstrlut08 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut08;
    unsigned int lrwstrlut18 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut18;
    unsigned int lrwstrlut28 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut28;
    unsigned int lrwstrlut38 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut38;
    unsigned int lrwstrlut48 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut48;
    unsigned int lrwstrlut58 = vpss_reg->VPSS_DRLRWSTRLUT8.bits.lrwstrlut58;
    unsigned int dr_lswadjlut0 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut0;
    unsigned int dr_lswadjlut1 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut1;
    unsigned int dr_lswadjlut2 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT0.bits.dr_lswadjlut2;
    unsigned int dr_lswadjlut3 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut3;
    unsigned int dr_lswadjlut4 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut4;
    unsigned int dr_lswadjlut5 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT1.bits.dr_lswadjlut5;
    unsigned int dr_lswadjlut6 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut6;
    unsigned int dr_lswadjlut7 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut7;
    unsigned int dr_lswadjlut8 = vpss_reg->VPSS_DRLSWSTRADJUSTLUT2.bits.dr_lswadjlut8;
    unsigned int dr_lrwadjlut0 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut0;
    unsigned int dr_lrwadjlut1 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut1;
    unsigned int dr_lrwadjlut2 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT0.bits.dr_lrwadjlut2;
    unsigned int dr_lrwadjlut3 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut3;
    unsigned int dr_lrwadjlut4 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut4;
    unsigned int dr_lrwadjlut5 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT1.bits.dr_lrwadjlut5;
    unsigned int dr_lrwadjlut6 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut6;
    unsigned int dr_lrwadjlut7 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut7;
    unsigned int dr_lrwadjlut8 = vpss_reg->VPSS_DRLRWSTRADJUSTLUT2.bits.dr_lrwadjlut8;

    unsigned int dr_angdifflut0 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut0;
    unsigned int dr_angdifflut1 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut1;
    unsigned int dr_angdifflut2 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut2;
    unsigned int dr_angdifflut3 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut3;
    unsigned int dr_angdifflut4 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut4;
    unsigned int dr_angdifflut5 = vpss_reg->VPSS_DRANGLESTRLUT1_0.bits.dr_angdifflut5;
    unsigned int dr_angdifflut6 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut6;
    unsigned int dr_angdifflut7 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut7;
    unsigned int dr_angdifflut8 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut8;
    unsigned int dr_angdifflut9 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut9;
    unsigned int dr_angdifflut10 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut10;
    unsigned int dr_angdifflut11 = vpss_reg->VPSS_DRANGLESTRLUT1_1.bits.dr_angdifflut11;
    unsigned int dr_angdifflut12 = vpss_reg->VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut12;
    unsigned int dr_angdifflut13 = vpss_reg->VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut13;
    unsigned int dr_angdifflut14 = vpss_reg->VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut14;
    unsigned int dr_angdifflut15 = vpss_reg->VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut15;
    unsigned int dr_angdifflut16 = vpss_reg->VPSS_DRANGLESTRLUT1_2.bits.dr_angdifflut16;
    unsigned int dr_angminlut0 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut0;
    unsigned int dr_angminlut1 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut1;
    unsigned int dr_angminlut2 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut2;
    unsigned int dr_angminlut3 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut3;
    unsigned int dr_angminlut4 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut4;
    unsigned int dr_angminlut5 = vpss_reg->VPSS_DRANGLESTRLUT2_0.bits.dr_angminlut5;
    unsigned int dr_angminlut6 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut6;
    unsigned int dr_angminlut7 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut7;
    unsigned int dr_angminlut8 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut8;
    unsigned int dr_angminlut9 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut9;
    unsigned int dr_angminlut10 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut10;
    unsigned int dr_angminlut11 = vpss_reg->VPSS_DRANGLESTRLUT2_1.bits.dr_angminlut11;
    unsigned int dr_angminlut12 = vpss_reg->VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut12;
    unsigned int dr_angminlut13 = vpss_reg->VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut13;
    unsigned int dr_angminlut14 = vpss_reg->VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut14;
    unsigned int dr_angminlut15 = vpss_reg->VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut15;
    unsigned int dr_angminlut16 = vpss_reg->VPSS_DRANGLESTRLUT2_2.bits.dr_angminlut16;

    unsigned int vpss_fmtc_demo_offset = vpss_reg->VPSS_FMTC_GAMMA_CSC_CTRL.bits.vpss_fmtc_demo_offset;


    unsigned int mcnr_meds_en = vpss_reg->VPSS_TNR_CONTRL.bits.mcnr_meds_en;

    unsigned int motion_mode = vpss_reg->VPSS_TNR_CONTRL.bits.motion_mode;

    unsigned int meanyadjshift = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.meanyadjshift;
    unsigned int meancadjshift = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.meancadjshift;
    unsigned int ymotioncalcmode = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.ymotioncalcmode;
    unsigned int cmotioncalcmode = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.cmotioncalcmode;

    unsigned int alpha1 = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.alpha1;
    unsigned int alpha2 = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.alpha2;

    signed int ymdcore = bit_conv(vpss_reg->VPSS_TNR_MAMD_GAIN.bits.ymdcore, 6);
    signed int cmdcore = bit_conv(vpss_reg->VPSS_TNR_MAMD_GAIN.bits.cmdcore, 6);
    unsigned int noisedetecten = vpss_reg->VPSS_TNR_MAND_CTRL.bits.noisedetecten;

    unsigned int motionestimateen = vpss_reg->VPSS_TNR_MAME_CTRL.bits.motionestimateen;

    unsigned int adj_mv_max = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_mv_max;
    unsigned int adj_mv_min = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_mv_min;
    unsigned int adj_0mv_min = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_0mv_min;
    unsigned int adj_xmv_min = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_xmv_min;
    unsigned int adj_0mv_max = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_0mv_max;
    unsigned int adj_xmv_max = vpss_reg->VPSS_TNR_MAME_MV_THD.bits.adj_xmv_max;

    unsigned int cbbegin1 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbbegin1;
    unsigned int crbegin1 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crbegin1;
    unsigned int cbend1 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbend1;
    unsigned int crend1 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crend1;
    unsigned int cbbegin2 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbbegin2;
    unsigned int crbegin2 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crbegin2;
    unsigned int cbend2 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbend2;
    unsigned int crend2 = vpss_reg->VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crend2;

    signed int ymotioncore = bit_conv(vpss_reg->VPSS_TNR_MAMC_MAP.bits.ymotioncore, 6);

    signed int cmotioncore = bit_conv(vpss_reg->VPSS_TNR_MAMC_MAP.bits.cmotioncore, 6);

    HI_U32 VC1_IN_WIDTH      = imgwidth;
    HI_U32 VC1_IN_HEIGHT     = (bfield ? (imgheight / 2) : imgheight);
    HI_U32 VC1_IN_FORMAT     = ((in_format == 0x1 || in_format == 0x6 || in_format == 0xb || in_format == 0xc || in_format == 0xd) ? 1 : 0);
    HI_U32 VC1_OUT_WIDTH     = VC1_IN_WIDTH;
    HI_U32 VC1_OUT_HEIGHT    = VC1_IN_HEIGHT;
    HI_U32 VC1_OUT_FORMAT    = VC1_IN_FORMAT;
    HI_U32 TNR_IN_WIDTH      = VC1_OUT_WIDTH;
    HI_U32 TNR_IN_HEIGHT     = VC1_OUT_HEIGHT;
    HI_U32 TNR_IN_FORMAT     = VC1_OUT_FORMAT;
    HI_U32 TNR_OUT_WIDTH     = TNR_IN_WIDTH;
    HI_U32 TNR_OUT_HEIGHT    = TNR_IN_HEIGHT;
    HI_U32 TNR_OUT_FORMAT    = TNR_IN_FORMAT;
    HI_U32 DEI_IN_WIDTH      = TNR_OUT_WIDTH;
    HI_U32 DEI_IN_HEIGHT     = TNR_OUT_HEIGHT;
    HI_U32 DEI_IN_FORMAT     = TNR_OUT_FORMAT;
    HI_U32 DEI_OUT_WIDTH     = DEI_IN_WIDTH;
    HI_U32 DEI_OUT_HEIGHT    = (bfield ? (dei_en ? imgheight : DEI_IN_HEIGHT) : imgheight);
    HI_U32 DEI_OUT_FORMAT    = DEI_IN_FORMAT;
    HI_U32 SNR_IN_WIDTH      = DEI_OUT_WIDTH;
    HI_U32 SNR_IN_HEIGHT     = DEI_OUT_HEIGHT;
    HI_U32 SNR_IN_FORMAT     = DEI_OUT_FORMAT;
    HI_U32 SNR_OUT_WIDTH     = SNR_IN_WIDTH;
    HI_U32 SNR_OUT_HEIGHT    = SNR_IN_HEIGHT;
    HI_U32 SNR_OUT_FORMAT    = SNR_IN_FORMAT;
    HI_U32 FMTC_IN_WIDTH     = SNR_OUT_WIDTH;
    HI_U32 FMTC_IN_HEIGHT    = SNR_OUT_HEIGHT;
    HI_U32 FMTC_IN_FORMAT    = SNR_OUT_FORMAT;
    HI_U32 FMTC_OUT_WIDTH    = FMTC_IN_WIDTH;
    HI_U32 FMTC_OUT_HEIGHT   = FMTC_IN_HEIGHT;
    HI_U32 FMTC_OUT_FORMAT   = FMTC_IN_FORMAT;
    HI_U32 VHD0_CROP_IN_WIDTH = FMTC_OUT_WIDTH;
    HI_U32 VHD0_CROP_IN_HEIGHT = FMTC_OUT_HEIGHT;
    //   HI_U32 VHD0_CROP_IN_FORMAT= FMTC_OUT_FORMAT;
    HI_U32 VHD0_CROP_OUT_WIDTH = (vhd0_crop_en) ? vhd0_crop_width : VHD0_CROP_IN_WIDTH;
    HI_U32 VHD0_CROP_OUT_HEIGHT = (vhd0_crop_en) ? vhd0_crop_height : VHD0_CROP_IN_HEIGHT;
    // HI_U32 VHD0_CROP_OUT_FORMAT= VHD0_CROP_IN_FORMAT;
    HI_U32 VHD0_ZME_IN_WIDTH = VHD0_CROP_OUT_WIDTH;
    HI_U32 VHD0_ZME_IN_HEIGHT = VHD0_CROP_OUT_HEIGHT;
    //   HI_U32 VHD0_ZME_IN_FORMAT= VHD0_CROP_OUT_FORMAT;
    HI_U32 VHD0_ZME_OUT_WIDTH = (zme_vhd0_en) ? vhd0_zme_ow : VHD0_ZME_IN_WIDTH;
    HI_U32 VHD0_ZME_OUT_HEIGHT = (zme_vhd0_en) ? vhd0_zme_oh : VHD0_ZME_IN_HEIGHT;
    //  HI_U32 VHD0_ZME_OUT_FORMAT= (zme_vhd0_en)?zme_out_fmt:VHD0_ZME_IN_FORMAT;
    HI_U32 VHD0_LBA_IN_WIDTH = VHD0_ZME_OUT_WIDTH;
    HI_U32 VHD0_LBA_IN_HEIGHT = VHD0_ZME_OUT_HEIGHT;
    // HI_U32 VHD0_LBA_IN_FORMAT= VHD0_ZME_OUT_FORMAT;
    //    HI_U32 VHD0_LBA_OUT_WIDTH= (vhd0_lba_en)?vhd0_lba_width:VHD0_LBA_IN_WIDTH;
    //    HI_U32 VHD0_LBA_OUT_HEIGHT= (vhd0_lba_en)?vhd0_lba_height:VHD0_LBA_IN_HEIGHT;
    //    HI_U32 VHD0_LBA_OUT_FORMAT= VHD0_LBA_IN_FORMAT;


    /*****************************/
    //   Gen From Constraint File
    /*****************************/
    if (nx2_vc1_en == 1)
    {
        VPSS_ASSERT((VC1_IN_WIDTH & 0xf) == 0xf);
        VPSS_ASSERT((VC1_IN_HEIGHT & 0xf) == 0xf);
        VPSS_ASSERT(VC1_IN_WIDTH >= 63 && VC1_IN_WIDTH <= 1919);
        VPSS_ASSERT(VC1_IN_HEIGHT >= 63 && VC1_IN_HEIGHT <= 1919);
        VPSS_ASSERT(VC1_IN_FORMAT == 0);
    }
    if (tnr_en == 1)
    {
        if (TNR_IN_FORMAT == YUV420 && bfield == 1)
        {
            VPSS_ASSERT((TNR_IN_HEIGHT & 0x1) == 1);
        }
        VPSS_ASSERT(TNR_IN_WIDTH >= 63 && TNR_IN_WIDTH <= 1919);
        VPSS_ASSERT(TNR_IN_HEIGHT >= 63 && TNR_IN_HEIGHT <= 1079);
        VPSS_ASSERT((TNR_IN_WIDTH & 0x1) == 1);
        VPSS_ASSERT((TNR_IN_HEIGHT & 0x1) == 1);
        if (mcnr_meds_en == 0)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 959);
        }
        if (mcnr_meds_en == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 255);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motionestimateen == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 127);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (noisedetecten == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motion_mode == 0)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motion_mode == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
            VPSS_ASSERT(TNR_IN_FORMAT == YUV422);
        }
        if (motion_mode == 2)
        {
            VPSS_ASSERT(TNR_IN_WIDTH > 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        //VPSS_ASSERT(ymotioncalcmode==0&&cmotioncalcmode==0);
        VPSS_ASSERT(crbegin1 <= crend1);
        VPSS_ASSERT(cbbegin1 <= cbend1);
        VPSS_ASSERT(crbegin2 <= crend2);
        VPSS_ASSERT(cbbegin2 <= cbend2);
        VPSS_ASSERT(meanyadjshift >= 0 && meanyadjshift <= 6);
        VPSS_ASSERT(meancadjshift >= 0 && meancadjshift <= 6);
        VPSS_ASSERT(alpha1 >= 0 && alpha1 <= 4);
        VPSS_ASSERT(alpha2 >= 0 && alpha2 <= 4);
        VPSS_ASSERT(adj_mv_max >= 16 && adj_mv_max <= 31);
        VPSS_ASSERT(adj_mv_min >= 0 && adj_mv_min <= 16);
        VPSS_ASSERT(adj_0mv_min >= 0 && adj_0mv_min <= 16);
        VPSS_ASSERT(adj_0mv_max >= 0 && adj_0mv_max <= 16);
        VPSS_ASSERT(adj_xmv_min >= 0 && adj_xmv_min <= 16);
        VPSS_ASSERT(adj_xmv_max >= 0 && adj_xmv_max <= 16);
        VPSS_ASSERT(ymdcore >= -32 && ymdcore <= 31);
        VPSS_ASSERT(cmdcore >= -32 && cmdcore <= 31);
        VPSS_ASSERT(ymotioncore >= -32 && ymotioncore <= 31);
        VPSS_ASSERT(cmotioncore >= -32 && cmotioncore <= 31);
    }
    if (dei_en == 1)
    {
        VPSS_ASSERT(DEI_IN_WIDTH >= 127 && DEI_IN_WIDTH <= 1919);
        VPSS_ASSERT((DEI_IN_WIDTH & 0x1) == 0x1);
        VPSS_ASSERT(DEI_IN_HEIGHT >= 31 && DEI_IN_HEIGHT <= 543);
        VPSS_ASSERT(DEI_IN_FORMAT == YUV422 || (DEI_IN_HEIGHT & 0x1) == 0x1);
        VPSS_ASSERT(k_max_core_mcw == 8);
        VPSS_ASSERT(k_max_dif_mcw == 8);
        VPSS_ASSERT(k1_max_mag_mcw == 8);
        VPSS_ASSERT(k0_max_mag_mcw == 8);
        VPSS_ASSERT(k_tbdif_mcw == 15);
        VPSS_ASSERT(k_tbmag_mcw == 0);
        VPSS_ASSERT(gain_lpf_dw == 15);
        VPSS_ASSERT(core_bhvdif_dw == 5);
        VPSS_ASSERT(k_bhvdif_dw == 64);
        VPSS_ASSERT(b_bhvdif_dw == 0);
        VPSS_ASSERT(b_hvdif_dw == 0);
        VPSS_ASSERT(core_hvdif_dw == 16);
        VPSS_ASSERT(core_mv_dw == -2);
        VPSS_ASSERT(b_mv_dw == 56);
        VPSS_ASSERT(x0_mv_dw == 8);
        VPSS_ASSERT(k0_mv_dw == 16);
        VPSS_ASSERT(g0_mv_dw == 32);
        VPSS_ASSERT(k1_mv_dw == 64);
        VPSS_ASSERT(gain_up_mclpfv == 16);
        VPSS_ASSERT(gain_dn_mclpfv == 16);
        VPSS_ASSERT(gain_mclpfh == 16);
        VPSS_ASSERT(g_pxlmag_mcw == 0);
        VPSS_ASSERT(submv_sadchk_en == 0);
        VPSS_ASSERT(stinfo_stop == 0);
        VPSS_ASSERT(die_c_mode == 1);
        VPSS_ASSERT(die_l_mode == 1);
        VPSS_ASSERT(recmode_frmfld_blend_mode == 0);
        VPSS_ASSERT(core_mag_rgmvls >= -64 && core_mag_rgmvls <= 63);
        VPSS_ASSERT(force_mvx >= -63 && force_mvx <= 63);
        VPSS_ASSERT(r0_mc >= 0 && r0_mc <= DEI_IN_HEIGHT);
        VPSS_ASSERT(c0_mc >= 0 && c0_mc <= DEI_IN_WIDTH);
        //VPSS_ASSERT(r1_mc>=0&&r1_mc<=DEI_IN_HEIGHT&&r1_mc>=r0_mc);
        //VPSS_ASSERT(c1_mc>=0&&c1_mc<=DEI_IN_WIDTH&&c1_mc>=c0_mc);
        VPSS_ASSERT(mcmvrange >= 0 && mcmvrange <= 32);
        VPSS_ASSERT(mcstartr >= 0 && mcstartr <= 255 && mcstartr + mcendr <= DEI_IN_HEIGHT);
        VPSS_ASSERT(mcstartc >= 0 && mcstartc <= 255 && mcstartc + mcendc <= DEI_IN_WIDTH);
        VPSS_ASSERT(mcendr >= 0 && mcendr <= 255 && mcstartr + mcendr <= DEI_IN_HEIGHT);
        VPSS_ASSERT(mcendc >= 0 && mcendc <= 255 && mcstartc + mcendc <= DEI_IN_WIDTH);
        VPSS_ASSERT(movethdh >= 0 && movethdh <= 32);
        VPSS_ASSERT(movethdl >= 0 && movethdl <= 32);
        VPSS_ASSERT(movecorig >= 0 && movecorig <= 32);
        VPSS_ASSERT(movegain >= 0 && movegain <= 32);
        VPSS_ASSERT(demo_mode_l >= 0 && demo_mode_l <= 2);
        VPSS_ASSERT(demo_mode_r >= 0 && demo_mode_r <= 2);
        VPSS_ASSERT(demo_border >= 0 && demo_border <= DEI_IN_WIDTH);
    }
    if (nx2_vc1_en == 1)
    {
        VPSS_ASSERT((VC1_IN_WIDTH & 0xf) == 0xf);
        VPSS_ASSERT((VC1_IN_HEIGHT & 0xf) == 0xf);
        VPSS_ASSERT(VC1_IN_WIDTH >= 31 && VC1_IN_WIDTH <= 1919);
        VPSS_ASSERT(VC1_IN_HEIGHT >= 31 && VC1_IN_HEIGHT <= 1079);
        VPSS_ASSERT(VC1_IN_FORMAT == 0);
    }
    if (tnr_en == 1)
    {
        if (TNR_IN_FORMAT == YUV420 && bfield == 1)
        {
            VPSS_ASSERT((TNR_IN_HEIGHT & 0x1) == 1);
        }
        VPSS_ASSERT(TNR_IN_WIDTH >= 63 && TNR_IN_WIDTH <= 1919);
        VPSS_ASSERT(TNR_IN_HEIGHT >= 31 && TNR_IN_HEIGHT <= 1079);
        VPSS_ASSERT((TNR_IN_WIDTH & 0x1) == 1);
        VPSS_ASSERT((TNR_IN_HEIGHT & 0x1) == 1);
        if (mcnr_meds_en == 0)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 959);
        }
        if (mcnr_meds_en == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 255);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motionestimateen == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 127);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (noisedetecten == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motion_mode == 0)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        if (motion_mode == 1)
        {
            VPSS_ASSERT(TNR_IN_WIDTH >= 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
            VPSS_ASSERT(TNR_IN_FORMAT == YUV422);
        }
        if (motion_mode == 2)
        {
            VPSS_ASSERT(TNR_IN_WIDTH > 63);
            VPSS_ASSERT(TNR_IN_WIDTH <= 1919);
        }
        //VPSS_ASSERT(ymotioncalcmode==0&&cmotioncalcmode==0);
        VPSS_ASSERT(crbegin1 <= crend1);
        VPSS_ASSERT(cbbegin1 <= cbend1);
        VPSS_ASSERT(crbegin2 <= crend2);
        VPSS_ASSERT(cbbegin2 <= cbend2);
        VPSS_ASSERT(meanyadjshift >= 0 && meanyadjshift <= 6);
        VPSS_ASSERT(meancadjshift >= 0 && meancadjshift <= 6);
        VPSS_ASSERT(alpha1 >= 0 && alpha1 <= 4);
        VPSS_ASSERT(alpha2 >= 0 && alpha2 <= 4);
        VPSS_ASSERT(adj_mv_max >= 16 && adj_mv_max <= 31);
        VPSS_ASSERT(adj_mv_min >= 0 && adj_mv_min <= 16);
        VPSS_ASSERT(adj_0mv_min >= 0 && adj_0mv_min <= 16);
        VPSS_ASSERT(adj_0mv_max >= 0 && adj_0mv_max <= 16);
        VPSS_ASSERT(adj_xmv_min >= 0 && adj_xmv_min <= 16);
        VPSS_ASSERT(adj_xmv_max >= 0 && adj_xmv_max <= 16);
        VPSS_ASSERT(ymdcore >= -32 && ymdcore <= 31);
        VPSS_ASSERT(cmdcore >= -32 && cmdcore <= 31);
        VPSS_ASSERT(ymotioncore >= -32 && ymotioncore <= 31);
        VPSS_ASSERT(cmotioncore >= -32 && cmotioncore <= 31);
    }
    if (dei_en == 1)
    {
        VPSS_ASSERT(DEI_IN_WIDTH >= 127 && DEI_IN_WIDTH <= 1919);
        VPSS_ASSERT((DEI_IN_WIDTH & 0x1) == 0x1);
        VPSS_ASSERT(DEI_IN_HEIGHT >= 31 && DEI_IN_HEIGHT <= 543);
        VPSS_ASSERT(DEI_IN_FORMAT == YUV422 || (DEI_IN_HEIGHT & 0x1) == 0x1);
        VPSS_ASSERT(k_max_core_mcw == 8);
        VPSS_ASSERT(k_max_dif_mcw == 8);
        VPSS_ASSERT(k1_max_mag_mcw == 8);
        VPSS_ASSERT(k0_max_mag_mcw == 8);
        VPSS_ASSERT(k_tbdif_mcw == 15);
        VPSS_ASSERT(k_tbmag_mcw == 0);
        VPSS_ASSERT(gain_lpf_dw == 15);
        VPSS_ASSERT(core_bhvdif_dw == 5);
        VPSS_ASSERT(k_bhvdif_dw == 64);
        VPSS_ASSERT(b_bhvdif_dw == 0);
        VPSS_ASSERT(b_hvdif_dw == 0);
        VPSS_ASSERT(core_hvdif_dw == 16);
        VPSS_ASSERT(core_mv_dw == -2);
        VPSS_ASSERT(b_mv_dw == 56);
        VPSS_ASSERT(x0_mv_dw == 8);
        VPSS_ASSERT(k0_mv_dw == 16);
        VPSS_ASSERT(g0_mv_dw == 32);
        VPSS_ASSERT(k1_mv_dw == 64);
        VPSS_ASSERT(gain_up_mclpfv == 16);
        VPSS_ASSERT(gain_dn_mclpfv == 16);
        VPSS_ASSERT(gain_mclpfh == 16);
        VPSS_ASSERT(g_pxlmag_mcw == 0);
        //VPSS_ASSERT(submv_sadchk_en==0);
        VPSS_ASSERT(stinfo_stop == 0);
        VPSS_ASSERT(die_c_mode == 1);
        VPSS_ASSERT(die_l_mode == 1);
        VPSS_ASSERT(recmode_frmfld_blend_mode == 0);
        VPSS_ASSERT(core_mag_rgmvls >= -64 && core_mag_rgmvls <= 63);
        VPSS_ASSERT(force_mvx >= -63 && force_mvx <= 63);
        VPSS_ASSERT(r0_mc >= 0 && r0_mc <= DEI_IN_HEIGHT);
        VPSS_ASSERT(c0_mc >= 0 && c0_mc <= DEI_IN_WIDTH);
        //VPSS_ASSERT(r1_mc>=0&&r1_mc<=DEI_IN_HEIGHT&&r1_mc>=r0_mc);
        //VPSS_ASSERT(c1_mc>=0&&c1_mc<=DEI_IN_WIDTH&&c1_mc>=c0_mc);
        VPSS_ASSERT(mcmvrange >= 0 && mcmvrange <= 32);
        VPSS_ASSERT(mcstartr >= 0 && mcstartr <= 255 && mcstartr + mcendr <= DEI_IN_HEIGHT);
        VPSS_ASSERT(mcstartc >= 0 && mcstartc <= 255 && mcstartc + mcendc <= DEI_IN_WIDTH);
        VPSS_ASSERT(mcendr >= 0 && mcendr <= 255 && mcstartr + mcendr <= DEI_IN_HEIGHT);
        VPSS_ASSERT(mcendc >= 0 && mcendc <= 255 && mcstartc + mcendc <= DEI_IN_WIDTH);
        VPSS_ASSERT(movethdh >= 0 && movethdh <= 32);
        VPSS_ASSERT(movethdl >= 0 && movethdl <= 32);
        VPSS_ASSERT(movecorig >= 0 && movecorig <= 32);
        VPSS_ASSERT(movegain >= 0 && movegain <= 32);
        VPSS_ASSERT(demo_mode_l >= 0 && demo_mode_l <= 2);
        VPSS_ASSERT(demo_mode_r >= 0 && demo_mode_r <= 2);
        VPSS_ASSERT(demo_border >= 0 && demo_border <= DEI_IN_WIDTH + 1);
        VPSS_ASSERT(min_north_strength >= -32768 && min_north_strength <= 32767);
        VPSS_ASSERT(DEI_BIT_DEPTH ? (bc1_max_dz >= 0 && bc1_max_dz <= 63) : (bc1_max_dz >= 0 && bc1_max_dz <= 255));
        VPSS_ASSERT(DEI_BIT_DEPTH ? (bc2_max_dz >= 0 && bc2_max_dz <= 63) : (bc2_max_dz >= 0 && bc2_max_dz <= 255));
        VPSS_ASSERT(bc_gain >= 0 && bc_gain <= 64);
        VPSS_ASSERT(fld_motion_thd_low >= 0 && fld_motion_thd_low <= 255 && fld_motion_thd_low <= fld_motion_thd_high);
        VPSS_ASSERT(fld_motion_thd_high >= 0 && fld_motion_thd_high <= 255 && fld_motion_thd_low <= fld_motion_thd_high);
        VPSS_ASSERT(fld_motion_curve_slope >= -32 && fld_motion_curve_slope <= 31);
        VPSS_ASSERT(motion_diff_thd_0 <= motion_diff_thd_1);
        VPSS_ASSERT(motion_diff_thd_1 <= motion_diff_thd_2);
        VPSS_ASSERT(motion_diff_thd_2 <= motion_diff_thd_3);
        VPSS_ASSERT(motion_diff_thd_3 <= motion_diff_thd_4);
        VPSS_ASSERT(motion_diff_thd_4 <= motion_diff_thd_5);
        VPSS_ASSERT(min_motion_iir_ratio >= 0 && min_motion_iir_ratio <= 64 && min_motion_iir_ratio <= max_motion_iir_ratio);
        VPSS_ASSERT(max_motion_iir_ratio >= 0 && max_motion_iir_ratio <= 64 && min_motion_iir_ratio <= max_motion_iir_ratio);
        VPSS_ASSERT(motion_iir_curve_slope_0 >= -32 && motion_iir_curve_slope_0 <= 31);
        VPSS_ASSERT(motion_iir_curve_slope_1 >= -32 && motion_iir_curve_slope_1 <= 31);
        VPSS_ASSERT(motion_iir_curve_slope_2 >= -32 && motion_iir_curve_slope_2 <= 31);
        VPSS_ASSERT(motion_iir_curve_slope_3 >= -32 && motion_iir_curve_slope_3 <= 31);
        VPSS_ASSERT(motion_iir_curve_ratio_1 == CLIP3(0, 127, motion_iir_curve_ratio_0 + ((motion_iir_curve_slope_0 * (motion_diff_thd_1 - motion_diff_thd_0) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(motion_iir_curve_ratio_2 == CLIP3(0, 127, motion_iir_curve_ratio_1 + ((motion_iir_curve_slope_1 * (motion_diff_thd_2 - motion_diff_thd_1) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(motion_iir_curve_ratio_3 == CLIP3(0, 127, motion_iir_curve_ratio_2 + ((motion_iir_curve_slope_2 * (motion_diff_thd_3 - motion_diff_thd_2) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(motion_iir_curve_ratio_4 == CLIP3(0, 127, motion_iir_curve_ratio_3 + ((motion_iir_curve_slope_3 * (motion_diff_thd_4 - motion_diff_thd_3) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(ppre_info_en == 1);
        VPSS_ASSERT(pre_info_en == 0);
        VPSS_ASSERT(two_four_pxl_share == 0);
        VPSS_ASSERT(frame_motion_smooth_thd0 <= frame_motion_smooth_thd1);
        VPSS_ASSERT(frame_motion_smooth_thd1 <= frame_motion_smooth_thd2);
        VPSS_ASSERT(frame_motion_smooth_thd2 <= frame_motion_smooth_thd3);
        VPSS_ASSERT(frame_motion_smooth_thd3 <= frame_motion_smooth_thd4);
        VPSS_ASSERT(frame_motion_smooth_thd4 <= frame_motion_smooth_thd5);
        VPSS_ASSERT(frame_motion_smooth_ratio_min >= 0 && frame_motion_smooth_ratio_min <= 64 && frame_motion_smooth_ratio_min <= frame_motion_smooth_ratio_max);
        VPSS_ASSERT(frame_motion_smooth_ratio_max >= 0 && frame_motion_smooth_ratio_max <= 64 && frame_motion_smooth_ratio_min <= frame_motion_smooth_ratio_max);
        VPSS_ASSERT(frame_motion_smooth_slope0 >= -32 && frame_motion_smooth_slope0 <= 31);
        VPSS_ASSERT(frame_motion_smooth_slope1 >= -32 && frame_motion_smooth_slope1 <= 31);
        VPSS_ASSERT(frame_motion_smooth_slope2 >= -32 && frame_motion_smooth_slope2 <= 31);
        VPSS_ASSERT(frame_motion_smooth_slope3 >= -32 && frame_motion_smooth_slope3 <= 31);
        VPSS_ASSERT(frame_motion_smooth_ratio1 == CLIP3(0, 127, frame_motion_smooth_ratio0 + ((frame_motion_smooth_slope0 * (frame_motion_smooth_thd1 - frame_motion_smooth_thd0) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_motion_smooth_ratio2 == CLIP3(0, 127, frame_motion_smooth_ratio1 + ((frame_motion_smooth_slope1 * (frame_motion_smooth_thd2 - frame_motion_smooth_thd1) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_motion_smooth_ratio3 == CLIP3(0, 127, frame_motion_smooth_ratio2 + ((frame_motion_smooth_slope2 * (frame_motion_smooth_thd3 - frame_motion_smooth_thd2) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_motion_smooth_ratio4 == CLIP3(0, 127, frame_motion_smooth_ratio3 + ((frame_motion_smooth_slope3 * (frame_motion_smooth_thd4 - frame_motion_smooth_thd3) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_field_blend_thd0 <= frame_field_blend_thd1);
        VPSS_ASSERT(frame_field_blend_thd1 <= frame_field_blend_thd2);
        VPSS_ASSERT(frame_field_blend_thd2 <= frame_field_blend_thd3);
        VPSS_ASSERT(frame_field_blend_thd3 <= frame_field_blend_thd4);
        VPSS_ASSERT(frame_field_blend_thd4 <= frame_field_blend_thd5);
        VPSS_ASSERT(frame_field_blend_ratio_min >= 0 && frame_field_blend_ratio_min <= 64 && frame_field_blend_ratio_min <= frame_field_blend_ratio_max);
        VPSS_ASSERT(frame_field_blend_ratio_max >= 0 && frame_field_blend_ratio_max <= 64 && frame_field_blend_ratio_min <= frame_field_blend_ratio_max);
        VPSS_ASSERT(frame_field_blend_slope0 >= -32 && frame_field_blend_slope0 <= 31);
        VPSS_ASSERT(frame_field_blend_slope1 >= -32 && frame_field_blend_slope1 <= 31);
        VPSS_ASSERT(frame_field_blend_slope2 >= -32 && frame_field_blend_slope2 <= 31);
        VPSS_ASSERT(frame_field_blend_slope3 >= -32 && frame_field_blend_slope3 <= 31);
        VPSS_ASSERT(frame_field_blend_ratio1 == CLIP3(0, 127, frame_field_blend_ratio0 + ((frame_field_blend_slope0 * (frame_field_blend_thd1 - frame_field_blend_thd0) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_field_blend_ratio2 == CLIP3(0, 127, frame_field_blend_ratio1 + ((frame_field_blend_slope1 * (frame_field_blend_thd2 - frame_field_blend_thd1) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_field_blend_ratio3 == CLIP3(0, 127, frame_field_blend_ratio2 + ((frame_field_blend_slope2 * (frame_field_blend_thd3 - frame_field_blend_thd2) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(frame_field_blend_ratio4 == CLIP3(0, 127, frame_field_blend_ratio3 + ((frame_field_blend_slope3 * (frame_field_blend_thd4 - frame_field_blend_thd3) + DEI_HALFVALUE) >> DEI_SHIFT)));
        VPSS_ASSERT(inter_diff_thd0 <= inter_diff_thd1);
        VPSS_ASSERT(inter_diff_thd1 <= inter_diff_thd2);
        VPSS_ASSERT(mc_strength_k0 >= -128 && mc_strength_k0 <= 127);
        VPSS_ASSERT(mc_strength_k1 >= -128 && mc_strength_k1 <= 127);
        VPSS_ASSERT(mc_strength_k2 >= -128 && mc_strength_k2 <= 127);
        VPSS_ASSERT(mc_strength_ming <= mc_strength_maxg);
    }
    if (snr_en == 1)
    {
        VPSS_ASSERT((SNR_IN_WIDTH >= 127) && (SNR_IN_WIDTH <= 1919) && ((SNR_IN_WIDTH & 0x1) == 1));
        if (SNR_IN_FORMAT == 1 )
        {
            VPSS_ASSERT((SNR_IN_HEIGHT >= 31) && (SNR_IN_HEIGHT <= 2047));
        }
        else
        {
            VPSS_ASSERT((SNR_IN_HEIGHT >= 31) && (SNR_IN_HEIGHT <= 2047) && ((SNR_IN_HEIGHT & 0x1) == 1));
        }
        //        VPSS_ASSERT((db_lum_h_blk_size>=4)&&(db_lum_h_blk_size<=64));
        VPSS_ASSERT((db_lum_hor_txt_win_size >= 0) && (db_lum_hor_txt_win_size <= 2));
        //VPSS_ASSERT((db_max_lum_hor_db_dist>=1)&&(db_max_lum_hor_db_dist<=12)&&(db_max_lum_hor_db_dist<=db_lum_h_blk_size/2));
        VPSS_ASSERT((db_dir_smooth_mode >= 0) && (db_dir_smooth_mode <= 2));
        VPSS_ASSERT((db_adpt_flt_mode >= 0) && (db_adpt_flt_mode <= 2));
        VPSS_ASSERT((db_adpt_delta_adj0 >= 0) && (db_adpt_delta_adj0 <= 3));
        VPSS_ASSERT((db_adpt_delta_scl >= 0) && (db_adpt_delta_scl <= 16));
        VPSS_ASSERT((db_dir_str_gain_lut_p0 >= 0) && (db_dir_str_gain_lut_p0 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p1 >= 0) && (db_dir_str_gain_lut_p1 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p2 >= 0) && (db_dir_str_gain_lut_p2 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p3 >= 0) && (db_dir_str_gain_lut_p3 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p4 >= 0) && (db_dir_str_gain_lut_p4 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p5 >= 0) && (db_dir_str_gain_lut_p5 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p6 >= 0) && (db_dir_str_gain_lut_p6 <= 8));
        VPSS_ASSERT((db_dir_str_gain_lut_p7 >= 0) && (db_dir_str_gain_lut_p7 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p0 >= 0) && (db_dir_str_lut_p0 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p1 >= 0) && (db_dir_str_lut_p1 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p2 >= 0) && (db_dir_str_lut_p2 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p3 >= 0) && (db_dir_str_lut_p3 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p4 >= 0) && (db_dir_str_lut_p4 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p5 >= 0) && (db_dir_str_lut_p5 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p6 >= 0) && (db_dir_str_lut_p6 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p7 >= 0) && (db_dir_str_lut_p7 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p8 >= 0) && (db_dir_str_lut_p8 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p9 >= 0) && (db_dir_str_lut_p9 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p10 >= 0) && (db_dir_str_lut_p10 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p11 >= 0) && (db_dir_str_lut_p11 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p12 >= 0) && (db_dir_str_lut_p12 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p13 >= 0) && (db_dir_str_lut_p13 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p14 >= 0) && (db_dir_str_lut_p14 <= 8));
        VPSS_ASSERT((db_dir_str_lut_p15 >= 0) && (db_dir_str_lut_p15 <= 8));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p0 >= 0) && (db_lum_h_str_fade_lut_p0 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p1 >= 0) && (db_lum_h_str_fade_lut_p1 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p2 >= 0) && (db_lum_h_str_fade_lut_p2 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p3 >= 0) && (db_lum_h_str_fade_lut_p3 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p4 >= 0) && (db_lum_h_str_fade_lut_p4 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p5 >= 0) && (db_lum_h_str_fade_lut_p5 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p6 >= 0) && (db_lum_h_str_fade_lut_p6 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p7 >= 0) && (db_lum_h_str_fade_lut_p7 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p8 >= 0) && (db_lum_h_str_fade_lut_p8 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p9 >= 0) && (db_lum_h_str_fade_lut_p9 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p10 >= 0) && (db_lum_h_str_fade_lut_p10 <= 7));
        VPSS_ASSERT((db_lum_h_str_fade_lut_p11 >= 0) && (db_lum_h_str_fade_lut_p11 <= 7));
        VPSS_ASSERT(regdrstrenth >= 0 && regdrstrenth <= 16);
        //VPSS_ASSERT(drdir_blend_str>=0&&drdir_blend_str<=8);
        //VPSS_ASSERT(alpha_acthvrange>=0&&alpha_acthvrange<=20460);
        //VPSS_ASSERT(dm_dir_blend_str>=0&&dm_dir_blend_str<=8);
        //VPSS_ASSERT(dm_lim_res_blend_str2>=0&&dm_lim_res_blend_str2<=8);
        //VPSS_ASSERT(dm_lim_res_blend_str1>=0&&dm_lim_res_blend_str1<=8);
        //VPSS_ASSERT(dm_limit_lsw_ratio>=2&&dm_limit_lsw_ratio<=6);
        //VPSS_ASSERT(dm_lsw_ratio>=2&&dm_lsw_ratio<=6);
        //VPSS_ASSERT(winact_limit>=0&&winact_limit<=40926);
        //VPSS_ASSERT(winact_cliplimit>=0&&winact_cliplimit<=40926);
        VPSS_ASSERT(lswstrlut00 >= 0 && lswstrlut00 <= 16);
        VPSS_ASSERT(lswstrlut10 >= 0 && lswstrlut10 <= 16);
        VPSS_ASSERT(lswstrlut20 >= 0 && lswstrlut20 <= 16);
        VPSS_ASSERT(lswstrlut30 >= 0 && lswstrlut30 <= 16);
        VPSS_ASSERT(lswstrlut40 >= 0 && lswstrlut40 <= 16);
        VPSS_ASSERT(lswstrlut50 >= 0 && lswstrlut50 <= 16);
        VPSS_ASSERT(lswstrlut01 >= 0 && lswstrlut01 <= 16);
        VPSS_ASSERT(lswstrlut11 >= 0 && lswstrlut11 <= 16);
        VPSS_ASSERT(lswstrlut21 >= 0 && lswstrlut21 <= 16);
        VPSS_ASSERT(lswstrlut31 >= 0 && lswstrlut31 <= 16);
        VPSS_ASSERT(lswstrlut41 >= 0 && lswstrlut41 <= 16);
        VPSS_ASSERT(lswstrlut51 >= 0 && lswstrlut51 <= 16);
        VPSS_ASSERT(lswstrlut02 >= 0 && lswstrlut02 <= 16);
        VPSS_ASSERT(lswstrlut12 >= 0 && lswstrlut12 <= 16);
        VPSS_ASSERT(lswstrlut22 >= 0 && lswstrlut22 <= 16);
        VPSS_ASSERT(lswstrlut32 >= 0 && lswstrlut32 <= 16);
        VPSS_ASSERT(lswstrlut42 >= 0 && lswstrlut42 <= 16);
        VPSS_ASSERT(lswstrlut52 >= 0 && lswstrlut52 <= 16);
        VPSS_ASSERT(lswstrlut03 >= 0 && lswstrlut03 <= 16);
        VPSS_ASSERT(lswstrlut13 >= 0 && lswstrlut13 <= 16);
        VPSS_ASSERT(lswstrlut23 >= 0 && lswstrlut23 <= 16);
        VPSS_ASSERT(lswstrlut33 >= 0 && lswstrlut33 <= 16);
        VPSS_ASSERT(lswstrlut43 >= 0 && lswstrlut43 <= 16);
        VPSS_ASSERT(lswstrlut53 >= 0 && lswstrlut53 <= 16);
        VPSS_ASSERT(lswstrlut04 >= 0 && lswstrlut04 <= 16);
        VPSS_ASSERT(lswstrlut14 >= 0 && lswstrlut14 <= 16);
        VPSS_ASSERT(lswstrlut24 >= 0 && lswstrlut24 <= 16);
        VPSS_ASSERT(lswstrlut34 >= 0 && lswstrlut34 <= 16);
        VPSS_ASSERT(lswstrlut44 >= 0 && lswstrlut44 <= 16);
        VPSS_ASSERT(lswstrlut54 >= 0 && lswstrlut54 <= 16);
        VPSS_ASSERT(lswstrlut05 >= 0 && lswstrlut05 <= 16);
        VPSS_ASSERT(lswstrlut15 >= 0 && lswstrlut15 <= 16);
        VPSS_ASSERT(lswstrlut25 >= 0 && lswstrlut25 <= 16);
        VPSS_ASSERT(lswstrlut35 >= 0 && lswstrlut35 <= 16);
        VPSS_ASSERT(lswstrlut45 >= 0 && lswstrlut45 <= 16);
        VPSS_ASSERT(lswstrlut55 >= 0 && lswstrlut55 <= 16);
        VPSS_ASSERT(lswstrlut06 >= 0 && lswstrlut06 <= 16);
        VPSS_ASSERT(lswstrlut16 >= 0 && lswstrlut16 <= 16);
        VPSS_ASSERT(lswstrlut26 >= 0 && lswstrlut26 <= 16);
        VPSS_ASSERT(lswstrlut36 >= 0 && lswstrlut36 <= 16);
        VPSS_ASSERT(lswstrlut46 >= 0 && lswstrlut46 <= 16);
        VPSS_ASSERT(lswstrlut56 >= 0 && lswstrlut56 <= 16);
        VPSS_ASSERT(lswstrlut07 >= 0 && lswstrlut07 <= 16);
        VPSS_ASSERT(lswstrlut17 >= 0 && lswstrlut17 <= 16);
        VPSS_ASSERT(lswstrlut27 >= 0 && lswstrlut27 <= 16);
        VPSS_ASSERT(lswstrlut37 >= 0 && lswstrlut37 <= 16);
        VPSS_ASSERT(lswstrlut47 >= 0 && lswstrlut47 <= 16);
        VPSS_ASSERT(lswstrlut57 >= 0 && lswstrlut57 <= 16);
        VPSS_ASSERT(lswstrlut08 >= 0 && lswstrlut08 <= 16);
        VPSS_ASSERT(lswstrlut18 >= 0 && lswstrlut18 <= 16);
        VPSS_ASSERT(lswstrlut28 >= 0 && lswstrlut28 <= 16);
        VPSS_ASSERT(lswstrlut38 >= 0 && lswstrlut38 <= 16);
        VPSS_ASSERT(lswstrlut48 >= 0 && lswstrlut48 <= 16);
        VPSS_ASSERT(lswstrlut58 >= 0 && lswstrlut58 <= 16);
        VPSS_ASSERT(lrwstrlut00 >= 0 && lrwstrlut00 <= 16);
        VPSS_ASSERT(lrwstrlut10 >= 0 && lrwstrlut10 <= 16);
        VPSS_ASSERT(lrwstrlut20 >= 0 && lrwstrlut20 <= 16);
        VPSS_ASSERT(lrwstrlut30 >= 0 && lrwstrlut30 <= 16);
        VPSS_ASSERT(lrwstrlut40 >= 0 && lrwstrlut40 <= 16);
        VPSS_ASSERT(lrwstrlut50 >= 0 && lrwstrlut50 <= 16);
        VPSS_ASSERT(lrwstrlut01 >= 0 && lrwstrlut01 <= 16);
        VPSS_ASSERT(lrwstrlut11 >= 0 && lrwstrlut11 <= 16);
        VPSS_ASSERT(lrwstrlut21 >= 0 && lrwstrlut21 <= 16);
        VPSS_ASSERT(lrwstrlut31 >= 0 && lrwstrlut31 <= 16);
        VPSS_ASSERT(lrwstrlut41 >= 0 && lrwstrlut41 <= 16);
        VPSS_ASSERT(lrwstrlut51 >= 0 && lrwstrlut51 <= 16);
        VPSS_ASSERT(lrwstrlut02 >= 0 && lrwstrlut02 <= 16);
        VPSS_ASSERT(lrwstrlut12 >= 0 && lrwstrlut12 <= 16);
        VPSS_ASSERT(lrwstrlut22 >= 0 && lrwstrlut22 <= 16);
        VPSS_ASSERT(lrwstrlut32 >= 0 && lrwstrlut32 <= 16);
        VPSS_ASSERT(lrwstrlut42 >= 0 && lrwstrlut42 <= 16);
        VPSS_ASSERT(lrwstrlut52 >= 0 && lrwstrlut52 <= 16);
        VPSS_ASSERT(lrwstrlut03 >= 0 && lrwstrlut03 <= 16);
        VPSS_ASSERT(lrwstrlut13 >= 0 && lrwstrlut13 <= 16);
        VPSS_ASSERT(lrwstrlut23 >= 0 && lrwstrlut23 <= 16);
        VPSS_ASSERT(lrwstrlut33 >= 0 && lrwstrlut33 <= 16);
        VPSS_ASSERT(lrwstrlut43 >= 0 && lrwstrlut43 <= 16);
        VPSS_ASSERT(lrwstrlut53 >= 0 && lrwstrlut53 <= 16);
        VPSS_ASSERT(lrwstrlut04 >= 0 && lrwstrlut04 <= 16);
        VPSS_ASSERT(lrwstrlut14 >= 0 && lrwstrlut14 <= 16);
        VPSS_ASSERT(lrwstrlut24 >= 0 && lrwstrlut24 <= 16);
        VPSS_ASSERT(lrwstrlut34 >= 0 && lrwstrlut34 <= 16);
        VPSS_ASSERT(lrwstrlut44 >= 0 && lrwstrlut44 <= 16);
        VPSS_ASSERT(lrwstrlut54 >= 0 && lrwstrlut54 <= 16);
        VPSS_ASSERT(lrwstrlut05 >= 0 && lrwstrlut05 <= 16);
        VPSS_ASSERT(lrwstrlut15 >= 0 && lrwstrlut15 <= 16);
        VPSS_ASSERT(lrwstrlut25 >= 0 && lrwstrlut25 <= 16);
        VPSS_ASSERT(lrwstrlut35 >= 0 && lrwstrlut35 <= 16);
        VPSS_ASSERT(lrwstrlut45 >= 0 && lrwstrlut45 <= 16);
        VPSS_ASSERT(lrwstrlut55 >= 0 && lrwstrlut55 <= 16);
        VPSS_ASSERT(lrwstrlut06 >= 0 && lrwstrlut06 <= 16);
        VPSS_ASSERT(lrwstrlut16 >= 0 && lrwstrlut16 <= 16);
        VPSS_ASSERT(lrwstrlut26 >= 0 && lrwstrlut26 <= 16);
        VPSS_ASSERT(lrwstrlut36 >= 0 && lrwstrlut36 <= 16);
        VPSS_ASSERT(lrwstrlut46 >= 0 && lrwstrlut46 <= 16);
        VPSS_ASSERT(lrwstrlut56 >= 0 && lrwstrlut56 <= 16);
        VPSS_ASSERT(lrwstrlut07 >= 0 && lrwstrlut07 <= 16);
        VPSS_ASSERT(lrwstrlut17 >= 0 && lrwstrlut17 <= 16);
        VPSS_ASSERT(lrwstrlut27 >= 0 && lrwstrlut27 <= 16);
        VPSS_ASSERT(lrwstrlut37 >= 0 && lrwstrlut37 <= 16);
        VPSS_ASSERT(lrwstrlut47 >= 0 && lrwstrlut47 <= 16);
        VPSS_ASSERT(lrwstrlut57 >= 0 && lrwstrlut57 <= 16);
        VPSS_ASSERT(lrwstrlut08 >= 0 && lrwstrlut08 <= 16);
        VPSS_ASSERT(lrwstrlut18 >= 0 && lrwstrlut18 <= 16);
        VPSS_ASSERT(lrwstrlut28 >= 0 && lrwstrlut28 <= 16);
        VPSS_ASSERT(lrwstrlut38 >= 0 && lrwstrlut38 <= 16);
        VPSS_ASSERT(lrwstrlut48 >= 0 && lrwstrlut48 <= 16);
        VPSS_ASSERT(lrwstrlut58 >= 0 && lrwstrlut58 <= 16);
        VPSS_ASSERT(dr_angminlut0 >= 0 && dr_angminlut0 <= 16);
        VPSS_ASSERT(dr_angminlut1 >= 0 && dr_angminlut1 <= 16);
        VPSS_ASSERT(dr_angminlut2 >= 0 && dr_angminlut2 <= 16);
        VPSS_ASSERT(dr_angminlut3 >= 0 && dr_angminlut3 <= 16);
        VPSS_ASSERT(dr_angminlut4 >= 0 && dr_angminlut4 <= 16);
        VPSS_ASSERT(dr_angminlut5 >= 0 && dr_angminlut5 <= 16);
        VPSS_ASSERT(dr_angminlut6 >= 0 && dr_angminlut6 <= 16);
        VPSS_ASSERT(dr_angminlut7 >= 0 && dr_angminlut7 <= 16);
        VPSS_ASSERT(dr_angminlut8 >= 0 && dr_angminlut8 <= 16);
        VPSS_ASSERT(dr_angminlut9 >= 0 && dr_angminlut9 <= 16);
        VPSS_ASSERT(dr_angminlut10 >= 0 && dr_angminlut10 <= 16);
        VPSS_ASSERT(dr_angminlut11 >= 0 && dr_angminlut11 <= 16);
        VPSS_ASSERT(dr_angminlut12 >= 0 && dr_angminlut12 <= 16);
        VPSS_ASSERT(dr_angminlut13 >= 0 && dr_angminlut13 <= 16);
        VPSS_ASSERT(dr_angminlut14 >= 0 && dr_angminlut14 <= 16);
        VPSS_ASSERT(dr_angminlut15 >= 0 && dr_angminlut15 <= 16);
        VPSS_ASSERT(dr_angminlut16 >= 0 && dr_angminlut16 <= 16);
        VPSS_ASSERT(dr_angdifflut0 >= 0 && dr_angdifflut0 <= 16);
        VPSS_ASSERT(dr_angdifflut1 >= 0 && dr_angdifflut1 <= 16);
        VPSS_ASSERT(dr_angdifflut2 >= 0 && dr_angdifflut2 <= 16);
        VPSS_ASSERT(dr_angdifflut3 >= 0 && dr_angdifflut3 <= 16);
        VPSS_ASSERT(dr_angdifflut4 >= 0 && dr_angdifflut4 <= 16);
        VPSS_ASSERT(dr_angdifflut5 >= 0 && dr_angdifflut5 <= 16);
        VPSS_ASSERT(dr_angdifflut6 >= 0 && dr_angdifflut6 <= 16);
        VPSS_ASSERT(dr_angdifflut7 >= 0 && dr_angdifflut7 <= 16);
        VPSS_ASSERT(dr_angdifflut8 >= 0 && dr_angdifflut8 <= 16);
        VPSS_ASSERT(dr_angdifflut9 >= 0 && dr_angdifflut9 <= 16);
        VPSS_ASSERT(dr_angdifflut10 >= 0 && dr_angdifflut10 <= 16);
        VPSS_ASSERT(dr_angdifflut11 >= 0 && dr_angdifflut11 <= 16);
        VPSS_ASSERT(dr_angdifflut12 >= 0 && dr_angdifflut12 <= 16);
        VPSS_ASSERT(dr_angdifflut13 >= 0 && dr_angdifflut13 <= 16);
        VPSS_ASSERT(dr_angdifflut14 >= 0 && dr_angdifflut14 <= 16);
        VPSS_ASSERT(dr_angdifflut15 >= 0 && dr_angdifflut15 <= 16);
        VPSS_ASSERT(dr_angdifflut16 >= 0 && dr_angdifflut16 <= 16);
        VPSS_ASSERT(dr_lswadjlut0 >= 0 && dr_lswadjlut0 <= 8);
        VPSS_ASSERT(dr_lswadjlut1 >= 0 && dr_lswadjlut1 <= 8);
        VPSS_ASSERT(dr_lswadjlut2 >= 0 && dr_lswadjlut2 <= 8);
        VPSS_ASSERT(dr_lswadjlut3 >= 0 && dr_lswadjlut3 <= 8);
        VPSS_ASSERT(dr_lswadjlut4 >= 0 && dr_lswadjlut4 <= 8);
        VPSS_ASSERT(dr_lswadjlut5 >= 0 && dr_lswadjlut5 <= 8);
        VPSS_ASSERT(dr_lswadjlut6 >= 0 && dr_lswadjlut6 <= 8);
        VPSS_ASSERT(dr_lswadjlut7 >= 0 && dr_lswadjlut7 <= 8);
        VPSS_ASSERT(dr_lswadjlut8 >= 0 && dr_lswadjlut8 <= 8);
        VPSS_ASSERT(dr_lrwadjlut0 >= 0 && dr_lrwadjlut0 <= 8);
        VPSS_ASSERT(dr_lrwadjlut1 >= 0 && dr_lrwadjlut1 <= 8);
        VPSS_ASSERT(dr_lrwadjlut2 >= 0 && dr_lrwadjlut2 <= 8);
        VPSS_ASSERT(dr_lrwadjlut3 >= 0 && dr_lrwadjlut3 <= 8);
        VPSS_ASSERT(dr_lrwadjlut4 >= 0 && dr_lrwadjlut4 <= 8);
        VPSS_ASSERT(dr_lrwadjlut5 >= 0 && dr_lrwadjlut5 <= 8);
        VPSS_ASSERT(dr_lrwadjlut6 >= 0 && dr_lrwadjlut6 <= 8);
        VPSS_ASSERT(dr_lrwadjlut7 >= 0 && dr_lrwadjlut7 <= 8);
        VPSS_ASSERT(dr_lrwadjlut8 >= 0 && dr_lrwadjlut8 <= 8);
        VPSS_ASSERT(dm_csw_trsnt_lt >= 0 && dm_csw_trsnt_lt <= 255);
        VPSS_ASSERT(dm_csw_trsnt_st >= 0 && dm_csw_trsnt_st <= 255);
        VPSS_ASSERT(dm_csw_trsnt_lt > dm_csw_trsnt_st);
        VPSS_ASSERT(dm_csw_trsnt_lt_10 >= 0 && dm_csw_trsnt_lt_10 <= 1023);
        VPSS_ASSERT(dm_csw_trsnt_st_10 >= 0 && dm_csw_trsnt_st_10 <= 1023);
        VPSS_ASSERT(dm_csw_trsnt_lt_10 > dm_csw_trsnt_st_10);
        VPSS_ASSERT(dm_mmf_lr >= -256 && dm_mmf_lr <= 255);
        VPSS_ASSERT(dm_mmf_sr >= -256 && dm_mmf_sr <= 255);
        VPSS_ASSERT(dm_trans_wid >= 0 && dm_trans_wid <= 255);
        VPSS_ASSERT(dm_trans_wid > dm_mmf_sr && dm_trans_wid < dm_mmf_lr);
        VPSS_ASSERT(dm_mmf_lr_10 >= -1024 && dm_mmf_lr_10 <= 1023);
        VPSS_ASSERT(dm_mmf_sr_10 >= -1024 && dm_mmf_sr_10 <= 1023);
        VPSS_ASSERT(dm_trans_wid_10 >= 0 && dm_trans_wid_10 <= 1023);
        VPSS_ASSERT(dm_trans_wid_10 > dm_mmf_sr_10 && dm_trans_wid_10 < dm_mmf_lr_10);
        VPSS_ASSERT(y2dwinwidth == 1 || y2dwinwidth == 3 || y2dwinwidth == 5 || y2dwinwidth == 9);
        VPSS_ASSERT(y2dwinheight == 1 || y2dwinheight == 3 || y2dwinheight == 5);
        VPSS_ASSERT(c2dwinwidth == 1 || c2dwinwidth == 3 || c2dwinwidth == 5);
        VPSS_ASSERT(c2dwinheight == 1 || c2dwinheight == 3);
        VPSS_ASSERT(edgeminratio <= edgemaxratio);
        VPSS_ASSERT(edgeminstrength <= edgemaxstrength);
        VPSS_ASSERT(edgestrth1 <= edgestrth2 && edgestrth2 <= edgestrth3);
        VPSS_ASSERT(edgemeanth1 <= edgemeanth2 && edgemeanth2 <= edgemeanth3 && edgemeanth3 <= edgemeanth4 && edgemeanth4 <= edgemeanth5 && edgemeanth5 <= edgemeanth6 && edgemeanth6 <= edgemeanth7 && edgemeanth7 <= edgemeanth8);

        VPSS_ASSERT(edge1 >= 0 && edge1 <= 15);
        VPSS_ASSERT(edge2 >= 0 && edge2 <= 15);
        VPSS_ASSERT(edge3 >= 0 && edge3 <= 15);

        VPSS_ASSERT(ratio1 >= 0 && ratio1 <= 31);
        VPSS_ASSERT(ratio2 >= 0 && ratio2 <= 31);
        VPSS_ASSERT(ratio3 >= 0 && ratio3 <= 31);
        VPSS_ASSERT(ratio4 >= 0 && ratio4 <= 31);
        VPSS_ASSERT(ratio5 >= 0 && ratio5 <= 31);
        VPSS_ASSERT(ratio6 >= 0 && ratio6 <= 31);
        VPSS_ASSERT(ratio7 >= 0 && ratio7 <= 31);
        VPSS_ASSERT(ratio8 >= 0 && ratio8 <= 31);

        VPSS_ASSERT(cb_begin1 <= cb_end1);
        VPSS_ASSERT(cb_begin2 <= cb_end2);
        VPSS_ASSERT(cr_begin1 <= cr_end1);
        VPSS_ASSERT(cr_begin2 <= cr_end2);
        //VPSS_ASSERT(test_en==0);
        //VPSS_ASSERT(test_color_cb==0);
        //VPSS_ASSERT(test_color_cr==0);
    }
    if (fmtc_en == 1)
    {
        VPSS_ASSERT(((FMTC_IN_WIDTH & 0x1) == 1) && (FMTC_IN_WIDTH >= 31 && FMTC_IN_WIDTH <= 1919));
        VPSS_ASSERT(((FMTC_IN_HEIGHT & 0x1) == 1) && (FMTC_IN_HEIGHT >= 31 && FMTC_IN_HEIGHT <= 1079));
        VPSS_ASSERT((FMTC_IN_FORMAT == YUV422) || (FMTC_IN_FORMAT == YUV420));
        VPSS_ASSERT(FMTC_OUT_WIDTH == FMTC_IN_WIDTH);
        VPSS_ASSERT(FMTC_OUT_HEIGHT == FMTC_IN_HEIGHT);
        VPSS_ASSERT(FMTC_OUT_FORMAT == FMTC_IN_FORMAT);
        VPSS_ASSERT(vpss_fmtc_demo_offset >= 0 && vpss_fmtc_demo_offset <= FMTC_IN_WIDTH + 1);
    }
    if (vhd0_crop_en == 1)
    {
        VPSS_ASSERT(VHD0_CROP_IN_WIDTH >= 63 && VHD0_CROP_IN_WIDTH <= 4095);
        VPSS_ASSERT(VHD0_CROP_IN_HEIGHT >= 63 && VHD0_CROP_IN_HEIGHT <= 4095);
        VPSS_ASSERT((vhd0_crop_x + vhd0_crop_width) <= VHD0_CROP_IN_WIDTH);
        VPSS_ASSERT((vhd0_crop_y + vhd0_crop_height) <= VHD0_CROP_IN_HEIGHT);
    }
    if (zme_vhd0_en == 1)
    {
        VPSS_ASSERT((VHD0_ZME_IN_WIDTH & 0x1) == 0x1);
        VPSS_ASSERT((VHD0_ZME_IN_HEIGHT & 0x1) == 0x1);
        VPSS_ASSERT(VHD0_ZME_IN_WIDTH >= 63 && VHD0_ZME_IN_WIDTH <= 4095);
        VPSS_ASSERT(VHD0_ZME_IN_HEIGHT >= 63 && VHD0_ZME_IN_HEIGHT <= 2303);
        VPSS_ASSERT(VHD0_ZME_OUT_WIDTH >= 31 && VHD0_ZME_OUT_WIDTH <= 1919);
        VPSS_ASSERT(VHD0_ZME_OUT_HEIGHT >= 31 && VHD0_ZME_OUT_HEIGHT <= 1079);
        //VPSS_ASSERT(hfir_order==0);
        VPSS_ASSERT((vhd0_zme_ow & 0x1) == 1);
        VPSS_ASSERT((vhd0_zme_oh & 0x1) == 1);
        //  VPSS_ASSERT(hratio==((long long)(VHD0_ZME_IN_WIDTH+1)*0x100000)/(vhd0_zme_ow+1));
        VPSS_ASSERT(hratio < 16 * 0x100000);
        VPSS_ASSERT(hratio > 0x100000 / 16);
        //VPSS_ASSERT(vratio==((VHD0_ZME_IN_HEIGHT+1)/2*0x1000)/((vhd0_zme_oh+1)/2));
        VPSS_ASSERT(vratio <= 15 * 0x1000);
        VPSS_ASSERT(vratio > 0x1000 / 16);
        VPSS_ASSERT(vchmsc_en == vlmsc_en);
        VPSS_ASSERT(hchmsc_en == hlmsc_en);
        VPSS_ASSERT(hor_loffset == 0x0);
        // VPSS_ASSERT(hor_coffset<=1*0x100000);
        //VPSS_ASSERT(hor_coffset>=-1*0x100000);
        VPSS_ASSERT(vluma_offset <= 0);
        //VPSS_ASSERT(vluma_offset>=-1*0x1000);
        VPSS_ASSERT(vchroma_offset <= 0);
        //VPSS_ASSERT(vchroma_offset>=-2*0x1000);
    }
    if (vhd0_lba_en == 1)
    {
        VPSS_ASSERT(VHD0_LBA_IN_WIDTH >= 63 && VHD0_LBA_IN_WIDTH <= 4095);
        VPSS_ASSERT(VHD0_LBA_IN_HEIGHT >= 63 && VHD0_LBA_IN_HEIGHT <= 4095);
        VPSS_ASSERT((vhd0_lba_xfpos + VHD0_LBA_IN_WIDTH) <= vhd0_lba_width);
        VPSS_ASSERT((vhd0_lba_yfpos + VHD0_LBA_IN_HEIGHT) <= vhd0_lba_height);
    }
    if (four_pix_en == 1)
    {
        VPSS_ASSERT(nx2_vc1_en == 0);
        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);
    }
    if (in_format == 0xb || in_format == 0xc || in_format == 0xd)
    {
        VPSS_ASSERT(dei_en == 0);
    }
    if (tnr_en && motionestimateen)
    {
        VPSS_ASSERT(rgme_en == 1);
        VPSS_ASSERT(dei_cfg_addr != 0);
    }

    VPSS_INFO ("vpss cfg constraint check end!\n");
#endif
}

HI_VOID VPSS_HAL_Assert(HI_S32 s32NodeId, volatile S_VPSS_REGS_TYPE *vpss_reg)
{
#if 0
    HI_BOOL bErrFlag = HI_FALSE; //err print

    HI_U32 vpss_tmp_width       = 0;//for size check
    HI_U32 vpss_tmp_height      = 0;
    HI_U32 vpss_tmp_format      = 0;
    HI_U32 vpss_vhd0_tmp_width  = 0;//for size check
    HI_U32 vpss_vhd0_tmp_height = 0;
    HI_U32 vpss_vhd0_tmp_format = 0;
    HI_U32 YC_422               = 0;
    //**************************//
    //       GET REG CFG
    //**************************//
    //MAC && BUS
    HI_U32 bfield              = vpss_reg->VPSS_CTRL.bits.bfield;
    HI_U32 in_format           = vpss_reg->VPSS_IN_CTRL.bits.in_format;
    HI_U32 nx2_offx            = vpss_reg->VPSS_NXT2_CTRL.bits.nxt2_hor_offset;
    HI_U32 nx2_offy            = vpss_reg->VPSS_NXT2_CTRL.bits.nxt2_ver_offset;
    HI_U32 nx1_offx            = vpss_reg->VPSS_NXT1_CTRL.bits.nxt1_hor_offset;
    HI_U32 nx1_offy            = vpss_reg->VPSS_NXT1_CTRL.bits.nxt1_ver_offset;
    HI_U32 cur_offx            = vpss_reg->VPSS_CUR_CTRL.bits.cur_hor_offset;
    HI_U32 cur_offy            = vpss_reg->VPSS_CUR_CTRL.bits.cur_ver_offset;
    HI_U32 ref_offx            = vpss_reg->VPSS_REF_CTRL.bits.ref_hor_offset;
    HI_U32 ref_offy            = vpss_reg->VPSS_REF_CTRL.bits.ref_ver_offset;
    HI_U32 cur_tunl_en         = vpss_reg->VPSS_NX2_TUNL_CTRL.bits.nx2_tunl_en;
    HI_U32 rotate_en           = vpss_reg->VPSS_CTRL.bits.rotate_en;
    HI_U32 vhd0_flip           = vpss_reg->VPSS_VHD0CTRL.bits.vhd0_flip;
    HI_U32 four_pix_en         = vpss_reg->VPSS_CTRL.bits.four_pix_en;
    HI_U32 img_pro_mode        = vpss_reg->VPSS_CTRL.bits.img_pro_mode;
    HI_U32 ram_bank            = vpss_reg->VPSS_CTRL2.bits.ram_bank;

    HI_U32 cur_type            = vpss_reg->VPSS_CUR_CTRL.bits.cur_tile_format;
    HI_U32 ref_type            = vpss_reg->VPSS_REF_CTRL.bits.ref_tile_format;
    HI_U32 nx1_type            = vpss_reg->VPSS_NXT1_CTRL.bits.nxt1_tile_format;
    HI_U32 nx2_type            = vpss_reg->VPSS_NXT2_CTRL.bits.nxt2_tile_format;
    HI_U32 nxt2_tile_spec_field = vpss_reg->VPSS_NXT2_CTRL.bits.nxt2_tile_spec_field;

    HI_U32 nx2_dcmp_en         = vpss_reg->VPSS_NXT2_CTRL.bits.nxt2_dcmp_en;
    HI_U32 in_pix_bitw         = vpss_reg->VPSS_IN_CTRL.bits.in_pix_bitw;

    HI_U32 nx2_width           = vpss_reg->VPSS_IMGSIZE.bits.imgwidth  + 1;
    HI_U32 nx2_height          = vpss_reg->VPSS_IMGSIZE.bits.imgheight + 1;

    HI_U32 ref_width           = vpss_reg->VPSS_REFSIZE.bits.refwidth  + 1;
    HI_U32 ref_height          = vpss_reg->VPSS_REFSIZE.bits.refheight + 1;

    //channel addr and stride
    // HI_U32 nx2_y_addr          = vpss_reg->VPSS_NXT2YADDR.bits.nxt2y_addr;
    // HI_U32 nx2_c_addr          = vpss_reg->VPSS_NXT2CADDR.bits.nxt2c_addr;
    // HI_U32 nx2_y_stride        = vpss_reg->VPSS_NXT2STRIDE.bits.nxt2y_stride;
    // HI_U32 nx2_c_stride        = vpss_reg->VPSS_NXT2STRIDE.bits.nxt2c_stride;
    HI_U32 nx2_y_head_addr     = vpss_reg->VPSS_NX2Y_HEAD_ADDR.bits.nx2y_top_head_addr;
    HI_U32 nx2_y_bot_head_addr = vpss_reg->VPSS_NX2Y_BOT_HEAD_ADDR.bits.nx2y_bot_head_addr;
    HI_U32 nx2_c_head_addr     = vpss_reg->VPSS_NX2C_HEAD_ADDR.bits.nx2c_top_head_addr;
    HI_U32 nx2_c_bot_head_addr = vpss_reg->VPSS_NX2C_BOT_HEAD_ADDR.bits.nx2c_bot_head_addr;
    // HI_U32 nx2_head_stride     = vpss_reg->VPSS_NX2_HEAD_STRIDE.bits.nx2_head_stride;

    HI_U32 nx1_y_addr          = vpss_reg->VPSS_NXT1YADDR.bits.nxt1y_addr;
    HI_U32 nx1_c_addr          = vpss_reg->VPSS_NXT1CADDR.bits.nxt1c_addr;
    // HI_U32 nx1_y_stride        = vpss_reg->VPSS_NXT1STRIDE.bits.nxt1y_stride;
    // HI_U32 nx1_c_stride        = vpss_reg->VPSS_NXT1STRIDE.bits.nxt1c_stride;

    HI_U32 cur_y_addr          = vpss_reg->VPSS_CURYADDR.bits.cury_addr;
    HI_U32 cur_c_addr          = vpss_reg->VPSS_CURCADDR.bits.curc_addr;
    // HI_U32 cur_y_stride        = vpss_reg->VPSS_CURSTRIDE.bits.cury_stride;
    // HI_U32 cur_c_stride        = vpss_reg->VPSS_CURSTRIDE.bits.curc_stride;

    HI_U32 ref_y_addr          = vpss_reg->VPSS_REFYADDR.bits.refy_addr;
    HI_U32 ref_c_addr          = vpss_reg->VPSS_REFCADDR.bits.refc_addr;
    // HI_U32 ref_y_stride        = vpss_reg->VPSS_REFSTRIDE.bits.refy_stride;
    //  HI_U32 ref_c_stride        = vpss_reg->VPSS_REFSTRIDE.bits.refc_stride;

    HI_U32 ree_y_addr          = vpss_reg->VPSS_REEYADDR.bits.reey_addr;
    HI_U32 ree_c_addr          = vpss_reg->VPSS_REECADDR.bits.reec_addr;
    //   HI_U32 ree_y_stride        = vpss_reg->VPSS_REESTRIDE.bits.reey_stride;
    //  HI_U32 ree_c_stride        = vpss_reg->VPSS_REESTRIDE.bits.reec_stride;

    HI_U32 prjv_cur_addr       = vpss_reg->VPSS_PRJVCURADDR.bits.prjv_cur_addr;
    HI_U32 prjh_cur_addr       = vpss_reg->VPSS_PRJHCURADDR.bits.prjh_cur_addr;
    //  HI_U32 prjv_cur_stride     = vpss_reg->VPSS_PRJCURSTRIDE.bits.prjv_cur_stride;
    //  HI_U32 prjh_cur_stride     = vpss_reg->VPSS_PRJCURSTRIDE.bits.prjh_cur_stride;

    HI_U32 rgmv_cur_addr       = vpss_reg->VPSS_RGMVCURADDR.bits.rgmv_cur_addr;
    // HI_U32 rgmv_cur_stride     = vpss_reg->VPSS_RGMVSTRIDE.bits.rgmv_cur_stride;
    HI_U32 rgmv_nx1_addr       = vpss_reg->VPSS_RGMVNX1ADDR.bits.rgmv_nx1_addr;
    //  HI_U32 rgmv_nx1_stride     = vpss_reg->VPSS_RGMVSTRIDE.bits.rgmv_nx1_stride;

    HI_U32 blkmv_nx1_addr      = vpss_reg->VPSS_BLKMVNX1ADDR.bits.blkmv_nx1_addr;
    // HI_U32 blkmv_nx1_stride    = vpss_reg->VPSS_BLKMVNX1STRIDE.bits.blkmv_nx1_stride;
    HI_U32 blkmv_cur_addr      = vpss_reg->VPSS_BLKMVCURADDR.bits.blkmv_cur_addr;
    // HI_U32 blkmv_cur_stride    = vpss_reg->VPSS_BLKMVSTRIDE.bits.blkmv_cur_stride;
    HI_U32 blkmv_ref_addr      = vpss_reg->VPSS_BLKMVREFADDR.bits.blkmv_ref_addr;
    //  HI_U32 blkmv_ref_stride    = vpss_reg->VPSS_BLKMVSTRIDE.bits.blkmv_ref_stride;

    HI_U32 blkmt_cur_addr      = vpss_reg->VPSS_BLKMTCURADDR.bits.blkmt_cur_addr;
    HI_U32 blkmt_ref_addr      = vpss_reg->VPSS_BLKMTREFADDR.bits.blkmt_ref_addr;
    HI_U32 tnr_rmad_addr       = vpss_reg->VPSS_MAD_RADDR.bits.mad_raddr;
    // HI_U32 tnr_rmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;

    // HI_U32 snr_rmad_addr       = vpss_reg->VPSS_SNR_MAD_RADDR.bits.snr_mad_raddr;
    // HI_U32 snr_rmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;

    HI_U32 dei_rst_addr        = vpss_reg->VPSS_STRADDR.bits.st_raddr;
    // HI_U32 dei_rst_stride      = vpss_reg->VPSS_STSTRIDE.bits.st_stride;

    // HI_U32 vhd0_y_addr         = vpss_reg->VPSS_VHD0YADDR.bits.vhd0y_addr;
    // HI_U32 vhd0_c_addr         = vpss_reg->VPSS_VHD0CADDR.bits.vhd0c_addr;
    // HI_U32 vhd0_y_stride       = vpss_reg->VPSS_VHD0STRIDE.bits.vhd0y_stride;
    //  HI_U32 vhd0_c_stride       = vpss_reg->VPSS_VHD0STRIDE.bits.vhd0c_stride;

    HI_U32 rfr_y_addr          = vpss_reg->VPSS_RFRYADDR.bits.rfry_addr;
    HI_U32 rfr_c_addr          = vpss_reg->VPSS_RFRCADDR.bits.rfrc_addr;
    HI_U32 rfr_y_stride        = vpss_reg->VPSS_RFRSTRIDE.bits.rfry_stride;
    HI_U32 rfr_c_stride        = vpss_reg->VPSS_RFRSTRIDE.bits.rfrc_stride;

    HI_U32 cue_y_addr          = vpss_reg->VPSS_CUEYADDR.bits.cuey_addr;
    HI_U32 cue_c_addr          = vpss_reg->VPSS_CUECADDR.bits.cuec_addr;
    // HI_U32 cue_y_stride        = vpss_reg->VPSS_CUESTRIDE.bits.cuey_stride;
    // HI_U32 cue_c_stride        = vpss_reg->VPSS_CUESTRIDE.bits.cuec_stride;

    HI_U32 prjv_nx2_addr       = vpss_reg->VPSS_PRJVNX2ADDR.bits.prjv_nx2_addr;
    HI_U32 prjh_nx2_addr       = vpss_reg->VPSS_PRJHNX2ADDR.bits.prjh_nx2_addr;
    //  HI_U32 prjv_nx2_stride     = vpss_reg->VPSS_PRJNX2STRIDE.bits.prjh_nx2_stride;
    //  HI_U32 prjh_nx2_stride     = vpss_reg->VPSS_PRJNX2STRIDE.bits.prjh_nx2_stride;

    //  HI_U32 blkmv_nx2_addr      = 0;//vpss_reg->VPSS_BLKMVNX2ADDR;
    // HI_U32 blkmv_nx2_stride    = 0;//vpss_reg->VPSS_BLKMVNX2STRIDE.bits.blkmv_nx2_stride;

    HI_U32 rgmv_nx2_addr       = vpss_reg->VPSS_RGMVNX2ADDR.bits.rgmv_nx2_addr;
    //HI_U32 rgmv_nx2_stride     = vpss_reg->VPSS_RGMVNX2STRIDE.bits.rgmv_nx2_stride;

    HI_U32 tnr_wmad_addr       = vpss_reg->VPSS_MAD_WADDR.bits.mad_waddr;
    //  HI_U32 tnr_wmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;

    HI_U32 dei_wst_addr        = vpss_reg->VPSS_STWADDR.bits.st_waddr;
    //  HI_U32 dei_wst_stride      = vpss_reg->VPSS_STSTRIDE.bits.st_stride;

    //VC1
    HI_U32 nx2_vc1_en          = vpss_reg->VPSS_CTRL.bits.nx2_vc1_en;
    HI_U32 nx1_vc1_en          = 0;//vpss_reg->VPSS_CTRL.bits.nx1_vc1_en;
    HI_U32 cur_vc1_en          = 0;//vpss_reg->VPSS_CTRL.bits.cur_vc1_en;
    HI_U32 ref_vc1_en          = 0;//vpss_reg->VPSS_CTRL.bits.ref_vc1_en;

    //TNR
    HI_U32 tnr_mode            = 0;//vpss_reg->VPSS_CTRL3.bits.tnr_mode;
    HI_U32 tnr_en              = vpss_reg->VPSS_CTRL.bits.tnr_en;
    HI_U32 rgme_en             = vpss_reg->VPSS_CTRL.bits.rgme_en;
    HI_U32 mcnr_meds_en        = vpss_reg->VPSS_TNR_CONTRL.bits.mcnr_meds_en;
    HI_U32 mcnr_en             = vpss_reg->VPSS_TNR_CONTRL.bits.mcnr_en;
    //  HI_U32 mcnr_rgme_mode      = vpss_reg->VPSS_TNR_CONTRL.bits.mcnr_rgme_mode;
    //  HI_U32 bfield_mode         = vpss_reg->VPSS_CTRL.bits.bfield_mode;
    HI_U32 motionedgeen        = 0;//vpss_reg->VPSS_SNR_ENABLE.bits.motionedgeen;
    HI_U32 motion_mode         = vpss_reg->VPSS_TNR_CONTRL.bits.motion_mode;
    HI_U32 cbcrupdateen        = vpss_reg->VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrupdateen;
    HI_U32 ymotionmode         = vpss_reg->VPSS_TNR_FILR_MODE.bits.ymotionmode;
    HI_U32 ymotioncalcmode     = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.ymotioncalcmode;
    HI_U32 cmotioncalcmode     = vpss_reg->VPSS_TNR_MAMD_CTRL.bits.cmotioncalcmode;
    HI_U32 motionestimateen    = vpss_reg->VPSS_TNR_MAME_CTRL.bits.motionestimateen;
    // HI_U32 noisedetecten       = vpss_reg->VPSS_TNR_MAND_CTRL.bits.noisedetecten;
    HI_U32 tnr_tmu_addr        = vpss_reg->VPSS_TNR_ADDR.bits.tnr_cfg_addr;
    HI_U32 rfr_en              = vpss_reg->VPSS_CTRL.bits.rfr_en;

    //DEI
    HI_U32 dei_en              = vpss_reg->VPSS_CTRL.bits.dei_en;
    HI_U32 mcdi_en             = vpss_reg->VPSS_CTRL.bits.mcdi_en;
    HI_U32 meds_en             = vpss_reg->VPSS_CTRL.bits.meds_en;
    HI_U32 ifmd_en             = vpss_reg->VPSS_CTRL.bits.ifmd_en;
    HI_U32 igbm_en             = vpss_reg->VPSS_CTRL.bits.igbm_en;
    HI_U32 mcstartr            = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcstartr               ;//0; //8bit; [0,255]
    HI_U32 mcstartc            = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcstartc               ;//0; //8bit; [0,255]
    HI_U32 mcendr              = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcendr                 ;//0; //8bit; [0,255]
    HI_U32 mcendc              = vpss_reg->VPSS_MCDI_LCDINEW0.bits.mcendc                 ;//0; //8bit; [0,255]
    HI_U32 pre_info_en         = vpss_reg->VPSS_DIEHISMODE.bits.pre_info_en                            ;
    HI_U32 ppre_info_en        = vpss_reg->VPSS_DIEHISMODE.bits.ppre_info_en                           ;
    HI_U32 dei_lmmode          = vpss_reg->VPSS_DIECTRL.bits.die_l_mode ; //0:5  1:4  2:3
    HI_U32 dei_cmmode          = vpss_reg->VPSS_DIECTRL.bits.die_c_mode;
    HI_U32 dei_tmu_addr        = vpss_reg->VPSS_DEI_ADDR.bits.dei_cfg_addr;
    HI_U32 two_four_pxl_share  = vpss_reg->VPSS_DIECTRL.bits.two_four_pxl_share                      ;

    //SNR
    HI_U32 snr_en              = vpss_reg->VPSS_CTRL.bits.snr_en;
    HI_U32 snr_nr_en           = vpss_reg->VPSS_SNR_CTRL.bits.snr_nr_en;
    HI_U32 db_en               = vpss_reg->VPSS_SNR_CTRL.bits.db_en;
    HI_U32 blk_det_en          = vpss_reg->VPSS_CTRL.bits.blk_det_en;
    HI_U32 det_hy_en           = vpss_reg->VPSS_SNR_CTRL.bits.det_hy_en;
    HI_U32 det_hc_en           = 0;
    HI_U32 det_vy_en           = 0;
    HI_U32 mad_mode            = vpss_reg->VPSS_SNR_CTRL.bits.mad_mode;
    HI_U32 snr_tmu_addr        = vpss_reg->VPSS_SNR_ADDR.bits.snr_cfg_addr;

    //VPZME
    //CROP
    HI_U32 vhd0_crop_en        = vpss_reg->VPSS_CTRL3.bits.vhd0_crop_en;
    HI_U32 vhd0_crop_x         = vpss_reg->VPSS_VHD0CROP_POS.bits.vhd0_crop_x;
    HI_U32 vhd0_crop_y         = vpss_reg->VPSS_VHD0CROP_POS.bits.vhd0_crop_y;
    HI_U32 vhd0_crop_width     = vpss_reg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width + 1;
    HI_U32 vhd0_crop_height    = vpss_reg->VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height + 1;
    //ZME
    //HI_U32 vhd0_pre_hfir_en    = vpss_reg->VPSS_CTRL3.bits.vhd0_pre_hfir_en;
    HI_U32 vhd0_zme_en         = vpss_reg->VPSS_CTRL3.bits.zme_vhd0_en;
    HI_U32 vhd0_zme_ow         = vpss_reg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow + 1;
    HI_U32 vhd0_zme_oh         = vpss_reg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh + 1;
    HI_U32 vhd0_zme_order      = vpss_reg->VPSS_VHD0_HSP.bits.hfir_order;
    HI_U32 vhd0_hlmsc_en       = vpss_reg->VPSS_VHD0_HSP.bits.hlmsc_en;
    HI_U32 vhd0_vlmsc_en       = vpss_reg->VPSS_VHD0_VSP.bits.vlmsc_en;
    HI_U32 vhd0_hchmsc_en      = vpss_reg->VPSS_VHD0_HSP.bits.hchmsc_en;
    HI_U32 vhd0_vchmsc_en      = vpss_reg->VPSS_VHD0_VSP.bits.vchmsc_en;
    HI_U32 vhd0_zme_outfmt     = vpss_reg->VPSS_VHD0_VSP.bits.zme_out_fmt;
    HI_U32 vhd0_zme_tmu_addr   = vpss_reg->VPSS_ZME_ADDR.bits.zme_cfg_addr;
    //LBA
    HI_U32 vhd0_lba_en         = vpss_reg->VPSS_CTRL3.bits.vhd0_lba_en;
    HI_U32 vhd0_lba_dis_width  = vpss_reg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_width  + 1;
    HI_U32 vhd0_lba_dis_height = vpss_reg->VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_height + 1;
    HI_U32 vhd0_lba_xfpos      = vpss_reg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_xfpos;
    HI_U32 vhd0_lba_yfpos      = vpss_reg->VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_yfpos;
    //VHD0
    HI_U32 vhd0_en             = vpss_reg->VPSS_CTRL.bits.vhd0_en;
    HI_U32 vhd0_pix_bitw       = vpss_reg->VPSS_VHD0CTRL.bits.vhd0_pix_bitw;
    HI_U32 vhd0_format         = vpss_reg->VPSS_VHD0CTRL.bits.vhd0_format;
    HI_U32 vhd0_out_width      = vpss_reg->VPSS_VHD0SIZE.bits.vhd0_width + 1;
    HI_U32 vhd0_out_height     = vpss_reg->VPSS_VHD0SIZE.bits.vhd0_height + 1;
    HI_U32 cts_en              = vpss_reg->VPSS_IN_CTRL.bits.cts_en;
    // HI_U32 vhd0_flip_en        = vpss_reg->VPSS_VHD0CTRL.bits.vhd0_flip;
    HI_U32 vhd0_mirror         = vpss_reg->VPSS_VHD0CTRL.bits.vhd0_mirror;
    HI_U32 vhd0_tunl_en        = vpss_reg->VPSS_VHD0_TUNL_CTRL.bits.vhd0_tunl_en;
    HI_U32 fmtc_en             = vpss_reg->VPSS_CTRL.bits.fmtc_en;

    //**************************//
    //       PRINT REG CFG
    //**************************//
    switch (in_format)
    {
        case 0x0://LINEAR_SP420   :
        case 0x3://SP422_1X2      :
        case 0x7://PLANAR_422_1X2 :
        case 0x4://PLANAR_400     :
        case 0x8://PLANAR_420     :
        case 0xa://PLANAR_410     :
        {
            YC_422 = 0;
        }
        break;

        case 0x1://SP422_2X1      :
        case 0x5://PLANAR_444     :
        case 0x6://PLANAR_422_2X1 :
        case 0x9://PLANAR_411     :
        case 0xb://PACKAGE422_YUYV:
        case 0xc://PACKAGE422_YVYU:
        case 0xd://PACKAGE422_UYVY:
        case 0xe://ARGB_8888       :
        case 0xf://ABGR_8888       :
        case 0x10://ARGB_1555       :
        case 0x11://ABGR_1555       :
        case 0x12://RGB_565         :
        case 0x13://BGR_565         :
        {
            YC_422 = 1;
        }
        break;
    }
    if (bfield == 1) //field in, offy is field's offsety. It should turn to frame's offsety.
    {
        ref_offy *= 2;
        cur_offy *= 2;
        nx1_offy *= 2;
        nx2_offy *= 2;
    }

    //**************************//
    //       CHECK REG CFG
    //**************************//
    //MAC && BUS
    //type/linear type
    if ((in_format == 0xb) || (in_format == 0xc) || (in_format == 0xd)) //package
    {
        VPSS_ASSERT(cur_type == 0);
        VPSS_ASSERT(ref_type == 0);
        VPSS_ASSERT(nx1_type == 0);
        VPSS_ASSERT(nx2_type == 0);
    }
    //if(bfield==1) {VPSS_ASSERT(nx2_type == 0);}//hi3798mv200 linear field
    //DCMP
    if (nx2_dcmp_en == 1)
    {
        VPSS_ASSERT(nx2_type == 1);
        VPSS_ASSERT(nx2_y_head_addr != 0);
        VPSS_ASSERT(nx2_c_head_addr != 0);
        VPSS_ASSERT(nx2_y_bot_head_addr != 0);
        VPSS_ASSERT(nx2_c_bot_head_addr != 0);
    }
    if (nx2_type == 0)
    {
        VPSS_ASSERT(nxt2_tile_spec_field == 0);
    }
    //if(nx2_dcmp_en==1 || nx2_type==1)//hi3798mv200
    //{
    //    VPSS_ASSERT(dei_en == 0);
    //    VPSS_ASSERT(tnr_en == 0);
    //    VPSS_ASSERT(snr_en == 0);
    //}
    //offset
    VPSS_ASSERT((nx2_offx % 2) == 0);
    VPSS_ASSERT((nx2_offy % 2) == 0);
    VPSS_ASSERT((nx1_offx % 2) == 0);
    VPSS_ASSERT((nx1_offy % 2) == 0);
    VPSS_ASSERT((cur_offx % 2) == 0);
    VPSS_ASSERT((cur_offy % 2) == 0);
    VPSS_ASSERT((ref_offx % 2) == 0);
    VPSS_ASSERT((ref_offy % 2) == 0);
    if (bfield == 1 && YC_422 == 0)
    {
        VPSS_ASSERT((nx2_offy % 4) == 0);
        VPSS_ASSERT((nx1_offy % 4) == 0);
        VPSS_ASSERT((cur_offy % 4) == 0);
        VPSS_ASSERT((ref_offy % 4) == 0);
    }
    if (in_format > 0x4)
    {
        VPSS_ASSERT((nx2_offx == 0) && (nx2_offy == 0));
    }
    //width & height
    VPSS_ASSERT(nx2_width  > 1);
    VPSS_ASSERT(nx2_height > 1);
    if ((bfield == 1) && (YC_422 == 0)) //field in, offy is field's offsety. It should turn to frame's offsety.
    {
        VPSS_ASSERT((nx2_height % 4) == 0);
    }
    //>FHD
    if ((nx2_width > 1920) || (nx2_height > 1088))
    {
        VPSS_ASSERT(nx2_vc1_en == 0);
        VPSS_ASSERT(nx1_vc1_en == 0);
        VPSS_ASSERT(cur_vc1_en == 0);
        VPSS_ASSERT(ref_vc1_en == 0);

        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);
        VPSS_ASSERT(fmtc_en == 0);
        VPSS_ASSERT(rfr_en == 0);
    }
    //4p/c
    if (four_pix_en == 1)
    {
        VPSS_ASSERT((nx2_offx % 4) == 0);
        VPSS_ASSERT((nx2_width % 4) == 0);
        VPSS_ASSERT(in_format < 0x5);
        VPSS_ASSERT(nx2_vc1_en == 0);
        VPSS_ASSERT(nx1_vc1_en == 0);
        VPSS_ASSERT(cur_vc1_en == 0);
        VPSS_ASSERT(ref_vc1_en == 0);

        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);
        VPSS_ASSERT(fmtc_en == 0);
        VPSS_ASSERT(rfr_en == 0);
    }
    //10bit
    if (in_pix_bitw == 1)
    {
        VPSS_ASSERT(ram_bank == 5);
        VPSS_ASSERT(four_pix_en == 1);
        VPSS_ASSERT(nx2_vc1_en == 0);
        VPSS_ASSERT(nx1_vc1_en == 0);
        VPSS_ASSERT(cur_vc1_en == 0);
        VPSS_ASSERT(ref_vc1_en == 0);

        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);
        VPSS_ASSERT(fmtc_en == 0);

        VPSS_ASSERT(rfr_en == 0);
        VPSS_ASSERT(vhd0_crop_en == 0);
        VPSS_ASSERT(vhd0_zme_en == 0);
        VPSS_ASSERT(vhd0_lba_en == 0);
    }
    VPSS_ASSERT(vhd0_pix_bitw == in_pix_bitw);
    //input tunnel
    if (cur_tunl_en == 1)
    {
        VPSS_ASSERT(rotate_en == 0);
        VPSS_ASSERT(bfield == 0);
        VPSS_ASSERT(in_format < 5);
        VPSS_ASSERT((nx2_offx == 0) && (nx2_offy == 0));
    }

    //GET width height format
    vpss_tmp_width       = nx2_width;//for size check
    vpss_tmp_height      = nx2_height;
    vpss_tmp_format      = YC_422;

    //VC1
    if (nx2_vc1_en || nx1_vc1_en || cur_vc1_en || ref_vc1_en)
    {
        VPSS_ASSERT((vpss_tmp_width % 16)  == 0);
        VPSS_ASSERT(vpss_tmp_format  == 0);//only 420
        if (bfield == 1)
        {
            VPSS_ASSERT((vpss_tmp_height % 32) == 0);
        }
        else
        {
            VPSS_ASSERT((vpss_tmp_height % 16) == 0);
        }
    }

    //TNR
    if (tnr_en == 1)
    {
        //if(motion_mode==1) {VPSS_ASSERT(vpss_tmp_width%4==0);}
        //if(vpss_tmp_width>720) {VPSS_ASSERT(rgme_en==0);}//3798mv200 mcnr only support SD
        //if(vpss_tmp_height>576) {VPSS_ASSERT(rgme_en==0);}

        VPSS_ASSERT(vpss_tmp_width  == ref_width);
        VPSS_ASSERT(vpss_tmp_height == ref_height);
        VPSS_ASSERT(in_pix_bitw == 0);
        VPSS_ASSERT(mcnr_en == 1);

        if (vpss_tmp_width < 128)
        {
            VPSS_ASSERT(rgme_en == 0);
        }
        if (rgme_en)
        {
            if (vpss_tmp_width < 256)
            {
                VPSS_ASSERT(mcnr_meds_en == 0);
            }
            if (vpss_tmp_width > 960)
            {
                VPSS_ASSERT(mcnr_meds_en == 1);
            }
        }
        if (motion_mode == 1)
        {
            VPSS_ASSERT(vpss_tmp_format == 1);
        }
        VPSS_ASSERT(cur_y_addr != 0);
        VPSS_ASSERT(cur_c_addr != 0);
        VPSS_ASSERT(tnr_rmad_addr != 0);
        VPSS_ASSERT(tnr_wmad_addr != 0);
        VPSS_ASSERT(tnr_tmu_addr != 0);

        if (rgme_en == 1)
        {
            VPSS_ASSERT(prjv_cur_addr != 0);
            VPSS_ASSERT(prjh_cur_addr != 0);

            VPSS_ASSERT(rgmv_cur_addr != 0);
            VPSS_ASSERT(rgmv_nx1_addr != 0);

            VPSS_ASSERT(prjv_nx2_addr != 0);
            VPSS_ASSERT(prjh_nx2_addr != 0);

            VPSS_ASSERT(rgmv_nx2_addr != 0);
        }

        if (vpss_tmp_format == 0) //while 420
        {
            VPSS_ASSERT(cbcrupdateen == 0);
            VPSS_ASSERT(ymotionmode  == 1);
        }

        //VPSS_ASSERT(ymotioncalcmode == 0);
        //VPSS_ASSERT(cmotioncalcmode == 0);

        //if(motion_mode==1)
        //{
        //    VPSS_ASSERT(vpss_tmp_width%4 == 0);
        //    //VPSS_ASSERT(vpss_tmp_width>720);//sharemotonen do no support SD size
        //}
        if (motionestimateen == 1)
        {
            VPSS_ASSERT(rgme_en == 1);
        }
        //if(noisedetecten==1)
        //{
        //    VPSS_ASSERT(vpss_tmp_width>=64 && vpss_tmp_width<=720);
        //}
    }
    if (rgme_en == 1)
    {
        VPSS_ASSERT(tnr_en == 1);
    }
    if ((snr_en == 1) && (tnr_en == 0) && (bfield == 0))
    {
        VPSS_ASSERT(motionedgeen == 0);
    }
    if (rfr_en == 1)
    {
        VPSS_ASSERT(four_pix_en == 0);
        VPSS_ASSERT(rfr_y_addr != 0);
        VPSS_ASSERT(rfr_c_addr != 0);
        VPSS_ASSERT(rfr_y_stride != 0);
        VPSS_ASSERT(rfr_c_stride != 0);
    }

    //DEI
    //if (bfield == 1)   {VPSS_ASSERT(dei_en == 1);}
    if (dei_en == 0)
    {
        VPSS_ASSERT(ifmd_en == 0);
        VPSS_ASSERT(igbm_en == 0);
        VPSS_ASSERT(mcdi_en == 0);
    }//VPSS_ASSERT(meds_en == 0);}
    if (dei_en == 1)
    {
        VPSS_ASSERT(dei_lmmode == 1);
    }
    if (dei_en == 1)
    {
        VPSS_ASSERT(tnr_mode == 0);
    }
    if (bfield == 1)
    {
        VPSS_ASSERT((in_format != 0xb) && (in_format != 0xc) && (in_format != 0xd));
    }
    if (dei_en == 1)
    {
        VPSS_ASSERT(nx2_width <= 1920);
        VPSS_ASSERT(nx2_width >= 128);
        VPSS_ASSERT(bfield == 1);
        VPSS_ASSERT(in_pix_bitw == 0);
        if (nx2_width <= 960)
        {
            VPSS_ASSERT(ram_bank == 0);
        }
        else
        {
            VPSS_ASSERT(ram_bank == 1);
        }
        VPSS_ASSERT(cts_en == 0);
        VPSS_ASSERT(two_four_pxl_share == 0);
        VPSS_ASSERT(vpss_tmp_width  == ref_width);
        VPSS_ASSERT(vpss_tmp_height == ref_height);

        if (vpss_tmp_width < 128)
        {
            VPSS_ASSERT(mcdi_en == 0);
        }
        if (vpss_tmp_width < 256)
        {
            VPSS_ASSERT(meds_en == 0);
        }
        if (mcdi_en)
        {
            if (vpss_tmp_width > 960)
            {
                VPSS_ASSERT(meds_en == 1);
            }
        }
        //if(vpss_tmp_width>720) {VPSS_ASSERT(mcdi_en==0);}
        //if(vpss_tmp_height>576) {VPSS_ASSERT(mcdi_en==0);}
        VPSS_ASSERT(dei_lmmode == dei_cmmode);
        //VPSS_ASSERT((ppre_info_en ^ pre_info_en==1));
        VPSS_ASSERT(pre_info_en == 0);
        VPSS_ASSERT(ppre_info_en == 1);
        VPSS_ASSERT((mcstartr + mcendr) <= vpss_tmp_height / 2 - 1);
        VPSS_ASSERT((mcstartc + mcendc) <= vpss_tmp_width - 1);


        VPSS_ASSERT(nx1_y_addr != 0);
        VPSS_ASSERT(nx1_c_addr != 0);
        VPSS_ASSERT(cur_y_addr != 0);
        VPSS_ASSERT(cur_c_addr != 0);
        VPSS_ASSERT(ref_y_addr != 0);
        VPSS_ASSERT(ref_c_addr != 0);
        VPSS_ASSERT(dei_rst_addr != 0);
        VPSS_ASSERT(dei_wst_addr != 0);
        VPSS_ASSERT(dei_tmu_addr != 0);

        if (mcdi_en == 1)
        {
            VPSS_ASSERT(ree_y_addr != 0);
            VPSS_ASSERT(ree_c_addr != 0);

            VPSS_ASSERT(prjv_cur_addr != 0);
            VPSS_ASSERT(prjh_cur_addr != 0);
            VPSS_ASSERT(prjv_nx2_addr != 0);
            VPSS_ASSERT(prjh_nx2_addr != 0);
            VPSS_ASSERT(rgmv_cur_addr != 0);
            VPSS_ASSERT(rgmv_nx1_addr != 0);
            VPSS_ASSERT(rgmv_nx2_addr != 0);

            VPSS_ASSERT(blkmv_nx1_addr != 0);
            VPSS_ASSERT(blkmv_cur_addr != 0);
            VPSS_ASSERT(blkmv_ref_addr != 0);

            VPSS_ASSERT(blkmt_cur_addr != 0);
            VPSS_ASSERT(blkmt_ref_addr != 0);

            VPSS_ASSERT(cue_y_addr != 0);
            VPSS_ASSERT(cue_c_addr != 0);

            //VPSS_ASSERT(blkmv_nx2_addr != 0);

        }
    }
    if ((dei_en == 0) && (rotate_en == 0))
    {
        if (nx2_width > 1920)
        {
            VPSS_ASSERT(ram_bank == 5);
        }
        else if (in_pix_bitw == 0)
        {
            if (nx2_width <= 960)
            {
                VPSS_ASSERT(ram_bank == 2);
            }
            else
            {
                VPSS_ASSERT(ram_bank == 3);
            }
        }
        if (bfield == 1)
        {
            if (nx2_width > 1920)
            {
                VPSS_ASSERT(four_pix_en == 1);
            }
            vpss_tmp_height = vpss_tmp_height / 2;
        }
    }

    //SNR
    if (snr_en == 1)
    {
        //VPSS_ASSERT(nx2_vc1_en==0);
        //VPSS_ASSERT(nx1_vc1_en==0);
        //VPSS_ASSERT(cur_vc1_en==0);
        //VPSS_ASSERT(ref_vc1_en==0);
        //VPSS_ASSERT(tnr_en==0);
        //VPSS_ASSERT(dei_en==0);
        //VPSS_ASSERT(vpss_tmp_width <= 720);
        //VPSS_ASSERT(vpss_tmp_height <= 576);
        VPSS_ASSERT(in_pix_bitw == 0);
        VPSS_ASSERT(snr_tmu_addr != 0);
        if ((dei_en == 0) && (tnr_en == 0))
        {
            VPSS_ASSERT(snr_nr_en == 0);
        }
        if (tnr_en == 1)
        {
            VPSS_ASSERT(motion_mode == mad_mode);
        }
        //  VPSS_ASSERT((in_format!=0xb)&&(in_format!=0xc)&&(in_format!=0xd));
    }

    //DBM
    if (blk_det_en == 1)
    {
        VPSS_ASSERT(snr_en == 1);
        VPSS_ASSERT(db_en == 1);
    }
    if (blk_det_en == 0)
    {
        VPSS_ASSERT(det_hy_en == 0);
        VPSS_ASSERT(det_hc_en == 0);
        VPSS_ASSERT(det_vy_en == 0);
    }
    if (fmtc_en == 1)
    {
        VPSS_ASSERT(dei_en == 0);
    }

    //VMUX
    vpss_vhd0_tmp_width  = vpss_tmp_width ;//for size check
    vpss_vhd0_tmp_height = vpss_tmp_height;
    vpss_vhd0_tmp_format = vpss_tmp_format;

    //RTT
    if (rotate_en == 1)
    {

        //VPSS_ASSERT(ram_bank==4);
        VPSS_ASSERT(nx2_type == 0);
        VPSS_ASSERT(in_format < 0x5);
        VPSS_ASSERT(vhd0_en     == 1);
        VPSS_ASSERT(in_pix_bitw == 0);
        VPSS_ASSERT(vhd0_pix_bitw == 0); //8bit
        VPSS_ASSERT((img_pro_mode == 1) || (img_pro_mode == 2));
        VPSS_ASSERT(vhd0_format == 0);
        VPSS_ASSERT(nx2_vc1_en == 0);
        VPSS_ASSERT(nx1_vc1_en == 0);
        VPSS_ASSERT(cur_vc1_en == 0);
        VPSS_ASSERT(ref_vc1_en == 0);

        VPSS_ASSERT(bfield == 0);
        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);


        VPSS_ASSERT(vhd0_crop_en == 0);
        VPSS_ASSERT(vhd0_zme_en == 0);
        VPSS_ASSERT(vhd0_lba_en == 0);

        vpss_vhd0_tmp_width  = vpss_tmp_height ;//for size check
        vpss_vhd0_tmp_height = vpss_tmp_width;
        vpss_vhd0_tmp_format = 0;//420
    }
    else if (nx2_width > 1920)
    {
        VPSS_ASSERT(ram_bank == 5);
        VPSS_ASSERT(tnr_en == 0);
        VPSS_ASSERT(dei_en == 0);
        VPSS_ASSERT(snr_en == 0);
    }

    //VPZME

    //CROP
    if (vhd0_crop_en == 1)
    {
        VPSS_ASSERT(vhd0_crop_x + vhd0_crop_width  <= vpss_vhd0_tmp_width);
        VPSS_ASSERT(vhd0_crop_y + vhd0_crop_height <= vpss_vhd0_tmp_height);

        //if(four_pix_en==1)
        //{
        //    VPSS_ASSERT((vhd0_crop_x%4) == 0);
        //    VPSS_ASSERT((vhd0_crop_width%4) == 0);
        //}

        vpss_vhd0_tmp_width  = vhd0_crop_width ;
        vpss_vhd0_tmp_height = vhd0_crop_height;

    }

    //ZME
    if (vhd0_zme_en == 1)
    {
        VPSS_ASSERT(vpss_vhd0_tmp_width <= 4096);
        VPSS_ASSERT(vpss_vhd0_tmp_height <= 4096);

        VPSS_ASSERT(vhd0_zme_ow <= 1920);
        VPSS_ASSERT(vhd0_zme_oh <= 1080);

        //if(four_pix_en == 1)
        //    VPSS_ASSERT(vhd0_zme_ow%4 == 0);

        //VPSS_ASSERT(vhd0_hlmsc_en == 1);
        VPSS_ASSERT(vhd0_zme_order == 0);
        VPSS_ASSERT(vhd0_vlmsc_en == vhd0_vchmsc_en);
        VPSS_ASSERT(vhd0_hlmsc_en == vhd0_hchmsc_en);

        VPSS_ASSERT(vhd0_zme_tmu_addr != 0);
        if (vpss_vhd0_tmp_format != vhd0_format)
        {
            VPSS_ASSERT(vhd0_zme_en == 1);
            VPSS_ASSERT(vhd0_vlmsc_en == 1);
            VPSS_ASSERT(vhd0_vchmsc_en == 1);
        }

        vpss_vhd0_tmp_format = (vhd0_zme_outfmt == 1) ? 0 : 1;
        vpss_vhd0_tmp_width  = vhd0_zme_ow ;
        vpss_vhd0_tmp_height = vhd0_zme_oh;
    }

    //LBA
    if (vhd0_lba_en == 1)
    {
        VPSS_ASSERT((vhd0_lba_dis_width  >= vpss_vhd0_tmp_width + vhd0_lba_xfpos));
        VPSS_ASSERT((vhd0_lba_dis_height >= vpss_vhd0_tmp_height + vhd0_lba_yfpos));

        //if(four_pix_en==1)
        //{
        //    VPSS_ASSERT((vhd0_lba_xfpos%4) == 0);
        //    VPSS_ASSERT((vhd0_lba_dis_width%4) == 0);
        //}

        vpss_vhd0_tmp_width  = vhd0_lba_dis_width ;
        vpss_vhd0_tmp_height = vhd0_lba_dis_height;
    }

    //MIRROR
    if (vhd0_mirror == 1)
    {
        VPSS_ASSERT(cts_en == 0);
    }

    //VHD0
    //output tunnel
    if (vhd0_tunl_en == 1)
    {
        VPSS_ASSERT(vhd0_flip == 0);
    }
    VPSS_ASSERT(vhd0_format == vpss_vhd0_tmp_format);
    VPSS_ASSERT(vpss_vhd0_tmp_width  == vhd0_out_width);
    VPSS_ASSERT(vpss_vhd0_tmp_height == vhd0_out_height);
    if (cts_en == 1)
    {
        VPSS_ASSERT(vhd0_pix_bitw == 1);
        VPSS_ASSERT(four_pix_en == 1);
    }

    VPSS_HAL_Limit(vpss_reg);

    if (bErrFlag == HI_TRUE)
    {
        CBB_ERRMSG("VPSS VPSS_ASSERT at Node	 = %d\n", s32NodeId              );
        CBB_ERRMSG("bfield               = %d;\n", bfield              );
        CBB_ERRMSG("in_format            = %d;\n", in_format           );
        CBB_ERRMSG("nx2_offx             = %d;\n", nx2_offx            );
        CBB_ERRMSG("nx2_offy             = %d;\n", nx2_offy            );
        CBB_ERRMSG("nx1_offx             = %d;\n", nx1_offx            );
        CBB_ERRMSG("nx1_offy             = %d;\n", nx1_offy            );
        CBB_ERRMSG("cur_offx             = %d;\n", cur_offx            );
        CBB_ERRMSG("cur_offy             = %d;\n", cur_offy            );
        CBB_ERRMSG("ref_offx             = %d;\n", ref_offx            );
        CBB_ERRMSG("ref_offy             = %d;\n", ref_offy            );
        CBB_ERRMSG("cur_tunl_en          = %d;\n", cur_tunl_en         );
        CBB_ERRMSG("rotate_en            = %d;\n", rotate_en           );
        CBB_ERRMSG("vhd0_tunl_en         = %d;\n", vhd0_tunl_en        );
        CBB_ERRMSG("vhd0_flip            = %d;\n", vhd0_flip           );
        CBB_ERRMSG("four_pix_en          = %d;\n", four_pix_en         );
        CBB_ERRMSG("img_pro_mode         = %d;\n", img_pro_mode        );

        CBB_ERRMSG("cur_type             = %d;\n", cur_type            );
        CBB_ERRMSG("ref_type             = %d;\n", ref_type            );
        CBB_ERRMSG("nx1_type             = %d;\n", nx1_type            );
        CBB_ERRMSG("nx2_type             = %d;\n", nx2_type            );

        CBB_ERRMSG("nx2_dcmp_en          = %d;\n", nx2_dcmp_en         );
        CBB_ERRMSG("in_pix_bitw          = %d;\n", in_pix_bitw         );

        CBB_ERRMSG("nx2_width            = %d;\n", nx2_width           );
        CBB_ERRMSG("nx2_height           = %d;\n", nx2_height          );

        CBB_ERRMSG("ref_width            = %d;\n", ref_width           );
        CBB_ERRMSG("ref_height           = %d;\n", ref_height          );


        //CBB_ERRMSG("nx2_y_addr           = %d;\n",nx2_y_addr          );
        //CBB_ERRMSG("nx2_c_addr           = %d;\n",nx2_c_addr          );
        //CBB_ERRMSG("nx2_y_stride         = %d;\n",nx2_y_stride        );
        //CBB_ERRMSG("nx2_c_stride         = %d;\n",nx2_c_stride        );
        CBB_ERRMSG("nx2_y_head_addr      = %d;\n", nx2_y_head_addr     );
        CBB_ERRMSG("nx2_c_head_addr      = %d;\n", nx2_c_head_addr     );
        //CBB_ERRMSG("nx2_head_stride      = %d;\n",nx2_head_stride     );

        CBB_ERRMSG("nx1_y_addr           = %d;\n", nx1_y_addr          );
        CBB_ERRMSG("nx1_c_addr           = %d;\n", nx1_c_addr          );
        //CBB_ERRMSG("nx1_y_stride         = %d;\n",nx1_y_stride        );
        //CBB_ERRMSG("nx1_c_stride         = %d;\n",nx1_c_stride        );

        CBB_ERRMSG("cur_y_addr           = %d;\n", cur_y_addr          );
        CBB_ERRMSG("cur_c_addr           = %d;\n", cur_c_addr          );
        //CBB_ERRMSG("cur_y_stride         = %d;\n",cur_y_stride        );
        //CBB_ERRMSG("cur_c_stride         = %d;\n",cur_c_stride        );

        CBB_ERRMSG("ref_y_addr           = %d;\n", ref_y_addr          );
        CBB_ERRMSG("ref_c_addr           = %d;\n", ref_c_addr          );
        //CBB_ERRMSG("ref_y_stride         = %d;\n",ref_y_stride        );
        //CBB_ERRMSG("ref_c_stride         = %d;\n",ref_c_stride        );

        CBB_ERRMSG("ree_y_addr           = %d;\n", ree_y_addr          );
        CBB_ERRMSG("ree_c_addr           = %d;\n", ree_c_addr          );
        //CBB_ERRMSG("ree_y_stride         = %d;\n",ree_y_stride        );
        //CBB_ERRMSG("ree_c_stride         = %d;\n",ree_c_stride        );

        CBB_ERRMSG("prjv_cur_addr        = %d;\n", prjv_cur_addr       );
        CBB_ERRMSG("prjh_cur_addr        = %d;\n", prjh_cur_addr       );
        //CBB_ERRMSG("prjv_cur_stride      = %d;\n",prjv_cur_stride     );
        //CBB_ERRMSG("prjh_cur_stride      = %d;\n",prjh_cur_stride     );

        CBB_ERRMSG("rgmv_cur_addr        = %d;\n", rgmv_cur_addr       );
        //CBB_ERRMSG("rgmv_cur_stride      = %d;\n",rgmv_cur_stride     );
        CBB_ERRMSG("rgmv_nx1_addr        = %d;\n", rgmv_nx1_addr       );
        //CBB_ERRMSG("rgmv_nx1_stride      = %d;\n",rgmv_nx1_stride     );

        CBB_ERRMSG("blkmv_nx1_addr       = %d;\n", blkmv_nx1_addr      );
        //CBB_ERRMSG("blkmv_nx1_stride     = %d;\n",blkmv_nx1_stride    );
        CBB_ERRMSG("blkmv_cur_addr       = %d;\n", blkmv_cur_addr      );
        //CBB_ERRMSG("blkmv_cur_stride     = %d;\n",blkmv_cur_stride    );
        CBB_ERRMSG("blkmv_ref_addr       = %d;\n", blkmv_ref_addr      );
        //CBB_ERRMSG("blkmv_ref_stride     = %d;\n",blkmv_ref_stride    );

        CBB_ERRMSG("tnr_rmad_addr        = %d;\n", tnr_rmad_addr       );
        //CBB_ERRMSG("tnr_rmad_stride      = %d;\n",tnr_rmad_stride     );

        //CBB_ERRMSG("snr_rmad_addr        = %d;\n",snr_rmad_addr       );
        //CBB_ERRMSG("snr_rmad_stride      = %d;\n",snr_rmad_stride     );

        CBB_ERRMSG("dei_rst_addr         = %d;\n", dei_rst_addr        );
        //CBB_ERRMSG("dei_rst_stride       = %d;\n",dei_rst_stride      );

        //CBB_ERRMSG("vhd0_y_addr          = %d;\n",vhd0_y_addr         );
        //CBB_ERRMSG("vhd0_c_addr          = %d;\n",vhd0_c_addr         );
        //CBB_ERRMSG("vhd0_y_stride        = %d;\n",vhd0_y_stride       );
        //CBB_ERRMSG("vhd0_c_stride        = %d;\n",vhd0_c_stride       );

        CBB_ERRMSG("rfr_y_addr           = %d;\n", rfr_y_addr          );
        CBB_ERRMSG("rfr_c_addr           = %d;\n", rfr_c_addr          );
        CBB_ERRMSG("rfr_y_stride         = %d;\n", rfr_y_stride        );
        CBB_ERRMSG("rfr_c_stride         = %d;\n", rfr_c_stride        );

        CBB_ERRMSG("cue_y_addr           = %d;\n", cue_y_addr          );
        CBB_ERRMSG("cue_c_addr           = %d;\n", cue_c_addr          );
        //CBB_ERRMSG("cue_y_stride         = %d;\n",cue_y_stride        );
        //CBB_ERRMSG("cue_c_stride         = %d;\n",cue_c_stride        );

        CBB_ERRMSG("prjv_nx2_addr        = %d;\n", prjv_nx2_addr       );
        CBB_ERRMSG("prjh_nx2_addr        = %d;\n", prjh_nx2_addr       );
        //CBB_ERRMSG("prjv_nx2_stride      = %d;\n",prjv_nx2_stride     );
        //CBB_ERRMSG("prjh_nx2_stride      = %d;\n",prjh_nx2_stride     );

        //CBB_ERRMSG("blkmv_nx2_addr       = %d;\n",blkmv_nx2_addr      );
        //CBB_ERRMSG("blkmv_nx2_stride     = %d;\n",blkmv_nx2_stride    );

        CBB_ERRMSG("rgmv_nx2_addr        = %d;\n", rgmv_nx2_addr       );
        //CBB_ERRMSG("rgmv_nx2_stride      = %d;\n",rgmv_nx2_stride     );

        CBB_ERRMSG("tnr_wmad_addr        = %d;\n", tnr_wmad_addr       );
        //CBB_ERRMSG("tnr_wmad_stride      = %d;\n",tnr_wmad_stride     );

        CBB_ERRMSG("dei_wst_addr         = %d;\n", dei_wst_addr        );
        //CBB_ERRMSG("dei_wst_stride       = %d;\n",dei_wst_stride      );


        CBB_ERRMSG("nx2_vc1_en           = %d;\n", nx2_vc1_en          );
        CBB_ERRMSG("nx1_vc1_en           = %d;\n", nx1_vc1_en          );
        CBB_ERRMSG("cur_vc1_en           = %d;\n", cur_vc1_en          );
        CBB_ERRMSG("ref_vc1_en           = %d;\n", ref_vc1_en          );


        CBB_ERRMSG("tnr_mode             = %d;\n", tnr_mode            );
        CBB_ERRMSG("tnr_en               = %d;\n", tnr_en              );
        CBB_ERRMSG("rgme_en              = %d;\n", rgme_en             );
        CBB_ERRMSG("motionedgeen         = %d;\n", motionedgeen        );
        CBB_ERRMSG("motion_mode          = %d;\n", motion_mode         );
        CBB_ERRMSG("cbcrupdateen         = %d;\n", cbcrupdateen        );
        CBB_ERRMSG("ymotionmode          = %d;\n", ymotionmode         );
        CBB_ERRMSG("ymotioncalcmode      = %d;\n", ymotioncalcmode     );
        CBB_ERRMSG("cmotioncalcmode      = %d;\n", cmotioncalcmode     );
        CBB_ERRMSG("motionestimateen     = %d;\n", motionestimateen    );
        //CBB_ERRMSG("noisedetecten        = %d;\n",noisedetecten       );
        CBB_ERRMSG("tnr_tmu_addr         = %d;\n", tnr_tmu_addr        );


        CBB_ERRMSG("dei_en               = %d;\n", dei_en              );
        CBB_ERRMSG("mcdi_en              = %d;\n", mcdi_en             );
        CBB_ERRMSG("ifmd_en              = %d;\n", ifmd_en             );
        CBB_ERRMSG("igbm_en              = %d;\n", igbm_en             );
        CBB_ERRMSG("mcstartr             = %d;\n", mcstartr            );
        CBB_ERRMSG("mcstartc             = %d;\n", mcstartc            );
        CBB_ERRMSG("mcendr               = %d;\n", mcendr              );
        CBB_ERRMSG("mcendc               = %d;\n", mcendc              );
        CBB_ERRMSG("pre_info_en          = %d;\n", pre_info_en         );
        CBB_ERRMSG("ppre_info_en         = %d;\n", ppre_info_en        );
        CBB_ERRMSG("dei_lmmode           = %d;\n", dei_lmmode          );
        CBB_ERRMSG("dei_cmmode           = %d;\n", dei_cmmode          );
        CBB_ERRMSG("dei_tmu_addr         = %d;\n", dei_tmu_addr        );


        CBB_ERRMSG("snr_en               = %d;\n", snr_en              );
        CBB_ERRMSG("db_en                = %d;\n", db_en               );
        CBB_ERRMSG("blk_det_en           = %d;\n", blk_det_en          );
        CBB_ERRMSG("det_hy_en            = %d;\n", det_hy_en           );
        CBB_ERRMSG("det_hc_en            = %d;\n", det_hc_en           );
        CBB_ERRMSG("det_vy_en            = %d;\n", det_vy_en           );
        CBB_ERRMSG("snr_tmu_addr         = %d;\n", snr_tmu_addr        );

        CBB_ERRMSG("vhd0_crop_en         = %d;\n", vhd0_crop_en        );
        CBB_ERRMSG("vhd0_crop_x          = %d;\n", vhd0_crop_x         );
        CBB_ERRMSG("vhd0_crop_y          = %d;\n", vhd0_crop_y         );
        CBB_ERRMSG("vhd0_crop_width      = %d;\n", vhd0_crop_width     );
        CBB_ERRMSG("vhd0_crop_height     = %d;\n", vhd0_crop_height    );

        CBB_ERRMSG("vhd0_zme_en          = %d;\n", vhd0_zme_en         );
        CBB_ERRMSG("vhd0_zme_ow          = %d;\n", vhd0_zme_ow         );
        CBB_ERRMSG("vhd0_zme_oh          = %d;\n", vhd0_zme_oh         );
        CBB_ERRMSG("vhd0_hlmsc_en        = %d;\n", vhd0_hlmsc_en       );
        CBB_ERRMSG("vhd0_vlmsc_en        = %d;\n", vhd0_vlmsc_en       );
        CBB_ERRMSG("vhd0_hchmsc_en       = %d;\n", vhd0_hchmsc_en      );
        CBB_ERRMSG("vhd0_vchmsc_en       = %d;\n", vhd0_vchmsc_en      );
        CBB_ERRMSG("vhd0_zme_outfmt      = %d;\n", vhd0_zme_outfmt     );
        CBB_ERRMSG("vhd0_zme_tmu_addr    = %d;\n", vhd0_zme_tmu_addr   );

        CBB_ERRMSG("vhd0_lba_en          = %d;\n", vhd0_lba_en         );
        CBB_ERRMSG("vhd0_lba_dis_width   = %d;\n", vhd0_lba_dis_width  );
        CBB_ERRMSG("vhd0_lba_dis_height  = %d;\n", vhd0_lba_dis_height );
        CBB_ERRMSG("vhd0_lba_xfpos       = %d;\n", vhd0_lba_xfpos      );
        CBB_ERRMSG("vhd0_lba_yfpos       = %d;\n", vhd0_lba_yfpos      );

        CBB_ERRMSG("vhd0_en              = %d;\n", vhd0_en             );
        CBB_ERRMSG("vhd0_pix_bitw        = %d;\n", vhd0_pix_bitw       );
        CBB_ERRMSG("vhd0_format          = %d;\n", vhd0_format         );
        CBB_ERRMSG("vhd0_out_width       = %d;\n", vhd0_out_width      );
        CBB_ERRMSG("vhd0_out_height      = %d;\n", vhd0_out_height     );
    }


    VPSS_INFO ("vpss cfg constraint check end!\n");

#endif
}


