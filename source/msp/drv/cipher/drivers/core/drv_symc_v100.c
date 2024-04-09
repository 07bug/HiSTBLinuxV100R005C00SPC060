/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_symc_v100.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_symc_v100.h"
#include "drv_symc.h"

#ifdef CHIP_SYMC_VER_V100

#define MAX_NODE_SIZE                (0x100000 - 16)

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! Define the struct of node */
typedef struct
{
    u32 phy_addr;  /*!<  physics address of buffer */
    u32 flags;     /*!<  flag */
    u32 length;    /*!<  length of buffer */
    u32 iv_addr;   /*!<  physics address of iv */
}symc_entry;

/*! Define the struct of iv in node */
typedef struct
{
    u32 iv[SYMC_IV_MAX_SIZE_IN_WORD];  /*!<  iv data */
}symc_entry_iv;

/*! Define the context of cipher */
typedef struct
{
    symc_entry *entry_in;     /*!<  in node list */
    symc_entry *entry_out;    /*!<  out node list */
    symc_entry_iv *entry_iv;  /*!<  buffer to store the IV */
    u32 iv[SYMC_IV_MAX_SIZE_IN_WORD];/*!<  iv data from user*/

    /* iv usage flag, should be CIPHER_IV_CHANGE_ONE_PKG
     * or CIPHER_IV_CHANGE_ALL_PKG.
     */
    u32 iv_flag;
    u32 id_in;                       /*!<  current in nodes index */
    u32 id_out;                      /*!<  current out nodes index */
    u32 cnt;                         /*!<  total count nodes to be computed */
    u32 done;                        /*!<  calculation finish flag*/
    crypto_queue_head  queue;        /*!<  quene list */
    callback_symc_isr callback;      /*!<  isr callback functon */
    callback_symc_destory destory;   /*!<  destory callback functon */
    void *ctx;                       /*!<  params for isr callback functon */
}symc_hard_context;

/*! Channel of cipher */
static channel_context symc_hard_channel[CRYPTO_HARD_CHANNEL_MAX];

/*! dma memory of cipher node list*/
static crypto_mem   symc_dma;

/*! symc already initialize or not */
static u32 symc_initialize = HI_FALSE;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/


static s32 drv_symc_done_try(u32 chn_num)
{
    U_INT_RAW status;
    symc_hard_context *ctx = HI_NULL;
    u32 process = 0;

    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    status.u32 = SYMC_READ(REG_INT_RAW);
    status.bits.chn_obuf_raw &= 0x01 << chn_num; /* check interception */

    /*clear interception*/
    SYMC_WRITE(REG_INT_RAW, status.u32);

    if (status.bits.chn_obuf_raw)
    {
        ctx = crypto_channel_get_context(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, chn_num);
        if (HI_NULL == ctx)
        {
            HI_LOG_ERROR("crypto channel get context failed,ctx is null!\n");
            return HI_ERR_CIPHER_INVALID_POINT;
        }

        process = SYMC_READ(REG_CHANn_OFULL_CNT(chn_num));
        SYMC_WRITE(REG_CHANn_IEMPTY_CNT(chn_num), process);
        SYMC_WRITE(REG_CHANn_OFULL_CNT(chn_num),  process);
        ctx->cnt -= process;
    }

    if (0 == status.bits.chn_obuf_raw)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

#ifdef CRYPTO_OS_INT_SUPPORT
static u32 drv_symc_done_notify(void)
{
    symc_hard_context *ctx = HI_NULL;
    U_INT_RAW status;
    u32 process = 0;
    u32 i;

    status.u32 = SYMC_READ(REG_INT_RAW);

    /*must clear interception before any operation */
    SYMC_WRITE(REG_INT_RAW, status.u32);

    /*just process the valid channel*/
    status.bits.chn_obuf_raw &= CIPHER_HARD_CHANNEL_MASK;

    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if ((status.bits.chn_obuf_raw >> i) & 0x01)
        {
            /* received interception, tell hardware that
             * we already process the output node
             */
            ctx = crypto_channel_get_context(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, i);
            if (HI_NULL == ctx)
            {
                HI_LOG_ERROR("crypto channel get context failed,ctx is null!\n");
                return 0;
            }

            process = SYMC_READ(REG_CHANn_OFULL_CNT(i));
            SYMC_WRITE(REG_CHANn_IEMPTY_CNT(i), process);
            SYMC_WRITE(REG_CHANn_OFULL_CNT(i),  process);
            ctx->cnt -= process;
        }
    }

    return status.bits.chn_obuf_raw; /* mask */

}

/*! symc interrupt process function */
static irqreturn_t drv_symc_interrupt_isr(s32 irq, void *devId)
{
    u32 mask, i;
    symc_hard_context *ctx = HI_NULL;
    s32 ret = HI_FAILURE;

    HI_LOG_DEBUG("symc irq: %d\n", irq);

    /* get channel context*/
    mask = drv_symc_done_notify();
    if (0 == mask)
    {
        HI_LOG_ERROR("Invalid mask.\n");
        return IRQ_NONE;
    }

    for (i=0; i< CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if ((mask >> i) & 0x01)
        {
            ctx = crypto_channel_get_context(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, i);
            if (HI_NULL == ctx)
            {
                HI_LOG_ERROR("Ctx get context failed.\n");
                return IRQ_NONE;
            }

            /*make sure all the loaded nodes are finished before start next compute*/
            if (0x00 != ctx->cnt)
            {
                continue;
            }

            /* continue to load other nodes */
            if ((ctx->callback) && (HI_FALSE == ctx->callback(ctx->ctx)))
            {
                HI_LOG_DEBUG("contiue to compute chn %d\n", i);
                ret = drv_symc_start(i);
                if (HI_SUCCESS != ret)
                {
                    return IRQ_NONE;
                }
            }
            else  /* finished, no more nodes need to be load */
            {
                ctx->done = HI_TRUE;
                HI_LOG_DEBUG("chn %d wake up\n", i);
                crypto_queue_wait_up(&ctx->queue);
            }
        }
    }

    return IRQ_HANDLED;
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
        HI_LOG_ERROR("Irq request failure, ret=%d, irq = %d", ret, int_num);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_REGISTER_IRQ);
        return ret;
    }

    /* initialize queue list*/
    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        crypto_queue_init(&((symc_hard_context *)symc_hard_channel[i].ctx)->queue);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*! symc unregister interrupt process function */
static void drv_symc_unregister_interrupt(void)
{
    u32 int_valid = 0, int_num = 0;
    const char *name = HI_NULL;

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
    U_INT_EN  int_en;
    U_INT_RAW int_raw;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, HI_NULL);

    if (HI_FALSE == int_valid)
    {
        int_en.u32 = SYMC_READ(REG_INT_EN);

        /*The top interrupt switch only can be enable/disable by secure CPU*/
        int_en.bits.sec_int_en = 0;
        int_en.bits.int_en = 0;
        int_en.bits.chn_obuf_en &= ~CIPHER_HARD_CHANNEL_MASK;
        SYMC_WRITE(REG_INT_EN, int_en.u32);
        HI_LOG_INFO("REG_INT_EN 0x%x\n", int_en.u32);
    }
    else
    {
        int_en.u32 = SYMC_READ(REG_INT_EN);

        /*The top interrupt switch only can be enable/disable by secure CPU*/
        int_en.bits.sec_int_en = 1;
        int_en.bits.int_en = 1;
        int_en.bits.chn_obuf_en = CIPHER_HARD_CHANNEL_MASK;
        SYMC_WRITE(REG_INT_EN, int_en.u32);
        HI_LOG_INFO("REG_INT_EN 0x%x\n", int_en.u32);
    }

    /* clear interception
     * the history of interception may trigge the system to
     * call the irq function before initialization
     * when register interrupt, this will cause a system abort.
     */
    int_raw.u32 = SYMC_READ(REG_INT_RAW);
    int_raw.bits.chn_obuf_raw &= CIPHER_HARD_CHANNEL_MASK; /* clear valid channel */
    SYMC_WRITE(REG_INT_RAW, int_raw.u32);

    HI_LOG_FuncExit();

    return;
}

#endif

/*! set symc entry */
static void drv_symc_set_entry(u32 chn, u32 dma_addr, u32 mmz_addr, void *cpu_addr)
{
    u32 i;
    symc_hard_context *ctx = (symc_hard_context *)symc_hard_channel[chn].ctx;

    HI_LOG_FuncEnter();

    /*set first in node addr*/
    HI_LOG_INFO("chn %d, entry in  dma addr 0x%x, mmz addr 0x%x, cpu addr 0x%p\n",
        chn, dma_addr, mmz_addr, cpu_addr);
    SYMC_WRITE(REG_CHANn_SRC_LST_SADDR(chn), mmz_addr);   /*node list must be mmz*/
    ctx->entry_in = cpu_addr;
    dma_addr += ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;
    mmz_addr += ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;
    cpu_addr = (u8*)cpu_addr + ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;

    /*set first out node addr*/
    HI_LOG_INFO("chn %d, entry out dma addr 0x%x, mmz addr 0x%x, cpu addr 0x%p\n",
        chn, dma_addr, mmz_addr, cpu_addr);
    SYMC_WRITE(REG_CHANn_DEST_LST_SADDR(chn), mmz_addr);   /*node list must be mmz*/
    ctx->entry_out = cpu_addr;
    dma_addr += ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;
    mmz_addr += ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;
    cpu_addr = (u8*)cpu_addr + ENTRY_NODE_SIZE * SYMC_MAX_LIST_NUM;

    /*set iv addr of in node*/
    HI_LOG_INFO("chn %d,        IV dma addr 0x%x, cpu addr 0x%p\n", chn, dma_addr, cpu_addr);
    for (i=0; i<SYMC_MAX_LIST_NUM; i++)
    {
        /*set iv dma addr to each in node, IV dma addr may be mmz or mmu*/
        ctx->entry_in[i].iv_addr = dma_addr;
        dma_addr += SYMC_IV_MAX_SIZE;
    }
    ctx->entry_iv = cpu_addr;
    cpu_addr = (u8*)cpu_addr + SYMC_IV_MAX_SIZE * SYMC_MAX_LIST_NUM;

    /*the symc module may be running at setup period,
     *Here, we must continue running immediately after the last node*/
    ctx->id_in = SYMC_READ(REG_CHANn_SRC_LST_RADDR(chn));
    ctx->id_out = SYMC_READ(REG_CHANn_DEST_LST_RADDR(chn));
    ctx->cnt = 0x00;
    HI_LOG_INFO("chn %d, id in %d, out %d\n\n", chn, ctx->id_in, ctx->id_out);

    /*set total node list Num */
    HI_LOG_DEBUG("set total node list Num\n");
    SYMC_WRITE(REG_CHANn_IBUF_NUM(chn), SYMC_MAX_LIST_NUM);
    SYMC_WRITE(REG_CHANn_OBUF_NUM(chn), SYMC_MAX_LIST_NUM);

    HI_LOG_FuncExit();

    return;
}

#ifdef CRYPTO_SMMU_SUPPORT

/*! set smmu */
static void drv_symc_smmu_bypass(void)
{
    U_CHANn_RD_DAT_ADDR_SMMU_BYPASS rd_mmu;
    U_CHANn_WR_DAT_ADDR_SMMU_BYPASS wr_mmu;

    HI_LOG_FuncEnter();

    rd_mmu.u32 = SYMC_READ(CHANn_RD_DAT_ADDR_SMMU_BYPASS);
    wr_mmu.u32 = SYMC_READ(CHANn_WR_DAT_ADDR_SMMU_BYPASS);

    /*bypass: 1-use mmz, 0-use mmu*/
    rd_mmu.bits.chann_rd_dat_addr_smmu_bypass &= ~(CIPHER_HARD_CHANNEL_MASK >> 1);
    wr_mmu.bits.chann_wr_dat_addr_smmu_bypass &= ~(CIPHER_HARD_CHANNEL_MASK >> 1);

    SYMC_WRITE(CHANn_RD_DAT_ADDR_SMMU_BYPASS, rd_mmu.u32);
    SYMC_WRITE(CHANn_WR_DAT_ADDR_SMMU_BYPASS, wr_mmu.u32);

    HI_LOG_INFO("CHANn_RD_DAT_ADDR_SMMU_BYPASS 0x%x\n", rd_mmu.u32);
    HI_LOG_INFO("CHANn_WR_DAT_ADDR_SMMU_BYPASS 0x%x\n", wr_mmu.u32);

    HI_LOG_FuncExit();

    return;
}

#ifdef CRYPTO_OS_INT_SUPPORT
/*! smmu int enable */
static void drv_symc_smmu_int_enable(void)
{
    U_SMMU_SCR scr;
    U_SMMU_INT int_en;

    HI_LOG_FuncEnter();

    /* enable smmu interception and disable bypass*/
    scr.u32 = SMMU_READ(REG_MMU_GLOBAL_CTR_ADDR);
    scr.bits.glb_bypass = 0;
    scr.bits.int_en = 1;
    SMMU_WRITE(REG_MMU_GLOBAL_CTR_ADDR, scr.u32);
    HI_LOG_INFO("REG_MMU_GLOBAL_CTR_ADDR 0x%x\n", scr.u32);

    /*enable interception*/
    if (crypto_is_sec_cpu())
    {
        int_en.u32 = SMMU_READ(REG_MMU_INTMAS_S);
        int_en.bits.ints_tlbmiss = 0;
        int_en.bits.ints_ptw_trans = 0;
        int_en.bits.ints_tlbinvalid = 0;
        SMMU_WRITE(REG_MMU_INTMAS_S, int_en.u32);
        HI_LOG_INFO("REG_MMU_INTMAS_S 0x%x\n", int_en.u32);
    }
    else
    {
        int_en.u32 = SMMU_READ(REG_MMU_INTMASK_NS);
        int_en.bits.ints_tlbmiss = 0;
        int_en.bits.ints_ptw_trans = 0;
        int_en.bits.ints_tlbinvalid = 0;
        SMMU_WRITE(REG_MMU_INTMASK_NS, int_en.u32);
        HI_LOG_INFO("REG_MMU_INTMASK_NS 0x%x\n", int_en.u32);
    }

    HI_LOG_FuncExit();

    return;
}
#endif

/*! smmu int disable */
static void drv_symc_smmu_int_disable(void)
{
    U_SMMU_SCR scr;
    U_SMMU_INT int_en;

    HI_LOG_FuncEnter();

    /* enable smmu interception and disable bypass*/
    scr.u32 = SMMU_READ(REG_MMU_GLOBAL_CTR_ADDR);
    scr.bits.glb_bypass = 0;
    scr.bits.int_en = 0;
    SMMU_WRITE(REG_MMU_GLOBAL_CTR_ADDR, scr.u32);
    HI_LOG_INFO("REG_MMU_GLOBAL_CTR_ADDR 0x%x\n", scr.u32);

    /* disable secure interception */
    int_en.u32 = SMMU_READ(REG_MMU_INTMAS_S);
    int_en.bits.ints_tlbmiss = 1;
    int_en.bits.ints_ptw_trans = 1;
    int_en.bits.ints_tlbinvalid = 1;
    SMMU_WRITE(REG_MMU_INTMAS_S, int_en.u32);
    HI_LOG_INFO("REG_MMU_INTMAS_S 0x%x\n", int_en.u32);

    /* disable non-secure interception */
    int_en.u32 = SMMU_READ(REG_MMU_INTMASK_NS);
    int_en.bits.ints_tlbmiss = 1;
    int_en.bits.ints_ptw_trans = 1;
    int_en.bits.ints_tlbinvalid = 1;
    SMMU_WRITE(REG_MMU_INTMASK_NS, int_en.u32);
    HI_LOG_INFO("REG_MMU_INTMASK_NS 0x%x\n", int_en.u32);

    HI_LOG_FuncExit();

    return;
}

/*! smmu set base address */
static s32 drv_symc_smmu_base_addr(void)
{
    u64 err_raddr = 0;
    u64 err_waddr = 0;
    u64 table_addr = 0;

    HI_LOG_FuncEnter();

    /* get table base addr from system api */
    smmu_get_table_addr(&err_raddr, &err_waddr, &table_addr);

    if (crypto_is_sec_cpu())
    {
#ifdef CHIP_SMMU_VER_V200
        SMMU_WRITE(REG_MMU_ERR_RDADDR_H_S, 0x00); /*default error read high addr*/
        SMMU_WRITE(REG_MMU_ERR_WRADDR_H_S, 0x00); /*default error write high addr*/
        SMMU_WRITE(REG_MMU_SCB_TTBR_H,     0x00); /*smmu page table high addr*/
#endif
        SMMU_WRITE(REG_MMU_ERR_RDADDR_S, (u32)err_raddr); /*default error read addr*/
        SMMU_WRITE(REG_MMU_ERR_WRADDR_S, (u32)err_waddr); /*default error write addr*/
        SMMU_WRITE(REG_MMU_SCB_TTBR, (u32)table_addr);    /*smmu page table addr*/

    }
    else
    {
#ifdef CHIP_SMMU_VER_V200
        SMMU_WRITE(REG_MMU_ERR_RDADDR_H_NS, 0x00);  /*default error read high addr*/
        SMMU_WRITE(REG_MMU_ERR_WRADDR_H_NS, 0x00);  /*default error write high addr*/
        SMMU_WRITE(REG_MMU_CB_TTBR_H,       0x00);  /*smmu page table high addr*/
#endif
        SMMU_WRITE(REG_MMU_ERR_RDADDR_NS, (u32)err_raddr);/*default error read addr*/
        SMMU_WRITE(REG_MMU_ERR_WRADDR_NS, (u32)err_waddr);/*default error write addr*/
        SMMU_WRITE(REG_MMU_CB_TTBR, (u32)table_addr);     /*smmu page table addr*/
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

/*! set secure channel,
 *  non-secure CPU can't change the value of SEC_CHN_CFG,
 *  so non-secure CPU call this function will do nothing.
 */
static void drv_symc_enable_secure(void)
{
    U_SEC_CHN_CFG sec;

    HI_LOG_FuncEnter();

    /*The REG_SEC_CHN_CFG only can be set by secure CPU*/
    sec.u32 = SYMC_READ(REG_SEC_CHN_CFG);
    sec.bits.sec_chn_cfg = CIPHER_HARD_CHANNEL_MASK;
    SYMC_WRITE(REG_SEC_CHN_CFG, sec.u32);
    HI_LOG_INFO("REG_SEC_CHN_CFG 0x%x\n", sec.u32);

    HI_LOG_FuncExit();

    return;
}

static void drv_symc_print_last_node(u32 chn_num)
{
    symc_entry *in = HI_NULL, *out = HI_NULL;
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = (symc_hard_context *)symc_hard_channel[chn_num].ctx;

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
        chn_num, in->phy_addr, in->length, out->phy_addr, out->length);

    HI_LOG_FuncExit();

    return;
}

static void drv_symc_print_status(u32 chn_num)
{
    U_INT_RAW    raw;
    U_INT_STATUS status;
    U_INT_EN     enable;
    U_SEC_CHN_CFG cfg;

    HI_LOG_FuncEnter();

    raw.u32 = SYMC_READ(REG_INT_RAW);
    status.u32 = SYMC_READ(REG_INT_STATUS);
    enable.u32 = SYMC_READ(REG_INT_EN);
    cfg.u32 = SYMC_READ(REG_SEC_CHN_CFG);

    HI_LOG_ERROR("\nsec_chn_cfg 0x%x, chn %d, nsec_int_en 0x%x, sec_int_en 0x%x, chn_obuf_en 0x%x, status 0x%x, raw 0x%x\n",
        (cfg.bits.sec_chn_cfg >> chn_num) & 0x01,
        chn_num, enable.bits.int_en, enable.bits.sec_int_en,
        (enable.bits.chn_obuf_en >> chn_num) & 0x01,
        (status.bits.chn_obuf_int >> chn_num) & 0x01,
        (raw.bits.chn_obuf_raw >> chn_num) & 0x01);

    HI_LOG_ERROR("\nThe cause of time out may be:\n"
                 "\t1. SMMU address invalid\n"
                 "\t2. interrupt number or name incorrect\n"
                 "\t3. CPU type mismatching, request %s CPU\n",
                 crypto_is_sec_cpu() ? "secure" : "non-secure");

    /* avoid compile error when HI_LOG_ERROR be defined to empty */
    CRYPTO_UNUSED(raw);
    CRYPTO_UNUSED(status);
    CRYPTO_UNUSED(enable);
    CRYPTO_UNUSED(cfg);

    HI_LOG_FuncExit();

    return;
}

static void drv_symc_get_err_code(u32 chn_num)
{
    HI_LOG_FuncEnter();

#ifdef CRYPTO_SMMU_SUPPORT
  {
       /* check error code
        * bit0: TLB miss
        * bit1: PTW transaciont error
        * bit2: TLB read invalid
        * bit3: TLB Write invalid
        */
        u32 code = 0;

        /*read error code*/
        if (crypto_is_sec_cpu())
        {
            code = SMMU_READ(REG_MMU_INTRAW_S);
            SMMU_WRITE(REG_MMU_INTRAW_S, code);
        }
        else
        {
            code = SMMU_READ(REG_MMU_INTRAW_NS);
            SMMU_WRITE(REG_MMU_INTRAW_NS, code);
        }
        HI_LOG_INFO("symc done, hardware error code 0x%x\n", code);

        if ((code >> 3) & 0x01)
        {
            HI_LOG_ERROR("MMU Error, there is a TLB Write invalid generated during the translation process.\n");
        }
        if ((code >> 2) & 0x01)
        {
            HI_LOG_ERROR("MMU Error, there is a TLB read invalid generated during the translation process.\n");
        }
        if ((code >> 1) & 0x01)
        {
            HI_LOG_ERROR("MMU Error, the PTW transaciont receive an error response.\n");
        }
        if ((code) & 0x01)
        {
            HI_LOG_ERROR("MMU Error, there is a TLB miss generated during the translation process.\n");
        }
    }
#endif

    /*print the inout buffer address*/
    drv_symc_print_last_node(chn_num);
    drv_symc_print_status(chn_num);

    HI_LOG_FuncExit();
    return;
}

void drv_symc_enrty_init(crypto_mem mem)
{
    u32 i;
    u32 dma_addr = 0;
    u32 mmz_addr = 0;
    void *cpu_addr = HI_NULL;

    HI_LOG_INFO("symc entry list configure\n");
    dma_addr = ADDR_L32(mem.dma_addr);
    mmz_addr = ADDR_L32(mem.mmz_addr);
    cpu_addr = mem.dma_virt;
    for (i=0; i<CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if ((CIPHER_HARD_CHANNEL_MASK >> i) & 0x01) /*valid channel*/
        {
            drv_symc_set_entry(i, dma_addr, mmz_addr, cpu_addr);
            dma_addr += CHN_LIST_SIZE; /* move to next channel */
            mmz_addr += CHN_LIST_SIZE; /* move to next channel */
            cpu_addr = (u8*)cpu_addr + CHN_LIST_SIZE; /* move to next channel */
        }
    }
    return;
}

/* encrypt data using special chn*/
HI_S32 drv_cipher_aes_test(HI_VOID)
{
    s32 ret = HI_SUCCESS;
    crypto_mem   mem;
    u32 chn = 0;
    u32 last = 0, first = 0;
    u32 key[SYMC_KEY_MAX_SIZE_IN_WORD] = {0};
    const char *gold_enc = "\x66\xE9\x4B\xD4\xEF\x8A\x2C\x3B\x88\x4C\xFA\x59\xCA\x34\x2B\x2E";
    s32 i;

    ret = crypto_mem_create(&mem, SEC_MMZ, "symc_data", AES_BLOCK_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, malloc ddr for symc test data failed\n");
        HI_LOG_PrintFuncErr(crypto_mem_create, ret);
        return ret;
    }

    /* read last used channel */
    last = SYMC_READ(REG_HL_APP_LEN) & 0xFF;

    /* read the max valid channel */
    for (i=CRYPTO_HARD_CHANNEL_MAX - 1; i>0; i--)
    {
        if (CIPHER_HARD_CHANNEL_MASK & (0x1 << i))
        {
            first = i;
            break;
        }
    }

    /* select a channel dfferent with last used channel*/
    if ( last == first)
    {
        chn = first - 1;
    }
    else
    {
        chn = first;
    }
    HI_LOG_INFO("drv cipher aes test, first %d, last chn %d, use chn %d\n", first, last, chn);

    symc_hard_channel[chn].open = HI_TRUE;
    drv_symc_set_key(chn, key, HI_FALSE);

    ret = drv_symc_config(chn, SYMC_ALG_AES, SYMC_MODE_ECB, SYMC_DAT_WIDTH_128,
        HI_FALSE, 0, SYMC_KEY_DEFAULT, HI_FALSE);
    if(HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_config, ret);
        goto exit;
    }
    crypto_memset(mem.dma_virt, AES_BLOCK_SIZE, 0, AES_BLOCK_SIZE);

    ret = drv_symc_add_inbuf(chn, mem.dma_addr, AES_BLOCK_SIZE, SYMC_NODE_USAGE_NORMAL);
    if(HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_inbuf, ret);
        goto exit;
    }

    ret = drv_symc_add_outbuf(chn, mem.dma_addr, AES_BLOCK_SIZE, SYMC_NODE_USAGE_NORMAL);
    if(HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_add_outbuf, ret);
        goto exit;
    }

    /* start running */
    ret = drv_symc_start(chn);
    if(HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_start, ret);
        goto exit;
    }

    /* wait done */
    ret = drv_symc_wait_done(chn, CRYPTO_TIME_OUT);
    if(HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_symc_wait_done, ret);
        goto exit;
    }
//    HI_PRINT_HEX("AES", mem.dma_virt, AES_BLOCK_SIZE);

    if (0 != memcmp(mem.dma_virt, gold_enc, AES_BLOCK_SIZE))
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_INIT);
        ret = HI_ERR_CIPHER_FAILED_INIT;
        goto exit;
    }

exit:
    crypto_mem_destory(&mem);
    symc_hard_channel[chn].open = HI_FALSE;

    return ret;
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

    sec.u32 = SYMC_READ(REG_SEC_CHN_CFG);

    /* change the secure type of chn0 */
    sec.bits.sec_chn_cfg ^= 0x01;
    SYMC_WRITE(REG_SEC_CHN_CFG, sec.u32);

    /* read the secure type of chn0 */
    tmp.u32 = SYMC_READ(REG_SEC_CHN_CFG);

    if (tmp.bits.sec_chn_cfg == sec.bits.sec_chn_cfg)
    {
        /* The REG_SEC_CHN_CFG only can be set by secure CPU
         * can write the cfg, must be secure CPU
         */
        secure =  HI_TRUE;

        /* recovery the secure type of chn0 */
        sec.bits.sec_chn_cfg ^= 0x01;
        SYMC_WRITE(REG_SEC_CHN_CFG, sec.u32);
    }

    HI_LOG_INFO("secure type: 0x%x\n", secure);

    HI_LOG_FuncExit();
    return secure;
}
#endif

s32 drv_symc_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    if (HI_TRUE == symc_initialize)
    {
        return HI_SUCCESS;
    }

    crypto_memset(&symc_dma, sizeof(symc_dma), 0, sizeof(symc_dma));

    ret = crypto_channel_init(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, sizeof(symc_hard_context));
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, symc channel list init failed\n");
        HI_LOG_PrintFuncErr(crypto_channel_init, ret);
        return ret;
    }

    HI_LOG_INFO("disable symc\n");
    module_disable(CRYPTO_MODULE_ID_SYMC);

    HI_LOG_INFO("enable symc\n");
    module_enable(CRYPTO_MODULE_ID_SYMC);

    HI_LOG_INFO("enable smmu\n");
    module_enable(CRYPTO_MODULE_ID_SMMU);

    HI_LOG_INFO("alloc memory for nodes list\n");
    ret = crypto_mem_create(&symc_dma, SEC_MMZ, "symc_node_list", SYMC_NODE_LIST_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, malloc ddr for symc nodes list failed\n");
        HI_LOG_PrintFuncErr(crypto_mem_create, ret);
        goto __error1;
    }

    HI_LOG_INFO("symc secure channel configure\n");
    drv_symc_enable_secure();

    HI_LOG_INFO("symc entry list configure\n");
    drv_symc_enrty_init(symc_dma);

#ifdef CRYPTO_SMMU_SUPPORT
    HI_LOG_INFO("symc SMMU configure\n");
    drv_symc_smmu_int_disable();
    drv_symc_smmu_bypass();
    drv_symc_smmu_base_addr();
#endif

#ifdef CRYPTO_OS_INT_SUPPORT

#ifdef CRYPTO_SMMU_SUPPORT
    drv_symc_smmu_int_enable();
#endif

    HI_LOG_INFO("symc interrupt configure\n");
    drv_symc_set_interrupt();

    HI_LOG_INFO("symc register interrupt function\n");
    ret = drv_symc_register_interrupt();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, register interrupt failed\n");
        HI_LOG_PrintFuncErr(drv_symc_register_interrupt, ret);
        crypto_mem_destory(&symc_dma);
        goto __error1;
    }
#endif

    symc_initialize = HI_TRUE;

    /* because can't reset hardware under tee environment
     * the low channel(1 or 2) may be used by boot or loader,
     * DRV_CIPHER_Init() will change the address of first node list,
     * this may occur a hardware error to analyse address,
     * so here need to start anther channel to computing once,
     * it will force the hardware re-read the address of first node list
     */
    ret = drv_cipher_aes_test();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncWar(drv_cipher_aes_test, ret);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

__error1:
    module_disable(CRYPTO_MODULE_ID_SMMU);
    module_disable(CRYPTO_MODULE_ID_SYMC);
    crypto_channel_deinit(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX);

    symc_initialize = HI_FALSE;

    HI_LOG_FuncExit();

    return ret;
}

s32 drv_symc_deinit(void)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);

    crypto_mem_destory(&symc_dma);

    module_disable(CRYPTO_MODULE_ID_SYMC);
    module_disable(CRYPTO_MODULE_ID_SMMU);

    crypto_channel_deinit(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX);

#ifdef CRYPTO_OS_INT_SUPPORT
    drv_symc_unregister_interrupt();
#endif

    symc_initialize = HI_FALSE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_resume(void)
{
    HI_LOG_FuncEnter();

    HI_LOG_INFO("enable symc\n");
    module_enable(CRYPTO_MODULE_ID_SYMC);
    module_enable(CRYPTO_MODULE_ID_SMMU);
    module_disable(CRYPTO_MODULE_ID_SM4);

    /* must be called before set register of
     - interrupt
     - channel
     */
    drv_symc_enable_secure();

#ifdef CRYPTO_SMMU_SUPPORT
    drv_symc_smmu_int_disable();
    drv_symc_smmu_bypass();
    drv_symc_smmu_base_addr();
#endif

#ifdef CRYPTO_OS_INT_SUPPORT
#ifdef CRYPTO_SMMU_SUPPORT
    drv_symc_smmu_int_enable();
#endif
    drv_symc_set_interrupt();
#endif

    drv_symc_enrty_init(symc_dma);

    HI_LOG_FuncExit();
    return HI_SUCCESS;

}

void drv_symc_suspend(void)
{
    HI_LOG_FuncEnter();

    module_disable(CRYPTO_MODULE_ID_SYMC);
    module_disable(CRYPTO_MODULE_ID_SMMU);

    HI_LOG_FuncExit();
    return ;
}

s32 drv_symc_alloc_chn(u32 *chn_num, CRYP_CIPHER_TYPE_E type)
{
    s32 ret = HI_FAILURE;
    u32 list = 0;
    u32 chn = 0;
    u32 resume = HI_FALSE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);

#ifdef RESERVED_NONSEC_CHANNEL_SUPPORT
    if (HI_UNF_CIPHER_TYPE_NONSEC == type)
    {
        chn = CIPHER_HARD_CHANNEL_CNT;
        if (HI_TRUE == symc_hard_channel[chn].open)
        {
            HI_LOG_ERROR("non secure channel is busy\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_BUSY);
            return HI_ERR_CIPHER_BUSY;
        }
        symc_hard_channel[chn].open = HI_TRUE;
        ret = HI_SUCCESS;
    }
    else
    {
        ret = crypto_channel_alloc(symc_hard_channel, CIPHER_HARD_CHANNEL_CNT,
            CIPHER_HARD_CHANNEL_MASK, &chn);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(crypto_channel_alloc, ret);
            return ret;
        }
    }
#else
    ret = crypto_channel_alloc(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX,
        CIPHER_HARD_CHANNEL_MASK, &chn);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(crypto_channel_alloc, ret);
        return ret;
    }
#endif

    /* hardware may be unexpected reset by other module or platform,
     * such as unexpected reset by fastboot after load tee image,
     * in this case, the hardware configuration will be reset,
     * here try to re-config the hardware.
     */
    list = SYMC_READ(REG_CHANn_SRC_LST_SADDR(chn));

#ifdef CRYPTO_SMMU_SUPPORT
    {
        u32 base = 0;

        if (crypto_is_sec_cpu())
        {
            base = SMMU_READ(REG_MMU_SCB_TTBR);
        }
        else
        {
            base = SMMU_READ(REG_MMU_CB_TTBR);
        }
        if ((0 == list) || (0 == base))
        {
            resume = HI_TRUE;
        }
    }
#else
    if (0 == list)
    {
        resume = HI_TRUE;
    }
#endif

    if (HI_TRUE == resume)
    {
        /* smmu base address or node list address is zero
         * means hardware be unexpected reset
         */
        HI_LOG_WARN("cipher module is not ready, try to resume it now...\n");
        ret = drv_symc_resume();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_symc_resume, ret);
            return ret;
        }
    }

    *chn_num = chn;
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_symc_free_chn(u32 chn_num)
{
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("crypto channel get context failed.\n");
        return;
    }

    if (HI_NULL != ctx->destory)
    {
        ctx->destory();
        ctx->destory = HI_NULL;
    }

    crypto_channel_free(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, chn_num);

    HI_LOG_FuncExit();
    return;
}

void drv_symc_set_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD], u32 ivlen, u32 flag)
{
    u32 i;
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_UNUSED(ivlen);

    ctx = crypto_channel_get_context(symc_hard_channel,
            CRYPTO_HARD_CHANNEL_MAX, chn_num);
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("crypto channel get context failed,ctx is null!\n");
        return;
    }

    /*copy iv data into channel context*/
    for (i=0; i<SYMC_IV_MAX_SIZE_IN_WORD; i++)
    {
        ctx->iv[i] = iv[i];
        HI_LOG_DEBUG("IV[%d] 0x%x\n", i, iv[i]);
    }
    ctx->iv_flag = flag;

    HI_LOG_INFO("iv_flag 0x%x\n", flag);

    HI_LOG_FuncExit();
    return;
}

void drv_symc_get_iv(u32 chn_num, u32 iv[SYMC_IV_MAX_SIZE_IN_WORD])
{
    u32 i;

    HI_LOG_FuncEnter();

    for (i=0; i<SYMC_IV_MAX_SIZE_IN_WORD; i++)
    {
        iv[i] = SYMC_READ(REG_CHAN_CIPHER_IVOUT(chn_num) + i * 4);
    }

    HI_LOG_FuncExit();
    return;
}

void drv_symc_set_key(u32 chn_num, u32 key[SYMC_KEY_MAX_SIZE_IN_WORD], u32 odd)
{
    u32 i;

    HI_LOG_FuncEnter();

    /* unsupport odd key */
    if (odd)
    {
        return;
    }

    for (i=0; i<SYMC_KEY_MAX_SIZE_IN_WORD; i++)
    {
        SYMC_WRITE(REG_CIPHER_KEY(chn_num) + i * 4, key[i]);
        HI_LOG_DEBUG("KEY[%d] 0x%x\n", i, key[i]);
    }

    HI_LOG_FuncExit();
    return;
}

void drv_symc_set_sm1_sk(u32 chn_num, u32 key[SYMC_SM1_SK_SIZE_IN_WORD])
{
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(key);
    return;
}

s32 drv_symc_add_inbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage)
{
    symc_entry *entry = HI_NULL;
    u32 *node_iv = HI_NULL;
    symc_hard_context *ctx = HI_NULL;
    u32 iv_flag = HI_FALSE;
    u32 length = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    HI_LOG_CHECK_PARAM(0 == buf_size);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    CRYPTO_ASSERT(HI_NULL != ctx);
    CRYPTO_ASSERT(SYMC_MAX_LIST_NUM > ctx->cnt);
    CRYPTO_ASSERT(SYMC_MAX_LIST_NUM > ctx->id_in);
    CRYPTO_ASSERT(SYMC_MAX_LIST_NUM > ctx->id_out);

    /* split the buf to mutlit node, as the max length of one node is 1M-16*/
    while(buf_size > 0)
    {
        if (SYMC_MAX_LIST_NUM < ctx->cnt)
        {
            HI_LOG_ERROR("node count %d overflow, max %d\n",  ctx->cnt, SYMC_MAX_LIST_NUM);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_OVERFLOW);
            return HI_ERR_CIPHER_OVERFLOW;
        }

        if (MAX_NODE_SIZE < buf_size)
        {
            length = MAX_NODE_SIZE;
        }
        else
        {
            length = buf_size;
        }
        entry = &ctx->entry_in[ctx->id_in];
        node_iv = ctx->entry_iv[ctx->id_in].iv;
        iv_flag = HI_FALSE;

        /*set dma addr and size, only support 32bit ddr*/
        entry->phy_addr = ADDR_L32(buf_phy);
        entry->length = length;

        /*set flag*/
        entry->flags = SYMC_BUF_LIST_FLAG_DUMM | SYMC_BUF_LIST_FLAG_EOL;

        HI_LOG_INFO("add inbuf, chn %d, id %d, addr 0x%x, length 0x%x, iv_flag %d\n",
            chn_num, ctx->id_in, entry->phy_addr, entry->length, ctx->iv_flag);

        /*first node must set iv except ecb mode*/
        if (CIPHER_IV_CHANGE_ONE_PKG == ctx->iv_flag)
        {
            iv_flag = HI_TRUE;

            /* don't set iv any more*/
            ctx->iv_flag = 0;
        }
        else if (CIPHER_IV_CHANGE_ALL_PKG == ctx->iv_flag)
        {
            iv_flag = HI_TRUE;
        }

        /* set iv to node */
        if (iv_flag)
        {
            entry->flags |= SYMC_BUF_LIST_FLAG_IVSET;
            node_iv[0] = ctx->iv[0];
            node_iv[1] = ctx->iv[1];
            node_iv[2] = ctx->iv[2];
            node_iv[3] = ctx->iv[3];
            HI_LOG_DEBUG("iv[0] 0x%x\n", node_iv[0]);
            HI_LOG_DEBUG("iv[1] 0x%x\n", node_iv[1]);
            HI_LOG_DEBUG("iv[2] 0x%x\n", node_iv[2]);
            HI_LOG_DEBUG("iv[3] 0x%x\n", node_iv[3]);
        }

        /* move to next node, reset to zero if overflow*/
        ctx->id_in++;
        if (SYMC_MAX_LIST_NUM == ctx->id_in)
        {
            ctx->id_in = 0;
        }

        /* total count of computed nodes add 1*/
        ctx->cnt++;

        ADDR_L32(buf_phy) += length;
        buf_size -= length;
    }
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_add_outbuf(u32 chn_num, compat_addr buf_phy, u32 buf_size, symc_node_usage usage)
{
    symc_entry *entry = HI_NULL;
    symc_hard_context *ctx = HI_NULL;
    u32 length = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    HI_LOG_CHECK_PARAM(0 == buf_size);

    CRYPTO_UNUSED(usage);

    ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("crypto channel get context failed,ctx is null!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    /* split the buf to mutlit node, as the max length of one node is 1M-16*/
    while(buf_size > 0)
    {
        if (MAX_NODE_SIZE < buf_size)
        {
            length = MAX_NODE_SIZE;
        }
        else
        {
            length = buf_size;
        }
        entry = &ctx->entry_out[ctx->id_out];

        /*set dma addr and size, only support 32bit ddr*/
        entry->phy_addr = ADDR_L32(buf_phy);
        entry->length = length;

        HI_LOG_INFO("add outbuf, chn %d, id %d, addr 0x%x, length 0x%x\n",
            chn_num, ctx->id_out, entry->phy_addr, entry->length);

        /*set flag*/
        entry->flags = SYMC_BUF_LIST_FLAG_DUMM | SYMC_BUF_LIST_FLAG_EOL;

        /*move to next node, reset to zero if overflow*/
        ctx->id_out++;
        if (SYMC_MAX_LIST_NUM == ctx->id_out)
        {
            ctx->id_out = 0;
        }

        ADDR_L32(buf_phy) += length;
        buf_size -= length;
    }
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_aead_ccm_add_n(u32 chn_num,  u8 *n)
{
    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(n);

    CRYPTO_ASSERT(0);

    HI_LOG_FuncExit();

    return HI_FAILURE;
}

s32 drv_aead_ccm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size)
{
    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(buf_phy);
    CRYPTO_UNUSED(buf_size);

    CRYPTO_ASSERT(0);

    HI_LOG_FuncExit();

    return HI_FAILURE;
}

s32 drv_aead_gcm_add_a(u32 chn_num, compat_addr buf_phy, u32 buf_size)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(buf_phy);
    CRYPTO_UNUSED(buf_size);

    CRYPTO_ASSERT(0);

    HI_LOG_FuncExit();

    return HI_FAILURE;
}

s32 drv_aead_get_tag(u32 chn_num, u32 *tag)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(tag);

    CRYPTO_ASSERT(0);

    HI_LOG_FuncExit();

    return HI_FAILURE;
}

s32 drv_aead_gcm_add_clen(u32 chn_num, u8 *clen)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(clen);

    CRYPTO_ASSERT(0);

    HI_LOG_FuncExit();

    return HI_FAILURE;
}

void drv_symc_add_buf_usage(u32 chn_num, u32 in, symc_node_usage usage)
{
    CRYPTO_UNUSED(chn_num);
    CRYPTO_UNUSED(in);
    CRYPTO_UNUSED(usage);
}

s32 drv_symc_node_check(symc_alg alg, symc_mode mode,
                    u32 klen, u32 block_size,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num)
{
    u32 i;
    u32 tail = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(0 != block_size);

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_UNUSED(alg);
    CRYPTO_UNUSED(mode);
    CRYPTO_UNUSED(klen);
    CRYPTO_UNUSED(input);
    CRYPTO_UNUSED(output);
    CRYPTO_UNUSED(usage_list);

    for (i = 0; i < pkg_num; i++)
    {
        HI_LOG_DEBUG("node %d, length 0x%x\n", i, length[i]);
        if (0 != (length[i] % block_size))
        {
             /* The last block of CTR mode don't need align with block size,
              * but the hardware require the data size must align with block size,
              * as the MMZ/MMU size is align with page size(4K) by system,
              * here we can increase the last block size to align with block size.
              */
             if ((SYMC_MODE_CTR == mode) && (i == pkg_num - 1))
             {
                 tail = length[i] % block_size;
                 if ( 0x00 != tail)
                 {
                    length[i] += block_size - tail;
                 }
             }
             else
             {
                 HI_LOG_ERROR("error, node length must be multiple of block size %d.\n",block_size);
                 HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_LENGTH);
                 return HI_ERR_CIPHER_INVALID_LENGTH;
             }
        }

        /* each node length can't be zero*/
        if (0 == length[i])
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
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_config(u32 chn_num, symc_alg alg, symc_mode mode, symc_width width,
            u32 decrypt, u32 sm1_round_num, symc_klen klen, u32 hard_key)
{
    U_CHANn_CIPHER_CTRL ctrl;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    HI_LOG_CHECK_PARAM(SYMC_ALG_AES < alg);
    HI_LOG_CHECK_PARAM(SYMC_MODE_CTR < mode);
    HI_LOG_CHECK_PARAM(SYMC_KEY_LEN_COUNT <= klen);

    CRYPTO_UNUSED(sm1_round_num);

    ctrl.u32 = SYMC_READ(REG_CHANn_CIPHER_CTRL(chn_num));

    ctrl.bits.decrypt = decrypt;
    ctrl.bits.mode = mode;
    ctrl.bits.alg_sel = alg;
    ctrl.bits.width = width;
    ctrl.bits.key_length = klen;
    ctrl.bits.key_sel = hard_key;
    ctrl.bits.key_adder = chn_num;
    ctrl.bits.weight = 1;

    SYMC_WRITE(REG_CHANn_CIPHER_CTRL(chn_num), ctrl.u32);
    HI_LOG_INFO("REG_CHANn_CIPHER_CTRL[%d] 0x%x\n", chn_num, ctrl.u32);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_set_isr_callback(u32 chn_num, callback_symc_isr callback, void *ctx)
{
    symc_hard_context *hisi_ctx = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    hisi_ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    if (HI_NULL == hisi_ctx)
    {
        HI_LOG_ERROR("crypto channel get context failed,hisi_ctx is null!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    hisi_ctx->callback = callback;
    hisi_ctx->ctx = ctx;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_start(u32 chn_num)
{
    symc_hard_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);
    ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    CRYPTO_ASSERT(HI_NULL != ctx);
    CRYPTO_ASSERT(0x01 <= ctx->cnt);

    HI_LOG_INFO("symc start, chn %d, cnt %d\n", chn_num, ctx->cnt);

    ctx->done = HI_FALSE;

    /* read last used channel */
    SYMC_WRITE(REG_HL_APP_LEN, chn_num);

    /*start work, the count of nodes to be computed is ctx->cnt*/
    SYMC_WRITE(REG_CHANn_INT_OCNTCFG(chn_num), ctx->cnt);
    SYMC_WRITE(REG_CHANn_OBUF_CNT(chn_num), ctx->cnt);

   /* make sure all the above explicit memory accesses and instructions are completed
    * before start the hardware.
    */
    ARM_MEMORY_BARRIER();

    SYMC_WRITE(REG_CHANn_IBUF_CNT(chn_num), ctx->cnt);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_symc_wait_done(u32 chn_num, u32 timeout)
{
    u32 int_valid = 0, int_num = 0;
    u32 i;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(symc_initialize);
    CRYPTO_ASSERT(CRYPTO_HARD_CHANNEL_MAX > chn_num);

    module_get_attr(CRYPTO_MODULE_ID_SYMC, &int_valid, &int_num, HI_NULL);

    HI_LOG_INFO("symc wait done, chn %d\n", chn_num);

#ifdef CRYPTO_OS_INT_SUPPORT
    /* interrupt support, wait irq*/
    if (int_valid)
    {
        symc_hard_context *ctx = HI_NULL;

        ctx = crypto_channel_get_context(symc_hard_channel, CRYPTO_HARD_CHANNEL_MAX, chn_num);
        if (HI_NULL == ctx)
        {
            HI_LOG_ERROR("crypto channel get context failed, ctx is null, chn=%d\n", chn_num);
            HI_LOG_PrintFuncErr(crypto_channel_get_context, HI_ERR_CIPHER_INVALID_POINT);
            return HI_ERR_CIPHER_INVALID_POINT;
        }

        /* wait interrupt */
        ret = crypto_queue_wait_timeout(ctx->queue, ctx->done != HI_FALSE, timeout);
        if (0x00 == ret)
        {
            HI_LOG_ERROR("wait done timeout, chn=%d\n", chn_num);
            HI_LOG_PrintFuncErr(crypto_queue_wait_timeout, HI_ERR_CIPHER_TIMEOUT);
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
        if (timeout <= i)
        {
            HI_LOG_ERROR("symc wait done timeout, chn=%d\n", chn_num);
            HI_LOG_PrintFuncErr(crypto_queue_wait_timeout, HI_ERR_CIPHER_TIMEOUT);
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

    ctx = crypto_channel_get_context(symc_hard_channel,
        CRYPTO_HARD_CHANNEL_MAX, chn_num);
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("crypto channel get context failed, chn=%d\n", chn_num);
        return;
    }

    ctx->destory = destory;

    HI_LOG_FuncExit();
    return;
}

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
void drv_symc_proc_ctrl(symc_chn_status *status, U_CHANn_CIPHER_CTRL ctrl)
{
    status->decrypt = ctrl.bits.decrypt;
    switch(ctrl.bits.alg_sel)
    {
        case CRYP_CIPHER_ALG_DES:
        {
            status->alg = "DES ";
            break;
        }
        case CRYP_CIPHER_ALG_3DES:
        {
            status->alg = "3DES";
            break;
        }
        case CRYP_CIPHER_ALG_AES:
        {
            status->alg = "AES ";
            break;
        }
        default:
        {
            status->alg = "BUTT";
            break;
        }
    }

    switch(ctrl.bits.mode)
    {
        case CRYP_CIPHER_WORK_MODE_ECB:
        {
            status->mode = "ECB ";
            break;
        }
        case CRYP_CIPHER_WORK_MODE_CBC:
        {
            status->mode = "CBC ";
            break;
        }
        case CRYP_CIPHER_WORK_MODE_CFB:
        {
            status->mode = "CFB ";
            break;
        }
        case CRYP_CIPHER_WORK_MODE_OFB:
        {
            status->mode = "OFB ";
            break;
        }
        case CRYP_CIPHER_WORK_MODE_CTR:
        {
            status->mode = "CTR ";
            break;
        }
#ifdef HI_PRODUCT_AEAD_SUPPORT
        case CRYP_CIPHER_WORK_MODE_CCM:
        {
            status->mode = "CCM ";
            break;
        }
        case CRYP_CIPHER_WORK_MODE_GCM:
        {
            status->mode = "GCM ";
            break;
        }
#endif
        default:
        {
            status->mode = "BUTT";
            break;
        }
    }

    if (ctrl.bits.alg_sel == CRYP_CIPHER_ALG_AES)
    {
        switch(ctrl.bits.key_length)
        {
            case CRYP_CIPHER_KEY_AES_128BIT:
            {
                status->klen = AES_KEY_128BIT;
                break;
            }
            case CRYP_CIPHER_KEY_AES_192BIT:
            {
                status->klen = AES_KEY_192BIT;
                break;
            }
            case CRYP_CIPHER_KEY_AES_256BIT:
            {
                status->klen = AES_KEY_256BIT;
                break;
            }
            default:
            {
                status->klen = 0;
                break;
            }
        }
    }
    else if (ctrl.bits.alg_sel == CRYP_CIPHER_ALG_DES)
    {
        status->klen = DES_KEY_SIZE;
    }
    else if (ctrl.bits.alg_sel == CRYP_CIPHER_ALG_3DES)
    {
        switch(ctrl.bits.key_length)
        {
            case CRYP_CIPHER_KEY_DES_3KEY:
            {
                status->klen = TDES_KEY_192BIT;
                break;
            }
            case CRYP_CIPHER_KEY_DES_2KEY:
            {
                status->klen = TDES_KEY_128BIT;
                break;
            }
            default:
            {
                status->klen = 0;
                break;
            }
        }
    }
    else
    {
        status->klen = 0;
    }

    if (ctrl.bits.key_sel)
    {
        status->ksrc = "HW";
    }
    else
    {
        status->ksrc = "SW";
    }

    return;
}

s32 drv_symc_proc_status(symc_chn_status *status)
{
    u32 addr = 0;
    U_CHANn_CIPHER_CTRL ctrl;
    U_INT_RAW stIntRaw;
    U_INT_EN stIntEn;
    u32 val;
    u32 i, j;

    for (i = 0; i < CRYPTO_HARD_CHANNEL_MAX; i++)
    {
        if (HI_TRUE == symc_hard_channel[i].open)
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
            addr = REG_CHANn_CIPHER_CTRL(i);
        }
        else
        {
            addr = REG_CHAN0_CIPHER_CTRL;
        }
        ctrl.u32 = SYMC_READ(addr);
        drv_symc_proc_ctrl(&status[i], ctrl);

        /* get data in */
		if (0 != i)
		{
		    addr = REG_CHANn_SRC_LST_SADDR(i);
		    status[i].inaddr = SYMC_READ(addr);
		}
		else
		{
			status[i].inaddr = REG_CHAN0_CIPHER_DIN;
		}

        /* get data out */
        if (0 != i)
        {
            addr = REG_CHANn_DEST_LST_SADDR(i);
            status[i].outaddr = SYMC_READ(addr);
        }
        else
        {
            status[0].outaddr = REG_CHAN0_CIPHER_DOUT;
        }

        for (j=0; j<4; j++)
        {
            val = SYMC_READ(REG_CHAN_CIPHER_IVOUT(i) + j*4);
            HEX2STR(status[i].iv+j*8, (HI_U8)(val & 0xFF));
            HEX2STR(status[i].iv+j*8+2, (HI_U8)((val >> 8) & 0xFF));
            HEX2STR(status[i].iv+j*8+4, (HI_U8)((val >> 16) & 0xFF));
            HEX2STR(status[i].iv+j*8+6, (HI_U8)((val >> 24) & 0xFF));
        }

        /* get INT RAW status */
        stIntRaw.u32 = SYMC_READ(REG_INT_RAW);
        status[i].inraw= (stIntRaw.bits.chn_ibuf_raw >> i) & 0x1;
        status[i].outraw= (stIntRaw.bits.chn_obuf_raw >> i) & 0x1;

        /* get INT EN status */
        stIntEn.u32 = SYMC_READ(REG_INT_EN);
        status[i].intswitch= stIntEn.bits.sec_int_en;
        status[i].inten= (stIntEn.bits.chn_ibuf_en >> i) & 0x1;
        status[i].outen= (stIntEn.bits.chn_obuf_en >> i) & 0x1;

        /* get INT_OINTCFG */
        addr = REG_CHANn_INT_OCNTCFG(i);
        status[i].outintcnt = SYMC_READ(addr);
    }

    return HI_SUCCESS;
}
#endif
/******* proc function end ********/

void drv_symc_get_capacity(symc_capacity *capacity)
{
    HI_LOG_FuncEnter();

    crypto_memset(capacity, sizeof(symc_capacity), 0,  sizeof(symc_capacity));

    /* AES */
    capacity->aes_ecb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_cbc = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_ofb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_cfb = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_ctr = CRYPTO_CAPACITY_SUPPORT;
    capacity->aes_cts = CRYPTO_CAPACITY_NONSUPPORT;

    /* TDES */
    capacity->tdes_ecb = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_cbc = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_ofb = CRYPTO_CAPACITY_SUPPORT;
    capacity->tdes_cfb = CRYPTO_CAPACITY_SUPPORT;

    /* DES */
    capacity->des_ecb = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_cbc = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_ofb = CRYPTO_CAPACITY_SUPPORT;
    capacity->des_cfb = CRYPTO_CAPACITY_SUPPORT;

    HI_LOG_FuncExit();

    return;
}

/** @}*/  /** <!-- ==== API Code end ====*/

#endif //End of CHIP_SYMC_VER_V100
