/******************************************************************************
 Copyright (C), 2009-2014, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : drv_descrambler_func.c
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       : 2013/04/16
 Description   :
******************************************************************************/

#include <linux/kernel.h>

#include "hi_type.h"
#include "hi_module.h"
#include "hi_drv_module.h"
#include "hi_kernel_adapt.h"

#include "hi_unf_descrambler.h"
#include "hi_mpi_descrambler.h"

#include "demux_debug.h"
#include "drv_demux_config.h"
#include "drv_demux_define.h"
#include "drv_descrambler.h"
#include "drv_descrambler_func.h"
#include "drv_descrambler_reg.h"
#include "hal_descrambler.h"
#include "hal_demux.h"

#include "drv_advca_ext.h"
#include "drv_klad_ext.h"
#ifdef CA_FRAMEWORK_V100_SUPPORT
static ADVCA_EXPORT_FUNC_S *g_pAdvcaFunc = HI_NULL;
#endif
HI_VOID DescInitHardFlag(Dmx_Set_S * DmxSet)
{
    DmxHalInitSpeCWOrder(DmxSet);
    DmxHalInitTdesCWOrder(DmxSet);
    DmxHalInitDesCWOrder(DmxSet);
}

    /* 98mv200_vmx_ultra use the the old version secure os */
#if defined(DMX_TEE_SUPPORT) && !(defined(HI_ADVCA_TYPE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200))
static HI_S32 __DmxKeyAcquire(HI_U32 DmxId, HI_U32 *KeyId)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Cluster_S *DmxCluster = GetDmxCluster();
    TEEC_Operation operation;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = DmxId;
    operation.params[0].value.b = 0;

    ret = DmxCluster->Ops->SendCmdToTA(TEEC_CMD_DESCRAMBLER_NONSEC_KEY_ACQUIRE, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_DEMUX("send TEEC_CMD_DESCRAMBLER_NONSEC_KEY_ACQUIRE to TA failed(0x%x).\n", ret);
        ret = HI_FAILURE;
        goto out;
    }

    *KeyId = operation.params[1].value.a;

out:
    return ret;
}

static HI_S32 __DmxKeyRelease(HI_U32 DmxId, const HI_U32 KeyId)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Cluster_S *DmxCluster = GetDmxCluster();
    TEEC_Operation operation;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.params[0].value.a = DmxId;
    operation.params[0].value.b = KeyId;

    ret = DmxCluster->Ops->SendCmdToTA(TEEC_CMD_DESCRAMBLER_NONSEC_KEY_RELEASE, &operation, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_DEMUX("send TEEC_CMD_DESCRAMBLER_NONSEC_KEY_RELEASE to TA failed(0x%x).\n", ret);
        ret = HI_FAILURE;
        goto out;
    }

out:
    return ret;
}
#endif

/*
 * key alloc and release helper functions.
 */
static HI_S32 DmxKeyAcquire(HI_U32 DmxId, HI_UNF_DMX_DESCRAMBLER_ATTR_S *Attr, HI_U32 *KeyId)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S  *KeyInfo = HI_NULL;

    BUG_ON(!mutex_is_locked(&DmxSet->LockAllKey));

    /* 98mv200_vmx_ultra use the the old version secure os */
#if defined(DMX_TEE_SUPPORT) && !(defined(HI_ADVCA_TYPE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200))
    if (unlikely(0 != __DmxKeyAcquire(DmxId, KeyId)))
    {
        HI_ERR_DEMUX("There is no available key now!\n");
        ret = HI_ERR_DMX_NOFREE_KEY;
        goto out;
    }

    if (!(*KeyId < DmxSet->DmxKeyCnt))
    {
        __DmxKeyRelease(DmxId, *KeyId);
        HI_ERR_DEMUX("the key(%d) is error which acquired from tee!\n", *KeyId);
        ret = HI_ERR_DMX_NOFREE_KEY;
        goto out;
    }
#else
    *KeyId = find_first_zero_bit(DmxSet->KeyBitmap, DmxSet->DmxKeyCnt);
    if (!(*KeyId < DmxSet->DmxKeyCnt))
    {
        HI_ERR_DEMUX("There is no available key now!\n");
        ret = HI_ERR_DMX_NOFREE_KEY;
        goto out;
    }
#endif

    KeyInfo = &DmxSet->DmxKeyInfo[*KeyId];

    mutex_lock(&KeyInfo->LockKey);

    KeyInfo->DmxId         = DmxId;
    KeyInfo->KeyId          = *KeyId;
    KeyInfo->Owner         = task_tgid_nr(current);
    KeyInfo->CaType       = Attr->enCaType;
    KeyInfo->CaEntropy    = Attr->enEntropyReduction;
    KeyInfo->DescType     = Attr->enDescramblerType;
    KeyInfo->KeyLen       = DMX_KEY_MAX_LEN / sizeof(HI_U32);

    set_bit(*KeyId, DmxSet->KeyBitmap);

    mutex_unlock(&KeyInfo->LockKey);

    ret = HI_SUCCESS;

out:
    return ret;
}

static inline HI_S32 DmxKeyRelease(HI_U32 DmxId, const HI_U32 KeyId)
{
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    BUG_ON(KeyId >= DmxSet->DmxKeyCnt);
    BUG_ON(!mutex_is_locked(&KeyInfo->LockKey));

    /* 98mv200_vmx_ultra use the the old version secure os */
#if defined(DMX_TEE_SUPPORT) && !(defined(HI_ADVCA_TYPE_VERIMATRIX_ULTRA) && defined(CHIP_TYPE_hi3798mv200))
    if (unlikely(__DmxKeyRelease(DmxId, KeyId) != HI_SUCCESS))
    {
        HI_ERR_DEMUX("can not release key(%d) from tee!\n", KeyId);
        return HI_FAILURE;
    }
#endif

    DescramblerReset(DmxSet, KeyId, KeyInfo);

    clear_bit(KeyId, DmxSet->KeyBitmap);

    return HI_SUCCESS;
}

/*
 * exclusively get and put key instance helper functions.
 */
HI_S32 DmxGetKeyInstance(Dmx_Set_S *DmxSet, HI_U32 KeyId)
{
    HI_S32 ret = HI_FAILURE;
    unsigned long mask, *p;
    DMX_KeyInfo_S  *KeyInfo = HI_NULL;

    if (unlikely(!DmxSet))
    {
        HI_ERR_DEMUX("Invalid DemuxSet.\n");
        ret = HI_ERR_DMX_INVALID_PARA;
        goto out0;
    }

    if (unlikely(KeyId >= DmxSet->DmxKeyCnt))
    {
        HI_ERR_DEMUX("Invalid key id :0x%x\n", KeyId);

        ret = HI_ERR_DMX_INVALID_PARA;
        goto out0;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    if (unlikely(0 != mutex_lock_interruptible(&KeyInfo->LockKey)))
    {
        HI_WARN_DEMUX("Key mutex interruptibled.\n");

        ret = HI_ERR_DMX_BUSY_KEY;
        goto out0;
    }

    mask = BIT_MASK(KeyId);
    p = ((unsigned long*)DmxSet->KeyBitmap) + BIT_WORD(KeyId);
    if (unlikely(!(*p & mask)))
    {
        HI_ERR_DEMUX("This Key(%d) instance has not alloced.\n", KeyId);
        ret = HI_ERR_DMX_INVALID_PARA;
        goto out1;
    }

    return HI_SUCCESS;

out1:
    mutex_unlock(&KeyInfo->LockKey);
out0:
    return ret;
}

HI_VOID DmxPutKeyInstance(Dmx_Set_S *DmxSet, HI_U32 KeyId)
{
    DMX_KeyInfo_S  *KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    BUG_ON(KeyId >= DmxSet->DmxKeyCnt);

    mutex_unlock(&KeyInfo->LockKey);
}

HI_VOID DescramblerReset(Dmx_Set_S *DmxSet, HI_U32 KeyId, DMX_KeyInfo_S *KeyInfo)
{
    KeyInfo->DmxId = DMX_INVALID_DEMUX_ID;
    KeyInfo->KeyId = DMX_INVALID_KEY_ID;
    KeyInfo->CaType = HI_UNF_DMX_CA_BUTT;

#ifdef HI_DEMUX_PROC_SUPPORT
    KeyInfo->ChanCount = 0;
    KeyInfo->AttachDescCnt = 0;
    KeyInfo->DetachDescCnt = 0;
    KeyInfo->SetOddKeyCnt = 0;
    KeyInfo->SetEvenKeyCnt = 0;

    memset(KeyInfo->EvenKey, 0, sizeof(KeyInfo->EvenKey));
    memset(KeyInfo->OddKey, 0, sizeof(KeyInfo->OddKey));
#endif
}

static HI_U32 DescGetTableId(HI_UNF_DMX_DESCRAMBLER_TYPE_E DescType)
{
    switch (DescType)
    {
        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 :
            return 0;

        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3 :
            return 1;

        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_IDSA :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB_L :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_L :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CTR :
            return 2;

        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CI :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CBC :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_NS :
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_NS :
        default :
            return 3;
    }
}

/* set clear cw only */
static HI_S32 DMXDescramblerSetKey(HI_U32 DmxId, HI_U32 KeyId, DMX_KEY_TYPE_E KeyType, HI_U8 *Key)
{
    HI_S32 ret = HI_SUCCESS;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = HI_NULL;
    HI_U32 i;

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out0;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    /* clear the cw as 0 */
    for (i = 0; i < KeyInfo->KeyLen; i++)
    {
        DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)Key)[i], KeyType, DMX_KEY_CW, KeyInfo->DescType);
    }

    DmxPutKeyInstance(DmxSet, KeyId);

out0:
    return ret;
}

HI_S32 DescCreate(HI_U32 DmxId, HI_U32 KeyId, HI_U32 CaType, HI_U32 DescType, HI_U32 CaEntropy)
{
    Dmx_Set_S * DmxSet = GetDmxSetByDmxid(DmxId);
    HI_U8 key[DMX_KEY_MAX_LEN]    = {0};

    DmxHalSetSecureKey(DmxSet, KeyId);

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 == DescType)
    {
        DmxHalSetEntropyReduction(DmxSet, KeyId, CaEntropy);
    }

    /* eable asa core clock */
    if (HI_UNF_DMX_DESCRAMBLER_TYPE_ASA == DescType)
    {
        DmxHalAsaClkSet(DmxSet, HI_TRUE);
    }

    /* eable sms4 core clock */
    if (HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_NS   == DescType
     || HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_IPTV == DescType
     || HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_ECB  == DescType
     || HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_CBC  == DescType)
    {
        DmxHalSms4ClkSet(DmxSet, HI_TRUE);
    }

    /* eable csa3 core clock */
    if (HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3 == DescType)
    {
        DmxHalCsa3ClkSet(DmxSet, HI_TRUE);
    }

    /* Enable IV set */
    DmxHalSetDmxIvEnable(DmxSet, DmxId, HI_TRUE);

    /* clear the iv and cw when creating the descrambler */
    DMX_OsiDescramblerSetIVKey(DmxId, KeyId, DMX_KEY_TYPE_EVEN, key);
    DMX_OsiDescramblerSetIVKey(DmxId, KeyId, DMX_KEY_TYPE_ODD, key);
    DMXDescramblerSetKey(DmxId, KeyId, DMX_KEY_TYPE_EVEN, key);
    DMXDescramblerSetKey(DmxId, KeyId, DMX_KEY_TYPE_ODD, key);

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA == DescType)
    {
        HI_S32 i = 0;
        /* the revert order of 0x445642544d4350544145534349535341 from ETSI TS 103 127 V1.1.1 (2013-05) */
        HI_U8 aes_cissa_iv[DMX_KEY_MAX_LEN] = {0x41, 0x53, 0x53, 0x49, 0x43, 0x53, 0x45, 0x41, 0x54, 0x50, 0x43, 0x4d, 0x54, 0x42, 0x56, 0x44};

        HI_WARN_DEMUX("Set the initial constant IV value for AES_CISSA\n");

        for (i = 0; i < 4; i++)
        {
            DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)aes_cissa_iv)[i], DMX_KEY_TYPE_EVEN, DMX_KEY_IV, DescType);
        }

        for (i = 0; i < 4; i++)
        {
            DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)aes_cissa_iv)[i], DMX_KEY_TYPE_ODD, DMX_KEY_IV, DescType);
        }
    }

    return HI_SUCCESS;
}

HI_S32 DescKeyDetach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId)
{
    HI_S32 ret;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_ChanInfo_S *ChanInfo    = &DmxSet->DmxChanInfo[ChanId];
    DMX_KeyInfo_S  *KeyInfo     = HI_NULL;

    if (unlikely(DMX_INVALID_KEY_ID == ChanInfo->KeyId))
    {
        HI_ERR_DEMUX("Channel %d has not attached any descrambler\n", ChanId);
        ret = HI_ERR_DMX_NOATTACH_KEY;
        goto out;
    }

    if (unlikely(ChanInfo->KeyId != KeyId))
    {
        HI_ERR_DEMUX("Detach Wrong Key(%d) from channel %d\n", KeyId, ChanId);
        ret = HI_ERR_DMX_UNMATCH_KEY;
        goto out;
    }

    if (unlikely(GetDmxSetByDmxid(ChanInfo->DmxId) != DmxSet))
    {
        HI_ERR_DEMUX("Channel(%d) attached with demux(%d) ,not demux(%d).\n", ChanId, ChanInfo->DmxId, DmxId);
        ret =  HI_ERR_DMX_INVALID_PARA;
        goto out;
    }

    ChanInfo->KeyId = DMX_INVALID_KEY_ID;

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];
#ifdef HI_DEMUX_PROC_SUPPORT
    -- KeyInfo->ChanCount;
    ++ KeyInfo->DetachDescCnt;
#endif

    DmxHalSetChannelCWIndex(DmxSet, ChanId, 0);
    DmxHalSetChanCwTabId(DmxSet, ChanId, 0);
    DmxHalSetChannelDsc(DmxSet, ChanId, HI_FALSE);

    ret = HI_SUCCESS;

out:
    return ret;
}

static HI_S32 DmxDescramblerCheckSupport(HI_UNF_DMX_CA_TYPE_E CaType, HI_UNF_DMX_DESCRAMBLER_TYPE_E DescramblerType, U_CA_INFO0 CaInfo)
{
    U_CA_INFO0 mask;
    HI_U32 value;

    mask.value = 0;
    switch (DescramblerType)
    {
        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2:
            mask.bits.dis_csa2 = 1;
            mask.bits.hardonly_csa2 = 1;
            break;

#ifdef DMX_DESCRAMBLER_TYPE_CSA3_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3:
            mask.bits.dis_csa3 = 1;
            mask.bits.hardonly_csa3 = 1;
            break;
#endif

#if defined(DMX_DESCRAMBLER_TYPE_SPE_SUPPORT)
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_IDSA:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA:
            mask.bits.dis_spe = 1;
            mask.bits.hardonly_spe = 1;
            break;

#elif defined(DMX_DESCRAMBLER_TYPE_SPE_V2_SUPPORT)
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_IDSA:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB:
            mask.bits.dis_spe = 1;
            mask.bits.hardonly_spe = 1;
            break;

        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA:
            mask.bits.dis_spe = 1;
            mask.bits.hardonly_aes_cbc = 1;
            break;

        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_ECB_L:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_L:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CTR:
            mask.bits.dis_spe = 1;
            mask.bits.hardonly_ctr_clr = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_DES_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CI:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_CBC:
            mask.bits.dis_des = 1;
            mask.bits.hardonly_des = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_DES_IPTV_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_DES_IPTV:
            mask.bits.dis_des = 1;
            mask.bits.hardonly_des = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_AES_NS_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_AES_NS:
            mask.bits.dis_novel = 1;
            mask.bits.hardonly_novel = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_SMS4_NS_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_NS:
            mask.bits.dis_novel = 1;
            mask.bits.hardonly_novel = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_SMS4_IPTV_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_IPTV:
            mask.bits.dis_others = 1;
            mask.bits.hardonly_others = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_SMS4_ECB_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_ECB:
            mask.bits.dis_others = 1;
            mask.bits.hardonly_others = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_SMS4_CBC_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_SMS4_CBC:
            mask.bits.dis_others = 1;
            mask.bits.hardonly_others = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_TDES_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_IPTV:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_ECB:
        case HI_UNF_DMX_DESCRAMBLER_TYPE_TDES_CBC:
            mask.bits.dis_tdes = 1;
            mask.bits.hardonly_others = 1;
            break;
#endif

#ifdef DMX_DESCRAMBLER_TYPE_ASA_SUPPORT
        case HI_UNF_DMX_DESCRAMBLER_TYPE_ASA:
#if (!defined(CHIP_TYPE_hi3716mv410)) && (!defined(CHIP_TYPE_hi3716mv420))
            mask.bits.dis_asa = 1;
#endif
            mask.bits.hardonly_others = 1;
            break;
#endif

        default:
            return HI_ERR_DMX_NOT_SUPPORT;
    }

    value = mask.value & CaInfo.value;

    /*hardonly*/
    if ((value & 0xFF) && (CaType == HI_UNF_DMX_CA_NORMAL))
    {
        return HI_ERR_DMX_NOT_SUPPORT;
    }

    /*disable*/
    value >>= 8;
    if (value  & 0x7F)
    {
#if defined(HI_DEBUG) && (HI_LOG_LEVEL >= HI_TRACE_LEVEL_WARN)
        HI_CHAR WarnStr[][20] = {
                "disable CSA2\n",
                "disable SPE\n",
                "disable DES\n",
                "disable novel\n",
                "disable CSA3\n",
                "disable others\n",
                "disable TDES\n",
                "disable multi2\n",
                "disable ASA\n",
            };
        HI_U32 WarnStrNum = sizeof(WarnStr)/sizeof(WarnStr[0]);
        HI_U32 i;

        for ( i=0; i<WarnStrNum; i++)
        {
            if (value & 1)
            {
                HI_WARN_DEMUX(WarnStr[i]);
                break;
            }
            value >>= 1;
        }
#endif
        return HI_ERR_DMX_NOT_SUPPORT;
    }

    return HI_SUCCESS;
}

/***********************************************************************************
* Function      : DMXDescramblerCreate
* Description   : create a new descrambler
* Input         :
* Output        : KeyId
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others:
***********************************************************************************/
HI_S32 DMXDescramblerCreate(HI_U32 DmxId, HI_U32 *KeyId, HI_UNF_DMX_DESCRAMBLER_ATTR_S *Attr)
{
    HI_S32 ret = HI_ERR_DMX_NOFREE_KEY;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    U_CA_INFO0   CaInfo;

    if (!DmxSet)
    {
        return HI_ERR_DMX_INVALID_PARA;
    }

    CaInfo.value = DmxHalGetOptCAType(DmxSet);

    ret = DmxDescramblerCheckSupport(Attr->enCaType, Attr->enDescramblerType, CaInfo);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    mutex_lock(&DmxSet->LockAllKey);

    ret = DmxKeyAcquire(DmxId, Attr, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    DescCreate(DmxId, *KeyId, Attr->enCaType, Attr->enDescramblerType, Attr->enEntropyReduction);

out:
    mutex_unlock(&DmxSet->LockAllKey);

    return ret;
}

HI_VOID DmxDescramblerResume(Dmx_Set_S *DmxSet)
{
    HI_U32 KeyId;

    for (KeyId = 0; KeyId < DmxSet->DmxKeyCnt; KeyId++)
    {
        DMX_KeyInfo_S *KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

        if (HI_UNF_DMX_CA_BUTT != KeyInfo->CaType)
        {
            DescCreate(KeyInfo->DmxId, KeyId, KeyInfo->CaType, KeyInfo->DescType, KeyInfo->CaEntropy);

#ifdef HI_DEMUX_PROC_SUPPORT
            KeyInfo->ChanCount = 0;

            DMX_OsiDescramblerSetKey(KeyInfo->DmxId, KeyId, DMX_KEY_TYPE_EVEN, (HI_U8*)KeyInfo->EvenKey);
            DMX_OsiDescramblerSetKey(KeyInfo->DmxId, KeyId, DMX_KEY_TYPE_ODD, (HI_U8*)KeyInfo->OddKey);
#endif
        }
    }
}

/***********************************************************************************
* Function      :   DMX_OsiNewDescrambler
* Description   :  apply a new descrambler
* Input         :
* Output        :  pKeyId
* Return        :  HI_SUCCESS:     success
*                  HI_FAILURE:
* Others:
***********************************************************************************/
HI_S32 DMX_OsiDescramblerCreate(HI_U32 DmxId, HI_U32 *KeyId, const HI_UNF_DMX_DESCRAMBLER_ATTR_S *DescAttr)
{
    HI_UNF_DMX_DESCRAMBLER_ATTR_S Attr;

    if ((HI_UNF_DMX_CA_NORMAL != DescAttr->enCaType) && (HI_UNF_DMX_CA_ADVANCE != DescAttr->enCaType))
    {
        HI_WARN_DEMUX("CaType=%d\n", DescAttr->enCaType);

        return HI_ERR_DMX_INVALID_PARA;
    }

    Attr.enCaType           = DescAttr->enCaType;
    Attr.enDescramblerType  = DescAttr->enDescramblerType;
    Attr.enEntropyReduction = HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE;

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 == DescAttr->enDescramblerType)
    {
        if (   (HI_UNF_DMX_CA_ENTROPY_REDUCTION_CLOSE   != DescAttr->enEntropyReduction)
            && (HI_UNF_DMX_CA_ENTROPY_REDUCTION_OPEN    != DescAttr->enEntropyReduction) )
        {
            HI_WARN_DEMUX("EntropyReduction=%d\n", DescAttr->enEntropyReduction);

            return HI_ERR_DMX_INVALID_PARA;
        }

        Attr.enEntropyReduction = DescAttr->enEntropyReduction;
    }

    return DMXDescramblerCreate(DmxId, KeyId, &Attr);
}

static HI_VOID DmxClsHwKey(HI_U32 DmxId, HI_U32 KeyId, HI_U32 DescCode)
{
#ifdef CA_FRAMEWORK_V200_SUPPORT
    s32 ret = HI_FAILURE;
    EXT_CLEAR_CW_KLAD_PARA_S stCfg = {0};
    KLAD_EXPORT_FUNC_S *KladFunc = HI_NULL;

    ret = HI_DRV_MODULE_GetFunction(HI_ID_CA, (HI_VOID**)&KladFunc);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_DEMUX("HI_DRV_MODULE_GetFunction failed!\n");
        return;
    }

    if ((HI_NULL == KladFunc) || (HI_NULL == KladFunc->pSetClearkey))
    {
        HI_ERR_DEMUX("Get klad function failed\n");
        return;
    }

    stCfg.handle   = DMX_KEYHANDLE(DmxId, KeyId);
    stCfg.enEngine = DescCode;
    stCfg.enSecEn  = KLAD_SEC_DISABLE;

    memset(stCfg.u8Key, 0x00, HI_UNF_KLAD_MAX_KEY_LEN);
    memset(stCfg.u8Key, 0xFF, HI_UNF_KLAD_MAX_KEY_LEN >> 1U);

    /* clear odd hw key */
    stCfg.bOdd     = HI_TRUE;
    ret = KladFunc->pSetClearkey(&stCfg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_DEMUX("klad_func->pSetClearkey failed,ret[0x%x]\n", ret);
        return;
    }

    /* clear even hw key */
    stCfg.bOdd     = HI_FALSE;
    ret = KladFunc->pSetClearkey(&stCfg);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_DEMUX("klad_func->pSetClearkey failed,ret[0x%x]\n", ret);
        return;
    }
#endif
    return;
}

/***********************************************************************************
* Function      : DMX_OsiDescramblerDestroy
* Description   : destroy a Descrambler
* Input         : KeyId
* Output        :
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others:
***********************************************************************************/
HI_S32 DMX_OsiDescramblerDestroy(HI_U32 DmxId, HI_U32 KeyId)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = HI_NULL;
    HI_U32 RawDescCdoe = 0;
    HI_U32 ChanId;

    if (unlikely(!DmxSet))
    {
        HI_ERR_DEMUX("Invalid DemuxSet.\n");
        ret = HI_ERR_DMX_INVALID_PARA;
        goto out;
    }

    mutex_lock(&DmxSet->LockAllChn);

    for_each_set_bit(ChanId, DmxSet->ChnBitmap, DmxSet->DmxChanCnt)
    {
        DMX_ChanInfo_S *ChanInfo = &DmxSet->DmxChanInfo[ChanId];

        if (ChanInfo->KeyId == KeyId)
        {
            BUG_ON(ChanInfo->DmxId >= GetDmxCluster()->Ops->GetDmxNum());

            DMX_OsiDescramblerDetach(DmxId, KeyId, ChanId);
        }
    }

    mutex_unlock(&DmxSet->LockAllChn);

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    /* clear the hw keyvalue of keyladder */
    BUG_ON(KeyId >= DmxSet->DmxKeyCnt);
    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];
    BUG_ON(!mutex_is_locked(&KeyInfo->LockKey));
    if (HI_UNF_DMX_CA_ADVANCE == KeyInfo->CaType)  /* only hardware key need to clear */
    {
        DmxHalGetRawDescCode(KeyInfo->DescType, &RawDescCdoe);
        DmxClsHwKey(DmxId, KeyId, RawDescCdoe);
    }

    ret = DmxKeyRelease(DmxId, KeyId);

    DmxPutKeyInstance(DmxSet, KeyId);
out:
    return ret;
}

HI_S32 DMX_OsiDescramblerGetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_UNF_DMX_DESCRAMBLER_ATTR_S *pstDescramblerAttr)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = HI_NULL;

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    pstDescramblerAttr->enCaType = KeyInfo->CaType;
    pstDescramblerAttr->enDescramblerType = KeyInfo->DescType;
    pstDescramblerAttr->enEntropyReduction = KeyInfo->CaEntropy;

    ret = HI_SUCCESS;

    DmxPutKeyInstance(DmxSet, KeyId);
out:
    return ret;
}

HI_S32 DMX_OsiDescramblerSetAttr(HI_U32 DmxId, HI_U32 KeyId, HI_UNF_DMX_DESCRAMBLER_ATTR_S *pstDescramblerAttr)
{
    HI_S32 ret = HI_ERR_DMX_INVALID_PARA;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = HI_NULL;

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out0;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    /* Don't support change enEntropyReduction attr */
    if (KeyInfo->CaEntropy != pstDescramblerAttr->enEntropyReduction)
    {
        ret = HI_ERR_DMX_INVALID_PARA;
        goto out1;
    }

    /* New attr become effective after set new attr for descrambler */
    KeyInfo->CaType = pstDescramblerAttr->enCaType;
    KeyInfo->DescType = pstDescramblerAttr->enDescramblerType;

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA == KeyInfo->DescType)
    {
        HI_S32 i = 0;
        /* the revert order of 0x445642544d4350544145534349535341 from ETSI TS 103 127 V1.1.1 (2013-05) */
        HI_U8 aes_cissa_iv[DMX_KEY_MAX_LEN] = {0x41, 0x53, 0x53, 0x49, 0x43, 0x53, 0x45, 0x41, 0x54, 0x50, 0x43, 0x4d, 0x54, 0x42, 0x56, 0x44};
        HI_WARN_DEMUX("Set the initial constant IV value for AES_CISSA\n");

        for (i = 0; i < 4; i++)
        {
            DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)aes_cissa_iv)[i], DMX_KEY_TYPE_EVEN, DMX_KEY_IV, KeyInfo->DescType);
        }

        for (i = 0; i < 4; i++)
        {
            DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)aes_cissa_iv)[i], DMX_KEY_TYPE_ODD, DMX_KEY_IV, KeyInfo->DescType);
        }

    }

    ret = HI_SUCCESS;

out1:
    DmxPutKeyInstance(DmxSet, KeyId);
out0:
    return ret;
}

HI_S32 DMX_OsiDescramblerSetKey(HI_U32 DmxId, HI_U32 KeyId, DMX_KEY_TYPE_E KeyType, HI_U8 *Key)
{
    HI_S32 ret = HI_SUCCESS;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S *KeyInfo = HI_NULL;
    HI_U32 i;
#ifdef CA_FRAMEWORK_V100_SUPPORT
    DRV_ADVCA_EXTFUNC_PARAM_S stAdvcaFuncParam = {0};
#endif
    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out0;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

#ifdef HI_DEMUX_PROC_SUPPORT
    for (i = 0; i < KeyInfo->KeyLen; i++)
    {
        if (DMX_KEY_TYPE_EVEN == KeyType)
        {
            KeyInfo->EvenKey[i] = ((HI_U32*)Key)[i];
        }
        else
        {
            KeyInfo->OddKey[i] = ((HI_U32*)Key)[i];
        }
    }

    /* add ref for set */
    if (DMX_KEY_TYPE_EVEN == KeyType)
    {
        KeyInfo->SetEvenKeyCnt ++;
    }
    else
    {
        KeyInfo->SetOddKeyCnt ++;
    }
#endif

    if (HI_UNF_DMX_CA_NORMAL == KeyInfo->CaType)
    {
        for (i = 0; i < KeyInfo->KeyLen; i++)
        {
            DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)Key)[i], KeyType, DMX_KEY_CW, KeyInfo->DescType);
        }
    }
#ifdef CA_FRAMEWORK_V100_SUPPORT
    else
    {
        /*change as get the function pointer every time when setting CW*/
        ret = HI_DRV_MODULE_GetFunction(HI_ID_CA, (HI_VOID**)&g_pAdvcaFunc);
        if (HI_SUCCESS != ret)
        {
            ret = HI_ERR_DMX_NOT_SUPPORT;
            goto out1;
        }

        if (g_pAdvcaFunc && g_pAdvcaFunc->pfnAdvcaCrypto)
        {
            memset(&stAdvcaFuncParam, 0, sizeof(stAdvcaFuncParam));

            if (HI_UNF_DMX_DESCRAMBLER_TYPE_CSA2 == KeyInfo->DescType)
            {
                stAdvcaFuncParam.enCAType = HI_UNF_CIPHER_CA_TYPE_CSA2;
            }
            else if (HI_UNF_DMX_DESCRAMBLER_TYPE_CSA3 == KeyInfo->DescType)
            {
                stAdvcaFuncParam.enCAType = HI_UNF_CIPHER_CA_TYPE_CSA3;
            }
            else
            {
                stAdvcaFuncParam.enCAType = HI_UNF_CIPHER_CA_TYPE_SP;
            }

            stAdvcaFuncParam.AddrID = KeyId;
            stAdvcaFuncParam.EvenOrOdd = KeyType;
            stAdvcaFuncParam.pu8Data = (HI_U8 *)Key;
            stAdvcaFuncParam.bIsDeCrypt = HI_TRUE;
            stAdvcaFuncParam.enTarget = DRV_ADVCA_CA_TARGET_DEMUX;
            ret = (g_pAdvcaFunc->pfnAdvcaCrypto)(stAdvcaFuncParam);
        }
    }
out1:
#endif
    DmxPutKeyInstance(DmxSet, KeyId);
out0:
    return ret;
}

HI_S32 DMX_OsiDescramblerSetIVKey(HI_U32 DmxId, HI_U32 KeyId, DMX_KEY_TYPE_E KeyType, HI_U8 *Key)
{
    HI_S32 ret = HI_FAILURE;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S  *KeyInfo = HI_NULL;
    HI_U8          tmp[DMX_KEY_MAX_LEN];
    HI_U32          i;

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out0;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CISSA == KeyInfo->DescType)
    {
        HI_WARN_DEMUX("AES_CISSA doesn't need to set IV!\n");
        ret = HI_SUCCESS;
        goto out1;
    }

    memcpy(tmp, Key, DMX_KEY_MAX_LEN);

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CI == KeyInfo->DescType  ||
        HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC == KeyInfo->DescType ||
        HI_UNF_DMX_DESCRAMBLER_TYPE_AES_IPTV == KeyInfo->DescType)    //change iv cw order, AES CI+ AES IPTV request
    {
        HI_U32  len = KeyInfo->KeyLen * sizeof(HI_U32);
        for (i = 0 ; i < len; i++)
        {
            tmp[i] = Key[len - i - 1];
        }
    }

    if (HI_UNF_DMX_DESCRAMBLER_TYPE_AES_CBC_IDSA == KeyInfo->DescType)
    {
        HI_WARN_DEMUX("AES_CBC_IDSA need to set 0 IV!\n");
        memset(tmp, 0x0, DMX_KEY_MAX_LEN);
    }

    for (i = 0; i < KeyInfo->KeyLen; i++)
    {
        DmxHalSetCWWord(DmxSet, KeyId, i, ((HI_U32*)tmp)[i], KeyType, DMX_KEY_IV, KeyInfo->DescType);
    }

    ret = HI_SUCCESS;

out1:
    DmxPutKeyInstance(DmxSet, KeyId);
out0:
    return ret;
}

/***********************************************************************************
* Function      : DMX_OsiDescramblerAttach
* Description   : attcg  Descrambler to channel
* Input         : KeyId, ChanId
* Output        :
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others        :
***********************************************************************************/
HI_S32 DMX_OsiDescramblerAttach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId)
{
    HI_S32 ret;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_ChanInfo_S *ChanInfo = HI_NULL;
    DMX_KeyInfo_S  *KeyInfo = HI_NULL;

    ret = DmxGetChnInstance(DmxSet, ChanId);
    if (HI_SUCCESS != ret)
    {
        goto out0;
    }

    ChanInfo = &DmxSet->DmxChanInfo[ChanId];

    if (GetDmxSetByDmxid(ChanInfo->DmxId) != DmxSet)
    {
        HI_ERR_DEMUX("Channel(%d) attached with demux(%d) ,not demux(%d).\n", ChanId, ChanInfo->DmxId, DmxId);
        ret =  HI_ERR_DMX_INVALID_PARA;
        goto out1;
    }

    if (unlikely(DMX_INVALID_KEY_ID != ChanInfo->KeyId))
    {
        ret = HI_ERR_DMX_ATTACHED_KEY;
        goto out1;
    }

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out1;
    }

    KeyInfo = &DmxSet->DmxKeyInfo[KeyId];

    ChanInfo->KeyId = KeyId;

#ifdef HI_DEMUX_PROC_SUPPORT
    ++ KeyInfo->ChanCount;
    ++ KeyInfo->AttachDescCnt;
#endif

    DmxHalSetChannelCWIndex(DmxSet, ChanId, KeyId);
    DmxHalSetChanCwTabId(DmxSet, ChanId, DescGetTableId(KeyInfo->DescType));
    DmxHalSetChannelDsc(DmxSet, ChanId, HI_TRUE);

    ret = HI_SUCCESS;

    DmxPutKeyInstance(DmxSet, KeyId);
out1:
    DmxPutChnInstance(DmxSet, ChanId);
out0:
    return ret;
}

/***********************************************************************************
* Function      : DMX_OsiDescramblerDetach
* Description   : dettach Descrambler from a channel
* Input         : KeyId, ChanId
* Output        :
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others        :
***********************************************************************************/
/*
 * upper caller must get channel instance.
 */
HI_S32 __DMX_OsiDescramblerDetach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId)
{
    HI_S32 ret;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);

    ret = DmxGetKeyInstance(DmxSet, KeyId);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    ret = DescKeyDetach(DmxId, KeyId, ChanId);

    DmxPutKeyInstance(DmxSet, KeyId);
out:
    return ret;
}

HI_S32 DMX_OsiDescramblerDetach(HI_U32 DmxId, HI_U32 KeyId, HI_U32 ChanId)
{
    HI_S32 ret;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);

    ret = DmxGetChnInstance(DmxSet, ChanId);
    if (HI_SUCCESS != ret)
    {
        goto out;
    }

    ret = __DMX_OsiDescramblerDetach(DmxId, KeyId, ChanId);

    DmxPutChnInstance(DmxSet, ChanId);
out:
    return ret;
}

/***********************************************************************************
* Function      : DMX_OsiDescramblerGetFreeKeyNum
* Description   : get free Descramber Num
* Input         :
* Output        : FreeCount
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others        :
***********************************************************************************/
HI_S32 DMX_OsiDescramblerGetFreeKeyNum(HI_U32 DmxId, HI_U32 *FreeCount)
{
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_KeyInfo_S  *KeyInfo = HI_NULL;
    HI_U32          i;

    if (!DmxSet)
    {
        return HI_ERR_DMX_INVALID_PARA;
    }

    KeyInfo     = DmxSet->DmxKeyInfo;

    *FreeCount = 0;

    for (i = 0; i < DmxSet->DmxKeyCnt; i++)
    {
        if (HI_UNF_DMX_CA_BUTT == KeyInfo[i].CaType)
        {
            ++(*FreeCount);
        }
    }

    return HI_SUCCESS;
}

/***********************************************************************************
* Function      : DMX_OsiDescramblerGetKeyId
* Description   : get key
* Input         : ChanId
* Output        : KeyId
* Return        : HI_SUCCESS
*                 HI_FAILURE
* Others        :
***********************************************************************************/
HI_S32 DMX_OsiDescramblerGetKeyId(HI_U32 DmxId, HI_U32 ChanId, HI_U32 *KeyId)
{
    HI_S32 ret = HI_ERR_DMX_NOATTACH_KEY;
    Dmx_Set_S *DmxSet = GetDmxSetByDmxid(DmxId);
    DMX_ChanInfo_S *ChanInfo = HI_NULL;

    ret = DmxGetChnInstance(DmxSet, ChanId);
    if (HI_SUCCESS != ret)
    {
        ret = HI_ERR_DMX_NOATTACH_KEY;
        goto out;
    }

    ChanInfo = &DmxSet->DmxChanInfo[ChanId];

    if (DMX_INVALID_KEY_ID != ChanInfo->KeyId)
    {
        BUG_ON(GetDmxSetByDmxid(ChanInfo->DmxId) != DmxSet);

        *KeyId = ChanInfo->KeyId;

        ret = HI_SUCCESS;
    }
    else
    {
        ret = HI_ERR_DMX_NOATTACH_KEY;
    }

    DmxPutChnInstance(DmxSet, ChanId);
out:
    return ret;
}

