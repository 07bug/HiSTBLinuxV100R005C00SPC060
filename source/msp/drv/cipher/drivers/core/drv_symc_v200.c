/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2_v200.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_symc_v200.h"
#include "drv_symc.h"

#ifdef CHIP_SYMC_VER_V200

#define KLAD_KEY_USE_ERR         0x01
#define ALG_LEN_ERR              0x02
#define SMMU_PAGE_UNVLID         0x04
#define OUT_SMMU_PAGE_NOT_VALID  0x08
#define KLAD_KEY_WRITE_ERR       0x10

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! \Length of pading buffer */
#define SYMC_PAD_BUFFER_LEN             (128)

/*! \Length of aes ccm/gcm key */
#define AES_CCM_GCM_KEY_LEN             (16)

/*! \Total Length of pading buffer */
#define SYMC_PAD_BUFFER_TOTAL_LEN       (SYMC_PAD_BUFFER_LEN * CIPHER_HARD_CHANNEL_CNT)

/*! spacc symc int entry struct which is defined by hardware, you can't change it */
typedef struct
{
    u32     spacc_cmd:2;    /*!<  reserve */
    u32     rev1:6;         /*!<  reserve */
    u32     sym_ctrl:7;     /*!<  symc control flag*/
    u32     rev2:1;         /*!<  reserve */
    u32     gcm_iv_len:4;   /*!<  gcm iv length */
    u32     rev3:12;        /*!<  reserve */
    u32     sym_start_high; /*!<  syma start high addr */
    u32     sym_start_addr; /*!<  syma start low addr */
    u32     sym_alg_length; /*!<  syma data length */
    u32     IV[4];          /*!<  symc IV */
}symc_entry_in;

/*! spacc symc out entry struct which is defined by hardware, you can't change it */
typedef struct
{
    u32    rev1:8;                /*!<  reserve */
    u32    aes_ctrl:4;            /*!<  aes contrl */
    u32    rev2:20;               /*!<  reserve */
    u32    sym_start_addr;        /*!<  syma start high addr */
    u32    sym_alg_length;        /*!<  syma data length */
    u32    hash_rslt_start_addr;  /*!<  syma data length */
    u32    tag[AEAD_TAG_SIZE_IN_WORD];  /*!<  CCM/GCM tag */
}symc_entry_out;

/*! Define the context of cipher */
typedef struct
{
    u32 open;                    /*!<  open or close */
    symc_entry_in *entry_in;     /*!<  in node list */
    symc_entry_out *entry_out;   /*!<  out node list */
    compat_addr    dma_entry;    /*!<  dma addr of node */
    compat_addr    dma_pad;      /*!<  dma addr of padding buffer, for CCM/GCM */
    u8*            via_pad;      /*!<  via addr of padding buffer, for CCM/GCM */
    u32            offset_pad;   /*!<  offset of padding buffer, for CCM/GCM */
    u32 iv[SYMC_IV_MAX_SIZE_IN_WORD];/*!<  iv data from user*/

    /* iv usage flag, should be CIPHER_IV_CHANGE_ONE_PKG
     * or CIPHER_IV_CHANGE_ALL_PKG.
     */
    u32 iv_flag;                     /*!<  iv flag */
    u32 iv_len;                      /*!<  iv length */
    symc_alg alg;                    /*!<  The alg of Symmetric cipher */
    symc_mode mode;                  /*!<  mode */
    u32 id_in;                       /*!<  current in nodes index */
    u32 id_out;                      /*!<  current out nodes index */
    u32 cnt_in;                      /*!<  total count in nodes to be computed */
    u32 cnt_out;                     /*!<  total count out nodes to be computed */
    u32 done;                        /*!<  calculation finish flag*/
    crypto_queue_head  queue;        /*!<  quene list */
    callback_symc_isr callback;      /*!<  isr callback functon */
    callback_symc_destory destory;   /*!<  destory callback functon */
    void *ctx;                       /*!<  params for isr callback functon */
}symc_hard_context;

/*! spacc symc_chn_who_used struct which is defined by hardware, you can't change it */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    non_sec_chn_who_used : 16   ; /* [15..0]  */
        unsigned int    sec_chn1_who_used     : 2   ; /* [17..16]  */
        unsigned int    reserved              : 22  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;
} symc_chn_who_used;

/*! Channel of cipher */
static symc_hard_context *hard_context = HI_NULL;

/*! dma memory of cipher node list*/
static crypto_mem   symc_dma;

/*! symc already initialize or not */
static u32 symc_initialize = HI_FALSE;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

#ifndef HI_ADVCA_FUNCTION_RELEASE
extern int dump_mem(void);
#endif

static s32 drv_symc_done_try(u32 chn_num)
{
    U_CIPHER_INT_RAW status;

    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    status.u32 = SYMC_READ(CIPHER_INT_RAW);
    status.bits.cipher_chn_obuf_raw &= 0x01 << chn_num; /* check interception */

    /*clear interception*/
    SYMC_WRITE(CIPHER_INT_RAW, status.u32);

    if (0 == status.bits.cipher_chn_obuf_raw)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

#ifdef CRYPTO_OS_INT_SUPPORT
static u32 drv_symc_done_notify(void)
{
    U_CIPHER_INT_STATUS status;
    U_CIPHER_INT_RAW    raw;

    status.u32 = SYMC_READ(CIPHER_INT_STATUS);
    raw.u32 = 0;

    /*just process the valid channel*/
    status.bits.cipher_chn_obuf_int &= CIPHER_HARD_CHANNEL_MASK;
    raw.bits.cipher_chn_obuf_raw = status.bits.cipher_chn_obuf_int;

    /*clear interception*/
    SYMC_WRITE(CIPHER_INT_RAW, raw.u32);

    return status.bits.cipher_chn_obuf_int; /* mask */
}

static u32 drv_hash_done_test(void)
{
    U_HASH_INT_STATUS int_st;
    u32 chn_mask = 0;

    int_st.u32 = SYMC_READ(HASH_INT_STATUS);

    /*just process the valid channel*/
    int_st.bits.hash_chn_oram_int &= HASH_HARD_CHANNEL_MASK;
    chn_mask = int_st.bits.hash_chn_oram_int;

    return chn_mask;
}

/*! symc interrupt process function */
static irqreturn_t drv_symc_interrupt_isr(s32 irq, void *devId)
{
    u32 mask, i;
    symc_hard_context *ctx = HI_NULL;
    irqreturn_t ret = IRQ_HANDLED;

    /* get channel context*/
    mask = drv_symc_done_notify();
    HI_LOG_DEBUG("symc irq: %d, mask 0x%x\n", irq, mask);

    for (i=0; i< CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if ((mask >> i) & 0x01)
        {
            ctx = &hard_context[i];
            if ((ctx->callback) && (HI_FALSE == ctx->callback(ctx->ctx)))
            {
                /* contiue to compute */
                HI_LOG_DEBUG("contiue to compute chn %d\n", i);
                ret = drv_symc_start(i);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_ERROR("drv symc start failed chn %d\n", i);
                    return IRQ_NONE;
                }
            }
            else
            {
                /* finish */
                ctx->done = HI_TRUE;
                HI_LOG_DEBUG("chn %d wake up\n", i);
                crypto_queue_wait_up(&ctx->queue);
            }
        }
    }

    /* symc and hash use the sample interrupt number
     * so if hash has occur interrupt, we should return IRQ_NONE
     * to tell system continue to process the hash interrupt.
     */
    if (0 != drv_hash_done_test())
    {
        ret = IRQ_NONE;
    }

    return ret;
}

/*! symc register interrupt process function */
static s32 drv_symc_register_interrupt(void)
{
    s32 ret = HI_FAILURE;
    u32 int_valid = 0, int_num = 0;
    u32 i;
    const char *name;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, &name);

    if (HI_FALSE == int_valid)
    {
        return HI_SUCCESS;
    }

    /* request irq */
    HI_LOG_DEBUG("symc request irq, num %d, name %s\n", int_num, name);
    ret = crypto_request_irq(int_num, drv_symc_interrupt_isr, name);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("Irq request failure, irq = %d", int_num);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_REGISTER_IRQ);
        return ret;
    }

    /* initialize queue list*/
    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        crypto_queue_init(&hard_context[i].queue);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*! symc unregister interrupt process function */
static void drv_symc_unregister_interrupt(void)
{
    u32 int_valid = 0, int_num = 0;
    const char *name;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, &name);

    if (HI_FALSE == int_valid)
    {
        return;
    }

    /* free irq */
    HI_LOG_DEBUG("symc free irq, num %d, name %s\n", int_num, name);
    crypto_free_irq(int_num, name);

    HI_LOG_FuncExit();

    return;
}

/*! set interrupt */
static void drv_symc_set_interrupt(void)
{
    u32 int_valid = 0, int_num = 0;
    U_CIPHER_INT_EN cipher_int_en;
    U_CIPHER_INT_RAW    raw;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, HI_NULL);

    if (int_valid)
    {
        /* Enable interrupt */
        cipher_int_en.u32 = SYMC_READ(CIPHER_INT_EN);

        if (crypto_is_sec_cpu())
        {
            cipher_int_en.bits.cipher_sec_int_en = 1;
        }
        else
        {
            cipher_int_en.bits.cipher_nsec_int_en = 1;
        }
        cipher_int_en.bits.cipher_chn_obuf_en |= CIPHER_HARD_CHANNEL_MASK;

        SYMC_WRITE(CIPHER_INT_EN, cipher_int_en.u32);
        HI_LOG_INFO("CIPHER_INT_EN: 0x%x\n", cipher_int_en.u32);
    }
    else
    {
        /* Disable interrupt */
        cipher_int_en.u32 = SYMC_READ(CIPHER_INT_EN);

        if (crypto_is_sec_cpu())
        {
            cipher_int_en.bits.cipher_sec_int_en = 0;
        }
        else
        {
            cipher_int_en.bits.cipher_nsec_int_en = 0;
        }
        SYMC_WRITE(CIPHER_INT_EN, cipher_int_en.u32);
        HI_LOG_INFO("CIPHER_INT_EN: 0x%x\n", cipher_int_en.u32);
    }

    /* clear interception
     * the history of interception may trigge the system to
     * call the irq function before initialization
     * when register interrupt, this will cause a system abort.
     */
    raw.u32 = SYMC_READ(CIPHER_INT_RAW);
    raw.bits.cipher_chn_obuf_raw &= CIPHER_HARD_CHANNEL_MASK; /* clear valid channel */
    SYMC_WRITE(CIPHER_INT_RAW, raw.u32);

    HI_LOG_FuncExit();

    return;
}

#endif

/*! set symc entry */
static s32 drv_symc_recover_entry(u32 chn)
{
    U_CHANN_CIPHER_IN_NODE_CFG cipher_in_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG cipher_out_cfg;
    symc_hard_context *ctx = &hard_context[chn];
    compat_addr out_addr;
    u32 entry = 0;

    HI_LOG_FuncEnter();

    /* set total num and start addr for cipher in node
     * On ree, the chn may be seized by tee,
     * so we must check it, that is check we can write the reg of chn or not.
     */
    SYMC_WRITE(CHANn_CIPHER_IN_NODE_START_ADDR(chn), ADDR_L32(ctx->dma_entry));
    SYMC_WRITE(CHANN_CIPHER_IN_NODE_START_HIGH(chn), ADDR_H32(ctx->dma_entry));
    entry =  SYMC_READ(CHANn_CIPHER_IN_NODE_START_ADDR(chn));
    if (entry != ADDR_L32(ctx->dma_entry))
    {
        HI_LOG_INFO("the ree chn be seized by tee\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_UNAVAILABLE);
        return HI_ERR_CIPHER_UNAVAILABLE;
    }
    cipher_in_cfg.u32  = SYMC_READ(CHANn_CIPHER_IN_NODE_CFG(chn));
    ctx->id_in = cipher_in_cfg.bits.cipher_in_node_wptr;
    HI_LOG_INFO("symc chn %d recover, id in  0x%x, IN_NODE_START_ADDR  0x%x, VIA %p\n",
        chn, ctx->id_in, ADDR_L32(ctx->dma_entry), ctx->entry_in);

    /*set total num and start addr for cipher out node*/
    cipher_out_cfg.u32 = SYMC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn));
    ADDR_U64(out_addr) = ADDR_U64(ctx->dma_entry) + SYMC_NODE_SIZE;
    SYMC_WRITE(CHANn_CIPHER_OUT_NODE_START_ADDR(chn), ADDR_L32(out_addr));
    SYMC_WRITE(CHANN_CIPHER_OUT_NODE_START_HIGH(chn), ADDR_H32(out_addr));
    ctx->id_out = cipher_out_cfg.bits.cipher_out_node_wptr;
    HI_LOG_INFO("symc chn %d recover, id out 0x%x, OUT_NODE_START_ADDR 0x%x, VIA %p\n",
        chn, ctx->id_out, ADDR_L32(ctx->dma_entry) + SYMC_NODE_SIZE,
        ctx->entry_out);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*! set symc entry */
static void drv_symc_set_entry(u32 chn, compat_addr dma_addr, void *cpu_addr)
{
    U_CHANN_CIPHER_IN_NODE_CFG cipher_in_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG cipher_out_cfg;
    symc_hard_context *ctx = &hard_context[chn];

    HI_LOG_FuncEnter();

    /*set total num and start addr for cipher in node*/
    cipher_in_cfg.u32  = SYMC_READ(CHANn_CIPHER_IN_NODE_CFG(chn));
    cipher_in_cfg.bits.cipher_in_node_total_num = SYMC_MAX_LIST_NUM;
    SYMC_WRITE(CHANn_CIPHER_IN_NODE_CFG(chn), cipher_in_cfg.u32);
    HI_LOG_INFO("CHANn_CIPHER_IN_NODE_CFG[0x%x]: \t0x%x, PHY: 0x%x, VIA %p\n",
        CHANn_CIPHER_IN_NODE_CFG(chn), cipher_in_cfg.u32, ADDR_L32(dma_addr), cpu_addr);
    ctx->entry_in = (symc_entry_in *)cpu_addr;
    ctx->cnt_in = 0;
    ADDR_U64(dma_addr) += SYMC_NODE_SIZE;
    cpu_addr = (u8*)cpu_addr + SYMC_NODE_SIZE;

    /*set total num and start addr for cipher out node*/
    cipher_out_cfg.u32 = SYMC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn));
    cipher_out_cfg.bits.cipher_out_node_total_num = SYMC_MAX_LIST_NUM;
    SYMC_WRITE(CHANn_CIPHER_OUT_NODE_CFG(chn), cipher_out_cfg.u32);
    HI_LOG_INFO("CHANn_CIPHER_OUT_NODE_CFG[0x%x]: \t0x%x, PHY: 0x%x, VIA %p\n",
        CHANn_CIPHER_OUT_NODE_CFG(chn), cipher_out_cfg.u32, ADDR_L32(dma_addr), cpu_addr);
    ctx->entry_out = (symc_entry_out*)cpu_addr;
    ctx->cnt_out = 0;
    ADDR_U64(dma_addr) += SYMC_NODE_SIZE;

    HI_LOG_FuncExit();
}

/*! set symc pad buffer */
static void drv_symc_set_pad_buffer(u32 chn, compat_addr dma_addr, void *cpu_addr)
{
    symc_hard_context *ctx = &hard_context[chn];

    ctx->dma_pad = dma_addr;
    ctx->via_pad = cpu_addr;
    ctx->offset_pad = 0x00;
}

/*! set smmu */
static void drv_symc_smmu_bypass(void)
{
#ifdef CRYPTO_SMMU_SUPPORT
        U_CIPHER_IN_SMMU_EN cipher_in_smmu_en;
        U_OUT_SMMU_EN out_smmu_en;

        HI_LOG_FuncEnter();

        cipher_in_smmu_en.u32 = SYMC_READ(CIPHER_IN_SMMU_EN);
        out_smmu_en.u32 = SYMC_READ(OUT_SMMU_EN);

        cipher_in_smmu_en.bits.cipher_in_chan_rd_dat_smmu_en  |= CIPHER_HARD_CHANNEL_MASK >> 1;
        cipher_in_smmu_en.bits.cipher_in_chan_rd_node_smmu_en &= ~(CIPHER_HARD_CHANNEL_MASK >> 1);

        out_smmu_en.bits.out_chan_wr_dat_smmu_en  |= CIPHER_HARD_CHANNEL_MASK >> 1;
        out_smmu_en.bits.out_chan_rd_node_smmu_en &= ~(CIPHER_HARD_CHANNEL_MASK >> 1);

        SYMC_WRITE(CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
        SYMC_WRITE(OUT_SMMU_EN, out_smmu_en.u32);

        HI_LOG_INFO("CIPHER_IN_SMMU_EN[0x%x]: 0x%x\n", CIPHER_IN_SMMU_EN, cipher_in_smmu_en.u32);
        HI_LOG_INFO("OUT_SMMU_EN[0x%x]      : 0x%x\n", OUT_SMMU_EN, out_smmu_en.u32);

        HI_LOG_FuncExit();
#endif
}

/*! smmu set base address */
static void drv_symc_smmu_base_addr(void)
{
#ifdef CRYPTO_SMMU_SUPPORT
    u64 err_raddr = 0;
    u64 err_waddr = 0;
    u64 table_addr = 0;

    HI_LOG_FuncEnter();

    /* get table base addr from system api */
    smmu_get_table_addr(&err_raddr, &err_waddr, &table_addr);

    if (crypto_is_sec_cpu())
    {
        SYMC_WRITE(SEC_SMMU_START_ADDR, (u32)table_addr);
        HI_LOG_INFO("SEC_SMMU_START_ADDR[0x%x]  : 0x%x\n", SEC_SMMU_START_ADDR, (u32)table_addr);
    }
    else
    {
        SYMC_WRITE(NORM_SMMU_START_ADDR, (u32)table_addr);
        HI_LOG_INFO("NORM_SMMU_START_ADDR[0x%x]  : 0x%x\n", NORM_SMMU_START_ADDR, (u32)table_addr);
    }
#endif

    HI_LOG_FuncExit();
    return;
}

/*! set secure channel,
 *  non-secure CPU can't change the value of SEC_CHN_CFG,
 *  so non-secure CPU call this function will do nothing.
 */
static void drv_symc_enable_secure(u32 chn, u32 enable)
{
    U_SEC_CHN_CFG sec_chn_cfg;

    HI_LOG_FuncEnter();

    /*The SEC_CHN_CFG only can be set by secure CPU*/
    sec_chn_cfg.u32 = SYMC_READ(SEC_CHN_CFG);
    if (HI_TRUE == enable)
    {
        sec_chn_cfg.bits.cipher_sec_chn_cfg |= 0x01 << chn;
    }
    else
    {
        sec_chn_cfg.bits.cipher_sec_chn_cfg &= ~(0x01 << chn);
    }
    SYMC_WRITE(SEC_CHN_CFG, sec_chn_cfg.u32);
    HI_LOG_INFO("SEC_CHN_CFG[0x%x]: 0x%x\n", SEC_CHN_CFG, sec_chn_cfg.u32);

    HI_LOG_FuncExit();

    return;
}

static void drv_symc_print_last_node(u32 chn_num)
{
    symc_entry_in *in = HI_NULL;
    symc_entry_out *out = HI_NULL;
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = &hard_context[chn_num];

    /* get last in node info*/
    if ( 0x00 == ctx->id_in)
    {
        in = &ctx->entry_in[SYMC_NODE_LIST_SIZE];
    }
    else
    {
        in = &ctx->entry_in[ctx->id_in - 1];
    }

    /* get last out node info*/
    if ( 0x00 == ctx->id_out)
    {
        out = &ctx->entry_out[SYMC_NODE_LIST_SIZE];
    }
    else
    {
        out = &ctx->entry_out[ctx->id_out - 1];
    }

    HI_LOG_ERROR("chn %d, src addr 0x%x, size 0x%x, dest addr 0x%x, size 0x%x\n",
        chn_num, in->sym_start_addr, in->sym_alg_length,
        out->sym_start_addr, out->sym_alg_length);
    CRYPTO_UNUSED(in);
    CRYPTO_UNUSED(out);

    HI_LOG_FuncExit();
    return;
}

static void drv_symc_print_status(u32 chn_num)
{
    U_CIPHER_INT_RAW    raw;
    U_CIPHER_INT_STATUS status;
    U_CIPHER_INT_EN     enable;
    U_SEC_CHN_CFG       cfg;

    HI_LOG_FuncEnter();

    raw.u32 = SYMC_READ(CIPHER_INT_RAW);
    status.u32 = SYMC_READ(CIPHER_INT_STATUS);
    enable.u32 = SYMC_READ(CIPHER_INT_EN);
    cfg.u32 = SYMC_READ(SEC_CHN_CFG);

    HI_LOG_ERROR("\nsec_chn_cfg 0x%x, chn %d, nsec_int_en 0x%x, sec_int_en 0x%x, chn_obuf_en 0x%x, status 0x%x, raw 0x%x\n",
        (cfg.bits.cipher_sec_chn_cfg >> chn_num) & 0x01,
        chn_num, enable.bits.cipher_nsec_int_en, enable.bits.cipher_sec_int_en,
        (enable.bits.cipher_chn_obuf_en >> chn_num) & 0x01,
        (status.bits.cipher_chn_obuf_int >> chn_num) & 0x01,
        (raw.bits.cipher_chn_obuf_raw >> chn_num) & 0x01);

    HI_LOG_ERROR("\nThe cause of time out may be:\n"
                 "\t1. SMMU address invalid\n"
                 "\t2. interrupt number or name incorrect\n"
                 "\t3. CPU type mismatching, request %s CPU\n",
                 crypto_is_sec_cpu() ? "secure" : "non-secure");

    HI_LOG_FuncExit();

    return;
}

static s32 drv_symc_get_err_code(u32 chn_num)
{
    u32 code = 0;

    HI_LOG_FuncEnter();

   /* check error code
    * bit0: klad_key_use_err
    * bit1: alg_len_err
    * bit2: smmu_page_unvlid
    * bit3: out_smmu_page_not_valid
    * bit4: klad_key_write_err
    */

    /*read error code*/
    code = SYMC_READ(CALC_ERR);

    if (code & KLAD_KEY_USE_ERR)
    {
        HI_LOG_ERROR("symc error: klad_key_use_err, chn %d !!!\n", chn_num);
    }
    if (code & ALG_LEN_ERR)
    {
        HI_LOG_ERROR("symc error: alg_len_err, chn %d !!!\n", chn_num);
    }
    if (code & SMMU_PAGE_UNVLID)
    {
        HI_LOG_ERROR("symc error: smmu_page_unvlid, chn %d !!!\n", chn_num);
    }
    if (code & OUT_SMMU_PAGE_NOT_VALID)
    {
        HI_LOG_ERROR("symc error: out_smmu_page_not_valid, chn %d !!!\n", chn_num);
    }
    if (code & KLAD_KEY_WRITE_ERR)
    {
        HI_LOG_ERROR("symc error: klad_key_write_err, chn %d !!!\n", chn_num);
    }

    /*print the inout buffer address*/
    drv_symc_print_last_node(chn_num);
    drv_symc_print_status(chn_num);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static void drv_symc_entry_init(crypto_mem  mem)
{
    u32 i = 0;
    void *cpu_addr = HI_NULL;
    compat_addr dma_pad;
    u8*    via_pad = HI_NULL;

    HI_LOG_FuncEnter();

    /* set in node and out node dma buffer */
    HI_LOG_INFO("symc entry list configure\n");
    cpu_addr = mem.dma_virt;

    /* skip the in node and out node dma buffer */
    ADDR_U64(dma_pad) = ADDR_U64(mem.dma_addr) + SYMC_NODE_LIST_SIZE;
    via_pad = (u8*)mem.dma_virt + SYMC_NODE_LIST_SIZE;

    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if ((CIPHER_HARD_CHANNEL_MASK >> i) & 0x01) /*valid channel*/
        {
            /* in node and out node */
            drv_symc_set_entry(i, mem.mmz_addr, cpu_addr);
            ADDR_U64(hard_context[i].dma_entry) = ADDR_U64(mem.mmz_addr);
            ADDR_U64(mem.mmz_addr) += SYMC_NODE_SIZE * 2; /* move to next channel */
            cpu_addr = (u8*)cpu_addr + SYMC_NODE_SIZE * 2; /* move to next channel */

            /* padding */
            drv_symc_set_pad_buffer(i, dma_pad, via_pad);
            ADDR_U64(dma_pad) += SYMC_PAD_BUFFER_LEN;
            via_pad += SYMC_PAD_BUFFER_LEN;
        }
    }

    HI_LOG_FuncExit();
    return;
}

static s32 drv_symc_mem_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    /** dma buffer struct
      * ((in_node || out_node) * chn_num) || (pad_buffer * chn_num)
      */
    HI_LOG_INFO("alloc memory for nodes list\n");
    ret = crypto_mem_create(&symc_dma, SEC_MMZ, "symc_node_list",
        SYMC_NODE_LIST_SIZE + SYMC_PAD_BUFFER_TOTAL_LEN);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, malloc ddr for symc nodes list failed\n");
        HI_LOG_PrintFuncErr(crypto_mem_create, ret);
        return ret;
    }

    drv_symc_entry_init(symc_dma);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 drv_symc_mem_deinit(void)
{
    s32 ret = HI_FAILURE;

    ret = crypto_mem_destory(&symc_dma);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(crypto_mem_destory, ret);
        return ret;
    }

    return HI_SUCCESS;
}

static s32 drv_symc_chn_resume(u32 chn_num)
{
    s32 ret = HI_FAILURE;
    u32 base = 0;

    HI_LOG_FuncEnter();

    if (crypto_is_sec_cpu())
    {
        base = SYMC_READ(SEC_SMMU_START_ADDR);
    }
    else
    {
        base = SYMC_READ(NORM_SMMU_START_ADDR);
    }

    if (0 == base)
    {
        /* smmu base address is zero means hardware be unexpected reset */
        HI_LOG_WARN("cipher module is not ready, try to resume it now...\n");
        ret = drv_symc_resume();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_resume, ret);
            return ret;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_alloc_chn(u32 *chn_num, CRYP_CIPHER_TYPE_E type)
{
    s32 ret = HI_ERR_CIPHER_BUSY;
    symc_chn_who_used tee, ree;
    u32 i = 0;
    u32 ree_use = 0, tee_use = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);

    CRYPTO_UNUSED(type);

    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        /* check the valid channel */
        if((CIPHER_HARD_CHANNEL_MASK & (0x1 << i)) && HI_FALSE == hard_context[i].open)
        {
            /*get every chanel status occupied with REE/TEE */
            tee.u32 = SYMC_READ(CHN_WHO_USED_TEE);
            ree.u32 = SYMC_READ(CHN_WHO_USED_REE);
            tee_use  = tee.bits.non_sec_chn_who_used & SYMC_CHN_MASK(i);
            ree_use  = ree.bits.non_sec_chn_who_used & SYMC_CHN_MASK(i);

            /* 0x00 is not used */
            if (0x00 == tee_use && 0x00 == ree_use)
            {
                ree.bits.non_sec_chn_who_used |= SYMC_CHN_MASK(i);
                SYMC_WRITE(CHN_WHO_USED_REE, ree.u32);

                /* check if the channal aleardy be useded by other cpu
                 * if other cpu break-in when write the CIPHER_NON_SEC_CHN_WHO_USED
                 * the value of CIPHER_NON_SEC_CHN_WHO_USED will be channged
                 */
                tee.u32 = SYMC_READ(CHN_WHO_USED_TEE);
                tee_use  = tee.bits.non_sec_chn_who_used & SYMC_CHN_MASK(i);
                if (tee_use)
                {
                    /* chn aleardy be used by tee */
                    ree.bits.non_sec_chn_who_used &= ~ SYMC_CHN_MASK(i);
                    SYMC_WRITE(CHN_WHO_USED_REE, ree.u32);
                    continue;
                }

                drv_symc_enable_secure(i, HI_TRUE);
                ret = drv_symc_recover_entry(i);
                if (HI_SUCCESS != ret)
                {
                    /* chn aleardy be used by tee */
                    ree.bits.non_sec_chn_who_used &= ~ SYMC_CHN_MASK(i);
                    SYMC_WRITE(CHN_WHO_USED_REE, ree.u32);
                    continue;
                }

                /* alloc channel */
                hard_context[i].open = HI_TRUE;
                *chn_num = i;
                HI_LOG_INFO("+++ alloc symc chn %d +++\n", i);
                break;
            }
        }
    }

    if (CRYPTO_HARD_CHANNEL_MAX <= i)
    {
        HI_LOG_ERROR("symc alloc channel failed\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_BUSY);
        return HI_ERR_CIPHER_BUSY;
    }

    /* hardware may be unexpected reset by other module or platform,
     * such as unexpected reset by fastboot after load tee image,
     * in this case, the hardware configuration will be reset,
     * here try to re-config the hardware.
     */
    ret = drv_symc_chn_resume(*chn_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_chn_resume, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_symc_free_chn(u32 chn_num)
{
    symc_chn_who_used used;

    HI_LOG_FuncEnter();

    if (HI_FALSE == hard_context[chn_num].open)
    {
        HI_LOG_FuncExit();
        return;
    }

    /* clean tee and ree mask */
#ifdef HI_PLATFORM_TYPE_TEE
    used.u32 = SYMC_READ(CHN_WHO_USED_TEE);
    used.bits.non_sec_chn_who_used &= ~ SYMC_CHN_MASK(chn_num);
    SYMC_WRITE(CHN_WHO_USED_TEE, used.u32);
#else
    used.u32 = SYMC_READ(CHN_WHO_USED_REE);
    used.bits.non_sec_chn_who_used &= ~ SYMC_CHN_MASK(chn_num);
    SYMC_WRITE(CHN_WHO_USED_REE, used.u32);
#endif

    drv_symc_enable_secure(chn_num, HI_FALSE);

    if (HI_NULL != hard_context[chn_num].destory)
    {
        hard_context[chn_num].destory();
        hard_context[chn_num].destory = HI_NULL;
    }

    /*free channel*/
    hard_context[chn_num].open = HI_FALSE;

    HI_LOG_INFO("--- free symc chn %d ---\n", chn_num);

    HI_LOG_FuncExit();
    return;
}

#ifdef CRYPTO_SWITCH_CPU
u32 drv_symc_is_secure(void)
{
    U_SEC_CHN_CFG sec;
    U_SEC_CHN_CFG tmp;
    u32 secure = HI_FALSE;

    HI_LOG_FuncEnter();

    HI_LOG_INFO("Change the secure type of the chn0 to get cpu type\n");
    module_enable(CRYPTO_MODULE_ID_SYMC);

    sec.u32 = SYMC_READ(SEC_CHN_CFG);

    /* change the secure type of chn0 */
    sec.bits.cipher_sec_chn_cfg ^= 0x01;
    SYMC_WRITE(SEC_CHN_CFG, sec.u32);

    /* read the secure type of chn0 */
    tmp.u32 = SYMC_READ(SEC_CHN_CFG);

    if (tmp.bits.cipher_sec_chn_cfg == sec.bits.cipher_sec_chn_cfg)
    {
        /* The REG_SEC_CHN_CFG only can be set by secure CPU
         * can write the cfg, must be secure CPU
         */
        secure =  HI_TRUE;

        /* recovery the secure type of chn0 */
        sec.bits.cipher_sec_chn_cfg ^= 0x01;
        SYMC_WRITE(SEC_CHN_CFG, sec.u32);
    }

    HI_LOG_INFO("secure type: 0x%x\n", secure);

    HI_LOG_FuncExit();
    return secure;
}
#endif

s32 drv_symc_init(void)
{
    s32 ret = HI_FAILURE;
    u32 i = 0;

    HI_LOG_FuncEnter();

    if (HI_TRUE == symc_initialize)
    {
        HI_LOG_FuncExit();
        return HI_SUCCESS;
    }

    hard_context = crypto_calloc(sizeof(symc_hard_context), CRYPTO_HARD_CHANNEL_MAX);
    if (HI_NULL == hard_context)
    {
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }
    crypto_memset(&symc_dma, sizeof(symc_dma), 0, sizeof(symc_dma));

    HI_LOG_INFO("enable symc\n");
    module_enable(CRYPTO_MODULE_ID_SYMC);

    module_disable(CRYPTO_MODULE_ID_SM4);

    ret = drv_symc_mem_init();
    if (HI_SUCCESS != ret)
    {
        goto __error;
    }
    HI_LOG_INFO("SYMC DMA buffer, MMU 0x%x, MMZ 0x%x, VIA %p, size 0x%x\n",
        ADDR_L32(symc_dma.dma_addr), ADDR_L32(symc_dma.mmz_addr),
        symc_dma.dma_virt, symc_dma.dma_size);

    HI_LOG_INFO("symc SMMU configure\n");
    drv_symc_smmu_bypass();
    drv_symc_smmu_base_addr();

#ifdef CRYPTO_OS_INT_SUPPORT
    HI_LOG_INFO("symc interrupt configure\n");
    drv_symc_set_interrupt();

    HI_LOG_INFO("symc register interrupt function\n");
    ret = drv_symc_register_interrupt();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, register interrupt failed\n");
        HI_LOG_PrintFuncErr(drv_symc_register_interrupt, ret);
        drv_symc_mem_deinit();
        goto __error;
    }
#endif

   /*  set all channel as non-secure channel,
    *  may be set it to secure channel when alloc handle.
    */
    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        /* check the valid channel */
        if (CIPHER_HARD_CHANNEL_MASK & (0x1 << i))
        {
            drv_symc_enable_secure(i, HI_FALSE);
        }
    }

    symc_initialize = HI_TRUE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;

__error:
    module_disable(CRYPTO_MODULE_ID_SYMC);
    crypto_free(hard_context);
    hard_context = HI_NULL;

    HI_LOG_FuncExit();
    return ret;
}

s32 drv_symc_resume(void)
{
    u32 i;
    symc_chn_who_used used;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_INFO("enable symc\n");
    module_enable(CRYPTO_MODULE_ID_SYMC);
    module_disable(CRYPTO_MODULE_ID_SM4);

    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if (hard_context[i].open)
        {
#ifdef HI_PLATFORM_TYPE_TEE
            used.u32 = SYMC_READ(CHN_WHO_USED_TEE);
            used.bits.non_sec_chn_who_used |= SYMC_CHN_MASK(i);
            SYMC_WRITE(CHN_WHO_USED_TEE, used.u32);
#else
            used.u32 = SYMC_READ(CHN_WHO_USED_REE);
            used.bits.non_sec_chn_who_used |= SYMC_CHN_MASK(i);
            SYMC_WRITE(CHN_WHO_USED_REE, used.u32);
#endif
            drv_symc_enable_secure(i, HI_TRUE);
            ret = drv_symc_recover_entry(i);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(drv_symc_recover_entry, ret);
                return ret;
            }
        }
    }

#ifdef CRYPTO_OS_INT_SUPPORT
    drv_symc_set_interrupt();
#endif

    drv_symc_entry_init(symc_dma);
    drv_symc_smmu_bypass();
    drv_symc_smmu_base_addr();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_symc_suspend(void)
{
    return;
}

s32 drv_symc_deinit(void)
{
    s32 ret = HI_FAILURE;
    u32 i;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);

    ret = drv_symc_mem_deinit();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_mem_deinit, ret);
        return ret;
    }
    module_disable(CRYPTO_MODULE_ID_SYMC);

#ifdef CRYPTO_OS_INT_SUPPORT
    drv_symc_unregister_interrupt();
#endif

    /* free all channel */
    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if (CIPHER_HARD_CHANNEL_MASK & (0x1 << i))
        {
            drv_symc_free_chn(i);
        }
    }

    crypto_free(hard_context);
    hard_context = HI_NULL;
    symc_initialize = HI_FALSE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_symc_add_buf_usage(u32 chn_num, u32 in, symc_node_usage usage)
{
    symc_hard_context *ctx = HI_NULL;
    u32 id = 0;

    ctx = &hard_context[chn_num];

    if (HI_TRUE == in)
    {
        /* get last node */
        id = (ctx->id_in == 0) ? SYMC_MAX_LIST_NUM - 1 : ctx->id_in - 1;

        ctx->entry_in[id].sym_ctrl |= usage;
        HI_LOG_INFO("chn %d, add symc in ctrl: id %d, ctrl 0x%x\n", chn_num, id, ctx->entry_in[id].sym_ctrl);
    }
    else
    {
        /* get last node */
        id = (ctx->id_out == 0) ? SYMC_MAX_LIST_NUM - 1 : ctx->id_out - 1;

        ctx->entry_out[id].aes_ctrl |= usage;
        HI_LOG_INFO("chn %d, add symc out ctrl: id %d, ctrl 0x%x\n", chn_num, id, ctx->entry_out[id].aes_ctrl);
    }

    return;
}

void drv_symc_set_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD], u32 ivlen, u32 flag)
{
    u32 i;
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = &hard_context[chn_num];

    /*copy iv data into channel context*/
    for (i=0; i<SYMC_IV_MAX_SIZE_IN_WORD; i++)
    {
        ctx->iv[i] = iv[i];
    }
    ctx->iv_flag = flag;
    ctx->iv_len = ivlen;

    HI_LOG_FuncExit();
    return;
}

void drv_symc_get_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD])
{
    u32 i;

    HI_LOG_FuncEnter();

    for (i=0; i<SYMC_IV_MAX_SIZE_IN_WORD; i++)
    {
        iv[i] = SYMC_READ(CHANn_CIPHER_IVOUT(chn_num) + i * 4);
        HI_LOG_DEBUG("IV[%d]: 0x%x\n", i, iv[i]);
    }

    HI_LOG_FuncExit();
    return;
}

void drv_symc_set_key(u32 chn_num, u32 key[SYMC_KEY_MAX_SIZE_IN_WORD], u32 odd)
{
    u32 i = 0;

    HI_LOG_FuncEnter();

    /*Set key, odd key only valid for aes ecb/cbc/ofb/cfb/ctr*/
    SYMC_WRITE(ODD_EVEN_KEY_SEL, odd);
    for (i=0; i<SYMC_KEY_MAX_SIZE_IN_WORD; i++)
    {
        SYMC_WRITE(CIPHER_KEY(chn_num)+i*4, key[i]);
        if (HI_FALSE == odd)
        {
            HI_LOG_DEBUG("key[0x%x]: 0x%x\n", CIPHER_KEY(chn_num)+i*4, key[i]);
        }
    }

    HI_LOG_FuncExit();
    return;
}

void drv_symc_set_sm1_sk(u32 chn_num, u32 key[SYMC_SM1_SK_SIZE_IN_WORD])
{
    u32 i = 0;

    for (i=0; i<SYMC_SM1_SK_SIZE_IN_WORD; i++)
    {
        SYMC_WRITE(SM1_SK(chn_num)+i*4, key[i]);
        HI_LOG_DEBUG("SK[0x%x]: 0x%x\n", SM1_SK(chn_num)+i*4, key[i]);
    }
    return;
}

s32 drv_symc_add_inbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage)
{
    symc_hard_context *ctx = HI_NULL;
    u32 id = 0, size = 0;
    u32 i = 0;
    void *addr = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];

    id = ctx->id_in;
    addr = &ctx->entry_in[id];
    size = sizeof(symc_entry_in);
    crypto_memset(addr, size, 0, size);
    ctx->entry_in[id].spacc_cmd = 0x00;
    ctx->entry_in[id].sym_start_addr = ADDR_L32(buf_phy);
    ctx->entry_in[id].sym_start_high = ADDR_H32(buf_phy);
    ctx->entry_in[id].sym_alg_length = buf_size;
    ctx->entry_in[id].sym_ctrl =  usage;

    if (SYMC_MODE_GCM == ctx->mode)
    {
        ctx->entry_in[id].gcm_iv_len = ctx->iv_len - 1;
    }

    /* set IV to every node, but the hardware only update th IV
     * from node when first flag is 1
     */
    for (i=0; i<SYMC_IV_MAX_SIZE_IN_WORD; i++)
    {
        ctx->entry_in[id].IV[i] = ctx->iv[i];
        HI_LOG_DEBUG("IV[%d]: 0x%x\n", i, ctx->iv[i]);
    }

    if (CIPHER_IV_CHANGE_ONE_PKG == ctx->iv_flag)
    {
        /* update iv for first node */
        ctx->iv_flag = 0x00;

        /* don't update iv any more */
        ctx->entry_in[id].sym_ctrl |= SYMC_NODE_USAGE_FIRST;
    }
    else if (CIPHER_IV_CHANGE_ALL_PKG == ctx->iv_flag)
    {
        /* update iv for all node */
        ctx->entry_in[id].sym_ctrl |= SYMC_NODE_USAGE_FIRST | SYMC_NODE_USAGE_LAST;
    }

    /* move to next node */
    ctx->id_in++;
    ctx->id_in %= SYMC_MAX_LIST_NUM;
    HI_LOG_INFO("chn %d, add symc in buf[%p]: id %d, addr 0x%x, len 0x%x, ctrl 0x%x\n",
        chn_num, &ctx->entry_in[id], id, ADDR_L32(buf_phy), buf_size, ctx->entry_in[id].sym_ctrl);

    /* total count of computed nodes add 1*/
    ctx->cnt_in++;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_add_outbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage)
{
    symc_hard_context *ctx = HI_NULL;
    u32 id = 0, size = 0;
    void *addr = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];

    id = ctx->id_out;
    addr = &ctx->entry_out[id];
    size = sizeof(symc_entry_out);
    crypto_memset(addr, size, 0, size);
    ctx->entry_out[id].sym_start_addr = ADDR_L32(buf_phy);
    ctx->entry_out[id].tag[0] = ADDR_H32(buf_phy);
    ctx->entry_out[id].sym_alg_length = buf_size;
    ctx->entry_out[id].aes_ctrl =  usage;

    /* move to next node */
    ctx->id_out++;
    ctx->id_out %= SYMC_MAX_LIST_NUM;
    HI_LOG_INFO("chn %d, add symc out buf[%p]: id %d, addr 0x%x, len 0x%x, ctrl 0x%x\n",
        chn_num, &ctx->entry_out[id], id, ADDR_L32(buf_phy), buf_size, usage);

    /* total count of computed nodes add 1*/
    ctx->cnt_out++;

   HI_LOG_FuncExit();
   return HI_SUCCESS;
}

s32 drv_aead_ccm_add_n(u32 chn_num, u8 *n)
{
    s32 ret = HI_FAILURE;
    symc_hard_context *ctx = HI_NULL;
    symc_node_usage usage = 0x00;
    compat_addr dma_pad;
    u8 *via_pad = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];

    HI_LOG_DEBUG("PAD buffer, PHY: 0x%x, VIA %p\n", ADDR_L32(ctx->dma_pad), ctx->via_pad);

    ADDR_U64(dma_pad) = ADDR_U64(ctx->dma_pad) + ctx->offset_pad;
    via_pad = ctx->via_pad + ctx->offset_pad;

    usage = SYMC_NODE_USAGE_IN_CCM_N | SYMC_NODE_USAGE_LAST;
    crypto_memcpy(via_pad, SYMC_CCM_N_LEN, n, SYMC_CCM_N_LEN);
    ctx->offset_pad += SYMC_CCM_N_LEN;
    ret = drv_symc_add_inbuf(chn_num, dma_pad, SYMC_CCM_N_LEN, usage);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static u32 drv_aead_ccm_a_head(u8 *buf, u32 alen)
{
   u32 idx = 0;

   /* Formatting of the Associated Data in B1, the length of A denotes as a*/
   /* The value a is encoded according to the following three cases:
    * If 0 < a < 2^16 - 2^8, then a  is encoded as a[0..15], i.e., two octets.
    * If 2^16 - 2^8 ¡Üa < 2^32, then a  is encoded as 0xff || 0xfe || a[0..31], i.e., six octets.
    * If 2^32 ¡Üa < 2^64, then  a is encoded as 0xff || 0xff || a[0..63], i.e., ten octets.
    * For example, if a=2^16, the encoding of a  is
    * 11111111 11111110 00000000 00000001 00000000 00000000.
    */
    if (alen < SYMC_CCM_A_SMALL_LEN)
    {
        buf[idx++] = (HI_U8)(alen >> 8);
        buf[idx++] = (HI_U8)(alen);
    }
    else
    {
        buf[idx++] = 0xFF;
        buf[idx++] = 0xFE;
        buf[idx++] = (HI_U8)(alen >> 24);
        buf[idx++] = (HI_U8)(alen >> 16);
        buf[idx++] = (HI_U8)(alen >> 8);
        buf[idx++] = (HI_U8)alen;
    }

    return idx;
}

s32 drv_aead_ccm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size)
{
    symc_hard_context *ctx = HI_NULL;
    compat_addr dma_pad;
    u8 *via_pad = HI_NULL;
    s32 ret = HI_FAILURE;
    u32 count = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);
    ctx = &hard_context[chn_num];
    CRYPTO_ASSERT(SYMC_PAD_BUFFER_LEN > (ctx->offset_pad + SYMC_CCM_A_HEAD_LEN));

    /* return success when alen is zero*/
    if (0x00 == buf_size)
    {
        return HI_SUCCESS;
    }

    ADDR_U64(dma_pad) = ADDR_U64(ctx->dma_pad) + ctx->offset_pad;
    via_pad = ctx->via_pad + ctx->offset_pad;
    crypto_memset(via_pad, AES_BLOCK_SIZE * 2, 0, AES_BLOCK_SIZE * 2);

    /* add ccm a head */
    count = drv_aead_ccm_a_head(via_pad, buf_size);
    ret = drv_symc_add_inbuf(chn_num, dma_pad, count, SYMC_NODE_USAGE_IN_CCM_A);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    /* move buffer addr */
    ctx->offset_pad += count;
    ADDR_U64(dma_pad) += count;
    via_pad += count;

    /*  add the phy of A into node list*/
    ret = drv_symc_add_inbuf(chn_num, buf_phy, buf_size, SYMC_NODE_USAGE_IN_CCM_A);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    /*if idx + Alen do not aligned with 16, padding 0 to the tail*/
    count = (buf_size + count) % AES_BLOCK_SIZE;
    if (0 < count)
    {
        /* add the padding phy of A into node list*/
        ret = drv_symc_add_inbuf(chn_num, dma_pad, AES_BLOCK_SIZE - count,
            SYMC_NODE_USAGE_IN_CCM_A);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
            return ret;
        }
        ctx->offset_pad += AES_BLOCK_SIZE - count;
    }

    /* add ccm a last flag */
    drv_symc_add_buf_usage(chn_num, HI_TRUE, SYMC_NODE_USAGE_LAST);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_aead_gcm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size)
{
    symc_hard_context *ctx = HI_NULL;
    compat_addr dma_pad;
    u8 *via_pad = HI_NULL;
    s32 ret = HI_FAILURE;
    u32 count = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);
    ctx = &hard_context[chn_num];
    CRYPTO_ASSERT(SYMC_PAD_BUFFER_LEN > (ctx->offset_pad + AES_BLOCK_SIZE));

    /* return success when alen is zero*/
    if (0x00 == buf_size)
    {
        HI_LOG_FuncExit();
        return HI_SUCCESS;
    }

    ADDR_U64(dma_pad) = ADDR_U64(ctx->dma_pad) + ctx->offset_pad;
    via_pad = ctx->via_pad + ctx->offset_pad;
    crypto_memset(via_pad, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);

    /*Add phy of A into node list*/
    ret = drv_symc_add_inbuf(chn_num, buf_phy, buf_size, SYMC_NODE_USAGE_IN_GCM_A);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    /*if Alen do not aligned with 16, padding 0 to the tail*/
    count = (buf_size + count) % AES_BLOCK_SIZE;
    if (0 < count)
    {
        /* add the padding phy of A into node list*/
        ret = drv_symc_add_inbuf(chn_num, dma_pad, AES_BLOCK_SIZE - count,
            SYMC_NODE_USAGE_IN_GCM_A);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
            return ret;
        }
        ctx->offset_pad += AES_BLOCK_SIZE - count;
    }

    /* add gcm a last flag */
    drv_symc_add_buf_usage(chn_num, HI_TRUE, SYMC_NODE_USAGE_LAST);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_aead_gcm_add_clen(u32 chn_num, u8 *clen)
{
    s32 ret = HI_FAILURE;
    symc_hard_context *ctx = HI_NULL;
    symc_node_usage usage = 0x00;
    compat_addr dma_pad;
    u8 *via_pad = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);
    ctx = &hard_context[chn_num];
    CRYPTO_ASSERT(SYMC_PAD_BUFFER_LEN > (ctx->offset_pad + SYMC_CCM_N_LEN));

    /* add Clen */
    ADDR_U64(dma_pad) = ADDR_U64(ctx->dma_pad) + ctx->offset_pad;
    via_pad = ctx->via_pad + ctx->offset_pad;

    usage = SYMC_NODE_USAGE_IN_GCM_LEN | SYMC_NODE_USAGE_LAST;

    crypto_memcpy(via_pad, SYMC_GCM_CLEN_LEN, clen, SYMC_GCM_CLEN_LEN);
    ctx->offset_pad += SYMC_GCM_CLEN_LEN;

    ret = drv_symc_add_inbuf(chn_num, dma_pad, SYMC_GCM_CLEN_LEN, usage);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_aead_get_tag(u32 chn_num, u32 *tag)
{
    symc_hard_context *ctx = HI_NULL;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    u32 last;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];

    out_node_cfg.u32 = SYMC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    last = out_node_cfg.bits.cipher_out_node_wptr;
    last = (last == 0) ? (SYMC_MAX_LIST_NUM - 1) : (last -1);

    crypto_memcpy(tag, AEAD_TAG_SIZE_IN_WORD * 4, ctx->entry_out[last].tag,
        AEAD_TAG_SIZE_IN_WORD * 4);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_node_check(symc_alg alg, symc_mode mode,
                    u32 klen, u32 block_size,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num)
{
    u32 i = 0;
    u32 total = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(0 != block_size);

    CRYPTO_UNUSED(input);
    CRYPTO_UNUSED(output);

    for (i=0; i<pkg_num; i++)
    {
        /* Used the odd key must accord with conditions as follows:*/
        if (usage_list[i] & SYMC_NODE_USAGE_ODD_KEY)
        {
             /* 1. Only support aes ecb/cbc/cfb/ofb/ctr */
            if ((SYMC_ALG_AES != alg)
               || ((SYMC_MODE_ECB != mode)
                  && (SYMC_MODE_CBC != mode)
                  && (SYMC_MODE_CFB != mode)
                  && (SYMC_MODE_OFB != mode)
                  && (SYMC_MODE_CTR != mode)))
            {
                 HI_LOG_ERROR("Odd key only support aes ecb/cbc/cfb/ofb/ctr.");
                 HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                 return HI_ERR_CIPHER_INVALID_PARA;
            }

            /* 2. Only support aes128 */
            if (AES_CCM_GCM_KEY_LEN != klen)
            {
                 HI_LOG_ERROR("Odd key only support aes128, klen %d\n", klen);
                 HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                 return HI_ERR_CIPHER_INVALID_PARA;
            }

            /* 3. each node length must be a multiple of 64*/
            if ((length[i] % (AES_BLOCK_SIZE * 4)) != 0)
            {
                 HI_LOG_ERROR("Odd key only supported when each node length is a multiple of 64.");
                 HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_LENGTH);
                 return HI_ERR_CIPHER_INVALID_LENGTH;
            }
        }

        /* each node length can't be zero*/
        if (length[i] == 0)
        {
            HI_LOG_ERROR("PKG len must large than 0.\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_LENGTH);
            return HI_ERR_CIPHER_INVALID_LENGTH;
        }

        /* check overflow */
        if (length[i] > ADDR_L32(input[i]) + length[i])
        {
            HI_LOG_ERROR("PKG len overflow.\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_LENGTH);
            return HI_ERR_CIPHER_INVALID_LENGTH;
        }
        total += length[i];
    }

    if((SYMC_ALG_NULL_CIPHER != alg) &&
        ((SYMC_MODE_ECB == mode)
        || (SYMC_MODE_CBC == mode)
        || (SYMC_MODE_CFB == mode)
        || (SYMC_MODE_OFB == mode)))
    {
       /* The length of data depend on alg and mode, which limit to hardware
        * for ecb/cbc/ofb/cfb, the total data length must aligned with block size.
        * for ctr/ccm/gcm, support any data length.
        */
        if (total % block_size != 0)
        {
            HI_LOG_ERROR("PKG len must align with 0x%x.\n", block_size);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_LENGTH);
            return HI_ERR_CIPHER_INVALID_LENGTH;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_config(u32 chn_num, symc_alg alg, symc_mode mode, symc_width width, u32 decrypt,
                u32 sm1_round_num, symc_klen klen, u32 hard_key)
{
    symc_hard_context *ctx = HI_NULL;
    U_CHANN_CIPHER_CTRL cipher_ctrl;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);
    HI_LOG_CHECK_PARAM(SYMC_ALG_COUNT <= alg);
    HI_LOG_CHECK_PARAM(SYMC_MODE_GCM < mode);
    HI_LOG_CHECK_PARAM(SYMC_KEY_LEN_COUNT <= klen);

    ctx = &hard_context[chn_num];

    /* record alg */
    ctx->alg = alg;
    CRYPTO_UNUSED(sm1_round_num);

    HI_LOG_INFO("symc configure, chn %d, alg %d, mode %d, dec %d, hard %d\n",
        chn_num, alg, mode, decrypt, hard_key);

    cipher_ctrl.u32 = SYMC_READ(CHANn_CIPHER_CTRL(chn_num));
    cipher_ctrl.bits.sym_chn_sm1_round_num = sm1_round_num;
    cipher_ctrl.bits.sym_chn_key_sel = hard_key;
    cipher_ctrl.bits.sym_chn_key_length = klen;
    cipher_ctrl.bits.sym_chn_dat_width = width;
    cipher_ctrl.bits.sym_chn_decrypt = decrypt;
    cipher_ctrl.bits.sym_chn_alg_sel = alg;
    cipher_ctrl.bits.sym_chn_alg_mode = mode;
    ctx->mode = mode;
    SYMC_WRITE(CHANn_CIPHER_CTRL(chn_num), cipher_ctrl.u32);
    HI_LOG_INFO("CHANn_CIPHER_CTRL(%d): 0x%x\n", chn_num, cipher_ctrl.u32);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_set_isr_callback(u32 chn_num, callback_symc_isr callback, void *ctx)
{
    symc_hard_context *hisi_ctx = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    hisi_ctx = &hard_context[chn_num];

    hisi_ctx->callback = callback;
    hisi_ctx->ctx = ctx;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_start(u32 chn_num)
{
    symc_hard_context *ctx = HI_NULL;
    U_CHANN_CIPHER_IN_NODE_CFG in_node_cfg;
    U_CHANN_CIPHER_OUT_NODE_CFG out_node_cfg;
    u32 ptr = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];

    HI_LOG_INFO("symc start, chn %d\n", chn_num);

    ctx->done = HI_FALSE;

    /*configure out nodes*/
    out_node_cfg.u32 = SYMC_READ(CHANn_CIPHER_OUT_NODE_CFG(chn_num));
    if (out_node_cfg.bits.cipher_out_node_wptr != out_node_cfg.bits.cipher_out_node_rptr)
    {
        HI_LOG_ERROR("Error, chn %d is busy.\n", chn_num);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_BUSY);
        return HI_ERR_CIPHER_BUSY;
    }
    ptr = out_node_cfg.bits.cipher_out_node_wptr + ctx->cnt_out;
    out_node_cfg.bits.cipher_out_node_wptr = ptr % SYMC_MAX_LIST_NUM;
    out_node_cfg.bits.cipher_out_node_mpackage_int_level = ctx->cnt_out;
    SYMC_WRITE(CHANn_CIPHER_OUT_NODE_CFG(chn_num), out_node_cfg.u32);
    HI_LOG_INFO("CHANn_CIPHER_OUT_NODE_CFG: 0x%x\n", out_node_cfg.u32);

    /*configure in nodes*/
    in_node_cfg.u32 = SYMC_READ(CHANn_CIPHER_IN_NODE_CFG(chn_num));
    if (in_node_cfg.bits.cipher_in_node_wptr != in_node_cfg.bits.cipher_in_node_rptr)
    {
        HI_LOG_ERROR("Error, chn %d is busy.\n", chn_num);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_BUSY);
        return HI_ERR_CIPHER_BUSY;
    }
    ptr = in_node_cfg.bits.cipher_in_node_wptr + ctx->cnt_in;
    in_node_cfg.bits.cipher_in_node_wptr = ptr % SYMC_MAX_LIST_NUM;
    in_node_cfg.bits.cipher_in_node_mpackage_int_level = ctx->cnt_in;

//    flush_cache(); /* may reduce the performance */

    /* SM4 may be disable independent from spacc */
    if (SYMC_ALG_SM4 == ctx->alg)
    {
        module_enable(CRYPTO_MODULE_ID_SM4);
    }

   /* make sure all the above explicit memory accesses and instructions are completed
    * before start the hardware.
    */
    ARM_MEMORY_BARRIER();

    /* start */
    SYMC_WRITE(CHANn_CIPHER_IN_NODE_CFG(chn_num), in_node_cfg.u32);
    HI_LOG_INFO("CHANn_CIPHER_IN_NODE_CFG: 0x%x\n", in_node_cfg.u32);

    /*all the nodes are processed, retset the cnount to zero */
    ctx->cnt_in = 0;
    ctx->cnt_out = 0;
    ctx->offset_pad = 0;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_wait_done(u32 chn_num, u32 timeout)
{
    u32 int_valid = 0, int_num = 0;
    u32 i;
    s32 ret = HI_FAILURE;
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_TRUE == symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = &hard_context[chn_num];
    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, HI_NULL);

#ifdef CRYPTO_OS_INT_SUPPORT
    /* interrupt support, wait irq*/
    if (int_valid)
    {
        /* wait interrupt */
        ret = crypto_queue_wait_timeout(ctx->queue, HI_FALSE != ctx->done, timeout);

        /* Disable SM4 independent from spacc */
        if (SYMC_ALG_SM4 == ctx->alg)
        {
            module_disable(CRYPTO_MODULE_ID_SM4);
        }

        if (0 == ret)
        {
            HI_LOG_ERROR("wait done timeout, chn=%d\n", chn_num);
            HI_LOG_PrintFuncErr(crypto_queue_wait_timeout, ret);
            drv_symc_get_err_code(chn_num);
            return HI_ERR_CIPHER_TIMEOUT;
        }
    }
    else /* interrupt unsupport, query the raw interrupt flag*/
#endif
    {
        for (i=0; i<timeout; i++)
        {
            ret = drv_symc_done_try(chn_num);
            if (HI_SUCCESS == ret)
            {
                break;
            }
            if (MS_TO_US >= i)
            {
                crypto_udelay(1);  /* short waitting for 1000 us */
            }
            else
            {
                crypto_msleep(1);  /* long waitting for 5000 ms*/
            }
        }

        /* Disable SM4 independent from spacc */
        if (SYMC_ALG_SM4 == ctx->alg)
        {
            module_disable(CRYPTO_MODULE_ID_SM4);
        }

        if (timeout <= i)
        {
            HI_LOG_ERROR("symc wait done timeout, chn=%d\n", chn_num);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_TIMEOUT);
            drv_symc_get_err_code(chn_num);
            return HI_ERR_CIPHER_TIMEOUT;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_symc_set_destory_callbcak(u32 chn_num, callback_symc_destory destory)
{
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = &hard_context[chn_num];
    ctx->destory = destory;

    HI_LOG_FuncExit();
    return;
}

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
s32 drv_symc_proc_status(symc_chn_status *status)
{
    u32 addr = 0;
    U_CHANN_CIPHER_CTRL ctrl;
    U_CIPHER_INT_RAW stIntRaw;
    U_CIPHER_INT_EN  stIntEn;
    U_CHANN_CIPHER_IN_NODE_CFG stInNode;
    u32 val;
    u32 i, j;

    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if (HI_TRUE == hard_context[i].open)
        {
            status[i].open = "open ";
        }
        else
        {
            status[i].open = "close";
        }
        /* get cipher ctrl */
        if (0 != i)
        {
            addr = CHANn_CIPHER_CTRL(i);
        }
        else
        {
            addr = CHAN0_CIPHER_CTRL;
        }

        ctrl.u32 = SYMC_READ(addr);
        status[i].decrypt = ctrl.bits.sym_chn_decrypt;
        switch(ctrl.bits.sym_chn_alg_sel)
        {
            case CRYP_CIPHER_ALG_DES:
            {
                status[i].alg = "DES ";
                break;
            }
            case CRYP_CIPHER_ALG_3DES:
            {
                status[i].alg = "3DES";
                break;
            }
            case CRYP_CIPHER_ALG_AES:
            {
                status[i].alg = "AES ";
                break;
            }
            case CRYP_CIPHER_ALG_SM1:
            {
                status[i].alg = "SM1 ";
                break;
            }
            case CRYP_CIPHER_ALG_SM4:
            {
                status[i].alg = "SM4 ";
                break;
            }
            case CRYP_CIPHER_ALG_DMA:
            {
                status[i].alg = "DMA ";
                break;
            }
            default:
            {
                status[i].alg = "BUTT";
                break;
            }
        }

        switch(ctrl.bits.sym_chn_alg_mode)
        {
            case CRYP_CIPHER_WORK_MODE_ECB:
            {
                status[i].mode = "ECB ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_CBC:
            {
                status[i].mode = "CBC ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_CFB:
            {
                status[i].mode = "CFB ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_OFB:
            {
                status[i].mode = "OFB ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_CTR:
            {
                status[i].mode = "CTR ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_CCM:
            {
                status[i].mode = "CCM ";
                break;
            }
            case CRYP_CIPHER_WORK_MODE_GCM:
            {
                status[i].mode = "GCM ";
                break;
            }
            default:
            {
                status[i].mode = "BUTT";
                break;
            }
        }

        if (ctrl.bits.sym_chn_alg_sel == CRYP_CIPHER_ALG_AES)
        {
            switch(ctrl.bits.sym_chn_key_length)
            {
                case CRYP_CIPHER_KEY_AES_128BIT:
                {
                    status[i].klen = AES_KEY_128BIT;
                    break;
                }
                case CRYP_CIPHER_KEY_AES_192BIT:
                {
                    status[i].klen = AES_KEY_192BIT;
                    break;
                }
                case CRYP_CIPHER_KEY_AES_256BIT:
                {
                    status[i].klen = AES_KEY_256BIT;
                    break;
                }
                default:
                {
                    status[i].klen = 0;
                    break;
                }
            }
        }
        else if (ctrl.bits.sym_chn_alg_sel == CRYP_CIPHER_ALG_DES)
        {
            status[i].klen = DES_KEY_SIZE;
        }
        else if (ctrl.bits.sym_chn_alg_sel == CRYP_CIPHER_ALG_3DES)
        {
            switch(ctrl.bits.sym_chn_key_length)
            {
                case CRYP_CIPHER_KEY_DES_3KEY:
                {
                    status[i].klen = TDES_KEY_192BIT;
                    break;
                }
                case CRYP_CIPHER_KEY_DES_2KEY:
                {
                    status[i].klen = TDES_KEY_128BIT;
                    break;
                }
                default:
                {
                    status[i].klen = 0;
                    break;
                }
            }
        }
        else if (ctrl.bits.sym_chn_alg_sel == CRYP_CIPHER_ALG_SM1)
        {
            status[i].klen = SM1_AK_EK_SIZE + SM1_SK_SIZE;
        }
        else if (ctrl.bits.sym_chn_alg_sel == CRYP_CIPHER_ALG_SM4)
        {
            status[i].klen = SM4_KEY_SIZE;
        }
        else
        {
            status[i].klen = 0;
        }

        if (ctrl.bits.sym_chn_key_sel)
        {
            status[i].ksrc = "HW";
        }
        else
        {
            status[i].ksrc = "SW";
        }

        /* get data in */
        if (0 != i)
        {
            addr = CHANn_CIPHER_IN_BUF_RPTR(i);
            status[i].inaddr = SYMC_READ(addr);
        }
        else
        {
            status[0].inaddr = CHAN0_CIPHER_DIN;
        }

        /* get data out */
        if (0 != i)
        {
            addr = CHANn_CIPHER_OUT_BUF_RPTR(i);
            status[i].outaddr = SYMC_READ(addr);
        }
        else
        {
            status[0].outaddr = CHAN0_CIPHER_DOUT;
        }

        for (j=0; j<4; j++)
        {
            val = SYMC_READ(CHANn_CIPHER_IVOUT(i) + j*4);
            HEX2STR(status[i].iv+j*8, (HI_U8)(val & 0xFF));
            HEX2STR(status[i].iv+j*8+2, (HI_U8)((val >> 8) & 0xFF));
            HEX2STR(status[i].iv+j*8+4, (HI_U8)((val >> 16) & 0xFF));
            HEX2STR(status[i].iv+j*8+6, (HI_U8)((val >> 24) & 0xFF));
        }

        /* get INT RAW status */
        stIntRaw.u32 = SYMC_READ(CIPHER_INT_RAW);
        status[i].inraw= (stIntRaw.bits.cipher_chn_ibuf_raw >> i) & 0x1;
        status[i].outraw= (stIntRaw.bits.cipher_chn_obuf_raw >> i) & 0x1;

        /* get INT EN status */
        stIntEn.u32 = SYMC_READ(CIPHER_INT_EN);
        status[i].intswitch= stIntEn.bits.cipher_nsec_int_en;
        status[i].inten= (stIntEn.bits.cipher_chn_ibuf_en >> i) & 0x1;
        status[i].outen= (stIntEn.bits.cipher_chn_obuf_en >> i) & 0x1;

        /* get INT_OINTCFG */
        addr = CHANn_CIPHER_IN_NODE_CFG(i);
        stInNode.u32 = SYMC_READ(addr);
        status[i].outintcnt = stInNode.bits.cipher_in_node_mpackage_int_level;

    }

    return HI_SUCCESS;
}
#endif
/******* proc function end ********/

void drv_symc_get_capacity(symc_capacity *capacity)
{
    HI_LOG_FuncEnter();

   /* the mode depend on alg, which limit to hardware
    * des/3des support ecb/cbc/cfb/ofb
    * aes support ecb/cbc/cfb/ofb/ctr/ccm/gcm
    * sm1 support ecb/cbc/cfb/ofb
    * sm4 support ecb/cbc/ctr
    */

    crypto_memset(capacity, sizeof(symc_capacity), 0,  sizeof(symc_capacity));

    /* AES */
    capacity->aes_ecb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_cbc = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_ofb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_cfb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_ctr = CRYPTO_CAPACITY_SUPPORT;
#ifdef CHIP_AES_CCM_GCM_SUPPORT
    capacity->aes_ccm = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_gcm = CRYPTO_CAPACITY_SUPPORT;
#endif

    /* TDES */
    capacity->tdes_ecb = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_cbc = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_ofb = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_cfb = CRYPTO_CAPACITY_SUPPORT;

    /* DES */
    capacity->des_ecb  = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_cbc  = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_ofb  = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_cfb  = CRYPTO_CAPACITY_SUPPORT;

    /* SM1 */
#ifdef CHIP_SYMC_SM1_SUPPORT
    capacity->sm1_ecb  = CRYPTO_CAPACITY_SUPPORT;
    capacity->sm1_cbc  = CRYPTO_CAPACITY_SUPPORT;
    capacity->sm1_ofb  = CRYPTO_CAPACITY_SUPPORT;
    capacity->sm1_cfb  = CRYPTO_CAPACITY_SUPPORT;
#endif

    /* SM4 */
    capacity->sm4_ecb  = CRYPTO_CAPACITY_SUPPORT;
    capacity->sm4_cbc  = CRYPTO_CAPACITY_SUPPORT;
    capacity->sm4_ctr  = CRYPTO_CAPACITY_SUPPORT;

    /* DMA */
    capacity->dma = CRYPTO_CAPACITY_SUPPORT;

    return;
}

/** @}*/  /** <!-- ==== API Code end ====*/

#endif //End of CHIP_SYMC_VER_V200
