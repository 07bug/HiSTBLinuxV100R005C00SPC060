#include "vdp_drv_ip_cap.h"


extern VDP_ADDR_CFG_S  gstVdpAddrCfg;

HI_VOID VDP_WBC_InitCapCfg(HI_U32 enLayer, VDP_CAP_CFG_S* pstCapCfg)
{
    memset(pstCapCfg, 0, sizeof(VDP_CAP_CFG_S));
    //addr config
    if(enLayer == VDP_LAYER_WBC_HD0)
    {
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64LumAddr = gstVdpAddrCfg.u64WbcLumDataAddr[enLayer] ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64ChmAddr = gstVdpAddrCfg.u64WbcChmDataAddr[enLayer] ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32LumStr  = gstVdpAddrCfg.u32WbcLumDataStr[enLayer]  ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32ChmStr  = gstVdpAddrCfg.u32WbcChmDataStr[enLayer]  ; 

        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64LumAddr = gstVdpAddrCfg.u64WbcLumHeadAddr[enLayer] ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64ChmAddr = gstVdpAddrCfg.u64WbcChmHeadAddr[enLayer] ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32LumStr  = gstVdpAddrCfg.u32WbcLumHeadStr[enLayer]  ; 
        pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32ChmStr  = gstVdpAddrCfg.u32WbcChmHeadStr[enLayer]  ; 
    }
    else
    {
        VDP_ASSERT(0);
    }

    pstCapCfg->bFlipEn          = HI_FALSE;
    pstCapCfg->bUvOrder         = HI_FALSE;
    pstCapCfg->enDataWidth      = VDP_DATA_WTH_8;
    pstCapCfg->enReqLen         = VDP_REQ_LENGTH_16;
    pstCapCfg->u32Interval      = 1;
    pstCapCfg->u32Wbc3dEn       = 0;
    pstCapCfg->stSrcRect.u32Wth = 256;
    pstCapCfg->stSrcRect.u32Hgt = 32 ;
    pstCapCfg->bSmmuEn          = HI_FALSE;
    pstCapCfg->bChkSumEn        = HI_TRUE ;

    pstCapCfg->stTunlCfg.bTunlEn           = HI_FALSE ;
    pstCapCfg->stTunlCfg.bTestModeEn       = HI_FALSE ;
    pstCapCfg->stTunlCfg.u64TunlAddr       = 0xfe00000;
    pstCapCfg->stTunlCfg.u32IntervalLine   = 8 ;
    pstCapCfg->stTunlCfg.u32PartFinishLine = 8 ;

}

HI_VOID VDP_WBC_SetCapCfg(HI_U32 enLayer, VDP_CAP_CFG_S* pstCapCfg)
{
#if EDA_TEST
    cout << "--------------------------------------------------------------" <<endl; 
    cout << "[wbc_cap] enLayer = " << enLayer <<endl; 
    cout << "[wbc_cap] pstCapCfg->bFlipEn                              = 0x" << hex << pstCapCfg->bFlipEn                              << endl;
    cout << "[wbc_cap] pstCapCfg->bUvOrder                             = 0x" << hex << pstCapCfg->bUvOrder                             << endl;
    cout << "[wbc_cap] pstCapCfg->enDataWidth                          = 0x" << hex << pstCapCfg->enDataWidth                          << endl;
    cout << "[wbc_cap] pstCapCfg->enReqLen                             = 0x" << hex << pstCapCfg->enReqLen                             << endl;
    cout << "[wbc_cap] pstCapCfg->u32Interval                          = 0x" << hex << pstCapCfg->u32Interval                          << endl;
    cout << "[wbc_cap] pstCapCfg->u32Wbc3dEn                           = 0x" << hex << pstCapCfg->u32Wbc3dEn                           << endl;
    cout << "[wbc_cap] pstCapCfg->stSrcRect.u32Wth                     = 0x" << hex << pstCapCfg->stSrcRect.u32Wth                     << endl;
    cout << "[wbc_cap] pstCapCfg->stSrcRect.u32Hgt                     = 0x" << hex << pstCapCfg->stSrcRect.u32Hgt                     << endl;
    cout << "[wbc_cap] pstCapCfg->bSmmuEn                              = 0x" << hex << pstCapCfg->bSmmuEn                              << endl;
    cout << "[wbc_cap] pstCapCfg->bChkSumEn                            = 0x" << hex << pstCapCfg->bChkSumEn                            << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64LumAddr = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64LumAddr << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64ChmAddr = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64ChmAddr << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32LumStr  = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32LumStr  << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32ChmStr  = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32ChmStr  << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64LumAddr = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64LumAddr << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64ChmAddr = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64ChmAddr << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32LumStr  = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32LumStr  << endl;
    cout << "[wbc_cap] pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32ChmStr  = 0x" << hex << pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32ChmStr  << endl;
    cout << "[wbc_cap] pstCapCfg->u64Finfo                             = 0x" << hex << pstCapCfg->u64Finfo                             << endl;
#endif
    HI_U32 u32Wth = pstCapCfg->stSrcRect.u32Wth;
    HI_U32 u32Hgt = pstCapCfg->stSrcRect.u32Hgt;

    VDP_CAP_SetWbcCmpEn       (enLayer, 0							                     ); 
    VDP_CAP_SetFlipEn         (enLayer, pstCapCfg->bFlipEn                              ); 
    VDP_CAP_SetUvOrder        (enLayer, pstCapCfg->bUvOrder                             ); 
    VDP_CAP_SetDataWidth      (enLayer, pstCapCfg->enDataWidth                          ); 
    VDP_CAP_SetWbcLen         (enLayer, pstCapCfg->enReqLen                             ); 
    VDP_CAP_SetReqInterval    (enLayer, pstCapCfg->u32Interval                          ); 
    VDP_CAP_SetWbc3dMode      (enLayer, pstCapCfg->u32Wbc3dEn                           ); 
    
#if MMU_TEST
    VDP_CAP_SetMmu2dBypass    (enLayer, 0                             ); 
    VDP_CAP_SetMmu3dBypass    (enLayer, 0                             ); 
#else
    VDP_CAP_SetMmu2dBypass    (enLayer, 1                             ); 
    VDP_CAP_SetMmu3dBypass    (enLayer, 1                             ); 
#endif

    VDP_CAP_SetChksumEn       (enLayer, pstCapCfg->bChkSumEn                            ); 

    VDP_CAP_SetWbcYstride     (enLayer,   pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32LumStr        ); 
    VDP_CAP_SetWbcCstride     (enLayer,   pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u32ChmStr        ); 
    VDP_CAP_SetWbcYaddrL      (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64LumAddr       ) & 0xffffffff) ); 
    VDP_CAP_SetWbcCaddrL      (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64ChmAddr       ) & 0xffffffff) ); 
    VDP_CAP_SetWbcYaddrH      (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64LumAddr >> 32 ) & 0xffffffff) ); 
    VDP_CAP_SetWbcCaddrH      (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA].u64ChmAddr >> 32 ) & 0xffffffff) ); 

    VDP_CAP_SetWbcYnstride    (enLayer,   pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32LumStr        ); 
    VDP_CAP_SetWbcCnstride    (enLayer,   pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u32ChmStr        ); 
    VDP_CAP_SetWbcYnaddrL     (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64LumAddr       ) & 0xffffffff) ); 
    VDP_CAP_SetWbcCnaddrL     (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64ChmAddr       ) & 0xffffffff) ); 
    VDP_CAP_SetWbcYnaddrH     (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64LumAddr >> 32 ) & 0xffffffff) ); 
    VDP_CAP_SetWbcCnaddrH     (enLayer, ((pstCapCfg->stAddr[VDP_CAP_ADDR_DATA_3D].u64ChmAddr >> 32 ) & 0xffffffff) ); 

    VDP_CAP_SetLowdlyEn       (enLayer, pstCapCfg->stTunlCfg.bTunlEn          ); 
    VDP_CAP_SetLowdlyTest     (enLayer, pstCapCfg->stTunlCfg.bTestModeEn      ); 
    VDP_CAP_SetPartfnsLineNum (enLayer, pstCapCfg->stTunlCfg.u32PartFinishLine); 
    VDP_CAP_SetWbPerLineNum   (enLayer, pstCapCfg->stTunlCfg.u32IntervalLine  ); 
    VDP_CAP_SetWbcTunladdrL   (enLayer, ((pstCapCfg->stTunlCfg.u64TunlAddr       ) & 0xffffffff)); 
    VDP_CAP_SetWbcTunladdrH   (enLayer, ((pstCapCfg->stTunlCfg.u64TunlAddr >> 32 ) & 0xffffffff)); 

    //---------------------------
    //Assertion
    //---------------------------
    #if 0
    if(0 == ((pstCapCfg->u64Finfo>>16)&0x1)) // finfo.pro
    {
        if(0 == ((pstCapCfg->u64Finfo)&0xff)) // finfo.fmt
        {
            VDP_ASSERT(0 == (pstCapCfg->stSrcRect.u32Hgt%4)); 
        }
    }
    VDP_ASSERT((0==((pstCapCfg->u64Finfo)&0xff))||(1==((pstCapCfg->u64Finfo)&0xff))||(2==((pstCapCfg->u64Finfo)&0xff)));

    /* Env Reg Setting */
    if(VDP_DISP_MODE_SBS == ((pstCapCfg->u64Finfo>>12)&0xf)) // finfo.img_2d3d_mode
    {
        u32Wth *= 2; 
    }

    if(0 == ((pstCapCfg->u64Finfo>>16)&0x1)) // finfo.pro
    {
        VDP_ASSERT(0 == (u32Hgt%2)); 
        u32Hgt /= 2; 
    }

    if((VDP_DISP_MODE_LBL == ((pstCapCfg->u64Finfo>>12)&0xf))||(VDP_DISP_MODE_TAB == ((pstCapCfg->u64Finfo>>12)&0xf))) // finfo.img_2d3d_mode
    {
        u32Hgt *= 2; 
    }
    #endif
    
    VDP_CAP_SetCapWidth	(enLayer, u32Wth-1 ); 
    VDP_CAP_SetCapHeight(enLayer, u32Hgt-1 ); 
    VDP_CAP_SetCapInfoH (enLayer, ((pstCapCfg->u64Finfo >> 32 ) & 0xffffffff) ); 
    VDP_CAP_SetCapInfoL	(enLayer, ((pstCapCfg->u64Finfo	   ) & 0xffffffff) );

    return;
}



