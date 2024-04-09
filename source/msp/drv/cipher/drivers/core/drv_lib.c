/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_lib.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_trng.h"

/*********************** Internal Structure Definition ***********************/
/** \addtogroup      base type*/
/** @{*/  /** <!-- [base]*/

/*crg register addr size*/
#define CRG_REG_ADDR_SIZE                       (0x100)

/*set a bit within a word*/
#undef  SET_BIT
#define SET_BIT(src, bit)        ((src) |= (1<<bit))

/*clear a bit within a word*/
#undef  CLEAR_BIT
#define CLEAR_BIT(src,bit)       ((src) &= ~(1<<bit))

/*! module already initialize or not */
static u32 module_initialize = HI_FALSE;

/*! \struct resource_channel
 * the tbale of base info of module, such as addr/reset/clk/ver.
*/
struct sys_arch_hardware_info
{
    /*the name of module, used for debug print and request interrupt*/
    const char *name;

    /*smoe field may be needn't to used*/
    u32 reset_valid: 1; /*bis[0], reset availability, 0-valid, 1-invalid*/
    u32 clk_valid: 1;   /*bis[1], clock availability, 0-valid, 1-invalid*/
    u32 phy_valid: 1;   /*bis[2], system address availability, 0-valid, 1-invalid*/
    u32 crg_valid: 1;   /*bis[3], CRG availability, 0-valid, 1-invalid*/
    u32 ver_valid: 1;   /*bis[4], version reg availability, 0-valid, 1-invalid*/
    u32 int_valid: 1;   /*bis[5], interrupt availability, 0-valid, 1-invalid*/
    u32 res_valid: 25;  /*bis[6..31]*/

    /*module base addr*/
    u32 reg_addr_phy;

    /*base logic addr size*/
    u32 reg_addr_size;

    /*crg register addr, which provide the switch of reset and clock*/
    u32 crg_addr_phy;

    /*the clk switch bit index within the crg register,
     *if the switch bis is provided by second crg register, you need to add 32*/
    u32 clk_bit: 8;

    /*the reset switch bit index within the crg register,
     * if the switch bis is provided by second crg register, you need to add 32*/
    u32 reset_bit: 8;

    /*the interrupt number*/
    u32 int_num: 8;

    /*the reserve bits*/
    u32 res: 8;

    /*the offset of version register*/
    u32 version_reg;

    /*the value of version register, you can used it to check the active module*/
    u32 version_val;

    /*cpu address of module register*/
    void *reg_addr_via;

    /*cpu address of crg register*/
    void *crg_addr_via;
};

static struct sys_arch_hardware_info hard_info_table[CRYPTO_MODULE_ID_CNT] =
{
    HARD_INFO_CIPHER,
    HARD_INFO_CIPHER_KEY,
    HARD_INFO_HASH,
    HARD_INFO_IFEP_RSA,
    HARD_INFO_SIC_RSA,
    HARD_INFO_TRNG,
    HARD_INFO_SM2,
    HARD_INFO_SM4,
    HARD_INFO_SMMU,
};

#ifdef CRYPTO_SWITCH_CPU
static struct sys_arch_hardware_info nsec_hard_info_table[CRYPTO_MODULE_ID_CNT] =
{
    NSEC_HARD_INFO_CIPHER,
    NSEC_HARD_INFO_CIPHER_KEY,
    NSEC_HARD_INFO_HASH,
    NSEC_HARD_INFO_IFEP_RSA,
    NSEC_HARD_INFO_SIC_RSA,
    NSEC_HARD_INFO_TRNG,
    NSEC_HARD_INFO_SM2,
    NSEC_HARD_INFO_SM4,
    NSEC_HARD_INFO_SMMU,
};

static u32 s_secure_cpu = HI_FALSE;
#endif

compat_addr compat_addr_zero = {.phy = 0};

extern u32 drv_symc_is_secure(void);

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      base*/
/** @{*/  /** <!--[base]*/

static s32 module_addr_map_reg(void)
{
    u32 i;
    u32 ret = HI_SUCCESS;
    struct sys_arch_hardware_info *table = HI_NULL;

    HI_LOG_FuncEnter();

    if (HI_TRUE == module_initialize)
    {
        return HI_SUCCESS;
    }

    for (i = 0; i < CRYPTO_MODULE_ID_CNT; i++)
    {
        table = &hard_info_table[i];

        HI_LOG_INFO("[%d] %s\n", i, table->name);

        /*io remap crg register*/
        if (table->crg_valid)
        {
            table->crg_addr_via = crypto_ioremap_nocache(table->crg_addr_phy, CRG_REG_ADDR_SIZE);
            if (table->crg_addr_via == HI_NULL)
            {
                HI_LOG_ERROR("iomap reg of module failed\n");
                module_addr_unmap();
                ret = HI_FAILURE;
                break;
            }
            HI_LOG_INFO("crg phy 0x%x, via 0x%p\n", table->crg_addr_phy, table->crg_addr_via);
        }

        /*io remap module register*/
        if (table->phy_valid)
        {
            table->reg_addr_via = crypto_ioremap_nocache(table->reg_addr_phy,
                table->reg_addr_size);
            if (table->reg_addr_via == HI_NULL)
            {
                HI_LOG_ERROR("iomap reg of module failed\n");
                module_addr_unmap();
                ret = HI_FAILURE;
                break;
            }
            HI_LOG_INFO("reg phy 0x%x, via 0x%p, size 0x%x\n", table->reg_addr_phy,
                table->reg_addr_via, table->reg_addr_size);
        }
    }

    module_initialize = HI_TRUE;

    HI_LOG_FuncExit();

    return ret;
}

/**
\brief  unmap the physics addr to cpu within the base table, contains the base addr and crg addr.
*/
s32 module_addr_unmap(void)
{
    u32 i;
    struct sys_arch_hardware_info *table = HI_NULL;

    HI_LOG_FuncEnter();

    if (HI_FALSE == module_initialize)
    {
        return HI_SUCCESS;
    }

    for (i = 0; i<CRYPTO_MODULE_ID_CNT; i++)
    {
        table = &hard_info_table[i];

        HI_LOG_INFO("[%d] %s\n", i, table->name);

        /*io unmap crg register*/
        if (table->crg_valid && table->crg_addr_via)
        {
            HI_LOG_INFO("crg via addr 0x%p\n", table->crg_addr_via);
            crypto_iounmap(table->crg_addr_via, CRG_REG_ADDR_SIZE);
            table->crg_addr_via = HI_NULL;
        }

        /*io unmap module register*/
        if (table->phy_valid && table->reg_addr_via)
        {
            HI_LOG_INFO("reg via addr 0x%p\n", table->reg_addr_via);
            crypto_iounmap(table->reg_addr_via, table->reg_addr_size);
            table->reg_addr_via = HI_NULL;
        }
    }

    module_initialize = HI_FALSE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief  map the physics addr to cpu within the base table, contains the base addr and crg addr.
*/
s32 module_addr_map(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = module_addr_map_reg();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(module_addr_map_reg, ret);
        return ret;
    }

#ifdef CRYPTO_SWITCH_CPU
    s_secure_cpu = drv_symc_is_secure();
    if (HI_TRUE == s_secure_cpu)
    {
        /* default secure cpu, do nothing */
        return HI_SUCCESS;
    }

    HI_LOG_INFO("non-secure CPU need to remap reg addr\n");

    /* use non-secure info */
    crypto_memcpy(&hard_info_table, sizeof(hard_info_table),
        &nsec_hard_info_table, sizeof(nsec_hard_info_table));

    /* remap module addr */
    ret = module_addr_unmap();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(module_addr_unmap, ret);
        return ret;
    }
    ret = module_addr_map_reg();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(module_addr_map, ret);
        return ret;
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief  get secure cpu type.
*/
u32 module_get_secure(void)
{
#ifdef CRYPTO_SEC_CPU
    return HI_TRUE;
#elif defined(CRYPTO_SWITCH_CPU)
    return s_secure_cpu;
#else
    return HI_FALSE;
#endif
}

/**
\brief  open clock.
*/
static void module_clock(module_id id, u32 open)
{
    u32 val = 0;
    u32 *addr = HI_NULL;
    struct sys_arch_hardware_info *table = HI_NULL;

    HI_LOG_FuncEnter();

    table = &hard_info_table[id];

    if (table->clk_valid)
    {
        if (HI_NULL == table->crg_addr_via)
        {
            HI_LOG_ERROR("\033[0;1;31m""%s clock failed, crg addr is null\n""\033[0m", table->name);
            return;
        }

        /*open clk, the addr may be need to add 1*/
        addr = table->crg_addr_via;
        addr += table->clk_bit / WORD_BIT_WIDTH;

        val = crypto_read(addr);

        if (open)
        {
            SET_BIT(val, table->clk_bit % WORD_BIT_WIDTH);
        }
        else
        {
            CLEAR_BIT(val, table->clk_bit % WORD_BIT_WIDTH);
        }

        crypto_write(addr, val);

        /*wait hardware clock active*/
        crypto_msleep(1);

        HI_LOG_INFO("%s clock, open   %d, bit %d, phy 0x%x, via 0x%p\n",
            table->name, open, table->clk_bit,
            table->crg_addr_phy, table->crg_addr_via);
    }

    HI_LOG_FuncExit();

    return;
}

static void module_reset(module_id id, u32 enable)
{
    u32 val = 0;
    u32 *addr = HI_NULL;
    u32 expect = 0;
    struct sys_arch_hardware_info *table = HI_NULL;

    HI_LOG_FuncEnter();

    table = &hard_info_table[id];

    if (table->reset_valid)
    {
        if (HI_NULL == table->crg_addr_via)
        {
            HI_LOG_ERROR("\033[0;1;31m""%s reset failed, crg addr is null\n""\033[0m", table->name);
            return;
        }

        /*the addr may be need to add 1*/
        addr = table->crg_addr_via;
        addr += table->reset_bit / WORD_BIT_WIDTH;

        val = crypto_read(addr);

        if (enable)
        {
            SET_BIT(val, table->reset_bit % WORD_BIT_WIDTH);
            expect = 0;
        }
        else
        {
            CLEAR_BIT(val, table->reset_bit % WORD_BIT_WIDTH);
            expect = table->version_val;
        }

        crypto_write(addr, val);

        /*wait hardware reset finish*/
        crypto_msleep(1);

        HI_LOG_INFO("%s reset, enable %d, bit %d, phy 0x%x, via 0x%p\n",
            table->name, enable, table->reset_bit,
            table->crg_addr_phy, table->crg_addr_via);

        /*check the value of version reg to make sure reset success*/
        if (table->ver_valid && table->reg_addr_via)
        {
            val = crypto_read(table->reg_addr_via + table->version_reg);
            if (val != expect)
            {
                HI_LOG_ERROR("\033[0;1;31m""%s reset failed, version reg should be 0x%x but 0x%x\n""\033[0m",
                    table->name, expect, val);
                return;
            }

            HI_LOG_INFO("%s version reg, offset 0x%x, expect val 0x%x, real val 0x%x\n",
                table->name, table->version_reg, expect, val);
        }
    }

    HI_LOG_FuncExit();

    return;
}

/**
\brief  enable a module, open clock  and remove reset signal.
*/
void module_enable(module_id id)
{
    module_clock(id, HI_TRUE);
    module_reset(id, HI_FALSE);
    return;
}

/**
\brief  disable a module, close clock and set reset signal.
*/
void module_disable(module_id id)
{
    module_reset(id, HI_TRUE);
    module_clock(id, HI_FALSE);
    return;
}

/**
\brief  get attribute of module.
*/
void module_get_attr(module_id id, u32 *int_valid, u32 *int_num, const char **name)
{
    *int_valid = hard_info_table[id].int_valid;
    *int_num = hard_info_table[id].int_num;
    if (name)
    {
        *name = hard_info_table[id].name;
    }

    return;
}

/**
\brief  read a register.
*/
u32 module_reg_read(module_id id, u32 offset)
{
    u32 val = 0;
    void *addr = HI_NULL;
    s32 ret = HI_FAILURE;

    CRYPTO_ASSERT(CRYPTO_MODULE_ID_CNT > id);
    HI_LOG_CHECK_PARAM(offset >= hard_info_table[id].reg_addr_size);

    /* tee may be read trng before cipher module init */
    if (HI_NULL == hard_info_table[id].reg_addr_via)
    {
        ret = module_addr_map();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(module_addr_map, ret);
            return 0;
        }
    }

    /*get the absolute address of reg*/
    addr = (u8*)(hard_info_table[id].reg_addr_via) + offset;
    val = crypto_read(addr);

//    HI_LOG_DEBUG("<-[0x%p] = 0x%x\n", addr, val);

    return val;
}

/**
\brief  write a register.
*/
void module_reg_write(module_id id, u32 offset, u32 val)
{
    void *addr = HI_NULL;
    s32 ret = HI_FAILURE;

    /*check if module is valid*/
    if (id >= CRYPTO_MODULE_ID_CNT)
    {
        HI_LOG_ERROR("error, invalid module id %d\n", id);
        return;
    }

    /*check if offset is valid*/
    if (offset >= hard_info_table[id].reg_addr_size)
    {
        HI_LOG_ERROR("error, module %d, reg offset overflow 0x%x\n", id, offset);
        return;
    }

    /* tee may be read trng before cipher module init */
    if (HI_NULL == hard_info_table[id].reg_addr_via)
    {
        ret = module_addr_map();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(module_addr_map, ret);
            return;
        }
    }

    /*get the absolute address of reg*/
    addr = (u8*)hard_info_table[id].reg_addr_via + offset;
    crypto_write(addr, val);

//    HI_LOG_DEBUG("->[0x%p] = 0x%x\n", addr, val);

    return;
}

/**
\brief  Initialize the channel list.
*/
s32 crypto_channel_init(channel_context *ctx, u32 num, u32 ctx_size)
{
    u32 size = 0;
    u32 i = 0;
    u8 *buf = HI_NULL;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_NULL != ctx);

    /* clear context */
    size = sizeof(channel_context) * num;
    crypto_memset(ctx, size, 0, size);

    /* set context buffer */
    if (ctx_size > 0)
    {
        buf = (u8*)crypto_malloc(ctx_size * num);
        if (HI_NULL == buf)
        {
            return HI_ERR_CIPHER_FAILED_MEM;
        }
        crypto_memset(buf, ctx_size * num, 0, ctx_size * num);

        /* the buffer addresss is stored at ctx[0].ctx*/
        for (i=0; i<num; i++)
        {
            ctx[i].ctx = buf;
            buf += ctx_size;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief  denit the channel list.
*/
s32 crypto_channel_deinit(channel_context *ctx, u32 num)
{
    u32 size = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_NULL != ctx);

    /* the buffer addresss is stored at ctx[0].ctx*/
    if (HI_NULL != ctx[0].ctx)
    {
        crypto_free(ctx[0].ctx);
        ctx[0].ctx = HI_NULL;
    }

    /* clear context */
    size = sizeof(channel_context) * num;
    crypto_memset(ctx, size, 0, size);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief  allocate a channel.
*/
s32 crypto_channel_alloc(channel_context *ctx, u32 num, u32 mask, u32 *id)
{
    s32 ret = HI_ERR_CIPHER_BUSY;
    u32 i = 0;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_NULL != ctx);
    CRYPTO_ASSERT(HI_NULL != id);

    for (i=0; i<num; i++)
    {
        /* check the valid channel */
        if (mask & (0x01 << i))
        {
            if (!ctx[i].open) /* found a free channel */
            {
                ret = HI_SUCCESS;
                ctx[i].open = HI_TRUE; /* alloc channel */
                *id = i;
                break;
            }
        }
    }

    if (i == num)
    {
        HI_LOG_ERROR("error, all channels are busy.\n");
    }

    HI_LOG_FuncExit();

    return ret;
}

/**
\brief  free a  channel.
*/
void crypto_channel_free(channel_context *ctx, u32 num, u32 id)
{
    HI_LOG_FuncEnter();

    /*free channel*/
    ctx[id].open = HI_FALSE;

    HI_LOG_FuncExit();
    return;
}

/**
\brief  get the private data of channel.
*/
void *crypto_channel_get_context(channel_context *ctx, u32 num, u32 id)
{
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("crypto_channel_get_context() ctx is HI_NULL\n");
        HI_LOG_PrintErrCode(0);
        return HI_NULL;
    }

    if ((id >= num) || (!ctx[id].open))
    {
        HI_LOG_ERROR("crypto_channel_get_context()- error, id %d, open %d, num %d\n",
            id, ctx[id].open, num);
        HI_LOG_PrintErrCode(0);
        return HI_NULL;
    }

    return ctx[id].ctx;
}

void crypto_memset(void *s, int sn, int val, int n)
{
    if (sn >= n)
    {
        memset(s, val, n);
    }
    else
    {
        HI_LOG_ERROR("error, memset overflow\n");
    }
}

void crypto_memcpy(void* s, int sn, const void* c, int n)
{
    if (sn >= n)
    {
        memcpy(s, c, n);
    }
    else
    {
        HI_LOG_ERROR("error, memcpy overflow\n");
    }
}

void HEX2STR(char buf[2], HI_U8 val)
{
    HI_U8 high, low;

    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;

    if (high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }

    if (low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }

}

void *crypto_calloc(size_t n, size_t size)
{
    void *ptr = HI_NULL;

    ptr = crypto_malloc(n * size);

    if (HI_NULL != ptr)
    {
        crypto_memset(ptr, n * size, 0, n * size);
    }

    return ptr;
}

u32 get_rand(void)
{
    u32 randnum = 0;

    cryp_trng_get_random(&randnum, -1);

    return randnum;
}

/** @}*/  /** <!-- ==== API Code end ====*/
