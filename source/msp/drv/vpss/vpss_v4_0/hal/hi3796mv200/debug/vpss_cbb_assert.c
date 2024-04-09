//#include <linux/io.h>
//#include <linux/delay.h>
#include "vpss_cbb_base.h"
#include "vpss_cbb_component.h"
#include "vpss_cbb_assert.h"

#if 0
#define ASSERT(n)      if(!(n)) { HI_PRINT("config error or something wrong ! LINE %d, FILE %s\n", __LINE__, __FILE__);}
#else
#define VPSS_ASSERT(ops) {\
        if(!(ops)) \
        {\
            bErrFlag = HI_TRUE;\
            VPSS_FATAL("ASSERT failed at: [%s] \n", #ops);\
        }}

#define ASSERT(ops)   VPSS_ASSERT(ops)
#endif

HI_VOID VPSS_HAL_Assert(HI_S32 s32NodeId, volatile S_VPSS_REGS_TYPE *vpss_reg)
{
    /*
        HI_BOOL bErrFlag            = HI_FALSE;
        HI_U32 vpss_tmp_width       = 0;//for size check
        HI_U32 vpss_tmp_height      = 0;
        HI_U32 vpss_tmp_format      = 0;
        HI_U32 vpss_vhd0_tmp_width  = 0;//for size check
        HI_U32 vpss_vhd0_tmp_height = 0;
        HI_U32 vpss_vhd0_tmp_format = 0;
        HI_U32 YC_422               = 0;
        //###################//
        //       GET REG CFG
        //###################//
        //MAC && BUS
        HI_U32 bfield              = vpss_reg->VPSS_CTRL.bits.bfield;
        HI_U32 bfield_mode         = vpss_reg->VPSS_CTRL.bits.bfield_mode;
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
        HI_U32 prot                = vpss_reg->VPSS_CTRL.bits.prot;
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
        HI_U32 nx2_y_addr          = vpss_reg->VPSS_NXT2YADDR.bits.nxt2y_addr;
        HI_U32 nx2_c_addr          = vpss_reg->VPSS_NXT2CADDR.bits.nxt2c_addr;
        HI_U32 nx2_y_stride        = vpss_reg->VPSS_NXT2STRIDE.bits.nxt2y_stride;
        HI_U32 nx2_c_stride        = vpss_reg->VPSS_NXT2STRIDE.bits.nxt2c_stride;
        HI_U32 nx2_y_head_addr     = vpss_reg->VPSS_NX2Y_HEAD_ADDR.bits.nx2y_top_head_addr;
        HI_U32 nx2_y_bot_head_addr = vpss_reg->VPSS_NX2Y_BOT_HEAD_ADDR.bits.nx2y_bot_head_addr;
        HI_U32 nx2_c_head_addr     = vpss_reg->VPSS_NX2C_HEAD_ADDR.bits.nx2c_top_head_addr;
        HI_U32 nx2_c_bot_head_addr = vpss_reg->VPSS_NX2C_BOT_HEAD_ADDR.bits.nx2c_bot_head_addr;
        HI_U32 nx2_head_stride     = vpss_reg->VPSS_NX2_HEAD_STRIDE.bits.nx2_head_stride;

        HI_U32 nx1_y_addr          = vpss_reg->VPSS_NXT1YADDR.bits.nxt1y_addr;
        HI_U32 nx1_c_addr          = vpss_reg->VPSS_NXT1CADDR.bits.nxt1c_addr;
        HI_U32 nx1_y_stride        = vpss_reg->VPSS_NXT1STRIDE.bits.nxt1y_stride;
        HI_U32 nx1_c_stride        = vpss_reg->VPSS_NXT1STRIDE.bits.nxt1c_stride;

        HI_U32 cur_y_addr          = vpss_reg->VPSS_CURYADDR.bits.cury_addr;
        HI_U32 cur_c_addr          = vpss_reg->VPSS_CURCADDR.bits.curc_addr;
        HI_U32 cur_y_stride        = vpss_reg->VPSS_CURSTRIDE.bits.cury_stride;
        HI_U32 cur_c_stride        = vpss_reg->VPSS_CURSTRIDE.bits.curc_stride;

        HI_U32 ref_y_addr          = vpss_reg->VPSS_REFYADDR.bits.refy_addr;
        HI_U32 ref_c_addr          = vpss_reg->VPSS_REFCADDR.bits.refc_addr;
        HI_U32 ref_y_stride        = vpss_reg->VPSS_REFSTRIDE.bits.refy_stride;
        HI_U32 ref_c_stride        = vpss_reg->VPSS_REFSTRIDE.bits.refc_stride;

        HI_U32 ree_y_addr          = vpss_reg->VPSS_REEYADDR.bits.reey_addr;
        HI_U32 ree_c_addr          = vpss_reg->VPSS_REECADDR.bits.reec_addr;
        HI_U32 ree_y_stride        = vpss_reg->VPSS_REESTRIDE.bits.reey_stride;
        HI_U32 ree_c_stride        = vpss_reg->VPSS_REESTRIDE.bits.reec_stride;

        HI_U32 prjv_cur_addr       = vpss_reg->VPSS_PRJVCURADDR.bits.prjv_cur_addr;
        HI_U32 prjh_cur_addr       = vpss_reg->VPSS_PRJHCURADDR.bits.prjh_cur_addr;
        HI_U32 prjv_cur_stride     = vpss_reg->VPSS_PRJCURSTRIDE.bits.prjv_cur_stride;
        HI_U32 prjh_cur_stride     = vpss_reg->VPSS_PRJCURSTRIDE.bits.prjh_cur_stride;

        HI_U32 rgmv_cur_addr       = vpss_reg->VPSS_RGMVCURADDR.bits.rgmv_cur_addr;
        HI_U32 rgmv_cur_stride     = vpss_reg->VPSS_RGMVSTRIDE.bits.rgmv_cur_stride;
        HI_U32 rgmv_nx1_addr       = vpss_reg->VPSS_RGMVNX1ADDR.bits.rgmv_nx1_addr;
        HI_U32 rgmv_nx1_stride     = vpss_reg->VPSS_RGMVSTRIDE.bits.rgmv_nx1_stride;

        HI_U32 blkmv_nx1_addr      = vpss_reg->VPSS_BLKMVNX1ADDR.bits.blkmv_nx1_addr;
        HI_U32 blkmv_nx1_stride    = vpss_reg->VPSS_BLKMVNX1STRIDE.bits.blkmv_nx1_stride;
        HI_U32 blkmv_cur_addr      = vpss_reg->VPSS_BLKMVCURADDR.bits.blkmv_cur_addr;
        HI_U32 blkmv_cur_stride    = vpss_reg->VPSS_BLKMVSTRIDE.bits.blkmv_cur_stride;
        HI_U32 blkmv_ref_addr      = vpss_reg->VPSS_BLKMVREFADDR.bits.blkmv_ref_addr;
        HI_U32 blkmv_ref_stride    = vpss_reg->VPSS_BLKMVSTRIDE.bits.blkmv_ref_stride;

        HI_U32 blkmt_cur_addr      = vpss_reg->VPSS_BLKMTCURADDR.bits.blkmt_cur_addr;
        HI_U32 blkmt_ref_addr      = vpss_reg->VPSS_BLKMTREFADDR.bits.blkmt_ref_addr;

        HI_U32 snr_rmad_addr       = vpss_reg->VPSS_SNR_MAD_RADDR.u32;
        HI_U32 snr_rmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;
        HI_U32 tnr_rmad_addr       = vpss_reg->VPSS_MAD_RADDR.bits.mad_raddr;
        HI_U32 tnr_rmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;

        HI_U32 dei_rst_addr        = vpss_reg->VPSS_STRADDR.u32;
        HI_U32 dei_rst_stride      = vpss_reg->VPSS_STSTRIDE.bits.st_stride;

        HI_U32 vhd0_y_addr         = vpss_reg->VPSS_VHD0YADDR.u32;
        HI_U32 vhd0_c_addr         = vpss_reg->VPSS_VHD0CADDR.u32;
        HI_U32 vhd0_y_stride       = vpss_reg->VPSS_VHD0STRIDE.bits.vhd0y_stride;
        HI_U32 vhd0_c_stride       = vpss_reg->VPSS_VHD0STRIDE.bits.vhd0c_stride;
        HI_U32 rfr_y_addr          = vpss_reg->VPSS_RFRYADDR.bits.rfry_addr;
        HI_U32 rfr_c_addr          = vpss_reg->VPSS_RFRCADDR.bits.rfrc_addr;
        HI_U32 rfr_y_stride        = vpss_reg->VPSS_RFRSTRIDE.bits.rfry_stride;
        HI_U32 rfr_c_stride        = vpss_reg->VPSS_RFRSTRIDE.bits.rfrc_stride;

        HI_U32 cue_y_addr          = vpss_reg->VPSS_CUEYADDR.u32;
        HI_U32 cue_c_addr          = vpss_reg->VPSS_CUECADDR.u32;
        HI_U32 cue_y_stride        = vpss_reg->VPSS_CUESTRIDE.bits.cuey_stride;
        HI_U32 cue_c_stride        = vpss_reg->VPSS_CUESTRIDE.bits.cuec_stride;

        HI_U32 prjv_nx2_addr       = vpss_reg->VPSS_PRJVNX2ADDR.u32;
        HI_U32 prjh_nx2_addr       = vpss_reg->VPSS_PRJHNX2ADDR.u32;
        HI_U32 prjv_nx2_stride     = vpss_reg->VPSS_PRJNX2STRIDE.bits.prjh_nx2_stride;
        HI_U32 prjh_nx2_stride     = vpss_reg->VPSS_PRJNX2STRIDE.bits.prjh_nx2_stride;

        HI_U32 blkmv_nx2_addr      = vpss_reg->VPSS_BLKMVNX1ADDR.u32;
        HI_U32 blkmv_nx2_stride    = vpss_reg->VPSS_BLKMVNX1STRIDE.bits.blkmv_nx1_stride;

        HI_U32 rgmv_nx2_addr       = vpss_reg->VPSS_RGMVNX2ADDR.u32;
        HI_U32 rgmv_nx2_stride     = vpss_reg->VPSS_RGMVNX2STRIDE.bits.rgmv_nx2_stride;

        HI_U32 tnr_wmad_addr       = vpss_reg->VPSS_MAD_WADDR.u32;
        HI_U32 tnr_wmad_stride     = vpss_reg->VPSS_MADSTRIDE.bits.mad_stride;

        HI_U32 dei_wst_addr        = vpss_reg->VPSS_STWADDR.u32;
        HI_U32 dei_wst_stride      = vpss_reg->VPSS_STSTRIDE.bits.st_stride;

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
        HI_U32 noisedetecten       = vpss_reg->VPSS_TNR_MAND_CTRL.bits.noisedetecten;
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

        //###################//
        //       PRINT REG CFG
        //###################//
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

        //###################//
        //       CHECK REG CFG
        //###################//
        //MAC && BUS
        //type/linear type
        if ((in_format == 0xb) || (in_format == 0xc) || (in_format == 0xd)) //package
        {
            ASSERT(cur_type == 0);
            ASSERT(ref_type == 0);
            ASSERT(nx1_type == 0);
            ASSERT(nx2_type == 0);
        }
        //if(bfield==1) {ASSERT(nx2_type == 0);}//hi3798mv200 linear field
        //DCMP
        if (nx2_dcmp_en == 1)
        {
            ASSERT(nx2_type == 1);
            ASSERT(nx2_y_head_addr != 0);
            ASSERT(nx2_c_head_addr != 0);
            ASSERT(nx2_y_bot_head_addr != 0);
            ASSERT(nx2_c_bot_head_addr != 0);
        }
        if (nx2_type == 0)
        {
            ASSERT(nxt2_tile_spec_field == 0);
        }
        //if(nx2_dcmp_en==1 || nx2_type==1)//hi3798mv200
        //{
        //    ASSERT(dei_en == 0);
        //    ASSERT(tnr_en == 0);
        //    ASSERT(snr_en == 0);
        //}
        //offset
        ASSERT((nx2_offx % 2) == 0);
        ASSERT((nx2_offy % 2) == 0);
        ASSERT((nx1_offx % 2) == 0);
        ASSERT((nx1_offy % 2) == 0);
        ASSERT((cur_offx % 2) == 0);
        ASSERT((cur_offy % 2) == 0);
        ASSERT((ref_offx % 2) == 0);
        ASSERT((ref_offy % 2) == 0);
        if (bfield == 1 && YC_422 == 0)
        {
            ASSERT((nx2_offy % 4) == 0);
            ASSERT((nx1_offy % 4) == 0);
            ASSERT((cur_offy % 4) == 0);
            ASSERT((ref_offy % 4) == 0);
        }
        if (in_format > 0x4)
        {
            ASSERT((nx2_offx == 0) && (nx2_offy == 0));
        }
        //width & height
        ASSERT(nx2_width  > 1);
        ASSERT(nx2_height > 1);
        if ((bfield == 1) && (YC_422 == 0)) //field in, offy is field's offsety. It should turn to frame's offsety.
        {
            ASSERT((nx2_height % 4) == 0);
        }
        //>FHD
        if ((nx2_width > 1920)) //||(nx2_height>1080))
        {
            ASSERT(nx2_vc1_en == 0);
            ASSERT(nx1_vc1_en == 0);
            ASSERT(cur_vc1_en == 0);
            ASSERT(ref_vc1_en == 0);

            ASSERT(tnr_en == 0);
            ASSERT(dei_en == 0);
            ASSERT(snr_en == 0);
            ASSERT(fmtc_en == 0);
            ASSERT(rfr_en == 0);
        }
        //4p/c
        if (four_pix_en == 1)
        {
            ASSERT((nx2_offx % 4) == 0);
            ASSERT((nx2_width % 4) == 0);
            ASSERT(in_format < 0x5);
            ASSERT(nx2_vc1_en == 0);
            ASSERT(nx1_vc1_en == 0);
            ASSERT(cur_vc1_en == 0);
            ASSERT(ref_vc1_en == 0);

            ASSERT(tnr_en == 0);
            ASSERT(dei_en == 0);
            ASSERT(snr_en == 0);
            ASSERT(fmtc_en == 0);
            ASSERT(rfr_en == 0);
        }
        //10bit
        if (in_pix_bitw == 1)
        {
            ASSERT(ram_bank == 6);
            if (cts_en)
            {
                ASSERT(four_pix_en == 1);
            }
            ASSERT(nx2_vc1_en == 0);
            ASSERT(nx1_vc1_en == 0);
            ASSERT(cur_vc1_en == 0);
            ASSERT(ref_vc1_en == 0);

            ASSERT(tnr_en == 0);
            ASSERT(dei_en == 0);
            ASSERT(snr_en == 0);
            ASSERT(fmtc_en == 0);
            ASSERT(rfr_en == 0);

            if (cts_en)
            {
                ASSERT(vhd0_crop_en == 0);
                ASSERT(vhd0_zme_en == 0);
                ASSERT(vhd0_lba_en == 0);
            }
        }
        ASSERT(vhd0_pix_bitw == in_pix_bitw);
        //input tunnel
        if (cur_tunl_en == 1)
        {
            ASSERT(rotate_en == 0);
            ASSERT(bfield == 0);
            ASSERT(in_format < 5);
            ASSERT((nx2_offx == 0) && (nx2_offy == 0));
        }

        //GET width height format
        vpss_tmp_width       = nx2_width;//for size check
        vpss_tmp_height      = nx2_height;
        vpss_tmp_format      = YC_422;

        //VC1
        if (nx2_vc1_en || nx1_vc1_en || cur_vc1_en || ref_vc1_en)
        {
            ASSERT((vpss_tmp_width % 16)  == 0);
            ASSERT(vpss_tmp_format  == 0);//only 420
            if (bfield == 1)
            {
                ASSERT((vpss_tmp_height % 32) == 0);
            }
            else
            {
                ASSERT((vpss_tmp_height % 16) == 0);
            }
        }

        //TNR
        if (tnr_en == 1)
        {
            //if(motion_mode==1) {ASSERT(vpss_tmp_width%4==0);}
            //if(vpss_tmp_width>720) {ASSERT(rgme_en==0);}//3798mv200 mcnr only support SD
            //if(vpss_tmp_height>576) {ASSERT(rgme_en==0);}

            ASSERT(vpss_tmp_width  == ref_width);
            ASSERT(vpss_tmp_height == ref_height);
            ASSERT(in_pix_bitw == 0);
            ASSERT(mcnr_en == 1);

            if (vpss_tmp_width < 128)
            {
                ASSERT(rgme_en == 0);
            }
            if (rgme_en)
            {
                if (vpss_tmp_width < 256)
                {
                    ASSERT(mcnr_meds_en == 0);
                }
                if (vpss_tmp_width > 960)
                {
                    ASSERT(mcnr_meds_en == 1);
                }
            }
            if (motion_mode == 1)
            {
                ASSERT(vpss_tmp_format == 1);
            }
            ASSERT(cur_y_addr != 0);
            ASSERT(cur_c_addr != 0);
            ASSERT(tnr_rmad_addr != 0);
            ASSERT(tnr_wmad_addr != 0);
            ASSERT(tnr_tmu_addr != 0);

            if (rgme_en == 1)
            {
                ASSERT(prjv_cur_addr != 0);
                ASSERT(prjh_cur_addr != 0);

                ASSERT(rgmv_cur_addr != 0);
                ASSERT(rgmv_nx1_addr != 0);

                ASSERT(prjv_nx2_addr != 0);
                ASSERT(prjh_nx2_addr != 0);

                ASSERT(rgmv_nx2_addr != 0);
            }

            if (vpss_tmp_format == 0) //while 420
            {
                ASSERT(cbcrupdateen == 0);
                ASSERT(ymotionmode  == 1);
            }

            ASSERT(ymotioncalcmode == 0);
            ASSERT(cmotioncalcmode == 0);

            //if(motion_mode==1)
            //{
            //    ASSERT(vpss_tmp_width%4 == 0);
            //    //ASSERT(vpss_tmp_width>720);//sharemotonen do no support SD size
            //}
            if (motionestimateen == 1)
            {
                ASSERT(rgme_en == 1);
            }
            //if(noisedetecten==1)
            //{
            //    ASSERT(vpss_tmp_width>=64 && vpss_tmp_width<=720);
            //}
        }
        if (rgme_en == 1)
        {
            ASSERT(tnr_en == 1);
        }
        if ((snr_en == 1) && (tnr_en == 0) && (bfield == 0))
        {
            ASSERT(motionedgeen == 0);
        }
        if (rfr_en == 1)
        {
            ASSERT(four_pix_en == 0);
            ASSERT(rfr_y_addr != 0);
            ASSERT(rfr_c_addr != 0);
            ASSERT(rfr_y_stride != 0);
            ASSERT(rfr_c_stride != 0);
        }

        //DEI
        //if (bfield == 1)   {ASSERT(dei_en == 1);}
        if (dei_en == 0)
        {
            ASSERT(ifmd_en == 0);
            ASSERT(igbm_en == 0);
            ASSERT(mcdi_en == 0);
        }//ASSERT(meds_en == 0);}
        if (dei_en == 1)
        {
            ASSERT(dei_lmmode == 1);
        }
        if (dei_en == 1)
        {
            ASSERT(tnr_mode == 0);
        }
        if (bfield == 1)
        {
            ASSERT((in_format != 0xb) && (in_format != 0xc) && (in_format != 0xd));
        }
        if (dei_en == 1)
        {
            ASSERT(nx2_width <= 1920);
            ASSERT(nx2_width >= 128);
            ASSERT(bfield == 1);
            ASSERT(in_pix_bitw == 0);
            if (nx2_width <= 960)
            {
                ASSERT(ram_bank == 0);
            }
            else
            {
                ASSERT(ram_bank == 1);
            }
            ASSERT(cts_en == 0);
            ASSERT(two_four_pxl_share == 0);
            ASSERT(vpss_tmp_width  == ref_width);
            ASSERT(vpss_tmp_height == ref_height);

            if (vpss_tmp_width < 128)
            {
                ASSERT(mcdi_en == 0);
            }
            if (vpss_tmp_width < 256)
            {
                ASSERT(meds_en == 0);
            }
            if (mcdi_en)
            {
                if (vpss_tmp_width > 960)
                {
                    ASSERT(meds_en == 1);
                }
            }
            //if(vpss_tmp_width>720) {ASSERT(mcdi_en==0);}
            //if(vpss_tmp_height>576) {ASSERT(mcdi_en==0);}
            ASSERT(dei_lmmode == dei_cmmode);
            //ASSERT((ppre_info_en ^ pre_info_en==1));
            ASSERT(pre_info_en == 0);
            ASSERT(ppre_info_en == 1);
            ASSERT((mcstartr + mcendr) <= vpss_tmp_height / 2 - 1);
            ASSERT((mcstartc + mcendc) <= vpss_tmp_width - 1);


            ASSERT(nx1_y_addr != 0);
            ASSERT(nx1_c_addr != 0);
            ASSERT(cur_y_addr != 0);
            ASSERT(cur_c_addr != 0);
            ASSERT(ref_y_addr != 0);
            ASSERT(ref_c_addr != 0);
            ASSERT(dei_rst_addr != 0);
            ASSERT(dei_wst_addr != 0);
            ASSERT(dei_tmu_addr != 0);

            if (mcdi_en == 1)
            {
                ASSERT(ree_y_addr != 0);
                ASSERT(ree_c_addr != 0);

                ASSERT(prjv_cur_addr != 0);
                ASSERT(prjh_cur_addr != 0);
                ASSERT(prjv_nx2_addr != 0);
                ASSERT(prjh_nx2_addr != 0);

                ASSERT(rgmv_cur_addr != 0);
                ASSERT(rgmv_nx1_addr != 0);
                ASSERT(rgmv_nx2_addr != 0);

                ASSERT(blkmv_nx1_addr != 0);
                ASSERT(blkmv_cur_addr != 0);
                ASSERT(blkmv_ref_addr != 0);

                ASSERT(blkmt_cur_addr != 0);
                ASSERT(blkmt_ref_addr != 0);

                ASSERT(cue_y_addr != 0);
                ASSERT(cue_c_addr != 0);

            }
        }
        if ((dei_en == 0) && (rotate_en == 0))
        {
            if (nx2_width > 1920)
            {
                // ASSERT(ram_bank==6); ////
            }
            else if (in_pix_bitw == 0)
            {
                if (nx2_width <= 960)
                {
                    ASSERT(ram_bank == 2);
                }
                else
                {
                    ASSERT(ram_bank == 3);
                }
            }
            if (bfield == 1)
            {
                if (nx2_width > 1920)
                {
                    ASSERT(four_pix_en == 1);
                }
                vpss_tmp_height = vpss_tmp_height / 2;
            }
        }

        //SNR
        if (snr_en == 1)
        {
            //ASSERT(nx2_vc1_en==0);
            //ASSERT(nx1_vc1_en==0);
            //ASSERT(cur_vc1_en==0);
            //ASSERT(ref_vc1_en==0);
            //ASSERT(tnr_en==0);
            //ASSERT(dei_en==0);
            //ASSERT(vpss_tmp_width <= 720);
            //ASSERT(vpss_tmp_height <= 576);
            ASSERT(in_pix_bitw == 0);
            ASSERT(snr_tmu_addr != 0);
            if ((dei_en == 0) && (tnr_en == 0))
            {
                ASSERT(snr_nr_en == 0);
            }
            if (tnr_en == 1)
            {
                ASSERT(motion_mode == mad_mode);
            }
            //  ASSERT((in_format!=0xb)&&(in_format!=0xc)&&(in_format!=0xd));
        }

        //DBM
        if (blk_det_en == 1)
        {
            ASSERT(snr_en == 1);
            ASSERT(db_en == 1);
        }
        if (blk_det_en == 0)
        {
            // ASSERT(det_hy_en == 0);
            ASSERT(det_hc_en == 0);
            ASSERT(det_vy_en == 0);
        }
        if (fmtc_en == 1)
        {
            ASSERT(dei_en == 0);
        }

        //VMUX
        vpss_vhd0_tmp_width  = vpss_tmp_width ;//for size check
        vpss_vhd0_tmp_height = vpss_tmp_height;
        vpss_vhd0_tmp_format = vpss_tmp_format;

        //RTT
        if (rotate_en == 1)
        {

            ASSERT(ram_bank == 4);
            ASSERT(nx2_type == 0);
            ASSERT(in_format < 0x5);
            ASSERT(vhd0_en     == 1);
            ASSERT(in_pix_bitw == 0);
            ASSERT(vhd0_pix_bitw == 0); //8bit
            ASSERT((img_pro_mode == 1) || (img_pro_mode == 2));
            ASSERT(vhd0_format == 0);
            ASSERT(nx2_vc1_en == 0);
            ASSERT(nx1_vc1_en == 0);
            ASSERT(cur_vc1_en == 0);
            ASSERT(ref_vc1_en == 0);

            ASSERT(bfield == 0);
            ASSERT(tnr_en == 0);
            ASSERT(dei_en == 0);
            ASSERT(snr_en == 0);


            ASSERT(vhd0_crop_en == 0);
            ASSERT(vhd0_zme_en == 0);
            ASSERT(vhd0_lba_en == 0);

            vpss_vhd0_tmp_width  = vpss_tmp_height ;//for size check
            vpss_vhd0_tmp_height = vpss_tmp_width;
            vpss_vhd0_tmp_format = 0;//420
        }
        else if (nx2_width > 1920)
        {
            //  ASSERT(ram_bank==6);
            ASSERT(tnr_en == 0);
            ASSERT(dei_en == 0);
            ASSERT(snr_en == 0);
        }


        //CROP
        if (vhd0_crop_en == 1)
        {
            ASSERT(vhd0_crop_x + vhd0_crop_width  <= vpss_vhd0_tmp_width);
            ASSERT(vhd0_crop_y + vhd0_crop_height <= vpss_vhd0_tmp_height);

            //if(four_pix_en==1)
            //{
            //    ASSERT((vhd0_crop_x%4) == 0);
            //    ASSERT((vhd0_crop_width%4) == 0);
            //}

            vpss_vhd0_tmp_width  = vhd0_crop_width ;
            vpss_vhd0_tmp_height = vhd0_crop_height;

        }

        //ZME
        if (vhd0_zme_en == 1)
        {
            ASSERT(vpss_vhd0_tmp_width <= 4096);
            ASSERT(vpss_vhd0_tmp_height <= 4096);

            ASSERT(vhd0_zme_ow <= 1920);
            //ASSERT(vhd0_zme_oh <= 1080);

            //if(four_pix_en == 1)
            //    ASSERT(vhd0_zme_ow%4 == 0);

            //ASSERT(vhd0_hlmsc_en == 1);
            ASSERT(vhd0_zme_order == 0);
            ASSERT(vhd0_vlmsc_en == vhd0_vchmsc_en);
            ASSERT(vhd0_hlmsc_en == vhd0_hchmsc_en);

            ASSERT(vhd0_zme_tmu_addr != 0);
            if (vpss_vhd0_tmp_format != vhd0_format)
            {
                ASSERT(vhd0_zme_en == 1);
                ASSERT(vhd0_vlmsc_en == 1);
                ASSERT(vhd0_vchmsc_en == 1);
            }

            vpss_vhd0_tmp_format = (vhd0_zme_outfmt == 1) ? 0 : 1;
            vpss_vhd0_tmp_width  = vhd0_zme_ow ;
            vpss_vhd0_tmp_height = vhd0_zme_oh;
        }

        //LBA
        if (vhd0_lba_en == 1)
        {
            ASSERT((vhd0_lba_dis_width  >= vpss_vhd0_tmp_width + vhd0_lba_xfpos));
            ASSERT((vhd0_lba_dis_height >= vpss_vhd0_tmp_height + vhd0_lba_yfpos));

            //if(four_pix_en==1)
            //{
            //    ASSERT((vhd0_lba_xfpos%4) == 0);
            //    ASSERT((vhd0_lba_dis_width%4) == 0);
            //}

            vpss_vhd0_tmp_width  = vhd0_lba_dis_width ;
            vpss_vhd0_tmp_height = vhd0_lba_dis_height;
        }

        //MIRROR
        if (vhd0_mirror == 1)
        {
            ASSERT(cts_en == 0);
        }

        //VHD0
        //output tunnel
        if (vhd0_tunl_en == 1)
        {
            ASSERT(vhd0_flip == 0);
        }
        ASSERT(vhd0_format == vpss_vhd0_tmp_format);
        ASSERT(vpss_vhd0_tmp_width  == vhd0_out_width);
        ASSERT(vpss_vhd0_tmp_height == vhd0_out_height);
        if (cts_en == 1)
        {
            ASSERT(vhd0_pix_bitw == 1);
            ASSERT(four_pix_en == 1);
        }


        if (HI_TRUE == bErrFlag)
        {
            if (HI_TRUE == bErrFlag)
            {
                HI_PRINT("\n###############\nVPSS Assert at Node = %d\n###############\n", s32NodeId);
            }
            else// (HI_TRUE == bForcePrintInfo)
            {
                HI_PRINT("\n###############\nVPSS Node(%d) Info\n###############\n", s32NodeId);
            }


            HI_PRINT("bfield               = %d;\n", bfield              );
            HI_PRINT("bfield_mode          = %d;\n", bfield_mode         );
            HI_PRINT("bSecurity            = %d;\n", prot                );


            HI_PRINT("in_format            = %d;\n", in_format           );
            HI_PRINT("nx2_offx             = %d;\n", nx2_offx            );
            HI_PRINT("nx2_offy             = %d;\n", nx2_offy            );
            HI_PRINT("nx1_offx             = %d;\n", nx1_offx            );
            HI_PRINT("nx1_offy             = %d;\n", nx1_offy            );
            HI_PRINT("cur_offx             = %d;\n", cur_offx            );
            HI_PRINT("cur_offy             = %d;\n", cur_offy            );
            HI_PRINT("ref_offx             = %d;\n", ref_offx            );
            HI_PRINT("ref_offy             = %d;\n", ref_offy            );
            HI_PRINT("cur_tunl_en          = %d;\n", cur_tunl_en         );
            HI_PRINT("rotate_en            = %d;\n", rotate_en           );
            HI_PRINT("vhd0_tunl_en         = %d;\n", vhd0_tunl_en        );
            HI_PRINT("vhd0_flip            = %d;\n", vhd0_flip           );
            HI_PRINT("four_pix_en          = %d;\n", four_pix_en         );
            HI_PRINT("img_pro_mode         = %d;\n", img_pro_mode        );

            HI_PRINT("cur_type             = %d;\n", cur_type            );
            HI_PRINT("ref_type             = %d;\n", ref_type            );
            HI_PRINT("nx1_type             = %d;\n", nx1_type            );
            HI_PRINT("nx2_type             = %d;\n", nx2_type            );

            HI_PRINT("nx2_dcmp_en          = %d;\n", nx2_dcmp_en         );
            HI_PRINT("in_pix_bitw          = %d;\n", in_pix_bitw         );

            HI_PRINT("nx2_width            = %d;\n", nx2_width           );
            HI_PRINT("nx2_height           = %d;\n", nx2_height          );

            HI_PRINT("ram_bank             = %d;\n", ram_bank            );

            HI_PRINT("ref_width            = %d;\n", ref_width           );
            HI_PRINT("ref_height           = %d;\n", ref_height          );


            HI_PRINT("nx2_y_addr           = %x;\n", nx2_y_addr          );
            HI_PRINT("nx2_c_addr           = %x;\n", nx2_c_addr          );
            HI_PRINT("nx2_y_stride         = %d;\n", nx2_y_stride        );
            HI_PRINT("nx2_c_stride         = %d;\n", nx2_c_stride        );
            HI_PRINT("nx2_y_head_addr      = %x;\n", nx2_y_head_addr     );
            HI_PRINT("nx2_c_head_addr      = %x;\n", nx2_c_head_addr     );
            HI_PRINT("nx2_head_stride      = %d;\n", nx2_head_stride     );

            HI_PRINT("nx1_y_addr           = %x;\n", nx1_y_addr          );
            HI_PRINT("nx1_c_addr           = %x;\n", nx1_c_addr          );
            HI_PRINT("nx1_y_stride         = %d;\n", nx1_y_stride        );
            HI_PRINT("nx1_c_stride         = %d;\n", nx1_c_stride        );

            HI_PRINT("cur_y_addr           = %x;\n", cur_y_addr          );
            HI_PRINT("cur_c_addr           = %x;\n", cur_c_addr          );
            HI_PRINT("cur_y_stride         = %d;\n", cur_y_stride        );
            HI_PRINT("cur_c_stride         = %d;\n", cur_c_stride        );

            HI_PRINT("ref_y_addr           = %x;\n", ref_y_addr          );
            HI_PRINT("ref_c_addr           = %x;\n", ref_c_addr          );
            HI_PRINT("ref_y_stride         = %d;\n", ref_y_stride        );
            HI_PRINT("ref_c_stride         = %d;\n", ref_c_stride        );

            HI_PRINT("ree_y_addr           = %x;\n", ree_y_addr          );
            HI_PRINT("ree_c_addr           = %x;\n", ree_c_addr          );
            HI_PRINT("ree_y_stride         = %d;\n", ree_y_stride        );
            HI_PRINT("ree_c_stride         = %d;\n", ree_c_stride        );

            HI_PRINT("prjv_cur_addr        = %x;\n", prjv_cur_addr       );
            HI_PRINT("prjh_cur_addr        = %x;\n", prjh_cur_addr       );
            HI_PRINT("prjv_cur_stride      = %d;\n", prjv_cur_stride     );
            HI_PRINT("prjh_cur_stride      = %d;\n", prjh_cur_stride     );

            HI_PRINT("rgmv_cur_addr        = %x;\n", rgmv_cur_addr       );
            HI_PRINT("rgmv_cur_stride      = %d;\n", rgmv_cur_stride     );
            HI_PRINT("rgmv_nx1_addr        = %x;\n", rgmv_nx1_addr       );
            HI_PRINT("rgmv_nx1_stride      = %d;\n", rgmv_nx1_stride     );

            HI_PRINT("blkmv_nx1_addr       = %x;\n", blkmv_nx1_addr      );
            HI_PRINT("blkmv_nx1_stride     = %d;\n", blkmv_nx1_stride    );
            HI_PRINT("blkmv_cur_addr       = %x;\n", blkmv_cur_addr      );
            HI_PRINT("blkmv_cur_stride     = %d;\n", blkmv_cur_stride    );
            HI_PRINT("blkmv_ref_addr       = %x;\n", blkmv_ref_addr      );
            HI_PRINT("blkmv_ref_stride     = %d;\n", blkmv_ref_stride    );

            HI_PRINT("tnr_rmad_addr        = %d;\n", tnr_rmad_addr       );
            HI_PRINT("tnr_rmad_stride      = %d;\n", tnr_rmad_stride     );

            HI_PRINT("snr_rmad_addr        = %x;\n", snr_rmad_addr       );
            HI_PRINT("snr_rmad_stride      = %d;\n", snr_rmad_stride     );

            HI_PRINT("dei_rst_addr         = %x;\n", dei_rst_addr        );
            HI_PRINT("dei_rst_stride       = %d;\n", dei_rst_stride      );

            HI_PRINT("vhd0_y_addr          = %x;\n", vhd0_y_addr         );
            HI_PRINT("vhd0_c_addr          = %x;\n", vhd0_c_addr         );
            HI_PRINT("vhd0_y_stride        = %d;\n", vhd0_y_stride       );
            HI_PRINT("vhd0_c_stride        = %d;\n", vhd0_c_stride       );

            HI_PRINT("rfr_y_addr           = %x;\n", rfr_y_addr          );
            HI_PRINT("rfr_c_addr           = %x;\n", rfr_c_addr          );
            HI_PRINT("rfr_y_stride         = %d;\n", rfr_y_stride        );
            HI_PRINT("rfr_c_stride         = %d;\n", rfr_c_stride        );

            HI_PRINT("cue_y_addr           = %x;\n", cue_y_addr          );
            HI_PRINT("cue_c_addr           = %x;\n", cue_c_addr          );
            HI_PRINT("cue_y_stride         = %d;\n", cue_y_stride        );
            HI_PRINT("cue_c_stride         = %d;\n", cue_c_stride        );

            HI_PRINT("prjv_nx2_addr        = %x;\n", prjv_nx2_addr       );
            HI_PRINT("prjh_nx2_addr        = %x;\n", prjh_nx2_addr       );
            HI_PRINT("prjv_nx2_stride      = %d;\n", prjv_nx2_stride     );
            HI_PRINT("prjh_nx2_stride      = %d;\n", prjh_nx2_stride     );

            HI_PRINT("blkmv_nx2_addr       = %x;\n", blkmv_nx2_addr      );
            HI_PRINT("blkmv_nx2_stride     = %d;\n", blkmv_nx2_stride    );

            HI_PRINT("rgmv_nx2_addr        = %x;\n", rgmv_nx2_addr       );
            HI_PRINT("rgmv_nx2_stride      = %d;\n", rgmv_nx2_stride     );

            HI_PRINT("tnr_wmad_addr        = %x;\n", tnr_wmad_addr       );
            HI_PRINT("tnr_wmad_stride      = %d;\n", tnr_wmad_stride     );

            HI_PRINT("dei_wst_addr         = %x;\n", dei_wst_addr        );
            HI_PRINT("dei_wst_stride       = %d;\n", dei_wst_stride      );


            HI_PRINT("nx2_vc1_en           = %d;\n", nx2_vc1_en          );
            HI_PRINT("nx1_vc1_en           = %d;\n", nx1_vc1_en          );
            HI_PRINT("cur_vc1_en           = %d;\n", cur_vc1_en          );
            HI_PRINT("ref_vc1_en           = %d;\n", ref_vc1_en          );


            HI_PRINT("tnr_mode             = %d;\n", tnr_mode            );
            HI_PRINT("tnr_en               = %d;\n", tnr_en              );
            HI_PRINT("rgme_en              = %d;\n", rgme_en             );
            HI_PRINT("motionedgeen         = %d;\n", motionedgeen        );
            //       HI_PRINT("sharemotionen        = %d;\n",sharemotionen       );
            HI_PRINT("cbcrupdateen         = %d;\n", cbcrupdateen        );
            HI_PRINT("ymotionmode          = %d;\n", ymotionmode         );
            HI_PRINT("ymotioncalcmode      = %d;\n", ymotioncalcmode     );
            HI_PRINT("cmotioncalcmode      = %d;\n", cmotioncalcmode     );
            HI_PRINT("motionestimateen     = %d;\n", motionestimateen    );
            HI_PRINT("noisedetecten        = %d;\n", noisedetecten       );
            HI_PRINT("tnr_tmu_addr         = %x;\n", tnr_tmu_addr        );


            HI_PRINT("dei_en               = %d;\n", dei_en              );
            HI_PRINT("mcdi_en              = %d;\n", mcdi_en             );
            HI_PRINT("ifmd_en              = %d;\n", ifmd_en             );
            HI_PRINT("igbm_en              = %d;\n", igbm_en             );
            HI_PRINT("mcstartr             = %d;\n", mcstartr            );
            HI_PRINT("mcstartc             = %d;\n", mcstartc            );
            HI_PRINT("mcendr               = %d;\n", mcendr              );
            HI_PRINT("mcendc               = %d;\n", mcendc              );
            HI_PRINT("pre_info_en          = %d;\n", pre_info_en         );
            HI_PRINT("ppre_info_en         = %d;\n", ppre_info_en        );
            HI_PRINT("dei_lmmode           = %d;\n", dei_lmmode          );
            HI_PRINT("dei_cmmode           = %d;\n", dei_cmmode          );
            HI_PRINT("dei_tmu_addr         = %x;\n", dei_tmu_addr        );


            HI_PRINT("snr_en               = %d;\n", snr_en              );
            HI_PRINT("db_en                = %d;\n", db_en               );
            HI_PRINT("blk_det_en           = %d;\n", blk_det_en          );
            HI_PRINT("det_hy_en            = %d;\n", det_hy_en           );
            HI_PRINT("det_hc_en            = %d;\n", det_hc_en           );
            HI_PRINT("det_vy_en            = %d;\n", det_vy_en           );
            HI_PRINT("snr_tmu_addr         = %x;\n", snr_tmu_addr        );


            //       HI_PRINT("vhd0_pre_vfir_en     = %d;\n",vhd0_pre_vfir_en    );
            //       HI_PRINT("vhd0_pre_vfir_mode   = %d;\n",vhd0_pre_vfir_mode  );

            HI_PRINT("vhd0_crop_en         = %d;\n", vhd0_crop_en        );
            HI_PRINT("vhd0_crop_x          = %d;\n", vhd0_crop_x         );
            HI_PRINT("vhd0_crop_y          = %d;\n", vhd0_crop_y         );
            HI_PRINT("vhd0_crop_width      = %d;\n", vhd0_crop_width     );
            HI_PRINT("vhd0_crop_height     = %d;\n", vhd0_crop_height    );

            HI_PRINT("vhd0_zme_en          = %d;\n", vhd0_zme_en         );
            HI_PRINT("vhd0_zme_ow          = %d;\n", vhd0_zme_ow         );
            HI_PRINT("vhd0_zme_oh          = %d;\n", vhd0_zme_oh         );
            HI_PRINT("vhd0_hlmsc_en        = %d;\n", vhd0_hlmsc_en       );
            HI_PRINT("vhd0_vlmsc_en        = %d;\n", vhd0_vlmsc_en       );
            HI_PRINT("vhd0_hchmsc_en       = %d;\n", vhd0_hchmsc_en      );
            HI_PRINT("vhd0_vchmsc_en       = %d;\n", vhd0_vchmsc_en      );
            HI_PRINT("vhd0_zme_outfmt      = %d;\n", vhd0_zme_outfmt     );
            HI_PRINT("vhd0_zme_tmu_addr    = %x;\n", vhd0_zme_tmu_addr   );

            HI_PRINT("vhd0_lba_en          = %d;\n", vhd0_lba_en         );
            HI_PRINT("vhd0_lba_dis_width   = %d;\n", vhd0_lba_dis_width  );
            HI_PRINT("vhd0_lba_dis_height  = %d;\n", vhd0_lba_dis_height );
            HI_PRINT("vhd0_lba_xfpos       = %d;\n", vhd0_lba_xfpos      );
            HI_PRINT("vhd0_lba_yfpos       = %d;\n", vhd0_lba_yfpos      );

            HI_PRINT("vhd0_en              = %d;\n", vhd0_en             );
            HI_PRINT("vhd0_pix_bitw        = %d;\n", vhd0_pix_bitw       );
            HI_PRINT("vhd0_format          = %d;\n", vhd0_format         );
            HI_PRINT("vhd0_out_width       = %d;\n", vhd0_out_width      );
            HI_PRINT("vhd0_out_height      = %d;\n", vhd0_out_height     );
        }
    */



}



