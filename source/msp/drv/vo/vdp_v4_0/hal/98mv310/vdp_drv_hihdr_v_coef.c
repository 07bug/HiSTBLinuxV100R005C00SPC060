#include "vdp_drv_hihdr_v_coef.h"

extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;
#if CBB_CFG_FROM_PQ
#else
/************* DeGamma Luts **************/
extern HI_U32 u32DeGmmLut_PQ[64];
// DeHLG Curve: BBC HDR
extern HI_U32 u32DeGmmLut_HLG[64];
// DeSLF Curve: AVS HDR
extern HI_U32 u32DeGmmLut_SLF[64];
// DeGamma Curve: SDR
extern HI_U32 u32DeGmmLut_24[64];
// DeHisi Curve: Hisi HDR
extern HI_U32 u32DeHisiLut[64];
extern HI_U32 u32DeGmmLut_xvYCC[64];

/************* ToneMapping Luts **************/
// ToneMapping Lut: Default
extern HI_U32 u32TMLut[64];
// ToneMapping Lut: HDR10  to SDR
extern HI_U32 u32TMLut_HDR2SDR[64];
// ToneMapping Lut: TCHDR to HDR10  to SDR
extern HI_U32 u32TMLutTCHDR2HDR102SDR[64];
// ToneMapping Lut: AVS to SDR
extern HI_U32 u32TMLut_SLF2SDR[64];
// ToneMapping Lut: AVS to HDR10
extern HI_U32 u32TMLutAVS2HDR10[64];
// ToneMapping Lut: HDR10 to HLG
extern HI_U32 u32TMLut_HDR2HLG[64] ;
extern HI_U32 u32TMLut_SDR2HLG[64];
extern HI_U32 u32TMLut_SDR2HDR[64];
// ToneMapping Lut: AVS to HDR10
extern HI_U32 u32TMLut_Linear[64];
// ToneMapping Lut: BBC to HDR10
extern HI_U32 u32TMLut_HLG2HDR[64];
// ToneMapping Lut: BBC to SDR
extern HI_U32 u32TMLut_HLG2SDR[64];
// ToneMapping Lut: Hisi to HDR10
extern HI_U32 u32TMLutHisi2HDR10[32];

/************* Smap Luts **************/
extern HI_U32 u32SMLut_HDR2SDR[32];
extern HI_U32 u32SMLut_Linear[32];
extern HI_U32 u32SMLutAVS2SDR[64];

/************* Gamma Luts **************/
extern HI_U32 u32GmmLut0[64];
//Gmm-8 Lut Params
extern HI_U32 u32GmmLut_PQ10000[64];
extern HI_U32 u32GmmLut_PQ1000[64];
extern HI_U32 u32PQLut[64];
//HLG Curve
extern HI_U32 u32GmmLut_HLG[64];
//Gamma Curve
extern HI_U32 u32GmmLut_22[64];
extern HI_U32 u32GmmLut_24[64];
#endif

HI_U32 u32Lutd[128];
HI_U32 u32Luts[128];

HI_S32 VDP_DRV_SendHiHdrVCoef(HI_U32 * plutd,HI_U32 * pluts)
{
    VDP_DRV_COEF_SEND_CFG   stCoefSend;
    HI_U8*                  addr = 0;
    HI_U8*                  addr1 = 0;

    FILE*                   fp_hihdr_v_coef_d   = NULL;
    FILE*                   fp_hihdr_v_coef_s   = NULL;
	void*                   p_coef_array[1]    = {plutd};
	HI_U32                  lut_length[1]      = {64};
	HI_U32                  coef_bit_length[1] = {16};

    addr = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_D];
    addr1 = gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_HIHDR_V_S];

	//tonemapping lut : 64x16
	stCoefSend.coef_addr         = addr                   ;
	stCoefSend.sti_type          = STI_FILE_COEF_HIHDR_V  ;
	stCoefSend.fp_coef           = fp_hihdr_v_coef_d      ;
	stCoefSend.lut_num           = 1                      ;
	stCoefSend.burst_num         = 1                      ;
	stCoefSend.cycle_num         = 8                      ;
	stCoefSend.p_coef_array      = p_coef_array           ;
	stCoefSend.lut_length        = lut_length             ;
	stCoefSend.coef_bit_length   = coef_bit_length        ;
	stCoefSend.data_type         = DRV_COEF_DATA_TYPE_U32 ;
	addr = VDP_DRV_SendCoef(&stCoefSend)                  ;

	//saturation mapping lut : 64x10
	p_coef_array[0]    = plutd+64                         ;
	lut_length[0]      = 32;//64                          ;
	coef_bit_length[0] = 10                               ;
    stCoefSend.coef_addr         = addr                   ;
	stCoefSend.p_coef_array      = p_coef_array           ;
	stCoefSend.lut_length        = lut_length             ;
	stCoefSend.coef_bit_length   = coef_bit_length        ;
	stCoefSend.data_type         = DRV_COEF_DATA_TYPE_U32 ;
	addr = VDP_DRV_SendCoef(&stCoefSend)                  ;


	//degamma lut : 64x21
	p_coef_array[0]    = pluts                            ;
	lut_length[0]      = 64                               ;
	coef_bit_length[0] = 21                               ;
	stCoefSend.fp_coef           = fp_hihdr_v_coef_s      ;
	stCoefSend.coef_addr         = addr1                  ;
	stCoefSend.cycle_num         = 6                      ;
	stCoefSend.p_coef_array      = p_coef_array           ;
	stCoefSend.lut_length        = lut_length             ;
	stCoefSend.coef_bit_length   = coef_bit_length        ;
	stCoefSend.data_type         = DRV_COEF_DATA_TYPE_U32 ;
	addr1 = VDP_DRV_SendCoef(&stCoefSend)                 ;

	//gamma lut : 64x12
	p_coef_array[0]    = pluts+64                         ;
	lut_length[0]      = 64                               ;
	coef_bit_length[0] = 12                               ;
	stCoefSend.fp_coef           = fp_hihdr_v_coef_s      ;
	stCoefSend.coef_addr         = addr1                  ;
	stCoefSend.cycle_num         = 10                     ;
	stCoefSend.p_coef_array      = p_coef_array           ;
	stCoefSend.lut_length        = lut_length             ;
	stCoefSend.coef_bit_length   = coef_bit_length        ;
	stCoefSend.data_type         = DRV_COEF_DATA_TYPE_U32 ;
	addr1 = VDP_DRV_SendCoef(&stCoefSend)                 ;

    return HI_SUCCESS;
}

HI_VOID VDP_DRV_SetHdrVCoef(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg)
{
    VDP_DRV_COEF_GEN_CFG   stCoefGen;

    HI_VOID * pDegammaLut;
    HI_VOID * pToneMapLut;
    HI_VOID * pSMapLut;
    HI_VOID * pGammaLut;

#if CBB_CFG_FROM_PQ
    pToneMapLut     = (HI_VOID *) pstHiHdrCfg->stTMAP.pu32LUTTM;
    pSMapLut        = (HI_VOID *) pstHiHdrCfg->stSMAP.pu32LUTSM;
    pDegammaLut     = (HI_VOID *) pstHiHdrCfg->stDeGmm.pu32LUT;
    pGammaLut       = (HI_VOID *) pstHiHdrCfg->stGmm.pu32LUT;
#else
    if(enHiHdrMode == HIHDR_HDR10_IN_SDR_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_HDR10_IN_SDR_OUT!\n");
        pToneMapLut     = u32TMLut_HDR2SDR;
        pSMapLut        = u32SMLut_HDR2SDR;
        pDegammaLut     = u32DeGmmLut_PQ;
        pGammaLut       = u32GmmLut_22;
    }
    else if(enHiHdrMode == HIHDR_HDR10_IN_HLG_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_HDR10_IN_HLG_OUT!\n");
        pToneMapLut     = u32TMLut_HDR2HLG;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_PQ;
        pGammaLut       = u32GmmLut_HLG;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_SDR_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_HLG_IN_SDR_OUT!\n");
        pToneMapLut     = u32TMLut_HLG2SDR;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_HLG;
        pGammaLut       = u32GmmLut_22;
    }
    else if(enHiHdrMode == HIHDR_HLG_IN_HDR10_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_HLG_IN_HDR10_OUT!\n");
        pToneMapLut     = u32TMLut_HLG2HDR;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_HLG;
        pGammaLut       = u32GmmLut_PQ1000;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_SDR_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SLF_IN_SDR_OUT!\n");
        pToneMapLut     = u32TMLut_SLF2SDR;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_SLF;
        pGammaLut       = u32GmmLut_22;
    }
    else if(enHiHdrMode == HIHDR_SLF_IN_HDR10_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SLF_IN_HDR10_OUT!\n");
        pToneMapLut     = u32TMLut_Linear;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_SLF;
        pGammaLut       = u32GmmLut_PQ10000;
    }
    else if(enHiHdrMode == HIHDR_BT2020_IN_709_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SDR2020_IN_709_OUT!\n");
        pToneMapLut     = u32TMLut_Linear;//not used
        pSMapLut        = u32SMLut_Linear;//not used
        pDegammaLut     = u32DeGmmLut_24;
        pGammaLut       = u32GmmLut_24;
    }
    else if(enHiHdrMode == HIHDR_XVYCC)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_XVYCC!\n");
        pToneMapLut     = u32TMLut;//not used
        pSMapLut        = u32SMLut_HDR2SDR;//not used
        pDegammaLut     = u32DeGmmLut_xvYCC;
        pGammaLut       = u32GmmLut_22;
    }
    else if(enHiHdrMode == HIHDR_SDR_BT2020CL_IN_BT709_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SDR2020CL_IN_709_OUT!\n");
        pToneMapLut     = u32TMLut_Linear;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_24;
        pGammaLut       = u32GmmLut_24;
    }
    else if(enHiHdrMode == HIHDR_SDR_IN_HDR10_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SDR709_IN_HDR10_OUT!\n");
        pToneMapLut     = u32TMLut_SDR2HDR;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_24;
        pGammaLut       = u32GmmLut_PQ1000;
    }
    else if(enHiHdrMode == HIHDR_SDR_IN_HLG_OUT)
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = VHDR_SDR709_IN_HLG_OUT!\n");
        pToneMapLut     = u32TMLut_SDR2HLG;
        pSMapLut        = u32SMLut_Linear;
        pDegammaLut     = u32DeGmmLut_24;
        pGammaLut       = u32GmmLut_HLG;
    }
    else
    {
        //VDP_PRINT("VHDR Coef : VhdrSceneMode = Default(HDR2SDR)!\n");
        pToneMapLut     = u32TMLut_HDR2SDR;
        pSMapLut        = u32SMLut_HDR2SDR;
        pDegammaLut     = u32DeGmmLut_PQ;
        pGammaLut       = u32GmmLut_22;
    }

#endif

    //tonemapping lut : 64x16
    stCoefGen.p_coef         = pToneMapLut;//lutd;
    stCoefGen.p_coef_new     = u32Lutd;
    stCoefGen.length         = 64;
    stCoefGen.coef_data_type = DRV_COEF_DATA_TYPE_U32;
    stCoefGen.coef_data_mode = VDP_RM_COEF_MODE_TYP;
    stCoefGen.coef_max       = ((1<<16) - 1);
    stCoefGen.coef_min       = 0;

    VDP_DRV_GenCoef(&stCoefGen);

    //saturation mapping lut : 64x10
    stCoefGen.p_coef         = pSMapLut;//&lutd[64];
    stCoefGen.p_coef_new     = &u32Lutd[64];
    stCoefGen.length         = 32;//64;
    stCoefGen.coef_data_type = DRV_COEF_DATA_TYPE_U32;
    stCoefGen.coef_data_mode = VDP_RM_COEF_MODE_TYP;
    stCoefGen.coef_max       = ((1<<10) - 1);
    stCoefGen.coef_min       = 0;

    VDP_DRV_GenCoef(&stCoefGen);


    //degamma lut : 64x21
    stCoefGen.p_coef         = pDegammaLut;//luts;
    stCoefGen.p_coef_new     = u32Luts;
    stCoefGen.length         = 64;
    stCoefGen.coef_data_type = DRV_COEF_DATA_TYPE_U32;
    stCoefGen.coef_data_mode = VDP_RM_COEF_MODE_TYP;
    stCoefGen.coef_max       = ((1<<21) - 1);
    stCoefGen.coef_min       = 0;

    VDP_DRV_GenCoef(&stCoefGen);

    //gamma lut : 64x12
    stCoefGen.p_coef         = pGammaLut;//&luts[64];
    stCoefGen.p_coef_new     = &u32Luts[64];
    stCoefGen.length         = 64;
    stCoefGen.coef_data_type = DRV_COEF_DATA_TYPE_U32;
    stCoefGen.coef_data_mode = VDP_RM_COEF_MODE_TYP;
    stCoefGen.coef_max       = ((1<<12) - 1);
    stCoefGen.coef_min       = 0;

    VDP_DRV_GenCoef(&stCoefGen);

    //send coef to DDR

    VDP_DRV_SendHiHdrVCoef(u32Lutd,u32Luts);
    //VDP_PRINT("[coef] hihdr_v coef send OK! \n");
}


