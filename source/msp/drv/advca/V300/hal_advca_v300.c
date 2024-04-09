/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_advca_v300.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#include "drv_advca_internal.h"
#include "drv_advca_external.h"
#include "asm/io.h"
#include "hi_drv_mem.h"
#include "drv_tee_advca.h"

#define ADVCA_MAGIC_NUM1 (0xa843dcad)
#define ADVCA_MAGIC_NUM2 (0x12f02456)

CA_KEYLADDER_INFO_S g_CSA2Info = {0};
CA_KEYLADDER_INFO_S g_CSA3Info = {0};
CA_KEYLADDER_INFO_S g_R2RInfo  = {0};
CA_KEYLADDER_INFO_S g_SPInfo   = {0};
CA_KEYLADDER_INFO_S g_MiscInfo = {0};
CA_KEYLADDER_INFO_S g_DCASInfo = {0};
CA_KEYLADDER_INFO_S g_TAInfo   = {0};
CA_KEYLADDER_INFO_S g_GDRMInfo = {0};
CA_KEYLADDER_INFO_S g_SECSTOREInfo   = {0};
#if defined(CHIP_TYPE_hi3798mv310)
CA_KEYLADDER_INFO_S g_BLDECInfo      = {0};
CA_KEYLADDER_INFO_S g_BLENCInfo      = {0};
#endif
static HI_BOOL g_IsSWPKKeyLadderOpen = HI_FALSE;

HI_U32 HAL_ADVCA_V300_Open(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKLadder = HI_UNF_ADVCA_KEYLADDER_BUTT;

    memset(&g_CSA2Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_CSA2Info.OpenFlag = HI_TRUE;
    g_CSA2Info.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    ret = HAL_ADVCA_V300_GetCWLadderLevel(&enKLadder);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("call HAL_ADVCA_V300_GetCWLadderLevel failed, ret: 0x%x", ret);
        return HI_FAILURE;
    }
    g_CSA2Info.MaxLevel = enKLadder + 1;

    memset(&g_CSA3Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_CSA3Info.OpenFlag = HI_TRUE;
    g_CSA3Info.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    ret = HAL_ADVCA_V300_GetCSA3LadderLevel(&enKLadder);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("call HAL_ADVCA_V300_GetCSA3LadderLevel failed, ret: 0x%x", ret);
        return HI_FAILURE;
    }
    g_CSA3Info.MaxLevel = enKLadder + 1;

    memset(&g_R2RInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_R2RInfo.OpenFlag = HI_TRUE;
    g_R2RInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    ret = HAL_ADVCA_V300_GetR2RLadderLevel(&enKLadder);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("call HAL_ADVCA_V300_GetR2RLadderLevel failed, ret: 0x%x", ret);
        return HI_FAILURE;
    }
    g_R2RInfo.MaxLevel = enKLadder + 1;

    memset(&g_SPInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_SPInfo.OpenFlag = HI_FALSE;
    g_SPInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_SPInfo.enDscMode = HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_IDSA;
    ret = HAL_ADVCA_V300_GetSPLadderLevel(&enKLadder);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("call HAL_ADVCA_V300_GetSPLadderLevel failed, ret: 0x%x", ret);
        return HI_FAILURE;
    }
    g_SPInfo.MaxLevel = enKLadder + 1;

    memset(&g_MiscInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_MiscInfo.OpenFlag = HI_FALSE;
    g_MiscInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    ret = HAL_ADVCA_V300_GetMiscKlLevel(&enKLadder);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("call HAL_ADVCA_V300_GetMiscKlLevel failed, ret: 0x%x", ret);
        return HI_FAILURE;
    }
    g_MiscInfo.MaxLevel = enKLadder + 1;

    memset(&g_DCASInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_DCASInfo.OpenFlag = HI_FALSE;
    g_DCASInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_DCASInfo.MaxLevel = 0x03;

    memset(&g_TAInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_TAInfo.OpenFlag = HI_FALSE;
    g_TAInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_TAInfo.MaxLevel = 0x03;    //Fixed to 3 level in Transformation Algorithm keyladder

    memset(&g_GDRMInfo, 0x0, sizeof (CA_KEYLADDER_INFO_S));
    g_GDRMInfo.OpenFlag = HI_FALSE;
    g_GDRMInfo.MaxLevel = 0x03;

    return HI_SUCCESS;
}

HI_U32 HAL_ADVCA_V300_Close(HI_VOID)
{
    memset(&g_CSA2Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_CSA3Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_R2RInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_SPInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_MiscInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_DCASInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_TAInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_GDRMInfo, 0, sizeof(CA_KEYLADDER_INFO_S));

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_V300_WaitStat(HI_VOID)
{
    HI_U32 cnt = 0;
    CA_V300_CA_STATE_U CAStatus;
    HI_S32 errState = 0;

    /* wait for KeyLadder calc done */
    // corform one value when test, about 500
    while (cnt < 50)
    {
        CAStatus.u32 = 0;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        if (CAStatus.bits.klad_busy == 0)
        {
            HI_INFO_CA("ca_decrypted finished, cnt:%d\n", cnt);
            break;
        }
        ca_msleep(10);
        cnt++;
    }

    if (cnt >= 50)
    {
        HI_ERR_CA("\n Error CA handle too long !!!!!!!!!!! \n");
        return HI_FAILURE;      /* time out */
    }

    /* not support 'last_key_not_rdy' */
    errState = CAStatus.bits.err_state;
    return errState;
}


HI_S32 HAL_ADVCA_V300_StatHardCwSel(HI_U32 *pu32Lock)
{
    HI_S32 Ret = HI_SUCCESS;

    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    //Get the OTP bit "ts_csa2_hardonly_en"
    Ret = DRV_CA_OTP_V200_GetTSCsa2HardonlyEn(pu32Lock);

    return Ret;
}


HI_S32 HAL_ADVCA_V300_StatR2RHardKey(HI_U32 *pu32Lock)
{
    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }
    //R2R decryption ladder lock.
    //*pbLock = g_pCaReg->CaCtrlProc.Bits.R2rHKeyLock;
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_StatTdesLock(HI_U32 *pu32Lock)
{
    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }
    //Whether to lock the multicipher to enable it to use the TDES rather than the DES.
    //*pbLock = g_pCaReg->CaCtrlProc.Bits.TdesLock;
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetCWLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetCSA2LadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_CSA2Info.MaxLevel = enSel;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetCWLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetCSA2LadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetR2RLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetR2RLadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_R2RInfo.MaxLevel = enSel;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetR2RLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetR2RLadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetSPLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if ((enSel < HI_UNF_ADVCA_KEYLADDER_LEV2) || (enSel >= HI_UNF_ADVCA_KEYLADDER_BUTT))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetSPLadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_SPInfo.MaxLevel = enSel;
    }
    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetSPLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetSPLadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetCSA3LadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetCSA3LadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_CSA3Info.MaxLevel = enSel;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetCSA3LadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetCSA3LadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;

    return Ret;
}


HI_S32 HAL_ADVCA_V300_SetCWAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= type)
    {
        HI_ERR_CA("Invalid CSA2 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid CSA2 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif
    g_CSA2Info.Alg = type;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCWAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *pAlgType)
{
    if(pAlgType == NULL)
    {
        HI_ERR_CA("pAlgType: NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *pAlgType = g_CSA2Info.Alg;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetCSA3Algorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= type)
    {
        HI_ERR_CA("Invalid CSA3 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid CSA3 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif

    g_CSA3Info.Alg = type;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCSA3Algorithm(HI_UNF_ADVCA_ALG_TYPE_E *pAlgType)
{
    if(pAlgType == NULL)
    {
        HI_ERR_CA("pAlgType: NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *pAlgType = g_CSA3Info.Alg;
    return HI_SUCCESS;
}


HI_S32 HAL_ADVCA_V300_SetR2RAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= type)
    {
        HI_ERR_CA("R2R Algorithm Error = %d ! \n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("R2R Algorithm Error = %d ! \n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif
    g_R2RInfo.Alg = type;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetR2RAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *type)
{
    if (NULL == type)
    {
	    HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *type = g_R2RInfo.Alg;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetSPAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= enType)
    {
        HI_ERR_CA("Invalid SP Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid SP Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif

    if (g_SPInfo.Alg != enType)
    {
        g_SPInfo.bKeyReset = HI_TRUE;
        g_SPInfo.Alg = enType;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSPAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    if (NULL == penType)
    {
        HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *penType = g_SPInfo.Alg;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= enType)
    {
        HI_ERR_CA("Invalid Misc Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid Misc Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif


    if (g_MiscInfo.Alg != enType)
    {
        g_MiscInfo.bKeyReset = HI_TRUE;
        g_MiscInfo.Alg = enType;
    }
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    if( NULL == penType)
    {
        HI_ERR_CA("Invalid param ,NULL pointer !\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *penType = g_MiscInfo.Alg;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetSecStoreAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if (HI_UNF_ADVCA_ALG_TYPE_BUTT <= enType)
    {
        HI_ERR_CA("Invalid SecStore Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#else
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid SecStore Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
#endif

    if (g_SECSTOREInfo.Alg != enType)
    {
        g_SECSTOREInfo.bKeyReset = HI_TRUE;
        g_SECSTOREInfo.Alg = enType;
    }
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSecStoreAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    if( NULL == penType)
    {
        HI_ERR_CA("Invalid param ,NULL pointer !\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *penType = g_SECSTOREInfo.Alg;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetBlDecAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_SM4))
    {
        HI_ERR_CA("Invalid BLDEC Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    if (g_BLDECInfo.Alg != enType)
    {
        g_BLDECInfo.bKeyReset = HI_TRUE;
        g_BLDECInfo.Alg = enType;
    }
    return HI_SUCCESS;
#else
    HI_ERR_CA("No Need Set BLDEC Keyladder algorithm (%d)!\n", enType);
    return HI_ERR_CA_NOT_SUPPORT;
#endif
}
HI_S32 HAL_ADVCA_V300_SetBlEncAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
#if defined(CHIP_TYPE_hi3798mv310)
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_SM4))
    {
        HI_ERR_CA("Invalid BLENC Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    if (g_BLENCInfo.Alg != enType)
    {
        g_BLENCInfo.bKeyReset = HI_TRUE;
        g_BLENCInfo.Alg = enType;
    }
    return HI_SUCCESS;
#else
    HI_ERR_CA("No Need Set BLENC Keyladder algorithm (%d)!\n", enType);
    return HI_ERR_CA_NOT_SUPPORT;
#endif
}

HI_S32 HAL_ADVCA_V300_SetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_U32 Ret = HI_SUCCESS;
    Ret = DRV_CA_OTP_V200_SetMiscKlLevel(enSel);
    if(Ret == HI_SUCCESS)
    {
        g_MiscInfo.MaxLevel = enSel;
    }
    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    if(NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    return DRV_CA_OTP_V200_GetMiscKlLevel(penSel);
}

HI_S32 HAL_ADVCA_V300_SetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E eDscMode)
{
    if (eDscMode >= HI_UNF_ADVCA_SP_DSC_MODE_BUTT)
    {
        HI_ERR_CA("Invaild SP Dsc Mode (%d )!\n", eDscMode);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_SPInfo.enDscMode = eDscMode;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *penType)
{
    if (NULL == penType)
    {
	    HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *penType = g_SPInfo.enDscMode;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetMiscDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E eDscMode)
{
    if (eDscMode >= HI_UNF_ADVCA_SP_DSC_MODE_BUTT)
    {
        HI_ERR_CA("Invaild SP Dsc Mode (%d )!\n", eDscMode);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_MiscInfo.enDscMode = eDscMode;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetMiscDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *penType)
{
    if (NULL == penType)
    {
	    HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *penType = g_MiscInfo.enDscMode;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptCw(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bEvenOrOdd)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CSA2_CTRL_U      CSA2Ctrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;
    struct timeval tv = {0};

    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_GetCWLadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel)
    {
        Ret = HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("call HAL_ADVCA_V300_DecTAKeyLadder return 0x%x!\n",Ret);
            return HI_FAILURE;
        }
    }
    else
    {
        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_FAILURE == Ret)
        {
            HI_ERR_CA("key ladder timeout\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }

        /*2  put DVB_RootKey（CK2）to CA register(DATA input) */
        //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }

    //(3)   配置寄存器CSA2_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    CSA2Ctrl.u32 = 0;
    CSA2Ctrl.bits.dsc_mode = 0;
    CSA2Ctrl.bits.level_sel = enLevel;
    CSA2Ctrl.bits.EvenOrOdd = bEvenOrOdd;  //0：当前是偶密钥；1：当前是奇密钥
    CSA2Ctrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID
    if (HI_UNF_ADVCA_ALG_TYPE_SM4 == g_CSA2Info.Alg)
    {
        CSA2Ctrl.bits.sm4_sel = 1;
    }
    else
    {
        CSA2Ctrl.bits.sm4_sel = 0;
        CSA2Ctrl.bits.tdes_aes_sel = g_CSA2Info.Alg;
    }
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //last level
    {
        CSA2Ctrl.bits.ta_kl_flag = 1;
    }
    DRV_ADVCA_WriteReg(CA_V300_CSA2_CTRL, CSA2Ctrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DVB_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("Cw key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);
        return HI_FAILURE;
    }

    do_gettimeofday(&tv);
    memcpy(g_CSA2Info.SessionKey[enLevel], pu32DataIn, 16);
    g_CSA2Info.SessionKey_sec[enLevel] = tv.tv_sec;

    g_CSA2Info.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

    //0：当前是偶密钥；1：当前是奇密钥
    if(g_CSA2Info.MaxLevel == (enLevel + 1))
    {
        if(bEvenOrOdd == 0x00)
        {
            memcpy(g_CSA2Info.LastEvenKey, pu32DataIn, 16);
            g_CSA2Info.LastEvenKey_secTime = tv.tv_sec;
        }
        else
        {
            memcpy(g_CSA2Info.LastOddKey, pu32DataIn, 16);
            g_CSA2Info.LastOddKey_secTime = tv.tv_sec;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptCsa3(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bEvenOrOdd)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CSA3_CTRL_U CSA3Ctrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;
    struct timeval tv = {0};

    /* para check*/
    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_GetCSA3LadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }


    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel)
    {
        Ret = HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("call HAL_ADVCA_V300_DecTAKeyLadder return 0x%x!\n",Ret);
            return HI_FAILURE;
        }
    }
    else
    {
        /*2  put DVB_RootKey（CK2）to CA register(DATA input) */
        //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }

    //(3)   配置寄存器CSA3_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    CSA3Ctrl.u32 = 0;
    CSA3Ctrl.bits.dsc_mode = 0x10;
    CSA3Ctrl.bits.level_sel = enLevel;
    CSA3Ctrl.bits.EvenOrOdd = bEvenOrOdd;
    CSA3Ctrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID
    if (HI_UNF_ADVCA_ALG_TYPE_SM4 == g_CSA3Info.Alg)
    {
        CSA3Ctrl.bits.sm4_sel = 1;
    }
    else
    {
        CSA3Ctrl.bits.sm4_sel = 0;
        CSA3Ctrl.bits.tdes_aes_sel = g_CSA3Info.Alg;
    }
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //last level
    {
        CSA3Ctrl.bits.ta_kl_flag = 1;
    }
    DRV_ADVCA_WriteReg(CA_V300_CSA3_CTRL, CSA3Ctrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DVB_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("CSA3 key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);
        return HI_FAILURE;
    }

    do_gettimeofday(&tv);
    memcpy(g_CSA3Info.SessionKey[enLevel], pu32DataIn, 16);
    g_CSA3Info.SessionKey_sec[enLevel] = tv.tv_sec;

    g_CSA3Info.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

    //0：当前是偶密钥；1：当前是奇密钥
    if(g_CSA3Info.MaxLevel == (enLevel + 1))
    {
        if(bEvenOrOdd == 0x00)
        {
            memcpy(g_CSA3Info.LastEvenKey, pu32DataIn, 16);
            g_CSA3Info.LastEvenKey_secTime = tv.tv_sec;
        }
        else
        {
            memcpy(g_CSA3Info.LastOddKey, pu32DataIn, 16);
            g_CSA3Info.LastOddKey_secTime = tv.tv_sec;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptR2R_REE(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bIsDeCrypt)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_R2R_CTRL_U R2RCtrl;
    struct timeval tv = {0};

    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put DVB_RootKey（CK2）to CA register(DATA input) */
    //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    //(3)   配置寄存器R2R_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    R2RCtrl.u32 = 0;
    R2RCtrl.bits.level_sel = enLevel;
    R2RCtrl.bits.mc_alg_sel = 0;//Multicipher Algorithm. default setting
#if defined(CHIP_TYPE_hi3798mv310)
    R2RCtrl.bits.key_addr = (AddrID << 1) & 0xFF; //Demux DescambleKey ID
#else
    R2RCtrl.bits.key_addr = AddrID & 0xFF; //Demux DescambleKey ID
#endif
    if (HI_UNF_ADVCA_ALG_TYPE_SM4 == g_R2RInfo.Alg)
    {
        R2RCtrl.bits.sm4_sel = 1;
    }
    else
    {
        R2RCtrl.bits.sm4_sel = 0;
        R2RCtrl.bits.tdes_aes_sel = g_R2RInfo.Alg;
    }

    DRV_ADVCA_WriteReg(CA_V300_R2R_CTRL, R2RCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (R2R_SP_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("R2R key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    do_gettimeofday(&tv);
    memcpy(g_R2RInfo.SessionKey[enLevel], pu32DataIn, 16);
    g_R2RInfo.SessionKey_sec[enLevel] = tv.tv_sec;

    g_R2RInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptR2R_TEE(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bIsDeCrypt)
{
    if (enLevel < HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        memcpy(g_R2RInfo.SessionKey[enLevel], pu32DataIn, 16);
        g_R2RInfo.addr = AddrID & 0xFF;
        return HI_SUCCESS;
    }

    HI_ERR_CA("Error: the Level is invalid para!\n");
    return HI_ERR_CA_INVALID_PARA;
}


HI_S32 HAL_ADVCA_V300_CryptR2R(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bIsDeCrypt)
{
    HI_S32 ret = HI_FAILURE;

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    if(g_IsSWPKKeyLadderOpen)
    {
        HAL_ADVCA_V300_DecryptSWPK(pu32DataIn, AddrID);
        return HI_SUCCESS;
    }

#if defined(KLAD_TYPE_TEE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200)
    ret = HAL_ADVCA_V300_CryptR2R_TEE(enLevel, pu32DataIn, AddrID, bIsDeCrypt);
#else
    ret = HAL_ADVCA_V300_CryptR2R_REE(enLevel, pu32DataIn, AddrID, bIsDeCrypt);
#endif

    return ret;
}

#if defined(KLAD_TYPE_TEE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200)
HI_S32 HAL_ADVCA_V300_R2R_CALLTEE(HI_VOID)
{
    HI_S32 i = 0;
    klad_session_para_s klad_attr = {0};

    klad_attr.klad_type = 0x3F00;/*HI_UNF_ADVCA_KEYLADDER_R2R;*/ /*add tee r2r keyladder type info*/

    klad_attr.attr.enAlg = g_R2RInfo.Alg;

    klad_attr.iv_flag = HI_FALSE;

    klad_attr.session_level = g_R2RInfo.MaxLevel - 1;

    for (i = 0; i < klad_attr.session_level; i++)
    {
        klad_attr.session_key[i].enLevel = i;
        memcpy(klad_attr.session_key[i].au8Key, g_R2RInfo.SessionKey[i], 16);
    }

    memcpy(klad_attr.content_key.au8Key, g_R2RInfo.SessionKey[i], 16);
    klad_attr.handle = g_R2RInfo.addr | (0x4d << 16); /*add tee cipher module id bit16-bit23*/
    return DEV_ADVCA_TeecSetKey(&klad_attr);
}
#endif

HI_S32 HAL_ADVCA_V300_DecryptSP(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                                HI_U32 *pu32DataIn,
                                HI_U32 AddrID,
                                HI_BOOL bEvenOrOdd,
                                DRV_ADVCA_CA_TARGET_E enCwTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_SP_CTRL_U unSPCtrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;
    struct timeval tv = {0};

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }
    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    if (CA_OTP_VENDOR_VERIMATRIX == enCaVendorType)
    {
        if (g_SPInfo.bKeyReset == HI_FALSE)
        {
            if (0 == memcmp(g_SPInfo.SessionKey[enLevel], pu32DataIn, 16))
            {
                return HI_SUCCESS;
            }
            g_SPInfo.bKeyReset = HI_TRUE;
        }
    }

    Ret = HAL_ADVCA_V300_GetSPLadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel)
    {
        Ret = HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("call HAL_ADVCA_V300_DecTAKeyLadder return 0x%x!\n",Ret);
            return HI_FAILURE;
        }
    }
    else
    {
        /*2  put SPE_RootKey（CK2）to CA register(DATA input) */
        //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }

    //(3)   配置寄存器SP_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    unSPCtrl.u32 = 0;
    if(HI_UNF_ADVCA_KEYLADDER_LEV5 == enLevel)
    {
        unSPCtrl.bits.level_sel_5 = 1;
    }
    else
    {
        unSPCtrl.bits.level_sel = enLevel;
    }

    if (HI_UNF_ADVCA_ALG_TYPE_SM4 == g_SPInfo.Alg)
    {
        unSPCtrl.bits.sm4_sel = 1;
    }
    else
    {
        unSPCtrl.bits.sm4_sel = 0;
        unSPCtrl.bits.tdes_aes_sel = g_SPInfo.Alg;
    }

    if(enCwTarget == DRV_ADVCA_CA_TARGET_DEMUX)
    {
        if (0 == (g_SPInfo.enDscMode & 0x4000))
        {
            unSPCtrl.bits.raw_mode = 0;          //payload模式
            unSPCtrl.bits.key_addr = ((AddrID & 0x7F) << 1) + bEvenOrOdd; //Demux DescambleKey ID + even_or_odd
            unSPCtrl.bits.dsc_mode = g_SPInfo.enDscMode;  //set demux DscMode
        }
        else
        {
            unSPCtrl.bits.raw_mode = 1;          //raw模式
#if defined(CHIP_TYPE_hi3798mv310)
            unSPCtrl.bits.key_addr = (AddrID << 1) & 0xFF;
#else
            unSPCtrl.bits.key_addr = AddrID & 0xFF; //multicipher channel ID
#endif
        }
    }
    else
    {
        unSPCtrl.bits.raw_mode = 1;          //raw模式
#if defined(CHIP_TYPE_hi3798mv310)
        unSPCtrl.bits.key_addr = (AddrID << 1) & 0xFF;
#else
        unSPCtrl.bits.key_addr = AddrID & 0xFF; //multicipher channel ID
#endif
    }

    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel)
    {
        unSPCtrl.bits.ta_kl_flag = 1;
    }

    DRV_ADVCA_WriteReg(CA_V300_SP_CTRL, unSPCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (R2R_SP_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("SP key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    do_gettimeofday(&tv);
    memcpy(g_SPInfo.SessionKey[enLevel], pu32DataIn, 16);
    g_SPInfo.SessionKey_sec[enLevel] = tv.tv_sec;

    g_SPInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

    //0：当前是偶密钥；1：当前是奇密钥
    if(g_SPInfo.MaxLevel == (enLevel + 1))
    {
        if(bEvenOrOdd == 0x00)
        {
            memcpy(g_SPInfo.LastEvenKey, pu32DataIn, 16);
            g_SPInfo.LastEvenKey_secTime = tv.tv_sec;
        }
        else
        {
            memcpy(g_SPInfo.LastOddKey, pu32DataIn, 16);
            g_SPInfo.LastOddKey_secTime = tv.tv_sec;
        }
    }


    if (CA_OTP_VENDOR_VERIMATRIX == enCaVendorType)
    {
        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV5)
        {
            g_SPInfo.bKeyReset = HI_FALSE;
        }
    }

    return HI_SUCCESS;
}


HI_S32 HAL_DAVCA_V300_EncryptDevicekey(HI_U32 *pDeviceKey, HI_U32 *pEncryptDeviceKey)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_GDRM_CTRL_U unGDRMCtrl;
    CA_V300_CONFIG_STATE_U unConfigStatus;

    if (HI_NULL == pDeviceKey || HI_NULL == pEncryptDeviceKey)
    {
       HI_ERR_CA("HI_NULL == pDataIn || HI_NULL == pEncryptDeviceKey\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */

    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pDeviceKey[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pDeviceKey[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pDeviceKey[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pDeviceKey[3]);

    unGDRMCtrl.u32 = 0;
    unGDRMCtrl.bits.level_sel = 0x0;
    unGDRMCtrl.bits.decryption = 0;

    DRV_ADVCA_WriteReg(CA_V300_GDRM_CTRL, unGDRMCtrl.u32); /* CAStatus.bits.klad_busy will be set to 1 */

    /* Now Wait, until CAStatus.bits.klad_busy == 0 */
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);
        return HI_FAILURE;
    }

    pEncryptDeviceKey[0] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST0);
    pEncryptDeviceKey[1] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST1);
    pEncryptDeviceKey[2] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST2);
    pEncryptDeviceKey[3] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST3);

    //Just to store it for /proc message
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);

        memcpy(g_GDRMInfo.SessionKey[0], (HI_U8 *)pDeviceKey, 16);
        memcpy(g_GDRMInfo.SessionKey[1], (HI_U8 *)pEncryptDeviceKey, 16);
        g_GDRMInfo.SessionKey_sec[0] = tv.tv_sec;
        g_GDRMInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_GDRM_CTRL);
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_EncryptSwpk(HI_U32 *pClearSwpk,HI_U32 *pEncryptSwpk)
{
    HI_U32 index;
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_BL_CTRL_ENC_U BlEncCtrl;

    /* Key Ladder internal use TDES.
    Just Need to input data. */

    if ((HI_NULL == pClearSwpk) || (HI_NULL == pEncryptSwpk))
    {
       HI_ERR_CA("HI_NULL == pClearSwpk or HI_NULL == pEncryptSwpk\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put R2R_RootKey（CK2）to CA register(DATA input) */
    //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
#if defined (CHIP_TYPE_hi3798cv200)  || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    //STB_ROOT key not have secure attr
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN0, pClearSwpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN1, pClearSwpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN2, pClearSwpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN3, pClearSwpk[3]);
#else
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pClearSwpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pClearSwpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pClearSwpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pClearSwpk[3]);
#endif

    BlEncCtrl.u32 = 0x01;
#if defined(CHIP_TYPE_hi3798mv310)
    if(HI_UNF_ADVCA_ALG_TYPE_SM4 == g_BLENCInfo.Alg)
    {
        BlEncCtrl.bits.sm4_sel  = 1;
    }
#endif
    //(3)   配置寄存器BL_CTRL_ENC，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_ENC, BlEncCtrl.u32);//0x1c Set Register

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    for(index = 0; index < 16; index += 4) //Data Result is 128bit(16Bytes) data
    {
        pEncryptSwpk[(index / 4)] = DRV_ADVCA_ReadReg(CA_V300_BLK_ENC_RSLT + index);
    }
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DCASOpen(HI_UNF_CIPHER_ALG_E enAlg)
{
    switch (enAlg)
    {
        case HI_UNF_CIPHER_ALG_3DES:
            g_DCASInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
            break;
        case HI_UNF_CIPHER_ALG_AES:
            g_DCASInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_AES;
            break;
#if defined(CHIP_TYPE_hi3798mv310)
        case HI_UNF_CIPHER_ALG_SM4:
            g_DCASInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_SM4;
            break;
#endif
        default:
            HI_ERR_CA("not support algorithm: %d\n", enAlg);
            return HI_FAILURE;
    }

    if (g_DCASInfo.OpenFlag != HI_TRUE)
    {
        g_DCASInfo.OpenFlag = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DCASClose(HI_VOID)
{
    if(g_DCASInfo.OpenFlag == HI_TRUE)
    {
        g_DCASInfo.OpenFlag = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptDCAS(HI_U32 enLevel, HI_U32 *pu32DataIn, HI_U32 AddrID, HI_BOOL bEvenOrOdd, HI_U32 *pDataOut, HI_UNF_ADVCA_CA_TARGET_E enKlTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_DCAS_CTRL_U DCASCtrl;

    if(g_DCASInfo.OpenFlag != HI_TRUE)
    {
        HI_ERR_CA("Error: DCAS is not Open\n");
        return HI_FAILURE;
    }

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    HI_INFO_CA("input: 0x%08x %08x %08x %08x\n", pu32DataIn[0], pu32DataIn[1], pu32DataIn[2], pu32DataIn[3]);
    /*2  put EncryptData to CA register(DATA input) */
    //(2)   配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    //(3)   配置寄存器DCAS_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    DCASCtrl.u32 = 0;
    DCASCtrl.bits.dsc_code_mc_alg_sel = 0;
    DCASCtrl.bits.level_sel = enLevel;
    if(enLevel == 0x04) //To Demux:0100：当前是第3级会话密钥,payload模式SP密钥；
    {
        if(enKlTarget == HI_UNF_ADVCA_CA_TARGET_DEMUX)
        {
            //设置第3级密钥的话，必须设置为0x04: 0100：当前是第3级会话密钥
            //0100：当前是第3级会话密钥,payload模式SP密钥；
            DCASCtrl.bits.level_sel = 0x04;
            DCASCtrl.bits.even_or_odd = bEvenOrOdd;  //Odd/Even Key
            /* Demux DescambleKey ID + even_or_odd */
            DCASCtrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID
        }
        else
        {
            //0101：当前是第3级会话密钥,raw模式SP密钥；
            DCASCtrl.bits.level_sel = 0x05;
            /* multicipher channel ID */
            DCASCtrl.bits.key_addr = AddrID & 0xFF; //Demux DescambleKey ID
        }
    }
    else if(enLevel == 0x05)  //To R2R,0101：当前是第3级会话密钥,raw模式SP密钥；
    {
        //R2R；0011：当前是第3级会话密钥,R2R密钥
        DCASCtrl.bits.level_sel = 0x05;
        /* multicipher channel ID */
#if defined(CHIP_TYPE_hi3798mv310)
        DCASCtrl.bits.key_addr = AddrID & 0xFF;
#else
        DCASCtrl.bits.even_or_odd = (AddrID & 0x01);
        DCASCtrl.bits.key_addr = (AddrID >> 1) & 0xFF;
#endif
    }

    if (g_DCASInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_SM4)
    {
        DCASCtrl.bits.sm4_sel = 1;
    }
    else if (g_DCASInfo.Alg == HI_UNF_ADVCA_ALG_TYPE_TDES)
    {
        DCASCtrl.bits.sm4_sel = 0;
        DCASCtrl.bits.tdes_aes_sel = 0;//0:tdes, 1:aes
    }
    else
    {
        DCASCtrl.bits.sm4_sel = 0;
        DCASCtrl.bits.tdes_aes_sel = 1;//0:tdes, 1:aes
    }

    DRV_ADVCA_WriteReg(CA_V300_DCAS_CTRL, DCASCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DCAS_KL_DISABLE_ERROR == Ret)
    {
        HI_ERR_CA("DCAS key ladder error: dcas_kl_disable error\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    if(DCASCtrl.bits.level_sel == 0x09) //DCAS reply DA-nonce
    {
        if (HI_NULL == pDataOut)
        {
           HI_ERR_CA("HI_NULL == pDataOut\n");
           return HI_ERR_CA_INVALID_PARA;
        }
        pDataOut[0] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE);
        pDataOut[1] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+4);
        pDataOut[2] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+8);
        pDataOut[3] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+12);
    }

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);

        memcpy(g_DCASInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 16);
        g_DCASInfo.SessionKey_sec[enLevel] = tv.tv_sec;
        //HI_INFO_CA("DCAS enLevel:%d\n", enLevel);
        g_DCASInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

        //0：当前是偶密钥；1：当前是奇密钥
        if ((g_DCASInfo.MaxLevel == (enLevel + 1))
        || (enLevel == 0x04) || (enLevel == 0x05))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_DCASInfo.LastEvenKey, pu32DataIn, 16);
                g_DCASInfo.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_DCASInfo.LastOddKey, pu32DataIn, 16);
                g_DCASInfo.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SWPKKeyLadderOpen(void)
{
    g_IsSWPKKeyLadderOpen = HI_TRUE;

#if defined(CHIP_TYPE_hi3798mv310)
    memset(&g_BLDECInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_BLDECInfo.OpenFlag = HI_TRUE;
    g_BLDECInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_BLDECInfo.MaxLevel = 0x01;

    memset(&g_BLENCInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_BLENCInfo.OpenFlag = HI_TRUE;
    g_BLENCInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_BLENCInfo.MaxLevel = 0x01;
#endif
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SWPKKeyLadderClose(void)
{
    g_IsSWPKKeyLadderOpen = HI_FALSE;

#if defined(CHIP_TYPE_hi3798mv310)
    memset(&g_BLDECInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_BLENCInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
#endif
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptSWPK(HI_U32 *pu32DataIn,HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_BL_CTRL_DEC_U BlDecCtrl;

    /* Key Ladder internal use TDES.
       Just Need to input data. */

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pClearSwpk, pClearSwpk\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
#if defined (CHIP_TYPE_hi3798cv200)  || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    //STB_ROOT key not have secure attr
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_NOMAL_DIN3, pu32DataIn[3]);
#else
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
#endif

    BlDecCtrl.u32 = 0;
#if defined(CHIP_TYPE_hi3798mv310)
    if(HI_UNF_ADVCA_ALG_TYPE_SM4 == g_BLDECInfo.Alg)
    {
        BlDecCtrl.bits.sm4_sel  = 1;
    }
#endif
    BlDecCtrl.bits.key_addr = AddrID & 0x3F;
    /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, BlDecCtrl.u32);//0x1c Set Register
/*    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, 0x01);*/  //0x1c Set Register

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptGDRM(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                        HI_U32 *pu32DataIn,
                        HI_U32 AddrID,
                        HI_BOOL bIsDeCrypt,
                        HI_UNF_ADVCA_CA_TARGET_E enKlTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_GDRM_CTRL_U unGDRMCtrl;
    HI_U32 looptime = 0;

    if (HI_NULL == pu32DataIn)
    {
        HI_ERR_CA("HI_NULL == pDataIn\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    /*
        'level_sel: '会话密钥交换级数。
        00：当前是1级会话密钥；AES ECB
        01：当前是2级会话密钥；AES ECB
        10：当前是3级会话密钥byte0~byte15；AES CBC
        11：当前是3级会话密钥高byte16~byte31；AES CBC。
    */
    switch (enLevel)
    {
        case HI_UNF_ADVCA_KEYLADDER_LEV1:
        case HI_UNF_ADVCA_KEYLADDER_LEV2:
            // do one time
            looptime =1;
            break;

        case HI_UNF_ADVCA_KEYLADDER_LEV3:
            // do 2 times
            // index 0: level_sel = 3;select pu32DataIn 0~15;
            // index 0: level_sel = 4;select pu32DataIn 16~31;
            looptime = 2;
            break;

        default:
            return HI_FAILURE;
    }

    while (looptime > 0)
    {
        /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
           The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
        unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
        if(unConfigStatus.bits.st_vld != 1)
        {
            HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
            return HI_FAILURE;
        }

        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_FAILURE == Ret)
        {
            HI_ERR_CA("Keyladder is busy now!\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }
        if( (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3) && (looptime == 1) )
        {
            /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[4]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[5]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[6]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[7]);
        }
        else
        {
            /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
        }

        /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
        unGDRMCtrl.u32 = 0;
        if(enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3)
        {
            if(looptime == 2)
            {
                unGDRMCtrl.bits.level_sel = 0x02;
            }
            else  //loop == 1;
            {
                unGDRMCtrl.bits.level_sel = 0x03;
            }
        }
        else
        {
            unGDRMCtrl.bits.level_sel = enLevel;
        }
        /* defaultTarget : Multicipher Algorithm. */
        unGDRMCtrl.bits.target_sel = enKlTarget;
        unGDRMCtrl.bits.decryption = bIsDeCrypt;

        if (HI_UNF_ADVCA_CA_TARGET_MULTICIPHER == enKlTarget)
        {
            /* multicipher channel ID */
            unGDRMCtrl.bits.even_or_odd = (AddrID & 0x7F) & 0x01; // first 1 bit
            unGDRMCtrl.bits.key_addr = (AddrID & 0x7F) >> 1;      // last 7 bits
        }
        else
        {
            unGDRMCtrl.bits.key_addr = AddrID & 0xFF;
        }

        DRV_ADVCA_WriteReg(CA_V300_GDRM_CTRL, unGDRMCtrl.u32); /* CAStatus.bits.klad_busy will be set to 1 */

        /* Now Wait, until CAStatus.bits.klad_busy == 0 */
        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_FAILURE == Ret)
        {
            HI_ERR_CA("key ladder timeout\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }
        else if (HI_SUCCESS != Ret)
        {
            CA_V300_CA_STATE_U CAStatus;
            CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
            HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

            return HI_FAILURE;
        }

        if (looptime > 0)
        {
            looptime --;
        }
    }

    if(enLevel < 4)
    {
        struct timeval tv = {0};

        g_GDRMInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_GDRM_CTRL);

        do_gettimeofday(&tv);
        if ((enLevel == HI_UNF_ADVCA_KEYLADDER_LEV1) || (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2))
        {
            memcpy(g_GDRMInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 16);
            g_GDRMInfo.SessionKey_sec[enLevel] = tv.tv_sec;
        }
        else if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3)
        {
            HI_U32 GG_Flag = 0;
            memcpy(g_GDRMInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 32);

            g_GDRMInfo.SessionKey_sec[enLevel] = tv.tv_sec;
            GG_Flag = DRV_ADVCA_ReadReg(CA_V300_GDRM_FLAG);

            memcpy(g_GDRMInfo.GG_Flag, &GG_Flag, 4);
        }
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetGDRMFlag(HI_U32 *pGDRMFlag)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;

    if (HI_NULL == pGDRMFlag)
    {
       HI_ERR_CA("HI_NULL == pGDRMFlag\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    pGDRMFlag[0] = DRV_ADVCA_ReadReg(CA_V300_GDRM_FLAG);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptMisc(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                            HI_U32 *pu32DataIn,
                            HI_U32 AddrID,
                            HI_BOOL bEvenOrOdd,
                            DRV_ADVCA_CA_TARGET_E enCwTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_MISC_CTRL_U unMiscCtrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    struct timeval tv = {0};

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }
    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    if (CA_OTP_VENDOR_VERIMATRIX == enCaVendorType)
    {
        if (g_MiscInfo.bKeyReset == HI_FALSE)
        {
            if (0 == memcmp(g_MiscInfo.SessionKey[enLevel], pu32DataIn, 16))
            {
                return HI_SUCCESS;
            }
            g_MiscInfo.bKeyReset = HI_TRUE;
        }
    }
    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
    unMiscCtrl.u32 = 0;
    if(enLevel == HI_UNF_ADVCA_KEYLADDER_LEV5)
    {
        unMiscCtrl.bits.level_sel_5 = 1;
    }
    else
    {
        unMiscCtrl.bits.level_sel = enLevel;
    }
    if (HI_UNF_ADVCA_ALG_TYPE_SM4 == g_MiscInfo.Alg)
    {
        unMiscCtrl.bits.sm4_sel = 1;
    }
    else
    {
        unMiscCtrl.bits.sm4_sel = 0;
        unMiscCtrl.bits.tdes_aes_sel = g_MiscInfo.Alg;
    }
    unMiscCtrl.bits.target_sel = enCwTarget;
    if (0 == unMiscCtrl.bits.target_sel)
    {
        /* Demux DescambleKey ID + even_or_odd */
        unMiscCtrl.bits.key_addr = ((AddrID & 0x7F) << 1) + bEvenOrOdd;
        unMiscCtrl.bits.dsc_mode = g_MiscInfo.enDscMode;  //set demux DscMode
    }
    else
    {
#if defined(CHIP_TYPE_hi3798mv310)
        unMiscCtrl.bits.key_addr = (AddrID << 1) & 0xFF;
#else
        /* multicipher channel ID */
        unMiscCtrl.bits.key_addr = AddrID & 0xFF;
#endif
    }

    /* CAStatus.bits.klad_busy will be set to 1 */
    DRV_ADVCA_WriteReg(CA_V300_MISC_CTRL, unMiscCtrl.u32);

    /* Now Wait until CAStatus.bits.klad_busy == 0 */
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (MISC_KL_LEVEL_ERROR == Ret)
    {
        HI_ERR_CA("MISC key ladder error: keyladder level is 2 in otp, but start 3rd level actually.\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    do_gettimeofday(&tv);
    memcpy(g_MiscInfo.SessionKey[enLevel], pu32DataIn, 16);
    g_MiscInfo.SessionKey_sec[enLevel] = tv.tv_sec;

    g_MiscInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);

    //0：当前是偶密钥；1：当前是奇密钥
    if(g_MiscInfo.MaxLevel == (enLevel + 1))
    {
        if(bEvenOrOdd == 0x00)
        {
            memcpy(g_MiscInfo.LastEvenKey, pu32DataIn, 16);
            g_MiscInfo.LastEvenKey_secTime = tv.tv_sec;
        }
        else
        {
            memcpy(g_MiscInfo.LastOddKey, pu32DataIn, 16);
            g_MiscInfo.LastOddKey_secTime = tv.tv_sec;
        }
    }

    if (CA_OTP_VENDOR_VERIMATRIX == enCaVendorType)
    {
        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV5)
        {
            g_MiscInfo.bKeyReset = HI_FALSE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptSecStore(HI_U32 *pu32DataIn,HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_SECSTORE_CTRL_U unSecStoreCtrl;

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    /* Config SEC_STORE_KL_CTRL, and then CA_STATE.klad_busy would be set */
    unSecStoreCtrl.u32 = 0;
    unSecStoreCtrl.bits.dec_enc_sel = 0;
    unSecStoreCtrl.bits.tdes_aes_sel = g_SECSTOREInfo.Alg;
    unSecStoreCtrl.bits.key_addr = AddrID & 0xFF;
    DRV_ADVCA_WriteReg(CA_V300_SEC_STORE_KL_CTRL, unSecStoreCtrl.u32);

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSecretKeyChecksumFlag(HI_U32 *pu32Checksum)
{
    HI_UNF_ADVCA_CHECKSUM_FLAG_U unChecksum;

    if( NULL == pu32Checksum)
    {
        HI_ERR_CA("ERROR! Null pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    unChecksum.u32 = 0;
    unChecksum.u32 = DRV_ADVCA_ReadReg(CA_V300_CHECKSUM_FLAG);
    *pu32Checksum = unChecksum.u32;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCAStates(HI_U32 *pu32State)
{
    if(NULL == pu32State)
    {
        HI_ERR_CA("ERROR! Null pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_STATE, *pu32State);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_ResetOTP(HI_VOID)
{
    OTP_V200_CRG_CTRL_U OtpV200CrgCtrl;

    OtpV200CrgCtrl.u32 = 0;

    /*Set the reset value of OTP: 0xF8A220C0 bit[10]*/
    OtpV200CrgCtrl.u32 = DRV_ADVCA_ReadReg(OTP_V200_CRG_ADDR);
    OtpV200CrgCtrl.bits.otp_srst_req = 1;
    DRV_ADVCA_WriteReg(OTP_V200_CRG_ADDR, OtpV200CrgCtrl.u32);

    ca_msleep(1);

    OtpV200CrgCtrl.bits.otp_srst_req = 0;
    DRV_ADVCA_WriteReg(OTP_V200_CRG_ADDR, OtpV200CrgCtrl.u32);
    return HI_SUCCESS;
}

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT

static HI_S32 HAL_ADVCA_ProcGetRegInfo2(HI_U32 *pu32Debug)
{
    HI_U8 *pu8VirAddr = HI_NULL;

    if ( NULL == pu32Debug )
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    pu8VirAddr= (HI_U8*)ioremap_nocache(REG_SYS_GEN24,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }

    *pu32Debug = DRV_ADVCA_SysReadReg(pu8VirAddr);
    iounmap(pu8VirAddr);

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_ProcGetRegInfo1(HI_U32 u32ChipID, HI_U32 *pu32Debug)
{
    HI_U32 wdata[4];
    CA_V300_JTAGKEY0 s_jtagkey0;
    CA_V300_JTAGKEY1 s_jtagkey1;
    HI_U8 *pu8VirAddr = HI_NULL;

    if ( NULL == pu32Debug )
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(wdata, 0, sizeof(HI_U32) * 4);
    s_jtagkey0.u32 = 0;
    s_jtagkey1.u32 = 0;

    s_jtagkey0.bits.data31 = (u32ChipID&(0x1<<14))>>14;
    s_jtagkey0.bits.data30 = (u32ChipID&(0x1<<20))>>20;
    s_jtagkey0.bits.data29 = (u32ChipID&(0x1<<2))>>2;
    s_jtagkey0.bits.data28 = (u32ChipID&(0x1<<29))>>29;

    s_jtagkey0.bits.data27 = (u32ChipID&(0x1<<4))>>4;
    s_jtagkey0.bits.data26 = (u32ChipID&(0x1<<19))>>19;
    s_jtagkey0.bits.data25 = (u32ChipID&(0x1<<6))>>6;
    s_jtagkey0.bits.data24 = (u32ChipID&(0x1<<16))>>16;

    s_jtagkey0.bits.data23 = (u32ChipID&(0x1<<22))>>22;
    s_jtagkey0.bits.data22 = (u32ChipID&(0x1<<26))>>26;
    s_jtagkey0.bits.data21 = (u32ChipID&(0x1<<10))>>10;
    s_jtagkey0.bits.data20 = (u32ChipID&(0x1<<1))>>1;

    s_jtagkey0.bits.data19 = (u32ChipID&(0x1<<12))>>12;
    s_jtagkey0.bits.data18 = (u32ChipID&(0x1<<24))>>24;
    s_jtagkey0.bits.data17 = (u32ChipID&(0x1<<0))>>0;
    s_jtagkey0.bits.data16 = (u32ChipID&(0x1<<15))>>15;

    s_jtagkey0.bits.data15 = (u32ChipID&(0x1<<7))>>7;
    s_jtagkey0.bits.data14 = (u32ChipID&(0x1<<31))>>31;
    s_jtagkey0.bits.data13 = (u32ChipID&(0x1<<18))>>18;
    s_jtagkey0.bits.data12 = (u32ChipID&(0x1<<27))>>27;

    s_jtagkey0.bits.data11 = (u32ChipID&(0x1<<11))>>11;
    s_jtagkey0.bits.data10 = (u32ChipID&(0x1<<21))>>21;
    s_jtagkey0.bits.data09 = (u32ChipID&(0x1<<8))>>8;
    s_jtagkey0.bits.data08 = (u32ChipID&(0x1<<23))>>23;

    s_jtagkey0.bits.data07 = (u32ChipID&(0x1<<13))>>13;
    s_jtagkey0.bits.data06 = (u32ChipID&(0x1<<25))>>25;
    s_jtagkey0.bits.data05 = (u32ChipID&(0x1<<9))>>9;
    s_jtagkey0.bits.data04 = (u32ChipID&(0x1<<5))>>5;

    s_jtagkey0.bits.data03 = (u32ChipID&(0x1<<28))>>28;
    s_jtagkey0.bits.data02 = (u32ChipID&(0x1<<3))>>3;
    s_jtagkey0.bits.data01 = (u32ChipID&(0x1<<30))>>30;
    s_jtagkey0.bits.data00 = (u32ChipID&(0x1<<17))>>17;

    wdata[0]=s_jtagkey0.u32;

    s_jtagkey1.bits.data03 = (wdata[0]&(0xff<<6))>>6;
    s_jtagkey1.bits.data02 = (wdata[0]&(0xff<<17))>>17;
    s_jtagkey1.bits.data01 = (wdata[0]&(0xff<<22))>>22;
    s_jtagkey1.bits.data00 = (wdata[0]&(0xff<<2))>>2;

    wdata[1] = s_jtagkey1.u32;
    wdata[2] = ADVCA_MAGIC_NUM1 ^ s_jtagkey0.u32;
    wdata[3] = ADVCA_MAGIC_NUM2 ^ s_jtagkey1.u32;

    pu8VirAddr= (HI_U8*)ioremap_nocache(CA_OTP_V200_SECCPUJTAGKEY0,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }
    (HI_VOID)DRV_ADVCA_SysWriteReg(pu8VirAddr, wdata[3]);
    (HI_VOID)DRV_ADVCA_SysWriteReg(pu8VirAddr + 0x4, ~wdata[2]); //CA_OTP_V200_SECCPUJTAGKEY1
    (HI_VOID)DRV_ADVCA_SysWriteReg(pu8VirAddr + 0x8, ~wdata[1]); //CA_OTP_V200_SECCPUJTAGKEY2
    (HI_VOID)DRV_ADVCA_SysWriteReg(pu8VirAddr + 0xc, wdata[0]);//CA_OTP_V200_SECCPUJTAGKEY3
    iounmap(pu8VirAddr);

    pu8VirAddr= (HI_U8*)ioremap_nocache(CA_OTP_V200_DEBUG00,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }
    pu32Debug[0] = 0;
    pu32Debug[0] = DRV_ADVCA_SysReadReg(pu8VirAddr);
    iounmap(pu8VirAddr);

    pu8VirAddr= (HI_U8*)ioremap_nocache(CA_OTP_V200_DEBUG11,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }

    pu32Debug[1] = 0;
    pu32Debug[1] = DRV_ADVCA_SysReadReg(pu8VirAddr);
    iounmap(pu8VirAddr);

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_ProcGetRegInfo3(HI_U32 *pu32Debug)
{
    HI_U8 *pu8VirAddr = HI_NULL;

    if ( NULL == pu32Debug )
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    pu8VirAddr= (HI_U8*)ioremap_nocache(REG_SYS_BRM_DEBUG,0x10);
    if(HI_NULL == pu8VirAddr)
    {
        HI_ERR_OTP("ioremap_nocache map error\n");
        return HI_FAILURE;
    }

    *pu32Debug = DRV_ADVCA_SysReadReg(pu8VirAddr);
    iounmap(pu8VirAddr);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_ProcGetReginfo(HI_U32 au32RegInfo[4])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ChipID = 0;

    if ( NULL == au32RegInfo )
    {
        HI_ERR_CA("Invalid param, NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_CHIPID, &u32ChipID);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("Get chipid failed! \n");
        return ret;
    }

    ret = HAL_ADVCA_ProcGetRegInfo1(u32ChipID, au32RegInfo);
    ret |= HAL_ADVCA_ProcGetRegInfo2(&au32RegInfo[2]);
    ret |= HAL_ADVCA_ProcGetRegInfo3(&au32RegInfo[3]);

    return ret;
}
#endif
/******* proc function end   ********/


HI_S32 HAL_ADVCA_V300_CryptbyStbRootkey(HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_STB_CTRL_U unStbCtrl;

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    //(3)   配置寄存器STB KEY CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    unStbCtrl.u32 = 0;
    unStbCtrl.bits.key_addr = AddrID & 0xFF;
    DRV_ADVCA_WriteReg(CA_V300_STB_KEY_CTRL, unStbCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptHCA(HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CAUK_CTRL_U unCaukCtrl;

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    //(3)   配置寄存器CAUK_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    unCaukCtrl.u32 = 0;
    unCaukCtrl.bits.key_addr = AddrID & 0xFF;
    DRV_ADVCA_WriteReg(CA_V300_CAUK_CTRL, unCaukCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        CA_V300_CA_STATE_U CAStatus;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("key ladder error state: %x\n", CAStatus.bits.err_state);

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel, HI_U32 *pu32InData, HI_U32 u32InDataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_TA_CTRL_U unTaCtrl;
    HI_U32 u32Loop, u32Count;
    struct timeval tv = {0};

    if (HI_NULL == pu32InData)
    {
       HI_ERR_CA("HI_NULL == pu32InData\n");
       return HI_ERR_CA_INVALID_PARA;
    }
    if (enLevel >= HI_UNF_ADVCA_KEYLADDER_BUTT)
    {
        HI_ERR_CA("Error: The Level is INVALID PARA!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1.
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    u32Count = u32InDataLen / 16;
    for (u32Loop = 0; u32Loop < u32Count; u32Loop++)
    {
        /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32InData[0 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32InData[1 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32InData[2 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32InData[3 + u32Loop * 4]);

        /* Config TA_CTRL, and then CA_STATE.klad_busy would be set */
        unTaCtrl.u32 = 0;
        unTaCtrl.bits.level_sel = enLevel;

        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2)
        {
            unTaCtrl.bits.dec_lut_alg_sel = HI_UNF_ADVCA_ALG_TYPE_AES;
        }

        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2 && ((u32Loop + 1) == u32Count))
        {
            unTaCtrl.bits.last_time = 1; //last time, should set it to 1.
        }
        else
        {
            unTaCtrl.bits.last_time = 0;
        }
        unTaCtrl.bits.lut_alg_sel = g_TAInfo.Alg;

        /* CAStatus.bits.klad_busy will be set to 1 */
        DRV_ADVCA_WriteReg(CA_V300_TA_KL_CTRL, unTaCtrl.u32);

        /* Now Wait until CAStatus.bits.klad_busy == 0 */
        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_FAILURE == Ret)
        {
            HI_ERR_CA("Key ladder timeout\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }
    }

    if(HI_UNF_ADVCA_KEYLADDER_LEV1 == enLevel)
    {
        do_gettimeofday(&tv);
        memcpy(g_TAInfo.SessionKey[enLevel], pu32InData, 16);
        g_TAInfo.SessionKey_sec[enLevel] = tv.tv_sec;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetTaAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid TA Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_TAInfo.Alg = enType;

    return HI_SUCCESS;
}
static HI_VOID C6_ADVCA_Swith(CA_KEYLADDER_ATTR_S *pDeststKeyladderAttr, CA_KEYLADDER_ATTR_S *pSrcstKeyladderAttr)
{
    HI_INFO_CA("enter C6_ADVCA_Swith\n");
    memset(pDeststKeyladderAttr, 0, sizeof(CA_KEYLADDER_ATTR_S));

    switch(pSrcstKeyladderAttr->enKeyLadderType)
    {
    case HI_UNF_ADVCA_KEYLADDER_MISC:
        pDeststKeyladderAttr->enKeyLadderType = HI_UNF_ADVCA_KEYLADDER_SP;

        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable      = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enAlgType    = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enAlgType;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode    = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enDscMode;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enStage      = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage;
        memcpy(pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, 16);
        break;
    case HI_UNF_ADVCA_KEYLADDER_SP:
        pDeststKeyladderAttr->enKeyLadderType = HI_UNF_ADVCA_KEYLADDER_MISC;

        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr   = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable      = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enAlgType    = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enAlgType;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enDscMode    = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode;
        pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage      = pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enStage;
        memcpy(pDeststKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, pSrcstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, 16);
        break;
    default:
        ;
    }

    HI_INFO_CA("quit C6_ADVCA_Swith\n");
    return ;
}

static HI_S32 checkVMXAdvanced(HI_BOOL *pbVMXAdvanced)
{
    HI_S32 ret = 0;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enValue = HI_UNF_ADVCA_KEYLADDER_BUTT;

    ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    ret = HAL_ADVCA_V300_GetMiscKlLevel(&enValue);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get Misck Level, ret=%d\n", ret);
        return HI_FAILURE;
    }

    if ((CA_OTP_VENDOR_VERIMATRIX == enCaVendorType) && (HI_UNF_ADVCA_KEYLADDER_LEV5 == enValue))
    {
        *pbVMXAdvanced = HI_TRUE;
    }
    else
    {
        *pbVMXAdvanced = HI_FALSE;
    }

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_V300_SetCSA2KeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E       enCsa2KeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    CA_CRYPTPM_S stCryptParam = {0};

    enCsa2KeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enCsa2KlAttr;
    if (enCsa2KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetCWAlgorithm(enKeyladderAlg);
    }
    else if (enCsa2KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.u8SessionKey, 16);
        Ret = HAL_ADVCA_V300_DecryptCw(stCryptParam.ladder, stCryptParam.pDin, 0, 0);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enCsa2KeyladderAttr = %d\n", enCsa2KeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetCSA3KeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E       enCsa3KeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    CA_CRYPTPM_S stCryptParam = {0};

    enCsa3KeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enCsa3KlAttr;
    if (enCsa3KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetCSA3Algorithm(enKeyladderAlg);
    }
    else if (enCsa3KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.u8SessionKey, 16);
        Ret = HAL_ADVCA_V300_DecryptCsa3(stCryptParam.ladder, stCryptParam.pDin, 0, 0);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enCsa3KeyladderAttr = %d\n", enCsa3KeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetR2RKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E        enR2RKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    CA_CRYPTPM_S stCryptParam = {0};

    enR2RKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enR2RKlAttr;
    if(enR2RKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetR2RAlgorithm(enKeyladderAlg);
    }
    else if(enR2RKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.u8SessionKey, 16);
        Ret = HAL_ADVCA_V300_CryptR2R(stCryptParam.ladder, stCryptParam.pDin, 0, 1);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enR2RKeyladderAttr = %d\n", enR2RKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetSPKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E         enSPKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    HI_UNF_ADVCA_SP_DSC_MODE_E               enSPDscMode;
    CA_CRYPTPM_S stCryptParam = {0};

    enSPKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr;
    if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetSPAlgorithm(enKeyladderAlg);
    }
    else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, 16);
        Ret = HAL_ADVCA_V300_DecryptSP(stCryptParam.ladder, stCryptParam.pDin, 0, 0, 0);
    }
    else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_DSC_MODE)
    {
        enSPDscMode =  pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode;
        Ret = HAL_ADVCA_V300_SetSPDscMode(enSPDscMode);
    }
    else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE)
    {
        g_SPInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable;
        Ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enR2RKeyladderAttr = %d\n", enSPKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetMISCKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E       enMiscKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    HI_UNF_ADVCA_SP_DSC_MODE_E               enSPDscMode;
    CA_CRYPTPM_S stCryptParam = {0};

    enMiscKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr;
    if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetMiscAlgorithm(enKeyladderAlg);
    }
    else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, 16);
        Ret = HAL_ADVCA_V300_DecryptMisc(stCryptParam.ladder, stCryptParam.pDin, 0, 0, 0);
    }
    else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_DSC_MODE)
    {
        enSPDscMode =  pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode;
        Ret = HAL_ADVCA_V300_SetMiscDscMode(enSPDscMode);
    }
    else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE)
    {
        g_MiscInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable;
        Ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enMiscKeyladderAttr = %d\n", enMiscKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}


static HI_S32 HAL_ADVCA_V300_SetTAKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E         enTaKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    HI_UNF_ADVCA_KEYLADDER_LEV_E             enKeyladderLevel;
    CA_CRYPTPM_S stCryptParam = {0};
    HI_U8 *pu8TmpBuf = NULL;
    HI_U32 u32TmpBufLen = 0;

    enTaKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enTAKlAttr;
    if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ENABLE)
    {
        g_TAInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.bEnable;
        Ret = HI_SUCCESS;
    }
    else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetTaAlgorithm(enKeyladderAlg);
    }
    else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_SESSION_KEY)
    {
        stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage;
        memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.au8SessionKey, 16);
        Ret = HAL_ADVCA_V300_DecTAKeyLadder(stCryptParam.ladder, stCryptParam.pDin, 16);
    }
    else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_LOAD_TRANDATA)
    {
        enKeyladderLevel = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage;
        pu8TmpBuf = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.u8TranData;
        u32TmpBufLen = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.u32TranDataLen;
        Ret = HAL_ADVCA_V300_DecTAKeyLadder(enKeyladderLevel, (HI_U32*)pu8TmpBuf, u32TmpBufLen);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enTaKeyladderAttr = %d\n", enTaKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

#if !defined(CHIP_TYPE_hi3798mv100) && !defined(CHIP_TYPE_hi3796mv100) && defined(HI_ADVCA_TYPE_VERIMATRIX)
static HI_S32 HAL_ADVCA_V300_SetGDRMKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_E       enGDRMKeyladderAttr;
    HI_U32 u32SessionKey[8] = {0};
    HI_U32 u32Output[4]     = {0};
    HI_U32 u32KeyAddr       = 0;

    enGDRMKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enGDRMKlAttr;
    if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENABLE == enGDRMKeyladderAttr)
    {
        g_GDRMInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.bEnable;
        Ret = HI_SUCCESS;
    }
    else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT == enGDRMKeyladderAttr)
    {
        memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 16);
        Ret = HAL_DAVCA_V300_EncryptDevicekey(u32SessionKey,
                                              u32Output);
        memcpy(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, u32Output, 16);
    }
    else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY == enGDRMKeyladderAttr)
    {
        if (HI_UNF_ADVCA_KEYLADDER_LEV3 == pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enStage)
        {
            memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 32);
            u32KeyAddr = HI_HANDLE_GET_CHNID(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.hCipherHandle);
        }
        else
        {
            memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 16);
            u32KeyAddr = 0;
        }
        Ret = HAL_ADVCA_V300_CryptGDRM(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enStage, u32SessionKey, u32KeyAddr, 1, 1);
    }
    else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG == enGDRMKeyladderAttr)
    {
        Ret = HAL_ADVCA_V300_GetGDRMFlag(u32Output);
        memcpy(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, u32Output, 4);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enGDRMKeyladderAttr = %d\n", enGDRMKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}
#endif

static HI_S32 HAL_ADVCA_V300_SetSecStoreKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_E       enSECKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;

    enSECKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSECStoreAttr.enSECSTREKlAttr;
    if (enSECKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSECStoreAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetSecStoreAlgorithm(enKeyladderAlg);
    }
    else if (enSECKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_ENABLE)
    {
        g_SECSTOREInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSECStoreAttr.bEnable;
        Ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enSECKeyladderAttr = %d\n", enSECKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetSWPKDecKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_E       enSWPKKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                     enKeyladderAlg;

    enSWPKKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSwpkDecAttr.enSWPKDECKlAttr;
    if (enSWPKKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSwpkDecAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetBlDecAlgorithm(enKeyladderAlg);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, enSWPKKeyladderAttr = %d\n", enSWPKKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

static HI_S32 HAL_ADVCA_V300_SetSWPKEncKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_E       enSWPKKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                     enKeyladderAlg;

    enSWPKKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSwpkEncAttr.enSWPKENCKlAttr;
    if (enSWPKKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_ALG)
    {
        enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSwpkEncAttr.enAlgType;
        Ret = HAL_ADVCA_V300_SetBlEncAlgorithm(enKeyladderAlg);
    }
    else
    {
        HI_ERR_CA("Invalid keyladder attribute, SWPKKey ladderAttr = %d\n", enSWPKKeyladderAttr);
        Ret = HI_ERR_CA_INVALID_PARA;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_ADVCA_KEYLADDER_TYPE_E            enKeyladderType;
    HI_BOOL bVMXAdvanced = HI_FALSE;

    CA_KEYLADDER_ATTR_S *pTempstKeyladderAttr = HI_NULL;

    if(pstKeyladderAttr == NULL)
    {
        HI_ERR_CA("Invalid param, pstKeyladderAttr = NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = checkVMXAdvanced(&bVMXAdvanced);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("checkVMXAdvanced error\n");
        return HI_FAILURE;
    }


    pTempstKeyladderAttr = (CA_KEYLADDER_ATTR_S *)HI_KMALLOC(HI_ID_CA, sizeof (CA_KEYLADDER_ATTR_S), GFP_KERNEL);
    if (HI_NULL == pTempstKeyladderAttr)
    {
        HI_ERR_CA("malloc ca_keyladder_attr_s error\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == bVMXAdvanced)
    {
        C6_ADVCA_Swith(pTempstKeyladderAttr, pstKeyladderAttr);
    }
    else
    {
        memcpy(pTempstKeyladderAttr, pstKeyladderAttr, sizeof(CA_KEYLADDER_ATTR_S));
    }

    enKeyladderType = pTempstKeyladderAttr->enKeyLadderType;
    switch(enKeyladderType)
    {
    case HI_UNF_ADVCA_KEYLADDER_CSA2:
        Ret = HAL_ADVCA_V300_SetCSA2KeyladderAttr(pTempstKeyladderAttr);
        break;

    case HI_UNF_ADVCA_KEYLADDER_CSA3:
        Ret = HAL_ADVCA_V300_SetCSA3KeyladderAttr(pTempstKeyladderAttr);
        break;

    case HI_UNF_ADVCA_KEYLADDER_R2R:
        Ret = HAL_ADVCA_V300_SetR2RKeyladderAttr(pTempstKeyladderAttr);
        break;

    case HI_UNF_ADVCA_KEYLADDER_SP:
        Ret = HAL_ADVCA_V300_SetSPKeyladderAttr(pTempstKeyladderAttr);
        break;

    case HI_UNF_ADVCA_KEYLADDER_MISC:
        Ret = HAL_ADVCA_V300_SetMISCKeyladderAttr(pTempstKeyladderAttr);
        break;
    case HI_UNF_ADVCA_KEYLADDER_TA:
        Ret = HAL_ADVCA_V300_SetTAKeyladderAttr(pTempstKeyladderAttr);
        break;
#if !defined(CHIP_TYPE_hi3798mv100) \
 && !defined(CHIP_TYPE_hi3796mv100) \
 && defined(HI_ADVCA_TYPE_VERIMATRIX)
    case HI_UNF_ADVCA_KEYLADDER_GDRM:
        Ret = HAL_ADVCA_V300_SetGDRMKeyladderAttr(pTempstKeyladderAttr);
        break;
#endif
    case HI_UNF_ADVCA_KEYLADDER_SECSTORE:
        Ret = HAL_ADVCA_V300_SetSecStoreKeyladderAttr(pTempstKeyladderAttr);
        break;
    case HI_UNF_ADVCA_KEYLADDER_SWPKDEC:
        Ret = HAL_ADVCA_V300_SetSWPKDecKeyladderAttr(pTempstKeyladderAttr);
        break;
    case HI_UNF_ADVCA_KEYLADDER_SWPKENC:
        Ret = HAL_ADVCA_V300_SetSWPKEncKeyladderAttr(pTempstKeyladderAttr);
        break;
    default:
        HI_ERR_CA("Invalid keyladder type, enKeyladderType = %d\n", enKeyladderType);
        Ret = HI_ERR_CA_INVALID_PARA;
        break;
    }

    HI_KFREE(HI_ID_CA, pTempstKeyladderAttr);

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GenChipConfCmac(HI_U8 *pu8ChipConfBitm, HI_U8 *pu8ChipConfCmac)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CFG_CBC_MAC_U unCfgCbcMacCtrl;

    if ((HI_NULL == pu8ChipConfBitm) || (HI_NULL == pu8ChipConfCmac))
    {
        HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, *((HI_U32*)pu8ChipConfBitm + 0));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, *((HI_U32*)pu8ChipConfBitm + 1));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, *((HI_U32*)pu8ChipConfBitm + 2));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, *((HI_U32*)pu8ChipConfBitm + 3));

    //(2)   配置寄存器CFG_CBC_MAC，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    unCfgCbcMacCtrl.u32 = 0;
    unCfgCbcMacCtrl.bits.start = 1;
    DRV_ADVCA_WriteReg(CA_V300_CFG_CMAC_CTRL, unCfgCbcMacCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    *(HI_U32*)pu8ChipConfCmac = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT);
    *(HI_U32*)(pu8ChipConfCmac + 0x04) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT  + 0x04);
    *(HI_U32*)(pu8ChipConfCmac + 0x08) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT + 0x08);
    *(HI_U32*)(pu8ChipConfCmac + 0x0C) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT + 0x0C);

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetIrdetoCsa3ActCode(HI_U8 *pu8Csa3ActCode)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CFG_IVRK_CTRL_U unCfgIvRkCtrl;

    if (HI_NULL == pu8Csa3ActCode)
    {
        HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, *(HI_U32*)pu8Csa3ActCode);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, *((HI_U32*)pu8Csa3ActCode + 1));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, *((HI_U32*)pu8Csa3ActCode + 2));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, *((HI_U32*)pu8Csa3ActCode + 3));

    //(2)   配置寄存器CFG_IVRK_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    unCfgIvRkCtrl.u32 = 0;
    unCfgIvRkCtrl.bits.alg_sel = g_CSA3Info.Alg;
    DRV_ADVCA_WriteReg(CA_V300_IVRK_CTRL, unCfgIvRkCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetCavendorOpt(CA_VENDOR_OPT_S *pstCavendorOpt)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_VENDORID_E enCaVendor;
    HI_UNF_ADVCA_CA_VENDOR_OPT_E enCaVendorOpt;
    HI_U8 *pu8TmpBuf = NULL;

    if (HI_NULL == pstCavendorOpt)
    {
        HI_ERR_CA("invalid param\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    enCaVendor = pstCavendorOpt->enCaVendor;
    enCaVendorOpt = pstCavendorOpt->stCaVendorOpt.enCaVendorOpt;
    switch(enCaVendor)
    {
    case HI_UNF_ADVCA_IRDETO:

        if (enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CHIP_CONF_CMAC)
        {
            Ret = HAL_ADVCA_V300_GenChipConfCmac(pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoChipConfCmac.au8ChipConfBitm,
                                                                                                        pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoChipConfCmac.au8ChipConfCmac);
        }
        else if (enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_ACTIVATION_CODE)
        {
            pu8TmpBuf = pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoCsa3ActCode.au8CSA3ActCode;
            Ret = HAL_ADVCA_V300_SetIrdetoCsa3ActCode(pu8TmpBuf);
        }
        else
        {
            HI_ERR_CA("Invalid CA vendor attribute, enCaVendorOpt = %d\n", enCaVendorOpt);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    default:
        HI_ERR_CA("Invalid CA vendor type, enCaVendor = %d\n", enCaVendor);
        break;
    }

    return Ret;
}

