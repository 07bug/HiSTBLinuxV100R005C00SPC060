#include "lib.h"
#include "cipher_define.h"
#include "cipher_reg.h"
#include "hi_cipher.h"

static struct cipher_symc_context   s_symc[CIPHER_LOGIC_MAX_CHN];
static struct cipher_digest_context s_digest[CIPHER_LOGIC_MAX_CHN];
static struct HASH_INFO  s_HashInfo;
static unsigned char s_u32CipherNodesPhy[384];

/* brief Reset the Cipher and configure it */
void HI_CIPHER_Init(void)
{
    unsigned int i;
    U_SEC_CHN_CFG sec_chn_cfg;
    void *page_phy;
    uint32_t Value = 0;

    memset(s_symc, 0, CIPHER_LOGIC_MAX_CHN * 28);
    memset(s_digest, 0, CIPHER_LOGIC_MAX_CHN * 16);
    s_HashInfo.bIsInit = 0;
    s_HashInfo.enMode = 0;
    s_HashInfo.enAlg = 0;
    memset(s_u32CipherNodesPhy, 0, 384);

    /* sm4 init*/
    //Value = reg_get(CIPHER_SM4_REG_BASE_ADDR_PHY);
    //HAL_SET_BIT(Value, 8);
    //reg_set(CIPHER_SM4_REG_BASE_ADDR_PHY,Value);

    /* spacc init*/
    Value = reg_get(CIPHER_SPACC_CRG_ADDR_PHY);
    HAL_SET_BIT(Value, 0);
    reg_set(CIPHER_SPACC_CRG_ADDR_PHY, Value);
    udelay(10);
    HAL_SET_BIT(Value, 4);
    reg_set(CIPHER_SPACC_CRG_ADDR_PHY, Value);
    udelay(10);
    HAL_CLEAR_BIT(Value, 4);
    reg_set(CIPHER_SPACC_CRG_ADDR_PHY, Value);

    cipher_memset_s(&s_symc, 0, sizeof(s_symc));
    cipher_memset_s(&s_digest, 0, sizeof(s_digest));

    /* Secure channel enable */
    sec_chn_cfg.u32 = reg_get(SEC_CHN_CFG);
    sec_chn_cfg.bits.cipher_sec_chn_cfg |= CIPHER_CHN_MASK;
    sec_chn_cfg.bits.hash_sec_chn_cfg |= CIPHER_CHN_MASK;
    reg_set(SEC_CHN_CFG, sec_chn_cfg.u32);
    CIPHER_DBG("SEC_CHN_CFG[%p]: 0x%x\n", SEC_CHN_CFG, sec_chn_cfg.u32);

    page_phy = s_u32CipherNodesPhy;

    for(i=CIPHER_PKGxN_CHAN_MIN; i<=CIPHER_PKGxN_CHAN_MAX; i++)
    {
        U_CHANN_CIPHER_IN_NODE_CFG cipher_in_cfg;
        U_CHANN_CIPHER_OUT_NODE_CFG cipher_out_cfg;
        U_CHANN_HASH_IN_NODE_CFG hash_in_cfg;

        /*set total num and start addr for cipher in node*/
        cipher_in_cfg.u32  = reg_get(CHANn_CIPHER_IN_NODE_CFG(i));
        cipher_in_cfg.bits.cipher_in_node_total_num = CIPHER_MAX_DEPTH;
        reg_set(CHANn_CIPHER_IN_NODE_CFG(i), cipher_in_cfg.u32);
        reg_set(CHANn_CIPHER_IN_NODE_START_ADDR(i), (u32)page_phy);
        CIPHER_DBG("CHANn_CIPHER_IN_NODE_CFG[%p]: \t0x%x, PHY: %p\n", CHANn_CIPHER_IN_NODE_CFG(i), cipher_in_cfg.u32, page_phy);
        s_symc[i].entry_symc_in = (struct cipher_symc_in_entry_t*)page_phy;
        s_symc[i].symc_cur_in_nodes = cipher_in_cfg.bits.cipher_in_node_wptr;
        s_symc[i].entry_symc_in_depth = 0;
        page_phy += SAPCC_SYMC_IN_ENTRY_TOTAL_SIZE;

        /*set total num and start addr for cipher out node*/
        cipher_out_cfg.u32 = reg_get(CHANn_CIPHER_OUT_NODE_CFG(i));
        cipher_out_cfg.bits.cipher_out_node_total_num = CIPHER_MAX_DEPTH;
        reg_set(CHANn_CIPHER_OUT_NODE_CFG(i), cipher_out_cfg.u32);
        reg_set(CHANn_CIPHER_OUT_NODE_START_ADDR(i), (u32)page_phy);
        CIPHER_DBG("CHANn_CIPHER_OUT_NODE_CFG[%p]: \t0x%x, PHY: %p\n", CHANn_CIPHER_OUT_NODE_CFG(i), cipher_out_cfg.u32, page_phy);
        s_symc[i].entry_symc_out = (struct cipher_symc_out_entry_t*)page_phy;
        s_symc[i].symc_cur_out_nodes = cipher_out_cfg.bits.cipher_out_node_wptr;
        s_symc[i].entry_symc_out_depth = 0;
        page_phy += SAPCC_SYMC_OUT_ENTRY_TOTAL_SIZE;

        /*set total num and start addr for hash in node*/
        hash_in_cfg.u32 = reg_get(CHANn_HASH_IN_NODE_CFG(i));
        hash_in_cfg.bits.hash_in_node_total_num = CIPHER_MAX_DEPTH;
        reg_set(CHANn_HASH_IN_NODE_CFG(i), hash_in_cfg.u32);
        //reg_set(CHANn_HASH_IN_NODE_START_ADDR(i), (u32)ADDR_MCU_LPDS_HASH_NODE);
        reg_set(CHANn_HASH_IN_NODE_START_ADDR(i), (u32)page_phy);
        CIPHER_DBG("CHANn_HASH_IN_NODE_CFG[%p]: \t0x%x, PHY: %p\n", CHANn_HASH_IN_NODE_CFG(i), hash_in_cfg.u32, page_phy);
       // s_digest[i].entry_digest_in = (struct cipher_digest_in_entry_t*)ADDR_MCU_LPDS_HASH_NODE;
        s_digest[i].entry_digest_in = (struct cipher_digest_in_entry_t*)page_phy;
        s_digest[i].digest_cur_in_nodes = hash_in_cfg.bits.hash_in_node_wptr;
        s_digest[i].entry_digest_in_depth = 0;
        page_phy += SAPCC_DIGEST_IN_ENTRY_TOTAL_SIZE;
    }
}

void HI_CIPHER_DeInit(void)
{
    uint32_t Value = 0;

    /* hash reset and canceling for clearing hash result */
    HAL_SET_BIT(Value, 4);
    reg_set(CIPHER_SPACC_CRG_ADDR_PHY, Value);
    HAL_CLEAR_BIT(Value, 4);
    reg_set(CIPHER_SPACC_CRG_ADDR_PHY, Value);

}

/* Plain and encrypting DMA functions */
static uint32_t cipher_symc_start(const uint32_t chn_num)
{
    U_CHANN_CIPHER_IN_NODE_CFG in_node_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    uint32_t ptr;
    struct cipher_symc_context *info = &s_symc[chn_num];

    out_node_cfg.u32 = reg_get(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    if (out_node_cfg.bits.cipher_out_node_wptr != out_node_cfg.bits.cipher_out_node_rptr)
    {
        CIPHER_DBG("Error, chn %d is busy.\n", chn_num);
        return HI_CIPHER_ERR_BUSY;
    }
    ptr = out_node_cfg.bits.cipher_out_node_wptr + info->entry_symc_out_depth;
    out_node_cfg.bits.cipher_out_node_wptr = ptr % CIPHER_MAX_DEPTH;
    out_node_cfg.bits.cipher_out_node_mpackage_int_level = info->entry_symc_out_depth;
    reg_set(CHANn_CIPHER_OUT_NODE_CFG(chn_num), out_node_cfg.u32);
    CIPHER_DBG("CHANn_CIPHER_OUT_NODE_CFG: 0x%x\n", out_node_cfg.u32);

    in_node_cfg.u32 = reg_get(CHANn_CIPHER_IN_NODE_CFG(chn_num));
    ptr = in_node_cfg.bits.cipher_in_node_wptr + info->entry_symc_in_depth;
    in_node_cfg.bits.cipher_in_node_wptr = ptr % CIPHER_MAX_DEPTH;
    in_node_cfg.bits.cipher_in_node_mpackage_int_level = info->entry_symc_in_depth;

    reg_set(CHANn_CIPHER_IN_NODE_CFG(chn_num), in_node_cfg.u32);

    CIPHER_DBG("CHANn_CIPHER_IN_NODE_CFG: 0x%x\n", in_node_cfg.u32);

    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    return AUTH_SUCCESS;
}

static uint32_t cipher_symc_done_notify(const uint32_t chn_num)
{
    U_CIPHER_INT_RAW    int_raw;
    uint32_t            chn_mask = 1<<chn_num;

    /* XXX CRS CHECK IF THIS MASKING SCHEME IS CORRECT XXX */

    int_raw.u32 = reg_get(CIPHER_INT_RAW);
    int_raw.bits.cipher_chn_obuf_raw &= chn_mask;
    chn_mask = int_raw.bits.cipher_chn_obuf_raw;
    reg_set(CIPHER_INT_RAW, int_raw.u32);

    return (chn_mask)? AUTH_SUCCESS : 0;
}

uint32_t HI_CIPHER_decrypt(const uint32_t u32SrcPhyAddr,  unsigned int decrypt_type,
                               const uint32_t u32Length, const uint32_t checksum)
{
    uint32_t id_in = 0, id_out = 0, size = 0;
    void *addr = NULL;
    unsigned u32TimeOut = 0;
    volatile uint32_t u32Mask = AUTH_FAILURE;
    struct cipher_symc_context *info = &s_symc[DMA_DECRYPT_CHANNEL];
    U_CHANN_CIPHER_CTRL cipher_ctrl;
    uint32_t srcAddr = u32SrcPhyAddr;

    /* Cipher symc configuration */
    // XXX CRS : this could be improved by reducing to a single constant XXX
    cipher_ctrl.u32 = reg_get(CHANn_CIPHER_CTRL(DMA_DECRYPT_CHANNEL));
    cipher_ctrl.bits.sym_chn_sm1_round_num = 0;
    cipher_ctrl.bits.sym_chn_key_sel = 1;
    cipher_ctrl.bits.sym_chn_key_length = 0;
    cipher_ctrl.bits.sym_chn_dat_width = SYMC_DAT_WIDTH128;
    cipher_ctrl.bits.sym_chn_decrypt = 0x01;
    if(HI_SYMC_ALG_SM4 == decrypt_type)
    {
         cipher_ctrl.bits.sym_chn_alg_sel = HI_SYMC_ALG_SM4;
    }
    else if(HI_SYMC_ALG_AES == decrypt_type)
    {
        cipher_ctrl.bits.sym_chn_alg_sel = HI_SYMC_ALG_AES;
    }
    cipher_ctrl.bits.sym_chn_alg_mode = HI_SYMC_MODE_CBC;
    reg_set(CHANn_CIPHER_CTRL(DMA_DECRYPT_CHANNEL), cipher_ctrl.u32);

    info->entry_symc_in_depth = 0;
    info->entry_symc_out_depth = 0;

    /* Input structure */
    id_in = info->symc_cur_in_nodes++;
    addr = &info->entry_symc_in[id_in];
    size = sizeof(struct cipher_symc_in_entry_t);
    cipher_memset_s(addr, 0, size);
    info->entry_symc_in[id_in].cipher_cmd = 0x00;
    info->entry_symc_in[id_in].sym_start_addr = srcAddr;
    info->entry_symc_in[id_in].sym_alg_length = u32Length;
    info->entry_symc_in[id_in].sym_ctrl =  CIPHER_CTRL_SYMC_IN_LAST | CIPHER_CTRL_SYMC_IN_FIRST;
    info->entry_symc_in_depth++;
    info->symc_cur_in_nodes %= CIPHER_MAX_DEPTH;

    /* Output structure */
    id_out = info->symc_cur_out_nodes++;
    addr = &info->entry_symc_out[id_out];
    cipher_memset_s(addr, 0, size);
    info->entry_symc_out[id_out].sym_start_addr = srcAddr; /* In-place copy */
    info->entry_symc_out[id_out].sym_alg_length = u32Length;
    info->entry_symc_out[id_out].aes_ctrl = CIPHER_CTRL_SYMC_OUT_LAST;
    info->entry_symc_out_depth++;
    info->symc_cur_out_nodes %= CIPHER_MAX_DEPTH;

    /* Start */
    cipher_symc_start(DMA_DECRYPT_CHANNEL);

    /* Wait for completion */
    while(u32TimeOut++ < CIPHER_TIME_OUT_LONG)
    {
        u32Mask = cipher_symc_done_notify(DMA_DECRYPT_CHANNEL);
        if (u32Mask == AUTH_SUCCESS)
        {
            return AUTH_SUCCESS;
        }
    }

    CIPHER_ERR("cipher_symc_enc/dec time out\n");

    return HI_CIPHER_ERR_TIMEOUT;
}

/* hash functions */
static uint32_t hash_process(uint32_t u32DataAddr, uint32_t u32DataLen, uint32_t enCtrl)
{
    uint32_t u32TimeOut = 0;
    volatile uint32_t u32Mask = 0;
    struct cipher_digest_context *info = &s_digest[HASH_HARD_CHN];
    uint32_t id = 0, size = 0;
    void *addr = NULL;
    uint32_t ptr = 0;
    U_CHANN_HASH_IN_NODE_CFG in_node_cfg;
    U_HASH_INT_RAW    int_raw;

    /* Configure the node */
    id = info->digest_cur_in_nodes++;
    addr = &info->entry_digest_in[id];
    size = sizeof(struct cipher_digest_in_entry_t);
    cipher_memset_s(addr, 0, size);
    info->entry_digest_in[id].cipher_cmd = 0x00;
    info->entry_digest_in[id].hash_start_addr = u32DataAddr;
    info->entry_digest_in[id].hash_alg_length = u32DataLen;
    info->entry_digest_in[id].hash_ctrl = enCtrl;
    info->entry_digest_in_depth++;
    info->digest_cur_in_nodes %= CIPHER_MAX_DEPTH;

    in_node_cfg.u32 = reg_get(CHANn_HASH_IN_NODE_CFG(HASH_HARD_CHN));
    if (in_node_cfg.bits.hash_in_node_wptr != in_node_cfg.bits.hash_in_node_rptr)
    {
        CIPHER_DBG("Error, chn %d is busy.\n", HASH_HARD_CHN);
        return HI_CIPHER_ERR_BUSY;
    }

    ptr = in_node_cfg.bits.hash_in_node_wptr + info->entry_digest_in_depth;
    in_node_cfg.bits.hash_in_node_wptr = ptr % CIPHER_MAX_DEPTH;
    in_node_cfg.bits.hash_in_node_mpackage_int_level = 1;

    reg_set(CHANn_HASH_IN_NODE_CFG(HASH_HARD_CHN), in_node_cfg.u32);

    info->entry_digest_in_depth = 0;

    while(u32TimeOut++ < CIPHER_TIME_OUT)
    {
        int_raw.u32 = reg_get(HASH_INT_RAW);
        int_raw.bits.hash_chn_oram_raw &= (1<<HASH_HARD_CHN);
        u32Mask = int_raw.bits.hash_chn_oram_raw;
        reg_set(HASH_INT_RAW, int_raw.u32);

        if (u32Mask)
        {
            return AUTH_SUCCESS;
        }

        udelay(100000);
        //random_delay();
    }

    return AUTH_FAILURE;
}

uint32_t HI_HASH_Padding(uint8_t *pu8Msg, uint32_t u32CurLen, uint32_t u32TotalLen)
{
    uint32_t u32Tmp = 0;
    uint32_t u32PaddingLen = 0;

    u32Tmp = u32TotalLen % HASH_BLOCK_SIZE;
    u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
    u32PaddingLen += 8;

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    cipher_memset_s(&pu8Msg[u32CurLen], 0, u32PaddingLen - 8);
    pu8Msg[u32CurLen++] = 0x80;
    u32CurLen+=u32PaddingLen - 1 - 8;

    /* write 8 bytes fix data length */
    pu8Msg[u32CurLen++] = 0x00;
    pu8Msg[u32CurLen++] = 0x00;
    pu8Msg[u32CurLen++] = 0x00;
    pu8Msg[u32CurLen++] = (uint8_t)((u32TotalLen >> 29) & 0x07);
    pu8Msg[u32CurLen++] = (uint8_t)((u32TotalLen >> 21) & 0xff);
    pu8Msg[u32CurLen++] = (uint8_t)((u32TotalLen >> 13) & 0xff);
    pu8Msg[u32CurLen++] = (uint8_t)((u32TotalLen >> 5 ) & 0xff);
    pu8Msg[u32CurLen++] = (uint8_t)((u32TotalLen << 3 )  & 0xff);

    return u32PaddingLen;
}

uint32_t HI_HASH_Init(unsigned int hash_type)
{
    struct cipher_digest_context *info = &s_digest[HASH_HARD_CHN];
    uint32_t state[16] = {
                              CPU_TO_BE32(SHA256_H0),
                              CPU_TO_BE32(SHA256_H1),
                              CPU_TO_BE32(SHA256_H2),
                              CPU_TO_BE32(SHA256_H3),
                              CPU_TO_BE32(SHA256_H4),
                              CPU_TO_BE32(SHA256_H5),
                              CPU_TO_BE32(SHA256_H6),
                              CPU_TO_BE32(SHA256_H7)
                             };
    uint32_t sm3_state[16] = {
                              CPU_TO_BE32(SM3_H0),
                              CPU_TO_BE32(SM3_H1),
                              CPU_TO_BE32(SM3_H2),
                              CPU_TO_BE32(SM3_H3),
                              CPU_TO_BE32(SM3_H4),
                              CPU_TO_BE32(SM3_H5),
                              CPU_TO_BE32(SM3_H6),
                              CPU_TO_BE32(SM3_H7)
                             };

    uint32_t i;
    U_CHANN_HASH_CTRL hash_ctrl;

    s_HashInfo.bIsInit = 0;
    s_HashInfo.enMode = HI_MODE_HASH;

    if(HI_HASH_ALG_SM3 == hash_type)
    {
        s_HashInfo.enAlg = HI_HASH_ALG_SM3;
    }else if(HI_HASH_ALG_SHA256 == hash_type)
    {
         s_HashInfo.enAlg = HI_HASH_ALG_SHA256;
    }

    hash_ctrl.u32 = reg_get(CHANn_HASH_CTRL(HASH_HARD_CHN));
    hash_ctrl.bits.hash_chn_mode = HI_MODE_HASH;
    if(HI_HASH_ALG_SM3 == hash_type)
    {
         hash_ctrl.bits.hash_chn_agl_sel = DIGEST_ALG_SM3;
    }
    else
    {
         hash_ctrl.bits.hash_chn_agl_sel = DIGEST_ALG_SHA256;
    }
    reg_set(CHANn_HASH_CTRL(HASH_HARD_CHN), hash_ctrl.u32);

    info->entry_digest_in_depth = 0;
    info->digest_len = 32;

    if(HI_HASH_ALG_SM3 == hash_type)
    {
        for(i=0; i<16; i++)
        {
            reg_set(CHANn_HASH_STATE_VAL_ADDR(HASH_HARD_CHN), i);
            reg_set(CHANn_HASH_STATE_VAL(HASH_HARD_CHN), sm3_state[i]);
        }
    }
    else if(HI_HASH_ALG_SHA256 == hash_type)
    {

        for(i=0; i<16; i++)
        {
            reg_set(CHANn_HASH_STATE_VAL_ADDR(HASH_HARD_CHN), i);
            reg_set(CHANn_HASH_STATE_VAL(HASH_HARD_CHN), state[i]);
        }
    }
    return AUTH_SUCCESS;
}

uint32_t HI_HASH_Update(const uint32_t u32DataAddr, const uint32_t u32DataLen)
{
    volatile uint32_t ret = AUTH_FAILURE;
    uint32_t enCtrl = CIPHER_CTRL_NONE;
    uint32_t dataAddr = u32DataAddr;

    if(!s_HashInfo.bIsInit)
    {
        enCtrl |= CIPHER_CTRL_HASH_IN_FIRST;
        s_HashInfo.bIsInit = 1;
    }
    enCtrl |= CIPHER_CTRL_HASH_IN_LAST;

    ret = hash_process(dataAddr, u32DataLen, enCtrl);
    if(AUTH_SUCCESS != ret)
    {
        CIPHER_ERR("SHA2 Update failed, ret = 0x%x.", ret);
        return HI_CIPHER_ERR_BUSY;
    }

    return AUTH_SUCCESS;
}

uint32_t HI_HASH_Final(const uint32_t u32DataAddr, const uint32_t u32DataLen, uint8_t *pu8OutputHash)
{
    uint32_t i = 0, tmp = 0;
    volatile uint32_t ret = AUTH_FAILURE;
    struct cipher_digest_context *info = &s_digest[HASH_HARD_CHN];
    uint32_t enCtrl = CIPHER_CTRL_NONE;
    uint32_t dataAddr = u32DataAddr;

    enCtrl = CIPHER_CTRL_HASH_IN_LAST;

    ret = hash_process(dataAddr, u32DataLen, enCtrl);
    if(AUTH_SUCCESS != ret)
    {
        CIPHER_ERR("cipher add in buf failed, ret = 0x%x.", ret);
        return HI_CIPHER_ERR_BUSY;
    }

    for(i=0; i<info->digest_len/4; i++)
    {
        reg_set(CHANn_HASH_STATE_VAL_ADDR(HASH_HARD_CHN), i);
        tmp = reg_get(CHANn_HASH_STATE_VAL(HASH_HARD_CHN));
        cipher_memcpy_s(pu8OutputHash+i*4, &tmp, 4);
    }

    return AUTH_SUCCESS;
}
