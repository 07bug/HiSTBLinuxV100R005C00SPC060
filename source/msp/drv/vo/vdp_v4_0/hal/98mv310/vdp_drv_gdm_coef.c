
#include "vdp_gen_coef.h"
#include "vdp_define.h"
#include "vdp_drv_comm.h"
#include "drv_pq_ext.h"
#include "vdp_drv_gdm_coef.h"
#include "vdp_hal_ip_hihdr_g.h"

extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;


HI_VOID Vdp_Drv_SetGdmCoef_Tmmp(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    VDP_DRV_COEF_SEND_CFG   stCoefSend;
    HI_U8*                  addr = 0;

    FILE*                   fp_hihdr_g_coef_tmap   = NULL;
    HI_S32 tcLut_s32_1[32];
    void  *p_coef_array[]    = {tcLut_s32_1};

    HI_U32                  lut_length[1]      = {32};
    HI_U32                  coef_bit_length[1] = {16};

    HI_S32 *pu32LutTmp = HI_NULL ;
    pu32LutTmp = (HI_S32 *)pstPqGfxHdrCfg->stTMAP.pu32LUTTM;

    if (HI_NULL == pu32LutTmp)
    {
        VDP_PRINT("stTMAP.pu32LUTTM is NULL!\n");
        return;
    }
    p_coef_array[0]    = (HI_S32 *)pstPqGfxHdrCfg->stTMAP.pu32LUTTM;

    addr  = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_TMP];

    stCoefSend.coef_addr         = addr                     ;
    stCoefSend.sti_type          = STI_FILE_COEF_HIHDR_G        ;
    stCoefSend.fp_coef           = fp_hihdr_g_coef_tmap                ;
    stCoefSend.lut_num           = 1                                    ;
    stCoefSend.burst_num         = 1                           ;
    stCoefSend.cycle_num         = 8                            ;
    stCoefSend.p_coef_array      = p_coef_array                        ;
    stCoefSend.lut_length        = lut_length                             ;
    stCoefSend.coef_bit_length   = coef_bit_length                       ;
    stCoefSend.data_type         = DRV_COEF_DATA_TYPE_U32         ;

    addr = VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_G_SetTmpCoefAddr ( gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_TMP]);
    VDP_HIHDR_G_SetTmpParaUpd     (1);

}


HI_VOID Vdp_Drv_SetGdmCoef_Gmma(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{

    VDP_DRV_COEF_SEND_CFG stCoefSend;
    HI_U8* addr = 0;

    FILE* fp_hihdr_g_coef_gmm = NULL;
    HI_S32 tcLut_s32_1[32];
    void *p_coef_array[] = {tcLut_s32_1};

    HI_U32 lut_length[1] = {64};
    HI_U32 coef_bit_length[1] = {12};

    HI_S32 *pu32LutTmp = HI_NULL ;
    pu32LutTmp = (HI_S32 *)pstPqGfxHdrCfg->stGmm.pu32LUT;

    if (HI_NULL == pu32LutTmp)
    {
    VDP_PRINT("stGmm.pu32LUT is NULL!\n");
    return;
    }
    p_coef_array[0] = (HI_S32 *)pstPqGfxHdrCfg->stGmm.pu32LUT;

    addr = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_G_GMM];

    stCoefSend.coef_addr = addr ;
    stCoefSend.sti_type = STI_FILE_COEF_HIHDR_G ;
    stCoefSend.fp_coef = fp_hihdr_g_coef_gmm ;
    stCoefSend.lut_num = 1 ;
    stCoefSend.burst_num = 1 ;
    stCoefSend.cycle_num = 10 ;
    stCoefSend.p_coef_array = p_coef_array ;
    stCoefSend.lut_length = lut_length ;
    stCoefSend.coef_bit_length = coef_bit_length ;
    stCoefSend.data_type = DRV_COEF_DATA_TYPE_U32 ;

    addr = VDP_DRV_SendCoef(&stCoefSend);
    VDP_HIHDR_G_SetGmmCoefAddr ( gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_HIHDR_G_GMM]);
    VDP_HIHDR_G_SetGmmParaUpd (1);

    return;
}





