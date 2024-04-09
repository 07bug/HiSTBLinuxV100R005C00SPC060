/******************************************************************************
 *
 * Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tee_drv_cenc.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-03-25
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_cenc.h"
#include "drv_symc.h"

#ifdef HI_SMMU_SUPPORT

#define CENC_MMU_NAME "cenc_buf"
#define DATA_UNIT_ODD_KEY                        (64)
#define CENC_FIRSTENCRYPTOFFSET_MAX_LEN          (AES_BLOCK_SIZE - 1)
#define CENC_IV_COUNTER_BYTE                     (8)

#define CENC_MMU_SIZE                            (0x1000)
#define CENC_SUBSAMPLE_MAX_NUM                   (100)
#define CENC_SUBSAMPLE_MAX_DATALEN               (0X100000)
#define CENC_MAX_DATALEN                         (0X2000000)

/* Max node number
 * For CTR padding, must large then 1
 */
#define CENC_MAX_NODE                            100

#define ALIGN64(x)                               (((x) + 63) & (~0x3F))
#define ALIGN16(x)                               (((x) + 15) & (~0x0F))
#define ALIGN4k(x)                               (((x) + 0xFFF) & (~0xFFF))

typedef struct
{
    u32 chn_num;
    u32 enc_len;                     /* Total length to decrypt */
    u32 ctr_counter;                 /* CTR IV Counter */
    u32 node_count;                  /* Total nodes to decrypt */
    CRYP_CIPHER_WORK_MODE_E enWorkMode;

    /* Init offset for clear data in Pattern
     * In original drivers, Pattern offset valid
     * for encrypt and clear data in CTR mode
     * But invalid for CBC mode
     * this may be a soft bug in original drivers.
     * as can't confirm it, here design it the
     * same with original drivers.
     */
    u32 enc_offset;                  /* Clear len in last Pattern for encrypt data */
    u32 clear_offset;                /* Clear len in last Pattern for clear data   */
    SMMU_BUFFER_S local;             /* local SMMU */
    u32 last_length;                 /* last local SMMU data length */
}cenc_info_s;

static cenc_info_s  cenc_info = {0};

void cenc_ddr_release(void)
{
    HI_LOG_FuncEnter();

    if (0x00 != cenc_info.local.u32Size)
    {
        HI_DRV_SMMU_UnmapAndRelease(&cenc_info.local);
        crypto_memset(&cenc_info.local, sizeof(cenc_info.local), 0, sizeof(cenc_info.local));
        HI_LOG_INFO("cenc release ddr\n");
    }

    HI_LOG_FuncExit();
    return ;
}

s32 cenc_ddr_alloc(u32 chn_num, u32 length)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    if (cenc_info.local.u32Size < length)
    {
        /* release the small mmz */
        cenc_ddr_release();

         /* allocate a large mmz, only support 32-bit ddr */
        ret = HI_DRV_SMMU_AllocAndMap(CENC_MMU_NAME, ALIGN4k(length), 0, &cenc_info.local);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(HI_DRV_SMMU_AllocAndMap, ret);
            return ret;
        }
        cenc_info.local.u32Size = ALIGN4k(length);
        HI_LOG_INFO("cenc alloc ddr, phy 0x%x, via %p, size 0x%x\n",
            cenc_info.local.u32StartSmmuAddr, cenc_info.local.pu8StartVirAddr, cenc_info.local.u32Size);

        /* release ddr when destory channel */
        drv_symc_set_destory_callbcak(chn_num, cenc_ddr_release);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_ddr_map(SMMU_BUFFER_S *input, SMMU_BUFFER_S *output)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = HI_DRV_SMMU_Map(input);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(HI_DRV_SMMU_Map, ret);
        return ret;
    }

    ret = HI_DRV_SMMU_Map(output);
    if (HI_SUCCESS != ret)
    {
        HI_DRV_SMMU_Unmap(input);
        HI_LOG_PrintFuncErr(HI_DRV_SMMU_Map, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_ddr_unmap(SMMU_BUFFER_S *input, SMMU_BUFFER_S *output)
{
    HI_LOG_FuncEnter();

    if (HI_NULL != input->pu8StartVirAddr)
    {
        HI_DRV_SMMU_Unmap(input);
    }

    if (HI_NULL != output->pu8StartVirAddr)
    {
        HI_DRV_SMMU_Unmap(output);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static HI_VOID cenc_config(u32 chn_num, CRYP_CIPHER_CTRL_S *ctrl)
{
    symc_mode mode = SYMC_MODE_CBC;

    if (CRYP_CIPHER_WORK_MODE_CTR == ctrl->enWorkMode)
    {
        mode = SYMC_MODE_CTR;
    }

    drv_symc_set_key(chn_num, ctrl->u32Key, HI_FALSE);
    drv_symc_config(chn_num, SYMC_ALG_AES, mode, SYMC_DAT_WIDTH_128,
            HI_TRUE, 0, SYMC_KEY_DEFAULT, ctrl->bKeyByCA);

    return;
}

static HI_VOID cenc_get_first_pattern(CRYP_CIPHER_SUBSAMPLE_EX_S *subsample_ex,
                                     u32 firstoffset,
                                     u32 *penclen, u32 *pu32DecLen)
{
    *penclen = 0x00;
    *pu32DecLen = 0x00;

    if ((0 == subsample_ex->u32PayloadPatternEncryptLen)
        && (0 == subsample_ex->u32PayloadPatternClearLen))
    {
        /* process non-pattern mode, all blocks in payload are encrypted
         * first pattern means the left length of first block
         */
        *penclen = (firstoffset == 0) ? 0x00 : AES_BLOCK_SIZE - firstoffset;
        *pu32DecLen = 0x00;
        return;
    }

    /* the head of payload may be part of last pattern in last subsample,
     * encrypt data stored in front of clear data
     * H | Pattern_offset(processed blocks)| First_offset(processed part of last block) | Part_last_Pattern_Blocks | E | C | E | C
     */
    if (subsample_ex->u32PayloadPatternOffsetLen < subsample_ex->u32PayloadPatternEncryptLen)
    {
        /* the processed data length less then encrypt data,
         * means still have some encrypt data request to process
         */
        *penclen = subsample_ex->u32PayloadPatternEncryptLen - subsample_ex->u32PayloadPatternOffsetLen - firstoffset;
        *pu32DecLen = subsample_ex->u32PayloadPatternClearLen;
    }
    else
    {
        /* have not encrypt data in first pattern */
        *penclen = 0x00;
        *pu32DecLen = (subsample_ex->u32PayloadPatternEncryptLen + subsample_ex->u32PayloadPatternClearLen) /* Pattern length*/
            - (subsample_ex->u32PayloadPatternOffsetLen + firstoffset);                             /* already processed length */
    }

    HI_LOG_INFO("First Pattern, enc_len 0x%x, dec len 0x%x\n", *penclen, *pu32DecLen);
}

/* CTR IV Counter
* when an 8 bytes Per_Sample_IV_Size is indicated,
* the least significant 8 bytes of the 16 bytes IV (bytes 8 to 15)
* SHALL be set to zero and used as a 64 bit block counter that is
* incremented by one for each subsequent 16 bytes cipher block offset of
* encrypted sample data.
*
* when an 16 bytes Per_Sample_IV_Size is indicated,
* the least significant 8 bytes(64 bit counter) reaches the maximum
* value(0xFFFFFFFFFFFFFFFF), then increamenting it SHALL reset the
* 8 bytes block counter to zero(bytes 8 to 15) without affecting
* the others 8 bytes of the counter(bytes 0 to 7).
*/
static u32 cenc_ctr128_iv_blocks(HI_U8* iv)
{
    u32 iv_number = 0;
    u32 id = CENC_IV_COUNTER_BYTE;

    /* high u32 */
    iv_number  = ((HI_U32)iv[id++]) << 24;
    iv_number |= ((HI_U32)iv[id++]) << 16;
    iv_number |= ((HI_U32)iv[id++]) << 8;
    iv_number |= ((HI_U32)iv[id++]);

    HI_LOG_INFO("high iv_number 0x%x\n", iv_number);
    if(iv_number != 0xFFFFFFFF)
    {
        /* blocks >= U32, return max value*/
        return 0xFFFFFFFF;
    }

    /* low u32 */
    iv_number  = ((HI_U32)iv[id++]) << 24;
    iv_number |= ((HI_U32)iv[id++]) << 16;
    iv_number |= ((HI_U32)iv[id++]) << 8;
    iv_number |= ((HI_U32)iv[id++]);
    HI_LOG_INFO("low iv_number 0x%x\n", iv_number);

    return (0xFFFFFFFF - iv_number) + 1;
}

/* CTR IV counter may be overflow, get the left length that can use current IV */
static u32 cenc_node_get_counter_length(u32 length)
{
    u32 counter = 0;
    u32 first_len = 0;

    HI_LOG_FuncEnter();

    /* as cenc data less than CENC_MAX_DATALE, below expression never overflow */
    counter = (cenc_info.enc_len + length + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;

    if (counter <= cenc_info.ctr_counter)
    {
        first_len = length;
    }
    else
    {
        /* as cenc_info.ctr_counter less than counter, below expression never overflow */
        first_len = cenc_info.ctr_counter * AES_BLOCK_SIZE - cenc_info.enc_len;
    }

    HI_LOG_INFO("CTR IV Counter 0x%x, total len 0x%x, cur len 0x%x, cur counter 0x%x, first len 0x%x\n",
        cenc_info.ctr_counter, cenc_info.enc_len, length, counter, first_len);

    HI_LOG_FuncExit();
    return first_len;
}

static s32 cenc_node_finish(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    if (0x00 == cenc_info.node_count)
    {
        return HI_SUCCESS;
    }

#ifdef CHIP_SYMC_VER_V100
    if (CRYP_CIPHER_WORK_MODE_CTR == cenc_info.enWorkMode)
    {
        compat_addr buf_phy;

       /* For version V100, hardware unsupport split joint data segment,
        * For CTR, must copy all data segment to a continuing DDR before decrypt,
        * then decrypt the continuing DDR after the data segment has been copied.
        */
        ADDR_H32(buf_phy) = 0x00;
        ADDR_L32(buf_phy) = cenc_info.local.u32StartSmmuAddr + cenc_info.last_length;
        ret = drv_symc_add_inbuf(cenc_info.chn_num, buf_phy, ALIGN16(cenc_info.enc_len), SYMC_NODE_USAGE_NORMAL);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
            return ret;
        }

        ret = drv_symc_add_outbuf(cenc_info.chn_num, buf_phy, ALIGN16(cenc_info.enc_len), SYMC_NODE_USAGE_LAST);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
            return ret;
        }
        cenc_info.last_length += cenc_info.enc_len;
    }
#endif
    drv_symc_add_buf_usage(cenc_info.chn_num, HI_TRUE, SYMC_NODE_USAGE_LAST);

    /* start decrypt */
    ret = drv_symc_start(cenc_info.chn_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_start, ret);
        return ret;
    }

    /* waitting decrypt finished */
    ret = drv_symc_wait_done(cenc_info.chn_num, CRYPTO_TIME_OUT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_wait_done, ret);
        return ret;
    }
    cenc_info.node_count = 0x00;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_node_update_iv(u32 *iv, u32 isback)
{
    s32 ret = HI_FAILURE;
    u32 cur_iv[CENC_IV_SIZE/WORD_WIDTH] = {0};
    u8 *u8iv = HI_NULL;
    u32 i;

    HI_LOG_FuncEnter();

    /* compute existing nodes */
    ret = cenc_node_finish();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_node_finish, ret);
        return ret;
    }

    if (HI_NULL == iv)
    {
        drv_symc_get_iv(cenc_info.chn_num, cur_iv);

        /* when an 16 bytes Per_Sample_IV_Size is indicated,
         * the least significant 8 bytes(64 bit counter) reaches the maximum
         * value(0xFFFFFFFFFFFFFFFF), then increamenting it SHALL reset the
         * 8 bytes block counter to zero(bytes 8 to 15) without affecting
         * the others 8 bytes of the counter(bytes 0 to 7).
         *
         * if byte 0~7 are zero, then the IV of last block
         * must be 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF,
         * as can't affecting the others 8 bytes of the counter(bytes 0 to 7),
         * here shall recovery the bytes 0 to 7 to 0xFFFFFFFFFFFFFFFF.
         */
        if (0x00 == cur_iv[2] && 0x00 == cur_iv[3])
        {
            /* IV overflow, byte 0~7 sub 1 */
            u8iv = (HI_U8*)cur_iv;
            for (i=0; i<CENC_IV_COUNTER_BYTE; i++)
            {
                u8iv[CENC_IV_COUNTER_BYTE - i -1] -= 0x01;
                if (0xFF != u8iv[CENC_IV_COUNTER_BYTE - i -1])
                {
                    break;
                }
            }
        }

        if (HI_TRUE == isback)
        {
            /* iv sub 1 */
            u8iv = (HI_U8*)cur_iv;
            for (i=0; i<CENC_IV_COUNTER_BYTE; i++)
            {
                u8iv[CENC_IV_SIZE - i -1] -= 0x01;
                if (0xFF != u8iv[CENC_IV_SIZE - i -1])
                {
                    break;
                }
            }
        }
    }
    else
    {
        crypto_memcpy(cur_iv, CENC_IV_SIZE, iv, CENC_IV_SIZE);
    }
    drv_symc_set_iv(cenc_info.chn_num, cur_iv, CENC_IV_SIZE, CIPHER_IV_CHANGE_ONE_PKG);
    cenc_info.ctr_counter = cenc_ctr128_iv_blocks((u8*)cur_iv);
    cenc_info.enc_len     = 0;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_node_addbuf(SMMU_BUFFER_S *inputBuffer,
                            SMMU_BUFFER_S *outputBuffer, u32 offset,
                            u32 length, symc_node_usage usage)
{
    s32 ret = HI_FAILURE;
    compat_addr buf_phy;
    u32 enclen = 0;

    if (0 == length)
    {
        return HI_SUCCESS;
    }

#ifdef CHIP_SYMC_VER_V100
    if (CRYP_CIPHER_WORK_MODE_CTR == cenc_info.enWorkMode)
    {
        /* For version V100, hardware unsupport split joint data segment,
         * For CTR, must copy all data segment to a continuing DDR before decrypt
         */
        crypto_memcpy(cenc_info.local.pu8StartVirAddr + cenc_info.last_length + cenc_info.enc_len,length,
            inputBuffer->pu8StartVirAddr + offset, length);
        cenc_info.node_count   += 0x01;
        cenc_info.enc_len      += length;
    }
    else
#endif
    {
        ADDR_H32(buf_phy) = 0x00;
        ADDR_L32(buf_phy) = inputBuffer->u32StartSmmuAddr + offset;
        ret = drv_symc_add_inbuf(cenc_info.chn_num, buf_phy, length, usage);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
            return ret;
        }

        ADDR_L32(buf_phy) = outputBuffer->u32StartSmmuAddr + offset;
        ret = drv_symc_add_outbuf(cenc_info.chn_num, buf_phy, length, SYMC_NODE_USAGE_LAST);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
            return ret;
        }

        cenc_info.node_count += 0x01;
        cenc_info.enc_len    += length;

        /* hardware support max 127 nodes, must start the hardware
         * before add next node when all nodes are used
         */
        if (CENC_MAX_NODE == cenc_info.node_count)
        {
            ret = cenc_node_finish();
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(cenc_node_finish, ret);
                return ret;
            }

            enclen = cenc_info.enc_len % AES_BLOCK_SIZE;

            /* Part of last block repuire to decrypted, pading the block to correct the IV */
            if ( 0 != enclen)
            {
                /* Reset the IV status */
                ret = cenc_node_update_iv(HI_NULL, HI_TRUE);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(cenc_node_update_iv, ret);
                    return ret;
                }

                ADDR_L32(buf_phy) = cenc_info.local.u32StartSmmuAddr + offset;
                ret = drv_symc_add_inbuf(cenc_info.chn_num, buf_phy, enclen, usage);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
                    return ret;
                }

                ADDR_L32(buf_phy) = cenc_info.local.u32StartSmmuAddr + offset;
                ret = drv_symc_add_outbuf(cenc_info.chn_num, buf_phy, enclen, SYMC_NODE_USAGE_LAST);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
                    return ret;
                }
                cenc_info.enc_len += enclen;
                cenc_info.node_count++;
            }
        }
    }

    return HI_SUCCESS;
}

static s32 cenc_node_init(u32 chn_num, HI_BOOL oddkey, CRYP_CIPHER_WORK_MODE_E enWorkMode,
                          u32 firstoffset, CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample)
{
    u32 enclen = 0, declen = 0;
    s32 ret = HI_FAILURE;
    symc_node_usage usage = SYMC_NODE_USAGE_NORMAL;

    HI_LOG_FuncEnter();

    if (oddkey & 0x01)
    {
        usage |= SYMC_NODE_USAGE_ODD_KEY;
    }

    /* Init cenc infotation, can't reset the value of cenc_info.local */
    cenc_info.chn_num    = chn_num;
    cenc_info.enWorkMode = enWorkMode;
    cenc_info.enc_offset   = 0x00;
    cenc_info.clear_offset = 0x00;
    cenc_info.ctr_counter  = 0x00;
    cenc_info.node_count   = 0x00;
    cenc_info.last_length  = 0x00;

    /* Part of last block repuire to processed ?
     * For CBC mode, firstoffset always be zero
     */
    if (0 != firstoffset)
    {
        (void)cenc_get_first_pattern(pstSubsample, firstoffset, &enclen, &declen);
        if ( 0 != enclen)
        {
            /* set enclen to padding length */
            enclen = firstoffset;
        }
    }

    /* For CTR, the enclen may be not zero */
    if (0x00 != enclen)
    {
        if (HI_TRUE == pstSubsample->u32IvChange)
        {
            ret = cenc_node_update_iv(pstSubsample->u32IV, HI_FALSE);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(cenc_node_update_iv, ret);
                return ret;
            }

            /* need't set iv for subsample 0 any more */
            pstSubsample->u32IvChange = HI_FALSE;
        }
        else
        {
            ret = cenc_node_update_iv(HI_NULL, HI_TRUE);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(cenc_node_update_iv, ret);
                return ret;
            }
        }

        /* Part of last block repuire to decrypted, pading the block to correct the IV */
        ret = cenc_node_addbuf(&cenc_info.local, &cenc_info.local, 0, enclen, usage);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_node_addbuf, ret);
            return ret;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static u32 cenc_get_encrypt_len(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample,
                                u32 firstoffset, u32 index,
                                u32 *out_offset, u32 *out_length)
{
    u32 pattern_len   = 0;
    u32 subsample_len = 0;
    u32 skip = 0;
    u32 enclen = 0, u32DecLen = 0;
    u32 offset = 0, length = 0;
    u32 cleft = 0;

    subsample_len = pstSubsample->u32ClearHeaderLen + pstSubsample->u32PayLoadLen;
    pattern_len   = pstSubsample->u32PayloadPatternEncryptLen + pstSubsample->u32PayloadPatternClearLen;

    if (CRYP_CIPHER_WORK_MODE_CTR == enWorkMode)
    {
        /*Pattern offset valid for encrypt and clear data in CTR mode
        * But invalid for CBC mode
        */
        cleft = cenc_info.enc_offset;
    }

    if ((0 == pstSubsample->u32PayloadPatternEncryptLen)
        && (0 == pstSubsample->u32PayloadPatternClearLen))
    {
        /* process non-pattern mode, all blocks in payload are encrypted */

        *out_offset = pstSubsample->u32ClearHeaderLen;
        *out_length = pstSubsample->u32PayLoadLen;
         skip    = subsample_len;

        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            /* less than 16 bytes are clear */
            *out_length &= ~0x0F;
        }

        return skip;
    }

    /* pattern mode */
    if ( 0 == index)
    {
        /* Process first pattern */
        cenc_get_first_pattern(pstSubsample, firstoffset, &enclen, &u32DecLen);

        /* PatternOffsetLen valid for encrypt data, but not clear data */
        offset = pstSubsample->u32ClearHeaderLen + cleft;
        length = enclen; /* may be zero */
        skip   = pstSubsample->u32ClearHeaderLen  + cleft + enclen + u32DecLen;
        cleft  = 0;
    }
    else
    {
        /* process integrated pattern */
        offset = index;
        length = pstSubsample->u32PayloadPatternEncryptLen;
        skip   = pattern_len; /* skip one pattern */
    }

    /* check overflow */
    if ((length + offset) > subsample_len)
    {
        length = subsample_len - offset;
        skip = subsample_len - index;

        /* encrypt length overflow, set it to the tail of subsample */
        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            /*less than 16 bytes are clear */
            length = (subsample_len - offset) & (~0x0F);
        }
    }
    else if ((index + skip) > subsample_len)
    {
        /* decrypt length overflow, set it to the tail of subsample */
        cleft  = (index + skip) - subsample_len;
        skip = subsample_len - index;
    }

    *out_offset   = offset;
    *out_length   = length;
    cenc_info.enc_offset = cleft;

    return skip;
}

static u32 cenc_get_clear_len(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                              CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample,
                              u32 firstoffset, u32 index,
                              u32 *out_offset, u32 *out_length)
{
    u32 pattern_len   = 0;
    u32 subsample_len = 0;
    u32 skip = 0;
    u32 enclen = 0, u32DecLen = 0;
    u32 offset = 0, length = 0;
    u32 cleft = 0;

    subsample_len = pstSubsample->u32ClearHeaderLen + pstSubsample->u32PayLoadLen;
    pattern_len   = pstSubsample->u32PayloadPatternEncryptLen + pstSubsample->u32PayloadPatternClearLen;
    offset        = index;

    if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
    {
        /* cbc will not encrypt the bytes less than 16. */
        if (AES_BLOCK_SIZE > (subsample_len - index))
        {
            /* encrypt block must >=16, so here the tail must be clear data */
            skip    = subsample_len - index;
            length = subsample_len - index;

            *out_offset = offset;
            *out_length = length;
            return skip;
        }

        /*Pattern offset valid for encrypt and clear data in CBC mode */
         cleft = 0;
    }
    else
    {
        /*Pattern offset valid for encrypt but invalid for clear data in CTR mode */
        cleft = cenc_info.clear_offset;
    }

    /*  non-pattern mode ? */
    if ((0 == pstSubsample->u32PayloadPatternEncryptLen)
        && (0 == pstSubsample->u32PayloadPatternClearLen))
    {
        /* all blocks in payload are encrypted */
        length = pstSubsample->u32ClearHeaderLen;
        skip   = pstSubsample->u32ClearHeaderLen;

        /* the CBC mode does not encrypt Blocks smaller than 16 Bytes */
        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            skip += pstSubsample->u32PayLoadLen & ~0x0F;
        }
        else
        {
            skip += pstSubsample->u32PayLoadLen;
        }

        *out_offset = offset;
        *out_length = length;
        return skip;
    }

    /* pattern mode */

    if ( 0 == index) /* first pattern may be incomplete */
    {
        /* clear head */
        length  = pstSubsample->u32ClearHeaderLen + cleft;
        skip    = pstSubsample->u32ClearHeaderLen + cleft;
        cleft   = 0;

        /* Process first pattern */
        cenc_get_first_pattern(pstSubsample, firstoffset, &enclen, &u32DecLen);
        if (0 != enclen)
        {
            /* Skip encrypt data in first pattern */
            skip += enclen;
        }
        else
        {
            length += u32DecLen;

            /* Skip clear data in first pattern and next pattern's encrypt data */
            skip   += u32DecLen + pstSubsample->u32PayloadPatternEncryptLen;
        }
    }
    else /* process complete pattern */
    {
        length = pstSubsample->u32PayloadPatternClearLen;
        skip   = pattern_len;
    }

    /* check overflow */
    if ((length + offset) > subsample_len)
    {
        /* clear data length overflow, set it to the tail of subsample */
        cleft  = (length + offset) - subsample_len;
        length = subsample_len - offset;
        skip   = subsample_len - offset;

        *out_offset = offset;
        *out_length = length;
        cenc_info.clear_offset = cleft;
        return skip;
    }

    /* here the encrypt data must be cut */
    if ((index + skip) > subsample_len)
    {
        skip = subsample_len - index;
        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            skip -= pstSubsample->u32PayLoadLen % AES_BLOCK_SIZE;
        }
    }

    *out_offset = offset;
    *out_length = length;
    cenc_info.clear_offset = cleft;
    return skip;
}

static s32 cenc_copy_clear_subsample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                        u32 firstoffset,
                                        SMMU_BUFFER_S *inputBuffer,
                                        SMMU_BUFFER_S *outputBuffer,
                                        CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample)
{
    u32 index = 0;
    u32 subsample_len = 0;
    u32 offset = 0;
    u32 length = 0;
    u32 skip = 0;

    HI_LOG_FuncEnter();

    subsample_len = pstSubsample->u32ClearHeaderLen + pstSubsample->u32PayLoadLen;

    while (index < subsample_len)
    {
        skip = cenc_get_clear_len(enWorkMode, pstSubsample, firstoffset,
                                       index, &offset, &length);
        HI_LOG_INFO("CBC Pattern clear data, index 0x%x, offset 0x%x, len 0x%x, skip 0x%x\n",
            index, offset, length, skip);

        if ( 0 != length)
        {
            if ((outputBuffer->u32Size + offset < offset)
                || (outputBuffer->u32Size + offset + length < length)
                || (subsample_len < length))
            {
                HI_LOG_ERROR("invalid reversal data length,");
                return HI_FAILURE;
            }
            crypto_memcpy(outputBuffer->pu8StartVirAddr + offset, subsample_len,
                inputBuffer->pu8StartVirAddr + offset, length);
        }

        index += skip;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_add_dec_subsample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                HI_BOOL oddkey, u32 first_offset,
                                SMMU_BUFFER_S *inputBuffer,
                                SMMU_BUFFER_S *outputBuffer,
                                CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample)
{
    s32 ret = HI_FAILURE;
    u32 index = 0;
    u32 subsample_len = 0;
    u32 offset = 0;
    u32 length = 0, enclen = 0;
    u32 skip = 0;
    symc_node_usage usage = SYMC_NODE_USAGE_NORMAL;

    HI_LOG_FuncEnter();

    if (oddkey & 0x01)
    {
        usage |= SYMC_NODE_USAGE_ODD_KEY;
    }

    subsample_len = pstSubsample->u32ClearHeaderLen + pstSubsample->u32PayLoadLen;
    while (index < subsample_len)
    {
        /* get a pattern's encrypt data from subsample */
        skip = cenc_get_encrypt_len(enWorkMode, pstSubsample, first_offset, index, &offset, &length);
        HI_LOG_INFO("Pattern encrypt data, index 0x%x, enc offset 0x%x, len 0x%x, skip 0x%x, usage 0x%x\n",
            index, offset, length, skip, usage);

        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            /* hardhawre will not decrypt the bytes less than 16,
             * but will update the IV, this will cause the iv
             * be incorrect for next subsample, so we can't
             * decrypt the bytes less than 16
             */
            enclen = length & ~0x0F;
        }
        else /* CTR */
        {
            enclen = cenc_node_get_counter_length(length);
            if (length > enclen)
            {
                /* IV overflow, split it to 2 nodes
                 * as total length of cenc data less than CENC_MAX_DATALEN,
                 * iv overflow may but only appear once.
                 */
                ret = cenc_node_addbuf(inputBuffer, outputBuffer, offset, enclen, usage | SYMC_NODE_USAGE_LAST);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(cenc_node_addbuf, ret);
                    return ret;
                }
                offset += enclen;
                length -= enclen;

                /* reset the 8 bytes block counter to zero(bytes 8 to 15)
                 * without affecting the others 8 bytes of the counter(bytes 0 to 7)
                 */
                ret = cenc_node_update_iv(HI_NULL, HI_FALSE);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(cenc_node_update_iv, ret);
                    return ret;
                }
            }
        }

        ret = cenc_node_addbuf(inputBuffer, outputBuffer, offset, length, usage);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_node_addbuf, ret);
            return ret;
        }
        index  += skip;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_add_subsample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                            HI_BOOL oddkey,
                            SMMU_BUFFER_S *inputBuffer,
                            SMMU_BUFFER_S *outputBuffer,
                            u32 first_offset,
                            CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubSample)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    /* set iv for subsample without subsample 0,
     * iv of subsample 0 is already set at start
     */
    if (HI_TRUE == pstSubSample->u32IvChange)
    {
        ret = cenc_node_update_iv(pstSubSample->u32IV, HI_FALSE);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_node_update_iv, ret);
            return ret;
        }
    }

    /* copy encrypt data to node list */
    ret = cenc_add_dec_subsample(enWorkMode, oddkey, first_offset, inputBuffer, outputBuffer, pstSubSample);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_add_dec_subsample, ret);
        return ret;
    }

    if ((0 == pstSubSample->u32PayloadPatternEncryptLen)
        && (0 == pstSubSample->u32PayloadPatternClearLen))
    {
        /* non-pattern mode, copy clear data to output buffer */
        ret = cenc_copy_clear_subsample(enWorkMode, first_offset, inputBuffer, outputBuffer, pstSubSample);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_copy_clear_subsample, ret);
            return ret;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/* The format of CBC subsample is: H means head, P means Payload
 * H | P | H | P | H | P
 *
 * The format of Payload is: E means encrypt data, C clear data
 * E | C | E | C | E | C
 * the CBC mode does not encrypt Blocks smaller than 16 Bytes to
 * avoid adding padding that would cahnge the file size.
 */
static s32 cenc_decrypt_sample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                            u32 chn_num,
                            HI_BOOL oddkey,
                            SMMU_BUFFER_S *inputBuffer,
                            SMMU_BUFFER_S *outputBuffer,
                            u32 firstoffset,
                            u32 bytelength,
                            CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsampleEx,
                            u32 number)
{
    s32 ret = HI_FAILURE;
    CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubSample = HI_NULL;
    SMMU_BUFFER_S stSubinput;
    SMMU_BUFFER_S stSuboutput;
    u32 subsample_len = 0;
    u32 i;

    HI_LOG_FuncEnter();

    pstSubSample = pstSubsampleEx;
    stSubinput.u32StartSmmuAddr  = inputBuffer->u32StartSmmuAddr;
    stSubinput.pu8StartVirAddr   = inputBuffer->pu8StartVirAddr;
    stSubinput.u32Size           = inputBuffer->u32Size;
    stSuboutput.u32StartSmmuAddr = outputBuffer->u32StartSmmuAddr;
    stSuboutput.pu8StartVirAddr  = outputBuffer->pu8StartVirAddr;
    stSuboutput.u32Size          = outputBuffer->u32Size;

    ret = cenc_node_init(chn_num, oddkey, enWorkMode, firstoffset, pstSubSample);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_node_init, ret);
        return ret;
    }

    for (i=0; i<number; i++)
    {
        if (!(oddkey & CENC_ODDKEY_SUPPORT) && (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode))
        {
            /* In CBC mode, IV is used by all subsample */
            pstSubSample->u32IvChange = HI_TRUE;
        }
        HI_LOG_INFO("subsample %d, input 0x%x, output 0x%x, iv-change %d\n", i,
            stSubinput.u32StartSmmuAddr, stSuboutput.u32StartSmmuAddr, pstSubSample->u32IvChange);

        ret = cenc_add_subsample(enWorkMode, oddkey, &stSubinput,
            &stSuboutput, firstoffset, pstSubSample);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_add_subsample, ret);
            return ret;
        }

        /* move to next subsample */
        subsample_len = pstSubSample->u32ClearHeaderLen + pstSubSample->u32PayLoadLen;
        stSubinput.u32StartSmmuAddr  += subsample_len;
        stSubinput.pu8StartVirAddr   += subsample_len;
        stSuboutput.u32StartSmmuAddr += subsample_len;
        stSuboutput.pu8StartVirAddr  += subsample_len;
        pstSubSample++;
    }

    ret = cenc_node_finish();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_node_finish, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#ifdef CHIP_SYMC_VER_V100
static s32 cenc_copy_dec_subsample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                                u32 first_offset,
                                SMMU_BUFFER_S *inputBuffer,
                                u32 *input_offset,
                                SMMU_BUFFER_S *outputBuffer,
                                CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample)
{
    u32 index = 0;
    u32 subsample_len = 0;
    u32 offset = 0;
    u32 length = 0;
    u32 skip = 0;

    HI_LOG_FuncEnter();

    subsample_len = pstSubsample->u32ClearHeaderLen + pstSubsample->u32PayLoadLen;
    while (index < subsample_len)
    {
        /* get a pattern's encrypt data from subsample */
        skip = cenc_get_encrypt_len(enWorkMode, pstSubsample, first_offset, index, &offset, &length);
        HI_LOG_INFO("Pattern encrypt data, index 0x%x, enc offset 0x%x, len 0x%x, skip 0x%x\n",
            index, offset, length, skip);

        if (CRYP_CIPHER_WORK_MODE_CBC == enWorkMode)
        {
            /* hardhawre will not decrypt the bytes less than 16,
             * but will update the IV, this will cause the iv
             * be incorrect for next subsample, so we can't
             * decrypt the bytes less than 16
             */
            length &= ~0x0F;
        }

        if (0 != length)
        {
            if ((outputBuffer->u32Size + offset < offset)
                || (inputBuffer->u32Size + *input_offset < *input_offset)
                || (outputBuffer->u32Size + offset +length < length)
                || (inputBuffer->u32Size + *input_offset + length < length))
            {
                HI_LOG_ERROR("Invalid data lenth overflowed.\n");
                return HI_FAILURE;
            }
            crypto_memcpy(outputBuffer->pu8StartVirAddr + offset, length, inputBuffer->pu8StartVirAddr + *input_offset, length);
        }
        *input_offset += length;
        index  += skip;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_copy_decrypt_sample(CRYP_CIPHER_WORK_MODE_E enWorkMode,
                            u32 chn_num,
                            SMMU_BUFFER_S *inputBuffer,
                            SMMU_BUFFER_S *outputBuffer,
                            u32 firstoffset,
                            u32 bytelength,
                            CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsampleEx,
                            u32 number)
{
    s32 ret = HI_FAILURE;
    CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubSample = HI_NULL;
    SMMU_BUFFER_S stSuboutput;
    SMMU_BUFFER_S stSubinput;
    u32 subsample_len = 0;
    u32 offset = 0;
    u32 enclen = 0, declen = 0;
    u32 i;

    HI_LOG_FuncEnter();

    pstSubSample = pstSubsampleEx;

    /* Part of last block repuire to processed ?
     * For CBC mode, firstoffset always be zero
     */
    if (0 != firstoffset)
    {
        (void)cenc_get_first_pattern(pstSubSample, firstoffset, &enclen, &declen);
        if ( 0 != enclen)
        {
            /* set enclen to padding length */
            offset = firstoffset;
        }
    }

    cenc_info.enc_offset = 0;
    stSuboutput.u32StartSmmuAddr = outputBuffer->u32StartSmmuAddr;
    stSuboutput.pu8StartVirAddr  = outputBuffer->pu8StartVirAddr;
    stSuboutput.u32Size          = outputBuffer->u32Size;
    stSubinput.u32StartSmmuAddr  = inputBuffer->u32StartSmmuAddr;
    stSubinput.pu8StartVirAddr   = inputBuffer->pu8StartVirAddr;
    stSubinput.u32Size           = inputBuffer->u32Size;

    for (i=0; i<number; i++)
    {
        HI_LOG_INFO("subsample %d, input 0x%x, offset 0x%x, output 0x%x, iv-change %d\n", i,
            inputBuffer->u32StartSmmuAddr, offset, stSuboutput.u32StartSmmuAddr, pstSubSample->u32IvChange);

        ret = cenc_copy_dec_subsample(enWorkMode, firstoffset, &stSubinput, &offset, &stSuboutput, pstSubSample);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_add_subsample, ret);
            return ret;
        }

        /* move to next subsample */
        subsample_len = pstSubSample->u32ClearHeaderLen + pstSubSample->u32PayLoadLen;
        stSuboutput.u32StartSmmuAddr += subsample_len;
        stSuboutput.pu8StartVirAddr  += subsample_len;
        pstSubSample++;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

static s32 cenc_ctr_fast_decrypt_sample(u32 chn_num, HI_BOOL oddkey, SMMU_BUFFER_S *inputBuffer,
                                        SMMU_BUFFER_S *outputBuffer,
                                        CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample)
{
    s32 ret = HI_FAILURE;
    compat_addr buf_phy;
    u32 counters = 0;
    u32 length = 0;
    symc_node_usage usage = SYMC_NODE_USAGE_NORMAL;

    HI_LOG_FuncEnter();

    if (oddkey & 0x01)
    {
        usage |= SYMC_NODE_USAGE_ODD_KEY;
    }
    if (outputBuffer->u32Size + pstSubsample->u32ClearHeaderLen < pstSubsample->u32ClearHeaderLen)
    {
        HI_LOG_ERROR("Invalid clear header length.\n");
        return HI_FAILURE;
    }

    crypto_memcpy(outputBuffer->pu8StartVirAddr, pstSubsample->u32ClearHeaderLen,
        inputBuffer->pu8StartVirAddr, pstSubsample->u32ClearHeaderLen);

    if (0x00 == pstSubsample->u32PayLoadLen)
    {
        return HI_SUCCESS;
    }

    drv_symc_set_iv(chn_num, pstSubsample->u32IV, CENC_IV_SIZE, CIPHER_IV_CHANGE_ONE_PKG);
    counters = cenc_ctr128_iv_blocks((HI_U8*)pstSubsample->u32IV);
    length = (pstSubsample->u32PayLoadLen + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE;
    if (length <= counters)
    {
        length = pstSubsample->u32PayLoadLen;
    }
    else
    {
        /* IV overflow */
        length = counters * AES_BLOCK_SIZE;
    }

    ADDR_H32(buf_phy) = 0x00;
    ADDR_L32(buf_phy) = inputBuffer->u32StartSmmuAddr + pstSubsample->u32ClearHeaderLen;
    ret = drv_symc_add_inbuf(chn_num, buf_phy, ALIGN16(length), usage | SYMC_NODE_USAGE_LAST);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    ADDR_L32(buf_phy) = outputBuffer->u32StartSmmuAddr + pstSubsample->u32ClearHeaderLen;
    ret = drv_symc_add_outbuf(chn_num, buf_phy, ALIGN16(length), SYMC_NODE_USAGE_LAST);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
        return ret;
    }

    /* IV overflow */
    if (length < pstSubsample->u32PayLoadLen)
    {
        pstSubsample->u32IV[2] = 0x00;
        pstSubsample->u32IV[3] = 0x00;
        drv_symc_set_iv(chn_num, pstSubsample->u32IV, CENC_IV_SIZE, CIPHER_IV_CHANGE_ONE_PKG);

        ADDR_H32(buf_phy) = 0x00;
        ADDR_L32(buf_phy) = inputBuffer->u32StartSmmuAddr + pstSubsample->u32ClearHeaderLen + length;
        ret = drv_symc_add_inbuf(chn_num, buf_phy, ALIGN16(pstSubsample->u32PayLoadLen - length), usage | SYMC_NODE_USAGE_LAST);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
            return ret;
        }

        ADDR_L32(buf_phy) = outputBuffer->u32StartSmmuAddr + pstSubsample->u32ClearHeaderLen + length;
        ret = drv_symc_add_outbuf(chn_num, buf_phy, ALIGN16(pstSubsample->u32PayLoadLen - length), SYMC_NODE_USAGE_LAST);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
            return ret;
        }
    }

    /* start decrypt */
    ret = drv_symc_start(chn_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_start, ret);
        return ret;
    }

    /* waitting decrypt finished */
    ret = drv_symc_wait_done(chn_num, CRYPTO_TIME_OUT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_wait_done, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_cbc_fast_decrypt_sample(u32 chn_num, HI_BOOL oddkey, SMMU_BUFFER_S *inputBuffer,
                                        SMMU_BUFFER_S *outputBuffer,
                                        CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample, u32 number)
{
    s32 ret = HI_FAILURE;
    compat_addr buf_phy;
    u32 enclen = 0;
    u32 length = 0;
    symc_node_usage usage = SYMC_NODE_USAGE_NORMAL;
    u32 i;

    HI_LOG_FuncEnter();

    if (oddkey & 0x01)
    {
        usage |= SYMC_NODE_USAGE_ODD_KEY;
    }

    drv_symc_set_iv(chn_num, pstSubsample->u32IV, CENC_IV_SIZE, CIPHER_IV_CHANGE_ALL_PKG);

    for (i=0; i<number; i++)
    {
        if (0 != pstSubsample->u32ClearHeaderLen)
        {
            if ((length + pstSubsample->u32ClearHeaderLen < length)
                || (outputBuffer->u32Size < length + pstSubsample->u32ClearHeaderLen))
            {
                HI_LOG_ERROR("Invalid length or clear header length.\n");
                return HI_FAILURE;
            }

            crypto_memcpy(outputBuffer->pu8StartVirAddr + length, pstSubsample->u32ClearHeaderLen,
                inputBuffer->pu8StartVirAddr + length, pstSubsample->u32ClearHeaderLen);
            length += pstSubsample->u32ClearHeaderLen;
        }

        enclen = pstSubsample->u32PayLoadLen & (~0x0F);
        if (0x00 != enclen)
        {
            ADDR_H32(buf_phy) = 0x00;
            ADDR_L32(buf_phy) = inputBuffer->u32StartSmmuAddr + length;
            ret = drv_symc_add_inbuf(chn_num, buf_phy, enclen, usage | SYMC_NODE_USAGE_LAST);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
                return ret;
            }

            ADDR_L32(buf_phy) = outputBuffer->u32StartSmmuAddr + length;
            ret = drv_symc_add_outbuf(chn_num, buf_phy, enclen, SYMC_NODE_USAGE_LAST);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
                return ret;
            }
            length += enclen;
        }

        if (enclen < pstSubsample->u32PayLoadLen)
        {

            if ((length + pstSubsample->u32PayLoadLen - enclen < length)
                || (inputBuffer->u32Size < length + pstSubsample->u32PayLoadLen - enclen))
            {
                HI_LOG_ERROR("Invalid length or clear header length.\n");
                return HI_FAILURE;
            }

            crypto_memcpy(outputBuffer->pu8StartVirAddr + length, pstSubsample->u32PayLoadLen - enclen,
                inputBuffer->pu8StartVirAddr + length, pstSubsample->u32PayLoadLen - enclen);
            length += pstSubsample->u32PayLoadLen - enclen;
        }
        pstSubsample++;
    }

    /* start decrypt */
    ret = drv_symc_start(chn_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_start, ret);
        return ret;
    }

    /* waitting decrypt finished */
    ret = drv_symc_wait_done(chn_num, CRYPTO_TIME_OUT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_wait_done, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cenc_decrypt_process(HI_HANDLE hCipher,
                    u8 *key,
                    HI_BOOL oddkey,
                    u32 inputaddr,
                    u32 outputaddr,
                    u32 bytelength,
                    u32 firstoffset,
                    CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubsample,
                    u32 number)
{
    s32 ret = HI_FAILURE;
    u32 chn_num = 0;
    CRYP_CIPHER_CTRL_S ctrl;
    SMMU_BUFFER_S inputBuffer;
    SMMU_BUFFER_S outputBuffer;

    HI_LOG_FuncEnter();

    crypto_memset(&inputBuffer, sizeof(inputBuffer), 0, sizeof(inputBuffer));
    crypto_memset(&outputBuffer, sizeof(outputBuffer), 0, sizeof(outputBuffer));
    crypto_memset(&ctrl, sizeof(ctrl), 0, sizeof(ctrl));

    ret = kapi_symc_unlock_get_config(hCipher, &ctrl);
    if (ret != HI_SUCCESS)
    {
        HI_LOG_PrintFuncErr(kapi_symc_unlock_get_config, ret);
        return ret;
    }

    if (HI_FALSE == ctrl.bKeyByCA)
    {
        /* Host key needn't support odd key*/
        oddkey &= ~0x01;
    }

    chn_num = HI_HANDLE_GET_CHNID(hCipher);
    crypto_memcpy(ctrl.u32Key, CENC_KEY_SIZE, key, CENC_KEY_SIZE);
    cenc_config(chn_num, &ctrl);

    inputBuffer.u32StartSmmuAddr  = inputaddr;
    outputBuffer.u32StartSmmuAddr = outputaddr;
    inputBuffer.u32Size = bytelength;
    outputBuffer.u32Size = bytelength;
    ret = cenc_ddr_map(&inputBuffer, &outputBuffer);
    if ( HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_ddr_map, ret);
        return ret;
    }

    if (CRYP_CIPHER_WORK_MODE_CTR == ctrl.enWorkMode
        && 1 == number
        && 0 == firstoffset
        && 0 == pstSubsample->u32PayloadPatternEncryptLen
        && 0 == pstSubsample->u32PayloadPatternClearLen
        && HI_TRUE == pstSubsample->u32IvChange)
    {
        ret = cenc_ctr_fast_decrypt_sample(chn_num, oddkey, &inputBuffer, &outputBuffer, pstSubsample);
        if ( HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_decrypt_sample, ret);
            cenc_ddr_unmap(&inputBuffer, &outputBuffer);
            return ret;
        }
        cenc_ddr_unmap(&inputBuffer, &outputBuffer);

        HI_LOG_FuncExit();
        return HI_SUCCESS;
    }

    if (CRYP_CIPHER_WORK_MODE_CBC == ctrl.enWorkMode
        && !(oddkey & CENC_ODDKEY_SUPPORT)
        && 0 == firstoffset
        && 0 == pstSubsample->u32PayloadPatternEncryptLen
        && 0 == pstSubsample->u32PayloadPatternClearLen
        && HI_TRUE == pstSubsample->u32IvChange)
    {
        ret = cenc_cbc_fast_decrypt_sample(chn_num, oddkey, &inputBuffer, &outputBuffer, pstSubsample, number);
        if ( HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_cbc_fast_decrypt_sample, ret);
            cenc_ddr_unmap(&inputBuffer, &outputBuffer);
            return ret;
        }
        cenc_ddr_unmap(&inputBuffer, &outputBuffer);

        HI_LOG_FuncExit();
        return HI_SUCCESS;
    }

    if (CRYP_CIPHER_WORK_MODE_CBC == ctrl.enWorkMode)
    {
        if (0 != firstoffset)
        {
            HI_LOG_ERROR("Under CBC mode, The First offset shall be zero\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            cenc_ddr_unmap(&inputBuffer, &outputBuffer);
            return ret;
        }
    }
    else if (CRYP_CIPHER_WORK_MODE_CTR == ctrl.enWorkMode)
    {
#ifdef CHIP_SYMC_VER_V100
        ret = cenc_ddr_alloc(chn_num, bytelength);
#else
        ret = cenc_ddr_alloc(chn_num, AES_BLOCK_SIZE);
#endif
        if ( HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_ddr_alloc, ret);
            cenc_ddr_unmap(&inputBuffer, &outputBuffer);
            return ret;
        }
    }
    else
    {
        HI_LOG_ERROR("invalid mode 0x%x\n", ctrl.enWorkMode);
        cenc_ddr_unmap(&inputBuffer, &outputBuffer);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if ((0 != pstSubsample->u32PayloadPatternEncryptLen)
        || (0 != pstSubsample->u32PayloadPatternClearLen))
    {
        /* pattern mode, Copy input data to output buffer */
        crypto_memcpy(outputBuffer.pu8StartVirAddr, bytelength, inputBuffer.pu8StartVirAddr, bytelength);
    }

    ret = cenc_decrypt_sample(ctrl.enWorkMode, chn_num, oddkey, &inputBuffer, &outputBuffer,
           firstoffset, bytelength, pstSubsample, number);
    if ( HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_decrypt_sample, ret);
        cenc_ddr_unmap(&inputBuffer, &outputBuffer);
        return ret;
    }

#ifdef CHIP_SYMC_VER_V100
    if (CRYP_CIPHER_WORK_MODE_CTR == cenc_info.enWorkMode)
    {
        /* For version V100, hardware unsupport split joint data segment,
         * For CTR, must copy all data segment to a continuing DDR,
         * then copy all data segment from continuing DDR to output buffer
         */
        ret = cenc_copy_decrypt_sample(ctrl.enWorkMode, chn_num, &cenc_info.local, &outputBuffer,
               firstoffset, bytelength, pstSubsample, number);
        if ( HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(cenc_decrypt_sample, ret);
            cenc_ddr_unmap(&inputBuffer, &outputBuffer);
            return ret;
        }
    }
#endif
    cenc_ddr_unmap(&inputBuffer, &outputBuffer);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_length_check(u32 bytelength, CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubSample, u32 number)
{
    u32 total = 0;
    u32 pattern_len = 0;
    u32 i;

    HI_LOG_FuncEnter();

    for(i= 0; i<number; i++)
    {
        HI_LOG_INFO("subsample %d, ClearHead 0x%x, Payload 0x%x, PatternEncryp 0x%x, PatternClear 0x%x, PatternOffset 0x%x, iv-change %d\n", i,
            pstSubSample[i].u32ClearHeaderLen,
            pstSubSample[i].u32PayLoadLen,
            pstSubSample[i].u32PayloadPatternEncryptLen,
            pstSubSample[i].u32PayloadPatternClearLen,
            pstSubSample[i].u32PayloadPatternOffsetLen,
            pstSubSample->u32IvChange);

        if(  (CENC_SUBSAMPLE_MAX_DATALEN < pstSubSample[i].u32PayloadPatternEncryptLen)
          || (CENC_SUBSAMPLE_MAX_DATALEN < pstSubSample[i].u32PayloadPatternClearLen)
          || (CENC_SUBSAMPLE_MAX_DATALEN < pstSubSample[i].u32PayloadPatternOffsetLen)
          || (CENC_MAX_DATALEN < pstSubSample[i].u32ClearHeaderLen)
          || (CENC_MAX_DATALEN < pstSubSample[i].u32PayLoadLen))
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }

        /* PatternOffsetLen means how many blocks already be processed in last Pattern,
         * so the PatternOffsetLen must less than PatternEncryptLen + PatternClearLen.
         */
        pattern_len = pstSubSample[i].u32PayloadPatternEncryptLen + pstSubSample[i].u32PayloadPatternClearLen;
        if(pstSubSample[i].u32PayloadPatternOffsetLen > pattern_len)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        total += pstSubSample[i].u32ClearHeaderLen + pstSubSample[i].u32PayLoadLen;
        if (total > bytelength)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    if (total != bytelength)
    {
        HI_LOG_ERROR("invalid CencDecrypt total data bytelength 0x%x, input length 0x%x!\n", total, bytelength);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 cenc_copy_user_data(u32 oddkey_support, u8 *iv, void *subsample, u32 number,
                                  CRYP_CIPHER_SUBSAMPLE_EX_S *subsample_ex)
{
    s32 ret = HI_FAILURE;
    u32 total = 0;
    u32 u32SubSampleLen = 0;
    CRYP_CIPHER_SUBSAMPLE_S stSubSample;
    u32 i;

    HI_LOG_FuncEnter();

    /* copy subsample from user buffer */
    if (HI_FALSE == oddkey_support)
    {
        /* support CRYP_CIPHER_CENCDecrypt */
        for (i=0; i<number; i++)
        {
            ret = crypto_copy_from_user(&stSubSample, (HI_U8*)subsample + total, sizeof(CRYP_CIPHER_SUBSAMPLE_S));
            if ( HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(crypto_copy_from_user, ret);
                return ret;
            }
            subsample_ex[i].u32ClearHeaderLen = stSubSample.u32ClearHeaderLen;
            subsample_ex[i].u32PayLoadLen = stSubSample.u32PayLoadLen;
            subsample_ex[i].u32PayloadPatternEncryptLen = stSubSample.u32PayloadPatternEncryptLen;
            subsample_ex[i].u32PayloadPatternClearLen = stSubSample.u32PayloadPatternClearLen;
            subsample_ex[i].u32PayloadPatternOffsetLen = stSubSample.u32PayloadPatternOffsetLen;
            subsample_ex[i].u32IvChange = HI_FALSE;
            crypto_memcpy(subsample_ex[i].u32IV, CENC_IV_SIZE, iv, CENC_IV_SIZE);
            total += sizeof(CRYP_CIPHER_SUBSAMPLE_S);
        }
        subsample_ex->u32IvChange = HI_TRUE;
        HI_LOG_INFO("*** copy SubSample to SubSampleEx ***\n");
    }
    else
    {
        u32SubSampleLen = number * sizeof(CRYP_CIPHER_SUBSAMPLE_EX_S);
        ret = crypto_copy_from_user(subsample_ex, subsample, u32SubSampleLen);
        if ( HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(crypto_copy_from_user, ret);
            return ret;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cenc_decrypt(u32 id,
                u8 *key,
                u8 *iv,
                u32 oddkey,
                u32 inputphy,
                u32 outputphy,
                u32 bytelength,
                u32 firstoffset,
                void *subsample,
                u32 number)
{
    s32 ret = HI_FAILURE;
    CRYP_CIPHER_SUBSAMPLE_EX_S *subsample_ex = HI_NULL;
    u32 subsample_len = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == iv);
    HI_LOG_CHECK_PARAM(HI_NULL == subsample);
    HI_LOG_CHECK_PARAM(0 == number);
    HI_LOG_CHECK_PARAM(CENC_SUBSAMPLE_MAX_NUM < number);
    HI_LOG_CHECK_PARAM(CENC_MAX_DATALEN < bytelength);
    HI_LOG_CHECK_PARAM(CENC_FIRSTENCRYPTOFFSET_MAX_LEN < firstoffset);
    HI_LOG_CHECK_PARAM(inputphy + bytelength < inputphy);
    HI_LOG_CHECK_PARAM(outputphy + bytelength < outputphy);

    HI_LOG_INFO("inputphy 0x%x, outputphy 0x%x, firstoffset 0x%x, bytelength 0x%x, number %d, oddkey 0x%x\n",
        inputphy, outputphy, firstoffset, bytelength, number, oddkey);

    subsample_len = number * sizeof(CRYP_CIPHER_SUBSAMPLE_EX_S);
    subsample_ex = (CRYP_CIPHER_SUBSAMPLE_EX_S *)crypto_malloc(subsample_len);
    if (HI_NULL == subsample_ex)
    {
        HI_LOG_PrintFuncErr(crypto_malloc, HI_FAILURE);
        return HI_FAILURE;
    }
    crypto_memset(subsample_ex, subsample_len, 0, subsample_len);

    /* copy subsample from user buffer */
    ret = cenc_copy_user_data(oddkey & CENC_ODDKEY_SUPPORT, iv, subsample, number, subsample_ex);
    if ( HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_copy_user_data, ret);
        goto _exit;
    }

    /* check the length avoid overflow or inversion */
    ret = cenc_length_check(bytelength, subsample_ex, number);
    if ( HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_length_check, ret);
        goto _exit;
    }

    ret = cenc_decrypt_process(id, key, oddkey,
                    inputphy, outputphy, bytelength,
                    firstoffset, subsample_ex, number);
    if ( HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cenc_decrypt_process, ret);
        goto _exit;
    }

_exit:
    crypto_free(subsample_ex);
    subsample_ex = HI_NULL;

    return HI_SUCCESS;
}

#else
s32 cenc_decrypt(u32 id,
                u8 *key,
                u8 *iv,
                u32 oddkey,
                u32 inputphy,
                u32 outputphy,
                u32 bytelength,
                u32 firstoffset,
                void *subsample,
                u32 number)
{
    HI_LOG_ERROR("error, nonsupport CENC\n");
    return HI_FAILURE;
}
#endif //End of HI_SMMU_SUPPORT

